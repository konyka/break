# Plugins / GeometryFlowCore

- module root: `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore`
- headers: 17; symbols: 462
- symbol kinds: class=24, enum=4, enumerator=32, function=159, macro=18, member=58, namespace=41, prototype=96, struct=17, typedef=13
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine
- PublicDependencyModuleNames: Core, GeometryCore

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/BaseNodes/BinaryOpLambdaNode.h` (Public)


#### class `UE::GeometryFlow::TBinaryOpLambdaNode`  
`template<typename T, int StorageTypeIdentifier> class TBinaryOpLambdaNode : public FNode`  
_L17-74_
- inherits: `FNode`
- L20 _protected typedef_ `using DataType = TMovableData<T, StorageTypeIdentifier>;`
- L22 _protected member_ `TUniqueFunction<T(const T& A, const T& B)> OpFunc;`
- L25 _public function_ `static const FString InParamArg1()`
- L26 _public function_ `static const FString InParamArg2()`
- L27 _public function_ `static const FString OutParamResult()`
- L30 _protected function_ `TBinaryOpLambdaNode()`
- L39 _public function_ `TBinaryOpLambdaNode(TUniqueFunction<T(const T& A, const T& B)>&& OpFuncIn) : TBinaryOpLambdaNode()`
- L44 _public function_ `virtual void Evaluate( const FNamedDataMap& DatasIn, FNamedDataMap& DatasOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/BaseNodes/SwitchNode.h` (Public)


#### class `UE::GeometryFlow::TSwitchNode`  
`template<typename T, int NumInputs, int StorageTypeIdentifier> class TSwitchNode : public FNode`  
_L27-170_
- inherits: `FNode`
- desc: TSwitchNode selects one of N inputs and provides it as an Output. This allows for a minimal amount of branching / control-flow in a fixed GeometryFlow Graph. Only the active Input is evaluated. The number of inputs is defined in the template type, eg TSwitchNode<FDynamicMesh3, 3, (int)EMeshProcessingDataTypes::DynamicMesh> is a switch node with 3 possible inputs. Dynamic number of inputs cannot be easily supported without changes at the graph evaluation level. Use UpdateSwitchValue() to select the active switch Input
- L30 _private member_ `static constexpr int NodeVersion = 1;`
- L32 _public typedef_ `typedef FNode Super;`
- L33 _public function_ `static FName StaticType()`
- L38 _public function_ `virtual FName GetType() const override`
- L39 _public function_ `virtual bool IsA(FName InType) const override`
- L40 _public function_ `virtual int32 GetVersionID() const override`
- L43 _protected typedef_ `using DataContainerType = TMovableData<T, StorageTypeIdentifier>;`
- L45 _protected member_ `int32 SwitchIndex = 0;`
- L48 _public function_ `static const FString InParamValue(int32 InputNum)`
- L53 _public function_ `static const FString OutParamValue()`
- L56 _public function_ `TSwitchNode()`
- L79 _public function_ `virtual void UpdateSwitchInputIndex(const int32& NewSwitchIndex)` — This function is used to update the Input Index, ie select which Output will be provided. This function always Invalidates the Output if the Index was changed.
- L95 _public function_ `virtual void CollectRequirements(const TArray<FString>& Outputs, TArray<FEvalRequirement>& RequiredInputsOut) override` — Determine which Inputs are required for the desired Output. This replaces the default behavior ("all inputs") with only the selected Input returned as a Requirement, which in turn allows the Graph Evaluator to skip evaluation of the other inputs.
- L125 _public function_ `virtual void Evaluate( const FNamedDataMap& DatasIn, FNamedDataMap& DatasOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/BaseNodes/TransferNode.h` (Public)


#### class `UE::GeometryFlow::TTransferNode`  
`template<typename T, int StorageTypeIdentifier> class TTransferNode : public FNode`  
_L16-73_
- inherits: `FNode`
- L19 _protected typedef_ `using DataContainerType = TMovableData<T, StorageTypeIdentifier>;`
- L22 _public function_ `static const FString InParamValue()`
- L23 _public function_ `static const FString OutParamValue()`
- L26 _public function_ `TTransferNode()`
- L35 _public function_ `virtual void Evaluate( const FNamedDataMap& DatasIn, FNamedDataMap& DatasOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/BaseNodes/TransformerWithSettingsNode.h` (Public)


#### class `UE::GeometryFlow::TTransformerWithSettingsNode`  
`class TTransformerWithSettingsNode : public FNode`  
_L22-106_
- inherits: `FNode`
- L25 _protected typedef_ `using OutputDataType = TMovableData<OutputType, OutputDataTypeIdentifier>;`
- L28 _public function_ `static const FString InParamInput()`
- L29 _public function_ `static const FString InParamSettings()`
- L30 _public function_ `static const FString OutParamResult()`
- L33 _public function_ `TTransformerWithSettingsNode()`
- L48 _protected function_ `virtual void ComputeOutput( const FNamedDataMap& DatasIn, const SettingsType& SettingsIn, const InputType& InputIn, OutputType& OutputOut)`
- L57 _protected function_ `virtual void CheckAdditionalInputs(const FNamedDataMap& DatasIn, bool& bRecomputeRequired, bool& bAllInputsValid)`
- L66 _public function_ `virtual void Evaluate( const FNamedDataMap& DatasIn, FNamedDataMap& DatasOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/GeometryFlowCoreModule.h` (Public)


#### class `FGeometryFlowCoreModule`  
`class FGeometryFlowCoreModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/GeometryFlowCoreNodeRegistration.h` (Public)


#### struct `UE::GeometryFlow::FCoreNodeRegistration`  
`struct FCoreNodeRegistration`  
_L12-16_
- L15 _public prototype_ `static void RegisterNodes();` — function that registers the core nodes defined in GeometryFlowCore (mostly POD source nodes)

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/GeometryFlowCoreNodes.h` (Public)


#### struct `FInt32Setting`  
`struct FInt32Setting`  
_L11-18_
- reflection: `USTRUCT()`
- L14 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EDataTypes::Integer);`
- L17 _public member_ `int32 Value = 0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### struct `FFloatSetting`  
`struct FFloatSetting`  
_L21-28_
- reflection: `USTRUCT()`
- L24 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EDataTypes::Float);`
- L27 _public member_ `float Value = 0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### struct `FDoubleSetting`  
`struct FDoubleSetting`  
_L31-38_
- reflection: `USTRUCT()`
- L34 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EDataTypes::Double);`
- L37 _public member_ `double Value = 0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### struct `FVector3fSetting`  
`struct FVector3fSetting`  
_L42-49_
- reflection: `USTRUCT()`
- L45 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EDataTypes::Vector3f);`
- L48 _public member_ `FVector3f Value = FVector3f(0, 0, 0);` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### struct `FVector3dSetting`  
`struct FVector3dSetting`  
_L52-59_
- reflection: `USTRUCT()`
- L55 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EDataTypes::Vector3d);`
- L58 _public member_ `FVector3d Value = FVector3d(0, 0, 0);` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### struct `FNameSetting`  
`struct FNameSetting`  
_L63-70_
- reflection: `USTRUCT()`
- L66 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EDataTypes::Name);`
- L69 _public member_ `FName Value;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### Free symbols / members of external scopes

