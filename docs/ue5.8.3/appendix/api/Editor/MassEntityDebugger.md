# Editor / MassEntityDebugger

- module root: `Source/Editor/MassEntityDebugger`
- headers: 21; symbols: 634
- symbol kinds: class=27, delegate=8, enum=6, enumerator=21, function=58, macro=3, member=224, namespace=13, prototype=254, struct=16, typedef=4
- PrivateDependencyModuleNames: ApplicationCore, Json, ToolWidgets
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, MassCore, MassEntity, Projects, Slate, SlateCore, UMG, UnrealEd, WorkspaceMenuStructure

### `Source/Editor/MassEntityDebugger/Private/MassDebuggerModel.h` (Private)


#### struct `UE::MassDebugger::FFragmentEntry`  
`struct FFragmentEntry`  
_L29-51_
- desc: A serializable wrapper for a fragment type and access method used for editable queries
- L32 _public prototype_ `TSharedPtr<FJsonObject> SerializeToJson() const;` — Convert this struct to a Json object
- L35 _public prototype_ `bool DeserializeFromJson(const TSharedPtr<FJsonObject>& JsonObject);` — Populate this struct from a Json object created with the above Serialize method
- L38 _public prototype_ `bool DeserializeFromJsonString(const FString& JsonString);` — Parse Json string then serialize from that (paste)
- L41 _public member_ `TWeakObjectPtr<const UScriptStruct> StructType;` — The current struct type (selected in the editor combo box)
- L44 _public member_ `EMassFragmentAccess AccessMode = EMassFragmentAccess::ReadOnly;` — Access mode for this fragment entry in a query (not used for tags)
- L47 _public member_ `EMassFragmentPresence Presence = EMassFragmentPresence::All;` — Presense requred for this fragment in a query
- L50 _public member_ `bool bShowAccessMode = true;` — Used to hide access mode when unused (e.g. with tags)

#### struct `UE::MassDebugger::FEditableQuery`  
`struct FEditableQuery`  
_L54-94_
- desc: A serializable and editable representation of a FMassEntityQuery
- L60 _public prototype_ `TSharedPtr<FJsonObject> SerializeToJson() const;` — Convert this entire object and it FragmentEntry arrays to Json Used to save user queries created in the debugger UI
- L66 _public prototype_ `bool DeserializeFromJson(const TSharedPtr<FJsonObject>& JsonObject);` — Deserialize Json object hierarchy and populate this struct Used to load saved user queries when opening the debugger
- L72 _public prototype_ `bool DeserializeFromJsonString(const FString& JsonString);` — Parse the Json string then deserialize Used to paste queries in the debugger
- L78 _public prototype_ `void InitFromEntityQuery(const FMassEntityQuery& InQuery, FMassDebuggerModel& DebuggerModel);` — Create an editable query from a runtime query struct Used to view/edit and use runtime queries (e.g. on a Processor) in the editor
- L81 _public member_ `FString Name;` — The visible/editable name of the query
- L84 _public member_ `TArray<TSharedPtr<FFragmentEntry>> FragmentRequirements;` — Editable representation of the fragment requirements for the query
- L87 _public member_ `TArray<TSharedPtr<FFragmentEntry>> TagRequirements;` — Editable representation of the tag requirements for the query
- L93 _public prototype_ `FMassEntityQuery BuildEntityQuery(const TSharedRef<FMassEntityManager> EntityManager);` — Create a usable runtime query from this editable query Used by the debugger to manually run entity queries or for breakpoints

#### enum `EMassDebuggerSelectionMode`  
`enum class EMassDebuggerSelectionMode : uint8`  
_L97-105_
- L99 _public enumerator_ `None`
- L100 _public enumerator_ `Processor`
- L101 _public enumerator_ `Archetype`
- L104 _public enumerator_ `MAX` — @todo future: Fragment

#### enum `EMassDebuggerProcessorSelection`  
`enum class EMassDebuggerProcessorSelection : uint8`  
_L107-112_
- L109 _public enumerator_ `None`
- L110 _public enumerator_ `Selected`
- L111 _public enumerator_ `MAX`

#### enum `EMassDebuggerProcessingGraphNodeSelection`  
`enum class EMassDebuggerProcessingGraphNodeSelection : uint8`  
_L114-120_
- L116 _public enumerator_ `None`
- L117 _public enumerator_ `WaitFor`
- L118 _public enumerator_ `Block`
- L119 _public enumerator_ `MAX`

#### struct `FMassDebuggerQueryData`  
`struct FMassDebuggerQueryData`  
_L123-136_
- L125 _public prototype_ `FMassDebuggerQueryData(const FMassEntityQuery& Query, const FText& InLabel);`
- L126 _public prototype_ `FMassDebuggerQueryData(const FMassSubsystemRequirements& SubsystemRequirements, const FText& InLabel);`
- L128 _public member_ `FMassExecutionRequirements ExecutionRequirements;`
- L129 _public member_ `FText Label;`
- L130 _public member_ `FText AdditionalInformation;`
- L132 _public member_ `FMassEntityQuery SourceQuery;`
- L134 _public prototype_ `int32 GetTotalBitsUsedCount();`
- L135 _public prototype_ `bool IsEmpty() const;`

#### struct `FMassDebuggerArchetypeData`  
`struct FMassDebuggerArchetypeData`  
_L138-179_
- L140 _public prototype_ `FMassDebuggerArchetypeData(const FMassArchetypeHandle& ArchetypeHandle);`
- L142 _public member_ `FMassArchetypeHandle Handle;`
- L144 _public member_ `FMassArchetypeCompositionDescriptor Composition;`
- L146 _public member_ `FMassElementBitSet SparseElementsBitset;`
- L149 _public member_ `uint32 CompositionHash = 0;` — Hash of the Compositions.
- L151 _public member_ `uint32 FullHash = 0;` — Combined hash of composition and shared fragments.
- L154 _public member_ `UE::Mass::Debug::FArchetypeStats ArchetypeStats;` — Archetype statistics
- L157 _public member_ `TArray<TSharedPtr<FMassDebuggerArchetypeData>> Children;` — Child debugger data (same as parent, but changed in some way)
- L159 _public member_ `TWeakPtr<FMassDebuggerArchetypeData> Parent;` — Parent debugger data.
- L163 _public member_ `int32 Index = INDEX_NONE;` — Index in FMassDebuggerModel::CachedArchetypes
- L165 _public member_ `FText Label;` — Display label
- L167 _public member_ `FText LabelLong;` — Display label
- L169 _public member_ `FText LabelTooltip;` — Display label tooltip
- L171 _public member_ `FText HashLabel;` — FullHash as a display string
- L173 _public member_ `FString PrimaryDebugName;` — Primary debug name, used for grouping derived archetypes.
- L176 _public member_ `bool bIsSelected = false;` — True if the archetype is selected.
- L178 _public prototype_ `int32 GetTotalBitsUsedCount() const;`

#### struct `FMassDebuggerProcessorData`  
`struct FMassDebuggerProcessorData`  
_L181-203_
- L183 _public prototype_ `FMassDebuggerProcessorData(const UMassProcessor& InProcessor);`
- L184 _public prototype_ `FMassDebuggerProcessorData(const FMassEntityManager& InEntityManager, const UMassProcessor& InProcessor, const TMap<FMassArchetypeHandle, TSharedPtr<FMassDebuggerArchetypeData>>& InTransientArchetypesMap);`
- L187 _private prototype_ `void SetProcessor(const UMassProcessor& InProcessor);`
- L190 _public member_ `FString Name;`
- L191 _public member_ `FString Label;`
- L192 _public member_ `uint32 ProcessorHash = 0;`
- L193 _public member_ `bool bIsActive = true;`
- L194 _public member_ `TWeakPtr<const FMassEntityManager> EntityManager;`
- L195 _public member_ `TWeakObjectPtr<const UMassProcessor> Processor;`
- L196 _public member_ `EMassDebuggerProcessorSelection Selection = EMassDebuggerProcessorSelection::None;`
- L197 _public member_ `TSharedPtr<FMassDebuggerQueryData> ProcessorRequirements;`
- L198 _public member_ `TArray<TSharedPtr<FMassDebuggerQueryData>> Queries;`
- L199 _public member_ `TArray<TSharedPtr<FMassDebuggerArchetypeData>> ValidArchetypes;`
- L201 _public member_ `FString Description;`

#### struct `FMassDebuggerFragmentData`  
`struct FMassDebuggerFragmentData`  
_L205-225_
- L207 _public prototype_ `FMassDebuggerFragmentData(TNotNull<const UScriptStruct*> InFragment);`
- L209 _public function_ `bool operator==(const FMassDebuggerFragmentData& Other) const`
- L219 _public member_ `FText Name;`
- L220 _public member_ `TWeakObjectPtr<const UScriptStruct> Fragment;`
- L221 _public member_ `TWeakPtr<const FMassEntityManager> EntityManager;`
- L222 _public member_ `TArray<FMassArchetypeHandle> Archetypes;`
- L223 _public member_ `TArray<TWeakObjectPtr<UMassProcessor>> Processors;`
- L224 _public member_ `int32 NumEntities = 0;`

