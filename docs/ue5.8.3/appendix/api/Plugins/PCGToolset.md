# Plugins / PCGToolset

- module root: `Plugins/Experimental/Toolsets/PCGToolset/Source/PCGToolset`
- headers: 8; symbols: 139
- symbol kinds: class=7, delegate=1, function=3, member=43, namespace=8, prototype=66, struct=9, variable=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Blutility, CoreUObject, Engine, Json, JsonUtilities, Kismet, LevelEditor, PCG, PCGEditor, Slate, SlateCore, UMG, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, EditorScriptingUtilities, Engine, PCG, Projects, ToolsetRegistry

### `Plugins/Experimental/Toolsets/PCGToolset/Source/PCGToolset/Private/PCGAttributePropertySelectorConverter.h` (Private)


#### class `UE::PCGToolset::FPCGAttributePropertySelectorConverter`  
`class FPCGAttributePropertySelectorConverter : public UE::ToolsetRegistry::FToolsetJsonConverter`  
_L13-22_
- inherits: `UE::ToolsetRegistry::FToolsetJsonConverter`
- desc: Converts FPCGAttributePropertySelector (and its Input/Output derivatives) to and from the plain PCG DSL string (e.g. "$Density", "@Metadata.MyAttr", "MyAttr.X.Y") so the LLM sees a single string instead of PCG's internal 6-field selector struct.
- L16 _public prototype_ `virtual FString GetName() const override;`
- L17 _public prototype_ `virtual bool CanConvertProperty(TNotNull<const FProperty*> Property) override;`
- L18 _public prototype_ `virtual TSharedPtr<FJsonObject> PropertyToJsonSchema(TNotNull<const FProperty*> Property) override;`
- L19 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToDefault(TNotNull<const FProperty*> Property, const FString& DefaultString) override;`
- L20 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToJsonData(TNotNull<FProperty*> Property, const void* Value) override;`
- L21 _public prototype_ `virtual bool JsonDataToProperty(const TSharedPtr<FJsonValue>& JsonValue, TNotNull<FProperty*> Property, void* OutValue, UObject* Outer) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PCGToolset` (scope `UE`)

### `Plugins/Experimental/Toolsets/PCGToolset/Source/PCGToolset/Public/PCGSpatialToolset.h` (Public)


