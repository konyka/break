# Plugins / ZoneGraph

- module root: `Plugins/Runtime/ZoneGraph/Source/ZoneGraph`
- headers: 17; symbols: 708
- symbol kinds: class=9, delegate=7, enum=12, enumerator=42, externvar=7, function=159, macro=8, member=206, namespace=14, prototype=195, struct=43, typedef=6
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, MassCore, MassEntity, RHI, RenderCore
- PublicIncludePathModuleNames: AIModule

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/BezierUtilities.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/IZoneGraphModule.h` (Public)


#### class `IZoneGraphModule`  
`class IZoneGraphModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IZoneGraphModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneGraphAStar.h` (Public)


#### struct `FZoneGraphAStarWrapper`  
`struct FZoneGraphAStarWrapper`  
_L15-36_
- desc: Warpper around zone graph to be used by FGraphAStar
- L17 _public function_ `FZoneGraphAStarWrapper(const FZoneGraphStorage& InZoneGraph) : ZoneGraph(InZoneGraph)`
- L23 _public typedef_ `typedef int32 FNodeRef;` — FGraphAStar: TGraph
- L25 _public function_ `inline bool IsValidRef(const FNodeRef NodeRef) const`
- L30 _public prototype_ `int32 GetNeighbourCountV2(const FZoneGraphAStarNode& Node) const;`
- L31 _public prototype_ `FNodeRef GetNeighbour(const FZoneGraphAStarNode& Node, const int32 NeighbourIndex) const;`
- L35 _protected member_ `const FZoneGraphStorage& ZoneGraph;`

#### struct `FZoneGraphAStarNode`  
`struct FZoneGraphAStarNode : public FGraphAStarDefaultNode<FZoneGraphAStarWrapper>`  
_L39-55_
- inherits: `FGraphAStarDefaultNode<FZoneGraphAStarWrapper>`
- desc: Node representation for FZoneGraphAStar
- L41 _public typedef_ `typedef FGraphAStarDefaultNode<FZoneGraphAStarWrapper> Super;`
- L42 _public typedef_ `typedef int32 FNodeRef;`
- L44 _public function_ `inline FZoneGraphAStarNode(const FNodeRef InNodeRef = INDEX_NONE, const FVector InPosition = FVector(TNumericLimits<FVector::FReal>::Max())) : Super(InNodeRef) , Position(InPosition)`
- L49 _public prototype_ `FZoneGraphAStarNode(const FZoneGraphAStarNode& Other) = default;`
- L50 _public prototype_ `FGraphAStarDefaultNode& operator=(const FGraphAStarDefaultNode& Other) = delete;`
- L52 _public function_ `bool IsStartOrIsEnd() const`
- L54 _public member_ `FVector Position;` — @todo: this will likely change to be a position along the lane

#### struct `FZoneGraphPathFilter`  
`struct FZoneGraphPathFilter`  
_L58-184_
- desc: Context for FGraphAStar::FindPath()
- L62 _public typedef_ `typedef int32 FNodeRef;`
- L64 _public function_ `FZoneGraphPathFilter(const FZoneGraphStorage& InGraph, const FZoneGraphLaneLocation& InStartLocation, const FZoneGraphLaneLocation& InEndLocation, const FZoneGraphTagFilter InZoneTagFilter = FZoneGraphTagFilter()) : ZoneStorage(InGraph) , ZoneTagFilter(InZoneTagFilter) , StartLocation(InStartLocation) , EndLocation(InEndLocation)`
- L71 _public function_ `bool IsStart(const FZoneGraphAStarNode& Node) const`
- L72 _public function_ `bool IsEnd(const FZoneGraphAStarNode& Node) const`
- L74 _public function_ `inline FVector::FReal GetHeuristicScale() const`
- L76 _public function_ `FVector::FReal GetHeuristicCost(const FZoneGraphAStarNode& NeighbourNode, const FZoneGraphAStarNode& EndNode) const`
- L98 _public function_ `FVector::FReal GetTraversalCost(const FZoneGraphAStarNode& CurNode, const FZoneGraphAStarNode& NeighbourNode) const`
- L170 _public function_ `inline bool IsTraversalAllowed(const FNodeRef StartNodeRef, const FNodeRef& Neighbour) const`
- L176 _public function_ `inline bool WantsPartialSolution() const`
- L177 _public function_ `inline bool ShouldIncludeStartNodeInPath() const`
- L180 _protected member_ `const FZoneGraphStorage& ZoneStorage;`
- L181 _protected member_ `const FZoneGraphTagFilter ZoneTagFilter;`
- L182 _protected member_ `const FZoneGraphLaneLocation StartLocation;`
- L183 _protected member_ `const FZoneGraphLaneLocation EndLocation;`

#### struct `FZoneGraphAStar`  
`struct FZoneGraphAStar : public FGraphAStar<FZoneGraphAStarWrapper, FGraphAStarDefaultPolicy, FZoneGraphAStarNode>`  
_L187-194_
- inherits: `FGraphAStar<FZoneGraphAStarWrapper,FGraphAStarDefaultPolicy,FZoneGraphAStarNode>`
- desc: A Star algorithm using lanes on zone graph
- L189 _public typedef_ `typedef FGraphAStar<FZoneGraphAStarWrapper, FGraphAStarDefaultPolicy, FZoneGraphAStarNode> Super;`
- L191 _public function_ `FZoneGraphAStar(const FZoneGraphAStarWrapper& Graph) : Super(Graph)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ZONEGRAPH_API`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneGraphBVTree.h` (Public)


#### struct `FZoneGraphBVNode`  
`struct FZoneGraphBVNode`  
_L12-56_
- reflection: `USTRUCT()`
- desc: Quantized BV-tree node.
- L16 _public prototype_ `FZoneGraphBVNode() = default;`
- L17 _public function_ `FZoneGraphBVNode(const uint16 InMinX, const uint16 InMinY, const uint16 InMinZ, const uint16 InMaxX, const uint16 InMaxY, const uint16 InMaxZ) : MinX(InMinX) , MinY(InMinY) , MinZ(InMinZ) , MaxX(InMaxX) , MaxY(InMaxY) , MaxZ(InMaxZ)`
- L27 _public function_ `bool DoesOverlap(const FZoneGraphBVNode& Other) const`
- L36 _public member_ `uint16 MinX = 0;` — `UPROPERTY()` — Quantized node bounds
- L39 _public member_ `uint16 MinY = 0;` — `UPROPERTY()`
- L42 _public member_ `uint16 MinZ = 0;` — `UPROPERTY()`
- L45 _public member_ `uint16 MaxX = 0;` — `UPROPERTY()`
- L48 _public member_ `uint16 MaxY = 0;` — `UPROPERTY()`
- L51 _public member_ `uint16 MaxZ = 0;` — `UPROPERTY()`
- L55 _public member_ `int32 Index = 0;` — `UPROPERTY()` — Item Index, or if negative, the node is internal and the index is relative index to next sibling.

#### struct `FZoneGraphBVTree`  
`struct FZoneGraphBVTree`  
_L60-139_
- reflection: `USTRUCT()`
- desc: Quantized BV-Tree
- L65 _public prototype_ `void Build(TStridedView<const FBox> Boxes);` — Build BV-tree from boxes, the index of the box in the array will be the index of the query result.
- L69 _public function_ `template<typename TFunc> void Query(const FBox& Bounds, TFunc&& Function) const` — Queries the BV-tree, calls Function on each child node which bounds overlap the query bounds.
- L91 _public prototype_ `void Query(const FBox& Bounds, TArray<int32>& OutItems) const;` — Queries the BV-tree, return index of overlapping items.
- L94 _public function_ `int32 GetNumNodes() const` — @return number of nodes in the tree
- L97 _public function_ `const FVector& GetOrigin() const` — @return quantization origin
- L100 _public function_ `float GetQuantizationScale() const` — @return world-to-quantized scaling factor
- L103 _public function_ `TConstArrayView<FZoneGraphBVNode> GetNodes() const` — @return Tree nodes.
- L106 _public function_ `FZoneGraphBVNode CalcNodeBounds(const FBox& Box) const` — @return quantized node bounds based on world bounds.
- L116 _public function_ `FBox CalcWorldBounds(const FZoneGraphBVNode& Node) const` — @return world bounding box of a node.
- L126 _protected member_ `static constexpr float MaxQuantizedCoord = float(MAX_uint16 - 1);` — Max quantized coordinate value during conversion, the scale is truncated to account for the expansion in CalcNodeBounds().
- L130 _protected member_ `FVector Origin = FVector::ZeroVector;` — `UPROPERTY()` — Quantization range origin
- L134 _protected member_ `float QuantizationScale = 0.0f;` — `UPROPERTY()` — Scale to convert from world coordinates to quantized range.
- L138 _protected member_ `TArray<FZoneGraphBVNode> Nodes;` — `UPROPERTY()` — BV-tree nodes.

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneGraphBuilder.h` (Public)


#### struct `FZoneGraphBuilderRegisteredComponent`  
`struct FZoneGraphBuilderRegisteredComponent`  
_L19-33_
- reflection: `USTRUCT()`
- L23 _public prototype_ `FZoneGraphBuilderRegisteredComponent() = default;`
- L24 _public function_ `FZoneGraphBuilderRegisteredComponent(UZoneShapeComponent* InComponent) : Component(InComponent)`
- L27 _public member_ `TObjectPtr<UZoneShapeComponent> Component = nullptr;` — `UPROPERTY()`
- L30 _public member_ `uint32 ShapeHash = 0;` — `UPROPERTY()`
- L32 _public member_ `FZoneGraphBuilderHashGrid2D::FCellLocation CellLoc;`

#### struct `FZoneShapeComponentBuildData`  
`struct FZoneShapeComponentBuildData`  
_L37-46_
- reflection: `USTRUCT()`
- desc: Build time data for UZoneShapeComponent
- L42 _public member_ `int32 ZoneIndex = 0;` — `UPROPERTY()`
- L45 _public member_ `TArray<FZoneGraphLaneHandle> Lanes;` — `UPROPERTY()`

#### struct `FZoneGraphBuildData`  
`struct FZoneGraphBuildData`  
_L50-61_
- reflection: `USTRUCT()`
- desc: Build time data, can be used to map things between editor representation and baked data.
- L54 _public function_ `void Reset()`
- L60 _public member_ `TMap<TObjectPtr<const UZoneShapeComponent>, FZoneShapeComponentBuildData> ZoneShapeComponentBuildData;` — `UPROPERTY()`

#### struct `FZoneGraphBuilder`  
`struct FZoneGraphBuilder`  
_L64-127_
- reflection: `USTRUCT()`
- L69 _public prototype_ `FZoneGraphBuilder();`
- L70 _public prototype_ `~FZoneGraphBuilder();`
- L72 _public prototype_ `void RegisterZoneShapeComponent(UZoneShapeComponent& ShapeComp);`
- L73 _public prototype_ `void UnregisterZoneShapeComponent(UZoneShapeComponent& ShapeComp);`
- L74 _public prototype_ `void OnZoneShapeComponentChanged(UZoneShapeComponent& ShapeComp);`
- L75 _public function_ `const TArray<FZoneGraphBuilderRegisteredComponent>& GetRegisteredZoneShapeComponents() const`
- L77 _public function_ `bool NeedsRebuild() const`
- L83 _public prototype_ `void BuildAll(const TArray<AZoneGraphData*>& AllZoneGraphData, const bool bForceRebuild);` — Builds zone graph for each zone graph data based on registered shapes. @param AllZoneGraphData All Zone Graph data to update. @param bForceRebuild If set will build graph even if it inputs have not changed.
- L85 _public prototype_ `void FindShapeConnections(const UZoneShapeComponent& SourceShapeComp, TArray<FZoneShapeConnection>& OutShapeConnections) const;`
- L89 _public prototype_ `static void BuildSingleShape(const UZoneShapeComponent& ShapeComp, const FMatrix& LocalToWorld, FZoneGraphStorage& OutZoneStorage);` — Converts single zone shape into a zone storage, used in UI for editing and rendering.
- L95 _public prototype_ `void QueryHashGrid(const FBox& Bounds, TArray<FZoneGraphBuilderHashGrid2D::ItemIDType>& OutResults);` — Returns items that potentially touch the bounds in the HashGrid. Operates on grid level, can have false positives. @param Bounds - Query bounding box. @param OutResults - Result of the query, IDs of potentially overlapping items.
- L98 _protected prototype_ `void Build(AZoneGraphData& ZoneGraphData);`
- L99 _protected prototype_ `void RequestRebuild();`
- L100 _protected prototype_ `void OnLaneProfileChanged(const FZoneLaneProfileRef& ChangedLaneProfileRef);`
- L101 _protected prototype_ `uint32 CalculateCombinedShapeHash(const AZoneGraphData& ZoneGraphData) const;`
- L102 _protected prototype_ `static void AppendShapeToZoneStorage(const UZoneShapeComponent& ShapeComp, const FMatrix& LocalToWorld, FZoneGraphStorage& OutZoneStorage, TArray<FZoneShapeLaneInternalLink>& OutInternalLinks, FZoneGraphBuildData* InBuildData = nullptr);`
- L103 _protected prototype_ `static void ConnectLanes(TArray<FZoneShapeLaneInternalLink>& InternalLinks, FZoneGraphStorage& OutZoneStorage);`
- L106 _protected member_ `TArray<FZoneGraphBuilderRegisteredComponent> ShapeComponents;` — `UPROPERTY(Transient)`
- L109 _protected member_ `TArray<int32> ShapeComponentsFreeList;` — `UPROPERTY(Transient)`
- L112 _protected member_ `TMap<TObjectPtr<UZoneShapeComponent>, int32> ShapeComponentToIndex;` — `UPROPERTY(Transient)`
- L115 _protected member_ `FZoneGraphBuildData BuildData;` — `UPROPERTY(Transient)`
- L118 _protected member_ `FDelegateHandle OnBuildSettingsChangedHandle;`
- L119 _protected member_ `FDelegateHandle OnTagsChangedHandle;`
- L120 _protected member_ `FDelegateHandle OnLaneProfileChangedHandle;`
- L123 _protected member_ `FZoneGraphBuilderHashGrid2D HashGrid;`
- L125 _protected member_ `bool bSkipHashCheck = false;`
- L126 _protected member_ `bool bIsDirty = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ZONEGRAPH_API`
- L16 _typedef_ `typedef THierarchicalHashGrid2D<5, 4> FZoneGraphBuilderHashGrid2D;` — 5 levels of hierarchy, 4 ration between levels (biggest bucket 4^5 = 1024 cells)

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneGraphData.h` (Public)


