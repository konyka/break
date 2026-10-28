# Plugins / MetasoundGenerator

- module root: `Plugins/Runtime/Metasound/Source/MetasoundGenerator`
- headers: 7; symbols: 357
- symbol kinds: class=13, delegate=5, enum=1, enumerator=3, function=11, macro=6, member=142, namespace=16, prototype=139, struct=15, typedef=6
- PrivateDependencyModuleNames: AudioChannelAgnosticCore, AudioExtensions, Engine, SignalProcessing, TraceLog
- PublicDependencyModuleNames: AudioMixer, Core, CoreUObject, MetasoundFrontend, MetasoundGraphCore, MetasoundStandardNodes

### `Plugins/Runtime/Metasound/Source/MetasoundGenerator/Private/MetasoundGeneratorBuilder.h` (Private)


#### class `Metasound::FAsyncMetaSoundBuilderBase`  
`class FAsyncMetaSoundBuilderBase : public FNonAbandonableTask`  
_L36-57_
- inherits: `FNonAbandonableTask`
- desc: Base class for building a metasound generator
- L39 _public prototype_ `FAsyncMetaSoundBuilderBase(FMetasoundGenerator* InGenerator, bool bInTriggerGenerator);`
- L41 _public prototype_ `virtual ~FAsyncMetaSoundBuilderBase() = default;`
- L43 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L49 _protected member_ `FMetasoundGenerator* Generator;`
- L50 _protected member_ `bool bTriggerGenerator;`
- L52 _protected prototype_ `void SetGraphOnGenerator(FOperatorAndInputs&& InOpAndInputs, FBuildResults&& InBuildResults);`
- L55 _private prototype_ `virtual const FGeneratorInitParams& GetGeneratorParams() const = 0;`

#### class `Metasound::FAsyncMetaSoundBuilder`  
`class FAsyncMetaSoundBuilder : public FAsyncMetaSoundBuilderBase`  
_L60-72_
- inherits: `FAsyncMetaSoundBuilderBase`
- desc: Task class for asynchronously building a FMetasoundGenerator
- L63 _public prototype_ `FAsyncMetaSoundBuilder(FMetasoundConstGraphGenerator* InGenerator, FGeneratorInitParams&& InInitParams, bool bInTriggerGenerator);`
- L65 _public prototype_ `virtual ~FAsyncMetaSoundBuilder() = default;`
- L67 _public prototype_ `void DoWork();`
- L70 _private prototype_ `virtual const FGeneratorInitParams& GetGeneratorParams() const override;`
- L71 _private member_ `FGeneratorInitParams InitParams;`

#### class `Metasound::FAsyncDynamicMetaSoundBuilder`  
`class FAsyncDynamicMetaSoundBuilder : public FAsyncMetaSoundBuilderBase`  
_L75-88_
- inherits: `FAsyncMetaSoundBuilderBase`
- desc: Task class for asynchronously building a FMetasoundDynamicGraphGenerator
- L78 _public prototype_ `FAsyncDynamicMetaSoundBuilder(FMetasoundDynamicGraphGenerator* InGenerator, FMetasoundDynamicGraphGeneratorInitParams&& InInitParams, bool bInTriggerGenerator);`
- L80 _public prototype_ `virtual ~FAsyncDynamicMetaSoundBuilder() = default;`
- L82 _public prototype_ `void DoWork();`
- L85 _private prototype_ `virtual const FGeneratorInitParams& GetGeneratorParams() const override;`
- L86 _private member_ `FMetasoundDynamicGraphGenerator* DynamicGenerator;`
- L87 _private member_ `FMetasoundDynamicGraphGeneratorInitParams InitParams;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace Metasound`
- L25 _namespace_ `namespace Frontend` (scope `Metasound`)
- L30 _namespace_ `namespace DynamicGraph` (scope `Metasound`)
- L90 _namespace_ `namespace GeneratorBuilder` (scope `Metasound`)
- L93 _prototype_ `TArray<FAudioBufferReadRef> FindOutputAudioBuffers(const TArray<FVertexName>& InAudioVertexNames, const FVertexInterfaceData& InVertexData, const FOperatorSettings& InOperatorSettings, const FTopLevelAssetPath& InAssetPath);` (scope `Metasound::GeneratorBuilder`) — Finds an array of audio buffer read references from the VertexData
- L96 _prototype_ `void LogBuildErrors(const FTopLevelAssetPath& InAssetPath, const FBuildResults& InBuildResults);` (scope `Metasound::GeneratorBuilder`) — Log any errors in the build results
- L99 _prototype_ `TUniquePtr<Frontend::FGraphAnalyzer> BuildGraphAnalyzer(TMap<FGuid, FDataReferenceCollection>&& InInternalDataReferences, const FMetasoundEnvironment& InEnvironment, const FOperatorSettings& InOperatorSettings);` (scope `Metasound::GeneratorBuilder`) — Build an analyzer for a graph
- L102 _prototype_ `FInputVertexInterfaceData BuildGraphOperatorInputs(const FOperatorSettings& InOperatorSettings, FGeneratorInitParams& InInitParams);` (scope `Metasound::GeneratorBuilder`) — Instantiate the input data references for a generator.
- L105 _prototype_ `FOperatorAndInputs BuildGraphOperator(const FOperatorSettings& InOperatorSettings, FGeneratorInitParams& InInitParams, FBuildResults& OutBuildResults);` (scope `Metasound::GeneratorBuilder`) — Build a standard graph operatpr
- L108 _prototype_ `FOperatorAndInputs BuildDynamicGraphOperator(const FOperatorSettings& InOperatorSettings, FMetasoundDynamicGraphGeneratorInitParams& InInitParams, const DynamicGraph::FDynamicOperatorUpdateCallbacks& InCallbacks, FBuildResults& OutBuildResults);` (scope `Metasound::GeneratorBuilder`) — Build a dynamic graph operator
- L111 _prototype_ `MetasoundGeneratorPrivate::FMetasoundGeneratorData BuildGeneratorData(const FOperatorSettings& InOperatorSettings, const FGeneratorInitParams& InInitParams, FOperatorAndInputs&& InGraphOperatorAndInputs, TUniquePtr<Frontend::FGraphAnalyzer> InAnalyzer);` (scope `Metasound::GeneratorBuilder`) — Create all the data required to run a FMetasoundGenerator
- L114 _prototype_ `void ResetGraphOperatorInputs(const FOperatorSettings& InOperatorSettings, TArray<FAudioParameter> InParameterOverrides, FInputVertexInterfaceData& InOutInterface);` (scope `Metasound::GeneratorBuilder`) — Resets FInputVertexInterfaceData to it's initial default state using the default literals stored ther-in. If a parameter exists in InParmaeterOverrides, that value is used instead.
- L117 _prototype_ `void InitializeParameterSetters(FInputVertexInterfaceData& InputData, MetasoundGeneratorPrivate::FParameterSetterSortedMap& OutParamSetters, TMap<FName, MetasoundGeneratorPrivate::FParameterPackSetter>& OutParamPackSetters);` (scope `Metasound::GeneratorBuilder`) — Initialize the maps of parameter setters for applying async input data to metasound inputs.
- L120 _prototype_ `void AddParameterSetterIfWritable(const FVertexName& InVertexName, FInputVertexInterfaceData& InputData, MetasoundGeneratorPrivate::FParameterSetterSortedMap& OutParamSetters, TMap<FName, MetasoundGeneratorPrivate::FParameterPackSetter>& OutParamPackSetters);` (scope `Metasound::GeneratorBuilder`) — Add a parameter setter to the parameter map if the data bound to the input vertex is writable.
- L123 _prototype_ `void AddParameterSetter(const Frontend::IDataTypeRegistry& InDataTypeRegistry, const FInputDataVertex& InVertex, const FAnyDataReference& InDataRef, MetasoundGeneratorPrivate::FParameterSetterSortedMap& OutParamSetters, TMap<FName, MetasoundGeneratorPrivate::FParameterPackSetter>& OutParamPackSetters);` (scope `Metasound::GeneratorBuilder`) — Add a parameter setter to the parameter map for the given vertex.

