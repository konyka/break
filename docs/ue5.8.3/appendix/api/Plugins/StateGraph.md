# Plugins / StateGraph

- module root: `Plugins/Experimental/StateGraph/Source/StateGraph`
- headers: 2; symbols: 123
- symbol kinds: class=3, delegate=3, enum=2, enumerator=12, function=27, macro=1, member=25, namespace=2, prototype=38, typedef=10
- PrivateDependencyModuleNames: Core

### `Plugins/Experimental/StateGraph/Source/StateGraph/Public/StateGraph.h` (Public)


#### class `UE::FStateGraphNode`  
`class FStateGraphNode : public TSharedFromThis<FStateGraphNode>, public FNoncopyable`  
_L41-177_
- inherits: `TSharedFromThis<FStateGraphNode>,FNoncopyable`
- desc: Abstract base class for all nodes in the state graph.
- L45 _public prototype_ `FStateGraphNode(FName InName);`
- L47 _public prototype_ `virtual ~FStateGraphNode();`
- L50 _public function_ `FName GetName() const` — Get the name of the node.
- L55 _public function_ `const FString& GetLogName() const`
- L75 _public function_ `EStatus GetStatus() const` — Get the status of the node.
- L81 _public function_ `const TCHAR* GetStatusName() const` — Get the status of the node as a string.
- L86 _public prototype_ `static const TCHAR* GetStatusName(EStatus Status);`
- L89 _public function_ `double GetTimeout() const` — Get timeout in seconds.
- L95 _public prototype_ `void SetTimeout(double InTimeout);` — Set timeout in seconds from when Start is run until Complete is run. If this timeout is exceeded, the Status is set to TimedOut.
- L97 _public function_ `FDateTime GetStartTime() const`
- L102 _public function_ `FDateTime GetCompletedTime() const`
- L108 _public prototype_ `double GetDuration() const;` — Get duration of time that the node has taken to run. Returns 0 if not yet started.
- L111 _public prototype_ `virtual bool CheckDependencies() const;` — Returns true if all dependencies are met and the node can be started. This base version checks that all nodes in the Dependencies set have been completed, but can be replaced or extended.
- L114 _public prototype_ `virtual void Complete();` — Set Status to Completed and notify the state graph to start other nodes which may have been blocked on this node.
- L117 _public prototype_ `virtual void Reset();` — Reset this node to NotStarted so it is run again. Override to reset any state or clean up pending async tasks.
- L120 _public function_ `FStateGraphPtr GetStateGraph() const` — Get the state graph for this node, which may be invalid if this node has not been added or was removed.
- L135 _public prototype_ `template<typename NodeType, typename... ArgsTypes> TSharedPtr<NodeType, ESPMode::ThreadSafe> Next(ArgsTypes&&... Args) const;` — Helper function to create a new node, add it to this node's StateGraph, and add this node as a dependency. This allows for chaining nodes together such as: StateGraph->CreateNode("NodeA", this, &SomeMemberFunction) ->Next("NodeB", &SomeStaticFunction) ->Next<SomeNodeClass>() ->Next("NodeC", [](FStateGraph& StateGraph, FStateGraphNodeFunctionComplete Complete) { Complete(); });
- L138 _public prototype_ `template<typename... ArgsTypes> FStateGraphNodeFunctionPtr Next(ArgsTypes&&... Args) const;`
- L140 _public member_ `TSet<FName> Dependencies;`
- L145 _protected prototype_ `virtual void Start() = 0;` — Start this node.
- L148 _protected function_ `virtual void TimedOut()` — Node timed out. Override to cleanup up any state or pending async tasks. This will not get called if OnNodeStatusChanged removes the node after updating the status to TimedOut.
- L151 _protected function_ `virtual void Removed()` — Node was removed from the state graph. Override to cleanup up any state or pending async tasks.
- L154 _protected prototype_ `virtual void UpdateConfig();` — Update config from INI files. Called when node is added to a state graph or during hotfixes. Override this to read any custom config the for the node.
- L157 _protected function_ `const FString& GetConfigSectionName() const` — Get the name of the node.
- L165 _private prototype_ `void SetStatus(EStatus NewStatus);` — Set status and fire delegate if needed.
- L167 _private member_ `FName Name;`
- L168 _private member_ `FString LogName;`
- L169 _private member_ `FString ConfigSectionName;`
- L170 _private member_ `EStatus Status = EStatus::NotStarted;`
- L171 _private member_ `FStateGraphWeakPtr StateGraphWeakPtr;`
- L172 _private member_ `FDateTime StartTime = 0.f;`
- L173 _private member_ `FDateTime CompletedTime = 0.f;`
- L174 _private member_ `double Timeout = 0.f;`
- L434 _function_ `template<typename NodeType, typename... ArgsTypes> TSharedPtr<NodeType, ESPMode::ThreadSafe> FStateGraphNode::Next(ArgsTypes&&... Args) const`
- L449 _function_ `template<typename... ArgsTypes> FStateGraphNodeFunctionPtr FStateGraphNode::Next(ArgsTypes&&... Args) const`