#### struct `FMassDebuggerBreakpointData`  
`struct FMassDebuggerBreakpointData`  
_L228-246_
- L230 _public prototype_ `FMassDebuggerBreakpointData() = default;`
- L231 _public prototype_ `FMassDebuggerBreakpointData(const UE::Mass::Debug::FBreakpoint& InBreakpoint, FMassDebuggerModel& Model);`
- L232 _public prototype_ `void ReconcileDataFromNames(FMassDebuggerModel& Model);`
- L233 _public prototype_ `void ReconcileDataFromEngineBreakpoint(FMassDebuggerModel& Model);`
- L234 _public prototype_ `void ApplyToEngine(FMassDebuggerModel& Model, bool bRefreshEngineBreakpoints = true);`
- L236 _public prototype_ `TSharedPtr<FJsonObject> SerializeToJson() const;`
- L237 _public prototype_ `bool DeserializeFromJson(const TSharedPtr<FJsonObject>& JsonObject);`
- L238 _public prototype_ `bool DeserializeFromJsonString(const FString& JsonString);`
- L240 _public member_ `UE::Mass::Debug::FBreakpoint BreakpointInstance;`
- L241 _public member_ `FString TriggerName;`
- L242 _public member_ `FString FilterName;`
- L243 _public member_ `TSharedPtr<FMassDebuggerFragmentData> TriggerFragment;`
- L244 _public member_ `TSharedPtr<FMassDebuggerProcessorData> TriggerProcessor;`
- L245 _public member_ `TSharedPtr<UE::MassDebugger::FEditableQuery> FilterQuery;`

#### struct `FMassDebuggerProcessingGraphNode`  
`struct FMassDebuggerProcessingGraphNode`  
_L248-258_
- L250 _public prototype_ `explicit FMassDebuggerProcessingGraphNode(const TSharedPtr<FMassDebuggerProcessorData>& InProcessorData, const UMassCompositeProcessor::FDependencyNode& InProcessorNode = UMassCompositeProcessor::FDependencyNode());`
- L252 _public prototype_ `FText GetLabel() const;`
- L254 _public member_ `TSharedPtr<FMassDebuggerProcessorData> ProcessorData;`
- L255 _public member_ `TArray<int32> WaitForNodes;`
- L256 _public member_ `TArray<int32> BlockNodes;`
- L257 _public member_ `EMassDebuggerProcessingGraphNodeSelection GraphNodeSelection = EMassDebuggerProcessingGraphNodeSelection::None;`

#### struct `FMassDebuggerProcessingGraph`  
`struct FMassDebuggerProcessingGraph`  
_L260-267_
- L262 _public prototype_ `FMassDebuggerProcessingGraph(const FMassDebuggerModel& DebuggerModel, TNotNull<const UMassCompositeProcessor*> InGraphOwner);`
- L264 _public member_ `FString Label;`
- L265 _public member_ `TArray<FMassDebuggerProcessingGraphNode> GraphNodes;`
- L266 _public member_ `bool bSingleTheadGraph = !bool(MASS_DO_PARALLEL);`

#### struct `FMassDebuggerEnvironment`  
`struct FMassDebuggerEnvironment`  
_L270-286_
- L272 _public prototype_ `explicit FMassDebuggerEnvironment(const TSharedRef<const FMassEntityManager>& InEntityManager);`
- L274 _public function_ `bool operator==(const FMassDebuggerEnvironment& Other) const`
- L276 _public prototype_ `FString GetDisplayName() const;`
- L277 _public prototype_ `TSharedPtr<const FMassEntityManager> GetEntityManager() const;`
- L278 _public prototype_ `TSharedPtr<FMassEntityManager> GetMutableEntityManager() const;`
- L279 _public function_ `bool IsWorldValid() const`
- L280 _public function_ `bool NeedsValidWorld() const`
- L282 _public member_ `TWeakPtr<const FMassEntityManager> EntityManager;`
- L283 _public member_ `TMap<FName, UE::Mass::Debug::FProcessorProviderFunction> ProcessorProviders;`
- L284 _public member_ `TWeakObjectPtr<UWorld> World;`
- L285 _public member_ `bool bNeedsValidWorld = false;`