### `Plugins/Runtime/Metasound/Source/MetasoundGenerator/Private/MetasoundGeneratorModuleImpl.h` (Private)


#### class `Metasound::FMetasoundGeneratorModule`  
`class FMetasoundGeneratorModule : public IMetasoundGeneratorModule`  
_L12-29_
- inherits: `IMetasoundGeneratorModule`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `virtual TSharedPtr<FOperatorPool> GetOperatorPool() override;`
- L20 _public prototype_ `virtual TSharedPtr<FConcurrentInstanceCounterManager> GetOperatorInstanceCounterManager() override;`
- L24 _private member_ `TSharedPtr<FOperatorPool> OperatorPool;`
- L25 _private member_ `TSharedPtr<FConcurrentInstanceCounterManager> OperatorInstanceCounterManager;`
- L27 _private member_ `FDelegateHandle CsvEndFrameDelegateHandle;`
- L28 _private member_ `FDelegateHandle PreAudioDeviceDestroyedHandle;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundGenerator/Private/MetasoundOperatorCacheStatTracker.h` (Private)


#### class `Metasound::Engine::FOperatorCacheStatTracker`  
`class FOperatorCacheStatTracker final`  
_L20-57_
- L23 _public prototype_ `FOperatorCacheStatTracker();`
- L24 _public prototype_ `~FOperatorCacheStatTracker();`
- L27 _public prototype_ `void RecordPreCacheRequest(const FOperatorBuildData& BuildData, int32 NumInstancesToBuild, int32 NumInstancesInCache);` — Called when we're pre-caching an operator. Called before AddOperator.
- L28 _public prototype_ `void RecordCacheEvent(const FOperatorPoolEntryID& OperatorID, bool bCacheHit, const FOperatorContext& Context);`
- L29 _public prototype_ `void OnOperatorAdded(const FOperatorPoolEntryID& OperatorID);`
- L30 _public prototype_ `void OnOperatorTrimmed(const FOperatorPoolEntryID& OperatorID);`
- L31 _public prototype_ `void OnOperatorRemoved(const FOperatorPoolEntryID& OperatorID);`
- L34 _private prototype_ `void OnCsvProfileEndFrame();`
- L53 _private member_ `TMap<FOperatorPoolEntryID, FStatEntry> StatEntries;`
- L54 _private member_ `mutable FCriticalSection CriticalSection;`
- L55 _private member_ `FDelegateHandle CsvEndFrameDelegateHandle;`
- L56 _private member_ `int32 NumInCache = 0;`

#### struct `Metasound::Engine::FOperatorCacheStatTracker::FStatEntry`  
`struct FStatEntry`  
_L36-51_
- L39 _public member_ `FTopLevelAssetPath GraphAssetPath;` — Stored as a TopLevelPath to avoid conversions writing out csv stats.
- L42 _public member_ `int32 NumInstancesBuilt;` — The actual number of instances we built.
- L46 _public member_ `int32 NumCacheSlots;` — The number of instances we have space to cache. This can be different from the number currently in the stack as those are removed when in use.
- L50 _public member_ `int32 NumAvailableInCache = 0;` — The number of operators sitting in the pool waiting to be used. Set exclusively by OnOperatorAdded/OnOperatorTrimmed.

#### Free symbols / members of external scopes

