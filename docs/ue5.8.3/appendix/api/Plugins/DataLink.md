# Plugins / DataLink

- module root: `Plugins/VirtualProduction/DataLink/Source/DataLink`
- headers: 31; symbols: 372
- symbol kinds: class=18, delegate=7, enum=6, enumerator=12, externvar=1, function=41, macro=10, member=93, namespace=12, prototype=145, struct=24, variable=3
- PrivateDependencyModuleNames: Engine
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkCoreTypes.h` (Public)


#### struct `FDataLinkString`  
`struct FDataLinkString`  
_L9-25_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public function_ `bool operator==(const FDataLinkString& InString) const`
- L24 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link")`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDataLinkString> : public TStructOpsTypeTraitsBase2<FDataLinkString>`  
_L28-34_
- inherits: `TStructOpsTypeTraitsBase2<FDataLinkString>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L31-33_

#### Free symbols / members of external scopes

- L13 _function_ `friend uint32 GetTypeHash(const FDataLinkString& InString)`
- L32 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonfd025a5c0103`)

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkDelegates.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATALINK_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DataLink` (scope `UE`)
- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnDataLinkOutputData, const FDataLinkExecutor&, FConstStructView);`
- L20 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnDataLinkOutputData, const FDataLinkExecutor&, FConstStructView);`
- L21 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnDataLinkExecutionFinished, const FDataLinkExecutor&, EDataLinkExecutionResult);`
- L21 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnDataLinkExecutionFinished, const FDataLinkExecutor&, EDataLinkExecutionResult);`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DataLink` (scope `UE`)
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EGraphCompileStatus, FOnRequestGraphCompilation, UDataLinkGraph*);`
- L25 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(EGraphCompileStatus, FOnRequestGraphCompilation, UDataLinkGraph*);` (scope `UE::DataLink`)
- L28 _externvar_ `extern FOnRequestGraphCompilation OnRequestCompilation;` (scope `UE::DataLink`) — Delegate to request to the editor module to compile a data link graph

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkEnums.h` (Public)


#### enum `UE::DataLink::EGraphCompileStatus`  
`enum class EGraphCompileStatus : uint8`  
_L10-16_
- L12 _public enumerator_ `Unknown`
- L13 _public enumerator_ `Warning`
- L14 _public enumerator_ `Error`
- L15 _public enumerator_ `UpToDate`

#### enum `EDataLinkExecutionResult`  
`enum class EDataLinkExecutionResult : uint8`  
_L21-25_
- reflection: `UENUM()`
- L23 _public enumerator_ `Failed`
- L24 _public enumerator_ `Succeeded`

#### enum `EDataLinkExecutionReply`  
`enum class EDataLinkExecutionReply : uint8`  
_L28-32_
- reflection: `UENUM()`
- L30 _public enumerator_ `Unhandled`
- L31 _public enumerator_ `Handled`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DataLink` (scope `UE`)

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkExecutor.h` (Public)


#### class `FDataLinkExecutor`  
`class FDataLinkExecutor : public FGCObject, public TSharedFromThis<FDataLinkExecutor>`  
_L23-170_
- inherits: `FGCObject,TSharedFromThis<FDataLinkExecutor>`
- desc: Executes a Data Link graph with custom instance data. @see FDataLinkExecutor::Run
- L30 _public prototype_ `static TSharedPtr<FDataLinkExecutor> Create(FDataLinkExecutorArguments&& InArgs);`
- L32 _public prototype_ `explicit FDataLinkExecutor(FPrivateToken);`
- L37 _public prototype_ `const FGuid& GetExecutorId() const;` — Gets the unique identifier for this Executor
- L44 _public prototype_ `FStringView GetContextName() const;` — Gets a brief description of the context for debugging purposes. Returns a valid context name when WITH_DATALINK_CONTEXT is true. Note: WITH_DATALINK_CONTEXT is true in builds with logging enabled.
- L47 _public prototype_ `UObject* GetContextObject() const;` — Gets the object that is responsible for this execution
- L49 _public function_ `bool IsRunning() const`
- L55 _public prototype_ `void Run();` — Called to start the graph execution
- L58 _public prototype_ `void Stop(EDataLinkExecutionResult InExecutionResult = EDataLinkExecutionResult::Succeeded);` — Called to stop graph execution
- L61 _public prototype_ `const FDataLinkNodeInstance& GetNodeInstance(const UDataLinkNode* InNode) const;` — Retrieves the node instance data of this execution for the given node
- L64 _public prototype_ `FDataLinkNodeInstance& GetNodeInstanceMutable(const UDataLinkNode* InNode);` — Retrieves the node instance data (mutable) of this execution for the given node
- L67 _public prototype_ `FDataLinkNodeInstance* FindNodeInstanceMutable(const UDataLinkNode* InNode);` — Finds the node instance data (mutable) of this execution for the given node, or null if already removed
- L74 _public prototype_ `void Next(const UDataLinkNode* InNode);` — Called when a node has received data successfully and is ready to pass it to the next node If this is called from the output node, it will broadcast this data to the listeners instead @param InNode the node that received this data
- L82 _public prototype_ `void NextPersist(const UDataLinkNode* InNode);` — Used by Nodes that keep receiving data (instead of being a one-off) to keep execution active. Called when a node has received data successfully and is ready to pass it to the next node If this is called from the output node, it will broadcast this data to the listeners instead. @param InNode the node that received this data
- L89 _public prototype_ `void Fail(const UDataLinkNode* InNode);` — Called when a node has failed to receive data and produce a valid output This stops the entire graph execution @param InNode the node that failed
- L93 _private prototype_ `bool ValidateRun();` — Called when running to ensure all the parameters are properly set. Returns true if run can be done, false otherwise
- L96 _private prototype_ `bool ValidateGraphOutputNode();` — Called to ensure the graph's output node is in a valid state. Returns true if run can be done, false otherwise
- L99 _private prototype_ `bool ValidateInputPins(TConstArrayView<FDataLinkPinReference> InInputPins, TConstArrayView<FConstStructView> InInputDataViews) const;` — Called in Pin execution to make sure the pins and data views match in compatibility
- L102 _private prototype_ `bool ExecuteEntryNodes();` — Called to execute the graph's input nodes
- L111 _private prototype_ `bool ExecuteInputPins(TConstArrayView<FDataLinkPinReference> InInputPins, TConstArrayView<FConstStructView> InInputDataViews, uint16* OutNodesExecuted = nullptr);` — Called to execute the given input pins with the input data @param InInputPins the input pins to execute (can belong to different nodes) @param InInputDataViews the matching data views for each input pin @param OutNodesExecuted the number of nodes that got executed @return true if the input pins were processed without error
- L113 _private prototype_ `bool ExecuteNode(const UDataLinkNode& InNode);`
- L116 _private prototype_ `void StopInternal();` — Called to stop graph execution
- L118 _private prototype_ `FDataLinkNodeInstance& FindOrAddNodeInstance(const UDataLinkNode* InNode);`
- L124 _private prototype_ `bool ValidateNodeExecutionStatus(const UDataLinkNode* InNode);` — Called when a node has executed and finished its logic. Checks that the node instance is valid and executing
- L127 _private prototype_ `void BroadcastFailure();` — Called when there was a failure in the graph execution
- L130 _private prototype_ `void BroadcastOutputData(FConstStructView InOutputData);` — Called when the entire graph execution has completed
- L133 _private prototype_ `virtual FString GetReferencerName() const override;`
- L134 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L138 _private member_ `const FGuid ExecutorId;` — Unique Identifier for this Executor
- L142 _private member_ `FString ContextName;` — Context string for additional information when logging
- L146 _private member_ `TObjectPtr<UObject> ContextObject;` — Object responsible for this execution
- L149 _private member_ `FDataLinkInstance Instance;` — The data link instance of this execution
- L152 _private member_ `TSharedPtr<FDataLinkSink> Sink;` — Sink where all the data for this execution is queried and stored
- L155 _private member_ `TArray<TObjectPtr<UDataLinkProcessor>> OutputProcessors;` — Container for all the output processors in this execution
- L158 _private member_ `FOnDataLinkOutputData OnOutputData;` — Delegate to call when the data link outputs data
- L161 _private member_ `FOnDataLinkExecutionFinished OnExecutionFinished;` — Delegate to call when the data link execution finishes
- L164 _private member_ `mutable TMap<TObjectPtr<const UDataLinkNode>, FDataLinkNodeInstance> NodeInstanceMap;` — Map of a Node to its Instance (Input, Output and Instance Data) for this execution
- L167 _private member_ `bool bPersistExecution = false;` — Whether to keep execution running upon data broadcast, or finish
- L169 _private member_ `bool bRunning = false;`