#### class `AZoneGraphData`  
`class AZoneGraphData : public AActor`  
_L14-77_
- reflection: `UCLASS(MinimalAPI, config = ZoneGraph, defaultconfig, NotBlueprintable)`
- inherits: `AActor`
- L18 _public prototype_ `AZoneGraphData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L21 _public prototype_ `virtual void PostActorCreated() override;`
- L22 _public prototype_ `virtual void PostLoad() override;`
- L23 _public prototype_ `virtual void Destroyed() override;`
- L24 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L25 _public prototype_ `virtual void PreRegisterAllComponents() override;`
- L26 _public prototype_ `virtual void PostUnregisterAllComponents() override;`
- L29 _public prototype_ `virtual void PostEditUndo() override;`
- L30 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L31 _public function_ `virtual bool CanChangeIsSpatiallyLoadedFlag() const override`
- L35 _public function_ `inline bool IsDrawingEnabled() const`
- L36 _public prototype_ `void UpdateDrawing() const;`
- L38 _public function_ `inline bool IsRegistered() const`
- L39 _public prototype_ `void OnRegistered(const FZoneGraphDataHandle DataHandle);`
- L40 _public prototype_ `void OnUnregistered();`
- L43 _public function_ `FZoneGraphStorage& GetStorageMutable()` — TODO: I wonder if the storage is unnecessary indirection?
- L44 _public function_ `const FZoneGraphStorage& GetStorage() const`
- L45 _public function_ `FCriticalSection& GetStorageLock() const`
- L47 _public prototype_ `FBox GetBounds() const;`
- L50 _public function_ `uint32 GetCombinedShapeHash() const` — @return Combined hash of all ZoneShapes that were used to build the data.
- L53 _public function_ `void SetCombinedShapeHash(const uint32 Hash)` — Sets Combined hash of all ZoneShapes that were used to build the data.
- L56 _protected prototype_ `bool RegisterWithSubsystem();`
- L57 _protected prototype_ `bool UnregisterWithSubsystem();`
- L59 _protected member_ `bool bRegistered;`
- L63 _protected member_ `bool bEnableDrawing;` — `UPROPERTY(Transient, EditAnywhere, Category = Display)` — if set to true then this zone graph data will be drawing itself when requested as part of "show navigation"
- L66 _protected member_ `TObjectPtr<UZoneGraphRenderingComponent> RenderingComp;` — `UPROPERTY(transient, duplicatetransient)`
- L69 _protected member_ `FZoneGraphStorage ZoneStorage;` — `UPROPERTY()`
- L72 _protected member_ `mutable FCriticalSection ZoneStorageLock;` — Critical section to prevent rendering of the zone graph storage data while it's getting rebuilt
- L76 _protected member_ `uint32 CombinedShapeHash = 0;` — `UPROPERTY()` — Combined hash of all ZoneShapes that were used to build the data.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ZONEGRAPH_API`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneGraphDelegates.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ZoneGraphDelegates` (scope `UE`)
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnZoneGraphDataBuildDone, const FZoneGraphBuildData& );` — Called when build is completed.
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnZoneGraphDataBuildDone, const FZoneGraphBuildData& );` (scope `UE::ZoneGraphDelegates`) — Called when build is completed.
- L17 _externvar_ `extern FOnZoneGraphDataBuildDone OnZoneGraphDataBuildDone;` (scope `UE::ZoneGraphDelegates`)
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnZoneGraphTagsChanged);` — Called when tags have changed.
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnZoneGraphTagsChanged);` (scope `UE::ZoneGraphDelegates`) — Called when tags have changed.
- L21 _externvar_ `extern FOnZoneGraphTagsChanged OnZoneGraphTagsChanged;` (scope `UE::ZoneGraphDelegates`)
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnZoneGraphLaneProfileChanged, const FZoneLaneProfileRef& );` — Called when name in a lane profile has changed.
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnZoneGraphLaneProfileChanged, const FZoneLaneProfileRef& );` (scope `UE::ZoneGraphDelegates`) — Called when name in a lane profile has changed.
- L25 _externvar_ `extern FOnZoneGraphLaneProfileChanged OnZoneGraphLaneProfileChanged;` (scope `UE::ZoneGraphDelegates`)
- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnZoneGraphBuildSettingsChanged);` — Called when build settings change.
- L28 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnZoneGraphBuildSettingsChanged);` (scope `UE::ZoneGraphDelegates`) — Called when build settings change.
- L29 _externvar_ `extern FOnZoneGraphBuildSettingsChanged OnZoneGraphBuildSettingsChanged;` (scope `UE::ZoneGraphDelegates`)
- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnZoneGraphRequestRebuild);` — Called when rebuild is requested
- L32 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnZoneGraphRequestRebuild);` (scope `UE::ZoneGraphDelegates`) — Called when rebuild is requested
- L33 _externvar_ `extern FOnZoneGraphRequestRebuild OnZoneGraphRequestRebuild;` (scope `UE::ZoneGraphDelegates`)
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnZoneGraphData, const AZoneGraphData* );`
- L36 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnZoneGraphData, const AZoneGraphData* );` (scope `UE::ZoneGraphDelegates`)
- L42 _externvar_ `extern FOnZoneGraphData OnPostZoneGraphDataAdded;` (scope `UE::ZoneGraphDelegates`) — Called when a zone graph gets registered to the zone graph subsystem. It is the listener responsibility to validate that the graph belongs to its associated world if needed.
- L48 _externvar_ `extern FOnZoneGraphData OnPreZoneGraphDataRemoved;` (scope `UE::ZoneGraphDelegates`) — Called when a zone graph gets unregistered from the zone graph subsystem. It is the listener responsibility to validate that the graph belongs to its associated world if needed.

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneGraphObjectCRC32.h` (Public)