- L8 _macro_ `#define METASOUND_OPERATORCACHEPROFILER_ENABLED COUNTERSTRACE_ENABLED`
- L12 _namespace_ `namespace Metasound`
- L18 _namespace_ `namespace Metasound`
- L18 _namespace_ `namespace Engine` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundGenerator/Public/MetasoundGenerator.h` (Public)


#### struct `Metasound::MetasoundGeneratorPrivate::FParameterSetter`  
`struct FParameterSetter`  
_L45-49_
- L47 _public member_ `Frontend::FLiteralAssignmentFunction Assign;`
- L48 _public member_ `FAnyDataReference DataReference;`

#### struct `Metasound::MetasoundGeneratorPrivate::FParameterPackSetter`  
`struct FParameterPackSetter`  
_L58-72_
- desc: A struct that provides a method of pushing "raw" data from a parameter pack into a specific metasound input node.
- L60 _public member_ `FName DataType;`
- L61 _public member_ `void* Destination;`
- L62 _public member_ `const Frontend::IParameterAssignmentFunction& Setter;`
- L63 _public function_ `FParameterPackSetter(FName InDataType, void* InDestination, const Frontend::IParameterAssignmentFunction& InSetter) : DataType(InDataType) , Destination(InDestination) , Setter(InSetter)`
- L68 _public function_ `void SetParameterWithPayload(const void* ParameterPayload) const`

#### struct `Metasound::MetasoundGeneratorPrivate::FMetasoundGeneratorData`  
`struct FMetasoundGeneratorData`  
_L74-86_
- L76 _public member_ `FOperatorSettings OperatorSettings;`
- L77 _public member_ `TUniquePtr<IOperator> GraphOperator;`
- L78 _public member_ `FVertexInterfaceData VertexInterfaceData;`
- L79 _public member_ `FParameterSetterSortedMap ParameterSetters;`
- L80 _public member_ `TMap<FName, FParameterPackSetter> ParameterPackSetters;`
- L81 _public member_ `TUniquePtr<Frontend::FGraphAnalyzer> GraphAnalyzer;`
- L82 _public member_ `TArray<TDataReadReference<FAudioBuffer>> OutputBuffers;`
- L83 _public member_ `FTriggerWriteRef TriggerOnPlayRef;`
- L84 _public member_ `FTriggerReadRef TriggerOnFinishRef;`
- L85 _public member_ `TOptional<FChannelAgnosticTypeReadRef> OutputChannelAgnosticRef;`

#### struct `Metasound::FOperatorPoolEntryID`  
`struct FOperatorPoolEntryID final`  
_L90-111_
- desc: ID for looking up a operator in the operator pool
- L97 _public prototype_ `FOperatorPoolEntryID(FGuid InOperatorID, FOperatorSettings InSettings);` — Construct an ID InOperatorID - ID of the operator. InSettings - Operator settings used to create the operator.
- L99 _public prototype_ `FString ToString() const;`
- L109 _private member_ `FGuid OperatorID;`
- L110 _private member_ `FOperatorSettings OperatorSettings;`

#### struct `Metasound::FGeneratorInitParams`  
`struct FGeneratorInitParams`  
_L113-135_
- L115 _public member_ `FOperatorSettings OperatorSettings;`
- L116 _public member_ `FOperatorBuilderSettings BuilderSettings;`
- L117 _public member_ `TSharedPtr<const IGraph, ESPMode::ThreadSafe> Graph;`
- L118 _public member_ `FMetasoundEnvironment Environment;`
- L120 _public member_ `TArray<FVertexName> AudioOutputNames;`
- L121 _public member_ `TArray<FAudioParameter> DefaultParameters;`
- L122 _public member_ `bool bBuildSynchronous = false;`
- L123 _public member_ `TSharedPtr<TSpscQueue<FMetaSoundParameterTransmitter::FParameter>> DataChannel;`
- L124 _public member_ `TSharedPtr<FGraphRenderCost> GraphRenderCost;`
- L125 _public member_ `FName ClassName;`
- L126 _public member_ `FTopLevelAssetPath AssetPath;`
- L132 _public member_ `FName SourceFormatName;` — CAT format identity (e.g. "Cat:Mono1Dot0"). Empty for non-CAT sources. The generator derives the mixer-compatible channel count internally: - CAT path:     from SourceFormatName via channel registry lookup + clamp. - Discrete path: from AudioOutputNames.Num().
- L134 _public prototype_ `static void Reset(FGeneratorInitParams& InParams);`

#### struct `Metasound::FMetasoundGeneratorInitParams`  
`struct UE_DEPRECATED(5.7, "Use FGeneratorInitParams instead (MetaSoundName is deprecated in favor of AssetPath") FMetasoundGeneratorInitParams : public FGeneratorInitParams`  
_L138-143_
- inherits: `FGeneratorInitParams`
- desc: Initialization params required for building a MetaSound generator
- L141 _public member_ `FString MetaSoundName = { };`

#### enum `Metasound::EVertexInterfaceChangeType`  
`enum class EVertexInterfaceChangeType : uint8`  
_L145-150_
- L147 _public enumerator_ `Added`
- L148 _public enumerator_ `Updated`
- L149 _public enumerator_ `Removed`

#### struct `Metasound::FVertexInterfaceChange`  
`struct FVertexInterfaceChange`  
_L152-157_
- L154 _public member_ `FVertexName VertexName;`
- L155 _public member_ `EMetasoundFrontendClassType VertexType;` — Input or Output
- L156 _public member_ `EVertexInterfaceChangeType ChangeType;`

#### class `Metasound::FMetasoundGenerator`  
`class FMetasoundGenerator : public ISoundGenerator`  
_L161-427_
- inherits: `ISoundGenerator`
- L164 _public typedef_ `using FOperatorUniquePtr = TUniquePtr<Metasound::IOperator>;`
- L165 _public typedef_ `using FAudioBufferReadRef = Metasound::FAudioBufferReadRef;`
- L167 _public member_ `const FOperatorSettings OperatorSettings;`
- L174 _public prototype_ `explicit FMetasoundGenerator(const FOperatorSettings& InOperatorSettings);`
- L176 _public prototype_ `virtual ~FMetasoundGenerator();`
- L184 _public function_ `template<typename DataType> void SetInputValue(const FVertexName& InName, DataType InData)` — Set the value of a graph's input data using the assignment operator. @param InName - The name of the graph's input data reference. @param InData - The value to assign.
- L198 _public function_ `template<typename DataType> void ApplyToInputValue(const FVertexName& InName, TFunctionRef<void(DataType&)> InFunc)` — Apply a function to the graph's input data. @param InName - The name of the graph's input data reference. @param InFunc - A function which takes the DataType as an input.
- L206 _public prototype_ `void QueueParameterPack(TSharedPtr<FMetasoundParameterPackStorage> ParameterPack);`
- L217 _public function_ `template<typename DataType> TOptional<TDataWriteReference<DataType>> GetInputWriteReference(const FVertexName InputName)` — Get a write reference to one of the generator's inputs, if it exists. NOTE: This reference is only safe to use immediately on the same thread that this generator's OnGenerateAudio() is called. @tparam DataType - The expected data type of the input @param InputName - The user-defined name of the input
- L238 _public function_ `template<typename DataType> TOptional<TDataReadReference<DataType>> GetOutputReadReference(const FVertexName OutputName)` — Get a read reference to one of the generator's outputs, if it exists. NOTE: This reference is only safe to use immediately on the same thread that this generator's OnGenerateAudio() is called. @tparam DataType - The expected data type of the output @param OutputName - The user-defined name of the output
- L250 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnVertexInterfaceDataUpdated, FVertexInterfaceData);`
- L251 _public member_ `FOnVertexInterfaceDataUpdated OnVertexInterfaceDataUpdated;`
- L253 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnVertexInterfaceDataUpdatedWithChanges, const TArray<FVertexInterfaceChange>&);`
- L254 _public member_ `FOnVertexInterfaceDataUpdatedWithChanges OnVertexInterfaceDataUpdatedWithChanges;`
- L261 _public prototype_ `void AddOutputVertexAnalyzer(const Frontend::FAnalyzerAddress& AnalyzerAddress);` — Add a vertex analyzer for a named output with the given address info. @param AnalyzerAddress - Address information for the analyzer
- L268 _public prototype_ `void RemoveOutputVertexAnalyzer(const Frontend::FAnalyzerAddress& AnalyzerAddress);` — Remove a vertex analyzer for a named output @param AnalyzerAddress - Address information for the analyzer
- L270 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_FourParams(FOnOutputChanged, FName, FName, FName, TSharedPtr<IOutputStorage>);`
- L271 _public member_ `FOnOutputChanged OnOutputChanged;`
- L274 _public prototype_ `virtual int32 GetNumChannels() const override;` — Return the number of audio channels.
- L277 _public prototype_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;`
- L278 _public prototype_ `virtual int32 GetDesiredNumSamplesToRenderPerCallback() const override;`
- L279 _public prototype_ `virtual bool IsFinished() const override;`
- L280 _public prototype_ `virtual float GetRelativeRenderCost() const override;`
- L287 _public function_ `void EnableRuntimeRenderTiming(bool Enable)` — Enables the performance timing of the metasound rendering process. You must call this before "GetCPUCoreUtilization" or the results will always be 0.0.
- L290 _public prototype_ `double GetCPUCoreUtilization() const;` — Fraction of a single CPU core used to render audio on a scale of 0.0 to 1.0
- L296 _public prototype_ `FDelegateHandle AddGraphSetCallback(FOnSetGraph::FDelegate&& Delegate);` — Called when a new graph has been "compiled" and set up as this generator's graph. Note: We don't allow direct assignment to the FOnSetGraph delegate because we want to give the Delegate an initial immediate callback if the generator already has a graph.
- L297 _public prototype_ `bool RemoveGraphSetCallback(const FDelegateHandle& Handle);`
- L302 _public function_ `void OnNextBuffer(TFunction<void(FMetasoundGenerator&)> Command)` — Enqueues a command for this generator to execute when its next buffer is requested by the mixer.  Enqueued commands are executed before OnGenerateAudio, and on the same thread.  They can safely access generator state.
- L309 _protected prototype_ `void InitBase(FGeneratorInitParams& InInitParams);`
- L313 _protected prototype_ `void SetGraph(TUniquePtr<MetasoundGeneratorPrivate::FMetasoundGeneratorData>&& InData, bool bTriggerGraph);` — SetGraph directly sets graph. Callers must ensure that no race conditions exist.
- L316 _protected prototype_ `virtual TUniquePtr<IOperator> ReleaseGraphOperator();`
- L317 _protected prototype_ `FInputVertexInterfaceData ReleaseInputVertexData();`
- L319 _protected member_ `FConcurrentInstanceCounter InstanceCounter;`
- L325 _protected prototype_ `void ClearGraph();` — Release the graph operator and remove any references to data owned by the graph operator.
- L326 _protected prototype_ `bool UpdateGraphIfPending();`
- L329 _protected member_ `std::atomic<bool> bVertexInterfaceHasChanged{ false };` — `UE_DEPRECATED(5.5, "Use VertexInterfaceChangesSinceLastBroadcast to determine if changes have occurred.")`
- L334 _private prototype_ `void SetPendingGraphBuildFailed();`
- L343 _private prototype_ `void SetPendingGraph(MetasoundGeneratorPrivate::FMetasoundGeneratorData&& InData, bool bTriggerGraph);` — Update the current graph operator with a new graph operator. The number of channels of InGraphOutputAudioRef must match the existing number of channels reported by GetNumChannels() in order for this function to successfully replace the graph operator. @param InData - Metasound data of built graph. @param bTriggerGraph - If true, "OnPlay" will be triggered on the new graph.
- L347 _private prototype_ `int32 FillWithBuffer(const Audio::FAlignedFloatBuffer& InBuffer, float* OutAudio, int32 MaxNumOutputSamples);` — Fill OutAudio with data in InBuffer, up to maximum number of samples. Returns the number of samples used.
- L350 _private prototype_ `void InterleaveGeneratedAudio();` — Metasound creates deinterleaved audio while sound generator requires interleaved audio.
- L352 _private prototype_ `void ApplyPendingUpdatesToInputs();`
- L354 _private prototype_ `void HandleRenderTimingEnableDisable();`
- L357 _protected member_ `FExecuter RootExecuter;`
- L358 _protected member_ `FVertexInterfaceData VertexInterfaceData;`
- L359 _protected member_ `TArray<FVertexInterfaceChange> VertexInterfaceChangesSinceLastBroadcast;`
- L361 _protected member_ `TArray<FAudioBufferReadRef> GraphOutputAudio;`
- L370 _protected member_ `TOptional<FChannelAgnosticState> GraphCatOutput;` — This is the CAT reference from the graph.
- L373 _protected member_ `FTriggerReadRef OnFinishedTriggerRef;` — Triggered when metasound is finished
- L375 _protected member_ `MetasoundGeneratorPrivate::FParameterSetterSortedMap ParameterSetters;`
- L379 _protected member_ `TMap<FName, MetasoundGeneratorPrivate::FParameterPackSetter> ParameterPackSetters;` — This map provides setters for all of the input nodes in the metasound graph. It is used when processing named parameters in a parameter pack.
- L380 _protected member_ `TSharedPtr<FGraphRenderCost> GraphRenderCost;`
- L383 _private member_ `FTopLevelAssetPath AssetPath;`
- L385 _private member_ `uint8 bIsGraphBuilding : 1 = 0;`
- L386 _private member_ `uint8 bIsFinishTriggered : 1 = 0;`
- L387 _private member_ `uint8 bIsFinished : 1 = 0;`
- L388 _private member_ `uint8 bPendingGraphTrigger : 1 = 1;`
- L389 _private member_ `uint8 bIsNewGraphPending : 1 = 0;`
- L390 _private member_ `uint8 bIsWaitingForFirstGraph : 1 = 1;`
- L391 _private member_ `uint8 bDoRuntimeRenderTiming : 1 = 0;`
- L393 _private member_ `int32 FinishSample = INDEX_NONE;`
- L394 _private member_ `int32 NumChannels = 0;`
- L395 _private member_ `FName SourceFormatName;` — Graph-side CAT format identity. Set in Environment upstream (MetasoundSource); held here for reference only. Mixer output uses NumChannels separately.
- L396 _private member_ `int32 NumFramesPerExecute = 0;`
- L397 _private member_ `int32 NumSamplesPerExecute = 0;`
- L399 _private member_ `Audio::FAlignedFloatBuffer InterleavedAudioBuffer;`
- L400 _private member_ `Audio::FAlignedFloatBuffer OverflowBuffer;`
- L402 _private member_ `FCriticalSection PendingGraphMutex;`
- L403 _private member_ `TUniquePtr<MetasoundGeneratorPrivate::FMetasoundGeneratorData> PendingGraphData;`
- L404 _private member_ `TUniquePtr<Frontend::FGraphAnalyzer> GraphAnalyzer;`
- L405 _private member_ `TSharedPtr<TSpscQueue<FMetaSoundParameterTransmitter::FParameter>> ParameterQueue;`
- L410 _private member_ `FSendAddress ParameterPackSendAddress;` — These next items are needed to provide a destination for the FAudioDevice, etc. to send parameter packs to. Every playing metasound will have a parameter destination that can accept parameter packs.
- L411 _private member_ `TReceiverPtr<FMetasoundParameterStorageWrapper> ParameterPackReceiver;`
- L416 _private member_ `TMpscQueue<TSharedPtr<FMetasoundParameterPackStorage>> ParameterPackQueue;` — While parameter packs may arrive via the IAudioParameterInterface system, a faster method of sending parameters is via the QueueParameterPack function and this queue.
- L418 _private member_ `TMpscQueue<TUniqueFunction<void()>> OutputAnalyzerModificationQueue;`
- L419 _private member_ `TArray<TUniquePtr<Frontend::IVertexAnalyzer>> OutputAnalyzers;`
- L421 _private member_ `FOnSetGraph OnSetGraph;`
- L423 _private member_ `double RenderTime = 0.0;`
- L424 _private member_ `TUniquePtr<MetasoundGeneratorPrivate::FRenderTimer> RenderTimer;`
- L426 _private member_ `std::atomic<float> RelativeRenderCost { 1.f };`

#### struct `Metasound::FMetasoundGenerator::FChannelAgnosticState`  
`struct FChannelAgnosticState`  
_L363-369_
- L365 _public member_ `FChannelAgnosticTypeReadRef GraphOutput;`
- L366 _public member_ `TOptional<Audio::FChannelAgnosticType> MixerOutput;` — Only allocated when transcode is needed (graph format != mixer format).
- L367 _public member_ `Audio::ChannelAgnosticTranscoder::FTranscoder Transcoder;` — Empty when identity — no transcode needed.
- L368 _public member_ `bool bIdentityTranscode = false;` — True when graph output format matches mixer format (skip transcode + extra buffer).

#### class `Metasound::FMetasoundConstGraphGenerator`  
`class FMetasoundConstGraphGenerator : public FMetasoundGenerator`  
_L432-454_
- inherits: `FMetasoundGenerator`
- desc: FMetasoundConstGraphGenerator generates audio from a given metasound IOperator which produces a multichannel audio output.
- L436 _public prototype_ `explicit FMetasoundConstGraphGenerator(FGeneratorInitParams&& InParams);`
- L438 _public prototype_ `explicit FMetasoundConstGraphGenerator(const FOperatorSettings& InOperatorSettings);`
- L440 _public prototype_ `void Init(FGeneratorInitParams&& InParams);`
- L446 _private prototype_ `void BuildGraph(FGeneratorInitParams&& InInitParams);`
- L447 _private prototype_ `bool TryUseCachedOperator(FGeneratorInitParams& InParams, bool bTriggerGenerator);`
- L448 _private prototype_ `void ReleaseOperatorToCache();`
- L450 _private member_ `TUniquePtr<FMetasoundEnvironment> EnvironmentPtr;`
- L451 _private member_ `TUniquePtr<FAsyncTaskBase> BuilderTask;`
- L452 _private member_ `TOptional<FOperatorPoolEntryID> OperatorPoolID;`
- L453 _private member_ `bool bUseOperatorPool = false;`

#### struct `Metasound::FMetasoundDynamicGraphGeneratorInitParams`  
`struct FMetasoundDynamicGraphGeneratorInitParams : FGeneratorInitParams`  
_L456-460_
- inherits: `FGeneratorInitParams`
- L458 _public member_ `TSharedPtr<TSpscQueue<TUniquePtr<DynamicGraph::IDynamicOperatorTransform>>> TransformQueue;`
- L459 _public prototype_ `static void Reset(FMetasoundDynamicGraphGeneratorInitParams& InParams);`

#### class `Metasound::FMetasoundDynamicGraphGenerator`  
`class FMetasoundDynamicGraphGenerator : public FMetasoundGenerator`  
_L465-495_
- inherits: `FMetasoundGenerator`
- desc: FMetasoundDynamicGraphGenerator generates audio from the given a dynamic operator. It also reacts to updates to inputs and outputs of the dynamic operator.
- L473 _public prototype_ `explicit FMetasoundDynamicGraphGenerator(const FOperatorSettings& InOperatorSettings);` — Create the generator with a graph operator and an output audio reference. @param InParams - The generator initialization parameters
- L475 _public prototype_ `void Init(FMetasoundDynamicGraphGeneratorInitParams&& InParams);`
- L477 _public prototype_ `virtual ~FMetasoundDynamicGraphGenerator();`
- L480 _public prototype_ `void OnInputAdded(const FVertexName& InVertexName, const FInputVertexInterfaceData& InInputData);` — The callbacks are executed when the equivalent change happens on the owned dynamic operator.
- L481 _public prototype_ `void OnInputRemoved(const FVertexName& InVertexName, const FInputVertexInterfaceData& InInputData);`
- L482 _public prototype_ `void OnOutputAdded(const FVertexName& InVertexName, const FOutputVertexInterfaceData& InOutputData);`
- L483 _public prototype_ `void OnOutputUpdated(const FVertexName& InVertexName, const FOutputVertexInterfaceData& InOutputData);`
- L484 _public prototype_ `void OnOutputRemoved(const FVertexName& InVertexName, const FOutputVertexInterfaceData& InOutputData);`
- L487 _protected prototype_ `virtual TUniquePtr<IOperator> ReleaseGraphOperator() override;`
- L490 _private prototype_ `void BuildGraph(FMetasoundDynamicGraphGeneratorInitParams&& InParams);`
- L493 _private member_ `TArray<FVertexName> AudioOutputNames;`
- L494 _private member_ `TUniquePtr<FAsyncTaskBase> BuilderTask;`

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API METASOUNDGENERATOR_API`
- L28 _macro_ `#define ENABLE_METASOUND_GENERATOR_RENDER_TIMING WITH_EDITOR`
- L32 _macro_ `#define ENABLE_METASOUND_GENERATOR_INSTANCE_COUNTING UE_TRACE_ENABLED && !UE_BUILD_SHIPPING`
- L34 _namespace_ `namespace Metasound`
- L36 _namespace_ `namespace DynamicGraph` (scope `Metasound`)
- L41 _namespace_ `namespace MetasoundGeneratorPrivate` (scope `Metasound`)
- L55 _typedef_ `using FParameterSetterSortedMap = TSortedMap<FName, FParameterSetter, FDefaultAllocator, FNameFastLess>;` (scope `Metasound::MetasoundGeneratorPrivate`) — In order to use FName as a key to a TSortedMap you have to explicitly choose which comparison implementation you want to use.  Declaring the type here helps minimize the confusion over why there are so many template arguments.
- L103 _function_ `friend inline uint32 GetTypeHash(const FOperatorPoolEntryID& InID)` (scope `Metasound`)
- L159 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FOnSetGraph);`
- L159 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FOnSetGraph);` (scope `Metasound`)
- L250 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnVertexInterfaceDataUpdated, FVertexInterfaceData);`
- L253 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnVertexInterfaceDataUpdatedWithChanges, const TArray<FVertexInterfaceChange>&);`
- L270 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_FourParams(FOnOutputChanged, FName, FName, FName, TSharedPtr<IOutputStorage>);`
- L304 _function_ `SynthCommand([this, Command = MoveTemp(Command)]() { Command(*this); });` (scope `Metasound::FMetasoundGenerator::OnNextBuffer`)

### `Plugins/Runtime/Metasound/Source/MetasoundGenerator/Public/MetasoundGeneratorModule.h` (Public)


#### class `Metasound::IMetasoundGeneratorModule`  
`class IMetasoundGeneratorModule : public IModuleInterface`  
_L17-22_
- inherits: `IModuleInterface`
- L20 _public prototype_ `virtual TSharedPtr<FOperatorPool> GetOperatorPool() = 0;`
- L21 _public prototype_ `virtual TSharedPtr<FConcurrentInstanceCounterManager> GetOperatorInstanceCounterManager() = 0;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetasoundGenerator, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetasoundGenerator, Log, All);`
- L11 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundGenerator/Public/MetasoundInstanceCounter.h` (Public)


