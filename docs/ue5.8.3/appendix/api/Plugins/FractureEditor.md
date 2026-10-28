# Plugins / FractureEditor

- module root: `Plugins/Experimental/ChaosEditor/Source/FractureEditor`
- headers: 42; symbols: 1879
- symbol kinds: class=116, delegate=7, enum=23, enumerator=85, function=223, macro=2, member=575, namespace=8, prototype=790, struct=16, typedef=18, variable=16
- PrivateDependencyModuleNames: Chaos, ContentBrowserData, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, DeveloperSettings, DynamicMesh, EditorFramework, EditorScriptingUtilities, Engine, FractureEngine, GeometryCollectionEditor, GeometryCollectionEngine, GeometryCore, GeometryFramework, InputCore, LevelEditor, MeshDescription, ModelingComponents, ModelingOperators, PhysicsCore, PlanarCut, PropertyEditor, Slate, SlateCore, StaticMeshDescription, ToolMenus, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: Core, EditorInteractiveToolsFramework, InteractiveToolsFramework, Voronoi

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureEditorCommands.h` (Private)


#### class `FFractureEditorCommands`  
`class FFractureEditorCommands : public TCommands<FFractureEditorCommands>`  
_L6-106_
- inherits: `TCommands<FFractureEditorCommands>`
- L9 _public prototype_ `FFractureEditorCommands();`
- L11 _public prototype_ `virtual void RegisterCommands() override;`
- L19 _protected member_ `TArray<FToolCommandInfo> RegisteredTools;` — Tool commands listed below are stored in this list
- L25 _public prototype_ `TSharedPtr<FUICommandInfo> FindToolByName(const FString& Name, bool& bFound) const;` — Find Tool start-command below by registered name (tool icon name in Mode palette)
- L28 _public member_ `TSharedPtr< FUICommandInfo > SelectAll;` — Selection Commands
- L29 _public member_ `TSharedPtr< FUICommandInfo > SelectNone;`
- L30 _public member_ `TSharedPtr< FUICommandInfo > SelectNeighbors;`
- L31 _public member_ `TSharedPtr< FUICommandInfo > SelectParent;`
- L32 _public member_ `TSharedPtr< FUICommandInfo > SelectChildren;`
- L33 _public member_ `TSharedPtr< FUICommandInfo > SelectSiblings;`
- L34 _public member_ `TSharedPtr< FUICommandInfo > SelectAllInLevel;`
- L35 _public member_ `TSharedPtr< FUICommandInfo > SelectInvert;`
- L36 _public member_ `TSharedPtr< FUICommandInfo > SelectLeaves;`
- L37 _public member_ `TSharedPtr< FUICommandInfo > SelectClusters;`
- L38 _public member_ `TSharedPtr< FUICommandInfo > SelectCustom;`
- L41 _public member_ `TSharedPtr< FUICommandInfo > ToggleShowBoneColors;` — View Settings
- L42 _public member_ `TSharedPtr< FUICommandInfo > ViewUpOneLevel;`
- L43 _public member_ `TSharedPtr< FUICommandInfo > ViewDownOneLevel;`
- L44 _public member_ `TSharedPtr< FUICommandInfo > ExplodeMore;`
- L45 _public member_ `TSharedPtr< FUICommandInfo > ExplodeLess;`
- L48 _public member_ `TSharedPtr< FUICommandInfo > CancelTool;` — Tool exit
- L51 _public member_ `TSharedPtr< FUICommandInfo > AutoCluster;` — Cluster Commands
- L52 _public member_ `TSharedPtr< FUICommandInfo > ClusterMagnet;`
- L53 _public member_ `TSharedPtr< FUICommandInfo > Cluster;`
- L54 _public member_ `TSharedPtr< FUICommandInfo > Uncluster;`
- L55 _public member_ `TSharedPtr< FUICommandInfo > Flatten;`
- L56 _public member_ `TSharedPtr< FUICommandInfo > MoveUp;`
- L57 _public member_ `TSharedPtr< FUICommandInfo > ClusterMerge;`
- L60 _public member_ `TSharedPtr< FUICommandInfo > DeleteBranch;` — Edit Commands
- L61 _public member_ `TSharedPtr< FUICommandInfo > Hide;`
- L62 _public member_ `TSharedPtr< FUICommandInfo > Unhide;`
- L63 _public member_ `TSharedPtr< FUICommandInfo > MergeSelected;`
- L64 _public member_ `TSharedPtr< FUICommandInfo > SplitSelected;`
- L67 _public member_ `TSharedPtr< FUICommandInfo > GenerateAsset;` — Generate Commands
- L68 _public member_ `TSharedPtr< FUICommandInfo > ResetAsset;`
- L71 _public member_ `TSharedPtr< FUICommandInfo > AddEmbeddedGeometry;` — Embed Commands
- L72 _public member_ `TSharedPtr< FUICommandInfo > AutoEmbedGeometry;`
- L73 _public member_ `TSharedPtr< FUICommandInfo > FlushEmbeddedGeometry;`
- L76 _public member_ `TSharedPtr< FUICommandInfo > AutoUV;` — UV Commands
- L79 _public member_ `TSharedPtr< FUICommandInfo > Materials;` — Material Commands
- L82 _public member_ `TSharedPtr< FUICommandInfo > Uniform;` — Fracture Commands
- L83 _public member_ `TSharedPtr< FUICommandInfo > Radial;`
- L84 _public member_ `TSharedPtr< FUICommandInfo > Clustered;`
- L85 _public member_ `TSharedPtr< FUICommandInfo > CustomVoronoi;`
- L86 _public member_ `TSharedPtr< FUICommandInfo > Planar;`
- L87 _public member_ `TSharedPtr< FUICommandInfo > Slice;`
- L88 _public member_ `TSharedPtr< FUICommandInfo > Brick;`
- L89 _public member_ `TSharedPtr< FUICommandInfo > Texture;`
- L90 _public member_ `TSharedPtr< FUICommandInfo > Mesh;`
- L93 _public member_ `TSharedPtr< FUICommandInfo > RecomputeNormals;` — Cleanup Commands
- L94 _public member_ `TSharedPtr< FUICommandInfo > Resample;`
- L95 _public member_ `TSharedPtr< FUICommandInfo > ConvertToMesh;`
- L96 _public member_ `TSharedPtr< FUICommandInfo > Validate;`
- L97 _public member_ `TSharedPtr< FUICommandInfo > MakeConvex;`
- L98 _public member_ `TSharedPtr< FUICommandInfo > Proximity;`
- L99 _public member_ `TSharedPtr< FUICommandInfo > FixTinyGeo;`
- L100 _public member_ `TSharedPtr< FUICommandInfo > SplitIslands;`
- L103 _public member_ `TSharedPtr< FUICommandInfo > SetInitialDynamicState;` — Property Commands
- L104 _public member_ `TSharedPtr< FUICommandInfo > SetRemoveOnBreak;`

#### struct `FFractureEditorCommands::FToolCommandInfo`  
`struct FToolCommandInfo`  
_L14-18_
- L16 _public member_ `FText ToolUIName;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> ToolCommand;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureEditorStyle.h` (Private)


#### class `FFractureEditorStyle`  
`class FFractureEditorStyle : public FSlateStyleSet`  
_L11-24_
- inherits: `FSlateStyleSet`
- desc: Slate style set that defines all the styles for the take recorder UI
- L15 _public member_ `static FName StyleName;`
- L18 _public prototype_ `static FFractureEditorStyle& Get();` — Access the singleton instance for this style set
- L22 _private prototype_ `FFractureEditorStyle();`
- L23 _private prototype_ `~FFractureEditorStyle();`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolAutoCluster.h` (Private)


#### enum `EFractureAutoClusterMode`  
`enum class EFractureAutoClusterMode : uint8`  
_L12-24_
- reflection: `UENUM()`
- desc: Note: Only Voronoi-based auto-clustering is currently supported
- L15 _public enumerator_ `BoundingBox UMETA(DisplayName = "Bounding Box")` — Overlapping bounding box
- L18 _public enumerator_ `Proximity UMETA(DisplayName = "Proximity")` — GC connectivity
- L21 _public enumerator_ `Distance UMETA(DisplayName = "Distance")` — Distance
- L23 _public enumerator_ `Voronoi UMETA(DisplayName = "Voronoi")`

#### enum `EClusterSizeMethod`  
`enum class EClusterSizeMethod : uint8`  
_L27-37_
- reflection: `UENUM()`
- L30 _public enumerator_ `ByNumber` — Cluster by specifying an absolute number of clusters
- L32 _public enumerator_ `ByFractionOfInput` — Cluster by specifying a fraction of the number of input bones
- L34 _public enumerator_ `BySize` — Cluster by specifying the density of the input bones
- L36 _public enumerator_ `ByGrid` — Cluster by a grid layout

#### class `UFractureAutoClusterSettings`  
`class UFractureAutoClusterSettings : public UFractureToolSettings`  
_L41-112_
- reflection: `UCLASS(DisplayName = "Auto Cluster", Category = "FractureTools")`
- inherits: `UFractureToolSettings`
- L46 _public function_ `UFractureAutoClusterSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L51 _public member_ `EFractureAutoClusterMode AutoClusterMode_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Simplified interface now only supports Voronoi clustering."))`
- L55 _public member_ `EClusterSizeMethod ClusterSizeMethod = EClusterSizeMethod::ByNumber;` — `UPROPERTY(EditAnywhere, Category = ClusterSize)` — How to choose the size of the clusters to create
- L59 _public member_ `uint32 SiteCount=10;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (DisplayName = "Cluster Sites", UIMin = "2", UIMax = "5000", ClampMin = "1", EditCondition = "ClusterSizeMethod == EClusterSizeMethod::ByNumber", EditConditionHides))` — Use a Voronoi diagram with this many Voronoi sites as a guide for deciding cluster boundaries
- L63 _public member_ `float SiteCountFraction = .25;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (DisplayName = "Cluster Fraction", ClampMin = "0", ClampMax = ".5", EditCondition = "ClusterSizeMethod == EClusterSizeMethod::ByFractionOfInput", EditConditionHides))` — Choose the number of Voronoi sites used for clustering as a fraction of the number of child bones to process
- L67 _public member_ `float SiteSize = 1;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (DisplayName = "Cluster Size", UIMin = ".01", UIMax = "100", ClampMin = ".0001", ClampMax = "10000", EditCondition = "ClusterSizeMethod == EClusterSizeMethod::BySize", EditConditionHides))` — Choose the Edge-Size of the cube used to groups bones under a cluster (in cm).
- L71 _public member_ `int ClusterGridWidth = 2;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (ClampMin = "1", UIMax = "20", EditCondition = "ClusterSizeMethod == EClusterSizeMethod::ByGrid", EditConditionHides))` — Choose the number of cluster sites to distribute along the X axis
- L75 _public member_ `int ClusterGridDepth = 2;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (ClampMin = "1", UIMax = "20", EditCondition = "ClusterSizeMethod == EClusterSizeMethod::ByGrid", EditConditionHides))` — Choose the number of cluster sites to distribute along the Y axis
- L79 _public member_ `int ClusterGridHeight = 2;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (ClampMin = "1", UIMax = "20", EditCondition = "ClusterSizeMethod == EClusterSizeMethod::ByGrid", EditConditionHides))` — Choose the number of cluster sites to distribute along the Z axis
- L83 _public member_ `bool bShowGridLines = true;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (EditCondition = "ClusterSizeMethod == EClusterSizeMethod::ByGrid", EditConditionHides))` — If true, show the cluster grid boundary lines.
- L87 _public member_ `float MinimumSize = 0;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (ClampMin = "0"))` — If a cluster has volume less than this value (in cm) cubed, then the auto-cluster process will attempt to merge it into a neighboring cluster.
- L91 _public member_ `int DriftIterations = 0;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (DisplayName = "Drift Iterations", ClampMin = "0", UIMax = "5", EditCondition = "ClusterSizeMethod == EClusterSizeMethod::ByGrid", EditConditionHides))` — For a grid distribution, optionally iteratively recenter the grid points to the center of the cluster geometry (technically: applying K-Means iterations) to balance the shape and distribution of the clusters
- L95 _public member_ `bool bPreferConvexity = false;` — `UPROPERTY(EditAnywhere, Category = AutoCluster, meta = (EditCondition = "ClusterSizeMethod != EClusterSizeMethod::ByGrid"))` — Whether to favor clusters that have a convex shape. (Note: Does not support ByGrid clustering.)
- L99 _public member_ `double ConcavityTolerance = 0;` — `UPROPERTY(EditAnywhere, Category = AutoCluster, meta = (EditCondition = "bPreferConvexity && ClusterSizeMethod != EClusterSizeMethod::ByGrid"))` — If > 0, cube root of maximum concave volume to add per cluster (ignoring concavity of individual parts)
- L103 _public member_ `bool bEnforceConnectivity=true;` — `UPROPERTY(EditAnywhere, Category = AutoCluster, meta = (DisplayName = "Enforce Cluster Connectivity"))` — If true, bones will only be added to the same cluster if they are physically connected (either directly, or via other bones in the same cluster)
- L107 _public member_ `bool bEnforceSiteParameters = true;` — `UPROPERTY(EditAnywhere, Category = AutoCluster, meta = (EditCondition = "bEnforceConnectivity == true && ClusterSizeMethod != EClusterSizeMethod::ByGrid && !bPreferConvexity"))` — If true, make sure the site parameters are matched as close as possible ( bEnforceConnectivity can make the number of site larger than the requested input may produce without it )
- L111 _public member_ `bool bAvoidIsolated = true;` — `UPROPERTY(EditAnywhere, Category = AutoCluster)` — If true, prevent the creation of clusters with only a single child, skipping creation of a new cluster in such cases.

#### class `UFractureToolAutoCluster`  
`class UFractureToolAutoCluster: public UFractureModalTool`  
_L116-155_
- reflection: `UCLASS(DisplayName="AutoCluster", Category="FractureTools")`
- inherits: `UFractureModalTool`
- L121 _public prototype_ `UFractureToolAutoCluster(const FObjectInitializer& ObjInit);`
- L124 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L125 _public prototype_ `virtual FText GetTooltipText() const override;`
- L126 _public prototype_ `virtual FText GetApplyText() const override;`
- L127 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L128 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L129 _public prototype_ `virtual void RegisterUICommand( FFractureEditorCommands* BindingContext );`
- L130 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L131 _public prototype_ `void DrawBox(FPrimitiveDrawInterface* PDI, FVector Center, float SideLength);`
- L133 _public prototype_ `virtual void FractureContextChanged() override;`
- L135 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L138 _public member_ `TObjectPtr<UFractureAutoClusterSettings> AutoClusterSettings;` — `UPROPERTY(EditAnywhere, Category = AutoCluster)`
- L141 _protected function_ `virtual void ClearVisualizations() override`
- L152 _private member_ `TArray<FVector> ShowGridPoints;`
- L153 _private member_ `TArray<TPair<FVector, FVector>> ShowGridLines;`
- L154 _private member_ `FVisualizationMappings GridPointsMappings, GridLinesMappings;`
- L154 _private member_ `FVisualizationMappings GridPointsMappings, GridLinesMappings;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolBackgroundTask.h` (Private)


#### class `UE::Fracture::TGeometryCollectionOperator`  
`template<typename ResultType> class TGeometryCollectionOperator : public UE::Geometry::TGenericDataOperator<ResultType>`  
_L18-48_
- inherits: `UE::Geometry::TGenericDataOperator<ResultType>`
- desc: Base class for background operators that update geometry collections (e.g. to fracture in a background thread)
- L21 _public member_ `int ResultGeometryIndex = -1;`
- L22 _public member_ `TUniquePtr<FGeometryCollection> CollectionCopy;`
- L24 _public function_ `TGeometryCollectionOperator(const FGeometryCollection& SourceCollection) : UE::Geometry::TGenericDataOperator<ResultType>(false)`
- L30 _public prototype_ `virtual ~TGeometryCollectionOperator() = default;`
- L32 _public function_ `virtual int GetResultGeometryIndex()`
- L38 _public function_ `virtual void OnSuccess(ResultType& Collection)` — Post-process the geometry collection on success
- L44 _public function_ `virtual void SetSuccessIndex()` — For operators where there is no geometry index to report, set a generic success value

#### class `UE::Fracture::FGeometryCollectionFractureOperator`  
`class FGeometryCollectionFractureOperator : public FGeometryCollectionOperator`  
_L54-71_
- inherits: `FGeometryCollectionOperator`
- desc: Fracture-specific operators also clear proximity on success
- L57 _public function_ `FGeometryCollectionFractureOperator(const FGeometryCollection& SourceCollection) : FGeometryCollectionOperator(SourceCollection)`
- L61 _public prototype_ `virtual ~FGeometryCollectionFractureOperator() = default;`
- L63 _public function_ `virtual void OnSuccess(FGeometryCollection& Collection) override`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Fracture` (scope `UE`)
- L51 _typedef_ `using FGeometryCollectionOperator = TGeometryCollectionOperator<FGeometryCollection>;` (scope `UE::Fracture`) — Most operators will also have FGeometryCollection as their result
- L74 _typedef_ `template<class OpType> using TBackgroundOpExecuter = UE::Geometry::FAsyncTaskExecuterWithProgressCancel<UE::Geometry::TModelingOpTask<OpType>>;` (scope `UE::Fracture`)
- L81 _function_ `template<class OpType> TUniquePtr<TBackgroundOpExecuter<OpType>> StartBackgroundTask(TUniquePtr<OpType>&& NewOp)` (scope `UE::Fracture`) — Start a background task Note: If automatically starting tasks in response to user actions, consider using a timeout to prevent launching too many tasks at once (TODO: consider encapsulating the timeout logic in a small struct here)
- L91 _function_ `template<class OpType> bool TickBackgroundTask(TUniquePtr<TBackgroundOpExecuter<OpType>>& BackgroundTask, bool bCancel, TFunctionRef<bool(TUniquePtr<typename OpType::ResultTypeName>&&)> SuccessCallback)` (scope `UE::Fracture`) — Tick a background task started by StartBackgroundTask (above) @return the result of SuccessCallback if the task has completed, false otherwise
- L127 _function_ `template<class OpType> void CancelBackgroundTask(TUniquePtr<TBackgroundOpExecuter<OpType>>& BackgroundTask)` (scope `UE::Fracture`) — Cancel the background task (or ignore if the pointer is empty)
- L138 _function_ `template<class GeometryCollectionOpType, typename ResultType> int RunCancellableGeometryCollectionOpGeneric(ResultType& ToUpdate, TFunctionRef<void(ResultType&, ResultType&)> AssignResult, TUniquePtr<GeometryCollectionOpType>&& NewOp, FText DefaultMessage, float DialogDelay = .5)` (scope `UE::Fracture`) — Run a blocking geometry collection op, but with a responsive cancel option
- L140 _typedef_ `using FGeometryCollectionTask = UE::Geometry::TModelingOpTask<GeometryCollectionOpType>;` (scope `UE::Fracture::RunCancellableGeometryCollectionOpGeneric`)
- L141 _typedef_ `using FExecuter = UE::Geometry::FAsyncTaskExecuterWithProgressCancel<FGeometryCollectionTask>;` (scope `UE::Fracture::RunCancellableGeometryCollectionOpGeneric`)
- L199 _function_ `template<class GeometryCollectionOpType> int RunCancellableGeometryCollectionOp(FGeometryCollection& ToUpdate, TUniquePtr<GeometryCollectionOpType>&& NewOp, FText DefaultMessage, float DialogDelay = .5)` (scope `UE::Fracture`)
- L203 _function_ `` (scope `UE::Fracture::RunCancellableGeometryCollectionOp`)

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolBrick.h` (Private)


#### enum `EFractureBrickBond`  
`enum class EFractureBrickBond : uint8`  
_L26-37_
- reflection: `UENUM()`
- desc: Brick Stacking Pattern
- L28 _public enumerator_ `Stretcher UMETA(DisplayName = "Stretcher")`
- L30 _public enumerator_ `Stack UMETA(DisplayName = "Stack")`
- L32 _public enumerator_ `English UMETA(DisplayName = "English")`
- L34 _public enumerator_ `Header UMETA(DisplayName = "Header")`
- L36 _public enumerator_ `Flemish UMETA(DisplayName = "Flemish")`

#### class `UFractureBrickSettings`  
`class UFractureBrickSettings : public UFractureToolSettings`  
_L41-77_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- L46 _public function_ `UFractureBrickSettings(const FObjectInitializer& ObjInit) : Super(ObjInit) , Bond(EFractureBrickBond::Stretcher) , BrickLength(194.f) , BrickHeight(57.f) , BrickDepth(92.f)`
- L56 _public member_ `EFractureBrickBond Bond;` — `UPROPERTY(EditAnywhere, Category = Brick)` — The brick bond pattern defines how the bricks are arranged
- L68 _public member_ `float BrickLength;` — `UPROPERTY(EditAnywhere, Category = Brick, meta = (UIMin = "0.1", UIMax = "500.0", ClampMin = "0.001"))` — Brick length (in cm)
- L72 _public member_ `float BrickHeight;` — `UPROPERTY(EditAnywhere, Category = Brick, meta = (UIMin = "0.1", UIMax = "500.0", ClampMin = "0.001"))` — Brick height (in cm)
- L76 _public member_ `float BrickDepth;` — `UPROPERTY(EditAnywhere, Category = Brick, meta = (UIMin = "0.1", UIMax = "500.0", ClampMin = "0.001"))` — Brick depth (in cm)

#### class `UFractureToolBrick`  
`class UFractureToolBrick : public UFractureToolCutterBase`  
_L81-130_
- reflection: `UCLASS(DisplayName="Brick", Category="FractureTools")`
- inherits: `UFractureToolCutterBase`
- L86 _public prototype_ `UFractureToolBrick(const FObjectInitializer& ObjInit);`
- L89 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L90 _public prototype_ `virtual FText GetTooltipText() const override;`
- L91 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L92 _public prototype_ `virtual void RegisterUICommand( FFractureEditorCommands* BindingContext ) override;`
- L93 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L94 _public prototype_ `void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L95 _public prototype_ `virtual void FractureContextChanged() override;`
- L96 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L97 _public prototype_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override;`
- L99 _public prototype_ `void GenerateBrickTransforms(const FBox& Bounds);`
- L101 _public function_ `virtual void ConfigureCutterSettings() override`
- L108 _protected function_ `virtual void ClearVisualizations() override`
- L120 _private member_ `TObjectPtr<UFractureBrickSettings> BrickSettings;` — `UPROPERTY()`
- L122 _private prototype_ `void AddBoxEdges(const FVector& Min, const FVector& Max);`
- L124 _private prototype_ `void UpdateBrickTransforms();`
- L126 _private member_ `TArray<FTransform> BrickTransforms;`
- L127 _private member_ `TArray<TTuple<FVector, FVector>> Edges;`
- L128 _private member_ `TArray<TTuple<FVector, FVector>> Boxes;`
- L129 _private member_ `FVisualizationMappings BricksMappings, EdgesMappings;`
- L129 _private member_ `FVisualizationMappings BricksMappings, EdgesMappings;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolClusterCutter.h` (Private)


#### class `UFractureClusterCutterSettings`  
`class UFractureClusterCutterSettings : public UFractureToolSettings`  
_L13-62_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- L18 _public function_ `UFractureClusterCutterSettings(const FObjectInitializer& ObjInit) : Super(ObjInit) , NumberClustersMin(8) , NumberClustersMax(8) , SitesPerClusterMin(2) , SitesPerClusterMax(30) , ClusterRadiusFractionMin(0.1f) , ClusterRadiusFractionMax(0.2f) , ClusterRadiusOffset(0.0f)`
- L31 _public member_ `int32 NumberClustersMin;` — `UPROPERTY(EditAnywhere, Category = ClusterVoronoi, meta = (DisplayName = "Min Num Clusters", UIMin = "1", UIMax = "200", ClampMin = "1"))` — Minimum number of clusters of Voronoi sites to create. The amount of clusters created will be chosen at random between Min and Max
- L35 _public member_ `int32 NumberClustersMax;` — `UPROPERTY(EditAnywhere, Category = ClusterVoronoi, meta = (DisplayName = "Max Num Clusters", UIMin = "1", UIMax = "200", ClampMin = "1"))` — Maximum number of clusters of Voronoi sites to create. The amount of clusters created will be chosen at random between Min and Max
- L39 _public member_ `int32 SitesPerClusterMin;` — `UPROPERTY(EditAnywhere, Category = ClusterVoronoi, meta = (DisplayName = "Min Sites Per Cluster", UIMin = "0", UIMax = "200", ClampMin = "0"))` — Minimum number of Voronoi sites per cluster. The amount of sites in each cluster will be chosen at random between Min and Max
- L43 _public member_ `int32 SitesPerClusterMax;` — `UPROPERTY(EditAnywhere, Category = ClusterVoronoi, meta = (DisplayName = "Max Sites Per Cluster", UIMin = "0", UIMax = "200", ClampMin = "0"))` — Maximum number of Voronoi sites per cluster. The amount of sites in each cluster will be chosen at random between Min and Max
- L50 _public member_ `float ClusterRadiusFractionMin;` — `UPROPERTY(EditAnywhere, Category = ClusterVoronoi, meta = (DisplayName = "Min Dist from Center (as Frac of Bounds)", UIMin = "0.0", UIMax = "1.0"))` — Minimum cluster radius (as fraction of the overall Voronoi diagram size). Cluster Radius Offset will be added to this Each Voronoi site will be placed at least this far (plus the Cluster Radius Offset) from its cluster center
- L57 _public member_ `float ClusterRadiusFractionMax;` — `UPROPERTY(EditAnywhere, Category = ClusterVoronoi, meta = (DisplayName = "Max Dist from Center (as Frac of Bounds)", UIMin = "0.0", UIMax = "1.0"))` — Maximum cluster radius (as fraction of the overall Voronoi diagram size). Cluster Radius Offset will be added to this Each Voronoi site will be placed at most this far (plus the Cluster Radius Offset) from its cluster center
- L61 _public member_ `float ClusterRadiusOffset;` — `UPROPERTY(EditAnywhere, Category = ClusterVoronoi)` — Cluster radius offset (in cm). This offset will be added to the 'Min/Max Dist from Center' distance

#### class `UFractureToolClusterCutter`  
`class UFractureToolClusterCutter : public UFractureToolVoronoiCutterBase`  
_L66-88_
- reflection: `UCLASS(DisplayName="Cluster Voronoi", Category="FractureTools")`
- inherits: `UFractureToolVoronoiCutterBase`
- L71 _public prototype_ `UFractureToolClusterCutter(const FObjectInitializer& ObjInit);`
- L74 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L75 _public prototype_ `virtual FText GetTooltipText() const override;`
- L76 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L77 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L79 _public prototype_ `virtual void RegisterUICommand( FFractureEditorCommands* BindingContext ) override;`
- L83 _public member_ `TObjectPtr<UFractureClusterCutterSettings> ClusterSettings;` — `UPROPERTY(EditAnywhere, Category = Cluster)`
- L86 _protected prototype_ `void GenerateVoronoiSites(const FFractureToolContext& Context, TArray<FVector>& Sites) override;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolClusterMagnet.h` (Private)


#### class `UFractureClusterMagnetSettings`  
`class UFractureClusterMagnetSettings : public UFractureToolSettings`  
_L19-33_
- reflection: `UCLASS(DisplayName = "Cluster Magnet", Category = "FractureTools")`
- inherits: `UFractureToolSettings`
- L24 _public function_ `UFractureClusterMagnetSettings(const FObjectInitializer& ObjInit) : Super(ObjInit) , Iterations(1)`
- L31 _public member_ `uint32 Iterations;` — `UPROPERTY(EditAnywhere, Category = ClusterMagnet, meta = (DisplayName = "Iterations", UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "500"))` — How widely to search for neighboring bones to add to the new clusters: When Iterations is 1, only direct neighbors of the selected bones can be added to the new clusters; increasing Iterations allows additional layers of neighbors-of-neighbors to be added