#### enum `UE::FStateGraphNode::EStatus`  
`enum class EStatus : uint8`  
_L60-72_
- L63 _public enumerator_ `NotStarted` — State graph has not attempted to start this node yet, or the node has been reset.
- L65 _public enumerator_ `Blocked` — State graph attempted to start this node, but it is waiting on dependencies or some external blocking condition.
- L67 _public enumerator_ `Started` — State graph has started this node by calling Start().
- L69 _public enumerator_ `Completed` — Node's Complete() function has been called, allowing dependent nodes to run.
- L71 _public enumerator_ `TimedOut` — Node timed out.

#### class `UE::FStateGraphNodeFunction`  
`class FStateGraphNodeFunction : public FStateGraphNode`  
_L185-198_
- inherits: `FStateGraphNode`
- desc: Node for wrapping functions as delegates.
- L189 _public prototype_ `FStateGraphNodeFunction(FName InName, const FStateGraphNodeFunctionStart& InStartFunction);`
- L190 _public prototype_ `virtual bool CheckDependencies() const override;`
- L194 _protected prototype_ `virtual void Start() override;`
- L195 _protected member_ `FStateGraphNodeFunctionStart StartFunction;`

#### class `UE::FStateGraph`  
`class FStateGraph : public TSharedFromThis<FStateGraph>, public FNoncopyable`  
_L203-429_
- inherits: `TSharedFromThis<FStateGraph>,FNoncopyable`
- desc: State graph class to run and manage nodes with.
- L207 _public prototype_ `FStateGraph(FName InName, const FString& InContextName = FString());`
- L209 _public prototype_ `virtual ~FStateGraph();`
- L212 _public prototype_ `void Initialize();` — Perform state graph initialization that could not run in constructor due to shared pointers not being ready, such as registering for hotfixes.
- L215 _public function_ `FName GetName() const` — Get the name of the state graph.
- L220 _public function_ `const FString& GetContextName() const`
- L225 _public function_ `const FString& GetLogName() const`
- L249 _public function_ `EStatus GetStatus() const` — Get the status of the state graph.
- L255 _public function_ `const TCHAR* GetStatusName() const` — Get the status of the state graph as a string.
- L260 _public prototype_ `static const TCHAR* GetStatusName(EStatus Status);`
- L263 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FStatusChanged, FStateGraph& , EStatus , EStatus );` — Delegate fired when the state graph status changes. Useful to know when it becomes blocked or times out.
- L264 _public member_ `FStatusChanged OnStatusChanged;`
- L267 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FNodeStatusChanged, FStateGraphNode& , FStateGraphNode::EStatus , FStateGraphNode::EStatus );` — Delegate fired when a node status changes.
- L268 _public member_ `FNodeStatusChanged OnNodeStatusChanged;`
- L271 _public function_ `double GetTimeout() const` — Get timeout in seconds.
- L277 _public prototype_ `void SetTimeout(double InTimeout);` — Set timeout in seconds from the initial run call (when Status changes from NotStarted to Running) to when Status changes to Completed.
- L279 _public function_ `FDateTime GetStartTime() const`
- L284 _public function_ `FDateTime GetCompletedTime() const`
- L290 _public prototype_ `double GetDuration() const;` — Get duration of time that the state graph has taken to run. Returns 0 if not yet started.
- L293 _public prototype_ `bool AddNode(const FStateGraphNodeRef& Node);` — Add a node to the state graph. Returns true if successful, false if the node is either already added to a state graph or if an existing node with the same name exists.
- L296 _public prototype_ `bool RemoveNode(FName NodeName);` — Remove a node from the state graph. Returns true if successful, false if no node was found for the name.
- L299 _public prototype_ `void RemoveAllNodes();` — Remove all nodes from the state graph that exist when this function is started. It's possible for nodes to be added back before this function returns if Node->Removed() adds nodes.
- L302 _public function_ `TMap<FName, FStateGraphNodeRef>& GetNodes()` — Get map of all nodes in the state graph. References should not be cached in case the node is destroyed.
- L308 _public function_ `FStateGraphNodeRef* GetNodeRef(FName NodeName)` — Get a node from the state graph. References should not be cached in case the node is destroyed.
- L315 _public function_ `template<typename NodeType = FStateGraphNode> TSharedPtr<NodeType, ESPMode::ThreadSafe> GetNode(FName NodeName)` — Get a node from the state graph, casting to a derived type if needed.
- L328 _public function_ `template<typename NodeType, typename... ArgsTypes> TSharedRef<NodeType, ESPMode::ThreadSafe> CreateNode(ArgsTypes&&... Args)` — Create and add a new node for a given node class type.
- L338 _public function_ `CreateNode(FName NodeName, ObjectType* Object, FunctionType Function, ArgsTypes&&... Args)`
- L372 _public function_ `CreateNode(FName NodeName, FunctionType Function, ArgsTypes&&... Args)`
- L378 _public prototype_ `bool AddDependencies(FName NodeName, const TArrayView<const FName> Dependencies);` — Helper function for adding dependencies to a node.
- L387 _public prototype_ `void Run();` — Run the state graph. This is run automatically when nodes complete to try starting any blocked nodes, so this only needs to be run manually when: - The state graph has not been run yet (Status = NotStarted). - The state graph has become blocked, and the blocking condition has been resolved (Status = Blocked). - A new node has been added to the state graph or dependencies for nodes have changed that may unblock existing nodes. - The state graph was reset or paused and should be started again.
- L392 _public prototype_ `void Reset();` — Stop and reset the state graph and all nodes. The state graph can be started again with Run().
- L397 _public prototype_ `void Pause();` — Pause the state graph and prevent additional nodes from being started. Other actions can still happen such as nodes completing nodes, adding nodes, resetting, etc.
- L400 _public prototype_ `void LogDebugInfo(ELogVerbosity::Type Verbosity);` — Log debug info for the state graph and each node.
- L404 _protected prototype_ `static bool IsNoTimeouts();`
- L408 _protected prototype_ `void SetStatus(EStatus NewStatus);` — Set status and fire delegate if needed.
- L411 _protected prototype_ `void UpdateConfig();` — Update config from INI files. Called from Initialize and during hotfixes.
- L414 _protected prototype_ `void OnConfigSectionsChanged(const FString& IniFilename, const TSet<FString>& SectionNames);` — Callback to update state graph and node configuration during hotfixes.
- L416 _protected member_ `FName Name;`
- L417 _protected member_ `FString ContextName;`
- L418 _protected member_ `FString LogName;`
- L419 _protected member_ `FString ConfigSectionName;`
- L420 _protected member_ `EStatus Status = EStatus::NotStarted;`
- L421 _protected member_ `FDateTime StartTime = 0.f;`
- L422 _protected member_ `FDateTime CompletedTime = 0.f;`
- L423 _protected member_ `double Timeout = 0.f;`
- L424 _protected member_ `TMap<FName, FStateGraphNodeRef> Nodes;`
- L425 _protected member_ `bool bRunning = false;`
- L426 _protected member_ `bool bRunAgain = false;`
- L427 _protected member_ `FTSTicker::FDelegateHandle TimeoutTicker;`
- L428 _protected member_ `FDelegateHandle ConfigSectionsChangedDelegate;`

