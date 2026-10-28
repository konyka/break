# Editor / MassEntityEditor

- module root: `Source/Editor/MassEntityEditor`
- headers: 8; symbols: 164
- symbol kinds: class=8, delegate=2, enum=1, enumerator=4, function=14, macro=4, member=56, namespace=18, prototype=52, struct=4, variable=1
- DynamicallyLoadedModuleNames: MassEntityDebugger
- PrivateDependencyModuleNames: AIGraph, AssetTools, ComponentVisualizers, DetailCustomizations, EditorSubsystem, GraphEditor, InputCore, KismetWidgets, MassCore, MassDeveloper, MessageLog, Projects, PropertyEditor, RenderCore, RewindDebuggerInterface, RewindDebuggerRuntimeInterface, Slate, ToolMenus, TraceLog, TraceServices
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MassEntity, SlateCore, UnrealEd

### `Source/Editor/MassEntityEditor/Private/Trace/MassEntityEventCache.h` (Private)


#### class `UE::Mass::Trace::FEntityEventCache`  
`class FEntityEventCache`  
_L22-77_
- desc: Caches entity events indexed by entity and archetype for efficient sub-track querying. The IMassTraceProvider only offers sequential enumeration, so this cache builds per-entity and per-archetype indices to avoid O(N) scans in every sub-track update.
- L33 _public prototype_ `void Update(const IMassTraceProvider& Provider, const TraceServices::IAnalysisSession& Session);` — Rebuild indices from the provider if GetUpdateCounter() has changed.
- L37 _public prototype_ `TConstArrayView<FCachedEntityEventRecord> GetEntityEvents(uint64 EntityId) const;` — Get all events for a specific entity. Returns empty array if entity not found.
- L40 _public prototype_ `const TSet<uint64>* GetEntitiesForArchetype(uint64 ArchetypeId) const;` — Get all entity IDs that have events referencing a specific archetype.
- L43 _public function_ `const TSet<uint64>& GetActiveArchetypeIds() const` — Get all archetype IDs that appear in the event data.
- L50 _public function_ `bool HasData() const` — Whether any data has been cached.
- L61 _private prototype_ `void ConvertTimesToRecordingTime(const TraceServices::IAnalysisSession& Session);` — Resolve frame indices from ProfileTime and ensure Event.Time is in ElapsedTime (recording time) space. New traces already carry correct ElapsedTime from emission; old traces lacking the RecordingTime field have Time == ProfileTime and are normalized relative to the first frame's start time as a backward-compatibility fallback.
- L64 _private member_ `TMap<uint64, TArray<FCachedEntityEventRecord>> EntityEvents;` — Entity ID -> array of events, sorted by ascending ProfileTime after Update()
- L67 _private member_ `TMap<uint64, TSet<uint64>> ArchetypeEntities;` — Archetype ID -> set of entity IDs that reference it
- L70 _private member_ `TSet<uint64> ActiveArchetypeIds;` — All archetype IDs that appear in the event data
- L73 _private member_ `uint64 LastUpdateCounter = 0;` — Last seen update counter from the provider
- L76 _private member_ `mutable FRWLock CacheLock;` — Protects all cache state from concurrent read/write access