#### struct `FMassDebuggerModel`  
`struct FMassDebuggerModel`  
_L289-438_
- L291 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRefresh);`
- L292 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnProcessorsSelected, TConstArrayView<TSharedPtr<FMassDebuggerProcessorData>>, ESelectInfo::Type);`
- L293 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnArchetypesSelected, TConstArrayView<TSharedPtr<FMassDebuggerArchetypeData>>, ESelectInfo::Type);`
- L294 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFragmentSelected, FName FragmentName);`
- L295 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnQueriesChanged);`
- L296 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnBreakpointsChanged);`
- L298 _public prototype_ `FMassDebuggerModel();`
- L299 _public prototype_ `~FMassDebuggerModel();`
- L301 _public prototype_ `void SetEnvironment(const TSharedPtr<FMassDebuggerEnvironment>& Item);`
- L303 _public prototype_ `void RefreshAll();`
- L305 _public prototype_ `void LoadQueriesFromDisk();`
- L307 _public prototype_ `void SelectProcessor(TSharedPtr<FMassDebuggerProcessorData>& Processor);`
- L308 _public prototype_ `void SelectProcessors(TArrayView<TSharedPtr<FMassDebuggerProcessorData>> Processors, ESelectInfo::Type SelectInfo);`
- L309 _public prototype_ `void ClearProcessorSelection();`
- L311 _public prototype_ `void SelectArchetypes(TArrayView<TSharedPtr<FMassDebuggerArchetypeData>> SelectedArchetypes, ESelectInfo::Type SelectInfo);`
- L312 _public prototype_ `void ClearArchetypeSelection();`
- L314 _public function_ `bool IsCurrentEnvironment(const FMassDebuggerEnvironment& InEnvironment) const`
- L315 _public function_ `bool IsCurrentEnvironmentValid() const`
- L316 _public function_ `bool HasEnvironmentSelected() const`
- L318 _public prototype_ `void CacheArchetypesData(TMap<FMassArchetypeHandle, TSharedPtr<FMassDebuggerArchetypeData>>& OutTransientArchetypesMap);`
- L319 _public prototype_ `void CacheProcessorsData(const TMap<FMassArchetypeHandle, TSharedPtr<FMassDebuggerArchetypeData>>& InTransientArchetypesMap, TArray<TNotNull<const UMassCompositeProcessor*>>& OutCompositeProcessors);`
- L320 _public prototype_ `void CacheProcessingGraphs(TConstArrayView<TNotNull<const UMassCompositeProcessor*>> InCompositeProcessors);`
- L322 _public prototype_ `void CacheFragmentData( TArray<TSharedPtr<FMassDebuggerFragmentData>>& OutData, const TConstArrayView<TWeakObjectPtr<const UScriptStruct>>& FragmentTypes, bool bAppend );`
- L327 _public prototype_ `void CacheFragmentData();`
- L328 _public prototype_ `TSharedPtr<FMassDebuggerFragmentData> FindFragmentData(const UScriptStruct* FragmentType);`
- L330 _public prototype_ `void CacheTagData();`
- L332 _public prototype_ `void LoadBreakpointsFromDisk();`
- L333 _public prototype_ `void SaveBreakpointsToDisk();`
- L334 _public prototype_ `void CreateBreakpoint();`
- L335 _public prototype_ `void CreateBreakpointFromString(const FString& InString);`
- L336 _public prototype_ `void ApplyBreakpointsToCurrentEnvironment();`
- L337 _public prototype_ `void ReconcileAllBreakpoints();`
- L338 _public prototype_ `void RemoveAllBreakpoints();`
- L339 _public prototype_ `void RemoveBreakpoint(UE::Mass::Debug::FBreakpointHandle Handle);`
- L341 _public prototype_ `float MinDistanceToSelectedArchetypes(const TSharedPtr<FMassDebuggerArchetypeData>& InArchetypeData) const;`
- L343 _public prototype_ `FText GetDisplayName() const;`
- L345 _public prototype_ `void MarkAsStale();`
- L346 _public prototype_ `bool IsStale() const;`
- L348 _public prototype_ `const TSharedPtr<FMassDebuggerProcessorData>& GetProcessorDataChecked(const UMassProcessor& Processor) const;`
- L350 _public prototype_ `void RegisterEntitiesView(TSharedRef<SMassEntitiesView> EntitiesView, int32 Index);`
- L352 _public member_ `static const int32 MaxEntityViewCount = 1;`
- L353 _public prototype_ `void ShowEntitiesView(int Index, FMassArchetypeHandle ArchetypeHandle);`
- L354 _public prototype_ `void ShowEntitiesView(int Index, TArray<FMassEntityHandle> EntitieHandles);`
- L355 _public prototype_ `void ShowEntitiesView(int Index, FMassEntityQuery& Query);`
- L356 _public prototype_ `void ShowEntitiesView(int Index, TConstArrayView<FMassEntityQuery*> InQueries);`
- L357 _public prototype_ `void ResetEntitiesViews();`
- L358 _public prototype_ `TWeakPtr<SMassEntitiesView> ShowEntitiesView(int32 Index);`
- L360 _public prototype_ `void RegisterQueryEditor(TSharedRef<UE::MassDebugger::SQueryEditorView> InQueryEditorView);`
- L361 _public prototype_ `void ShowQueryInEditor(const FMassEntityQuery& InQuery, const FString& InQueryName);`
- L362 _public prototype_ `void RefreshQueries();`
- L365 _protected prototype_ `void StoreArchetypes(const FMassEntityManager& EntityManager, TMap<FMassArchetypeHandle, TSharedPtr<FMassDebuggerArchetypeData>>& OutTransientArchetypesMap);`
- L367 _protected prototype_ `void ResetSelectedArchetypes();`
- L368 _protected prototype_ `void ResetSelectedProcessors();`
- L370 _protected prototype_ `void OnEntitySelected(const FMassEntityManager& EntityManager, const FMassEntityHandle EntityHandle);`
- L371 _protected prototype_ `void OnBreakpointsChanged();`
- L374 _public member_ `TWeakPtr<SMassDebugger> DebuggerWindow;`
- L376 _public member_ `FOnRefresh OnRefreshDelegate;`
- L377 _public member_ `FOnProcessorsSelected OnProcessorsSelectedDelegate;`
- L378 _public member_ `FOnArchetypesSelected OnArchetypesSelectedDelegate;`
- L379 _public member_ `FOnFragmentSelected OnFragmentSelectedDelegate;`
- L380 _public member_ `FOnBreakpointsChanged OnEditorBreakpointsChangedDelegate;`
- L381 _public member_ `FOnQueriesChanged OnQueriesChangedDelegate;`
- L383 _public member_ `EMassDebuggerSelectionMode SelectionMode = EMassDebuggerSelectionMode::None;`
- L385 _public member_ `TSharedPtr<FMassDebuggerEnvironment> Environment;`
- L396 _public member_ `TArray<TSharedPtr<UE::MassDebugger::FEditableQuery>> QueryList;`
- L397 _public member_ `TArray<TSharedPtr<FMassDebuggerFragmentData>> CachedTagData;`
- L398 _public member_ `TArray<TSharedPtr<FMassDebuggerFragmentData>> CachedFragmentData;`
- L399 _public member_ `TArray<TSharedPtr<FProcessorCollection>> CachedProcessorCollections;`
- L400 _public member_ `TArray<TSharedPtr<FMassDebuggerProcessorData>> SelectedProcessors;`
- L401 _public member_ `TArray<TSharedPtr<FMassDebuggerArchetypeData>> CachedAllArchetypes;`
- L402 _public member_ `TArray<TSharedPtr<FMassDebuggerArchetypeData>> CachedArchetypeRepresentatives;`
- L403 _public member_ `TArray<TSharedPtr<FMassDebuggerArchetypeData>> SelectedArchetypes;`
- L404 _public member_ `TArray<TSharedPtr<FMassDebuggerProcessingGraph>> CachedProcessingGraphs;`
- L405 _public member_ `TArray<TSharedPtr<FMassDebuggerBreakpointData>> CachedBreakpoints;`
- L408 _public member_ `TArray<TSharedPtr<FString>> ProcessorNames;` — Name lists and maps for easy lookup from widgets
- L409 _public member_ `TMap<FString, TWeakPtr<FMassDebuggerProcessorData>> ProcessorMap;`
- L410 _public member_ `TArray<TSharedPtr<FString>> FragmentNames;`
- L411 _public member_ `TMap<FString, TWeakPtr<FMassDebuggerFragmentData>> FragmentMap;`
- L412 _public member_ `TArray<TSharedPtr<FString>> TagNames;`
- L413 _public member_ `TMap<FString, TWeakPtr<FMassDebuggerFragmentData>> TagMap;`
- L414 _public member_ `TArray<TSharedPtr<FString>> QueryNames;`
- L415 _public member_ `TMap<FString, TWeakPtr<UE::MassDebugger::FEditableQuery>> QueryMap;`
- L417 _public member_ `TMap<FMassArchetypeHandle, TSharedPtr<FMassDebuggerArchetypeData>> HandleToArchetypeMap;`
- L419 _public member_ `TArray<TArray<float>> ArchetypeDistances;`
- L421 _public member_ `FString EnvironmentDisplayName;`
- L423 _public member_ `FDelegateHandle OnEntitySelectedHandle;`
- L424 _public member_ `FDelegateHandle OnBreakpointsChangedHandle;`
- L426 _public prototype_ `void SelectFragment(FName InFragementName);`
- L427 _public prototype_ `FName GetSelectedFragment();`
- L430 _protected member_ `TArray<TSharedPtr<FMassDebuggerProcessorData>> AllCachedProcessors;`
- L431 _protected member_ `TArray<TWeakPtr<SMassEntitiesView>> EntityViews;`
- L432 _protected member_ `TWeakPtr<UE::MassDebugger::SQueryEditorView> QueryEditorView;`
- L433 _protected member_ `FName SelectedFragmentName;`
- L437 _public member_ `TArray<TSharedPtr<FMassDebuggerProcessorData>> CachedProcessors;` — `UE_DEPRECATED(5.6, "CachedProcessors property is now deprecated. Use CachedProcessorCollections instead. ")`

#### struct `FMassDebuggerModel::FProcessorCollection`  
`struct FProcessorCollection`  
_L386-394_
- L388 _public function_ `FProcessorCollection(FName InLabel = FName()) : Label(InLabel)`
- L392 _public member_ `FName Label;`
- L393 _public member_ `TArray<TSharedPtr<FMassDebuggerProcessorData>> Container;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MassDebugger` (scope `UE`)
- L214 _function_ `friend uint32 GetTypeHash(const FMassDebuggerFragmentData& Item)`
- L291 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRefresh);`
- L292 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnProcessorsSelected, TConstArrayView<TSharedPtr<FMassDebuggerProcessorData>>, ESelectInfo::Type);`
- L293 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnArchetypesSelected, TConstArrayView<TSharedPtr<FMassDebuggerArchetypeData>>, ESelectInfo::Type);`
- L294 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFragmentSelected, FName FragmentName);`
- L295 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnQueriesChanged);`
- L296 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnBreakpointsChanged);`

### `Source/Editor/MassEntityDebugger/Private/MassDebuggerStyle.h` (Private)


#### class `FMassDebuggerStyle`  
`class FMassDebuggerStyle`  
_L10-25_
- L13 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L15 _public function_ `static ISlateStyle& Get()`
- L16 _public prototype_ `static FName GetStyleSetName();`
- L18 _public function_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL)`
- L24 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MASSENTITYDEBUGGER_API`

### `Source/Editor/MassEntityDebugger/Private/SMassArchetype.h` (Private)