#### class `Metasound::FConcurrentInstanceCounterManager`  
`class FConcurrentInstanceCounterManager`  
_L26-67_
- L29 _public prototype_ `FConcurrentInstanceCounterManager(const FString InCategoryName);`
- L31 _public prototype_ `void Increment(const FTopLevelAssetPath& InstancePath);`
- L32 _public prototype_ `void Decrement(const FTopLevelAssetPath& InstancePath);`
- L34 _public prototype_ `int64 GetCountForPath(const FTopLevelAssetPath& InPath);`
- L35 _public prototype_ `int64 GetPeakCountForPath(const FTopLevelAssetPath& InPath);`
- L37 _public prototype_ `void VisitStats(TFunctionRef<void(const FTopLevelAssetPath&, int64)> Visitor);`
- L61 _private prototype_ `FStats& GetOrAddStats(const FTopLevelAssetPath& AssetPath);`
- L63 _private member_ `TMap<FTopLevelAssetPath, FStats> StatsMap;`
- L64 _private member_ `FCriticalSection MapCritSec;`
- L65 _private member_ `FString CategoryName;`

#### struct `Metasound::FConcurrentInstanceCounterManager::FStats`  
`struct FStats`  
_L40-59_
- L44 _public prototype_ `FStats(const FString& InCategoryName, const FTopLevelAssetPath& InPath);`
- L49 _public prototype_ `void Increment();`
- L50 _public prototype_ `void Decrement();`
- L52 _public prototype_ `int64 GetCount() const;`
- L53 _public prototype_ `int64 GetPeakCount() const;`
- L56 _private member_ `TUniquePtr<CounterType> TraceCounter;`
- L57 _private member_ `int64 PeakCount;`