#### class `FZoneGraphObjectCRC32`  
`class FZoneGraphObjectCRC32 : public FArchiveObjectCrc32`  
_L17-47_
- inherits: `FArchiveObjectCrc32`
- desc: Archive based object hashing to be used with ZoneGraph data calculation. If a property is has "IncludeInHash" meta tag, any of it's child properties will be included in the hash. Editor only s it relies on meta data.
- L22 _public function_ `bool HasMetaDataInChain(const FProperty* InProperty, FName Key) const` — @return True, if any of the properties in the chain has the Key set
- L41 _public function_ `virtual bool ShouldSkipProperty(const FProperty* InProperty) const override`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneGraphQuery.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ZoneGraph` (scope `UE`)
- L7 _namespace_ `namespace Query` (scope `UE::ZoneGraph`)
- L11 _prototype_ `bool GetLaneLength(const FZoneGraphStorage& Storage, const uint32 LaneIndex, float& OutLength);` (scope `UE::ZoneGraph::Query`) — Returns the length of a specific lane.
- L14 _prototype_ `bool GetLaneLength(const FZoneGraphStorage& Storage, const FZoneGraphLaneHandle LaneHandle, float& OutLength);` (scope `UE::ZoneGraph::Query`) — Returns the length of a specific lane.
- L17 _prototype_ `bool GetLaneWidth(const FZoneGraphStorage& Storage, const uint32 LaneIndex, float& OutWidth);` (scope `UE::ZoneGraph::Query`) — Returns the width of a specific lane.
- L20 _prototype_ `bool GetLaneWidth(const FZoneGraphStorage& Storage, const FZoneGraphLaneHandle LaneHandle, float& OutWidth);` (scope `UE::ZoneGraph::Query`) — Returns the width of a specific lane.
- L23 _prototype_ `bool GetLaneTags(const FZoneGraphStorage& Storage, const FZoneGraphLaneHandle& LaneHandle, FZoneGraphTagMask& OutTags);` (scope `UE::ZoneGraph::Query`) — Returns the tags of a specific lane.
- L26 _prototype_ `bool GetLaneTags(const FZoneGraphStorage& Storage, const uint32 LaneIndex, FZoneGraphTagMask& OutTags);` (scope `UE::ZoneGraph::Query`) — Returns the tags of a specific lane.
- L29 _prototype_ `bool GetLinkedLanes(const FZoneGraphStorage& Storage, const uint32 LaneIndex, const EZoneLaneLinkType Types, const EZoneLaneLinkFlags IncludeFlags, const EZoneLaneLinkFlags ExcludeFlags, TArray<FZoneGraphLinkedLane>& OutLinkedLanes);` (scope `UE::ZoneGraph::Query`) — Returns links to connected lanes of a specific lane. Flags are only used for adjacent lanes.
- L32 _prototype_ `bool GetLinkedLanes(const FZoneGraphStorage& Storage, const FZoneGraphLaneHandle LaneHandle, const EZoneLaneLinkType Types, const EZoneLaneLinkFlags IncludeFlags, const EZoneLaneLinkFlags ExcludeFlags, TArray<FZoneGraphLinkedLane>& OutLinkedLanes);` (scope `UE::ZoneGraph::Query`) — Returns links to connected lanes of a specific lane. Flags are only used for adjacent lanes.
- L35 _prototype_ `bool GetFirstLinkedLane(const FZoneGraphStorage& Storage, const uint32 LaneIndex, const EZoneLaneLinkType Types, const EZoneLaneLinkFlags IncludeFlags, const EZoneLaneLinkFlags ExcludeFlags, FZoneGraphLinkedLane& OutLinkedLane);` (scope `UE::ZoneGraph::Query`) — Returns first link matching the connection and flags. Flags are only used for adjacent lanes..
- L38 _prototype_ `bool GetFirstLinkedLane(const FZoneGraphStorage& Storage, const FZoneGraphLaneHandle LaneHandle, const EZoneLaneLinkType Types, const EZoneLaneLinkFlags IncludeFlags, const EZoneLaneLinkFlags ExcludeFlags, FZoneGraphLinkedLane& OutLinkedLane);` (scope `UE::ZoneGraph::Query`) — Returns first link matching the connection and flags. Flags are only used for adjacent lanes.
- L41 _prototype_ `bool AdvanceLaneLocation(const FZoneGraphStorage& Storage, const FZoneGraphLaneLocation& InLaneLocation, const float AdvanceDistance, FZoneGraphLaneLocation& OutLaneLocation);` (scope `UE::ZoneGraph::Query`) — Moves LaneLocation along a lane.
- L44 _prototype_ `bool AdvanceLaneLocation(const FZoneGraphStorage& Storage, const FZoneGraphLaneLocation& InLaneLocation, const float AdvanceDistance, TArray<FZoneGraphLaneLocation>& OutLaneLocations);` (scope `UE::ZoneGraph::Query`) — Moves LaneLocation along a lane and provides list of locations containing all segments start location along the way and final interpolated location.
- L47 _prototype_ `bool CalculateLocationAlongLane(const FZoneGraphStorage& Storage, const uint32 LaneIndex, const float Distance, FZoneGraphLaneLocation& OutLaneLocation);` (scope `UE::ZoneGraph::Query`) — Returns location at a distance along a specific lane.
- L50 _prototype_ `bool CalculateLocationAlongLane(const FZoneGraphStorage& Storage, const FZoneGraphLaneHandle LaneHandle, const float Distance, FZoneGraphLaneLocation& OutLaneLocation);` (scope `UE::ZoneGraph::Query`) — Returns location at a distance along a specific lane.
- L53 _prototype_ `bool CalculateLocationAlongLaneFromRatio(const FZoneGraphStorage& Storage, const uint32 LaneIndex, const float Ratio, FZoneGraphLaneLocation& OutLaneLocation);` (scope `UE::ZoneGraph::Query`) — Returns location at a given lane lenght ratio [0..1] along a specific lane.
- L56 _prototype_ `bool CalculateLocationAlongLaneFromRatio(const FZoneGraphStorage& Storage, const FZoneGraphLaneHandle LaneHandle, const float Ratio, FZoneGraphLaneLocation& OutLaneLocation);` (scope `UE::ZoneGraph::Query`) — Returns location at a given lane lenght ratio [0..1] along a specific lane.
- L59 _prototype_ `bool CalculateLaneSegmentIndexAtDistance(const FZoneGraphStorage& Storage, const uint32 LaneIndex, const float Distance, int32& OutSegmentIndex);` (scope `UE::ZoneGraph::Query`) — Returns segment index at distance along a specific lane.
- L62 _prototype_ `bool CalculateLaneSegmentIndexAtDistance(const FZoneGraphStorage& Storage, const FZoneGraphLaneHandle LaneHandle, const float Distance, int32& OutSegmentIndex);` (scope `UE::ZoneGraph::Query`) — Returns segment index at distance along a specific lane.
- L65 _prototype_ `bool FindNearestLocationOnLane(const FZoneGraphStorage& Storage, const FZoneGraphLaneHandle LaneHandle, const FBox& Bounds, FZoneGraphLaneLocation& OutLaneLocation, float& OutDistanceSqr);` (scope `UE::ZoneGraph::Query`) — Find nearest location on a specific lane.
- L68 _prototype_ `bool FindNearestLocationOnLane(const FZoneGraphStorage& Storage, const FZoneGraphLaneHandle LaneHandle, const FVector& Center, const float Range, FZoneGraphLaneLocation& OutLaneLocation, float& OutDistanceSqr);` (scope `UE::ZoneGraph::Query`) — Find nearest location on a specific lane.
- L71 _prototype_ `bool FindNearestLane(const FZoneGraphStorage& Storage, const FBox& Bounds, const FZoneGraphTagFilter TagFilter, FZoneGraphLaneLocation& OutLaneLocation, float& OutDistanceSqr);` (scope `UE::ZoneGraph::Query`) — Finds nearest lane in ZoneGraph Storage.
- L74 _prototype_ `bool FindOverlappingLanes(const FZoneGraphStorage& Storage, const FBox& Bounds, const FZoneGraphTagFilter TagFilter, TArray<FZoneGraphLaneHandle>& OutLanes);` (scope `UE::ZoneGraph::Query`) — Finds overlapping lanes in ZoneGraph Storage.
- L77 _prototype_ `bool FindLaneOverlaps(const FZoneGraphStorage& Storage, const FVector& Center, const float Radius, const FZoneGraphTagFilter TagFilter, TArray<FZoneGraphLaneSection>& OutLaneSections);` (scope `UE::ZoneGraph::Query`) — Find sections of lanes fully overlapping (including lane width) in ZoneGraph Storage.

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneGraphRenderingComponent.h` (Public)


#### class `FZoneGraphSceneProxy`  
`class FZoneGraphSceneProxy : public FDebugRenderSceneProxy`  
_L17-59_
- inherits: `FDebugRenderSceneProxy`
- desc: exported to API for GameplayDebugger module
- L20 _public prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L22 _public prototype_ `FZoneGraphSceneProxy(const UPrimitiveComponent& InComponent, const AZoneGraphData& ZoneGraph);`
- L23 _public prototype_ `virtual ~FZoneGraphSceneProxy();`
- L25 _public prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;`
- L40 _public prototype_ `static FDrawDistances GetDrawDistances(const float MinDrawDistance, const float MaxDrawDistance);`
- L41 _public prototype_ `static FZoneVisibility CalculateZoneVisibility(const FDrawDistances& Distances, const FVector Origin, const FVector Position);`
- L42 _public prototype_ `static bool ShouldRenderZoneGraph(const FSceneView& View);`
- L46 _protected prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L48 _protected function_ `virtual uint32 GetMemoryFootprint(void) const override`
- L50 _protected function_ `uint32 GetAllocatedSize(void) const`
- L57 _private member_ `TWeakObjectPtr<UZoneGraphRenderingComponent> WeakRenderingComponent;`
- L58 _private member_ `bool bSkipDistanceCheck;`

#### struct `FZoneGraphSceneProxy::FZoneVisibility`  
`struct FZoneVisibility`  
_L27-32_
- L29 _public member_ `bool bVisible = false;`
- L30 _public member_ `bool bDetailsVisible = false;`
- L31 _public member_ `float Alpha = 1.0f;`

#### struct `FZoneGraphSceneProxy::FDrawDistances`  
`struct FDrawDistances`  
_L33-39_
- L35 _public member_ `float MinDrawDistanceSqr = 0.f;`
- L36 _public member_ `float MaxDrawDistanceSqr = FLT_MAX;`
- L37 _public member_ `float FadeDrawDistanceSqr = FLT_MAX;`
- L38 _public member_ `float DetailDrawDistanceSqr = FLT_MAX;`

#### class `UZoneGraphRenderingComponent`  
`class UZoneGraphRenderingComponent : public UPrimitiveComponent`  
_L62-96_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object, editinlinenew)`
- inherits: `UPrimitiveComponent`
- L67 _public prototype_ `UZoneGraphRenderingComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L70 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L71 _public prototype_ `virtual void OnRegister() override;`
- L72 _public prototype_ `virtual void OnUnregister() override;`
- L76 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L79 _public function_ `void ForceUpdate()`
- L80 _public function_ `bool IsForcingUpdate() const`
- L82 _public prototype_ `static bool IsNavigationShowFlagSet(const UWorld* World);`
- L86 _protected prototype_ `void CheckDrawFlagTimerFunction();`
- L90 _protected member_ `FDelegateHandle DebugTextDrawingDelegateHandle;`
- L93 _protected member_ `bool bPreviousShowNavigation;`
- L94 _protected member_ `bool bForceUpdate;`
- L95 _protected member_ `FTimerHandle TimerHandle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ZONEGRAPH_API`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneGraphRenderingUtilities.h` (Public)


#### struct `UE::ZoneGraph::RenderingUtilities::FLaneHighlight`  
`struct FLaneHighlight`  
_L14-21_
- L16 _public function_ `bool IsValid() const`
- L18 _public member_ `FVector Position = FVector::ZeroVector;`
- L19 _public member_ `FQuat Rotation = FQuat::Identity;`
- L20 _public member_ `float Width = 0.0f;`

