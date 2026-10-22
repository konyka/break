# Plugins / GameplayGraph

- module root: `Plugins/Experimental/GameplayGraph/Source/GameplayGraph`
- headers: 10; symbols: 339
- symbol kinds: class=12, delegate=11, enum=4, enumerator=16, function=104, macro=5, member=50, namespace=4, prototype=102, struct=16, typedef=15
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Experimental/GameplayGraph/Source/GameplayGraph/Public/Graph/Algorithms/Connectivity/ConnectedComponents.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Graph`
- L8 _namespace_ `namespace Algorithms` (scope `Graph`)
- L15 _prototype_ `TArray<TSet<FGraphVertexHandle>> FindConnectedComponents(const TSet<FGraphVertexHandle>& StartingSet);` (scope `Graph::Algorithms`) — Given a set of nodes, returns an array of connected components. Note that any nodes that may be otherwise connected to the input nodes will be ignored for the output if they are not in the input set.

### `Plugins/Experimental/GameplayGraph/Source/GameplayGraph/Public/Graph/Algorithms/Search/Search.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Graph`
- L6 _namespace_ `namespace Algorithms` (scope `Graph`)
- L9 _typedef_ `using FSearchCallback = TFunction<bool(const FGraphVertexHandle&)>;` (scope `Graph::Algorithms`) — Returns whether we've found what we've wanted to find (i.e. returning true will end the search).
- L11 _prototype_ `FGraphVertexHandle BFS(const FGraphVertexHandle& Start, FSearchCallback Callback);` (scope `Graph::Algorithms`)
- L12 _prototype_ `FGraphVertexHandle DFS(const FGraphVertexHandle& Start, FSearchCallback Callback);` (scope `Graph::Algorithms`)

### `Plugins/Experimental/GameplayGraph/Source/GameplayGraph/Public/Graph/Graph.h` (Public)


#### struct `FGraphProperties`  
`struct FGraphProperties`  
_L22-34_
- reflection: `USTRUCT()`
- L26 _public prototype_ `FGraphProperties() = default;`
- L29 _public member_ `bool bGenerateIslands = true;` — `UPROPERTY(SaveGame)`

#### struct `FEdgeSpecifier`  
`struct FEdgeSpecifier`  
_L41-64_
- desc: Undirected edge descriptor. Always VertexHandle1 <= VertexHandle2.
- L43 _public prototype_ `FEdgeSpecifier(const FGraphVertexHandle& InVertexHandle1, const FGraphVertexHandle& InVertexHandle2);`
- L44 _public prototype_ `FEdgeSpecifier(const FEdgeSpecifier&) = default;`
- L45 _public prototype_ `FEdgeSpecifier(FEdgeSpecifier&&) = default;`
- L46 _public prototype_ `FEdgeSpecifier& operator=(const FEdgeSpecifier&) = default;`
- L47 _public prototype_ `FEdgeSpecifier& operator=(FEdgeSpecifier&&) = default;`
- L58 _public function_ `const FGraphVertexHandle& GetVertexHandle1() const`
- L59 _public function_ `const FGraphVertexHandle& GetVertexHandle2() const`
- L62 _private member_ `FGraphVertexHandle VertexHandle1;`
- L63 _private member_ `FGraphVertexHandle VertexHandle2;`
- L197 _function_ `inline FEdgeSpecifier::FEdgeSpecifier(const FGraphVertexHandle& InVertexHandle1, const FGraphVertexHandle& InVertexHandle2) : VertexHandle1(InVertexHandle1) , VertexHandle2(InVertexHandle2)`

#### class `UGraph`  
`class UGraph: public UObject`  
_L92-193_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: A UGraph is a collection of nodes and edges. This graph representation is meant to be easily integrable into gameplay systems in the Unreal Engine. Conceptually, you can imagine that a graph is meant to easily represent relationships so we can answer queries such as: - Are these two nodes connected to each other? - How far away are these two nodes? - Who is the closest node that has XYZ? - etc. UGraph provides an interface to be able to run such queries. However, ultimately what makes the graph useful is not only the relationships represented by the edges, but also the data that is stored on each node and each edge. Depending on what the user wants to represent, the user will have to subclass UGraphVertex and UGraphEdge to hold that data. As the user adds nodes and edges into the graph, they will also be implicitly creating "islands" (i.e. a connected component in the graph). Each graph may have multiple islands. Users of the graph can disable the island detection/creation if needed. Note that this is an UNDIRECTED GRAPH.
- L96 _public prototype_ `UGraph() = default;`
- L98 _public prototype_ `void Empty();`
- L99 _public prototype_ `void InitializeFromProperties(const FGraphProperties& Properties);`
- L102 _public prototype_ `FGraphVertexHandle GetCompleteNodeHandle(const FGraphVertexHandle& InHandle) const;` — Given a node handle, find the handle in the current graph with a proper element set.
- L105 _public prototype_ `FGraphVertexHandle CreateVertex(FGraphUniqueIndex InUniqueIndex = FGraphUniqueIndex::CreateUniqueIndex(false));` — Create a node with the specified subclass, adds it to the graph, and returns a handle to it.
- L108 _public prototype_ `void ChangeVertexHandle(const FGraphVertexHandle& OldVertexHandle, const FGraphVertexHandle& NewVertexHandle);` — Changes a node handle, updating all the references. The vertex must exist.
- L111 _public prototype_ `void CreateBulkEdges(TArray<FEdgeSpecifier>&& NodesToConnect);` — Creates edges in bulk. This is more efficient than calling CreateEdge multiple times since we will only try to assign a node to an island once.
- L114 _public prototype_ `void RemoveVertex(const FGraphVertexHandle& NodeHandle);` — Removes a node from the graph along with any edges that contain it.
- L116 _public prototype_ `void RemoveBulkVertices(const TArray<FGraphVertexHandle>& InHandles);`
- L119 _public prototype_ `void RemoveEdge(const FGraphVertexHandle& VertexHandleA, const FGraphVertexHandle& VertexHandleB);` — Removes an edge between two nodes
- L122 _public prototype_ `virtual void FinalizeVertex(const FGraphVertexHandle& InHandle);` — This should be called immediately after a node and any relevant edges have been added to the graph.
- L125 _public prototype_ `void RemoveIsland(const FGraphIslandHandle& IslandHandle);` — Remove an island from the graph.
- L128 _public prototype_ `void RefreshIslandConnectivity(const FGraphIslandHandle& IslandHandle);` — Refresh the connectivity of the given island (re-check to see whether it should be split).
- L130 _public function_ `int32 NumVertices() const`
- L131 _public function_ `int32 NumIslands() const`
- L134 _public function_ `template<typename TLambda> void ForEachIsland(TLambda&& Lambda)`
- L142 _public member_ `FOnGraphVertexCreated OnVertexCreated;`
- L143 _public member_ `FOnGraphIslandCreated OnIslandCreated;`
- L144 _public member_ `FOnGraphEdgeCreated OnEdgeCreated;`
- L145 _public member_ `FOnGraphEdgeRemoved OnEdgeRemoved;`
- L147 _public function_ `const TMap<FGraphVertexHandle, TObjectPtr<UGraphVertex>>& GetVertices() const`
- L148 _public function_ `const TMap<FGraphIslandHandle, TObjectPtr<UGraphIsland>>& GetIslands() const`
- L149 _public function_ `const FGraphProperties& GetProperties() const`
- L151 _public prototype_ `UGraphVertex* GetSafeVertexFromHandle(const FGraphVertexHandle& Handle) const;`
- L152 _public prototype_ `UGraphIsland* GetSafeIslandFromHandle(const FGraphIslandHandle& Handle) const;`
- L159 _protected prototype_ `void MergeOrCreateIslands(const TArray<FEdgeSpecifier>& InEdges);` — When we add multiple edges into the graph. This function will ensure that the interactions we make externally are kept to a minimum.
- L162 _protected prototype_ `void RemoveOrSplitIsland(TObjectPtr<UGraphIsland> Island);` — After a change, this function will remove the island if it's empty or will attempt to split it into two smaller islands.
- L165 _protected prototype_ `void ReserveVertices(int32 Delta);` — Used for bulk loading in vertices/edges/islands.
- L166 _protected prototype_ `void ReserveIslands(int32 Delta);`
- L169 _private member_ `TMap<FGraphVertexHandle, TObjectPtr<UGraphVertex>> Vertices;` — `UPROPERTY()`
- L172 _private member_ `TMap<FGraphIslandHandle, TObjectPtr<UGraphIsland>> Islands;` — `UPROPERTY()`
- L173 _private member_ `FGraphProperties Properties;`
- L176 _private prototype_ `FGraphIslandHandle CreateIsland(TArray<FGraphVertexHandle> Nodes, FGraphUniqueIndex InUniqueIndex = FGraphUniqueIndex());` — Creates an island out of a given set of nodes.
- L179 _private prototype_ `bool CreateEdge(FGraphVertexHandle Node1, FGraphVertexHandle Node2, bool bMergeIslands = true);` — Creates an edge between the two nodes.
- L182 _private prototype_ `void RegisterVertex(TObjectPtr<UGraphVertex> Node);` — Adds a node to the graph's node collection and modifies the NextAvailableNodeUniqueIndex as necessary to maintain its validity.
- L185 _private prototype_ `void RegisterIsland(TObjectPtr<UGraphIsland> Edge);` — Add an island to the graph and modifies the NextAvailableIslandUniqueIndex as necessary to maintain its validity.
- L188 _private prototype_ `void RemoveEdgeInternal(const FGraphVertexHandle& VertexHandleA, const FGraphVertexHandle& VertexHandleB, bool bHandleIslands);` — Need this so that users aren't able to pass in bHandleIslands = false.
- L191 _private prototype_ `virtual TObjectPtr<UGraphVertex> CreateTypedVertex() const;` — Factory functions for creating an appropriately typed node/edge/island.
- L192 _private prototype_ `virtual TObjectPtr<UGraphIsland> CreateTypedIsland() const;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API GAMEPLAYGRAPH_API`
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGraphVertexCreated, const FGraphVertexHandle&);`
- L36 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGraphVertexCreated, const FGraphVertexHandle&);`
- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGraphIslandCreated, const FGraphIslandHandle&);`
- L37 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGraphIslandCreated, const FGraphIslandHandle&);`
- L53 _function_ `friend uint32 GetTypeHash(const FEdgeSpecifier& InEdge)`
- L66 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGraphEdgeCreated, const FEdgeSpecifier&);`
- L66 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGraphEdgeCreated, const FEdgeSpecifier&);`
- L67 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGraphEdgeRemoved, const FEdgeSpecifier&);`
- L67 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGraphEdgeRemoved, const FEdgeSpecifier&);`

### `Plugins/Experimental/GameplayGraph/Source/GameplayGraph/Public/Graph/GraphDefaultSerialization.h` (Public)


#### struct `FSerializedEdgeData`  
`struct FSerializedEdgeData`  
_L13-31_
- reflection: `USTRUCT()`
- L18 _public member_ `FGraphVertexHandle Node1;` — `UPROPERTY(SaveGame)`
- L21 _public member_ `FGraphVertexHandle Node2;` — `UPROPERTY(SaveGame)`

#### struct `FSerializedIslandData`  
`struct FSerializedIslandData`  
_L34-44_
- reflection: `USTRUCT()`
- L39 _public member_ `TArray<FGraphVertexHandle> Vertices;` — `UPROPERTY(SaveGame)`

#### struct `FSerializableGraph`  
`struct FSerializableGraph`  
_L54-71_
- reflection: `USTRUCT()`
- desc: The minimum amount of data we need to serialize to be able to reconstruct the graph as it was. Note that classes that inherit from UGraph and its elements will no doubt want to extend the graph with actual information on each node/edge/island. In that case, they should extend FSerializableGraph to contain the extra information per graph handle. Furthermore, they'll need to extend UGraph to have its own typed serialization save/load functions that call the base functions in UGraph first.
- L59 _public member_ `FGraphProperties Properties;` — `UPROPERTY(SaveGame)`
- L62 _public member_ `TArray<FGraphVertexHandle> Vertices;` — `UPROPERTY(SaveGame)`
- L65 _public member_ `TArray<FSerializedEdgeData> Edges;` — `UPROPERTY(SaveGame)`
- L68 _public member_ `TMap<FGraphIslandHandle, FSerializedIslandData> Islands;` — `UPROPERTY(SaveGame)`

#### class `TDefaultGraphSerialization`  
`template<typename TSerializableGraph> class TDefaultGraphSerialization : public IGraphSerialization`  
_L74-132_
- inherits: `IGraphSerialization`
- L78 _public prototype_ `virtual ~TDefaultGraphSerialization() = default;`
- L80 _public function_ `const TSerializableGraph& GetData() const`
- L82 _public function_ `virtual void Initialize(int32 NumVertices, int32 NumEdges, int32 NumIslands) override`
- L89 _public function_ `virtual void WriteGraphProperties(const FGraphProperties& Properties) override`
- L94 _public function_ `virtual void WriteGraphVertex(const FGraphVertexHandle& VertexHandle, const UGraphVertex* Vertex) override`
- L99 _public function_ `virtual void WriteGraphEdge(const FGraphVertexHandle& VertexHandleA, const FGraphVertexHandle& VertexHandleB) override`
- L107 _public function_ `virtual void WriteGraphIsland(const FGraphIslandHandle& IslandHandle, const UGraphIsland* Island) override`
- L123 _public function_ `virtual void Reset() override`
- L131 _protected member_ `TSerializableGraph Data;`

#### class `TDefaultGraphDeserialization`  
`template<typename TSerializableGraph> class TDefaultGraphDeserialization : public IGraphDeserialization`  
_L135-215_
- inherits: `IGraphDeserialization`
- L139 _public function_ `explicit TDefaultGraphDeserialization(const TSerializableGraph& InData) : Data(InData)`
- L143 _public prototype_ `virtual ~TDefaultGraphDeserialization() = default;`
- L145 _public function_ `virtual const FGraphProperties& GetProperties() const override`
- L150 _public function_ `virtual int32 NumVertices() const override`
- L155 _public function_ `virtual void ForEveryVertex(const TFunction<FGraphVertexHandle(const FGraphVertexHandle&)>& Lambda) const override`
- L167 _public function_ `virtual int32 NumEdges() const override`
- L172 _public function_ `virtual void ForEveryEdge(const TFunction<bool(const FEdgeSpecifier&)>& Lambda) const override`
- L184 _public function_ `virtual int32 NumIslands() const override`
- L189 _public function_ `virtual void ForEveryIsland(const TFunction<FGraphIslandHandle(const FGraphIslandHandle&, const FIslandConstructionData&)>& Lambda) const override`
- L210 _protected function_ `virtual void OnDeserializedVertex(const FGraphVertexHandle& VertexHandle) const`
- L211 _protected function_ `virtual void OnDeserializedEdge(const FEdgeSpecifier& Edge) const`
- L212 _protected function_ `virtual void OnDeserializedIsland(const FGraphIslandHandle& IslandHandle) const`
- L214 _protected member_ `const TSerializableGraph& Data;`

#### enum `EDefaultDeltaActionType`  
`enum class EDefaultDeltaActionType`  
_L223-227_
- desc: DELTA ACTIONS
- L225 _public enumerator_ `Add`
- L226 _public enumerator_ `Remove`

#### struct `TDefaultGraphVertexDeltaAction`  
`template<EDefaultDeltaActionType Type> struct TDefaultGraphVertexDeltaAction : public TDerivedGraphDeltaAction<TDefaultGraphVertexDeltaAction<Type>>`  
_L230-238_
- inherits: `TDerivedGraphDeltaAction<TDefaultGraphVertexDeltaAction<Type>>`
- L233 _public function_ `explicit TDefaultGraphVertexDeltaAction(const FGraphVertexHandle& InHandle) : VertexHandle(InHandle)`
- L237 _public member_ `FGraphVertexHandle VertexHandle;`

#### struct `TDefaultGraphEdgeDeltaAction`  
`template<EDefaultDeltaActionType Type> struct TDefaultGraphEdgeDeltaAction : public TDerivedGraphDeltaAction<TDefaultGraphEdgeDeltaAction<Type>>`  
_L241-249_
- inherits: `TDerivedGraphDeltaAction<TDefaultGraphEdgeDeltaAction<Type>>`
- L244 _public function_ `explicit TDefaultGraphEdgeDeltaAction(const FEdgeSpecifier& InEdge) : Edge(InEdge)`
- L248 _public member_ `FEdgeSpecifier Edge;`

#### struct `TDefaultGraphIslandDeltaAction`  
`template<EDefaultDeltaActionType Type> struct TDefaultGraphIslandDeltaAction : public TDerivedGraphDeltaAction<TDefaultGraphIslandDeltaAction<Type>>`  
_L252-260_
- inherits: `TDerivedGraphDeltaAction<TDefaultGraphIslandDeltaAction<Type>>`
- L255 _public function_ `explicit TDefaultGraphIslandDeltaAction(const FGraphIslandHandle& InHandle) : IslandHandle(InHandle)`
- L259 _public member_ `FGraphIslandHandle IslandHandle;`

#### struct `TDefaultGraphIslandVertexDeltaAction`  
`template<EDefaultDeltaActionType Type> struct TDefaultGraphIslandVertexDeltaAction : public TDerivedGraphDeltaAction<TDefaultGraphIslandVertexDeltaAction<Type>>`  
_L264-274_
- inherits: `TDerivedGraphDeltaAction<TDefaultGraphIslandVertexDeltaAction<Type>>`
- L267 _public function_ `explicit TDefaultGraphIslandVertexDeltaAction(const FGraphIslandHandle& InIslandHandle, const FGraphVertexHandle& InVertexHandle) : IslandHandle(InIslandHandle) , VertexHandle(InVertexHandle)`
- L272 _public member_ `FGraphIslandHandle IslandHandle;`
- L273 _public member_ `FGraphVertexHandle VertexHandle;`

#### class `TDefaultGraphDeltaActionHandler`  
`template<typename TInSerializableGraph> class TDefaultGraphDeltaActionHandler : public TGraphDeltaActionHandler<TInSerializableGraph>`  
_L280-375_
- inherits: `TGraphDeltaActionHandler<TInSerializableGraph>`
- desc: DELTA HANDLER
- L282 _private typedef_ `using TThisClass = TDefaultGraphDeltaActionHandler<TInSerializableGraph>;`
- L285 _public typedef_ `using FCreateVertexDeltaAction = TDefaultGraphVertexDeltaAction<EDefaultDeltaActionType::Add>;`
- L286 _public typedef_ `using FRemoveVertexDeltaAction = TDefaultGraphVertexDeltaAction<EDefaultDeltaActionType::Remove>;`
- L288 _public typedef_ `using FCreateEdgeDeltaAction = TDefaultGraphEdgeDeltaAction<EDefaultDeltaActionType::Add>;`
- L289 _public typedef_ `using FRemoveEdgeDeltaAction = TDefaultGraphEdgeDeltaAction<EDefaultDeltaActionType::Remove>;`
- L291 _public typedef_ `using FCreateIslandDeltaAction = TDefaultGraphIslandDeltaAction<EDefaultDeltaActionType::Add>;`
- L292 _public typedef_ `using FRemoveIslandDeltaAction = TDefaultGraphIslandDeltaAction<EDefaultDeltaActionType::Remove>;`
- L294 _public typedef_ `using FAddIslandVertexDeltaAction = TDefaultGraphIslandVertexDeltaAction<EDefaultDeltaActionType::Add>;`
- L295 _public typedef_ `using FRemoveIslandVertexDeltaAction = TDefaultGraphIslandVertexDeltaAction<EDefaultDeltaActionType::Remove>;`
- L297 _public function_ `virtual void InitializeFromGraph(const TInSerializableGraph& InGraph) override`
- L303 _public function_ `virtual void Flush(TInSerializableGraph& OutGraph) override`
- L309 _public function_ `void Visit(const FCreateVertexDeltaAction& Action, TInSerializableGraph& OutGraph)`
- L315 _public function_ `void Visit(const FRemoveVertexDeltaAction& Action, TInSerializableGraph& OutGraph)`
- L321 _public function_ `void Visit(const FCreateEdgeDeltaAction& Action, TInSerializableGraph& OutGraph)`
- L330 _public function_ `void Visit(const FRemoveEdgeDeltaAction& Action, TInSerializableGraph& OutGraph)`
- L339 _public function_ `void Visit(const FCreateIslandDeltaAction& Action, TInSerializableGraph& OutGraph)`
- L347 _public function_ `void Visit(const FRemoveIslandDeltaAction& Action, TInSerializableGraph& OutGraph)`
- L353 _public function_ `void Visit(const FAddIslandVertexDeltaAction& Action, TInSerializableGraph& OutGraph)`
- L362 _public function_ `void Visit(const FRemoveIslandVertexDeltaAction& Action, TInSerializableGraph& OutGraph)`
- L373 _private member_ `TSet<FGraphVertexHandle> IncrementalVertices;` — Doing removes from the vertex and edges arrays is too slow so we make sets that we apply operations to that we copy over to the array in Flush.
- L374 _private member_ `TSet<FSerializedEdgeData> IncrementalEdges;`

#### class `TDefaultGraphIncrementalSerialization`  
`template<typename TSerializer, typename TDeltaActionHandler> class TDefaultGraphIncrementalSerialization : public TGraphIncrementalSerialization<TSerializer, TDeltaActionHandler>`  
_L383-512_
- inherits: `TGraphIncrementalSerialization<TSerializer,TDeltaActionHandler>`
- desc: INCREMENTAL SERIALIZER
- L389 _public function_ `explicit TDefaultGraphIncrementalSerialization(UGraph* InGraph) : TGraphIncrementalSerialization<TSerializer, TDeltaActionHandler>(InGraph)`
- L411 _public function_ `~TDefaultGraphIncrementalSerialization()`
- L433 _protected function_ `virtual void OnGraphVertexCreated(const FGraphVertexHandle& VertexHandle)`
- L439 _protected function_ `virtual void OnGraphVertexRemoved(const FGraphVertexHandle& VertexHandle)`
- L445 _protected function_ `virtual void OnGraphEdgeCreated(const FEdgeSpecifier& Edge)`
- L450 _protected function_ `virtual void OnGraphEdgeRemoved(const FEdgeSpecifier& Edge)`
- L455 _protected function_ `virtual void OnGraphIslandCreated(const FGraphIslandHandle& IslandHandle)`
- L461 _protected function_ `virtual void OnGraphIslandRemoved(const FGraphIslandHandle& IslandHandle)`
- L467 _protected function_ `virtual void OnGraphIslandVertexAdded(const FGraphIslandHandle& IslandHandle, const FGraphVertexHandle& VertexHandle)`
- L472 _protected function_ `virtual void OnGraphIslandVertexRemoved(const FGraphIslandHandle& IslandHandle, const FGraphVertexHandle& VertexHandle)`
- L477 _protected function_ `virtual void StartListenToVertexChanges(const FGraphVertexHandle& VertexHandle)`
- L485 _protected function_ `virtual void StopListenToVertexChanges(const FGraphVertexHandle& VertexHandle)`
- L493 _protected function_ `virtual void StartListenToIslandChanges(const FGraphIslandHandle& IslandHandle)`
- L503 _protected function_ `virtual void StopListenToIslandChanges(const FGraphIslandHandle& IslandHandle)`

#### Free symbols / members of external scopes

- L27 _function_ `friend uint32 GetTypeHash(const FSerializedEdgeData& EdgeData)`
- L217 _typedef_ `using FDefaultGraphSerialization = TDefaultGraphSerialization<FSerializableGraph>;`
- L218 _typedef_ `using FDefaultGraphDeserialization = TDefaultGraphDeserialization<FSerializableGraph>;`
- L377 _typedef_ `using FDefaultGraphDeltaActionHandler = TDefaultGraphDeltaActionHandler<FSerializableGraph>;`
- L514 _typedef_ `using FDefaultGraphIncrementalSerialization = TDefaultGraphIncrementalSerialization<FDefaultGraphSerialization, FDefaultGraphDeltaActionHandler>;`

### `Plugins/Experimental/GameplayGraph/Source/GameplayGraph/Public/Graph/GraphElement.h` (Public)


#### enum `EGraphElementType`  
`enum class EGraphElementType`  
_L14-20_
- reflection: `UENUM()`
- L16 _public enumerator_ `Node`
- L17 _public enumerator_ `Edge`
- L18 _public enumerator_ `Island`
- L19 _public enumerator_ `Unknown`

#### class `UGraphElement`  
`class UGraphElement : public UObject`  
_L23-53_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UObject`
- L27 _public prototype_ `explicit UGraphElement(EGraphElementType InElementType);`
- L28 _public function_ `EGraphElementType GetElementType() const`
- L32 _protected prototype_ `UGraphElement();`
- L34 _protected function_ `void SetUniqueIndex(FGraphUniqueIndex InUniqueIndex)`
- L35 _protected function_ `FGraphUniqueIndex GetUniqueIndex() const`
- L37 _protected prototype_ `void SetParentGraph(TObjectPtr<UGraph> InGraph);`
- L38 _protected prototype_ `TObjectPtr<UGraph> GetGraph() const;`
- L41 _protected function_ `virtual void OnCreate()` — Called when we create this element and prior to setting any properties.
- L45 _private member_ `EGraphElementType ElementType = EGraphElementType::Unknown;` — `UPROPERTY()`
- L49 _private member_ `FGraphUniqueIndex UniqueIndex = FGraphUniqueIndex();` — `UPROPERTY()` — Will match the UniqueIndex in the UGraphHandle that references this element.
- L52 _private member_ `TWeakObjectPtr<UGraph> ParentGraph;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYGRAPH_API`

