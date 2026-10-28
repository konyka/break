# Plugins / MetasoundFrontend

- module root: `Plugins/Runtime/Metasound/Source/MetasoundFrontend`
- headers: 113; symbols: 6137
- symbol kinds: class=254, delegate=16, enum=30, enumerator=92, externvar=43, function=971, macro=114, member=1128, namespace=239, prototype=2765, struct=243, typedef=240, variable=2
- PrivateDependencyModuleNames: Projects
- PublicDependencyModuleNames: AudioChannelAgnosticCore, AudioExtensions, Core, CoreUObject, Json, JsonUtilities, MetasoundGraphCore, Serialization, SignalProcessing, Slate, SlateCore

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/Interfaces/MetasoundFrontendInterfaceBindingRegistryPrivate.h` (Private)


#### class `Metasound::Frontend::FInterfaceBindingRegistry`  
`class FInterfaceBindingRegistry : public IInterfaceBindingRegistry`  
_L14-32_
- inherits: `IInterfaceBindingRegistry`
- L17 _public prototype_ `FInterfaceBindingRegistry() = default;`
- L19 _public prototype_ `virtual ~FInterfaceBindingRegistry() = default;`
- L21 _public prototype_ `virtual bool FindInterfaceBindingEntries(const FMetasoundFrontendVersion& InInputInterfaceVersion, TArray<const FInterfaceBindingRegistryEntry*>& OutEntries) const override;`
- L23 _public prototype_ `virtual void RegisterInterfaceBinding(const FMetasoundFrontendVersion& InInputInterfaceVersion, TUniquePtr<FInterfaceBindingRegistryEntry>&& InEntry) override;`
- L25 _public prototype_ `virtual bool UnregisterInterfaceBinding(const FMetasoundFrontendVersion& InInputInterfaceVersion, const FMetasoundFrontendVersion& InOutputInterfaceVersion) override;`
- L27 _public prototype_ `virtual bool UnregisterAllInterfaceBindings(const FMetasoundFrontendVersion& InInputInterfaceVersion) override;`
- L31 _private member_ `TMultiMap<FMetasoundFrontendVersion, TUniquePtr<FInterfaceBindingRegistryEntry>> Entries;` — MultiMap of interface bindings keyed by the shared input interface version for an array of connection-priority sorted bindings

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/Interfaces/MetasoundFrontendInterfaceRegistryPrivate.h` (Private)


#### class `Metasound::Frontend::FInterfaceRegistry`  
`class FInterfaceRegistry : public IInterfaceRegistry`  
_L17-46_
- inherits: `IInterfaceRegistry`
- L20 _public prototype_ `static FInterfaceRegistry& Get();`
- L22 _public prototype_ `FInterfaceRegistry();`
- L24 _public prototype_ `virtual ~FInterfaceRegistry() = default;`
- L26 _public prototype_ `virtual bool ContainsInput(const FMetasoundFrontendVersion& InVersion, const FMetasoundFrontendVertex& InInput) const override;`
- L27 _public prototype_ `virtual bool ContainsInterface(const FMetasoundFrontendVersion& InVersion) const override;`
- L28 _public prototype_ `virtual bool ContainsOutput(const FMetasoundFrontendVersion& InVersion, const FMetasoundFrontendVertex& InOutput) const override;`
- L30 _public prototype_ `virtual bool FindInterface(const FMetasoundFrontendVersion& InVersion, FMetasoundFrontendInterface& OutInterface) const override;`
- L31 _public prototype_ `virtual bool FindInterfaceRouter(const FMetasoundFrontendVersion& InVersion, FName& OutRouter) const override;`
- L32 _public prototype_ `virtual TSharedPtr<IBuilderVersionTransform> FindInterfaceUpdateTransform(const FMetasoundFrontendVersion& InVersion) const override;`
- L33 _public prototype_ `virtual bool RegisterInterface(TUniquePtr<IInterfaceRegistryEntry>&& InEntry) override;`
- L35 _public prototype_ `TUniquePtr<FInterfaceTransactionStream> CreateTransactionStream();`
- L38 _private prototype_ `bool IsInterfaceVertexNameValid(FName InterfaceNamespace, FName FullVertexName, FName* VertexNamespace) const;`
- L40 _private typedef_ `using FInterfaceTransactionBuffer = TTransactionBuffer<FInterfaceRegistryTransaction>;`
- L42 _private member_ `mutable FTransactionallySafeCriticalSection EntriesCriticalSection;`
- L43 _private member_ `TMap<FMetasoundFrontendVersion, TUniquePtr<IInterfaceRegistryEntry>> Entries;`
- L45 _private member_ `TSharedRef<FInterfaceTransactionBuffer> TransactionBuffer;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Metasound`
- L13 _namespace_ `namespace Frontend` (scope `Metasound`)
- L15 _typedef_ `using FInterfaceTransactionStream = TTransactionStream<FInterfaceRegistryTransaction>;` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundAssetManagerTransactionPrivate.h` (Private)


#### class `Metasound::Frontend::FAssetManagerTransactor`  
`class FAssetManagerTransactor : public IMetaSoundAssetTransactor`  
_L14-25_
- inherits: `IMetaSoundAssetTransactor`
- L17 _public prototype_ `FAssetManagerTransactor();`
- L19 _public prototype_ `TUniquePtr<FAssetManagerTransactionStream> CreateTransactionStream();`
- L20 _public prototype_ `virtual void RegisterAsset(FMetaSoundAssetKey Key) override;`
- L21 _public prototype_ `virtual void UnregisterAsset(FMetaSoundAssetKey Key) override;`
- L24 _private member_ `TSharedRef<FAssetManagerTransactionBuffer> TransactionBuffer;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Metasound`
- L9 _namespace_ `namespace Frontend` (scope `Metasound`)
- L11 _typedef_ `using FAssetManagerTransactionBuffer = TTransactionBuffer<FAssetManagerTransaction>;` (scope `Metasound::Frontend`)
- L12 _typedef_ `using FAssetManagerTransactionStream = TTransactionStream<FAssetManagerTransaction>;` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundAssetTagCollections.h` (Private)


#### struct `FMetaSoundAssetTagCollections`  
`struct FMetaSoundAssetTagCollections`  
_L13-21_
- reflection: `USTRUCT()`
- desc: Minimal Json-serializable arrays of asset tag data. Helper struct for asset tag serialization of collection properties.
- L19 _public member_ `TArray<FMetaSoundAssetKey> AssetKeys;` — `UPROPERTY()`

#### struct `FMetaSoundAssetTagClassCollections`  
`struct FMetaSoundAssetTagClassCollections`  
_L27-38_
- reflection: `USTRUCT()`
- desc: Minimal Json-serializable arrays of asset class tag data. Helper struct for asset tag serialization of collection properties.
- L33 _public member_ `TArray<FMetasoundFrontendInterfaceMetadata> DefinedInterfaces;` — `UPROPERTY()`
- L36 _public member_ `TArray<FMetasoundFrontendVersion> InheritedInterfaces;` — `UPROPERTY()`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundFrontendDocumentCache.h` (Private)


#### class `Metasound::Frontend::FDocumentGraphEdgeCache`  
`class FDocumentGraphEdgeCache : public IDocumentGraphEdgeCache`  
_L19-58_
- inherits: `IDocumentGraphEdgeCache`
- L25 _private prototype_ `FDocumentGraphEdgeCache();` — Only exists to make TSharedFromThis happy, but should never be called
- L26 _private prototype_ `FDocumentGraphEdgeCache(TSharedRef<const FDocumentCache> ParentCache, const FGuid& InPageID);`
- L29 _public prototype_ `static TSharedRef<FDocumentGraphEdgeCache> Create(TSharedRef<const FDocumentCache> ParentCache, const FGuid& InPageID, FDocumentModifyDelegates& OutDelegates);`
- L30 _public prototype_ `virtual ~FDocumentGraphEdgeCache() = default;`
- L33 _public prototype_ `virtual bool ContainsEdge(const FMetasoundFrontendEdge& InEdge) const override;` — IDocumentGraphEdgeCache implementation
- L35 _public prototype_ `virtual bool IsNodeInputConnected(const FGuid& InNodeID, const FGuid& InVertexID) const override;`
- L36 _public prototype_ `virtual bool IsNodeOutputConnected(const FGuid& InNodeID, const FGuid& InVertexID) const override;`
- L38 _public prototype_ `virtual TArray<const FMetasoundFrontendEdge*> FindEdges(const FGuid& InNodeID, const FGuid& InVertexID) const override;`
- L39 _public prototype_ `virtual const int32* FindEdgeIndexToNodeInput(const FGuid& InNodeID, const FGuid& InVertexID) const override;`
- L40 _public prototype_ `virtual const TArrayView<const int32> FindEdgeIndicesFromNodeOutput(const FGuid& InNodeID, const FGuid& InVertexID) const override;`
- L42 _public prototype_ `int32 GetTransactionCount() const;`
- L45 _private prototype_ `void Init(FEdgeModifyDelegates& OutDelegates);`
- L46 _private prototype_ `void OnEdgeAdded(int32 InNewIndex);`
- L47 _private prototype_ `void OnRemoveSwappingEdge(int32 SwapIndex, int32 LastIndex);`
- L50 _private member_ `TMap<FMetasoundFrontendVertexHandle, TArray<int32>> OutputToEdgeIndices;` — Cache of outputs NodeId/VertexId pairs to associated edge indices
- L53 _private member_ `TMap<FMetasoundFrontendVertexHandle, int32> InputToEdgeIndex;` — Cache of Input NodeId/VertexId pairs to associated edge indices
- L55 _private member_ `TWeakPtr<const FDocumentCache> Parent;`
- L56 _private member_ `FGuid PageID;`
- L57 _private member_ `int32 TransactionCount = 0;`

#### class `Metasound::Frontend::FDocumentGraphNodeCache`  
`class FDocumentGraphNodeCache : public IDocumentGraphNodeCache`  
_L61-113_
- inherits: `IDocumentGraphNodeCache`
- L67 _private prototype_ `FDocumentGraphNodeCache();` — Only exists to make TSharedFromThis happy, but should never be called
- L68 _private prototype_ `FDocumentGraphNodeCache(TSharedRef<const FDocumentCache> ParentCache, const FGuid& InPageID);`
- L71 _public prototype_ `static TSharedRef<FDocumentGraphNodeCache> Create(TSharedRef<const FDocumentCache> ParentCache, const FGuid& InPageID, FDocumentModifyDelegates& OutDelegates);`
- L72 _public prototype_ `virtual ~FDocumentGraphNodeCache() = default;`
- L75 _public prototype_ `virtual bool ContainsNode(const FGuid& InNodeID) const override;` — IDocumentGraphNodeCache implementation
- L76 _public prototype_ `virtual bool ContainsNodesOfClassID(const FGuid& InClassID) const override;`
- L78 _public prototype_ `virtual const int32* FindNodeIndex(const FGuid& InNodeID) const override;`
- L79 _public prototype_ `virtual TArray<const FMetasoundFrontendNode*> FindNodesOfClassID(const FGuid& InClassID) const override;`
- L80 _public prototype_ `virtual const FMetasoundFrontendNode* FindNode(const FGuid& InNodeID) const override;`
- L82 _public prototype_ `virtual TArray<const FMetasoundFrontendVertex*> FindNodeInputs(const FGuid& InNodeID, FName TypeName = FName()) const override;`
- L83 _public prototype_ `virtual TArray<const FMetasoundFrontendVertex*> FindNodeOutputs(const FGuid& InNodeID, FName TypeName = FName()) const override;`
- L85 _public prototype_ `virtual const FMetasoundFrontendVertex* FindInputVertex(const FGuid& InNodeID, const FGuid& InVertexID) const override;`
- L86 _public prototype_ `virtual const FMetasoundFrontendVertex* FindInputVertex(const FGuid& InNodeID, FName InVertexName) const override;`
- L87 _public prototype_ `virtual const FMetasoundFrontendVertex* FindOutputVertex(const FGuid& InNodeID, const FGuid& InVertexID) const override;`
- L88 _public prototype_ `virtual const FMetasoundFrontendVertex* FindOutputVertex(const FGuid& InNodeID, FName InVertexName) const override;`
- L90 _public prototype_ `virtual TArray<const FMetasoundFrontendVertex*> FindReroutedInputVertices(const FGuid& InNodeID, const FGuid& InVertexID, TArray<const FMetasoundFrontendNode*>* ConnectedNodes = nullptr, bool* bOutIsRerouted = nullptr) const override;`
- L91 _public prototype_ `virtual TArray<const FMetasoundFrontendVertex*> FindReroutedInputVertices(const FGuid& InNodeID, FName InVertexName, TArray<const FMetasoundFrontendNode*>* ConnectedNodes = nullptr, bool* bOutIsRerouted = nullptr) const override;`
- L92 _public prototype_ `virtual const FMetasoundFrontendVertex* FindReroutedOutputVertex(const FGuid& InNodeID, const FGuid& InVertexID, const FMetasoundFrontendNode** ConnectedNodes = nullptr, bool* bOutIsRerouted = nullptr) const override;`
- L93 _public prototype_ `virtual const FMetasoundFrontendVertex* FindReroutedOutputVertex(const FGuid& InNodeID, FName InVertexName, const FMetasoundFrontendNode** ConnectedNodes = nullptr, bool* bOutIsRerouted = nullptr) const override;`
- L95 _public prototype_ `int32 GetTransactionCount() const;`
- L98 _private prototype_ `void Init(FNodeModifyDelegates& OutDelegates);`
- L99 _private prototype_ `void OnNodeAdded(int32 NewIndex);`
- L100 _private prototype_ `void OnNodeInputLiteralSet(int32 NodeIndex, int32 VertexIndex, int32 LiteralIndex);`
- L101 _private prototype_ `void OnRemoveSwappingNode(int32 IndexBeingRemoved, int32 LastIndex);`
- L102 _private prototype_ `void OnRemovingNodeInputLiteral(int32 NodeIndex, int32 VertexIndex, int32 LiteralIndex);`
- L105 _private member_ `TSortedMap<FGuid, int32> IDToIndex;` — Cache of NodeId to array index of node
- L108 _private member_ `TSortedMap<FGuid, TArray<int32>> ClassIDToNodeIndices;` — Cache of ClassID to referencing node indices
- L110 _private member_ `TWeakPtr<const FDocumentCache> Parent;`
- L111 _private member_ `FGuid PageID;`
- L112 _private member_ `int32 TransactionCount = 0;`

#### class `Metasound::Frontend::FDocumentGraphInterfaceCache`  
`class FDocumentGraphInterfaceCache : public IDocumentGraphInterfaceCache`  
_L116-171_
- inherits: `IDocumentGraphInterfaceCache`
- L121 _private prototype_ `FDocumentGraphInterfaceCache(TSharedRef<const FDocumentCache> ParentCache);`
- L124 _public prototype_ `static TSharedRef<FDocumentGraphInterfaceCache> Create(TSharedRef<const FDocumentCache> ParentCache, FInterfaceModifyDelegates& OutDelegates);`
- L125 _public prototype_ `virtual ~FDocumentGraphInterfaceCache() = default;`
- L128 _public prototype_ `virtual const FMetasoundFrontendClassInput* FindInput(FName InputName) const override;` — IDocumentGraphInterfaceCache implementation
- L129 _public prototype_ `virtual const int32* FindInputIndex(FName InputName) const override;`
- L130 _public prototype_ `virtual const FMetasoundFrontendClassOutput* FindOutput(FName OutputName) const override;`
- L131 _public prototype_ `virtual const int32* FindOutputIndex(FName OutputName) const override;`
- L133 _public prototype_ `int32 GetTransactionCount() const;`
- L136 _private prototype_ `void Init(FInterfaceModifyDelegates& OutDelegates);`
- L138 _private prototype_ `void OnInputAdded(int32 NewIndex);`
- L139 _private prototype_ `void OnRemovingInput(int32 IndexBeingRemoved);`
- L140 _private prototype_ `void OnInputNameChanged(FName OldName, FName NewName);`
- L141 _private prototype_ `void OnInputDataTypeChanged(int32 Index);`
- L142 _private prototype_ `void OnInputDefaultChanged(const FDocumentArrayPagedInputArgs& Args);`
- L143 _private prototype_ `void OnInputInheritsDefaultChanged(int32 NewIndex);`
- L145 _private prototype_ `void OnInputDisplayNameChanged(int32 Index);`
- L146 _private prototype_ `void OnInputDescriptionChanged(int32 Index);`
- L147 _private prototype_ `void OnInputSortOrderIndexChanged(int32 Index);`
- L148 _private prototype_ `void OnInputIsAdvancedDisplayChanged(int32 Index);`
- L151 _private prototype_ `void OnOutputAdded(int32 NewIndex);`
- L152 _private prototype_ `void OnRemovingOutput(int32 IndexBeingRemoved);`
- L153 _private prototype_ `void OnOutputNameChanged(FName OldName, FName NewName);`
- L154 _private prototype_ `void OnOutputDataTypeChanged(int32 Index);`
- L156 _private prototype_ `void OnOutputDisplayNameChanged(int32 Index);`
- L157 _private prototype_ `void OnOutputDescriptionChanged(int32 Index);`
- L158 _private prototype_ `void OnOutputSortOrderIndexChanged(int32 Index);`
- L159 _private prototype_ `void OnOutputIsAdvancedDisplayChanged(int32 Index);`
- L163 _private member_ `TMap<FName, int32> InputNameToIndex;` — Cache of Input name to array index of input
- L166 _private member_ `TMap<FName, int32> OutputNameToIndex;` — Cache of Output name to array index of output
- L168 _private member_ `TWeakPtr<const FDocumentCache> Parent;`
- L170 _private member_ `int32 TransactionCount = 0;`

#### class `Metasound::Frontend::FDocumentCache`  
`class FDocumentCache : public IDocumentCache`  
_L174-251_
- inherits: `IDocumentCache`
- L180 _private prototype_ `FDocumentCache();` — Only exists to make TSharedFromThis happy, but should never be called
- L181 _private prototype_ `FDocumentCache(const FMetasoundFrontendDocument& InDocument, TSharedRef<FDocumentModifyDelegates> Delegates);`
- L184 _public prototype_ `static TSharedRef<FDocumentCache> Create(const FMetasoundFrontendDocument& InDocument, TSharedRef<FDocumentModifyDelegates> Delegates, const FGuid& InBuildPageID, bool bPrimeCache);`
- L185 _public prototype_ `virtual ~FDocumentCache() = default;`
- L187 _public prototype_ `virtual bool ContainsDependency(const FNodeRegistryKey& InClassKey) const override;`
- L188 _public prototype_ `virtual bool ContainsDependencyOfType(EMetasoundFrontendClassType ClassType) const override;`
- L190 _public prototype_ `virtual const FMetasoundFrontendClass* FindDependency(const FNodeRegistryKey& InClassKey) const override;`
- L191 _public prototype_ `virtual const FMetasoundFrontendClass* FindDependency(const FGuid& InClassID) const override;`
- L192 _public prototype_ `virtual const int32* FindDependencyIndex(const Metasound::Frontend::FNodeRegistryKey& InClassKey) const override;`
- L193 _public prototype_ `virtual const int32* FindDependencyIndex(const FGuid& InClassID) const override;`
- L195 _public prototype_ `virtual const FMetasoundFrontendDocument& GetDocument() const override;`
- L196 _public prototype_ `virtual const IDocumentGraphEdgeCache& GetEdgeCache(const FGuid& InPageID) const override;`
- L197 _public prototype_ `virtual const IDocumentGraphNodeCache& GetNodeCache(const FGuid& InPageID) const override;`
- L198 _public prototype_ `virtual const IDocumentGraphInterfaceCache& GetInterfaceCache() const override;`
- L201 _public prototype_ `virtual void SetBuildPageID(const FGuid& InPageID) override;`
- L204 _public prototype_ `int32 GetTransactionCount() const;`
- L205 _public prototype_ `int32 GetTransactionCount(const FGuid& InPageID) const;`
- L208 _private prototype_ `void Init(const FGuid& InBuildPageID, bool bPrimeCache);`
- L210 _private prototype_ `void OnDependencyAdded(int32 InNewIndex);`
- L211 _private prototype_ `void OnRemoveSwappingDependency(int32 SwapIndex, int32 LastIndex);`
- L212 _private prototype_ `void OnRenamingDependencyClass(const int32 IndexBeingRenamed, const FMetasoundFrontendClassName& NewName);`
- L229 _private prototype_ `FDocumentDependencyCache& GetDependencyCache();` — Private as cached queried data for fast access at document layer is minimal (i.e. dependencies by class id), so API is just passed through document cache interface. Opaque create getter API kept similar to calls above to separately implemented caches for parity.
- L230 _private prototype_ `const FDocumentDependencyCache& GetDependencyCache() const;`
- L233 _private member_ `mutable TSharedPtr<FDocumentDependencyCache> DependencyCache;` — Caches are mutable to be able to be loaded on demand if cache does not exist at the time of an initial query
- L236 _private member_ `mutable TSortedMap<FGuid, TSharedPtr<FDocumentGraphEdgeCache>> EdgeCacheMap;` — Sorted map of PageID to EdgeCache
- L239 _private member_ `mutable TSortedMap<FGuid, TSharedPtr<FDocumentGraphNodeCache>> NodeCacheMap;` — Sorted map of PageID to NodeCache
- L241 _private member_ `mutable TSharedPtr<FDocumentGraphInterfaceCache> InterfaceCache;`
- L243 _private member_ `const FMetasoundFrontendDocument* Document = nullptr;`
- L244 _private member_ `TSharedRef<FDocumentModifyDelegates> ModifyDelegates;`
- L247 _private member_ `int32 TransactionCount = 0;` — Number of transactions processed since builder was instantiated
- L250 _private member_ `FGuid BuildPageID;` — Currently set build PageID, which is the default PageID for API calls that do not specify a targeted PageID.

#### struct `Metasound::Frontend::FDocumentCache::FDocumentDependencyCache`  
`struct FDocumentDependencyCache : public TSharedFromThis<FDocumentDependencyCache>`  
_L214-224_
- inherits: `TSharedFromThis<FDocumentDependencyCache>`
- L216 _public prototype_ `FDocumentDependencyCache(const FMetasoundFrontendDocument& InDocument);`
- L217 _public prototype_ `~FDocumentDependencyCache() = default;`
- L220 _public member_ `TSortedMap<FGuid, int32> IDToIndex;` — Cache of dependency (Class) ID to corresponding class dependency index
- L223 _public member_ `TSortedMap<FNodeRegistryKey, int32> KeyToIndex;` — Cache of version data to corresponding class dependency index

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Metasound`
- L14 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundFrontendDocumentController.h` (Private)


#### class `Metasound::Frontend::FDocumentController`  
`class FDocumentController : public IDocumentController`  
_L15-117_
- inherits: `IDocumentController`
- desc: FDocumentController represents an entire Metasound document.
- L23 _public prototype_ `FDocumentController(FDocumentAccessPtr InDocumentPtr);` — Construct a FDocumentController. @param InDocument - Document to be manipulated.
- L25 _public function_ `static FDocumentHandle CreateDocumentHandle(FDocumentAccessPtr InDocument, bool bReloadBuilder = true)`
- L47 _public function_ `static FConstDocumentHandle CreateDocumentHandle(FConstDocumentAccessPtr InDocument)` — Create a FDocumentController. @param InDocument - Document to be manipulated. @return A document handle.
- L52 _public prototype_ `virtual ~FDocumentController() = default;`
- L54 _public prototype_ `bool IsValid() const override;`
- L56 _public prototype_ `const TArray<FMetasoundFrontendClass>& GetDependencies() const override;`
- L57 _public prototype_ `void IterateDependencies(TFunctionRef<void(FMetasoundFrontendClass&)> InFunction) override;`
- L58 _public prototype_ `void IterateDependencies(TFunctionRef<void(const FMetasoundFrontendClass&)> InFunction) const override;`
- L59 _public prototype_ `const TArray<FMetasoundFrontendGraphClass>& GetSubgraphs() const override;`
- L60 _public prototype_ `const FMetasoundFrontendGraphClass& GetRootGraphClass() const override;`
- L61 _public prototype_ `void SetRootGraphClass(FMetasoundFrontendGraphClass&& InClass) override;`
- L63 _public prototype_ `FConstClassAccessPtr FindDependencyWithID(FGuid InClassID) const override;`
- L64 _public prototype_ `FConstGraphClassAccessPtr FindSubgraphWithID(FGuid InClassID) const override;`
- L65 _public prototype_ `FConstClassAccessPtr FindClassWithID(FGuid InClassID) const override;`
- L67 _public prototype_ `FConstClassAccessPtr FindClass(const FNodeRegistryKey& InKey) const override;`
- L68 _public prototype_ `FConstClassAccessPtr FindClass(const FMetasoundFrontendClassMetadata& InMetadata) const override;`
- L70 _public prototype_ `FConstClassAccessPtr FindOrAddClass(const FNodeRegistryKey& InKey, bool bInRefreshFromRegistry) override;`
- L71 _public prototype_ `FConstClassAccessPtr FindOrAddClass(const FMetasoundFrontendClassMetadata& InMetadata) override;`
- L73 _public prototype_ `FGraphHandle AddDuplicateSubgraph(const IGraphController& InGraph) override;`
- L75 _public prototype_ `const TSet<FMetasoundFrontendVersion>& GetInterfaceVersions() const override;`
- L76 _public prototype_ `void AddInterfaceVersion(const FMetasoundFrontendVersion& InVersion) override;`
- L77 _public prototype_ `void RemoveInterfaceVersion(const FMetasoundFrontendVersion& InVersion) override;`
- L78 _public prototype_ `void ClearInterfaceVersions() override;`
- L80 _public prototype_ `void SetMetadata(const FMetasoundFrontendDocumentMetadata& InMetadata) override;`
- L81 _public prototype_ `const FMetasoundFrontendDocumentMetadata& GetMetadata() const override;`
- L82 _public prototype_ `FMetasoundFrontendDocumentMetadata* GetMetadata() override;`
- L84 _public prototype_ `void RemoveUnreferencedDependencies() override;`
- L85 _public prototype_ `TArray<FConstClassAccessPtr> SynchronizeDependencyMetadata() override;`
- L87 _public prototype_ `FGraphHandle GetRootGraph() override;`
- L88 _public prototype_ `FConstGraphHandle GetRootGraph() const override;`
- L90 _public prototype_ `FDocumentAccessPtr GetDocumentPtr() override;`
- L91 _public prototype_ `const FDocumentAccessPtr GetDocumentPtr() const override;`
- L94 _public prototype_ `TArray<FGraphHandle> GetSubgraphHandles() override;` — Returns an array of all subgraphs for this document.
- L97 _public prototype_ `TArray<FConstGraphHandle> GetSubgraphHandles() const override;` — Returns an array of all subgraphs for this document.
- L100 _public prototype_ `FGraphHandle GetSubgraphWithClassID(FGuid InClassID) override;` — Returns a graphs in the document with the given class ID.
- L103 _public prototype_ `FConstGraphHandle GetSubgraphWithClassID(FGuid InClassID) const override;` — Returns a graphs in the document with the given class ID.
- L105 _public prototype_ `bool ExportToJSONAsset(const FString& InAbsolutePath) const override;`
- L106 _public prototype_ `FString ExportToJSON() const override;`
- L109 _protected prototype_ `FDocumentAccess ShareAccess() override;`
- L110 _protected prototype_ `FConstDocumentAccess ShareAccess() const override;`
- L113 _private prototype_ `void DeduplicateDependencies();`
- L114 _private prototype_ `bool AddDuplicateSubgraph(const FMetasoundFrontendGraphClass& InGraphToCopy, const FMetasoundFrontendDocument& InOtherDocument);`
- L116 _private member_ `FDocumentAccessPtr DocumentPtr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundFrontendGraphController.h` (Private)


#### class `Metasound::Frontend::FGraphController`  
`class FGraphController : public IGraphController`  
_L27-285_
- inherits: `IGraphController`
- desc: FGraphController represents a Metasound graph class.
- L45 _public prototype_ `FGraphController(EPrivateToken InToken, const FInitParams& InParams);` — Constructor takes a private token so it can only be instantiated by using the static creation functions. This protects against some error conditions which would result in a zombie object. The creation methods can detect the error conditions and return an invalid controller on error
- L51 _public prototype_ `static FGraphHandle CreateGraphHandle(const FInitParams& InParams);` — Create a graph handle. @return A graph handle. On error, an invalid handle is returned.
- L57 _public prototype_ `static FConstGraphHandle CreateConstGraphHandle(const FInitParams& InParams);` — Create a graph handle. @return A graph handle. On error, an invalid handle is returned.
- L59 _public prototype_ `virtual ~FGraphController() = default;`
- L61 _public prototype_ `bool IsValid() const override;`
- L63 _public prototype_ `FGuid GetClassID() const override;`
- L66 _public prototype_ `FText GetDisplayName() const override;`
- L69 _public prototype_ `TArray<FVertexName> GetInputVertexNames() const override;`
- L70 _public prototype_ `TArray<FVertexName> GetOutputVertexNames() const override;`
- L71 _public prototype_ `FConstClassInputAccessPtr FindClassInputWithName(const FVertexName& InName) const override;`
- L72 _public prototype_ `FConstClassOutputAccessPtr FindClassOutputWithName(const FVertexName& InName) const override;`
- L73 _public prototype_ `FGuid GetVertexIDForInputVertex(const FVertexName& InInputName) const override;`
- L74 _public prototype_ `FGuid GetVertexIDForOutputVertex(const FVertexName& InOutputName) const override;`
- L76 _public prototype_ `TArray<FNodeHandle> GetNodes() override;`
- L77 _public prototype_ `TArray<FConstNodeHandle> GetConstNodes() const override;`
- L79 _public prototype_ `FConstNodeHandle GetNodeWithID(FGuid InNodeID) const override;`
- L80 _public prototype_ `FNodeHandle GetNodeWithID(FGuid InNodeID) override;`
- L82 _public prototype_ `TArray<FNodeHandle> GetInputNodes() override;`
- L83 _public prototype_ `TArray<FConstNodeHandle> GetConstInputNodes() const override;`
- L85 _public prototype_ `virtual FVariableHandle AddVariable(const FName& InDataType) override;`
- L86 _public prototype_ `virtual FVariableHandle FindVariable(const FGuid& InVariableID) override;`
- L87 _public prototype_ `virtual FConstVariableHandle FindVariable(const FGuid& InVariableID) const override;`
- L88 _public prototype_ `virtual FVariableHandle FindVariableContainingNode(const FGuid& InNodeID) override;`
- L89 _public prototype_ `virtual FConstVariableHandle FindVariableContainingNode(const FGuid& InNodeID) const override;`
- L92 _public prototype_ `virtual bool RemoveVariable(const FGuid& InVariableID) override;` — `UE_DEPRECATED(5.8, "Use the MetaSound Builder API")`
- L94 _public prototype_ `virtual TArray<FVariableHandle> GetVariables() override;`
- L95 _public prototype_ `virtual TArray<FConstVariableHandle> GetVariables() const override;`
- L96 _public prototype_ `virtual FNodeHandle FindOrAddVariableMutatorNode(const FGuid& InVariableID) override;`
- L97 _public prototype_ `virtual FNodeHandle AddVariableAccessorNode(const FGuid& InVariableID) override;`
- L98 _public prototype_ `virtual FNodeHandle AddVariableDeferredAccessorNode(const FGuid& InVariableID) override;`
- L100 _public prototype_ `void ClearGraph() override;`
- L102 _public prototype_ `void IterateNodes(TFunctionRef<void(FNodeHandle)> InFunction, EMetasoundFrontendClassType InClassType) override;`
- L103 _public prototype_ `void IterateConstNodes(TFunctionRef<void(FConstNodeHandle)> InFunction, EMetasoundFrontendClassType InClassType) const override;`
- L105 _public prototype_ `TArray<FNodeHandle> GetOutputNodes() override;`
- L106 _public prototype_ `TArray<FConstNodeHandle> GetConstOutputNodes() const override;`
- L109 _public prototype_ `virtual const FMetasoundFrontendGraphStyle& GetGraphStyle() const override;`
- L110 _public prototype_ `virtual const FMetasoundFrontendInterfaceStyle& GetInputStyle() const override;`
- L111 _public prototype_ `virtual const FMetasoundFrontendInterfaceStyle& GetOutputStyle() const override;`
- L112 _public prototype_ `virtual void SetGraphStyle(FMetasoundFrontendGraphStyle Style) override;`
- L113 _public prototype_ `virtual void SetInputStyle(FMetasoundFrontendInterfaceStyle Style) override;`
- L114 _public prototype_ `virtual void SetOutputStyle(FMetasoundFrontendInterfaceStyle Style) override;`
- L117 _public prototype_ `bool ContainsInputVertex(const FVertexName& InName, const FName& InTypeName) const override;`
- L118 _public prototype_ `bool ContainsInputVertexWithName(const FVertexName& InName) const override;`
- L119 _public prototype_ `bool ContainsOutputVertex(const FVertexName& InName, const FName& InTypeName) const override;`
- L120 _public prototype_ `bool ContainsOutputVertexWithName(const FVertexName& InName) const override;`
- L122 _public prototype_ `FConstNodeHandle GetInputNodeWithName(const FVertexName& InName) const override;`
- L123 _public prototype_ `FConstNodeHandle GetOutputNodeWithName(const FVertexName& InName) const override;`
- L125 _public prototype_ `FNodeHandle GetInputNodeWithName(const FVertexName& InName) override;`
- L126 _public prototype_ `FNodeHandle GetOutputNodeWithName(const FVertexName& InName) override;`
- L128 _public prototype_ `FNodeHandle AddInputVertex(const FMetasoundFrontendClassInput& InDescription) override;`
- L129 _public prototype_ `bool RemoveInputVertex(const FVertexName& InName) override;`
- L131 _public prototype_ `FNodeHandle AddOutputVertex(const FMetasoundFrontendClassOutput& InDescription) override;`
- L132 _public prototype_ `FNodeHandle AddOutputVertex(const FVertexName& InName, const FName InTypeName) override;`
- L133 _public prototype_ `bool RemoveOutputVertex(const FVertexName& InName) override;`
- L135 _public prototype_ `void UpdateInterfaceChangeID() override;`
- L139 _public prototype_ `ELiteralType GetPreferredLiteralTypeForInputVertex(const FVertexName& InInputName) const override;` — This can be used to determine what kind of property editor we should use for the data type of a given input. Will return Invalid if the input couldn't be found, or if the input doesn't support any kind of literals.
- L142 _public prototype_ `UClass* GetSupportedClassForInputVertex(const FVertexName& InInputName) override;` — For inputs whose preferred literal type is UObject or UObjectArray, this can be used to determine the UObject corresponding to that input's datatype.
- L145 _public prototype_ `virtual FMetasoundFrontendLiteral GetDefaultInput(const FGuid& InVertexID) const override;` — `UE_DEPRECATED(5.7, "Use version which provides page order")`
- L147 _public prototype_ `virtual FMetasoundFrontendLiteral GetDefaultInput(const FGuid& InVertexID, TArrayView<const FGuid> InPageOrder) const override;`
- L153 _public prototype_ `virtual bool SetDefaultInput(const FGuid& InVertexID, const FMetasoundFrontendLiteral& InLiteral) override;` — `UE_DEPRECATED(5.7, "Use version which provides page order")`
- L155 _public prototype_ `virtual bool SetDefaultInput(const FGuid& InVertexID, const FMetasoundFrontendLiteral& InLiteral, TArrayView<const FGuid> InPageOrder) override;`
- L156 _public prototype_ `bool SetDefaultInputToDefaultLiteralOfType(const FGuid& InVertexID) override;`
- L160 _public prototype_ `const FText& GetInputDescription(const FVertexName& InName) const override;` — Get the description for the input with the given name.
- L163 _public prototype_ `const FText& GetOutputDescription(const FVertexName& InName) const override;` — Get the description for the output with the given name.
- L166 _public prototype_ `void SetInputDescription(const FVertexName& InName, const FText& InDescription) override;` — Set the description for the input with the given name
- L169 _public prototype_ `void SetOutputDescription(const FVertexName& InName, const FText& InDescription) override;` — Set the description for the input with the given name
- L172 _public prototype_ `void SetInputDisplayName(const FVertexName& InName, const FText& InDisplayName) override;` — Set the display name for the input with the given name
- L175 _public prototype_ `void SetOutputDisplayName(const FVertexName& InName, const FText& InDisplayName) override;` — Set the display name for the output with the given name
- L179 _public prototype_ `int32 GetSortOrderIndexForInput(const FVertexName& InName) const override;`
- L180 _public prototype_ `int32 GetSortOrderIndexForOutput(const FVertexName& InName) const override;`
- L184 _public prototype_ `void SetSortOrderIndexForInput(const FVertexName& InName, int32 InSortOrderIndex) override;`
- L185 _public prototype_ `void SetSortOrderIndexForOutput(const FVertexName& InName, int32 InSortOrderIndex) override;`
- L188 _public prototype_ `FNodeHandle AddNode(const FNodeRegistryKey& InNodeClass, FGuid InNodeGuid) override;`
- L189 _public prototype_ `FNodeHandle AddNode(const FMetasoundFrontendClassMetadata& InClassMetadata, FGuid InNodeGuid) override;`
- L190 _public prototype_ `FNodeHandle AddDuplicateNode(const INodeController& InNode) override;`
- L191 _public prototype_ `FNodeHandle AddTemplateNode(const INodeTemplate& InNodeTemplate, FNodeTemplateGenerateInterfaceParams Params, FGuid InNodeGuid = FGuid::NewGuid()) override;`
- L197 _public prototype_ `bool RemoveNode(INodeController& InNode) override;` — `UE_DEPRECATED(5.8, "Use the MetaSound Builder API")`
- L199 _public prototype_ `const FMetasoundFrontendClassMetadata& GetGraphMetadata() const override;`
- L200 _public prototype_ `void SetGraphMetadata(const FMetasoundFrontendClassMetadata& InClassMetadata) override;`
- L202 _public prototype_ `FNodeHandle CreateEmptySubgraph(const FMetasoundFrontendClassMetadata& InInfo) override;`
- L204 _public prototype_ `FDocumentHandle GetOwningDocument() override;`
- L205 _public prototype_ `FConstDocumentHandle GetOwningDocument() const override;`
- L208 _public prototype_ `virtual const FMetasoundFrontendClassInput* FindInputDescriptionWithName(const FVertexName& InName) const;` — Exposed to aid in transition of controller API to Document Builder API
- L209 _public prototype_ `virtual const FMetasoundFrontendClassInput* FindInputDescriptionWithVertexID(const FGuid& InVertexID) const;`
- L210 _public prototype_ `virtual const FMetasoundFrontendClassOutput* FindOutputDescriptionWithName(const FVertexName& InName) const;`
- L211 _public prototype_ `virtual const FMetasoundFrontendClassOutput* FindOutputDescriptionWithVertexID(const FGuid& InVertexID) const;`
- L215 _protected prototype_ `FDocumentAccess ShareAccess() override;`
- L216 _protected prototype_ `FConstDocumentAccess ShareAccess() const override;`
- L220 _private prototype_ `FGuid FindVariableIDOfVariableContainingNode(const FGuid& InNodeID) const;`
- L221 _private prototype_ `FMetasoundFrontendVariable* FindFrontendVariable(const FGuid& InVariableID);`
- L222 _private prototype_ `const FMetasoundFrontendVariable* FindFrontendVariable(const FGuid& InVariableID) const;`
- L223 _private prototype_ `FNodeHandle FindHeadNodeInVariableStack(const FGuid& InVariableID);`
- L224 _private prototype_ `FNodeHandle FindTailNodeInVariableStack(const FGuid& InVariableID);`
- L226 _private prototype_ `void RemoveNodeIDFromAssociatedVariable(const INodeController& InNode);`
- L228 _private prototype_ `void SpliceVariableNodeFromVariableStack(INodeController& InNode);` — Remove variable node from variable stack, and reconnect variable to remaining nodes.
- L231 _private prototype_ `FNodeHandle AddNode(FConstClassAccessPtr InExistingDependency, FGuid InNodeGuid);`
- L232 _private prototype_ `bool RemoveNode(const FMetasoundFrontendNode& InDesc);`
- L233 _private prototype_ `bool RemoveInput(const FMetasoundFrontendNode& InNode);`
- L234 _private prototype_ `bool RemoveOutput(const FMetasoundFrontendNode& InNode);`
- L236 _private prototype_ `FNodeHandle GetNodeByPredicate(TFunctionRef<bool (const FMetasoundFrontendClass&, const FMetasoundFrontendNode&)> InPredicate);`
- L237 _private prototype_ `FConstNodeHandle GetNodeByPredicate(TFunctionRef<bool (const FMetasoundFrontendClass&, const FMetasoundFrontendNode&)> InPredicate) const;`
- L239 _private prototype_ `TArray<FNodeHandle> GetNodesByPredicate(TFunctionRef<bool (const FMetasoundFrontendClass&, const FMetasoundFrontendNode&)> InFilterFunc);`
- L240 _private prototype_ `TArray<FConstNodeHandle> GetNodesByPredicate(TFunctionRef<bool (const FMetasoundFrontendClass&, const FMetasoundFrontendNode&)> InFilterFunc) const;`
- L255 _private prototype_ `bool ContainsNodesAndClassesByPredicate(TFunctionRef<bool (const FMetasoundFrontendClass&, const FMetasoundFrontendNode&)> InPredicate) const;`
- L256 _private prototype_ `TArray<FNodeAndClass> GetNodesAndClasses();`
- L257 _private prototype_ `TArray<FConstNodeAndClass> GetNodesAndClasses() const;`
- L259 _private prototype_ `TArray<FNodeAndClass> GetNodesAndClassesByPredicate(TFunctionRef<bool (const FMetasoundFrontendClass&, const FMetasoundFrontendNode&)> InPredicate);`
- L260 _private prototype_ `TArray<FConstNodeAndClass> GetNodesAndClassesByPredicate(TFunctionRef<bool (const FMetasoundFrontendClass&, const FMetasoundFrontendNode&)> InPredicate) const;`
- L263 _private prototype_ `TArray<FNodeHandle> GetNodeHandles(TArrayView<const FNodeAndClass> InNodesAndClasses);`
- L264 _private prototype_ `TArray<FConstNodeHandle> GetNodeHandles(TArrayView<const FConstNodeAndClass> InNodesAndClasses) const;`
- L266 _private prototype_ `FNodeHandle GetNodeHandle(const FNodeAndClass& InNodeAndClass);`
- L267 _private prototype_ `FConstNodeHandle GetNodeHandle(const FConstNodeAndClass& InNodeAndClass) const;`
- L269 _private prototype_ `FMetasoundFrontendClassInput* FindInputDescriptionWithName(const FVertexName& InName);`
- L271 _private prototype_ `FMetasoundFrontendClassInput* FindInputDescriptionWithVertexID(const FGuid& InVertexID);`
- L273 _private prototype_ `FMetasoundFrontendClassOutput* FindOutputDescriptionWithName(const FVertexName& InName);`
- L275 _private prototype_ `FMetasoundFrontendClassOutput* FindOutputDescriptionWithVertexID(const FGuid& InVertexID);`
- L277 _private prototype_ `FClassInputAccessPtr FindInputDescriptionWithNodeID(FGuid InNodeID);`
- L278 _private prototype_ `FConstClassInputAccessPtr FindInputDescriptionWithNodeID(FGuid InNodeID) const;`
- L280 _private prototype_ `FClassOutputAccessPtr FindOutputDescriptionWithNodeID(FGuid InNodeID);`
- L281 _private prototype_ `FConstClassOutputAccessPtr FindOutputDescriptionWithNodeID(FGuid InNodeID) const;`
- L283 _private member_ `FGraphClassAccessPtr GraphClassPtr;`
- L284 _private member_ `FDocumentHandle OwningDocument;`

#### enum `Metasound::Frontend::FGraphController::EPrivateToken`  
`enum EPrivateToken`  
_L30-30_
- desc: Private token only allows members or friends to call constructor.
- L30 _public enumerator_ `enum EPrivateToken { Token }; public: struct FInitParams { FGraphClassAccessPtr GraphClassPtr; FDocumentHandle OwningDocument;` — Private token only allows members or friends to call constructor.

#### struct `Metasound::Frontend::FGraphController::FInitParams`  
`struct FInitParams`  
_L34-38_
- L36 _public member_ `FGraphClassAccessPtr GraphClassPtr;`
- L37 _public member_ `FDocumentHandle OwningDocument;`

#### struct `Metasound::Frontend::FGraphController::FNodeAndClass`  
`struct FNodeAndClass`  
_L243-247_
- L245 _public member_ `FNodeAccessPtr Node;`
- L246 _public member_ `FConstClassAccessPtr Class;`

#### struct `Metasound::Frontend::FGraphController::FConstNodeAndClass`  
`struct FConstNodeAndClass`  
_L249-253_
- L251 _public member_ `FConstNodeAccessPtr Node;`
- L252 _public member_ `FConstClassAccessPtr Class;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Metasound`
- L19 _namespace_ `namespace Frontend` (scope `Metasound`)
- L23 _prototype_ `const FMetasoundFrontendGraph& FindConstBuildGraphChecked(const FMetasoundFrontendGraphClass& InGraphClass);` (scope `Metasound::Frontend`) — Convenience functions used for finding targeted graph to mutate as the transition away from controllers is on-going, however documents can now contain multiple graph topologies (i.e. paged graphs) to select from.
- L24 _prototype_ `FMetasoundFrontendGraph& FindBuildGraphChecked(FMetasoundFrontendGraphClass& InGraphClass);` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundFrontendInputController.h` (Private)


#### class `Metasound::Frontend::FBaseInputController`  
`class FBaseInputController : public IInputController`  
_L18-97_
- inherits: `IInputController`
- desc: FBaseInputController provides common functionality for multiple derived input controllers.
- L20 _private typedef_ `using FRegistry = FMetasoundFrontendRegistryContainer;`
- L33 _public prototype_ `FBaseInputController(const FInitParams& InParams);` — Construct the input controller base.
- L35 _public prototype_ `virtual ~FBaseInputController() = default;`
- L37 _public prototype_ `virtual bool IsValid() const override;`
- L39 _public prototype_ `virtual FGuid GetID() const override;`
- L40 _public prototype_ `virtual const FName& GetDataType() const override;`
- L41 _public prototype_ `virtual const FVertexName& GetName() const override;`
- L42 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetVertexAccessType() const override;`
- L43 _public prototype_ `virtual bool ClearLiteral() override;`
- L44 _public prototype_ `virtual const FMetasoundFrontendLiteral* GetLiteral() const override;`
- L45 _public prototype_ `virtual void SetLiteral(const FMetasoundFrontendLiteral& InLiteral) override;`
- L47 _public prototype_ `virtual const FMetasoundFrontendLiteral* GetClassDefaultLiteral() const override;`
- L51 _public function_ `virtual void SetName(const FVertexName& InName) override` — This only exists to allow for transform fix-ups to easily cleanup input/output vertex names & should not be used for typical edit or runtime callsites.
- L54 _public prototype_ `virtual FText GetDisplayName() const override;`
- L55 _public prototype_ `virtual const FText& GetTooltip() const override;`
- L58 _public prototype_ `virtual const FMetasoundFrontendVertexMetadata& GetMetadata() const override;` — Input metadata
- L62 _public prototype_ `virtual FGuid GetOwningNodeID() const override;` — Owning node info
- L63 _public prototype_ `virtual FNodeHandle GetOwningNode() override;`
- L64 _public prototype_ `virtual FConstNodeHandle GetOwningNode() const override;`
- L67 _public prototype_ `virtual bool IsConnectionUserModifiable() const override;` — Connection info
- L68 _public prototype_ `virtual bool IsConnected() const override;`
- L69 _public prototype_ `virtual FOutputHandle GetConnectedOutput() override;`
- L70 _public prototype_ `virtual FConstOutputHandle GetConnectedOutput() const override;`
- L72 _public prototype_ `virtual FConnectability CanConnectTo(const IOutputController& InController) const override;`
- L73 _public prototype_ `virtual bool Connect(IOutputController& InController) override;`
- L76 _public prototype_ `virtual bool ConnectWithConverterNode(IOutputController& InController, const FConverterNodeInfo& InNodeClassName) override;` — Connection controls.
- L78 _public prototype_ `virtual bool Disconnect(IOutputController& InController) override;`
- L79 _public prototype_ `virtual bool Disconnect() override;`
- L81 _public prototype_ `virtual void ClearConnectedObjectLiterals() override;`
- L86 _protected prototype_ `virtual FDocumentAccess ShareAccess() override;`
- L87 _protected prototype_ `virtual FConstDocumentAccess ShareAccess() const override;`
- L89 _protected prototype_ `const FMetasoundFrontendEdge* FindEdge() const;`
- L90 _protected prototype_ `FMetasoundFrontendEdge* FindEdge();`
- L92 _protected member_ `FGuid ID;`
- L93 _protected member_ `FConstVertexAccessPtr NodeVertexPtr;`
- L94 _protected member_ `FConstClassInputAccessPtr ClassInputPtr;`
- L95 _protected member_ `FGraphAccessPtr GraphPtr;`
- L96 _protected member_ `FNodeHandle OwningNode;`

#### struct `Metasound::Frontend::FBaseInputController::FInitParams`  
`struct FInitParams`  
_L23-30_
- L25 _public member_ `FGuid ID;`
- L26 _public member_ `FConstVertexAccessPtr NodeVertexPtr;`
- L27 _public member_ `FConstClassInputAccessPtr ClassInputPtr;`
- L28 _public member_ `FGraphAccessPtr GraphPtr;`
- L29 _public member_ `FNodeHandle OwningNode;`

#### class `Metasound::Frontend::FOutputNodeInputController`  
`class FOutputNodeInputController : public FBaseInputController`  
_L105-145_
- inherits: `FBaseInputController`
- desc: FOutputNodeInputController represents the input vertex of an output node. FOutputNodeInputController is largely to represent outputs exposed from a graph.
- L107 _private typedef_ `using FRegistry = FMetasoundFrontendRegistryContainer;`
- L120 _public prototype_ `FOutputNodeInputController(const FInitParams& InParams);` — Constructs the input controller.
- L122 _public prototype_ `virtual bool IsValid() const override;`
- L125 _public prototype_ `virtual FText GetDisplayName() const override;`
- L126 _public prototype_ `virtual const FText& GetTooltip() const override;`
- L129 _public prototype_ `virtual const FMetasoundFrontendVertexMetadata& GetMetadata() const override;` — Input metadata
- L132 _public prototype_ `virtual void SetName(const FVertexName& InName) override;`
- L133 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetVertexAccessType() const override;`
- L137 _protected prototype_ `virtual FDocumentAccess ShareAccess() override;`
- L138 _protected prototype_ `virtual FConstDocumentAccess ShareAccess() const override;`
- L142 _private member_ `mutable FText CachedDisplayName;`
- L144 _private member_ `FConstClassOutputAccessPtr OwningGraphClassOutputPtr;`

#### struct `Metasound::Frontend::FOutputNodeInputController::FInitParams`  
`struct FInitParams`  
_L109-117_
- L111 _public member_ `FGuid ID;`
- L112 _public member_ `FConstVertexAccessPtr NodeVertexPtr;`
- L113 _public member_ `FConstClassInputAccessPtr ClassInputPtr;`
- L114 _public member_ `FConstClassOutputAccessPtr OwningGraphClassOutputPtr;`
- L115 _public member_ `FGraphAccessPtr GraphPtr;`
- L116 _public member_ `FNodeHandle OwningNode;`

#### class `Metasound::Frontend::FInputNodeInputController`  
`class FInputNodeInputController : public FBaseInputController`  
_L153-192_
- inherits: `FBaseInputController`
- desc: FInputNodeInputController represents the input vertex of an output node. FInputNodeInputController is largely to represent outputs exposed from a graph.
- L155 _private typedef_ `using FRegistry = FMetasoundFrontendRegistryContainer;`
- L168 _public prototype_ `FInputNodeInputController(const FInitParams& InParams);` — Constructs the input controller.
- L170 _public prototype_ `virtual bool IsValid() const override;`
- L173 _public prototype_ `virtual FText GetDisplayName() const override;`
- L174 _public prototype_ `virtual const FText& GetTooltip() const override;`
- L177 _public prototype_ `virtual const FMetasoundFrontendVertexMetadata& GetMetadata() const override;` — Input metadata
- L180 _public prototype_ `virtual void SetName(const FVertexName& InName) override;`
- L181 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetVertexAccessType() const override;`
- L183 _public prototype_ `virtual bool IsConnectionUserModifiable() const override;`
- L184 _public prototype_ `virtual FConnectability CanConnectTo(const IOutputController& InController) const override;`
- L185 _public prototype_ `virtual bool Connect(IOutputController& InController) override;`
- L188 _public prototype_ `virtual bool ConnectWithConverterNode(IOutputController& InController, const FConverterNodeInfo& InNodeClassName) override;` — Connection controls.
- L191 _private member_ `FConstClassInputAccessPtr OwningGraphClassInputPtr;`

#### struct `Metasound::Frontend::FInputNodeInputController::FInitParams`  
`struct FInitParams`  
_L157-165_
- L159 _public member_ `FGuid ID;`
- L160 _public member_ `FConstVertexAccessPtr NodeVertexPtr;`
- L161 _public member_ `FConstClassInputAccessPtr ClassInputPtr;`
- L162 _public member_ `FConstClassInputAccessPtr OwningGraphClassInputPtr;`
- L163 _public member_ `FGraphAccessPtr GraphPtr;`
- L164 _public member_ `FNodeHandle OwningNode;`

#### class `Metasound::Frontend::FVariableInputController`  
`class FVariableInputController : public FBaseInputController`  
_L195-205_
- inherits: `FBaseInputController`
- desc: Input controller for variable data type.
- L198 _public typedef_ `using FInitParams = FBaseInputController::FInitParams;`
- L200 _public prototype_ `FVariableInputController(const FInitParams& InParams);`
- L201 _public prototype_ `virtual ~FVariableInputController() = default;`
- L204 _public prototype_ `virtual bool IsConnectionUserModifiable() const override;` — Variable data type connections are not modifiable by users

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Metasound`
- L13 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundFrontendInvalidController.h` (Private)


#### class `Metasound::Frontend::FInvalidOutputController`  
`class FInvalidOutputController : public IOutputController`  
_L56-95_
- inherits: `IOutputController`
- desc: FInvalidOutputController is a controller which is always invalid. All methods return defaults and return error flags or invalid values.
- L59 _public prototype_ `FInvalidOutputController() = default;`
- L61 _public prototype_ `virtual ~FInvalidOutputController() = default;`
- L64 _public function_ `virtual bool IsValid() const override`
- L65 _public function_ `virtual FGuid GetID() const override`
- L66 _public function_ `virtual const FName& GetDataType() const override`
- L67 _public function_ `virtual const FVertexName& GetName() const override`
- L68 _public function_ `virtual EMetasoundFrontendVertexAccessType GetVertexAccessType() const override`
- L71 _public function_ `virtual FText GetDisplayName() const override`
- L72 _public function_ `virtual const FText& GetTooltip() const override`
- L73 _public function_ `virtual const FMetasoundFrontendVertexMetadata& GetMetadata() const override`
- L76 _public function_ `virtual FGuid GetOwningNodeID() const override`
- L77 _public prototype_ `virtual FNodeHandle GetOwningNode() override;`
- L78 _public prototype_ `virtual FConstNodeHandle GetOwningNode() const override;`
- L79 _public function_ `virtual void SetName(const FVertexName& InName) override`
- L80 _public function_ `virtual bool IsConnected() const override`
- L81 _public function_ `virtual TArray<FInputHandle> GetConnectedInputs() override`
- L82 _public function_ `virtual TArray<FConstInputHandle> GetConstConnectedInputs() const override`
- L83 _public function_ `virtual bool Disconnect() override`
- L85 _public function_ `virtual bool IsConnectionUserModifiable() const override`
- L86 _public function_ `virtual FConnectability CanConnectTo(const IInputController& InController) const override`
- L87 _public function_ `virtual bool Connect(IInputController& InController) override`
- L88 _public function_ `virtual bool ConnectWithConverterNode(IInputController& InController, const FConverterNodeInfo& InNodeClassName) override`
- L89 _public function_ `virtual bool Disconnect(IInputController& InController) override`
- L92 _protected function_ `virtual FDocumentAccess ShareAccess() override`
- L93 _protected function_ `virtual FConstDocumentAccess ShareAccess() const override`

#### class `Metasound::Frontend::FInvalidInputController`  
`class FInvalidInputController : public IInputController`  
_L101-144_
- inherits: `IInputController`
- desc: FInvalidInputController is a controller which is always invalid. All methods return defaults and return error flags or invalid values.
- L104 _public prototype_ `FInvalidInputController() = default;`
- L105 _public prototype_ `virtual ~FInvalidInputController() = default;`
- L107 _public function_ `virtual bool IsValid() const override`
- L108 _public function_ `virtual FGuid GetID() const override`
- L109 _public function_ `virtual bool IsConnected() const override`
- L110 _public function_ `virtual const FName& GetDataType() const override`
- L111 _public function_ `virtual const FVertexName& GetName() const override`
- L112 _public function_ `virtual EMetasoundFrontendVertexAccessType GetVertexAccessType() const override`
- L115 _public function_ `virtual FText GetDisplayName() const override`
- L116 _public function_ `virtual const FText& GetTooltip() const override`
- L117 _public function_ `virtual const FMetasoundFrontendVertexMetadata& GetMetadata() const override`
- L120 _public function_ `virtual bool ClearLiteral() override`
- L121 _public function_ `virtual const FMetasoundFrontendLiteral* GetLiteral() const override`
- L122 _public function_ `virtual void SetLiteral(const FMetasoundFrontendLiteral& InLiteral)`
- L123 _public function_ `virtual const FMetasoundFrontendLiteral* GetClassDefaultLiteral() const override`
- L124 _public function_ `virtual FGuid GetOwningNodeID() const override`
- L125 _public prototype_ `virtual FNodeHandle GetOwningNode() override;`
- L126 _public prototype_ `virtual FConstNodeHandle GetOwningNode() const override;`
- L128 _public function_ `virtual bool IsConnectionUserModifiable() const override`
- L129 _public function_ `virtual FOutputHandle GetConnectedOutput() override`
- L130 _public function_ `virtual FConstOutputHandle GetConnectedOutput() const override`
- L131 _public function_ `virtual bool Disconnect() override`
- L133 _public function_ `virtual void SetName(const FVertexName& InName) override`
- L135 _public function_ `virtual FConnectability CanConnectTo(const IOutputController& InController) const override`
- L136 _public function_ `virtual bool Connect(IOutputController& InController) override`
- L137 _public function_ `virtual bool ConnectWithConverterNode(IOutputController& InController, const FConverterNodeInfo& InNodeClassName) override`
- L138 _public function_ `virtual bool Disconnect(IOutputController& InController) override`
- L140 _public function_ `virtual void ClearConnectedObjectLiterals() override`
- L142 _protected function_ `virtual FDocumentAccess ShareAccess() override`
- L143 _protected function_ `virtual FConstDocumentAccess ShareAccess() const override`

#### class `Metasound::Frontend::FInvalidVariableController`  
`class FInvalidVariableController : public IVariableController`  
_L146-193_
- inherits: `IVariableController`
- L149 _public prototype_ `FInvalidVariableController() = default;`
- L150 _public prototype_ `virtual ~FInvalidVariableController() = default;`
- L153 _public function_ `virtual bool IsValid() const override` — Returns true if the controller is in a valid state.
- L155 _public function_ `virtual FGuid GetID() const override`
- L158 _public function_ `virtual const FName& GetDataType() const override` — Returns the data type name associated with this output.
- L161 _public function_ `virtual const FName& GetName() const override` — Returns the name associated with this variable.
- L162 _public function_ `virtual void SetName(const FName&) override`
- L166 _public function_ `virtual FText GetDisplayName() const override` — Returns the human readable name associated with this output.
- L167 _public function_ `virtual void SetDisplayName(const FText&) override`
- L168 _public function_ `virtual FText GetDescription() const override`
- L169 _public function_ `virtual void SetDescription(const FText&) override`
- L172 _public function_ `virtual FNodeHandle FindMutatorNode() override`
- L173 _public function_ `virtual FConstNodeHandle FindMutatorNode() const override`
- L174 _public function_ `virtual TArray<FNodeHandle> FindAccessorNodes() override`
- L175 _public function_ `virtual TArray<FConstNodeHandle> FindAccessorNodes() const override`
- L176 _public function_ `virtual TArray<FNodeHandle> FindDeferredAccessorNodes() override`
- L177 _public function_ `virtual TArray<FConstNodeHandle> FindDeferredAccessorNodes() const override`
- L180 _public function_ `virtual FGraphHandle GetOwningGraph() override` — Returns a FGraphHandle to the node which owns this output.
- L183 _public function_ `virtual FConstGraphHandle GetOwningGraph() const override` — Returns a FConstGraphHandle to the node which owns this output.
- L186 _public function_ `virtual const FMetasoundFrontendLiteral& GetLiteral() const override` — Returns the value for the given variable instance if set.
- L189 _public function_ `virtual bool SetLiteral(const FMetasoundFrontendLiteral& InLiteral) override` — Sets the value for the given variable instance
- L191 _protected function_ `virtual FDocumentAccess ShareAccess() override`
- L192 _protected function_ `virtual FConstDocumentAccess ShareAccess() const override`

#### class `Metasound::Frontend::FInvalidNodeController`  
`class FInvalidNodeController : public INodeController`  
_L200-303_
- inherits: `INodeController`
- desc: FInvalidNodeController is a controller which is always invalid. All methods return defaults and return error flags or invalid values.
- L204 _public prototype_ `FInvalidNodeController() = default;`
- L205 _public prototype_ `virtual ~FInvalidNodeController() = default;`
- L207 _public function_ `virtual bool IsValid() const override`
- L209 _public function_ `virtual TArray<FInputHandle> GetInputs() override`
- L210 _public function_ `virtual TArray<FOutputHandle> GetOutputs() override`
- L211 _public function_ `virtual TArray<FConstInputHandle> GetConstInputs() const override`
- L212 _public function_ `virtual TArray<FConstOutputHandle> GetConstOutputs() const override`
- L214 _public function_ `virtual FInputHandle GetInputWithVertexName(const FVertexName& InName) override`
- L215 _public function_ `virtual FConstInputHandle GetConstInputWithVertexName(const FVertexName& InName) const override`
- L216 _public function_ `virtual FOutputHandle GetOutputWithVertexName(const FVertexName& InName) override`
- L217 _public function_ `virtual FConstOutputHandle GetConstOutputWithVertexName(const FVertexName& InName) const override`
- L218 _public function_ `virtual FInputHandle GetInputWithID(FGuid InVertexID) override`
- L219 _public function_ `virtual FOutputHandle GetOutputWithID(FGuid InVertexID) override`
- L220 _public function_ `virtual FConstInputHandle GetInputWithID(FGuid InVertexID) const override`
- L221 _public function_ `virtual FConstOutputHandle GetOutputWithID(FGuid InVertexID) const override`
- L224 _public function_ `virtual const FMetasoundFrontendNodeStyle& GetNodeStyle() const override`
- L225 _public function_ `virtual void SetNodeStyle(const FMetasoundFrontendNodeStyle& InNodeStyle) override`
- L228 _public function_ `virtual void SetNodeName(const FVertexName& InName) override`
- L230 _public function_ `virtual FNodeHandle ReplaceWithVersion(const FMetasoundFrontendVersionNumber& InNewVersion, TArray<FVertexNameAndType>* OutDisconnectedInputs, TArray<FVertexNameAndType>* OutDisconnectedOutputs) override`
- L233 _public function_ `virtual bool CanAddInput(const FVertexName& InVertexName) const override`
- L234 _public function_ `virtual FInputHandle AddInput(const FVertexName& InVertexName, const FMetasoundFrontendLiteral* InDefault) override`
- L235 _public function_ `virtual bool RemoveInput(FGuid InVertexID) override`
- L237 _public function_ `virtual bool CanAddOutput(const FVertexName& InVertexName) const override`
- L238 _public function_ `virtual FInputHandle AddOutput(const FVertexName& InVertexName, const FMetasoundFrontendLiteral* InDefault) override`
- L239 _public function_ `virtual bool RemoveOutput(FGuid InVertexID) override`
- L241 _public function_ `virtual bool ClearInputLiteral(FGuid InVertexID) override`
- L242 _public function_ `virtual const FMetasoundFrontendLiteral* GetInputLiteral(const FGuid& InVertexID) const override`
- L243 _public function_ `virtual void SetInputLiteral(const FMetasoundFrontendVertexLiteral& InVertexLiteral) override`
- L245 _public function_ `virtual const FMetasoundFrontendClassInterface& GetClassInterface() const override`
- L246 _public function_ `virtual const FMetasoundFrontendClassMetadata& GetClassMetadata() const override`
- L248 _public function_ `virtual const FMetasoundFrontendNodeInterface& GetNodeInterface() const override`
- L251 _public function_ `virtual const FMetasoundFrontendInterfaceStyle& GetInputStyle() const override`
- L252 _public function_ `virtual const FMetasoundFrontendInterfaceStyle& GetOutputStyle() const override`
- L253 _public function_ `virtual const FMetasoundFrontendClassStyle& GetClassStyle() const override`
- L255 _public function_ `virtual const FText& GetDescription() const override`
- L259 _public function_ `virtual const FMetasoundFrontendVersion& GetInterfaceVersion() const` — `UE_DEPRECATED(5.8, "Controllers are being actively deprecated, and this call was not thread safe in certain contexts")`
- L262 _public function_ `virtual bool IsInterfaceMember() const override` — `UE_DEPRECATED(5.8, "Controllers are being actively deprecated, and this call was not thread safe in certain contexts")`
- L265 _public function_ `virtual bool DiffAgainstRegistryInterface(FClassInterfaceUpdates& OutInterfaceUpdates, bool bInUseHighestMinorVersion, bool bInForceRegeneratedClassInterfaceOverride) const override`
- L266 _public function_ `virtual bool CanAutoUpdate(FClassInterfaceUpdates& OutInterfaceUpdates) const override`
- L269 _public prototype_ `virtual TSharedRef<IGraphController> AsGraph() override;`
- L270 _public prototype_ `virtual TSharedRef<const IGraphController> AsGraph() const override;`
- L272 _public function_ `virtual FGuid GetID() const override`
- L273 _public function_ `virtual FGuid GetClassID() const override`
- L275 _public function_ `virtual FGuid GetOwningGraphClassID() const override`
- L276 _public prototype_ `virtual TSharedRef<IGraphController> GetOwningGraph() override;`
- L277 _public prototype_ `virtual TSharedRef<const IGraphController> GetOwningGraph() const override;`
- L279 _public function_ `virtual void IterateInputs(TUniqueFunction<void(FInputHandle)> InFunction) override`
- L280 _public function_ `virtual void IterateConstInputs(TUniqueFunction<void(FConstInputHandle)> InFunction) const override`
- L282 _public function_ `virtual void IterateOutputs(TUniqueFunction<void(FOutputHandle)> InFunction) override`
- L283 _public function_ `virtual void IterateConstOutputs(TUniqueFunction<void(FConstOutputHandle)> InFunction) const override`
- L285 _public function_ `virtual int32 GetNumInputs() const override`
- L286 _public function_ `virtual int32 GetNumOutputs() const override`
- L288 _public function_ `virtual const FVertexName& GetNodeName() const override`
- L290 _public function_ `virtual void SetNodeConfiguration(TInstancedStruct<FMetaSoundFrontendNodeConfiguration> InConfig) override`
- L291 _public function_ `virtual TConstStructView<FMetaSoundFrontendNodeConfiguration> GetNodeConfiguration() const override`
- L294 _public function_ `virtual FText GetDisplayName() const override`
- L295 _public function_ `virtual const FText& GetDisplayTitle() const override`
- L296 _public function_ `virtual void SetDescription(const FText& InDescription) override`
- L297 _public function_ `virtual void SetDisplayName(const FText& InText) override`
- L301 _protected function_ `virtual FDocumentAccess ShareAccess() override`
- L302 _protected function_ `virtual FConstDocumentAccess ShareAccess() const override`

#### class `Metasound::Frontend::FInvalidGraphController`  
`class FInvalidGraphController : public IGraphController`  
_L309-452_
- inherits: `IGraphController`
- desc: FInvalidGraphController is a controller which is always invalid. All methods return defaults and return error flags or invalid values.
- L312 _public prototype_ `FInvalidGraphController() = default;`
- L313 _public prototype_ `virtual ~FInvalidGraphController() = default;`
- L315 _public function_ `virtual bool IsValid() const override`
- L316 _public function_ `virtual FGuid GetClassID() const override`
- L319 _public function_ `virtual FText GetDisplayName() const override`
- L322 _public function_ `virtual TArray<FVertexName> GetInputVertexNames() const override`
- L323 _public function_ `virtual TArray<FVertexName> GetOutputVertexNames() const override`
- L325 _public function_ `virtual TArray<FNodeHandle> GetNodes() override`
- L326 _public function_ `virtual TArray<FConstNodeHandle> GetConstNodes() const override`
- L328 _public function_ `virtual FConstNodeHandle GetNodeWithID(FGuid InNodeID) const override`
- L329 _public function_ `virtual FNodeHandle GetNodeWithID(FGuid InNodeID) override`
- L331 _public function_ `virtual TArray<FNodeHandle> GetOutputNodes() override`
- L332 _public function_ `virtual TArray<FNodeHandle> GetInputNodes() override`
- L333 _public function_ `virtual TArray<FConstNodeHandle> GetConstOutputNodes() const override`
- L334 _public function_ `virtual TArray<FConstNodeHandle> GetConstInputNodes() const override`
- L336 _public function_ `virtual FVariableHandle AddVariable(const FName& InDataTypeName) override`
- L337 _public function_ `virtual FVariableHandle FindVariable(const FGuid& InVariableID) override`
- L338 _public function_ `virtual FConstVariableHandle FindVariable(const FGuid& InVariableID) const`
- L339 _public function_ `virtual FVariableHandle FindVariableContainingNode(const FGuid& InNodeID) override`
- L340 _public function_ `virtual FConstVariableHandle FindVariableContainingNode(const FGuid& InNodeID) const override`
- L341 _public function_ `virtual TArray<FVariableHandle> GetVariables() override`
- L342 _public function_ `virtual TArray<FConstVariableHandle> GetVariables() const override`
- L343 _public function_ `virtual FNodeHandle FindOrAddVariableMutatorNode(const FGuid& InVariableID) override`
- L344 _public function_ `virtual FNodeHandle AddVariableAccessorNode(const FGuid& InVariableID) override`
- L345 _public function_ `virtual FNodeHandle AddVariableDeferredAccessorNode(const FGuid& InVariableID) override`
- L348 _public function_ `virtual const FMetasoundFrontendGraphStyle& GetGraphStyle() const override`
- L349 _public function_ `virtual void SetGraphStyle(FMetasoundFrontendGraphStyle InStyle) override`
- L350 _public function_ `virtual const FMetasoundFrontendInterfaceStyle& GetInputStyle() const override`
- L351 _public function_ `virtual const FMetasoundFrontendInterfaceStyle& GetOutputStyle() const override`
- L352 _public function_ `virtual void SetInputStyle(FMetasoundFrontendInterfaceStyle InStyle) override`
- L353 _public function_ `virtual void SetOutputStyle(FMetasoundFrontendInterfaceStyle InStyle) override`
- L356 _public function_ `virtual void ClearGraph() override`
- L358 _public function_ `virtual void IterateConstNodes(TFunctionRef<void(FConstNodeHandle)> InFunction, EMetasoundFrontendClassType InClassType ) const override`
- L359 _public function_ `virtual void IterateNodes(TFunctionRef<void(FNodeHandle)> InFunction, EMetasoundFrontendClassType InClassType ) override`
- L361 _public function_ `virtual bool ContainsOutputVertex(const FVertexName& InName, const FName& InTypeName) const override`
- L362 _public function_ `virtual bool ContainsOutputVertexWithName(const FVertexName& InName) const override`
- L363 _public function_ `virtual bool ContainsInputVertex(const FVertexName& InName, const FName& InTypeName) const override`
- L364 _public function_ `virtual bool ContainsInputVertexWithName(const FVertexName& InName) const override`
- L366 _public function_ `virtual FConstNodeHandle GetOutputNodeWithName(const FVertexName& InName) const override`
- L367 _public function_ `virtual FConstNodeHandle GetInputNodeWithName(const FVertexName& InName) const override`
- L368 _public function_ `virtual FNodeHandle GetOutputNodeWithName(const FVertexName& InName) override`
- L369 _public function_ `virtual FNodeHandle GetInputNodeWithName(const FVertexName& InName) override`
- L371 _public function_ `virtual FConstClassInputAccessPtr FindClassInputWithName(const FVertexName& InName) const override`
- L372 _public function_ `virtual FConstClassOutputAccessPtr FindClassOutputWithName(const FVertexName& InName) const override`
- L374 _public function_ `virtual FNodeHandle AddInputVertex(const FMetasoundFrontendClassInput& InDescription) override`
- L375 _public function_ `virtual bool RemoveInputVertex(const FVertexName& InputName) override`
- L377 _public function_ `virtual FNodeHandle AddOutputVertex(const FMetasoundFrontendClassOutput& InDescription) override`
- L378 _public function_ `virtual TSharedRef<INodeController> AddOutputVertex(const FVertexName& InName, const FName InTypeName) override`
- L379 _public function_ `virtual bool RemoveOutputVertex(const FVertexName& OutputName) override`
- L383 _public function_ `virtual ELiteralType GetPreferredLiteralTypeForInputVertex(const FVertexName& InInputName) const override` — This can be used to determine what kind of property editor we should use for the data type of a given input. Will return Invalid if the input couldn't be found, or if the input doesn't support any kind of literals.
- L386 _public function_ `virtual UClass* GetSupportedClassForInputVertex(const FVertexName& InInputName) override` — For inputs whose preferred literal type is UObject or UObjectArray, this can be used to determine the UObject corresponding to that input's datatype.
- L388 _public function_ `virtual FGuid GetVertexIDForInputVertex(const FVertexName& InInputName) const override`
- L389 _public function_ `virtual FGuid GetVertexIDForOutputVertex(const FVertexName& InOutputName) const override`
- L391 _public function_ `virtual FMetasoundFrontendLiteral GetDefaultInput(const FGuid& InVertexID) const override` — `UE_DEPRECATED(5.7, "Use version which provides page order")`
- L393 _public function_ `virtual FMetasoundFrontendLiteral GetDefaultInput(const FGuid& InVertexID, TArrayView<const FGuid> InPageOrder) const override`
- L399 _public function_ `virtual bool SetDefaultInput(const FGuid& InVertexID, const FMetasoundFrontendLiteral& InLiteral) override` — `UE_DEPRECATED(5.7, "Use version which provides page order")`
- L401 _public function_ `virtual bool SetDefaultInput(const FGuid& InVertexID, const FMetasoundFrontendLiteral& InLiteral, TArrayView<const FGuid> InPageOrder) override`
- L403 _public function_ `virtual bool SetDefaultInputToDefaultLiteralOfType(const FGuid& InVertexID) override`
- L406 _public function_ `virtual const FText& GetInputDescription(const FVertexName& InName) const override`
- L407 _public function_ `virtual const FText& GetOutputDescription(const FVertexName& InName) const override`
- L409 _public function_ `virtual void SetInputDescription(const FVertexName& InName, const FText& InDescription) override`
- L410 _public function_ `virtual void SetOutputDescription(const FVertexName& InName, const FText& InDescription) override`
- L411 _public function_ `virtual void SetInputDisplayName(const FVertexName& InName, const FText& InDisplayName) override`
- L412 _public function_ `virtual void SetOutputDisplayName(const FVertexName& InName, const FText& InDisplayName) override`
- L415 _public function_ `virtual int32 GetSortOrderIndexForInput(const FVertexName& InName) const`
- L416 _public function_ `virtual int32 GetSortOrderIndexForOutput(const FVertexName& InName) const`
- L419 _public function_ `virtual void SetSortOrderIndexForInput(const FVertexName& InName, int32 InSortOrderIndex)`
- L420 _public function_ `virtual void SetSortOrderIndexForOutput(const FVertexName& InName, int32 InSortOrderIndex)`
- L423 _public function_ `virtual FNodeHandle AddNode(const FNodeRegistryKey& InNodeClass, FGuid InNodeGuid) override`
- L424 _public function_ `virtual FNodeHandle AddNode(const FMetasoundFrontendClassMetadata& InNodeClass, FGuid InNodeGuid) override`
- L425 _public function_ `virtual FNodeHandle AddDuplicateNode(const INodeController& InNode) override`
- L426 _public function_ `virtual FNodeHandle AddTemplateNode(const FNodeRegistryKey& InNodeClass, FMetasoundFrontendNodeInterface&& InNodeInterface, FGuid InNodeGuid) override`
- L427 _public function_ `virtual FNodeHandle AddTemplateNode(const INodeTemplate& InNodeTemplate, FNodeTemplateGenerateInterfaceParams Params, FGuid InNodeGuid = FGuid::NewGuid()) override`
- L430 _public function_ `virtual bool RemoveNode(INodeController& InNode) override` — `UE_DEPRECATED(5.8, "Use the MetaSound Builder API")`
- L433 _public function_ `virtual const FMetasoundFrontendClassMetadata& GetGraphMetadata() const override` — Returns the metadata for the current graph, including the name, description and author.
- L435 _public function_ `virtual void SetGraphMetadata(const FMetasoundFrontendClassMetadata& InMetadata) override`
- L437 _public function_ `virtual FNodeHandle CreateEmptySubgraph(const FMetasoundFrontendClassMetadata& InInfo) override`
- L439 _public prototype_ `virtual FDocumentHandle GetOwningDocument() override;`
- L440 _public prototype_ `virtual FConstDocumentHandle GetOwningDocument() const override;`
- L442 _public function_ `virtual void UpdateInterfaceChangeID() override`
- L444 _public function_ `virtual const FMetasoundFrontendClassInput* FindInputDescriptionWithName(const FVertexName& InName) const override`
- L445 _public function_ `virtual const FMetasoundFrontendClassInput* FindInputDescriptionWithVertexID(const FGuid& InVertexID) const override`
- L446 _public function_ `virtual const FMetasoundFrontendClassOutput* FindOutputDescriptionWithName(const FVertexName& InName) const override`
- L447 _public function_ `virtual const FMetasoundFrontendClassOutput* FindOutputDescriptionWithVertexID(const FGuid& InVertexID) const override`
- L450 _protected function_ `virtual FDocumentAccess ShareAccess() override`
- L451 _protected function_ `virtual FConstDocumentAccess ShareAccess() const override`

#### class `Metasound::Frontend::FInvalidDocumentController`  
`class FInvalidDocumentController : public IDocumentController`  
_L458-515_
- inherits: `IDocumentController`
- desc: FInvalidDocumentController is a controller which is always invalid. All methods return defaults and return error flags or invalid values.
- L461 _public prototype_ `FInvalidDocumentController() = default;`
- L462 _public prototype_ `virtual ~FInvalidDocumentController() = default;`
- L464 _public function_ `virtual bool IsValid() const override`
- L466 _public function_ `virtual const TArray<FMetasoundFrontendClass>& GetDependencies() const override`
- L467 _public function_ `virtual void IterateDependencies(TFunctionRef<void(FMetasoundFrontendClass&)> InFunction) override`
- L468 _public function_ `virtual void IterateDependencies(TFunctionRef<void(const FMetasoundFrontendClass&)> InFunction) const override`
- L469 _public function_ `virtual const TArray<FMetasoundFrontendGraphClass>& GetSubgraphs() const override`
- L470 _public function_ `virtual const FMetasoundFrontendGraphClass& GetRootGraphClass() const override`
- L471 _public function_ `virtual void SetRootGraphClass(FMetasoundFrontendGraphClass&& InClass) override`
- L473 _public function_ `virtual FConstClassAccessPtr FindDependencyWithID(FGuid InClassID) const override`
- L474 _public function_ `virtual FConstGraphClassAccessPtr FindSubgraphWithID(FGuid InClassID) const override`
- L475 _public function_ `virtual FConstClassAccessPtr FindClassWithID(FGuid InClassID) const override`
- L477 _public function_ `virtual FConstClassAccessPtr FindClass(const FNodeRegistryKey& InKey) const override`
- L478 _public function_ `virtual FConstClassAccessPtr FindOrAddClass(const FNodeRegistryKey& InKey, bool bInRefreshFromRegistry) override`
- L479 _public function_ `virtual FConstClassAccessPtr FindClass(const FMetasoundFrontendClassMetadata& InMetadata) const override`
- L480 _public function_ `virtual FConstClassAccessPtr FindOrAddClass(const FMetasoundFrontendClassMetadata& InMetadata) override`
- L481 _public function_ `virtual FGraphHandle AddDuplicateSubgraph(const IGraphController& InGraph) override`
- L483 _public function_ `virtual const TSet<FMetasoundFrontendVersion>& GetInterfaceVersions() const override`
- L484 _public function_ `virtual void AddInterfaceVersion(const FMetasoundFrontendVersion& InVersion) override`
- L485 _public function_ `virtual void RemoveInterfaceVersion(const FMetasoundFrontendVersion& InVersion) override`
- L486 _public function_ `virtual void ClearInterfaceVersions() override`
- L488 _public function_ `virtual void SetMetadata(const FMetasoundFrontendDocumentMetadata& InMetadata) override`
- L489 _public function_ `virtual const FMetasoundFrontendDocumentMetadata& GetMetadata() const override`
- L490 _public function_ `virtual FMetasoundFrontendDocumentMetadata* GetMetadata() override`
- L492 _public function_ `virtual void RemoveUnreferencedDependencies() override`
- L493 _public function_ `virtual TArray<FConstClassAccessPtr> SynchronizeDependencyMetadata() override`
- L495 _public function_ `virtual TArray<FGraphHandle> GetSubgraphHandles() override`
- L497 _public function_ `virtual TArray<FConstGraphHandle> GetSubgraphHandles() const override`
- L499 _public function_ `virtual FGraphHandle GetSubgraphWithClassID(FGuid InClassID) override`
- L501 _public function_ `virtual FConstGraphHandle GetSubgraphWithClassID(FGuid InClassID) const override`
- L503 _public prototype_ `virtual TSharedRef<IGraphController> GetRootGraph() override;`
- L504 _public prototype_ `virtual TSharedRef<const IGraphController> GetRootGraph() const override;`
- L505 _public prototype_ `virtual FDocumentAccessPtr GetDocumentPtr() override;`
- L506 _public prototype_ `virtual const FDocumentAccessPtr GetDocumentPtr() const override;`
- L508 _public function_ `virtual bool ExportToJSONAsset(const FString& InAbsolutePath) const override`
- L509 _public function_ `virtual FString ExportToJSON() const override`
- L513 _protected function_ `virtual FDocumentAccess ShareAccess() override`
- L514 _protected function_ `virtual FConstDocumentAccess ShareAccess() const override`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L20 _namespace_ `namespace Metasound`
- L22 _namespace_ `namespace Frontend` (scope `Metasound`)
- L24 _namespace_ `namespace Invalid` (scope `Metasound::Frontend`)
- L26 _prototype_ `const FText& GetInvalidText();` (scope `Metasound::Frontend::Invalid`)
- L27 _prototype_ `const FName& GetInvalidName();` (scope `Metasound::Frontend::Invalid`)
- L28 _prototype_ `const FString& GetInvalidString();` (scope `Metasound::Frontend::Invalid`)
- L31 _prototype_ `const FMetasoundFrontendVertexMetadata& GetInvalidVertexMetadata();` (scope `Metasound::Frontend::Invalid`)
- L32 _prototype_ `const FMetasoundFrontendInterfaceStyle& GetInvalidInterfaceStyle();` (scope `Metasound::Frontend::Invalid`)
- L33 _prototype_ `const FMetasoundFrontendClassStyle& GetInvalidClassStyle();` (scope `Metasound::Frontend::Invalid`)
- L34 _prototype_ `const FMetasoundFrontendGraphStyle& GetInvalidGraphStyle();` (scope `Metasound::Frontend::Invalid`)
- L37 _prototype_ `const FMetasoundFrontendLiteral& GetInvalidLiteral();` (scope `Metasound::Frontend::Invalid`)
- L38 _prototype_ `const FMetasoundFrontendClassInterface& GetInvalidClassInterface();` (scope `Metasound::Frontend::Invalid`)
- L39 _prototype_ `const FMetasoundFrontendNodeInterface& GetInvalidNodeInterface();` (scope `Metasound::Frontend::Invalid`)
- L40 _prototype_ `const FMetasoundFrontendClassMetadata& GetInvalidClassMetadata();` (scope `Metasound::Frontend::Invalid`)
- L43 _prototype_ `const FMetasoundFrontendGraphClassPresetOptions& GetInvalidGraphClassPresetOptions();` (scope `Metasound::Frontend::Invalid`) — `UE_DEPRECATED(5.8, "Preset options are now serialized in the Preset MetaSound Template")`
- L45 _prototype_ `const FMetasoundFrontendGraphClass& GetInvalidGraphClass();` (scope `Metasound::Frontend::Invalid`)
- L46 _prototype_ `const TArray<FMetasoundFrontendClass>& GetInvalidClassArray();` (scope `Metasound::Frontend::Invalid`)
- L47 _prototype_ `const TArray<FMetasoundFrontendGraphClass>& GetInvalidGraphClassArray();` (scope `Metasound::Frontend::Invalid`)
- L48 _prototype_ `const TSet<FName>& GetInvalidNameSet();` (scope `Metasound::Frontend::Invalid`)
- L49 _prototype_ `const FMetasoundFrontendDocumentMetadata& GetInvalidDocumentMetadata();` (scope `Metasound::Frontend::Invalid`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundFrontendNodeClassRegistryPrivate.h` (Private)


#### class `Metasound::Frontend::INodeTemplateRegistryEntry`  
`class INodeTemplateRegistryEntry`  
_L33-43_
- desc: INodeClassRegistryTemplateEntry declares the interface for a node registry entry. Each node class in the registry must satisfy this interface.
- L36 _public prototype_ `virtual ~INodeTemplateRegistryEntry() = default;`
- L39 _public prototype_ `virtual const FNodeClassInfo& GetClassInfo() const;` — `UE_DEPRECATED(5.8, "Use GetFrontendClass() instead")`
- L42 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendClass() const = 0;` — Return a FMetasoundFrontendClass which describes the node.

#### class `Metasound::Frontend::FNodeClassRegistry`  
`class FNodeClassRegistry : public INodeClassRegistry`  
_L46-232_
- inherits: `INodeClassRegistry`
- desc: Registry container private implementation.
- L49 _private prototype_ `FNodeClassRegistry();`
- L52 _public prototype_ `FNodeClassRegistry(const FNodeClassRegistry&) = delete;`
- L53 _public prototype_ `FNodeClassRegistry& operator=(const FNodeClassRegistry&) = delete;`
- L55 _public prototype_ `static FNodeClassRegistry& Get();`
- L56 _public prototype_ `static void Shutdown();`
- L58 _public prototype_ `virtual ~FNodeClassRegistry() = default;`
- L61 _public prototype_ `virtual bool EnqueueInitCommand(TUniqueFunction<void()>&& InFunc) override;` — Add a function to the init command array.
- L63 _public prototype_ `virtual void SetObjectReferencer(TUniquePtr<IObjectReferencer> InReferencer) override;`
- L66 _public prototype_ `virtual void RegisterPendingNodes() override;` — This is called on module startup. This invokes any registration commands enqueued by our registration macros.
- L69 _public prototype_ `virtual void WaitForAsyncGraphRegistration(const FGraphRegistryKey& InRegistryKey) const override;` — Wait for async graph registration to complete for a specific graph
- L74 _public prototype_ `virtual TSharedPtr<const FGraph> GetGraph(const FGraphRegistryKey& InRegistryKey) const override;` — Retrieve a registered graph. If the graph is registered asynchronously, this will wait until the registration task has completed.
- L82 _public prototype_ `virtual FNodeClassRegistryKey RegisterNode(TUniquePtr<Metasound::Frontend::INodeClassRegistryEntry>&& InEntry) override;` — Register external node with the frontend. @param InEntry - Entry to register. @return True on success.
- L83 _public prototype_ `virtual bool UnregisterNode(const FNodeClassRegistryKey& InKey) override;`
- L86 _public prototype_ `virtual bool RegisterNodeMigration(const FNodeMigrationInfo& InMigrationInfo) override;`
- L87 _public prototype_ `virtual bool UnregisterNodeMigration(const FNodeMigrationInfo& InMigrationInfo) override;`
- L88 _public prototype_ `virtual FName GetOwningPluginName(const FNodeClassRegistryKey& InKey) const override;`
- L89 _public prototype_ `virtual FName GetOwningModuleName(const FNodeClassRegistryKey& InKey) const override;`
- L91 _public prototype_ `virtual void RegisterCustomNodeUpdateTransform(const FMetasoundFrontendClassName& ClassName, int32 MajorVersion, const TSharedRef<const FBaseNodeUpdateTransform>& InTransform) override;`
- L93 _public prototype_ `virtual bool UnregisterCustomNodeUpdateTransform(const FMetasoundFrontendClassName& ClassName, int32 MajorVersion) override;`
- L95 _public prototype_ `virtual const TSharedPtr<const FBaseNodeUpdateTransform> FindCustomNodeUpdateTransform(const FMetasoundFrontendClassName& ClassName, int32 MajorVersion) const override;`
- L98 _public prototype_ `virtual bool IsNodeRegistered(const FNodeClassRegistryKey& InKey) const override;`
- L99 _public prototype_ `virtual bool IsGraphRegistered(const FGraphRegistryKey& InKey) const override;`
- L101 _public prototype_ `virtual bool RegisterConversionNode(const FConverterNodeClassRegistryKey& InConversionKey, const FConverterNodeInfo& InNodeInfo) override;`
- L102 _public prototype_ `virtual bool UnregisterConversionNode(const FConverterNodeClassRegistryKey& InConversionKey, const FNodeClassRegistryKey& InNodeKey) override;`
- L105 _public prototype_ `virtual void IterateRegistry(FIterateMetasoundFrontendClassFunction InIterFunc, EMetasoundFrontendClassType InClassType = EMetasoundFrontendClassType::Invalid) const override;` — `UE_DEPRECATED(5.8, "Use Metasound::Frontend::ISearchEngine instead.")`
- L108 _public prototype_ `virtual bool FindDefaultVertexInterface(const FNodeClassRegistryKey& InKey, FVertexInterface& OutVertexInterface) const override;` — Find Frontend class data.
- L109 _public prototype_ `virtual bool FindClassInterface(const FNodeClassRegistryKey& InKey, FClassInterface& OutClassInterface) const override;`
- L111 _public prototype_ `virtual bool FindFrontendClassFromRegistered(const FNodeClassRegistryKey& InKey, FMetasoundFrontendClass& OutClass) const override;`
- L113 _public prototype_ `virtual bool IsCompatibleNodeConfiguration(const FNodeClassRegistryKey& InKey, TConstStructView<FMetaSoundFrontendNodeConfiguration> InNodeConfiguration) const override;`
- L114 _public prototype_ `virtual TInstancedStruct<FMetaSoundFrontendNodeConfiguration> CreateFrontendNodeConfiguration(const FNodeClassRegistryKey& InKey) const override;`
- L116 _public prototype_ `virtual bool FindImplementedInterfacesFromRegistered(const Metasound::Frontend::FNodeClassRegistryKey& InKey, TSet<FMetasoundFrontendVersion>& OutInterfaceVersions) const override;`
- L118 _public prototype_ `virtual bool FindInputNodeRegistryKeyForDataType(const FName& InDataTypeName, const EMetasoundFrontendVertexAccessType InAccessType, FNodeClassRegistryKey& OutKey) override;`
- L119 _public prototype_ `virtual bool FindVariableNodeRegistryKeyForDataType(const FName& InDataTypeName, FNodeClassRegistryKey& OutKey) override;`
- L120 _public prototype_ `virtual bool FindOutputNodeRegistryKeyForDataType(const FName& InDataTypeName, const EMetasoundFrontendVertexAccessType InAccessType, FNodeClassRegistryKey& OutKey) override;`
- L123 _public prototype_ `virtual TUniquePtr<Metasound::INode> CreateNode(const FNodeClassRegistryKey& InKey, Metasound::FNodeData InNodeData) const override;` — Create a new instance of a C++ implemented node from the registry.
- L127 _public prototype_ `virtual TArray<FConverterNodeInfo> GetPossibleConverterNodes(const FName& FromDataType, const FName& ToDataType) override;` — Returns a list of possible nodes to use to convert from FromDataType to ToDataType. Returns an empty array if none are available.
- L133 _public prototype_ `void NotifyPluginUnmounted(IPlugin& Plugin);` — Cancels async graphs contained in the given directory and waits for all associated unregistration tasks associated with the given plugin to complete such that subsequent call to GC all remaining plugin-specific content is not being blocked by in-flight registration tasks.
- L136 _public prototype_ `FGraphRegistryKey RegisterGraph(const TScriptInterface<IMetaSoundDocumentInterface>& InDocumentInterface, TArrayView<const FGuid> InPageOrder);` — Register a graph from an IMetaSoundDocumentInterface
- L139 _public prototype_ `bool UnregisterGraph(const FGraphRegistryKey& InRegistryKey, const TScriptInterface<IMetaSoundDocumentInterface>& InDocumentInterface);` — Unregister a graph
- L142 _public prototype_ `FNodeClassRegistryKey RegisterNodeTemplate(TUniquePtr<Metasound::Frontend::INodeTemplateRegistryEntry>&& InEntry);` — Private implementation until hardened and used for template nodes other than reroutes.
- L143 _public prototype_ `bool UnregisterNodeTemplate(const FNodeClassRegistryKey& InKey);`
- L146 _public prototype_ `TUniquePtr<FNodeClassRegistryTransactionStream> CreateTransactionStream();` — Create a transaction stream for any newly transactions
- L160 _private prototype_ `void BuildAndRegisterGraphFromDocument(const FMetasoundFrontendDocument& InDocument, const FProxyDataCache& InProxyDataCache, const FGraphRegistryKey& InGraphRegistryKey, TArrayView<const FGuid> InPageOrder);`
- L162 _private prototype_ `void AddRegistrationTask(const FGraphRegistryKey& InKey, FActiveRegistrationTaskInfo&& TaskInfo);`
- L163 _private prototype_ `void RemoveRegistrationTask(const FGraphRegistryKey& InKey, int32 InRegistrationTaskID, FNodeClassRegistryTransaction::ETransactionType TransactionType);`
- L167 _private prototype_ `void AddDocumentReference(TScriptInterface<IMetaSoundDocumentInterface> DocumentInterface);` — Adds reference to document's owning UObject to internal ObjectReferencer, indicating async registration/unregistration task(s) are depending on it.
- L171 _private prototype_ `void RemoveDocumentReference(TScriptInterface<IMetaSoundDocumentInterface> DocumentInterface);` — Removes reference to document's owning UObject from internal ObjectReferencer, indicating async registration/unregistration task(s) are no longer depending on it.
- L173 _private prototype_ `bool UnregisterNodeInternal(const FNodeClassRegistryKey& InKey);`
- L174 _private prototype_ `FNodeClassRegistryKey RegisterNodeInternal(TUniquePtr<INodeClassRegistryEntry>&& InEntry);`
- L176 _private member_ `static FNodeClassRegistry* LazySingleton;`
- L178 _private prototype_ `void WaitForAsyncRegistrationInternal(const FNodeClassRegistryKey& InRegistryKey, const FTopLevelAssetPath* InAssetPath) const;`
- L180 _private prototype_ `void RegisterGraphInternal(const FGraphRegistryKey& InKey, TSharedPtr<const FGraph> InGraph);`
- L181 _private prototype_ `bool UnregisterGraphInternal(const FGraphRegistryKey& InKey);`
- L188 _private prototype_ `bool AccessNodeEntryThreadSafe(const FNodeClassRegistryKey& InKey, TFunctionRef<void(const INodeClassRegistryEntry&)> InFunc) const;` — Access a node entry safely. Node entries can be added/removed asynchronously. Functions passed to this method will be executed in a manner where access to the node registry entry is safe from threading issues. @returns true if a node registry entry was found and the function executed. False if the entry was not found and the function not executed.
- L190 _private prototype_ `const INodeTemplateRegistryEntry* FindNodeTemplateEntry(const FNodeClassRegistryKey& InKey) const;`
- L192 _private prototype_ `bool IsCustomNodeUpdateTransformWellFormed(const FMetasoundFrontendClassName& ClassName, int32 MajorVersion, const TSharedRef<const FBaseNodeUpdateTransform>& InTransform);`
- L198 _private member_ `static constexpr int32 MaxNumNodesAndDatatypesToInitialize = 2048;` — This buffer is used to enqueue nodes and datatypes to register when the module has been initialized, in order to avoid bad behavior with ensures, logs, etc. on static initialization. The bad news is that TInlineAllocator is the safest allocator to use on static init. The good news is that none of these lambdas typically have captures, so this should have low memory overhead.
- L199 _private member_ `TArray<TUniqueFunction<void()>, TInlineAllocator<MaxNumNodesAndDatatypesToInitialize>> LazyInitCommands;`
- L201 _private member_ `FCriticalSection LazyInitCommandCritSection;`
- L204 _private member_ `TMultiMap<FNodeClassRegistryKey, TSharedRef<INodeClassRegistryEntry, ESPMode::ThreadSafe>> RegisteredNodes;` — Registry in which we keep all information about nodes implemented in C++.
- L207 _private member_ `TMultiMap<FNodeClassRegistryKey, FNodeMigrationInfo> NodeMigrations;`
- L209 _private typedef_ `using FMajorNodeUpdateTransformKey = TPair<const FMetasoundFrontendClassName, int32 >;` — Custom node update transforms
- L210 _private member_ `TMap<FMajorNodeUpdateTransformKey, TSharedRef<const FBaseNodeUpdateTransform>> CustomNodeUpdateTransforms;`
- L214 _private member_ `TMap<FNodeClassRegistryKey, TSharedRef<INodeTemplateRegistryEntry, ESPMode::ThreadSafe>> RegisteredNodeTemplates;` — Registry in which we keep all information about dynamically-generated templated nodes via in C++.
- L217 _private member_ `TMap<FGraphRegistryKey, TSharedPtr<const FGraph>> RegisteredGraphs;` — Map of all registered graphs
- L220 _private member_ `TMap<FConverterNodeClassRegistryKey, FConverterNodeClassRegistryValue> ConverterNodeClassRegistry;` — Registry in which we keep lists of possible nodes to use to convert between two datatypes
- L222 _private member_ `TSharedRef<FNodeClassRegistryTransactionBuffer> TransactionBuffer;`
- L224 _private member_ `mutable FTransactionallySafeCriticalSection RegistryMapsCriticalSection;`
- L225 _private member_ `mutable FTransactionallySafeCriticalSection ActiveRegistrationTasksCriticalSection;`
- L226 _private member_ `mutable FTransactionallySafeCriticalSection ObjectReferencerCriticalSection;`
- L228 _private member_ `UE::Tasks::FPipe AsyncRegistrationPipe;`
- L229 _private member_ `int32 RegistrationTaskCntr = 0;`
- L230 _private member_ `TMap<FNodeClassRegistryKey, TArray<FActiveRegistrationTaskInfo>> ActiveRegistrationTasks;`
- L231 _private member_ `TUniquePtr<INodeClassRegistry::IObjectReferencer> ObjectReferencer;`

#### struct `Metasound::Frontend::FNodeClassRegistry::FActiveRegistrationTaskInfo`  
`struct FActiveRegistrationTaskInfo`  
_L149-158_
- L151 _public member_ `FNodeClassRegistryTransaction::ETransactionType TransactionType = FNodeClassRegistryTransaction::ETransactionType::NodeRegistration;`
- L152 _public member_ `UE::Tasks::FTask Task;`
- L153 _public member_ `FTopLevelAssetPath AssetPath;`
- L154 _public member_ `int32 RegistrationTaskID = 0;`
- L155 _public member_ `const TScriptInterface<IMetaSoundDocumentInterface> RegistryDocInterface;`
- L157 _public member_ `TSharedPtr<UE::Tasks::FCancellationToken> CancellationToken;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Metasound`
- L23 _namespace_ `namespace Metasound`
- L23 _namespace_ `namespace Frontend` (scope `Metasound`)
- L27 _typedef_ `using FNodeClassRegistryTransactionBuffer = TTransactionBuffer<FNodeClassRegistryTransaction>;` (scope `Metasound::Frontend`)
- L28 _typedef_ `using FNodeClassRegistryTransactionStream = TTransactionStream<FNodeClassRegistryTransaction>;` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundFrontendNodeController.h` (Private)


#### class `Metasound::Frontend::FBaseNodeController`  
`class FBaseNodeController : public INodeController`  
_L18-259_
- inherits: `INodeController`
- desc: FBaseNodeController provides common functionality for multiple derived node controllers.
- L30 _public prototype_ `FBaseNodeController(const FInitParams& InParams);` — Construct a base node controller.
- L32 _public prototype_ `virtual bool IsValid() const override;`
- L35 _public prototype_ `virtual FGuid GetOwningGraphClassID() const override;` — Owning graph info
- L36 _public prototype_ `virtual FGraphHandle GetOwningGraph() override;`
- L37 _public prototype_ `virtual FConstGraphHandle GetOwningGraph() const override;`
- L40 _public prototype_ `virtual FGuid GetID() const override;` — Info about this node.
- L41 _public prototype_ `virtual FGuid GetClassID() const override;`
- L43 _public prototype_ `virtual bool ClearInputLiteral(FGuid InVertexID) override;`
- L44 _public prototype_ `virtual const FMetasoundFrontendLiteral* GetInputLiteral(const FGuid& InVertexID) const override;`
- L45 _public prototype_ `virtual void SetInputLiteral(const FMetasoundFrontendVertexLiteral& InVertexLiteral) override;`
- L47 _public prototype_ `virtual const FMetasoundFrontendClassInterface& GetClassInterface() const override;`
- L48 _public prototype_ `virtual const FMetasoundFrontendClassMetadata& GetClassMetadata() const override;`
- L50 _public prototype_ `virtual const FMetasoundFrontendNodeInterface& GetNodeInterface() const override;`
- L53 _public prototype_ `virtual const FMetasoundFrontendInterfaceStyle& GetInputStyle() const override;`
- L54 _public prototype_ `virtual const FMetasoundFrontendInterfaceStyle& GetOutputStyle() const override;`
- L55 _public prototype_ `virtual const FMetasoundFrontendClassStyle& GetClassStyle() const override;`
- L59 _public prototype_ `virtual const FMetasoundFrontendNodeStyle& GetNodeStyle() const override;`
- L60 _public prototype_ `virtual void SetNodeStyle(const FMetasoundFrontendNodeStyle& InStyle) override;`
- L63 _public prototype_ `virtual void SetNodeConfiguration(TInstancedStruct<FMetaSoundFrontendNodeConfiguration> InConfig) override;`
- L64 _public prototype_ `virtual TConstStructView<FMetaSoundFrontendNodeConfiguration> GetNodeConfiguration() const override;`
- L68 _public prototype_ `virtual bool DiffAgainstRegistryInterface(FClassInterfaceUpdates& OutInterfaceUpdates, bool bInUseHighestMinorVersion, bool bInForceRegenerateClassInterfaceOverride) const override;` — `UE_DEPRECATED(5.6, "Moved to FMetaSoundFrontendDocumentBuilder")`
- L71 _public prototype_ `virtual bool CanAutoUpdate(FClassInterfaceUpdates& OutInterfaceUpdates) const override;` — `UE_DEPRECATED(5.7, "Moved to FMetaSoundFrontendDocumentBuilder")`
- L74 _public prototype_ `virtual FNodeHandle ReplaceWithVersion(const FMetasoundFrontendVersionNumber& InNewVersion, TArray<FVertexNameAndType>* OutDisconnectedInputs, TArray<FVertexNameAndType>* OutDisconnectedOutputs) override;`
- L76 _public prototype_ `virtual const FVertexName& GetNodeName() const override;`
- L79 _public function_ `virtual void SetNodeName(const FVertexName& InName) override` — This only exists to allow for transform fix-ups to easily cleanup input/output node names.
- L83 _public prototype_ `virtual const FText& GetDescription() const override;` — Description of the given node.
- L87 _public prototype_ `virtual FText GetDisplayName() const override;` — Returns the readable display name of the given node (Used only within MetaSound Editor context, and not guaranteed to be a unique identifier).
- L90 _public function_ `virtual void SetDescription(const FText& InDescription) override` — Sets the description of the node.
- L93 _public function_ `virtual void SetDisplayName(const FText& InDisplayName) override` — Sets the display name of the node.
- L96 _public prototype_ `virtual const FText& GetDisplayTitle() const override;` — Returns the title of the given node (what to label in visual node).
- L99 _public prototype_ `virtual bool CanAddInput(const FVertexName& InVertexName) const override;`
- L100 _public prototype_ `virtual FInputHandle AddInput(const FVertexName& InVertexName, const FMetasoundFrontendLiteral* InDefault) override;`
- L101 _public prototype_ `virtual bool RemoveInput(FGuid InVertexID) override;`
- L103 _public prototype_ `virtual bool CanAddOutput(const FVertexName& InVertexName) const override;`
- L104 _public prototype_ `virtual FInputHandle AddOutput(const FVertexName& InVertexName, const FMetasoundFrontendLiteral* InDefault) override;`
- L105 _public prototype_ `virtual bool RemoveOutput(FGuid InVertexID) override;`
- L108 _public prototype_ `virtual TArray<FInputHandle> GetInputs() override;` — Returns all node inputs.
- L111 _public prototype_ `virtual TArray<FConstInputHandle> GetConstInputs() const override;` — Returns all node inputs.
- L113 _public prototype_ `virtual void IterateConstInputs(TUniqueFunction<void(FConstInputHandle)> InFunction) const override;`
- L114 _public prototype_ `virtual void IterateConstOutputs(TUniqueFunction<void(FConstOutputHandle)> InFunction) const override;`
- L116 _public prototype_ `virtual void IterateInputs(TUniqueFunction<void(FInputHandle)> InFunction) override;`
- L117 _public prototype_ `virtual void IterateOutputs(TUniqueFunction<void(FOutputHandle)> InFunction) override;`
- L119 _public prototype_ `virtual int32 GetNumInputs() const override;`
- L120 _public prototype_ `virtual int32 GetNumOutputs() const override;`
- L122 _public prototype_ `virtual FInputHandle GetInputWithVertexName(const FVertexName& InName) override;`
- L123 _public prototype_ `virtual FConstInputHandle GetConstInputWithVertexName(const FVertexName& InName) const override;`
- L126 _public prototype_ `virtual TArray<FOutputHandle> GetOutputs() override;` — Returns all node outputs.
- L129 _public prototype_ `virtual TArray<FConstOutputHandle> GetConstOutputs() const override;` — Returns all node outputs.
- L131 _public prototype_ `virtual FOutputHandle GetOutputWithVertexName(const FVertexName& InName) override;`
- L132 _public prototype_ `virtual FConstOutputHandle GetConstOutputWithVertexName(const FVertexName& InName) const override;`
- L134 _public prototype_ `virtual bool IsInterfaceMember() const override;`
- L135 _public prototype_ `virtual const FMetasoundFrontendVersion& GetInterfaceVersion() const override;`
- L141 _public prototype_ `virtual FInputHandle GetInputWithID(FGuid InVertexID) override;` — Returns an input with the given id. If the input does not exist, an invalid handle is returned.
- L147 _public prototype_ `virtual FConstInputHandle GetInputWithID(FGuid InVertexID) const override;` — Returns an input with the given name. If the input does not exist, an invalid handle is returned.
- L153 _public prototype_ `virtual FOutputHandle GetOutputWithID(FGuid InVertexID) override;` — Returns an output with the given name. If the output does not exist, an invalid handle is returned.
- L159 _public prototype_ `virtual FConstOutputHandle GetOutputWithID(FGuid InVertexID) const override;` — Returns an output with the given name. If the output does not exist, an invalid handle is returned.
- L161 _public prototype_ `virtual FGraphHandle AsGraph() override;`
- L162 _public prototype_ `virtual FConstGraphHandle AsGraph() const override;`
- L166 _protected prototype_ `const FMetasoundFrontendClassInterface* GetClassInterfaceForNode() const;`
- L168 _protected prototype_ `virtual FDocumentAccess ShareAccess() override;`
- L169 _protected prototype_ `virtual FConstDocumentAccess ShareAccess() const override;`
- L172 _protected member_ `FNodeAccessPtr NodePtr;`
- L173 _protected member_ `FConstClassAccessPtr ClassPtr;`
- L174 _protected member_ `FGraphHandle OwningGraph;`
- L190 _protected prototype_ `virtual TArray<FInputControllerParams> GetInputControllerParams() const;`
- L191 _protected prototype_ `virtual TArray<FOutputControllerParams> GetOutputControllerParams() const;`
- L193 _protected prototype_ `virtual bool FindInputControllerParamsWithVertexName(const FVertexName& InName, FInputControllerParams& OutParams) const;`
- L194 _protected prototype_ `virtual bool FindOutputControllerParamsWithVertexName(const FVertexName& InName, FOutputControllerParams& OutParams) const;`
- L196 _protected prototype_ `virtual bool FindInputControllerParamsWithID(FGuid InVertexID, FInputControllerParams& OutParams) const;`
- L197 _protected prototype_ `virtual bool FindOutputControllerParamsWithID(FGuid InVertexID, FOutputControllerParams& OutParams) const;`
- L199 _protected prototype_ `virtual FInputHandle CreateInputController(FGuid InVertexID, FConstVertexAccessPtr InNodeVertexPtr, FConstClassInputAccessPtr InClassInputPtr, FNodeHandle InOwningNode) const = 0;`
- L200 _protected prototype_ `virtual FOutputHandle CreateOutputController(FGuid InVertexID, FConstVertexAccessPtr InNodeVertexPtr, FConstClassOutputAccessPtr InClassOutputPtr, FNodeHandle InOwningNode) const = 0;`
- L203 _private prototype_ `void SetClassInterfaceOverride(TInstancedStruct<FMetasoundFrontendClassInterface> InClassInterfaceOverride);`
- L204 _private prototype_ `TConstStructView<FMetasoundFrontendClassInterface> GetClassInterfaceOverride() const;`
- L216 _private prototype_ `bool FindRegisteredClass(const FMetasoundFrontendClassMetadata& InMetadata, bool bInUseHighestMinorVersion, FMetasoundFrontendClass& OutInterface) const;`
- L218 _private prototype_ `bool ShouldReplaceExistingNodeConfig(TConstStructView<FMetaSoundFrontendNodeConfiguration> InRegisteredNodeConfig, TConstStructView<FMetaSoundFrontendNodeConfiguration> InExistingConfig) const;`
- L219 _private prototype_ `const FMetasoundFrontendClassInterface& GetApplicableRegistryInterface(const FMetasoundFrontendClass& InRegisteredClass, const FNodeConfigurationUpdateData& InNodeConfigUpdates) const;`
- L220 _private prototype_ `void FindNodeConfigurationUpdates(const FMetasoundFrontendClass& InRegisteredClass, FNodeConfigurationUpdateData& OutNodeConfigUpdates, bool bInForceRegenerateClassInterfaceOverride) const;`
- L223 _private prototype_ `void DiffClassInterfaces(const FMetasoundFrontendClassInterface& InOriginalInterface, const FMetasoundFrontendClassInterface& InNewInterface, FClassInterfaceUpdates& OutClassInterfaceUpdates) const;`
- L256 _private prototype_ `FNodeInstanceReplacementData CaptureNodeInstanceReplacementData();`
- L257 _private prototype_ `void ApplyNodeInstanceReplacementData(const FMetasoundFrontendClass& InReplacementClass, INodeController& InReplacementNode, FNodeInstanceReplacementData&& InInstanceData, TArray<FVertexNameAndType>* OutDisconnectedInputs, TArray<FVertexNameAndType>* OutDisconnectedOutputs);`

#### struct `Metasound::Frontend::FBaseNodeController::FInitParams`  
`struct FInitParams`  
_L22-27_
- L24 _public member_ `FNodeAccessPtr NodePtr;`
- L25 _public member_ `FConstClassAccessPtr ClassPtr;`
- L26 _public member_ `FGraphHandle OwningGraph;`

#### struct `Metasound::Frontend::FBaseNodeController::FInputControllerParams`  
`struct FInputControllerParams`  
_L176-181_
- L178 _public member_ `FGuid VertexID;`
- L179 _public member_ `FConstVertexAccessPtr NodeVertexPtr;`
- L180 _public member_ `FConstClassInputAccessPtr ClassInputPtr;`

#### struct `Metasound::Frontend::FBaseNodeController::FOutputControllerParams`  
`struct FOutputControllerParams`  
_L183-188_
- L185 _public member_ `FGuid VertexID;`
- L186 _public member_ `FConstVertexAccessPtr NodeVertexPtr;`
- L187 _public member_ `FConstClassOutputAccessPtr ClassOutputPtr;`

#### struct `Metasound::Frontend::FBaseNodeController::FNodeConfigurationUpdateData`  
`struct FNodeConfigurationUpdateData`  
_L206-213_
- L208 _public member_ `TConstStructView<FMetaSoundFrontendNodeConfiguration> ExistingConfig;`
- L209 _public member_ `TConstStructView<FMetasoundFrontendClassInterface> ExistingClassInterfaceOverride;`
- L210 _public member_ `TInstancedStruct<FMetaSoundFrontendNodeConfiguration> RegisteredConfig;`
- L211 _public member_ `TInstancedStruct<FMetasoundFrontendClassInterface> RegeneratedClassInterfaceOverride;`
- L212 _public member_ `bool bDidUpdateClassInterfaceOverride = false;`

#### struct `Metasound::Frontend::FBaseNodeController::FInputConnectionInfo`  
`struct FInputConnectionInfo`  
_L226-233_
- L228 _public member_ `FOutputHandle ConnectedOutput;`
- L229 _public member_ `FVertexName Name;`
- L230 _public member_ `FName DataType;`
- L231 _public member_ `FMetasoundFrontendLiteral DefaultValue;`
- L232 _public member_ `bool bLiteralSet = false;`

#### struct `Metasound::Frontend::FBaseNodeController::FOutputConnectionInfo`  
`struct FOutputConnectionInfo`  
_L235-240_
- L237 _public member_ `TArray<FInputHandle> ConnectedInputs;`
- L238 _public member_ `FVertexName VertexName;`
- L239 _public member_ `FName DataType;`

#### struct `Metasound::Frontend::FBaseNodeController::FNodeInstanceReplacementData`  
`struct FNodeInstanceReplacementData`  
_L242-254_
- L246 _public member_ `FMetasoundFrontendNodeStyle Style;`
- L249 _public member_ `TInstancedStruct<FMetaSoundFrontendNodeConfiguration> Configuration;`
- L250 _public member_ `TInstancedStruct<FMetasoundFrontendClassInterface> ClassInterfaceOverride;`
- L251 _public member_ `TMap<FVertexNameAndType, FInputConnectionInfo> InputConnections;`
- L252 _public member_ `TMap<FVertexNameAndType, FOutputConnectionInfo> OutputConnections;`
- L253 _public member_ `FGuid NodeID;`

#### class `Metasound::Frontend::FNodeController`  
`class FNodeController : public FBaseNodeController`  
_L262-311_
- inherits: `FBaseNodeController`
- desc: Represents an external node (defined in either code or by an asset's root graph).
- L283 _public prototype_ `FNodeController(EPrivateToken InToken, const FInitParams& InParams);` — Constructor takes a private token so it can only be instantiated by using the static creation functions. This protects against some error conditions which would result in a zombie object. The creation methods can detect the error conditions and return an invalid controller on error
- L289 _public prototype_ `static FNodeHandle CreateNodeHandle(const FInitParams& InParams);` — Create a node handle for an external node. @return A Node handle. On error, an invalid node handle is returned.
- L295 _public prototype_ `static FConstNodeHandle CreateConstNodeHandle(const FInitParams& InParams);` — Create a node handle for an external node. @return A Node handle. On error, an invalid node handle is returned.
- L297 _public prototype_ `virtual ~FNodeController() = default;`
- L299 _public prototype_ `virtual bool IsValid() const override;`
- L302 _protected prototype_ `virtual FDocumentAccess ShareAccess() override;`
- L303 _protected prototype_ `virtual FConstDocumentAccess ShareAccess() const override;`
- L305 _protected prototype_ `virtual FInputHandle CreateInputController(FGuid InVertexID, FConstVertexAccessPtr InNodeVertexPtr, FConstClassInputAccessPtr InClassInputPtr, FNodeHandle InOwningNode) const override;`
- L306 _protected prototype_ `virtual FOutputHandle CreateOutputController(FGuid InVertexID, FConstVertexAccessPtr InNodeVertexPtr, FConstClassOutputAccessPtr InClassOutputPtr, FNodeHandle InOwningNode) const override;`
- L310 _private member_ `FGraphAccessPtr GraphPtr;`

#### enum `Metasound::Frontend::FNodeController::EPrivateToken`  
`enum EPrivateToken`  
_L267-267_
- desc: Private token only allows members, friends or derived classes to call constructor.
- L267 _public enumerator_ `enum EPrivateToken { Token }; public: struct FInitParams { FNodeAccessPtr NodePtr; FConstClassAccessPtr ClassPtr; FGraphAccessPtr GraphPtr;` — Private token only allows members, friends or derived classes to call constructor.

#### struct `Metasound::Frontend::FNodeController::FInitParams`  
`struct FInitParams`  
_L270-276_
- L272 _public member_ `FNodeAccessPtr NodePtr;`
- L273 _public member_ `FConstClassAccessPtr ClassPtr;`
- L274 _public member_ `FGraphAccessPtr GraphPtr;`
- L275 _public member_ `FGraphHandle OwningGraph;`

#### class `Metasound::Frontend::FOutputNodeController`  
`class FOutputNodeController: public FBaseNodeController`  
_L314-378_
- inherits: `FBaseNodeController`
- desc: FOutputNodeController represents an output node.
- L335 _public prototype_ `FOutputNodeController(EPrivateToken InToken, const FInitParams& InParams);` — Constructor takes a private token so it can only be instantiated by using the static creation functions. This protects against some error conditions which would result in a zombie object. The creation methods can detect the error conditions and return an invalid controller on error
- L341 _public prototype_ `static FNodeHandle CreateOutputNodeHandle(const FInitParams& InParams);` — Create a node handle for an output node. @return A Node handle. On error, an invalid node handle is returned.
- L347 _public prototype_ `static FConstNodeHandle CreateConstOutputNodeHandle(const FInitParams& InParams);` — Create a node handle for an output node. @return A Node handle. On error, an invalid node handle is returned.
- L350 _public prototype_ `virtual ~FOutputNodeController() = default;`
- L352 _public prototype_ `virtual bool IsValid() const override;`
- L355 _public prototype_ `virtual const FText& GetDescription() const override;`
- L356 _public prototype_ `virtual FText GetDisplayName() const override;`
- L357 _public prototype_ `virtual const FText& GetDisplayTitle() const override;`
- L358 _public prototype_ `virtual void SetDescription(const FText& InDescription) override;`
- L359 _public prototype_ `virtual void SetDisplayName(const FText& InText) override;`
- L362 _public prototype_ `virtual void SetNodeName(const FVertexName& InName) override;`
- L363 _public prototype_ `virtual const FMetasoundFrontendVersion& GetInterfaceVersion() const override;`
- L367 _protected prototype_ `virtual FDocumentAccess ShareAccess() override;`
- L368 _protected prototype_ `virtual FConstDocumentAccess ShareAccess() const override;`
- L370 _protected prototype_ `virtual FInputHandle CreateInputController(FGuid InVertexID, FConstVertexAccessPtr InNodeVertexPtr, FConstClassInputAccessPtr InClassInputPtr, FNodeHandle InOwningNode) const override;`
- L372 _protected prototype_ `virtual FOutputHandle CreateOutputController(FGuid InVertexID, FConstVertexAccessPtr InNodeVertexPtr, FConstClassOutputAccessPtr InClassOutputPtr, FNodeHandle InOwningNode) const override;`
- L376 _private member_ `FGraphAccessPtr GraphPtr;`
- L377 _private member_ `FConstClassOutputAccessPtr OwningGraphClassOutputPtr;`

#### enum `Metasound::Frontend::FOutputNodeController::EPrivateToken`  
`enum EPrivateToken`  
_L318-318_
- desc: Private token only allows members or friends to call constructor.
- L318 _public enumerator_ `enum EPrivateToken { Token }; public: struct FInitParams { FNodeAccessPtr NodePtr; FConstClassAccessPtr ClassPtr; FConstClassOutputAccessPtr OwningGraphClassOutputPtr;` — Private token only allows members or friends to call constructor.

#### struct `Metasound::Frontend::FOutputNodeController::FInitParams`  
`struct FInitParams`  
_L321-328_
- L323 _public member_ `FNodeAccessPtr NodePtr;`
- L324 _public member_ `FConstClassAccessPtr ClassPtr;`
- L325 _public member_ `FConstClassOutputAccessPtr OwningGraphClassOutputPtr;`
- L326 _public member_ `FGraphAccessPtr GraphPtr;`
- L327 _public member_ `FGraphHandle OwningGraph;`

#### class `Metasound::Frontend::FInputNodeController`  
`class FInputNodeController: public FBaseNodeController`  
_L381-448_
- inherits: `FBaseNodeController`
- desc: FInputNodeController represents an input node.
- L402 _public prototype_ `FInputNodeController(EPrivateToken InToken, const FInitParams& InParams);` — Constructor takes a private token so it can only be instantiated by using the static creation functions. This protects against some error conditions which would result in a zombie object. The creation methods can detect the error conditions and return an invalid controller on error
- L408 _public prototype_ `static FNodeHandle CreateInputNodeHandle(const FInitParams& InParams);` — Create a node handle for an input node. @return A Node handle. On error, an invalid node handle is returned.
- L414 _public prototype_ `static FConstNodeHandle CreateConstInputNodeHandle(const FInitParams& InParams);` — Create a node handle for an input node. @return A Node handle. On error, an invalid node handle is returned.
- L416 _public prototype_ `virtual ~FInputNodeController() = default;`
- L419 _public prototype_ `virtual const FText& GetDescription() const override;`
- L420 _public prototype_ `virtual FText GetDisplayName() const override;`
- L421 _public prototype_ `virtual const FText& GetDisplayTitle() const override;`
- L422 _public prototype_ `virtual void SetDescription(const FText& InDescription) override;`
- L423 _public prototype_ `virtual void SetDisplayName(const FText& InText) override;`
- L426 _public prototype_ `virtual const FMetasoundFrontendVersion& GetInterfaceVersion() const override;`
- L427 _public prototype_ `virtual bool IsValid() const override;`
- L428 _public prototype_ `virtual void SetNodeName(const FVertexName& InName) override;`
- L431 _public function_ `virtual bool ClearInputLiteral(FGuid InVertexID) override` — No-ops as inputs do not handle literals the same way as other nodes
- L432 _public function_ `virtual const FMetasoundFrontendLiteral* GetInputLiteral(const FGuid& InVertexID) const override`
- L433 _public function_ `virtual void SetInputLiteral(const FMetasoundFrontendVertexLiteral& InVertexLiteral) override`
- L437 _protected prototype_ `virtual FDocumentAccess ShareAccess() override;`
- L438 _protected prototype_ `virtual FConstDocumentAccess ShareAccess() const override;`
- L440 _protected prototype_ `virtual FInputHandle CreateInputController(FGuid InVertexID, FConstVertexAccessPtr InNodeVertexPtr, FConstClassInputAccessPtr InClassInputPtr, FNodeHandle InOwningNode) const override;`
- L442 _protected prototype_ `virtual FOutputHandle CreateOutputController(FGuid InVertexID, FConstVertexAccessPtr InNodeVertexPtr, FConstClassOutputAccessPtr InClassOutputPtr, FNodeHandle InOwningNode) const override;`
- L446 _private member_ `FConstClassInputAccessPtr OwningGraphClassInputPtr;`
- L447 _private member_ `FGraphAccessPtr GraphPtr;`

#### enum `Metasound::Frontend::FInputNodeController::EPrivateToken`  
`enum EPrivateToken`  
_L385-385_
- desc: Private token only allows members or friends to call constructor.
- L385 _public enumerator_ `enum EPrivateToken { Token }; public: struct FInitParams { FNodeAccessPtr NodePtr; FConstClassAccessPtr ClassPtr; FConstClassInputAccessPtr OwningGraphClassInputPtr;` — Private token only allows members or friends to call constructor.

#### struct `Metasound::Frontend::FInputNodeController::FInitParams`  
`struct FInitParams`  
_L388-395_
- L390 _public member_ `FNodeAccessPtr NodePtr;`
- L391 _public member_ `FConstClassAccessPtr ClassPtr;`
- L392 _public member_ `FConstClassInputAccessPtr OwningGraphClassInputPtr;`
- L393 _public member_ `FGraphAccessPtr GraphPtr;`
- L394 _public member_ `FGraphHandle OwningGraph;`

#### class `Metasound::Frontend::FVariableNodeController`  
`class FVariableNodeController : public FNodeController`  
_L451-491_
- inherits: `FNodeController`
- desc: Represents an variable node
- L453 _private typedef_ `using Super = FNodeController;`
- L459 _public typedef_ `using FInitParams = FNodeController::FInitParams;`
- L466 _public prototype_ `FVariableNodeController(EPrivateToken InToken, const FInitParams& InParams);` — Constructor takes a private token so it can only be instantiated by using the static creation functions. This protects against some error conditions which would result in a zombie object. The creation methods can detect the error conditions and return an invalid controller on error
- L472 _public prototype_ `static FNodeHandle CreateNodeHandle(const FInitParams& InParams);` — Create a node handle for a variable node. @return A Node handle. On error, an invalid node handle is returned.
- L478 _public prototype_ `static FConstNodeHandle CreateConstNodeHandle(const FInitParams& InParams);` — Create a node handle for a variable node. @return A Node handle. On error, an invalid node handle is returned.
- L480 _public prototype_ `virtual ~FVariableNodeController() = default;`
- L484 _protected prototype_ `virtual FInputHandle CreateInputController(FGuid InVertexID, FConstVertexAccessPtr InNodeVertexPtr, FConstClassInputAccessPtr InClassInputPtr, FNodeHandle InOwningNode) const override;`
- L485 _protected prototype_ `virtual FOutputHandle CreateOutputController(FGuid InVertexID, FConstVertexAccessPtr InNodeVertexPtr, FConstClassOutputAccessPtr InClassOutputPtr, FNodeHandle InOwningNode) const override;`
- L489 _private prototype_ `static bool IsSupportedClassType(EMetasoundFrontendClassType InClassType);`
- L490 _private prototype_ `static bool IsVariableDataType(const FName& InTypeName);`

#### enum `Metasound::Frontend::FVariableNodeController::EPrivateToken`  
`enum EPrivateToken`  
_L456-456_
- desc: Private token only allows members or friends to call constructor.
- L456 _public enumerator_ `enum EPrivateToken { Token }; public: using FInitParams = FNodeController::FInitParams;` — Private token only allows members or friends to call constructor.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Metasound`
- L13 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundFrontendOutputController.h` (Private)


#### class `Metasound::Frontend::FBaseOutputController`  
`class FBaseOutputController : public IOutputController`  
_L19-88_
- inherits: `IOutputController`
- desc: FBaseOutputController provides common functionality for multiple derived output controllers.
- L21 _private typedef_ `using FRegistry = FMetasoundFrontendRegistryContainer;`
- L37 _public prototype_ `FBaseOutputController(const FInitParams& InParams);` — Construct the output controller base.
- L39 _public prototype_ `virtual ~FBaseOutputController() = default;`
- L41 _public prototype_ `virtual bool IsValid() const override;`
- L43 _public prototype_ `virtual FGuid GetID() const override;`
- L44 _public prototype_ `virtual const FName& GetDataType() const override;`
- L45 _public prototype_ `virtual const FVertexName& GetName() const override;`
- L46 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetVertexAccessType() const override;`
- L49 _public prototype_ `virtual FText GetDisplayName() const override;`
- L50 _public prototype_ `virtual const FText& GetTooltip() const override;`
- L53 _public prototype_ `virtual const FMetasoundFrontendVertexMetadata& GetMetadata() const override;` — Output metadata
- L57 _public prototype_ `virtual FGuid GetOwningNodeID() const override;` — Return info on containing node.
- L58 _public prototype_ `virtual FNodeHandle GetOwningNode() override;`
- L59 _public prototype_ `virtual FConstNodeHandle GetOwningNode() const override;`
- L61 _public function_ `virtual void SetName(const FVertexName& InName) override`
- L63 _public prototype_ `virtual bool IsConnected() const override;`
- L64 _public prototype_ `virtual TArray<FInputHandle> GetConnectedInputs() override;`
- L65 _public prototype_ `virtual TArray<FConstInputHandle> GetConstConnectedInputs() const override;`
- L66 _public prototype_ `virtual bool Disconnect() override;`
- L69 _public prototype_ `virtual bool IsConnectionUserModifiable() const override;` — Connection logic.
- L70 _public prototype_ `virtual FConnectability CanConnectTo(const IInputController& InController) const override;`
- L71 _public prototype_ `virtual bool Connect(IInputController& InController) override;`
- L72 _public prototype_ `virtual bool ConnectWithConverterNode(IInputController& InController, const FConverterNodeInfo& InNodeClassName) override;`
- L73 _public prototype_ `virtual bool Disconnect(IInputController& InController) override;`
- L76 _protected prototype_ `virtual FDocumentAccess ShareAccess() override;`
- L77 _protected prototype_ `virtual FConstDocumentAccess ShareAccess() const override;`
- L79 _protected member_ `FGuid ID;`
- L80 _protected member_ `FConstVertexAccessPtr NodeVertexPtr;`
- L81 _protected member_ `FConstClassOutputAccessPtr ClassOutputPtr;`
- L82 _protected member_ `FGraphAccessPtr GraphPtr;`
- L83 _protected member_ `FNodeHandle OwningNode;`
- L87 _private prototype_ `TArray<FMetasoundFrontendEdge> FindEdges() const;`

#### struct `Metasound::Frontend::FBaseOutputController::FInitParams`  
`struct FInitParams`  
_L24-34_
- L26 _public member_ `FGuid ID;`
- L28 _public member_ `FConstVertexAccessPtr NodeVertexPtr;`
- L29 _public member_ `FConstClassOutputAccessPtr ClassOutputPtr;`
- L30 _public member_ `FGraphAccessPtr GraphPtr;`
- L33 _public member_ `FNodeHandle OwningNode;` — Node handle which owns this output.

#### class `Metasound::Frontend::FInputNodeOutputController`  
`class FInputNodeOutputController : public FBaseOutputController`  
_L97-140_
- inherits: `FBaseOutputController`
- desc: FInputNodeOutputController represents the output vertex of an input node. FInputNodeOutputController is largely to represent inputs coming into graph.
- L99 _private typedef_ `using FRegistry = FMetasoundFrontendRegistryContainer;`
- L115 _public prototype_ `FInputNodeOutputController(const FInitParams& InParams);` — Constructs the output controller.
- L117 _public prototype_ `virtual ~FInputNodeOutputController() = default;`
- L119 _public prototype_ `virtual bool IsValid() const override;`
- L122 _public prototype_ `virtual FText GetDisplayName() const override;`
- L123 _public prototype_ `virtual const FText& GetTooltip() const override;`
- L126 _public prototype_ `virtual const FMetasoundFrontendVertexMetadata& GetMetadata() const override;` — Input metadata
- L129 _public prototype_ `virtual void SetName(const FVertexName& InName) override;`
- L130 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetVertexAccessType() const override;`
- L133 _protected prototype_ `virtual FDocumentAccess ShareAccess() override;`
- L134 _protected prototype_ `virtual FConstDocumentAccess ShareAccess() const override;`
- L137 _private member_ `mutable FText CachedDisplayName;`
- L139 _private member_ `FConstClassInputAccessPtr OwningGraphClassInputPtr;`

#### struct `Metasound::Frontend::FInputNodeOutputController::FInitParams`  
`struct FInitParams`  
_L101-112_
- L103 _public member_ `FGuid ID;`
- L105 _public member_ `FConstVertexAccessPtr NodeVertexPtr;`
- L106 _public member_ `FConstClassOutputAccessPtr ClassOutputPtr;`
- L107 _public member_ `FConstClassInputAccessPtr OwningGraphClassInputPtr;`
- L108 _public member_ `FGraphAccessPtr GraphPtr;`
- L111 _public member_ `FNodeHandle OwningNode;` — Node handle which owns this output.

#### class `Metasound::Frontend::FOutputNodeOutputController`  
`class FOutputNodeOutputController : public FBaseOutputController`  
_L148-190_
- inherits: `FBaseOutputController`
- desc: FOutputNodeOutputController represents the output vertex of an input node. FOutputNodeOutputController is largely to represent inputs coming into graph.
- L150 _private typedef_ `using FRegistry = FMetasoundFrontendRegistryContainer;`
- L166 _public prototype_ `FOutputNodeOutputController(const FInitParams& InParams);` — Constructs the output controller.
- L168 _public prototype_ `virtual ~FOutputNodeOutputController() = default;`
- L170 _public prototype_ `virtual bool IsValid() const override;`
- L173 _public prototype_ `virtual FText GetDisplayName() const override;`
- L174 _public prototype_ `virtual const FText& GetTooltip() const override;`
- L177 _public prototype_ `virtual const FMetasoundFrontendVertexMetadata& GetMetadata() const override;` — Output metadata
- L180 _public prototype_ `virtual void SetName(const FVertexName& InName) override;`
- L181 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetVertexAccessType() const override;`
- L183 _public prototype_ `virtual bool IsConnectionUserModifiable() const override;`
- L184 _public prototype_ `virtual FConnectability CanConnectTo(const IInputController& InController) const override;`
- L185 _public prototype_ `virtual bool Connect(IInputController& InController) override;`
- L186 _public prototype_ `virtual bool ConnectWithConverterNode(IInputController& InController, const FConverterNodeInfo& InNodeClassName) override;`
- L189 _private member_ `FConstClassOutputAccessPtr OwningGraphClassOutputPtr;`

#### struct `Metasound::Frontend::FOutputNodeOutputController::FInitParams`  
`struct FInitParams`  
_L152-163_
- L154 _public member_ `FGuid ID;`
- L156 _public member_ `FConstVertexAccessPtr NodeVertexPtr;`
- L157 _public member_ `FConstClassOutputAccessPtr ClassOutputPtr;`
- L158 _public member_ `FConstClassOutputAccessPtr OwningGraphClassOutputPtr;`
- L159 _public member_ `FGraphAccessPtr GraphPtr;`
- L162 _public member_ `FNodeHandle OwningNode;` — Node handle which owns this output.

#### class `Metasound::Frontend::FVariableOutputController`  
`class FVariableOutputController : public FBaseOutputController`  
_L193-203_
- inherits: `FBaseOutputController`
- desc: Output controller for variable data type.
- L196 _public typedef_ `using FInitParams = FBaseOutputController::FInitParams;`
- L198 _public prototype_ `FVariableOutputController(const FInitParams& InParams);`
- L199 _public prototype_ `virtual ~FVariableOutputController() = default;`
- L202 _public prototype_ `virtual bool IsConnectionUserModifiable() const override;` — Variable data type connections are not modifiable by users

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Metasound`
- L14 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundFrontendProxyDataCache.h` (Private)


#### class `Metasound::Frontend::FProxyDataCache`  
`class FProxyDataCache`  
_L31-74_
- desc: FProxyDataCache creates and holds onto Audio::IProxyData produced from UObjects. A proxy data cache is useful in scenarios where proxies need to be retrieved from a thread where calling UObject functions is not safe. Additionally, the proxy data cache only creates a single proxy per a UObject when creating proxies from a FMetasoundFrontendDocument or any of it's subobjects.
- L35 _public prototype_ `void CreateAndCacheProxies(const FMetasoundFrontendDocument& InDocument, TArrayView<const FGuid> InPageOrder);` — Create and cache all proxies found in a document.
- L38 _public prototype_ `void CreateAndCacheProxies(const FMetasoundFrontendGraphClass& InGraphClass, TArrayView<const FGuid> InPageOrder);` — Create and cache all proxies found in a graph class.
- L41 _public prototype_ `void CreateAndCacheProxies(const FMetasoundFrontendClass& InClass, TArrayView<const FGuid> InPageOrder);` — Create and cache all proxies found in a frontend class class.
- L49 _public prototype_ `void CacheProxy(const UObject* InUObject, TSharedPtr<Audio::IProxyData> InProxy);` — Cache a specific object associated with a UObject pointer. No methods or data are accessed from the UObject pointer passed into this method. This method is safe even if the underlying UObject is invalid or garbage collected before or during this call.
- L58 _public prototype_ `bool Contains(const UObject* InUObject) const;` — Returns true if there is a proxy stored which is associated with the UObject address. No methods or data are accessed from the UObject pointer passed into this method. This method is safe even if the underlying UObject is invalid or garbage collected before or during this call.
- L68 _public prototype_ `const TSharedPtr<Audio::IProxyData>* FindProxy(const UObject* InObject) const;` — Returns a pointer to an existing proxy if one has been cached. Returns nullptr if none exist. No methods or data are accessed from the UObject pointer passed into this method. This method is safe even if the underlying UObject is invalid or garbage collected before or during this call.
- L71 _private typedef_ `using FUObjectMemoryAddress = const void*;`
- L73 _private member_ `TMap<FUObjectMemoryAddress, TSharedPtr<Audio::IProxyData>> ProxyCache;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Audio`
- L20 _namespace_ `namespace Metasound`
- L22 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundFrontendRegistryTransaction.h` (Private)


#### class `Metasound::Frontend::TTransactionBuffer`  
`template<typename TransactionType> class TTransactionBuffer`  
_L27-154_
- desc: Maintains a limited history of TransactionTypes. Calls are threadsafe (excluding the constructor and destructor.)
- L31 _public function_ `TTransactionBuffer() : NumRemovedTransactions(0) , CurrentReaderHandle(0)`
- L40 _public function_ `int32 AddTransaction(TransactionType&& InRegistryTransaction)` — Add a transaction to the history. Threadsafe. @return The transaction ID associated with the action.
- L50 _public function_ `FTransactionReaderHandle CreateReader()` — Create a new transaction reader for this buffer.
- L63 _public function_ `FTransactionReaderHandle DuplicateReader(FTransactionReaderHandle InReaderHandle)` — Create a duplicate reader which has the same read position as the provided reader handle.
- L81 _public function_ `void DestroyReader(FTransactionReaderHandle ReaderHandle)` — Destroy a reader associated with this buffer.
- L97 _public function_ `template<typename CallableType> void StreamTransactions(FTransactionReaderHandle InReaderHandle, CallableType InCallable)` — Invoke a function on all unread transactions. @param InReaderHandle - Handle of a valid reader for this buffer. @param InCallable - A callable of the form Callable(const TransactionType&)
- L126 _private function_ `void RemoveTransactionsStreamedToAllReaders()` — Remove transactions that have been streamed by all valid readers.
- L148 _private member_ `FCriticalSection RegistryTransactionMutex;`
- L150 _private member_ `int32 NumRemovedTransactions = 0;`
- L151 _private member_ `FTransactionReaderHandle CurrentReaderHandle = 0;`
- L152 _private member_ `TSortedMap<FTransactionReaderHandle, int32> ReaderPositions;`
- L153 _private member_ `TArray<TransactionType> TransactionHistory;`

#### class `Metasound::Frontend::TTransactionStream`  
`template<typename TransactionType> class TTransactionStream`  
_L159-216_
- desc: A transaction stream which streams data from a transaction buffer.
- L161 _private typedef_ `using TransactionBufferType = TTransactionBuffer<TransactionType>;`
- L163 _public function_ `TTransactionStream(TSharedRef<TransactionBufferType, ESPMode::ThreadSafe> InBuffer) : Buffer(InBuffer)`
- L169 _public function_ `TTransactionStream(const TTransactionStream& InOther) : Buffer(InOther.Buffer)`
- L175 _public function_ `TTransactionStream& operator=(const TTransactionStream& InOther)`
- L183 _public function_ `TTransactionStream(TTransactionStream&& InOther) : Buffer(MoveTemp(InOther.Buffer)) , ReaderHandle(InOther.ReaderHandle)`
- L190 _public function_ `TTransactionStream& operator=(TTransactionStream&& InOther)`
- L198 _public function_ `~TTransactionStream()`
- L208 _public function_ `template <typename CallableType> void Stream(CallableType Callable)` — Invoke a function on all unstreamed transactions. @param InCallable - A callable of the form Callable(const TransactionType&)
- L214 _private member_ `TSharedRef<TransactionBufferType, ESPMode::ThreadSafe> Buffer;`
- L215 _private member_ `FTransactionReaderHandle ReaderHandle = -1;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Metasound`
- L16 _namespace_ `namespace Frontend` (scope `Metasound`)
- L18 _externvar_ `extern int32 MetaSoundFrontendDiscardStreamedRegistryTransactionsCVar;` (scope `Metasound::Frontend`)
- L19 _externvar_ `extern FAutoConsoleVariableRef CVarMetaSoundFrontendDiscardStreamedRegistryTransactions;` (scope `Metasound::Frontend`)
- L21 _typedef_ `using FTransactionReaderHandle = uint32;` (scope `Metasound::Frontend`)
- L130 _function_ `const auto* MinElement = Algo::MinElementBy(ReaderPositions, [](const auto& Pair){return Pair.Value;});` (scope `Metasound::Frontend::TTransactionBuffer::RemoveTransactionsStreamedToAllReaders`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundFrontendSearchEngineCore.h` (Private)


#### class `Metasound::Frontend::SearchEngineQuerySteps::FMapClassToFullClassNameAndMajorVersion`  
`class FMapClassToFullClassNameAndMajorVersion : public IFrontendQueryMapStep`  
_L24-28_
- inherits: `IFrontendQueryMapStep`
- L27 _public prototype_ `virtual FFrontendQueryKey Map(const FFrontendQueryEntry& InEntry) const override;`

#### class `Metasound::Frontend::SearchEngineQuerySteps::FInterfaceRegistryTransactionSource`  
`class FInterfaceRegistryTransactionSource : public IFrontendQueryStreamStep`  
_L30-38_
- inherits: `IFrontendQueryStreamStep`
- L33 _public prototype_ `FInterfaceRegistryTransactionSource();`
- L34 _public prototype_ `virtual void Stream(TArray<FFrontendQueryValue>& OutEntries) override;`
- L37 _private member_ `TUniquePtr<FInterfaceTransactionStream> TransactionStream;`

#### class `Metasound::Frontend::SearchEngineQuerySteps::FMapInterfaceRegistryTransactionsToInterfaceRegistryVersions`  
`class FMapInterfaceRegistryTransactionsToInterfaceRegistryVersions : public IFrontendQueryMapStep`  
_L40-44_
- inherits: `IFrontendQueryMapStep`
- L43 _public prototype_ `virtual FFrontendQueryKey Map(const FFrontendQueryEntry& InEntry) const override;`

#### class `Metasound::Frontend::SearchEngineQuerySteps::FMapInterfaceRegistryTransactionToInterfaceName`  
`class FMapInterfaceRegistryTransactionToInterfaceName : public IFrontendQueryMapStep`  
_L46-50_
- inherits: `IFrontendQueryMapStep`
- L49 _public prototype_ `virtual FFrontendQueryKey Map(const FFrontendQueryEntry& InEntry) const override;`

#### class `Metasound::Frontend::SearchEngineQuerySteps::FReduceInterfaceRegistryTransactionsToCurrentStatus`  
`class FReduceInterfaceRegistryTransactionsToCurrentStatus : public IFrontendQueryReduceStep`  
_L52-59_
- inherits: `IFrontendQueryReduceStep`
- L55 _public prototype_ `virtual void Reduce(const FFrontendQueryKey& InKey, FFrontendQueryPartition& InOutEntries) const override;`
- L57 _private prototype_ `static FInterfaceRegistryTransaction::FTimeType GetTransactionTimestamp(const FFrontendQueryEntry& InEntry);`
- L58 _private prototype_ `static bool IsValidTransactionOfType(FInterfaceRegistryTransaction::ETransactionType InType, const FFrontendQueryEntry* InEntry);`

#### class `Metasound::Frontend::SearchEngineQuerySteps::FMapUClassToDefaultInterface`  
`class FMapUClassToDefaultInterface : public IFrontendQueryMultiMapStep`  
_L61-65_
- inherits: `IFrontendQueryMultiMapStep`
- L64 _public prototype_ `virtual TArray<FFrontendQueryKey> Map(const FFrontendQueryEntry& InEntry) const override;`

#### class `Metasound::Frontend::SearchEngineQuerySteps::FMapVersionToNameAndMajorVersion`  
`class FMapVersionToNameAndMajorVersion : public IFrontendQueryMapStep`  
_L67-72_
- inherits: `IFrontendQueryMapStep`
- L70 _public prototype_ `static FFrontendQueryKey GetKey(const FString& InName, int32 InMajorVersion);`
- L71 _public prototype_ `virtual FFrontendQueryKey Map(const FFrontendQueryEntry& InEntry) const override;`

#### class `Metasound::Frontend::SearchEngineQuerySteps::FReduceToHighestVersion`  
`class FReduceToHighestVersion : public IFrontendQueryReduceStep`  
_L74-78_
- inherits: `IFrontendQueryReduceStep`
- L77 _public prototype_ `virtual void Reduce(const FFrontendQueryKey& InKey, FFrontendQueryPartition& InOutEntries) const override;`

#### class `Metasound::Frontend::SearchEngineQuerySteps::FRemoveDeprecatedClasses`  
`class FRemoveDeprecatedClasses : public IFrontendQueryFilterStep`  
_L80-86_
- inherits: `IFrontendQueryFilterStep`
- L83 _public prototype_ `FRemoveDeprecatedClasses() = default;`
- L85 _public prototype_ `virtual bool Filter(const FFrontendQueryEntry& InEntry) const override;`

#### class `Metasound::Frontend::SearchEngineQuerySteps::FMapVersionToName`  
`class FMapVersionToName : public IFrontendQueryMapStep`  
_L88-92_
- inherits: `IFrontendQueryMapStep`
- L91 _public prototype_ `virtual FFrontendQueryKey Map(const FFrontendQueryEntry& InEntry) const override;`

#### class `Metasound::Frontend::SearchEngineQuerySteps::FTransformInterfaceRegistryTransactionToInterfaceVersion`  
`class FTransformInterfaceRegistryTransactionToInterfaceVersion : public IFrontendQueryTransformStep`  
_L94-98_
- inherits: `IFrontendQueryTransformStep`
- L97 _public prototype_ `virtual void Transform(FFrontendQueryEntry::FValue& InValue) const override;`

#### struct `Metasound::Frontend::ISearchEngineQuery`  
`struct ISearchEngineQuery`  
_L113-119_
- desc: Base interface for a search engine query. This allows the query to be primed to improve execution performance in critical call-stacks.
- L117 _public prototype_ `virtual void Prime() = 0;` — Prime the query to improve execution performance during subsequent queries.
- L118 _public prototype_ `virtual ~ISearchEngineQuery() = default;`

#### struct `Metasound::Frontend::TSearchEngineQuery`  
`template<typename QueryPolicy, typename... ArgTypes> struct TSearchEngineQuery : public ISearchEngineQuery`  
_L156-233_
- inherits: `ISearchEngineQuery`
- desc: TSearchEngineQuery provides a base for all queries used in the search engine. It requires a `QueryPolicy` as a template parameter. A `QueryPolicy` is a struct containing a static function to create the query, a static function to build a result from the query selection, and query result type. Example: struct FQueryPolicyExample { using ResultType = FMetaSoundClassInfo; static FFrontendQuery CreateQuery() { using namespace SearchEngineQuerySteps; FFrontendQuery Query; Query.AddStep<FNodeClassRegistrationEvents>() .AddStep<FMapClassRegistrationEventsToNodeRegistryKeys>() .AddStep<FReduceRegistrationEventsToCurrentStatus>() .AddStep<FTransformNodeClassRegistrationEventsToClassInfo>(); return Query; } static ResultType BuildResult(const FFrontendQueryPartition& InPartition) { FMetaSoundClassInfo MetaSoundClass; if (ensureMsgf(InPartition.Num() > 0, TEXT("Cannot retrieve class from empty partition"))) { MetaSoundClass = InPartition.CreateConstIterator()->Value.Get<FMetaSoundClassInfo>(); } return MetaSoundClass; } };
- L158 _public typedef_ `using ResultType = typename QueryPolicy::ResultType;`
- L160 _public function_ `TSearchEngineQuery(ArgTypes&&... Args) : Query(QueryPolicy::CreateQuery(Forward<ArgTypes>(Args)...))`
- L165 _public function_ `virtual void Prime() override`
- L174 _public function_ `ResultType UpdateAndFindResult(const FFrontendQueryKey& InKey)` — Updates the query to the most recent value and returns the result.
- L189 _public function_ `bool UpdateAndFindResult(const FFrontendQueryKey& InKey, ResultType& OutResult)` — Updates the query to the most recent value and assigns the value to OutResult. Returns true on success, false on failure.
- L204 _private function_ `void Update()`
- L230 _private member_ `FCriticalSection QueryCriticalSection;`
- L231 _private member_ `FFrontendQuery Query;`
- L232 _private member_ `TMap<FFrontendQueryKey, ResultType> ResultCache;`

#### struct `Metasound::Frontend::FFindClassWithHighestMinorVersionQueryPolicy`  
`struct FFindClassWithHighestMinorVersionQueryPolicy`  
_L237-243_
- desc: Policy for finding highest versioned metasound class by name and major version.
- L239 _public typedef_ `using ResultType = FNodeRegistryKey;`
- L241 _public prototype_ `static FFrontendQuery CreateQuery();`
- L242 _public prototype_ `static ResultType BuildResult(const FFrontendQueryPartition& InPartition);`

#### struct `Metasound::Frontend::FFindAllRegisteredInterfacesWithNameQueryPolicy`  
`struct FFindAllRegisteredInterfacesWithNameQueryPolicy`  
_L247-253_
- desc: Policy for finding all registered interface versions (name & version number) by name.
- L249 _public typedef_ `using ResultType = TArray<FMetasoundFrontendVersion>;`
- L251 _public prototype_ `static FFrontendQuery CreateQuery();`
- L252 _public prototype_ `static TArray<FMetasoundFrontendVersion> BuildResult(const FFrontendQueryPartition& InPartition);`

#### struct `Metasound::Frontend::FFindHighestVersionOfInterfaceQueryPolicy`  
`struct FFindHighestVersionOfInterfaceQueryPolicy`  
_L256-262_
- desc: Policy for finding the highest version registered interfaces by name.
- L258 _public typedef_ `using ResultType = FMetasoundFrontendVersion;`
- L260 _public prototype_ `static FFrontendQuery CreateQuery();`
- L261 _public prototype_ `static FMetasoundFrontendVersion BuildResult(const FFrontendQueryPartition& InPartition);`

#### struct `Metasound::Frontend::FFindAllInterfacesQueryPolicy`  
`struct FFindAllInterfacesQueryPolicy`  
_L265-271_
- desc: Policy for finding all registered interfaces.
- L267 _public typedef_ `using ResultType = TArray<FMetasoundFrontendVersion>;`
- L269 _public prototype_ `static FFrontendQuery CreateQuery();`
- L270 _public prototype_ `static ResultType BuildResult(const FFrontendQueryPartition& InPartition);`

#### struct `Metasound::Frontend::FFindAllInterfacesIncludingAllVersionsQueryPolicy`  
`struct FFindAllInterfacesIncludingAllVersionsQueryPolicy`  
_L274-280_
- desc: Policy for finding all registered interfaces (including deprecated).
- L276 _public typedef_ `using ResultType = TArray<FMetasoundFrontendVersion>;`
- L278 _public prototype_ `static FFrontendQuery CreateQuery();`
- L279 _public prototype_ `static TArray<FMetasoundFrontendVersion> BuildResult(const FFrontendQueryPartition& InPartition);`

#### struct `Metasound::Frontend::FFindAllDefaultInterfaceVersionsForUClassQueryPolicy`  
`struct FFindAllDefaultInterfaceVersionsForUClassQueryPolicy`  
_L283-289_
- desc: Policy for finding all default interface versions for a given UClass
- L285 _public typedef_ `using ResultType = TArray<FMetasoundFrontendVersion>;`
- L287 _public prototype_ `static FFrontendQuery CreateQuery();`
- L288 _public prototype_ `static TArray<FMetasoundFrontendVersion> BuildResult(const FFrontendQueryPartition& InPartition);`

#### class `Metasound::Frontend::FSearchEngineCore`  
`class FSearchEngineCore : public ISearchEngine`  
_L292-318_
- inherits: `ISearchEngine`
- desc: Supports essential search engine functionality needed for runtime.
- L294 _private prototype_ `FSearchEngineCore(const FSearchEngineCore&) = delete;`
- L295 _private prototype_ `FSearchEngineCore(FSearchEngineCore&&) = delete;`
- L296 _private prototype_ `FSearchEngineCore& operator=(const FSearchEngineCore&) = delete;`
- L297 _private prototype_ `FSearchEngineCore& operator=(FSearchEngineCore&&) = delete;`
- L300 _public prototype_ `FSearchEngineCore() = default;`
- L301 _public prototype_ `virtual ~FSearchEngineCore() = default;`
- L303 _public prototype_ `virtual void Prime() override;`
- L305 _public prototype_ `virtual bool FindRegisteredClass(const FMetasoundFrontendClassName& InName, int32 InMajorVersion, FMetaSoundClassInfo& OutClass) override;`
- L307 _public prototype_ `virtual TArray<FMetasoundFrontendVersion> FindUClassDefaultInterfaceVersions(const FTopLevelAssetPath& InUClassPath) override;`
- L308 _public prototype_ `virtual TArray<FMetasoundFrontendVersion> FindAllRegisteredInterfacesWithName(FName InInterfaceName) override;`
- L310 _public prototype_ `virtual bool FindHighestInterfaceVersion(FName InInterfaceName, FMetasoundFrontendVersion& OutVersion) override;`
- L311 _public prototype_ `virtual bool FindInterfaceWithHighestVersion(FName InInterfaceName, FMetasoundFrontendInterface& OutInterface) override;`
- L314 _private member_ `TSearchEngineQuery<FFindClassWithHighestMinorVersionQueryPolicy> FindClassWithHighestMinorVersionQuery;`
- L315 _private member_ `TSearchEngineQuery<FFindAllRegisteredInterfacesWithNameQueryPolicy> FindAllRegisteredInterfacesWithNameQuery;`
- L316 _private member_ `TSearchEngineQuery<FFindAllDefaultInterfaceVersionsForUClassQueryPolicy> FindAllDefaultInterfaceVersionsForUClassQuery;`
- L317 _private member_ `TSearchEngineQuery<FFindHighestVersionOfInterfaceQueryPolicy> FindHighestVersionOfInterfaceQueryPolicy;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Metasound`
- L18 _namespace_ `namespace Frontend` (scope `Metasound`)
- L20 _namespace_ `namespace SearchEngineQuerySteps` (scope `Metasound::Frontend`)
- L101 _prototype_ `TArray<FMetaSoundClassInfo> BuildArrayOfClassesFromPartition(const FFrontendQueryPartition& InPartition);` (scope `Metasound::Frontend::SearchEngineQuerySteps`) — Convert an array of partitions into an array of metasound frontend classes.
- L103 _prototype_ `FMetaSoundClassInfo BuildSingleClassFromPartition(const FFrontendQueryPartition& InPartition);` (scope `Metasound::Frontend::SearchEngineQuerySteps`)
- L105 _prototype_ `FMetasoundFrontendVersion BuildSingleVersionFromPartition(const FFrontendQueryPartition& InPartition);` (scope `Metasound::Frontend::SearchEngineQuerySteps`)
- L108 _prototype_ `TArray<FMetasoundFrontendVersion> BuildArrayOfVersionsFromPartition(const FFrontendQueryPartition& InPartition);` (scope `Metasound::Frontend::SearchEngineQuerySteps`) — Convert an array of partitions into an array of metasound frontend versions.

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundFrontendSearchEngineEditorOnly.h` (Private)


#### struct `Metasound::Frontend::FFindAllAssetClassInfoQueryPolicy`  
`struct FFindAllAssetClassInfoQueryPolicy`  
_L15-21_
- desc: Policy for finding all registered asset classes that are not deprecated and referenceable.
- L17 _public typedef_ `using ResultType = TArray<FMetaSoundClassInfo>;`
- L19 _public prototype_ `static FFrontendQuery CreateQuery();`
- L20 _public prototype_ `static ResultType BuildResult(const FFrontendQueryPartition& InPartition);`

#### struct `Metasound::Frontend::FFindAllClassesQueryPolicy`  
`struct FFindAllClassesQueryPolicy`  
_L24-30_
- desc: Policy for finding all registered metasound classes that are not deprecated and referenceable.
- L26 _public typedef_ `using ResultType = TArray<FMetaSoundClassInfo>;`
- L28 _public prototype_ `static FFrontendQuery CreateQuery();`
- L29 _public prototype_ `static ResultType BuildResult(const FFrontendQueryPartition& InPartition);`

#### struct `Metasound::Frontend::FFindAllRegisteredClassesIncludingAllVersionsQueryPolicy`  
`struct FFindAllRegisteredClassesIncludingAllVersionsQueryPolicy`  
_L33-39_
- desc: Policy for finding all registered metasound classes, including deprecated classes.
- L35 _public typedef_ `using ResultType = TArray<FMetaSoundClassInfo>;`
- L37 _public prototype_ `static FFrontendQuery CreateQuery();`
- L38 _public prototype_ `static ResultType BuildResult(const FFrontendQueryPartition& InPartition);`

#### struct `Metasound::Frontend::FFindAllRegisteredAssetsQueryPolicy`  
`struct FFindAllRegisteredAssetsQueryPolicy`  
_L42-48_
- desc: Policy for finding all registered metasound assets.
- L44 _public typedef_ `using ResultType = TArray<FMetaSoundClassInfo>;`
- L46 _public prototype_ `static FFrontendQuery CreateQuery();`
- L47 _public prototype_ `static ResultType BuildResult(const FFrontendQueryPartition& InPartition);`

#### struct `Metasound::Frontend::FFindClassesWithNameSortedQueryPolicy`  
`struct FFindClassesWithNameSortedQueryPolicy`  
_L52-58_
- desc: Policy for finding all registered metasound classes sorted by version and indexed by name.
- L54 _public typedef_ `using ResultType = TArray<FMetaSoundClassInfo>;`
- L56 _public prototype_ `static FFrontendQuery CreateQuery();`
- L57 _public prototype_ `static ResultType BuildResult(const FFrontendQueryPartition& InPartition);`

#### struct `Metasound::Frontend::FFindClassesWithNameUnsortedQueryPolicy`  
`struct FFindClassesWithNameUnsortedQueryPolicy`  
_L61-67_
- desc: Policy for finding all registered metasound classes indexed by name.
- L63 _public typedef_ `using ResultType = TArray<FMetaSoundClassInfo>;`
- L65 _public prototype_ `static FFrontendQuery CreateQuery();`
- L66 _public prototype_ `static ResultType BuildResult(const FFrontendQueryPartition& InPartition);`

#### struct `Metasound::Frontend::FFindClassWithHighestVersionQueryPolicy`  
`struct FFindClassWithHighestVersionQueryPolicy`  
_L70-76_
- desc: Policy for finding highest versioned metasound class by name.
- L72 _public typedef_ `using ResultType = FMetaSoundClassInfo;`
- L74 _public prototype_ `static FFrontendQuery CreateQuery();`
- L75 _public prototype_ `static ResultType BuildResult(const FFrontendQueryPartition& InPartition);`

#### class `Metasound::Frontend::FSearchEngineEditorOnly`  
`class FSearchEngineEditorOnly : public FSearchEngineCore`  
_L81-110_
- inherits: `FSearchEngineCore`
- desc: To minimize runtime memory costs during gampeplay, some search engine queries are only exposed when the editor only data is available. This class supports the editor only functionality of the search engine.
- L83 _private prototype_ `FSearchEngineEditorOnly(const FSearchEngineEditorOnly&) = delete;`
- L84 _private prototype_ `FSearchEngineEditorOnly(FSearchEngineEditorOnly&&) = delete;`
- L85 _private prototype_ `FSearchEngineEditorOnly& operator=(const FSearchEngineEditorOnly&) = delete;`
- L86 _private prototype_ `FSearchEngineEditorOnly& operator=(FSearchEngineEditorOnly&&) = delete;`
- L88 _private typedef_ `using Super = FSearchEngineCore;`
- L91 _public prototype_ `FSearchEngineEditorOnly() = default;`
- L92 _public prototype_ `virtual ~FSearchEngineEditorOnly() = default;`
- L94 _public prototype_ `virtual void Prime() override;`
- L95 _public prototype_ `virtual TArray<FMetaSoundClassInfo> FindAllClasses(ISearchEngine::EResultVersion VersionOptions, bool bIncludeUnloadedAssets = false) override;`
- L96 _public prototype_ `virtual TArray<FMetaSoundClassInfo> FindClassesWithName(const FMetasoundFrontendClassName& InName, ESortByVersion SortByVersion = ESortByVersion::Yes) override;`
- L97 _public prototype_ `virtual TArray<FMetasoundFrontendClass> FindClassesWithName(const FMetasoundFrontendClassName& InName, bool bInSortByVersion) override;`
- L98 _public prototype_ `virtual bool FindClassWithHighestVersion(const FMetasoundFrontendClassName& InName, FMetaSoundClassInfo& OutClassInfo) override;`
- L99 _public prototype_ `virtual TArray<FMetasoundFrontendVersion> FindAllInterfaceVersions(bool bInIncludeAllVersions) override;`
- L102 _private member_ `TSearchEngineQuery<FFindAllAssetClassInfoQueryPolicy> FindAllAssetClassInfoQuery;`
- L103 _private member_ `TSearchEngineQuery<FFindAllClassesQueryPolicy> FindAllClassesQuery;`
- L104 _private member_ `TSearchEngineQuery<FFindAllRegisteredClassesIncludingAllVersionsQueryPolicy> FindAllClassesIncludingAllVersionsQuery;`
- L105 _private member_ `TSearchEngineQuery<FFindClassesWithNameUnsortedQueryPolicy> FindClassesWithNameUnsortedQuery;`
- L106 _private member_ `TSearchEngineQuery<FFindClassesWithNameSortedQueryPolicy> FindClassesWithNameSortedQuery;`
- L107 _private member_ `TSearchEngineQuery<FFindClassWithHighestVersionQueryPolicy> FindClassWithHighestVersionQuery;`
- L108 _private member_ `TSearchEngineQuery<FFindAllInterfacesQueryPolicy> FindAllInterfacesQuery;`
- L109 _private member_ `TSearchEngineQuery<FFindAllInterfacesIncludingAllVersionsQueryPolicy> FindAllInterfacesIncludingAllVersionsQuery;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundFrontendSubgraphNodeController.h` (Private)


#### class `Metasound::Frontend::FSubgraphNodeController`  
`class FSubgraphNodeController : public FBaseNodeController`  
_L15-81_
- inherits: `FBaseNodeController`
- desc: Controller for nodes representing subgraphs. Handles synchronization of node interface to subgraph interface.
- L20 _private typedef_ `using Super = FBaseNodeController;`
- L36 _public prototype_ `FSubgraphNodeController(EPrivateToken InToken, const FInitParams& InParams);` — Constructor takes a private token so it can only be instantiated by using the static creation functions. This protects against some error conditions which would result in a zombie object. The creation methods can detect the error conditions and return an invalid controller on error
- L42 _public prototype_ `static FNodeHandle CreateNodeHandle(const FInitParams& InParams);` — Create a node handle for a external or subgraph node. @return A Node handle. On error, an invalid node handle is returned.
- L48 _public prototype_ `static FConstNodeHandle CreateConstNodeHandle(const FInitParams& InParams);` — Create a node handle for a external or subgraph node. @return A Node handle. On error, an invalid node handle is returned.
- L50 _public prototype_ `virtual ~FSubgraphNodeController() = default;`
- L52 _public prototype_ `bool IsValid() const override;`
- L54 _public prototype_ `virtual int32 GetNumInputs() const override;`
- L56 _public prototype_ `virtual int32 GetNumOutputs() const override;`
- L59 _protected typedef_ `using FInputControllerParams = FBaseNodeController::FInputControllerParams;`
- L60 _protected typedef_ `using FOutputControllerParams = FBaseNodeController::FOutputControllerParams;`
- L62 _protected prototype_ `virtual FDocumentAccess ShareAccess() override;`
- L63 _protected prototype_ `virtual FConstDocumentAccess ShareAccess() const override;`
- L65 _protected prototype_ `virtual TArray<FInputControllerParams> GetInputControllerParams() const override;`
- L66 _protected prototype_ `virtual TArray<FOutputControllerParams> GetOutputControllerParams() const override;`
- L68 _protected prototype_ `virtual bool FindInputControllerParamsWithVertexName(const FVertexName& InName, FInputControllerParams& OutParams) const override;`
- L69 _protected prototype_ `virtual bool FindOutputControllerParamsWithVertexName(const FVertexName& InName, FOutputControllerParams& OutParams) const override;`
- L71 _protected prototype_ `virtual bool FindInputControllerParamsWithID(FGuid InVertexID, FInputControllerParams& OutParams) const override;`
- L72 _protected prototype_ `virtual bool FindOutputControllerParamsWithID(FGuid InVertexID, FOutputControllerParams& OutParams) const override;`
- L75 _private prototype_ `void ConformNodeInterfaceToClassInterface();`
- L77 _private prototype_ `virtual FInputHandle CreateInputController(FGuid InVertexID, FConstVertexAccessPtr InNodeVertexPtr, FConstClassInputAccessPtr InClassInputPtr, FNodeHandle InOwningNode) const override;`
- L78 _private prototype_ `virtual FOutputHandle CreateOutputController(FGuid InVertexID, FConstVertexAccessPtr InNodeVertexPtr, FConstClassOutputAccessPtr InClassOutputPtr, FNodeHandle InOwningNode) const override;`
- L80 _private member_ `FGraphAccessPtr GraphPtr;`

#### enum `Metasound::Frontend::FSubgraphNodeController::EPrivateToken`  
`enum EPrivateToken`  
_L18-18_
- desc: Private token only allows members or friends to call constructor.
- L18 _public enumerator_ `enum EPrivateToken { Token }; using Super = FBaseNodeController; public: struct FInitParams { FNodeAccessPtr NodePtr;` — Private token only allows members or friends to call constructor.

#### struct `Metasound::Frontend::FSubgraphNodeController::FInitParams`  
`struct FInitParams`  
_L23-29_
- L25 _public member_ `FNodeAccessPtr NodePtr;`
- L26 _public member_ `FConstClassAccessPtr ClassPtr;`
- L27 _public member_ `FGraphAccessPtr GraphPtr;`
- L28 _public member_ `FGraphHandle OwningGraph;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`
- L10 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundFrontendVariableController.h` (Private)


#### class `Metasound::Frontend::FVariableController`  
`class FVariableController : public IVariableController`  
_L17-96_
- inherits: `IVariableController`
- L26 _public prototype_ `FVariableController(const FInitParams& InParams);`
- L27 _public prototype_ `virtual ~FVariableController() = default;`
- L30 _public prototype_ `virtual bool IsValid() const override;` — Returns true if the controller is in a valid state.
- L32 _public prototype_ `virtual FGuid GetID() const override;`
- L35 _public prototype_ `virtual const FName& GetDataType() const override;` — Returns the data type name associated with this variable.
- L38 _public prototype_ `virtual const FName& GetName() const override;` — Returns the name associated with this variable.
- L41 _public prototype_ `virtual void SetName(const FName& InName) override;` — Sets the name associated with this variable.
- L45 _public prototype_ `virtual FText GetDisplayName() const override;` — Returns the human readable name associated with this variable.
- L48 _public prototype_ `virtual void SetDisplayName(const FText& InDisplayName) override;` — Sets the human readable name associated with this variable.
- L51 _public prototype_ `virtual FText GetDescription() const override;` — Returns the human readable description associated with this variable.
- L54 _public prototype_ `virtual void SetDescription(const FText& InDescription) override;` — Sets the human readable description associated with this variable.
- L58 _public prototype_ `virtual FNodeHandle FindMutatorNode() override;` — Returns the mutator node associated with this variable.
- L61 _public prototype_ `virtual FConstNodeHandle FindMutatorNode() const override;` — Returns the mutator node associated with this variable.
- L64 _public prototype_ `virtual TArray<FNodeHandle> FindAccessorNodes() override;` — Returns the accessor nodes associated with this variable.
- L67 _public prototype_ `virtual TArray<FConstNodeHandle> FindAccessorNodes() const override;` — Returns the accessor nodes associated with this variable.
- L70 _public prototype_ `virtual TArray<FNodeHandle> FindDeferredAccessorNodes() override;` — Returns the deferred accessor nodes associated with this variable.
- L73 _public prototype_ `virtual TArray<FConstNodeHandle> FindDeferredAccessorNodes() const override;` — Returns the deferred accessor nodes associated with this variable.
- L76 _public prototype_ `virtual FGraphHandle GetOwningGraph() override;` — Returns a FGraphHandle to the node which owns this variable.
- L79 _public prototype_ `virtual FConstGraphHandle GetOwningGraph() const override;` — Returns a FConstGraphHandle to the node which owns this variable.
- L82 _public prototype_ `virtual const FMetasoundFrontendLiteral& GetLiteral() const override;` — Returns the value for the given variable instance if set.
- L85 _public prototype_ `virtual bool SetLiteral(const FMetasoundFrontendLiteral& InLiteral) override;` — Sets the value for the given variable instance
- L88 _private prototype_ `virtual FConstDocumentAccess ShareAccess() const override;`
- L89 _private prototype_ `virtual FDocumentAccess ShareAccess() override;`
- L91 _private prototype_ `TArray<FNodeHandle> GetNodeArray(const TArray<FGuid>& InNodeIDs);`
- L92 _private prototype_ `TArray<FConstNodeHandle> GetNodeArray(const TArray<FGuid>& InNodeIDs) const;`
- L94 _private member_ `FVariableAccessPtr VariablePtr;`
- L95 _private member_ `FGraphHandle OwningGraph;`

#### struct `Metasound::Frontend::FVariableController::FInitParams`  
`struct FInitParams`  
_L20-24_
- L22 _public member_ `FVariableAccessPtr VariablePtr;`
- L23 _public member_ `FGraphHandle OwningGraph;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L13 _namespace_ `namespace Metasound`
- L15 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundGraphNode.h` (Private)


#### class `Metasound::Frontend::FGraphNode`  
`class FGraphNode : public INode`  
_L16-60_
- inherits: `INode`
- desc: FGraphNode is used to create unique INodes based off of a IGraph. Individual nodes need to reflect their InstanceName and InstanceID, but otherwise they simply encapsulate a shared set of behavior. To minimize memory usage, a single shared IGraph is used for all nodes referring to the same IGraph.
- L37 _public prototype_ `FGraphNode(const FNodeInitData& InNodeInitData, TSharedRef<const IGraph> InGraphToWrap);`
- L39 _public prototype_ `FGraphNode(FNodeData InNodeData, TSharedRef<const IGraph> InGraphToWrap);`
- L41 _public prototype_ `virtual const FName& GetInstanceName() const override;`
- L43 _public prototype_ `virtual const FGuid& GetInstanceID() const override;`
- L45 _public prototype_ `virtual const FNodeClassMetadata& GetMetadata() const override;`
- L47 _public prototype_ `virtual const FVertexInterface& GetVertexInterface() const override;`
- L49 _public prototype_ `virtual void SetDefaultInput(const FVertexName& InVertexName, const FLiteral& InLiteral) override;`
- L51 _public prototype_ `virtual TSharedPtr<const IOperatorData> GetOperatorData() const override;`
- L53 _public prototype_ `virtual FOperatorFactorySharedRef GetDefaultOperatorFactory() const override;`
- L57 _private member_ `FNodeData NodeData;`
- L58 _private member_ `TSharedRef<FGraphOperatorFactoryAdapter> Factory;`
- L59 _private member_ `TSharedRef<const IGraph> Graph;`

#### class `Metasound::Frontend::FGraphNode::FGraphOperatorFactoryAdapter`  
`class FGraphOperatorFactoryAdapter : public IOperatorFactory`  
_L23-34_
- inherits: `IOperatorFactory`
- desc: This adapter class forwards the correct FBuilderOperatorParams to the graph's operator creation method. Many operator creation methods downcast the supplied INode in `FBuilderOperatorParams` and so it is required that it point to the correct runtime instance when calling CreateOperator(...)
- L26 _public prototype_ `FGraphOperatorFactoryAdapter(const IGraph& InGraph);`
- L27 _public prototype_ `virtual ~FGraphOperatorFactoryAdapter() = default;`
- L29 _public prototype_ `virtual TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults) override;`
- L32 _private member_ `const IGraph* Graph;` — Only store pointer because owning node keeps wrapped IGraph alive.
- L33 _private member_ `FOperatorFactorySharedRef GraphFactory;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Metasound`
- L9 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Private/MetasoundJsonBackend.h` (Private)


#### struct `Metasound::StructDeserializerBackendUtilities`  
`struct StructDeserializerBackendUtilities`  
_L28-117_
- L40 _public function_ `static bool ClearPropertyValue(FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex)` — Clears the value of the given property. @param Property The property to clear. @param Outer The property that contains the property to be cleared, if any. @param Data A pointer to the memory holding the property's data. @param ArrayIndex The index of the element to clear (if the property is an array). @return true on success, false otherwise. @see SetPropertyValue
- L71 _public function_ `static void* GetPropertyValuePtr(FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex)` — Gets a pointer to object of the given property. @param Property The property to get. @param Outer The property that contains the property to be get, if any. @param Data A pointer to the memory holding the property's data. @param ArrayIndex The index of the element to set (if the property is an array). @return A pointer to the object represented by the property, null otherwise.. @see ClearPropertyValue
- L107 _public function_ `template<typename PropertyType, typename ValueType> static bool SetPropertyValue(PropertyType* Property, FProperty* Outer, void* Data, int32 ArrayIndex, const ValueType& Value)` — Sets the value of the given property. @param Property The property to set. @param Outer The property that contains the property to be set, if any. @param Data A pointer to the memory holding the property's data. @param ArrayIndex The index of the element to set (if the property is an array). @return true on success, false otherwise. @see ClearPropertyValue

#### class `Metasound::TJsonStructSerializerBackend`  
`template <class CharType, class PrintPolicy = TPrettyJsonPrintPolicy<CharType>> class TJsonStructSerializerBackend : public IStructSerializerBackend`  
_L173-397_
- inherits: `IStructSerializerBackend`
- desc: Implements a writer for UStruct serialization using Json. Optionally, CharType and PrettyPrintPolicy can be subsituted using template arguments.
- L184 _public function_ `TJsonStructSerializerBackend(FArchive& InArchive, const EStructSerializerBackendFlags InFlags) : JsonWriter(TJsonWriter<CharType, PrintPolicy>::Create(&InArchive)) , Flags(InFlags)` — Creates and initializes a new instance with the given flags. @param InArchive The archive to serialize into. @param InFlags The flags that control the serialization behavior (typically EStructSerializerBackendFlags::Default).
- L189 _public prototype_ `~TJsonStructSerializerBackend() = default;`
- L195 _public function_ `virtual void BeginArray(const FStructSerializerState& State) override`
- L213 _public function_ `virtual void BeginStructure(const FStructSerializerState& State) override`
- L238 _public function_ `virtual void EndArray(const FStructSerializerState& State) override`
- L243 _public function_ `virtual void EndStructure(const FStructSerializerState& State) override`
- L248 _public function_ `virtual void WriteComment(const FString& Comment) override`
- L253 _public function_ `virtual void WriteProperty(const FStructSerializerState& State, int32 ArrayIndex = 0) override`
- L385 _protected function_ `TSharedRef<TJsonWriter<CharType, PrintPolicy>>& GetWriter()` — Allow access to the internal JsonWriter to subclasses
- L393 _private member_ `TSharedRef<TJsonWriter<CharType, PrintPolicy>> JsonWriter;` — Holds the Json writer used for the actual serialization.
- L396 _private member_ `EStructSerializerBackendFlags Flags;` — Flags controlling the serialization behavior.

#### class `Metasound::TJsonStructDeserializerBackend`  
`template <class CharType> class TJsonStructDeserializerBackend : public IStructDeserializerBackend`  
_L406-702_
- inherits: `IStructDeserializerBackend`
- desc: Implements a reader for UStruct deserialization using Json. Optionally, CharType that we're decoding from can be substituted using the CharType template argument.
- L416 _public function_ `TJsonStructDeserializerBackend(FArchive& Archive) : JsonReader(TJsonReader<CharType>::Create(&Archive))` — Creates and initializes a new instance. @param Archive The archive to deserialize from.
- L420 _public prototype_ `~TJsonStructDeserializerBackend() = default;`
- L426 _public function_ `virtual const FString& GetCurrentPropertyName() const override`
- L431 _public function_ `virtual FString GetDebugString() const override`
- L436 _public function_ `virtual const FString& GetLastErrorMessage() const override`
- L441 _public function_ `virtual bool GetNextToken(EStructDeserializerBackendTokens& OutToken) override`
- L486 _public function_ `virtual bool ReadProperty(FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex) override`
- L666 _public function_ `virtual void SkipArray() override`
- L671 _public function_ `virtual void SkipStructure() override`
- L677 _protected function_ `FString& GetLastIdentifier()`
- L682 _protected function_ `EJsonNotation GetLastNotation()`
- L687 _protected function_ `TSharedRef<TJsonReader<CharType>>& GetReader()`
- L695 _private member_ `FString LastIdentifier;` — Holds the name of the last read Json identifier.
- L698 _private member_ `EJsonNotation LastNotation;` — Holds the last read Json notation.
- L701 _private member_ `TSharedRef<TJsonReader<CharType>> JsonReader;` — Holds the Json reader used for the actual reading of the archive.

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace Metasound`
- L26 _typedef_ `typedef ANSICHAR DefaultCharType;` (scope `Metasound`)
- L119 _namespace_ `namespace JsonStructSerializerBackend` (scope `Metasound`)
- L123 _function_ `template<typename JsonWriterType, typename ValueType> static void WritePropertyValue(const TSharedRef<JsonWriterType> JsonWriter, const FStructSerializerState& State, const ValueType& Value)` (scope `Metasound::JsonStructSerializerBackend`) — Writes a property value to the serialization output.
- L145 _function_ `static void WriteNull(const TSharedRef<TJsonWriter<UCS2CHAR>> JsonWriter, const FStructSerializerState& State)` (scope `Metasound::JsonStructSerializerBackend`) — Writes a null value to the serialization output.

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Analysis/MetasoundFrontendAnalyzerAddress.h` (Public)


#### class `Metasound::Frontend::FAnalyzerAddress`  
`class FAnalyzerAddress : public FTransmissionAddress`  
_L23-74_
- inherits: `FTransmissionAddress`
- desc: String serializable (as key) channel of analyzer or its internal members that can be written to or read from using the Transmission System.
- L26 _public prototype_ `FAnalyzerAddress(const FString& InAddressString);`
- L27 _public prototype_ `FAnalyzerAddress() = default;`
- L29 _public prototype_ `virtual ~FAnalyzerAddress() = default;`
- L31 _public prototype_ `virtual FName GetAddressType() const override;`
- L33 _public prototype_ `virtual FName GetDataType() const override;`
- L35 _public prototype_ `virtual TUniquePtr<FTransmissionAddress> Clone() const override;`
- L38 _public prototype_ `virtual FString ToString() const override;` — Converts AnalyzerAddress to String representation using the PathSeparator
- L40 _public prototype_ `virtual uint32 GetHash() const override;`
- L42 _public prototype_ `virtual bool IsEqual(const FTransmissionAddress& InOther) const override;`
- L45 _public member_ `uint64 InstanceID = TNumericLimits<uint64>::Max();` — Active Instance ID to monitor
- L48 _public member_ `FGuid NodeID;` — ID of Node being monitored
- L52 _public member_ `FVertexName OutputName;` — Name of output to monitor (not to be confused with the Analyzer's members, which are specific to the analyzer instance being addressed)
- L55 _public member_ `FName DataType;` — DataType of the given channel
- L58 _public member_ `FName AnalyzerName;` — Name of Analyzer
- L62 _public member_ `FGuid AnalyzerInstanceID;` — Instance ID of analyzer (allowing for multiple analyzer of the same type to be addressed at the same output).
- L68 _public member_ `FName AnalyzerMemberName;` — Optional name used to specify a channel for a given analyzer's inputs/outputs. If not provided (i.e. 'none'), single input & output are assumed to share the same name. Useful if the analyzer requires outputting multiple analysis values. Can potentially be used as an input as well to modify analyzer settings.
- L73 _public member_ `bool UseDataTransmissionCenter = true;` — Specifies whether to use the data transmission center for passing values to views.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L15 _macro_ `#define METASOUND_ANALYZER_PATH_SEPARATOR TEXT("/")`
- L17 _namespace_ `namespace Metasound`
- L19 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Analysis/MetasoundFrontendAnalyzerFactory.h` (Public)


#### class `Metasound::Frontend::IVertexAnalyzerFactory`  
`class IVertexAnalyzerFactory`  
_L12-20_
- L15 _public prototype_ `virtual ~IVertexAnalyzerFactory() = default;`
- L17 _public prototype_ `virtual const TArray<FAnalyzerOutput>& GetAnalyzerOutputs() const = 0;`
- L18 _public prototype_ `virtual FName GetDataType() const = 0;`
- L19 _public prototype_ `virtual TUniquePtr<IVertexAnalyzer> CreateAnalyzer(const FCreateAnalyzerParams& InParams) const = 0;`

#### class `Metasound::Frontend::TVertexAnalyzerFactory`  
`template<typename TAnalyzerClass> class TVertexAnalyzerFactory : public IVertexAnalyzerFactory`  
_L23-35_
- inherits: `IVertexAnalyzerFactory`
- L26 _public function_ `static const FName& GetAnalyzerName()`
- L28 _public prototype_ `virtual ~TVertexAnalyzerFactory() = default;`
- L30 _public function_ `virtual FName GetDataType() const override`
- L31 _public function_ `virtual TUniquePtr<IVertexAnalyzer> CreateAnalyzer(const FCreateAnalyzerParams& InParams) const override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`
- L10 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Analysis/MetasoundFrontendAnalyzerRegistry.h` (Public)


#### class `Metasound::Frontend::IVertexAnalyzerRegistry`  
`class IVertexAnalyzerRegistry`  
_L19-28_
- L22 _public prototype_ `virtual ~IVertexAnalyzerRegistry() = default;`
- L24 _public prototype_ `static IVertexAnalyzerRegistry& Get();`
- L26 _public prototype_ `virtual const IVertexAnalyzerFactory* FindAnalyzerFactory(FName InAnalyzerName) const = 0;`
- L27 _public prototype_ `virtual void RegisterAnalyzerFactory(FName AnalyzerName, TUniquePtr<IVertexAnalyzerFactory>&& Factory) = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L9 _namespace_ `namespace Metasound`
- L14 _namespace_ `namespace Frontend` (scope `Metasound`)
- L32 _macro_ `#define METASOUND_REGISTER_VERTEX_ANALYZER_FACTORY(ANALYZER_CLASS) \`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Analysis/MetasoundFrontendAnalyzerView.h` (Public)


#### class `Metasound::Frontend::FMetasoundAnalyzerView`  
`class FMetasoundAnalyzerView`  
_L27-64_
- desc: Pairs an IReceiver with a given AnalyzerAddress, which enables watching a particular analyzer result on any given thread.
- L29 _private member_ `TMap<FName, TSharedPtr<IReceiver>> OutputReceivers;`
- L32 _public member_ `const FAnalyzerAddress AnalyzerAddress = { };`
- L34 _public prototype_ `FMetasoundAnalyzerView() = default;`
- L35 _public prototype_ `FMetasoundAnalyzerView(FAnalyzerAddress&& InAnalyzerAddress);`
- L37 _public prototype_ `void BindToAllOutputs(const FOperatorSettings& InOperatorSettings);`
- L38 _public prototype_ `bool UnbindOutput(FName InOutputName);`
- L41 _public function_ `template <typename DataType> bool TryGetOutputData(FName InOutputName, DataType& OutValue)`
- L63 _public prototype_ `TArray<FBoundOutputDescription> GetBoundOutputDescriptions() const;`

#### struct `Metasound::Frontend::FMetasoundAnalyzerView::FBoundOutputDescription`  
`struct FBoundOutputDescription`  
_L57-61_
- L59 _public member_ `FName Name;`
- L60 _public member_ `FName TypeName;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L18 _namespace_ `namespace Metasound`
- L23 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Analysis/MetasoundFrontendGraphAnalyzer.h` (Public)


#### class `Metasound::Frontend::FGraphAnalyzerAddress`  
`class FGraphAnalyzerAddress : public FTransmissionAddress`  
_L20-67_
- inherits: `FTransmissionAddress`
- L22 _private member_ `uint64 InstanceID = INDEX_NONE;`
- L25 _public function_ `FGraphAnalyzerAddress(uint64 InInstanceID) : InstanceID(InInstanceID)`
- L30 _public prototype_ `virtual ~FGraphAnalyzerAddress() = default;`
- L32 _public function_ `virtual FName GetAddressType() const override`
- L37 _public function_ `virtual FName GetDataType() const override`
- L42 _public function_ `virtual TUniquePtr<FTransmissionAddress> Clone() const override`
- L47 _public function_ `virtual FString ToString() const override`
- L52 _public function_ `virtual uint32 GetHash() const override`
- L57 _public function_ `virtual bool IsEqual(const FTransmissionAddress& InOther) const override`

#### class `Metasound::Frontend::FGraphAnalyzer`  
`class FGraphAnalyzer`  
_L71-86_
- desc: Handles intrinsic analysis operations within a given graph should the graph's operator be enabled for analysis.
- L73 _private member_ `const FOperatorSettings OperatorSettings;`
- L74 _private member_ `const uint64 InstanceID = INDEX_NONE;`
- L76 _private member_ `TUniquePtr<IReceiver> ActiveAnalyzerReceiver;`
- L77 _private member_ `TArray<TUniquePtr<Frontend::IVertexAnalyzer>> Analyzers;`
- L78 _private member_ `FNodeVertexDataReferenceMap InternalDataReferences;`
- L81 _public prototype_ `FGraphAnalyzer(const FOperatorSettings& InSettings, uint64 InInstanceID, FNodeVertexDataReferenceMap&& InGraphReferences);`
- L82 _public prototype_ `~FGraphAnalyzer() = default;`
- L85 _public prototype_ `void Execute();` — Execute analysis for the current block

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L14 _namespace_ `namespace Metasound`
- L16 _namespace_ `namespace Frontend` (scope `Metasound`)
- L18 _typedef_ `using FNodeVertexDataReferenceMap = TMap<FGuid, FDataReferenceCollection>;` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Analysis/MetasoundFrontendGraphAnalyzerView.h` (Public)


#### class `Metasound::Frontend::FMetasoundGraphAnalyzerView`  
`class FMetasoundGraphAnalyzerView`  
_L23-62_
- L26 _private member_ `TUniquePtr<ISender> ActiveAnalyzerSender;` — Sender in charge of supplying expected vertex analyzers currently being analyzed.
- L29 _private member_ `TSet<FAnalyzerAddress> ActiveAnalyzers;` — Set of active analyzer addresses used for what analyzers should be active on the associated graph instance
- L31 _private prototype_ `const FMetasoundAssetBase& GetMetaSoundAssetChecked() const;`
- L32 _private prototype_ `void SendActiveAnalyzers();`
- L34 _private member_ `uint64 InstanceID = INDEX_NONE;`
- L35 _private member_ `const FMetasoundAssetBase* MetaSoundAsset = nullptr;`
- L37 _private member_ `FOperatorSettings OperatorSettings = { 48000, 100 };`
- L39 _private typedef_ `using FMetasoundGraphAnalyzerOutputKey = TTuple<FGuid , FName >;`
- L40 _private member_ `TMap<FMetasoundGraphAnalyzerOutputKey, TArray<FMetasoundAnalyzerView>> AnalyzerViews;`
- L42 _private prototype_ `FMetasoundGraphAnalyzerView(const FMetasoundGraphAnalyzerView&) = delete;`
- L43 _private prototype_ `FMetasoundGraphAnalyzerView(FMetasoundGraphAnalyzerView&&) = delete;`
- L44 _private prototype_ `FMetasoundGraphAnalyzerView& operator=(const FMetasoundGraphAnalyzerView&) = delete;`
- L45 _private prototype_ `FMetasoundGraphAnalyzerView& operator=(FMetasoundGraphAnalyzerView&&) = delete;`
- L48 _public prototype_ `FMetasoundGraphAnalyzerView() = default;`
- L50 _public prototype_ `FMetasoundGraphAnalyzerView(const FMetasoundAssetBase& InAssetBase, uint64 InInstanceID, const FOperatorSettings& InOperatorSettings);`
- L51 _public prototype_ `~FMetasoundGraphAnalyzerView();`
- L53 _public prototype_ `void AddAnalyzerForAllSupportedOutputs(FName InAnalyzerName, bool bInRequiresConnection = true);`
- L54 _public prototype_ `FGuid AddAnalyzerForSpecifiedOutput(const FGuid& InNodeID, FVertexName InOutputName, FName InAnalyzerName, FName InAnalyzerMemberName);`
- L55 _public prototype_ `void RemoveAnalyzerForAllSupportedOutputs(FName InAnalyzerName);`
- L56 _public prototype_ `void RemoveAnalyzerInstance(FName InAnalyzerName, const FGuid& InAnalyzerInstanceID);`
- L57 _public prototype_ `bool HasAnalyzerInstance(FName InAnalyzerName, const FGuid& InAnalyzerInstanceID) const;`
- L58 _public prototype_ `TArray<FMetasoundAnalyzerView*> GetAnalyzerViews(FName InAnalyzerName);`
- L59 _public prototype_ `TArray<const FMetasoundAnalyzerView*> GetAnalyzerViews(FName InAnalyzerName) const;`
- L60 _public prototype_ `TArray<FMetasoundAnalyzerView*> GetAnalyzerViewsForOutput(const FGuid& InNodeID, FName InOutputName, FName InAnalyzerName);`
- L61 _public prototype_ `TArray<const FMetasoundAnalyzerView*> GetAnalyzerViewsForOutput(const FGuid& InNodeID, FName InOutputName, FName InAnalyzerName) const;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L19 _namespace_ `namespace Metasound`
- L21 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Analysis/MetasoundFrontendVertexAnalyzer.h` (Public)


#### struct `Metasound::Frontend::FAnalyzerOutput`  
`struct FAnalyzerOutput`  
_L21-25_
- desc: Output of analyzer (not to be confused with the node vertex output which an analyzer may be processing).  Used to signify by an analyzer what information is sent to other threads using an analyzer view for logging, displaying, processing, etc. resulting analyzer data.
- L23 _public member_ `FName Name;`
- L24 _public member_ `FName DataType;`

#### struct `Metasound::Frontend::FCreateAnalyzerParams`  
`struct FCreateAnalyzerParams`  
_L28-39_
- desc: Parameters used to generate an analyzer instance
- L31 _public member_ `const FAnalyzerAddress& AnalyzerAddress;` — Address of analyzer
- L34 _public member_ `const FOperatorSettings& OperatorSettings;` — OperatorSettings used for analyzer execution
- L38 _public member_ `const FAnyDataReference& VertexDataReference;` — Data reference to vertex (currently only output vertices support analysis) writing data to be analyzed.

#### class `Metasound::Frontend::IVertexAnalyzer`  
`class IVertexAnalyzer`  
_L43-62_
- desc: Analyzer that watches a data reference associated with a particular node vertex. Currently, only output node vertex analysis is supported.
- L46 _public prototype_ `virtual ~IVertexAnalyzer() = default;`
- L49 _public prototype_ `virtual const FAnalyzerAddress& GetAnalyzerAddress() const = 0;` — Returns analyzer address
- L52 _public prototype_ `virtual FDataReferenceID GetDataReferenceId() const = 0;` — Returns the data reference id for the analyzer's input
- L55 _public prototype_ `virtual void SetDataReference(const FAnyDataReference& NewDataRef) = 0;` — Re-bind the analyzer's input
- L58 _public prototype_ `virtual void Execute() = 0;` — Executes analysis
- L60 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnOutputDataChanged, FName, TSharedPtr<IOutputStorage>);`
- L61 _public member_ `FOnOutputDataChanged OnOutputDataChanged;`

#### class `Metasound::Frontend::IBoundAnalyzerOutput`  
`class IBoundAnalyzerOutput`  
_L67-80_
- desc: Bound output from an analyzer (not to be confused with an output vertex) sent internally using the Transmission System. Each bound output corresponds to a DataChannel with an analyzer view or views potentially receiving analysis results.
- L70 _public prototype_ `virtual ~IBoundAnalyzerOutput() = default;`
- L73 _public prototype_ `virtual FAnyDataReference GetDataReference() const = 0;` — Returns the data reference associated with the analyzer's output
- L76 _public prototype_ `virtual void PushData() = 0;` — Pushes data to the sender to be forwarded to all actively associated analyser views.
- L79 _public prototype_ `virtual TSharedPtr<IOutputStorage> CreateOutputData() const = 0;` — Gets the latest value to pass to IVertexAnalyzer::OnOutputDataChanged

#### class `Metasound::Frontend::TBoundAnalyzerOutput`  
`template<typename DataType> class TBoundAnalyzerOutput final : public IBoundAnalyzerOutput`  
_L84-131_
- inherits: `IBoundAnalyzerOutput`
- desc: Templatized implementation of a bound analyzer output (see IBoundAnalyzerOutput)
- L87 _public function_ `TBoundAnalyzerOutput(const FAnalyzerAddress& InAnalyzerOutputAddress, const FOperatorSettings& InOperatorSettings, TDataReadReference<DataType> InData) : Address(InAnalyzerOutputAddress) , DataRef(InData)`
- L95 _public function_ `virtual ~TBoundAnalyzerOutput() override`
- L109 _public function_ `virtual FAnyDataReference GetDataReference() const override`
- L114 _public function_ `virtual void PushData() override`
- L122 _public function_ `virtual TSharedPtr<IOutputStorage> CreateOutputData() const override`
- L128 _private member_ `FAnalyzerAddress Address;`
- L129 _private member_ `TDataReadReference<DataType> DataRef;`
- L130 _private member_ `TUniquePtr<TSender<DataType>> Sender;`

#### class `Metasound::Frontend::FVertexAnalyzerBase`  
`class FVertexAnalyzerBase : public IVertexAnalyzer`  
_L134-206_
- inherits: `IVertexAnalyzer`
- desc: Base implementation of a vertex analyzer.
- L137 _public function_ `FVertexAnalyzerBase(const FAnalyzerAddress& InAnalyzerAddress, const FAnyDataReference& InDataReference) : AnalyzerAddress(InAnalyzerAddress) , VertexDataReference(InDataReference)`
- L143 _public prototype_ `virtual ~FVertexAnalyzerBase() = default;`
- L145 _public function_ `virtual const FAnalyzerAddress& GetAnalyzerAddress() const override`
- L150 _public function_ `virtual FDataReferenceID GetDataReferenceId() const override final`
- L155 _public function_ `virtual void SetDataReference(const FAnyDataReference& NewDataRef) override final`
- L161 _protected typedef_ `using FBoundOutputDataPtr = TSharedPtr<IBoundAnalyzerOutput>;`
- L166 _protected function_ `void MarkOutputDirty()` — Marks all output channels as dirty, refreshing all bound data. Likely best called after all computation is complete within an execution call, to be implemented by the child class.
- L179 _protected function_ `bool UnbindOutputData(FName InAnalyzerOutputName)` — Unbinds a particular named analyzer output
- L186 _protected function_ `template<typename DataType> void BindOutputData(FName InAnalyzerOutputName, const FOperatorSettings& InOperatorSettings, TDataReadReference<DataType> InData)` — Binds a particular named analyzer output to be updated when MarkOutputDirty is called.
- L197 _protected function_ `template<typename DataType> const DataType& GetVertexData() const` — Returns the most recent vertex data.
- L203 _private member_ `FAnalyzerAddress AnalyzerAddress;`
- L204 _private member_ `TMap<FName, FBoundOutputDataPtr> BoundOutputData;`
- L205 _private member_ `FAnyDataReference VertexDataReference;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Metasound`
- L15 _namespace_ `namespace Frontend` (scope `Metasound`)
- L60 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnOutputDataChanged, FName, TSharedPtr<IOutputStorage>);`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Analysis/MetasoundFrontendVertexAnalyzerAudioBuffer.h` (Public)


#### class `Metasound::Frontend::FVertexAnalyzerAudioBuffer`  
`class FVertexAnalyzerAudioBuffer : public FVertexAnalyzerBase`  
_L16-44_
- inherits: `FVertexAnalyzerBase`
- L19 _public prototype_ `static const FName& GetAnalyzerName();`
- L20 _public prototype_ `static const FName& GetDataType();`
- L37 _public prototype_ `FVertexAnalyzerAudioBuffer(const FCreateAnalyzerParams& InParams);`
- L38 _public prototype_ `virtual ~FVertexAnalyzerAudioBuffer() = default;`
- L40 _public prototype_ `virtual void Execute() override;`
- L43 _private member_ `FAudioBufferWriteRef AudioBuffer;`

#### struct `Metasound::Frontend::FVertexAnalyzerAudioBuffer::FOutputs`  
`struct FOutputs`  
_L22-25_
- L24 _public prototype_ `static const FAnalyzerOutput& GetValue();`

#### class `Metasound::Frontend::FVertexAnalyzerAudioBuffer::FFactory`  
`class FFactory : public TVertexAnalyzerFactory<FVertexAnalyzerAudioBuffer>`  
_L27-35_
- inherits: `TVertexAnalyzerFactory<FVertexAnalyzerAudioBuffer>`
- L30 _public function_ `virtual const TArray<FAnalyzerOutput>& GetAnalyzerOutputs() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L12 _namespace_ `namespace Metasound`
- L14 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Analysis/MetasoundFrontendVertexAnalyzerEnvelopeFollower.h` (Public)


#### class `Metasound::Frontend::FVertexAnalyzerEnvelopeFollower`  
`class FVertexAnalyzerEnvelopeFollower : public FVertexAnalyzerBase`  
_L19-48_
- inherits: `FVertexAnalyzerBase`
- L22 _public prototype_ `static const FName& GetAnalyzerName();`
- L23 _public prototype_ `static const FName& GetDataType();`
- L40 _public prototype_ `FVertexAnalyzerEnvelopeFollower(const FCreateAnalyzerParams& InParams);`
- L41 _public prototype_ `virtual ~FVertexAnalyzerEnvelopeFollower() = default;`
- L43 _public prototype_ `virtual void Execute() override;`
- L46 _private member_ `Audio::FEnvelopeFollower EnvelopeFollower;`
- L47 _private member_ `TDataWriteReference<float> EnvelopeValue;`

#### struct `Metasound::Frontend::FVertexAnalyzerEnvelopeFollower::FOutputs`  
`struct FOutputs`  
_L25-28_
- L27 _public prototype_ `static const FAnalyzerOutput& GetValue();`

#### class `Metasound::Frontend::FVertexAnalyzerEnvelopeFollower::FFactory`  
`class FFactory : public TVertexAnalyzerFactory<FVertexAnalyzerEnvelopeFollower>`  
_L30-38_
- inherits: `TVertexAnalyzerFactory<FVertexAnalyzerEnvelopeFollower>`
- L33 _public function_ `virtual const TArray<FAnalyzerOutput>& GetAnalyzerOutputs() const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L15 _namespace_ `namespace Metasound`
- L17 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Analysis/MetasoundFrontendVertexAnalyzerForwardValue.h` (Public)


#### class `Metasound::Frontend::TVertexAnalyzerForwardValue`  
`template <typename ChildClass, typename DataType> class TVertexAnalyzerForwardValue : public FVertexAnalyzerBase`  
_L24-89_
- inherits: `FVertexAnalyzerBase`
- desc: Templatized implementation of the simplest/cheapest form of an analyzer, which just forwards a given value to an associated view or views. Can be used in conjunction with an additional process, task, etc. handled by a view to avoid further processing/expense within the graph execution thread context.
- L26 _private member_ `DataType LastValue;`
- L27 _private member_ `bool HasExecuted = false;`
- L30 _public function_ `static const FName& GetDataType()`
- L59 _public function_ `TVertexAnalyzerForwardValue(const FCreateAnalyzerParams& InParams) : FVertexAnalyzerBase(InParams.AnalyzerAddress, InParams.VertexDataReference)`
- L66 _public prototype_ `virtual ~TVertexAnalyzerForwardValue() = default;`
- L68 _public function_ `virtual void Execute() override`
- L84 _private function_ `void UpdateValue(const DataType& Value)`

#### struct `Metasound::Frontend::TVertexAnalyzerForwardValue::FOutputs`  
`struct FOutputs`  
_L35-47_
- L37 _public function_ `static const FAnalyzerOutput& GetValue()`

#### class `Metasound::Frontend::TVertexAnalyzerForwardValue::FFactory`  
`class FFactory : public TVertexAnalyzerFactory<ChildClass>`  
_L49-57_
- inherits: `TVertexAnalyzerFactory<ChildClass>`
- L52 _public function_ `virtual const TArray<FAnalyzerOutput>& GetAnalyzerOutputs() const override`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Metasound`
- L16 _namespace_ `namespace Frontend` (scope `Metasound`)
- L40 _function_ `` (scope `Metasound::Frontend::TVertexAnalyzerForwardValue::FOutputs::GetValue`)
- L91 _macro_ `#define METASOUND_DECLARE_FORWARD_VALUE_ANALYZER(ClassType, AnalyzerFName, DataType) \`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Analysis/MetasoundFrontendVertexAnalyzerTriggerDensity.h` (Public)


#### class `Metasound::Frontend::FVertexAnalyzerTriggerDensity`  
`class FVertexAnalyzerTriggerDensity : public FVertexAnalyzerBase`  
_L16-48_
- inherits: `FVertexAnalyzerBase`
- L19 _public prototype_ `static const FName& GetAnalyzerName();`
- L20 _public prototype_ `static const FName& GetDataType();`
- L37 _public prototype_ `FVertexAnalyzerTriggerDensity(const FCreateAnalyzerParams& InParams);`
- L38 _public prototype_ `virtual ~FVertexAnalyzerTriggerDensity();`
- L40 _public prototype_ `virtual void Execute() override;`
- L44 _private member_ `Audio::FEnvelopeFollower EnvelopeFollower;`
- L45 _private member_ `TDataWriteReference<float> EnvelopeValue;`
- L46 _private member_ `int32 NumFramesPerBlock = 0;`
- L47 _private member_ `Audio::FAlignedFloatBuffer ScratchBuffer;`

#### struct `Metasound::Frontend::FVertexAnalyzerTriggerDensity::FOutputs`  
`struct FOutputs`  
_L22-25_
- L24 _public prototype_ `static const FAnalyzerOutput& GetValue();`

#### class `Metasound::Frontend::FVertexAnalyzerTriggerDensity::FFactory`  
`class FFactory : public TVertexAnalyzerFactory<FVertexAnalyzerTriggerDensity>`  
_L27-35_
- inherits: `TVertexAnalyzerFactory<FVertexAnalyzerTriggerDensity>`
- L30 _public function_ `virtual const TArray<FAnalyzerOutput>& GetAnalyzerOutputs() const override`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Metasound`
- L14 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Analysis/MetasoundFrontendVertexAnalyzerTriggerToTime.h` (Public)


#### class `Metasound::Frontend::FVertexAnalyzerTriggerToTime`  
`class FVertexAnalyzerTriggerToTime final : public FVertexAnalyzerBase`  
_L14-42_
- inherits: `FVertexAnalyzerBase`
- L17 _public prototype_ `static const FName& GetAnalyzerName();`
- L18 _public prototype_ `static const FName& GetDataType();`
- L31 _public prototype_ `explicit FVertexAnalyzerTriggerToTime(const FCreateAnalyzerParams& InParams);`
- L32 _public prototype_ `virtual ~FVertexAnalyzerTriggerToTime() override = default;`
- L34 _public prototype_ `virtual void Execute() override;`
- L37 _private member_ `const FSampleRate SampleRate;`
- L38 _private member_ `const int32 FramesPerBlock;`
- L39 _private member_ `const double SecondsPerBlock;`
- L40 _private member_ `FTime BlockStartTime{ 0.0f };`
- L41 _private member_ `TDataWriteReference<FTime> LastTriggerTime;`

#### struct `Metasound::Frontend::FVertexAnalyzerTriggerToTime::FOutputs`  
`struct FOutputs`  
_L20-23_
- L22 _public prototype_ `static const FAnalyzerOutput& GetValue();`

#### class `Metasound::Frontend::FVertexAnalyzerTriggerToTime::FFactory`  
`class FFactory final : public TVertexAnalyzerFactory<FVertexAnalyzerTriggerToTime>`  
_L25-29_
- inherits: `TVertexAnalyzerFactory<FVertexAnalyzerTriggerToTime>`
- L28 _public prototype_ `virtual const TArray<FAnalyzerOutput>& GetAnalyzerOutputs() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L10 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/DocumentTemplates/MetasoundFrontendDocumentTemplate.h` (Public)


#### struct `FMetaSoundFrontendDocumentTemplate`  
`struct FMetaSoundFrontendDocumentTemplate`  
_L34-107_
- reflection: `USTRUCT(BlueprintType, meta = (Hidden))`
- desc: Struct housed on a MetaSoundDocument and used to define procedural behavior applied when making modifications to a MetaSound prior to serialization. Templates enable MetaSounds to be procedurally generated at edit and cook-time to adhere to a specific design or topology anytime a given configuration or its respective properties are changed, enabling faster and more accurate iteration where fully-customized MetaSound edit behavior is not desired.
- L38 _public prototype_ `virtual ~FMetaSoundFrontendDocumentTemplate() = default;`
- L42 _public prototype_ `UE_INTERNAL virtual bool ConfigureDocument(FMetaSoundFrontendDocumentBuilder& OutBuilder);` — Executes procedural configuration of document template. Returns true if template applied to document, false if not (resulting in a follow-up call to reset the document).
- L94 _public prototype_ `virtual EDataValidationResult IsDataValid(const FMetaSoundFrontendDocumentBuilder& Builder, FDataValidationContext& InOutContext) const;`
- L102 _public prototype_ `Metasound::Frontend::FOnConfigPropertyChangedDelegate& GetPropertyChangedDelegate() const;`
- L105 _private member_ `mutable Metasound::Frontend::FOnConfigPropertyChangedDelegate PropertyChangedDelegate;`

#### struct `FMetaSoundFrontendDocumentTemplate::FEditorOptions`  
`struct FEditorOptions`  
_L45-89_
- L88 _public prototype_ `static const FEditorOptions& GetDefaultOptions();` — Default options if none are specified

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L22 _namespace_ `namespace Metasound`
- L22 _namespace_ `namespace Frontend` (scope `Metasound`)
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfigPropertyChangedDelegate, const FPropertyChangedEvent& );`
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfigPropertyChangedDelegate, const FPropertyChangedEvent& );` (scope `Metasound::Frontend`)
- L110 _namespace_ `namespace Metasound`
- L110 _namespace_ `namespace Frontend` (scope `Metasound`)
- L112 _typedef_ `using FMetaSoundTemplate = FMetaSoundFrontendDocumentTemplate;` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/DocumentTemplates/MetasoundFrontendDocumentVertexTemplate.h` (Public)


#### struct `FMetaSoundFrontendDocumentTemplateVertexMetadata`  
`struct FMetaSoundFrontendDocumentTemplateVertexMetadata`  
_L17-42_
- reflection: `USTRUCT(BlueprintType)`
- desc: Vertex metadata displayed on MetaSound inputs & outputs pertaining to a given configuration.
- L22 _public prototype_ `FMetaSoundFrontendDocumentTemplateVertexMetadata() = default;`
- L24 _public prototype_ `virtual ~FMetaSoundFrontendDocumentTemplateVertexMetadata() = default;`
- L29 _public function_ `virtual bool IsDefaultEditable() const` — If true, default values are directly editable if the parent configuration lists member editing as enabled.
- L33 _public function_ `virtual void OnDefaultReset(const FMetaSoundFrontendDocumentBuilder& Builder, const FMetasoundFrontendClassVertex& InVertex)`
- L36 _public function_ `virtual void OnDefaultUpdated(const FMetaSoundFrontendDocumentBuilder& Builder, const FMetasoundFrontendClassVertex& InVertex)`
- L40 _public function_ `virtual void OnPropertyChanged(const FPropertyChangedEvent& InEvent, FMetaSoundFrontendDocumentBuilder& OutBuilder, const FMetasoundFrontendClassVertex& InVertex)`

#### struct `FMetaSoundFrontendDocumentVertexTemplate`  
`struct FMetaSoundFrontendDocumentVertexTemplate : public FMetaSoundFrontendDocumentTemplate`  
_L46-127_
- reflection: `USTRUCT(BlueprintType, meta = (Hidden))`
- inherits: `FMetaSoundFrontendDocumentTemplate`
- desc: Template of a MetaSound that stores vertex (input or output) Metadata to display alongside standard properties in MetaSound vertex editors.
- L50 _public prototype_ `virtual ~FMetaSoundFrontendDocumentVertexTemplate() = default;`
- L54 _public prototype_ `UE_INTERNAL FMetaSoundFrontendDocumentTemplateVertexMetadata* AddVertexMetadata(const FMetaSoundFrontendDocumentBuilder& Builder, const FMetasoundFrontendClassVertex& InVertex);` — Creates and stores new VertexMetadata. Overwrites if metadata already exists with default constructed VertexMetadata if template supports Metadata.
- L60 _public function_ `template <typename TTemplateVertexMetadata> UE_INTERNAL TTemplateVertexMetadata* AddVertexMetadata(const FMetaSoundFrontendDocumentBuilder& Builder, const FMetasoundFrontendClassVertex& InVertex)` — Creates and stores new VertexMetadata with the provided type and name, asserting that the type created by the overloaded template matches the template type. Overwrites if metadata already exists with default constructed VertexMetadata. Returns null if template does not support Metadata.
- L80 _public prototype_ `bool ContainsVertexMetadata(const FGuid& NodeID) const;` — Returns whether or not there is existing Metadata with the given NodeID.
- L84 _public function_ `template <typename TTemplateVertexMetadata = FMetaSoundFrontendDocumentTemplateVertexMetadata> UE_INTERNAL TTemplateVertexMetadata* FindVertexMetadata(const FGuid& NodeID)` — Helper function to returns VertexMetadata with the provided class type and name and cast to underlying config type.
- L96 _public function_ `template <typename TTemplateVertexMetadata = FMetaSoundFrontendDocumentTemplateVertexMetadata> const TTemplateVertexMetadata* FindConstVertexMetadata(const FGuid& NodeID) const` — Helper function to returns VertexMetadata with the provided class type and name and cast to underlying config type.
- L106 _public function_ `const UScriptStruct* GetVertexMetadataStruct(const FGuid& NodeID) const`
- L126 _private member_ `TMap<FGuid, TInstancedStruct<FMetaSoundFrontendDocumentTemplateVertexMetadata>> VertexMetadata;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L130 _namespace_ `namespace Metasound`
- L130 _namespace_ `namespace Frontend` (scope `Metasound`)
- L132 _typedef_ `using FDocumentVertexTemplate = FMetaSoundFrontendDocumentVertexTemplate;` (scope `Metasound::Frontend`)
- L133 _typedef_ `using FTemplateVertexMetadata = FMetaSoundFrontendDocumentTemplateVertexMetadata;` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/DocumentTemplates/MetasoundFrontendPresetTemplate.h` (Public)


#### struct `FMetaSoundFrontendPresetTemplate`  
`struct FMetaSoundFrontendPresetTemplate final : public FMetaSoundFrontendDocumentVertexTemplate`  
_L19-49_
- reflection: `USTRUCT(BlueprintType, DisplayName = "Preset")`
- inherits: `FMetaSoundFrontendDocumentVertexTemplate`
- L23 _public prototype_ `virtual ~FMetaSoundFrontendPresetTemplate() = default;`
- L26 _public prototype_ `UE_INTERNAL virtual bool ConfigureDocument(FMetaSoundFrontendDocumentBuilder& OutBuilder) override;`
- L44 _protected prototype_ `UE_INTERNAL virtual TInstancedStruct<FMetaSoundFrontendDocumentTemplateVertexMetadata> ConstructVertexMetadata(const FMetaSoundFrontendDocumentBuilder& Builder, const FMetasoundFrontendClassVertex& InVertex) const override;`
- L48 _public member_ `TScriptInterface<IMetaSoundDocumentInterface> Parent;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Preset Options")`

#### struct `FMetaSoundFrontendPresetVertexMetadata`  
`struct FMetaSoundFrontendPresetVertexMetadata : public FMetaSoundFrontendDocumentTemplateVertexMetadata`  
_L52-69_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMetaSoundFrontendDocumentTemplateVertexMetadata`
- L56 _public prototype_ `virtual ~FMetaSoundFrontendPresetVertexMetadata() = default;`
- L59 _public prototype_ `virtual bool IsDefaultEditable() const override;`
- L62 _public prototype_ `virtual void OnDefaultReset(const FMetaSoundFrontendDocumentBuilder& Builder, const FMetasoundFrontendClassVertex& InVertex) override;`
- L63 _public prototype_ `virtual void OnDefaultUpdated(const FMetaSoundFrontendDocumentBuilder& Builder, const FMetasoundFrontendClassVertex& InVertex) override;`
- L68 _public member_ `bool bOverrideInheritedDefault = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PresetOptions)` — Enables overriding the input's inherited default value otherwise provided by the parent graph. Setting to true disables the configuration utilizing the input's default value if updated on the parent asset.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L71 _namespace_ `namespace Metasound`
- L71 _namespace_ `namespace Frontend` (scope `Metasound`)
- L73 _typedef_ `using FPresetTemplate = FMetaSoundFrontendPresetTemplate;` (scope `Metasound::Frontend`)
- L74 _typedef_ `using FPresetVertexMetadata = FMetaSoundFrontendPresetVertexMetadata;` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Interfaces/MetasoundFrontendInterface.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Metasound`
- L9 _namespace_ `namespace Frontend` (scope `Metasound`)
- L11 _prototype_ `bool IsSubsetOfInterface(const FMetasoundFrontendInterface& InSubsetInterface, const FMetasoundFrontendInterface& InSupersetInterface);` (scope `Metasound::Frontend`)
- L13 _prototype_ `bool IsSubsetOfClassInterface(const FMetasoundFrontendInterface& InSubsetInterface, const FMetasoundFrontendClassInterface& InSupersetClassInterface);` (scope `Metasound::Frontend`)
- L16 _prototype_ `bool IsSubsetOfClass(const FMetasoundFrontendInterface& InSubsetInterface, const FMetasoundFrontendClass& InSupersetClass);` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.6, "Use IsSubsetOfClassInterface instead")`
- L19 _prototype_ `bool IsEquivalentInterface(const FMetasoundFrontendInterface& InInputInterface, const FMetasoundFrontendInterface& InTargetInterface);` (scope `Metasound::Frontend`)
- L21 _prototype_ `bool IsEqualInterface(const FMetasoundFrontendInterface& InInputInterface, const FMetasoundFrontendInterface& InTargetInterface);` (scope `Metasound::Frontend`)
- L24 _prototype_ `int32 InputOutputDifferenceCount(const FMetasoundFrontendClass& InClass, const FMetasoundFrontendInterface& InInterface);` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.6, "Use InputOutputDifferenceCount which accepts a FMetasoundFrontendClassInterface instead")`
- L26 _prototype_ `int32 InputOutputDifferenceCount(const FMetasoundFrontendClassInterface& InClass, const FMetasoundFrontendInterface& InInterface);` (scope `Metasound::Frontend`)
- L28 _prototype_ `int32 InputOutputDifferenceCount(const FMetasoundFrontendInterface& InInterfaceA, const FMetasoundFrontendInterface& InInterfaceB);` (scope `Metasound::Frontend`)
- L31 _prototype_ `bool DeclaredInterfaceVersionsMatch(const FMetasoundFrontendDocument& InDocumentA, const FMetasoundFrontendDocument& InDocumentB);` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.6, "All interface functionality is in the MetaSoundFrontendDocumentBuilder API")`
- L34 _prototype_ `const FMetasoundFrontendInterface* FindMostSimilarInterfaceSupportingEnvironment(const FMetasoundFrontendGraphClass& InRootGraph, const TArray<FMetasoundFrontendClass>& InDependencies, const TArray<FMetasoundFrontendGraphClass>& InSubgraphs, const TArray<FMetasoundFrontendInterface>& InCandidateInterfaces);` (scope `Metasound::Frontend`)
- L36 _prototype_ `const FMetasoundFrontendInterface* FindMostSimilarInterfaceSupportingEnvironment(const FMetasoundFrontendDocument& InDocument, const TArray<FMetasoundFrontendInterface>& InCandidateInterfaces);` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Interfaces/MetasoundFrontendInterfaceBindingRegistry.h` (Public)


#### class `Metasound::Frontend::FInterfaceBindingRegistryEntry`  
`class FInterfaceBindingRegistryEntry`  
_L13-32_
- L15 _private member_ `const FMetasoundFrontendVersion OutputInterfaceVersion;`
- L16 _private member_ `const TArray<FMetasoundFrontendInterfaceVertexBinding> VertexBindings;`
- L17 _private member_ `const int32 BindingPriority = 0;`
- L20 _public prototype_ `FInterfaceBindingRegistryEntry(const FMetasoundFrontendInterfaceBinding& InBinding);`
- L21 _public prototype_ `virtual ~FInterfaceBindingRegistryEntry() = default;`
- L24 _public prototype_ `const FMetasoundFrontendVersion& GetOutputInterfaceVersion() const;` — Returns the output interface version corresponding with the given binding entry.
- L27 _public prototype_ `const TArray<FMetasoundFrontendInterfaceVertexBinding>& GetVertexBindings() const;` — Returns array of FName pairs that describe how the output and input interfaces are to bind
- L31 _public prototype_ `int32 GetBindingPriority() const;` — If two binding registry entries match output & input interfaces versions, integer corresponds to which binding takes priority for a given bind operation. Lower numbers are higher priority.

#### class `Metasound::Frontend::IInterfaceBindingRegistry`  
`class IInterfaceBindingRegistry`  
_L39-56_
- desc: Registry of interface bindings, a way to characterize how MetaSound node instances that implement a give set of interfaces "bind" to other nodes that implement a second set set of interfaces. Binding is an abstracted way to connect two nodes together using multiple edges as defined through this registry. Accessing this registry is currently not thread safe and only expected to be occur on the Game Thread.
- L43 _public prototype_ `static IInterfaceBindingRegistry& Get();` — Returns binding registry singleton.
- L46 _public prototype_ `virtual bool FindInterfaceBindingEntries(const FMetasoundFrontendVersion& InInputInterfaceVersion, TArray<const FInterfaceBindingRegistryEntry*>& OutEntries) const = 0;` — Find all bindings associated with the given input interface version. Returns true if interface binding is found, false if not.
- L49 _public prototype_ `virtual void RegisterInterfaceBinding(const FMetasoundFrontendVersion& InInputInterfaceVersion, TUniquePtr<FInterfaceBindingRegistryEntry>&& InEntry) = 0;` — Add interface bindings to the registry.
- L52 _public prototype_ `virtual bool UnregisterInterfaceBinding(const FMetasoundFrontendVersion& InInputInterfaceVersion, const FMetasoundFrontendVersion& InOutputInterfaceVersion) = 0;` — Removes an interface binding from registry.
- L55 _public prototype_ `virtual bool UnregisterAllInterfaceBindings(const FMetasoundFrontendVersion& InInputInterfaceVersion) = 0;` — Removes all interface bindings associated with the given input interface if found. Returns true if found and removed, false if not found.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L11 _namespace_ `namespace Metasound`
- L11 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Interfaces/MetasoundFrontendInterfaceRegistry.h` (Public)


#### class `Metasound::Frontend::IInterfaceRegistryEntry`  
`class IInterfaceRegistryEntry`  
_L31-54_
- L34 _public prototype_ `virtual ~IInterfaceRegistryEntry() = default;`
- L37 _public prototype_ `virtual const FMetasoundFrontendInterface& GetInterface() const = 0;` — MetaSound Interface definition
- L40 _public function_ `virtual bool IsDeprecated() const` — Whether or not entry is deprecated or not. If false, entry is checked for validity on registration in editor builds.
- L43 _public prototype_ `virtual FName GetRouterName() const = 0;` — Name of routing system used to update interface inputs (ex. ParameterInterface or DataReference).
- L46 _public function_ `virtual bool UpdateRootGraphInterface(FDocumentHandle InDocument) const` — `UE_DEPRECATED(5.7, "Transform accessor must be thread safe, and thus a shared pointer is passed via 'GetUpdateTransform'")`
- L49 _public function_ `virtual bool UpdateRootGraphInterface(FMetaSoundFrontendDocumentBuilder& InDocumentBuilder) const` — `UE_DEPRECATED(5.8, "Transform accessor must be thread safe, and thus a shared pointer is passed via 'GetUpdateTransform'")`
- L53 _public prototype_ `virtual TSharedRef<IBuilderVersionTransform> GetUpdateTransform() const = 0;` — Returns transform indicating how to update a given document if versioning is required to this interface from a deprecated version. If not specified, update simply adds the given interface as a new interface to the given builder's document.

#### class `Metasound::Frontend::FInterfaceRegistryTransaction`  
`class FInterfaceRegistryTransaction`  
_L56-86_
- L59 _public typedef_ `using FTimeType = uint64;`
- L70 _public prototype_ `FInterfaceRegistryTransaction(ETransactionType InType, const FInterfaceRegistryKey& InKey, const FMetasoundFrontendVersion& InInterfaceVersion, FTimeType InTimestamp);` — `UE_DEPRECATED(5.8, "Interface keys are deprecated: Frontend Version is now directly used as hashable interface identifier")`
- L72 _public prototype_ `FInterfaceRegistryTransaction(ETransactionType InType, const FMetasoundFrontendVersion& InInterfaceVersion, FTimeType InTimestamp);`
- L74 _public prototype_ `ETransactionType GetTransactionType() const;`
- L75 _public prototype_ `const FMetasoundFrontendVersion& GetInterfaceVersion() const;`
- L78 _public prototype_ `const FInterfaceRegistryKey& GetInterfaceRegistryKey() const;` — `UE_DEPRECATED(5.8, "Interface keys are deprecated: Frontend Version is now directly used as hashable interface identifier")`
- L80 _public prototype_ `FTimeType GetTimestamp() const;`
- L83 _private member_ `ETransactionType Type;`
- L84 _private member_ `FMetasoundFrontendVersion InterfaceVersion;`
- L85 _private member_ `FTimeType Timestamp;`

#### enum `Metasound::Frontend::FInterfaceRegistryTransaction::ETransactionType`  
`enum class ETransactionType : uint8`  
_L62-67_
- desc: Describes the type of transaction.
- L64 _public enumerator_ `InterfaceRegistration` — Something was added to the registry.
- L65 _public enumerator_ `InterfaceUnregistration` — Something was removed from the registry.
- L66 _public enumerator_ `Invalid`

#### class `Metasound::Frontend::IInterfaceRegistry`  
`class IInterfaceRegistry`  
_L88-118_
- L91 _public prototype_ `static IInterfaceRegistry& Get();`
- L93 _public prototype_ `virtual ~IInterfaceRegistry() = default;`
- L96 _public prototype_ `virtual bool RegisterInterface(TUniquePtr<IInterfaceRegistryEntry>&& InEntry) = 0;` — Register an interface
- L98 _public prototype_ `virtual bool ContainsInput(const FMetasoundFrontendVersion& InVersion, const FMetasoundFrontendVertex& InInput) const = 0;`
- L100 _public prototype_ `virtual bool ContainsInterface(const FMetasoundFrontendVersion& InVersion) const = 0;`
- L102 _public prototype_ `virtual bool ContainsOutput(const FMetasoundFrontendVersion& InVersion, const FMetasoundFrontendVertex& InOutput) const = 0;`
- L105 _public function_ `virtual const IInterfaceRegistryEntry* FindInterfaceRegistryEntry(const FInterfaceRegistryKey& InKey) const` — `UE_DEPRECATED(5.8, "Interface keys are deprecated: Frontend Version is now directly used as hashable interface identifier. In addition, direct access to entry is not thread safe, use FindInterface call instead.")`
- L108 _public function_ `virtual bool FindInterface(const FInterfaceRegistryKey& InKey, FMetasoundFrontendInterface& OutInterface) const` — `UE_DEPRECATED(5.8, "Interface keys are deprecated: Frontend Version is now directly used as hashable interface identifier")`
- L111 _public prototype_ `virtual bool FindInterface(const FMetasoundFrontendVersion& InVersion, FMetasoundFrontendInterface& OutInterface) const = 0;` — Find an interface with the given version. Returns true if interface is found, false if not.
- L114 _public prototype_ `virtual bool FindInterfaceRouter(const FMetasoundFrontendVersion& InVersion, FName& OutRouter) const = 0;` — Returns the name of the router for the given interface.
- L117 _public prototype_ `virtual TSharedPtr<IBuilderVersionTransform> FindInterfaceUpdateTransform(const FMetasoundFrontendVersion& InVersion) const = 0;` — Find the interface update transform associated with the given version if found.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L13 _namespace_ `namespace Metasound`
- L13 _namespace_ `namespace Frontend` (scope `Metasound`)
- L19 _typedef_ `using FInterfaceRegistryKey = FString;` (scope `Metasound::Frontend`) — Interface keys are actively being deprecated: Frontend Version is now directly used as hashable interface identifier")
- L20 _typedef_ `using FRegistryTransactionID = int32;` (scope `Metasound::Frontend`)
- L23 _prototype_ `bool IsValidInterfaceRegistryKey(const FInterfaceRegistryKey& InKey);` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.8, "Interface keys are deprecated: Frontend Version is now directly used as hashable interface identifier")`
- L26 _prototype_ `FInterfaceRegistryKey GetInterfaceRegistryKey(const FMetasoundFrontendVersion& InInterfaceVersion);` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.8, "Interface keys are deprecated: Frontend Version is now directly used as hashable interface identifier")`
- L29 _prototype_ `FInterfaceRegistryKey GetInterfaceRegistryKey(const FMetasoundFrontendInterface& InInterface);` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.8, "Interface keys are deprecated: Frontend Version is now directly used as hashable interface identifier")`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Interfaces/MetasoundFrontendSourceInterface.h` (Public)


#### class `Metasound::Frontend::SourceInterface::FUpdateInterface`  
`class FUpdateInterface : public Frontend::IDocumentTransform`  
_L92-96_
- inherits: `Frontend::IDocumentTransform`
- L95 _public prototype_ `virtual bool Transform(Frontend::FDocumentHandle InDocument) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L15 _namespace_ `namespace Metasound`
- L17 _namespace_ `namespace Frontend` (scope `Metasound`)
- L19 _namespace_ `namespace SourceOneShotInterface` (scope `Metasound::Frontend`)
- L21 _namespace_ `namespace Outputs` (scope `Metasound::Frontend::SourceOneShotInterface`)
- L23 _externvar_ `const extern FName OnFinished;` (scope `Metasound::Frontend::SourceOneShotInterface::Outputs`)
- L26 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Frontend::SourceOneShotInterface`)
- L28 _prototype_ `Audio::FParameterInterfacePtr CreateInterface(const UClass& InClass);` (scope `Metasound::Frontend::SourceOneShotInterface`)
- L31 _namespace_ `namespace SourceStartTimeInterface` (scope `Metasound::Frontend`)
- L33 _namespace_ `namespace Inputs` (scope `Metasound::Frontend::SourceStartTimeInterface`)
- L35 _externvar_ `const extern FName StartTime;` (scope `Metasound::Frontend::SourceStartTimeInterface::Inputs`)
- L38 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Frontend::SourceStartTimeInterface`)
- L40 _prototype_ `Audio::FParameterInterfacePtr CreateInterface(const UClass& InClass);` (scope `Metasound::Frontend::SourceStartTimeInterface`)
- L43 _namespace_ `namespace SourceInterfaceV1_0` (scope `Metasound::Frontend`)
- L45 _namespace_ `namespace Inputs` (scope `Metasound::Frontend::SourceInterfaceV1_0`)
- L47 _externvar_ `const extern FName OnPlay;` (scope `Metasound::Frontend::SourceInterfaceV1_0::Inputs`)
- L50 _namespace_ `namespace Outputs` (scope `Metasound::Frontend::SourceInterfaceV1_0`)
- L52 _externvar_ `const extern FName OnFinished;` (scope `Metasound::Frontend::SourceInterfaceV1_0::Outputs`)
- L55 _namespace_ `namespace Environment` (scope `Metasound::Frontend::SourceInterfaceV1_0`)
- L57 _externvar_ `const extern FName DeviceID;` (scope `Metasound::Frontend::SourceInterfaceV1_0::Environment`)
- L58 _externvar_ `const extern FName GraphName;` (scope `Metasound::Frontend::SourceInterfaceV1_0::Environment`)
- L59 _externvar_ `const extern FName IsPreview;` (scope `Metasound::Frontend::SourceInterfaceV1_0::Environment`)
- L60 _externvar_ `const extern FName SoundUniqueID;` (scope `Metasound::Frontend::SourceInterfaceV1_0::Environment`)
- L61 _externvar_ `const extern FName TransmitterID;` (scope `Metasound::Frontend::SourceInterfaceV1_0::Environment`)
- L64 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Frontend::SourceInterfaceV1_0`)
- L66 _prototype_ `Audio::FParameterInterfacePtr CreateInterface(const UClass& InClass);` (scope `Metasound::Frontend::SourceInterfaceV1_0`)
- L69 _namespace_ `namespace SourceInterface` (scope `Metasound::Frontend`)
- L71 _namespace_ `namespace Inputs` (scope `Metasound::Frontend::SourceInterface`)
- L73 _externvar_ `const extern FName OnPlay;` (scope `Metasound::Frontend::SourceInterface::Inputs`)
- L76 _namespace_ `namespace Environment` (scope `Metasound::Frontend::SourceInterface`)
- L78 _externvar_ `const extern FName DeviceID;` (scope `Metasound::Frontend::SourceInterface::Environment`)
- L79 _externvar_ `const extern FName GraphName;` (scope `Metasound::Frontend::SourceInterface::Environment`)
- L80 _externvar_ `const extern FName IsPreview;` (scope `Metasound::Frontend::SourceInterface::Environment`)
- L81 _externvar_ `const extern FName SoundUniqueID;` (scope `Metasound::Frontend::SourceInterface::Environment`)
- L82 _externvar_ `const extern FName TransmitterID;` (scope `Metasound::Frontend::SourceInterface::Environment`)
- L83 _externvar_ `const extern FName AudioMixerNumOutputFrames;` (scope `Metasound::Frontend::SourceInterface::Environment`)
- L84 _externvar_ `const extern FName AudioMixerSampleRate;` (scope `Metasound::Frontend::SourceInterface::Environment`)
- L85 _externvar_ `const extern FName SourceFormatName;` (scope `Metasound::Frontend::SourceInterface::Environment`)
- L88 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Frontend::SourceInterface`)
- L90 _prototype_ `Audio::FParameterInterfacePtr CreateInterface(const UClass& InClass);` (scope `Metasound::Frontend::SourceInterface`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundAccessPtr.h` (Public)


#### struct `Metasound::Frontend::FAccessToken`  
`struct FAccessToken`  
_L29-29_
- desc: The access token mirrors the lifespan of a object in a non-intrusive manner. A TAccessPtr<> can be created to reference an object, but use an access token to determine whether the referenced object is accessible. When the access token is destroyed, the access pointer becomes invalid.

#### class `Metasound::Frontend::TAccessPtr`  
`template<typename Type> class TAccessPtr`  
_L50-185_
- desc: TAccessPtr TAccessPtr is used to determine whether an object has been destructed or not. It is useful when an object cannot be wrapped in a TSharedPtr. A TAccessPtr is functionally similar to a TWeakPtr, but it cannot pin the object. In order to determine whether an object as accessible, the TAccessPtr executes a TFunctions<> which returns object. If a nullptr is returned, then the object is not accessible. Object pointers  held within a TAccessPtr must only be accessed on the thread where the objects gets destructed to avoid having the object destructed while in use. If the TAccessPtr's underlying object is accessed when the pointer is invalid, a fallback object will be returned. @tparam Type - The type of object to track.
- L56 _public typedef_ `using FTokenType = FAccessToken;`
- L57 _public typedef_ `using ObjectType = Type;`
- L59 _public member_ `static Type FallbackObject;`
- L64 _public function_ `Type* Get() const` — Returns a pointer to the accessible object. If the object is inaccessible, a nullptr is returned.
- L82 _public function_ `template<typename AccessPtrType, typename FunctionType> AccessPtrType GetMemberAccessPtr(FunctionType InGetMember) const` — Returns an access pointer to a member of the wrapped object. @tparam AccessPtrType - The access pointer type to return. @tparam FunctionType - A type which is callable accepts a reference to the wrapped object and returns a pointer to the member. @param InGetMember - A FunctionType accepts a reference to the wrapped object and returns a pointer to the member.
- L98 _public function_ `TAccessPtr() : GetObject([]() { return static_cast<Type*>(nullptr); })`
- L99 _public function_ `: GetObject([]() { return static_cast<Type*>(nullptr); })`
- L107 _public function_ `TAccessPtr(TWeakPtr<FTokenType> AccessToken, Type& InRef)` — Creates a access pointer using an access token.
- L128 _public function_ `template<typename OtherType> TAccessPtr(const TAccessPtr<OtherType>& InOther, EConstCast InTag)` — Creates an access pointer from another using a const casts.
- L144 _public function_ `TAccessPtr(const TAccessPtr<OtherType>& InOther, EDerivedCopy InTag=EDerivedCopy::Tag)`
- L155 _public prototype_ `TAccessPtr(const TAccessPtr<Type>& InOther) = default;`
- L156 _public prototype_ `TAccessPtr<Type>& operator=(const TAccessPtr<Type>& InOther) = default;`
- L158 _public prototype_ `TAccessPtr(TAccessPtr<Type>&& InOther) = default;`
- L159 _public prototype_ `TAccessPtr& operator=(TAccessPtr<Type>&& InOther) = default;`
- L173 _protected member_ `mutable Type* CachedObjectPtr = nullptr;`
- L175 _protected member_ `TFunction<Type*()> GetObject;`
- L177 _protected function_ `TAccessPtr(TFunction<Type*()> InGetObject) : GetObject(InGetObject)`

#### enum `Metasound::Frontend::TAccessPtr::EConstCast`  
`enum class EConstCast`  
_L52-52_
- L52 _public enumerator_ `enum class EConstCast { Tag }; enum class EDerivedCopy { Tag }; public: using FTokenType = FAccessToken; using ObjectType = Type; static Type FallbackObject;`

#### enum `Metasound::Frontend::TAccessPtr::EDerivedCopy`  
`enum class EDerivedCopy`  
_L53-53_
- L53 _public enumerator_ `enum class EDerivedCopy { Tag }; public: using FTokenType = FAccessToken; using ObjectType = Type; static Type FallbackObject;`

#### class `Metasound::Frontend::FAccessPoint`  
`class FAccessPoint`  
_L194-224_
- desc: FAccessPoint acts as a lifecycle tracker for the TAccessPtrs it creates. When this object is destructed, all associated TAccessPtrs will become invalid.
- L197 _public typedef_ `using FTokenType = FAccessToken;`
- L199 _public function_ `FAccessPoint()`
- L204 _public function_ `FAccessPoint(const FAccessPoint&)`
- L211 _public function_ `FAccessPoint& operator=(const FAccessPoint&)` — Do not copy token from other access point on assignment
- L220 _private prototype_ `FAccessPoint(FAccessPoint&&) = delete;`
- L221 _private prototype_ `FAccessPoint& operator=(FAccessPoint&&) = delete;`
- L223 _private member_ `TSharedPtr<FTokenType> Token;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define METASOUND_FRONTEND_ACCESSPTR_DEBUG_INFO 1`
- L15 _macro_ `#define METASOUND_FRONTEND_ACCESSPTR_DEBUG_INFO 0`
- L18 _namespace_ `namespace Metasound`
- L20 _namespace_ `namespace Frontend` (scope `Metasound`)
- L84 _typedef_ `using MemberType = typename AccessPtrType::ObjectType;` (scope `Metasound::Frontend::TAccessPtr::GetMemberAccessPtr`)
- L87 _function_ `` (scope `Metasound::Frontend::TAccessPtr::GetMemberAccessPtr`)
- L112 _function_ `` (scope `Metasound::Frontend::TAccessPtr::TAccessPtr`)
- L188 _member_ `template<typename Type> Type TAccessPtr<Type>::FallbackObject = Type();` (scope `Metasound::Frontend::TAccessPtr<Type>`)
- L227 _function_ `template<typename AccessPtrType, typename Type> AccessPtrType MakeAccessPtr(const FAccessPoint& InAccessPoint, Type& InRef)` (scope `Metasound::Frontend`)
- L233 _function_ `template<typename ToAccessPtrType, typename FromAccessPtrType> ToAccessPtrType ConstCastAccessPtr(const FromAccessPtrType& InAccessPtr)` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundArrayNodes.h` (Public)


#### struct `Metasound::MetasoundArrayNodesPrivate::TArrayElementType`  
`template<typename ArrayType> struct TArrayElementType`  
_L55-58_
- desc: Retrieve the ElementType from an ArrayType
- L64 _public typedef_ `using Type = ElementType;`

#### struct `Metasound::MetasoundArrayNodesPrivate::TArrayElementType`  
`template<typename ElementType> struct TArrayElementType<TArray<ElementType>>`  
_L62-65_
- desc: ElementType specialization for TArray types.
- L64 _public typedef_ `using Type = ElementType;`

#### class `Metasound::TArrayNumOperator`  
`template<typename ArrayType> class TArrayNumOperator : public TExecutableOperator<TArrayNumOperator<ArrayType>>`  
_L97-161_
- inherits: `TExecutableOperator<TArrayNumOperator<ArrayType>>`
- desc: TArrayNumOperator gets the number of elements in an Array. The operator uses the FNodeFacade and defines the vertex, metadata and vertex interface statically on the operator class.
- L100 _public typedef_ `using FArrayDataReadReference = TDataReadReference<ArrayType>;`
- L102 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L111 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L124 _public function_ `TArrayNumOperator(FArrayDataReadReference InArray) : Array(InArray) , Num(TDataWriteReference<int32>::CreateNew())`
- L132 _public prototype_ `virtual ~TArrayNumOperator() = default;`
- L134 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L140 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData) override`
- L147 _public function_ `void Execute()`
- L152 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L159 _private member_ `FArrayDataReadReference Array;`
- L160 _private member_ `TDataWriteReference<int32> Num;`

#### class `Metasound::TArrayGetOperator`  
`template<typename ArrayType> class TArrayGetOperator : public TExecutableOperator<TArrayGetOperator<ArrayType>>`  
_L171-318_
- inherits: `TExecutableOperator<TArrayGetOperator<ArrayType>>`
- desc: TArrayGetOperator copies a value from the array to the output when a trigger occurs. Initially, the output value is default constructed and will remain that way until until a trigger is encountered.
- L174 _public typedef_ `using FArrayDataReadReference = TDataReadReference<ArrayType>;`
- L175 _public typedef_ `using ElementType = typename MetasoundArrayNodesPrivate::TArrayElementType<ArrayType>::Type;`
- L178 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L197 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L235 _public function_ `TArrayGetOperator(const FOperatorSettings& InSettings, FInitParams&& InParams) : Trigger(InParams.Trigger) , Array(InParams.Array) , Index(InParams.Index) , Value(TDataWriteReferenceFactory<ElementType>::CreateExplicitArgs(InSettings)) #if WITH_METASOUND_DEBUG_ENVIRONMENT , GraphName(InParams.GraphName) #endif`
- L253 _public prototype_ `virtual ~TArrayGetOperator() = default;`
- L255 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L264 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData) override`
- L271 _public function_ `void Execute()`
- L292 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L309 _private member_ `TDataReadReference<FTrigger> Trigger;`
- L310 _private member_ `FArrayDataReadReference Array;`
- L311 _private member_ `TDataReadReference<int32> Index;`
- L312 _private member_ `TDataWriteReference<ElementType> Value;`
- L315 _private member_ `FString GraphName;`

#### struct `Metasound::TArrayGetOperator::FInitParams`  
`struct FInitParams`  
_L187-195_
- L189 _public member_ `TDataReadReference<FTrigger> Trigger;`
- L190 _public member_ `FArrayDataReadReference Array;`
- L191 _public member_ `TDataReadReference<int32> Index;`
- L193 _public member_ `FString GraphName;`

#### class `Metasound::TArraySetOperator`  
`template<typename ArrayType> class TArraySetOperator : public TExecutableOperator<TArraySetOperator<ArrayType>>`  
_L325-461_
- inherits: `TExecutableOperator<TArraySetOperator<ArrayType>>`
- desc: TArraySetOperator sets an element in an array to a specific value.
- L328 _public typedef_ `using FArrayDataReadReference = TDataReadReference<ArrayType>;`
- L329 _public typedef_ `using FArrayDataWriteReference = TDataWriteReference<ArrayType>;`
- L330 _public typedef_ `using ElementType = typename MetasoundArrayNodesPrivate::TArrayElementType<ArrayType>::Type;`
- L332 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L353 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L391 _public function_ `TArraySetOperator(const FOperatorSettings& InSettings, FInitParams&& InParams) : OperatorSettings(InSettings) , Trigger(InParams.Trigger) , InitArray(InParams.InitArray) , Array(InParams.Array) , Index(InParams.Index) , Value(InParams.Value) #if WITH_METASOUND_DEBUG_ENVIRONMENT , GraphName(InParams.GraphName) #endif`
- L404 _public prototype_ `virtual ~TArraySetOperator() = default;`
- L406 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L416 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData) override`
- L423 _public function_ `void Execute()`
- L443 _public function_ `void Reset(const IOperator::FResetParams& Inparams)`
- L449 _private member_ `FOperatorSettings OperatorSettings;`
- L451 _private member_ `TDataReadReference<FTrigger> Trigger;`
- L452 _private member_ `FArrayDataReadReference InitArray;`
- L453 _private member_ `FArrayDataWriteReference Array;`
- L454 _private member_ `TDataReadReference<int32> Index;`
- L455 _private member_ `TDataReadReference<ElementType> Value;`
- L458 _private member_ `FString GraphName;`

#### struct `Metasound::TArraySetOperator::FInitParams`  
`struct FInitParams`  
_L341-351_
- L343 _public member_ `TDataReadReference<FTrigger> Trigger;`
- L344 _public member_ `FArrayDataReadReference InitArray;`
- L345 _public member_ `FArrayDataWriteReference Array;`
- L346 _public member_ `TDataReadReference<int32> Index;`
- L347 _public member_ `TDataReadReference<ElementType> Value;`
- L349 _public member_ `FString GraphName;`

#### class `Metasound::TArrayConcatOperator`  
`template<typename ArrayType> class TArrayConcatOperator : public TExecutableOperator<TArrayConcatOperator<ArrayType>>`  
_L468-546_
- inherits: `TExecutableOperator<TArrayConcatOperator<ArrayType>>`
- desc: TArrayConcatOperator concatenates two arrays on trigger.
- L471 _public typedef_ `using FArrayDataReadReference = TDataReadReference<ArrayType>;`
- L472 _public typedef_ `using FArrayDataWriteReference = TDataWriteReference<ArrayType>;`
- L473 _public typedef_ `using ElementType = typename MetasoundArrayNodesPrivate::TArrayElementType<ArrayType>::Type;`
- L475 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L484 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L500 _public function_ `TArrayConcatOperator(TDataReadReference<FTrigger> InTrigger, FArrayDataReadReference InLeftArray, FArrayDataReadReference InRightArray) : Trigger(InTrigger) , LeftArray(InLeftArray) , RightArray(InRightArray) , OutArray(TDataWriteReference<ArrayType>::CreateNew())`
- L508 _public prototype_ `virtual ~TArrayConcatOperator() = default;`
- L510 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L519 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData) override`
- L526 _public function_ `void Execute()`
- L535 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L542 _private member_ `TDataReadReference<FTrigger> Trigger;`
- L543 _private member_ `FArrayDataReadReference LeftArray;`
- L544 _private member_ `FArrayDataReadReference RightArray;`
- L545 _private member_ `FArrayDataWriteReference OutArray;`

#### class `Metasound::TArraySubsetOperator`  
`template<typename ArrayType> class TArraySubsetOperator : public TExecutableOperator<TArraySubsetOperator<ArrayType>>`  
_L553-647_
- inherits: `TExecutableOperator<TArraySubsetOperator<ArrayType>>`
- desc: TArraySubsetOperator slices an array on trigger.
- L556 _public typedef_ `using FArrayDataReadReference = TDataReadReference<ArrayType>;`
- L557 _public typedef_ `using FArrayDataWriteReference = TDataWriteReference<ArrayType>;`
- L558 _public typedef_ `using ElementType = typename MetasoundArrayNodesPrivate::TArrayElementType<ArrayType>::Type;`
- L560 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L569 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L589 _public function_ `TArraySubsetOperator(TDataReadReference<FTrigger> InTrigger, FArrayDataReadReference InInputArray, TDataReadReference<int32> InStartIndex, TDataReadReference<int32> InEndIndex, TDataWriteReference<ArrayType> InOutputArray) : Trigger(InTrigger) , InputArray(InInputArray) , StartIndex(InStartIndex) , EndIndex(InEndIndex) , OutputArray(InOutputArray)`
- L598 _public prototype_ `virtual ~TArraySubsetOperator() = default;`
- L600 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L610 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData) override`
- L617 _public function_ `void Execute()`
- L635 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L642 _private member_ `TDataReadReference<FTrigger> Trigger;`
- L643 _private member_ `FArrayDataReadReference InputArray;`
- L644 _private member_ `TDataReadReference<int32> StartIndex;`
- L645 _private member_ `TDataReadReference<int32> EndIndex;`
- L646 _private member_ `FArrayDataWriteReference OutputArray;`

#### class `Metasound::TArrayLastIndexOperator`  
`template<typename ArrayType> class TArrayLastIndexOperator : public TExecutableOperator<TArrayLastIndexOperator<ArrayType>>`  
_L654-718_
- inherits: `TExecutableOperator<TArrayLastIndexOperator<ArrayType>>`
- desc: TArrayLastIndex gets last index of an array.
- L657 _public typedef_ `using FArrayDataReadReference = TDataReadReference<ArrayType>;`
- L659 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L668 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L681 _public function_ `TArrayLastIndexOperator(FArrayDataReadReference InArray) : Array(InArray) , LastIndex(TDataWriteReference<int32>::CreateNew())`
- L689 _public prototype_ `virtual ~TArrayLastIndexOperator() = default;`
- L691 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L697 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData) override`
- L704 _public function_ `void Execute()`
- L709 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L716 _private member_ `FArrayDataReadReference Array;`
- L717 _private member_ `TDataWriteReference<int32> LastIndex;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define LOCTEXT_NAMESPACE "MetasoundFrontend"`
- L24 _namespace_ `namespace Metasound`
- L26 _namespace_ `namespace MetasoundArrayNodesPrivate` (scope `Metasound`)
- L29 _prototype_ `FNodeClassName CreateArrayNodeClassName(const FName& InOperatorName, const FName& InDataTypeName);` (scope `Metasound::MetasoundArrayNodesPrivate`) — Convenience function for make FNodeClassMetadata of array nodes.
- L30 _prototype_ `FNodeClassMetadata CreateArrayNodeClassMetadata(const FName& InDataTypeName, const FName& InOperatorName, const FText& InDisplayName, const FText& InDescription, const FVertexInterface& InDefaultInterface, int32 MajorVersion=1, int32 MinorVersion=0, bool bIsDeprecated=false);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L32 _prototype_ `FVertexInterface CreateArrayNumInterface(const FName& InArrayDataTypeName);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L33 _prototype_ `FVertexInterface CreateArrayGetInterface(const FName& InArrayDataTypeName, const FName& InDataTypeName);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L34 _prototype_ `FVertexInterface CreateArraySetInterface(const FName& InArrayDataTypeName, const FName& InDataTypeName);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L35 _prototype_ `FVertexInterface CreateArraySubsetInterface(const FName& InArrayDataTypeName);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L36 _prototype_ `FVertexInterface CreateArrayConcatInterface(const FName& InArrayDataTypeName);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L37 _prototype_ `FVertexInterface CreateArrayLastIndexInterface(const FName& InArrayDataTypeName);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L39 _prototype_ `Frontend::FNodeClassRegistryKey CreateArrayNumNodeClassRegistryKey(const FName& InArrayDataTypeName);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L40 _prototype_ `Frontend::FNodeClassRegistryKey CreateArrayGetNodeClassRegistryKey(const FName& InArrayDataTypeName);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L41 _prototype_ `Frontend::FNodeClassRegistryKey CreateArraySetNodeClassRegistryKey(const FName& InArrayDataTypeName);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L42 _prototype_ `Frontend::FNodeClassRegistryKey CreateArraySubsetNodeClassRegistryKey(const FName& InArrayDataTypeName);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L43 _prototype_ `Frontend::FNodeClassRegistryKey CreateArrayConcatNodeClassRegistryKey(const FName& InArrayDataTypeName);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L44 _prototype_ `Frontend::FNodeClassRegistryKey CreateArrayLastIndexNodeClassRegistryKey(const FName& InArrayDataTypeName);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L46 _prototype_ `FNodeClassMetadata CreateArrayNumNodeClassMetadata(const FName& InArrayDataTypeName, const FText& InArrayDataTypeDisplayText);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L47 _prototype_ `FNodeClassMetadata CreateArrayGetNodeClassMetadata(const FName& InArrayDataTypeName, const FName& InElementDataTypeName, const FText& InArrayDataTypeDisplayText);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L48 _prototype_ `FNodeClassMetadata CreateArraySetNodeClassMetadata(const FName& InArrayDataTypeName, const FName& InElementDataTypeName, const FText& InArrayDataTypeDisplayText);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L49 _prototype_ `FNodeClassMetadata CreateArraySubsetNodeClassMetadata(const FName& InArrayDataTypeName, const FText& InArrayDataTypeDisplayText);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L50 _prototype_ `FNodeClassMetadata CreateArrayConcatNodeClassMetadata(const FName& InArrayDataTypeName, const FText& InArrayDataTypeDisplayText);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L51 _prototype_ `FNodeClassMetadata CreateArrayLastIndexNodeClassMetadata(const FName& InArrayDataTypeName, const FText& InArrayDataTypeDisplayText);` (scope `Metasound::MetasoundArrayNodesPrivate`)
- L68 _namespace_ `namespace ArrayNodeVertexNames` (scope `Metasound`)
- L70 _externvar_ `extern const FLazyName InputInitialArrayName;` (scope `Metasound::ArrayNodeVertexNames`)
- L71 _externvar_ `extern const FText InputInitialArrayTooltip;` (scope `Metasound::ArrayNodeVertexNames`)
- L72 _externvar_ `extern const FText InputInitialArrayDisplayName;` (scope `Metasound::ArrayNodeVertexNames`)
- L164 _typedef_ `template<typename ArrayType> using TArrayNumNode = TNodeFacade<TArrayNumOperator<ArrayType>>;` (scope `Metasound`)
- L321 _typedef_ `template<typename ArrayType> using TArrayGetNode = TNodeFacade<TArrayGetOperator<ArrayType>>;` (scope `Metasound`)
- L464 _typedef_ `template<typename ArrayType> using TArraySetNode = TNodeFacade<TArraySetOperator<ArrayType>>;` (scope `Metasound`)
- L549 _typedef_ `template<typename ArrayType> using TArrayConcatNode = TNodeFacade<TArrayConcatOperator<ArrayType>>;` (scope `Metasound`)
- L650 _typedef_ `template<typename ArrayType> using TArraySubsetNode = TNodeFacade<TArraySubsetOperator<ArrayType>>;` (scope `Metasound`)
- L721 _typedef_ `template<typename ArrayType> using TArrayLastIndexNode = TNodeFacade<TArrayLastIndexOperator<ArrayType>>;` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundArrayNodesRegistration.h` (Public)


#### struct `Metasound::TEnableArrayNodes`  
`template<typename ... ElementType> struct TEnableArrayNodes`  
_L16-19_
- L18 _public member_ `static constexpr bool Value = true;`

#### struct `Metasound::MetasoundArrayNodesPrivate::TArrayNodeSupport`  
`template<typename ArrayType> struct TArrayNodeSupport`  
_L29-65_
- desc: TArrayNodeSupport acts as a configuration sturct to determine whether a particular TArrayNode can be instantiated for a specific ArrayType. Some ArrayNodes require that the array elements have certain properties such as default element constructors, element copy constructors, etc.
- L32 _private typedef_ `using ElementType = typename MetasoundArrayNodesPrivate::TArrayElementType<ArrayType>::Type;`
- L34 _private member_ `static constexpr bool bIsElementParsableAndAssignable = TIsParsable<ElementType>::Value && std::is_copy_assignable<ElementType>::value;`
- L36 _private member_ `static constexpr bool bEnabled = TEnableArrayNodes<ElementType>::Value;`
- L41 _public member_ `static constexpr bool bIsArrayNumSupported = bEnabled;` — Array num is supported for all array types.
- L44 _public member_ `static constexpr bool bIsArrayLastIndexSupported = bEnabled;` — Array last index is supported for all array types.
- L49 _public member_ `static constexpr bool bIsArrayGetSupported = bEnabled && bIsElementParsableAndAssignable;` — Element must be default parsable to create get operator because a value must be returned even if the index is invalid. Also values are assigned by copy.
- L52 _public member_ `static constexpr bool bIsArraySetSupported = bEnabled && std::is_copy_assignable<ElementType>::value && std::is_copy_constructible<ElementType>::value;` — Element must be copy assignable to set the value.
- L55 _public member_ `static constexpr bool bIsArrayConcatSupported = bEnabled && std::is_copy_constructible<ElementType>::value;` — Elements must be copy constructible
- L58 _public member_ `static constexpr bool bIsArraySubsetSupported = bEnabled && std::is_copy_constructible<ElementType>::value;` — Elements must be copy constructible
- L61 _public member_ `static constexpr bool bIsArrayShuffleSupported = bEnabled && bIsElementParsableAndAssignable;` — Array shuffle is supported for all types that get is supported for.
- L64 _public member_ `static constexpr bool bIsArrayRandomGetSupported = bEnabled && bIsElementParsableAndAssignable;` — Random get is supported for all types that get is supported for.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Metasound`
- L21 _namespace_ `namespace MetasoundArrayNodesPrivate` (scope `Metasound`)
- L68 _namespace_ `namespace Frontend` (scope `Metasound`)
- L75 _function_ `template<typename ArrayType> bool RegisterArrayNodes(const FModuleInfo& InModuleInfo)` (scope `Metasound::Frontend`) — Registers all available array nodes which can be instantiated for the given ArrayType. Some nodes cannot be instantiated due to limitations of the array elements.
- L88 _typedef_ `using FGetNodeType = typename Metasound::TArrayGetNode<ArrayType>;` (scope `Metasound::Frontend::RegisterArrayNodes`)
- L94 _typedef_ `using FSetNodeType = typename Metasound::TArraySetNode<ArrayType>;` (scope `Metasound::Frontend::RegisterArrayNodes`)
- L100 _typedef_ `using FSubsetNodeType = typename Metasound::TArraySubsetNode<ArrayType>;` (scope `Metasound::Frontend::RegisterArrayNodes`)
- L106 _typedef_ `using FConcatNodeType = typename Metasound::TArrayConcatNode<ArrayType>;` (scope `Metasound::Frontend::RegisterArrayNodes`)
- L112 _typedef_ `using FShuffleNodeType = typename Metasound::TArrayShuffleNode<ArrayType>;` (scope `Metasound::Frontend::RegisterArrayNodes`)
- L118 _typedef_ `using FRandomGetNodeType = typename Metasound::TArrayRandomGetNode<ArrayType>;` (scope `Metasound::Frontend::RegisterArrayNodes`)
- L131 _prototype_ `bool UnregisterArrayNodes(const FName& InArrayDataTypeName, const FModuleInfo& InModuleInfo);` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundArrayRandomNode.h` (Public)


#### enum `Metasound::ESharedStateBehaviorType`  
`enum class ESharedStateBehaviorType : int32`  
_L84-89_
- L86 _public enumerator_ `SameNode`
- L87 _public enumerator_ `SameNodeInComposition`
- L88 _public enumerator_ `SameData`

#### class `Metasound::FArrayRandomGet`  
`class FArrayRandomGet`  
_L94-129_
- L97 _public prototype_ `FArrayRandomGet() = default;`
- L98 _public prototype_ `FArrayRandomGet(int32 InSeed, int32 InMaxIndex, const TArray<float>& InWeights, int32 InNoRepeatOrder);`
- L99 _public prototype_ `~FArrayRandomGet() = default;`
- L102 _public prototype_ `void Init(int32 InSeed, int32 InMaxIndex, const TArray<float>& InWeights, int32 InNoRepeatOrder);` — `UE_DEPRECATED(5.5, "Use UpdateState instead")`
- L103 _public prototype_ `void UpdateState(int32 InSeed, int32 InMaxIndex, const TArray<float>& InWeights, int32 InNoRepeatOrder);`
- L104 _public prototype_ `void SetSeed(int32 InSeed);`
- L105 _public prototype_ `void SetNoRepeatOrder(int32 InNoRepeatOrder);`
- L106 _public prototype_ `void SetRandomWeights(const TArray<float>& InRandomWeights);`
- L107 _public prototype_ `void ResetSeed();`
- L108 _public prototype_ `int32 NextValue();`
- L110 _public function_ `int32 GetNoRepeatOrder() const`
- L111 _public function_ `int32 GetMaxIndex() const`
- L114 _private prototype_ `float ComputeTotalWeight();`
- L117 _private member_ `TArray<int32> PreviousIndices;` — The current index into the array of indicies (wraps between 0 and ShuffleIndices.Num())
- L118 _private member_ `TUniquePtr<TCircularQueue<int32>> PreviousIndicesQueue;`
- L119 _private member_ `int32 NoRepeatOrder = INDEX_NONE;`
- L122 _private member_ `int32 MaxIndex = 0;` — Array of indices (in order 0 to Num)
- L123 _private member_ `TArray<float> RandomWeights;`
- L126 _private member_ `FRandomStream RandomStream;` — Random stream to use to randomize the shuffling
- L127 _private member_ `int32 Seed = INDEX_NONE;`
- L128 _private member_ `bool bRandomStreamInitialized = false;`

#### struct `Metasound::InitSharedStateArgs`  
`struct InitSharedStateArgs`  
_L131-139_
- L133 _public member_ `FGuid SharedStateId;`
- L134 _public member_ `int32 Seed = INDEX_NONE;`
- L135 _public member_ `int32 NumElements = 0;`
- L136 _public member_ `int32 NoRepeatOrder = 0;`
- L137 _public member_ `bool bIsPreviewSound = false;`
- L138 _public member_ `TArray<float> Weights;`

#### class `Metasound::FSharedStateRandomGetManager`  
`class FSharedStateRandomGetManager`  
_L141-171_
- L144 _public prototype_ `static FSharedStateRandomGetManager& Get();`
- L146 _public prototype_ `void InitSharedState(InitSharedStateArgs& InArgs);`
- L148 _public prototype_ `void InitOrUpdate(InitSharedStateArgs& InStateArgs);` — Initialize or update state for a given shared state id. No lock, so call this function within one if needed
- L152 _public prototype_ `int32 NextValue(const FGuid& InSharedStateId, InitSharedStateArgs& InStateArgs);` — Get the next array index Init or update state with the given args, then return next value (within a single lock operation)
- L153 _public prototype_ `int32 NextValue(const FGuid& InSharedStateId);`
- L155 _public prototype_ `void SetSeed(const FGuid& InSharedStateId, int32 InSeed);`
- L156 _public prototype_ `void SetNoRepeatOrder(const FGuid& InSharedStateId, int32 InNoRepeatOrder);`
- L157 _public prototype_ `void SetRandomWeights(const FGuid& InSharedStateId, const TArray<float>& InRandomWeights);`
- L160 _public prototype_ `void ResetSeed(const FGuid& InSharedStateId, InitSharedStateArgs& InStateArgs);` — Init or update state with the given args, then reset seed (within a single lock operation)
- L161 _public prototype_ `void ResetSeed(const FGuid& InSharedStateId);`
- L165 _private prototype_ `FSharedStateRandomGetManager() = default;`
- L166 _private prototype_ `~FSharedStateRandomGetManager() = default;`
- L168 _private member_ `FCriticalSection CritSect;`
- L170 _private member_ `TMap<FGuid, TUniquePtr<FArrayRandomGet>> RandomGets;`

#### class `Metasound::TArrayRandomGetOperator`  
`template<typename ArrayType> class TArrayRandomGetOperator : public TExecutableOperator<TArrayRandomGetOperator<ArrayType>>`  
_L174-533_
- inherits: `TExecutableOperator<TArrayRandomGetOperator<ArrayType>>`
- L177 _public typedef_ `using FArrayDataReadReference = TDataReadReference<ArrayType>;`
- L178 _public typedef_ `using FArrayWeightReadReference = TDataReadReference<TArray<float>>;`
- L179 _public typedef_ `using WeightsArrayType = TArray<float>;`
- L180 _public typedef_ `using ElementType = typename MetasoundArrayNodesPrivate::TArrayElementType<ArrayType>::Type;`
- L181 _public typedef_ `using FElementTypeWriteReference = TDataWriteReference<ElementType>;`
- L183 _public function_ `static const FVertexInterface& GetDefaultInterface()`
- L193 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L201 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L220 _public function_ `TArrayRandomGetOperator( const FBuildOperatorParams& InParams, const FTriggerReadRef& InTriggerNext, const FTriggerReadRef& InTriggerReset, const FArrayDataReadReference& InInputArray, const TDataReadReference<WeightsArrayType>& InInputWeightsArray, const FInt32ReadRef& InSeedValue, const FInt32ReadRef& InNoRepeatOrder, const FBoolReadRef& bInEnableSharedState, const FEnumSharedStateBehaviorType InSharedStateBehavior) : TriggerNext(InTriggerNext) , TriggerReset(InTriggerReset) , InputArray(InInputArray) , InputWeightsArray(InInputWeightsArray) , SeedValue(InSeedValue) , NoRepeatOrder(InNoRepeatOrder) , bEnableSharedState(bInEnableSharedState) , SharedStateBehavior(InSharedStateBehavior) , TriggerOnNext(FTriggerWriteRef::CreateNew(InParams.OperatorSettings)) , TriggerOnReset(FTriggerWriteRef::CreateNew(InParams.OperatorSettings)) , OutValue(TDataWriteReferenceFactory<ElementType>::CreateAny(InParams.OperatorSettings)) , OutIndex(FInt32WriteRef::CreateNew(INDEX_NONE))`
- L247 _public prototype_ `virtual ~TArrayRandomGetOperator() = default;`
- L249 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override`
- L262 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override`
- L271 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L328 _public function_ `void Execute()`
- L389 _private function_ `void CreateSharedStateArgs(InitSharedStateArgs& InOutStateArgs)`
- L399 _private function_ `void ExecuteTriggerReset(int32 StartFrame)`
- L432 _private function_ `void ExecuteTriggerNext(int32 StartFrame)`
- L481 _private function_ `FGuid GetSameNodeSharedStateId(const FGuid& InNodeId, const FGuid& InOtherId) const` — Hash combine the current node id with another id
- L492 _private function_ `FGuid GetSameNodeInCompositionId(const FGuid& InNodeId, const TArray<FGuid>& InGraphHierarchy) const` — Hash combine the current node id with the graph hierarchy ids
- L506 _private member_ `FTriggerReadRef TriggerNext;` — Inputs
- L507 _private member_ `FTriggerReadRef TriggerReset;`
- L508 _private member_ `FArrayDataReadReference InputArray;`
- L509 _private member_ `TDataReadReference<WeightsArrayType> InputWeightsArray;`
- L510 _private member_ `FInt32ReadRef SeedValue;`
- L511 _private member_ `FInt32ReadRef NoRepeatOrder;`
- L512 _private member_ `FBoolReadRef bEnableSharedState;`
- L513 _private member_ `FEnumSharedStateBehaviorType SharedStateBehavior;`
- L516 _private member_ `FTriggerWriteRef TriggerOnNext;` — Outputs
- L517 _private member_ `FTriggerWriteRef TriggerOnReset;`
- L518 _private member_ `TDataWriteReference<ElementType> OutValue;`
- L519 _private member_ `FInt32WriteRef OutIndex;`
- L522 _private member_ `FString GraphName;`
- L523 _private member_ `bool bHasLoggedEmptyArrayWarning = false;`
- L524 _private member_ `bool bHasLoggedMissingGraphHierarchyWarning = false;`
- L525 _private member_ `FString DebugSharedStateBehaviorString;`
- L529 _private member_ `TUniquePtr<FArrayRandomGet> ArrayRandomGet;` — Data
- L530 _private member_ `FGuid NodeId;`
- L531 _private member_ `FGuid SharedStateId;`
- L532 _private member_ `bool bIsPreviewSound = false;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L19 _macro_ `#define LOCTEXT_NAMESPACE "MetasoundFrontend"`
- L21 _namespace_ `namespace MetasoundArrayHashPrivate`
- L24 _function_ `template<typename ElementType> FGuid GetArrayContentHashGuid(const TArray<ElementType>& InArray)` (scope `MetasoundArrayHashPrivate`)
- L59 _namespace_ `namespace Metasound`
- L61 _namespace_ `namespace ArrayNodeRandomGetVertexNames` (scope `Metasound`)
- L77 _namespace_ `namespace ArrayRandomNodePrivate` (scope `Metasound`)
- L79 _prototype_ `Frontend::FNodeClassRegistryKey CreateArrayRandomNodeClassRegistryKey(const FName& InArrayDataTypeName);` (scope `Metasound::ArrayRandomNodePrivate`)
- L80 _prototype_ `FVertexInterface CreateArrayRandomNodeInterface(const FName& InArrayDataTypeName, const FName& InElementDataTypeName);` (scope `Metasound::ArrayRandomNodePrivate`)
- L81 _prototype_ `FNodeClassMetadata CreateArrayRandomNodeClassMetadata(const FName& InArrayDataTypeName, const FName& InElementDataTypeName, const FText& InArrayDataTypeDisplayText);` (scope `Metasound::ArrayRandomNodePrivate`)
- L346 _function_ `` (scope `Metasound::TArrayRandomGetOperator::Execute`)
- L536 _typedef_ `template<typename ArrayType> using TArrayRandomGetNode = TNodeFacade<TArrayRandomGetOperator<ArrayType>>;` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundArrayShuffleNode.h` (Public)


#### class `Metasound::FArrayIndexShuffler`  
`class FArrayIndexShuffler`  
_L54-85_
- L57 _public prototype_ `FArrayIndexShuffler() = default;`
- L58 _public prototype_ `FArrayIndexShuffler(int32 InSeed, int32 MaxIndices);`
- L60 _public prototype_ `void Init(int32 InSeed, int32 MaxIndices);`
- L61 _public prototype_ `void SetSeed(int32 InSeed);`
- L62 _public prototype_ `void ResetSeed();`
- L65 _public prototype_ `bool NextValue(bool bAutoShuffle, int32& OutIndex);` — Returns the next value in the array indices. Returns true if the array was re-shuffled automatically.
- L68 _public prototype_ `void ShuffleArray();` — Shuffle the array with the given max indices
- L72 _private prototype_ `void RandomSwap(int32 InCurrentIndex, int32 InStartIndex, int32 InEndIndex);` — Helper function to swap the current index with a random index
- L75 _private member_ `int32 CurrentIndex = 0;` — The current index into the array of indicies (wraps between 0 and ShuffleIndices.Num())
- L78 _private member_ `int32 PrevValue = INDEX_NONE;` — The previously returned value. Used to avoid repeating the last value on shuffle.
- L81 _private member_ `TArray<int32> ShuffleIndices;` — Array of indices (in order 0 to Num), shuffled
- L84 _private member_ `FRandomStream RandomStream;` — Random stream to use to randomize the shuffling

#### class `Metasound::FSharedStateShuffleManager`  
`class FSharedStateShuffleManager`  
_L87-141_
- L90 _public function_ `static FSharedStateShuffleManager& Get()`
- L96 _public function_ `void InitSharedState(uint32 InSharedStateId, int32 InSeed, int32 InNumElements)`
- L106 _public function_ `bool NextValue(uint32 InSharedStateId, bool bAutoShuffle, int32& OutIndex)`
- L113 _public function_ `void SetSeed(uint32 InSharedStateId, int32 InSeed)`
- L120 _public function_ `void ResetSeed(uint32 InSharedStateId)`
- L127 _public function_ `void ShuffleArray(uint32 InSharedStateId)`
- L135 _private prototype_ `FSharedStateShuffleManager() = default;`
- L136 _private prototype_ `~FSharedStateShuffleManager() = default;`
- L138 _private member_ `FCriticalSection CritSect;`
- L140 _private member_ `TMap<uint32, TUniquePtr<FArrayIndexShuffler>> Shufflers;`

#### class `Metasound::TArrayShuffleOperator`  
`template<typename ArrayType> class TArrayShuffleOperator : public TExecutableOperator<TArrayShuffleOperator<ArrayType>>`  
_L145-419_
- inherits: `TExecutableOperator<TArrayShuffleOperator<ArrayType>>`
- desc: TArrayShuffleOperator shuffles an array on trigger and outputs values sequentially on "next". It avoids repeating shuffled elements and supports auto-shuffling.
- L148 _public typedef_ `using FArrayDataReadReference = TDataReadReference<ArrayType>;`
- L149 _public typedef_ `using ElementType = typename MetasoundArrayNodesPrivate::TArrayElementType<ArrayType>::Type;`
- L150 _public typedef_ `using FElementTypeWriteReference = TDataWriteReference<ElementType>;`
- L152 _public function_ `static const FVertexInterface& GetDefaultInterface()`
- L162 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L170 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L188 _public function_ `TArrayShuffleOperator( const FBuildOperatorParams& InParams, const TDataReadReference<FTrigger>& InTriggerNext, const TDataReadReference<FTrigger>& InTriggerShuffle, const TDataReadReference<FTrigger>& InTriggerReset, const FArrayDataReadReference& InInputArray, const TDataReadReference<int32>& InSeedValue, const TDataReadReference<bool>& bInAutoShuffle, const TDataReadReference<bool>& bInEnableSharedState) : TriggerNext(InTriggerNext) , TriggerShuffle(InTriggerShuffle) , TriggerReset(InTriggerReset) , InputArray(InInputArray) , SeedValue(InSeedValue) , bAutoShuffle(bInAutoShuffle) , bEnableSharedState(bInEnableSharedState) , TriggerOnShuffle(FTriggerWriteRef::CreateNew(InParams.OperatorSettings)) , OutValue(TDataWriteReferenceFactory<ElementType>::CreateAny(InParams.OperatorSettings))`
- L210 _public prototype_ `virtual ~TArrayShuffleOperator() = default;`
- L212 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override`
- L225 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override`
- L235 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L254 _public function_ `void Execute()`
- L322 _private function_ `void InitializeShufflers(int32 InSize)`
- L338 _private function_ `void Seed(int32 InNewSeed)`
- L354 _private function_ `void Reset()`
- L368 _private function_ `bool GetNextIndex(int32& OutIndex)`
- L387 _private function_ `void Shuffle()`
- L402 _private member_ `TDataReadReference<FTrigger> TriggerNext;` — Inputs
- L403 _private member_ `TDataReadReference<FTrigger> TriggerShuffle;`
- L404 _private member_ `TDataReadReference<FTrigger> TriggerReset;`
- L405 _private member_ `FArrayDataReadReference InputArray;`
- L406 _private member_ `TDataReadReference<int32> SeedValue;`
- L407 _private member_ `TDataReadReference<bool> bAutoShuffle;`
- L408 _private member_ `TDataReadReference<bool> bEnableSharedState;`
- L411 _private member_ `TDataWriteReference<FTrigger> TriggerOnShuffle;` — Outputs
- L412 _private member_ `TDataWriteReference<ElementType> OutValue;`
- L415 _private member_ `TUniquePtr<FArrayIndexShuffler> ArrayIndexShuffler;` — Data
- L416 _private member_ `int32 PrevSeedValue = INDEX_NONE;`
- L417 _private member_ `int32 PrevArraySize = 0;`
- L418 _private member_ `uint32 SharedStateUniqueId = INDEX_NONE;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L25 _macro_ `#define LOCTEXT_NAMESPACE "MetasoundFrontend"`
- L28 _namespace_ `namespace Metasound`
- L31 _namespace_ `namespace ArrayNodeShuffleVertexNames` (scope `Metasound`)
- L47 _namespace_ `namespace ArrayShuffleNodePrivate` (scope `Metasound`)
- L49 _prototype_ `Frontend::FNodeClassRegistryKey CreateArrayShuffleNodeClassRegistryKey(const FName& InArrayDataTypeName);` (scope `Metasound::ArrayShuffleNodePrivate`)
- L50 _prototype_ `FVertexInterface CreateArrayShuffleNodeInterface(const FName& InArrayDataTypeName, const FName& InElementDataTypeName);` (scope `Metasound::ArrayShuffleNodePrivate`)
- L51 _prototype_ `FNodeClassMetadata CreateArrayShuffleNodeClassMetadata(const FName& InArrayDataTypeName, const FName& InElementDataTypeName, const FText& InArrayDataTypeDisplayText);` (scope `Metasound::ArrayShuffleNodePrivate`)
- L278 _function_ `` (scope `Metasound::TArrayShuffleOperator::Execute`)
- L422 _typedef_ `template<typename ArrayType> using TArrayShuffleNode = TNodeFacade<TArrayShuffleOperator<ArrayType>>;` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundAssetBase.h` (Public)


#### class `FMetasoundAssetBase`  
`class FMetasoundAssetBase : public IAudioProxyDataFactory`  
_L59-242_
- inherits: `IAudioProxyDataFactory`
- desc: FMetasoundAssetBase is a mix-in subclass for UObjects which utilize MetaSound objects. As MetaSounds can now be generated dynamically via the Builder API, the name does not accurately reflect this classes current implementation.  While it currently has some support for asset, editor graph & document accessors (actively being deprecated), its primary use is to support all access to runtime-specific, MetaSound features and associated data, such as proxy generation and runtime node class registration.  For forward support of the MetaSound document model and supported accessors, see 'IMetaSoundDocumentInterface'.
- L62 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;`
- L64 _public member_ `static const FString FileExtension;`
- L66 _public prototype_ `FMetasoundAssetBase() = default;`
- L67 _public prototype_ `virtual ~FMetasoundAssetBase() = default;`
- L70 _public prototype_ `virtual FText GetDisplayName() const = 0;`
- L75 _public prototype_ `virtual UEdGraph* GetGraph() const = 0;` — Returns the graph associated with this Metasound. Graph is required to be referenced on Metasound UObject for editor serialization purposes. @return Editor graph associated with this metasound uobject.
- L76 _public prototype_ `virtual UEdGraph& GetGraphChecked() const = 0;`
- L77 _public prototype_ `virtual void MigrateEditorGraph(FMetaSoundFrontendDocumentBuilder& OutBuilder) = 0;`
- L82 _public prototype_ `virtual void SetGraph(UEdGraph* InGraph) = 0;` — Sets the graph associated with this Metasound. Graph is required to be referenced on Metasound UObject for editor serialization purposes. @param Editor graph associated with this metasound object.
- L85 _public function_ `virtual void SetRegistryAssetClassInfo(const Metasound::Frontend::FNodeClassInfo& InClassInfo)` — `UE_DEPRECATED(5.6, "AssetClass tags now directly serialized using UObject GetAssetRegistryTags call")`
- L89 _public prototype_ `void UpdateAndRegisterForExecution();` — `UE_DEPRECATED(5.7, "Use method which requires a FMetaSoundAssetRegistrationOptions")`
- L93 _public prototype_ `virtual void UpdateAndRegisterForExecution(const Metasound::Frontend::FMetaSoundAssetRegistrationOptions& InRegistrationOptions);` — Registers the root graph of the given asset with the MetaSound Frontend. Unlike 'UpdateAndRegisterForSerialization", this call generates all necessary runtime data to execute the given graph (i.e. INodes).
- L96 _public prototype_ `void UnregisterGraphWithFrontend();` — Unregisters the root graph of the given asset with the MetaSound Frontend.
- L103 _public prototype_ `void UpdateAndRegisterForSerialization(FName CookPlatformName = { });` — `UE_DEPRECATED(5.7, "Use method which passes in FMetaSoundAssetCookOptions")` — Updates and registers this and referenced MetaSound document objects with the NodeClass Registry. AutoUpdates and optimizes aforementioned documents for serialization. Unlike 'UpdateAndRegisterForRuntime', does not generate required runtime data for graph execution.
- L108 _public prototype_ `void UpdateAndRegisterForSerialization(const Metasound::Frontend::FMetaSoundAssetCookOptions& InCookOptions);` — Updates and registers this and referenced MetaSound document objects with the NodeClass Registry. AutoUpdates and optimizes aforementioned documents for serialization. Unlike 'UpdateAndRegisterForRuntime', does not generate required runtime data for graph execution.
- L113 _public prototype_ `void RebuildReferencedAssetClasses();` — Rebuild dependent asset classes
- L117 _public prototype_ `bool IsInterfaceDeclared(const FMetasoundFrontendVersion& InVersion) const;` — Returns whether an interface with the given version is declared by the given asset's document.
- L120 _public prototype_ `virtual const TSet<FString>& GetReferencedAssetClassKeys() const = 0;` — Returns all the class keys of this asset's referenced assets
- L124 _public prototype_ `virtual TArray<FMetasoundAssetBase*> GetReferencedAssets() const = 0;` — Returns set of class references set call to serialize in the editor Used at runtime load register referenced classes.
- L128 _public function_ `virtual const TSet<FSoftObjectPath>& GetAsyncReferencedAssetClassPaths() const` — `UE_DEPRECATED(5.8, "Dynamic loading of referenced assets is deprecated")`
- L137 _public function_ `virtual void OnAsyncReferencedAssetsLoaded(const TArray<FMetasoundAssetBase*>& InAsyncReferences)` — `UE_DEPRECATED(5.8, "This is deprecated behavior and will become UE_INTERNAL API in a future release for back compat.")`
- L140 _public prototype_ `bool AddingReferenceCausesLoop(const FMetasoundAssetBase& InMetaSound) const;`
- L142 _public prototype_ `bool IsReferencedAsset(const FMetasoundAssetBase& InAssetToCheck) const;`
- L144 _public prototype_ `bool IsRegistered() const;`
- L147 _public prototype_ `bool ImportFromJSON(const FString& InJSON);` — `UE_DEPRECATED(5.8, "Feature no longer supported")`
- L150 _public prototype_ `bool ImportFromJSONAsset(const FString& InAbsolutePath);` — `UE_DEPRECATED(5.8, "Feature no longer supported")`
- L153 _public prototype_ `Metasound::Frontend::FDocumentHandle GetDocumentHandle(bool bReloadBuilder = true);` — Soft Deprecated in favor of DocumentBuilder API. Returns handle for the root metasound graph of this asset.
- L154 _public prototype_ `Metasound::Frontend::FConstDocumentHandle GetDocumentHandle() const;`
- L157 _public prototype_ `Metasound::Frontend::FGraphHandle GetRootGraphHandle();` — Soft Deprecated in favor of DocumentBuilder API. Returns handle for the root metasound graph of this asset.
- L158 _public prototype_ `Metasound::Frontend::FConstGraphHandle GetRootGraphHandle() const;`
- L160 _public prototype_ `virtual const FMetasoundFrontendDocument& GetConstDocumentChecked() const;`
- L164 _public prototype_ `FMetasoundFrontendDocument& GetDocumentChecked();` — Soft deprecated.  Document layer should not be directly mutated via asset base in anticipation of moving all mutable document calls to the Frontend/Subsystem Document Builder API.
- L166 _public prototype_ `const Metasound::Frontend::FGraphRegistryKey& GetGraphRegistryKey() const;`
- L170 _public prototype_ `bool VersionAsset(FMetaSoundFrontendDocumentBuilder& Builder);` — `UE_DEPRECATED(5.8, "Implementation is now internal and moved to VersioningManager.")`
- L175 _public prototype_ `void CacheRegistryMetadata();` — `UE_DEPRECATED(5.7, "Moved to FMetaSoundFrontendDocumentBuilder")`
- L177 _public prototype_ `FMetasoundFrontendDocumentModifyContext& GetModifyContext();`
- L179 _public prototype_ `const FMetasoundFrontendDocumentModifyContext& GetConstModifyContext() const;`
- L183 _public prototype_ `bool MarkMetasoundDocumentDirty() const;` — Calls the outermost package and marks it dirty.
- L192 _public prototype_ `virtual UObject* GetOwningAsset() = 0;` — Returns the owning asset responsible for transactions applied to MetaSound
- L195 _public prototype_ `virtual const UObject* GetOwningAsset() const = 0;` — Returns the owning asset responsible for transactions applied to MetaSound
- L197 _public prototype_ `FString GetOwningAssetName() const;`
- L200 _public prototype_ `void ClearVersionedOnLoad();`
- L201 _public prototype_ `bool GetVersionedOnLoad() const;`
- L202 _public prototype_ `void SetVersionedOnLoad();`
- L206 _protected prototype_ `void OnNotifyBeginDestroy();`
- L211 _protected function_ `virtual void SetReferencedAssetClasses(TSet<Metasound::Frontend::IMetaSoundAssetManager::FAssetInfo>&& InAssetClasses)` — `UE_DEPRECATED(5.6, "Use SetReferencedAssets instead")`
- L214 _protected prototype_ `virtual void SetReferencedAssets(TSet<Metasound::Frontend::IMetaSoundAssetManager::FAssetRef>&& InAssetRefs) = 0;`
- L218 _protected prototype_ `FText GetDisplayName(FString&& InTypeName) const;`
- L224 _protected prototype_ `virtual Metasound::Frontend::FDocumentAccessPtr GetDocumentAccessPtr(bool bReloadBuilder = true) = 0;` — `UE_DEPRECATED(5.6, "AccessPtrs are actively being deprecated. Writable access outside of the builder API " " is particularly problematic as in so accessing, the builder's caches are reset which can cause major " "editor performance regressions.")`
- L227 _protected prototype_ `virtual Metasound::Frontend::FConstDocumentAccessPtr GetDocumentConstAccessPtr() const = 0;` — Returns an access pointer to the document.
- L230 _protected prototype_ `void RegisterAssetDependencies(const Metasound::Frontend::FMetaSoundAssetRegistrationOptions & InRegistrationOptions);` — Ensures all referenced graph classes are registered (or re-registers depending on options).
- L234 _private prototype_ `void UpdateAndRegisterReferencesForSerialization(const Metasound::Frontend::FMetaSoundAssetCookOptions& InCookOptions);`
- L236 _private member_ `bool bVersionedOnLoad = false;`
- L239 _private member_ `Metasound::Frontend::FGraphRegistryKey GraphRegistryKey;`
- L241 _private member_ `FMetasoundAssetProxyPtr Proxy;`

#### struct `FMetasoundAssetBase::FSendInfoAndVertexName`  
`struct FSendInfoAndVertexName`  
_L185-189_
- L187 _public member_ `Metasound::FMetaSoundParameterTransmitter::FSendInfo SendInfo;`
- L188 _public member_ `Metasound::FVertexName VertexName;`

#### class `FMetasoundAssetProxy`  
`class FMetasoundAssetProxy final : public Audio::TProxyData<FMetasoundAssetProxy>`  
_L244-269_
- inherits: `Audio::TProxyData<FMetasoundAssetProxy>`
- L247 _public prototype_ `IMPL_AUDIOPROXY_CLASS(FMetasoundAssetProxy);`
- L255 _public prototype_ `explicit FMetasoundAssetProxy(const FParameters& InParams);`
- L257 _public prototype_ `FMetasoundAssetProxy(const FMetasoundAssetProxy& Other);`
- L259 _public prototype_ `const Metasound::Frontend::FGraphRegistryKey& GetGraphRegistryKey() const;`
- L261 _public prototype_ `const Metasound::IGraph* GetGraph() const;`
- L263 _public prototype_ `const TSet<FMetasoundFrontendVersion>& GetInterfaces() const;`
- L267 _private member_ `TSet<FMetasoundFrontendVersion> Interfaces;`
- L268 _private member_ `Metasound::Frontend::FGraphRegistryKey GraphRegistryKey;`

#### struct `FMetasoundAssetProxy::FParameters`  
`struct FParameters`  
_L249-253_
- L251 _public member_ `TSet<FMetasoundFrontendVersion> Interfaces;`
- L252 _public member_ `Metasound::Frontend::FGraphRegistryKey GraphRegistryKey;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L26 _typedef_ `typedef TMulticastDelegate<void(IConsoleVariable*), FDefaultDelegateUserPolicy> FConsoleVariableMulticastDelegate;`
- L29 _typedef_ `using FMetasoundAssetProxyPtr = TSharedPtr<FMetasoundAssetProxy>;`
- L31 _namespace_ `namespace Metasound`
- L35 _namespace_ `namespace Frontend` (scope `Metasound`)
- L40 _prototype_ `TRange<float> GetBlockRateClampRange();` (scope `Metasound::Frontend`)
- L41 _prototype_ `float GetBlockRateOverride();` (scope `Metasound::Frontend`)
- L42 _prototype_ `FConsoleVariableMulticastDelegate& GetBlockRateOverrideChangedDelegate();` (scope `Metasound::Frontend`)
- L44 _prototype_ `TRange<int32> GetSampleRateClampRange();` (scope `Metasound::Frontend`)
- L45 _prototype_ `int32 GetSampleRateOverride();` (scope `Metasound::Frontend`)
- L46 _prototype_ `FConsoleVariableMulticastDelegate& GetSampleRateOverrideChangedDelegate();` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundAssetKey.h` (Public)


#### struct `FMetaSoundAssetKey`  
`struct FMetaSoundAssetKey`  
_L19-65_
- reflection: `USTRUCT()`
- L24 _public member_ `FMetasoundFrontendClassName ClassName;` — `UPROPERTY()`
- L27 _public member_ `FMetasoundFrontendVersionNumber Version;` — `UPROPERTY()`
- L29 _public prototype_ `FMetaSoundAssetKey() = default;`
- L30 _public prototype_ `FMetaSoundAssetKey(const FMetasoundFrontendClassName& InClassName, const FMetasoundFrontendVersionNumber& InVersion);`
- L31 _public prototype_ `FMetaSoundAssetKey(const Metasound::Frontend::FNodeClassRegistryKey& RegKey);`
- L32 _public prototype_ `FMetaSoundAssetKey(const FMetasoundFrontendClassMetadata& InMetadata);`
- L55 _public prototype_ `static const FMetaSoundAssetKey& GetInvalid();` — Returns invalid asset key.
- L58 _public prototype_ `bool IsValid() const;` — Returns whether or not key is valid.
- L61 _public prototype_ `static bool IsValidType(EMetasoundFrontendClassType ClassType);` — Returns whether or not ClassType is supported by asset/asset key.
- L64 _public prototype_ `FString ToString() const;` — Returns string representation of asset key.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L34 _function_ `inline friend bool operator==(const FMetaSoundAssetKey& InLHS, const FMetaSoundAssetKey& InRHS)`
- L39 _function_ `inline friend bool operator<(const FMetaSoundAssetKey& InLHS, const FMetaSoundAssetKey& InRHS)`
- L49 _function_ `friend inline uint32 GetTypeHash(const FMetaSoundAssetKey& InKey)`
- L67 _namespace_ `namespace Metasound`
- L67 _namespace_ `namespace Frontend` (scope `Metasound`)
- L69 _typedef_ `using FAssetKey UE_DEPRECATED(5.6, "Moved to global namespac` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundAssetManager.h` (Public)


#### struct `FMetaSoundDocumentInfo`  
`struct FMetaSoundDocumentInfo`  
_L37-58_
- reflection: `USTRUCT(BlueprintType, DisplayName = "MetaSound Document Info")`
- L41 _public prototype_ `FMetaSoundDocumentInfo();`
- L42 _public prototype_ `FMetaSoundDocumentInfo(const IMetaSoundDocumentInterface& InDocInterface);`
- L43 _public prototype_ `FMetaSoundDocumentInfo(const FAssetData& InAssetData, bool& bOutIsValid);`
- L45 _public prototype_ `void ExportToContext(FAssetRegistryTagsContext& OutContext) const;`
- L49 _public member_ `FMetasoundFrontendVersionNumber DocumentVersion;` — `UPROPERTY(BlueprintReadOnly, Category = DocumentInfo)` — Version of document
- L53 _public member_ `TArray<FMetaSoundAssetKey> ReferencedAssetKeys;` — `UPROPERTY()` — Versions of referenced asset class keys
- L57 _public member_ `uint8 bIsPreset : 1;` — `UPROPERTY(BlueprintReadOnly, Category = DocumentInfo)` — Whether asset is a preset or not.

#### struct `Metasound::Frontend::FMetaSoundAssetRegistrationOptions`  
`struct FMetaSoundAssetRegistrationOptions`  
_L62-101_
- L66 _public member_ `bool bForceReregister = true;` — If true, forces a re-register of this class (and all class dependencies if the following option 'bRegisterDependencies' is enabled).
- L70 _public member_ `bool bForceViewSynchronization = true;` — If true, forces flag to resync all view (editor) data pertaining to the given asset(s) being registered.
- L76 _public member_ `bool bRegisterDependencies = true;` — If true, recursively attempts to register dependencies. (TODO: Determine if this option should be removed. Must validate that failed dependency updates due to auto-update for ex. being disabled is handled gracefully at runtime.)
- L80 _public member_ `bool bAutoUpdate = true;` — Attempt to auto-update (Only runs if class not registered or set to force re-register. Will not respect being set to true if project-level MetaSoundSettings specify to not run auto-update.)
- L83 _public member_ `bool bAutoUpdateLogWarningOnDroppedConnection = false;` — If true, warnings will be logged if updating a node results in existing connections being discarded.
- L87 _public member_ `bool bPreprocessDocument = true;` — Soft deprecated. Preprocessing now handled contextually if cooking or serializing.
- L90 _public member_ `bool bRebuildReferencedAssetClasses = true;` — Attempt to rebuild referenced classes (only run if class not registered or set to force re-register)
- L93 _public member_ `bool bRegisterCopyIfAsync = false;` — No longer used. Memory management of document (i.e. copying or using object's version) inferred internally
- L96 _public member_ `bool bIgnoreIfLiveAuditioning = false;` — If currently previewing the given MetaSound, registration request is ignored.
- L100 _public member_ `TArrayView<const FGuid> PageOrder;` — Contains a ranking of the preferred page to use with the most preferred page ID being first.

#### struct `Metasound::Frontend::FMetaSoundAssetCookOptions`  
`struct FMetaSoundAssetCookOptions`  
_L103-113_
- L106 _public member_ `bool bStripUnusedPages = false;` — If true, any unused page will get removed during cook.
- L109 _public member_ `TArray<FGuid> PagesToTarget;` — Which PageIDs are going to available for targeting after cook.
- L112 _public member_ `TArray<FGuid> PageOrder;` — The PageOrder to use when cooking.

#### struct `Metasound::Frontend::FMetaSoundAssetClassInfo`  
`struct FMetaSoundAssetClassInfo : public FMetaSoundClassInfo`  
_L121-157_
- inherits: `FMetaSoundClassInfo`
- desc: At runtime, contains a minimal set of information needed to further query additional class data from the Node Class Registries. At edit-time, contains this plus additional data useful for informing user of applicable asset classes within given edit contexts (see 'FMetaSoundEditorGraphSchema').
- L123 _public prototype_ `FMetaSoundAssetClassInfo() = default;`
- L124 _public prototype_ `FMetaSoundAssetClassInfo(const IMetaSoundDocumentInterface& InDocInterface);`
- L129 _public prototype_ `FMetaSoundAssetClassInfo(const FAssetData& InAssetData);` — Attempts to transform AssetTag data from the given AssetData to this class info (asset may or may not be loaded). bIsValid set to false if object isn't loaded and any fields fail to load/are not serialized (i.e. tags are out-of-date).
- L132 _public prototype_ `virtual void ExportToContext(FAssetRegistryTagsContext& OutContext) const override;` — Exports tag data to the given RegistryContext
- L137 _public prototype_ `static bool TryGetAssetKey(const FAssetData& InAssetData, FMetaSoundAssetKey& OutKey);` — If asset is loaded, retrieves asset key from loaded data. Otherwise, parses just the tag data necessary to get the given asset's asset key. Does not attempt to load asset, and will fail if data is not found and asset isn't loaded.
- L142 _public prototype_ `static bool TryGetAssetClassName(const FAssetData& InAssetData, FMetasoundFrontendClassName& OutClassName);` — If asset is loaded, retrieves asset class name from loaded data. Otherwise, parses just the tag data necessary to get the given asset's class name. Does not attempt to load asset, and will fail if data is not found and asset isn't loaded.
- L145 _protected prototype_ `virtual void InitFromDocument(const IMetaSoundDocumentInterface& InDocInterface) override;`
- L148 _private prototype_ `static bool TryGetAssetClassTag(const FAssetData& InAssetData, FString& OutClassIDString);`
- L152 _public member_ `FTopLevelAssetPath AssetPath;` — Path to asset containing graph if external type and references asset class.
- L155 _public member_ `FMetaSoundDocumentInfo DocInfo;`

#### class `Metasound::Frontend::IMetaSoundAssetManager`  
`class IMetaSoundAssetManager`  
_L160-361_
- L163 _public prototype_ `virtual ~IMetaSoundAssetManager() = default;`
- L165 _public prototype_ `static IMetaSoundAssetManager* Get();`
- L166 _public prototype_ `static IMetaSoundAssetManager& GetChecked();`
- L167 _public prototype_ `static void Deinitialize();`
- L168 _public prototype_ `static void Initialize(TUniquePtr<IMetaSoundAssetManager>&& InInterface);`
- L173 _public typedef_ `using FOnUpdatedAssetLoaded = TFunction<void(FMetaSoundAssetKey, UObject&)>;` — Passed template function pointer to execute in certain contexts when a MetaSound object is either already loaded or has completed asynchronous load.  Due to some implementation restrictions when constructing FLoadPackageAsyncDelegate, this has to be a copyable function (vs. TUniqueFunction).
- L180 _public function_ `inline friend bool operator==(const FAssetRef& InLHS, const FAssetRef& InRHS)`
- L185 _public function_ `inline friend uint32 GetTypeHash(const FAssetRef& InInfo)`
- L196 _public function_ `inline friend bool operator==(const FAssetInfo& InLHS, const FAssetInfo& InRHS)`
- L201 _public function_ `inline friend uint32 GetTypeHash(const FAssetInfo& InInfo)`
- L224 _public prototype_ `virtual bool AddAssetReferences(FMetasoundAssetBase& InAssetBase) = 0;` — Adds missing assets using the provided asset's local reference class cache. Used to prime system from asset attempting to register prior to asset scan being complete. Returns true if references were added, false if it they are already found.
- L228 _public function_ `virtual FMetaSoundAssetKey AddOrUpdateAsset(const UObject& InObject)` — `UE_DEPRECATED(5.6, "Moved to AddOrUpdateFromObject")`
- L231 _public function_ `virtual FMetaSoundAssetKey AddOrUpdateAsset(const FAssetData& InAssetData)` — `UE_DEPRECATED(5.6, "Moved to AddOrLoadAndUpdateFromObjectAsync")`
- L234 _public prototype_ `virtual FMetaSoundAssetKey AddOrUpdateFromObject(const UObject& InObject) = 0;` — Add or Update a MetaSound Asset's entry data from a loaded MetaSound asset UObject.
- L239 _public prototype_ `virtual void AddOrLoadAndUpdateFromObjectAsync(const FAssetData& InAssetData, FOnUpdatedAssetLoaded&& OnUpdatedAssetLoaded) = 0;` — Add or Update a MetaSound Asset's entry data from an object, loading it if it isn't already.  On initial call, requests object load asynchronously and runs provided function on successful completion. If asset is already loaded, runs provided function immediately on entry update (synchronously).
- L243 _public prototype_ `virtual void AddOrUpdateFromAssetData(const FAssetData& InAssetData) = 0;` — Add or Update a MetaSound Asset's entry data from AssetData. Potentially loads asset and adds asynchronously if asset or associated tag schema is out-of-date.
- L246 _public function_ `virtual bool CanAutoUpdate(const FMetasoundFrontendClassName& InClassName) const` — `UE_DEPRECATED(5.7, "AutoUpdate is required now prior to MetaSounds executing runtime builds")`
- L249 _public prototype_ `virtual bool ContainsKey(const FMetaSoundAssetKey& InAssetKey) const = 0;` — Whether or not the asset manager has loaded the given asset
- L253 _public prototype_ `virtual bool ContainsKey(const Metasound::Frontend::FNodeRegistryKey& InRegistryKey) const = 0;` — Whether or not the asset manager has loaded one or more assets with the given registry key. Returns false if key is not valid asset key (ex. input or output class key, variable, etc.)
- L257 _public prototype_ `virtual FMetasoundAssetBase* FindAsset(const FMetaSoundAssetKey& InAssetKey) const = 0;` — Returns object (if loaded) associated with the given key (null if key not registered with the AssetManager) If multiple assets are associated with the given key, the last one is returned.
- L263 _public prototype_ `virtual TArray<Frontend::FMetaSoundClassInfo> FindRegisteredClassInfo(const FMetaSoundAssetKey& InKey) const = 0;` — Returns all class info associated with the given asset key (may be more than one due to errors in duplication of assets, improper plugin migration, etc. but should usually just be a single entry) registered with the manager. Info may not be returned if the asset has yet to be registered with the MetaSoundAssetManager or may be out-of-date if edited after last registration attempt via AddOrUpdate... calls.
- L266 _public prototype_ `virtual TScriptInterface<IMetaSoundDocumentInterface> FindAssetAsDocumentInterface(const FMetaSoundAssetKey& InKey) const = 0;` — Returns object (if loaded) associated with the given key as a Document Interface (null if key not registered with the AssetManager)
- L270 _public prototype_ `virtual FTopLevelAssetPath FindAssetPath(const FMetaSoundAssetKey& InAssetKey) const = 0;` — Returns path associated with the given key (returns invalid asset path if key not registered with the AssetManager or was not loaded from asset) If multiple assets are associated with the given key, the last one is returned.
- L273 _public prototype_ `virtual TArray<FTopLevelAssetPath> FindAssetPaths(const FMetaSoundAssetKey& InAssetKey) const = 0;` — Returns all paths associated with the given key (returns empty array if key not registered with the AssetManager or was not loaded from asset)
- L276 _public prototype_ `virtual FMetasoundAssetBase* GetAsAsset(UObject& InObject) const = 0;` — Converts an object to an AssetBase if its a registered asset
- L277 _public prototype_ `virtual const FMetasoundAssetBase* GetAsAsset(const UObject& InObject) const = 0;`
- L282 _public function_ `virtual TSet<FAssetInfo> GetReferencedAssetClasses(const FMetasoundAssetBase& InAssetBase) const` — `UE_DEPRECATED(5.6, "Use GetReferencedAssets instead")`
- L286 _public prototype_ `virtual TSet<FAssetRef> GetReferencedAssets(const FMetasoundAssetBase& InAssetBase) const = 0;` — Generates all asset info associated with registered assets that are referenced by the provided asset's graph.
- L292 _public prototype_ `virtual bool GetReferencedPresetHierarchy(FMetasoundAssetBase& InAsset, TArray<FMetasoundAssetBase*>& OutReferencedAssets) const = 0;` — Get assets this asset is a preset of, recursively for presets of presets. This means finding all references including the last non preset, but not graphs used directly in non-preset composition. Ex. MetaSound A is a preset of MetaSound B, which is a preset of MetaSound C, which references D by composition -> When called on A, will return B and C. If not a preset, returns false.
- L296 _public prototype_ `UE_INTERNAL virtual Frontend::FMetaSoundAssetRegistrationOptions GetRegistrationOptions() const = 0;` — Returns default registration options for MetaSound assets
- L299 _public prototype_ `virtual bool IsAssetClass(const FMetasoundFrontendClassMetadata& ClassMetadata) const = 0;` — Returns whether or not the given ClassMetadata is both valid asset ClassMetadata and is registered.
- L302 _public function_ `virtual void IterateAssets(TFunctionRef<void(const FMetaSoundAssetKey, const TArray<FTopLevelAssetPath>&)> Iter) const` — `UE_DEPRECATED(5.6, "Moved to Iterate ClassInfo")`
- L305 _public prototype_ `virtual void SetLogActiveAssetsOnShutdown(bool bLogActiveAssetsOnShutdown) = 0;` — Set flag for logging active assets on shutdown. In certain cases (ex. validation), it is expected that assets are active at shutdown
- L308 _public prototype_ `virtual bool TryGetAssetIDFromClassName(const FMetasoundFrontendClassName& InClassName, FGuid& OutGuid) const = 0;` — Attempts to retrieve the AssetID from the given ClassName if the ClassName is from a valid asset.
- L311 _public prototype_ `virtual FMetasoundAssetBase* TryLoadAsset(const FSoftObjectPath& InObjectPath) const = 0;` — Attempts to load an FMetasoundAssetBase from the given path, or returns it if its already loaded
- L314 _public prototype_ `virtual FMetasoundAssetBase* TryLoadAssetFromKey(const FMetaSoundAssetKey& InAssetKey) const = 0;` — Returns asset associated with the given key (null if key not registered with the AssetManager or was not loaded from asset)
- L318 _public prototype_ `virtual bool TryLoadReferencedAssets(const FMetasoundAssetBase& InAssetBase, TArray<FMetasoundAssetBase*>& OutReferencedAssets) const = 0;` — Try to load referenced assets of the given asset or return them if they are already loaded (non-recursive). @return - True if all referenced assets successfully loaded, false if not.
- L323 _public prototype_ `virtual bool ReassignClassName(TScriptInterface<IMetaSoundDocumentInterface> DocInterface) = 0;` — Assigns a new arbitrary class name to the given document, which can cause references to be invalidated. (See
- L328 _public function_ `virtual void RequestAsyncLoadReferencedAssets(FMetasoundAssetBase& InAssetBase, const TSet<FSoftObjectPath>* Paths = nullptr)` — `UE_DEPRECATED(5.8, "This is a deprecated feature, and exists to port old soft object references to hard references.")`
- L332 _public function_ `virtual void ReloadMetaSoundAssets() const` — `UE_DEPRECATED(5.8, "Use 'ReregisterLoadedAssets' instead.")`
- L335 _public prototype_ `virtual void RemoveAsset(const UObject& InObject) = 0;` — Removes object from MetaSound asset manager
- L338 _public prototype_ `virtual void RemoveAsset(const FAssetData& InAssetData) = 0;` — Removes object from MetaSound asset manager
- L341 _public prototype_ `virtual void RenameAsset(const FAssetData& InAssetData, const FString& InOldObjectPath) = 0;` — Updates the given MetaSound's asset record with the new name and optionally reregisters it with the Frontend Node Class Registry.
- L345 _public prototype_ `virtual void ReregisterLoadedAssets() const = 0;` — Finds all currently loaded assets and re-registers them with the MetasoundUObjectRegistry. Ensures all paged data is targeted appropriately and can be expensive.
- L351 _public prototype_ `virtual FVersionAssetResults SetAccessFlagsOnAssetsInFolders(const TArray<FString>& FolderPaths, EMetasoundFrontendClassAccessFlags Flags, bool bRecursePaths) const = 0;` — Sets all access flags to the provided flags for the given assets. Optionally, recurses the given paths. Populates the provided array with MetaSound packages whose document versions were out-of-date and consequently updated. Returns resulting assets that were updated and those not.
- L356 _public prototype_ `virtual FVersionAssetResults VersionAssetsInFolders(const TArray<FString>& FolderPaths, bool bRecursePaths = true) const = 0;` — Versions all MetaSound asset tags & documents found within the given folder paths. Optionally, recurses the given paths. Populates the provided array with MetaSound packages whose document versions were out-of-date and consequently updated. Returns resulting versioned and unversioned paths.
- L359 _public prototype_ `virtual void WaitUntilAsyncLoadReferencedAssetsComplete(const FMetasoundAssetBase& InAssetBase) = 0;` — Waits until all async load requests related to this asset are complete.

#### struct `Metasound::Frontend::IMetaSoundAssetManager::FAssetRef`  
`struct FAssetRef`  
_L175-189_
- L177 _public member_ `FMetaSoundAssetKey Key;`
- L178 _public member_ `FTopLevelAssetPath Path;`

#### struct `Metasound::Frontend::IMetaSoundAssetManager::FAssetInfo`  
`struct UE_DEPRECATED(5.6, "Use FAssetRef instead") FAssetInfo`  
_L191-205_
- L193 _public member_ `FNodeRegistryKey RegistryKey;`
- L194 _public member_ `FSoftObjectPath AssetPath;`

#### struct `Metasound::Frontend::IMetaSoundAssetManager::FVersionAssetResults`  
`struct FVersionAssetResults`  
_L208-219_
- L210 _public member_ `TArray<FTopLevelAssetPath> FailedPackages;`
- L211 _public member_ `TArray<UPackage*> PackagesToReserialize;`
- L212 _public member_ `TArray<FTopLevelAssetPath> PackagesUpToDate;`
- L215 _public function_ `bool DocumentsFoundInPackages() const` — Returns whether or not documents were found and loaded/attempted to version

#### class `Metasound::Frontend::FMetaSoundAssetManagerBase`  
`class FMetaSoundAssetManagerBase : public IMetaSoundAssetManager`  
_L363-373_
- inherits: `IMetaSoundAssetManager`
- L366 _public prototype_ `FMetaSoundAssetManagerBase();`
- L367 _public prototype_ `virtual ~FMetaSoundAssetManagerBase() = default;`
- L369 _public prototype_ `IMetaSoundAssetTransactor& GetTransactor();`
- L372 _private member_ `TUniquePtr<IMetaSoundAssetTransactor> Transactor;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L60 _namespace_ `namespace Metasound`
- L60 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundAssetManagerTransaction.h` (Public)


#### class `Metasound::Frontend::FAssetManagerTransaction`  
`class FAssetManagerTransaction`  
_L14-39_
- L17 _public typedef_ `using FTimeType = uint64;`
- L27 _public prototype_ `static FString LexToString(ETransactionType InTransactionType);`
- L29 _public prototype_ `FAssetManagerTransaction(ETransactionType InType, const FMetaSoundAssetKey& InKey, FTimeType InTimestamp);`
- L31 _public prototype_ `ETransactionType GetTransactionType() const;`
- L32 _public prototype_ `FNodeClassRegistryKey GetNodeRegistryKey() const;`
- L33 _public prototype_ `FTimeType GetTimestamp() const;`
- L36 _private member_ `ETransactionType Type;`
- L37 _private member_ `FNodeClassRegistryKey Key;`
- L38 _private member_ `FTimeType Timestamp;`

#### enum `Metasound::Frontend::FAssetManagerTransaction::ETransactionType`  
`enum class ETransactionType : uint8`  
_L20-25_
- desc: Describes the type of transaction.
- L22 _public enumerator_ `AssetRegistration` — Something was added to the registry.
- L23 _public enumerator_ `AssetUnregistration` — Something was removed from the registry.
- L24 _public enumerator_ `Invalid`

#### class `Metasound::Frontend::IMetaSoundAssetTransactor`  
`class IMetaSoundAssetTransactor`  
_L41-48_
- L44 _public prototype_ `virtual ~IMetaSoundAssetTransactor() = default;`
- L46 _public prototype_ `virtual void RegisterAsset(FMetaSoundAssetKey Key) = 0;`
- L47 _public prototype_ `virtual void UnregisterAsset(FMetaSoundAssetKey Key) = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L12 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundAutoConverterNode.h` (Public)


#### struct `Metasound::AutoConverterNodePrivate::FConvertDataTypeInfo`  
`struct FConvertDataTypeInfo`  
_L24-32_
- L26 _public member_ `FName FromDataTypeName;`
- L27 _public member_ `FText FromDataTypeText;`
- L28 _public member_ `FName ToDataTypeName;`
- L29 _public member_ `FText ToDataTypeText;`
- L30 _public member_ `bool bIsFromEnum;`
- L31 _public member_ `bool bIsToEnum;`

#### struct `Metasound::TIsAutoConvertible`  
`template<typename TFromDataType, typename TToDataType> struct TIsAutoConvertible`  
_L62-71_
- desc: Determines whether an auto converter node will be registered to convert between two types.
- L64 _public member_ `static constexpr bool bIsConvertible = std::is_convertible<TFromDataType, TToDataType>::value;`
- L67 _public member_ `static constexpr bool bIsIntToEnumConversion = std::is_same<int32, TFromDataType>::value && TEnumTraits<TToDataType>::bIsEnum;` — Handle case of converting enums to/from integers.
- L68 _public member_ `static constexpr bool bIsEnumToIntConversion = TEnumTraits<TFromDataType>::bIsEnum && std::is_same<int32, TToDataType>::value;`
- L70 _public member_ `static constexpr bool Value = bIsConvertible || bIsIntToEnumConversion || bIsEnumToIntConversion;`

#### class `Metasound::TAutoConverterNode`  
`template<typename FromDataType, typename ToDataType> class TAutoConverterNode : public FBasicNode`  
_L76-237_
- inherits: `FBasicNode`
- desc: This convenience node can be registered and will invoke static_cast<ToDataType>(FromDataType) every time it is executed, with a special case for enum <-> int32 conversions.
- L82 _public function_ `static const FVertexName& GetInputName()`
- L88 _public function_ `static const FVertexName& GetOutputName()`
- L94 _public function_ `static FVertexInterface DeclareVertexInterface()`
- L100 _public function_ `static const FNodeClassMetadata& GetAutoConverterNodeMetadata()`
- L217 _public function_ `TAutoConverterNode(const FNodeInitData& InInitData) : TAutoConverterNode(FNodeData(InInitData.InstanceName, InInitData.InstanceID, DeclareVertexInterface()), MakeShared<const FNodeClassMetadata>(GetAutoConverterNodeMetadata()))`
- L222 _public function_ `TAutoConverterNode(FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InClassMetadata) : FBasicNode(MoveTemp(InNodeData), MoveTemp(InClassMetadata)) , Factory(MakeOperatorFactoryRef<FCoverterOperatorFactory>())`
- L228 _public prototype_ `virtual ~TAutoConverterNode() = default;`
- L230 _public function_ `virtual FOperatorFactorySharedRef GetDefaultOperatorFactory() const override`
- L236 _private member_ `FOperatorFactorySharedRef Factory;`

#### class `Metasound::TAutoConverterNode::FConverterOperator`  
`class FConverterOperator : public TExecutableOperator<FConverterOperator>`  
_L112-196_
- inherits: `TExecutableOperator<FConverterOperator>`
- desc: FConverterOperator converts from "FromDataType" to "ToDataType" using a implicit conversion operators.
- L116 _public function_ `FConverterOperator(TDataReadReference<FromDataType> InFromDataReference, TDataWriteReference<ToDataType> InToDataReference) : FromData(InFromDataReference) , ToData(InToDataReference)`
- L123 _public prototype_ `virtual ~FConverterOperator() = default;`
- L125 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L130 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData) override`
- L135 _public function_ `void Execute()`
- L181 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L189 _private member_ `TDataReadReference<FromDataType> FromData;`
- L190 _private member_ `TDataWriteReference<ToDataType> ToData;`
- L194 _private member_ `bool bHasLoggedInvalidEnum = false;` — To prevent log spam, keep track of whether we've logged an invalid enum value being converted already and the previous int value (need both bool and int for the initial case)
- L195 _private member_ `int32 PreviousIntValueForEnumConversion = 0;`

#### class `Metasound::TAutoConverterNode::FCoverterOperatorFactory`  
`class FCoverterOperatorFactory : public IOperatorFactory`  
_L201-213_
- inherits: `IOperatorFactory`
- desc: FConverterOperatorFactory creates an operator which converts from "FromDataType" to "ToDataType".
- L204 _public prototype_ `FCoverterOperatorFactory() = default;`
- L206 _public function_ `virtual TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults) override`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Metasound`
- L22 _namespace_ `namespace AutoConverterNodePrivate` (scope `Metasound`)
- L34 _prototype_ `FVertexName GetInputName(const FConvertDataTypeInfo& InInfo);` (scope `Metasound::AutoConverterNodePrivate`)
- L36 _prototype_ `FVertexName GetOutputName(const FConvertDataTypeInfo& InInfo);` (scope `Metasound::AutoConverterNodePrivate`)
- L38 _prototype_ `FVertexInterface CreateVertexInterface(const FConvertDataTypeInfo& InInfo);` (scope `Metasound::AutoConverterNodePrivate`)
- L40 _prototype_ `FNodeClassName CreateAutoConverterNodeClassName(const FName& InFromDataType, const FName& InToDataType);` (scope `Metasound::AutoConverterNodePrivate`)
- L41 _prototype_ `Frontend::FNodeClassRegistryKey CreateAutoConverterNodeClassRegistryKey(const FName& InFromDataType, const FName& InToDataType);` (scope `Metasound::AutoConverterNodePrivate`)
- L42 _prototype_ `FNodeClassMetadata CreateAutoConverterNodeMetadata(const FConvertDataTypeInfo& InInfo);` (scope `Metasound::AutoConverterNodePrivate`)
- L45 _function_ `template<typename FromDataType, typename ToDataType> FConvertDataTypeInfo MakeConvertDataTypeInfo()` (scope `Metasound::AutoConverterNodePrivate`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundChannelAgnosticAutoTypes.h` (Public)


#### enum `EMetasoundChannelAgnosticSourceFormatChooser`  
`enum class EMetasoundChannelAgnosticSourceFormatChooser : uint8`  
_L11-15_
- reflection: `UENUM()`
- L13 _public enumerator_ `Auto`
- L14 _public enumerator_ `Custom`

#### enum `EMetasoundChannelAgnosticNodeFormatChooser`  
`enum class EMetasoundChannelAgnosticNodeFormatChooser : uint8`  
_L18-23_
- reflection: `UENUM()`
- L20 _public enumerator_ `Auto`
- L21 _public enumerator_ `Source`
- L22 _public enumerator_ `Custom`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METASOUNDFRONTEND_API`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundChannelAgnosticDataSchemas.h` (Public)


#### struct `FCatDataTypeSchema`  
`struct FCatDataTypeSchema`  
_L26-48_
- reflection: `USTRUCT()`
- L35 _public member_ `FName BaseType;` — `UPROPERTY()`
- L38 _public member_ `FName FamilyType;` — `UPROPERTY()`
- L41 _public member_ `FString FriendlyName;` — `UPROPERTY()`
- L44 _public member_ `bool bIsAbstract = false;` — `UPROPERTY()`
- L47 _public member_ `bool bIsParentsDefault = false;` — `UPROPERTY()`

#### struct `FCatSoundfieldDataSchema`  
`struct FCatSoundfieldDataSchema : public FCatDataTypeSchema`  
_L51-58_
- reflection: `USTRUCT()`
- inherits: `FCatDataTypeSchema`

#### struct `FCatDiscreteChannel`  
`struct FCatDiscreteChannel`  
_L61-77_
- reflection: `USTRUCT()`
- L70 _public member_ `float AzimuthDegrees = 0;` — `UPROPERTY()` — -180 to 180 azimuth.
- L73 _public member_ `FName ID;` — `UPROPERTY()` — ID of the Speaker. This could be unique ID or match the Short form of the Speaker ID.
- L76 _public member_ `bool bIsSpatialized = true;` — `UPROPERTY()` — If this is off, azimuth+degrees do nothing. (for excluding from panner).

#### enum `ECatDiscreteOrderPolicy`  
`enum class ECatDiscreteOrderPolicy : uint32`  
_L81-85_
- reflection: `UENUM()`
- L83 _public enumerator_ `ChannelEnum` — Format uses the order of the AudioMixerChannel (which is the same as WavFormatEx)
- L84 _public enumerator_ `Explicit` — If explicit, use the Order[] array here to define it.

#### struct `FCatDiscreteDataSchema`  
`struct FCatDiscreteDataSchema : public FCatDataTypeSchema`  
_L88-101_
- reflection: `USTRUCT()`
- inherits: `FCatDataTypeSchema`
- L97 _public member_ `TArray<FName> Order;` — `UPROPERTY()`
- L100 _public member_ `TArray<FCatDiscreteChannel> Speakers;` — `UPROPERTY()`

#### struct `FCatCompositeDataSchema`  
`struct FCatCompositeDataSchema : public FCatDataTypeSchema`  
_L104-108_
- reflection: `USTRUCT()`
- inherits: `FCatDataTypeSchema`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundChannelAgnosticType.h` (Public)


#### class `Metasound::FChannelAgnosticType`  
`class FChannelAgnosticType : public Audio::FChannelAgnosticType`  
_L13-46_
- inherits: `Audio::FChannelAgnosticType`
- L17 _public typedef_ `using Super = Audio::FChannelAgnosticType;`
- L19 _public function_ `static FName GetRegisteredTypeName()`
- L28 _public function_ `const FName& GetDataTypeName() const` — Metasound Polymorphic Type Id+Name. (required for intrusive references to work).
- L29 _public function_ `const void* GetDataTypeId() const`
- L35 _public prototype_ `static FName GetCatDefaultCatFormat();`
- L37 _public prototype_ `static TSharedRef<FChannelAgnosticType, ESPMode::NotThreadSafe> CreateNew(const FOperatorSettings& InSettings, const FName InDerivedType=GetCatDefaultCatFormat());`
- L42 _public prototype_ `FChannelAgnosticType(const int32 InNumFramesPerBlock, const FName& InChannelTypeName);`
- L43 _public prototype_ `FChannelAgnosticType(const FOperatorSettings& InSettings, const FName& InChannelTypeName);`

#### class `Metasound::FDiscreteChannelAgnosticType`  
`class FDiscreteChannelAgnosticType : public FChannelAgnosticType`  
_L48-74_
- inherits: `FChannelAgnosticType`
- L53 _public function_ `static FName GetRegisteredTypeName()`
- L58 _public typedef_ `using Super = FChannelAgnosticType;`
- L63 _public prototype_ `static FName GetDefaultCatFormat();`
- L66 _public prototype_ `static TSharedRef<FDiscreteChannelAgnosticType, ESPMode::NotThreadSafe> CreateNew(const FOperatorSettings& InSettings, const FName InDerivedType=GetDefaultCatFormat());` — Factory function for the default case.
- L72 _public function_ `FDiscreteChannelAgnosticType(const FOperatorSettings& InSettings, const FName InDerivedType) : Super(InSettings, InDerivedType)`

#### class `Metasound::FSoundfieldChannelAgnosticType`  
`class FSoundfieldChannelAgnosticType : public FChannelAgnosticType`  
_L75-97_
- inherits: `FChannelAgnosticType`
- L80 _public function_ `static FName GetRegisteredTypeName()`
- L85 _public typedef_ `using Super = FChannelAgnosticType;`
- L87 _public prototype_ `static FName GetDefaultCatFormat();`
- L88 _public prototype_ `static TSharedRef<FSoundfieldChannelAgnosticType, ESPMode::NotThreadSafe> CreateNew(const FOperatorSettings& InSettings, const FName InDerivedType=GetDefaultCatFormat());`
- L91 _public function_ `FSoundfieldChannelAgnosticType(const FOperatorSettings& InSettings, const FName InDerivedType) : Super(InSettings, InDerivedType)`

#### class `Metasound::FCompositeChannelAgnosticType`  
`class FCompositeChannelAgnosticType : public FChannelAgnosticType`  
_L98-119_
- inherits: `FChannelAgnosticType`
- L103 _public function_ `static FName GetRegisteredTypeName()`
- L108 _public typedef_ `using Super = FChannelAgnosticType;`
- L110 _public prototype_ `static FName GetDefaultCatFormat();`
- L111 _public prototype_ `static TSharedRef<FCompositeChannelAgnosticType, ESPMode::NotThreadSafe> CreateNew(const FOperatorSettings& InSettings, const FName InDerivedType=GetDefaultCatFormat());`
- L113 _public function_ `FCompositeChannelAgnosticType(const FOperatorSettings& InSettings, const FName InDerivedType) : Super(InSettings, InDerivedType)`

#### struct `Metasound::TEnableAutoArrayTypeRegistration`  
`template<> struct TEnableAutoArrayTypeRegistration<FChannelAgnosticType>`  
_L139-139_
- desc: Disable auto-generated array nodes. CAT types are polymorphic/abstract and should not expose array variants in the MetaSound editor.
- L139 _public member_ `template<> struct TEnableAutoArrayTypeRegistration<FChannelAgnosticType> { static constexpr bool Value = false; };` — Disable auto-generated array nodes. CAT types are polymorphic/abstract and should not expose array variants in the MetaSound editor.

#### struct `Metasound::TEnableAutoArrayTypeRegistration`  
`template<> struct TEnableAutoArrayTypeRegistration<FChannelAgnosticType>`  
_L140-140_
- desc: Disable auto-generated array nodes. CAT types are polymorphic/abstract and should not expose array variants in the MetaSound editor.
- L139 _public member_ `template<> struct TEnableAutoArrayTypeRegistration<FChannelAgnosticType> { static constexpr bool Value = false; };` — Disable auto-generated array nodes. CAT types are polymorphic/abstract and should not expose array variants in the MetaSound editor.

#### struct `Metasound::TEnableAutoArrayTypeRegistration`  
`template<> struct TEnableAutoArrayTypeRegistration<FChannelAgnosticType>`  
_L141-141_
- desc: Disable auto-generated array nodes. CAT types are polymorphic/abstract and should not expose array variants in the MetaSound editor.
- L139 _public member_ `template<> struct TEnableAutoArrayTypeRegistration<FChannelAgnosticType> { static constexpr bool Value = false; };` — Disable auto-generated array nodes. CAT types are polymorphic/abstract and should not expose array variants in the MetaSound editor.

#### struct `Metasound::TEnableAutoArrayTypeRegistration`  
`template<> struct TEnableAutoArrayTypeRegistration<FChannelAgnosticType>`  
_L142-142_
- desc: Disable auto-generated array nodes. CAT types are polymorphic/abstract and should not expose array variants in the MetaSound editor.
- L139 _public member_ `template<> struct TEnableAutoArrayTypeRegistration<FChannelAgnosticType> { static constexpr bool Value = false; };` — Disable auto-generated array nodes. CAT types are polymorphic/abstract and should not expose array variants in the MetaSound editor.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L11 _namespace_ `namespace Metasound`
- L123 _namespace_ `namespace Metasound`
- L132 _prototype_ `DECLARE_METASOUND_POLY_TYPE(Metasound::FChannelAgnosticType, void, true);` (scope `Metasound`) — Declare Polymorphic DataTypes.
- L133 _prototype_ `DECLARE_METASOUND_POLY_TYPE(Metasound::FCompositeChannelAgnosticType, Metasound::FChannelAgnosticType, true);` (scope `Metasound`)
- L134 _prototype_ `DECLARE_METASOUND_POLY_TYPE(Metasound::FDiscreteChannelAgnosticType, Metasound::FChannelAgnosticType, true);` (scope `Metasound`)
- L135 _prototype_ `DECLARE_METASOUND_POLY_TYPE(Metasound::FSoundfieldChannelAgnosticType, Metasound::FChannelAgnosticType, true);` (scope `Metasound`)
- L144 _prototype_ `bool IsExperimentalPluginEnabled();` (scope `Metasound`) — Public helper.

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundConverterNodeRegistrationMacro.h` (Public)


#### Free symbols / members of external scopes

- L19 _function_ `bool RegisterConversionNode(const Metasound::FVertexName& FromPin, const Metasound::FVertexName& ToPin, const Metasound::FNodeClassMetadata& InNodeMetadata)` — `UE_DEPRECATED(5.8, "Converter node can be registered directly with the INodeClassRegistry in the owning modules startup/shutdown methods")`
- L21 _typedef_ `using FConverterNodeRegistryKey = ::Metasound::Frontend::FConverterNodeRegistryKey;` (scope `RegisterConversionNode`)
- L22 _typedef_ `using FConverterNodeInfo = ::Metasound::Frontend::FConverterNodeInfo;` (scope `RegisterConversionNode`)
- L52 _macro_ `#define MS_CONVERTER_BOOL(Node, FromDataType, ToDataType) MS_CONVERTER_BOOL_HIDDEN(Node, FromDataType, ToDataType)` — Convenience macro for token pasting the three parameters for the converter node into a unique static bool name:
- L53 _macro_ `#define MS_CONVERTER_BOOL_HIDDEN(Node, FromDataType, ToDataType) Node ## FromDataType ## ToDataType`
- L55 _macro_ `#define MS_INVOKE_CONVERTER_REGISTRATION_HIDDEN(NodeType, FromDataType, ToDataType, FromOutputPin, ToInputPin) FMetasoundFrontendRegistryContainer::Get()->EnqueueInitCommand([](){ ::Metasound::RegisterConversionNode<NodeType, FromDataType, `
- L57 _macro_ `#define MS_INVOKE_CONSTRUCTOR_REGISTRATION(NodeType, FromDataType, ToDataType, FromOutputPin, ToInputPin) MS_CONVERTER_BOOL(NodeType, FromDataType, ToDataType) = MS_INVOKE_CONVERTER_REGISTRATION_HIDDEN(NodeType, FromDataType, ToDataType, Fr`
- L61 _macro_ `#define REGISTER_METASOUND_CONVERTER(NodeType, FromDataType, ToDataType, FromOutputPin, ToInputPin) UE_DEPRECATED_MACRO(5.8, "REGISTER_METASOUND_CONVERTER will no longer be supported. Use explicit registration during module startup/shutdown` — This macro exposes a previously registered node as a valid way to convert from one datatype to another. When a user tries to connect a FromDataType output to a ToDataType input pin, this node will pop up as a potential node to insert between the two.

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundDataTypeRegistrationMacro.h` (Public)


#### struct `Metasound::TEnableAutoArrayTypeRegistration`  
`template<typename UnderlyingType> struct TEnableAutoArrayTypeRegistration<TVariable<UnderlyingType>>`  
_L41-44_
- desc: Disable registering of arrays of variables.
- L43 _public member_ `static constexpr bool Value = false;`

#### struct `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::TLiteralArrayEnum`  
`template<ELiteralType LiteralType> struct TLiteralArrayEnum`  
_L54-59_
- desc: Returns the Array version of a literal type if it exists.
- L58 _public member_ `static constexpr ELiteralType Value = ELiteralType::None;` — Default to TArray default constructor by using ELiteralType::None
- L65 _public member_ `static constexpr ELiteralType Value = ELiteralType::NoneArray;`
- L72 _public member_ `static constexpr ELiteralType Value = ELiteralType::BooleanArray;`
- L79 _public member_ `static constexpr ELiteralType Value = ELiteralType::IntegerArray;`
- L86 _public member_ `static constexpr ELiteralType Value = ELiteralType::FloatArray;`
- L93 _public member_ `static constexpr ELiteralType Value = ELiteralType::StringArray;`
- L100 _public member_ `static constexpr ELiteralType Value = ELiteralType::UObjectProxyArray;`

#### struct `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::TLiteralArrayEnum`  
`template<> struct TLiteralArrayEnum<ELiteralType::None>`  
_L63-66_
- desc: Specialization for None->NoneArray
- L58 _public member_ `static constexpr ELiteralType Value = ELiteralType::None;` — Default to TArray default constructor by using ELiteralType::None
- L65 _public member_ `static constexpr ELiteralType Value = ELiteralType::NoneArray;`
- L72 _public member_ `static constexpr ELiteralType Value = ELiteralType::BooleanArray;`
- L79 _public member_ `static constexpr ELiteralType Value = ELiteralType::IntegerArray;`
- L86 _public member_ `static constexpr ELiteralType Value = ELiteralType::FloatArray;`
- L93 _public member_ `static constexpr ELiteralType Value = ELiteralType::StringArray;`
- L100 _public member_ `static constexpr ELiteralType Value = ELiteralType::UObjectProxyArray;`

#### struct `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::TLiteralArrayEnum`  
`template<> struct TLiteralArrayEnum<ELiteralType::Boolean>`  
_L70-73_
- desc: Specialization for Boolean->BooleanArray
- L58 _public member_ `static constexpr ELiteralType Value = ELiteralType::None;` — Default to TArray default constructor by using ELiteralType::None
- L65 _public member_ `static constexpr ELiteralType Value = ELiteralType::NoneArray;`
- L72 _public member_ `static constexpr ELiteralType Value = ELiteralType::BooleanArray;`
- L79 _public member_ `static constexpr ELiteralType Value = ELiteralType::IntegerArray;`
- L86 _public member_ `static constexpr ELiteralType Value = ELiteralType::FloatArray;`
- L93 _public member_ `static constexpr ELiteralType Value = ELiteralType::StringArray;`
- L100 _public member_ `static constexpr ELiteralType Value = ELiteralType::UObjectProxyArray;`

#### struct `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::TLiteralArrayEnum`  
`template<> struct TLiteralArrayEnum<ELiteralType::Integer>`  
_L77-80_
- desc: Specialization for Integer->IntegerArray
- L58 _public member_ `static constexpr ELiteralType Value = ELiteralType::None;` — Default to TArray default constructor by using ELiteralType::None
- L65 _public member_ `static constexpr ELiteralType Value = ELiteralType::NoneArray;`
- L72 _public member_ `static constexpr ELiteralType Value = ELiteralType::BooleanArray;`
- L79 _public member_ `static constexpr ELiteralType Value = ELiteralType::IntegerArray;`
- L86 _public member_ `static constexpr ELiteralType Value = ELiteralType::FloatArray;`
- L93 _public member_ `static constexpr ELiteralType Value = ELiteralType::StringArray;`
- L100 _public member_ `static constexpr ELiteralType Value = ELiteralType::UObjectProxyArray;`

#### struct `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::TLiteralArrayEnum`  
`template<> struct TLiteralArrayEnum<ELiteralType::Float>`  
_L84-87_
- desc: Specialization for Float->FloatArray
- L58 _public member_ `static constexpr ELiteralType Value = ELiteralType::None;` — Default to TArray default constructor by using ELiteralType::None
- L65 _public member_ `static constexpr ELiteralType Value = ELiteralType::NoneArray;`
- L72 _public member_ `static constexpr ELiteralType Value = ELiteralType::BooleanArray;`
- L79 _public member_ `static constexpr ELiteralType Value = ELiteralType::IntegerArray;`
- L86 _public member_ `static constexpr ELiteralType Value = ELiteralType::FloatArray;`
- L93 _public member_ `static constexpr ELiteralType Value = ELiteralType::StringArray;`
- L100 _public member_ `static constexpr ELiteralType Value = ELiteralType::UObjectProxyArray;`

#### struct `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::TLiteralArrayEnum`  
`template<> struct TLiteralArrayEnum<ELiteralType::String>`  
_L91-94_
- desc: Specialization for String->StringArray
- L58 _public member_ `static constexpr ELiteralType Value = ELiteralType::None;` — Default to TArray default constructor by using ELiteralType::None
- L65 _public member_ `static constexpr ELiteralType Value = ELiteralType::NoneArray;`
- L72 _public member_ `static constexpr ELiteralType Value = ELiteralType::BooleanArray;`
- L79 _public member_ `static constexpr ELiteralType Value = ELiteralType::IntegerArray;`
- L86 _public member_ `static constexpr ELiteralType Value = ELiteralType::FloatArray;`
- L93 _public member_ `static constexpr ELiteralType Value = ELiteralType::StringArray;`
- L100 _public member_ `static constexpr ELiteralType Value = ELiteralType::UObjectProxyArray;`

#### struct `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::TLiteralArrayEnum`  
`template<> struct TLiteralArrayEnum<ELiteralType::UObjectProxy>`  
_L98-101_
- desc: Specialization for UObjectProxy->UObjectProxyArray
- L58 _public member_ `static constexpr ELiteralType Value = ELiteralType::None;` — Default to TArray default constructor by using ELiteralType::None
- L65 _public member_ `static constexpr ELiteralType Value = ELiteralType::NoneArray;`
- L72 _public member_ `static constexpr ELiteralType Value = ELiteralType::BooleanArray;`
- L79 _public member_ `static constexpr ELiteralType Value = ELiteralType::IntegerArray;`
- L86 _public member_ `static constexpr ELiteralType Value = ELiteralType::FloatArray;`
- L93 _public member_ `static constexpr ELiteralType Value = ELiteralType::StringArray;`
- L100 _public member_ `static constexpr ELiteralType Value = ELiteralType::UObjectProxyArray;`

#### struct `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::GetEnumDataTypeInterface::FEnumHandler`  
`struct FEnumHandler : Metasound::Frontend::IEnumDataTypeInterface`  
_L260-288_
- inherits: `Metasound::Frontend::IEnumDataTypeInterface`
- L262 _public function_ `FName GetNamespace() const override`
- L267 _public function_ `int32 GetDefaultValue() const override`
- L272 _public function_ `const TArray<FGenericInt32Entry>& GetAllEntries() const override`

#### struct `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::HasRawParameterAssignmentOp`  
`template <typename T, typename V = void> struct HasRawParameterAssignmentOp`  
_L297-297_
- L297 _public member_ `template <typename T, typename V = void> struct HasRawParameterAssignmentOp { bool value = false; };`
- L300 _public member_ `template <typename T> struct HasRawParameterAssignmentOp<T, decltype(&T::AssignRawParameter, void())> { bool value = true; };`

#### struct `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::HasRawParameterAssignmentOp`  
`template <typename T> struct HasRawParameterAssignmentOp<T, decltype(&T::AssignRawParameter, void())>`  
_L300-300_
- L297 _public member_ `template <typename T, typename V = void> struct HasRawParameterAssignmentOp { bool value = false; };`
- L300 _public member_ `template <typename T> struct HasRawParameterAssignmentOp<T, decltype(&T::AssignRawParameter, void())> { bool value = true; };`

#### class `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::FDataTypeRegistryEntryBase`  
`class FDataTypeRegistryEntryBase : public IDataTypeRegistryEntry`  
_L303-376_
- inherits: `IDataTypeRegistryEntry`
- desc: Base registry entry for any data type
- L306 _public prototype_ `FDataTypeRegistryEntryBase(const Frontend::FDataTypeRegistryInfo& Info, const TSharedPtr<Frontend::IEnumDataTypeInterface>& EnumInterface);`
- L309 _public prototype_ `virtual const Frontend::FDataTypeRegistryInfo& GetDataTypeInfo() const override;`
- L310 _public prototype_ `virtual TSharedPtr<const Frontend::IEnumDataTypeInterface> GetEnumInterface() const override;`
- L311 _public prototype_ `virtual TSharedPtr<IPolymorphicDataTypeInterface> GetPolymorphicInterface() const override;`
- L312 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendInputClass() const override;`
- L313 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetInputClassMetadata() const override;`
- L314 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendConstructorInputClass() const override;`
- L315 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetConstructorInputClassMetadata() const override;`
- L316 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendLiteralClass() const override;`
- L317 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendOutputClass() const override;`
- L318 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetOutputClassMetadata() const override;`
- L319 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendConstructorOutputClass() const override;`
- L320 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetConstructorOutputClassMetadata() const override;`
- L321 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendVariableClass() const override;`
- L322 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetVariableClassMetadata() const override;`
- L323 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendVariableMutatorClass() const override;`
- L324 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetVariableMutatorClassMetadata() const override;`
- L325 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendVariableAccessorClass() const override;`
- L326 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetVariableAccessorClassMetadata() const override;`
- L327 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendVariableDeferredAccessorClass() const override;`
- L328 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetVariableDeferredAccessorClassMetadata() const override;`
- L329 _public prototype_ `virtual const Frontend::IParameterAssignmentFunction& GetRawAssignmentFunction() const override;`
- L330 _public prototype_ `virtual Frontend::FLiteralAssignmentFunction GetLiteralAssignmentFunction() const override;`
- L331 _public prototype_ `virtual TUniquePtr<INode> CreateOutputNode(FNodeData InNodeData) const override;`
- L332 _public prototype_ `virtual TUniquePtr<INode> CreateConstructorOutputNode(FNodeData InNodeData) const override;`
- L335 _protected member_ `Frontend::FDataTypeRegistryInfo Info;`
- L336 _protected member_ `FMetasoundFrontendClass InputClass;`
- L337 _protected member_ `TSharedPtr<const FNodeClassMetadata> InputClassMetadata;`
- L338 _protected member_ `FMetasoundFrontendClass ConstructorInputClass;`
- L339 _protected member_ `TSharedPtr<const FNodeClassMetadata> ConstructorInputClassMetadata;`
- L340 _protected member_ `FMetasoundFrontendClass OutputClass;`
- L341 _protected member_ `TSharedPtr<const FNodeClassMetadata> OutputClassMetadata;`
- L342 _protected member_ `FMetasoundFrontendClass ConstructorOutputClass;`
- L343 _protected member_ `TSharedPtr<const FNodeClassMetadata> ConstructorOutputClassMetadata;`
- L345 _protected member_ `FMetasoundFrontendClass LiteralClass;`
- L347 _protected member_ `FMetasoundFrontendClass VariableClass;`
- L348 _protected member_ `TSharedPtr<const FNodeClassMetadata> VariableClassMetadata;`
- L349 _protected member_ `FMetasoundFrontendClass VariableMutatorClass;`
- L350 _protected member_ `TSharedPtr<const FNodeClassMetadata> VariableMutatorClassMetadata;`
- L351 _protected member_ `FMetasoundFrontendClass VariableAccessorClass;`
- L352 _protected member_ `TSharedPtr<const FNodeClassMetadata> VariableAccessorClassMetadata;`
- L353 _protected member_ `FMetasoundFrontendClass VariableDeferredAccessorClass;`
- L354 _protected member_ `TSharedPtr<const FNodeClassMetadata> VariableDeferredAccessorClassMetadata;`
- L355 _protected member_ `TSharedPtr<Frontend::IEnumDataTypeInterface> EnumInterface;`
- L356 _protected member_ `TSharedPtr<IPolymorphicDataTypeInterface> PolymorphicInterface;`
- L357 _protected member_ `Frontend::IParameterAssignmentFunction RawAssignmentFunction;`
- L358 _protected member_ `Frontend::FLiteralAssignmentFunction LiteralAssignmentFunction = nullptr;`
- L360 _protected typedef_ `typedef void CreateNodeClassMetadataFunc();`
- L362 _protected prototype_ `void InitNodeClassesBase( const FNodeClassMetadata& InputClassMetadata, const FNodeClassMetadata& OutputClassMetadata, const FNodeClassMetadata& LiteralPrototypeMetadata, const FNodeClassMetadata& VariableClassMetadata, const FNodeClassMetadata& VariableMutatorClassMetadata, const FNodeClassMetadata& VariableAccessorClassMetadata, const FNodeClassMetadata& VariableDeferredAccessorClassMetadata );`
- L372 _protected prototype_ `void InitNodeClassesBaseConstructor( const FNodeClassMetadata& ConstructorInputClassMetadata, const FNodeClassMetadata& ConstructorOutputClassMetadata );`

#### class `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::RegisterDataTypeWithFrontendInternal::FDataTypeRegistryEntry`  
`class FDataTypeRegistryEntry : public FDataTypeRegistryEntryBase`  
_L396-663_
- inherits: `FDataTypeRegistryEntryBase`
- L398 _private function_ `void InitRawAssignmentFunction()`
- L432 _private function_ `void InitLiteralAssignmentFunction()`
- L443 _private function_ `void InitNodeClasses()`
- L472 _private function_ `void InitPolymorphicInterface()`
- L487 _public function_ `FDataTypeRegistryEntry() : FDataTypeRegistryEntryBase(CreateDataTypeInfo<TDataType, PreferredArgType, UClassToUse>(), GetEnumDataTypeInterface<TDataType>())`
- L498 _public function_ `virtual TUniquePtr<INode> CreateInputNode(FNodeData InNodeData) const override`
- L515 _public function_ `virtual TUniquePtr<INode> CreateConstructorInputNode(FNodeData InNodeData) const override`
- L533 _public function_ `virtual TUniquePtr<INode> CreateLiteralNode(FLiteralNodeConstructorParams&& InParams) const override` — `UE_DEPRECATED(5.6, "Direct creation of literal nodes will no longer be supported")`
- L546 _public function_ `virtual TUniquePtr<INode> CreateReceiveNode(const FNodeInitData& InParams) const override` — `UE_DEPRECATED(5.6, "Direct creation of receive nodes will no longer be supported")`
- L560 _public function_ `virtual TUniquePtr<INode> CreateVariableNode(FLiteral InLiteral, FNodeData InNodeData) const override`
- L572 _public function_ `virtual TUniquePtr<INode> CreateVariableMutatorNode(FNodeData InNodeData) const override`
- L584 _public function_ `virtual TUniquePtr<INode> CreateVariableAccessorNode(FNodeData InNodeData) const override`
- L596 _public function_ `virtual TUniquePtr<INode> CreateVariableDeferredAccessorNode(FNodeData InNodeData) const override`
- L608 _public function_ `virtual TSharedPtr<Audio::IProxyData> CreateProxy(UObject* InObject) const override`
- L630 _public function_ `virtual TOptional<FAnyDataReference> CreateDataReference(EDataReferenceAccessType InAccessType, const FLiteral& InLiteral, const FOperatorSettings& InOperatorSettings) const override`
- L652 _public function_ `virtual TSharedPtr<IDataChannel, ESPMode::ThreadSafe> CreateDataChannel(const FOperatorSettings& InOperatorSettings) const override`

#### struct `Metasound::Frontend::TMetasoundDataTypeRegistration`  
`template<typename DataType> struct TMetasoundDataTypeRegistration`  
_L813-822_
- desc: Registration info for a data type. @tparam DataType - The data type to be registered.
- L818 _public member_ `static constexpr bool bCanRegister = TInputNode<DataType, EVertexAccessType::Reference>::bCanRegister;` — To register a data type, an input node must be able to instantiate it.
- L821 _public member_ `static const bool bSuccessfullyRegistered = false;` — This is no longer used.

#### Free symbols / members of external scopes

- L35 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L37 _namespace_ `namespace Metasound`
- L47 _namespace_ `namespace Metasound`
- L47 _namespace_ `namespace Frontend` (scope `Metasound`)
- L50 _namespace_ `namespace MetasoundDataTypeRegistrationPrivate` (scope `Metasound::Frontend`)
- L106 _function_ `template<typename TDataType> void RegisterSendAndReceiveNodes(const FModuleInfo& InModuleInfo)` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate`) — Register the send and receive nodes of a datatype if it is supported
- L118 _prototype_ `void UnregisterSendAndReceiveNodes(const FName& InDataTypeName, const FModuleInfo& InModuleInfo);` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate`) — Unregister the send and receive nodes related to a datatype.
- L122 _function_ `template<typename TFromDataType, typename TToDataType> void RegisterAutoConverterNode(INodeClassRegistry& InRegistry, const FModuleInfo& InModuleInfo)` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate`) — Register an autoconverter node for a specific data type conversion. Only registers the node if it is supported and not already registered.
- L137 _typedef_ `using FConverterNode = Metasound::TAutoConverterNode<TFromDataType, TToDataType>;` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::RegisterAutoConverterNode`)
- L153 _prototype_ `void UnregisterAutoConverterNode(INodeClassRegistry& InRegistry, const FName& InFromDataTypeName, const FName& InToDataTypeName, const FModuleInfo& InModuleInfo);` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate`) — Unregister any autoconverter node that is registered for going converting between specific data types
- L157 _function_ `template<typename TDataType> void RegisterAutoConverterNodes(const FModuleInfo& InModuleInfo)` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate`) — Register a slew of basic converter nodes for basic types
- L175 _prototype_ `void UnregisterAutoConverterNodes(const FName& InDataTypeName, const FModuleInfo& InModuleInfo);` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate`) — Unregister a slew of basic converter nodes for basic types.
- L184 _function_ `template<typename TDataType, ELiteralType PreferredArgType, typename UClassToUse> Frontend::FDataTypeRegistryInfo CreateDataTypeInfo()` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate`) — Creates the FDataTypeRegistryInfo for a data type. @tparam TDataType - The data type to create info for. @tparam PreferredArgType - The preferred constructor argument type to use when creating an instance of the data type. @tparam UClassToUse - The preferred UObject class to use when constructing from an Audio::IProxyData.
- L231 _typedef_ `using Base = typename TPolymorphicTraits<TDataType>::BaseType;` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::CreateDataTypeInfo`)
- L248 _function_ `template<typename TDataType> TSharedPtr<Frontend::IEnumDataTypeInterface> GetEnumDataTypeInterface()` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate`) — Returns an IEnumDataTypeInterface pointer for the data type. If the data type has no IEnumDataTypeInterface, the returned pointer will be invalid. @tparam TDataType - The data type to create the interface for. @return A shared pointer to the IEnumDataTypeInterface. If the TDataType does not have an IEnumDataTypeInterface, returns an invalid pointer.
- L252 _typedef_ `using FEnumTraits = TEnumTraits<TDataType>;` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::GetEnumDataTypeInterface`)
- L257 _typedef_ `using InnerType = typename FEnumTraits::InnerType;` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::GetEnumDataTypeInterface`)
- L258 _typedef_ `using FStringHelper = TEnumStringHelper<InnerType>;` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::GetEnumDataTypeInterface`)
- L275 _function_ `` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::GetEnumDataTypeInterface::FEnumHandler::GetAllEntries`)
- L391 _function_ `template<typename TDataType, ELiteralType PreferredArgType = ELiteralType::None, typename UClassToUse = void> bool RegisterDataTypeWithFrontendInternal(const FModuleInfo& InModuleInfo)` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate`) — Registers a data type with the MetaSound Frontend. This allows the data type to be used in Input and Output nodes by informing the Frontend how to instantiate an instance. @tparam TDataType - The data type to register. @tparam PreferredArgType - The preferred constructor argument type to use when creating an instance of the data type. @tparam UClassToUse - The preferred UObject class to use when constructing from an Audio::IProxyDataPtr. If the type is not constructible with an Audio::IProxyDataPtr, then this should be void. @return True on success, false on failure.
- L402 _function_ `this->RawAssignmentFunction = [](const void* src, void* dest)` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::RegisterDataTypeWithFrontendInternal::FDataTypeRegistryEntry::InitRawAssignmentFunction`)
- L409 _function_ `` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::RegisterDataTypeWithFrontendInternal::FDataTypeRegistryEntry::InitRawAssignmentFunction`)
- L419 _typedef_ `using FSmallFixedArray = TParamPackFixedArray<typename TDataType::ElementType, 1>;` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::RegisterDataTypeWithFrontendInternal::FDataTypeRegistryEntry::InitRawAssignmentFunction::__anon546c60f50402`) — sanity check to be sure memory layout is the same regardless of number of elements in the fixed array...
- L420 _typedef_ `using FLargeFixedArray = TParamPackFixedArray<typename TDataType::ElementType, 200>;` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::RegisterDataTypeWithFrontendInternal::FDataTypeRegistryEntry::InitRawAssignmentFunction::__anon546c60f50402`)
- L437 _function_ `` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::RegisterDataTypeWithFrontendInternal::FDataTypeRegistryEntry::InitLiteralAssignmentFunction`)
- L474 _typedef_ `using FPolyTraits = TPolymorphicTraits<TDataType>;` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::RegisterDataTypeWithFrontendInternal::FDataTypeRegistryEntry::InitPolymorphicInterface`)
- L477 _typedef_ `using BaseType = FPolyTraits::BaseType;` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::RegisterDataTypeWithFrontendInternal::FDataTypeRegistryEntry::InitPolymorphicInterface`)
- L683 _prototype_ `bool UnregisterDataTypeWithFrontendInternal(const FName& InDataTypeName, const FModuleInfo& InModuleInfo);` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate`) — Unregister a datatype as well as some autogenerated nodes. This should unregister all nodes that were registered during RegisterDataTypeWIthFrontendInternal<>(...)
- L697 _function_ `template<typename TDataType, ELiteralType PreferredArgType> bool RegisterDataTypeArrayWithFrontend(const FModuleInfo& InModuleInfo)` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate`) — Registers an array of a data type with the MetaSound Frontend. This allows an array of the data type to be used in Input, Output, Send and Receive nodes by informing the Frontend how to instantiate an instance. @tparam TDataType - The data type to register. @tparam PreferredArgType - The preferred constructor argument type to use when creating an instance of the data type. @tparam UClassToUse - The preferred UObject class to use when constructing from an Audio::IProxyDataPtr. If the type is not constructible with an Audio::IProxyDataPtr, then this should be void. @return True on success, false on failure.
- L700 _typedef_ `using TArrayType = TArray<TDataType>;` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::RegisterDataTypeArrayWithFrontend`)
- L716 _function_ `template<typename TDataType> bool UnregisterDataTypeArrayWithFrontend(const FModuleInfo& InModuleInfo)` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate`)
- L722 _typedef_ `using TArrayType = TArray<TDataType>;` (scope `Metasound::Frontend::MetasoundDataTypeRegistrationPrivate::UnregisterDataTypeArrayWithFrontend`)
- L754 _function_ `template<typename TDataType, ELiteralType PreferredArgType = ELiteralType::None, typename UClassToUse = void> bool RegisterDataType(const FModuleInfo& InModuleInfo)` (scope `Metasound::Frontend`) — Registers a data type with the MetaSound Frontend. This allows the data type to be used in Input, Output, Send and Receive  nodes by informing the Frontend how to instantiate an instance. @tparam TDataType - The data type to register. @tparam PreferredArgType - The preferred constructor argument type to use when creating an instance of the data type. @tparam UClassToUse - The preferred UObject class to use when constructing from an Audio::IProxyDataPtr. If the type is not constructible with an Audio::IProxyDataPtr, then this should be void. @return True on success, false on failure.
- L775 _function_ `template<typename TDataType> bool UnregisterDataType(const FModuleInfo& InModuleInfo)` (scope `Metasound::Frontend`) — Unregisters a data type with the MetaSound Frontend. @tparam TDataType - The data type to register. @return True on success, false on failure.
- L802 _function_ `bool RegisterDataType()` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.7, "Use RegisterDataType(const FModuleInfo&) instead")`
- L825 _namespace_ `namespace Metasound`
- L828 _typedef_ `template<typename DataType> using TMetasoundDataTypeRegistration UE_DEPRECATED(5.6, "Use Frontend::TMetasoundDataTypeRegistration") = Fronten` (scope `Metasound`)
- L832 _function_ `bool RegisterDataTypeWithFrontend()` (scope `Metasound`) — `UE_DEPRECATED(5.6, "Use Frontend::RegisterDataType instead")`
- L839 _macro_ `#define CANNOT_REGISTER_METASOUND_DATA_TYPE_ASSERT_STRING(DataType) \`
- L856 _macro_ `#define ENQUEUE_METASOUND_DATATYPE_REGISTRATION_COMMAND(DataType, DataTypeName, ...) \`
- L869 _macro_ `#define REGISTER_METASOUND_DATATYPE(DataType, DataTypeName, ...) \` — This should be used to expose a datatype as a potential input or output for a metasound graph. The first argument to the macro is the class to expose. the second argument is the display name of that type in the Metasound editor. Optionally, a Metasound::ELiteralType can be passed in to designate a preferred literal type- For example, if Metasound::ELiteralType::Float is passed in, we will default to using a float parameter to create this datatype. If no argument is passed in, we will infer a literal type to use. If Metasound::ELiteralType::Invalid can be used to enforce that we don't provide space for a literal, in which case you should have a default constructor or a constructor that takes [const FOperatorSettings&] implemented. If you pass in a preferred arg type, please make sure that the passed in datatype has a matching constructor, since we won't check this until runtime.
- L874 _macro_ `#define DISABLE_METASOUND_ARRAYS_FOR_TYPE(TYPENAME)\` — Helper macro for disabling auto array registration

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundDocumentInterface.h` (Public)


#### class `UMetaSoundDocumentInterface`  
`class UMetaSoundDocumentInterface : public UInterface`  
_L25-28_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (DisplayName = "MetaSound Document Interface", CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: UInterface for all MetaSound UClasses that implement a MetaSound document as a means for accessing data via code, scripting, execution, or node class generation.

#### class `IMetaSoundDocumentInterface`  
`class IMetaSoundDocumentInterface : public IInterface`  
_L30-67_
- inherits: `IInterface`
- L35 _public prototype_ `virtual FTopLevelAssetPath GetAssetPathChecked() const = 0;`
- L39 _public prototype_ `virtual const FMetasoundFrontendDocument& GetConstDocument() const = 0;` — Returns read-only reference to the the MetaSoundFrontendDocument containing all MetaSound runtime & editor data.
- L42 _public prototype_ `virtual const UClass& GetBaseMetaSoundUClass() const = 0;` — Returns the parent class registered with the MetaSound UObject registry.
- L45 _public prototype_ `virtual const UClass& GetBuilderUClass() const = 0;` — Returns the builder class used to modify the given document.
- L48 _public prototype_ `virtual EMetasoundFrontendClassAccessFlags GetDefaultAccessFlags() const = 0;` — Returns the default access flags utilized when document is initialized.
- L52 _public prototype_ `virtual bool ConformObjectToDocument() = 0;` — Conforms UProperty data outside the Frontend Document Model to the document's data. Returns whether or not object data was modified.
- L55 _public prototype_ `virtual bool IsActivelyBuilding() const = 0;` — Returns whether or not a document builder is currently active and can mutate the given interface's document
- L58 _private prototype_ `virtual FMetasoundFrontendDocument& GetDocument() = 0;`
- L63 _private prototype_ `virtual void OnBeginActiveBuilder() = 0;` — Derived classes can implement these methods to react to a builder beginning or finishing. Begin and Finish are tied to the lifetime of the active FMetaSoundFrontendDocumentBuilder.
- L64 _private prototype_ `virtual void OnFinishActiveBuilder() = 0;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L70 _namespace_ `namespace Metasound`
- L70 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundDynamicInterfaceNodeConfiguration.h` (Public)


#### struct `FMetaSoundDynamicInterfaceNodeConfiguration`  
`struct FMetaSoundDynamicInterfaceNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L29-44_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- desc: Built-in FMetaSoundFrontendNodeConfiguration subclass that stores sub-interface instance counts and variant type selections as serializable UPROPERTY data. Node developers who declare a FClassInterface with sub-interfaces and/or variants can use this configuration type (or have it auto-applied) instead of writing a custom configuration subclass. Sub-interface counts are stored as a map of sub-interface name to instance count. Variant selections are stored as a map of variant name to data type name. OverrideDefaultInterface() looks up the FClassInterface from the node registry and calls CreateVertexInterface() with the stored configurations, producing a FMetasoundFrontendClassInterface with the correct vertex layout.
- L35 _public member_ `TMap<FName, uint32> SubInterfaceCounts;` — `UPROPERTY()` — Sub-interface instance counts, keyed by sub-interface name.
- L39 _public member_ `TMap<FName, FName> VariantSelections;` — `UPROPERTY()` — Variant type selections, keyed by variant name.
- L41 _public prototype_ `virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const override;`
- L43 _public prototype_ `virtual TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDFRONTEND_API`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundEnum.h` (Public)


#### struct `Metasound::TEnumEntry`  
`template<typename T> struct TEnumEntry`  
_L41-59_
- desc: Struct to hold each of the entries of the Enum.
- L43 _public member_ `T Value;`
- L44 _public member_ `FName Name;`
- L46 _public member_ `FText DisplayName;`
- L47 _public member_ `FText Tooltip;`
- L51 _public function_ `operator TEnumEntry<int32>() const` — Allow implicit conversion to int32 entry

#### struct `Metasound::TEnumStringHelperBase`  
`template<typename Derived, typename EnumType> struct TEnumStringHelperBase`  
_L65-101_
- desc: CRTP base class for Enum String Helper type. Provides common code for all specializations.
- L68 _public function_ `static TOptional<FName> ToName(EnumType InValue)` — Give a enum value e.g. 'EMyEnum::One', convert that to a Name (if its valid)
- L80 _public function_ `static TOptional<EnumType> FromName(const FName InName)` — Give a Name "EMyEnum::One", convert that to a Enum Value
- L92 _public function_ `static TArray<FName> GetAllNames()` — Return all possible names.

#### struct `Metasound::TEnumStringHelper`  
`template<typename T> struct TEnumStringHelper : TEnumStringHelperBase<TEnumStringHelper<T>, T>`  
_L106-109_
- inherits: `TEnumStringHelperBase<TEnumStringHelper<T>,T>`
- desc: Metasound Enum String Helper

#### class `Metasound::TEnum`  
`template<typename EnumType, EnumType DefaultValue> class TEnum final`  
_L114-268_
- desc: Metasound Enum Wrapper
- L117 _public typedef_ `using InnerType = EnumType;`
- L118 _public typedef_ `using SerializedType = int32;`
- L119 _public typedef_ `using UnderlyingType = std::underlying_type_t<EnumType>;`
- L121 _public function_ `static constexpr bool EnumTypeIsSupported()`
- L160 _public prototype_ `static_assert(EnumTypeIsSupported(), "Enu`
- L163 _public function_ `explicit TEnum(EnumType InValue = DefaultValue)` — Default.
- L187 _public function_ `explicit TEnum(int32 InIntValue) : TEnum(static_cast<EnumType>(InIntValue))` — From Int32 (this is the common path from a Literal).
- L193 _public function_ `explicit TEnum(FName InValueName)` — From Name
- L218 _public function_ `explicit TEnum(const FString& InString) : TEnum(FName(*InString))` — Slow, construct from FString to FName.
- L223 _public function_ `EnumType Get() const`
- L228 _public function_ `int32 ToInt() const`
- L234 _public function_ `TOptional<FName> ToName() const` — Convert to its FName (if possible).
- L240 _public function_ `operator EnumType() const` — Conversion operator to automatically convert this to its underlying enum type.
- L246 _public function_ `static TOptional<FName> ToName(EnumType InValue)` — Convert from EnumValue to FName (if possible).
- L252 _public function_ `static TOptional<EnumType> NameToEnum(FName InValue)` — Convert from Name to EnumValue (if possible).
- L258 _public function_ `static TArray<FName> GetAllNames()` — Return all possible Names
- L265 _private member_ `EnumType EnumValue = DefaultValue;` — Keep the type in its fully typed form for debugging.
- L267 _private member_ `static bool bHasWarnedNameToEnumConversionFailure;`

#### struct `Metasound::TEnumTraits`  
`template<typename T> struct TEnumTraits`  
_L274-279_
- L276 _public member_ `static constexpr bool bIsEnum = false;`
- L277 _public typedef_ `using InnerType = int32;`
- L278 _public member_ `static constexpr int32 DefaultValue = 0;`
- L284 _public member_ `static constexpr bool bIsEnum = true;`
- L285 _public typedef_ `using InnerType = T;`
- L286 _public member_ `static constexpr T DefaultValue = D;`

#### struct `Metasound::TEnumTraits`  
`template<typename T, T D> struct TEnumTraits<TEnum<T, D>>`  
_L282-287_
- L276 _public member_ `static constexpr bool bIsEnum = false;`
- L277 _public typedef_ `using InnerType = int32;`
- L278 _public member_ `static constexpr int32 DefaultValue = 0;`
- L284 _public member_ `static constexpr bool bIsEnum = true;`
- L285 _public typedef_ `using InnerType = T;`
- L286 _public member_ `static constexpr T DefaultValue = D;`

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace Metasound`
- L174 _function_ `Algo::Transform(GetAllNames(), ValueStrings, [](const FName& Name) { return Name.ToString(); });` (scope `Metasound::TEnum::TEnum`)
- L271 _member_ `template<typename EnumType, EnumType DefaultValue> bool TEnum<EnumType, DefaultValue>::bHasWarnedNameToEnumConversionFailure = false;` (scope `Metasound::TEnum<EnumType, DefaultValue>`)
- L309 _macro_ `#define DECLARE_METASOUND_ENUM(ENUMNAME, DEFAULT, API, ENUMTYPEDEF, TYPEINFO, READREF, WRITEREF)\` — DECLARE_METASOUND_ENUM @param ENUMNAME - The typename of your EnumType you want to use for Metasounds. e.g. MyEnum @param DEFAULT - A fully qualified default Enum value. e.g. EMyEnum::One @param API - The module API this is declared inside e.g. METASOUNDSTANDARDNODES_API @param ENUMTYPEDEF - The name of the TEnum<YourType> wrapper type @param TYPEINFO - The name of the TypeInfo type you want to define e.g. FMyEnumTypeInfo @param READREF - The name of the Read Reference type you want to define. e.g FMyEnumReadRef @param WRITEREF -The name of the Write Reference type you want to define e.g. FMyEnumWriteRef

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundEnumRegistrationMacro.h` (Public)


#### struct `Metasound::TEnableAutoConverterNodeRegistration`  
`template<typename FromDataType, typename EnumType, EnumType DefaultValue> struct TEnableAutoConverterNodeRegistration<FromDataType, TEnum<EnumType, DefaultValue>>`  
_L14-17_
- desc: Enable registration of converter nodes which convert from int32 to enums
- L16 _public member_ `static constexpr bool Value = std::is_same<int32, FromDataType>::value;`
- L23 _public member_ `static constexpr bool Value = std::is_same<int32, ToDataType>::value;`

#### struct `Metasound::TEnableAutoConverterNodeRegistration`  
`template<typename ToDataType, typename EnumType, EnumType DefaultValue> struct TEnableAutoConverterNodeRegistration<TEnum<EnumType, DefaultValue>, ToDataType>`  
_L21-24_
- desc: Enable registration of converter nodes which convert from enums to int32
- L16 _public member_ `static constexpr bool Value = std::is_same<int32, FromDataType>::value;`
- L23 _public member_ `static constexpr bool Value = std::is_same<int32, ToDataType>::value;`

#### struct `Metasound::TEnableAutoArrayTypeRegistration`  
`template<typename EnumType, EnumType DefaultValue> struct TEnableAutoArrayTypeRegistration<TEnum<EnumType, DefaultValue>>`  
_L28-31_
- desc: Disable arrays of enums
- L30 _public member_ `static constexpr bool Value = false;`

#### struct `Metasound::TEnableArrayNodes`  
`template<typename EnumType, EnumType DefaultValue> struct TEnableArrayNodes<TEnum<EnumType, DefaultValue>>`  
_L35-38_
- desc: Disable array nodes of enums
- L37 _public member_ `static constexpr bool Value = false;`

#### struct `Metasound::TEnableTransmissionNodeRegistration`  
`template<typename EnumType, EnumType DefaultValue> struct TEnableTransmissionNodeRegistration<TEnum<EnumType, DefaultValue>>`  
_L42-46_
- desc: Specialization of TIsTransmittable<> to disable transmission of enums.
- L45 _public member_ `static constexpr bool Value = false;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Metasound`
- L54 _macro_ `#define DEFINE_METASOUND_ENUM_BEGIN(ENUMNAME,ENUMTYPEDEF,DATATYPENAMESTRING)\` — DEFINE_METASOUND_ENUM_BEGIN @param ENUMNAME - The typename of your raw EnumType you want to use for Metasounds. e.g. EMyType @param ENUMTYPEDEF - The name of the TEnum<YourType> wrapper type @param DATATYPENAMESTRING - The string that will the data type name "Enum:<string>" e.g. "MyEnum"
- L68 _macro_ `#define DEFINE_METASOUND_ENUM_ENTRY(ENTRY, DISPLAYNAME_KEY, DISPLAYNAME, TOOLTIP_KEY, TOOLTIP) { ENTRY, TEXT(#ENTRY), LOCTEXT(DISPLAYNAME_KEY, DISPLAYNAME), LOCTEXT(TOOLTIP_KEY, TOOLTIP) }`
- L69 _macro_ `#define DEFINE_METASOUND_ENUM_ENTRY_NOTOOLTIP(ENTRY, DISPLAYNAME_KEY, DISPLAYNAME) { ENTRY, TEXT(#ENTRY), LOCTEXT(DISPLAYNAME_KEY, DISPLAYNAME) }`
- L71 _macro_ `#define DEFINE_METASOUND_ENUM_ENTRY(ENTRY, DISPLAYNAME_KEY, DISPLAYNAME, TOOLTIP_KEY, TOOLTIP) { ENTRY, TEXT(#ENTRY) }`
- L72 _macro_ `#define DEFINE_METASOUND_ENUM_ENTRY_NOTOOLTIP(ENTRY, DISPLAYNAME_KEY, DISPLAYNAME) { ENTRY, TEXT(#ENTRY) }`
- L77 _macro_ `#define DEFINE_METASOUND_ENUM_END() \` — DEFINE_METASOUND_ENUM_END - macro which ends the function body of the GetAllEntries function

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontend.h` (Public)


#### struct `Metasound::Frontend::FConnectability`  
`struct FConnectability`  
_L92-118_
- desc: Struct that indicates whether an input and an output can be connected, and whether an intermediate node is necessary to connect the two.
- L109 _public member_ `EConnectable Connectable = EConnectable::No;`
- L111 _public member_ `EReason Reason = EReason::None;`
- L117 _public member_ `TArray<FConverterNodeInfo> PossibleConverterNodeClasses;` — If Connectable is EConnectable::YesWithConverterNode, this will be a populated list of nodes we can use to convert between the input and output.

#### enum `Metasound::Frontend::FConnectability::EConnectable`  
`enum class EConnectable`  
_L94-99_
- L96 _public enumerator_ `Yes`
- L97 _public enumerator_ `No`
- L98 _public enumerator_ `YesWithConverterNode`

#### enum `Metasound::Frontend::FConnectability::EReason`  
`enum class EReason : uint8`  
_L101-107_
- L103 _public enumerator_ `None`
- L104 _public enumerator_ `IncompatibleDataTypes`
- L105 _public enumerator_ `CausesLoop`
- L106 _public enumerator_ `IncompatibleAccessTypes`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Metasound`
- L18 _namespace_ `namespace Frontend` (scope `Metasound`)
- L26 _prototype_ `FMetasoundFrontendClass GenerateClass(const FNodeClassMetadata& InNodeMetadata, EMetasoundFrontendClassType ClassType=EMetasoundFrontendClassType::External);` (scope `Metasound::Frontend`) — Generates a new FMetasoundFrontendClass from Node Metadata @param InNodeMetadata - Metadata describing an external node. @return FrontendClass for natively-defined node.
- L34 _prototype_ `FMetasoundFrontendClass GenerateClass(const Metasound::Frontend::FNodeRegistryKey& InKey);` (scope `Metasound::Frontend`) — Generates a new FMetasoundFrontendClass from node lookup info. @param InInfo - Class info for a already registered external node. @return FrontendClass for natively-defined node.
- L44 _function_ `template<typename NodeType> FMetasoundFrontendClass GenerateClass(const FNodeInitData& InNodeInitData)` (scope `Metasound::Frontend`) — Generates a new FMetasoundFrontendClass from Node init data @tparam NodeType - Type of node to instantiate. @param InNodeInitData - Data used to call constructor of node. @return FrontendClass for natively-defined node.
- L63 _function_ `template<typename NodeType> FMetasoundFrontendClass GenerateClass()` (scope `Metasound::Frontend`) — Generates a new FMetasoundFrontendClass from a NodeType @tparam NodeType - Type of node. @return FrontendClass for natively-defined node.
- L73 _prototype_ `bool ImportJSONToMetasound(const FString& InJSON, FMetasoundFrontendDocument& OutMetasoundDocument);` (scope `Metasound::Frontend`) — Takes a JSON string and deserializes it into a Metasound document struct. @returns false if the file couldn't be found or parsed into a document.
- L77 _prototype_ `bool ImportJSONAssetToMetasound(const FString& InPath, FMetasoundFrontendDocument& OutMetasoundDocument);` (scope `Metasound::Frontend`) — Opens a json document at the given absolute path and deserializes it into a Metasound document struct. @returns false if the file couldn't be found or parsed into a document.
- L86 _prototype_ `FVertexInterface CreateDefaultVertexInterfaceFromClass(const FMetasoundFrontendClass& InNodeClass, const FProxyDataCache* InProxyDataCache = nullptr);` (scope `Metasound::Frontend`) — If called on the game thread, no proxy data cache is needed for object literal creation, but if called from other threads, the proxy data cache must be provided.
- L88 _prototype_ `FVertexInterface CreateDefaultVertexInterfaceFromClassNoProxy(const FMetasoundFrontendClass& InNodeClass);` (scope `Metasound::Frontend`) — Does not create proxies, so no thread restrictions.

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendArchetypeRegistry.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendController.h` (Public)


#### struct `Metasound::Frontend::FConstDocumentAccess`  
`struct FConstDocumentAccess`  
_L73-83_
- desc: Container holding various access pointers to the FMetasoundFrontendDocument
- L75 _public member_ `FConstVertexAccessPtr ConstVertex;`
- L76 _public member_ `FConstClassInputAccessPtr ConstClassInput;`
- L77 _public member_ `FConstClassOutputAccessPtr ConstClassOutput;`
- L78 _public member_ `FConstNodeAccessPtr ConstNode;`
- L79 _public member_ `FConstClassAccessPtr ConstClass;`
- L80 _public member_ `FConstGraphClassAccessPtr ConstGraphClass;`
- L81 _public member_ `FConstGraphAccessPtr ConstGraph;`
- L82 _public member_ `FConstDocumentAccessPtr ConstDocument;`

#### struct `Metasound::Frontend::FDocumentAccess`  
`struct FDocumentAccess : public FConstDocumentAccess`  
_L86-96_
- inherits: `FConstDocumentAccess`
- desc: Container holding various access pointers to the FMetasoundFrontendDocument
- L88 _public member_ `FVertexAccessPtr Vertex;`
- L89 _public member_ `FClassInputAccessPtr ClassInput;`
- L90 _public member_ `FClassOutputAccessPtr ClassOutput;`
- L91 _public member_ `FNodeAccessPtr Node;`
- L92 _public member_ `FClassAccessPtr Class;`
- L93 _public member_ `FGraphClassAccessPtr GraphClass;`
- L94 _public member_ `FGraphAccessPtr Graph;`
- L95 _public member_ `FDocumentAccessPtr Document;`

#### class `Metasound::Frontend::IDocumentAccessor`  
`class IDocumentAccessor`  
_L102-134_
- desc: IDocumentAccessor describes an interface for various I*Controllers to interact with each other without exposing that interface publicly or requiring friendship between various controller implementation classes.
- L115 _protected prototype_ `virtual FDocumentAccess ShareAccess() = 0;` — Share access to FMetasoundFrontendDocument objects. Derived classes must implement this method. In the implementation, derived classes should set the various TAccessPtrs on FDocumentAccess to the TAccessPtrs held internal in the derived class. Sharing access simplifies operations involving multiple frontend controllers by providing direct access to the FMetasoundFrontendDocument objects to be edited.
- L127 _protected prototype_ `virtual FConstDocumentAccess ShareAccess() const = 0;` — Share access to FMetasoundFrontendDocument objects. Derived classes must implement this method. In the implementation, derived classes should set the various TAccessPtrs on FDocumentAccess to the TAccessPtrs held internal in the derived class. Sharing access simplifies operations involving multiple frontend controllers by providing direct access to the FMetasoundFrontendDocument objects to be edited.
- L130 _protected prototype_ `static FDocumentAccess GetSharedAccess(IDocumentAccessor& InDocumentAccessor);` — Returns the shared access from an IDocumentAccessor.
- L133 _protected prototype_ `static FConstDocumentAccess GetSharedAccess(const IDocumentAccessor& InDocumentAccessor);` — Returns the shared access from an IDocumentAccessor.

#### class `Metasound::Frontend::IOutputController`  
`class IOutputController : public TSharedFromThis<IOutputController>, public IDocumentAccessor`  
_L137-217_
- inherits: `TSharedFromThis<IOutputController>,IDocumentAccessor`
- desc: An IOutputController provides methods for querying and manipulating a metasound output vertex.
- L140 _public prototype_ `static FOutputHandle GetInvalidHandle();`
- L142 _public prototype_ `IOutputController() = default;`
- L143 _public prototype_ `virtual ~IOutputController() = default;`
- L146 _public prototype_ `virtual bool IsValid() const = 0;` — Returns true if the controller is in a valid state.
- L148 _public prototype_ `virtual FGuid GetID() const = 0;`
- L151 _public prototype_ `virtual const FName& GetDataType() const = 0;` — Returns the data type name associated with this output.
- L154 _public prototype_ `virtual const FVertexName& GetName() const = 0;` — Returns the name associated with this output.
- L157 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetVertexAccessType() const = 0;` — Returns the vertex access type.
- L161 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Returns the human readable name associated with this output.
- L164 _public prototype_ `virtual const FText& GetTooltip() const = 0;` — Returns the tooltip associated with this output.
- L167 _public prototype_ `virtual const FMetasoundFrontendVertexMetadata& GetMetadata() const = 0;` — Returns all metadata associated with this output.
- L171 _public prototype_ `virtual FGuid GetOwningNodeID() const = 0;` — Returns the ID of the node which owns this output.
- L174 _public prototype_ `virtual FNodeHandle GetOwningNode() = 0;` — Returns a FNodeHandle to the node which owns this output.
- L177 _public prototype_ `virtual FConstNodeHandle GetOwningNode() const = 0;` — Returns a FConstNodeHandle to the node which owns this output.
- L180 _public prototype_ `virtual void SetName(const FVertexName& InName) = 0;` — This should only be used as a means of fixing up vertex names for document model versioning transform(s).
- L184 _public prototype_ `virtual bool IsConnectionUserModifiable() const = 0;` — Returns true if the output connections can be directly modified by a user.  Returns false otherwise.
- L187 _public prototype_ `virtual bool IsConnected() const = 0;` — Return true if the input is connect to an output.
- L191 _public prototype_ `virtual TArray<FInputHandle> GetConnectedInputs() = 0;` — Returns the currently connected output. If this input is not connected, the returned handle will be invalid.
- L195 _public prototype_ `virtual TArray<FConstInputHandle> GetConstConnectedInputs() const = 0;` — Returns the currently connected output. If this input is not connected, the returned handle will be invalid.
- L197 _public prototype_ `virtual bool Disconnect() = 0;`
- L200 _public prototype_ `virtual FConnectability CanConnectTo(const IInputController& InController) const = 0;` — Returns information describing connectability between this output and the supplied input.
- L205 _public prototype_ `virtual bool Connect(IInputController& InController) = 0;` — Connects this output and the supplied input. @return True on success, false on failure.
- L210 _public prototype_ `virtual bool ConnectWithConverterNode(IInputController& InController, const FConverterNodeInfo& InNodeClassName) = 0;` — Connects this output to the input using a converter node. @return True on success, false on failure.
- L215 _public prototype_ `virtual bool Disconnect(IInputController& InController) = 0;` — Disconnects this output from the input. @return True on success, false on failure.

#### class `Metasound::Frontend::IVariableController`  
`class IVariableController : public TSharedFromThis<IVariableController>, public IDocumentAccessor`  
_L219-285_
- inherits: `TSharedFromThis<IVariableController>,IDocumentAccessor`
- L222 _public prototype_ `static FVariableHandle GetInvalidHandle();`
- L224 _public prototype_ `IVariableController() = default;`
- L225 _public prototype_ `virtual ~IVariableController() = default;`
- L228 _public prototype_ `virtual bool IsValid() const = 0;` — Returns true if the controller is in a valid state.
- L231 _public prototype_ `virtual FGuid GetID() const = 0;` — Returns the variable ID.
- L234 _public prototype_ `virtual const FName& GetDataType() const = 0;` — Returns the data type name associated with this variable.
- L237 _public prototype_ `virtual const FName& GetName() const = 0;` — Returns the name associated with this variable.
- L240 _public prototype_ `virtual void SetName(const FName& InName) = 0;` — Sets the name associated with this variable.
- L244 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Returns the human readable name associated with this variable.
- L247 _public prototype_ `virtual void SetDisplayName(const FText& InDisplayName) = 0;` — Sets the human readable name associated with this variable.
- L250 _public prototype_ `virtual FText GetDescription() const = 0;` — Returns the human readable description associated with this variable.
- L253 _public prototype_ `virtual void SetDescription(const FText& InDescription) = 0;` — Sets the human readable description associated with this variable.
- L257 _public prototype_ `virtual FNodeHandle FindMutatorNode() = 0;` — Returns the mutator node associated with this variable.
- L260 _public prototype_ `virtual FConstNodeHandle FindMutatorNode() const = 0;` — Returns the mutator node associated with this variable.
- L263 _public prototype_ `virtual TArray<FNodeHandle> FindAccessorNodes() = 0;` — Returns the accessor nodes associated with this variable.
- L266 _public prototype_ `virtual TArray<FConstNodeHandle> FindAccessorNodes() const = 0;` — Returns the accessor nodes associated with this variable.
- L269 _public prototype_ `virtual TArray<FNodeHandle> FindDeferredAccessorNodes() = 0;` — Returns the deferred accessor nodes associated with this variable.
- L272 _public prototype_ `virtual TArray<FConstNodeHandle> FindDeferredAccessorNodes() const = 0;` — Returns the deferred accessor nodes associated with this variable.
- L275 _public prototype_ `virtual FGraphHandle GetOwningGraph() = 0;` — Returns a FGraphHandle to the node which owns this variable.
- L278 _public prototype_ `virtual FConstGraphHandle GetOwningGraph() const = 0;` — Returns a FConstGraphHandle to the node which owns this variable.
- L281 _public prototype_ `virtual const FMetasoundFrontendLiteral& GetLiteral() const = 0;` — Returns the value for the given variable instance if set.
- L284 _public prototype_ `virtual bool SetLiteral(const FMetasoundFrontendLiteral& InLiteral) = 0;` — Sets the value for the given variable instance

#### class `Metasound::Frontend::IInputController`  
`class IInputController : public TSharedFromThis<IInputController>, public IDocumentAccessor`  
_L288-388_
- inherits: `TSharedFromThis<IInputController>,IDocumentAccessor`
- desc: An IInputController provides methods for querying and manipulating a metasound input vertex.
- L291 _public prototype_ `static FInputHandle GetInvalidHandle();`
- L293 _public prototype_ `IInputController() = default;`
- L294 _public prototype_ `virtual ~IInputController() = default;`
- L297 _public prototype_ `virtual bool IsValid() const = 0;` — Returns true if the controller is in a valid state.
- L299 _public prototype_ `virtual FGuid GetID() const = 0;`
- L302 _public prototype_ `virtual bool IsConnected() const = 0;` — Return true if the input is connect to an output.
- L305 _public prototype_ `virtual const FName& GetDataType() const = 0;` — Returns the data type name associated with this input.
- L308 _public prototype_ `virtual const FVertexName& GetName() const = 0;` — Returns the data type name associated with this input.
- L311 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetVertexAccessType() const = 0;` — Returns the vertex access type.
- L315 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Returns the data type name associated with this input.
- L319 _public prototype_ `virtual bool ClearLiteral() = 0;` — Clears the value for the given input instance if set.
- L322 _public prototype_ `virtual const FMetasoundFrontendLiteral* GetLiteral() const = 0;` — Returns the value for the given input instance if set.
- L325 _public prototype_ `virtual void SetLiteral(const FMetasoundFrontendLiteral& InLiteral) = 0;` — Sets the value for the given input instance (effectively overriding the class default).
- L328 _public prototype_ `virtual const FMetasoundFrontendLiteral* GetClassDefaultLiteral() const = 0;` — Returns the class default value of the given input.
- L332 _public prototype_ `virtual const FText& GetTooltip() const = 0;` — Returns the data type name associated with this input.
- L335 _public prototype_ `virtual const FMetasoundFrontendVertexMetadata& GetMetadata() const = 0;` — Returns all metadata associated with this input.
- L339 _public prototype_ `virtual FGuid GetOwningNodeID() const = 0;` — Returns the ID of the node which owns this output.
- L342 _public prototype_ `virtual FNodeHandle GetOwningNode() = 0;` — Returns a FNodeHandle to the node which owns this output.
- L345 _public prototype_ `virtual FConstNodeHandle GetOwningNode() const = 0;` — Returns a FConstNodeHandle to the node which owns this output.
- L349 _public prototype_ `virtual FOutputHandle GetConnectedOutput() = 0;` — Returns the currently connected output. If this input is not connected, the returned handle will be invalid.
- L353 _public prototype_ `virtual FConstOutputHandle GetConnectedOutput() const = 0;` — Returns the currently connected output. If this input is not connected, the returned handle will be invalid.
- L356 _public prototype_ `virtual void SetName(const FVertexName& InName) = 0;` — This should only be used as a means of fixing up vertex names for document model versioning transform(s).
- L360 _public prototype_ `virtual bool IsConnectionUserModifiable() const = 0;` — Returns true if the input connections can be directly modified by a user.  Returns false otherwise.
- L363 _public prototype_ `virtual FConnectability CanConnectTo(const IOutputController& InController) const = 0;` — Returns information describing connectability between this input and the supplied output.
- L368 _public prototype_ `virtual bool Connect(IOutputController& InController) = 0;` — Connects this input and the supplied output. @return True on success, false on failure.
- L373 _public prototype_ `virtual bool ConnectWithConverterNode(IOutputController& InController, const FConverterNodeInfo& InNodeClassName) = 0;` — Connects this input to the output using a converter node. @return True on success, false on failure.
- L378 _public prototype_ `virtual bool Disconnect(IOutputController& InController) = 0;` — Disconnects this input from the given output. @return True on success, false on failure.
- L383 _public prototype_ `virtual bool Disconnect() = 0;` — Disconnects this input from any connected output. @return True on success, false on failure.
- L387 _public prototype_ `virtual void ClearConnectedObjectLiterals() = 0;` — Clear object literals to prevent referencing assets on connected inputs that are not used in the graph.

#### class `Metasound::Frontend::INodeController`  
`class INodeController : public TSharedFromThis<INodeController>, public IDocumentAccessor`  
_L391-576_
- inherits: `TSharedFromThis<INodeController>,IDocumentAccessor`
- desc: An INodeController provides methods for querying and manipulating a Metasound node.
- L395 _public prototype_ `static FNodeHandle GetInvalidHandle();`
- L397 _public typedef_ `using FVertexNameAndType = TTuple<FVertexName, FName>;`
- L399 _public prototype_ `INodeController() = default;`
- L400 _public prototype_ `virtual ~INodeController() = default;`
- L403 _public prototype_ `virtual bool IsValid() const = 0;` — Returns true if the controller is in a valid state.
- L406 _public prototype_ `virtual TArray<FInputHandle> GetInputs() = 0;` — Returns all node inputs.
- L409 _public prototype_ `virtual TArray<FConstInputHandle> GetConstInputs() const = 0;` — Returns all node inputs.
- L413 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Returns the display name of the given node (what to distinguish and label in visual arrays, such as context menus).
- L416 _public prototype_ `virtual void SetDescription(const FText& InDescription) = 0;` — Sets the description of the node.
- L419 _public prototype_ `virtual void SetDisplayName(const FText& InDisplayName) = 0;` — Sets the display name of the node.
- L422 _public prototype_ `virtual const FText& GetDisplayTitle() const = 0;` — Returns the title of the given node (what to label when displayed as visual node).
- L425 _public prototype_ `virtual void SetNodeName(const FVertexName& InName) = 0;`
- L428 _public prototype_ `virtual void IterateInputs(TUniqueFunction<void(FInputHandle)> InFunction) = 0;` — Iterate over inputs
- L429 _public prototype_ `virtual void IterateConstInputs(TUniqueFunction<void(FConstInputHandle)> InFunction) const = 0;`
- L432 _public prototype_ `virtual int32 GetNumInputs() const = 0;` — Returns number of node inputs.
- L435 _public prototype_ `virtual void IterateOutputs(TUniqueFunction<void(FOutputHandle)> InFunction) = 0;` — Iterate over outputs
- L436 _public prototype_ `virtual void IterateConstOutputs(TUniqueFunction<void(FConstOutputHandle)> InFunction) const = 0;`
- L439 _public prototype_ `virtual int32 GetNumOutputs() const = 0;` — Returns number of node outputs.
- L441 _public prototype_ `virtual FInputHandle GetInputWithVertexName(const FVertexName& InName) = 0;`
- L442 _public prototype_ `virtual FConstInputHandle GetConstInputWithVertexName(const FVertexName& InName) const = 0;`
- L445 _public prototype_ `virtual TArray<FOutputHandle> GetOutputs() = 0;` — Returns all node outputs.
- L448 _public prototype_ `virtual TArray<FConstOutputHandle> GetConstOutputs() const = 0;` — Returns all node outputs.
- L450 _public prototype_ `virtual FOutputHandle GetOutputWithVertexName(const FVertexName& InName) = 0;`
- L451 _public prototype_ `virtual FConstOutputHandle GetConstOutputWithVertexName(const FVertexName& InName) const = 0;`
- L453 _public prototype_ `virtual bool IsInterfaceMember() const = 0;`
- L454 _public prototype_ `virtual const FMetasoundFrontendVersion& GetInterfaceVersion() const = 0;`
- L461 _public prototype_ `virtual FNodeHandle ReplaceWithVersion(const FMetasoundFrontendVersionNumber& InNewVersion, TArray<FVertexNameAndType>* OutDisconnectedInputs, TArray<FVertexNameAndType>* OutDisconnectedOutputs) = 0;` — Replaces this node with a new node of the provided version number, and attempts to rebuild edges where possible with matching vertex names that share the same DataType. Returns a node handle to the new node.  If operation fails, returns a handle to this node.
- L468 _public prototype_ `virtual FInputHandle GetInputWithID(FGuid InVertexID) = 0;` — Returns an input with the given id. If the input does not exist, an invalid handle is returned.
- L474 _public prototype_ `virtual FConstInputHandle GetInputWithID(FGuid InVertexID) const = 0;` — Returns an input with the given name. If the input does not exist, an invalid handle is returned.
- L480 _public prototype_ `virtual FOutputHandle GetOutputWithID(FGuid InVertexID) = 0;` — Returns an output with the given name. If the output does not exist, an invalid handle is returned.
- L486 _public prototype_ `virtual FConstOutputHandle GetOutputWithID(FGuid InVertexID) const = 0;` — Returns an output with the given name. If the output does not exist, an invalid handle is returned.
- L488 _public prototype_ `virtual bool CanAddInput(const FVertexName& InVertexName) const = 0;`
- L489 _public prototype_ `virtual FInputHandle AddInput(const FVertexName& InVertexName, const FMetasoundFrontendLiteral* InDefault) = 0;`
- L490 _public prototype_ `virtual bool RemoveInput(FGuid InVertexID) = 0;`
- L492 _public prototype_ `virtual bool CanAddOutput(const FVertexName& InVertexName) const = 0;`
- L493 _public prototype_ `virtual FInputHandle AddOutput(const FVertexName& InVertexName, const FMetasoundFrontendLiteral* InDefault) = 0;`
- L494 _public prototype_ `virtual bool RemoveOutput(FGuid InVertexID) = 0;`
- L497 _public prototype_ `virtual const FMetasoundFrontendLiteral* GetInputLiteral(const FGuid& InVertexID) const = 0;` — Returns an input's default literal if set, null if not.
- L500 _public prototype_ `virtual void SetInputLiteral(const FMetasoundFrontendVertexLiteral& InVertexLiteral) = 0;` — Sets an input's default literal
- L503 _public prototype_ `virtual bool ClearInputLiteral(FGuid InVertexID) = 0;` — Clears an input's default literal
- L505 _public prototype_ `virtual const FMetasoundFrontendClassMetadata& GetClassMetadata() const = 0;`
- L506 _public prototype_ `virtual const FMetasoundFrontendClassInterface& GetClassInterface() const = 0;`
- L511 _public prototype_ `virtual const FMetasoundFrontendNodeInterface& GetNodeInterface() const = 0;` — Returns the node interface, which may be different than the class interface if the class supports dynamic input/output behavior (ex. Templates).
- L515 _public prototype_ `virtual const FMetasoundFrontendInterfaceStyle& GetOutputStyle() const = 0;` — Returns associated node class data
- L516 _public prototype_ `virtual const FMetasoundFrontendInterfaceStyle& GetInputStyle() const = 0;`
- L517 _public prototype_ `virtual const FMetasoundFrontendClassStyle& GetClassStyle() const = 0;`
- L522 _public prototype_ `virtual bool DiffAgainstRegistryInterface(FClassInterfaceUpdates& OutInterfaceUpdates, bool bInUseHighestMinorVersion, bool bInForceRegenerateClassInterfaceOverride=true) const = 0;` — `UE_DEPRECATED(5.6, "Moved to FMetaSoundFrontendDocumentBuilder")`
- L533 _public prototype_ `virtual bool CanAutoUpdate(FClassInterfaceUpdates& OutInterfaceUpdates) const = 0;` — `UE_DEPRECATED(5.7, "Moved to FMetaSoundFrontendDocumentBuilder")` — Returns whether the node is eligible for auto-updating (i.e. has undergone minor revision or the interface has changed, but no higher major revision is available). Provides interface updates to populate with any information regarding interface updates. Can return true if the interface has changed but only cosmetic differences (ex. DisplayName only used in editor) but no runtime behavior has been modified.
- L538 _public prototype_ `virtual const FText& GetDescription() const = 0;` — Description of the given node.
- L544 _public prototype_ `virtual FGraphHandle AsGraph() = 0;` — If the node is also a graph, this returns a graph handle. If the node is not also a graph, it will return an invalid handle.
- L549 _public prototype_ `virtual FConstGraphHandle AsGraph() const = 0;` — If the node is also a graph, this returns a graph handle. If the node is not also a graph, it will return an invalid handle.
- L552 _public prototype_ `virtual const FVertexName& GetNodeName() const = 0;` — Returns the name of this node.
- L555 _public prototype_ `virtual const FMetasoundFrontendNodeStyle& GetNodeStyle() const = 0;`
- L556 _public prototype_ `virtual void SetNodeStyle(const FMetasoundFrontendNodeStyle& InStyle) = 0;`
- L559 _public prototype_ `virtual void SetNodeConfiguration(TInstancedStruct<FMetaSoundFrontendNodeConfiguration> InConfig) = 0;`
- L560 _public prototype_ `virtual TConstStructView<FMetaSoundFrontendNodeConfiguration> GetNodeConfiguration() const = 0;`
- L563 _public prototype_ `virtual FGuid GetID() const = 0;` — Returns the ID associated with this node.
- L566 _public prototype_ `virtual FGuid GetClassID() const = 0;` — Returns the ID associated with the node class.
- L569 _public prototype_ `virtual FGuid GetOwningGraphClassID() const = 0;` — Returns the class ID of the metasound class which owns this node.
- L572 _public prototype_ `virtual FGraphHandle GetOwningGraph() = 0;` — Returns the graph which owns this node.
- L575 _public prototype_ `virtual FConstGraphHandle GetOwningGraph() const = 0;` — Returns the graph which owns this node.

#### class `Metasound::Frontend::IGraphController`  
`class IGraphController : public TSharedFromThis<IGraphController>, public IDocumentAccessor`  
_L579-972_
- inherits: `TSharedFromThis<IGraphController>,IDocumentAccessor`
- desc: An IGraphController provides methods for querying and manipulating a Metasound graph.
- L582 _public prototype_ `static FGraphHandle GetInvalidHandle();`
- L584 _public prototype_ `IGraphController() = default;`
- L585 _public prototype_ `virtual ~IGraphController() = default;`
- L588 _public prototype_ `virtual bool IsValid() const = 0;` — Returns true if the controller is in a valid state.
- L591 _public prototype_ `virtual FGuid GetClassID() const = 0;` — Returns the ClassID associated with this graph.
- L594 _public prototype_ `virtual const FMetasoundFrontendGraphClassPresetOptions& GetGraphPresetOptions() const;` — `UE_DEPRECATED(5.8, "Preset options are now serialized in the Preset MetaSound Template")`
- L597 _public prototype_ `virtual void SetGraphPresetOptions(const FMetasoundFrontendGraphClassPresetOptions& InPresetOptions);` — `UE_DEPRECATED(5.8, "Preset options are now serialized in the Preset MetaSound Template")`
- L600 _public prototype_ `virtual const FMetasoundFrontendClassMetadata& GetGraphMetadata() const = 0;` — Return the metadata for the current graph.
- L603 _public prototype_ `virtual void SetGraphMetadata(const FMetasoundFrontendClassMetadata& InMetadata) = 0;` — Sets the metadata for the current graph.
- L607 _public prototype_ `virtual const FMetasoundFrontendGraphStyle& GetGraphStyle() const = 0;` — Returns graph style.
- L609 _public prototype_ `virtual const FMetasoundFrontendInterfaceStyle& GetInputStyle() const = 0;`
- L610 _public prototype_ `virtual const FMetasoundFrontendInterfaceStyle& GetOutputStyle() const = 0;`
- L613 _public prototype_ `virtual void SetGraphStyle(FMetasoundFrontendGraphStyle Style) = 0;` — Sets graph style.
- L616 _public prototype_ `virtual void SetInputStyle(FMetasoundFrontendInterfaceStyle Style) = 0;` — Sets the input style for the graph.
- L619 _public prototype_ `virtual void SetOutputStyle(FMetasoundFrontendInterfaceStyle Style) = 0;` — Sets the output style for the graph.
- L622 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Return the display name of the graph.
- L625 _public prototype_ `virtual TArray<FVertexName> GetInputVertexNames() const = 0;`
- L626 _public prototype_ `virtual TArray<FVertexName> GetOutputVertexNames() const = 0;`
- L629 _public prototype_ `virtual TArray<FNodeHandle> GetNodes() = 0;` — Returns all nodes in the graph.
- L632 _public prototype_ `virtual FConstNodeHandle GetNodeWithID(FGuid InNodeID) const = 0;` — Returns a node by NodeID. If the node does not exist, an invalid handle is returned.
- L635 _public prototype_ `virtual TArray<FConstNodeHandle> GetConstNodes() const = 0;` — Returns all nodes in the graph.
- L638 _public prototype_ `virtual FNodeHandle GetNodeWithID(FGuid InNodeID) = 0;` — Returns a node by NodeID. If the node does not exist, an invalid handle is returned.
- L641 _public prototype_ `virtual TArray<FNodeHandle> GetOutputNodes() = 0;` — Returns all output nodes in the graph.
- L644 _public prototype_ `virtual TArray<FConstNodeHandle> GetConstOutputNodes() const = 0;` — Returns all output nodes in the graph.
- L647 _public prototype_ `virtual TArray<FNodeHandle> GetInputNodes() = 0;` — Returns all input nodes in the graph.
- L650 _public prototype_ `virtual TArray<FConstNodeHandle> GetConstInputNodes() const = 0;` — Returns all input nodes in the graph.
- L653 _public prototype_ `virtual const TSet<FName>& GetInputsInheritingDefault() const;` — `UE_DEPRECATED(5.8, "Preset options are now serialized in the Preset MetaSound Template")`
- L656 _public prototype_ `virtual bool SetInputInheritsDefault(FName InName, bool bDefaultIsInherited);` — `UE_DEPRECATED(5.8, "Preset options are now serialized in the Preset MetaSound Template")`
- L659 _public prototype_ `virtual void SetInputsInheritingDefault(TSet<FName>&& InNames);` — `UE_DEPRECATED(5.8, "Preset options are now serialized in the Preset MetaSound Template")`
- L662 _public prototype_ `virtual FVariableHandle AddVariable(const FName& InDataTypeName) = 0;` — Adds a new variable to the graph
- L668 _public prototype_ `virtual FVariableHandle FindVariable(const FGuid& InVariableID) = 0;` — Finds a variable by ID. @param InVariableID - ID of existing variable.
- L674 _public prototype_ `virtual FConstVariableHandle FindVariable(const FGuid& InVariableID) const = 0;` — Finds a variable by ID. @param InVariableID - ID of existing variable.
- L681 _public prototype_ `virtual FVariableHandle FindVariableContainingNode(const FGuid& InNodeID) = 0;` — Finds a variable inspecting the nodes associated with the variable. @param InNodeID - ID of node associated with variable. @return If found, returns valid variable handle. An invalid handle otherwise.
- L688 _public prototype_ `virtual FConstVariableHandle FindVariableContainingNode(const FGuid& InNodeID) const = 0;` — Finds a variable inspecting the nodes associated with the variable. @param InNodeID - ID of node associated with variable. @return If found, returns valid variable handle. An invalid handle otherwise.
- L691 _public function_ `virtual bool RemoveVariable(const FGuid& InVariableID)` — `UE_DEPRECATED(5.8, "Use the MetaSound Builder API")`
- L694 _public prototype_ `virtual TArray<FVariableHandle> GetVariables() = 0;` — Returns an array of all variables associated with the graph.
- L697 _public prototype_ `virtual TArray<FConstVariableHandle> GetVariables() const = 0;` — Returns an array of all variables associated with the graph.
- L703 _public prototype_ `virtual FNodeHandle FindOrAddVariableMutatorNode(const FGuid& InVariableID) = 0;` — Returns the variable mutator node. If none exist, one is created. @param InVariableID - ID of existing variable.
- L709 _public prototype_ `virtual FNodeHandle AddVariableAccessorNode(const FGuid& InVariableID) = 0;` — Creates and returns a variable accessor node. @param InVariableID - ID of existing variable.
- L715 _public prototype_ `virtual FNodeHandle AddVariableDeferredAccessorNode(const FGuid& InVariableID) = 0;` — Creates and returns a variable deferred accessor node. @param InVariableID - ID of existing variable.
- L719 _public prototype_ `virtual void ClearGraph() = 0;` — Clears the graph, its associated interface, and synchronizes removed dependencies with the owning graph.
- L722 _public prototype_ `virtual void IterateNodes(TFunctionRef<void(FNodeHandle)> InFunction, EMetasoundFrontendClassType InClassType = EMetasoundFrontendClassType::Invalid) = 0;` — Iterate over all input nodes with the given function. If ClassType is specified, only iterate over given type.
- L725 _public prototype_ `virtual void IterateConstNodes(TFunctionRef<void(FConstNodeHandle)> InFunction, EMetasoundFrontendClassType InClassType = EMetasoundFrontendClassType::Invalid) const = 0;` — Iterate over all nodes with the given function. If ClassType is specified, only iterate over given type.
- L733 _public prototype_ `virtual bool ContainsOutputVertex(const FVertexName& InName, const FName& InTypeName) const = 0;` — Returns true if an output vertex with the given Name exists. @param InName - Name of vertex. @param InTypeName - DataType Name of vertex. @return True if the vertex exists, false otherwise.
- L741 _public prototype_ `virtual bool ContainsOutputVertexWithName(const FVertexName& InName) const = 0;` — Returns true if an output vertex with the given Name exists. @param InName - Name of vertex. @param InTypeName - DataType Name of vertex. @return True if the vertex exists, false otherwise.
- L748 _public prototype_ `virtual bool ContainsInputVertex(const FVertexName& InName, const FName& InTypeName) const = 0;` — Returns true if an input vertex with the given Name exists. @param InName - Name of vertex. @return True if the vertex exists, false otherwise.
- L755 _public prototype_ `virtual bool ContainsInputVertexWithName(const FVertexName& InName) const = 0;` — Returns true if an input vertex with the given Name exists. @param InName - Name of vertex. @return True if the vertex exists, false otherwise.
- L763 _public prototype_ `virtual FNodeHandle GetOutputNodeWithName(const FVertexName& InName) = 0;` — Returns a handle to an existing output node for the given graph output name. If no output exists with the given name, an invalid node handle is returned. @param InName - Name of graph output.. @return The node handle for the output node. If the output does not exist, an invalid handle is returned.
- L771 _public prototype_ `virtual FConstNodeHandle GetOutputNodeWithName(const FVertexName& InName) const = 0;` — Returns a handle to an existing output node for the given graph output name. If no output exists with the given name, an invalid node handle is returned. @param InName - Name of graph output. @return The node handle for the output node. If the node does not exist, an invalid handle is returned.
- L779 _public prototype_ `virtual FNodeHandle GetInputNodeWithName(const FVertexName & InName) = 0;` — Returns a handle to an existing input node for the given graph input name. If no input exists with the given name, an invalid node handle is returned. @param InName - Name of graph input. @return The node handle for the input node. If the node does not exist, an invalid handle is returned.
- L787 _public prototype_ `virtual FConstNodeHandle GetInputNodeWithName(const FVertexName& InName) const = 0;` — Returns a handle to an existing input node for the given graph input name. If no input exists with the given name, an invalid node handle is returned. @param InName - Name of graph input. @return The node handle for the input node. If the node does not exist, an invalid handle is returned.
- L789 _public prototype_ `virtual FConstClassInputAccessPtr FindClassInputWithName(const FVertexName& InName) const = 0;`
- L790 _public prototype_ `virtual FConstClassOutputAccessPtr FindClassOutputWithName(const FVertexName& InName) const = 0;`
- L797 _public prototype_ `virtual FNodeHandle AddInputVertex(const FMetasoundFrontendClassInput& InDescription) = 0;` — Add a new input node using the input description. @param InDescription - Description for input of graph. @return On success, a valid input node handle. On failure, an invalid node handle.
- L800 _public prototype_ `virtual bool RemoveInputVertex(const FVertexName& InputName) = 0;` — Remove the input with the given name. Returns true if successfully removed, false otherwise.
- L807 _public prototype_ `virtual FNodeHandle AddOutputVertex(const FMetasoundFrontendClassOutput& InDescription) = 0;` — Add a new output node using the output description. @param InDescription - Description for output of graph. @return On success, a valid output node handle. On failure, an invalid node handle.
- L808 _public prototype_ `virtual FNodeHandle AddOutputVertex(const FVertexName& InName, const FName InTypeName) = 0;`
- L811 _public prototype_ `virtual bool RemoveOutputVertex(const FVertexName& OutputName) = 0;` — Remove the output with the given name. Returns true if successfully removed, false otherwise.
- L820 _public prototype_ `virtual ELiteralType GetPreferredLiteralTypeForInputVertex(const FVertexName& InInputName) const = 0;` — Returns the preferred literal argument type for a given input. Returns ELiteralType::Invalid if the input couldn't be found, or if the input doesn't support any kind of literals. @param InInputName - Name of graph input. @return The preferred literal argument type.
- L829 _public prototype_ `virtual UClass* GetSupportedClassForInputVertex(const FVertexName& InInputName) = 0;` — Return the UObject class corresponding an input. Meaningful for inputs whose preferred literal type is UObject or UObjectArray. @param InInputName - Name of graph input. @return The UClass* for the literal argument input. nullptr on error or if UObject argument is not supported.
- L831 _public prototype_ `virtual FGuid GetVertexIDForInputVertex(const FVertexName& InInputName) const = 0;`
- L832 _public prototype_ `virtual FGuid GetVertexIDForOutputVertex(const FVertexName& InOutputName) const = 0;`
- L835 _public prototype_ `virtual FMetasoundFrontendLiteral GetDefaultInput(const FGuid& InVertexID) const = 0;` — `UE_DEPRECATED(5.7, "Use version which provides page order")`
- L837 _public prototype_ `virtual FMetasoundFrontendLiteral GetDefaultInput(const FGuid& InVertexID, TArrayView<const FGuid> InPageOrder) const = 0;`
- L843 _public prototype_ `virtual bool SetDefaultInput(const FGuid& InVertexID, const FMetasoundFrontendLiteral& InLiteral) = 0;` — `UE_DEPRECATED(5.7, "Use version which provides page order")`
- L845 _public prototype_ `virtual bool SetDefaultInput(const FGuid& InVertexID, const FMetasoundFrontendLiteral& InLiteral, TArrayView<const FGuid> InPageOrder) = 0;`
- L855 _public prototype_ `virtual bool SetDefaultInputToDefaultLiteralOfType(const FGuid& InVertexID) = 0;` — Set the default value for the graph input. @param InInputName - Name of the graph input. @param InVertexID - Vertex to set to DataType default. @param InDataTypeName - Name of datatype to set to default. @return True on success. False if the input does not exist or if the literal type was incompatible with the input.
- L859 _public prototype_ `virtual void SetInputDisplayName(const FVertexName& InName, const FText& InDisplayName) = 0;` — Set the display name for the input with the given name.
- L862 _public prototype_ `virtual void SetOutputDisplayName(const FVertexName& InName, const FText& InDisplayName) = 0;` — Set the display name for the output with the given name.
- L865 _public prototype_ `virtual const FText& GetInputDescription(const FVertexName& InName) const = 0;` — Get the description for the input with the given name.
- L868 _public prototype_ `virtual const FText& GetOutputDescription(const FVertexName& InName) const = 0;` — Get the description for the output with the given name.
- L871 _public prototype_ `virtual void SetInputDescription(const FVertexName& InName, const FText& InDescription) = 0;` — Set the description for the input with the given name.
- L874 _public prototype_ `virtual void SetOutputDescription(const FVertexName& InName, const FText& InDescription) = 0;` — Set the description for the output with the given name.
- L879 _public prototype_ `virtual int32 GetSortOrderIndexForInput(const FVertexName& InName) const = 0;` — Returns the sort order index for the input with the given name. Returns 0 if not found or unset.
- L882 _public prototype_ `virtual int32 GetSortOrderIndexForOutput(const FVertexName& InName) const = 0;` — Returns the sort order index for the input with the given name. Returns 0 if not found or unset.
- L887 _public prototype_ `virtual void SetSortOrderIndexForInput(const FVertexName& InName, int32 InSortOrderIndex) = 0;` — Sets the sort order index for the input with the given name. No-ops if input not found.
- L890 _public prototype_ `virtual void SetSortOrderIndexForOutput(const FVertexName& InName, int32 InSortOrderIndex) = 0;` — Sets the sort order index for the output with the given name. No-ops if output not found.
- L898 _public prototype_ `virtual void UpdateInterfaceChangeID() = 0;` — Updates the ChangeID for the class interface, which signals AutoUpdate to attempt to patch class references at runtime even if the graph class has not been versioned. TODO: Remove this once underlying architecture no longer requires it.
- L901 _public function_ `virtual bool ClearLiteralForInput(const FVertexName& InInputName, FGuid InVertexID)` — `UE_DEPRECATED(5.8, "Use Builder API instead")`
- L911 _public prototype_ `virtual FNodeHandle AddNode(const FNodeRegistryKey& InKey, FGuid InNodeGuid = FGuid::NewGuid()) = 0;` — Add a new node to this graph from the node registry. @param InKey - Registry key for node. @param InNodeGuid - (Optional) Explicit guid for the new node. Must be unique within the graph. Only useful to specify explicitly when caller is managing or tracking the graph's guids (ex. replacing removed node). @return Node handle for class. On error, an invalid handle is returned.
- L921 _public prototype_ `virtual FNodeHandle AddNode(const FMetasoundFrontendClassMetadata& InClassMetadata, FGuid InNodeGuid = FGuid::NewGuid()) = 0;` — Add a new node to this graph. @param InClassMetadata - Info for node class. @param InNodeGuid - (Optional) Explicit guid for the new node. Must be unique within the graph. Only useful to specify explicitly when caller is managing or tracking the graph's guids (ex. replacing removed node). @return Node handle for class. On error, an invalid handle is returned.
- L931 _public prototype_ `virtual FNodeHandle AddDuplicateNode(const INodeController& InNodeController) = 0;` — Add a new node to this graph by duplicating the supplied node. The new node has the same interface and node class as the supplied node. This method will not duplicate node connections. @param InNodeController - Node to duplicate. @return Node handle for new node. On error, an invalid handle is returned.
- L941 _public prototype_ `virtual FNodeHandle AddTemplateNode(const INodeTemplate& InNodeTemplate, FNodeTemplateGenerateInterfaceParams Params, FGuid InNodeGuid = FGuid::NewGuid()) = 0;` — Add a new template node to this graph, providing the defined interface as expected by the caller. @param InNodeTemplate - Node template to use to generate node @param InNodeGuid - (Optional) Explicit guid for the new node. Must be unique within the graph. Only useful to specify explicitly when caller is managing or tracking the graph's guids (ex. replacing removed node). @return Node handle for class. On error, an invalid handle is returned.
- L944 _public function_ `virtual FNodeHandle AddTemplateNode(const FNodeRegistryKey& InKey, FMetasoundFrontendNodeInterface&& InNodeInterface, FGuid InNodeGuid = FGuid::NewGuid())` — `UE_DEPRECATED(5.5, "Use overload that provides INodeTemplate instead")`
- L950 _public prototype_ `virtual bool RemoveNode(INodeController& InNode) = 0;` — Remove the node corresponding to this node handle. @return True on success, false on failure.
- L960 _public prototype_ `virtual FNodeHandle CreateEmptySubgraph(const FMetasoundFrontendClassMetadata& InInfo) = 0;` — Creates and inserts a new subgraph into this graph using the given metadata. By calling AsGraph() on the returned node handle, callers can modify the new subgraph. @param InInfo - Metadata for the subgraph. @return Handle to the subgraph node. On error, the handle is invalid.
- L963 _public prototype_ `virtual FDocumentHandle GetOwningDocument() = 0;` — Returns a handle to the document owning this graph.
- L966 _public prototype_ `virtual FConstDocumentHandle GetOwningDocument() const = 0;` — Returns a handle to the document owning this graph.
- L968 _public prototype_ `virtual const FMetasoundFrontendClassInput* FindInputDescriptionWithName(const FVertexName& InName) const = 0;`
- L969 _public prototype_ `virtual const FMetasoundFrontendClassInput* FindInputDescriptionWithVertexID(const FGuid& InVertexID) const = 0;`
- L970 _public prototype_ `virtual const FMetasoundFrontendClassOutput* FindOutputDescriptionWithName(const FVertexName& InName) const = 0;`
- L971 _public prototype_ `virtual const FMetasoundFrontendClassOutput* FindOutputDescriptionWithVertexID(const FGuid& InVertexID) const = 0;`

#### class `Metasound::Frontend::IDocumentController`  
`class IDocumentController : public TSharedFromThis<IDocumentController>, public IDocumentAccessor`  
_L975-1103_
- inherits: `TSharedFromThis<IDocumentController>,IDocumentAccessor`
- desc: An IDocumentController provides methods for querying and manipulating a Metasound document.
- L978 _public prototype_ `static FDocumentHandle GetInvalidHandle();`
- L981 _public prototype_ `static FDocumentHandle CreateDocumentHandle(FDocumentAccessPtr InDocument, bool bReloadBuilder = true);` — Create a document from FMetasoundFrontendDocument description pointer.
- L982 _public prototype_ `static FDocumentHandle CreateDocumentHandle(FMetasoundFrontendDocument& InDocument);`
- L985 _public prototype_ `static FConstDocumentHandle CreateDocumentHandle(FConstDocumentAccessPtr InDocument);` — Create a document from FMetasoundFrontendDocument description pointer.
- L986 _public prototype_ `static FConstDocumentHandle CreateDocumentHandle(const FMetasoundFrontendDocument& InDocument);`
- L988 _public prototype_ `IDocumentController() = default;`
- L989 _public prototype_ `virtual ~IDocumentController() = default;`
- L992 _public prototype_ `virtual bool IsValid() const = 0;` — Returns true if the controller is in a valid state.
- L996 _public prototype_ `virtual void IterateDependencies(TFunctionRef<void(FMetasoundFrontendClass&)> InFunction) = 0;` — Iterates all dependent class definitions that exist on the document (do not necessarily correspond to registered dependencies)
- L997 _public prototype_ `virtual void IterateDependencies(TFunctionRef<void(const FMetasoundFrontendClass&)> InFunction) const = 0;`
- L1003 _public prototype_ `virtual const TArray<FMetasoundFrontendClass>& GetDependencies() const = 0;` — Returns an array of all class dependencies for this document.
- L1004 _public prototype_ `virtual const TArray<FMetasoundFrontendGraphClass>& GetSubgraphs() const = 0;`
- L1005 _public prototype_ `virtual const FMetasoundFrontendGraphClass& GetRootGraphClass() const = 0;`
- L1006 _public prototype_ `virtual void SetRootGraphClass(FMetasoundFrontendGraphClass&& InClass) = 0;`
- L1008 _public prototype_ `virtual FConstClassAccessPtr FindDependencyWithID(FGuid InClassID) const = 0;`
- L1009 _public prototype_ `virtual FConstGraphClassAccessPtr FindSubgraphWithID(FGuid InClassID) const = 0;`
- L1010 _public prototype_ `virtual FConstClassAccessPtr FindClassWithID(FGuid InClassID) const = 0;`
- L1012 _public prototype_ `virtual void SetMetadata(const FMetasoundFrontendDocumentMetadata& InMetadata) = 0;`
- L1013 _public prototype_ `virtual const FMetasoundFrontendDocumentMetadata& GetMetadata() const = 0;`
- L1014 _public prototype_ `virtual FMetasoundFrontendDocumentMetadata* GetMetadata() = 0;`
- L1021 _public prototype_ `virtual FConstClassAccessPtr FindClass(const FNodeRegistryKey& InKey) const = 0;` — Returns an existing Metasound class description corresponding to a dependency which matches the provided class information. @return A pointer to the found object, or nullptr if it could not be found.
- L1031 _public prototype_ `virtual FConstClassAccessPtr FindOrAddClass(const FNodeRegistryKey& InKey, bool bInRefreshFromRegistry = false) = 0;` — Attempts to find an existing Metasound class description corresponding to a dependency which matches the provided class information. If the class is not found in the current dependencies, it is added to the dependencies. If found and bInRefreshFromRegistry is set (optional) , copies the version found in the registry to the document. @return A pointer to the object, or nullptr on error.
- L1038 _public prototype_ `virtual FConstClassAccessPtr FindClass(const FMetasoundFrontendClassMetadata& InMetadata) const = 0;` — Returns an existing Metasound class description corresponding to a dependency which matches the provided class information. @return A pointer to the found object, or nullptr if it could not be found.
- L1047 _public prototype_ `virtual FConstClassAccessPtr FindOrAddClass(const FMetasoundFrontendClassMetadata& InMetadata) = 0;` — Attempts to find an existing Metasound class description corresponding to a dependency which matches the provided class information. If the class is not found in the current dependencies, it is added to the dependencies. @return A pointer to the object, or nullptr on error.
- L1056 _public prototype_ `virtual FGraphHandle AddDuplicateSubgraph(const IGraphController& InGraph) = 0;` — Adds a duplicate subgraph to the document. This method creates a copy of the graph and adds all the graph dependencies to this document. @param InGraph - Graph to copy. @return Handle to new graph. On error, an invalid handle is returned.
- L1058 _public prototype_ `virtual const TSet<FMetasoundFrontendVersion>& GetInterfaceVersions() const = 0;`
- L1060 _public prototype_ `virtual void AddInterfaceVersion(const FMetasoundFrontendVersion& InVersion) = 0;`
- L1061 _public prototype_ `virtual void RemoveInterfaceVersion(const FMetasoundFrontendVersion& InVersion) = 0;`
- L1062 _public prototype_ `virtual void ClearInterfaceVersions() = 0;`
- L1066 _public prototype_ `virtual void RemoveUnreferencedDependencies() = 0;` — Removes all dependencies which are no longer referenced by any graphs within this document.
- L1071 _public prototype_ `virtual TArray<FConstClassAccessPtr> SynchronizeDependencyMetadata() = 0;` — Synchronizes all dependency Metadata in document with that found in the registry. If not found in the registry, no action taken.  Returns array of pointers to classes that were modified.
- L1074 _public prototype_ `virtual TArray<FGraphHandle> GetSubgraphHandles() = 0;` — Returns an array of all subgraphs for this document.
- L1077 _public prototype_ `virtual TArray<FConstGraphHandle> GetSubgraphHandles() const = 0;` — Returns an array of all subgraphs for this document.
- L1080 _public prototype_ `virtual FGraphHandle GetSubgraphWithClassID(FGuid InClassID) = 0;` — Returns a graphs in the document with the given class ID.
- L1083 _public prototype_ `virtual FConstGraphHandle GetSubgraphWithClassID(FGuid InClassID) const = 0;` — Returns a graphs in the document with the given class ID.
- L1086 _public prototype_ `virtual FGraphHandle GetRootGraph() = 0;` — Returns the root graph of this document.
- L1089 _public prototype_ `virtual FConstGraphHandle GetRootGraph() const = 0;` — Returns the root graph of this document.
- L1092 _public prototype_ `virtual FDocumentAccessPtr GetDocumentPtr() = 0;` — Returns the document if set.
- L1093 _public prototype_ `virtual const FDocumentAccessPtr GetDocumentPtr() const = 0;`
- L1099 _public prototype_ `virtual bool ExportToJSONAsset(const FString& InAbsolutePath) const = 0;` — Exports the document to a json file at the provided path. @return True on success, false on failure.
- L1102 _public prototype_ `virtual FString ExportToJSON() const = 0;` — Exports the document to a json formatted string.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L44 _namespace_ `namespace Metasound`
- L46 _namespace_ `namespace Frontend` (scope `Metasound`)
- L58 _typedef_ `using FInputHandle = TSharedRef<IInputController>;` (scope `Metasound::Frontend`) — Metasound Frontend Handles are all TSharedRefs of various Metasound Frontend Controllers.
- L59 _typedef_ `using FConstInputHandle = TSharedRef<const IInputController>;` (scope `Metasound::Frontend`)
- L60 _typedef_ `using FOutputHandle = TSharedRef<IOutputController>;` (scope `Metasound::Frontend`)
- L61 _typedef_ `using FConstOutputHandle = TSharedRef<const IOutputController>;` (scope `Metasound::Frontend`)
- L62 _typedef_ `using FVariableHandle = TSharedRef<IVariableController>;` (scope `Metasound::Frontend`)
- L63 _typedef_ `using FConstVariableHandle = TSharedRef<const IVariableController>;` (scope `Metasound::Frontend`)
- L64 _typedef_ `using FNodeHandle = TSharedRef<INodeController>;` (scope `Metasound::Frontend`)
- L65 _typedef_ `using FConstNodeHandle = TSharedRef<const INodeController>;` (scope `Metasound::Frontend`)
- L66 _typedef_ `using FGraphHandle = TSharedRef<IGraphController>;` (scope `Metasound::Frontend`)
- L67 _typedef_ `using FConstGraphHandle = TSharedRef<const IGraphController>;` (scope `Metasound::Frontend`)
- L68 _typedef_ `using FDocumentHandle = TSharedRef<IDocumentController>;` (scope `Metasound::Frontend`)
- L69 _typedef_ `using FConstDocumentHandle = TSharedRef<const IDocumentController>;` (scope `Metasound::Frontend`)
- L1106 _prototype_ `FConstOutputHandle FindReroutedOutput(FConstOutputHandle InOutputHandle);` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.5, "Reroute output recursion is now privately implemented in the reroute template node class. Use template registry to query reroute node input/output attributes")`
- L1109 _prototype_ `void FindReroutedInputs(FConstInputHandle InHandleToCheck, TArray<FConstInputHandle>& InOutInputHandles);` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.5, "Reroute input recursion is now privately implemented in the reroute template node class. Use template registry to query reroute node input/output attributes")`
- L1112 _prototype_ `void IterateReroutedInputs(FConstInputHandle InHandleToCheck, TFunctionRef<void(FConstInputHandle)> Func);` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.5, "Reroute input recursion is now privately implemented in the reroute template node class. Use template registry to query reroute node input/output attributes")`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendDataTypeRegistry.h` (Public)


#### struct `Metasound::Frontend::FDataTypeRegistryInfo`  
`struct FDataTypeRegistryInfo`  
_L32-95_
- desc: FDataTypeRegsitryInfo contains runtime inspectable behavior of a registered MetaSound data type.
- L35 _public member_ `FName DataTypeName;` — The name of the data type.
- L37 _public member_ `FText DataTypeDisplayText;`
- L40 _public member_ `ELiteralType PreferredLiteralType = ELiteralType::Invalid;` — The preferred constructor argument type for creating instances of the data type.
- L43 _public member_ `bool bIsParsable = false;` — Constructor argument support in TDataTypeLiteralFactory<TDataType>;
- L44 _public member_ `bool bIsDefaultParsable = false;`
- L45 _public member_ `bool bIsBoolParsable = false;`
- L46 _public member_ `bool bIsIntParsable = false;`
- L47 _public member_ `bool bIsFloatParsable = false;`
- L48 _public member_ `bool bIsStringParsable = false;`
- L49 _public member_ `bool bIsProxyParsable = false;`
- L50 _public member_ `bool bIsUniquePtrProxyParsable_DEPRECATED = false;`
- L51 _public member_ `bool bIsDefaultArrayParsable = false;`
- L52 _public member_ `bool bIsBoolArrayParsable = false;`
- L53 _public member_ `bool bIsIntArrayParsable = false;`
- L54 _public member_ `bool bIsFloatArrayParsable = false;`
- L55 _public member_ `bool bIsStringArrayParsable = false;`
- L56 _public member_ `bool bIsProxyArrayParsable = false;`
- L57 _public member_ `bool bIsUniquePtrProxyArrayParsable_DEPRECATED = false;`
- L60 _public member_ `bool bIsEnum = false;` — Is a TEnum wrapped enum
- L63 _public member_ `bool bIsExplicit = false;` — Whether exact types are required
- L66 _public member_ `bool bIsTransmittable = false;` — Determines whether the type can be used with send/receive transmitters
- L69 _public member_ `bool bIsVariable = false;` — Returns if DataType is a Variable type
- L72 _public member_ `bool bIsConstructorType = false;` — Returns if DataType can be used for constructor vertices.
- L75 _public member_ `bool bIsArrayType = false;` — Returns if DataType represents an array type (ex. TArray<float>, TArray<int32>, etc.).
- L78 _public member_ `bool bIsArrayParseable = false;` — Returns if DataType supports array parsing and passing array of base type to constructor.
- L81 _public member_ `UClass* ProxyGeneratorClass = nullptr;` — If provided in registration call, UClass this datatype was registered with.
- L84 _public function_ `const bool IsDataTypeProxyParsable() const` — Whether the data type can be created from a UObject proxy.
- L90 _public member_ `bool bIsPolymorphic = false;` — If this type is polymorphic.
- L91 _public member_ `bool bIsAbstract = false;`
- L94 _public member_ `FName ParentDataTypeName = {};` — If this type is polymorphic, what is its parent.

#### struct `Metasound::Frontend::IEnumDataTypeInterface`  
`struct IEnumDataTypeInterface`  
_L98-142_
- desc: Interface for metadata of a registered MetaSound enum type.
- L100 _public typedef_ `using FGenericInt32Entry = TEnumEntry<int32>;`
- L102 _public prototype_ `virtual ~IEnumDataTypeInterface() = default;`
- L104 _public prototype_ `virtual const TArray<FGenericInt32Entry>& GetAllEntries() const = 0;`
- L105 _public prototype_ `virtual FName GetNamespace() const = 0;`
- L106 _public prototype_ `virtual int32 GetDefaultValue() const = 0;`
- L109 _public function_ `template<typename Predicate> TOptional<FGenericInt32Entry> FindEntryBy(Predicate Pred) const`
- L118 _public function_ `TOptional<FGenericInt32Entry> FindByValue(int32 InEnumValue) const`
- L122 _public function_ `TOptional<FGenericInt32Entry> FindByName(FName InEnumName) const`
- L126 _public function_ `TOptional<FName> ToName(int32 InEnumValue) const`
- L134 _public function_ `TOptional<int32> ToValue(FName InName) const`

#### class `Metasound::Frontend::IDataTypeRegistryEntry`  
`class IDataTypeRegistryEntry`  
_L147-269_
- desc: Registry entry interface for a MetaSound data type.
- L150 _public prototype_ `virtual ~IDataTypeRegistryEntry() = default;`
- L153 _public prototype_ `virtual const FDataTypeRegistryInfo& GetDataTypeInfo() const = 0;` — Return the FDataTypeRegistryInfo for the data type
- L158 _public prototype_ `virtual TSharedPtr<const IEnumDataTypeInterface> GetEnumInterface() const = 0;` — Return the enum interface for the data type. If the data type does not support an enum interface, the returned pointer should be invalid.
- L164 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendInputClass() const = 0;` — Return an FMetasoundFrontendClass representing an input node of the data type.
- L167 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetInputClassMetadata() const = 0;` — Return an FNodeClassMetadata representing an input node of the data type.
- L170 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendConstructorInputClass() const = 0;` — Return an FMetasoundFrontendClass representing an input node of the data type.
- L173 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetConstructorInputClassMetadata() const = 0;` — Return an FNodeClassMetadata representing an input node of the data type.
- L176 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendLiteralClass() const = 0;` — Return an FMetasoundFrontendClass representing a variable node of the data type.
- L179 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendOutputClass() const = 0;` — Return an FMetasoundFrontendClass representing an output node of the data type.
- L182 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetOutputClassMetadata() const = 0;` — Return an FNodeClassMetadata representing an output node of the data type.
- L185 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendConstructorOutputClass() const = 0;` — Return an FMetasoundFrontendClass representing an input node of the data type.
- L188 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetConstructorOutputClassMetadata() const = 0;` — Return an FNodeClassMetadata representing an input node of the data type.
- L191 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendVariableClass() const = 0;` — Return an FMetasoundFrontendClass representing an init variable node of the data type.
- L194 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetVariableClassMetadata() const = 0;` — Return an FNodeClassMetadata representing an init variable node of the data type.
- L197 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendVariableMutatorClass() const = 0;` — Return an FMetasoundFrontendClass representing an set variable node of the data type.
- L200 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetVariableMutatorClassMetadata() const = 0;` — Return an FNodeClassMetadata representing an set variable node of the data type.
- L203 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendVariableAccessorClass() const = 0;` — Return an FMetasoundFrontendClass representing an get variable node of the data type.
- L206 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetVariableAccessorClassMetadata() const = 0;` — Return an FNodeClassMetadata representing an get variable node of the data type.
- L209 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendVariableDeferredAccessorClass() const = 0;` — Return an FMetasoundFrontendClass representing an get delayed variable node of the data type.
- L212 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetVariableDeferredAccessorClassMetadata() const = 0;` — Return an FNodeClassMetadata representing an get delayed variable node of the data type.
- L215 _public prototype_ `virtual TUniquePtr<INode> CreateInputNode(FNodeData InNodeData) const = 0;` — Create an input node
- L218 _public prototype_ `virtual TUniquePtr<INode> CreateConstructorInputNode(FNodeData InNodeData) const = 0;` — Create a constructor input node
- L221 _public prototype_ `virtual TUniquePtr<INode> CreateOutputNode(FNodeData InNodeData) const = 0;` — Create an output node
- L224 _public prototype_ `virtual TUniquePtr<INode> CreateConstructorOutputNode(FNodeData InNodeData) const = 0;` — Create a constructor output node
- L228 _public prototype_ `virtual TUniquePtr<INode> CreateLiteralNode(FLiteralNodeConstructorParams&&) const = 0;` — `UE_DEPRECATED(5.6, "Direct creation of literal nodes will no longer be supported")` — Create a literal node (deprecated — literal values should be set on the connected node directly).
- L232 _public prototype_ `virtual TUniquePtr<INode> CreateReceiveNode(const FNodeInitData&) const = 0;` — `UE_DEPRECATED(5.6, "Direct creation of receive nodes will no longer be supported")` — Create a receive node for this data type.
- L235 _public prototype_ `virtual const IParameterAssignmentFunction& GetRawAssignmentFunction() const = 0;` — Get function that should be used when a parameter pack contains a setting this data type.
- L238 _public prototype_ `virtual FLiteralAssignmentFunction GetLiteralAssignmentFunction() const = 0;` — Get a function that can be used to assign a FLiteral to a FAnyDataReference.
- L244 _public prototype_ `virtual TUniquePtr<INode> CreateVariableNode(FLiteral InInitValue, FNodeData) const = 0;` — Create a init variable node for this data type. @param InInitValue - A literal used to create the variable.
- L247 _public prototype_ `virtual TUniquePtr<INode> CreateVariableMutatorNode(FNodeData) const = 0;` — Create a set variable node for this data type.
- L250 _public prototype_ `virtual TUniquePtr<INode> CreateVariableAccessorNode(FNodeData) const = 0;` — Create a get variable node for this data type.
- L253 _public prototype_ `virtual TUniquePtr<INode> CreateVariableDeferredAccessorNode(FNodeData) const = 0;` — Create a get delayed variable node for this data type.
- L256 _public prototype_ `virtual TOptional<FAnyDataReference> CreateDataReference(EDataReferenceAccessType InAccessType, const FLiteral& InLiteral, const FOperatorSettings& InOperatorSettings) const = 0;` — Create a data reference from a literal.
- L260 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxy(UObject* InObject) const = 0;` — Create a proxy from a UObject. If this data type does not support UObject proxies, return a nullptr.
- L264 _public prototype_ `virtual TSharedPtr<IDataChannel, ESPMode::ThreadSafe> CreateDataChannel(const FOperatorSettings&) const = 0;` — Create a data channel for transmission. If this data type does not support transmission, return a nullptr.
- L268 _public function_ `virtual TUniquePtr<IDataTypeRegistryEntry> Clone() const` — `UE_DEPRECATED(5.6, "Cloning is not required for IDataTypeRegistryEntries")` — Clone this registry entry.

#### class `Metasound::Frontend::IDataTypeRegistry`  
`class IDataTypeRegistry`  
_L271-399_
- L274 _public prototype_ `static IDataTypeRegistry& Get();`
- L275 _public prototype_ `virtual ~IDataTypeRegistry() = default;`
- L282 _public prototype_ `virtual bool RegisterDataType(TUniquePtr<IDataTypeRegistryEntry>&& InEntry) = 0;` — Register a data type @param InEntry - TUniquePtr to data type registry entry. @return True on success, false on failure.
- L289 _public prototype_ `virtual bool UnregisterDataType(const FName& InDataTypeName) = 0;` — Unregister a data type. @param InDataTypeName @return True on success, false on failure.
- L292 _public prototype_ `virtual void GetRegisteredDataTypeNames(TArray<FName>& OutNames) const = 0;` — Provides all names of registered DataTypes.
- L294 _public prototype_ `virtual const IDataTypeRegistryEntry* FindDataTypeRegistryEntry(const FName& InDataTypeName) const = 0;`
- L297 _public prototype_ `virtual bool GetDataTypeInfo(const UObject* InObject, FDataTypeRegistryInfo& OutInfo) const = 0;` — Returns DataType info associated with the provided object.
- L300 _public prototype_ `virtual bool GetDataTypeInfo(UClass* InClass, FDataTypeRegistryInfo& OutInfo) const = 0;` — Returns DataType info associated with the provided object class.
- L303 _public prototype_ `virtual bool GetDataTypeInfo(const FName& InDataType, FDataTypeRegistryInfo& OutInfo) const = 0;` — Returns DataType info associated with the provided DataType name.
- L306 _public prototype_ `virtual void IterateDataTypeInfo(TFunctionRef<void(const FDataTypeRegistryInfo&)> InFunction) const = 0;` — Iterates all registered data type info
- L309 _public prototype_ `virtual bool IsRegistered(const FName& InDataType) const = 0;` — Returns whether or not a DataType is registered with the given name.
- L312 _public prototype_ `virtual TSharedPtr<const IEnumDataTypeInterface> GetEnumInterfaceForDataType(const FName& InDataType) const = 0;` — Return the enum interface for a data type. If the data type does not have an enum interface, returns a nullptr.
- L314 _public prototype_ `virtual ELiteralType GetDesiredLiteralType(const FName& InDataType) const = 0;`
- L316 _public prototype_ `virtual bool IsLiteralTypeSupported(const FName& InDataType, ELiteralType InLiteralType) const = 0;`
- L317 _public prototype_ `virtual bool IsLiteralTypeSupported(const FName& InDataType, EMetasoundFrontendLiteralType InLiteralType) const = 0;`
- L318 _public prototype_ `virtual bool IsUObjectProxyFactory(UObject* InObject) const = 0;`
- L319 _public prototype_ `virtual bool IsValidUObjectForDataType(const FName& InDataTypeName, const UObject* InUObject) const = 0;`
- L321 _public prototype_ `virtual UClass* GetUClassForDataType(const FName& InDataType) const = 0;`
- L323 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyFromUObject(const FName& InDataType, UObject* InObject) const = 0;`
- L325 _public prototype_ `virtual FLiteral CreateDefaultLiteral(const FName& InDataType) const = 0;`
- L326 _public prototype_ `virtual FLiteral CreateLiteralFromUObject(const FName& InDataType, UObject* InObject) const = 0;`
- L327 _public prototype_ `virtual FLiteral CreateLiteralFromUObjectArray(const FName& InDataType, const TArray<UObject*>& InObjectArray) const = 0;`
- L330 _public prototype_ `virtual TOptional<FAnyDataReference> CreateDataReference(const FName& InDataType, EDataReferenceAccessType InAccessType, const FLiteral& InLiteral, const FOperatorSettings& InOperatorSettings) const = 0;` — Create a data reference of the data type given a literal. If not supported, the result will be not be set.
- L332 _public prototype_ `virtual TSharedPtr<IDataChannel, ESPMode::ThreadSafe> CreateDataChannel(const FName& InDataType, const FOperatorSettings& InOperatorSettings) const = 0;`
- L335 _public prototype_ `virtual const IParameterAssignmentFunction& GetRawAssignmentFunction(const FName& InDataType) const = 0;` — Get function that should be used when a parameter pack contains a setting for the specified data type.
- L338 _public prototype_ `virtual FLiteralAssignmentFunction GetLiteralAssignmentFunction(const FName& InDataType) const = 0;` — Get a function that can be used to assign a FLiteral to a FAnyDataReference.
- L341 _public prototype_ `virtual bool GetFrontendInputClass(const FName& InDataType, FMetasoundFrontendClass& OutClass) const = 0;` — Return an FMetasoundFrontendClass representing an input node of the data type.
- L344 _public prototype_ `virtual bool GetFrontendConstructorInputClass(const FName& InDataType, FMetasoundFrontendClass& OutClass) const = 0;` — Return an FMetasoundFrontendClass representing an input node of the data type.
- L347 _public prototype_ `virtual bool GetFrontendLiteralClass(const FName& InDataType, FMetasoundFrontendClass& OutClass) const = 0;` — Return an FMetasoundFrontendClass representing a variable node of the data type.
- L350 _public prototype_ `virtual bool GetFrontendOutputClass(const FName& InDataType, FMetasoundFrontendClass& OutClass) const = 0;` — Return an FMetasoundFrontendClass representing an output node of the data type.
- L353 _public prototype_ `virtual bool GetFrontendConstructorOutputClass(const FName& InDataType, FMetasoundFrontendClass& OutClass) const = 0;` — Return an FMetasoundFrontendClass representing an output node of the data type.
- L356 _public prototype_ `virtual bool GetFrontendVariableClass(const FName& InDataType, FMetasoundFrontendClass& OutClass) const = 0;` — Return an FMetasoundFrontendClass representing an init variable node of the data type.
- L359 _public prototype_ `virtual bool GetFrontendVariableMutatorClass(const FName& InDataType, FMetasoundFrontendClass& OutClass) const = 0;` — Return an FMetasoundFrontendClass representing an set variable node of the data type.
- L362 _public prototype_ `virtual bool GetFrontendVariableAccessorClass(const FName& InDataType, FMetasoundFrontendClass& OutClass) const = 0;` — Return an FMetasoundFrontendClass representing an get variable node of the data type.
- L365 _public prototype_ `virtual bool GetFrontendVariableDeferredAccessorClass(const FName& InDataType, FMetasoundFrontendClass& OutClass) const = 0;` — Return an FMetasoundFrontendClass representing an get delayed variable node of the data type.
- L370 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetInputClassMetadata(const FName& InDataType) const = 0;`
- L371 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetConstructorInputClassMetadata(const FName& InDataType) const = 0;`
- L372 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetOutputClassMetadata(const FName& InDataType) const = 0;`
- L373 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetConstructorOutputClassMetadata(const FName& InDataType) const = 0;`
- L374 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetVariableClassMetadata(const FName& InDataType) const = 0;`
- L375 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetVariableMutatorClassMetadata(const FName& InDataType) const = 0;`
- L376 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetVariableAccessorClassMetadata(const FName& InDataType) const = 0;`
- L377 _public prototype_ `virtual TSharedPtr<const FNodeClassMetadata> GetVariableDeferredAccessorClassMetadata(const FName& InDataType) const = 0;`
- L384 _public prototype_ `virtual TUniquePtr<INode> CreateInputNode(const FName& InInputType, FNodeData InNodeData) const = 0;`
- L385 _public prototype_ `virtual TUniquePtr<INode> CreateConstructorInputNode(const FName& InInputType, FNodeData InNodeData) const = 0;`
- L388 _public prototype_ `virtual TUniquePtr<INode> CreateLiteralNode(const FName& InLiteralType, FLiteralNodeConstructorParams&& InParams) const = 0;` — `UE_DEPRECATED(5.6, "Direct creation of literal nodes will no longer be supported")`
- L391 _public prototype_ `virtual TUniquePtr<INode> CreateReceiveNode(const FName& InDataType, const FNodeInitData&) const = 0;` — `UE_DEPRECATED(5.6, "Direct creation of receive nodes will no longer be supported")`
- L393 _public prototype_ `virtual TUniquePtr<INode> CreateOutputNode(const FName& InDataTypeName, FNodeData InNodeData) const = 0;`
- L394 _public prototype_ `virtual TUniquePtr<INode> CreateConstructorOutputNode(const FName& InDataTypeName, FNodeData InNodeData) const = 0;`
- L395 _public prototype_ `virtual TUniquePtr<INode> CreateVariableNode(const FName& InDataType, FLiteral InLiteral, FNodeData InNodeData) const = 0;`
- L396 _public prototype_ `virtual TUniquePtr<INode> CreateVariableMutatorNode(const FName& InDataType, FNodeData InNodeData) const = 0;`
- L397 _public prototype_ `virtual TUniquePtr<INode> CreateVariableAccessorNode(const FName& InDataType, FNodeData InNodeData) const = 0;`
- L398 _public prototype_ `virtual TUniquePtr<INode> CreateVariableDeferredAccessorNode(const FName& InDataType, FNodeData InNodeData) const = 0;`

#### struct `Metasound::Frontend::IPolymorphicDataTypeInterface`  
`struct IPolymorphicDataTypeInterface`  
_L405-410_
- desc: IPolymorphicDataTypeInterface. Experimental API.
- L407 _public prototype_ `virtual ~IPolymorphicDataTypeInterface() = default;`

#### class `Metasound::Frontend::FPolymorphicDataTypeBase`  
`class FPolymorphicDataTypeBase : public IPolymorphicDataTypeInterface`  
_L416-430_
- inherits: `IPolymorphicDataTypeInterface`
- desc: FPolymorphicDataTypeBase Experimental API.
- L419 _public prototype_ `FPolymorphicDataTypeBase(const FName InDataTypeName, const FName InParentName = NAME_None, const bool InbIsAbstract = false);`
- L420 _public prototype_ `virtual ~FPolymorphicDataTypeBase() override = default;`
- L425 _private prototype_ `void ResolveParent(const IDataTypeRegistry& InRegistry) const;`
- L426 _private member_ `FName DataTypeName = NAME_None;`
- L427 _private member_ `FName ParentTypeName = NAME_None;`
- L428 _private member_ `bool bIsAbstract = false;`
- L429 _private member_ `mutable TWeakPtr<const IPolymorphicDataTypeInterface> ParentDataType;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L18 _namespace_ `namespace Metasound`
- L22 _namespace_ `namespace Frontend` (scope `Metasound`)
- L24 _typedef_ `using IParameterAssignmentFunction = TUniqueFunction<void(const void*,void*)>;` (scope `Metasound::Frontend`)
- L27 _typedef_ `using FLiteralAssignmentFunction = void(*)(const FOperatorSettings& InOperatorSettings, const FLiteral& InLiteral, const FAnyDataReference& OutDataRef);` (scope `Metasound::Frontend`) — Function signature for assigning a FLiteral to a FAnyDataReference
- L120 _function_ `return FindEntryBy([InEnumValue](const FGenericInt32Entry& i) -> bool { return i.Value == InEnumValue; });` (scope `Metasound::Frontend::IEnumDataTypeInterface::FindByValue`)
- L124 _function_ `return FindEntryBy([InEnumName](const FGenericInt32Entry& i) -> bool { return i.Name == InEnumName; });` (scope `Metasound::Frontend::IEnumDataTypeInterface::FindByName`)
- L438 _prototype_ `void CreateDefaults(const FOperatorSettings& InOperatorSettings, FInputVertexInterfaceData& OutVertexData);` (scope `Metasound::Frontend`) — Create data references for all inputs on the FInputVertexInterfaceData using the default literals which live on the FInputDataVertexes. If the vertex has access type EVertexAccessType::Reference, a writable data reference will be set, otherwise a value data reference will be set.
- L447 _prototype_ `void CreateDefaultsIfNotBound(const FOperatorSettings& InOperatorSettings, FInputVertexInterfaceData& OutVertexData);` (scope `Metasound::Frontend`) — Create data references for all inputs on the FInputVertexInterfaceData which do not already have a data reference bound. Defaults are created using the default literals which live on the FInputDataVertexes. If the vertex has access type EVertexAccessType::Reference, a writable data reference will be set, otherwise a value data reference will be set.

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendDataTypeTraits.h` (Public)


#### struct `Metasound::TEnableAutoArrayTypeRegistration`  
`template<typename ... Type> struct TEnableAutoArrayTypeRegistration`  
_L16-19_
- desc: Enables or disables automatic registration of array types given a MetaSound data type. By default this is true, and all data types will have an associated TArray<DataType> registered if it is supported.
- L18 _public member_ `static constexpr bool Value = true;`

#### struct `Metasound::TEnableAutoConverterNodeRegistration`  
`template<typename ... Type> struct TEnableAutoConverterNodeRegistration`  
_L26-29_
- desc: Enables or disables automatic registration of auto conversion nodes given a MetaSound data type. By default this is true, and all data types will have associated conversion nodes registered based upon the data types supported constructors and implicit conversions.
- L28 _public member_ `static constexpr bool Value = true;`

#### struct `Metasound::TEnableTransmissionNodeRegistration`  
`template<typename ... Type> struct TEnableTransmissionNodeRegistration`  
_L34-37_
- desc: Enables or disables send and receive node registration for a given MetaSound data type. By default this is false because send/receive nodes are deprecated.
- L36 _public member_ `static constexpr bool Value = false;`
- L42 _public member_ `static constexpr bool Value = TEnableTransmissionNodeRegistration<ElementType>::Value;`

#### struct `Metasound::TEnableTransmissionNodeRegistration`  
`template<typename ElementType> struct TEnableTransmissionNodeRegistration<TArray<ElementType>>`  
_L40-43_
- L36 _public member_ `static constexpr bool Value = false;`
- L42 _public member_ `static constexpr bool Value = TEnableTransmissionNodeRegistration<ElementType>::Value;`

#### struct `Metasound::TEnableConstructorVertex`  
`template<typename ... Type> struct TEnableConstructorVertex`  
_L49-52_
- desc: Enables or disables using a data type in constructor vertices. By default this is true and all data types that support copy assignment and copy construction.
- L51 _public member_ `static constexpr bool Value = true;`

#### struct `Metasound::TIsCopyable`  
`template <typename TDataType> struct TIsCopyable`  
_L56-64_
- desc: Helper utility to test if we a datatype is copyable
- L59 _private member_ `static constexpr bool bIsCopyConstructible = std::is_copy_constructible<TDataType>::value;`
- L60 _private member_ `static constexpr bool bIsCopyAssignable = std::is_copy_assignable<TDataType>::value;`
- L63 _public member_ `static constexpr bool Value = bIsCopyConstructible && bIsCopyAssignable;`

#### struct `Metasound::TIsConstructorVertexSupported`  
`template<typename TDataType> struct TIsConstructorVertexSupported`  
_L68-76_
- desc: Helper to test if data type can be used on constructor pins.
- L71 _private member_ `static constexpr bool bIsParsable = TLiteralTraits<TDataType>::bIsParsableFromAnyLiteralType;`
- L72 _private member_ `static constexpr bool bIsCopyable = TIsCopyable<TDataType>::Value;`
- L73 _private member_ `static constexpr bool bIsEnabled = TEnableConstructorVertex<TDataType>::Value;`
- L75 _public member_ `static constexpr bool Value = bIsParsable && bIsCopyable && bIsEnabled;`

#### struct `Metasound::TIsExplicit`  
`template <typename TDataType> struct TIsExplicit`  
_L80-83_
- desc: Helper utility to test if exact types are required for a datatype.
- L82 _public member_ `static constexpr bool Value = false;`

#### struct `Metasound::TIsTransmittable`  
`template <typename TDataType> struct TIsTransmittable`  
_L87-90_
- desc: Helper utility to test if we can transmit a datatype between a send and a receive node.
- L89 _public member_ `static constexpr bool Value = TIsCopyable<TDataType>::Value;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendDocument.h` (Public)


#### class `FMetasoundFrontendDocumentModifyContext`  
`class FMetasoundFrontendDocumentModifyContext`  
_L76-125_
- desc: Struct containing any modified data breadcrumbs to inform what the editor/view layer must synchronize or refresh.
- L80 _private member_ `bool bDocumentModified = true;` — Whether or not the owning asset's MetaSoundDocument has been modified. True by default to force refreshing views on loading/reloading asset.
- L83 _private member_ `bool bForceRefreshViews = true;` — Whether or not to force refresh all views. True by default to force refreshing views on loading/reloading asset.
- L86 _private member_ `TSet<FName> InterfacesModified;` — Which Interfaces have been modified since the last editor graph synchronization
- L89 _private member_ `TSet<FGuid> MemberIDsModified;` — Which MemberIDs have been modified since the last editor graph synchronization
- L92 _private member_ `TSet<FGuid> NodeIDsModified;` — Which NodeIDs have been modified since the last editor graph synchronization
- L95 _public prototype_ `void ClearDocumentModified();`
- L97 _public prototype_ `bool GetDocumentModified() const;`
- L98 _public prototype_ `bool GetForceRefreshViews() const;`
- L99 _public prototype_ `const TSet<FName>& GetInterfacesModified() const;`
- L100 _public prototype_ `const TSet<FGuid>& GetNodeIDsModified() const;`
- L101 _public prototype_ `const TSet<FGuid>& GetMemberIDsModified() const;`
- L103 _public prototype_ `void Reset();`
- L105 _public prototype_ `void SetDocumentModified();`
- L106 _public prototype_ `void SetForceRefreshViews();`
- L109 _public prototype_ `void AddInterfaceModified(FName InInterfaceModified);` — Adds an interface name to the set of interfaces that have been modified since last context reset/construction
- L112 _public prototype_ `void AddInterfacesModified(const TSet<FName>& InInterfacesModified);` — Performs union of provided interface set with the set of interfaces that have been modified since last context reset/construction
- L115 _public prototype_ `void AddMemberIDModified(const FGuid& InMemberNodeIDModified);` — Adds a MemberID to the set of MemberIDs that have been modified since last context reset/construction
- L118 _public prototype_ `void AddMemberIDsModified(const TSet<FGuid>& InMemberIDsModified);` — Performs union of provided MemberIDs set with the set of MemberIDs that have been modified since last context reset/construction
- L121 _public prototype_ `void AddNodeIDModified(const FGuid& InNodeIDModified);` — Performs union of provided NodeID set with the set of NodeIDs that have been modified since last context reset/construction
- L124 _public prototype_ `void AddNodeIDsModified(const TSet<FGuid>& InNodeIDsModified);` — Performs union of provided NodeID set with the set of NodeIDs that have been modified since last context reset/construction

#### enum `EMetasoundFrontendVertexAccessType`  
`enum class EMetasoundFrontendVertexAccessType`  
_L131-139_
- reflection: `UENUM()`
- desc: Describes how a vertex accesses the data connected to it.
- L133 _public enumerator_ `Reference` — The vertex accesses data by reference.
- L134 _public enumerator_ `Value` — The vertex accesses data by value.
- L136 _public enumerator_ `Unset` — The vertex access level is unset (ex. vertex on an unconnected reroute node).

#### enum `EMetasoundFrontendClassAccessFlags`  
`enum class EMetasoundFrontendClassAccessFlags : uint16`  
_L142-155_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L144 _public enumerator_ `None = 0 UMETA(Hidden)`
- L148 _public enumerator_ `Deprecated = 1 << 0` — Class is marked as deprecated when referenced by MetaSounds in the editor.
- L152 _public enumerator_ `Referenceable = 1 << 1` — If set, MetaSound can be referenced by other MetaSounds in either editor or by builder Blueprint API.
- L154 _public enumerator_ `Default = Referenceable UMETA(Hidden)`

#### enum `EMetasoundFrontendClassType`  
`enum class EMetasoundFrontendClassType : uint8`  
_L171-205_
- reflection: `UENUM(MinimalAPI)`
- L174 _public enumerator_ `External = 0` — The MetaSound class is defined externally, in compiled code or in another document.
- L177 _public enumerator_ `Graph` — The MetaSound class is a graph within the containing document.
- L180 _public enumerator_ `Input` — The MetaSound class is an input into a graph in the containing document.
- L183 _public enumerator_ `Output` — The MetaSound class is an output from a graph in the containing document.
- L186 _public enumerator_ `Literal` — The MetaSound class is an literal requiring a literal value to construct.
- L189 _public enumerator_ `Variable` — The MetaSound class is an variable requiring a literal value to construct.
- L192 _public enumerator_ `VariableDeferredAccessor` — The MetaSound class accesses variables.
- L195 _public enumerator_ `VariableAccessor` — The MetaSound class accesses variables.
- L198 _public enumerator_ `VariableMutator` — The MetaSound class mutates variables.
- L202 _public enumerator_ `Template` — The MetaSound class is defined only by the Frontend, and associatively performs a functional operation within the given document in a registration/cook step.
- L204 _public enumerator_ `Invalid UMETA(Hidden)`

#### enum `EMetaSoundFrontendGraphCommentMoveMode`  
`enum class EMetaSoundFrontendGraphCommentMoveMode : uint8`  
_L208-215_
- reflection: `UENUM()`
- L211 _public enumerator_ `GroupMovement UMETA(DisplayName = "Group Movement")` — This comment box will move any fully contained nodes when it moves.
- L214 _public enumerator_ `NoGroupMovement UMETA(DisplayName = "Comment")` — This comment box has no effect on nodes contained inside it.

#### struct `FMetasoundCommentNodeIntVector`  
`struct FMetasoundCommentNodeIntVector : public FIntVector2`  
_L224-247_
- reflection: `USTRUCT()`
- inherits: `FIntVector2`
- desc: Migratory type to avoid adding dependency on Slate FDeprecateSlateVector2D, and by extension, bring in unnecessary Engine dependencies therein.  At one point, this dependency was incorrectly added leading to in-determinant serialization as either a double or a float vector. This type exists to resolve that discrepancy properly. Considered soft deprecated and not to be used for runtime.
- L228 _public prototype_ `FMetasoundCommentNodeIntVector() = default;`
- L229 _public prototype_ `FMetasoundCommentNodeIntVector(const FIntVector2& InValue);`
- L230 _public prototype_ `FMetasoundCommentNodeIntVector(const FVector2f& InValue);`
- L231 _public prototype_ `FMetasoundCommentNodeIntVector(const FVector2d& InValue);`
- L234 _public prototype_ `FMetasoundCommentNodeIntVector(const FDeprecateSlateVector2D& InValue);`
- L237 _public prototype_ `FMetasoundCommentNodeIntVector& operator=(const FVector2f& InValue);`
- L238 _public prototype_ `FMetasoundCommentNodeIntVector& operator=(const FVector2d& InValue);`
- L239 _public prototype_ `FMetasoundCommentNodeIntVector& operator=(const FIntVector2& InValue);`
- L242 _public prototype_ `FMetasoundCommentNodeIntVector& operator=(const FDeprecateSlateVector2D& InValue);`
- L245 _public prototype_ `bool Serialize(FStructuredArchive::FSlot Slot);`
- L246 _public prototype_ `bool SerializeFromMismatchedTag(const struct FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMetasoundCommentNodeIntVector> : TStructOpsTypeTraitsBase2<FMetasoundCommentNodeIntVector>`  
_L250-257_
- inherits: `TStructOpsTypeTraitsBase2<FMetasoundCommentNodeIntVector>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L254-256_

#### struct `FMetaSoundFrontendGraphComment`  
`struct FMetaSoundFrontendGraphComment`  
_L261-290_
- reflection: `USTRUCT()`
- L267 _public member_ `FLinearColor Color = FLinearColor::Black;` — `UPROPERTY()`
- L270 _public member_ `FString Comment;` — `UPROPERTY()`
- L273 _public member_ `int32 Depth = 0;` — `UPROPERTY()`
- L276 _public member_ `int32 FontSize = 0;` — `UPROPERTY()`
- L279 _public member_ `FMetasoundCommentNodeIntVector Position = FIntVector2::ZeroValue;` — `UPROPERTY()`
- L282 _public member_ `FMetasoundCommentNodeIntVector Size = FIntVector2::ZeroValue;` — `UPROPERTY()`
- L285 _public member_ `EMetaSoundFrontendGraphCommentMoveMode MoveMode = EMetaSoundFrontendGraphCommentMoveMode::GroupMovement;` — `UPROPERTY()`
- L288 _public member_ `uint8 bColorBubble : 1;` — `UPROPERTY()`

#### struct `FMetasoundFrontendVersionNumber`  
`struct FMetasoundFrontendVersionNumber`  
_L294-369_
- reflection: `USTRUCT(BlueprintType)`
- desc: General purpose version number for Metasound Frontend objects.
- L298 _public prototype_ `static bool Parse(const FString& InString, FMetasoundFrontendVersionNumber& OutVersionNumber);`
- L302 _public member_ `int32 Major = 1;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = General)` — Major version number.
- L306 _public member_ `int32 Minor = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = General)` — Minor version number.
- L308 _public prototype_ `static const FMetasoundFrontendVersionNumber& GetInvalid();`
- L309 _public prototype_ `bool IsValid() const;`
- L311 _public prototype_ `Audio::FParameterInterface::FVersion ToInterfaceVersion() const;`
- L363 _public prototype_ `FString ToString() const;`

#### struct `FMetasoundFrontendVersion`  
`struct FMetasoundFrontendVersion`  
_L373-445_
- reflection: `USTRUCT(BlueprintType)`
- desc: General purpose version info for Metasound Frontend objects.
- L379 _public member_ `FName Name;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CustomView)` — Name of version.
- L383 _public member_ `FMetasoundFrontendVersionNumber Number;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CustomView)` — Version number.
- L385 _public prototype_ `FString ToString() const;`
- L387 _public prototype_ `bool IsValid() const;`
- L389 _public prototype_ `static const FMetasoundFrontendVersion& GetInvalid();`

#### struct `FMetasoundFrontendVertex`  
`struct FMetasoundFrontendVertex`  
_L449-469_
- reflection: `USTRUCT()`
- desc: An FMetasoundFrontendVertex provides a named connection point of a node.
- L455 _public member_ `FName Name;` — `UPROPERTY(VisibleAnywhere, Category = CustomView)` — Name of the vertex. Unique amongst other vertices on the same interface.
- L459 _public member_ `FName TypeName;` — `UPROPERTY(VisibleAnywhere, Category = Parameters)` — Data type name of the vertex.
- L463 _public member_ `FGuid VertexID;` — `UPROPERTY()` — ID of vertex
- L466 _public prototype_ `static bool IsFunctionalEquivalent(const FMetasoundFrontendVertex& InLHS, const FMetasoundFrontendVertex& InRHS);` — Returns true if vertices have equal name & type.

#### struct `FMetasoundFrontendVertexHandle`  
`struct FMetasoundFrontendVertexHandle`  
_L473-505_
- reflection: `USTRUCT()`
- desc: Pair of guids used to address location of vertex within a FrontendDocument graph
- L479 _public member_ `FGuid NodeID;` — `UPROPERTY()`
- L482 _public member_ `FGuid VertexID;` — `UPROPERTY()`
- L486 _public function_ `bool IsSet() const` — Returns whether or not the vertex handle is set (may or may not be valid depending on what builder context it is referenced against)

#### struct `FMetasoundFrontendVertexLiteral`  
`struct FMetasoundFrontendVertexLiteral`  
_L509-520_
- reflection: `USTRUCT()`
- desc: Contains a default value for a single vertex ID
- L515 _public member_ `FGuid VertexID = Metasound::FrontendInvalidID;` — `UPROPERTY(VisibleAnywhere, Category = Parameters)` — ID of vertex.
- L519 _public member_ `FMetasoundFrontendLiteral Value;` — `UPROPERTY(EditAnywhere, Category = Parameters)` — Value to use when constructing input.

#### struct `FMetasoundFrontendVariable`  
`struct FMetasoundFrontendVariable`  
_L524-570_
- reflection: `USTRUCT()`
- desc: Contains graph data associated with a variable.
- L530 _public member_ `FName Name;` — `UPROPERTY(VisibleAnywhere, Category = CustomView)` — Name of the vertex. Unique amongst other vertices on the same interface.
- L535 _public member_ `FText DisplayName;` — `UPROPERTY()` — Variable display name
- L539 _public member_ `FText Description;` — `UPROPERTY()` — Variable description
- L545 _public member_ `FName TypeName;` — `UPROPERTY()` — Variable data type name
- L549 _public member_ `FMetasoundFrontendLiteral Literal;` — `UPROPERTY()` — Literal used to initialize the variable.
- L553 _public member_ `FGuid ID = Metasound::FrontendInvalidID;` — `UPROPERTY()` — Unique ID for the variable
- L557 _public member_ `FGuid VariableNodeID = Metasound::FrontendInvalidID;` — `UPROPERTY()` — Node ID of the associated VariableNode
- L561 _public member_ `FGuid MutatorNodeID = Metasound::FrontendInvalidID;` — `UPROPERTY()` — Node ID of the associated VariableMutatorNode
- L565 _public member_ `TArray<FGuid> AccessorNodeIDs;` — `UPROPERTY()` — Node IDs of the associated VariableAccessorNodes
- L569 _public member_ `TArray<FGuid> DeferredAccessorNodeIDs;` — `UPROPERTY()` — Node IDs of the associated VariableDeferredAccessorNodes

#### struct `FMetasoundFrontendNodeInterface`  
`struct FMetasoundFrontendNodeInterface`  
_L574-602_
- reflection: `USTRUCT()`
- L578 _public prototype_ `FMetasoundFrontendNodeInterface() = default;`
- L581 _public prototype_ `FMetasoundFrontendNodeInterface(const FMetasoundFrontendClassInterface& InClassInterface);` — Create a node interface which satisfies an existing class interface.
- L586 _public prototype_ `bool Update(const FMetasoundFrontendClassInterface& InClassInterface);` — Update the current node interface with the given class interface Return true if interface update resulted in interface changes
- L589 _public prototype_ `bool Update(const FMetasoundFrontendClassInterface& InClassInterface, TFunctionRef<void(const FMetasoundFrontendVertex&)> OnPreRemoveInput, TFunctionRef<void(const FMetasoundFrontendVertex&)> OnPreRemoveOutput);`
- L593 _public member_ `TArray<FMetasoundFrontendVertex> Inputs;` — `UPROPERTY()` — Input vertices to node.
- L597 _public member_ `TArray<FMetasoundFrontendVertex> Outputs;` — `UPROPERTY()` — Output vertices to node.
- L601 _public member_ `TArray<FMetasoundFrontendVertex> Environment;` — `UPROPERTY()` — Environment variables of node.

#### struct `FMetaSoundFrontendNodeConfiguration`  
`struct FMetaSoundFrontendNodeConfiguration`  
_L630-642_
- reflection: `USTRUCT()`
- desc: Struct for configuring a node. You can inherit from this and include data passed to the operator and/or data used to determine an override of the node's interface. In order for node configuration data to be editable in the details panel, UProperties on your substruct should be marked with EditAnywhere. Optional custom details customizations can be registered via IMetasoundEditorModule::RegisterCustomNodeConfigurationDetailsCustomization Example: USTRUCT() struct FMetaSoundExperimentalExampleNodeConfiguration : public FMetaSoundFrontendNodeConfiguration { GENERATED_BODY() UPROPERTY(EditAnywhere, Category = General, meta = (ClampMin = "1", ClampMax = "1000")) uint32 NumInputs; virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const; virtual TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override; }
- L634 _public prototype_ `virtual ~FMetaSoundFrontendNodeConfiguration() = default;`
- L637 _public prototype_ `virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const;` — Get the current interface for the class based upon the node extension

#### enum `EMetasoundFrontendNodeStyleDisplayVisibility`  
`enum class EMetasoundFrontendNodeStyleDisplayVisibility : uint8`  
_L647-651_
- reflection: `UENUM()`
- desc: DEPRECATED in Document Model v1.1
- L649 _public enumerator_ `Visible`
- L650 _public enumerator_ `Hidden`

#### struct `FMetasoundFrontendNodeStyleDisplay`  
`struct FMetasoundFrontendNodeStyleDisplay`  
_L654-676_
- reflection: `USTRUCT()`
- L661 _public member_ `EMetasoundFrontendNodeStyleDisplayVisibility Visibility = EMetasoundFrontendNodeStyleDisplayVisibility::Visible;` — `UPROPERTY()` — DEPRECATED in Document Model v1.1: Visibility state of node
- L666 _public member_ `TMap<FGuid, FVector2D> Locations;` — `UPROPERTY()` — Map of visual node guid to 2D location. May have more than one if the node allows displaying in more than one place on the graph (Only functionally relevant for nodes that cannot contain inputs.)
- L670 _public member_ `FString Comment;` — `UPROPERTY()` — Comment to display about the given instance's usage
- L674 _public member_ `bool bCommentVisible = false;` — `UPROPERTY()` — Whether or not the comment is visible or not

#### struct `FMetasoundFrontendNodeStyle`  
`struct FMetasoundFrontendNodeStyle`  
_L679-701_
- reflection: `USTRUCT()`
- L686 _public member_ `FMetasoundFrontendNodeStyleDisplay Display;` — `UPROPERTY()` — Display style of a node
- L691 _public member_ `mutable bool bMessageNodeUpdated = false;` — `UPROPERTY(Transient)` — Whether or not to display if the node's version has been updated
- L694 _public member_ `bool bIsPrivate = false;` — `UPROPERTY()`
- L698 _public member_ `bool bUnconnectedPinsHidden = false;` — `UPROPERTY()` — Whether or not Unconnected pins are hidden

#### struct `FMetasoundFrontendEdge`  
`struct FMetasoundFrontendEdge`  
_L706-755_
- reflection: `USTRUCT()`
- desc: Represents a single connection from one point to another.
- L712 _public member_ `FGuid FromNodeID = Metasound::FrontendInvalidID;` — `UPROPERTY()` — ID of source node.
- L716 _public member_ `FGuid FromVertexID = Metasound::FrontendInvalidID;` — `UPROPERTY()` — ID of source point on source node.
- L720 _public member_ `FGuid ToNodeID = Metasound::FrontendInvalidID;` — `UPROPERTY()` — ID of destination node.
- L724 _public member_ `FGuid ToVertexID = Metasound::FrontendInvalidID;` — `UPROPERTY()` — ID of destination point on destination node.
- L726 _public function_ `FMetasoundFrontendVertexHandle GetFromVertexHandle() const`
- L731 _public function_ `FMetasoundFrontendVertexHandle GetToVertexHandle() const`

#### struct `FMetasoundFrontendEdgeStyleLiteralColorPair`  
`struct FMetasoundFrontendEdgeStyleLiteralColorPair`  
_L758-767_
- reflection: `USTRUCT()`
- L763 _public member_ `FMetasoundFrontendLiteral Value;` — `UPROPERTY()`
- L766 _public member_ `FLinearColor Color = Metasound::Frontend::DisplayStyle::EdgeAnimation::DefaultColor;` — `UPROPERTY()`

#### struct `FMetasoundFrontendEdgeStyle`  
`struct FMetasoundFrontendEdgeStyle`  
_L771-787_
- reflection: `USTRUCT()`
- desc: Styling for all edges associated with a given output (characterized by NodeID & Name)
- L777 _public member_ `FGuid NodeID;` — `UPROPERTY()` — Node ID for associated edge(s) that should use the given style data.
- L781 _public member_ `FName OutputName;` — `UPROPERTY()` — Name of node's output to associate style information for its associated edge(s).
- L786 _public member_ `TArray<FMetasoundFrontendEdgeStyleLiteralColorPair> LiteralColorPairs;` — `UPROPERTY()` — Array of colors used to animate given output's associated edge(s). Interpolation between values dependent on value used.

#### struct `FMetasoundFrontendGraphStyle`  
`struct FMetasoundFrontendGraphStyle`  
_L791-808_
- reflection: `USTRUCT()`
- desc: Styling for a class
- L798 _public member_ `bool bIsGraphEditable = true;` — `UPROPERTY()` — Whether or not the graph is editable by a user
- L802 _public member_ `TArray<FMetasoundFrontendEdgeStyle> EdgeStyles;` — `UPROPERTY()` — Styles for graph edges.
- L806 _public member_ `TMap<FGuid, FMetaSoundFrontendGraphComment> Comments;` — `UPROPERTY()` — Map of comment id to comment data

#### struct `FMetasoundFrontendVertexMetadata`  
`struct FMetasoundFrontendVertexMetadata`  
_L813-924_
- reflection: `USTRUCT()`
- desc: Metadata associated with a vertex.
- L821 _private member_ `FText DisplayName;` — `UPROPERTY(EditAnywhere, Category = Parameters, meta = (DisplayName = "Name"))` — Display name for a vertex
- L826 _private member_ `FText DisplayNameTransient;` — `UPROPERTY(Transient)` — Display name for a vertex if vertex is natively defined (must be transient to avoid localization desync on load)
- L830 _private member_ `FText Description;` — `UPROPERTY(EditAnywhere, Category = Parameters)` — Description of the vertex.
- L835 _private member_ `FText DescriptionTransient;` — `UPROPERTY(Transient)` — Description of the vertex if vertex is natively defined (must be transient to avoid localization desync on load)
- L840 _public member_ `int32 SortOrderIndex = 0;` — `UPROPERTY()` — Order index of vertex member when shown as a node.
- L844 _public member_ `bool bIsAdvancedDisplay = false;` — `UPROPERTY()` — If true, vertex is shown for advanced display.
- L853 _private member_ `bool bSerializeText = true;` — `UPROPERTY()` — Whether or not the given metadata text should be serialized or is procedurally maintained via auto-update & the referenced registry class (to avoid localization text desync).  Should be false for classes serialized as externally-defined dependencies or interfaces.
- L855 _private function_ `FText& GetDescription()`
- L860 _private function_ `FText& GetDisplayName()`
- L866 _public function_ `const FText& GetDescription() const`
- L871 _public function_ `const FText& GetDisplayName() const`
- L876 _public function_ `bool GetSerializeText() const`
- L881 _public function_ `void SetDescription(const FText& InText)`
- L886 _public function_ `void SetDisplayName(const FText& InText)`
- L891 _public function_ `void SetIsAdvancedDisplay(const bool InIsAdvancedDisplay)`
- L896 _public function_ `void SetSerializeText(bool bInSerializeText)`

#### struct `FMetasoundFrontendClassVertex`  
`struct FMetasoundFrontendClassVertex : public FMetasoundFrontendVertex`  
_L927-952_
- reflection: `USTRUCT()`
- inherits: `FMetasoundFrontendVertex`
- L932 _public member_ `FGuid NodeID = Metasound::FrontendInvalidID;` — `UPROPERTY()`
- L937 _public member_ `FMetasoundFrontendVertexMetadata Metadata;` — `UPROPERTY(EditAnywhere, Category = CustomView)` — Metadata associated with vertex.
- L939 _public function_ `const bool GetIsAdvancedDisplay() const`
- L943 _public member_ `EMetasoundFrontendVertexAccessType AccessType = EMetasoundFrontendVertexAccessType::Reference;` — `UPROPERTY()`
- L946 _public prototype_ `void SplitName(FName& OutNamespace, FName& OutParameterName) const;` — Splits name into namespace & parameter name
- L948 _public prototype_ `static bool IsFunctionalEquivalent(const FMetasoundFrontendClassVertex& InLHS, const FMetasoundFrontendClassVertex& InRHS);`
- L951 _public prototype_ `static bool CanConnectVertexAccessTypes(EMetasoundFrontendVertexAccessType InFromType, EMetasoundFrontendVertexAccessType InToType);` — Whether vertex access types are compatible when connecting from an output to an input

#### struct `FMetasoundFrontendClassStyleDisplay`  
`struct FMetasoundFrontendClassStyleDisplay`  
_L957-1000_
- reflection: `USTRUCT()`
- desc: Information regarding how to display a node class
- L962 _public prototype_ `FMetasoundFrontendClassStyleDisplay() = default;`
- L964 _public function_ `FMetasoundFrontendClassStyleDisplay(const Metasound::FNodeDisplayStyle& InDisplayStyle) : ImageName(InDisplayStyle.ImageName) , bShowName(InDisplayStyle.bShowName) , bShowInputNames(InDisplayStyle.bShowInputNames) , bShowOutputNames(InDisplayStyle.bShowOutputNames) , bShowLiterals(InDisplayStyle.bShowLiterals) , StyleSet(InDisplayStyle.StyleSet) , Icon(InDisplayStyle.Icon) , Color(InDisplayStyle.Color)`
- L977 _public member_ `FName ImageName;` — `UPROPERTY()`
- L980 _public member_ `bool bShowName = true;` — `UPROPERTY()`
- L983 _public member_ `bool bShowInputNames = true;` — `UPROPERTY()`
- L986 _public member_ `bool bShowOutputNames = true;` — `UPROPERTY()`
- L989 _public member_ `bool bShowLiterals = true;` — `UPROPERTY()`
- L992 _public member_ `FName StyleSet;` — `UPROPERTY()`
- L995 _public member_ `FName Icon;` — `UPROPERTY()`
- L998 _public member_ `FName Color;` — `UPROPERTY()`

#### struct `FMetasoundFrontendClassInputDefault`  
`struct FMetasoundFrontendClassInputDefault`  
_L1004-1021_
- reflection: `USTRUCT()`
- L1008 _public prototype_ `FMetasoundFrontendClassInputDefault() = default;`
- L1009 _public prototype_ `FMetasoundFrontendClassInputDefault(FMetasoundFrontendLiteral InLiteral);`
- L1010 _public prototype_ `FMetasoundFrontendClassInputDefault(const FGuid& InPageID, FMetasoundFrontendLiteral InLiteral = { });`
- L1011 _public prototype_ `FMetasoundFrontendClassInputDefault(const FAudioParameter& InParameter);`
- L1013 _public prototype_ `static bool IsFunctionalEquivalent(const FMetasoundFrontendClassInputDefault& InLHS, const FMetasoundFrontendClassInputDefault& InRHS);`
- L1017 _public member_ `FMetasoundFrontendLiteral Literal;` — `UPROPERTY()`
- L1020 _public member_ `FGuid PageID = Metasound::Frontend::DefaultPageID;` — `UPROPERTY()`

#### struct `FMetasoundFrontendClassInput`  
`struct FMetasoundFrontendClassInput : public FMetasoundFrontendClassVertex`  
_L1025-1059_
- reflection: `USTRUCT()`
- inherits: `FMetasoundFrontendClassVertex`
- desc: Contains info for input vertex of a Metasound class.
- L1029 _public prototype_ `FMetasoundFrontendClassInput() = default;`
- L1030 _public prototype_ `FMetasoundFrontendClassInput(const FMetasoundFrontendClassVertex& InOther);`
- L1031 _public prototype_ `FMetasoundFrontendClassInput(const Audio::FParameterInterface::FInput& InInput);`
- L1035 _public member_ `FMetasoundFrontendLiteral DefaultLiteral = FMetasoundFrontendLiteral::GetInvalid();` — `UPROPERTY(meta = (DeprecationMessage = "5.5 - Direct access will be revoked and page manipulation limited to public API in future builds. Field has been rolled into DefaultLiterals Array."))`
- L1038 _public prototype_ `static bool IsFunctionalEquivalent(const FMetasoundFrontendClassInput& InLHS, const FMetasoundFrontendClassInput& InRHS);`
- L1042 _private member_ `TArray<FMetasoundFrontendClassInputDefault> Defaults;` — `UPROPERTY(EditAnywhere, Category = Parameters)`
- L1045 _public prototype_ `FMetasoundFrontendLiteral& AddDefault(const FGuid& InPageID);`
- L1046 _public prototype_ `bool ContainsDefault(const FGuid& InPageID) const;`
- L1047 _public prototype_ `const FMetasoundFrontendLiteral* FindConstDefault(const FGuid& InPageID) const;`
- L1048 _public prototype_ `const FMetasoundFrontendLiteral& FindConstDefaultChecked(const FGuid& InPageID) const;`
- L1049 _public prototype_ `FMetasoundFrontendLiteral* FindDefault(const FGuid& InPageID);`
- L1050 _public prototype_ `FMetasoundFrontendLiteral& FindDefaultChecked(const FGuid& InPageID);`
- L1051 _public prototype_ `const TArray<FMetasoundFrontendClassInputDefault>& GetDefaults() const;`
- L1052 _public prototype_ `FMetasoundFrontendLiteral& InitDefault();`
- L1053 _public prototype_ `void InitDefault(FMetasoundFrontendLiteral InitLiteral);`
- L1054 _public prototype_ `void IterateDefaults(TFunctionRef<void(const FGuid&, FMetasoundFrontendLiteral&)> IterFunc);`
- L1055 _public prototype_ `void IterateDefaults(TFunctionRef<void(const FGuid&, const FMetasoundFrontendLiteral&)> IterFunc) const;`
- L1056 _public prototype_ `bool RemoveDefault(const FGuid& InPageID);`
- L1057 _public prototype_ `void ResetDefaults(bool bInitializeDefaultPage = true);`
- L1058 _public prototype_ `void SetDefaults(TArray<FMetasoundFrontendClassInputDefault> InputDefaults);`

#### struct `FMetasoundFrontendClassVariable`  
`struct FMetasoundFrontendClassVariable : public FMetasoundFrontendClassVertex`  
_L1063-1073_
- reflection: `USTRUCT()`
- inherits: `FMetasoundFrontendClassVertex`
- desc: Contains info for variable vertex of a Metasound class.
- L1067 _public prototype_ `FMetasoundFrontendClassVariable() = default;`
- L1068 _public prototype_ `FMetasoundFrontendClassVariable(const FMetasoundFrontendClassVertex& InOther);`
- L1072 _public member_ `FMetasoundFrontendLiteral DefaultLiteral;` — `UPROPERTY(EditAnywhere, Category = Parameters)` — Default value for this variable.

#### struct `FMetasoundFrontendClassOutput`  
`struct FMetasoundFrontendClassOutput : public FMetasoundFrontendClassVertex`  
_L1077-1084_
- reflection: `USTRUCT()`
- inherits: `FMetasoundFrontendClassVertex`
- desc: Contains info for output vertex of a Metasound class.
- L1081 _public prototype_ `FMetasoundFrontendClassOutput() = default;`
- L1082 _public prototype_ `FMetasoundFrontendClassOutput(const FMetasoundFrontendClassVertex& InOther);`
- L1083 _public prototype_ `FMetasoundFrontendClassOutput(const Audio::FParameterInterface::FOutput& Output);`

#### struct `FMetasoundFrontendClassEnvironmentVariable`  
`struct FMetasoundFrontendClassEnvironmentVariable`  
_L1087-1106_
- reflection: `USTRUCT()`
- L1091 _public prototype_ `FMetasoundFrontendClassEnvironmentVariable() = default;`
- L1092 _public prototype_ `FMetasoundFrontendClassEnvironmentVariable(const Audio::FParameterInterface::FEnvironmentVariable& InVariable);`
- L1096 _public member_ `FName Name;` — `UPROPERTY()` — Name of environment variable.
- L1100 _public member_ `FName TypeName;` — `UPROPERTY()` — Type of environment variable.
- L1105 _public member_ `bool bIsRequired = true;` — `UPROPERTY()` — True if the environment variable is needed in order to instantiate a node instance of the class. TODO: Should be deprecated?

#### struct `FMetasoundFrontendInterfaceStyle`  
`struct FMetasoundFrontendInterfaceStyle`  
_L1110-1163_
- reflection: `USTRUCT()`
- desc: Style info of an interface.
- L1117 _public member_ `TArray<int32> DefaultSortOrder;` — `UPROPERTY()` — Default vertex sort order, where array index mirrors array interface index and value is display sort index.
- L1121 _public member_ `TMap<FName, FText> RequiredMembers;` — `UPROPERTY()` — Map of member names with FText to be used as warnings if not hooked up
- L1123 _public prototype_ `void SortVertices(TArray<const FMetasoundFrontendVertex*>& OutVertices, TFunctionRef<FText(const FMetasoundFrontendVertex&)> InGetDisplayNamePredicate) const;`
- L1127 _public function_ `void SortDefaults(TArray<HandleType>& OutHandles, NamePredicateType InGetDisplayNamePredicate) const` — `UE_DEPRECATED(5.7, "Use SortVertices and the builder API instead of this template (which is built primarily for use with the controller API, currently being deprecated)")`

#### struct `FMetasoundFrontendClassInterface`  
`struct FMetasoundFrontendClassInterface`  
_L1166-1306_
- reflection: `USTRUCT()`
- L1175 _private member_ `FMetasoundFrontendInterfaceStyle InputStyle;` — `UPROPERTY()` — Style info for inputs.
- L1179 _private member_ `FMetasoundFrontendInterfaceStyle OutputStyle;` — `UPROPERTY()` — Style info for outputs.
- L1186 _public prototype_ `static FMetasoundFrontendClassInterface GenerateClassInterface(const Metasound::FVertexInterface& InVertexInterface);` — Generates class interface intended to be used as a registry descriptor from FNodeClassMetadata. Does not initialize a change ID as it is not considered to be transactional.
- L1190 _public member_ `TArray<FMetasoundFrontendClassInput> Inputs;` — `UPROPERTY(VisibleAnywhere, Category = CustomView)` — Description of class inputs.
- L1194 _public member_ `TArray<FMetasoundFrontendClassOutput> Outputs;` — `UPROPERTY(VisibleAnywhere, Category = CustomView)` — Description of class outputs.
- L1198 _public member_ `TArray<FMetasoundFrontendClassEnvironmentVariable> Environment;` — `UPROPERTY(VisibleAnywhere, Category = CustomView)` — Description of class environment variables.
- L1202 _private member_ `FGuid ChangeID;` — `UPROPERTY(Transient)`
- L1206 _public function_ `const FMetasoundFrontendInterfaceStyle& GetInputStyle() const`
- L1211 _public function_ `void SetInputStyle(FMetasoundFrontendInterfaceStyle InInputStyle)`
- L1225 _public function_ `const FMetasoundFrontendInterfaceStyle& GetOutputStyle() const`
- L1230 _public function_ `void SetOutputStyle(FMetasoundFrontendInterfaceStyle InOutputStyle)`
- L1244 _public function_ `void AddRequiredInputToStyle(const FName& InInputName, const FText& InRequiredText)`
- L1250 _public function_ `void AddRequiredOutputToStyle(const FName& InOutputName, const FText& InRequiredText)`
- L1256 _public function_ `bool IsMemberInputRequired(const FName& InInputName, FText& OutRequiredText)`
- L1266 _public function_ `bool IsMemberOutputRequired(const FName& InOutputName, FText& OutRequiredText)`
- L1276 _public function_ `void AddSortOrderToInputStyle(const int32 InSortOrder)`
- L1282 _public function_ `void AddSortOrderToOutputStyle(const int32 InSortOrder)`
- L1290 _public function_ `const FGuid& GetChangeID() const`
- L1299 _public function_ `void UpdateChangeID()` — TODO: This is unfortunately required to be manually managed and executed anytime the input/output/environment arrays are mutated due to the design of the controller system obscuring away read/write permissions when querying.  Need to add accessors and refactor so that this isn't as error prone and remove manual execution at the call sites when mutating aforementioned UPROPERTIES.

#### struct `FMetasoundFrontendInterfaceVertexBinding`  
`struct FMetasoundFrontendInterfaceVertexBinding`  
_L1309-1338_
- reflection: `USTRUCT()`
- L1314 _public member_ `FName OutputName;` — `UPROPERTY()`
- L1317 _public member_ `FName InputName;` — `UPROPERTY()`
- L1329 _public function_ `FString ToString() const`

#### struct `FMetasoundFrontendInterfaceBinding`  
`struct FMetasoundFrontendInterfaceBinding`  
_L1342-1363_
- reflection: `USTRUCT()`
- L1348 _public member_ `FMetasoundFrontendVersion OutputInterfaceVersion;` — `UPROPERTY()` — Version of interface to bind from (the corresponding output vertices)
- L1352 _public member_ `FMetasoundFrontendVersion InputInterfaceVersion;` — `UPROPERTY()` — Version of interface to bind to (the corresponding input vertices)
- L1357 _public member_ `int32 BindingPriority = 0;` — `UPROPERTY()` — Value describing if interface binding priority is higher or lower than another interface binding that may be shared between vertices attempting to be connected via binding functionality.
- L1362 _public member_ `TArray<FMetasoundFrontendInterfaceVertexBinding> VertexBindings;` — `UPROPERTY()` — Array of named pairs (output & input names) that describe what edges to create if binding functionality is executed between two nodes.

#### struct `FMetasoundFrontendInterfaceUClassOptions`  
`struct FMetasoundFrontendInterfaceUClassOptions`  
_L1369-1388_
- reflection: `USTRUCT(BlueprintType)`
- desc: Options used to restrict a corresponding UClass that interface may be applied to. If unspecified, interface is assumed to be applicable to any arbitrary UClass.
- L1373 _public prototype_ `FMetasoundFrontendInterfaceUClassOptions() = default;`
- L1374 _public prototype_ `FMetasoundFrontendInterfaceUClassOptions(const Audio::FParameterInterface::FClassOptions& InOptions);`
- L1375 _public prototype_ `FMetasoundFrontendInterfaceUClassOptions(const FTopLevelAssetPath& InClassPath, bool bInIsModifiable = true, bool bInIsDefault = false);`
- L1379 _public member_ `FTopLevelAssetPath ClassPath;` — `UPROPERTY(BlueprintReadOnly, Category = Interface)` — Path to MetaSound class interface can be added to (ex. UMetaSoundSource or UMetaSound)
- L1383 _public member_ `bool bIsModifiable = true;` — `UPROPERTY()` — True if user can add or remove the given class directly to or from the inherited interface UI, false if not.
- L1387 _public member_ `bool bIsDefault = false;` — `UPROPERTY()` — True if interface should be added by default to newly created MetaSound assets, false if not.

#### struct `FMetasoundFrontendInterfaceMetadata`  
`struct FMetasoundFrontendInterfaceMetadata`  
_L1392-1410_
- reflection: `USTRUCT(BlueprintType)`
- L1398 _public member_ `FMetasoundFrontendVersion Version;` — `UPROPERTY(BlueprintReadOnly, Category = Interface)` — Name and version number of the interface
- L1403 _public member_ `TArray<FMetasoundFrontendInterfaceUClassOptions> UClassOptions;` — `UPROPERTY(BlueprintReadOnly, Category = Interface)` — If specified, options used to restrict a corresponding UClass that interface may be applied to.  If unspecified, interface is assumed to be applicable to any arbitrary UClass.
- L1408 _public member_ `FText Description;` — `UPROPERTY(VisibleAnywhere, Category = Interface)` — Developer-supplied description of the interface

#### struct `FMetasoundFrontendInterface`  
`struct FMetasoundFrontendInterface : public FMetasoundFrontendClassInterface`  
_L1415-1435_
- reflection: `USTRUCT()`
- inherits: `FMetasoundFrontendClassInterface`
- desc: Definition of an interface that an FMetasoundFrontendClass adheres to in part or full.
- L1419 _public prototype_ `FMetasoundFrontendInterface() = default;`
- L1420 _public prototype_ `FMetasoundFrontendInterface(Audio::FParameterInterfacePtr InInterface);`
- L1423 _public member_ `FMetasoundFrontendInterfaceMetadata Metadata;` — `UPROPERTY()`
- L1427 _public member_ `FMetasoundFrontendVersion Version;` — `UPROPERTY(Transient, meta = (DeprecatedProperty, DeprecationMessage = "5.6 - Field never serialized but will be in the future, and moved to Metadata. Will be removed in subsequent release."))`
- L1430 _public member_ `TArray<FMetasoundFrontendInterfaceUClassOptions> UClassOptions;` — `UPROPERTY(Transient, meta = (DeprecatedProperty, DeprecationMessage = "5.6 - Field never serialized but will be in the future, and moved to Metadata. Will be removed in subsequent release."))`
- L1433 _public prototype_ `const FMetasoundFrontendInterfaceUClassOptions* FindClassOptions(const FTopLevelAssetPath& InClassPath) const;` — `UE_DEPRECATED(5.6, "Inlined where necessary. Use desired predicate look-up on UClassOptions from now-shared Metadata struct above.")`

#### struct `FMetasoundFrontendClassName`  
`struct FMetasoundFrontendClassName`  
_L1440-1510_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "MetaSound Class Name"))`
- desc: Name of a Metasound class
- L1444 _public prototype_ `FMetasoundFrontendClassName() = default;`
- L1445 _public prototype_ `FMetasoundFrontendClassName(const FName& InNamespace, const FName& InName);`
- L1446 _public prototype_ `FMetasoundFrontendClassName(const FName& InNamespace, const FName& InName, const FName& InVariant);`
- L1447 _public prototype_ `FMetasoundFrontendClassName(const Metasound::FNodeClassName& InName);`
- L1451 _public member_ `FName Namespace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General)` — Namespace of class.
- L1455 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General)` — Name of class.
- L1459 _public member_ `FName Variant;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = General)` — Variant of class. The Variant is used to describe an equivalent class which performs the same operation but on differing types.
- L1462 _public prototype_ `FName GetFullName() const;` — Returns a full name of the class.
- L1465 _public prototype_ `FName GetScopedName() const;` — Returns scoped name representing namespace and name.
- L1468 _public member_ `static const FMetasoundFrontendClassName InvalidClassName;` — Invalid form of class name (i.e. empty namespace, name, and variant)
- L1471 _public prototype_ `bool IsValid() const;` — Whether or not this instance of a class name is a valid name.
- L1474 _public prototype_ `Metasound::FNodeClassName ToNodeClassName() const;` — Returns NodeClassName version of full name
- L1477 _public prototype_ `FString ToString() const;` — Return string version of full name.
- L1480 _public prototype_ `void ToString(FNameBuilder& NameBuilder) const;` — Return a string into an existing FNameBuilder
- L1483 _public prototype_ `static bool Parse(const FString& InClassName, FMetasoundFrontendClassName& OutClassName);` — Parses string into class name.  For deserialization and debug use only.

#### struct `FMetasoundFrontendClassMetadata`  
`struct FMetasoundFrontendClassMetadata`  
_L1514-1746_
- reflection: `USTRUCT()`
- L1518 _public prototype_ `FMetasoundFrontendClassMetadata();`
- L1521 _public prototype_ `static FMetasoundFrontendClassMetadata GenerateClassMetadata(const Metasound::FNodeClassMetadata& InNodeClassMetadata, EMetasoundFrontendClassType InType);` — Generates class metadata intended to be used as a registry descriptor from FNodeClassMetadata. Does not initialize a change ID as it is not considered to be transactional.
- L1525 _private member_ `FMetasoundFrontendClassName ClassName;` — `UPROPERTY(VisibleAnywhere, Category = Metasound)`
- L1528 _private member_ `FMetasoundFrontendVersionNumber Version;` — `UPROPERTY(VisibleAnywhere, Category = Metasound)`
- L1531 _private member_ `EMetasoundFrontendClassType Type = EMetasoundFrontendClassType::Invalid;` — `UPROPERTY(VisibleAnywhere, Category = Metasound)`
- L1535 _private member_ `FText DisplayName;` — `UPROPERTY(EditAnywhere, Category = Metasound)`
- L1538 _private member_ `FText DisplayNameTransient;` — `UPROPERTY(Transient)`
- L1541 _private member_ `FText Description;` — `UPROPERTY(EditAnywhere, Category = Metasound)`
- L1544 _private member_ `FText DescriptionTransient;` — `UPROPERTY(Transient)`
- L1551 _private member_ `FText PromptIfMissingTransient;` — `UPROPERTY(Transient)` — TODO: Move to using a non-localized hint path.  Due to localization, loading & the fact that class registration happens on demand (post serialization), copying an FText to the referencing document can result in localization ids mismatched to different text when attempting to gather text.
- L1554 _private member_ `FString Author;` — `UPROPERTY(EditAnywhere, Category = Metasound)`
- L1557 _private member_ `TArray<FText> Keywords;` — `UPROPERTY(EditAnywhere, Category = Metasound)`
- L1560 _private member_ `TArray<FText> KeywordsTransient;` — `UPROPERTY(Transient)`
- L1563 _private member_ `TArray<FText> CategoryHierarchy;` — `UPROPERTY(EditAnywhere, Category = Metasound)`
- L1566 _private member_ `TArray<FText> CategoryHierarchyTransient;` — `UPROPERTY(Transient)`
- L1570 _private member_ `bool bIsDeprecated = false;` — `UPROPERTY(meta = (Deprecated = 5.7, DeprecationMessage = "Use Access Flags instead"))` — If true, this node is deprecated and should not be used in new MetaSounds.
- L1574 _private member_ `uint16 AccessFlags = static_cast<uint16>(EMetasoundFrontendClassAccessFlags::Referenceable);` — `UPROPERTY(EditAnywhere, Category = Metasound, meta = (Bitmask, BitmaskEnum = "/Script/MetasoundFrontend.EMetasoundFrontendClassAccessFlags"))`
- L1581 _private member_ `bool bAutoUpdateManagesInterface = false;` — `UPROPERTY(meta = (Deprecated = 5.6, DeprecationMessage = "Boolean no longer observed (auto-update rules are managed by project settings now)"))` — If true, auto-update will manage (add and remove) inputs/outputs associated with internally connected nodes when the interface of the given node is auto-updated.
- L1589 _private member_ `bool bSerializeText = true;` — `UPROPERTY()` — Whether or not the given metadata text should be serialized or is procedurally maintained via auto-update & the referenced registry class (to avoid localization text desync).  Should be false for classes serialized as externally-defined dependencies or interfaces.
- L1595 _private member_ `FGuid ChangeID;` — `UPROPERTY(Transient)` — ID used to identify if any of the above have been modified, to determine if the parent class should be auto-updated.
- L1599 _public function_ `static FName GetAccessFlagsPropertyName()`
- L1604 _public function_ `static FName GetAuthorPropertyName()`
- L1609 _public function_ `static FName GetCategoryHierarchyPropertyName()`
- L1614 _public function_ `static FName GetDisplayNamePropertyName()`
- L1619 _public function_ `static FName GetDescriptionPropertyName()`
- L1625 _public function_ `static FName GetIsDeprecatedPropertyName()` — `UE_DEPRECATED(5.7, "Deprecated in favor of access flags")`
- L1632 _public function_ `static FName GetKeywordsPropertyName()`
- L1637 _public function_ `static FName GetClassNamePropertyName()`
- L1642 _public function_ `static FName GetVersionPropertyName()`
- L1648 _public function_ `const FMetasoundFrontendClassName& GetClassName() const`
- L1653 _public prototype_ `void SetClassName(const FMetasoundFrontendClassName& InClassName);`
- L1655 _public prototype_ `EMetasoundFrontendClassType GetType() const;`
- L1656 _public prototype_ `const FMetasoundFrontendVersionNumber& GetVersion() const;`
- L1657 _public prototype_ `void AddAccessFlags(EMetasoundFrontendClassAccessFlags InAccessFlags);`
- L1658 _public prototype_ `void ClearAccessFlags();`
- L1659 _public prototype_ `EMetasoundFrontendClassAccessFlags GetAccessFlags() const;`
- L1660 _public prototype_ `void RemoveAccessFlags(EMetasoundFrontendClassAccessFlags InAccessFlags);`
- L1661 _public prototype_ `void SetAccessFlags(EMetasoundFrontendClassAccessFlags InAccessFlags);`
- L1664 _public function_ `const FText& GetDisplayName() const`
- L1669 _public function_ `const FText& GetDescription() const`
- L1674 _public function_ `const FText& GetPromptIfMissing() const`
- L1679 _public function_ `const FString& GetAuthor() const`
- L1684 _public function_ `const TArray<FText>& GetKeywords() const`
- L1689 _public function_ `const TArray<FText>& GetCategoryHierarchy() const`
- L1694 _public prototype_ `void SetAuthor(const FString& InAuthor);`
- L1695 _public prototype_ `void SetCategoryHierarchy(const TArray<FText>& InCategoryHierarchy);`
- L1696 _public prototype_ `void SetDescription(const FText& InDescription);`
- L1697 _public prototype_ `void SetDisplayName(const FText& InDisplayName);`
- L1700 _public prototype_ `void SetIsDeprecated(bool bInIsDeprecated);` — `UE_DEPRECATED(5.7, "Use Add/Remove/Reset/Set/ClearAccessFlags instead")`
- L1702 _public prototype_ `void SetKeywords(const TArray<FText>& InKeywords);`
- L1703 _public prototype_ `void SetPromptIfMissing(const FText& InPromptIfMissing);`
- L1707 _public prototype_ `void SetSerializeText(bool bInSerializeText);`
- L1710 _public prototype_ `void SetVersion(const FMetasoundFrontendVersionNumber& InVersion);`
- L1712 _public function_ `const FGuid& GetChangeID() const`
- L1719 _public function_ `bool GetIsDeprecated() const` — `UE_DEPRECATED(5.7, "Use GetAccessFlags instead")`
- L1725 _public function_ `void SetType(const EMetasoundFrontendClassType InType)`
- L1736 _public function_ `bool GetAndClearAutoUpdateManagesInterface_Deprecated()` — Deprecated field in favor of GraphClass PresetOptions

#### struct `FMetasoundFrontendClassStyle`  
`struct FMetasoundFrontendClassStyle`  
_L1750-1778_
- reflection: `USTRUCT()`
- L1757 _public member_ `FMetasoundFrontendClassStyleDisplay Display;` — `UPROPERTY()`
- L1760 _public prototype_ `static FMetasoundFrontendClassStyle GenerateClassStyle(const Metasound::FNodeDisplayStyle& InNodeDisplayStyle);` — Generates class style from core node class metadata.
- L1763 _public function_ `void UpdateChangeID() const` — Editor only ID that allows for pumping view to reflect changes to class.
- L1768 _public function_ `FGuid GetChangeID() const`
- L1776 _private member_ `mutable FGuid ChangeID;` — `UPROPERTY(Transient)` — TODO: Deprecate this change behavior in favor of using the builder API transaction counters

#### struct `FMetasoundFrontendClass`  
`struct FMetasoundFrontendClass`  
_L1781-1825_
- reflection: `USTRUCT()`
- L1786 _public prototype_ `FMetasoundFrontendClass() = default;`
- L1787 _public prototype_ `virtual ~FMetasoundFrontendClass() = default;`
- L1788 _public prototype_ `FMetasoundFrontendClass(const FMetasoundFrontendClass&) = default;`
- L1789 _public prototype_ `FMetasoundFrontendClass(FMetasoundFrontendClass&&) = default;`
- L1790 _public prototype_ `FMetasoundFrontendClass& operator=(const FMetasoundFrontendClass&) = default;`
- L1791 _public prototype_ `FMetasoundFrontendClass& operator=(FMetasoundFrontendClass&&) = default;`
- L1795 _public member_ `FGuid ID = Metasound::FrontendInvalidID;` — `UPROPERTY()`
- L1798 _public member_ `FMetasoundFrontendClassMetadata Metadata;` — `UPROPERTY(EditAnywhere, Category = CustomView)`
- L1802 _public member_ `FMetasoundFrontendClassInterface Interface;` — `UE_DEPRECATED(5.6, "Use Get/Set Default Interface instead")` — `UPROPERTY(EditAnywhere, Category = CustomView)`
- L1805 _public prototype_ `void SetDefaultInterface(const FMetasoundFrontendClassInterface& InInterface);`
- L1806 _public prototype_ `FMetasoundFrontendClassInterface& GetDefaultInterface();`
- L1807 _public prototype_ `const FMetasoundFrontendClassInterface& GetDefaultInterface() const;`
- L1808 _public prototype_ `const FMetasoundFrontendClassInterface& GetInterfaceForNode(const FMetasoundFrontendNode& InNode) const;`
- L1812 _public member_ `FMetasoundFrontendClassStyle Style;` — `UPROPERTY()`
- L1823 _public prototype_ `static bool CacheGraphDependencyMetadataFromRegistry(FMetasoundFrontendClass& InOutDependency);` — Caches transient style, class & vertex Metadata found in the registry on a passed (presumed) dependency.  Only modifies properties that are not necessary for serialization or core graph generation. @return - Whether class was found in the registry & data was cached successfully.

#### struct `FMetasoundFrontendNode`  
`struct FMetasoundFrontendNode`  
_L1829-1889_
- reflection: `USTRUCT()`
- desc: An FMetasoundFrontendNode represents a single instance of a FMetasoundFrontendClass
- L1833 _public prototype_ `FMetasoundFrontendNode() = default;`
- L1836 _public prototype_ `FMetasoundFrontendNode(const FMetasoundFrontendClass& InClass);` — `UE_DEPRECATED(5.6, "Please use constructor which accepts a node extension.")`
- L1839 _public prototype_ `FMetasoundFrontendNode(const FMetasoundFrontendClass& InClass, TInstancedStruct<FMetaSoundFrontendNodeConfiguration> InConfiguration);` — Construct a node from a node class and an optional node extension
- L1844 _private member_ `FGuid ID = Metasound::FrontendInvalidID;` — `UPROPERTY()` — Unique ID of this node.
- L1849 _public member_ `FGuid ClassID = Metasound::FrontendInvalidID;` — `UPROPERTY()` — ID of FMetasoundFrontendClass corresponding to this node.
- L1853 _public member_ `FName Name;` — `UPROPERTY()` — Name of node instance.
- L1857 _public member_ `FMetasoundFrontendNodeInterface Interface;` — `UPROPERTY()` — Interface of node instance.
- L1861 _public member_ `TArray<FMetasoundFrontendVertexLiteral> InputLiterals;` — `UPROPERTY()` — Default values for node inputs.
- L1868 _public member_ `TInstancedStruct<FMetaSoundFrontendNodeConfiguration> Configuration;` — `UPROPERTY(EditAnywhere, Category = CustomView, meta = (EditCondition = "false", HideProperty))` — Instance of a configuration for this node. This property is EditAnywhere with a false EditCondition so child properties (ex. node configuration) have exposed property handles for details customization code, but they should not be editable elsewhere in the editor (ex. property matrix)
- L1872 _public member_ `TInstancedStruct<FMetasoundFrontendClassInterface> ClassInterfaceOverride;` — `UPROPERTY()` — An optional override to the default class interface.
- L1877 _public member_ `FMetasoundFrontendNodeStyle Style;` — `UPROPERTY()` — Style info related to a node.
- L1880 _public function_ `const FGuid& GetID() const`
- L1885 _public function_ `void UpdateID(const FGuid& InNewGuid)`

#### struct `FMetasoundFrontendGraphClassPresetOptions`  
`struct FMetasoundFrontendGraphClassPresetOptions`  
_L1896-1907_
- reflection: `USTRUCT()`
- desc: Preset options related to a parent graph class.  A graph class with bIsPreset set to true auto-updates to mirror the interface members (inputs & outputs) of the single, referenced node. It also connects all of these nodes' interface members on update to corresponding inputs & outputs, and inherits input defaults from the referenced node unless otherwise specified.
- L1902 _public member_ `bool bIsPreset = false;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "5.8 - Preset options are now serialized in the Preset MetaSound Template. See 'FMetaSoundFrontendPresetTemplate'"))`
- L1905 _public member_ `TSet<FName> InputsInheritingDefault;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "5.8 - Preset options are now serialized in the Preset MetaSound Template. See 'FMetaSoundFrontendPresetTemplate'"))`

#### struct `FMetasoundFrontendGraph`  
`struct FMetasoundFrontendGraph`  
_L1910-1937_
- reflection: `USTRUCT()`
- L1919 _public member_ `TArray<FMetasoundFrontendNode> Nodes;` — `UPROPERTY(EditAnywhere, Category = CustomView, meta = (EditCondition = "false", HideProperty))` — Node contained in graph This property is EditAnywhere with a false EditCondition so child properties (ex. node configuration) have exposed property handles for details customization code, but they should not be editable elsewhere in the editor (ex. property matrix)
- L1923 _public member_ `TArray<FMetasoundFrontendEdge> Edges;` — `UPROPERTY()` — Connections between points on nodes.
- L1927 _public member_ `TArray<FMetasoundFrontendVariable> Variables;` — `UPROPERTY()` — Graph local variables.
- L1932 _public member_ `FMetasoundFrontendGraphStyle Style;` — `UPROPERTY()` — Style of graph display.
- L1936 _public member_ `FGuid PageID;` — `UPROPERTY()`

#### struct `FMetasoundFrontendGraphClass`  
`struct FMetasoundFrontendGraphClass : public FMetasoundFrontendClass`  
_L1940-2006_
- reflection: `USTRUCT()`
- inherits: `FMetasoundFrontendClass`
- L1945 _public prototype_ `FMetasoundFrontendGraphClass();`
- L1946 _public prototype_ `virtual ~FMetasoundFrontendGraphClass();`
- L1950 _public member_ `FMetasoundFrontendGraph Graph;` — `UPROPERTY(meta = (DeprecationMessage = "5.5 - GraphClasses now support multiple paged graphs. Use the provided page graph accessors"))`
- L1958 _private member_ `TArray<FMetasoundFrontendGraph> PagedGraphs;` — `UPROPERTY(EditAnywhere, Category = CustomView, meta = (EditCondition = "false", HideProperty))` — This property is EditAnywhere with a false EditCondition so child properties (ex. node configuration) have exposed property handles for details customization code, but they should not be editable elsewhere in the editor (ex. property matrix)
- L1963 _public member_ `FMetasoundFrontendGraphClassPresetOptions PresetOptions;` — `UPROPERTY(meta = (DeprecationMessage = "5.8 - PresetOptions is now characterized as configuration vertex metadata on MetaSound Document."))`
- L1965 _public prototype_ `const FMetasoundFrontendGraph& AddGraphPage(const FGuid& InPageID, bool bDuplicateLastGraph = true, bool bSetAsBuildGraph = true);`
- L1971 _public prototype_ `bool RemoveGraphPage(const FGuid& InPageID, FGuid* OutAdjacentPageID = nullptr);` — Removes the page associated with the given PageID.  Returns true if removed, false if not. If provided an "AdjacentPageID," sets the value at the given pointer to a page ID adjacent to the removed page. If last page was removed, returns the default graph ID (which may or may not exist).
- L1974 _public prototype_ `void ResetGraphPages(bool bClearDefaultGraph);` — Removes all graph pages except the default.  If bClearDefaultPage is true, clears the default graph page implementation.
- L1977 _public prototype_ `bool ContainsGraphPage(const FGuid& InPageID) const;`
- L1979 _public prototype_ `FMetasoundFrontendGraph& InitDefaultGraphPage();`
- L1981 _public prototype_ `void IterateGraphPages(TFunctionRef<void(FMetasoundFrontendGraph&)> IterFunc);`
- L1982 _public prototype_ `void IterateGraphPages(TFunctionRef<void(const FMetasoundFrontendGraph&)> IterFunc) const;`
- L1984 _public prototype_ `FMetasoundFrontendGraph* FindGraph(const FGuid& InPageID);`
- L1985 _public prototype_ `FMetasoundFrontendGraph& FindGraphChecked(const FGuid& InPageID);`
- L1986 _public prototype_ `const FMetasoundFrontendGraph* FindConstGraph(const FGuid& InPageID) const;`
- L1987 _public prototype_ `const FMetasoundFrontendGraph& FindConstGraphChecked(const FGuid& InPageID) const;`
- L1988 _public function_ `const TArray<FMetasoundFrontendGraph>& GetConstGraphPages() const`
- L1989 _public prototype_ `FMetasoundFrontendGraph& GetDefaultGraph();`
- L1990 _public prototype_ `const FMetasoundFrontendGraph& GetConstDefaultGraph() const;`
- L1991 _public prototype_ `void ResetGraphs();`

#### struct `FMetasoundFrontendGraphClass::IPropertyVersionTransform`  
`struct IPropertyVersionTransform`  
_L1994-2004_
- L1997 _public prototype_ `virtual ~IPropertyVersionTransform() = default;`
- L2000 _protected prototype_ `virtual bool Transform(FMetasoundFrontendGraphClass& OutClass) const = 0;`
- L2003 _protected prototype_ `static TArray<FMetasoundFrontendGraph>& GetPagesUnsafe(FMetasoundFrontendGraphClass& GraphClass);` — Allows for unsafe access to a document for property migration.

#### class `UMetaSoundFrontendMemberMetadata`  
`class UMetaSoundFrontendMemberMetadata : public UObject`  
_L2009-2022_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L2016 _public member_ `FGuid MemberID;` — `UPROPERTY()`
- L2020 _public function_ `virtual bool MigrateProperties()` — Enables migrating properties during asynchronous versioning safely. Favor using this over versioning properties on 'PostLoad' to avoid race conditions.

#### struct `FMetasoundFrontendDocumentMetadata`  
`struct FMetasoundFrontendDocumentMetadata`  
_L2025-2042_
- reflection: `USTRUCT()`
- L2030 _public member_ `FMetasoundFrontendVersion Version;` — `UPROPERTY()`
- L2034 _public member_ `mutable FMetasoundFrontendDocumentModifyContext ModifyContext;` — Actively being deprecated in favor of Document Builder Transaction Listener API.
- L2040 _public member_ `TMap<FGuid, TObjectPtr<UMetaSoundFrontendMemberMetadata>> MemberMetadata;` — `UPROPERTY()` — Map of MemberID to metadata used to constrain how literals can be manipulated with the editor context. This can be used to implement things like numeric ranges, hardware control parameters, etc.

#### struct `FMetasoundFrontendDocument`  
`struct FMetasoundFrontendDocument`  
_L2045-2113_
- reflection: `USTRUCT()`
- L2052 _public prototype_ `static FMetasoundFrontendVersionNumber GetMaxVersion();` — `UE_DEPRECATED(5.8, "MaxVersion is now externally accessible via FVersioningManager::GetMaxDocumentVersion()")`
- L2055 _public member_ `Metasound::Frontend::FAccessPoint AccessPoint;`
- L2057 _public prototype_ `FMetasoundFrontendDocument();`
- L2060 _public member_ `FMetasoundFrontendDocumentMetadata Metadata;` — `UPROPERTY(EditAnywhere, Category = Metadata)`
- L2063 _public member_ `TSet<FMetasoundFrontendVersion> Interfaces;` — `UPROPERTY(VisibleAnywhere, Category = CustomView)`
- L2066 _public member_ `FMetasoundFrontendGraphClass RootGraph;` — `UPROPERTY(EditAnywhere, Category = CustomView)`
- L2069 _public member_ `TArray<FMetasoundFrontendGraphClass> Subgraphs;` — `UPROPERTY()`
- L2072 _public member_ `TArray<FMetasoundFrontendClass> Dependencies;` — `UPROPERTY()`
- L2075 _public member_ `TInstancedStruct<FMetaSoundFrontendDocumentTemplate> Template;` — `UPROPERTY(EditAnywhere, Category = CustomView)`
- L2077 _public function_ `uint32 GetNextIdCounter() const`
- L2085 _private member_ `FMetasoundFrontendVersion ArchetypeVersion;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "5.0 - ArchetypeVersion has been migrated to InterfaceVersions array."))`
- L2088 _private member_ `TArray<FMetasoundFrontendVersion> InterfaceVersions;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "5.0 - InterfaceVersions has been migrated to Interfaces set."))`
- L2095 _private member_ `mutable uint32 IdCounter = 1;` — `UPROPERTY()` — Used for generating deterministic IDs per document. Serialized to avoid id collisions if deterministic IDs are ever serialized (not ideal, but can occur in less common commandlet use cases such as resaving serialized assets procedurally).
- L2100 _public function_ `bool RequiresInterfaceVersioning() const` — `UE_DEPRECATED(5.8, "Moved to internal implementation. See 'MigrateProperties'")`
- L2106 _public function_ `void VersionInterfaces()` — `UE_DEPRECATED(5.8, "Moved to internal implementation. See 'MigrateProperties'")`
- L2111 _public prototype_ `UE_INTERNAL bool MigrateProperties();` — Migrates data from deprecated properties to new properties

#### struct `Metasound::Frontend::FClassInterfaceUpdates`  
`struct FClassInterfaceUpdates`  
_L2169-2208_
- desc: Provides list of interface members that have been added or removed when querying if a node's class has been updated. Editor only as interface can only be updated from editor builds.
- L2171 _public prototype_ `FClassInterfaceUpdates() = default;`
- L2172 _public member_ `TArray<const FMetasoundFrontendClassInput*> AddedInputs;`
- L2173 _public member_ `TArray<const FMetasoundFrontendClassOutput*> AddedOutputs;`
- L2174 _public member_ `TArray<const FMetasoundFrontendClassInput*> RemovedInputs;`
- L2175 _public member_ `TArray<const FMetasoundFrontendClassOutput*> RemovedOutputs;`
- L2176 _public member_ `TInstancedStruct<FMetaSoundFrontendNodeConfiguration> AddedConfiguration;`
- L2177 _public member_ `TConstStructView<FMetaSoundFrontendNodeConfiguration> RemovedConfiguration;`
- L2178 _public member_ `TInstancedStruct<FMetasoundFrontendClassInterface> AddedClassInterfaceOverride;`
- L2179 _public member_ `TConstStructView<FMetasoundFrontendClassInterface> RemovedClassInterfaceOverride;`
- L2181 _public function_ `bool ContainsRemovedMembers() const`
- L2186 _public function_ `bool ContainsAddedMembers() const`
- L2191 _public function_ `bool ContainsUpdatedNodeConfig() const`
- L2196 _public function_ `bool ContainsUpdatedNodeClassInterfaceOverride() const`
- L2201 _public function_ `bool ContainsChanges() const`
- L2207 _public member_ `FMetasoundFrontendClass RegistryClass;` — Cached copy of registry class potentially referenced by added members

#### Free symbols / members of external scopes

- L28 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L39 _namespace_ `namespace Metasound`
- L44 _externvar_ `extern const FGuid FrontendInvalidID;` (scope `Metasound`)
- L46 _namespace_ `namespace Frontend` (scope `Metasound`)
- L48 _externvar_ `extern int32 MetaSoundAutoUpdateNativeClassesOfEqualVersionCVar;` (scope `Metasound::Frontend`)
- L50 _variable_ `constexpr FGuid DefaultPageID(0, 0, 0, 0);` (scope `Metasound::Frontend`)
- L51 _variable_ `constexpr TCHAR DefaultPageName[] = TEXT("Def` (scope `Metasound::Frontend`)
- L54 _externvar_ `extern const FText DefaultPageDisplayName;` (scope `Metasound::Frontend`)
- L57 _namespace_ `namespace DisplayStyle` (scope `Metasound::Frontend`)
- L59 _namespace_ `namespace EdgeAnimation` (scope `Metasound::Frontend::DisplayStyle`)
- L61 _externvar_ `extern const FLinearColor DefaultColor;` (scope `Metasound::Frontend::DisplayStyle::EdgeAnimation`)
- L64 _namespace_ `namespace NodeLayout` (scope `Metasound::Frontend::DisplayStyle`)
- L66 _externvar_ `extern const FVector2D DefaultOffsetX;` (scope `Metasound::Frontend::DisplayStyle::NodeLayout`)
- L67 _externvar_ `extern const FVector2D DefaultOffsetY;` (scope `Metasound::Frontend::DisplayStyle::NodeLayout`)
- L162 _prototype_ `FString LexToString(const EMetasoundFrontendClassAccessFlags& InFlag);`
- L255 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon846680ab0103`)
- L313 _function_ `friend bool operator==(const FMetasoundFrontendVersionNumber& InLHS, const FMetasoundFrontendVersionNumber& InRHS)`
- L318 _function_ `friend bool operator!=(const FMetasoundFrontendVersionNumber& InLHS, const FMetasoundFrontendVersionNumber& InRHS)`
- L323 _function_ `friend bool operator>(const FMetasoundFrontendVersionNumber& InLHS, const FMetasoundFrontendVersionNumber& InRHS)`
- L338 _function_ `friend bool operator>=(const FMetasoundFrontendVersionNumber& InLHS, const FMetasoundFrontendVersionNumber& InRHS)`
- L343 _function_ `friend bool operator<(const FMetasoundFrontendVersionNumber& InLHS, const FMetasoundFrontendVersionNumber& InRHS)`
- L358 _function_ `friend bool operator<=(const FMetasoundFrontendVersionNumber& InLHS, const FMetasoundFrontendVersionNumber& InRHS)`
- L365 _function_ `friend inline uint32 GetTypeHash(const FMetasoundFrontendVersionNumber& InNumber)`
- L391 _function_ `friend bool operator==(const FMetasoundFrontendVersion& InLHS, const FMetasoundFrontendVersion& InRHS)`
- L396 _function_ `friend bool operator!=(const FMetasoundFrontendVersion& InLHS, const FMetasoundFrontendVersion& InRHS)`
- L401 _function_ `friend bool operator>(const FMetasoundFrontendVersion& InLHS, const FMetasoundFrontendVersion& InRHS)`
- L416 _function_ `friend bool operator>=(const FMetasoundFrontendVersion& InLHS, const FMetasoundFrontendVersion& InRHS)`
- L421 _function_ `friend bool operator<(const FMetasoundFrontendVersion& InLHS, const FMetasoundFrontendVersion& InRHS)`
- L436 _function_ `friend bool operator<=(const FMetasoundFrontendVersion& InLHS, const FMetasoundFrontendVersion& InRHS)`
- L441 _function_ `friend inline uint32 GetTypeHash(const FMetasoundFrontendVersion& InVersion)`
- L491 _function_ `friend bool operator==(const FMetasoundFrontendVertexHandle& InLHS, const FMetasoundFrontendVertexHandle& InRHS)`
- L496 _function_ `friend bool operator!=(const FMetasoundFrontendVertexHandle& InLHS, const FMetasoundFrontendVertexHandle& InRHS)`
- L501 _function_ `friend inline uint32 GetTypeHash(const FMetasoundFrontendVertexHandle& InHandle)`
- L736 _function_ `friend bool operator==(const FMetasoundFrontendEdge& InLHS, const FMetasoundFrontendEdge& InRHS)`
- L744 _function_ `friend bool operator!=(const FMetasoundFrontendEdge& InLHS, const FMetasoundFrontendEdge& InRHS)`
- L749 _function_ `friend inline uint32 GetTypeHash(const FMetasoundFrontendEdge& InEdge)`
- L1148 _function_ `` (scope `FMetasoundFrontendInterfaceStyle::SortDefaults`)
- L1319 _function_ `friend bool operator==(const FMetasoundFrontendInterfaceVertexBinding& InLHS, const FMetasoundFrontendInterfaceVertexBinding& InRHS)`
- L1324 _function_ `friend bool operator!=(const FMetasoundFrontendInterfaceVertexBinding& InLHS, const FMetasoundFrontendInterfaceVertexBinding& InRHS)`
- L1334 _function_ `friend inline uint32 GetTypeHash(const FMetasoundFrontendInterfaceVertexBinding& InBinding)`
- L1485 _function_ `friend inline uint32 GetTypeHash(const FMetasoundFrontendClassName& ClassName)`
- L1491 _function_ `friend inline bool operator==(const FMetasoundFrontendClassName& InLHS, const FMetasoundFrontendClassName& InRHS)`
- L1496 _function_ `friend inline bool operator<(const FMetasoundFrontendClassName& InLHS, const FMetasoundFrontendClassName& InRHS)`
- L2115 _prototype_ `const TCHAR* LexToString(EMetasoundFrontendClassType InClassType);`
- L2116 _prototype_ `const TCHAR* LexToString(EMetasoundFrontendVertexAccessType InVertexAccess);`
- L2118 _namespace_ `namespace Metasound`
- L2118 _namespace_ `namespace Frontend` (scope `Metasound`)
- L2121 _prototype_ `EMetasoundFrontendVertexAccessType CoreVertexAccessTypeToFrontendVertexAccessType(Metasound::EVertexAccessType InAccessType);` (scope `Metasound::Frontend`) — Convert access type between enums
- L2124 _prototype_ `EVertexAccessType FrontendVertexAccessTypeToCoreVertexAccessType(EMetasoundFrontendVertexAccessType InAccessType);` (scope `Metasound::Frontend`) — Convert access type between enums
- L2126 _prototype_ `bool StringToClassType(const FString& InString, EMetasoundFrontendClassType& OutClassType);` (scope `Metasound::Frontend`)
- L2129 _typedef_ `using FForEachLiteralFunctionRef = TFunctionRef<void(const FName& InDataTypeName, const FMetasoundFrontendLiteral&)>;` (scope `Metasound::Frontend`) — Signature of function called for each found literal.
- L2133 _prototype_ `void ForEachLiteral(const FMetasoundFrontendDocument& InDoc, FForEachLiteralFunctionRef OnLiteral);` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.7, "Use version which requires a PageOrder")` — Execute the provided function for each literal on a FMetasoundFrontendDocument.
- L2137 _prototype_ `void ForEachLiteral(const FMetasoundFrontendGraphClass& InGraphClass, FForEachLiteralFunctionRef OnLiteral);` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.7, "Use version which requires a PageOrder")` — Execute the provided function for each literal on a FMetasoundFrontendGraphClass.
- L2141 _prototype_ `void ForEachLiteral(const FMetasoundFrontendClass& InClass, FForEachLiteralFunctionRef OnLiteral);` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.7, "Use version which requires a PageOrder")` — Execute the provided function for each literal on a FMetasoundFrontendClass.
- L2145 _prototype_ `void ForEachLiteral(const FMetasoundFrontendNode& InNode, FForEachLiteralFunctionRef OnLiteral);` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.7, "Use version which requires a PageOrder")` — Execute the provided function for each literal on a FMetasoundFrontendNode.
- L2148 _prototype_ `void ForEachLiteral(const FMetasoundFrontendClassInterface& InClassInterface, FForEachLiteralFunctionRef OnLiteral);` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.7, "Use version which requires a PageOrder")`
- L2151 _prototype_ `void ForEachLiteral(const FMetasoundFrontendDocument& InDoc, FForEachLiteralFunctionRef OnLiteral, TArrayView<const FGuid> InPageOrder);` (scope `Metasound::Frontend`) — Execute the provided function for each literal on a FMetasoundFrontendDocument.
- L2154 _prototype_ `void ForEachLiteral(const FMetasoundFrontendGraphClass& InGraphClass, FForEachLiteralFunctionRef OnLiteral, TArrayView<const FGuid> InPageOrder);` (scope `Metasound::Frontend`) — Execute the provided function for each literal on a FMetasoundFrontendGraphClass.
- L2157 _prototype_ `void ForEachLiteral(const FMetasoundFrontendClass& InClass, FForEachLiteralFunctionRef OnLiteral, TArrayView<const FGuid> InPageOrder);` (scope `Metasound::Frontend`) — Execute the provided function for each literal on a FMetasoundFrontendClass.
- L2160 _prototype_ `void ForEachLiteral(const FMetasoundFrontendClassInterface& InClassInterface, FForEachLiteralFunctionRef OnLiteral, TArrayView<const FGuid> InPageOrder);` (scope `Metasound::Frontend`) — Execute the provided function for each literal on a FMetasoundFrontendClassInterface.
- L2163 _prototype_ `void ForEachLiteral(const FMetasoundFrontendNode& InNode, FForEachLiteralFunctionRef OnLiteral, TArrayView<const FGuid> InPageOrder);` (scope `Metasound::Frontend`) — Execute the provided function for each literal on a FMetasoundFrontendNode.

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendDocumentAccessPtr.h` (Public)


#### class `Metasound::Frontend::FNodeAccessPtr`  
`class FNodeAccessPtr : public TAccessPtr<FMetasoundFrontendNode>`  
_L34-51_
- inherits: `TAccessPtr<FMetasoundFrontendNode>`
- L37 _public typedef_ `using Super = TAccessPtr<FMetasoundFrontendNode>;`
- L42 _public prototype_ `FVertexAccessPtr GetInputWithName(const FVertexName& InName);`
- L43 _public prototype_ `FVertexAccessPtr GetInputWithVertexID(const FGuid& InID);`
- L44 _public prototype_ `FVertexAccessPtr GetOutputWithName(const FVertexName& InName);`
- L45 _public prototype_ `FVertexAccessPtr GetOutputWithVertexID(const FGuid& InID);`
- L47 _public prototype_ `FConstVertexAccessPtr GetInputWithName(const FVertexName& InName) const;`
- L48 _public prototype_ `FConstVertexAccessPtr GetInputWithVertexID(const FGuid& InID) const;`
- L49 _public prototype_ `FConstVertexAccessPtr GetOutputWithName(const FVertexName& InName) const;`
- L50 _public prototype_ `FConstVertexAccessPtr GetOutputWithVertexID(const FGuid& InID) const;`

#### class `Metasound::Frontend::FConstNodeAccessPtr`  
`class FConstNodeAccessPtr : public TAccessPtr<const FMetasoundFrontendNode>`  
_L53-65_
- inherits: `TAccessPtr<constFMetasoundFrontendNode>`
- L56 _public typedef_ `using Super = TAccessPtr<const FMetasoundFrontendNode>;`
- L61 _public prototype_ `FConstVertexAccessPtr GetInputWithName(const FVertexName& InName) const;`
- L62 _public prototype_ `FConstVertexAccessPtr GetInputWithVertexID(const FGuid& InID) const;`
- L63 _public prototype_ `FConstVertexAccessPtr GetOutputWithName(const FVertexName& InName) const;`
- L64 _public prototype_ `FConstVertexAccessPtr GetOutputWithVertexID(const FGuid& InID) const;`

#### class `Metasound::Frontend::FClassAccessPtr`  
`class FClassAccessPtr : public TAccessPtr<FMetasoundFrontendClass>`  
_L70-82_
- inherits: `TAccessPtr<FMetasoundFrontendClass>`
- L73 _public typedef_ `using Super = TAccessPtr<FMetasoundFrontendClass>;`
- L78 _public prototype_ `FClassInputAccessPtr GetInputWithName(const FVertexName& InName);`
- L79 _public prototype_ `FClassOutputAccessPtr GetOutputWithName(const FVertexName& InName);`
- L80 _public prototype_ `FConstClassInputAccessPtr GetInputWithName(const FVertexName& InName) const;`
- L81 _public prototype_ `FConstClassOutputAccessPtr GetOutputWithName(const FVertexName& InName) const;`

#### class `Metasound::Frontend::FConstClassAccessPtr`  
`class FConstClassAccessPtr : public TAccessPtr<const FMetasoundFrontendClass>`  
_L84-94_
- inherits: `TAccessPtr<constFMetasoundFrontendClass>`
- L87 _public typedef_ `using Super = TAccessPtr<const FMetasoundFrontendClass>;`
- L92 _public prototype_ `FConstClassInputAccessPtr GetInputWithName(const FVertexName& InName) const;`
- L93 _public prototype_ `FConstClassOutputAccessPtr GetOutputWithName(const FVertexName& InName) const;`

#### class `Metasound::Frontend::FGraphClassAccessPtr`  
`class FGraphClassAccessPtr : public TAccessPtr<FMetasoundFrontendGraphClass>`  
_L96-121_
- inherits: `TAccessPtr<FMetasoundFrontendGraphClass>`
- L99 _public typedef_ `using Super = TAccessPtr<FMetasoundFrontendGraphClass>;`
- L104 _public prototype_ `FClassInputAccessPtr GetInputWithName(const FVertexName& InName);`
- L105 _public prototype_ `FClassInputAccessPtr GetInputWithNodeID(const FGuid& InNodeID);`
- L106 _public prototype_ `FClassOutputAccessPtr GetOutputWithName(const FVertexName& InName);`
- L107 _public prototype_ `FClassOutputAccessPtr GetOutputWithNodeID(const FGuid& InNodeID);`
- L109 _public prototype_ `FVariableAccessPtr GetVariableWithID(const FGuid& InID);`
- L110 _public prototype_ `FNodeAccessPtr GetNodeWithNodeID(const FGuid& InNodeID);`
- L111 _public prototype_ `FGraphAccessPtr GetGraph();`
- L113 _public prototype_ `FConstClassInputAccessPtr GetInputWithName(const FVertexName& InName) const;`
- L114 _public prototype_ `FConstClassInputAccessPtr GetInputWithNodeID(const FGuid& InNodeID) const;`
- L115 _public prototype_ `FConstClassOutputAccessPtr GetOutputWithName(const FVertexName& InName) const;`
- L116 _public prototype_ `FConstClassOutputAccessPtr GetOutputWithNodeID(const FGuid& InNodeID) const;`
- L118 _public prototype_ `FConstVariableAccessPtr GetVariableWithID(const FGuid& InID) const;`
- L119 _public prototype_ `FConstNodeAccessPtr GetNodeWithNodeID(const FGuid& InNodeID) const;`
- L120 _public prototype_ `FConstGraphAccessPtr GetGraph() const;`

#### class `Metasound::Frontend::FConstGraphClassAccessPtr`  
`class FConstGraphClassAccessPtr : public TAccessPtr<const FMetasoundFrontendGraphClass>`  
_L123-137_
- inherits: `TAccessPtr<constFMetasoundFrontendGraphClass>`
- L125 _private typedef_ `using Super = TAccessPtr<const FMetasoundFrontendGraphClass>;`
- L130 _private prototype_ `FConstClassInputAccessPtr GetInputWithName(const FVertexName& InName) const;`
- L131 _private prototype_ `FConstClassInputAccessPtr GetInputWithNodeID(const FGuid& InNodeID) const;`
- L132 _private prototype_ `FConstClassOutputAccessPtr GetOutputWithName(const FVertexName& InName) const;`
- L133 _private prototype_ `FConstClassOutputAccessPtr GetOutputWithNodeID(const FGuid& InNodeID) const;`
- L134 _private prototype_ `FConstVariableAccessPtr GetVariableWithID(const FGuid& InID) const;`
- L135 _private prototype_ `FConstNodeAccessPtr GetNodeWithNodeID(const FGuid& InNodeID) const;`
- L136 _private prototype_ `FConstGraphAccessPtr GetGraph() const;`

#### class `Metasound::Frontend::FDocumentAccessPtr`  
`class FDocumentAccessPtr : public TAccessPtr<FMetasoundFrontendDocument>`  
_L139-168_
- inherits: `TAccessPtr<FMetasoundFrontendDocument>`
- L142 _public typedef_ `using Super = TAccessPtr<FMetasoundFrontendDocument>;`
- L147 _public prototype_ `FGraphClassAccessPtr GetRootGraph();`
- L148 _public prototype_ `FGraphClassAccessPtr GetSubgraphWithID(const FGuid& InID);`
- L149 _public prototype_ `FClassAccessPtr GetDependencyWithID(const FGuid& InID);`
- L150 _public prototype_ `FClassAccessPtr GetClassWithID(const FGuid& InID);`
- L151 _public prototype_ `FClassAccessPtr GetClassWithMetadata(const FMetasoundFrontendClassMetadata& InMetadata);`
- L154 _public prototype_ `FClassAccessPtr GetClassWithInfo(const FNodeClassInfo& InInfo);` — `UE_DEPRECATED(5.8, "FNodeClassInfo is actively being deprecated, use overload with FNodeClassRegistryKey instead")`
- L156 _public prototype_ `FClassAccessPtr GetClassWithRegistryKey(const FNodeRegistryKey& InKey);`
- L158 _public prototype_ `FConstGraphClassAccessPtr GetRootGraph() const;`
- L159 _public prototype_ `FConstGraphClassAccessPtr GetSubgraphWithID(const FGuid& InID) const;`
- L160 _public prototype_ `FConstClassAccessPtr GetDependencyWithID(const FGuid& InID) const;`
- L161 _public prototype_ `FConstClassAccessPtr GetClassWithID(const FGuid& InID) const;`
- L162 _public prototype_ `FConstClassAccessPtr GetClassWithMetadata(const FMetasoundFrontendClassMetadata& InMetadata) const;`
- L165 _public prototype_ `FConstClassAccessPtr GetClassWithInfo(const FNodeClassInfo& InInfo) const;` — `UE_DEPRECATED(5.8, "FNodeClassInfo is actively being deprecated, use overload with FNodeClassRegistryKey instead")`
- L167 _public prototype_ `FConstClassAccessPtr GetClassWithRegistryKey(const FNodeRegistryKey& InKey) const;`

#### class `Metasound::Frontend::FConstDocumentAccessPtr`  
`class FConstDocumentAccessPtr : public TAccessPtr<const FMetasoundFrontendDocument>`  
_L170-188_
- inherits: `TAccessPtr<constFMetasoundFrontendDocument>`
- L173 _public typedef_ `using Super = TAccessPtr<const FMetasoundFrontendDocument>;`
- L178 _public prototype_ `FConstGraphClassAccessPtr GetRootGraph() const;`
- L179 _public prototype_ `FConstGraphClassAccessPtr GetSubgraphWithID(const FGuid& InID) const;`
- L180 _public prototype_ `FConstClassAccessPtr GetDependencyWithID(const FGuid& InID) const;`
- L181 _public prototype_ `FConstClassAccessPtr GetClassWithID(const FGuid& InID) const;`
- L182 _public prototype_ `FConstClassAccessPtr GetClassWithMetadata(const FMetasoundFrontendClassMetadata& InMetadata) const;`
- L185 _public prototype_ `FConstClassAccessPtr GetClassWithInfo(const FNodeClassInfo& InInfo) const;` — `UE_DEPRECATED(5.8, "FNodeClassInfo is actively being deprecated, use overload with FNodeClassRegistryKey instead")`
- L187 _public prototype_ `FConstClassAccessPtr GetClassWithRegistryKey(const FNodeRegistryKey& InKey) const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L21 _namespace_ `namespace Metasound`
- L23 _namespace_ `namespace Frontend` (scope `Metasound`)
- L25 _typedef_ `using FVertexAccessPtr = TAccessPtr<FMetasoundFrontendVertex>;` (scope `Metasound::Frontend`)
- L26 _typedef_ `using FConstVertexAccessPtr = TAccessPtr<const FMetasoundFrontendVertex>;` (scope `Metasound::Frontend`)
- L27 _typedef_ `using FClassInputAccessPtr = TAccessPtr<FMetasoundFrontendClassInput>;` (scope `Metasound::Frontend`)
- L28 _typedef_ `using FConstClassInputAccessPtr = TAccessPtr<const FMetasoundFrontendClassInput>;` (scope `Metasound::Frontend`)
- L29 _typedef_ `using FClassOutputAccessPtr = TAccessPtr<FMetasoundFrontendClassOutput>;` (scope `Metasound::Frontend`)
- L30 _typedef_ `using FConstClassOutputAccessPtr = TAccessPtr<const FMetasoundFrontendClassOutput>;` (scope `Metasound::Frontend`)
- L31 _typedef_ `using FVariableAccessPtr = TAccessPtr<FMetasoundFrontendVariable>;` (scope `Metasound::Frontend`)
- L32 _typedef_ `using FConstVariableAccessPtr = TAccessPtr<const FMetasoundFrontendVariable>;` (scope `Metasound::Frontend`)
- L67 _typedef_ `using FGraphAccessPtr = TAccessPtr<FMetasoundFrontendGraph>;` (scope `Metasound::Frontend`)
- L68 _typedef_ `using FConstGraphAccessPtr = TAccessPtr<const FMetasoundFrontendGraph>;` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendDocumentBuilder.h` (Public)


#### enum `Metasound::Frontend::EInvalidEdgeReason`  
`enum class EInvalidEdgeReason : uint8`  
_L50-58_
- L52 _public enumerator_ `None = 0`
- L53 _public enumerator_ `MismatchedAccessType`
- L54 _public enumerator_ `MismatchedDataType`
- L55 _public enumerator_ `MissingInput`
- L56 _public enumerator_ `MissingOutput`
- L57 _public enumerator_ `COUNT`

#### struct `Metasound::Frontend::FNamedEdge`  
`struct FNamedEdge`  
_L62-88_
- L64 _public member_ `const FGuid OutputNodeID;`
- L65 _public member_ `const FName OutputName;`
- L66 _public member_ `const FGuid InputNodeID;`
- L67 _public member_ `const FName InputName;`

#### struct `Metasound::Frontend::FModifyInterfaceOptions`  
`struct FModifyInterfaceOptions`  
_L90-111_
- L92 _public prototype_ `FModifyInterfaceOptions(const TArray<FMetasoundFrontendInterface>& InInterfacesToRemove, const TArray<FMetasoundFrontendInterface>& InInterfacesToAdd, const FMetaSoundFrontendDocumentBuilder* InReferencedBuilder =nullptr);`
- L93 _public prototype_ `FModifyInterfaceOptions(TArray<FMetasoundFrontendInterface>&& InInterfacesToRemove, TArray<FMetasoundFrontendInterface>&& InInterfacesToAdd, const FMetaSoundFrontendDocumentBuilder* InReferencedBuilder = nullptr);`
- L94 _public prototype_ `FModifyInterfaceOptions(const TArray<FMetasoundFrontendVersion>& InInterfaceVersionsToRemove, const TArray<FMetasoundFrontendVersion>& InInterfaceVersionsToAdd, const FMetaSoundFrontendDocumentBuilder* InReferencedBuilder = nullptr);`
- L96 _public member_ `TArray<FMetasoundFrontendInterface> InterfacesToRemove;`
- L97 _public member_ `TArray<FMetasoundFrontendInterface> InterfacesToAdd;`
- L103 _public member_ `TFunction<bool(FName, FName)> NamePairingFunction;` — Function used to determine if an old of a removed interface and new member of an added interface are considered equal and to be swapped, retaining preexisting connections (and locations if in editor and 'SetDefaultNodeLocations' option is set)
- L106 _public member_ `bool bSetDefaultNodeLocations = true;`
- L110 _public member_ `const FMetaSoundFrontendDocumentBuilder* ReferencedBuilder = nullptr;` — Optional builder to copy node ids from instead of regenerating

#### class `UMetaSoundBuilderDocument`  
`class UMetaSoundBuilderDocument : public UObject, public IMetaSoundDocumentInterface`  
_L118-177_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IMetaSoundDocumentInterface`
- desc: Builder Document UObject, which is only used for registration purposes when attempting async registration whereby the original document is serialized and must not be mutated.
- L123 _public prototype_ `UMetaSoundBuilderDocument(const FObjectInitializer& ObjectInitializer);`
- L126 _public prototype_ `static UMetaSoundBuilderDocument& Create(const IMetaSoundDocumentInterface& InDocToCopy);` — Create and return a valid builder document which copies the provided interface's document & class
- L128 _public prototype_ `virtual bool ConformObjectToDocument() override;`
- L131 _public prototype_ `virtual const FMetasoundFrontendDocument& GetConstDocument() const override;` — Returns the document
- L134 _public prototype_ `virtual EMetasoundFrontendClassAccessFlags GetDefaultAccessFlags() const final override;` — Returns the default access flags utilized when document is initialized.
- L137 _public prototype_ `virtual FTopLevelAssetPath GetAssetPathChecked() const override;` — Returns temp path of builder document
- L140 _public prototype_ `virtual const UClass& GetBaseMetaSoundUClass() const final override;` — Returns the base class registered with the MetaSound UObject registry.
- L143 _public prototype_ `virtual const UClass& GetBuilderUClass() const final override;` — Returns the builder class used to modify the given document.
- L146 _public prototype_ `virtual bool IsActivelyBuilding() const final override;` — Returns if the document is being actively built (always true as builder documents are always being actively built)
- L149 _private prototype_ `virtual FMetasoundFrontendDocument& GetDocument() override;`
- L156 _private function_ `template<typename TTemplateType> TTemplateType* GetTemplateAs()` — Convenience template function for attempting to get the underlying pointer of the set configuration. If the provided configuration type is not that which the current document is set to or no configuration is set, returns null.
- L163 _private function_ `TTemplateType* GetDocumentConfigurationAs()` — `UE_DEPRECATED(5.8, "Use GetTemplateAs() instead")`
- L166 _private prototype_ `virtual void OnBeginActiveBuilder() override;`
- L167 _private prototype_ `virtual void OnFinishActiveBuilder() override;`
- L170 _private member_ `FMetasoundFrontendDocument Document;` — `UPROPERTY(Transient)`
- L173 _private member_ `TObjectPtr<const UClass> MetaSoundUClass = nullptr;` — `UPROPERTY(Transient)`
- L176 _private member_ `TObjectPtr<const UClass> BuilderUClass = nullptr;` — `UPROPERTY(Transient)`

#### struct `FMetaSoundFrontendDocumentBuilder`  
`struct FMetaSoundFrontendDocumentBuilder`  
_L184-975_
- reflection: `USTRUCT()`
- desc: Builder used to support dynamically generating MetaSound documents at runtime. Builder contains caches that speed up common search and modification operations on a given document, which may result in slower performance on construction, but faster manipulation of its managed document.  The builder's managed copy of a document is expected to not be modified by any external system to avoid cache becoming stale.
- L190 _public prototype_ `FMetaSoundFrontendDocumentBuilder(TScriptInterface<IMetaSoundDocumentInterface> InDocumentInterface = { }, TSharedPtr<Metasound::Frontend::FDocumentModifyDelegates> InDocumentDelegates = { }, bool bPrimeCache = false);` — Default ctor should typically never be used directly as builder interface (and optionally delegates) should be specified on construction (Default exists only to make UObject reflection happy).
- L191 _public prototype_ `virtual ~FMetaSoundFrontendDocumentBuilder();`
- L194 _public prototype_ `void FinishBuilding();` — Call when the builder will no longer modify the IMetaSoundDocumentInterface
- L196 _public prototype_ `void AddAccessFlags(EMetasoundFrontendClassAccessFlags AccessFlags);`
- L197 _public prototype_ `void ClearAccessFlags();`
- L198 _public prototype_ `EMetasoundFrontendClassAccessFlags GetAccessFlags() const;`
- L199 _public prototype_ `void RemoveAccessFlags(EMetasoundFrontendClassAccessFlags AccessFlags);`
- L200 _public prototype_ `void SetAccessFlags(EMetasoundFrontendClassAccessFlags AccessFlags);`
- L203 _public prototype_ `const FMetasoundFrontendClass* AddDependency(FMetasoundFrontendClass NewDependency);` — Adds new dependency to MetaSound. Typically not necessary to call directly as dependencies are added automatically via registry when nodes are added, and can be removed when no longer referenced (see 'RemoveUnusedDependencies`).
- L205 _public prototype_ `void AddEdge(FMetasoundFrontendEdge&& InNewEdge, const FGuid* InPageID = nullptr);`
- L206 _public prototype_ `bool AddNamedEdges(const TSet<Metasound::Frontend::FNamedEdge>& ConnectionsToMake, TArray<const FMetasoundFrontendEdge*>* OutEdgesCreated = nullptr, bool bReplaceExistingConnections = true, const FGuid* InPageID = nullptr);`
- L207 _public prototype_ `bool AddEdgesByNodeClassInterfaceBindings(const FGuid& InFromNodeID, const FGuid& InToNodeID, bool bReplaceExistingConnections = true, const FGuid* InPageID = nullptr);`
- L208 _public prototype_ `bool AddEdgesFromMatchingInterfaceNodeOutputsToGraphOutputs(const FGuid& InNodeID, TArray<const FMetasoundFrontendEdge*>& OutEdgesCreated, bool bReplaceExistingConnections = true, const FGuid* InPageID = nullptr);`
- L209 _public prototype_ `bool AddEdgesFromMatchingInterfaceNodeInputsToGraphInputs(const FGuid& InNodeID, TArray<const FMetasoundFrontendEdge*>& OutEdgesCreated, bool bReplaceExistingConnections = true, const FGuid* InPageID = nullptr);`
- L213 _public prototype_ `const FMetasoundFrontendNode* AddGraphInput(FMetasoundFrontendClassInput ClassInput, const FGuid* InPageID = nullptr);` — Adds Graph Input to document, which in turn adds a referencing input node to ALL pages.  If valid PageID is provided, returns associated page's node pointer. If none provided, returns node pointer to node for the builder's currently set build page ID (see 'GetBuildPageID').
- L215 _public prototype_ `const FMetasoundFrontendVariable* AddGraphVariable(FName VariableName, FName DataType, const FMetasoundFrontendLiteral* Literal = nullptr, const FText* DisplayName = nullptr, const FText* Description = nullptr, const FGuid* InPageID = nullptr);`
- L216 _public prototype_ `const FMetasoundFrontendNode* AddGraphVariableNode(FName VariableName, EMetasoundFrontendClassType ClassType, FGuid InNodeID = FGuid::NewGuid(), const FGuid* InPageID = nullptr);`
- L217 _public prototype_ `const FMetasoundFrontendNode* AddGraphVariableMutatorNode(FName VariableName, FGuid InNodeID = FGuid::NewGuid(), const FGuid* InPageID = nullptr);`
- L218 _public prototype_ `const FMetasoundFrontendNode* AddGraphVariableAccessorNode(FName VariableName, FGuid InNodeID = FGuid::NewGuid(), const FGuid* InPageID = nullptr);`
- L219 _public prototype_ `const FMetasoundFrontendNode* AddGraphVariableDeferredAccessorNode(FName VariableName, FGuid InNodeID = FGuid::NewGuid(), const FGuid* InPageID = nullptr);`
- L223 _public prototype_ `const FMetasoundFrontendNode* AddGraphNode(const FMetasoundFrontendGraphClass& InClass, FGuid InNodeID = FGuid::NewGuid(), const FGuid* InPageID = nullptr);` — Adds node to document to the page associated with the given PageID.  If no valid PageID is provided, adds and returns node pointer to node for the builder's currently set build page ID (see 'GetBuildPageID').
- L227 _public prototype_ `const FMetasoundFrontendNode* AddGraphOutput(FMetasoundFrontendClassOutput ClassOutput, const FGuid* InPageID = nullptr);` — Adds Graph Output to document, which in turn adds a referencing output node to ALL pages.  If valid PageID is provided, returns associated page's node pointer. If none provided, returns node pointer to node for the builder's currently set build page ID (see 'GetBuildPageID').
- L230 _public prototype_ `bool AddInterface(FName InterfaceName);` — Adds an interface and associated inputs and outputs
- L235 _public prototype_ `UE_INTERNAL bool AddInterface(FName InterfaceName, bool bAddUserModifiableInterfaceOnly, const FMetaSoundFrontendDocumentBuilder* ReferenceBuilder);` — Internal AddInterface call for use in rebuild preset root graph If bAddUserModifiableInterfaceOnly is true, only user modifiable interfaces can be added (see FMetasoundFrontendInterfaceUClassOptions) Reference builder is used to copy node ids for added members so they aren't just regenerated with NewGuid
- L237 _public prototype_ `const FMetasoundFrontendNode* AddNodeByClassName(const FMetasoundFrontendClassName& InClassName, int32 InMajorVersion = 1, FGuid InNodeID = FGuid::NewGuid(), const FGuid* InPageID = nullptr);`
- L240 _public prototype_ `UE_INTERNAL const FMetasoundFrontendNode* AddNodeByClassName(const FMetasoundFrontendClassName& InClassName, int32 InMajorVersion, int32 InMinorVersion, FGuid InNodeID = FGuid::NewGuid(), const FGuid* InPageID = nullptr);` — Add node with specific major and minor version. The public version of AddNodeByClassName adds the highest minor version for a given major version
- L242 _public prototype_ `const FMetasoundFrontendNode* AddNodeByTemplate(const Metasound::Frontend::INodeTemplate& InTemplate, FNodeTemplateGenerateInterfaceParams Params, FGuid InNodeID = FGuid::NewGuid(), const FGuid* InPageID = nullptr);`
- L246 _public prototype_ `const FMetasoundFrontendGraph& AddGraphPage(const FGuid& InPageID, bool bDuplicateLastGraph, bool bSetAsBuildGraph = true);` — Adds a graph page to the given builder's document
- L249 _public prototype_ `UE_INTERNAL void ApplyNodeInstanceReplacementData(Metasound::Frontend::NodeReplacement::FNodeInstanceReplacementData&& InInstanceData, const FGuid& InNodeID, const FGuid* InPageID = nullptr, TArray<Metasound::Frontend::FVertexNameAndType>* OutDisconnectedInputs=nullptr, TArray<Metasound::Frontend::FVertexNameAndType>* OutDisconnectedOutputs=nullptr);` — Applying node instance replacement data for node update transforms/autoupdate
- L252 _public prototype_ `UE_INTERNAL Metasound::Frontend::NodeReplacement::FNodeInstanceReplacementData CaptureNodeInstanceReplacementData(const FGuid& InNodeID, const FGuid* InPageID = nullptr) const;` — Capture node replacement data for the existing node (connections, defaults, configuration, etc.)
- L258 _public prototype_ `void CacheRegistryMetadata() const;` — Caches transient dependency metadata & style (class & vertex) found in the registry that is not necessary for serialization or core graph generation.
- L263 _public prototype_ `bool CanAddEdge(const FMetasoundFrontendEdge& InEdge, const FGuid* InPageID = nullptr) const;` — Returns whether or not the given edge can be added, which requires that its input is not already connected and the edge is valid (see function 'IsValidEdge').
- L273 _public prototype_ `UE_INTERNAL bool CanAutoUpdate(const FGuid& InNodeID, const FGuid* InPageID = nullptr) const;` — Returns whether the node is eligible for auto-updating. Eligibility reasons include minor version revision, node update transform found, or the interface has changed, but no higher major revision is available. Can return true if the interface has changed but with only cosmetic differences (ex. DisplayName only used in editor) but no runtime behavior has been modified.
- L281 _public prototype_ `void ClearDocument(TSharedRef<Metasound::Frontend::FDocumentModifyDelegates> ModifyDelegates);` — Clears document completely of all graph page data (nodes, edges, & member metadata), dependencies, interfaces, member metadata, preset state, etc. Leaves ClassMetadata intact. Reloads the builder state, so external delegates must be relinked if desired. NOTE: Template struct is not cleared and must be managed by separate API call (see SetTemplate').
- L284 _public prototype_ `bool ClearMemberMetadata(const FGuid& InMemberID);`
- L290 _public prototype_ `bool ConformObjectToDocument();`
- L292 _public prototype_ `bool ContainsDependencyOfType(EMetasoundFrontendClassType ClassType) const;`
- L293 _public prototype_ `bool ContainsEdge(const FMetasoundFrontendEdge& InEdge, const FGuid* InPageID = nullptr) const;`
- L294 _public prototype_ `bool ContainsNode(const FGuid& InNodeID, const FGuid* InPageID = nullptr) const;`
- L297 _public prototype_ `bool ConvertFromPreset();` — `UE_DEPRECATED(5.8, "Use SetTemplate instead")`
- L300 _public prototype_ `bool ConvertToPreset(const FMetasoundFrontendDocument& InReferencedDocument, TSharedPtr<Metasound::Frontend::FDocumentModifyDelegates> ModifyDelegates = { });` — `UE_DEPRECATED(5.8, "Use SetTemplate instead")`
- L303 _public prototype_ `bool ConvertToPreset(const FMetaSoundFrontendDocumentBuilder& InReferencedDocumentBuilder, TSharedPtr<Metasound::Frontend::FDocumentModifyDelegates> ModifyDelegates = { });` — `UE_DEPRECATED(5.8, "Use SetTemplate instead")`
- L306 _public prototype_ `static TOptional<Metasound::FAnyDataReference> CreateDataReference(const Metasound::FOperatorSettings& InOperatorSettings, FName DataType, const Metasound::FLiteral& InLiteral, Metasound::EDataReferenceAccessType AccessType);`
- L311 _public prototype_ `UE_INTERNAL bool NodeInterfaceMatchesClassInterface(const FGuid& InNodeID, const FGuid& InPageID) const;` — Returns whether the node's interface is functionally the same as the node's class interface.
- L315 _public prototype_ `bool DiffAgainstRegistryInterface(const FGuid& InNodeID, const FGuid& InPageID, bool bInUseHighestMinorVersion, Metasound::Frontend::FClassInterfaceUpdates& OutInterfaceUpdates, bool bInForceRegenerateClassInterfaceOverride = true) const;` — Fills out the provided ClassInterfaceUpdate struct with the differences between the registry's version of the class interface and that of the node. Returns whether or not the interface was found in the registry.
- L318 _public prototype_ `const FMetasoundFrontendClassInput* DuplicateGraphInput(FName ExistingName, FName NewName);`
- L319 _public prototype_ `const FMetasoundFrontendClassOutput* DuplicateGraphOutput(FName ExistingName, FName NewName);`
- L320 _public prototype_ `const FMetasoundFrontendVariable* DuplicateGraphVariable(FName ExistingName, FName NewName, const FGuid* InPageID = nullptr);`
- L322 _public prototype_ `TConstStructView<FMetasoundFrontendClassInterface> FindClassInterfaceOverride(const FGuid& InNodeID, const FGuid* InPageID = nullptr) const;`
- L325 _public prototype_ `const FMetasoundFrontendEdgeStyle* FindConstEdgeStyle(const FGuid& InNodeID, FName OutputName, const FGuid* InPageID = nullptr) const;`
- L326 _public prototype_ `FMetasoundFrontendEdgeStyle* FindEdgeStyle(const FGuid& InNodeID, FName OutputName, const FGuid* InPageID = nullptr);`
- L327 _public prototype_ `FMetasoundFrontendEdgeStyle& FindOrAddEdgeStyle(const FGuid& InNodeID, FName OutputName, const FGuid* InPageID = nullptr);`
- L328 _public prototype_ `const FMetaSoundFrontendGraphComment* FindGraphComment(const FGuid& InCommentID, const FGuid* InPageID = nullptr) const;`
- L329 _public prototype_ `FMetaSoundFrontendGraphComment* FindGraphComment(const FGuid& InCommentID, const FGuid* InPageID = nullptr);`
- L330 _public prototype_ `FMetaSoundFrontendGraphComment& FindOrAddGraphComment(const FGuid& InCommentID, const FGuid* InPageID = nullptr);`
- L331 _public prototype_ `UMetaSoundFrontendMemberMetadata* FindMemberMetadata(const FGuid& InMemberID) const;`
- L335 _public prototype_ `static bool FindDeclaredInterfaces(const FMetasoundFrontendDocument& InDocument, TArray<const Metasound::Frontend::IInterfaceRegistryEntry*>& OutInterfaces);` — `UE_DEPRECATED(5.8, "Direct access to IInterfaceRegistryEntry is deprecated as it is not thread safe. Must now get copy of interface directly from the InterfaceRegistry.")`
- L338 _public prototype_ `bool FindDeclaredInterfaces(TArray<const Metasound::Frontend::IInterfaceRegistryEntry*>& OutInterfaces) const;` — `UE_DEPRECATED(5.8, "Direct access to IInterfaceRegistryEntry is deprecated as it is not thread safe. Must now get copy of interface directly from the InterfaceRegistry.")`
- L340 _public prototype_ `const FMetasoundFrontendClass* FindDependency(const FGuid& InClassID) const;`
- L341 _public prototype_ `const FMetasoundFrontendClass* FindDependency(const FMetasoundFrontendClassMetadata& InMetadata) const;`
- L342 _public prototype_ `const FMetasoundFrontendClass* FindDependency(const Metasound::Frontend::FNodeRegistryKey& InRegistryKey) const;`
- L344 _public prototype_ `TArray<const FMetasoundFrontendEdge*> FindEdges(const FGuid& InNodeID, const FGuid& InVertexID, const FGuid* InPageID = nullptr) const;`
- L346 _public prototype_ `const FMetasoundFrontendClassInput* FindGraphInput(FName InputName) const;`
- L347 _public prototype_ `const FMetasoundFrontendNode* FindGraphInputNode(FName InputName, const FGuid* InPageID = nullptr) const;`
- L348 _public prototype_ `const FMetasoundFrontendClassOutput* FindGraphOutput(FName OutputName) const;`
- L349 _public prototype_ `const FMetasoundFrontendNode* FindGraphOutputNode(FName OutputName, const FGuid* InPageID = nullptr) const;`
- L351 _public prototype_ `const FMetasoundFrontendVariable* FindGraphVariable(const FGuid& InVariableID, const FGuid* InPageID = nullptr) const;`
- L352 _public prototype_ `const FMetasoundFrontendVariable* FindGraphVariable(FName InVariableName, const FGuid* InPageID = nullptr) const;`
- L353 _public prototype_ `const FMetasoundFrontendVariable* FindGraphVariableByNodeID(const FGuid& InNodeID, const FGuid* InPageID = nullptr) const;`
- L355 _public prototype_ `bool FindInterfaceInputNodes(FName InterfaceName, TArray<const FMetasoundFrontendNode*>& OutInputs, const FGuid* InPageID = nullptr) const;`
- L356 _public prototype_ `bool FindInterfaceOutputNodes(FName InterfaceName, TArray<const FMetasoundFrontendNode*>& OutOutputs, const FGuid* InPageID = nullptr) const;`
- L359 _public prototype_ `const FMetasoundFrontendGraph& FindConstBuildGraphChecked() const;` — Accessor for the currently set build graph.
- L361 _public prototype_ `const FMetasoundFrontendNode* FindNode(const FGuid& InNodeID, const FGuid* InPageID = nullptr) const;`
- L363 _public prototype_ `const TConstStructView<FMetaSoundFrontendNodeConfiguration> FindNodeConfiguration(const FGuid& InNodeID, const FGuid* InPageID = nullptr) const;`
- L369 _public prototype_ `const int32* FindNodeIndex(const FGuid& InNodeID, const FGuid* InPageID = nullptr) const;` — Return the node's index in the document's specified paged graph's node array
- L372 _public prototype_ `TArray<const FMetasoundFrontendVertex*> FindUserModifiableNodeInputs(const FGuid& InNodeID, const FGuid* InPageID = nullptr) const;` — Returns all inputs on a given node that are user modifiable
- L375 _public prototype_ `TArray<const FMetasoundFrontendVertex*> FindUserModifiableNodeOutputs(const FGuid& InNodeID, const FGuid* InPageID = nullptr) const;` — Returns all outputs on a given node that are user modifiable
- L377 _public prototype_ `const FMetasoundFrontendVertex* FindNodeInput(const FGuid& InNodeID, const FGuid& InVertexID, const FGuid* InPageID = nullptr) const;`
- L378 _public prototype_ `const FMetasoundFrontendVertex* FindNodeInput(const FGuid& InNodeID, FName InVertexName, const FGuid* InPageID = nullptr) const;`
- L381 _public prototype_ `const TArray<FMetasoundFrontendClassInputDefault>* FindNodeClassInputDefaults(const FGuid& InNodeID, FName InVertexName, const FGuid* InPageID = nullptr) const;` — Returns class defaults associated with the given node input (as defined in the associated node's dependency)
- L384 _public prototype_ `const FMetasoundFrontendVertexLiteral* FindNodeInputDefault(const FGuid& InNodeID, const FGuid& InVertexID, const FGuid* InPageID = nullptr) const;` — Returns node input's vertex default if valid and assigned.
- L387 _public prototype_ `const FMetasoundFrontendVertexLiteral* FindNodeInputDefault(const FGuid& InNodeID, FName InVertexName, const FGuid* InPageID = nullptr) const;` — Returns node input's vertex default if valid and assigned.
- L389 _public prototype_ `TArray<const FMetasoundFrontendVertex*> FindNodeInputs(const FGuid& InNodeID, FName TypeName = FName(), const FGuid* InPageID = nullptr) const;`
- L390 _public prototype_ `TArray<const FMetasoundFrontendVertex*> FindNodeInputsConnectedToNodeOutput(const FGuid& InOutputNodeID, const FGuid& InOutputVertexID, TArray<const FMetasoundFrontendNode*>* ConnectedInputNodes = nullptr, const FGuid* InPageID = nullptr) const;`
- L392 _public prototype_ `const FMetasoundFrontendVertex* FindNodeOutput(const FGuid& InNodeID, const FGuid& InVertexID, const FGuid* InPageID = nullptr) const;`
- L393 _public prototype_ `const FMetasoundFrontendVertex* FindNodeOutput(const FGuid& InNodeID, FName InVertexName, const FGuid* InPageID = nullptr) const;`
- L394 _public prototype_ `TArray<const FMetasoundFrontendVertex*> FindNodeOutputs(const FGuid& InNodeID, FName TypeName = FName(), const FGuid* InPageID = nullptr) const;`
- L395 _public prototype_ `const FMetasoundFrontendVertex* FindNodeOutputConnectedToNodeInput(const FGuid& InInputNodeID, const FGuid& InInputVertexID, const FMetasoundFrontendNode** ConnectedOutputNode = nullptr, const FGuid* InPageID = nullptr) const;`
- L399 _public prototype_ `int32 FindGraphPageIndex(const FGuid& InPageID) const;` — Return the index of the given page in the document's PagedGraphs array. Returns INDEX_NONE in document where the given graph with the provided PageID is not found.
- L402 _public function_ `int32 FindPageIndex(const FGuid& InPageID) const` — `UE_DEPRECATED(5.8, "Use 'FindGraphPageIndex' instead")`
- L404 _public prototype_ `const FMetasoundFrontendDocument& GetConstDocumentChecked() const;`
- L411 _public function_ `template<typename TVertexMetadataType> UE_INTERNAL TVertexMetadataType* FindVertexMetadata(const FGuid& InNodeID) const` — Convenience function for attempting to get the underlying mutable document template vertex metadata. If the provided template vertex type is not that which the current document is set to or no document template is set, returns null.
- L428 _public function_ `template<typename TVertexMetadataType> UE_INTERNAL const TVertexMetadataType* FindConstVertexMetadata(const FGuid& InNodeID) const` — Convenience function for attempting to get the underlying mutable document template vertex metadata. If the provided template vertex type is not that which the current document is set to or no document template is set, returns null.
- L444 _public prototype_ `TStructView<FMetaSoundFrontendDocumentTemplate> GetDocumentTemplate() const;` — Returns mutable struct view of document template if set. Internal use only to avoid writing against struct members in invalid or dangerous, non-editor contexts (use 'SetTemplate' instead for most script or edit-time applications).
- L447 _public prototype_ `TStructView<FMetaSoundFrontendDocumentTemplate> GetDocumentConfiguration() const;` — Soft deprecated. To be deprecated in subsequent change.
- L451 _public prototype_ `TConstStructView<FMetaSoundFrontendDocumentTemplate> GetConstDocumentTemplate() const;` — Returns struct view of document template if set.
- L454 _public function_ `TConstStructView<FMetaSoundFrontendDocumentTemplate> GetConstDocumentConfiguration() const` — `UE_DEPRECATED(5.8, "Use GetConstDocumentTemplate() instead")`
- L460 _public function_ `template<typename TTemplateType> const TTemplateType* GetConstTemplateAs() const` — Convenience template function for attempting to get the underlying const pointer of the set configuration. If the provided configuration type is not that which the current document is set to or no configuration is set, returns null.
- L467 _public function_ `const TTemplateType* GetConstDocumentConfigurationAs() const` — `UE_DEPRECATED(5.8, "Use GetConstTemplateAs() instead")`
- L469 _public prototype_ `const IMetaSoundDocumentInterface& GetConstDocumentInterfaceChecked() const;`
- L470 _public prototype_ `const FString GetDebugName() const;`
- L473 _public prototype_ `const FGuid& GetBuildPageID() const;` — The graph ID used when requests are made to mutate specific paged graph topology (ex. adding or removing nodes or edges)
- L477 _public prototype_ `const FMetasoundFrontendNodeStyle* GetNodeStyle(const FGuid& InNodeID, const FGuid* InPageID = nullptr) const;` — Gets the editor-only style of a node with the given ID.
- L485 _public prototype_ `FText GetNodeTitle(const FGuid& InNodeID, const FGuid* InPageID = nullptr) const;` — Title used when displaying the given node. Returned text falls back in the following order: 1. If input, output, or variable (member), returns member type name. 2. If external or template node, uses: a. Node's class display name if set b. Asset name (if class is defined as an asset) c. Class name (if class is defined in code)
- L489 _public function_ `template<typename TObjectType> TObjectType& CastDocumentObjectChecked() const`
- L500 _public prototype_ `FMetasoundFrontendClassName GenerateNewClassName();` — Generates and returns new class name for the given builder's document. Should be used with extreme caution (i.e. on new assets, when migrating assets, or upon generation of transient MetaSounds), as using a persistent builder registered with the DocumentBuilderRegistry may result in stale asset records keyed off of an undefined class name.  In addition, this can potentially leave existing node references in an abandoned state to this class causing asset validation errors.
- L502 _public prototype_ `FName GenerateUniqueInputName(const FString& InBaseName) const;`
- L503 _public prototype_ `FName GenerateUniqueOutputName(const FString& InBaseName) const;`
- L504 _public prototype_ `FName GenerateUniqueVariableName(const FString& InBaseName) const;`
- L506 _public prototype_ `Metasound::Frontend::FDocumentModifyDelegates& GetDocumentDelegates();`
- L510 _public prototype_ `const FTopLevelAssetPath& GetHintPath() const;` — Path for document object provided at construction time. Cached on builder as a useful means of debugging and enables weak reference removal from the builder registry should the object be mid-destruction.
- L512 _public prototype_ `FMetasoundAssetBase& GetMetasoundAsset() const;`
- L515 _public prototype_ `FMetasoundAssetBase* GetReferencedPresetAsset() const;` — `UE_DEPRECATED(5.8, "Use Template API to access configuration as type FMetaSoundFrontendPresetTemplate and use the 'Parent' property directly.")`
- L517 _public prototype_ `int32 GetTransactionCount() const;`
- L519 _public prototype_ `TArray<const FMetasoundFrontendNode*> GetGraphInputTemplateNodes(FName InInputName, const FGuid* InPageID = nullptr);`
- L522 _public prototype_ `const TSet<FName>* GetGraphInputsInheritingDefault() const;` — `UE_DEPRECATED(5.8, "Input inheritance data is now stored on MetaSound Preset template metadata.")`
- L524 _public prototype_ `EMetasoundFrontendVertexAccessType GetNodeInputAccessType(const FGuid& InNodeID, const FGuid& InVertexID, const FGuid* InPageID = nullptr) const;`
- L530 _public prototype_ `FText GetNodeInputDisplayName(const FGuid& InNodeID, const FName VertexName, const FGuid* InPageID = nullptr) const;` — Returns friendly name of the given node input vertex. Unlike a straight look-up of the vertex metadata value, this tries and determines the best display name based on the parent node's class, if no display name is given converts the base FName to FText, etc.
- L535 _public prototype_ `FText GetNodeOutputDisplayName(const FGuid& InNodeID, const FName VertexName, const FGuid* InPageID = nullptr) const;` — Returns friendly name of the given node output vertex. Unlike a straight look-up of the vertex metadata value, this tries and determines the best display name based on the parent node's class, if no display name is given converts the base FName to FText, etc.
- L538 _public prototype_ `EMetasoundFrontendVertexAccessType GetNodeOutputAccessType(const FGuid& InNodeID, const FGuid& InVertexID, const FGuid* InPageID = nullptr) const;`
- L541 _public prototype_ `const bool GetIsAdvancedDisplay(const FName MemberName, const EMetasoundFrontendClassType Type) const;`
- L545 _public prototype_ `const FMetasoundFrontendLiteral* GetGraphInputDefault(FName InputName, const FGuid* InPageID = nullptr) const;` — Returns the default value set for the input with the given name on the given page.
- L548 _public prototype_ `const FMetasoundFrontendLiteral* GetGraphVariableDefault(FName InputName, const FGuid* InPageID = nullptr) const;` — Returns the default value set for the variable with the given name on the given page.
- L552 _public prototype_ `bool GetIsGraphEditable(const FGuid* InPageID = nullptr) const;` — If PageID set, returns whether or not the given page is editable.  If no page ID is set, returns whether graph with set build ID is editable.
- L556 _public prototype_ `void InitDocument(const FMetasoundFrontendDocument* InDocumentTemplate = nullptr, const FMetasoundFrontendClassName* InNewClassName = nullptr, bool bResetVersion = true);` — Initializes the builder's document, using the (optional) provided document template, (optional) class name, and (optionally) whether or not to reset the existing class version.
- L559 _public prototype_ `static void InitGraphClassMetadata(FMetasoundFrontendClassMetadata& InOutMetadata, bool bResetVersion = false, const FMetasoundFrontendClassName* NewClassName = nullptr);` — Initializes GraphClass Metadata, optionally resetting the version back to 1.0 and/or creating a unique class name if a name is not provided.
- L560 _public prototype_ `void InitGraphClassMetadata(bool bResetVersion, const FMetasoundFrontendClassName* NewClassName);`
- L562 _public prototype_ `void InitNodeLocations();`
- L568 _public prototype_ `bool IsDependencyReferenced(const FGuid& InClassID) const;`
- L572 _public function_ `template<typename TTemplateType> const bool IsDocumentConfiguredBy() const` — Determines if the builder is configured the given template type
- L582 _public prototype_ `bool IsNodeInputConnected(const FGuid& InNodeID, const FGuid& InVertexID, const FGuid* InPageID = nullptr) const;`
- L583 _public prototype_ `bool IsNodeInputConnectionUserModifiable(const FGuid& InNodeID, const FGuid& InVertexID, const FGuid* InPageID = nullptr) const;`
- L584 _public prototype_ `bool IsNodeOutputConnected(const FGuid& InNodeID, const FGuid& InVertexID, const FGuid* InPageID = nullptr) const;`
- L585 _public prototype_ `bool IsNodeOutputConnectionUserModifiable(const FGuid& InNodeID, const FGuid& InVertexID, const FGuid* InPageID = nullptr) const;`
- L587 _public prototype_ `bool IsInterfaceDeclared(FName InInterfaceName) const;`
- L588 _public prototype_ `bool IsInterfaceDeclared(const FMetasoundFrontendVersion& InInterfaceVersion) const;`
- L589 _public prototype_ `bool IsPreset() const;`
- L592 _public prototype_ `bool IsValid() const;` — Returns whether or not builder is attached to a DocumentInterface and is valid to build or act on a document.
- L596 _public prototype_ `Metasound::Frontend::EInvalidEdgeReason IsValidEdge(const FMetasoundFrontendEdge& InEdge, const FGuid* InPageID = nullptr) const;` — Returns whether or not the given edge is valid (i.e. represents an input and output that equate in data and access types) or malformed. Note that this does not return whether or not the given edge exists, but rather if it could be legally applied to the given edge vertices.
- L599 _public prototype_ `void IterateNodes(Metasound::Frontend::FConstClassAndNodeFunctionRef Func, const FGuid* InPageID = nullptr) const;` — Iterates all nodes for the given page (uses build page ID if not provided).
- L602 _public prototype_ `void IterateNodesByPredicate(Metasound::Frontend::FConstClassAndNodeAndPageIDFunctionRef Func, Metasound::Frontend::FNodePredicateFunctionRef PredicateFunc, const FGuid* InPageID = nullptr, bool bIterateAllPages = false) const;` — Iterates nodes, filtered by the given predicate. If bIterateAllPages is true, nodes on all pages will be considered and Page ID is ignored.
- L605 _public prototype_ `void IterateNodesByClassType(Metasound::Frontend::FConstClassAndNodeFunctionRef Func, EMetasoundFrontendClassType ClassType, const FGuid* InPageID = nullptr) const;` — Iterates nodes that are filtered by only subscribing to a class with the given type (asserts if provided invalid class type).
- L607 _public prototype_ `bool ModifyInterfaces(Metasound::Frontend::FModifyInterfaceOptions&& InOptions);`
- L610 _public prototype_ `bool RemoveDependency(const FGuid& InClassID);` — Removes all dependencies with the given ClassID. Removes any nodes (and corresponding edges) remaining in any MetaSound paged graphs.
- L613 _public prototype_ `bool RemoveDependency(EMetasoundFrontendClassType ClassType, const FMetasoundFrontendClassName& InClassName, const FMetasoundFrontendVersionNumber& InClassVersionNumber);` — Removes all dependencies with the given Class Type, Name, & Version Number. Removes any nodes (and corresponding edges) remaining in any MetaSound paged graphs.
- L615 _public prototype_ `bool RemoveEdge(const FMetasoundFrontendEdge& EdgeToRemove, const FGuid* InPageID = nullptr);`
- L618 _public prototype_ `bool RemoveEdges(const FGuid& InNodeID, const FGuid* InPageID = nullptr);` — Removes all edges connected to an input or output vertex associated with the node of the given ID.
- L620 _public prototype_ `bool RemoveEdgesByNodeClassInterfaceBindings(const FGuid& InOutputNodeID, const FGuid& InInputNodeID, const FGuid* InPageID = nullptr);`
- L621 _public prototype_ `bool RemoveEdgesFromNodeOutput(const FGuid& InNodeID, const FGuid& InVertexID, const FGuid* InPageID = nullptr);`
- L622 _public prototype_ `bool RemoveEdgeToNodeInput(const FGuid& InNodeID, const FGuid& InVertexID, const FGuid* InPageID = nullptr);`
- L625 _public prototype_ `bool RemoveEdgeStyle(const FGuid& InNodeID, FName OutputName, const FGuid* InPageID = nullptr);`
- L626 _public prototype_ `bool RemoveGraphComment(const FGuid& InCommentID, const FGuid* InPageID = nullptr);`
- L629 _public prototype_ `bool RemoveGraphInput(FName InputName, bool bRemoveTemplateInputNodes = true);`
- L630 _public prototype_ `bool RemoveGraphOutput(FName OutputName);`
- L633 _public prototype_ `bool RemoveGraphPage(const FGuid& InPageID);`
- L636 _public prototype_ `bool RemoveGraphVariable(FName VariableName, const FGuid* InPageID = nullptr);`
- L638 _public prototype_ `bool RemoveInterface(FName Name);`
- L639 _public prototype_ `bool RemoveNamedEdges(const TSet<Metasound::Frontend::FNamedEdge>& InNamedEdgesToRemove, TArray<FMetasoundFrontendEdge>* OutRemovedEdges = nullptr, const FGuid* InPageID = nullptr);`
- L642 _public prototype_ `bool RemoveNode(const FGuid& InNodeID, const FGuid* InPageID = nullptr);` — Removes node and connected edges from document. Does not remove dependency. Use RemoveUnusedDependencies
- L645 _public prototype_ `int32 RemoveNodeLocation(const FGuid& InNodeID, const FGuid* InLocationGuid = nullptr, const FGuid* InPageID = nullptr);`
- L648 _public prototype_ `void Reload(TSharedPtr<Metasound::Frontend::FDocumentModifyDelegates> Delegates = {}, bool bPrimeCache = false);`
- L651 _public prototype_ `bool RemoveGraphInputDefault(FName InputName, const FGuid& InPageID, bool bClearInheritsDefault);` — `UE_DEPRECATED(5.8, "Input inheritance data is now cached in MetaSound Preset template vertex metadata. No need to call directly here. Use overload without 'bClearInheritsDefault' parameter.")`
- L652 _public prototype_ `bool RemoveGraphInputDefault(FName InputName, const FGuid& InPageID);`
- L654 _public prototype_ `UE_INTERNAL bool StripGraphInputDefault(FName InputName, const FGuid& InPageID);` — Internal function to remove graph input default for cook. Same as RemoveGraphInputDefault but removing the default page input default is allowed.
- L656 _public prototype_ `bool RemoveNodeInputDefault(const FGuid& InNodeID, const FGuid& InVertexID, const FGuid* InPageID = nullptr);`
- L657 _public prototype_ `bool RemoveUnusedDependencies();`
- L662 _public prototype_ `bool ReplaceDependency(const Metasound::Frontend::FNodeClassRegistryKey& OldClass, const Metasound::Frontend::FNodeClassRegistryKey& NewClass, TArray<Metasound::Frontend::FVertexNameAndType>* OutDisconnectedInputs = nullptr, TArray<Metasound::Frontend::FVertexNameAndType>* OutDisconnectedOutputs = nullptr);` — Replaces existing dependency with a new one. Removes all nodes using this class, and readds nodes with new class, trying to maintain existing connections (based on name/data type) and data. Optionally report disconnected inputs and outputs
- L664 _public prototype_ `bool ResetGraphInputDefault(FName InputName);`
- L667 _public prototype_ `void ResetGraphPages(bool bClearDefaultGraph);` — Removes all graph pages except the default.  If bClearDefaultPage is true, clears the default graph page implementation.
- L671 _public prototype_ `void SetAuthor(const FString& InAuthor);`
- L682 _public prototype_ `bool SetBuildPageID(const FGuid& InBuildPageID, bool bBroadcastDelegate = true);` — Sets the builder's targeted paged graph ID to the given ID if it exists. Returns true if the builder is already targeting the given ID or if it successfully found a page implementation with the given ID and was able to switch to it, false if not. Swapping the targeted build graph ID clears the local cache, so swapping frequently can induce cache thrashing. BroadcastDelegate should always be true unless dealing with the controller API (exposed as a mechanism for mutating via controllers while deprecating.  Option will be removed in a future build).
- L687 _public prototype_ `void SetTemplate(TInstancedStruct<FMetaSoundFrontendDocumentTemplate> InConfig);` — Sets the entire internal configuration with that provided.
- L690 _public function_ `void SetDocumentConfiguration(TInstancedStruct<FMetaSoundFrontendDocumentTemplate> InConfig)` — `UE_DEPRECATED(5.8, "Use SetTemplate() instead")`
- L693 _public prototype_ `void SetTemplateProperties(TFunctionRef<void(TStructView<FMetaSoundFrontendDocumentTemplate>)> SetPropertyFunction);` — Update the given document template inline using the internal struct view passed to a given function.
- L696 _public function_ `void SetDocumentConfigurationProperties(TFunctionRef<void(TStructView<FMetaSoundFrontendDocumentTemplate>)> SetPropertyFunction)` — `UE_DEPRECATED(5.8, "Use SetTemplateProperties() instead")`
- L702 _public function_ `template <typename TConfig> bool SetTemplateProperties(TFunctionRef<void(TConfig&)> SetPropertyFunction)` — If struct type of function coincides with that of the given builder's MetaSound configuration, sets the given document template properties inline using the internal struct view passed to a given function. Returns true if set function successfully executed, false if not.
- L724 _public function_ `bool SetDocumentConfigurationProperties(TFunctionRef<void(TConfig&)> SetPropertyFunction)` — `UE_DEPRECATED(5.8, "Use SetTemplateProperties() instead")`
- L730 _public prototype_ `void SetIsGraphEditable(bool bIsEditable, const FGuid* PageID = nullptr) const;` — If page ID is provided, updates the graph's editable flag to the given value. If no page ID is provided, sets *all* paged graph fields to the given value.
- L734 _public prototype_ `bool SetGraphInputAdvancedDisplay(const FName InputName, const bool InAdvancedDisplay);` — Sets the given input`s IsAdvancedDisplay state. AdvancedDisplay pins are hidden in the node by default. returns true if state was changed.
- L740 _public prototype_ `bool SetGraphInputAccessType(FName InputName, EMetasoundFrontendVertexAccessType AccessType);` — Sets the given graph input's access type. If connected to other nodes and access type is not compatible, associated edges/connections are removed.  Returns true if either DataType was successfully set to new value or if AccessType is already the given AccessType.
- L745 _public prototype_ `bool SetGraphInputDataType(FName InputName, FName DataType);` — Sets the given graph input's data type. If connected to other nodes, associated edges/connections are removed.  Returns true if either DataType was successfully set to new value or if DataType is already the given DataType.
- L749 _public prototype_ `bool SetGraphInputDefault(FName InputName, FMetasoundFrontendLiteral InDefaultLiteral, const FGuid* InPageID = nullptr, EMetaSoundLiteralChangeType InChangeType = EMetaSoundLiteralChangeType::Set);` — Set the given graph input's default(s). Change type can be optionally passed in so the on input changed delegate can report the context, since a set can be used to perform remove/reset operations.
- L750 _public prototype_ `bool SetGraphInputDefaults(FName InputName, TArray<FMetasoundFrontendClassInputDefault> Defaults, EMetaSoundLiteralChangeType InChangeType = EMetaSoundLiteralChangeType::Set);`
- L754 _public prototype_ `bool SetGraphInputDescription(FName InputName, FText Description);` — Sets the graph input's description. Returns true if found and set, false if not.
- L757 _public prototype_ `bool SetGraphInputDisplayName(FName InputName, FText DisplayName);` — Sets the graph input's display name. Returns true if found and set, false if not.
- L761 _public prototype_ `bool SetGraphInputInheritsDefault(FName InName, bool bInputInheritsDefault, bool bForceUpdate = false);` — `UE_DEPRECATED(5.8, "Input inheritance information moved to preset document template")`
- L764 _public prototype_ `bool SetGraphInputsInheritingDefault(TSet<FName>&& InNames);` — `UE_DEPRECATED(5.8, "Input inheritance information moved to preset document template")`
- L767 _public prototype_ `bool SetGraphInputName(FName InputName, FName InName);` — Sets a given graph input's name to a new name. Succeeds if the graph output exists and the new name is set (or is the same as the old name).
- L771 _public prototype_ `bool SetGraphInputSortOrderIndex(const FName InputName, const int32 InSortOrderIndex);` — Sets the graph input's sort order index. Returns true if found and set, false if not.
- L774 _public prototype_ `bool SetGraphOutputSortOrderIndex(const FName OutputName, const int32 InSortOrderIndex);` — Sets the graph output's sort order index. Returns true if found and set, false if not.
- L778 _public prototype_ `bool SetGraphOutputAdvancedDisplay(const FName OutputName, const bool InAdvancedDisplay);` — Sets the given output`s IsAdvancedDisplay state. AdvancedDisplay pins are hidden in the node by default. returns true if state was changed.
- L784 _public prototype_ `bool SetGraphOutputAccessType(FName OutputName, EMetasoundFrontendVertexAccessType AccessType);` — Sets the given graph output's access type. If connected to other nodes and access type is not compatible, associated edges/connections are removed.  Returns true if either DataType was successfully set to new value or if AccessType is already the given AccessType.
- L789 _public prototype_ `bool SetGraphOutputDataType(FName OutputName, FName DataType);` — Sets the given graph output's data type. If connected to other nodes, associated edges/connections are removed.  Returns true if either DataType was successfully set to new value or if DataType is already the given DataType.
- L793 _public prototype_ `bool SetGraphOutputDescription(FName OutputName, FText Description);` — Sets the graph output's description. Returns true if found and set, false if not.
- L796 _public prototype_ `bool SetGraphOutputDisplayName(FName OutputName, FText DisplayName);` — Sets the graph input's display name. Returns true if found and set, false if not.
- L800 _public prototype_ `bool SetGraphOutputName(FName InputName, FName InName);` — Sets a given graph output's name to a new name. Succeeds if the graph output exists and the new name is set (or is the same as the old name).
- L803 _public prototype_ `bool SetGraphVariableDefault(FName VariableName, FMetasoundFrontendLiteral InDefaultLiteral, const FGuid* InPageID = nullptr);` — Sets the given graph variable's default.
- L807 _public prototype_ `bool SetGraphVariableDescription(FName VariableName, FText Description, const FGuid* InPageID = nullptr);` — Sets the given graph variable's description.
- L810 _public prototype_ `bool SetGraphVariableDisplayName(FName VariableName, FText DisplayName, const FGuid* InPageID = nullptr);` — Sets the given graph variable's display name.
- L814 _public prototype_ `bool SetGraphVariableName(FName VariableName, FName NewName, const FGuid* InPageID = nullptr);` — Sets the given graph variable's description.
- L817 _public prototype_ `void SetDisplayName(const FText& InDisplayName);`
- L818 _public prototype_ `void SetDescription(const FText& InDescription);`
- L819 _public prototype_ `void SetKeywords(const TArray<FText>& InKeywords);`
- L820 _public prototype_ `void SetCategoryHierarchy(const TArray<FText>& InCategoryHierarchy);`
- L823 _public prototype_ `void SetIsDeprecated(const bool bInIsDeprecated);` — `UE_DEPRECATED(5.7, "Use AccessFlags API calls with deprecation flag instead")`
- L824 _public prototype_ `void SetInputStyle(FMetasoundFrontendInterfaceStyle&& Style);`
- L825 _public prototype_ `void SetOutputStyle(FMetasoundFrontendInterfaceStyle&& Style);`
- L827 _public prototype_ `void SetMemberMetadata(UMetaSoundFrontendMemberMetadata& NewMetadata);`
- L831 _public prototype_ `bool SetNodeComment(const FGuid& InNodeID, FString&& InNewComment, const FGuid* InPageID = nullptr);` — Sets the editor-only comment to the provided value. Returns true if the node was found and the comment was updated, false if not.
- L835 _public prototype_ `bool SetNodeCommentVisible(const FGuid& InNodeID, bool bIsVisible, const FGuid* InPageID = nullptr);` — Sets the editor-only comment visibility. Returns true if the node was found and the visibility was set, false if not.
- L839 _public prototype_ `bool SetNodeLocation(const FGuid& InNodeID, const FVector2D& InLocation, const FGuid* InLocationGuid = nullptr, const FGuid* InPageID = nullptr);` — Sets the editor-only node location of a node with the given ID to the provided location. Returns true if the node was found and the location was updated, false if not.
- L842 _public prototype_ `bool SetNodeUnconnectedPinsHidden(const FGuid& InNodeID, const bool bUnconnectedPinsHidden, const FGuid* InPageID = nullptr);` — Sets the editor-only Unconnected Pins Hidden for a node with the given ID.
- L847 _public prototype_ `bool SetNodeConfiguration(const FGuid& InNodeID, TInstancedStruct<FMetaSoundFrontendNodeConfiguration> InNodeConfiguration, const FGuid* InPageID = nullptr);` — Sets the node configuration for the given node and updates the interface returns true if the node configuration is set
- L849 _public prototype_ `bool SetNodeInputDefault(const FGuid& InNodeID, const FGuid& InVertexID, const FMetasoundFrontendLiteral& InLiteral, const FGuid* InPageID = nullptr);`
- L852 _public prototype_ `void SetVersionNumber(const FMetasoundFrontendVersionNumber& InDocumentVersionNumber);` — Sets the document's version number.  Should only be called by document versioning.
- L854 _public prototype_ `bool SwapGraphInput(const FMetasoundFrontendClassVertex& InExistingInputVertex, const FMetasoundFrontendClassVertex& NewInputVertex);`
- L855 _public prototype_ `bool SwapGraphOutput(const FMetasoundFrontendClassVertex& InExistingOutputVertex, const FMetasoundFrontendClassVertex& NewOutputVertex);`
- L861 _public prototype_ `bool SynchronizeDependencyMetadata(TArray<const FMetasoundFrontendClass*>* InOutModifiedClasses = nullptr);` — Synchronizes all dependency Metadata in document with that found in the registry. If not found in the registry, no action taken. Returns false if any dependencies could not be checked for updates. If provided array, pointers to classes that were modified will be added to it.
- L863 _public prototype_ `bool UpdateDependencyRegistryData(const TMap<Metasound::Frontend::FNodeRegistryKey, Metasound::Frontend::FNodeRegistryKey>& OldToNewClassKeys);`
- L868 _public prototype_ `bool UpdateNodeInterfaceFromConfiguration(const FGuid& InNodeID, const FGuid* InPageID = nullptr);` — If a node contains a node configuration, update the node class interface and interface. Returns true if node is found.
- L873 _public prototype_ `bool TransformTemplateNodes();` — Transforms template nodes within the given builder's document, which can include swapping associated edges and/or replacing nodes with other, registry-defined concrete node class instances. Returns true if any template nodes were processed.
- L889 _public prototype_ `const FTopLevelAssetPath GetBuilderClassPath() const;`
- L892 _private member_ `bool bInTemplateScope = false;`
- L894 _private typedef_ `using FFinalizeNodeFunctionRef = TFunctionRef<void(FMetasoundFrontendNode&, const Metasound::Frontend::FNodeRegistryKey&)>;`
- L896 _private prototype_ `TInstancedStruct<FMetaSoundFrontendNodeConfiguration> CreateFrontendNodeConfiguration(const FMetasoundFrontendClassMetadata& InClassMetadata) const;`
- L897 _private prototype_ `TInstancedStruct<FMetaSoundFrontendNodeConfiguration> CreateFrontendNodeConfiguration(EMetasoundFrontendClassType InClassType, const Metasound::Frontend::FNodeRegistryKey& InClassKey) const;`
- L899 _private prototype_ `bool AddInterfaceInternal(FName InterfaceName, bool bAddUserModifiableInterfaceOnly = true, const FMetaSoundFrontendDocumentBuilder* ReferenceBuilder = nullptr);`
- L901 _private prototype_ `FMetasoundFrontendNode* AddNodeInternal(const FMetasoundFrontendClassMetadata& InClassMetadata, Metasound::Frontend::FFinalizeNodeFunctionRef FinalizeNode, const FGuid& InPageID, FGuid InNodeID = FGuid::NewGuid(), int32* NewNodeIndex = nullptr);`
- L902 _private prototype_ `FMetasoundFrontendNode* AddNodeInternal(const Metasound::Frontend::FNodeRegistryKey& InClassKey, FFinalizeNodeFunctionRef FinalizeNode, const FGuid& InPageID, FGuid InNodeID = FGuid::NewGuid(), int32* NewNodeIndex = nullptr);`
- L904 _private prototype_ `const FMetasoundFrontendNode* AddNodeByClassInternal(FMetasoundFrontendClass&& InClass, FGuid InNodeID, const FGuid* InPageID);`
- L906 _private prototype_ `void BeginBuilding(TSharedPtr<Metasound::Frontend::FDocumentModifyDelegates> Delegates = {}, bool bPrimeCache = false);`
- L912 _private prototype_ `bool ConformGraphInputNodeToClass(const FMetasoundFrontendClassInput& GraphInput);` — Conforms GraphOutput node's ClassID, Access & Data Type with the GraphOutput. Creates and removes dependencies as necessary within the document dependency array. Does *NOT* modify edge data (i.e. if the DataType is changed on the given node and it has corresponding edges, edges may then be invalid due to access type/DataType incompatibility).
- L918 _private prototype_ `bool ConformGraphOutputNodeToClass(const FMetasoundFrontendClassOutput& GraphOutput);` — Conforms GraphOutput node's ClassID, Access & Data Type with the GraphOutput. Creates and removes dependencies as necessary within the document dependency array. Does *NOT* modify edge data (i.e. if the DataType is changed on the given node and it has corresponding edges, edges may then be invalid due to access type/DataType incompatibility).
- L920 _private prototype_ `FMetasoundFrontendGraph& FindBuildGraphChecked() const;`
- L922 _private prototype_ `FMetasoundFrontendVariable* FindGraphVariableInternal(FName InVariableName, const FGuid* InPageID = nullptr);`
- L924 _private prototype_ `bool FindNodeClassInterfaces(const FGuid& InNodeID, TSet<FMetasoundFrontendVersion>& OutInterfaces, const FGuid& InPageID) const;`
- L928 _private prototype_ `FMetasoundFrontendNode* FindNodeInternal(const FGuid& InNodeID, const FGuid* InPageID = nullptr);` — Returns pointer to editable node.  Modifying data on the node directly can be inherently dangerous if associated node cache data is not updated to reflect any changes to the given node (ex. changing NodeID, interface, etc.)
- L930 _private prototype_ `const FMetasoundFrontendNode* FindHeadNodeInVariableStack(FName VariableName, const FGuid* InPageID = nullptr) const;`
- L931 _private prototype_ `const FMetasoundFrontendNode* FindTailNodeInVariableStack(FName VariableName, const FGuid* InPageID = nullptr) const;`
- L933 _private prototype_ `void IterateNodesConnectedWithVertex(const FMetasoundFrontendVertexHandle& Vertex, TFunctionRef<void(const FMetasoundFrontendEdge&, FMetasoundFrontendNode&)> NodeIndexIterFunc, const FGuid& InPageID);`
- L935 _private prototype_ `FMetasoundFrontendDocument& GetDocumentChecked() const;`
- L936 _private prototype_ `IMetaSoundDocumentInterface& GetDocumentInterfaceChecked() const;`
- L942 _private prototype_ `UE_INTERNAL const FMetasoundFrontendClass* ReplaceDependencyInternal(const FMetasoundFrontendClass& OldDependency, FMetasoundFrontendClass NewDependency);` — In place dependency replacement of a dependency with a new dependency at the same index with the same ID For internal use only as a bit of a backdoor for updating multiple nodes of dependency that requires an in place update so subsequent updates use the new dependency but without having to Remove and Add the old dependency and all its nodes at once Returns new dependency
- L943 _private prototype_ `void RemoveSwapDependencyInternal(int32 Index);`
- L945 _private prototype_ `bool RemoveGraphInputDefaultInternal(FName InputName, const FGuid& InPageID);`
- L947 _private prototype_ `bool SpliceVariableNodeFromStack(const FGuid& InNodeID, const FGuid& InPageID);`
- L948 _private prototype_ `bool UnlinkVariableNode(const FGuid& InNodeID, const FGuid& InPageID);`
- L959 _private prototype_ `bool ShouldReplaceExistingNodeConfig(TConstStructView<FMetaSoundFrontendNodeConfiguration> InRegisteredNodeConfig, TConstStructView<FMetaSoundFrontendNodeConfiguration> InExistingConfig) const;`
- L960 _private prototype_ `const FMetasoundFrontendClassInterface& GetApplicableRegistryInterface(const FMetasoundFrontendClass& InRegisteredClass, const FNodeConfigurationUpdateData& InNodeConfigurationUpdates) const;`
- L961 _private prototype_ `void FindNodeConfigurationUpdates(const FGuid& InNodeID, const FGuid& InPageID, const FMetasoundFrontendClass& InRegisteredClass, FNodeConfigurationUpdateData& OutNodeConfigUpdates, bool bInForceRegenerateClassInterfaceOverride) const;`
- L964 _private member_ `TScriptInterface<IMetaSoundDocumentInterface> DocumentInterface;` — `UPROPERTY(Transient)`
- L969 _private member_ `FGuid BuildPageID;` — `UPROPERTY(Transient)` — Page ID to apply build transaction to if no optional PageID is provided in explicit function call. (Also used to support back compat for Controller API until mutable controllers are adequately deprecated).
- L971 _private member_ `TSharedPtr<Metasound::Frontend::IDocumentCache> DocumentCache;`
- L972 _private member_ `TSharedPtr<Metasound::Frontend::FDocumentModifyDelegates> DocumentDelegates;`
- L974 _private member_ `FTopLevelAssetPath HintPath;`

#### struct `FMetaSoundFrontendDocumentBuilder::IPropertyVersionTransform`  
`struct IPropertyVersionTransform`  
_L876-886_
- desc: Struct enabling property migration of data that must be applied prior to versioning logic
- L879 _public prototype_ `virtual ~IPropertyVersionTransform() = default;`
- L882 _protected prototype_ `virtual bool Transform(FMetaSoundFrontendDocumentBuilder& Builder) const = 0;`
- L885 _protected prototype_ `static FMetasoundFrontendDocument& GetDocumentUnsafe(const FMetaSoundFrontendDocumentBuilder& Builder);` — Allows for unsafe access to a document for property migration.

#### struct `FMetaSoundFrontendDocumentBuilder::FNodeConfigurationUpdateData`  
`struct FNodeConfigurationUpdateData`  
_L950-957_
- L952 _public member_ `TConstStructView<FMetaSoundFrontendNodeConfiguration> ExistingConfig;`
- L953 _public member_ `TConstStructView<FMetasoundFrontendClassInterface> ExistingClassInterfaceOverride;`
- L954 _public member_ `TInstancedStruct<FMetaSoundFrontendNodeConfiguration> RegisteredConfig;`
- L955 _public member_ `TInstancedStruct<FMetasoundFrontendClassInterface> RegeneratedClassInterfaceOverride;`
- L956 _public member_ `bool bDidUpdateClassInterfaceOverride = false;`

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L34 _namespace_ `namespace Metasound`
- L34 _namespace_ `namespace Frontend` (scope `Metasound`)
- L40 _typedef_ `using FNodePredicateFunctionRef = TFunctionRef<bool(const FMetasoundFrontendNode&)>;` (scope `Metasound::Frontend`)
- L41 _typedef_ `using FConstClassAndNodeFunctionRef = TFunctionRef<void(const FMetasoundFrontendClass&, const FMetasoundFrontendNode&)>;` (scope `Metasound::Frontend`)
- L42 _typedef_ `using FConstClassAndNodeAndPageIDFunctionRef = TFunctionRef<void(const FMetasoundFrontendClass&, const FMetasoundFrontendNode&, const FGuid&)>;` (scope `Metasound::Frontend`)
- L43 _typedef_ `using FFinalizeNodeFunctionRef = TFunctionRef<void(FMetasoundFrontendNode&, const Metasound::Frontend::FNodeRegistryKey&)>;` (scope `Metasound::Frontend`)
- L44 _typedef_ `using FVertexNameAndType = TTuple<FName, FName>;` (scope `Metasound::Frontend`)
- L46 _namespace_ `namespace NodeReplacement` (scope `Metasound::Frontend`)
- L60 _prototype_ `FString LexToString(const EInvalidEdgeReason& InReason);` (scope `Metasound::Frontend`)
- L69 _function_ `friend bool operator==(const FNamedEdge& InLHS, const FNamedEdge& InRHS)` (scope `Metasound::Frontend`)
- L77 _function_ `friend bool operator!=(const FNamedEdge& InLHS, const FNamedEdge& InRHS)` (scope `Metasound::Frontend`)
- L82 _function_ `friend inline uint32 GetTypeHash(const FNamedEdge& InBinding)` (scope `Metasound::Frontend`)
- L710 _function_ `` (scope `FMetaSoundFrontendDocumentBuilder::SetTemplateProperties`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendDocumentBuilderRegistry.h` (Public)


#### class `Metasound::Frontend::IDocumentBuilderRegistry`  
`class IDocumentBuilderRegistry`  
_L26-88_
- L29 _public prototype_ `virtual ~IDocumentBuilderRegistry() = default;`
- L38 _public prototype_ `virtual bool CookPages(FName CookPlatformName, FMetaSoundFrontendDocumentBuilder& Builder) const = 0;` — `UE_DEPRECATED(5.7, "Use StripUnusedPages(...) instead.")` — Given the provided builder, removes paged data within the associated document for a cooked build. This function removes graphs and input defaults which are not to ever be used by a given cook platform, allowing users to optimize away data and scale the amount of memory required for initial load of input UObjects and graph topology, which can also positively effect runtime performance as well, etc. Returns true if builder modified the document, false if not.
- L41 _public prototype_ `virtual FMetaSoundFrontendDocumentBuilder* FindBuilder(TScriptInterface<IMetaSoundDocumentInterface> MetaSound) const = 0;`
- L42 _public prototype_ `virtual FMetaSoundFrontendDocumentBuilder* FindBuilder(const FMetasoundFrontendClassName& ClassName, const FTopLevelAssetPath& AssetPath) const = 0;`
- L43 _public prototype_ `virtual TArray<FMetaSoundFrontendDocumentBuilder*> FindBuilders(const FMetasoundFrontendClassName& ClassName) const = 0;`
- L44 _public prototype_ `virtual FMetaSoundFrontendDocumentBuilder* FindOutermostBuilder(const UObject& InSubObject) const = 0;`
- L52 _public prototype_ `virtual FMetaSoundFrontendDocumentBuilder& FindOrBeginBuilding(TScriptInterface<IMetaSoundDocumentInterface> MetaSound) = 0;` — Find the existing builder for the given MetaSound, or optionally begin building by attaching a new builder.  Only available in builds with editor only data as building serialized assets (which may have template nodes, cooked builds do not) is only supported when editor data is loaded. Creating transient builders can simply be done by passing a new MetaSound asset to a FMetaSoundFrontendDocumentBuilder constructor, or this registry's implementation may supply its own create call for tracking and reuse purposes.
- L57 _public prototype_ `virtual bool FinishBuilding(const FMetasoundFrontendClassName& InClassName, bool bForceUnregisterNodeClass = false) const = 0;` — Removes builder from registry, clearing any cached builder state. (Optionally) forces unregistration from the Frontend Node Class Registry (If the builder has outstanding transactions, unregistration from the Node Class Registry will occur regardless).
- L58 _public prototype_ `virtual bool FinishBuilding(const FMetasoundFrontendClassName& InClassName, const FTopLevelAssetPath& InAssetPath, bool bForceUnregisterNodeClass = false) const = 0;`
- L62 _public prototype_ `virtual bool ReloadBuilder(const FMetasoundFrontendClassName& InClassName) const = 0;` — Reloads the given builder, maintaining all modify delegate subscriptions. Returns true if builder was found and reloaded, false if not found.
- L65 _public prototype_ `virtual FGuid ResolveTargetPageID(const FMetasoundFrontendGraphClass& InGraphClass) const = 0;` — `UE_DEPRECATED(5.7, "This is no longer supported. FindPreferredPage(...)")`
- L68 _public prototype_ `virtual FGuid ResolveTargetPageID(const FMetasoundFrontendClassInput& InClassInput) const = 0;` — `UE_DEPRECATED(5.7, "This is no longer supported. FindPreferredPage(...)")`
- L71 _public prototype_ `virtual FGuid ResolveTargetPageID(const TArray<FMetasoundFrontendClassInputDefault>& Defaults) const = 0;` — `UE_DEPRECATED(5.7, "This is no longer supported. FindPreferredPage(...)")`
- L74 _public prototype_ `virtual TArrayView<const FGuid> GetPageOrder() const = 0;` — `UE_DEPRECATED(5.7, "This is only used to support existing deprecated functionality")`
- L78 _public prototype_ `virtual TArray<FGuid> GetCookedTargetPages(FName InPlatformName) const = 0;` — `UE_DEPRECATED(5.7, "This is only used to support existing deprecated functionality")`
- L81 _public prototype_ `virtual TArray<FGuid> GetCookedPageOrder(FName InPlatformName) const = 0;` — `UE_DEPRECATED(5.7, "This is only used to support existing deprecated functionality")`
- L84 _public prototype_ `static class IDocumentBuilderRegistry* Get();`
- L85 _public prototype_ `static class IDocumentBuilderRegistry& GetChecked();`
- L86 _public prototype_ `static void Deinitialize();`
- L87 _public prototype_ `static void Initialize(TUniquePtr<IDocumentBuilderRegistry>&& InBuilderRegistry);`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L24 _namespace_ `namespace Metasound`
- L24 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendDocumentCacheInterface.h` (Public)


#### class `Metasound::Frontend::IDocumentGraphNodeCache`  
`class IDocumentGraphNodeCache : public TSharedFromThis<IDocumentGraphNodeCache>`  
_L26-65_
- inherits: `TSharedFromThis<IDocumentGraphNodeCache>`
- desc: Interface for querying cached document nodes.
- L29 _public prototype_ `virtual ~IDocumentGraphNodeCache() = default;`
- L31 _public prototype_ `virtual bool ContainsNode(const FGuid& InNodeID) const = 0;`
- L32 _public prototype_ `virtual bool ContainsNodesOfClassID(const FGuid& InClassID) const = 0;`
- L34 _public prototype_ `virtual const int32* FindNodeIndex(const FGuid& InNodeID) const = 0;`
- L35 _public prototype_ `virtual TArray<const FMetasoundFrontendNode*> FindNodesOfClassID(const FGuid& InClassID) const = 0;`
- L37 _public prototype_ `virtual const FMetasoundFrontendNode* FindNode(const FGuid& InNodeID) const = 0;`
- L39 _public prototype_ `virtual TArray<const FMetasoundFrontendVertex*> FindNodeInputs(const FGuid& InNodeID, FName TypeName = FName()) const = 0;`
- L40 _public prototype_ `virtual TArray<const FMetasoundFrontendVertex*> FindNodeOutputs(const FGuid& InNodeID, FName TypeName = FName()) const = 0;`
- L43 _public prototype_ `virtual const FMetasoundFrontendVertex* FindInputVertex(const FGuid& InNodeID, const FGuid& InVertexID) const = 0;` — Returns corresponding input vertex if it exists
- L46 _public prototype_ `virtual const FMetasoundFrontendVertex* FindInputVertex(const FGuid& InNodeID, FName InVertexName) const = 0;` — Returns corresponding input vertex if it exists
- L49 _public prototype_ `virtual const FMetasoundFrontendVertex* FindOutputVertex(const FGuid& InNodeID, const FGuid& InVertexID) const = 0;` — Returns corresponding output vertex if it exists
- L52 _public prototype_ `virtual const FMetasoundFrontendVertex* FindOutputVertex(const FGuid& InNodeID, FName InVertexName) const = 0;` — Returns corresponding output vertex if it exists
- L55 _public prototype_ `virtual TArray<const FMetasoundFrontendVertex*> FindReroutedInputVertices(const FGuid& InNodeID, const FGuid& InVertexID, TArray<const FMetasoundFrontendNode*>* ConnectedNodes = nullptr, bool* bOutIsRerouted = nullptr) const = 0;` — Recursively finds rerouted input vertices if they exist. Returns corresponding nodes to vertices if array provided. Sets boolean determining if connected to reroute if provided (optional).
- L58 _public prototype_ `virtual TArray<const FMetasoundFrontendVertex*> FindReroutedInputVertices(const FGuid& InNodeID, FName InVertexName, TArray<const FMetasoundFrontendNode*>* ConnectedNodes = nullptr, bool* bOutIsRerouted = nullptr) const = 0;` — Recursively finds rerouted input vertices if they exist. Returns corresponding nodes to vertices if array provided. Sets boolean determining if connected to reroute if provided (optional).
- L61 _public prototype_ `virtual const FMetasoundFrontendVertex* FindReroutedOutputVertex(const FGuid& InNodeID, const FGuid& InVertexID, const FMetasoundFrontendNode** ConnectedNodes = nullptr, bool* bOutIsRerouted = nullptr) const = 0;` — Recursively finds rerouted output vertex if it exist. Returns corresponding nodes to vertices if pointer provided. Sets boolean determining if connected to reroute if provided (optional).
- L64 _public prototype_ `virtual const FMetasoundFrontendVertex* FindReroutedOutputVertex(const FGuid& InNodeID, FName InVertexName, const FMetasoundFrontendNode** ConnectedNodes = nullptr, bool* bOutIsRerouted = nullptr) const = 0;` — Recursively finds rerouted output vertex if it exist. Returns corresponding node to vertices if pointer provided. Sets boolean determining if connected to reroute if provided (optional).

#### class `Metasound::Frontend::IDocumentGraphEdgeCache`  
`class IDocumentGraphEdgeCache : public TSharedFromThis<IDocumentGraphEdgeCache>`  
_L68-82_
- inherits: `TSharedFromThis<IDocumentGraphEdgeCache>`
- desc: Interface for querying cached document edges.
- L71 _public prototype_ `virtual ~IDocumentGraphEdgeCache() = default;`
- L73 _public prototype_ `virtual bool ContainsEdge(const FMetasoundFrontendEdge& InEdge) const = 0;`
- L75 _public prototype_ `virtual bool IsNodeInputConnected(const FGuid& InNodeID, const FGuid& InVertexID) const = 0;`
- L76 _public prototype_ `virtual bool IsNodeOutputConnected(const FGuid& InNodeID, const FGuid& InVertexID) const = 0;`
- L78 _public prototype_ `virtual TArray<const FMetasoundFrontendEdge*> FindEdges(const FGuid& InNodeID, const FGuid& InVertexID) const = 0;`
- L79 _public prototype_ `virtual const int32* FindEdgeIndexToNodeInput(const FGuid& InNodeID, const FGuid& InVertexID) const = 0;`
- L81 _public prototype_ `virtual const TArrayView<const int32> FindEdgeIndicesFromNodeOutput(const FGuid& InNodeID, const FGuid& InVertexID) const = 0;`

#### class `Metasound::Frontend::IDocumentGraphInterfaceCache`  
`class IDocumentGraphInterfaceCache : public TSharedFromThis<IDocumentGraphInterfaceCache>`  
_L85-94_
- inherits: `TSharedFromThis<IDocumentGraphInterfaceCache>`
- desc: Interface for querying cached document interface.
- L88 _public prototype_ `virtual ~IDocumentGraphInterfaceCache() = default;`
- L90 _public prototype_ `virtual const FMetasoundFrontendClassInput* FindInput(FName InputName) const = 0;`
- L91 _public prototype_ `virtual const int32* FindInputIndex(FName InputName) const = 0;`
- L92 _public prototype_ `virtual const FMetasoundFrontendClassOutput* FindOutput(FName OutputName) const = 0;`
- L93 _public prototype_ `virtual const int32* FindOutputIndex(FName OutputName) const = 0;`

#### class `Metasound::Frontend::IDocumentCache`  
`class IDocumentCache : public TSharedFromThis<IDocumentCache>`  
_L97-130_
- inherits: `TSharedFromThis<IDocumentCache>`
- desc: Interface for querying cached document dependencies.
- L100 _public prototype_ `virtual ~IDocumentCache() = default;`
- L102 _public prototype_ `virtual bool ContainsDependency(const FNodeRegistryKey& InClassKey) const = 0;`
- L103 _public prototype_ `virtual bool ContainsDependencyOfType(EMetasoundFrontendClassType ClassType) const = 0;`
- L104 _public prototype_ `virtual const FMetasoundFrontendClass* FindDependency(const Metasound::Frontend::FNodeRegistryKey& InClassKey) const = 0;`
- L105 _public prototype_ `virtual const FMetasoundFrontendClass* FindDependency(const FGuid& InClassID) const = 0;`
- L106 _public prototype_ `virtual const int32* FindDependencyIndex(const Metasound::Frontend::FNodeRegistryKey& InClassKey) const = 0;`
- L107 _public prototype_ `virtual const int32* FindDependencyIndex(const FGuid& InClassID) const = 0;`
- L109 _public prototype_ `virtual const FMetasoundFrontendDocument& GetDocument() const = 0;`
- L112 _public function_ `virtual const IDocumentGraphNodeCache& GetNodeCache() const` — `UE_DEPRECATED(5.5, "Use overload providing pageID")`
- L115 _public prototype_ `virtual const IDocumentGraphNodeCache& GetNodeCache(const FGuid& InPageID) const = 0;` — Returns NodeCache associated with the given PageID
- L118 _public function_ `virtual const IDocumentGraphEdgeCache& GetEdgeCache() const` — `UE_DEPRECATED(5.5, "Use overload providing pageID")`
- L121 _public prototype_ `virtual const IDocumentGraphEdgeCache& GetEdgeCache(const FGuid& InPageID) const = 0;` — Returns EdgeCache associated with the given PageID
- L124 _public prototype_ `virtual const IDocumentGraphInterfaceCache& GetInterfaceCache() const = 0;` — Returns InterfaceCache for the given document
- L128 _public prototype_ `virtual void SetBuildPageID(const FGuid& InPageID) = 0;` — Sets the default BuildPageID for the given document

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace Metasound`
- L23 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendDocumentIdGenerator.h` (Public)


#### class `Metasound::Frontend::FDocumentIDGenerator`  
`class FDocumentIDGenerator`  
_L48-78_
- desc: For generating IDs using a given document. USAGE: If you want everything within the calling scope to be deterministic, use the scope determinism lock like you would a `FScopeLock` { constexpr bool bIsDeterministic = true; FDocumentIDGenerator::FScopeDeterminism DeterminismScope(bIsDeterministic); // Anything called in this scope will use a deterministic ID generator. // Once the `DeterminismScope` variable is destroyed, it will return to // whatever the prior behavior was MetaSoundAsset->UpdateOrWhatever(); } void FMetaSoundAsset::UpdateOrWhatever() { // Anytime you call IDGen::Create*ID(..), it will obey whatever the outside scope set it to be. AddNewNodeOrWhatever(...) } void FMetaSoundAsset::AddNodeOrWhatever(...) { FDocumentIDGenerator& IDGen = FDocumentIDGenerator::Get(); FGuid NewNodeID = IDGen::CreateNewNodeID(); ... }
- L62 _public prototype_ `static FDocumentIDGenerator& Get();`
- L64 _public prototype_ `FGuid CreateNodeID(const FMetasoundFrontendDocument& InDocument) const;`
- L65 _public prototype_ `FGuid CreateVertexID(const FMetasoundFrontendDocument& InDocument) const;`
- L66 _public prototype_ `FGuid CreateClassID(const FMetasoundFrontendDocument& InDocument) const;`
- L68 _public prototype_ `FGuid CreateIDFromDocument(const FMetasoundFrontendDocument& InDocument) const;`
- L71 _private prototype_ `FDocumentIDGenerator() = default;`
- L74 _private prototype_ `void SetDeterminism(bool bInIsDeterministic);`
- L75 _private prototype_ `bool GetDeterminism() const;`
- L77 _private member_ `bool bIsDeterministic = false;`

#### class `Metasound::Frontend::FDocumentIDGenerator::FScopeDeterminism`  
`class FScopeDeterminism final`  
_L51-60_
- L54 _public prototype_ `FScopeDeterminism(bool bInIsDeterministic);`
- L55 _public prototype_ `bool GetDeterminism() const;`
- L56 _public prototype_ `~FScopeDeterminism();`
- L59 _private member_ `bool bOriginalValue = false;`

#### class `Metasound::Frontend::FClassIDGenerator`  
`class FClassIDGenerator`  
_L84-95_
- desc: For generating IDs that are derived from a given class vertex.  Unlike document ID generation, the class ID generator's results are not unique upon each request and therefore can deterministically generate the same ID for the same provided vertex.
- L87 _public prototype_ `static FClassIDGenerator& Get();`
- L89 _public prototype_ `FGuid CreateInputID(const FMetasoundFrontendClassInput& Input) const;`
- L90 _public prototype_ `FGuid CreateInputID(const Audio::FParameterInterface::FInput& Input) const;`
- L91 _public prototype_ `FGuid CreateOutputID(const FMetasoundFrontendClassOutput& Output) const;`
- L92 _public prototype_ `FGuid CreateOutputID(const Audio::FParameterInterface::FOutput& Output) const;`
- L94 _public prototype_ `FGuid CreateNamespacedIDFromString(const FGuid& NamespaceGuid, const FString& StringToHash) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L10 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace Frontend` (scope `Metasound`)
- L14 _externvar_ `extern int32 MetaSoundEnableCookDeterministicIDGeneration;` (scope `Metasound::Frontend`)
- L97 _prototype_ `FGuid CreateLocallyUniqueId();` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendDocumentModifyDelegates.h` (Public)


#### enum `EMetaSoundLiteralChangeType`  
`enum class EMetaSoundLiteralChangeType : uint8`  
_L27-40_
- reflection: `UENUM(BlueprintType)`
- L30 _public enumerator_ `Invalid = 0` — Initial, unset type
- L33 _public enumerator_ `Set` — Default is set
- L36 _public enumerator_ `Remove` — Default is removed for this page
- L39 _public enumerator_ `Reset` — Default is reset to default value

#### struct `Metasound::Frontend::FDocumentMutatePageArgs`  
`struct FDocumentMutatePageArgs`  
_L44-47_
- L46 _public member_ `FGuid PageID;`

#### enum `Metasound::Frontend::EDocumentTemplateChangeType`  
`enum class EDocumentTemplateChangeType : uint8`  
_L49-63_
- L52 _public enumerator_ `Invalid = 0` — Initial, unset value.
- L55 _public enumerator_ `Property` — Config property or properties were changed
- L59 _public enumerator_ `Struct` — Config struct has been completely replaced (Could now be unset/cleared)
- L62 _public enumerator_ `UndoRedo` — Transaction has been re-applied (redo) or rolled back (undo)

#### struct `Metasound::Frontend::FDocumentArrayPagedInputArgs`  
`struct FDocumentArrayPagedInputArgs`  
_L65-70_
- L67 _public member_ `int32 Index = INDEX_NONE;`
- L68 _public member_ `FGuid PageID;`
- L69 _public member_ `EMetaSoundLiteralChangeType ChangeType = EMetaSoundLiteralChangeType::Invalid;`

#### struct `Metasound::Frontend::FDocumentTemplateChangedArgs`  
`struct FDocumentTemplateChangedArgs`  
_L73-76_
- L75 _public member_ `EDocumentTemplateChangeType Type = EDocumentTemplateChangeType::Invalid;`

#### struct `Metasound::Frontend::FDocumentPresetStateChangedArgs`  
`struct FDocumentPresetStateChangedArgs`  
_L90-90_
- desc: Soft deprecated in 5.8 in favor of FOnDocumentTemplateChanged.  Once delegate is removed, it can be officially deprecated.

#### struct `Metasound::Frontend::FPageModifyDelegates`  
`struct FPageModifyDelegates`  
_L99-104_
- L101 _public member_ `FOnDocumentPageAdded OnPageAdded;`
- L102 _public member_ `FOnDocumentRemovingPage OnRemovingPage;`
- L103 _public member_ `FOnDocumentPageSet OnPageSet;`

#### struct `Metasound::Frontend::FInterfaceModifyDelegates`  
`struct FInterfaceModifyDelegates`  
_L106-140_
- L108 _public member_ `FOnMetaSoundFrontendDocumentMutateInterfaceArray OnInterfaceAdded;`
- L109 _public member_ `FOnMetaSoundFrontendDocumentMutateInterfaceArray OnRemovingInterface;`
- L111 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnInputAdded;`
- L112 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnRemovingInput;`
- L113 _public member_ `FOnMetaSoundFrontendDocumentRenameVertex OnInputNameChanged;`
- L114 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnInputDataTypeChanged;`
- L115 _public member_ `FOnMetaSoundFrontendDocumentMutateInput OnInputDefaultChanged;`
- L116 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnInputIsConstructorPinChanged;`
- L117 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnInputInheritsDefaultChanged;`
- L120 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnInputDisplayNameChanged;`
- L121 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnInputDescriptionChanged;`
- L122 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnInputSortOrderIndexChanged;`
- L123 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnInputIsAdvancedDisplayChanged;`
- L126 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnOutputAdded;`
- L127 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnRemovingOutput;`
- L128 _public member_ `FOnMetaSoundFrontendDocumentRenameVertex OnOutputNameChanged;`
- L129 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnOutputDataTypeChanged;`
- L130 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnOutputIsConstructorPinChanged;`
- L132 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnOutputDisplayNameChanged;`
- L133 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnOutputDescriptionChanged;`
- L134 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnOutputSortOrderIndexChanged;`
- L135 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnOutputIsAdvancedDisplayChanged;`
- L137 _public member_ `FOnMetaSoundFrontendDocumentMutateMember OnMemberMetadataSet;`
- L138 _public member_ `FOnMetaSoundFrontendDocumentMutateMember OnRemovingMemberMetadata;`

#### struct `Metasound::Frontend::FNodeModifyDelegates`  
`struct FNodeModifyDelegates`  
_L142-150_
- L144 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnNodeAdded;`
- L145 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnNodeConfigurationUpdated;`
- L146 _public member_ `FOnMetaSoundFrontendDocumentRemoveSwappingArray OnRemoveSwappingNode;`
- L148 _public member_ `FOnMetaSoundFrontendDocumentMutateNodeInputLiteralArray OnNodeInputLiteralSet;`
- L149 _public member_ `FOnMetaSoundFrontendDocumentMutateNodeInputLiteralArray OnRemovingNodeInputLiteral;`

#### struct `Metasound::Frontend::FEdgeModifyDelegates`  
`struct FEdgeModifyDelegates`  
_L152-156_
- L154 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnEdgeAdded;`
- L155 _public member_ `FOnMetaSoundFrontendDocumentRemoveSwappingArray OnRemoveSwappingEdge;`

#### struct `Metasound::Frontend::FGraphModifyDelegates`  
`struct FGraphModifyDelegates`  
_L158-162_
- L160 _public member_ `FEdgeModifyDelegates EdgeDelegates;`
- L161 _public member_ `FNodeModifyDelegates NodeDelegates;`

#### struct `Metasound::Frontend::FDocumentModifyDelegates`  
`struct FDocumentModifyDelegates : TSharedFromThis<FDocumentModifyDelegates>`  
_L164-208_
- inherits: `TSharedFromThis<FDocumentModifyDelegates>`
- L166 _public prototype_ `FDocumentModifyDelegates();`
- L167 _public prototype_ `FDocumentModifyDelegates(const FMetasoundFrontendDocument& Document);`
- L170 _public prototype_ `~FDocumentModifyDelegates() = default;`
- L173 _public member_ `FOnMetaSoundFrontendDocumentMutateMetadata OnDocumentMetadataChanged;`
- L174 _public member_ `FOnMetaSoundFrontendDocumentMutateArray OnDependencyAdded;`
- L175 _public member_ `FOnMetaSoundFrontendDocumentRemoveSwappingArray OnRemoveSwappingDependency;`
- L176 _public member_ `FOnMetaSoundFrontendDocumentRenameClass OnRenamingDependencyClass;`
- L179 _public member_ `FOnDocumentPresetStateChanged OnPresetStateChanged;` — Soft deprecated in 5.8: "Use OnDocumentTemplateChanged instead"
- L181 _public member_ `FOnDocumentTemplateChanged OnDocumentTemplateChanged;`
- L183 _public member_ `FPageModifyDelegates PageDelegates;`
- L184 _public member_ `FInterfaceModifyDelegates InterfaceDelegates;`
- L187 _private member_ `TSortedMap<FGuid, FGraphModifyDelegates> GraphDelegates;`
- L190 _public prototype_ `void AddPageDelegates(const FGuid& InPageID);`
- L191 _public prototype_ `void RemovePageDelegates(const FGuid& InPageID, bool bBroadcastNotify = true);`
- L194 _public prototype_ `FNodeModifyDelegates& FindNodeDelegatesChecked(const FGuid& InPageID);` — `UE_DEPRECATED(5.7, "Use FindGraphDelegatesChecked instead")`
- L197 _public prototype_ `FEdgeModifyDelegates& FindEdgeDelegatesChecked(const FGuid& InPageID);` — `UE_DEPRECATED(5.7, "Use FindGraphDelegatesChecked instead")`
- L200 _public prototype_ `void IterateGraphEdgeDelegates(TFunctionRef<void(FEdgeModifyDelegates&)> Func);` — `UE_DEPRECATED(5.7, "Use IterateGraphDelegates instead")`
- L203 _public prototype_ `void IterateGraphNodeDelegates(TFunctionRef<void(FNodeModifyDelegates&)> Func);` — `UE_DEPRECATED(5.7, "Use IterateGraphDelegates instead")`
- L205 _public prototype_ `FGraphModifyDelegates& FindGraphDelegatesChecked(const FGuid& InPageID);`
- L207 _public prototype_ `void IterateGraphDelegates(TFunctionRef<void(FGraphModifyDelegates&)> Func);`

#### class `Metasound::Frontend::IDocumentBuilderTransactionListener`  
`class IDocumentBuilderTransactionListener : public TSharedFromThis<IDocumentBuilderTransactionListener>`  
_L210-217_
- inherits: `TSharedFromThis<IDocumentBuilderTransactionListener>`
- L213 _public prototype_ `virtual ~IDocumentBuilderTransactionListener() = default;`
- L216 _public prototype_ `virtual void OnBuilderReloaded(FDocumentModifyDelegates& OutDelegates) = 0;` — Called when the builder is reloaded, at which point the document cache and delegates are refreshed

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMetaSoundFrontendDocumentMutateMetadata);` — TODO: Move these to namespace
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMetaSoundFrontendDocumentMutateMetadata);` — TODO: Move these to namespace
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMetaSoundFrontendDocumentMutateArray, int32 );`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMetaSoundFrontendDocumentMutateArray, int32 );`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMetaSoundFrontendDocumentMutateInterfaceArray, const FMetasoundFrontendInterface& );`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMetaSoundFrontendDocumentMutateInterfaceArray, const FMetasoundFrontendInterface& );`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundFrontendDocumentRemoveSwappingArray, int32 , int32 );`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundFrontendDocumentRemoveSwappingArray, int32 , int32 );`
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundFrontendDocumentRenameClass, const int32 , const FMetasoundFrontendClassName& );`
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundFrontendDocumentRenameClass, const int32 , const FMetasoundFrontendClassName& );`
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnMetaSoundFrontendDocumentMutateNodeInputLiteralArray, int32 , int32 , int32 );`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnMetaSoundFrontendDocumentMutateNodeInputLiteralArray, int32 , int32 , int32 );`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundFrontendDocumentRenameVertex, FName , FName );`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundFrontendDocumentRenameVertex, FName , FName );`
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMetaSoundFrontendDocumentMutateMember, FGuid );`
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMetaSoundFrontendDocumentMutateMember, FGuid );`
- L42 _namespace_ `namespace Metasound`
- L42 _namespace_ `namespace Frontend` (scope `Metasound`)
- L71 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMetaSoundFrontendDocumentMutateInput, const FDocumentArrayPagedInputArgs& );`
- L71 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMetaSoundFrontendDocumentMutateInput, const FDocumentArrayPagedInputArgs& );` (scope `Metasound::Frontend`)
- L78 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDocumentTemplateChanged, const FDocumentTemplateChangedArgs& );`
- L78 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDocumentTemplateChanged, const FDocumentTemplateChangedArgs& );` (scope `Metasound::Frontend`)
- L81 _typedef_ `typedef FOnDocumentTemplateChanged FOnDocumentConfigurationChanged;` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.8, "Use FOnDocumentTemplateChanged instead")`
- L84 _typedef_ `typedef EDocumentTemplateChangeType EDocumentConfigChangeType;` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.8, "Use EDocumentTemplateChangeType instead")`
- L87 _typedef_ `typedef FDocumentTemplateChangedArgs FDocumentConfigChangedArgs;` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.8, "Use FDocumentTemplateChangedArgs instead")`
- L93 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDocumentPresetStateChanged, const FDocumentPresetStateChangedArgs& );` — Soft deprecated in 5.8 as usage is no longer valid (migrated to OnDocumentTemplateChanged)
- L93 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDocumentPresetStateChanged, const FDocumentPresetStateChangedArgs& );` (scope `Metasound::Frontend`) — Soft deprecated in 5.8 as usage is no longer valid (migrated to OnDocumentTemplateChanged)
- L95 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDocumentPageAdded, const FDocumentMutatePageArgs& );`
- L95 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDocumentPageAdded, const FDocumentMutatePageArgs& );` (scope `Metasound::Frontend`)
- L96 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDocumentRemovingPage, const FDocumentMutatePageArgs& );`
- L96 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDocumentRemovingPage, const FDocumentMutatePageArgs& );` (scope `Metasound::Frontend`)
- L97 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDocumentPageSet, const FDocumentMutatePageArgs& );`
- L97 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDocumentPageSet, const FDocumentMutatePageArgs& );` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendDocumentVersioning.h` (Public)


#### class `Metasound::Frontend::FVersioningManager`  
`class FVersioningManager`  
_L32-88_
- desc: Asynchronously manages versioning of provided MetaSounds asset data. Only required for serialized assets and passed data for managing immediately upon loading in builds with editor-only data enabled.
- L35 _public prototype_ `FVersioningManager() = default;`
- L36 _public prototype_ `~FVersioningManager();`
- L38 _public prototype_ `static FVersioningManager& Get();`
- L39 _public prototype_ `static void Initialize();`
- L40 _public prototype_ `static void Shutdown();`
- L43 _public prototype_ `static FMetasoundFrontendVersionNumber GetMaxDocumentVersion();` — Current, max document version
- L49 _public prototype_ `UE_INTERNAL static FMetasoundFrontendVersionNumber GetPageMigrationVersion();` — Version where page data was migrated from a singleton graph to multiple paged graphs.  Some legacy behavior requires access to this version to initialize a builder prior to versioning document data.
- L54 _public prototype_ `UE_INTERNAL static bool ChangeIDComparisonEnabledInAutoUpdate();` — Feature to check if an ID is changed when Document Metadata is updated. Is actively being deprecated in favor of the Builder API where transaction ids are centrally tracked.
- L57 _public prototype_ `void VersionAssetAsync(UObject& InMetaSound, bool bIsDeterministic);` — Versions the given MetaSound asynchronously. Ensures provided MetaSound is a serialized asset.
- L62 _public prototype_ `bool VersionInterfaces(FMetaSoundFrontendDocumentBuilder& DocBuilder) const;` — Versions document interfaces on the given builder's object. Primarily exposed for testing purposes from other modules. Waits for all other active async versioning requests for safety (is and should not be called from versioning async task).
- L65 _public prototype_ `void WaitUntilVersioningComplete(const UObject& InMetaSound) const;` — Waits until the given MetaSound is finished asynchronously versioning.
- L69 _private prototype_ `bool VersionDocument(FMetaSoundFrontendDocumentBuilder& DocBuilder) const;` — Versions Frontend Document. Called asynchronously while versioning asset.
- L73 _private prototype_ `bool VersionInterfacesInternal(FMetaSoundFrontendDocumentBuilder& DocBuilder) const;` — Interface versioning implementation (does not guard against thread access or impose any timing restrictions as the public API call does).
- L76 _private prototype_ `void WaitUntilVersioningReferencesComplete(const UObject& InMetaSound) const;` — Waits until the given MetaSound's references finish asynchronously versioning.
- L78 _private typedef_ `using FUniqueId = uint32;`
- L80 _private member_ `mutable FCriticalSection ActiveVersionCritSection;`
- L87 _private member_ `TMap<FUniqueId, FTaskData> ActiveVersionTaskData;`

#### struct `Metasound::Frontend::FVersioningManager::FTaskData`  
`struct FTaskData`  
_L82-86_
- L84 _public member_ `TStrongObjectPtr<UObject> AssetPtr;`
- L85 _public member_ `UE::Tasks::FTask Task;`

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L27 _namespace_ `namespace Metasound`
- L27 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendGraph.h` (Public)


#### class `Metasound::FFrontendGraph`  
`class FFrontendGraph : public FGraph`  
_L28-91_
- inherits: `FGraph`
- desc: FFrontendGraph is a utility graph for use in the frontend. It can own nodes that live within the graph and provides query interfaces for finding nodes by dependency ID or input/output index.
- L32 _public prototype_ `FFrontendGraph(const FString& InInstanceName, const FGuid& InInstanceID);` — `UE_DEPRECATED(5.7, "Use constructor that provides a top-level asset path instead")`
- L39 _public prototype_ `FFrontendGraph(const FTopLevelAssetPath& InAssetPath, const FGuid& InInstanceID);` — FFrontendGraph constructor. @parma InAssetPath - Path to this graph's asset. @parma InInstanceID - ID of this graph.
- L41 _public prototype_ `virtual ~FFrontendGraph() = default;`
- L51 _public prototype_ `void AddInputNode(FGuid InNodeID, int32 InIndex, const FVertexName& InVertexName, TSharedPtr<const INode> InNode);` — `UE_DEPRECATED(5.6, "Use AddInputNode(...) version which does not take an InIndex")` — Add an input node to this graph. @param InNodeID - The NodeID related to the parent FMetasoundFrontendClass. @param InIndex - The positional index for the input. @param InVertexName - The key for the graph input vertex. @param InNode - A shared pointer to an input node.
- L64 _public prototype_ `void AddOutputNode(FGuid InNodeID, int32 InIndex, const FVertexName& InVertexName, TSharedPtr<const INode> InNode);` — `UE_DEPRECATED(5.6, "Use AddOutputNode(...) version which does not take an InIndex")` — Add an output node to this graph. @param InNodeID - The NodeID related to the parent FMetasoundFrontendClass. @param InIndex - The positional index for the output. @param InVertexName - The key for the graph output vertex. @param InNode - A shared pointer to an output node.
- L76 _public prototype_ `const INode* FindInputNode(int32 InIndex) const;` — `UE_DEPRECATED(5.6, "Retrieving input nodes nodes by index will no longer supported on this object")` — Retrieve node by input index. @param InIndex - The index of the requested input. @return Pointer to the Node if it is stored on this graph. nullptr otherwise.
- L85 _public prototype_ `const INode* FindOutputNode(int32 InIndex) const;` — `UE_DEPRECATED(5.6, "Retrieving output nodes nodes by index will no longer supported on this object")` — Retrieve node by output index. @param InIndex - The index of the requested output. @return Pointer to the Node if it is stored on this graph. nullptr otherwise.
- L89 _private member_ `TMap<int32, const INode*> InputNodes;`
- L90 _private member_ `TMap<int32, const INode*> OutputNodes;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L22 _namespace_ `namespace Metasound`
- L93 _typedef_ `using FFrontendGraphBuilder UE_DEPRECATED(5.6, "FFrontendGraphBuilder is depr` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendGraphBuilder.h` (Public)


#### class `Metasound::Frontend::FGraphBuilder`  
`class FGraphBuilder`  
_L37-144_
- desc: FGraphBuilder builds a FFrontendGraph from a FMetasoundDocument or FMetasoundFrontendClass.
- L84 _public prototype_ `static TUniquePtr<INode> CreateNode(const FCreateNodeParams& InParams);` — Create a INode from a document representation of the node. Note: This does not connect the node or place it in any graph.
- L87 _public prototype_ `static TUniquePtr<FFrontendGraph> CreateGraph(const FMetasoundFrontendDocument& InDocument, const FTopLevelAssetPath& InAssetPath, TArrayView<const FGuid> InPageOrder = { });` — Create a FFrontendGraph from a FMetasoundFrontendDocument.
- L90 _public prototype_ `static TUniquePtr<FFrontendGraph> CreateGraph( const FMetasoundFrontendDocument& InDocument, const Frontend::FProxyDataCache& InProxies, const FTopLevelAssetPath& InAssetPath, const FGuid InGraphId = Frontend::CreateLocallyUniqueId(), TArrayView<const FGuid> InPageOrder = { });` — Create a FFrontendGraph from a FMetasoundFrontendDocument retrieving proxies from a FProxyDataCache.
- L98 _public prototype_ `static TUniquePtr<FFrontendGraph> CreateGraph( const FMetasoundFrontendGraphClass& InGraph, const TArray<FMetasoundFrontendGraphClass>& InSubgraphs, const TArray<FMetasoundFrontendClass>& InDependencies, const FTopLevelAssetPath& InAssetPath, TArrayView<const FGuid> InPageOrder = { });` — Create a FFrontendGraph from a FMetasoundFrontendDocument and subobjects.
- L106 _public prototype_ `static TUniquePtr<FFrontendGraph> CreateGraph( const FMetasoundFrontendGraphClass& InGraph, const TArray<FMetasoundFrontendGraphClass>& InSubgraphs, const TArray<FMetasoundFrontendClass>& InDependencies, const Frontend::FProxyDataCache& InProxyDataCache, const FTopLevelAssetPath& InAssetPath, const FGuid InGraphId = Frontend::CreateLocallyUniqueId(), TArrayView<const FGuid> InPageOrder = { });` — Create a FFrontendGraph from a FMetasoundFrontendDocument and subobjects, retrieving proxies from a FProxyDataCache.
- L117 _public prototype_ `static TUniquePtr<FFrontendGraph> CreateGraph(const FMetasoundFrontendDocument& InDocument, const FString& InDebugAssetName, TArrayView<const FGuid> InPageOrder = { });` — `UE_DEPRECATED(5.7, "Use overload providing TopLevelAssetPath instead of DebugAssetName string")` — DEPRECATED API BELOW
- L120 _public prototype_ `static TUniquePtr<FFrontendGraph> CreateGraph( const FMetasoundFrontendDocument& InDocument, const Frontend::FProxyDataCache& InProxies, const FString& InDebugAssetName, const FGuid InGraphId = Frontend::CreateLocallyUniqueId(), TArrayView<const FGuid> InPageOrder = { });` — `UE_DEPRECATED(5.7, "Use overload providing TopLevelAssetPath instead of DebugAssetName string")`
- L128 _public prototype_ `static TUniquePtr<FFrontendGraph> CreateGraph( const FMetasoundFrontendGraphClass& InGraph, const TArray<FMetasoundFrontendGraphClass>& InSubgraphs, const TArray<FMetasoundFrontendClass>& InDependencies, const FString& InDebugAssetName, TArrayView<const FGuid> InPageOrder = { });` — `UE_DEPRECATED(5.7, "Use overload providing TopLevelAssetPath instead of DebugAssetName string")`

#### struct `Metasound::Frontend::FGraphBuilder::FCreateNodeParams`  
`struct FCreateNodeParams`  
_L41-78_
- L45 _public member_ `const FString DebugAssetName = { };` — `UE_DEPRECATED(5.7, "Deprecated in favor of AssetPath")`
- L49 _public member_ `const FMetasoundFrontendNode& FrontendNode;` — The Frontend representation of the node being created.
- L52 _public member_ `const FMetasoundFrontendClass& FrontendNodeClass;` — The Frontend Node Class representing the node.
- L55 _public member_ `const FMetasoundFrontendGraph& OwningFrontendGraph;` — The Frontend Graph which contains the Frontend Node being created.
- L58 _public member_ `const FMetasoundFrontendGraphClass& OwningFrontendGraphClass;` — The Frontend Graph Class which contains the OwningFrontendGraph.
- L62 _public member_ `const Frontend::FProxyDataCache* ProxyDataCache = nullptr;` — Optional ProxyDataCache. This is needed for creating nodes when being executed off of the game thread.
- L66 _public member_ `const Frontend::IDataTypeRegistry* DataTypeRegistry = nullptr;` — Optional DataTypeRegistry. Providing a reusable data type registry can avoid repeated lookups to gather the registry.
- L70 _public member_ `const TMap<FGuid, TSharedPtr<const IGraph>>* Subgraphs = nullptr;` — Optional subgraph map. Subgraphs are not fully supported in MetaSound so this is kept optional to avoid creation of unused TMap<>s.
- L74 _public member_ `TArrayView<const FGuid> PageOrder = { };` — An array of preferred pages where most preferred pages occur before less preferred.
- L77 _public member_ `const FTopLevelAssetPath& OwningAssetPath;` — AssetPath to graph of which the node is being added to.

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L23 _namespace_ `namespace Metasound`
- L29 _namespace_ `namespace Metasound`
- L29 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendGraphLayer.h` (Public)


#### struct `FMetasoundFrontendGraphLayer`  
`struct FMetasoundFrontendGraphLayer`  
_L16-31_
- reflection: `USTRUCT()`
- L21 _public member_ `TArray<FMetasoundFrontendClass> Dependencies;` — `UPROPERTY()`
- L24 _public member_ `FMetasoundFrontendGraph Graph;` — `UPROPERTY()`
- L27 _public member_ `TArray<FMetasoundFrontendClassInput> Inputs;` — `UPROPERTY()`
- L30 _public member_ `TArray<FMetasoundFrontendClassOutput> Outputs;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METASOUNDFRONTEND_API`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendGraphLinter.h` (Public)


#### class `Metasound::Frontend::FGraphLinter`  
`class FGraphLinter`  
_L20-41_
- L23 _public typedef_ `using FDepthFirstVisitFunction = TFunctionRef<TSet<FGuid> (const INodeController&)>;`
- L28 _public prototype_ `static bool DoesConnectionCauseLoop(const IInputController& InInputController, const IOutputController& InOutputController);` — Returns true if connecting thing input and output controllers will cause a loop in the graph. Returns false otherwise.
- L32 _public prototype_ `static bool IsReachableDownstream(const INodeController& InFromNode, const INodeController& InToNode);` — Returns true if the FromNode can reach the ToNode by traversing the graph in the forward direction.
- L37 _public prototype_ `static bool IsReachableUpstream(const INodeController& InFromNode, const INodeController& InToNode);` — Returns true if the FromNode can reach the ToNode by traversing the graph backwards (aka by traversing the transpose graph).
- L40 _public prototype_ `static void DepthFirstTraversal(const INodeController& Node, FDepthFirstVisitFunction Visit);` — Visits nodes using depth first traversals.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L11 _namespace_ `namespace Metasound`
- L13 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendLiteral.h` (Public)


#### enum `EMetasoundFrontendLiteralType`  
`enum class EMetasoundFrontendLiteralType : uint8`  
_L22-40_
- reflection: `UENUM(BlueprintType)`
- desc: The type of a given literal for an input value. The EMetasoundFrontendLiteralType's are matched to Metasound::ELiteralType`s by giving them the same value. This supports easy conversion from one type to another.
- L25 _public enumerator_ `None = static_cast<uint8>(Metasound::ELiteralType::None)` — A value of None expresses that an object being constructed with a literal should be default constructed.
- L26 _public enumerator_ `Boolean = static_cast<uint8>(Metasound::ELiteralType::Boolean)`
- L27 _public enumerator_ `Integer = static_cast<uint8>(Metasound::ELiteralType::Integer)`
- L28 _public enumerator_ `Float = static_cast<uint8>(Metasound::ELiteralType::Float)`
- L29 _public enumerator_ `String = static_cast<uint8>(Metasound::ELiteralType::String)`
- L30 _public enumerator_ `UObject = static_cast<uint8>(Metasound::ELiteralType::UObjectProxy)`
- L32 _public enumerator_ `NoneArray = static_cast<uint8>(Metasound::ELiteralType::NoneArray)` — A NoneArray expresses the number of objects to be default constructed.
- L33 _public enumerator_ `BooleanArray = static_cast<uint8>(Metasound::ELiteralType::BooleanArray)`
- L34 _public enumerator_ `IntegerArray = static_cast<uint8>(Metasound::ELiteralType::IntegerArray)`
- L35 _public enumerator_ `FloatArray = static_cast<uint8>(Metasound::ELiteralType::FloatArray)`
- L36 _public enumerator_ `StringArray = static_cast<uint8>(Metasound::ELiteralType::StringArray)`
- L37 _public enumerator_ `UObjectArray = static_cast<uint8>(Metasound::ELiteralType::UObjectProxyArray)`
- L39 _public enumerator_ `Invalid UMETA(Hidden)`

#### struct `FMetasoundFrontendLiteral`  
`struct FMetasoundFrontendLiteral`  
_L71-180_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "MetaSound Literal"))`
- desc: Represents the serialized version of variant literal types.
- L78 _public prototype_ `FMetasoundFrontendLiteral() = default;`
- L80 _public prototype_ `FMetasoundFrontendLiteral(const Metasound::FLiteral& InLiteral);`
- L82 _public prototype_ `FMetasoundFrontendLiteral(const FAudioParameter& InParameter);`
- L87 _private member_ `EMetasoundFrontendLiteralType Type = EMetasoundFrontendLiteralType::None;` — `UPROPERTY()` — The set type of this literal.
- L90 _private member_ `int32 AsNumDefault = 0;` — `UPROPERTY()`
- L93 _private member_ `TArray<bool> AsBoolean;` — `UPROPERTY()`
- L96 _private member_ `TArray<int32> AsInteger;` — `UPROPERTY()`
- L99 _private member_ `TArray<float> AsFloat;` — `UPROPERTY()`
- L102 _private member_ `TArray<FString> AsString;` — `UPROPERTY()`
- L105 _private member_ `TArray<TObjectPtr<UObject>> AsUObject;` — `UPROPERTY()`
- L109 _public prototype_ `bool IsArray() const;` — Returns true if the stored Type is an array type.
- L112 _public prototype_ `bool IsEqual(const FMetasoundFrontendLiteral& InOther) const;` — Returns whether the other literal is value equivalent
- L115 _public prototype_ `bool IsValid() const;` — Returns true if the literal is in a valid state (Type != EMetasoundFrontendLiteralType::Invalid)
- L117 _public prototype_ `bool TryGet(UObject*& OutValue) const;`
- L118 _public prototype_ `bool TryGet(TArray<UObject*>& OutValue) const;`
- L120 _public prototype_ `bool TryGet(bool& OutValue) const;`
- L121 _public prototype_ `bool TryGet(TArray<bool>& OutValue) const;`
- L122 _public prototype_ `bool TryGet(int32& OutValue) const;`
- L123 _public prototype_ `bool TryGet(TArray<int32>& OutValue) const;`
- L124 _public prototype_ `bool TryGet(float& OutValue) const;`
- L125 _public prototype_ `bool TryGet(TArray<float>& OutValue) const;`
- L126 _public prototype_ `bool TryGet(FString& OutValue) const;`
- L127 _public prototype_ `bool TryGet(TArray<FString>& OutValue) const;`
- L130 _public prototype_ `void SetType(EMetasoundFrontendLiteralType InType);` — Sets the literal to the given type and value to default;
- L132 _public prototype_ `void Set(FDefault InValue);`
- L133 _public prototype_ `void Set(FDefaultArray InValue);`
- L134 _public prototype_ `void Set(bool InValue);`
- L135 _public prototype_ `void Set(TArray<bool> InValue);`
- L136 _public prototype_ `void Set(int32 InValue);`
- L137 _public prototype_ `void Set(TArray<int32> InValue);`
- L138 _public prototype_ `void Set(float InValue);`
- L139 _public prototype_ `void Set(TArray<float> InValue);`
- L140 _public prototype_ `void Set(FString InValue);`
- L141 _public prototype_ `void Set(TArray<FString> InValue);`
- L142 _public prototype_ `void Set(UObject* InValue);`
- L143 _public prototype_ `void Set(TArray<UObject*> InValue);`
- L145 _public prototype_ `void SetFromLiteral(const Metasound::FLiteral& InLiteral);`
- L147 _public prototype_ `EMetasoundFrontendLiteralType GetType() const;`
- L150 _public prototype_ `int32 GetArrayNum() const;` — Get the number of array elements if this literal is an array type, otherwise return 0
- L159 _public prototype_ `Metasound::FLiteral ToLiteral(const FName& InMetaSoundDataType, const Metasound::Frontend::IDataTypeRegistry* InDataTypeRegistry=nullptr, const Metasound::Frontend::FProxyDataCache* InProxyDataCache=nullptr) const;` — Return a Metasound::FLiteral representation of this object. @param InMetaSoundDataType - The name of the MetaSound data type @param InDataTypeRegistry - A pointer to an existing data type registry. If null, the data type registry will be retrieved within this function. @param InProxyDataCache - A pointer to an existing proxy data cache. If not null, UObject proxies will be retrieved from the cache. If null, UObject proxies will be created in this function. @returns An FLiteral. If the data type couldn't be found, or if the literal type was incompatible with the data type, then an invalid FLiteral is returned.
- L162 _public prototype_ `Metasound::FLiteral ToLiteralNoProxy() const;` — Return a Metasound::FLiteral representation of this object, excluding UObject proxies.
- L165 _public prototype_ `FString ToString() const;` — Convert the value to a string for printing.
- L168 _public prototype_ `void Clear();` — Remove any stored data and set to an invalid state.
- L170 _public prototype_ `static FMetasoundFrontendLiteral GetInvalid();`
- L179 _private prototype_ `void Empty();` — Remove all values.

#### struct `FMetasoundFrontendLiteral::FDefault`  
`struct FDefault`  
_L75-75_

#### struct `FMetasoundFrontendLiteral::FDefaultArray`  
`struct FDefaultArray`  
_L76-76_
- L76 _public member_ `struct FDefaultArray { int32 Num = 0; };`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L60 _namespace_ `namespace Metasound`
- L62 _namespace_ `namespace Frontend` (scope `Metasound`)
- L172 _function_ `friend bool operator==(const FMetasoundFrontendLiteral& A, const FMetasoundFrontendLiteral& B)`
- L182 _namespace_ `namespace Metasound`
- L182 _namespace_ `namespace Frontend` (scope `Metasound`)
- L185 _prototype_ `EMetasoundFrontendLiteralType GetMetasoundFrontendLiteralType(ELiteralType InLiteralType);` (scope `Metasound::Frontend`) — Convenience function to convert Metasound::ELiteralType to EMetasoundFrontendLiteralType.
- L188 _prototype_ `ELiteralType GetMetasoundLiteralType(EMetasoundFrontendLiteralType InLiteralType);` (scope `Metasound::Frontend`) — Convenience function to convert EMetasoundFrontendLiteralType to Metasound::ELiteralType.
- L191 _function_ `template<typename ... ArgTypes> FMetasoundFrontendLiteral MakeFrontendLiteral(ArgTypes&& ... InArgs)` (scope `Metasound::Frontend`)
- L211 _function_ `template <typename ObjectType = UObject> FMetasoundFrontendLiteral MakeFrontendLiteral(TConstArrayView<TObjectPtr<ObjectType>> ObjectPtrs)` (scope `Metasound::Frontend`)
- L214 _function_ `auto ObjPtrToPtr = [](const TObjectPtr<ObjectType> Obj)` (scope `Metasound::Frontend::MakeFrontendLiteral`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendModuleRegistrationMacros.h` (Public)


#### struct `Metasound::Frontend::FModuleInfo`  
`struct FModuleInfo`  
_L76-82_
- desc: FModuleInfo captures information about the module which registers an item.
- L79 _public member_ `FLazyName PluginName;`
- L80 _public member_ `FLazyName ModuleName;`

#### struct `Metasound::Frontend::RegistrationPrivate::FRegistrationAction`  
`struct FRegistrationAction`  
_L90-111_
- desc: Registration actions build a linked list during static initialization.
- L92 _public prototype_ `FRegistrationAction(FRegistrationAction*& InOutHead, FRegistrationFunction InRegister, FRegistrationFunction InUnregister);`
- L97 _public function_ `template<size_t N> FRegistrationAction(FRegistrationAction*& InOutHead, FRegistrationFunction InRegister, FRegistrationFunction InUnregister, const TCHAR(&NameLiteral)[N]) : FRegistrationAction(InOutHead, InRegister, InUnregister)` — Include debug name info in editoronly_data builds.
- L104 _public member_ `FRegistrationAction* Next = nullptr;`
- L105 _public member_ `FRegistrationFunction Register = nullptr;`
- L106 _public member_ `FRegistrationFunction Unregister = nullptr;`
- L109 _public member_ `const TCHAR* Name = nullptr;` — Warning: Expected to be only used with string literals which provide static storage duration.

#### class `Metasound::Frontend::RegistrationPrivate::FRegistrationListBase`  
`class FRegistrationListBase`  
_L115-122_
- desc: FRegistrationListBase implements common functionality used by all registration list classes
- L119 _public prototype_ `static void RegisterAll(const FModuleInfo& InOwningModuleInfo, FRegistrationAction* Head);` — Calls "Register" all FRegistrationActions in the linked list beginning with the provided Head.
- L121 _public prototype_ `static void UnregisterAll(const FModuleInfo& InOwningModuleInfo, FRegistrationAction* Head);` — Calls "Unregister" all FRegistrationActions in the linked list beginning with the provided Head.

#### class `Metasound::Frontend::RegistrationPrivate::FGlobalRegistrationList`  
`class FGlobalRegistrationList`  
_L128-173_
- desc: FGlobalRegistrationList is a fallback for when the module has not defined the proper macros to create it's own registration list. This class should not be used because it cannot appropriately execute unregister actions for a single plugin or module unloading.
- L131 _public member_ `static FModuleInfo ModuleInfo;`
- L163 _public prototype_ `static FRegistrationAction*& GetHeadAction();` — `UE_DEPRECATED(5.7, "Macro based registration has been updated. See MetasoundFrontendModuleRegistrationMacros.h for a guide on defining module level registration.")`
- L169 _public prototype_ `static FRegistrationAction*& GetRegisterTailAction();` — Used internally to do incremental registration on a global list.
- L171 _public prototype_ `static void RegisterAll(const FModuleInfo& InOwningModuleInfo, FRegistrationAction* Head);`
- L172 _public prototype_ `static void UnregisterAll(const FModuleInfo& InOwningModuleInfo, FRegistrationAction* Head);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L12 _macro_ `#define METASOUND_ENABLE_PER_MODULE_REGISTRATION 1`
- L14 _macro_ `#define METASOUND_ENABLE_PER_MODULE_REGISTRATION 0`
- L73 _namespace_ `namespace Metasound`
- L73 _namespace_ `namespace Frontend` (scope `Metasound`)
- L84 _namespace_ `namespace RegistrationPrivate` (scope `Metasound::Frontend`)
- L87 _typedef_ `typedef bool (*FRegistrationFunction)(const FModuleInfo&);` (scope `Metasound::Frontend::RegistrationPrivate`) — Function signature of a registration function
- L184 _macro_ `#define METASOUND_UNREGISTER_ON_MODULE_SHUTDOWN 1` — By default, always unregister on module shutdown. The only time we do not unregister is when things cannot be associated with a module. This currently only happens when using the deprecated global registration list.
- L187 _macro_ `#define METASOUND_MODULE_REGISTRATION_LIST_CLASS UE_JOIN(F, METASOUND_PLUGIN, _, METASOUND_MODULE, _Registration)` — Module registration list class name
- L191 _macro_ `#define METASOUND_DEFINE_MODULE_REGISTRATION_LIST \` — Declare a module registration list. This needs to be visible wherever METASOUND_REGISTER_NODE is called. Generally this can be a header file within the module's Private directory.
- L209 _macro_ `#define METASOUND_MODULE_REGISTRATION_LIST_DEFINED`
- L215 _macro_ `#define METASOUND_IMPLEMENT_MODULE_REGISTRATION_LIST_INFO \`
- L227 _macro_ `#define METASOUND_IMPLEMENT_MODULE_REGISTRATION_LIST \` — Implement a module registration list. This should be placed within a CPP file.
- L257 _macro_ `#define METASOUND_MODULE_REGISTRATION_LIST_CLASS_NS ::Metasound::Frontend::RegistrationPrivate::METASOUND_MODULE_REGISTRATION_LIST_CLASS` — The registration list class including global namespace access
- L260 _macro_ `#define METASOUND_GET_HEAD_REGISTRATION_ACTION METASOUND_MODULE_REGISTRATION_LIST_CLASS_NS::GetHeadAction()` — Retrieve the head action from the registration list class
- L263 _macro_ `#define METASOUND_GET_MODULE_LIST_INFO METASOUND_MODULE_REGISTRATION_LIST_CLASS_NS::ModuleInfo` — Retrieve the module info from the registration list class
- L266 _macro_ `#define METASOUND_REGISTER_ITEMS_IN_MODULE METASOUND_MODULE_REGISTRATION_LIST_CLASS_NS::RegisterAll(METASOUND_GET_MODULE_LIST_INFO, METASOUND_GET_HEAD_REGISTRATION_ACTION);` — Register all nodes in the registration list class
- L270 _macro_ `#define METASOUND_UNREGISTER_ITEMS_IN_MODULE METASOUND_MODULE_REGISTRATION_LIST_CLASS_NS::UnregisterAll(METASOUND_GET_MODULE_LIST_INFO, METASOUND_GET_HEAD_REGISTRATION_ACTION);`
- L279 _macro_ `#define METASOUND_IMPLEMENT_REGISTRATION_ACTION(UniqueName, RegisterFunction, UnregisterFunction) static ::Metasound::Frontend::RegistrationPrivate::FRegistrationAction UE_JOIN(RegistrationAction,UniqueName)(METASOUND_GET_HEAD_REGISTRATION_` — With editoronly data includes additional debug logging info

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendNodeClassRegistry.h` (Public)


#### class `Metasound::Frontend::INodeClassRegistryEntry`  
`class INodeClassRegistryEntry`  
_L40-90_
- desc: INodeClassRegistryEntry declares the interface for a node registry entry. Each node class in the registry must satisfy this interface.
- L43 _public prototype_ `virtual ~INodeClassRegistryEntry() = default;`
- L46 _public function_ `virtual const FNodeClassInfo& GetClassInfo() const` — `UE_DEPRECATED(5.8, "NodeClassInfo is actively being deprecated. Use FNodeClassRegistryKey instead (which can be generated from the frontend class)")`
- L49 _public prototype_ `virtual TUniquePtr<INode> CreateNode(FNodeData) const = 0;` — Create a node given FNodeData.
- L52 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendClass() const = 0;` — Return a FMetasoundFrontendClass which describes the node.
- L56 _public function_ `virtual TUniquePtr<INodeClassRegistryEntry> Clone() const` — `UE_DEPRECATED(5.6, "Node Class Registration Entries do not need to be cloned.")` — Clone this registry entry.
- L62 _public prototype_ `virtual const TSet<FMetasoundFrontendVersion>* GetImplementedInterfaces() const = 0;` — Returns set of implemented interface versions. Returns nullptr if node class implementation does not support interface implementation.
- L64 _public prototype_ `virtual FVertexInterface GetDefaultVertexInterface() const = 0;`
- L68 _public prototype_ `virtual const FClassInterface& GetClassInterface() const = 0;` — Return the FClassInterface for this node class, which includes sub-interface and variant schema information.
- L72 _public function_ `virtual bool IsNative() const` — `UE_DEPRECATED(5.6, "Node class registry no longer tracks nature of implementation (i.e. if was registered " "from an asset or c++. Use the MetaSoundAssetManager to determine if the class has been defined within an asset(s).")`
- L76 _public prototype_ `virtual TInstancedStruct<FMetaSoundFrontendNodeConfiguration> CreateFrontendNodeConfiguration() const = 0;`
- L78 _public prototype_ `virtual TInstancedStruct<FMetaSoundFrontendNodeConfiguration> CreateFrontendNodeConfiguration() const;`
- L81 _public prototype_ `virtual bool IsCompatibleNodeConfiguration(TConstStructView<FMetaSoundFrontendNodeConfiguration> InNodeConfiguration) const = 0;` — Return whether this entry's node configuration is compatible with the given node configuration.
- L85 _public prototype_ `virtual FName GetPluginName() const;` — Name of the plugin registering this node.
- L88 _public prototype_ `virtual FName GetModuleName() const;` — Name of the module registering this node.

#### struct `Metasound::Frontend::FConverterNodeClassRegistryKey`  
`struct FConverterNodeClassRegistryKey`  
_L94-111_
- L97 _public member_ `FName FromDataType;` — The datatype one would like to convert from.
- L100 _public member_ `FName ToDataType;` — The datatype one would like to convert to.
- L102 _public function_ `inline bool operator==(const FConverterNodeClassRegistryKey& Other) const`

#### struct `Metasound::Frontend::FConverterNodeClassInfo`  
`struct FConverterNodeClassInfo`  
_L114-129_
- L117 _public member_ `FVertexName PreferredConverterInputPin;` — If this node has multiple input pins, we use this to designate which pin should be used.
- L120 _public member_ `FVertexName PreferredConverterOutputPin;` — If this node has multiple output pins, we use this to designate which pin should be used.
- L123 _public member_ `FNodeClassRegistryKey NodeKey;` — The key for this node in the node registry.
- L125 _public function_ `inline bool operator==(const FConverterNodeClassInfo& Other) const`

#### struct `Metasound::Frontend::FConverterNodeClassRegistryValue`  
`struct FConverterNodeClassRegistryValue`  
_L132-136_
- L135 _public member_ `TArray<FConverterNodeClassInfo> PotentialConverterNodes;` — A list of nodes that can perform a conversion between the two datatypes described in the FConverterNodeClassRegistryKey for this map element.

#### class `Metasound::Frontend::FNodeClassRegistryTransaction`  
`class FNodeClassRegistryTransaction`  
_L141-212_
- L144 _public typedef_ `using FTimeType = uint64;`
- L156 _public function_ `static FString LexToString(ETransactionType InTransactionType)`
- L196 _public prototype_ `FNodeClassRegistryTransaction(ETransactionType InType, const FNodeClassInfo& InNodeClassInfo, FTimeType InTimestamp);` — `UE_DEPRECATED(5.8, "Use constructor providing RegistryKey instead as NodeClassInfo is actively being deprecated")`
- L198 _public prototype_ `FNodeClassRegistryTransaction(ETransactionType InType, FNodeClassRegistryKey InRegistryKey, FTimeType InTimestamp);`
- L200 _public prototype_ `ETransactionType GetTransactionType() const;`
- L203 _public prototype_ `const FNodeClassInfo& GetNodeClassInfo() const;` — `UE_DEPRECATED(5.8, "NodeClassInfo is actively being deprecated. Use NodeRegistryKey instead (and SearchEngine to enquire about node class data via newer FMetaSoundClassInfo struct)")`
- L205 _public prototype_ `FNodeClassRegistryKey GetNodeRegistryKey() const;`
- L206 _public prototype_ `FTimeType GetTimestamp() const;`
- L209 _private member_ `ETransactionType Type;`
- L210 _private member_ `FNodeClassRegistryKey RegistryKey;`
- L211 _private member_ `FTimeType Timestamp;`

#### enum `Metasound::Frontend::FNodeClassRegistryTransaction::ETransactionType`  
`enum class ETransactionType : uint8`  
_L147-154_
- desc: Describes the type of transaction.
- L149 _public enumerator_ `NodeRegistration` — Something was added to the registry.
- L150 _public enumerator_ `NodeUnregistration` — Something was removed from the registry.
- L151 _public enumerator_ `NodeMigrationRegistration` — Something migrated.
- L152 _public enumerator_ `NodeMigrationUnregistration` — Module doing migration is unloaded.
- L153 _public enumerator_ `Invalid`

#### class `Metasound::Frontend::INodeClassRegistry`  
`class INodeClassRegistry`  
_L229-397_
- desc: Singleton registry for all types and nodes.
- L250 _public prototype_ `static INodeClassRegistry* Get();`
- L251 _public prototype_ `static INodeClassRegistry& GetChecked();`
- L254 _public prototype_ `static void ShutdownMetasoundFrontend();` — `UE_DEPRECATED(5.6, "This function is no longer supported")`
- L257 _public prototype_ `static bool GetFrontendClassFromRegistered(const FNodeClassRegistryKey& InKey, FMetasoundFrontendClass& OutClass);`
- L259 _public prototype_ `static bool GetInputNodeRegistryKeyForDataType(const FName& InDataTypeName, const EMetasoundFrontendVertexAccessType InAccessType, FNodeClassRegistryKey& OutKey);`
- L260 _public prototype_ `static bool GetVariableNodeRegistryKeyForDataType(const FName& InDataTypeName, FNodeClassRegistryKey& OutKey);`
- L261 _public prototype_ `static bool GetOutputNodeRegistryKeyForDataType(const FName& InDataTypeName, const EMetasoundFrontendVertexAccessType InAccessType, FNodeClassRegistryKey& OutKey);`
- L264 _protected prototype_ `INodeClassRegistry() = default;`
- L266 _public prototype_ `virtual ~INodeClassRegistry() = default;`
- L268 _public prototype_ `INodeClassRegistry(const INodeClassRegistry&) = delete;`
- L269 _public prototype_ `INodeClassRegistry& operator=(const INodeClassRegistry&) = delete;`
- L274 _public prototype_ `virtual bool EnqueueInitCommand(TUniqueFunction<void()>&& InFunc) = 0;` — `UE_DEPRECATED(5.7, "Enqueuing init commands is no longer support. See MetasoundFrontendModuleRegistrationMacros.h for information on queuing up registeration actions.")` — Enqueue and init command for registering a node or data type. The command queue will be processed on module init or when calling `RegisterPendingNodes()`
- L276 _public prototype_ `virtual void SetObjectReferencer(TUniquePtr<IObjectReferencer> InReferencer) = 0;`
- L280 _public prototype_ `virtual void RegisterPendingNodes() = 0;` — `UE_DEPRECATED(5.7, "Replace with METASOUND_REGISTER_ITEMS_IN_MODULE. See MetasoundFrontendModuleRegistrationMacros.h for more info on triggering registration of nodes and data types.")` — This is called on module startup. This invokes any registration commands enqueued by our registration macros.
- L283 _public prototype_ `virtual void WaitForAsyncGraphRegistration(const FGraphRegistryKey& InRegistryKey) const = 0;` — Wait for async graph registration to complete for a specific graph
- L288 _public prototype_ `virtual TSharedPtr<const Metasound::FGraph> GetGraph(const FGraphRegistryKey& InRegistryKey) const = 0;` — Retrieve a registered graph. If the graph is registered asynchronously, this will wait until the registration task has completed.
- L298 _public prototype_ `virtual FNodeClassRegistryKey RegisterNode(TUniquePtr<INodeClassRegistryEntry>&& InEntry) = 0;` — Register an external node with the frontend. @param InCreateNode - Function for creating node from FNodeInitData. @param InCreateDescription - Function for creating a FMetasoundFrontendClass. @return A node registration key. If the registration failed, then the registry key will be invalid.
- L306 _public prototype_ `virtual bool UnregisterNode(const FNodeClassRegistryKey& InKey) = 0;` — Unregister an external node from the frontend. @param InKey - The registration key for the node. @return True on success, false on failure.
- L310 _public prototype_ `virtual bool RegisterNodeMigration(const FNodeMigrationInfo& InMigrationInfo) = 0;` — Register a node migration from one plugin and/or module to another.
- L313 _public prototype_ `virtual bool UnregisterNodeMigration(const FNodeMigrationInfo& InMigrationInfo) = 0;` — Unregister a node migration from one plugin and/or module to another. This should be used during module shutdown.
- L316 _public prototype_ `virtual FName GetOwningPluginName(const FNodeClassRegistryKey& InKey) const = 0;` — Name of the plugin registering this node.
- L319 _public prototype_ `virtual FName GetOwningModuleName(const FNodeClassRegistryKey& InKey) const = 0;` — Name of the module registering this node.
- L323 _public prototype_ `virtual bool IsNodeRegistered(const FNodeClassRegistryKey& InKey) const = 0;` — Returns true if the provided registry key corresponds to a valid registered node.
- L326 _public prototype_ `virtual bool IsGraphRegistered(const FGraphRegistryKey& InKey) const = 0;` — Returns true if the provided registry key (node key and asset path) corresponds to a valid registered graph.
- L330 _public function_ `virtual bool IsNodeNative(const FNodeClassRegistryKey& InKey) const` — `UE_DEPRECATED(5.6, "Node class registry no longer tracks donor asset state/implementation at the interface " "level. Use the MetaSoundAssetManager to determine if the class has been defined within an asset(s).")`
- L334 _public prototype_ `virtual void IterateRegistry(FIterateMetasoundFrontendClassFunction InIterFunc, EMetasoundFrontendClassType InClassType = EMetasoundFrontendClassType::Invalid) const = 0;` — `UE_DEPRECATED(5.8, "This will be used internally only due to thread safety issues. Use Metasound::Frontend::ISearchEngine instead.")` — Iterates class types in registry.  If InClassType is set to a valid class type (optional), only iterates classes of the given type
- L340 _public prototype_ `virtual bool FindDefaultVertexInterface(const FNodeClassRegistryKey& InKey, FVertexInterface& OutVertexInterface) const = 0;` — Get the default vertex interface for the node class entry for the given key, returning true on success, false otherwise
- L344 _public prototype_ `virtual bool FindClassInterface(const FNodeClassRegistryKey& InKey, FClassInterface& OutClassInterface) const = 0;` — Get the FClassInterface (with sub-interface/variant schema) for the given key. Returns true on success, false if the key is not found.
- L346 _public prototype_ `virtual bool FindFrontendClassFromRegistered(const FNodeClassRegistryKey& InKey, FMetasoundFrontendClass& OutClass) const = 0;`
- L349 _public prototype_ `virtual bool IsCompatibleNodeConfiguration(const FNodeClassRegistryKey& InKey, TConstStructView<FMetaSoundFrontendNodeConfiguration> InNodeConfiguration) const = 0;` — Returns true if the provided node configuration is compatible (same derived class) with the registered configuration for the node represented by the registry key.
- L352 _public prototype_ `virtual TInstancedStruct<FMetaSoundFrontendNodeConfiguration> CreateFrontendNodeConfiguration(const FNodeClassRegistryKey& InKey) const = 0;` — Return the node extension associated with the node. If there is no extension associated with the node, the returned TInstancedStruct will be invalid.
- L354 _public prototype_ `virtual bool FindImplementedInterfacesFromRegistered(const FNodeClassRegistryKey& InKey, TSet<FMetasoundFrontendVersion>& OutInterfaceVersions) const = 0;`
- L356 _public prototype_ `virtual bool FindInputNodeRegistryKeyForDataType(const FName& InDataTypeName, const EMetasoundFrontendVertexAccessType InAccessType, FNodeClassRegistryKey& OutKey) = 0;`
- L357 _public prototype_ `virtual bool FindVariableNodeRegistryKeyForDataType(const FName& InDataTypeName, FNodeClassRegistryKey& OutKey) = 0;`
- L358 _public prototype_ `virtual bool FindOutputNodeRegistryKeyForDataType(const FName& InDataTypeName, const EMetasoundFrontendVertexAccessType InAccessType, FNodeClassRegistryKey& OutKey) = 0;`
- L364 _public prototype_ `virtual TUniquePtr<Metasound::INode> CreateNode(const FNodeClassRegistryKey& InKey, Metasound::FNodeData) const = 0;` — Create a MetaSound Node with the given registration key and Node Data Returns an invalid TUniquePtr<> if the key is not in the registry.
- L372 _public prototype_ `virtual bool RegisterConversionNode(const FConverterNodeClassRegistryKey& InConversionKey, const FConverterNodeClassInfo& InNodeInfo) = 0;` — Registers a node as a converter node
- L375 _public prototype_ `virtual bool UnregisterConversionNode(const FConverterNodeClassRegistryKey& InConversionKey, const FNodeClassRegistryKey& InNodeKey) = 0;` — Unregisters a node as a converter node
- L379 _public prototype_ `virtual TArray<FConverterNodeClassInfo> GetPossibleConverterNodes(const FName& FromDataType, const FName& ToDataType) = 0;` — Returns a list of possible nodes to use to convert from FromDataType to ToDataType. Returns an empty array if none are available.
- L387 _public prototype_ `virtual void RegisterCustomNodeUpdateTransform(const FMetasoundFrontendClassName& ClassName, int32 MajorVersion, const TSharedRef<const FBaseNodeUpdateTransform>& InTransform) = 0;` — Node Update Transforms Register a node update transform associated with a registered node class and major version. Autoapplied node update transforms will be applied after all minor version updates for the node's major version have been applied during autoupdate

#### class `Metasound::Frontend::INodeClassRegistry::IObjectReferencer`  
`class IObjectReferencer`  
_L237-247_
- desc: The MetaSound frontend does not rely on the Engine module and therefore does not have the ability to provide GC protection. This interface allows external modules to provide GC protection so that async tasks can safely use UObjects
- L240 _public prototype_ `virtual ~IObjectReferencer() = default;`
- L243 _public prototype_ `virtual void AddObject(UObject* InObject) = 0;` — Called when an object should be referenced.
- L246 _public prototype_ `virtual void RemoveObject(UObject* InObject) = 0;` — Called when an object no longer needs to be referenced.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L15 _macro_ `#define UE_METASOUND_PURE_VIRTUAL_CREATE_FRONTEND_NODE_EXTENSION (0)`
- L21 _namespace_ `namespace Metasound`
- L24 _namespace_ `namespace Frontend` (scope `Metasound`)
- L26 _typedef_ `using FIterateMetasoundFrontendClassFunction = TFunctionRef<void(const FMetasoundFrontendClass&)>;` (scope `Metasound::Frontend`)
- L30 _typedef_ `using FIterateMetasoundFrontendClassFunction UE_DEPRECATED(5.6, "Use TIterateMetasoundFrontendClassFunction defined in` (scope `Metasound`)
- L35 _namespace_ `namespace Metasound`
- L35 _namespace_ `namespace Frontend` (scope `Metasound`)
- L92 _typedef_ `using INodeRegistryEntry UE_DEPRECATED(5.6, "Use INodeClassRegistryEntry i` (scope `Metasound::Frontend`)
- L107 _function_ `friend uint32 GetTypeHash(const FConverterNodeClassRegistryKey& InKey)` (scope `Metasound::Frontend`)
- L112 _typedef_ `using FConverterNodeRegistryKey = FConverterNodeClassRegistryKey;` (scope `Metasound::Frontend`)
- L130 _typedef_ `using FConverterNodeInfo = FConverterNodeClassInfo;` (scope `Metasound::Frontend`)
- L137 _typedef_ `using FConverterNodeClassRegistryValue = FConverterNodeClassRegistryValue;` (scope `Metasound::Frontend`)
- L139 _typedef_ `using FRegistryTransactionID = int32;` (scope `Metasound::Frontend`)
- L214 _typedef_ `using FNodeRegistryTransaction UE_DEPRECATED(5.8, "FNodeRegistryTransaction is now FNo` (scope `Metasound::Frontend`)
- L216 _namespace_ `namespace NodeClassRegistryKey` (scope `Metasound::Frontend`)
- L219 _prototype_ `bool IsEqual(const FMetasoundFrontendClassMetadata& InLHS, const FMetasoundFrontendClassMetadata& InRHS);` (scope `Metasound::Frontend::NodeClassRegistryKey`) — Returns true if the class metadata represent the same entry in the node registry.
- L222 _prototype_ `bool IsEqual(const FNodeClassInfo& InLHS, const FMetasoundFrontendClassMetadata& InRHS);` (scope `Metasound::Frontend::NodeClassRegistryKey`) — Returns true if the class info and class metadata represent the same entry in the node registry.

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendNodeMigration.h` (Public)


#### struct `Metasound::Frontend::FNodeMigrationInfo`  
`struct FNodeMigrationInfo`  
_L12-36_
- L15 _public member_ `FName UEVersion;` — UE Version when migration occurred (e.g. "5.6")
- L18 _public member_ `FNodeClassName ClassName;` — ClassName of node which was migrated
- L21 _public member_ `int32 MajorVersion = -1;` — Major version of node when migration happened
- L24 _public member_ `int32 MinorVersion = -1;` — Minor version of node when migration happened
- L27 _public member_ `FName FromPlugin;` — Prior plugin and module where node was registered.
- L28 _public member_ `FName FromModule;`
- L31 _public member_ `FName ToPlugin;` — New plugin and module where node is registered.
- L32 _public member_ `FName ToModule;`
- L34 _public prototype_ `FString ToString() const;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L9 _namespace_ `namespace Metasound`
- L9 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendNodeTemplateRegistry.h` (Public)


#### struct `FNodeTemplateGenerateInterfaceParams`  
`struct FNodeTemplateGenerateInterfaceParams`  
_L30-42_
- reflection: `USTRUCT()`
- L38 _public member_ `TArray<FName> InputsToConnect;` — `UPROPERTY()` — TODO: Currently just DataType FName. Subsequent change will replace this with a VertexHandle and will add builder reference to once builder supports template nodes and controllers are no longer used to add template nodes from editor code.
- L41 _public member_ `TArray<FName> OutputsToConnect;` — `UPROPERTY()`

#### struct `Metasound::Frontend::FTemplateNodeTransactionContext`  
`struct FTemplateNodeTransactionContext`  
_L55-65_
- L58 _public member_ `const FMetaSoundFrontendDocumentBuilder& Builder;` — Builder executing the transaction
- L61 _public member_ `const FGuid& PageID;` — PageID of node being acted on
- L64 _public member_ `const FMetasoundFrontendNode* Node = nullptr;` — Node being transacted on

#### struct `Metasound::Frontend::FTemplateNodeEdgeTransactionContext`  
`struct FTemplateNodeEdgeTransactionContext`  
_L67-86_
- L70 _public member_ `const FMetaSoundFrontendDocumentBuilder& Builder;` — Builder executing the transaction
- L73 _public member_ `const FGuid& PageID;` — PageID of node being acted on
- L76 _public member_ `const FMetasoundFrontendNode* FromNode = nullptr;` — From node being transacted on
- L79 _public member_ `const FMetasoundFrontendVertex* FromOutput = nullptr;` — Node Output being transacted on
- L82 _public member_ `const FMetasoundFrontendNode* ToNode = nullptr;` — To Node being transacted on
- L85 _public member_ `const FMetasoundFrontendVertex* ToInput = nullptr;` — Node Input being transacted on

#### struct `Metasound::Frontend::FTemplateNodeEdgeRemoveTransactionContext`  
`struct FTemplateNodeEdgeRemoveTransactionContext : public FTemplateNodeEdgeTransactionContext`  
_L93-104_
- inherits: `FTemplateNodeEdgeTransactionContext`
- desc: Removal requires re-instating an input default, which must be selected based on page context.  Selection of page context is engine-level behavior.  Thus, a function ref is provided for default selection should the node template be providing a graph topology reduction that requires look-up of a separate node's input on intercepting the given edge removal transaction.
- L95 _public typedef_ `using FResolveActiveInputDefaultFunctionRef = TFunctionRef<const FMetasoundFrontendLiteral*( const FGuid& , const FName )>;`
- L103 _public member_ `const FResolveActiveInputDefaultFunctionRef ResolveActiveNodeInputDefault;` — Reference to function used to determine preferred page input default for a given node's vertex. If default is set directly on paged node, uses that value. Otherwise, uses the default provided by the node's class interface.

#### class `Metasound::Frontend::INodeTemplateTransform`  
`class INodeTemplateTransform`  
_L107-114_
- L110 _public prototype_ `virtual ~INodeTemplateTransform() = default;`
- L113 _public prototype_ `virtual bool Transform(const FGuid& InPageID, const FGuid& InNodeID, FMetaSoundFrontendDocumentBuilder& OutBuilder) const = 0;` — Return true if the builder was modified, false otherwise.

#### class `Metasound::Frontend::INodeTemplate`  
`class INodeTemplate`  
_L121-208_
- desc: Base interface for a node template, which acts in place of frontend node class and respective instance(s). Instances are preprocessed, allowing for custom graph manipulation prior to generating a respective runtime graph operator representation.
- L124 _public prototype_ `virtual FMetasoundFrontendNodeInterface GenerateNodeInterface(FNodeTemplateGenerateInterfaceParams InParams) const = 0;`
- L126 _public prototype_ `virtual ~INodeTemplate() = default;`
- L128 _public prototype_ `virtual const TArray<FMetasoundFrontendClassInputDefault>* FindNodeClassInputDefaults( const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, FName VertexName) const = 0;`
- L135 _public prototype_ `virtual const FMetasoundFrontendClassName& GetClassName() const = 0;` — Returns note template class name.
- L138 _public prototype_ `virtual TInstancedStruct<FMetaSoundFrontendTemplateNodeConfiguration> CreateFrontendTemplateNodeConfiguration() const = 0;` — Create a node configuration for the node template.
- L141 _public prototype_ `virtual FText GetNodeDisplayName(const IMetaSoundDocumentInterface& Interface, const FGuid& InPageID, const FGuid& InNodeID) const = 0;`
- L143 _public prototype_ `virtual FText GetInputVertexDisplayName(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, FName InputName) const = 0;`
- L145 _public prototype_ `virtual FText GetOutputVertexDisplayName(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, FName OutputName) const = 0;`
- L147 _public prototype_ `static FText ResolveMemberDisplayName(FName VertexName, FText DisplayName, bool bIncludeNamespace);`
- L151 _public prototype_ `virtual TUniquePtr<INodeTemplateTransform> GenerateNodeTransform() const = 0;` — Generates node transform that is used to preprocess nodes.
- L154 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendClass() const = 0;` — Returns the class definition for the given node class template.
- L157 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetNodeInputAccessType(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, const FGuid& InVertexID) const = 0;` — Returns access type of the given input within the provided builder's document
- L160 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetNodeOutputAccessType(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, const FGuid& InVertexID) const = 0;` — Returns access type of the given output within the provided builder's document
- L163 _public prototype_ `virtual const FMetasoundFrontendVersionNumber& GetVersionNumber() const = 0;` — Returns note template class version.
- L168 _public prototype_ `virtual bool HasRequiredConnections(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, FString* OutMessage = nullptr) const = 0;` — Returns whether or not the given node template has the necessary required connections to be preprocessed (editor only).
- L172 _public prototype_ `virtual bool IsInputAccessTypeDynamic() const = 0;` — Returns whether template can dynamically assign a node's input access type (as opposed to it being assigned on the class input definition)
- L175 _public prototype_ `virtual bool IsInputConnectionUserModifiable() const = 0;` — Whether or not input connections are user modifiable
- L178 _public prototype_ `virtual bool IsOutputAccessTypeDynamic() const = 0;` — Returns whether template can dynamically assign a node's output's access type (as opposed to it being assigned on the class output definition)
- L181 _public prototype_ `virtual bool IsOutputConnectionUserModifiable() const = 0;` — Whether or not output connections are user modifiable
- L185 _public prototype_ `virtual bool IsValidNodeInterface(const FMetasoundFrontendNodeInterface& InNodeInterface) const = 0;` — Given the provided node interface, returns whether or not it conforms to an expected format that can be successfully manipulated by a generated node template transform.
- L190 _public prototype_ `virtual bool OnEdgeAdded(const FTemplateNodeEdgeTransactionContext& TransactionContext, DynamicGraph::FDynamicOperatorTransactor& OutTransactor) const = 0;` — Provided a Frontend transaction context, apply adding edge transaction to the given dynamic core transactor. Returns whether or not Frontend operation was handled and applied to the given transactor.
- L194 _public prototype_ `virtual bool OnNodeAdded(const FTemplateNodeTransactionContext& TransactionContext, DynamicGraph::FDynamicOperatorTransactor& OutTransactor) const = 0;` — Provided a Frontend transaction context, apply adding node transaction to the given dynamic core transactor. Returns whether or not Frontend operation was handled and applied to the given transactor.
- L198 _public prototype_ `virtual bool OnNodeConfigurationUpdated(const FTemplateNodeTransactionContext& TransactionContext, DynamicGraph::FDynamicOperatorTransactor& OutTransactor) const = 0;` — Provided a Frontend transaction context, apply updating node config transaction to the given dynamic core transactor. Returns whether or not Frontend operation was handled and applied to the given transactor.
- L202 _public prototype_ `virtual bool OnRemoveSwappingEdge(const FTemplateNodeEdgeRemoveTransactionContext& TransactionContext, DynamicGraph::FDynamicOperatorTransactor& OutTransactor) const = 0;` — Provided a Frontend transaction context, apply removing edge transaction to the given dynamic core transactor. Returns whether or not Frontend operation was handled and applied to the given transactor.
- L206 _public prototype_ `virtual bool OnRemoveSwappingNode(const FTemplateNodeTransactionContext& TransactionContext, DynamicGraph::FDynamicOperatorTransactor& OutTransactor) const = 0;` — Provided a Frontend transaction context, apply removing node transaction to the given dynamic core transactor. Returns whether or not Frontend operation was handled and applied to the given transactor.

#### class `Metasound::Frontend::INodeTemplateRegistry`  
`class INodeTemplateRegistry`  
_L210-223_
- L214 _public prototype_ `static INodeTemplateRegistry& Get();` — Returns singleton template registry.
- L216 _public prototype_ `virtual ~INodeTemplateRegistry() = default;`
- L219 _public prototype_ `virtual const INodeTemplate* FindTemplate(const FNodeRegistryKey& InKey) const = 0;` — Find a template with the given key. Returns null if entry not found with given key.
- L222 _public prototype_ `virtual const INodeTemplate* FindTemplate(const FMetasoundFrontendClassName& InClassName) const = 0;` — Find a template with the given class name with the highest version. Returns null if entry not found with given name.

#### class `Metasound::Frontend::FNodeTemplateBase`  
`class FNodeTemplateBase : public INodeTemplate`  
_L225-243_
- inherits: `INodeTemplate`
- L228 _public prototype_ `virtual const TArray<FMetasoundFrontendClassInputDefault>* FindNodeClassInputDefaults(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, FName VertexName) const override;`
- L229 _public prototype_ `virtual TInstancedStruct<FMetaSoundFrontendTemplateNodeConfiguration> CreateFrontendTemplateNodeConfiguration() const override;`
- L232 _public prototype_ `virtual FText GetNodeDisplayName(const IMetaSoundDocumentInterface& Interface, const FGuid& InPageID, const FGuid& InNodeID) const override;`
- L233 _public prototype_ `virtual FText GetInputVertexDisplayName(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, FName InputName) const override;`
- L234 _public prototype_ `virtual FText GetOutputVertexDisplayName(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, FName OutputName) const override;`
- L235 _public prototype_ `virtual bool HasRequiredConnections(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, FString* OutMessage = nullptr) const override;`
- L237 _public prototype_ `virtual bool OnEdgeAdded(const FTemplateNodeEdgeTransactionContext& TransactionContext, DynamicGraph::FDynamicOperatorTransactor& OutTransactor) const override;`
- L238 _public prototype_ `virtual bool OnNodeAdded(const FTemplateNodeTransactionContext& TransactionContext, DynamicGraph::FDynamicOperatorTransactor& OutTransactor) const override;`
- L239 _public prototype_ `virtual bool OnNodeConfigurationUpdated(const FTemplateNodeTransactionContext& TransactionContext, DynamicGraph::FDynamicOperatorTransactor& OutTransactor) const override;`
- L240 _public prototype_ `virtual bool OnRemoveSwappingEdge(const FTemplateNodeEdgeRemoveTransactionContext& TransactionContext, DynamicGraph::FDynamicOperatorTransactor& OutTransactor) const override;`
- L241 _public prototype_ `virtual bool OnRemoveSwappingNode(const FTemplateNodeTransactionContext& TransactionContext, DynamicGraph::FDynamicOperatorTransactor& OutTransactor) const override;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L20 _namespace_ `namespace Metasound`
- L22 _namespace_ `namespace DynamicGraph` (scope `Metasound`)
- L44 _namespace_ `namespace Metasound`
- L44 _namespace_ `namespace Frontend` (scope `Metasound`)
- L53 _typedef_ `using FConstNodeHandle = TSharedRef<const INodeController>;` (scope `Metasound::Frontend`)
- L248 _prototype_ `void RegisterNodeTemplate(TUniquePtr<INodeTemplate>&& InTemplate);` (scope `Metasound::Frontend`) — Register/UnregisterNodeTemplate are limited to internal implementation to avoid document corruption. Node Config is likely the better option for most class interface "switching" applications (templates are reserved for cook-only applications/optimizations with more advanced node instance interface manipulation).
- L249 _prototype_ `void UnregisterNodeTemplate(const FMetasoundFrontendClassName& InClassName, const FMetasoundFrontendVersionNumber& InTemplateVersion);` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendNodeUpdateTransform.h` (Public)


#### struct `Metasound::Frontend::NodeReplacement::FInputConnectionInfo`  
`struct UE_EXPERIMENTAL(5.8, "Node update transforms are experimental") FInputConnectionInfo`  
_L17-26_
- L20 _public member_ `FMetasoundFrontendVertexHandle ConnectedOutput;` — Handle of connected output vertex
- L22 _public member_ `FName Name;` — Name and data type of node input vertex
- L23 _public member_ `FName DataType;`
- L24 _public member_ `FMetasoundFrontendLiteral DefaultValue;`
- L25 _public member_ `bool bLiteralSet = false;`

#### struct `Metasound::Frontend::NodeReplacement::FOutputConnectionInfo`  
`struct UE_EXPERIMENTAL(5.8, "Node update transforms are experimental") FOutputConnectionInfo`  
_L28-35_
- L31 _public member_ `TArray<FMetasoundFrontendVertexHandle> ConnectedInputs;` — Handles of connected input vertices
- L33 _public member_ `FName Name;` — Name and data type of node output vertex
- L34 _public member_ `FName DataType;`

#### struct `Metasound::Frontend::NodeReplacement::FNodeInstanceReplacementData`  
`struct UE_EXPERIMENTAL(5.8, "Node update transforms are experimental") FNodeInstanceReplacementData`  
_L42-53_
- L45 _public member_ `FMetasoundFrontendNodeStyle Style;`
- L48 _public member_ `TInstancedStruct<FMetaSoundFrontendNodeConfiguration> Configuration;`
- L49 _public member_ `TInstancedStruct<FMetasoundFrontendClassInterface> ClassInterfaceOverride;`
- L51 _public member_ `FInputConnections InputConnections;`
- L52 _public member_ `FOutputConnections OutputConnections;`

#### struct `Metasound::Frontend::FNodeUpdateTransformData`  
`struct UE_EXPERIMENTAL(5.8, "Node update transforms are experimental") FNodeUpdateTransformData`  
_L58-61_
- desc: Cached data for performing a node update (ex. old node connections that need to be reapplied after replacing it)
- L60 _public member_ `NodeReplacement::FNodeInstanceReplacementData NodeReplacementData;`

#### class `Metasound::Frontend::INodeUpdateTransform`  
`class UE_EXPERIMENTAL(5.7, "Node update transforms are experimental") INodeUpdateTransform`  
_L63-80_
- L67 _public prototype_ `virtual ~INodeUpdateTransform() = default;`
- L71 _public prototype_ `virtual FNodeClassRegistryKey GetNewNodeClassKey() const = 0;` — The node class registry key of the new node that the old node will be transformed into Node update transforms are many to 1 or 1 to 1 node replacements
- L74 _public prototype_ `virtual bool ShouldAutoApply() const = 0;` — Whether the transform should be automatically applied to node class keys registered with this transform during autoupdate
- L78 _public prototype_ `UE_INTERNAL virtual void Update(FMetaSoundFrontendDocumentBuilder& InOutBuilder, const FGuid InNodeID, const FGuid* InPageID = nullptr) const = 0;` — Perform the internal node replacement update on a given node Not exposed directly to users, see subclasses for the data that users can customize

#### class `Metasound::Frontend::FBaseNodeUpdateTransform`  
`class UE_EXPERIMENTAL(5.8, "Node update transforms are experimental") FBaseNodeUpdateTransform : public INodeUpdateTransform`  
_L84-103_
- inherits: `INodeUpdateTransform`
- desc: Base update transform that replaces a node with another node of the given target node class key, maintaining connections and data if possible. Inherit from this to make a custom node update transform.
- L88 _public prototype_ `FBaseNodeUpdateTransform(const FNodeClassRegistryKey& InNewNodeClassKey);`
- L90 _public prototype_ `virtual FNodeClassRegistryKey GetNewNodeClassKey() const override;`
- L92 _public prototype_ `virtual bool ShouldAutoApply() const override;`
- L94 _public prototype_ `UE_INTERNAL virtual void Update(FMetaSoundFrontendDocumentBuilder& InOutBuilder, const FGuid InNodeID, const FGuid* InPageID) const final override;`
- L98 _public prototype_ `virtual FNodeUpdateTransformData CreateNodeUpdateTransformData(const FMetaSoundFrontendDocumentBuilder& InOutBuilder, const FGuid& InNodeID, const FGuid* InPageID) const;` — Data (ex. connections, defaults, node configuration) to be reapplied to the new node after it has been updated This represents the data we want applied to the new node (ex. new node configuration), which is not necessarily just what we currently have (though in simplest case those are the same)
- L101 _private member_ `FNodeClassRegistryKey NewNodeClassKey;`

#### class `Metasound::Frontend::FMaintainDefaultsNodeUpdateTransform`  
`class UE_EXPERIMENTAL(5.8, "Node update transforms are experimental") FMaintainDefaultsNodeUpdateTransform : public FBaseNodeUpdateTransform`  
_L110-119_
- inherits: `FBaseNodeUpdateTransform`
- desc: An example node update transform for maintaining a node's specified default values, when the next version has a new default value and would otherwise stomp currently unoverwritten values. If a user has overwritten the value, it will stay as that overwritten value. Ex. A filter bandwidth default is changed in v2.0, so use this transform to keep old content at the v1.0 default if the default was not set on the individual nodes, while new content will use the new v2.0 default
- L114 _public prototype_ `FMaintainDefaultsNodeUpdateTransform(const FNodeClassRegistryKey& InTargetNodeClassKey);`
- L116 _public prototype_ `virtual FNodeUpdateTransformData CreateNodeUpdateTransformData(const FMetaSoundFrontendDocumentBuilder& InOutBuilder, const FGuid& InNodeID, const FGuid* InPageID) const override;`
- L117 _public prototype_ `virtual bool ShouldAutoApply() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L12 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace Frontend` (scope `Metasound`)
- L14 _typedef_ `using FVertexNameAndType = TTuple<FName, FName>;` (scope `Metasound::Frontend`)
- L15 _namespace_ `namespace NodeReplacement` (scope `Metasound::Frontend`)
- L38 _typedef_ `using FInputConnections = TMap<FVertexNameAndType, FInputConnectionInfo>;` (scope `Metasound::Frontend::NodeReplacement`) — Map of input name/type to input info
- L40 _typedef_ `using FOutputConnections = TMap<FVertexNameAndType, FOutputConnectionInfo>;` (scope `Metasound::Frontend::NodeReplacement`) — Map of output name/type to connected inputs

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendNodesCategories.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Metasound`
- L9 _namespace_ `namespace NodeCategories` (scope `Metasound`)
- L11 _externvar_ `extern const FText Conversions;` (scope `Metasound::NodeCategories`)
- L12 _externvar_ `extern const FText EnumConversions;` (scope `Metasound::NodeCategories`)
- L13 _externvar_ `extern const FText Functions;` (scope `Metasound::NodeCategories`)
- L14 _externvar_ `extern const FText Graphs;` (scope `Metasound::NodeCategories`)
- L15 _externvar_ `extern const FText Inputs;` (scope `Metasound::NodeCategories`)
- L16 _externvar_ `extern const FText Outputs;` (scope `Metasound::NodeCategories`)
- L17 _externvar_ `extern const FText Variables;` (scope `Metasound::NodeCategories`)
- L18 _externvar_ `extern const FText Favorites;` (scope `Metasound::NodeCategories`)
- L19 _externvar_ `extern const FText Recents;` (scope `Metasound::NodeCategories`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendPages.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L14 _namespace_ `namespace Metasound`
- L14 _namespace_ `namespace Frontend` (scope `Metasound`)
- L21 _prototype_ `bool StripUnusedPages(FMetaSoundFrontendDocumentBuilder& InBuilder, TArrayView<const FGuid> InTargetPages, TArrayView<const FGuid> InPageOrder);` (scope `Metasound::Frontend`) — Remove page data which will not be use given the supplied target pages and page order. @return true if the builder removed any pages.
- L32 _function_ `template<typename ElementType> const ElementType* FindPreferredPage(const TArray<ElementType>& InElements, TArrayView<const FGuid> InPageOrder)` (scope `Metasound::Frontend`) — Return a pointer to the most preferred element for a given page order. PageIDs with lower indices in InPageOrder are preferred over those with higher indices. If none of the elements have a PageID which exists in the InPageOrder, then a pointer to the first element is returned. If the InElements array is empty, then nullptr is returned.

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendQuery.h` (Public)


#### struct `FMetaSoundClassVertexInfo`  
`struct FMetaSoundClassVertexInfo`  
_L66-78_
- reflection: `USTRUCT(BlueprintType)`
- desc: Condensed set of class vertex data that is serialized to editor-only asset tag data, allowing editor scripts and code to query MetaSounds without loading them in entirety.
- L71 _public member_ `FName Name;` — `UPROPERTY(BlueprintReadOnly, Category = ClassInfo)`
- L74 _public member_ `FName TypeName;` — `UPROPERTY(BlueprintReadOnly, Category = ClassInfo)`
- L77 _public member_ `EMetasoundFrontendVertexAccessType AccessType = EMetasoundFrontendVertexAccessType::Unset;` — `UPROPERTY(BlueprintReadOnly, Category = ClassInfo)`

#### struct `FMetaSoundClassSearchInfo`  
`struct FMetaSoundClassSearchInfo`  
_L84-104_
- reflection: `USTRUCT(BlueprintType)`
- desc: Condensed set of class metadata that is serialized to editor-only asset tag data, allowing editor scripts and code to search and display MetaSounds without loading in asset selection contexts without loading them in entirety.
- L88 _public prototype_ `FMetaSoundClassSearchInfo() = default;`
- L89 _public prototype_ `FMetaSoundClassSearchInfo(const FMetasoundFrontendClassMetadata& InClassMetadata);`
- L94 _public member_ `FText ClassDisplayName;` — `UPROPERTY(BlueprintReadOnly, Category = ClassInfo)` — Human readable DisplayName of Class (optional, overrides the package name in the editor if specified by MetaSound Asset Author).
- L97 _public member_ `FText ClassDescription;` — `UPROPERTY(BlueprintReadOnly, Category = ClassInfo)`
- L100 _public member_ `TArray<FText> Hierarchy;` — `UPROPERTY(BlueprintReadOnly, Category = ClassInfo)`
- L103 _public member_ `TArray<FText> Keywords;` — `UPROPERTY(BlueprintReadOnly, Category = ClassInfo)`

#### struct `FMetaSoundClassVertexCollectionInfo`  
`struct FMetaSoundClassVertexCollectionInfo`  
_L110-116_
- reflection: `USTRUCT(BlueprintType)`
- desc: Condensed set of vertex data that is serialized to editor-only asset tag data, allowing editor scripts and code to query MetaSounds without loading them in entirety.
- L115 _public member_ `TArray<FMetaSoundClassVertexInfo> ClassVertexInfo;` — `UPROPERTY(BlueprintReadOnly, Category = ClassInfo)`

#### struct `FMetaSoundClassInterfaceInfo`  
`struct FMetaSoundClassInterfaceInfo`  
_L122-154_
- reflection: `USTRUCT(BlueprintType, DisplayName = "MetaSound Class Interface Info")`
- desc: Condensed set of class data that is serialized to editor-only asset tag data, allowing editor scripts and code to query MetaSounds without loading them in entirety.
- L126 _public prototype_ `FMetaSoundClassInterfaceInfo() = default;`
- L127 _public prototype_ `FMetaSoundClassInterfaceInfo(const IMetaSoundDocumentInterface& InDocInterface);`
- L128 _public prototype_ `FMetaSoundClassInterfaceInfo(const FMetasoundFrontendClass& InClass);`
- L129 _public prototype_ `FMetaSoundClassInterfaceInfo(const FAssetData& InAssetData, bool& bOutIsValid);`
- L131 _public prototype_ `void ExportToContext(FAssetRegistryTagsContext& OutContext) const;`
- L135 _public member_ `TArray<FMetasoundFrontendInterfaceMetadata> DefinedInterfaces;` — `UPROPERTY(BlueprintReadOnly, Category = ClassInfo)` — Interfaces metadata associated with interfaces defined by this class.
- L139 _public member_ `FMetaSoundClassSearchInfo SearchInfo;` — `UPROPERTY(BlueprintReadOnly, Category = ClassInfo)` — Editor-only search info
- L144 _public member_ `TArray<FMetaSoundClassVertexInfo> Inputs;` — `UPROPERTY(BlueprintReadOnly, Category = ClassInfo)` — Collection of identifiable input vertex data cached in query for fast access & serializability (ex. in asset tags)
- L149 _public member_ `TArray<FMetaSoundClassVertexInfo> Outputs;` — `UPROPERTY(BlueprintReadOnly, Category = ClassInfo)` — Collection of identifiable output vertex data cached in query for fast access & serializability (ex. in asset tags)
- L153 _public member_ `TArray<FMetasoundFrontendVersion> InheritedInterfaces;` — `UPROPERTY(BlueprintReadOnly, Category = ClassInfo)` — Interfaces metadata associated with a given class definition.

#### struct `Metasound::Frontend::FMetaSoundClassInfo`  
`struct FMetaSoundClassInfo`  
_L164-212_
- desc: Class query info accessible in the Search Engine.  Represents class info for a given class that may or may not be loaded and/or registered (ex. in editor, class info may be supplied by asset registry tags or class info could be provided by a cloud service, enabling class browsing without a local asset required to be loaded or registered with the node class registry).
- L166 _public prototype_ `FMetaSoundClassInfo(EMetasoundFrontendClassType InClassType = EMetasoundFrontendClassType::Invalid);`
- L167 _public prototype_ `FMetaSoundClassInfo(const FMetasoundFrontendClass& InClass);`
- L168 _public prototype_ `FMetaSoundClassInfo(const FAssetData& InAssetData);`
- L170 _public prototype_ `virtual ~FMetaSoundClassInfo() = default;`
- L173 _public prototype_ `virtual void ExportToContext(FAssetRegistryTagsContext& OutContext) const;` — Exports class query info as tag data to the given RegistryContext
- L178 _public prototype_ `static bool TryGetClassVersion(const FAssetData& InAssetData, FMetasoundFrontendVersionNumber& OutKey);` — If asset is loaded, retrieves version number from loaded data. Otherwise, parses just the tag data necessary to get the given asset's version number. Does not attempt to load asset, and will fail if data is not found and asset isn't loaded.
- L181 _protected prototype_ `virtual void InitFromDocument(const IMetaSoundDocumentInterface& InDocInterface);`
- L185 _public member_ `FMetasoundFrontendClassName ClassName;` — ClassName of class
- L187 _public member_ `EMetasoundFrontendClassType ClassType = EMetasoundFrontendClassType::Invalid;`
- L190 _public member_ `FMetasoundFrontendVersionNumber Version;` — Version of class
- L193 _public member_ `FMetaSoundClassInterfaceInfo InterfaceInfo;`
- L195 _public prototype_ `bool InheritsInterface(FName InterfaceName, const FMetasoundFrontendVersionNumber& VersionNumber = { 0, 0 }) const;`
- L198 _public function_ `FNodeClassRegistryKey ToRegistryKey() const`
- L203 _public member_ `EMetasoundFrontendClassAccessFlags AccessFlags;`
- L211 _public member_ `uint8 bIsValid : 1;` — If true, class info is valid and accurately reflects that from what was provided on construction. If false, info was constructed from AssetData that failed to provide all expected tags or tag values (indicating tag data is out-of-date). Default constructed info is considered invalid as well.

#### struct `Metasound::FFrontendQueryKey`  
`struct FFrontendQueryKey`  
_L219-244_
- desc: FFrontendQueryKey allows entries to be partitioned by their key. A key can be created by default constructor, int32, FString or FName.
- L221 _public prototype_ `FFrontendQueryKey();`
- L222 _public prototype_ `explicit FFrontendQueryKey(int32 InKey);`
- L223 _public prototype_ `explicit FFrontendQueryKey(const FString& InKey);`
- L224 _public prototype_ `explicit FFrontendQueryKey(const FName& InKey);`
- L226 _public prototype_ `FFrontendQueryKey(const FFrontendQueryKey&) = default;`
- L227 _public prototype_ `FFrontendQueryKey& operator=(const FFrontendQueryKey&) = default;`
- L228 _public prototype_ `FFrontendQueryKey(FFrontendQueryKey&&) = default;`
- L229 _public prototype_ `FFrontendQueryKey& operator=(FFrontendQueryKey&&) = default;`
- L236 _public prototype_ `bool IsNull() const;`
- L241 _private typedef_ `using FKeyType = TVariant<FNull, int32, FString, FName>;`
- L242 _private member_ `FKeyType Key;`
- L243 _private member_ `uint32 Hash;`

#### struct `Metasound::FFrontendQueryKey::FNull`  
`struct FNull`  
_L239-239_

#### struct `Metasound::FFrontendQueryEntry`  
`struct FFrontendQueryEntry`  
_L258-268_
- desc: FFrontendQueryEntry represents one value in the query. It contains an ID, value and score.
- L260 _public typedef_ `using FValue = FFrontendQueryValue;`
- L262 _public member_ `FGuid ID;`
- L263 _public member_ `FValue Value;`
- L264 _public member_ `float Score = 0.f;`

#### class `Metasound::IFrontendQueryStep`  
`class IFrontendQueryStep`  
_L279-283_
- desc: Interface for an individual step in a query
- L282 _public prototype_ `virtual ~IFrontendQueryStep() = default;`

#### class `Metasound::IFrontendQueryStreamStep`  
`class IFrontendQueryStreamStep : public IFrontendQueryStep`  
_L286-291_
- inherits: `IFrontendQueryStep`
- desc: Interface for a query step which streams new entries.
- L289 _public prototype_ `virtual ~IFrontendQueryStreamStep() = default;`
- L290 _public prototype_ `virtual void Stream(TArray<FFrontendQueryValue>& OutEntries) = 0;`

#### class `Metasound::IFrontendQueryTransformStep`  
`class IFrontendQueryTransformStep : public IFrontendQueryStep`  
_L294-299_
- inherits: `IFrontendQueryStep`
- desc: Interface for a query step which transforms an entry's value.
- L297 _public prototype_ `virtual ~IFrontendQueryTransformStep() = default;`
- L298 _public prototype_ `virtual void Transform(FFrontendQueryEntry::FValue& InValue) const = 0;`

#### class `Metasound::IFrontendQueryMapStep`  
`class IFrontendQueryMapStep : public IFrontendQueryStep`  
_L302-307_
- inherits: `IFrontendQueryStep`
- desc: Interface for a query step which maps entries to keys.
- L305 _public prototype_ `virtual ~IFrontendQueryMapStep() = default;`
- L306 _public prototype_ `virtual FFrontendQueryKey Map(const FFrontendQueryEntry& InEntry) const = 0;`

#### class `Metasound::IFrontendQueryMultiMapStep`  
`class IFrontendQueryMultiMapStep : public IFrontendQueryStep`  
_L310-315_
- inherits: `IFrontendQueryStep`
- desc: Interface for a query step which maps entries to multiple keys.
- L313 _public prototype_ `virtual ~IFrontendQueryMultiMapStep() = default;`
- L314 _public prototype_ `virtual TArray<FFrontendQueryKey> Map(const FFrontendQueryEntry& InEntry) const = 0;`

#### class `Metasound::IFrontendQueryReduceStep`  
`class IFrontendQueryReduceStep : public IFrontendQueryStep`  
_L318-323_
- inherits: `IFrontendQueryStep`
- desc: Interface for a query step which reduces entries with the same key.
- L321 _public prototype_ `virtual ~IFrontendQueryReduceStep() = default;`
- L322 _public prototype_ `virtual void Reduce(const FFrontendQueryKey& InKey, FFrontendQueryPartition& InOutEntries) const = 0;`

#### class `Metasound::IFrontendQueryFilterStep`  
`class IFrontendQueryFilterStep : public IFrontendQueryStep`  
_L326-331_
- inherits: `IFrontendQueryStep`
- desc: Interface for a query step which filters entries.
- L329 _public prototype_ `virtual ~IFrontendQueryFilterStep() = default;`
- L330 _public prototype_ `virtual bool Filter(const FFrontendQueryEntry& InEntry) const = 0;`

#### class `Metasound::IFrontendQueryScoreStep`  
`class IFrontendQueryScoreStep : public IFrontendQueryStep`  
_L334-339_
- inherits: `IFrontendQueryStep`
- desc: Interface for a query step which scores entries.
- L337 _public prototype_ `virtual ~IFrontendQueryScoreStep() = default;`
- L338 _public prototype_ `virtual float Score(const FFrontendQueryEntry& InEntry) const = 0;`

#### class `Metasound::IFrontendQuerySortStep`  
`class IFrontendQuerySortStep : public IFrontendQueryStep`  
_L342-347_
- inherits: `IFrontendQueryStep`
- desc: Interface for a query step which sorts entries.
- L345 _public prototype_ `virtual ~IFrontendQuerySortStep() = default;`
- L346 _public prototype_ `virtual bool Sort(const FFrontendQueryEntry& InEntryLHS, const FFrontendQueryEntry& InEntryRHS) const = 0;`

#### class `Metasound::IFrontendQueryLimitStep`  
`class IFrontendQueryLimitStep : public IFrontendQueryStep`  
_L349-354_
- inherits: `IFrontendQueryStep`
- L352 _public prototype_ `virtual ~IFrontendQueryLimitStep() = default;`
- L353 _public prototype_ `virtual int32 Limit() const = 0;`

#### class `Metasound::FFrontendQueryStep`  
`class FFrontendQueryStep`  
_L359-461_
- desc: FFrontendQueryStep wraps all the support IFrontenQueryStep interfaces and supplies unified `ExecuteStep(...)` member function.
- L361 _private prototype_ `FFrontendQueryStep() = delete;`
- L405 _public typedef_ `using FStreamFunction = TUniqueFunction<void (TArray<FFrontendQueryValue>&)>;`
- L406 _public typedef_ `using FTransformFunction = TFunction<void (FFrontendQueryEntry::FValue&)>;`
- L407 _public typedef_ `using FMapFunction = TFunction<FFrontendQueryKey (const FFrontendQueryEntry&)>;`
- L408 _public typedef_ `using FMultiMapFunction = TFunction<TArray<FFrontendQueryKey>(const FFrontendQueryEntry&)>;`
- L409 _public typedef_ `using FReduceFunction = TFunction<void (const FFrontendQueryKey& InKey, FFrontendQueryPartition& InOutEntries)>;`
- L410 _public typedef_ `using FFilterFunction = TFunction<bool (const FFrontendQueryEntry&)>;`
- L411 _public typedef_ `using FScoreFunction = TFunction<float (const FFrontendQueryEntry&)>;`
- L412 _public typedef_ `using FSortFunction = TFunction<bool (const FFrontendQueryEntry& InEntryLHS, const FFrontendQueryEntry& InEntryRHS)>;`
- L413 _public typedef_ `using FLimitFunction = TFunction<int32 ()>;`
- L416 _public prototype_ `FFrontendQueryStep(FStreamFunction&& InFunc);` — Create query step using TFunction or lambda.
- L417 _public prototype_ `FFrontendQueryStep(FTransformFunction&& InFunc);`
- L418 _public prototype_ `FFrontendQueryStep(FMapFunction&& InFunc);`
- L419 _public prototype_ `FFrontendQueryStep(FMultiMapFunction&& InFunc);`
- L420 _public prototype_ `FFrontendQueryStep(FReduceFunction&& InFunc);`
- L421 _public prototype_ `FFrontendQueryStep(FFilterFunction&& InFilt);`
- L422 _public prototype_ `FFrontendQueryStep(FScoreFunction&& InScore);`
- L423 _public prototype_ `FFrontendQueryStep(FSortFunction&& InSort);`
- L424 _public prototype_ `FFrontendQueryStep(FLimitFunction&& InLimit);`
- L427 _public prototype_ `FFrontendQueryStep(TUniquePtr<IFrontendQueryStreamStep>&& InStep);` — Create a query step using a IFrontedQueryStep
- L428 _public prototype_ `FFrontendQueryStep(TUniquePtr<IFrontendQueryTransformStep>&& InStep);`
- L429 _public prototype_ `FFrontendQueryStep(TUniquePtr<IFrontendQueryMapStep>&& InStep);`
- L430 _public prototype_ `FFrontendQueryStep(TUniquePtr<IFrontendQueryMultiMapStep>&& InStep);`
- L431 _public prototype_ `FFrontendQueryStep(TUniquePtr<IFrontendQueryReduceStep>&& InStep);`
- L432 _public prototype_ `FFrontendQueryStep(TUniquePtr<IFrontendQueryFilterStep>&& InStep);`
- L433 _public prototype_ `FFrontendQueryStep(TUniquePtr<IFrontendQueryScoreStep>&& InStep);`
- L434 _public prototype_ `FFrontendQueryStep(TUniquePtr<IFrontendQuerySortStep>&& InStep);`
- L435 _public prototype_ `FFrontendQueryStep(TUniquePtr<IFrontendQueryLimitStep>&& InStep);`
- L439 _public prototype_ `void Merge(FIncremental& InIncremental, FFrontendQuerySelection& InOutSelection) const;` — Merge an incremental result with the prior result from this step.
- L442 _public prototype_ `void Execute(TSet<FFrontendQueryKey>& InOutUpdatedKeys, FFrontendQuerySelection& InOutResult) const;` — Execute step. Assume not other prior results exist.
- L450 _public prototype_ `bool IsDependentOnPartitionComposition() const;` — Returns true if a steps result is conditioned on the composition of a partition. Most steps are only dependent upon individual entries, but some (Reduce, Limit, Sort) are specifically dependent upon the composition of the Partition. They require special handling during incremental updates.
- L453 _public prototype_ `bool CanProcessRemovals() const;` — Return true if the step can be used to process downstream removals.
- L457 _public prototype_ `bool CanProduceEntries() const;` — Return true if the step can produce new entries. This information is used to early-out on queries with no new entries.
- L460 _private member_ `TUniquePtr<IStepExecuter> StepExecuter;`

#### struct `Metasound::FFrontendQueryStep::FIncremental`  
`struct FIncremental`  
_L365-376_
- desc: Represents an incremental update to the existing data.
- L368 _public member_ `TSet<FFrontendQueryKey> ActiveKeys;` — Keys that are affected by this incremental update.
- L370 _public member_ `FFrontendQuerySelection ActiveSelection;` — The selection being manipulated in the incremental update.
- L373 _public member_ `TSet<FFrontendQueryKey> ActiveRemovalKeys;` — Keys that contain active removals.
- L375 _public member_ `FFrontendQuerySelection ActiveRemovalSelection;` — Selection containing entries to remove during a merge.

#### struct `Metasound::FFrontendQueryStep::IStepExecuter`  
`struct IStepExecuter`  
_L379-403_
- desc: Interface for executing a step in the query.
- L381 _public prototype_ `virtual ~IStepExecuter() = default;`
- L384 _public prototype_ `virtual void Merge(FIncremental& InOutIncremental, FFrontendQuerySelection& InOutSelection) const = 0;` — Merge new result with the existing result from this step.
- L387 _public prototype_ `virtual void Execute(TSet<FFrontendQueryKey>& InOutUpdatedKeys, FFrontendQuerySelection& InOutResult) const = 0;` — Execute step.
- L395 _public prototype_ `virtual bool IsDependentOnPartitionComposition() const = 0;` — Returns true if a steps result is conditioned on the composition of a partition. Most steps are only dependent upon individual entries, but some (Reduce, Limit, Sort) are specifically dependent upon the composition of the Partition. They require special handling during incremental updates.
- L398 _public prototype_ `virtual bool CanProcessRemovals() const = 0;` — Return true if the step can be used to process downstream removals.
- L402 _public prototype_ `virtual bool CanProduceEntries() const = 0;` — Return true if the step can produce new entries. This information is used to early-out on queries with no new entries.

#### class `Metasound::FFrontendQuery`  
`class FFrontendQuery`  
_L464-537_
- desc: FFrontendQuery contains a set of query steps which produce a FFrontendQuerySelectionView
- L468 _public typedef_ `using FStreamFunction = FFrontendQueryStep::FStreamFunction;`
- L469 _public typedef_ `using FTransformFunction = FFrontendQueryStep::FTransformFunction;`
- L470 _public typedef_ `using FMapFunction = FFrontendQueryStep::FMapFunction;`
- L471 _public typedef_ `using FReduceFunction = FFrontendQueryStep::FReduceFunction;`
- L472 _public typedef_ `using FFilterFunction = FFrontendQueryStep::FFilterFunction;`
- L473 _public typedef_ `using FScoreFunction = FFrontendQueryStep::FScoreFunction;`
- L474 _public typedef_ `using FSortFunction = FFrontendQueryStep::FSortFunction;`
- L475 _public typedef_ `using FLimitFunction = FFrontendQueryStep::FLimitFunction;`
- L477 _public prototype_ `FFrontendQuery();`
- L478 _public prototype_ `FFrontendQuery(FFrontendQuery&&) = default;`
- L479 _public prototype_ `FFrontendQuery& operator=(FFrontendQuery&&) = default;`
- L481 _public prototype_ `FFrontendQuery(const FFrontendQuery&) = delete;`
- L482 _public prototype_ `FFrontendQuery& operator=(const FFrontendQuery&) = delete;`
- L487 _public function_ `template<typename StepType, typename... ArgTypes> FFrontendQuery& AddStep(ArgTypes&&... Args)` — Add a step to the query.
- L493 _public function_ `template<typename FuncType> FFrontendQuery& AddFunctionStep(FuncType&& InFunc)`
- L498 _public prototype_ `FFrontendQuery& AddStreamLambdaStep(FStreamFunction&& InFunc);`
- L499 _public prototype_ `FFrontendQuery& AddTransformLambdaStep(FTransformFunction&& InFunc);`
- L500 _public prototype_ `FFrontendQuery& AddMapLambdaStep(FMapFunction&& InFunc);`
- L501 _public prototype_ `FFrontendQuery& AddReduceLambdaStep(FReduceFunction&& InFunc);`
- L502 _public prototype_ `FFrontendQuery& AddFilterLambdaStep(FFilterFunction&& InFunc);`
- L503 _public prototype_ `FFrontendQuery& AddScoreLambdaStep(FScoreFunction&& InFunc);`
- L504 _public prototype_ `FFrontendQuery& AddSortLambdaStep(FSortFunction&& InFunc);`
- L505 _public prototype_ `FFrontendQuery& AddLimitLambdaStep(FLimitFunction&& InFunc);`
- L508 _public prototype_ `FFrontendQuery& AddStep(TUniquePtr<FFrontendQueryStep>&& InStep);` — Add a step to the query.
- L511 _public prototype_ `const FFrontendQuerySelection& Update(TSet<FFrontendQueryKey>& OutUpdatedKeys);` — Calls all steps in the query and returns the selection.
- L512 _public prototype_ `const FFrontendQuerySelection& Update();`
- L515 _public prototype_ `const FFrontendQuerySelection& GetSelection() const;` — Returns the current result.
- L518 _private typedef_ `using FIncremental = FFrontendQueryStep::FIncremental;`
- L520 _private prototype_ `void UpdateInternal(TSet<FFrontendQueryKey>& OutUpdatedKeys);`
- L521 _private prototype_ `void MergeInternal(FFrontendQueryStep& Step, FIncremental& InOutIncremental, FFrontendQuerySelection& InOutMergedSelection);`
- L523 _private member_ `TSharedRef<FFrontendQuerySelection, ESPMode::ThreadSafe> Result;`
- L533 _private prototype_ `void AppendPartitions(const TSet<FFrontendQueryKey>& InKeysToAppend, const FFrontendQuerySelection& InSelection, TSet<FFrontendQueryKey>& OutKeysModified, FFrontendQuerySelection& OutSelection) const;`
- L535 _private member_ `TArray<FStepInfo> Steps;`
- L536 _private member_ `int32 FinalEntryProducingStepIndex = INDEX_NONE;`

#### struct `Metasound::FFrontendQuery::FStepInfo`  
`struct FStepInfo`  
_L525-531_
- L527 _public member_ `TUniquePtr<FFrontendQueryStep> Step;`
- L528 _public member_ `FFrontendQuerySelection OutputCache;`
- L529 _public member_ `bool bMergeAndCacheOutput = false;`
- L530 _public member_ `bool bProcessRemovals = false;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L156 _namespace_ `namespace Metasound`
- L158 _namespace_ `namespace Frontend` (scope `Metasound`)
- L247 _typedef_ `using FFrontendQueryValue = TVariant < FMetasoundFrontendVersion, Frontend::FAssetManagerTransaction, Frontend::FInterfaceRegistryTransaction, Frontend::FMetaSoundClassInfo, Frontend::FNodeClassRegistryTransaction >;` (scope `Metasound`) — A FFrontendQueryValue contains data of interest.
- L273 _typedef_ `using FFrontendQueryPartition = TArray<FFrontendQueryEntry, TInlineAllocator<1>>;` (scope `Metasound`)
- L276 _typedef_ `using FFrontendQuerySelection = TSortedMap<FFrontendQueryKey, FFrontendQueryPartition>;` (scope `Metasound`) — A FFrontendQuerySelection holds a map of keys to partitions.

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendQuerySteps.h` (Public)


#### class `Metasound::FMapToNull`  
`class FMapToNull : public IFrontendQueryMapStep`  
_L20-27_
- inherits: `IFrontendQueryMapStep`
- L23 _public function_ `virtual FFrontendQueryKey Map(const FFrontendQueryEntry& InEntry) const override`

#### class `Metasound::FNodeClassRegistrationEvents`  
`class FNodeClassRegistrationEvents : public IFrontendQueryStreamStep`  
_L31-39_
- inherits: `IFrontendQueryStreamStep`
- desc: Streams node classes that have been newly registered or unregistered since last call to Stream()
- L34 _public prototype_ `FNodeClassRegistrationEvents();`
- L35 _public prototype_ `virtual void Stream(TArray<FFrontendQueryValue>& OutValues) override;`
- L38 _private member_ `TPimplPtr<FNodeClassRegistrationEventsPimpl> Pimpl;`

#### class `Metasound::FAssetRegistrationEvents`  
`class FAssetRegistrationEvents : public IFrontendQueryStreamStep`  
_L43-51_
- inherits: `IFrontendQueryStreamStep`
- desc: Streams assets that have been newly registered or unregistered since last call to Stream()
- L46 _public prototype_ `FAssetRegistrationEvents();`
- L47 _public prototype_ `virtual void Stream(TArray<FFrontendQueryValue>& OutValues) override;`
- L50 _private member_ `TPimplPtr<FAssetRegistrationEventsPimpl> Pimpl;`

#### class `Metasound::FMapAssetRegistrationEventsToNodeRegistryKeys`  
`class FMapAssetRegistrationEventsToNodeRegistryKeys : public IFrontendQueryMapStep`  
_L54-58_
- inherits: `IFrontendQueryMapStep`
- desc: Partitions asset registration events by their node registration keys.
- L57 _public prototype_ `virtual FFrontendQueryKey Map(const FFrontendQueryEntry& InEntry) const override;`

#### class `Metasound::FMapClassRegistrationEventsToNodeRegistryKeys`  
`class FMapClassRegistrationEventsToNodeRegistryKeys : public IFrontendQueryMapStep`  
_L61-65_
- inherits: `IFrontendQueryMapStep`
- desc: Partitions class registration events by their node registration keys.
- L64 _public prototype_ `virtual FFrontendQueryKey Map(const FFrontendQueryEntry& InEntry) const override;`

#### class `Metasound::FReduceAssetRegistrationEventsToCurrentStatus`  
`class FReduceAssetRegistrationEventsToCurrentStatus : public IFrontendQueryReduceStep`  
_L70-78_
- inherits: `IFrontendQueryReduceStep`
- desc: Reduces asset registration events mapped to the same key by inspecting their add/remove state in order to determine their final state. If an item has been added more than it has been removed, then it is added to the output. Otherwise, it is omitted.
- L73 _public prototype_ `virtual void Reduce(const FFrontendQueryKey& InKey, FFrontendQueryPartition& InOutEntries) const override;`
- L75 _private typedef_ `using FTimeType = Frontend::FAssetManagerTransaction::FTimeType;`
- L76 _private prototype_ `static FTimeType GetTransactionTimestamp(const FFrontendQueryEntry& InEntry);`
- L77 _private prototype_ `static bool IsValidTransactionOfType(Frontend::FAssetManagerTransaction::ETransactionType InType, const FFrontendQueryEntry* InEntry);`

#### class `Metasound::FReduceRegistrationEventsToCurrentStatus`  
`class FReduceRegistrationEventsToCurrentStatus: public IFrontendQueryReduceStep`  
_L83-91_
- inherits: `IFrontendQueryReduceStep`
- desc: Reduces registration events mapped to the same key by inspecting their add/remove state in order to determine their final state. If an item has been added more than it has been removed, then it is added to the output. Otherwise, it is omitted.
- L86 _public prototype_ `virtual void Reduce(const FFrontendQueryKey& InKey, FFrontendQueryPartition& InOutEntries) const override;`
- L88 _private typedef_ `using FTimeType = Frontend::FNodeClassRegistryTransaction::FTimeType;`
- L89 _private prototype_ `static FTimeType GetTransactionTimestamp(const FFrontendQueryEntry& InEntry);`
- L90 _private prototype_ `static bool IsValidTransactionOfType(Frontend::FNodeClassRegistryTransaction::ETransactionType InType, const FFrontendQueryEntry* InEntry);`

#### class `Metasound::FTransformAssetRegistrationEventsToClassInfo`  
`class FTransformAssetRegistrationEventsToClassInfo : public IFrontendQueryTransformStep`  
_L94-98_
- inherits: `IFrontendQueryTransformStep`
- desc: Transforms an asset registration event into a FMetaSoundClassInfo.
- L97 _public prototype_ `virtual void Transform(FFrontendQueryEntry::FValue& InValue) const override;`

#### class `Metasound::FTransformNodeClassRegistrationEventsToClassInfo`  
`class FTransformNodeClassRegistrationEventsToClassInfo : public IFrontendQueryTransformStep`  
_L101-105_
- inherits: `IFrontendQueryTransformStep`
- desc: Transforms a node class registration event into a FMetaSoundClassInfo.
- L104 _public prototype_ `virtual void Transform(FFrontendQueryEntry::FValue& InValue) const override;`

#### class `Metasound::FFilterClassesByInputVertexDataType`  
`class FFilterClassesByInputVertexDataType : public IFrontendQueryFilterStep`  
_L107-122_
- inherits: `IFrontendQueryFilterStep`
- L111 _public function_ `template<typename DataType> FFilterClassesByInputVertexDataType() : FFilterClassesByInputVertexDataType(GetMetasoundDataTypeName<DataType>())`
- L116 _public prototype_ `FFilterClassesByInputVertexDataType(const FName& InTypeName);`
- L118 _public prototype_ `virtual bool Filter(const FFrontendQueryEntry& InEntry) const override;`
- L121 _private member_ `FName InputVertexTypeName;`

#### class `Metasound::FFilterClassesByOutputVertexDataType`  
`class FFilterClassesByOutputVertexDataType : public IFrontendQueryFilterStep`  
_L124-139_
- inherits: `IFrontendQueryFilterStep`
- L128 _public function_ `template<typename DataType> FFilterClassesByOutputVertexDataType() : FFilterClassesByOutputVertexDataType(GetMetasoundDataTypeName<DataType>())`
- L133 _public prototype_ `FFilterClassesByOutputVertexDataType(const FName& InTypeName);`
- L135 _public prototype_ `virtual bool Filter(const FFrontendQueryEntry& InEntry) const override;`
- L138 _private member_ `FName OutputVertexTypeName;`

#### class `Metasound::FMapClassesToClassName`  
`class FMapClassesToClassName : public IFrontendQueryMapStep`  
_L141-146_
- inherits: `IFrontendQueryMapStep`
- L144 _public prototype_ `virtual FFrontendQueryKey Map(const FFrontendQueryEntry& InEntry) const override;`

#### class `Metasound::FFilterClassesByClassID`  
`class FFilterClassesByClassID : public IFrontendQueryFilterStep`  
_L148-157_
- inherits: `IFrontendQueryFilterStep`
- L151 _public prototype_ `FFilterClassesByClassID(const FGuid InClassID);`
- L153 _public prototype_ `virtual bool Filter(const FFrontendQueryEntry& InEntry) const override;`
- L156 _private member_ `FGuid ClassID;`

#### class `Metasound::FMapToFullClassName`  
`class FMapToFullClassName : public IFrontendQueryMapStep`  
_L159-163_
- inherits: `IFrontendQueryMapStep`
- L162 _public prototype_ `virtual FFrontendQueryKey Map(const FFrontendQueryEntry& InEntry) const override;`

#### class `Metasound::FReduceClassesToHighestVersion`  
`class FReduceClassesToHighestVersion : public IFrontendQueryReduceStep`  
_L165-169_
- inherits: `IFrontendQueryReduceStep`
- L168 _public prototype_ `virtual void Reduce(const FFrontendQueryKey& InKey, FFrontendQueryPartition& InOutEntries) const override;`

#### class `Metasound::FSortClassesByVersion`  
`class FSortClassesByVersion : public IFrontendQuerySortStep`  
_L171-175_
- inherits: `IFrontendQuerySortStep`
- L174 _public prototype_ `virtual bool Sort(const FFrontendQueryEntry& InEntryLHS, const FFrontendQueryEntry& InEntryRHS) const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L14 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendRegistries.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendRegistryContainer.h` (Public)


#### Free symbols / members of external scopes

- L26 _typedef_ `using FMetasoundFrontendRegistryContainer = Metasound::Frontend::INodeClassRegistry;`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendRegistryKey.h` (Public)


#### struct `Metasound::Frontend::FNodeClassInfo`  
`struct FNodeClassInfo`  
_L20-73_
- desc: FNodeClassInfo contains a minimal set of information needed to find and query node classes. THIS CLASS IS ACTIVELY BEING DEPRECATED. USE FNodeClassRegistryKey instead.
- L23 _public member_ `FMetasoundFrontendClassName ClassName;` — ClassName of the given class
- L26 _public member_ `EMetasoundFrontendClassType Type = EMetasoundFrontendClassType::Invalid;` — The type of this node class
- L29 _public member_ `FGuid AssetClassID;` — `UE_DEPRECATED(5.6, "Data now characterized in asset class data")`
- L32 _public member_ `FTopLevelAssetPath AssetPath;` — `UE_DEPRECATED(5.6, "Data now characterized in asset class data")`
- L35 _public member_ `FMetasoundFrontendVersionNumber Version;` — Version of the registered class
- L39 _public member_ `TSet<FName> InputTypes;` — `UE_DEPRECATED(5.6, "Data now characterized in asset class data ('Inputs')")`
- L42 _public member_ `TSet<FName> OutputTypes;` — `UE_DEPRECATED(5.6, "Type data no longer required by class info ('Outputs')")`
- L45 _public member_ `bool bIsPreset;` — `UE_DEPRECATED(5.6, "Preset data no longer required by class info")`
- L48 _public prototype_ `FNodeClassInfo();`
- L53 _public prototype_ `FNodeClassInfo(const FMetasoundFrontendClassMetadata& InMetadata);` — Constructor used to generate NodeClassInfo from a class' Metadata. (Does not cache AssetPath and thus may not support loading asset should the class originate from one).
- L56 _public prototype_ `FNodeClassInfo(const FMetasoundFrontendGraphClass& InClass);` — Constructor used to generate NodeClassInfo from a graph class
- L59 _public prototype_ `FNodeClassInfo(const FMetasoundFrontendGraphClass& InClass, const FTopLevelAssetPath& InAssetPath);` — `UE_DEPRECATED(5.6, "Asset data no longer contained on NodeClassInfo, see AssetClass Info")`
- L61 _public prototype_ `FNodeClassInfo(const FNodeClassInfo& Other);`
- L62 _public prototype_ `FNodeClassInfo(FNodeClassInfo&& Other);`
- L64 _public prototype_ `FNodeClassInfo& operator=(const FNodeClassInfo& Other);`
- L65 _public prototype_ `FNodeClassInfo& operator=(FNodeClassInfo&& Other);`
- L68 _public function_ `static const FNodeClassInfo& GetInvalid()` — Added to aid in deprecation of this class in favor of FNodeClassRegistryKey

#### struct `Metasound::Frontend::FNodeClassRegistryKey`  
`struct FNodeClassRegistryKey`  
_L75-137_
- L77 _public member_ `EMetasoundFrontendClassType Type = EMetasoundFrontendClassType::Invalid;`
- L78 _public member_ `FMetasoundFrontendClassName ClassName;`
- L79 _public member_ `FMetasoundFrontendVersionNumber Version;`
- L81 _public prototype_ `FNodeClassRegistryKey() = default;`
- L82 _public prototype_ `FNodeClassRegistryKey(EMetasoundFrontendClassType InType, const FMetasoundFrontendClassName& InClassName, int32 InMajorVersion, int32 InMinorVersion);`
- L83 _public prototype_ `FNodeClassRegistryKey(EMetasoundFrontendClassType InType, const FMetasoundFrontendClassName& InClassName, const FMetasoundFrontendVersionNumber& InVersion);`
- L84 _public prototype_ `FNodeClassRegistryKey(const FNodeClassMetadata& InNodeMetadata);`
- L85 _public prototype_ `FNodeClassRegistryKey(const FMetasoundFrontendClassMetadata& InNodeMetadata);`
- L86 _public prototype_ `FNodeClassRegistryKey(const FMetasoundFrontendGraphClass& InGraphClass);`
- L89 _public prototype_ `FNodeClassRegistryKey(const FNodeClassInfo& InClassInfo);` — `UE_DEPRECATED(5.8, "FNodeClassInfo is actively being deprecated, use overload with NodeClassRegistryKey or otherwise")`
- L91 _public prototype_ `FNodeClassRegistryKey(const FMetaSoundAssetKey& AssetKey);`
- L120 _public prototype_ `static const FNodeClassRegistryKey& GetInvalid();` — Returns invalid (default constructed) key
- L123 _public prototype_ `bool IsValid() const;` — Returns whether or not instance is valid or not
- L126 _public prototype_ `void Reset();` — Resets the key back to an invalid default state
- L129 _public prototype_ `FString ToString() const;` — Returns string representation of key
- L132 _public prototype_ `FString ToString(const FString& InScopeHeader) const;` — Convenience function to convert to a string representation of the given key with a scope header (primarily for tracing).
- L136 _public prototype_ `static bool Parse(const FString& InKeyString, FNodeClassRegistryKey& OutKey);` — Parses string representation of key into registry key.  For debug and deserialization use only. Returns true if parsed successfully.

#### struct `Metasound::Frontend::FGraphClassRegistryKey`  
`struct FGraphClassRegistryKey`  
_L140-163_
- L142 _public member_ `FNodeClassRegistryKey NodeKey;`
- L143 _public member_ `FTopLevelAssetPath AssetPath;`
- L144 _public member_ `uint32 ObjectID = (uint32)INDEX_NONE;`
- L146 _public prototype_ `FString ToString() const;`
- L149 _public prototype_ `FString ToString(const FString& InScopeHeader) const;` — Convenience function to convert to a string representation of the given key with a scope header (primarily for tracing).
- L151 _public prototype_ `bool IsValid() const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L15 _namespace_ `namespace Metasound`
- L15 _namespace_ `namespace Frontend` (scope `Metasound`)
- L93 _function_ `inline friend bool operator==(const FNodeClassRegistryKey& InLHS, const FNodeClassRegistryKey& InRHS)` (scope `Metasound::Frontend`)
- L98 _function_ `inline friend bool operator<(const FNodeClassRegistryKey& InLHS, const FNodeClassRegistryKey& InRHS)` (scope `Metasound::Frontend`)
- L113 _function_ `friend inline uint32 GetTypeHash(const FNodeClassRegistryKey& InKey)` (scope `Metasound::Frontend`)
- L138 _typedef_ `using FNodeRegistryKey = FNodeClassRegistryKey;` (scope `Metasound::Frontend`)
- L153 _function_ `inline friend bool operator==(const FGraphClassRegistryKey& InLHS, const FGraphClassRegistryKey& InRHS)` (scope `Metasound::Frontend`)
- L158 _function_ `friend inline uint32 GetTypeHash(const FGraphClassRegistryKey& InKey)` (scope `Metasound::Frontend`)
- L164 _typedef_ `using FGraphRegistryKey = FGraphClassRegistryKey;` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendSearchEngine.h` (Public)


#### class `Metasound::Frontend::ISearchEngine`  
`class ISearchEngine`  
_L21-98_
- desc: Interface for frontend search engine. A frontend search engine provides a simple interface for common frontend queries. It also serves as an opportunity to cache queries to reduce CPU load.
- L37 _public prototype_ `static ISearchEngine& Get();` — Return an instance of a search engine.
- L39 _public prototype_ `virtual ~ISearchEngine() = default;`
- L42 _public prototype_ `virtual void Prime() = 0;` — Updates internal state to speed up queries.
- L45 _public prototype_ `virtual bool FindRegisteredClass(const FMetasoundFrontendClassName& InName, int32 InMajorVersion, FMetaSoundClassInfo& OutClass) = 0;` — Find the class info with the given ClassName & Major Version. Returns false if not found, true if found.
- L48 _public prototype_ `virtual bool FindClassWithHighestMinorVersion(const FMetasoundFrontendClassName& InName, int32 InMajorVersion, FMetasoundFrontendClass& OutClass);` — `UE_DEPRECATED(5.8, "Use FindRegisteredClass. If a full class definition is required, use the resulting class info to look-up the class directly from the INodeClassRegistry.")`
- L51 _public prototype_ `virtual TArray<FMetasoundFrontendVersion> FindAllRegisteredInterfacesWithName(FName InInterfaceName) = 0;` — Finds all registered interfaces with the given name.
- L54 _public prototype_ `virtual bool FindHighestInterfaceVersion(FName InInterfaceName, FMetasoundFrontendVersion& OutVersion) = 0;` — Finds the registered interface version with the highest version of the given name. Returns true if found, false if not.
- L57 _public prototype_ `virtual bool FindInterfaceWithHighestVersion(FName InInterfaceName, FMetasoundFrontendInterface& OutInterface) = 0;` — Finds the registered interface with the highest version of the given name. Returns true if found, false if not.
- L60 _public prototype_ `virtual TArray<FMetasoundFrontendVersion> FindUClassDefaultInterfaceVersions(const FTopLevelAssetPath& InUClassPath) = 0;` — Returns all interfaces that are to be added to a given document when it is initialized on an object with the given class
- L67 _public prototype_ `virtual TArray<FMetaSoundClassInfo> FindAllClasses(EResultVersion Options, bool bIncludeUnloadedAssets = false) = 0;` — Find all class infos including those not registered but available via the asset manager for selection. Options - If set to 'All', include all versions (i.e. deprecated classes and versions of classes that are not the highest major version). bIncludeUnloadedAssets - If true, include class info for assets not loaded/registered.
- L70 _public prototype_ `virtual TArray<FMetasoundFrontendClass> FindAllClasses(bool bInIncludeAllVersions);` — `UE_DEPRECATED(5.8, "Use FindAllClasses overload that returns ClassInfo instead")`
- L75 _public prototype_ `virtual TArray<FMetaSoundClassInfo> FindClassesWithName(const FMetasoundFrontendClassName& InName, ESortByVersion SortByVersion = ESortByVersion::Yes) = 0;` — Find all class info with the given ClassName. (Optional) Sort matches based on version.
- L80 _public prototype_ `virtual TArray<FMetasoundFrontendClass> FindClassesWithName(const FMetasoundFrontendClassName& InName, bool bInSortByVersion) = 0;` — Find all classes with the given ClassName. (Optional) Sort matches based on version.
- L84 _public prototype_ `virtual bool FindClassWithHighestVersion(const FMetasoundFrontendClassName& InName, FMetaSoundClassInfo& OutInfo) = 0;` — Find the highest version of class info with the given ClassName. Returns false if not found, true if found.
- L87 _public prototype_ `virtual bool FindClassWithHighestVersion(const FMetasoundFrontendClassName& InName, FMetasoundFrontendClass& OutClass);` — (To be deprecated) Find the highest version of a class with the given ClassName. Returns false if not found, true if found.
- L90 _public prototype_ `virtual TArray<FMetasoundFrontendVersion> FindAllInterfaceVersions(bool bInIncludeAllVersions = false) = 0;` — Returns array with all registered interface versions. Optionally, include interface versions that are not the highest version.
- L93 _public function_ `virtual TArray<FMetasoundFrontendInterface> FindAllInterfaces(bool bInIncludeAllVersions = false)` — `UE_DEPRECATED(5.8, "Use FindAllInterfaceVersions instead, and refine results further if required using IInterfaceRegistry")`
- L97 _protected prototype_ `ISearchEngine() = default;`

#### enum `Metasound::Frontend::ISearchEngine::EResultVersion`  
`enum class EResultVersion : uint8`  
_L24-28_
- L26 _public enumerator_ `All`
- L27 _public enumerator_ `Highest`

#### enum `Metasound::Frontend::ISearchEngine::ESortByVersion`  
`enum class ESortByVersion : uint8`  
_L30-34_
- L32 _public enumerator_ `Yes`
- L33 _public enumerator_ `No`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L12 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendTemplateNodeConfiguration.h` (Public)


#### struct `FMetaSoundFrontendTemplateNodeConfiguration`  
`struct FMetaSoundFrontendTemplateNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L14-17_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- desc: Default node configuration used by the Node Template system (see IMetaSoundNodeTemplateBase & FNodeTemplateBase). Distinct from FMetaSoundFrontendDocumentTemplate, which configures the MetaSound document as a whole. Also distinct from FMetaSoundFrontendNodeConfiguration, which stores per-node interface swap data (node configuration, a separate feature).

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundFrontendTransform.h` (Public)


#### class `Metasound::Frontend::IBuilderTransform`  
`class IBuilderTransform`  
_L41-47_
- L44 _public prototype_ `virtual ~IBuilderTransform() = default;`
- L46 _public prototype_ `virtual bool Transform(FMetaSoundFrontendDocumentBuilder& InOutBuilder) const = 0;`

#### class `Metasound::Frontend::IBuilderVersionTransform`  
`class IBuilderVersionTransform : public IBuilderTransform`  
_L49-56_
- inherits: `IBuilderTransform`
- L52 _public prototype_ `virtual ~IBuilderVersionTransform() = default;`
- L55 _public prototype_ `virtual const FMetasoundFrontendVersion& GetVersion() const = 0;` — Returns version update transform applies

#### class `Metasound::Frontend::IDocumentTransform`  
`class IDocumentTransform`  
_L59-74_
- desc: Interface for transforms applied to documents.
- L62 _public prototype_ `virtual ~IDocumentTransform() = default;`
- L65 _public prototype_ `virtual bool Transform(FDocumentHandle InDocument) const = 0;` — Return true if InDocument was modified, false otherwise.
- L73 _public prototype_ `virtual bool Transform(FMetasoundFrontendDocument& InOutDocument) const;` — Return true if InDocument was modified, false otherwise. This function is soft deprecated.  It is not pure virtual to grandfather in old transform implementation. Old transforms should be deprecated and rewritten to use the Controller-less API in the interest of better performance and simplicity.

#### class `Metasound::Frontend::IGraphTransform`  
`class UE_DEPRECATED(5.8, "Use IBuilderTransform or similar instead") IGraphTransform`  
_L76-82_
- L79 _public prototype_ `virtual ~IGraphTransform() = default;`
- L81 _public prototype_ `virtual bool Transform(FMetasoundFrontendGraph& InOutGraph) const = 0;`

#### class `Metasound::Frontend::INodeTransform`  
`class UE_DEPRECATED(5.8, "Use IBuilderTransform or similar instead") INodeTransform`  
_L85-91_
- desc: Interface for transforming a node.
- L88 _public prototype_ `virtual ~INodeTransform() = default;`
- L90 _public prototype_ `virtual bool Transform(const FGuid& InNodeID, FMetaSoundFrontendDocumentBuilder& OutBuilder) const;`

#### class `Metasound::Frontend::FModifyRootGraphInterfaces`  
`class FModifyRootGraphInterfaces : public IDocumentTransform`  
_L94-151_
- inherits: `IDocumentTransform`
- desc: Adds or swaps document members (inputs, outputs) and removing any document members where necessary and adding those missing.
- L97 _public prototype_ `FModifyRootGraphInterfaces(const TArray<FMetasoundFrontendInterface>& InInterfacesToRemove, const TArray<FMetasoundFrontendInterface>& InInterfacesToAdd);`
- L98 _public prototype_ `FModifyRootGraphInterfaces(const TArray<FMetasoundFrontendVersion>& InInterfaceVersionsToRemove, const TArray<FMetasoundFrontendVersion>& InInterfaceVersionsToAdd);`
- L103 _public prototype_ `void SetDefaultNodeLocations(bool bInSetDefaultNodeLocations);` — Whether or not to propagate node locations to new members. Setting to false results in members not having a default physical location in the editor graph.
- L109 _public prototype_ `void SetNamePairingFunction(const TFunction<bool(FName, FName)>& InNamePairingFunction);` — Override function used to match removed members with added members, allowing transform to preserve connections made between removed interface members & new interface members that may be related but not be named the same.
- L111 _public prototype_ `virtual bool Transform(FDocumentHandle InDocument) const override;`
- L112 _public prototype_ `virtual bool Transform(FMetasoundFrontendDocument& InOutDocument) const override;`
- L115 _private prototype_ `bool AddMissingVertices(FGraphHandle GraphHandle) const;`
- L116 _private prototype_ `void Init(const TFunction<bool(FName, FName)>* InNamePairingFunction = nullptr);`
- L117 _private prototype_ `bool SwapPairedVertices(FGraphHandle GraphHandle) const;`
- L118 _private prototype_ `bool RemoveUnsupportedVertices(FGraphHandle GraphHandle) const;`
- L119 _private prototype_ `bool UpdateInterfacesInternal(FDocumentHandle DocumentHandle) const;`
- L122 _private prototype_ `void UpdateAddedVertexNodePositions(FGraphHandle GraphHandle) const;`
- L124 _private member_ `bool bSetDefaultNodeLocations = true;`
- L127 _private member_ `TArray<FMetasoundFrontendInterface> InterfacesToRemove;`
- L128 _private member_ `TArray<FMetasoundFrontendInterface> InterfacesToAdd;`
- L130 _private typedef_ `using FVertexPair = TTuple<FMetasoundFrontendClassVertex, FMetasoundFrontendClassVertex>;`
- L131 _private member_ `TArray<FVertexPair> PairedInputs;`
- L132 _private member_ `TArray<FVertexPair> PairedOutputs;`
- L146 _private member_ `TArray<FInputData> InputsToAdd;`
- L147 _private member_ `TArray<FMetasoundFrontendClassInput> InputsToRemove;`
- L148 _private member_ `TArray<FOutputData> OutputsToAdd;`
- L149 _private member_ `TArray<FMetasoundFrontendClassOutput> OutputsToRemove;`

#### struct `Metasound::Frontend::FModifyRootGraphInterfaces::FInputData`  
`struct FInputData`  
_L134-138_
- L136 _public member_ `FMetasoundFrontendClassInput Input;`
- L137 _public member_ `const FMetasoundFrontendInterface* InputInterface = nullptr;`

#### struct `Metasound::Frontend::FModifyRootGraphInterfaces::FOutputData`  
`struct FOutputData`  
_L140-144_
- L142 _public member_ `FMetasoundFrontendClassOutput Output;`
- L143 _public member_ `const FMetasoundFrontendInterface* OutputInterface = nullptr;`

#### class `Metasound::Frontend::FUpdateRootGraphInterface`  
`class FUpdateRootGraphInterface : public IDocumentTransform`  
_L153-162_
- inherits: `IDocumentTransform`
- L156 _public function_ `FUpdateRootGraphInterface(const FMetasoundFrontendVersion& InInterfaceVersion, const FString& InOwningAssetName=FString(TEXT("Unknown")))`
- L161 _public function_ `virtual bool Transform(FDocumentHandle InDocument) const override` — `UE_DEPRECATED(5.5, "RootGraph update is now handled privately by internal MetaSound asset management")`

#### class `Metasound::Frontend::FRebuildPresetRootGraph`  
`class FRebuildPresetRootGraph : public IDocumentTransform`  
_L167-217_
- inherits: `IDocumentTransform`
- desc: Completely rebuilds the graph connecting a preset's inputs to the reference (parent) document's root graph. It maintains previously set input values entered upon the preset's wrapping graph.
- L174 _public function_ `FRebuildPresetRootGraph(FConstDocumentHandle InReferencedDocument) : ParentBuilder(nullptr)` — `UE_DEPRECATED(5.7, "Use the constructor which takes a FMetaSoundFrontendDocumentBuilder")` — Create transform. @param InReferenceDocument - The document containing the wrapped MetaSound graph.
- L179 _public function_ `FRebuildPresetRootGraph(const FMetaSoundFrontendDocumentBuilder& InParentDocumentBuilder) : ParentBuilder(&InParentDocumentBuilder)`
- L185 _public prototype_ `FRebuildPresetRootGraph(const FMetasoundFrontendDocument& InReferencedDocument);` — `UE_DEPRECATED(5.7, "Use Transform which takes in a document builder.")`
- L188 _public prototype_ `virtual bool Transform(FDocumentHandle InDocument) const override;` — `UE_DEPRECATED(5.7, "Use Transform which takes in a document builder.")`
- L191 _public prototype_ `virtual bool Transform(FMetasoundFrontendDocument& InOutDocument) const override;` — `UE_DEPRECATED(5.7, "Use Transform which takes in a document builder.")`
- L193 _public prototype_ `bool Transform(FMetaSoundFrontendDocumentBuilder& InOutBuilderToTransform) const;`
- L199 _private prototype_ `TArray<FMetasoundFrontendClassInput> GenerateRequiredClassInputs(FMetaSoundFrontendDocumentBuilder& InDocumentToTransformBuilder) const;` — Get the class inputs needed for this preset. Input literals set on the preset graph will be used if they are set as overriding the default from the parent graph.
- L202 _private prototype_ `TArray<FMetasoundFrontendClassOutput> GenerateRequiredClassOutputs(FMetaSoundFrontendDocumentBuilder& InDocumentToTransformBuilder) const;` — Get the class Outputs needed for this preset.
- L205 _private prototype_ `void AddAndConnectInputs(const FMetaSoundFrontendPresetTemplate& PresetTemplate, const TArray<FMetasoundFrontendClassInput>& InClassInputs, FMetaSoundFrontendDocumentBuilder& InOutBuilderToTransform, const FGuid& InReferencedNodeID) const;` — Add inputs to parent graph and connect to wrapped graph node.
- L208 _private prototype_ `void AddAndConnectOutputs(const TArray<FMetasoundFrontendClassOutput>& InClassOutputs, FMetaSoundFrontendDocumentBuilder& InOutBuilderToTransform, const FGuid& InReferencedNodeID) const;` — Add outputs to parent graph and connect to wrapped graph node.
- L211 _private typedef_ `using FMemberIDToMetadataMap = TMap<FGuid, TObjectPtr<UMetaSoundFrontendMemberMetadata>>;`
- L212 _private prototype_ `void AddMemberMetadata(const FMemberIDToMetadataMap& InCachedMemberMetadata, FMetaSoundFrontendDocumentBuilder& InOutBuilderToTransform) const;`
- L213 _private prototype_ `FMemberIDToMetadataMap CacheMemberMetadata(const FMetaSoundFrontendPresetTemplate& PresetTemplate, FMetaSoundFrontendDocumentBuilder& InOutBuilderToTransform) const;`
- L216 _private member_ `const FMetaSoundFrontendDocumentBuilder* ParentBuilder = nullptr;`

#### class `Metasound::Frontend::FAutoUpdateRootGraph`  
`class FAutoUpdateRootGraph`  
_L223-255_
- desc: Automatically updates all nodes and respective dependencies in graph where newer versions exist in the loaded MetaSound Class Node Registry.
- L231 _public function_ `FAutoUpdateRootGraph(FString&& InDebugAssetPath, bool bInLogWarningOnDroppedConnection) : DebugAssetPath(MoveTemp(InDebugAssetPath)) , bLogWarningOnDroppedConnection(bInLogWarningOnDroppedConnection)` — Construct an AutoUpdate transform @param InDebugAssetPath - Asset path used for debug logs on warnings and errors. @param bInLogWarningOnDroppedConnections - If true, warnings will be logged if a node update results in a dropped connection.
- L238 _public prototype_ `bool Transform(FDocumentHandle InDocument);` — `UE_DEPRECATED(5.7, "Use Transform which takes in a document builder.")`
- L240 _public prototype_ `bool Transform(FMetaSoundFrontendDocumentBuilder& InOutBuilderToTransform);`
- L241 _public prototype_ `static bool CanAutoUpdate(const FMetaSoundFrontendDocumentBuilder& InOutBuilderToTransform, const FGuid& InNodeID, const FGuid& InPageID);`
- L244 _private prototype_ `bool UpdateExternalDependencies(FMetaSoundFrontendDocumentBuilder& InOutBuilderToTransform);` — Helper function to go through external nodes and update dependencies
- L246 _private prototype_ `static bool HasInterfaceUpdate(const FMetaSoundFrontendDocumentBuilder& InOutBuilderToTransform, const FGuid& InNodeID, const FGuid& InPageID);`
- L247 _private prototype_ `static bool HasAutoAppliedCustomUpdateTransform(const FMetasoundFrontendClassName& InClassName, int32 InMajorVersion);`
- L250 _private prototype_ `bool ProcessMinorVersionUpdate(FMetaSoundFrontendDocumentBuilder& InOutBuilderToTransform, const FNodeClassRegistryKey& InCurrentNodeKey, const FNodeClassRegistryKey& InHighestRegistryVersionKey, const FGuid& InNodeID, const FGuid& InPageID, FString* InOutAutoUpdateReasonString=nullptr);` — Process various updates. Returns true if an update was applied.
- L251 _private prototype_ `bool ProcessMajorVersionUpdate(FMetaSoundFrontendDocumentBuilder& InOutBuilderToTransform, const FNodeClassRegistryKey& InCurrentNodeRegistryKey, const FGuid& InNodeID, const FGuid& InPageID, FNodeClassRegistryKey& OutNewNodeRegistryKey);`
- L253 _private member_ `const FString DebugAssetPath;`
- L254 _private member_ `bool bLogWarningOnDroppedConnection;`

#### class `Metasound::Frontend::FRenameRootGraphClass`  
`class FRenameRootGraphClass : public IDocumentTransform`  
_L259-287_
- inherits: `IDocumentTransform`
- desc: Sets the document's graph class, optionally updating the namespace and variant.
- L261 _private member_ `const FMetasoundFrontendClassName NewClassName;`
- L265 _public function_ `static bool Generate(FDocumentHandle InDocument, const FGuid& InGuid, const FName Namespace = { }, const FName Variant = { })` — `UE_DEPRECATED(5.5, "Use FMetasoundFrontendDocumentBuilder::GenerateNewClassName instead")`
- L271 _public function_ `static bool Generate(FMetasoundFrontendDocument& InDocument, const FGuid& InGuid, const FName Namespace = { }, const FName Variant = { })` — `UE_DEPRECATED(5.5, "Use FMetasoundFrontendDocumentBuilder::GenerateNewClassName instead")`
- L277 _public function_ `FRenameRootGraphClass(const FMetasoundFrontendClassName InClassName) : NewClassName(InClassName)` — `UE_DEPRECATED(5.5, "Use FMetasoundFrontendDocumentBuilder::GenerateNewClassName instead")`
- L283 _public prototype_ `bool Transform(FDocumentHandle InDocument) const override;` — `UE_DEPRECATED(5.5, "Use FMetasoundFrontendDocumentBuilder::GenerateNewClassName instead")`
- L286 _public prototype_ `bool Transform(FMetasoundFrontendDocument& InOutDocument) const override;` — `UE_DEPRECATED(5.5, "Use FMetasoundFrontendDocumentBuilder::GenerateNewClassName instead")`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L22 _macro_ `#define METASOUND_VERSIONING_LOG(Verbosity, Format, ...) if (DocumentTransform::bVersioningLoggingEnabled) { UE_LOG(LogMetaSound, Verbosity, Format, ##__VA_ARGS__); }`
- L24 _namespace_ `namespace Metasound`
- L24 _namespace_ `namespace Frontend` (scope `Metasound`)
- L26 _namespace_ `namespace DocumentTransform` (scope `Metasound::Frontend`)
- L28 _externvar_ `extern bool bVersioningLoggingEnabled;` (scope `Metasound::Frontend::DocumentTransform`)
- L31 _typedef_ `using FGetNodeDisplayNameProjection = TFunction<FText(const FNodeHandle&)>;` (scope `Metasound::Frontend::DocumentTransform`)
- L32 _typedef_ `using FGetNodeDisplayNameProjectionRef = TFunctionRef<FText(const FNodeHandle&)>;` (scope `Metasound::Frontend::DocumentTransform`)
- L34 _prototype_ `bool GetVersioningLoggingEnabled();` (scope `Metasound::Frontend::DocumentTransform`)
- L35 _prototype_ `void SetVersioningLoggingEnabled(bool bIsEnabled);` (scope `Metasound::Frontend::DocumentTransform`)
- L36 _prototype_ `void RegisterNodeDisplayNameProjection(FGetNodeDisplayNameProjection&& InNameProjection);` (scope `Metasound::Frontend::DocumentTransform`)
- L37 _prototype_ `FGetNodeDisplayNameProjectionRef GetNodeDisplayNameProjection();` (scope `Metasound::Frontend::DocumentTransform`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundInputNode.h` (Public)


#### class `Metasound::MetasoundInputNodePrivate::FNonExecutableInputOperatorBase`  
`class FNonExecutableInputOperatorBase : public IOperator`  
_L23-38_
- inherits: `IOperator`
- L26 _public prototype_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override;`
- L27 _public prototype_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override;`
- L29 _public prototype_ `virtual IOperator::FExecuteFunction GetExecuteFunction() override;`
- L30 _public prototype_ `virtual IOperator::FPostExecuteFunction GetPostExecuteFunction() override;`
- L31 _public prototype_ `virtual IOperator::FResetFunction GetResetFunction() override;`
- L34 _protected prototype_ `FNonExecutableInputOperatorBase(const FVertexName& InVertexName, FAnyDataReference&& InDataRef);`
- L36 _protected member_ `FVertexName VertexName;`
- L37 _protected member_ `FAnyDataReference DataRef;`

#### class `Metasound::MetasoundInputNodePrivate::FNonExecutableInputPassThroughOperator`  
`class FNonExecutableInputPassThroughOperator : public FNonExecutableInputOperatorBase`  
_L41-55_
- inherits: `FNonExecutableInputOperatorBase`
- L45 _public function_ `template<typename DataType> FNonExecutableInputPassThroughOperator(const FVertexName& InVertexName, const TDataReadReference<DataType>& InDataRef) : FNonExecutableInputOperatorBase(InVertexName, FAnyDataReference{InDataRef})`
- L51 _public function_ `template<typename DataType> FNonExecutableInputPassThroughOperator(const FVertexName& InVertexName, const TDataWriteReference<DataType>& InDataRef) : FNonExecutableInputPassThroughOperator(InVertexName, TDataReadReference<DataType>(InDataRef))`

#### class `Metasound::MetasoundInputNodePrivate::TInputValueOperator`  
`template<typename DataType> class TInputValueOperator : public FNonExecutableInputOperatorBase`  
_L60-80_
- inherits: `FNonExecutableInputOperatorBase`
- desc: TInputValueOperator provides an input for value references.
- L66 _public function_ `explicit TInputValueOperator(const FName& InVertexName, const TDataValueReference<DataType>& InValueRef) : FNonExecutableInputOperatorBase(InVertexName, FAnyDataReference{InValueRef})` — Construct an TInputValueOperator with the name of the vertex and the value reference associated with input.
- L71 _public function_ `TInputValueOperator(const FVertexName& InVertexName, const FOperatorSettings& InSettings, const FLiteral& InLiteral) : FNonExecutableInputOperatorBase(InVertexName, FAnyDataReference{TDataValueReferenceLiteralFactory<DataType>::CreateExplicitArgs(InSettings, InLiteral)})`
- L76 _public function_ `TInputValueOperator(const FVertexName& InVertexName, const FOperatorSettings& InSettings, const FInputVertexInterfaceData& InInterfaceData) : FNonExecutableInputOperatorBase(InVertexName, FAnyDataReference{InInterfaceData.GetOrCreateDefaultDataValueReference<DataType>(InVertexName, InSettings)})`

#### class `Metasound::MetasoundInputNodePrivate::TPostExecutableInputOperator`  
`template<typename DataType> class TPostExecutableInputOperator : public IOperator`  
_L83-165_
- inherits: `IOperator`
- L88 _public typedef_ `using FDataWriteReference = TDataWriteReference<DataType>;`
- L90 _public function_ `TPostExecutableInputOperator(const FVertexName& InDataReferenceName, TDataWriteReference<DataType> InValue) : DataReferenceName(InDataReferenceName) , DataRef(InValue)`
- L96 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override`
- L101 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override`
- L106 _public function_ `virtual FExecuteFunction GetExecuteFunction() override`
- L111 _public function_ `virtual FPostExecuteFunction GetPostExecuteFunction() override`
- L126 _public function_ `virtual FResetFunction GetResetFunction() override`
- L142 _protected function_ `static void NoOpReset(IOperator* InOperator, const IOperator::FResetParams& InParams)`
- L149 _protected function_ `static void PostExecute(IOperator* InOperator)`
- L163 _protected member_ `FVertexName DataReferenceName;`
- L164 _protected member_ `FAnyDataReference DataRef;`

#### class `Metasound::MetasoundInputNodePrivate::TResetablePostExecutableInputOperator`  
`template<typename DataType> class TResetablePostExecutableInputOperator : public TPostExecutableInputOperator<DataType>`  
_L172-222_
- inherits: `TPostExecutableInputOperator<DataType>`
- desc: To reset the state of a PostExecutable input operator, we need to reset the data to it's original state. In order to do that, the FLiteral is stored on the operator so that it can be used to reinitialize the data when the operator reset.
- L175 _public typedef_ `using FDataWriteReference = TDataWriteReference<DataType>;`
- L176 _public typedef_ `using FDataWriteReferenceFactory = TDataWriteReferenceLiteralFactory<DataType>;`
- L179 _public function_ `TResetablePostExecutableInputOperator(const FVertexName& InDataReferenceName, const FOperatorSettings& InSettings, const FLiteral& InLiteral) : TPostExecutableInputOperator<DataType>(InDataReferenceName, FDataWriteReferenceFactory::CreateExplicitArgs(InSettings, InLiteral)) , Literal(InLiteral)`
- L185 _public function_ `TResetablePostExecutableInputOperator(const FVertexName& InDataReferenceName, const FOperatorSettings& InSettings, const FInputVertexInterfaceData& InData) : TPostExecutableInputOperator<DataType>(InDataReferenceName, InData.GetOrCreateDefaultDataWriteReference<DataType>(InDataReferenceName, InSettings)) , Literal(InData.GetVertex(InDataReferenceName).GetDefaultLiteral())`
- L192 _public function_ `virtual IOperator::FResetFunction GetResetFunction() override`
- L207 _private function_ `static void Reset(IOperator* InOperator, const IOperator::FResetParams& InParams)`
- L221 _private member_ `FLiteral Literal;`

#### class `Metasound::MetasoundInputNodePrivate::TInputNodeOperatorFactory`  
`template<typename DataType, EVertexAccessType VertexAccess=EVertexAccessType::Reference> class TInputNodeOperatorFactory : public IOperatorFactory`  
_L253-311_
- inherits: `IOperatorFactory`
- desc: Factory for creating input operators.
- L255 _private member_ `static constexpr bool bIsReferenceVertexAccess = VertexAccess == EVertexAccessType::Reference;`
- L256 _private member_ `static constexpr bool bIsValueVertexAccess = VertexAccess == EVertexAccessType::Value;`
- L261 _private typedef_ `using FPassThroughDataReference = std::conditional_t<bIsReferenceVertexAccess, TDataReadReference<DataType>, TDataValueReference<DataType>>;` — Choose which data reference type is created based on template parameters
- L264 _private function_ `FPassThroughDataReference CreatePassThroughDataReference(const FAnyDataReference& InRef)` — Return correct data reference type based on vertex access type for pass through scenario.
- L281 _public function_ `explicit TInputNodeOperatorFactory(const FVertexName& InVertexName) : VertexName(InVertexName)`
- L286 _public function_ `virtual TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults) override`
- L310 _private member_ `FVertexName VertexName;`

#### class `Metasound::FInputNode`  
`class FInputNode : public FBasicNode`  
_L315-348_
- inherits: `FBasicNode`
- desc: FInputNode represents an input to a metasound graph.
- L317 _private member_ `static FLazyName ConstructorVariant;`
- L320 _private prototype_ `static FName GetVariantName(EVertexAccessType InVertexAccess);` — Use Variant names to differentiate between normal input nodes and constructor input nodes.
- L322 _private prototype_ `static FVertexInterface CreateVertexInterface(const FVertexName& InVertexName, const FName& InDataTypeName, EVertexAccessType InVertexAccess, const FLiteral& InLiteral);`
- L326 _protected prototype_ `static FVertexInterface CreateDefaultVertexInterface(const FVertexName& InVertexName, const FName& InDataTypeName, EVertexAccessType InVertexAccess, const FLiteral* InDefaultLiteral=nullptr);`
- L328 _protected prototype_ `explicit FInputNode(FOperatorFactorySharedRef InFactory, FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InClassMetadata);`
- L331 _public prototype_ `static FText GetInputDescription();`
- L333 _public prototype_ `static FNodeClassMetadata GetNodeMetadata(const FVertexName& InVertexName, const FName& InDataTypeName, EVertexAccessType InVertexAccess);` — `UE_DEPRECATED(5.6, "Use CreateNodeClassMetadata(...) instead")`
- L334 _public prototype_ `static FNodeClassMetadata CreateNodeClassMetadata(const FVertexName& InVertexName, const FName& InDataTypeName, EVertexAccessType InVertexAccess);`
- L338 _public prototype_ `explicit FInputNode(FInputNodeConstructorParams&& InParams, const FName& InDataTypeName, EVertexAccessType InVertexAccess, FOperatorFactorySharedRef InFactory);` — Construct a TInputNode using the TInputOperatorLiteralFactory<> and moving InParam to the TInputOperatorLiteralFactory constructor.
- L342 _public prototype_ `const FVertexName& GetVertexName() const;` — `UE_DEPRECATED(5.6, "You can find the vertex name by inspecting the FVertexInterface.")`
- L344 _public prototype_ `virtual TSharedRef<IOperatorFactory, ESPMode::ThreadSafe> GetDefaultOperatorFactory() const override;`
- L347 _private member_ `FOperatorFactorySharedRef Factory;`

#### class `Metasound::TInputNode`  
`template<typename DataType, EVertexAccessType VertexAccess=EVertexAccessType::Reference> class TInputNode : public FInputNode`  
_L353-388_
- inherits: `FInputNode`
- desc: TInputNode represents an input to a metasound graph.
- L355 _private member_ `static constexpr bool bIsConstructorInput = VertexAccess == EVertexAccessType::Value;`
- L356 _private member_ `static constexpr bool bIsSupportedConstructorInput = TIsConstructorVertexSupported<DataType>::Value && bIsConstructorInput;`
- L357 _private member_ `static constexpr bool bIsReferenceInput = VertexAccess == EVertexAccessType::Reference;`
- L358 _private member_ `static constexpr bool bIsSupportedReferenceInput = TLiteralTraits<DataType>::bIsParsableFromAnyLiteralType && bIsReferenceInput;`
- L360 _private member_ `static constexpr bool bIsSupportedInput = bIsSupportedConstructorInput || bIsSupportedReferenceInput;`
- L364 _public member_ `static constexpr bool bCanRegister = bIsSupportedInput;` — If true, this node can be instantiated by the Frontend.
- L367 _public function_ `static FNodeClassMetadata GetNodeInfo(const FVertexName& InVertexName)` — `UE_DEPRECATED(5.6, "Use CreateNodeClassMetadata(...) instead")`
- L372 _public function_ `static FNodeClassMetadata CreateNodeClassMetadata(const FVertexName& InVertexName)`
- L379 _public function_ `explicit TInputNode(FInputNodeConstructorParams&& InParams) : FInputNode(MoveTemp(InParams), GetMetasoundDataTypeName<DataType>(), VertexAccess, MakeShared<MetasoundInputNodePrivate::TInputNodeOperatorFactory<DataType, VertexAccess>>(InParams.VertexName))` — Construct a TInputNode using the TInputOperatorLiteralFactory<> and moving InParam to the TInputOperatorLiteralFactory constructor.
- L384 _public function_ `explicit TInputNode(const FVertexName& InVertexName, FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InClassMetadata) : FInputNode(MakeShared<MetasoundInputNodePrivate::TInputNodeOperatorFactory<DataType, VertexAccess>>(InVertexName), MoveTemp(InNodeData), MoveTemp(InClassMetadata))`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L19 _namespace_ `namespace Metasound`
- L21 _namespace_ `namespace MetasoundInputNodePrivate` (scope `Metasound`)
- L151 _typedef_ `using FPostExecutableInputOperator = TPostExecutableInputOperator<DataType>;` (scope `Metasound::MetasoundInputNodePrivate::TPostExecutableInputOperator::PostExecute`)
- L209 _typedef_ `using FResetablePostExecutableInputOperator = TResetablePostExecutableInputOperator<DataType>;` (scope `Metasound::MetasoundInputNodePrivate::TResetablePostExecutableInputOperator::Reset`)
- L226 _typedef_ `template<typename DataType, EVertexAccessType VertexAccess=EVertexAccessType::Reference> using TNonOwningInputOperator = std::conditional_t< TPostExecutableDataType<DataType>::bIsPostExecutable, TPostExecutableInputOperator<DataType>,` (scope `Metasound::MetasoundInputNodePrivate`) — Non owning input operator that may need execution.
- L235 _typedef_ `template<typename DataType, EVertexAccessType VertexAccess=EVertexAccessType::Reference> using TInputOperator = std::conditional_t< VertexAccess == EVertexAccessType::Value || !TPostExecutableDataType<DataType>::bIsPostExecutable, MetasoundInputNodePrivate::TInputValueOperator<DataType>,` (scope `Metasound`) — Owning input operator that may need execution.
- L243 _typedef_ `template<typename DataType, EVertexAccessType VertexAccess=EVertexAccessType::Reference> using TPassThroughOperator = std::conditional_t< VertexAccess == EVertexAccessType::Value, MetasoundInputNodePrivate::TInputValueOperator<DataType>, MetasoundInputNodePrivate::FNonExecutableInputPassThroughOperator >;` (scope `Metasound`) — Choose pass through operator based upon data type and access type
- L249 _namespace_ `namespace MetasoundInputNodePrivate` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundLiteralNode.h` (Public)


#### class `Metasound::TLiteralOperator`  
`template<typename DataType> class UE_DEPRECATED(5.3, "The TLiteralOperator will be removed.") TLiteralOperator : public FNoOpOperator`  
_L26-50_
- inherits: `FNoOpOperator`
- L31 _public function_ `TLiteralOperator(TDataValueReference<DataType> InValue) : Value (InValue)`
- L36 _public prototype_ `virtual ~TLiteralOperator() = default;`
- L38 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L42 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData) override`
- L49 _private member_ `TDataValueReference<DataType> Value;`

#### class `Metasound::TExecutableLiteralOperator`  
`template<typename DataType> class UE_DEPRECATED(5.3, "The TExecutableLiteralOperator will be removed.") TExecutableLiteralOperator : public TExecutableOperator<TExecutableLiteralOperator<DataType>>`  
_L58-114_
- inherits: `TExecutableOperator<TExecutableLiteralOperator<DataType>>`
- desc: TExecutableLiteralOperator is used for executable types. The majority of literals are constant values, but executable data types cannot be constant values. Note: this is supporting for FTrigger literals which are deprecated.
- L63 _public typedef_ `using FDataWriteReference = TDataWriteReference<DataType>;`
- L65 _public function_ `TExecutableLiteralOperator(const FOperatorSettings& InSettings, const FLiteral& InLiteral)`
- L74 _public prototype_ `virtual ~TExecutableLiteralOperator() = default;`
- L76 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`
- L80 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData) override`
- L86 _public function_ `virtual FDataReferenceCollection GetInputs() const override`
- L92 _public function_ `virtual FDataReferenceCollection GetOutputs() const override`
- L100 _public function_ `void Execute()`
- L105 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L111 _private member_ `FLiteral Literal;`
- L112 _private member_ `FDataWriteReference InputValue;`
- L113 _private member_ `FDataWriteReference OutputValue;`

#### class `Metasound::TLiteralOperatorLiteralFactory`  
`template<typename DataType> class TLiteralOperatorLiteralFactory : public IOperatorFactory`  
_L119-147_
- inherits: `IOperatorFactory`
- desc: TLiteralOperatorLiteralFactory creates an input by passing it a literal.
- L123 _public typedef_ `using FDataWriteReference = TDataWriteReference<DataType>;`
- L125 _public function_ `TLiteralOperatorLiteralFactory(FLiteral&& InInitParam) : InitParam(MoveTemp(InInitParam))`
- L130 _public prototype_ `virtual TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults) override;`
- L146 _private member_ `FLiteral InitParam;`
- L205 _function_ `template<typename DataType> TUniquePtr<IOperator> TLiteralOperatorLiteralFactory<DataType>::CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`

#### class `Metasound::TLiteralOperatorLiteralFactory::FLiteralOperator`  
`class FLiteralOperator : public TInputOperator<DataType>`  
_L134-144_
- inherits: `TInputOperator<DataType>`
- L139 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override`

#### class `Metasound::FLiteralNode`  
`class FLiteralNode : public FNode`  
_L150-168_
- inherits: `FNode`
- desc: TLiteralNode represents a variable within a metasound graph.
- L153 _protected prototype_ `static FVertexInterface CreateVertexInterface(const FName& InDataTypeName, EVertexAccessType InAccessType);`
- L157 _public prototype_ `static FNodeClassMetadata GetNodeMetadata(const FName& InDataTypeName, EVertexAccessType InAccessType);`
- L159 _public prototype_ `FLiteralNode(const FVertexName& InInstanceName, const FGuid& InInstanceID, const FName& InDataTypeName, EVertexAccessType InAccessType, FOperatorFactorySharedRef InFactory);`
- L161 _public prototype_ `virtual const FVertexInterface& GetVertexInterface() const override;`
- L163 _public prototype_ `virtual TSharedRef<IOperatorFactory, ESPMode::ThreadSafe> GetDefaultOperatorFactory() const override;`
- L166 _private member_ `FVertexInterface Interface;`
- L167 _private member_ `FOperatorFactorySharedRef Factory;`

#### class `Metasound::TLiteralNode`  
`template<typename DataType> class TLiteralNode : public FLiteralNode`  
_L172-202_
- inherits: `FLiteralNode`
- desc: TLiteralNode represents a variable within a metasound graph.
- L176 _private member_ `static constexpr bool bIsExecutableDataType = TExecutableDataType<DataType>::bIsExecutable;` — Executable data types handle Triggers which need to be advanced every block.
- L177 _private member_ `static constexpr bool bIsPostExecutableDataType = TPostExecutableDataType<DataType>::bIsPostExecutable;`
- L180 _private member_ `static constexpr EVertexAccessType AccessType = (bIsExecutableDataType || bIsPostExecutableDataType) ? EVertexAccessType::Reference : EVertexAccessType::Value;` — If the data type is executable, we treat it as a reference since it is non-const
- L185 _public function_ `static FVertexInterface DeclareVertexInterface()` — `UE_DEPRECATED(5.3, "Use the default interface on the node class metadata")`
- L190 _public function_ `static FNodeClassMetadata GetNodeInfo()`
- L197 _public function_ `explicit TLiteralNode(const FVertexName& InInstanceName, const FGuid& InInstanceID, FLiteral&& InParam) : FLiteralNode(InInstanceName, InInstanceID, GetMetasoundDataTypeName<DataType>(), AccessType, MakeOperatorFactoryRef<TLiteralOperatorLiteralFactory<DataType>>(MoveTemp(InParam)))` — Construct a TLiteralNode using the TLiteralOperatorLiteralFactory<> and moving InParam to the TLiteralOperatorLiteralFactory constructor.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L16 _macro_ `#define LOCTEXT_NAMESPACE "MetasoundLiteralNode"`
- L18 _namespace_ `namespace Metasound`
- L20 _namespace_ `namespace LiteralNodeNames` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundNodeConstructorParams.h` (Public)


#### struct `Metasound::FDefaultNamedVertexNodeConstructorParams`  
`struct FDefaultNamedVertexNodeConstructorParams`  
_L11-17_
- desc: Base implementation for NodeConstructorCallbacks
- L14 _public member_ `FVertexName NodeName;` — the instance name and name of the specific connection that should be used.
- L15 _public member_ `FGuid InstanceID;`
- L16 _public member_ `FVertexName VertexName;`

#### struct `Metasound::FDefaultNamedVertexWithLiteralNodeConstructorParams`  
`struct FDefaultNamedVertexWithLiteralNodeConstructorParams`  
_L19-26_
- L22 _public member_ `FVertexName NodeName;` — the instance name and name of the specific connection that should be used.
- L23 _public member_ `FGuid InstanceID;`
- L24 _public member_ `FVertexName VertexName;`
- L25 _public member_ `FLiteral InitParam = FLiteral::CreateInvalid();`

#### struct `Metasound::FDefaultLiteralNodeConstructorParams`  
`struct FDefaultLiteralNodeConstructorParams`  
_L28-33_
- L30 _public member_ `FVertexName NodeName;`
- L31 _public member_ `FGuid InstanceID;`
- L32 _public member_ `FLiteral Literal = FLiteral::CreateInvalid();`

#### struct `Metasound::FInputNodeConstructorParams`  
`struct FInputNodeConstructorParams`  
_L35-48_
- L38 _public member_ `FVertexName NodeName;` — the instance name and name of the specific connection that should be used.
- L39 _public member_ `FGuid InstanceID;`
- L40 _public member_ `FVertexName VertexName;`
- L41 _public member_ `FLiteral InitParam = FLiteral::CreateInvalid();`
- L44 _public member_ `FName PolymorphicTypeName;` — If defined this is the polymorphic type name to use.
- L47 _public member_ `bool bEnableTransmission = false;` — `UE_DEPRECATED(5.3, "Transmission is no longer enabled on input nodes. In order set values on a MetaSound input, access them through the bound FInputVertexInterfaceData.")`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`
- L50 _typedef_ `using FOutputNodeConstructorParams = FDefaultNamedVertexNodeConstructorParams;` (scope `Metasound`)
- L51 _typedef_ `using FLiteralNodeConstructorParams = FDefaultLiteralNodeConstructorParams;` (scope `Metasound`)
- L52 _typedef_ `using FVariableNodeConstructorParams = FDefaultLiteralNodeConstructorParams;` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundNodeRegistrationMacro.h` (Public)


#### class `Metasound::Frontend::NodeRegistrationPrivate::FNodeRegistryEntryBase`  
`class FNodeRegistryEntryBase : public INodeClassRegistryEntry`  
_L34-70_
- inherits: `INodeClassRegistryEntry`
- desc: Utilize base class to reduce template bloat in TNodeRegistryEntry
- L37 _public prototype_ `FNodeRegistryEntryBase(const Metasound::FNodeClassMetadata& InMetadata, const FModuleInfo& InOwningModuleInfo);`
- L39 _public prototype_ `virtual ~FNodeRegistryEntryBase() = default;`
- L41 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendClass() const override;`
- L43 _public prototype_ `virtual const TSet<FMetasoundFrontendVersion>* GetImplementedInterfaces() const override;`
- L45 _public prototype_ `virtual FVertexInterface GetDefaultVertexInterface() const override;`
- L47 _public prototype_ `virtual const FClassInterface& GetClassInterface() const override;`
- L49 _public prototype_ `virtual TInstancedStruct<FMetaSoundFrontendNodeConfiguration> CreateFrontendNodeConfiguration() const override;`
- L50 _public prototype_ `virtual bool IsCompatibleNodeConfiguration(TConstStructView<FMetaSoundFrontendNodeConfiguration> InNodeConfiguration) const override;`
- L53 _public prototype_ `virtual FName GetPluginName() const override;`
- L55 _public prototype_ `virtual FName GetModuleName() const override;`
- L60 _protected prototype_ `TSharedRef<const FNodeClassMetadata> GetNodeClassMetadata() const;`
- L63 _private member_ `TSharedRef<FNodeClassMetadata> ClassMetadata;`
- L64 _private member_ `FMetasoundFrontendClass FrontendClass;`
- L67 _private member_ `FName PluginName;`
- L68 _private member_ `FName ModuleName;`

#### class `Metasound::Frontend::NodeRegistrationPrivate::TNodeRegistryEntryBase`  
`template<typename TNodeType> class TNodeRegistryEntryBase : public FNodeRegistryEntryBase`  
_L73-98_
- inherits: `FNodeRegistryEntryBase`
- L79 _public function_ `virtual TUniquePtr<INode> CreateNode(FNodeData InNodeData) const override`

#### class `Metasound::Frontend::NodeRegistrationPrivate::TNodeRegistryEntry`  
`template<typename NodeType, typename ConfigurationType> class TNodeRegistryEntry : public TNodeRegistryEntryBase<NodeType>`  
_L102-127_
- inherits: `TNodeRegistryEntryBase<NodeType>`
- desc: A node registry entry which also provides a node extension.
- L106 _public function_ `TNodeRegistryEntry(const Metasound::FNodeClassMetadata& InMetadata, const FModuleInfo& InOwningModuleInfo) : TNodeRegistryEntryBase<NodeType>(InMetadata, InOwningModuleInfo)`
- L118 _public function_ `virtual TInstancedStruct<FMetaSoundFrontendNodeConfiguration> CreateFrontendNodeConfiguration() const override`
- L123 _public function_ `virtual bool IsCompatibleNodeConfiguration(TConstStructView<FMetaSoundFrontendNodeConfiguration> InNodeConfiguration) const override`

#### class `Metasound::Frontend::NodeRegistrationPrivate::TNodeRegistryEntry`  
`template<typename NodeType> class TNodeRegistryEntry<NodeType, void> : public TNodeRegistryEntryBase<NodeType>`  
_L131-135_
- inherits: `TNodeRegistryEntryBase<NodeType>`
- desc: A partial template specialization for scenario where no node extension is provided.
- L106 _public function_ `TNodeRegistryEntry(const Metasound::FNodeClassMetadata& InMetadata, const FModuleInfo& InOwningModuleInfo) : TNodeRegistryEntryBase<NodeType>(InMetadata, InOwningModuleInfo)`
- L118 _public function_ `virtual TInstancedStruct<FMetaSoundFrontendNodeConfiguration> CreateFrontendNodeConfiguration() const override`
- L123 _public function_ `virtual bool IsCompatibleNodeConfiguration(TConstStructView<FMetaSoundFrontendNodeConfiguration> InNodeConfiguration) const override`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L25 _macro_ `#define UE_METASOUND_DISABLE_5_6_NODE_REGISTRATION_DEPRECATION_WARNINGS (0)`
- L28 _namespace_ `namespace Metasound`
- L28 _namespace_ `namespace Frontend` (scope `Metasound`)
- L31 _namespace_ `namespace NodeRegistrationPrivate` (scope `Metasound::Frontend`)
- L137 _prototype_ `bool RegisterNodeInternal(TUniquePtr<INodeClassRegistryEntry>&& InEntry);` (scope `Metasound::Frontend::NodeRegistrationPrivate`)
- L141 _function_ `template<typename TNodeType, typename ConfigurationType=void> bool RegisterNode(const FNodeClassMetadata& InMetadata, const FModuleInfo& InOwningModuleInfo)` (scope `Metasound::Frontend`)
- L165 _function_ `bool RegisterNode(const FNodeClassMetadata& InMetadata)` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.7, "Use RegisterNode(...) which provides FModuleInfo")`
- L171 _function_ `template <typename TNodeType, typename ConfigurationType=void> bool RegisterNode(const FModuleInfo& InOwningModuleInfo)` (scope `Metasound::Frontend`)
- L189 _function_ `bool RegisterNode()` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.7, "Use RegisterNode(...) which provides FModuleInfo")`
- L195 _prototype_ `bool UnregisterNode(const FNodeClassRegistryKey& InRegistryKey, const FModuleInfo& InOwningModuleInfo);` (scope `Metasound::Frontend`) — Unregister a node using a registry key.
- L198 _prototype_ `bool UnregisterNode(const FNodeClassMetadata& InMetadata, const FModuleInfo& InOwningModuleInfo);` (scope `Metasound::Frontend`) — Unregister a node using FNodeClassMetadata.
- L202 _function_ `template<typename TNodeType> bool UnregisterNode(const FModuleInfo& InOwningModuleInfo)` (scope `Metasound::Frontend`) — Unregister a node by node template param.
- L218 _function_ `bool UnregisterNode()` (scope `Metasound::Frontend`) — `UE_DEPRECATED(5.7, "Use UnregisterNode(...) which provides FModuleInfo")`
- L224 _namespace_ `namespace Metasound`
- L228 _function_ `bool RegisterNodeWithFrontend()` (scope `Metasound`) — `UE_DEPRECATED(5.6, "Use Frontend::RegisterNode()")`
- L235 _function_ `bool RegisterNodeWithFrontend(const Metasound::FNodeClassMetadata& InMetadata)` (scope `Metasound`) — `UE_DEPRECATED(5.6, "Use Frontend::RegisterNode(const Metasound::FNodeClassMetadata&)")`
- L241 _macro_ `#define METASOUND_REGISTER_NODE_AND_CONFIGURATION(NodeClass, ConfigurationClass) \`
- L247 _macro_ `#define METASOUND_REGISTER_NODE(NodeClass) METASOUND_REGISTER_NODE_AND_CONFIGURATION(NodeClass, void)`
- L253 _macro_ `#define METASOUND_LOCTEXT(KEY, NAME_TEXT) LOCTEXT(KEY, NAME_TEXT)`
- L254 _macro_ `#define METASOUND_LOCTEXT_FORMAT(KEY, NAME_TEXT, ...) FText::Format(LOCTEXT(KEY, NAME_TEXT), __VA_ARGS__)`
- L256 _macro_ `#define METASOUND_LOCTEXT(KEY, NAME_TEXT) FText{}`
- L257 _macro_ `#define METASOUND_LOCTEXT_FORMAT(KEY, NAME_TEXT, ...) FText{}`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundOutputNode.h` (Public)


#### class `Metasound::FMissingOutputNodeInputReferenceError`  
`class FMissingOutputNodeInputReferenceError : public FBuildErrorBase`  
_L34-54_
- inherits: `FBuildErrorBase`
- desc: FMissingOutputNodeInputReferenceError Caused by Output not being able to generate an IOperator instance due to the type requiring an input reference (i.e. it is not default constructable).
- L37 _public function_ `FMissingOutputNodeInputReferenceError(const INode& InNode, const FText& InDataType) : FBuildErrorBase( "MetasoundMissingOutputDataReferenceForTypeError", METASOUND_LOCTEXT_FORMAT("MissingOutputNodeInputReferenceForTypeError", "Missing required output node input reference for type {0}.", InDataType))`
- L45 _public function_ `FMissingOutputNodeInputReferenceError(const INode& InNode) : FBuildErrorBase( "MetasoundMissingOutputDataReferenceError", METASOUND_LOCTEXT("MissingOutputNodeInputReferenceError", "Missing required output node input reference."))`
- L53 _public prototype_ `virtual ~FMissingOutputNodeInputReferenceError() = default;`

#### class `Metasound::FOutputNode`  
`class FOutputNode : public FBasicNode`  
_L56-72_
- inherits: `FBasicNode`
- L59 _public prototype_ `FOutputNode(const FVertexName& InVertexName, FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InClassMetadata);`
- L61 _public prototype_ `static FName GetVariantName(EVertexAccessType InVertexAccessType);`
- L62 _public prototype_ `static FNodeClassMetadata CreateNodeClassMetadata(const FVertexName& InVertexName, const FName& InDataTypeName, EVertexAccessType InVertexAccessType);`
- L63 _public prototype_ `static FVertexInterface CreateVertexInterface(const FVertexName& InVertexName, const FName& InDataTypeName, EVertexAccessType InVertexAccessType);`
- L65 _public prototype_ `virtual TSharedRef<IOperatorFactory, ESPMode::ThreadSafe> GetDefaultOperatorFactory() const override;`
- L68 _protected prototype_ `FOutputNode(const FVertexName& InVertexName, const FGuid& InInstanceID, const FVertexName& InInstanceName, const FName& InDataTypeName, EVertexAccessType InVertexAccessType);`
- L71 _private member_ `TSharedRef<OutputNodePrivate::FOutputOperatorFactory, ESPMode::ThreadSafe> Factory;`

#### class `Metasound::TOutputNode`  
`template<typename DataType, EVertexAccessType VertexAccess=EVertexAccessType::Reference> class TOutputNode : public FOutputNode`  
_L76-88_
- inherits: `FOutputNode`
- desc: Output nodes are used to expose graph data to external entities.
- L79 _public function_ `TOutputNode(const FVertexName& InInstanceName, const FGuid& InInstanceID, const FVertexName& InVertexName) : FOutputNode(InVertexName, InInstanceID, InInstanceName, GetMetasoundDataTypeName<DataType>(), VertexAccess)`
- L84 _public function_ `TOutputNode(const FVertexName& InVertexName, FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InClassMetadata) : FOutputNode(InVertexName, MoveTemp(InNodeData), MoveTemp(InClassMetadata))`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L20 _macro_ `#define LOCTEXT_NAMESPACE "MetasoundGraphCore"`
- L22 _namespace_ `namespace Metasound`
- L24 _namespace_ `namespace OutputNodePrivate` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundOutputStorage.h` (Public)


#### class `Metasound::IOutputStorage`  
`class IOutputStorage`  
_L10-18_
- L13 _public prototype_ `virtual ~IOutputStorage() = default;`
- L15 _public prototype_ `virtual FName GetDataTypeName() const = 0;`
- L17 _public prototype_ `virtual TUniquePtr<IOutputStorage> Clone() const = 0;`

#### class `Metasound::TOutputStorage`  
`template<typename DataType> class TOutputStorage final : public IOutputStorage`  
_L21-56_
- inherits: `IOutputStorage`
- L24 _public function_ `explicit TOutputStorage(const DataType& InData) : Data(InData)`
- L28 _public function_ `virtual FName GetDataTypeName() const override`
- L34 _public function_ `virtual TUniquePtr<IOutputStorage> Clone() const override`
- L39 _public function_ `void Set(const DataType& Value)`
- L44 _public function_ `void Set(DataType&& Value)`
- L49 _public function_ `const DataType& Get() const`
- L55 _private member_ `DataType Data;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundParameterPack.h` (Public)


#### struct `MetasoundParameterPackPrivate::FMetasoundParameterPackItemBase`  
`struct FMetasoundParameterPackItemBase`  
_L23-41_
- L25 _public function_ `FMetasoundParameterPackItemBase(const FName& InName, const FName& InTypeName, uint16 InNextOffset, uint16 InValueOffset) : Name(InName) , TypeName(InTypeName) , NextHeaderOffset(InNextOffset) , ValueOffset(InValueOffset)`
- L31 _public prototype_ `FMetasoundParameterPackItemBase(const FMetasoundParameterPackItemBase& Other) = default;`
- L32 _public function_ `void* GetPayload()`
- L37 _public member_ `FName Name;`
- L38 _public member_ `FName TypeName;`
- L39 _public member_ `uint16 NextHeaderOffset;`
- L40 _public member_ `uint16 ValueOffset;`

#### struct `MetasoundParameterPackPrivate::TRootValueTypeHelper`  
`template<bool, typename T, int32 MaxNumItems = 0> struct TRootValueTypeHelper`  
_L44-44_
- L44 _public typedef_ `template<bool, typename T, int32 MaxNumItems = 0> struct TRootValueTypeHelper { using Type = T; };`
- L47 _public typedef_ `template<typename T, int32 MaxNumItems> struct TRootValueTypeHelper<true, T, MaxNumItems> { using Type = Metasound::TParamPackFixedArray<typename T::ElementType, MaxNumItems>; };`

#### struct `MetasoundParameterPackPrivate::TRootValueTypeHelper`  
`template<typename T, int32 MaxNumItems> struct TRootValueTypeHelper<true, T, MaxNumItems>`  
_L47-47_
- L44 _public typedef_ `template<bool, typename T, int32 MaxNumItems = 0> struct TRootValueTypeHelper { using Type = T; };`
- L47 _public typedef_ `template<typename T, int32 MaxNumItems> struct TRootValueTypeHelper<true, T, MaxNumItems> { using Type = Metasound::TParamPackFixedArray<typename T::ElementType, MaxNumItems>; };`

#### struct `MetasoundParameterPackPrivate::TRootValueType`  
`template<typename T, int32 MaxNumItems = 0> struct TRootValueType : TRootValueTypeHelper<TIsTArray_V<T>, T, MaxNumItems>`  
_L50-50_
- inherits: `TRootValueTypeHelper<TIsTArray_V<T>,T,MaxNumItems>`

#### struct `MetasoundParameterPackPrivate::FMetasoundParameterPackItem`  
`template <typename T, int32 MaxNumItems = 0> struct FMetasoundParameterPackItem : public FMetasoundParameterPackItemBase`  
_L56-75_
- inherits: `FMetasoundParameterPackItemBase`
- desc: A template that lets us stick an arbitrary data type into the raw 'bag-o-bytes' that is the parameter storage. Uses the base class above.
- L58 _public typedef_ `using ThisType = FMetasoundParameterPackItem<T,MaxNumItems>;`
- L59 _public function_ `FMetasoundParameterPackItem(const FName& InName, const FName& InTypeName, const T& InValue) : FMetasoundParameterPackItemBase(InName, InTypeName, SizeOfParam(InValue), offsetof(FMetasoundParameterPackItem<ThisType>, Value)) , Value(InValue)`
- L68 _public prototype_ `FMetasoundParameterPackItem(const FMetasoundParameterPackItem& Other) = default;`
- L69 _public member_ `typename TRootValueType<T, MaxNumItems>::Type Value;`
- L71 _public function_ `static uint16 SizeOfParam(const T& InValue)`

#### struct `FMetasoundParameterPackStorage`  
`struct FMetasoundParameterPackStorage`  
_L79-248_
- desc: This next class owns the 'bag-o-bytes' that holds all of the parameters.
- L81 _public member_ `TArray<uint8> Storage;`
- L82 _public member_ `int32 StorageBytesInUse = 0;`
- L84 _public prototype_ `FMetasoundParameterPackStorage() = default;`
- L85 _public function_ `FMetasoundParameterPackStorage(const FMetasoundParameterPackStorage& Other) : Storage(Other.Storage) , StorageBytesInUse(Other.StorageBytesInUse)`
- L89 _public function_ `FMetasoundParameterPackStorage(FMetasoundParameterPackStorage&& Other) : Storage(MoveTemp(Other.Storage)) , StorageBytesInUse(Other.StorageBytesInUse)`
- L154 _public function_ `ParameterIterator begin()`
- L163 _public function_ `ParameterIterator end()`
- L169 _public function_ `template<typename T, int32 MaxNumItems = 0> MetasoundParameterPackPrivate::FMetasoundParameterPackItem<T, MaxNumItems>* FindParameter(const FName& ParamName, const FName& InTypeName)`
- L203 _public function_ `template<typename T> std::enable_if_t<!std::is_class_v<T>,T*> AddParameter(const FName& Name, const FName& InTypeName, const T& InValue)` — non-class version
- L219 _public function_ `template<typename T> std::enable_if_t<std::is_class_v<T> && !TIsTArray_V<T>, T*> AddParameter(const FName& Name, const FName& InTypeName, const T& InValue)` — class version
- L235 _public function_ `template<typename T, int32 MaxNumItems> std::enable_if_t<std::is_class_v<T> && TIsTArray_V<T>, void> AddArrayParameter(const FName& Name, const FName& InTypeName, const T& InValue)` — array version

#### struct `FMetasoundParameterPackStorage::ParameterIterator`  
`struct ParameterIterator`  
_L96-152_
- L98 _public member_ `uint8* CurrentNode;`
- L99 _public member_ `uint8* EndAddress;`
- L101 _public function_ `ParameterIterator(uint8* Start, uint8* End) : CurrentNode(Start) , EndAddress(End)`
- L106 _public function_ `ParameterIterator& operator++()`
- L123 _public function_ `ParameterIterator operator++(int)`
- L130 _public function_ `bool operator==(const ParameterIterator& Other) const`
- L135 _public function_ `bool operator!=(const ParameterIterator& Other) const`
- L140 _public function_ `MetasoundParameterPackPrivate::FMetasoundParameterPackItemBase* operator->()`
- L146 _public function_ `MetasoundParameterPackPrivate::FMetasoundParameterPackItemBase* GetParameterBase()`

#### enum `ESetParamResult`  
`enum class ESetParamResult : uint8`  
_L253-257_
- reflection: `UENUM(BlueprintType)`
- L255 _public enumerator_ `Succeeded`
- L256 _public enumerator_ `Failed`

#### class `UMetasoundParameterPack`  
`class UMetasoundParameterPack : public UObject, public IAudioProxyDataFactory`  
_L262-442_
- reflection: `UCLASS(MinimalAPI, BlueprintType,meta = (DisplayName = "MetaSoundParameterPack"))`
- inherits: `UObject,IAudioProxyDataFactory`
- desc: Here is the UObject BlueprintType that can be used in c++ and blueprint code. It holds a FMetasoundParamStorage instance and can pass it along to the audio system's SetObjectParameter function via an AudioProxy.
- L269 _public prototype_ `static UMetasoundParameterPack* MakeMetasoundParameterPack();` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack")`
- L272 _public prototype_ `ESetParamResult SetBool(FName ParameterName, bool InValue, bool OnlyIfExists = true);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = ReturnValue))`
- L274 _public prototype_ `ESetParamResult SetInt(FName ParameterName, int32 InValue, bool OnlyIfExists = true);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = ReturnValue))`
- L276 _public prototype_ `ESetParamResult SetFloat(FName ParameterName, float InValue, bool OnlyIfExists = true);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = ReturnValue))`
- L278 _public prototype_ `ESetParamResult SetString(FName ParameterName, const FString& InValue, bool OnlyIfExists = true);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = ReturnValue))`
- L280 _public prototype_ `ESetParamResult SetTrigger(FName ParameterName, bool OnlyIfExists = true);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = ReturnValue))`
- L283 _public prototype_ `bool GetBool(FName ParameterName, ESetParamResult& Result) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = "Result"))`
- L285 _public prototype_ `int32 GetInt(FName ParameterName, ESetParamResult& Result) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = "Result"))`
- L287 _public prototype_ `float GetFloat(FName ParameterName, ESetParamResult& Result) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = "Result"))`
- L289 _public prototype_ `FString GetString(FName ParameterName, ESetParamResult& Result) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = "Result"))`
- L291 _public prototype_ `bool GetTrigger(FName ParameterName, ESetParamResult& Result) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = "Result"))`
- L294 _public prototype_ `bool HasBool(FName ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = ReturnValue))`
- L296 _public prototype_ `bool HasInt(FName ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = ReturnValue))`
- L298 _public prototype_ `bool HasFloat(FName ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = ReturnValue))`
- L300 _public prototype_ `bool HasString(FName ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = ReturnValue))`
- L302 _public prototype_ `bool HasTrigger(FName ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = ReturnValue))`
- L304 _public prototype_ `void AddBoolParameter(FName Name, bool InValue);`
- L305 _public prototype_ `void AddIntParameter(FName Name, int32 InValue);`
- L306 _public prototype_ `void AddFloatParameter(FName Name, float InValue);`
- L307 _public prototype_ `void AddStringParameter(FName Name, const FString& InValue);`
- L308 _public prototype_ `void AddTriggerParameter(FName Name, bool InValue = true);`
- L311 _public prototype_ `bool* GetBoolParameterPtr(FName Name) const;` — YIKES! BEWARE: If the returned pointers are only valid until another parameter is added!
- L312 _public prototype_ `int32* GetIntParameterPtr(FName Name) const;`
- L313 _public prototype_ `float* GetFloatParameterPtr(FName Name) const;`
- L314 _public prototype_ `FString* GetStringParameterPtr(FName Name) const;`
- L315 _public prototype_ `bool* GetTriggerParameterPtr(FName Name) const;`
- L318 _public function_ `template<typename T> ESetParamResult SetParameter(const FName& Name, const FName& InTypeName, const T& InValue, bool OnlyIfExists = true)`
- L336 _public function_ `template<typename T, int32 MaxNumItems> ESetParamResult SetArrayParameter(const FName& Name, const FName& InTypeName, const T& InValue, bool OnlyIfExists = true)`
- L359 _public function_ `template<typename T, int32 MaxNumItems=0> bool HasParameter(const FName& Name, const FName& InTypeName) const`
- L369 _public function_ `template<typename T> void AddParameter(const FName& Name, const FName& InTypeName, const T& InValue)`
- L379 _public function_ `template<typename T, int32 MaxNumItems> void AddArrayParameter(const FName& Name, const FName& InTypeName, const T& InValue)`
- L389 _public function_ `template<typename T> T GetParameter(const FName& Name, const FName& InTypeName, ESetParamResult& Result) const`
- L402 _public function_ `template<typename T, int32 MaxNumItems> void GetParameter(const FName& Name, const FName& InTypeName, TArray<typename T::ElementType>& ResultArray, ESetParamResult& Result) const`
- L414 _public prototype_ `TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;`
- L419 _public prototype_ `static Metasound::FSendAddress CreateSendAddressFromEnvironment(const Metasound::FMetasoundEnvironment& InEnvironment);` — `UE_DEPRECATED(5.3, "FSendAddress are no longer used to communicate with MetaSound instances.")` — A couple of utilities for use by MetasoundAssetBase and MetasoundGenerator to set up the routing for parameter packs
- L420 _public prototype_ `static FMetasoundFrontendClassInput GetClassInput();`
- L422 _public prototype_ `FSharedMetasoundParameterStoragePtr GetParameterStorage() const;`
- L423 _public prototype_ `FSharedMetasoundParameterStoragePtr GetCopyOfParameterStorage() const;`
- L427 _private function_ `template<typename T, int MaxNumItems = 0> typename MetasoundParameterPackPrivate::TRootValueType<T, MaxNumItems>::Type* GetParameterPtr(const FName& Name, const FName& InTypeName) const`
- L441 _private member_ `FSharedMetasoundParameterStoragePtr ParameterStorage;`

#### class `FMetasoundParameterPackProxy`  
`class FMetasoundParameterPackProxy : public Audio::TProxyData<FMetasoundParameterPackProxy>`  
_L445-461_
- inherits: `Audio::TProxyData<FMetasoundParameterPackProxy>`
- desc: Here is the proxy that UMetasoundParameterPack creates when asked for a proxy by the audio system
- L448 _public prototype_ `IMPL_AUDIOPROXY_CLASS(FMetasoundParameterPackProxy);`
- L450 _public function_ `explicit FMetasoundParameterPackProxy(FSharedMetasoundParameterStoragePtr& Data) : ParameterStoragePtr(Data)`
- L454 _public function_ `FSharedMetasoundParameterStoragePtr GetParamStorage()`
- L460 _private member_ `FSharedMetasoundParameterStoragePtr ParameterStoragePtr;`

#### class `FMetasoundParameterStorageWrapper`  
`class FMetasoundParameterStorageWrapper`  
_L465-520_
- desc: And finally... A type we can register with Metasound that holds a TSharedPtr to an FMetasoundParamStorage instance. It can be created by various systems in Metasound given a proxy.
- L467 _private member_ `FSharedMetasoundParameterStoragePtr ParameterStoragePtr;`
- L471 _public prototype_ `FMetasoundParameterStorageWrapper() = default;`
- L472 _public prototype_ `FMetasoundParameterStorageWrapper(const FMetasoundParameterStorageWrapper&) = default;`
- L473 _public prototype_ `FMetasoundParameterStorageWrapper& operator=(const FMetasoundParameterStorageWrapper& Other) = default;`
- L474 _public function_ `FMetasoundParameterStorageWrapper(const TSharedPtr<Audio::IProxyData>& InInitData)`
- L487 _public function_ `FSharedMetasoundParameterStoragePtr Get() const`
- L492 _public function_ `bool IsPackValid() const`
- L497 _public function_ `const FSharedMetasoundParameterStoragePtr& GetPackProxy() const`
- L502 _public function_ `const FMetasoundParameterPackStorage* operator->() const`
- L507 _public function_ `FMetasoundParameterPackStorage* operator->()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L21 _namespace_ `namespace MetasoundParameterPackPrivate`
- L250 _typedef_ `using FSharedMetasoundParameterStoragePtr = TSharedPtr<FMetasoundParameterPackStorage, ESPMode::ThreadSafe>;`
- L512 _function_ `friend inline uint32 GetTypeHash(const FMetasoundParameterStorageWrapper& InParameterStorageWrapper)`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundParameterPackFixedArray.h` (Public)


#### class `Metasound::TParamPackFixedArray`  
`template<typename ElementType, int32 NumInlineElements> class TParamPackFixedArray`  
_L12-54_
- L15 _public function_ `TParamPackFixedArray(const TArray<ElementType>& Other)`
- L20 _public function_ `TParamPackFixedArray<ElementType, NumInlineElements>& operator=(const TArray<ElementType>& Other)`
- L31 _public function_ `void CopyToArray(TArray<ElementType>& Dest) const`
- L40 _public function_ `inline const ElementType* GetData() const`
- L45 _public function_ `inline ElementType* GetData()`
- L51 _public member_ `int32 NumValidElements = 0;`
- L52 _public typedef_ `using FByteBucketType = TTypeCompatibleBytes<ElementType>;`
- L53 _public member_ `FByteBucketType InlineData[NumInlineElements];`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundParameterTransmitter.h` (Public)


#### class `Metasound::FMetaSoundParameterTransmitter`  
`class FMetaSoundParameterTransmitter : public Audio::FParameterTransmitterBase`  
_L38-143_
- inherits: `Audio::FParameterTransmitterBase`
- desc: FMetaSoundParameterTransmitter provides a communication interface for sending values to a MetaSound instance. It relies on the send/receive transmission system to ferry data from the transmitter to the MetaSound instance. Data will be safely ushered across thread boundaries in scenarios where the instance transmitter and metasound instance live on different threads.
- L40 _private prototype_ `FMetaSoundParameterTransmitter(const FMetaSoundParameterTransmitter&) = delete;`
- L41 _private prototype_ `FMetaSoundParameterTransmitter& operator=(const FMetaSoundParameterTransmitter&) = delete;`
- L103 _public prototype_ `static FSendAddress CreateSendAddressFromEnvironment(const FMetasoundEnvironment& InEnvironment, const FVertexName& InVertexName, const FName& InTypeName);` — `UE_DEPRECATED(5.3, "This function is no longer used. Send addresses are no longer used when communicating with MetaSound inputs")` — Creates a unique send address using the given MetaSound environment.
- L107 _public prototype_ `static FSendAddress CreateSendAddressFromInstanceID(uint64 InInstanceID, const FVertexName& InVertexName, const FName& InTypeName);` — `UE_DEPRECATED(5.3, "This function is no longer used. Send addresses are no longer used when communicating with MetaSound inputs")` — Creates a unique send address using the given InstanceID.
- L109 _public prototype_ `FMetaSoundParameterTransmitter(FMetaSoundParameterTransmitter::FInitParams&& InInitParams);`
- L110 _public prototype_ `virtual ~FMetaSoundParameterTransmitter() = default;`
- L112 _public prototype_ `void AddAvailableParameter(FName InName);`
- L113 _public prototype_ `void RemoveAvailableParameter(FName InName);`
- L119 _public prototype_ `virtual bool SetParameters(TArray<FAudioParameter>&& InParameters) override;` — Sets parameters using array of AudioParameter structs @param InParameter - Parameter to set.
- L128 _public prototype_ `bool SetParameterWithLiteral(FName InParameterName, const FLiteral& InValue);` — Set a parameter using a literal. @param InParameterName - Name of MetaSound instance parameter. @param InValue - Literal value used to construct parameter value. @return true on success, false on failure.
- L137 _private prototype_ `bool SetVirtualizedParameters(TArray<FAudioParameter>&& InParameters);` — Set parameters when virtualized @return true if all non trigger parameters are set on the parameter base (trigger parameters are removed on virtualized sounds and parameters are not actually set on the MetaSound until realization)
- L139 _private member_ `uint64 InstanceID;`
- L140 _private member_ `FName DebugMetaSoundName;`
- L141 _private member_ `TArray<FName> AvailableParameterNames;`
- L142 _private member_ `TSharedPtr<TSpscQueue<FParameter>> DataChannel;`

#### struct `Metasound::FMetaSoundParameterTransmitter::FSendInfo`  
`struct FSendInfo`  
_L47-57_
- desc: FSendInfo describes the MetaSounds input parameters as well as the necessary information to route data to the instances inputs.
- L50 _public member_ `FSendAddress Address;` — Global address of instance input.
- L53 _public member_ `FName ParameterName;` — Name of parameter on MetaSound instance.
- L56 _public member_ `FName TypeName;` — Type name of parameter on MetaSound instance.

#### struct `Metasound::FMetaSoundParameterTransmitter::FParameter`  
`struct FParameter`  
_L60-64_
- L62 _public member_ `FName Name;`
- L63 _public member_ `FLiteral Value;`

#### struct `Metasound::FMetaSoundParameterTransmitter::FInitParams`  
`struct FInitParams`  
_L67-99_
- desc: Initialization parameters for a FMetaSoundParameterTransmitter.
- L71 _public member_ `FOperatorSettings OperatorSettings;` — FOperatorSettings must match the operator settings of the MetaSound instance to ensure proper operation.
- L74 _public member_ `uint64 InstanceID;` — ID of the MetaSound instance.
- L77 _public member_ `TArray<FName> ValidParameterNames;` — Available input parameters on MetaSound instance.
- L80 _public member_ `TArray<FSendInfo> Infos;` — Available input parameters on MetaSound instance.
- L83 _public member_ `FName DebugMetaSoundName;` — Name of MetaSound used to log parameter related errors.
- L86 _public member_ `TArray<FAudioParameter> DefaultParams;` — Default Audio Parameters set when transmitter is initialized.
- L89 _public member_ `TSharedPtr<TSpscQueue<FParameter>> DataChannel;` — Shared queue used to communicate with running MetaSound instance.
- L91 _public function_ `FInitParams(const FOperatorSettings& InSettings, uint64 InInstanceID, TArray<FAudioParameter>&& InDefaultParams, TArray<FName>&& InValidParameterNames, TSharedPtr<TSpscQueue<FParameter>> InDataChannel) : OperatorSettings(InSettings) , InstanceID(InInstanceID) , ValidParameterNames(MoveTemp(InValidParameterNames)) , DefaultParams(MoveTemp(InDefaultParams)) , DataChannel(InDataChannel)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L18 _namespace_ `namespace Metasound`
- L20 _externvar_ `extern int32 MetaSoundParameterEnableWarningOnIgnoredParameterCVar;` (scope `Metasound`)
- L24 _namespace_ `namespace Frontend` (scope `Metasound`)
- L26 _prototype_ `FLiteral ConvertParameterToLiteral(FAudioParameter&& InValue);` (scope `Metasound::Frontend`)
- L27 _prototype_ `FLiteral ConvertParameterToLiteral(const FAudioParameter& InValue);` (scope `Metasound::Frontend`)
- L28 _prototype_ `FName ConvertParameterToDataType(EAudioParameterType InParameterType);` (scope `Metasound::Frontend`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundPrimitives.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundReceiveNode.h` (Public)


#### class `Metasound::ReceiveNodePrivate::TReceiverOperator`  
`template<typename TDataType> class TReceiverOperator : public TExecutableOperator<TReceiverOperator<TDataType>>`  
_L44-221_
- inherits: `TExecutableOperator<TReceiverOperator<TDataType>>`
- L46 _private prototype_ `TReceiverOperator() = delete;`
- L49 _public function_ `static FVertexInterface DeclareVertexInterface()`
- L63 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L92 _public function_ `TReceiverOperator(TDataReadReference<TDataType> InInitDataRef, TDataWriteReference<TDataType> InOutDataRef, TDataReadReference<FSendAddress> InSendAddress, const FOperatorSettings& InOperatorSettings) : bHasNotReceivedData(true) , DefaultData(InInitDataRef) , OutputData(InOutDataRef) , SendAddress(InSendAddress) , CachedSendAddress(*InSendAddress) , CachedReceiverParams({InOperatorSettings}) , Receiver(nullptr)`
- L104 _public function_ `virtual ~TReceiverOperator()`
- L109 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override`
- L116 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override`
- L122 _public function_ `void Execute()`
- L158 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L167 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L188 _private function_ `FSendAddress GetSendAddressWithDataType(const FSendAddress& InAddress) const`
- L196 _private function_ `TReceiverPtr<TDataType> CreateNewReceiver() const`
- L205 _private function_ `void ResetReceiverAndCleanupChannel()`
- L211 _private member_ `bool bHasNotReceivedData;`
- L213 _private member_ `TDataReadReference<TDataType> DefaultData;`
- L214 _private member_ `TDataWriteReference<TDataType> OutputData;`
- L215 _private member_ `TDataReadReference<FSendAddress> SendAddress;`
- L217 _private member_ `FSendAddress CachedSendAddress;`
- L218 _private member_ `FReceiverInitParams CachedReceiverParams;`
- L220 _private member_ `TReceiverPtr<TDataType> Receiver;`

#### class `Metasound::TReceiveNode`  
`template<typename TDataType> class TReceiveNode : public TNodeFacade<ReceiveNodePrivate::TReceiverOperator<TDataType>>`  
_L225-241_
- inherits: `TNodeFacade<ReceiveNodePrivate::TReceiverOperator<TDataType>>`
- L228 _public typedef_ `using FOperator = ReceiveNodePrivate::TReceiverOperator<TDataType>;`
- L229 _public typedef_ `using FSuper = TNodeFacade<FOperator>;`
- L232 _public function_ `static FVertexInterface DeclareVertexInterface()`
- L237 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "MetasoundFrontend"`
- L21 _namespace_ `namespace Metasound`
- L23 _namespace_ `namespace ReceiveNodeInfo` (scope `Metasound`)
- L30 _externvar_ `extern const FDataVertexMetadata DefaultDataInputMetadata;` (scope `Metasound::ReceiveNodeInfo`)
- L31 _externvar_ `extern const FDataVertexMetadata OutputMetadata;` (scope `Metasound::ReceiveNodeInfo`)
- L33 _prototype_ `FNodeClassName GetClassNameForDataType(const FName& InDataTypeName);` (scope `Metasound::ReceiveNodeInfo`)
- L34 _prototype_ `int32 GetCurrentMajorVersion();` (scope `Metasound::ReceiveNodeInfo`)
- L35 _prototype_ `int32 GetCurrentMinorVersion();` (scope `Metasound::ReceiveNodeInfo`)
- L38 _namespace_ `namespace ReceiveNodePrivate` (scope `Metasound`)
- L41 _prototype_ `Frontend::FNodeClassRegistryKey CreateNodeClassRegistryKey(const FName& InDataTypeName);` (scope `Metasound::ReceiveNodePrivate`)
- L66 _function_ `` (scope `Metasound::ReceiveNodePrivate::TReceiverOperator::GetNodeInfo`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundRouter.h` (Public)


#### class `Metasound::FTransmissionAddress`  
`class FTransmissionAddress`  
_L59-117_
- desc: A FTranmissionAddress acts as a identifier for a data channel shared by one or more senders and or receivers. Different addressing schemes are supported by deriving a system specific address type from a FTransmissionAddress. This allows different systems to construct and store address information in their desired format while all utilizing the same system for transmission.
- L62 _public prototype_ `FTransmissionAddress() = default;`
- L63 _public prototype_ `virtual ~FTransmissionAddress() = default;`
- L71 _public prototype_ `virtual FName GetAddressType() const = 0;` — Return the type of address. The AddressType must be unique per a subclass of FTransmissionAddress as it is used to determine the validity of a static_cast from FTransmissionAddress to the derived address type.
- L73 _public prototype_ `bool operator==(const FTransmissionAddress& InOther) const;`
- L74 _public prototype_ `bool operator!=(const FTransmissionAddress& InOther) const;`
- L77 _public prototype_ `virtual FName GetDataType() const = 0;` — Return the data type.
- L80 _public prototype_ `virtual TUniquePtr<FTransmissionAddress> Clone() const = 0;` — Clone the address.
- L83 _public prototype_ `virtual FString ToString() const = 0;` — Return a string representation of the address for debugging.
- L113 _private prototype_ `virtual uint32 GetHash() const = 0;` — Create a hash of the address.
- L116 _private prototype_ `virtual bool IsEqual(const FTransmissionAddress& InOther) const = 0;` — Determine if the given address is equal to this address.

#### struct `Metasound::FTransmissionAddress::THasStaticAddressType`  
`template<typename DerivedAddressType> struct THasStaticAddressType`  
_L92-110_
- L101 _private prototype_ `static std::true_type CheckIfStaticMemberExists(int32);`
- L105 _private prototype_ `template<typename> static std::false_type CheckIfStaticMemberExists(...);` — SFINAE: If the static member `T::AddressType` does not exist, then this template is used.
- L109 _public member_ `static constexpr bool Value = decltype(CheckIfStaticMemberExists<DerivedAddressType>(0))::value;` — True if the static member T::AddressType exists.

#### class `Metasound::FSendAddress`  
`class FSendAddress : public FTransmissionAddress`  
_L145-176_
- inherits: `FTransmissionAddress`
- desc: FSendAddress is used as a addressing system for MetaSound Send nodes, Recieve nodes and MetaSound script communication
- L148 _public member_ `static const FLazyName AddressType;`
- L150 _public prototype_ `FSendAddress() = default;`
- L153 _public prototype_ `FSendAddress(const FString& InChannelName);` — Create an address without a data type or instance ID
- L156 _public prototype_ `FSendAddress(const FName& InChannelName, const FName& InDataType, uint64 InInstanceID=INDEX_NONE);` — Create an address with a channel name, data type and optionally an instance ID.
- L158 _public prototype_ `virtual FName GetAddressType() const override;`
- L159 _public prototype_ `virtual FName GetDataType() const override;`
- L160 _public prototype_ `virtual TUniquePtr<FTransmissionAddress> Clone() const override;`
- L161 _public prototype_ `virtual FString ToString() const override;`
- L163 _public prototype_ `const FName& GetChannelName() const;`
- L164 _public prototype_ `uint64 GetInstanceID() const;`
- L168 _private prototype_ `virtual uint32 GetHash() const override;`
- L169 _private prototype_ `virtual bool IsEqual(const FTransmissionAddress& InOther) const override;`
- L171 _private member_ `FName ChannelName;`
- L172 _private member_ `FName DataType;`
- L175 _private member_ `uint64 InstanceID = INDEX_NONE;` — For instance-specific addresses, this uint64 is the instance of this metasound.

#### class `Metasound::IDataTransmissionBase`  
`class IDataTransmissionBase`  
_L184-225_
- desc: Base class that defines shared state and utilities for senders, receivers, and the shared channel state.
- L187 _public prototype_ `IDataTransmissionBase() = delete;`
- L189 _public function_ `IDataTransmissionBase(FName InDataType) : DataType(InDataType)`
- L194 _public prototype_ `virtual ~IDataTransmissionBase() = default;`
- L197 _public function_ `template<typename TSenderImplementation> bool CheckType() const`
- L204 _public function_ `template<typename TSenderImplementation> const TSenderImplementation& GetAs() const`
- L211 _public function_ `template<typename TSenderImplementation> TSenderImplementation& GetAs()`
- L217 _public function_ `FName GetDataType() const`
- L224 _protected member_ `FName DataType;` — The data type for this sender.

#### class `Metasound::IReceiver`  
`class IReceiver : public IDataTransmissionBase`  
_L231-244_
- inherits: `IDataTransmissionBase`
- desc: This is a handle to something that will retrieve a datatype. Intentionally opaque- to use, one will need to call IReceiver::GetAs<TReceiver<YourDataType>>().
- L234 _public function_ `IReceiver(TSharedPtr<IDataChannel, ESPMode::ThreadSafe> InDataChannel, FName DataType) : IDataTransmissionBase(DataType) , DataChannel(InDataChannel)`
- L240 _public prototype_ `virtual ~IReceiver();`
- L243 _protected member_ `TSharedPtr<IDataChannel, ESPMode::ThreadSafe> DataChannel;`

#### class `Metasound::ISender`  
`class ISender : public IDataTransmissionBase`  
_L248-265_
- inherits: `IDataTransmissionBase`
- desc: This is a handle to something that will retrieve a datatype. Intentionally opaque- to use, one will need to call ISender::GetAs<TSender<YourDataType>>().
- L251 _public function_ `ISender(TSharedPtr<IDataChannel, ESPMode::ThreadSafe> InDataChannel, FName DataType) : IDataTransmissionBase(DataType) , DataChannel(InDataChannel)`
- L256 _public prototype_ `virtual ~ISender();`
- L258 _public prototype_ `virtual int64 GetPayloadID() const = 0;`
- L261 _public prototype_ `virtual bool PushLiteral(const FLiteral& InLiteral) = 0;` — Constructs the value with a literal and pushes to data channel.
- L264 _protected member_ `TSharedPtr<IDataChannel, ESPMode::ThreadSafe> DataChannel;`

#### struct `Metasound::FSenderInitParams`  
`struct FSenderInitParams`  
_L267-271_
- L269 _public member_ `FOperatorSettings OperatorSettings;`
- L270 _public member_ `float DelayTimeInSeconds;`

#### struct `Metasound::FReceiverInitParams`  
`struct FReceiverInitParams`  
_L273-276_
- L275 _public member_ `FOperatorSettings OperatorSettings;`

#### class `Metasound::IDataChannel`  
`class IDataChannel : public IDataTransmissionBase, public TSharedFromThis<IDataChannel, ESPMode::ThreadSafe>`  
_L280-343_
- inherits: `IDataTransmissionBase,TSharedFromThis<IDataChannel,ESPMode::ThreadSafe>`
- desc: This contains an intermediary buffer for use between the send and receive nodes. Typically only used by ISender and IReceiver implementations.
- L283 _public prototype_ `virtual ~IDataChannel() = default;`
- L285 _public function_ `IDataChannel(FName DataType) : IDataTransmissionBase(DataType)`
- L289 _public function_ `TUniquePtr<IReceiver> NewReceiver(const FReceiverInitParams& InitParams)`
- L295 _public function_ `TUniquePtr<ISender> NewSender(const FSenderInitParams& InitParams)`
- L301 _public function_ `uint32 GetNumActiveReceivers() const`
- L306 _public function_ `uint32 GetNumActiveSenders() const`
- L311 _public function_ `virtual int64 GetPayloadID() const`
- L312 _public prototype_ `virtual int64 CreateNewPayloadID() = 0;`
- L313 _public function_ `virtual bool PushOpaque(ISender& InSender)`
- L314 _public function_ `virtual void PopOpaque(IReceiver& InReceiver)`
- L315 _public function_ `virtual bool IsEmpty() const`
- L317 _public function_ `virtual FName GetDataType()`
- L319 _public function_ `virtual bool PushLiteral(const FLiteral& InParam)`
- L322 _protected function_ `virtual TUniquePtr<IReceiver> ConstructNewReceiverImplementation(const FReceiverInitParams& InitParams)`
- L323 _protected function_ `virtual TUniquePtr<ISender> ConstructNewSenderImplementation(const FSenderInitParams& InitParams)`
- L326 _private function_ `void OnSenderDestroyed()`
- L332 _private function_ `void OnReceiverDestroyed()`
- L341 _private member_ `FThreadSafeCounter NumAliveReceivers;`
- L342 _private member_ `FThreadSafeCounter NumAliveSenders;`

#### class `Metasound::TNonOperationalSender`  
`template<typename TDataType> class TNonOperationalSender : public ISender`  
_L347-351_
- inherits: `ISender`
- desc: Generic templates:
- L350 _public function_ `bool Push(const TDataType& InValue)`

#### class `Metasound::TNonOperationalReceiver`  
`template<typename TDataType> class TNonOperationalReceiver : public IReceiver`  
_L354-358_
- inherits: `IReceiver`
- L357 _public function_ `bool Pop(TDataType& OutValue)`

#### class `Metasound::TNonOperationalDataChannel`  
`template<typename TDataType> class TNonOperationalDataChannel : public IDataChannel`  
_L361-414_
- inherits: `IDataChannel`
- L366 _public function_ `TNonOperationalDataChannel(const FOperatorSettings& InOperatorSettings) : IDataChannel(FName()) , PayloadIDCounter(0)`
- L371 _public function_ `virtual bool PushOpaque(ISender& InSender) override`
- L376 _public function_ `virtual void PopOpaque(IReceiver& InReceiver) override`
- L381 _public function_ `virtual int64 CreateNewPayloadID() override`
- L387 _public function_ `virtual bool IsEmpty() const override`
- L392 _public function_ `virtual FName GetDataType() override`
- L397 _public function_ `static FName GetDataTypeName()`
- L403 _protected function_ `virtual TUniquePtr<IReceiver> ConstructNewReceiverImplementation(const FReceiverInitParams& InitParams) override`
- L408 _protected function_ `virtual TUniquePtr<ISender> ConstructNewSenderImplementation(const FSenderInitParams& InitParams) override`
- L413 _private member_ `std::atomic<int64> PayloadIDCounter;`

#### class `Metasound::TSender`  
`template<typename TDataType> class TSender : public ISender`  
_L418-521_
- inherits: `ISender`
- desc: Specializations for trivially copyable types:
- L423 _private member_ `static constexpr float BufferResizeThreshold = 2.0f;` — This can be changed to change when we reallocate the internal buffer for this sender.
- L425 _private member_ `bool bMessageDataTypeError = true;`
- L429 _public function_ `bool Push(const TDataType& InElement)`
- L443 _public function_ `bool PushLiteral(const FLiteral& InLiteral) override`
- L461 _public function_ `bool SetDelay(float InSeconds)` — Resets the delay for this specific sender. if this goes beyond the threshold set by BufferResizeThreshold, we reallocate.
- L468 _public function_ `static FName GetDataTypeName()`
- L473 _public function_ `TSender(const FSenderInitParams& InitParams, TSharedPtr<IDataChannel, ESPMode::ThreadSafe> InDataChannel) : ISender(InDataChannel, GetDataTypeName()) , Params(InitParams)`
- L480 _public function_ `int64 GetPayloadID() const override`
- L485 _public function_ `TDataType RetrievePayload()`
- L492 _public function_ `bool PushToDataChannel()` — Push from the SenderBuffer to the data channel.
- L509 _private member_ `Audio::TCircularAudioBuffer<TDataType> SenderBuffer;` — This buffer acts as a delay line for this sender specifically.
- L511 _private member_ `int64 PayloadID = 0;`
- L515 _private member_ `TUniquePtr<TDataType> Payload;` — lazily initialized holder for payload, allocated on first call to Push. Placed on the heap so that we don't have to assume we know how to construct TDataType.
- L517 _private member_ `FSenderInitParams Params;`
- L520 _private member_ `uint32 NumElementsToDelayBy = 0;` — The amount of pop operations before elements before this sender pushed appear.

#### class `Metasound::TReceiver`  
`template<typename TDataType> class TReceiver : public IReceiver`  
_L524-595_
- inherits: `IReceiver`
- L529 _public function_ `bool CanPop() const`
- L545 _public function_ `bool Pop(TDataType& OutValue)` — Pop the latest value from the data channel.
- L561 _public function_ `static FName GetDataTypeName()`
- L566 _public function_ `TReceiver(const FReceiverInitParams& InitParams, TSharedPtr<IDataChannel, ESPMode::ThreadSafe> InDataChannel) : IReceiver(InDataChannel, GetDataTypeName()) , OperatorSettings(InitParams.OperatorSettings)`
- L572 _public function_ `void PushPayload(int64 InPayloadID, const TDataType& InDataPayload)`
- L592 _private member_ `int64 LastPayloadID = INDEX_NONE;`
- L593 _private member_ `TUniquePtr<TDataType> Payload;`
- L594 _private member_ `FOperatorSettings OperatorSettings;`

#### class `Metasound::TCopyableDataChannel`  
`template<typename TDataType> class TCopyableDataChannel : public IDataChannel`  
_L599-715_
- inherits: `IDataChannel`
- desc: Generic templated implementation of IDataChannel that can use for any copyable type.
- L605 _public function_ `TCopyableDataChannel(const FOperatorSettings& InOperatorSettings) : IDataChannel(GetDataTypeName()) , OperatorSettings(InOperatorSettings) , PayloadIDCounter(0)`
- L611 _public function_ `virtual int64 GetPayloadID() const override`
- L616 _public function_ `virtual int64 CreateNewPayloadID() override`
- L622 _public function_ `virtual bool PushOpaque(ISender& InSender) override`
- L642 _public function_ `virtual void PopOpaque(IReceiver& InReceiver) override`
- L653 _public function_ `virtual bool IsEmpty() const override`
- L658 _public function_ `static FName GetDataTypeName()`
- L663 _public function_ `virtual FName GetDataType() override`
- L668 _public function_ `virtual bool PushLiteral(const FLiteral& InParam)`
- L693 _protected function_ `virtual TUniquePtr<IReceiver> ConstructNewReceiverImplementation(const FReceiverInitParams& InitParams) override`
- L698 _protected function_ `virtual TUniquePtr<ISender> ConstructNewSenderImplementation(const FSenderInitParams& InitParams) override`
- L707 _private member_ `TUniquePtr<TDataType> AtomicData;` — NOTE- In the future, this could be changed to use a TCircualrAudioBuffer or a TQueue for lockless operation. The primary challenge with this is handling multiple senders and receivers. In order to support multiple senders and receivers at scale, we'd need a good implementation of a bounded MPMC queue for arbitrary datatypes.
- L708 _private member_ `FCriticalSection AtomicDataLock;`
- L710 _private member_ `int64 PayloadID = INDEX_NONE;`
- L712 _private member_ `FOperatorSettings OperatorSettings;`
- L714 _private member_ `std::atomic<int64> PayloadIDCounter;`

#### class `Metasound::TAudioSender`  
`template<typename TDataType> class TAudioSender : public ISender`  
_L719-808_
- inherits: `ISender`
- desc: AUDIO SPECIALIZATIONS:
- L721 _private member_ `static constexpr float BufferResizeThreshold = 2.0f;`
- L722 _private member_ `static const int32 MaxChannels = 8;`
- L725 _public function_ `bool Push(const TDataType& InElement)`
- L748 _public function_ `int64 GetPayloadID() const override`
- L753 _public function_ `bool PushLiteral(const FLiteral& InLiteral) override`
- L760 _public function_ `bool SetDelay(float InSeconds)` — Resets the delay for this sender.
- L784 _public function_ `static FName GetDataTypeName()`
- L789 _public function_ `TAudioSender(const FSenderInitParams& InitParams, TSharedPtr<IDataChannel, ESPMode::ThreadSafe> InDataChannel, TArray<Audio::FPatchInput>&& Inputs) : ISender(InDataChannel, GetDataTypeName()) , DataChannelInputs(MoveTemp(Inputs)) , Params(InitParams)`
- L799 _private member_ `TArray<Audio::TCircularAudioBuffer<float>> DelayLines;` — This buffer acts as a delay line for this sender specifically.
- L801 _private member_ `uint32 DelayTimeInFrames;`
- L803 _private member_ `TArray<Audio::FPatchInput> DataChannelInputs;`
- L805 _private member_ `TArray<Audio::FAlignedFloatBuffer> IntermediaryBuffers;`
- L807 _private member_ `FSenderInitParams Params;`

#### class `Metasound::TAudioReceiver`  
`template<typename TDataType> class TAudioReceiver : public IReceiver`  
_L811-859_
- inherits: `IReceiver`
- L813 _private member_ `static constexpr float BufferResizeThreshold = 2.0f;`
- L814 _private member_ `static const int32 MaxChannels = 8;`
- L817 _public function_ `bool CanPop() const`
- L824 _public function_ `bool Pop(TDataType& OutElement)`
- L842 _public function_ `static FName GetDataTypeName()`
- L847 _public function_ `TAudioReceiver(const FReceiverInitParams& InitParams, TSharedPtr<IDataChannel, ESPMode::ThreadSafe> InDataChannel, TArray<Audio::FPatchOutputStrongPtr>&& Outputs) : IReceiver(InDataChannel, GetDataTypeName()) , DataChannelOutputs(MoveTemp(Outputs)) , Params(InitParams)`
- L856 _private member_ `TArray<Audio::FPatchOutputStrongPtr> DataChannelOutputs;`
- L858 _private member_ `FReceiverInitParams Params;`

#### class `Metasound::TAudioDataChannel`  
`template<typename TDataType> class TAudioDataChannel : public IDataChannel`  
_L862-934_
- inherits: `IDataChannel`
- L865 _private member_ `static const int32 MaxChannels = 8;`
- L867 _public function_ `TAudioDataChannel(const FOperatorSettings& InOperatorSettings) : IDataChannel(GetDataTypeName()) , PayloadIDCounter(0)`
- L874 _public function_ `virtual bool PushOpaque(ISender& InSender) override`
- L879 _public function_ `virtual void PopOpaque(IReceiver& InReceiver) override`
- L887 _public function_ `virtual int64 CreateNewPayloadID() override`
- L893 _public function_ `virtual bool IsEmpty() const override`
- L898 _public function_ `static FName GetDataTypeName()`
- L903 _public function_ `virtual FName GetDataType() override`
- L909 _protected function_ `virtual TUniquePtr<IReceiver> ConstructNewReceiverImplementation(const FReceiverInitParams& InitParams) override`
- L920 _protected function_ `virtual TUniquePtr<ISender> ConstructNewSenderImplementation(const FSenderInitParams& InitParams) override`
- L932 _private member_ `TArray<Audio::FPatchMixerSplitter> AudioBuses;`
- L933 _private member_ `std::atomic<int64> PayloadIDCounter;`

#### class `Metasound::FAddressRouter`  
``  
_L1014-1090_
- L1019 _public prototype_ `TSharedPtr<IDataChannel, ESPMode::ThreadSafe> FindDataChannel(const FTransmissionAddress& InAddress);`
- L1020 _public prototype_ `TSharedPtr<IDataChannel, ESPMode::ThreadSafe> GetDataChannel(const FTransmissionAddress& InAddress, const FOperatorSettings& InOperatorSettings);`
- L1022 _public prototype_ `TUniquePtr<ISender> RegisterNewSender(const FTransmissionAddress& InAddress, const FSenderInitParams& InitParams);`
- L1023 _public prototype_ `TUniquePtr<IReceiver> RegisterNewReceiver(const FTransmissionAddress& InAddress, const FReceiverInitParams& InitParams);`
- L1026 _public function_ `template<typename TDataType> TReceiverPtr<TDataType> RegisterNewReceiver(const FTransmissionAddress& InAddress, const FReceiverInitParams& InitParams)`
- L1040 _public function_ `template<typename TDataType> TSenderPtr<TDataType> RegisterNewSender(const FTransmissionAddress& InAddress, const FSenderInitParams& InitParams)`
- L1054 _public prototype_ `bool PushLiteral(const FName& InDataTypeName, const FName& InChannelName, const FLiteral& InParam);` — `UE_DEPRECATED(5.1, "Pushing literals from the Metasound::FAddressRouter will no longer be supported in future released.")`
- L1056 _public prototype_ `bool UnregisterDataChannel(const FTransmissionAddress& InAddress);`
- L1057 _public prototype_ `bool UnregisterDataChannelIfUnconnected(const FTransmissionAddress& InAddress);`
- L1059 _public prototype_ `FAddressRouter(const FAddressRouter& Other);`
- L1060 _public prototype_ `FAddressRouter() = default;`
- L1088 _private member_ `TMap<FTransmissionAddressKey, TSharedRef<IDataChannel, ESPMode::ThreadSafe>> DataChannelMap;`
- L1089 _private member_ `FCriticalSection DataChannelMapMutationLock;`

#### class `Metasound::FAddressRouter::FTransmissionAddressKey`  
`class FTransmissionAddressKey : public FTransmissionAddress`  
_L1067-1086_
- inherits: `FTransmissionAddress`
- desc: Wrapper class for having an FTransmissionAddress work in a TMap<> This implements the copy constructor and copy assignment operator by calling the virtual Clone() method.
- L1070 _public prototype_ `FTransmissionAddressKey(const FTransmissionAddress& InCopy);`
- L1071 _public prototype_ `FTransmissionAddressKey(const FTransmissionAddressKey& InCopy);`
- L1072 _public prototype_ `FTransmissionAddressKey(TUniquePtr<FTransmissionAddress>&& InImpl);`
- L1073 _public prototype_ `virtual ~FTransmissionAddressKey() = default;`
- L1075 _public prototype_ `FTransmissionAddressKey& operator=(const FTransmissionAddress& InOther);`
- L1076 _public prototype_ `virtual FName GetAddressType() const override;`
- L1077 _public prototype_ `virtual FName GetDataType() const override;`
- L1078 _public prototype_ `virtual TUniquePtr<FTransmissionAddress> Clone() const override;`
- L1079 _public prototype_ `virtual FString ToString() const override;`
- L1082 _private prototype_ `virtual uint32 GetHash() const override;`
- L1083 _private prototype_ `virtual bool IsEqual(const FTransmissionAddress& InOther) const override;`
- L1085 _private member_ `TUniquePtr<FTransmissionAddress> PImpl;`

#### class `Metasound::FDataTransmissionCenter`  
`class FDataTransmissionCenter`  
_L1094-1158_
- desc: Main entry point for all sender/receiver registration.
- L1100 _public prototype_ `static FDataTransmissionCenter& Get();` — Returns the universal router.
- L1104 _public prototype_ `TUniquePtr<ISender> RegisterNewSender(const FTransmissionAddress& InAddress, const FSenderInitParams& InitParams);` — Creates a new object to push data to an address. Returns a new sender, or nullptr if registration failed.
- L1109 _public function_ `template<typename TDataType> TSenderPtr<TDataType> RegisterNewSender(const FTransmissionAddress& InAddress, const FSenderInitParams& InitParams)` — Creates a new object to push data to an address. Returns a new sender, or nullptr if registration failed.
- L1124 _public prototype_ `TUniquePtr<IReceiver> RegisterNewReceiver(const FTransmissionAddress& InAddress, const FReceiverInitParams& InitParams);` — Registers a new object to poll data from an address. Returns a new receiver, or nullptr if registration failed.
- L1129 _public function_ `template<typename TDataType> TReceiverPtr<TDataType> RegisterNewReceiver(const FTransmissionAddress& InAddress, const FReceiverInitParams& InitParams)` — Registers a new object to poll data from an address. Returns a new receiver, or nullptr if registration failed.
- L1143 _public prototype_ `bool UnregisterDataChannel(const FTransmissionAddress& InAddress);` — Unregisters DataChannel irrespective of number of receivers or senders still active.
- L1146 _public prototype_ `bool UnregisterDataChannelIfUnconnected(const FTransmissionAddress& InAddress);` — Unregister a data channel if there are no senders or receivers
- L1151 _public prototype_ `bool PushLiteral(FName DataTypeName, FName GlobalChannelName, const FLiteral& InParam);` — `UE_DEPRECATED(5.1, "Pushing literals from the Metasound::FDataTransmissionCenter will no longer be supported in future released.")` — Pushes a literal parameter to a specific data channel in the global router. returns false if the literal type isn't supported.
- L1155 _private member_ `FAddressRouter GlobalRouter;` — Single map of FNames to IDataChannels
- L1157 _private prototype_ `FDataTransmissionCenter() = default;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L45 _namespace_ `namespace Metasound`
- L49 _prototype_ `uint32 GetTypeHash(const Metasound::FTransmissionAddress&);` (scope `Metasound`)
- L126 _function_ `template<typename DerivedAddressType> const DerivedAddressType* CastAddressType(const FTransmissionAddress& InOther)` (scope `Metasound`) — Attempt to cast a FTransmissionAddress to a derived address type. This function uses the FTransmissionAddress::GetAddressType() method to determine whether the cast is legal. Each subclass of FTransmissionAddress *MUST* provide a unique address type to protect against invalid casts.
- L178 _function_ `inline uint32 GetTypeHash(const Metasound::FTransmissionAddress& InAddress)` (scope `Metasound`)
- L940 _typedef_ `template<typename TDataType, typename USenderType = typename std::conditional<TIsDerivedFrom<TDataType, IAudioDataType>::Value, TAudioSender<TDataType>, TSender<TDataType>>::type> using TSenderPtr = TUniquePtr<USenderType>;` (scope `Metasound`)
- L943 _typedef_ `template<typename TDataType, typename UReceiverType = typename std::conditional<TIsDerivedFrom<TDataType, IAudioDataType>::Value, TAudioReceiver<TDataType>, TReceiver<TDataType>>::type> using TReceiverPtr = TUniquePtr<UReceiverType>;` (scope `Metasound`)
- L948 _function_ `template<typename TDataType, typename TEnableIf<std::is_copy_constructible<TDataType>::value && !TIsDerivedFrom<TDataType, IAudioDataType>::Value, bool>::Type = true> TSharedRef<IDataChannel, ESPMode::ThreadSafe> MakeDataChannel(const FOperatorSettings& InSettings)` (scope `Metasound`)
- L954 _function_ `template<typename TDataType, typename TEnableIf<TIsDerivedFrom<TDataType, IAudioDataType>::Value, bool>::Type = true> TSharedRef<IDataChannel, ESPMode::ThreadSafe> MakeDataChannel(const FOperatorSettings& InSettings)` (scope `Metasound`)
- L960 _function_ `template<typename TDataType, typename TEnableIf<!std::is_copy_constructible<TDataType>::value && !TIsDerivedFrom<TDataType, IAudioDataType>::Value, bool>::Type = true> TSharedRef<IDataChannel, ESPMode::ThreadSafe> MakeDataChannel(const FOperatorSettings& InSettings)` (scope `Metasound`)
- L969 _function_ `template <typename TDataType, typename TEnableIf<TIsDerivedFrom<TDataType, IAudioDataType>::Value, bool>::Type = true> TSenderPtr<TDataType> Downcast(TUniquePtr<ISender>&& InPtr)` (scope `Metasound`) — For Audio Senders:
- L977 _function_ `template <typename TDataType, typename TEnableIf<std::is_copy_constructible<TDataType>::value && !TIsDerivedFrom<TDataType, IAudioDataType>::Value, bool>::Type = true> TSenderPtr<TDataType> Downcast(TUniquePtr<ISender>&& InPtr)` (scope `Metasound`) — For generic senders for copyable types:
- L985 _function_ `template <typename TDataType, typename TEnableIf<!std::is_copy_constructible<TDataType>::value && !TIsDerivedFrom<TDataType, IAudioDataType>::Value, bool>::Type = true> TSenderPtr<TDataType> Downcast(TUniquePtr<ISender>&& InPtr)` (scope `Metasound`) — For invalid types (non-copyable AND not an audio type):
- L992 _function_ `template <typename TDataType, typename TEnableIf<TIsDerivedFrom<TDataType, IAudioDataType>::Value, bool>::Type = true> TReceiverPtr<TDataType> Downcast(TUniquePtr<IReceiver>&& InPtr)` (scope `Metasound`) — For audio receivers:
- L1000 _function_ `template <typename TDataType, typename TEnableIf<std::is_copy_constructible<TDataType>::value && !TIsDerivedFrom<TDataType, IAudioDataType>::Value, bool>::Type = true> TReceiverPtr<TDataType> Downcast(TUniquePtr<IReceiver>&& InPtr)` (scope `Metasound`) — For generic receivers for copyable types:
- L1008 _function_ `template <typename TDataType, typename TEnableIf<!std::is_copy_constructible<TDataType>::value && !TIsDerivedFrom<TDataType, IAudioDataType>::Value, bool>::Type = true> TReceiverPtr<TDataType> Downcast(TUniquePtr<IReceiver>&& InPtr)` (scope `Metasound`) — For invalid types (non-copyable AND not an audio type):

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundSendNode.h` (Public)


#### class `Metasound::SendNodePrivate::TSendOperator`  
`template<typename TDataType> class TSendOperator : public TExecutableOperator<TSendOperator<TDataType>>`  
_L46-162_
- inherits: `TExecutableOperator<TSendOperator<TDataType>>`
- L51 _public function_ `TSendOperator(TDataReadReference<TDataType> InInputData, TDataReadReference<FSendAddress> InSendAddress, const FOperatorSettings& InOperatorSettings) : InputData(InInputData) , SendAddress(InSendAddress) , CachedSendAddress(*InSendAddress) , CachedSenderParams({InOperatorSettings, 0.0f}) , Sender(nullptr)`
- L61 _public function_ `virtual ~TSendOperator()`
- L66 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override`
- L75 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override`
- L79 _public function_ `void Execute()`
- L92 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L100 _public function_ `static FVertexInterface DeclareVertexInterface()`
- L105 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L111 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L133 _private function_ `FSendAddress GetSendAddressWithDataType(const FSendAddress& InAddress) const`
- L141 _private function_ `TSenderPtr<TDataType> CreateNewSender() const`
- L150 _private function_ `void ResetSenderAndCleanupChannel()`
- L156 _private member_ `TDataReadReference<TDataType> InputData;`
- L157 _private member_ `TDataReadReference<FSendAddress> SendAddress;`
- L158 _private member_ `FSendAddress CachedSendAddress;`
- L159 _private member_ `FSenderInitParams CachedSenderParams;`
- L161 _private member_ `TSenderPtr<TDataType> Sender;`

#### class `Metasound::TSendNode`  
`template<typename TDataType> class TSendNode : public TNodeFacade<SendNodePrivate::TSendOperator<TDataType>>`  
_L168-191_
- inherits: `TNodeFacade<SendNodePrivate::TSendOperator<TDataType>>`
- L171 _public typedef_ `using FOperator = SendNodePrivate::TSendOperator<TDataType>;`
- L172 _public typedef_ `using FSuper = TNodeFacade<SendNodePrivate::TSendOperator<TDataType>>;`
- L176 _public function_ `static const FVertexName& GetSendInputName()` — `UE_DEPRECATED(5.8, "This will no longer be supported")`
- L182 _public function_ `static FVertexInterface DeclareVertexInterface()` — `UE_DEPRECATED(5.8, "This will no longer be supported")`
- L187 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "MetasoundFrontend"`
- L21 _namespace_ `namespace Metasound`
- L23 _namespace_ `namespace SendVertexNames` (scope `Metasound`)
- L28 _namespace_ `namespace SendNodePrivate` (scope `Metasound`)
- L31 _prototype_ `FVertexInterface CreateVertexInterface(const FName& InDataTypeName);` (scope `Metasound::SendNodePrivate`)
- L34 _prototype_ `FNodeClassName CreateNodeClassName(const FName& InDataTypeName);` (scope `Metasound::SendNodePrivate`)
- L37 _prototype_ `Frontend::FNodeClassRegistryKey CreateNodeClassRegistryKey(const FName& InDataTypeName);` (scope `Metasound::SendNodePrivate`)
- L40 _prototype_ `FNodeClassMetadata CreateNodeClassMetadata(const FName& InDataTypeName, const FText& InDataTypeDisplayText);` (scope `Metasound::SendNodePrivate`)
- L43 _prototype_ `const FName& GetSendInputName(const FName& InDataTypeName);` (scope `Metasound::SendNodePrivate`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundTime.h` (Public)


#### class `Metasound::FTime`  
`class FTime`  
_L12-368_
- desc: Strongly typed time class
- L14 _private typedef_ `using TimeType = double;`
- L17 _private member_ `TimeType Time = 0;`
- L20 _public function_ `FTime()`
- L24 _public function_ `explicit FTime(TimeType InTime) : Time(InTime)`
- L29 _public function_ `explicit FTime(float InTime) : Time(static_cast<TimeType>(InTime))`
- L34 _public function_ `FTime(const FTime& InOtherTime) : Time(InOtherTime.Time)`
- L39 _public function_ `static const FTime& Zero()`
- L46 _public function_ `TimeType GetSeconds() const` — Return the time as seconds.
- L51 _public function_ `FTime& operator=(const FTime& InRHS)`
- L89 _public function_ `FTime& operator-=(const FTime& InRHS)`
- L111 _public function_ `FTime& operator+=(const FTime& InRHS)`
- L133 _public function_ `FTime operator-(const FTime& InRHS) const`
- L152 _public function_ `FTime operator+(const FTime& InRHS) const`
- L172 _public function_ `template<typename ArithmeticType> ArithmeticType operator*(const FTime& InRHS) const`
- L193 _public function_ `template<typename ArithmeticType> ArithmeticType operator/(const FTime& InRHS) const`
- L213 _public function_ `bool operator<(const FTime& InRHS) const`
- L232 _public function_ `bool operator<=(const FTime& InRHS) const`
- L251 _public function_ `bool operator>(const FTime& InRHS) const`
- L270 _public function_ `bool operator>=(const FTime& InRHS) const`
- L296 _public function_ `bool operator!=(const FTime& InRHS) const`
- L328 _public function_ `template<typename ArithmeticType = TimeType> static ArithmeticType ToMilliseconds(const FTime& InTime)`
- L335 _public function_ `template<typename ArithmeticType = TimeType> static ArithmeticType ToMicroseconds(const FTime& InTime)`
- L342 _public function_ `template<typename ArithmeticType> static FTime FromSeconds(const ArithmeticType& InSeconds)`
- L349 _public function_ `template<typename ArithmeticType> static FTime FromMilliseconds(const ArithmeticType& InMilliseconds)`
- L356 _public function_ `template<typename ArithmeticType> static FTime FromMicroseconds(const ArithmeticType& InMicroseconds)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Metasound`
- L58 _function_ `template<typename ArithmeticType> friend ArithmeticType& operator*=(ArithmeticType& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L66 _function_ `template<typename ArithmeticType> friend FTime& operator*=(FTime& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L74 _function_ `template<typename ArithmeticType> friend ArithmeticType& operator/=(ArithmeticType& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L82 _function_ `template<typename ArithmeticType> friend FTime& operator/=(FTime& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L96 _function_ `template<typename ArithmeticType> friend ArithmeticType& operator-=(ArithmeticType& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L104 _function_ `template<typename ArithmeticType> friend FTime& operator-=(FTime& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L118 _function_ `template<typename ArithmeticType> friend ArithmeticType& operator+=(ArithmeticType& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L126 _function_ `template<typename ArithmeticType> friend FTime& operator+=(FTime& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L139 _function_ `template<typename ArithmeticType> friend ArithmeticType operator-(const ArithmeticType& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L146 _function_ `template<typename ArithmeticType> friend FTime operator-(const FTime& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L158 _function_ `template<typename ArithmeticType> friend ArithmeticType operator+(const ArithmeticType& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L165 _function_ `template<typename ArithmeticType> friend FTime operator+(const FTime& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L179 _function_ `template<typename ArithmeticType> friend ArithmeticType operator*(const ArithmeticType& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L186 _function_ `template<typename ArithmeticType> friend FTime operator*(const FTime& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L200 _function_ `template<typename ArithmeticType> friend ArithmeticType& operator/(const ArithmeticType& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L207 _function_ `template<typename ArithmeticType> friend FTime operator/(const FTime& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L219 _function_ `template<typename ArithmeticType> friend bool operator<(const ArithmeticType& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L226 _function_ `template<typename ArithmeticType> friend bool operator<(const FTime& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L238 _function_ `template<typename ArithmeticType> friend bool operator<=(const ArithmeticType& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L245 _function_ `template<typename ArithmeticType> friend bool operator<=(const FTime& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L257 _function_ `template<typename ArithmeticType> friend bool operator>(const FTime& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L264 _function_ `template<typename ArithmeticType> friend bool operator>(const ArithmeticType& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L276 _function_ `template<typename ArithmeticType> friend bool operator>=(const ArithmeticType& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L283 _function_ `template<typename ArithmeticType> friend bool operator>=(const FTime& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L290 _function_ `template<typename ArithmeticType> friend bool operator!=(const ArithmeticType& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L302 _function_ `template<typename ArithmeticType> friend bool operator!=(const FTime& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L308 _function_ `friend bool operator==(const FTime& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L314 _function_ `template<typename ArithmeticType> friend bool operator==(const ArithmeticType& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L321 _function_ `template<typename ArithmeticType> friend bool operator==(const FTime& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L362 _function_ `friend inline uint32 GetTypeHash(const FTime& InTime)` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundTransmissionRegistration.h` (Public)


#### struct `Metasound::MetasoundTransmissionPrivate::TEnableTransmission`  
`template<typename DataType> struct TEnableTransmission`  
_L16-19_
- desc: Determines whether send/receive nodes are enabled for a specific data type.
- L18 _public member_ `static constexpr bool Value = true;`

#### struct `Metasound::MetasoundTransmissionPrivate::TTransmissionSupport`  
`template<typename DataType> struct TTransmissionSupport`  
_L26-42_
- desc: TTransmissionSupport determines whether the send/receive system is supported for a given data type. It is used to add send/receive support when possible, and avoid errors when registering data types that do not support the transmission system.
- L29 _private member_ `static constexpr bool bEnabled = TEnableTransmission<DataType>::Value;`
- L33 _private member_ `static constexpr bool bIsCopyable = std::is_copy_assignable<DataType>::value && std::is_copy_constructible<DataType>::value;` — All types that support copy assignment and copy construction can be used in the transmission system.
- L37 _private member_ `static constexpr bool bIsAudioDataType = std::is_base_of<IAudioDataType, DataType>::value;` — IAudioDataType derived classes have specialized templates for the transmission system.
- L41 _public member_ `static constexpr bool bIsTransmissionSupported = bEnabled && (bIsCopyable || bIsAudioDataType);`
- L52 _public member_ `static constexpr bool bIsCopyable = std::is_copy_assignable<ElementType>::value && std::is_copy_constructible<ElementType>::value;`
- L54 _public member_ `static constexpr bool bEnabled = TEnableTransmission<TArray<ElementType>>::Value;`
- L58 _public member_ `static constexpr bool bIsTransmissionSupported = bIsCopyable && bEnabled;`

#### struct `Metasound::MetasoundTransmissionPrivate::TTransmissionSupport`  
`template<typename ElementType> struct TTransmissionSupport<TArray<ElementType>>`  
_L50-59_
- desc: At the time of writing this code, TArray incorrectly defines a copy constructor even when the underlying elements or not copyable. Normally this results in compilation errors when trying to utilize the erroneously defined TArray copy constructor. This specialization checks the underlying TArray element type to determine if the array is copyable.
- L29 _private member_ `static constexpr bool bEnabled = TEnableTransmission<DataType>::Value;`
- L33 _private member_ `static constexpr bool bIsCopyable = std::is_copy_assignable<DataType>::value && std::is_copy_constructible<DataType>::value;` — All types that support copy assignment and copy construction can be used in the transmission system.
- L37 _private member_ `static constexpr bool bIsAudioDataType = std::is_base_of<IAudioDataType, DataType>::value;` — IAudioDataType derived classes have specialized templates for the transmission system.
- L41 _public member_ `static constexpr bool bIsTransmissionSupported = bEnabled && (bIsCopyable || bIsAudioDataType);`
- L52 _public member_ `static constexpr bool bIsCopyable = std::is_copy_assignable<ElementType>::value && std::is_copy_constructible<ElementType>::value;`
- L54 _public member_ `static constexpr bool bEnabled = TEnableTransmission<TArray<ElementType>>::Value;`
- L58 _public member_ `static constexpr bool bIsTransmissionSupported = bIsCopyable && bEnabled;`

#### struct `Metasound::FTransmissionDataChannelFactory`  
`struct FTransmissionDataChannelFactory`  
_L62-96_
- L75 _public function_ `static TSharedPtr<IDataChannel, ESPMode::ThreadSafe> CreateDataChannel(const FOperatorSettings& InOperatorSettings)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace MetasoundTransmissionPrivate` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundTrigger.h` (Public)


#### class `Metasound::FTrigger`  
`class FTrigger`  
_L23-191_
- desc: FTrigger supports sample accurate triggering, sample accurate internal tracking, and a convenient interface for running trigger-aligned audio signal processing routines on buffers.. FTriggers are triggered using FTrigger::TriggerTime or FTrigger::TriggerFrame. FTriggers track time internally by calling FTrigger::Advance. Executing audio signal processing on buffers can be performed by calling FTrigger::ExecuteBlock or FTrigger::LookAhead.
- L31 _public prototype_ `explicit FTrigger(const FOperatorSettings& InSettings, bool bShouldTrigger);` — FTrigger constructor. @param InSettings - Operator settings. @param bShouldTrigger - If true, triggers first sample.
- L38 _public prototype_ `explicit FTrigger(const FOperatorSettings& InSettings, int32 InFrameToTrigger);` — FTrigger constructor. @param InFrameToTrigger - Set specific frame to trigger. @param InSettings - Operator settings.
- L44 _public prototype_ `FTrigger(const FOperatorSettings& InSettings);` — FTrigger constructor. By default it is not triggered. @param InSettings - Operator settings.
- L50 _public prototype_ `void AssignRawParameter(const void* ParamPackPayload);` — For use when a Trigger request is found in a Parameter Pack @param ParamPackPayload - A pointer to a bool which should always be 'true'.
- L56 _public prototype_ `void TriggerFrame(int32 InFrameToTrigger);` — Trigger a specific frame in the future. @param InFrameToTrigger - Index of frame to trigger.
- L59 _public prototype_ `void AdvanceBlock();` — Advance internal frame counters by block size.
- L62 _public prototype_ `void Advance(int32 InNumFrames);` — Advance internal frame counters by specific frame count.
- L65 _public prototype_ `int32 Num() const;` — Number of triggered frames.
- L68 _public prototype_ `int32 NumTriggeredInBlock() const;` — Returns true if there is a trigger in the current block of audio
- L76 _public prototype_ `int32 operator[](int32 InTriggerIndex) const;` — Returns frame index for a given trigger index. @param InIndex - Index of trigger. Must be a value between 0 and Num(). @return The frame of the trigger.
- L82 _public prototype_ `int32 First() const;` — Returns frame index for the first trigger in the block. @return The frame of the first trigger in the block or -1 if there is no trigger in the block.
- L88 _public prototype_ `int32 Last() const;` — Returns frame index for the last trigger in the block. @return The frame of the last trigger in the block or -1 if there is no trigger in the block.
- L91 _public prototype_ `bool IsTriggered() const;` — Returns true if there are any triggered frames.
- L94 _public prototype_ `bool IsTriggeredInBlock() const;` — Returns true there is a trigger in the current block of audio.
- L100 _public prototype_ `operator bool() const;` — Implicit conversion of FTrigger into bool by calling IsTriggeredInBlock() @return Returns true if frame is triggered in current block.
- L103 _public prototype_ `void Reset();` — Removes all triggered frames.
- L106 _public prototype_ `void RemoveAfter(int32 InFrameIndex);` — Removes all triggers which occur after the frame index.
- L120 _public function_ `template<typename PreTriggerType, typename OnTriggerType> void ExecuteBlock(PreTriggerType InPreTrigger, OnTriggerType InOnTrigger) const` — Executes one block of frames and calls underlying InPreTrigger and InOnTrigger functions with frame indices. @param InPreTrigger - A function which handles frames before the first trigger in the current block. The function must accept the arguments (int32 StartFrame, int32 EndFrame). @param InOnTrigger - A function which handles frames starting with the triggers index and ending the next trigger index or the number of frames in a block.. The function must accept the arguments (int32 StartFrame, int32 EndFrame).
- L138 _public function_ `template<typename PreTriggerType, typename OnTriggerType> void LookAhead(int32 InNumFrames, PreTriggerType InPreTrigger, OnTriggerType InOnTrigger) const` — Executes a desired number of frames and calls underlying InPreTrigger and InOnTrigger functions with frame indices. @param InNumFrames - The number of frames to look ahead. @param InPreTrigger - A function which handles frames before the first trigger in the range of frames. The function must accept the arguments (int32 StartFrame, int32 EndFrame). @param InOnTrigger - A function which handles frames starting with the triggers index and ending the next trigger index or InNumFrames The function must accept the arguments (int32 StartFrame, int32 EndFrame).
- L148 _public function_ `const TArray<int32>& GetTriggeredFrames() const`
- L154 _private prototype_ `void UpdateLastTriggerIndexInBlock();`
- L157 _private function_ `template<typename PreTriggerType, typename OnTriggerType> void ExecuteFrames(int32 InNumFrames, int32 InLastTriggerIndex, PreTriggerType InPreTrigger, OnTriggerType InOnTrigger) const`
- L183 _private member_ `TArray<int32> TriggeredFrames;`
- L185 _private member_ `bool bHasAdvanced = false;`
- L186 _private member_ `bool bTriggeredFromInit = false;`
- L187 _private member_ `bool bHasTrigger = false;`
- L188 _private member_ `int32 NumFramesPerBlock = 0;`
- L189 _private member_ `FSampleRate SampleRate = 0;`
- L190 _private member_ `int32 LastTriggerIndexInBlock = 0;`

#### struct `Metasound::TPostExecutableDataType`  
`template<> struct TPostExecutableDataType<FTrigger>`  
_L194-202_
- L196 _public member_ `static constexpr bool bIsPostExecutable = true;`
- L198 _public function_ `static void PostExecute(FTrigger& InOutData)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L12 _namespace_ `namespace Metasound`
- L207 _prototype_ `const TCHAR* LexToString(const Metasound::FTrigger& Trigger);`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/MetasoundVariableRegistration.h` (Public)


#### struct `Metasound::Frontend::TEnableVariables`  
`template<typename DataType> struct TEnableVariables`  
_L14-18_
- desc: Allow or disallow types to be registered as MetaSound Variables.
- L17 _public member_ `static constexpr bool Value = true;` — By default, all registered MetaSound data types are variables.

#### struct `Metasound::Frontend::TVariablesSupport`  
`template<typename DataType> struct TVariablesSupport`  
_L24-36_
- desc: Determine if data type supports necessary operations required of all MetaSound variable types.
- L29 _private member_ `static constexpr bool bIsCopyAssignable = std::is_copy_assignable<DataType>::value;`
- L30 _private member_ `static constexpr bool bIsParsableFromLiteral = TLiteralTraits<DataType>::bIsParsableFromAnyLiteralType;`
- L35 _public member_ `static constexpr bool bIsVariableSupported = bIsCopyAssignable && bIsParsableFromLiteral;` — MetaSound variables must be copy-assignable and parsable from a FLiteral

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`
- L10 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/NodeTemplates/MetasoundFrontendNodeTemplateAudioAnalyzer.h` (Public)


#### class `Metasound::Frontend::FAudioAnalyzerNodeTemplate`  
`class FAudioAnalyzerNodeTemplate : public FNodeTemplateBase`  
_L10-28_
- inherits: `FNodeTemplateBase`
- L13 _public member_ `static const FMetasoundFrontendClassName ClassName;`
- L14 _public member_ `static const FMetasoundFrontendVersionNumber VersionNumber;`
- L16 _public prototype_ `virtual FMetasoundFrontendNodeInterface GenerateNodeInterface(FNodeTemplateGenerateInterfaceParams InParams) const override;`
- L17 _public prototype_ `virtual const FMetasoundFrontendClassName& GetClassName() const override;`
- L18 _public prototype_ `virtual TUniquePtr<INodeTemplateTransform> GenerateNodeTransform() const override;`
- L19 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendClass() const override;`
- L20 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetNodeInputAccessType(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, const FGuid& InVertexID) const override;`
- L21 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetNodeOutputAccessType(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, const FGuid& InVertexID) const override;`
- L22 _public prototype_ `virtual const FMetasoundFrontendVersionNumber& GetVersionNumber() const override;`
- L23 _public prototype_ `virtual bool IsInputAccessTypeDynamic() const override;`
- L24 _public prototype_ `virtual bool IsInputConnectionUserModifiable() const override;`
- L25 _public prototype_ `virtual bool IsOutputAccessTypeDynamic() const override;`
- L26 _public prototype_ `virtual bool IsOutputConnectionUserModifiable() const override;`
- L27 _public prototype_ `virtual bool IsValidNodeInterface(const FMetasoundFrontendNodeInterface& InNodeInterface) const override;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L8 _namespace_ `namespace Metasound`
- L8 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/NodeTemplates/MetasoundFrontendNodeTemplateInput.h` (Public)


#### class `Metasound::Frontend::FInputNodeTemplate`  
`class FInputNodeTemplate : public FRerouteNodeTemplate`  
_L25-68_
- inherits: `FRerouteNodeTemplate`
- desc: Specialized node that connects an input node's single output to various input destinations. While similar to reroute nodes, primarily exists to visually distinguish an input having multiple locations in a visual graph while sharing implementation at runtime, while also differentiating general input style from a typical reroute.
- L28 _public member_ `static const FMetasoundFrontendClassName ClassName;`
- L29 _public member_ `static const FMetasoundFrontendVersionNumber VersionNumber;`
- L31 _public prototype_ `static const FInputNodeTemplate& GetChecked();`
- L32 _public prototype_ `static const FNodeRegistryKey& GetRegistryKey();`
- L34 _public prototype_ `virtual ~FInputNodeTemplate() = default;`
- L39 _public prototype_ `static const FMetasoundFrontendNode* CreateNode(FMetaSoundFrontendDocumentBuilder& InOutBuilder, FName InputName, const FGuid* InPageID = nullptr);` — Adds template node and connects with the input of the provided name on the page with the provided id (defaults to builder's build page ID if not provided)
- L42 _public prototype_ `virtual const TArray<FMetasoundFrontendClassInputDefault>* FindNodeClassInputDefaults(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, FName VertexName) const override;`
- L43 _public prototype_ `virtual const FMetasoundFrontendClassName& GetClassName() const override;`
- L46 _public prototype_ `virtual FText GetNodeDisplayName(const IMetaSoundDocumentInterface& Interface, const FGuid& InPageID, const FGuid& InNodeID) const override;`
- L49 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendClass() const override;`
- L50 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetNodeInputAccessType(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, const FGuid& InVertexID) const override;`
- L51 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetNodeOutputAccessType(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, const FGuid& InVertexID) const override;`
- L54 _public prototype_ `virtual FText GetOutputVertexDisplayName(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, FName OutputName) const override;`
- L55 _public prototype_ `virtual bool HasRequiredConnections(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, FString* OutMessage = nullptr) const override;`
- L62 _public prototype_ `bool Inject(FMetaSoundFrontendDocumentBuilder& InOutBuilder, bool bForceNodeCreation = false) const;` — Injects template nodes between builder's document inputs not connected to existing template inputs, copying locational data from the represented input metadata. If bForceNodeCreation is false, only generates a template input node if a connection between the input and other nodes exists. If true, will inject template node irrespective of whether or not the input has connections.
- L65 _public prototype_ `virtual bool IsInputAccessTypeDynamic() const override;`
- L66 _public prototype_ `virtual bool IsInputConnectionUserModifiable() const override;`
- L67 _public prototype_ `virtual bool IsOutputAccessTypeDynamic() const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L19 _namespace_ `namespace Metasound`
- L19 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/NodeTemplates/MetasoundFrontendNodeTemplateReroute.h` (Public)


#### class `Metasound::Frontend::FRerouteNodeTemplate`  
`class FRerouteNodeTemplate : public FNodeTemplateBase`  
_L17-58_
- inherits: `FNodeTemplateBase`
- L20 _public member_ `static const FMetasoundFrontendClassName ClassName;`
- L22 _public member_ `static const FMetasoundFrontendVersionNumber VersionNumber;`
- L24 _public prototype_ `static const FNodeRegistryKey& GetRegistryKey();`
- L27 _public function_ `static FMetasoundFrontendNodeInterface CreateNodeInterfaceFromDataType(FName InDataType)` — `UE_DEPRECATED(5.5, "Look-up template via registry and use non-static GenerateNodeInterface instead with provided params")`
- L29 _public prototype_ `virtual ~FRerouteNodeTemplate() = default;`
- L31 _public prototype_ `virtual const FMetasoundFrontendClassName& GetClassName() const override;`
- L34 _public prototype_ `virtual FText GetNodeDisplayName(const IMetaSoundDocumentInterface& DocumentInterface, const FGuid& InPageID, const FGuid& InNodeID) const override;`
- L37 _public prototype_ `virtual FMetasoundFrontendNodeInterface GenerateNodeInterface(FNodeTemplateGenerateInterfaceParams InParams) const override;`
- L38 _public prototype_ `virtual TUniquePtr<INodeTemplateTransform> GenerateNodeTransform() const override;`
- L39 _public prototype_ `virtual const FMetasoundFrontendClass& GetFrontendClass() const override;`
- L40 _public prototype_ `virtual const TArray<FMetasoundFrontendClassInputDefault>* FindNodeClassInputDefaults(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, FName VertexName) const override;`
- L41 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetNodeInputAccessType(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, const FGuid& InVertexID) const override;`
- L42 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetNodeOutputAccessType(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, const FGuid& InVertexID) const override;`
- L43 _public prototype_ `virtual const FMetasoundFrontendVersionNumber& GetVersionNumber() const override;`
- L44 _public prototype_ `virtual bool IsInputAccessTypeDynamic() const override;`
- L45 _public prototype_ `virtual bool IsInputConnectionUserModifiable() const override;`
- L46 _public prototype_ `virtual bool IsOutputConnectionUserModifiable() const override;`
- L47 _public prototype_ `virtual bool IsOutputAccessTypeDynamic() const override;`
- L48 _public prototype_ `virtual bool IsValidNodeInterface(const FMetasoundFrontendNodeInterface& InNodeInterface) const override;`
- L51 _public prototype_ `virtual bool HasRequiredConnections(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FGuid& InPageID, const FGuid& InNodeID, FString* OutMessage = nullptr) const override;`
- L53 _public prototype_ `virtual bool OnEdgeAdded(const FTemplateNodeEdgeTransactionContext& TransactionContext, DynamicGraph::FDynamicOperatorTransactor& OutTransactor) const override;`
- L54 _public prototype_ `virtual bool OnNodeAdded(const FTemplateNodeTransactionContext& TransactionContext, DynamicGraph::FDynamicOperatorTransactor& OutTransactor) const override;`
- L55 _public prototype_ `virtual bool OnRemoveSwappingEdge(const FTemplateNodeEdgeRemoveTransactionContext& TransactionContext, DynamicGraph::FDynamicOperatorTransactor& OutTransactor) const override;`
- L56 _public prototype_ `virtual bool OnRemoveSwappingNode(const FTemplateNodeTransactionContext& TransactionContext, DynamicGraph::FDynamicOperatorTransactor& OutTransactor) const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METASOUNDFRONTEND_API`
- L15 _namespace_ `namespace Metasound`
- L15 _namespace_ `namespace Frontend` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Traits/MetasoundNodeConstructorTraits.h` (Public)


#### struct `Metasound::TIsNodeConstructorSupported`  
`template<typename T> struct TIsNodeConstructorSupported`  
_L13-21_
- desc: Determines whether the constructor provided by the node is usable in node registration.
- L16 _private member_ `static constexpr bool bIsConstructibleWithFNodeData = std::is_constructible_v<T, ::Metasound::FNodeData>;`
- L17 _private member_ `static constexpr bool bIsConstructibleWithFNodeDataAndClassMetadata = std::is_constructible_v<T, ::Metasound::FNodeData, TSharedRef<const FNodeClassMetadata>>;`
- L20 _public member_ `static constexpr bool Value = bIsConstructibleWithFNodeData || bIsConstructibleWithFNodeDataAndClassMetadata;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundFrontend/Public/Traits/MetasoundNodeStaticMemberTraits.h` (Public)


#### class `Metasound::TIsCreateNodeClassMetadataDeclared`  
`template <typename U> class TIsCreateNodeClassMetadataDeclared`  
_L10-25_
- L17 _private prototype_ `template<typename T> static uint8 Check(Helper<FNodeClassMetadata(*)(), &T::CreateNodeClassMetadata>*);`
- L19 _private prototype_ `template<typename T> static uint16 Check(...);`
- L24 _public member_ `static constexpr bool Value = sizeof(Check<U>(0)) == sizeof(uint8);` — If the function exists, then "Value" is true. Otherwise "Value" is false.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Metasound`