#### struct `FDataLinkExecutor::FPrivateToken`  
`struct FPrivateToken`  
_L27-27_
- L27 _public prototype_ `struct FPrivateToken`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkExecutorArguments.h` (Public)


#### class `FDataLinkExecutorArguments`  
`class FDataLinkExecutorArguments`  
_L14-64_
- L19 _public prototype_ `FDataLinkExecutorArguments(const FDataLinkInstance& InInstance);`
- L21 _public prototype_ `FDataLinkExecutorArguments(FDataLinkInstance&& InInstance);`
- L25 _public prototype_ `FDataLinkExecutorArguments&& SetContextName(const FString& InContextName);` — Added context information of the execution
- L27 _public prototype_ `FDataLinkExecutorArguments&& SetContextName(FString&& InContextName);` — Added context information of the execution
- L31 _public prototype_ `FDataLinkExecutorArguments&& SetContextObject(UObject* InContextObject);` — Sets the object responsible for this execution
- L34 _public prototype_ `FDataLinkExecutorArguments&& SetSink(const TSharedPtr<FDataLinkSink>& InSink);` — Sets the Sink to use. If unset, the Executor will create its own temporary sink
- L37 _public prototype_ `FDataLinkExecutorArguments&& SetOutputProcessors(TConstArrayView<UDataLinkProcessor*> InOutputProcessors);` — Sets the output processors
- L40 _public prototype_ `FDataLinkExecutorArguments&& SetOnOutputData(FOnDataLinkOutputData&& InDelegate);` — The delegate to call when the execution outputs data
- L43 _public prototype_ `FDataLinkExecutorArguments&& SetOnFinished(FOnDataLinkExecutionFinished&& InDelegate);` — The delegate to call when the execution finishes
- L46 _private member_ `FDataLinkInstance Instance;`
- L49 _private member_ `FString ContextName;`
- L52 _private member_ `TObjectPtr<UObject> ContextObject;`
- L54 _private member_ `TSharedPtr<FDataLinkSink> Sink;`
- L57 _private member_ `TArray<TObjectPtr<UDataLinkProcessor>> OutputProcessors;` — The output processors to use for the execution
- L60 _private member_ `FOnDataLinkOutputData OnOutputData;` — Delegate called when data link execution has output data ready
- L63 _private member_ `FOnDataLinkExecutionFinished OnExecutionFinished;` — Delegate called when data link execution has finished completely

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkExecutorObject.h` (Public)


#### class `UDataLinkExecutorObject`  
`class UDataLinkExecutorObject : public UObject`  
_L19-64_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UObject`
- desc: UObject wrapper for Data Link Executor for Blueprint usage
- L25 _private prototype_ `bool IsRunning() const;` — `UFUNCTION(BlueprintPure, Category="Data Link")` — Returns whether there's an active data link execution happening
- L29 _private prototype_ `void Run();` — `UFUNCTION(BlueprintCallable, Category="Data Link")` — Executes the Data Link Instance, stopping the existing active execution if any
- L33 _private prototype_ `void Stop();` — `UFUNCTION(BlueprintCallable, Category="Data Link")` — Stops an existing data link execution if active
- L37 _protected prototype_ `void NotifyOutputDataReceived(const FDataLinkExecutor& InExecutor, FConstStructView InOutputDataView);` — Called when data has been received. Calls the OnOutputData delegate
- L40 _protected prototype_ `void NotifyExecutionFinished(const FDataLinkExecutor& InExecutor, EDataLinkExecutionResult InExecutionResult);` — Called when execution has finished. Calls the OnExecutionFinished delegate
- L44 _protected member_ `FDataLinkInstance DataLinkInstance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link", meta=(ExposeOnSpawn="true"))` — Data link graph and input data to execute
- L48 _protected member_ `FString ContextName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link", meta=(ExposeOnSpawn="true"), AdvancedDisplay)` — Additional context to identify the data link execution
- L52 _protected member_ `TScriptInterface<IDataLinkSinkProvider> SinkProvider;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link", meta=(ExposeOnSpawn="true"), AdvancedDisplay)` — Optional: Sink to use for cross execution storage
- L56 _protected member_ `FReceiveDataLinkOutputData OnOutputData;` — `UPROPERTY(BlueprintAssignable, Category="Data Link", meta=(HideInDetailPanel))` — Delegate called when data link execution has output data ready
- L60 _protected member_ `FReceiveDataLinkExecutionFinished OnExecutionFinished;` — `UPROPERTY(BlueprintAssignable, Category="Data Link", meta=(HideInDetailPanel))` — Delegate called when data link execution has finished completely
- L63 _protected member_ `TSharedPtr<FDataLinkExecutor> Executor;` — The underlying executor that this object wraps

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATALINK_API`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReceiveDataLinkOutputData, FInstancedStruct, OutputData);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReceiveDataLinkOutputData, FInstancedStruct, OutputData);`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReceiveDataLinkExecutionFinished, EDataLinkExecutionResult, Result);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReceiveDataLinkExecutionFinished, EDataLinkExecutionResult, Result);`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkGraph.h` (Public)