#### class `UPCGSpatialToolset`  
`class UPCGSpatialToolset : public UToolsetDefinition`  
_L10-26_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UToolsetDefinition`
- L25 _public prototype_ `static UPCGExecuteGraphInstanceAsyncResult* RunPCGInstantGraph(UPCGGraph* Graph, const TMap<FString, FString>& Params);` — `UFUNCTION(meta = (AICallable), Category = "PCG|Graph")` — Runs an instant PCG graph with the specified parameters in fire-and-forget mode (Should be called directly: Not callable in a python context execution context) @param Graph - The PCG graph to execute @param Params - Key-value parameters to pass to the graph @return Array of per-node execution messages emitted while running the graph (empty on success with no issues).

### `Plugins/Experimental/Toolsets/PCGToolset/Source/PCGToolset/Public/PCGToolset.h` (Public)


#### class `UPCGToolset`  
`class UPCGToolset : public UToolsetDefinition`  
_L16-387_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UToolsetDefinition`
- desc: Toolset for building and modifying PCG graphs
- L30 _public prototype_ `static UPCGGraph* CreateGraph(const FString& Name, const FString& Path = TEXT("/Gam` — `UFUNCTION(meta = (AICallable), Category = "PCG|Graph")` — Creates a new saved PCG graph asset. @param Name - Name for the new PCG graph asset (e.g., "PCG_ForestScatter") @param Path - Content folder path where the asset should be created. Defaults to "/Game/PCG" @return The created PCG graph
- L41 _public prototype_ `static FPCGGraphStructure GetGraphStructure(const UPCGGraph* Graph);` — `UFUNCTION(meta = (AICallable), Category = "PCG|GraphParams")` — Returns the complete structure of a PCG graph including all nodes, connections, exposed parameters, and comment boxes. @param Graph - Graph to inspect @return FPCGGraphStructure with graph name, description, nodes, and edges
- L51 _public prototype_ `static bool SetGraphParams(UPCGGraph* Graph, const TArray<FPCGParamDefinition>& Params);` — `UFUNCTION(meta = (AICallable), Category = "PCG|GraphParams")` — Adds one or more graph user parameters to a specific PCG graph, such that they will be overridable in per graph instance. @param Graph - Graph to add graph parameter to @param Params - TArray<FPCGParamDefinition> An array of UStruct for Name, Type, Description, ContainerType (optional) and DefaultValueJson (optional). If user explicitly want special default values the DefaultValueJson MUST be set, otherwise OMIT DefaultValueJson for standard UE default values! @return boolean representing success/failed
- L61 _public prototype_ `static bool RemoveGraphParams(UPCGGraph* Graph, const TArray<FName>& ParamNames);` — `UFUNCTION(meta = (AICallable), Category = "PCG|GraphParams")` — Removes graph parameters to a specific PCG graph, such that they are not overridable anymore. @param Graph - Graph to remove graph parameter(s) from @param ParamNames - An array of existing param names that will be removed. @return boolean representing success/failed
- L70 _public prototype_ `static FPCGGraphSchema GetGraphSchema(const UPCGGraph* Graph);` — `UFUNCTION(meta = (AICallable), Category = "PCG|GraphParams")` — Returns the schema for a PCG Graph's graph parameters @param Graph - Graph to get the graph parameters of. @return FPCGGraphSchema with graph name, params schema (JSON), input/output pins
- L79 _public prototype_ `static FString GetGraphDescription(const UPCGGraph* Graph);` — `UFUNCTION(meta = (AICallable), Category = "PCG|GraphParams")` — Returns the description of a PCG graph. @param Graph - Graph to get the description of. @return The graph's description text, or empty string if the graph has no description set.
- L89 _public prototype_ `static bool SetGraphDescription(UPCGGraph* Graph, const FString& Description);` — `UFUNCTION(meta = (AICallable), Category = "PCG|GraphParams")` — Set the description of a PCGGraph @param Graph - Graph to set description of. @param Description - New description of graph @return boolean representing success/failed
- L98 _public prototype_ `static TArray<FPCGGraphInstanceInfo> ListGraphInstances();` — `UFUNCTION(meta = (AICallable), Category = "PCG|GraphInstance")` — Gets all actors with a PCG graph instance in the scene. @return Array of FPCGGraphInstanceInfo for all actors with a graph instance
- L112 _public prototype_ `static FPCGGraphInstanceInfo SpawnGraphInstance(UPCGGraph* Graph, const FString& Name, const FTransform& Transform, const FString& JsonParams = "");` — `UFUNCTION(meta = (AICallable), Category = "PCG|GraphInstance")`
- L122 _public prototype_ `static UPCGExecuteGraphInstanceAsyncResult* ExecuteGraphInstance(const APCGVolume* PCGVolume);` — `UFUNCTION(meta = (AICallable, NonTransactableToolCall), Category = "PCG|GraphInstanceParams")` — Executes the graph instance and returns any issues encountered during execution. @param PCGVolume - The PCG Volume whose graph instance to execute. @return Array of messages emitted while executing the graph instance (empty on success with no issues)
- L131 _public prototype_ `static FInstancedPropertyBag GetGraphInstanceParams(const APCGVolume* PCGVolume);` — `UFUNCTION(meta = (AICallable), Category = "PCG|GraphInstanceParams")` — Gets the graph instance params of a specific actor, actor MUST have a graph instance @param PCGVolume - The actor to get graph instance params from @return FInstancedPropertyBag containing the filtered graph instance parameters
- L141 _public prototype_ `static bool SetGraphInstanceParams(const APCGVolume* PCGVolume, const FString& JsonParams);` — `UFUNCTION(meta = (AICallable), Category = "PCG|GraphInstanceParams")` — Sets the graph instance params of a specific actor, actor MUST have a graph instance @param PCGVolume - The actor to set graph instance params for @param JsonParams - JSON string representing JsonObject for the params to set. MUST be in format: {{"property_1_name": "property_1_value"}, ...} @return boolean representing success/failed
- L151 _public prototype_ `static bool ResetGraphInstanceParams(const APCGVolume* PCGVolume, const TArray<FName>& ParamNames);` — `UFUNCTION(meta = (AICallable), Category = "PCG|GraphInstanceParams")` — Resets the given graph instance params back to the graph's default values. Actor MUST have a graph instance. @param PCGVolume - The actor to reset graph instance params for. @param ParamNames - Names of the parameters to reset. @return boolean representing success/failed
- L161 _public prototype_ `static TArray<FString> ListNativeNodes(const bool bCommonOnly = true);` — `UFUNCTION(meta = (AICallable), Category = "PCG|Nodes")` — Returns a list of available native PCG node type names. @param bCommonOnly Whether to only return the commonly used Native nodes. Only use bCommonOnly = false if the user specifically asks for it. @return Array of native node type names
- L170 _public prototype_ `static TArray<FString> ListAvailableSubgraphs();` — `UFUNCTION(meta = (AICallable), Category = "PCG|Nodes")` — Lists the PCG graphs that can be used with the Subgraph native node. Only these graphs should be used with the Subgraph native node. @return Array of graph asset paths that can be used with the Subgraph native node
- L180 _public prototype_ `static FPCGNativeNodeSchema GetNativeNodeSchema(const FString& NodeName);` — `UFUNCTION(meta = (AICallable), Category = "PCG|Nodes")` — Returns the schema for a PCG node type including input/output pins, parameters, and their types. @param NodeName - Node name @return FPCGNativeNodeSchema with node name, description, properties schema (JSON), input/output pins
- L196 _public prototype_ `static UPCGNode* AddNode( UPCGGraph* Graph, const FString& NativeNodeType, const FString& NodeName, const FString& JsonParams = FString(), const FString& NodeTitle = FString(), const FString& NodeComment = FString(), const int32 XPositionIdx = 0, const int32 YPositionIdx = 0);` — `UFUNCTION(meta = (AICallable), Category = "PCG|Nodes")` — Adds a native node to the graph. @param Graph - Graph to modify. @param NativeNodeType - The native type of the added node. @param NodeName - The name of the added node. (Must be unique identifier in the graph) @param JsonParams - The Json string representing a dictionary of the params to set on the node. Optional. Default is empty. Only non-default params need be included. @param NodeTitle - The Display Title of the node. Optional. Default is empty. @param NodeComment - The comment attached to the node, if needed. Default is empty. @param XPositionIdx - The X coordinate of the position of the node in the editor. Optional. Default is 0. Typical node size X is 200 @param YPositionIdx - The Y coordinate of the position of the node in the editor. Optional. Default is 0. Typical node size Y is 100 @return The Added Node object
- L220 _public prototype_ `static UPCGNode* AddSubgraphNode( UPCGGraph* Graph, UPCGGraph* SubGraphForNode, const FString& NodeName, const FString& JsonParams = FString(), const FString& NodeTitle = FString(), const FString& NodeComment = FString(), const int32 XPositionIdx = 0, const int32 YPositionIdx = 0);` — `UFUNCTION(meta = (AICallable), Category = "PCG|Nodes")` — Adds a subgraph node to the graph. @param Graph - Graph to modify. @param SubGraphForNode - The subgraph to use in the added node. @param NodeName - The name of the added node. (Must be unique identifier in the graph) @param JsonParams - The Json string representing a dictionary of the params to override on the graph. Optional. Default is empty. Only non-default params need be included @param NodeTitle - The Display Title of the node. Optional. Default is empty. @param NodeComment - The comment attached to the node, if needed. Default is empty and will clear the comment. @param XPositionIdx - The X coordinate of the position of the node in the editor. Optional. Default is 0. Typical node size X is 200 @param YPositionIdx - The Y coordinate of the position of the node in the editor. Optional. Default is 0. Typical node size Y is 100 @return The Added Node object
- L239 _public prototype_ `static bool UpdateNode(UPCGNode* Node, const FString& JsonParams = FString(), const FString& NodeTitle = FString());` — `UFUNCTION(meta = (AICallable), Category = "PCG|Nodes")` — Updates a node by changing its params and/or title. @param Node - The node to modify. @param JsonParams - The Json string representing a dictionary of the params to override. Optional. Default is empty. Only non-default params need be included @param NodeTitle - The Display Title of the node. Optional. Default is empty. Empty will keep the old title @return boolean representing success/failed
- L249 _public prototype_ `static bool SetNodeComment(UPCGNode* Node, const FString& NodeComment);` — `UFUNCTION(meta = (AICallable), Category = "PCG|Nodes")` — Change the comment on the specified node. @param Node - The node to set the comment on. @param NodeComment - The comment attached to the node. @return boolean representing success/failed
- L258 _public prototype_ `static FPCGNodeInfo GetNodeInfo(const UPCGNode* Node);` — `UFUNCTION(meta = (AICallable), Category = "PCG|Nodes")` — Returns node details including name, position, and all parameter values. @param Node - The node to get info from. @return FPCGNodeInfo with node details including name, position, type, and parameter overrides
- L269 _public prototype_ `static bool RepositionNode(UPCGNode* Node, const int32 XPositionIdx, const int32 YPositionIdx);` — `UFUNCTION(meta = (AICallable), Category = "PCG|Nodes")` — Change the position of node. @param Node - The node to modify the position. @param XPositionIdx - The X coordinate of the position of the node in the editor. @param YPositionIdx - The Y coordinate of the position of the node in the editor. @return boolean representing success/failed
- L279 _public prototype_ `static bool RemoveNode(UPCGGraph* Graph, UPCGNode* Node);` — `UFUNCTION(meta = (AICallable), Category = "PCG|Nodes")` — Removes the node from the graph, will also remove edges connected to the node. @param Graph - The graph to remove the node from. @param Node - The node to remove. @return boolean representing success/failed
- L291 _public prototype_ `static TArray<UPCGNode*> ConnectNodePins(UPCGNode* FromNode, const FString& FromPinLabel, UPCGNode* ToNode, const FString& ToPinLabel);` — `UFUNCTION(meta = (AICallable), Category = "PCG|Nodes")` — Add an edge between two nodes connected to the specified pins. @param FromNode - The source node of the edge to add. @param FromPinLabel - The label of the source pin of the source node. @param ToNode - The destination node of the edge to add. @param ToPinLabel - The label of the destination pin of the destination node. @return The list of nodes (conversions and/or filters) that were added to allow the connection to work.
- L304 _public prototype_ `static bool DisconnectNodePins(UPCGNode* FromNode, const FString& FromPinLabel, UPCGNode* ToNode, const FString& ToPinLabel);` — `UFUNCTION(meta = (AICallable), Category = "PCG|Nodes")` — Removes the edge between two nodes connected to the specified pins. @param FromNode - The source node of the edge to add. @param FromPinLabel - The label of the source pin of the source node. @param ToNode - The destination node of the edge to add. @param ToPinLabel - The label of the destination pin of the destination node. @return boolean representing success/failed
- L325 _public prototype_ `static FString GetNodeDataView( const APCGVolume* PCGVolume, const UPCGNode* Node, const FString& PinLabel = TEXT("Out"), const FString& AttributeName = FString(), const int32 StartIndex = 0, const int32 EndIndex = -1);` — `UFUNCTION(meta = (AICallable), Category = "PCG|Data")` — Returns a JSON Data View of a specific node's output data from the last graph execution. On first call, enables inspection so future ExecuteGraphInstance calls store per-node data. If no inspection data exists, returns an error prompting re-execution. IMPORTANT: Inspection state is shared at the graph asset level. If multiple actors use the same graph, you MUST call this tool (and ExecuteGraphInstance) on only one actor at a time. Wait for each call to fully complete before calling on the next actor. Concurrent calls on actors sharing the same graph will cause a freeze. @param PCGVolume - The PCG Volume whose graph was executed. @param Node - The node whose output to inspect. @param PinLabel - Output pin label to read. Defaults to "Out". @param AttributeName - Filter to a single attribute/property (e.g. "$Position", "$Density", "MyCustomAttr"). Empty = all attributes. @param StartIndex - Element range start, inclusive, 0-based. Default 0. @param EndIndex - Element range end, exclusive. -1 means all elements (Python slice convention). Default -1. @return JSON string with the data view contents
- L346 _public prototype_ `static FString AddCommentBox(UPCGGraph* Graph, const TArray<UPCGNode*>& Nodes, const FString& Comment, FLinearColor Color = FLinearColor::White);` — `UFUNCTION(meta = (AICallable), Category = "PCG|CommentBox")` — Adds a comment box around the given nodes. Note: If the bounding box of the nodes include other nodes, they will be included in the comment. @param Graph - Graph to add comment to. @param Nodes - The list of nodes to include in the comment box. @param Comment - The comment to put on the comment box. @param Color - The color of the comment box. Defaults to White @return The unique id of the comment node. (Can be used to edit/remove the comment)
- L360 _public prototype_ `static bool UpdateCommentBox( UPCGGraph* Graph, const FString& CommentId, const TArray<UPCGNode*>& Nodes, const FString& Comment = FString(), FLinearColor Color = FLinearColor::White);` — `UFUNCTION(meta = (AICallable), Category = "PCG|CommentBox")` — Updates an existing comment box with new nodes and value. Note: If the bounding box of the nodes include other nodes, they will be included in the comment. @param Graph - Graph to add comment to. @param CommentId - The unique id of the comment to update. @param Nodes - The list of nodes to include in the comment box. If empty, the box will keep its current dimensions. @param Comment - The new comment to put on the comment box. If empty, will keep the same text as it was. Default is empty. @param Color - The color of the comment box. Defaults to White @return boolean representing success/failed
- L375 _public prototype_ `static bool RemoveCommentBox(UPCGGraph* Graph, const FString& CommentId);` — `UFUNCTION(meta = (AICallable), Category = "PCG|CommentBox")` — Removes a comment box from the graph. Does not affect the nodes it contains. @param Graph - Graph to remove the comment from. @param CommentId - The unique id of the comment to remove. @return boolean representing success/failed
- L386 _public prototype_ `static UToolCallAsyncResultVoid* DrawSpline(const FString& ActorLabel, const FString& ActorTag, bool bRedraw, bool bClosedSpline);` — `UFUNCTION(meta = (AICallable), Category = "PCG|Other")` — Triggers the user to draw a spline in the viewport to be used later in the world building. Waits for the user to be done. @param ActorLabel - The label of the actor created or if bRedraw, the label of the actor to redraw the spline @param ActorTag - Tag assigned to the actor @param bRedraw - false: creates a new actor with the spline. true: find an actor with the label, and replaces its spline. @param bClosedSpline - true: closed spline (region) false: path.

