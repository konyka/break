# Plugins / MetasoundGraphCore

- module root: `Plugins/Runtime/Metasound/Source/MetasoundGraphCore`
- headers: 44; symbols: 2216
- symbol kinds: class=116, enum=14, enumerator=46, externvar=8, function=459, macro=91, member=470, namespace=77, prototype=664, struct=141, typedef=126, variable=4
- PrivateDependencyModuleNames: MathCore, TraceLog
- PublicDependencyModuleNames: AudioExtensions, Core, CoreUObject, SignalProcessing

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Private/MetasoundDynamicGraphAlgo.h` (Private)


#### struct `Metasound::DynamicGraph::FExecuteEntry`  
`struct FExecuteEntry final`  
_L22-37_
- desc: Convenience wrapper for execute function of an IOperator.
- L24 _public prototype_ `FExecuteEntry(int32 InOrdinal, FOperatorID InOperatorID, IOperator& InOperator, IOperator::FExecuteFunction InFunc);`
- L26 _public function_ `void Execute()`
- L33 _public member_ `int32 Ordinal;`
- L34 _public member_ `FOperatorID OperatorID;`
- L35 _public member_ `IOperator* Operator;`
- L36 _public member_ `IOperator::FExecuteFunction Function;`

#### struct `Metasound::DynamicGraph::FPostExecuteEntry`  
`struct FPostExecuteEntry final`  
_L40-55_
- desc: Convenience wrapper for post execute function of an IOperator.
- L42 _public prototype_ `FPostExecuteEntry(int32 InOrdinal, FOperatorID InOperatorID, IOperator& InOperator, IOperator::FPostExecuteFunction InFunc);`
- L44 _public function_ `void PostExecute()`
- L51 _public member_ `int32 Ordinal;`
- L52 _public member_ `FOperatorID OperatorID;`
- L53 _public member_ `IOperator* Operator;`
- L54 _public member_ `IOperator::FPostExecuteFunction Function;`

#### struct `Metasound::DynamicGraph::FResetEntry`  
`struct FResetEntry final`  
_L58-73_
- desc: Convenience wrapper for reset function of an IOperator.
- L60 _public prototype_ `FResetEntry(int32 InOrdinal, FOperatorID InOperatorID, IOperator& InOperator, IOperator::FResetFunction InFunc);`
- L62 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L69 _public member_ `int32 Ordinal;`
- L70 _public member_ `FOperatorID OperatorID;`
- L71 _public member_ `IOperator* Operator;`
- L72 _public member_ `IOperator::FResetFunction Function;`

#### struct `Metasound::DynamicGraph::FDynamicGraphOperatorData`  
`struct FDynamicGraphOperatorData : DirectedGraphAlgo::FGraphOperatorData`  
_L77-92_
- inherits: `DirectedGraphAlgo::FGraphOperatorData`
- desc: Collection of data needed to support a dynamic operator
- L79 _public prototype_ `FDynamicGraphOperatorData(const FOperatorSettings& InSettings);`
- L80 _public prototype_ `FDynamicGraphOperatorData(const FOperatorSettings& InSettings, const FDynamicOperatorUpdateCallbacks& InCallbacks);`
- L83 _public prototype_ `void InitTables();` — Initialize the Execute/PostExecute/Reset tables.
- L87 _public member_ `FDynamicOperatorUpdateCallbacks OperatorUpdateCallbacks;` — A collection of optional callbacks which can be invoked when various updates are made to this collection of data.
- L89 _public member_ `TArray<FExecuteEntry> ExecuteTable;`
- L90 _public member_ `TArray<FPostExecuteEntry> PostExecuteTable;`
- L91 _public member_ `TArray<FResetEntry> ResetTable;`

#### class `Metasound::DynamicGraph::IDynamicGraphInPlaceBuildable`  
`class IDynamicGraphInPlaceBuildable`  
_L97-112_
- desc: Interface to allow FOperatorBuilder special access to internal FDynamicGraphOperatorData structures when the operator is being built.
- L100 _public prototype_ `virtual ~IDynamicGraphInPlaceBuildable() = default;`
- L111 _private prototype_ `virtual FDynamicGraphOperatorData& GetDynamicGraphOperatorData() = 0;` — This function gives FOperatorBuilder access to the graph's internal data. This allows the FOperatorBuilder to build the operator in place by modifying the internal data structure of the operator. An alternative approach would be to pass the data to the operator as a constructor argument. "In Place" building was chosen because it simplifies and streamlines the build process within the FOperatorBuilder.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Metasound`
- L14 _namespace_ `namespace DynamicGraph` (scope `Metasound`)
- L18 _typedef_ `using FOperatorInfo = DirectedGraphAlgo::FGraphOperatorData::FOperatorInfo;` (scope `Metasound::DynamicGraph`)
- L19 _typedef_ `using FOperatorID = DirectedGraphAlgo::FOperatorID;` (scope `Metasound::DynamicGraph`)
- L118 _prototype_ `void SetOrdinalsAndSort(const TMap<FOperatorID, int32>& InOrdinals, FDynamicGraphOperatorData& InOutGraphOperatorData);` (scope `Metasound::DynamicGraph`) — Sets the ordinals of operators and sorts executions tables. @param InOrdinals - A map of FOperatorID to ordinal. @param InOutGraphOperatorData - The graph data where the updated ordinals should be applied.
- L124 _prototype_ `void SwapOrdinalsAndSort(const TArray<FOrdinalSwap>& InSwaps, FDynamicGraphOperatorData& InOutGraphOperatorData);` (scope `Metasound::DynamicGraph`) — Applies the ordinal swaps to operators and sorts execution tables. @param InSwaps - An array of ordinal swaps. @param InOutGraphOperatorData - The graph data where the updated ordinals should be applied.
- L137 _prototype_ `void PropagateBindUpdate(FOperatorID InInitialOperatorID, const FVertexName& InVertexName, const FAnyDataReference& InNewReference, FDynamicGraphOperatorData& InOutGraphOperatorData);` (scope `Metasound::DynamicGraph`) — Propagate FVertexInterfaceData updates through the operators in the Dynamic Graph Operator Data. A change to an operator's input may result in a change to the operator's output. The updates to the operator's output and any subsequent knock-on operator output updates need to be propagated through all the relevant operators in the graph. @param InInitialOperatorID - ID of operator which will have it's input updated. @param InVertexName - Vertex name on the initial operator which will have it's input updated. @param InNewReference - New data reference to apply to the operators input vertex. @param InOutGraphOperatorData - Graph data which will be updated with new references.
- L142 _prototype_ `void UpdateOutputVertexData(FDynamicGraphOperatorData& InOutGraphOperatorData);` (scope `Metasound::DynamicGraph`) — Iterate through the output operators and make force that their output data references are reflected in the graph's FOutputVertexInterfaceData
- L145 _prototype_ `void RebindWrappedOperator(const FOperatorID& InOperatorID, FOperatorInfo& InOperatorInfo, FDynamicGraphOperatorData& InGraphOperatorData);` (scope `Metasound::DynamicGraph`) — Rebinds an operator which is wrapping another operator.
- L148 _prototype_ `void RebindGraphInputs(FInputVertexInterfaceData& InOutVertexData, FDynamicGraphOperatorData& InOutGraphOperatorData);` (scope `Metasound::DynamicGraph`) — Rebind the graph inputs, updating internal operator bindings as needed.
- L151 _prototype_ `void RebindGraphOutputs(FOutputVertexInterfaceData& InOutVertexData, FDynamicGraphOperatorData& InOutGraphOperatorData);` (scope `Metasound::DynamicGraph`) — Rebind the graph inputs, updating internal operator bindings as needed.
- L159 _prototype_ `void InsertOperator(FOperatorID InOperatorID, FOperatorInfo InOperatorInfo, FDynamicGraphOperatorData& InOutGraphOperatorData);` (scope `Metasound::DynamicGraph`) — Insert an operator into the graph data and add to execution tables. @param InOperatorID - ID of new operator. @param InOperatorInfo - Info containing describing operator. @param InOutGraphOperatorData - Graph data where the operator will be inserted.
- L167 _prototype_ `void RemoveOperator(FOperatorID InOperatorID, const TArray<FOperatorID>& InOperatorsConnectedToInput, FDynamicGraphOperatorData& InOutGraphOperatorData);` (scope `Metasound::DynamicGraph`) — Remove operator and related connections from the graph data. @param InOperatorID - ID of operator to remove. @param InOperatorsConnectedToInput - An array of operator IDs denoting which operators connect to the input of operator being removed. @param InOutGraphOperatorData - Graph data where the operator will be removed from.
- L169 _namespace_ `namespace Debug` (scope `Metasound::DynamicGraph`)
- L171 _prototype_ `void EnsureIfDynamicGraphOperatorDataIsCorrupt(const FDynamicGraphOperatorData& InData);` (scope `Metasound::DynamicGraph::Debug`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Private/MetasoundDynamicOperator.h` (Private)


#### enum `Metasound::DynamicGraph::EDynamicOperatorTransformQueueAction`  
`enum class EDynamicOperatorTransformQueueAction : uint8`  
_L38-42_
- desc: Action to perform after a single transformation.
- L40 _public enumerator_ `Continue` — Perform next operator if it exists.
- L41 _public enumerator_ `Fence` — Wait to perform next operator until the operator has been executed.

#### class `Metasound::DynamicGraph::IDynamicOperatorTransform`  
`class IDynamicOperatorTransform`  
_L45-50_
- desc: Interface for transformation of dynamic graph operator data.
- L48 _public prototype_ `virtual ~IDynamicOperatorTransform() = default;`
- L49 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) = 0;`

#### class `Metasound::DynamicGraph::FDynamicOperator`  
`class FDynamicOperator : public IOperator, public IDynamicGraphInPlaceBuildable`  
_L56-96_
- inherits: `IOperator,IDynamicGraphInPlaceBuildable`
- desc: An FDynamicOperator is a MetaSound operator which can dynamically change it's topology. Changes are communicated to the dynamic operator through a TransformationQueue.
- L60 _public prototype_ `FDynamicOperator(const FOperatorSettings& InSettings);`
- L61 _public prototype_ `FDynamicOperator(const FOperatorSettings& InSettings, TSharedPtr<TSpscQueue<TUniquePtr<IDynamicOperatorTransform>>> TransformQueue, const FDynamicOperatorUpdateCallbacks& InOperatorUpdateCallbacks);`
- L63 _public prototype_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override;`
- L64 _public prototype_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override;`
- L66 _public prototype_ `virtual IOperator::FResetFunction GetResetFunction() override;`
- L68 _public prototype_ `virtual IOperator::FExecuteFunction GetExecuteFunction() override;`
- L70 _public prototype_ `virtual IOperator::FPostExecuteFunction GetPostExecuteFunction() override;`
- L73 _public prototype_ `void FlushEnqueuedTransforms();` — Force all transformations in the transaction queue to be applied.
- L80 _private prototype_ `virtual FDynamicGraphOperatorData& GetDynamicGraphOperatorData() override;`
- L82 _private prototype_ `void ApplyTransformsUntilFence();`
- L83 _private prototype_ `void ApplyTransformsUntilFenceOrTimeout(double InTimeoutInSeconds);`
- L84 _private prototype_ `void Execute();`
- L85 _private prototype_ `void PostExecute();`
- L86 _private prototype_ `void Reset(const IOperator::FResetParams& InParams);`
- L88 _private prototype_ `static void StaticReset(IOperator* InOperator, const IOperator::FResetParams& InParams);`
- L89 _private prototype_ `static void StaticExecute(IOperator* InOperator);`
- L90 _private prototype_ `static void StaticPostExecute(IOperator* InOperator);`
- L92 _private member_ `FDynamicGraphOperatorData DynamicOperatorData;`
- L94 _private member_ `TSharedPtr<TSpscQueue<TUniquePtr<IDynamicOperatorTransform>>> TransformQueue;`
- L95 _private member_ `bool bExecuteFenceIsSet = false;`

#### class `Metasound::DynamicGraph::FNullTransform`  
`class FNullTransform : public IDynamicOperatorTransform`  
_L99-103_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which does nothing.
- L102 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`

#### class `Metasound::DynamicGraph::FSetOperatorOrdinalsAndSort`  
`class FSetOperatorOrdinalsAndSort : public IDynamicOperatorTransform`  
_L106-113_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which determines the order of execution for operators.
- L109 _public prototype_ `FSetOperatorOrdinalsAndSort(TMap<FOperatorID, int32> InOrdinals);`
- L110 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L112 _private member_ `TMap<FOperatorID, int32> Ordinals;`

#### class `Metasound::DynamicGraph::FSwapOperatorOrdinalsAndSort`  
`class FSwapOperatorOrdinalsAndSort : public IDynamicOperatorTransform`  
_L116-123_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which applies operator ordinal swaps.
- L119 _public prototype_ `FSwapOperatorOrdinalsAndSort(TArray<FOrdinalSwap> InSwaps);`
- L120 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L122 _private member_ `TArray<FOrdinalSwap> Swaps;`

#### class `Metasound::DynamicGraph::FInsertOperator`  
`class FInsertOperator : public IDynamicOperatorTransform`  
_L126-134_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which adds an operator.
- L129 _public prototype_ `FInsertOperator(FOperatorID InOperatorID, FOperatorInfo InInfo);`
- L130 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L132 _private member_ `FOperatorID OperatorID;`
- L133 _private member_ `FOperatorInfo OperatorInfo;`

#### class `Metasound::DynamicGraph::FRemoveOperator`  
`class FRemoveOperator : public IDynamicOperatorTransform`  
_L137-145_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which removes an operator.
- L140 _public prototype_ `FRemoveOperator(FOperatorID InOperatorID, TArray<FOperatorID> InOperatorsConnectedToInput);`
- L141 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L143 _private member_ `FOperatorID OperatorID;`
- L144 _private member_ `TArray<FOperatorID> OperatorsConnectedToInput;`

#### class `Metasound::DynamicGraph::FAddInput`  
`class FAddInput : public IDynamicOperatorTransform`  
_L148-157_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which exposes an input to the graph.
- L151 _public prototype_ `FAddInput(FOperatorID InOperatorID, const FVertexName& InVertexName, FAnyDataReference InDataReference);`
- L152 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L154 _private member_ `FOperatorID OperatorID;`
- L155 _private member_ `FVertexName VertexName;`
- L156 _private member_ `FAnyDataReference DataReference;`

#### class `Metasound::DynamicGraph::FRemoveInput`  
`class FRemoveInput : public IDynamicOperatorTransform`  
_L160-167_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which removes an input to the graph.
- L163 _public prototype_ `FRemoveInput(const FVertexName& InVertexName);`
- L164 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L166 _private member_ `FVertexName VertexName;`

#### class `Metasound::DynamicGraph::FAddOutput`  
`class FAddOutput: public IDynamicOperatorTransform`  
_L170-178_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which exposes an output from the graph.
- L173 _public prototype_ `FAddOutput(FOperatorID InOperatorID, const FVertexName& InVertexName);`
- L174 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L176 _private member_ `FOperatorID OperatorID;`
- L177 _private member_ `FVertexName VertexName;`

#### class `Metasound::DynamicGraph::FRemoveOutput`  
`class FRemoveOutput: public IDynamicOperatorTransform`  
_L181-188_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which removes an output from the graph.
- L184 _public prototype_ `FRemoveOutput(const FVertexName& InVertexName);`
- L185 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L187 _private member_ `FVertexName VertexName;`

#### class `Metasound::DynamicGraph::FExecuteFence`  
`class FExecuteFence : public IDynamicOperatorTransform`  
_L191-195_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which pauses the transformation queue until the dynamic operator has executed.
- L194 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`

#### class `Metasound::DynamicGraph::FConnectOperators`  
`class FConnectOperators : public IDynamicOperatorTransform`  
_L198-208_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which connects two vertices in the graph.
- L201 _public prototype_ `FConnectOperators(FOperatorID InFromOpID, const FName& InFromVert, FOperatorID InToOpID, const FName& InToVert);`
- L202 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L204 _private member_ `FOperatorID FromOpID;`
- L205 _private member_ `FOperatorID ToOpID;`
- L206 _private member_ `FName FromVert;`
- L207 _private member_ `FName ToVert;`

#### class `Metasound::DynamicGraph::FSwapOperatorConnection`  
`class FSwapOperatorConnection : public IDynamicOperatorTransform`  
_L211-223_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which disconnects two vertices in the graph.
- L214 _public prototype_ `FSwapOperatorConnection(FOperatorID InOriginalFromOpID, const FName& InOriginalFromVert, FOperatorID InNewFromOpID, const FName& InNewFromVert, FOperatorID InToOpID, const FName& InToVert);`
- L215 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L217 _private member_ `FConnectOperators ConnectTransform;`
- L219 _private member_ `FOperatorID OriginalFromOpID;`
- L220 _private member_ `FOperatorID ToOpID;`
- L221 _private member_ `FName OriginalFromVert;`
- L222 _private member_ `FName ToVert;`

#### class `Metasound::DynamicGraph::FSetOperatorInput`  
`class FSetOperatorInput : public IDynamicOperatorTransform`  
_L226-237_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which sets the input to an operator to a specified literal.
- L229 _public prototype_ `FSetOperatorInput(FOperatorID InToOpID, const FName& InToVert, FAnyDataReference InDataRef);`
- L231 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L234 _private member_ `FOperatorID ToOpID;`
- L235 _private member_ `FName ToVert;`
- L236 _private member_ `FAnyDataReference DataRef;`

#### class `Metasound::DynamicGraph::FRemoveOperatorConnection`  
`class FRemoveOperatorConnection : public IDynamicOperatorTransform`  
_L240-253_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which disconnects two vertices in the graph, replacing the input with a given data reference.
- L243 _public prototype_ `FRemoveOperatorConnection(FOperatorID InFromOpID, const FName& InFromVertName, FOperatorID InToOpID, const FName& InToVertName, FAnyDataReference InReplacementDataRef);`
- L244 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L247 _private member_ `FSetOperatorInput SetOperatorInputTransform;`
- L249 _private member_ `FOperatorID FromOpID;`
- L250 _private member_ `FOperatorID ToOpID;`
- L251 _private member_ `FName FromVertName;`
- L252 _private member_ `FName ToVertName;`

#### class `Metasound::DynamicGraph::FAtomicTransform`  
`class FAtomicTransform : public IDynamicOperatorTransform`  
_L257-264_
- inherits: `IDynamicOperatorTransform`
- desc: A transform which groups multiple transformations together and forces them to all complete before the dynamic operator executes.
- L260 _public prototype_ `FAtomicTransform(TArray<TUniquePtr<IDynamicOperatorTransform>> InTransforms);`
- L261 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L263 _private member_ `TArray<TUniquePtr<IDynamicOperatorTransform>> Transforms;`

#### enum `Metasound::DynamicGraph::EAudioFadeType`  
`enum class EAudioFadeType : uint8`  
_L266-270_
- L268 _public enumerator_ `FadeIn` — Fade from silent to full volume.
- L269 _public enumerator_ `FadeOut` — Fade from full volume to silent.

#### class `Metasound::DynamicGraph::FBeginAudioFadeTransform`  
`class FBeginAudioFadeTransform : public IDynamicOperatorTransform`  
_L284-295_
- inherits: `IDynamicOperatorTransform`
- desc: Marks the beginning of an audio fade. When scheduling fade transformations on a dynamic operator, an FBeginAudioFadeTransform must be matched with an FEndAudioTransform with an FExecuteFence between them. The FBeginAudioFadeTransform sets up the graph to perform a set of audio fades. The FExecuteFence forces the fade to occur before any additional transforms are performed. The FEndAudioFadeTransform cleans up any temporary state that was needed to perform the fade.
- L288 _public prototype_ `FBeginAudioFadeTransform(FOperatorID InOperatorIDToFade, EAudioFadeType InFadeType, TArrayView<const FVertexName> InInputVerticesToFade, TArrayView<const FVertexName> InOutputVerticesToFade);`
- L289 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L291 _private member_ `FOperatorID OperatorIDToFade;`
- L292 _private member_ `FAudioFadeOperatorWrapper::EFadeState InitFadeState;`
- L293 _private member_ `TArray<FVertexName> InputVerticesToFade;`
- L294 _private member_ `TArray<FVertexName> OutputVerticesToFade;`

#### class `Metasound::DynamicGraph::FEndAudioFadeTransform`  
`class FEndAudioFadeTransform : public IDynamicOperatorTransform`  
_L298-305_
- inherits: `IDynamicOperatorTransform`
- desc: Marks the end of an audio fade.
- L301 _public prototype_ `FEndAudioFadeTransform(FOperatorID InOperatorIDToFade);`
- L302 _public prototype_ `virtual EDynamicOperatorTransformQueueAction Transform(FDynamicGraphOperatorData& InGraphOperatorData) override;`
- L304 _private member_ `FOperatorID OperatorIDToFade;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define METASOUND_DEBUG_DYNAMIC_TRANSACTOR !UE_BUILD_SHIPPING`
- L20 _namespace_ `namespace Metasound`
- L22 _namespace_ `namespace DynamicGraph` (scope `Metasound`)
- L29 _namespace_ `namespace Debug` (scope `Metasound::DynamicGraph`)
- L35 _typedef_ `using FLiteralAssignmentFunction = void(*)(const FOperatorSettings& InOperatorSettings, const FLiteral& InLiteral, const FAnyDataReference& OutDataRef);` (scope `Metasound::DynamicGraph`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Private/MetasoundDynamicOperatorAudioFade.h` (Private)


#### class `Metasound::DynamicGraph::FAudioFadeOperatorWrapper`  
`class FAudioFadeOperatorWrapper : public TExecutableOperator<FAudioFadeOperatorWrapper>`  
_L25-67_
- inherits: `TExecutableOperator<FAudioFadeOperatorWrapper>`
- desc: FAudioFadeOperatorWrapper wraps an existing operator and applies a fade in/out to any designated audio buffers on the next execution. The fade will only occur over a single audio buffer and will be finalized during calls to PostExecute. When this operator wraps another operator, it will also provide different output data references for any faded output audio buffers. Users of this operator should be wary to rebind downstream operators in any graph using this operator wrapper. The wrapped operator can be release if desired, though it leaves this operator in a state where it will have no effect on any audio buffers.
- L36 _public prototype_ `FAudioFadeOperatorWrapper(EFadeState InInitialFadeState, const FOperatorSettings& InOperatorSettings, const FInputVertexInterfaceData& InInputData, TUniquePtr<IOperator> InOperator, TArrayView<const FVertexName> InInputVerticesToFade, TArrayView<const FVertexName> InOutputVerticesToFade);`
- L38 _public prototype_ `TUniquePtr<IOperator> ReleaseOperator();`
- L40 _public prototype_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override;`
- L41 _public prototype_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override;`
- L43 _public prototype_ `void Execute();`
- L44 _public prototype_ `void PostExecute();`
- L45 _public prototype_ `void Reset(const IOperator::FResetParams& InParams);`
- L49 _private prototype_ `void InitInputBuffers(const FOperatorSettings& InOperatorSettings, const FInputVertexInterfaceData& InInputData);`
- L50 _private prototype_ `void InitOutputBuffers(const FOperatorSettings& InOperatorSettings);`
- L52 _private prototype_ `void FadeBuffers(const TArray<TDataReadReference<FAudioBuffer>>& InSrc, const TArray<TDataWriteReference<FAudioBuffer>>& InDst);`
- L53 _private prototype_ `void SetWrappedOperatorInputs(const FInputVertexInterfaceData& InInputData);`
- L55 _private member_ `FExecuter WrappedOperator;`
- L57 _private member_ `TArray<FVertexName> InputVerticesToFade;`
- L58 _private member_ `TArray<FVertexName> OutputVerticesToFade;`
- L60 _private member_ `TArray<TDataReadReference<FAudioBuffer>> WrappedInputAudioBuffers;`
- L61 _private member_ `TArray<TDataWriteReference<FAudioBuffer>> FadedInputAudioBuffers;`
- L62 _private member_ `TArray<TDataReadReference<FAudioBuffer>> WrappedOutputAudioBuffers;`
- L63 _private member_ `TArray<TDataWriteReference<FAudioBuffer>> FadedOutputAudioBuffers;`
- L65 _private member_ `EFadeState InitialFadeState;`
- L66 _private member_ `EFadeState FadeState;`

#### enum `Metasound::DynamicGraph::FAudioFadeOperatorWrapper::EFadeState`  
`enum class EFadeState : uint8`  
_L28-34_
- L30 _public enumerator_ `Silence`
- L31 _public enumerator_ `FadingOut`
- L32 _public enumerator_ `FadingIn`
- L33 _public enumerator_ `FullVolume`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace DynamicGraph` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Private/MetasoundGraphAlgoPrivate.h` (Private)


#### struct `Metasound::DirectedGraphAlgo::FGraphOperatorData`  
`struct FGraphOperatorData`  
_L26-67_
- desc: FGraphOoperatorData contains all the objects needed to implement a runtime instance of a MetaSound graph.
- L52 _public prototype_ `FGraphOperatorData(const FOperatorSettings& InOperatorSettings);`
- L54 _public member_ `FOperatorSettings OperatorSettings;`
- L57 _public member_ `FVertexInterfaceData VertexData;` — Vertex Data bound to the graph
- L60 _public member_ `TSortedMap<FOperatorID, FOperatorInfo> OperatorMap;` — Map of all operators in graph
- L63 _public member_ `TSortedVertexNameMap<FOperatorID> InputVertexMap;` — Map with input vertex name as key, and OperatorID of input node as value.
- L66 _public member_ `TSortedVertexNameMap<FOperatorID> OutputVertexMap;` — Map with output vertex name as key, and OperatorID of output node as value.

#### struct `Metasound::DirectedGraphAlgo::FGraphOperatorData::FVertexDestination`  
`struct FVertexDestination`  
_L29-33_
- desc: Represents an input of an operator
- L31 _public member_ `FOperatorID OperatorID;`
- L32 _public member_ `FVertexName VertexName;`

#### struct `Metasound::DirectedGraphAlgo::FGraphOperatorData::FOperatorInfo`  
`struct FOperatorInfo`  
_L35-50_
- L40 _public member_ `int32 Ordinal;` — The ordinal associated with the operator. Ordinals can be used to determine ordering of operators, but shouldn't be considered as indexes.
- L42 _public member_ `TUniquePtr<IOperator> Operator;`
- L45 _public member_ `FVertexInterfaceData VertexData;` — Vertex Data bound to operator.
- L49 _public member_ `TSortedVertexNameMap<TArray<FVertexDestination>> OutputConnections;` — Map where the operators output vertex is the key, and an array of output connections is the value.

#### struct `Metasound::DirectedGraphAlgo::FStaticGraphOperatorData`  
`struct FStaticGraphOperatorData : FGraphOperatorData`  
_L73-79_
- inherits: `FGraphOperatorData`
- desc: FStaticGraphOperatorData contains FGraphOperatorData plus a static ordering of nodes. This structure allows the FOpeatorBuilder to more efficiently inform the FGraphOperator how the operators should order execution tables.
- L78 _public member_ `TArray<const INode*> NodeOrder;` — Order of node execution

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Metasound`
- L16 _namespace_ `namespace DirectedGraphAlgo` (scope `Metasound`)
- L19 _typedef_ `using FOperatorID = uintptr_t;` (scope `Metasound::DirectedGraphAlgo`) — ID used to lookup operators.
- L22 _prototype_ `FOperatorID GetOperatorID(const INode& InNode);` (scope `Metasound::DirectedGraphAlgo`) — Retrieve an operator ID from a node.
- L23 _prototype_ `FOperatorID GetOperatorID(const INode* InNode);` (scope `Metasound::DirectedGraphAlgo`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Private/MetasoundProfilingOperator.h` (Private)


#### class `Metasound::FProfilingOperator`  
`class FProfilingOperator : public IOperator`  
_L20-110_
- inherits: `IOperator`
- desc: This is a wrapper around any IOperator that causes its functions to be timed for Insights
- L23 _public function_ `FProfilingOperator( TUniquePtr<IOperator>&& WrappedOperator, const INode* Node) : Operator(MoveTemp(WrappedOperator)) , ResetFunction(Operator->GetResetFunction()) , ExecuteFunction(Operator->GetExecuteFunction()) , PostExecuteFunction(Operator->GetPostExecuteFunction()) , InsightsResetEventSpecId(0) , InsightsExecuteEventSpecId(0) , InsightsPostExecuteEventSpecId(0)`
- L51 _public prototype_ `void SetAssetMetaData(const ThreadLocalDebug::FAssetMetaData& InAssetMetaData);`
- L54 _public prototype_ `virtual ~FProfilingOperator() = default;`
- L56 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L61 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData)`
- L66 _public function_ `virtual FResetFunction GetResetFunction() override`
- L74 _public function_ `virtual FExecuteFunction GetExecuteFunction() override`
- L82 _public function_ `virtual FPostExecuteFunction GetPostExecuteFunction() override`
- L91 _public prototype_ `static void StaticReset(IOperator* InOperator, const IOperator::FResetParams& InParams);`
- L92 _public prototype_ `static void StaticExecute(IOperator* InOperator);`
- L93 _public prototype_ `static void StaticPostExecute(IOperator* InOperator);`
- L97 _private member_ `ThreadLocalDebug::FAssetMetaData AssetMetaData;`
- L100 _private member_ `TUniquePtr<IOperator> Operator;`
- L101 _private member_ `FResetFunction ResetFunction;`
- L102 _private member_ `FExecuteFunction ExecuteFunction;`
- L103 _private member_ `FPostExecuteFunction PostExecuteFunction;`
- L104 _private member_ `FString InsightsResetEventName;`
- L105 _private member_ `FString InsightsExecuteEventName;`
- L106 _private member_ `FString InsightsPostExecuteEventName;`
- L107 _private member_ `uint32 InsightsResetEventSpecId;`
- L108 _private member_ `uint32 InsightsExecuteEventSpecId;`
- L109 _private member_ `uint32 InsightsPostExecuteEventSpecId;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace Profiling` (scope `Metasound`)
- L14 _prototype_ `void Init();` (scope `Metasound::Profiling`)
- L15 _prototype_ `bool OperatorShouldBeProfiled(const FNodeClassMetadata& NodeMetadata);` (scope `Metasound::Profiling`)
- L16 _prototype_ `bool ProfileAllGraphs();` (scope `Metasound::Profiling`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Private/MetasoundRebindableGraphOperator.h` (Private)


#### class `Metasound::FRebindableGraphOperator`  
`class FRebindableGraphOperator : public TExecutableOperator<FRebindableGraphOperator>, public DynamicGraph::IDynamicGraphInPlaceBuildable`  
_L16-39_
- inherits: `TExecutableOperator<FRebindableGraphOperator>,DynamicGraph::IDynamicGraphInPlaceBuildable`
- L20 _public prototype_ `FRebindableGraphOperator(const FOperatorSettings& InOperatorSettigns);`
- L23 _public prototype_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override;` — Bind the graph's interface data references to FVertexInterfaceData.
- L24 _public prototype_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override;`
- L26 _public prototype_ `void Execute();`
- L27 _public prototype_ `void PostExecute();`
- L28 _public prototype_ `void Reset(const IOperator::FResetParams& InParams);`
- L30 _public prototype_ `virtual IOperator::FPostExecuteFunction GetPostExecuteFunction() override;`
- L33 _private prototype_ `static void StaticPostExecute(IOperator* InOperator);`
- L36 _private prototype_ `virtual DynamicGraph::FDynamicGraphOperatorData& GetDynamicGraphOperatorData() override;` — Interface for FOperatorBuilder to access internal data structure.
- L38 _private member_ `DynamicGraph::FDynamicGraphOperatorData GraphOperatorData;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Private/MetasoundVertexPrivate.h` (Private)


#### struct `Metasound::VertexPrivate::FPrivateAccessTag`  
`struct FPrivateAccessTag`  
_L9-11_
- desc: Used to control API access when a method must be public but we do not want it to be used outside of this module.

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace Metasound`
- L5 _namespace_ `namespace VertexPrivate` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundAudioBuffer.h` (Public)


#### class `Metasound::FAudioBuffer`  
`class FAudioBuffer`  
_L23-145_
- desc: FAudioBuffer FAudioBuffer is the default buffer for passing audio data between nodes.  It should not be resized. It is compatible with functions accepting const references to FAlignedFloatBuffer (const FAlignedFloatBuffer&) arguments via an implicit conversion operator which exposes the underlying FAlignedFloatBuffer container.
- L30 _public function_ `explicit FAudioBuffer(int32 InNumSamples)` — Create an FAudioBuffer with a specific number of samples. @param InNumSamples - Number of samples in buffer.
- L43 _public function_ `FAudioBuffer(const FOperatorSettings& InSettings)` — This is the constructor used by the frontend.
- L53 _public function_ `FAudioBuffer()`
- L62 _public function_ `inline const float* GetData() const` — Return a pointer to the audio float data.
- L71 _public function_ `inline float* GetData()` — Return a pointer to the audio float data.
- L80 _public function_ `inline int32 Num() const` — Return the number of samples in the audio buffer.
- L89 _public function_ `inline operator const Audio::FAlignedFloatBuffer& () const` — Implicit conversion to Audio::FAlignedFloatBuffer
- L101 _public function_ `inline operator Audio::FAlignedFloatBuffer& ()` — Implicit conversion to Audio::FAlignedFloatBuffer WARNING: if the buffer is resized, it will cause errors.
- L110 _public function_ `inline operator TArrayView<const float> () const` — Implicit conversion to Audio::FAlignedFloatBuffer
- L122 _public function_ `inline operator TArrayView<float> ()` — Implicit conversion to Audio::FAlignedFloatBuffer WARNING: if the buffer is resized, it will cause errors.
- L130 _public function_ `inline void Zero()`
- L140 _private member_ `Audio::FAlignedFloatBuffer Buffer;`
- L143 _private member_ `int32 InitialNum;`

#### class `Metasound::IAudioDataType`  
`class IAudioDataType`  
_L151-163_
- desc: This empty base class is used so that we can specialize various nodes (Send, Receive, etc.) for subclasses of IAudioDatatype.

#### Free symbols / members of external scopes

- L12 _macro_ `#define METASOUNDGRAPHCORE_CHECKAUDIONUM !(UE_BUILD_SHIPPING || UE_BUILD_TEST)` — Define which determines whether to check that the size of the audio buffer has not changed since initialization
- L14 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundBasicNode.h` (Public)


#### class `Metasound::FBasicNode`  
`class FBasicNode : public INode`  
_L12-46_
- inherits: `INode`
- L20 _public prototype_ `FBasicNode(const FNodeData& InNodeData, const TSharedRef<const FNodeClassMetadata>& InClassMetadata);` — Construct a basic node. @param InNodeData - Information unique to this node instance. @param InClassMetadata - Shared object representing the node class.
- L22 _public prototype_ `virtual ~FBasicNode() = default;`
- L25 _public prototype_ `virtual const FName& GetInstanceName() const override;` — Return the name of this specific instance of the node class.
- L28 _public prototype_ `virtual const FGuid& GetInstanceID() const override;` — Return the ID of this specific instance of the node class.
- L31 _public prototype_ `virtual const FNodeClassMetadata& GetMetadata() const override;` — Return metadata associated with this node.
- L34 _public prototype_ `virtual const FVertexInterface& GetVertexInterface() const override;` — Return the interface associated with this node instance.
- L37 _public prototype_ `virtual void SetDefaultInput(const FVertexName& InVertexName, const FLiteral& InLiteral) override;` — Set the default literal for an input vertex.
- L40 _public prototype_ `virtual TSharedPtr<const IOperatorData> GetOperatorData() const override;` — Return the configuration for this node.
- L44 _private member_ `FNodeData NodeData;`
- L45 _private member_ `TSharedRef<const FNodeClassMetadata> ClassMetadata;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L10 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundBuildError.h` (Public)


#### class `Metasound::FBuildErrorBase`  
`class FBuildErrorBase : public IOperatorBuildError`  
_L20-73_
- inherits: `IOperatorBuildError`
- desc: FBuildErrorBase A general build error which contains a error type and human readable error description.
- L24 _public prototype_ `FBuildErrorBase(const FName& InErrorType, const FText& InErrorDescription);`
- L26 _public prototype_ `virtual ~FBuildErrorBase() = default;`
- L29 _public prototype_ `virtual const FName& GetErrorType() const override;` — Returns the type of error.
- L32 _public prototype_ `virtual const FText& GetErrorDescription() const override;` — Returns a human readable error description.
- L35 _public prototype_ `virtual const TArray<FInputDataDestination>& GetInputDataDestinations() const override;` — Returns an array of destinations associated with the error.
- L38 _public prototype_ `virtual const TArray<FOutputDataSource>& GetOutputDataSources() const override;` — Returns an array of sources associated with the error.
- L41 _public prototype_ `virtual const TArray<FDataEdge>& GetDataEdges() const override;` — Returns an array of edges associated with the error.
- L44 _public prototype_ `virtual const TArray<const INode*>& GetNodes() const override;` — Returns an array of Nodes associated with the error.
- L49 _protected prototype_ `void AddInputDataDestination(const FInputDataDestination& InInputDataDestination);` — Add input destinations to be associated with error.
- L50 _protected prototype_ `void AddInputDataDestinations(TArrayView<const FInputDataDestination> InInputDataDestinations);`
- L53 _protected prototype_ `void AddOutputDataSource(const FOutputDataSource& InOutputDataSource);` — Add input destinations to be associated with error.
- L54 _protected prototype_ `void AddOutputDataSources(TArrayView<const FOutputDataSource> InOutputDataSources);`
- L57 _protected prototype_ `void AddDataEdge(const FDataEdge& InEdge);` — Add edges to be associated with error.
- L58 _protected prototype_ `void AddDataEdges(TArrayView<const FDataEdge> InEdges);`
- L61 _protected prototype_ `void AddNode(const INode& InNode);` — Add nodes to be associated with error.
- L62 _protected prototype_ `void AddNodes(TArrayView<INode const* const> InNodes);`
- L66 _private member_ `FName ErrorType;`
- L67 _private member_ `FText ErrorDescription;`
- L69 _private member_ `TArray<const INode*> Nodes;`
- L70 _private member_ `TArray<FDataEdge> Edges;`
- L71 _private member_ `TArray<FInputDataDestination> Destinations;`
- L72 _private member_ `TArray<FOutputDataSource> Sources;`

#### class `Metasound::FDanglingVertexError`  
`class FDanglingVertexError : public FBuildErrorBase`  
_L80-95_
- inherits: `FBuildErrorBase`
- desc: FDanglingVertexError Caused by FDataEdges, FInputDataDestinations or FOutputDataSources pointing to null nodes.
- L83 _public member_ `static const FName ErrorType;`
- L85 _public prototype_ `FDanglingVertexError(const FInputDataDestination& InDest);`
- L86 _public prototype_ `FDanglingVertexError(const FOutputDataSource& InSource);`
- L87 _public prototype_ `FDanglingVertexError(const FDataEdge& InEdge);`
- L89 _public prototype_ `virtual ~FDanglingVertexError() = default;`
- L92 _protected prototype_ `FDanglingVertexError();`

#### class `Metasound::FMissingVertexError`  
`class FMissingVertexError : public FBuildErrorBase`  
_L101-112_
- inherits: `FBuildErrorBase`
- desc: FMissingVertexError Caused by a referenced FDataVertex which does not exist on a node.
- L104 _public member_ `static const FName ErrorType;`
- L106 _public prototype_ `FMissingVertexError(const FInputDataDestination& InDestination);`
- L107 _public prototype_ `FMissingVertexError(const FOutputDataSource& InSource);`
- L109 _public prototype_ `virtual ~FMissingVertexError() = default;`

#### class `Metasound::FDuplicateInputError`  
`class FDuplicateInputError : public FBuildErrorBase`  
_L119-129_
- inherits: `FBuildErrorBase`
- desc: FDuplicateInputError Caused by multiple FDataEdges pointing same FInputDataDestination
- L122 _public member_ `static const FName ErrorType;`
- L124 _public prototype_ `FDuplicateInputError(const TArrayView<FDataEdge> InEdges);`
- L126 _public prototype_ `virtual ~FDuplicateInputError() = default;`

#### class `Metasound::FGraphCycleError`  
`class FGraphCycleError : public FBuildErrorBase`  
_L135-145_
- inherits: `FBuildErrorBase`
- desc: FGraphCycleError Caused by circular paths in graph.
- L138 _public member_ `static const FName ErrorType;`
- L140 _public prototype_ `FGraphCycleError(TArrayView<INode const* const> InNodes, const TArray<FDataEdge>& InEdges);`
- L142 _public prototype_ `virtual ~FGraphCycleError() = default;`

#### class `Metasound::FNodePrunedError`  
`class FNodePrunedError : public FBuildErrorBase`  
_L152-162_
- inherits: `FBuildErrorBase`
- desc: FNodePrunedError Caused by nodes which are in the graph but unreachable from the graph's inputs and/or outputs.
- L155 _public member_ `static const FName ErrorType;`
- L157 _public prototype_ `FNodePrunedError(const INode* InNode);`
- L159 _public prototype_ `virtual ~FNodePrunedError() = default;`

#### class `Metasound::FInternalError`  
`class FInternalError : public FBuildErrorBase`  
_L168-183_
- inherits: `FBuildErrorBase`
- desc: FInternalError Caused by internal state or logic errors.
- L171 _public member_ `static const FName ErrorType;`
- L173 _public prototype_ `FInternalError(const FString& InFileName, int32 InLineNumber);`
- L175 _public prototype_ `virtual ~FInternalError() = default;`
- L177 _public prototype_ `const FString& GetFileName() const;`
- L178 _public prototype_ `int32 GetLineNumber() const;`
- L181 _private member_ `FString FileName;`
- L182 _private member_ `int32 LineNumber;`

#### class `Metasound::FMissingInputDataReferenceError`  
`class FMissingInputDataReferenceError : public FBuildErrorBase`  
_L190-199_
- inherits: `FBuildErrorBase`
- desc: FMissingInputDataReferenceError Caused by IOperators not exposing expected IDataReferences in their input FDataReferenceCollection
- L194 _public member_ `static const FName ErrorType;`
- L196 _public prototype_ `FMissingInputDataReferenceError(const FInputDataDestination& InInputDataDestination);`
- L198 _public prototype_ `virtual ~FMissingInputDataReferenceError() = default;`

#### class `Metasound::FMissingOutputDataReferenceError`  
`class FMissingOutputDataReferenceError : public FBuildErrorBase`  
_L206-216_
- inherits: `FBuildErrorBase`
- desc: FMissingOutputDataReferenceError Caused by IOperators not exposing expected IDataReferences in their output FDataReferenceCollection
- L210 _public member_ `static const FName ErrorType;`
- L212 _public prototype_ `FMissingOutputDataReferenceError(const FOutputDataSource& InOutputDataSource);`
- L214 _public prototype_ `virtual ~FMissingOutputDataReferenceError() = default;`

#### class `Metasound::FInvalidConnectionDataTypeError`  
`class FInvalidConnectionDataTypeError : public FBuildErrorBase`  
_L223-232_
- inherits: `FBuildErrorBase`
- desc: FInvalidConnectionDataTypeError Caused when edges describe a connection between vertices with different data types.
- L227 _public member_ `static const FName ErrorType;`
- L229 _public prototype_ `FInvalidConnectionDataTypeError(const FDataEdge& InEdge);`
- L231 _public prototype_ `virtual ~FInvalidConnectionDataTypeError() = default;`

#### class `Metasound::FInputReceiverInitializationError`  
`class FInputReceiverInitializationError : public FBuildErrorBase`  
_L238-247_
- inherits: `FBuildErrorBase`
- desc: FInputReceiverInitializationError Caused by Inputs that are set to enable transmission fail to create a receiver.
- L242 _public member_ `static const FName ErrorType;`
- L244 _public prototype_ `FInputReceiverInitializationError(const INode& InInputNode, const FName& InVertexKey, const FName& InDataType);`
- L246 _public prototype_ `virtual ~FInputReceiverInitializationError() = default;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L13 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundBuilderInterface.h` (Public)


#### class `Metasound::IOperatorBuildError`  
`class IOperatorBuildError`  
_L25-47_
- desc: IOperatorBuildError This interface is intended for errors encountered when building an GraphOperator.
- L28 _public prototype_ `virtual ~IOperatorBuildError() = default;`
- L31 _public prototype_ `virtual const FName& GetErrorType() const = 0;` — Returns the type of error.
- L34 _public prototype_ `virtual const FText& GetErrorDescription() const = 0;` — Returns a human readable error description.
- L37 _public prototype_ `virtual const TArray<FInputDataDestination>& GetInputDataDestinations() const = 0;` — Returns an array of destinations associated with the error.
- L40 _public prototype_ `virtual const TArray<FOutputDataSource>& GetOutputDataSources() const = 0;` — Returns an array of sources associated with the error.
- L43 _public prototype_ `virtual const TArray<const INode*>& GetNodes() const = 0;` — Returns an array of Nodes associated with the error.
- L46 _public prototype_ `virtual const TArray<FDataEdge>& GetDataEdges() const = 0;` — Returns an array of edges associated with the error.

#### struct `Metasound::FBuildResults`  
`struct FBuildResults`  
_L53-60_
- desc: Structure of all resulting data generated during graph operator build.
- L56 _public member_ `FBuildErrorArray Errors;` — An array of errors. Errors can be added if issues occur while creating an IOperator.
- L59 _public member_ `TMap<FGuid, FDataReferenceCollection> InternalDataReferences;` — Internal data references if enabled by build settings (not populated if disabled).

#### struct `Metasound::FBuildOperatorParams`  
`struct FBuildOperatorParams`  
_L65-100_
- desc: FBuildOperatorParams holds the parameters provided to operator factories during the creation of an IOperator
- L67 _public function_ `FBuildOperatorParams(const INode& InNode, const FOperatorSettings& InOperatorSettings, const FInputVertexInterfaceData& InInputData, const FMetasoundEnvironment& InEnvironment, const IOperatorBuilder* InBuilder=nullptr, FGraphRenderCost* InGraphRenderCost=nullptr) : Node(InNode) , OperatorSettings(InOperatorSettings) , InputData(InInputData) , Environment(InEnvironment) , Builder(InBuilder) , GraphRenderCost(InGraphRenderCost)`
- L78 _public member_ `const INode& Node;` — The node associated with this factory and the desired IOperator.
- L81 _public member_ `const FOperatorSettings& OperatorSettings;` — General operator settings for the graph.
- L84 _public member_ `const FInputVertexInterfaceData& InputData;` — Input data references for an IOperator
- L87 _public member_ `const FMetasoundEnvironment& Environment;` — Environment settings available.
- L90 _public member_ `const IOperatorBuilder* Builder = nullptr;` — Pointer to builder actively building graph.
- L93 _public member_ `FGraphRenderCost* GraphRenderCost = nullptr;` — Runtime render cost tracker.
- L96 _public function_ `operator IOperator::FResetParams() const` — Implicit conversion to FResetParams for convenience.

#### struct `Metasound::FBuildGraphParams`  
`struct FBuildGraphParams`  
_L104-117_
- desc: Parameters for building an operator from a graph.
- L107 _public member_ `const IGraph& Graph;` — Reference to graph being built.
- L110 _public member_ `const FOperatorSettings& OperatorSettings;` — General operator settings for the graph.
- L113 _public member_ `const FDataReferenceCollection& InputDataReferences;` — Collection of input parameters available for an IOperator.
- L116 _public member_ `const FMetasoundEnvironment& Environment;` — Environment settings available.

#### struct `Metasound::FBuildGraphOperatorParams`  
`struct FBuildGraphOperatorParams`  
_L120-155_
- desc: Parameters for building an operator from a graph.
- L122 _public function_ `FBuildGraphOperatorParams(const IGraph& InGraph, const FOperatorSettings& InOperatorSettings, const FInputVertexInterfaceData& InInputData, const FMetasoundEnvironment& InEnvironment, FGraphRenderCost* InGraphRenderCost=nullptr) : Graph(InGraph) , OperatorSettings(InOperatorSettings) , InputData(InInputData) , Environment(InEnvironment) , GraphRenderCost(InGraphRenderCost)`
- L132 _public member_ `const IGraph& Graph;` — Reference to graph being built.
- L135 _public member_ `const FOperatorSettings& OperatorSettings;` — General operator settings for the graph.
- L138 _public member_ `const FInputVertexInterfaceData& InputData;` — Bound input data available for an IOperator.
- L141 _public member_ `const FMetasoundEnvironment& Environment;` — Environment settings available.
- L144 _public member_ `FGraphRenderCost* GraphRenderCost = nullptr;` — Runtime render cost tracker.
- L146 _public member_ `FName ClassName;`
- L147 _public member_ `FName AssetName;`
- L148 _public member_ `FName AssetPath;`
- L151 _public function_ `static FBuildGraphOperatorParams FromBuildOperatorParams(const IGraph& InGraph, const FBuildOperatorParams& InParams)` — Convert operator building params to graph building params

#### class `Metasound::IOperatorFactory`  
`class IOperatorFactory`  
_L180-186_
- desc: IOperatorFactory IOperatorFactory defines an interface for building an IOperator from an INode.  In practice, each INode returns its own IOperatorFactory through the INode::GetDefaultOperatorFactory() member function.
- L183 _public prototype_ `virtual ~IOperatorFactory() = default;`
- L185 _public prototype_ `virtual TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults) = 0;`

#### class `Metasound::IOperatorBuilder`  
`class IOperatorBuilder`  
_L193-209_
- desc: IOperatorBuilder Defines an interface for building a graph of operators from a graph of nodes.
- L197 _public typedef_ `using FBuildErrorPtr = TUniquePtr<IOperatorBuildError>;` — A TUniquePtr of an IOperatorBuildError
- L199 _public prototype_ `virtual ~IOperatorBuilder() = default;`
- L208 _public prototype_ `virtual TUniquePtr<IOperator> BuildGraphOperator(const FBuildGraphOperatorParams& InParams, FBuildResults& OutResults) const = 0;` — Build a graph operator from a graph. @params InParams - Input parameters for building a graph. @param OutResults - Results data pertaining to the given build operator result. @return A unique pointer to the built IOperator. Null if build failed.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Metasound`
- L50 _typedef_ `using FBuildErrorArray = TArray<TUniquePtr<IOperatorBuildError>>;` (scope `Metasound`) — Array of build errors.
- L168 _function_ `template<typename ErrorType, typename... ArgTypes> void AddBuildError(FBuildErrorArray& OutErrors, ArgTypes&&... Args)` (scope `Metasound`) — Convenience template for adding build errors. The function can be used in the following way: FBuildErrorArray MyErrorArray; AddBuildError<FMyBuildErrorType>(MyErrorArray, MyBuildErrorConstructorArgs...); @param OutErrors - Array which holds the errors. @param Args - Constructor arguments for the error.

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundDataFactory.h` (Public)


#### struct `Metasound::DataFactoryPrivate::TDataTypeConstructorTraits`  
`template<typename DataType, typename... ArgTypes> struct TDataTypeConstructorTraits`  
_L24-37_
- desc: Description of available constructors for a registered Metasound Data Type. @tparam DataType - The registered Metasound Data Type. @tparam ArgTypes - A parameter pack of arguments to be passed to the data type's constructor.
- L27 _public member_ `static constexpr bool bIsArrayDefaultConstructible = false;` — Array construction for TArray types.
- L28 _public member_ `static constexpr bool bIsArrayConstructibleWithSettings = false;`
- L29 _public member_ `static constexpr bool bIsArrayConstructibleWithArgs = false;`
- L30 _public member_ `static constexpr bool bIsArrayConstructibleWithSettingsAndArgs = false;`
- L33 _public member_ `static constexpr bool bIsDefaultConstructible = std::is_constructible<DataType>::value || CHasFactoryFunctionDefaultConstruction<DataType>;` — DataType Construction
- L34 _public member_ `static constexpr bool bIsConstructibleWithSettings = std::is_constructible<DataType, const FOperatorSettings&>::value || CHasFactoryFunctionWithSettings<DataType>;`
- L35 _public member_ `static constexpr bool bIsConstructibleWithArgs = std::is_constructible<DataType, ArgTypes...>::value || CHasFactoryFunctionWithArgs<DataType, ArgTypes...>;`
- L36 _public member_ `static constexpr bool bIsConstructibleWithSettingsAndArgs = std::is_constructible<DataType, const FOperatorSettings&, ArgTypes...>::value || CHasFactoryFunctionWithSettingsAndArgs<DataType, ArgTypes...>;`
- L46 _private typedef_ `using DataType = TArray<ElementType>;`
- L47 _private typedef_ `using ElementConstructorTraits = TDataTypeConstructorTraits<ElementType, OtherElementType>;`
- L51 _private member_ `static constexpr bool bIsOtherElementNone = std::is_same<FLiteral::FNone, OtherElementType>::value;` — FLiteral::FNone is a special case where an array of TArray<FLiteral::FNone> only determines the number of elements that should be default constructed.
- L56 _public member_ `static constexpr bool bIsArrayDefaultConstructible = ElementConstructorTraits::bIsDefaultConstructible && bIsOtherElementNone;` — Array construction of TArray types.
- L57 _public member_ `static constexpr bool bIsArrayConstructibleWithSettings = ElementConstructorTraits::bIsConstructibleWithSettings && bIsOtherElementNone;`
- L58 _public member_ `static constexpr bool bIsArrayConstructibleWithArgs = ElementConstructorTraits::bIsConstructibleWithArgs;`
- L59 _public member_ `static constexpr bool bIsArrayConstructibleWithSettingsAndArgs = ElementConstructorTraits::bIsConstructibleWithSettingsAndArgs;`
- L62 _public member_ `static constexpr bool bIsDefaultConstructible = std::is_constructible<DataType>::value;` — TArray construction
- L63 _public member_ `static constexpr bool bIsConstructibleWithSettings = std::is_constructible<DataType, const FOperatorSettings&>::value;`
- L64 _public member_ `static constexpr bool bIsConstructibleWithArgs = std::is_constructible<ElementType, OtherElementType>::value;`
- L66 _public member_ `static constexpr bool bIsConstructibleWithSettingsAndArgs = false;` — TArray does not take operator settings.

#### struct `Metasound::DataFactoryPrivate::TDataTypeConstructorTraits`  
`template<typename ElementType, typename OtherElementType> struct TDataTypeConstructorTraits<TArray<ElementType>, TArray<OtherElementType>>`  
_L43-67_
- desc: Partial specialization for TArray<> types. A TArray can be constructed elementwise with an array containing constructor args.
- L27 _public member_ `static constexpr bool bIsArrayDefaultConstructible = false;` — Array construction for TArray types.
- L28 _public member_ `static constexpr bool bIsArrayConstructibleWithSettings = false;`
- L29 _public member_ `static constexpr bool bIsArrayConstructibleWithArgs = false;`
- L30 _public member_ `static constexpr bool bIsArrayConstructibleWithSettingsAndArgs = false;`
- L33 _public member_ `static constexpr bool bIsDefaultConstructible = std::is_constructible<DataType>::value || CHasFactoryFunctionDefaultConstruction<DataType>;` — DataType Construction
- L34 _public member_ `static constexpr bool bIsConstructibleWithSettings = std::is_constructible<DataType, const FOperatorSettings&>::value || CHasFactoryFunctionWithSettings<DataType>;`
- L35 _public member_ `static constexpr bool bIsConstructibleWithArgs = std::is_constructible<DataType, ArgTypes...>::value || CHasFactoryFunctionWithArgs<DataType, ArgTypes...>;`
- L36 _public member_ `static constexpr bool bIsConstructibleWithSettingsAndArgs = std::is_constructible<DataType, const FOperatorSettings&, ArgTypes...>::value || CHasFactoryFunctionWithSettingsAndArgs<DataType, ArgTypes...>;`
- L46 _private typedef_ `using DataType = TArray<ElementType>;`
- L47 _private typedef_ `using ElementConstructorTraits = TDataTypeConstructorTraits<ElementType, OtherElementType>;`
- L51 _private member_ `static constexpr bool bIsOtherElementNone = std::is_same<FLiteral::FNone, OtherElementType>::value;` — FLiteral::FNone is a special case where an array of TArray<FLiteral::FNone> only determines the number of elements that should be default constructed.
- L56 _public member_ `static constexpr bool bIsArrayDefaultConstructible = ElementConstructorTraits::bIsDefaultConstructible && bIsOtherElementNone;` — Array construction of TArray types.
- L57 _public member_ `static constexpr bool bIsArrayConstructibleWithSettings = ElementConstructorTraits::bIsConstructibleWithSettings && bIsOtherElementNone;`
- L58 _public member_ `static constexpr bool bIsArrayConstructibleWithArgs = ElementConstructorTraits::bIsConstructibleWithArgs;`
- L59 _public member_ `static constexpr bool bIsArrayConstructibleWithSettingsAndArgs = ElementConstructorTraits::bIsConstructibleWithSettingsAndArgs;`
- L62 _public member_ `static constexpr bool bIsDefaultConstructible = std::is_constructible<DataType>::value;` — TArray construction
- L63 _public member_ `static constexpr bool bIsConstructibleWithSettings = std::is_constructible<DataType, const FOperatorSettings&>::value;`
- L64 _public member_ `static constexpr bool bIsConstructibleWithArgs = std::is_constructible<ElementType, OtherElementType>::value;`
- L66 _public member_ `static constexpr bool bIsConstructibleWithSettingsAndArgs = false;` — TArray does not take operator settings.

#### struct `Metasound::DataFactoryPrivate::TDataTypeVariantConstructorTraits`  
`template<typename DataType, typename ArgType, typename... AdditionalTypes> struct TDataTypeVariantConstructorTraits<DataType, ArgType, AdditionalTypes...>`  
_L81-102_
- desc: Specialization for unrolling parameter packs.
- L86 _private typedef_ `using FAdditionalConstructorTraits = TDataTypeVariantConstructorTraits<DataType, AdditionalTypes...>;` — Recursive declaration to get constructor traits for the additional types.
- L89 _private typedef_ `using FArgConstructorTraits = TDataTypeConstructorTraits<DataType, ArgType>;` — Constructor traits for this ArgType
- L93 _public member_ `static constexpr bool bIsArrayDefaultConstructible = FAdditionalConstructorTraits::bIsArrayDefaultConstructible;`
- L94 _public member_ `static constexpr bool bIsArrayConstructibleWithSettings = FAdditionalConstructorTraits::bIsArrayConstructibleWithSettings;`
- L95 _public member_ `static constexpr bool bIsArrayConstructibleWithArgs = FArgConstructorTraits::bIsArrayConstructibleWithArgs || FAdditionalConstructorTraits::bIsArrayConstructibleWithArgs;`
- L96 _public member_ `static constexpr bool bIsArrayConstructibleWithSettingsAndArgs = FArgConstructorTraits::bIsArrayConstructibleWithSettingsAndArgs || FAdditionalConstructorTraits::bIsArrayConstructibleWithSettingsAndArgs;`
- L98 _public member_ `static constexpr bool bIsDefaultConstructible = FAdditionalConstructorTraits::bIsDefaultConstructible;`
- L99 _public member_ `static constexpr bool bIsConstructibleWithSettings = FAdditionalConstructorTraits::bIsConstructibleWithSettings;`
- L100 _public member_ `static constexpr bool bIsConstructibleWithArgs = FArgConstructorTraits::bIsConstructibleWithArgs || FAdditionalConstructorTraits::bIsConstructibleWithArgs;`
- L101 _public member_ `static constexpr bool bIsConstructibleWithSettingsAndArgs = FArgConstructorTraits::bIsConstructibleWithSettingsAndArgs || FAdditionalConstructorTraits::bIsConstructibleWithSettingsAndArgs;`
- L109 _public typedef_ `using FConstructorTraits = TDataTypeConstructorTraits<DataType, ArgType>;` — Constructor traits for this arg type.
- L112 _public member_ `static constexpr bool bIsArrayDefaultConstructible = FConstructorTraits::bIsArrayDefaultConstructible;`
- L113 _public member_ `static constexpr bool bIsArrayConstructibleWithSettings = FConstructorTraits::bIsArrayConstructibleWithSettings;`
- L114 _public member_ `static constexpr bool bIsArrayConstructibleWithArgs = FConstructorTraits::bIsArrayConstructibleWithArgs;`
- L115 _public member_ `static constexpr bool bIsArrayConstructibleWithSettingsAndArgs = FConstructorTraits::bIsArrayConstructibleWithSettingsAndArgs;`
- L117 _public member_ `static constexpr bool bIsDefaultConstructible = FConstructorTraits::bIsDefaultConstructible;`
- L118 _public member_ `static constexpr bool bIsConstructibleWithSettings = FConstructorTraits::bIsConstructibleWithSettings;`
- L119 _public member_ `static constexpr bool bIsConstructibleWithArgs = FConstructorTraits::bIsConstructibleWithArgs;`
- L120 _public member_ `static constexpr bool bIsConstructibleWithSettingsAndArgs = FConstructorTraits::bIsConstructibleWithSettingsAndArgs;`
- L129 _private typedef_ `using FConstructorTraits = TDataTypeVariantConstructorTraits<DataType, FirstVariantType, AdditionalVariantTypes...>;`

#### struct `Metasound::DataFactoryPrivate::TDataTypeVariantConstructorTraits`  
``  
_L106-121_
- L86 _private typedef_ `using FAdditionalConstructorTraits = TDataTypeVariantConstructorTraits<DataType, AdditionalTypes...>;` — Recursive declaration to get constructor traits for the additional types.
- L89 _private typedef_ `using FArgConstructorTraits = TDataTypeConstructorTraits<DataType, ArgType>;` — Constructor traits for this ArgType
- L93 _public member_ `static constexpr bool bIsArrayDefaultConstructible = FAdditionalConstructorTraits::bIsArrayDefaultConstructible;`
- L94 _public member_ `static constexpr bool bIsArrayConstructibleWithSettings = FAdditionalConstructorTraits::bIsArrayConstructibleWithSettings;`
- L95 _public member_ `static constexpr bool bIsArrayConstructibleWithArgs = FArgConstructorTraits::bIsArrayConstructibleWithArgs || FAdditionalConstructorTraits::bIsArrayConstructibleWithArgs;`
- L96 _public member_ `static constexpr bool bIsArrayConstructibleWithSettingsAndArgs = FArgConstructorTraits::bIsArrayConstructibleWithSettingsAndArgs || FAdditionalConstructorTraits::bIsArrayConstructibleWithSettingsAndArgs;`
- L98 _public member_ `static constexpr bool bIsDefaultConstructible = FAdditionalConstructorTraits::bIsDefaultConstructible;`
- L99 _public member_ `static constexpr bool bIsConstructibleWithSettings = FAdditionalConstructorTraits::bIsConstructibleWithSettings;`
- L100 _public member_ `static constexpr bool bIsConstructibleWithArgs = FArgConstructorTraits::bIsConstructibleWithArgs || FAdditionalConstructorTraits::bIsConstructibleWithArgs;`
- L101 _public member_ `static constexpr bool bIsConstructibleWithSettingsAndArgs = FArgConstructorTraits::bIsConstructibleWithSettingsAndArgs || FAdditionalConstructorTraits::bIsConstructibleWithSettingsAndArgs;`
- L109 _public typedef_ `using FConstructorTraits = TDataTypeConstructorTraits<DataType, ArgType>;` — Constructor traits for this arg type.
- L112 _public member_ `static constexpr bool bIsArrayDefaultConstructible = FConstructorTraits::bIsArrayDefaultConstructible;`
- L113 _public member_ `static constexpr bool bIsArrayConstructibleWithSettings = FConstructorTraits::bIsArrayConstructibleWithSettings;`
- L114 _public member_ `static constexpr bool bIsArrayConstructibleWithArgs = FConstructorTraits::bIsArrayConstructibleWithArgs;`
- L115 _public member_ `static constexpr bool bIsArrayConstructibleWithSettingsAndArgs = FConstructorTraits::bIsArrayConstructibleWithSettingsAndArgs;`
- L117 _public member_ `static constexpr bool bIsDefaultConstructible = FConstructorTraits::bIsDefaultConstructible;`
- L118 _public member_ `static constexpr bool bIsConstructibleWithSettings = FConstructorTraits::bIsConstructibleWithSettings;`
- L119 _public member_ `static constexpr bool bIsConstructibleWithArgs = FConstructorTraits::bIsConstructibleWithArgs;`
- L120 _public member_ `static constexpr bool bIsConstructibleWithSettingsAndArgs = FConstructorTraits::bIsConstructibleWithSettingsAndArgs;`
- L129 _private typedef_ `using FConstructorTraits = TDataTypeVariantConstructorTraits<DataType, FirstVariantType, AdditionalVariantTypes...>;`

#### struct `Metasound::DataFactoryPrivate::TDataTypeVariantConstructorTraits`  
`template<typename DataType, typename FirstVariantType, typename... AdditionalVariantTypes> struct TDataTypeVariantConstructorTraits<DataType, TVariant<FirstVariantType, AdditionalVariantTypes...>>`  
_L125-142_
- desc: Specialization for unpacking the types supported by a TVariant.
- L86 _private typedef_ `using FAdditionalConstructorTraits = TDataTypeVariantConstructorTraits<DataType, AdditionalTypes...>;` — Recursive declaration to get constructor traits for the additional types.
- L89 _private typedef_ `using FArgConstructorTraits = TDataTypeConstructorTraits<DataType, ArgType>;` — Constructor traits for this ArgType
- L93 _public member_ `static constexpr bool bIsArrayDefaultConstructible = FAdditionalConstructorTraits::bIsArrayDefaultConstructible;`
- L94 _public member_ `static constexpr bool bIsArrayConstructibleWithSettings = FAdditionalConstructorTraits::bIsArrayConstructibleWithSettings;`
- L95 _public member_ `static constexpr bool bIsArrayConstructibleWithArgs = FArgConstructorTraits::bIsArrayConstructibleWithArgs || FAdditionalConstructorTraits::bIsArrayConstructibleWithArgs;`
- L96 _public member_ `static constexpr bool bIsArrayConstructibleWithSettingsAndArgs = FArgConstructorTraits::bIsArrayConstructibleWithSettingsAndArgs || FAdditionalConstructorTraits::bIsArrayConstructibleWithSettingsAndArgs;`
- L98 _public member_ `static constexpr bool bIsDefaultConstructible = FAdditionalConstructorTraits::bIsDefaultConstructible;`
- L99 _public member_ `static constexpr bool bIsConstructibleWithSettings = FAdditionalConstructorTraits::bIsConstructibleWithSettings;`
- L100 _public member_ `static constexpr bool bIsConstructibleWithArgs = FArgConstructorTraits::bIsConstructibleWithArgs || FAdditionalConstructorTraits::bIsConstructibleWithArgs;`
- L101 _public member_ `static constexpr bool bIsConstructibleWithSettingsAndArgs = FArgConstructorTraits::bIsConstructibleWithSettingsAndArgs || FAdditionalConstructorTraits::bIsConstructibleWithSettingsAndArgs;`
- L109 _public typedef_ `using FConstructorTraits = TDataTypeConstructorTraits<DataType, ArgType>;` — Constructor traits for this arg type.
- L112 _public member_ `static constexpr bool bIsArrayDefaultConstructible = FConstructorTraits::bIsArrayDefaultConstructible;`
- L113 _public member_ `static constexpr bool bIsArrayConstructibleWithSettings = FConstructorTraits::bIsArrayConstructibleWithSettings;`
- L114 _public member_ `static constexpr bool bIsArrayConstructibleWithArgs = FConstructorTraits::bIsArrayConstructibleWithArgs;`
- L115 _public member_ `static constexpr bool bIsArrayConstructibleWithSettingsAndArgs = FConstructorTraits::bIsArrayConstructibleWithSettingsAndArgs;`
- L117 _public member_ `static constexpr bool bIsDefaultConstructible = FConstructorTraits::bIsDefaultConstructible;`
- L118 _public member_ `static constexpr bool bIsConstructibleWithSettings = FConstructorTraits::bIsConstructibleWithSettings;`
- L119 _public member_ `static constexpr bool bIsConstructibleWithArgs = FConstructorTraits::bIsConstructibleWithArgs;`
- L120 _public member_ `static constexpr bool bIsConstructibleWithSettingsAndArgs = FConstructorTraits::bIsConstructibleWithSettingsAndArgs;`
- L129 _private typedef_ `using FConstructorTraits = TDataTypeVariantConstructorTraits<DataType, FirstVariantType, AdditionalVariantTypes...>;`

#### struct `Metasound::DataFactoryPrivate::TExplicitConstructorForwarding`  
`template<typename DataType, typename... ArgTypes> struct TExplicitConstructorForwarding`  
_L152-162_
- desc: Denotes that both FOperatorSettings and parameter pack arguments must be used in the constructor of the Metasound Data Type. @tparam DataType - The registered Metasound Data Type. @tparam ArgTypes - A parameter pack of arguments to be passed to the data type's constructor.
- L154 _public typedef_ `using TConstructorTraits = TDataTypeConstructorTraits<DataType, ArgTypes...>;`
- L156 _public member_ `static constexpr bool bForwardSettingsAndArgs = TConstructorTraits::bIsConstructibleWithSettingsAndArgs || CHasFactoryFunctionWithSettingsAndArgs<DataType, ArgTypes...>;`
- L157 _public member_ `static constexpr bool bForwardArgs = false;`
- L158 _public member_ `static constexpr bool bForwardSettings = false;`
- L159 _public member_ `static constexpr bool bForwardNone = false;`
- L161 _public member_ `static constexpr bool bCannotForwardToConstructor = !(bForwardSettingsAndArgs || bForwardArgs || bForwardSettings || bForwardNone);`

#### struct `Metasound::DataFactoryPrivate::TExplicitArgsConstructorForwarding`  
`template<typename DataType, typename... ArgTypes> struct TExplicitArgsConstructorForwarding`  
_L171-181_
- desc: Denotes that parameter pack arguments must be used in the constructor of the Metasound Data Type. The use of the FOperatorSettings is optional. @tparam DataType - The registered Metasound Data Type. @tparam ArgTypes - A parameter pack of arguments to be passed to the data type's constructor.
- L173 _public typedef_ `using TConstructorTraits = TDataTypeConstructorTraits<DataType, ArgTypes...>;`
- L175 _public member_ `static constexpr bool bForwardSettingsAndArgs = TConstructorTraits::bIsConstructibleWithSettingsAndArgs || CHasFactoryFunctionWithSettingsAndArgs<DataType, ArgTypes...>;`
- L176 _public member_ `static constexpr bool bForwardArgs = !bForwardSettingsAndArgs && (TConstructorTraits::bIsConstructibleWithArgs || CHasFactoryFunctionWithArgs<DataType, ArgTypes...>);`
- L177 _public member_ `static constexpr bool bForwardSettings = false;`
- L178 _public member_ `static constexpr bool bForwardNone = false;`
- L180 _public member_ `static constexpr bool bCannotForwardToConstructor = !(bForwardSettingsAndArgs || bForwardArgs || bForwardSettings || bForwardNone);`

#### struct `Metasound::DataFactoryPrivate::TAnyConstructorForwarding`  
`template<typename DataType, typename... ArgTypes> struct TAnyConstructorForwarding`  
_L190-200_
- desc: Denotes that parameter pack arguments and/or FOperatorSettings is optional when constructing the Metasound Data Type. @tparam DataType - The registered Metasound Data Type. @tparam ArgTypes - A parameter pack of arguments to be passed to the data type's constructor.
- L192 _public typedef_ `using TConstructorTraits = TDataTypeConstructorTraits<DataType, ArgTypes...>;`
- L194 _public member_ `static constexpr bool bForwardSettingsAndArgs = TConstructorTraits::bIsConstructibleWithSettingsAndArgs || CHasFactoryFunctionWithSettingsAndArgs<DataType, ArgTypes...>;`
- L195 _public member_ `static constexpr bool bForwardArgs = !bForwardSettingsAndArgs && (TConstructorTraits::bIsConstructibleWithArgs || CHasFactoryFunctionWithArgs<DataType, ArgTypes...>);`
- L196 _public member_ `static constexpr bool bForwardSettings = !(bForwardArgs || bForwardSettingsAndArgs) && (TConstructorTraits::bIsConstructibleWithSettings || CHasFactoryFunctionWithSettings<DataType>);`
- L197 _public member_ `static constexpr bool bForwardNone = !(bForwardArgs || bForwardSettingsAndArgs || bForwardSettings) && (TConstructorTraits::bIsDefaultConstructible || CHasFactoryFunctionDefaultConstruction<DataType>);`
- L199 _public member_ `static constexpr bool bCannotForwardToConstructor = !(bForwardSettingsAndArgs || bForwardArgs || bForwardSettings || bForwardNone);`

#### struct `Metasound::DataFactoryPrivate::TDataTypeCreator`  
`template<typename DataType> struct TDataTypeCreator`  
_L204-211_
- desc: Create a DataType. For use in TDataFactory.
- L207 _public function_ `template<typename... ArgTypes> static DataType CreateNew(ArgTypes&&... Args)`

#### struct `Metasound::DataFactoryPrivate::TDataFactoryInternal`  
`template<typename DataType, typename CreatorType> struct TDataFactoryInternal`  
_L228-328_
- desc: Core factory type for creating objects related to metasound data types. TDataFactoryInternal provides a unified interface for constructing objects using a FOperatorSettings and a parameter pack of arguments. The ArgForwardType uses SFINAE to choose whether to forward all arguments, a subset of arguments or no arguments to the underlying CreatorType. @tparam DataType - The registered metasound data type which defines the supported constructors. @tparam CreatorType - A class providing a static "CreateNew(...)" function which accepts the forwarded arguments and returns an object.
- L244 _public function_ `static auto CreateNew(const FOperatorSettings& InSettings, ArgTypes&&... Args)`

#### struct `Metasound::DataFactoryPrivate::TDataVariantFactoryInternal`  
`template<typename DataType, typename CreatorType> struct TDataVariantFactoryInternal`  
_L343-576_
- desc: Core factory type for creating objects related to Metasound DataTypes. TDataVariantFactoryInternal provides a unified interface for constructing objects using a FOperatorSettings and TVariant arguments. The VariantParseType uses SFINAE to choose how to interpret the TVariant argument. @tparam DataType - The registered metasound data type which defines the supported constructors. @tparam CreatorType - A class providing a static "CreateNewFromVariant(...)" function which accepts the forwarded arguments and returns an object.
- L345 _public typedef_ `using FInternalFactory = TDataFactoryInternal<DataType, CreatorType>;`
- L362 _public function_ `static auto CreateNewFromVariant(const FOperatorSettings& InSettings, const VariantType& InVariant)`

#### struct `Metasound::DataFactoryPrivate::TTypePromoter`  
`template<bool ValidType, typename ThisType, typename PreviousType = void> struct TTypePromoter`  
_L580-584_
- desc: Promote which type to use for fallback
- L582 _public typedef_ `typedef PreviousType Type;`
- L583 _public member_ `static constexpr bool bIsValidType = ValidType;`
- L591 _public member_ `static constexpr bool bIsValidType = true;`
- L599 _public member_ `static constexpr bool bIsValidType = !std::is_same<PreviousType, void>::value;`
- L606 _public typedef_ `typedef ThisType Type;`

#### struct `Metasound::DataFactoryPrivate::TTypePromoter`  
`template<typename ThisType, typename PreviousType> struct TTypePromoter<true, ThisType, PreviousType>`  
_L588-592_
- desc: TTypePromoter partial specialization for ValidType=true
- L582 _public typedef_ `typedef PreviousType Type;`
- L583 _public member_ `static constexpr bool bIsValidType = ValidType;`
- L591 _public member_ `static constexpr bool bIsValidType = true;`
- L599 _public member_ `static constexpr bool bIsValidType = !std::is_same<PreviousType, void>::value;`
- L606 _public typedef_ `typedef ThisType Type;`

#### struct `Metasound::DataFactoryPrivate::TTypePromoter`  
`template<typename ThisType, typename PreviousType> struct TTypePromoter<false, ThisType, PreviousType>`  
_L596-600_
- desc: TTypePromoter partial specialization for ValidType=false
- L582 _public typedef_ `typedef PreviousType Type;`
- L583 _public member_ `static constexpr bool bIsValidType = ValidType;`
- L591 _public member_ `static constexpr bool bIsValidType = true;`
- L599 _public member_ `static constexpr bool bIsValidType = !std::is_same<PreviousType, void>::value;`
- L606 _public typedef_ `typedef ThisType Type;`

#### struct `Metasound::DataFactoryPrivate::TTypePromoter`  
`template<typename ThisType> struct TTypePromoter<true, ThisType>`  
_L604-608_
- desc: TTypePromoter partial specialization for ValidType=true and no PreviousType.
- L582 _public typedef_ `typedef PreviousType Type;`
- L583 _public member_ `static constexpr bool bIsValidType = ValidType;`
- L591 _public member_ `static constexpr bool bIsValidType = true;`
- L599 _public member_ `static constexpr bool bIsValidType = !std::is_same<PreviousType, void>::value;`
- L606 _public typedef_ `typedef ThisType Type;`

#### struct `Metasound::DataFactoryPrivate::TDataTypeVariantFallbackHelper`  
`template<typename DataType, typename ThisArgType, typename... VariantArgTypes> struct TDataTypeVariantFallbackHelper`  
_L614-639_
- desc: Helper for determine whether constructor accepts the variant type. Supports unrolling the parameter pack via recursive template.
- L618 _private member_ `static constexpr bool bIsConstructibleWithThisArg = std::is_constructible<DataType, ThisArgType>::value;`
- L619 _private member_ `static constexpr bool bIsConstructibleWithSettingsAndThisArg = std::is_constructible<DataType, const FOperatorSettings&, ThisArgType>::value;`
- L621 _private member_ `static constexpr bool bPromotThisArgType = bIsConstructibleWithThisArg || bIsConstructibleWithSettingsAndThisArg;`
- L622 _private typedef_ `using FVariantPromoter = TTypePromoter<bPromotThisArgType, ThisArgType, typename TDataTypeVariantFallbackHelper<DataType, VariantArgTypes...>::FallbackType>;`
- L628 _public member_ `static constexpr bool bIsConstructibleWithArgs = bIsConstructibleWithThisArg || TDataTypeVariantFallbackHelper<DataType, VariantArgTypes...>::bIsConstructibleWithArgs;` — True if the DataType is default constructible or constructible with any of the variant types.
- L632 _public member_ `static constexpr bool bIsConstructibleWithSettingsAndArgs = bIsConstructibleWithSettingsAndThisArg || TDataTypeVariantFallbackHelper<DataType, VariantArgTypes...>::bIsConstructibleWithSettingsAndArgs;` — True if the DataType is default constructible or constructible with any of the variant types.
- L635 _public typedef_ `typedef typename FVariantPromoter::Type FallbackType;` — Fallback type to use if there is no other way to construct the object.
- L638 _public member_ `static constexpr bool bIsConstructibleWithFallbackArg = FVariantPromoter::bIsValidType;` — True if the constructor accepts the fallback type.
- L651 _private typedef_ `using FVariantPromoter = TTypePromoter<bPromotThisArgType, ThisArgType>;`
- L656 _public member_ `static constexpr bool bIsConstructibleWithArgs = bIsConstructibleWithThisArg;` — True if the DataType is default constructible or constructible with any of the variant types.
- L660 _public member_ `static constexpr bool bIsConstructibleWithSettingsAndArgs = bIsConstructibleWithSettingsAndThisArg;` — True if the DataType is default constructible or constructible with any of the variant types.

#### struct `Metasound::DataFactoryPrivate::TDataTypeVariantFallbackHelper`  
`template<typename DataType, typename ThisArgType> struct TDataTypeVariantFallbackHelper<DataType, ThisArgType>`  
_L644-666_
- desc: Specialization of TDataTypeVariantFallbackHelper to handle end of recursion on VariantArgTypes.
- L618 _private member_ `static constexpr bool bIsConstructibleWithThisArg = std::is_constructible<DataType, ThisArgType>::value;`
- L619 _private member_ `static constexpr bool bIsConstructibleWithSettingsAndThisArg = std::is_constructible<DataType, const FOperatorSettings&, ThisArgType>::value;`
- L621 _private member_ `static constexpr bool bPromotThisArgType = bIsConstructibleWithThisArg || bIsConstructibleWithSettingsAndThisArg;`
- L622 _private typedef_ `using FVariantPromoter = TTypePromoter<bPromotThisArgType, ThisArgType, typename TDataTypeVariantFallbackHelper<DataType, VariantArgTypes...>::FallbackType>;`
- L628 _public member_ `static constexpr bool bIsConstructibleWithArgs = bIsConstructibleWithThisArg || TDataTypeVariantFallbackHelper<DataType, VariantArgTypes...>::bIsConstructibleWithArgs;` — True if the DataType is default constructible or constructible with any of the variant types.
- L632 _public member_ `static constexpr bool bIsConstructibleWithSettingsAndArgs = bIsConstructibleWithSettingsAndThisArg || TDataTypeVariantFallbackHelper<DataType, VariantArgTypes...>::bIsConstructibleWithSettingsAndArgs;` — True if the DataType is default constructible or constructible with any of the variant types.
- L635 _public typedef_ `typedef typename FVariantPromoter::Type FallbackType;` — Fallback type to use if there is no other way to construct the object.
- L638 _public member_ `static constexpr bool bIsConstructibleWithFallbackArg = FVariantPromoter::bIsValidType;` — True if the constructor accepts the fallback type.
- L651 _private typedef_ `using FVariantPromoter = TTypePromoter<bPromotThisArgType, ThisArgType>;`
- L656 _public member_ `static constexpr bool bIsConstructibleWithArgs = bIsConstructibleWithThisArg;` — True if the DataType is default constructible or constructible with any of the variant types.
- L660 _public member_ `static constexpr bool bIsConstructibleWithSettingsAndArgs = bIsConstructibleWithSettingsAndThisArg;` — True if the DataType is default constructible or constructible with any of the variant types.

#### struct `Metasound::DataFactoryPrivate::TElementType`  
`template<typename ContainterType> struct TElementType`  
_L670-673_
- desc: TElementType determines the element type of a container.
- L672 _public typedef_ `using Type = void;`
- L679 _public typedef_ `using Type = ElementType;`

#### struct `Metasound::DataFactoryPrivate::TElementType`  
`template<typename ElementType> struct TElementType<TArray<ElementType>>`  
_L677-680_
- desc: TElementType specialization for TArray
- L672 _public typedef_ `using Type = void;`
- L679 _public typedef_ `using Type = ElementType;`

#### struct `Metasound::DataFactoryPrivate::TDataTypeVariantParsing`  
`template<typename DataType, typename DesiredArgType, typename FirstVariantType, typename... AdditionalVariantTypes> struct TDataTypeVariantParsing`  
_L686-720_
- desc: TDataTypeVariantParsing informs the TDataVariantFactoryInternal on which factory method to instantiate.
- L689 _private typedef_ `using FDesiredConstructorTraits = TDataTypeConstructorTraits<DataType, DesiredArgType>;`
- L690 _private typedef_ `using FFallbackHelper = TDataTypeVariantFallbackHelper<DataType, FirstVariantType, AdditionalVariantTypes...>;`
- L693 _private member_ `static constexpr bool bCanCreateArrayElementsWithArg = FDesiredConstructorTraits::bIsArrayConstructibleWithArgs || FDesiredConstructorTraits::bIsArrayConstructibleWithSettingsAndArgs;` — Determine which elementwise construction methods are supported
- L694 _private member_ `static constexpr bool bCanCreateArrayElementsWithSettings = FDesiredConstructorTraits::bIsArrayConstructibleWithSettings;`
- L695 _private member_ `static constexpr bool bCanCreateArrayElementsWithDefaultConstructor = FDesiredConstructorTraits::bIsArrayDefaultConstructible;`
- L698 _private member_ `static constexpr bool bCanCreateWithArg = FDesiredConstructorTraits::bIsConstructibleWithArgs || FDesiredConstructorTraits::bIsConstructibleWithSettingsAndArgs;` — Determine which construction methods are supported
- L699 _private member_ `static constexpr bool bCanCreateWithoutArg = FDesiredConstructorTraits::bIsConstructibleWithSettings || FDesiredConstructorTraits::bIsDefaultConstructible;`
- L700 _private member_ `static constexpr bool bCanCreateWithFallbackArg = FFallbackHelper::bIsConstructibleWithFallbackArg;`
- L704 _public member_ `static constexpr bool bCannotForwardToConstructor = !(bCanCreateWithArg || bCanCreateWithoutArg || bCanCreateWithFallbackArg || bCanCreateArrayElementsWithArg || bCanCreateArrayElementsWithDefaultConstructor);`
- L707 _public member_ `static constexpr bool bCreateArrayElementsWithArg = bCanCreateArrayElementsWithArg;` — Determine which construction method to use.
- L708 _public member_ `static constexpr bool bCreateArrayElementsWithSettings = !(bCanCreateArrayElementsWithArg) && bCanCreateArrayElementsWithSettings;`
- L709 _public member_ `static constexpr bool bCreateArrayElementsWithDefaultConstructor = !(bCanCreateArrayElementsWithArg || bCreateArrayElementsWithSettings) && bCanCreateArrayElementsWithDefaultConstructor;`
- L711 _public member_ `static constexpr bool bCreateWithArg = !(bCreateArrayElementsWithArg || bCreateArrayElementsWithSettings || bCreateArrayElementsWithDefaultConstructor) && bCanCreateWithArg;`
- L712 _public member_ `static constexpr bool bCreateWithoutArg = !(bCreateArrayElementsWithArg || bCreateArrayElementsWithSettings || bCreateArrayElementsWithDefaultConstructor || bCreateWithArg) && bCanCreateWithoutArg;`
- L713 _public member_ `static constexpr bool bCreateWithFallbackArg = !(bCreateArrayElementsWithArg || bCreateArrayElementsWithSettings || bCreateArrayElementsWithDefaultConstructor || bCreateWithArg || bCreateWithoutArg) && bCanCreateWithFallbackArg;`
- L716 _public typedef_ `using ElementType = typename TElementType<DataType>::Type;` — Determine types
- L717 _public typedef_ `using ArgElementType = typename TElementType<DesiredArgType>::Type;`
- L718 _public typedef_ `using ArgType = DesiredArgType;`
- L719 _public typedef_ `using FallbackArgType = typename FFallbackHelper::FallbackType;`

#### struct `Metasound::TIsParsable`  
`template<typename DataType, typename... ArgTypes> struct TIsParsable`  
_L730-738_
- desc: Determines whether a DataType supports a constructor which accepts and FOperatorSettings with ArgTypes and/or just ArgTypes. @tparam DataType - The registered Metasound Data Type. @tparam ArgTypes - A parameter pack of arguments to be passed to the data type's constructor.
- L732 _public typedef_ `using FConstructorTraits = DataFactoryPrivate::TDataTypeConstructorTraits<DataType, ArgTypes...>;`
- L737 _public member_ `static constexpr bool Value = FConstructorTraits::bIsConstructibleWithArgs || FConstructorTraits::bIsConstructibleWithSettingsAndArgs || FConstructorTraits::bIsArrayConstructibleWithArgs || FConstructorTraits::bIsArrayConstructibleWithSettingsAndArgs;` — True if the DataType supports a constructor which accepts and FOperatorSettings with ArgTypes and/or just ArgTypes. False otherwise.
- L744 _public typedef_ `using FConstructorTraits = DataFactoryPrivate::TDataTypeConstructorTraits<DataType>;`
- L754 _public typedef_ `using FElementConstructorTraits = DataFactoryPrivate::TDataTypeConstructorTraits<DataElementType>;`
- L757 _public member_ `static constexpr bool Value = FElementConstructorTraits::bIsConstructibleWithArgs || FElementConstructorTraits::bIsConstructibleWithSettingsAndArgs ;` — True if the DataElementType supports a default constructor or constructor which accepts and FOperatorSettings.

#### struct `Metasound::TIsParsable`  
`template<typename DataType> struct TIsParsable<DataType, FLiteral::FNone>`  
_L742-748_
- desc: Specialization for FLiteral::FNone arg type.
- L732 _public typedef_ `using FConstructorTraits = DataFactoryPrivate::TDataTypeConstructorTraits<DataType, ArgTypes...>;`
- L737 _public member_ `static constexpr bool Value = FConstructorTraits::bIsConstructibleWithArgs || FConstructorTraits::bIsConstructibleWithSettingsAndArgs || FConstructorTraits::bIsArrayConstructibleWithArgs || FConstructorTraits::bIsArrayConstructibleWithSettingsAndArgs;` — True if the DataType supports a constructor which accepts and FOperatorSettings with ArgTypes and/or just ArgTypes. False otherwise.
- L744 _public typedef_ `using FConstructorTraits = DataFactoryPrivate::TDataTypeConstructorTraits<DataType>;`
- L754 _public typedef_ `using FElementConstructorTraits = DataFactoryPrivate::TDataTypeConstructorTraits<DataElementType>;`
- L757 _public member_ `static constexpr bool Value = FElementConstructorTraits::bIsConstructibleWithArgs || FElementConstructorTraits::bIsConstructibleWithSettingsAndArgs ;` — True if the DataElementType supports a default constructor or constructor which accepts and FOperatorSettings.

#### struct `Metasound::TIsParsable`  
`template<typename DataElementType> struct TIsParsable<TArray<DataElementType>, TArray<FLiteral::FNone>>`  
_L752-758_
- desc: Specialization for TArray data type and TArray<FLiteral::FNone> arg type.
- L732 _public typedef_ `using FConstructorTraits = DataFactoryPrivate::TDataTypeConstructorTraits<DataType, ArgTypes...>;`
- L737 _public member_ `static constexpr bool Value = FConstructorTraits::bIsConstructibleWithArgs || FConstructorTraits::bIsConstructibleWithSettingsAndArgs || FConstructorTraits::bIsArrayConstructibleWithArgs || FConstructorTraits::bIsArrayConstructibleWithSettingsAndArgs;` — True if the DataType supports a constructor which accepts and FOperatorSettings with ArgTypes and/or just ArgTypes. False otherwise.
- L744 _public typedef_ `using FConstructorTraits = DataFactoryPrivate::TDataTypeConstructorTraits<DataType>;`
- L754 _public typedef_ `using FElementConstructorTraits = DataFactoryPrivate::TDataTypeConstructorTraits<DataElementType>;`
- L757 _public member_ `static constexpr bool Value = FElementConstructorTraits::bIsConstructibleWithArgs || FElementConstructorTraits::bIsConstructibleWithSettingsAndArgs ;` — True if the DataElementType supports a default constructor or constructor which accepts and FOperatorSettings.

#### struct `Metasound::TIsArrayType`  
`template<typename DataType> struct TIsArrayType`  
_L762-765_
- desc: Determines whether a DataType is an array type.
- L764 _public member_ `static constexpr bool Value = false;`
- L771 _public member_ `static constexpr bool Value = true;`

#### struct `Metasound::TIsArrayType`  
`template<typename DataElementType> struct TIsArrayType<TArray<DataElementType>>`  
_L769-772_
- desc: Specialization for Array DataTypes.
- L764 _public member_ `static constexpr bool Value = false;`
- L771 _public member_ `static constexpr bool Value = true;`

#### struct `Metasound::TLiteralTraits`  
`template<typename DataType> struct TLiteralTraits`  
_L779-869_
- desc: Determines whether a DataType supports construction using the given literal. @tparam DataType - The registered Metasound Data Type.
- L781 _public typedef_ `using TVariantConstructorTraits = DataFactoryPrivate::TDataTypeVariantConstructorTraits<DataType, FLiteral::FVariantType>;`
- L783 _public member_ `static constexpr bool bIsParseableFromAnyArrayLiteralType = TVariantConstructorTraits::bIsArrayDefaultConstructible || TVariantConstructorTraits::bIsArrayConstructibleWithSettings || TVariantConstructorTraits::bIsArrayConstructibleWithArgs || TVariantConstructorTraits::bIsArrayConstructibleWithSettingsAndArgs;`
- L789 _public member_ `static constexpr bool bIsParsableFromAnyLiteralType = TVariantConstructorTraits::bIsDefaultConstructible || TVariantConstructorTraits::bIsConstructibleWithSettings || TVariantConstructorTraits::bIsConstructibleWithArgs || TVariantConstructorTraits::bIsConstructibleWithSettingsAndArgs || bIsParseableFromAnyArrayLiteralType;`
- L806 _public function_ `static const bool IsParsable(const FLiteral& InLiteral)` — Determines if a constructor for the DataType exists which accepts an FOperatorSettings with the literals constructor arg type, and/or one that accepts the literal constructor arg type. @param InLiteral - The literal containing the constructor argument. @return True if a constructor for the DataType exists which accepts an FOperatorSettings with the literals constructor arg type, or one that accepts the literal constructor arg type. It returns False otherwise.

#### struct `Metasound::TDataFactory`  
`template<typename DataType, typename CreatorType> struct TDataFactory`  
_L883-945_
- desc: A base factory type for creating objects related to Metasound DataTypes. TDataFactory provides a unified interface for constructing objects using a FOperatorSettings and a parameter pack of arguments. The various factory methods determine how strictly the DataType constructors must match the arguments to the factory method. @tparam DataType - The registered metasound data type which defines the supported constructors. @tparam CreatorType - A class providing a static "CreateNew(...)" function which accepts the forwarded arguments and returns an object.
- L885 _public typedef_ `using FInternalFactory = DataFactoryPrivate::TDataFactoryInternal<DataType, CreatorType>;`
- L889 _public function_ `template<typename... ArgTypes> static auto CreateAny(const FOperatorSettings& InSettings, ArgTypes&&... Args)` — Create the object using any supported constructor.
- L911 _public function_ `template<typename... ArgTypes> static auto CreateExplicit(const FOperatorSettings& InSettings, ArgTypes&&... Args)` — Create the object using only a constructor which exactly matches the arguments to this factory method.
- L930 _public function_ `template<typename... ArgTypes> static auto CreateExplicitArgs(const FOperatorSettings& InSettings, ArgTypes&&... Args)` — Create the object using only constructors which utilize all arguments in the parameter pack (ArgTypes...).

#### struct `Metasound::TDataTypeFactory`  
`template<typename DataType> struct TDataTypeFactory : TDataFactory<DataType, DataFactoryPrivate::TDataTypeCreator<DataType>>`  
_L957-959_
- inherits: `TDataFactory<DataType,DataFactoryPrivate::TDataTypeCreator<DataType>>`
- desc: TDataTypeFactory creates a DataType. TDataTypeFactory provides several factory methods for forwarding arguments from the factory method to the DataType constructor.  See TDataFactory for more information on the provided factory methods. @tparam DataType - The Metasound DataType.

#### struct `Metasound::TDataValueReferenceFactory`  
`template<typename DataType> struct TDataValueReferenceFactory : TDataFactory<DataType, TDataValueReference<DataType>>`  
_L970-972_
- inherits: `TDataFactory<DataType,TDataValueReference<DataType>>`
- desc: TDataValueReferenceFactory creates TDataValueReferences for the given DataType. TDataValueReferenceFactory provides several factory methods for forwarding arguments from the factory method to the DataType constructor.  See TDataFactory for more information on the provided factory methods. @tparam DataType - The Metasound DataType of the TDataValueReference.

#### struct `Metasound::TDataReadReferenceFactory`  
`template<typename DataType> struct TDataReadReferenceFactory : TDataFactory<DataType, TDataReadReference<DataType>>`  
_L983-985_
- inherits: `TDataFactory<DataType,TDataReadReference<DataType>>`
- desc: TDataReadReferenceFactory creates TDataReadReferences for the given DataType. TDataReadReferenceFactory provides several factory methods for forwarding arguments from the factory method to the DataType constructor.  See TDataFactory for more information on the provided factory methods. @tparam DataType - The Metasound DataType of the TDataReadReference.

#### struct `Metasound::TDataWriteReferenceFactory`  
`template<typename DataType> struct TDataWriteReferenceFactory : TDataFactory<DataType, TDataWriteReference<DataType>>`  
_L996-998_
- inherits: `TDataFactory<DataType,TDataWriteReference<DataType>>`
- desc: TDataWriteReferenceFactory creates TDataWriteReferences for the given DataType. TDataWriteReferenceFactory provides several factory methods for forwarding arguments from the factory method to the DataType constructor.  See TDataFactory for more information on the provided factory methods. @tparam DataType - The Metasound DataType of the TDataWriteReference.

#### struct `Metasound::TDataLiteralFactory`  
`template<typename DataType, typename CreatorType> struct TDataLiteralFactory`  
_L1013-1161_
- desc: A base factory type for creating objects related to Metasound DataTypes. TDataLiteralFactory provides a unified interface for constructing objects using a FOperatorSettings and FLiteral. The various factory methods determine how strictly the DataType constructors must match the arguments to the factory method. @tparam DataType - The registered metasound data type which defines the supported constructors. @tparam CreatorType - A class providing a static "CreateNew(...)" function which accepts the forwarded arguments and returns an object.
- L1015 _public typedef_ `using FInternalFactory = DataFactoryPrivate::TDataVariantFactoryInternal<DataType, CreatorType>;`
- L1019 _public function_ `template<typename FirstVariantType, typename... AdditionalVariantTypes> static auto CreateAny(const FOperatorSettings& InSettings, const TVariant<FirstVariantType, AdditionalVariantTypes...>& InVariant)` — Create the object using any supported constructor.
- L1028 _public function_ `template<typename DesiredArgType, typename FirstVariantType, typename... AdditionalVariantTypes> static auto CreateExplicitArgs(const FOperatorSettings& InSettings, const TVariant<FirstVariantType, AdditionalVariantTypes...>& InVariant)` — Create the object using only constructors which utilize the InVariant.
- L1044 _public function_ `static auto CreateExplicitArgs(const FOperatorSettings& InSettings, const FLiteral& InLiteral)` — Create the object using only constructors which utilize the InLiteral. @param InSettings - The FOperatorSettings to be passed to the DataType constructor if an appropriate constructor exists. @param InLiteral - The literal to be passed to the constructor. @return An object related to the DataType. The exact type determined by the CreatorType class template parameter.

#### struct `Metasound::TDataTypeLiteralFactory`  
`template<typename DataType> struct TDataTypeLiteralFactory : TDataLiteralFactory<DataType, DataFactoryPrivate::TDataTypeCreator<DataType>>`  
_L1172-1174_
- inherits: `TDataLiteralFactory<DataType,DataFactoryPrivate::TDataTypeCreator<DataType>>`
- desc: TDataTypeLiteralFactory creates a DataType. TDataTypeLiteralFactory provides several factory methods for forwarding arguments from the factory method to the DataType constructor.  See TDataFactory for more information on the provided factory methods. @tparam DataType - The Metasound DataType.

#### struct `Metasound::TDataValueReferenceLiteralFactory`  
`template<typename DataType> struct TDataValueReferenceLiteralFactory : TDataLiteralFactory<DataType, TDataValueReference<DataType>>`  
_L1185-1187_
- inherits: `TDataLiteralFactory<DataType,TDataValueReference<DataType>>`
- desc: TDataValueReferenceLiteralFactory creates TDataValueReferences for the given DataType. TDataValueReferenceLiteralFactory provides several factory methods for forwarding arguments from the factory method to the DataType constructor.  See TDataFactory for more information on the provided factory methods. @tparam DataType - The Metasound DataType of the TDataValueReference.

#### struct `Metasound::TDataReadReferenceLiteralFactory`  
`template<typename DataType> struct TDataReadReferenceLiteralFactory : TDataLiteralFactory<DataType, TDataReadReference<DataType>>`  
_L1198-1200_
- inherits: `TDataLiteralFactory<DataType,TDataReadReference<DataType>>`
- desc: TDataReadReferenceLiteralFactory creates TDataReadReferences for the given DataType. TDataReadReferenceLiteralFactory provides several factory methods for forwarding arguments from the factory method to the DataType constructor.  See TDataFactory for more information on the provided factory methods. @tparam DataType - The Metasound DataType of the TDataReadReference.

#### struct `Metasound::TDataWriteReferenceLiteralFactory`  
`template<typename DataType> struct TDataWriteReferenceLiteralFactory : TDataLiteralFactory<DataType, TDataWriteReference<DataType>>`  
_L1211-1213_
- inherits: `TDataLiteralFactory<DataType,TDataWriteReference<DataType>>`
- desc: TDataWriteReferenceLiteralFactory creates TDataWriteReferences for the given DataType. TDataWriteReferenceLiteralFactory provides several factory methods for forwarding arguments from the factory method to the DataType constructor.  See TDataFactory for more information on the provided factory methods. @tparam DataType - The Metasound DataType of the TDataWriteReference.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Metasound`
- L13 _namespace_ `namespace DataFactoryPrivate` (scope `Metasound`)
- L16 _typedef_ `using ProxyDataPtrType_DEPRECATED = TUniquePtr<Audio::IProxyData>;` (scope `Metasound::DataFactoryPrivate`) — Deprecated in 5.2. Use TSharedPtr<Audio::IProxyData> instead of TUniquePtr<Audio::IProxyData>.
- L365 _typedef_ `using TExplicitArgsConstructorForwarding = TExplicitArgsConstructorForwarding<DataType, typename VariantParseType::ArgType>;` (scope `Metasound::DataFactoryPrivate::TDataVariantFactoryInternal::CreateNewFromVariant`) — The constructor must use the desired variant argument.
- L387 _typedef_ `using TExplicitArgsConstructorForwarding = TExplicitArgsConstructorForwarding<DataType>;` (scope `Metasound::DataFactoryPrivate::TDataVariantFactoryInternal::CreateNewFromVariant`) — The constructor must be the default constructor or accept a FOperatorSettings.
- L418 _typedef_ `using FConstructorForwarding = TExplicitArgsConstructorForwarding<DataType>;` (scope `Metasound::DataFactoryPrivate::TDataVariantFactoryInternal::CreateNewFromVariant`)
- L420 _typedef_ `using FArgType = typename VariantParseType::ArgType;` (scope `Metasound::DataFactoryPrivate::TDataVariantFactoryInternal::CreateNewFromVariant`)
- L421 _typedef_ `using FArgElementType = typename VariantParseType::ArgElementType;` (scope `Metasound::DataFactoryPrivate::TDataVariantFactoryInternal::CreateNewFromVariant`)
- L422 _typedef_ `using FElementType = typename VariantParseType::ElementType;` (scope `Metasound::DataFactoryPrivate::TDataVariantFactoryInternal::CreateNewFromVariant`)
- L423 _typedef_ `using FElementConstructorForwarding = TExplicitArgsConstructorForwarding<FElementType, FArgElementType>;` (scope `Metasound::DataFactoryPrivate::TDataVariantFactoryInternal::CreateNewFromVariant`)
- L425 _typedef_ `using FElementFactory = TDataFactoryInternal<FElementType, DataFactoryPrivate::TDataTypeCreator<FElementType>>;` (scope `Metasound::DataFactoryPrivate::TDataVariantFactoryInternal::CreateNewFromVariant`)
- L462 _typedef_ `using FElementConstructorForwarding = TExplicitArgsConstructorForwarding<FElementType>;` (scope `Metasound::DataFactoryPrivate::TDataVariantFactoryInternal::CreateNewFromVariant`)
- L542 _typedef_ `using TExplicitArgsConstructorForwarding = TExplicitArgsConstructorForwarding<DataType, typename VariantParseType::FallbackArgType>;` (scope `Metasound::DataFactoryPrivate::TDataVariantFactoryInternal::CreateNewFromVariant`) — The constructor must use the fallback variant argument.
- L891 _typedef_ `using TForwarding = DataFactoryPrivate::TAnyConstructorForwarding<DataType, ArgTypes...>;` (scope `Metasound::TDataFactory::CreateAny`)
- L913 _typedef_ `using TForwarding = DataFactoryPrivate::TExplicitConstructorForwarding<DataType, ArgTypes...>;` (scope `Metasound::TDataFactory::CreateExplicit`)
- L932 _typedef_ `using TForwarding = DataFactoryPrivate::TExplicitArgsConstructorForwarding<DataType, ArgTypes...>;` (scope `Metasound::TDataFactory::CreateExplicitArgs`)
- L1021 _typedef_ `using FDataVariantParsing = DataFactoryPrivate::TDataTypeVariantParsing<DataType, void, FirstVariantType, AdditionalVariantTypes...>;` (scope `Metasound::TDataLiteralFactory::CreateAny`)
- L1030 _typedef_ `using FDataVariantParsing = DataFactoryPrivate::TDataTypeVariantParsing<DataType, DesiredArgType, FirstVariantType, AdditionalVariantTypes...>;` (scope `Metasound::TDataLiteralFactory::CreateExplicitArgs`)
- L1075 _typedef_ `using FFactoryForDeprecatedPtr = TDataFactory<DataType, CreatorType>;` (scope `Metasound::TDataLiteralFactory::CreateExplicitArgs`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundDataReference.h` (Public)


#### class `Metasound::IDataReference`  
`class IDataReference`  
_L54-72_
- desc: A Data Reference Interface. A parameter references provides information and access to a shared object in the graph.
- L57 _public member_ `static const FName RouterName;`
- L59 _public prototype_ `virtual ~IDataReference() = default;`
- L62 _public prototype_ `virtual const FName& GetDataTypeName() const = 0;` — Returns the name of the data type.
- L65 _public prototype_ `virtual const void* const GetDataTypeId() const = 0;` — Returns the ID of the parameter type.
- L68 _public prototype_ `virtual TUniquePtr<IDataReference> Clone() const = 0;` — Creates a copy of the parameter type.
- L71 _public prototype_ `virtual void* GetRaw() const = 0;` — provides a raw pointer to the storage where the data actually resides.

#### enum `Metasound::EDataRefShouldConstruct`  
`enum class EDataRefShouldConstruct`  
_L138-141_
- desc: This enum is used as a token to explicitly delineate when we should create a new object for the reference, or use a different constructor.
- L140 _public enumerator_ `NewObject`

#### struct `Metasound::TDynamicDataReferencePolicy`  
`template<typename DataType> requires (!TPolymorphicTraits<DataType>::bIsPolymorphic) struct TDynamicDataReferencePolicy<DataType>`  
_L172-177_
- L174 _public function_ `template<typename QueryType> bool IsA(const DataType*) const`
- L175 _public function_ `template<typename QueryType> bool IsA(const DataType*) const`
- L176 _public function_ `const void* GetDataTypeId(const DataType*) const`
- L185 _public function_ `template<typename QueryType> bool IsA(const DataType* InOuter) const`
- L190 _public function_ `const FName& GetDataTypeName(const DataType* InOuter) const`
- L195 _public function_ `const void* GetDataTypeId(const DataType* InOuter) const`

#### struct `Metasound::TDynamicDataReferencePolicy`  
`template<typename DataType> requires (TPolymorphicTraits<DataType>::bIsPolymorphic) struct TDynamicDataReferencePolicy<DataType>`  
_L181-199_
- L174 _public function_ `template<typename QueryType> bool IsA(const DataType*) const`
- L175 _public function_ `template<typename QueryType> bool IsA(const DataType*) const`
- L176 _public function_ `const void* GetDataTypeId(const DataType*) const`
- L185 _public function_ `template<typename QueryType> bool IsA(const DataType* InOuter) const`
- L190 _public function_ `const FName& GetDataTypeName(const DataType* InOuter) const`
- L195 _public function_ `const void* GetDataTypeId(const DataType* InOuter) const`

#### class `Metasound::TDataReference`  
`template <typename DataType> class TDataReference : public IDataReference`  
_L207-351_
- inherits: `IDataReference`
- desc: Template class for a paramter reference. This fulfills the IParamterRef interface, utilizing TDataReferenceTypeInfo to define the the TypeName and TypeId of the parameter.
- L215 _protected function_ `template <typename... ArgTypes> TDataReference(EDataRefShouldConstruct InToken, ArgTypes&&... Args) : ObjectReference(MakeShared<DataType, ESPMode::NotThreadSafe>(Forward<ArgTypes>(Args)...))` — This constructor forwards arguments to an underlying constructor.
- L221 _protected function_ `template <typename... ArgTypes> TDataReference(EDataRefShouldConstruct InToken, ArgTypes&&... Args) requires(CIsPolymorphicAndAbstract<DataType>) : ObjectReference(DataType::CreateNew(Forward<ArgTypes>(Args)...))`
- L227 _protected typedef_ `typedef TSharedRef<DataType, ESPMode::NotThreadSafe> FRefType;`
- L229 _protected function_ `explicit TDataReference(EDataRefShouldConstruct , FRefType InRef) : ObjectReference(MoveTemp(InRef))`
- L233 _protected function_ `explicit TDataReference(EDataRefShouldConstruct, FRefType InRef, const FName InTypeName, const void* InTypeId) : ObjectReference(MoveTemp(InRef))`
- L242 _public typedef_ `typedef TDataReferenceTypeInfo<DataType> FInfoType;`
- L247 _public function_ `template <typename... ArgTypes> static TDataReference<DataType> CreateNew(ArgTypes&&... Args)` — This should be used to construct a new DataType object and return this TDataReference as a wrapper around it.
- L257 _public function_ `template <typename... ArgTypes> static TDataReference<DataType> CreateNew(ArgTypes&&... Args) requires (CIsPolymorphicAndAbstract<DataType>)` — Polymorphic form of CreateNew.
- L266 _public function_ `static TDataReference CreateNewDerived(ArgTypes&&... Args)`
- L277 _public function_ `static TDataReference CreateNewDerivedAs(const FName& InDerivedTypeName, FMetasoundDataTypeId InDerivedTypeId, ArgTypes&&... Args)`
- L298 _public prototype_ `TDataReference(const TDataReference<DataType>& Other) = default;` — Enable copy constructor
- L301 _public prototype_ `TDataReference(TDataReference<DataType>&& Other) = default;` — Enable move constructor
- L304 _public prototype_ `TDataReference<DataType>& operator=(const TDataReference<DataType>& Other) = default;` — Enable copy operator
- L307 _public prototype_ `TDataReference<DataType>& operator=(TDataReference<DataType>&& Other) = default;` — Enable move operator
- L310 _public function_ `virtual const FName& GetDataTypeName() const override` — Return the name of the underlying type.
- L316 _public function_ `virtual const void* const GetDataTypeId() const override` — Return the ID of the underlying type.
- L322 _public function_ `virtual void* GetRaw() const override` — Return a raw pointer to the data.
- L329 _public function_ `bool IsA() const`
- L336 _public function_ `TOptional<TSharedRef<CastType, ESPMode::NotThreadSafe>> TryCast() const`
- L349 _protected member_ `FRefType ObjectReference;` — Protected object reference is utilized by subclasses which define what access is provided to the ObjectReference.
- L350 _protected member_ `TDynamicDataReferencePolicy<DataType> ObjectReferencePolicy;`

#### class `Metasound::TDataValueReference`  
`template<typename DataType> class TDataValueReference : public TDataReference<DataType>`  
_L364-482_
- inherits: `TDataReference<DataType>`
- desc: TDataValueReference represents a constant value and provides read only access. A TDataValueReference can never change value.
- L368 _private function_ `template <typename... ArgTypes> TDataValueReference(EDataRefShouldConstruct InToken, ArgTypes&&... Args) : TDataReference<DataType>(InToken, Forward<ArgTypes>(Args)...)` — Construct operator with no arguments if the DataType has a default constructor.
- L374 _private function_ `TDataValueReference(const TDataReference<DataType>& InRef) : TDataReference<DataType>(InRef)` — Constructor taking data reference. Used for casting
- L385 _private typedef_ `using FRefType = TDataReference<DataType>::FRefType;`
- L386 _private function_ `TDataValueReference(EDataRefShouldConstruct, FRefType InRef, FName InTypeName, const void* InTypeId) : TDataReference<DataType>(EDataRefShouldConstruct::NewObject, MoveTemp(InRef), InTypeName, InTypeId)`
- L395 _public function_ `template <typename... ArgTypes> static TDataValueReference<DataType> CreateNew(ArgTypes&&... Args)` — This should be used to construct a new DataType object and return this TDataValueReference as a wrapper around it.
- L402 _public function_ `template <typename... ArgTypes> static TDataValueReference<DataType> CreateNew(ArgTypes&&... Args) requires (CIsPolymorphicAndAbstract<DataType>)`
- L410 _public function_ `static TDataValueReference CreateNewDerived(ArgTypes&&... Args)`
- L421 _public function_ `static TDataValueReference CreateNewDerivedAs(const FName& InDerivedTypeName, FMetasoundDataTypeId InDerivedTypeId, ArgTypes&&... Args)`
- L441 _public prototype_ `TDataValueReference(const TDataValueReference<DataType>& Other) = default;` — Enable copy constructor
- L444 _public prototype_ `TDataValueReference(TDataValueReference<DataType>&& Other) = default;` — Enable move constructor
- L447 _public prototype_ `TDataValueReference<DataType>& operator=(const TDataValueReference<DataType>& Other) = default;` — Enable assignment operator.
- L450 _public prototype_ `TDataValueReference<DataType>& operator=(TDataValueReference<DataType>&& Other) = default;` — Enable move operator.
- L453 _public function_ `operator TDataReadReference<DataType>() const` — Implicit conversion to a readable parameter.
- L459 _public function_ `inline const DataType& operator*() const` — Const access to the underlying parameter object.
- L465 _public function_ `inline const DataType* operator->() const` — Const access to the underlying parameter object.
- L470 _public function_ `inline const DataType* Get() const`
- L476 _public function_ `virtual TUniquePtr<IDataReference> Clone() const override` — Create a clone of this parameter reference.

#### class `Metasound::TDataWriteReference`  
`template <typename DataType> class TDataWriteReference : public TDataReference<DataType>`  
_L512-634_
- inherits: `TDataReference<DataType>`
- desc: TDataWriteReference provides write access to a shared parameter reference.
- L516 _private function_ `template <typename... ArgTypes> TDataWriteReference(EDataRefShouldConstruct InToken, ArgTypes&&... Args) : TDataReference<DataType>(InToken, Forward<ArgTypes>(Args)...)` — Construct operator with no arguments if the DataType has a default constructor.
- L524 _private function_ `TDataWriteReference<DataType>(const TDataReference<DataType>& InDataReference) : TDataReference<DataType>(InDataReference)` — Create a writable ref from a blank parameter ref. Should be done with care and understanding of side-effects of converting a ref to a writable ref.
- L533 _private typedef_ `using FRefType = TDataReference<DataType>::FRefType;`
- L534 _private function_ `TDataWriteReference(EDataRefShouldConstruct, FRefType InRef, FName InTypeName, const void* InTypeId) : TDataReference<DataType>(EDataRefShouldConstruct::NewObject, MoveTemp(InRef), InTypeName, InTypeId)`
- L542 _public function_ `template <typename... ArgTypes> static TDataWriteReference<DataType> CreateNew(ArgTypes&&... Args)` — This should be used to construct a new DataType object and return this TDataWriteReference as a wrapper around it.
- L550 _public function_ `template <typename... ArgTypes> static TDataWriteReference<DataType> CreateNew(ArgTypes&&... Args) requires (CIsPolymorphicAndAbstract<DataType>)` — This should be used to construct a new DataType object and return this TDataWriteReference as a wrapper around it.
- L558 _public function_ `static TDataWriteReference CreateNewDerived(ArgTypes&&... Args)`
- L568 _public function_ `template <typename Derived, typename... ArgTypes> static TDataWriteReference CreateNewDerivedAs(const FName& InDerivedTypeName, FMetasoundDataTypeId InDerivedTypeId, ArgTypes&&... Args)`
- L588 _public prototype_ `TDataWriteReference(const TDataWriteReference<DataType>& Other) = default;` — Enable copy constructor
- L591 _public prototype_ `TDataWriteReference(TDataWriteReference<DataType>&& Other) = default;` — Enable move constructor
- L594 _public prototype_ `TDataWriteReference<DataType>& operator=(const TDataWriteReference<DataType>& Other) = default;` — Enable assignment operator.
- L597 _public prototype_ `TDataWriteReference<DataType>& operator=(TDataWriteReference<DataType>&& Other) = default;` — Enable move operator.
- L600 _public function_ `operator TDataReadReference<DataType>() const` — Implicit conversion to a readable parameter.
- L606 _public function_ `inline DataType& operator*() const` — Non-const access to the underlying parameter object.
- L612 _public function_ `inline DataType* operator->() const` — Non-const access to the underlying parameter object.
- L618 _public function_ `inline DataType* Get() const` — Non-const access to the underlying parameter object.
- L624 _public function_ `virtual TUniquePtr<IDataReference> Clone() const override` — Create a clone of this parameter reference.

#### class `Metasound::TDataReadReference`  
`template <typename DataType> class TDataReadReference : public TDataReference<DataType>`  
_L654-768_
- inherits: `TDataReference<DataType>`
- desc: TDataReadReference provides read access to a shared parameter reference.
- L658 _private function_ `template <typename... ArgTypes> TDataReadReference(EDataRefShouldConstruct InToken, ArgTypes&&... Args) : TDataReference<DataType>(InToken, Forward<ArgTypes>(Args)...)` — Construct operator with no arguments if the DataType has a default constructor.
- L663 _private typedef_ `using FRefType = typename TDataReference<DataType>::FRefType;`
- L664 _private function_ `TDataReadReference(EDataRefShouldConstruct, FRefType InRef, FName InTypeName, const void* InTypeId) : TDataReference<DataType>(EDataRefShouldConstruct::NewObject, MoveTemp(InRef), InTypeName, InTypeId)`
- L673 _public function_ `template <typename... ArgTypes> static TDataReadReference<DataType> CreateNew(ArgTypes&&... Args)` — This should be used to construct a new DataType object and return this TDataReadReference as a wrapper around it.
- L680 _public function_ `template <typename... ArgTypes> static TDataReadReference<DataType> CreateNew(ArgTypes&&... Args) requires (CIsPolymorphicAndAbstract<DataType>)`
- L688 _public function_ `static TDataReadReference CreateNewDerived(ArgTypes&&... Args)`
- L699 _public function_ `static TDataReadReference CreateNewDerivedAs(const FName& InDerivedTypeName, FMetasoundDataTypeId InDerivedTypeId, ArgTypes&&... Args)`
- L716 _public prototype_ `TDataReadReference(const TDataReadReference& Other) = default;`
- L719 _public function_ `explicit TDataReadReference(const TDataWriteReference<DataType>& WritableRef) : TDataReference<DataType>(WritableRef)` — Construct a readable parameter ref from a writable parameter ref.
- L725 _public function_ `explicit TDataReadReference(const TDataValueReference<DataType>& ValueRef) : TDataReference<DataType>(ValueRef)` — Construct a readable reference from a value reference.
- L731 _public function_ `TDataReadReference<DataType>& operator=(const TDataWriteReference<DataType>& Other)` — Assign a readable parameter ref from a writable parameter ref.
- L738 _public prototype_ `TDataReadReference<DataType>& operator=(const TDataReadReference<DataType>& Other) = default;` — Enable copy operator
- L741 _public prototype_ `TDataReadReference<DataType>& operator=(TDataReadReference<DataType>&& Other) = default;` — Enable move operator
- L744 _public function_ `inline const DataType& operator*() const` — Const access to the underlying parameter object.
- L750 _public function_ `inline const DataType* operator->() const` — Const access to the underlying parameter object.
- L756 _public function_ `inline const DataType* Get() const` — Non-const access to the underlying parameter object.
- L762 _public function_ `virtual TUniquePtr<IDataReference> Clone() const override` — Create a clone of this parameter reference.

#### enum `Metasound::EDataReferenceAccessType`  
`enum class EDataReferenceAccessType : uint8`  
_L776-782_
- desc: EDataReferenceAccessType describes the underlying data reference access type for a data reference contained in a FAnyDataReference. This value can be used to determine which methods are supported for accessing a data reference using GetDataReadReference<>() or GetDataWriteReference<>()
- L778 _public enumerator_ `None = 0x00` — The data is inaccessible, or the data reference does not exist.
- L779 _public enumerator_ `Read = 0x01` — The data is accessible through a TDataReadReference.
- L780 _public enumerator_ `Write = 0x02` — The data is accessible through a TDataWriteReference.
- L781 _public enumerator_ `Value = 0x04` — The data is accessible by value.

#### class `Metasound::FAnyDataReference`  
`class FAnyDataReference : public IDataReference`  
_L792-1104_
- inherits: `IDataReference`
- desc: Container for any data reference. This container maintains the underlying containers access type (Read or Write) and data type. This allows for convenient storage by implementing a virtual copy constructor and assignment operator.
- L916 _private function_ `FAnyDataReference(EDataReferenceAccessType InAccessType, const IDataReference& InDataRef) : AccessType(InAccessType) , DataRefPtr(InDataRef.Clone())` — Private constructor.
- L927 _public function_ `template<typename DataType> FAnyDataReference(const TDataReadReference<DataType>& InDataRef) : FAnyDataReference(EDataReferenceAccessType::Read, InDataRef)` — Construct with a TDataReadReference.
- L934 _public function_ `template<typename DataType> FAnyDataReference(const TDataWriteReference<DataType>& InDataRef) : FAnyDataReference(EDataReferenceAccessType::Write, InDataRef)` — Construct with a TDataWriteReference.
- L941 _public function_ `template<typename DataType> FAnyDataReference(const TDataValueReference<DataType>& InDataRef) : FAnyDataReference(EDataReferenceAccessType::Value, InDataRef)` — Construct with a TDataValueReference.
- L947 _public function_ `FAnyDataReference(const FAnyDataReference& InOther) : FAnyDataReference(InOther.AccessType, *InOther.DataRefPtr)` — Copy construct with a FAnyDataReference.
- L953 _public function_ `FAnyDataReference& operator=(const FAnyDataReference& InOther)` — Assignment.
- L965 _public function_ `EDataReferenceAccessType GetAccessType() const` — Returns the access type of the underlying data reference.
- L971 _public function_ `virtual const FName& GetDataTypeName() const override` — Returns the data type name of the underlying data reference.
- L978 _public function_ `virtual const void* const GetDataTypeId() const override` — Returns the data type ID of the underlying data reference.
- L985 _public function_ `virtual TUniquePtr<IDataReference> Clone() const override` — Returns a clone of the underlying data reference.
- L992 _public function_ `void* GetRaw() const` — Return a raw pointer to the data.
- L1003 _public function_ `template<typename ReturnType> ReturnType GetAs() const` — Return the data in the specified format. The template argument can be any of the support TData*Reference<> types, the underlying DataType or a const DataType* pointer.
- L1022 _public function_ `template<typename DataType> const DataType* GetValue() const` — Returns the current value of a reference. This method's behavior is undefined and an assert will be called if the DataType differs from the underlying data reference's DataType.
- L1039 _public function_ `template<typename DataType> DataType* GetWritableValue() const` — Return a non-const pointer to the data. If the vertex is bound with this will return a valid pointer. Otherwise it will return a nullptr.  This method will assert if the reference is bound, but not writable or if the data type does match.
- L1062 _public function_ `template<typename DataType> TDataValueReference<DataType> GetDataValueReference() const` — Get access to a TDataValueReference. This method will return a valid TDataValueReference of the templated data type. The returned object is only valid if: 1. The template parameter DataType matches that of the underlying data reference. 2. The underlying data reference is has Value access. If this method's behavior is undefined and will assert if it is called with a mismatched data type or unsupported access type.
- L1079 _public function_ `template<typename DataType> TDataReadReference<DataType> GetDataReadReference() const` — Get access to a TDataReadReference. This method will return a valid TDataReadReference of the templated data type. The returned object is only valid if: 1. The template parameter DataType matches that of the underlying data reference. 2. The underlying data reference is has Read, Write or Value access. If this method's behavior is undefined and will assert if it is called with a mismatched data type or unsupported access type.
- L1095 _public function_ `template<typename DataType> TDataWriteReference<DataType> GetDataWriteReference() const` — Get access to a TDataWriteReference. This method will return a valid TDataWriteReference of the templated data type. The returned object is only valid if: 1. The template paramter DataType matches that of the underlying data reference. 2. The underlying data reference is has Write access. If this method's behavior is undefined and will assert if it is called with a mismatched data type or unsupported access type.
- L1102 _private member_ `EDataReferenceAccessType AccessType = EDataReferenceAccessType::None;`
- L1103 _private member_ `TUniquePtr<IDataReference> DataRefPtr;`

#### struct `Metasound::FAnyDataReference::TGetAs`  
`template<typename ResultType> struct TGetAs`  
_L799-854_
- desc: TGetAs allows for template specialization of data retrieval and conversion rules for the various flavors of data referencing. The default implementation assumes we are attempting to retrieve the value stored in the data reference.
- L802 _private typedef_ `using DataType = typename std::decay_t<std::remove_pointer_t<ResultType>>;`
- L806 _private function_ `static ResultType DerefPointerIfNonPointerResultType(const DataType* InData)` — Only deref a pointer if the returned type is specifically requested to be a non-pointer.
- L823 _public function_ `static ResultType Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)` — Return a the underlying data by value or by const pointer depending upon the template parameter ResultType
- L860 _public function_ `static TDataReadReference<DataType> Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)`
- L892 _public function_ `static TDataValueReference<DataType> Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)`
- L904 _public function_ `static TDataWriteReference<DataType> Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)`

#### struct `Metasound::FAnyDataReference::TGetAs`  
`template<typename DataType> struct TGetAs<TDataReadReference<DataType>>`  
_L858-886_
- desc: Template specialization for retrieving data reference as a TDataReadReference<DataType>
- L802 _private typedef_ `using DataType = typename std::decay_t<std::remove_pointer_t<ResultType>>;`
- L806 _private function_ `static ResultType DerefPointerIfNonPointerResultType(const DataType* InData)` — Only deref a pointer if the returned type is specifically requested to be a non-pointer.
- L823 _public function_ `static ResultType Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)` — Return a the underlying data by value or by const pointer depending upon the template parameter ResultType
- L860 _public function_ `static TDataReadReference<DataType> Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)`
- L892 _public function_ `static TDataValueReference<DataType> Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)`
- L904 _public function_ `static TDataWriteReference<DataType> Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)`

#### struct `Metasound::FAnyDataReference::TGetAs`  
`template<typename DataType> struct TGetAs<TDataValueReference<DataType>>`  
_L890-898_
- desc: Template specialization for retrieving data reference as a TDataValueReference<DataType>
- L802 _private typedef_ `using DataType = typename std::decay_t<std::remove_pointer_t<ResultType>>;`
- L806 _private function_ `static ResultType DerefPointerIfNonPointerResultType(const DataType* InData)` — Only deref a pointer if the returned type is specifically requested to be a non-pointer.
- L823 _public function_ `static ResultType Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)` — Return a the underlying data by value or by const pointer depending upon the template parameter ResultType
- L860 _public function_ `static TDataReadReference<DataType> Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)`
- L892 _public function_ `static TDataValueReference<DataType> Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)`
- L904 _public function_ `static TDataWriteReference<DataType> Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)`

#### struct `Metasound::FAnyDataReference::TGetAs`  
`template<typename DataType> struct TGetAs<TDataWriteReference<DataType>>`  
_L902-912_
- desc: Template specialization for retrieving data reference as a TDataWriteReference<DataType>
- L802 _private typedef_ `using DataType = typename std::decay_t<std::remove_pointer_t<ResultType>>;`
- L806 _private function_ `static ResultType DerefPointerIfNonPointerResultType(const DataType* InData)` — Only deref a pointer if the returned type is specifically requested to be a non-pointer.
- L823 _public function_ `static ResultType Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)` — Return a the underlying data by value or by const pointer depending upon the template parameter ResultType
- L860 _public function_ `static TDataReadReference<DataType> Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)`
- L892 _public function_ `static TDataValueReference<DataType> Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)`
- L904 _public function_ `static TDataWriteReference<DataType> Get(EDataReferenceAccessType InAccessType, const IDataReference& InRef)`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L20 _namespace_ `namespace Audio`
- L26 _namespace_ `namespace Metasound`
- L34 _prototype_ `FString LexToString(Metasound::EDataReferenceAccessType InAccessType);` — Convert a EDataReferenceAccessType to FString.
- L36 _typedef_ `using FMetasoundDataTypeId = void const* const;`
- L38 _namespace_ `namespace Metasound`
- L41 _typedef_ `using FDataReferenceID = const void*;` (scope `Metasound`) — Unique ID type which corresponds to the underlying object referred to by a data reference.
- L44 _prototype_ `FName CreateArrayTypeNameFromElementTypeName(const FName InTypeName);` (scope `Metasound`) — Returns array type associated with the base datatype provided(ex. 'Float:Array' if 'Float' is provided)
- L47 _prototype_ `FName CreateElementTypeNameFromArrayTypeName(const FName InArrayTypeName);` (scope `Metasound`) — Returns the base data type with the array extension(ex. 'Float' if 'Float:Array' is provided)
- L75 _function_ `inline FDataReferenceID GetDataReferenceID(const IDataReference& InDataReference)` (scope `Metasound`) — Return the ID of the data reference.
- L82 _function_ `bool IsChildOf(const FName InBaseType)` (scope `Metasound`)
- L92 _typedef_ `using Base = typename TPolymorphicTraits<T>::BaseType;` (scope `Metasound::IsChildOf`)
- L106 _function_ `template<typename DataType> requires TPolymorphicTraits<DataType>::bIsPolymorphic bool IsDataReferenceOfType(const IDataReference& InReference)` (scope `Metasound`) — Polymorphic overload
- L119 _typedef_ `using FPolyType = TPolymorphicTraits<DataType>;` (scope `Metasound::IsDataReferenceOfType`) — Recurse to base type
- L126 _function_ `template<typename DataType> requires (!TPolymorphicTraits<DataType>::bIsPolymorphic) bool IsDataReferenceOfType(const IDataReference& InReference)` (scope `Metasound`) — Non-polymorphic fallback
- L143 _namespace_ `namespace MetasoundDataReferencePrivate` (scope `Metasound`)
- L147 _function_ `TSharedRef<Base, ESPMode::NotThreadSafe> MakeRefOf(ArgTypes&&... Args)` (scope `Metasound::MetasoundDataReferencePrivate`)
- L159 _function_ `TSharedRef<Base, ESPMode::NotThreadSafe> MakeRefOf(ArgTypes&&... Args) requires CHasFactoryFunction<Derived, ArgTypes...>` (scope `Metasound::MetasoundDataReferencePrivate`)
- L478 _typedef_ `typedef TDataValueReference<DataType> FValueDataReference;` (scope `Metasound::TDataValueReference::Clone`)
- L492 _function_ `template<typename T> TDataValueReference<T> ValueCast(const TDataReadReference<T>& InRef)` (scope `Metasound`) — Cast a TDataReadReference to a TDataValueReference. In general TDataReadReferences should not be converted into TDataValueReferences unless the caller can be certain that no other TDataWriteReference exists for the underlying parameter. Having a TDataWriteReferences to an existing TDataValueReference can cause confusing behavior as values references are not expected to change value.
- L505 _function_ `template<typename T> TDataValueReference<T> ValueCast(const TDataWriteReference<T>& InRef)` (scope `Metasound`) — Cast a TDataWriteReference to a TDataValueReference. In general TDataWriteReferences should never beconverted into TDataValueReferences unless the caller can be certain that no other TDataWriteReference exists for the underlying parameter. Having a TDataWriteReferences to an existing TDataValueReference can cause confusing behavior as values references are not expected to change value.
- L626 _typedef_ `typedef TDataWriteReference<DataType> FDataWriteReference;` (scope `Metasound::TDataWriteReference::Clone`)
- L644 _function_ `template <typename DataType> TDataWriteReference<DataType> WriteCast(const TDataReadReference<DataType>& InReadableRef)` (scope `Metasound`) — Cast a TDataReadReference to a TDataWriteReference. In general TDataReadReferences should not be converted into TDataWriteReferences unless the caller can be certain that no other TDataWriteReference exists for the underlying parameter. Having multiple TDataWriteReferences to the same parameter can cause confusion behavior as values are overwritten in an underterministic fashion.
- L764 _typedef_ `typedef TDataReadReference<DataType> FDataReadReference;` (scope `Metasound::TDataReadReference::Clone`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundDataReferenceCollection.h` (Public)


#### class `Metasound::FDataReferenceCollection`  
`class FDataReferenceCollection`  
_L17-264_
- L19 _private typedef_ `using FDataReferenceMap = TMap<FVertexName, FAnyDataReference>;`
- L29 _public function_ `template<typename DataType> void AddDataReadReference(const FVertexName& InName, const TDataReadReference<DataType>& InDataReference)` — Add a readable data reference to the collection. @param InName - Name of data reference. @InDataReference - Readable data reference.
- L42 _public function_ `template<typename DataType> void AddDataReadReference(const FVertexName& InName, const TDataWriteReference<DataType>& InDataReference)` — Add a readable data reference to the collection. @param InName - Name of data reference. @InDataReference - Writable data reference.
- L55 _public function_ `template<typename DataType> void AddDataWriteReference(const FVertexName& InName, const TDataWriteReference<DataType>& InDataReference)` — Add a writable data reference to the collection. @param InName - Name of data reference. @InDataReference - Writable data reference.
- L63 _public prototype_ `void AddDataReference(const FVertexName& InName, FAnyDataReference&& InDataReference);` — Add a data reference to this collection.
- L74 _public prototype_ `bool AddDataReadReferenceFrom(const FVertexName& InLocalName, const FDataReferenceCollection& InOtherCollection, const FVertexName& InOtherName, const FName& InOtherTypeName);` — Add a readable data reference from another collection. @param InLocalName - Name to give data added to this collection. @param InOtherCollection - Collection which contains the desired data reference. @param InOtherName - Name of desired data in other collection. @param InOtherType - TypeName of desired data. @return True if the data was successfully added. False otherwise.
- L85 _public prototype_ `bool AddDataWriteReferenceFrom(const FVertexName& InLocalName, const FDataReferenceCollection& InOtherCollection, const FVertexName& InOtherName, const FName& InOtherTypeName);` — Add a writable data reference from another collection. @param InLocalName - Name to give data added to this collection. @param InOtherCollection - Collection which contains the desired data reference. @param InOtherName - Name of desired data in other collection. @param InOtherType - TypeName of desired data. @return True if the data was successfully added. False otherwise.
- L94 _public prototype_ `bool ContainsDataReadReference(const FVertexName& InName, const FName& InTypeName) const;` — Query whether a readable data reference is within the collection. @param InName - Name of the data. @param InTypeName - TypeName of teh data. @return True if the data exists in the collection. False otherwise.
- L103 _public prototype_ `bool ContainsDataWriteReference(const FVertexName& InName, const FName& InTypeName) const;` — Query whether a writable data reference is within the collection. @param InName - Name of the data. @param InTypeName - TypeName of teh data. @return True if the data exists in the collection. False otherwise.
- L109 _public prototype_ `const FAnyDataReference* FindDataReference(const FVertexName& InName) const;` — Returns pointer to data reference if it exists for a given vertex name. If no data reference exists for the given vertex name, a nullptr is returned.
- L118 _public function_ `template<typename DataType> bool ContainsDataReadReference(const FVertexName& InName) const` — Query whether a readable data reference is within the collection. @param InName - Name of the data. @return True if the data exists in the collection. False otherwise.
- L139 _public function_ `template<typename DataType> bool ContainsDataWriteReference(const FVertexName& InName) const` — Query whether a writable data reference is within the collection. @param InName - Name of the data. @return True if the data exists in the collection. False otherwise.
- L160 _public function_ `template<typename DataType> TDataReadReference<DataType> GetDataReadReference(const FVertexName& InName) const` — Returns a readable data ref from the collection. @param InName - Name of readable data. @return A readable data reference.
- L177 _public function_ `template<typename DataType, typename... ConstructorArgTypes> TDataReadReference<DataType> GetDataReadReferenceOrConstruct(FVertexName InName, ConstructorArgTypes&&... ConstructorArgs) const` — Returns a readable data ref from the collection or construct one if one is not there. @param InName - Name of readable data. @param ConstructorArgs - Arguments to pass to constructor of TDataReadReference<DataType> @return A readable data reference.
- L201 _public function_ `template<typename DataType> TDataReadReference<DataType> GetDataReadReferenceOrConstructWithVertexDefault(const FInputVertexInterface& InputVertices, FVertexName InName, const FOperatorSettings& InSettings) const` — Returns a readable data ref from the collection or construct one if one is not there with the default provided from the given input vertex collection. @param InputVertices - Collection of input vertices to retrieve default from if reference is not available @param InName - Name of readable data. @param InSettings - OperatorSettings of Metasound Operator @return A readable data reference.
- L229 _public function_ `template<typename DataType> TDataWriteReference<DataType> GetDataWriteReference(const FVertexName& InName) const` — Returns a writable data ref from the collection. @param InName - Name of readable data. @return A readable data reference.
- L246 _public function_ `template<typename DataType, typename... ConstructorArgTypes> TDataWriteReference<DataType> GetDataWriteReferenceOrConstruct(const FVertexName& InName, ConstructorArgTypes&&... ConstructorArgs) const` — Returns a writable data ref from the collection or construct one if one is not there. @param InName - Name of readable data. @param ConstructorArgs - Arguments to pass to constructor of TDataWriteReference<DataType> @return A readable data reference.
- L263 _private member_ `FDataReferenceMap DataRefMap;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L12 _namespace_ `namespace Metasound`
- L179 _typedef_ `typedef TDataReadReference<DataType> FDataRefType;` (scope `Metasound::FDataReferenceCollection::GetDataReadReferenceOrConstruct`)
- L203 _typedef_ `using FDataFactory = TDataReadReferenceLiteralFactory<DataType>;` (scope `Metasound::FDataReferenceCollection::GetDataReadReferenceOrConstructWithVertexDefault`)
- L248 _typedef_ `typedef TDataWriteReference<DataType> FDataRefType;` (scope `Metasound::FDataReferenceCollection::GetDataWriteReferenceOrConstruct`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundDataReferenceMacro.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define DECLARE_METASOUND_DATA_REFERENCE_CORE_TYPE(DataType, ModuleApi) \`
- L21 _macro_ `#define DECLARE_METASOUND_DATA_REFERENCE_ALIAS_TYPES(DataType, DataTypeInfoTypeName, DataReadReferenceTypeName, DataWriteReferenceTypeName) \`
- L27 _macro_ `#define DECLARE_METASOUND_DATA_REFERENCE_TYPES_NO_ALIASES(DataType, ModuleApi) \`
- L37 _macro_ `#define DECLARE_METASOUND_DATA_REFERENCE_TYPES(DataType, ModuleApi, DataTypeInfoTypeName, DataReadReferenceTypeName, DataWriteReferenceTypeName) \` — Declares a metasound parameter type by - Adding typedefs for commonly used template types. - Defining parameter type traits.
- L41 _macro_ `#define DEFINE_METASOUND_DATA_REFERENCE_CORE_TYPE(DataType, DataTypeName, DataTypeLoctextKey) \`
- L54 _macro_ `#define METASOUND_DATA_TYPE_NAME_VARIABLE_TYPE_SPECIFIER ":Variable"`
- L55 _macro_ `#define METASOUND_DATA_TYPE_NAME_ARRAY_TYPE_SPECIFIER ":Array"`
- L58 _macro_ `#define DEFINE_METASOUND_DATA_TYPE(DataType, DataTypeName) \` — This only needs to be called if you don't plan on calling REGISTER_METASOUND_DATATYPE.

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundDataTypeGetTraits.h` (Public)


#### struct `Metasound::TDataReferenceTypeInfo`  
`template<> struct TDataReferenceTypeInfo<void>`  
_L21-31_
- desc: Specialize void data type for internal use.
- L23 _public member_ `static const TCHAR* TypeName;`
- L24 _public member_ `static const void* const TypeId;`
- L25 _public prototype_ `static const FText& GetTypeDisplayText();`
- L26 _public function_ `static const void* GetTypeId()`
- L30 _private member_ `static const void* const TypePtr;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Metasound`
- L35 _function_ `template<typename DataType> const FName& GetMetasoundDataTypeName()` (scope `Metasound`) — Return the data type FName for a registered data type.
- L44 _function_ `template<typename DataType> const FString& GetMetasoundDataTypeString()` (scope `Metasound`) — Return the data type string for a registered data type.
- L53 _function_ `template<typename DataType> const FText& GetMetasoundDataTypeDisplayText()` (scope `Metasound`) — Return the display text for a registered data type.
- L63 _function_ `template<typename DataType> const void* const GetMetasoundDataTypeId()` (scope `Metasound`) — Return the data type ID for a registered data type. This ID is runtime constant but may change between executions and builds.

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundDynamicOperatorTransactor.h` (Public)


#### struct `Metasound::DynamicGraph::FDynamicOperatorUpdateCallbacks`  
`struct FDynamicOperatorUpdateCallbacks`  
_L68-75_
- desc: A collection of callbacks for handling updates to MetaSound dynamic operators. Callbacks are invoked on the same thread which executes the dynamic operator.
- L70 _public member_ `FOnInputVertexUpdated OnInputAdded;`
- L71 _public member_ `FOnInputVertexUpdated OnInputRemoved;`
- L72 _public member_ `FOnOutputVertexUpdated OnOutputAdded;`
- L73 _public member_ `FOnOutputVertexUpdated OnOutputUpdated;`
- L74 _public member_ `FOnOutputVertexUpdated OnOutputRemoved;`

#### struct `Metasound::DynamicGraph::FOrdinalSwap`  
`struct FOrdinalSwap`  
_L80-95_
- desc: FOrdinalSwap represents a change in ordinal for an individual operator.
- L82 _public member_ `FOperatorID OperatorID = 0;`
- L83 _public member_ `int32 OriginalOrdinal = ORDINAL_NONE;`
- L84 _public member_ `int32 NewOrdinal = ORDINAL_NONE;`
- L91 _public function_ `static bool OriginalOrdinalLessThan(const FOrdinalSwap& InLHS, const FOrdinalSwap& InRHS)`

#### class `Metasound::DynamicGraph::FDynamicGraphIncrementalSorter`  
`class FDynamicGraphIncrementalSorter`  
_L105-172_
- desc: FDynamicGraphIncrementalSorter implements a dynamic topological sorting algorithm which offers several optimizations over doing full sorts. - It can detect if a sort is needed or not. If a sort is unneeded we can skip sorts. - Sorts are generally not done on the entire set of operators. The sort is generally done on a subset of nodes related to the nodes being connected.
- L116 _public prototype_ `FDynamicGraphIncrementalSorter();`
- L118 _public prototype_ `FDynamicGraphIncrementalSorter(const FGraph& InGraph);`
- L123 _public prototype_ `int32 InsertOperator(FOperatorID InOperator, EInsertLocation InLocation);` — Insert a node into the graph. @return Ordinal of added operator.
- L130 _public prototype_ `int32 RemoveOperator(FOperatorID InOperatorID);` — Remove a node from the graph. @param OpeartorID - ID of operator to remove @return Ordinal of removed operator.
- L133 _public prototype_ `void GenerateOrdinals(TMap<FOperatorID, int32>& OutOrdinals) const;` — Populate a TMap<> with an ordinal for every operator.
- L142 _public prototype_ `void AddDataEdge(FOperatorID InFromOperatorID, FOperatorID InToOperatorID, TArray<FOrdinalSwap>& OutOrdinalUpdates);` — Add an edge to the graph, connecting two vertices from two nodes. @param InFromOperatorID - Operator which contains the output vertex. @param InToOperatorID - Operator which contains the input vertex. @param OutOrdinalUpdates - Array to populate with ordinal updates to maintain topological sort of graph.
- L145 _public prototype_ `void RemoveDataEdge(FOperatorID InFromOperatorID, FOperatorID InToOperatorID);` — Remove the given data edge.
- L165 _private prototype_ `void IncrementalTopologicalSortForNewEdge(FOperatorID InFromOperatorID, int32 InFromOrdinal, FOperatorID InToOperatorID, int32 InToOdinal, TArray<FOrdinalSwap>& OutUpdates);`
- L167 _private prototype_ `void Init(const FGraph& InGraph);`
- L169 _private member_ `int32 MaxOrdinal = 0;`
- L170 _private member_ `int32 MinOrdinal = 0;`
- L171 _private member_ `TMap<FOperatorID, FIncrementalSortOperatorInfo> OperatorMap;`

#### enum `Metasound::DynamicGraph::FDynamicGraphIncrementalSorter::EInsertLocation`  
`enum class EInsertLocation : uint8`  
_L110-114_
- desc: Where to insert a new operator.
- L112 _public enumerator_ `First`
- L113 _public enumerator_ `Last`

#### struct `Metasound::DynamicGraph::FDynamicGraphIncrementalSorter::FIncrementalSortOperatorInfo`  
`struct FIncrementalSortOperatorInfo`  
_L153-163_
- L155 _public member_ `int32 Ordinal;`
- L161 _public member_ `TArray<FOperatorID> Inputs;` — We track connections in order to determine whether a dependency exists between two operators. Because two operators can have multiple shared edges, FOperatorIDs may appear multiple times in these arrays.
- L162 _public member_ `TArray<FOperatorID> Outputs;`

#### class `Metasound::DynamicGraph::FDynamicOperatorTransactor`  
`class FDynamicOperatorTransactor`  
_L183-306_
- desc: The FDynamicOperatorTransactor is used for communicating with a dynamic MetaSound operator. Graph manipulations performed on the transactor are forwarded to dynamic operators using the transform queue. Each modification is converted into IDynamicOperatorTransforms which are consumed by dynamic operators during their execution.
- L186 _public prototype_ `FDynamicOperatorTransactor& operator=(const FDynamicOperatorTransactor&) = delete;`
- L187 _public prototype_ `FDynamicOperatorTransactor(const FDynamicOperatorTransactor&) = delete;`
- L189 _public prototype_ `FDynamicOperatorTransactor();`
- L190 _public prototype_ `FDynamicOperatorTransactor(const FGraph& InGraph);`
- L194 _public prototype_ `TSharedRef<TSpscQueue<TUniquePtr<IDynamicOperatorTransform>>> CreateTransformQueue(const FOperatorSettings& InOperatorSettings, const FMetasoundEnvironment& InEnvironment);` — `UE_DEPRECATED(5.5, "Replace with CreateTransformQueue overload including FGraphRenderCost")` — Create a queue for communication with a dynamic operator.
- L195 _public prototype_ `TSharedRef<TSpscQueue<TUniquePtr<IDynamicOperatorTransform>>> CreateTransformQueue(const FOperatorSettings& InOperatorSettings, const FMetasoundEnvironment& InEnvironment, const TSharedPtr<FGraphRenderCost>& InRenderCost);`
- L198 _public prototype_ `bool AddNode(const FGuid& InNodeID, TUniquePtr<INode> InNode);` — Add a node to the graph.
- L201 _public prototype_ `bool RemoveNode(const FGuid& InNodeID);` — Remove a node from the graph.
- L211 _public prototype_ `void AddDataEdge(const FGuid& InFromNodeID, const FVertexName& InFromVertex, const FGuid& InToNodeID, const FVertexName& InToVertex);` — Add an edge to the graph, connecting two vertices from two nodes. @param FromNode - Node which contains the output vertex. @param FromVertex - Key of the vertex in the FromNode. @param ToNode - Node which contains the input vertex. @param ToVertex - Key of the vertex in the ToNode.
- L214 _public prototype_ `void RemoveDataEdge(const FGuid& InFromNode, const FVertexName& InFromVertexName, const FGuid& InToNode, const FVertexName& InToVertexName, TUniquePtr<INode> InReplacementLiteralNode);` — `UE_DEPRECATED(5.6, "Literal nodes will no longer be supported. Use RemoveDataEdge with an FLiteral instead.")`
- L217 _public prototype_ `void RemoveDataEdge(const FGuid& InFromNode, const FVertexName& InFromVertexName, const FGuid& InToNode, const FVertexName& InToVertexName, FLiteral InReplacementLiteral, const FReferenceCreationFunction InReferenceCreateFunc);` — Remove the given data edge.
- L220 _public prototype_ `void SetValue(const FGuid& InNodeID, const FVertexName& InVertexName, TUniquePtr<INode> InLiteralNode);` — `UE_DEPRECATED(5.6, "Setting values using a literal node will no longer be supported. Set literal on the vertex interface instead.")`
- L223 _public prototype_ `void SetValue(const FGuid& InNodeID, const FVertexName& InVertexName, const FLiteral& InLiteral, const FReferenceCreationFunction InReferenceCreateFunc);` — Set the value on a unconnected node input vertex.
- L231 _public prototype_ `void AddInputDataDestination(const FGuid& InNode, const FVertexName& InVertexName, const FLiteral& InDefaultLiteral, FReferenceCreationFunction InFunc);` — Add an input data destination to describe how data provided outside this graph should be routed internally. @param InNode - Node which receives the data. @param InVertexName - Key for input vertex on InNode.
- L234 _public prototype_ `void RemoveInputDataDestination(const FVertexName& InVertexName);` — Remove an exposed input from the graph.
- L242 _public prototype_ `void AddOutputDataSource(const FGuid& InNode, const FVertexName& InVertexName);` — Add an output data source which describes routing of data which is owned this graph and exposed externally. @param InNode - Node which produces the data. @param InVertexName - Key for output vertex on InNode.
- L245 _public prototype_ `void RemoveOutputDataSource(const FVertexName& InVertexName);` — Remove an exposed output from the graph.
- L248 _public prototype_ `const FGraph& GetGraph() const;` — Return internal version of graph.
- L254 _private prototype_ `void RemoveNodeInternal(const INode& InNode, bool bInRemoveDataEdgesWithNode);`
- L255 _private prototype_ `void FadeAndRemoveNodeInternal(const INode& InNode, TArrayView<const FVertexName> InOutputsToFade, bool bInRemoveDataEdgesWithNode);`
- L257 _private prototype_ `void EnqueueInsertOperatorTransform(const INode& InNode, int32 InOrdinal);`
- L258 _private prototype_ `void EnqueueRemoveOperatorTransform(const INode& InNode, const TArray<FOperatorID>& InOperatorsConnectedToInput);`
- L259 _private prototype_ `void EnqueueBeginFadeOperatorTransform(const INode& InNode, EAudioFadeType InFadeType, TArrayView<const FVertexName> InInputsToFade, TArrayView<const FVertexName> InOutputsToFade);`
- L260 _private prototype_ `void EnqueueEndFadeOperatorTransform(const INode& InNode);`
- L263 _private prototype_ `void EnqueueRemoveEdgeOperatorTransform_Deprecated(const INode& InFromNode, const FVertexName& InFromVertexName, const INode& InToNode, const FVertexName& InToVertexName, const INode& InReplacementLiteralNode, int32 InLiteralOrdinal);` — Only used by deprecated 5.6 functions
- L264 _private prototype_ `void EnqueueFadeAndRemoveEdgeOperatorTransform_Deprecated(const INode& InFromNode, const FVertexName& InFromVertexName, const INode& InToNode, const FVertexName& InToVertexName, const INode& InReplacementLiteralNode, int32 InLiteralOrdinal);`
- L266 _private prototype_ `void EnqueueRemoveEdgeOperatorTransform(const INode& InFromNode, const FVertexName& InFromVertexName, const INode& InToNode, const FVertexName& InToVertexName, const FLiteral& InReplacementLiteral, const FReferenceCreationFunction InReferenceCreateFunc);`
- L267 _private prototype_ `void EnqueueFadeAndRemoveEdgeOperatorTransform(const INode& InFromNode, const FVertexName& InFromVertexName, const INode& InToNode, const FVertexName& InToVertexName, const FLiteral& InReplacementLiteral, const FReferenceCreationFunction InReferenceCreateFunc);`
- L269 _private prototype_ `void EnqueueAddEdgeOperatorTransform(const INode& InFromNode, const FVertexName& InFromVertex, const INode& InToNode, const FVertexName& InToVertex, const TArray<FOrdinalSwap>& InOrdinalUpdates);`
- L270 _private prototype_ `void EnqueueFadeAndAddEdgeOperatorTransform(const INode& InFromNode, const FVertexName& InFromVertex, const INode& InToNode, const FVertexName& InToVertex, const TArray<FOrdinalSwap>& InOrdinalUpdates);`
- L272 _private prototype_ `void AddDataEdgeInternal(const INode& InFromNode, const FVertexName& InFromVertex, const FGuid& InToNodeID, const INode& InToNode, const FVertexName& InToVertex);`
- L281 _private typedef_ `using FCreateTransformFunctionRef = TFunctionRef<TUniquePtr<IDynamicOperatorTransform>(const FDynamicOperatorInfo& InOperatorInfo)>;`
- L283 _private prototype_ `TUniquePtr<IDynamicOperatorTransform> CreateInsertOperatorTransform(const INode& InNode, int32 InOrdinal, const FOperatorSettings& InOperatorSettings, const FMetasoundEnvironment& InEnvironment, FGraphRenderCost* InGraphRenderCost) const;`
- L285 _private prototype_ `void EnqueueTransformOnOperatorQueues(FCreateTransformFunctionRef InFunc);`
- L287 _private member_ `FOperatorBuilder OperatorBuilder;`
- L288 _private member_ `FGraph Graph;`
- L289 _private member_ `FDynamicGraphIncrementalSorter GraphSorter;`
- L292 _private member_ `TArray<FDynamicOperatorInfo> OperatorInfos;`
- L301 _private member_ `TSortedMap<FLiteralNodeID, TUniquePtr<INode>> LiteralNodeMap;`

#### struct `Metasound::DynamicGraph::FDynamicOperatorTransactor::FDynamicOperatorInfo`  
`struct FDynamicOperatorInfo`  
_L273-279_
- L275 _public member_ `FOperatorSettings OperatorSettings;`
- L276 _public member_ `FMetasoundEnvironment Environment;`
- L277 _public member_ `TSharedPtr<FGraphRenderCost> GraphRenderCost;`
- L278 _public member_ `TWeakPtr<TSpscQueue<TUniquePtr<IDynamicOperatorTransform>>> Queue;`

#### struct `Metasound::DynamicGraph::FDynamicOperatorTransactor::FLiteralNodeID`  
`struct FLiteralNodeID`  
_L294-298_
- L296 _public member_ `FGuid ToNode;`
- L297 _public member_ `FVertexName ToVertex;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L20 _macro_ `#define METASOUND_DEBUG_DYNAMIC_TRANSACTOR !UE_BUILD_SHIPPING`
- L23 _namespace_ `namespace Metasound`
- L29 _namespace_ `namespace DynamicGraph` (scope `Metasound`)
- L39 _namespace_ `namespace Debug` (scope `Metasound::DynamicGraph`)
- L54 _prototype_ `bool CompareAndLogGraphRepresentationDiscrepancies(const FDynamicOperatorTransactor& InTransactor, const FDynamicOperator& InDynamicOperator);` (scope `Metasound::DynamicGraph::Debug`) — This can be used when debugging Dynamic Operator internals. The FDynamicOperatorTransactor and FDynamicOperator have three graph representations. Maintaining three different graph representations can be error prone. This method can be used to validate the graphs are equivalent, or help diagnose where they differ. The three graph representations are: 1. An IGraph contains in the FDynamicOperatorTransactor 2. A FDynamicGraphIncrementalSorter in the FDynamicOperatorTransactor 3. A FDynamicGraphOperatorData in the FDynamicOperator. This method returns true if all three graph representations are equivalent, and false otherwsie. Graph differences are logged to help diagnose the issue.
- L58 _typedef_ `using FOperatorID = uintptr_t;` (scope `Metasound::DynamicGraph`)
- L59 _typedef_ `using FLiteralAssignmentFunction = void(*)(const FOperatorSettings& InOperatorSettings, const FLiteral& InLiteral, const FAnyDataReference& OutDataRef);` (scope `Metasound::DynamicGraph`)
- L60 _typedef_ `using FReferenceCreationFunction = TOptional<FAnyDataReference>(*)(const FOperatorSettings& InSettings, FName DataType, const FLiteral& InLiteral, EDataReferenceAccessType InAccessType);` (scope `Metasound::DynamicGraph`)
- L61 _typedef_ `using FOnInputVertexUpdated = TFunction<void(const FVertexName&, const FInputVertexInterfaceData&)>;` (scope `Metasound::DynamicGraph`)
- L62 _typedef_ `using FOnOutputVertexUpdated = TFunction<void(const FVertexName&, const FOutputVertexInterfaceData&)>;` (scope `Metasound::DynamicGraph`)
- L77 _variable_ `constexpr int32 ORDINAL_NONE = TNumericLimits<int32>::Max();` (scope `Metasound::DynamicGraph`)
- L86 _function_ `friend bool operator==(const FOrdinalSwap& InOrdinalSwap, FOperatorID InOperatorID)` (scope `Metasound::DynamicGraph`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundEnvironment.h` (Public)


#### struct `Metasound::MetasoundEnvironmentPrivate::TSpecializationHelper`  
`template<typename DataType> struct TSpecializationHelper`  
_L42-45_
- desc: Helper class to ensure that DECLARE_METASOUND_ENVIRONMENT_VARIABLE is used.

#### enum `Metasound::MetasoundEnvironmentPrivate::TSpecializationHelper::(anonymous)`  
`enum`  
_L44-44_

#### struct `Metasound::TEnvironmentVariableTypeInfo`  
`struct TEnvironmentVariableTypeInfo`  
_L51-59_
- desc: struct METASOUNDGRAPHCORE_API TEnvironmentVariableTypeInfo
- L53 _public typedef_ `typedef VarType Type;`
- L55 _public member_ `static const FMetasoundEnvironmentVariableTypeId TypeId;`

#### class `Metasound::IMetasoundEnvironmentVariable`  
`class IMetasoundEnvironmentVariable`  
_L74-95_
- desc: Interface for a metasound environment variable which supports a name, a runtime type ID, and a clone method.
- L82 _private prototype_ `IMetasoundEnvironmentVariable() = default;`
- L85 _public prototype_ `virtual ~IMetasoundEnvironmentVariable() = default;`
- L88 _public prototype_ `virtual const FName& GetName() const = 0;` — The name of this environment variable.
- L91 _public prototype_ `virtual FMetasoundEnvironmentVariableTypeId GetTypeId() const = 0;` — The type id of this environment variable.
- L94 _public prototype_ `virtual TUniquePtr<IMetasoundEnvironmentVariable> Clone() const = 0;` — Create a copy of this environment variable.

#### class `Metasound::TMetasoundEnvironmentVariable`  
`template<typename Type> class TMetasoundEnvironmentVariable : public IMetasoundEnvironmentVariable`  
_L98-154_
- inherits: `IMetasoundEnvironmentVariable`
- L115 _public function_ `template<typename... ArgTypes> TMetasoundEnvironmentVariable(const FName& InName, ArgTypes&&... Args) : Name(InName) , Value(Forward<ArgTypes>(Args)...)` — Construct an environment variable @param InName - Name of the environment variable. @param ...Args - Parameter pack to be forwarded to underlying types constructor.
- L122 _public function_ `const Type& GetValue() const` — Get the current value.
- L128 _public function_ `void SetValue(const Type& InValue)` — Set the current value.
- L134 _public function_ `const FName& GetName() const override` — Get the name of this environment variable.
- L140 _public function_ `FMetasoundEnvironmentVariableTypeId GetTypeId() const override` — Get the type ID of this environment variable.
- L146 _public function_ `TUniquePtr<IMetasoundEnvironmentVariable> Clone() const override` — Create a clone of this environment variable.
- L152 _private member_ `FName Name;`
- L153 _private member_ `Type Value;`

#### class `Metasound::FMetasoundEnvironment`  
`class FMetasoundEnvironment`  
_L187-279_
- desc: FMetasoundEnvironment contains a set of TMetasoundEnvironmentVariables requiring that each environment variable has a unique name.
- L190 _public prototype_ `FMetasoundEnvironment() = default;`
- L191 _public prototype_ `~FMetasoundEnvironment() = default;`
- L193 _public prototype_ `FMetasoundEnvironment(const FMetasoundEnvironment& InOther);`
- L195 _public prototype_ `FMetasoundEnvironment& operator=(const FMetasoundEnvironment& InOther);`
- L204 _public function_ `template<typename VarType> bool IsType(const FName& InVariableName) const` — Returns true if the environment variable with the given name contains the data of the same type as `VarType` @param InVariableName - Name of environment variable. @tparam VarType - Type of the underlying data stored in the environment variable.
- L216 _public function_ `template<typename VarType> bool Contains(const FName& InVariableName) const` — Returns true if the environment contains a variable with the name `InVariableName` and the type `VarType`. @param InVariableName - Name of environment variable. @tparam VarType - Type of the underlying data stored in the environment variable.
- L233 _public function_ `template<typename VarType> VarType GetValue(const FName& InVariableName) const` — Returns the environment variable data. @param InVariableName - Name of environment variable. @tparam VarType - Type of the underlying data stored in the environment variable. @return copy of the underlying data.
- L252 _public function_ `template<typename VarType> void SetValue(const FName& InVariableName, const VarType& InValue)` — Sets the environment variable data @param InVariableName - Name of environment variable. @tparam VarType - Type of the underlying data stored in the environment variable. @return const ref to the underlying data.
- L261 _public function_ `void SetValue(TUniquePtr<IMetasoundEnvironmentVariable> InValue)` — Sets the environment variable data from a given environment variable @param InValue - Environment variable to set.
- L266 _public typedef_ `using FRangedForConstIteratorType = TSortedMap<FName, TUniquePtr<IMetasoundEnvironmentVariable>, FDefaultAllocator, FNameFastLess>::RangedForConstIteratorType;`
- L267 _public function_ `FRangedForConstIteratorType begin() const`
- L272 _public function_ `FRangedForConstIteratorType end() const`
- L278 _private member_ `TSortedMap<FName, TUniquePtr<IMetasoundEnvironmentVariable>, FDefaultAllocator, FNameFastLess> Variables;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L14 _macro_ `#define WITH_METASOUND_DEBUG_ENVIRONMENT !UE_BUILD_SHIPPING`
- L17 _macro_ `#define DECLARE_METASOUND_ENVIRONMENT_VARIABLE_TYPE(DLL_API, VarType) \`
- L29 _macro_ `#define DEFINE_METASOUND_ENVIRONMENT_VARIABLE_TYPE(VarType) \`
- L34 _typedef_ `using FMetasoundEnvironmentVariableTypeId = void const* const;`
- L36 _namespace_ `namespace Metasound`
- L38 _namespace_ `namespace MetasoundEnvironmentPrivate` (scope `Metasound`)
- L44 _enumerator_ `enum { Value = false };` (scope `Metasound::MetasoundEnvironmentPrivate::TSpecializationHelper::__anonc78dcd1c0103`)
- L64 _function_ `template<typename Type> FMetasoundEnvironmentVariableTypeId GetMetasoundEnvironmentVariableTypeId()` (scope `Metasound`) — Return the type ID for a environment variable type.
- L66 _typedef_ `using FTypeInfo = TEnvironmentVariableTypeInfo< std::decay_t<Type> >;` (scope `Metasound::GetMetasoundEnvironmentVariableTypeId`)
- L159 _function_ `template<typename VarType> bool IsEnvironmentVariableOfType(const IMetasoundEnvironmentVariable& InVar)` (scope `Metasound`) — Returns true if the environment variable contains the same type as the `VarType`
- L166 _function_ `template<typename Type> TMetasoundEnvironmentVariable<Type>& CastMetasoundEnvironmentVariableChecked(IMetasoundEnvironmentVariable& InVar)` (scope `Metasound`) — Casts an environment variable to the derived type.
- L168 _typedef_ `using FDerivedType = TMetasoundEnvironmentVariable<Type>;` (scope `Metasound::CastMetasoundEnvironmentVariableChecked`)
- L176 _function_ `template<typename Type> const TMetasoundEnvironmentVariable<Type>& CastMetasoundEnvironmentVariableChecked(const IMetasoundEnvironmentVariable& InVar)` (scope `Metasound`) — Casts an environment variable to the derived type.
- L281 _namespace_ `namespace CoreInterface` (scope `Metasound`)
- L283 _namespace_ `namespace Environment` (scope `Metasound::CoreInterface`)
- L287 _externvar_ `const extern FLazyName InstanceID;` (scope `Metasound::CoreInterface::Environment`) — The InstanceID acts as an external ID for communicating and in and out of MetaSounds. Each MetaSound has a unique InstanceID
- L290 _externvar_ `const extern FLazyName GraphHierarchy;` (scope `Metasound::CoreInterface::Environment`) — An array representing the graph hierarchy.

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundExecutableOperator.h` (Public)


#### class `Metasound::MetasoundExecutableOperatorPrivate::TIsResetMethodDeclared`  
`template <typename U> class TIsResetMethodDeclared`  
_L17-30_
- desc: Helper template to determine whether a member function is declared for a given template class.
- L24 _private prototype_ `template<typename T> static uint8 Check(Helper<void(T::*)(const IOperator::FResetParams&), &T::Reset>*);`
- L26 _private prototype_ `template<typename T> static uint16 Check(...);`
- L29 _public member_ `static constexpr bool Value = sizeof(Check<U>(0)) == sizeof(uint8);`

#### struct `Metasound::MetasoundExecutableOperatorPrivate::TResetFunctionAdapter`  
`template<typename OperatorType> struct TResetFunctionAdapter`  
_L45-77_
- desc: Helper to determine whether an Reset(...) function exists. Some nodes have an Execute() call without an Reset(...) call because Reset(...) was introduced after several MetaSound releases. In order allow operators to compile, we make the Intiailize(...) function optional for subclasses of TExecutableOperator. This adapter determines whether it Reset(...) exists or not. Note: This helper must be instantiated inside the functions and cannot be part of the `TExecutableOperator<OperatorType>` class definition as classes are not completely defined at the point in the compilation process when static constexpr class members are evaluated.
- L49 _public function_ `static IOperator::FResetFunction GetResetFunction()` — Returns an IOperator::FResetFunction if the OperatorType has a Reset(...) class member function.
- L62 _private function_ `static void ResetFunction(IOperator* InOperator, const IOperator::FResetParams& InParams)`

#### class `Metasound::MetasoundExecutableOperatorPrivate::TIsPostExecuteMethodDeclared`  
`template <typename U> class TIsPostExecuteMethodDeclared`  
_L82-95_
- desc: Helper template to determine whether a member function is declared for a given template class.
- L89 _private prototype_ `template<typename T> static uint8 Check(Helper<void(T::*)(), &T::PostExecute>*);`
- L91 _private prototype_ `template<typename T> static uint16 Check(...);`
- L94 _public member_ `static constexpr bool Value = sizeof(Check<U>(0)) == sizeof(uint8);`

#### struct `Metasound::MetasoundExecutableOperatorPrivate::TPostExecuteFunctionAdapter`  
`template<typename OperatorType> struct TPostExecuteFunctionAdapter`  
_L104-136_
- desc: Helper to determine whether an PostExecute(...) function exists. Note: This helper must be instantiated inside the functions and cannot be part of the `TExecutableOperator<OperatorType>` class definition as classes are not completely defined at the point in the compilation process when static constexpr class members are evaluated.
- L108 _public function_ `static IOperator::FPostExecuteFunction GetPostExecuteFunction()` — Returns an IOperator::FPostExecuteFunction if the OperatorType has a PostExecute(...) class member function.
- L121 _private function_ `static void PostExecuteFunction(IOperator* InOperator)`

#### struct `Metasound::TExecutableDataType`  
`template<class DataType> struct TExecutableDataType`  
_L144-157_
- desc: As a general rule, ExecutableDataTypes should be avoided whenever possible as they incur an undesired cost and are generally not typically necessary. This is primarily for the special case of trigger types, where state management cannot be avoided (or rather an avoidable design has yet to be formulated).
- L146 _public member_ `static constexpr bool bIsExecutable = false;`
- L148 _public function_ `static void Execute(const DataType& InData, const DataType& OutData)`
- L153 _public function_ `static void ExecuteInline(DataType& InData, bool bInUpdated)`

#### struct `Metasound::TPostExecutableDataType`  
`template<class DataType> struct TPostExecutableDataType`  
_L160-167_
- L162 _public member_ `static constexpr bool bIsPostExecutable = false;`

#### class `Metasound::TExecutableOperator`  
`template<class DerivedOperatorType> class TExecutableOperator : public IOperator`  
_L186-217_
- inherits: `IOperator`
- desc: Convenience class for supporting the IOperator interface's GetExecuteFunction virtual member function. Derived classes should inherit from this template class as well as implement a void Execute() member function. class MyOperator : public TExecutableOperator<MyOperator> { public: ... void Execute() { ... } };
- L190 _public prototype_ `virtual ~TExecutableOperator() = default;`
- L192 _public function_ `virtual FResetFunction GetResetFunction() override`
- L197 _public function_ `virtual FExecuteFunction GetExecuteFunction() override`
- L202 _public function_ `virtual FPostExecuteFunction GetPostExecuteFunction() override`
- L209 _private function_ `static void ExecuteFunction(IOperator* InOperator)`

#### class `Metasound::FNoOpOperator`  
`class FNoOpOperator : public IOperator`  
_L223-242_
- inherits: `IOperator`
- desc: FNoOpOperator is for IOperators which do not perform any execution. Their only behavior is to perform operations on constructor or through the Bind(...) methods.
- L226 _public prototype_ `virtual ~FNoOpOperator() = default;`
- L228 _public function_ `virtual FExecuteFunction GetExecuteFunction() override`
- L233 _public function_ `virtual FResetFunction GetResetFunction() override`
- L238 _public function_ `virtual FPostExecuteFunction GetPostExecuteFunction() override`

#### class `Metasound::FExecuter`  
`class FExecuter : public IOperator`  
_L248-357_
- inherits: `IOperator`
- desc: FExecuter Wraps an IOperator and provides an Execute() member function.
- L251 _public typedef_ `using FOperatorPtr = TUniquePtr<IOperator>;`
- L253 _public function_ `FExecuter()`
- L257 _public function_ `FExecuter(FOperatorPtr InOperator)`
- L262 _public function_ `void SetOperator(FOperatorPtr InOperator)`
- L278 _public function_ `TUniquePtr<IOperator> ReleaseOperator()`
- L286 _public function_ `void Execute()`
- L294 _public function_ `void PostExecute()`
- L302 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L310 _public function_ `bool IsNoOp()`
- L315 _public function_ `bool IsValid() const`
- L320 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L328 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData) override`
- L336 _public function_ `virtual IOperator::FExecuteFunction GetExecuteFunction() override`
- L341 _public function_ `virtual IOperator::FPostExecuteFunction GetPostExecuteFunction() override`
- L346 _public function_ `virtual IOperator::FResetFunction GetResetFunction() override`
- L352 _private member_ `FOperatorPtr Operator;`
- L354 _private member_ `IOperator::FExecuteFunction ExecuteFunction = nullptr;`
- L355 _private member_ `IOperator::FPostExecuteFunction PostExecuteFunction = nullptr;`
- L356 _private member_ `IOperator::FResetFunction ResetFunction = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace MetasoundExecutableOperatorPrivate` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundFacade.h` (Public)


#### class `Metasound::MetasoundFacadePrivate::TIsFactoryMethodDeclared`  
`template <typename U> class TIsFactoryMethodDeclared`  
_L20-36_
- desc: Helper template to determine whether a static class function is declared for a given template class.
- L28 _private prototype_ `template<typename T> static uint8 Check(Helper<TUniquePtr<IOperator>(*)(const FBuildOperatorParams& InParams, FBuildResults& OutResults), &T::CreateOperator>*);` — Check for "static TUniquePtr<IOperator> U::CreateOperator(const FBuildOperatorParams& Inparams, FBuildResults& OutErrors)"
- L30 _private prototype_ `template<typename T> static uint16 Check(...);`
- L35 _public member_ `static constexpr bool Value = sizeof(Check<U>(0)) == sizeof(uint8_t);` — If the function exists, then "Value" is true. Otherwise "Value" is false.

#### class `Metasound::MetasoundFacadePrivate::TIsNodeInfoDeclared`  
`template <typename U> class TIsNodeInfoDeclared`  
_L41-61_
- desc: Helper template to determine whether a static class function is declared for a given template class.
- L49 _private prototype_ `template<typename T> static uint8 Check(Helper<const FNodeClassMetadata&(*)(), &T::GetNodeInfo>*);` — Check for "static const FNodeClassMetadata& U::GetNodeInfo()"
- L53 _private prototype_ `template<typename T> static uint8 Check(Helper<FNodeClassMetadata(*)(), &T::GetNodeInfo>*);` — Check for "static FNodeClassMetadata U::GetNodeInfo()"
- L55 _private prototype_ `template<typename T> static uint16 Check(...);`
- L60 _public member_ `static constexpr bool Value = sizeof(Check<U>(0)) == sizeof(uint8_t);` — If the function exists, then "Value" is true. Otherwise "Value" is false.

#### struct `Metasound::TFacadeOperatorClass`  
`template<typename OperatorType> struct TFacadeOperatorClass`  
_L69-82_
- desc: TFacadeOperatorClass encapsulates an operator type and checks that the required static functions exist to build the facade operator class.  It is required to call the FNodeFacade template constructor.
- L81 _public typedef_ `typedef OperatorType Type;`

#### class `Metasound::FNodeFacade`  
`class FNodeFacade : public FBasicNode`  
_L91-159_
- inherits: `FBasicNode`
- desc: FNodeFacade implements a significant amount of boilerplate code required to build a Metasound INode. FNodeFacade is particularly useful for an INode which has a static FVertexInterface, and always creates the same IOperator type. The type of the concrete IOperator class to instantiate is defined in the FNodeFacade constructors TFacadeOperatorClass<>.
- L112 _public prototype_ `FNodeFacade() = delete;`
- L123 _public function_ `template<typename OperatorType> FNodeFacade(const FVertexName& InInstanceName, const FGuid& InInstanceID, TFacadeOperatorClass<OperatorType> OperatorClass) : FNodeFacade(InInstanceName, InInstanceID, OperatorType::GetNodeInfo(), &OperatorType::CreateOperator)` — FNodeFacade constructor using the OperatorType template parameter to get the node info, operator factory method and vertex interface. @param InInstanceName - Instance name for the node. @param InInstanceID - Instance ID for the node. @param OperatorClass - Template class wrapper for the underlying IOperator which is created by this node.
- L129 _public function_ `template<typename OperatorType> FNodeFacade(const FNodeInitData& InInitData, TFacadeOperatorClass<OperatorType> OperatorClass) : FNodeFacade(InInitData.InstanceName, InInitData.InstanceID, OperatorType::GetNodeInfo(), &OperatorType::CreateOperator)`
- L135 _public function_ `template<typename OperatorType> FNodeFacade(const FNodeData& InNodeData, const TSharedRef<const FNodeClassMetadata>& InClassMetadata, TFacadeOperatorClass<OperatorType> OperatorClass) : FNodeFacade(InNodeData, InClassMetadata, &OperatorType::CreateOperator)`
- L140 _public prototype_ `virtual ~FNodeFacade() = default;`
- L143 _public prototype_ `virtual FOperatorFactorySharedRef GetDefaultOperatorFactory() const override;` — Return a reference to the default operator factory.
- L146 _private function_ `FORCENOINLINE FNodeFacade(const FVertexName& InInstanceName, const FGuid& InInstanceID, const FNodeClassMetadata& InNodeInfo, FFactory::FCreateOperatorFunction InCreate) : FBasicNode(FNodeData(InInstanceName, InInstanceID, InNodeInfo.DefaultInterface.CreateVertexInterface()), MakeShared<FNodeClassMetadata>(InNodeInfo)) , Factory(MakeShared<FFactory, ESPMode::ThreadSafe>(InCreate))`
- L152 _private function_ `FORCENOINLINE FNodeFacade(const FNodeData& InNodeData, const TSharedRef<const FNodeClassMetadata>& InClassMetadata, FFactory::FCreateOperatorFunction InCreate) : FBasicNode(InNodeData, InClassMetadata) , Factory(MakeShared<FFactory, ESPMode::ThreadSafe>(InCreate))`
- L158 _private member_ `TSharedRef<IOperatorFactory, ESPMode::ThreadSafe> Factory;`

#### class `Metasound::FNodeFacade::FFactory`  
`class FFactory : public IOperatorFactory`  
_L95-108_
- inherits: `IOperatorFactory`
- desc: Factory class for create an IOperator by using a TFunction matching the signature of the CreateOperator function.
- L97 _private typedef_ `using FCreateOperatorFunction = TUniquePtr<IOperator>(*)(const FBuildOperatorParams& InParams, FBuildResults& OutResults);`
- L101 _public prototype_ `FFactory(FCreateOperatorFunction InCreateFunc);`
- L103 _public prototype_ `virtual TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults) override;`
- L107 _private member_ `FCreateOperatorFunction CreateFunc;`

#### class `Metasound::TNodeFacade`  
`template<typename OperatorType> class TNodeFacade : public FNodeFacade`  
_L166-188_
- inherits: `FNodeFacade`
- desc: TNodeFacade further reduces boilerplate code by allowing shorthand node implementations. in the form: TNodeFacade<FMyOperator>
- L169 _public function_ `TNodeFacade(const FName& InNodeName, const FGuid& InNodeID) : TNodeFacade(FNodeInitData{InNodeName, InNodeID})`
- L174 _public function_ `TNodeFacade(const FNodeInitData& InInitData) : FNodeFacade(InInitData, TFacadeOperatorClass<OperatorType>())`
- L179 _public function_ `TNodeFacade(const FNodeData& InNodeData, const TSharedRef<const FNodeClassMetadata>& InClassMetadata) : FNodeFacade(InNodeData, InClassMetadata, TFacadeOperatorClass<OperatorType>())`
- L184 _public function_ `static FNodeClassMetadata CreateNodeClassMetadata()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L13 _namespace_ `namespace Metasound`
- L15 _namespace_ `namespace MetasoundFacadePrivate` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundGlobals.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Metasound`
- L10 _prototype_ `bool CanEverExecuteGraph(bool bIsCooking = false);` (scope `Metasound`) — Returns true if a MetaSound is expected to execute, false if not.

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundGraph.h` (Public)


#### class `Metasound::FGraph`  
`class FGraph : public IGraph`  
_L19-288_
- inherits: `IGraph`
- desc: FGraph contains the edges between nodes as well as input and output vertices.  FGraph does not maintain ownership over any node. Nodes used within the graph must be valid for the lifetime of the graph.
- L23 _public prototype_ `FGraph(const FString& InInstanceName, const FGuid& InInstanceID, TSharedPtr<const IOperatorData> InNodeConfig = { });` — `UE_DEPRECATED(5.7, "Use constructor that provides an FName or AssetPath instead")`
- L27 _public prototype_ `FGraph(const FName& InInstanceName, const FGuid& InInstanceID, TSharedPtr<const IOperatorData> InNodeConfig = { });` — Constructor to be used for dynamically generated MetaSounds not associated with a given asset (ex. test graphs, graphs not represented by an asset-contained frontend document, etc.)
- L31 _public prototype_ `FGraph(const FTopLevelAssetPath& InAssetPath, const FGuid& InInstanceID, TSharedPtr<const IOperatorData> InNodeConfig = { });` — Constructor to be used for MetaSounds associated with a given asset. Both transient and serialized assets should use this constructor, as transient assets are contained in the transient package)
- L33 _public prototype_ `virtual ~FGraph() = default;`
- L36 _public prototype_ `virtual const FTopLevelAssetPath& GetAssetPath() const override;` — Returns path to graph's authoring content (invalid if generated dynamically).
- L39 _public prototype_ `virtual const FVertexName& GetInstanceName() const override;` — Return the name of this specific instance of the node class.
- L42 _public prototype_ `virtual const FGuid& GetInstanceID() const override;` — Return the ID of this specific instance of the node class.
- L45 _public prototype_ `virtual const FNodeClassMetadata& GetMetadata() const override;` — Return metadata about this graph.
- L48 _public prototype_ `virtual const TArray<FDataEdge>& GetDataEdges() const override;` — Retrieve all the edges associated with a graph.
- L51 _public prototype_ `virtual const FVertexInterface& GetVertexInterface() const override;` — Return the current vertex interface.
- L54 _public prototype_ `virtual void SetDefaultInput(const FVertexName& InVertexName, const FLiteral& InLiteral) override;` — Set the default value associated with an input vertex.
- L57 _public prototype_ `virtual TSharedPtr<const IOperatorData> GetOperatorData() const override;` — Return the configuration for this graph.
- L60 _public prototype_ `virtual const FInputDataDestinationCollection& GetInputDataDestinations() const override;` — Get vertices which contain input parameters.
- L63 _public prototype_ `virtual const FOutputDataSourceCollection& GetOutputDataSources() const override;` — Get vertices which contain output parameters.
- L66 _public prototype_ `void AddDataEdge(const FDataEdge& InEdge);` — Add an edge to the graph.
- L78 _public prototype_ `bool AddDataEdge(const INode& FromNode, const FVertexName& FromVertexKey, const INode& ToNode, const FVertexName& ToVertexKey);` — Add an edge to the graph, connecting two vertices from two nodes. @param FromNode - Node which contains the output vertex. @param FromVertexKey - Key of the vertex in the FromNode. @param ToNode - Node which contains the input vertex. @param ToVertexKey - Key of the vertex in the ToNode. @return True if the edge was successfully added. False otherwise.
- L84 _public prototype_ `bool RemoveDataEdge(const INode& FromNode, const FVertexName& FromVertexKey, const INode& ToNode, const FVertexName& ToVertexKey);` — Remove the given data edge. @return True on success, false on failure.
- L93 _public function_ `void RemoveDataEdgeByPredicate(const PredicateType& Predicate)` — `UE_DEPRECATED(5.3, "Removing data edges by predicate is no longer supported")`
- L99 _public prototype_ `void RemoveDataEdgesWithNode(const INode& InNode);` — Removes all edges with connected to the node.
- L102 _public prototype_ `void AddNode(const FGuid& InNodeID, TSharedPtr<const INode> InNode);` — `UE_DEPRECATED(5.6, "Use AddNode(...) which accepts a unique ptr")`
- L109 _public prototype_ `void AddNode(const FGuid& InNodeID, TUniquePtr<INode> InNode);` — Store a node on this graph. @param InNodeID - A unique ID associated with the node. @param InNode - A shared pointer to a node.
- L117 _public prototype_ `void SetNodeDefaultInput(const FGuid& InNodeID, const FVertexName& InVertexName, const FLiteral& InLiteral);` — Set the input default literal for a node that exists in the graph. @param InNodeID - ID of not to update. @param InVertexName - Name of input vertex on the node. @param InLiteral - Literal used to construct default input.
- L126 _public prototype_ `void AddInputNode(FGuid InNodeID, const FVertexName& InVertexName, TSharedPtr<const INode> InNode);` — `UE_DEPRECATED(5.6, "Use AddInputNode(...) which accepts a unique ptr")` — Add an input node to this graph. @param InNodeID - A unique ID associated with the node. @param InVertexName - The key for the graph input vertex. @param InNode - A shared pointer to an input node.
- L134 _public prototype_ `void AddInputNode(FGuid InNodeID, const FVertexName& InVertexName, TUniquePtr<INode> InNode);` — Add an input node to this graph. @param InNodeID - A unique ID associated with the node. @param InVertexName - The key for the graph input vertex. @param InNode - A unique pointer to an input node.
- L143 _public prototype_ `void AddOutputNode(FGuid InNodeID, const FVertexName& InVertexName, TSharedPtr<const INode> InNode);` — `UE_DEPRECATED(5.6, "Use AddOutputNode(...) which accepts a unique ptr")` — Add an output node to this graph. @param InNodeID - A unique ID associated with the node. @param InVertexName - The key for the graph output vertex. @param InNode - A shared pointer to an output node.
- L151 _public prototype_ `void AddOutputNode(FGuid InNodeID, const FVertexName& InVertexName, TUniquePtr<INode> InNode);` — Add an output node to this graph. @param InNodeID - A unique ID associated with the node. @param InVertexName - The key for the graph output vertex. @param InNode - A shared pointer to an output node.
- L159 _public prototype_ `const INode* FindNode(const FGuid& InNodeID) const;` — Retrieve node by node ID. @param InNodeID - The NodeID of the requested Node. @return Pointer to the Node if it is stored on this graph. nullptr otherwise.
- L167 _public prototype_ `int32 FindUnconnectedNodes(TArray<TPair<FGuid, const INode*>>& OutUnconnectedNodes) const;` — Populates an array with all nodes which exist in the graph but do not have any connections. @param OutUnconnectedNodes - Array to populate. @return Number of unconnected nodes found.
- L176 _public prototype_ `bool RemoveNode(const FGuid& InNodeID, bool bInRemoveDataEdgesWithNode = true);` — Removes node from graph. @param InNodeID - ID of node to remove. @param bInRemoveDataEdgesWithNode - If true, will also call RemoveDataEdgesWithNode(...) @return true if node exists and is removed, false otherwise.
- L187 _public prototype_ `bool AddInputDataDestination(const INode& InNode, const FVertexName& InVertexName);` — Add an input data destination to describe how data provided outside this graph should be routed internally. @param InNode - Node which receives the data. @param InVertexName - Key for input vertex on InNode. @return True if the destination was successfully added. False otherwise.
- L193 _public prototype_ `void AddInputDataDestination(const FInputDataDestination& InDestination);` — Add an input data destination to describe how data provided outside this graph should be routed internally.
- L201 _public prototype_ `bool RemoveInputDataDestination(const FVertexName& InVertexName);` — Remove an input data destination by vertex name @param InVertexName - Name of vertex to remove. @return True if destination existed and was successfully removed. False otherwise.
- L212 _public prototype_ `bool AddOutputDataSource(const INode& InNode, const FVertexName& InVertexName);` — Add an output data source which describes routing of data which is owned this graph and exposed externally. @param InNode - Node which produces the data. @param InVertexName - Key for output vertex on InNode. @return True if the source was successfully added. False otherwise.
- L217 _public prototype_ `void AddOutputDataSource(const FOutputDataSource& InSource);` — Add an output data source which describes routing of data which is owned this graph and exposed externally.
- L225 _public prototype_ `bool RemoveOutputDataSource(const FVertexName& InVertexName);` — Remove an output data source by vertex name @param InVertexName - Name of vertex to remove. @return True if source existed and was successfully removed. False otherwise.
- L228 _public prototype_ `virtual FOperatorFactorySharedRef GetDefaultOperatorFactory() const override;` — Return a reference to the default operator factory.
- L233 _private prototype_ `INode* FindMutableNode(const FGuid& InNodeID);` — Non-const access to nodes should not be exposed publicly so that graph edges can be assured to be consistent.
- L243 _private member_ `FTopLevelAssetPath AssetPath;`
- L244 _private member_ `FVertexName InstanceName;`
- L245 _private member_ `FGuid InstanceID;`
- L247 _private member_ `FNodeClassMetadata Metadata;`
- L251 _private member_ `FVertexInterface GraphInterface;` — Mutable vertex interface used for graph input/output mutations. Initialized from Metadata.DefaultInterface
- L253 _private member_ `TSharedPtr<const IOperatorData> OperatorData;`
- L255 _private member_ `TArray<FDataEdge> Edges;`
- L284 _private member_ `TSortedMap<FGuid, FDeprecationNodeStorageAdapter> Nodes;`
- L286 _private member_ `FInputDataDestinationCollection InputDestinations;`
- L287 _private member_ `FOutputDataSourceCollection OutputSources;`

#### class `Metasound::FGraph::FFactory`  
`class FFactory : public IOperatorFactory`  
_L235-241_
- inherits: `IOperatorFactory`
- L238 _public prototype_ `virtual ~FFactory() = default;`
- L240 _public prototype_ `virtual TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults) override;`

#### struct `Metasound::FGraph::FDeprecationNodeStorageAdapter`  
`struct FDeprecationNodeStorageAdapter`  
_L261-282_
- desc: This struct is used to handle back-compatibility with the deprecated API. To support the old API, we still hold onto shared pointers of nodes in the graph. Once the deprecated API is removed, we can remove this struct and simply store unique ptrs.
- L263 _public prototype_ `FDeprecationNodeStorageAdapter() = default;`
- L265 _public function_ `FDeprecationNodeStorageAdapter(TUniquePtr<INode> InNode) : Storage(InNode.Get())`
- L271 _public function_ `FDeprecationNodeStorageAdapter(TSharedPtr<const INode> InNode) : Storage(MoveTemp(InNode))`
- L276 _public prototype_ `const INode* GetConstNode() const;`
- L277 _public prototype_ `INode* GetMutableNode() const;`
- L280 _private member_ `INode* MutableNode = nullptr;`
- L281 _private member_ `TSharedPtr<const INode> Storage;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L13 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundGraphAlgo.h` (Public)


#### struct `Metasound::DirectedGraphAlgo::FStronglyConnectedComponent`  
`struct FStronglyConnectedComponent`  
_L27-34_
- desc: A strongly connected component containing Metasound INodes and FDataEdges.
- L30 _public member_ `TArray<const INode*> Nodes;` — Nodes in the strongly connected component.
- L33 _public member_ `TArray<FDataEdge> Edges;` — FDataEdges in the strongly connected component.

#### struct `Metasound::FDirectedGraphAlgo`  
`struct FDirectedGraphAlgo`  
_L39-172_
- L47 _public prototype_ `static TPimplPtr<FDirectedGraphAlgoAdapter> CreateDirectedGraphAlgoAdapter(const IGraph& InGraph);` — The FDirectedGraphAlgoAdapter caches internal representations of the passed in IGraph. Using this can reduce redundant calcuations when multiple algorithms are run on the same IGraph (without altering the IGraph). This function creates the adapter.
- L58 _public prototype_ `static bool DepthFirstTopologicalSort(const IGraph& InGraph, TArray<const INode*>& OutNodeOrder);` — Sort the nodes of a directed acyclic graph using a depth-first topological sorting algorithm. @param InGraph      - The graph containing edges and nodes to sort. @param OutNodeOrder - An array of nodes from InGraph put in a valid topological sorted order. @return True if sorting was successful, false otherwise.
- L69 _public prototype_ `static bool DepthFirstTopologicalSort(const FDirectedGraphAlgoAdapter& InAdapter, TArray<const INode*>& OutNodeOrder);` — Sort the nodes of a directed acyclic graph using a depth-first topological sorting algorithm. @param InAdapter    - The adapter containing edges and nodes to sort. @param OutNodeOrder - An array of nodes from InGraph put in a valid topological sorted order. @return True if sorting was successful, false otherwise.
- L80 _public prototype_ `static bool KahnTopologicalSort(const IGraph& InGraph, TArray<const INode*>& OutNodeOrder);` — Sort the nodes of a directed acyclic graph using Kahn's topological sorting algorithm. @param InGraph      - The graph containing edges and nodes to sort. @param OutNodeOrder - An array of nodes from InGraph put in a valid topological sorted order. @return True if sorting was successful, false otherwise.
- L91 _public prototype_ `static bool KahnTopologicalSort(const FDirectedGraphAlgoAdapter& InAdapter, TArray<const INode*>& OutNodeOrder);` — Sort the nodes of a directed acyclic graph using Kahn's topological sorting algorithm. @param InAdapter    - The adapter containing edges and nodes to sort. @param OutNodeOrder - An array of nodes from InGraph put in a valid topological sorted order. @return True if sorting was successful, false otherwise.
- L106 _public prototype_ `static bool TarjanStronglyConnectedComponents(const IGraph& InGraph, TArray<DirectedGraphAlgo::FStronglyConnectedComponent>& OutComponents, bool bExcludeSingleVertex = true);` — Find strongly connected components given a Metasound IGraph. @param InGraph              - Graph to be analyzed. @param OutComponents        - Strongly connected components found in the graph are be added to this array. @param bExcludeSingleVertex - If true, single vertices are not be returned as strongly connected components. If false, single vertices may be returned as strongly connected components. @return True if one or more strongly connected components are added to OutComponents. False otherwise.
- L121 _public prototype_ `static bool TarjanStronglyConnectedComponents(const FDirectedGraphAlgoAdapter& InAdapter, TArray<DirectedGraphAlgo::FStronglyConnectedComponent>& OutComponents, bool bExcludeSingleVertex = true);` — Find strongly connected components given a Metasound IGraph. @param InAdapter            - The adapter containing edges and nodes to analyze. @param OutComponents        - Strongly connected components found in the graph are be added to this array. @param bExcludeSingleVertex - If true, single vertices are not be returned as strongly connected components. If false, single vertices may be returned as strongly connected components. @return True if one or more strongly connected components are added to OutComponents. False otherwise.
- L129 _public prototype_ `static void FindReachableNodesFromInput(const IGraph& InGraph, TSet<const INode*>& OutNodes);` — Finds all nodes which can be reached by traversing the graph beginning from FInputDataDestination nodes. @param InGraph  - The graph to be traversed. @param OutNodes - The nodes which were reached during traversal.
- L137 _public prototype_ `static void FindReachableNodesFromInput(const FDirectedGraphAlgoAdapter& InAdapter, TSet<const INode*>& OutNodes);` — Finds all nodes which can be reached by traversing the graph beginning from FInputDataDestination nodes. @param InAdapter - The adapter to be traversed. @param OutNodes  - The nodes which were reached during traversal.
- L145 _public prototype_ `static void FindReachableNodesFromOutput(const IGraph& InGraph, TSet<const INode*>& OutNodes);` — Finds all nodes which can be reached by traversing the transpose graph beginning from FOutputDataSource nodes. @param InGraph  - The graph to be traversed. @param OutNodes - The nodes which were reached during traversal.
- L153 _public prototype_ `static void FindReachableNodesFromOutput(const FDirectedGraphAlgoAdapter& InAdapter, TSet<const INode*>& OutNodes);` — Finds all nodes which can be reached by traversing the transpose graph beginning from FOutputDataSource nodes. @param InAdapter - The adapter to be traversed. @param OutNodes  - The nodes which were reached during traversal.
- L162 _public prototype_ `static void FindReachableNodes(const IGraph& InGraph, TSet<const INode*>& OutNodes);` — Finds all nodes which can be reached by traversing the graph beginning from FInputDataDestinations or by traversing the transpose graph beginning from FOutputDataSource nodes. @param InGraph  - The graph to be traversed. @param OutNodes - The nodes which were reached during traversal.
- L171 _public prototype_ `static void FindReachableNodes(const FDirectedGraphAlgoAdapter& InAdapter, TSet<const INode*>& OutNodes);` — Finds all nodes which can be reached by traversing the graph beginning from FInputDataDestinations or by traversing the transpose graph beginning from FOutputDataSource nodes. @param InAdapter - The adapter to be traversed. @param OutNodes  - The nodes which were reached during traversal.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L13 _namespace_ `namespace Metasound`
- L22 _namespace_ `namespace DirectedGraphAlgo` (scope `Metasound`)
- L37 _typedef_ `using FStronglyConnectedComponent UE_DEPRECATED(5.3, "Use the equivalent type declared in 'namespace Direc` (scope `Metasound`)
- L174 _namespace_ `namespace DirectedGraphAlgo` (scope `Metasound`)
- L182 _prototype_ `TPimplPtr<FDirectedGraphAlgoAdapter> CreateDirectedGraphAlgoAdapter(const IGraph& InGraph);` (scope `Metasound::DirectedGraphAlgo`) — The FDirectedGraphAlgoAdapter caches internal representations of the passed in IGraph. Using this can reduce redundant calcuations when multiple algorithms are run on the same IGraph (without altering the IGraph). This function creates the adapter.
- L193 _prototype_ `bool DepthFirstTopologicalSort(const IGraph& InGraph, TArray<const INode*>& OutNodeOrder);` (scope `Metasound::DirectedGraphAlgo`) — Sort the nodes of a directed acyclic graph using a depth-first topological sorting algorithm. @param InGraph      - The graph containing edges and nodes to sort. @param OutNodeOrder - An array of nodes from InGraph put in a valid topological sorted order. @return True if sorting was successful, false otherwise.
- L204 _prototype_ `bool DepthFirstTopologicalSort(const FDirectedGraphAlgoAdapter& InAdapter, TArray<const INode*>& OutNodeOrder);` (scope `Metasound::DirectedGraphAlgo`) — Sort the nodes of a directed acyclic graph using a depth-first topological sorting algorithm. @param InAdapter    - The adapter containing edges and nodes to sort. @param OutNodeOrder - An array of nodes from InGraph put in a valid topological sorted order. @return True if sorting was successful, false otherwise.
- L215 _prototype_ `bool KahnTopologicalSort(const IGraph& InGraph, TArray<const INode*>& OutNodeOrder);` (scope `Metasound::DirectedGraphAlgo`) — Sort the nodes of a directed acyclic graph using Kahn's topological sorting algorithm. @param InGraph      - The graph containing edges and nodes to sort. @param OutNodeOrder - An array of nodes from InGraph put in a valid topological sorted order. @return True if sorting was successful, false otherwise.
- L226 _prototype_ `bool KahnTopologicalSort(const FDirectedGraphAlgoAdapter& InAdapter, TArray<const INode*>& OutNodeOrder);` (scope `Metasound::DirectedGraphAlgo`) — Sort the nodes of a directed acyclic graph using Kahn's topological sorting algorithm. @param InAdapter    - The adapter containing edges and nodes to sort. @param OutNodeOrder - An array of nodes from InGraph put in a valid topological sorted order. @return True if sorting was successful, false otherwise.
- L241 _prototype_ `bool TarjanStronglyConnectedComponents(const IGraph& InGraph, TArray<FStronglyConnectedComponent>& OutComponents, bool bExcludeSingleVertex = true);` (scope `Metasound::DirectedGraphAlgo`) — Find strongly connected components given a Metasound IGraph. @param InGraph              - Graph to be analyzed. @param OutComponents        - Strongly connected components found in the graph are be added to this array. @param bExcludeSingleVertex - If true, single vertices are not be returned as strongly connected components. If false, single vertices may be returned as strongly connected components. @return True if one or more strongly connected components are added to OutComponents. False otherwise.
- L256 _prototype_ `bool TarjanStronglyConnectedComponents(const FDirectedGraphAlgoAdapter& InAdapter, TArray<FStronglyConnectedComponent>& OutComponents, bool bExcludeSingleVertex = true);` (scope `Metasound::DirectedGraphAlgo`) — Find strongly connected components given a Metasound IGraph. @param InAdapter            - The adapter containing edges and nodes to analyze. @param OutComponents        - Strongly connected components found in the graph are be added to this array. @param bExcludeSingleVertex - If true, single vertices are not be returned as strongly connected components. If false, single vertices may be returned as strongly connected components. @return True if one or more strongly connected components are added to OutComponents. False otherwise.
- L264 _prototype_ `void FindReachableNodesFromInput(const IGraph& InGraph, TSet<const INode*>& OutNodes);` (scope `Metasound::DirectedGraphAlgo`) — Finds all nodes which can be reached by traversing the graph beginning from FInputDataDestination nodes. @param InGraph  - The graph to be traversed. @param OutNodes - The nodes which were reached during traversal.
- L272 _prototype_ `void FindReachableNodesFromInput(const FDirectedGraphAlgoAdapter& InAdapter, TSet<const INode*>& OutNodes);` (scope `Metasound::DirectedGraphAlgo`) — Finds all nodes which can be reached by traversing the graph beginning from FInputDataDestination nodes. @param InAdapter - The adapter to be traversed. @param OutNodes  - The nodes which were reached during traversal.
- L280 _prototype_ `void FindReachableNodesFromOutput(const IGraph& InGraph, TSet<const INode*>& OutNodes);` (scope `Metasound::DirectedGraphAlgo`) — Finds all nodes which can be reached by traversing the transpose graph beginning from FOutputDataSource nodes. @param InGraph  - The graph to be traversed. @param OutNodes - The nodes which were reached during traversal.
- L288 _prototype_ `void FindReachableNodesFromOutput(const FDirectedGraphAlgoAdapter& InAdapter, TSet<const INode*>& OutNodes);` (scope `Metasound::DirectedGraphAlgo`) — Finds all nodes which can be reached by traversing the transpose graph beginning from FOutputDataSource nodes. @param InAdapter - The adapter to be traversed. @param OutNodes  - The nodes which were reached during traversal.
- L297 _prototype_ `void FindReachableNodes(const IGraph& InGraph, TSet<const INode*>& OutNodes);` (scope `Metasound::DirectedGraphAlgo`) — Finds all nodes which can be reached by traversing the graph beginning from FInputDataDestinations or by traversing the transpose graph beginning from FOutputDataSource nodes. @param InGraph  - The graph to be traversed. @param OutNodes - The nodes which were reached during traversal.
- L306 _prototype_ `void FindReachableNodes(const FDirectedGraphAlgoAdapter& InAdapter, TSet<const INode*>& OutNodes);` (scope `Metasound::DirectedGraphAlgo`) — Finds all nodes which can be reached by traversing the graph beginning from FInputDataDestinations or by traversing the transpose graph beginning from FOutputDataSource nodes. @param InAdapter - The adapter to be traversed. @param OutNodes  - The nodes which were reached during traversal.

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundGraphCoreModule.h` (Public)


#### class `Metasound::IMetasoundGraphCoreModule`  
`class IMetasoundGraphCoreModule : public IModuleInterface`  
_L10-12_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundGraphLinter.h` (Public)


#### class `Metasound::FGraphLinter`  
`class FGraphLinter`  
_L21-84_
- desc: FGraphLinter Functions for detecting issues and errors in an IGraph.
- L24 _public typedef_ `using FBuildErrorPtr = TUniquePtr<IOperatorBuildError>;`
- L37 _public prototype_ `static bool ValidateEdgeDataTypesMatch(const IGraph& InGraph, TArray<FBuildErrorPtr>& OutErrors);` — Validate each FDataEdge in the IGraph by checking that the FInputDataSource and FOutputDataDestination data types are equal. Errors will be generated if unequal data types are detected. @param InGraph - Graph to analyze. @param OutErrors - Array to hold detected errors. @return True if no errors detected. False otherwise.
- L49 _public prototype_ `static bool ValidateVerticesExist(const IGraph& InGraph, TArray<FBuildErrorPtr>& OutErrors);` — Validate each FDataEdge in the IGraph by checking that the corresponding INodes contain matching FDataVertex information as described by the FDataEdge. Errors will be generated if inconsistencies are detected. @param InGraph - Graph to analyze. @param OutErrors - Array to hold detected errors. @return True if no errors detected. False otherwise.
- L61 _public prototype_ `static bool ValidateNoDuplicateInputs(const IGraph& InGraph, TArray<FBuildErrorPtr>& OutErrors);` — Validate the IGraph by checking for duplicate inputs connected to an individual vertex on a given node. Errors will be generated if duplicates are detected. @param InGraph - Graph to analyze. @param OutErrors - Array to hold detected errors. @return True if no errors detected. False otherwise.
- L72 _public prototype_ `static bool ValidateNoCyclesInGraph(const IGraph& InGraph, TArray<FBuildErrorPtr>& OutErrors);` — Validate the IGraph by checking for cycles. Errors will be generated if a cycle is detected in the graph. @param InGraph - Graph to analyze. @param OutErrors - Array to hold detected errors. @return True if no errors detected. False otherwise.
- L83 _public prototype_ `static bool ValidateNoCyclesInGraph(const FDirectedGraphAlgoAdapter& InAdapter, TArray<FBuildErrorPtr>& OutErrors);` — Validate the IGraph by checking for cycles. Errors will be generated if a cycle is detected in the graph. @param InAdapter - Graph adapter to analyze. @param OutErrors - Array to hold detected errors. @return True if no errors detected. False otherwise.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L12 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundGraphOperator.h` (Public)


#### class `Metasound::FGraphOperator`  
`class FGraphOperator : public TExecutableOperator<FGraphOperator>`  
_L23-92_
- inherits: `TExecutableOperator<FGraphOperator>`
- L26 _public typedef_ `using FOperatorPtr = TUniquePtr<IOperator>;`
- L27 _public typedef_ `using FExecuteFunction = IOperator::FExecuteFunction;`
- L28 _public typedef_ `using FResetFunction = IOperator::FResetFunction;`
- L29 _public typedef_ `using FResetParams = IOperator::FResetParams;`
- L31 _public prototype_ `FGraphOperator() = default;`
- L32 _public prototype_ `FGraphOperator(TUniquePtr<DirectedGraphAlgo::FStaticGraphOperatorData> InOperatorData);`
- L34 _public prototype_ `virtual ~FGraphOperator() = default;`
- L37 _public prototype_ `void AppendOperator(FOperatorPtr InOperator);` — Add an operator to the end of the executation stack.
- L41 _public prototype_ `void SetVertexInterfaceData(FVertexInterfaceData&& InVertexData);` — Set the vertex interface data. This data will be copied to output during calls to Bind(InOutVertexData).
- L44 _public prototype_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override;` — Bind the graph's interface data references to FVertexInterfaceData.
- L45 _public prototype_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override;`
- L47 _public prototype_ `virtual IOperator::FPostExecuteFunction GetPostExecuteFunction() override;`
- L49 _public prototype_ `void Execute();`
- L50 _public prototype_ `void PostExecute();`
- L51 _public prototype_ `void Reset(const FResetParams& InParams);`
- L55 _private prototype_ `FGraphOperator& operator=(const FGraphOperator&) = delete;` — Delete copy operator because underlying types cannot be copied.
- L56 _private prototype_ `FGraphOperator(const FGraphOperator&) = delete;`
- L58 _private prototype_ `static void StaticPostExecute(IOperator* Operator);`
- L87 _private member_ `TArray<FExecuteEntry> ExecuteStack;`
- L88 _private member_ `TArray<FPostExecuteEntry> PostExecuteStack;`
- L89 _private member_ `TArray<FResetEntry> ResetStack;`
- L90 _private member_ `TArray<TUniquePtr<IOperator>> ActiveOperators;`
- L91 _private member_ `FVertexInterfaceData VertexData;`

#### struct `Metasound::FGraphOperator::FExecuteEntry`  
`struct FExecuteEntry`  
_L60-67_
- L62 _public prototype_ `FExecuteEntry(IOperator& InOperator, FExecuteFunction InFunc);`
- L63 _public prototype_ `void Execute();`
- L65 _public member_ `IOperator* Operator;`
- L66 _public member_ `FExecuteFunction Function;`

#### struct `Metasound::FGraphOperator::FPostExecuteEntry`  
`struct FPostExecuteEntry`  
_L69-76_
- L71 _public prototype_ `FPostExecuteEntry(IOperator& InOperator, FPostExecuteFunction InFunc);`
- L72 _public prototype_ `void PostExecute();`
- L74 _public member_ `IOperator* Operator;`
- L75 _public member_ `FPostExecuteFunction Function;`

#### struct `Metasound::FGraphOperator::FResetEntry`  
`struct FResetEntry`  
_L78-85_
- L80 _public prototype_ `FResetEntry(IOperator& InOperator, FResetFunction InFunc);`
- L81 _public prototype_ `void Reset(const FResetParams& InParams);`
- L83 _public member_ `IOperator* Operator;`
- L84 _public member_ `FResetFunction Function;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L15 _namespace_ `namespace Metasound`
- L18 _namespace_ `namespace DirectedGraphAlgo` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundLiteral.h` (Public)


#### enum `Metasound::ELiteralType`  
`enum class ELiteralType : uint8`  
_L23-40_
- desc: ELiteralType describes the format of the values held in the literal.
- L25 _public enumerator_ `None` — If the literal is None, TType(const FOperatorSettings&) or TType() will be invoked.
- L26 _public enumerator_ `Boolean`
- L27 _public enumerator_ `Integer`
- L28 _public enumerator_ `Float`
- L29 _public enumerator_ `String`
- L30 _public enumerator_ `UObjectProxy`
- L31 _public enumerator_ `NoneArray` — For NoneArray types,  TType(const FOperatorSettings&) or TType() will be invoked for each element in the array.
- L32 _public enumerator_ `BooleanArray`
- L33 _public enumerator_ `IntegerArray`
- L34 _public enumerator_ `FloatArray`
- L35 _public enumerator_ `StringArray`
- L36 _public enumerator_ `UObjectProxyArray`
- L37 _public enumerator_ `Invalid` — The literal is in an invalid state and cannot be used to construct an object.
- L39 _public enumerator_ `COUNT`

#### struct `Metasound::FLiteral`  
`struct FLiteral`  
_L70-162_
- desc: FLiteral represents a constant value in a Metasound graph and is primarily used to invoke the correct constructor of a Metasound data type. To be constructed using a FLiteral, the Metasound data type must support a constructor which accepts one of the types supported by a FLiteral. The Metasound data type may optionally accept a `const FOperatorSettings&` in addition. Example: // Somewhere before DECLARE_METASOUND_DATA_REFERENCE_TYPES(FAudioBuffer...), ParseFrom<FAudioBuffer>(int32) is defined // which means this data type can be created from an integer. Metasound::FAudioBuffer ::Metasound::ParseFrom<Metasound::FAudioBuffer>(int32 InNumFrames, const ::Metasound::FOperatorSettings&) { return Metasound::FAudioBuffer(InNumFrames); } //... // In the frontend, we know that int and pass it to somewhere in MetasoundGraphCore... FLiteral InitParam(512); //... // In the backend, we can safely construct an FAudioBuffer. if(InitParam.IsCompatibleWithType<Metasound::FAudioBuffer>()) { Metasound::FAudioBuffer AudioBuffer = InitParam.ParseTo<Metasound::FAudioBuffer>(); //... }
- L85 _public typedef_ `using FVariantType = TVariant< FNone, bool, int32, float, FString, TSharedPtr<Audio::IProxyData>,`
- L97 _public function_ `FLiteral(ArgType&& Arg)`
- L106 _public function_ `FLiteral()` — Construct a literal param with no arguments.
- L114 _public member_ `FVariantType Value;`
- L117 _public prototype_ `static FLiteral CreateInvalid();` — builds an invalid FLiteral.
- L118 _public prototype_ `static FLiteral GetDefaultForType(ELiteralType InType);`
- L120 _public prototype_ `bool IsValid() const;`
- L122 _public prototype_ `ELiteralType GetType() const;`
- L125 _public function_ `template<typename ArgType> void Set(ArgType&& Arg)`
- L136 _private member_ `FString DebugString;`
- L138 _private prototype_ `void InitDebugString() const;`

#### struct `Metasound::FLiteral::FInvalid`  
`struct FInvalid`  
_L77-77_

#### struct `Metasound::FLiteral::FNone`  
`struct FNone`  
_L83-83_
- desc: FNone is used in scenarios where an object is constructed with an FLiteral where the expected object constructor is the default constructor, or a constructor which accepts an FOperatorSettings.

#### struct `Metasound::FLiteral::TIsSupportedLiteralTypeHelper`  
`template<typename U, typename ... Ts> struct TIsSupportedLiteralTypeHelper`  
_L144-147_
- desc: Helper function to determine if type "U" can be stored in this FLiteral.
- L146 _public member_ `static constexpr bool Value = UE::Core::Private::TParameterPackTypeIndex<U, Ts...>::Value != (SIZE_T)-1;`
- L153 _public member_ `static constexpr bool Value = TIsSupportedLiteralTypeHelper<U, T, Ts...>::Value;`

#### struct `Metasound::FLiteral::TIsSupportedLiteralTypeHelper`  
`template<typename U, typename T, typename ... Ts> struct TIsSupportedLiteralTypeHelper<U, TVariant<T, Ts...>>`  
_L151-154_
- desc: Helper function to determine if type "U" can be stored in this FLiteral.
- L146 _public member_ `static constexpr bool Value = UE::Core::Private::TParameterPackTypeIndex<U, Ts...>::Value != (SIZE_T)-1;`
- L153 _public member_ `static constexpr bool Value = TIsSupportedLiteralTypeHelper<U, T, Ts...>::Value;`

#### struct `Metasound::FLiteral::TIsSupportedLiteralType`  
`template<typename U> struct TIsSupportedLiteralType`  
_L158-161_
- desc: Determine if type "U" can be stored in this FLiteral.
- L160 _public member_ `static constexpr bool Value = TIsSupportedLiteralTypeHelper<typename std::decay<U>::type, FVariantType>::Value;`

#### struct `Metasound::MetasoundLiteralIntrinsics::TLiteralDefaultValueFromDecayed`  
`template<typename ... ArgTypes> struct TLiteralDefaultValueFromDecayed`  
_L247-247_
- L252 _public function_ `static const ArgType& GetValue()`
- L262 _public function_ `static FLiteral::FNone GetValue()`
- L271 _public function_ `static const FString& GetValue()`
- L281 _public function_ `static const TArray<ElementType>& GetValue()`
- L291 _public function_ `static TSharedPtr<Audio::IProxyData> GetValue()`
- L300 _public function_ `static TArray<TSharedPtr<Audio::IProxyData>> GetValue()`

#### struct `Metasound::MetasoundLiteralIntrinsics::TLiteralDefaultValueFromDecayed`  
`template<typename ArgType> struct TLiteralDefaultValueFromDecayed<ArgType>`  
_L250-257_
- L252 _public function_ `static const ArgType& GetValue()`
- L262 _public function_ `static FLiteral::FNone GetValue()`
- L271 _public function_ `static const FString& GetValue()`
- L281 _public function_ `static const TArray<ElementType>& GetValue()`
- L291 _public function_ `static TSharedPtr<Audio::IProxyData> GetValue()`
- L300 _public function_ `static TArray<TSharedPtr<Audio::IProxyData>> GetValue()`

#### struct `Metasound::MetasoundLiteralIntrinsics::TLiteralDefaultValueFromDecayed`  
`template<> struct TLiteralDefaultValueFromDecayed<FLiteral::FNone>`  
_L260-266_
- L252 _public function_ `static const ArgType& GetValue()`
- L262 _public function_ `static FLiteral::FNone GetValue()`
- L271 _public function_ `static const FString& GetValue()`
- L281 _public function_ `static const TArray<ElementType>& GetValue()`
- L291 _public function_ `static TSharedPtr<Audio::IProxyData> GetValue()`
- L300 _public function_ `static TArray<TSharedPtr<Audio::IProxyData>> GetValue()`

#### struct `Metasound::MetasoundLiteralIntrinsics::TLiteralDefaultValueFromDecayed`  
`template<> struct TLiteralDefaultValueFromDecayed<FString>`  
_L269-276_
- L252 _public function_ `static const ArgType& GetValue()`
- L262 _public function_ `static FLiteral::FNone GetValue()`
- L271 _public function_ `static const FString& GetValue()`
- L281 _public function_ `static const TArray<ElementType>& GetValue()`
- L291 _public function_ `static TSharedPtr<Audio::IProxyData> GetValue()`
- L300 _public function_ `static TArray<TSharedPtr<Audio::IProxyData>> GetValue()`

#### struct `Metasound::MetasoundLiteralIntrinsics::TLiteralDefaultValueFromDecayed`  
`template<typename ElementType> struct TLiteralDefaultValueFromDecayed<TArray<ElementType>>`  
_L279-286_
- L252 _public function_ `static const ArgType& GetValue()`
- L262 _public function_ `static FLiteral::FNone GetValue()`
- L271 _public function_ `static const FString& GetValue()`
- L281 _public function_ `static const TArray<ElementType>& GetValue()`
- L291 _public function_ `static TSharedPtr<Audio::IProxyData> GetValue()`
- L300 _public function_ `static TArray<TSharedPtr<Audio::IProxyData>> GetValue()`

#### struct `Metasound::MetasoundLiteralIntrinsics::TLiteralDefaultValueFromDecayed`  
`template<> struct TLiteralDefaultValueFromDecayed<TSharedPtr<Audio::IProxyData>>`  
_L289-295_
- L252 _public function_ `static const ArgType& GetValue()`
- L262 _public function_ `static FLiteral::FNone GetValue()`
- L271 _public function_ `static const FString& GetValue()`
- L281 _public function_ `static const TArray<ElementType>& GetValue()`
- L291 _public function_ `static TSharedPtr<Audio::IProxyData> GetValue()`
- L300 _public function_ `static TArray<TSharedPtr<Audio::IProxyData>> GetValue()`

#### struct `Metasound::MetasoundLiteralIntrinsics::TLiteralDefaultValueFromDecayed`  
`template<> struct TLiteralDefaultValueFromDecayed<TArray<TSharedPtr<Audio::IProxyData>>>`  
_L298-304_
- L252 _public function_ `static const ArgType& GetValue()`
- L262 _public function_ `static FLiteral::FNone GetValue()`
- L271 _public function_ `static const FString& GetValue()`
- L281 _public function_ `static const TArray<ElementType>& GetValue()`
- L291 _public function_ `static TSharedPtr<Audio::IProxyData> GetValue()`
- L300 _public function_ `static TArray<TSharedPtr<Audio::IProxyData>> GetValue()`

#### struct `Metasound::TLiteralTypeInfo`  
`template<typename... ArgTypes> struct TLiteralTypeInfo`  
_L313-313_
- desc: Provides literal type information for a given type. @tparam ArgType - A C++ type.
- L318 _public typedef_ `using FDecayedType = typename std::decay<ArgType>::type;`
- L320 _public function_ `static const ELiteralType GetLiteralArgTypeEnum()` — Returns the associated ELiteralType for the C++ type provided in the TLiteralTypeInfo<Type>
- L326 _public function_ `static auto GetDefaultValue()`
- L346 _public function_ `static FLiteral::FNone GetDefaultValue()`

#### struct `Metasound::TLiteralTypeInfo`  
`template<typename ArgType> struct TLiteralTypeInfo<ArgType>`  
_L316-330_
- L318 _public typedef_ `using FDecayedType = typename std::decay<ArgType>::type;`
- L320 _public function_ `static const ELiteralType GetLiteralArgTypeEnum()` — Returns the associated ELiteralType for the C++ type provided in the TLiteralTypeInfo<Type>
- L326 _public function_ `static auto GetDefaultValue()`
- L346 _public function_ `static FLiteral::FNone GetDefaultValue()`

#### struct `Metasound::TLiteralTypeInfo`  
`template<> struct TLiteralTypeInfo<>`  
_L337-350_
- desc: Provides literal type information for a given type. @tparam ArgType - A C++ type.
- L318 _public typedef_ `using FDecayedType = typename std::decay<ArgType>::type;`
- L320 _public function_ `static const ELiteralType GetLiteralArgTypeEnum()` — Returns the associated ELiteralType for the C++ type provided in the TLiteralTypeInfo<Type>
- L326 _public function_ `static auto GetDefaultValue()`
- L346 _public function_ `static FLiteral::FNone GetDefaultValue()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L13 _macro_ `#define METASOUND_DEBUG_LITERALS 0`
- L20 _namespace_ `namespace Metasound`
- L164 _namespace_ `namespace MetasoundLiteralIntrinsics` (scope `Metasound`)
- L168 _function_ `template<typename... ArgTypes> ELiteralType GetLiteralArgTypeFromDecayed()` (scope `Metasound::MetasoundLiteralIntrinsics`) — Default template for converting a template parameter to a literal argument type
- L174 _function_ `template<> inline ELiteralType GetLiteralArgTypeFromDecayed<>()` (scope `Metasound::MetasoundLiteralIntrinsics`)
- L181 _function_ `template<> inline ELiteralType GetLiteralArgTypeFromDecayed<bool>()` (scope `Metasound::MetasoundLiteralIntrinsics`)
- L187 _function_ `template<> inline ELiteralType GetLiteralArgTypeFromDecayed<int32>()` (scope `Metasound::MetasoundLiteralIntrinsics`)
- L193 _function_ `template<> inline ELiteralType GetLiteralArgTypeFromDecayed<float>()` (scope `Metasound::MetasoundLiteralIntrinsics`)
- L199 _function_ `template<> inline ELiteralType GetLiteralArgTypeFromDecayed<FString>()` (scope `Metasound::MetasoundLiteralIntrinsics`)
- L205 _function_ `template<> inline ELiteralType GetLiteralArgTypeFromDecayed<TSharedPtr<Audio::IProxyData>>()` (scope `Metasound::MetasoundLiteralIntrinsics`)
- L211 _function_ `template<> inline ELiteralType GetLiteralArgTypeFromDecayed<TArray<FLiteral::FNone>>()` (scope `Metasound::MetasoundLiteralIntrinsics`)
- L217 _function_ `template<> inline ELiteralType GetLiteralArgTypeFromDecayed<TArray<bool>>()` (scope `Metasound::MetasoundLiteralIntrinsics`)
- L223 _function_ `template<> inline ELiteralType GetLiteralArgTypeFromDecayed<TArray<int32>>()` (scope `Metasound::MetasoundLiteralIntrinsics`)
- L229 _function_ `template<> inline ELiteralType GetLiteralArgTypeFromDecayed<TArray<float>>()` (scope `Metasound::MetasoundLiteralIntrinsics`)
- L235 _function_ `template<> inline ELiteralType GetLiteralArgTypeFromDecayed<TArray<FString>>()` (scope `Metasound::MetasoundLiteralIntrinsics`)
- L241 _function_ `template<> inline ELiteralType GetLiteralArgTypeFromDecayed<TArray<TSharedPtr<Audio::IProxyData>>>()` (scope `Metasound::MetasoundLiteralIntrinsics`)
- L353 _prototype_ `FString LexToString(const Metasound::FLiteral& InLiteral);`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaSound, Log, All);`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundNode.h` (Public)


#### class `Metasound::FNode`  
`class FNode : public INode`  
_L16-48_
- inherits: `INode`
- L19 _public prototype_ `FNode(const FVertexName& InInstanceName, const FGuid& InInstanceID, const FNodeClassMetadata& InInfo, TSharedPtr<const IOperatorData> InOperatorData={});`
- L21 _public prototype_ `virtual ~FNode() = default;`
- L24 _public prototype_ `virtual const FVertexName& GetInstanceName() const override;` — Return the name of this specific instance of the node class.
- L27 _public prototype_ `virtual const FGuid& GetInstanceID() const override;` — Return the ID of this specific instance of the node class.
- L30 _public prototype_ `virtual const FNodeClassMetadata& GetMetadata() const override;` — Return metadata associated with this node.
- L32 _public prototype_ `virtual const FVertexInterface& GetVertexInterface() const override;`
- L34 _public prototype_ `virtual void SetDefaultInput(const FVertexName& InVertexName, const FLiteral& InLiteral) override;`
- L36 _public prototype_ `virtual TSharedPtr<const IOperatorData> GetOperatorData() const override;`
- L39 _private member_ `FVertexName InstanceName;`
- L40 _private member_ `FGuid InstanceID;`
- L41 _private member_ `FNodeClassMetadata Info;`
- L45 _private member_ `FVertexInterface VertexInterface;` — Mutable vertex interface for SetDefaultInput. Initialized from Info.DefaultInterface (implicit conversion from FClassInterface).
- L47 _private member_ `TSharedPtr<const IOperatorData> OperatorData;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L12 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundNodeInterface.h` (Public)


#### struct `Metasound::FNodeData`  
`struct FNodeData`  
_L39-51_
- desc: Data used to construct a Node.
- L41 _public prototype_ `FNodeData();`
- L42 _public prototype_ `FNodeData(const FNodeData&);`
- L43 _public prototype_ `FNodeData(const FName& InName, const FGuid& InID, FVertexInterface InInterface);`
- L44 _public prototype_ `FNodeData(const FName& InName, const FGuid& InID, FVertexInterface InInterface, TSharedPtr<const IOperatorData> InOperatorData);`
- L45 _public prototype_ `~FNodeData();`
- L47 _public member_ `FName Name;`
- L48 _public member_ `FGuid ID;`
- L49 _public member_ `FVertexInterface Interface;`
- L50 _public member_ `TSharedPtr<const IOperatorData> OperatorData;`

#### struct `Metasound::FNodeDisplayStyle`  
`struct FNodeDisplayStyle`  
_L56-81_
- desc: Node style data
- L59 _public member_ `FName ImageName;` — Icon name identifier associated with node.
- L62 _public member_ `bool bShowName = true;` — Whether or not to show name in visual layout.
- L65 _public member_ `bool bShowInputNames = true;` — Whether or not to show input names in visual layout.
- L68 _public member_ `bool bShowOutputNames = true;` — Whether or not to show output names in visual layout.
- L71 _public member_ `bool bShowLiterals = true;` — Whether or not to show input literals in visual layout.
- L74 _public member_ `FName StyleSet;` — Name of the Slate style associated with node (color, icon).
- L77 _public member_ `FName Icon;` — Name of the node's icon defined in Style.
- L80 _public member_ `FName Color;` — Name of the color defined in Style.

#### class `Metasound::FNodeClassName`  
`class FNodeClassName`  
_L93-134_
- desc: Name of a node class. FNodeClassName is used for lookup and declaring interoperability. Namespaces are provided as a convenience to avoid name collisions. Nodes with equal Namespace and Name, but different Variants are considered to be interoperable. They can be used to define nodes that perform the same function, but have differing vertex types.
- L96 _public prototype_ `FNodeClassName();`
- L98 _public prototype_ `FNodeClassName(const FName& InNamespace, const FName& InName, const FName& InVariant);`
- L101 _public prototype_ `const FName& GetNamespace() const;` — Namespace of node class.
- L104 _public prototype_ `const FName& GetName() const;` — Name of node class.
- L107 _public prototype_ `const FName& GetVariant() const;` — Variant of node class.
- L110 _public prototype_ `const FString ToString() const;` — The full name of the Node formatted Namespace.Name and optionally appended with .Variant if valid
- L113 _public prototype_ `bool IsValid() const;` — Whether or not this instance of a node class name is a valid name.
- L115 _public prototype_ `static FName FormatFullName(const FName& InNamespace, const FName& InName, const FName& InVariant);`
- L116 _public prototype_ `static FName FormatScopedName(const FName& InNamespace, const FName& InName);`
- L118 _public prototype_ `static void FormatFullName(FNameBuilder& InBuilder, const FName& InNamespace, const FName& InName, const FName& InVariant);`
- L119 _public prototype_ `static void FormatScopedName(FNameBuilder& InBuilder, const FName& InNamespace, const FName& InName);`
- L122 _public member_ `static const FNodeClassName InvalidNodeClassName;` — Invalid form of node class name (i.e. empty namespace, name, and variant)
- L131 _private member_ `FName Namespace;`
- L132 _private member_ `FName Name;`
- L133 _private member_ `FName Variant;`

#### enum `Metasound::ENodeClassAccessFlags`  
`enum class ENodeClassAccessFlags : uint16`  
_L136-147_
- L138 _public enumerator_ `None = 0`
- L141 _public enumerator_ `Deprecated = 1 << 0` — Node class is deprecated and should not be used in new MetaSounds.
- L144 _public enumerator_ `Referenceable = 1 << 1` — Node class can be referenced by MetaSound graphs
- L146 _public enumerator_ `Default = Referenceable`

#### struct `Metasound::FNodeClassMetadata`  
`struct FNodeClassMetadata`  
_L150-214_
- desc: Provides metadata for a given node.
- L152 _public prototype_ `FNodeClassMetadata();`
- L153 _public prototype_ `FNodeClassMetadata(const FNodeClassMetadata& InOther);`
- L154 _public prototype_ `FNodeClassMetadata( FNodeClassName InClassName, int32 InMajorVersion, int32 InMinorVersion, FText InDisplayName = { }, FText InDescription = { }, FString InAuthor = { }, FText InPromptIfMissing = { }, FClassInterface InDefaultInterface = { }, TArray<FText> InCategoryHierarchy = { }, TArray<FText> InKeywords = { }, FNodeDisplayStyle InDisplayStyle = { });`
- L167 _public prototype_ `~FNodeClassMetadata();`
- L169 _public prototype_ `FNodeClassMetadata& operator=(const FNodeClassMetadata& InOther);`
- L170 _public prototype_ `FNodeClassMetadata& operator=(FNodeClassMetadata&& InOther);`
- L173 _public prototype_ `static const FNodeClassMetadata& GetEmpty();` — Returns an empty FNodeClassMetadata object.
- L176 _public member_ `FNodeClassName ClassName;` — Name of class. Used for registration and lookup.
- L179 _public member_ `int32 MajorVersion;` — Major version of node. Used for registration and lookup.
- L182 _public member_ `int32 MinorVersion;` — Minor version of node.
- L185 _public member_ `FText DisplayName;` — Display name of node class.
- L188 _public member_ `FText Description;` — Human readable description of node.
- L191 _public member_ `FString Author;` — Author information.
- L194 _public member_ `FText PromptIfMissing;` — Human readable prompt for acquiring plugin in case node is not loaded.
- L197 _public member_ `FClassInterface DefaultInterface;` — Default class interface for the node.
- L200 _public member_ `TArray<FText> CategoryHierarchy;` — Hierarchy of categories for displaying node.
- L203 _public member_ `TArray<FText> Keywords;` — List of keywords for contextual node searching.
- L206 _public member_ `FNodeDisplayStyle DisplayStyle;` — Display style for node when visualized.
- L208 _public member_ `ENodeClassAccessFlags AccessFlags;`
- L212 _public member_ `bool bDeprecated;` — `UE_DEPRECATED(5.7, "Use AccessFlags instead")`

#### class `Metasound::INodeBase`  
`class INodeBase`  
_L220-253_
- desc: INodeBase Interface for all nodes that can describe their name, type, inputs and outputs.
- L223 _public prototype_ `virtual ~INodeBase() = default;`
- L226 _public prototype_ `virtual const FName& GetInstanceName() const = 0;` — Return the name of this specific instance of the node class.
- L229 _public prototype_ `virtual const FGuid& GetInstanceID() const = 0;` — Return the ID of this node instance.
- L232 _public prototype_ `virtual const FNodeClassMetadata& GetMetadata() const = 0;` — Return the type name of this node.
- L235 _public prototype_ `virtual const FVertexInterface& GetVertexInterface() const = 0;` — Return the current vertex interface.
- L240 _public prototype_ `virtual void SetDefaultInput(const FVertexName& InVertexName, const FLiteral& InLiteral) = 0;`
- L242 _public prototype_ `virtual void SetDefaultInput(const FVertexName& InVertexName, const FLiteral& InLiteral);`

#### class `Metasound::INode`  
`class INode : public INodeBase`  
_L272-279_
- inherits: `INodeBase`
- desc: INode Interface for all nodes that can create operators.
- L275 _public prototype_ `virtual ~INode() = default;`
- L278 _public prototype_ `virtual FOperatorFactorySharedRef GetDefaultOperatorFactory() const = 0;` — Return a reference to the default operator factory.

#### struct `Metasound::FOutputDataSource`  
`struct FOutputDataSource`  
_L284-307_
- desc: FOutputDataSource describes the source of data which is produced within a graph and exposed external to the graph.
- L287 _public member_ `const INode* Node = nullptr;` — Node containing the output data vertex.
- L290 _public member_ `FOutputDataVertex Vertex;` — Output data vertex.
- L292 _public function_ `FOutputDataSource()`
- L296 _public function_ `FOutputDataSource(const INode& InNode, const FOutputDataVertex& InVertex) : Node(&InNode) , Vertex(InVertex)`

#### struct `Metasound::FInputDataDestination`  
`struct FInputDataDestination`  
_L312-334_
- desc: FInputDataSource describes the destination of data which produced external to the graph and read internal to the graph.
- L315 _public member_ `const INode* Node = nullptr;` — Node containing the input data vertex.
- L318 _public member_ `FInputDataVertex Vertex;` — Input data vertex of edge.
- L320 _public function_ `FInputDataDestination()`
- L324 _public function_ `FInputDataDestination(const INode& InNode, const FInputDataVertex& InVertex) : Node(&InNode) , Vertex(InVertex)`

#### struct `Metasound::FDataEdge`  
`struct FDataEdge`  
_L364-384_
- desc: FDataEdge An edge describes a connection between two Nodes.
- L366 _public member_ `FOutputDataSource From;`
- L368 _public member_ `FInputDataDestination To;`
- L370 _public function_ `FDataEdge()`
- L374 _public function_ `FDataEdge(const FOutputDataSource& InFrom, const FInputDataDestination& InTo) : From(InFrom) , To(InTo)`

#### class `Metasound::IGraph`  
`class IGraph : public INode`  
_L388-404_
- inherits: `INode`
- desc: Interface for graph of nodes.
- L391 _public prototype_ `virtual ~IGraph() = default;`
- L394 _public prototype_ `virtual const FTopLevelAssetPath& GetAssetPath() const = 0;` — Returns path to graph's authoring content (invalid if generated dynamically).
- L397 _public prototype_ `virtual const TArray<FDataEdge>& GetDataEdges() const = 0;` — Retrieve all the edges associated with a graph.
- L400 _public prototype_ `virtual const FInputDataDestinationCollection& GetInputDataDestinations() const = 0;` — Get vertices which contain input parameters.
- L403 _public prototype_ `virtual const FOutputDataSourceCollection& GetOutputDataSources() const = 0;` — Get vertices which contain output parameters.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L20 _macro_ `#define UE_METASOUND_PURE_VIRTUAL_SET_DEFAULT_INPUT 0`
- L27 _macro_ `#define UE_METASOUND_PURE_VIRTUAL_GET_OPERATOR_DATA 0`
- L30 _namespace_ `namespace Metasound`
- L35 _externvar_ `extern const FString PluginAuthor;` (scope `Metasound`)
- L36 _externvar_ `extern const FText PluginNodeMissingPrompt;` (scope `Metasound`)
- L124 _function_ `friend inline bool operator==(const FNodeClassName& InLHS, const FNodeClassName& InRHS)` (scope `Metasound`)
- L259 _typedef_ `typedef TSharedRef<IOperatorFactory, ESPMode::ThreadSafe> FOperatorFactorySharedRef;` (scope `Metasound`) — Shared ref type of operator factory.
- L263 _function_ `template<typename FactoryType, typename... ArgTypes> TSharedRef<FactoryType, ESPMode::ThreadSafe> MakeOperatorFactoryRef(ArgTypes&&... Args)` (scope `Metasound`) — Convenience function for making operator factory references
- L337 _typedef_ `typedef TTuple<const INode*, FVertexName> FNodeDataVertexKey;` (scope `Metasound`) — Key type for an FOutputDataSource or FInputDataDestination.
- L342 _typedef_ `typedef TMap<FNodeDataVertexKey, FOutputDataSource> FOutputDataSourceCollection;` (scope `Metasound`) — FOutputDataSourceCollection contains multiple FOutputDataSources mapped by FNodeDataVertexKeys.
- L347 _typedef_ `typedef TMap<FNodeDataVertexKey, FInputDataDestination> FInputDataDestinationCollection;` (scope `Metasound`) — FInputDataDestinationCollection contains multiple FInputDataDestinations mapped by FNodeDataVertexKeys.
- L350 _function_ `inline FNodeDataVertexKey MakeSourceDataVertexKey(const FOutputDataSource& InSource)` (scope `Metasound`) — Make a FNodeDataVertexKey from an FOutputDataSource.
- L355 _function_ `inline FNodeDataVertexKey MakeDestinationDataVertexKey(const FInputDataDestination& InDestination)` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundOperatorBuilder.h` (Public)


#### struct `Metasound::FBuildDynamicGraphOperatorParams`  
`struct FBuildDynamicGraphOperatorParams : FBuildGraphOperatorParams`  
_L48-52_
- inherits: `FBuildGraphOperatorParams`
- desc: Parameters for building a dynamic graph operator consist of the parameters needed to build a standard graph operator as well as a transform queue and set of callbacks in order to communicate and react to changes in the dynamic operator.
- L50 _public member_ `TSharedPtr<TSpscQueue<TUniquePtr<DynamicGraph::IDynamicOperatorTransform>>> TransformQueue;`
- L51 _public member_ `const DynamicGraph::FDynamicOperatorUpdateCallbacks& OperatorUpdateCallbacks;`

#### class `Metasound::FOperatorBuilder`  
`class FOperatorBuilder : public IOperatorBuilder`  
_L55-181_
- inherits: `IOperatorBuilder`
- desc: FOperatorBuilder builds an IOperator from an IGraph.
- L63 _public prototype_ `FOperatorBuilder(const FOperatorBuilderSettings& InBuilderSettings);` — FOperatorBuilder constructor. @param InBuilderSettings  - Settings to configure builder options.
- L65 _public prototype_ `virtual ~FOperatorBuilder();`
- L75 _public prototype_ `virtual TUniquePtr<IOperator> BuildGraphOperator(const FBuildGraphOperatorParams& InParams, FBuildResults& OutResults) const override;` — Create an IOperator from an IGraph. @param InParams   - Params of the current build @param OutResults - Results data pertaining to the given build operator result. @return A TUniquePtr to an IOperator. If the processes was unsuccessful, the returned pointer will contain a nullptr and be invalid.
- L85 _public prototype_ `TUniquePtr<IOperator> BuildDynamicGraphOperator(const FBuildDynamicGraphOperatorParams& InParams, FBuildResults& OutResults);` — Create an dynamic IOperator from an IGraph. @param InParams                  - Params of the current build @param OutResults                - Results data pertaining to the given build operator result. @return A TUniquePtr to an IOperator. If the processes was unsuccessful, the returned pointer will contain a nullptr and be invalid.
- L137 _private prototype_ `FBuildStatus DepthFirstTopologicalSort(OperatorBuilder::FBuildContext& InOutContext, TArray<const INode*>& OutNodes) const;` — Perform topological sort using depth first algorithm.
- L140 _private prototype_ `FBuildStatus KahnsTopologicalSort(OperatorBuilder::FBuildContext& InOutContext, TArray<const INode*>& OutNodes) const;` — Perform topological sort using kahns algorithm.
- L143 _private prototype_ `FBuildStatus PruneNodes(OperatorBuilder::FBuildContext& InOutContext, TArray<const INode*>& InOutNodes) const;` — Prune unreachable nodes from InOutNodes
- L146 _private prototype_ `void InitializeVertexInterfaceData(const IGraph& InGraph, DirectedGraphAlgo::FGraphOperatorData& InOutGraphOperatorData) const;` — Creates FVertexInterfaceData from the IGraph.
- L149 _private prototype_ `void InitializeOperatorInfo(const IGraph& InGraph ,TArray<const INode*>& InSortedNodes, DirectedGraphAlgo::FGraphOperatorData& InOutGraphOperatorData) const;` — Initialize Operator Info
- L152 _private prototype_ `FBuildStatus GatherExternalInputDataReferences(OperatorBuilder::FBuildContext& InOutContext, const FInputVertexInterfaceData& InExternalInputData) const;` — Get and route input data references for inputs provided externally to the graph.
- L155 _private prototype_ `void GatherInternalGraphDataReferences(OperatorBuilder::FBuildContext& InOutContext, const TArray<const INode*>& InNodes, TMap<FGuid, FDataReferenceCollection>& OutNodeVertexData) const;` — Graphs all internal graph references and places them in output map.
- L158 _private prototype_ `FBuildStatus ValidateOperatorOutputsAreBound(const INode& InNode, const FOutputVertexInterfaceData& InVertexData) const;` — Validates whether all operator outputs are bound to data references.
- L161 _private prototype_ `FBuildStatus GatherGraphDataReferences(OperatorBuilder::FBuildContext& InOutContext, FVertexInterfaceData& OutVertexData) const;` — Get all input/output data references for a given graph.
- L164 _private prototype_ `FBuildStatus CreateOperators(OperatorBuilder::FBuildContext& InOutContext, const TArray<const INode*>& InSortedNodes, const FInputVertexInterfaceData& InExternalInputData) const;` — Call the operator factories for the nodes
- L167 _private prototype_ `TUniquePtr<IOperator> BuildRebindableGraphOperator(const FBuildGraphOperatorParams& InParams, FBuildResults& OutResults) const;` — Creates a graph operator where the set of operators does not change, but the input data can be rebound.
- L170 _private prototype_ `TUniquePtr<IOperator> BuildStaticGraphOperator(const FBuildGraphOperatorParams& InParams, FBuildResults& OutResults) const;` — Creates a graph operator where teh set of operators is constant and the input data cannot be rebound.
- L173 _private prototype_ `bool BuildGraphOperatorData(const FBuildGraphOperatorParams& InParams, DirectedGraphAlgo::FGraphOperatorData& OutGraphOperatorData, TArray<const INode*>& OutNodeOrder, FBuildResults& OutResults) const;` — Builds graph operator data structure.
- L176 _private prototype_ `DynamicGraph::FDynamicGraphOperatorData& GetDynamicGraphOperatorData(DynamicGraph::IDynamicGraphInPlaceBuildable& InBuildable) const;` — Access function for retrieving FDynamicGraphOperatorData from an IDynamicGraphInPlaceBuildable.
- L178 _private prototype_ `FBuildStatus::EStatus GetMaxErrorLevel() const;`
- L180 _private member_ `FOperatorBuilderSettings BuilderSettings;`

#### struct `Metasound::FOperatorBuilder::FBuildStatus`  
`struct FBuildStatus`  
_L90-133_
- desc: Handles build status of current build operation.
- L112 _public prototype_ `FBuildStatus() = default;`
- L114 _public function_ `FBuildStatus(FBuildStatus::EStatus InStatus) : Value(InStatus)`
- L120 _public function_ `FBuildStatus& operator |= (FBuildStatus RHS)` — Merge build statuses by taking the maximum of EStatus.
- L126 _public function_ `operator EStatus() const`
- L132 _private member_ `EStatus Value = NoError;`

#### enum `Metasound::FOperatorBuilder::FBuildStatus::EStatus`  
`enum EStatus`  
_L99-109_
- desc: Enumeration of build status states. Note: plain enum used here instead of enum class so that implicit conversion to int32 can be utilized. It is assumed that the build status int32 values increase as the build status deteriorates. Build statuses are merged by taking the maximum int32 value of the EStatus.
- L102 _public enumerator_ `NoError = 0` — No error has been encountered.
- L105 _public enumerator_ `NonFatalError = 1` — A non fatal error has been encountered.
- L108 _public enumerator_ `FatalError = 2` — A fatal error has been encountered.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L20 _namespace_ `namespace Metasound`
- L27 _namespace_ `namespace OperatorBuilder` (scope `Metasound`)
- L32 _namespace_ `namespace DynamicGraph` (scope `Metasound`)
- L40 _namespace_ `namespace DirectedGraphAlgo` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundOperatorBuilderSettings.h` (Public)


#### enum `Metasound::EOperatorBuilderNodePruning`  
`enum class EOperatorBuilderNodePruning : uint8`  
_L19-32_
- desc: EOperatorBuildNodePruning expresses the desired pruning behavior during the node pruning step. Some nodes are unreachable in the graph either by traversing from the input nodes to from the output nodes. Because they are not dependent, they have no impact on the produced output and can be pruned without causing any change to the declared behavior of the graph.
- L22 _public enumerator_ `None` — Do not prune any nodes.
- L25 _public enumerator_ `PruneNodesWithoutOutputDependency` — Prune nodes which cannot be reached from the output nodes.
- L28 _public enumerator_ `PruneNodesWithoutInputDependency` — Prune nodes which cannot be reached from the input nodes.
- L31 _public enumerator_ `PruneNodesWithoutExternalDependency` — Prune nodes which cannot be reached from the input nodes or output nodes.

#### struct `Metasound::FOperatorBuilderSettings`  
`struct FOperatorBuilderSettings`  
_L38-110_
- desc: FOperatorBuilderSettings Settings for building IGraphs into IOperators.
- L41 _public member_ `EOperatorBuilderNodePruning PruningMode = EOperatorBuilderNodePruning::None;` — Desired node pruning behavior.
- L46 _public member_ `bool bValidateNoCyclesInGraph = true;` — If true, the IGraph will be analyzed to detect cycles. Errors will be generated if a cycle is detected in the graph.
- L51 _public member_ `bool bValidateNoDuplicateInputs = true;` — If true, the inputs to each node in the IGraph will be analyzed to detect duplicate inputs connected to an individual vertex on a given node.  Errors will be generated if duplicates are detected.
- L58 _public member_ `bool bValidateVerticesExist = true;` — If true, each FDataEdge in the IGraph will be validated by checking that the corresponding INodes contain matching FDataVertex information as described by the FDataEdge. Errors will be generated if inconsistencies are detected.
- L64 _public member_ `bool bValidateEdgeDataTypesMatch = true;` — If true, each FDataEdge in the IGraph will be validated by checking that the FInputDataSource and FOutputDataDestination data types are equal. Errors will be generated if unequal data types are detected.
- L70 _public member_ `bool bValidateOperatorOutputsAreBound = true;` — If true, each IOperator in the graph will be validated by checking that each output of the FVertexInterface is bound to data. Errors will be generated outputs are not bound.
- L76 _public member_ `bool bFailOnAnyError = false;` — If true, the builder will return an invalid IOperator if any errors are detected. If false, the builder will return an invalid IOperator only if fatal errors are detected.
- L80 _public member_ `bool bPopulateInternalDataReferences = false;` — If true, enables tracking all internal data references (can be used for analyzing internal graph state by managing sound generator).
- L88 _public member_ `bool bEnableOperatorRebind = false;` — If true, the operator created by the builder will be able to update the underlying data of it's input and output data references through the IOperator::BindInputs(...) and IOperator BindOutputs(...) methods. This requires that the created operator maintain additional data and results in a modest increase in memory usage.
- L94 _public member_ `bool bProfileOperators = false;` — If true, the graph's operators will be wrapped in ProfilingOperator instances and insights events will be generated for their Execute functions.
- L97 _public prototype_ `static const FOperatorBuilderSettings& GetDefaultSettings();` — Return the default settings for the current build environment.
- L100 _public prototype_ `static const FOperatorBuilderSettings& GetDefaultDebugSettings();` — Return the default settings for a debug build environment.
- L103 _public prototype_ `static const FOperatorBuilderSettings& GetDefaultDevelopementSettings();` — Return the default settings for a development build environment.
- L106 _public prototype_ `static const FOperatorBuilderSettings& GetDefaultTestSettings();` — Return the default settings for a test build environment.
- L109 _public prototype_ `static const FOperatorBuilderSettings& GetDefaultShippingSettings();` — Return the default settings for a shipping build environment.

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L9 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundOperatorData.h` (Public)


#### struct `Metasound::OperatorDataPrivate::THasOperatorDataTypeNameMember`  
`template<typename OperatorDataType> struct THasOperatorDataTypeNameMember`  
_L15-40_
- desc: Helper template for determining whether a static OperatorDataTypeName exists on the node configuration class declaration.
- L19 _private prototype_ `template<typename T> static std::negation<std::is_member_pointer<decltype(&T::OperatorDataTypeName)>> HasStaticMemberHelper(int32);`
- L22 _private prototype_ `template<typename T> static std::false_type HasStaticMemberHelper(...);`
- L26 _private typedef_ `template<typename T> using THasStaticMember = decltype(HasStaticMemberHelper<T>(0));` — If there is a static member named T::OperatorDataTypeName, than THasStaticMember<T> will be of type std::true_type
- L29 _private prototype_ `template<typename T> static std::is_convertible<decltype(T::OperatorDataTypeName), FName> IsConvertibleToFNameHelper(int32);`
- L32 _private prototype_ `template<typename T> static std::false_type IsConvertibleToFNameHelper(...);`
- L36 _private typedef_ `template<typename T> using TIsConvertibleToFName = decltype(IsConvertibleToFNameHelper<T>(0));` — If the member T::OperatorDataTypeName exists and is convertible to an FName, this will be of std::true_type
- L39 _public member_ `static constexpr bool Value = TIsConvertibleToFName<OperatorDataType>::value && THasStaticMember<OperatorDataType>::value;`

#### class `Metasound::IOperatorData`  
`class IOperatorData`  
_L44-52_
- desc: Base class for node configurations.
- L47 _public prototype_ `IOperatorData() = default;`
- L48 _public prototype_ `virtual ~IOperatorData() = default;`
- L51 _public prototype_ `virtual FName GetOperatorDataTypeName() const = 0;` — Return a typename use for safe downcasting of the IOperatorData.

#### class `Metasound::TOperatorData`  
`template<typename DerivedType> class TOperatorData : public IOperatorData`  
_L64-76_
- inherits: `IOperatorData`
- desc: Node configuration CRTP. Node configurations should derived from this class to enable downcasting. class FMyOperatorData : public TOperatorData<FMyOperatorData> { public: static const FLazyName OperatorDataTypeName; };
- L68 _public prototype_ `TOperatorData() = default;`
- L69 _public prototype_ `virtual ~TOperatorData() = default;`
- L71 _public function_ `virtual FName GetOperatorDataTypeName() const override final`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Metasound`
- L11 _namespace_ `namespace OperatorDataPrivate` (scope `Metasound`)
- L80 _function_ `template<typename OperatorDataType> FName GetStaticOperatorDataTypeName()` (scope `Metasound`) — Returns the type name of the node configuration object.
- L90 _function_ `bool IsOperatorDataOfType(const IOperatorData& InNodeConfig)` (scope `Metasound`)
- L104 _function_ `CastOperatorData(ProvidedOperatorDataType* InOperatorData)` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundOperatorInterface.h` (Public)


#### class `Metasound::IOperator`  
`class IOperator`  
_L15-186_
- desc: IOperator IOperator defines the interface for render time operations.  IOperators are created using an INodeOperatorFactory.
- L33 _public prototype_ `virtual ~IOperator() = default;`
- L45 _public prototype_ `virtual FDataReferenceCollection GetInputs() const;` — `UE_DEPRECATED(5.3, "GetInputs() has been replaced by BindInputs(FInputVertexInterfaceData&).")` — GetInputs() has been deprecated in favor of BindInputs(...). Please update your code by removing the implementation to GetInputs() and implementing BindInputs(...).  In future releases, the GetInputs() virtual method will be removed. Note: IOperators which do not correctly implement BindInputs(...) and BindOutputs(...) will not function correctly with MetaSound operator caching and live auditioning in the MetaSound Builder BP API.
- L57 _public prototype_ `virtual FDataReferenceCollection GetOutputs() const;` — `UE_DEPRECATED(5.3, "GetOutputs() has been replaced by BindOutputs(FOutputVertexInterfaceData&)")` — GetOutputs() has been deprecated in favor of BindOutputs(...). Please update your code by removing the implementation to GetOutputs() and implementing BindOutputs(...).  In future releases, the GetOutputs() virtual method will be removed. Note: IOperators which do not correctly implement BindInputs(...) and BindOutputs(...) will not function correctly with MetaSound operator caching and live auditioning in the MetaSound Builder BP API.
- L69 _public prototype_ `virtual void Bind(FVertexInterfaceData& InVertexData) const;` — `UE_DEPRECATED(5.3, "Bind(FVertexInterfaceData&) has been replaced by BindInputs(FInputVertexInterfaceDAta&) and BindOutputs(FOutputVertexInterfaceData&)")` — Bind(...) has been deprecated in favor of BindInputs(...) and BindOutputs(...). Please update your code by removing the implementation to Bind(...) and implementing BindOutputs(...).  In future releases, the Bind(...) virtual method will be removed. Note: IOperators which do not correctly implement BindInputs(...) and BindOutputs(...) will not function correctly with MetaSound operator caching and live auditioning in the MetaSound Builder BP API.
- L103 _public prototype_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData);` — BindInputs binds data references in the IOperator with the FInputVertexInterfaceData. All input data references should be bound to the InVertexData to support other MetaSound systems such as MetaSound BP API, Operator Caching, and live auditioning. Note: The virtual function IOPerator::BindInputs(...) will be made a pure virtual when IOperator::GetInputs() is removed at or after release 5.5 Note: Binding an data reference may update the which underlying object the reference points to. Any operator which caches pointers or values from data references must update their cached pointers in the call to BindInputs(...).  Operators which do not cache the underlying pointer of a data reference do not need to update anything after BindInputs(...) Example: FMyOperator::FMyOperator(TDataReadReference<float> InGain, TDataReadReference<FAudioBuffer> InAudioBuffer) : Gain(InGain) , AudioBuffer(InAudioBuffer) { MyBufferPtr = AudioBuffer->GetData(); } void FMyOperator::BindInputs(FInputVertexInterfaceData& InVertexData) { InVertexData.BindReadVertex("Gain", Gain); InVertexData.BindReadVertex("Audio", AudioBuffer); // Update MyBufferPtr in case AudioBuffer references a new FAudioBuffer. MyBufferPtr = AudioBuffer->GetData(); }
- L137 _public prototype_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData);` — BindOutputs binds data references in the IOperator with the FOutputVertexInterfaceData. All output data references should be bound to the InVertexData to support other MetaSound systems such as MetaSound BP API, Operator Caching, and live auditioning. Note: The virtual function IOPerator::BindOutputs(...) will be made a pure virtual when IOperator::GetOutputs() is removed at or after release 5.5 Note: Binding an data reference may update the which underlying object the reference points to. Any operator which caches pointers or values from data references must update their cached pointers in the call to BindOutputs(...).  Operators which do not cache the underlying pointer of a data reference do not need to update anything after BindOutputs(...) Example: FMyOperator::FMyOperator(TDataWriteReference<float> InGain, TDataWriteReference<FAudioBuffer> InAudioBuffer) : Gain(InGain) , AudioBuffer(InAudioBuffer) { MyBufferPtr = AudioBuffer->GetData(); } void FMyOperator::BindOutputs(FOutputVertexInterfaceData& InVertexData) { InVertexData.BindReadVertex("Gain", Gain); InVertexData.BindReadVertex("Audio", AudioBuffer); // Update MyBufferPtr in case AudioBuffer references a new FAudioBuffer. MyBufferPtr = AudioBuffer->GetData(); }
- L143 _public typedef_ `using FResetFunction = void(*)(IOperator*, const FResetParams& InParams);` — Pointer to initialize function for an operator. @param IOperator* - The operator associated with the function pointer.
- L153 _public prototype_ `virtual FResetFunction GetResetFunction() = 0;` — Return the reset function to call during graph execution. The IOperator* argument to the FExecutionFunction will be the same IOperator instance which returned the execution function. nullptr return values are valid and signal an IOperator which does not need to be reset.
- L159 _public typedef_ `using FExecuteFunction = void(*)(IOperator*);` — Pointer to execute function for an operator. @param IOperator* - The operator associated with the function pointer.
- L169 _public prototype_ `virtual FExecuteFunction GetExecuteFunction() = 0;` — Return the execution function to call during graph execution. The IOperator* argument to the FExecutionFunction will be the same IOperator instance which returned the execution function. nullptr return values are valid and signal an IOperator which does not need to be executed.
- L175 _public typedef_ `using FPostExecuteFunction = void(*)(IOperator*);` — Pointer to post execute function for an operator. @param IOperator* - The operator associated with the function pointer.
- L185 _public prototype_ `virtual FPostExecuteFunction GetPostExecuteFunction() = 0;` — Return the FPostExecute function to call during graph post execution. The IOperator* argument to the FPostExecutionFunction will be the same IOperator instance which returned the execution function. nullptr return values are valid and signal an IOperator which does not need to be post executed.

#### struct `Metasound::IOperator::FResetParams`  
`struct FResetParams`  
_L21-31_
- desc: FResetOperatorParams holds the parameters provided to an IOperator's reset function.
- L24 _public member_ `const FOperatorSettings& OperatorSettings;` — General operator settings for the graph.
- L27 _public member_ `const FMetasoundEnvironment& Environment;` — Environment settings available.
- L30 _public member_ `const FGraphRenderCost* GraphRenderCost = nullptr;` — Object for tracking runtime render cost of a MetaSound

#### struct `Metasound::FOperatorAndInputs`  
`struct FOperatorAndInputs`  
_L189-194_
- desc: todo: better place to put this? needs to be in core
- L191 _public member_ `TUniquePtr<IOperator> Operator;`
- L192 _public member_ `FInputVertexInterfaceData Inputs;`
- L193 _public member_ `TSharedPtr<FGraphRenderCost> RenderCost;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundOperatorSettings.h` (Public)


#### class `Metasound::FOperatorSettings`  
`class FOperatorSettings`  
_L40-115_
- desc: FOperatorSettings Audio settings for Metasound IOperators including audio sample rate, block rate and frames per block. The audio SampleRate defines the number of audio samples per a second of a mono waveform. The BlockRate defines the number of times an IOperator's execution function will be triggered per a second of audio content. The NumFramesPerBlock defines the number of audio frames written-to and/or read-from during a single call to an IOperator's execution function. GetNumFramesPerBlock() is required to return a value that abides by the alignment requirements of FAudioBuffer, FAlignedFloatBuffer and the math routines declared in BufferVectorOperations.h. This enables the vast majority of Metasound IOperators to take advantage of SIMD hardware accelerations. In order to achieve SIMD alignment, desired block rates must be slightly adjusted to match the boundaries of the given sample rate and SIMD alignment. GetActualBlockRate() returns the true block rate after adhering to sample rate and SIMD boundaries.
- L48 _public prototype_ `FOperatorSettings(FSampleRate InSampleRate, float InTargetBlockRate);` — FOperatorSettings constructor. @param InSampleRate      - Audio sample rate in Hz. @param InTargetBlockRate - The desired block rate in Hz.
- L51 _public prototype_ `void SetSampleRate(FSampleRate InSampleRate);` — Set the audio sample rate in Hz.
- L54 _public function_ `inline float GetSampleRate() const` — Get the audio sample rate in Hz.
- L66 _public prototype_ `void SetTargetBlockRate(float InTargetBlockRate);` — Set the target block rate in Hz. In order to achieve SIMD alignment, target block rates must be adjusted to match the boundaries of the given sample rate and SIMD alignment. GetActualBlockRate() returns the true block rate after adhering to sample rate and SIMD boundaries.
- L69 _public prototype_ `float GetTargetBlockRate() const;` — Get the target block rate in Hz.
- L74 _public prototype_ `float GetActualBlockRate() const;` — Get the actual block rate in Hz after adhering to sample rate and SIMD alignment.
- L84 _public function_ `inline int32 GetNumFramesPerBlock() const` — Get the number of audio frames in a block. This function is required to return a value that abides by the alignment requirements of FAudioBuffer, FAlignedFloatBuffer and the math routines declared in BufferVectorOperations.h. This enables the vast majority of Metasound IOperators to take advantage of SIMD hardware accelerations.
- L90 _public prototype_ `FString ToString() const;` — Convert to human readable string.
- L104 _private prototype_ `void Update();` — Update actual block rate and frames per block.
- L106 _private prototype_ `int32 RoundToAligned(int32 Alignment, int32 InNum) const;`
- L108 _private member_ `FSampleRate SampleRate = 1;`
- L110 _private member_ `float TargetBlockRate = 1.f;`
- L112 _private member_ `float ActualBlockRate = 1.f;`
- L114 _private member_ `int32 NumFramesPerBlock = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L9 _namespace_ `namespace Metasound`
- L11 _typedef_ `using FSampleRate = int32;` (scope `Metasound`)
- L95 _function_ `friend inline uint32 GetTypeHash(const FOperatorSettings& InSettings)` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundParamHelper.h` (Public)


#### Free symbols / members of external scopes

- L54 _macro_ `#define DECLARE_METASOUND_PARAM(API_EXPORT, PARAM_NAME) \` — Declare a node parameter that can be accessed by other code (e.g. tests) @param API_EXPORT If this parameter should be available to other modules (common), provide your module API export here @param PARAM_NAME The parameter name
- L61 _macro_ `#define DEFINE_METASOUND_PARAM(NAME, NAME_TEXT, TOOLTIP_TEXT) \`
- L71 _macro_ `#define METASOUND_PARAM(NAME, NAME_TEXT, TOOLTIP_TEXT) \`
- L80 _macro_ `#define METASOUND_GET_PARAM_NAME(NAME) NAME##Name`
- L83 _macro_ `#define METASOUND_GET_PARAM_TT(NAME) NAME##Tooltip`
- L84 _macro_ `#define METASOUND_GET_PARAM_NAME_AND_TT(NAME) NAME##Name, NAME##Tooltip`
- L85 _macro_ `#define METASOUND_GET_PARAM_METADATA(NAME) FDataVertexMetadata { NAME##Tooltip, NAME##DisplayName }`
- L86 _macro_ `#define METASOUND_GET_PARAM_METADATA_ADVANCED(NAME) FDataVertexMetadata { NAME##Tooltip, NAME##DisplayName, true }`
- L87 _macro_ `#define METASOUND_GET_PARAM_DISPLAYNAME(NAME) NAME##DisplayName`
- L89 _macro_ `#define METASOUND_GET_PARAM_TT(NAME) FText{}`
- L90 _macro_ `#define METASOUND_GET_PARAM_NAME_AND_TT(NAME) NAME##Name, FText{}`
- L91 _macro_ `#define METASOUND_GET_PARAM_METADATA(NAME) FDataVertexMetadata::EmptyBasic`
- L92 _macro_ `#define METASOUND_GET_PARAM_METADATA_ADVANCED(NAME) FDataVertexMetadata::EmptyAdvanced`
- L93 _macro_ `#define METASOUND_GET_PARAM_DISPLAYNAME(NAME) FText{}`
- L95 _macro_ `#define METASOUND_GET_PARAM_NAME_AND_METADATA(NAME) METASOUND_GET_PARAM_NAME(NAME), METASOUND_GET_PARAM_METADATA(NAME)`
- L97 _macro_ `#define METASOUND_GET_PARAM_NAME_AND_METADATA_ADVANCED(NAME) METASOUND_GET_PARAM_NAME(NAME), METASOUND_GET_PARAM_METADATA_ADVANCED(NAME)`
- L99 _macro_ `#define METASOUND_GET_PARAM_NAME_WITH_INDEX(NAME, INDEX) *FString::Format(*static_cast<FName>(NAME##Name).ToString(), {INDEX})`
- L101 _macro_ `#define METASOUND_GET_PARAM_NAME_WITH_INDEX_AND_TT(NAME, INDEX) METASOUND_GET_PARAM_NAME_WITH_INDEX(NAME, INDEX), FText::Format(NAME##Tooltip, INDEX)`
- L102 _macro_ `#define METASOUND_GET_PARAM_TT_WITH_INDEX(NAME, INDEX) FText::Format(NAME##Tooltip, INDEX)`
- L103 _macro_ `#define METASOUND_GET_PARAM_NAME_WITH_INDEX_AND_METADATA(NAME, INDEX) METASOUND_GET_PARAM_NAME_WITH_INDEX(NAME, INDEX), FDataVertexMetadata {FText::Format(NAME##Tooltip, INDEX)}`
- L105 _macro_ `#define METASOUND_GET_PARAM_NAME_WITH_INDEX_AND_TT(NAME, INDEX) *FString::Format(*static_cast<FName>(NAME##Name).ToString(), {INDEX}), FText{}`
- L106 _macro_ `#define METASOUND_GET_PARAM_TT_WITH_INDEX(NAME, INDEX) FText{}`
- L107 _macro_ `#define METASOUND_GET_PARAM_NAME_WITH_INDEX_AND_METADATA(NAME, INDEX) *FString::Format(*static_cast<FName>(NAME##Name).ToString(), {INDEX}), FDataVertexMetadata::EmptyBasic`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundPolymorphic.h` (Public)


#### struct `Metasound::TPolymorphicTraits`  
`template<typename T> struct TPolymorphicTraits`  
_L13-18_
- L15 _public member_ `static constexpr bool bIsPolymorphic = false;`
- L16 _public member_ `static constexpr bool bIsAbstract = false;`
- L17 _public typedef_ `using BaseType = void;`

#### struct `Metasound::FPolyTypeInfo`  
`struct FPolyTypeInfo`  
_L20-25_
- L22 _public member_ `FName TypeName = NAME_None;`
- L23 _public member_ `FName BaseTypeName = NAME_None;`
- L24 _public member_ `bool bIsPolymorphic = false;`

#### class `Metasound::FPolyRegistry`  
`class FPolyRegistry`  
_L77-96_
- L92 _public prototype_ `void GetAllRegisteredTypes(TArray<FPolyTypeInfo>& Out) const;`
- L95 _private member_ `TMap<FName, FPolyTypeInfo> Map;`

#### struct `Metasound::TPolyRegistrar`  
`template <typename T> struct TPolyRegistrar`  
_L99-123_
- L101 _public function_ `TPolyRegistrar()`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`
- L48 _prototype_ `requires std::is_constructible_v<DataType, ArgTypes...>;` (scope `Metasound`)
- L110 _typedef_ `using Base = TPolymorphicTraits<T>::BaseType;` (scope `Metasound::TPolyRegistrar::TPolyRegistrar`)
- L134 _macro_ `#define DECLARE_METASOUND_POLY_TYPE(TYPE, BASE, IS_ABSTRACT)\`
- L145 _macro_ `#define REGISTER_METASOUND_POLY_TYPE(T) static Metasound::TPolyRegistrar<T> UE_JOIN(GPolyReg,__COUNTER__);`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundRenderCost.h` (Public)


#### class `Metasound::FGraphRenderCost`  
`class FGraphRenderCost : public TSharedFromThis<FGraphRenderCost>`  
_L28-62_
- inherits: `TSharedFromThis<FGraphRenderCost>`
- desc: FGraphRenderCost represents the accumulated render cost of a graph. Individual nodes in a graph can report their render cost through an FNodeRenderCost. The render cost of each node is added together to determine the graph's render cost.
- L36 _public prototype_ `FGraphRenderCost(EPrivateToken InToken);`
- L38 _public prototype_ `static TSharedRef<FGraphRenderCost> MakeGraphRenderCost();`
- L46 _public prototype_ `FNodeRenderCost AddNode(const FGuid& InNodeInstanceID, const FMetasoundEnvironment& InEnv);` — Add a node to the graph's render cost. @param InNodeInstanceID - ID of the node to add. @param InEnv - The environment used to create the node. @return FNodeRenderCost object for reporting the render cost of individual nodes.
- L49 _public prototype_ `void ResetNodeRenderCosts();` — Reset the individual node render costs to zero.
- L52 _public prototype_ `float ComputeGraphRenderCost() const;` — Adds all the individual node render costs and returns the result.
- L55 _private prototype_ `void SetNodeRenderCost(int32 InNodeIndex, float InRenderCost);`
- L57 _private member_ `TArray<float> NodeCosts;`
- L58 _private prototype_ `void AddNodeHierarchy(const FGuid& InNodeInstanceID, const FMetasoundEnvironment& InEnv);`
- L60 _private member_ `TArray<TArray<FGuid>> NodeHierarchies;`

#### enum `Metasound::FGraphRenderCost::EPrivateToken`  
`enum EPrivateToken`  
_L31-31_
- desc: Private token to enforce creation of shared reference.
- L31 _public enumerator_ `enum EPrivateToken { PrivateToken }; friend class FNodeRenderCost; public: UE_API FGraphRenderCost(EPrivateToken InToken); static UE_API TSharedRef<FGraphRenderCost> MakeGraphRenderCost();` — Private token to enforce creation of shared reference.

#### class `Metasound::FNodeRenderCost`  
`class FNodeRenderCost`  
_L68-87_
- desc: FNodeRenderCost allows individual nodes to report their render cost. FNodeRenderCost should be created with FGraphRenderCost::AddNode(...)
- L71 _private prototype_ `FNodeRenderCost(int32 InNodeIndex, TSharedRef<FGraphRenderCost> InGraphRenderCost);`
- L79 _public prototype_ `FNodeRenderCost() = default;` — The default constructor is provided for convenience, but creating a FNodeRenderCost with the default constructor will allow any method for reading or accumulating a nodes render cost. Instead, FNodeRenderCost should be created with FGraphRenderCost::AddNode(...) so that it is associated and aggregated within a graph.
- L82 _public prototype_ `void SetRenderCost(float InCost);` — Set the render cost of this node.
- L85 _private member_ `int32 NodeIndex = INDEX_NONE;`
- L86 _private member_ `TSharedPtr<FGraphRenderCost> GraphRenderCost;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L15 _macro_ `#define UE_METASOUNDRENDERCOST_TRACK_NODE_HIERARCHY (!UE_BUILD_SHIPPING)`
- L18 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundThreadLocalDebug.h` (Public)


#### struct `Metasound::ThreadLocalDebug::FAssetMetaData`  
`struct FAssetMetaData`  
_L56-61_
- L58 _public member_ `FName ClassName;`
- L59 _public member_ `FName AssetName;`
- L60 _public member_ `FName AssetPath;`

#### struct `Metasound::ThreadLocalDebug::FScopeDebugActiveNode`  
`struct FScopeDebugActiveNode final`  
_L69-87_
- L71 _public prototype_ `explicit FScopeDebugActiveNode(FDebugInfo* InDebugInfo, const INode* InNode);`
- L73 _public prototype_ `~FScopeDebugActiveNode();`
- L75 _public prototype_ `FScopeDebugActiveNode(const FScopeDebugActiveNode&) = delete;`
- L76 _public prototype_ `FScopeDebugActiveNode(FScopeDebugActiveNode&&) = delete;`
- L77 _public prototype_ `FScopeDebugActiveNode& operator=(const FScopeDebugActiveNode&) = delete;`
- L78 _public prototype_ `FScopeDebugActiveNode& operator=(FScopeDebugActiveNode&&) = delete;`
- L80 _public function_ `const FAssetMetaData& GetAssetMetaData() const`
- L83 _private prototype_ `void UpdateAssetMetaData();`
- L84 _private member_ `FAssetMetaData AssetMetaData;`
- L85 _private member_ `const INode* PriorNode = nullptr;`
- L86 _private member_ `FDebugInfo* DebugInfo = nullptr;`

#### Free symbols / members of external scopes

- L42 _macro_ `#define UE_METASOUND_DEBUG_ENABLED (DO_CHECK || DO_ENSURE)`
- L47 _namespace_ `namespace Metasound`
- L52 _namespace_ `namespace ThreadLocalDebug` (scope `Metasound`)
- L63 _prototype_ `FDebugInfo* GetDebugInfoOnThisThread();` (scope `Metasound::ThreadLocalDebug`)
- L64 _prototype_ `void SetAssetScopeForThisThread(FName Class, FName Name, FName Path);` (scope `Metasound::ThreadLocalDebug`)
- L66 _prototype_ `const TCHAR* GetActiveNodeClassNameAndVersionOnThisThread();` (scope `Metasound::ThreadLocalDebug`)
- L95 _macro_ `#define METASOUND_DEBUG_SCOPE_NAME __MetaSoundDebugScope`
- L96 _macro_ `#define METASOUND_DEBUG_DECLARE_SCOPE ::Metasound::ThreadLocalDebug::FDebugInfo* METASOUND_DEBUG_SCOPE_NAME = ::Metasound::ThreadLocalDebug::GetDebugInfoOnThisThread();`
- L98 _macro_ `#define METASOUND_DEBUG_SET_ACTIVE_NODE_SCOPE(InNodePtr)\`
- L105 _macro_ `#define METASOUND_DEBUG_ACTIVE_ASSET_SCOPE (__MetaSoundDebugScope_ActiveNode.GetAssetMetaData())`
- L107 _macro_ `#define METASOUND_DEBUG_ACTIVE_NODE_NAME (::Metasound::ThreadLocalDebug::GetActiveNodeClassNameAndVersionOnThisThread())`
- L109 _macro_ `#define METASOUND_DEBUG_SET_ACTIVE_ASSET_SCOPE(AssetName, AssetClass, AssetPath)\`
- L115 _macro_ `#define METASOUND_DEBUG_SCOPE_NAME`
- L116 _macro_ `#define METASOUND_DEBUG_DECLARE_SCOPE`
- L117 _macro_ `#define METASOUND_DEBUG_SET_ACTIVE_NODE_SCOPE(InNodePtr)`
- L118 _macro_ `#define METASOUND_DEBUG_ACTIVE_ASSET_SCOPE`
- L119 _macro_ `#define METASOUND_DEBUG_ACTIVE_NODE_NAME TEXT("[Metasound debug disable. Use UE_METASOUND_DEBUG_ENABLED to enable]")`
- L120 _macro_ `#define METASOUND_DEBUG_SET_ACTIVE_ASSET_SCOPE(AssetName, AssetClass, AssetPath)`

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundTrace.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define METASOUND_CPUPROFILERTRACE_ENABLED 1`
- L12 _macro_ `#define METASOUND_CPUPROFILERTRACE_ENABLED 0`
- L21 _macro_ `#define METASOUND_TRACE_CPUPROFILER_EVENT_SCOPE_COND(Name, Cond)\` — Copied from SCOPED_NAMED_EVENT but modified to accommodate event names containing ::
- L25 _macro_ `#define METASOUND_TRACE_CPUPROFILER_EVENT_SCOPE(Name)\`
- L28 _macro_ `#define METASOUND_TRACE_CPUPROFILER_EVENT_SCOPE_TEXT_COND(Name, Cond) \`
- L32 _macro_ `#define METASOUND_TRACE_CPUPROFILER_EVENT_SCOPE_TEXT(Name) \`
- L36 _macro_ `#define METASOUND_TRACE_CPUPROFILER_EVENT_SCOPE_FAST(TraceSpecId, Name) \` — Uses cached Insights SpecId to avoid string lookup
- L43 _macro_ `#define METASOUND_TRACE_CPUPROFILER_EVENT_SCOPE_COND(Name, Cond)`
- L44 _macro_ `#define METASOUND_TRACE_CPUPROFILER_EVENT_SCOPE(Name)`
- L45 _macro_ `#define METASOUND_TRACE_CPUPROFILER_EVENT_SCOPE_TEXT_COND(Name, Cond)`
- L46 _macro_ `#define METASOUND_TRACE_CPUPROFILER_EVENT_SCOPE_TEXT(Name)`
- L47 _macro_ `#define METASOUND_TRACE_CPUPROFILER_EVENT_SCOPE_FAST(TraceSpecId, Name)`
- L53 _macro_ `#define METASOUND_LLM_SCOPE LLM_SCOPE_BYTAG(Audio_MetaSound);` — Convenience macro for Audio_MetaSound LLM scope to avoid misspells.

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundVariable.h` (Public)


#### struct `Metasound::MetasoundVariablePrivate::FConstructWithLiteral`  
`struct FConstructWithLiteral`  
_L19-19_
- desc: This tag resolves issues around the behavior of the TLiteralTraits<>::bIsParsable. Use of the tag dispatch in constructing TVariable<> disables implicit conversions of FLiteral::FVariantType underlying types to FLiteral.

#### struct `Metasound::TVariable`  
`template<typename DataType> struct TVariable`  
_L27-132_
- desc: A MetaSound Variable contains a data reference's prior and current value. @tparam DataType - Underlying data type of data reference.
- L29 _public typedef_ `using FWriteReference = TDataWriteReference<DataType>;`
- L30 _public typedef_ `using FReadReference = TDataReadReference<DataType>;`
- L32 _public prototype_ `TVariable() = delete;`
- L33 _public prototype_ `TVariable(TVariable&&) = default;`
- L34 _public prototype_ `TVariable(const TVariable&) = default;`
- L41 _public function_ `TVariable(const FLiteral& InInitialValue, MetasoundVariablePrivate::FConstructWithLiteral) : Literal(InInitialValue)` — Create a delayed variable. @param InInitialValue - A literal used to construct the initial value.
- L46 _public function_ `bool RequiresDelayedDataCopy() const`
- L58 _public function_ `void CopyReferencedData()`
- L67 _public function_ `void SetDataReference(FReadReference InDataReference)`
- L72 _public function_ `void InitDataReference(const FOperatorSettings& InOperatorSettings)`
- L82 _public function_ `FReadReference GetDataReference() const` — Get the current data reference.
- L88 _public function_ `void BindDataReference(FOutputVertexInterfaceData& InVertexData, const FVertexName& InVertexName)`
- L94 _public function_ `void BindDelayedDataReference(FOutputVertexInterfaceData& InVertexData, const FVertexName& InVertexName)`
- L100 _public function_ `void InitDelayedDataReference(const FOperatorSettings& InOperatorSettings)`
- L109 _public function_ `FReadReference GetDelayedDataReference() const` — Get the delayed data reference
- L115 _public function_ `void Reset(const FOperatorSettings& InOperatorSettings)`
- L129 _private member_ `FLiteral Literal;`
- L130 _private member_ `TOptional<FWriteReference> DelayedDataReference;`
- L131 _private member_ `TOptional<FReadReference> DataReference;`

#### struct `Metasound::TIsVariable`  
`template<typename DataType> struct TIsVariable`  
_L136-139_
- desc: Template to determine if data type is a variable.
- L138 _public member_ `static constexpr bool Value = false;`
- L145 _public member_ `static constexpr bool Value = true;`

#### struct `Metasound::TIsVariable`  
`template<typename UnderlyingDataType> struct TIsVariable<TVariable<UnderlyingDataType>>`  
_L143-146_
- desc: Template specialization to determine if data type is a variable.
- L138 _public member_ `static constexpr bool Value = false;`
- L145 _public member_ `static constexpr bool Value = true;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Metasound`
- L14 _namespace_ `namespace MetasoundVariablePrivate` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundVariableNodes.h` (Public)


#### class `Metasound::MetasoundVariableNodesPrivate::TVariableOperator`  
`template<typename DataType> class TVariableOperator : public FNoOpOperator`  
_L83-109_
- inherits: `FNoOpOperator`
- L85 _private typedef_ `using FVariable = TVariable<DataType>;`
- L88 _public function_ `TVariableOperator(const FOperatorSettings& InOperatorSettings, const FLiteral& InLiteral) : Variable(TDataWriteReference<FVariable>::CreateNew(InLiteral, MetasoundVariablePrivate::FConstructWithLiteral()))`
- L93 _public prototype_ `virtual ~TVariableOperator() = default;`
- L95 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L99 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& OutVertexData) override`
- L108 _private member_ `TDataWriteReference<FVariable> Variable;`

#### class `Metasound::MetasoundVariableNodesPrivate::TVariableMutatorOperator`  
`template<typename DataType> class TVariableMutatorOperator : public IOperator`  
_L113-265_
- inherits: `IOperator`
- desc: Operator for providing setting a variable
- L116 _public typedef_ `using FVariable = TVariable<DataType>;`
- L118 _public function_ `static FVertexInterface DeclareVertexInterface()`
- L133 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L160 _public function_ `TVariableMutatorOperator(TDataWriteReference<FVariable> InVariable, TDataReadReference<DataType> InData) : Variable(InVariable) , Data(InData)`
- L167 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L186 _public prototype_ `virtual ~TVariableMutatorOperator() = default;`
- L188 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L201 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData) override`
- L207 _public function_ `void PostExecute()`
- L212 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L217 _public function_ `virtual IOperator::FExecuteFunction GetExecuteFunction() override`
- L223 _public function_ `virtual IOperator::FPostExecuteFunction GetPostExecuteFunction() override`
- L237 _public function_ `virtual IOperator::FResetFunction GetResetFunction() override`
- L253 _private function_ `static void StaticPostExecute(IOperator* InOperator)`
- L258 _private function_ `static void StaticReset(IOperator* InOperator, const IOperator::FResetParams& InParams)`
- L263 _private member_ `TDataWriteReference<FVariable> Variable;`
- L264 _private member_ `TDataReadReference<DataType> Data;`

#### class `Metasound::MetasoundVariableNodesPrivate::TVariableDeferredAccessorOperator`  
`template<typename DataType> class TVariableDeferredAccessorOperator : public FNoOpOperator`  
_L269-364_
- inherits: `FNoOpOperator`
- desc: Operator for providing delayed access to a variable
- L273 _public typedef_ `using FVariable = TVariable<DataType>;`
- L275 _public function_ `static FVertexInterface DeclareVertexInterface()`
- L290 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L316 _public function_ `TVariableDeferredAccessorOperator(TDataWriteReference<FVariable> InVariable) : Variable(InVariable) , DelayedData(Variable->GetDelayedDataReference())`
- L322 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L341 _public prototype_ `virtual ~TVariableDeferredAccessorOperator() = default;`
- L343 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L352 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData) override`
- L362 _private member_ `TDataWriteReference<FVariable> Variable;`
- L363 _private member_ `TDataReadReference<DataType> DelayedData;`

#### class `Metasound::MetasoundVariableNodesPrivate::TVariableAccessorOperator`  
`template<typename DataType> class TVariableAccessorOperator : public FNoOpOperator`  
_L368-461_
- inherits: `FNoOpOperator`
- desc: Operator for providing inline access to a variable
- L372 _public typedef_ `using FVariable = TVariable<DataType>;`
- L374 _public function_ `static FVertexInterface DeclareVertexInterface()`
- L389 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L415 _public function_ `TVariableAccessorOperator(TDataWriteReference<FVariable> InVariable) : Variable(InVariable)`
- L420 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L439 _public prototype_ `virtual ~TVariableAccessorOperator() = default;`
- L441 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L450 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData) override`
- L460 _private member_ `TDataWriteReference<FVariable> Variable;`

#### class `Metasound::TVariableNode`  
`template<typename DataType> class TVariableNode : public FBasicNode`  
_L468-546_
- inherits: `FBasicNode`
- desc: Variable nodes initialize variable values. The output of a VariableNode is a TVariable.
- L470 _private typedef_ `using FVariable = TVariable<DataType>;`
- L491 _private function_ `static FVertexInterface DeclareVertexInterface()`
- L506 _public function_ `TVariableNode(const FVertexName& InNodeName, const FGuid& InInstanceID, FLiteral&& InLiteral) : TVariableNode(MoveTemp(InLiteral), FNodeData{InNodeName, InInstanceID, DeclareVertexInterface()}, MakeShared<const FNodeClassMetadata>(CreateNodeClassMetadata()))`
- L511 _public function_ `TVariableNode(FLiteral InLiteral, FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InClassMetadata) : FBasicNode(MoveTemp(InNodeData), MoveTemp(InClassMetadata)) , Factory(MakeShared<FFactory>(MoveTemp(InLiteral)))`
- L517 _public function_ `static FNodeClassMetadata CreateNodeClassMetadata()`
- L538 _public function_ `virtual TSharedRef<IOperatorFactory, ESPMode::ThreadSafe> GetDefaultOperatorFactory() const override`
- L545 _private member_ `FOperatorFactorySharedRef Factory;`

#### class `Metasound::TVariableNode::FFactory`  
`class FFactory : public IOperatorFactory`  
_L472-488_
- inherits: `IOperatorFactory`
- L475 _public function_ `FFactory(FLiteral&& InLiteral) : Literal(MoveTemp(InLiteral))`
- L480 _public prototype_ `virtual ~FFactory() = default;`
- L482 _public function_ `virtual TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults) override`
- L487 _private member_ `FLiteral Literal;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define LOCTEXT_NAMESPACE "MetasoundGraphCore"`
- L18 _namespace_ `namespace Metasound`
- L20 _namespace_ `namespace VariableNames` (scope `Metasound`)
- L28 _externvar_ `extern const FDataVertexMetadata OutputDataMetadata;` (scope `Metasound::VariableNames`)
- L29 _externvar_ `extern const FDataVertexMetadata InputVariableMetadata;` (scope `Metasound::VariableNames`)
- L30 _externvar_ `extern const FDataVertexMetadata OutputVariableMetadata;` (scope `Metasound::VariableNames`)
- L33 _prototype_ `FNodeClassName GetVariableNodeClassName(const FName& InDataTypeName);` (scope `Metasound::VariableNames`) — Class name for variable node.
- L36 _prototype_ `FNodeClassName GetVariableMutatorNodeClassName(const FName& InDataTypeName);` (scope `Metasound::VariableNames`) — Class name for variable mutator node.
- L39 _prototype_ `FNodeClassName GetVariableAccessorNodeClassName(const FName& InDataTypeName);` (scope `Metasound::VariableNames`) — Class name for variable accessor node
- L42 _prototype_ `FNodeClassName GetVariableDeferredAccessorNodeClassName(const FName& InDataTypeName);` (scope `Metasound::VariableNames`) — Class name for variable deferred accessor node.
- L46 _function_ `template<typename DataType> const FNodeClassName& GetVariableNodeClassName()` (scope `Metasound::VariableNames`) — Class name for variable node.
- L54 _function_ `template<typename DataType> const FNodeClassName& GetVariableMutatorNodeClassName()` (scope `Metasound::VariableNames`) — Class name for variable mutator node.
- L62 _function_ `template<typename DataType> const FNodeClassName& GetVariableAccessorNodeClassName()` (scope `Metasound::VariableNames`) — Class name for variable accessor node
- L70 _function_ `template<typename DataType> const FNodeClassName& GetVariableDeferredAccessorNodeClassName()` (scope `Metasound::VariableNames`) — Class name for variable deferred accessor node.
- L78 _namespace_ `namespace MetasoundVariableNodesPrivate` (scope `Metasound`)
- L80 _prototype_ `bool IsSupportedVertexData(const IDataReference& InCurrentVariableRef, const FInputVertexInterfaceData& InNew);` (scope `Metasound::MetasoundVariableNodesPrivate`)
- L136 _function_ `` (scope `Metasound::MetasoundVariableNodesPrivate::TVariableMutatorOperator::GetNodeInfo`)
- L293 _function_ `` (scope `Metasound::MetasoundVariableNodesPrivate::TVariableDeferredAccessorOperator::GetNodeInfo`)
- L392 _function_ `` (scope `Metasound::MetasoundVariableNodesPrivate::TVariableAccessorOperator::GetNodeInfo`)
- L550 _typedef_ `template<typename DataType> using TVariableMutatorNode = TNodeFacade<MetasoundVariableNodesPrivate::TVariableMutatorOperator<DataType>>;` (scope `Metasound`) — TVariableMutatorNode allows variable values to be set.
- L558 _typedef_ `template<typename DataType> using TVariableDeferredAccessorNode = TNodeFacade<MetasoundVariableNodesPrivate::TVariableDeferredAccessorOperator<DataType>>;` (scope `Metasound`) — TVariableDeferredAccessorNode provides access to the prior executions variable value. TVariableDeferredAccessorNodes must always be before TVariableMutatorNodes in the dependency order.
- L562 _typedef_ `template<typename DataType> using TVariableAccessorNode = TNodeFacade<MetasoundVariableNodesPrivate::TVariableAccessorOperator<DataType>>;` (scope `Metasound`) — FGetVariable node provides delay free, cpu free access to a set variable.

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundVertex.h` (Public)


#### struct `Metasound::FVariantDescription`  
`struct FVariantDescription`  
_L23-27_
- desc: Describes a variant on a ClassInterface
- L25 _public member_ `FName VariantName;`
- L26 _public member_ `TArray<FName> DataTypes;` — Array of supported data types.

#### struct `Metasound::VertexPrivate::FSubInterfaceLayout`  
`struct FSubInterfaceLayout`  
_L49-59_
- desc: Contains a list of sub-interface spans where the span indices refer to vertex indices of an array containing vertices.
- L57 _public member_ `FName SubInterfaceName;`
- L58 _public member_ `TArray<FInstance> Instances;`

#### struct `Metasound::VertexPrivate::FSubInterfaceLayout::FInstance`  
`struct FInstance`  
_L51-55_
- L53 _public member_ `uint16 Begin = 0;`
- L54 _public member_ `uint16 End = 0;` — Exclusive

#### struct `Metasound::VertexPrivate::FSubInterfaceClassLayout`  
`struct FSubInterfaceClassLayout`  
_L62-67_
- desc: Contains the location of an individual sub interface in a FClassInterface
- L64 _public member_ `FName SubInterfaceName;`
- L65 _public member_ `uint16 Begin = 0;`
- L66 _public member_ `uint16 End = 0;` — Exclusive.

#### enum `Metasound::VertexPrivate::EVertexDirection`  
`enum class EVertexDirection : uint8`  
_L70-74_
- desc: Denotes whether a vertex belongs to the input or output interface
- L72 _public enumerator_ `Input`
- L73 _public enumerator_ `Output`

#### struct `Metasound::VertexPrivate::FVertexKey`  
`struct FVertexKey`  
_L77-95_
- desc: A key for placing input and output vertices in a shared container.
- L79 _public member_ `FVertexName Name;`
- L80 _public member_ `EVertexDirection Direction;`

#### struct `Metasound::VertexPrivate::TEqualVertexName`  
`template<typename VertexType> struct TEqualVertexName`  
_L99-112_
- desc: Functor for finding vertices with equal names
- L101 _public member_ `const FVertexName& NameRef;`
- L103 _public function_ `TEqualVertexName(const FVertexName& InName) : NameRef(InName)`
- L108 _public function_ `inline bool operator()(const VertexType& InOther) const`

#### struct `Metasound::VertexPrivate::TNumOfTypeInPack`  
`template<typename T> struct TNumOfTypeInPack`  
_L116-124_
- desc: constexpr count of the number of a instances of type T in a parameter pack
- L119 _public function_ `template<typename ... Ts> static constexpr uint32 Get()`

#### struct `Metasound::FDataVertexMetadata`  
`struct FDataVertexMetadata`  
_L145-153_
- desc: Vertex metadata
- L147 _public member_ `FText Description;`
- L148 _public member_ `FText DisplayName;`
- L149 _public member_ `bool bIsAdvancedDisplay = false;`
- L151 _public member_ `static FDataVertexMetadata EmptyBasic;`
- L152 _public member_ `static FDataVertexMetadata EmptyAdvanced;`

#### enum `Metasound::EVertexAccessType`  
`enum class EVertexAccessType`  
_L156-160_
- desc: Describe how the vertex will access connected data.
- L158 _public enumerator_ `Reference` — Vertex accesses the data references
- L159 _public enumerator_ `Value` — Vertex accesses the data value.

#### class `Metasound::FDataVertex`  
`class FDataVertex`  
_L167-207_
- desc: FDataVertex An FDataVertex is a named vertex of a MetaSound node which can contain data.
- L172 _public prototype_ `FDataVertex() = default;`
- L181 _public function_ `FDataVertex(const FVertexName& InVertexName, const FName& InDataTypeName, const FDataVertexMetadata& InMetadata, EVertexAccessType InAccessType) : VertexName(InVertexName) , DataTypeName(InDataTypeName) #if WITH_EDITORONLY_DATA , Metadata(InMetadata) #endif` — FDataVertex Constructor @InVertexName - Name of vertex. @InDataTypeName - Name of data type. @InMetadata - Metadata pertaining to given vertex. @InAccessType - The access type of the vertex.
- L192 _public prototype_ `virtual ~FDataVertex() = default;`
- L195 _public member_ `FVertexName VertexName;` — Name of vertex.
- L198 _public member_ `FName DataTypeName;` — Type name of data.
- L202 _public member_ `FDataVertexMetadata Metadata;` — Metadata associated with vertex.
- L206 _public member_ `EVertexAccessType AccessType;` — Access type of the vertex.

#### class `Metasound::FInputDataVertex`  
`class FInputDataVertex : public FDataVertex`  
_L210-256_
- inherits: `FDataVertex`
- desc: FInputDataVertex
- L214 _public prototype_ `FInputDataVertex() = default;`
- L217 _public function_ `FInputDataVertex(const FVertexName& InVertexName, const FName& InDataTypeName, const FDataVertexMetadata& InMetadata, EVertexAccessType InAccessType=EVertexAccessType::Reference) : FDataVertex(InVertexName, InDataTypeName, InMetadata, InAccessType) , Literal(FLiteral::FNone{})` — Construct an FInputDataVertex.
- L225 _public function_ `template<typename LiteralValueType> FInputDataVertex(const FVertexName& InVertexName, const FName& InDataTypeName, const FDataVertexMetadata& InMetadata, EVertexAccessType InAccessType, const LiteralValueType& InLiteralValue) : FDataVertex(InVertexName, InDataTypeName, InMetadata, InAccessType) , Literal(InLiteralValue)` — Construct an FInputDataVertex with a default literal.
- L231 _public function_ `FInputDataVertex(const FVertexName& InVertexName, const FName& InDataTypeName, const FDataVertexMetadata& InMetadata, EVertexAccessType InAccessType, const FLiteral& InLiteral) : FDataVertex(InVertexName, InDataTypeName, InMetadata, InAccessType) , Literal(InLiteral)`
- L238 _public function_ `FLiteral GetDefaultLiteral() const` — Returns the default literal associated with this input.
- L244 _public function_ `void SetDefaultLiteral(const FLiteral& InLiteral)` — Set the default literal for this vertex
- L255 _private member_ `FLiteral Literal;`

#### class `Metasound::TInputDataVertex`  
`template<typename DataType> class TInputDataVertex : public FInputDataVertex`  
_L260-282_
- inherits: `FInputDataVertex`
- desc: Create a FInputDataVertex with a templated MetaSound data type.
- L263 _public prototype_ `TInputDataVertex() = default;`
- L266 _public function_ `template<typename... ArgTypes> FORCENOINLINE TInputDataVertex(const FVertexName& InVertexName, const FDataVertexMetadata& InMetadata, ArgTypes&&... Args) : FInputDataVertex(InVertexName, GetMetasoundDataTypeName<DataType>(), InMetadata, EVertexAccessType::Reference, Forward<ArgTypes>(Args)...)`
- L272 _public function_ `template<typename... ArgTypes> FORCENOINLINE TInputDataVertex(const FLazyName& InVertexName, const FDataVertexMetadata& InMetadata, ArgTypes&&... Args) : FInputDataVertex(InVertexName, GetMetasoundDataTypeName<DataType>(), InMetadata, EVertexAccessType::Reference, Forward<ArgTypes>(Args)...)`
- L278 _public function_ `template<typename... ArgTypes> FORCENOINLINE TInputDataVertex(const char* InVertexName, const FDataVertexMetadata& InMetadata, ArgTypes&&... Args) : FInputDataVertex(InVertexName, GetMetasoundDataTypeName<DataType>(), InMetadata, EVertexAccessType::Reference, Forward<ArgTypes>(Args)...)`

#### class `Metasound::TInputConstructorVertex`  
`template<typename DataType> class TInputConstructorVertex : public FInputDataVertex`  
_L287-297_
- inherits: `FInputDataVertex`
- desc: Create a FInputDataVertex with a templated MetaSound data type which only reads data at operator time.
- L290 _public prototype_ `TInputConstructorVertex() = default;`
- L293 _public function_ `template<typename... ArgTypes> TInputConstructorVertex(const FVertexName& InVertexName, const FDataVertexMetadata& InMetadata, ArgTypes&&... Args) : FInputDataVertex(InVertexName, GetMetasoundDataTypeName<DataType>(), InMetadata, EVertexAccessType::Value, Forward<ArgTypes>(Args)...)`

#### class `Metasound::FOutputDataVertex`  
`class FOutputDataVertex : public FDataVertex`  
_L303-311_
- inherits: `FDataVertex`
- desc: FOutputDataVertex Vertex for outputs.

#### class `Metasound::TOutputDataVertex`  
`template<typename DataType> class TOutputDataVertex : public FOutputDataVertex`  
_L315-338_
- inherits: `FOutputDataVertex`
- desc: Create a FOutputDataVertex with a templated MetaSound data type.
- L319 _public prototype_ `TOutputDataVertex() = default;`
- L322 _public function_ `template<typename... ArgTypes> FORCENOINLINE TOutputDataVertex(const FVertexName& InVertexName, const FDataVertexMetadata& InMetadata, ArgTypes&&... Args) : FOutputDataVertex(InVertexName, GetMetasoundDataTypeName<DataType>(), InMetadata, EVertexAccessType::Reference, Forward<ArgTypes>(Args)...)`
- L328 _public function_ `template<typename... ArgTypes> FORCENOINLINE TOutputDataVertex(const FLazyName& InVertexName, const FDataVertexMetadata& InMetadata, ArgTypes&&... Args) : FOutputDataVertex(InVertexName, GetMetasoundDataTypeName<DataType>(), InMetadata, EVertexAccessType::Reference, Forward<ArgTypes>(Args)...)`
- L334 _public function_ `template<typename... ArgTypes> FORCENOINLINE TOutputDataVertex(const char* InVertexName, const FDataVertexMetadata& InMetadata, ArgTypes&&... Args) : FOutputDataVertex(InVertexName, GetMetasoundDataTypeName<DataType>(), InMetadata, EVertexAccessType::Reference, Forward<ArgTypes>(Args)...)`

#### class `Metasound::TOutputConstructorVertex`  
`template<typename DataType> class TOutputConstructorVertex : public FOutputDataVertex`  
_L344-355_
- inherits: `FOutputDataVertex`
- desc: Create a FOutputDataVertex with a templated MetaSound data type which is only sets data at operator construction time.
- L348 _public prototype_ `TOutputConstructorVertex() = default;`
- L351 _public function_ `template<typename... ArgTypes> TOutputConstructorVertex(const FVertexName& InVertexName, const FDataVertexMetadata& InMetadata, ArgTypes&&... Args) : FOutputDataVertex(InVertexName, GetMetasoundDataTypeName<DataType>(), InMetadata, EVertexAccessType::Value, Forward<ArgTypes>(Args)...)`

#### class `Metasound::FEnvironmentVertex`  
`class FEnvironmentVertex`  
_L362-391_
- desc: FEnvironmentVertex A vertex for environment variables.
- L370 _public function_ `FEnvironmentVertex(const FVertexName& InVertexName, const FText& InDescription) : VertexName(InVertexName) #if WITH_EDITORONLY_DATA , Description(InDescription) #endif` — FEnvironmentVertex Construtor @InVertexName - Name of vertex. @InDescription - Human readable vertex description.
- L378 _public prototype_ `virtual ~FEnvironmentVertex() = default;`
- L381 _public member_ `FVertexName VertexName;` — Name of vertex.
- L385 _public member_ `FText Description;` — Description of the vertex.

#### class `Metasound::TVertexInterfaceImpl`  
`template<typename VertexType> class TVertexInterfaceImpl`  
_L397-551_
- desc: TVertexInterfaceImpls encapsulates multiple related data vertices. It requires that each vertex in the group have a unique FVertexName.
- L399 _private typedef_ `using FEqualVertexName = VertexPrivate::TEqualVertexName<VertexType>;`
- L401 _private function_ `void AddOrUpdateVertex(VertexType&& InVertex)`
- L414 _public typedef_ `using RangedForConstIteratorType = typename TArray<VertexType>::RangedForConstIteratorType;`
- L416 _public prototype_ `TVertexInterfaceImpl() = default;`
- L419 _public function_ `explicit TVertexInterfaceImpl(TArray<VertexType> InVertices) : Vertices(MoveTemp(InVertices))` — Construct with prebuilt array of vertices.
- L429 _public function_ `explicit TVertexInterfaceImpl(VertexTypes&&... InVertices)` — `UE_DEPRECATED(5.6, "Use the constructors of derived classes instead (FInputVertexInterface, FOutputVertexInterface, etc).")`
- L444 _public function_ `void Add(const VertexType& InVertex)` — Add a vertex.
- L449 _public function_ `void Add(VertexType&& InVertex)`
- L454 _public function_ `void Append(TArrayView<const VertexType> InVertices)`
- L463 _public function_ `bool Remove(const FVertexName& InKey)` — Remove a vertex by key.
- L470 _public function_ `bool Contains(const FVertexName& InKey) const` — Returns true if this contains a vertex with a matching key.
- L476 _public function_ `VertexType* Find(const FVertexName& InKey)` — Find a vertex with a given VertexName
- L482 _public function_ `const VertexType* Find(const FVertexName& InKey) const` — Find a vertex with a given VertexName
- L493 _public function_ `int32 GetSortOrderIndex(const FVertexName& InKey) const` — Return the sort order index of a vertex with the given name. @param InKey - FVertexName of vertex of interest. @return The index of the vertex. INDEX_NONE if the vertex does not exist.
- L499 _public function_ `const VertexType& operator[](const FVertexName& InName) const` — Return the vertex for a given vertex key.
- L507 _public function_ `RangedForConstIteratorType begin() const` — Iterator for ranged for loops.
- L513 _public function_ `RangedForConstIteratorType end() const` — Iterator for ranged for loops.
- L519 _public function_ `int32 Num() const` — Returns the number of vertices in the group.
- L525 _public function_ `const VertexType& At(int32 InIndex) const` — Return a vertex at an index.
- L531 _public function_ `VertexType& At(int32 InIndex)` — Return a vertex at an index.
- L550 _protected member_ `TArray<VertexType> Vertices;`

#### class `Metasound::VertexPrivate::FInputVertexInterfaceDeclarationBuilder`  
`class FInputVertexInterfaceDeclarationBuilder`  
_L585-611_
- desc: Interface builder for FInputVertexInterface declarations.
- L588 _public prototype_ `FInputVertexInterfaceDeclarationBuilder(TArray<FInputDataVertex>& OutVertices);`
- L591 _public function_ `template<typename... ArgTypes> void Build(ArgTypes&&... InArgs)`
- L608 _private prototype_ `void Add(FInputDataVertex&& InVertex);`
- L610 _private member_ `TArray<FInputDataVertex>& Vertices;`

#### class `Metasound::VertexPrivate::FOutputVertexInterfaceDeclarationBuilder`  
`class FOutputVertexInterfaceDeclarationBuilder`  
_L614-640_
- desc: Interface builder for FOutputVertexInterface declarations.
- L617 _public prototype_ `FOutputVertexInterfaceDeclarationBuilder(TArray<FOutputDataVertex>& OutVertices);`
- L620 _public function_ `template<typename... ArgTypes> void Build(ArgTypes&&... InArgs)`
- L637 _private prototype_ `void Add(FOutputDataVertex&& InVertex);`
- L639 _private member_ `TArray<FOutputDataVertex>& Vertices;`

#### class `Metasound::VertexPrivate::FEnvironmentDeclarationBuilder`  
`class FEnvironmentDeclarationBuilder`  
_L643-664_
- desc: Interface builder for FEnvironmentInterface declarations.
- L646 _public prototype_ `FEnvironmentDeclarationBuilder(TArray<FEnvironmentVertex>& OutVertices);`
- L649 _public function_ `template<typename... ArgTypes> void Build(ArgTypes&&... InArgs)`
- L663 _private member_ `TArray<FEnvironmentVertex>& Vertices;`

#### class `Metasound::FInputVertexInterface`  
`class FInputVertexInterface : public TVertexInterfaceImpl<FInputDataVertex>`  
_L668-705_
- inherits: `TVertexInterfaceImpl<FInputDataVertex>`
- desc: Interface representing the inputs of a node.
- L671 _public prototype_ `FInputVertexInterface();`
- L686 _public function_ `template<typename... ArgTypes> explicit FInputVertexInterface(ArgTypes && ... InArgs)` — Construct an FInputVertexInterface from a parameter pack. This allows node interfaces to be declared in a single function. For example: FInputVertexInterface Interface { TInputDataVertex<float>(...), TInputDataVertex<int32>(...), TInputDataVertex<float>(...) };
- L692 _public prototype_ `FInputVertexInterface(TArray<FInputDataVertex> InVertices, TArray<VertexPrivate::FSubInterfaceLayout> InSubInterfaces={});`
- L695 _public prototype_ `void ForEachSubInterfaceInstance(const FName& InSubInterfaceName, TFunctionRef<void (TConstArrayView<FInputDataVertex>)> Callable) const;` — Iterate through all repetitions of a sub interface.
- L697 _public prototype_ `void ForEachSubInterfaceInstance(const FName& InSubInterfaceName, TFunctionRef<void (TArrayView<FInputDataVertex>)> Callable);` — Iterate through all repetitions of a sub interface.
- L698 _public prototype_ `TConstArrayView<VertexPrivate::FSubInterfaceLayout> GetSubInterfaces(const VertexPrivate::FPrivateAccessTag& InTag) const;`
- L702 _private prototype_ `const VertexPrivate::FSubInterfaceLayout* FindSubInterfaceLayout(const FName& InName) const;`
- L704 _private member_ `TArray<VertexPrivate::FSubInterfaceLayout> SubInterfaces;`

#### class `Metasound::FOutputVertexInterface`  
`class FOutputVertexInterface : public TVertexInterfaceImpl<FOutputDataVertex>`  
_L708-749_
- inherits: `TVertexInterfaceImpl<FOutputDataVertex>`
- desc: Interface representing the outputs of a node.
- L711 _public prototype_ `FOutputVertexInterface();`
- L726 _public function_ `template<typename... ArgTypes> explicit FOutputVertexInterface(ArgTypes && ... InArgs) : FOutputVertexInterface()` — Construct an FOutputVertexInterface from a parameter pack. This allows node interfaces to be declared in a single function. For example: FOutputVertexInterface Interface { TOutputDataVertex<float>(...), TOutputDataVertex<int32>(...), TOutputDataVertex<float>(...) };
- L733 _public prototype_ `FOutputVertexInterface(TArray<FOutputDataVertex> InVertices, TArray<VertexPrivate::FSubInterfaceLayout> InSubInterfaces={});`
- L736 _public prototype_ `void ForEachSubInterfaceInstance(const FName& InSubInterfaceName, TFunctionRef<void (TConstArrayView<FOutputDataVertex>)> Callable) const;` — Iterate through all repetitions of a sub interface.
- L738 _public prototype_ `void ForEachSubInterfaceInstance(const FName& InSubInterfaceName, TFunctionRef<void (TArrayView<FOutputDataVertex>)> Callable);` — Iterate through all repetitions of a sub interface.
- L740 _public prototype_ `TConstArrayView<VertexPrivate::FSubInterfaceLayout> GetSubInterfaces(const VertexPrivate::FPrivateAccessTag& InTag) const;`
- L746 _private prototype_ `const VertexPrivate::FSubInterfaceLayout* FindSubInterfaceLayout(const FName& InName) const;`
- L748 _private member_ `TArray<VertexPrivate::FSubInterfaceLayout> SubInterfaces;`

#### class `Metasound::FEnvironmentVertexInterface`  
`class FEnvironmentVertexInterface : public TVertexInterfaceImpl<FEnvironmentVertex>`  
_L752-765_
- inherits: `TVertexInterfaceImpl<FEnvironmentVertex>`
- desc: Interface representing the environment variables used by a node.
- L755 _public prototype_ `FEnvironmentVertexInterface() = default;`
- L758 _public function_ `template<typename... ArgTypes> explicit FEnvironmentVertexInterface(ArgTypes && ... InArgs)`
- L764 _public prototype_ `explicit FEnvironmentVertexInterface(TArray<FEnvironmentVertex> InVertices);`

#### class `Metasound::FVertexInterface`  
`class FVertexInterface`  
_L770-833_
- desc: FVertexInterface provides access to a collection of input and output vertex interfaces.
- L775 _public prototype_ `FVertexInterface();` — Default constructor.
- L778 _public prototype_ `FVertexInterface(const FInputVertexInterface& InInputs, const FOutputVertexInterface& InOutputs);` — Construct with an input and output interface.
- L781 _public prototype_ `FVertexInterface(FInputVertexInterface InInputs, FOutputVertexInterface InOutputs, FEnvironmentVertexInterface InEnvironmentVariables);` — Construct with input, output and environment interface.
- L784 _public prototype_ `~FVertexInterface();` — Destructor.
- L787 _public prototype_ `const FInputVertexInterface& GetInputInterface() const;` — Return the input interface.
- L790 _public prototype_ `FInputVertexInterface& GetInputInterface();` — Return the input interface.
- L793 _public prototype_ `const FInputDataVertex& GetInputVertex(const FVertexName& InKey) const;` — Return an input vertex.
- L796 _public prototype_ `bool ContainsInputVertex(const FVertexName& InKey) const;` — Returns true if an input vertex with the given key exists.
- L799 _public prototype_ `const FOutputVertexInterface& GetOutputInterface() const;` — Return the output interface.
- L802 _public prototype_ `FOutputVertexInterface& GetOutputInterface();` — Return the output interface.
- L805 _public prototype_ `const FOutputDataVertex& GetOutputVertex(const FVertexName& InName) const;` — Return an output vertex.
- L808 _public prototype_ `bool ContainsOutputVertex(const FVertexName& InName) const;` — Returns true if an output vertex with the given name exists.
- L811 _public prototype_ `const FEnvironmentVertexInterface& GetEnvironmentInterface() const;` — Return the output interface.
- L814 _public prototype_ `FEnvironmentVertexInterface& GetEnvironmentInterface();` — Return the output interface.
- L817 _public prototype_ `const FEnvironmentVertex& GetEnvironmentVertex(const FVertexName& InKey) const;` — Return an output vertex.
- L820 _public prototype_ `bool ContainsEnvironmentVertex(const FVertexName& InKey) const;` — Returns true if an output vertex with the given key exists.
- L830 _private member_ `FInputVertexInterface InputInterface;`
- L831 _private member_ `FOutputVertexInterface OutputInterface;`
- L832 _private member_ `FEnvironmentVertexInterface EnvironmentInterface;`

#### struct `Metasound::FSubInterfaceDescription`  
`struct FSubInterfaceDescription`  
_L836-842_
- desc: A description of a sub interface which is used when declaring a FClassInterface
- L838 _public member_ `FName SubInterfaceName;`
- L839 _public member_ `uint32 Min;` — Minimum number of instances of the sub interface.
- L840 _public member_ `uint32 Max;` — Maximum number of instances of the sub interface.
- L841 _public member_ `uint32 NumDefault;` — Default number of instances of the sub interface if desired num is unspecified.

#### class `Metasound::FVariantVertex`  
`class FVariantVertex`  
_L853-880_
- desc: A variant vertex represents a vertex that has a variant data type. Vertices are associated with a variant by using the VariantName. Multiple vertices may share the same variant.
- L858 _protected prototype_ `FVariantVertex(const FVertexName& InVertexName, const FVertexName& InVariantName, const FDataVertexMetadata& InMetadata, EVertexAccessType InAccessType);` — Derived classes using this constructor must remember to initialize the DataTypeNames array
- L862 _public prototype_ `FVariantVertex(const FVertexName& InVertexName, const FName& InVariantName, const TArray<FName>& InDataTypeNames, const FDataVertexMetadata& InMetadata, EVertexAccessType InAccessType);`
- L865 _public member_ `FVertexName VertexName;` — Name of vertex.
- L868 _public member_ `FName VariantName;` — Name of variant associated with the vertex.
- L871 _public member_ `TArray<FName> DataTypeNames;` — Possible data types supported by the variant.
- L875 _public member_ `FDataVertexMetadata Metadata;` — Metadata associated with vertex.
- L879 _public member_ `EVertexAccessType AccessType;` — Access type of the vertex.

#### class `Metasound::FInputVariantVertex`  
`class FInputVariantVertex : public FVariantVertex`  
_L885-900_
- inherits: `FVariantVertex`
- desc: An input variant vertex represents an input vertex that has a variant data type. Vertices are associated with a variant by using the VariantName. Multiple vertices may share the same variant.
- L890 _protected prototype_ `FInputVariantVertex(const FVertexName& InVertexName, const FName& InVariantName, const FDataVertexMetadata& InMetadata, EVertexAccessType InAccessType);` — Derived classes using this constructor must remember to initialize the DataTypeNames array and Literals array.
- L893 _public prototype_ `FInputVariantVertex(const FVertexName& InVertexName, const FName& InVariantName, const TArray<FName>& InDataTypeNames, const FDataVertexMetadata& InMetadata, EVertexAccessType InAccessType, const TArray<FLiteral>& InLiterals);`
- L895 _public member_ `TArray<FLiteral> Literals;`

#### class `Metasound::FOutputVariantVertex`  
`class FOutputVariantVertex : public FVariantVertex`  
_L905-913_
- inherits: `FVariantVertex`
- desc: An output variant vertex represents an output vertex that has a variant data type. Vertices are associated with a variant by using the VariantName. Multiple vertices may share the same variant.

#### class `Metasound::TInputVariantVertex`  
`template<typename ... DataTypes> class TInputVariantVertex : public FInputVariantVertex`  
_L956-978_
- inherits: `FInputVariantVertex`
- desc: An input variant vertex represents an input vertex that has a variant data type. Vertices are associated with a variant by using the VariantName. Multiple vertices may share the same variant. The supported data types of the variant are declared by the template arguments to the vertex. TInputVariantVertex<float, int32>(...) will produce a variant which supports float or int32.
- L959 _public prototype_ `TInputVariantVertex() = default;`
- L962 _public function_ `template<typename... ArgTypes> FORCENOINLINE TInputVariantVertex(const FVertexName& InVertexName, const FVertexName& InVariantName, const FDataVertexMetadata& InMetadata, ArgTypes&&... Args) : FInputVariantVertex(InVertexName, InVariantName, InMetadata, EVertexAccessType::Reference)`
- L974 _public function_ `template<typename... ArgTypes> FORCENOINLINE TInputVariantVertex(const FVertexName& InVertexName, const FDataVertexMetadata& InMetadata, ArgTypes&&... Args) : TInputVariantVertex(InVertexName, InVertexName, InMetadata, Forward<ArgTypes>(Args)...)` — Vertex w/ variant name matching vertex name.

#### class `Metasound::TOutputVariantVertex`  
`template<typename ... DataTypes> class TOutputVariantVertex : public FOutputVariantVertex`  
_L989-1008_
- inherits: `FOutputVariantVertex`
- desc: An output variant vertex represents an output vertex that has a variant data type. Vertices are associated with a variant by using the VariantName. Multiple vertices may share the same variant. The supported data types of the variant are declared by the template arguments to the vertex. TOutputVariantVertex<float, int32>(...) will produce a variant which supports float or int32.
- L992 _public prototype_ `TOutputVariantVertex() = default;`
- L994 _public function_ `FORCENOINLINE TOutputVariantVertex(const FVertexName& InVertexName, const FVertexName& InVariantName, const FDataVertexMetadata& InMetadata) : FOutputVariantVertex(InVertexName, InVariantName, InMetadata, EVertexAccessType::Reference)`
- L1004 _public function_ `FORCENOINLINE TOutputVariantVertex(const FVertexName& InVertexName, const FDataVertexMetadata& InMetadata) : TOutputVariantVertex(InVertexName, InVertexName, InMetadata)` — Vertex with variant name matching vertex name.

#### struct `Metasound::VertexPrivate::FClassInterfaceData`  
`struct FClassInterfaceData`  
_L1021-1034_
- desc: Data structure used to efficiently store class declarations w/o introducing unneeded allocations. FClassInterfaceData generally only lives for the duration of a function call.
- L1023 _public member_ `TArray<FSubInterfaceDescription, TInlineAllocator<4>> SubInterfaces;`
- L1024 _public member_ `TArray<FSubInterfaceClassLayout, TInlineAllocator<2>> InputSubInterfaceLayouts;`
- L1025 _public member_ `TArray<FSubInterfaceClassLayout, TInlineAllocator<2>> OutputSubInterfaceLayouts;`
- L1027 _public member_ `TSortedMap<FVertexKey, uint8, TInlineAllocator<4>> VertexKeyToVariantIndex;`
- L1028 _public member_ `TArray<FVariantDescription, TInlineAllocator<4>> Variants;`
- L1029 _public member_ `TSortedVertexNameMap<TArray<FLiteral, TInlineAllocator<4>>, TInlineAllocator<4>> VariantLiterals;`
- L1031 _public member_ `TArray<FInputDataVertex, TInlineAllocator<8>> Inputs;`
- L1032 _public member_ `TArray<FOutputDataVertex, TInlineAllocator<8>> Outputs;`
- L1033 _public member_ `TArray<FEnvironmentVertex, TInlineAllocator<4>> EnvironmentVariables;`

#### struct `Metasound::VertexPrivate::FVariantSchema`  
`struct FVariantSchema`  
_L1037-1044_
- desc: Stores information to describe variants on a class interface
- L1039 _public member_ `TSortedMap<VertexPrivate::FVertexKey, uint8> VertexKeyToVariantIndex;`
- L1040 _public member_ `TArray<FVariantDescription> Variants;`
- L1041 _public member_ `TSortedVertexNameMap<TArray<FLiteral, TInlineAllocator<2>>> VariantLiterals;`
- L1043 _public prototype_ `static FVariantSchema FromClassInterfaceData(const VertexPrivate::FClassInterfaceData& InClassInterfaceData);`

#### struct `Metasound::VertexPrivate::FSubInterfaceSchema`  
`struct FSubInterfaceSchema`  
_L1047-1054_
- desc: Stores information to describe sub interfaces on a class interface.
- L1049 _public member_ `TArray<FSubInterfaceDescription> SubInterfaces;`
- L1050 _public member_ `TArray<VertexPrivate::FSubInterfaceClassLayout> InputSubInterfaceLayouts;`
- L1051 _public member_ `TArray<VertexPrivate::FSubInterfaceClassLayout> OutputSubInterfaceLayouts;`
- L1053 _public prototype_ `static FSubInterfaceSchema FromClassInterfaceData(const VertexPrivate::FClassInterfaceData& InClassInterfaceData);`

#### class `Metasound::VertexPrivate::FClassInterfaceDataBuilder`  
`class FClassInterfaceDataBuilder`  
_L1073-1103_
- desc: The FClassInterfaceDataBuilder assembles declared inputs, outputs, variants and subinterfaces into a FClassInterfaceData object. This is largely to simply the task of node authors when they declare a nodes interface. Instead of building an interface sequentially, they can declare the interface and allow the builder to build the correct object. e.g: FClassInterface ClassInterface = CreateClassInterface( TInputDataVertex<float>(...) FSubInterface{ "MySub", TInputVariantVertex<float, int32>(...) } TOutDataVertex<FAudioBuffer>(...) );
- L1077 _public function_ `template<typename ... Args> FClassInterfaceDataBuilder& Build(Args&& ... InArgs)`
- L1083 _public prototype_ `const FClassInterfaceData& GetClassInterfaceData() const;`
- L1086 _private prototype_ `void Add(const FInputDataVertex* InInputVertex);`
- L1087 _private prototype_ `void Add(const FOutputDataVertex* InOutputVertex);`
- L1088 _private prototype_ `void Add(const FEnvironmentVertex* InEnvironmentVertex);`
- L1090 _private prototype_ `void Add(const FSubInterfaceDescription* InSubInterfaceDescription);`
- L1091 _private prototype_ `void Add(const FSubInterface* InSubInterface);`
- L1092 _private prototype_ `void Add(const FInputVariantVertex* InInputVariantVertex);`
- L1093 _private prototype_ `void Add(const FOutputVariantVertex* InOutputVariantVertex);`
- L1095 _private prototype_ `bool ContainsAnySubInterfaces() const;`
- L1096 _private prototype_ `void AddSubInterfaceVertices(const FName& InSubInterfaceName, const FClassInterfaceData& InSubInterfaceData);`
- L1097 _private prototype_ `void MergeSubInterfaceVariantData(const FClassInterfaceData& InSubInterfaceData);`
- L1099 _private prototype_ `uint8 FindOrAddVariant(const FVariantVertex& InVariantVertex);`
- L1100 _private prototype_ `int32 IndexOfVariant(const FName& InName) const;`
- L1102 _private member_ `FClassInterfaceData ClassInterfaceData;`

#### class `Metasound::VertexPrivate::FBuildableInterface`  
`class FBuildableInterface`  
_L1106-1124_
- desc: FBuildableInterface supports composition when declaring FSubInterfaces
- L1109 _public prototype_ `FBuildableInterface() = default;`
- L1110 _public prototype_ `FBuildableInterface(const FBuildableInterface&) = default;`
- L1111 _public prototype_ `FBuildableInterface(FBuildableInterface&&) = default;`
- L1114 _public function_ `template<class FirstArgType, class... AdditionalArgTypes> FBuildableInterface(FirstArgType&& InFirstArg, AdditionalArgTypes&&... InAdditionalArgs)`
- L1120 _public prototype_ `const FClassInterfaceDataBuilder& GetClassInterfaceDataBuilder() const;`
- L1123 _private member_ `FClassInterfaceDataBuilder Builder;`

#### class `Metasound::FSubInterface`  
`class FSubInterface : public VertexPrivate::FBuildableInterface`  
_L1128-1142_
- inherits: `VertexPrivate::FBuildableInterface`
- L1132 _public function_ `template<typename ... ArgTypes> FSubInterface(FLazyName InName, ArgTypes&&... InArgs) : FBuildableInterface(Forward<ArgTypes>(InArgs)...) , SubInterfaceName(InName)`
- L1138 _public prototype_ `const FName GetName() const;`
- L1141 _private member_ `FName SubInterfaceName;`

#### class `Metasound::FClassInterface`  
`class FClassInterface`  
_L1150-1216_
- desc: An FClassInterface defines the class interface of a MetaSound C++ node class. This interface may contain basic vertices, but also subinterfaces and variants. The FClassInterface is used to create the FVertexInterface for individual node instances. It does so by combining the FClassInterface definition with subinterface and variant configurations.
- L1153 _public prototype_ `FClassInterface() = default;`
- L1154 _public prototype_ `~FClassInterface() = default;`
- L1157 _public prototype_ `FClassInterface(const FClassInterface& Other);` — Copy constructor (deep-copies schema data).
- L1160 _public prototype_ `FClassInterface& operator=(const FClassInterface& Other);` — Copy assignment (deep-copies schema data).
- L1163 _public prototype_ `FClassInterface(FClassInterface&&) = default;` — Move constructor.
- L1166 _public prototype_ `FClassInterface& operator=(FClassInterface&&) = default;` — Move assignment.
- L1170 _public prototype_ `FClassInterface(const FVertexInterface& InVertexInterface);` — Construct from a FVertexInterface. The resulting FClassInterface has no sub-interfaces or variants — it simply wraps the flat vertex lists.
- L1174 _public prototype_ `operator FVertexInterface() const;` — Conversion to FVertexInterface. Returns the default-configured interface (no sub-interface or variant configurations).
- L1177 _public prototype_ `FClassInterface(const VertexPrivate::FClassInterfaceData& InClassInterfaceData);`
- L1180 _public prototype_ `FVertexInterface CreateVertexInterface() const;` — Create a FVertexInterface with default configuration (no sub-interface or variant overrides).
- L1183 _public prototype_ `FVertexInterface CreateVertexInterface(const TMap<FName, uint32>& InSubInterfaceCounts, const TMap<FName, FName>& InVariantSelections) const;` — Create a FVertexInterface with the given configuration.
- L1186 _public prototype_ `TConstArrayView<FSubInterfaceDescription> GetSubInterfaceDescriptions() const;` — Return any sub interfaces on this class interface.
- L1189 _public prototype_ `TConstArrayView<FVariantDescription> GetVariantDescriptions() const;` — Return any variants on this class interface.
- L1193 _public prototype_ `const FVariantDescription* FindVariantDescriptionForInput(const FVertexName& InVertexName) const;` — Return a variant description for a given input vertex if the vertex is associated with a variant.
- L1197 _public prototype_ `const FVariantDescription* FindVariantDescriptionForOutput(const FVertexName& InVertexName) const;` — Return a variant description for a given output vertex if the vertex is associated with a variant.
- L1200 _public function_ `bool ContainsSubInterfaces() const` — Returns true if this class interface contains sub-interface definitions.
- L1203 _public function_ `bool ContainsVariants() const` — Returns true if this class interface contains variant definitions.
- L1210 _private member_ `TUniquePtr<VertexPrivate::FVariantSchema> VariantSchema;` — Many nodes do not need this extra configurable information. Save on memory storage by offloading this extra functionality behind a unique ptr. Deep-copied in copy constructor/assignment to preserve value semantics.
- L1211 _private member_ `TUniquePtr<VertexPrivate::FSubInterfaceSchema> SubInterfaceSchema;`
- L1213 _private member_ `TArray<FInputDataVertex, TInlineAllocator<1>> Inputs;`
- L1214 _private member_ `TArray<FOutputDataVertex, TInlineAllocator<1>> Outputs;`
- L1215 _private member_ `TArray<FEnvironmentVertex> EnvironmentVariables;`

#### struct `Metasound::FNodeInitData`  
`struct FNodeInitData`  
_L1240-1244_
- desc: This struct is used to pass in any arguments required for constructing a single node instance. because of this, all FNode implementations have to implement a constructor that takes an FNodeInitData instance.
- L1242 _public member_ `FVertexName InstanceName;`
- L1243 _public member_ `FGuid InstanceID;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L16 _namespace_ `namespace Metasound`
- L19 _typedef_ `using FVertexName = FName;` (scope `Metasound`) — Name of a given vertex.  Only unique for a given node interface.
- L30 _namespace_ `namespace VertexPrivate` (scope `Metasound`)
- L38 _namespace_ `namespace SubInterface` (scope `Metasound::VertexPrivate`)
- L42 _variable_ `static constexpr uint16 InvalidInstancePosition = TNumericLimits<uint16>::Max();` (scope `Metasound::VertexPrivate::SubInterface`) — These are utilized to make sure we don't overflow uint16 capacity in case someone declares a ridiculously large interface.
- L43 _variable_ `static constexpr uint16 MaxInstancePosition = TNumericLimits<uint16>::Max() - 1;` (scope `Metasound::VertexPrivate::SubInterface`)
- L44 _variable_ `static constexpr uint16 MinInstancePosition = 0;` (scope `Metasound::VertexPrivate::SubInterface`)
- L82 _function_ `friend bool operator==(const FVertexKey& InLHS, const FVertexKey& InRHS)` (scope `Metasound::VertexPrivate`)
- L87 _function_ `friend bool operator<(const FVertexKey& InLHS, const FVertexKey& InRHS)` (scope `Metasound::VertexPrivate`)
- L142 _typedef_ `template<typename ValueType, typename AllocatorType=FDefaultAllocator> using TSortedVertexNameMap = TSortedMap<FVertexName, ValueType, AllocatorType, FNameFastLess>;` (scope `Metasound`) — Convenience for using a TSortedMap with FVertexName Key type. This template makes it convenient to create a TSortedMap with an FVertexName while also avoiding compilation errors incurred from using the FName default "less than" operator in the TSortedMap implementation. - FVertexName is an alias to FName. - TSortedMap<FName, ValueType> fails to compile since the "less than" operator specific implementation needs to be chosen (FastLess vs LexicalLess) - Due to the template argument order of TSortedMap this also forces you to choose the allocator. - This is all a bit of an annoyance to do every time we use a TSortedMap with an FVertexName as the key.
- L537 _function_ `friend bool operator==(const TVertexInterfaceImpl<VertexType>& InLHS, const TVertexInterfaceImpl<VertexType>& InRHS)` (scope `Metasound`) — Compare whether two vertex interfaces are equal.
- L543 _function_ `friend bool operator!=(const TVertexInterfaceImpl<VertexType>& InLHS, const TVertexInterfaceImpl<VertexType>& InRHS)` (scope `Metasound`) — Compare whether two vertex interfaces are unequal.
- L554 _typedef_ `template<typename VertexType> using TVertexInterfaceGroup UE_DEPRECATED(5.6, "Use TVertexInterfaceImpl instead") = T` (scope `Metasound`)
- L556 _namespace_ `namespace VertexPrivate` (scope `Metasound`)
- L848 _externvar_ `extern const FLazyName GVariantDataTypeName;` (scope `Metasound`) — The data type name used for a variant vertex which has not been given a concrete MetaSound data type.
- L915 _namespace_ `namespace VertexPrivate` (scope `Metasound`)
- L918 _function_ `template<typename ... DataTypes> void BuildArrayOfTypeNames(TArray<FName>& InOutArray)` (scope `Metasound::VertexPrivate`)
- L927 _function_ `template<typename ... ArgTypes> void BuildArrayOfLiterals(int32 InNumDataTypes, TArray<FLiteral>& InOutArray, ArgTypes&&...Args)` (scope `Metasound::VertexPrivate`)
- L1016 _namespace_ `namespace VertexPrivate` (scope `Metasound`)
- L1231 _function_ `template<typename ... ArgTypes> FClassInterface CreateClassInterface(ArgTypes&& ... InArgs)` (scope `Metasound`) — Create a FClassInterface by declaring the vertices, subinterfaces and variants. e.g: FClassInterface ClassInterface = CreateClassInterface( TInputDataVertex<float>(...) FSubInterface{ "MySub", TInputVariantVertex<float, int32>(...) } TOutDataVertex<FAudioBuffer>(...) );
- L1248 _prototype_ `FString LexToString(Metasound::EVertexAccessType InAccessType);` — Convert EVertexAccessType to string

### `Plugins/Runtime/Metasound/Source/MetasoundGraphCore/Public/MetasoundVertexData.h` (Public)


#### struct `Metasound::VertexDataPrivate::TGetVertexAccess`  
`template<typename ...> struct TGetVertexAccess`  
_L41-43_
- desc: Helper for getting a EVertexAccessType from a TData*Reference<DataType> object
- L48 _public member_ `static constexpr EVertexAccessType VertexAccess = EVertexAccessType::Reference;`
- L60 _public member_ `static constexpr EVertexAccessType VertexAccess = EVertexAccessType::Value;`

#### struct `Metasound::VertexDataPrivate::TGetVertexAccess`  
`template<typename DataType> struct TGetVertexAccess<TDataReadReference<DataType>>`  
_L46-49_
- L48 _public member_ `static constexpr EVertexAccessType VertexAccess = EVertexAccessType::Reference;`
- L60 _public member_ `static constexpr EVertexAccessType VertexAccess = EVertexAccessType::Value;`

#### struct `Metasound::VertexDataPrivate::TGetVertexAccess`  
`template<typename DataType> struct TGetVertexAccess<TDataWriteReference<DataType>>`  
_L52-55_
- L48 _public member_ `static constexpr EVertexAccessType VertexAccess = EVertexAccessType::Reference;`
- L60 _public member_ `static constexpr EVertexAccessType VertexAccess = EVertexAccessType::Value;`

#### struct `Metasound::VertexDataPrivate::TGetVertexAccess`  
`template<typename DataType> struct TGetVertexAccess<TDataValueReference<DataType>>`  
_L58-61_
- L48 _public member_ `static constexpr EVertexAccessType VertexAccess = EVertexAccessType::Reference;`
- L60 _public member_ `static constexpr EVertexAccessType VertexAccess = EVertexAccessType::Value;`

#### struct `Metasound::VertexDataPrivate::TGetReferenceDataTypeT`  
`template<typename ...> struct TGetReferenceDataTypeT`  
_L67-70_
- desc: TGetReferencDataTypeT is a template trait which determines the underlying type stored in a data reference
- L75 _public typedef_ `using Type = DataType;`

#### struct `Metasound::VertexDataPrivate::TGetReferenceDataTypeT`  
`template<typename DataType> struct TGetReferenceDataTypeT<TDataReadReference<DataType>>`  
_L73-76_
- L75 _public typedef_ `using Type = DataType;`

#### struct `Metasound::VertexDataPrivate::TGetReferenceDataTypeT`  
`template<typename DataType> struct TGetReferenceDataTypeT<TDataWriteReference<DataType>>`  
_L79-82_
- L75 _public typedef_ `using Type = DataType;`

#### struct `Metasound::VertexDataPrivate::TGetReferenceDataTypeT`  
`template<typename DataType> struct TGetReferenceDataTypeT<TDataValueReference<DataType>>`  
_L85-88_
- L75 _public typedef_ `using Type = DataType;`

#### struct `Metasound::VertexDataPrivate::TFactoryFacade`  
`template<typename Type> struct TFactoryFacade`  
_L98-110_
- desc: TFactoryFacace is a factory for data types which uses the class template type to determine which flavor of DataReference to create.
- L100 _public function_ `static Type CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L106 _public function_ `template<typename ... ArgTypes> static Type CreateWithArgs(ArgTypes&&... Args)`
- L115 _public function_ `static TDataReadReference<DataType> CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L121 _public function_ `template<typename ... ArgTypes> static TDataReadReference<DataType> CreateWithArgs(ArgTypes&&... Args)`
- L130 _public function_ `static TDataWriteReference<DataType> CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L136 _public function_ `template<typename ... ArgTypes> static TDataWriteReference<DataType> CreateWithArgs(ArgTypes&&... Args)`
- L145 _public function_ `static TDataValueReference<DataType> CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L151 _public function_ `template<typename ... ArgTypes> static TDataValueReference<DataType> CreateWithArgs(ArgTypes&&... Args)`

#### struct `Metasound::VertexDataPrivate::TFactoryFacade`  
`template<typename DataType> struct TFactoryFacade<TDataReadReference<DataType>>`  
_L113-125_
- L100 _public function_ `static Type CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L106 _public function_ `template<typename ... ArgTypes> static Type CreateWithArgs(ArgTypes&&... Args)`
- L115 _public function_ `static TDataReadReference<DataType> CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L121 _public function_ `template<typename ... ArgTypes> static TDataReadReference<DataType> CreateWithArgs(ArgTypes&&... Args)`
- L130 _public function_ `static TDataWriteReference<DataType> CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L136 _public function_ `template<typename ... ArgTypes> static TDataWriteReference<DataType> CreateWithArgs(ArgTypes&&... Args)`
- L145 _public function_ `static TDataValueReference<DataType> CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L151 _public function_ `template<typename ... ArgTypes> static TDataValueReference<DataType> CreateWithArgs(ArgTypes&&... Args)`

#### struct `Metasound::VertexDataPrivate::TFactoryFacade`  
`template<typename DataType> struct TFactoryFacade<TDataWriteReference<DataType>>`  
_L128-140_
- L100 _public function_ `static Type CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L106 _public function_ `template<typename ... ArgTypes> static Type CreateWithArgs(ArgTypes&&... Args)`
- L115 _public function_ `static TDataReadReference<DataType> CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L121 _public function_ `template<typename ... ArgTypes> static TDataReadReference<DataType> CreateWithArgs(ArgTypes&&... Args)`
- L130 _public function_ `static TDataWriteReference<DataType> CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L136 _public function_ `template<typename ... ArgTypes> static TDataWriteReference<DataType> CreateWithArgs(ArgTypes&&... Args)`
- L145 _public function_ `static TDataValueReference<DataType> CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L151 _public function_ `template<typename ... ArgTypes> static TDataValueReference<DataType> CreateWithArgs(ArgTypes&&... Args)`

#### struct `Metasound::VertexDataPrivate::TFactoryFacade`  
`template<typename DataType> struct TFactoryFacade<TDataValueReference<DataType>>`  
_L143-155_
- L100 _public function_ `static Type CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L106 _public function_ `template<typename ... ArgTypes> static Type CreateWithArgs(ArgTypes&&... Args)`
- L115 _public function_ `static TDataReadReference<DataType> CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L121 _public function_ `template<typename ... ArgTypes> static TDataReadReference<DataType> CreateWithArgs(ArgTypes&&... Args)`
- L130 _public function_ `static TDataWriteReference<DataType> CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L136 _public function_ `template<typename ... ArgTypes> static TDataWriteReference<DataType> CreateWithArgs(ArgTypes&&... Args)`
- L145 _public function_ `static TDataValueReference<DataType> CreateWithLiteral(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L151 _public function_ `template<typename ... ArgTypes> static TDataValueReference<DataType> CreateWithArgs(ArgTypes&&... Args)`

#### struct `Metasound::VertexDataPrivate::TTriggerDeprecatedBindAPIWarning`  
`template<typename T> struct TTriggerDeprecatedBindAPIWarning`  
_L158-160_
- L166 _public function_ `inline void Trigger()` — `UE_DEPRECATED(5.6, "Please use a non-const lvalue reference for data references passed to this function. Const data references can sometimes be created by passing in temporary objects and/or triggering implicit conversion.")`

#### struct `Metasound::VertexDataPrivate::TTriggerDeprecatedBindAPIWarning`  
`template<typename T> struct TTriggerDeprecatedBindAPIWarning<const T>`  
_L163-169_
- L166 _public function_ `inline void Trigger()` — `UE_DEPRECATED(5.6, "Please use a non-const lvalue reference for data references passed to this function. Const data references can sometimes be created by passing in temporary objects and/or triggering implicit conversion.")`

#### class `Metasound::VertexDataPrivate::FInputBinding`  
`class FInputBinding`  
_L172-320_
- desc: An input binding which connects an FInputVertex to a IDataReference
- L176 _public prototype_ `FInputBinding(FInputDataVertex&& InVertex);`
- L177 _public prototype_ `FInputBinding(const FInputDataVertex& InVertex);`
- L178 _public prototype_ `FInputBinding(const FVertexName& InVertexName, FAnyDataReference&& InReference);`
- L181 _public function_ `template<typename DataReferenceType> void BindRead(DataReferenceType& InOutDataReference)`
- L194 _public function_ `template<typename DataType> void BindWrite(TDataWriteReference<DataType>& InOutDataReference)`
- L207 _public function_ `template<typename DataReferenceType> void Bind(DataReferenceType& InOutDataReference)`
- L236 _public prototype_ `void Bind(FInputBinding& InBinding);`
- L240 _public function_ `template<typename DataReferenceType> void Set(const DataReferenceType& InDataReference)` — Set the data reference, overwriting any existing bound data references
- L251 _public prototype_ `void Set(FAnyDataReference&& InAnyDataReference);` — Set the data reference, overwriting any existing bound data references
- L253 _public prototype_ `const FInputDataVertex& GetVertex() const;`
- L255 _public prototype_ `void SetDefaultLiteral(const FLiteral& InLiteral);`
- L257 _public prototype_ `bool IsBound() const;`
- L259 _public prototype_ `EDataReferenceAccessType GetAccessType() const;`
- L261 _public prototype_ `const FAnyDataReference* GetDataReference() const;`
- L263 _public prototype_ `FDataReferenceID GetDataReferenceID() const;`
- L268 _public function_ `template<typename AsType> AsType GetDataReferenceAs() const` — Get the bound data reference. This assumes the data reference exists and is convertible to the AsType.
- L278 _public function_ `template<typename AsType> AsType GetOrCreateDefaultAs(const FOperatorSettings& InSettings) const` — Get the bound data reference if it exists. Otherwise create and return a data reference by constructing one using the Vertex's default literal.
- L294 _public function_ `template<typename AsType, typename ... ArgTypes> AsType GetOrConstructAs(ArgTypes&&... Args) const` — Get the bound data reference if it exists. Otherwise create and return a data reference by constructing one the supplied constructor arguments.
- L309 _public function_ `template<typename DataType> void SetValue(const DataType& InValue)` — Set the value with a constant value reference.
- L318 _private member_ `FInputDataVertex Vertex;`
- L319 _private member_ `TOptional<FAnyDataReference> Data;`

#### class `Metasound::VertexDataPrivate::FOutputBinding`  
`class FOutputBinding`  
_L324-443_
- desc: Binds an IDataReference to a FOutputDataVertex
- L327 _public prototype_ `FOutputBinding(FOutputDataVertex&& InVertex);`
- L328 _public prototype_ `FOutputBinding(const FOutputDataVertex& InVertex);`
- L329 _public prototype_ `FOutputBinding(const FVertexName& InVertexName, FAnyDataReference&& InReference);`
- L332 _public function_ `template<typename DataType> void BindValue(const TDataValueReference<DataType>& InOutDataReference)`
- L338 _public function_ `template<typename DataReferenceType> void BindRead(DataReferenceType& InOutDataReference)`
- L344 _public function_ `template<typename DataType> void BindReadFromAny(FAnyDataReference& InOutDataReference)`
- L350 _public function_ `template<typename DataType> void BindWrite(TDataWriteReference<DataType>& InOutDataReference)`
- L356 _public function_ `template<typename DataReferenceType> void Bind(DataReferenceType& InOutDataReference)`
- L378 _public prototype_ `void Bind(FOutputBinding& InBinding);`
- L382 _public function_ `template<typename DataReferenceType> void Set(const DataReferenceType& InDataReference)` — Set the data reference, overwriting any existing bound data references
- L393 _public prototype_ `void Set(FAnyDataReference&& InAnyDataReference);` — Set the data reference, overwriting any existing bound data references
- L395 _public prototype_ `const FOutputDataVertex& GetVertex() const;`
- L397 _public prototype_ `bool IsBound() const;`
- L399 _public prototype_ `EDataReferenceAccessType GetAccessType() const;`
- L402 _public prototype_ `const FAnyDataReference* GetDataReference() const;` — Get data reference
- L404 _public prototype_ `FDataReferenceID GetDataReferenceID() const;`
- L409 _public function_ `template<typename AsType> AsType GetDataReferenceAs() const` — Get the bound data reference. This assumes the data reference exists and is convertible to the AsType.
- L419 _public function_ `template<typename AsType, typename ... ArgTypes> AsType GetOrConstructAs(ArgTypes&&... Args) const` — Get the bound data reference if it exists. Otherwise create and return a data reference by constructing one the supplied constructor arguments.
- L433 _public function_ `template<typename DataType> void SetValue(const DataType& InValue)` — Set the value with a constant value reference.
- L441 _private member_ `FOutputDataVertex Vertex;`
- L442 _private member_ `TOptional<FAnyDataReference> Data;`

#### struct `Metasound::VertexDataPrivate::TCreateInputBinding`  
`template<typename DataReferenceType> struct TCreateInputBinding`  
_L448-463_
- desc: Functor for creating a new FInputBinding from a IDataReference derived class and a vertex name.
- L450 _public member_ `const FVertexName& VertexName;`
- L451 _public member_ `DataReferenceType& Ref;`
- L453 _public function_ `TCreateInputBinding(const FVertexName& InVertexName, DataReferenceType& InRef) : VertexName(InVertexName) , Ref(InRef)`
- L458 _public function_ `FInputBinding operator()() const`

#### struct `Metasound::VertexDataPrivate::TCreateOutputBinding`  
`template<typename DataReferenceType> struct TCreateOutputBinding`  
_L467-482_
- desc: Functor for creating a new FOutputBinding from a IDataReference derived class and a vertex name.
- L469 _public member_ `const FVertexName& VertexName;`
- L470 _public member_ `DataReferenceType& Ref;`
- L472 _public function_ `TCreateOutputBinding(const FVertexName& InVertexName, DataReferenceType& InRef) : VertexName(InVertexName) , Ref(InRef)`
- L477 _public function_ `FOutputBinding operator()() const`

#### class `Metasound::FInputVertexInterfaceData`  
`class FInputVertexInterfaceData`  
_L539-994_
- desc: An input vertex interface with optionally bound data references.
- L541 _private typedef_ `using FInputBinding = VertexDataPrivate::FInputBinding;`
- L545 _public typedef_ `using FRangedForIteratorType = typename TArray<FInputBinding>::RangedForIteratorType;`
- L546 _public typedef_ `using FRangedForConstIteratorType = typename TArray<FInputBinding>::RangedForConstIteratorType;`
- L549 _public prototype_ `FInputVertexInterfaceData();` — Construct with an FInputVertexInterface. This will default to a unfrozen vertex interface.
- L552 _public prototype_ `FInputVertexInterfaceData(const FInputVertexInterface& InVertexInterface);` — Construct with an FInputVertexInterface. This will default to a frozen vertex interface.
- L555 _public prototype_ `bool IsVertexInterfaceFrozen() const;` — Returns true if the vertex interface is frozen.
- L564 _public prototype_ `void SetIsVertexInterfaceFrozen(bool bInIsVertexInterfaceFrozen);` — Set whether the vertex interface is frozen or not. If frozen, attempts to access vertices which do not already exist will result in an error. If not frozen, attempts to bind to a missing vertex will automatically add the missing vertex.
- L568 _public prototype_ `bool Contains(const FVertexName& InVertexName) const;` — Returns true if a vertex exists with the provided name. This does not reflect whether the vertex is bound or not.
- L572 _public function_ `template<typename DataType> void SetValue(const FVertexName& InVertexName, const DataType& InValue)` — Set the value of a vertex.
- L588 _public function_ `void BindReadVertex(const FVertexName& InVertexName, const TDataReadReference<DataType>& InOutDataReference)` — `UE_DEPRECATED(5.6, "Please use a non-const lvalue reference for data references passed to this function. Const data references can sometimes be created by passing in temporary objects and/or triggering implicit conversion.")`
- L595 _public function_ `template<typename DataType> void BindReadVertex(const FVertexName& InVertexName, TDataReadReference<DataType>& InOutDataReference)` — Bind a read vertex from a read reference.
- L605 _public function_ `template<typename DataType> void BindReadVertex(const FVertexName& InVertexName, TDataWriteReference<DataType>& InOutDataReference)` — Bind a read vertex from a write reference.
- L616 _public function_ `void BindWriteVertex(const FVertexName& InVertexName, const TDataWriteReference<DataType>& InOutDataReference)` — `UE_DEPRECATED(5.6, "Please use a non-const lvalue reference for data references passed to this function. Const data references can sometimes be created by passing in temporary objects and/or triggering implicit conversion.")`
- L623 _public function_ `template<typename DataType> void BindWriteVertex(const FVertexName& InVertexName, TDataWriteReference<DataType>& InOutDataReference)` — Bind a write vertex from a write reference.
- L632 _public prototype_ `void BindVertex(const FVertexName& InVertexName, const FAnyDataReference& InOutDataReference);` — `UE_DEPRECATED(5.6, "Please use a non-const lvalue reference for data references passed to this function. Const data references can sometimes be created by passing in temporary objects and/or triggering implicit conversion.")` — Bind a vertex with a any data reference.
- L636 _public function_ `template<typename DataReferenceType> void BindVertex(const FVertexName& InVertexName, DataReferenceType& InOutDataReference)` — Bind a vertex with a a data reference.
- L644 _public prototype_ `void BindVertex(const FVertexName& InVertexName, FAnyDataReference& InOutDataReference);` — Bind a vertex with a any data reference.
- L657 _public function_ `void BindSubInterfaceVertices(const FName& InSubInterfaceName, const FName& InVertexName, RangeType& InOutDataReferences)`
- L673 _public function_ `void BindSubInterfaceWriteVertices(const FName& InSubInterfaceName, const FName& InVertexName, RangeType& InOutDataReferences)`
- L689 _public function_ `void BindSubInterfaceReadVertices(const FName& InSubInterfaceName, const FName& InVertexName, RangeType& InOutDataReferences)`
- L705 _public function_ `void SetSubInterfaceValues(const FName& InSubInterfaceName, const FName& InVertexName, const RangeType& InValues)`
- L716 _public prototype_ `void Bind(const FInputVertexInterfaceData& InOutInputVertexData);` — `UE_DEPRECATED(5.6, "Please use a non-const lvalue reference for data references passed to this function. Const data references can sometimes be created by passing in temporary objects and/or triggering implicit conversion.")` — Bind vertex data using other vertex data.
- L719 _public prototype_ `void Bind(FInputVertexInterfaceData& InOutInputVertexData);` — Bind vertex data using other vertex data.
- L722 _public prototype_ `void SetVertex(const FVertexName& InVertexName, const FAnyDataReference& InDataReference);` — Sets a vertex to use a data reference, ignoring any existing data bound to the vertex.
- L724 _public prototype_ `void SetVertex(const FVertexName& InVertexName, FAnyDataReference&& InDataReference);` — Sets a vertex to use a data reference, ignoring any existing data bound to the vertex.
- L728 _public prototype_ `void Set(const FDataReferenceCollection& InCollection);` — `UE_DEPRECATED(5.6, "Do not use FDataReferenceCollection.")` — Set a data references to vertices with matching vertex names. Ignores any existing data bound to the vertex.
- L732 _public prototype_ `FDataReferenceCollection ToDataReferenceCollection() const;` — `UE_DEPRECATED(5.6, "Do not use FDataReferenceCollection.")` — Convert vertex data to a data reference collection.
- L735 _public prototype_ `const FInputDataVertex& GetVertex(const FVertexName& InVertexName) const;` — Return the vertex associated with the vertex name.
- L738 _public prototype_ `void SetDefaultLiteral(const FVertexName& InVertexName, const FLiteral& InLiteral);` — Set the default literal used to create default values.
- L741 _public prototype_ `void AddVertex(const FInputDataVertex& InVertex);` — Add a vertex. VertexInterfaceData must be unfrozen.
- L744 _public prototype_ `void RemoveVertex(const FVertexName& InVertexName);` — Remove a vertex. VertexInterfaceData must be unfrozen.
- L748 _public prototype_ `bool IsVertexBound(const FVertexName& InVertexName) const;` — Returns true if a vertex with the given vertex name exists and is bound to a data reference.
- L753 _public prototype_ `EDataReferenceAccessType GetVertexDataAccessType(const FVertexName& InVertexName) const;` — Returns the access type of a bound vertex. If the vertex does not exist or if it is unbound, this will return EDataReferenceAccessType::None
- L757 _public prototype_ `bool AreAllVerticesBound() const;` — Returns true if all vertices in the FInputVertexInterface are bound to data references.
- L759 _public function_ `FRangedForIteratorType begin()`
- L764 _public function_ `FRangedForIteratorType end()`
- L769 _public function_ `FRangedForConstIteratorType begin() const`
- L774 _public function_ `FRangedForConstIteratorType end() const`
- L780 _public prototype_ `const FAnyDataReference* FindDataReference(const FVertexName& InVertexName) const;` — Find data reference bound to vertex. Returns a nullptr if no data reference is bound.
- L784 _public function_ `template<typename DataType> const DataType* GetValue(const FVertexName& InVertexName) const` — Returns the current value of a vertex.
- L798 _public function_ `template<typename DataType> DataType GetOrCreateDefaultValue(const FVertexName& InVertexName, const FOperatorSettings& InSettings) const` — Gets the value of the bound data reference if it exists. Otherwise create and return a value by constructing one using the Vertex's default literal.
- L808 _public function_ `template<typename DataType> TDataValueReference<DataType> GetOrCreateDefaultDataValueReference(const FVertexName& InVertexName, const FOperatorSettings& InSettings) const` — Gets the value of the bound data reference if it exists. Otherwise create and return a value by constructing one using the Vertex's default literal.
- L816 _public function_ `template<typename DataType> TDataReadReference<DataType> GetDataReadReference(const FVertexName& InVertexName) const` — Get data read reference assuming data is bound and read or write accessible.
- L827 _public function_ `template<typename DataType> TDataReadReference<DataType> GetOrCreateDefaultDataReadReference(const FVertexName& InVertexName, const FOperatorSettings& InSettings) const` — Get the bound data read reference if it exists. Otherwise create and return a data read reference by constructing one using the Vertex's default literal.
- L847 _public function_ `TDataReadReference<DataType> GetOrConstructDataReadReference(const FVertexName& InVertexName, ConstructorArgTypes&&... ConstructorArgs) const` — `UE_DEPRECATED(5.6, "Please GetOrCreateDefaultDataReadReference instead.")`
- L864 _public function_ `template<typename DataType> TDataWriteReference<DataType> GetDataWriteReference(const FVertexName& InVertexName) const` — Get data write reference assuming data is bound and write accessible.
- L875 _public function_ `template<typename DataType> TDataWriteReference<DataType> GetOrCreateDefaultDataWriteReference(const FVertexName& InVertexName, const FOperatorSettings& InSettings) const` — Get the bound data write reference if it exists. Otherwise create and return a data write reference by constructing one using the Vertex's default literal.
- L895 _public function_ `TDataWriteReference<DataType> GetOrConstructDataWriteReference(const FVertexName& InVertexName, ConstructorArgTypes&&... ConstructorArgs) const` — `UE_DEPRECATED(5.6, "Please GetOrCreateDefaultDataWriteReference instead.")`
- L916 _public function_ `TArray<DataReferenceType> GetOrCreateDefaultSubInterfaceAs(const FName& InSubInterfaceName, const FVertexName& InVertexName, const FOperatorSettings& InSettings) const`
- L936 _public function_ `TArray<TDataReadReference<DataType>> GetOrCreateDefaultSubInterfaceDataReadReferences(const FName& InSubInterfaceName, const FVertexName& InVertexName, const FOperatorSettings& InSettings) const`
- L948 _public function_ `TArray<TDataWriteReference<DataType>> GetOrCreateDefaultSubInterfaceDataWriteReferences(const FName& InSubInterfaceName, const FVertexName& InVertexName, const FOperatorSettings& InSettings) const`
- L960 _public function_ `TArray<DataType> GetOrCreateDefaultSubInterfaceValues(const FName& InSubInterfaceName, const FVertexName& InVertexName, const FOperatorSettings& InSettings) const`
- L979 _private prototype_ `void Apply(const FVertexName& InVertexName, TFunctionRef<FInputBinding ()> InCreateFunc, TFunctionRef<void (FInputBinding&)> InApplyFunc);`
- L980 _private prototype_ `void ForEachSubInterfaceBinding(const FName& InSubInterfaceName, const FVertexName& InVertexName, uint32 InExpectedNumSubInterfaceInstances, TFunctionRef<void (uint32, FInputBinding&)> InApplyFunc);`
- L981 _private prototype_ `void ForEachSubInterfaceBinding(const FName& InSubInterfaceName, const FVertexName& InVertexName, uint32 InExpectedNumSubInterfaceInstances, TFunctionRef<void (uint32, const FInputBinding&)> InApplyFunc) const;`
- L983 _private prototype_ `FInputBinding* Find(const FVertexName& InVertexName);`
- L984 _private prototype_ `const FInputBinding* Find(const FVertexName& InVertexName) const;`
- L986 _private prototype_ `FInputBinding* FindChecked(const FVertexName& InVertexName);`
- L987 _private prototype_ `const FInputBinding* FindChecked(const FVertexName& InVertexName) const;`
- L989 _private prototype_ `const VertexPrivate::FSubInterfaceLayout* FindSubInterface(const FName& InSubInterfaceName) const;`
- L991 _private member_ `bool bIsVertexInterfaceFrozen = false;`
- L992 _private member_ `TArray<FInputBinding> Bindings;`
- L993 _private member_ `TArray<VertexPrivate::FSubInterfaceLayout> SubInterfaces;`

#### class `Metasound::FOutputVertexInterfaceData`  
`class FOutputVertexInterfaceData`  
_L998-1386_
- desc: An output vertex interface with optionally bound data references.
- L1000 _private typedef_ `using FOutputBinding = VertexDataPrivate::FOutputBinding;`
- L1004 _public typedef_ `using FRangedForIteratorType = typename TArray<FOutputBinding>::RangedForIteratorType;`
- L1005 _public typedef_ `using FRangedForConstIteratorType = typename TArray<FOutputBinding>::RangedForConstIteratorType;`
- L1008 _public prototype_ `FOutputVertexInterfaceData();` — Construct with an FOutputVertexInterface. This will default to a unfrozen vertex interface.
- L1011 _public prototype_ `FOutputVertexInterfaceData(const FOutputVertexInterface& InVertexInterface);` — Construct with an FOutputVertexInterface. This will default to a frozen vertex interface.
- L1014 _public prototype_ `bool IsVertexInterfaceFrozen() const;` — Returns true if the vertex interface is frozen.
- L1023 _public prototype_ `void SetIsVertexInterfaceFrozen(bool bInIsVertexInterfaceFrozen);` — Set whether the vertex interface is frozen or not. If frozen, attempts to access vertices which do not already exist will result in an error. If not frozen, attempts to bind to a missing vertex will automatically add the missing vertex.
- L1027 _public prototype_ `bool Contains(const FVertexName& InVertexName) const;` — Returns true if a vertex exists with the provided name. This does not reflect whether the vertex is bound or not.
- L1031 _public function_ `template<typename DataType> void SetValue(const FVertexName& InVertexName, const DataType& InValue)` — Set the value of a vertex.
- L1046 _public function_ `void BindValueVertex(const FVertexName& InVertexName, const TDataValueReference<DataType>& InOutDataReference)` — `UE_DEPRECATED(5.6, "Please use a non-const lvalue reference for data references passed to this function. Const data references can sometimes be created by passing in temporary objects and/or triggering implicit conversion.")`
- L1056 _public function_ `void BindReadVertex(const FVertexName& InVertexName, const TDataValueReference<DataType>& InOutDataReference)` — `UE_DEPRECATED(5.6, "Please use a non-const lvalue reference for data references passed to this function. Const data references can sometimes be created by passing in temporary objects and/or triggering implicit conversion.")`
- L1064 _public function_ `void BindReadVertex(const FVertexName& InVertexName, const TDataReadReference<DataType>& InOutDataReference)` — `UE_DEPRECATED(5.6, "Please use a non-const lvalue reference for data references passed to this function. Const data references can sometimes be created by passing in temporary objects and/or triggering implicit conversion.")`
- L1071 _public function_ `template<typename DataType> void BindReadVertex(const FVertexName& InVertexName, TDataReadReference<DataType>& InOutDataReference)` — Bind a read vertex from a read reference.
- L1081 _public function_ `void BindReadVertex(const FVertexName& InVertexName, const TDataWriteReference<DataType>& InOutDataReference)` — `UE_DEPRECATED(5.6, "Please use a non-const lvalue reference for data references passed to this function. Const data references can sometimes be created by passing in temporary objects and/or triggering implicit conversion.")`
- L1088 _public function_ `template<typename DataType> void BindReadVertex(const FVertexName& InVertexName, TDataWriteReference<DataType>& InOutDataReference)` — Bind a read vertex from a write reference.
- L1098 _public function_ `template<typename DataType> void BindReadVertex(const FVertexName& InVertexName, FAnyDataReference& InOutDataReference)` — Bind a read vertex from a any reference.
- L1116 _public function_ `void BindWriteVertex(const FVertexName& InVertexName, const TDataWriteReference<DataType>& InOutDataReference)` — `UE_DEPRECATED(5.6, "Please use a non-const lvalue reference for data references passed to this function. Const data references can sometimes be created by passing in temporary objects and/or triggering implicit conversion.")`
- L1123 _public function_ `template<typename DataType> void BindWriteVertex(const FVertexName& InVertexName, TDataWriteReference<DataType>& InOutDataReference)` — Bind a write vertex from a write reference.
- L1132 _public prototype_ `void BindVertex(const FVertexName& InVertexName, const FAnyDataReference& InOutDataReference);` — `UE_DEPRECATED(5.6, "Please use a non-const lvalue reference for data references passed to this function. Const data references can sometimes be created by passing in temporary objects and/or triggering implicit conversion.")` — Bind a vertex with a any data reference.
- L1136 _public function_ `template<typename DataReferenceType> void BindVertex(const FVertexName& InVertexName, DataReferenceType& InOutDataReference)` — Bind a vertex with a data reference.
- L1144 _public prototype_ `void BindVertex(const FVertexName& InVertexName, FAnyDataReference& InOutDataReference);` — Bind a vertex with any data reference.
- L1157 _public function_ `void BindSubInterfaceVertices(const FName& InSubInterfaceName, const FName& InVertexName, RangeType& InOutDataReferences)`
- L1175 _public function_ `void BindSubInterfaceWriteVertices(const FName& InSubInterfaceName, const FName& InVertexName, RangeType& InOutDataReferences)`
- L1193 _public function_ `void BindSubInterfaceReadVertices(const FName& InSubInterfaceName, const FName& InVertexName, RangeType& InOutDataReferences)`
- L1211 _public function_ `void SetSubInterfaceValues(const FName& InSubInterfaceName, const FName& InVertexName, const RangeType& InValues)`
- L1224 _public prototype_ `void Bind(const FOutputVertexInterfaceData& InOutOutputVertexData);` — `UE_DEPRECATED(5.6, "Please use a non-const lvalue reference for data references passed to this function. Const data references can sometimes be created by passing in temporary objects and/or triggering implicit conversion.")` — Bind vertex data using other vertex data.
- L1226 _public prototype_ `void Bind(FOutputVertexInterfaceData& InOutOutputVertexData);` — Bind vertex data using other vertex data.
- L1229 _public prototype_ `void SetVertex(const FVertexName& InVertexName, const FAnyDataReference& InDataReference);` — Set a data reference to a vertex, ignoring any existing data bound to the vertex
- L1231 _public prototype_ `void SetVertex(const FVertexName& InVertexName, FAnyDataReference&& InDataReference);` — Set a data reference to a vertex, ignoring any existing data bound to the vertex
- L1235 _public prototype_ `void Set(const FDataReferenceCollection& InCollection);` — `UE_DEPRECATED(5.6, "Do not use FDataReferenceCollection.")` — Set a data references to vertices with matching vertex names.
- L1239 _public prototype_ `FDataReferenceCollection ToDataReferenceCollection() const;` — `UE_DEPRECATED(5.6, "Do not use FDataReferenceCollection.")` — Converts the vertex data to a data reference collection.
- L1243 _public prototype_ `bool IsVertexBound(const FVertexName& InVertexName) const;` — Returns true if a vertex with the given vertex name exists and is bound to a data reference.
- L1246 _public prototype_ `const FOutputDataVertex& GetVertex(const FVertexName& InVertexName) const;` — Return the vertex associated with the vertex name.
- L1249 _public prototype_ `void AddVertex(const FOutputDataVertex& InVertex);` — Add a vertex. VertexInterfaceData must be unfrozen.
- L1252 _public prototype_ `void RemoveVertex(const FVertexName& InVertexName);` — Remove a vertex. VertexInterfaceData must be unfrozen.
- L1257 _public prototype_ `EDataReferenceAccessType GetVertexDataAccessType(const FVertexName& InVertexName) const;` — Returns the access type of a bound vertex. If the vertex does not exist or if it is unbound, this will return EDataReferenceAccessType::None
- L1261 _public prototype_ `bool AreAllVerticesBound() const;` — Returns true if all vertices in the FInputVertexInterface are bound to data references.
- L1263 _public function_ `FRangedForIteratorType begin()`
- L1268 _public function_ `FRangedForIteratorType end()`
- L1273 _public function_ `FRangedForConstIteratorType begin() const`
- L1278 _public function_ `FRangedForConstIteratorType end() const`
- L1284 _public prototype_ `const FAnyDataReference* FindDataReference(const FVertexName& InVertexName) const;` — Find data reference bound to vertex. Returns a nullptr if no data reference is bound.
- L1288 _public function_ `template<typename DataType> const DataType* GetValue(const FVertexName& InVertexName) const` — Returns the current value of a vertex.
- L1304 _public function_ `template<typename DataType> TDataReadReference<DataType> GetDataReadReference(const FVertexName& InVertexName) const` — Get data read reference assuming data is bound and read or write accessible.
- L1315 _public function_ `template<typename DataType, typename ... ConstructorArgTypes> TDataReadReference<DataType> GetOrConstructDataReadReference(const FVertexName& InVertexName, ConstructorArgTypes&&... ConstructorArgs) const` — Get the bound data read reference if it exists. Otherwise create and return a data read reference by constructing one the supplied constructor arguments.
- L1332 _public function_ `template<typename DataType> TDataWriteReference<DataType> GetDataWriteReference(const FVertexName& InVertexName) const` — Get data write reference assuming data is bound and write accessible.
- L1343 _public function_ `template<typename DataType, typename ... ConstructorArgTypes> TDataWriteReference<DataType> GetOrConstructDataWriteReference(const FVertexName& InVertexName, ConstructorArgTypes&&... ConstructorArgs) const` — Get the bound data write reference if it exists. Otherwise create and return a data write reference by constructing one the supplied constructor arguments.
- L1372 _private prototype_ `void Apply(const FVertexName& InVertexName, TFunctionRef<FOutputBinding ()> InCreateFunc, TFunctionRef<void (FOutputBinding&)> InBindFunc);`
- L1373 _private prototype_ `void ForEachSubInterfaceBinding(const FName& InSubInterfaceName, const FVertexName& InVertexName, uint32 InExpectedNumSubInterfaceInstances, TFunctionRef<void (uint32, FOutputBinding&)> InApplyFunc);`
- L1374 _private prototype_ `void ForEachSubInterfaceBinding(const FName& InSubInterfaceName, const FVertexName& InVertexName, uint32 InExpectedNumSubInterfaceInstances, TFunctionRef<void (uint32, const FOutputBinding&)> InApplyFunc) const;`
- L1376 _private prototype_ `FOutputBinding* Find(const FVertexName& InVertexName);`
- L1377 _private prototype_ `const FOutputBinding* Find(const FVertexName& InVertexName) const;`
- L1378 _private prototype_ `const VertexPrivate::FSubInterfaceLayout* FindSubInterface(const FName& InSubInterfaceName) const;`
- L1380 _private prototype_ `FOutputBinding* FindChecked(const FVertexName& InVertexName);`
- L1381 _private prototype_ `const FOutputBinding* FindChecked(const FVertexName& InVertexName) const;`
- L1383 _private member_ `bool bIsVertexInterfaceFrozen = false;`
- L1384 _private member_ `TArray<FOutputBinding> Bindings;`
- L1385 _private member_ `TArray<VertexPrivate::FSubInterfaceLayout> SubInterfaces;`

#### class `Metasound::FVertexInterfaceData`  
`class FVertexInterfaceData`  
_L1389-1433_
- desc: A vertex interface with optionally bound data.
- L1393 _public prototype_ `FVertexInterfaceData() = default;`
- L1396 _public prototype_ `FVertexInterfaceData(const FVertexInterface& InVertexInterface);` — Construct using an FVertexInterface.
- L1400 _public prototype_ `void Bind(const FVertexInterfaceData& InVertexData);` — `UE_DEPRECATED(5.6, "Please use a non-const lvalue reference for data passed to this function. Const data can sometimes be created by passing in temporary objects and/or triggering implicit conversion.")` — Set vertex data using other vertex data.
- L1403 _public prototype_ `void Bind(FVertexInterfaceData& InVertexData);` — Set vertex data using other vertex data.
- L1406 _public function_ `FInputVertexInterfaceData& GetInputs()` — Get input vertex interface data.
- L1412 _public function_ `const FInputVertexInterfaceData& GetInputs() const` — Get input vertex interface data.
- L1418 _public function_ `FOutputVertexInterfaceData& GetOutputs()` — Get output vertex interface data.
- L1424 _public function_ `const FOutputVertexInterfaceData& GetOutputs() const` — Get output vertex interface data.
- L1431 _private member_ `FInputVertexInterfaceData InputVertexInterfaceData;`
- L1432 _private member_ `FOutputVertexInterfaceData OutputVertexInterfaceData;`

#### struct `Metasound::FVertexDataState`  
`struct FVertexDataState`  
_L1438-1445_
- desc: FVertexDataState encapsulates which data reference a vertex is associated with. The ID refers to the underlying object associated with the IDataReference.
- L1440 _public member_ `FVertexName VertexName;`
- L1441 _public member_ `FDataReferenceID ID;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API METASOUNDGRAPHCORE_API`
- L23 _macro_ `#define ENABLE_METASOUND_ACCESS_TYPE_COMPATIBILITY_TEST DO_CHECK` — Enable runtime tests for compatible access types between vertex access types and data references bound to the vertex.
- L25 _namespace_ `namespace Metasound`
- L27 _namespace_ `namespace VertexDataPrivate` (scope `Metasound`)
- L32 _prototype_ `void CheckAccessTypeCompatibility(const FDataVertex& InDataVertex, const FAnyDataReference& InDataReference);` (scope `Metasound::VertexDataPrivate`)
- L37 _prototype_ `EVertexAccessType DataReferenceAccessTypeToVertexAccessType(EDataReferenceAccessType InReferenceAccessType);` (scope `Metasound::VertexDataPrivate`)
- L92 _typedef_ `template<typename T> using TGetReferenceDataType = typename TGetReferenceDataTypeT<T>::Type;` (scope `Metasound::VertexDataPrivate`) — TGetReferencDataType is the underlying type stored in a data reference
- L575 _function_ `` (scope `Metasound::FInputVertexInterfaceData::SetValue`)
- L580 _function_ `auto BindData = [&](FInputBinding& Binding)` (scope `Metasound::FInputVertexInterfaceData::SetValue`)
- L598 _function_ `auto BindData = [&](FInputBinding& Binding)` (scope `Metasound::FInputVertexInterfaceData::BindReadVertex`)
- L626 _function_ `auto BindData = [&](FInputBinding& Binding)` (scope `Metasound::FInputVertexInterfaceData::BindWriteVertex`)
- L639 _function_ `auto BindData = [&](FInputBinding& Binding)` (scope `Metasound::FInputVertexInterfaceData::BindVertex`)
- L660 _function_ `` (scope `Metasound::FInputVertexInterfaceData::BindSubInterfaceVertices`)
- L676 _function_ `` (scope `Metasound::FInputVertexInterfaceData::BindSubInterfaceWriteVertices`)
- L692 _function_ `` (scope `Metasound::FInputVertexInterfaceData::BindSubInterfaceReadVertices`)
- L708 _function_ `` (scope `Metasound::FInputVertexInterfaceData::SetSubInterfaceValues`)
- L920 _function_ `` (scope `Metasound::FInputVertexInterfaceData::GetOrCreateDefaultSubInterfaceAs`)
- L1034 _function_ `` (scope `Metasound::FOutputVertexInterfaceData::SetValue`)
- L1039 _function_ `auto BindData = [&](FOutputBinding& Binding)` (scope `Metasound::FOutputVertexInterfaceData::SetValue`)
- L1049 _function_ `auto BindData = [&](FOutputBinding& Binding)` (scope `Metasound::FOutputVertexInterfaceData::BindValueVertex`)
- L1074 _function_ `auto BindData = [&](FOutputBinding& Binding)` (scope `Metasound::FOutputVertexInterfaceData::BindReadVertex`)
- L1105 _function_ `` (scope `Metasound::FOutputVertexInterfaceData::BindReadVertex`)
- L1126 _function_ `auto BindData = [&](FOutputBinding& Binding)` (scope `Metasound::FOutputVertexInterfaceData::BindWriteVertex`)
- L1139 _function_ `auto BindData = [&](FOutputBinding& Binding)` (scope `Metasound::FOutputVertexInterfaceData::BindVertex`)
- L1162 _function_ `` (scope `Metasound::FOutputVertexInterfaceData::BindSubInterfaceVertices`)
- L1180 _function_ `` (scope `Metasound::FOutputVertexInterfaceData::BindSubInterfaceWriteVertices`)
- L1198 _function_ `` (scope `Metasound::FOutputVertexInterfaceData::BindSubInterfaceReadVertices`)
- L1216 _function_ `` (scope `Metasound::FOutputVertexInterfaceData::SetSubInterfaceValues`)
- L1448 _prototype_ `void GetVertexInterfaceDataState(const FInputVertexInterfaceData& InVertexInterface, TArray<FVertexDataState>& OutState);` (scope `Metasound`) — Caches a representation of the current data references bound to the vertex interface
- L1450 _prototype_ `void GetVertexInterfaceDataState(const FOutputVertexInterfaceData& InVertexInterface, TArray<FVertexDataState>& OutState);` (scope `Metasound`) — Caches a representation of the current data references bound to the vertex interface
- L1453 _prototype_ `void CompareVertexInterfaceDataToPriorState(const FInputVertexInterfaceData& InCurrentInterface, const TArray<FVertexDataState>& InPriorState, TSortedVertexNameMap<FAnyDataReference>& OutUpdates);` (scope `Metasound`) — Compares the current data bound to the vertex interface with a prior cached state.
- L1455 _prototype_ `void CompareVertexInterfaceDataToPriorState(const FOutputVertexInterfaceData& InCurrentInterface, const TArray<FVertexDataState>& InPriorState, TSortedVertexNameMap<FAnyDataReference>& OutUpdates);` (scope `Metasound`) — Compares the current data bound to the vertex interface with a prior cached state.