#### class `UDataLinkGraph`  
`class UDataLinkGraph : public UObject`  
_L20-90_
- reflection: `UCLASS(MinimalAPI, BlueprintType, DisplayName="Motion Design Data Link Graph")`
- inherits: `UObject`
- L29 _public prototype_ `int32 GetInputPinCount() const;` — Counts the number of input pins within the input node list that are not linked to other nodes
- L32 _public prototype_ `TArray<FDataLinkPinReference> GetInputPins() const;` — Retrieves the Input Pins from the input nodes that are not linked to other nodes
- L35 _public prototype_ `bool ForEachInputPin(TFunctionRef<bool(FDataLinkPinReference)> InFunction) const;` — Iterates the input pins from the input nodes that are not linked to other nodes. These serve as the 'input pin' for the graph
- L37 _public function_ `TConstArrayView<const UDataLinkNode*> GetInputNodes() const`
- L42 _public function_ `const UDataLinkNode* GetOutputNode() const`
- L47 _public function_ `FName GetOutputPinName() const`
- L53 _public function_ `UEdGraph* GetEdGraph() const`
- L58 _public function_ `static TMulticastDelegateRegistration<void(UDataLinkGraph*)>& OnGraphCompiled()`
- L66 _private member_ `static TMulticastDelegate<void(UDataLinkGraph*)> OnGraphCompiledDelegate;`
- L71 _private member_ `TArray<TObjectPtr<UDataLinkNode>> Nodes;` — `UPROPERTY()` — All the compiled nodes present in this graph
- L75 _private member_ `TArray<TObjectPtr<UDataLinkNode>> InputNodes;` — `UPROPERTY()` — The nodes that the graph starts off with
- L79 _private member_ `TObjectPtr<UDataLinkNode> OutputNode;` — `UPROPERTY()` — The node that provides the result data
- L83 _private member_ `FName OutputPinName;` — `UPROPERTY()` — Output Node Pin name that provides the result data
- L88 _private member_ `TObjectPtr<UEdGraph> EdGraph;` — `UPROPERTY()` — EdGraph used to compile the nodes in this graph

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATALINK_API`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkInputDataViewer.h` (Public)


#### struct `FDataLinkInputDataEntry`  
`struct FDataLinkInputDataEntry`  
_L9-24_
- L11 _public function_ `bool operator==(FName InInputName) const`
- L17 _public prototype_ `FString ToDebugString() const;` — Converts the input data to a string for debugging purposes
- L20 _public member_ `FName Name;` — Name of the Input Data
- L23 _public member_ `FConstStructView DataView;` — View to the Input Data

#### class `FDataLinkInputDataViewer`  
`class FDataLinkInputDataViewer`  
_L28-59_
- L33 _public prototype_ `explicit FDataLinkInputDataViewer(TConstArrayView<FDataLinkPin> InInputPins);`
- L35 _public prototype_ `FConstStructView Find(FName InInputName) const;`
- L37 _public function_ `int32 Num() const`
- L43 _public function_ `template<typename T> const T& Get(FName InInputName) const`
- L48 _public prototype_ `TConstArrayView<FDataLinkInputDataEntry> GetDataEntries() const;`
- L51 _public prototype_ `FString ToDebugString() const;` — Converts the output data to a string for debugging purposes
- L54 _private prototype_ `bool HasInvalidDataEntry() const;`
- L56 _private prototype_ `void SetEntryData(const FDataLinkPin& InPin, FConstStructView InInputDataView);`
- L58 _private member_ `TArray<FDataLinkInputDataEntry> DataEntries;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DATALINK_API`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkInstance.h` (Public)


#### struct `FDataLinkInputData`  
`struct FDataLinkInputData`  
_L15-28_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes an Input Entry to the Data Link
- L19 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& InPropertyTag, FStructuredArchive::FSlot InSlot);`
- L23 _public member_ `FText DisplayName;` — `UPROPERTY(VisibleAnywhere, Category="Data Link")` — The display name of the input data
- L27 _public member_ `FInstancedStruct Data;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link", meta=(StructTypeConst))` — The input data to feed into the data link graph

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDataLinkInputData> : public TStructOpsTypeTraitsBase2<FDataLinkInputData>`  
_L31-37_
- inherits: `TStructOpsTypeTraitsBase2<FDataLinkInputData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L34-36_