#### class `UFractureToolClusterMagnet`  
`class UFractureToolClusterMagnet : public UFractureModalTool`  
_L37-59_
- reflection: `UCLASS(DisplayName = "ClusterMagnet", Category = "FractureTools")`
- inherits: `UFractureModalTool`
- L42 _public typedef_ `using FGeometryCollectionPtr = TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe>;`
- L44 _public prototype_ `UFractureToolClusterMagnet(const FObjectInitializer& ObjInit);`
- L47 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L48 _public prototype_ `virtual FText GetTooltipText() const override;`
- L49 _public prototype_ `virtual FText GetApplyText() const override;`
- L50 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L51 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L52 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext);`
- L54 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L57 _public member_ `TObjectPtr<UFractureClusterMagnetSettings> ClusterMagnetSettings;` — `UPROPERTY(EditAnywhere, Category = AutoCluster)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L13 _typedef_ `using FParticles = TParticles<FReal, 3>;` (scope `Chaos`)

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolClustering.h` (Private)


#### class `UFractureToolFlattenAll`  
`class UFractureToolFlattenAll : public UFractureActionTool`  
_L11-24_
- reflection: `UCLASS(DisplayName = "Flatten All", Category = "FractureTools")`
- inherits: `UFractureActionTool`
- L16 _public function_ `UFractureToolFlattenAll(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L19 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L20 _public prototype_ `virtual FText GetTooltipText() const override;`
- L21 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L22 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L23 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolCluster`  
`class UFractureToolCluster : public UFractureActionTool`  
_L28-41_
- reflection: `UCLASS(DisplayName = "Cluster", Category = "FractureTools")`
- inherits: `UFractureActionTool`
- L33 _public function_ `UFractureToolCluster(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L36 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L37 _public prototype_ `virtual FText GetTooltipText() const override;`
- L38 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L39 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L40 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolUncluster`  
`class UFractureToolUncluster : public UFractureActionTool`  
_L45-58_
- reflection: `UCLASS(DisplayName = "Uncluster", Category = "FractureTools")`
- inherits: `UFractureActionTool`
- L50 _public function_ `UFractureToolUncluster(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L53 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L54 _public prototype_ `virtual FText GetTooltipText() const override;`
- L55 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L56 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L57 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolMoveUp`  
`class UFractureToolMoveUp : public UFractureActionTool`  
_L62-75_
- reflection: `UCLASS(DisplayName = "MoveUp", Category = "FractureTools")`
- inherits: `UFractureActionTool`
- L67 _public function_ `UFractureToolMoveUp(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L70 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L71 _public prototype_ `virtual FText GetTooltipText() const override;`
- L72 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L73 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L74 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolClusterMerge`  
`class UFractureToolClusterMerge : public UFractureActionTool`  
_L79-92_
- reflection: `UCLASS(DisplayName = "ClusterMerge", Category = "FractureTools")`
- inherits: `UFractureActionTool`
- L84 _public function_ `UFractureToolClusterMerge(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L87 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L88 _public prototype_ `virtual FText GetTooltipText() const override;`
- L89 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L90 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L91 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolContext.h` (Private)


#### class `FFractureToolContext`  
`class FFractureToolContext`  
_L12-83_
- L16 _public typedef_ `using FGeometryCollectionPtr = TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe>;`
- L19 _public prototype_ `FFractureToolContext(UGeometryCollectionComponent* InGeometryCollectionComponent);` — Generate a tool context based on the bone selection of the specified GeometryCollectionComponent.
- L22 _public prototype_ `void Sanitize(bool bFavorParents = true);` — @param bFavorParents	If true, when a child and its (grand)parent are both selected, only include the top-level bone in the sanitized selection
- L23 _public prototype_ `void ConvertSelectionToLeafNodes();`
- L24 _public prototype_ `void ConvertSelectionToRigidNodes();`
- L25 _public prototype_ `void ConvertSelectionToEmbeddedGeometryNodes();`
- L26 _public prototype_ `void ConvertSelectionToClusterNodes();`
- L27 _public prototype_ `void FilterSelectionBySimulationType(FGeometryCollection::ESimulationTypes KeepSimulationType);`
- L28 _public prototype_ `void ConvertSelectionToLevel(int32 TargetLevel, bool bAllowSelectChildren, bool bAllowSelectParents);`
- L29 _public prototype_ `void RemoveChildrenOfSelectedNodesFromSelection();`
- L30 _public prototype_ `void ConvertEmbeddedSelectionToParents();`
- L31 _public prototype_ `void RemoveRootNodes();`
- L33 _public prototype_ `void RandomReduceSelection(float ProbToKeep);` — @param ProbToKeep The chance to keep each bone in the selection
- L35 _public function_ `const TArray<int32>& GetSelection() const`
- L36 _public function_ `TArray<int32>& GetSelection()`
- L37 _public function_ `void SetSelection(const TArray<int32>& NewSelection)`
- L44 _public function_ `UGeometryCollectionComponent* GetGeometryCollectionComponent() const`
- L45 _public function_ `FGeometryCollectionPtr GetGeometryCollection() const`
- L46 _public function_ `UGeometryCollection* GetFracturedGeometryCollection() const`
- L49 _public prototype_ `TMap<int32, TArray<int32>> GetClusteredSelections();` — Return selection in sibling groups
- L51 _public function_ `FBox GetWorldBounds() const`
- L52 _public function_ `FBox GetBounds() const`
- L53 _public function_ `void SetBounds(FBox& InBounds)`
- L54 _public function_ `int32 GetSeed() const`
- L55 _public function_ `void SetSeed(int32 InSeed)`
- L56 _public function_ `FTransform GetTransform() const`
- L58 _public function_ `bool IsValid() const`
- L60 _public prototype_ `void GenerateGuids(int32 StartIdx);`
- L63 _private prototype_ `bool HasSelectedAncestor(int32 Index) const;`
- L64 _private function_ `bool IsValidBone(int32 Index) const`
- L68 _private prototype_ `void ConvertSelectionToLeafNodes(int32 Index, TArray<int32>& LeafSelection);`
- L69 _private prototype_ `void ConvertSelectionToRigidNodes(int32 Index, TArray<int32>& RigidSelection);`
- L70 _private prototype_ `void ConvertSelectionToEmbeddedGeometryNodes(int32 Index, TArray<int32>& EmbeddedSelection);`
- L73 _private member_ `TArray<int32> SelectedBones;`
- L74 _private member_ `FGeometryCollectionPtr GeometryCollection;`
- L75 _private member_ `UGeometryCollectionComponent* GeometryCollectionComponent;`
- L76 _private member_ `UGeometryCollection* FracturedGeometryCollection;`
- L79 _private member_ `FTransform Transform;` — Fracture specific members
- L80 _private member_ `FBox Bounds;`
- L81 _private member_ `int32 RandomSeed;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolConvert.h` (Private)


#### class `UFractureConvertSettings`  
`class UFractureConvertSettings : public UFractureToolSettings`  
_L14-43_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings related to geometry collection -> static mesh conversion
- L20 _public function_ `UFractureConvertSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L26 _public member_ `bool bPromptForBaseName = true;` — `UPROPERTY(EditAnywhere, Category = AssetSettings)` — Whether to prompt user for a location and base name for the generated meshes, or automatically place them next to the source geometry collections
- L30 _public member_ `bool bPerBone = true;` — `UPROPERTY(EditAnywhere, Category = AssetSettings)` — Whether to generate a separate mesh for each bone, or one combined mesh
- L34 _public member_ `bool bCenterPivots = false;` — `UPROPERTY(EditAnywhere, Category = GeometrySettings)` — Whether to center the pivot for each mesh, or use the pivot from the geometry collection
- L38 _public member_ `bool bPlaceInWorld = true;` — `UPROPERTY(EditAnywhere, Category = ActorSettings)` — Whether to place new static mesh actors in the level
- L42 _public member_ `bool bSelectNewActors = false;` — `UPROPERTY(EditAnywhere, Category = ActorSettings, meta = (EditCondition = "bPlaceInWorld"))` — Whether to select new static mesh actors

#### class `UFractureReimportSettings`  
`class UFractureReimportSettings : public UFractureToolSettings`  
_L47-60_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings related to geometry collection -> static mesh conversion
- L54 _public member_ `bool bOddMaterialsAreInternal = true;` — `UPROPERTY(EditAnywhere, Category = ReimportSettings)` — If checked, materials will be updated on export to ensure that odd-numbered material IDs correspond to internal faces, and this will be used on re-import to assign correct material IDs

#### class `UFractureToolConvert`  
`class UFractureToolConvert : public UFractureModalTool`  
_L63-105_
- reflection: `UCLASS(DisplayName = "Convert Tool", Category = "FractureTools")`
- inherits: `UFractureModalTool`
- L68 _public prototype_ `UFractureToolConvert(const FObjectInitializer& ObjInit);`
- L75 _public prototype_ `virtual FText GetDisplayText() const override;` — This is the Text that will appear on the tool button to execute the tool
- L76 _public prototype_ `virtual FText GetTooltipText() const override;`
- L78 _public function_ `virtual FText GetApplyText() const override` — This is the Text that will appear on the button to execute the fracture
- L79 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L80 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L81 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L82 _public prototype_ `virtual void FractureContextChanged() override;`
- L83 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L85 _public prototype_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override;` — Executes function that generates new geometry. Returns the first new geometry index.
- L86 _public prototype_ `virtual bool CanExecute() const override;`
- L87 _public function_ `virtual bool ExecuteUpdatesShape() const override`
- L91 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L94 _public prototype_ `const TSharedPtr<FUICommandInfo>& GetUICommandInfo() const;` — Gets the UI command info for this command
- L96 _public prototype_ `virtual TArray<FFractureToolContext> GetFractureToolContexts() const override;`
- L101 _protected member_ `TObjectPtr<UFractureConvertSettings> ConvertSettings;` — `UPROPERTY(EditAnywhere, Category = Slicing)`
- L104 _protected member_ `TObjectPtr<UFractureReimportSettings> ReimportSettings;` — `UPROPERTY(EditAnywhere, Category = Slicing)`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolConvex.h` (Private)


#### class `UFractureConvexSettings`  
`class UFractureConvexSettings : public UFractureToolSettings`  
_L15-67_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings controlling how convex hulls are generated for geometry collections
- L21 _public function_ `UFractureConvexSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L27 _public member_ `double CanExceedFraction = .5;` — `UPROPERTY(EditAnywhere, Category = Automatic, meta = (DisplayName = "Allow Larger Hull Fraction", ClampMin = "0"))` — Fraction (of geometry volume) by which a cluster's convex hull volume can exceed the actual geometry volume before instead using the hulls of the children.  0 means the convex volume cannot exceed the geometry volume; 1 means the convex volume is allowed to be 100% larger (2x) the geometry volume.
- L31 _public member_ `double SimplificationDistanceThreshold = 10.0;` — `UPROPERTY(EditAnywhere, Category = Automatic, meta = (ClampMin = "0"))` — We simplify the convex shape to keep points spaced at least this far apart (except to keep the hull from collapsing to zero volume)
- L35 _public member_ `EConvexOverlapRemoval RemoveOverlaps = EConvexOverlapRemoval::All;` — `UPROPERTY(EditAnywhere, Category = AutomaticOverlapRemoval)` — Whether to automatically cut away overlapping parts of the convex hulls, to avoid the simulation 'popping' to fix the overlaps
- L39 _public member_ `double OverlapRemovalShrinkPercent = 0.0;` — `UPROPERTY(EditAnywhere, Category = AutomaticOverlapRemoval, meta = (UIMin = "0", ClampMax = "99.9"))` — Overlap removal will be computed as if convex hulls were this percentage smaller (in range 0-100)
- L43 _public member_ `double FractionAllowRemove = .5;` — `UPROPERTY(EditAnywhere, Category = AutomaticOverlapRemoval, meta = (DisplayName = "Max Removal Fraction", ClampMin = ".01", ClampMax = "1"))` — Fraction of the convex hulls for a cluster that we can remove before using the hulls of the children
- L47 _public prototype_ `void DeleteFromSelected();` — `UFUNCTION(CallInEditor, Category = Custom, meta = (DisplayName = "Delete From Selected"))` — Delete convex hulls from selected clusters.  Does not affect hulls on leaves.
- L51 _public member_ `bool bSeeThroughLines = false;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (DisplayName = "See Through Lines"))` — When enabled, convex visualization lines will show through the actual geometry
- L55 _public member_ `float LineThickness = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (DisplayName = "Line Thickness", ClampMin = ".00", ClampMax = "1.0"))` — line thickness
- L66 _public prototype_ `void ClearCustomConvex();` — `UFUNCTION(CallInEditor, Category = Custom, meta = (DisplayName = "Clear Custom Convex"))` — Clear any manual adjustments to convex hulls on the selected bones

#### class `UFractureConvexActions`  
`class UFractureConvexActions : public UFractureToolSettings`  
_L74-93_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: UFUNCTION actions to manage convex hulls generation for geometry collections (These are pulled out from the above settings object mainly to control their ordering in the properties panel)
- L80 _public function_ `UFractureConvexActions(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L86 _public prototype_ `void SaveAsDefaults();` — `UFUNCTION(CallInEditor, Category = ProjectDefaults, meta = (DisplayName = "Save As Defaults"))` — Save settings as project defaults, to be used for all new geometry collections
- L90 _public prototype_ `void SetFromDefaults();` — `UFUNCTION(CallInEditor, Category = ProjectDefaults, meta = (DisplayName = "Set From Defaults"))` — Set settings from current project defaults

#### class `UFractureToolConvex`  
`class UFractureToolConvex : public UFractureModalTool`  
_L97-165_
- reflection: `UCLASS(DisplayName = "Convex Tool", Category = "FractureTools")`
- inherits: `UFractureModalTool`
- L102 _public prototype_ `UFractureToolConvex(const FObjectInitializer& ObjInit);`
- L109 _public prototype_ `virtual FText GetDisplayText() const override;` — This is the Text that will appear on the tool button to execute the tool
- L110 _public prototype_ `virtual FText GetTooltipText() const override;`
- L112 _public function_ `virtual FText GetApplyText() const override` — This is the Text that will appear on the button to execute the fracture
- L113 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L114 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L115 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L116 _public prototype_ `virtual void FractureContextChanged() override;`
- L117 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L119 _public prototype_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override;` — Executes function that generates new geometry. Returns the first new geometry index.
- L120 _public prototype_ `virtual bool CanExecute() const override;`
- L121 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L124 _public prototype_ `const TSharedPtr<FUICommandInfo>& GetUICommandInfo() const;` — Gets the UI command info for this command
- L126 _public prototype_ `virtual TArray<FFractureToolContext> GetFractureToolContexts() const override;`
- L128 _public prototype_ `void DeleteConvexFromSelected();`
- L129 _public prototype_ `void PromoteChildren();`
- L130 _public prototype_ `void ClearCustomConvex();`
- L132 _public prototype_ `virtual void Setup(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L136 _public member_ `TObjectPtr<UFractureConvexSettings> ConvexSettings;` — `UPROPERTY(EditAnywhere, Category = Convex)`
- L141 _protected member_ `TObjectPtr<UFractureConvexActions> ConvexActions;` — `UPROPERTY(EditAnywhere, Category = Convex)`
- L143 _protected function_ `virtual void ClearVisualizations() override`
- L151 _protected prototype_ `void AddConvexHullVizualizationData(const Chaos::FConvex& ConvexHull, const FTransform& WorldSpaceTransform, bool bIsCustom, bool bIsUnionOfHulls);`
- L152 _protected prototype_ `void AddVisualizationData(FGeometryCollection& Collection, const FTransform& OuterTransform, int32 TransformIdx, bool bUseExternalCollision, bool bIsUnionOfHulls = false);`
- L161 _protected member_ `TArray<FVector> HullPoints;`
- L162 _protected member_ `TArray<FEdgeVisInfo> HullEdges;`
- L163 _protected member_ `FVisualizationMappings EdgesMappings;`

#### struct `UFractureToolConvex::FEdgeVisInfo`  
`struct FEdgeVisInfo`  
_L154-159_
- L156 _public member_ `int32 A, B;`
- L156 _public member_ `int32 A, B;`
- L157 _public member_ `int8 bIsCustom : 1;` — allow for different coloring of hulls that have been manually set vs auto-generated ones
- L158 _public member_ `int8 bIsUnion : 1;` — this edge is part of a union of hulls ( cluster does not have a convex and is using a union of the children )

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolCustomVoronoi.h` (Private)


#### enum `EVoronoiPattern`  
`enum class EVoronoiPattern`  
_L13-25_
- reflection: `UENUM()`
- L16 _public enumerator_ `Centered` — Add a single site centered on the gizmo (or multiple if Variability is > 0)
- L18 _public enumerator_ `Uniform` — Add uniform-random sites
- L20 _public enumerator_ `Grid` — Add a regular grid of points
- L22 _public enumerator_ `MeshVertices` — Add a point at every mesh vertex
- L24 _public enumerator_ `SelectedBones` — Add a point per vertex of the selected bones

#### enum `EDownsamplingMode`  
`enum class EDownsamplingMode`  
_L28-36_
- reflection: `UENUM()`
- L31 _public enumerator_ `Random` — Downsample points by randomly removing points, without considering spacing
- L33 _public enumerator_ `UniformSpacing` — Downsample points so they're spread evenly across space, favoring points on sharp features
- L35 _public enumerator_ `KeepSharp` — Downsample points so points on sharp features are the last to be removed

#### class `UFractureCustomVoronoiSettings`  
`class UFractureCustomVoronoiSettings : public UFractureToolSettings`  
_L39-115_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- L44 _public function_ `UFractureCustomVoronoiSettings(const FObjectInitializer& ObjInit) : Super(ObjInit) , Variability(0.0f)`
- L51 _public member_ `EVoronoiPattern VoronoiPattern = EVoronoiPattern::Uniform;` — `UPROPERTY(EditAnywhere, Category = LiveVoronoiSites, meta = (DisplayName = "Pattern"))` — Method to generate next group of voronoi sites
- L55 _public member_ `float NormalOffset = 0.0f;` — `UPROPERTY(EditAnywhere, Category = LiveVoronoiSites, meta = (EditCondition = "VoronoiPattern == EVoronoiPattern::MeshVertices || VoronoiPattern == EVoronoiPattern::SelectedBones"))` — Offset point samples in the vertex normal directions
- L59 _public member_ `float Variability = 0.0f;` — `UPROPERTY(EditAnywhere, Category = LiveVoronoiSites, meta = (DisplayName = "Variability", UIMin = "0.0", ClampMin = "0.0"))` — Amount to randomly displace each Voronoi site (in cm)
- L64 _public member_ `int32 SitesToAdd = 20;` — `UPROPERTY(EditAnywhere, Category = LiveVoronoiSites, meta = (DisplayName = "Sites To Add", ClampMin = "1", UIMax = "1000", ClampMax = "5000", EditCondition = "VoronoiPattern != EVoronoiPattern::MeshVertices && VoronoiPattern != EVoronoiPattern::Grid", EditConditionHides))` — Number of Voronoi sites to add
- L69 _public member_ `int32 GridX = 5;` — `UPROPERTY(EditAnywhere, Category = LiveVoronoiSites, meta = (DisplayName = "Sites in X", ClampMin = "1", UIMax = "100", ClampMax = "5000", EditCondition = "VoronoiPattern == EVoronoiPattern::Grid", EditConditionHides))` — Number of sites to add to grid in X
- L74 _public member_ `int32 GridY = 5;` — `UPROPERTY(EditAnywhere, Category = LiveVoronoiSites, meta = (DisplayName = "Sites in Y", ClampMin = "1", UIMax = "100", ClampMax = "5000", EditCondition = "VoronoiPattern == EVoronoiPattern::Grid", EditConditionHides))` — Number of sites to add to grid in Y
- L79 _public member_ `int32 GridZ = 5;` — `UPROPERTY(EditAnywhere, Category = LiveVoronoiSites, meta = (DisplayName = "Sites in Z", ClampMin = "1", UIMax = "100", ClampMax = "5000", EditCondition = "VoronoiPattern == EVoronoiPattern::Grid", EditConditionHides))` — Number of sites to add to grid in Z
- L83 _public member_ `float SkipFraction = 0.0;` — `UPROPERTY(EditAnywhere, Category = LiveVoronoiSites, meta = (ClampMin = "0", ClampMax = "1"))` — Fraction of points to skip
- L87 _public member_ `EDownsamplingMode SkipMode;` — `UPROPERTY(EditAnywhere, Category = LiveVoronoiSites)` — Strategy used for skipping points; only used if SkipFraction is greater than 0
- L92 _public member_ `TSoftObjectPtr<AStaticMeshActor> ReferenceMesh;` — `UPROPERTY(EditAnywhere, Category = LiveVoronoiSites, meta = (DisplayName = "Reference Mesh", EditCondition = "VoronoiPattern == EVoronoiPattern::MeshVertices", EditConditionHides))` — Static mesh actor to be used as a reference when adding Voronoi sites
- L96 _public member_ `bool bStartAtActor = false;` — `UPROPERTY(EditAnywhere, Category = LiveVoronoiSites, meta = (EditCondition = "VoronoiPattern == EVoronoiPattern::MeshVertices", EditConditionHides))` — Whether to use the reference mesh actor's transform when placing the Voronoi sites, or center them at the current gizmo location instead
- L100 _public prototype_ `void FreezeLiveSites();` — `UFUNCTION(CallInEditor, Category = CustomVoronoi)` — Freeze the current live Voronoi Sites based on the current parameters
- L104 _public prototype_ `void ClearFrozenSites();` — `UFUNCTION(CallInEditor, Category = CustomVoronoi)` — Remove all frozen sites
- L108 _public prototype_ `void UnfreezeSites();` — `UFUNCTION(CallInEditor, Category = CustomVoronoi)` — Unfreeze all frozen sites
- L112 _public prototype_ `void RegenerateLiveSites();` — `UFUNCTION(CallInEditor, Category = CustomVoronoi)` — Re-run the live Voronoi sites generator, using the current settings and selection bounds
- L114 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`

#### class `UFractureToolCustomVoronoi`  
`class UFractureToolCustomVoronoi : public UFractureToolVoronoiCutterBase`  
_L119-194_
- reflection: `UCLASS(DisplayName="Custom Voronoi", Category="FractureTools")`
- inherits: `UFractureToolVoronoiCutterBase`
- L124 _public prototype_ `UFractureToolCustomVoronoi(const FObjectInitializer& ObjInit);`
- L127 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L128 _public prototype_ `virtual FText GetTooltipText() const override;`
- L129 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L130 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L131 _public prototype_ `virtual void SelectedBonesChanged() override;`
- L133 _public prototype_ `virtual void RegisterUICommand( FFractureEditorCommands* BindingContext ) override;`
- L137 _public member_ `TObjectPtr<UFractureCustomVoronoiSettings> CustomVoronoiSettings;` — `UPROPERTY(EditAnywhere, Category = Uniform)` — CustomVoronoi Voronoi Fracture Input Settings
- L140 _public member_ `TObjectPtr<UFractureTransformGizmoSettings> GizmoSettings;` — `UPROPERTY(EditAnywhere, Category = Uniform)`
- L142 _public prototype_ `virtual void Setup(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L143 _public prototype_ `virtual void Shutdown() override;`
- L146 _public function_ `void ClearLiveSites()` — Clear "live" voronoi sites (sites that are being edited by current settings / gizmo) -- they will repopulate on next call to GenerateVoronoiSites()
- L151 _public function_ `void FreezeLiveSites()`
- L161 _public function_ `void ClearFrozenSites()`
- L166 _public function_ `void UnfreezeSites()`
- L177 _public prototype_ `void GenerateLivePattern(const TArray<FFractureToolContext>& FractureContexts, int32 RandomSeed);` — Re-calculate the "live transformed" voronoi sites based on current settings
- L179 _public prototype_ `void FractureContextChanged() override;`
- L182 _protected prototype_ `void GenerateVoronoiSites(const FFractureToolContext& Context, TArray<FVector>& Sites) override;`
- L184 _protected prototype_ `FTransform GetGizmoTransform() const;`
- L187 _protected member_ `TArray<FVector> FrozenSites;` — Sites that are not currently live-edited
- L190 _protected member_ `TArray<FVector> LiveSites;` — Voronoi sites that are currently being regenerated and moved
- L193 _protected member_ `FBox CombinedWorldBounds = FBox(EForceInit::ForceInit);` — Bounds of the combined, currently-selected fracture contexts, to be used the next time the fracture pattern is generated

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolCutter.h` (Private)


#### class `UFractureCutterSettings`  
`class UFractureCutterSettings : public UFractureToolSettings`  
_L23-184_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings specifically related to the one-time destructive fracturing of a mesh
- L29 _public function_ `UFractureCutterSettings(const FObjectInitializer& ObjInit) : Super(ObjInit) , RandomSeed(-1) , ChanceToFracture(1.0) , bGroupFracture(true) , bDrawSites(false) , bDrawDiagram(true) , Amplitude(0.0f) , Frequency(0.1f) , Persistence(0.5f) , Lacunarity(2.0f) , OctaveNumber(4) , PointSpacing(10)`
- L44 _public prototype_ `void TransferNoiseSettings(FNoiseSettings& NoiseSettingsOut);`
- L48 _public member_ `FString InternalMaterial;` — `UPROPERTY(EditAnywhere, Category = Materials, meta = (TransientToolProperty, DisplayName = "Internal Material", GetOptions = GetMaterialNamesFunc, NoResetToDefault))` — Material to set for internal faces on fracture. 'Automatic' will use the most common 'internal' material in each geometry, or the last valid material if no internal faces are found
- L51 _public function_ `const TArray<FString>& GetMaterialNamesFunc()` — `UFUNCTION()`
- L53 _public function_ `void UpdateActiveMaterialNames(TArray<FString> InMaterialNamesList)`
- L63 _public function_ `int32 GetInternalMaterialID()` — Get the user-chosen internal material ID, or INDEX_NONE if 'Automatic' is chosen
- L71 _public member_ `int32 RandomSeed;` — `UPROPERTY(EditAnywhere, Category = CommonFracture, meta = (DisplayName = "Random Seed", UIMin = "-1", UIMax = "1000", ClampMin = "-1"))` — Random number generator seed for repeatability. If the value is -1, a different random seed will be used every time, otherwise the specified seed will always be used
- L75 _public member_ `float ChanceToFracture;` — `UPROPERTY(EditAnywhere, Category = CommonFracture, meta = (DisplayName = "Chance To Fracture Per Bone", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Chance to fracture each selected bone. If 0, no bones will fracture; if 1, all bones will fracture.
- L79 _public member_ `bool bGroupFracture;` — `UPROPERTY(EditAnywhere, Category = CommonFracture, meta = (EditCondition = "bGroupFractureToggleEnabled", HideEditConditionToggle, DisplayName = "Group Fracture"))` — Generate a fracture pattern across all selected meshes.
- L83 _public member_ `bool bGroupFractureToggleEnabled = true;` — `UPROPERTY()` — This flag allows tools to disable the above bGroupFracture option if/when it is not applicable
- L87 _public member_ `bool bSplitIslands = true;` — `UPROPERTY(EditAnywhere, Category = "CommonFracture|Split Islands")` — Whether to split the fractured mesh pieces into separate islands based on geometric connectivity after fracturing
- L91 _public member_ `float CloseVertexDistance = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "CommonFracture|Split Islands", meta = (EditCondition = "bSplitIslands", Units = "cm", ClampMin = "0.0"))` — Distance threshold for connecting spatially-close vertices before computing islands
- L95 _public member_ `float VertexToSurfaceBridgeDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "CommonFracture|Split Islands", meta = (EditCondition = "bSplitIslands", Units = "cm", ClampMin = "0.0"))` — If > 0, bridge separate islands whose surfaces are within this vertex-to-triangle distance. 0 = disabled.
- L99 _public member_ `float Grout = 0.0f;` — `UPROPERTY(EditAnywhere, Category = CommonFracture, meta = (UIMin = "0.0", ClampMin = "0.0", EditCondition = "bGroutSettingEnabled", HideEditConditionToggle, EditConditionHides))` — Amount of space to leave between cut pieces
- L103 _public member_ `bool bGroutSettingEnabled = true;` — `UPROPERTY()` — This flag allows tools to disable the above Grout setting if/when it's not applicable
- L107 _public member_ `bool bDrawSites;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (EditCondition = "bDrawSitesToggleEnabled", HideEditConditionToggle, EditConditionHides, DisplayName = "Draw Sites"))` — Draw points marking the centers of pieces to be cut out by the fracture pattern.
- L111 _public member_ `bool bDrawSitesToggleEnabled = true;` — `UPROPERTY()` — This flag allows tools to disable the above bDrawSites option if/when it is not applicable
- L115 _public member_ `bool bDrawDiagram;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (DisplayName = "Draw Diagram"))` — Draw the edges of the fracture pattern.
- L119 _public member_ `bool bDrawNoisePreview = true;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (EditCondition = "bNoisePreviewToggleEnabled", HideEditConditionToggle, EditConditionHides))` — Whether to show a solid preview of the cutting geometry, including any noise displacement
- L123 _public member_ `bool bNoisePreviewToggleEnabled = true;` — `UPROPERTY()` — This flag allows tools to disable the above bDrawNoisePreview option if/when it is not applicable
- L127 _public member_ `float FractionPreviewCells = .1f;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bDrawNoisePreview && bDrawSitesToggleEnabled", HideEditConditionToggle, EditConditionHides))` — Fraction of cells to show in noise preview
- L131 _public member_ `double NoisePreviewScale = 1.;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (ClampMin = ".01", ClampMax = "1000", UIMin = ".25", UIMax = "10", EditCondition = "bDrawNoisePreview && bNoisePreviewHasScale", HideEditConditionToggle, EditConditionHides))` — Scale of the noise preview plane
- L135 _public member_ `bool bNoisePreviewHasScale = false;` — `UPROPERTY()` — This flag allows tools to disable the noise preview scale setting if it's not applicable
- L139 _public member_ `float Amplitude;` — `UPROPERTY(EditAnywhere, Category = Noise, meta = (UIMin = "0.0", EditCondition = "bNoiseSettingsEnabled", HideEditConditionToggle, EditConditionHides))` — Size of the Perlin noise displacement (in cm). If 0, no noise will be applied
- L143 _public member_ `float Frequency;` — `UPROPERTY(EditAnywhere, Category = Noise, meta = (EditCondition = "bNoiseSettingsEnabled", HideEditConditionToggle, EditConditionHides))` — Period of the Perlin noise.  Smaller values will create a smoother noise pattern
- L147 _public member_ `float Persistence;` — `UPROPERTY(EditAnywhere, Category = Noise, meta = (UIMin = "0.01", UIMax = "1.0", EditCondition = "bNoiseSettingsEnabled", HideEditConditionToggle, EditConditionHides))` — Persistence of the layers of Perlin noise. At each layer (octave) after the first, the amplitude of the Perlin noise is scaled by this factor
- L151 _public member_ `float Lacunarity;` — `UPROPERTY(EditAnywhere, Category = Noise, meta = (UIMin = "1.0", UIMax = "4.0", EditCondition = "bNoiseSettingsEnabled", HideEditConditionToggle, EditConditionHides))` — Lacunarity of the layers of Perlin noise. At each layer (octave) after the first, the frequency of the Perlin noise is scaled by this factor
- L158 _public member_ `int32 OctaveNumber;` — `UPROPERTY(EditAnywhere, Category = Noise, meta = (ClampMin = "1", UIMax = "8", EditCondition = "bNoiseSettingsEnabled", HideEditConditionToggle, EditConditionHides))` — Number of fractal layers of Perlin noise to apply. Each layer is additive, with Amplitude and Frequency parameters scaled by Persistence and Lacunarity Smaller values (1 or 2) will create noise that looks like gentle rolling hills, while larger values (> 4) will tend to look more like craggy mountains
- L162 _public member_ `float PointSpacing;` — `UPROPERTY(EditAnywhere, Category = Noise, meta = (DisplayName = "Point Spacing", UIMin = "1", ClampMin = "0.1", EditCondition = "bNoiseSettingsEnabled", HideEditConditionToggle, EditConditionHides))` — Distance (in cm) between vertices on cut surfaces where noise is added.  Larger spacing between vertices will create more efficient meshes with fewer triangles, but less resolution to see the shape of the added noise
- L166 _public member_ `bool bNoiseSettingsEnabled = true;` — `UPROPERTY()` — This flag allows tools to disable the above Noise settings if/when they are not applicable
- L169 _public function_ `float GetMaxVertexMovement()` — Get the maximum distance a vertex could be moved by a combination of grout and noise
- L183 _private member_ `TArray<FString> ActiveMaterialNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`