### `Plugins/Experimental/Toolsets/PCGToolset/Source/PCGToolset/Public/PCGToolsetCustomTypes.h` (Public)


#### struct `FPCGGraphInstanceInfo`  
`struct FPCGGraphInstanceInfo`  
_L12-21_
- reflection: `USTRUCT()`
- L17 _public member_ `TObjectPtr<APCGVolume> Actor = nullptr;` — `UPROPERTY()`
- L20 _public member_ `TObjectPtr<UPCGGraph> Graph = nullptr;` — `UPROPERTY()`

#### struct `FPCGParamDefinition`  
`struct FPCGParamDefinition`  
_L24-42_
- reflection: `USTRUCT()`
- L29 _public member_ `FName Name;` — `UPROPERTY()`
- L32 _public member_ `EPCGMetadataTypes Type = EPCGMetadataTypes::Unknown;` — `UPROPERTY()`
- L35 _public member_ `FString Description;` — `UPROPERTY()`
- L38 _public member_ `EPropertyBagContainerType ContainerType = EPropertyBagContainerType::None;` — `UPROPERTY()`
- L41 _public member_ `FString DefaultValueJson = TEXT("");` — `UPROPERTY()`

#### struct `FPCGPinInfo`  
`struct FPCGPinInfo`  
_L45-57_
- reflection: `USTRUCT()`
- L50 _public member_ `FString Name;` — `UPROPERTY()`
- L53 _public member_ `FString Type;` — `UPROPERTY()`
- L56 _public member_ `FString Description;` — `UPROPERTY()`