#### struct `FDataLinkInstance`  
`struct FDataLinkInstance`  
_L41-55_
- reflection: `USTRUCT(BlueprintType)`
- desc: Instance of a data link to be executed
- L46 _public prototype_ `TArray<FConstStructView> GetInputDataViews() const;` — Converts the Input Data into an array of Const Struct Views
- L50 _public member_ `TObjectPtr<UDataLinkGraph> DataLinkGraph;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link")` — The data link graph to execute
- L54 _public member_ `TArray<FDataLinkInputData> InputData;` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite, Category="Data Link", meta=(EditFixedOrder))` — The initial input data to feed into the data link graph

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATALINK_API`
- L35 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon20981e730103`)

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataLink, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataLink, Log, All);`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkNames.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DataLink` (scope `UE`)
- L9 _variable_ `const FLazyName InputDefault(TEXT("Inpu` (scope `UE::DataLink`)
- L10 _variable_ `const FLazyName OutputDefault(TEXT("Outp` (scope `UE::DataLink`)

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkNode.h` (Public)


#### class `UDataLinkNode`  
`class UDataLinkNode : public UObject`  
_L26-104_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Base class for nodes in a data link graph, that handles the logic of the node. The instance data of the node can be gotten through the FDataLinkExecutor. Each node consists of an Input struct, and an Output struct. A data link node can be connected to another so long as the output struct of one is compatible with the input struct of the other.
- L33 _public prototype_ `void Execute(FDataLinkExecutor& InExecutor) const;`
- L36 _public prototype_ `void Stop(const FDataLinkExecutor& InExecutor) const;` — Called when the node is still executing and is forced to stop execution and clean up its resources
- L38 _public function_ `TConstArrayView<FDataLinkPin> GetInputPins() const`
- L43 _public function_ `TConstArrayView<FDataLinkPin> GetOutputPins() const`
- L48 _public function_ `const UScriptStruct* GetInstanceStruct() const`
- L55 _public prototype_ `void FixupNode();` — Called when the node has been compiled to fix data to be valid to use at runtime
- L56 _public prototype_ `void BuildMetadata(FDataLinkNodeMetadata& OutMetadata) const;`
- L59 _public prototype_ `void BuildPins(TArray<FDataLinkPin>& OutInputPins, TArray<FDataLinkPin>& OutOutputPins) const;`
- L63 _protected function_ `virtual void OnFixupNode()`
- L68 _protected function_ `virtual void OnBuildMetadata(FDataLinkNodeMetadata& Metadata) const` — Call to retrieve the metadata for this node
- L74 _protected function_ `virtual void OnBuildPins(FDataLinkPinBuilder& Inputs, FDataLinkPinBuilder& Outputs) const` — Call to setup the pins required by this node
- L82 _protected function_ `virtual EDataLinkExecutionReply OnExecute(FDataLinkExecutor& InExecutor) const` — Execution logic of the node @return whether the implementation handled the execution (regardless if it has finished or not)
- L88 _protected function_ `virtual void OnStop(const FDataLinkExecutor& InExecutor) const` — Called when the node is still executing and is forced to stop execution and clean up its resources
- L94 _protected member_ `TObjectPtr<const UScriptStruct> InstanceStruct;` — `UPROPERTY()` — Optional instance data struct for data outside input and output
- L99 _private member_ `TArray<FDataLinkPin> InputPins;` — `UPROPERTY()` — Input Pins to start the execution on this Data Link node
- L103 _private member_ `TArray<FDataLinkPin> OutputPins;` — `UPROPERTY()` — Output pins that feed the result of this node's execution

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATALINK_API`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkNodeInstance.h` (Public)


#### enum `EDataLinkNodeStatus`  
`enum class EDataLinkNodeStatus : uint8`  
_L13-17_
- L15 _public enumerator_ `NotStarted`
- L16 _public enumerator_ `Executing`

#### struct `FDataLinkNodeInstance`  
`struct FDataLinkNodeInstance`  
_L19-73_
- L23 _public prototype_ `explicit FDataLinkNodeInstance(const UDataLinkNode& InNode);`
- L25 _public prototype_ `void AddReferencedObjects(FReferenceCollector& InCollector);`
- L27 _public function_ `const FDataLinkInputDataViewer& GetInputDataViewer() const`
- L32 _public function_ `const FDataLinkOutputDataViewer& GetOutputDataViewer() const`
- L37 _public function_ `FConstStructView GetInstanceData() const`
- L42 _public function_ `FStructView GetInstanceDataMutable()`
- L47 _public function_ `const FDataLinkSinkKey& GetSinkKey() const`
- L57 _private member_ `FDataLinkSinkKey SinkKey;` — The Sink Key for this Node Instance Saved here to avoid recreating if it needs to be re-used.
- L60 _private member_ `FDataLinkInputDataViewer InputDataViewer;` — Views of the input data, matching the Node's Input Pins
- L63 _private member_ `FDataLinkOutputDataViewer OutputDataViewer;` — Views of the output data, matching the Node's Output Pins
- L69 _private member_ `FInstancedStruct InstanceData;` — Optional data within the node instanced for every execution. This is used to store data outside of the input/output data.
- L72 _private member_ `EDataLinkNodeStatus Status = EDataLinkNodeStatus::NotStarted;` — Current Status of a Node

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkNodeMetadata.h` (Public)


#### struct `FDataLinkNodeMetadata`  
`struct FDataLinkNodeMetadata`  
_L11-41_
- desc: Metadata of a Node for Editor-side representation.
- L13 _public function_ `FDataLinkNodeMetadata& SetDisplayName(const FText& InDisplayName)`
- L19 _public function_ `FDataLinkNodeMetadata& SetTooltipText(const FText& InDescription)`
- L25 _public function_ `const FText& GetDisplayName() const`
- L30 _public function_ `const FText& GetTooltipText() const`
- L37 _private member_ `FText DisplayName;` — Display name of the Node
- L40 _private member_ `FText TooltipText;` — Description for the node. Used for the Tooltip text of nodes

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkOutputDataViewer.h` (Public)


#### struct `FDataLinkOutputDataEntry`  
`struct FDataLinkOutputDataEntry`  
_L11-29_
- L13 _public function_ `bool operator==(FName InOutputName) const`
- L19 _public member_ `FName Name;` — Name of the Output Data
- L21 _public prototype_ `FStructView GetDataView(const UScriptStruct* InDesiredStruct) const;`
- L24 _public prototype_ `FString ToDebugString() const;` — Converts the output data to a string for debugging purposes
- L28 _private member_ `mutable FInstancedStruct OutputData;` — Output Data instantiated

#### class `FDataLinkOutputDataViewer`  
`class FDataLinkOutputDataViewer`  
_L31-53_
- L34 _public prototype_ `explicit FDataLinkOutputDataViewer(TConstArrayView<FDataLinkPin> InOutputPins);`
- L36 _public prototype_ `FStructView Find(FName InOutputName, const UScriptStruct* InDesiredStruct = nullptr) const;`
- L38 _public function_ `int32 Num() const`
- L44 _public function_ `template<typename T> T& Get(FName InOutputName) const`
- L49 _public prototype_ `FString ToDebugString() const;`
- L52 _private member_ `TArray<FDataLinkOutputDataEntry> DataEntries;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DATALINK_API`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkPin.h` (Public)


#### struct `FDataLinkPin`  
`struct FDataLinkPin`  
_L12-48_
- reflection: `USTRUCT()`
- L16 _public prototype_ `FDataLinkPin() = default;`
- L18 _public prototype_ `explicit FDataLinkPin(FName InPinName);`
- L20 _public prototype_ `const FDataLinkPin* GetLinkedInputPin() const;`
- L22 _public prototype_ `FText GetDisplayName() const;`
- L24 _public function_ `bool operator==(const FName InName) const`
- L31 _public member_ `FName Name;` — `UPROPERTY()` — Unique name for the Pin
- L35 _public member_ `FText DisplayName;` — `UPROPERTY()` — Display name of the Pin
- L39 _public member_ `TObjectPtr<const UScriptStruct> Struct;` — `UPROPERTY()` — Struct type of the Pin
- L43 _public member_ `TObjectPtr<const UDataLinkNode> LinkedNode;` — `UPROPERTY()` — The node this pin connects to
- L47 _public member_ `int32 LinkedIndex = INDEX_NONE;` — `UPROPERTY()` — the pin index at which this pin connects to the linked node (to find linked pin)

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkPinBuilder.h` (Public)


#### struct `FDataLinkPinParameters`  
`struct FDataLinkPinParameters`  
_L9-33_
- desc: Short-lived parameter building for a single pin
- L11 _public prototype_ `explicit FDataLinkPinParameters(FDataLinkPin& InPin);`
- L17 _public prototype_ `FDataLinkPinParameters& SetDisplayName(FText&& InPinDisplayName);` — Optionally sets the display text of the pin If not set, it will use the pin's unique name instead.
- L20 _public function_ `template<typename InStruct UE_REQUIRES(TModels_V<CStaticStructProvider, InStruct>)> FDataLinkPinParameters& SetStruct()`
- L29 _public prototype_ `FDataLinkPinParameters& SetStruct(const UScriptStruct* InPinStruct);` — Sets the struct of the pin. Can be left null for cases like output pins where the struct might not be known
- L32 _private member_ `FDataLinkPin& Pin;`

#### struct `FDataLinkPinBuilder`  
`struct FDataLinkPinBuilder`  
_L36-55_
- desc: Short-lived builder for pin arrays limiting to only add pins with unique names
- L38 _public prototype_ `explicit FDataLinkPinBuilder(TArray<FDataLinkPin>& OutPins);`
- L44 _public prototype_ `void AddCapacity(int32 InNumToAdd);` — Possibly re-allocates the array to ensure its capacity can hold the number of items to add without further re-allocations @param InNumToAdd the number of new elements to add
- L51 _public prototype_ `FDataLinkPinParameters Add(FName InPinName);` — Adds a new pin to the array with a given unique name @param InPinName the unique name of the pin @return parameter object to further customize the pin
- L54 _private member_ `TArray<FDataLinkPin>& Pins;`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkPinReference.h` (Public)


#### struct `FDataLinkPinReference`  
`struct FDataLinkPinReference`  
_L11-22_
- desc: Short-lived data containing a pin reference with the Node that owns it.
- L13 _public function_ `explicit FDataLinkPinReference(const UDataLinkNode* InOwningNode, const FDataLinkPin* InPin) : OwningNode(InOwningNode) , Pin(InPin)`
- L19 _public member_ `TObjectPtr<const UDataLinkNode> OwningNode;`
- L21 _public member_ `const FDataLinkPin* Pin = nullptr;`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkProcessor.h` (Public)


#### class `UDataLinkProcessor`  
`class UDataLinkProcessor : public UObject`  
_L14-40_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew)`
- inherits: `UObject`
- desc: Processors execute logic on the output data of a data link graph execution
- L20 _public prototype_ `void Initialize(const FDataLinkExecutor& InExecutor);` — Called at the start of the data link graph execution, prior to running any data link node
- L23 _public prototype_ `void ProcessOutput(const FDataLinkExecutor& InExecutor, FConstStructView InOutputDataView);` — Called when the data link graph execution has output data
- L26 _public prototype_ `void Finalize(const FDataLinkExecutor& InExecutor, EDataLinkExecutionResult InExecutionResult);` — Called at the end of the data link graph execution
- L29 _protected function_ `virtual void OnInitialize(const FDataLinkExecutor& InExecutor)`
- L33 _protected function_ `virtual void OnProcessOutput(const FDataLinkExecutor& InExecutor, FConstStructView InOutputDataView)`
- L37 _protected function_ `virtual void OnFinalize(const FDataLinkExecutor& InExecutor, EDataLinkExecutionResult InExecutionResult)`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkProcessorBlueprint.h` (Public)


#### class `UDataLinkProcessorBlueprint`  
`class UDataLinkProcessorBlueprint : public UDataLinkProcessor`  
_L9-49_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable)`
- inherits: `UDataLinkProcessor`
- L15 _public prototype_ `UObject* GetContextObject() const;` — `UFUNCTION(BlueprintPure, Category="Data Link")`
- L19 _public prototype_ `void Initialize();` — `UFUNCTION(BlueprintImplementableEvent)` — Called at the start of the data link graph execution, prior to running any data link node
- L23 _public prototype_ `void ProcessOutput(const FInstancedStruct& InOutputData);` — `UFUNCTION(BlueprintImplementableEvent)` — Called when the data link graph execution has output data
- L27 _public prototype_ `void Finalize(EDataLinkExecutionResult InExecutionResult);` — `UFUNCTION(BlueprintImplementableEvent)` — Called at the end of the data link graph execution
- L31 _protected prototype_ `virtual void OnInitialize(const FDataLinkExecutor& InExecutor);`
- L32 _protected prototype_ `virtual void OnProcessOutput(const FDataLinkExecutor& InExecutor, FConstStructView InOutputDataView) override;`
- L33 _protected prototype_ `virtual void OnFinalize(const FDataLinkExecutor& InExecutor, EDataLinkExecutionResult InExecutionResult) override;`
- L37 _protected prototype_ `virtual UWorld* GetWorld() const override;`
- L45 _protected member_ `FInstancedStruct OutputData;` — `UPROPERTY()` — Cached output data to avoid memory allocation if the output keeps being the same struct. Only reallocs if struct mismatches. Unlike FConstStructView FInstancedStruct is supported in Blueprints.
- L48 _protected member_ `TWeakPtr<const FDataLinkExecutor> ExecutorWeak;` — Object responsible for the execution

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkRequestProxy.h` (Public)


#### class `UDataLinkRequestProxy`  
`class UE_DEPRECATED(5.7, "Data Link Request Proxy deprecated. Use Data Link Executor Object instead") UDataLinkRequestProxy : public UObject`  
_L17-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L23 _public member_ `FOnDataLinkOutputDataProxy OnOutputData;` — `UPROPERTY(BlueprintAssignable)`
- L28 _public prototype_ `static UDataLinkRequestProxy* CreateRequestProxy(FDataLinkInstance InDataLinkInstance , UObject* InExecutionContext , TScriptInterface<IDataLinkSinkProvider> InDataLinkSinkProvider);` — `UE_DEPRECATED(5.7, "Data Link Request Proxy deprecated. Use Data Link Executor Object instead")` — `UFUNCTION(BlueprintCallable, Category="Data Link", meta=(BlueprintInternalUseOnly))`
- L33 _public prototype_ `void ProcessRequest(FDataLinkInstance&& InDataLinkInstance , UObject* InExecutionContext , TScriptInterface<IDataLinkSinkProvider> InDataLinkSinkProvider);`
- L38 _private prototype_ `void OnOutputDataReceived(const FDataLinkExecutor& InExecutor, FConstStructView InOutputData);`
- L40 _private member_ `TSharedPtr<FDataLinkExecutor> DataLinkExecutor;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDataLinkOutputDataProxy, const FInstancedStruct&, OutputData, EDataLinkExecutionResult, ExecutionResult);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDataLinkOutputDataProxy, const FInstancedStruct&, OutputData, EDataLinkExecutionResult, ExecutionResult);`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkSink.h` (Public)