- L72 _namespace_ `namespace UE`
- L74 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/GeometryFlowGraph.h` (Public)


#### enum `UE::GeometryFlow::ENodeCachingStrategy`  
`enum class ENodeCachingStrategy`  
_L27-32_
- L29 _public enumerator_ `Default = 0`
- L30 _public enumerator_ `AlwaysCache = 1`
- L31 _public enumerator_ `NeverCache = 2`

#### class `UE::GeometryFlow::FGraph`  
`class FGraph`  
_L42-418_
- L46 _private member_ `static constexpr float SerializationVersion = 1.0;` — version used in serialization
- L50 _public prototype_ `~FGraph();`
- L52 _public function_ `float GetVersionID() const`
- L67 _public function_ `friend FArchive& operator<<(FArchive& Ar, FHandle& H)` — Serialization operator for FHandle @parm Ar Archive to serialize with. @param H  Handle to serialize. @returns Passing down serializing archive
- L96 _public function_ `friend FArchive& operator<<(FArchive& Ar, FConnection& C)` — Serialization operator for FConnection @parm Ar Archive to serialize with. @param C  Connection to serialize. @returns Passing down serializing archive
- L122 _public function_ `template <typename NodeType> bool CanAddNodeOfType()` — return @false if the node type is not registered
- L129 _public function_ `template <typename NodeType> FHandle AddNodeOfType(const FString& Identifier = FString(""), ENodeCachingStrategy CachingStrategy = ENodeCachingStrategy::Default)` — Add a node of specified type to the graph.  An invalid FHandle will be returned if failed (e.g. node type not registered)
- L136 _public prototype_ `FHandle AddNodeOfType( const FName TypeName, const FString& Identifier = FString(""), ENodeCachingStrategy CachingStrategy = ENodeCachingStrategy::Default);` — Add a node of specified type to the graph.  An invalid FHandle will be returned if failed (e.g. node type not registered)
- L142 _public function_ `void RemoveNode(const FHandle Handle)` — Note: once removed, any external handles to this node will be stale.
- L154 _public prototype_ `bool IsDependent(FHandle DependentNode, FHandle IndependentNode) const;` — returns true if DependentNode is dependent on IndependentNode in the graph. special cases: will return false if either handle is invalid, if both handles are the same (and valid) it will return true.
- L157 _public prototype_ `EGeometryFlowResult CanAddConnection(FHandle FromNode, FString FromOutput, FHandle ToNode, FString ToInput) const;` — returns EGeometryFlowResult::Ok if the Connection can be added, otherwise returns the reason for failure
- L159 _public prototype_ `EGeometryFlowResult AddConnection(FHandle FromNode, FString FromOutput, FHandle ToNode, FString ToInput);`
- L161 _public prototype_ `EGeometryFlowResult InferConnection(FHandle FromNode, FHandle ToNode);`
- L164 _public prototype_ `EGeometryFlowResult FindInputConnections(FHandle ToNode, TArray<FGraph::FConnection>& ConnectionsOut) const;` — find all the input connections for the specified node.
- L167 _public function_ `void RemoveNodeInputConnections(FHandle NodeHandle)` — remove input connections to the specifed node
- L178 _public function_ `void RemoveNodeOutputConnections(FHandle NodeHandle)` — remove all output connections to the specified node.
- L189 _public function_ `void RemoveNodeConnections(FHandle NodeHandle)` — remove all connections to the specified node.
- L195 _public prototype_ `EGeometryFlowResult RemoveConnectionForInput(FHandle ToNode, FString ToInput);`
- L197 _public prototype_ `TSet<FHandle> GetSourceNodes() const;`
- L198 _public prototype_ `TSet<FHandle> GetNodesWithNoConnectedInputs() const;`
- L201 _public function_ `template<typename T> EGeometryFlowResult EvaluateResult( FHandle Node, FString OutputName, T& Storage, int32 StorageTypeIdentifier, TUniquePtr<FEvaluationInfo>& EvaluationInfo, bool bTryTakeResult)`
- L216 _public function_ `bool CanEvaluate( FHandle Node, FString OutputName )`
- L226 _public function_ `template<typename NodeType> EGeometryFlowResult ApplyToNodeOfType( FHandle NodeHandle, TFunctionRef<void(NodeType&)> ApplyFunc)` — Applies the functor to the node as derived type if possible.
- L241 _public function_ `EGeometryFlowResult ApplyToNode( FHandle NodeHandle, TFunctionRef<void(FNode&)> ApplyFunc)` — Applies the functor to the node as FNode.
- L254 _public prototype_ `EGeometryFlowResult GetInputTypeForNode(FHandle NodeHandle, FString InputName, int32& Type) const;`
- L255 _public prototype_ `EGeometryFlowResult GetOutputTypeForNode(FHandle NodeHandle, FString OutputName, int32& Type) const;`
- L257 _public prototype_ `void ConfigureCachingStrategy(ENodeCachingStrategy NewStrategy);`
- L258 _public prototype_ `EGeometryFlowResult SetNodeCachingStrategy(FHandle NodeHandle, ENodeCachingStrategy Strategy);`
- L260 _public prototype_ `FString DebugDumpGraph(TFunction<bool(TSafeSharedPtr<FNode>)> IncludeNodeFn) const;`
- L276 _public prototype_ `void Serialize(FArchive& Ar);` — Serialize this graph to an archive.
- L289 _protected function_ `bool CanAddNodeOfType(const FName TypeName)`
- L296 _protected function_ `ENodeAddResult AddNodeOfType(const FName TypeName, const FHandle Handle, const FString& Identifier, ENodeCachingStrategy CachingStrategy)`
- L325 _protected function_ `template<typename T> EGeometryFlowResult EvaluateResultInternal( FHandle Node, FString OutputName, T& Storage, int32 StorageTypeIdentifier, TUniquePtr<FEvaluationInfo>& EvaluationInfo, bool bTryTakeResult)`
- L367 _protected member_ `int32 NodeCounter = 0;`
- L369 _protected member_ `ENodeCachingStrategy DefaultCachingStrategy = ENodeCachingStrategy::AlwaysCache;`
- L378 _protected member_ `TMap<FHandle, FNodeInfo> AllNodes;`
- L379 _protected member_ `TMap<FHandle, TSafeSharedPtr<FRWLock>> AllNodeLocks;`
- L381 _protected prototype_ `TSafeSharedPtr<FNode> FindNode(FHandle Handle) const;`
- L383 _protected prototype_ `ENodeCachingStrategy GetCachingStrategyForNode(FHandle NodeHandle) const;`
- L384 _protected prototype_ `TSafeSharedPtr<FRWLock> FindNodeLock(FHandle Handle) const;`
- L386 _protected member_ `TArray<FConnection> Connections;`
- L388 _protected prototype_ `EGeometryFlowResult FindConnectionForInput(FHandle ToNode, FString ToInput, FConnection& ConnectionOut) const;`
- L390 _protected prototype_ `int32 CountOutputConnections(FHandle FromNode, const FString& FromOutput) const;`
- L392 _protected prototype_ `TSafeSharedPtr<IData> ComputeOutputData( FHandle Node, FString OutputName, TUniquePtr<FEvaluationInfo>& EvaluationInfo, bool bStealOutputData = false);`
- L399 _protected prototype_ `bool CanComputeOutput( FHandle Node, FString OutputName);` — retrun @true if all the graph connections needed for this computation exist
- L408 _protected prototype_ `bool VistDependencies(FHandle NodeHandle, TFunctionRef<bool(FGraph::FHandle)> Vistor) const;` — Visits upstream dependencies for the specified node and calls the Visitor functor (in parallel) on each. Terminates if Vistor returns true, or if the upstream graph is exhausted. @return true if terminated by the Visitor.
- L410 _protected function_ `bool IsInCycle(FHandle NodeHandle)`
- L417 _protected member_ `FCriticalSection EvaluateLock;`

#### struct `UE::GeometryFlow::FGraph::FHandle`  
`struct FHandle`  
_L54-78_
- L56 _public member_ `static const int32 InvalidHandle = -1;`
- L57 _public member_ `int32 Identifier = InvalidHandle;`
- L58 _public function_ `bool operator==(const FHandle& OtherHandle) const`
- L74 _public function_ `void Serialize(FArchive& Ar)` — Serialize FHandle to an archive

#### struct `UE::GeometryFlow::FGraph::FConnection`  
`struct FConnection`  
_L82-118_
- L84 _public member_ `FHandle FromNode;`
- L85 _public member_ `FString FromOutput;`
- L86 _public member_ `FHandle ToNode;`
- L87 _public member_ `FString ToInput;`
- L103 _public function_ `void Serialize(FArchive& Ar)` — Serialize FHandle to an archive
- L111 _public function_ `bool operator==(const FConnection& Other) const`

#### enum `UE::GeometryFlow::FGraph::ENodeAddResult`  
`enum class ENodeAddResult`  
_L281-286_
- L283 _public enumerator_ `Success = 0`
- L284 _public enumerator_ `Failed_HandleExists = 1`
- L285 _public enumerator_ `Failed_UnregisteredType = 2`

#### struct `UE::GeometryFlow::FGraph::FNodeInfo`  
`struct FNodeInfo`  
_L371-376_
- L373 _public member_ `TSafeSharedPtr<FNode> Node;`
- L374 _public member_ `FName NodeTypeName = FName("Unk`
- L375 _public member_ `ENodeCachingStrategy CachingStrategy = ENodeCachingStrategy::Default;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYFLOWCORE_API`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryFlowGraph, Display, All);`
- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L169 _function_ `int32 index = Connections.IndexOfByPredicate([&](const FConnection& Conn) { return (Conn.ToNode == NodeHandle); });` (scope `UE::GeometryFlow::FGraph::RemoveNodeInputConnections`)
- L173 _function_ `index = Connections.IndexOfByPredicate([&](const FConnection& Conn) { return (Conn.ToNode == NodeHandle); });` (scope `UE::GeometryFlow::FGraph::RemoveNodeInputConnections`)
- L180 _function_ `int32 index = Connections.IndexOfByPredicate([&](const FConnection& Conn) { return (Conn.FromNode == NodeHandle); });` (scope `UE::GeometryFlow::FGraph::RemoveNodeOutputConnections`)
- L184 _function_ `index = Connections.IndexOfByPredicate([&](const FConnection& Conn) { return (Conn.FromNode == NodeHandle); });` (scope `UE::GeometryFlow::FGraph::RemoveNodeOutputConnections`)
- L269 _function_ `friend FArchive& operator<<(FArchive& Ar, FGraph& Graph)` (scope `UE::GeometryFlow`) — Serialization operator for FGraph. @param Ar Archive to serialize with. @param Graph Graph to serialize. @returns Passing down serializing archive.
- L413 _function_ `auto Visitor = [this, Start](FGraph::FHandle UpstreamHandle)` (scope `UE::GeometryFlow::FGraph::IsInCycle`)
- L421 _function_ `inline uint32 GetTypeHash(FGraph::FHandle Handle)` (scope `UE::GeometryFlow`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/GeometryFlowGraphUtil.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L18 _function_ `template<typename SourceNodeType> void UpdateSourceNodeValue(FGraph& Graph, FGraph::FHandle NodeHandle, const typename SourceNodeType::CppType& NewValue)` (scope `UE::GeometryFlow`)
- L21 _function_ `` (scope `UE::GeometryFlow::UpdateSourceNodeValue`)
- L31 _function_ `template<typename SwitchNodeType> void UpdateSwitchNodeInputIndex(FGraph& Graph, FGraph::FHandle NodeHandle, int32 NewSwitchIndex)` (scope `UE::GeometryFlow`) — Update the integer index that controls which Input to a TSwitchNode will be provided as it's Output.
- L34 _function_ `` (scope `UE::GeometryFlow::UpdateSwitchNodeInputIndex`)
- L42 _function_ `template<typename SettingsType> void UpdateSettingsSourceNodeValue(FGraph& Graph, FGraph::FHandle NodeHandle, const SettingsType& NewSettings)` (scope `UE::GeometryFlow`)
- L44 _typedef_ `using SettingsSourceNodeType = TSourceNodeBase<SettingsType, SettingsType::DataTypeIdentifier>;` (scope `UE::GeometryFlow::UpdateSettingsSourceNodeValue`)
- L47 _function_ `` (scope `UE::GeometryFlow::UpdateSettingsSourceNodeValue`)
- L53 _function_ `inline int FindAnyConnectionFromNode(FGraph::FHandle FromNode, const TArray<FGraph::FConnection>& Connections)` (scope `UE::GeometryFlow`) — Returns an index into the Connections array or -1 if not found
- L67 _function_ `inline int FindAnyConnectionToNode(FGraph::FHandle ToNode, const TArray<FGraph::FConnection>& Connections)` (scope `UE::GeometryFlow`) — Returns an index into the Connections array or -1 if not found
- L81 _function_ `inline TArray<int> FindAllConnectionsToNode(FGraph::FHandle ToNodeID, const TArray<FGraph::FConnection>& Connections)` (scope `UE::GeometryFlow`) — Returns an indices into the Connections array

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/GeometryFlowImmutableData.h` (Public)