#### struct `UE::ZoneGraph::RenderingUtilities::FZoneDrawAnnotator`  
`struct FZoneDrawAnnotator`  
_L23-28_
- L25 _public member_ `TOptional<FZoneGraphTagMask> VisualizedTagsOverride;`
- L26 _public member_ `TOptional<FZoneGraphTagMask> ZoneTagsOverride;`
- L27 _public member_ `TOptional<TFunctionRef<FZoneGraphTagMask(int32 LaneIndex, const FZoneLaneData& Lane)>> GetLaneTagsOverride;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ZoneGraph` (scope `UE`)
- L11 _namespace_ `namespace RenderingUtilities` (scope `UE::ZoneGraph`)
- L30 _prototype_ `FColor GetTagMaskColor(const FZoneGraphTagMask TagMask, TConstArrayView<FZoneGraphTagInfo> TagInfo);` (scope `UE::ZoneGraph::RenderingUtilities`)
- L31 _prototype_ `void DrawZoneBoundary(const FZoneGraphStorage& ZoneStorage, int32 ZoneIndex, FPrimitiveDrawInterface* PDI, const FMatrix& LocalToWorld, const float LineThickness, const float DepthBias, const float Alpha, const FZoneDrawAnnotator& Annotator = { });` (scope `UE::ZoneGraph::RenderingUtilities`)
- L32 _prototype_ `void DrawLane(const FZoneGraphStorage& ZoneStorage, FPrimitiveDrawInterface* PDI, const FZoneGraphLaneHandle& LaneHandle, const FColor Color, const float LineThickness = 5.f, const FVector& Offset = FVector::ZeroVector);` (scope `UE::ZoneGraph::RenderingUtilities`)
- L33 _prototype_ `void DrawLane(const FZoneGraphStorage& ZoneStorage, FPrimitiveDrawInterface* PDI, const FZoneGraphLaneLocation& InStartLocation, const FZoneGraphLaneLocation& InEndLocation, const FColor Color, const float LineThickness = 5.f, const FVector& Offset = FVector::ZeroVector);` (scope `UE::ZoneGraph::RenderingUtilities`)
- L34 _prototype_ `void DrawLanes(const FZoneGraphStorage& ZoneStorage, FPrimitiveDrawInterface* PDI, const TArray<FZoneGraphLaneHandle>& Lanes, const FColor Color, const float LineThickness = 5.f, const FVector& Offset = FVector::ZeroVector);` (scope `UE::ZoneGraph::RenderingUtilities`)
- L35 _prototype_ `void DrawLinkedLanes(const FZoneGraphStorage& ZoneStorage, FPrimitiveDrawInterface* PDI, const FZoneGraphLaneHandle& SourceLaneHandle, const TArray<FZoneGraphLinkedLane>& LinkedLanes, const float LineThickness = 5.f);` (scope `UE::ZoneGraph::RenderingUtilities`)
- L36 _prototype_ `void DrawLanePath(const FZoneGraphStorage& ZoneStorage, FPrimitiveDrawInterface* PDI, const FZoneGraphLanePath& LanePath, const FColor Color, const float LineThickness = 5.f);` (scope `UE::ZoneGraph::RenderingUtilities`)
- L37 _prototype_ `void DrawZoneLanes(const FZoneGraphStorage& ZoneStorage, int32 ZoneIndex, FPrimitiveDrawInterface* PDI, const FMatrix& LocalToWorld, const float LineThickness, const float DepthBias, const float Alpha, const bool bDrawDetails = true, const FLaneHighlight& LaneHighlight = FLaneHighlight(), const FZoneDrawAnnotator& Annotator = { });` (scope `UE::ZoneGraph::RenderingUtilities`)
- L39 _prototype_ `void DrawZoneShapeConnector(const FZoneShapeConnector& Connector, const FZoneShapeConnection* Connection, FPrimitiveDrawInterface* PDI, const FMatrix& LocalToWorld, const float DepthBias);` (scope `UE::ZoneGraph::RenderingUtilities`)
- L40 _prototype_ `void DrawZoneShapeConnectors(TConstArrayView<FZoneShapeConnector> Connectors, TConstArrayView<FZoneShapeConnection> Connections, FPrimitiveDrawInterface* PDI, const FMatrix& LocalToWorld, const float DepthBias);` (scope `UE::ZoneGraph::RenderingUtilities`)
- L42 _prototype_ `void DrawLaneDirections(const FZoneGraphStorage& ZoneStorage, FPrimitiveDrawInterface* PDI, const FZoneGraphLaneHandle LaneHandle, const FColor Color);` (scope `UE::ZoneGraph::RenderingUtilities`)
- L43 _prototype_ `void DrawLaneSmoothing(const FZoneGraphStorage& ZoneStorage, FPrimitiveDrawInterface* PDI, const FZoneGraphLaneHandle LaneHandle, const FColor Color);` (scope `UE::ZoneGraph::RenderingUtilities`)
- L45 _prototype_ `void AppendLane(FDebugRenderSceneProxy* DebugProxy, const FZoneGraphStorage& ZoneStorage, const FZoneGraphLaneHandle& LaneHandle, const FColor Color, const float LineThickness = 5.f, const FVector& Offset = FVector::ZeroVector);` (scope `UE::ZoneGraph::RenderingUtilities`)
- L46 _prototype_ `void AppendLane(FDebugRenderSceneProxy* DebugProxy, const FZoneGraphStorage& ZoneStorage, const FZoneGraphLaneLocation& InStartLocation, const FZoneGraphLaneLocation& InEndLocation, const FColor Color, const float LineThickness = 5.f, const FVector& Offset = FVector::ZeroVector);` (scope `UE::ZoneGraph::RenderingUtilities`)
- L47 _prototype_ `void AppendLaneSection(FDebugRenderSceneProxy* DebugProxy, const FZoneGraphStorage& ZoneStorage, const FZoneGraphLaneSection& Section, const FColor Color, const float LineThickness = 5.f, const FVector& Offset = FVector::ZeroVector);` (scope `UE::ZoneGraph::RenderingUtilities`)

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneGraphSettings.h` (Public)


#### class `UZoneGraphSettings`  
`class UZoneGraphSettings : public UDeveloperSettings`  
_L19-75_
- reflection: `UCLASS(MinimalAPI, config = Plugins, defaultconfig, DisplayName = "Zone Graph")`
- inherits: `UDeveloperSettings`
- desc: Implements the settings for the ZoneGraph plugin.
- L23 _public prototype_ `UZoneGraphSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L25 _public function_ `const TArray<FZoneLaneProfile>& GetLaneProfiles() const`
- L27 _public prototype_ `const FZoneLaneProfile* GetLaneProfileByRef(const FZoneLaneProfileRef& LaneProfileRef) const;`
- L28 _public prototype_ `const FZoneLaneProfile* GetLaneProfileByID(const FGuid& ID) const;`
- L31 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L33 _public prototype_ `const FZoneLaneProfile* GetDefaultLaneProfile() const;`
- L36 _public prototype_ `TConstArrayView<FZoneGraphTagInfo> GetTagInfos() const;`
- L37 _public prototype_ `void GetValidTagInfos(TArray<FZoneGraphTagInfo>& OutInfos) const;`
- L39 _public function_ `FZoneGraphTagMask GetVisualizedTags() const`
- L41 _public function_ `const FZoneGraphBuildSettings& GetBuildSettings() const`
- L43 _public function_ `float GetShapeMaxDrawDistance() const`
- L45 _public function_ `bool ShouldBuildZoneGraphWhileEditing() const`
- L51 _public prototype_ `uint32 GetBuildHash() const;` — Calculates hash values from all build settings Can be used to determine if the settings have changed between builds. Use property meta tag "ExcludeFromHash" to exclude non build related properties. @return Hash value of all build related settings.
- L56 _protected member_ `TArray<FZoneLaneProfile> LaneProfiles;` — `UPROPERTY(EditAnywhere, config, Category = ZoneGraph, meta = (IncludeInHash))`
- L59 _protected member_ `FZoneGraphTagInfo Tags[static_cast<int32>(EZoneGraphTags::MaxTags)];` — `UPROPERTY(EditAnywhere, config, Category = ZoneGraph)`
- L63 _protected member_ `FZoneGraphTagMask VisualizedTags = FZoneGraphTagMask::All;` — `UPROPERTY(EditAnywhere, config, Category = ZoneGraph)` — Tags which affect visualization (i.e. color of lanes).
- L67 _protected member_ `float ShapeMaxDrawDistance = 20000.0f;` — `UPROPERTY(EditAnywhere, config, Category = ZoneGraph)` — Max draw distance for shapes visualization.
- L70 _protected member_ `FZoneGraphBuildSettings BuildSettings;` — `UPROPERTY(EditAnywhere, config, Category = ZoneGraph, meta = (IncludeInHash))`
- L74 _protected member_ `bool bBuildZoneGraphWhileEditing = false;` — `UPROPERTY(EditAnywhere, config, Category = ZoneGraph)` — When set to true ZoneGraph will build as it is being edited.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ZONEGRAPH_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ZoneGraph` (scope `UE`)
- L9 _namespace_ `namespace Helpers` (scope `UE::ZoneGraph`)
- L11 _prototype_ `FName GetTagName(const FZoneGraphTag Tag);` (scope `UE::ZoneGraph::Helpers`)
- L12 _prototype_ `FString GetTagMaskString(const FZoneGraphTagMask TagMask, const TCHAR* Separator);` (scope `UE::ZoneGraph::Helpers`)

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneGraphSubsystem.h` (Public)


#### struct `FRegisteredZoneGraphData`  
`struct FRegisteredZoneGraphData`  
_L20-36_
- reflection: `USTRUCT()`
- desc: Struct representing registered ZoneGraph data in the subsystem.
- L24 _public function_ `void Reset(int32 InGeneration = 1)`
- L32 _public member_ `TObjectPtr<AZoneGraphData> ZoneGraphData = nullptr;` — `UPROPERTY()`
- L34 _public member_ `int32 Generation = 1;` — Starting at generation 1 so that 0 can be invalid.
- L35 _public member_ `bool bInUse = false;` — Extra bit indicating that the data is in meant to be in use. This tried to capture the case where ZoneGraphData might get nullified without notifying.

#### class `UZoneGraphSubsystem`  
`class UZoneGraphSubsystem : public UTickableWorldSubsystem`  
_L40-165_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTickableWorldSubsystem`
- L44 _public prototype_ `UZoneGraphSubsystem();`
- L46 _public prototype_ `FZoneGraphDataHandle RegisterZoneGraphData(AZoneGraphData& InZoneGraphData);`
- L47 _public prototype_ `void UnregisterZoneGraphData(AZoneGraphData& InZoneGraphData);`
- L48 _public function_ `TConstArrayView<FRegisteredZoneGraphData> GetRegisteredZoneGraphData() const`
- L51 _public function_ `FZoneGraphBuilder& GetBuilder()`
- L57 _public prototype_ `const AZoneGraphData* GetZoneGraphData(const FZoneGraphDataHandle DataHandle) const;` — Returns Zone Graph data associated with specified handle.
- L60 _public function_ `const FZoneGraphStorage* GetZoneGraphStorage(const FZoneGraphDataHandle DataHandle) const` — Returns Zone Graph data storage associated with specified handle, or nullptr if not found.
- L73 _public prototype_ `bool FindNearestLane(const FBox& QueryBounds, const FZoneGraphTagFilter TagFilter, FZoneGraphLaneLocation& OutLaneLocation, float& OutDistanceSqr) const;` — Find nearest lane that touches the query bounds. Finds results from all registered ZoneGraph data.
- L76 _public prototype_ `bool FindOverlappingLanes(const FBox& QueryBounds, const FZoneGraphTagFilter TagFilter, TArray<FZoneGraphLaneHandle>& OutLanes) const;` — Find overlapping lanes that touches the query bounds. Finds results from all registered ZoneGraph data.
- L79 _public prototype_ `bool FindLaneOverlaps(const FVector& Center, const float Radius, const FZoneGraphTagFilter TagFilter, TArray<FZoneGraphLaneSection>& OutLaneSections) const;` — Find sections of lanes fully overlapping (including lane width). Finds results from all registered ZoneGraph data.
- L82 _public prototype_ `bool AdvanceLaneLocation(const FZoneGraphLaneLocation& InLaneLocation, const float AdvanceDistance, FZoneGraphLaneLocation& OutLaneLocation) const;` — Moves LaneLocation along a lane.
- L85 _public prototype_ `bool CalculateLocationAlongLane(const FZoneGraphLaneHandle LaneHandle, const float Distance, FZoneGraphLaneLocation& OutLaneLocation) const;` — Returns point at a distance along a specific lane.
- L88 _public prototype_ `bool FindNearestLocationOnLane(const FZoneGraphLaneHandle LaneHandle, const FBox& Bounds, FZoneGraphLaneLocation& OutLaneLocation, float& OutDistanceSqr) const;` — Find nearest location on a specific lane.
- L91 _public prototype_ `bool FindNearestLocationOnLane(const FZoneGraphLaneHandle LaneHandle, const FVector& Center, const float Range, FZoneGraphLaneLocation& OutLaneLocation, float& OutDistanceSqr) const;` — Find nearest location on a specific lane.
- L94 _public prototype_ `bool IsLaneValid(const FZoneGraphLaneHandle LaneHandle) const;` — returns true if lane handle is valid.
- L97 _public prototype_ `bool GetLaneLength(const FZoneGraphLaneHandle LaneHandle, float& OutLength) const;` — Returns the length of a specific lane.
- L100 _public prototype_ `bool GetLaneWidth(const FZoneGraphLaneHandle LaneHandle, float& OutWidth) const;` — Returns the width of a specific lane.
- L103 _public prototype_ `bool GetLaneTags(const FZoneGraphLaneHandle LaneHandle, FZoneGraphTagMask& OutTags) const;` — Returns the Tags of a specific lane.
- L106 _public prototype_ `bool GetLinkedLanes(const FZoneGraphLaneHandle LaneHandle, const EZoneLaneLinkType Types, const EZoneLaneLinkFlags IncludeFlags, const EZoneLaneLinkFlags ExcludeFlags, TArray<FZoneGraphLinkedLane>& OutLinkedLanes) const;` — Returns all links to connected lanes of a specific lane.
- L109 _public prototype_ `bool GetFirstLinkedLane(const FZoneGraphLaneHandle LaneHandle, const EZoneLaneLinkType Types, const EZoneLaneLinkFlags IncludeFlags, const EZoneLaneLinkFlags ExcludeFlags, FZoneGraphLinkedLane& OutLinkedLane) const;` — Returns handle to first linked lane matching the connection type and flags.
- L112 _public prototype_ `FBox GetCombinedBounds() const;` — Returns bounds of all ZoneGraph data.
- L117 _public prototype_ `FZoneGraphTag GetTagByName(FName TagName) const;` — Returns tag based on name.
- L120 _public prototype_ `FName GetTagName(FZoneGraphTag Tag) const;` — Returns the name of a specific tag.
- L123 _public prototype_ `const FZoneGraphTagInfo* GetTagInfo(FZoneGraphTag Tag) const;` — Returns info about a specific tag.
- L126 _public prototype_ `TConstArrayView<FZoneGraphTagInfo> GetTagInfos() const;` — Returns all tag infos
- L129 _public function_ `virtual bool IsTickableInEditor() const override`
- L133 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L134 _protected prototype_ `virtual void PostInitialize() override;`
- L135 _protected prototype_ `virtual void Deinitialize() override;`
- L136 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L137 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L139 _protected prototype_ `void RemoveRegisteredDataItem(const int32 Index);`
- L140 _protected prototype_ `void UnregisterStaleZoneGraphDataInstances();`
- L141 _protected prototype_ `void RegisterZoneGraphDataInstances();`
- L143 _protected prototype_ `void OnActorMoved(AActor* Actor);`
- L144 _protected prototype_ `void OnRequestRebuild();`
- L145 _protected prototype_ `void SpawnMissingZoneGraphData();`
- L149 _protected prototype_ `void RebuildGraph(const bool bForceRebuild = false);` — Rebuilds the graph. @param bForceRebuild Settings this flag will force rebuild even if the data may be up to date.
- L152 _protected member_ `FCriticalSection DataRegistrationSection;`
- L155 _protected member_ `TArray<FRegisteredZoneGraphData> RegisteredZoneGraphData;` — `UPROPERTY()`
- L156 _protected member_ `TArray<int32> ZoneGraphDataFreeList;`
- L158 _protected member_ `bool bInitialized;`
- L161 _protected member_ `FDelegateHandle OnActorMovedHandle;`
- L162 _protected member_ `FDelegateHandle OnRequestRebuildHandle;`
- L163 _protected member_ `FZoneGraphBuilder Builder;`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UZoneGraphSubsystem> final`  
_L168-175_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L171-174_