#### struct `FDataLinkSinkKey`  
`struct FDataLinkSinkKey`  
_L15-34_
- desc: Struct used as the Key to access the data for a given node and input data
- L17 _public prototype_ `FDataLinkSinkKey() = default;`
- L19 _public prototype_ `explicit FDataLinkSinkKey(TSubclassOf<UDataLinkNode> InNodeClass, const FDataLinkInputDataViewer& InInputDataViewer);`
- L21 _public prototype_ `bool operator==(const FDataLinkSinkKey& InOther) const;`
- L27 _private member_ `FObjectKey NodeClass;` — Class of the node that this data will be used in
- L30 _private member_ `TArray<FDataLinkInputDataEntry, TInlineAllocator<2>> InputDataEntries;` — Views of the input data.
- L33 _private member_ `uint64 CachedHash = 0;` — Hash computed in ctor

#### struct `FDataLinkSink`  
`struct FDataLinkSink`  
_L37-61_
- desc: Sink that caches node data to be reusable by nodes with the same logic (i.e. "class") and input data
- L43 _public prototype_ `FInstancedStruct& FindOrAddCachedData(const FDataLinkNodeInstance& InNodeInstance, TOptional<const UScriptStruct*> InDesiredStruct = {});` — Returns the output data view that matches the node class and the settings within the input data view. @return a data view to the output data
- L46 _public function_ `template<typename T> T& FindOrAddCachedData(const FDataLinkNodeInstance& InNodeInstance)`
- L52 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& InCollector);`
- L60 _private member_ `TMap<FDataLinkSinkKey, FInstancedStruct> CachedDataMap;` — Map of the Node & Input Data to the Cached Data This stores output data for Input data regardless if it's hashable or not. For input data without a type hash implementation, it should return a type hash of 0, generating collisions that then should get the correct element via comparison.

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkSinkObject.h` (Public)