#### enum `UE::FStateGraph::EStatus`  
`enum class EStatus : uint8`  
_L230-246_
- L233 _public enumerator_ `NotStarted` — State graph has not started yet.
- L235 _public enumerator_ `Running` — State graph is running.
- L237 _public enumerator_ `Waiting` — State graph is waiting for one or more nodes to complete.
- L239 _public enumerator_ `Blocked` — State graph is blocked due to missing dependencies.
- L241 _public enumerator_ `Completed` — State graph has completed.
- L243 _public enumerator_ `Paused` — State graph has been paused.
- L245 _public enumerator_ `TimedOut` — State graph timed out and stopped running.

#### Free symbols / members of external scopes

- L32 _macro_ `#define UE_API STATEGRAPH_API`
- L34 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStateGraph, Log, All);`
- L36 _namespace_ `namespace UE`
- L180 _delegate_ `DECLARE_DELEGATE_TwoParams(FStateGraphNodeFunctionStart, FStateGraph& , FStateGraphNodeFunctionComplete );` — Start function delegate type for FStateGraphNodeFunction nodes.
- L180 _prototype_ `DECLARE_DELEGATE_TwoParams(FStateGraphNodeFunctionStart, FStateGraph& , FStateGraphNodeFunctionComplete );` (scope `UE`) — Start function delegate type for FStateGraphNodeFunction nodes.
- L263 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FStatusChanged, FStateGraph& , EStatus , EStatus );` — Delegate fired when the state graph status changes. Useful to know when it becomes blocked or times out.
- L267 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FNodeStatusChanged, FStateGraphNode& , FStateGraphNode::EStatus , FStateGraphNode::EStatus );` — Delegate fired when a node status changes.

### `Plugins/Experimental/StateGraph/Source/StateGraph/Public/StateGraphFwd.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L11 _typedef_ `using FStateGraphRef = TSharedRef<FStateGraph, ESPMode::ThreadSafe>;` (scope `UE`)
- L12 _typedef_ `using FStateGraphPtr = TSharedPtr<FStateGraph, ESPMode::ThreadSafe>;` (scope `UE`)
- L13 _typedef_ `using FStateGraphWeakPtr = TWeakPtr<FStateGraph, ESPMode::ThreadSafe>;` (scope `UE`)
- L16 _typedef_ `using FStateGraphNodeRef = TSharedRef<FStateGraphNode, ESPMode::ThreadSafe>;` (scope `UE`)
- L17 _typedef_ `using FStateGraphNodePtr = TSharedPtr<FStateGraphNode, ESPMode::ThreadSafe>;` (scope `UE`)
- L18 _typedef_ `using FStateGraphNodeWeakPtr = TWeakPtr<FStateGraphNode, ESPMode::ThreadSafe>;` (scope `UE`)
- L21 _typedef_ `using FStateGraphNodeFunctionRef = TSharedRef<FStateGraphNodeFunction, ESPMode::ThreadSafe>;` (scope `UE`)
- L22 _typedef_ `using FStateGraphNodeFunctionPtr = TSharedPtr<FStateGraphNodeFunction, ESPMode::ThreadSafe>;` (scope `UE`)
- L23 _typedef_ `using FStateGraphNodeFunctionWeakPtr = TWeakPtr<FStateGraphNodeFunction, ESPMode::ThreadSafe>;` (scope `UE`)
- L26 _typedef_ `using FStateGraphNodeFunctionComplete = TFunction<void()>;` (scope `UE`) — Complete function type passed into FStateGraphNodeFunction node start functions.