#### struct `FPCGEdgeInfo`  
`struct FPCGEdgeInfo`  
_L60-75_
- reflection: `USTRUCT()`
- L65 _public member_ `FString SrcNode;` — `UPROPERTY()`
- L68 _public member_ `FString SrcPin;` — `UPROPERTY()`
- L71 _public member_ `FString DestNode;` — `UPROPERTY()`
- L74 _public member_ `FString DestPin;` — `UPROPERTY()`

#### struct `FPCGNodeInfo`  
`struct FPCGNodeInfo`  
_L78-105_
- reflection: `USTRUCT()`
- L83 _public member_ `FString Name;` — `UPROPERTY()`
- L86 _public member_ `FString Path;` — `UPROPERTY()`
- L89 _public member_ `FString Position;` — `UPROPERTY()`
- L92 _public member_ `FString Title;` — `UPROPERTY()`
- L95 _public member_ `bool bEnabled = true;` — `UPROPERTY()`
- L98 _public member_ `FString Comment;` — `UPROPERTY()`
- L101 _public member_ `FString NodeType;` — `UPROPERTY()`
- L104 _public member_ `FInstancedPropertyBag ParamOverrides;` — `UPROPERTY()`

#### struct `FPCGGraphStructure`  
`struct FPCGGraphStructure`  
_L108-123_
- reflection: `USTRUCT()`
- L113 _public member_ `FString Name;` — `UPROPERTY()`
- L116 _public member_ `FString Description;` — `UPROPERTY()`
- L119 _public member_ `TArray<FPCGNodeInfo> Nodes;` — `UPROPERTY()`
- L122 _public member_ `TArray<FPCGEdgeInfo> Edges;` — `UPROPERTY()`