### `Plugins/Experimental/GameplayGraph/Source/GameplayGraph/Public/Graph/GraphHandle.h` (Public)


#### struct `FGraphUniqueIndex`  
`struct FGraphUniqueIndex`  
_L18-93_
- reflection: `USTRUCT()`
- L22 _public function_ `FGraphUniqueIndex(bool InIsTemp = false) : UniqueIndex(FGuid()) , bIsTemporary(InIsTemp)`
- L27 _public function_ `FGraphUniqueIndex(FGuid InUniqueIndex, bool InIsTemp = false) : UniqueIndex(InUniqueIndex) , bIsTemporary(InIsTemp)`
- L33 _public function_ `bool IsValid() const`
- L38 _public function_ `bool IsTemporary() const`
- L43 _public function_ `void SetTemporary(bool InTemp)`
- L48 _public function_ `FGraphUniqueIndex NextUniqueIndex() const`
- L53 _public function_ `static FGraphUniqueIndex CreateUniqueIndex(bool InIsTemp = false)`
- L58 _public function_ `bool operator==(const FGraphUniqueIndex& Other) const`
- L63 _public function_ `bool operator!=(const FGraphUniqueIndex& Other) const`
- L68 _public function_ `bool operator<(const FGraphUniqueIndex& Other) const`
- L78 _public function_ `FString ToString() const`
- L87 _private member_ `FGuid UniqueIndex = FGuid();` — `UPROPERTY(SaveGame)` — Unique identifier within a graph.
- L91 _private member_ `bool bIsTemporary = false;` — `UPROPERTY(Transient)` — Temporary Status for index