#### class `SMassArchetype`  
`class SMassArchetype : public SCompoundWidget`  
_L11-26_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SMassArchetype)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FMassDebuggerArchetypeData> InArchetypeData, TSharedPtr<FMassDebuggerArchetypeData> InBaseArchetypeData, const EMassBitSetDiffPrune Prune, TSharedRef<FMassDebuggerModel> InDebuggerModel);`
- L21 _protected member_ `TSharedPtr<FMassDebuggerArchetypeData> ArchetypeData;`
- L22 _protected member_ `TSharedPtr<FMassDebuggerModel> DebuggerModel;`
- L23 _protected member_ `bool bBitSetsVisible = true;`
- L24 _protected member_ `bool bEntitiesVisible = true;`
- L25 _protected prototype_ `FReply ShowEntities();`

### `Source/Editor/MassEntityDebugger/Private/SMassArchetypesView.h` (Private)


#### class `SMassArchetypesView`  
`class SMassArchetypesView : public SMassDebuggerViewBase`  
_L15-39_
- inherits: `SMassDebuggerViewBase`
- L18 _public function_ `SLATE_BEGIN_ARGS(SMassArchetypesView)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FMassDebuggerModel> InDebuggerModel);`
- L25 _public prototype_ `void HandleSelectionChanged(TSharedPtr<FMassDebuggerArchetypeData> InNode, ESelectInfo::Type InSelectInfo);`
- L28 _protected prototype_ `virtual void OnRefresh() override;`
- L29 _protected prototype_ `virtual void OnProcessorsSelected(TConstArrayView<TSharedPtr<FMassDebuggerProcessorData>> SelectedProcessors, ESelectInfo::Type SelectInfo) override;`
- L30 _protected prototype_ `virtual void OnArchetypesSelected(TConstArrayView<TSharedPtr<FMassDebuggerArchetypeData>> SelectedArchetypes, ESelectInfo::Type SelectInfo) override;`
- L32 _protected prototype_ `void RebuildSelectedView();`
- L34 _protected member_ `TSharedPtr<STreeView<TSharedPtr<FMassDebuggerArchetypeData>>> ArchetypesTreeView;`
- L35 _protected member_ `TSharedPtr<SScrollBox> SelectedArchetypesView;`
- L36 _protected member_ `TSharedPtr<SHeaderRow> ArchetypesHeaderRow;`
- L37 _protected member_ `TSharedPtr<FMassDebuggerArchetypeData> DiffBase;`
- L38 _protected member_ `TArray<TSharedPtr<FMassDebuggerArchetypeData>> TreeViewSource;`

### `Source/Editor/MassEntityDebugger/Private/SMassBitSet.h` (Private)


#### enum `EMassBitSetDisplayMode`  
`enum class EMassBitSetDisplayMode`  
_L21-26_
- L23 _public enumerator_ `ReadOnly`
- L24 _public enumerator_ `ReadWrite`
- L25 _public enumerator_ `MAX`

#### class `SMassBitSet`  
`template<typename TBitSet> class SMassBitSet : public SCompoundWidget`  
_L29-112_
- inherits: `SCompoundWidget`
- L32 _public function_ `SLATE_BEGIN_ARGS(SMassBitSet) : _SlotPadding(5.f) , _TextColor(FLinearColor(1.f, 1.f, 1.f)) , _BackgroundBrush(FMassDebuggerStyle::GetBrush("MassDebug.Fragment"))`
- L37 _public function_ `SLATE_ATTRIBUTE(FMargin, SlotPadding) SLATE_ATTRIBUTE(FLinearColor, TextColor) SLATE_ATTRIBUTE(const FSlateBrush*, BackgroundBrush) SLATE_END_ARGS() void Construct(const SMassBitSet::FArguments& InArgs, TSharedRef<FMassDebuggerModel> DebuggerModel, const FString& Label, const TBitSet& BitSet)`
- L47 _public function_ `void Construct(const SMassBitSet::FArguments& InArgs, TSharedRef<FMassDebuggerModel> DebuggerModel, const FString& Label, TConstArrayView<TBitSet> BitSets, TConstArrayView<const FSlateBrush*> InBrushes = TConstArrayView<const FSlateBrush*>())`
- L81 _protected function_ `void AddBitSet(const SMassBitSet::FArguments& InArgs, TSharedRef<SWrapBox>& ButtonBox, const TBitSet& BitSet, const FSlateBrush* Brush , TSharedRef<FMassDebuggerModel> DebuggerModel)`

#### enum `EMassBitSetDiffPrune`  
`enum class EMassBitSetDiffPrune : uint8`  
_L115-119_
- L117 _public enumerator_ `None` — No pruning
- L118 _public enumerator_ `Same` — Prune tags that exists in base

#### class `SMassBitSetDiff`  
`template<typename TBitSet> class SMassBitSetDiff : public SCompoundWidget`  
_L122-279_
- inherits: `SCompoundWidget`
- L125 _public function_ `SLATE_BEGIN_ARGS(SMassBitSetDiff) : _SlotPadding(5.f) , _TextColor(FLinearColor(1.f, 1.f, 1.f)) , _BackgroundBrush(FMassDebuggerStyle::GetBrush("MassDebug.Fragment"))`
- L130 _public function_ `SLATE_ATTRIBUTE(FMargin, SlotPadding) SLATE_ATTRIBUTE(FLinearColor, TextColor) SLATE_ATTRIBUTE(const FSlateBrush*, BackgroundBrush) SLATE_END_ARGS() void Construct(const SMassBitSetDiff::FArguments& InArgs, const FString& Label, const TBitSet& BaseBitSet, const TBitSet& BitSet , const EMassBitSetDiffPrune Prune, TSharedRef<FMassDebuggerModel> DebuggerModel)`
- L173 _protected function_ `void AddBitSet(const SMassBitSetDiff::FArguments& InArgs, TSharedRef<SWrapBox>& ButtonBox, const TBitSet& BaseBitSet, const TBitSet& BitSet , const FSlateBrush* Brush, const EMassBitSetDiffPrune Prune, TSharedRef<FMassDebuggerModel> DebuggerModel)`

#### Free symbols / members of external scopes

- L17 _macro_ `#define LOCTEXT_NAMESPACE "SMassDebugger"`
- L99 _function_ `` (scope `SMassBitSet::AddBitSet`)
- L155 _function_ `` (scope `SMassBitSetDiff::SLATE_ATTRIBUTE`)
- L239 _function_ `.Visibility_Lambda([Icon] { return Icon != nullptr ? EVisibility::Visible : EVisibility::Collapsed; }) .DesiredSizeOverride(FVector2D(10.0f, 10.0f)) ] + SHorizontalBox::Slot() .AutoWidth() .VAlign(VAlign_Center) [ SNew(SButton) .OnClicked_Lambda([Name, DebuggerModel]() { DebuggerModel->SelectFragment(FName(*Name)); return FReply::Handled(); }) [ SNew(STextBlock) .Text(FText::FromString(Name)) ] ] ] ];` (scope `SMassBitSetDiff::AddBitSet`)
- L248 _function_ `` (scope `SMassBitSetDiff::AddBitSet`)
- L281 _namespace_ `namespace UE`
- L281 _namespace_ `namespace Mass` (scope `UE`)
- L281 _namespace_ `namespace Debugger` (scope `UE::Mass`)
- L281 _namespace_ `namespace UI` (scope `UE::Mass::Debugger`)
- L284 _function_ `template<typename TBitSet> void AddBitSet(TSharedRef<SVerticalBox>& Box, const TBitSet& BitSetAccess, const FString& Label, const FSlateBrush* Brush, TSharedRef<FMassDebuggerModel> DebuggerModel)` (scope `UE::Mass::Debugger::UI`)
- L300 _function_ `template<typename TBitSet> void AddBitSetDiff(TSharedRef<SVerticalBox>& Box, const TBitSet& BaseBitSet, const TBitSet& BitSet, const FString& Label, const FSlateBrush* Brush , const EMassBitSetDiffPrune Prune, TSharedRef<FMassDebuggerModel> DebuggerModel)` (scope `UE::Mass::Debugger::UI`)

### `Source/Editor/MassEntityDebugger/Private/SMassBreakpointsView.h` (Private)


#### class `SMassBreakpointsView`  
`class SMassBreakpointsView : public SMassDebuggerViewBase`  
_L18-81_
- inherits: `SMassDebuggerViewBase`
- L21 _public function_ `SLATE_BEGIN_ARGS(SMassBreakpointsView)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FMassDebuggerModel> InModel);`
- L30 _protected function_ `virtual void OnRefresh() override` — SMassDebuggerViewBase overrides
- L35 _protected function_ `virtual void OnProcessorsSelected(TConstArrayView<TSharedPtr<FMassDebuggerProcessorData>> SelectedProcessors, ESelectInfo::Type SelectInfo)`
- L39 _protected function_ `virtual void OnArchetypesSelected(TConstArrayView<TSharedPtr<FMassDebuggerArchetypeData>> SelectedArchetypes, ESelectInfo::Type SelectInfo)`
- L65 _private prototype_ `void RefreshBreakpoints();`
- L66 _private prototype_ `FReply ClearBreakpointsClicked();`
- L67 _private prototype_ `FReply SaveBreakpointsClicked();`
- L68 _private prototype_ `FReply PasteBreakpointClicked();`
- L69 _private prototype_ `FReply NewBreakpointClicked();`
- L71 _private prototype_ `TSharedRef<ITableRow> OnGenerateBreakpointRow( TSharedPtr<FMassDebuggerBreakpointData> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L75 _private member_ `TSharedPtr<SListView<TSharedPtr<FMassDebuggerBreakpointData>>> BreakpointsListView;`
- L77 _private member_ `TArray<TSharedPtr<FString>> TriggerTypeOptions;`
- L78 _private member_ `TMap<UE::Mass::Debug::FBreakpoint::ETriggerType, TSharedPtr<FString>> TriggerMap;`
- L79 _private member_ `TArray<TSharedPtr<FString>> FilterTypeOptions;`
- L80 _private member_ `TMap<UE::Mass::Debug::FBreakpoint::EFilterType, TSharedPtr<FString>> FilterMap;`

#### class `SMassBreakpointsView::SBreakpointTableRow`  
`class SBreakpointTableRow : public SMultiColumnTableRow<TSharedPtr<FMassDebuggerBreakpointData>>`  
_L45-63_
- inherits: `SMultiColumnTableRow<TSharedPtr<FMassDebuggerBreakpointData>>`
- L48 _public function_ `SLATE_BEGIN_ARGS(SBreakpointTableRow)`
- L51 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedRef<SMassBreakpointsView> InParentView, TSharedRef<FMassDebuggerBreakpointData> InBreakpointData, TSharedRef<FMassDebuggerModel> InModel);`
- L54 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L55 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L58 _private member_ `TSharedPtr<STextBlock> HitCount;`
- L60 _private member_ `TWeakPtr<FMassDebuggerBreakpointData> BreakpointData;`
- L61 _private member_ `TWeakPtr<FMassDebuggerModel> DebuggerModel;`
- L62 _private member_ `TWeakPtr<SMassBreakpointsView> ParentView;`