#### class `UDataLinkSinkObject`  
`class UDataLinkSinkObject : public UObject, public IDataLinkSinkProvider`  
_L12-29_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IDataLinkSinkProvider`
- L17 _public prototype_ `UDataLinkSinkObject();`
- L20 _public prototype_ `void ResetSink();` — `UFUNCTION(BlueprintCallable, Category="Data Link")`
- L23 _public prototype_ `virtual TSharedPtr<FDataLinkSink> GetSink() const override;`
- L24 _public prototype_ `virtual const UDataLinkSinkObject* GetSinkObject_Implementation() const override;`
- L28 _private member_ `TSharedPtr<FDataLinkSink> Sink;`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/DataLinkUtils.h` (Public)


#### struct `UE::DataLink::FConstPropertyView`  
`struct FConstPropertyView`  
_L50-54_
- L52 _public member_ `const FProperty* Property = nullptr;`
- L53 _public member_ `const uint8* Memory = nullptr;`

#### struct `UE::DataLink::FPropertyView`  
`struct FPropertyView`  
_L64-68_
- L66 _public member_ `FProperty* Property = nullptr;`
- L67 _public member_ `uint8* Memory = nullptr;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API DATALINK_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace DataLink` (scope `UE`)
- L32 _prototype_ `bool CopyDataView(FStructView InDestView, FConstStructView InSourceView);` (scope `UE::DataLink`) — Copies a given source view into dest view if the script structs match @param InDestView the struct view to copy to @param InSourceView the struct view to copy from @return true if the struct views were compatible and the copy was performed
- L41 _prototype_ `bool ReplaceObject(UObject*& InOutObject, UObject* InOuter, UClass* InClass);` (scope `UE::DataLink`) — Replaces a given Object with a new object with the same name but different class @param InOutObject object to replace. Can come in as null @param InOuter outer of the object. Must be valid. @param InClass new class of the new object that will replace the older one @return true if the operation took place, false otherwise
- L48 _prototype_ `TSharedPtr<FDataLinkSink> TryGetSink(TScriptInterface<IDataLinkSinkProvider> InSinkProvider);` (scope `UE::DataLink`) — Attempts to get the underlying Sink from the given Sink Provider @param InSinkProvider the sink provider interface @return the sink if found
- L62 _prototype_ `FConstPropertyView ResolveConstPropertyView(FConstStructView InBaseStructView, const FString& InPropertyPath, FString* OutError = nullptr);` (scope `UE::DataLink`) — Sets the input data to match the current graph's inputs @param InBaseStructView the base struct to start looking for the property path @param InPropertyPath the property path to look for @param OutError optional error message if property returns null @return the resolved property view (property and memory ptr)
- L76 _prototype_ `FPropertyView ResolvePropertyView(FStructView InBaseStructView, const FString& InPropertyPath, FString* OutError = nullptr);` (scope `UE::DataLink`) — Sets the input data to match the current graph's inputs @param InBaseStructView the base struct to start looking for the property path @param InPropertyPath the property path to look for @param OutError optional error message if property returns null @return the resolved property view (property and memory ptr)
- L83 _prototype_ `void SetInputData(UDataLinkGraph* InGraph, TArray<FDataLinkInputData>& OutInputData);` (scope `UE::DataLink`) — Sets the input data to match the current graph's inputs @param InGraph the data link graph to get the input pins to update from @param OutInputData the input data to update
- L86 _prototype_ `FString StructViewToDebugString(FConstStructView InDataView);` (scope `UE::DataLink`) — Converts the given struct data view to a debug string

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/IDataLinkSinkProvider.h` (Public)


#### class `UDataLinkSinkProvider`  
`class UDataLinkSinkProvider : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IDataLinkSinkProvider`  
`class IDataLinkSinkProvider`  
_L17-29_
- L23 _public prototype_ `const UDataLinkSinkObject* GetSinkObject() const;` — `UFUNCTION(BlueprintNativeEvent, Category="Data Link")`
- L25 _public function_ `virtual TSharedPtr<FDataLinkSink> GetSink() const`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/Nodes/DataLinkConstant.h` (Public)