#### class `UE::GeometryFlow::TImmutableData`  
`template<typename T, int32 DataTypeIdentifier> class TImmutableData : public IData`  
_L17-68_
- inherits: `IData`
- L20 _public member_ `TUniquePtr<const T> Data;`
- L22 _public function_ `TImmutableData()`
- L26 _public function_ `TImmutableData(TUniquePtr<const T>&& DataIn)`
- L31 _public function_ `virtual int32 GetPayloadType() const override`
- L36 _public function_ `virtual int64 GetPayloadBytes() const override`
- L42 _public function_ `virtual bool CopyData(void* StorageType, int32 AsType) const override`
- L48 _public function_ `virtual bool MoveDataOut(void* StorageType, int32 AsType) override`
- L58 _protected function_ `virtual const void* GetRawDataPointerUnsafe() const override` — This is used by IData::GetDataConstRef(). Should probably not be called in other contexts...
- L64 _protected function_ `const T& GetData() const`

#### class `UE::GeometryFlow::TImmutableNodeInput`  
`template<typename T, int32 StorageTypeIdentifier> class TImmutableNodeInput : public INodeInput`  
_L75-88_
- inherits: `INodeInput`
- L79 _public function_ `virtual int32 GetDataType() const`
- L83 _public function_ `virtual bool CanTransformInput() const override`