#### struct `FPCGGraphSchema`  
`struct FPCGGraphSchema`  
_L126-141_
- reflection: `USTRUCT()`
- L131 _public member_ `FString Name;` — `UPROPERTY()`
- L134 _public member_ `FString GraphParamsSchema;` — `UPROPERTY()`
- L137 _public member_ `TArray<FPCGPinInfo> InputPins;` — `UPROPERTY()`
- L140 _public member_ `TArray<FPCGPinInfo> OutputPins;` — `UPROPERTY()`

#### struct `FPCGNativeNodeSchema`  
`struct FPCGNativeNodeSchema`  
_L144-162_
- reflection: `USTRUCT()`
- L149 _public member_ `FString Name;` — `UPROPERTY()`
- L152 _public member_ `FString Description;` — `UPROPERTY()`
- L155 _public member_ `FString PropertiesSchema;` — `UPROPERTY()`
- L158 _public member_ `TArray<FPCGPinInfo> InputPins;` — `UPROPERTY()`
- L161 _public member_ `TArray<FPCGPinInfo> OutputPins;` — `UPROPERTY()`

#### struct `FPCGNodeExecutionMessage`  
`struct FPCGNodeExecutionMessage`  
_L165-177_
- reflection: `USTRUCT()`
- L170 _public member_ `FString Message;` — `UPROPERTY()`
- L173 _public member_ `FString Severity;` — `UPROPERTY()`
- L176 _public member_ `FString ReporterNode;` — `UPROPERTY()`