#### class `UFractureCollisionSettings`  
`class UFractureCollisionSettings : public UFractureToolSettings`  
_L188-219_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings related to the collision properties of the fractured mesh pieces
- L193 _public function_ `UFractureCollisionSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L203 _public member_ `bool bAddSamplesForCollision = false;` — `UPROPERTY(EditAnywhere, Category = Collision)` — If enabled, add extra vertices (without triangles) to the geometry in regions where vertices are spaced too far apart (e.g. across large triangles) These extra vertices will be used as collision samples in particle-implicit collisions, and can help the physics system detect collisions more accurately Note this is *only* useful for simulations that use particle-implicit collisions
- L210 _public member_ `float PointSpacing = 50.0f;` — `UPROPERTY(EditAnywhere, Category = Collision, meta = (UIMin = "1", ClampMin = "0.1", EditCondition = "bAddSamplesForCollision"))` — The number of centimeters to allow between vertices on the mesh surface: If there are gaps larger than this, add additional vertices (without triangles) to help support particle-implicit collisions Only used if Add Samples For Collision is enabled
- L213 _public function_ `float GetPointSpacing()` — Get point spacing or the special value of 0 if adding collision samples is disabled

#### class `UFractureToolCutterBase`  
`class UFractureToolCutterBase : public UFractureInteractiveTool`  
_L222-298_
- reflection: `UCLASS(Abstract, DisplayName = "Cutter Base", Category = "FractureTools")`
- inherits: `UFractureInteractiveTool`
- L227 _public prototype_ `UFractureToolCutterBase(const FObjectInitializer& ObjInit);`
- L230 _public function_ `virtual FText GetApplyText() const override` — This is the Text that will appear on the button to execute the fracture
- L232 _public prototype_ `virtual bool CanExecute() const override;`
- L234 _public prototype_ `virtual TArray<FFractureToolContext> GetFractureToolContexts() const override;`
- L236 _public function_ `virtual void FractureContextChanged() override`
- L241 _public function_ `virtual void Setup(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override`
- L251 _public function_ `virtual void ConfigureCutterSettings()` — Set tool-specific defaults for the cutter settings (e.g., disable grout/noise if needed)
- L261 _public function_ `virtual void SelectedBonesChanged() override`
- L267 _public prototype_ `FBox GetCombinedBounds(const TArray<FFractureToolContext>& Contexts) const;`
- L270 _public prototype_ `virtual void PostFractureProcess(const FFractureToolContext& FractureContext, int32 FirstNewGeometryIndex) override;` — Post-processing; sets user-specified internal material on fracture (if not automatic)
- L272 _public function_ `virtual void UpdateUseGizmo(bool bUseGizmo)`
- L277 _public function_ `void SetMandateGroupFracture(bool bMandateGroupFracture)`
- L288 _protected member_ `TObjectPtr<UFractureCutterSettings> CutterSettings;` — `UPROPERTY(EditAnywhere, Category = Slicing)`
- L291 _protected member_ `TObjectPtr<UFractureCollisionSettings> CollisionSettings;` — `UPROPERTY(EditAnywhere, Category = Collision)`
- L295 _protected prototype_ `void UpdateDefaultRandomSeed();` — Manage which seed to use when no specific random seed is specified, to control when the seed changes (primarily to avoid the seed changing between creating the preview and doing the actual cut)
- L296 _protected member_ `int32 DefaultRandomSeed = 0;`

#### struct `FVoronoiDiagramInput`  
`struct FVoronoiDiagramInput`  
_L301-309_
- L303 _public member_ `FTransform Transform;`
- L304 _public member_ `int32 SourceComponentIdx;`
- L305 _public member_ `int32 BoneIdx;`
- L306 _public member_ `TArray<FVector> Sites;`
- L307 _public member_ `FBox Bounds;`
- L308 _public member_ `int32 NoiseSeed;`

#### struct `FCellDiagramResult`  
`struct FCellDiagramResult`  
_L311-323_
- L313 _public function_ `FCellDiagramResult(FPlanarCells Diagram, int32 SourceComponentIdx, int32 BoneIdx, FTransform Transform, FBox Bounds, int32 NoiseSeed) : Diagram(Diagram), SourceComponentIdx(SourceComponentIdx), BoneIdx(BoneIdx), Transform(Transform), Bounds(Bounds), NoiseSeed(NoiseSeed)`
- L317 _public member_ `FPlanarCells Diagram;`
- L318 _public member_ `int32 SourceComponentIdx;`
- L319 _public member_ `int32 BoneIdx;`
- L320 _public member_ `FTransform Transform;`
- L321 _public member_ `FBox Bounds;`
- L322 _public member_ `int32 NoiseSeed;`

#### struct `FCellNoisePreviewResult`  
`struct FCellNoisePreviewResult`  
_L325-331_
- L327 _public member_ `UE::Geometry::FDynamicMesh3 NoiseMesh;`
- L328 _public member_ `int32 SourceComponentIdx;`
- L329 _public member_ `int32 BoneIdx;`
- L330 _public member_ `FTransform Transform;`

#### class `FCellNoisePreviewOp`  
`class FCellNoisePreviewOp : public UE::Geometry::TGenericDataOperator<TArray<FCellNoisePreviewResult>>`  
_L333-348_
- inherits: `UE::Geometry::TGenericDataOperator<TArray<FCellNoisePreviewResult>>`
- L336 _public function_ `FCellNoisePreviewOp(TArray<FCellDiagramResult>&& ComputedDiagrams) : ComputedDiagrams(MoveTemp(ComputedDiagrams))`
- L338 _public prototype_ `virtual ~FCellNoisePreviewOp() = default;`
- L340 _public member_ `TArray<FCellDiagramResult> ComputedDiagrams;`
- L341 _public member_ `float PointSpacing;`
- L342 _public member_ `float Grout;`
- L344 _public member_ `float KeepCellsFrac = .1f;`
- L347 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;` — TGenericDataOperator interface:

#### class `FVoronoiCellsOp`  
`class FVoronoiCellsOp : public UE::Geometry::TGenericDataOperator<TArray<FCellDiagramResult>>`  
_L350-363_
- inherits: `UE::Geometry::TGenericDataOperator<TArray<FCellDiagramResult>>`
- L354 _public function_ `FVoronoiCellsOp(TArray<FVoronoiDiagramInput>&& Inputs) : Diagrams(MoveTemp(Inputs))`
- L357 _public prototype_ `virtual ~FVoronoiCellsOp() = default;`
- L359 _public member_ `TArray<FVoronoiDiagramInput> Diagrams;`
- L362 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;` — TGenericDataOperator interface:

#### class `UFractureToolVoronoiCutterBase`  
`class UFractureToolVoronoiCutterBase : public UFractureToolCutterBase`  
_L367-445_
- reflection: `UCLASS(Abstract, DisplayName = "Voronoi Base", Category = "FractureTools")`
- inherits: `UFractureToolCutterBase`
- L372 _public prototype_ `UFractureToolVoronoiCutterBase(const FObjectInitializer& ObjInit);`
- L374 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L375 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L377 _public prototype_ `virtual void FractureContextChanged() override;`
- L378 _public prototype_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override;`
- L381 _protected function_ `virtual void GenerateVoronoiSites(const FFractureToolContext& Context, TArray<FVector>& Sites)`
- L383 _protected prototype_ `FBox GetVoronoiBounds(const FFractureToolContext& FractureContext, const TArray<FVector>& Sites) const;`
- L385 _protected function_ `virtual void ClearVisualizations()`
- L400 _protected function_ `void ClearEdges()`
- L414 _protected prototype_ `void ClearMeshes();`
- L416 _protected prototype_ `virtual void UpdateVisualizations(TArray<FFractureToolContext>& FractureContexts);`
- L417 _protected prototype_ `virtual void AddLineVisualizations(TArray<FCellDiagramResult>& DiagramResults);`
- L418 _protected prototype_ `virtual void AddNoiseVisualizations(TArray<FCellNoisePreviewResult>& NoiseResults);`
- L422 _private member_ `TArray<TObjectPtr<ULineSetComponent>> VoronoiLineSets;` — `UPROPERTY()`
- L424 _private member_ `TArray<TObjectPtr<UDynamicMeshComponent>> VoronoiNoisePreviews;` — `UPROPERTY()`
- L430 _private member_ `TUniquePtr<UE::Fracture::TBackgroundOpExecuter<FVoronoiCellsOp>> ComputeCells = nullptr;` — Background compute
- L431 _private member_ `TUniquePtr<UE::Fracture::TBackgroundOpExecuter<FCellNoisePreviewOp>> ComputeNoisePreview = nullptr;`
- L433 _private member_ `TArray<FVoronoiDiagramInput> DiagramInputs;`
- L434 _private member_ `bool bDiagramUpdated = false;`
- L435 _private member_ `float ComputeRelaunchDelay = 0;`
- L437 _private member_ `TArray<int32> CellMember;`
- L438 _private member_ `TArray<FVector> VoronoiSites;`
- L440 _private member_ `TArray<FColor> Colors;`
- L442 _private member_ `FVisualizationMappings SitesMappings, EdgesMappings;`
- L442 _private member_ `FVisualizationMappings SitesMappings, EdgesMappings;`
- L444 _private prototype_ `void UpdateLineSetExplodedVectors();`

#### class `UFractureTransformGizmoSettings`  
`class UFractureTransformGizmoSettings : public UFractureToolSettings`  
_L452-503_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: This helps create a 3D transform gizmo that can be used to adjust fracture placement Note it is tailored to UFractureToolCutterBase, and expects Setup(), Shutdown() and ResetGizmo() to be called on tool setup, shutdown, and selection change respectively
- L457 _public prototype_ `UFractureTransformGizmoSettings(const FObjectInitializer & ObjInit);`
- L459 _public prototype_ `void Setup(UFractureToolCutterBase* Cutter, ETransformGizmoSubElements GizmoElements = ETransformGizmoSubElements::StandardTranslateRotate);`
- L460 _public prototype_ `void Shutdown();`
- L462 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L464 _public prototype_ `void TransformChanged(UTransformProxy* Proxy, FTransform Transform);`
- L466 _public prototype_ `void ResetGizmo(bool bResetRotation = false);`
- L468 _public function_ `bool IsGizmoEnabled()`
- L473 _public function_ `FTransform GetTransform()`
- L480 _public member_ `bool bUseGizmo = true;` — `UPROPERTY(EditAnywhere, Category = PlacementControls, meta = (EditCondition = "bShowUseGizmoOption", EditConditionHides, HideEditConditionToggle))` — Use a 3D rigid transform gizmo to place the fracture pattern.  Only supports grouped fracture.
- L484 _public member_ `bool bCenterOnSelection = true;` — `UPROPERTY(EditAnywhere, Category = PlacementControls, meta = (EditCondition = "bUseGizmo", EditConditionHides))` — Recenter the gizmo to the center of the selection when selection changes
- L487 _public member_ `bool bShowUseGizmoOption = true;` — `UPROPERTY()`
- L490 _public member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo = nullptr;` — `UPROPERTY()`
- L493 _public member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — `UPROPERTY()`
- L498 _protected member_ `TObjectPtr<UFractureToolCutterBase> AttachedCutter = nullptr;` — `UPROPERTY()`
- L502 _protected member_ `TObjectPtr<UInteractiveToolsContext> UsedToolsContext = nullptr;` — `UPROPERTY()` — the tools context responsible for the gizmo

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolEditing.h` (Private)


#### class `UFractureToolDeleteBranch`  
`class UFractureToolDeleteBranch : public UFractureActionTool`  
_L10-23_
- reflection: `UCLASS(DisplayName = "Delete Branch", Category = "FractureTools")`
- inherits: `UFractureActionTool`
- L15 _public function_ `UFractureToolDeleteBranch(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L18 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L19 _public prototype_ `virtual FText GetTooltipText() const override;`
- L20 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L21 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L22 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolMergeSelected`  
`class UFractureToolMergeSelected : public UFractureActionTool`  
_L26-39_
- reflection: `UCLASS(DisplayName = "Merge Selected", Category = "FractureTools")`
- inherits: `UFractureActionTool`
- L31 _public function_ `UFractureToolMergeSelected(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L34 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L35 _public prototype_ `virtual FText GetTooltipText() const override;`
- L36 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L37 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L38 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolSplitSelected`  
`class UFractureToolSplitSelected : public UFractureActionTool`  
_L42-55_
- reflection: `UCLASS(DisplayName = "Split Selected", Category = "FractureTools")`
- inherits: `UFractureActionTool`
- L47 _public function_ `UFractureToolSplitSelected(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L50 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L51 _public prototype_ `virtual FText GetTooltipText() const override;`
- L52 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L53 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L54 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolHide`  
`class UFractureToolHide : public UFractureActionTool`  
_L60-73_
- reflection: `UCLASS(DisplayName = "Hide", Category = "FractureTools")`
- inherits: `UFractureActionTool`
- L65 _public function_ `UFractureToolHide(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L68 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L69 _public prototype_ `virtual FText GetTooltipText() const override;`
- L70 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L71 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L72 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolUnhide`  
`class UFractureToolUnhide : public UFractureActionTool`  
_L77-90_
- reflection: `UCLASS(DisplayName = "Unhide", Category = "FractureTools")`
- inherits: `UFractureActionTool`
- L82 _public function_ `UFractureToolUnhide(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L85 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L86 _public prototype_ `virtual FText GetTooltipText() const override;`
- L87 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L88 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L89 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureValidateSettings`  
`class UFractureValidateSettings : public UFractureToolSettings`  
_L95-118_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings for the Validate tool
- L101 _public function_ `UFractureValidateSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L108 _public member_ `bool bRemoveUnreferencedGeometry = true;` — `UPROPERTY(EditAnywhere, Category = CleanUnused)` — Find and remove any unused geometry data
- L112 _public member_ `bool bRemoveClustersOfOne = false;` — `UPROPERTY(EditAnywhere, Category = Clustering)` — Whether to collapse any clusters with only a single child
- L116 _public member_ `bool bRemoveDanglingClusters = false;` — `UPROPERTY(EditAnywhere, Category = Clustering)` — Remove dangling clusters -- Note this can invalidate caches

#### class `UFractureToolValidate`  
`class UFractureToolValidate : public UFractureModalTool`  
_L124-149_
- reflection: `UCLASS(DisplayName = "Validate", Category = "FractureTools")`
- inherits: `UFractureModalTool`
- L129 _public prototype_ `UFractureToolValidate(const FObjectInitializer& ObjInit);`
- L132 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L133 _public prototype_ `virtual FText GetTooltipText() const override;`
- L134 _public function_ `virtual FText GetApplyText() const override`
- L136 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L138 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L139 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L140 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L141 _public function_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override`
- L148 _public member_ `TObjectPtr<UFractureValidateSettings> ValidationSettings;` — `UPROPERTY(EditAnywhere, Category = Validation)`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolEmbed.h` (Private)


#### class `UFractureToolAddEmbeddedGeometry`  
`class UFractureToolAddEmbeddedGeometry : public UFractureActionTool`  
_L11-28_
- reflection: `UCLASS()`
- inherits: `UFractureActionTool`
- L16 _public function_ `UFractureToolAddEmbeddedGeometry(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L19 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L20 _public prototype_ `virtual FText GetTooltipText() const override;`
- L21 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L22 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L23 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L24 _public prototype_ `virtual bool CanExecute() const override;`
- L27 _private prototype_ `static TArray<UStaticMeshComponent*> GetSelectedStaticMeshComponents();`

#### class `UFractureToolAutoEmbedGeometry`  
`class UFractureToolAutoEmbedGeometry : public UFractureActionTool`  
_L32-49_
- reflection: `UCLASS()`
- inherits: `UFractureActionTool`
- L37 _public function_ `UFractureToolAutoEmbedGeometry(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L40 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L41 _public prototype_ `virtual FText GetTooltipText() const override;`
- L42 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L43 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L44 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L45 _public prototype_ `virtual bool CanExecute() const override;`
- L48 _private prototype_ `static TArray<UStaticMeshComponent*> GetSelectedStaticMeshComponents();`

#### class `UFractureToolFlushEmbeddedGeometrySettings`  
`class UFractureToolFlushEmbeddedGeometrySettings : public UFractureToolSettings`  
_L53-65_
- reflection: `UCLASS(DisplayName = "Flush Embedded Geometry", Category = "FractureTools")`
- inherits: `UFractureToolSettings`
- L58 _public function_ `UFractureToolFlushEmbeddedGeometrySettings(const FObjectInitializer& ObjInit) : Super(ObjInit) , bExtractAsStaticMeshActors(false)`
- L64 _public member_ `bool bExtractAsStaticMeshActors;` — `UPROPERTY(EditAnywhere, Category = EmbeddedGeometry, meta = (DisplayName = "Extract As StaticMesh Actors"))`

#### class `UFractureToolFlushEmbeddedGeometry`  
`class UFractureToolFlushEmbeddedGeometry : public UFractureModalTool`  
_L68-91_
- reflection: `UCLASS(DisplayName = "FlushEmbeddedGeometry", Category = "FractureTools")`
- inherits: `UFractureModalTool`
- L73 _public typedef_ `using FGeometryCollectionPtr = TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe>;`
- L75 _public prototype_ `UFractureToolFlushEmbeddedGeometry(const FObjectInitializer& ObjInit);`
- L78 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L79 _public prototype_ `virtual FText GetTooltipText() const override;`
- L80 _public prototype_ `virtual FText GetApplyText() const override;`
- L81 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L82 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L83 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext);`
- L85 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L88 _public member_ `TObjectPtr<UFractureToolFlushEmbeddedGeometrySettings> FlushEmbeddedGeometrySettings;` — `UPROPERTY(EditAnywhere, Category = EmbeddedGeometry)`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolFixTinyGeo.h` (Private)


#### enum `EGeometrySelectionMethod`  
`enum class EGeometrySelectionMethod`  
_L13-19_
- reflection: `UENUM()`
- L16 _public enumerator_ `VolumeCubeRoot UMETA(DisplayName = "Size")` — Select by cube root of volume
- L18 _public enumerator_ `RelativeVolume` — Select by cube root of volume relative to the overall shape's cube root of volume

#### enum `ENeighborSelectionMethod`  
`enum class ENeighborSelectionMethod`  
_L22-30_
- reflection: `UENUM()`
- L25 _public enumerator_ `LargestNeighbor` — Merge to the neighbor with the largest volume
- L27 _public enumerator_ `NearestCenter` — Merge to the neighbor with the closest center
- L29 _public enumerator_ `LargestContactArea` — Merge to the neighbor with the largest contact surface area

#### enum `EUseBoneSelection`  
`enum class EUseBoneSelection`  
_L33-38_
- reflection: `UENUM()`
- L35 _public enumerator_ `NoEffect`
- L36 _public enumerator_ `AlsoMergeSelected`
- L37 _public enumerator_ `OnlyMergeSelected`

#### enum `EMergeType`  
`enum class EMergeType : uint8`  
_L41-45_
- reflection: `UENUM()`
- L43 _public enumerator_ `MergeGeometry`
- L44 _public enumerator_ `MergeClusters`

#### class `UFractureTinyGeoSettings`  
`class UFractureTinyGeoSettings : public UFractureToolSettings`  
_L49-103_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings controlling how geometry is selected and merged into neighboring geometry
- L55 _public function_ `UFractureTinyGeoSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L61 _public member_ `EMergeType MergeType = EMergeType::MergeGeometry;` — `UPROPERTY(EditAnywhere, Category = MergeSettings)` — Whether to merge small geometry, or small clusters
- L65 _public member_ `bool bOnFractureLevel = true;` — `UPROPERTY(EditAnywhere, Category = MergeSettings, meta = (EditCondition = "!bFractureLevelIsAll && MergeType == EMergeType::MergeClusters", EditConditionHides))` — Only consider bones at the current Fracture Level
- L69 _public member_ `bool bOnlyClusters = false;` — `UPROPERTY(EditAnywhere, Category = MergeSettings, meta = (EditCondition = "!bFractureLevelIsAll && MergeType == EMergeType::MergeClusters && bOnFractureLevel", EditConditionHides))` — Only auto-consider clusters for merging. Note that leaf nodes can still be consider if manually selected.
- L73 _public member_ `bool bOnlySameParent = true;` — `UPROPERTY(EditAnywhere, Category = MergeSettings)` — Only merge to neighbors with the same parent in the hierarchy
- L77 _public member_ `bool bFractureLevelIsAll = false;` — `UPROPERTY()` — Helper variable to let the EditConditions above check whether the Fracture Level is set to 'All'
- L80 _public member_ `ENeighborSelectionMethod NeighborSelection = ENeighborSelectionMethod::LargestNeighbor;` — `UPROPERTY(EditAnywhere, Category = MergeSettings, meta = (DisplayName = "Merge To"))`
- L84 _public member_ `bool bOnlyToConnected = true;` — `UPROPERTY(EditAnywhere, Category = MergeSettings, meta = (EditCondition = "MergeType == EMergeType::MergeClusters", EditConditionHides))` — Only merge pieces that are connected in the proximity graph. If unchecked, connected pieces will still be favored, but if none are available the closest disconnected piece can be merged.
- L88 _public member_ `EUseBoneSelection UseBoneSelection;` — `UPROPERTY(EditAnywhere, Category = MergeSettings, meta = (DisplayName = "Bone Selection"))` — Options for using the current bone selection
- L92 _public member_ `EGeometrySelectionMethod SelectionMethod = EGeometrySelectionMethod::RelativeVolume;` — `UPROPERTY(EditAnywhere, Category = FilterSettings)`
- L96 _public member_ `double MinVolumeCubeRoot = 1;` — `UPROPERTY(EditAnywhere, Category = FilterSettings, meta = (DisplayName = "MinSize", ClampMin = ".00001", UIMin = ".1", UIMax = "10", EditCondition = "SelectionMethod == EGeometrySelectionMethod::VolumeCubeRoot", EditConditionHides))` — If size (cube root of volume) is less than this value, geometry should be merged into neighbors -- i.e. a value of 2 merges geometry smaller than a 2x2x2 cube
- L101 _public member_ `double RelativeVolume = .01;` — `UPROPERTY(EditAnywhere, Category = FilterSettings, meta = (ClampMin = "0", UIMax = ".1", ClampMax = "1.0", EditCondition = "SelectionMethod == EGeometrySelectionMethod::RelativeVolume", EditConditionHides))` — If cube root of volume relative to the overall shape's cube root of volume is less than this, the geometry should be merged into its neighbors. (Note: This is a bit different from the histogram viewer's "Relative Size," which instead shows values relative to the largest rigid bone.)

#### class `UFractureToolFixTinyGeo`  
`class UFractureToolFixTinyGeo : public UFractureToolCutterBase`  
_L109-156_
- reflection: `UCLASS(DisplayName = "Geometry Merge Tool", Category = "FractureTools")`
- inherits: `UFractureToolCutterBase`
- desc: Note this tool doesn't actually fracture, but it does remake pieces of geometry and shares a lot of machinery with the fracture tools
- L114 _public prototype_ `UFractureToolFixTinyGeo(const FObjectInitializer& ObjInit);`
- L117 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L118 _public prototype_ `virtual FText GetTooltipText() const override;`
- L119 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L121 _public function_ `virtual FText GetApplyText() const override`
- L123 _public prototype_ `void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L125 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L127 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L129 _public prototype_ `virtual void FractureContextChanged() override;`
- L130 _public prototype_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override;`
- L131 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L132 _public prototype_ `virtual void Setup(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L135 _protected function_ `virtual void ClearVisualizations() override`
- L145 _private member_ `TObjectPtr<UFractureTinyGeoSettings> TinyGeoSettings;` — `UPROPERTY(EditAnywhere, Category = FixGeo)`
- L147 _private member_ `TArray<FBox> ToRemoveBounds;` — Bounds in global space but without exploded vectors applied
- L148 _private member_ `FVisualizationMappings ToRemoveMappings;`
- L150 _private prototype_ `static double GetTotalVolume(const FGeometryCollection& Collection, const TArray<double>& Volumes);`
- L151 _private prototype_ `double GetMinVolume(double TotalVolume) const;`
- L152 _private member_ `const double VolDimScale = .01;` — compute volumes in meters instead of cm, for saner units at typical scales
- L154 _private prototype_ `bool CollectTargetBones(FGeometryCollection& Collection, const TArray<int32>& Selection, TArray<int32>& OutSmallIndices, TArray<double>& OutVolumes, double& OutMinVolume);`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolGenerators.h` (Private)


#### class `UFractureToolGenerateAsset`  
`class UFractureToolGenerateAsset : public UFractureActionTool`  
_L14-66_
- reflection: `UCLASS()`
- inherits: `UFractureActionTool`
- L29 _public function_ `UFractureToolGenerateAsset(const FObjectInitializer& ObjInit) : Super(ObjInit) , AssetPath(FString(TEXT("/Game")))`
- L35 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L36 _public prototype_ `virtual FText GetTooltipText() const override;`
- L37 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L38 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L39 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L40 _public prototype_ `virtual bool CanExecute() const override;`
- L43 _private prototype_ `void OpenGenerateAssetDialog(TArray<AActor*>& Actors);`
- L44 _private prototype_ `void OnGenerateAssetPathChosen(const FCreationParameters& Params, TArray<AActor*> Actors);`
- L45 _private prototype_ `AGeometryCollectionActor* ConvertActorsToGeometryCollection(const FCreationParameters& Params, bool bAddInternalMaterials, TArray<AActor*>& Actors);`
- L46 _private prototype_ `class AGeometryCollectionActor* CreateNewGeometryActor(const FString& Name, const FTransform& Transform, bool AddMaterials );`
- L47 _private prototype_ `static AActor* AddActor(ULevel* InLevel, UClass* Class);`
- L49 _private prototype_ `FString GetDefaultAssetPath(const TArray<AActor*>& Actors) const;`
- L52 _private member_ `TWeakPtr<FFractureEditorModeToolkit> Toolkit;`
- L55 _private member_ `FString AssetPath;` — `UPROPERTY()`
- L58 _private member_ `TObjectPtr<UDataflow> LastDataflowAsset = nullptr;` — `UPROPERTY()`
- L61 _private member_ `TObjectPtr<UPhysicalMaterial> LastPhysicalMaterial = nullptr;` — `UPROPERTY()`
- L63 _private member_ `bool bLastSplitComponents = false;`
- L64 _private member_ `bool bLastFromToMesh = false;`
- L65 _private member_ `bool bLastUseRootProxies = true;`

#### struct `UFractureToolGenerateAsset::FCreationParameters`  
`struct FCreationParameters`  
_L19-27_
- L21 _public member_ `FString AssetPath;`
- L22 _public member_ `bool bFromToMeshTool = false;`
- L23 _public member_ `bool bSplitIslands = false;`
- L24 _public member_ `bool bUseRootProxies = true;`
- L25 _public member_ `TObjectPtr<UDataflow> DataflowAsset;`
- L26 _public member_ `TObjectPtr<UPhysicalMaterial> PhysicalMaterial;`

#### class `UGeometryCollectionResetSettings`  
`class UGeometryCollectionResetSettings : public UFractureToolSettings`  
_L71-83_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- L76 _public function_ `UGeometryCollectionResetSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L82 _public member_ `bool bResetMaterials = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Whether to reset the materials along with the rest of the collection, or attempt to keep the current materials across the reset.

#### class `UFractureToolResetAsset`  
`class UFractureToolResetAsset : public UFractureModalTool`  
_L87-109_
- reflection: `UCLASS()`
- inherits: `UFractureModalTool`
- L92 _public prototype_ `UFractureToolResetAsset(const FObjectInitializer& ObjInit);`
- L95 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L96 _public prototype_ `virtual FText GetTooltipText() const override;`
- L97 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L98 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L99 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L100 _public prototype_ `virtual bool CanExecute() const override;`
- L103 _public prototype_ `virtual FText GetApplyText() const override;` — UFractureModalTool Interface
- L104 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L108 _private member_ `TObjectPtr<UGeometryCollectionResetSettings> ResetSettings;` — `UPROPERTY()`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolMaterials.h` (Private)


#### enum `EMaterialAssignmentTargets`  
`enum class EMaterialAssignmentTargets`  
_L13-18_
- reflection: `UENUM()`
- L15 _public enumerator_ `OnlyInternalFaces`
- L16 _public enumerator_ `OnlyExternalFaces`
- L17 _public enumerator_ `AllFaces`

#### class `UFractureMaterialsSettings`  
`class UFractureMaterialsSettings : public UFractureToolSettings`  
_L22-94_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings related to setting materials on a Geometry Collection
- L28 _public function_ `UFractureMaterialsSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L35 _public member_ `FString EditingCollection;` — `UPROPERTY(VisibleAnywhere, Category = AssetMaterials, meta = (NoResetToDefault))` — Geometry Collection selected for editing
- L39 _public member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(EditAnywhere, Category = AssetMaterials, EditFixedSize, meta = (DisplayName = "Asset Materials", NoResetToDefault, EditCondition = "bHaveTargetCollection", HideEditConditionToggle))` — Materials on the selected Geometry Collection's underlying asset (the Rest Collection).
- L43 _public prototype_ `void AddMaterialSlot();` — `UFUNCTION(CallInEditor, Category = AssetMaterials)` — Add a new material slot to the selected geometry collections
- L47 _public prototype_ `void RemoveMaterialSlot();` — `UFUNCTION(CallInEditor, Category = AssetMaterials)` — Remove the last material slot from the selected Geometry Collections. (Will not remove the final material.)
- L51 _public prototype_ `void UseAssetMaterialsOnComponents();` — `UFUNCTION(CallInEditor, Category = ComponentMaterials)` — Clear material overrides on components using this asset, so the asset materials are used
- L55 _public member_ `bool bOnlySelectedComponents = false;` — `UPROPERTY(EditAnywhere, Category = ComponentMaterials)` — Whether 'Use Asset Materials On Components' should only update the selected components, or update all components using this asset
- L59 _public member_ `FString AssignMaterial;` — `UPROPERTY(EditAnywhere, Category = AssignMaterials, meta = (TransientToolProperty, DisplayName = "Assign Material", GetOptions = GetMaterialNamesFunc, NoResetToDefault))` — Material to assign to selected faces
- L63 _public member_ `EMaterialAssignmentTargets ToFaces = EMaterialAssignmentTargets::OnlyInternalFaces;` — `UPROPERTY(EditAnywhere, Category = AssignMaterials)` — Which subset of faces to update materials assignments on, for the selected geometry
- L67 _public member_ `bool bOnlySelectedBones = true;` — `UPROPERTY(EditAnywhere, Category = AssignMaterials)` — Whether to only assign materials for faces in the selected bones, or the whole geometry collection
- L70 _public function_ `const TArray<FString>& GetMaterialNamesFunc()` — `UFUNCTION()`
- L72 _public function_ `void UpdateActiveMaterialNames(TArray<FString> InMaterialNamesList)`
- L81 _public function_ `int32 GetAssignMaterialID()`
- L87 _public member_ `bool bHaveTargetCollection = false;` — `UPROPERTY()`
- L92 _private member_ `TArray<FString> AssignMaterialNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`

#### class `UFractureToolMaterials`  
`class UFractureToolMaterials : public UFractureModalTool`  
_L98-158_
- reflection: `UCLASS(DisplayName = "Materials Tool", Category = "FractureTools")`
- inherits: `UFractureModalTool`
- L103 _public prototype_ `UFractureToolMaterials(const FObjectInitializer& ObjInit);`
- L110 _public prototype_ `virtual FText GetDisplayText() const override;` — This is the Text that will appear on the tool button to execute the tool
- L111 _public prototype_ `virtual FText GetTooltipText() const override;`
- L113 _public function_ `virtual FText GetApplyText() const override` — This is the Text that will appear on the button to execute the fracture
- L114 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L115 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L116 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L117 _public prototype_ `virtual void FractureContextChanged() override;`
- L118 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L120 _public prototype_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override;` — Executes function that generates new geometry. Returns the first new geometry index.
- L121 _public prototype_ `virtual bool CanExecute() const override;`
- L122 _public function_ `virtual bool ExecuteUpdatesShape() const override`
- L126 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L128 _public prototype_ `virtual void SelectedBonesChanged() override;`
- L131 _public function_ `virtual void Setup(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override` — Called when the modal tool is entered
- L137 _public function_ `virtual void Shutdown()`
- L143 _public prototype_ `void UpdateActiveMaterialsInfo();`
- L145 _public prototype_ `virtual TArray<FFractureToolContext> GetFractureToolContexts() const override;`
- L147 _public prototype_ `void RemoveMaterialSlot();`
- L148 _public prototype_ `void AddMaterialSlot();`
- L149 _public prototype_ `void ClearMaterialOverridesOnComponents(bool bOnlySelected = false);`
- L153 _protected member_ `TObjectPtr<UFractureMaterialsSettings> MaterialsSettings;` — `UPROPERTY(EditAnywhere, Category = Slicing)`
- L157 _protected member_ `TWeakObjectPtr<UGeometryCollectionComponent> ActiveSelectedComponent = nullptr;` — `UPROPERTY()` — Track the geometry collection asset last used to populate the materials list, if any

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolMeshCut.h` (Private)


#### enum `EMeshCutDistribution`  
`enum class EMeshCutDistribution`  
_L13-21_
- reflection: `UENUM()`
- L16 _public enumerator_ `SingleCut` — Cut only once, at the cutting mesh's current location in the level
- L18 _public enumerator_ `UniformRandom` — Scatter the cutting mesh in a uniform random distribution around the geometry bounding box
- L20 _public enumerator_ `Grid` — Arrange the cutting mesh in a regular grid pattern

#### class `UFractureMeshCutSettings`  
`class UFractureMeshCutSettings : public UFractureToolSettings`  
_L24-87_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- L29 _public function_ `UFractureMeshCutSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L34 _public member_ `TSoftObjectPtr<AStaticMeshActor> CuttingActor;` — `UPROPERTY(EditAnywhere, Category = MeshCut, meta = (DisplayName = "Cutting Actor"))` — Static Mesh Actor to be used as a cutting surface. For best results, use a closed, watertight mesh
- L38 _public member_ `EMeshCutDistribution CutDistribution = EMeshCutDistribution::SingleCut;` — `UPROPERTY(EditAnywhere, Category = Distribution)` — How to arrange the mesh cuts in space
- L43 _public member_ `int NumberToScatter = 10;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (ClampMin = "1", UIMax = "5000", EditCondition = "CutDistribution == EMeshCutDistribution::UniformRandom", EditConditionHides))` — Number of meshes to random scatter
- L48 _public member_ `int32 GridX = 5;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DisplayName = "Grid Width", ClampMin = "1", UIMax = "100", ClampMax = "5000", EditCondition = "CutDistribution == EMeshCutDistribution::Grid", EditConditionHides))` — Number of meshes to add to grid in X
- L53 _public member_ `int32 GridY = 5;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DisplayName = "Grid Depth", ClampMin = "1", UIMax = "100", ClampMax = "5000", EditCondition = "CutDistribution == EMeshCutDistribution::Grid", EditConditionHides))` — Number of meshes to add to grid in Y
- L58 _public member_ `int32 GridZ = 5;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DisplayName = "Grid Height", ClampMin = "1", UIMax = "100", ClampMax = "5000", EditCondition = "CutDistribution == EMeshCutDistribution::Grid", EditConditionHides))` — Number of meshes to add to grid in Z
- L62 _public member_ `float Variability = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DisplayName = "Variability", EditCondition = "CutDistribution == EMeshCutDistribution::Grid", EditConditionHides, UIMin = "0.0", ClampMin = "0.0"))` — Magnitude of random displacement to cutting meshes
- L66 _public member_ `float MinScaleFactor = .5;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (ClampMin = "0.001", EditCondition = "CutDistribution != EMeshCutDistribution::SingleCut", EditConditionHides))` — Minimum scale factor to apply to cutting meshes. A random scale will be chosen between Min and Max
- L70 _public member_ `float MaxScaleFactor = 1.5;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (ClampMin = "0.001", EditCondition = "CutDistribution != EMeshCutDistribution::SingleCut", EditConditionHides))` — Maximum scale factor to apply to cutting meshes. A random scale will be chosen between Min and Max
- L74 _public member_ `bool bRandomOrientation = true;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (EditCondition = "CutDistribution != EMeshCutDistribution::SingleCut", EditConditionHides))` — Whether to randomly vary the orientation of the cutting meshes
- L78 _public member_ `float RollRange = 180;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DisplayName = "+/- Roll Range", EditCondition = "CutDistribution != EMeshCutDistribution::SingleCut && bRandomOrientation", EditConditionHides, ClampMin = "0", ClampMax = "180"))` — Roll will be chosen between -Range and +Range
- L82 _public member_ `float PitchRange = 180;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DisplayName = "+/- Pitch Range", EditCondition = "CutDistribution != EMeshCutDistribution::SingleCut && bRandomOrientation", EditConditionHides, ClampMin = "0", ClampMax = "180"))` — Pitch will be chosen between -Range and +Range
- L86 _public member_ `float YawRange = 180;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DisplayName = "+/- Yaw Range", EditCondition = "CutDistribution != EMeshCutDistribution::SingleCut && bRandomOrientation", EditConditionHides, ClampMin = "0", ClampMax = "180"))` — Yaw will be chosen between -Range and +Range

#### class `UFractureToolMeshCut`  
`class UFractureToolMeshCut : public UFractureToolCutterBase`  
_L91-142_
- reflection: `UCLASS(DisplayName = "Mesh Cut Tool", Category = "FractureTools")`
- inherits: `UFractureToolCutterBase`
- L96 _public prototype_ `UFractureToolMeshCut(const FObjectInitializer& ObjInit);`
- L99 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L100 _public prototype_ `virtual FText GetTooltipText() const override;`
- L101 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L103 _public prototype_ `void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L105 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L107 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L109 _public prototype_ `virtual void FractureContextChanged() override;`
- L110 _public prototype_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override;`
- L112 _public function_ `virtual void ConfigureCutterSettings() override`
- L123 _protected function_ `virtual void ClearVisualizations() override`
- L133 _private member_ `TObjectPtr<UFractureMeshCutSettings> MeshCutSettings;` — `UPROPERTY(EditAnywhere, Category = Slicing)` — Slicing
- L136 _private prototype_ `bool IsCuttingActorValid();` — check if the chosen actor can be used to cut the geometry collection (i.e. if it is a valid static mesh actor with a non-empty static mesh)
- L138 _private prototype_ `void GenerateMeshTransforms(const FFractureToolContext& Context, TArray<FTransform>& MeshTransforms);`
- L140 _private member_ `TArray<FTransform> RenderMeshTransforms;`
- L141 _private member_ `FVisualizationMappings TransformsMappings;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolPlaneCut.h` (Private)


#### class `UFracturePlaneCutSettings`  
`class UFracturePlaneCutSettings : public UFractureToolSettings`  
_L16-32_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- L21 _public function_ `UFracturePlaneCutSettings(const FObjectInitializer& ObjInit) : Super(ObjInit) , NumberPlanarCuts(1)`
- L27 _public member_ `int32 NumberPlanarCuts;` — `UPROPERTY(EditAnywhere, Category = PlaneCut, meta = (DisplayName = "Number of Cuts", UIMin = "1", UIMax = "20", ClampMin = "1", EditCondition = "bCanCutWithMultiplePlanes", HideEditConditionToggle))` — Number of cutting planes. Only used when "Use Gizmo" is disabled
- L30 _public member_ `bool bCanCutWithMultiplePlanes = false;` — `UPROPERTY()`

#### class `UFractureToolPlaneCut`  
`class UFractureToolPlaneCut : public UFractureToolCutterBase, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L36-98_
- reflection: `UCLASS(DisplayName = "Plane Cut Tool", Category = "FractureTools")`
- inherits: `UFractureToolCutterBase,UE::Geometry::IDynamicMeshOperatorFactory`
- L41 _public prototype_ `UFractureToolPlaneCut(const FObjectInitializer& ObjInit);`
- L44 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L45 _public prototype_ `virtual FText GetTooltipText() const override;`
- L46 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L47 _public prototype_ `virtual void SelectedBonesChanged() override;`
- L50 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L51 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L53 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L55 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L57 _public prototype_ `virtual void FractureContextChanged() override;`
- L58 _public prototype_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override;`
- L60 _public prototype_ `virtual void Setup(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L61 _public prototype_ `virtual void Shutdown() override;`
- L64 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API, for generating noise preview meshes
- L66 _public function_ `virtual void ConfigureCutterSettings() override`
- L74 _protected prototype_ `virtual void ClearVisualizations() override;`
- L76 _protected prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L81 _private member_ `TObjectPtr<UFracturePlaneCutSettings> PlaneCutSettings;` — `UPROPERTY(EditAnywhere, Category = Slicing)` — Slicing
- L84 _private member_ `TObjectPtr<UFractureTransformGizmoSettings> GizmoSettings;` — `UPROPERTY(EditAnywhere, Category = Uniform)`
- L87 _private member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> NoisePreview;` — `UPROPERTY()`
- L89 _private prototype_ `void GenerateSliceTransforms(const FFractureToolContext& Context, TArray<FTransform>& CuttingPlaneTransforms);`
- L91 _private member_ `float RenderCuttingPlaneSize;`
- L92 _private member_ `const float GizmoPlaneSize = 100.f;`
- L93 _private member_ `TArray<FTransform> RenderCuttingPlanesTransforms;`
- L94 _private member_ `TArray<FNoiseOffsets> NoiseOffsets;`
- L95 _private member_ `TArray<FVector> NoisePivots;`
- L96 _private member_ `FVisualizationMappings PlanesMappings;`
- L97 _private member_ `float NoisePreviewExplodeAmount = 0;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolProperties.h` (Private)


#### enum `EDynamicStateOverrideEnum`  
`enum class EDynamicStateOverrideEnum : uint8`  
_L10-17_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `NoOverride = 0 UMETA(DisplayName = "No Override")`
- L14 _public enumerator_ `Sleeping = 1 UMETA(Hidden, DisplayName = "Sleeping")`
- L15 _public enumerator_ `Kinematic = 2 UMETA(DisplayName = "Kinematic")`
- L16 _public enumerator_ `Static = 3 UMETA(DisplayName = "Static")`

#### class `UFractureInitialDynamicStateSettings`  
`class UFractureInitialDynamicStateSettings : public UFractureToolSettings`  
_L21-36_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings specifically related to the one-time destructive fracturing of a mesh
- L27 _public function_ `UFractureInitialDynamicStateSettings(const FObjectInitializer& ObjInit) : Super(ObjInit) , InitialDynamicState(EDynamicStateOverrideEnum::Kinematic)`
- L34 _public member_ `EDynamicStateOverrideEnum InitialDynamicState;` — `UPROPERTY(EditAnywhere, Category = SetInitialDynamicState, meta = (DisplayName = "Initial Dynamic State"))` — Simulation state to be set on selected bones

#### class `UFractureToolSetInitialDynamicState`  
`class UFractureToolSetInitialDynamicState : public UFractureModalTool`  
_L40-65_
- reflection: `UCLASS(DisplayName = "State", Category = "FractureTools")`
- inherits: `UFractureModalTool`
- L45 _public prototype_ `UFractureToolSetInitialDynamicState(const FObjectInitializer& ObjInit);`
- L47 _public typedef_ `using FGeometryCollectionPtr = TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe>;`
- L50 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L51 _public prototype_ `virtual FText GetTooltipText() const override;`
- L52 _public prototype_ `virtual FText GetApplyText() const override;`
- L53 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L54 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L56 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L58 _public prototype_ `virtual void Setup(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L59 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L62 _public member_ `TObjectPtr<UFractureInitialDynamicStateSettings> StateSettings;` — `UPROPERTY(EditAnywhere, Category = InitialDynamicState)`
- L64 _public prototype_ `static void SetSelectedInitialDynamicState(int32 InitialDynamicState);`

#### class `UFractureRemoveOnBreakSettings`  
`class UFractureRemoveOnBreakSettings : public UFractureToolSettings`  
_L68-101_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- L74 _public function_ `UFractureRemoveOnBreakSettings(const FObjectInitializer& ObjInit) : Super(ObjInit) , Enabled(true) , PostBreakTimer(0,0) , ClusterCrumbling(false) , RemovalTimer(2,3)`
- L84 _public member_ `bool Enabled;` — `UPROPERTY(EditAnywhere, Category = SetRemoveOnBreak, meta = (DisplayName = "Enabled"))` — whether or not the remove on fracture is enabled
- L88 _public member_ `FVector2f PostBreakTimer;` — `UPROPERTY(EditAnywhere, Category = SetRemoveOnBreak, meta = (DisplayName = "Post Break Timer", EditCondition="Enabled"))` — Min/Max time after break before removal starts
- L92 _public member_ `bool ClusterCrumbling;` — `UPROPERTY(EditAnywhere, Category = SetRemoveOnBreak, meta = (DisplayName = "Cluster Crumbling", EditCondition="Enabled"))` — When set, clusters will crumble when post break timer expires, non clusters will simply use the removal timer
- L96 _public member_ `FVector2f RemovalTimer;` — `UPROPERTY(EditAnywhere, Category = SetRemoveOnBreak, meta = (DisplayName = "Removal Timer", EditCondition="!ClusterCrumbling && Enabled"))` — Min/Max time for how long removal lasts - not applicable when cluster crumbling is on
- L100 _public prototype_ `void DeleteRemoveOnBreakData();` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayName = "Delete Remove-On-Break Data"))` — remove the remove on break attribute from the geometry collection, usefull to save memory on the asset if not needed

#### class `UFractureToolSetRemoveOnBreak`  
`class UFractureToolSetRemoveOnBreak : public UFractureModalTool`  
_L104-133_
- reflection: `UCLASS(DisplayName = "RemoveOnBreak", Category = "FractureTools")`
- inherits: `UFractureModalTool`
- L109 _public prototype_ `UFractureToolSetRemoveOnBreak(const FObjectInitializer& ObjInit);`
- L111 _public typedef_ `using FGeometryCollectionPtr = TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe>;`
- L114 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L115 _public prototype_ `virtual FText GetTooltipText() const override;`
- L116 _public prototype_ `virtual FText GetApplyText() const override;`
- L117 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L118 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L120 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L122 _public prototype_ `virtual void Setup(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L124 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L126 _public prototype_ `void DeleteRemoveOnBreakData();`
- L129 _public member_ `TObjectPtr<UFractureRemoveOnBreakSettings> RemoveOnBreakSettings;` — `UPROPERTY(EditAnywhere, Category = InitialDynamicState)`
- L132 _private member_ `TWeakPtr<FFractureEditorModeToolkit> Toolkit;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolProximity.h` (Private)


#### class `UFractureProximitySettings`  
`class UFractureProximitySettings : public UFractureToolSettings`  
_L15-73_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings controlling how proximity is detected for geometry collections
- L21 _public function_ `UFractureProximitySettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L27 _public member_ `EProximityMethod Method = EProximityMethod::Precise;` — `UPROPERTY(EditAnywhere, Category = Automatic)` — Which method to use to decide whether a given piece of geometry is in proximity with another
- L32 _public member_ `double DistanceThreshold = 1;` — `UPROPERTY(EditAnywhere, Category = Automatic, meta = (ClampMin = "0", EditCondition = "Method == EProximityMethod::ConvexHull || ContactMethod == EProximityContactMethod::ConvexHullSharpContact || ContactMethod == EProximityContactMethod::ConvexHullAreaContact || ContactAreaMethod == EConnectionContactMethod::ConvexHullContactArea"))` — If hull-based proximity detection is enabled, amount to expand hulls when searching for overlapping neighbors
- L36 _public member_ `EProximityContactMethod ContactMethod = EProximityContactMethod::MinOverlapInProjectionToMajorAxes;` — `UPROPERTY(EditAnywhere, Category = Automatic)` — Method to use to determine the contact between two pieces, if the Contact Threshold is greater than 0
- L40 _public member_ `double ContactThreshold = 0;` — `UPROPERTY(EditAnywhere, Category = Automatic, meta = (ClampMin = "0"))` — If greater than zero, proximity will be additionally filtered by a 'contact' threshold, in cm, to exclude grazing / corner proximity
- L44 _public member_ `bool bUseAsConnectionGraph = false;` — `UPROPERTY(EditAnywhere, Category = Automatic)` — Whether to automatically transform the proximity graph into a connection graph to be used for simulation
- L48 _public member_ `EConnectionContactMethod ContactAreaMethod = EConnectionContactMethod::None;` — `UPROPERTY(EditAnywhere, Category = Automatic)` — Method to use for determining contact areas that define the strength of connections for destruction simulation
- L52 _public member_ `bool bShowProximity = true;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — Whether to display the proximity graph edges
- L56 _public member_ `bool bOnlyShowForSelected = false;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (EditCondition = "bShowProximity"))` — Whether to only show the proximity graph connections for selected bones
- L60 _public member_ `float LineThickness = 0.5;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Line thickness for connections
- L64 _public member_ `FColor LineColor = FColor::Yellow;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — Line color for connections
- L68 _public member_ `float CenterSize = 8.f;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (ClampMin = "0.0", ClampMax = "20.0"))` — Point size for centers
- L72 _public member_ `FColor CenterColor = FColor::Blue;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — Point color for centers