### `Source/Editor/MassEntityDebugger/Private/SMassDebugger.h` (Private)


#### class `FMassDebuggerCommands`  
`class FMassDebuggerCommands : public TCommands<FMassDebuggerCommands>`  
_L15-27_
- inherits: `TCommands<FMassDebuggerCommands>`
- L19 _public prototype_ `FMassDebuggerCommands();` — Default constructor.
- L23 _public prototype_ `virtual void RegisterCommands() override;` — TCommands interface
- L26 _public member_ `TSharedPtr<FUICommandInfo> RefreshData;`

#### class `SMassDebuggerTab`  
`class SMassDebuggerTab : public SDockTab`  
_L29-33_
- inherits: `SDockTab`
- L32 _public function_ `virtual bool SupportsKeyboardFocus() const override`

#### class `SMassDebugger`  
`class SMassDebugger : public SCompoundWidget`  
_L35-113_
- inherits: `SCompoundWidget`
- L39 _public function_ `SLATE_BEGIN_ARGS(SMassDebugger)`
- L45 _public prototype_ `SMassDebugger();`
- L46 _public prototype_ `virtual ~SMassDebugger();`
- L55 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow);` — Constructs the application. @param InArgs The Slate argument list. @param ConstructUnderMajorTab The major tab which will contain the debugger @param ConstructUnderWindow The window in which this widget is being constructed.
- L57 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L59 _public prototype_ `void ShowProcessorView() const;`
- L60 _public prototype_ `void ShowArchetypesView() const;`
- L61 _public prototype_ `void ShowBreakpointsView() const;`
- L62 _public prototype_ `void ShowProcessingGraphsView() const;`
- L63 _public prototype_ `void ShowFragmentsView() const;`
- L64 _public prototype_ `void ShowEntitesView() const;`
- L65 _public prototype_ `void ResetLayout();`
- L66 _public prototype_ `void ShowSelectedView() const;`
- L67 _public prototype_ `void ShowQueryEditorView() const;`
- L69 _public prototype_ `static bool IsAutoSwitchEnvironmentsEnabled();`
- L72 _protected prototype_ `TSharedRef<SDockTab> SpawnToolbar(const FSpawnTabArgs& Args);`
- L73 _protected prototype_ `TSharedRef<SDockTab> SpawnProcessorsTab(const FSpawnTabArgs& Args);`
- L74 _protected prototype_ `TSharedRef<SDockTab> SpawnProcessingTab(const FSpawnTabArgs& Args);`
- L75 _protected prototype_ `TSharedRef<SDockTab> SpawnFragmentsTab(const FSpawnTabArgs& Args);`
- L76 _protected prototype_ `TSharedRef<SDockTab> SpawnArchetypesTab(const FSpawnTabArgs& Args);`
- L77 _protected prototype_ `TSharedRef<SDockTab> SpawnBreakpointsTab(const FSpawnTabArgs& Args);`
- L78 _protected prototype_ `TSharedRef<SDockTab> SpawnEntitiesTab(const FSpawnTabArgs& Args);`
- L79 _protected prototype_ `TSharedRef<SDockTab> SpawnQueryEditorTab(const FSpawnTabArgs& Args);`
- L81 _protected prototype_ `TSharedRef<FTabManager::FLayout> CreateDefaultLayout();`
- L82 _protected prototype_ `TSharedRef<SWidget> GenerateWindowMenu();`
- L84 _protected prototype_ `void BindDelegates();`
- L85 _protected prototype_ `void OnEntityManagerInitialized(const FMassEntityManager& EntityManager);`
- L86 _protected prototype_ `void OnEntityManagerDeinitialized(const FMassEntityManager& EntityManager);`
- L87 _protected prototype_ `void HandleEnvironmentChanged(TSharedPtr<FMassDebuggerEnvironment> Item, ESelectInfo::Type SelectInfo);`
- L88 _protected prototype_ `void RebuildEnvironmentsList();`
- L90 _protected prototype_ `bool CanRefreshData();`
- L91 _protected prototype_ `void RefreshData();`
- L94 _protected prototype_ `void OnProcessorProviderRegistered(const FMassDebugger::FEnvironment& Environment);`
- L98 _protected member_ `TSharedRef<FUICommandList> CommandList;` — Holds the list of UI commands.
- L101 _protected member_ `TSharedPtr<FTabManager> TabManager;` — Holds the tab manager that manages the front-end's tabs.
- L103 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<FMassDebuggerEnvironment>>> EnvironmentComboBox;`
- L104 _protected member_ `TSharedPtr<STextBlock> EnvironmentComboLabel;`
- L106 _protected member_ `TArray<TSharedPtr<FMassDebuggerEnvironment>> EnvironmentsList;`
- L108 _protected member_ `TSharedRef<FMassDebuggerModel> DebuggerModel;`
- L110 _protected member_ `FDelegateHandle OnEntityManagerInitializedHandle;`
- L111 _protected member_ `FDelegateHandle OnEntityManagerDeinitializedHandle;`
- L112 _protected member_ `FDelegateHandle OnProcessorProviderRegisteredHandle;`

### `Source/Editor/MassEntityDebugger/Private/SMassDebuggerViewBase.h` (Private)


#### class `SMassDebuggerViewBase`  
`class SMassDebuggerViewBase : public SCompoundWidget`  
_L11-31_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SMassDebuggerViewBase)`
- L17 _public prototype_ `virtual ~SMassDebuggerViewBase();`
- L20 _protected prototype_ `void Initialize(TSharedRef<FMassDebuggerModel> InDebuggerModel);`
- L22 _protected prototype_ `virtual void OnRefresh() = 0;`
- L23 _protected prototype_ `virtual void OnProcessorsSelected(TConstArrayView<TSharedPtr<FMassDebuggerProcessorData>> SelectedProcessors, ESelectInfo::Type SelectInfo) = 0;`
- L24 _protected prototype_ `virtual void OnArchetypesSelected(TConstArrayView<TSharedPtr<FMassDebuggerArchetypeData>> SelectedArchetypes, ESelectInfo::Type SelectInfo) = 0;`
- L26 _protected member_ `FDelegateHandle OnRefreshHandle;`
- L27 _protected member_ `FDelegateHandle OnProcessorsSelectedHandle;`
- L28 _protected member_ `FDelegateHandle OnArchetypesSelectedHandle;`
- L30 _protected member_ `TSharedPtr<FMassDebuggerModel> DebuggerModel;`

### `Source/Editor/MassEntityDebugger/Private/SMassEntitiesList.h` (Private)


#### class `SMassEntitiesList`  
`class SMassEntitiesList : public SCompoundWidget`  
_L20-129_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SMassEntitiesList)`
- L25 _public prototype_ `SLATE_ARGUMENT(TArray<FMassEntityHandle>, Entities) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FMassDebuggerModel> InDebuggerModel);`
- L29 _public prototype_ `void SetEntities(const TArray<FMassEntityHandle>& InEntities);`
- L30 _public prototype_ `void RefreshEntityData();`
- L32 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L65 _public typedef_ `using EntitiesTableRowPtr = TSharedPtr<FGridRow>;`
- L85 _public function_ `TSharedPtr<SBox> GetFragmentSelectBox()`
- L90 _public function_ `void AutoUpdateEntityData(bool bEnable)`
- L96 _private member_ `TArray<EntitiesTableRowPtr> GridRows;`
- L97 _private member_ `TArray<FMassEntitiesListColumn> Columns;`
- L98 _private member_ `TMap<FName, int32> ColumnIndexByID;`
- L100 _private prototype_ `void BuildGrid();`
- L101 _private prototype_ `void PopulateGridColumns();`
- L102 _private prototype_ `void RefreshFragmentData();`
- L104 _private prototype_ `void AddPropertyRecursive(TSharedPtr<SHorizontalBox> HBox, TSharedPtr<SVerticalBox> VBox, TSharedPtr<IPropertyHandle> Prop, bool bShowName = false);`
- L105 _private member_ `TArray<FName> AvailableFragmentNames;`
- L106 _private member_ `TArray<FName> SelectedFragmentNames;`
- L107 _private member_ `TArray<const UScriptStruct*> SelectedFragmentTypes;`
- L108 _private prototype_ `FReply OnClearAllSelectedFragmentsClicked();`
- L110 _private member_ `TSharedPtr<SBox> FragmentSelectBox;`
- L112 _private member_ `bool bAutoUpdateEntityData = false;`
- L114 _private prototype_ `void OnFragmentCheckStateChanged(ECheckBoxState NewState, FName FragmentName);`
- L115 _private prototype_ `ECheckBoxState GetFragmentCheckState(FName FragmentName) const;`
- L116 _private prototype_ `void CreateFragmentSelectDropdown();`
- L117 _private member_ `TSharedPtr<FMassDebuggerModel> DebuggerModel;`
- L118 _private prototype_ `void UpdateTreeColumns();`
- L119 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(FName ColumnId) const;`
- L120 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L121 _private member_ `bool bSortAscending = true;`
- L123 _private prototype_ `void TreeView_OnGetChildren(SMassEntitiesList::EntitiesTableRowPtr InParent, TArray<SMassEntitiesList::EntitiesTableRowPtr>& OutChildren);`
- L124 _private prototype_ `TSharedRef<ITableRow> TreeView_OnGenerateRow(EntitiesTableRowPtr RowPtr, const TSharedRef<STableViewBase>& OwnerTable);`
- L126 _private member_ `TSharedPtr<STreeView<EntitiesTableRowPtr>> TreeView;`
- L127 _private member_ `TSharedPtr<SHeaderRow> TreeViewHeaderRow;`
- L128 _private member_ `TArray<TSharedRef<IDetailTreeNode>> NodesToSearch;`

#### struct `SMassEntitiesList::FMassEntitiesListColumn`  
`struct FMassEntitiesListColumn`  
_L36-42_
- L38 _public member_ `const UScriptStruct* StructType = nullptr;`
- L39 _public member_ `const FProperty* Property = nullptr;`
- L40 _public member_ `FString ColumnLabel;`
- L41 _public member_ `FName ColumnID;`

#### struct `SMassEntitiesList::FGridRow`  
`struct FGridRow`  
_L44-59_
- L55 _public member_ `TArray<FFragmentInfo> FragmentInfo;`
- L56 _public member_ `FMassEntityHandle Entity;`
- L57 _public member_ `TWeakPtr<SMassEntitiesList> EntitiesList;`
- L58 _public member_ `bool bDirty = true;`

#### struct `SMassEntitiesList::FGridRow::FFragmentInfo`  
`struct FFragmentInfo`  
_L46-53_
- L48 _public member_ `const UScriptStruct* StructType = nullptr;`
- L49 _public member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;`
- L52 _public member_ `TSharedPtr<FStructOnScope> StructData;` — this is a snapshot copy of the actual mass fragment data