#### Free symbols / members of external scopes

- L172 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon67fc89350103`)
- L173 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon67fc89350103`)

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneGraphTypes.h` (Public)


#### struct `FZoneHandle`  
`struct FZoneHandle`  
_L15-36_
- reflection: `USTRUCT()`
- L19 _public member_ `static const FZoneHandle Invalid;`
- L21 _public prototype_ `FZoneHandle() = default;`
- L22 _public function_ `explicit FZoneHandle(uint32 InIndex) : Index(InIndex)`
- L24 _public function_ `bool IsValid() const`
- L26 _public function_ `bool operator==(const FZoneHandle& RHS) const`
- L27 _public function_ `bool operator!=(const FZoneHandle& RHS) const`
- L29 _public function_ `uint32 GetIndex() const`
- L32 _private member_ `static const uint32 InvalidIndex = uint32(-1);`
- L35 _private member_ `uint32 Index = InvalidIndex;` — `UPROPERTY()`

#### enum `EZoneGraphTags`  
`enum class EZoneGraphTags`  
_L39-43_
- reflection: `UENUM()`
- L41 _public enumerator_ `MaxTags = 32`
- L42 _public enumerator_ `MaxTagIndex = MaxTags - 1`

#### struct `FZoneGraphTag`  
`struct FZoneGraphTag`  
_L46-103_
- reflection: `USTRUCT(BlueprintType)`
- L50 _public member_ `static const FZoneGraphTag None;`
- L52 _public prototype_ `FZoneGraphTag() = default;`
- L54 _public function_ `explicit FZoneGraphTag(const uint8 InBit) : Bit(InBit)`
- L60 _public function_ `void Set(const uint8 InBit)`
- L66 _public function_ `uint8 Get() const`
- L71 _public function_ `void Reset()`
- L76 _public function_ `bool IsValid() const`
- L81 _public function_ `bool operator==(const FZoneGraphTag& RHS) const`
- L86 _public function_ `bool operator!=(const FZoneGraphTag& RHS) const`
- L99 _private member_ `static const uint8 NoneValue;`
- L102 _private member_ `uint8 Bit = NoneValue;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))`

#### enum `EZoneLaneTagMaskComparison`  
`enum class EZoneLaneTagMaskComparison : uint8`  
_L106-111_
- reflection: `UENUM(BlueprintType)`
- L108 _public enumerator_ `Any` — Does masks share ANY tags.
- L109 _public enumerator_ `All` — Does masks share ALL tags.
- L110 _public enumerator_ `Not` — Does NOT masks share any tags.

#### struct `FZoneGraphTagMask`  
`struct FZoneGraphTagMask`  
_L114-201_
- reflection: `USTRUCT(BlueprintType)`
- L118 _public member_ `static const FZoneGraphTagMask All;`
- L119 _public member_ `static const FZoneGraphTagMask None;`
- L121 _public prototype_ `FZoneGraphTagMask() = default;`
- L122 _public function_ `FZoneGraphTagMask(const FZoneGraphTag InTag) : Mask(InTag.IsValid() ? uint32(1) << InTag.Bit : 0)`
- L123 _public function_ `explicit FZoneGraphTagMask(uint32 InMask) : Mask(InMask)`
- L125 _public function_ `void Add(const FZoneGraphTagMask InTags)`
- L130 _public function_ `void Add(const FZoneGraphTag InTag)`
- L138 _public function_ `void Remove(const FZoneGraphTagMask InTags)`
- L143 _public function_ `void Remove(const FZoneGraphTag InTag)`
- L151 _public function_ `bool ContainsAny(const FZoneGraphTagMask InTags) const`
- L156 _public function_ `bool ContainsAll(const FZoneGraphTagMask InTags) const`
- L161 _public function_ `bool Contains(const FZoneGraphTag InTag) const`
- L166 _public function_ `bool CompareMasks(const FZoneGraphTagMask InTags, const EZoneLaneTagMaskComparison Operand) const`
- L182 _public function_ `uint32 GetValue() const`
- L184 _public function_ `bool operator==(const FZoneGraphTagMask& RHS) const`
- L185 _public function_ `bool operator!=(const FZoneGraphTagMask& RHS) const`
- L200 _private member_ `uint32 Mask = 0;` — `UPROPERTY(Category = Zone, EditAnywhere)`

#### struct `FZoneGraphTagFilter`  
`struct FZoneGraphTagFilter`  
_L206-228_
- reflection: `USTRUCT()`
- desc: Filter passes if any of the 'AnyTags', and all of the 'AllTags', and none of the 'NotTags' are present. Setting include or exclude tags to None, will skip that particular check.
- L210 _public function_ `bool Pass(const FZoneGraphTagMask Tags) const`
- L217 _public function_ `bool operator==(const FZoneGraphTagFilter& RHS) const`
- L218 _public function_ `bool operator!=(const FZoneGraphTagFilter& RHS) const`
- L221 _public member_ `FZoneGraphTagMask AnyTags = FZoneGraphTagMask::None;` — `UPROPERTY(Category = Zone, EditAnywhere)`
- L224 _public member_ `FZoneGraphTagMask AllTags = FZoneGraphTagMask::None;` — `UPROPERTY(Category = Zone, EditAnywhere)`
- L227 _public member_ `FZoneGraphTagMask NotTags = FZoneGraphTagMask::None;` — `UPROPERTY(Category = Zone, EditAnywhere)`

#### struct `FZoneGraphTagInfo`  
`struct FZoneGraphTagInfo`  
_L231-245_
- reflection: `USTRUCT()`
- L235 _public function_ `bool IsValid() const`
- L238 _public member_ `FName Name;` — `UPROPERTY(Category = Zone, EditAnywhere)`
- L241 _public member_ `FColor Color = FColor(ForceInit);` — `UPROPERTY(Category = Zone, EditAnywhere)`
- L244 _public member_ `FZoneGraphTag Tag;` — `UPROPERTY(Category = Zone, EditAnywhere)`

#### enum `EZoneLaneDirection`  
`enum class EZoneLaneDirection : uint8`  
_L248-253_
- reflection: `UENUM(BlueprintType)`
- L250 _public enumerator_ `None = 0x0` — No movement, this lane is treated as spacer or median.
- L251 _public enumerator_ `Forward = 0x1` — Move forward relative to the markup.
- L252 _public enumerator_ `Backward = 0x2` — Move backward relative to the markup.

#### struct `FZoneLaneDesc`  
`struct FZoneLaneDesc`  
_L257-274_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes single lane.
- L263 _public member_ `float Width = 150.0f;` — `UPROPERTY(Category = Lane, EditAnywhere, BlueprintReadOnly)` — Width of the lane
- L267 _public member_ `EZoneLaneDirection Direction = EZoneLaneDirection::Forward;` — `UPROPERTY(Category = Lane, EditAnywhere, BlueprintReadOnly)` — Direction of the lane
- L271 _public member_ `FZoneGraphTagMask Tags = FZoneGraphTagMask(1);` — `UPROPERTY(Category = Lane, EditAnywhere, BlueprintReadOnly)` — Lane tags
- L273 _public prototype_ `bool operator==(const FZoneLaneDesc& Other) const;`

#### struct `FZoneLaneProfile`  
`struct FZoneLaneProfile`  
_L278-312_
- reflection: `USTRUCT()`
- desc: Describes template of multiple parallel lanes, created in settings.
- L282 _public function_ `FZoneLaneProfile() : ID(FGuid::NewGuid())`
- L288 _public function_ `float GetLanesTotalWidth() const` — Gets combined total with of all lanes.
- L299 _public prototype_ `bool IsSymmetrical() const;` — Returns true of the profile is symmetrical.
- L302 _public prototype_ `void ReverseLanes();` — Reverses the lane profile. The lanes array will be reversed, as well as the lane directions.
- L305 _public member_ `FName Name;` — `UPROPERTY(Category = Lane, EditAnywhere)`
- L308 _public member_ `FGuid ID;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`
- L311 _public member_ `TArray<FZoneLaneDesc> Lanes;` — `UPROPERTY(Category = Lane, EditAnywhere)`

#### struct `FZoneLaneProfileRef`  
`struct FZoneLaneProfileRef`  
_L316-345_
- reflection: `USTRUCT(BlueprintType)`
- desc: Reference to a lane profile.
- L320 _public function_ `FZoneLaneProfileRef()`
- L324 _public function_ `FZoneLaneProfileRef(const FZoneLaneProfile& LaneProfile)`
- L330 _public function_ `bool Equals(const FZoneLaneProfile& LaneProfile) const`
- L335 _public function_ `bool operator==(const FZoneLaneProfileRef& RHS) const`
- L341 _public member_ `FName Name;` — `UPROPERTY(Category = Lane, EditAnywhere, BlueprintReadWrite)`
- L344 _public member_ `FGuid ID;` — `UPROPERTY(Category = Lane, EditAnywhere, BlueprintReadWrite)`

#### enum `EZoneLaneLinkType`  
`enum class EZoneLaneLinkType : uint8`  
_L350-357_
- reflection: `UENUM()`
- desc: Describes how the linked lane relates to the lane spatially. Each type is a bitmask, so that some APIs can filter based on link types.
- L352 _public enumerator_ `None = 0`
- L353 _public enumerator_ `All = MAX_uint8`
- L354 _public enumerator_ `Outgoing = 1 << 0` — The lane is connected at the end of the current lane and going out.
- L355 _public enumerator_ `Incoming = 1 << 1` — The lane is connected at the beginning of the current lane and coming in.
- L356 _public enumerator_ `Adjacent = 1 << 2` — The lane is in same zone, immediately adjacent to the current lane, can be opposite direction or not, see EZoneLaneLinkFlags

#### enum `EZoneLaneLinkFlags`  
`enum class EZoneLaneLinkFlags : uint8`  
_L363-372_
- reflection: `UENUM()`
- desc: Flags describing the details of a linked adjacent lane. Flags are only used for adjacent lanes.
- L365 _public enumerator_ `None = 0`
- L366 _public enumerator_ `All = MAX_uint8`
- L367 _public enumerator_ `Left = 1 << 0` — Left of the current lane
- L368 _public enumerator_ `Right = 1 << 1` — Right of the current lane
- L369 _public enumerator_ `Splitting = 1 << 2` — Splitting from current lane at start
- L370 _public enumerator_ `Merging = 1 << 3` — Merging into the current lane at end
- L371 _public enumerator_ `OppositeDirection = 1 << 4` — Opposition direction than current lane

#### struct `FZoneLaneLinkData`  
`struct FZoneLaneLinkData`  
_L376-398_
- reflection: `USTRUCT()`
- L380 _public prototype_ `FZoneLaneLinkData() = default;`
- L381 _public function_ `FZoneLaneLinkData(const int32 InDestLaneIndex, const EZoneLaneLinkType InType, const EZoneLaneLinkFlags InFlags) : DestLaneIndex(InDestLaneIndex), Type(InType), Flags((uint8)InFlags)`
- L383 _public function_ `bool HasFlags(const EZoneLaneLinkFlags InFlags) const`
- L384 _public function_ `EZoneLaneLinkFlags GetFlags() const`
- L385 _public function_ `void SetFlags(const EZoneLaneLinkFlags InFlags)`
- L389 _public member_ `int32 DestLaneIndex = 0;` — `UPROPERTY()` — Index to destination lane in FZoneGraphStorage::Lanes.
- L393 _public member_ `EZoneLaneLinkType Type = EZoneLaneLinkType::None;` — `UPROPERTY()` — Type of the connection.
- L397 _public member_ `uint8 Flags = 0;` — `UPROPERTY()` — Specifics about the connection type, see EZoneLaneLinkFlags.

#### struct `FZoneLaneData`  
`struct FZoneLaneData`  
_L402-445_
- reflection: `USTRUCT()`
- desc: TODO: We could replace *End with *Num, and use uint16. Begin probably needs to be int32/uint32
- L406 _public function_ `int32 GetLinkCount() const`
- L407 _public function_ `int32 GetNumPoints() const`
- L408 _public function_ `int32 GetLastPoint() const`
- L412 _public member_ `float Width = 0.0f;` — `UPROPERTY()` — Width of the lane
- L416 _public member_ `FZoneGraphTagMask Tags = FZoneGraphTagMask(1);` — `UPROPERTY()` — Lane tags
- L420 _public member_ `int32 PointsBegin = 0;` — `UPROPERTY()` — First point of the lane polyline in FZoneGraphStorage::LanePoints.
- L424 _public member_ `int32 PointsEnd = 0;` — `UPROPERTY()` — One past the last point of the lane polyline.
- L428 _public member_ `int32 LinksBegin = 0;` — `UPROPERTY()` — First link in FZoneGraphStorage::LaneLinks.
- L432 _public member_ `int32 LinksEnd = 0;` — `UPROPERTY()` — One past the last lane link.
- L436 _public member_ `int32 ZoneIndex = 0;` — `UPROPERTY()` — Index of the zone this lane belongs to.
- L440 _public member_ `uint16 StartEntryId = 0;` — `UPROPERTY()` — Source data entry ID, this generally corresponds to input data point index.
- L444 _public member_ `uint16 EndEntryId = 0;` — `UPROPERTY()` — Source data entry ID.

#### struct `FZoneData`  
`struct FZoneData`  
_L448-477_
- reflection: `USTRUCT()`
- L452 _public function_ `int32 GetLaneCount() const`
- L456 _public member_ `int32 BoundaryPointsBegin = 0;` — `UPROPERTY()` — First point of the zone boundary polyline in FZoneGraphStorage::BoundaryPoints.
- L460 _public member_ `int32 BoundaryPointsEnd = 0;` — `UPROPERTY()` — One past the last point of the zone boundary polyline.
- L464 _public member_ `int32 LanesBegin = 0;` — `UPROPERTY()` — First lane of the zone in FZoneGraphStorage::Lanes.
- L468 _public member_ `int32 LanesEnd = 0;` — `UPROPERTY()` — One past the last lane.
- L472 _public member_ `FBox Bounds = FBox(ForceInit);` — `UPROPERTY()` — Bounding box of the zone
- L476 _public member_ `FZoneGraphTagMask Tags = FZoneGraphTagMask(1);` — `UPROPERTY()` — Zone tags

#### struct `FZoneGraphDataHandle`  
`struct FZoneGraphDataHandle`  
_L480-517_
- reflection: `USTRUCT()`
- L484 _public member_ `static const uint16 InvalidGeneration;` — 0
- L486 _public prototype_ `FZoneGraphDataHandle() = default;`
- L487 _public function_ `FZoneGraphDataHandle(const uint16 InIndex, const uint16 InGeneration) : Index(InIndex), Generation(InGeneration)`
- L490 _public member_ `uint16 Index = 0;` — `UPROPERTY(Transient)`
- L493 _public member_ `uint16 Generation = 0;` — `UPROPERTY(Transient)`
- L495 _public function_ `bool operator==(const FZoneGraphDataHandle& Other) const`
- L500 _public function_ `bool operator!=(const FZoneGraphDataHandle& Other) const`
- L510 _public function_ `void Reset()`
- L516 _public function_ `bool IsValid() const` — Any index is valid, but Generation = 0 means invalid.

#### struct `FZoneGraphLaneHandle`  
`struct FZoneGraphLaneHandle`  
_L520-557_
- reflection: `USTRUCT()`
- L524 _public prototype_ `FZoneGraphLaneHandle() = default;`
- L525 _public function_ `FZoneGraphLaneHandle(const int32 InLaneIndex, const FZoneGraphDataHandle InDataHandle) : Index(InLaneIndex), DataHandle(InDataHandle)`
- L528 _public member_ `int32 Index = INDEX_NONE;` — `UPROPERTY(Transient)`
- L531 _public member_ `FZoneGraphDataHandle DataHandle;` — `UPROPERTY(Transient)`
- L533 _public function_ `bool operator==(const FZoneGraphLaneHandle& Other) const`
- L538 _public function_ `bool operator!=(const FZoneGraphLaneHandle& Other) const`
- L548 _public function_ `void Reset()`
- L554 _public function_ `FString ToString() const`
- L556 _public function_ `bool IsValid() const`

#### struct `FZoneGraphLaneLocation`  
`struct FZoneGraphLaneLocation`  
_L560-597_
- reflection: `USTRUCT()`
- L565 _public member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY(Transient)`
- L568 _public member_ `FVector Direction = FVector::ForwardVector;` — `UPROPERTY(Transient)`
- L571 _public member_ `FVector Tangent = FVector::ForwardVector;` — `UPROPERTY(Transient)`
- L574 _public member_ `FVector Up = FVector::UpVector;` — `UPROPERTY(Transient)`
- L577 _public member_ `FZoneGraphLaneHandle LaneHandle;` — `UPROPERTY(Transient)`
- L580 _public member_ `int32 LaneSegment = 0;` — `UPROPERTY(Transient)`
- L583 _public member_ `float DistanceAlongLane = 0.0f;` — `UPROPERTY(Transient)`
- L585 _public function_ `void Reset()`
- L596 _public function_ `bool IsValid() const`