#### struct `FGraphHandle`  
`struct FGraphHandle`  
_L102-133_
- reflection: `USTRUCT()`
- desc: For persistence, every node in a graph is given a unique index. A FGraphHandle encapsulates that index to make it easy to go from the index to the node and vice versa.
- L106 _public prototype_ `FGraphHandle() = default;`
- L107 _public prototype_ `FGraphHandle(FGraphUniqueIndex InUniqueIndex, UGraph* InGraph);`
- L108 _public prototype_ `virtual ~FGraphHandle() = default;`
- L110 _public prototype_ `void Clear();`
- L113 _public prototype_ `bool IsValid() const;` — Whether or not this handle has been initialized.
- L114 _public prototype_ `bool IsComplete() const;`
- L115 _public function_ `virtual bool HasElement() const`
- L117 _public function_ `FGraphUniqueIndex GetUniqueIndex() const`
- L118 _public function_ `UGraph* GetGraph() const`
- L120 _public prototype_ `bool operator==(const FGraphHandle& Other) const;`
- L121 _public prototype_ `bool operator!=(const FGraphHandle& Other) const;`
- L122 _public prototype_ `bool operator<(const FGraphHandle& Other) const;`
- L128 _private member_ `FGraphUniqueIndex UniqueIndex = FGraphUniqueIndex();` — `UPROPERTY(SaveGame)` — Unique identifier within a graph.
- L132 _private member_ `TWeakObjectPtr<UGraph> WeakGraph;` — `UPROPERTY(Transient)` — Pointer to the graph
- L169 _function_ `inline bool FGraphHandle::IsValid() const`
- L174 _function_ `inline bool FGraphHandle::IsComplete() const`
- L179 _function_ `inline bool FGraphHandle::operator==(const FGraphHandle& Other) const`
- L184 _function_ `inline bool FGraphHandle::operator!=(const FGraphHandle& Other) const`
- L189 _function_ `inline bool FGraphHandle::operator<(const FGraphHandle& Other) const`