#### class `UFractureProximityActions`  
`class UFractureProximityActions : public UFractureToolSettings`  
_L81-99_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: UFUNCTION actions to manage default proximity detection settings for geometry collections (These are pulled out from the above settings object mainly to control their ordering in the properties panel)
- L87 _public function_ `UFractureProximityActions(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L93 _public prototype_ `void SaveAsDefaults();` — `UFUNCTION(CallInEditor, Category = ProjectDefaults, meta = (DisplayName = "Save As Defaults"))` — Save settings as project defaults, to be used for all new geometry collections
- L97 _public prototype_ `void SetFromDefaults();` — `UFUNCTION(CallInEditor, Category = ProjectDefaults, meta = (DisplayName = "Set From Defaults"))` — Set settings from current project defaults

#### class `UFractureToolProximity`  
`class UFractureToolProximity : public UFractureModalTool`  
_L103-165_
- reflection: `UCLASS(DisplayName = "Proximity Tool", Category = "FractureTools")`
- inherits: `UFractureModalTool`
- L108 _public prototype_ `UFractureToolProximity(const FObjectInitializer& ObjInit);`
- L115 _public prototype_ `virtual FText GetDisplayText() const override;` — This is the Text that will appear on the tool button to execute the tool
- L116 _public prototype_ `virtual FText GetTooltipText() const override;`
- L118 _public function_ `virtual FText GetApplyText() const override` — This is the Text that will appear on the button to execute the fracture
- L119 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L120 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L121 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L122 _public prototype_ `virtual void FractureContextChanged() override;`
- L123 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L125 _public prototype_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override;` — Executes function that generates new geometry. Returns the first new geometry index.
- L126 _public prototype_ `virtual bool CanExecute() const override;`
- L127 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L130 _public prototype_ `const TSharedPtr<FUICommandInfo>& GetUICommandInfo() const;` — Gets the UI command info for this command
- L132 _public prototype_ `virtual TArray<FFractureToolContext> GetFractureToolContexts() const override;`
- L134 _public prototype_ `virtual void Setup(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L137 _public member_ `TObjectPtr<UFractureProximitySettings> ProximitySettings;` — `UPROPERTY(EditAnywhere, Category = Proximity)`
- L142 _private member_ `TObjectPtr<UFractureProximityActions> ProximityActions;` — `UPROPERTY(EditAnywhere, Category = Proximity)`
- L144 _private prototype_ `void UpdateVisualizations();`
- L145 _private function_ `virtual void ClearVisualizations() override`
- L163 _private member_ `TArray<FCollectionVisInfo> ProximityVisualizations;`

#### struct `UFractureToolProximity::FEdgeVisInfo`  
`struct FEdgeVisInfo`  
_L151-154_
- L153 _public member_ `int32 A, B;`
- L153 _public member_ `int32 A, B;`

#### struct `UFractureToolProximity::FCollectionVisInfo`  
`struct FCollectionVisInfo`  
_L156-161_
- L158 _public member_ `TArray<FEdgeVisInfo> ProximityEdges;`
- L159 _public member_ `TArray<FVector> GeoCenters;`
- L160 _public member_ `int32 CollectionIndex;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolRadial.h` (Private)


#### class `UFractureRadialSettings`  
`class UFractureRadialSettings : public UFractureToolSettings`  
_L13-79_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- L18 _public function_ `UFractureRadialSettings(const FObjectInitializer& ObjInit) : Super(ObjInit) , Center(FVector(0, 0, 0)) , Normal(FVector(0, 0, 1))`
- L26 _public member_ `FVector Center;` — `UPROPERTY(EditAnywhere, Category = RadialVoronoi, meta = (EditCondition = "!bPositionedByGizmo", HideEditConditionToggle))` — Center of generated pattern. Only used when "Use Gizmo" is disabled
- L30 _public member_ `FVector Normal;` — `UPROPERTY(EditAnywhere, Category = RadialVoronoi, meta = (EditCondition = "!bPositionedByGizmo", HideEditConditionToggle))` — Normal to plane in which sites are generated. Only used when "Use Gizmo" is disabled
- L33 _public member_ `bool bPositionedByGizmo = true;` — `UPROPERTY()`
- L37 _public member_ `int AngularSteps = 5;` — `UPROPERTY(EditAnywhere, Category = RadialVoronoi, meta = (DisplayName = "Angular Steps", UIMin = "1", UIMax = "50", ClampMin = "1"))` — Number of angular steps
- L41 _public member_ `float AngleOffset = 0.0f;` — `UPROPERTY(EditAnywhere, Category = RadialVoronoi, meta = (DisplayName = "Angle Offset"))` — Angle offset at each radial step (in degrees)
- L45 _public member_ `float AngularNoise = 0.f;` — `UPROPERTY(EditAnywhere, Category = RadialVoronoi)` — Amount of global variation to apply to each angular step (in degrees)
- L49 _public member_ `float Radius = 50.0f;` — `UPROPERTY(EditAnywhere, Category = RadialVoronoi, meta = (DisplayName = "Radius", UIMin = "0.0", ClampMin = "0.0"))` — Pattern radius (in cm)
- L53 _public member_ `int RadialSteps = 5;` — `UPROPERTY(EditAnywhere, Category = RadialVoronoi, meta = (DisplayName = "Radial Steps", UIMin = "1", UIMax = "50", ClampMin = "1"))` — Number of radial steps
- L57 _public member_ `float RadialStepExponent = 1.f;` — `UPROPERTY(EditAnywhere, Category = RadialVoronoi, meta = (UIMin = ".01", UIMax = "10", ClampMin = ".01", ClampMax = "20"))` — Radial steps will follow a distribution based on this exponent, i.e., Pow(distance from center, RadialStepExponent)
- L61 _public member_ `float RadialMinStep = 1.f;` — `UPROPERTY(EditAnywhere, Category = RadialVoronoi, meta = (UIMin = ".25", ClampMin = ".01"))` — Minimum radial separation between any two voronoi points (in cm)
- L65 _public member_ `float RadialNoise = 0.f;` — `UPROPERTY(EditAnywhere, Category = RadialVoronoi, meta = (ClampMin = "0"))` — Amount of global variation to apply to each radial step (in cm)
- L70 _public member_ `float RadialVariability = 0.f;` — `UPROPERTY(EditAnywhere, Category = PerPointVariability, meta = (ClampMin = "0.0"))` — Amount to randomly displace each Voronoi site radially (in cm)
- L74 _public member_ `float AngularVariability = 0.f;` — `UPROPERTY(EditAnywhere, Category = PerPointVariability, meta = (ClampMin = "0.0"))` — Amount to randomly displace each Voronoi site in angle (in degrees)
- L78 _public member_ `float AxialVariability = 0.f;` — `UPROPERTY(EditAnywhere, Category = PerPointVariability, meta = (ClampMin = "0.0"))` — Amount to randomly displace each Voronoi site in the direction of the rotation axis (in cm)

#### class `UFractureToolRadial`  
`class UFractureToolRadial : public UFractureToolVoronoiCutterBase`  
_L83-119_
- reflection: `UCLASS(DisplayName="Radial Voronoi", Category="FractureTools")`
- inherits: `UFractureToolVoronoiCutterBase`
- L88 _public prototype_ `UFractureToolRadial(const FObjectInitializer& ObjInit);`
- L91 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L92 _public prototype_ `virtual FText GetTooltipText() const override;`
- L93 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L94 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L95 _public prototype_ `virtual void SelectedBonesChanged() override;`
- L97 _public prototype_ `virtual void RegisterUICommand( FFractureEditorCommands* BindingContext ) override;`
- L101 _public member_ `TObjectPtr<UFractureRadialSettings> RadialSettings;` — `UPROPERTY(EditAnywhere, Category = Uniform)` — Radial Voronoi Fracture Input Settings
- L104 _public member_ `TObjectPtr<UFractureTransformGizmoSettings> GizmoSettings;` — `UPROPERTY(EditAnywhere, Category = Uniform)`
- L106 _public prototype_ `virtual void Setup(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L107 _public prototype_ `virtual void Shutdown() override;`
- L109 _public function_ `virtual void UpdateUseGizmo(bool bUseGizmo) override`
- L117 _protected prototype_ `void GenerateVoronoiSites(const FFractureToolContext& Context, TArray<FVector>& Sites) override;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolRecomputeNormals.h` (Private)


#### class `UFractureRecomputeNormalsSettings`  
`class UFractureRecomputeNormalsSettings : public UFractureToolSettings`  
_L14-51_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings for visualizing and recomputing normals and tangents
- L20 _public function_ `UFractureRecomputeNormalsSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L26 _public member_ `bool bShowNormals = true;` — `UPROPERTY(EditAnywhere, Category = DisplaySettings)` — Whether to display normal vectors
- L30 _public member_ `bool bShowTangents = true;` — `UPROPERTY(EditAnywhere, Category = DisplaySettings)` — Whether to display tangent and bitangent vectors
- L34 _public member_ `float Length = 2.0f;` — `UPROPERTY(EditAnywhere, Category = DisplaySettings, meta = (ClampMin = ".001", ClampMax = "100", UIMax = "10"))` — Length of display normal and tangent vectors
- L38 _public member_ `bool bOnlyTangents = false;` — `UPROPERTY(EditAnywhere, Category = RecomputeSettings)` — Whether to only recompute tangents, and leave normals as they were
- L42 _public member_ `bool bRecomputeSharpEdges = false;` — `UPROPERTY(EditAnywhere, Category = RecomputeSettings, meta = (EditCondition = "!bOnlyTangents"))` — If true, update where edges are 'sharp' by comparing adjacent triangle face normals vs the Sharp Edge Angle Threshold.
- L46 _public member_ `float SharpEdgeAngleThreshold = 60.0f;` — `UPROPERTY(EditAnywhere, Category = RecomputeSettings, meta = (UIMin = "0.0", UIMax = "180.0", ClampMin = "0.0", ClampMax = "180.0", EditCondition = "bRecomputeSharpEdges && !bOnlyTangents"))` — Threshold on angle of change in face normals across an edge, above which we create a sharp edge if bRecomputeSharpEdges is true
- L50 _public member_ `bool bOnlyInternalSurfaces = true;` — `UPROPERTY(EditAnywhere, Category = RecomputeSettings, AdvancedDisplay)` — Whether to only change internal surface normals / tangents

#### class `UFractureToolRecomputeNormals`  
`class UFractureToolRecomputeNormals : public UFractureToolCutterBase`  
_L56-103_
- reflection: `UCLASS(DisplayName = "Recompute Normals Tool", Category = "FractureTools")`
- inherits: `UFractureToolCutterBase`
- desc: Note this tool doesn't actually fracture, but it does remake pieces of geometry and shares a lot of machinery with the fracture tools
- L61 _public prototype_ `UFractureToolRecomputeNormals(const FObjectInitializer& ObjInit);`
- L64 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L65 _public prototype_ `virtual FText GetTooltipText() const override;`
- L66 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L68 _public function_ `virtual FText GetApplyText() const override`
- L70 _public prototype_ `void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L72 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L74 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L76 _public prototype_ `virtual void FractureContextChanged() override;`
- L77 _public prototype_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override;`
- L78 _public function_ `virtual bool ExecuteUpdatesShape() const override`
- L85 _protected member_ `TObjectPtr<UFractureRecomputeNormalsSettings> NormalsSettings;` — `UPROPERTY()`
- L87 _protected function_ `virtual void ClearVisualizations() override`
- L97 _protected member_ `TArray<FVector> DisplayVertices;`
- L98 _protected member_ `TArray<FVector> DisplayNormals;`
- L99 _protected member_ `TArray<FVector> DisplayTanUs;`
- L100 _protected member_ `TArray<FVector> DisplayTanVs;`
- L101 _protected member_ `FVisualizationMappings PointsMappings;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolResample.h` (Private)


#### class `UFractureResampleSettings`  
`class UFractureResampleSettings : public UFractureToolSettings`  
_L14-28_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings giving additional control over geometry resampling + related visualization
- L20 _public function_ `UFractureResampleSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L26 _public member_ `bool bOnlyShowAddedPoints = false;` — `UPROPERTY(EditAnywhere, Category = FilterSettings)` — Whether to visualize all mesh vertices or only the ones added by resampling

#### class `UFractureToolResample`  
`class UFractureToolResample : public UFractureToolCutterBase`  
_L32-75_
- reflection: `UCLASS(DisplayName = "Resample Tool", Category = "FractureTools")`
- inherits: `UFractureToolCutterBase`
- desc: Note this tool doesn't actually fracture, but it does remake pieces of geometry and shares a lot of machinery with the fracture tools
- L37 _public prototype_ `UFractureToolResample(const FObjectInitializer& ObjInit);`
- L40 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L41 _public prototype_ `virtual FText GetTooltipText() const override;`
- L42 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L44 _public function_ `virtual FText GetApplyText() const override`
- L46 _public prototype_ `void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L48 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L50 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L52 _public prototype_ `virtual void FractureContextChanged() override;`
- L53 _public prototype_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override;`
- L54 _public function_ `virtual bool ExecuteUpdatesShape() const override`
- L60 _protected function_ `virtual void ClearVisualizations() override`
- L71 _private member_ `TObjectPtr<UFractureResampleSettings> ResampleSettings;` — `UPROPERTY(EditAnywhere, Category = FixGeo)`
- L73 _private member_ `TArray<FVector> GeneratedPoints;`
- L74 _private member_ `FVisualizationMappings PointsMappings;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolSelection.h` (Private)


#### enum `EVolumeSelectionMethod`  
`enum class EVolumeSelectionMethod`  
_L18-26_
- reflection: `UENUM()`
- L21 _public enumerator_ `CubeRootOfVolume` — Select by cube root of volume
- L23 _public enumerator_ `RelativeToWhole` — Select by cube root of volume relative to the overall shape's cube root of volume
- L25 _public enumerator_ `RelativeToLargest` — Select by cube root of volume relative to the largest single geometry

#### enum `ESelectionOperation`  
`enum class ESelectionOperation`  
_L29-34_
- reflection: `UENUM()`
- L31 _public enumerator_ `Replace`
- L32 _public enumerator_ `Add`
- L33 _public enumerator_ `Remove`

#### enum `EMouseSelectionMethod`  
`enum class EMouseSelectionMethod`  
_L37-44_
- reflection: `UENUM()`
- L40 _public enumerator_ `RectSelect` — Click+Drag a rectangle to select -- hold shift to append, ctrl to subtract, and ctrl+shift to toggle
- L42 _public enumerator_ `StandardSelect` — Selection that works the same as when the tool is not active

#### class `UFractureSelectionSettings`  
`class UFractureSelectionSettings : public UFractureToolSettings`  
_L48-92_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings controlling how geometry is selected
- L54 _public function_ `UFractureSelectionSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L59 _public member_ `EMouseSelectionMethod MouseSelectionMethod = EMouseSelectionMethod::RectSelect;` — `UPROPERTY(EditAnywhere, Category = MouseInteraction)`
- L63 _public member_ `EVolumeSelectionMethod VolumeSelectionMethod = EVolumeSelectionMethod::RelativeToLargest;` — `UPROPERTY(EditAnywhere, Category = FilterSettings)` — What values to use when filtering by volume.  Note all values are presented as cube roots to give more intuitive scales (e.g., to select bones with volume less than a 10x10x10 cube, choose CubeRootOfVolume and MaxVolume=10, rather than needing to multiply out to 1000)
- L67 _public member_ `ESelectionOperation SelectionOperation = ESelectionOperation::Replace;` — `UPROPERTY(EditAnywhere, Category = FilterSettings)` — How to update the selection from the filter
- L71 _public member_ `double MinVolume = 0;` — `UPROPERTY(EditAnywhere, Category = FilterSettings, meta = (ClampMin = ".00001", UIMin = ".1", UIMax = "1000", EditCondition = "VolumeSelectionMethod == EVolumeSelectionMethod::CubeRoot", EditConditionHides))` — Sets the minimum volume (as computed by the Volume Selection Method) that should be included in the filter
- L75 _public member_ `double MaxVolume = 0;` — `UPROPERTY(EditAnywhere, Category = FilterSettings, meta = (ClampMin = ".00001", UIMin = ".1", UIMax = "1000", EditCondition = "VolumeSelectionMethod == EVolumeSelectionMethod::CubeRoot", EditConditionHides))` — Sets the maximum volume (as computed by the Volume Selection Method) that should be included in the filter
- L79 _public member_ `double MinVolumeFrac = 0;` — `UPROPERTY(EditAnywhere, Category = FilterSettings, meta = (ClampMin = ".00001", UIMin = ".01", UIMax = "1", EditCondition = "VolumeSelectionMethod != EVolumeSelectionMethod::CubeRoot", EditConditionHides))` — Sets the minimum volume (as computed by the Volume Selection Method) that should be included in the filter
- L83 _public member_ `double MaxVolumeFrac = 0;` — `UPROPERTY(EditAnywhere, Category = FilterSettings, meta = (ClampMin = ".00001", UIMin = ".01", UIMax = "1", EditCondition = "VolumeSelectionMethod != EVolumeSelectionMethod::CubeRoot", EditConditionHides))` — Sets the maximum volume (as computed by the Volume Selection Method) that should be included in the filter
- L87 _public member_ `double KeepFraction = 1;` — `UPROPERTY(EditAnywhere, Category = FilterSettings, meta = (ClampMin = ".00001", UIMin = ".01", UIMax = "1"))` — Fraction of bones to keep in the selection: If less than 1, bones will be randomly excluded from the selection filter
- L91 _public member_ `int RandomSeed = 1;` — `UPROPERTY(EditAnywhere, Category = FilterSettings)` — Seed to use for randomization when deciding which bones to keep w/ the Keep Fraction

#### class `URectangleMarqueeManager`  
`class URectangleMarqueeManager : public UObject, public IClickDragBehaviorTarget`  
_L111-194_
- reflection: `UCLASS()`
- inherits: `UObject,IClickDragBehaviorTarget`
- desc: Adapted from URectangleMarqueeMechanic, the mechanic for a rectangle "marquee" selection, to operate without the UInteractionMechanic framework. It creates and maintains the 2D rectangle associated with a mouse drag. It does not test against any scene geometry, nor does it maintain any sort of list of selected objects. You must manually call the Setup(), Render() and DrawHUD() functions. Note these functions have been changed from the Mechanic versions to be easier to call without additional InteractiveTool machinery Attach to the delegates and use the passed rectangle to test against your geometry. TODO: Refactor this into a more generalized / generally usable class in RectangleMarqueeMechanic.h, and share more common code with URectangleMarqueeMechanic.
- L123 _public member_ `bool bUseExternalClickDragBehavior = false;` — `UPROPERTY()` — If true, then the URectangleMarqueeManager will not create an internal UClickDragInputBehavior in ::Setup(), allowing the client to control the marquee with an external InputBehavior that uses the marquee manager as its IClickDragBehaviorTarget. For instance, this allows the mechanic to be hooked in as the drag component of a USingleClickOrDragInputBehavior. Must be configured before calling ::Setup()
- L132 _public member_ `double OnDragRectangleChangedDeferredThreshold = TNumericLimits<double>::Max();` — `UPROPERTY()` — If the computation time for a single call to OnDragRectangleChanged ever exceeds this threshold then future calls to this function (in the current drag sequence) will be deferred until the mouse button is released. This will improve the responsiveness of the UI. The default value is set so this optimization is never triggered, if you want it you can set this to a small value e.g., 1./60 (time elapsed by 1 frame at 60 fps)
- L136 _public prototype_ `void Setup(TFunctionRef<void(UInputBehavior*, void*)> AddBehaviorFunc);`
- L137 _public prototype_ `void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI);`
- L138 _public prototype_ `void DrawHUD(FCanvas* Canvas, bool bThisViewHasFocus);`
- L140 _public prototype_ `bool IsEnabled();`
- L141 _public prototype_ `void SetIsEnabled(bool bOn);`
- L149 _public prototype_ `void SetBasePriority(const FInputCapturePriority& Priority);` — Sets the base priority so that users can make sure that their own behaviors are higher priority. The marquee will not use any priority value higher than this. Can be called before or after Setup(). Only relevant if bUseExternalClickDragBehavior is false
- L154 _public prototype_ `FInputCapturePriority GetPriority() const;` — Gets the current priority used by the marquee behavior
- L159 _public member_ `FSimpleMulticastDelegate OnDragRectangleStarted;` — Called when user starts dragging a new rectangle.
- L164 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnDragRectangleChangedEvent, const FCameraRectangle&);` — Called as the user drags the other corner of the rectangle around.
- L165 _public member_ `OnDragRectangleChangedEvent OnDragRectangleChanged;`
- L172 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(OnDragRectangleFinishedEvent, const FCameraRectangle&, bool bCancelled);` — Called once the user lets go of the mouse button after dragging out a rectangle. The last dragged rectangle is passed here so that clients can choose to just implement this function in simple cases. bCancelled flag is true when the drag finishes due to a disabling of the mechanic or due to a TerminateDragSequence call, rather than a normal drag completion.
- L173 _public member_ `OnDragRectangleFinishedEvent OnDragRectangleFinished;`
- L177 _protected member_ `TObjectPtr<UClickDragInputBehavior> ClickDragBehavior = nullptr;` — `UPROPERTY()`
- L179 _protected member_ `FCameraRectangle CameraRectangle;`
- L181 _protected member_ `FInputCapturePriority BasePriority = FInputCapturePriority(FInputCapturePriority::DEFAULT_TOOL_PRIORITY);`
- L185 _private prototype_ `FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos);`
- L186 _private prototype_ `void OnClickPress(const FInputDeviceRay& PressPos);`
- L187 _private prototype_ `void OnClickDrag(const FInputDeviceRay& DragPos);`
- L188 _private prototype_ `void OnClickRelease(const FInputDeviceRay& ReleasePos);`
- L189 _private prototype_ `void OnTerminateDragSequence();`
- L191 _private member_ `bool bIsEnabled;`
- L192 _private member_ `bool bIsDragging;`
- L193 _private member_ `bool bIsOnDragRectangleChangedDeferred;`

#### class `UFractureToolSelection`  
`class UFractureToolSelection : public UFractureToolCutterBase, public IClickBehaviorTarget`  
_L201-286_
- reflection: `UCLASS(DisplayName = "Custom Selection Tool", Category = "FractureTools")`
- inherits: `UFractureToolCutterBase,IClickBehaviorTarget`
- desc: Note this tool doesn't actually fracture, but it does remake pieces of geometry and shares a lot of machinery with the fracture tools
- L206 _public prototype_ `UFractureToolSelection(const FObjectInitializer& ObjInit);`
- L209 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L210 _public prototype_ `virtual FText GetTooltipText() const override;`
- L211 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L213 _public function_ `virtual FText GetApplyText() const override`
- L215 _public prototype_ `void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L216 _public prototype_ `void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L218 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L220 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L222 _public prototype_ `virtual void FractureContextChanged() override;`
- L224 _public function_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override` — ExecuteFracture unused, because this tool doesn't modify geometry; instead, it overrides Execute
- L225 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L226 _public prototype_ `void UpdateSelection(FFractureToolContext& FractureContext);`
- L228 _public prototype_ `virtual void Setup(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L229 _public prototype_ `virtual void Shutdown() override;`
- L232 _public function_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override` — IClickBehaviorTarget implementation
- L236 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L237 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L239 _public prototype_ `void CreateRectangleSelectionBehavior();`
- L240 _public prototype_ `void DestroyRectangleSelectionBehavior();`
- L243 _protected function_ `virtual void ClearVisualizations() override`
- L251 _protected member_ `TObjectPtr<UInputBehaviorSet> SelectionBehaviorSet = nullptr;` — `UPROPERTY()`
- L254 _protected member_ `TObjectPtr<ULocalInputBehaviorSource> SelectionBehaviorSource = nullptr;` — `UPROPERTY()`
- L257 _protected member_ `TObjectPtr<URectangleMarqueeManager> RectangleMarqueeManager = nullptr;` — `UPROPERTY()`
- L261 _protected member_ `TObjectPtr<UInteractiveToolsContext> UsedToolsContext = nullptr;` — `UPROPERTY()` — the tools context responsible for the selection input router
- L264 _protected member_ `bool bShiftToggle = false;` — Support for Shift and Ctrl toggle
- L265 _protected member_ `bool bCtrlToggle = false;`
- L266 _protected member_ `static const int32 ShiftModifierID = 1;`
- L267 _protected member_ `static const int32 CtrlModifierID = 2;`
- L270 _protected prototype_ `void OnDragRectangleStarted();` — Rectangle selection
- L271 _protected prototype_ `void OnDragRectangleChanged(const FCameraRectangle& Rectangle);`
- L272 _protected prototype_ `void OnDragRectangleFinished(const FCameraRectangle& Rectangle, bool bCancelled);`
- L277 _private member_ `TObjectPtr<UFractureSelectionSettings> SelectionSettings;` — `UPROPERTY(EditAnywhere, Category = FixGeo)`
- L279 _private member_ `TArray<FBox> SelectionBounds;` — Bounds in global space but without exploded vectors applied
- L280 _private member_ `FVisualizationMappings SelectionMappings;`
- L282 _private prototype_ `TInterval<float> GetVolumeRange(const TManagedArray<float>& Volumes, const TManagedArray<int32>& SimulationType) const;`
- L283 _private prototype_ `bool GetBonesByVolume(const FGeometryCollection& Collection, TArray<int32>& FilterIndices);`
- L284 _private member_ `const double VolDimScale = .01;` — compute volumes in meters instead of cm, for saner units at typical scales