#### class `UE::GeometryFlow::TImmutableNodeOutput`  
`template<typename T, int32 StorageTypeIdentifier> class TImmutableNodeOutput final : public INodeOutput`  
_L94-104_
- inherits: `INodeOutput`
- L97 _public function_ `TImmutableNodeOutput()`
- L103 _public function_ `virtual int32 GetDataType() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L10 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/GeometryFlowMovableData.h` (Public)


#### struct `UE::GeometryFlow::TSerializationMethod`  
`template <typename DataType> struct TSerializationMethod`  
_L19-22_
- desc: This must be specialized for new data types. see GeometryFlowTSourceNode.h for example
- L21 _public prototype_ `static void Serialize(FArchive& Ar, DataType& T);`

#### class `UE::GeometryFlow::TMovableData`  
`template<typename T, int32 DataTypeIdentifier> class TMovableData : public IData`  
_L27-103_
- inherits: `IData`
- L29 _private typedef_ `typedef IData Super;`
- L31 _public member_ `T Data;`
- L33 _public function_ `TMovableData()`
- L37 _public function_ `TMovableData(const T& InitialValue)`
- L42 _public function_ `virtual int32 GetPayloadType() const override`
- L47 _public function_ `virtual int64 GetPayloadBytes() const override`
- L52 _public function_ `virtual bool CopyData(void* StorageType, int32 AsType) const override`
- L62 _public function_ `virtual bool MoveDataOut(void* StorageType, int32 AsType) override`
- L73 _protected function_ `virtual const void* GetRawDataPointerUnsafe() const override`
- L81 _public function_ `void GetData(T& DataOut) const`
- L86 _public function_ `void SetData(const T& DataIn)`
- L92 _public function_ `void MoveData(T&& DataIn)`
- L98 _public function_ `void Serialize(FArchive& Ar)`

#### class `UE::GeometryFlow::TBasicNodeInput`  
`template<typename T, int32 StorageTypeIdentifier> class TBasicNodeInput : public INodeInput`  
_L110-115_
- inherits: `INodeInput`
- L114 _public function_ `virtual int32 GetDataType() const`

#### class `UE::GeometryFlow::TBasicNodeOutput`  
`template<typename T, int32 StorageTypeIdentifier> class TBasicNodeOutput final : public INodeOutput`  
_L121-131_
- inherits: `INodeOutput`
- L124 _public function_ `TBasicNodeOutput()`
- L130 _public function_ `virtual int32 GetDataType() const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/GeometryFlowNode.h` (Public)


#### class `UE::GeometryFlow::IData`  
`class IData`  
_L29-89_
- L32 _public prototype_ `virtual ~IData() = default;`
- L34 _public prototype_ `virtual int32 GetPayloadType() const = 0;`
- L35 _public prototype_ `virtual int64 GetPayloadBytes() const = 0;`
- L36 _public prototype_ `virtual bool CopyData(void* StorageType, int32 AsType) const = 0;`
- L37 _public prototype_ `virtual bool MoveDataOut(void* StorageType, int32 AsType) = 0;`
- L40 _protected prototype_ `virtual const void* GetRawDataPointerUnsafe() const = 0;`
- L44 _public function_ `virtual bool IsSameType(const IData& OtherType)`
- L50 _public function_ `template<typename T> void GetDataCopy(T& DataOut, int32 AsType) const`
- L56 _public function_ `template<typename T> const T& GetDataConstRef(int32 AsType) const`
- L63 _public function_ `template<typename T> void GiveTo(T& DataOut, int32 AsType)`
- L69 _public function_ `virtual int32 GetTimestamp() const`
- L75 _protected member_ `int32 Timestamp = 0;`
- L79 _protected function_ `virtual void IncrementTimestamp()`
- L84 _protected function_ `virtual void SetMaxTimestamp(int32 ExternalTimestamp)`

#### struct `UE::GeometryFlow::FNodeInputFlags`  
`struct FNodeInputFlags`  
_L93-98_
- L95 _public member_ `bool bCanTransformInput = false;`
- L97 _public function_ `static FNodeInputFlags Transformable()`

#### class `UE::GeometryFlow::INodeInput`  
`class INodeInput`  
_L101-126_
- L104 _public prototype_ `virtual ~INodeInput() = default;`
- L110 _public prototype_ `virtual int32 GetDataType() const = 0;`
- L119 _public function_ `virtual FNodeInputFlags GetInputFlags() const`
- L120 _public function_ `virtual bool CanTransformInput() const`
- L122 _protected member_ `FNodeInputFlags InputFlags;`
- L123 _protected function_ `virtual void SetInputFlags(FNodeInputFlags SetFlags)`