#### struct `FGraphVertexHandle`  
`struct FGraphVertexHandle : public FGraphHandle`  
_L136-149_
- reflection: `USTRUCT()`
- inherits: `FGraphHandle`
- L140 _public member_ `static FGraphVertexHandle Invalid;`
- L142 _public prototype_ `FGraphVertexHandle() = default;`
- L143 _public function_ `FGraphVertexHandle(FGraphUniqueIndex InUniqueIndex, UGraph* InGraph) : FGraphHandle(InUniqueIndex, InGraph)`
- L147 _public prototype_ `UGraphVertex* GetVertex() const;`
- L148 _public prototype_ `virtual bool HasElement() const override;`

#### struct `FGraphIslandHandle`  
`struct FGraphIslandHandle : public FGraphHandle`  
_L152-165_
- reflection: `USTRUCT()`
- inherits: `FGraphHandle`
- L156 _public member_ `static FGraphIslandHandle Invalid;`
- L158 _public prototype_ `FGraphIslandHandle() = default;`
- L159 _public function_ `FGraphIslandHandle(FGraphUniqueIndex InUniqueIndex, UGraph* InGraph) : FGraphHandle(InUniqueIndex, InGraph)`
- L163 _public prototype_ `UGraphIsland* GetIsland() const;`
- L164 _public prototype_ `virtual bool HasElement() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYGRAPH_API`
- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayGraph, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayGraph, Log, All);`
- L73 _function_ `friend uint32 GetTypeHash(const FGraphUniqueIndex& InUniqueIndex)`
- L194 _function_ `inline uint32 GetTypeHash(const FGraphHandle& Handle)`

### `Plugins/Experimental/GameplayGraph/Source/GameplayGraph/Public/Graph/GraphIncrementalSerialization.h` (Public)


#### struct `TDerivedGraphDeltaAction`  
`template<typename TDerived> struct TDerivedGraphDeltaAction`  
_L26-34_
- L30 _public function_ `template<typename TDeltaActionHandler> void Accept(TDeltaActionHandler& Visitor, typename TDeltaActionHandler::TSerializableGraph& OutGraph) const`

#### class `TGraphDeltaActionHandler`  
`template<typename TInSerializableGraph> class TGraphDeltaActionHandler`  
_L37-63_
- L46 _public typedef_ `using TSerializableGraph = TInSerializableGraph;`
- L48 _public function_ `TGraphDeltaActionHandler()`
- L52 _public prototype_ `virtual ~TGraphDeltaActionHandler() = default;`
- L54 _public function_ `virtual void InitializeFromGraph(const TSerializableGraph& InGraph)`
- L55 _public function_ `virtual void Flush(TSerializableGraph& OutGraph)`
- L59 _public function_ `template<typename TAction> void Visit(const TAction& Action, TSerializableGraph& OutGraph)` — Catch-all to remind users if their delta action handler doesn't actually support an action they created.

#### struct `TGraphDeltaActionHandler::AlwaysFalse`  
`template<typename T> struct AlwaysFalse`  
_L40-44_
- L43 _public member_ `static constexpr bool False = false;`

#### class `TGraphIncrementalSerialization`  
`template<typename TSerializer, typename TDeltaActionHandler> class TGraphIncrementalSerialization`  
_L66-112_
- L69 _public prototype_ `virtual ~TGraphIncrementalSerialization() = default;`
- L71 _public function_ `explicit TGraphIncrementalSerialization(UGraph* InGraph) : Graph(InGraph)`
- L88 _public function_ `const typename TDeltaActionHandler::TSerializableGraph& GetLatestData()` — This is not a const function as derived classes as the DeltaActionHandler may need to do a final pass on buffered data for example.
- L96 _protected function_ `template<typename TDeltaAction, typename... TParams> void AddDeltaAction(TParams... Params)`
- L102 _protected function_ `UGraph* GetGraph() const`
- L108 _private member_ `TWeakObjectPtr<UGraph> Graph;`
- L109 _private member_ `typename TDeltaActionHandler::TSerializableGraph SerializedGraphData;`
- L111 _private member_ `TDeltaActionHandler DeltaActionHandler;` — Note that the assumption here is that TDeltaActionHandler is the most derived type already so we don't need to use a pointer here.

### `Plugins/Experimental/GameplayGraph/Source/GameplayGraph/Public/Graph/GraphIsland.h` (Public)


#### enum `EGraphIslandOperations`  
`enum class EGraphIslandOperations : int32`  
_L16-24_
- reflection: `UENUM()`
- desc: These are the possible operations that can be done to an island. The graph will attempt to check that the island is allowing these operations before successfully performing any of these operations. By default all operations are allowed.
- L18 _public enumerator_ `None = 0`
- L19 _public enumerator_ `Add = 1 << 0`
- L20 _public enumerator_ `Split = 1 << 1`
- L21 _public enumerator_ `Merge = 1 << 2`
- L22 _public enumerator_ `Destroy = 1 << 3`
- L23 _public enumerator_ `All = Add | Split | Merge | Destroy`

#### enum `EGraphIslandConnectivityChange`  
`enum class EGraphIslandConnectivityChange : int32`  
_L28-38_
- reflection: `UENUM()`
- L31 _public enumerator_ `VertexAdd` — Vertex added into an island
- L33 _public enumerator_ `SplitFrom` — An island is split into 2 more islands
- L35 _public enumerator_ `SplitTo` — An island was created by splitting an old island.
- L37 _public enumerator_ `Other` — Some other undefined change - not used by the library but can be used by external users as a no-op of sorts.

#### class `UGraphIsland`  
`class UGraphIsland : public UGraphElement`  
_L57-115_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGraphElement`
- L61 _public prototype_ `UGraphIsland();`
- L63 _public function_ `FGraphIslandHandle Handle() const`
- L68 _public function_ `bool IsEmpty() const`
- L69 _public function_ `const TSet<FGraphVertexHandle>& GetVertices() const`
- L70 _public function_ `int32 Num() const`
- L72 _public function_ `bool IsOperationAllowed(EGraphIslandOperations Op) const`
- L73 _public prototype_ `void SetOperationAllowed(EGraphIslandOperations Op, bool bAllowed);`
- L76 _public function_ `template<typename TLambda> void ForEachVertex(TLambda&& Lambda)`
- L85 _public prototype_ `void AddVertex(const FGraphVertexHandle& Node);` — Adds a single node into this island.
- L88 _public prototype_ `void RemoveVertex(const FGraphVertexHandle& Node);` — Removes a node from the island.
- L91 _public prototype_ `virtual void ChangeVertexHandle(const FGraphVertexHandle& OldVertexHandle, const FGraphVertexHandle& NewVertexHandle);` — Changes a node handle. The vertex must exist.
- L93 _public member_ `FOnGraphIslandVertexAdded OnVertexAdded;`
- L94 _public member_ `FOnGraphIslandVertexRemoved OnVertexRemoved;`
- L95 _public member_ `FOnGraphIslandDestroyed OnDestroyed;`
- L96 _public member_ `FOnGraphIslandConnectedComponentsChanged OnConnectivityChanged;`
- L101 _protected prototype_ `virtual void HandleOnVertexAdded(const FGraphVertexHandle& Handle);`
- L102 _protected prototype_ `virtual void HandleOnVertexRemoved(const FGraphVertexHandle& Handle);`
- L103 _protected prototype_ `virtual void HandleOnDestroyed();`
- L104 _protected prototype_ `virtual void HandleOnConnectivityChanged(EGraphIslandConnectivityChange Change);`
- L107 _protected prototype_ `void Destroy();` — Called when removing the island from the graph.
- L111 _private member_ `TSet<FGraphVertexHandle> Vertices;` — `UPROPERTY(SaveGame)`
- L114 _private member_ `EGraphIslandOperations AllowedOperations = EGraphIslandOperations::All;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYGRAPH_API`
- L25 _prototype_ `ENUM_CLASS_FLAGS(EGraphIslandOperations);`
- L45 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGraphIslandConnectedComponentsChanged, const FGraphIslandHandle&, EGraphIslandConnectivityChange);` — Delegate to track when some sort of batch change has occurred on this island that probably changes its connectivity. This is different from FOnGraphIslandNodeRemoved since FOnGraphIslandDestructiveChangeFinish will only be called once for the graph for a given operation while FOnGraphIslandNodeRemoved may be called multiple times if we're removing more than one node from the island at a given time. Note that this will only be called as a result of a destructive change. So repeatedly adding a node to an island won't call this event.
- L45 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGraphIslandConnectedComponentsChanged, const FGraphIslandHandle&, EGraphIslandConnectivityChange);` — Delegate to track when some sort of batch change has occurred on this island that probably changes its connectivity. This is different from FOnGraphIslandNodeRemoved since FOnGraphIslandDestructiveChangeFinish will only be called once for the graph for a given operation while FOnGraphIslandNodeRemoved may be called multiple times if we're removing more than one node from the island at a given time. Note that this will only be called as a result of a destructive change. So repeatedly adding a node to an island won't call this event.
- L48 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGraphIslandDestroyed, const FGraphIslandHandle&);` — Delegate to track when this island should no longer exist.
- L48 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGraphIslandDestroyed, const FGraphIslandHandle&);` — Delegate to track when this island should no longer exist.
- L51 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGraphIslandVertexAdded, const FGraphIslandHandle&, const FGraphVertexHandle&);` — Delegate to track the event when the island has a node added to it.
- L51 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGraphIslandVertexAdded, const FGraphIslandHandle&, const FGraphVertexHandle&);` — Delegate to track the event when the island has a node added to it.
- L54 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGraphIslandVertexRemoved, const FGraphIslandHandle&, const FGraphVertexHandle&);` — Delegate to track the event when the island has a node removed from it.
- L54 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGraphIslandVertexRemoved, const FGraphIslandHandle&, const FGraphVertexHandle&);` — Delegate to track the event when the island has a node removed from it.