#### class `SMassEntitiesList::SEntitiesTableRow`  
`class SEntitiesTableRow : public SMultiColumnTableRow<EntitiesTableRowPtr>`  
_L67-83_
- inherits: `SMultiColumnTableRow<EntitiesTableRowPtr>`
- L69 _private typedef_ `using Super = SMultiColumnTableRow<EntitiesTableRowPtr>;`
- L71 _public function_ `SLATE_BEGIN_ARGS(SEntitiesTableRow)`
- L72 _public prototype_ `SLATE_ARGUMENT(EntitiesTableRowPtr, EntitiesTableRow) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L77 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L80 _private member_ `EntitiesTableRowPtr TableRowPtr;`
- L81 _private prototype_ `TSharedRef<SWidget> GenerateBreakpointWidget(FGridRow::FFragmentInfo& Info);`
- L82 _private prototype_ `TSharedRef<SWidget> GenerateDataWidget(const FProperty* Property, FGridRow::FFragmentInfo& Info);`

### `Source/Editor/MassEntityDebugger/Private/SMassEntitiesView.h` (Private)


#### class `SMassEntitiesView`  
`class SMassEntitiesView : public SMassDebuggerViewBase`  
_L13-69_
- inherits: `SMassDebuggerViewBase`
- L16 _public function_ `SLATE_BEGIN_ARGS(SMassEntitiesView)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FMassDebuggerModel> InDebuggerModel, uint32 InEntitiesViewIndex);`
- L23 _public prototype_ `void ShowEntities(FMassArchetypeHandle InArchetypeHandle);`
- L24 _public prototype_ `void ShowEntities(const TArray<FMassEntityHandle>& InEntities);`
- L25 _public prototype_ `void ShowEntities(FMassEntityQuery& InQuery);`
- L26 _public prototype_ `void ShowEntities(TConstArrayView<FMassEntityQuery*> InQueries);`
- L27 _public prototype_ `void ClearEntities();`
- L38 _protected prototype_ `FReply ShowAllEntities();`
- L39 _protected prototype_ `FReply RefreshEntityList();`
- L40 _protected prototype_ `FReply RefreshEntityData();`
- L42 _protected prototype_ `void OnAutoUpdateChanged(ECheckBoxState NewState);`
- L43 _protected prototype_ `float GetUpdateInterval() const;`
- L44 _protected prototype_ `void OnUpdateIntervalChanged(float NewValue);`
- L46 _protected prototype_ `virtual void OnRefresh() override;`
- L49 _protected function_ `virtual void OnProcessorsSelected(TConstArrayView<TSharedPtr<FMassDebuggerProcessorData>> SelectedProcessors, ESelectInfo::Type SelectInfo) override` — Unused pure virtual function
- L55 _protected function_ `virtual void OnArchetypesSelected(TConstArrayView<TSharedPtr<FMassDebuggerArchetypeData>> SelectedArchetypes, ESelectInfo::Type SelectInfo) override` — Unused pure virtual function
- L60 _protected member_ `EShowEntitiesFrom ShowEntitiesFrom;`
- L61 _protected member_ `TSharedPtr<SMassEntitiesList> EntitiesList;`
- L62 _protected member_ `FMassArchetypeHandle ArchetypeHandle;`
- L63 _protected member_ `TSharedPtr<STextBlock> ListLabel;`
- L64 _protected member_ `TArray<FMassEntityHandle> TempEntityList;`
- L65 _protected member_ `uint32 EntitiesViewIndex;`
- L66 _protected member_ `FMassEntityQuery Query;`
- L67 _protected member_ `TConstArrayView<FMassEntityQuery*> Queries;`
- L68 _protected member_ `TSharedPtr<SCheckBox> AutoUpdateCheckbox;`

#### enum `SMassEntitiesView::EShowEntitiesFrom`  
`enum class EShowEntitiesFrom`  
_L30-37_
- L32 _public enumerator_ `List`
- L33 _public enumerator_ `Archetype`
- L34 _public enumerator_ `Query`
- L35 _public enumerator_ `QueryList`
- L36 _public enumerator_ `All`

### `Source/Editor/MassEntityDebugger/Private/SMassFragmentsView.h` (Private)


#### class `UE::MassDebugger::FragmentsView::SFragmentsTableRow`  
`class SFragmentsTableRow : public SMultiColumnTableRow<FFragmentsTableRowPtr>`  
_L24-37_
- inherits: `SMultiColumnTableRow<FFragmentsTableRowPtr>`
- L26 _private typedef_ `using Super = SMultiColumnTableRow<FFragmentsTableRowPtr>;`
- L29 _public function_ `SLATE_BEGIN_ARGS(SFragmentsTableRow)`
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, FFragmentsTableRowPtr InFragmentDataPtr);`
- L33 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L36 _private member_ `FFragmentsTableRowPtr FragmentDataPtr;`