#### struct `UE::Mass::Trace::FEntityEventCache::FCachedEntityEventRecord`  
`struct FCachedEntityEventRecord : FEntityEventRecord`  
_L26-30_
- inherits: `FEntityEventRecord`
- desc: Extended event record with frame index resolved at cache build time.
- L29 _public member_ `uint32 FrameIndex = 0;` — Game frame index this event belongs to. Events in the same frame share the same index.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mass` (scope `UE`)
- L14 _namespace_ `namespace Trace` (scope `UE::Mass`)

### `Source/Editor/MassEntityEditor/Private/Trace/MassEntityTrack.h` (Private)


#### class `UE::Mass::Trace::FEntityTrack`  
`class FEntityTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L19-57_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- desc: Per-entity leaf track showing lifecycle events (created, archetype change, destroyed) on a timeline with color-coded points and lifetime windows.
- L22 _public prototype_ `FEntityTrack(uint64 InEntityId, TSharedRef<FEntityEventCache> InCache);`
- L24 _public function_ `uint64 GetEntityId() const`
- L31 _private prototype_ `virtual bool UpdateInternal() override;`
- L32 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L33 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L34 _private prototype_ `virtual FSlateIcon GetIconInternal() override;`
- L35 _private prototype_ `virtual FName GetNameInternal() const override;`
- L36 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L37 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L41 _private prototype_ `virtual bool HasDebugDataInternal() const override;`
- L42 _private prototype_ `virtual FText GetStepCommandTooltipInternal(RewindDebugger::EStepMode StepMode) const override;`
- L43 _private prototype_ `virtual TOptional<double> GetStepFrameTimeInternal(RewindDebugger::EStepMode StepMode, const FScrubTimeInformation& CurrentScrubTime) const override;`
- L45 _private prototype_ `TSharedPtr<SEventTimelineView::FTimelineEventData> GetEventData() const;`
- L47 _private member_ `uint64 EntityId = 0;`
- L48 _private member_ `TSharedRef<FEntityEventCache> Cache;`
- L50 _private member_ `mutable TSharedPtr<SEventTimelineView::FTimelineEventData> EventData;`
- L51 _private member_ `mutable int32 TicksSinceEventRebuild = 0;`
- L53 _private member_ `TSharedPtr<SMassEntityDetailsView> DetailsView;`
- L55 _private member_ `FText DisplayName;`
- L56 _private member_ `FSlateIcon Icon;`

#### class `UE::Mass::Trace::FEntityTrackCreator`  
`class FEntityTrackCreator : public RewindDebugger::IRewindDebuggerTrackCreator`  
_L63-73_
- inherits: `RewindDebugger::IRewindDebuggerTrackCreator`
- desc: Track creator for individual Mass entity tracks. Creates FEntityTrack under FMassEntityHandle object tracks.
- L66 _private prototype_ `virtual FName GetTargetTypeNameInternal() const override;`
- L67 _private prototype_ `virtual FName GetNameInternal() const override;`
- L68 _private prototype_ `virtual void GetTrackTypesInternal(TArray<RewindDebugger::FRewindDebuggerTrackType>& Types) const override;`
- L69 _private prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L70 _private prototype_ `virtual bool HasDebugInfoInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L72 _private member_ `mutable TSharedRef<FEntityEventCache> Cache = MakeShared<FEntityEventCache>();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mass` (scope `UE`)
- L12 _namespace_ `namespace Trace` (scope `UE::Mass`)

### `Source/Editor/MassEntityEditor/Private/Trace/MassRewindDebuggerIntegration.h` (Private)


#### class `FMassRewindDebuggerRuntimeExtension`  
`class FMassRewindDebuggerRuntimeExtension final : public IRewindDebuggerRuntimeExtension`  
_L11-16_
- inherits: `IRewindDebuggerRuntimeExtension`
- desc: Runtime extension that enables/disables the Mass trace channel when RewindDebugger recording starts/stops.
- L14 _protected prototype_ `virtual void RecordingStarted() override;`
- L15 _protected prototype_ `virtual void RecordingStopped() override;`

### `Source/Editor/MassEntityEditor/Private/Trace/SMassEntityDetailsView.h` (Private)


#### class `SMassEntityDetailsView`  
`class SMassEntityDetailsView : public SCompoundWidget`  
_L24-92_
- inherits: `SCompoundWidget`
- desc: Details widget for a single Mass entity. Shows a diff-style table of fragments between previous and current archetype.
- L46 _public function_ `SLATE_BEGIN_ARGS(SMassEntityDetailsView)`
- L47 _public prototype_ `SLATE_ARGUMENT(uint64, EntityId) SLATE_ARGUMENT(const UE::Mass::Trace::FEntityEventCache*, Cache) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L52 _public prototype_ `void SetScrubTime(double Time);`
- L55 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L67 _private prototype_ `void RebuildFragmentList();`
- L68 _private prototype_ `void SortFragmentEntries();`
- L69 _private prototype_ `FArchetypeResolution ResolveArchetypesAtScrubTime() const;`
- L71 _private prototype_ `EColumnSortMode::Type GetSortModeForColumn(FName ColumnId) const;`
- L72 _private prototype_ `void OnSortModeChanged(EColumnSortPriority::Type Priority, const FName& ColumnId, EColumnSortMode::Type InSortMode);`
- L74 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FFragmentEntry> Entry, const TSharedRef<STableViewBase>& OwnerTable);`
- L76 _private member_ `uint64 EntityId = 0;`
- L77 _private member_ `const UE::Mass::Trace::FEntityEventCache* Cache = nullptr;`
- L78 _private member_ `double CurrentScrubTime = 0.0;`
- L79 _private member_ `uint64 LastDisplayedArchetypeId = 0;`
- L80 _private member_ `uint64 LastDisplayedPreviousArchetypeId = 0;`
- L81 _private member_ `uint64 LastDisplayedArchetypeBeforeBatch = 0;`
- L82 _private member_ `int32 LastDisplayedMergeCount = 0;`
- L83 _private member_ `TArray<uint64> LastBatchArchetypeIds;`
- L85 _private member_ `TArray<TSharedPtr<FFragmentEntry>> FragmentEntries;`
- L86 _private member_ `TSharedPtr<SListView<TSharedPtr<FFragmentEntry>>> ListView;`
- L87 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L88 _private member_ `TSharedPtr<STextBlock> MergeInfoText;`
- L90 _private member_ `FName SortColumn;`
- L91 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Ascending;`

