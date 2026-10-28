# Plugins / MeshPartitionEditor

- module root: `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor`
- headers: 75; symbols: 3046
- symbol kinds: class=83, delegate=4, enum=39, enumerator=124, externvar=17, function=420, macro=36, member=995, namespace=198, prototype=1028, struct=87, typedef=15
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ActionableMessage, CQTest, CoreUObject, DerivedDataCache, DynamicMesh, Engine, Foliage, GeometryAlgorithms, GeometryCore, GeometryFramework, GeometryScriptingEditor, ImageCore, InputCore, LevelEditor, MeshConversion, MeshConversionEngineTypes, MeshDescription, MeshPartitionCompute, ModelingComponentsEditorOnly, ModelingOperators, ModelingToolsEditorMode, NaniteUtilities, PhysicsCore, Projects, RHI, RenderCore, Renderer, SceneOutliner, Slate, SlateCore, SourceControl, StaticMeshDescription, ToolMenus, TypedElementFramework, TypedElementRuntime, UnrealEd, VEUVCore
- PublicDependencyModuleNames: Core, EditorSubsystem, MeshPartition, ModelingComponents

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Internal/MeshPartitionPreviewSceneProxy.h` (Internal)


#### class `UE::MeshPartition::FMegaMeshCustomPreviewSceneProxy`  
`class FMegaMeshCustomPreviewSceneProxy : public FPrimitiveSceneProxy`  
_L25-73_
- inherits: `FPrimitiveSceneProxy`
- L28 _public prototype_ `FMegaMeshCustomPreviewSceneProxy(UPreviewMeshComponent* InComponent);`
- L29 _public prototype_ `virtual ~FMegaMeshCustomPreviewSceneProxy();`
- L31 _public prototype_ `void InitResources(const FMeshData& Mesh);`
- L33 _public prototype_ `virtual void DrawStaticElements(FStaticPrimitiveDrawInterface* PDI) override;`
- L34 _public prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;`
- L37 _public prototype_ `void InitRayTracingGeometry(FRHICommandListBase& RHICmdList);`
- L38 _public prototype_ `virtual bool IsRayTracingRelevant() const override;`
- L39 _public prototype_ `virtual bool HasRayTracingRepresentation() const override;`
- L40 _public prototype_ `virtual void GetDynamicRayTracingInstances(FRayTracingInstanceCollector& Collector) override;`
- L43 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L44 _public prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L45 _public prototype_ `virtual HHitProxy* CreateHitProxies(UPrimitiveComponent* Component, TArray<TRefCountPtr<HHitProxy> >& OutHitProxies) override;`
- L47 _public prototype_ `virtual uint32 GetMemoryFootprint(void) const override;`
- L48 _public prototype_ `uint32 GetAllocatedSize(void) const;`
- L50 _public function_ `FBufferRHIRef GetPositionVertexBufferRHI() const`
- L51 _public function_ `FBufferRHIRef GetTexCoordVertexBufferRHI() const`
- L52 _public function_ `FBufferRHIRef GetIndexBufferRHI() const`
- L53 _public function_ `uint32 GetNumVertices() const`
- L54 _public function_ `uint32 GetNumTriangles() const`
- L55 _public function_ `uint32 GetNumTexCoords() const`
- L56 _public function_ `bool GetUseFullPrecisionUVs() const`
- L59 _private member_ `FLocalVertexFactory VertexFactory;`
- L61 _private member_ `FMaterialRelevance MaterialRelevance;`
- L62 _private member_ `UMaterialInterface* Material = nullptr;`
- L64 _private member_ `FStaticMeshVertexBuffer StaticMeshVertexBuffer;`
- L65 _private member_ `FPositionVertexBuffer PositionVertexBuffer;`
- L66 _private member_ `FColorVertexBuffer ColorVertexBuffer;`
- L68 _private member_ `FDynamicMeshIndexBuffer32 IndexBuffer;`
- L71 _private member_ `FRayTracingGeometry RayTracingGeometry;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Private/MeshPartitionCollisionGeneration.h` (Private)


#### enum `UE::MeshPartition::Collision::ECollisionSimplificationMethod`  
`enum class ECollisionSimplificationMethod`  
_L16-20_
- reflection: `UENUM()`
- L18 _public enumerator_ `Cluster`
- L19 _public enumerator_ `QEM`

#### struct `UE::MeshPartition::Collision::FCollisionSimplificationSettings`  
`struct FCollisionSimplificationSettings`  
_L23-81_
- reflection: `USTRUCT()`
- L32 _public member_ `bool bCutMeshAlongMaterialBoundaries = true;` — `UPROPERTY(EditAnywhere, Category = "Material Boundaries")` — Whether to cut original mesh triangles along physical material boundaries. Otherwise, triangles will be assigned discretely to a material based on the average vertex weights. Note this introduces additional triangles initially, but can create smoother, more-accurate material boundaries that can be better-simplified.
- L36 _public member_ `float MaterialBoundaryCutSnapTolerance = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Material Boundaries", meta = (Units = "cm", EditCondition = bCutMeshAlongMaterialBoundaries))` — When cutting material boundaries, tolerance distance at which to snap material boundary to existing geometry rather than cutting the mesh
- L40 _public member_ `bool bSimplifyCollision = false;` — `UPROPERTY(EditAnywhere, Category = "Simplification", meta = (ToolTip = "Enable collision simplification on the separate collision components"))`
- L43 _public member_ `ECollisionSimplificationMethod SimplifyMethod = ECollisionSimplificationMethod::QEM;` — `UPROPERTY(EditAnywhere, Category = "Simplification")`
- L47 _public member_ `float MaterialBoundaryDistanceTolerance = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Simplification", meta = (Units = "cm", EditCondition = "SimplifyMethod==ECollisionSimplificationMethod::QEM"))` — Constrain how much simplification can move material boundaries away from their original positions
- L51 _public member_ `float ErrorTolerance = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Simplification", meta = (Units = "cm", EditCondition = "SimplifyMethod==ECollisionSimplificationMethod::QEM"))` — If positive, set a geometric error tolerance
- L55 _public member_ `float EdgeLength = -1.f;` — `UPROPERTY(EditAnywhere, Category = "Simplification", meta = (Units = "cm"))` — If positive, set a target edge length
- L60 _public member_ `bool bScaleAccuracyViaNormal = true;` — `UPROPERTY(EditAnywhere, Category = "Simplification")` — Whether to scale requested collision accuracy (error tolerance / edge length) locally based on surface normal's alignment with a target direction (e.g. to favor accuracy on 'walkable' surfaces)
- L64 _public member_ `float LocalAccuracyScale = 2.5f;` — `UPROPERTY(EditAnywhere, Category = "Simplification|ScaleAccuracy", meta = (EditCondition="bScaleAccuracyViaNormal"))` — Scale up the requested accuracy (error metric and/or measured edge length) by up-to this amount for surfaces w/ normal aligned to ScaleAccuracyNormalDirection
- L68 _public member_ `float ScaleToMinNormalAngle = 26.f;` — `UPROPERTY(EditAnywhere, Category = "Simplification|ScaleAccuracy", meta = (EditCondition = "bScaleAccuracyViaNormal", ClampMin = 0, ClampMax = 180, Units = Degrees))` — Min normal alignment angle vs ScaleAccuracyNormalDirection, at which to finish scaling up simplifier accuracy, in degrees
- L72 _public member_ `float ScaleFromMaxNormalAngle = 53.f;` — `UPROPERTY(EditAnywhere, Category = "Simplification|ScaleAccuracy", meta = (EditCondition = "bScaleAccuracyViaNormal", ClampMin=0, ClampMax=180, Units = Degrees))` — Max normal alignment angle vs ScaleAccuracyNormalDirection, at which to start scaling up simplifier accuracy, in degrees
- L76 _public member_ `FVector3d ScaleAccuracyNormalDirection = FVector(0., 0., 1.);` — `UPROPERTY(EditAnywhere, Category = "Simplification|ScaleAccuracy", meta = (EditCondition = "bScaleAccuracyViaNormal"))` — The normal direction that should have highest accuracy
- L79 _public prototype_ `void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const;`

#### struct `UE::MeshPartition::Collision::FMeshToCollisionSettings`  
`struct FMeshToCollisionSettings`  
_L83-98_
- L85 _public member_ `UE::MeshPartition::Collision::FCollisionSimplificationSettings SimplificationSettings;`
- L88 _public member_ `TArray<UE::MeshPartition::FPhysicalMaterialChannel> PhysicalMaterialChannels;` — Physical material channels; vertex weight channels will be translated to per - triangle physical materials via this mapping
- L91 _public member_ `UPhysicalMaterial* DefaultPhysicalMaterial = nullptr;` — Default physical material, to set if channels not found
- L94 _public member_ `bool bFastCook = true;` — Prioritize cooking speed over runtime speed
- L97 _public member_ `bool bDisableActiveEdgePrecompute = true;` — Turn off ActiveEdgePrecompute (This makes cooking faster, but will slow contact generation)

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshPartition` (scope `UE`)
- L13 _namespace_ `namespace Collision` (scope `UE::MeshPartition`)
- L100 _prototype_ `void ConvertMeshToCollisionData(const FMeshData& Mesh, FMeshPartitionCollisionData& CollisionData, const FMeshToCollisionSettings& Settings);` (scope `UE::MeshPartition::Collision`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Private/MeshPartitionModifierTaskGraph.h` (Private)


#### class `UE::MeshPartition::FModifierTaskGraph`  
`class FModifierTaskGraph`  
_L24-152_
- desc: MegaMeshModifierTaskGraph builds a dependency graph to applying mega mesh modifiers in parallel and async. Overlapping modifiers apply in a region serially while respecting their relative type and sub priorities.
- L27 _public prototype_ `FModifierTaskGraph();`
- L28 _public prototype_ `~FModifierTaskGraph();`
- L40 _public prototype_ `Tasks::FTask Execute(FMeshData&& InBaseMesh, const FGuid& InBaseGroupCacheKey, MeshPartition::FModifierGroup&& ModifierGroup, const FTransform& InTransform, TArrayView<const FName> InModifierTypePriorities, const bool bInUseCache = true);` — Builds and launches the task graph from a given set of modifiers and priorities. @param InBaseMesh Mesh to use as the base for modifier applications. Data is moved out of this parameter. @param InBaseGroupCacheKey the cache key of all base modifiers @param InModifiers the list of modifiers to apply to the `InBaseMesh`. @param InTransform Worldspace transform for the final mesh. @param InModifierTypePriorities The ordered list of modifier type priorities. If a modifier type can't be found in this list, it will be given the lowest priority. @param bInUseCache If false, will force the cache to be disabled. @return returns a task that is signalled when the graph execution completes.
- L42 _public prototype_ `bool IsComplete() const;`
- L44 _public prototype_ `void WaitForCompletion();`
- L46 _public function_ `FMeshData& GetResultMesh()`
- L48 _public prototype_ `MeshPartition::FBuildPerfStats GetBuildPerfStats() const;`
- L50 _public prototype_ `void Cancel();`
- L52 _public function_ `bool IsCanceled() const`
- L89 _private prototype_ `void BuildDependencyGraph(TConstArrayView<FName> InModifierTypePriorities);`
- L91 _private prototype_ `void PrepareViewCache();`
- L93 _private prototype_ `void ApplyTaskWriteback(FModifierInstanceTask& InTask);`
- L95 _private prototype_ `void OnTaskCompleted(int TaskIndex);`
- L98 _private prototype_ `void OnGraphCompleted();` — Called asynchronously when the full graph has completed execution
- L101 _private prototype_ `void LogDotGraph();`
- L103 _private prototype_ `void ValidateInstanceOutputsForDeterminism(FModifierInstanceTask& InTask);`
- L107 _private member_ `FGuid BaseGroupKey;` — Hash of the guids for all the bases running through the graph
- L109 _private member_ `MeshPartition::FModifierGroup Group;`
- L112 _private member_ `MeshPartition::FModifierGraphCache::FBaseGroupViewCacheData ActiveGroupCacheData;` — Local working copy of cache data for the base group currently being operated on
- L115 _private member_ `TArray<FModifierInstanceTask> Tasks;` — Complete list of all the tasks, should never be modified during task execution.
- L118 _private member_ `TArray<TArray<FInstanceIndex>> PrerequisiteMap;` — Maps a task id to the list of task ids which must complete before the given task can start.
- L121 _private member_ `TArray<TArray<FInstanceIndex>> DownstreamMap;` — Maps a task id to the list of task ids which are downstream of the task index.
- L124 _private member_ `TArray<FGuid> InstanceViewCacheKeys;` — Cache key of the local view for each modifier instance
- L127 _private member_ `TArray<bool> InstancesReusingCachedViews;` — Maps the modifier instance index to a flag indicating if it can reuse its cached data or not.
- L130 _private member_ `FMeshData Mesh;` — The mesh to which all the modifications are applied
- L132 _private member_ `Tasks::FTask GraphCompleteTask;`
- L135 _private member_ `FSharedPipe MeshPipe;` — Ensures writebacks to the source mesh which need to be exclusive are exclusive, but shared writes and reads can still occur in parallel to each other.
- L138 _private member_ `uint64 ExecuteStartTime = 0;` — Track the execution start time and end time to compute wall clock time
- L139 _private member_ `uint64 ExecuteEndTime = 0;`
- L147 _private member_ `bool bUsingCache = false;` — Determines if this graph is using the cache. This value is set at the moment Execute is called and latched in order to prevent potential race condition if the user sets the flag while the graph is executing asynchronously. It would be bad if the graph starts with caching disabled and then it were suddenly enabled before the graph completed.
- L149 _private member_ `bool bIsCancelled = false;`
- L151 _private prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(MeshAccessDetector);`

#### enum `UE::MeshPartition::FModifierTaskGraph::ETaskState`  
`enum class ETaskState`  
_L55-63_
- L57 _public enumerator_ `Invalid`
- L59 _public enumerator_ `Waiting` — Task is waiting for dependencies to complete execution.
- L61 _public enumerator_ `Active` — Task is active and writing back to the mesh.
- L62 _public enumerator_ `Completed`

#### struct `UE::MeshPartition::FModifierTaskGraph::FModifierInstanceTask`  
`struct FModifierInstanceTask`  
_L65-87_
- L67 _public member_ `ETaskState State = ETaskState::Invalid;`
- L69 _public member_ `FBox WritebackBounds;`
- L71 _public member_ `Tasks::FTaskEvent TriggerEvent;`
- L72 _public member_ `Tasks::FTask BuildViewTask;`
- L73 _public member_ `Tasks::FTask ComputeTask;`
- L74 _public member_ `Tasks::FTask WriteTask;`
- L75 _public member_ `Tasks::FTask CompleteTask;`
- L77 _public member_ `MeshPartition::FMeshView MeshView;`
- L78 _public member_ `FInstanceIndex InstanceIndex;`
- L80 _public member_ `uint64 PerformanceCounter = 0;`
- L83 _public member_ `bool bUsingCachedView = false;` — Determines if, at view build time, this task can reuse the view stored in the cache.
- L86 _public member_ `bool bDebugWasCachePoisoned = false;` — Track if the task's cache entry was explicitly dirtied by a modifier invalidating the work-region (for debug purposes only).

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Private/MeshPartitionOutlinerFilter.h` (Private)


#### class `UE::MeshPartition::FMeshPartitionOutlinerFilter`  
`class FMeshPartitionOutlinerFilter : public FGenericFilter<const ISceneOutlinerTreeItem&>`  
_L10-16_
- inherits: `FGenericFilter<constISceneOutlinerTreeItem&>`
- L13 _public prototype_ `FMeshPartitionOutlinerFilter(TSharedPtr<FFilterCategory> InCategory);`
- L15 _public prototype_ `virtual bool PassesFilter(const ISceneOutlinerTreeItem& InItem) const override;`

#### class `UE::MeshPartition::FBaseModifierFilter`  
`class FBaseModifierFilter : public FGenericFilter<const ISceneOutlinerTreeItem&>`  
_L18-25_
- inherits: `FGenericFilter<constISceneOutlinerTreeItem&>`
- L21 _public prototype_ `FBaseModifierFilter(TSharedPtr<FFilterCategory> InCategory);`
- L23 _public prototype_ `virtual bool PassesFilter(const ISceneOutlinerTreeItem& InItem) const override;`
- L24 _public function_ `virtual bool IsInverseFilter() const override`

#### class `UE::MeshPartition::FBuiltSectionFilter`  
`class FBuiltSectionFilter : public FGenericFilter<const ISceneOutlinerTreeItem&>`  
_L27-34_
- inherits: `FGenericFilter<constISceneOutlinerTreeItem&>`
- L30 _public prototype_ `FBuiltSectionFilter(TSharedPtr<FFilterCategory> InCategory);`
- L32 _public prototype_ `virtual bool PassesFilter(const ISceneOutlinerTreeItem& InItem) const override;`
- L33 _public function_ `virtual bool IsInverseFilter() const override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Private/MeshPartitionPreviewVisualizers.h` (Private)


#### class `UE::MeshPartition::FMeshPreviewVisualizer`  
`class FMeshPreviewVisualizer : public FComponentVisualizer`  
_L13-18_
- inherits: `FComponentVisualizer`
- desc: Visualizer intended to handle clicks on mega mesh preview components, to route the selection to the corresponding base section.
- L16 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* ViewportClient, HComponentVisProxy* VisProxy, const FViewportClick& Click);`
- L17 _public function_ `virtual bool ShouldAutoSelectElementOnHandleClick() const` — we handle selection in VisProxyHandleClick

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Private/Modifiers/MeshPartitionModifierVisualizer.h` (Private)


#### class `UE::MeshPartition::FMegaMeshModifierVisualizer`  
`class FMegaMeshModifierVisualizer : public FComponentVisualizer`  
_L12-16_
- inherits: `FComponentVisualizer`
- desc: Provides an interface for components to visualize themselves when selected in the editor.
- L15 _private prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Private/Modifiers/MeshPartitionSplineCachedData.h` (Private)


#### struct `UE::MeshPartition::FSplineCachedSurfaceData`  
`struct FSplineCachedSurfaceData`  
_L18-30_
- desc: Holds surface patch data that gets generated on a background thread and potentially passed to newly created background threads if that work doesn't change. Also used for debug visualization.
- L20 _public member_ `TSharedPtr<Geometry::FDynamicMesh3> MeshedLoop;`
- L21 _public member_ `TSharedPtr<Geometry::FDynamicMeshAABBTree3> MeshedLoopSpatial;`
- L25 _public member_ `std::atomic<bool> bNeedsInitializing = false;` — In cases where the same cache data is needed for multiple applications, this bool guards it against being initialized more than once.
- L29 _public member_ `std::atomic<bool> bInitializationCompleted = false;` — This is only set to true once the struct is fully initialized. Once true, the struct is not touched (and is therefore safe to use on all threads).

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Geometry` (scope `UE`)
- L11 _typedef_ `template<typename T> class TMeshAABBTree3;` (scope `UE::Geometry`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Private/Modifiers/Ops/MeshPartitionRemeshOp.h` (Private)


#### class `UE::MeshPartition::FMegaMeshRemeshBackgroundOpBase`  
`class FMegaMeshRemeshBackgroundOpBase : public MeshPartition::IModifierBackgroundOp`  
_L12-42_
- inherits: `MeshPartition::IModifierBackgroundOp`
- L16 _public prototype_ `FMegaMeshRemeshBackgroundOpBase(const FName& InOperationName);`
- L17 _public prototype_ `~FMegaMeshRemeshBackgroundOpBase() = default;`
- L19 _public member_ `FBox GlobalBounds;`
- L20 _public member_ `Geometry::FAxisAlignedBox3d LocalCoverage;`
- L21 _public member_ `FTransform ModifierToWorld;`
- L22 _public member_ `bool bComputeNormalSeams;`
- L23 _public member_ `double NormalSeamDotProductThreshold;`
- L24 _public member_ `EMegaMeshRemeshModifierBoundaryMode BoundaryMode;`
- L25 _public member_ `bool bDisallowUnsafeBoundaryEdits;`
- L26 _public member_ `bool bDisallowSafeEditsOutsideCoverage;`
- L27 _public member_ `float TargetEdgeLength;`
- L28 _public member_ `int32 RemeshIterations;`
- L29 _public member_ `float SmoothingStrength;`
- L30 _public member_ `ERemeshSmoothingType SmoothingType;`
- L31 _public member_ `bool bProjectToInputMesh;`
- L33 _public member_ `bool bUseDensityWeightChannel = false;`
- L34 _public member_ `MeshPartition::FChannelName DensityWeightChannelName;`
- L35 _public member_ `float RelativeDensity;`
- L36 _public member_ `bool bUseWeightThreshold = false;`
- L37 _public member_ `float MinWeightThreshold = 0.f;`
- L41 _protected prototype_ `void RemeshROI(FDynamicMesh3& Mesh, const FTransform3d& MegaMeshTransform, const TSet<int32>& TriangleROI) const;`

#### class `UE::MeshPartition::FMegaMeshRemeshBackgroundOp`  
`class FMegaMeshRemeshBackgroundOp : public FMegaMeshRemeshBackgroundOpBase`  
_L45-70_
- inherits: `FMegaMeshRemeshBackgroundOpBase`
- L48 _public prototype_ `FMegaMeshRemeshBackgroundOp(const FName& InOperationName);`
- L49 _public prototype_ `~FMegaMeshRemeshBackgroundOp() = default;`
- L52 _public function_ `static FGuid GetCodeVersionKey()` — Generate a new random guid before submitting any code changes to the op
- L60 _private prototype_ `virtual void GetInstancesInBounds(const FBox& InBounds, TArray<FInstanceInfo>& OutInstanceInfos) const override;`
- L61 _private prototype_ `virtual void ApplyModifications(MeshPartition::FMeshView& InMeshView, const FTransform3d& InTransform, const FInstanceInfo& InInstanceDesc) const override;`
- L66 _private function_ `virtual bool DisableDDCWrite() const override` — Set to true whenever iterating on code changes to prevent any builds including this modifier being picked up by ddc and poisoning the cache/generating lots of unused intermediate data.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Private/Modifiers/Ops/MeshPartitionTessellateOp.h` (Private)


#### class `UE::MeshPartition::FMegaMeshTessellateBackgroundOpBase`  
`class FMegaMeshTessellateBackgroundOpBase : public MeshPartition::IModifierBackgroundOp`  
_L12-45_
- inherits: `MeshPartition::IModifierBackgroundOp`
- L15 _public prototype_ `FMegaMeshTessellateBackgroundOpBase(const FName& InOperationName);`
- L16 _public prototype_ `~FMegaMeshTessellateBackgroundOpBase() = default;`
- L18 _public member_ `FBox LocalBounds;`
- L19 _public member_ `FBox GlobalBounds;`
- L21 _public member_ `bool bUseTargetEdgeLength;`
- L22 _public member_ `int32 TessellationLevel;`
- L23 _public member_ `float TargetEdgeLength;`
- L24 _public member_ `int32 MaxTessellationLevel;`
- L26 _public member_ `bool bUseDensityWeightChannel = false;`
- L27 _public member_ `MeshPartition::FChannelName DensityWeightChannelName;`
- L28 _public member_ `float RelativeDensity;`
- L29 _public member_ `bool bUseWeightThreshold = false;`
- L30 _public member_ `float MinWeightThreshold = 0.f;`
- L32 _public member_ `bool bVertexSmoothing;`
- L33 _public member_ `double SmoothingStrength;`
- L34 _public member_ `int32 PostProcessingIterations;`
- L35 _public member_ `bool bResampleUVs;`
- L36 _public member_ `bool bEdgeFlips;`
- L38 _public member_ `EMegaMeshRemeshModifierTessellateMethod TessellationMethod;`
- L39 _public member_ `FTransform ModifierTransform;`
- L43 _protected prototype_ `void TessellateROI(FDynamicMesh3& Mesh, const FTransform3d& MegaMeshTransform, const TSet<int32>& TriangleROI) const;`
- L44 _protected prototype_ `void PostProcess(FDynamicMesh3& Mesh) const;`

#### class `UE::MeshPartition::FMegaMeshTessellateBackgroundOp`  
`class FMegaMeshTessellateBackgroundOp : public FMegaMeshTessellateBackgroundOpBase`  
_L48-73_
- inherits: `FMegaMeshTessellateBackgroundOpBase`
- L51 _public prototype_ `FMegaMeshTessellateBackgroundOp(const FName& InOperationName);`
- L52 _public prototype_ `~FMegaMeshTessellateBackgroundOp() = default;`
- L55 _public function_ `static FGuid GetCodeVersionKey()` — Generate a new random guid before submitting any code changes to the op
- L63 _private prototype_ `virtual void GetInstancesInBounds(const FBox& InBounds, TArray<FInstanceInfo>& OutInstanceInfos) const override;`
- L64 _private prototype_ `virtual void ApplyModifications(MeshPartition::FMeshView& InMeshView, const FTransform3d& InTransform, const FInstanceInfo& InInstanceDesc) const override;`
- L69 _private function_ `virtual bool DisableDDCWrite() const override` — Set to true whenever iterating on code changes to prevent any builds including this modifier being picked up by ddc and poisoning the cache/generating lots of unused intermediate data.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Private/Modifiers/Ops/MeshPartitionTexturePatchOp.h` (Private)


#### class `UE::MeshPartition::FTexturePatchModifierOp`  
`class FTexturePatchModifierOp : public MeshPartition::IModifierBackgroundOp`  
_L10-128_
- inherits: `MeshPartition::IModifierBackgroundOp`
- L13 _public function_ `FTexturePatchModifierOp(const FName& InOperationName) : MeshPartition::IModifierBackgroundOp(InOperationName)`
- L73 _public member_ `TOptional<FHeightEntry> HeightChannel;`
- L74 _public member_ `TArray<FWeightEntry> WeightChannels;`
- L76 _public member_ `TArray<FBox> GlobalBounds;`
- L77 _public member_ `TArray<FTransform> PatchTransforms;`
- L78 _public member_ `FVector2D UnscaledPatchCoverage;`
- L79 _public member_ `double VerticalPatchExtentUp;`
- L80 _public member_ `double VerticalPatchExtentDown;`
- L82 _public member_ `MeshPartition::ETexturePatchTessellationMode TessellationMode;`
- L83 _public member_ `MeshPartition::ETexturePatchTessellationErrorMode TessellationErrorMode;`
- L84 _public member_ `float TessellationError;`
- L85 _public member_ `float MinimumEdgeLength;`
- L86 _public member_ `float MaximumEdgeLength;`
- L87 _public member_ `float FeatureSensitivity;`
- L88 _public member_ `bool bMeshRegularization;`
- L89 _public member_ `FName DetailAdjustmentChannelName;`
- L91 _public prototype_ `static double GetFalloffAlpha(const FVector2d LocalPatchExtent, const FVector2d Local2DPosition, const FTextureEntry& Entry, const FFalloffData& FalloffData);`
- L93 _public prototype_ `static double ApplyCurve(const FTextureEntry& InTextureEntry, double Value);`
- L96 _public prototype_ `static float GetAlphaValue(const FTextureEntry& InTextureEntry, const FVector2f& InSamplingCoordinates, float Value);` — Gets alpha at sampling coordinates, using appropriate alpha mode
- L98 _public prototype_ `static void PrepFalloffData(const FVector2d& LocalPatchExtent, const FTextureEntry& TextureEntry, FFalloffData& Data);`
- L100 _public prototype_ `virtual void GetInstancesInBounds(const FBox& InBounds, TArray<FInstanceInfo>& OutInstanceInfos) const override;`
- L102 _public prototype_ `virtual void ApplyModifications(MeshPartition::FMeshView& InMeshView, const FTransform3d& InTransform, const FInstanceInfo& InInstanceDesc) const override;`
- L106 _public function_ `static FGuid GetCodeVersionKey()` — Generate a new random guid before submitting any code changes to the op
- L114 _public function_ `virtual bool DisableDDCWrite() const override` — Set to true whenever iterating on code changes to prevent any builds including this modifier being picked up by ddc and poisoning the cache/generating lots of unused intermediate data.
- L118 _private function_ `bool ShouldApplyAdaptiveDisplacement() const`
- L123 _private prototype_ `void ApplyAdaptiveDisplacement(MeshPartition::FMeshView& InMeshView, const FTransform3d& InTransform, const FInstanceInfo& InInstanceDesc) const;`
- L126 _private prototype_ `void ApplyDisplacement(MeshPartition::FMeshView& InMeshView, const FTransform3d& InTransform, const FInstanceInfo& InInstanceDesc) const;`

#### struct `UE::MeshPartition::FTexturePatchModifierOp::FFalloffData`  
`struct FFalloffData`  
_L16-22_
- desc: Falloff-related values per texture, to use in the loop further below
- L18 _public member_ `double ClampedRadius = 0;`
- L19 _public member_ `double ClampedFalloff = 0;`
- L20 _public member_ `FVector2d CornerCenter = FVector2d::Zero();`
- L21 _public member_ `MeshPartition::ETexturePatchFalloffMode FalloffModeToUse = MeshPartition::ETexturePatchFalloffMode::Smooth;`

#### struct `UE::MeshPartition::FTexturePatchModifierOp::FTextureEntry`  
`struct FTextureEntry`  
_L23-49_
- L25 _public function_ `FTextureEntry(TSharedRef<const FChannelFieldData> InFieldData) : FieldData(InFieldData)`
- L30 _public member_ `MeshPartition::ETexturePatchBlendMode BlendMode;`
- L31 _public member_ `double SoftnessParameter;`
- L33 _public member_ `TSharedRef<const FChannelFieldData> FieldData;`
- L35 _public member_ `double ZeroInEncoding;`
- L36 _public member_ `double EncodingScale;`
- L38 _public member_ `MeshPartition::ETexturePatchAlphaMode AlphaMode;`
- L39 _public member_ `double SelfMaskTolerance;`
- L41 _public member_ `TSharedPtr<const FRichCurve> ValueCurve;`
- L42 _public member_ `double ValueCurveOffset;`
- L43 _public member_ `double ValueCurveScale;`
- L45 _public member_ `MeshPartition::ETexturePatchFalloffMode FalloffMode;`
- L46 _public member_ `float FalloffDistance;`
- L47 _public member_ `float CornerRadius;`
- L48 _public member_ `TSharedPtr<const FRichCurve> FalloffCurve;`

#### struct `UE::MeshPartition::FTexturePatchModifierOp::FHeightEntry`  
`struct FHeightEntry : public FTextureEntry`  
_L50-60_
- inherits: `FTextureEntry`
- L52 _public function_ `FHeightEntry(TSharedRef<const FChannelFieldData> InFieldData, TSharedRef<Utils::TAsyncTransform<Geometry::FDisplacementMap>> InDisplacementMap) : FTextureEntry(InFieldData) , DisplacementMap(InDisplacementMap)`
- L58 _public member_ `TSharedRef<Utils::TAsyncTransform<Geometry::FDisplacementMap>> DisplacementMap;`
- L59 _public member_ `FName HeightScaleWeightChannel;`

#### struct `UE::MeshPartition::FTexturePatchModifierOp::FWeightEntry`  
`struct FWeightEntry : public FTextureEntry`  
_L61-71_
- inherits: `FTextureEntry`
- L63 _public function_ `FWeightEntry(TSharedRef<const FChannelFieldData> InFieldData) : FTextureEntry(InFieldData)`
- L68 _public member_ `FName WeightChannelName;`
- L69 _public member_ `bool bApplyHeightMinMaxBlend;`
- L70 _public member_ `double HeightMinMaxBlendDistance;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Private/Modifiers/Tessellation/AdaptiveDisplacement.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)
- L17 _namespace_ `namespace MeshPartition` (scope `UE`)
- L23 _prototype_ `void TessellateAdaptive( Geometry::FDynamicMesh3& Mesh, const FTransform3d& MeshToWorld, const FTransform3d& PatchToWorld, const FVector2D& UnscaledPatchCoverage, const UE::Geometry::FDisplacementMap& DisplacementMap, const float Center,` (scope `UE::MeshPartition`) — Adaptively tessellate the mesh according to specified displacement map, not applying the displacement. Sampling coordinates will be determined from transformed points from mesh to patch space, applying UnscaledPatchCoverage to [-0.5, 0.5]^2 range shifted to [0,1]^2.

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Private/Modifiers/Tessellation/HalfEdgeMesh.h` (Private)


#### class `UE::Geometry::FHalfEdgeMesh`  
`class FHalfEdgeMesh`  
_L24-572_
- desc: Simplistic mesh class with half-edges and edges that provides the interface needed by TParallelAdaptiveRefinement
- L26 _private function_ `FORCEINLINE static uint32 Cycle3(uint32 Value)`
- L34 _public typedef_ `using FIndex3i = UE::Geometry::FIndex3i;`
- L36 _public typedef_ `using RealType = float;`
- L37 _public typedef_ `using VecType = FVector3f;`
- L82 _public prototype_ `void BuildTopology();` — should be called after all triangles have been added
- L84 _public function_ `inline void AddVertex(const FVector3f& Position, const FVector2f& UV, const FVector3f& Normal)`
- L89 _public function_ `inline void AddTriangle(const FIndex3i& Triangle)`
- L94 _public function_ `void ReserveTriangles(const int32 TriangleCount)`
- L101 _public function_ `void ReserveVertices(const int32 VertexCount)`
- L107 _public function_ `[[nodiscard]] FORCEINLINE int32 GetVertexIndex(const int32 TriIndex, const int32 TriEdgeIndex) const`
- L115 _public function_ `[[nodiscard]] FORCEINLINE FIndex3i GetTriangle(const int32 TriIndex) const`
- L127 _public function_ `FORCEINLINE void SetTriangle(const int32 TriIndex, const FIndex3i& Triangle, const int32 ParentTriIndex)`
- L142 _public function_ `[[nodiscard]] FORCEINLINE FIndex3i GetBaseTriangle(const int32 BaseTriangleIndex) const`
- L150 _public function_ `[[nodiscard]] FORCEINLINE FIndex2i GetHalfEdgeVertexIndices(const int32 HalfEdgeIndex) const`
- L156 _public function_ `[[nodiscard]] FORCEINLINE FIndex2i GetEdgeVertexIndices(const int32 EdgeIndex) const`
- L162 _public function_ `FORCEINLINE void GetEdge(const int32 EdgeIndex, FIndex2i& OutVerts, FIndex2i& OutTris) const`
- L172 _public function_ `[[nodiscard]] FORCEINLINE int32 GetEdgeID(const int32 TriIndex, const int32 k) const`
- L177 _public function_ `[[nodiscard]] FORCEINLINE const FVector3f& GetVertexPosition(const int32 TriIndex, const int32 TriEdgeIndex) const`
- L182 _public function_ `[[nodiscard]] FORCEINLINE const FVector3f& GetVertexPosition(const int32 VertexIndex) const`
- L187 _public function_ `[[nodiscard]] FORCEINLINE const FVector2f& GetUV(const int32 VertexIndex) const`
- L192 _public function_ `[[nodiscard]] FORCEINLINE const FVector3f& GetNormal(const int32 VertexIndex) const`
- L197 _public function_ `[[nodiscard]] FORCEINLINE const FVertex& GetVertex(const int32 VertexIndex) const`
- L202 _public function_ `FORCEINLINE void SetVertexPosition(const int32 VertexIndex, const FVector3f Position)`
- L207 _public function_ `FORCEINLINE void GetTriVertices(const int32 TriIndex, FVector3f& v0, FVector3f& v1, FVector3f& v2) const`
- L214 _public function_ `[[nodiscard]] FORCEINLINE int32 MaxVertexID() const`
- L219 _public function_ `[[nodiscard]] FORCEINLINE bool IsValidVertex(const int32 VertexID) const`
- L224 _public function_ `[[nodiscard]] FORCEINLINE int32 MaxTriID() const`
- L229 _public function_ `[[nodiscard]] FORCEINLINE bool IsValidTri(const int32 TriIndex) const`
- L235 _public function_ `[[nodiscard]] FORCEINLINE int32 GetAdjTriangle(const int32 TriIndex, const int32 TriEdgeIndex) const` — Return the triangle index on the other side of the half edge given by TriIndex, TriEdgeIndex or IndexConstants::InvalidID on boundary
- L246 _public function_ `[[nodiscard]] FORCEINLINE TPair<int32,int32> GetAdjEdge(const int32 TriIndex, const int32 TriEdgeIndex) const` — Return (adjacent triangle index or IndexConstants::InvalidID on boundary, adjacent local edge index)
- L259 _public function_ `[[nodiscard]] FORCEINLINE int32 GetAdjHalfEdge(const int32 TriIndex, const int32 TriEdgeIndex) const` — Return the triangle index on the other side of the half edge given by TriIndex, TriEdgeIndex or IndexConstants::InvalidID on boundary
- L264 _public function_ `[[nodiscard]] FORCEINLINE bool EdgeManifoldCheck(const int32 TriIndex, const int32 TriEdgeIndex) const`
- L284 _public function_ `[[nodiscard]] FORCEINLINE bool AllowEdgeFlip(const int32 TriIndex, const int32 TriEdgeIndex, const int32 AdjTriIndex ) const`
- L289 _public function_ `[[nodiscard]] FORCEINLINE bool AllowEdgeSplit(const int32 TriIndex, const int32 TriEdgeIndex ) const`
- L295 _public function_ `[[nodiscard]] FORCEINLINE FVector3f GetTriangleNormal(const int32 TriIndex) const`
- L309 _public function_ `FORCEINLINE int32 AddEdges( int32 EdgesToAdd )`
- L314 _public function_ `FORCEINLINE int32 AddVertices( int32 VerticesToAdd )`
- L320 _public function_ `FORCEINLINE int32 AddTriangles( const int32 TrianglesToAdd )`
- L334 _public function_ `inline void InterpolateVertex(const float Weight, const int32 TargetIdx, const int32 EdgeIndex)` — Interpolate vertex \param TargetIdx along given edge with provided weight (with respect to first half-edge).
- L494 _public function_ `[[nodiscard]] FORCEINLINE int32 HalfEdgeCount() const`
- L499 _public function_ `[[nodiscard]] FORCEINLINE int32 EdgeCount() const`
- L504 _public function_ `[[nodiscard]] FORCEINLINE int32 GetEdgeIndex(int32 TriIndex, int LocalEdgeIndex) const`
- L509 _public function_ `FORCEINLINE void LinkEdge(int32 HalfEdgeIndex0, int32 HalfEdgeIndex1)`
- L518 _public function_ `FORCEINLINE void LinkEdge(int32 HalfEdgeIndex0, int32 HalfEdgeIndex1, int32 EdgeIdx, int32 ParentEdgeIdx)`
- L542 _public function_ `void Unlink(int32 HalfEdgeIndex)`
- L553 _public function_ `int32 GetBaseTriangleIndex(const int32 TriIndex) const`
- L558 _public prototype_ `void CheckConsistency() const;`
- L560 _public prototype_ `void Dump(std::ostream& out) const;`
- L564 _private member_ `TArray<FIndex3i> Triangles;` — triangle as triplets
- L565 _private member_ `TArray<FVertex> Vertices;`
- L566 _private member_ `TArray<FHalfEdge> HalfEdges;`
- L567 _private member_ `TArray<FEdge> Edges;`
- L569 _private member_ `TArray<int32> BaseTriangleIndices;` — triangle to base triangle
- L570 _private member_ `TArray<FIndex3i> BaseTriangles;`
- L571 _private member_ `TArray<FEdge> BaseEdges;`
- L574 _function_ `inline void FHalfEdgeMesh::CheckConsistency() const`
- L600 _function_ `inline void FHalfEdgeMesh::Dump(std::ostream& out) const`

#### struct `UE::Geometry::FHalfEdgeMesh::FHalfEdge`  
`struct FHalfEdge`  
_L39-43_
- L41 _public member_ `int32 AdjHalfEdge;` — neighboring half-edge, winding opposite direction
- L42 _public member_ `int32 Edge;` — shared edge index

#### struct `UE::Geometry::FHalfEdgeMesh::FEdge`  
`struct FEdge`  
_L45-49_
- L47 _public member_ `FIndex2i HalfEdge;` — opposing halfedges. on boundary second halfedge is IndexConstants::InvalidID
- L48 _public member_ `int32 BaseEdge { IndexConstants::InvalidID };`

#### struct `UE::Geometry::FHalfEdgeMesh::FVertex`  
`struct FVertex`  
_L51-79_
- L53 _public member_ `FVector3f Position;`
- L54 _public member_ `FVector2f UV;` — sampling coords
- L55 _public member_ `FVector3f Normal;` — displacement direction
- L56 _public member_ `FVector3f Barycentric;` — barycentric coordinates with respect to base triangle
- L60 _public member_ `int32 BaseHalfEdge { IndexConstants::InvalidID };` — for edges, tracks the base halfedge. for interior vertices, only used to track the base triangle, with respect to which barycentric coordinates are valid
- L63 _public member_ `int32 BaseAdjHalfEdge { IndexConstants::InvalidID };` — neighbor halfedge of the base mesh. InvalidID for interior vertices or boundary vertices
- L66 _public function_ `void Flip()` — swaps the two halfedges and the meaning the barycentric coordinates respectively

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshPartition` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Geometry` (scope `UE`)
- L615 _prototype_ `void ConvertToHalfEdgeMesh(const FDynamicMesh3& Mesh, FHalfEdgeMesh& HalfEdgeMesh);` (scope `UE::Geometry`)
- L617 _prototype_ `void ConvertToDynamicMesh3(const FHalfEdgeMesh& HalfEdgeMesh, const FDynamicMesh3& InputMesh, FDynamicMesh3& RefinedMesh);` (scope `UE::Geometry`)
- L619 _prototype_ `void ConvertToMeshPartitionMesh(const FHalfEdgeMesh& HalfEdgeMesh, const FDynamicMesh3& InputMesh, UE::MeshPartition::FMeshData& OutputMesh);` (scope `UE::Geometry`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Private/Modifiers/Tessellation/MeshPostProcessing.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)
- L17 _prototype_ `void PostProcessMesh(FDynamicMesh3& Mesh, TArray<FVector3d>& Displacements, FDisplaceFunc DisplacementFunctor, const double MinimumEdgeLength, const double MaximumEdgeLength);` (scope `UE::Geometry`) — Improve mesh regularity by splitting long edges, applying Delaunay-flips and volume-preserving mesh smoothing. If the CVar CVarTessellationRemeshingIterations is set, the Remesher is run, using the specified edge lengths as target lengths
- L20 _prototype_ `void RegularizeMesh(FDynamicMesh3& Mesh);` (scope `UE::Geometry`) — Apply volume preserving regularization multiple times, based on CVar MegaMesh.AdaptiveTessellation.RegularizationSteps

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Private/SharedPipe.h` (Private)


#### class `FSharedPipe`  
`class FSharedPipe`  
_L18-175_
- desc: A specialized implementation of `UE::Tasks::FPipe` which supports concurrent readers. The execution of tasks in the FSharedPipe will always be FIFO in the order that the prerequisites are satisfied. FSharedPipe is similar to FRWLock allowing multiple concurrent readers or a single writer however it does so in a non-blocking manner. `LaunchExclusive` behaves much like FPipe::Launch. Exclusive tasks enqueued into the FSharedPipe will never execute concurrently with any other task launched into this pipe. Where FSharedPipe differs from FPipe is the ability to have multiple shared readers for the same resource through the `LaunchShared` function. Shared tasks will execute through the pipe concurrently.
- L29 _public function_ `explicit FSharedPipe(const TCHAR* InDebugName) : DebugName(InDebugName)`
- L34 _public function_ `~FSharedPipe()`
- L39 _public function_ `bool HasWork()`
- L45 _public function_ `template<typename TaskBodyType, typename PrerequisitesCollectionType> UE::Tasks::FTask LaunchExclusive ( const TCHAR* InDebugName, TaskBodyType&& TaskBody, PrerequisitesCollectionType&& Prerequisites, UE::Tasks::ETaskPriority TaskPriority = UE::Tasks::ETaskPriority::Normal, UE::Tasks::EExtendedTaskPriority ExtendedPriority = UE::Tasks::EExtendedTaskPriority::None )`
- L95 _public function_ `template<typename TaskBodyType, typename PrerequisitesCollectionType> UE::Tasks::FTask LaunchShared( const TCHAR* InDebugName, TaskBodyType&& TaskBody, PrerequisitesCollectionType&& Prerequisites, UE::Tasks::ETaskPriority TaskPriority = UE::Tasks::ETaskPriority::Normal, UE::Tasks::EExtendedTaskPriority ExtendedPriority = UE::Tasks::EExtendedTaskPriority::None )`
- L152 _private member_ `UE::FMutex Mutex;`
- L160 _private member_ `UE::Tasks::FTask LastExclusiveTaskInPipe;` — Tail of the linked list of exclusive tasks. When a new exclusive task is pushed into the pipe, we immediately swap the last exclusive task to the new task to ensure that any subsequent tasks are correctly ordered after this one. The task graph's internal prerequisite system manages the rest of the linked list for us.
- L168 _private member_ `TArray<UE::Tasks::FTask> ActiveSharedTasks;` — Retain a list of all currently executing shared tasks. When a new exclusive task is pushed into the pipe, all of these are set as prerequisites for that task to ensure it only begins execution when the currently executing shared tasks have completed. No new shared tasks are launched once this process begins until the exclusive task list completes.
- L170 _private member_ `std::atomic<uint64> TaskCount = { 0 };`
- L172 _private prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(AccessDetector);`
- L174 _private member_ `const TCHAR* DebugName;`

#### enum `FSharedPipe::EExecutionMode`  
`enum EExecutionMode`  
_L20-24_
- L22 _public enumerator_ `Shared`
- L23 _public enumerator_ `Exclusive`

#### Free symbols / members of external scopes

- L59 _function_ `` (scope `FSharedPipe::LaunchExclusive`)
- L75 _function_ `` (scope `FSharedPipe::LaunchExclusive::__anon0e4f8ffc0102`)
- L108 _function_ `` (scope `FSharedPipe::LaunchShared`)
- L128 _function_ `` (scope `FSharedPipe::LaunchShared::__anon0e4f8ffc0302`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionBuildPerfStats.h` (Public)


#### struct `UE::MeshPartition::FPerModifierBuildPerfStats`  
`struct FPerModifierBuildPerfStats`  
_L11-36_
- reflection: `USTRUCT()`
- L15 _public function_ `void AddInstanceStat(double InInstanceExecTime)`
- L25 _public member_ `int32 InstanceCount = 0;` — `UPROPERTY(VisibleAnywhere, Category = MegaMesh, meta=(EditCondition="InstanceCount > 1", EditConditionHides))` — Total number of instances.
- L29 _public member_ `double TotalExecutionTime = 0.;` — `UPROPERTY(VisibleAnywhere, Category = MegaMesh, meta=(DisplayName="Total Execution Time (Seconds)"))` — Accumulated modifier timings across all Instances.
- L32 _public member_ `double MinInstanceExecutionTime = TNumericLimits<double>::Max();` — `UPROPERTY(VisibleAnywhere, Category = MegaMesh, meta=(DisplayName = "Min Instance Exec Time (Seconds)", EditCondition="InstanceCount > 1", EditConditionHides))`
- L35 _public member_ `double MaxInstanceExecutionTime = 0.;` — `UPROPERTY(VisibleAnywhere, Category = MegaMesh, meta=(DisplayName = "Max Instance Exec Time (Seconds)", EditCondition="InstanceCount > 1", EditConditionHides))`

#### struct `UE::MeshPartition::FBuildPerfStats`  
`struct FBuildPerfStats`  
_L39-49_
- reflection: `USTRUCT()`
- L45 _public member_ `double WallTime = 0.;` — `UPROPERTY(VisibleAnywhere, Category = MegaMesh, meta=(DisplayName = "Wall Clock Time (Seconds)"))` — Wall clock time to process all modifiers.
- L48 _public member_ `TMap<FSoftObjectPath, MeshPartition::FPerModifierBuildPerfStats> PerModifierTimings;` — `UPROPERTY(VisibleAnywhere, Category = MegaMesh, meta=(ForceInlineRow))`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionChannelCollection.h` (Public)


#### enum `UE::MeshPartition::EChannelUVUnwrapQuality`  
`enum class EChannelUVUnwrapQuality : uint8`  
_L28-34_
- desc: Quality tier requested for the UV unwrap. Currently only used by the VolumeEncoded method
- L31 _public enumerator_ `Full` — Full-quality unwrap
- L33 _public enumerator_ `Preview` — Lower-quality preset tuned for interactive preview iteration

#### struct `UE::MeshPartition::FVEUVLayoutOptions`  
`struct FVEUVLayoutOptions`  
_L37-45_
- desc: Options specific to the Volume-Encoded UV algorithm
- L40 _public member_ `float SamplesPerSquareMeter = 0.025f;` — Target sample count per square meter of section surface area. Drives FVEUVConfig::Sampling.TotalSamples.
- L42 _public member_ `FIntVector VoxelCount = FIntVector(4, 4, 1);` — Voxel grid dimensions used by the optimizer. Drives FVEUVConfig::VoxelCount.
- L44 _public member_ `bool bAcceptOutputOnFailure = false;` — Ignore VEUV result validation failures and always accept the output; useful for debugging failure cases.

#### struct `UE::MeshPartition::FPlaneProjectionLayoutOptions`  
`struct FPlaneProjectionLayoutOptions`  
_L48-54_
- desc: Options specific to the PlaneProject UV layout method
- L51 _public member_ `EPlaneProjectionNormalSource NormalSource = EPlaneProjectionNormalSource::FixedPlane;` — Whether to project along the section's area-weighted average normal or a fixed direction.
- L53 _public member_ `FVector FixedNormal = FVector(0.0, 0.0, 1.0);` — Plane normal used when NormalSource is FixedPlane. Need not be unit length; normalized at use.

#### struct `UE::MeshPartition::FChannelCollectionUVLayoutOptions`  
`struct FChannelCollectionUVLayoutOptions`  
_L56-70_
- L58 _public prototype_ `static FChannelCollectionUVLayoutOptions GetDefaults();`
- L59 _public prototype_ `static FChannelCollectionUVLayoutOptions GetFromDefinition(const UMeshPartitionDefinition* InDefinition);`
- L61 _public member_ `float TexelSize;`
- L62 _public member_ `int32 MaxTextureResolution;`
- L64 _public member_ `float GutterTexelCount = 4.0f;` — Desired (approx.) texels between UV islands
- L65 _public member_ `EChannelCollectionUVLayoutMethod UVLayoutMethod;`
- L66 _public member_ `EChannelUVUnwrapQuality UVQuality = EChannelUVUnwrapQuality::Full;`
- L69 _public member_ `FPlaneProjectionLayoutOptions PlaneProjection;`

#### struct `UE::MeshPartition::FSectionDomainMapping`  
`struct FSectionDomainMapping`  
_L72-90_
- L74 _public member_ `double TexelSize3D = 100.0;` — Size of one texel in position unit [u] assigned from definition
- L75 _public member_ `int32 MaxImageResolution = 4092;`
- L76 _public member_ `int32 MinImageResolution = 0;`
- L77 _public member_ `int32 ImageResolution = 0;`
- L79 _public member_ `double Area3D = 0;`
- L80 _public member_ `double AreaUV = 0;`
- L82 _public member_ `double Size3D = 0;`
- L83 _public member_ `double SizeUV = 0;`
- L86 _public member_ `float GutterTexelCount = 4.0f;` — Output-texel-space gap between UV islands
- L88 _public function_ `float GetGutterTexelCount() const`
- L89 _public function_ `float GetGutterUV() const`

#### struct `UE::MeshPartition::FSectionChannels`  
`struct FSectionChannels`  
_L92-99_
- L94 _public member_ `TArray<uint8> Table;`
- L95 _public member_ `FVector2f TexcoordMetrics = { 1.0f, 1.0f };`
- L96 _public member_ `TStrongObjectPtr<UTexture> Texture;`
- L97 _public member_ `TOptional<FSectionChannelGenerationMeshData> Mesh;`
- L98 _public member_ `FSectionChannelDomainData Domain;`

#### class `UE::MeshPartition::FChannelTextureRenderer`  
`class FChannelTextureRenderer`  
_L110-220_
- desc: FMegaMeshChannelCollection contains functions and objects needed to build the rendering elements representing the masks and channels for the sections of the mega mesh Each base is assigned an Id in the collection allowing to reference and access other resources associated with it such as individual textures stored in the Texture collection
- L115 _public member_ `static constexpr int32 NumChannelsPerPage = 1;`
- L116 _public member_ `static constexpr float DefaultTexelSize = 100.0f;` — Default texel size (in world unit) driving the channel rasterization resolution
- L117 _public member_ `static constexpr int32 DefaultMaxImageResolution = 4096;` — Default maximum channel texture resolution generated per section
- L127 _public prototype_ `static Tasks::TTask<FSectionChannels> BuildTextureForSection(const FMeshData& InSectionMesh, UObject* InOwner, bool bInDownloadToAsset, const MeshPartition::FChannelMap& InChannels, float InTexelResolution);` — Builds the texture for the different bases contained in a modifier group and their associated modifiers. Will also update the MegaMesh's texture collection. @param InSectionMesh The Section mesh generated by the MeshPartition pipeline containing the Channel information that needs to be rasterized in the channel texture @param InOwner An optional owner for the texture generated (otherwise, it is the ChannelCollection). This is used for compiled section, where the texture generated is directly assigned to its section actor @param bInDownloadToAsset whether to download the mip data from video memory into the UTexture asset. Must be used for serialized compiled sections. @param InChannels Channel to attribute id mapping. @param InTexelSize worldspace size of a texel in the output channel textures.
- L129 _public prototype_ `static Tasks::TTask<FSectionChannels> BuildTextureForSectionWithCachedTopology( const Geometry::FDynamicMesh3& InSectionMesh, const FChannelRenderUVMeshTopology& InCachedTopology, UObject* InOwner, bool bInDownloadToAsset, const MeshPartition::FChannelMap& InChannels);`
- L136 _public prototype_ `static FChannelRenderUVMeshTopology GenerateUVMeshTopology(const Geometry::FDynamicMesh3& InSectionMesh, FVector InScale, float InTexelResolution);`
- L201 _private prototype_ `static UTexture* GetDefaultTexture();`
- L203 _private prototype_ `static void GenerateSectionMeshUVs(const FMeshData& InSectionMesh, FSection& InSection, float InTexelResolution);`
- L204 _private prototype_ `static void GenerateSectionMeshChannels(const FMeshData& InSectionMesh, FSection& InSection, const MeshPartition::FChannelMap& InChannels);`
- L205 _private prototype_ `static void GenerateSectionMeshChannels(const Geometry::FDynamicMesh3& InSectionMesh, FSection& InSection, const MeshPartition::FChannelMap& InChannels);`
- L207 _private prototype_ `static FSection BuildSectionFromCachedTopology(const FChannelRenderUVMeshTopology& InTopology);`
- L209 _private prototype_ `static UTexture* AllocateSectionTextureResource(int32 InSizeX, int32 InSizeY, int32 InArraySize, EPixelFormat InFormat, UObject* InOuter, const FName InName);`
- L210 _private prototype_ `static void RenderSectionChannels(UTexture* InOutSectionTextures, FSection InSection);`
- L211 _private prototype_ `static void DownloadSectionTextureToAsset(UTexture* InAllocatedTexture);`
- L213 _private prototype_ `static Tasks::TTask<TOptional<UTexture*>> LaunchAllocateTextureTask(Tasks::TTask<FSection> InBuildSectionTask, UObject* InOwner);`
- L214 _private prototype_ `static Tasks::TTask<FSectionChannels> LaunchRenderTextureTask(Tasks::TTask<FSection> InBuildSectionTask, Tasks::TTask<TOptional<UTexture*>> InAllocateTextureTask, bool bInDownloadToAsset, bool bInExtractUVSectionMeshData = false);`
- L218 _public prototype_ `static void CreateSectionUVLayout(FMeshData& InOutSectionMesh, const FChannelCollectionUVLayoutOptions& GenerationOptions, const FTransform& OptionalWorldTransform = FTransform::Identity);` — @param OptionalWorldTransform World transform of the associated section, used for debug/visualization tooling

#### struct `UE::MeshPartition::FChannelTextureRenderer::FSection`  
`struct FSection`  
_L150-183_
- desc: Section element A section struct is created for every unique section encountered The section is associated to its Texture slot allocation on the first generation The section UVmesh data is regenerated everytime the section is dirtied because bases or modifiers have been edited The section UVDomain data store the intermediate steps of the mapping algorithm used to unify the uvdomain of each bases into one uv domain for the section The section generated data is cached for efficienty in editor mode. The generated data is useful for debugging and inspection
- L167 _public member_ `FUVMesh UVmesh;`
- L169 _public member_ `TArray<FBox2f> Bases_UVBox;`
- L170 _public member_ `TArray<TArray<int32>> Islands_Bases;`
- L171 _public member_ `TArray<FBox2f> Islands_UVBox;`
- L172 _public member_ `TArray<FBox2f> SectionIslands_UVBox;`
- L173 _public member_ `TArray<FBox2f> FreeRects;`
- L175 _public function_ `int32 NumActivePages() const`
- L177 _public member_ `TArray<uint8> ChannelOffsetTable;`
- L179 _public member_ `FUint32Vector2 RasterResolution;`
- L180 _public member_ `FVector2f TexcoordMetrics;`
- L182 _public member_ `FSectionDomainMapping DomainMapping;`

#### struct `UE::MeshPartition::FChannelTextureRenderer::FSection::FUVMesh`  
`struct FUVMesh`  
_L152-166_
- L154 _public member_ `TArray<FInt32Vector2> BaseIndicesRanges;`
- L155 _public member_ `TArray<int32> Indices;`
- L156 _public member_ `TArray<FVector2f> UVs;`
- L157 _public member_ `TArray<FInt32Vector3> Outlines;`
- L158 _public member_ `TArray<float> Channels;`
- L159 _public member_ `TArray<int32> ChannelActiveCounts;`
- L160 _public member_ `TArray<uint8> ActiveChannelIndices;`
- L161 _public member_ `TArray<int32> UVElementToVertexID;`
- L162 _public member_ `int32 VertexCount;`
- L164 _public function_ `int32 NumIndices() const`
- L165 _public function_ `int32 NumChannels() const`

#### struct `UE::MeshPartition::FChannelTextureRenderer::FChannelRenderUVMeshTopology`  
`struct FChannelRenderUVMeshTopology`  
_L188-198_
- desc: Cached UV mesh topology that remains constant during displacement and paint operations.
- L190 _public member_ `TArray<int32> Indices;`
- L191 _public member_ `TArray<FVector2f> UVs;`
- L192 _public member_ `TArray<int32> UVElementToVertexID;`
- L193 _public member_ `int32 VertexCount;`
- L195 _public member_ `FSectionDomainMapping DomainMapping;`
- L196 _public member_ `FUint32Vector2 RasterResolution;`
- L197 _public member_ `FVector2f TexcoordMetrics;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MeshPartition` (scope `UE`)
- L102 _prototype_ `void ApplyChannels(ACompiledSection* InSection, const FSectionChannels& InChannels, const float InMaterialCacheTexelSize);` (scope `UE::MeshPartition`) — Apply pre-built channel data (texture, texcoord metrics, table) to a compiled section.

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionCollisionTransformer.h` (Public)


#### struct `UE::MeshPartition::FCollisionTransformer`  
`struct FCollisionTransformer : public MeshPartition::FTransformer`  
_L22-61_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `MeshPartition::FTransformer`
- desc: Mesh Partition Transformer producing and attaching a collision component for each transformer unit present in the execution context.
- L27 _public prototype_ `FCollisionTransformer() = default;`
- L29 _public prototype_ `virtual void Initialize(const MeshPartition::UMeshPartitionDefinition* InDefinition, const MeshPartition::FCommonBuildVariant& InVariant) override;`
- L31 _public prototype_ `virtual bool Execute(MeshPartition::FTransformerContext& InTransformerContext) const override;`
- L33 _public prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& InDependencies) const override;`
- L36 _private prototype_ `void BuildCollisionData(const MeshPartition::FTransformerContext& InTransformerContext, const int32 InEntryIndex, TArray<TSharedPtr<FMeshPartitionCollisionData>>& OutCollisionData) const;`
- L38 _private prototype_ `void FinalizeCollisionData(const MeshPartition::FTransformerContext& InTransformerContext, const TArray<TSharedPtr<FMeshPartitionCollisionData>>& InCollisionData) const;`
- L42 _private member_ `TArray<MeshPartition::FPhysicalMaterialChannel> PhysicalMaterialChannels;` — `UPROPERTY()`
- L45 _private member_ `TObjectPtr<UPhysicalMaterial> DefaultPhysicalMaterial;` — `UPROPERTY()`
- L48 _private member_ `MeshPartition::Collision::FCollisionSimplificationSettings CollisionSimplificationSettings;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Simplification")`
- L51 _private member_ `FCollisionProfileName CollisionProfile = UCollisionProfile::BlockAll_ProfileName;` — `UPROPERTY(EditAnywhere, Category = "Collision")`
- L54 _private member_ `bool bCanEverAffectNavigation = true;` — `UPROPERTY(EditAnywhere, Category = "Collision")`
- L57 _private member_ `bool bFastCook = false;` — `UPROPERTY(EditAnywhere, Category = "Collision")` — todo(luc.eygasier): should be true for preview sections  Or we could pass the execution type in the context and the transformer adapts.
- L60 _private member_ `bool bDisableActiveEdgePrecompute = false;` — `UPROPERTY(EditAnywhere, Category = "Collision")` — todo(luc.eygasier):  should be true for preview sections  Or we could pass the execution type in the context and the transformer adapts.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionDependencyContext.h` (Public)


#### class `UE::MeshPartition::FDependencyContext`  
`class FDependencyContext : public IDependencyInterface`  
_L18-80_
- inherits: `IDependencyInterface`
- desc: Collects all package and class dependencies, but does not do any hashing.
- L54 _private member_ `TMap<const UObject*, EDependencyFlags> ObjectDependencies;`
- L55 _private member_ `TSet<const UClass*> ClassDependencies;`
- L56 _private member_ `FNoOpArchive NoOpArchive;`
- L61 _protected prototype_ `TArray<FName> GetPackageDependencies(const IAssetRegistry& InAssetRegistry) const;`
- L62 _protected prototype_ `TArray<const UClass*> GetClassDependencies() const;`
- L65 _public prototype_ `FDependencyContext() = default;`
- L66 _public prototype_ `virtual ~FDependencyContext() override = default;`
- L68 _public prototype_ `virtual void AddPackageDependency(const UObject* InObject, EDependencyFlags InDependencyFlags = EDependencyFlags::None) override;`
- L69 _public prototype_ `virtual void AddPackageDependency(TArrayView<UObject*> InObjectArray) override;`
- L70 _public prototype_ `virtual void AddClassDependency(const UClass* InClass) override;`
- L71 _public function_ `virtual FArchive& GetDependentDataArchive() override`
- L73 _public prototype_ `virtual void operator+=(const UDynamicMesh& InMesh) override;`
- L74 _public prototype_ `virtual void operator+=(const UStaticMesh& InMesh) override;`
- L75 _public prototype_ `virtual void operator+=(const UTexture& InTexture) override;`
- L76 _public prototype_ `virtual void operator+=(const UTexture2D& InTexture) override;`
- L77 _public prototype_ `virtual void operator+=(const UCurveFloat& InCurveFloat) override;`
- L78 _public prototype_ `virtual void operator+=(const USplineComponent& InSpline) override;`
- L79 _public prototype_ `virtual void operator+=(const UObject& InObject) override;`

#### class `UE::MeshPartition::FDependencyContext::FNoOpArchive`  
`class FNoOpArchive : public FArchive`  
_L21-52_
- inherits: `FArchive`
- desc: This is a dummy archive that makes any serialization calls into a no-op.
- L24 _public function_ `FNoOpArchive()`
- L29 _public function_ `virtual void Reset() override`
- L35 _public function_ `virtual void Serialize(void*, int64) override`
- L36 _public function_ `virtual void SerializeBool(bool&) override`
- L37 _public function_ `virtual void SerializeBits(void*, int64) override`
- L38 _public function_ `virtual bool SerializeBulkData(FBulkData&, const FBulkDataSerializationParams&) override`
- L39 _public function_ `virtual void SerializeInt(uint32&, uint32) override`
- L40 _public function_ `virtual void SerializeIntPacked(uint32&) override`
- L41 _public function_ `virtual void SerializeIntPacked64(uint64&) override`
- L43 _public function_ `virtual FArchive& operator<<(FName&) override`
- L44 _public function_ `virtual FArchive& operator<<(FText&) override`
- L45 _public function_ `virtual FArchive& operator<<(UObject*&) override`
- L46 _public function_ `virtual FArchive& operator<<(FField*&) override`
- L47 _public function_ `virtual FArchive& operator<<(FLazyObjectPtr&) override`
- L48 _public function_ `virtual FArchive& operator<<(FObjectPtr&) override`
- L49 _public function_ `virtual FArchive& operator<<(FSoftObjectPtr&) override`
- L50 _public function_ `virtual FArchive& operator<<(FSoftObjectPath&) override`
- L51 _public function_ `virtual FArchive& operator<<(FWeakObjectPtr&) override`

#### class `UE::MeshPartition::FDependencyHash`  
`class FDependencyHash : public IDependencyInterface`  
_L83-162_
- inherits: `IDependencyInterface`
- desc: Hashes all the data, but does not collect any class or packages dependencies.
- L88 _public prototype_ `FDependencyHash() = default;`
- L89 _public prototype_ `virtual ~FDependencyHash() override = default;`
- L91 _public function_ `virtual void AddPackageDependency(const UObject* InObject, EDependencyFlags InDependencyFlags = EDependencyFlags::None) override`
- L92 _public function_ `virtual void AddPackageDependency(TArrayView<UObject*> InObjectArray) override`
- L93 _public function_ `virtual void AddClassDependency(const UClass* InClass) override`
- L94 _public function_ `virtual FArchive& GetDependentDataArchive() override`
- L96 _public prototype_ `virtual void operator+=(const UDynamicMesh& InMesh) override;`
- L97 _public prototype_ `virtual void operator+=(const UStaticMesh& InMesh) override;`
- L98 _public prototype_ `virtual void operator+=(const UTexture& InTexture) override;`
- L99 _public prototype_ `virtual void operator+=(const UTexture2D& InTexture) override;`
- L100 _public prototype_ `virtual void operator+=(const UCurveFloat& InCurveFloat) override;`
- L101 _public prototype_ `virtual void operator+=(const USplineComponent& InSpline) override;`
- L102 _public prototype_ `virtual void operator+=(const UObject& InObject) override;`
- L105 _public prototype_ `FGuid GetDependentDataHash() const;` — return the hash of all dependencies hashed up until this point
- L161 _private member_ `FHashArchive HashArchive;`

#### class `UE::MeshPartition::FDependencyHash::FHashArchive`  
`class FHashArchive : public FArchive`  
_L109-159_
- inherits: `FArchive`
- desc: Accumulates a hash for all serialized data.
- L112 _public function_ `FHashArchive()`
- L117 _public function_ `virtual void Reset() override`
- L124 _public function_ `virtual FArchive& operator<<(UObject*& Value) override`
- L125 _public function_ `virtual FArchive& operator<<(FLazyObjectPtr& Value) override`
- L126 _public function_ `virtual FArchive& operator<<(FObjectPtr& Value) override`
- L127 _public function_ `virtual FArchive& operator<<(FSoftObjectPtr& Value) override`
- L128 _public function_ `virtual FArchive& operator<<(FSoftObjectPath& Value) override`
- L129 _public function_ `virtual FArchive& operator<<(FWeakObjectPtr& Value) override`
- L131 _public function_ `virtual void Serialize(void* Data, const int64 Num) override`
- L136 _public function_ `FBlake3Hash GetHash() const`
- L142 _public function_ `void IgnoreObjectReferences(TUniqueFunction<void()>&& SerializeFunc)` — This executes the passed in serialization function, and explicitly ignores object references during its execution.
- L150 _private function_ `FArchive& CheckObjectReferences()`
- L157 _private member_ `FBlake3 HashBuilder;`
- L158 _private member_ `bool bAllowIgnoringObjectReferences = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionDescriptorCache.h` (Public)


#### struct `UE::MeshPartition::FModifierGrouping`  
`struct FModifierGrouping`  
_L22-42_
- L28 _public prototype_ `FModifierGrouping(const MeshPartition::FCompiledSectionBuildVariant& InBuildVariant, const UMeshPartitionDefinition& InDefinition, const MeshPartition::FModifierGroup& AllModifiersGroupSorted);`
- L31 _private member_ `FName BuildVariantName;`
- L34 _private member_ `TArray<MeshPartition::FModifierGroup> ModifierGroups;` — section groups for this build variant
- L39 _public function_ `TConstArrayView<MeshPartition::FModifierGroup> GetModifierGroups() const`
- L41 _public function_ `FName GetBuildVariantName() const`

#### struct `UE::MeshPartition::FCachedDescriptors`  
`struct FCachedDescriptors`  
_L45-127_
- desc: stores all of the descriptors relevant to a specific AMeshPartition actor, as well as the FModifierGrouping for each build variant
- L52 _public prototype_ `FCachedDescriptors(const AMeshPartition* InMeshPartition, TConstArrayView<MeshPartition::FModifierDesc> InAllModifiersSorted, TArray<FCompiledSectionDescriptor>&& InCompiledSections);`
- L56 _public prototype_ `FCachedDescriptors(const FGuid& InMeshPartitionGUID, const AMeshPartition* InMeshPartitionActor);` — this constructor initializes the cached descriptors, but does not fill out the data.  Used in the construction by FWorldCachedDescriptors TODO: this should be private
- L60 _private member_ `FGuid MeshPartitionGUID;` — actor GUID of the mesh partition actor
- L63 _private member_ `TSoftObjectPtr<const AMeshPartition> MeshPartitionActor;` — object path of the mesh partition actor
- L66 _private member_ `MeshPartition::FModifierGroup AllModifiersGroup;` — group containing all existing modifiers (including both base and non-base modifiers)
- L69 _private member_ `TArray<FCompiledSectionDescriptor> CompiledSections;` — all existing compiled section descriptors
- L72 _private member_ `TMap<FName, MeshPartition::FModifierGrouping> BuildVariants;` — section groups for each build variant
- L75 _public prototype_ `MeshPartition::FModifierGroup BuildModifierGroupForBaseModifierPaths(TConstArrayView<FSoftObjectPath> BaseModifierPaths) const;`
- L77 _public function_ `TConstArrayView<FModifierDesc> GetAllModifiers() const`
- L82 _public function_ `TConstArrayView<FModifierDesc> GetAllBaseModifiers() const`
- L87 _public function_ `TConstArrayView<FCompiledSectionDescriptor> GetCompiledSections() const`
- L92 _public function_ `const MeshPartition::FModifierGrouping* GetCachedBuildVariant(const FName& InBuildVariantName) const`
- L101 _public function_ `TConstArrayView<MeshPartition::FModifierGroup> GetModifierGroups(const MeshPartition::FCompiledSectionBuildVariant& BuildVariant) const`
- L111 _public function_ `const FSoftObjectPath& GetMeshPartitionPath() const`
- L116 _public function_ `const FGuid& GetMeshPartitionGUID() const`
- L121 _public function_ `const AMeshPartition* GetMeshPartitionActor() const`
- L126 _public prototype_ `void ForAllBuildVariants(TFunctionRef<bool(const MeshPartition::FModifierGrouping&)> InFunc) const;`

#### struct `UE::MeshPartition::FWorldCachedDescriptors`  
`struct FWorldCachedDescriptors`  
_L130-159_
- desc: stores the FCachedDescriptors for all AMeshPartition actors in a world
- L135 _private member_ `TSoftObjectPtr<const UWorld> World;`
- L137 _private member_ `int32 TotalCompiledSections = 0;`
- L138 _private member_ `int32 TotalModifiers = 0;`
- L139 _private member_ `int32 TotalBuildVariants = 0;`
- L140 _private member_ `int32 TotalSectionGroups = 0;`
- L142 _private member_ `TArray<TSharedPtr<MeshPartition::FCachedDescriptors>> AllMeshPartitionsCachedDescriptors;`
- L145 _private member_ `TMap<FGuid, TSharedPtr<MeshPartition::FCachedDescriptors>> CachedDescriptorsByGUID;` — Mapping storing the cached descriptors for each mega mesh actor GUID.
- L149 _private member_ `TMap<FSoftObjectPath, TSharedPtr<MeshPartition::FCachedDescriptors>> CachedDescriptorsByPath;` — Mapping storing the cached descriptors for each mega mesh actor path.  We only cache one entry per unique path Bt there can be two paths pointing to the same FCachedDescriptors, if they both share a GUID
- L151 _private prototype_ `TSharedPtr<MeshPartition::FCachedDescriptors> FindOrAddByActor(const AMeshPartition& MeshPartitionActor);`
- L152 _private prototype_ `TSharedPtr<MeshPartition::FCachedDescriptors> FindOrAddByGUID(const FGuid& MeshPartitionGUID);`
- L155 _public prototype_ `TSharedPtr<MeshPartition::FCachedDescriptors> GetCachedDescriptors(const AMeshPartition& MeshPartitionActor) const;`
- L156 _public prototype_ `TSharedPtr<MeshPartition::FCachedDescriptors> GetCachedDescriptorsByPath(const FSoftObjectPath& MeshPartitionPath) const;`
- L157 _public prototype_ `TSharedPtr<MeshPartition::FCachedDescriptors> GetCachedDescriptorsByGuid(const FGuid& MeshPartitionGUID) const;`
- L158 _public function_ `TConstArrayView<TSharedPtr<MeshPartition::FCachedDescriptors>> GetAllMeshPartitionsCachedDescriptors() const`

#### struct `UE::MeshPartition::FModifierDescriptorCache`  
`struct FModifierDescriptorCache`  
_L161-186_
- L165 _public prototype_ `void UpdateCacheForAllMeshPartitionsInWorld(UWorld* World, TArray<FGuid>* OutAllMeshPartitionGuidsInWorld = nullptr);` — returns an array of the mesh partition guids that exist in the world
- L167 _public prototype_ `TSharedPtr<MeshPartition::FCachedDescriptors> GetCachedDescriptors(const AMeshPartition* MeshPartition);`
- L168 _public prototype_ `TSharedPtr<MeshPartition::FCachedDescriptors> GetCachedDescriptorsByPath(FSoftObjectPath MeshPartitionPath);`
- L169 _public prototype_ `TSharedPtr<MeshPartition::FCachedDescriptors> GetCachedDescriptorsByGuid(FGuid MeshPartitionGUID);`
- L171 _public prototype_ `void ForAllCachedDescriptors(TFunctionRef<bool(const FSoftObjectPath&, const TSharedPtr<MeshPartition::FCachedDescriptors>&)> InFunc) const;`
- L174 _private prototype_ `void AddMeshPartitionToGuidMap(const AMeshPartition* MeshPartition);`
- L179 _private member_ `TMultiMap<FGuid, FSoftObjectPath> GuidToMeshPartitionPath;` — Mapping from MeshPartitionGuid (ActorGuid of AMeshPartition actor) to the soft object (path) pointer to the AMeshPartition.  Populated by cached mesh partitions. This can have multiple entries -- for example when a world is duplicated, like when PIE, the same GUID maps to a new object path.
- L182 _private member_ `TMap<FSoftObjectPath, TSharedPtr<MeshPartition::FCachedDescriptors>> CachedDescriptors;` — mapping storing the cached descriptors for each mega mesh actor
- L185 _private prototype_ `TSharedPtr<FWorldCachedDescriptors> GetDescriptorsForAllMeshPartitionsInWorld(UWorld* World);` — returns the set of MeshPartition-relevant descriptors in the input World

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionEditorComponent.h` (Public)


#### struct `UE::MeshPartition::FPreviewSectionBuildContext`  
`struct FPreviewSectionBuildContext`  
_L47-58_
- reflection: `USTRUCT()`
- desc: Struct used to manage async preview section builds.
- L52 _public member_ `TArray<TObjectPtr<MeshPartition::APreviewSection>> IntersectingPreviewSections;` — `UPROPERTY()`
- L55 _public member_ `TSet<TObjectPtr<MeshPartition::UModifierComponent>> OutdatedBases;` — `UPROPERTY()`
- L57 _public member_ `TArray<MeshPartition::FBuildTaskHandle> BuildTasks;`

#### struct `UE::MeshPartition::FPrepareCompiledSectionsParams`  
`struct FPrepareCompiledSectionsParams`  
_L61-78_
- desc: Parameters for PrepareCompiledSections.
- L64 _public member_ `const MeshPartition::FMeshData& FullMesh;` — Full mesh for this modifier group.
- L68 _public member_ `MeshPartition::FGridSettings GridSettings;` — Grid configuration (CellSize=0 = no grid splitting). Set by the builder from ResolveGridFromPipeline().
- L71 _public member_ `TMap<FIntVector, MeshPartition::FMeshData> OutCellMeshes;` — Receives per-cell sub-meshes after the call, keyed by absolute grid coordinate.
- L74 _public member_ `MeshPartition::ACompiledSection* ReuseSection = nullptr;` — Existing section actor to reuse instead of spawning a new one (single-section only).
- L77 _public member_ `bool bUseStaticMobility = true;` — Mobility for spawned actors (applies to single-section path only; grid always uses static).

#### class `UE::MeshPartition::UMeshPartitionEditorComponent`  
`class UMeshPartitionEditorComponent : public UMeshPartitionComponent`  
_L81-547_
- reflection: `UCLASS(MinimalAPI, ClassGroup=(MeshPartition))`
- inherits: `UMeshPartitionComponent`
- L86 _public prototype_ `UMeshPartitionEditorComponent();`
- L87 _public prototype_ `~UMeshPartitionEditorComponent();`
- L90 _public prototype_ `virtual void OnUnregister() override;`
- L91 _public prototype_ `virtual void CheckForErrors() override;`
- L95 _public prototype_ `virtual void PostRegisterMegaMeshComponents() override;`
- L96 _public prototype_ `virtual void PostUnregisterMegaMeshComponents() override;`
- L100 _public prototype_ `void Update();` — Updates the UMeshPartitionEditorComponent flushing pending async tasks and rebuilding pending modifications if needed.
- L106 _public prototype_ `void SetBuildModifierFilterFunction(FModifierFilterFunc InFunc);` — Assigns a filter function to control which modifiers are included in the build process @param InFunc the filter function to use
- L111 _public prototype_ `void ClearBuildModifierFilterFunction();` — Clears any assigned filter function to control which modifiers are included in the build process
- L117 _public prototype_ `void ForceRebuildAllSections(const EChangeType InChangeType);` — Force rebuild the entire megamesh @param InChangeType The type of change to trigger
- L123 _public prototype_ `void BuildMegaMeshPreviewSections(TConstArrayView<const FBox> InBounds);` — Builds one or multiple APreviewSections encompassing the provided bounds. MeshPartition::APreviewSection is a EditorOnly class. @param InBounds The bounds to use to build the compiled section.
- L135 _public prototype_ `TArray<MeshPartition::ACompiledSection*> PrepareCompiledSections( const MeshPartition::FCompiledSectionBuildInfo& InBuildInfo, const MeshPartition::FCompiledSectionBuildVariant& InBuildVariant, MeshPartition::FPrepareCompiledSectionsParams& InParams) const;` — Spawns one or more ACompiledSection actors for a modifier group. Dispatches to a grid-aligned split or a single section based on InBuildVariant.bSplitSectionsToMatchWorldPartitionRuntimeGrid and InParams.GridSettings.IsGridSplit(): - Grid path (bSplitSectionsToMatchWorldPartitionRuntimeGrid=true, InParams.GridSettings.IsGridSplit()): Splits FullMesh by GridSettings (honoring bIs2D), spawns one section per intersecting cell, populates OutCellMeshes with the per-cell sub-meshes. - Single path (all other cases): Spawns one section. Warns if bSplitSectionsToMatchWorldPartitionRuntimeGrid=true but GridSettings.IsGridSplit() is false. @return Array of spawned/reused sections; never empty on success.
- L148 _public prototype_ `void ExecuteTransformers(MeshPartition::UPreviewMeshComponent* InPreviewMeshComponent, const MeshPartition::UMeshPartitionDefinition* InDefinition, const MeshPartition::FCommonBuildVariant& InBuildVariant);` — Only used when building a preview section. Executes transformers on a preview mesh component. This is a synchronous operation and should only be used to be able to render properly the preview mesh. Any expensive operation should be delayed until building proper derived data. @param InPreviewMeshComponent The preview component the transformer will be executed on. @param InDefinition The definition in use. @param InVariant The build variant in use.
- L157 _public prototype_ `TUniquePtr<MeshPartition::FTransformerContext> LaunchTransformers(TArray<MeshPartition::FTransformerUnit>&& InTransformerUnits, const MeshPartition::UMeshPartitionDefinition* InDefinition, const MeshPartition::FCommonBuildVariant& InBuildVariant);` — Launches transformers associated with this build variant, seeding the pipeline with the provided initial units. @param InTransformerUnits The initial transformer units for the pipeline. The pipeline will take ownership of all units. @param InDefinition The definition used to launch the transformer pipeline. @param InBuildVariant The variant used to launch the transformer pipeline. @return If successful, launches the transformer pipeline and returns a new FTransformerContext.
- L163 _public prototype_ `void BuildMegaMeshCompiledSectionTextures(MeshPartition::ACompiledSection* InCompiledSection, const MeshPartition::FModifierGroup& InModifierGroup, FMeshData& InOutBuiltMesh);` — Builds the collection of textures containing the channel map information and binds it to the compiled section's material. Modify the UVs of the MeshData for the Section
- L172 _public prototype_ `AActor* SpawnBaseModifier(FDynamicMesh3&& InMesh, const TArray<UMaterialInterface*>& InMaterials, const FTransform& InTransform, const bool bRegisterModifier = true);` — Spawns a Base Modifier using the provided mesh and transform. @param InMesh The dynamic mesh to setup @param InMaterials The initial material used by the base. @param InTransform The transform to use. @return If successful, returns the new Base Modifier, nullptr otherwise.
- L181 _public function_ `template<class ActorType> ActorType* SpawnTransientActor(const FTransform& InActorTransform = FTransform::Identity)` — Spawns a transient preview actor of the specified type into the persistent level of this component's world. Forces the spawn into the persistent level of the editor component so these actors are never placed inside the currently edited level instance or external data layer.
- L191 _public prototype_ `AActor* SpawnTransientActor(TSubclassOf<AActor> InClass, const FTransform& InTransform = FTransform::Identity);` — Spawns a transient preview actor of the specified type into the persistent level of this component's world. Forces the spawn into the persistent level of the editor component so these actors are never placed inside the currently edited level instance or external data layer.
- L194 _public prototype_ `void UpdateMaterial();` — Updates the currently used material resources (section material instance and channel textures).
- L203 _public prototype_ `void PostBuildSectionMesh(AActor* InSection, const MeshPartition::FMeshData& InBuiltMesh, TConstArrayView<TWeakObjectPtr<MeshPartition::UModifierComponent>> InModifiers) const;` — Called after a MeshPartition::APreviewSection or MeshPartition::ACompiledSection FMeshData has been built. Will call modifiers in need of performing additional processing. @param InSection The section on which the processing can be performed. @param InBuiltMesh The result of the build operation. @param InModifiers The modifiers applied to this section.
- L211 _public prototype_ `void PostProcessSection(AActor* InSection, TConstArrayView<TWeakObjectPtr<MeshPartition::UModifierComponent>> InModifiers) const;` — Called after a MeshPartition::APreviewSection or MeshPartition::ACompiledSection has been built and their associate mesh finalized. Will call modifiers in need of performing additional processing. @param InSection The section on which the processing can be performed. @param InModifiers The modifiers applied to this section.
- L223 _public prototype_ `void ApplyBuiltMeshToSection(MeshPartition::ACompiledSection* InSection, TSharedPtr<const MeshPartition::FMeshData> InMesh, const MeshPartition::FSectionChannels& InChannels, const MeshPartition::FModifierGroup& InModifierGroup);` — Runs the full synchronous post-build pipeline on a compiled section: PrepareCompiledSections → ApplyChannels → PostBuildSectionMesh → Transformers (wait) → PostProcessSection. Resolves Definition and BuildVariant from the section's BuildInfo internally. Callers must ensure the section's BuildInfo is up-to-date before calling. @param InSection The section to finalize. @param InMesh The built mesh data (shared ownership for transformer pipeline). @param InChannels Pre-built channel data (texture, texcoord metrics, table). @param InModifierGroup The modifier group for this section.
- L234 _public prototype_ `void OnModifierChanged(MeshPartition::UModifierComponent* InChangedModifier, TConstArrayView<FBox> InBounds, const EChangeType InChangeType);` — Called when a modifier contributing to the MegaMesh changed. Will invalidate and trigger a rebuilt of changed areas. @param InChangedModifier The modifier which has changed. @param InBounds The bounds impacted by the modifier. @param InChangeType the type of this change event.
- L235 _public prototype_ `void OnBoundsChanged(TConstArrayView<FBox> InBounds, const EChangeType InChangeType);`
- L240 _public prototype_ `void OnModifierAssigned();` — Called when a MeshPartition::UModifierComponent is assigned or unassigned to this MegaMesh.
- L245 _public prototype_ `void UpdateModifierList();` — Recreates list of relevant modifiers by looking through all the loaded modifiers.
- L252 _public prototype_ `TArray<MeshPartition::UModifierComponent*> GetModifiersFiltered(TFunctionRef<bool(const MeshPartition::UModifierComponent*)> InFilter) const;` — Returns a list of all MegaMeshModifiers that affect this MegaMesh and  all match the passed filter. @param InFilter If this function returns true for a given modifier, it will be added to the returned list. @return The list of matching modifiers.
- L258 _public prototype_ `void ForAllCurrentModifiers(TFunctionRef<bool(MeshPartition::UModifierComponent*)> InFunc) const;` — Calls the provided function on all currently loaded MeshPartition::UModifierComponent belonging to the owner MegaMesh. @param InFunc The function that will be called on MeshPartition::UModifierComponent. Should return true to continue iteration, false to stop.
- L264 _public prototype_ `void ForAllPreviewSections(TFunctionRef<bool(MeshPartition::APreviewSection*)> InFunc) const;` — Calls the provided function on all APreviewSections belonging to the owner MegaMesh. @param InFunc The function that will be called on MeshPartition::APreviewSection. Should return true to continue iteration, false to stop.
- L272 _public prototype_ `void GetModifiersToProcessForPreviews(TSet<MeshPartition::UModifierComponent*>& OutModifiers, const TArray<MeshPartition::APreviewSection*>& InPreviewSections, TConstArrayView<FBox> InBoundsToBuild) const;` — Retrieves all currently loaded modifiers to process, intersecting the provided bounds or belonging to the provided preview sections. @param OutModifiers A set containing the MeshPartition::UModifierComponent to process. @param InPreviewSections the preview sections used to retrieve base modifiers. @param InBoundsToBuild The bounds used to filter the modifiers.
- L284 _public prototype_ `void InvalidateConflictingPreviewSectionBuildContexts(TSet<MeshPartition::UModifierComponent*>& InOutModifiers, const TArray<MeshPartition::APreviewSection*>& InPreviewSections, const MeshPartition::FPreviewSectionBuildContext& InCurrentBuildContext);` — Iterates through current preview section async builds. Invalidating builds containing common bases with the most recent one. Taking ownership of intersecting preview sections and modifiers contained in conflicting builds. @param InOutModifiers An array containing the MeshPartition::UModifierComponent to process. @param InPreviewSections the preview sections used to retrieve base modifiers. @param InCurrentBuildContext The most recent build context.
- L293 _public prototype_ `void GetModifiersWithinBounds(TArray<MeshPartition::UModifierComponent*>& OutModifiers, TConstArrayView<const FBox> InBoundsToBuild) const;` — Retrieves all currently loaded modifiers which intersect with the passed bounding boxes. @param OutModifiers An array containing the MeshPartition::UModifierComponent within the provided bounds. @param InBoundsToBuild The bounds used to filter the modifiers.
- L300 _public prototype_ `void GetModifiersAffectingBounds(TArray<MeshPartition::UModifierComponent*>& OutModifiers, TConstArrayView<const FBox> InBoundsToBuild) const;` — Retrieves all currently loaded modifiers which affect the passed bounding boxes, taking into account chained modifications. @param OutModifiers An array containing the MeshPartition::UModifierComponent affecting the provided bounds. @param InBoundsToBuild The bounds used to filter the modifiers.
- L307 _public prototype_ `void GetModifiersAffectingModifiers(TArray<MeshPartition::UModifierComponent*>& OutModifiers, const TArray<MeshPartition::UModifierComponent*>& InModifiers) const;` — Retrieves all currently loaded modifiers which affect the passed modifiers, taking into account chained modifications. @param OutModifiers An array containing the MeshPartition::UModifierComponent affecting the provided modifiers. @param InModifiers The modifiers used to filter the result.
- L309 _public prototype_ `const MeshPartition::FCommonBuildVariant& GetPreviewBuildVariant() const;`
- L311 _public prototype_ `void SetBaseModifiersHidden(bool bInHideBaseModifiers);`
- L312 _public function_ `bool ShouldHideBaseModifiers() const`
- L319 _public prototype_ `uint32 GetModifierLayerIndex(const FName& InModifierLayer) const;` — Returns the effective layer stack ordering index for a modifier's layer name, depending on if a definition is available or not. @param InModifierLayer The modifier's layer name @return Index of the layer
- L325 _public function_ `void SetPreviewSectionBuildEnabled(const bool bInEnabled)` — Enables/Disables preview section building. @param bInEnabled True if building preview section is enabled.
- L326 _public function_ `bool IsPreviewSectionBuildEnabled() const`
- L332 _public function_ `bool ArePreviewSectionsVisible() const` — Returns true if preview sections are currently visible. @return true if preview sections are currently visible.
- L333 _public prototype_ `void SetPreviewSectionsVisibility(const bool bInArePreviewSectionsVisible);`
- L340 _public prototype_ `void SetToolTargetVisibility(const TArray<MeshPartition::APreviewSection*> InPreviewSections, const bool bInVisible);` — Called when preview sections are targeted by tools. Is responsible to hide/unhide appropriate preview and interactive sections. @param InPreviewSections The targtted preview sections. @param bInVisible True if they should be visible, false otherwise.
- L345 _public prototype_ `UMeshPartitionDefinition* GetMegaMeshDefinition() const;` — @return The Owner's currently used UMeshPartitionDefinition.
- L350 _public prototype_ `virtual void OnDefinitionChanged(UMeshPartitionDefinition* InNewDefinition) override;` — Callback called when the owner's currently used UMeshPartitionDefinition changed.
- L355 _public prototype_ `UMaterialInterface* GetDefinitionMaterial() const;` — @return the Material described by the definition and generated for this MegaMesh instance
- L357 _public function_ `UMaterialInterface* GetEditorOverrideMaterial() const`
- L363 _public prototype_ `void OnModifierLoaded(MeshPartition::UModifierComponent* InModifier);` — Called when a MeshPartition::UModifierComponent has been loaded via WorldPartition. @param InModifier The loaded Modifier.
- L369 _public prototype_ `void OnModifierUnloaded(MeshPartition::UModifierComponent* InModifier);` — Called when a MeshPartition::UModifierComponent has been unloaded via WorldPartition. @param InModifier The unloaded Modifier.
- L374 _public prototype_ `bool IsSynchronousPreviewSectionBuildForced() const;` — @return true if the preview section build process is forced to synchronous.
- L375 _public function_ `void SetForceSynchronousPreviewSectionBuild(const bool bInForced)`
- L383 _public prototype_ `void SetPauseTransformerPipeline(const bool bInShouldPauseTransformerPipeline);` — Pauses/Unpauses PreviewSections' transformers execution depending on the provided argument. In case of pause, will also take care of notifying the user the build have been paused. In case of unpause, will also launch the previously paused builds. @param bInShouldPauseTransformerPipeline Should preview sections' transformer execution be paused.
- L386 _public prototype_ `bool IsModifierParticipatingInActivePreviewSectionBuild(const MeshPartition::UModifierComponent* InModifier) const;` — Search all active preview section builds and check if a given modifier is participating in one or more builds.
- L389 _public prototype_ `bool IsAnyPreviewSectionBuildActive() const;` — Check if any of the preview section builds are running.
- L392 _public prototype_ `void ResetGroupRegistry(TConstArrayView<const MeshPartition::FModifierGroup> InModifierGroups);` — Re-initializes the group registry with the provided modifier groups.
- L393 _public prototype_ `void ResetGroupRegistry();`
- L395 _public prototype_ `const MeshPartition::FModifierGroup* FindGroupInRegistry(const FGuid& InGroupKey) const;`
- L398 _public prototype_ `bool ShouldRecomputeTangents() const;` — Will return true if preview section transformer pipeline is paused and the recompute tangents feature is enabled.
- L404 _protected prototype_ `void OnLoadedActorAddedToLevel(const TArray<AActor*>&);` — Called after loading or unloading actors in the current level.
- L405 _protected prototype_ `void OnLoadedActorRemovedFromLevel(AActor&);`
- L410 _protected prototype_ `void OnLevelActorDeleted(AActor* Actor);` — Called during actor deletion, giving us a chance to uninitialize modifiers
- L415 _protected prototype_ `void OnSelectionChanged(UObject* InObject);` — Called when selection changed in the editor.
- L420 _protected prototype_ `void QueuePendingModifierChange(MeshPartition::UModifierComponent* InChangedModifier, TConstArrayView<FBox> InBoundingBoxes, const EChangeType InChangeType);` — Adds the modifier change information to a pending queue of modifier changes to be bulk processed together usually on the next tick.
- L428 _protected prototype_ `TArray<FBox> GetIntersectingPreviewSections(TConstArrayView<FBox> InBounds, TArray<TObjectPtr<MeshPartition::APreviewSection>>& OutIntersectingPreviewSections);` — Gets the PreviewSection intersecting the provided bounds in the provided array. @param InBounds The bounds to rebuild. @param OutIntersectingPreviewSections Output argument, returns the intersecting preview sections. @return An adjusted array of FBox, encompassing the provided bounds plus intersecting preview sections.
- L434 _protected prototype_ `void DestroyPreviewSections(TArray<TObjectPtr<MeshPartition::APreviewSection>>& InSectionsToDestroy);` — Destroys the provided preview sections. Nullifying any links. @param InSectionsToDestroy The preview sections to be destroyed.
- L441 _protected prototype_ `static void UpdateLinks(const MeshPartition::FModifierGroup& InModifierGroup, MeshPartition::APreviewSection* InPreviewSection);` — Updates the relationship links between bases and preview sections. @param InModifierGroup The modifier group used to build the preview section. @param InPreviewSection The preview section resulting from the modifier group.
- L448 _protected prototype_ `void OnDefinitionModified(const FName& InMemberName, const FName& InPropertyName);` — Callback called when properties are modified in the owner's currently used UMeshPartitionDefinition. @param InMemberName The member name of the changed property. @param InPropertyName The name of the changed property.
- L451 _protected prototype_ `void ResetInteractiveSection();` — Resets the state of the interactive preview section and all preview sections intersecting it.
- L457 _protected prototype_ `void SetInteractiveModifiers(const TArray<MeshPartition::UModifierComponent*>& InModifiers);` — Setup interactive section, preview sections and the provided modifiers to be able to enter interactive mode. @param The modifiers to setup. Can be an empty array to clear the previously setup interactive modifiers.
- L462 _protected prototype_ `bool IsInteractiveModeEnabled() const;` — @return True if interactive mode is currently enabled.
- L467 _protected prototype_ `bool IsInteractiveModeReady() const;` — @return True if interactive mode is currently enabled, setup and ready to be used.
- L470 _protected prototype_ `void OnPreviewSectionSimplificationEnabledChanged(IConsoleVariable* InConsoleVariable);` — Will invalidate any simplified preview section if the simplification is disabled.
- L477 _private prototype_ `void FinalizeAsyncTasks(const bool bInCompleteAllTasks = false);` — Takes care of managing async tasks. Should be only called from gamethread. @param bInCompleteAllTasks If true, will try to finalize all completed tasks. False will just complete one task.
- L482 _private prototype_ `void FinalizePreviewSectionBuilds();` — Takes care of managing preview section async tasks. Should be only called from gamethread.
- L487 _private prototype_ `uint32 GetPreviewSectionBuildNumber() const;` — @return The current number of preview section being built.
- L490 _private member_ `TArray<TObjectPtr<MeshPartition::APreviewSection>> PreviewSections;` — `UPROPERTY(Transient)`
- L493 _private member_ `TArray<TObjectPtr<MeshPartition::UModifierComponent>> CurrentModifiers;` — `UPROPERTY(Transient)`
- L496 _private member_ `TObjectPtr<MeshPartition::AInteractiveSection> InteractiveSection;` — `UPROPERTY(Transient)`
- L499 _private member_ `TArray<TObjectPtr<MeshPartition::APreviewSection>> InteractivePreviewSections;` — `UPROPERTY(Transient)`
- L502 _private member_ `TArray<TUniquePtr<MeshPartition::FTransformerContext>> PreviewSectionTransformerContexts;` — As FTransformerContext can be passed to async thread and the array entry can be relocated, better allocate it.
- L504 _private member_ `TSet<TObjectKey<MeshPartition::APreviewSection>> PreviewSectionsToDestroy;`
- L507 _private member_ `TArray<MeshPartition::FPreviewSectionBuildContext> PreviewSectionBuildContexts;` — `UPROPERTY(Transient)`
- L510 _private member_ `TWeakObjectPtr<AActor> LastActorSelected = nullptr;` — `UPROPERTY(Transient)`
- L513 _private member_ `bool bHideBaseModifiers = true;` — `UPROPERTY(Transient)`
- L516 _private member_ `bool bArePreviewSectionsVisible = true;` — `UPROPERTY(Transient)`
- L519 _private member_ `bool bBuildPreviewSection = true;` — `UPROPERTY(Transient)`
- L522 _private member_ `bool bIsTransformerPipelinePaused = false;` — `UPROPERTY(Transient)`
- L525 _private member_ `bool bForceSynchronousPreviewSectionBuild = false;` — `UPROPERTY(Transient)`
- L530 _private member_ `TObjectPtr<UMaterialInterface> EditorMaterialOverride;` — `UPROPERTY(EditAnywhere, Category = "Rendering")` — Optional material override to use in the editor when displaying the tool previews or pre-transformed preview meshes. If set to none, Definition material will be used.
- L532 _private member_ `FModifierFilterFunc BuildModifierFilterFunc;`
- L534 _private member_ `MeshPartition::FModifierGroupRegistry GroupRegistry;`
- L537 _private member_ `bool bPendingModifierListChange = false;` — True when UpdateFromActorListChange needs to be called
- L539 _private member_ `bool bModifierListChanged = false;` — Set by OnLevelActorDeleted so we know that changes were made in the next UpdateModifierList
- L543 _private member_ `TMap<EChangeType, TSet<FBox>> PendingChangedBounds;` — Queued bounds updates to process on the next update. These bounds invalidate all layers and are not associated with modifiers
- L546 _private member_ `TMap<FSoftObjectPath, TArray<MeshPartition::FModifierChangeInfo>> PendingChangedModifiers;` — Queued bounds updates to process on the next update. Bounds are associated per modifier and updates can be more granular with this knowledge.

#### Free symbols / members of external scopes

- L21 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`
- L25 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace MeshPartition` (scope `UE`)
- L41 _externvar_ `extern TAutoConsoleVariable<bool> CVarMegaMeshEnablePreviewSimplification;` (scope `UE::MeshPartition`)
- L42 _externvar_ `extern TAutoConsoleVariable<float> CVarMegaMeshPreviewSimplificationEdgeLength;` (scope `UE::MeshPartition`)
- L43 _externvar_ `extern TAutoConsoleVariable<int32> CVarMegaMeshPreviewSimplificationMinVertexNumber;` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionEditorModule.h` (Public)


#### class `UE::MeshPartition::FMeshPartitionEditorModule`  
`class FMeshPartitionEditorModule : public IModuleInterface`  
_L15-31_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _private prototype_ `void OnPostEngineInit();`
- L24 _private prototype_ `void ModulesChangedCallback(FName InModuleName, EModuleChangeReason InChangeReason);`
- L26 _private prototype_ `void RegisterFoliageBaseIDClassIgnoreList();`
- L28 _private prototype_ `void OnMinimapWarmupTick(UWorld* World);`
- L30 _private member_ `TArray<FName> VisualizersToUnregisterOnShutdown;`

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMegaMeshEditor, Log, All);`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionEditorSubsystem.h` (Public)


#### enum `UE::MeshPartition::EChangeType`  
`enum class EChangeType`  
_L29-46_
- L35 _public enumerator_ `StateChange` — Represents a change to the state of the megamesh/modifier. For example: changing any serialized properties such as the position or bounds of a modifier.
- L42 _public enumerator_ `TransientStateChange` — Represents a change to transient state. Transient state would be restored to a default value when reloading a map. For example: temporarily hiding a modifier via a flag which is not serialized.
- L45 _public enumerator_ `TransientChange` — Represents a transient change such as loading or unloading a modifier, changing an editor visualization setting, etc.

#### struct `UE::MeshPartition::FModifierChangeInfo`  
`struct FModifierChangeInfo`  
_L48-53_
- L50 _public member_ `MeshPartition::FModifierDesc ModifierDesc;`
- L51 _public member_ `TArray<FBox> ChangedBounds;`
- L52 _public member_ `EChangeType ChangeType;`

#### struct `UE::MeshPartition::FOnChangedEventInfo`  
`struct FOnChangedEventInfo`  
_L55-64_
- L57 _public member_ `const UMeshPartitionEditorComponent* ChangedEditorComponent;`
- L60 _public member_ `const TMap<FSoftObjectPath, TArray<MeshPartition::FModifierChangeInfo>>& ChangedModifiers;` — Per modifier invalidated regions
- L63 _public member_ `const TMap<EChangeType, TSet<FBox>>& ChangedBounds;` — Fully invalidated regions (modifier agnostic changes which invalidate all layers)

#### class `UE::MeshPartition::UMeshPartitionEditorSubsystem`  
`class UMeshPartitionEditorSubsystem : public UEditorSubsystem, public FTickableEditorObject, public MeshPartition::IMeshPartitionCompilerInterface`  
_L67-199_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem,FTickableEditorObject,MeshPartition::IMeshPartitionCompilerInterface`
- L71 _public prototype_ `DECLARE_EVENT_OneParam(UMeshPartitionEditorSubsystem, FOnMegaMeshChanged, const FOnChangedEventInfo&);`
- L73 _public prototype_ `UMeshPartitionEditorSubsystem();`
- L76 _public prototype_ `virtual void Tick(float InDeltaSeconds) override;`
- L77 _public function_ `virtual bool IsTickable() const override`
- L78 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L79 _public prototype_ `virtual TStatId GetStatId() const override;`
- L82 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& InCollection) override;`
- L83 _public prototype_ `virtual void Deinitialize() override;`
- L85 _public prototype_ `static UMeshPartitionEditorSubsystem* Get();`
- L87 _public function_ `static MeshPartition::FModifierGraphCache* GetGraphCache()`
- L93 _public function_ `static MeshPartition::FMeshBuilder* GetMeshBuilder()`
- L99 _public function_ `static MeshPartition::FModifierDescriptorCache* GetDescriptorCache()`
- L105 _public function_ `static MeshPartition::EditorUtils::FPIEPathFixer& GetPIEPathFixer()`
- L115 _public prototype_ `virtual void BuildPlaceholderCompiledSection(MeshPartition::ACompiledSection* CompiledSection) override;` — Fill out a placeholder compiled section by building the mesh for the relevant megamesh modifiers
- L120 _public prototype_ `uint32 GetTotalPreviewSectionBuildNumber() const;` — @return The current total number of preview sections being built for all MegaMeshes.
- L125 _public prototype_ `uint32 GetTotalInteractiveSectionBuildNumber() const;` — @return The current total number of interactive sections being built for all MegaMeshes.
- L132 _public prototype_ `void SetPreviewSectionBuildNumber(UMeshPartitionEditorComponent* InMegaMeshEditorComponent, uint32 InPreviewSectionBuildNumber);` — Sets the number of preview sections being built by a given MegaMeshEditorComponent. @param InMegaMeshEditorComponent The editor component to update. @param InPreviewSectionBuildNumber The new number of preview sections being built.
- L139 _public prototype_ `void SetInteractiveSectionBuild(UMeshPartitionEditorComponent* InMegaMeshEditorComponent, const bool bInIsBuilding);` — Sets the state of the interactive section build owned by a MegaMeshEditorComponent. @param InMegaMeshEditorComponent The editor component holding the interactive section to update. @param bInIsBuilding True if the editor component is currently preparing the interactive section.
- L141 _public prototype_ `FTextFormat GetPreviewSectionNameFormat() const;`
- L142 _public prototype_ `FTextFormat GetInteractiveSectionNameFormat() const;`
- L144 _public function_ `FOnMegaMeshChanged& OnMegaMeshChanged()`
- L146 _public prototype_ `TSharedPtr<FMeshPartitionWorldUpdater> GetPIEWorldUpdaterForWorld(UWorld* World);`
- L148 _public prototype_ `void OnStartPIE(const bool bIsSimulating);`
- L149 _public prototype_ `void OnPostPIEStarted(const bool bIsSimulating);`
- L151 _public prototype_ `void OnPrepareEditorGameWorldForPIE(UWorldPartition* WorldPartition);`
- L152 _public prototype_ `void OnShutdownEditorGameWorldForPIE(UWorldPartition* WorldPartition);`
- L154 _public prototype_ `void EndPIE(const bool bIsSimulating);`
- L155 _public prototype_ `void ShutdownPIE(const bool bIsSimulating);`
- L156 _public prototype_ `void CancelPIE();`
- L158 _public prototype_ `int32 CountMeshPartitions(UWorld* World);`
- L160 _public prototype_ `void TrackGarbagePreviewSection(MeshPartition::APreviewSection* InPreviewSectionToDestroy);`
- L161 _public prototype_ `void OnPostGC();`
- L164 _private member_ `MeshPartition::FModifierDescriptorCache DescriptorCache;`
- L165 _private member_ `MeshPartition::FModifierGraphCache GraphCache;`
- L166 _private member_ `MeshPartition::FMeshBuilder MeshBuilder;`
- L169 _private member_ `MeshPartition::FSeparateWorldBuilder SeparateWorldBuilder;` — `UPROPERTY()`
- L172 _private typedef_ `template <typename KeyType, typename ValueType> using TWeakObjectPtrKeyMap = TMap<KeyType, ValueType, FDefaultSetAllocator, TWeakObjectPtrMapKeyFuncs<KeyType, ValueType>>;`
- L174 _private member_ `TWeakObjectPtrKeyMap<TWeakObjectPtr<UMeshPartitionEditorComponent>, uint32> EditorComponentToPreviewSectionBuildNumber;`
- L175 _private member_ `TUniquePtr<FAsyncCompilationNotification> PreviewSectionBuildNotification;`
- L177 _private member_ `uint32 TotalPreviewSectionBuildNumber = 0;`
- L179 _private member_ `TSet<TObjectPtr<UMeshPartitionEditorComponent>> InteractiveEditorComponents;`
- L180 _private member_ `TUniquePtr<FAsyncCompilationNotification> InteractiveSectionBuildNotification;`
- L182 _private member_ `FOnMegaMeshChanged MegaMeshChangedEvent;`
- L184 _private member_ `bool bIsTickable = true;`
- L188 _private member_ `TSharedPtr<FMeshPartitionWorldUpdater> PIEWorldUpdater;` — cached world updater for current PIE session (if any) - this tracks what exists, up to date status, and what needs to be created / updated this only applies to the world specified by PIEOriginalEditorWorldPath (which is the currently open world in editor at PIE startup)
- L189 _private member_ `FSoftObjectPath PIEOriginalEditorWorldPath;`
- L191 _private member_ `MeshPartition::EditorUtils::FPIEPathFixer PIEPathFixer;`
- L193 _private member_ `bool bCancelPIE = false;`
- L198 _private member_ `int64 EstimatedGarbagePreviewSectionTotalMB = 0.;` — Retain an estimate of the total memory occupied by preview sections which have not been GC'd. The editor does not GC incrementally nor at memory pressure and garbage preview section mesh data can represent a significant amount of memory over time.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MeshPartition` (scope `UE`)
- L71 _delegate_ `DECLARE_EVENT_OneParam(UMeshPartitionEditorSubsystem, FOnMegaMeshChanged, const FOnChangedEventInfo&);`

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionEditorUtils.h` (Public)


#### struct `UE::MeshPartition::EditorUtils::FFinalizeStaticMeshParams`  
`struct FFinalizeStaticMeshParams`  
_L98-111_
- desc: Struct used to pass settings to FinalizeStaticMesh.
- L100 _public member_ `UStaticMesh* StaticMesh = nullptr;`
- L101 _public member_ `UMaterialInterface* Material = nullptr;`
- L102 _public member_ `FCollisionProfileName CollisionProfile = UCollisionProfile::BlockAll_ProfileName;`
- L103 _public member_ `int32 NumLODs = 0;`
- L104 _public member_ `bool bCanEverAffectNavigation = false;`
- L105 _public member_ `bool bUseNanite = true;`
- L106 _public member_ `bool bSetupSections = true;`
- L107 _public member_ `ENaniteGenerateFallback NaniteFallbackMode = ENaniteGenerateFallback::Enabled;`
- L108 _public member_ `ENaniteFallbackTarget NaniteFallbackTarget = ENaniteFallbackTarget::PercentTriangles;`
- L109 _public member_ `float NaniteFallbackPercentTriangles = 0.2f;`
- L110 _public member_ `float NaniteFallbackRelativeError = 1.0f;`

#### struct `UE::MeshPartition::EditorUtils::FPIEPathFixer`  
`struct FPIEPathFixer`  
_L119-126_
- desc: Removes any PIE path mangling from an FSoftObjectPath, if any is present, returning the non-PIE / original path. Do not use across multiple PIE contexts without Resetting(), as the mapping is cached and may change
- L122 _private member_ `TMap<FName, FName> PIEToNonPIEPackageName;`
- L124 _public prototype_ `void Reset();`
- L125 _public prototype_ `void FixInPlace(FSoftObjectPath& InOutPath);`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MeshPartition` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace MeshPartition` (scope `UE`)
- L25 _namespace_ `namespace EditorUtils` (scope `UE::MeshPartition`)
- L32 _prototype_ `int32 GetMegaMeshClassVersionFromClass(const UClass* InClass);` (scope `UE::MeshPartition::EditorUtils`) — Get the MegaMesh-specific version key of the specified class (NOTE: We use positive MegaMeshClassVersion numbers to indicate deterministic cache keys.)
- L40 _prototype_ `FGuid ComputePackageHash(IAssetRegistry& AssetRegistry, TArrayView<const FName> PackageNames, TArray<uint32>* OutPackageChecksums = nullptr);` (scope `UE::MeshPartition::EditorUtils`) — Compute the combined PackageHash for a set of packages @param AssetRegistry the asset registry used to query each package's file hash.  You should call AssetRegistry.WaitForCompletion() prior to calling this function. @param PackageNames the set of Packages to compute the hash of. Assumed to already be in a deterministic sorted order. @param OutPackageChecksums if non-null, a package checksum is appended for each input Package
- L48 _prototype_ `FGuid ComputeClassHash(TArrayView<const UClass*> Classes, TArray<uint32>* OutClassChecksums = nullptr);` (scope `UE::MeshPartition::EditorUtils`) — Compute the combined ClassHash for a set of classes (hash of their MegaMeshClassVersion metadata) This is used to detect when a modifier implementation has changed. @param Classes the set of classes to compute the hash of. @param OutClassChecksums if non-null, a class checksum is appended to the array for each input Class
- L52 _prototype_ `bool PackageHashIsUpToDate(const MeshPartition::FCompiledSectionBuildInfo& BuildInfo, IAssetRegistry& AssetRegistry);` (scope `UE::MeshPartition::EditorUtils`) — Check if the package and class hashes recorded on a compiled section are up to date
- L53 _prototype_ `bool ClassHashIsUpToDate(const MeshPartition::FCompiledSectionBuildInfo& BuildInfo);` (scope `UE::MeshPartition::EditorUtils`)
- L60 _prototype_ `TArray<FGuid> FindMatchingCompiledSectionsFromPackageHashes( TArrayView<const FCompiledSectionDescriptor> CompiledSectionDescriptorsToSearch, const MeshPartition::FCompiledSectionBuildInfo& BuildInfo, IAssetRegistry& AssetRegistry);` (scope `UE::MeshPartition::EditorUtils`) — Find all pre-existing compiled sections that match BuildInfo by identity, BuildVariantHash, ModifierSetHash, PackageHash, and ClassHash. Returns GUIDs for all matching siblings (e.g. N grid-split sections from the same group). Empty result means no reuse is possible. Does not require loading modifiers.
- L69 _prototype_ `TArray<FGuid> FindMatchingCompiledSectionsFromModifierHash( TArrayView<const FCompiledSectionDescriptor> CompiledSectionDescriptorsToSearch, const MeshPartition::FCompiledSectionBuildInfo& BuildInfo);` (scope `UE::MeshPartition::EditorUtils`) — Find all pre-existing compiled sections that match BuildInfo by identity, BuildVariantHash, and ModifiersHash. Returns GUIDs for all matching siblings. Empty result means no reuse is possible.
- L78 _prototype_ `bool ValidateObjectsAreUnloaded(TConstArrayView<TWeakObjectPtr<AActor>> InActorsToValidate);` (scope `UE::MeshPartition::EditorUtils`) — Check if a set of objects are unloaded, and if not, log the GC refs that are keeping them from being garbage collected @param a list of weak object pointers to actors that should have been unloaded in a call to GarbageCollect @return true if the objects were unloaded, false if any are still in memory
- L86 _prototype_ `UStaticMesh* CreateStaticMesh(UObject* InOuter, const FName InStaticMeshName);` (scope `UE::MeshPartition::EditorUtils`) — Creates a static mesh UObject. @param InOuter The outer UObject to use when creating the UStaticMesh. @param InStaticMeshName The name to use as a base to generate a unique name. @return The created UStaticMesh.
- L95 _prototype_ `void BuildSourceModel(FStaticMeshSourceModel& OutSourceModel, const FMeshData& InBuiltMesh, bool bInRecomputeNormals = false, bool bInRecomputeTangents = true);` (scope `UE::MeshPartition::EditorUtils`) — Builds a FStaticMeshSourceModel from the provided built MegaMesh Mesh. @param OutSourceModel The result of the conversion. @param InBuiltMesh The Mesh to use as source. @param bInRecomputeNormals Should normals be recomputed while building the static mesh @param bInRecomputeTangents Should tangents be recomputed while building the static mesh
- L114 _prototype_ `void FinalizeStaticMesh(const FFinalizeStaticMeshParams& InParams);` (scope `UE::MeshPartition::EditorUtils`) — Finalizes the build of the provided static mesh given the settings contained in the passed struct.
- L132 _prototype_ `ITargetPlatform* GetPreviewPlatform(FName& OutPreviewPlatformName);` (scope `UE::MeshPartition::EditorUtils`) — Get the current preview platform, if any (null if no preview is set) @param OutPreviewPlatformName The name of the preview platform, only valid if ITargetPlatform is returned
- L139 _prototype_ `TArray<ITargetPlatform*> GetTargetPlatforms();` (scope `UE::MeshPartition::EditorUtils`) — Return the set of current target platforms.  When cooking, this will be the set of active target platforms. When preview mode is active, it will be the preview platform (as best we can determine). Otherwise it will be the current platform.
- L142 _prototype_ `UMaterialInstanceDynamic* GetOrCreateMaterialInstance(UMaterialInstanceDynamic* InMID, const UMaterialInterface* InBaseMegaMeshMaterial, UObject* InOuter, const FName& InName, EObjectFlags InAdditionalObjectFlags);` (scope `UE::MeshPartition::EditorUtils`) — Creates or reuses a dynamic material instance.

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionEditorWorldSubsystem.h` (Public)


#### class `UE::MeshPartition::UMeshPartitionEditorWorldSubsystem`  
`class UMeshPartitionEditorWorldSubsystem : public UTickableWorldSubsystem`  
_L12-24_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UTickableWorldSubsystem`
- L16 _public function_ `virtual bool IsTickable() const override`
- L17 _public function_ `virtual bool IsTickableInEditor() const override`
- L18 _public function_ `virtual bool DoesSupportWorldType(EWorldType::Type InWorldType) const override`
- L19 _public prototype_ `virtual TStatId GetStatId() const override;`
- L21 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L23 _public prototype_ `static void ReportSectionStatus();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionFarFieldTransformer.h` (Public)


#### struct `UE::MeshPartition::FFarFieldTransformer`  
`struct FFarFieldTransformer : public MeshPartition::FTransformer`  
_L22-43_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `MeshPartition::FTransformer`
- desc: Mesh Partition Transformer producing and attaching a far field mesh for each transformer unit present in the execution context. Should be placed relatively early in the pipeline to avoid being executed after a subsection transformer.
- L27 _public prototype_ `FFarFieldTransformer() = default;`
- L29 _public prototype_ `virtual bool Execute(MeshPartition::FTransformerContext& InTransformerContext) const override;`
- L31 _public prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& InDependencies) const override;`
- L34 _private prototype_ `TArray<UStaticMesh*> CreateStaticMeshes(MeshPartition::FTransformerContext& InTransformerContext) const;`
- L36 _private prototype_ `void BuildStaticMesh(MeshPartition::FTransformerContext& InTransformerContext, UE::Tasks::TTask<TArray<UStaticMesh*>>& InCreateStaticMeshesTask, const int32 InTransformerUnitIndex) const;`
- L38 _private prototype_ `void FinalizeStaticMeshes(MeshPartition::FTransformerContext& InTransformerContext, UE::Tasks::TTask<TArray<UStaticMesh*>>& InCreateStaticMeshesTask) const;`
- L42 _private member_ `float FarFieldMeshEdgeLength = 1000;` — `UPROPERTY(EditAnywhere, Category="Far Field", meta=(ToolTip="Target edge length used by the simplifier when building the far field mesh."))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionGroupRegistry.h` (Public)


#### class `UE::MeshPartition::FModifierGroupRegistry`  
`class FModifierGroupRegistry`  
_L25-126_
- desc: Registry for managing collections of modifier groups within mesh partition workflows. This class maintains both a committed set of groups and a staged set that allows modifications to be previewed or accumulated before being finalized. Typical usage flow: - StageGroup() to prepare a new or modified group. - CommitStagedGroup() to move it into the persistent registry. - RevertStagedGroup() to discard staged changes. - RemoveGroup() to fully delete a committed group.
- L28 _public typedef_ `using FGroupKeyToGroup = TMap<FGuid, MeshPartition::FModifierGroup>;`
- L36 _public prototype_ `static FGuid GetGroupRegistryKey(const MeshPartition::FModifierGroup& InGroup);` — Generates a unique registry key for the given group based on its contents. @param InGroup The group to evaluate. @return A unique FGuid representing the group.
- L44 _public prototype_ `FGuid StageGroup(const MeshPartition::FModifierGroup& InGroup);` — Adds a group to the staged collection, pending commit. @param InGroup The group to stage. @return A unique FGuid representing the staged group.
- L52 _public prototype_ `bool CommitStagedGroup(const FGuid& InGroupKey);` — Moves a staged group into the committed collection. @param InGroupKey The key identifying the staged group to commit. @return true if the group have been successfully committed.
- L60 _public prototype_ `bool RevertStagedGroup(const FGuid& InGroupKey);` — Discards a staged group without committing it. @param InGroupKey The key identifying the staged group to revert. @return true if the group have been successfully reverted.
- L67 _public prototype_ `void RemoveGroup(const FGuid& InGroupKey);` — Removes a committed group from the registry. @param InGroupKey The key identifying the group to remove.
- L72 _public prototype_ `void Reset();` — Clears both committed and staged groups.
- L83 _public prototype_ `void Reset(TConstArrayView<const MeshPartition::FModifierGroup> InModifierGroups);` — Resets the modifier group registry with a predefined set of groups. This clears any existing committed and staged groups, then populates the registry with the provided collection. Each group is keyed using its generated registry key. @param InModifierGroups  Array of modifier groups to register as the initial state. All groups are considered committed after initialization.
- L86 _public function_ `const FGroupKeyToGroup& GetGroups() const` — @return The committed group map.
- L89 _public function_ `const FGroupKeyToGroup& GetStagedGroups() const` — @return The staged group map.
- L97 _public prototype_ `const MeshPartition::FModifierGroup* FindGroup(const FGuid& InKey) const;` — Finds a committed group by its key. @param InKey The group identifier. @return Pointer to the group if found, otherwise nullptr.
- L105 _public prototype_ `const MeshPartition::FModifierGroup* FindStagedGroup(const FGuid& InKey) const;` — Finds a staged group by its key. @param InKey The group identifier. @return Pointer to the staged group if found, otherwise nullptr.
- L113 _public prototype_ `TArray<MeshPartition::FModifierGroup> FindGroupsContainingModifiers(TConstArrayView<MeshPartition::FModifierDesc> InModifiers) const;` — Searches for groups containing the given set of modifiers. @param InModifiers List of modifiers to search for. @return Array of groups that contain at least one of the specified modifiers.
- L121 _public prototype_ `TArray<MeshPartition::FModifierGroup> FindGroupsIntersectingBounds(TConstArrayView<const FBox> InBounds) const;` — Searches for groups intersecting the provided bounds. @param InBounds List of bounds to check for. @return Array of groups that contain at least one of the specified bounds.
- L124 _private member_ `FGroupKeyToGroup Groups;`
- L125 _private member_ `FGroupKeyToGroup StagedGroups;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionHeightmapImporter.h` (Public)


#### struct `UE::MeshPartition::FHeightmapImportParams`  
`struct FHeightmapImportParams`  
_L22-43_
- desc: List of parameters for the MegaMesh Heightmap Importer.
- L24 _public member_ `UWorld* World;`
- L27 _public member_ `FString HeightmapFilename;` — Filename of the heightmap to use for import.
- L30 _public member_ `FInt32Point MeshResolution;` — Number of vertices in X/Y dimension for the generated mesh.
- L33 _public member_ `FVector MeshSize;` — World space size of the generated mesh.
- L36 _public member_ `FInt32Point SectionsResolution;` — Number of sections in X/Y dimension.
- L39 _public member_ `bool bSaveAndUnload;` — Save and unload sections as they are created.
- L42 _public member_ `FInt32Point LocationVolumesResolution;` — Number of location volumes in X/Y dimension.

#### struct `UE::MeshPartition::FSectionInfo`  
`struct FSectionInfo`  
_L48-54_
- desc: Information about generated sections within an axis-aligned grid.
- L50 _public member_ `FInt32Point IndexXY;` — 2D index within the uniform grid
- L51 _public member_ `FInt32Point Resolution;` — Mesh resolution within the section (as quads)
- L52 _public member_ `FVector2d MinUV;` — Start of the section expressed as UV-style [0..1] values relative to the overall mesh size.
- L53 _public member_ `FVector2d MaxUV;` — End of the section similar to MinUV.

#### class `UE::MeshPartition::FHeightmapImporter`  
`class FHeightmapImporter`  
_L59-110_
- desc: Imports a heightmap texture file as a new MegaMesh actor which is automatically partitioned along a grid where each tile will have the specified maximum number of vertices.
- L62 _public prototype_ `FHeightmapImporter(const FHeightmapImportParams& InParams);`
- L69 _public prototype_ `bool Import(FPackageSourceControlHelper* InSourceControlHelper);` — Execute the import operation. If an FPackageSourceControlHelper is provided, newly created packages will also be added to source control. Returns true if the operation succeeded, false otherwise. Note: On failure, a diagnostic error message can be retrieved with `GetErrorText`.
- L72 _public function_ `const FText& GetErrorText() const` — Returns the reason for failure, if any occurred.
- L75 _public function_ `AMeshPartition* GetMegaMesh() const` — Returns the newly created mega mesh actor
- L78 _public prototype_ `static TArray<FSectionInfo> GetSectionInfos(const FHeightmapImportParams& Params);` — Returns the sections that need to be generated based on a given set of parameters.
- L81 _private prototype_ `bool BeginLoadHeightmapFile();`
- L82 _private prototype_ `void SaveActorPackages(const TArray<TWeakObjectPtr<AActor>>& InActorsToSave);`
- L85 _private prototype_ `void CancelAndWait();` — Cancel and block until all outstanding tasks are finished executing.
- L87 _private prototype_ `void UnloadActors(const TArray<TWeakObjectPtr<AActor>>& InActorsToUnload) const;`
- L89 _private member_ `FHeightmapImportParams Params;`
- L91 _private member_ `Tasks::TTask<TArray64<uint16>> LoadHeightmapTask;`
- L93 _private member_ `FInt32Point HeightmapResolution = {0};`
- L95 _private member_ `AMeshPartition* MegaMesh = nullptr;`
- L97 _private member_ `FText ErrorText;`
- L99 _private member_ `TArray<TPair<int, Tasks::FTask>> MeshTasks;`
- L100 _private member_ `TArray<MeshPartition::UMeshProviderModifier*> MegaMeshMeshProviders;`
- L104 _private member_ `TArray<Geometry::FDynamicMesh3> Meshes;` — The importer operates on isolated FDynamicMeshes on parallel threads and are then moved onto the output mesh provider on the game thread. This ensures the correct events/callbacks are fired for the DynamicMeshComponent to ensure bounds are computed, proxies recreated, etc.
- L107 _private member_ `TArray<FString> SavedPackages;` — Retain a list of all packages that were saved and unloaded in case the user cancels so they can be reverted.
- L109 _private member_ `bool bIsCancelled = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionInteractiveSection.h` (Public)


#### enum `UE::MeshPartition::EInteractiveSectionState`  
`enum class EInteractiveSectionState : uint8`  
_L23-30_
- L25 _public enumerator_ `Initialized = 0`
- L26 _public enumerator_ `BuildingBase`
- L27 _public enumerator_ `PreparingBase`
- L28 _public enumerator_ `BasePrepared`
- L29 _public enumerator_ `BuildingPreviewMesh`

#### class `UE::MeshPartition::AInteractiveSection`  
`class AInteractiveSection : public AActor`  
_L39-146_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `AActor`
- desc: This is a transient actor, expressing an interactive part of a MegaMesh. This means a region of the MegaMesh where processing is optimized for speed so a modifier can be interacted with and respond in a timeframe suited for interaction. It only exists in the editor.
- L44 _public prototype_ `AInteractiveSection();`
- L47 _public prototype_ `void Tick(float InDeltaSeconds) override;` — AActor Implementation
- L48 _public function_ `virtual bool ShouldTickIfViewportsOnly() const override`
- L51 _public prototype_ `void Update();`
- L52 _public prototype_ `void SetParent(AMeshPartition* InMegaMesh);`
- L54 _public prototype_ `UMeshPartitionEditorComponent* GetMegaMeshEditorComponent() const;`
- L57 _public function_ `const TArray<TObjectPtr<MeshPartition::UModifierComponent>>& GetInteractiveModifiers() const` — @return The current Interactive Modifiers used by this interactive section.
- L64 _public prototype_ `void SetInteractiveModifiers(const TArray<MeshPartition::UModifierComponent*>& InModifiers, MeshPartition::FBuilderSettings&& InSettings);` — Setup the current interactive modifier to be used by this interactive section. @param InModifiers The modifiers to setup. @param InSettings The settings used to build the initial base on top of which to apply the interactive modifier.
- L67 _public prototype_ `void ClearInteractiveModifiers();` — Resets the current interactive modifiers for this interactive section. Cancelling all pending tasks if possible.
- L70 _public prototype_ `void OnModifierChanged();` — Called when the current interactive modifier changed to update the interactive section.
- L78 _public prototype_ `static FModifierFilterFunc InteractiveSectionBaseFilter(const TArray<MeshPartition::UModifierComponent*>& InModifiers, TConstArrayView<FName> InTypePriorities);` — Will filter any modifiers that should be applied after the provided modifiers. Will also filter all provided modifiers. @param InModifiers The modifiers that will be applied on top of the base. @param InTypePriorities The type priorities to use. @return A FModifierFilterFunc to be used in the builder.
- L84 _public prototype_ `void AddModifier(MeshPartition::UModifierComponent* InModifier);` — Adds a modifier to the list of managed interactive modifiers. @param InModifier The modifier to add.
- L90 _public prototype_ `void RemoveModifier(MeshPartition::UModifierComponent* InModifier);` — Removes a modifier to the list of managed interactive modifiers. @param InModifier The modifier to remove.
- L93 _public function_ `bool IsInteractiveSectionActive() const` — @return True if the interactive section is being used.
- L95 _public function_ `UMaterialInstanceDynamic* GetMaterialInstance() const`
- L96 _public function_ `void SetMaterialInstance(UMaterialInstanceDynamic* InMaterialInstance)`
- L100 _private prototype_ `void UpdateBuildingBase();` — Will transition and launch the preparing base task if building the initial base task completed.
- L103 _private prototype_ `void UpdatePreparingBase();` — Will transition and apply the current interactive modifier if preparing the base task completed.
- L106 _private prototype_ `void UpdateBuildingPreviewMesh();` — Will transition and setup the mesh component with the built result if the preview mesh is available and copies are done.
- L109 _private function_ `FMeshData& GetCurrentSourceBase()` — @return The current base mesh used as a source by the mesh builder.
- L112 _private function_ `FMeshData& GetCurrentCopySource()` — @return The current base mesh used as a copy source.
- L115 _private function_ `FMeshData& GetCurrentCopyDestination()` — @return The current base mesh used as a copy destination.
- L118 _private function_ `void RotateBaseMeshes()` — Rotates the basemeshes source, copy source, copy destination.
- L122 _private member_ `TObjectPtr<UPreviewMeshComponent> PreviewMeshComponent;` — `UPROPERTY(Transient)`
- L125 _private member_ `TArray<TObjectPtr<MeshPartition::UModifierComponent>> InteractiveModifiers;` — `UPROPERTY(Transient)`
- L128 _private member_ `TSoftObjectPtr<AMeshPartition> Parent;` — `UPROPERTY(Transient)`
- L131 _private member_ `TObjectPtr<UMaterialInstanceDynamic> MaterialInstance;` — `UPROPERTY(Transient)`
- L133 _private member_ `MeshPartition::FBuilderSettings BuildSettings;`
- L135 _private member_ `TArray<MeshPartition::FBuildTaskHandle> BaseBuildTasks;`
- L136 _private member_ `TArray<MeshPartition::FBuildTaskHandle> PreviewBuildTasks;`
- L137 _private member_ `Tasks::FTask BaseSetupTask;`
- L138 _private member_ `Tasks::FTask CopyTask;`
- L140 _private member_ `FMeshData BaseMeshes[3];`
- L141 _private member_ `uint32 CurrentSourceBase = 0;`
- L143 _private member_ `EInteractiveSectionState State;`
- L145 _private member_ `bool bPendingBuildIsOutdated = false;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionMaterialExpressionUtils.h` (Public)


#### class `UE::MeshPartition::UMaterialExpressionMeshPartitionResource`  
`class UMaterialExpressionMeshPartitionResource : public UMaterialExpression`  
_L27-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMaterialExpression`
- desc: Core MeshPartition material expression providing access to the channel(s) texture resource
- L34 _protected member_ `TWeakObjectPtr<UTexture2DArray> TextureParameter;` — `UPROPERTY(Transient)` — The actual texture assigned by the MeshPartition using the Material
- L37 _protected prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L38 _protected prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L41 _protected prototype_ `virtual FGuid& GetParameterExpressionId() override;`
- L42 _protected function_ `virtual bool CanReferenceTexture() const override`
- L43 _protected prototype_ `virtual UObject* GetReferencedTexture() const override;`
- L45 _protected function_ `virtual uint32 GetOutputType(int32 OutputIndex) override`

#### class `UE::MeshPartition::UMaterialExpressionMeshPartitionTexcoord`  
`class UMaterialExpressionMeshPartitionTexcoord : public UMaterialExpression`  
_L55-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMaterialExpression`
- desc: Core MeshPartition material expression providing access to the channel texcoord at the fragment
- L62 _protected prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L63 _protected prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L66 _protected function_ `virtual uint32 GetOutputType(int32 OutputIndex) override`

#### class `UE::MeshPartition::UMaterialExpressionMeshPartitionChannelSample`  
`class UMaterialExpressionMeshPartitionChannelSample : public UMaterialExpression`  
_L76-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMaterialExpression`
- desc: Core MeshPartition expression allowing to sample one of the channels at a texcoord location
- L83 _protected prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L84 _protected prototype_ `virtual EMaterialValueType GetInputValueType(int32 InputIndex) override;`
- L85 _protected prototype_ `virtual EMaterialValueType GetOutputValueType(int32 OutputIndex) override;`
- L86 _protected prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L93 _public member_ `FExpressionInput ChannelTextureInput;` — `UPROPERTY()` — Input: MeshPartition Resource from the shared parameter expression
- L97 _public prototype_ `TArray<FName> GetDefinitionChannels() const;` — `UFUNCTION(CallInEditor)` — Retrieve the list of Channels available in the associated MeshPartitionDefinition
- L98 _public prototype_ `int32 FindChannelIndex(FName InChannel) const;`
- L102 _public member_ `FName Channel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshPartition, meta = (GetOptions = "GetDefinitionChannels", NoResetToDefault))` — The name of the channel sample by this expression
- L106 _public member_ `TObjectPtr<UMeshPartitionDefinition> MeshPartitionDefinition;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshPartition)` — The MeshPartition definition associated providing the list of channels

#### class `UE::MeshPartition::UMaterialExpressionMeshPartitionChannelSampleIndex`  
`class UMaterialExpressionMeshPartitionChannelSampleIndex : public UMaterialExpression`  
_L114-139_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMaterialExpression`
- desc: Core MeshPartition expression allowing to sample one of the channels at a texcoord location
- L121 _protected prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L122 _protected prototype_ `virtual EMaterialValueType GetInputValueType(int32 InputIndex) override;`
- L123 _protected prototype_ `virtual EMaterialValueType GetOutputValueType(int32 OutputIndex) override;`
- L124 _protected prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L130 _public member_ `FExpressionInput ChannelTextureInput;` — `UPROPERTY()` — Input: MeshPartition Resource from the shared parameter expression
- L134 _public member_ `FExpressionInput ChannelIndex;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstChannelIndex' if not specified"))` — The name of the channel sample by this expression
- L138 _public member_ `int32 ConstChannelIndex = 0;` — `UPROPERTY(EditAnywhere, Category = MeshPartition, meta = (OverridingInputProperty = "ChannelIndex"))` — only used if A is not hooked up

#### class `UE::MeshPartition::UMaterialExpressionMeshPartitionInspector`  
`class UMaterialExpressionMeshPartitionInspector : public UMaterialExpression`  
_L146-163_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMaterialExpression`
- desc: Helper material expression providing an easy channel inspector rendering
- L153 _protected prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L154 _protected prototype_ `virtual EMaterialValueType GetInputValueType(int32 InputIndex) override;`
- L155 _protected prototype_ `virtual EMaterialValueType GetOutputValueType(int32 OutputIndex) override;`
- L156 _protected prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L162 _protected member_ `FExpressionInput ChannelTextureInput;` — `UPROPERTY()` — Input: MeshPartition Resource from the shared parameter expression

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshPartition` (scope `UE`)
- L13 _namespace_ `namespace MaterialExpression` (scope `UE::MeshPartition`)
- L16 _prototype_ `int32 CompilePickChannelTexture(class FMaterialCompiler* Compiler, int32 InTextureCollection_IDX, int32 InChannelPage_IDX);` (scope `UE::MeshPartition::MaterialExpression`)
- L17 _prototype_ `int32 CompileFetchChannel(class FMaterialCompiler* Compiler, int32 InTextureCollection_IDX, int32 InChannel_IDX);` (scope `UE::MeshPartition::MaterialExpression`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionMeshBuilder.h` (Public)


#### struct `UE::MeshPartition::GridHelpers::FGridDimensions`  
`struct FGridDimensions`  
_L63-70_
- desc: Result of grid dimension computation: snapped origin + per-axis counts + per-axis extent.
- L65 _public member_ `FVector SnappedMin;`
- L66 _public member_ `FIntVector OriginCoord;`
- L67 _public member_ `FIntVector CellNumber;`
- L68 _public member_ `FVector CellExtent;` — Per-axis size of one cell. (CellSize, CellSize, CellSize) in 3D; in 2D the Z component carries the full input Z extent.
- L69 _public member_ `int32 TotalCells;`

#### class `UE::MeshPartition::FMeshBuilder`  
`class FMeshBuilder`  
_L172-214_
- desc: Class used to Build FDynamicMesh3 + optional FDynamicMeshAABBTree3 from a build settings and modifier group. It has an optional internal local cache and can write/read to/from ddc based on the builder settings.
- L178 _protected prototype_ `FMeshBuilder();`
- L185 _public prototype_ `MeshPartition::FBuildTaskHandle Build(const MeshPartition::FBuilderSettings& InSettings, const MeshPartition::FModifierGroup& InModifierGroup, bool bAllowDDC);` — Start the async mesh build task or returns a result from its internal cache.
- L190 _public prototype_ `void Cancel(const TSharedPtr<MeshPartition::FBuildTask>& InBuildTask);` — Cancel an in flight async mesh build task.
- L195 _public prototype_ `void ClearCache();` — Clears the internal cache.
- L200 _public prototype_ `double GetCacheTotalMemoryUsageMB() const;` — Returns the total size used by the cache (Mesh + Spatial)
- L206 _private prototype_ `MeshPartition::FBuildTaskHandle Build_Internal(const MeshPartition::FBuilderSettings& InSettings, MeshPartition::FModifierGroup&& InModifierGroup, bool bAllowDDC);` — Start the async mesh build task or returns a result from its internal cache.  This version can be called on any thread, and requires the modifier group to be prepared ahead of time.
- L208 _private prototype_ `bool QueryCache(const MeshPartition::FBuilderSettings& InSettings, FBlake3Hash InKey, MeshPartition::FBuildTaskHandle& OutHandle);`
- L209 _private prototype_ `void EnforceMemoryBudget();`
- L211 _private member_ `mutable UE::FMutex CacheMutex;`
- L212 _private member_ `TLruCache<FBlake3Hash, TSharedPtr<MeshPartition::FBuildTask>> Cache;`
- L213 _private member_ `double LastEnforceMemoryBudget = 0.0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MeshPartition` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MeshPartition` (scope `UE`)
- L18 _namespace_ `namespace FilterHelpers` (scope `UE::MeshPartition`)
- L20 _prototype_ `uint32 FindLayerPriorityIndexFromName(TConstArrayView<FName> InLayerStack, const FName& InLayerName);` (scope `UE::MeshPartition::FilterHelpers`)
- L25 _prototype_ `FModifierFilterFunc FilterModifiersByLastLayerToBuild(const FName& InLastLayerToBuild, bool bInInclusive = true);` (scope `UE::MeshPartition::FilterHelpers`) — Filters the list of modifier descriptors to remove any modifiers which belong in layers higher than the passed layer.
- L30 _prototype_ `FModifierFilterFunc FilterModifiersUntilSubpriorityWithinLayer(const FName& InLastLayerToBuild, double InLastSubPriorityToBuild, bool bInInclusive = true);` (scope `UE::MeshPartition::FilterHelpers`) — Filters the list of modifier descriptors to remove any modifiers which belong in layers higher than the passed layer and sub priority.
- L35 _prototype_ `FModifierFilterFunc FilterModifiersByLastModifierToBuild(const MeshPartition::FModifierDesc& InModifierDescriptor, bool bInInclusive = true);` (scope `UE::MeshPartition::FilterHelpers`) — Filters the list of modifier descriptors to remove any modifiers which are sorted after the passed modifier.
- L40 _prototype_ `FModifierFilterFunc FilterModifiersByIndexToBuild(const uint32& InIndexToBuild, bool bInInclusive);` (scope `UE::MeshPartition::FilterHelpers`) — Filters the list of modifier descriptors to remove any modifiers which belong in layers higher than the passed layer index.
- L45 _prototype_ `FModifierFilterFunc FilterOnlyBaseModifiers();` (scope `UE::MeshPartition::FilterHelpers`) — Filters the list of modifier descriptors to keep only the bases.
- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace MeshPartition` (scope `UE`)
- L48 _namespace_ `namespace Build` (scope `UE::MeshPartition`)
- L51 _prototype_ `TArray<MeshPartition::FBuildTaskHandle> LaunchBuilds(const MeshPartition::FBuilderSettings& InSettings);` (scope `UE::MeshPartition::Build`) — Starts the async mesh build tasks.
- L54 _prototype_ `void Wait(TConstArrayView<MeshPartition::FBuildTaskHandle> InTasks);` (scope `UE::MeshPartition::Build`) — Blocks the current thread until all async mesh build tasks are complete
- L57 _prototype_ `bool AreAllTasksComplete(TConstArrayView<MeshPartition::FBuildTaskHandle> InTasks);` (scope `UE::MeshPartition::Build`) — Returns true if all InTasks are completed.
- L60 _namespace_ `namespace UE`
- L60 _namespace_ `namespace MeshPartition` (scope `UE`)
- L60 _namespace_ `namespace GridHelpers` (scope `UE::MeshPartition`)
- L79 _prototype_ `FVector ComputeLocalAnchor(const MeshPartition::FGridSettings& InGridSettings, const FTransform& InLocalToWorld);` (scope `UE::MeshPartition::GridHelpers`) — Returns the snap anchor in translated by the passed argument. Translation-only: LocalAnchor = InGridSettings.WorldOriginOffset - InLocalToWorld.GetTranslation(). @param InGridSettings Grid configuration carrying the world-space WP origin. @param InLocalToWorld The transform to offset the grid. Pass FTransform::Identity for non world space aligned splits. @return The snap anchor expressed in the same space as the mesh bounds (mesh-local).
- L93 _prototype_ `FGridDimensions ComputeGridDimensions(const FBox& InBounds, const MeshPartition::FGridSettings& InGridSettings, const FTransform& InLocalToWorld);` (scope `UE::MeshPartition::GridHelpers`) — Computes grid dimensions from bounds and grid configuration. Snaps bounds min to grid-aligned coordinate (floor) anchored on ComputeLocalAnchor(InGridSettings, InLocalToWorld), then divides the snapped extents. With WorldOriginOffset=Zero and InLocalToWorld=Identity, this reproduces the legacy world-zero-anchored snap. Pass the actor's LocalToWorld to align the lattice with a WP runtime grid even when the MeshPartition actor is translated. This is the single source of truth for grid dimension logic — used by both BuildSections and EstimateGridCells. @param InBounds The bounding box to subdivide (mesh-local space when InLocalToWorld is the actor transform). @param InGridSettings Grid configuration. CellSize must be > 0; bIs2D collapses Z into a single column; WorldOriginOffset offsets the lattice. @param InLocalToWorld Actor transform used to shift WorldOriginOffset into the same space as InBounds. Pass FTransform::Identity for non world space aligned splits. @return Grid dimensions including snapped origin, per-axis cell counts, and per-axis cell extent.
- L104 _prototype_ `TMap<FIntVector, MeshPartition::FMeshData> BuildGridCellMeshes(const MeshPartition::FMeshData& InMesh, const MeshPartition::FGridSettings& InGridSettings, const FTransform& InLocalToWorld);` (scope `UE::MeshPartition::GridHelpers`) — Splits a mesh into grid-aligned cells and returns a map keyed by absolute world-space grid coordinates. Each coordinate component = floor((cellLocalMin - LocalAnchor) / CellSize), making it independent of the input bounds. Empty cells are excluded from the result. @param InMesh The mesh to split. @param InGridSettings Grid configuration. CellSize must be > 0; bIs2D collapses Z (all cells share Z=0; cell mesh spans full source Z range). @param InLocalToWorld Actor transform used by ComputeLocalAnchor to align cells with a WP runtime grid. Pass FTransform::Identity for non world space aligned splits. @return Map from absolute grid coordinate to cell mesh. Only non-empty cells are included.
- L107 _namespace_ `namespace UE`
- L107 _namespace_ `namespace MeshPartition` (scope `UE`)
- L107 _namespace_ `namespace BuildHelpers` (scope `UE::MeshPartition`)
- L115 _prototype_ `bool ShouldApplyBaseSimplificationForGroup(const MeshPartition::FModifierGroup& InGroup, const MeshPartition::FBuilderSettings& InSettings);` (scope `UE::MeshPartition::BuildHelpers`) — Returns true if the base simplifications is enabled, taking into account the provided group and build settings. @param InGroup The group to check. @param InSettings The build settings associated with the provided group. @return True if the base simplifications is enabled.
- L123 _prototype_ `FGuid ComputeBaseCacheKey(const MeshPartition::FModifierGroup& InGroup, const MeshPartition::FBuilderSettings& InSettings);` (scope `UE::MeshPartition::BuildHelpers`) — Returns the cache key for the bases of the provided group, taking into account the build settings. @param InGroup The group used to compute the cache key. @param InSettings The build settings associated with the provided group. @return An FGuid, representing the base cache key.
- L132 _prototype_ `UE::Tasks::FTask ProcessModifierGroup( const MeshPartition::FBuilderSettings& InSettings, MeshPartition::FModifierGroup InModifierGroup, TSharedPtr<MeshPartition::FModifierTaskGraph> InTaskGraph);` (scope `UE::MeshPartition::BuildHelpers`) — Collapses the modifier stack. Returning a modified FDynamicMesh3 provided as argument. @param InSettings The build settings associated with the provided group @param InModifierGroup The modifier group to process. @param InTaskGraph The task graph used for the processing. @return A processing task.
- L137 _prototype_ `TArray<MeshPartition::FModifierDesc> InitializeModifierDescriptors(const MeshPartition::FBuilderSettings& InSettings);` (scope `UE::MeshPartition::BuildHelpers`)
- L150 _prototype_ `TArray<MeshPartition::FMeshData> BuildSections(const MeshPartition::FMeshData& InMesh, const GridHelpers::FGridDimensions& InGridDimensions, const bool bInFilterEmptyMeshes);` (scope `UE::MeshPartition::BuildHelpers`) — Splits the given mesh into multiple meshes according to pre-computed grid dimensions. Callers compute FGridDimensions via GridHelpers::ComputeGridDimensions and pass it here -- this avoids recomputing dimensions when the caller already needs them (e.g. BuildGridCellMeshes), and keeps BuildSections agnostic of how the grid was resolved (FGridSettings, FTransform, future fields, ...). @param InMesh The mesh to split. @param InGridDimensions Pre-computed grid dimensions. Determines per-cell extent, count, and snapping origin. @param bInFilterEmptyMeshes When true, empty cells are removed from the output; when false all cells are included. @return An array containing the splitted mesh.
- L160 _prototype_ `MeshPartition::FMeshData SimplifyMesh(const MeshPartition::FMeshData& InSourceMesh, const float InEdgeLength, const bool bInTransferAttributes, const bool bTransferNormals);` (scope `UE::MeshPartition::BuildHelpers`) — Produces a simplified version of the input mesh by collapsing edges whose lengths fall below the requested tolerance. @param InSourceMesh          The source mesh to simplify. @param InEdgeLength          Target edge-length tolerance in Unreal units. @param bInTransferAttributes If true, per-element attributes are propagated to the simplified mesh. @param bTransferNormals 		If true, normals will be propagated to the simplified mesh. @return A new mesh containing the simplified geometry.
- L165 _namespace_ `namespace UE`
- L165 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionMeshBuilderCommon.h` (Public)


#### enum `UE::MeshPartition::EFilterBoundsMode`  
`enum class EFilterBoundsMode`  
_L24-30_
- L27 _public enumerator_ `Inclusive` — Include triangles inside filter bounds.
- L29 _public enumerator_ `Exclusive` — Exclude triangles inside filter bounds.

#### struct `UE::MeshPartition::FBuilderSettings`  
`struct FBuilderSettings`  
_L32-103_
- L35 _public member_ `MeshPartition::EBuildType BuildType = MeshPartition::EBuildType::Request;` — The type of build requested.
- L37 _public member_ `FTransform Transform;`
- L40 _public member_ `TArray<MeshPartition::UModifierComponent*> ModifiersToProcess;` — List of modifiers (including base modifiers) to process
- L43 _public member_ `TArray<FName> TypePriorities;` — Modifier Type priority stack. Modifiers are sorted according to what index their type appears in this array
- L49 _public member_ `TArray<Geometry::FOrientedBox3d> FilterBounds;` — Optional bounds to filter the output mesh triangles. Only triangles fully contained within the bounds will be kept.
- L51 _public member_ `MeshPartition::EFilterBoundsMode FilterBoundsMode = EFilterBoundsMode::Inclusive;`
- L54 _public member_ `FModifierFilterFunc ModifierFilter;` — Optional filter function for the list of modifiers to process.
- L57 _public member_ `TOptional<TNotNull<FMeshData*>> BaseMesh;` — Optional if set, will be used instead of base modifiers.
- L63 _public member_ `double MaxSectionComplexity;` — Maximum complexity value allowed when building meshes. The system will aggregate modifiers into groups which attempt to satisfy this constraint.
- L66 _public member_ `bool bRecomputeNormals = false;` — Should we recompute normals after processing modifiers.
- L69 _public member_ `bool bRecomputeTangents = false;` — Should we recompute tangents after processing modifiers.
- L78 _public member_ `TOptional<FSimplifierOptions> SimplifierOptions;` — Optional settings to run a simplifier pass on the result of the processing pipeline.
- L81 _public member_ `TOptional<FChannelCollectionUVLayoutOptions> TexcoordGenerationOptions;` — Optional settings to run a texcoord generation pass on the result of the processing pipeline.
- L90 _public member_ `TOptional<FChannelRenderSettings> ChannelRenderSettings;` — Optional settings which control channel texture rendering. If unset, no channel texture will be produced
- L93 _public member_ `bool bCacheResult = false;` — Cache result
- L96 _public member_ `bool bBuildSpatial = false;` — Build spatial query structure
- L99 _public member_ `bool bAllowDDCRead = false;` — Should builds with these settings be allowed to use the DDC cache to avoid processing.
- L102 _public member_ `bool bAllowDDCWrite = false;` — Should builds produced with these settings be allowed to store their results in DDC.

#### struct `UE::MeshPartition::FBuilderSettings::FSimplifierOptions`  
`struct FSimplifierOptions`  
_L71-75_
- L73 _public member_ `float TargetEdgeLength;`
- L74 _public member_ `int32 MinVertexCount;`

#### struct `UE::MeshPartition::FBuilderSettings::FChannelRenderSettings`  
`struct FChannelRenderSettings`  
_L83-87_
- L85 _public member_ `MeshPartition::FChannelMap ChannelMap;`
- L86 _public member_ `float TexelSize;`

#### struct `UE::MeshPartition::FBuildTaskHandle`  
`struct FBuildTaskHandle`  
_L114-141_
- desc: Handle on a TSharedPtr<MeshPartition::FBuildTask>. This class is used so that multiple build requests can share the same Task. Handle can be cancelled if it is the only handle left. Handles have a shared pointer on their build task so that the underlying cache can be cleared without breaking in-flight tasks.
- L117 _public prototype_ `FBuildTaskHandle() = default;`
- L118 _public prototype_ `~FBuildTaskHandle();`
- L119 _public prototype_ `FBuildTaskHandle(MeshPartition::FBuildTaskHandle&& InHandle);`
- L120 _public prototype_ `FBuildTaskHandle(const MeshPartition::FBuildTaskHandle& InHandle);`
- L121 _public prototype_ `FBuildTaskHandle& operator=(const MeshPartition::FBuildTaskHandle& InHandle);`
- L122 _public prototype_ `FBuildTaskHandle& operator=(MeshPartition::FBuildTaskHandle&& InHandle);`
- L124 _public prototype_ `bool Wait() const;`
- L125 _public prototype_ `bool IsCompleted() const;`
- L126 _public prototype_ `void Cancel();`
- L128 _public function_ `bool IsCancelled() const`
- L129 _public function_ `const TSharedPtr<MeshPartition::FBuildTask>& GetTask() const`
- L134 _private prototype_ `FBuildTaskHandle(const TSharedPtr<MeshPartition::FBuildTask>& InBuildTask);`
- L135 _private prototype_ `void Release(const TSharedPtr<MeshPartition::FBuildTask>& InTask, bool bCancel);`
- L137 _private member_ `TSharedPtr<MeshPartition::FBuildTask> Task;`
- L140 _private member_ `bool bIsCancelled = false;` — This can be true without the underlying task being effectively cancelled if it has other existing handles.

#### struct `UE::MeshPartition::FBuildTask`  
`struct FBuildTask : public TSharedFromThis<MeshPartition::FBuildTask>`  
_L146-202_
- inherits: `TSharedFromThis<MeshPartition::FBuildTask>`
- desc: Task / Result / Cache entry class for the MeshPartition::FMeshBuilder
- L149 _public function_ `const FTransform& GetTransform() const`
- L150 _public function_ `const MeshPartition::FModifierGroup& GetGroup() const`
- L151 _public function_ `const SIZE_T GetByteCount() const`
- L153 _public prototype_ `TSharedPtr<const FMeshData> GetMesh() const;`
- L154 _public prototype_ `TSharedPtr<FMeshData> GetMutableMesh();`
- L156 _public prototype_ `TSharedPtr<const FMeshABBTree3> GetSpatial() const;`
- L158 _public prototype_ `TSharedPtr<const MeshPartition::FSectionChannels> GetSectionChannels() const;`
- L160 _public prototype_ `MeshPartition::FBuildTaskHandle CreateHandle();`
- L162 _public prototype_ `MeshPartition::FBuildPerfStats GetBuildPerfStats() const;`
- L164 _public prototype_ `bool Wait() const;`
- L171 _private member_ `std::atomic<int32> Handles = 0;` — Current user count for this task.
- L174 _private member_ `bool bIsCancelled = false;` — Will be true if this build has been invalidated.
- L177 _private member_ `bool bIsCached = false;` — If true, calling GetMutableMesh() will fail as we can't give up ownership of the DynamicMesh.
- L180 _private member_ `bool bBuildSpatial = false;` — If true, the task isn't completed without its Spatial member being built.
- L183 _private member_ `MeshPartition::FModifierGroup Group;` — Group representing all the modifiers which were aggregated and contributed to this mesh.
- L185 _private member_ `FTransform Transform;`
- L187 _private member_ `TSharedPtr<MeshPartition::FModifierTaskGraph> TaskGraph;`
- L190 _private member_ `Tasks::FTask BuildTask;` — Async task for modifier processing.
- L192 _private member_ `FBlake3Hash Key;`
- L195 _private member_ `SIZE_T MeshByteCount = 0;` — Results
- L196 _private member_ `TSharedPtr<FMeshData> Mesh;`
- L198 _private member_ `SIZE_T SpatialByteCount = 0;`
- L199 _private member_ `TSharedPtr<FMeshABBTree3> Spatial;`
- L201 _private member_ `TSharedPtr<MeshPartition::FSectionChannels> SectionChannels;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)
- L22 _typedef_ `using FModifierFilterFunc = TFunction<bool(const MeshPartition::FBuilderSettings&, const MeshPartition::FModifierDesc&)>;` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionMeshSkirt.h` (Public)


#### enum `UE::MeshPartition::EMeshSkirtDirectionMethod`  
`enum class EMeshSkirtDirectionMethod`  
_L17-21_
- reflection: `UENUM()`
- L19 _public enumerator_ `FixedDirection`
- L20 _public enumerator_ `VertexNormal`

#### struct `UE::MeshPartition::FMeshSkirtSettings`  
`struct FMeshSkirtSettings`  
_L24-52_
- reflection: `USTRUCT(MinimalAPI)`
- L31 _public member_ `float Width = 10.f;` — `UPROPERTY(EditAnywhere, Category = "MeshSkirt", meta = (ClampMin = 0))` — Distance to offset the skirt vertices from the boundary, in the local plane of the boundary
- L35 _public member_ `float PushDown = 10.f;` — `UPROPERTY(EditAnywhere, Category = "MeshSkirt", meta = (ClampMin = 0))` — Amount to push down the offset vertices
- L39 _public member_ `EMeshSkirtDirectionMethod PushMethod = EMeshSkirtDirectionMethod::VertexNormal;` — `UPROPERTY(EditAnywhere, Category = "MeshSkirt")` — Method to choose the direction to push offset vertices
- L43 _public member_ `FVector PushDirection = FVector(0, 0, -1);` — `UPROPERTY(EditAnywhere, Category = "MeshSkirt", meta = (EditCondition = "PushMethod==EMeshSkirtDirectionMethod::FixedDirection"))` — Direction to push the offset skirt vertices, if using a fixed direction Push Method
- L47 _public member_ `float VertexSnapTolerance = UE_SMALL_NUMBER;` — `UPROPERTY(EditAnywhere, Category = "MeshSkirt", AdvancedDisplay, meta = (ClampMin = 0))` — Consider vertices closer than this distance to be the same for purposes of boundary walking
- L51 _public member_ `float BoundaryMinPerimeter = 1000.f;` — `UPROPERTY(EditAnywhere, Category = "MeshSkirt", AdvancedDisplay, meta = (ClampMin = 0))` — Do not add skirts to boundaries with perimeter smaller than this (to skip mesh boundaries that are not section boundaries)

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MeshPartition` (scope `UE`)
- L54 _prototype_ `void AddMeshSkirt(FMeshData& InOutMeshData, const FMeshSkirtSettings& InSettings);` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionMeshView.h` (Public)


#### enum `UE::MeshPartition::EMeshViewComponents`  
`enum class EMeshViewComponents : int32`  
_L13-34_
- L15 _public enumerator_ `None = 0`
- L18 _public enumerator_ `VertexPos = (1 << 0)` — Reads or writes the vertex positions of the internal mesh.
- L27 _public enumerator_ `DynamicSubmesh = (1 << 1)` — When reading, this provides the view an FDynamicSubmesh3 of the region internal mesh inside the view bounds. When writing, this allows the view to inject new topology and replace existing triangles in the region with new ones. Writing a DynamicSubmesh is a stronger operation than VertexPos and will have a worse impact on performance. Prefer VertexPos when possible.
- L30 _public enumerator_ `VertexAttributeWeight = (1 << 2)` — Reads or writes the vertex attributes of the internal mesh.
- L33 _public enumerator_ `VertexUVs = (1 << 3)` — Reads or writes to the vertex uv sets.

#### struct `UE::MeshPartition::FDynamicSubmesh`  
`struct FDynamicSubmesh`  
_L44-92_
- desc: Subclass of FDynamicSubmesh3 which allows remapping of the base mesh pointer. This is a very dangerous operation which is only possible because of the invariants established through the MegaMesh system. Remapping only occurs when caching is deemed possible, which is guaranteed to produce an identical base FDynamicMesh3. Thus, all the mappings are consistent.
- L47 _public prototype_ `FDynamicSubmesh(const FMeshData& InSourceMesh, const TArray<int>& InTriangles, TSet<Geometry::FIndex2i>&& InEdgesOnSubmeshBoundary);`
- L49 _public function_ `FDynamicSubmesh()`
- L50 _public prototype_ `FDynamicSubmesh(const FDynamicSubmesh& InOther) = default;`
- L51 _public prototype_ `FDynamicSubmesh(FDynamicSubmesh&& InOther) = default;`
- L52 _public prototype_ `FDynamicSubmesh& operator=(const FDynamicSubmesh& InOther) = default;`
- L53 _public prototype_ `FDynamicSubmesh& operator=(FDynamicSubmesh&& InOther) = default;`
- L55 _public function_ `const Geometry::FDynamicMesh3& GetSubmesh() const`
- L56 _public function_ `Geometry::FDynamicMesh3& GetSubmesh()`
- L58 _public function_ `int MapVertexToSubmesh(int VertexID) const`
- L60 _public prototype_ `bool VertexExistsInBaseMesh(int VertexID) const;`
- L61 _public function_ `int MapVertexToBaseMesh(int VertexID) const`
- L63 _public prototype_ `void RemapToParentMesh(const FMeshData& InNewSourceMesh);`
- L65 _public prototype_ `bool GetSubmeshInternalBoundaryEdges(TSet<int>& OutSubmeshInternalBoundaryEdges) const;`
- L67 _public function_ `SIZE_T GetByteCount() const`
- L75 _public member_ `const FMeshData* SourceMesh = nullptr;`
- L77 _public prototype_ `TMap<FName, Geometry::FDynamicMeshWeightAttribute*> GetSubmeshWeightLayers();`
- L79 _public member_ `Geometry::FDynamicMesh3 Mesh;`
- L82 _public member_ `Geometry::FIndexMapi VertexMap;` — Maps vertices to/from the source mesh from/to vertices in the submesh
- L85 _public member_ `TMap<int, int> TriangleMap;` — Maps source mesh triangles to submesh triangles
- L91 _public member_ `TSet<Geometry::FIndex2i> EdgesOnSubmeshBoundary;` — Remember the edges which used to be the boundary edges of the submesh. (VertexIDs are in the source mesh) These are the edges which are shared with the source mesh and may cause cracks if they are modified.

#### class `UE::MeshPartition::FMeshView`  
`class FMeshView`  
_L99-228_
- desc: A constrained view of an FDynamicMesh3 which is provided to MegaMeshModifierComponents when they apply modifications. The view is constructed to only provide data within a specified bounding region to ensure modifiers only modify the base mesh within their bounds.
- L102 _public prototype_ `FMeshView() = default;`
- L105 _public prototype_ `FMeshView(FMeshData* InMesh, FBox InBounds, EMeshViewComponents InReadComponents, EMeshViewComponents InWriteComponents, const TArray<FName>& InUsedChannels);` — @param InBounds The bounds over which we colllect the view data. Expected to be in the local space of the input mesh.
- L106 _public prototype_ `FMeshView(const FMeshView&) = default;`
- L107 _public prototype_ `FMeshView& operator=(const FMeshView&) = default;`
- L109 _public prototype_ `bool Compare(const FMeshView& InOther);`
- L112 _public prototype_ `FVector3d GetVertexPos(int InVertexIndex) const;` — Returns the vertex position of the base mesh for a given vertex index.
- L115 _public prototype_ `float GetVertexAttributeWeight(FName InChannelName, int InVertexIndex) const;` — Returns the weight of the vertex attribute for the requested channel.
- L117 _public prototype_ `FVector2f GetVertexUV(int InVertexIndex, int InUVChannelIndex) const;`
- L120 _public prototype_ `void SetVertexPos(int InVertexIndex, FVector3d InNewVertexPos);` — Sets the vertex position in the base mesh for a given vertex index.
- L123 _public prototype_ `void SetVertexAttributeWeight(FName InChannelName, int InVertexIndex, float InNewVertexWeight);` — Sets the weight of the vertex attribute for the requested channel.
- L125 _public prototype_ `void SetVertexUV(int InVertexIndex, FVector2f InNewVertexUV, int InUVChannelIndex);`
- L127 _public function_ `int VertexCount() const`
- L137 _public function_ `const Geometry::FDynamicMesh3& GetSubmesh() const` — Get an immutable reference to the submesh provided by the view. This is only a valid operation if the view requested read access to a DynamicSubmesh.
- L147 _public function_ `Geometry::FDynamicMesh3& GetSubmeshMutable()` — Get a mutable reference to the submesh provided by the view. This is only a valid operation if the view requested write access to a DynamicSubmesh.
- L153 _public function_ `int GetSubmeshVID(int InVertexIndex) const`
- L166 _public prototype_ `bool GetSubmeshInternalBoundaryEdges(TSet<int32>& OutSubmeshEIDs) const;` — Gets the edges in the submesh that have a neighboring triangle in the base mesh. If an edge in this set were to be split, it would create a crack when merging the submesh back, because the new vertex will not be in the base mesh version of the edge. @return True if successul (we found all edge correspondences we expected)
- L171 _public prototype_ `double GetMemoryUsageMB() const;` — Returns the current memory usage of this mesh view in megabytes.
- L178 _private prototype_ `void Build();` — Builds the mesh view of a dynamic mesh, collecting all the attributes from the ReadComponents that are within the set bounds of the view.
- L184 _private prototype_ `void RemapParentMesh(FMeshData* InNewMeshInternal);` — Remaps all internal data structures which reference a specific base DynamicMesh to point to the new dynamic mesh. This is used to retarged the mesh view output data so it can be applied to a new base mesh.
- L189 _private prototype_ `void Writeback();` — Applies any writes made to the view by a modifier back to the internal mesh.
- L194 _private prototype_ `void Release();` — Release any memory held by this mesh view.
- L197 _private member_ `FMeshData* MeshInternal;`
- L198 _private member_ `FBox Bounds;`
- L200 _private member_ `EMeshViewComponents ReadComponents;`
- L201 _private member_ `EMeshViewComponents WriteComponents;`
- L202 _private member_ `TArray<FName> UsedChannels;`
- L210 _private member_ `MeshPartition::FDynamicSubmesh Submesh;` — Submesh over the view region. Only exists if read/write components require a DynamicSubmesh.
- L213 _private member_ `TArray<int> VertexIDs;` — View of vertex ids of the source mesh which overlap the view bounds
- L216 _private member_ `TArray<FVector3d> VertexPositions;` — Cache vertex positions for deferred writeback
- L217 _private member_ `TArray<TArray<FVector2f>> VertexUVs;`
- L220 _private member_ `TArray<int> TriangleIDs;` — View of triangle ids of the source mesh which overlap the view bounds
- L224 _private member_ `TArray<int> TriangleIDsTouchingBounds;` — Retains the set of triangles which have only some of its vertices inside the bounds This is the set of triangles which needs to be checked when looking to weld vertices
- L227 _private member_ `TMap<FName, TArray<float>> AttributeWeightChannels;` — Cached vertex attribute weights for deferred writeback.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MeshPartition` (scope `UE`)
- L36 _prototype_ `ENUM_CLASS_FLAGS(EMeshViewComponents);` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionModifierActor.h` (Public)


#### class `UE::MeshPartition::AModifierActor`  
`class AModifierActor : public AActor`  
_L23-36_
- reflection: `UCLASS(MinimalAPI, HideCategories=(HLOD, Physics, Cooking, Activation, Replication, Collision, Networking, Input, Actor, Visualize, WorldPartition, LOD, AssetUserData, Navigation, LevelInstance, DataLayers, Tags))`
- inherits: `AActor`
- L28 _public prototype_ `AModifierActor();`
- L31 _public member_ `TObjectPtr<MeshPartition::UModifierComponent> Modifier;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Mesh Partition")`
- L35 _protected member_ `TObjectPtr<USceneComponent> DefaultSceneRoot;` — `UPROPERTY(VisibleAnywhere, Category="Actor")`

#### class `UE::MeshPartition::UModifierActorFactory`  
`class UModifierActorFactory : public UActorFactory`  
_L39-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorFactory`
- L44 _private prototype_ `virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams) override;`
- L45 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L46 _private prototype_ `virtual FString GetDefaultActorLabel(UObject* Asset) const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionModifierComponent.h` (Public)


#### struct `UE::MeshPartition::FPriorityLayerName`  
`struct FPriorityLayerName : public FNameWrapper`  
_L47-54_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FNameWrapper`
- desc: Version of FNameWrapper to use for priority layer names. Gets used with a detail customization that uses GetOptions metadata function to constrain options when a toggle is engaged.
- L51 _public prototype_ `FPriorityLayerName() = default;`
- L52 _public function_ `FPriorityLayerName(const FName& NameIn) : FNameWrapper(NameIn)`

#### class `UE::MeshPartition::IModifierBackgroundOp`  
`class IModifierBackgroundOp`  
_L60-122_
- desc: An object created by a modifier to apply its modifications on background worker threads. Any data that the object uses must be thread-safe to access.
- L63 _public typedef_ `using FInstanceInfo = UE::MeshPartition::FInstanceInfo;`
- L65 _public prototype_ `IModifierBackgroundOp(const FName& InOperationName);`
- L67 _public function_ `virtual ~IModifierBackgroundOp()`
- L73 _public prototype_ `virtual void GetInstancesInBounds(const FBox& InBounds, TArray<FInstanceInfo>& OutInstanceInfos) const = 0;` — Given some bounds, give back the relevant instances of the modifier. For many modifiers there is just one instance, but some may have multiple instances in the world that share most settings but differ in location/bounds/etc.
- L80 _public prototype_ `virtual void ApplyModifications(MeshPartition::FMeshView& InMeshView, const FTransform3d& InTransform, const FInstanceInfo& InInstanceInfo) const = 0;` — Modify the provided MeshView for the given instance. @param InMeshView The view to the mega mesh that this component is allowed to modify. Modifiers can only affect the mesh within their defined bounds. The view enforces this constraint. @param InTransform The World Transform of the modified mesh.
- L82 _public function_ `UE::Tasks::FTask GetAsyncPrepareTask() const`
- L84 _public function_ `FName GetOperationName() const`
- L89 _public prototype_ `virtual bool DisableDDCWrite() const = 0;` — Flag which controls whether builds including this modifier are allowed to be cached in DDC.
- L94 _public function_ `virtual TSharedPtr<const FDynamicMesh3> GetMesh() const`
- L98 _public function_ `virtual FTransform GetMeshTransform() const`
- L102 _protected function_ `static bool AddDefaultInstanceIfIntersects(const FBox& ModifierBounds, const FBox& QueryBounds, TArray<FInstanceInfo>& InstanceInfosOut)` — Helper that adds a single instance with ID 0 that edits vertex positions if the given bounds intersect the query bounds.
- L120 _protected member_ `const FName OperationName;`
- L121 _protected member_ `UE::Tasks::FTask AsyncPrepareTask;`

#### class `UE::MeshPartition::FPassthroughBackgroundOp`  
`class FPassthroughBackgroundOp : public MeshPartition::IModifierBackgroundOp`  
_L125-142_
- inherits: `MeshPartition::IModifierBackgroundOp`
- desc: An operation doing nothing. Can be returned by modifier wanting to be skipped depending on the execution context.
- L128 _public function_ `FPassthroughBackgroundOp(const FName& InOperationName) : MeshPartition::IModifierBackgroundOp(InOperationName)`
- L130 _public function_ `virtual void GetInstancesInBounds(const FBox& InBounds, TArray<FInstanceInfo>& OutInstanceInfos) const override`
- L135 _public function_ `virtual void ApplyModifications(MeshPartition::FMeshView& InMeshView, const FTransform3d& InTransform, const FInstanceInfo& InInstanceDesc) const override`
- L139 _public function_ `virtual bool DisableDDCWrite() const override`
- L141 _public member_ `FBox GlobalBounds;`

#### class `UE::MeshPartition::IBaseMeshProviderOp`  
`class IBaseMeshProviderOp : public MeshPartition::IModifierBackgroundOp`  
_L148-166_
- inherits: `MeshPartition::IModifierBackgroundOp`
- desc: An object created by base sections to provide the base mesh when requested on background worker threads. This is done through a function in case we someday want procedurally generated base sections.
- L151 _public function_ `IBaseMeshProviderOp(const FName& InOperationName) : MeshPartition::IModifierBackgroundOp(InOperationName)`
- L153 _public function_ `virtual void GetInstancesInBounds(const FBox& InBounds, TArray<FInstanceInfo>& OutInstanceInfos) const`
- L160 _public function_ `virtual void ApplyModifications(MeshPartition::FMeshView& InMeshView, const FTransform3d& InTransform, const FInstanceInfo& InInstanceInfo) const` — Modify the provided MeshView for the given instance. @param InMeshView The view to the mega mesh that this component is allowed to modify. Modifiers can only affect the mesh within their defined bounds. The view enforces this constraint. @param InTransform The World Transform of the modified mesh.
- L165 _public function_ `virtual bool DisableDDCWrite() const` — Flag which controls whether builds including this modifier are allowed to be cached in DDC.

#### class `UE::MeshPartition::UModifierComponent`  
`class UModifierComponent : public UPrimitiveComponent, public MeshPartition::IModifierBlueprintInterface`  
_L219-735_
- reflection: `UCLASS(MinimalAPI, Abstract, HideCategories = (HLOD, RayTracing, TextureStreaming, Physics, Collision, Lighting, Rendering, Mobile, Navigation, Activation, Cooking, LOD, AssetUserData), meta = (MegaMeshClassVersion = "0"))`
- inherits: `UPrimitiveComponent,MeshPartition::IModifierBlueprintInterface`
- desc: This is the base class for components modifying the MegaMesh. This is an EditorOnly Component. Their bounds represent the area they are affecting. They provide (overridable) interface to interact with the MegaMesh: * Logic to attach/detach to the AMeshPartition (to move/update the MegaMesh as a whole) * Invalidate bounds when updated (trigger a new compilation process for an area) * Perform modification as a step (by modifying a FDynamicMesh) (could evolve into adding/modifying a displacement render target in the future). The MegaMeshClassVersion meta data should be set to a positive number if you provide a deterministic cache behavior via GatherDependencies() (non-positive ModifierVersions will instead use random cache keys that are updated on change, and are less reliable in general) Whenever the implementation of the class is changed (such that it would generate a different result in Apply), the MegaMeshClassVersion should be bumped.
- L225 _public prototype_ `UModifierComponent();`
- L228 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject Implementation
- L229 _public function_ `virtual bool IsEditorOnly() const override`
- L230 _public prototype_ `virtual void PreEditChange(FProperty* InPropertyAboutToChange) override;`
- L232 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L233 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L234 _public prototype_ `virtual void PreEditUndo() override;`
- L235 _public prototype_ `virtual void PostEditUndo() override;`
- L239 _public prototype_ `virtual void OnRegister() override;` — UActorComponent Implementation
- L240 _public prototype_ `virtual void OnUnregister() override;`
- L241 _public prototype_ `virtual void OnComponentDestroyed(bool bInDestroyingHierarchy) override;`
- L242 _public prototype_ `virtual TUniquePtr<FWorldPartitionComponentDesc> CreateClassComponentDesc() const;`
- L243 _public prototype_ `virtual FBox GetStreamingBoundsEditor() const override;`
- L244 _public prototype_ `virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData() const override;`
- L246 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;` — We need this for the SceneProxy to function properly.
- L250 _public prototype_ `virtual void PostEditComponentMove(bool bFinished) override;` — USceneComponent Implementation
- L251 _public prototype_ `virtual void OnUpdateTransform(EUpdateTransformFlags InUpdateTransformFlags, ETeleportType InTeleport) override;`
- L256 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L263 _public function_ `virtual void InitializeModifier()` — Called after a modifier have been loaded and registered to the MegaMesh in case it needs initialization.
- L268 _public function_ `virtual void UninitializeModifier()` — Called before a modifier will be unloaded and unregistered in case it need resource cleaning.
- L271 _public prototype_ `void PrepareResources();` — Ensures any async resources required by this modifier are prepared.
- L273 _public function_ `virtual UE::Tasks::FTask GetAsyncPrepareResourcesTask() const`
- L279 _public prototype_ `virtual void MarkAsRegisteredWithMeshPartition(const AMeshPartition* InMeshPartition);` — Called by UMeshPartitionEditorComponent when gathering all of its modifiers to let the modifier know that it has been registered, so that it doesn't try to call OnModifierAssigned unnecessarily.
- L284 _public prototype_ `AMeshPartition* GetAffectedMeshPartition() const;` — @return The MeshPartition currently affected by this modifier.
- L290 _public prototype_ `UMeshPartitionEditorComponent* GetMeshPartitionEditorComponent() const;` — A helper to retrieve the parent AMeshPartition's UMeshPartitionEditorComponent. @return the UMeshPartitionEditorComponent used by the parent AMeshPartition.
- L296 _public prototype_ `void SetAffectedMeshPartition(AMeshPartition* InMeshPartition);` — Sets the MeshPartition to be affected by this modifier. @param InMeshPartition to be affected by this modifier.
- L304 _public prototype_ `void BP_SetAffectedMegaMesh(AMeshPartition* InMeshPartition) override;` — `UFUNCTION(BlueprintCallable, Category = "Mesh Partition Modifier", meta = (DisplayName = "Set Affected Mesh Partition"))` — Sets the MeshPartition to be affected by this modifier. @param InMeshParitition to be affected by this modifier.
- L310 _public prototype_ `AActor* BindToNearestMeshPartition();` — Binds the modifier to the nearest MeshPartition in the world @return Nearest attached actor of the bound mesh partition. Otherwise, nullptr if no valid mesh partition was found.
- L317 _public prototype_ `AActor* BP_BindToNearestMeshPartition();` — `UFUNCTION(BlueprintCallable, Category = "Mesh Partition Modifier", meta=(DisplayName="Bind To Nearest Mesh Partition"))` — Binds the modifier to the nearest MeshPartition. @return Nearest attached actor of the bound mesh partition. Otherwise, nullptr if no valid mesh partition was found.
- L322 _public function_ `MeshPartition::APreviewSection* GetPreviewSection() const` — @return If this component is a Base Modifier. Will return the preview section using this modifier as a base.
- L328 _public prototype_ `virtual void SetPreviewSection(MeshPartition::APreviewSection* InPreviewSection);` — Sets the internal preview section. Meaning this base modifier is used to build the preview section. @param InPreviewSection The preview section to set.
- L333 _public function_ `bool IsFree() const` — @return True if this base modifier isn't used by any preview section.
- L338 _public function_ `const MeshPartition::FBaseGrowth& GetBaseGrowth() const` — @return The BaseGrowth structure, representing how a given modifier should grow the base bounds.
- L344 _public prototype_ `void SetBaseGrowth(const FBaseGrowth& InBaseGrowth);` — Sets the BaseGrowth structure, representing how a given modifier should grow the base bounds. @param InBaseGrowth FBaseGrowth structure to set.
- L349 _public function_ `const FName& GetType() const` — @return The type of this modifier. Used by the processing stack.
- L354 _public function_ `double GetPriority() const` — @return The sub priority used for Modifiers belonging to the same type.
- L355 _public function_ `void SetPriority(const double InPriority)`
- L360 _public function_ `const FGuid& GetCacheKey() const` — @return The key used to determine the state of cached preview builds which depend on instances of this modifier.
- L366 _public function_ `void SetType(const FName& InType)` — Sets the type of this modifier. @param InType The type of this modifier to set.
- L372 _public function_ `void SetIgnoreChanged(const bool bInIgnoreChanged)` — Allows to modulate OnChanged behavior. @param bInIgnoreChanged If true, OnChanged will not forward the callback to UMeshPartitionEditorComponent.
- L378 _public function_ `virtual FBox ComputeCombinedBounds() const` — This function returns single bounding box representing the total area this modifier may affect. This is used for things like world partition streaming bounds which cannot be made more granular than a singular bounds.
- L386 _public function_ `virtual TArray<FBox> ComputeBounds() const` — Computes the set of bounding boxes describing the regions this modifier is affecting. Modifiers overriding this function should try to be granular to avoid rebuilding more meshes than are required.
- L391 _public prototype_ `void UpdateLastAppliedBounds();` — Last applied bounds is updated when the modifier is applied to the mesh so changes to those bounds can be tracked and updates can be triggered.
- L396 _public prototype_ `bool IntersectsAnyBounds(TConstArrayView<FBox> InBoundsToTest) const;` — @return True if any of the input bounds intersects this modifiers bounds
- L401 _public function_ `virtual bool IsContiguous() const` — @return True if this modifier shouldn't be splitted across multiple sections.
- L409 _public prototype_ `static FName BuildPropertyKey(const FString& InModifierIndex, const FName& InKey);` — Builds a PropertyKey to be used in ActorDesc properties. @param InModifierIndex The index of this modifier in the actor descriptor's list of modifiers. @param InKey The key of the property. @return A FName ready to be used in ActorDesc properties.
- L416 _public prototype_ `virtual void OnChanged(TConstArrayView<const FBox> InBoundingBoxes, EChangeType InChangeType);` — Called when the modifier changed and needs to be processed again. Will forward the call to the appropriate UMeshPartitionEditorComponent. @param InBoundingBox The invalidated BoundingBox. Should encompass the whole actor. @param bInChangeNondeterministicCacheKeys True will change the cache key (for modifiers with non-deterministic cache keys), invalidating any cached megamesh sections produced by the modifier.
- L422 _public function_ `virtual void PropertyChanged(FPropertyChangedEvent& InPropertyChangedEvent)` — Called after a class member property changes. Equivalent to PostEditChangeProperty, only separated out to allow the base class to handle housekeeping tasks related to Megamesh updates. @param InPropertyChangedEvent The property event indicating what has been changed
- L429 _public function_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const` — Called to prepare for applying the modifier. The produced background operation will be called to apply the modifications on a worker thread. Ignored if it returns nullptr. @param InBuildType The context for which this operation is generated for.
- L432 _public function_ `template <typename T, typename... InArgs> TSharedPtr<T> AllocateBackgroundOp(const FName& InOpName, InArgs&&... Args) const`
- L442 _public function_ `virtual bool CanRender() const` — @return True if this modifier is contributing to the MegaMesh's texture.
- L451 _public function_ `virtual void PostBuildSectionMesh(AActor* InSection, const MeshPartition::FMeshData& InBuiltMesh)` — Called after a MeshPartition::APreviewSection or MeshPartition::ACompiledSection FMeshData has been built in case the modifier needs to perform additional processing. @param InSection The built section on which to perform additional processing. @param InBuiltMesh The result of the build operation.
- L459 _public function_ `virtual void PostProcessSection(AActor* InSection)` — Called after a MeshPartition::APreviewSection or MeshPartition::ACompiledSection has been built and their associated mesh finalized in case the modifier needs to perform additional processing. @param InSection The built section on which to perform additional processing.
- L466 _public function_ `virtual double GetComplexity() const` — Gets the added complexity when applying this modifier. For example, a mesh adding its vertices should return the vertex number. @return The complexity this modifier adds.
- L473 _public function_ `virtual float GetComplexityMultiplier() const` — Gets the complexity multiplier when applying this modifier. For example, a modifier re-meshing a base by doubling the amount of detail should return 2. @return The complexity multiplier.
- L479 _public function_ `virtual bool IsBase() const` — Allows to determine if this modifier will be used as a base. @return True if this modifier will be the first to be processed on the stack.
- L485 _public function_ `virtual void OnMegaMeshDefinitionChanged(const UMeshPartitionDefinition* InDefinition)` — Called when the parent AMeshPartition's UMeshPartitionDefinition changed. @param InDefinition The new UMeshPartitionDefinition.
- L492 _public function_ `virtual void OnMegaMeshDefinitionModified(const UMeshPartitionDefinition* InDefinition, const FName& InPropertyName)` — Called when a property from the parent AMeshPartition's UMeshPartitionDefinition changed. @param InDefinition The currently used UMeshPartitionDefinition. @param InPropertyName The property that changed.
- L498 _public function_ `virtual void SetIsTemporarilyHiddenInEditor(const bool bInIsHidden)` — Called to show/hide components. Should be responsible of propagating the hidden state to owned/attached components. @param bInIsHidden True if the current component should be hidden.
- L500 _public function_ `static bool IsAffectedMeshPartitionPropertyName(const FName& InName)`
- L507 _public function_ `virtual void DrawVisualization(const FSceneView* View, FPrimitiveDrawInterface* PDI) const` — Called by the visualizer to give the modifier an oppertunity to render a debug visualization of itself when selected. @param View the current SceneView @param PDI a pointer to the drawing interface for the viewport
- L514 _public prototype_ `TArray<FName> GetMegaMeshDefinitionChannels() const;` — `UFUNCTION(CallInEditor)` — Function collecting the current list of channels declared in the MegaMesh Definition This is used by the ui of any Modifier presenting a channel option.
- L520 _public prototype_ `TArray<FName> GetDefinitionPriorityLayers() const;` — `UFUNCTION()` — Function collecting the current list of priority layers declared in the Mesh Partition Definition.
- L527 _public prototype_ `void SetPriorityLayer(const FName PriorityLayer);` — `UFUNCTION()` — Function setting the priority layer for this modifier from the declared priority layers in the Mesh Partition Definition.
- L534 _public prototype_ `FName GetPriorityLayer() const;` — `UFUNCTION()` — Function getting the priority layer for this modifier from the declared priority layers in the Mesh Partition Definition.
- L539 _public prototype_ `virtual FColor EditorUnselectedModifierColor() const;` — Get the color of the modifier in it's unselected state for scene proxy drawing.
- L544 _public prototype_ `void SetDrawBounds(bool bEnabled);` — Called by the SceneProxy to determine if the component should be visualized at the current moment.
- L545 _public prototype_ `virtual bool ShouldDrawBoundingBox() const;`
- L554 _public prototype_ `FGuid UpdateCacheKey(bool bInChangeCacheKey = false);` — Updates the stored cache key. Deterministic cache keys are always recomputed (by calling GatherDependencies). Non-determinstic cache keys are only changed when bInChangeCacheKey is true. UpdateCacheKey(true) is called when changes are made to the properties. (NOTE: We use positive MegaMeshClassVersion numbers to indicate deterministic cache keys.)
- L563 _public prototype_ `int32 GetMegaMeshClassVersion() const;` — Get the MegaMeshClassVersion of this modifier. Final, because this is just a helper function that calls GetMegaMeshClassVersionFromClass. It MUST return the same value as GetMegaMeshClassVersionFromClass(). (NOTE: We use positive MegaMeshClassVersion numbers to indicate we should use deterministic cache keys calculated from the dependencies gathered via GatherDependencies())
- L565 _public function_ `virtual FGuid GetCodeVersionKey() const`
- L572 _public function_ `virtual bool IsTemporarilyDisabledInEditor() const` — Returns true if the modifier is temporarily disabled from being processed in any MegaMesh builds. Note: Builds containing temporarily disabled modifiers do not get written to DDC, as this state is expected to be reset on next map load. Also does not affect compiled section builds
- L577 _public function_ `bool GetIsDisabledFlag() const` — @return The raw value of the serialized bIsDisabled flag.
- L582 _public prototype_ `void SetIsDisabledFlag(const bool bInIsDisabled);` — @param bInIsDisabled Sets disabled flag for the modifier.
- L587 _public function_ `bool IsDisabled() const` — @return True if the modifier should be processed.
- L592 _public function_ `void SetIsInteractive(const bool bInIsInteractive)` — Marks this modifier as currently interactive. @param bInIsInteractive Set to true if this modifier is currently interactive.
- L595 _public function_ `bool IsInteractive() const` — @return True if this modifier is currently interactive
- L598 _public function_ `virtual TArray<UModifierComponent*> GetInteractiveProxies()` — @return An array of modifiers to use when building meshes for interactive mode.
- L608 _protected prototype_ `FBox GetOwnerBounds(const bool bShouldBeRegistered) const;` — Gets the bound of the actor owning this component. @param bShouldBeRegistered True if the method should also take into account unregistered components. @return The bounding box of the owner.
- L641 _protected prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const;` — Gather Dependencies for this modifier, including asset and class dependencies and other relevant data (for example local settings) that affect the modifier apply behavior. The dependencies are used to detect changes to the modifier that would require rebuilding sections that use this modifier. Both incremental build of compiled sections, as well as the in-editor build of preview sections track the declared dependencies. PackageHash incremental build is a method to detect changes by that does not require loading the Modifiers into memory, so is much faster than a ModifierHash check, and is usually the best method to use for incremental iterative local builds on large worlds. PackageHash requires that all relevant assets and classes that affect the application of this modifier (in the current state) are declared in GatherDependencies(), so it can track whether the packages have changed on disk, or class implementations have changed. You do not need to declare the modifier itself, it's parent actor, or the modifier's class as dependencies in GatherDependencies(). Those are automatically pulled in by the system.  Any additional assets or classes used should be declared (especially assets stored in different packages). Note that the class implementations are tracked by their MegaMeshClassVersion metadata, so any class that is modified in a way that affects modifier application behavior needs to change it's MegaMeshClassVersion metadata. If a derived modifier class does NOT overrid
- L647 _protected prototype_ `UMeshPartitionDefinition* GetMegaMeshDefinition() const;` — A helper to retrieve the parent AMeshPartition's UMeshPartitionDefinition. @return the UMeshPartitionDefinition used by the parent AMeshPartition.
- L656 _protected function_ `virtual bool ShouldShowSpriteComponent() const` — Determines whether the editor-only sprite billboard is shown Note: currently this only gets queried on component creation, so dynamic visibility control will require the subclass to update the visibility itself.
- L661 _private prototype_ `void RegisterWithMegaMeshIfNeeded();` — If bNeedToRegisterWithMegaMesh is true and we have a MegaMesh, notifies it of our existence and sets bNeedToRegisterWithMegaMesh to false.
- L664 _private prototype_ `bool IsInRelevantWorld() const;` — Used to filter out modifiers that are a template in the BP editor, or are in the BP preview viewport
- L667 _private prototype_ `void CreateModifierSpriteComponent();`
- L671 _private member_ `TWeakObjectPtr<MeshPartition::APreviewSection> PreviewSection;` — `UPROPERTY(Transient)`
- L678 _private member_ `TSoftObjectPtr<AMeshPartition> AffectedMegaMesh;` — `UPROPERTY(EditInstanceOnly, Category = "Modifier", Meta = (DisplayName = "Affected Mesh Partition"))` — MegaMesh affected by the modifier. Its associated definition controls the ordering of priority layers, and channels available in the final result.
- L681 _private member_ `MeshPartition::FBaseGrowth BaseGrowth;` — `UPROPERTY(EditAnywhere, Category = "Modifier", AdvancedDisplay)`
- L687 _private member_ `FPriorityLayerName Type;` — `UPROPERTY(EditAnywhere, Category = "Modifier", Meta = (DisplayName = "Priority Layer", GetOptions = "GetDefinitionPriorityLayers"))` — Modifiers are grouped into priority layers whose relative application order is controlled by the mesh partition definition.
- L693 _private member_ `double Priority = 0.;` — `UPROPERTY(EditAnywhere, Category = "Modifier", Meta = (DisplayName = "Sub-Priority"))` — The sub priority orders modifiers within the same priority layer (higher is applied later).
- L696 _private member_ `FGuid CacheKey;` — `UPROPERTY(VisibleAnywhere, Category = "Modifier|Advanced", AdvancedDisplay, DuplicateTransient, TextExportTransient)`
- L700 _private member_ `bool bDrawBounds;` — `UPROPERTY(Transient)` — Transient Visualization Settings
- L704 _private member_ `bool bIsDisabled = false;` — `UPROPERTY(EditInstanceOnly, Category = "Modifier|ModifierSettings", Meta = (DisplayName = "Disabled"))` — Disable processing this modifier completely.
- L712 _private member_ `bool bIsTemporarilyDisabledInEditor = false;` — `UPROPERTY(EditInstanceOnly, Category = "Modifier|ModifierSettings", SkipSerialization, Transient, DuplicateTransient, TextExportTransient, Meta = (DisplayName = "Disabled only in Editor", EditCondition = "!bIsDisabled"))` — Temporarily disable processing this modifier in any Mesh Partition builds (Preview/PCG Query/Modifier tool targets). Note: Builds containing temporarily disabled modifiers do not get written to DDC, as this state is expected to be reset on next map load. Also does not affect compiled section builds.
- L715 _private member_ `TArray<FBox> LastAppliedBounds;` — The last bounds of the modifier that were integrated into the built mesh
- L720 _private member_ `TArray<FBox> LastSubmittedBounds;` — The last bounds of the modifier that were submitted for evaluation, which may or may not have been applied yet. Used for invalidating in-flight section builds.
- L723 _private member_ `AMeshPartition* PreUndoMeshPartition = nullptr;` — Used to detect changes to our assigned megamesh across undo
- L727 _private member_ `bool bNeedToRegisterWithMeshPartition = true;` — Transient property that starts out true to make it easy to make sure that the MegaMesh knows of our existence (particularly when copying modifiers).
- L729 _private member_ `bool bIgnoreChanged = false;`
- L730 _private member_ `bool bIsInteractive = false;`

#### struct `UE::MeshPartition::FModifierComponentInstanceData`  
`struct FModifierComponentInstanceData : public FPrimitiveComponentInstanceData`  
_L739-765_
- reflection: `USTRUCT()`
- inherits: `FPrimitiveComponentInstanceData`
- desc: Used to store un-serialized modifier component data during RerunConstructionScripts
- L743 _public function_ `FModifierComponentInstanceData() : bIsTemporarilyDisabledInEditor(false)`
- L746 _public function_ `explicit FModifierComponentInstanceData(const MeshPartition::UModifierComponent* SourceComponent) : Super(SourceComponent) , bIsTemporarilyDisabledInEditor(SourceComponent && SourceComponent->bIsTemporarilyDisabledInEditor)`
- L750 _public prototype_ `virtual ~FModifierComponentInstanceData() = default;`
- L752 _public function_ `virtual bool ContainsData() const override`
- L757 _public function_ `virtual void ApplyToComponent(UActorComponent* Component, const ECacheApplyPhase CacheApplyPhase) override`
- L764 _public member_ `bool bIsTemporarilyDisabledInEditor = false;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<UE::MeshPartition::FPriorityLayerName> : public TStructOpsTypeTraitsBase2<UE::MeshPartition::FPriorityLayerName>`  
_L770-776_
- inherits: `TStructOpsTypeTraitsBase2<UE::MeshPartition::FPriorityLayerName>`
- desc: Needed to get SerializeFromMismatchedTag to be called to convert from serialized FName properties

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L773-775_

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L22 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace MeshPartition` (scope `UE`)
- L35 _namespace_ `namespace MegaMeshModifierComponentLocals` (scope `UE::MeshPartition`)
- L38 _prototype_ `void SetSpriteSize(float Size);` (scope `UE::MeshPartition::MegaMeshModifierComponentLocals`) — for friending
- L39 _prototype_ `void SetSpritePath(const FString& Path);` (scope `UE::MeshPartition::MegaMeshModifierComponentLocals`)
- L172 _namespace_ `namespace MegaMeshModifierProperties`
- L174 _externvar_ `extern const FName PropertiesVersionNumberName;` (scope `MegaMeshModifierProperties`)
- L175 _externvar_ `extern const FName MegaMeshModifiersNum;` (scope `MegaMeshModifierProperties`)
- L176 _externvar_ `extern const FName MegaMeshModifierPath;` (scope `MegaMeshModifierProperties`)
- L177 _externvar_ `extern const FName MegaMeshGUID;` (scope `MegaMeshModifierProperties`)
- L178 _externvar_ `extern const FName Class;` (scope `MegaMeshModifierProperties`)
- L179 _externvar_ `extern const FName BaseGrowth;` (scope `MegaMeshModifierProperties`)
- L180 _externvar_ `extern const FName Type;` (scope `MegaMeshModifierProperties`)
- L181 _externvar_ `extern const FName Priority;` (scope `MegaMeshModifierProperties`)
- L182 _externvar_ `extern const FName Complexity;` (scope `MegaMeshModifierProperties`)
- L183 _externvar_ `extern const FName ComplexityMultiplier;` (scope `MegaMeshModifierProperties`)
- L184 _externvar_ `extern const FName IsContiguous;` (scope `MegaMeshModifierProperties`)
- L185 _externvar_ `extern const FName IsDisabled;` (scope `MegaMeshModifierProperties`)
- L187 _externvar_ `extern const uint32 PropertiesVersionNumber;` (scope `MegaMeshModifierProperties`)
- L192 _namespace_ `namespace UE`
- L192 _namespace_ `namespace MeshPartition` (scope `UE`)
- L198 _namespace_ `namespace MegaMeshModifierType` (scope `UE::MeshPartition`)
- L203 _externvar_ `extern const FName Base;` (scope `UE::MeshPartition::MegaMeshModifierType`) — The base type represent all meshes forming the first layer to be processed.
- L774 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon5d01b0a40103`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionModifierComponentDesc.h` (Public)


#### class `UE::MeshPartition::FWorldPartitionModifierComponentDesc`  
`class FWorldPartitionModifierComponentDesc : public FWorldPartitionComponentDesc`  
_L11-58_
- inherits: `FWorldPartitionComponentDesc`
- L14 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L15 _public prototype_ `virtual void Init(const UActorComponent* InComponent) override;`
- L16 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L21 _public member_ `FTransform ComponentTransform;` — `UE_DEPRECATED(5.8, "ComponentTransform is no longer updated and is only present for backwards compatibity. Use ComponentToActorTransform instead")` — Component->World transform. Serialized in the descriptor so we can transform the LocalBounds back into worldspace after serializing.
- L27 _public member_ `FTransform ComponentToActorTransform;` — Component->Actor transform. Serialized in the descriptor so we can transform the LocalBounds back into worldspace after serializing after multiplying by the actor transform in the actor descriptor.
- L30 _public member_ `FSoftObjectPath ModifierPath;` — Path to the modifier component, used as a unique identifier for this modifier
- L33 _public member_ `FName Type;` — Type of the modifier, affects grouping and sort order
- L36 _public member_ `double Priority;` — Relative priority of this modifier, affects sort order
- L39 _public member_ `FGuid MegaMeshGuid;` — The world partition actor desc GUID for the parent mega mesh actor
- L42 _public member_ `FBox LocalBounds;` — Localspace bounds of the modifier. Must be serialized as local space bounds for delta serialization to work.
- L45 _public member_ `MeshPartition::FBaseGrowth BaseGrowth;` — Other values used to compute groups
- L46 _public member_ `double Complexity;`
- L47 _public member_ `float ComplexityMultiplier;`
- L48 _public member_ `bool bIsContiguous;`
- L49 _public member_ `bool bIsDisabled;`
- L50 _public member_ `bool bIsBase;`
- L57 _public member_ `bool bHasComponentToActorTransform;` — Indicates if this component has a ComponentToActor transform or not. This allows us to detect old modifiers which serialized the incorrect transform and still load them without breaking.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionModifierDescriptors.h` (Public)


#### enum `UE::MeshPartition::EBuildType`  
`enum class EBuildType : uint8`  
_L32-51_
- desc: Enum describing the type of usecase requesting a mesh build.
- L35 _public enumerator_ `Request = 0` — A manual build request external to the pipeline.
- L38 _public enumerator_ `PreviewSection = 1 << 0` — The result will be used to create a preview section.
- L41 _public enumerator_ `CompiledSection = 1 << 1` — The result will be used to create a compiled section.
- L44 _public enumerator_ `InteractiveBase = 1 << 2` — Request to build the frozen version of the modifiers stack. Used as a base to apply interactive modifiers onto.
- L47 _public enumerator_ `InteractiveModifier = 1 << 3` — Request to apply the interactive modifiers on top of an already existing base.
- L50 _public enumerator_ `SimplifiedPreviewSection = 1 << 4` — Request to build a simplified preview section.

#### struct `UE::MeshPartition::FBaseGrowth`  
`struct FBaseGrowth`  
_L57-80_
- reflection: `USTRUCT()`
- desc: Struct describing how a modifier should grow the base so other modifiers can be taken into account when creating groups.
- L61 _public prototype_ `const bool& operator[](const uint32 InIndex) const;`
- L62 _public prototype_ `FString ToString() const;`
- L63 _public prototype_ `bool InitFromString(const FString& InSourceString);`
- L71 _public member_ `bool X = false;` — `UPROPERTY(EditAnywhere, Category = "MeshPartition")`
- L74 _public member_ `bool Y = false;` — `UPROPERTY(EditAnywhere, Category = "MeshPartition")`
- L77 _public member_ `bool Z = true;` — `UPROPERTY(EditAnywhere, Category = "MeshPartition")`
- L79 _public prototype_ `bool operator==(const FBaseGrowth&) const = default;`

#### struct `UE::MeshPartition::FModifierDesc`  
`struct FModifierDesc`  
_L86-130_
- desc: Struct that can hold all of the ActorDesc properties for a mega mesh modifier (These are the properties that are available when the modifiers are not loaded into memory)
- L89 _public member_ `FSoftObjectPath ModifierPath;` — Path to the modifier component, used as a unique identifier for this modifier
- L92 _public member_ `FSoftClassPath ClassPath;` — Path to the modifier class, used to identify the class to check code versions
- L95 _public member_ `FName Type;` — Type of the modifier, affects grouping and sort order
- L98 _public member_ `double Priority;` — Relative priority of this modifier, affects sort order
- L101 _public member_ `FGuid OwnerGuid;` — World partition actor desc GUID for the actor containing this modifier component
- L104 _public member_ `FGuid MegaMeshGuid;` — The world partition actor desc GUID for the parent mega mesh actor
- L107 _public member_ `FBox Bounds;` — Other values used to compute groups
- L108 _public member_ `MeshPartition::FBaseGrowth BaseGrowth;`
- L109 _public member_ `double Complexity;`
- L110 _public member_ `float ComplexityMultiplier;`
- L111 _public member_ `bool bIsContiguous;`
- L112 _public member_ `bool bIsDisabled;`
- L113 _public member_ `bool bIsBase;`
- L116 _public prototype_ `FModifierDesc();` — construct an empty / default descriptor
- L119 _public prototype_ `FModifierDesc(const MeshPartition::UModifierComponent& InModifier);` — construct from a modifier
- L123 _public prototype_ `FModifierDesc(const FWorldPartitionActorDescInstance& InActorDescInstance, int32 InModifierIndex);` — construct from InActorDescInstance (which can have multiple modifiers, this builds the one indicated by InModifierIndex) #todo: remove once all modifiers in older maps have been resaved.
- L124 _public prototype_ `FModifierDesc(const FWorldPartitionActorDescInstance& InActorDescInstance, const FWorldPartitionModifierComponentDesc& InComponentDesc);`
- L126 _public prototype_ `bool operator==(const FModifierDesc&) const = default;`
- L128 _public prototype_ `bool IsValid() const;`
- L129 _public function_ `bool IsBase() const`

#### struct `UE::MeshPartition::FModifierIndex`  
`struct FModifierIndex`  
_L133-144_
- desc: Typesafe wrapper for identifying and indexing modifier component data inside Modifier Groups
- L135 _public typedef_ `using IndexType = int32;`
- L137 _public function_ `FModifierIndex() : Index(INDEX_NONE)`
- L138 _public function_ `explicit FModifierIndex(IndexType InIndex) : Index(InIndex)`
- L140 _public member_ `IndexType Index;`
- L143 _public function_ `operator IndexType() const` — Implicit conversion operator to int to allow using this directly as an array index for convenience.

#### struct `UE::MeshPartition::FInstanceIndex`  
`struct FInstanceIndex`  
_L147-158_
- desc: Typesafe wrapper for identifying and indexing modifier instances inside Modifier Groups
- L149 _public typedef_ `using IndexType = int32;`
- L151 _public function_ `FInstanceIndex() : Index(INDEX_NONE)`
- L152 _public function_ `explicit FInstanceIndex(IndexType InIndex) : Index(InIndex)`
- L154 _public member_ `IndexType Index;`
- L157 _public function_ `operator IndexType() const` — Implicit conversion operator to int to allow using this directly as an array index for convenience.

#### struct `UE::MeshPartition::FInstanceInfo`  
`struct FInstanceInfo`  
_L169-178_
- desc: Per-Instance modifier data. Modifiers may declare 0 or more FInstanceInfos. Instances will be processed through the MegaMesh processing pipeline as individual entities whose dependencies are based on the instance's proper bounds rather than the encapsulating bounds of the owning modifier. How modifiers choose to interpret the different instances and what kind of per-instance data they wish to store is modifier-specific. The simplest case is usually a separate transform/bounds per-instance but can be as complex as separate mesh data or separate textures.
- L171 _public member_ `FBox Bounds;`
- L172 _public member_ `FModifierIndex ModifierIndex;`
- L173 _public member_ `int32 InstanceID;`
- L175 _public member_ `EMeshViewComponents ReadViewComponents;` — #todo: move out of per instance data?
- L176 _public member_ `EMeshViewComponents WriteViewComponents;` — #todo: move out of per instance data?
- L177 _public member_ `TArray<FName> UsedChannels;` — #todo: move out of per instance data?

#### struct `UE::MeshPartition::TIndexIterator`  
`template <typename IndexType> struct TIndexIterator`  
_L181-220_
- L183 _public function_ `inline bool operator==(const TIndexIterator<IndexType>& InOther) const`
- L187 _public function_ `inline bool operator!=(const TIndexIterator<IndexType>& InOther) const`
- L192 _public function_ `inline IndexType operator*() const`
- L197 _public function_ `inline TIndexIterator<IndexType>& operator++()` — prefix
- L202 _public function_ `inline TIndexIterator<IndexType> operator++(int32)` — postfix
- L209 _public function_ `TIndexIterator<IndexType>(int32 InIndex) : Index(InIndex)`
- L214 _private function_ `void Next()`
- L219 _private member_ `int32 Index = 0;`

#### struct `UE::MeshPartition::TIndexRange`  
`template <typename IndexType> struct TIndexRange`  
_L223-245_
- L229 _public function_ `TIndexRange(int32 InStart, int32 InEnd) : Start(InStart) , End(InEnd)` — Creates a ranged-based for compatible range which returns all the indices from [Start, End) (inclusive start, exclusive end) Eg: TIndexRange(1, 5) -> [1, 2, 3, 4]
- L234 _public function_ `TIndexIterator<IndexType> begin()`
- L238 _public function_ `TIndexIterator<IndexType> end()`
- L243 _public member_ `int32 Start = 0;`
- L244 _public member_ `int32 End = 0;`

#### class `UE::MeshPartition::IModifierResolver`  
`class IModifierResolver`  
_L247-252_
- L250 _public prototype_ `virtual MeshPartition::UModifierComponent* ResolveModifier(const MeshPartition::FModifierDesc& ModifierDesc) = 0;`
- L251 _public function_ `virtual ~IModifierResolver()`

#### struct `UE::MeshPartition::FModifierGroup`  
`struct FModifierGroup`  
_L254-489_
- L274 _public prototype_ `static bool ShouldApplyModifierBefore(TConstArrayView<FName> InLayerPriorities, const MeshPartition::FModifierDesc& InModifier, const MeshPartition::FModifierDesc& InOtherModifier);` — Returns true if the first passed modifier should be applied before the second according to the passed list of type priorities.
- L277 _public prototype_ `bool ShouldApplyInstanceBefore(TConstArrayView<FName> InLayerPriorities, const FInstanceInfo& InInstance, const FInstanceInfo& InOtherInstance) const;` — Returns true if the first passed modifier instance should be applied before the second according to the passed list of type priorities.
- L278 _public function_ `bool ShouldApplyInstanceBefore(TConstArrayView<FName> InLayerPriorities, FInstanceIndex InInstanceIndex, FInstanceIndex InOtherInstanceIndex) const`
- L283 _public function_ `void SetModifierResolver(TSharedPtr<MeshPartition::IModifierResolver> InModifierResolver)`
- L286 _public prototype_ `static bool HasDependency(const MeshPartition::FModifierDesc& InModifier, const MeshPartition::FModifierDesc& InOtherModifier);` — Returns true if the passed modifiers have a build dependency on each other.
- L287 _public prototype_ `bool HasDependency(const FInstanceInfo& InInstance, const FInstanceInfo& InOtherInstance) const;`
- L288 _public function_ `bool HasDependency(FInstanceIndex InInstanceIndex, FInstanceIndex InOtherInstanceIndex) const`
- L294 _public prototype_ `bool ValidateIsSorted(TConstArrayView<FName> InLayerPriorities) const;` — Returns true if the modifier descriptor list is correctly sorted by priority. Used for debug validation only.
- L296 _public prototype_ `FBox ComputeBaseBounds() const;`
- L297 _public prototype_ `double ComputeBaseComplexity() const;`
- L298 _public prototype_ `double ComputeTotalComplexity() const;`
- L300 _public prototype_ `void Add(const MeshPartition::FModifierDesc& InBaseDesc);`
- L301 _public prototype_ `void AddBase(const MeshPartition::FModifierDesc& InBaseDesc);`
- L302 _public prototype_ `void AddModifier(const MeshPartition::FModifierDesc& InModifierDesc);`
- L304 _public prototype_ `void AddModifierSorted(TConstArrayView<FName> InModifierTypePriorities, const MeshPartition::FModifierDesc& InModifierDesc);` — Inserts a new modifier to this group at the correct index considering the sort priority.
- L307 _public prototype_ `void Sort(TConstArrayView<FName> InModifierTypePriorities);` — Sorts the modifiers in this group in sort priority.
- L310 _public prototype_ `void RemoveDisabledModifiers();` — Removes all disabled modifiers from the group.
- L311 _public prototype_ `bool IsEmpty() const;`
- L313 _public function_ `const TOptional<MeshPartition::EBuildType>& GetBuildType() const`
- L315 _public function_ `void SetBuildType(MeshPartition::EBuildType InBuildType)`
- L320 _public prototype_ `void ProgressToState(EState InTarget);`
- L323 _public prototype_ `MeshPartition::FModifierGroup CreateAsyncBuildGroup();` — Creates a copy of the build group for async processing.
- L325 _public function_ `const MeshPartition::FModifierDesc& GetModifierDesc(FInstanceIndex InInstanceIndex) const`
- L330 _public function_ `const MeshPartition::FModifierDesc& GetModifierDesc(const FInstanceInfo& InInstance) const`
- L335 _public function_ `const MeshPartition::FModifierDesc& GetModifierDesc(FModifierIndex InIndex) const`
- L340 _public function_ `const FInstanceInfo& GetInstanceInfo(FInstanceIndex InIndex) const`
- L346 _public function_ `FModifierIndex GetModifierIndex(FInstanceIndex InIndex) const`
- L353 _public function_ `TSharedPtr<const MeshPartition::IModifierBackgroundOp> GetModifierOp(FModifierIndex InIndex) const`
- L359 _public function_ `TSharedPtr<const MeshPartition::IModifierBackgroundOp> GetModifierOp(FInstanceIndex InIndex) const`
- L365 _public prototype_ `TWeakObjectPtr<MeshPartition::UModifierComponent> GetModifierPtr(FModifierIndex InIndex) const;`
- L367 _public function_ `FGuid GetModifierCacheKey(FModifierIndex InIndex) const`
- L374 _public function_ `FGuid GetModifierCacheKey(FInstanceIndex InIndex) const`
- L380 _public prototype_ `FGuid ComputeBaseModifierSetHash() const;`
- L381 _public prototype_ `FGuid ComputeBaseCacheKey() const;`
- L382 _public prototype_ `FGuid ComputeModifierSetHash() const;`
- L383 _public prototype_ `FGuid UpdateAndComputeModifierGroupHash();`
- L385 _public prototype_ `FBlake3Hash ComputeGroupBuildHash() const;`
- L387 _public function_ `TIndexRange<FModifierIndex> AllModifierIndices() const`
- L391 _public function_ `TIndexRange<FModifierIndex> BaseIndices() const`
- L395 _public function_ `TIndexRange<FModifierIndex> ModifierIndices() const`
- L399 _public function_ `TIndexRange<FInstanceIndex> InstanceIndices() const`
- L406 _public function_ `TConstArrayView<MeshPartition::FModifierDesc> AllModifierDescs() const`
- L410 _public function_ `TConstArrayView<MeshPartition::FModifierDesc> BaseDescs() const`
- L414 _public function_ `TConstArrayView<MeshPartition::FModifierDesc> ModifierDescs() const`
- L418 _public function_ `TConstArrayView<FInstanceInfo> Instances() const`
- L425 _public prototype_ `void ForAllModifiers(TFunctionRef<bool(MeshPartition::UModifierComponent*)> InFunc, bool bSkipInvalidModifiers = false) const;` — @param bSkipInvalidModifiers If true, silently skip null modifiers. (Otherwise, we will still skip them but will trigger an ensure)
- L427 _public prototype_ `void ForEachBase(TFunctionRef<bool(MeshPartition::UModifierComponent*)> InFunc) const;`
- L429 _public prototype_ `void ForEachModifier(TFunctionRef<bool(MeshPartition::UModifierComponent*)> InFunc) const;`
- L431 _public prototype_ `TArray<TWeakObjectPtr<MeshPartition::UModifierComponent>> AllResolvedModifierPtrs() const;`
- L434 _private prototype_ `void ForEachModifier_Internal(TConstArrayView<TSoftObjectPtr<MeshPartition::UModifierComponent>> InModifierPtrs, TFunctionRef<bool(MeshPartition::UModifierComponent*)> InFunc, bool bSkipInvalidModifiers = false) const;`
- L436 _private function_ `TConstArrayView<TSoftObjectPtr<MeshPartition::UModifierComponent>> AllModifierPtrs() const`
- L442 _private function_ `TConstArrayView<TSoftObjectPtr<MeshPartition::UModifierComponent>> BasePtrs() const`
- L448 _private function_ `TConstArrayView<TSoftObjectPtr<MeshPartition::UModifierComponent>> ModifierPtrs() const`
- L455 _private prototype_ `static int8 CompareModifierOrder(TConstArrayView<FName> InLayerPriorities, const MeshPartition::FModifierDesc& InModifier, const MeshPartition::FModifierDesc& InOtherModifier);`
- L458 _private prototype_ `void ResolveModifierPtrs();` — Resolves the MeshPartition::UModifierComponent pointers from the soft object paths in the descriptors.
- L460 _private prototype_ `void PrepareResources();` — Calls MeshPartition::UModifierComponent::PrepareResources on each modifier in the group.
- L462 _private prototype_ `void CreateBackgroundOps(MeshPartition::EBuildType InBuildType);` — Create the async background operators
- L464 _private prototype_ `void InitInstances();` — Initializes all modifier instances for processing on the async thread by the task graph.
- L469 _private member_ `TArray<MeshPartition::FModifierDesc> ModifierDescriptors;` — Sorted lists of modifier data where bases appear first, followed by non-base modifiers
- L471 _private member_ `TArray<TSoftObjectPtr<MeshPartition::UModifierComponent>> ModifierPointers;` — List of soft object ptrs to loaded modifier objects. These are initialized after the group is finalized and map 1-1 with ModifierDescs.
- L473 _private member_ `TArray<FGuid> ModifierCacheKeys;` — List of modifier cache keys. These are initialized after the group is finalized and map 1-1 with ModifierDescs.
- L475 _private member_ `TArray<TSharedPtr<const MeshPartition::IModifierBackgroundOp>> ModifierOps;` — List of modifier background operators. These are initialized after the group is finalized and map 1-1 with ModifierDescs.
- L478 _private member_ `TArray<FInstanceInfo> InstanceInfos;` — Per Modifier Instance Data
- L480 _private member_ `int32 NumBases = 0;`
- L483 _private member_ `bool bAsyncGroup = false;` — Group is prepared for use on the async threads. It is no longer permitted to use it to reference GT objects.
- L485 _private member_ `TSharedPtr<MeshPartition::IModifierResolver> ModifierResolver;`
- L487 _private member_ `EState CurrentState = EState::Uninitialized;`
- L488 _private member_ `TOptional<MeshPartition::EBuildType> BuildType;`

#### enum `UE::MeshPartition::FModifierGroup::EState`  
`enum class EState : uint32`  
_L257-271_
- L259 _public enumerator_ `Uninitialized = 0`
- L261 _public enumerator_ `DescriptorsFinalized = 1` — Modifier group is now locked and further changes to the grouping is blocked.
- L266 _public enumerator_ `ModifiersResolved = 2` — Resolved the MeshPartition::UModifierComponent pointers from the soft object paths in the descriptors. Until this point only FModifierDescriptors are valid.
- L268 _public enumerator_ `BackgroundOpsCreated = 3` — Created the async background operators
- L270 _public enumerator_ `InstancesReady = 4` — Initialized all modifier instances for processing on the async thread by the task graph.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MeshPartition` (scope `UE`)
- L65 _function_ `friend FArchive& operator<<(FArchive& Ar, FBaseGrowth& BaseGrowth)` (scope `UE::MeshPartition`)
- L491 _prototype_ `void SortModifierDescriptors(TConstArrayView<const FName> InModifierTypePriorities, TArray<MeshPartition::FModifierDesc>& InOutModifierDescriptors);` (scope `UE::MeshPartition`)
- L492 _prototype_ `TArray<MeshPartition::FModifierGroup> BuildModifierGroups(TConstArrayView<MeshPartition::FModifierDesc> InModifierDescriptors, const MeshPartition::FBuilderSettings& InSettings);` (scope `UE::MeshPartition`)
- L493 _prototype_ `MeshPartition::FModifierGroup BuildModifierGroupForBase(TConstArrayView<MeshPartition::FModifierDesc> InBaseSet, TConstArrayView<MeshPartition::FModifierDesc> InAllNonBaseModifiersSorted);` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionModifierGraphCache.h` (Public)


#### class `UE::MeshPartition::FModifierGraphCache`  
`class FModifierGraphCache`  
_L15-134_
- L18 _public prototype_ `FModifierGraphCache();`
- L25 _public prototype_ `void CacheMergedBaseMesh(const FGuid& InCacheKey, const FMeshData& InMesh);` — Stores a new mesh result in the cache with the corresponding cache key. @param InCacheKey The combined hash of all the base modifiers composing the merged base @param InMesh The resulting intermediate mesh at the cached layer.
- L33 _public prototype_ `bool GetCachedMergedBaseMesh(const FGuid& InCacheKey, FMeshData& OutCachedMesh);` — Retrieves a copy of an entry of the cache, if it exists. @param InCacheKey key created from hashing base modifier cache keys @param OutCachedMesh If cache hit, result is copied to the out param. @return True if a cache hit occured and cache entry was copied to the OutCachedMesh param.
- L36 _public prototype_ `double GetTotalMemoryUsageMB() const;` — Returns the current memory usage of the cache in MB.
- L39 _public prototype_ `double GetViewCacheMemoryUsageMB() const;` — Returns the current memory usage of the view cache in MB.
- L42 _public function_ `double GetMergedBaseCacheMemoryUsageMB() const` — Returns the current memory usage of the view cache in MB.
- L45 _public prototype_ `void Clear();` — Clears all cache entries and resets the cache.
- L47 _public prototype_ `static bool IsCachingEnabled();`
- L79 _public prototype_ `bool CopyBaseGroupViewCacheData(const FGuid& InBaseGroupKey, TConstArrayView<FSoftObjectPath> InModifierPaths, FBaseGroupViewCacheData& OutBaseGroupViewCacheData);` — Copies all cache entries for the passed set of modifier guids in a given base set into the output cache data. @param InBaseGroupCacheKey Hash of all the base modifier cache keys. Views are cached per modifier per base group, so the same modifier may have a different view if it applies to multiple bases. @param InModifierPaths The list of modifier paths whose cache entries should be retrieved. @param OutbaseGroupCacheData Output parameter where the requested cache data will be stored. @return Returns true if there is an existing cache entry for this base group.
- L89 _public prototype_ `void CacheBaseGroupViewCacheData(const FGuid& InBaseGroupCacheKey, FBaseGroupViewCacheData&& InBaseGroupViewCacheData);` — Writes the InBaseGroupCacheData into the persistent cache, moving the data out of the input parameter. InBaseGroupCacheData may contain only a subset of all the modifiers which are affecting the cache. In the case where local builders are executing, this may be the case. @param InBaseGroupKey Hash of all base modifier guids. @param InBaseGroupCacheData Set of modifier views to add to the cache for the base group. Data will be moved out of this parameter so should no longer be referenced after calling this function.
- L92 _private prototype_ `void CopyMesh(const FMeshData& InSourceMesh, FMeshData& OutMesh);`
- L94 _private prototype_ `void AddMergedBaseToCache_Unsafe(const FGuid& InCacheKey, const FMeshData& InMesh);`
- L97 _private prototype_ `void EnsureViewMemoryBudget();` — Ensures that the view cache does not exceed the memory budget. Evicts LRU entries if memory budget is exceeded.
- L99 _private prototype_ `double RemoveLeastRecentlyUsedMergedBase_Unsafe();`
- L100 _private prototype_ `double RemoveLeastRecentlyUsedViewCache_Unsafe();`
- L107 _private member_ `TLruCache<FGuid, FMergedBaseCacheEntry> MergedBaseCache;`
- L110 _private member_ `double BaseMeshMemoryUsedMB = 0;` — Current memory used by the cache to store full merged base meshes.
- L113 _private member_ `mutable FRWLock MergedBaseCacheMutex;` — Mutex to lock access to the LruCache
- L116 _private member_ `TMap<FGuid, TSharedPtr<FBaseGroupViewCacheData>> BaseViewCacheData;` — Map of base groups to that group's cache data.
- L118 _private typedef_ `using FBaseGroupGuid = FGuid;`
- L124 _private member_ `TLruCache<FSoftObjectPath, TPair<FBaseGroupGuid, double>> LeastRecentlyUsedModifiers;` — LruCache which stores the most recently used modifiers so we can evict modifiers which have not been used across all base sections recently.
- L130 _private member_ `mutable FMutex BaseViewCacheDataMutex;` — Locks the BaseViewCacheData and LRUModifier data. These two structures are almost always accessed together, so one mutex for both simplifies the code.
- L133 _private member_ `mutable FRWLock LayersToCacheMutex;` — Mutex to lock access to the list of layers to cache.

#### struct `UE::MeshPartition::FModifierGraphCache::FModifierCacheData`  
`struct FModifierCacheData`  
_L49-61_
- L51 _public member_ `FGuid CacheKey;`
- L55 _public member_ `TArray<FGuid> LocalViewHashes;` — Per instance local view hash. Hash sequence of all the modifiers which are applied in the local region of this instance and before this instance.
- L58 _public member_ `TArray<MeshPartition::FMeshView> MeshViews;` — Per instance cached mesh views
- L60 _public prototype_ `double GetMemoryUsageMB() const;`

#### struct `UE::MeshPartition::FModifierGraphCache::FBaseGroupViewCacheData`  
`struct FBaseGroupViewCacheData`  
_L63-69_
- L66 _public member_ `TMap<FSoftObjectPath, FModifierCacheData> ModifierCacheData;` — Maps static modifier guids to their cache data
- L68 _public member_ `FMutex Mutex;`

#### struct `UE::MeshPartition::FModifierGraphCache::FMergedBaseCacheEntry`  
`struct FMergedBaseCacheEntry`  
_L102-105_
- L104 _public member_ `FMeshData MeshData;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionModifierUtils.h` (Public)


#### enum `UE::MeshPartition::Utils::ERectangleFalloffMode`  
`enum class ERectangleFalloffMode`  
_L37-42_
- L39 _public enumerator_ `Linear`
- L40 _public enumerator_ `Smooth`
- L41 _public enumerator_ `CustomCurve`

#### class `UE::MeshPartition::Utils::FRectangleFalloffData`  
`class FRectangleFalloffData`  
_L45-63_
- desc: Helper for storing data used in multiple GetRectangleFalloffAlpha calls.
- L48 _public prototype_ `FRectangleFalloffData( const FVector2d& RectangleExtentIn, double CornerRadiusIn, double FalloffDistanceIn, ERectangleFalloffMode FalloffModeIn = ERectangleFalloffMode::Smooth, TSharedPtr<const FRichCurve> FalloffCurveIn = nullptr);`
- L54 _private member_ `FVector2d RectangleExtent;`
- L55 _private member_ `ERectangleFalloffMode FalloffMode = ERectangleFalloffMode::Smooth;`
- L56 _private member_ `double FalloffDistance = 0;`
- L57 _private member_ `TSharedPtr<const FRichCurve> FalloffCurve;`
- L58 _private member_ `double ClampedRadius = 0;`
- L59 _private member_ `double ClampedFalloff = 0;`
- L60 _private member_ `FVector2d CornerCenter = FVector2d::Zero();`

#### class `UE::MeshPartition::Utils::FHashArchive`  
`class FHashArchive : public FArchiveMD5`  
_L70-99_
- inherits: `FArchiveMD5`
- desc: Suggested hash method for computing modifier CacheKeys
- L73 _public function_ `FHashArchive()`
- L75 _public prototype_ `void operator += (const UDynamicMesh& Mesh);`
- L76 _public prototype_ `void operator += (const UDynamicMesh* Mesh);`
- L78 _public prototype_ `void operator += (const UStaticMesh& Mesh);`
- L79 _public prototype_ `void operator += (const UStaticMesh* Mesh);`
- L81 _public prototype_ `void operator += (const UTexture& Texture);`
- L82 _public prototype_ `void operator += (const UTexture* Texture);`
- L87 _public function_ `template<typename T> void operator += (T* Data)` — non-const pointers can just be serialized as const pointers (without this definition, the const reference template below is invoked for const pointers)
- L94 _public function_ `template<typename T> void operator += (const T& Data)` — use += operator to hash const types by making a non-const copy (basically a write-only serializer)

#### class `UE::MeshPartition::Utils::TAsyncTransform`  
`template<typename OutputT> class TAsyncTransform`  
_L133-195_
- desc: Utility class to transform some Input data into an Output data asynchronously. TAsyncTransform will only hold on to the input data for as long as it is required to construct the output. Once the output is prepared, the input data will be released. TAsyncTransform and the input data can be destroyed without waiting for the operation to complete. TAsyncTransform also provides utilities to chain multiple transforms together. Once the result of the prerequisite transform is ready it will chain into the subsequent. The subsequent output data will only be ready when both transforms are completed.
- L137 _public function_ `template<typename InputT, typename F> TAsyncTransform(TSharedRef<const InputT> InData, F&& AsyncInitFunc, UE::Tasks::FTask Prerequisite = {}) : AsyncData(MakeShared<OutputT>()) , AsyncInitTask(Tasks::Launch(TEXT("TAsyncInitData::AsyncInit"), [Data = MoveTemp(InData), AsyncData = AsyncData, AsyncInitFunc = MoveTemp(AsyncInitFunc)]() mutable { TUniqueFunction<OutputT(const InputT&)> AsyncInitFuncWrapper = MoveTemp(AsyncInitFunc); TRACE_CPUPROFILER_EVENT_SCOPE(TAsyncTransform::Init); *AsyncData = AsyncInitFuncWrapper(*Data); }, Prerequisite))`
- L141 _public function_ ``
- L150 _public function_ `template<typename InputT, typename F> TAsyncTransform(InputT InData, F&& AsyncInitFunc, UE::Tasks::FTask Prerequisite = {}) : AsyncData(MakeShared<OutputT>()) , AsyncInitTask(Tasks::Launch(TEXT("TAsyncInitData::AsyncInit"), [Data = MoveTemp(InData), AsyncData = AsyncData, AsyncInitFunc = MoveTemp(AsyncInitFunc)]() mutable { TUniqueFunction<OutputT(InputT)> AsyncInitFuncWrapper = MoveTemp(AsyncInitFunc); TRACE_CPUPROFILER_EVENT_SCOPE(TAsyncTransform::Init); *AsyncData = AsyncInitFuncWrapper(MoveTemp(Data)); }, Prerequisite))`
- L162 _public function_ `const OutputT& GetResult() const`
- L172 _public function_ `bool IsCompleted() const`
- L177 _public function_ `UE::Tasks::FTask GetAsyncInitTask() const`
- L183 _public function_ `template<typename ChainedOutputT> TAsyncTransform<ChainedOutputT> Chain(TUniqueFunction<ChainedOutputT(const OutputT&)>&& AsyncInitFunc) const`
- L192 _private member_ `TSharedRef<OutputT> AsyncData;`
- L194 _private member_ `const Tasks::FTask AsyncInitTask;`

#### class `UE::MeshPartition::Utils::TAsyncInitData`  
`template<typename ConstDataType, typename AsyncDataType> class TAsyncInitData : public TAsyncTransform<AsyncDataType>`  
_L202-232_
- inherits: `TAsyncTransform<AsyncDataType>`
- desc: TAsyncInitData expands on TAsyncTransform but also holds a persistent reference to the input data. Allowing it to be accessed even once the task has completed execution.
- L205 _public typedef_ `using Super = TAsyncTransform<AsyncDataType>;`
- L206 _public typedef_ `using AsyncInitFuncType = TUniqueFunction<AsyncDataType(const ConstDataType&)>;`
- L208 _public function_ `TAsyncInitData(TSharedRef<const ConstDataType> InData, AsyncInitFuncType&& AsyncInitFunc, UE::Tasks::FTask Prerequisite = {}) : Super(InData, MoveTemp(AsyncInitFunc), Prerequisite) , Data(InData)`
- L214 _public function_ `TAsyncInitData(TSharedRef<const ConstDataType> InData) : Super(InData) , Data(InData)`
- L220 _public function_ `const ConstDataType& GetImmutable() const`
- L225 _public function_ `const AsyncDataType& GetAsyncData() const`
- L231 _private member_ `TSharedRef<const ConstDataType> Data;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MeshPartition` (scope `UE`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace MeshPartition` (scope `UE`)
- L28 _namespace_ `namespace Utils` (scope `UE::MeshPartition`)
- L30 _prototype_ `TArray<FBox> CollectBoundingBoxesForSpline( const USplineComponent* SplineComponent, TFunctionRef<float(float)> GetWidthForDistanceAlongSpline, TFunctionRef<float(float)> GetHeightForDistanceAlongSpline, float MaxSquaredDistance );` (scope `UE::MeshPartition::Utils`)
- L64 _prototype_ `double GetRectangleFalloffAlpha(const FVector2d Local2DCoordinates, const FRectangleFalloffData& FalloffData);` (scope `UE::MeshPartition::Utils`)
- L67 _prototype_ `FGuid BetterHashCombine(const FGuid& GuidA, const FGuid& GuidB);` (scope `UE::MeshPartition::Utils`) — better deterministic hash combine, that mixes the data between the four DWORDs of the FGuid, instead of just hashing each independently
- L107 _prototype_ `void ForEachMegaMeshDescInWorldPartition(UWorldPartition* InWorldPartition, TFunctionRef<void(MeshPartition::FModifierDesc& Descriptor)> PerModifierCallback, TFunctionRef<void(FCompiledSectionDescriptor& Descriptor)> PerSectionCallback);` (scope `UE::MeshPartition::Utils`) — Gathers descriptors for all of the mega mesh modifiers and compiled sections in the world partition @param InWorldPartition The world partition to use to iterate actor descriptors. @param PerModifierCallback the callback function that is invoked for each Modifier descriptor found. @param PerSectionCallback the callback function that is invoked for each CompiledSection descriptor found.
- L114 _prototype_ `void ForEachModifierDescInActorDesc(const FWorldPartitionActorDescInstance* ActorDescInstance, TFunctionRef<void(MeshPartition::FModifierDesc& Descriptor)> PerModifierCallback);` (scope `UE::MeshPartition::Utils`) — Gathers descriptors for mega mesh modifiers from the ActorDescInstance @param ActorDescInstance The world partition actor descriptor to gather modifier from. @param PerModifierCallback the callback function that is invoked for each Modifier descriptor found.
- L119 _prototype_ `bool IsNonzeroWeightLayer(const UE::Geometry::FDynamicMesh3& Mesh, int32 WeightLayerIndex);` (scope `UE::MeshPartition::Utils`) — Returns true if the given index weight layer exists on the mesh, and has a nonzero value on at least one vertex.
- L236 _function_ `template<typename ...TasksTypes> UE::Tasks::FTask MakeJoinTask(TasksTypes&&... InitTasks)` (scope `UE::MeshPartition::Utils`) — Utility which merges the join tasks of multiple separate init tasks into a single task event.
- L241 _function_ `TEXT("TAsyncInitTask::Join"), []()` (scope `UE::MeshPartition::Utils::MakeJoinTask`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionPlatformCellTransformer.h` (Public)


#### class `UE::MeshPartition::UPlatformCellTransformer`  
`class UPlatformCellTransformer : public UWorldPartitionRuntimeCellTransformer`  
_L15-21_
- reflection: `UCLASS(meta = (DisplayName = "Mesh Partition Platform Cell Transformer"))`
- inherits: `UWorldPartitionRuntimeCellTransformer`
- L19 _public prototype_ `virtual bool ShouldStripRuntimeCell(const UWorldPartitionRuntimeCell* InCell) const override;`
- L20 _public prototype_ `virtual void TransformRuntimeCell(UWorldPartitionRuntimeCell* InCell) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionPreviewComponents.h` (Public)


#### class `UE::MeshPartition::UStaticMeshPreviewComponent`  
`class UStaticMeshPreviewComponent : public UMeshPartitionStaticMeshComponent`  
_L25-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshPartitionStaticMeshComponent`
- desc: Subclass of static mesh component in order to customize the hit proxy, which needs to be custom to allow our visualizer to customize click handling for preview components (to route selection to base sections).
- L33 _public prototype_ `virtual HHitProxy* CreateMeshHitProxy(int32 SectionIndex, int32 MaterialIndex) const override;` — Static mesh scene proxy calls into this method to set up hit proxies for different sections (note: there is still also a hitproxy that points to the preview component itself, but that doesn't seem to get in the way).

#### class `UE::MeshPartition::UPreviewMeshComponent`  
`class UPreviewMeshComponent : public UMeshComponent, public IInterface_CollisionDataProvider`  
_L38-93_
- reflection: `UCLASS(MinimalAPI, meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)`
- inherits: `UMeshComponent,IInterface_CollisionDataProvider`
- L43 _public prototype_ `UPreviewMeshComponent();`
- L45 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& Size) override;`
- L47 _public prototype_ `void SetMeshData(TSharedRef<const MeshPartition::FMeshData> InMeshData);`
- L48 _public prototype_ `void SetMeshData(MeshPartition::FMeshData&& InMeshData);`
- L50 _public function_ `TSharedPtr<const FMeshData> GetMeshData()`
- L53 _public prototype_ `FMegaMeshCustomPreviewSceneProxy* GetCustomSceneProxy() const;` — Returns the custom preview scene proxy if one has been created, otherwise nullptr.
- L55 _public function_ `virtual int32 GetNumMaterials() const override`
- L56 _public prototype_ `virtual void SetMaterial(int32 ElementIndex, UMaterialInterface* Material) override;`
- L57 _public prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials) const override;`
- L58 _public prototype_ `virtual UBodySetup* GetBodySetup() override;`
- L60 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L62 _public prototype_ `virtual void OnRegister() override;`
- L63 _public prototype_ `virtual void OnUnregister() override;`
- L66 _public prototype_ `virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;`
- L67 _public prototype_ `virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;`
- L68 _public prototype_ `virtual bool GetTriMeshSizeEstimates(struct FTriMeshCollisionDataEstimates& OutTriMeshEstimates, bool bInUseAllTriData) const override;`
- L69 _public prototype_ `virtual void GetMeshId(FString& OutMeshId) override;`
- L73 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L75 _private prototype_ `void RebuildPhysicsData();`
- L76 _private prototype_ `UBodySetup* CreateBodySetupHelper();`
- L78 _private prototype_ `void AbortPendingPhysicsCook();`
- L79 _private prototype_ `void FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup);`
- L83 _public member_ `TArray<TObjectPtr<class UMaterialCacheVirtualTexture>> MaterialCacheTextures;` — `UPROPERTY(Transient, Experimental)`
- L87 _private member_ `TObjectPtr<UBodySetup> MeshBodySetup;` — `UPROPERTY(Transient, Instanced)`
- L90 _private member_ `TObjectPtr<UBodySetup> AsyncBodySetup;` — `UPROPERTY(Transient, Instanced)` — Body setup being cooked asynchronously
- L92 _private member_ `TSharedPtr<const FMeshData> MeshData;`

#### struct `UE::MeshPartition::HPreviewProxy`  
`struct HPreviewProxy : public HComponentVisProxy`  
_L99-114_
- inherits: `HComponentVisProxy`
- desc: Simple custom hitproxy similar to HActor, but inheriting from HComponentVisProxy to allow our visualizers to customize the click handling inside FComponentVisualizerManager::HandleProxyForComponentVis
- L101 _public prototype_ `DECLARE_HIT_PROXY();`
- L103 _public prototype_ `HPreviewProxy(const UActorComponent* InComponent);`
- L105 _public member_ `TWeakObjectPtr<const AActor> Actor;`
- L107 _public function_ `virtual FTypedElementHandle GetElementHandle() const override`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionPreviewSection.h` (Public)


#### class `UE::MeshPartition::APreviewSection`  
`class APreviewSection : public AActor`  
_L39-184_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `AActor`
- desc: This is a transient actor, expressing a “compiled” part of a MegaMesh. This means a region of the MegaMesh where all processing has been performed to produce the final result. It only exists in the editor.
- L44 _public prototype_ `APreviewSection();`
- L47 _public prototype_ `virtual void BeginDestroy() override;` — UObject Implementation
- L51 _public prototype_ `virtual void PostRegisterAllComponents() override;` — AActor Implementation
- L52 _public prototype_ `virtual void PostUnregisterAllComponents() override;`
- L55 _public function_ `const TArray<TObjectPtr<UStaticMeshComponent>>& GetMeshComponents() const`
- L57 _public prototype_ `void AddMesh(UStaticMesh* InStaticMesh, const FStaticMeshDescriptor& InDescriptor);`
- L58 _public prototype_ `void SetFarFieldMesh(UStaticMesh* InStaticMesh);`
- L59 _public prototype_ `void AddCollisionComponent(UMeshPartitionCollisionComponent* InCollisionComponent);`
- L60 _public prototype_ `TArray<TObjectPtr<UStaticMesh>> GetMeshes() const;`
- L61 _public prototype_ `TSharedPtr<const MeshPartition::FMeshData> GetPreviewMesh() const;`
- L62 _public function_ `UPreviewMeshComponent* GetPreviewMeshComponent() const`
- L63 _public prototype_ `void SetPreviewMesh(TSharedRef<const MeshPartition::FMeshData> InMeshData, const FName& InCollisionProfileName, const bool bInCanEverAffectNavigation);`
- L65 _public prototype_ `AMeshPartition* GetParent() const;`
- L66 _public prototype_ `void SetParent(AMeshPartition* InMegaMesh);`
- L68 _public prototype_ `void SetMaterialInstance(UMaterialInstanceDynamic* InMaterialInstance);`
- L69 _public function_ `UMaterialInstanceDynamic* GetMaterialInstance() const`
- L71 _public prototype_ `void SetChannelData(TConstArrayView<uint8> InChannelTable, const FVector2f& InTexcoordDesc);`
- L72 _public function_ `const TArray<uint8>& GetChannelTable() const`
- L73 _public prototype_ `void SetChannelTexture(UTexture* InChannelTexture);`
- L74 _public function_ `UTexture* GetChannelTexture() const`
- L76 _public function_ `void SetChannelGenerationMesh(const MeshPartition::FSectionChannelGenerationMeshData& InSection)`
- L77 _public function_ `const MeshPartition::FSectionChannelGenerationMeshData& GetChannelGenerationMesh() const`
- L79 _public prototype_ `void SetBuildPerfStats(MeshPartition::FBuildPerfStats&& InBuildPerfStats);`
- L80 _public prototype_ `const MeshPartition::FBuildPerfStats& GetBuildPerfStats() const;`
- L82 _public function_ `void SetIsTransformerPipelinePaused(const bool bInIsPaused)`
- L83 _public function_ `bool IsTransformerPipelinedPaused() const`
- L85 _public prototype_ `void OnMeshPartitionDefinitionChanged(const UMeshPartitionDefinition* InDefinition);`
- L86 _public prototype_ `void OnMeshPartitionDefinitionModified(const UMeshPartitionDefinition* InDefinition, const FName& InPropertyName);`
- L88 _public prototype_ `void SetMaterialCacheTileCount(const FIntPoint& TileCount);`
- L89 _public prototype_ `void RecreateMaterialCacheTextures();`
- L91 _public function_ `const TArray<TWeakObjectPtr<MeshPartition::UModifierComponent>>& GetBaseModifiers() const`
- L92 _public prototype_ `void AddBaseModifier(const TWeakObjectPtr<MeshPartition::UModifierComponent>& InBaseModifier);`
- L93 _public prototype_ `void RemoveBaseModifier(const TWeakObjectPtr<MeshPartition::UModifierComponent>& InBaseModifier);`
- L95 _public function_ `const TArray<TWeakObjectPtr<MeshPartition::UModifierComponent>>& GetModifiers() const`
- L96 _public prototype_ `void AddModifier(const TWeakObjectPtr<MeshPartition::UModifierComponent>& InModifier);`
- L98 _public function_ `FBox GetPreviewMeshBounds() const`
- L100 _public prototype_ `UMeshPartitionEditorComponent* GetMegaMeshEditorComponent() const;`
- L102 _public prototype_ `void SetRuntimeVirtualTextures(const TArray<TObjectPtr<URuntimeVirtualTexture>>& InRVTs);`
- L104 _public function_ `void SetGroupRegistryKey(const FGuid& InKey)`
- L105 _public function_ `FGuid GetGroupRegistryKey() const`
- L107 _public prototype_ `void ForAllPrimitiveComponents(TFunctionRef<bool(UPrimitiveComponent*)> InFunc) const;`
- L109 _private prototype_ `void OnStaticMeshBuild(UStaticMesh* InStaticMesh);`
- L110 _private prototype_ `void OnFarFieldStaticMeshBuild(UStaticMesh* InStaticMesh);`
- L111 _private prototype_ `void InvalidateRenderStates();`
- L113 _private prototype_ `UMaterialInterface* GetPreviewMaterial() const;`
- L117 _private member_ `TArray<TWeakObjectPtr<MeshPartition::UModifierComponent>> BaseModifiers;` — `UPROPERTY(Transient)`
- L120 _private member_ `TArray<TWeakObjectPtr<MeshPartition::UModifierComponent>> Modifiers;` — `UPROPERTY(Transient)`
- L123 _private member_ `TObjectPtr<UPreviewMeshComponent> PreviewMeshComponent;` — `UPROPERTY(Transient)`
- L127 _private member_ `TArray<TObjectPtr<UStaticMeshComponent>> VirtualTextureFallbackMeshComponents;` — `UPROPERTY(Transient)` — Fallback components for virtual texture rendering, this is a stop-gap solution, will be removed later
- L130 _private member_ `bool bIsTransformerPipelinePaused = false;` — `UPROPERTY(Transient)`
- L133 _private member_ `TArray<TObjectPtr<UStaticMeshComponent>> MeshComponents;` — `UPROPERTY()`
- L136 _private member_ `TArray<TObjectPtr<UMeshPartitionCollisionComponent>> CollisionComponents;` — `UPROPERTY()`
- L141 _private member_ `TObjectPtr<UStaticMeshComponent> FarFieldMeshComponent;` — `UPROPERTY()` — #todo: it would be better for the component to be visible so it shows up in the details panel. However, currently the details panel will block the static mesh compilation in order to display the details.
- L144 _private member_ `TSoftObjectPtr<AMeshPartition> Parent;` — `UPROPERTY()`
- L147 _private member_ `TObjectPtr<UMaterialInstanceDynamic> MaterialInstance;` — `UPROPERTY(EditAnywhere, Category = "MeshPartition")`
- L150 _private member_ `TObjectPtr<UTexture> ChannelTexture;` — `UPROPERTY(EditAnywhere, Category = "MeshPartition")`
- L153 _private member_ `FVector2f ChannelTexcoordDesc;` — `UPROPERTY()`
- L156 _private member_ `TArray<uint8> ChannelTable;` — `UPROPERTY()`
- L159 _private member_ `FIntPoint MaterialCacheTileCount = FIntPoint(1, 1);` — `UPROPERTY()`
- L163 _private member_ `TArray<TObjectPtr<UMaterialCacheVirtualTexture>> MaterialCacheTextures;` — `UPROPERTY(Transient, Experimental)` — All allocated material cache textures
- L173 _private member_ `FBox PreviewMeshBounds;` — `UPROPERTY()` — Cached preview mesh bounds. When the static mesh build finishes, the DynamicMeshComponent no longer contains valid bounds data and the component bounds will simply return a very small box (note: not empty/invalid) around the origin. Conversely, while the static mesh build is processing, the StaticMeshComponent will return the same small bounds around the origin. Rather than relying on either of them, we simply cache the bounds of the mesh when it is assigned to the preview section.
- L176 _private member_ `MeshPartition::FBuildPerfStats BuildPerfStats;` — `UPROPERTY(VisibleAnywhere, Category = MeshPartition)`
- L178 _private member_ `FGuid GroupRegistryKey;`
- L181 _private member_ `FSectionChannelGenerationMeshData SectionChannelMesh;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L17 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionRVTTransformer.h` (Public)


#### struct `UE::MeshPartition::FRVTTransformer`  
`struct FRVTTransformer : public MeshPartition::FTransformer`  
_L23-40_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `MeshPartition::FTransformer`
- desc: Mesh Partition Transformer binding the provided RVT to the sections present in the context. Will only apply the transformation once per section.
- L28 _public prototype_ `virtual bool Execute(MeshPartition::UPreviewMeshComponent& InPreviewMeshComponent, const MeshPartition::UMeshPartitionDefinition* InDefinition, const MeshPartition::FCommonBuildVariant& InBuildVariant) const;`
- L30 _public prototype_ `virtual bool Execute(MeshPartition::FTransformerContext& InTransformerContext) const override;`
- L32 _public prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& InDependencies) const override;`
- L35 _private prototype_ `void SetRuntimeVirtualTextures(const MeshPartition::FTransformerContext& InTransformerContext) const;`
- L39 _private member_ `TArray<TObjectPtr<URuntimeVirtualTexture>> RuntimeVirtualTextures;` — `UPROPERTY(EditAnywhere, Category = "Material|RVT")`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionRectangleGenerator.h` (Public)


#### struct `UE::MeshPartition::FRectangleGeneratorUtils`  
`struct FRectangleGeneratorUtils`  
_L24-69_
- L40 _public prototype_ `static FInt32Point ComputeSectionResolution(const FInt32Point MeshResolution, const int32 MaxTrianglesPerSection);` — Compute the canonical section for the spatial decomposition of the given mesh resolution (in quads). A resolution of zero will be returned if any of the inputs are .leq. to zero. Note: when the mesh is decomposed into sections, it may require some smaller sections to complete the decomposition (see comment in ComputeSectionInfos )
- L47 _public prototype_ `static TArray<FSectionInfo> ComputeSectionInfos(const FInt32Point MeshResolution, const FInt32Point SectionsResolution);` — Compute the partitions of the the mesh based on the provided mesh resolution and optimal section resolution. Note, in the case that the mesh resolution is not a multiple of the section resolution, the remainder sections will be smaller. @return Array of FSectionInfo
- L53 _public prototype_ `static TArray<MeshPartition::UMeshProviderModifier*> SpawnBaseModifiers(const TArray<FSectionInfo>& SectionInfos, const FVector& MeshSize, const FVector2d& MeshWorldOffset, const FTransform& ToWorld, const bool bRegisterModifers, UWorldPartition* WorldPartition, UMeshPartitionEditorComponent* MegaMeshEditorComponent, FSlowTask* SlowTask = nullptr);` — Spawn in the world (and optionally register) base modifiers associated with the MegaMesh by means of the provided MegaMeshEditorComponent @return Array of pointers to the MegaMesh MeshProviders corresponding to the base modifiers.
- L58 _public prototype_ `static void SpawnLocationVolumes(const FVector& MeshSize, const FVector2d& MeshWorldOffset, const FInt32Point& LocationVolumesResolution, UWorld* const World, AMeshPartition* const MegaMesh, FSlowTask* SlowTask = nullptr);` — Spawn location volumes in the world and attach them to the MegaMesh.  To be used by world partition.
- L60 _public prototype_ `static ALocationVolume* CreateLocationVolume(UWorld* const World, AMeshPartition* const MegaMesh, const FString& Label, const FBox& Bounds);`
- L66 _public prototype_ `static void GenerateSectionMesh(Geometry::FDynamicMesh3& Mesh, const FSectionInfo& SectionInfo, const FVector& MeshSize, TFunction<double(FVector2f) >& GetHeight);` — Create a height field rectangular mesh with the size and UVs specified by SectionInfo If GetHeight references an unset TFunction, the mesh will be planar.

#### struct `UE::MeshPartition::FRectangleGeneratorUtils::FSectionInfo`  
`struct FSectionInfo`  
_L26-32_
- L28 _public member_ `FInt32Point IndexXY;`
- L29 _public member_ `FInt32Point Resolution;`
- L30 _public member_ `FVector2d MinUV;`
- L31 _public member_ `FVector2d MaxUV;`

#### class `UE::MeshPartition::FMegaMeshGeneratorBase`  
`class FMegaMeshGeneratorBase`  
_L73-110_
- desc: This base class exists to share functionality related to actor unloading and packages when generating a multi-section Mega Mesh.   It is not intended to be used independently.
- L76 _public prototype_ `FMegaMeshGeneratorBase() = default;`
- L79 _public function_ `const FText& GetErrorText() const`
- L82 _public function_ `AMeshPartition* GetMegaMesh() const` — Returns the associated mega mesh actor
- L87 _protected prototype_ `void SaveActorPackages(const TArray<TWeakObjectPtr<AActor>>& InActorsToSave);`
- L90 _protected prototype_ `void CancelAndWait(UWorld* World);` — Cancel and block until all outstanding tasks are finished executing.
- L92 _protected prototype_ `void UnloadActors(const TArray<TWeakObjectPtr<AActor>>& InActorsToUnload, UWorld* World) const;`
- L95 _protected member_ `AMeshPartition* MegaMesh = nullptr;`
- L97 _protected member_ `FText ErrorText;`
- L99 _protected member_ `TArray<TPair<int, Tasks::FTask>> MeshTasks;`
- L100 _protected member_ `TArray<MeshPartition::UMeshProviderModifier*> MegaMeshMeshProviders;`
- L104 _protected member_ `TArray<Geometry::FDynamicMesh3> Meshes;` — This class operates on isolated FDynamicMeshes on parallel threads and are then moved onto the output mesh provider on the GT This ensures the correct events/callbacks are fired for the DynamicMeshComponent to ensure bounds are computed, proxies recreated, etc.
- L107 _protected member_ `TArray<FString> SavedPackages;` — Retain a list of all packages that were saved and unloaded in case the user cancels so they can be reverted.
- L109 _protected member_ `bool bIsCancelled = false;`

#### struct `UE::MeshPartition::FMegaMeshRectangleGeneratorParams`  
`struct FMegaMeshRectangleGeneratorParams`  
_L116-132_
- desc: List of parameters for the MegaMesh Rectangle Generator.
- L119 _public member_ `FInt32Point MeshResolution;` — Number of vertices in X/Y dimension for the generated mesh.
- L122 _public member_ `FVector2D MeshSize;` — World space size of the generated mesh.
- L125 _public member_ `FInt32Point SectionsResolution;` — Number of sections in X/Y dimension.
- L128 _public member_ `bool bSaveAndUnload;` — Save and unload sections as they are created.
- L131 _public member_ `FInt32Point LocationVolumesResolution;` — Number of location volumes in X/Y dimension.

#### class `UE::MeshPartition::FMegaMeshRectangleGenerator`  
`class FMegaMeshRectangleGenerator : public FMegaMeshGeneratorBase`  
_L136-171_
- inherits: `FMegaMeshGeneratorBase`
- desc: Class that generates a rectangular MegaMesh that has been partitioned into multiple underlying DynamicMeshes
- L139 _public function_ `FMegaMeshRectangleGenerator(const FMegaMeshRectangleGeneratorParams& InParams, UWorld& InWorld, FTransform InToWorld, AMeshPartition* InMegaMesh = nullptr) : World(&InWorld) , Params(InParams) , ToWorld(InToWorld) , ExistingMegaMesh(InMegaMesh)`
- L152 _public prototype_ `bool Generate(FPackageSourceControlHelper* InSourceControlHelper);` — Execute the Generate operation. If an FPackageSourceControlHelper is provided, newly created packages will also be added to source control. Returns true if the operation succeeded, false otherwise. Note: On failure, diagnostic error message can be retrieved with `GetErrorText`.
- L156 _protected prototype_ `FMegaMeshRectangleGenerator();`
- L158 _protected typedef_ `using FSectionInfo = MeshPartition::FRectangleGeneratorUtils::FSectionInfo;`
- L160 _protected prototype_ `Tasks::FTask LaunchBuildSectionTask(const FSectionInfo& SectionInfo, Geometry::FDynamicMesh3& Mesh);`
- L162 _protected member_ `UWorld* World = nullptr;`
- L164 _protected member_ `FMegaMeshRectangleGeneratorParams Params;`
- L167 _protected member_ `FTransform ToWorld;` — controls the actual placement of the MegaMeshRetangle
- L170 _protected member_ `AMeshPartition* ExistingMegaMesh = nullptr;` — if null, a new megamesh will be generated

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionRenderingUtils.h` (Public)


#### class `UE::MeshPartition::FRenderCaptureManager`  
`class FRenderCaptureManager`  
_L10-20_
- L12 _private member_ `int NextCaptureCounter = 0;`
- L13 _private member_ `TUniquePtr<RenderCaptureInterface::FScopedCapture> CurrentCapture;`
- L15 _public prototype_ `static FRenderCaptureManager& Get();`
- L17 _public prototype_ `static void CaptureNextBatch();`
- L18 _public prototype_ `static void BeginCapture(FRDGBuilder& InGraphBuilder);`
- L19 _public prototype_ `static void EndCapture();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionRuntimeCellTransformer.h` (Public)


#### class `UE::MeshPartition::URuntimeCellTransformer`  
`class URuntimeCellTransformer : public UWorldPartitionRuntimeCellTransformer`  
_L14-34_
- reflection: `UCLASS()`
- inherits: `UWorldPartitionRuntimeCellTransformer`
- L20 _public prototype_ `virtual void PreTransform(ULevel* InLevel) override;`
- L21 _public prototype_ `virtual void Transform(ULevel* InLevel) override;`
- L22 _public prototype_ `virtual void PostTransform(ULevel* InLevel) override;`
- L28 _private member_ `TSharedPtr<FMeshPartitionWorldUpdater> WorldUpdater;`
- L30 _private member_ `int32 CellsPreTransformed = 0;`
- L31 _private member_ `int32 CellsTransformed = 0;`
- L32 _private member_ `int32 CellsPostTransformed = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionSeparateWorldBuilder.h` (Public)


#### struct `UE::MeshPartition::FSeparateWorldBuilder`  
`struct FSeparateWorldBuilder`  
_L15-68_
- reflection: `USTRUCT()`
- L19 _public prototype_ `~FSeparateWorldBuilder();`
- L22 _public prototype_ `void RequestCompiledSectionBuild(MeshPartition::ACompiledSection* InCompiledSection);` — Add a compiled section build request to the queue
- L25 _public prototype_ `void Tick();` — Execute queued compiled section builds
- L28 _public prototype_ `void ClearRequests();` — Clears all pending compiled section builds requests.
- L48 _private prototype_ `void BuildCompiledSectionMesh(MeshPartition::ACompiledSection* InCompiledSection, FName InBuildVariantName);`
- L53 _private member_ `TObjectPtr<UPackage> BuilderPackage;` — `UPROPERTY()` — Current package used as a container for the separate world
- L56 _private member_ `TObjectPtr<UWorld> BuilderWorld;` — `UPROPERTY()`
- L59 _private member_ `TArray<TWeakObjectPtr<MeshPartition::ACompiledSection>> CompiledSectionsToBuild;` — `UPROPERTY()`
- L62 _private member_ `TArray<MeshPartition::FBuildTaskHandle> TaskHandles;` — other state that doesn't hold GC refs
- L63 _private member_ `TArray<FGuid> AllMegaMeshGuidsInWorld;`
- L67 _private member_ `TSharedPtr<FModifierGroupBuildCache> GroupBuildCache;` — Per-group build cache for grid-split sections (avoids N full mesh rebuilds per group). Lifetime is enforced by FBuilderWorldScope.

#### class `UE::MeshPartition::FSeparateWorldBuilder::FBuilderWorldScope`  
`class FBuilderWorldScope`  
_L35-45_
- desc: RAII guard for the BuilderWorld lifecycle. Constructs the BuilderWorld + package on entry; on exit, clears GroupBuildCache->Entries (cached modifier actor refs) before tearing the world down so cache entries never outlive the world they live in. Stack-only, used by Tick().
- L38 _public prototype_ `FBuilderWorldScope(FSeparateWorldBuilder& InOwner, const FString& InWorldPackageName);`
- L39 _public prototype_ `~FBuilderWorldScope();`
- L44 _private member_ `FSeparateWorldBuilder& Owner;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionSkirtTransformer.h` (Public)


#### struct `UE::MeshPartition::FMeshSkirtTransformer`  
`struct FMeshSkirtTransformer : public MeshPartition::FTransformer`  
_L21-56_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `MeshPartition::FTransformer`
- desc: Deprecated no-op transformer. Use FStaticMeshTransformer mesh skirt settings instead.
- L26 _public prototype_ `virtual bool Execute(MeshPartition::FTransformerContext& InTransformerContext) const override;`
- L28 _public prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& InDependencies) const override;`
- L34 _private member_ `float Width = 10.f;` — `UPROPERTY(EditAnywhere, Category="MeshSkirt", meta = (ClampMin = 0))` — Distance to offset the skirt vertices from the boundary, in the local plane of the boundary
- L38 _private member_ `float PushDown = 10.f;` — `UPROPERTY(EditAnywhere, Category="MeshSkirt", meta = (ClampMin = 0))` — Amount to push down the offset vertices
- L42 _private member_ `EMeshSkirtDirectionMethod PushMethod = EMeshSkirtDirectionMethod::VertexNormal;` — `UPROPERTY(EditAnywhere, Category="MeshSkirt")` — Method to choose the direction to push offset vertices
- L46 _private member_ `FVector PushDirection = FVector(0, 0, -1);` — `UPROPERTY(EditAnywhere, Category = "MeshSkirt", meta = (EditCondition = "PushMethod==EMeshSkirtDirectionMethod::FixedDirection"))` — Direction to push the offset skirt vertices, if using a fixed direction Push Method
- L50 _private member_ `float VertexSnapTolerance = UE_SMALL_NUMBER;` — `UPROPERTY(EditAnywhere, Category = "MeshSkirt", AdvancedDisplay, meta = (ClampMin = 0))` — Consider vertices closer than this distance to be the same for purposes of boundary walking
- L54 _private member_ `float BoundaryMinPerimeter = 1000.f;` — `UPROPERTY(EditAnywhere, Category = "MeshSkirt", AdvancedDisplay, meta = (ClampMin = 0))` — Do not add skirts to boundaries with perimeter smaller than this (to skip mesh boundaries that are not section boundaries)

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionStaticMeshTransformer.h` (Public)


#### enum `UE::MeshPartition::EMeshPartitionSimplificationMode`  
`enum class EMeshPartitionSimplificationMode : uint8`  
_L27-40_
- reflection: `UENUM()`
- desc: Selects which simplification inputs the user authors directly and which are derived. Driving values vs. derived values are paired so the UI can grey out the dependent fields.
- L30 _public enumerator_ `AutoScreenSizeFromError UMETA(DisplayName = "Derive ScreenSize from Error")` — ErrorTolerance drives simplification; ScreenSize is derived from the achieved deviation and PixelError.
- L33 _public enumerator_ `AutoErrorToleranceFromScreenSize UMETA(DisplayName = "Derive Target ErrorTolerance from ScreenSize")` — ScreenSize drives simplification; ErrorTolerance is derived from ScreenSize and PixelError.
- L36 _public enumerator_ `TriangleCountFromScreenSize UMETA(DisplayName = "TriangleCount from ScreenSize")` — ScreenSize drives simplification via MaxTrianglesFraction = ScreenSize; ErrorTolerance is unused.
- L39 _public enumerator_ `Custom UMETA(DisplayName = "Custom")` — All fields authored manually; no field is derived.

#### struct `UE::MeshPartition::FMeshPartitionTransformerSimplificationSettings`  
`struct FMeshPartitionTransformerSimplificationSettings`  
_L43-155_
- reflection: `USTRUCT()`
- L51 _public member_ `EMeshPartitionSimplificationMode Mode = EMeshPartitionSimplificationMode::Custom;` — `UPROPERTY(EditAnywhere, Category = "Simplification")` — Selects which inputs are authored manually and which are derived. See EMeshPartitionSimplificationMode.
- L62 _public member_ `float ErrorTolerance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Simplification", meta = (EditCondition = "Mode == EMeshPartitionSimplificationMode::AutoScreenSizeFromError || Mode == EMeshPartitionSimplificationMode::Custom"))` — If positive, acceptable geometric deviation from the input surface, otherwise unused. Will not decimate further than specified MinTrianglesFraction, and will always decimate at least to MaxTrianglesFraction (regardless of error tolerance). This is the recommended way of controlling detail. Derived in AutoErrorToleranceFromScreenSize mode. Unused in TriangleCountFromScreenSize mode.
- L68 _public member_ `float EdgeLength = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Simplification")` — If positive, maximum edge length to simplify up to.
- L74 _public member_ `float MinTrianglesFraction = 0.01f;` — `UPROPERTY(EditAnywhere, Category = "Simplification", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "ErrorTolerance > 0 || Mode == EMeshPartitionSimplificationMode::AutoErrorToleranceFromScreenSize"))` — Keep at least this fraction of the input triangles. Only applies when using error tolerance criterion.
- L86 _public member_ `float MaxTrianglesFraction = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Simplification", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "Mode != EMeshPartitionSimplificationMode::TriangleCountFromScreenSize"))` — Maximum fraction of triangles to retain. When ErrorTolerance > 0, this is a cap: the simplifier will always decimate at least to this fraction of the input, even if the error tolerance would otherwise prevent further collapses. When ErrorTolerance == 0, this becomes the target retention fraction (the simplifier reduces straight down to this triangle count). Default 1 = no reduction from this criterion. Derived in TriangleCountFromScreenSize mode (=ScreenSize).
- L95 _public member_ `float ScaleCorrection = 100.0f;` — `UPROPERTY(EditAnywhere, Category = "Simplification")` — Scaling term to re-balance the geometric and attribute layer influence of the simplifier. This value should reflect the relative scale of feature size of terrain vs standard assets. Increasing this value boosts the preservation of attributes (normals, tangents, UVs), but increasing it excessively will degrade geometric fidelity.
- L101 _public member_ `float MeshRegularization = 0.0005f;` — `UPROPERTY(EditAnywhere, Category = "Simplification")` — Regularization weight that can help to produce higher intrinsic quality in flat areas.
- L114 _public member_ `float ScreenSize = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Simplification", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "Mode != EMeshPartitionSimplificationMode::AutoScreenSizeFromError"))` — Screen size at which this LOD becomes active, expressed as the projected diameter of the mesh's bounding sphere relative to the viewport (0..1). The runtime selects the coarsest LOD whose ScreenSize still exceeds the current on-screen diameter, so this should monotonically decrease across LODs. Leave at 0 to fall back to the geometric default Pow(0.75, LODIndex) for that slot. Derived in AutoScreenSizeFromError mode.
- L122 _public member_ `float PixelError = 8.0f;` — `UPROPERTY(EditAnywhere, Category = "Simplification", meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "Mode != EMeshPartitionSimplificationMode::TriangleCountFromScreenSize"))` — Pixel error budget used to convert between ScreenSize and geometric deviation: allow up to this many pixels of geometric deviation (at 1920x1080, 90-degree HFOV) for this LOD. Higher values let the LOD activate closer to the camera. Unused in TriangleCountFromScreenSize mode.
- L129 _public member_ `float NormalAttributeWeight = 16.0f;` — `UPROPERTY(EditAnywhere, Category = "Simplification|Advanced", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Influence of per-corner normals on the attribute-aware quadric. Larger values preserve normal fidelity at the expense of geometry; 0 disables the normal term entirely.
- L135 _public member_ `float TangentAttributeWeight = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Simplification|Advanced", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Influence of tangents/bitangents on the attribute-aware quadric.
- L141 _public member_ `float ColorAttributeWeight = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Simplification|Advanced", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Influence of vertex colors on the attribute-aware quadric.
- L147 _public member_ `float TexCoordAttributeWeight = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Simplification|Advanced", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Influence of UVs on the attribute-aware quadric.
- L154 _public member_ `float WeightLayerWeight = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Simplification|Advanced", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Influence of weight-map layers on the attribute-aware quadric. 0 disables weight layers (matching the library default); the historical transformer default of 0.2 enables them.

#### struct `UE::MeshPartition::FLODSettings`  
`struct FLODSettings`  
_L158-168_
- reflection: `USTRUCT()`
- L164 _public member_ `bool bReduceMesh = false;` — `UPROPERTY(EditAnywhere, Category = "LOD")`
- L167 _public member_ `FMeshPartitionTransformerSimplificationSettings SimplifierSettings;` — `UPROPERTY(EditAnywhere, Category = "LOD", meta = (EditCondition = "bReduceMesh"))`

#### struct `UE::MeshPartition::FStaticMeshTransformer`  
`struct FStaticMeshTransformer : public MeshPartition::FTransformer`  
_L174-226_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `MeshPartition::FTransformer`
- desc: Mesh Partition Transformer producing and attaching a static mesh component for each transformer unit present in the execution context.
- L179 _public prototype_ `virtual bool Execute(MeshPartition::FTransformerContext& InTransformerContext) const override;`
- L181 _public prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& InDependencies) const override;`
- L184 _private prototype_ `TArray<UStaticMesh*> CreateStaticMeshes(MeshPartition::FTransformerContext& InTransformerContext) const;`
- L186 _private prototype_ `void BuildStaticMesh(MeshPartition::FTransformerContext& InTransformerContext, UE::Tasks::TTask<TArray<UStaticMesh*>>& InCreateStaticMeshesTask, const int32 InTransformerUnitIndex) const;`
- L188 _private prototype_ `void FinalizeStaticMeshes(MeshPartition::FTransformerContext& InTransformerContext, UE::Tasks::TTask<TArray<UStaticMesh*>>& InCreateStaticMeshesTask) const;`
- L192 _private member_ `FCollisionProfileName CollisionProfile = UCollisionProfile::NoCollision_ProfileName;` — `UPROPERTY(EditAnywhere, Category = "Collision")`
- L195 _private member_ `TArray<MeshPartition::FLODSettings> LODs;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh")`
- L198 _private member_ `EStaticMeshLODStreaming LODStreaming = EStaticMeshLODStreaming::Default;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh")`
- L201 _private member_ `FPerPlatformInt NumStreamedLODs;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh")`
- L204 _private member_ `bool bCanEverAffectNavigation = false;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh")`
- L207 _private member_ `bool bApplyMeshSkirt = false;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh|Skirt")`
- L210 _private member_ `FMeshSkirtSettings MeshSkirtSettings;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh|Skirt", meta = (EditCondition = "bApplyMeshSkirt"))`
- L213 _private member_ `bool bUseNanite = true;` — `UPROPERTY(EditAnywhere, Category = "Nanite")`
- L216 _private member_ `ENaniteGenerateFallback NaniteFallbackMode = ENaniteGenerateFallback::Enabled;` — `UPROPERTY(EditAnywhere, Category = "Nanite", meta = (EditCondition = "bUseNanite", DisplayName = "Generate Fallback Mesh"))`
- L219 _private member_ `ENaniteFallbackTarget NaniteFallbackTarget = ENaniteFallbackTarget::PercentTriangles;` — `UPROPERTY(EditAnywhere, Category = "Nanite", meta = (EditCondition = "bUseNanite"))`
- L222 _private member_ `float NaniteFallbackPercentTriangles = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Nanite", meta = (EditCondition = "bUseNanite && NaniteFallbackTarget == ENaniteFallbackTarget::PercentTriangles", ClampMin = "0.0", ClampMax = "1.0"))`
- L225 _private member_ `float NaniteFallbackRelativeError = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Nanite", meta = (EditCondition = "bUseNanite && NaniteFallbackTarget == ENaniteFallbackTarget::RelativeError", ClampMin = "0.0"))`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionSubsectionTransformer.h` (Public)


#### struct `UE::MeshPartition::FSubsectionTransformer`  
`struct FSubsectionTransformer : public MeshPartition::FTransformer`  
_L21-33_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `MeshPartition::FTransformer`
- desc: Mesh Partition Transformer producing multiple transformer units by splitting the meshdata contained in the pipeline transformer units. Effectively acts as a demultiplexer.
- L26 _public prototype_ `virtual bool Execute(MeshPartition::FTransformerContext& InTransformerContext) const override;`
- L28 _public prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& InDependencies) const override;`
- L32 _private member_ `uint32 SubSectionSize = 12800;` — `UPROPERTY(EditAnywhere, Category="Subsection")`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionWPActorPropertiesTransformer.h` (Public)


#### struct `UE::MeshPartition::FWPActorPropertiesTransformer`  
`struct FWPActorPropertiesTransformer : public MeshPartition::FTransformer`  
_L24-53_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `MeshPartition::FTransformer`
- desc: Mesh Partition Transformer setting up all relevant WP properties for sections being produced. Will only apply the transformation once per section.
- L29 _public prototype_ `virtual bool Execute(MeshPartition::FTransformerContext& InTransformerContext) const override;`
- L31 _public prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& InDependencies) const override;`
- L33 _public function_ `FName GetRuntimeGrid() const`
- L36 _private prototype_ `void SetActorProperties(const MeshPartition::FTransformerContext& InTransformerContext) const;`
- L40 _private member_ `bool bIsSpatiallyLoaded = true;` — `UPROPERTY(EditAnywhere, Category = "WorldPartition")`
- L43 _private member_ `FName RuntimeGrid;` — `UPROPERTY(EditAnywhere, Category = "WorldPartition")`
- L46 _private member_ `TArray<TSoftObjectPtr<UDataLayerAsset>> DataLayerAssets;` — `UPROPERTY(EditAnywhere, Category = "DataLayers")`
- L49 _private member_ `TSoftObjectPtr<UHLODLayer> HLODLayer;` — `UPROPERTY(EditAnywhere, Category = "HLOD", meta = (DisplayName = "HLOD Layer"))`
- L52 _private member_ `bool bIncludeActorInHLOD = false;` — `UPROPERTY(EditAnywhere, Category = "HLOD", meta = (DisplayName = "Include Actor in HLOD"))`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionWorldPartitionHelpers.h` (Public)


#### struct `UE::MeshPartition::WorldPartitionHelpers::FGridCellEstimate`  
`struct FGridCellEstimate`  
_L33-37_
- desc: Estimated grid cell with its absolute world-space coordinate and bounding box.
- L35 _public member_ `FIntVector GridCellCoord;`
- L36 _public member_ `FBox CellBounds;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshPartition` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MeshPartition` (scope `UE`)
- L21 _namespace_ `namespace WorldPartitionHelpers` (scope `UE::MeshPartition`)
- L30 _prototype_ `MeshPartition::FGridSettings ResolveGridFromPipeline(const MeshPartition::FCompiledSectionBuildVariant& InBuildVariant, const UWorld* InWorld);` (scope `UE::MeshPartition::WorldPartitionHelpers`) — Resolves the WP grid for a build variant by scanning its transformer pipeline. Finds the last FWPActorPropertiesTransformer, reads its RuntimeGrid name, and resolves both the cell size and the 2D flag in a single pass. Fallback: if the named grid is not found, tries the main grid (NAME_None). Returns a default-constructed FGridSettings (CellSize=0, bIs2D=false) if no WP transformer is found or no grid resolves.
- L44 _prototype_ `TArray<FGridCellEstimate> EstimateGridCells(const FBox& InGroupBounds, const MeshPartition::FGridSettings& InGridSettings, const FTransform& InLocalToWorld);` (scope `UE::MeshPartition::WorldPartitionHelpers`) — Computes per-cell bounds from a bounding box and grid configuration, using the same snapping as BuildSections. Returns all cells that the bounds overlap (some may contain no actual geometry). When `InGridSettings.bIs2D` is true, all cells share `GridCellCoord.Z=0` and span the full Z extent of `InGroupBounds`. Pass the MeshPartition actor's LocalToWorld so cell coords align with the WP runtime grid when the actor is translated; pass FTransform::Identity for non world space aligned splits.
- L46 _prototype_ `TSet<ULevelStreaming*> LoadAllLevelInstances(UWorldPartition* WorldPartition, TSet<FWorldPartitionReference>& InOutActorRefs);` (scope `UE::MeshPartition::WorldPartitionHelpers`)
- L48 _prototype_ `void LoadAllActorsFromStreamingLevels( MeshPartition::FModifierGroup& InGroup, const AMeshPartition* InMegaMesh, UWorldPartition* WorldPartition, TSet<FWorldPartitionReference>& InOutActorRefs, TFunctionRef<void(AActor* Modifier, bool bIsInLevelInstance)> PerActorCallback, TFunctionRef<void(MeshPartition::UModifierComponent* Modifier, bool bIsInLevelInstance)> PerModifierCallback);` (scope `UE::MeshPartition::WorldPartitionHelpers`)
- L56 _prototype_ `void LoadGroupModifiersViaWorldPartitionRef(MeshPartition::FModifierGroup& InGroup, UWorldPartition* InWorldPartition, TSet<FWorldPartitionReference>& OutActorRefs);` (scope `UE::MeshPartition::WorldPartitionHelpers`)
- L58 _prototype_ `void LoadAllRelevantMegaMeshActors(MeshPartition::FModifierGroup& InGroup, const AMeshPartition* InMegaMesh, TSet<FWorldPartitionReference>& OutActorRefs, TFunctionRef<void(AActor* Modifier, bool bIsInLevelInstance)> PerActorCallback, TFunctionRef<void(MeshPartition::UModifierComponent* Modifier, bool bIsInLevelInstance)> PerModifierCallback);` (scope `UE::MeshPartition::WorldPartitionHelpers`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/MeshPartitionWorldUpdater.h` (Public)


#### struct `UE::MeshPartition::FCompiledSectionStatus`  
`struct FCompiledSectionStatus`  
_L16-31_
- desc: what is the state of the prebuilt compiled sections for a group
- L18 _public member_ `bool bChecked : 1 = false;` — status has been determined
- L19 _public member_ `bool bIsPlaceholder : 1 = false;` — is a PIE placeholder
- L20 _public member_ `bool bNonTargetVariant : 1 = false;` — corresponds to a build variant that is not a target of this updater
- L21 _public member_ `bool bMismatchedModifiers : 1 = false;` — modifier set hash does not match any target group (set hash is derived from the modifier paths)
- L22 _public member_ `bool bBuildVariantHashMatches : 1 = false;` — build variant hash matches (definition/variant settings unchanged)
- L23 _public member_ `bool bPackageHashMatches : 1 = false;` — package hash matches
- L24 _public member_ `bool bClassHashMatches : 1 = false;` — class hash matches
- L25 _public member_ `bool bCannotFindFile : 1 = false;` — cannot find the compiled section file (asset registry does not know about it)
- L26 _public member_ `bool bIsDuplicate : 1 = false;` — is a duplicate of another compiled section (and this one should not be used)
- L27 _public member_ `bool bReuse : 1 = false;` — compiled section should be reused, because it is the best up-to-date compiled section for a target group
- L29 _public prototype_ `FString ToString() const;`
- L30 _public prototype_ `FString GetDetailsString(int32 CompiledSectionIndex, const FMeshPartitionUpdater& MeshPartitionUpdater, IAssetRegistry& AssetRegistry) const;`

#### struct `UE::MeshPartition::FBuildVariantUpdater`  
`struct FBuildVariantUpdater`  
_L34-79_
- desc: This structure reflects the status of compiled sections on disk (registered in the asset registry), with respect to the desired set of groups in a CachedBuildVariant.
- L39 _public prototype_ `FBuildVariantUpdater(const FGuid& InBuildKey, const AMeshPartition* InMeshPartition, const UMeshPartitionDefinition& InMeshPartitionDefinition, const MeshPartition::FModifierGrouping& InTargetModifierGrouping, TSharedPtr<MeshPartition::FCachedDescriptors> InAllMeshPartitionDescriptors, IAssetRegistry& InAssetRegistry, const UWorld* InWorld);`
- L43 _private member_ `FCompiledSectionBuildInfo BuildInfo;` — partial BuildInfo for this build variant (used to initialize PIE placeholders, and also stores info like BuildVariantName)
- L46 _private member_ `TSharedPtr<MeshPartition::FCachedDescriptors> AllMeshPartitionDescriptors;` — this TSharedPtr keeps the CachedBuildVariant from being deallocated
- L49 _private member_ `const MeshPartition::FModifierGrouping& TargetGrouping;` — the set of groups for a build variant
- L52 _private member_ `TMap<FGuid, int32> ModifierSetHashToTargetGroupIndex;` — mapping from modifier set hash to target group (index into TargetGrouping)
- L56 _private member_ `TArray<TMap<FIntVector, int32>> ReusableCompiledSectionIndicesForGroup;` — Per-group reuse tracking: maps GridCellCoord → CompiledSectionIndex in the MeshPartitionUpdater's CompiledSections array. For non-grid sections, the key is InvalidGridCellCoord. Empty map = no reusable sections for that group.
- L59 _private member_ `TMap<FSoftObjectPath, MeshPartition::FModifierDesc> BaseModifiersNeedingCreation;` — The set of base modifiers that are not currently represented within an up to date compiled section
- L62 _private member_ `MeshPartition::FGridSettings GridSettings;` — Grid configuration for this build variant (CellSize=0 = not grid-aligned or resolution failed)
- L66 _public function_ `int32 GetTargetGroupIndexFromModifierSetHash(const FGuid& ModifierSetHash) const` — Returns the target group index for the group with the specified modifier set hash.  Returns -1 if no matching target group is found.
- L67 _public function_ `TConstArrayView<MeshPartition::FModifierGroup> GetTargetModifierGroups() const`
- L69 _public function_ `FName GetBuildVariantName() const`
- L70 _public function_ `const MeshPartition::FModifierGrouping& GetTargetGrouping() const`
- L71 _public function_ `const FCompiledSectionBuildInfo& GetBuildInfo() const`
- L72 _public function_ `const FSoftObjectPath& GetMeshPartitionPath() const`
- L73 _public function_ `const MeshPartition::FGridSettings& GetGridSettings() const`
- L75 _public prototype_ `bool HasReusableCompiledSectionsForGroup(int32 InGroupIndex, const FMeshPartitionUpdater& InMeshPartitionUpdater) const;`
- L76 _public function_ `const TMap<FIntVector, int32>& GetReusableCompiledSectionIndicesForGroup(int32 InGroupIndex) const`
- L78 _public function_ `const TMap<FSoftObjectPath, MeshPartition::FModifierDesc>& GetBaseModifiersNeedingCreation() const`

#### struct `UE::MeshPartition::FMeshPartitionUpdater`  
`struct FMeshPartitionUpdater`  
_L82-122_
- desc: captures the current state of a single mesh partition build variant, and manages what needs to be done to bring it up to date
- L85 _public member_ `TSharedPtr<MeshPartition::FCachedDescriptors> AllCachedDescriptors;` — this shared ptr keeps the MeshPartition::FCachedDescriptors and all sub-structures (including the CompiledSections array) alive until we are done with our operation
- L88 _public member_ `TConstArrayView<FCompiledSectionDescriptor> CompiledSections;` — the set of existing compiled sections for our mesh partition (across ALL build variants) - this points into the array inside AllCachedDescriptors
- L91 _public member_ `TArray<MeshPartition::FCompiledSectionStatus> CompiledSectionStatus;` — Status of each compiled section (array is 1:1 with CompiledSections above)
- L94 _public member_ `TMap<FName, FBuildVariantUpdater> BuildVariantUpdaters;` — Updater for each build variant, indexed by build variant name
- L97 _public member_ `TMap<FGuid, int32> ActorGuidToCompiledSectionIndex;` — Maps a compiled section actor guid to its index in the CompiledSections array
- L103 _public member_ `TWeakObjectPtr<const AMeshPartition> MeshPartition;` — MeshPartition actor that owns this updater. Held weakly so callers can resolve the live actor transform on demand (e.g. for AMeshPartition::WorldToLocal/LocalToWorld during placeholder cell estimation) -- avoids the stale-snapshot class of bug if the actor is moved between updater construction and placeholder creation.
- L106 _public member_ `mutable int32 RemovedOutOfDate = 0;` — stats for what was updated (NOTE that if this updater is used on multiple copies of the world, i.e. during multi-head PIE, then these stats are aggregated)
- L107 _public member_ `mutable int32 RemovedNonTargetBuildVariant = 0;` — compiled sections removed for not being part of a target build variant
- L108 _public member_ `mutable int32 ReusedCompiledSections = 0;` — existing compiled sections that were re-used
- L109 _public member_ `mutable int32 AddedPlaceholderCompiledSections = 0;` — placeholder compiled sections created
- L110 _public member_ `mutable int32 RemovedUnknown = 0;` — compiled sections removed because they did not correspond to any compiled section tracked in this updater (unexpected state)
- L113 _public prototype_ `FMeshPartitionUpdater(const FGuid& InBuildKey, const AMeshPartition* InMeshPartition, const UMeshPartitionDefinition& InMeshPartitionDefinition, TSharedPtr<MeshPartition::FCachedDescriptors> InMeshPartitionAllCachedDescriptors, TConstArrayView<FName> InTargetBuildVariantNames, IAssetRegistry& InAssetRegistry, const UWorld* InWorld);`
- L114 _public function_ `const FBuildVariantUpdater* GetBuildVariantUpdater(const FName& BuildVariantName) const`
- L115 _public prototype_ `void ForAllBuildVariants(TFunctionRef<bool(const MeshPartition::FBuildVariantUpdater&)> InFunc) const;`
- L117 _public function_ `const FCompiledSectionDescriptor* GetCompiledSectionDescriptor(int32 CompiledSectionIndex) const`
- L118 _public prototype_ `const FCompiledSectionStatus* GetCompiledSectionStatus(int32 CompiledSectionIndex) const;`
- L119 _public prototype_ `const FCompiledSectionStatus* GetCompiledSectionStatus(const ACompiledSection* CompiledSection) const;`
- L121 _public prototype_ `void GetStatusSummary(FStatusSummary& InOutSummary) const;`

#### struct `UE::MeshPartition::FMeshPartitionWorldUpdater`  
`struct FMeshPartitionWorldUpdater`  
_L125-161_
- desc: captures the current state of all mesh partitions in a world, and manages what needs to be done to bring the world up to date
- L135 _private member_ `EUpdateMode UpdateMode;`
- L136 _private member_ `FGuid BuildKey;`
- L139 _private member_ `TMap<FGuid, FMeshPartitionUpdater> MeshPartitionUpdaters;` — Updater for each mesh partition in the world, indexed by mesh partition guid
- L142 _private member_ `TWeakObjectPtr<UWorld> PlaceholdersAddedToWorld;` — record the world that placeholders were added to, so we can remove them afterwards
- L146 _public prototype_ `FMeshPartitionWorldUpdater(UWorld* InWorld, EUpdateMode InUpdateMode);` — construct world updater for the specified world
- L148 _public function_ `EUpdateMode GetUpdateMode() const`
- L149 _public function_ `const FGuid& GetBuildKey() const`
- L151 _public prototype_ `int32 CreatePlaceholderActors(UWorld* InTargetWorld);`
- L152 _public prototype_ `int32 RemovePlaceholderActors();`
- L153 _public function_ `UWorld* GetPlaceholderWorld() const`
- L155 _public prototype_ `const FMeshPartitionUpdater* GetMeshPartitionUpdaterFor(const ACompiledSection* CompiledSection) const;`
- L156 _public prototype_ `const FCompiledSectionStatus* GetCompiledSectionStatus(const ACompiledSection* CompiledSection) const;`
- L158 _public prototype_ `void ReportStats() const;`
- L159 _public prototype_ `void GetStatusSummary(FStatusSummary& InOutSummary) const;`
- L160 _public prototype_ `void ReportSectionStatus(UWorld* InWorld) const;`

#### enum `UE::MeshPartition::FMeshPartitionWorldUpdater::EUpdateMode`  
`enum EUpdateMode`  
_L127-132_
- L129 _public enumerator_ `ForPIE` — will query mesh partitions and build variants necessary for PIE
- L130 _public enumerator_ `ForCook` — query all mesh partitions across all configured build variants - for cook, will issue warnings if compiled sections are not up to date
- L131 _public enumerator_ `ForCompile` — query all mesh partitions across all configured build variants - for compile

#### struct `UE::MeshPartition::FStatusSummary`  
`struct FStatusSummary`  
_L164-213_
- desc: summary of the status of compiled sections and groups
- L167 _public member_ `int32 MeshPartitionCount = 0;` — overall counts
- L168 _public member_ `int32 TargetBuildVariantCount = 0;` — total number of target build variants (sum over all mesh partitions)
- L169 _public member_ `int32 GroupCount = 0;` — total target modifier groups (sum over all mesh partitions, all target build variants)
- L170 _public member_ `int32 CompiledSectionCount = 0;` — total existing compiled sections (including out of date sections)
- L200 _public member_ `FCompiledSections CompiledSections;`
- L203 _public function_ `int32 SectionsUpToDate()` — Compiled sections that are up to date and will be reused (grid-split groups contribute N each)
- L206 _public function_ `int32 SectionsOutOfDate()` — Compiled sections whose package or class hash is out of date
- L209 _public function_ `int32 GroupsMissing()` — Modifier groups that have no corresponding compiled section at all
- L212 _public function_ `int32 CompiledSectionsToRemove()` — compiled sections that should be deleted

#### struct `UE::MeshPartition::FStatusSummary::FCompiledSections`  
`struct FCompiledSections`  
_L172-199_
- L178 _public member_ `int32 Placeholders = 0;` — these compiled sections should be removed (RuntimeCellTransformer actively deletes them)
- L179 _public member_ `int32 NonTargetVariant = 0;` — compiled sections that do not correspond to any target build variant
- L180 _public member_ `int32 MismatchedModifiers = 0;` — compiled sections whose modifier sets do not correspond to any target group
- L181 _public member_ `int32 Duplicates = 0;` — compiled sections that are redundant duplicates of the same build variant + modifier group
- L182 _public member_ `int32 BuildVariantHashFails = 0;` — compiled sections whose build variant hash is out of date (definition/variant settings changed — section is fundamentally invalid)
- L185 _public member_ `int32 PackageHashFails = 0;` — these compiled sections need to be updated (content is stale but configuration matches)
- L186 _public member_ `int32 ClassHashFails = 0;` — compiled sections whose class hashes are out of date and need to be rebuilt, but do correspond to a current group
- L189 _public member_ `int32 Reuse = 0;` — these compiled sections can be reused
- L192 _public member_ `int32 Missing = 0;` — these compiled sections are missing and need to be created
- L195 _public member_ `int32 CannotFindFile = 0;` — compiled sections that WERE reuseable, but were recently deleted (they still exist in the actor descriptors, but are not in the asset registry) - we can safely ignore these, they will be added to Missing if needed
- L198 _public member_ `int32 Unknown = 0;` — this should always be zero, it's counting compiled sections that have none of the above status flags set, which shouldn't happen

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/CodeReusableMeshPartitionModifierInterface.h` (Public)


#### class `UE::MeshPartition::UCodeReusableModifier`  
`class UCodeReusableModifier : public UInterface`  
_L12-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `UE::MeshPartition::ICodeReusableModifier`  
`class ICodeReusableModifier`  
_L23-52_
- desc: A modifier that implements this interface may be reused by code that manages modifiers. Notably, it can be reused by PCG elements that make use of UE::MeshPartition::Utils::GetPCGManagedMegaMeshModifier.
- L40 _public prototype_ `virtual void SetDisabledByCode(bool bDisabledIn) = 0;` — Used by code to temporarily deactive the modifier. For example, a PCG spawning node would use this function to temporarily deactivate the modifier at the start of graph execution so that it can sample an unmodified megamesh, but still have the component around in case it is able to reuse it later. Note that higher-level MegaMesh systems won't know about this deactivation, so implementers are responsible for making sure that the modifier doesn't make any changes and its cache keys are appropriately invalidated.
- L45 _public prototype_ `virtual void ResetForReuse() = 0;` — Called to prep the modifier for reinitializing with entirely different data.
- L51 _public prototype_ `virtual bool IsUsed() const = 0;` — Can be called to determine whether this reusable modifier ended up actually being used, so that it can be cleaned up by its managing system if not.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionBooleanModifier.h` (Public)


#### enum `UE::MeshPartition::EBooleanOperation`  
`enum class EBooleanOperation`  
_L23-33_
- reflection: `UENUM()`
- desc: CSG operation types
- L26 _public enumerator_ `Union = 0 UMETA(DisplayName = "Union")` — Merges the Tool and Mesh Partition geometry into a locally-closed surface, removing internal surfaces where they overlap.
- L29 _public enumerator_ `Subtract = 1 UMETA(DisplayName = "Subtract")` — Subtracts the Tool mesh from the Mesh Partition geometry, removing overlapping geometry and capping the result into a locally-closed surface.
- L32 _public enumerator_ `Trim = 2 UMETA(DisplayName = "Trim")` — Cuts away Mesh Partition geometry inside the Tool mesh, leaving an open hole at the boundary.

#### enum `UE::MeshPartition::EBooleanInsideTestMethod`  
`enum class EBooleanInsideTestMethod`  
_L37-41_
- reflection: `UENUM()`
- desc: Method to use for determining what is 'inside' a mesh
- L40 _public enumerator_ `WindingNumber = 0` — Use the fast winding number to determine if a point is inside a mesh

#### enum `UE::MeshPartition::EBooleanToolMeshEmbedding`  
`enum class EBooleanToolMeshEmbedding`  
_L45-56_
- reflection: `UENUM()`
- desc: Options to account for geometry outside the local region of the Boolean modifier tool mesh.
- L49 _public enumerator_ `Intersecting` — Assume the terrain locally passes through the Boolean operator bounds, and extends to a closed solid outside those bounds. Use this as the default for most terrain Booleans.
- L52 _public enumerator_ `Inside` — Assume terrain outside the Boolean operator fully encloses the operator's bounds. Use this if the Boolean is applied fully underground.
- L55 _public enumerator_ `Outside` — Assume no terrain from outside the operator bounds will affect the Boolean operation. Use this if the Boolean is applied fully above ground.

#### enum `UE::MeshPartition::EBooleanModifierChannelSourceMode`  
`enum class EBooleanModifierChannelSourceMode : uint8`  
_L59-64_
- reflection: `UENUM()`
- L61 _public enumerator_ `VertexColor`
- L62 _public enumerator_ `VertexWeight`
- L63 _public enumerator_ `Constant`

#### enum `UE::MeshPartition::EMegaMeshBooleanModifierPreviewVisOptions`  
`enum class EMegaMeshBooleanModifierPreviewVisOptions : uint8`  
_L67-72_
- reflection: `UENUM()`
- L69 _public enumerator_ `WhenTemporarilyDisabled`
- L70 _public enumerator_ `Never`
- L71 _public enumerator_ `Always`

#### struct `UE::MeshPartition::FBooleanModifierWeightEntry`  
`struct FBooleanModifierWeightEntry`  
_L76-101_
- reflection: `USTRUCT()`
- desc: Define weight channels to transfer from the boolean tool mesh
- L82 _public member_ `MeshPartition::FChannelName ChannelName;` — `UPROPERTY(EditAnywhere, Category = WeightAttribute, meta = (GetOptions = "GetMegaMeshDefinitionChannels"))` — The destination attribute channel to write.
- L86 _public member_ `MeshPartition::EBooleanModifierChannelSourceMode SourceMode = MeshPartition::EBooleanModifierChannelSourceMode::VertexColor;` — `UPROPERTY(EditAnywhere, Category = Weight)` — Determines where the values to write are acquired.
- L91 _public member_ `int32 VertexColorIndex = 0;` — `UPROPERTY(EditAnywhere, Category = Weight, meta = (ClampMin = "0", ClampMax = "3", EditCondition = "SourceMode == EBooleanModifierChannelSourceMode::VertexColor", EditConditionHides))` — Which channel of a vertex color to use as source data (0 through 3 for RGBA)
- L96 _public member_ `FName SourceWeightChannelName;` — `UPROPERTY(EditAnywhere, Category = Weight, meta = ( EditCondition = "SourceMode == EBooleanModifierChannelSourceMode::VertexWeight", EditConditionHides))` — Vertex weight channel name to use as source data
- L100 _public member_ `float WriteValue = 1.f;` — `UPROPERTY(EditAnywhere, Category = Weight, meta = ( EditCondition = "SourceMode == EBooleanModifierChannelSourceMode::Constant", EditConditionHides))`

#### class `UE::MeshPartition::UBooleanModifier`  
`class UBooleanModifier : public MeshPartition::UMeshBasedModifierBase`  
_L105-257_
- reflection: `UCLASS(MinimalAPI, PrioritizeCategories = ("Modifier", "Mesh", "Boolean", "WeightChannels"), meta = (BlueprintSpawnableComponent, MegaMeshClassVersion = "1"))`
- inherits: `MeshPartition::UMeshBasedModifierBase`
- L110 _public prototype_ `UBooleanModifier();`
- L116 _public prototype_ `void UpdateFromMesh();` — `UFUNCTION(CallInEditor, Category = Mesh)` — Updates internal mesh data from given detail panel inputs
- L119 _public prototype_ `virtual void ProcessMeshInstance(FDynamicMesh3& OutMesh);` — MeshPartition::UMeshBasedModifierBase
- L122 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;` — MeshPartition::UModifierComponent
- L123 _public function_ `virtual bool IsContiguous() const`
- L124 _public prototype_ `TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const;`
- L125 _public prototype_ `virtual FGuid GetCodeVersionKey() const override;`
- L126 _public prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const override;`
- L127 _public prototype_ `virtual double GetComplexity() const;`
- L134 _public function_ `void SetExpandOperatorBounds(const FVector3d& InExpandOperatorBounds)` — Sets the amount to expand the global Boolean operation bounds beyond the tool mesh bounds. @param InExpandOperatorBounds The expansion amount along each axis.
- L139 _public function_ `const FVector3d& GetExpandOperatorBounds() const` — @return The amount to expand the global Boolean operation bounds beyond the tool mesh bounds.
- L142 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject
- L143 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L145 _public prototype_ `virtual void DrawVisualization(const FSceneView* View, FPrimitiveDrawInterface* PDI) const override;`
- L149 _private prototype_ `virtual void PostUpdateMeshInstance(const FDynamicMesh3& MeshInstanceData) override;`
- L151 _private prototype_ `FBox ComputeWorldExpandedBounds(FVector ExpandAmount) const;`
- L153 _private function_ `bool ShouldDrawSolidPreview() const`
- L171 _private member_ `double PreOpSimplifierStrength { 0 };` — `UPROPERTY(EditAnywhere, Category = Mesh, meta = (ClampMin = "0.0", UIMax = "200"))` — Strength of simplification to apply to the op mesh before using it in the boolean operation. Higher value indicates more simplification, 0 is none. Value corresponds to desired edge length in the simplified mesh.
- L177 _private member_ `bool bSimplifierConstrainBoundary = true;` — `UPROPERTY(EditAnywhere, Category = Mesh, AdvancedDisplay)` — When simplifying, whether to try to preserve boundary edge flow.
- L183 _private member_ `bool bSimplifierConstrainSeams = false;` — `UPROPERTY(EditAnywhere, Category = Mesh, AdvancedDisplay)` — When simplifying, whether to try to preserve various seam edge flows (UVs, normals, etc).
- L189 _private member_ `TArray<MeshPartition::FBooleanModifierWeightEntry> WeightChannels;` — `UPROPERTY(EditAnywhere, Category = WeightChannels, Meta = (ShowOnlyInnerProperties))` — Weight Channels to transfer from the tool mesh to the target mesh
- L192 _private member_ `MeshPartition::EBooleanOperation BooleanOp { MeshPartition::EBooleanOperation::Union };` — `UPROPERTY(EditAnywhere, Category = Boolean)`
- L201 _private member_ `MeshPartition::EBooleanToolMeshEmbedding ToolMeshEmbedding = MeshPartition::EBooleanToolMeshEmbedding::Intersecting;` — `UPROPERTY(EditAnywhere, Category = Boolean, meta = (EditCondition="BooleanOp != EBooleanOperation::Trim"))` — What to assume about the terrain/target mesh beyond the local operator bounds of the modifier. This is useful for e.g. using Boolean subtractions to create caverns underneath the surface terrain, without needing to extend the Boolean operator bounds all the way to the surface.
- L206 _private member_ `MeshPartition::EBooleanInsideTestMethod InsideTargetMeshTestMethod = MeshPartition::EBooleanInsideTestMethod::WindingNumber;` — `UPROPERTY(/*EditAnywhere, Category = Boolean, AdvancedDisplay*/)`
- L211 _private member_ `double TargetWindingThreshold{ 0.5 };` — `UPROPERTY(EditAnywhere, Category = Boolean, AdvancedDisplay, meta = (EditCondition = "InsideTargetMeshTestMethod == EBooleanInsideTestMethod::WindingNumber", UIMin = "0.0", UIMax = "1.0"))` — Winding number threshold to determine inside of the Target mesh, if the InsideTargetMeshTestMethod is WindingNumber
- L215 _private member_ `double ToolWindingThreshold{ 0.5 };` — `UPROPERTY(EditAnywhere, Category = Boolean, AdvancedDisplay, meta = (UIMin = "0.0", UIMax = "1.0"))` — Winding number threshold to determine the inside of the tool mesh.
- L219 _private member_ `bool bSimplifyAlongNewEdges{ true };` — `UPROPERTY(EditAnywhere, Category = Boolean)` — Apply simplification of newly introduced edges at mesh boundaries.
- L223 _private member_ `bool bWeldSharedEdges{ true };` — `UPROPERTY(EditAnywhere, Category = Boolean, AdvancedDisplay)` — Whether to weld newly-created cut edges where the input meshes meet.
- L233 _private member_ `FVector3d ExpandSectionInclusionBounds{ 100.,100.,100. };` — `UPROPERTY(EditAnywhere, Category = Boolean, meta = (ClampMin = "0.0", UIMax = "100000.0"))` — Amount to expand the global bounds defining which sections the modifier may write to. Use this to artificially extend the modifier bounds when it does not overlap any input sections, to make sure that it will find a section to write to. Note: Expanding these bounds will not expand the amount of geometry the Boolean operator sees or affects.
- L240 _private member_ `FVector3d ExpandOperatorBounds{ 100.,100.,100. };` — `UPROPERTY(EditAnywhere, Category = Boolean, meta = (UIMin = "0.0", UIMax = "10000.0"))` — Amount to expand the global Boolean operation bounds beyond the tool mesh bounds. Use this to expand the amount of terrain geometry that can be directly used in the Boolean operation.
- L244 _private member_ `bool bDrawLocalBounds{ true };` — `UPROPERTY(EditAnywhere, Category = "Modifier|Visualization")`
- L247 _private member_ `bool bDrawWorldBounds{ true };` — `UPROPERTY(EditAnywhere, Category = "Modifier|Visualization")`
- L250 _private member_ `bool bDrawWireMesh{ true };` — `UPROPERTY(EditAnywhere, Category = "Modifier|Visualization")`
- L253 _private member_ `EMegaMeshBooleanModifierPreviewVisOptions DrawSolidMesh = EMegaMeshBooleanModifierPreviewVisOptions::WhenTemporarilyDisabled;` — `UPROPERTY(EditAnywhere, Category = "Modifier|Visualization")`
- L256 _private member_ `TObjectPtr<UDynamicMeshComponent> ToolPreviewComponent = nullptr;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionEditableModifierBase.h` (Public)


#### class `UE::MeshPartition::UEditableModifierBase`  
`class UEditableModifierBase : public MeshPartition::UModifierComponent`  
_L17-59_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `MeshPartition::UModifierComponent`
- desc: A base class for modifiers that want to support direct editing via a tool target
- L23 _public function_ `UEditableModifierBase()`
- L26 _public function_ `virtual bool SupportsToolEditing() const` — Whether to allow tools to launch and edit this modifier
- L33 _public function_ `virtual void ApplyEditWithMesh(const FDynamicMesh3& UpdatedMesh)` — Update the modifier using the updated mesh
- L38 _public function_ `virtual void PrepareForEdit(FDynamicMesh3& EditMesh) const` — Apply any custom, modifier-specific initialization to the extracted mesh before launching tooling to edit it
- L46 _public function_ `virtual TArray<Geometry::FOrientedBox3d> GetBoundsForEdit() const` — Bounds to use for editing the modifier. As opposed to ComputeBounds, these bounds are oriented to allow edited modifiers to more tightly fit their shape. This is especially important for the tools to generate a nice preview. Note: Is allowed to differ from ComputeBounds

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MeshPartition` (scope `UE`)
- L51 _function_ `` (scope `UE::MeshPartition::UEditableModifierBase::GetBoundsForEdit`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionInstancedPatchModifier.h` (Public)


#### class `UE::MeshPartition::UInstancedPatchModifier`  
`class UInstancedPatchModifier : public MeshPartition::UPatchModifier , public ICodeReusableModifier`  
_L26-70_
- reflection: `UCLASS(MinimalAPI, PrioritizeCategories = ("Modifier", "Patch"), meta = (MegaMeshClassVersion = "1"))`
- inherits: `MeshPartition::UPatchModifier,ICodeReusableModifier`
- desc: Variant of the MeshPartition::UPatchModifier which supports multiple instances of the same parameter with different instance locations, to be used with PCG. Instanced patches are approximately as fast to compute as non-instanced patches, but it is substantially faster to add/remove individual instances.
- L32 _public prototype_ `UInstancedPatchModifier();`
- L35 _public prototype_ `virtual void SetDisabledByCode(bool bDisabledByCode) override;` — ICodeReusableModifier
- L36 _public prototype_ `virtual void ResetForReuse() override;`
- L37 _public prototype_ `virtual bool IsUsed() const override;`
- L40 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L41 _public prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;`
- L42 _public prototype_ `virtual FGuid GetCodeVersionKey() const override;`
- L43 _public prototype_ `virtual bool IsTemporarilyDisabledInEditor() const override;`
- L46 _public prototype_ `void AddInstances(const TArray<FVector>& InNewInstances);`
- L47 _public prototype_ `void ClearInstances();`
- L48 _public function_ `int32 NumInstances() const`
- L54 _protected prototype_ `FVector GetInstanceWorldspaceLocation(int InInstanceID) const;` — @return Position of instance in worldspace
- L56 _protected prototype_ `FBox GetInstanceWorldspaceBounds(int InInstanceID) const;` — @return Bounds of instance in worldspace
- L58 _protected prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const override;`
- L63 _private member_ `TArray<FVector> Instances;` — `UPROPERTY()` — Instance positions in this component's local space
- L66 _private member_ `mutable TSharedPtr<const TArray<FVector>> InstancesForBackgroundOp;` — Cached to avoid copying array on each CreateBackgroundOp when instances have not actually changed.
- L69 _private member_ `bool bDisabledByCode = false;` — See ICodeReusableModifier::SetDisabledByCode

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshPartition` (scope `UE`)
- L15 _namespace_ `namespace MegaMeshInstancedPatchModifierLocals` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionInstancedProjectionModifier.h` (Public)


#### struct `UE::MeshPartition::FInstancedProjectionModifierInstance`  
`struct FInstancedProjectionModifierInstance`  
_L21-40_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data needed for an instance of the mesh projection modifier.
- L26 _public member_ `TObjectPtr<const UDynamicMesh> Mesh = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Projection)`
- L29 _public member_ `FTransform MeshToWorld = FTransform::Identity;` — `UPROPERTY(VisibleAnywhere, Category = Projection)`
- L37 _public member_ `FTransform ProjectionToWorld = FTransform::Identity;` — `UPROPERTY(VisibleAnywhere, Category = Projection)` — Determines the direction in which projection is done. The projection is done to a point raycasted in the negative Z direction of this transform, and only vertices inside ProjectionSpaceBounds (which is given in the projection space) are modified.
- L39 _public member_ `FBox ProjectionSpaceBounds;` — `UPROPERTY(VisibleAnywhere, Category = Projection)`

#### class `UE::MeshPartition::UInstancedProjectionModifier`  
`class UInstancedProjectionModifier : public MeshPartition::UModifierComponent , public ICodeReusableModifier`  
_L47-125_
- reflection: `UCLASS(MinimalAPI, PrioritizeCategories = ("Modifier", "Settings"))`
- inherits: `MeshPartition::UModifierComponent,ICodeReusableModifier`
- desc: Modifier that takes meshes and projects the megamesh to them, capable of holding multiple projection instances at once so that a new component doesn't have to be created for each one in PCG.
- L53 _public prototype_ `UInstancedProjectionModifier();`
- L56 _public prototype_ `virtual void SetDisabledByCode(bool bDisabledByCode) override;` — ICodeReusableModifier
- L57 _public prototype_ `virtual void ResetForReuse() override;`
- L58 _public prototype_ `virtual bool IsUsed() const override;`
- L61 _public prototype_ `virtual void InitializeModifier() override;` — MeshPartition::UModifierComponent
- L62 _public prototype_ `virtual void UninitializeModifier() override;`
- L63 _public prototype_ `[[nodiscard]] virtual TArray<FBox> ComputeBounds() const override;`
- L64 _public prototype_ `TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const;`
- L65 _public prototype_ `virtual void DrawVisualization(const FSceneView* View, FPrimitiveDrawInterface* PDI) const;`
- L66 _public prototype_ `virtual FGuid GetCodeVersionKey() const override;`
- L67 _public prototype_ `virtual bool IsTemporarilyDisabledInEditor() const;`
- L70 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject
- L72 _public prototype_ `virtual void PreEditChange(FEditPropertyChain& PropertyAboutToChange) override;`
- L73 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L80 _public prototype_ `void AddInstance(const MeshPartition::FInstancedProjectionModifierInstance& NewInstance, bool bUpdateCachedMesh);` — @param bUpdateCachedMesh If true, then any existing cached version of the provided mesh will be updated. This can be set to false when adding multiple instances in a row that share the same mesh, to avoid recreating the cached data each time.
- L81 _public prototype_ `void ClearInstances();`
- L82 _public function_ `int32 NumInstances() const`
- L83 _public prototype_ `const MeshPartition::FInstancedProjectionModifierInstance* GetInstanceAtIndex(int32 Index) const;`
- L86 _private prototype_ `bool CreateCachedData(const UDynamicMesh* MeshKey, bool bUpdateIfExisting);`
- L87 _private prototype_ `UDynamicMesh* GetOrCreateMeshCopy(const UDynamicMesh* MeshKey);`
- L89 _private prototype_ `void OnCurveChanged(UCurveBase* Curve, EPropertyChangeType::Type ChangeType);`
- L90 _private prototype_ `void AttachCurveListeners();`
- L91 _private prototype_ `void DetachCurveListeners();`
- L95 _private member_ `TArray<MeshPartition::FInstancedProjectionModifierInstance> Instances;` — `UPROPERTY(VisibleAnywhere, Category = Settings)`
- L98 _private member_ `bool bDrawAffectedBox = true;` — `UPROPERTY(EditAnywhere, Category = Settings, AdvancedDisplay)`
- L101 _private member_ `bool bDrawGlobalBounds = true;` — `UPROPERTY(EditAnywhere, Category = Settings, AdvancedDisplay)`
- L104 _private member_ `MeshPartition::EProjectModifierBlendMode BlendMode = MeshPartition::EProjectModifierBlendMode::Set;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L107 _private member_ `MeshPartition::FProjectModifierFalloffSettings HeightFalloff;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L110 _private member_ `TArray<FProjectModifierWeightEntry> WeightChannels;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L113 _private member_ `TMap<const UDynamicMesh*, TSharedPtr<const Geometry::FDynamicMesh3>> ThreadSafeMeshCopies;` — Updated by CreateCachedData. Key is our own copy of a mesh.
- L114 _private member_ `TMap<const UDynamicMesh*, TSharedPtr<const Geometry::FDynamicMeshAABBTree3>> MeshSpatials;`
- L119 _private member_ `TMap<const UDynamicMesh*, TWeakObjectPtr<UDynamicMesh>> SourceMeshToInstanceMesh;` — Updated by GetOrCreateMeshCopy. Key is a mesh provided to us in AddInstance. We make copies of any meshes passed to us, and this lets us avoid making duplicate copies. Note: on load, this will no longer be initialized, so we would start making copies if we added the same meshes. It's unclear whether this is worth dealing with.
- L122 _private member_ `bool bDisabledByCode = false;` — See ICodeReusableModifier::SetDisabledByCode

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionInstancedTexturePatchModifier.h` (Public)


#### class `UE::MeshPartition::UInstancedTexturePatchModifier`  
`class UInstancedTexturePatchModifier : public MeshPartition::UTexturePatchModifier , public ICodeReusableModifier`  
_L15-51_
- reflection: `UCLASS(MinimalAPI, PrioritizeCategories = ("Modifier", "HeightDisplacement", "WeightChannels", "AdaptiveTessellation", "Instance"), meta = (BlueprintSpawnableComponent, MegaMeshClassVersion = "1"))`
- inherits: `MeshPartition::UTexturePatchModifier,ICodeReusableModifier`
- L20 _public prototype_ `UInstancedTexturePatchModifier();`
- L23 _public prototype_ `virtual void SetDisabledByCode(bool bDisabledByCode) override;` — ICodeReusableModifier
- L24 _public prototype_ `virtual void ResetForReuse() override;`
- L25 _public prototype_ `virtual bool IsUsed() const override;`
- L28 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L29 _public prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;`
- L30 _public prototype_ `virtual FGuid GetCodeVersionKey() const override;`
- L31 _public prototype_ `virtual bool IsTemporarilyDisabledInEditor() const override;`
- L32 _public prototype_ `virtual void DrawVisualization(const FSceneView* View, FPrimitiveDrawInterface* PDI) const override;`
- L35 _public prototype_ `void AddInstances(const TArray<FVector>& InNewInstances);`
- L36 _public prototype_ `void ClearInstances();`
- L37 _public function_ `int32 NumInstances() const`
- L40 _protected prototype_ `FTransform GetInstanceWorldspaceTransform(int InInstanceID) const;`
- L42 _protected prototype_ `FBox GetInstanceWorldspaceBounds(int InInstanceID) const;` — @return Bounds of instance in worldspace
- L44 _protected prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const override;`
- L48 _private member_ `TArray<FTransform> Instances;` — `UPROPERTY(EditAnywhere, Category = Instance)`
- L50 _private member_ `bool bDisabledByCode = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionLatticeModifier.h` (Public)


#### class `UE::MeshPartition::ULatticeModifier`  
`class ULatticeModifier : public MeshPartition::UEditableModifierBase, public ILatticeStateStorage`  
_L17-103_
- reflection: `UCLASS(MinimalAPI, PrioritizeCategories = ("Modifier", "Lattice", "Interpolation"), meta = (BlueprintSpawnableComponent))`
- inherits: `MeshPartition::UEditableModifierBase,ILatticeStateStorage`
- L23 _public prototype_ `ULatticeModifier() = default;`
- L24 _public prototype_ `virtual ~ULatticeModifier() = default;`
- L29 _private prototype_ `virtual void StoreLatticePoints(const TArray<FVector3d>& LatticePoints) override;` — ILatticeStateStorage
- L30 _private prototype_ `virtual void ReadLatticePoints(TArray<FVector3d>& LatticePoints) const override;`
- L31 _private prototype_ `virtual void StoreInterpolationType(ELatticeInterpolationType Type) override;`
- L32 _private prototype_ `virtual ELatticeInterpolationType ReadInterpolationType() const override;`
- L33 _private prototype_ `virtual Geometry::FAxisAlignedBox3d GetInitialBounds() const override;`
- L34 _private prototype_ `virtual Geometry::FTransformSRT3d GetTransform() const override;`
- L35 _private prototype_ `virtual Geometry::FVector3i GetResolution() const override;`
- L36 _private prototype_ `virtual void InteractiveToolStarted() override;`
- L37 _private prototype_ `virtual void InteractiveToolShutDown() override;`
- L41 _private prototype_ `virtual void PostInitProperties() override;`
- L42 _private prototype_ `virtual void BeginDestroy() override;`
- L43 _private prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L44 _private prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L48 _private prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;` — UMegaMeshEditorActorComponent Implementation
- L49 _private prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L50 _private prototype_ `virtual void DrawVisualization(const FSceneView* View, FPrimitiveDrawInterface* PDI) const override;`
- L53 _private prototype_ `virtual void PrepareForEdit(FDynamicMesh3& EditMesh) const override;` — MeshPartition::UEditableModifierBase
- L55 _private prototype_ `void InitializeControlPoints();`
- L57 _private prototype_ `FBox ComputeLocalBounds() const;`
- L62 _private member_ `TArray<FVector3d> LatticeControlPoints;` — `UPROPERTY()` — Lattice control points
- L66 _private member_ `FVector3d Extents = FVector3d(1000, 1000, 1000);` — `UPROPERTY(EditAnywhere, Category = Lattice, meta=(EditCondition = "!bToolIsRunning", HideEditConditionToggle))` — Region affected by the lattice deformer
- L70 _private member_ `FIntVector LatticeResolution = FIntVector(5, 5, 5);` — `UPROPERTY(EditAnywhere, Category = Lattice, meta = (EditCondition = "!bToolIsRunning", HideEditConditionToggle))` — Number of lattice vertices along each axis
- L74 _private member_ `ELatticeInterpolationType InterpolationType = ELatticeInterpolationType::Linear;` — `UPROPERTY(EditAnywhere, Category = Interpolation, meta = (EditCondition = "!bToolIsRunning"))` — Whether to use linear or cubic interpolation to get new mesh vertex positions from the lattice
- L78 _private member_ `bool bDrawLocalBounds = false;` — `UPROPERTY(EditAnywhere, Category = Lattice, AdvancedDisplay)` — Whether to draw the bounding box of the undeformed lattice
- L82 _private member_ `bool bDrawLatticePoints = false;` — `UPROPERTY(EditAnywhere, Category = Lattice, AdvancedDisplay)` — Whether to draw the lattice vertices
- L85 _private member_ `Geometry::FVector3i PreviousLatticeResolution;` — Cached value of the lattice resolution property
- L86 _private member_ `FVector3d PreviousLatticeExtents;`
- L90 _private prototype_ `void ClearLattice();` — `UFUNCTION(CallInEditor, Category = Lattice)` — Delete all lattice changes and reset to initial configuration
- L94 _private prototype_ `void StartLatticeTool();` — `UFUNCTION(CallInEditor, Category = Lattice)` — Start the interactice lattice deformer tool. NOTE: Modeling Mode must be active for this to do anything
- L98 _private member_ `bool bToolIsRunning = false;` — `UPROPERTY(meta = (TransientToolProperty))` — Not user visible
- L100 _private member_ `FDelegateHandle OnEditorModeChanged;`
- L101 _private member_ `FDelegateHandle OnToolStartedDelegateHandle;`
- L102 _private member_ `FDelegateHandle OnToolEndedDelegateHandle;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionLevelInstanceAdapter.h` (Public)


#### class `UE::MeshPartition::ULevelInstanceAdapter`  
`class ULevelInstanceAdapter : public MeshPartition::UModifierComponent`  
_L20-68_
- reflection: `UCLASS(meta=(BlueprintSpawnableComponent))`
- inherits: `MeshPartition::UModifierComponent`
- desc: MeshPartition::ULevelInstanceAdapter is a MeshPartition::UModifierComponent that can be attached to a LevelInstance actor in the world to allow all UModifierComponents inside of that level instance to affect the same MegaMesh that the adapter is set to affect.
- L25 _public prototype_ `ULevelInstanceAdapter();`
- L26 _public prototype_ `~ULevelInstanceAdapter();`
- L29 _public prototype_ `virtual void PreEditChange(FProperty* InPropertyAboutToChange) override;` — UObject Implementation
- L30 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L34 _public prototype_ `virtual void OnRegister() override;` — UActorComponent Implementation
- L35 _public prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L39 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L40 _public prototype_ `virtual TArray<MeshPartition::UModifierComponent*> GetInteractiveProxies() override;`
- L41 _public prototype_ `virtual void OnChanged(TConstArrayView<const FBox> InBoundingBoxes, EChangeType InChangeType);`
- L44 _protected prototype_ `void FixupModifiersInLevelInstance();`
- L45 _protected prototype_ `void FixupModifierInstance(MeshPartition::UModifierComponent* InModifier);`
- L52 _protected prototype_ `void OnLevelAdded(ULevel* InLevel, UWorld* InWorld);` — Called by the engine when a new level is added to the world. The adapter will check if this new level is owned by the level instance and uses this to know when the level instance is ready and streamed in.
- L59 _protected prototype_ `void OnLoadedActorAddedToLevel(AActor& InActor);` — In the case of a LevelInstance with streaming enabled, it is not sufficient to depend on LevelAdded. Each actor is loaded into the level instance independently through a sub-worldpartition so the only reliable way to fixup modifiers in those actors is individually as they stream in.
- L62 _protected prototype_ `ILevelInstanceInterface* GetOwningLevelInstance() const;` — Returns the owning level instance actor, or null if this component was incorrectly attached to a non-levelinstance.
- L64 _protected prototype_ `void ForEachModifierInLevelInstance(TFunctionRef<void(MeshPartition::UModifierComponent*)> InOp) const;`
- L67 _private member_ `TSet<MeshPartition::UModifierComponent*> OwnedModifiers;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionMeshBasedModifierBase.h` (Public)


#### class `UE::MeshPartition::FAsyncMeshInstanceData`  
`class FAsyncMeshInstanceData`  
_L26-81_
- L29 _public function_ `FAsyncMeshInstanceData(FDynamicMesh3 InMesh) : Mesh(MakeShared<FDynamicMesh3>(MoveTemp(InMesh))) , AABBTree(Mesh, [](const FDynamicMesh3& InMesh) { TRACE_CPUPROFILER_EVENT_SCOPE(FAsyncMeshInstanceData::BuildAABBTree); return Geometry::FDynamicMeshAABBTree3(&InMesh); }) , MeshHash(Mesh, [](const FDynamicMesh3& InMesh) { TRACE_CPUPROFILER_EVENT_SCOPE(FAsyncMeshInstanceData::ComputeMeshHash); MeshPartition::Utils::FHashArchive HashArchive; HashArchive += InMesh; return HashArchive.GetGuidFromHash(); })`
- L32 _public function_ ``
- L47 _public function_ `UE::Geometry::FAxisAlignedBox3d GetBounds() const`
- L56 _public function_ `UE::Tasks::FTask GetAsyncInitTask() const`
- L61 _public function_ `const FDynamicMesh3& GetMesh() const`
- L66 _public function_ `const UE::Geometry::FDynamicMeshAABBTree3& GetAABBTree() const`
- L71 _public function_ `const FGuid& GetHash() const`
- L77 _private member_ `TSharedRef<const FDynamicMesh3> Mesh;`
- L79 _private member_ `MeshPartition::Utils::TAsyncTransform<UE::Geometry::FDynamicMeshAABBTree3> AABBTree;`
- L80 _private member_ `MeshPartition::Utils::TAsyncTransform<FGuid> MeshHash;`

#### enum `UE::MeshPartition::EModifierMeshSourceMode`  
`enum class EModifierMeshSourceMode : uint8`  
_L85-89_
- reflection: `UENUM(BlueprintType)`
- L87 _public enumerator_ `DynamicMeshComponent`
- L88 _public enumerator_ `StaticMesh`

#### class `UE::MeshPartition::UMeshBasedModifierBase`  
`class UMeshBasedModifierBase : public MeshPartition::UModifierComponent`  
_L98-184_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `MeshPartition::UModifierComponent`
- desc: A helper base class for modifiers that want to use a mesh that a user sets using the detail panel. If a class doesn't use the detail panel to set the mesh, it should not need to use this base class, but it could use MeshPartition::UMeshBasedModifierBase::FMeshInstanceData to hold data about mesh instances.
- L113 _public prototype_ `UMeshBasedModifierBase();`
- L116 _public prototype_ `virtual void InitializeModifier() override;` — MeshPartition::UModifierComponent
- L117 _public function_ `virtual UE::Tasks::FTask GetAsyncPrepareResourcesTask() const override`
- L120 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject
- L121 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L122 _public prototype_ `virtual void PostEditUndo() override;`
- L124 _public prototype_ `virtual bool SetMeshComponent(UDynamicMeshComponent* DynamicMeshComponent);`
- L126 _public prototype_ `virtual void SetMeshSourceMode(const MeshPartition::EModifierMeshSourceMode InModifierMeshSourceMode);`
- L127 _public prototype_ `virtual MeshPartition::EModifierMeshSourceMode GetMeshSourceMode() const;`
- L129 _public prototype_ `virtual void SetStaticMesh(UStaticMesh* InStaticMesh);`
- L130 _public prototype_ `virtual UStaticMesh* GetStaticMesh() const;`
- L134 _private prototype_ `static bool CopyDynamicMeshComponent(const UDynamicMeshComponent* MeshComponent, bool bWantAttributes, FDynamicMesh3& OutMesh);`
- L136 _private prototype_ `static bool CopyStaticMesh(const UStaticMesh* StaticMesh, EMeshLODIdentifier DesiredLOD, bool bWantAttributes, FDynamicMesh3& OutMesh);`
- L140 _private member_ `MeshPartition::EModifierMeshSourceMode MeshSourceMode = MeshPartition::EModifierMeshSourceMode::DynamicMeshComponent;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L144 _private member_ `TObjectPtr<UStaticMesh> StaticMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = Mesh, Meta = ( EditCondition = "MeshSourceMode == EModifierMeshSourceMode::StaticMesh", EditConditionHides))`
- L147 _private prototype_ `void BP_SetStaticMesh(UStaticMesh* Mesh);` — `UFUNCTION(BlueprintCallable, Category = "Mesh Partition Modifier", meta=(DisplayName="Set Static Mesh"))`
- L156 _private member_ `int32 DesiredLOD = -1;` — `UPROPERTY(EditAnywhere, Category = Mesh, AdvancedDisplay, Meta = (ClampMin = -1, ClampMax = 7, EditCondition = "MeshSourceMode == EModifierMeshSourceMode::StaticMesh", EditConditionHides))` — Level of detail of the mesh to use. Currently only supports non-auto-generated LODs. Negative one indicates highest quality LOD (including HiRes, if available). If chosen LOD does not exist or is auto generated, next available LOD is used.
- L161 _private member_ `FComponentReference MeshComponent;` — `UPROPERTY(EditInstanceOnly, Category = Mesh, Meta = (UseComponentPicker, AllowAnyActor, AllowedClasses = "/Script/GeometryFramework.DynamicMeshComponent", EditCondition = "MeshSourceMode == EModifierMeshSourceMode::DynamicMeshComponent", EditConditionHides))`
- L165 _private member_ `TWeakObjectPtr<UDynamicMeshComponent> UpdatingDynamicMeshComponent = nullptr;` — `UPROPERTY()` — Weak pointer to the mesh component which has its update event linked to this modifier (if any)
- L167 _private prototype_ `void OnDynamicMeshChanged(UDynamicMeshComponent*);`
- L169 _private prototype_ `EMeshLODIdentifier GetDesiredLOD() const;`
- L171 _protected member_ `TSharedPtr<FAsyncMeshInstanceData> MeshInstance;`
- L173 _protected prototype_ `void UpdateMeshInstance();`
- L175 _protected member_ `bool bKeepInternalMeshAttributes = false;`
- L178 _protected function_ `virtual void ProcessMeshInstance(FDynamicMesh3& InstanceDataOut)` — Apply any post-processing and compute derived data (including Spatial and MeshBounds) after a mesh instance is created/updated
- L181 _protected function_ `virtual void PostUpdateMeshInstance(const FDynamicMesh3&)` — Called after Mesh Instance has been updated (changed or cleared)
- L183 _protected prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& DependencyContext) const override;`

#### struct `UE::MeshPartition::UMeshBasedModifierBase::FMeshInstanceData`  
`struct FMeshInstanceData`  
_L105-111_
- desc: Encapsulates information one would want for a mesh-based modifier, so that a single modifier component could potentially manage multiple instances at once.
- L107 _public member_ `TSharedPtr<Geometry::FDynamicMesh3> Mesh;`
- L108 _public member_ `TSharedPtr<Geometry::FDynamicMeshAABBTree3> Spatial;`
- L109 _public member_ `TSharedPtr<Geometry::FAxisAlignedBox3d> MeshBounds;`
- L110 _public member_ `FGuid MeshHash;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Geometry` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionMeshProjectModifier.h` (Public)


#### class `UE::MeshPartition::UMeshProjectModifier`  
`class UMeshProjectModifier : public MeshPartition::UMeshBasedModifierBase`  
_L19-152_
- reflection: `UCLASS(MinimalAPI, PrioritizeCategories = ("Modifier", "Mesh", "Settings", "Visualize"), meta = (BlueprintSpawnableComponent, MegaMeshClassVersion = "1"))`
- inherits: `MeshPartition::UMeshBasedModifierBase`
- L25 _public prototype_ `UMeshProjectModifier();`
- L31 _public prototype_ `void UpdateFromMesh();` — `UFUNCTION(CallInEditor, Category = Settings)` — Updates internal mesh data from given detail panel inputs
- L34 _public prototype_ `virtual void InitializeModifier() override;` — MeshPartition::UModifierComponent
- L35 _public prototype_ `virtual void UninitializeModifier() override;`
- L36 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L37 _public prototype_ `TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const;`
- L38 _public prototype_ `virtual void DrawVisualization(const FSceneView* View, FPrimitiveDrawInterface* PDI) const;`
- L39 _public prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const override;`
- L40 _public prototype_ `virtual FGuid GetCodeVersionKey() const override;`
- L44 _public prototype_ `virtual void PreEditChange(FEditPropertyChain& PropertyAboutToChange) override;`
- L45 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L85 _public prototype_ `static void ProjectOntoMesh(MeshPartition::FMeshView& MeshView, const FTransform3d& MegameshTransform, const FDynamicMesh3& ProjectionMesh, const FTransform& ProjectionMeshToWorld, const Geometry::FDynamicMeshAABBTree3& ProjectionMeshSpatial, const FTransform& ProjectionTransform, const Geometry::FAxisAlignedBox3d& ProjectionSpaceBounds, const FProjectOntoMeshOptionalParams& OptionalParams = FProjectOntoMeshOptionalParams());`
- L93 _private prototype_ `void GetProjectionTransformAndBounds(FTransform& ProjectionTransformOut, Geometry::FAxisAlignedBox3d& ProjectionSpaceBoundsOut) const;`
- L96 _private prototype_ `void OnCurveChanged(UCurveBase* Curve, EPropertyChangeType::Type ChangeType);`
- L97 _private prototype_ `void AttachCurveListeners();`
- L98 _private prototype_ `void DetachCurveListeners();`
- L104 _private member_ `float VerticalExtentUp = 10000.f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0"), AdvancedDisplay)` — How far up above the projection mesh the modifier affects megamesh vertices.
- L110 _private member_ `float VerticalExtentDown = 10000.f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0"), AdvancedDisplay)` — How far down below the projection mesh the modifier affects megamesh vertices.
- L117 _private member_ `bool bUseRelativeProjectionDirection = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DisplayName = "Direction Follows Mesh"))` — When true, the projection direction is specified relative to the mesh (whose transform is the component transform). When false, the the projection direction is specified in world space, not tied to the mesh transform.
- L120 _private member_ `FRotator AbsoluteProjectionDirection;` — `UPROPERTY(EditAnywhere, Category = Settings, Meta = (EditCondition = "!bUseRelativeProjectionDirection", EditConditionHides))`
- L123 _private member_ `FRotator RelativeProjectionDirection;` — `UPROPERTY(EditAnywhere, Category = Settings, Meta = (EditCondition = "bUseRelativeProjectionDirection", EditConditionHides))`
- L126 _private member_ `MeshPartition::EProjectModifierBlendMode BlendMode = MeshPartition::EProjectModifierBlendMode::Set;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L135 _private member_ `double BlendSoftness = 0.0;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", UIMax = "1000", EditConditionHides, EditCondition = "BlendMode != EProjectModifierBlendMode::Set"))` — When using Raise or Lower blend modes, smooths the displacement in areas where the existing mesh is close to the projection mesh. Specifically, it does a smooth min/max in areas where the projection mesh is withing BlendSoftness distance of the affected mesh.
- L138 _private member_ `MeshPartition::FProjectModifierFalloffSettings HeightFalloff;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L141 _private member_ `TArray<FProjectModifierWeightEntry> WeightChannels;` — `UPROPERTY(EditAnywhere, Category = Settings, Meta = (ShowOnlyInnerProperties))`
- L144 _private member_ `bool bDrawLocalBounds = true;` — `UPROPERTY(EditAnywhere, Category = Visualize, AdvancedDisplay)`
- L151 _private member_ `bool bDrawProjectionRectangle = true;` — `UPROPERTY(EditAnywhere, Category = Visualize, AdvancedDisplay)` — Draws a rectangle cross section of the affected box at the component location. Note that the size is determined by the size of the mesh, so this is not shown if the mesh is not set.

#### struct `UE::MeshPartition::UMeshProjectModifier::FFalloffParams`  
`struct FFalloffParams`  
_L47-55_
- L49 _public prototype_ `void Initialize(const MeshPartition::FProjectModifierFalloffSettings& Settings);`
- L51 _public member_ `Utils::ERectangleFalloffMode Mode = Utils::ERectangleFalloffMode::Smooth;`
- L52 _public member_ `float Distance = 0;`
- L53 _public member_ `double CornerRadius = 0;`
- L54 _public member_ `TSharedPtr<const FRichCurve> FalloffCurve = nullptr;`

#### struct `UE::MeshPartition::UMeshProjectModifier::FWeightEntryParams`  
`struct FWeightEntryParams`  
_L57-70_
- L59 _public prototype_ `void Initialize(const FProjectModifierWeightEntry& Entry);`
- L61 _public member_ `FName WeightChannelName;`
- L63 _public member_ `MeshPartition::EProjectModifierChannelSourceMode SourceMode = MeshPartition::EProjectModifierChannelSourceMode::VertexColor;`
- L64 _public member_ `FName SourceWeightChannelName;`
- L65 _public member_ `int32 VertexColorIndex = 0;`
- L67 _public member_ `MeshPartition::EProjectModifierBlendMode BlendMode;`
- L68 _public member_ `TOptional<FFalloffParams> FalloffOverrides;`
- L69 _public member_ `TOptional<double> HeightMinMaxBlendDistance;`

#### struct `UE::MeshPartition::UMeshProjectModifier::FProjectOntoMeshOptionalParams`  
`struct FProjectOntoMeshOptionalParams`  
_L72-83_
- L76 _public function_ `FProjectOntoMeshOptionalParams()`
- L78 _public member_ `MeshPartition::EProjectModifierBlendMode BlendMode = MeshPartition::EProjectModifierBlendMode::Set;`
- L79 _public member_ `double BlendSoftnessInProjectionSpace = 0;`
- L80 _public member_ `FFalloffParams FalloffSettings;`
- L82 _public member_ `TArray<FWeightEntryParams> WeightEntries;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionMeshProvider.h` (Public)


#### class `UE::MeshPartition::UMeshProviderModifier`  
`class UMeshProviderModifier : public MeshPartition::UModifierComponent`  
_L28-92_
- reflection: `UCLASS(MinimalAPI, meta = (BlueprintSpawnableComponent, MegaMeshClassVersion = "1"))`
- inherits: `MeshPartition::UModifierComponent`
- desc: This is a Base modifier aimed to be used on a MegaMesh. MeshPartition::UMeshProviderModifier is holding a dynamic mesh which is intended to be used as a first layer.
- L33 _public prototype_ `UMeshProviderModifier();`
- L38 _public prototype_ `const FDynamicMesh3* GetMesh() const;` — Gets the internal mesh.
- L44 _public prototype_ `void SetMesh(FDynamicMesh3&& InDynamicMesh, bool bEmitChange = false);` — Sets the internal mesh. @param bEmitChange If true, an undo/redo transaction is issued for the operation.
- L49 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreviewSectionReassignment, UMeshProviderModifier*, MeshPartition::APreviewSection* Section);` — Gives a delegate that is fired if the base section's preview section is reassigned (due to a rebuild). This is useful, for example, if you want to continue suppressing the visibility of a base section's output.
- L50 _public function_ `FOnPreviewSectionReassignment& OnPreviewSectionReassignment()`
- L53 _public prototype_ `virtual void OnRegister() override;` — UActorComponent Implementation
- L57 _public prototype_ `virtual void PostLoad() override;` — UObject, needed to fixup missing RF_Transactional flags
- L60 _public prototype_ `virtual void InitializeModifier() override;` — MeshPartition::UModifierComponent Implementation
- L61 _public prototype_ `virtual void UninitializeModifier() override;`
- L62 _public prototype_ `virtual void SetPreviewSection(MeshPartition::APreviewSection* InPreviewSection) override;`
- L63 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L64 _public prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;`
- L65 _public prototype_ `virtual double GetComplexity() const override;`
- L66 _public prototype_ `virtual void SetIsTemporarilyHiddenInEditor(const bool bInIsHidden) override;`
- L67 _public prototype_ `virtual void DrawVisualization(const FSceneView* View, FPrimitiveDrawInterface* PDI) const override;`
- L68 _public function_ `virtual bool IsBase() const override`
- L72 _public prototype_ `void SetMaterial(int32 InElementIndex, UMaterialInterface* InMaterial);` — Used to forward SetMaterial to the internal dynamic mesh.
- L76 _protected prototype_ `void OnDynamicMeshChanged();` — Called when the internal dynamic mesh changed. Will call MeshPartition::UModifierComponent::OnChanged.
- L77 _protected prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const override;`
- L81 _private member_ `TObjectPtr<UDynamicMeshComponent> MeshComponent;` — `UPROPERTY()`
- L83 _private member_ `mutable TSharedPtr<const FDynamicMesh3> MeshCopyForBackgroundOps;`
- L86 _private member_ `uint64 LastFrameChanged = 0;` — todo(luc.eygasier): investigate why OnMeshChanged event is always fired twice.
- L88 _private member_ `FOnPreviewSectionReassignment OnPreviewSectionReassignmentDelegate;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L17 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MeshPartition` (scope `UE`)
- L49 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreviewSectionReassignment, UMeshProviderModifier*, MeshPartition::APreviewSection* Section);` — Gives a delegate that is fired if the base section's preview section is reassigned (due to a rebuild). This is useful, for example, if you want to continue suppressing the visibility of a base section's output.

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionNoiseModifier.h` (Public)


#### enum `UE::MeshPartition::EFBMMode`  
`enum class EFBMMode : uint8`  
_L18-34_
- reflection: `UENUM()`
- L23 _public enumerator_ `Standard` — Classic Perlin Noise
- L28 _public enumerator_ `Turbulent` — Turbulent Modifier, creating upward bumps.
- L33 _public enumerator_ `Ridge` — Ridge Modifier, creating sharper creases and ridges.

#### enum `UE::MeshPartition::ENoiseModifierType`  
`enum class ENoiseModifierType : uint8`  
_L37-48_
- reflection: `UENUM()`
- L42 _public enumerator_ `FBmNoise UMETA(DisplayName = "fBM Noise")` — Fractal Brownian Motion based on Perlin Noise
- L47 _public enumerator_ `SineWave UMETA(DisplayName = "Sine Wave")` — Move vertices in spatial sine wave pattern

#### enum `UE::MeshPartition::ENoiseParameterization`  
`enum class ENoiseParameterization : uint8`  
_L51-60_
- reflection: `UENUM()`
- L55 _public enumerator_ `World UMETA(DisplayName = "World Space")` — Use World XY coordinates.
- L59 _public enumerator_ `Patch UMETA(DisplayName = "Patch Space")` — Use Patch XY coordinates.

#### class `UE::MeshPartition::UNoiseModifier`  
`class UNoiseModifier : public MeshPartition::UModifierComponent`  
_L66-167_
- reflection: `UCLASS(MinimalAPI, PrioritizeCategories = ("Modifier", "Noise", "NoiseTransform", "Channels"), meta = (BlueprintSpawnableComponent))`
- inherits: `MeshPartition::UModifierComponent`
- desc: A simple modifier that will deform a MegaMesh by pulling all vertices within `Radius` units to the same Z position of the patch component.
- L71 _public prototype_ `UNoiseModifier();`
- L74 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L75 _public prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;`
- L77 _public prototype_ `virtual void DrawVisualization(const FSceneView* View, FPrimitiveDrawInterface* PDI) const override;`
- L78 _public prototype_ `virtual FGuid GetCodeVersionKey() const override;`
- L81 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject
- L84 _private function_ `Geometry::FAxisAlignedBox3d GetLocalCoverage() const`
- L91 _private member_ `FVector3d UnscaledCoverage = FVector3d(2000., 2000., 50000.);` — `UPROPERTY(EditAnywhere, Category = NoiseTransform, meta = (UIMin = "0", ClampMin = "0", AllowPreserveRatio = true))` — XY-Region in which the modifier applies noise, centered at modifier location. It will be transformed by the component transform.
- L95 _private member_ `MeshPartition::ENoiseParameterization ParametrizationType = MeshPartition::ENoiseParameterization::World;` — `UPROPERTY(EditAnywhere, Category = NoiseTransform, meta = (DisplayName = "Parametrization"))` — Determines which coordinates to feed into the noise function.
- L99 _private member_ `FVector2D NoiseTranslate{ 0., 0. };` — `UPROPERTY(EditAnywhere, Category = NoiseTransform)` — 2D Translation applied to noise coordinates.
- L103 _private member_ `FVector2D NoiseFrequency{ 0.001, 0.001 };` — `UPROPERTY(EditAnywhere, Category = NoiseTransform, meta = (AllowPreserveRatio = true))` — 2D Frequency multiplier applied to noise coordinates.
- L107 _private member_ `double NoiseRotation{ 0. };` — `UPROPERTY(EditAnywhere, Category = NoiseTransform, meta = (UIMin = "0.0", UIMax = "360.0"))` — 2D Rotation applied to noise coordinates.
- L111 _private member_ `MeshPartition::ENoiseModifierType DisplacementType = MeshPartition::ENoiseModifierType::FBmNoise;` — `UPROPERTY(EditAnywhere, Category = Noise, meta = (DisplayName = "Noise Type"))` — Displacement type
- L115 _private member_ `MeshPartition::EFBMMode FBMMode { MeshPartition::EFBMMode::Standard };` — `UPROPERTY(EditAnywhere, Category = Noise, meta = (EditConditionHides, EditCondition = "DisplacementType == ENoiseModifierType::FBmNoise"))` — Noise modification control.
- L119 _private member_ `double Intensity { 1. };` — `UPROPERTY(EditAnywhere, Category = Noise)` — Amplitude of the noise function.
- L123 _private member_ `double Falloff { 0.5 };` — `UPROPERTY(EditAnywhere, Category = Noise, meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Controls the amount of smooth falloff towards the boundary of the control region.
- L130 _private member_ `int FBMOctaves{ 4 };` — `UPROPERTY(EditAnywhere, Category = Noise, meta = (UIMin = "1", UIMax = "8", ClampMin = "1", ClampMax = "16", EditConditionHides, EditCondition = "DisplacementType == ENoiseModifierType::FBmNoise"))` — Number of octaves.
- L135 _private member_ `double FBMLacunarity{ 2. };` — `UPROPERTY(EditAnywhere, Category = Noise, meta = (UIMin = "1.0", ClampMin="1.0", EditConditionHides, EditCondition = "DisplacementType == ENoiseModifierType::FBmNoise"))` — Multplier applied to frequency when going to finer octave.
- L140 _private member_ `double FBMGain{ 0.5 };` — `UPROPERTY(EditAnywhere, Category = Noise, meta = (UIMin = "0.1", UIMax = "1.0", ClampMin = "0.1", ClampMax = "1.0", EditConditionHides, EditCondition = "DisplacementType == ENoiseModifierType::FBmNoise"))` — Multplier applied to amplitude when going to finer octave.
- L145 _private member_ `double FBMSmoothness{ 0.02 };` — `UPROPERTY(EditAnywhere, Category = Noise, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditConditionHides, EditCondition = "DisplacementType == ENoiseModifierType::FBmNoise"))` — Smoothness control applied to Turbulent and Ridge modes.
- L150 _private member_ `double FBMGamma{ 2.0 };` — `UPROPERTY(EditAnywhere, Category = Noise, meta = (UIMin = "0.5", UIMax = "4.0", ClampMin = "0.2", ClampMax = "16.0", EditConditionHides, EditCondition = "DisplacementType == ENoiseModifierType::FBmNoise"))` — Gamma control applied to Turbulent and Ridge modes.
- L153 _private member_ `bool bWriteToWeightChannel = false;` — `UPROPERTY(EditAnywhere, Category=Channels)`
- L157 _private member_ `MeshPartition::FChannelName WeightChannelName;` — `UPROPERTY(EditAnywhere, Category=Channels, meta = (GetOptions = "GetMegaMeshDefinitionChannels", NoResetToDefault, EditCondition = "bWriteToWeightChannel"))`
- L161 _private member_ `bool bDrawPatchRectangle = true;` — `UPROPERTY(EditAnywhere, Category = Visualization, AdvancedDisplay)` — When true, draws a red rectangle showing patch area in editor.
- L165 _private member_ `bool bDrawAffectedBox = true;` — `UPROPERTY(EditAnywhere, Category = Visualization, AdvancedDisplay)` — When true, draws a box showing affected volume in editor.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionPatchModifier.h` (Public)


#### class `UE::MeshPartition::UPatchModifier`  
`class UPatchModifier : public MeshPartition::UModifierComponent`  
_L27-96_
- reflection: `UCLASS(MinimalAPI, PrioritizeCategories = ("Modifier", "Patch"), meta=(BlueprintSpawnableComponent, MegaMeshClassVersion = "1"))`
- inherits: `MeshPartition::UModifierComponent`
- desc: A simple modifier that will deform a MegaMesh by pulling all vertices within `Radius` units to the same Z position of the patch component.
- L32 _public prototype_ `UPatchModifier();`
- L35 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L36 _public prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;`
- L37 _public prototype_ `virtual FGuid GetCodeVersionKey() const override;`
- L41 _public prototype_ `void SetRadius(float InRadius);`
- L42 _public prototype_ `void SetFalloff(float InFalloff);`
- L43 _public prototype_ `void SetMaxZDistance(float InMaxZDistance);`
- L44 _public prototype_ `void SetWriteToWeightChannel(bool bInWriteToWeightChannel);`
- L45 _public prototype_ `void SetWeightChannelName(FName InWeightChannelName);`
- L47 _public function_ `float GetRadius() const`
- L48 _public function_ `float GetFalloff() const`
- L49 _public function_ `float GetMaxZDistance() const`
- L50 _public function_ `bool ShouldWriteToWeightChannel() const`
- L51 _public function_ `FName GetWeightChannelName() const`
- L54 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject
- L75 _protected prototype_ `static void ApplyDeformation(const FSettings& Settings, MeshPartition::FMeshView& InMeshView, const FVector& Location);`
- L78 _protected prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const override;`
- L82 _protected member_ `float Radius = 1000.f;` — `UPROPERTY(EditAnywhere, Category=Patch)` — Radius around the patch component's location that is affected by the patch
- L85 _protected member_ `float Falloff = 1000.f;` — `UPROPERTY(EditAnywhere, Category=Patch)`
- L88 _protected member_ `float MaxZDistance = 20000.f;` — `UPROPERTY(EditAnywhere, Category=Patch)`
- L91 _protected member_ `bool bWriteToWeightChannel = false;` — `UPROPERTY(EditAnywhere, Category=Patch)`
- L95 _protected member_ `MeshPartition::FChannelName WeightChannelName;` — `UPROPERTY(EditAnywhere, Category = Patch, Meta = (EditCondition = "bWriteToWeightChannel", GetOptions = "GetMegaMeshDefinitionChannels"))` — When bWriteToWeightChannel is true, the channel to write to.

#### struct `UE::MeshPartition::UPatchModifier::FSettings`  
`struct FSettings`  
_L58-74_
- desc: Helper struct to package settings that are common accross MeshPartition::UPatchModifier and MeshPartition::UInstancedPatchModifier
- L60 _public function_ `FSettings()`
- L61 _public function_ `FSettings(const UPatchModifier& Patch) : Radius(Patch.Radius) , Falloff(Patch.Falloff) , MaxZDistance(Patch.MaxZDistance) , bWriteToWeightChannel(Patch.bWriteToWeightChannel) , WeightChannelName(Patch.WeightChannelName.GetName())`
- L69 _public member_ `float Radius;`
- L70 _public member_ `float Falloff;`
- L71 _public member_ `float MaxZDistance;`
- L72 _public member_ `bool bWriteToWeightChannel;`
- L73 _public member_ `FName WeightChannelName;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MeshPartition` (scope `UE`)
- L18 _namespace_ `namespace MegaMeshPatchModifierLocals` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionProjectSculptLayersModifier.h` (Public)


#### enum `UE::MeshPartition::ESculptLayerProjectMethod`  
`enum class ESculptLayerProjectMethod : uint8`  
_L27-33_
- reflection: `UENUM(BlueprintType)`
- L30 _public enumerator_ `FixedDirection` — Transfer sculpt layers by projection along a fixed direction
- L32 _public enumerator_ `ClosestPoints` — Transfer sculpt layers from the closest point on the reference mesh

#### enum `UE::MeshPartition::ESculptLayerSetWeightChannelMethod`  
`enum class ESculptLayerSetWeightChannelMethod : uint8`  
_L36-41_
- reflection: `UENUM()`
- L38 _public enumerator_ `Disabled`
- L39 _public enumerator_ `Set`
- L40 _public enumerator_ `Add`

#### struct `UE::MeshPartition::FSculptLayerModifierWeightAttributeEntry`  
`struct FSculptLayerModifierWeightAttributeEntry`  
_L44-80_
- reflection: `USTRUCT()`
- L50 _public member_ `MeshPartition::FChannelName ChannelName;` — `UPROPERTY(EditAnywhere, Category = WeightAttribute, meta = (GetOptions = "GetMegaMeshDefinitionChannels"))` — The destination attribute channel to write.
- L57 _public member_ `ESculptLayerSetWeightChannelMethod Method = ESculptLayerSetWeightChannelMethod::Set;` — `UPROPERTY(EditAnywhere, Category = WeightAttribute)` — How to apply weight channel values. Note that for an internal channel, Set and Add are equivalent.
- L64 _public member_ `float BlendWeight = 1.0f;` — `UPROPERTY(EditAnywhere, Category = WeightAttribute)` — Scale the effect of the modifier on this channel. Note that for an internal channel, this directly scales the channel values.
- L68 _public member_ `bool bScaleSculptLayers = false;` — `UPROPERTY(EditAnywhere, Category = WeightAttribute)` — Whether to use the channel weights to scale the displacement applied by sculpt layers
- L72 _public member_ `bool bClampRange = false;` — `UPROPERTY(EditAnywhere, Category = WeightAttribute)` — Whether to clamp the channel weights to the zero-to-one range
- L79 _public member_ `bool bInternalChannel = false;` — `UPROPERTY(EditAnywhere, Category = WeightAttribute, AdvancedDisplay)` — Whether to isolate this weight channel to this modifier -- and not read/write from the target mesh. For example, use this to define a channel that is solely used for scaling sculpt layers on this modifier.

#### class `UE::MeshPartition::UProjectMeshLayersModifier`  
`class UProjectMeshLayersModifier : public MeshPartition::UEditableModifierBase , public IMeshSculptLayersManager , public ICodeReusableModifier`  
_L86-287_
- reflection: `UCLASS(MinimalAPI, PrioritizeCategories=("Modifier","MeshLayers","AttributeWeights","Projection"), meta = (BlueprintSpawnableComponent, DisplayName = "BrushModifier", MegaMeshClassVersion = "1"))`
- inherits: `MeshPartition::UEditableModifierBase,IMeshSculptLayersManager,ICodeReusableModifier`
- desc: Modifier to manage layers of custom mesh detail, and project them onto a partitioned mesh
- L94 _public prototype_ `UProjectMeshLayersModifier();`
- L97 _public prototype_ `virtual void SetDisabledByCode(bool bDisabledIn) override;` — ICodeReusableModifier
- L98 _public prototype_ `virtual void ResetForReuse() override;`
- L99 _public prototype_ `virtual bool IsUsed() const override;`
- L102 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;` — MeshPartition::UModifierComponent implementation
- L103 _public prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;`
- L104 _public prototype_ `virtual void DrawVisualization(const FSceneView* View, FPrimitiveDrawInterface* PDI) const override;`
- L105 _public prototype_ `virtual void InitializeModifier() override;`
- L106 _public prototype_ `virtual FGuid GetCodeVersionKey() const override;`
- L107 _public prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const override;`
- L108 _public prototype_ `virtual bool IsTemporarilyDisabledInEditor() const override;`
- L109 _public prototype_ `virtual UE::Tasks::FTask GetAsyncPrepareResourcesTask() const override;`
- L112 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject
- L113 _public prototype_ `virtual void PostLoad() override;` — called after load
- L114 _public prototype_ `virtual void PostEditImport() override;` — called after duplicate/copy
- L117 _public prototype_ `virtual void ApplyEditWithMesh(const FDynamicMesh3& UpdatedMesh) override;` — MeshPartition::UEditableModifierBase implementation
- L118 _public prototype_ `virtual void PrepareForEdit(FDynamicMesh3& EditMesh) const override;`
- L119 _public prototype_ `virtual TArray<Geometry::FOrientedBox3d> GetBoundsForEdit() const override;`
- L122 _public function_ `virtual bool HasSculptLayers() const override` — IMeshSculptLayersManager implementation
- L126 _public function_ `virtual int32 NumLockedBaseSculptLayers() const override`
- L132 _public prototype_ `void SetSculptLayerMesh(const FDynamicMesh3& Mesh, bool bTransact);` — Call to directly set the sculpt layer mesh. Cached/dependent data will be automatically updated as well.
- L134 _public function_ `TArray<FSculptLayerModifierWeightAttributeEntry> GetChannelEntries() const`
- L137 _public function_ `void SetChannelEntries(const TArray<FSculptLayerModifierWeightAttributeEntry>& EntriesIn)` — Directly set the channels to write
- L140 _public function_ `void SetClosestPointProjection(double MaxDistance)` — Set projection method to closest point, and sets the max distance
- L148 _public function_ `void SetEditVolumeExtents(const FVector3d& EditExtentsIn)`
- L151 _public prototype_ `FName GetLayerName(const int32 LayerIndex) const;` — Return the name of the sculpt layer at the provided index
- L154 _public prototype_ `void SetLayerName(const int32 InLayerIndex, const FName InName);` — Sets the name of the layer at the provided index to the provided name
- L157 _public prototype_ `void SetLayerWeight(const int32 InLayerIndex, const double InWeight, const EPropertyChangeType::Type ChangeType);` — Sets the weight of the layer at the provided index to the provided weight
- L160 _public function_ `int32 GetActiveLayer() const` — Gets the ActiveLayer
- L162 _public prototype_ `DECLARE_MULTICAST_DELEGATE(OnMeshLayersModifierPanelRequestRebuild);`
- L163 _public member_ `OnMeshLayersModifierPanelRequestRebuild OnMeshLayersPanelRequestRebuild;`
- L171 _private prototype_ `void ClearMesh();` — `UFUNCTION(CallInEditor, Category = Mesh)` — Clear the sculpt mesh entirely
- L174 _private prototype_ `FTransform GetProjectionTransform() const;` — Get the transform of the projection operator
- L176 _private prototype_ `Geometry::FAxisAlignedBox3d GetProjectionBounds(const Geometry::FAxisAlignedBox3d& InputBounds, const FTransform& InProjectionTransform) const;` — Get the bounds of the projection operator, in projection space, from InputBounds in mesh space
- L178 _private prototype_ `Geometry::FAxisAlignedBox3d GetProjectionEditBounds() const;` — Get the bounds of the current edit extents, in projection space
- L180 _private prototype_ `void OnMeshObjectChanged(UDynamicMesh* ChangedMeshObject, FDynamicMeshChangeInfo ChangeInfo);` — Called whenever internal MeshObject is modified, fires OnMeshChanged and OnMeshVerticesChanged above
- L182 _private prototype_ `void BuildCachedData();` — Build the AABB tree and the mesh copy for the current sculpt mesh
- L184 _private prototype_ `void ComputeMaxLayerOffsets();` — Find the maximum offset values in each layer, to help quickly compute bounding boxes
- L186 _private prototype_ `int32 GetProjectionMeshNumLayers() const;` — Get the number of sculpt layers on the current sculpt mesh
- L189 _private prototype_ `virtual void OnRegister() override;` — UActorComponent override to rebuild cached data as needed -- for example, across e.g. blueprint re-running construction scripts
- L193 _private prototype_ `void ApplyMeshUpdate();`
- L197 _private member_ `FVector2D EditExtents = FVector2D(500, 500);` — `UPROPERTY(EditAnywhere, Category = MeshLayers, meta = (ClampMin = "0", DisplayName = "Edit Projected Extents", EditCondition = "ProjectMethod == ESculptLayerProjectMethod::FixedDirection", EditConditionHides))` — Size of the region to project and sculpt
- L201 _private member_ `FVector EditVolumeExtents = FVector(500, 500, 500);` — `UPROPERTY(EditAnywhere, Category = MeshLayers, meta = (ClampMin = "0", EditCondition = "ProjectMethod == ESculptLayerProjectMethod::ClosestPoints", EditConditionHides))` — Size of the region to sculpt
- L207 _private member_ `bool bDiscardUnsculpted = false;` — `UPROPERTY(EditAnywhere, Category = MeshLayers)` — If enabled, unsculpted triangles will be discarded from the projection mesh, which can make the sculpts offsets faster to apply. Note: Disabling this can help block undesired projections of the sculpt offsets on some finely-detailed or layered surfaces. Note: Currently not supported if using AttributeWeightChannels -- no triangles will be discarded in this case.
- L212 _private member_ `int32 ActiveLayer = 1;` — `UPROPERTY()` — Last layer edited/selected in tools (where 1 is the first sculpt layer, since 0 is the base) Note this is saved for persistence across edits in tools, and does not affect the modifier result
- L217 _public member_ `TArray<double> LayerWeights;` — `UPROPERTY(EditAnywhere, EditFixedSize, NoClear, Category = MeshLayers, meta = (NoResetToDefault, UIMin = "-1", UIMax = "2"))` — Weights to apply to each sculpt layer. Note the base layer is not included.
- L222 _private prototype_ `TArray<FSculptLayerModifierWeightAttributeEntry> GetActiveWeightChannels() const;` — Helper to get the 'active' weight channels that will actually be used by the modifier (e.g., w/ disabled channels filtered out)
- L227 _private member_ `bool bSculptAbsolutePositions = false;` — `UPROPERTY(EditAnywhere, Category = MeshLayers)` — Whether to transform sculpted vertices directly to corresponding positions of the reference sculpt mesh. Otherwise, only the offsets will be transferred. Note: Absolute positioning can be blended away by using Attribute Weight Channels with 'Scale Sculpt Layers' enabled
- L231 _private member_ `TArray<FSculptLayerModifierWeightAttributeEntry> AttributeWeightChannels;` — `UPROPERTY(EditAnywhere, Category = AttributeWeights, Meta = (ShowOnlyInnerProperties))` — Optionally specify attribute weight channels to be transferred
- L234 _private prototype_ `TConstArrayView<double> GetActiveLayerWeights() const;` — Return a view of the active layer weights -- i.e., SourceLayerWeights if bUseSourceLayerWeights, or LayerWeights otherwise
- L238 _private member_ `ESculptLayerProjectMethod ProjectMethod = ESculptLayerProjectMethod::FixedDirection;` — `UPROPERTY(EditAnywhere, Category = Projection)` — Method to transfer offsets to the mesh partition mesh
- L242 _private member_ `float MaxClosestPointDistance = 100;` — `UPROPERTY(EditAnywhere, Category = Projection, meta = (EditCondition = "ProjectMethod == ESculptLayerProjectMethod::ClosestPoints", EditConditionHides))` — Farthest distance to search for a closest point on the reference mesh
- L246 _private member_ `bool bUseBoundaryFalloff = true;` — `UPROPERTY(EditAnywhere, Category = Projection, meta = (EditCondition = "ProjectMethod == ESculptLayerProjectMethod::ClosestPoints", EditConditionHides))` — Whether to apply a smooth falloff of influence for vertices where the closest point is on a mesh boundary
- L251 _private member_ `float BoundaryFalloffDistanceFactor = 1;` — `UPROPERTY(EditAnywhere, Category = Projection, meta = (ClampMin = "0", UIMax = "1", EditCondition = "ProjectMethod == ESculptLayerProjectMethod::ClosestPoints && bUseBoundaryFalloff", EditConditionHides))` — The distance over which a smooth falloff is applied for vertices that map to boundary edges of the reference mesh, as a factor of Max Closest Point Distance. A value of 1 will result in a smooth falloff over the full Max Closest Point Distance range, and a value of 0 will result in offsets clamping to 0 for all vertices that map to the boundary.
- L255 _private member_ `float VerticalExtentUp = 10000.f;` — `UPROPERTY(EditAnywhere, Category = Projection, meta = (ClampMin = "0", EditCondition = "ProjectMethod == ESculptLayerProjectMethod::FixedDirection", EditConditionHides), AdvancedDisplay)` — How far up above the projection mesh the modifier affects megamesh vertices, relative to the direction of projection.
- L259 _private member_ `float VerticalExtentDown = 10000.f;` — `UPROPERTY(EditAnywhere, Category = Projection, meta = (ClampMin = "0", EditCondition = "ProjectMethod == ESculptLayerProjectMethod::FixedDirection", EditConditionHides), AdvancedDisplay)` — How far down below the projection mesh the modifier affects megamesh vertices, relative to the direction of projection.
- L263 _private member_ `bool bDrawAffectedBox = true;` — `UPROPERTY(EditAnywhere, Category = Visualize, AdvancedDisplay)` — Whether to draw the bounds of the projection
- L267 _private member_ `bool bDrawSculptSourceBounds = true;` — `UPROPERTY(EditAnywhere, Category = Visualize, AdvancedDisplay)` — Whether to draw the bounds of the source geometry that sculpt layers are transferred from (not including sculpt offsets)
- L271 _private member_ `bool bDrawDebugMesh = false;` — `UPROPERTY(EditAnywhere, Category = Visualize, AdvancedDisplay)` — Draws edges of the stored mesh for debugging
- L274 _private member_ `TArray<FVector3d> MaxLayerOffset;` — Cache of maximum offset per layer, across all modifier meshes, used to conservatively predict how much the bounds could be expanded by the modifier
- L278 _private member_ `TObjectPtr<UDynamicMesh> MeshObject;` — `UPROPERTY()` — The mesh that holds the current sculpt layers
- L281 _private member_ `FDelegateHandle MeshObjectChangedHandle;` — Handle for OnMeshObjectChanged which is registered with MeshObject::OnMeshChanged delegate
- L283 _private member_ `TSharedPtr<FAsyncMeshInstanceData> MeshInstance;`
- L286 _private member_ `bool bDisabledByCode = false;` — See ICodeReusableModifier::SetDisabledByCode

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MeshPartition` (scope `UE`)
- L162 _delegate_ `DECLARE_MULTICAST_DELEGATE(OnMeshLayersModifierPanelRequestRebuild);`
- L289 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSculptLayersModifier, Warning, All);`
- L289 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSculptLayersModifier, Warning, All);`

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionRemeshModifier.h` (Public)


#### enum `UE::MeshPartition::ERemeshModifierOperation`  
`enum class ERemeshModifierOperation : uint8`  
_L23-27_
- reflection: `UENUM()`
- L25 _public enumerator_ `Remesh`
- L26 _public enumerator_ `Tessellate`

#### class `UE::MeshPartition::URemeshModifierBase`  
`class URemeshModifierBase : public MeshPartition::UModifierComponent`  
_L33-273_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `MeshPartition::UModifierComponent`
- desc: Base class for modifiers that do Remeshing/Tessellation
- L39 _public prototype_ `URemeshModifierBase() = default;`
- L40 _public prototype_ `virtual ~URemeshModifierBase() = default;`
- L48 _public function_ `ERemeshModifierOperation GetCurrentOperation() const`
- L49 _public prototype_ `void SetCurrentOperation(const ERemeshModifierOperation InOperation);`
- L55 _public function_ `EMegaMeshRemeshModifierBoundaryMode GetBoundaryMode() const`
- L56 _public prototype_ `void SetBoundaryMode(const EMegaMeshRemeshModifierBoundaryMode InMode);`
- L58 _public function_ `bool GetDisallowUnsafeBoundaryEdits() const`
- L59 _public prototype_ `void SetDisallowUnsafeBoundaryEdits(const bool bDisallow);`
- L61 _public function_ `float GetTargetEdgeLength() const`
- L62 _public prototype_ `void SetTargetEdgeLength(const float InLength);`
- L64 _public function_ `int32 GetRemeshIterations() const`
- L65 _public prototype_ `void SetRemeshIterations(const int32 InIterations);`
- L67 _public function_ `float GetSmoothingStrength() const`
- L68 _public prototype_ `void SetSmoothingStrength(const float InStrength);`
- L70 _public function_ `ERemeshSmoothingType GetSmoothingType() const`
- L71 _public prototype_ `void SetSmoothingType(const ERemeshSmoothingType InType);`
- L73 _public function_ `bool GetPreserveNormalSeams() const`
- L74 _public prototype_ `void SetPreserveNormalSeams(const bool bPreserve);`
- L76 _public function_ `float GetSharpEdgeAngleThreshold() const`
- L77 _public prototype_ `void SetSharpEdgeAngleThreshold(const float InThreshold);`
- L79 _public function_ `bool GetProjectToInputMesh() const`
- L80 _public prototype_ `void SetProjectToInputMesh(const bool bProject);`
- L86 _public function_ `EMegaMeshRemeshModifierTessellateMethod GetTessellationMethod() const`
- L87 _public prototype_ `void SetTessellationMethod(const EMegaMeshRemeshModifierTessellateMethod InMethod);`
- L89 _public function_ `bool GetUseTargetEdgeLength() const`
- L90 _public prototype_ `void SetUseTargetEdgeLength(const bool bUse);`
- L92 _public function_ `float GetTessellationTargetEdgeLength() const`
- L93 _public prototype_ `void SetTessellationTargetEdgeLength(const float InLength);`
- L95 _public function_ `int32 GetTessellationLevel() const`
- L96 _public prototype_ `void SetTessellationLevel(const int32 InLevel);`
- L98 _public function_ `int32 GetMaxTessellationLevel() const`
- L99 _public prototype_ `void SetMaxTessellationLevel(const int32 InMaxLevel);`
- L101 _public function_ `int32 GetPostProcessingIterations() const`
- L102 _public prototype_ `void SetPostProcessingIterations(const int32 InIterations);`
- L104 _public function_ `bool GetVertexSmoothing() const`
- L105 _public prototype_ `void SetVertexSmoothing(const bool bSmoothing);`
- L107 _public function_ `float GetTessellateSmoothingStrength() const`
- L108 _public prototype_ `void SetTessellateSmoothingStrength(const float InStrength);`
- L110 _public function_ `bool GetResampleUVs() const`
- L111 _public prototype_ `void SetResampleUVs(const bool bResample);`
- L113 _public function_ `bool GetEdgeFlips() const`
- L114 _public prototype_ `void SetEdgeFlips(const bool bFlips);`
- L120 _public function_ `bool GetUseDensityWeightChannel() const`
- L121 _public prototype_ `void SetUseDensityWeightChannel(const bool bUse);`
- L123 _public function_ `const FChannelName& GetDensityWeightChannelName() const`
- L124 _public prototype_ `void SetDensityWeightChannelName(const FChannelName& InName);`
- L126 _public function_ `float GetRelativeDensity() const`
- L127 _public prototype_ `void SetRelativeDensity(const float InDensity);`
- L131 _protected prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const override;`
- L134 _protected member_ `MeshPartition::ERemeshModifierOperation CurrentOperation = MeshPartition::ERemeshModifierOperation::Remesh;` — `UPROPERTY(EditAnywhere, Category = "RemeshOperation", meta = (DisplayName = "Mode"))`
- L144 _protected member_ `EMegaMeshRemeshModifierBoundaryMode BoundaryMode = EMegaMeshRemeshModifierBoundaryMode::SplitOnly;` — `UPROPERTY(EditAnywhere, Category = Remesh, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Remesh"))` — How to treat edges on the boundary of the covered region.
- L148 _protected member_ `float TargetEdgeLength = 1000.f;` — `UPROPERTY(EditAnywhere, Category=Remesh, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Remesh", UIMin = "0.1", ClampMin = "0.1"))` — Desired average mesh edge length
- L152 _protected member_ `int32 RemeshIterations = 15;` — `UPROPERTY(EditAnywhere, Category=Remesh, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Remesh"))` — Number of remeshing passes over the whole mesh
- L156 _protected member_ `float SmoothingStrength = 0.25f;` — `UPROPERTY(EditAnywhere, Category = Remesh, meta = (DisplayName = "Smoothing Rate", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "(CurrentOperation == ERemeshModifierOperation::Remesh)"))` — How aggressively to move vertices during smoothing
- L160 _protected member_ `ERemeshSmoothingType SmoothingType = ERemeshSmoothingType::Uniform;` — `UPROPERTY(EditAnywhere, Category = Remesh, meta = (DisplayName = "Smoothing Mode", EditCondition = "CurrentOperation == ERemeshModifierOperation::Remesh"))` — Vertex smoothing scheme
- L164 _protected member_ `bool bPreserveNormalSeams = false;` — `UPROPERTY(EditAnywhere, Category = Remesh, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Remesh"))` — If true, precompute vertex normals over the mesh and mark normal discontinuities as constraints. This can help preserve sharp features of the mesh
- L168 _protected member_ `float SharpEdgeAngleThreshold = 60.0f;` — `UPROPERTY(EditAnywhere, Category = Remesh, meta = (DisplayName = "Sharp Angle Threshold", Units = Degrees, UIMin = "0.0", UIMax = "180.0", ClampMin = "0.0", ClampMax = "180.0", EditCondition = "bPreserveNormalSeams && CurrentOperation == ERemeshModifierOperation::Remesh"))` — Threshold on angle of change in face normals across an edge, above which we create a sharp edge if bPreserveNormalSeams is true
- L172 _protected member_ `bool bProjectToInputMesh = false;` — `UPROPERTY(EditAnywhere, Category = Remesh, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Remesh"))` — If true, vertices will be projected back to the input surface after each remeshing pass
- L181 _protected member_ `bool bDisallowUnsafeBoundaryEdits = true;` — `UPROPERTY(EditAnywhere, Category = Remesh, AdvancedDisplay, Meta = (EditCondition = "(BoundaryMode != EMegaMeshRemeshModifierBoundaryMode::FullyConstrained) && (CurrentOperation == ERemeshModifierOperation::Remesh)", DisplayName = "Disallow Unsafe Edits"))` — When true, the region affected by the modifier is contracted such that any edges that have neighbors outside the view that the modifier is given are not modified. This ensures that the view can be stitched back into the larger mesh properly (otherwise, potentially invisible cracks would appear in cases where a vertex was added to the boundary of the view but not the base mesh).
- L191 _protected member_ `bool bDisallowSafeEditsOutsideCoverage = false;` — `UPROPERTY(EditAnywhere, Category = Remesh, AdvancedDisplay, Meta = (EditCondition = "(BoundaryMode != EMegaMeshRemeshModifierBoundaryMode::FullyConstrained) && (CurrentOperation == ERemeshModifierOperation::Remesh)", DisplayName = "Disallow Edits Outside"))` — When true, the region affected by the modifier is contracted such that no triangles outside coverage are split. when false, some triangles that lie partially outside of the coverage but still inside the view (if the coverage is not aligned to view) are allowed to be split to allow for splits in the boundary of the fully contained region. This can safely remain false to maximize the remeshed region as long as you accept some partially-covered triangles being modified.
- L199 _protected member_ `EMegaMeshRemeshModifierTessellateMethod TessellationMethod = EMegaMeshRemeshModifierTessellateMethod::AdaptiveRegular;` — `UPROPERTY(EditAnywhere, Category = Tessellate, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Tessellate"))` — Type of tessellation to perform
- L203 _protected member_ `bool bUseTargetEdgeLength = false;` — `UPROPERTY(EditAnywhere, Category = Tessellate, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Tessellate"))` — If true, subdivide each triangle until its longest edge is shorter than TargetEdgeLength
- L207 _protected member_ `float TessellationTargetEdgeLength = 1000.f;` — `UPROPERTY(EditAnywhere, Category = Tessellate, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Tessellate && bUseTargetEdgeLength", UIMin = "0.1", ClampMin = "0.1"))` — Edge length threshold for tessellation
- L211 _protected member_ `int32 TessellationLevel = 1;` — `UPROPERTY(EditAnywhere, Category = Tessellate, meta = (EditCondition = "!bUseTargetEdgeLength && (CurrentOperation == ERemeshModifierOperation::Tessellate)", UIMin = 0, UIMax = 10, ClampMin = 0))` — Number of times to subdivide each triangle (possibly excluding triangles close to the region boundary)
- L215 _protected member_ `int32 MaxTessellationLevel = 1;` — `UPROPERTY(EditAnywhere, Category = Tessellate, meta = (EditCondition = "bUseTargetEdgeLength && (CurrentOperation == ERemeshModifierOperation::Tessellate)", UIMin = 0, UIMax = 10, ClampMin = 0))` — When using the target edge length, limit the tessellation level per triangle to this value to avoid excessive computation
- L219 _protected member_ `int32 PostProcessingIterations = 0;` — `UPROPERTY(EditAnywhere, Category = Tessellate, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Tessellate", UIMin = 0, UIMax = 40, ClampMin = 0))` — Number of  passes of mesh optimization to perform after tessellation is finished
- L223 _protected member_ `bool bVertexSmoothing = false;` — `UPROPERTY(EditAnywhere, Category = Tessellate, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Tessellate"))` — Whether to apply vertex smoothing during post-processing
- L227 _protected member_ `float TessellateSmoothingStrength = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Tessellate, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Tessellate", UIMin = 0, UIMax = 1.0, ClampMin = 0, ClampMax = 1.0))` — How aggressively to move vertices during smoothing
- L231 _protected member_ `bool bResampleUVs = false;` — `UPROPERTY(EditAnywhere, Category = Tessellate, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Tessellate"))` — Whether to resample texture coordinates from the input mesh to avoid texture distortion
- L235 _protected member_ `bool bEdgeFlips = false;` — `UPROPERTY(EditAnywhere, Category = Tessellate, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Tessellate"))` — Whether to flip edges to improve mesh quality during post-processing
- L247 _protected member_ `bool bUseDensityWeightChannel = false;` — `UPROPERTY(EditAnywhere, Category = DensityWeightChannel, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Remesh || bUseTargetEdgeLength"))` — If true, use the weights on the specified channel to modulate the relative mesh density. Where the density weight values are 0.0, the desired average edge length is TargetEdgeLength. Where density weight values are 1.0, the desired average edge length is MinTargetEdgeLength. For density weight values between 0 and 1, the desired average edge length is interpolated between TargetEdgeLength and MinTargetEdgeLength.
- L252 _protected member_ `MeshPartition::FChannelName DensityWeightChannelName;` — `UPROPERTY(EditAnywhere, Category = DensityWeightChannel, meta = (GetOptions = "GetMegaMeshDefinitionChannels", NoResetToDefault, EditCondition = "CurrentOperation == ERemeshModifierOperation::Remesh || bUseTargetEdgeLength"))` — Name of the channel used to modulate the relative mesh density
- L255 _protected member_ `float RelativeDensity = 0.f;` — `UPROPERTY(EditAnywhere, Category = DensityWeightChannel, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Remesh || bUseTargetEdgeLength", UIMin = "-2.0", UIMax = "2.0"))`
- L259 _protected member_ `bool bUseWeightThreshold = false;` — `UPROPERTY(EditAnywhere, Category = DensityWeightChannel, meta = (EditCondition = "CurrentOperation == ERemeshModifierOperation::Remesh || bUseTargetEdgeLength"))` — Whether to only change the mesh where weight values are above the MinWeightThreshold
- L263 _protected member_ `float MinWeightThreshold = 0.01f;` — `UPROPERTY(EditAnywhere, Category = DensityWeightChannel, meta = (EditCondition = "bUseWeightThreshold && (CurrentOperation == ERemeshModifierOperation::Remesh || bUseTargetEdgeLength)", UIMin = "0.0", UIMax = "1.0"))` — Min weight threshold below which the mesh will not be changed
- L267 _protected member_ `bool bDrawAffectedBox = true;` — `UPROPERTY(EditAnywhere, Category = "Modifier|ModifierSettings", meta = (DisplayName = "Local Bounds"))` — When true, draws a box showing affected volume in editor
- L271 _protected member_ `bool bWorldBounds = false;` — `UPROPERTY(EditAnywhere, Category = "Modifier|ModifierSettings")` — When true, draws an axis-aligned box containing the potentially non-axis-aligned Local Bounds

#### class `UE::MeshPartition::URemeshModifier`  
`class URemeshModifier : public MeshPartition::URemeshModifierBase`  
_L281-314_
- reflection: `UCLASS(MinimalAPI, PrioritizeCategories = ("Modifier", "Coverage", "RemeshOperation", "Remesh", "Tessellate", "DensityWeightChannel"), meta = (BlueprintSpawnableComponent, MegaMeshClassVersion = "2"))`
- inherits: `MeshPartition::URemeshModifierBase`
- desc: MegaMeshModifier that does local remeshing or tessellation. Note that currently only triangles whose vertices are entirely inside the modifier's box of influence will be affected.
- L287 _public prototype_ `URemeshModifier();`
- L288 _public prototype_ `virtual ~URemeshModifier() = default;`
- L291 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject
- L293 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L295 _public prototype_ `void SetUnscaledCoverage(const FVector3d& InUnscaledCoverage);`
- L296 _public prototype_ `FVector3d GetUnscaledCoverage() const;`
- L301 _private prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;` — MeshPartition::UModifierComponent
- L302 _private prototype_ `virtual void DrawVisualization(const FSceneView* View, FPrimitiveDrawInterface* PDI) const override;`
- L303 _private prototype_ `virtual FGuid GetCodeVersionKey() const override;`
- L304 _private prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const override;`
- L306 _private prototype_ `Geometry::FAxisAlignedBox3d GetLocalCoverage() const;`
- L312 _private member_ `FVector3d UnscaledCoverage = FVector3d(2000, 2000, 10000);` — `UPROPERTY(EditAnywhere, Category = Coverage, meta = (UIMin = "0", ClampMin = "0"))` — Box in which the modifier remeshes, centered at modifier location. This will be scaled according to component scale.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionSimpleWriteModifier.h` (Public)


#### struct `UE::MeshPartition::FSimpleWriteModifier_ChannelValues`  
`struct FSimpleWriteModifier_ChannelValues`  
_L26-40_
- reflection: `USTRUCT()`
- L30 _public prototype_ `FSimpleWriteModifier_ChannelValues() = default;`
- L31 _public function_ `FSimpleWriteModifier_ChannelValues(const FName& NameIn, const TArray<float>& ValuesIn) : Name(NameIn) , Values(ValuesIn)`
- L37 _public member_ `FName Name;` — `UPROPERTY()`
- L39 _public member_ `TArray<float> Values;` — `UPROPERTY()`

#### class `UE::MeshPartition::USimpleWriteModifier`  
`class USimpleWriteModifier : public MeshPartition::UModifierComponent , public ICodeReusableModifier`  
_L49-103_
- reflection: `UCLASS(MinimalAPI, meta = (MegaMeshClassVersion = "1"))`
- inherits: `MeshPartition::UModifierComponent,ICodeReusableModifier`
- desc: Modifier intended to be used with PCG
- L55 _public prototype_ `USimpleWriteModifier();`
- L58 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;` — MeshPartition::UModifierComponent
- L59 _public prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;`
- L60 _public prototype_ `virtual FGuid GetCodeVersionKey() const override;`
- L61 _public prototype_ `virtual bool IsTemporarilyDisabledInEditor() const override;`
- L64 _public prototype_ `virtual void SetDisabledByCode(bool bDisabledIn) override;` — ICodeReusableModifier
- L65 _public prototype_ `virtual void ResetForReuse() override;`
- L66 _public prototype_ `virtual bool IsUsed() const override;`
- L68 _public prototype_ `void ReinitializePoints( const TArray<FVector3d>& SourcePositions, const TArray<FVector3d>* DestPositions, const TArray<TPair<FName, TArray<float>>>& WeightChannelValues);`
- L74 _protected prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const override;`
- L77 _private prototype_ `void ClearPoints();`
- L78 _private prototype_ `void ResetCachedData();`
- L81 _private member_ `TArray<FVector3d> SourcePositions;` — `UPROPERTY()`
- L83 _private member_ `TOptional<TArray<FVector3d>> DestPositions;` — `UPROPERTY()`
- L86 _private member_ `TArray<MeshPartition::FSimpleWriteModifier_ChannelValues> WeightChannelValues;` — `UPROPERTY()`
- L88 _private member_ `FBox GlobalBounds;` — `UPROPERTY()`
- L92 _private member_ `FBox ExpandedBounds;` — `UPROPERTY()` — This is the same as GlobalBounds but expanded by a very small number so that we can make sure to grab any points that were on the edges and might otherwise be missed due to imprecision.
- L95 _private member_ `mutable TSharedPtr<const TArray<FVector3d>> SourcePositions_BackgroundOp;` — Cached data for CreateBackgroundOp
- L96 _private member_ `mutable TSharedPtr<const TArray<FVector3d>> DestPositions_BackgroundOp;`
- L97 _private member_ `mutable TSharedPtr<const TArray<TPair<FName, TArray<float>>>> WeightChannelValues_BackgroundOp;`
- L98 _private member_ `mutable TSharedPtr<const Geometry::TPointHashGrid3<int32, double>> HashGrid_BackgroundOp;`
- L100 _private member_ `bool bDisabledByCode = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)
- L17 _namespace_ `namespace MegaMeshWriteModifierLocals` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionSplineDelegateHelper.h` (Public)


#### class `UE::MeshPartition::FSplineDelegateHelper`  
`class FSplineDelegateHelper`  
_L17-105_
- desc: Helper that manages spline-change delegates (undo/redo, property, transform). Both USplineModifier and USplineRemeshModifier own an instance of this to avoid duplicating the registration/unregistration boilerplate.
- L21 _public typedef_ `using FOnSplineChanged = TFunction<void()>;` — Callback invoked when any spline delegate fires.
- L23 _public function_ `FSplineDelegateHelper(UObject* InOwner, FOnSplineChanged InCallback) : Owner(InOwner) , Callback(MoveTemp(InCallback))`
- L29 _public function_ `~FSplineDelegateHelper()`
- L35 _public function_ `void Register(USplineComponent* Spline)` — Bind delegates to a new spline (unbinds any previous one first).
- L69 _public function_ `void Unregister()` — Unbind all delegates.
- L99 _private member_ `UObject* Owner = nullptr;`
- L100 _private member_ `FOnSplineChanged Callback;`
- L101 _private member_ `FDelegateHandle OnTransactedHandle;`
- L102 _private member_ `FDelegateHandle OnChangedHandle;`
- L103 _private member_ `FDelegateHandle OnTransformUpdatedHandle;`
- L104 _private member_ `TWeakObjectPtr<USplineComponent> RegisteredSpline;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshPartition` (scope `UE`)
- L48 _function_ `` (scope `UE::MeshPartition::FSplineDelegateHelper::Register`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionSplineModifier.h` (Public)


#### enum `UE::MeshPartition::ESplineModifierBlendMode`  
`enum class ESplineModifierBlendMode : uint8`  
_L41-51_
- reflection: `UENUM()`
- L44 _public enumerator_ `Normal` — No restrictions on which vertices are affected
- L47 _public enumerator_ `Min` — Only move vertices lying on the positive Z side of the spline
- L50 _public enumerator_ `Max` — Only move vertices lying on the negative Z side of the spline

#### enum `UE::MeshPartition::ESplineModifierWriteMode`  
`enum class ESplineModifierWriteMode : uint8`  
_L55-62_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Which outputs a spline modifier writes.
- L58 _public enumerator_ `Positions = (1 << 0)` — Displace vertex positions along the spline projection direction.
- L61 _public enumerator_ `Weights = (1 << 1)` — Write to weight channels using the spline falloff as the blending alpha.

#### enum `UE::MeshPartition::ESplineWeightBlendMode`  
`enum class ESplineWeightBlendMode : uint8`  
_L67-80_
- reflection: `UENUM()`
- desc: How a spline modifier's weight channel value is combined with existing values.
- L70 _public enumerator_ `AlphaBlend` — The new value replaces the existing value, blended by the spline falloff.
- L73 _public enumerator_ `Additive` — The new value is added to the existing value, scaled by the spline falloff.
- L76 _public enumerator_ `Min` — Takes the minimum of the existing and new values, blended by the spline falloff.
- L79 _public enumerator_ `Max` — Takes the maximum of the existing and new values, blended by the spline falloff.

#### enum `UE::MeshPartition::ESplineModifierInteriorSmoothMode`  
`enum class ESplineModifierInteriorSmoothMode : uint8`  
_L83-93_
- reflection: `UENUM()`
- L86 _public enumerator_ `Simple = 1` — Snaps the MegaMesh surface to the closest point on the region within the spline.
- L89 _public enumerator_ `Smooth = 2` — Smooths the Megamesh surface against the spline boundary, accounting for falloff normals at the edge.
- L92 _public enumerator_ `DetailPreserving = 3` — Transfers the underlying Megamesh surface detail to fit within the spline boundary.

#### struct `UE::MeshPartition::FSplineModifierWeightEntry`  
`struct FSplineModifierWeightEntry`  
_L100-115_
- reflection: `USTRUCT()`
- desc: Describes a single weight channel entry for a spline modifier. The spline's own falloff (HeightAlpha) is used as the blending alpha.
- L106 _public member_ `MeshPartition::FChannelName WeightChannelName;` — `UPROPERTY(EditAnywhere, Category = "", meta = (GetOptions = "GetMegaMeshDefinitionChannels", NoResetToDefault))` — Which weight channel to write.
- L110 _public member_ `double Value = 1.0;` — `UPROPERTY(EditAnywhere, Category = "")` — The value to write at full influence.
- L114 _public member_ `MeshPartition::ESplineWeightBlendMode BlendMode = MeshPartition::ESplineWeightBlendMode::AlphaBlend;` — `UPROPERTY(EditAnywhere, Category = "")` — How the value is blended with the existing channel value.

#### class `UE::MeshPartition::USplineModifier`  
`class USplineModifier : public MeshPartition::UModifierComponent, public MeshPartition::ISplineModifierBlueprintInterface`  
_L121-412_
- reflection: `UCLASS(MinimalAPI, PrioritizeCategories = ("Modifier", "Coverage", "Spline", "EdgeFalloff", "Interior", "WeightChannels"), meta = (BlueprintSpawnableComponent, MegaMeshClassVersion = "-1"))`
- inherits: `MeshPartition::UModifierComponent,MeshPartition::ISplineModifierBlueprintInterface`
- desc: A flexible spline based modifier, suitable for representing ridgelines, channels, raised hills, and lowered depression pockets.
- L126 _public prototype_ `USplineModifier();`
- L127 _public prototype_ `virtual ~USplineModifier();`
- L130 _public prototype_ `virtual void PreEditChange(FProperty* InPropertyAboutToChange) override;` — UObject Implementation
- L131 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L132 _public prototype_ `virtual void PostEditUndo() override;`
- L133 _public prototype_ `virtual void PostLoad() override;`
- L137 _public prototype_ `virtual void InitializeModifier() override;` — MeshPartition::UModifierComponent Implementation
- L138 _public prototype_ `virtual void UninitializeModifier() override;`
- L139 _public prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;`
- L140 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L141 _public prototype_ `virtual void DrawVisualization(const FSceneView* View, FPrimitiveDrawInterface* PDI) const override;`
- L142 _public prototype_ `virtual FGuid GetCodeVersionKey() const override;`
- L143 _public prototype_ `virtual bool IsContiguous() const override;`
- L148 _public prototype_ `void UpdateSplineData();` — `UFUNCTION(CallInEditor, Category = "Spline")` — Rebuild modifier state based on the spline. Note: Use if anything seems weird or out of date!
- L150 _public prototype_ `void SetSplineComponent(USplineComponent* InSplineComponent, bool bUpdate = true);`
- L151 _public prototype_ `USplineComponent* GetSplineComponent() const;`
- L154 _public prototype_ `virtual void BP_SetSplineComponent(USplineComponent* InSplineComponent) override;` — `UFUNCTION(BlueprintCallable, Category = "Spline", meta = (DisplayName = "Set Spline Component"))`
- L156 _public prototype_ `void SetProjectedSplineCurve(FInterpCurveVector&& NewProjectedCurve) const;`
- L158 _public function_ `float GetMaxZDistance() const`
- L162 _public prototype_ `void SetMaxZDistance(float InMaxZDistance);`
- L164 _public prototype_ `void SetUseNearestSplineFrameForDisplacement(bool InUseNearestSplineFrameForDisplacement);`
- L166 _public function_ `float GetFalloffDistance() const`
- L170 _public prototype_ `void SetFalloffDistance(float InFalloffDistance);`
- L172 _public function_ `float GetSplinePolygonErrorTolerance() const`
- L176 _public prototype_ `void SetSplinePolygonErrorTolerance(float InSplinePolygonErrorTolerance);`
- L178 _public function_ `double GetMeshedInteriorNumTriTarget() const`
- L182 _public prototype_ `void SetMeshedInteriorNumTriTarget(double InMeshedInteriorNumTriTarget);`
- L184 _public function_ `float GetFalloffBoundsMultiplier() const`
- L188 _public prototype_ `void SetFalloffBoundsMultiplier(float InFalloffBoundsMultiplier);`
- L190 _public function_ `ESplineModifierInteriorSmoothMode GetInteriorSmoothMode() const`
- L194 _public prototype_ `void SetInteriorSmoothMode(ESplineModifierInteriorSmoothMode InInteriorSmoothMode);`
- L196 _public function_ `float GetMaxProjectionHeightExtent() const`
- L200 _public prototype_ `void SetMaxProjectionHeightExtent(float InMaxProjectionHeightExtent);`
- L202 _public prototype_ `void SetMeshClosedInterior(bool InbMeshClosedInterior);`
- L204 _public prototype_ `void SetUseSplineScaleForFalloff(bool bInUseSplineScaleForFalloff);`
- L206 _public function_ `bool GetExpandBoundsBySplineScale() const`
- L210 _public prototype_ `void SetExpandBoundsBySplineScale(bool bInExpandBoundsBySplineScale);`
- L217 _private member_ `FComponentReference SplineRef;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L220 _private member_ `TSoftObjectPtr<USplineComponent> SplinePtr;` — `UPROPERTY(EditAnywhere, Category = "Spline", meta = (DisplayName="Spline"))`
- L228 _private member_ `FString TemplateSplineComponentName;` — `UPROPERTY(EditDefaultsOnly, Category = "Hidden", meta = (DisplayName = "Spline Component Name"))` — Allows specifying a spline by name if the spline component is not yet instanced (for example in a Blueprint class). At instance creation (after RegisterAllComponents), the actual USplineComponent on the owning actor is resolved using this name. Editable in Blueprint class (defaults) only, not per-instance.
- L234 _private member_ `uint8 WriteMode = static_cast<uint8>(MeshPartition::ESplineModifierWriteMode::Positions | MeshPartition::ESplineModifierWriteMode::Weights);` — `UPROPERTY(EditAnywhere, Category = "Coverage", meta = (Bitmask, BitmaskEnum = "/Script/MeshPartitionEditor.ESplineModifierWriteMode"))` — Controls which outputs this spline modifier writes.
- L240 _private member_ `float FalloffDistance = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Coverage", meta = (UIMin = 5, UIMax = 1500, ClampMin = 0.1))` — Determines how far in projected world distance the spline affects the mesh to either side of it. A higher value results in a slower slope.
- L246 _private member_ `bool bUseSplineScaleForFalloff = true;` — `UPROPERTY(EditAnywhere, Category = "Coverage", meta = (DisplayName = "Spline Scale for Falloff"))` — When true, the scale Y values along the spline are multiplied by FalloffDistance to get the final falloff distance to use.
- L254 _private member_ `float PlateauDistance = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Coverage", meta = (UIMin = 0, UIMax = 1500, ClampMin = 0))` — Distance from the spline that remains at full influence before the falloff begins. At 0, the falloff starts immediately at the spline (triangular profile). Values greater than 0 create a flat plateau of that width, followed by the falloff region (trapezoid profile).
- L260 _private member_ `bool bUseSplineScaleForPlateau = false;` — `UPROPERTY(EditAnywhere, Category = "Coverage", meta = (DisplayName = "Spline Scale for Plateau"))` — When true, the scale Y values along the spline are multiplied by PlateauDistance to get the final plateau distance to use.
- L263 _private member_ `float FalloffPlateauRatio = 0.0f;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use PlateauDistance instead"))`
- L270 _private member_ `bool bMeshClosedInterior = true;` — `UPROPERTY(EditAnywhere, Category = "Interior")` — When true, closed splines get meshed to create a plateau. When false, they continue to operate like open splines, creating volcano-like structures.
- L278 _private member_ `bool bUseNearestSplineFrameForDisplacement = false;` — `UPROPERTY(EditAnywhere, Category = "Coverage", meta = (DisplayName = "Displace Nearest Frame"))` — When true, instead of using the Component Z as a single projection/height direction, the direction is taken from the rotation around the nearest spline point to each vertex. This is ignored when using a closed loop with bMeshClosedInterior set to true.
- L284 _private member_ `bool bNearestFrameFastApproximation = false;` — `UPROPERTY(EditAnywhere, Category = "Coverage", meta = (EditCondition = bUseNearestSplineFrameForDisplacement))` — When true use a faster but less accurate method for getting the nearest frame on the spline
- L293 _private member_ `ESplineModifierBlendMode BlendMode = ESplineModifierBlendMode::Normal;` — `UPROPERTY(EditAnywhere, Category = "Coverage")` — When set to Min only vertices on the +Z side of the spline are affected. When Max only vertices on the -Z side of the spline are affected, and when it's Normal there is no restriction based on the Z axis. If bUseNearestSplineFrameForDisplacement is also true, then the Min/Max is computed with respect to the nearest frame's rotated Z axis.
- L296 _private member_ `bool bSingleSidedProjection_DEPRECATED = false;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use BlendMode instead"))`
- L302 _private member_ `float MaxZDistance = 2000.f;` — `UPROPERTY(EditAnywhere, Category = "Coverage", meta = (ClampMin = 0, UIMax = 10000))` — When projecting in a single direction, the amount to extend the Z bounds in each direction around modifier location
- L310 _private member_ `float MaxProjectionHeightExtent = 500;` — `UPROPERTY(EditAnywhere, Category = "Coverage", meta = (EditCondition = "bUseNearestSplineFrameForDisplacement"))` — This is used instead of MaxZDistance when bUseNearestSplineFrameForDisplacement is true, since we expand the bounds in all directions, not just Z, in that case, so we want to be more conservative.
- L317 _private member_ `bool bExpandBoundsBySplineScale = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "EdgeFalloff", meta = (EditCondition = "bUseSplineScaleForFalloff"))` — When true, the bounds expansion automatically accounts for the maximum spline scale value, replacing FalloffBoundsMultiplier. When false, FalloffBoundsMultiplier is used instead.
- L325 _private member_ `float FalloffBoundsMultiplier = 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "EdgeFalloff", meta = (UIMin = 0.1, UIMax = 10, ClampMin = 0.1, EditCondition = "!bExpandBoundsBySplineScale"))` — When calculating bounds, the falloff value is multiplied by this value. This can be set above 1 if the spline has scale above 1 along its length, and bUseSplineScaleForFalloff is true. Ignored when bExpandBoundsBySplineScale is true.
- L329 _private member_ `bool bDrawProjectionPlane = false;` — `UPROPERTY(EditAnywhere, Category = "Modifier|ModifierSettings", meta = (DisplayName = "Projection Plane", EditCondition = "!bUseNearestSplineFrameForDisplacement"))`
- L332 _private member_ `bool bDrawLocalBounds = true;` — `UPROPERTY(EditAnywhere, Category = "Modifier|ModifierSettings", meta = (DisplayName = "Local Bounds"))`
- L335 _private member_ `bool bDrawSplineFrames = false;` — `UPROPERTY(EditAnywhere, Category = "Modifier|ModifierSettings", meta = (DisplayName = "Spline Frames"))`
- L338 _private member_ `int32 NumSplineFrames = 10;` — `UPROPERTY(EditAnywhere, Category = "Modifier|ModifierSettings", meta = (EditCondition = bDrawSplineFrames))`
- L341 _private member_ `double FrameScale = 100.0;` — `UPROPERTY(EditAnywhere, Category = "Modifier|ModifierSettings", meta = (EditCondition = bDrawSplineFrames, UIMin = 0.1, UIMax = 2000, ClampMin = 0.1))`
- L344 _private member_ `bool bDrawProjectedSpline = false;` — `UPROPERTY(EditAnywhere, Category = "Modifier|ModifierSettings", meta = (DisplayName = "Projected Spline", EditCondition = "bUseNearestSplineFrameForDisplacement && !bNearestFrameFastApproximation"))`
- L350 _private member_ `bool bUseEdgeFalloffCurve = false;` — `UPROPERTY(EditAnywhere, Category = "EdgeFalloff")` — Uses a curve for the falloff shape.
- L353 _private member_ `TObjectPtr<UCurveFloat> EdgeFalloffCurve = nullptr;` — `UPROPERTY(EditAnywhere, Category = "EdgeFalloff", meta = (EditCondition = "bUseEdgeFalloffCurve"))`
- L361 _private member_ `bool bSplineIsLeftOfFalloffCurve = false;` — `UPROPERTY(EditAnywhere, Category = "EdgeFalloff", meta = (DisplayName = "Spline Left of Falloff", EditCondition = "Spline Left of Falloff"))` — When false, the falloff curve in interpreted with the x axis as moving closer to the spline in the positive direction, i.e. the falloff is an alpha remapping. When true, the x axis moves away from the spline in the positive direction, i.e. the curve is a remapping of 1-Alpha.
- L363 _private member_ `FDelegateHandle EdgeFalloffUpdateHandle;`
- L370 _private member_ `MeshPartition::ESplineModifierInteriorSmoothMode InteriorSmoothMode = MeshPartition::ESplineModifierInteriorSmoothMode::Simple;` — `UPROPERTY(EditAnywhere, Category = "Interior", meta = (EditCondition = "bMeshClosedInterior"))` — Sets a smoothing operation that is run on the interior. Note that any value other than "Simple" increases the cost of the modifier due to its need for topology information.
- L376 _private member_ `float SplinePolygonErrorTolerance = 5.f;` — `UPROPERTY(EditAnywhere, Category = "Interior", meta = (DisplayName = "Spline Error Tolerance", EditCondition = "bMeshClosedInterior", UIMin = 5, ClampMin = 5))` — When meshing the interior, controls the resolution of a polyline estimate of the boundary.
- L384 _private member_ `double MeshedInteriorNumTriTarget = 500;` — `UPROPERTY(EditAnywhere, Category = "Interior", meta = (DisplayName = "Num Tri Target", EditCondition = "bMeshClosedInterior", UIMax = 2000, ClampMin = 1))` — When meshing the interior, roughly controls the granularity of the remeshing (higher is more triangles). This is not actually a true target number of triangles- instead we target an edge length corresponding to equilateral triangles of area sized TotalArea/NumTriTarget.
- L387 _private member_ `bool bShowDebugSurface = false;` — `UPROPERTY(EditAnywhere, Category = "Interior", meta = (EditCondition = "bMeshClosedInterior"))`
- L393 _private member_ `TArray<FSplineModifierWeightEntry> WeightChannels;` — `UPROPERTY(EditAnywhere, Category = "WeightChannels")` — Weight channels written by this modifier, using the spline falloff as the blending alpha.
- L395 _private prototype_ `void UpdateWhenEdgeFalloffChanges(UCurveBase* Curve, EPropertyChangeType::Type);`
- L397 _private prototype_ `FBox ComputeLocalBounds() const;`
- L399 _private prototype_ `bool ShouldFillInterior() const;`
- L401 _private prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const override;`
- L402 _private member_ `mutable TSharedPtr<const FSplineCachedSurfaceData> CurrentCachedData;`
- L403 _private member_ `mutable uint32 LastSplineVersion = 0;`
- L405 _private member_ `mutable FInterpCurveVector ProjectedSplineCurve;`
- L406 _private member_ `mutable FCriticalSection ProjectedSplineCurveMutex;`
- L409 _private member_ `TUniquePtr<FSplineDelegateHelper> SplineDelegateHelper;` — Manages spline-change delegate registration/unregistration.

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L26 _namespace_ `namespace MegaMeshSplineModifierLocals`
- L32 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`
- L33 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMeshOperator);`
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace MeshPartition` (scope `UE`)
- L63 _prototype_ `ENUM_CLASS_FLAGS(ESplineModifierWriteMode);` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionSplineRemeshModifier.h` (Public)


#### class `UE::MeshPartition::USplineRemeshModifier`  
`class USplineRemeshModifier : public MeshPartition::URemeshModifierBase`  
_L21-92_
- reflection: `UCLASS(MinimalAPI, PrioritizeCategories = ("Modifier", "Coverage", "Spline", "RemeshOperation", "Remesh", "Tessellate", "DensityWeightChannel"), meta = (BlueprintSpawnableComponent, MegaMeshClassVersion = "-1"))`
- inherits: `MeshPartition::URemeshModifierBase`
- desc: A modifier that will remesh or tessellate all triangles within some distance to a spline
- L26 _public prototype_ `USplineRemeshModifier();`
- L27 _public prototype_ `virtual ~USplineRemeshModifier() = default;`
- L31 _public prototype_ `void UpdateSplineData();` — `UFUNCTION(CallInEditor, Category = "Spline")` — Rebuild modifier state based on the spline. Note: Use if anything seems weird or out of date!
- L33 _public prototype_ `void SetSplineComponent(USplineComponent*, bool bUpdate = true);`
- L37 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L39 _private prototype_ `virtual void InitializeModifier() override;`
- L40 _private prototype_ `virtual void UninitializeModifier() override;`
- L42 _private prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;`
- L43 _private prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L44 _private prototype_ `virtual void DrawVisualization(const FSceneView* View, FPrimitiveDrawInterface* PDI) const override;`
- L45 _private prototype_ `virtual FGuid GetCodeVersionKey() const override;`
- L46 _private prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const override;`
- L48 _private prototype_ `USplineComponent* GetSplineComponent() const;`
- L49 _private prototype_ `FBox ComputeLocalBounds() const;`
- L54 _private member_ `FComponentReference SplineRef;` — `UPROPERTY(EditAnywhere, Category = Spline, meta = (DisplayName="Spline", UseComponentPicker, AllowedClasses = "/Script/Engine.SplineComponent"))`
- L58 _private member_ `float SplineRadius = 500.f;` — `UPROPERTY(EditAnywhere, Category = Coverage, meta = (UIMin = 5, UIMax = 1500, ClampMin = 0.1))` — Radius around the spline that defines the region of effect. If the spline is closed, this also defines the thickness of the generated volume
- L62 _private member_ `bool bCreateVolumeFromClosedSpline = false;` — `UPROPERTY(EditAnywhere, Category = Interior)` — If true and if the spline is closed, generate a volume defined by the Spline and Spline Radius. Triangles within the volume are affected by the modifier
- L66 _private member_ `float ROIVolumePolygonErrorTolerance = 5.f;` — `UPROPERTY(EditAnywhere, Category = Interior, AdvancedDisplay, meta = (UIMin = 5, ClampMin = 5, EditCondition = bCreateVolumeFromClosedSpline))` — When generating a volume from a closed spline, this is the maximum distance from the spline to its polyline estimate
- L70 _private member_ `double ROIVolumeTargetResolution = 500;` — `UPROPERTY(EditAnywhere, Category = Interior, AdvancedDisplay, meta = (UIMax = 2000, ClampMin = 1, EditCondition = bCreateVolumeFromClosedSpline))` — When generating a volume from a closed spline, this roughly controls the resolution of the enclosing surface
- L77 _private member_ `bool bDrawSplineRadius = false;` — `UPROPERTY(EditAnywhere, Category = "Modifier|ModifierSettings")` — Whether to visualize the spline radius using circles
- L81 _private member_ `int SplineRadiusSamples = 10;` — `UPROPERTY(EditAnywhere, Category = "Modifier|ModifierSettings", meta = (EditCondition = bDrawSplineRadius, UIMin = 0, UIMax = 100, ClampMin = 0, ClampMax = 1000))` — If we are visualizing the spline radius, how many circles to use
- L85 _private member_ `bool bDrawSurface = false;` — `UPROPERTY(EditAnywhere, Category = "Modifier|ModifierSettings")` — Whether to visualize surface generated from the closed spline
- L87 _private member_ `mutable TSharedPtr<const FSplineCachedSurfaceData> CurrentCachedData;`
- L88 _private member_ `mutable uint32 LastSplineVersion = 0;`
- L91 _private member_ `TUniquePtr<FSplineDelegateHelper> SplineDelegateHelper;` — Manages spline-change delegate registration/unregistration.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionTexturePatchModifier.h` (Public)


#### enum `UE::MeshPartition::ETexturePatchBlendMode`  
`enum class ETexturePatchBlendMode : uint8`  
_L30-44_
- reflection: `UENUM(BlueprintType)`
- L34 _public enumerator_ `AlphaBlend` — The value in the patch determines the "vertical" (in patch Z direction) target position, and this is blended with the existing position using alpha/falloff.
- L37 _public enumerator_ `Additive` — The value in the patch is an offset to add to the current positions in the patch Z direction.
- L40 _public enumerator_ `Min` — Like Alpha Blend mode, but limited to only moving existing vertices downward in patch Z direction.
- L43 _public enumerator_ `Max` — Like Alpha Blend mode, but limited to only moving existing vertices upward in patch Z direction.

#### enum `UE::MeshPartition::ETexturePatchFalloffMode`  
`enum class ETexturePatchFalloffMode : uint8`  
_L47-52_
- reflection: `UENUM(BlueprintType)`
- L49 _public enumerator_ `Linear`
- L50 _public enumerator_ `Smooth`
- L51 _public enumerator_ `CustomCurve`

#### enum `UE::MeshPartition::ETexturePatchAlphaMode`  
`enum class ETexturePatchAlphaMode : uint8`  
_L55-68_
- reflection: `UENUM(BlueprintType)`
- L58 _public enumerator_ `AlwaysOne` — Alpha is always 1.0
- L61 _public enumerator_ `SelfMask` — Alpha is 0 wherever the texture patch has a zero value, and 1.0 where it is nonzero
- L64 _public enumerator_ `ThisAlphaChannel` — A channel on the texture being used for values
- L67 _public enumerator_ `OtherAlphaChannel` — A channel on some other texture, other than the value texture

#### enum `UE::MeshPartition::ETexturePatchTessellationMode`  
`enum class ETexturePatchTessellationMode : uint8`  
_L72-88_
- reflection: `UENUM(BlueprintType)`
- L77 _public enumerator_ `NonAdaptive UMETA(DisplayName = "None")` — Vertex displacement only
- L82 _public enumerator_ `Adaptive` — Adaptive Tessellation (high quality)
- L87 _public enumerator_ `AdaptiveFast` — Parallel Adaptive Tessellation (fast)

#### enum `UE::MeshPartition::ETexturePatchTessellationErrorMode`  
`enum class ETexturePatchTessellationErrorMode : uint8`  
_L92-103_
- reflection: `UENUM(BlueprintType)`
- L97 _public enumerator_ `Absolute` — Target error specified in scene-units.
- L102 _public enumerator_ `Relative` — Scale-invariant tessellation detail, relative to object bounds.

#### class `UE::MeshPartition::UTexturePatchEntry`  
`class UTexturePatchEntry : public UObject`  
_L107-262_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- L112 _public prototype_ `void SetTextureAsset(UTexture2D* InTextureAsset);`
- L113 _public prototype_ `UTexture2D* GetTextureAsset() const;`
- L115 _public prototype_ `void SetTextureChannelIndex(const int32 InTextureChannelIndex);`
- L116 _public prototype_ `int32 GetTextureChannelIndex() const;`
- L118 _public prototype_ `void SetAlphaBlendingMode(const MeshPartition::ETexturePatchAlphaMode InTexturePatchAlphaMode);`
- L119 _public prototype_ `ETexturePatchAlphaMode GetAlphaBlendingMode() const;`
- L121 _public prototype_ `void SetTexturePatchBlendMode(const MeshPartition::ETexturePatchBlendMode InTexturePatchBlendMode);`
- L122 _public prototype_ `ETexturePatchBlendMode GetTexturePatchBlendMode() const;`
- L124 _public prototype_ `void SetUseValueCurve(const bool bInUseValueCurve);`
- L125 _public prototype_ `bool GetUseValueCurve() const;`
- L127 _public prototype_ `void SetValueCurve(UCurveFloat* InValueCurve);`
- L128 _public prototype_ `UCurveFloat* GetValueCurve() const;`
- L139 _private member_ `TObjectPtr<UTexture2D> TextureAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "", meta = (DisallowedAssetDataTags = "VirtualTextureStreaming=True"))` — Texture that the patch samples. Note that currently the patch will not know to trigger a reapplication if the data inside the asset changes somehow.
- L145 _private member_ `int32 TextureChannelIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "", DisplayName = "Texture Channel", meta = (ClampMin = "0", ClampMax = "3"))` — Channel index to sample in the texture asset. R: 0, G: 1, B:2, A:3
- L149 _private member_ `MeshPartition::ETexturePatchAlphaMode AlphaMode = MeshPartition::ETexturePatchAlphaMode::SelfMask;` — `UPROPERTY(EditAnywhere, Category = "Alpha Blending")`
- L153 _private member_ `TObjectPtr<UTexture2D> AlphaTextureAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Alpha Blending", meta = (DisallowedAssetDataTags = "VirtualTextureStreaming=True", EditCondition = "AlphaMode == ETexturePatchAlphaMode::OtherAlphaChannel", EditConditionHides))`
- L157 _private member_ `int32 AlphaChannelIndex = 3;` — `UPROPERTY(EditAnywhere, Category = "Alpha Blending", meta = (ClampMin = "0", ClampMax = "3", EditConditionHides, EditCondition = "AlphaMode == ETexturePatchAlphaMode::ThisAlphaChannel || AlphaMode == ETexturePatchAlphaMode::OtherAlphaChannel"))`
- L164 _private member_ `double SelfMaskTolerance = 0.001;` — `UPROPERTY(EditAnywhere, Category = "Alpha Blending", meta = (ClampMin = "0", UIMax = "1", EditCondition = "AlphaMode == ETexturePatchAlphaMode::SelfMask", EditConditionHides))` — When using "Self Mask" alpha mode, the alpha will be set to 0 if absolute value of the texture sampled values is this or lower.
- L170 _private member_ `MeshPartition::ETexturePatchBlendMode BlendMode = MeshPartition::ETexturePatchBlendMode::AlphaBlend;` — `UPROPERTY(EditAnywhere, Category = "Alpha Blending")` — How the values from the texture affect the intensity.
- L179 _private member_ `double SoftnessParameter = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Alpha Blending", meta = (ClampMin = "0.0", UIMax = "1000", EditConditionHides, EditCondition = "BlendMode == ETexturePatchBlendMode::Min || BlendMode == ETexturePatchBlendMode::Max"))` — When using Min or Max BlendMode, allows for the transition between current values and new values to be smoothed out, to prevent sharp edges when intersecting existing geometry in the center of the modifier (where the falloff does not reach). The parameter corresponds to distance between the desired and current heights across which the min/max is blended.
- L186 _private member_ `MeshPartition::ETexturePatchFalloffMode FalloffMode = MeshPartition::ETexturePatchFalloffMode::Smooth;` — `UPROPERTY(EditAnywhere, Category = "Falloff", DisplayName = "Mode")` — How effects of the patch are decreased along the edges of the modifier. The effect will take place across Falloff Distance from the modifier edges.
- L192 _private member_ `float FalloffDistance = 0;` — `UPROPERTY(EditAnywhere, Category = "Falloff", meta = (ClampMin = "0", UIMax = "2000"))` — Distance (in local space) across which to fall off the patch effects from the edge.
- L199 _private member_ `float CornerRadius = 0;` — `UPROPERTY(EditAnywhere, Category = "Falloff", meta = (ClampMin = "0", UIMax = "2000"))` — When not 0, the corners are rounded with the given radius (clamped to half of the smallest dimension). A square patch with maximal corner radius becomes a circle.
- L203 _private member_ `TObjectPtr<UCurveFloat> FalloffCurve;` — `UPROPERTY(EditAnywhere, Category = "Falloff", DisplayName = "Curve", meta = ( EditCondition = "FalloffMode == ETexturePatchFalloffMode::CustomCurve", EditConditionHides))`
- L209 _private member_ `bool bUseValueCurve = false;` — `UPROPERTY(EditAnywhere, Category = "Curve Adjustment")` — When true, allows a custom curve to remap values from the texture, before Scale and Zero Value are applied.
- L215 _private member_ `TObjectPtr<UCurveFloat> ValueCurve = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Curve Adjustment", meta = (EditCondition = "bUseValueCurve", EditConditionHides))` — Optional adjustment curve that can be applied to texture values (similar to a contrast adjustment).
- L224 _private member_ `double ValueCurveOffset = 0;` — `UPROPERTY(EditAnywhere, Category = "Curve Adjustment", meta = (UIMin = "0", UIMax = "2000", EditCondition="bUseValueCurve", EditConditionHides), AdvancedDisplay)` — If the texture values are not in the range [0,1], gives a way to remap to a [0,1] range for using the adjustment curve. The input to the curve will be transformed via (Input - ValueCurveOffset) / ValueCurveScale, and the output will be transformed back via Output * AjustmentCurveScale + AjustmentCurveOffset.
- L231 _private member_ `double ValueCurveScale = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Curve Adjustment", meta = (ClampMin = "0.000001", UIMax = "2000", EditCondition = "bUseValueCurve", EditConditionHides), AdvancedDisplay)` — If the texture values are not in the range [0,1], gives a way to remap to a [0,1] range for using the adjustment curve. The input to the curve will be transformed via (Input - ValueCurveOffset) / ValueCurveScale, and the output will be transformed back via Output * AdjustmentCurveScale + AdjustmentCurveOffset.
- L233 _private member_ `FDelegateHandle FalloffCurveListenerHandle;`
- L234 _private member_ `FDelegateHandle ValueCurveListenerHandle;`
- L236 _private function_ `void TriggerModifierUpdate()`
- L247 _private prototype_ `void OnCurveChanged(UCurveBase* Curve, EPropertyChangeType::Type ChangeType);`
- L248 _private prototype_ `void AttachCurveListeners();`
- L249 _private prototype_ `void DetachCurveListeners();`
- L252 _private prototype_ `virtual void PreEditChange(FEditPropertyChain& PropertyAboutToChange) override;` — UObject
- L253 _private prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`

#### class `UE::MeshPartition::UTexturePatchHeightEntry`  
`class UTexturePatchHeightEntry : public MeshPartition::UTexturePatchEntry`  
_L265-298_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `MeshPartition::UTexturePatchEntry`
- L277 _private member_ `double EncodingScale = 1000.;` — `UPROPERTY(EditAnywhere, Category = "", DisplayName = "Scale", meta = (DisplayAfter = "TextureChannelIndex", UIMin = "0", UIMax = "10000"))` — How to scale values read from the texture, controlling the intensity in the local space of the component. If the texture stores values in the range [0,1], then you will need to scale this up quite high to turn those values into noticeable effects on the mesh.
- L285 _private member_ `double ZeroInEncoding = 0.5;` — `UPROPERTY(EditAnywhere, Category = "", DisplayName = "Zero Value", meta = (DisplayAfter = "EncodingScale", UIMin = "0", UIMax = "1"))` — What value is considered 0 in the texture. For instance if your texture stores values in the range [0,1], then 0.5 may be your zero. In alpha blend mode, vertices would be moved to patch plane at this value, and in additive mode, no displacement would be made.
- L291 _private member_ `MeshPartition::FChannelName HeightScaleWeightChannel;` — `UPROPERTY(EditAnywhere, Category = "", DisplayName = "Scale Weight Channel", meta = (DisplayAfter = "ZeroInEncoding", GetOptions = "GetMegaMeshDefinitionChannels", NoResetToDefault))` — Optional weight channel to attenuate height scale.
- L294 _private prototype_ `TArray<FName> GetMegaMeshDefinitionChannels() const;` — `UFUNCTION()`

#### class `UE::MeshPartition::UTexturePatchWeightEntry`  
`class UTexturePatchWeightEntry : public MeshPartition::UTexturePatchEntry`  
_L301-356_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `MeshPartition::UTexturePatchEntry`
- L309 _private prototype_ `void CopyFalloffSettings();` — `UFUNCTION(CallInEditor, Category = "", DisplayName = "Copy Falloff", BlueprintCallable)` — Copy all falloff settings from the displacement channel to all weight channels.
- L313 _private member_ `MeshPartition::FChannelName WeightChannelName;` — `UPROPERTY(EditAnywhere, Category = "", meta = (GetOptions = "GetMegaMeshDefinitionChannels", NoResetToDefault))`
- L320 _private member_ `bool bApplyHeightMinMaxBlend = false;` — `UPROPERTY(EditAnywhere, Category = "")` — Only relevant when Min or Max blend mode is used for height. When true, the weights are not applied in areas where the height data was ignored due to above/below the current values in min/max blend mode.
- L329 _private member_ `double HeightMinMaxBlendDistance = 0.0;` — `UPROPERTY(EditAnywhere, Category = "", meta = (ClampMin = "0", UIMax = "1000", EditCondition = "bApplyHeightMinMaxBlend", EditConditionHides))` — When using "Apply Height Min Max Blend," this parameter sets the range of heights across which the weights will blend. If this parameter is equal to Softness Parameter, then heights blended by the Softness Parameter will also have their weights linearly blended.
- L340 _private member_ `double EncodingScale = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Advanced", DisplayName = "Scale", meta = (UIMin = "0", UIMax = "5"))` — How to scale values obtained from the texture. Note: this is applied after the value curve, if that is used.
- L348 _private member_ `double ZeroInEncoding = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Advanced", DisplayName = "Zero Value", meta = (UIMin = "0", UIMax = "1"))` — What value is considered 0 in the texture. For instance you may choose to change the zero to 0.5, so that values of 0 become -0.5 when applied. Note: this is applied after the value curve, if that is used.
- L352 _private prototype_ `TArray<FName> GetMegaMeshDefinitionChannels() const;` — `UFUNCTION()`

#### class `UE::MeshPartition::UTexturePatchModifier`  
`class UTexturePatchModifier : public MeshPartition::UModifierComponent`  
_L363-576_
- reflection: `UCLASS(MinimalAPI, PrioritizeCategories = ("Modifier", "HeightDisplacement", "WeightChannels", "AdaptiveTessellation"), meta=(BlueprintSpawnableComponent, MegaMeshClassVersion = "1"))`
- inherits: `MeshPartition::UModifierComponent`
- desc: A modifier that reads from a given texture and moves vertices in the megamesh in some "vertical" direction (where vertical is determined by the Z direction of this component).
- L368 _public prototype_ `UTexturePatchModifier();`
- L378 _public function_ `virtual FVector2D GetUnscaledCoverage() const` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Gives size in unscaled world coordinates (ie before applying patch transform) of the patch as measured between the centers of the outermost pixels. Measuring the coverage this way means that a patch can affect the same region of the landscape regardless of patch resolution. This is also the range across which bilinear interpolation always has correct values, so the area outside this center portion is usually set as a "dead" border that doesn't affect the landscape.
- L385 _public prototype_ `virtual void SetUnscaledCoverage(const FVector2D Coverage);` — `UFUNCTION(BlueprintCallable, Category = LandscapePatch)` — Set the patch coverage (see GetUnscaledCoverage for description).
- L387 _public prototype_ `void SetApplyComponentZScale(const bool bInApplyComponentZScale);`
- L388 _public prototype_ `bool GetApplyComponentZScale() const;`
- L390 _public prototype_ `void SetHeightChannel(UTexturePatchHeightEntry* InHeightEntry);`
- L391 _public prototype_ `UTexturePatchHeightEntry* GetHeightChannel() const;`
- L393 _public prototype_ `void SetAdaptiveTessellationMode(const ETexturePatchTessellationMode InTessellationMode);`
- L394 _public prototype_ `ETexturePatchTessellationMode GetAdaptiveTesselationMode() const;`
- L397 _public prototype_ `virtual void InitializeModifier() override;` — MeshPartition::UModifierComponent
- L398 _public prototype_ `virtual void UninitializeModifier() override;`
- L399 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L400 _public prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;`
- L401 _public prototype_ `virtual void DrawVisualization(const FSceneView* View, FPrimitiveDrawInterface* PDI) const override;`
- L402 _public prototype_ `virtual FGuid GetCodeVersionKey() const override;`
- L403 _public prototype_ `virtual Tasks::FTask GetAsyncPrepareResourcesTask() const override;`
- L406 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject
- L408 _public prototype_ `virtual void PreEditChange(FEditPropertyChain& PropertyAboutToChange) override;`
- L409 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L410 _public prototype_ `virtual void PostEditUndo() override;`
- L412 _public function_ `void TriggerUpdate()`
- L417 _public prototype_ `void OnInnerObjectModified(const FPropertyChangedEvent& InnerPropertyChangedEvent);`
- L430 _protected member_ `FVector2D UnscaledPatchCoverage = FVector2D(1000, 1000);` — `UPROPERTY(EditAnywhere, Category = "Modifier|Extent", meta = (UIMin = "0", ClampMin = "0"))` — At scale 1.0, the X and Y of the region affected by the height patch. This corresponds to the distance from the center of the first pixel to the center of the last pixel in the patch texture in the X and Y directions.
- L436 _protected member_ `float VerticalPatchExtentUp = 10000.f;` — `UPROPERTY(EditAnywhere, Category = "Modifier|Extent", meta = (ClampMin = "0"), AdvancedDisplay, DisplayName = "Vertical Extent Up")` — How far up above the center it affects vertices in the mesh.
- L442 _protected member_ `float VerticalPatchExtentDown = 10000.f;` — `UPROPERTY(EditAnywhere, Category = "Modifier|Extent", meta = (ClampMin = "0"), AdvancedDisplay, DisplayName = "Vertical Extent Down")` — How far down below the patch it affects vertices in the mesh.
- L448 _protected member_ `bool bDrawPatchRectangle = true;` — `UPROPERTY(EditAnywhere, Category = "Modifier|Visualization")` — When true, draws a red rectangle showing patch area in editor.
- L454 _protected member_ `bool bDrawAffectedBox = true;` — `UPROPERTY(EditAnywhere, Category = "Modifier|Visualization")` — When true, draws a box showing affected volume in editor.
- L461 _protected member_ `TObjectPtr<MeshPartition::UTexturePatchHeightEntry> HeightChannel;` — `UPROPERTY(EditAnywhere, Instanced, Category = HeightDisplacement, DisplayName = "Input", meta=(ShowOnlyInnerProperties))`
- L464 _protected member_ `TArray<TObjectPtr<MeshPartition::UTexturePatchWeightEntry>> WeightChannels;` — `UPROPERTY(EditAnywhere, Instanced, Category = WeightChannels, DisplayName = "Outputs", meta=(ShowOnlyInnerProperties))`
- L470 _protected prototype_ `void MatchWeightFalloffsToHeight();` — `UFUNCTION(BlueprintCallable, Category = WeightChannels)` — Copy falloff settings from height channel to all weight layers
- L476 _protected prototype_ `void MatchWeightAlphaBlendToHeight();` — `UFUNCTION(BlueprintCallable, Category = WeightChannels)` — Copy alpha blend settings from height channel to all weight layers
- L482 _protected prototype_ `void MatchWeightCurveToHeight();` — `UFUNCTION(BlueprintCallable, Category = WeightChannels)` — Copy curve settings from height channel to all weight layers
- L489 _protected prototype_ `void UpdateFromTexture();` — `UFUNCTION(CallInEditor, Category = HeightDisplacement, DisplayName = "Force All Texture Assets Reread", BlueprintCallable)` — Trigger reading data from all texture asset again. This automatically happens if the texture asset, channel, or the "use alpha" flag is changed.
- L495 _protected member_ `bool bApplyComponentZScale = true;` — `UPROPERTY(EditAnywhere, Category = HeightDisplacement, AdvancedDisplay, meta = (DisplayName = "Apply Component Z Scale"))` — Whether to apply the patch Z scale to the height stored in the patch.
- L505 _protected member_ `MeshPartition::ETexturePatchTessellationMode TessellationMode = MeshPartition::ETexturePatchTessellationMode::NonAdaptive;` — `UPROPERTY(EditAnywhere, Category = AdaptiveTessellation, DisplayName = "Mode")` — Tessellation mode to apply.
- L511 _protected member_ `float TessellationError = 50;` — `UPROPERTY(EditAnywhere, Category = AdaptiveTessellation, DisplayName = "Error Tolerance")` — Primary parameter to controlling tessellation detail when using adaptive tessellation (lower values produce finer meshes). When mode is absolute, correspond to world units error.
- L517 _protected member_ `MeshPartition::ETexturePatchTessellationErrorMode TessellationErrorMode = MeshPartition::ETexturePatchTessellationErrorMode::Absolute;` — `UPROPERTY(EditAnywhere, Category = AdaptiveTessellation, AdvancedDisplay, DisplayName = "Error Mode")` — Control whether error criterion is related to world units (absolute) or scale-invariant (relative).
- L523 _protected member_ `float MinimumEdgeLength = 0;` — `UPROPERTY(EditAnywhere, Category = AdaptiveTessellation, AdvancedDisplay)` — Tessellation will not refine edges smaller than this value.
- L529 _protected member_ `float MaximumEdgeLength = 10000;` — `UPROPERTY(EditAnywhere, Category = AdaptiveTessellation, AdvancedDisplay)` — Tessellation will always refine edges larger than this value.
- L535 _protected member_ `bool bTessellationMeshRegularization = false;` — `UPROPERTY(EditAnywhere, Category = AdaptiveTessellation, AdvancedDisplay, meta = (DisplayName = "Mesh Optimization"))` — Whether additional mesh regularization will be applied after tessellation.
- L541 _protected member_ `float TessellationFeatureSensitivity = 0.75f;` — `UPROPERTY(EditAnywhere, Category = AdaptiveTessellation, AdvancedDisplay, meta = (DisplayName = "Feature Sensitivity", ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))` — Controls the sensitivity to features. A higher value will refine more at high curvature areas. Only applies in mode Adaptive Fast.
- L547 _protected member_ `MeshPartition::FChannelName DetailAdjustmentChannelName;` — `UPROPERTY(EditAnywhere, Category = AdaptiveTessellation, AdvancedDisplay, DisplayName = "Detail Adjustment Channel", meta = (GetOptions = "GetMegaMeshDefinitionChannels", NoResetToDefault))` — Optional channel to adjust tessellation detail. Positive values increase detail and negative values decrease detail.
- L550 _protected prototype_ `bool HasScalarField() const;`
- L552 _protected prototype_ `void UpdateAllTextureData();`
- L553 _protected prototype_ `void UpdateHeightChannel();`
- L554 _protected prototype_ `void UpdateWeightChannel(int32 Index);`
- L555 _protected prototype_ `void UpdateChannelData(const UTexturePatchEntry* Channel);`
- L556 _protected prototype_ `void UpdateDisplacementMap();`
- L558 _protected prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const override;`
- L569 _protected member_ `TSharedPtr<const FChannelFieldData> HeightChannelField;` — Since patch application happens in parallel threads, we prep our texture data into a cache (so that we can complete texture compilation, etc) and then use that. To make this cache work across any UnscaledPatchCoverage, it is stored such that it can be sampled using Local2DCoordinates/UnscaledPatchCoverage. This is almost like a UV lookup into the texture with a (-0.5,-0.5) offset but not quite, because the [0,1] range stretches between the middles of the extremal pixels rather than their edges. TODO: We might want to cache the read data for textures in some external system to reuse it across many patches. Also, it would be good to update that data when the texture changes by watching its hash.
- L570 _protected member_ `TArray<TSharedPtr<const FChannelFieldData>> WeightChannelFields;`
- L571 _protected member_ `TSharedPtr<Utils::TAsyncTransform<Geometry::FDisplacementMap>> FilteredDisplacementMap;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Geometry` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/Modifiers/MeshPartitionWeightUtilityModifier.h` (Public)


#### class `UE::MeshPartition::UWeightUtilityModifier`  
`class UWeightUtilityModifier : public MeshPartition::UModifierComponent`  
_L22-82_
- reflection: `UCLASS(MinimalAPI, PrioritizeCategories = ("Modifier", "Profile"), meta=(BlueprintSpawnableComponent, MegaMeshClassVersion = "1"))`
- inherits: `MeshPartition::UModifierComponent`
- desc: A simple modifier that will write a radial profile with falloff to a weight channel.
- L27 _public prototype_ `UWeightUtilityModifier();`
- L30 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L31 _public prototype_ `virtual TSharedPtr<const UE::MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;`
- L32 _public prototype_ `virtual FGuid GetCodeVersionKey() const override;`
- L39 _protected prototype_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& Dependencies) const override;`
- L45 _protected member_ `float Radius = 1000.f;` — `UPROPERTY(EditAnywhere, Category = Profile)` — Radius of the constant inner disk.
- L51 _protected member_ `float Falloff = 1000.f;` — `UPROPERTY(EditAnywhere, Category = Profile)` — Falloff distance starting from the inner disk.
- L57 _protected member_ `float InnerValue = 1.f;` — `UPROPERTY(EditAnywhere, Category = Profile)` — Weight value within the inner disk.
- L63 _protected member_ `float OuterValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = Profile)` — Weight value at the outside of the falloff region.
- L69 _protected member_ `bool bCosineWeighted = { false };` — `UPROPERTY(EditAnywhere, Category = Profile)` — Multiply the clamped positive cosine between the component Z direction and the mesh normal (front-sidedness factor).
- L75 _protected member_ `float MaxZDistance = 20000.f;` — `UPROPERTY(EditAnywhere, Category = Profile)` — Maximum distance from the component center in Z-direction to affect base region.
- L81 _protected member_ `FName WeightChannelName;` — `UPROPERTY(EditAnywhere, Category = Profile, meta = (GetOptions = "GetMegaMeshDefinitionChannels", NoResetToDefault))` — Target weight channel to write to.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHPARTITIONEDITOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MeshPartition` (scope `UE`)
- L13 _namespace_ `namespace MegaMeshWeightUtilityModifierLocals` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditor/Public/WorldPartitionMeshPartitionBuilder.h` (Public)


#### enum `UE::MeshPartition::EMeshPartitionReuseMode`  
`enum class EMeshPartitionReuseMode`  
_L29-36_
- reflection: `UENUM()`
- L31 _public enumerator_ `ForceRebuild` — slowest: rebuild all compiled sections, even if we don't think it is necessary
- L32 _public enumerator_ `ByModifierHash` — fast:	skip building compiled sections where the modifier cachekey hash has not changed (requires loading the modifiers to calculate their cache keys)
- L33 _public enumerator_ `ByPackageHash` — fastest: does not require loading modifiers. skip building compiled sections where the dependent asset packages (as declared by GatherDependencies) have not changed.
- L34 _public enumerator_ `ValidateHashes` — fast:	runs both package hash and modifier hash paths, and validates their behavior.  Used mainly for debugging.
- L35 _public enumerator_ `Count UMETA(Hidden)`

#### class `UE::MeshPartition::UWorldPartitionMeshPartitionBuilder`  
`class UWorldPartitionMeshPartitionBuilder : public UWorldPartitionBuilder`  
_L46-221_
- reflection: `UCLASS()`
- inherits: `UWorldPartitionBuilder`
- desc: Example Command Line: ProjectName MapName -run=WorldPartitionBuilderCommandlet -SCCProvider=Perforce -Builder=WorldPartitionMeshPartitionBuilder
- L143 _public function_ `virtual bool RequiresCommandletRendering() const override` — UWorldPartitionBuilder interface begin
- L144 _public function_ `virtual ELoadingMode GetLoadingMode() const override`
- L145 _public prototype_ `virtual bool PreRun(UWorld* World, FPackageSourceControlHelper& PackageHelper) override;`
- L146 _public prototype_ `virtual bool RunInternal(UWorld* World, const FCellInfo& InCellInfo, FPackageSourceControlHelper& InPackageHelper) override;`
- L147 _public function_ `virtual bool CanProcessNonPartitionedWorlds() const override`
- L150 _public prototype_ `static bool CanBuildMeshPartitions(const UWorld* InWorld, FName InBuildOption);`
- L151 _public prototype_ `static EEditorBuildResult BuildMeshPartitions(UWorld* InWorld, EMeshPartitionReuseMode ReuseMode);`
- L157 _private prototype_ `bool BuildMeshPartition(const AMeshPartition* InMeshPartition, const FGuid& BuildKey, UE::MeshPartition::FModifierDescriptorCache& DescriptorCache, FSourceControlHelper& InSourceControlHelper);` — Build a MeshPartition
- L166 _private prototype_ `void ExecuteModifierGroupTasks(TIndirectArray<FModifierGroupTask>& InModifierGroupTasks, UWorld* InWorld, const AMeshPartition* InMeshPartition, FSourceControlHelper& InSourceControlHelper);` — Executes and manages all modifier group tasks upon completion. @Param InModifierGroupTasks The modifier group tasks to execute. @param InWorld The current world. @param InMeshPartition The AMeshPartition the modifiers belong to. @param InSourceControlHelper A helper for saving and source control operations.
- L173 _private prototype_ `void LoadActors(const AMeshPartition* InMeshPartition, FModifierGroupTask& InModifierGroupTask);` — Loads the modifier owners. Populating the lookup table and refcounting the loaded modifier owners. @param InMeshPartition The AMeshPartition the modifiers belong to. @param InModifierGroupTask The ModifierGroupTask that needs processing.
- L175 _private prototype_ `void AssignSectionToPlatformDataLayers(MeshPartition::ACompiledSection* InCompiledSection) const;`
- L183 _private prototype_ `void GatherDependenciesAndComputeHashes(FModifierGroupTask& InOutTask, IAssetRegistry& AssetRegistry);` — Gather the set of all package dependencies from the modifiers in the ModifierGroup. @param AssetRegistry the asset registry we use to track recursive dependencies.  Must be up to date before calling this function for correct results. @param ModifierGroup the modifier group to gather dependencies from @return An array of package names for packages containing dependencies of the modifier group, sorted in a deterministic order.
- L191 _private prototype_ `static bool SavePackages(const TArray<UPackage*>& PackagesToSave, FSourceControlHelper& InSourceControlHelper);` — Helper to save a package. @param PackagesToSave The package to save. @param InSourceControlHelper A helper for saving and source control operations. @return
- L199 _private prototype_ `void SaveAndCollectGarbage(UWorld* InWorld, FSourceControlHelper& InSourceControlHelper, FModifierGroupTask& InModifierGroupTask);` — Waits for all compilable before saving and cleaning resources if memory is needed and the resources are not needed anymore. @param InWorld The current world. @param InSourceControlHelper A helper for saving and source control operations. @param InModifierGroupTask The ModifierGroupTask that needs saving.
- L201 _private prototype_ `bool SubmitToSourceControl(UWorld* InWorld);`
- L205 _private member_ `EMeshPartitionReuseMode ReuseMode = EMeshPartitionReuseMode::ByPackageHash;` — `UPROPERTY(meta=(CommandLineArgument))`
- L208 _private member_ `int32 MaxTasksInFlight = 16;` — `UPROPERTY(meta=(CommandLineArgument))`
- L210 _private member_ `TObjectPtr<UWorldPartition> WorldPartition = nullptr;`
- L213 _private member_ `TSet<FGuid> CompiledSectionActorDescGuidsToKeep;` — Build state
- L214 _private member_ `int32 TotalBuiltCompiledSections = 0;`
- L215 _private member_ `int32 TotalFailedCompiledSections = 0;`
- L216 _private member_ `int32 TotalReusedCompiledSections = 0;`
- L217 _private member_ `int32 TotalNumberOfSectionsToBuild = 0;`
- L220 _private member_ `FBuilderModifiedFiles ModifiedFiles;` — Tracks all package files (added / edited / deleted) produced during the build, for source control submission.

#### enum `UE::MeshPartition::UWorldPartitionMeshPartitionBuilder::ETaskState`  
`enum class ETaskState`  
_L50-69_
- L52 _public enumerator_ `Invalid`
- L54 _public enumerator_ `Ready` — Task is ready to execute
- L56 _public enumerator_ `ActorLoaded` — The modifier and base actor are loaded
- L58 _public enumerator_ `LaunchedProcessModifierTask` — Launched the async process modifier task, but the task has not yet started
- L60 _public enumerator_ `ProcessingModifiers` — The task is currently processing the modifiers, building the FDynamicMesh3
- L62 _public enumerator_ `ModifiersProcessed` — Modifiers are processed. Built mesh data is ready
- L64 _public enumerator_ `TransformersLaunched` — The Transformers pipeline is launched and processing.
- L66 _public enumerator_ `TransformersExecuted` — The Transformers pipeline execution is done.
- L68 _public enumerator_ `Completed` — Task's work is done

#### enum `UE::MeshPartition::UWorldPartitionMeshPartitionBuilder::ETaskResult`  
`enum class ETaskResult`  
_L71-81_
- L74 _public enumerator_ `None` — Initial state, not yet complete
- L76 _public enumerator_ `BuildFail` — Failed to build a new compiled section
- L78 _public enumerator_ `BuildSuccess` — Successfully built a new compiled section
- L80 _public enumerator_ `ReuseExisting` — Reused an existing compiled section

#### struct `UE::MeshPartition::UWorldPartitionMeshPartitionBuilder::FModifierGroupTask`  
`struct FModifierGroupTask`  
_L83-139_
- L86 _public member_ `UE::MeshPartition::FModifierGroup ModifierGroup;` — Inputs
- L87 _public member_ `MeshPartition::FBuilderSettings BuilderSettings;`
- L88 _public member_ `MeshPartition::FCompiledSectionBuildInfo BuildInfo;`
- L89 _public member_ `const MeshPartition::FCompiledSectionBuildVariant& BuildVariant;`
- L90 _public member_ `UMeshPartitionEditorComponent* MeshPartitionEditorComponent = nullptr;`
- L91 _public member_ `UWorldPartitionMeshPartitionBuilder& WorldPartitionMeshPartitionBuilder;`
- L96 _public member_ `TArrayView<const FCompiledSectionDescriptor> OldCompiledSectionDescriptors;` — array of pre-existing compiled sections (potentially re-usable for incremental rebuild) NOTE: this is NOT thread safe, and only works because we always synchronously complete this task and deallocate it  before destroying the array this view references.
- L99 _public member_ `MeshPartition::FGridSettings GridSettings;` — Grid configuration for this variant (CellSize=0 = no grid splitting). Set once per variant, before the task loop.
- L102 _public member_ `ETaskResult Result = ETaskResult::None;` — Results
- L105 _public member_ `TArray<MeshPartition::ACompiledSection*> CompiledSections;` — All compiled sections produced for this group (N per WP grid cell; 1 for single-section path)
- L107 _public member_ `TArray<FGuid> ReuseCompiledSectionActorDescGuids;`
- L110 _public member_ `ETaskState State = ETaskState::Invalid;` — internal intermediate state
- L112 _public member_ `TUniquePtr<MeshPartition::FTransformerContext> TransformerContext;`
- L113 _public member_ `UE::Tasks::TTask<FMeshData> ProcessModifierTask;`
- L114 _public member_ `TSharedPtr<MeshPartition::FModifierTaskGraph> ModifierTaskGraph;`
- L116 _public member_ `TArray<UPackage*> ModifiedPackages;`
- L117 _public member_ `TSet<AActor*> ModifierOwners;` — set of actors containing one of our modifier components
- L118 _public member_ `TSet<FWorldPartitionReference> ActorRefs;` — references to world partition actors that must remain loaded while this task is running
- L120 _public function_ `FModifierGroupTask(UE::MeshPartition::FModifierGroup&& InModifierGroup, const MeshPartition::FBuilderSettings& InBuilderSettings, const MeshPartition::FCompiledSectionBuildInfo& InBuildInfo, const MeshPartition::FCompiledSectionBuildVariant& InBuildVariant, UMeshPartitionEditorComponent* InMeshPartitionEditorComponent, UWorldPartitionMeshPartitionBuilder& InWorldPartitionMeshPartitionBuilder, TArrayView<const FCompiledSectionDescriptor> InOldCompiledSectionDescriptors) : ModifierGroup(MoveTemp(InModifierGroup)) , BuilderSettings(InBuilderSettings) , BuildInfo(InBuildInfo) , BuildVariant(InBuildVariant) , MeshPartitionEditorComponent(InMeshPartitionEditorComponent) , WorldPartitionMeshPartitionBuilder(InWorldPartitionMeshPartitionBuilder) , OldCompiledSectionDescriptors(InOldCompiledSectionDescriptors)`
- L130 _public function_ `FModifierGroupTask(const UE::MeshPartition::FModifierGroup& InModifierGroup, const MeshPartition::FBuilderSettings& InBuilderSettings, const MeshPartition::FCompiledSectionBuildInfo& InBuildInfo, const MeshPartition::FCompiledSectionBuildVariant& InBuildVariant, UMeshPartitionEditorComponent* InMeshPartitionEditorComponent, UWorldPartitionMeshPartitionBuilder& InWorldPartitionMeshPartitionBuilder, TArrayView<const FCompiledSectionDescriptor> InOldCompiledSectionDescriptors) : ModifierGroup(InModifierGroup) , BuilderSettings(InBuilderSettings) , BuildInfo(InBuildInfo) , BuildVariant(InBuildVariant) , MeshPartitionEditorComponent(InMeshPartitionEditorComponent) , WorldPartitionMeshPartitionBuilder(InWorldPartitionMeshPartitionBuilder) , OldCompiledSectionDescriptors(InOldCompiledSectionDescriptors)`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MeshPartition` (scope `UE`)
- L40 _prototype_ `ENUM_RANGE_BY_COUNT(UE::MeshPartition::EMeshPartitionReuseMode, UE::MeshPartition::EMeshPartitionReuseMode::Count);` — ENUM_RANGE_BY_COUNT defines a symbol that needs to be declared in the global namespace.
- L42 _namespace_ `namespace UE`
- L42 _namespace_ `namespace MeshPartition` (scope `UE`)