#### class `Metasound::FConcurrentInstanceCounter`  
`class FConcurrentInstanceCounter`  
_L71-90_
- L75 _public prototype_ `FConcurrentInstanceCounter() = delete;` — ctor
- L76 _public prototype_ `FConcurrentInstanceCounter(TSharedPtr<FConcurrentInstanceCounterManager> InCounterManager);`
- L77 _public prototype_ `FConcurrentInstanceCounter(const FTopLevelAssetPath& InPath, TSharedPtr<FConcurrentInstanceCounterManager> InCounterManager);`
- L80 _public prototype_ `virtual ~FConcurrentInstanceCounter();` — dtor
- L83 _public prototype_ `void Init(const FTopLevelAssetPath& InPath);` — for non-RAII clients
- L86 _private prototype_ `FConcurrentInstanceCounterManager& GetManagerChecked();`
- L88 _private member_ `FTopLevelAssetPath InstancePath;`
- L89 _private member_ `TSharedPtr<FConcurrentInstanceCounterManager> ManagerPtr;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Metasound`
- L18 _typedef_ `using CounterType = FCountersTrace::FCounterInt;` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundGenerator/Public/MetasoundOperatorCache.h` (Public)


#### class `Metasound::OperatorPoolPrivate::FWindowedHitRate`  
`class FWindowedHitRate`  
_L37-71_
- L41 _public prototype_ `FWindowedHitRate();` — ctor
- L42 _public prototype_ `void Update();`
- L43 _public prototype_ `void AddHit();`
- L44 _public prototype_ `void AddMiss();`
- L54 _private member_ `TArray<IntermediateResult> History;`
- L56 _private member_ `uint32 CurrHitCount = 0;`
- L57 _private member_ `uint32 CurrTotal = 0;`
- L58 _private member_ `uint32 RunningHitCount = 0;`
- L59 _private member_ `uint32 RunningTotal = 0;`
- L61 _private member_ `float CurrTTLSeconds = 0.f;`
- L63 _private member_ `uint64 PreviousTimeCycles = 0;`
- L64 _private member_ `bool bIsFirstUpdate = true;`
- L66 _private prototype_ `void FirstUpdate();`
- L67 _private prototype_ `void SetWindowLength(const float InNewLengthSeconds);`
- L68 _private prototype_ `void ExpireResult(const IntermediateResult& InResultToExpire);`
- L69 _private prototype_ `void TickResults(const float DeltaTimeSeconds);`

#### struct `Metasound::OperatorPoolPrivate::FWindowedHitRate::IntermediateResult`  
`struct IntermediateResult`  
_L47-52_
- L49 _public member_ `uint32 NumHits = 0;`
- L50 _public member_ `uint32 Total = 0;`
- L51 _public member_ `float TTLSeconds;`

#### struct `Metasound::FOperatorPoolSettings`  
`struct FOperatorPoolSettings`  
_L76-79_
- L78 _public member_ `uint32 MaxNumOperators = 64;`

#### struct `Metasound::FOperatorBuildData`  
`struct FOperatorBuildData`  
_L83-102_
- desc: Data required to build an operator without immediately playing it
- L85 _public member_ `FGeneratorInitParams InitParams;`
- L86 _public member_ `Frontend::FGraphRegistryKey RegistryKey;`
- L87 _public member_ `FGuid AssetClassID;`
- L88 _public member_ `int32 NumInstances;`
- L91 _public member_ `bool bTouchExisting = false;` — If true, touches existing assets and only builds remaining number if required
- L93 _public prototype_ `FOperatorBuildData() = delete;`
- L94 _public prototype_ `FOperatorBuildData( FGeneratorInitParams&& InInitParams , Frontend::FGraphRegistryKey InRegistryKey , FGuid InAssetID , int32 InNumInstances = 1 , bool bInTouchExisting = false );`

#### struct `Metasound::FOperatorContext`  
`struct FOperatorContext`  
_L105-114_
- desc: Provides additional debug context for the operator the pool is interacting with.
- L108 _public member_ `FTopLevelAssetPath GraphAssetPath;` — Path to underlying graph asset
- L111 _public member_ `FTopLevelAssetPath AssetPath;` — Path to asset with given operator (presets have different paths than graph asset)
- L113 _public prototype_ `static FOperatorContext FromInitParams(const FGeneratorInitParams& InParams);`

#### class `Metasound::FOperatorPool`  
`class FOperatorPool : public TSharedFromThis<FOperatorPool>`  
_L118-180_
- inherits: `TSharedFromThis<FOperatorPool>`
- desc: Pool of re-useable metasound operators to be used / put back by the metasound generator operators can also be pre-constructed via the UMetasoundCacheSubsystem BP api.
- L122 _public prototype_ `FOperatorPool(FOperatorPoolSettings InSettings = { });`
- L123 _public prototype_ `~FOperatorPool();`
- L125 _public prototype_ `FOperatorAndInputs ClaimOperator(const FOperatorPoolEntryID& InOperatorID, const FOperatorContext& InContext);`
- L127 _public prototype_ `void AddOperator(const FOperatorPoolEntryID& InOperatorID, TUniquePtr<IOperator>&& InOperator, FInputVertexInterfaceData&& InputData, TSharedPtr<FGraphRenderCost>&& InRenderCost = {});`
- L128 _public prototype_ `void AddOperator(const FOperatorPoolEntryID& InOperatorID, FOperatorAndInputs&& OperatorAndInputs);`
- L130 _public prototype_ `void BuildAndAddOperator(TUniquePtr<FOperatorBuildData> InBuildData);`
- L132 _public prototype_ `void TouchOperators(const FOperatorPoolEntryID& InOperatorID, int32 NumToTouch = 1);`
- L133 _public prototype_ `void TouchOperatorsViaAssetClassID(const FGuid& InAssetClassID, int32 NumToTouch = 1);`
- L135 _public prototype_ `bool IsStopping() const;`
- L137 _public prototype_ `void RemoveOperatorsWithID(const FOperatorPoolEntryID& InOperatorID);`
- L138 _public prototype_ `void RemoveOperatorsWithAssetClassID(const FGuid& InAssetClassID);`
- L140 _public prototype_ `int32 GetNumCachedOperatorsWithID(const FOperatorPoolEntryID& InOperatorID) const;`
- L141 _public prototype_ `int32 GetNumCachedOperatorsWithAssetClassID(const FGuid& InAssetClassID) const;`
- L143 _public prototype_ `void SetMaxNumOperators(uint32 InMaxNumOperators);`
- L145 _public prototype_ `void UpdateHitRateTracker();`
- L148 _public prototype_ `void StopAsyncTasks();`
- L150 _public typedef_ `using FTaskId = int32;`
- L151 _public typedef_ `using FTaskFunction = TUniqueFunction<void(FOperatorPool::FTaskId, TWeakPtr<FOperatorPool>)>;`
- L154 _private member_ `FTaskId LastTaskId = 0;`
- L156 _private prototype_ `void AddAssetIdToGraphIdLookUpInternal(const FGuid& InAssetClassID, const FOperatorPoolEntryID& InOperatorID);`
- L157 _private prototype_ `void AddOperatorInternal(const FOperatorPoolEntryID& InOperatorID, FOperatorAndInputs&& OperatorAndInputs);`
- L158 _private prototype_ `bool ExecuteTaskAsync(FTaskFunction&& InFunction);`
- L159 _private prototype_ `void Trim();`
- L161 _private member_ `FOperatorPoolSettings Settings;`
- L162 _private member_ `mutable FCriticalSection CriticalSection;`
- L165 _private member_ `OperatorPoolPrivate::FWindowedHitRate HitRateTracker;`
- L166 _private member_ `TUniquePtr<Engine::FOperatorCacheStatTracker> CacheStatTracker;`
- L171 _private member_ `std::atomic<bool> bStopping;` — Notifies active build tasks to abort as soon as possible and gates additional build tasks from being added.
- L173 _private member_ `TMap<FTaskId, UE::Tasks::FTask> ActiveBuildTasks;`
- L174 _private member_ `UE::Tasks::FPipe AsyncBuildPipe;`
- L176 _private member_ `TMap<FOperatorPoolEntryID, TArray<FOperatorAndInputs>> Operators;`
- L177 _private member_ `TMap<FGuid, FOperatorPoolEntryID> AssetIdToGraphIdLookUp;`
- L178 _private member_ `TMultiMap<FOperatorPoolEntryID, FGuid> GraphIdToAssetIdLookUp;`
- L179 _private member_ `TArray<FOperatorPoolEntryID> Stack;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API METASOUNDGENERATOR_API`
- L19 _macro_ `#define METASOUND_OPERATORCACHEPROFILER_ENABLED COUNTERSTRACE_ENABLED`
- L21 _namespace_ `namespace Metasound`
- L24 _namespace_ `namespace Engine` (scope `Metasound`)
- L29 _prototype_ `void RecordOperatorStat(const FTopLevelAssetPath& InAssetPath, int32 CategoryIndex, int32 Value, ECsvCustomStatOp StatOp);` (scope `Metasound::Engine`)
- L30 _prototype_ `void RecordOperatorStat(const FTopLevelAssetPath& InAssetPath, int32 CategoryIndex, float Value, ECsvCustomStatOp StatOp);` (scope `Metasound::Engine`)
- L31 _prototype_ `void RecordOperatorStat(const FTopLevelAssetPath& InAssetPath, int32 CategoryIndex, double Value, ECsvCustomStatOp StatOp);` (scope `Metasound::Engine`)
- L35 _namespace_ `namespace OperatorPoolPrivate` (scope `Metasound`)