#### class `UDataLinkConstant`  
`class UDataLinkConstant : public UDataLinkNode`  
_L11-34_
- reflection: `UCLASS(MinimalAPI, DisplayName="Constant", Category="Core")`
- inherits: `UDataLinkNode`
- desc: Constants are a no-input node that provide a struct instance that does not change in execution time
- L16 _public prototype_ `void SetStruct(const UScriptStruct* InStructType);`
- L21 _protected prototype_ `virtual void OnFixupNode() override;`
- L22 _protected prototype_ `virtual void OnBuildMetadata(FDataLinkNodeMetadata& Metadata) const override;`
- L24 _protected prototype_ `virtual void OnBuildPins(FDataLinkPinBuilder& Inputs, FDataLinkPinBuilder& Outputs) const override;`
- L25 _protected prototype_ `virtual EDataLinkExecutionReply OnExecute(FDataLinkExecutor& InExecutor) const override;`
- L30 _private member_ `FText DisplayName;` — `UPROPERTY(EditAnywhere, Category="Data Link", meta=(InvalidatesNode))`
- L33 _private member_ `FInstancedStruct Instance;` — `UPROPERTY(EditAnywhere, Category="Data Link", meta=(InvalidatesNode))`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/Nodes/Script/DataLinkScriptNode.h` (Public)


#### struct `FDataLinkScriptPin`  
`struct FDataLinkScriptPin`  
_L11-22_
- reflection: `USTRUCT()`
- L17 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "DataLink")` — Unique name for the Pin
- L21 _public member_ `TObjectPtr<const UScriptStruct> Struct;` — `UPROPERTY(EditAnywhere, Category = "DataLink")` — Struct type of the Pin

#### class `UDataLinkScriptNode`  
`class UDataLinkScriptNode : public UObject`  
_L31-92_
- reflection: `UCLASS(Abstract, MinimalAPI, Blueprintable)`
- inherits: `UObject`
- desc: Script Nodes are a Blueprint Implementation of a Data Link Node. It does not inherit from UDataLinkNode, as the wrapper does this and forwards the logic execution here. This is done to allow for blueprints mutable nature (e.g. allowing users to set variables) @see UDataLinkScriptNodeWrapper
- L38 _public prototype_ `void Execute(const UDataLinkNode* InNode, FDataLinkExecutor& InExecutor);`
- L40 _public prototype_ `void Stop();`
- L43 _public prototype_ `void OnExecute();` — `UFUNCTION(BlueprintImplementableEvent)`
- L46 _public prototype_ `void OnStop();` — `UFUNCTION(BlueprintImplementableEvent)`
- L53 _public prototype_ `bool Succeed(const FInstancedStruct& OutputData, bool bPersistExecution);` — `UFUNCTION(BlueprintCallable, Category="Data Link", DisplayName="Succeed")` — Called to move to the next node to execute (or finish if last node) providing the output data as an instanced struct Set Persist Execution to true so that the graph does not finish, but keeps pushing data.
- L57 _public prototype_ `bool SucceedWildcard(int32 OutputData, bool bPersistExecution);` — `UFUNCTION(BlueprintCallable, CustomThunk, Category="Data Link", DisplayName="Succeed (Wildcard)", meta=(CustomStructureParam="OutputData"))` — Called to move to the next node to execute (or finish if last node) and providing the output data as a wildcard
- L61 _public prototype_ `void Fail();` — `UFUNCTION(BlueprintCallable, Category="Data Link")` — Called to fail execution
- L65 _public prototype_ `bool GetInputData(FInstancedStruct& InputData, FName InputName) const;` — `UFUNCTION(BlueprintCallable, Category="Data Link", DisplayName="Get Input Data")` — Retrieves the input data as an Instanced Struct
- L69 _public prototype_ `bool GetInputDataWildcard(int32& InputData, FName InputName) const;` — `UFUNCTION(BlueprintCallable, CustomThunk, Category="Data Link", DisplayName="Get Input Data (Wildcard)", meta=(CustomStructureParam="InputData"))` — Retrieves the input data as a Wildcard
- L73 _protected prototype_ `virtual UWorld* GetWorld() const override;`
- L77 _private prototype_ `UObject* GetContextObject() const;`
- L83 _private member_ `TArray<FDataLinkScriptPin> InputPins;` — `UPROPERTY(EditDefaultsOnly, Category="Data Link")`
- L86 _private member_ `FDataLinkScriptPin OutputPin;` — `UPROPERTY(EditDefaultsOnly, Category="Data Link")`
- L89 _private member_ `TObjectPtr<const UDataLinkNode> Node;` — `UPROPERTY()`
- L91 _private member_ `TWeakPtr<FDataLinkExecutor> ExecutorWeak;`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/Nodes/Script/DataLinkScriptNodeWrapper.h` (Public)


#### struct `FDataLinkScriptNodeInstance`  
`struct FDataLinkScriptNodeInstance`  
_L15-21_
- reflection: `USTRUCT()`
- desc: Wrapper struct for the Node Instance containing the actual blueprint implementation of the data link logic
- L20 _public member_ `TObjectPtr<UDataLinkScriptNode> Node;` — `UPROPERTY()`

#### class `UDataLinkScriptNodeWrapper`  
`class UDataLinkScriptNodeWrapper : public UDataLinkNode`  
_L30-67_
- reflection: `UCLASS(MinimalAPI, DisplayName="Blueprint Node", meta=(Hidden))`
- inherits: `UDataLinkNode`
- desc: Wrapper to the actual blueprint implementation of the node. Data Link Nodes are by-design immutable in execution, and only modify input/output/instance data provided by the executor. Data Link Script Nodes are mutable (like typical blueprints) so their actual implementation (UDataLinkScriptNode) is instanced in every execution @see UDataLinkScriptNode
- L35 _public prototype_ `UDataLinkScriptNodeWrapper();`
- L37 _public function_ `static FName GetNodeClassPropertyName()`
- L42 _public prototype_ `void SetNodeClass(TSubclassOf<UDataLinkScriptNode> InNodeClass);`
- L47 _protected prototype_ `virtual void OnBuildMetadata(FDataLinkNodeMetadata& Metadata) const override;`
- L49 _protected prototype_ `virtual void OnBuildPins(FDataLinkPinBuilder& Inputs, FDataLinkPinBuilder& Outputs) const override;`
- L50 _protected prototype_ `virtual EDataLinkExecutionReply OnExecute(FDataLinkExecutor& InExecutor) const override;`
- L51 _protected prototype_ `virtual void OnStop(const FDataLinkExecutor& InExecutor) const override;`
- L55 _private prototype_ `UDataLinkScriptNode* GetDefaultNode() const;`
- L62 _private member_ `TSubclassOf<UDataLinkScriptNode> NodeClass;` — `UPROPERTY(meta=(InvalidatesNode))` — The node class to instantiate. The selected node class determines the pins of this node.
- L66 _private member_ `TObjectPtr<UDataLinkScriptNode> TemplateNode;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Data Link")` — Instance of Node Class serving as template for the execution instances

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATALINK_API`

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/Nodes/String/DataLinkNodeStringBuilder.h` (Public)