### `Plugins/Experimental/GameplayGraph/Source/GameplayGraph/Public/Graph/GraphSerialization.h` (Public)


#### class `IGraphSerialization`  
`class IGraphSerialization`  
_L14-25_
- L17 _public prototype_ `virtual ~IGraphSerialization() = default;`
- L19 _public prototype_ `virtual void Initialize(int32 NumVertices, int32 NumEdges, int32 NumIslands) = 0;`
- L20 _public prototype_ `virtual void WriteGraphProperties(const FGraphProperties& Properties) = 0;`
- L21 _public prototype_ `virtual void WriteGraphVertex(const FGraphVertexHandle& VertexHandle, const UGraphVertex* Vertex) = 0;`
- L22 _public prototype_ `virtual void WriteGraphEdge(const FGraphVertexHandle& VertexHandleA, const FGraphVertexHandle& VertexHandleB) = 0;`
- L23 _public prototype_ `virtual void WriteGraphIsland(const FGraphIslandHandle& IslandHandle, const UGraphIsland* Island) = 0;`
- L24 _public prototype_ `virtual void Reset() = 0;`

#### class `IGraphDeserialization`  
`class IGraphDeserialization`  
_L27-46_
- L30 _public prototype_ `virtual ~IGraphDeserialization() = default;`
- L32 _public prototype_ `virtual const FGraphProperties& GetProperties() const = 0;`
- L33 _public prototype_ `virtual int32 NumVertices() const = 0;`
- L34 _public prototype_ `virtual void ForEveryVertex(const TFunction<FGraphVertexHandle(const FGraphVertexHandle&)>& Lambda) const = 0;`
- L36 _public prototype_ `virtual int32 NumEdges() const = 0;`
- L37 _public prototype_ `virtual void ForEveryEdge(const TFunction<bool(const FEdgeSpecifier&)>& Lambda) const = 0;`
- L44 _public prototype_ `virtual int32 NumIslands() const = 0;`
- L45 _public prototype_ `virtual void ForEveryIsland(const TFunction<FGraphIslandHandle(const FGraphIslandHandle&, const FIslandConstructionData&)>& Lambda) const = 0;`