#### Free symbols / members of external scopes

- L164 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnDragRectangleChangedEvent, const FCameraRectangle&);` — Called as the user drags the other corner of the rectangle around.
- L172 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(OnDragRectangleFinishedEvent, const FCameraRectangle&, bool bCancelled);` — Called once the user lets go of the mouse button after dragging out a rectangle. The last dragged rectangle is passed here so that clients can choose to just implement this function in simple cases. bCancelled flag is true when the drag finishes due to a disabling of the mechanic or due to a TerminateDragSequence call, rather than a normal drag completion.

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolSelectors.h` (Private)


#### class `UFractureToolSelectAll`  
`class UFractureToolSelectAll : public UFractureActionTool`  
_L19-35_
- reflection: `UCLASS(DisplayName = "Select All", Category = "FractureTools")`
- inherits: `UFractureActionTool`
- L24 _public function_ `UFractureToolSelectAll(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L27 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L28 _public prototype_ `virtual FText GetTooltipText() const override;`
- L29 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L30 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L31 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`
- L34 _protected prototype_ `void SelectByMode(FFractureEditorModeToolkit* InToolkit, GeometryCollection::ESelectionMode SelectionMode);`

#### class `UFractureToolSelectNone`  
`class UFractureToolSelectNone : public UFractureToolSelectAll`  
_L39-52_
- reflection: `UCLASS(DisplayName = "Select None", Category = "FractureTools")`
- inherits: `UFractureToolSelectAll`
- L44 _public function_ `UFractureToolSelectNone(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L47 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L48 _public prototype_ `virtual FText GetTooltipText() const override;`
- L49 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L50 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L51 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolSelectNeighbors`  
`class UFractureToolSelectNeighbors : public UFractureToolSelectAll`  
_L56-69_
- reflection: `UCLASS(DisplayName = "Select Neighbors", Category = "FractureTools")`
- inherits: `UFractureToolSelectAll`
- L61 _public function_ `UFractureToolSelectNeighbors(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L64 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L65 _public prototype_ `virtual FText GetTooltipText() const override;`
- L66 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L67 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L68 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolSelectParent`  
`class UFractureToolSelectParent : public UFractureToolSelectAll`  
_L73-86_
- reflection: `UCLASS(DisplayName = "Select Parent", Category = "FractureTools")`
- inherits: `UFractureToolSelectAll`
- L78 _public function_ `UFractureToolSelectParent(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L81 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L82 _public prototype_ `virtual FText GetTooltipText() const override;`
- L83 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L84 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L85 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolSelectChildren`  
`class UFractureToolSelectChildren : public UFractureToolSelectAll`  
_L90-103_
- reflection: `UCLASS(DisplayName = "Select Children", Category = "FractureTools")`
- inherits: `UFractureToolSelectAll`
- L95 _public function_ `UFractureToolSelectChildren(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L98 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L99 _public prototype_ `virtual FText GetTooltipText() const override;`
- L100 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L101 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L102 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolSelectSiblings`  
`class UFractureToolSelectSiblings : public UFractureToolSelectAll`  
_L106-119_
- reflection: `UCLASS(DisplayName = "Select Siblings", Category = "FractureTools")`
- inherits: `UFractureToolSelectAll`
- L111 _public function_ `UFractureToolSelectSiblings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L114 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L115 _public prototype_ `virtual FText GetTooltipText() const override;`
- L116 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L117 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L118 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolSelectAllInLevel`  
`class UFractureToolSelectAllInLevel : public UFractureToolSelectAll`  
_L123-136_
- reflection: `UCLASS(DisplayName = "Select All In Level", Category = "FractureTools")`
- inherits: `UFractureToolSelectAll`
- L128 _public function_ `UFractureToolSelectAllInLevel(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L131 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L132 _public prototype_ `virtual FText GetTooltipText() const override;`
- L133 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L134 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L135 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolSelectInvert`  
`class UFractureToolSelectInvert : public UFractureToolSelectAll`  
_L140-153_
- reflection: `UCLASS(DisplayName = "Select Invert", Category = "FractureTools")`
- inherits: `UFractureToolSelectAll`
- L145 _public function_ `UFractureToolSelectInvert(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L148 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L149 _public prototype_ `virtual FText GetTooltipText() const override;`
- L150 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L151 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L152 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolSelectLeaf`  
`class UFractureToolSelectLeaf : public UFractureToolSelectAll`  
_L157-170_
- reflection: `UCLASS(DisplayName = "Select Leaves", Category = "FractureTools")`
- inherits: `UFractureToolSelectAll`
- L162 _public function_ `UFractureToolSelectLeaf(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L165 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L166 _public prototype_ `virtual FText GetTooltipText() const override;`
- L167 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L168 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L169 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### class `UFractureToolSelectCluster`  
`class UFractureToolSelectCluster : public UFractureToolSelectAll`  
_L174-187_
- reflection: `UCLASS(DisplayName = "Select Clusters", Category = "FractureTools")`
- inherits: `UFractureToolSelectAll`
- L179 _public function_ `UFractureToolSelectCluster(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L182 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureActionTool Interface
- L183 _public prototype_ `virtual FText GetTooltipText() const override;`
- L184 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L185 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L186 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace GeometryCollection`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolSlice.h` (Private)


#### class `UFractureSliceSettings`  
`class UFractureSliceSettings : public UFractureToolSettings`  
_L14-47_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- L19 _public function_ `UFractureSliceSettings(const FObjectInitializer& ObjInit) : Super(ObjInit) , SlicesX(3) , SlicesY(3) , SlicesZ(1) , SliceAngleVariation(0.0f) , SliceOffsetVariation(0.0f)`
- L30 _public member_ `int32 SlicesX;` — `UPROPERTY(EditAnywhere, Category = Slicing, meta = (UIMin = "0"))` — Number of slices along the X axis
- L34 _public member_ `int32 SlicesY;` — `UPROPERTY(EditAnywhere, Category = Slicing, meta = (UIMin = "0"))` — Number of slices along the Y axis
- L38 _public member_ `int32 SlicesZ;` — `UPROPERTY(EditAnywhere, Category = Slicing, meta = (UIMin = "0"))` — Number of slices along the Z axis
- L42 _public member_ `float SliceAngleVariation;` — `UPROPERTY(EditAnywhere, Category = Slicing, meta = (DisplayName = "Random Angle Variation", UIMin = "0.0", UIMax = "90.0"))` — Maximum angle (in degrees) to randomly rotate each slicing plane
- L46 _public member_ `float SliceOffsetVariation;` — `UPROPERTY(EditAnywhere, Category = Slicing, meta = (DisplayName = "Random Offset Variation", UIMin = "0.0"))` — Maximum distance (in cm) to randomly shift each slicing plane

#### class `UFractureToolSlice`  
`class UFractureToolSlice : public UFractureToolCutterBase`  
_L50-95_
- reflection: `UCLASS(DisplayName="Slice Tool", Category="FractureTools")`
- inherits: `UFractureToolCutterBase`
- L55 _public prototype_ `UFractureToolSlice(const FObjectInitializer& ObjInit);`
- L58 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L59 _public prototype_ `virtual FText GetTooltipText() const override;`
- L60 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L62 _public prototype_ `virtual void RegisterUICommand( FFractureEditorCommands* BindingContext ) override;`
- L64 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L65 _public prototype_ `void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L67 _public prototype_ `virtual void FractureContextChanged() override;`
- L68 _public prototype_ `virtual int32 ExecuteFracture(const FFractureToolContext& Context) override;`
- L70 _public prototype_ `void GenerateSliceTransforms(const FFractureToolContext& Context, TArray<FTransform>& CuttingPlaneTransforms);`
- L72 _public function_ `virtual void ConfigureCutterSettings() override`
- L81 _public member_ `TObjectPtr<UFractureSliceSettings> SliceSettings;` — `UPROPERTY(EditAnywhere, Category = Slicing)` — Slicing
- L84 _protected function_ `virtual void ClearVisualizations() override`
- L92 _private member_ `float RenderCuttingPlaneSize;`
- L93 _private member_ `TArray<FTransform> RenderCuttingPlanesTransforms;`
- L94 _private member_ `FVisualizationMappings PlanesMappings;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolSplitIslands.h` (Private)


#### class `UFractureSplitIslandsSettings`  
`class UFractureSplitIslandsSettings : public UFractureToolSettings`  
_L14-32_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings for the Split Islands tool
- L20 _public function_ `UFractureSplitIslandsSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L26 _public member_ `float CloseVertexDistance = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "Split Islands", meta = (Units = "cm", ClampMin = "0.0"))` — Distance threshold for connecting spatially-close vertices before computing islands
- L30 _public member_ `float VertexToSurfaceBridgeDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Split Islands", meta = (Units = "cm", ClampMin = "0.0"))` — If > 0, bridge separate islands whose surfaces are within this vertex-to-triangle distance. 0 = disabled.

#### class `UFractureToolSplitIslands`  
`class UFractureToolSplitIslands : public UFractureModalTool`  
_L36-64_
- reflection: `UCLASS(DisplayName = "Split Islands", Category = "FractureTools")`
- inherits: `UFractureModalTool`
- L41 _public prototype_ `UFractureToolSplitIslands(const FObjectInitializer& ObjInit);`
- L47 _public prototype_ `virtual FText GetDisplayText() const override;`
- L48 _public prototype_ `virtual FText GetTooltipText() const override;`
- L49 _public function_ `virtual FText GetApplyText() const override`
- L50 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L51 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L52 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L53 _public prototype_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override;`
- L54 _public prototype_ `virtual bool CanExecute() const override;`
- L56 _public prototype_ `virtual TArray<FFractureToolContext> GetFractureToolContexts() const override;`
- L59 _public member_ `TObjectPtr<UFractureSplitIslandsSettings> SplitIslandsSettings;` — `UPROPERTY(EditAnywhere, Category = SplitIslands)`
- L62 _public member_ `TObjectPtr<UFractureCollisionSettings> CollisionSettings;` — `UPROPERTY(EditAnywhere, Category = Collision)`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolUV.h` (Private)


#### enum `EAutoUVTextureResolution`  
`enum class EAutoUVTextureResolution : int32`  
_L15-27_
- reflection: `UENUM()`
- L17 _public enumerator_ `Resolution16 = 16 UMETA(DisplayName = "16 x 16")`
- L18 _public enumerator_ `Resolution32 = 32 UMETA(DisplayName = "32 x 32")`
- L19 _public enumerator_ `Resolution64 = 64 UMETA(DisplayName = "64 x 64")`
- L20 _public enumerator_ `Resolution128 = 128 UMETA(DisplayName = "128 x 128")`
- L21 _public enumerator_ `Resolution256 = 256 UMETA(DisplayName = "256 x 256")`
- L22 _public enumerator_ `Resolution512 = 512 UMETA(DisplayName = "512 x 512")`
- L23 _public enumerator_ `Resolution1024 = 1024 UMETA(DisplayName = "1024 x 1024")`
- L24 _public enumerator_ `Resolution2048 = 2048 UMETA(DisplayName = "2048 x 2048")`
- L25 _public enumerator_ `Resolution4096 = 4096 UMETA(DisplayName = "4096 x 4096")`
- L26 _public enumerator_ `Resolution8192 = 8192 UMETA(DisplayName = "8192 x 8192")`

#### enum `ETextureType`  
`enum class ETextureType`  
_L30-38_
- reflection: `UENUM()`
- L33 _public enumerator_ `ThicknessAndSurfaceAttributes` — Bake thickness, ambient occlusion, and a smoothed curvature metric
- L35 _public enumerator_ `SpatialGradients` — Bake position relative to the bounding box
- L37 _public enumerator_ `Normals` — Bake surface normals

#### enum `ETargetFaces`  
`enum class ETargetFaces`  
_L41-53_
- reflection: `UENUM()`
- L44 _public enumerator_ `InternalFaces` — Target internal faces
- L46 _public enumerator_ `InternalFacesAndSelectedMaterialIDs` — Target internal faces and those with material IDs matching a custom list
- L48 _public enumerator_ `SelectedMaterialIDs` — Target faces with material IDs matching a custom list
- L50 _public enumerator_ `ExternalFaces` — Target external faces
- L52 _public enumerator_ `AllFaces` — Target all faces

#### class `UFractureAutoUVSettings`  
`class UFractureAutoUVSettings : public UFractureToolSettings`  
_L57-229_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- desc: Settings for UV layout and texture baking on the geometry collection
- L63 _public function_ `UFractureAutoUVSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L71 _public member_ `FString UVChannel;` — `UPROPERTY(EditAnywhere, Category = UVChannel, meta = (DisplayName = "UV Channel", GetOptions = GetUVChannelNamesFunc))` — Which UV channel to use for layout and baking
- L74 _public function_ `const TArray<FString>& GetUVChannelNamesFunc()` — `UFUNCTION()`
- L80 _public member_ `TArray<FString> UVChannelNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`
- L82 _public prototype_ `void SetNumUVChannels(int32 NumUVChannels);`
- L83 _public prototype_ `int32 GetSelectedChannelIndex(bool bForceToZeroOnFailure = true);`
- L87 _public function_ `void AddUVChannel()` — `UFUNCTION(CallInEditor, Category = UVChannel, meta = (DisplayName = "Add UV Channel"))` — Add a UV channel to the Geometry Collection
- L94 _public function_ `void DeleteUVChannel()` — `UFUNCTION(CallInEditor, Category = UVChannel, meta = (DisplayName = "Delete UV Channel"))` — Remove the last UV channel from the Geometry Collection
- L99 _public prototype_ `void ChangeNumUVChannels(int32 Delta);`
- L103 _public prototype_ `void LayoutUVs();` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayName = "Layout UVs", DisplayPriority = 1))` — Immediately layout and update the UVs of the selected Geometry Collection, for faces with the Target Material IDs
- L107 _public prototype_ `void BakeTexture();` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayName = "Bake Texture", DisplayPriority = 2))` — Bake a new texture with the chosen attributes, aligned to the current UV layout
- L111 _public prototype_ `void DisableBoneColors();` — `UFUNCTION(CallInEditor, Category = Operations)` — Disable "Show Bone Colors" on the selected Geometry Collection Components, so textures are visible. This setting can also be toggled directly on the Component itself
- L115 _public member_ `FVector ProjectionScale = FVector(100, 100, 100);` — `UPROPERTY(EditAnywhere, Category = Unwrap, meta = (EditCondition = "!bAutoFitToBounds"))` — The scale factor to use for UV box projection
- L119 _public member_ `bool bAutoFitToBounds = false;` — `UPROPERTY(EditAnywhere, Category = Unwrap, AdvancedDisplay)` — Set the scale factor for UV box projection based on the bounding box of the geometry
- L123 _public member_ `bool bUniformProjectionScale = false;` — `UPROPERTY(EditAnywhere, Category = Unwrap, AdvancedDisplay, meta = (DisplayName = "Uniform Scale"))` — Ensure the projection scale is the same on each axis, either by repeating the X Axis scale, or using the max box dimension if Auto Fit to Bounds is selected.
- L127 _public member_ `FVector2D ProjectionUVOffset = FVector2D(.5, .5);` — `UPROPERTY(EditAnywhere, Category = Unwrap, AdvancedDisplay, meta = (DisplayName = "UV Offset"))` — UV Offset to apply after UV box projection
- L131 _public member_ `bool bCenterAtPivot = false;` — `UPROPERTY(EditAnywhere, Category = Unwrap, AdvancedDisplay)` — Optionally center the UV projection around the object pivot
- L135 _public prototype_ `void BoxProjectUVs();` — `UFUNCTION(CallInEditor, Category = Unwrap, meta = (DisplayName = "Box Project UVs"))` — Immediately perform a box projection to update the internal UVs of the selected Geometry Collection
- L139 _public member_ `ETargetFaces TargetFaces;` — `UPROPERTY(EditAnywhere, Category = MapSettings)` — Choose whether to target internal faces, or a custom selection
- L143 _public member_ `TArray<int32> MaterialIDs;` — `UPROPERTY(EditAnywhere, Category = MapSettings, meta = (EditCondition = "TargetFaces != ETargetFaces::InternalFaces && TargetFaces != ETargetFaces::AllFaces && TargetFaces != ETargetFaces::ExternalFaces", EditConditionHides))` — Custom selection of material IDs to target for texturing
- L147 _public member_ `EAutoUVTextureResolution Resolution = EAutoUVTextureResolution::Resolution512;` — `UPROPERTY(EditAnywhere, Category = MapSettings)` — The pixel resolution of the generated map
- L151 _public member_ `int32 GutterSize = 2;` — `UPROPERTY(EditAnywhere, Category = MapSettings, meta = (ClampMin = "1", ClampMax = "10", UIMax = "6"))` — Approximate space to leave between UV islands, measured in texels
- L155 _public member_ `bool bClearGutterAlpha = false;` — `UPROPERTY(EditAnywhere, Category = MapSettings)` — Whether to set gutter texels to transparent, or to copy them unchanged from the closest interior texel value.
- L159 _public member_ `bool bFullyPadGutterOnBake = true;` — `UPROPERTY(EditAnywhere, Category = MapSettings)` — Whether to extend copied border texel values into all empty texture space, beyond the Gutter Size. Only applied when baking, does not affect spacing for UV Layout.
- L163 _public member_ `int32 GutterPaddingOnBake = 4;` — `UPROPERTY(EditAnywhere, Category = MapSettings, meta = (ClampMin = "0", UIMax = "10", EditCondition="!bFullyPadGutterOnBake"))` — Amount of texels to extend copied border texel values into empty texture space, beyond the Gutter Size. Only applied when baking, does not affect spacing for UV Layout.
- L167 _public member_ `TObjectPtr<UTexture2D> Result;` — `UPROPERTY(VisibleAnywhere, Category = MapSettings)` — The resulting automatically-generated texture map
- L171 _public member_ `bool bPromptToSave = true;` — `UPROPERTY(EditAnywhere, Category = MapSettings)` — Whether to prompt user for an asset name for each generated texture, or automatically place them next to the source Geometry Collections
- L175 _public member_ `bool bReplaceExisting = true;` — `UPROPERTY(EditAnywhere, Category = MapSettings)` — Whether to allow the new texture to overwrite an existing texture
- L179 _public member_ `ETextureType BakeTextureType = ETextureType::ThicknessAndSurfaceAttributes;` — `UPROPERTY(EditAnywhere, Category = AttributesToBake)` — Which standard set of texture channels to bake
- L183 _public member_ `bool bDistToOuter = true;` — `UPROPERTY(EditAnywhere, Category = AttributesToBake, meta = (EditCondition = "BakeTextureType == ETextureType::ThicknessAndSurfaceAttributes", EditConditionHides))` — Bake the distance to the external surface to a texture channel (red)
- L187 _public member_ `bool bAmbientOcclusion = true;` — `UPROPERTY(EditAnywhere, Category = AttributesToBake, meta = (EditCondition = "BakeTextureType == ETextureType::ThicknessAndSurfaceAttributes", EditConditionHides))` — Bake the ambient occlusion of each bone (considered separately) to a texture channel (green)
- L195 _public member_ `bool bSmoothedCurvature = false;` — `UPROPERTY(EditAnywhere, Category = AttributesToBake, meta = (EditCondition = "BakeTextureType == ETextureType::ThicknessAndSurfaceAttributes", EditConditionHides))` — Bake a smoothed curvature metric to a texture channel (blue) Specifically, this is the mean curvature of a smoothed copy of each fractured piece, baked back to the respective fracture piece Note that this attribute is relatively expensive to compute
- L199 _public member_ `double MaxDistance = 100;` — `UPROPERTY(EditAnywhere, Category = DistToOuterSettings, meta = (EditCondition = "BakeTextureType == ETextureType::ThicknessAndSurfaceAttributes && bDistToOuter", EditConditionHides, UIMin = "1", UIMax = "100", ClampMin = ".01", ClampMax = "1000"))` — Max distance to search for the outer mesh surface
- L203 _public member_ `int OcclusionRays = 16;` — `UPROPERTY(EditAnywhere, Category = AmbientOcclusionSettings, meta = (EditCondition = "BakeTextureType == ETextureType::ThicknessAndSurfaceAttributes && bAmbientOcclusion", EditConditionHides, UIMin = "1", UIMax = "1024", ClampMin = "0", ClampMax = "50000"))` — Number of occlusion rays
- L207 _public member_ `double OcclusionBlurRadius = 2.25;` — `UPROPERTY(EditAnywhere, Category = AmbientOcclusionSettings, meta = (EditCondition = "BakeTextureType == ETextureType::ThicknessAndSurfaceAttributes && bAmbientOcclusion", EditConditionHides, UIMin = "0", UIMax = "10.0", ClampMin = "0", ClampMax = "100.0"))` — Pixel Radius of Gaussian Blur Kernel applied to AO map (0 will apply no blur)
- L211 _public member_ `double CurvatureBlurRadius = 2.25;` — `UPROPERTY(EditAnywhere, Category = SmoothedCurvatureSettings, meta = (EditCondition = "BakeTextureType == ETextureType::ThicknessAndSurfaceAttributes && bSmoothedCurvature", EditConditionHides, UIMin = "0", UIMax = "10.0", ClampMin = "0", ClampMax = "100.0"))` — Pixel Radius of Gaussian Blur Kernel applied to Curvature map (0 will apply no blur)
- L215 _public member_ `int VoxelResolution = 128;` — `UPROPERTY(EditAnywhere, Category = SmoothedCurvatureSettings, meta = (EditCondition = "BakeTextureType == ETextureType::ThicknessAndSurfaceAttributes && bSmoothedCurvature", EditConditionHides, UIMin = "8", UIMax = "512", ClampMin = "4", ClampMax = "1024"))` — Voxel resolution of smoothed shape representation
- L219 _public member_ `int SmoothingIterations = 10;` — `UPROPERTY(EditAnywhere, Category = SmoothedCurvatureSettings, meta = (EditCondition = "BakeTextureType == ETextureType::ThicknessAndSurfaceAttributes && bSmoothedCurvature", EditConditionHides, UIMin = "2", UIMax = "100", ClampMin = "2", ClampMax = "1000"))` — Amount of smoothing iterations to apply before computing curvature
- L223 _public member_ `double ThicknessFactor = 4;` — `UPROPERTY(EditAnywhere, Category = SmoothedCurvatureSettings, meta = (EditCondition = "BakeTextureType == ETextureType::ThicknessAndSurfaceAttributes && bSmoothedCurvature", EditConditionHides, UIMin = "2", UIMax = "10.0", ClampMin = "1", ClampMax = "100.0"))` — Distance to search for correspondence between fractured shape and smoothed shape, as factor of voxel size
- L227 _public member_ `double MaxCurvature = .1;` — `UPROPERTY(EditAnywhere, Category = SmoothedCurvatureSettings, meta = (EditCondition = "BakeTextureType == ETextureType::ThicknessAndSurfaceAttributes && bSmoothedCurvature", EditConditionHides, UIMin = ".01", UIMax = "1", ClampMin = ".0001", ClampMax = "10"))` — Curvatures in the range [-MaxCurvature, MaxCurvature] will be mapped from [0,1]. Values outside that range will be clamped

#### class `UFractureToolAutoUV`  
`class UFractureToolAutoUV : public UFractureModalTool`  
_L233-288_
- reflection: `UCLASS(DisplayName = "AutoUV Tool", Category = "FractureTools")`
- inherits: `UFractureModalTool`
- L238 _public prototype_ `UFractureToolAutoUV(const FObjectInitializer& ObjInit);`
- L245 _public prototype_ `virtual FText GetDisplayText() const override;` — This is the Text that will appear on the tool button to execute the tool
- L246 _public prototype_ `virtual FText GetTooltipText() const override;`
- L248 _public function_ `virtual FText GetApplyText() const override` — This is the Text that will appear on the button to execute the fracture
- L249 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L250 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L251 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L252 _public prototype_ `virtual void FractureContextChanged() override;`
- L253 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L255 _public prototype_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext) override;` — Executes function that generates new geometry. Returns the first new geometry index.
- L256 _public prototype_ `virtual bool CanExecute() const override;`
- L257 _public function_ `virtual bool ExecuteUpdatesShape() const override`
- L261 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L264 _public prototype_ `const TSharedPtr<FUICommandInfo>& GetUICommandInfo() const;` — Gets the UI command info for this command
- L266 _public prototype_ `virtual TArray<FFractureToolContext> GetFractureToolContexts() const override;`
- L269 _public prototype_ `void UpdateUVChannels(int32 TargetNumUVChannels);` — Update number of UV channels for selected geometry collections
- L272 _public prototype_ `void BoxProjectUVs();` — Create new UV islands via box projection for the selected geometry collections
- L274 _public prototype_ `void DisableBoneColors();`
- L276 _public prototype_ `void LayoutUVs();`
- L277 _public prototype_ `void BakeTexture();`
- L282 _protected member_ `TObjectPtr<UFractureAutoUVSettings> AutoUVSettings;` — `UPROPERTY(EditAnywhere, Category = Slicing)`
- L284 _protected prototype_ `bool SaveGeneratedTexture(UE::Geometry::TImageBuilder<FVector4f>& ImageBuilder, FString ObjectBaseName, const UObject* RelativeToAsset, bool bPromptToSave, bool bAllowReplace);`
- L286 _protected prototype_ `bool LayoutUVsForComponent(UGeometryCollectionComponent* Component);`
- L287 _protected prototype_ `void BakeTextureForComponent(UGeometryCollectionComponent* Component);`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolUniform.h` (Private)


#### class `UFractureUniformSettings`  
`class UFractureUniformSettings : public UFractureToolSettings`  
_L12-31_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UFractureToolSettings`
- L17 _public function_ `UFractureUniformSettings(const FObjectInitializer& ObjInit) : Super(ObjInit) , NumberVoronoiSitesMin(20) , NumberVoronoiSitesMax(20)`
- L25 _public member_ `int32 NumberVoronoiSitesMin;` — `UPROPERTY(EditAnywhere, Category = UniformVoronoi, meta = (DisplayName = "Min Voronoi Sites", UIMin = "1", UIMax = "5000", ClampMin = "1"))` — Minimum Number of Voronoi sites. The amount of sites per Voronoi diagram will be chosen at random between Min and Max
- L29 _public member_ `int32 NumberVoronoiSitesMax;` — `UPROPERTY(EditAnywhere, Category = UniformVoronoi, meta = (DisplayName = "Max Voronoi Sites", UIMin = "1", UIMax = "5000", ClampMin = "1"))` — Maximum Number of Voronoi sites. The amount of sites per Voronoi diagram will be chosen at random between Min and Max

#### class `UFractureToolUniform`  
`class UFractureToolUniform : public UFractureToolVoronoiCutterBase`  
_L35-56_
- reflection: `UCLASS(DisplayName="Uniform Voronoi", Category="FractureTools")`
- inherits: `UFractureToolVoronoiCutterBase`
- L40 _public prototype_ `UFractureToolUniform(const FObjectInitializer& ObjInit);`
- L43 _public prototype_ `virtual FText GetDisplayText() const override;` — UFractureTool Interface
- L44 _public prototype_ `virtual FText GetTooltipText() const override;`
- L45 _public prototype_ `virtual FSlateIcon GetToolIcon() const override;`
- L46 _public prototype_ `virtual TArray<UObject*> GetSettingsObjects() const override;`
- L47 _public prototype_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext) override;`
- L52 _public member_ `TObjectPtr<UFractureUniformSettings> UniformSettings;` — `UPROPERTY(EditAnywhere, Category = Uniform)` — Uniform Voronoi Fracture Input Settings
- L55 _protected prototype_ `void GenerateVoronoiSites(const FFractureToolContext& Context, TArray<FVector>& Sites) override;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/GeometryCollectionOutlinerDragDrop.h` (Private)


#### class `FGeometryCollectionBoneDragDrop`  
`class FGeometryCollectionBoneDragDrop : public FDecoratedDragDropOp`  
_L13-47_
- inherits: `FDecoratedDragDropOp`
- desc: This operation is a bone which can be dragged and dropped to another bone in the outliner.
- L18 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FGeometryCollectionBoneDragDrop, FDecoratedDragDropOp) TArray<int32> BonePayload;`
- L22 _public member_ `TSharedPtr<FGeometryCollection,ESPMode::ThreadSafe> GeometryCollection;`
- L24 _public function_ `static TSharedRef<FGeometryCollectionBoneDragDrop> New(TSharedPtr<FGeometryCollection,ESPMode::ThreadSafe> InGeometryCollection, TArray<int32>& InBonePayload)`
- L36 _public prototype_ `bool ValidateDrop(const FGeometryCollection* OtherGeometryCollection, int32 OtherBone, FText& MessageText);` — Return true if dropping the BonePayload onto OtherBone is a valid operation. If it's not, return false and provide reason in MessageText.
- L39 _public prototype_ `bool ReparentBones(const FGeometryCollection* OtherGeometryCollection, int32 OtherBone);` — Reparent BonePayload to OtherBone if this is a valid operation. Return false otherwise.
- L42 _private prototype_ `bool ContainsCluster() const;`
- L43 _private prototype_ `bool ContainsRigid() const;`
- L44 _private prototype_ `bool ContainsEmbedded() const;`
- L45 _private prototype_ `bool ContainsInstance() const;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/SGeometryCollectionHistogram.h` (Private)


#### enum `EInspectedAttributeEnum`  
`enum class EInspectedAttributeEnum : uint8`  
_L27-33_
- reflection: `UENUM(BlueprintType)`
- L29 _public enumerator_ `Volume = 0 UMETA(DisplayName = "Volume")`
- L30 _public enumerator_ `Level = 1 UMETA(DisplayName = "Level")`
- L31 _public enumerator_ `InitialDynamicState = 3 UMETA(DisplayName = "InitialDynamicState")`
- L32 _public enumerator_ `Size = 4 UMETA(DisplayName = "RelativeSize")`

#### class `UHistogramSettings`  
`class UHistogramSettings : public UObject`  
_L37-64_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Settings for Histogram configuration.
- L42 _public prototype_ `UHistogramSettings(const FObjectInitializer& ObjInit);`
- L46 _public member_ `EInspectedAttributeEnum InspectedAttribute;` — `UPROPERTY(EditAnywhere, Category = HistogramSettings, meta = (DisplayName = "Inspected Attribute"))` — What attribute are we inspecting?
- L50 _public member_ `bool bSorted;` — `UPROPERTY(EditAnywhere, Category = HistogramSettings, meta = (DisplayName = "Sort Values"))` — Sort the values?
- L54 _public member_ `bool bShowClusters=true;` — `UPROPERTY(EditAnywhere, Category = HistogramSettings, meta = (DisplayName = "Show Clusters"))` — Show clusters?
- L58 _public member_ `bool bShowRigids=true;` — `UPROPERTY(EditAnywhere, Category = HistogramSettings, meta = (DisplayName = "Show Rigids"))` — Show rigids?
- L62 _public member_ `bool bShowEmbedded=true;` — `UPROPERTY(EditAnywhere, Category = HistogramSettings, meta = (DisplayName = "Show Embedded Geometry"))` — Show embedded geometry?

#### class `FGeometryCollectionHistogramItemComponent`  
`class FGeometryCollectionHistogramItemComponent : public TSharedFromThis<FGeometryCollectionHistogramItemComponent>`  
_L66-83_
- inherits: `TSharedFromThis<FGeometryCollectionHistogramItemComponent>`
- L69 _public function_ `FGeometryCollectionHistogramItemComponent(UGeometryCollectionComponent* InComponent) : Component(InComponent)`
- L74 _public function_ `UGeometryCollectionComponent* GetComponent() const`
- L76 _public prototype_ `FGeometryCollectionHistogramItemPtr GetItemFromBoneIndex(int32 BoneIndex) const;`
- L78 _public prototype_ `FGeometryCollectionHistogramItemList RegenerateNodes(int32 LevelView);`
- L81 _private member_ `TWeakObjectPtr<UGeometryCollectionComponent> Component;`
- L82 _private member_ `TMap<int32, FGeometryCollectionHistogramItemPtr> ItemByBoneIndex;`

#### class `FGeometryCollectionHistogramItem`  
`class FGeometryCollectionHistogramItem : public TSharedFromThis<FGeometryCollectionHistogramItem>`  
_L87-121_
- inherits: `TSharedFromThis<FGeometryCollectionHistogramItem>`
- L90 _public function_ `FGeometryCollectionHistogramItem(const int32 InBoneIndex, const TSharedPtr<FGeometryCollectionHistogramItemComponent> InParentComponentItem) : BoneIndex(InBoneIndex) , ParentComponentItem(InParentComponentItem) , ListIndex(0) , NodeColor(FLinearColor::Black) , NormalizedValue(0.0) , InspectedValue(0.0)`
- L99 _public prototype_ `TSharedRef<ITableRow> MakeHistogramRowWidget(const TSharedRef<STableViewBase>& InOwnerTable);`
- L101 _public function_ `UGeometryCollectionComponent* GetComponent() const`
- L103 _public function_ `float GetInspectedValue() const`
- L104 _public function_ `void SetColor(const FLinearColor& InColor)`
- L105 _public prototype_ `void SetInspectedAttribute(EInspectedAttributeEnum InspectedAttribute);`
- L106 _public prototype_ `void SetNormalizedValue(float MinValue, float MaxValue);`
- L108 _public function_ `int32 GetBoneIndex() const`
- L109 _public function_ `void SetListIndex(int32 InListIndex)`
- L110 _public function_ `int32 GetListIndex() const`
- L113 _private member_ `const int32 BoneIndex;`
- L114 _private member_ `const TSharedPtr<FGeometryCollectionHistogramItemComponent> ParentComponentItem;`
- L116 _private member_ `int32 ListIndex;`
- L117 _private member_ `FLinearColor NodeColor;`
- L118 _private member_ `float NormalizedValue;`
- L119 _private member_ `float InspectedValue;`
- L120 _private member_ `FString HoverString;`

#### class `SGeometryCollectionHistogram`  
`class SGeometryCollectionHistogram : public SCompoundWidget`  
_L125-161_
- inherits: `SCompoundWidget`
- L127 _private prototype_ `DECLARE_DELEGATE_TwoParams(FOnBoneSelectionChanged, UGeometryCollectionComponent*, TArray<int32>&);`
- L129 _private function_ `SLATE_BEGIN_ARGS(SGeometryCollectionHistogram)`
- L137 _public prototype_ `void Construct(const FArguments& InArgs);`
- L139 _public prototype_ `TSharedRef<ITableRow> MakeHistogramRowWidget(FGeometryCollectionHistogramItemPtr InInfo, const TSharedRef<STableViewBase>& OwnerTable);`
- L140 _public prototype_ `void SetComponents(const TArray<UGeometryCollectionComponent*>& InNewComponents, int32 LevelView);`
- L141 _public prototype_ `void SetBoneSelection(UGeometryCollectionComponent* RootComponent, const TArray<int32>& InSelection, bool bClearCurrentSelection, int32 FocusBoneIdx = -1);`
- L142 _public prototype_ `void InspectAttribute(EInspectedAttributeEnum InspectedAttribute);`
- L143 _public prototype_ `void RefreshView(bool bSorted);`
- L144 _public prototype_ `void RegenerateNodes(int32 LevelView);`
- L145 _public function_ `void ClearSelection()`
- L146 _public function_ `bool IsSelected()`
- L149 _private prototype_ `void OnSelectionChanged(FGeometryCollectionHistogramItemPtr Item, ESelectInfo::Type SelectInfo);`
- L151 _private prototype_ `void NormalizeInspectedValues();`
- L152 _private prototype_ `void SetListIndices();`
- L155 _private member_ `TSharedPtr<SListView<FGeometryCollectionHistogramItemPtr>> ListView;`
- L156 _private member_ `TArray<TSharedPtr<FGeometryCollectionHistogramItemComponent>> RootNodes;`
- L157 _private member_ `TArray<FGeometryCollectionHistogramItemPtr> LeafNodes;`
- L159 _private member_ `FOnBoneSelectionChanged BoneSelectionChangedDelegate;`
- L160 _private member_ `bool bPerformingSelection;`

#### Free symbols / members of external scopes

- L22 _typedef_ `using FGeometryCollectionHistogramItemPtr = TSharedPtr<FGeometryCollectionHistogramItem>;`
- L23 _typedef_ `using FGeometryCollectionHistogramItemList = TArray<TSharedPtr<FGeometryCollectionHistogramItem>>;`
- L127 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnBoneSelectionChanged, UGeometryCollectionComponent*, TArray<int32>&);`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/SGeometryCollectionOutliner.h` (Private)


#### enum `EOutlinerItemNameEnum`  
`enum class EOutlinerItemNameEnum : uint8`  
_L36-40_
- reflection: `UENUM(BlueprintType)`
- L38 _public enumerator_ `BoneName = 0 UMETA(DisplayName = "Bone Name")`
- L39 _public enumerator_ `BoneIndex = 1 UMETA(DisplayName = "Bone Index")`

#### class `UOutlinerSettings`  
`class UOutlinerSettings : public UObject`  
_L44-58_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Settings for Outliner configuration.
- L49 _public prototype_ `UOutlinerSettings(const FObjectInitializer& ObjInit);`
- L53 _public member_ `bool ColorByLevel;` — `UPROPERTY(EditAnywhere, Category = OutlinerSettings, meta = (DisplayName = "Color By Level"))` — whether to use level coloring
- L57 _public member_ `EOutlinerColumnMode ColumnMode;` — `UPROPERTY(EditAnywhere, Category = OutlinerSettings, meta = (DisplayName = "Column Mode"))` — the column to be display in the outliner

#### class `FGeometryCollectionTreeItem`  
`class FGeometryCollectionTreeItem : public TSharedFromThis<FGeometryCollectionTreeItem>`  
_L61-81_
- inherits: `TSharedFromThis<FGeometryCollectionTreeItem>`
- L64 _public prototype_ `virtual ~FGeometryCollectionTreeItem() = default;`
- L65 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, bool bIsPinned = false) = 0;`
- L66 _public prototype_ `virtual void GetChildren(FGeometryCollectionTreeItemList& OutChildren) = 0;`
- L67 _public prototype_ `virtual UGeometryCollectionComponent* GetComponent() const = 0;`
- L69 _public function_ `virtual int32 GetBoneIndex() const`
- L71 _public function_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L72 _public function_ `virtual FReply OnDrop(const FDragDropEvent& DragDropEvent)`
- L74 _public function_ `virtual void OnDragEnter(FDragDropEvent const& InDragDropEvent)`
- L75 _public prototype_ `virtual void OnDragLeave(FDragDropEvent const& InDragDropEvent);`
- L78 _public prototype_ `void GenerateContextMenu(UToolMenu* Menu, SGeometryCollectionOutliner& Outliner);` — void MakeDynamicStateMenu(UToolMenu* Menu, SGeometryCollectionOutliner& Outliner);
- L80 _public prototype_ `static FColor GetColorPerDepth(uint32 Depth);`

#### class `FGeometryCollectionItemDataFacade`  
`class FGeometryCollectionItemDataFacade`  
_L85-138_
- L88 _public prototype_ `FGeometryCollectionItemDataFacade(FManagedArrayCollection& InCollection);`
- L90 _public prototype_ `void FillFromGeometryCollectionComponent(const UGeometryCollectionComponent& GeometryCollectionComponent, EOutlinerColumnMode ColumnMode);`
- L92 _public function_ `bool IsLevelAttributeValid() const`
- L93 _public function_ `bool IsSimulationtypeAttributeValid() const`
- L94 _public function_ `bool IsVisibleAttributeValid() const`
- L95 _public function_ `bool IsRemoveOnBreakAttributeValid() const`
- L97 _public function_ `const TManagedArray<int32>& GetLevel() const`
- L98 _public function_ `const TManagedArray<int32>& GetSimulationType() const`
- L99 _public function_ `const TManagedArray<bool>& GetVisible() const`
- L101 _public prototype_ `bool IsValidBoneIndex(int32 BoneIndex) const;`
- L102 _public prototype_ `FString GetBoneName(int32 Index) const;`
- L103 _public prototype_ `int32 GetBoneCount() const;`
- L104 _public prototype_ `float GetRelativeSize(int32 Index) const;`
- L105 _public prototype_ `float GetVolumetricUnit(int32 Index) const;`
- L106 _public prototype_ `int32 GetInitialState(int32 Index) const;`
- L107 _public prototype_ `bool IsAnchored(int32 Index) const;`
- L108 _public prototype_ `float GetDamage(int32 Index) const;`
- L109 _public prototype_ `float GetDamageThreshold(int32 Index) const;`
- L110 _public prototype_ `bool IsBroken(int32 Index) const;`
- L111 _public prototype_ `FRemoveOnBreakData GetRemoveOnBreakData(int32 Index) const;`
- L112 _public prototype_ `bool HasSourceCollision(int32 Index) const;`
- L113 _public prototype_ `bool IsSourceCollisionUsed(int32 Index) const;`
- L114 _public prototype_ `int32 GetConvexCount(int32 Index) const;`
- L115 _public prototype_ `int32 GetTriangleCount(int32 Index) const;`
- L116 _public prototype_ `int32 GetVertexCount(int32 Index) const;`
- L119 _private member_ `FManagedArrayCollection& DataCollection;`
- L120 _private member_ `TManagedArrayAccessor<FString> BoneNameAttribute;`
- L121 _private member_ `TManagedArrayAccessor<int32> LevelAttribute;`
- L123 _private member_ `TManagedArrayAccessor<bool> VisibleAttribute;` — TManagedArrayAccessor<TArray<int32>>ChildrenAttribute;
- L124 _private member_ `TManagedArrayAccessor<int32> InitialStateAttribute;`
- L125 _private member_ `TManagedArrayAccessor<float> RelativeSizeAttribute;`
- L126 _private member_ `TManagedArrayAccessor<float> VolumetricUnitAttribute;`
- L127 _private member_ `TManagedArrayAccessor<bool> AnchoredAttribute;`
- L128 _private member_ `TManagedArrayAccessor<float> DamageAttribute;`
- L129 _private member_ `TManagedArrayAccessor<float> DamageThresholdAttribute;`
- L130 _private member_ `TManagedArrayAccessor<bool> BrokenStateAttribute;`
- L131 _private member_ `TManagedArrayAccessor<FVector4f> RemoveOnBreakAttribute;`
- L132 _private member_ `TManagedArrayAccessor<int32> SimulationTypeAttribute;`
- L133 _private member_ `TManagedArrayAccessor<bool> HasSourceCollisionAttribute;`
- L134 _private member_ `TManagedArrayAccessor<bool> SourceCollisionUsedAttribute;`
- L135 _private member_ `TManagedArrayAccessor<int32> ConvexCountAttribute;`
- L136 _private member_ `TManagedArrayAccessor<int32> TriangleCountAttribute;`
- L137 _private member_ `TManagedArrayAccessor<int32> VertexCountAttribute;`

#### class `FGeometryCollectionTreeItemComponent`  
`class FGeometryCollectionTreeItemComponent : public FGeometryCollectionTreeItem`  
_L140-204_
- inherits: `FGeometryCollectionTreeItem`
- L143 _public function_ `FGeometryCollectionTreeItemComponent(UGeometryCollectionComponent* InComponent, TSharedPtr<STreeView<FGeometryCollectionTreeItemPtr>> InTreeView) : Component(InComponent) , TreeView(InTreeView) , DataCollectionFacade(DataCollection)`
- L151 _public prototype_ `virtual ~FGeometryCollectionTreeItemComponent() = default;`
- L154 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, bool bIsPinned = false);` — FGeometryCollectionTreeItem interface
- L155 _public prototype_ `virtual void GetChildren(FGeometryCollectionTreeItemList& OutChildren) override;`
- L156 _public function_ `virtual UGeometryCollectionComponent* GetComponent() const override`
- L159 _public prototype_ `FGeometryCollectionTreeItemPtr GetItemFromBoneIndex(int32 BoneIndex) const;`
- L161 _public prototype_ `void GetChildrenForBone(FGeometryCollectionTreeItemBone& BoneItem, FGeometryCollectionTreeItemList& OutChildren) const;`
- L162 _public prototype_ `bool HasChildrenForBone(const FGeometryCollectionTreeItemBone& BoneItem) const;`
- L164 _public prototype_ `void ExpandAll();`
- L165 _public prototype_ `void GenerateDataCollection();`
- L166 _public prototype_ `void RegenerateChildren();`
- L167 _public prototype_ `void RequestTreeRefresh();`
- L169 _public prototype_ `void SetHistogramSelection(TArray<int32>& SelectedBones);`
- L171 _public function_ `const FGeometryCollectionItemDataFacade& GetDataCollectionFacade() const`
- L172 _public function_ `FGeometryCollectionItemDataFacade& GetDataCollectionFacade()`
- L174 _public prototype_ `bool IsValid() const;`
- L177 _public function_ `void Invalidate()` — Mark item as unused/invalid; helpful because slate defers destroying tree items and can still run callbacks on them until tick
- L183 _private prototype_ `bool FilterBoneIndex(int32 BoneIndex) const;`
- L186 _private member_ `TWeakObjectPtr<UGeometryCollectionComponent> Component;`
- L188 _private member_ `TSharedPtr<STreeView<FGeometryCollectionTreeItemPtr>> TreeView;`
- L191 _private member_ `TArray<FGeometryCollectionTreeItemPtr> ChildItems;` — The direct children under this component
- L192 _private member_ `TMap<int32, FGeometryCollectionTreeItemPtr> ItemsByBoneIndex;`
- L193 _private member_ `int32 RootIndex;`
- L195 _private member_ `TArray<int32> HistogramSelection;`
- L198 _private member_ `FManagedArrayCollection DataCollection;` — collection used to store the displayed information
- L199 _private member_ `FGeometryCollectionItemDataFacade DataCollectionFacade;`
- L202 _private member_ `bool bInvalidated = false;` — track whether the item has been explicitly invalidated

#### class `FGeometryCollectionTreeItemBone`  
`class FGeometryCollectionTreeItemBone : public FGeometryCollectionTreeItem`  
_L206-254_
- inherits: `FGeometryCollectionTreeItem`
- L210 _public function_ `FGeometryCollectionTreeItemBone(const int32 InBoneIndex, FGeometryCollectionTreeItemComponent* InParentComponentItem) : BoneIndex(InBoneIndex) , ParentComponentItem(InParentComponentItem) , ItemColor(FSlateColor::UseForeground())`
- L217 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, bool bIsPinned = false);` — FGeometryCollectionTreeItem interface
- L218 _public prototype_ `TSharedRef<SWidget> MakeBoneIndexColumnWidget() const;`
- L219 _public prototype_ `TSharedRef<SWidget> MakeBoneNameColumnWidget() const;`
- L220 _public prototype_ `TSharedRef<SWidget> MakeRelativeSizeColumnWidget() const;`
- L221 _public prototype_ `TSharedRef<SWidget> MakeVolumeColumnWidget() const;`
- L222 _public prototype_ `TSharedRef<SWidget> MakeDamagesColumnWidget() const;`
- L223 _public prototype_ `TSharedRef<SWidget> MakeDamageThresholdColumnWidget() const;`
- L224 _public prototype_ `TSharedRef<SWidget> MakeBrokenColumnWidget() const;`
- L225 _public prototype_ `TSharedRef<SWidget> MakeInitialStateColumnWidget() const;`
- L226 _public prototype_ `TSharedRef<SWidget> MakeAnchoredColumnWidget() const;`
- L227 _public prototype_ `TSharedRef<SWidget> MakePostBreakTimeColumnWidget() const;`
- L228 _public prototype_ `TSharedRef<SWidget> MakeRemovalTimeColumnWidget() const;`
- L229 _public prototype_ `TSharedRef<SWidget> MakeImportedCollisionsColumnWidget() const;`
- L230 _public prototype_ `TSharedRef<SWidget> MakeConvexCountColumnWidget() const;`
- L231 _public prototype_ `TSharedRef<SWidget> MakeTriangleCountColumnWidget() const;`
- L232 _public prototype_ `TSharedRef<SWidget> MakeVertexCountColumnWidget() const;`
- L233 _public prototype_ `TSharedRef<SWidget> MakeEmptyColumnWidget() const;`
- L234 _public prototype_ `virtual void GetChildren(FGeometryCollectionTreeItemList& OutChildren) override;`
- L235 _public prototype_ `bool IsValidBone() const;`
- L236 _public function_ `virtual int32 GetBoneIndex() const override`
- L237 _public function_ `virtual UGeometryCollectionComponent* GetComponent() const`
- L238 _public prototype_ `bool HasChildren() const;`
- L241 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L242 _protected prototype_ `virtual FReply OnDrop(const FDragDropEvent& DragDropEvent) override;`
- L243 _protected prototype_ `virtual void OnDragEnter(FDragDropEvent const& InDragDropEvent) override;`
- L246 _private prototype_ `void UpdateItemFromCollection();`
- L248 _private prototype_ `const FGeometryCollectionItemDataFacade& GetDataCollectionFacade() const;`
- L251 _private member_ `const int32 BoneIndex;`
- L252 _private member_ `FGeometryCollectionTreeItemComponent* ParentComponentItem;`
- L253 _private member_ `FSlateColor ItemColor;`

#### class `SGeometryCollectionOutlinerRow`  
`class SGeometryCollectionOutlinerRow : public SMultiColumnTableRow<FGeometryCollectionTreeItemBonePtr>`  
_L282-304_
- inherits: `SMultiColumnTableRow<FGeometryCollectionTreeItemBonePtr>`
- L285 _protected member_ `FGeometryCollectionTreeItemBonePtr Item;`
- L288 _public function_ `SLATE_BEGIN_ARGS(SGeometryCollectionOutlinerRow)`
- L289 _public prototype_ `SLATE_END_ARGS() virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L293 _public function_ `void Construct(const FArguments& InArgs, TSharedRef<STableViewBase> OwnerTableView, FGeometryCollectionTreeItemBonePtr InItemToEdit)`

#### class `SGeometryCollectionOutliner`  
`class SGeometryCollectionOutliner: public SCompoundWidget`  
_L306-353_
- inherits: `SCompoundWidget`
- L308 _private prototype_ `DECLARE_DELEGATE_TwoParams(FOnBoneSelectionChanged, UGeometryCollectionComponent*, TArray<int32>&);`
- L310 _private function_ `SLATE_BEGIN_ARGS( SGeometryCollectionOutliner )`
- L318 _public prototype_ `void Construct(const FArguments& InArgs);`
- L320 _public prototype_ `void RegenerateItems();`
- L321 _public prototype_ `void RegenerateHeader();`
- L322 _public prototype_ `void RegenerateRootData();`
- L324 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(FGeometryCollectionTreeItemPtr InInfo, const TSharedRef<STableViewBase>& OwnerTable);`
- L325 _public prototype_ `TSharedRef<ITableRow> OnGeneratePinnedRowWidget(FGeometryCollectionTreeItemPtr InItem, const TSharedRef<STableViewBase>& InOwnerTable, bool bPinned);`
- L326 _public prototype_ `void OnGetChildren(TSharedPtr<FGeometryCollectionTreeItem> InInfo, TArray< TSharedPtr<FGeometryCollectionTreeItem> >& OutChildren);`
- L327 _public prototype_ `TSharedPtr<SWidget> OnOpenContextMenu();`
- L329 _public prototype_ `void UpdateGeometryCollection();`
- L330 _public prototype_ `void SetComponents(const TArray<UGeometryCollectionComponent*>& InNewComponents);`
- L331 _public prototype_ `void SetBoneSelection(UGeometryCollectionComponent* RootComponent, const TArray<int32>& InSelection, bool bClearCurrentSelection, int32 FocusBoneIdx = -1);`
- L332 _public prototype_ `int32 GetBoneSelectionCount() const;`
- L333 _public prototype_ `int32 GetBoneDisplayedCount() const;`
- L335 _public prototype_ `void SetInitialDynamicState(int32 InDynamicState);`
- L336 _public prototype_ `void SetAnchored(bool bAnchored);`
- L338 _public prototype_ `void ExpandAll();`
- L339 _public prototype_ `void ExpandRecursive(TSharedPtr<FGeometryCollectionTreeItem> TreeItem, bool bInExpansionState) const;`
- L342 _public prototype_ `void SetHistogramSelection(UGeometryCollectionComponent* RootComponent, TArray<int32>& SelectedBones);` — Set the histogram filter on the component matching RootComponent.
- L345 _private prototype_ `void OnSelectionChanged(FGeometryCollectionTreeItemPtr Item, ESelectInfo::Type SelectInfo);`
- L348 _private member_ `TSharedPtr<STreeView<FGeometryCollectionTreeItemPtr>> TreeView;`
- L349 _private member_ `TSharedPtr< SHeaderRow > HeaderRowWidget;`
- L350 _private member_ `TArray<TSharedPtr<FGeometryCollectionTreeItemComponent>> RootNodes;`
- L351 _private member_ `FOnBoneSelectionChanged BoneSelectionChangedDelegate;`
- L352 _private member_ `bool bPerformingSelection;`

#### Free symbols / members of external scopes

- L31 _typedef_ `typedef TArray<TSharedPtr<FGeometryCollectionTreeItem>> FGeometryCollectionTreeItemList;`
- L32 _typedef_ `typedef TSharedPtr<FGeometryCollectionTreeItem> FGeometryCollectionTreeItemPtr;`
- L83 _typedef_ `using FRemoveOnBreakData = GeometryCollection::Facades::FRemoveOnBreakData;`
- L256 _typedef_ `typedef TSharedPtr<class FGeometryCollectionTreeItemBone> FGeometryCollectionTreeItemBonePtr;`
- L258 _namespace_ `namespace SGeometryCollectionOutlinerColumnID`
- L260 _variable_ `const FName BoneIndex("Ind` (scope `SGeometryCollectionOutlinerColumnID`)
- L261 _variable_ `const FName BoneName("Nam` (scope `SGeometryCollectionOutlinerColumnID`)
- L263 _variable_ `const FName RelativeSize("Rel` (scope `SGeometryCollectionOutlinerColumnID`) — State and Size column mode
- L264 _variable_ `const FName Volume("Vol` (scope `SGeometryCollectionOutlinerColumnID`)
- L265 _variable_ `const FName InitialState("Ini` (scope `SGeometryCollectionOutlinerColumnID`)
- L266 _variable_ `const FName Anchored("Anc` (scope `SGeometryCollectionOutlinerColumnID`)
- L268 _variable_ `const FName Damage("Dam` (scope `SGeometryCollectionOutlinerColumnID`) — Damage Column Mode
- L269 _variable_ `const FName DamageThreshold("Dam` (scope `SGeometryCollectionOutlinerColumnID`)
- L270 _variable_ `const FName Broken("Bro` (scope `SGeometryCollectionOutlinerColumnID`)
- L272 _variable_ `const FName PostBreakTime("Pos` (scope `SGeometryCollectionOutlinerColumnID`) — Removal Column Mode
- L273 _variable_ `const FName RemovalTime("Rem` (scope `SGeometryCollectionOutlinerColumnID`)
- L275 _variable_ `const FName ConvexCount("Con` (scope `SGeometryCollectionOutlinerColumnID`) — Collision Column Mode
- L276 _variable_ `const FName ImportedCollisions("Imp` (scope `SGeometryCollectionOutlinerColumnID`)
- L278 _variable_ `const FName VertexCount("Ver` (scope `SGeometryCollectionOutlinerColumnID`) — Geometry Column Mode
- L279 _variable_ `const FName TriangleCount("Tri` (scope `SGeometryCollectionOutlinerColumnID`)
- L308 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnBoneSelectionChanged, UGeometryCollectionComponent*, TArray<int32>&);`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/SGeometryCollectionStatistics.h` (Private)


#### struct `FGeometryCollectionStatistics`  
`struct FGeometryCollectionStatistics`  
_L10-15_
- L12 _public member_ `TArray<uint32> CountsPerLevel;`
- L13 _public member_ `TArray<uint32> ConvexCountPerLevel;`
- L14 _public member_ `uint32 EmbeddedCount = 0;`

#### class `SGeometryCollectionStatistics`  
`class SGeometryCollectionStatistics : public SCompoundWidget`  
_L17-58_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SGeometryCollectionStatistics)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _public prototype_ `void SetStatistics(const FGeometryCollectionStatistics& Stats);`
- L33 _public prototype_ `void Refresh();`
- L46 _private typedef_ `using FListItemPtr = TSharedPtr<FStatRow>;`
- L49 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(FListItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Callback for generating package info rows.
- L54 _private member_ `TSharedPtr<SListView<FListItemPtr>> StatListView;` — Holds the ListView of package details rows.
- L57 _private member_ `TArray<FListItemPtr> StatItems;` — Holds the package details rows.

#### struct `SGeometryCollectionStatistics::FStatRow`  
`struct FStatRow`  
_L38-44_
- desc: Holds basic information about a stat.
- L40 _public member_ `FText Name;`
- L41 _public member_ `FText NumBones;`
- L42 _public member_ `FText NumConvex;`
- L43 _public member_ `FSlateColor TextColor;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Public/FractureEditor.h` (Public)


#### class `FFractureEditorModule`  
`class FFractureEditorModule : public IModuleInterface`  
_L12-26_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() const;` — Extensibility Manager for Adding Fracture Tools
- L25 _private member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Public/FractureEditorMode.h` (Public)


#### class `UFractureEditorMode`  
`class UFractureEditorMode : public UBaseLegacyWidgetEdMode, public FEditorUndoClient, public ILegacyEdModeSelectInterface`  
_L21-99_
- reflection: `UCLASS(Transient)`
- inherits: `UBaseLegacyWidgetEdMode,FEditorUndoClient,ILegacyEdModeSelectInterface`
- L25 _public member_ `const static FEditorModeID EM_FractureEditorModeId;`
- L27 _public prototype_ `UFractureEditorMode();`
- L28 _public prototype_ `virtual ~UFractureEditorMode();`
- L34 _public prototype_ `virtual void Enter() override;` — UEdMode interface
- L35 _public prototype_ `virtual void Exit() override;`
- L37 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L38 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L39 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L41 _public prototype_ `virtual void CreateToolkit() override;`
- L42 _public prototype_ `bool UsesToolkits() const override;`
- L43 _public prototype_ `virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;`
- L44 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L47 _public prototype_ `bool SelectFromClick(HHitProxy* HitProxy, bool bCtrlDown, bool bShiftDown);` — Helper for HandleClick, exposed to allow other code paths to handle clicks via the same code path
- L49 _public prototype_ `virtual bool ComputeBoundingBoxForViewportFocus(AActor* Actor, UPrimitiveComponent* PrimitiveComponent, FBox& InOutBox) const;`
- L50 _public prototype_ `virtual bool GetPivotForOrbit(FVector& OutPivot) const override;`
- L54 _public prototype_ `virtual bool InputAxis(FEditorViewportClient* InViewportClient, FViewport* InViewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime) override;` — ILegacyEdModeViewportInterface
- L55 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L58 _public prototype_ `virtual bool BoxSelect(FBox& InBox, bool InSelect = true) override;` — ILegacyEdModeSelectInterface
- L59 _public prototype_ `virtual bool FrustumSelect(const FConvexVolume& InFrustum, FEditorViewportClient* InViewportClient, bool InSelect) override;`
- L62 _public prototype_ `bool UpdateSelectionInFrustum(const FConvexVolume& InFrustum, AActor* Actor, bool bStrictDragSelection, bool bAppend, bool bRemove);` — Helpers for FrustumSelect + to expose similar selection functionality to other code
- L63 _public prototype_ `bool UpdateSelection(const TArray<int32>& PreviousSelection, TArray<int32>& Bones, bool bAppend, bool bRemove);`
- L66 _public prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;` — FEditorUndoClient interface
- L67 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L68 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L72 _public prototype_ `void RefreshOutlinerWithCurrentSelection();` — Used to update outliner when the selection hasn't change -- needed because the outliner is not built yet when Enter() is called TODO: We may be able to remove this function if we can find a way to invoke Enter's current selection-update logic after the outliner UI is built
- L75 _private prototype_ `void OnUndoRedo();`
- L76 _private prototype_ `void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);`
- L77 _private prototype_ `void GetComponentGlobalBounds(UGeometryCollectionComponent* GeometryCollectionComponent, TArray<FBox>& BoundsPerBone) const;`
- L78 _private prototype_ `void SelectionStateChanged();`
- L81 _private prototype_ `void HandlePackageReloaded(const EPackageReloadPhase InPackageReloadPhase, FPackageReloadedEvent* InPackageReloadedEvent);` — Handle package reloading (might be our geometry collection)
- L83 _private prototype_ `static FConvexVolume TransformFrustum(const FConvexVolume& InFrustum, const FMatrix& InMatrix);`
- L84 _private prototype_ `static FConvexVolume GetVolumeFromBox(const FBox &InBox);`
- L86 _private prototype_ `void ConfigureRealTimeViewportsOverride(bool bEnable);`
- L88 _private prototype_ `void RenderSelectionAsBoxes(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI);`
- L92 _private member_ `TArray<TWeakObjectPtr<UGeometryCollectionComponent>> SelectedGeometryComponents;` — This selection set is updated from actor selection changed event.  We change state on components as they are selected so we have to maintain or own list
- L95 _private prototype_ `TArray<UGeometryCollectionComponent*> GetValidSelectedGeometryComponents();` — Return an array of all selected geometry collection components that are still valid/non-null
- L98 _private member_ `mutable TOptional<FVector> CustomOrbitPivot;` — Hack: We have to set this to work around the editor defaulting to orbit around selection and breaking our custom per-bone orbiting

#### struct `FFractureModeCustomSectionColor`  
`struct FFractureModeCustomSectionColor`  
_L108-119_
- reflection: `USTRUCT()`
- desc: Defines a color to be used for a particular Tool Palette Section
- L114 _public member_ `FString SectionName = TEXT("");` — `UPROPERTY(EditAnywhere, Category = "SectionColor")` — Name of Section in Fracture Mode Tool Palette
- L118 _public member_ `FLinearColor Color = FLinearColor::Gray;` — `UPROPERTY(EditAnywhere, Category = "SectionColor")` — Custom Header Color

#### struct `FFractureModeCustomToolColor`  
`struct FFractureModeCustomToolColor`  
_L126-143_
- reflection: `USTRUCT()`
- desc: Defines a color to be used for a particular Tool Palette Section
- L138 _public member_ `FString ToolName = TEXT("");` — `UPROPERTY(EditAnywhere, Category = "ToolColor")` — Name of Section or Tool in Fracture Mode Tool Palette Format: SectionName        (Specifies a default color for all tools in the section.) SectionName.ToolName        (Specifies an override color for a specific tool in the given section.)
- L142 _public member_ `FLinearColor Color = FLinearColor::Gray;` — `UPROPERTY(EditAnywhere, Category = "ToolColor")` — Custom Tool Color

#### class `UFractureModeCustomizationSettings`  
`class UFractureModeCustomizationSettings : public UDeveloperSettings`  
_L147-192_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UDeveloperSettings`
- L154 _public function_ `virtual FName GetContainerName() const`
- L155 _public function_ `virtual FName GetCategoryName() const`
- L156 _public function_ `virtual FName GetSectionName() const`
- L158 _public function_ `virtual FText GetSectionText() const override`
- L163 _public function_ `virtual FText GetSectionDescription() const override`
- L173 _public member_ `TArray<FString> ToolSectionOrder;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|UI Customization")` — Add the names of Fracture Mode Tool Palette Sections to have them appear at the top of the Tool Palette, in the order listed below.
- L177 _public member_ `TArray<FString> ToolFavorites;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|UI Customization")` — Tool Names listed in the array below will appear in a Favorites section at the top of the Fracture Mode Tool Palette
- L181 _public member_ `TArray<FFractureModeCustomSectionColor> SectionColors;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|UI Customization")` — Custom Section Header Colors for listed Sections in the Fracture Mode Tool Palette
- L191 _public member_ `TArray<FFractureModeCustomToolColor> ToolColors;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|UI Customization")` — Custom Tool Colors for listed Tools in the Fracture Mode Tool Palette. Format: SectionName        (Specifies a default color for all tools in the section.) SectionName.ToolName        (Specifies an override color for a specific tool in the given section.)

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace FractureTransactionContexts`
- L17 _variable_ `static const TCHAR SelectBoneContext[] = TEXT("Sel` (scope `FractureTransactionContexts`)

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Public/FractureEditorModeToolkit.h` (Public)


#### class `FFractureViewSettingsCustomization`  
`class FFractureViewSettingsCustomization : public IDetailCustomization`  
_L49-59_
- inherits: `IDetailCustomization`
- L52 _public prototype_ `FFractureViewSettingsCustomization(FFractureEditorModeToolkit* FractureToolkit);`
- L53 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(FFractureEditorModeToolkit* FractureToolkit);`
- L55 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L58 _private member_ `FFractureEditorModeToolkit* Toolkit;`

#### class `FHistogramSettingsCustomization`  
`class FHistogramSettingsCustomization : public IDetailCustomization`  
_L61-71_
- inherits: `IDetailCustomization`
- L64 _public prototype_ `FHistogramSettingsCustomization(FFractureEditorModeToolkit* FractureToolkit);`
- L65 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(FFractureEditorModeToolkit* FractureToolkit);`
- L67 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L70 _private member_ `FFractureEditorModeToolkit* Toolkit;`

#### class `FOutlinerSettingsCustomization`  
`class FOutlinerSettingsCustomization : public IDetailCustomization`  
_L73-83_
- inherits: `IDetailCustomization`
- L76 _public prototype_ `FOutlinerSettingsCustomization(FFractureEditorModeToolkit* FractureToolkit);`
- L77 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(FFractureEditorModeToolkit* FractureToolkit);`
- L79 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L82 _private member_ `FFractureEditorModeToolkit* Toolkit;`

#### struct `FTextAndSlateColor`  
`struct FTextAndSlateColor`  
_L85-93_
- L87 _public function_ `FTextAndSlateColor(const FText& InText, const FSlateColor& InColor) : Text(InText) , Color(InColor)`
- L91 _public member_ `FText Text;`
- L92 _public member_ `FSlateColor Color;`

#### enum `EOutlinerColumnMode`  
`enum class EOutlinerColumnMode : uint8`  
_L96-104_
- reflection: `UENUM(BlueprintType)`
- L98 _public enumerator_ `State = 0 UMETA(DisplayName = "State")`
- L99 _public enumerator_ `Damage = 1 UMETA(DisplayName = "Damage")`
- L100 _public enumerator_ `Removal = 2 UMETA(DisplayName = "Removal")`
- L101 _public enumerator_ `Collision = 3 UMETA(DisplayName = "Collision")`
- L102 _public enumerator_ `Size = 4 UMETA(DisplayName = "Size")`
- L103 _public enumerator_ `Geometry = 5 UMETA(DisplayName = "Geometry")`

#### class `FFractureEditorModeToolkit`  
`class FFractureEditorModeToolkit : public FModeToolkit, public FGCObject`  
_L106-292_
- inherits: `FModeToolkit,FGCObject`
- L110 _public typedef_ `using FGeometryCollectionPtr = TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe>;`
- L112 _public prototype_ `FFractureEditorModeToolkit();`
- L113 _public prototype_ `~FFractureEditorModeToolkit();`
- L116 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;` — FModeToolkit interface
- L118 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L119 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L120 _public prototype_ `virtual class FEdMode* GetEditorMode() const override;`
- L121 _public prototype_ `virtual TSharedPtr<class SWidget> GetInlineContent() const override;`
- L124 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L125 _public function_ `virtual FString GetReferencerName() const override`
- L130 _public prototype_ `void ExecuteAction(UFractureActionTool* InActionTool);`
- L131 _public prototype_ `bool CanExecuteAction(UFractureActionTool* InActionTool) const;`
- L133 _public prototype_ `bool CanSetModalTool(UFractureModalTool* InActiveTool) const;`
- L134 _public prototype_ `void SetActiveTool(UFractureModalTool* InActiveTool);`
- L135 _public prototype_ `UFractureModalTool* GetActiveTool() const;`
- L136 _public prototype_ `bool IsActiveTool(UFractureModalTool* InActiveTool);`
- L137 _public prototype_ `void ShutdownActiveTool();`
- L139 _public prototype_ `void Shutdown();`
- L141 _public prototype_ `void SetOutlinerComponents(const TArray<UGeometryCollectionComponent*>& InNewComponents);`
- L142 _public prototype_ `void SetBoneSelection(UGeometryCollectionComponent* InRootComponent, const TArray<int32>& InSelectedBones, bool bClearCurrentSelection, int32 FocusBoneIdx = -1);`
- L145 _public prototype_ `float GetExplodedViewValue() const;` — View Settings
- L146 _public prototype_ `int32 GetLevelViewValue() const;`
- L147 _public prototype_ `bool GetHideUnselectedValue() const;`
- L148 _public prototype_ `void OnSetExplodedViewValue(float NewValue);`
- L149 _public prototype_ `void OnSetLevelViewValue(int32 NewValue);`
- L151 _public prototype_ `void OnExplodedViewValueChanged();`
- L152 _public prototype_ `void OnLevelViewValueChanged();`
- L153 _public prototype_ `void OnHideUnselectedChanged();`
- L154 _public prototype_ `void UpdateHideForComponent(UGeometryCollectionComponent* Component);`
- L157 _public prototype_ `void OnObjectPostEditChange( UObject* Object, FPropertyChangedEvent& PropertyChangedEvent );` — Update any View Property Changes
- L159 _public prototype_ `TSharedRef<SWidget> GetLevelViewMenuContent(TSharedRef<IPropertyHandle> PropertyHandle);`
- L160 _public prototype_ `TSharedRef<SWidget> GetViewMenuContent();`
- L162 _public prototype_ `void ToggleShowBoneColors();`
- L164 _public prototype_ `void ViewUpOneLevel();`
- L165 _public prototype_ `void ViewDownOneLevel();`
- L168 _public prototype_ `FReply OnModalClicked();` — Modal Command Callback
- L169 _public prototype_ `bool CanExecuteModal() const;`
- L171 _public prototype_ `static void GetSelectedGeometryCollectionComponents(TSet<UGeometryCollectionComponent*>& GeomCompSelection);`
- L173 _public prototype_ `static void AddAdditionalAttributesIfRequired(UGeometryCollection* GeometryCollectionObject);`
- L174 _public prototype_ `int32 GetLevelCount();`
- L176 _public prototype_ `void GetStatisticsSummary(FGeometryCollectionStatistics& Stats) const;`
- L177 _public prototype_ `FText GetSelectionInfo() const;`
- L180 _public member_ `const static TArray<FName> PaletteNames;` — Returns the number of Mode specific tabs in the mode toolbar
- L181 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& InPaletteName) const;`
- L182 _public prototype_ `virtual FText GetToolPaletteDisplayName(FName PaletteName) const;`
- L185 _public function_ `virtual bool HasExclusiveToolPalettes() const` — Exclusive Tool Palettes only allow users to use tools from one palette at a time
- L188 _public function_ `virtual bool HasIntegratedToolPalettes() const` — Integrated Tool Palettes show up in the same panel as their details
- L190 _public prototype_ `void SetInitialPalette();`
- L191 _public prototype_ `virtual void BuildToolPalette(FName PaletteName, class FToolBarBuilder& ToolbarBuilder);`
- L192 _public prototype_ `virtual void OnToolPaletteChanged(FName PaletteName) override;`
- L195 _public prototype_ `virtual FText GetActiveToolDisplayName() const;` — Modes Panel Header Information
- L196 _public prototype_ `virtual FText GetActiveToolMessage() const;`
- L198 _public prototype_ `void UpdateExplodedVectors(UGeometryCollectionComponent* GeometryCollectionComponent) const;`
- L200 _public prototype_ `void RefreshOutliner();`
- L202 _public prototype_ `void RegenerateOutliner();`
- L203 _public prototype_ `void RegenerateHistogram();`
- L205 _public member_ `TSharedPtr<SWidget> ExplodedViewWidget;`
- L206 _public member_ `TSharedPtr<SWidget> LevelViewWidget;`
- L207 _public member_ `TSharedPtr<SWidget> ShowBoneColorsWidget;`
- L209 _public prototype_ `void SetOutlinerColumnMode(EOutlinerColumnMode ColumnMode);`
- L212 _public prototype_ `bool IsCachedOutlinerGeometryStale(const TArray<TWeakObjectPtr<UGeometryCollectionComponent>>& SelectedComponents) const;` — function to poll whether the geometry collection data cached by the outliner is stale compared to the current geometry (using quick heuristics such as bone counts)
- L216 _protected prototype_ `virtual void RequestModeUITabs() override;` — FModeToolkit interface
- L217 _protected prototype_ `virtual void InvokeUI() override;`
- L219 _protected prototype_ `TSharedRef<SDockTab> CreateHierarchyTab(const FSpawnTabArgs& Args);`
- L220 _protected prototype_ `TSharedRef<SDockTab> CreateStatisticsTab(const FSpawnTabArgs& Args);`
- L221 _protected prototype_ `static bool IsGeometryCollectionSelected();`
- L222 _protected prototype_ `static bool IsSelectedActorsInEditorWorld();`
- L224 _protected prototype_ `void InvalidateCachedDetailPanelState(UObject* ChangedObject);`
- L227 _protected prototype_ `void InvalidateHitProxies();` — Invalidate the hit proxies for all level viewports; we need to do this after updating geometry collection(s)
- L230 _private prototype_ `static void UpdateGeometryComponentAttributes(UGeometryCollectionComponent* Component);`
- L232 _private prototype_ `void OnOutlinerBoneSelectionChanged(UGeometryCollectionComponent* RootComponent, TArray<int32>& SelectedBones);`
- L233 _private prototype_ `void OnHistogramBoneSelectionChanged(UGeometryCollectionComponent* RootComponent, TArray<int32>& SelectedBones);`
- L234 _private prototype_ `void BindCommands();`
- L236 _private prototype_ `void SetHideForUnselected(UGeometryCollectionComponent* GCComp);`
- L239 _private prototype_ `void HandleMapChanged(UWorld* NewWorld, EMapChangeType MapChangeType);` — Callback for map changes.
- L241 _private prototype_ `FReply OnRefreshOutlinerButtonClicked();`
- L243 _private prototype_ `TSharedRef<SWidget> MakeMenu_FractureModeConfigSettings();`
- L244 _private prototype_ `void UpdateAssetLocationMode(TSharedPtr<FString> NewString);`
- L245 _private prototype_ `void UpdateAssetPanelFromSettings();`
- L246 _private prototype_ `void OnProjectSettingsModified();`
- L248 _private prototype_ `void UpdateOutlinerHeader();`
- L250 _private prototype_ `void CreateVariableOverrideDetailView();`
- L251 _private prototype_ `void OnPropertyValueChanged(const FPropertyChangedEvent& PropertyChangedEvent);`
- L252 _private prototype_ `void RefreshVariableOverrideDetailView(const UGeometryCollection* RestCollection);`
- L254 _private prototype_ `FReply OnDataflowOverridesUpdateAsset();`
- L255 _private prototype_ `bool CanDataflowOverridesUpdateAsset() const;`
- L256 _private prototype_ `bool GetDataflowOverridesUpdateAssetEnabled() const;`
- L258 _private prototype_ `void CreateDataflowProgressBar();`
- L261 _private member_ `TObjectPtr<UFractureModalTool> ActiveTool;`
- L264 _private member_ `FDelegateHandle BeginPIEDelegateHandle;` — called when PIE is about to start, shuts down active tools
- L266 _private member_ `FDelegateHandle ProjectSettingsModifiedHandle;` — calls with the project settings are modified; used to keep the quick settings up to date
- L268 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L269 _private member_ `TSharedPtr<IDetailsView> FractureSettingsDetailsView;`
- L270 _private member_ `TSharedPtr<IStructureDetailsView> OverridesDetailsView;`
- L271 _private member_ `TSharedPtr<IDetailsView> HistogramDetailsView;`
- L272 _private member_ `TSharedPtr<IDetailsView> OutlinerDetailsView;`
- L273 _private member_ `TSharedPtr<SWidget> ToolkitWidget;`
- L274 _private member_ `TSharedPtr<SGeometryCollectionOutliner> OutlinerView;`
- L275 _private member_ `TSharedPtr<SGeometryCollectionHistogram> HistogramView;`
- L276 _private member_ `TWeakPtr<SDockTab> HierarchyTab;`
- L277 _private member_ `FMinorTabConfig HierarchyTabInfo;`
- L278 _private member_ `TWeakPtr<SDockTab> StatisticsTab;`
- L279 _private member_ `FMinorTabConfig StatisticsTabInfo;`
- L280 _private member_ `TSharedPtr<SGeometryCollectionStatistics> StatisticsView;`
- L281 _private member_ `TArray<TSharedPtr<FString>> AssetLocationModes;`
- L282 _private member_ `TSharedPtr<STextComboBox> AssetLocationMode;`
- L283 _private member_ `TSharedPtr<SWidget> DataflowProgressBar;`
- L285 _private member_ `TSharedPtr<UE::Dataflow::FEngineContext> DataflowContext;`
- L286 _private member_ `TSharedPtr<UE::Dataflow::IDataflowEvaluator> DataflowEvaluator;`
- L289 _private member_ `int64 OutlinerCachedBoneCount = 0, OutlinerCachedVertexCount = 0, OutlinerCachedHullCount = 0;` — Simple cached statistics to allow use to quickly/heuristically check for stale geometry collection data
- L289 _private member_ `int64 OutlinerCachedBoneCount = 0, OutlinerCachedVertexCount = 0, OutlinerCachedHullCount = 0;` — Simple cached statistics to allow use to quickly/heuristically check for stale geometry collection data
- L289 _private member_ `int64 OutlinerCachedBoneCount = 0, OutlinerCachedVertexCount = 0, OutlinerCachedHullCount = 0;` — Simple cached statistics to allow use to quickly/heuristically check for stale geometry collection data
- L291 _private member_ `FDelegateHandle OnFinishedChangingVariableOverridesDelegateHandle;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API FRACTUREEDITOR_API`
- L38 _namespace_ `namespace GeometryCollection`
- L43 _namespace_ `namespace Chaos`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Public/FractureModeSettings.h` (Public)


#### enum `EFractureModeNewAssetLocation`  
`enum class EFractureModeNewAssetLocation`  
_L19-29_
- reflection: `UENUM()`
- desc: Control the default asset folder presented when using the "New" tool to create a Geometry Collection in Fracture Mode
- L22 _public enumerator_ `SourceAssetFolder` — Default to creating rest collections in the same folder as the source asset.
- L25 _public enumerator_ `LastUsedFolder` — Default to creating rest collections in the last folder selected this session. If no folder was selected yet, use the Source Asset Folder.
- L28 _public enumerator_ `ContentBrowserFolder` — Default to creating reset collections in the currently-visible Asset Browser folder if available, otherwise use the Last Used Folder.

#### class `UFractureModeSettings`  
`class UFractureModeSettings : public UDeveloperSettings`  
_L35-123_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UDeveloperSettings`
- desc: Settings for the Fracture Editor Mode.
- L43 _public function_ `virtual FName GetContainerName() const override`
- L44 _public function_ `virtual FName GetCategoryName() const override`
- L45 _public function_ `virtual FName GetSectionName() const override`
- L47 _public function_ `virtual FText GetSectionText() const override`
- L48 _public function_ `virtual FText GetSectionDescription() const override`
- L54 _public member_ `EFractureModeNewAssetLocation NewAssetLocation = EFractureModeNewAssetLocation::SourceAssetFolder;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|Asset Location")` — The default asset folder presented when using the "New" tool to create a Geometry Collection in Fracture Mode
- L58 _public member_ `float ConvexCanExceedFraction = .5;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|Convex Generation Defaults", meta = (ClampMin = "0", DisplayName = "Allow Larger Hull Fraction"))` — Default fraction of geometry volume by which a cluster's convex hull volume can exceed the actual geometry volume before instead using the hulls of the children.  0 means the convex volume cannot exceed the geometry volume; 1 means the convex volume is allowed to be 100% larger (2x) the geometry volume.
- L62 _public member_ `float ConvexSimplificationDistanceThreshold = 10;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|Convex Generation Defaults", meta = (ClampMin = "0", DisplayName = "Simplification Distance Threshold"))` — Default simplification threshold for convex hulls of new geometry collections
- L66 _public member_ `EConvexOverlapRemoval ConvexRemoveOverlaps = EConvexOverlapRemoval::All;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|Convex Generation Defaults|Overlap Removal", meta = (DisplayName = "Remove Overlaps"))` — Default overlap removal setting for convex hulls of new geometry collections
- L70 _public member_ `float ConvexOverlapRemovalShrinkPercent = 0;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|Convex Generation Defaults|Overlap Removal", meta = (UIMin = "0", ClampMax = "99.9", DisplayName = "Overlap Removal Shrink Percent"))` — Default overlap removal shrink percent (in range 0-100) for convex hulls of new geometry collections. Overlap removal will be computed assuming convex shapes will be scaled down by this percentage.
- L74 _public member_ `double ConvexFractionAllowRemove = .5;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|Convex Generation Defaults|Overlap Removal", meta = (DisplayName = "Max Removal Fraction", ClampMin = ".01", ClampMax = "1"))` — Default fraction of convex hulls for a transform that we can remove before using the hulls of the children
- L79 _public member_ `EProximityMethod ProximityMethod = EProximityMethod::Precise;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|Proximity Detection Defaults", meta = (DisplayName = "Detection Method"))` — Default method used to detect proximity of geometry in a new geometry collection
- L83 _public member_ `float ProximityDistanceThreshold = 1;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|Proximity Detection Defaults", meta = (ClampMin = "0", DisplayName = "Distance Threshold", EditCondition = "ProximityMethod == EProximityMethod::ConvexHull"))` — When Proximity Detection Method is Convex Hull, how close two hulls need to be to be considered as 'in proximity'
- L87 _public member_ `bool bProximityUseAsConnectionGraph = false;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|Proximity Detection Defaults", meta = (DisplayName = "Use As Connection Graph"))` — Whether to automatically transform the proximity graph into a connection graph to be used for simulation
- L91 _public member_ `EConnectionContactMethod ProximityConnectionContactAreaMethod = EConnectionContactMethod::None;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|Proximity Detection Defaults", meta = (DisplayName = "Connection Contact Method"))` — Method to use to determine the area of the contact for transforms that are connected in the connection graph used for simulation. Only used if "Use As Connection Graph" is enabled.
- L95 _public member_ `EProximityContactMethod ProximityContactMethod = EProximityContactMethod::MinOverlapInProjectionToMajorAxes;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|Proximity Detection Defaults", meta = (DisplayName = "Contact Filter Method"))` — Method to use to determine the contact between two pieces, if the Contact Threshold is greater than 0, for the purpose of filtering out too-small contacts
- L99 _public member_ `float ProximityContactThreshold = 0;` — `UPROPERTY(config, EditAnywhere, Category = "Fracture Mode|Proximity Detection Defaults", meta = (ClampMin = "0", DisplayName = "Contact Threshold"))` — If greater than zero, proximity will be additionally filtered by a 'contact' threshold, in cm, to exclude grazing / corner proximity
- L103 _public prototype_ `void ApplyDefaultConvexSettings(FGeometryCollection& GeometryCollection) const;` — Apply Convex Generation Defaults to a GeometryCollection
- L106 _public prototype_ `void ApplyDefaultProximitySettings(FGeometryCollection& GeometryCollection) const;` — Apply Proximity Detection Defaults to a GeometryCollection
- L109 _public prototype_ `void ApplyDefaultSettings(FGeometryCollection& GeometryCollection) const;` — Apply all default settings to a GeometryCollection
- L112 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(UFractureModeSettingsModified, UObject*, FProperty*);`
- L113 _public member_ `UFractureModeSettingsModified OnModified;`
- L115 _public function_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API FRACTUREEDITOR_API`
- L112 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(UFractureModeSettingsModified, UObject*, FProperty*);`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Public/FractureSelectionTools.h` (Public)


#### class `FFractureSelectionTools`  
`class FFractureSelectionTools`  
_L10-26_
- L22 _public prototype_ `static void ToggleSelectedBones(UGeometryCollectionComponent* GeometryCollectionComponent, const TArray<int32>& BoneIndices, bool bClearCurrentSelection, bool bAdd, bool bSnapToLevel = true);` — Sets the selected bones on a geometry collection component @param GeometryCollectionComponent	The component with bones being selected @param BoneIndices					The indices to select @param bClearCurrentSelection		Whether to clear the current selection set or just append the new indices to it @param bAdd							Whether to always add the BoneIndices to the selection, or to toggle them (i.e., de-select if they were previously selected) @param bSnapToLevel					Whether to snap the selection to the nearest visible bones (in the 3D view and outliner) by searching the parent bones
- L23 _public prototype_ `static void ClearSelectedBones(UGeometryCollectionComponent* GeometryCollectionComponent);`
- L25 _public prototype_ `static void SelectNeighbors(UGeometryCollectionComponent* GeometryCollectionComponent);`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Public/FractureSettings.h` (Public)


#### enum `EFractureSelectionDisplayMode`  
`enum class EFractureSelectionDisplayMode : uint8`  
_L13-23_
- reflection: `UENUM()`
- L16 _public enumerator_ `Highlight` — Use a glow material to highlight the selection - Nanite Geometry Collection will ignore it and use bounding boxes instead
- L19 _public enumerator_ `BoundingBox` — Use bounding boxes to show selection - Nanite Geometry Collection will default to that
- L22 _public enumerator_ `None` — do not display bone selection at all

#### class `UFractureSettings`  
`class UFractureSettings: public UObject`  
_L28-54_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Settings specifically related to viewing fractured meshes
- L33 _public prototype_ `UFractureSettings(const FObjectInitializer& ObjInit);`
- L37 _public member_ `float ExplodeAmount;` — `UPROPERTY(EditAnywhere, Category = ViewSettings, meta = (DisplayName = "Explode Amount", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount to expand the displayed Geometry Collection bones into an 'exploded view'
- L41 _public member_ `int32 FractureLevel;` — `UPROPERTY(EditAnywhere, Category = ViewSettings, meta = (DisplayName = "Fracture Level", UIMin = "-1" ))` — Current level of the Geometry Collection displayed
- L45 _public member_ `bool bHideUnselected;` — `UPROPERTY(EditAnywhere, Category = ViewSettings, meta = (DisplayName = "Hide Unselected"))` — When active, only show selected bones
- L49 _public member_ `EFractureSelectionDisplayMode SelectionDisplayMode;` — `UPROPERTY(EditAnywhere, Category = ViewSettings, meta = (DisplayName = "Highlight Selected"))` — How to display the selection in the viewport
- L52 _public member_ `TWeakObjectPtr<const UGeometryCollection> RestCollection = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = ViewSettings)`

### `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Public/FractureTool.h` (Public)


#### class `UFractureToolSettings`  
`class UFractureToolSettings : public UObject`  
_L27-38_
- reflection: `UCLASS(Abstract, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L31 _public function_ `UFractureToolSettings(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L33 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L34 _public prototype_ `void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L37 _public member_ `TObjectPtr<UFractureModalTool> OwnerTool;` — `UPROPERTY()`

#### class `UFractureActionTool`  
`class UFractureActionTool : public UObject`  
_L44-105_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: Tools derived from this class should require parameter inputs from the user, only the bone selection.
- L49 _public function_ `UFractureActionTool(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L52 _public function_ `virtual FText GetDisplayText() const` — This is the Text that will appear on the tool button to execute the tool
- L53 _public function_ `virtual FText GetTooltipText() const`
- L55 _public function_ `virtual FSlateIcon GetToolIcon() const`
- L58 _public function_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit)` — Executes the command.  Derived types need to be implemented in a thread safe way
- L59 _public prototype_ `virtual bool CanExecute() const;`
- L62 _public prototype_ `const TSharedPtr<FUICommandInfo>& GetUICommandInfo() const;` — Gets the UI command info for this command
- L64 _public function_ `virtual void RegisterUICommand(FFractureEditorCommands* BindingContext)`
- L66 _public prototype_ `virtual TArray<FFractureToolContext> GetFractureToolContexts() const;`
- L87 _public prototype_ `static void GetSelectedGeometryCollectionComponents(TSet<UGeometryCollectionComponent*>& GeomCompSelection, bool bFilterForUniqueRestCollections = false);` — Get the Geometry Collection components in the current selection @param GeomCompSelection					the set to fill with Geometry Collection components @param bFilterForUniqueRestCollections	if true, and selection contains multiple components backed by the same Rest Collection asset, the selection will be filtered to only contain one component per asset
- L88 _public prototype_ `static TArray<FString> GetSelectedComponentMaterialNames(bool bIncludeDefault, bool bUseFullNamesIfPossible = true);`
- L92 _protected prototype_ `static bool IsStaticMeshSelected();`
- L93 _protected prototype_ `static bool IsGeometryCollectionSelected();`
- L94 _protected prototype_ `static void AddSingleRootNodeIfRequired(UGeometryCollection* GeometryCollectionObject);`
- L95 _protected prototype_ `static void AddAdditionalAttributesIfRequired(UGeometryCollection* GeometryCollectionObject);`
- L96 _protected prototype_ `static void Refresh(FFractureToolContext& Context, FFractureEditorModeToolkit* Toolkit, bool bClearSelection=false);`
- L97 _protected prototype_ `static void Refresh(UGeometryCollectionComponent* Component, FFractureEditorModeToolkit* Toolkit, const TArray<int32>& SetSelection, bool bClearSelection=false, bool bMustUpdateBoneColors=false);`
- L98 _protected prototype_ `static void SetOutlinerComponents(TArray<FFractureToolContext>& InContexts, FFractureEditorModeToolkit* Toolkit);`
- L99 _protected prototype_ `static void ClearProximity(FGeometryCollection* GeometryCollection);`
- L103 _protected member_ `TSharedPtr<FUICommandInfo> UICommandInfo;`

#### struct `UFractureActionTool::FModifyContextScope`  
`struct FModifyContextScope`  
_L69-78_
- desc: Scope sets up modification and updates UI after
- L71 _public member_ `UFractureActionTool* ActionTool;`
- L72 _public member_ `FFractureToolContext* FractureContext;`
- L73 _public member_ `bool bNeedPhysicsUpdate;`
- L75 _public prototype_ `FModifyContextScope(UFractureActionTool* ActionTool, FFractureToolContext* FractureContext, bool bWantPhysicsUpdate = true);`
- L77 _public prototype_ `~FModifyContextScope();`

#### struct `FVisualizationMappings`  
`struct FVisualizationMappings`  
_L108-142_
- desc: Helper structure to correspond a UFractureModalTool's VisualizedCollections with elements of the tool's visualizations
- L118 _public member_ `TArray<FIndexMapping> Mappings;`
- L120 _public prototype_ `FVector GetExplodedVector(int32 MappingIdx, const UGeometryCollectionComponent* Collection) const;`
- L122 _public function_ `void Empty()`
- L127 _public function_ `void AddMapping(int32 CollectionIdx, int32 BoneIdx, int32 StartIdx = INDEX_NONE)`
- L131 _public function_ `int32 GetEndIdx(int32 CorrespondIdx, int32 ArrayNum) const`

#### struct `FVisualizationMappings::FIndexMapping`  
`struct FIndexMapping`  
_L111-116_
- desc: helper structure to map visualized geometry to source geometry and the bone that it corresponds to (if applicable)
- L113 _public member_ `int32 CollectionIdx = INDEX_NONE;` — index into VisualizedCollections
- L114 _public member_ `int32 BoneIdx = INDEX_NONE;` — transform (bone) index in geometry collection that corresponds to the visualization
- L115 _public member_ `int32 StartIdx = INDEX_NONE;` — index of first element of visualization-related array that uses this map (e.g. index into VoronoiSites)

#### class `UFractureModalTool`  
`class UFractureModalTool : public UFractureActionTool`  
_L146-245_
- reflection: `UCLASS(Abstract)`
- inherits: `UFractureActionTool`
- desc: Tools derived from this class provide parameter details and operate modally.
- L151 _public function_ `UFractureModalTool(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L153 _public function_ `virtual TArray<UObject*> GetSettingsObjects() const`
- L154 _public function_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)`
- L157 _public function_ `virtual FText GetApplyText() const` — This is the Text that will appear on the button to execute the fracture
- L160 _public prototype_ `virtual void Execute(TWeakPtr<FFractureEditorModeToolkit> InToolkit) override;` — Executes the command.  Derived types need to be implemented in a thread safe way
- L161 _public prototype_ `virtual bool CanExecute() const override;`
- L163 _public function_ `virtual bool ExecuteUpdatesShape() const` — @return true if the edit will change the shape data of the geometry collection(s) (including changing the clusters) -- used to indicate whether we need to update the convex hulls
- L169 _public function_ `virtual int32 ExecuteFracture(const FFractureToolContext& FractureContext)` — Executes function that generates new geometry. Returns the first new geometry index.
- L172 _public function_ `virtual void PostFractureProcess(const FFractureToolContext& FractureContext, int32 FirstNewGeometryIndex)` — Optional processing after a successful fracture (i.e., will not be called if ExecuteFracture returns INDEX_NONE)
- L177 _public function_ `virtual void OnTick(float DeltaTime)`
- L180 _public function_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)` — Draw callback from edmode
- L181 _public function_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas)`
- L183 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L184 _public function_ `virtual void FractureContextChanged()`
- L187 _public function_ `virtual void SelectedBonesChanged()` — Called when the selection changes, and when the modal tool is entered
- L190 _public function_ `virtual void Setup(TWeakPtr<FFractureEditorModeToolkit> InToolkit)` — Called when the modal tool is entered
- L196 _public function_ `virtual void Shutdown()` — Called when the modal tool is exited (on switching to a new modal tool or exiting the fracture editor mode)
- L204 _public function_ `virtual void OnComponentTransformChanged(UGeometryCollectionComponent* Component)` — Called when a selected geometry collection component is moved in the scene
- L215 _public prototype_ `virtual void NotifyOfPropertyChangeByTool(UFractureToolSettings* PropertySet) const;` — Call after changing properties internally in the tool to allow external views of the property to update properly. This is meant as an outward notification mechanism, not a way to to pass along notifications, so don't call this if the property is changed externally (i.e., this should not usually be called from OnPropertyModified unless the tool adds changes of its own).
- L222 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnToolPropertyInternallyModified, UObject*);` — OnPropertyModifiedDirectlyByTool is broadcast when a property is changed internally by the tool. This allows any external display of such properties to update. In a DetailsView, for instance, it refreshes certain cached states such as edit condition states for other properties.
- L223 _public member_ `OnToolPropertyInternallyModified OnPropertyModifiedDirectlyByTool;`
- L229 _protected member_ `TArray<TObjectPtr<UGeometryCollectionComponent>> VisualizedCollections;` — `UPROPERTY()` — Geometry collection components referenced by visualizations
- L231 _protected function_ `virtual void ClearVisualizations()`
- L236 _protected prototype_ `void EnumerateVisualizationMapping(const FVisualizationMappings& Mappings, int32 ArrayNum, TFunctionRef<void(int32 Idx, FVector ExplodedVector)> Func) const;`
- L238 _protected prototype_ `void OnComponentTransformChangedInternal(USceneComponent* InRootComponent, ETeleportType Teleport);`
- L241 _protected prototype_ `void OverrideEditorViewFlagsForLineRendering();` — Call to override editor view flags to disable temporal AA and motion blur, which make the lines look bad
- L243 _protected prototype_ `void RestoreEditorViewFlags();` — Restore editor view flags

#### class `UFractureInteractiveTool`  
`class UFractureInteractiveTool : public UFractureModalTool`  
_L250-259_
- reflection: `UCLASS(Abstract)`
- inherits: `UFractureModalTool`
- desc: Tools derived from this class provide parameter details, operate modally and use a viewport manipulator to set certain parameters.
- L255 _public function_ `UFractureInteractiveTool(const FObjectInitializer& ObjInit) : Super(ObjInit)`

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFractureTool, Log, All);`
- L24 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFractureTool, Log, All);`
- L222 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnToolPropertyInternallyModified, UObject*);` — OnPropertyModifiedDirectlyByTool is broadcast when a property is changed internally by the tool. This allows any external display of such properties to update. In a DetailsView, for instance, it refreshes certain cached states such as edit condition states for other properties.