#### class `UE::GeometryFlow::INodeOutput`  
`class INodeOutput`  
_L132-177_
- L135 _public prototype_ `virtual ~INodeOutput() = default;`
- L137 _public prototype_ `virtual int32 GetDataType() const = 0;`
- L139 _public function_ `virtual void UpdateOutput(TSafeSharedPtr<IData> NewData)`
- L149 _public function_ `virtual bool HasCachedOutput() const`
- L154 _public function_ `virtual void ClearOutputCache()`
- L159 _public function_ `virtual TSafeSharedPtr<IData> GetOutput() const`
- L165 _public function_ `virtual TSafeSharedPtr<IData> StealOutput()`
- L175 _protected member_ `int32 LastDataTimestamp = 0;`
- L176 _protected member_ `TSafeSharedPtr<IData> CachedValue;`

#### struct `UE::GeometryFlow::FDataFlags`  
`struct FDataFlags`  
_L181-184_
- L183 _public member_ `bool bIsMutableData = false;`

#### class `UE::GeometryFlow::FNamedDataMap`  
`class FNamedDataMap`  
_L187-245_
- L190 _protected member_ `TArray<FString> Names;`
- L191 _protected member_ `TArray<TSafeSharedPtr<IData>> Datas;`
- L192 _protected member_ `TArray<FDataFlags> DatasFlags;`
- L195 _public function_ `void Add(const FString& Name, FDataFlags Flags = FDataFlags())`
- L203 _public function_ `void Add(const FString& Name, TSafeSharedPtr<IData> Data, FDataFlags Flags = FDataFlags())`
- L211 _public function_ `bool Contains(const FString& Name) const`
- L213 _public function_ `const TArray<FString>& GetNames() const`
- L215 _public function_ `TSafeSharedPtr<IData> FindData(const FString& Name) const`
- L225 _public function_ `FDataFlags GetDataFlags(const FString& Name) const`
- L235 _public function_ `bool SetData(const FString& Name, TSafeSharedPtr<IData> Data)`

#### class `UE::GeometryFlow::FEvaluationInfo`  
`class FEvaluationInfo`  
_L250-269_
- L253 _public prototype_ `FEvaluationInfo();`
- L254 _public prototype_ `virtual ~FEvaluationInfo() = default;`
- L256 _public prototype_ `virtual void Reset();`
- L258 _public prototype_ `virtual void CountEvaluation(FNode* Node);`
- L259 _public function_ `int NumEvaluations() const`
- L261 _public prototype_ `virtual void CountCompute(FNode* Node);`
- L262 _public function_ `int NumComputes() const`
- L264 _public member_ `FProgressCancel* Progress = nullptr;`
- L267 _protected member_ `std::atomic<int> EvaluationsCount;`
- L268 _protected member_ `std::atomic<int> ComputesCount;`

#### struct `UE::GeometryFlow::FEvalRequirement`  
`struct FEvalRequirement`  
_L274-284_
- L276 _public member_ `FString InputName;`
- L277 _public member_ `FNodeInputFlags InputFlags;`
- L279 _public function_ `FEvalRequirement()`
- L280 _public function_ `FEvalRequirement(const FString& Name) : InputName(Name)`
- L282 _public function_ `FEvalRequirement(const FString& NameIn, FNodeInputFlags InputFlagsIn) : InputName(NameIn), InputFlags(InputFlagsIn)`

#### class `UE::GeometryFlow::FNode`  
`class FNode`  
_L288-440_
- L292 _public prototype_ `FNode() = default;`
- L293 _public prototype_ `FNode(const FNode&) = delete;`
- L294 _public prototype_ `FNode& operator=(const FNode&) = delete;`
- L295 _public prototype_ `FNode(FNode&&) = default;`
- L296 _public prototype_ `FNode& operator=(FNode&&) = default;`
- L297 _public prototype_ `virtual ~FNode() = default;`
- L301 _public function_ `static FName StaticType()` — --- Derived nodes should implement these quasi-RTTI methods using the provided macro GEOMETRYFLOW_NODE_RTTI()
- L302 _public function_ `virtual FName GetType() const`
- L303 _public function_ `virtual bool IsA(FName InType) const`
- L309 _public function_ `void SetIdentifier(const FString& IdentifierIn)`
- L310 _public function_ `const FString& GetIdentifier() const`
- L313 _public function_ `virtual int32 GetVersionID() const` — version number used for serialization - to allow for changes in node data.
- L314 _public function_ `virtual void Serialize(FArchive& Ar)`
- L334 _public prototype_ `EGeometryFlowResult GetInputType(FString Name, int32& TypeOut) const;`
- L335 _public prototype_ `EGeometryFlowResult GetOutputType(FString Name, int32& TypeOut) const;`
- L337 _public prototype_ `FNodeInputFlags GetInputFlags(FString InputName) const;`
- L339 _public prototype_ `virtual void EnumerateInputs(TFunctionRef<void(const FString& Name, const TUniquePtr<INodeInput>& Input)> EnumerateFunc) const;`
- L340 _public prototype_ `virtual void EnumerateOutputs(TFunctionRef<void(const FString& Name, const TUniquePtr<INodeOutput>& Output)> EnumerateFunc) const;`
- L342 _public prototype_ `virtual bool IsOutputAvailable(FString OutputName) const;`
- L344 _public prototype_ `virtual TSafeSharedPtr<IData> StealOutput(FString OutputName);`
- L346 _public prototype_ `TSafeSharedPtr<IData> GetOutput(const FString& OutputName) const;`
- L352 _public prototype_ `virtual void CollectRequirements( const TArray<FString>& Outputs, TArray<FEvalRequirement>& RequiredInputsOut);` — Find the list of named inputs that must be available to compute the named Outputs. By default will return all Inputs if any of the listed Outputs exists on this Node.
- L356 _public prototype_ `virtual void CollectAllRequirements(TArray<FEvalRequirement>& RequiredInputsOut);`
- L358 _public prototype_ `virtual void Evaluate( const FNamedDataMap& DatasIn, FNamedDataMap& DatasOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) = 0;`
- L363 _public function_ `virtual TSafeSharedPtr<IData> GetDefaultInputData(FString InputName) const`
- L375 _protected prototype_ `void AddInput(FString Name, TUniquePtr<INodeInput>&& Input, TSafeSharedPtr<IData> DefaultData = TSafeSharedPtr<IData>());` — derived types configure inputs and outputs in their constructor
- L376 _protected prototype_ `void AddOutput(FString Name, TUniquePtr<INodeOutput>&& Output);`
- L382 _protected member_ `FString Identifier;`
- L411 _protected prototype_ `virtual void SetOutput( const FString& OutputName, TSafeSharedPtr<IData> NewData );`
- L416 _protected prototype_ `virtual void ClearOutput(const FString& OutputName);`
- L417 _protected prototype_ `virtual void ClearAllOutputs();`
- L419 _protected member_ `TArray<FNodeInputInfo> NodeInputs;`
- L420 _protected member_ `TArray<FNodeOutputInfo> NodeOutputs;`
- L422 _protected member_ `TMap<FString, TSafeSharedPtr<IData>> InputDefaultValues;`
- L426 _protected prototype_ `void ConfigureInputFlags(const FString& InputName, FNodeInputFlags Flags);` — helper functions for setup
- L429 _protected prototype_ `bool IsInputDirty(FString Name, int32 NewTimestamp) const;` — helper functions for evaluation
- L430 _protected prototype_ `bool CheckIsInputDirtyAndUpdate(FString Name, int32 NewTimestamp);`
- L431 _protected prototype_ `void UpdateInputTimestamp(FString Name, int32 NewTimestamp);`
- L433 _protected prototype_ `TSafeSharedPtr<IData> FindAndUpdateInputForEvaluate(const FString& InputName, const FNamedDataMap& DatasIn, bool& bAccumModifiedOut, bool& bAccumValidOut);`
- L439 _protected function_ `virtual void UpdateVersion(FArchive& Ar, int32 SavedVersion)` — override this in derived node if the version number has been bumped