#### class `UDataLinkNodeStringBuilder`  
`class UDataLinkNodeStringBuilder : public UDataLinkNode`  
_L11-35_
- reflection: `UCLASS(MinimalAPI, DisplayName="String Builder", Category="Core")`
- inherits: `UDataLinkNode`
- desc: Builder Node to help form a more complex string with parameters
- L17 _protected prototype_ `virtual void OnBuildPins(FDataLinkPinBuilder& Inputs, FDataLinkPinBuilder& Outputs) const override;`
- L18 _protected prototype_ `virtual EDataLinkExecutionReply OnExecute(FDataLinkExecutor& InExecutor) const override;`
- L23 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L30 _private member_ `TArray<FString> Segments;` — `UPROPERTY(EditAnywhere, Category="Data Link", meta=(InvalidatesNode))` — The Segments to build, where a token can be defined as {Token Name} in its own isolated entry
- L34 _private member_ `TArray<FDataLinkStringBuilderToken> Tokens;` — `UPROPERTY()` — The tokens found within the Segment Array

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/Nodes/String/DataLinkReplaceString.h` (Public)


#### struct `FDataLinkReplaceStringEntry`  
`struct FDataLinkReplaceStringEntry`  
_L16-27_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `FString Pattern;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link Replace")` — The regex pattern to match
- L26 _public member_ `FString Replacement;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link Replace")` — The replacement string, can use capture groups with $ (e.g. $1)

#### struct `FDataLinkReplaceStringSettings`  
`struct FDataLinkReplaceStringSettings`  
_L30-37_
- reflection: `USTRUCT(BlueprintType)`
- L36 _public member_ `TArray<FDataLinkReplaceStringEntry> ReplaceEntries;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link Regex")` — Entries to run in order

#### class `UDataLinkReplaceString`  
`class UDataLinkReplaceString : public UDataLinkNode`  
_L41-50_
- reflection: `UCLASS(MinimalAPI, DisplayName="Replace String", Category="Core")`
- inherits: `UDataLinkNode`
- desc: Replaces a string multiple times with simple or regex patterns
- L47 _protected prototype_ `virtual void OnBuildPins(FDataLinkPinBuilder& Inputs, FDataLinkPinBuilder& Outputs) const override;`
- L48 _protected prototype_ `virtual EDataLinkExecutionReply OnExecute(FDataLinkExecutor& InExecutor) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATALINK_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DataLink` (scope `UE`)
- L12 _variable_ `const FLazyName InputReplaceSettings(TEXT("Inpu` (scope `UE::DataLink`)

### `Plugins/VirtualProduction/DataLink/Source/DataLink/Public/Nodes/String/DataLinkStringBuilder.h` (Public)


#### struct `FDataLinkStringBuilderToken`  
`struct FDataLinkStringBuilderToken`  
_L16-27_
- reflection: `USTRUCT()`
- L22 _public member_ `FName Name;` — `UPROPERTY()` — Name of the token. Used to build the Input Pin
- L26 _public member_ `TArray<int32> Indices;` — `UPROPERTY()` — The indices this token is located in the Segment array

#### struct `FDataLinkStringBuilder`  
`struct FDataLinkStringBuilder`  
_L33-53_
- desc: Logic for String building for re-usability between different nodes without needing to inherit from each other @see UDataLinkNodeStringBuilder
- L35 _public function_ `explicit FDataLinkStringBuilder(TConstArrayView<FString> InSegments, TConstArrayView<FDataLinkStringBuilderToken> InTokens) : Segments(InSegments) , Tokens(InTokens)`
- L41 _public prototype_ `bool BuildString(const FDataLinkInputDataViewer& InTokenValues, FString& InOutResult) const;`
- L43 _public prototype_ `void BuildInputPins(FDataLinkPinBuilder& Inputs) const;`
- L45 _public prototype_ `static void GatherTokens(TConstArrayView<FString> InSegments, TArray<FDataLinkStringBuilderToken>& OutTokens);`
- L48 _private prototype_ `void ForEachResolvedSegment(const FDataLinkInputDataViewer& InTokenValues, TFunctionRef<void(FStringView InResolvedSegment)> InFunction) const;`
- L50 _private member_ `TConstArrayView<FString> Segments;`
- L52 _private member_ `TConstArrayView<FDataLinkStringBuilderToken> Tokens;`