#### class `UPCGExecuteGraphInstanceAsyncResult`  
`class UPCGExecuteGraphInstanceAsyncResult : public UToolCallAsyncResult`  
_L180-192_
- reflection: `UCLASS()`
- inherits: `UToolCallAsyncResult`
- L185 _public function_ `bool SetValue(TArray<FPCGNodeExecutionMessage>&& InValue)`
- L191 _public member_ `TArray<FPCGNodeExecutionMessage> Value;` — `UPROPERTY()`

### `Plugins/Experimental/Toolsets/PCGToolset/Source/PCGToolset/Public/PCGToolsetLibraryCore.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace PCGToolsetLibrary`
- L14 _namespace_ `namespace Json` (scope `PCGToolsetLibrary`)
- L16 _prototype_ `TSharedPtr<FJsonObject> ParseJson(const FString& JsonString);` (scope `PCGToolsetLibrary::Json`)
- L17 _prototype_ `FString ToJsonString(const TSharedPtr<FJsonObject>& JsonObject);` (scope `PCGToolsetLibrary::Json`)
- L18 _prototype_ `FString ToJsonString(const TArray<TSharedPtr<FJsonValue>>& JsonArray);` (scope `PCGToolsetLibrary::Json`)
- L21 _namespace_ `namespace Graph` (scope `PCGToolsetLibrary`)
- L24 _prototype_ `FInstancedPropertyBag BuildFilteredBag(const FInstancedPropertyBag& SourceBag);` (scope `PCGToolsetLibrary::Graph`) — Clones SourceBag, excluding internal PCG params (see Constants::PrimitiveInternalParamNames).
- L27 _prototype_ `void EnablePropertyOverrides(UPCGGraphInstance* GraphInstance, const TSharedPtr<FJsonObject>& JsonKeys);` (scope `PCGToolsetLibrary::Graph`) — Marks each top-level key in JsonKeys as an override on the graph instance's parameter bag.
- L30 _prototype_ `bool IsPrimitiveInternalParam(const FProperty* Property);` (scope `PCGToolsetLibrary::Graph`) — True for PCG-internal params that should never be shown or edited by the LLM.
- L33 _prototype_ `void RaiseScopedErrors(const PCGUtils::FScopedCall& ScopedCall);` (scope `PCGToolsetLibrary::Graph`) — Re-raises captured errors/warnings from a scoped call as script errors to the tool caller.
- L36 _prototype_ `FString VerbosityToString(ELogVerbosity::Type Verbosity);` (scope `PCGToolsetLibrary::Graph`) — Maps a log verbosity to the short severity label used in FPCGNodeExecutionMessage.
- L39 _prototype_ `FInstancedPropertyBag GetGraphParams(const UPCGGraph* Graph);` (scope `PCGToolsetLibrary::Graph`) — Returns Graph's user-parameters bag, minus internal params.
- L42 _prototype_ `FInstancedPropertyBag GetSubgraphNodeParamOverrides(const UPCGSubgraphSettings* SubgraphSettings, const UPCGGraph* Subgraph);` (scope `PCGToolsetLibrary::Graph`) — Returns only the params the subgraph node overrides from its graph defaults.
- L45 _prototype_ `bool SetGraphInstanceParams(UPCGGraphInstance* GraphInstance, const FString& JsonParams);` (scope `PCGToolsetLibrary::Graph`) — Applies JSON param values to the graph instance's overrides bag and marks each as overridden.
- L48 _prototype_ `TArray<FPCGNodeInfo> GetGraphNodesInfo(const UPCGGraph* Graph);` (scope `PCGToolsetLibrary::Graph`) — Returns FPCGNodeInfo for every node in Graph (including the synthetic input/output nodes).
- L51 _prototype_ `TArray<FProperty*> GetNodePropertiesFromSettings(TSubclassOf<UPCGSettings> InSettingsClass);` (scope `PCGToolsetLibrary::Graph`) — Returns the editable, LLM-visible FPropertys defined on InSettingsClass (stops at UPCGSettings).
- L54 _prototype_ `const TMap<FName, UPCGSettings*>& GetNodeNameToSettingsMap();` (scope `PCGToolsetLibrary::Graph`) — Returns the cached "display title -> default settings" lookup for every exposed PCG settings subclass.
- L57 _prototype_ `FPCGNodeInfo GetNodeInfo(const UPCGNode* Node);` (scope `PCGToolsetLibrary::Graph`) — Returns the display-ready info (name, position, type, overrides) for a single node.
- L60 _prototype_ `TArray<FPCGPinInfo> GetNodePinsSchema(const TArray<FPCGPinProperties>& PinProperties);` (scope `PCGToolsetLibrary::Graph`) — Converts PCG pin properties into FPCGPinInfo records for schema output.
- L63 _prototype_ `TArray<FPCGEdgeInfo> GetGraphEdges(const UPCGGraph* Graph);` (scope `PCGToolsetLibrary::Graph`) — Returns every edge in Graph as FPCGEdgeInfo (src/dest node + pin labels).
- L66 _prototype_ `UPCGSettings* GetRealDefaultObject(UClass* PCGSettingClass);` (scope `PCGToolsetLibrary::Graph`) — Returns a cached fresh instance of PCGSettingClass (avoids stale CDO defaults).
- L69 _function_ `TArray<FString> FindGraphPaths(const TSet<FName>& PackagePaths, TFunctionRef<bool(const FString& )> PathPredicate = [](const FString&) { return true; });` (scope `PCGToolsetLibrary::Graph`) — Finds PCG graph assets in the given package paths, optionally filtered by a path-substring predicate.
- L69 _prototype_ `TArray<FString> FindGraphPaths(const TSet<FName>& PackagePaths, TFunctionRef<bool(const FString& )> PathPredicate = [](const FString&) { return true; });` (scope `PCGToolsetLibrary::Graph`) — Finds PCG graph assets in the given package paths, optionally filtered by a path-substring predicate.
- L72 _namespace_ `namespace Constants` (scope `PCGToolsetLibrary`)
- L74 _variable_ `static const TSet<FString> PrimitiveInternalParamNames = { TEXT("InputsProcessingGraph"), TEXT("InputsFallbackGraph"), TEXT("CoreProcessGraph"), TEXT("PrepareOutputsGraph") };` (scope `PCGToolsetLibrary::Constants`)
- L78 _variable_ `static const TSet<FString> CommonNativeNodes = { TEXT("Add Attribute"),TEXT("Add Component"),TEXT("Attribute Bitwise Op"),TEXT("Attribute Boolean Op"), TEXT("Attribute Cast"),TEXT("Attribute Compare Op"),TEXT("Attribute Maths Op"),TEXT("Attribute Noise"), TEXT("Attribute Partition"),TEXT("Attribute Reduce"),TEXT("Attribute Remap"),TEXT("Attribute Remove Duplicates"), TEXT("Attribute Rename"),TEXT("Attribute Rotator Op"),TEXT("Attribute Select"),TEXT("Attribute String Op"), TEXT("Attribute Transform Op"),TEXT("Attribute Trig Op"),TEXT("Attribute Vector Op"),TEXT("Bounds Modifier"), TEXT("Branch"),TEXT("Combine Points"),TEXT("Copy Attributes"),TEXT("Copy Points"),TEXT("Create Constant"), TEXT("Create Points"),TEXT("Create Points Grid"),TEXT("Create Points Sphere"),TEXT("Create Polygon 2D"), TEXT("Create Spline"),TEXT("Create Surface From Polygon2D"),TEXT("Create Surface From Spline"), TEXT("Delete Attributes"),TEXT("Difference"),TEXT("Distance"),TEXT("Duplicate Point"),TEXT("Extents Modifier"), TEXT("Extract Attribute"),TEXT("Filter Attribute Elements"),TEXT("Filter Attribute Elements by Range"), TEXT("Filter Data - Any"),TEXT("Filter Data By Attribute"),TEXT("Filter Data By Index"), TEXT("Filter Elements By Index"),TEXT("Get Actor Data"),TEXT("Get Actor Property"), TEXT("Get Attribute From Point Index"),TEXT("Get Attribute Set from Index"),TEXT("Get Landscape Data"), TEXT("Get PCG Component Data"),TEXT("Get Property From Object Path"),TEXT("Get Segment"), TEXT("Get Spline Cont ...` (scope `PCGToolsetLibrary::Constants`)
- L109 _prototype_ `TSet<FName> GetSubgraphDirectories();` (scope `PCGToolsetLibrary::Constants`) — Helpers to get directory settings
- L110 _prototype_ `TSet<FName> GetExamplesDirectories();` (scope `PCGToolsetLibrary::Constants`)
- L111 _prototype_ `TSet<FName> GetInstantGraphDirectories();` (scope `PCGToolsetLibrary::Constants`)