#### struct `IGraphDeserialization::FIslandConstructionData`  
`struct FIslandConstructionData`  
_L39-42_
- L41 _public member_ `TArray<FGraphVertexHandle> Vertices;`

### `Plugins/Experimental/GameplayGraph/Source/GameplayGraph/Public/Graph/GraphVertex.h` (Public)


#### class `UGraphVertex`  
`class UGraphVertex : public UGraphElement`  
_L15-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGraphElement`
- L19 _public prototype_ `UGraphVertex();`
- L21 _public function_ `FGraphVertexHandle Handle() const`
- L26 _public prototype_ `bool HasEdgeTo(const FGraphVertexHandle& Other) const;`
- L27 _public function_ `int32 NumEdges() const`
- L29 _public function_ `const FGraphIslandHandle& GetParentIsland() const`
- L32 _public function_ `template<typename TLambda> void ForEachAdjacentVertex(TLambda&& Lambda)`
- L40 _public function_ `const TSet<FGraphVertexHandle>& GetEdges() const`
- L43 _public prototype_ `void ChangeEdgeVertexHandle(const FGraphVertexHandle& OldVertexHandle, const FGraphVertexHandle& NewVertexHandle);` — Changes an edge vertex handle. The vertex must exist.
- L45 _public member_ `FOnGraphVertexRemoved OnVertexRemoved;`
- L46 _public member_ `FOnGraphVertexParentIslandSet OnParentIslandSet;`
- L52 _protected prototype_ `void AddEdgeTo(const FGraphVertexHandle& Node);`
- L53 _protected prototype_ `void RemoveEdge(const FGraphVertexHandle& AdjacentVertexHandle);`
- L54 _protected prototype_ `void SetParentIsland(const FGraphIslandHandle& Island);`
- L56 _protected prototype_ `virtual void HandleOnVertexRemoved();`
- L60 _private member_ `TSet<FGraphVertexHandle> Edges;` — `UPROPERTY()`
- L63 _private member_ `FGraphIslandHandle ParentIsland;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYGRAPH_API`
- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGraphVertexRemoved, const FGraphVertexHandle&);` — Event for when the node has been removed from the graph.
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGraphVertexRemoved, const FGraphVertexHandle&);` — Event for when the node has been removed from the graph.
- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGraphVertexParentIslandSet, const FGraphVertexHandle&, const FGraphIslandHandle&);`
- L12 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGraphVertexParentIslandSet, const FGraphVertexHandle&, const FGraphIslandHandle&);`