#### enum `SMassEntityDetailsView::EDiffStatus`  
`enum class EDiffStatus : uint8`  
_L27-33_
- L29 _public enumerator_ `Unchanged`
- L30 _public enumerator_ `Added`
- L31 _public enumerator_ `Removed`
- L32 _public enumerator_ `Readded`

#### struct `SMassEntityDetailsView::FFragmentEntry`  
`struct FFragmentEntry`  
_L35-44_
- L37 _public member_ `const UE::Mass::Trace::FFragmentInfo* Info = nullptr;`
- L38 _public member_ `EDiffStatus Status = EDiffStatus::Unchanged;`
- L40 _public member_ `int32 AddedAtStep = 0;` — Step at which the fragment was added (Added/Readded). 0 = not applicable.
- L42 _public member_ `int32 RemovedAtStep = 0;` — Step at which the fragment was removed (Removed/Readded). 0 = not applicable.
- L43 _public member_ `bool bHasPrevious = false;`

#### struct `SMassEntityDetailsView::FArchetypeResolution`  
`struct FArchetypeResolution`  
_L57-65_
- L59 _public member_ `uint64 CurrentArchetype = 0;`
- L60 _public member_ `uint64 PreviousArchetype = 0;`
- L62 _public member_ `uint64 ArchetypeBeforeBatch = 0;` — Archetype the entity was in before the first event in the current frame's batch.
- L63 _public member_ `int32 MergeCount = 0;`
- L64 _public member_ `TArray<uint64> BatchArchetypeIds;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mass` (scope `UE`)
- L14 _namespace_ `namespace Trace` (scope `UE::Mass`)

### `Source/Editor/MassEntityEditor/Public/MassEditorStyle.h` (Public)


#### class `FMassEntityEditorStyle`  
`class FMassEntityEditorStyle`  
_L9-28_
- L12 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static void Shutdown();`
- L14 _public function_ `static TSharedPtr<ISlateStyle> Get()`
- L15 _public prototype_ `static FName GetStyleSetName();`
- L17 _public function_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL)`
- L22 _public prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L27 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MASSENTITYEDITOR_API`

### `Source/Editor/MassEntityEditor/Public/MassEntityEditor.h` (Public)


#### struct `FMassEditorNotification`  
`struct FMassEditorNotification`  
_L12-26_
- reflection: `USTRUCT()`
- L16 _public member_ `EMessageSeverity::Type Severity = EMessageSeverity::Error;`
- L17 _public member_ `FText Message;`
- L23 _public member_ `bool bIncludeSeeOutputLogForDetails = false;` — If set to true then a clickable "see log for details" message will be added to the message log. Clicking the message takes the user to the Output Log.
- L25 _public prototype_ `void Show();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSENTITYEDITOR_API`
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Mass` (scope `UE`)
- L28 _namespace_ `namespace Editor` (scope `UE::Mass`)
- L30 _variable_ `const FName MessageLogPageName(TEXT("Mass` (scope `UE::Mass::Editor`)