#### struct `UE::GeometryFlow::FNode::FNodeInputInfo`  
`struct FNodeInputInfo`  
_L384-396_
- L387 _public prototype_ `FNodeInputInfo() = default;` — explicitly non-copyable because of embedded TUniquePtr
- L388 _public prototype_ `FNodeInputInfo(const FNodeInputInfo&) = delete;`
- L389 _public prototype_ `FNodeInputInfo& operator=(const FNodeInputInfo&) = delete;`
- L390 _public prototype_ `FNodeInputInfo(FNodeInputInfo&&) = default;`
- L391 _public prototype_ `FNodeInputInfo& operator=(FNodeInputInfo&&) = default;`
- L393 _public member_ `FString Name;`
- L394 _public member_ `int32 LastTimestamp = -1;`
- L395 _public member_ `TUniquePtr<INodeInput> Input;`

#### struct `UE::GeometryFlow::FNode::FNodeOutputInfo`  
`struct FNodeOutputInfo`  
_L398-409_
- L401 _public prototype_ `FNodeOutputInfo() = default;` — explicitly non-copyable because of embedded TUniquePtr
- L402 _public prototype_ `FNodeOutputInfo(const FNodeOutputInfo&) = delete;`
- L403 _public prototype_ `FNodeOutputInfo& operator=(const FNodeOutputInfo&) = delete;`
- L404 _public prototype_ `FNodeOutputInfo(FNodeOutputInfo&&) = default;`
- L405 _public prototype_ `FNodeOutputInfo& operator=(FNodeOutputInfo&&) = default;`
- L407 _public member_ `FString Name;`
- L408 _public member_ `TUniquePtr<INodeOutput> Output;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYFLOWCORE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L24 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L443 _function_ `template<typename NodeType> NodeType* CastToNodePtr(FNode* Node)` (scope `UE::GeometryFlow`)
- L453 _macro_ `#define GEOMETRYFLOW_NODE_RTTI(TYPE, SuperType) \`
- L462 _macro_ `#define GEOMETRYFLOW_NODE_INTERNAL(TYPE, VersionID, SuperType) \`

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/GeometryFlowNodeFactory.h` (Public)


#### class `UE::GeometryFlow::FNodeFactory`  
`class FNodeFactory`  
_L18-101_
- desc: Singleton used to create nodes UE::GeometryFlow::FGraph, introduced to help with serialization. this contains an map between FNames and function pointers that can create the named nodes.
- L33 _public prototype_ `FNodeFactory(const FNodeFactory&) = delete;`
- L37 _public prototype_ `static FNodeFactory& GetInstance();`
- L38 _public prototype_ `static void TearDown();`
- L42 _public function_ `template <typename NodeType> bool RegisterType(FString NodeTypePrettyName = FString(), FString TypeCategory = FString())` — returns false if the NodeTypeName is already registered.
- L66 _public function_ `template <typename NodeType> bool CanMake() const`
- L72 _public function_ `bool CanMake(const FName NodeTypeName) const`
- L78 _public function_ `TUniquePtr<FNode> CreateNodeOfType(const FName NodeTypeName) const` — For unregistered types, this returns a null ptr.
- L89 _public function_ `const TMap<const FName, FNodeFactory::FNodeFactoryInfo>& GetFactories() const`
- L93 _protected member_ `TMap<const FName, FNodeFactoryInfo> Factories;`
- L97 _protected function_ `FNodeFactory()`