#### struct `FZoneGraphCompactLaneLocation`  
`struct FZoneGraphCompactLaneLocation`  
_L601-614_
- reflection: `USTRUCT()`
- desc: Minimal amount of data to search and compare lane location.
- L605 _public prototype_ `FZoneGraphCompactLaneLocation() = default;`
- L606 _public function_ `FZoneGraphCompactLaneLocation(const FZoneGraphLaneLocation& Location) : LaneHandle(Location.LaneHandle), DistanceAlongLane(Location.DistanceAlongLane)`
- L607 _public function_ `FZoneGraphCompactLaneLocation(const FZoneGraphLaneHandle Handle, const float Distance) : LaneHandle(Handle), DistanceAlongLane(Distance)`
- L610 _public member_ `FZoneGraphLaneHandle LaneHandle;` — `UPROPERTY(Transient)`
- L613 _public member_ `float DistanceAlongLane = 0.0f;` — `UPROPERTY(Transient)`

#### struct `FZoneGraphLaneSection`  
`struct FZoneGraphLaneSection`  
_L618-635_
- reflection: `USTRUCT()`
- desc: Section of a lane
- L622 _public function_ `bool operator==(const FZoneGraphLaneSection& Other) const`
- L628 _public member_ `FZoneGraphLaneHandle LaneHandle;` — `UPROPERTY(Transient)`
- L631 _public member_ `float StartDistanceAlongLane = 0.0f;` — `UPROPERTY(Transient)`
- L634 _public member_ `float EndDistanceAlongLane = 0.0f;` — `UPROPERTY(Transient)`

#### struct `FZoneGraphLinkedLane`  
`struct FZoneGraphLinkedLane`  
_L639-670_
- reflection: `USTRUCT()`
- desc: Linked lane, used for query results. See also: FZoneLaneLinkData
- L643 _public prototype_ `FZoneGraphLinkedLane() = default;`
- L644 _public function_ `FZoneGraphLinkedLane(const FZoneGraphLaneHandle InDestLane, const EZoneLaneLinkType InType, const EZoneLaneLinkFlags InFlags) : DestLane(InDestLane), Type(InType), Flags((uint8)InFlags)`
- L646 _public function_ `void Reset()`
- L653 _public function_ `bool IsValid() const`
- L655 _public function_ `bool HasFlags(const EZoneLaneLinkFlags InFlags) const`
- L656 _public function_ `EZoneLaneLinkFlags GetFlags() const`
- L657 _public function_ `void SetFlags(const EZoneLaneLinkFlags InFlags)`
- L661 _public member_ `FZoneGraphLaneHandle DestLane = {};` — `UPROPERTY()` — Destination lane handle
- L665 _public member_ `EZoneLaneLinkType Type = EZoneLaneLinkType::None;` — `UPROPERTY()` — Type of the connection.
- L669 _public member_ `uint8 Flags = 0;` — `UPROPERTY()` — Specifics about the connection type, see EZoneLaneLinkFlags.

#### struct `FZoneGraphLanePath`  
`struct FZoneGraphLanePath`  
_L672-689_
- L674 _public member_ `FZoneGraphLaneLocation StartLaneLocation;`
- L675 _public member_ `FZoneGraphLaneLocation EndLaneLocation;`
- L676 _public member_ `TArray<FZoneGraphLaneHandle> Lanes;`
- L678 _public function_ `void Reset(const TArray<FZoneGraphLaneHandle>::SizeType NewSize = 0)`
- L685 _public function_ `void Add(const FZoneGraphLaneHandle& LaneHandle)`

#### struct `FZoneGraphStorage`  
`struct FZoneGraphStorage`  
_L692-741_
- reflection: `USTRUCT()`
- L696 _public prototype_ `void Reset();`
- L697 _public function_ `const FZoneData& GetZoneDataFromLaneIndex(int32 LaneIndex) const`
- L701 _public member_ `TArray<FZoneData> Zones;` — `UPROPERTY()` — All the zones.
- L705 _public member_ `TArray<FZoneLaneData> Lanes;` — `UPROPERTY()` — All the lanes, referred by zones.
- L709 _public member_ `TArray<FVector> BoundaryPoints;` — `UPROPERTY()` — All the zone boundary points, referred by zones.
- L713 _public member_ `TArray<FVector> LanePoints;` — `UPROPERTY()` — All the lane points, referred by lanes.
- L717 _public member_ `TArray<FVector> LaneUpVectors;` — `UPROPERTY()` — All the lane up vectors, referred by lanes.
- L721 _public member_ `TArray<FVector> LaneTangentVectors;` — `UPROPERTY()` — All the lane tangent vectors, referred by lanes.
- L725 _public member_ `TArray<float> LanePointProgressions;` — `UPROPERTY()` — All the lane progression distances, referred by lanes.
- L729 _public member_ `TArray<FZoneLaneLinkData> LaneLinks;` — `UPROPERTY()` — All the lane links, referred by lanes.
- L733 _public member_ `FBox Bounds = FBox(ForceInit);` — `UPROPERTY()` — Bounding box of all zones.
- L737 _public member_ `FZoneGraphBVTree ZoneBVTree;` — `UPROPERTY()` — BV-Tree of Zones
- L740 _public member_ `FZoneGraphDataHandle DataHandle;` — The handle that this storage represents, updated when data is registered to ZoneGraphSubsystem, used for query results.

#### enum `FZoneShapeType`  
`enum class FZoneShapeType : uint8`  
_L745-749_
- reflection: `UENUM(BlueprintType)`
- L747 _public enumerator_ `Spline` — Bezier spline shape
- L748 _public enumerator_ `Polygon` — Bezier polygon shape

#### enum `EZoneShapePolygonRoutingType`  
`enum class EZoneShapePolygonRoutingType : uint8`  
_L752-756_
- reflection: `UENUM(BlueprintType)`
- L754 _public enumerator_ `Bezier` — Use bezier curves for routing.
- L755 _public enumerator_ `Arcs` — Use arcs for lane routing.

#### enum `EZoneShapeLaneConnectionRestrictions`  
`enum class EZoneShapeLaneConnectionRestrictions : uint8`  
_L759-766_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L761 _public enumerator_ `None = 0 UMETA(Hidden)`
- L762 _public enumerator_ `NoLeftTurn = 1 << 0` — No left turning destinations allowed.
- L763 _public enumerator_ `NoRightTurn = 1 << 1` — No right turning destinations allowed.
- L764 _public enumerator_ `OneLanePerDestination = 1 << 2` — Connect to only one nearest lane per destination.
- L765 _public enumerator_ `MergeLanesToOneDestinationLane = 1 << 3` — Connect all the incoming lanes to one destination lane.

