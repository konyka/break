# Editor / EditorToolEvents

- module root: `Source/Editor/EditorToolEvents`
- headers: 3; symbols: 29
- symbol kinds: class=2, delegate=2, function=1, member=10, prototype=12, struct=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Json, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Source/Editor/EditorToolEvents/Public/EditorToolDelegates.h` (Public)


#### struct `FEditorToolDelegates`  
`struct FEditorToolDelegates`  
_L13-24_
- L18 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FEditorToolStarted, const FString & );` — Broadcasted for editor tools OnLoad or OnInitialize, if available to notify when tool used
- L19 _public member_ `static FEditorToolStarted OnEditorToolStarted;`
- L22 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSendEditorFocusSummary, TSharedPtr<FJsonObject> );` — Broadcasted when the editor is closed and sends a summary of widget focus data
- L23 _public member_ `static FSendEditorFocusSummary OnSendEditorFocusSummary;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FEditorToolStarted, const FString & );` — Broadcasted for editor tools OnLoad or OnInitialize, if available to notify when tool used
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSendEditorFocusSummary, TSharedPtr<FJsonObject> );` — Broadcasted when the editor is closed and sends a summary of widget focus data

### `Source/Editor/EditorToolEvents/Public/EditorToolEventsModule.h` (Public)


#### class `FEditorToolEventsModule`  
`class FEditorToolEventsModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Source/Editor/EditorToolEvents/Public/EditorUsageAnalyticsSummary.h` (Public)


#### struct `FFocusedWindowAnalyticData`  
`struct FFocusedWindowAnalyticData`  
_L11-16_
- L14 _public member_ `TMap<FString, double> FocusedTabs;` — Name, time in seconds focused
- L15 _public member_ `uint32 WindowId;`

#### class `FEditorUsageAnalyticsSummary`  
`class FEditorUsageAnalyticsSummary : FNoncopyable`  
_L23-62_
- inherits: `FNoncopyable`
- desc: Collects editor events we wish to send as a summary that are not critical enough to be in our summary store.
- L26 _public prototype_ `static FEditorUsageAnalyticsSummary& Get();`
- L28 _public prototype_ `FEditorUsageAnalyticsSummary();`
- L30 _public prototype_ `void Start();`
- L32 _public prototype_ `void Shutdown();`
- L35 _public prototype_ `TSharedPtr<FJsonObject> GetSummaryDataAsJsonObject(bool bReset = false);` — Get's the current usage summary. If bReset is true, clears out current summary. (useful when collecting summaries per project instead of session)
- L38 _public function_ `bool IsActive()` — Returns true if start has been called. Makes it so we can still check the summary even if the CVAR to turn it off is true or otherwise disabled.
- L40 _public prototype_ `virtual ~FEditorUsageAnalyticsSummary() = default;`
- L44 _private prototype_ `void OnSlateUserInteraction(double DeltaTime);`
- L45 _private prototype_ `void UpdateUserFocusTimes(double CurrTimeSecs);`
- L47 _private member_ `TMap<FString, FFocusedWindowAnalyticData> FocusedWindows;`
- L50 _private member_ `std::atomic<double> TimeOfLastUpdate;` — Time since we last updated our focus stats
- L53 _private member_ `mutable FTransactionallySafeCriticalSection StoreLock;` — Slate interaction and shutting down can come from different threads so we need a log for FocusedWindow data
- L56 _private member_ `FTimespan UpdatePeriod;` — Period we want to wait between focus time updates (some events might lead us to update sooner)
- L59 _private member_ `double NextUpdateTimeSeconds = 0.0;` — The next time the session properties should be persisted to disk.
- L61 _private member_ `bool bActive = false;`