#### struct `UE::GeometryFlow::FNodeFactory::FNodeFactoryInfo`  
`struct FNodeFactoryInfo`  
_L23-30_
- L25 _public typedef_ `typedef TFunction<TUniquePtr<FNode>() > FNodeTypeFactory;`
- L27 _public member_ `FString TypePrettyName;`
- L28 _public member_ `FString TypeCategory;`
- L29 _public member_ `FNodeTypeFactory TypeFactory;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L59 _function_ `FNodeFactoryInfo NodeFactoryInfo=` (scope `UE::GeometryFlow::FNodeFactory::RegisterType`)
- L110 _macro_ `#define GEOMETRYFLOW_QUOTE(x) #x` — by convention we register the nodes with an FName derived from the actual node class name
- L113 _macro_ `#define GEOMETRYFLOW_REGISTER_NODE_TYPE(ReadableName) \` — Register type F{ReadableName} with the FName {ReadableName}
- L118 _macro_ `#define GEOMETRYFLOW_REGISTER_BASIC_TYPES_NODE(ReadableName) \` — Register Source Node type F{ReadableName}SourceNode  with FName {ReadableName}
- L123 _macro_ `#define GEOMETRYFLOW_REGISTER_SETTINGS_NODE_TYPE(ReadableName) \` — Register Setting Source Node type  F{ReadableName}SettingsSourceNode with FName {ReadableName}Settings
- L128 _macro_ `#define GEOMETRYFLOW_REGISTER_NODE_AND_SETTINGS_NODE(ReadableName) \` — Register two nodes (an opperator and its settings).  F{ReadableName}Node with FName {ReadableName} and  F{ReadableName}SettingsSourceNode with FName {ReadableName}Settings

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/GeometryFlowNodeUtil.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L17 _function_ `template<typename DataType> TSafeSharedPtr<TMovableData<DataType, DataType::DataTypeIdentifier>> MakeMovableData(DataType&& Data)` (scope `UE::GeometryFlow`)
- L24 _function_ `template<typename DataType> TUniquePtr<TBasicNodeInput<DataType, DataType::DataTypeIdentifier>> MakeBasicInput()` (scope `UE::GeometryFlow`)
- L30 _function_ `template<typename DataType> TUniquePtr<TBasicNodeOutput<DataType, DataType::DataTypeIdentifier>> MakeBasicOutput()` (scope `UE::GeometryFlow`)
- L36 _function_ `template<typename T> EGeometryFlowResult ExtractData(TSafeSharedPtr<IData> Data, T& Storage, int32 StorageTypeIdentifier, bool bTryTakeResult)` (scope `UE::GeometryFlow`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/GeometryFlowTSourceNode.h` (Public)


#### class `UE::GeometryFlow::FSourceNodeBase`  
`class FSourceNodeBase : public FNode`  
_L21-51_
- inherits: `FNode`
- L23 _private member_ `static constexpr int Version = 1;`
- L26 _public prototype_ `FSourceNodeBase() = default;`
- L28 _public prototype_ `virtual ~FSourceNodeBase() = default;`
- L31 _public function_ `virtual int GetSourceDataType() const`
- L34 _public function_ `virtual void CollectRequirements(const TArray<FString>& Outputs, TArray<FEvalRequirement>& RequiredInputsOut) override` — source nodes have no input ( hence no requirements)
- L39 _public function_ `virtual void CollectAllRequirements(TArray<FEvalRequirement>& RequiredInputsOut) override` — source nodes have no input ( hence no requirements)
- L46 _public prototype_ `virtual TSharedPtr<FStructOnScope> AsStructOnScope() const = 0;` — copy the source data into an object that can be displayed in UI
- L49 _public prototype_ `virtual void UpdateSourceFromStructOnScope(const FStructOnScope& StructOnScope) = 0;` — allow the source data to be updated (to reflect changes in the UI)

#### class `UE::GeometryFlow::TSourceNodeBase`  
`template<typename T, int32 StorageTypeIdentifier> class TSourceNodeBase : public FSourceNodeBase`  
_L54-119_
- inherits: `FSourceNodeBase`
- L57 _protected typedef_ `using DataType = TMovableData<T, StorageTypeIdentifier>;`
- L59 _protected member_ `TSafeSharedPtr<DataType> Value;`
- L62 _public typedef_ `using CppType = T;`
- L63 _public member_ `static constexpr int DataTypeIdentifier = StorageTypeIdentifier;`
- L65 _public function_ `static const FString OutParamValue()`
- L68 _public function_ `TSourceNodeBase()`
- L77 _public prototype_ `virtual ~TSourceNodeBase() = default;`
- L79 _public function_ `virtual int GetSourceDataType() const override`
- L81 _public function_ `void UpdateSourceValue(const T& NewValue)`
- L87 _public function_ `void GetSourceValue(T& OutValue)`
- L92 _public function_ `virtual void Evaluate( const FNamedDataMap& DatasIn, FNamedDataMap& DatasOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L104 _public function_ `virtual TSharedPtr<FStructOnScope> AsStructOnScope() const override` — copy the UStruct into an object that can be displayed
- L111 _public function_ `virtual void UpdateSourceFromStructOnScope(const FStructOnScope& StructOnScope) override` — used to update the source UStruct when the displayed version has been changed.
- L115 _public function_ `virtual void Serialize(FArchive& Ar) override`

#### class `UE::GeometryFlow::TUStructSourceNode`  
`template<typename UStructType, int32 StorageTypeIdentifier> class TUStructSourceNode : public TSourceNodeBase<UStructType, StorageTypeIdentifier>`  
_L125-160_
- inherits: `TSourceNodeBase<UStructType,StorageTypeIdentifier>`
- desc: Add ability to expose parameters to UI. Note This can only be made for source nodes that have the correct UStructType.
- L130 _public typedef_ `using CppType = UStructType;`
- L135 _public prototype_ `virtual ~TUStructSourceNode() = default;`
- L138 _public function_ `virtual TSharedPtr<FStructOnScope> AsStructOnScope() const override` — copy the UStruct into an object that can be displayed
- L149 _public function_ `virtual void UpdateSourceFromStructOnScope(const FStructOnScope& StructOnScope) override` — used to update the source UStruct when the displayed version has been changed.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L140 _typedef_ `typedef TStructOnScope<UStructType> FTypedStructOnScope;` (scope `UE::GeometryFlow::TUStructSourceNode::AsStructOnScope`)
- L163 _namespace_ `namespace (anonymous)` (scope `UE::GeometryFlow`)
- L166 _function_ `template <typename PODType> void PODSerializer(FArchive& Ar, PODType& Data)` (scope `UE::GeometryFlow::__anon153f46060111`)
- L172 _function_ `template <typename PODStructType> void PODStructSerializer(FArchive& Ar, PODStructType& Data)` (scope `UE::GeometryFlow::__anon153f46060111`)
- L184 _function_ `template <typename UStructType> void UStructSerializer(FArchive& Ar, UStructType& Data)` (scope `UE::GeometryFlow::__anon153f46060111`)
- L201 _macro_ `#define GEOMETRYFLOW_DECLARE_BASIC_TYPES_WO_SERIALIZATION(TypeName, CppType, TypeIdentifier, VersionIntID) \` — This macro declares a MovableData, Node Input/Output, and TSourceNode type for a given C++ type/identifier eg GEOMETRYFLOW_DECLARE_BASIC_TYPES(Int32, int, (int)EDataTypes::Integer) will declare/define: - TMovableData type named FDataInt32 - TBasicNodeInput type named FInt32Input - TBasicNodeOutput type named FInt32Output - TSourceNode type named FInt32SourceNode
- L218 _macro_ `#define GEOMETRYFLOW_DECLARE_BASIC_TYPES(TypeName, CppType, TypeIdentifier, VersionIntID) \` — This macro declares a MovableData, Node Input/Output, and TSourceNode type for a given C++ type/identifier in addition to simple POD serialization for the movable data type eg GEOMETRYFLOW_DECLARE_BASIC_TYPES(Int32, int, (int)EDataTypes::Integer) will declare/define: - TMovableData type named FDataInt32 - TBasicNodeInput type named FInt32Input - TBasicNodeOutput type named FInt32Output - TSourceNode type named FInt32SourceNode
- L233 _macro_ `#define GEOMETRYFLOW_DECLARE_BASIC_TYPES_NULL_SERIALIZE(TypeName, CppType, TypeIdentifier, VersionIntID) \` — This macro declares a MovableData, Node Input/Output, and TSourceNode type for a given C++ type/identifier and injects null serialization code. eg GEOMETRYFLOW_DECLARE_BASIC_TYPES(Int32, int, (int)EDataTypes::Integer) will declare/define: - TMovableData type named FDataInt32 - TBasicNodeInput type named FInt32Input - TBasicNodeOutput type named FInt32Output - TSourceNode type named FInt32SourceNode
- L248 _macro_ `#define GEOMETRYFLOW_DECLARE_BASIC_USTRUCT_TYPES(TypeName, CppType, TypeIdentifier, VersionIntID) \` — This macro declares a MovableData, Node Input/Output, and TSourceNode type for a given C++ type/identifier eg GEOMETRYFLOW_DECLARE_BASIC_TYPES(Int32, FInt32Setting, (int)EDataTypes::Integer) will declare/define: - TMovableData type named FDataInt32 - TBasicNodeInput type named FInt32Input - TBasicNodeOutput type named FInt32Output - TSourceNode type named FInt32SourceNode where FInt32Setting is a UStruct
- L264 _macro_ `#define GEOMETRYFLOW_DECLARE_SETTINGS_TYPES_WO_SERIALIZATION(CppType, ReadableName, VersionIntID) \` — This macro defines two classes for a given C++ class: - TMovableData typedef named FData[XYZ]Settings - TSourceNode typedef named F[XYZ]SettingsSourceNode The assumption is the class has an integer static/constexpr member SettingsType::DataTypeIdentifier that defines the type integer
- L276 _macro_ `#define GEOMETRYFLOW_DECLARE_SETTINGS_TYPES(CppType, ReadableName, VersionIntID) \` — This macro defines two classes for a given C++ class: - TMovableData typedef named FData[XYZ]Settings - TSourceNode typedef named F[XYZ]SettingsSourceNode The assumption is the class has an integer static/constexpr member SettingsType::DataTypeIdentifier that defines the type integer
- L288 _macro_ `#define GEOMETRYFLOW_DECLARE_SETTINGS_TYPES_NULL_SERIALIZE(CppType, ReadableName, VersionIntID) \` — This macro defines two classes for a given C++ class: - TMovableData typedef named FData[XYZ]Settings - TSourceNode typedef named F[XYZ]SettingsSourceNode The assumption is the class has an integer static/constexpr member SettingsType::DataTypeIdentifier that defines the type integer
- L292 _macro_ `#define GEOMETRYFLOW_DECLARE_USTRUCT_SETTINGS_TYPES(CppType, ReadableName, VersionIntID) \`

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/GeometryFlowTypes.h` (Public)


#### enum `UE::GeometryFlow::EGeometryFlowResult`  
`enum class EGeometryFlowResult`  
_L33-46_
- L35 _public enumerator_ `Ok = 0`
- L36 _public enumerator_ `NodeDoesNotExist = 1`
- L37 _public enumerator_ `InputDoesNotExist = 2`
- L38 _public enumerator_ `OutputDoesNotExist = 3`
- L39 _public enumerator_ `UnmatchedTypes = 4`
- L40 _public enumerator_ `ConnectionDoesNotExist = 5`
- L41 _public enumerator_ `NoMatchesFound = 6`
- L42 _public enumerator_ `MultipleMatchingAmbiguityFound = 7`
- L43 _public enumerator_ `OperationCancelled = 8`
- L44 _public enumerator_ `InputAlreadyConnected = 9`
- L45 _public enumerator_ `ConnectionRejectedCreatesCycle = 10`

#### enum `UE::GeometryFlow::EDataTypes`  
`enum class EDataTypes`  
_L53-78_
- desc: Every data type in a GeometryFlow graph requires a unique integer to identify the type. This enum defines various integer ranges used by the known data/node libraries.
- L55 _public enumerator_ `Integer = 0`
- L56 _public enumerator_ `Float = 1`
- L57 _public enumerator_ `Double = 2`
- L59 _public enumerator_ `IntegerStruct = 3`
- L60 _public enumerator_ `FloatStruct = 4`
- L61 _public enumerator_ `DoubleStruct = 5`
- L63 _public enumerator_ `Vector3f = 20`
- L64 _public enumerator_ `Vector3d = 21`
- L66 _public enumerator_ `Vector3fStruct = 22`
- L67 _public enumerator_ `Vector3dStruct = 23`
- L69 _public enumerator_ `Name = 30`
- L71 _public enumerator_ `NameStruct = 31`
- L73 _public enumerator_ `BaseMeshProcessingTypes = 1000`
- L74 _public enumerator_ `BaseMeshProcessingTypesEditor = 2000`
- L77 _public enumerator_ `UserDefinedTypes = 10000`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L14 _typedef_ `template <typename T> using TSafeSharedPtr = TSharedPtr<T, ESPMode::ThreadSafe>;` (scope `UE::GeometryFlow`) — alias for Thread-Safe TSharedPtr
- L18 _function_ `template<typename T, typename... InArgTypes> TSafeSharedPtr<T> MakeSafeShared(InArgTypes&&... Args)` (scope `UE::GeometryFlow`) — wrapper around MakeShared for creating a TSafeSharedPtr
- L86 _macro_ `#define DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(TypeID) static constexpr int DataTypeIdentifier = (int)TypeID;` — This macro declares the type identifier for a GeometryFlow data type. Generally TypeID is declared in an enum, like EDataTypes above, or EMeshProcessingDataTypes in GeometryFlowMeshProcessing. Standard usage is to include at the top of the relevant class/struct definition.

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowCore/Public/MathNodes/ArithmeticNodes.h` (Public)


#### class `UE::GeometryFlow::TBinaryOpAddNode`  
`template<typename T, int StorageTypeIdentifier> class TBinaryOpAddNode : public TBinaryOpLambdaNode<T, StorageTypeIdentifier>`  
_L16-21_
- inherits: `TBinaryOpLambdaNode<T,StorageTypeIdentifier>`
- L19 _public function_ `TBinaryOpAddNode() : TBinaryOpLambdaNode<T, StorageTypeIdentifier>([](const T& A, const T& B) { return A + B; })`
- L19 _public function_ `TBinaryOpAddNode() : TBinaryOpLambdaNode<T, StorageTypeIdentifier>([](const T& A, const T& B) { return A + B; })`

#### class `UE::GeometryFlow::FAddFloatNode`  
`class FAddFloatNode : public TBinaryOpAddNode<float, (int)EDataTypes::Float>`  
_L23-27_
- inherits: `TBinaryOpAddNode<float,(int)EDataTypes::Float>`
- L25 _private member_ `static constexpr int NodeVersion = 1;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace GeometryFlow` (scope `UE`)