#### enum `FZoneShapePointType`  
`enum class FZoneShapePointType : uint8`  
_L770-776_
- reflection: `UENUM(BlueprintType)`
- L772 _public enumerator_ `Sharp` — Sharp corner
- L773 _public enumerator_ `Bezier` — Round corner, defined by manual bezier handles
- L774 _public enumerator_ `AutoBezier` — Round corner, defined by automatic bezier handles
- L775 _public enumerator_ `LaneProfile` — Lane profile corner, length is defined by lane profile.

#### struct `FZoneShapePoint`  
`struct FZoneShapePoint`  
_L779-859_
- reflection: `USTRUCT(BlueprintType)`
- L783 _public member_ `static const uint8 InheritLaneProfile;`
- L785 _public function_ `FZoneShapePoint() : Type(FZoneShapePointType::Sharp), LaneProfile(InheritLaneProfile)`
- L786 _public function_ `FZoneShapePoint(const FVector& InPosition) : Position(InPosition), Type(FZoneShapePointType::Sharp), LaneProfile(InheritLaneProfile)`
- L789 _public prototype_ `FVector GetInControlPoint() const;` — Returns incoming Bezier control point. Adjust rotation.
- L792 _public prototype_ `FVector GetOutControlPoint() const;` — Returns outgoing Bezier control point. Adjust rotation.
- L795 _public prototype_ `void SetInControlPoint(const FVector& InPoint);` — Sets incoming Bezier control point. Adjust rotation.
- L798 _public prototype_ `void SetOutControlPoint(const FVector& InPoint);` — Sets outgoing Bezier control point. Adjust rotation.
- L801 _public prototype_ `FVector GetLaneProfileLeft() const;` — Returns left edge of lane profile control point (similar relation as outgoing control point). Adjust rotation.
- L804 _public prototype_ `FVector GetLaneProfileRight() const;` — Returns right edge of lane profile control point (similar relation as incoming control point). Adjust rotation.
- L807 _public prototype_ `void SetLaneProfileLeft(const FVector& InPoint);` — Sets left edge of lane profile control point.
- L810 _public prototype_ `void SetLaneProfileRight(const FVector& InPoint);` — Returns right edge of lane profile control point. Adjust rotation.
- L813 _public prototype_ `void SetRotationFromForwardAndUp(const FVector& Forward, const FVector& Up);` — Sets rotation pitch/yaw to match Forward direction, and then uses Up direction to find roll angle.
- L815 _public function_ `void SetLaneConnectionRestrictions(const EZoneShapeLaneConnectionRestrictions Restrictions)`
- L816 _public function_ `EZoneShapeLaneConnectionRestrictions GetLaneConnectionRestrictions() const`
- L820 _public member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite)` — Position of the point
- L824 _public member_ `FVector InControlPoint_DEPRECATED = FVector::ZeroVector;` — `UPROPERTY()` — Incoming control point
- L828 _public member_ `FVector OutControlPoint_DEPRECATED = FVector::ZeroVector;` — `UPROPERTY()` — Outgoing control point
- L832 _public member_ `float TangentLength = 0.0f;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite)` — Length of the Bezier point tangents, or cached half-width of the lane profile.
- L836 _public member_ `float InnerTurnRadius = 100.0f;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite)` — Inner turn radius associated with this point. Used when polygon shape routing is set to 'Arcs'.
- L841 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite)` — Rotation of the point. Forward direction of the rotation matches the tangents. For Lane Profile points, the forward directions points into the shape so that we can match the incoming lanes rotation.
- L845 _public member_ `FZoneShapePointType Type = FZoneShapePointType::Sharp;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite)` — Type of the control point
- L850 _public member_ `uint8 LaneProfile = InheritLaneProfile;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite)` — Index to external array referring to Lane Profile, or FZoneShapePoint::InheritLaneProfile if we should use Shape's lane profile. This is a little awkward indirection, but keeps the point memory usage in check.
- L854 _public member_ `bool bReverseLaneProfile = false;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite)` — True of lane profile should be reversed.
- L858 _public member_ `int32 LaneConnectionRestrictions = 0;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "/Script/ZoneGraph.EZoneShapeLaneConnectionRestrictions"))` — Lane connection restrictions

#### struct `FZoneShapeConnector`  
`struct FZoneShapeConnector`  
_L863-894_
- reflection: `USTRUCT()`
- desc: Shape connectors represent locations where shapes can be connected together.
- L869 _public member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY()` — Position of the connector.
- L873 _public member_ `FVector Normal = FVector::ForwardVector;` — `UPROPERTY()` — Normal direction of the connector.
- L877 _public member_ `FVector Up = FVector::UpVector;` — `UPROPERTY()` — Up direction of the connector.
- L881 _public member_ `int32 PointIndex = 0;` — `UPROPERTY()` — Point index of UZoneShapeComponent.
- L885 _public member_ `FZoneLaneProfileRef LaneProfile;` — `UPROPERTY()` — Lane template of the connector.
- L889 _public member_ `bool bReverseLaneProfile = false;` — `UPROPERTY()` — True if lane profile should be treated as reversed.
- L893 _public member_ `FZoneShapeType ShapeType = FZoneShapeType::Spline;` — `UPROPERTY()` — Which type of shape the connector belongs to.

#### struct `FZoneShapeConnection`  
`struct FZoneShapeConnection`  
_L898-909_
- reflection: `USTRUCT()`
- desc: Connection between two shape connectors.
- L904 _public member_ `TWeakObjectPtr<class UZoneShapeComponent> ShapeComponent = nullptr;` — `UPROPERTY()` — Connected shape.
- L908 _public member_ `int32 ConnectorIndex = 0;` — `UPROPERTY()` — Connector index at the connected shape.

#### struct `FZoneGraphTessellationSettings`  
`struct FZoneGraphTessellationSettings`  
_L913-924_
- reflection: `USTRUCT()`
- L919 _public member_ `FZoneGraphTagFilter LaneFilter;` — `UPROPERTY(Category = Zone, EditAnywhere)` — Lanes to apply this tolerance
- L923 _public member_ `float TessellationTolerance = 1.0f;` — `UPROPERTY(Category = Zone, EditAnywhere)` — Tessellation tolerance, the error between tessellated point and the spline.

#### enum `EZoneGraphLaneRoutingCountRule`  
`enum class EZoneGraphLaneRoutingCountRule : uint8`  
_L927-932_
- reflection: `UENUM(BlueprintType)`
- L929 _public enumerator_ `Any` — Any number of entries
- L930 _public enumerator_ `One` — Just one entry
- L931 _public enumerator_ `Many` — Many entries

#### struct `FZoneGraphLaneRoutingRule`  
`struct FZoneGraphLaneRoutingRule`  
_L935-962_
- reflection: `USTRUCT()`
- L940 _public member_ `bool bEnabled = true;` — `UPROPERTY(Category = Rule, EditAnywhere)`
- L943 _public member_ `FString Comment;` — `UPROPERTY(Category = Rule, EditAnywhere)`
- L946 _public member_ `FZoneGraphTagFilter ZoneTagFilter;` — `UPROPERTY(Category = Rule, EditAnywhere)`
- L949 _public member_ `FZoneLaneProfileRef SourceLaneProfile;` — `UPROPERTY(Category = Rule, EditAnywhere)`
- L952 _public member_ `FZoneLaneProfileRef DestinationLaneProfile;` — `UPROPERTY(Category = Rule, EditAnywhere)`
- L955 _public member_ `EZoneGraphLaneRoutingCountRule SourceOutgoingConnections = EZoneGraphLaneRoutingCountRule::Any;` — `UPROPERTY(Category = Rule, EditAnywhere)`
- L958 _public member_ `EZoneGraphLaneRoutingCountRule DestinationIncomingConnections = EZoneGraphLaneRoutingCountRule::Any;` — `UPROPERTY(Category = Rule, EditAnywhere)`
- L961 _public member_ `int32 ConnectionRestrictions = 0;` — `UPROPERTY(Category = Rule, EditAnywhere, meta = (Bitmask, BitmaskEnum = "/Script/ZoneGraph.EZoneShapeLaneConnectionRestrictions"))`

#### struct `FZoneGraphBuildSettings`  
`struct FZoneGraphBuildSettings`  
_L965-1024_
- reflection: `USTRUCT()`
- L970 _public prototype_ `float GetLaneTessellationTolerance(const FZoneGraphTagMask LaneTags) const;` — @return tessellation tolerance for specific case, or common tolerance if no match.
- L973 _public prototype_ `EZoneShapeLaneConnectionRestrictions GetConnectionRestrictions(const FZoneGraphTagMask ZoneTags, const FZoneLaneProfileRef& SourceLaneProfile, const int32 SourceConnectionCount, const FZoneLaneProfileRef& DestinationLaneProfile, const int32 DestinationConnectionCount) const;` — @return Connection restrictions for specified lane based on PolygonRoutingRules
- L979 _public member_ `float CommonTessellationTolerance = 1.0f;` — `UPROPERTY(Category = Lanes, EditAnywhere)` — Common tolerance for all lane tessellation, the error between tessellated point and the spline.
- L983 _public member_ `TArray<FZoneGraphTessellationSettings> SpecificTessellationTolerances;` — `UPROPERTY(Category = Lanes, EditAnywhere)` — Custom tessellation tolerances based on lane tags, first match is returned.
- L987 _public member_ `float LaneConnectionAngle = 120.0f;` — `UPROPERTY(Category = Lanes, EditAnywhere)` — Max relative angle (in degrees) between two lane profiles for them to be connected with lanes. In degrees.
- L991 _public member_ `FZoneGraphTagMask LaneConnectionMask = FZoneGraphTagMask::All;` — `UPROPERTY(Category = Lanes, EditAnywhere)` — Mask of tags which should be used to check if lanes should connect.
- L995 _public member_ `float TurnThresholdAngle = 5.0f;` — `UPROPERTY(Category = Lanes, EditAnywhere)` — When the relative angle (in degrees) to destination on a polygon is more than the specified angle, it is considered left or right turn.
- L999 _public member_ `TArray<FZoneGraphLaneRoutingRule> PolygonRoutingRules;` — `UPROPERTY(Category = Lanes, EditAnywhere)` — Routing rules applied to polygon shapes
- L1003 _public member_ `float ConnectionSnapDistance = 25.0f;` — `UPROPERTY(Category = PointSnapping, EditAnywhere)` — Max distance between two shape points for them to be snapped together.
- L1007 _public member_ `float ConnectionSnapAngle = 10.0f;` — `UPROPERTY(Category = PointSnapping, EditAnywhere)` — Max relative angle (in degrees) between two shape points for them to be snapped together.
- L1011 _public member_ `double DragEndpointAutoConnectRange = 250.0;` — `UPROPERTY(Category = PointSnapping, EditAnywhere)` — Max distance to auto connect a dragged end control point to the closest connector when released.
- L1015 _public member_ `double DragEndpointAutoIntersectionRange = 250.0;` — `UPROPERTY(Category = PointSnapping, EditAnywhere)` — Max distance to automatically create an intersection with a dragged end control point and the overlapping zone shape when released.
- L1019 _public member_ `double SnapAutoIntersectionToClosestPointTolerance = 100.0;` — `UPROPERTY(Category = PointSnapping, EditAnywhere)` — If the location to create auto intersection is closer than the tolerance to a spline point, use the spline point instead of nearest point on spline to create the intersection.
- L1023 _public member_ `bool bShow3DRadiusForAutoConnectionAndIntersection = false;` — `UPROPERTY(Category = PointSnapping, EditAnywhere)` — If true, draws a sphere for the auto connection/interseciont area. Otherwise, draws a circle.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ZONEGRAPH_API`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogZoneGraph, Warning, All);`
- L91 _function_ `friend uint32 GetTypeHash(const FZoneGraphTag& Tag)`
- L187 _function_ `friend uint32 GetTypeHash(const FZoneGraphTagMask& ZoneGraphTagMask)`
- L192 _function_ `friend FZoneGraphTagMask operator&(const FZoneGraphTagMask& LHS, const FZoneGraphTagMask& RHS)`
- L193 _function_ `friend FZoneGraphTagMask operator|(const FZoneGraphTagMask& LHS, const FZoneGraphTagMask& RHS)`
- L194 _function_ `friend FZoneGraphTagMask operator~(const FZoneGraphTagMask& InMask)`
- L505 _function_ `friend uint32 GetTypeHash(const FZoneGraphDataHandle& Handle)`
- L543 _function_ `friend uint32 GetTypeHash(const FZoneGraphLaneHandle& Handle)`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneShapeActor.h` (Public)