### `Source/Editor/MassEntityEditor/Public/MassEntityEditorModule.h` (Public)


#### class `FMassEntityEditorModule`  
`class FMassEntityEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L26-61_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- desc: The public interface to this module
- L29 _public prototype_ `virtual void StartupModule() override;`
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L32 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override`
- L37 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override`
- L42 _public function_ `TSharedPtr<FGraphNodeClassHelper> GetProcessorClassCache()`
- L49 _protected prototype_ `static void OnWorldCleanup(UWorld* , bool , bool );`
- L50 _protected member_ `FDelegateHandle OnWorldCleanupHandle;`
- L53 _protected member_ `TSharedPtr<FGraphNodeClassHelper> ProcessorClassCache;`
- L55 _protected member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L56 _protected member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L59 _protected member_ `TUniquePtr<UE::Mass::Trace::FEntityTrackCreator> EntityTrackCreator;`
- L60 _protected member_ `TUniquePtr<FMassRewindDebuggerRuntimeExtension> RuntimeExtension;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSENTITYEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Mass` (scope `UE`)
- L18 _namespace_ `namespace Trace` (scope `UE::Mass`)

### `Source/Editor/MassEntityEditor/Public/MassEntityEditorSubsystem.h` (Public)


#### class `UMassEntityEditorSubsystem`  
`class UMassEntityEditorSubsystem : public UEngineSubsystem`  
_L22-74_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem`
- desc: This is an Engine Subsystem that is selectively enabled using WITH_EDITOR so it is available in custom programs that run the editor with -game
- L27 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreTick, float );`
- L28 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostTick, float );`
- L30 _public prototype_ `UMassEntityEditorSubsystem();`
- L31 _public prototype_ `~UMassEntityEditorSubsystem();`
- L33 _public prototype_ `static UMassEntityEditorSubsystem* Get();`
- L35 _public function_ `TSharedRef<FMassEntityManager> GetMutableEntityManager()`
- L36 _public function_ `TSharedRef<FMassProcessingPhaseManager> GetMutablePhaseManager()`
- L38 _public function_ `FOnPreTick& GetOnPreTickDelegate()`
- L39 _public function_ `FOnPostTick& GetOnPostTickDelegate()`
- L42 _public prototype_ `void RegisterDynamicProcessor(UMassProcessor& Processor);` — Registers a dynamic processor. This needs to be a fully formed processor and will be slotted in during the next tick.
- L44 _public prototype_ `void UnregisterDynamicProcessor(UMassProcessor& Processor);` — Removes a previously registered dynamic processor of throws an assert if not found.
- L48 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem interface begin
- L49 _protected prototype_ `virtual void Deinitialize() override;`
- L50 _protected prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L53 _protected prototype_ `void InitializeMassInternals();`
- L54 _protected prototype_ `void StopAndCleanUp();`
- L57 _protected prototype_ `void Tick(float DeltaTime);`
- L59 _protected member_ `UE::Mass::FMassEditorTickFunction* EditorTickFunction = nullptr;`
- L61 _protected member_ `TSharedRef<FMassEntityManager> EntityManager;`
- L63 _protected member_ `TSharedRef<FMassProcessingPhaseManager> PhaseManager;`
- L65 _protected member_ `FMassProcessingPhaseConfig ProcessingPhasesConfig[(uint8)EMassProcessingPhase::MAX];`
- L68 _protected member_ `FOnPreTick OnPreTickDelegate;` — Gets broadcast right before issuing FMassProcessingPhaseManager's phases execution
- L70 _protected member_ `FOnPostTick OnPostTickDelegate;` — Gets broadcast right after completing FMassProcessingPhaseManager's phases execution
- L72 _protected member_ `bool IsProcessing{ false };`
- L73 _protected member_ `FDelegateHandle OnSettingsInitializedHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSENTITYEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mass` (scope `UE`)
- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreTick, float );`
- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostTick, float );`