#### class `UE::MassDebugger::FragmentsView::SFragmentsView`  
`class SFragmentsView : public SMassDebuggerViewBase`  
_L40-66_
- inherits: `SMassDebuggerViewBase`
- L43 _public function_ `SLATE_BEGIN_ARGS(SFragmentsView)`
- L45 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FMassDebuggerModel> InDebuggerModel);`
- L48 _public prototype_ `virtual void OnRefresh() override;`
- L49 _public function_ `virtual void OnProcessorsSelected(TConstArrayView<TSharedPtr<FMassDebuggerProcessorData>> SelectedProcessors, ESelectInfo::Type SelectInfo) override`
- L51 _public function_ `virtual void OnArchetypesSelected(TConstArrayView<TSharedPtr<FMassDebuggerArchetypeData>> SelectedArchetypes, ESelectInfo::Type SelectInfo) override`
- L55 _protected prototype_ `TSharedRef<ITableRow> OnGenerateFragmentRow(FFragmentsTableRowPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L56 _protected prototype_ `void RefreshFragmentList();`
- L58 _protected prototype_ `EColumnSortMode::Type GetColumnSortMode(FName ColumnId) const;`
- L59 _protected prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L62 _private member_ `TSharedPtr<SListView<FFragmentsTableRowPtr>> FragmentsList;`
- L63 _private member_ `TArray<FFragmentsTableRowPtr> FragmentListItemsSource;`
- L64 _private member_ `FName SortByColumnId;`
- L65 _private member_ `bool bSortAscending = true;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MassDebugger` (scope `UE`)
- L19 _namespace_ `namespace FragmentsView` (scope `UE::MassDebugger`)
- L22 _typedef_ `using FFragmentsTableRowPtr = TSharedPtr<FMassDebuggerFragmentData>;` (scope `UE::MassDebugger::FragmentsView`)

### `Source/Editor/MassEntityDebugger/Private/SMassProcessingGraphView.h` (Private)


#### struct `FMassDebuggerProcessingGraphNodeTreeItem`  
`struct FMassDebuggerProcessingGraphNodeTreeItem`  
_L12-18_
- L14 _public prototype_ `FMassDebuggerProcessingGraphNodeTreeItem(const FMassDebuggerProcessingGraphNode& InNode);`
- L16 _public member_ `FMassDebuggerProcessingGraphNode Node;`
- L17 _public member_ `TArray<TSharedPtr<FMassDebuggerProcessingGraphNodeTreeItem>> ChildItems;`

#### class `SMassProcessingGraphView`  
`class SMassProcessingGraphView : public SMassDebuggerViewBase`  
_L20-51_
- inherits: `SMassDebuggerViewBase`
- L23 _public function_ `SLATE_BEGIN_ARGS(SMassProcessingGraphView) : _OffsetPerLevel(10.f)`
- L26 _public prototype_ `SLATE_ATTRIBUTE(float, OffsetPerLevel) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FMassDebuggerModel> InDebuggerModel);`
- L31 _public prototype_ `void Display(TSharedPtr<FMassDebuggerProcessingGraph> InProcessingGraphData);`
- L34 _protected prototype_ `void HandleSelectionChanged(TSharedPtr<FMassDebuggerProcessingGraphNodeTreeItem> InNode, ESelectInfo::Type InSelectInfo);`
- L36 _protected prototype_ `virtual void OnRefresh() override;`
- L37 _protected prototype_ `virtual void OnProcessorsSelected(TConstArrayView<TSharedPtr<FMassDebuggerProcessorData>> SelectedProcessors, ESelectInfo::Type) override;`
- L38 _protected prototype_ `virtual void OnArchetypesSelected(TConstArrayView<TSharedPtr<FMassDebuggerArchetypeData>> SelectedArchetypes, ESelectInfo::Type) override;`
- L40 _protected prototype_ `void ClearSelection();`
- L41 _protected prototype_ `void MarkDependencies(const FMassDebuggerProcessingGraphNode& Node);`
- L43 _protected member_ `TSharedPtr<FMassDebuggerProcessingGraph> ProcessingGraphData;`
- L44 _protected member_ `TSharedPtr<SVerticalBox> ItemsBox;`
- L45 _protected member_ `float OffsetPerLevel;`
- L47 _protected member_ `TArray<TSharedPtr<FMassDebuggerProcessingGraphNodeTreeItem>> AllNodes;`
- L48 _protected member_ `TArray<TSharedPtr<FMassDebuggerProcessingGraphNodeTreeItem>> RootNodes;`
- L50 _protected member_ `TSharedPtr<STreeView<TSharedPtr<FMassDebuggerProcessingGraphNodeTreeItem>>> GraphNodesTree;`

### `Source/Editor/MassEntityDebugger/Private/SMassProcessingView.h` (Private)


#### class `SMassProcessingView`  
`class SMassProcessingView : public SCompoundWidget`  
_L12-34_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SMassProcessingView)`
- L19 _public prototype_ `~SMassProcessingView();`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<FMassDebuggerModel> InDebuggerModel);`
- L24 _protected prototype_ `void OnRefresh();`
- L26 _protected member_ `TSharedPtr<FMassDebuggerModel> DebuggerModel;`
- L28 _protected member_ `TSharedPtr<SListView<TSharedPtr<FMassDebuggerProcessingGraph>>> GraphsListWidget;`
- L30 _protected member_ `TSharedPtr<SMassProcessingGraphView> ProcessingGraphWidget;`
- L31 _protected member_ `FString SelectedLabel;`
- L33 _protected member_ `FDelegateHandle OnRefreshHandle;`

### `Source/Editor/MassEntityDebugger/Private/SMassProcessor.h` (Private)


#### class `SMassProcessor`  
`class SMassProcessor : public SCompoundWidget`  
_L9-20_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SMassProcessor)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FMassDebuggerProcessorData> InProcessorData, TSharedRef<FMassDebuggerModel> InDebuggerModel);`
- L19 _protected member_ `TSharedPtr<FMassDebuggerProcessorData> ProcessorData;`

### `Source/Editor/MassEntityDebugger/Private/SMassProcessorsView.h` (Private)


#### class `SMassProcessorsView`  
`class SMassProcessorsView : public SMassDebuggerViewBase`  
_L17-49_
- inherits: `SMassDebuggerViewBase`
- L20 _public function_ `SLATE_BEGIN_ARGS(SMassProcessorsView)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FMassDebuggerModel>& InDebuggerModel);`
- L27 _public prototype_ `void PopulateProcessorList();`
- L30 _protected prototype_ `virtual void OnRefresh() override;`
- L31 _protected prototype_ `virtual void OnProcessorsSelected(TConstArrayView<TSharedPtr<FMassDebuggerProcessorData>> SelectedProcessors, ESelectInfo::Type SelectInfo) override;`
- L32 _protected prototype_ `virtual void OnArchetypesSelected(TConstArrayView<TSharedPtr<FMassDebuggerArchetypeData>> SelectedArchetypes, ESelectInfo::Type SelectInfo) override;`
- L34 _protected prototype_ `void ProcessorListSelectionChanged(TSharedPtr<FMassDebuggerProcessorData> SelectedItem, ESelectInfo::Type SelectInfo);`
- L38 _protected prototype_ `void OnClearSelection(const SMassProcessorCollectionListView& TransientSource);`
- L40 _protected member_ `TSharedPtr<SListView<TSharedPtr<FMassDebuggerModel::FProcessorCollection>>> ProcessorCollectionsListWidget;`
- L41 _protected member_ `TArray<TSharedPtr<SMassProcessorCollectionListView>> ProcessorsListWidgets;`
- L42 _protected member_ `TSharedPtr<SMassProcessor> ProcessorWidget;`
- L43 _protected member_ `TSharedPtr<SVerticalBox> ProcessorsBox;`
- L45 _protected prototype_ `DECLARE_DELEGATE_TwoParams(FOnProcessorSelectionChanged, TSharedPtr<FMassDebuggerProcessorData>, ESelectInfo::Type);`
- L46 _protected member_ `FOnProcessorSelectionChanged OnProcessorSelectionChanged;`
- L48 _protected member_ `bool bClearingSelection = false;`

#### Free symbols / members of external scopes

- L45 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnProcessorSelectionChanged, TSharedPtr<FMassDebuggerProcessorData>, ESelectInfo::Type);`

### `Source/Editor/MassEntityDebugger/Private/SMassProcessorsWidget.h` (Private)


#### class `SMassProcessorWidget`  
`class SMassProcessorWidget : public SCompoundWidget`  
_L13-38_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SMassProcessorWidget)`
- L18 _public prototype_ `virtual ~SMassProcessorWidget();`
- L20 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FMassDebuggerProcessorData> InDebuggerProcessorData, TSharedRef<FMassDebuggerModel> InDebuggerModel);`
- L23 _private prototype_ `FReply HandleExpandTextClicked();`
- L24 _private prototype_ `FReply HandleExpandGraphClicked();`
- L25 _private prototype_ `FReply HandleSelectProcessorClicked();`
- L26 _private prototype_ `FReply HandleOpenSourceLocationClicked();`
- L27 _private prototype_ `FReply HandleShowEntitiesClicked();`
- L28 _private prototype_ `void HandleFragmentSelected(FName SelectedFragment);`
- L29 _private member_ `bool bIsExpandedText;`
- L30 _private member_ `bool bIsExpandedGraph;`
- L31 _private member_ `TSharedPtr<SBox> TextBoxContainer;`
- L32 _private member_ `TSharedPtr<SBox> GraphBoxContainer;`
- L33 _private member_ `TSharedPtr<SBorder> Border;`
- L34 _private member_ `TSharedPtr<FMassDebuggerProcessorData> ProcessorData;`
- L35 _private member_ `TSharedPtr<FMassDebuggerModel> DebuggerModel;`
- L36 _private prototype_ `const FSlateBrush* GetBorderByFragmentSelection();`
- L37 _private member_ `FDelegateHandle OnFragmentSelectChangeHandle;`

### `Source/Editor/MassEntityDebugger/Private/SMassQuery.h` (Private)