### `Plugins/Experimental/Toolsets/PCGToolset/Source/PCGToolset/Public/PCGToolsetModule.h` (Public)


#### class `FPCGToolsetModule`  
`class FPCGToolsetModule : public IModuleInterface`  
_L15-23_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _private member_ `TSharedPtr<UE::PCGToolset::FPCGAttributePropertySelectorConverter> SelectorConverter;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PCGToolset` (scope `UE`)
- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGToolset, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGToolset, Log, All);`

### `Plugins/Experimental/Toolsets/PCGToolset/Source/PCGToolset/Public/PCGToolsetSettings.h` (Public)


#### class `UPCGToolsetSettings`  
`class UPCGToolsetSettings : public UDeveloperSettings`  
_L13-47_
- reflection: `UCLASS(Config=Editor, DefaultConfig, meta=(DisplayName="PCG Toolset"))`
- inherits: `UDeveloperSettings`
- desc: Settings for the PCGToolset plugin
- L18 _public prototype_ `UPCGToolsetSettings();`
- L25 _public member_ `TArray<FDirectoryPath> SubgraphDirectories;` — `UPROPERTY(Config, EditAnywhere, Category = "Primitives", meta = (ContentDir, LongPackageName, DisplayName = "Subgraph Directories", Tooltip = "Directories containing PCG subgraph primitives to expose to the AI"))` — Directories to search for subgraph primitives that will be exposed to the AI. These graphs should be reusable building blocks for PCG graph creation.
- L32 _public member_ `TArray<FDirectoryPath> ExampleGraphDirectories;` — `UPROPERTY(Config, EditAnywhere, Category = "Examples", meta = (ContentDir, LongPackageName, DisplayName = "Example Graph Directories", Tooltip = "Directories containing example PCG graphs for AI reference"))` — Directories to search for example PCG graphs that will be shown to the AI. These graphs serve as learning examples for the AI to understand patterns.
- L39 _public member_ `TArray<FDirectoryPath> InstantGraphDirectories;` — `UPROPERTY(Config, EditAnywhere, Category = "Instants", meta = (ContentDir, LongPackageName, DisplayName = "Instant Graph Directories", Tooltip = "Directories containing instant PCG graphs for AI execution"))` — Directories to search for instant PCG graphs that will be exposed to the AI. These graphs are ready-to-execute templates the AI can run directly.
- L42 _public prototype_ `virtual FName GetCategoryName() const override;` — UDeveloperSettings interface
- L44 _public prototype_ `virtual FText GetSectionText() const override;`
- L45 _public prototype_ `virtual FText GetSectionDescription() const override;`

### `Plugins/Experimental/Toolsets/PCGToolset/Source/PCGToolset/Public/PCGToolsetSkills.h` (Public)


#### class `UPCGGraphGenerationSkill`  
`class UPCGGraphGenerationSkill : public UAgentSkill`  
_L11-31_
- reflection: `UCLASS()`
- inherits: `UAgentSkill`
- L16 _protected function_ `virtual FString GeneratePrompt_Implementation(const FString& InitialInstructions) const override`