#### class `AZoneShape`  
`class AZoneShape : public AActor`  
_L14-32_
- reflection: `UCLASS(MinimalAPI, hidecategories = (Input))`
- inherits: `AActor`
- desc: Zone Shape actor for standalone zone markup.
- L18 _public prototype_ `AZoneShape(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L20 _public function_ `virtual bool IsEditorOnly() const override`
- L22 _public function_ `const UZoneShapeComponent* GetShape() const`
- L25 _public function_ `virtual bool CanChangeIsSpatiallyLoadedFlag() const override`
- L31 _protected member_ `TObjectPtr<UZoneShapeComponent> ShapeComponent;` — `UPROPERTY(Category = Zone, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ZONEGRAPH_API`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneShapeComponent.h` (Public)


#### struct `FZoneShapeCustomVersion`  
`struct FZoneShapeCustomVersion`  
_L16-35_
- desc: Custom serialization version for ZoneShapeComponent
- L31 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L34 _private function_ `FZoneShapeCustomVersion()`

#### enum `FZoneShapeCustomVersion::Type`  
`enum Type`  
_L18-28_
- L21 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L23 _public enumerator_ `AddedRoll` — Added roll to points.
- L26 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L27 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### class `UZoneShapeComponent`  
`class UZoneShapeComponent : public UPrimitiveComponent`  
_L39-231_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Custom, BlueprintType, ShowCategories = (Mobility), HideCategories = (Physics, Collision, Lighting, Rendering, Mobile), meta = (BlueprintSpawnableComponent))`
- inherits: `UPrimitiveComponent`
- L43 _public prototype_ `UZoneShapeComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L45 _public function_ `virtual bool IsEditorOnly() const override`
- L47 _public prototype_ `virtual void OnRegister() override;`
- L48 _public prototype_ `virtual void OnUnregister() override;`
- L50 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L51 _public prototype_ `virtual void PostLoad() override;`
- L53 _public prototype_ `DECLARE_EVENT(UZoneShapeComponent, FOnShapeDataChanged);`
- L54 _public function_ `FOnShapeDataChanged& OnShapeDataChanged()`
- L56 _public prototype_ `virtual void PostEditImport() override;`
- L57 _public prototype_ `virtual void PostEditUndo() override;`
- L58 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L60 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L64 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L69 _public prototype_ `void UpdateShape();` — Updates shape, calculates auto tangents, and adjusts lane points to match the lane templates, updates connectors and connections.
- L72 _public prototype_ `void UpdateShapeConnectors();` — Updates shape connectors from the points.
- L75 _public prototype_ `void UpdateConnectedShapes();` — Updates how shape connectors are connected to other shapes.
- L78 _public prototype_ `void UpdateMatingConnectedShapes();` — Updates how shape connectors are connected to other shapes. In case a connection is found, the mating shape is updated too.
- L83 _public prototype_ `void UpdatePointRotationAndTangent(int32 PointIndex);` — Calculates rotation and tangent for a specific point. @param PointIndex index of the point to update
- L86 _public prototype_ `bool IsShapeClosed() const;` — Returns true if the shape is closed form.
- L92 _public prototype_ `int32 AddUniquePerPointLaneProfile(const FZoneLaneProfileRef& NewLaneProfileRef);` — Adds new one if one does not exists @param NewLaneProfileRef New profile to add. @return index to the lane profile, or INDEX_NONE if new lane template could not be added.
- L95 _public prototype_ `void CompactPerPointLaneProfiles();` — Removes unused items from the per point lane template array.
- L98 _public prototype_ `void ClearPerPointLaneProfiles();` — Removes per point lane templates.
- L101 _public prototype_ `void GetSplineLaneProfile(FZoneLaneProfile& OutLaneProfile) const;` — @return The shape template used for the spline shape.
- L104 _public prototype_ `void GetPolygonLaneProfiles(TArray<FZoneLaneProfile>& OutLaneProfiles) const;` — @return Lane template for each point in the polygon shape.
- L107 _public function_ `const FZoneLaneProfileRef& GetCommonLaneProfile()` — @return Lane profile which is used for spline lanes, and polygon points which are set to Inherit.
- L112 _public function_ `void SetCommonLaneProfile(const FZoneLaneProfileRef& LaneProfileRef)` — Sets lane profile which is used for spline lanes, and polygon points which are set to Inherit. @param LaneProfileRef New lane profile.
- L115 _public function_ `int32 GetNumPoints() const` — @return Number of points in the shape.
- L118 _public function_ `int32 GetNumSegments() const` — @return Number of segments in the shape.
- L121 _public function_ `TConstArrayView<FZoneShapePoint> GetPoints() const` — @return View to the points array.
- L124 _public function_ `TArray<FZoneShapePoint>& GetMutablePoints()` — @return Mutable reference to the points array.
- L127 _public function_ `TConstArrayView<FZoneLaneProfileRef> GetPerPointLaneProfiles() const` — @return lane templates referred by points.
- L130 _public function_ `TConstArrayView<FZoneShapeConnector> GetShapeConnectors() const` — @return View to shape connectors array.
- L133 _public function_ `TConstArrayView<FZoneShapeConnection> GetConnectedShapes() const` — @return View to connected shapes.
- L136 _public prototype_ `const FZoneShapeConnector* GetShapeConnectorByPointIndex(int32 PointIndex) const;` — @return Connector at the given point.
- L140 _public function_ `FZoneShapeType GetShapeType() const` — `UFUNCTION(Category = Zone, BlueprintPure)` — @return Shape type.
- L146 _public function_ `void SetShapeType(FZoneShapeType Type)` — `UFUNCTION(Category = Zone, BlueprintCallable)` — Sets shape type. @param Type New shape type.
- L150 _public function_ `FZoneGraphTagMask GetTags() const` — `UFUNCTION(Category = Zone, BlueprintPure)` — @return Shape's tags.
- L153 _public function_ `FZoneGraphTagMask& GetMutableTags()` — @return Tags that can be changed.
- L159 _public function_ `void SetTags(const FZoneGraphTagMask NewTags)` — `UFUNCTION(Category = Zone, BlueprintCallable)` — Sets shape tags. @param NewTags New tags to set.
- L163 _public function_ `bool IsLaneProfileReversed() const` — `UFUNCTION(Category = Zone, BlueprintPure)` — @return True if common lane profile is reversed.
- L170 _public function_ `bool SetReverseLaneProfile(bool bReverse)` — `UFUNCTION(Category = Zone, BlueprintCallable)` — Set whether common lane profile should be reversed. @param bReverse Reverse state @return Newly set reversed state.
- L173 _public function_ `EZoneShapePolygonRoutingType GetPolygonRoutingType() const` — @return Polygon routing type
- L177 _public function_ `void SetPolygonRoutingType(const EZoneShapePolygonRoutingType NewType)` — `UFUNCTION(Category = Zone, BlueprintCallable)` — Sets the polygon routing type.
- L181 _public prototype_ `uint32 GetShapeHash() const;` — @return Hash value of the shape data. Can be used to determine if the shape has changed.
- L188 _private member_ `FZoneLaneProfileRef LaneProfile;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true", IncludeInHash))` — Common lane template for whole shape
- L192 _private member_ `bool bReverseLaneProfile = false;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", IncludeInHash))` — True if lane profile should be reversed
- L196 _private member_ `TArray<FZoneLaneProfileRef> PerPointLaneProfiles;` — `UPROPERTY(Category = Zone, VisibleAnywhere, meta = (IncludeInHash, EditCondition = "false", EditConditionHides))` — Array of lane templates indexed by the points when the shape is polygon.
- L200 _private member_ `TArray<FZoneShapePoint> Points;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", IncludeInHash))` — Shape points
- L204 _private member_ `FZoneShapeType ShapeType;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", IncludeInHash))` — Shape type, spline or polygon
- L208 _private member_ `EZoneShapePolygonRoutingType PolygonRoutingType = EZoneShapePolygonRoutingType::Bezier;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", IncludeInHash, EditCondition = "ShapeType == FZoneShapeType::Polygon"))` — Polygon shape routing type
- L212 _private member_ `FZoneGraphTagMask Tags;` — `UPROPERTY(Category = Zone, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", IncludeInHash))` — Zone tags, the lanes inherit zone tags.
- L216 _private member_ `TArray<FZoneShapeConnector> ShapeConnectors;` — `UPROPERTY(Transient)` — Connectors for other shapes (not stored, these are refreshed from points).
- L220 _private member_ `TArray<FZoneShapeConnection> ConnectedShapes;` — `UPROPERTY(Transient)` — Array of connections matching ShapeConnectors (not stored, these are refreshed from connectors).
- L223 _private prototype_ `void OnLaneProfileChanged(const FZoneLaneProfileRef& ChangedLaneProfileRef);`
- L225 _private member_ `FDelegateHandle OnLaneProfileChangedHandle;`
- L229 _private member_ `FOnShapeDataChanged ShapeDataChangedEvent;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ZONEGRAPH_API`
- L53 _delegate_ `DECLARE_EVENT(UZoneShapeComponent, FOnShapeDataChanged);`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneShapeUtilities.h` (Public)


#### struct `FZoneShapeLaneInternalLink`  
`struct FZoneShapeLaneInternalLink`  
_L10-26_
- reflection: `USTRUCT()`
- desc: Struct describing a link for a specified lane, used during building
- L14 _public prototype_ `FZoneShapeLaneInternalLink() = default;`
- L15 _public function_ `FZoneShapeLaneInternalLink(const int32 InLaneIdex, const FZoneLaneLinkData InLinkData) : LaneIndex(InLaneIdex), LinkData(InLinkData)`
- L17 _public function_ `bool operator<(const FZoneShapeLaneInternalLink& RHS) const`
- L21 _public member_ `int32 LaneIndex = 0;` — `UPROPERTY()` — Lane index to which the link belongs to
- L25 _public member_ `FZoneLaneLinkData LinkData = {};` — `UPROPERTY()` — Link details

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace ZoneShape` (scope `UE`)
- L28 _namespace_ `namespace Utilities` (scope `UE::ZoneShape`)
- L32 _prototype_ `void TessellateSplineShape(TConstArrayView<FZoneShapePoint> Points, const FZoneLaneProfile& LaneProfile, const FZoneGraphTagMask ZoneTags, const FMatrix& LocalToWorld, FZoneGraphStorage& OutZoneStorage, TArray<FZoneShapeLaneInternalLink>& OutInternalLinks);` (scope `UE::ZoneShape::Utilities`) — Converts spline shape to a zone data.
- L36 _prototype_ `void TessellatePolygonShape(TConstArrayView<FZoneShapePoint> Points, const EZoneShapePolygonRoutingType RoutingType, TConstArrayView<FZoneLaneProfile> LaneProfiles, const FZoneGraphTagMask ZoneTags, const FMatrix& LocalToWorld, FZoneGraphStorage& OutZoneStorage, TArray<FZoneShapeLaneInternalLink>& OutInternalLinks);` (scope `UE::ZoneShape::Utilities`) — Converts polygon shape to a zone data.
- L40 _prototype_ `void GetCubicBezierPointsFromShapeSegment(const FZoneShapePoint& StartShapePoint, const FZoneShapePoint& EndShapePoint, const FMatrix& LocalToWorld, FVector& OutStartPoint, FVector& OutStartControlPoint, FVector& OutEndControlPoint, FVector& OutEndPoint);` (scope `UE::ZoneShape::Utilities`) — Returns cubic bezier points for give shape segment. Adjusts end points based on shape point types.