#### class `SMassQuery`  
`class SMassQuery : public SCompoundWidget`  
_L9-21_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SMassQuery)`
- L14 _public prototype_ `SLATE_ATTRIBUTE(FString, EditName) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FMassDebuggerQueryData> InQueryData, TSharedRef<FMassDebuggerModel> InDebuggerModel);`
- L20 _protected member_ `TSharedPtr<FMassDebuggerQueryData> QueryData;`

### `Source/Editor/MassEntityDebugger/Private/SMassQueryEditor.h` (Private)


#### class `UE::MassDebugger::SQueryEditor`  
`class SQueryEditor : public SCompoundWidget`  
_L21-97_
- inherits: `SCompoundWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS(SQueryEditor) : _DebuggerModel() , _InitialRequirements()`
- L29 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FMassDebuggerModel>, DebuggerModel) SLATE_ARGUMENT(FMassFragmentRequirements, InitialRequirements) SLATE_EVENT(FRequirementsChanged, OnRequirementsChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L35 _public prototype_ `void SetQuery(TSharedPtr<FEditableQuery>& InQuery);`
- L38 _private prototype_ `void ApplyChanges();`
- L39 _private prototype_ `void Load();`
- L40 _private prototype_ `void HandleNameTextCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L42 _private prototype_ `TSharedRef<ITableRow> OnGenerateFragmentRow(TSharedPtr<FFragmentEntry> InEntry, const TSharedRef<STableViewBase>& OwnerTable);`
- L44 _private prototype_ `TSharedRef<ITableRow> OnGenerateTagRow(TSharedPtr<FFragmentEntry> InEntry, const TSharedRef<STableViewBase>& OwnerTable);`
- L46 _private prototype_ `FReply OnAddFragment();`
- L47 _private prototype_ `FReply OnRemoveFragment(TSharedPtr<FFragmentEntry> InEntry);`
- L49 _private prototype_ `FReply OnAddTag();`
- L50 _private prototype_ `FReply OnRemoveTag(TSharedPtr<FFragmentEntry> InEntry);`
- L52 _private prototype_ `void NotifyRequirementsChanged();`
- L54 _private member_ `TWeakPtr<FMassDebuggerModel> DebuggerModel;`
- L56 _private member_ `FRequirementsChanged OnRequirementsChanged;`
- L57 _private member_ `TSharedPtr<FEditableQuery> Query;`
- L59 _private member_ `TArray<TSharedPtr<FFragmentEntry>> FragmentEntries;`
- L60 _private member_ `TArray<TSharedPtr<FFragmentEntry>> TagEntries;`
- L62 _private member_ `TArray<TSharedPtr<FString>> AvailableFragmentNames;`
- L63 _private member_ `TMap<FString, TWeakObjectPtr<const UScriptStruct>> FragmentNamesToTypes;`
- L64 _private member_ `TArray<TSharedPtr<FString>> AvailableTagNames;`
- L65 _private member_ `TMap<FString, TWeakObjectPtr<const UScriptStruct>> TagNamesToTypes;`
- L90 _private member_ `TArray<TSharedPtr<FName>> FragmentAccessNames;`
- L91 _private member_ `TArray<TSharedPtr<FName>> FragmentPresenceNames;`
- L92 _private member_ `TMap<FName, EMassFragmentAccess> FragmentAccessMap;`
- L93 _private member_ `TMap<FName, EMassFragmentPresence> FragmentPresenceMap;`
- L95 _private member_ `TSharedPtr<SListView<TSharedPtr<FFragmentEntry>>> FragmentListView;`
- L96 _private member_ `TSharedPtr<SListView<TSharedPtr<FFragmentEntry>>> TagListView;`

#### class `UE::MassDebugger::SQueryEditor::SFragmentSelectorRow`  
`class SFragmentSelectorRow : public STableRow<TSharedPtr<FFragmentEntry>>`  
_L68-88_
- inherits: `STableRow<TSharedPtr<FFragmentEntry>>`
- L72 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, const TSharedPtr<FFragmentEntry>& InEntry, TSharedRef<SQueryEditor> InOwnerRequirementsEditor, bool bInShowTags);`
- L74 _public member_ `TSharedPtr<SSearchableComboBox> FragmentsComboBox;`
- L76 _public prototype_ `void OnFragmentTypeChanged(TSharedPtr<TWeakObjectPtr<const UScriptStruct>> NewType, ESelectInfo::Type, TSharedPtr<FFragmentEntry> Entry);`
- L77 _public prototype_ `void OnFragmentAccessChanged(EMassFragmentAccess NewAccess, ESelectInfo::Type, TSharedPtr<FFragmentEntry> Entry);`
- L78 _public prototype_ `void OnFragmentPresenceChanged(EMassFragmentPresence NewPresence, ESelectInfo::Type, TSharedPtr<FFragmentEntry> Entry);`
- L79 _public prototype_ `void OnTagTypeChanged(TSharedPtr<TWeakObjectPtr<const UScriptStruct>> NewType, ESelectInfo::Type, TSharedPtr<FFragmentEntry> Entry);`
- L80 _public prototype_ `void OnTagPresenceChanged(EMassFragmentPresence NewPresence, ESelectInfo::Type, TSharedPtr<FFragmentEntry> Entry);`
- L82 _public prototype_ `FText GetFragmentTypeText(TSharedPtr<FFragmentEntry> Entry) const;`
- L83 _public prototype_ `FText GetTagTypeText(TSharedPtr<FFragmentEntry> Entry) const;`
- L84 _public prototype_ `FText GetTagPresenceText(TSharedPtr<FFragmentEntry> Entry) const;`
- L86 _public member_ `TWeakPtr<SQueryEditor> OwnerRequirementsEditor;`
- L87 _public member_ `bool bShowTags;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MassDebugger` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FRequirementsChanged, TSharedPtr<FEditableQuery>&);`
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FRequirementsChanged, TSharedPtr<FEditableQuery>&);` (scope `UE::MassDebugger`)

### `Source/Editor/MassEntityDebugger/Private/SMassQueryEditorView.h` (Private)


#### class `UE::MassDebugger::SQueryEditorView`  
`class SQueryEditorView : public SMassDebuggerViewBase`  
_L14-51_
- inherits: `SMassDebuggerViewBase`
- L17 _public function_ `SLATE_BEGIN_ARGS(SQueryEditorView)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FMassDebuggerModel> InDebuggerModel);`
- L23 _public prototype_ `virtual void OnRefresh() override;`
- L24 _public function_ `virtual void OnProcessorsSelected(TConstArrayView<TSharedPtr<FMassDebuggerProcessorData>> SelectedProcessors, ESelectInfo::Type SelectInfo) override`
- L26 _public function_ `virtual void OnArchetypesSelected(TConstArrayView<TSharedPtr<FMassDebuggerArchetypeData>> SelectedArchetypes, ESelectInfo::Type SelectInfo) override`
- L29 _public prototype_ `void ShowQuery(const FMassEntityQuery& InQuery, const FString& InQueryName);`
- L31 _public prototype_ `FReply OnSaveQuery();`
- L32 _public prototype_ `FReply OnSaveAllQueries();`
- L33 _public prototype_ `FReply OnCopyQuery();`
- L34 _public prototype_ `FReply OnPasteQuery();`
- L38 _protected member_ `TSharedPtr<SListView<TSharedPtr<FEditableQuery>>> QueryListView;`
- L39 _protected member_ `TSharedPtr<SQueryEditor> QueryEditor;`
- L40 _protected member_ `TSharedPtr<FEditableQuery> SelectedQuery;`
- L42 _protected member_ `TWeakPtr<FMassDebuggerModel> DebuggerModel;`
- L44 _protected prototype_ `TSharedRef<ITableRow> OnGenerateQueryRow(TSharedPtr<FEditableQuery> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L45 _protected prototype_ `FReply OnAddQuery();`
- L46 _protected prototype_ `FReply OnDeleteQuery(TSharedPtr<FEditableQuery> InItem);`
- L47 _protected prototype_ `FReply OnEditQuery(TSharedPtr<FEditableQuery> InItem);`
- L48 _protected prototype_ `FReply OnViewEntities(TSharedPtr<FEditableQuery> InItem);`
- L49 _protected prototype_ `void OnRequirementsChanged(TSharedPtr<FEditableQuery>& Query);`
- L50 _protected prototype_ `void OnQueriesChanged();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MassDebugger` (scope `UE`)

### `Source/Editor/MassEntityDebugger/Public/IMassDebuggerModule.h` (Public)


#### class `IMassDebuggerModule`  
`class IMassDebuggerModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline IMassDebuggerModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Source/Editor/MassEntityDebugger/Public/MassDebuggerSettings.h` (Public)


#### class `UMassDebuggerSettings`  
`class UMassDebuggerSettings : public UMassModuleSettings`  
_L14-21_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings, DisplayName = "Mass Debugger")`
- inherits: `UMassModuleSettings`
- L20 _public member_ `bool bStripMassPrefix = true;` — `UPROPERTY(EditAnywhere, config, Category=Debugger)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define GET_MASSDEBUGGER_CONFIG_VALUE(a) \`
