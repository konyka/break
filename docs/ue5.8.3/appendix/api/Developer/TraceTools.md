# Developer / TraceTools

- module root: `Source/Developer/TraceTools`
- headers: 18; symbols: 520
- symbol kinds: class=19, delegate=12, enum=2, enumerator=4, function=40, macro=1, member=128, namespace=37, prototype=267, struct=9, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, InputCore, SessionServices, SharedSettingsWidgets, Slate, SlateCore, Sockets, TraceLog

### `Source/Developer/TraceTools/Private/Models/ITraceFilterPreset.h` (Private)


#### struct `UE::TraceTools::ITraceFilterPreset`  
`struct ITraceFilterPreset : public TSharedFromThis<ITraceFilterPreset>`  
_L13-43_
- inherits: `TSharedFromThis<ITraceFilterPreset>`
- desc: Interface for structures representing a filtering preset
- L16 _public prototype_ `virtual ~ITraceFilterPreset() = default;`
- L18 _public prototype_ `virtual FString GetName() const = 0;`
- L19 _public prototype_ `virtual FText GetDisplayText() const = 0;`
- L20 _public prototype_ `virtual FText GetDescription() const = 0;`
- L23 _public prototype_ `virtual void GetAllowlistedNames(TArray<FString>& OutNames) const = 0;` — Returns all names which pass this preset its filter
- L25 _public prototype_ `virtual bool CanDelete() const = 0;` — Whether or not this preset can be deleted
- L27 _public prototype_ `virtual bool IsLocal() const = 0;` — Whether or not this preset only exists locally
- L29 _public prototype_ `virtual bool IsEnginePreset() const = 0;` — Whether or not this preset is a runtime preset
- L32 _public prototype_ `virtual void Save(const TArray<TSharedPtr<ITraceObject>>& InObjects) = 0;` — Update this preset according to the provided set of trace objects
- L34 _public prototype_ `virtual void Save() = 0;`
- L36 _public prototype_ `virtual void Rename(const FString& InNewName) = 0;`
- L37 _public prototype_ `virtual bool Delete() = 0;`
- L40 _public prototype_ `virtual bool MakeShared() = 0;` — Transition preset between being local and shared, moves between local and default INI files
- L41 _public prototype_ `virtual bool MakeLocal() = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace TraceTools` (scope `UE`)

### `Source/Developer/TraceTools/Private/Models/ITraceObject.h` (Private)


#### class `UE::TraceTools::ITraceObject`  
`class ITraceObject : public TSharedFromThis<ITraceObject>`  
_L10-44_
- inherits: `TSharedFromThis<ITraceObject>`
- L13 _public prototype_ `virtual ~ITraceObject() = default;`
- L16 _public prototype_ `virtual FString GetName() const = 0;` — Returns the name representing this object
- L19 _public prototype_ `virtual FString GetDescription() const = 0;` — Returns the description representing this object
- L22 _public prototype_ `virtual FText GetDisplayText() const = 0;` — Returns the user-facing name for this object
- L25 _public prototype_ `virtual FText GetTooltipText() const = 0;` — Returns the tooltip text for this object
- L28 _public prototype_ `virtual void SetIsFiltered(bool bState) = 0;` — Set whether or not this object should (not) be filtered out
- L31 _public prototype_ `virtual bool IsReadOnly() const = 0;` — Returns whether or not this object can be changed by the user.
- L34 _public prototype_ `virtual void SetPending() = 0;` — Set whether or not this object is pending an update of its state (from the connect edTrace connection)
- L37 _public prototype_ `virtual bool IsFiltered() const = 0;` — Returns whether or not this object is set to be filtered out (true = filtered; false = not filtered)
- L40 _public prototype_ `virtual bool IsPending() const = 0;` — Returns whether or not this object is pending a filter-state update (SetPending previously called)
- L43 _public prototype_ `virtual void GetSearchString(TArray<FString>& OutFilterStrings) const = 0;` — Returns string representing this object in a search (treeview filtering)

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace TraceTools` (scope `UE`)

### `Source/Developer/TraceTools/Private/Models/TraceChannel.h` (Private)


#### class `UE::TraceTools::FTraceChannel`  
`class FTraceChannel : public ITraceObject`  
_L12-46_
- inherits: `ITraceObject`
- L15 _public prototype_ `FTraceChannel(FString InName, FString InDescription, FString InParentName, uint32 InId, bool bInEnabled, bool bInReadOnly, TSharedPtr<ISessionTraceFilterService> InFilterService);`
- L18 _public prototype_ `virtual FText GetDisplayText() const override;` — Begin ITraceObject overrides
- L19 _public prototype_ `virtual FText GetTooltipText() const override;`
- L20 _public prototype_ `virtual FString GetName() const override;`
- L21 _public prototype_ `virtual FString GetDescription() const override;`
- L22 _public prototype_ `virtual void SetPending() override;`
- L23 _public prototype_ `virtual bool IsReadOnly() const override;`
- L24 _public prototype_ `virtual void SetIsFiltered(bool bState) override;`
- L25 _public prototype_ `virtual bool IsFiltered() const override;`
- L26 _public prototype_ `virtual bool IsPending() const override;`
- L27 _public prototype_ `virtual void GetSearchString(TArray<FString>& OutFilterStrings) const override;`
- L32 _protected member_ `FString Name;` — This channel's name
- L34 _protected member_ `FString Description;` — This channel's description
- L36 _protected member_ `FString ParentName;` — Channel's parent (group) name
- L38 _protected member_ `uint32 Id;` — Channel's id
- L41 _protected member_ `bool bFiltered;` — Whether or not this channel is filtered out, true = filtered; false = not filtered
- L42 _protected member_ `bool bIsPending;`
- L43 _protected member_ `bool bReadOnly;`
- L45 _protected member_ `TSharedPtr<ISessionTraceFilterService> FilterService;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace TraceTools` (scope `UE`)

### `Source/Developer/TraceTools/Private/Models/TraceControlCommands.h` (Private)


#### class `UE::TraceTools::FTraceControlCommands`  
`class FTraceControlCommands : public TCommands<FTraceControlCommands>`  
_L15-55_
- inherits: `TCommands<FTraceControlCommands>`
- L21 _public function_ `FTraceControlCommands() : TCommands<FTraceControlCommands>( "TraceControl", NSLOCTEXT("Contexts", "TraceControl", "Trace Control"), NAME_None, FTraceToolsStyle::GetStyleSetName() )` — Default constructor.
- L31 _public function_ `virtual void RegisterCommands() override` — TCommands interface
- L47 _public member_ `TSharedPtr<FUICommandInfo> SetTraceTargetServer;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> SetTraceTargetFile;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> StartTrace;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> StopTrace;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> TraceSnapshot;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> TraceBookmark;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> TraceScreenshot;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> ToggleStatNamedEvents;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "SessionConsoleCommands"`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace TraceTools` (scope `UE`)

### `Source/Developer/TraceTools/Private/Models/TraceFilterPresets.h` (Private)


#### struct `UE::TraceTools::FFilterPresetHelpers`  
`struct FFilterPresetHelpers`  
_L11-19_
- L14 _public prototype_ `static void CreateNewPreset(const TArray<TSharedPtr<ITraceObject>>& InObjects);` — Creates a new filtering preset according to the specific object names
- L16 _public prototype_ `static void ExtractEnabledObjectNames(const TArray<TSharedPtr<ITraceObject>>& InObjects, TArray<FString>& OutNames);` — Creates a set of strings, corresponding to set of non-filtered out object as part of InObjects
- L18 _public prototype_ `static bool CanModifySharedPreset();` — Returns whether or not shared presets can be modified, requires write-flag on default confing files

#### struct `FTraceFilterData`  
`struct FTraceFilterData`  
_L24-38_
- reflection: `USTRUCT()`
- desc: Structure representing an individual preset in configuration (ini) files
- L29 _public member_ `FString Name;` — `UPROPERTY()`
- L32 _public member_ `TArray<FString> AllowlistedNames;` — `UPROPERTY()`
- L34 _public function_ `bool operator==(const FTraceFilterData& Other) const`

#### class `ULocalTraceFilterPresetContainer`  
`class ULocalTraceFilterPresetContainer : public UObject`  
_L42-56_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UObject`
- desc: UObject containers for the preset data
- L48 _public prototype_ `void GetUserPresets(TArray<TSharedPtr<UE::TraceTools::ITraceFilterPreset>>& OutPresets);`
- L50 _public prototype_ `static void AddFilterData(const FTraceFilterData& InFilterData);`
- L51 _public prototype_ `static bool RemoveFilterData(const FTraceFilterData& InFilterData);`
- L52 _public prototype_ `static void Save();`
- L55 _protected member_ `TArray<FTraceFilterData> UserPresets;` — `UPROPERTY(Config)`

#### class `USharedTraceFilterPresetContainer`  
`class USharedTraceFilterPresetContainer : public UObject`  
_L59-73_
- reflection: `UCLASS(Config = Engine, DefaultConfig)`
- inherits: `UObject`
- L65 _public prototype_ `void GetSharedUserPresets(TArray<TSharedPtr<UE::TraceTools::ITraceFilterPreset>>& OutPresets);`
- L67 _public prototype_ `static void AddFilterData(const FTraceFilterData& InFilterData);`
- L68 _public prototype_ `static bool RemoveFilterData(const FTraceFilterData& InFilterData);`
- L69 _public prototype_ `static void Save();`
- L72 _protected member_ `TArray<FTraceFilterData> SharedPresets;` — `UPROPERTY(Config)`

#### struct `UE::TraceTools::FFilterPresetBase`  
`struct FFilterPresetBase : public ITraceFilterPreset`  
_L79-87_
- inherits: `ITraceFilterPreset`
- desc: Base implementation of a filter preset
- L82 _protected function_ `FFilterPresetBase(const FString& InName) : Name(InName)`
- L83 _protected prototype_ `virtual FText GetDescription() const;`
- L86 _protected member_ `FString Name;`

#### struct `UE::TraceTools::FFilterPreset`  
`struct FFilterPreset : public FFilterPresetBase`  
_L89-110_
- inherits: `FFilterPresetBase`
- L92 _public function_ `FFilterPreset(const FString& InName, FTraceFilterData& InFilterData) : FFilterPresetBase(InName), FilterData(InFilterData)`
- L95 _public prototype_ `virtual FString GetName() const override;` — Begin ITraceFilterPreset overrides
- L96 _public prototype_ `virtual FText GetDisplayText() const;`
- L97 _public prototype_ `virtual void GetAllowlistedNames(TArray<FString>& OutNames) const override;`
- L98 _public prototype_ `virtual bool CanDelete() const override;`
- L99 _public prototype_ `virtual void Rename(const FString& InNewName) override;`
- L100 _public prototype_ `virtual bool Delete() override;`
- L101 _public prototype_ `virtual bool MakeShared() override;`
- L102 _public prototype_ `virtual bool MakeLocal() override;`
- L103 _public prototype_ `virtual bool IsLocal() const override;`
- L104 _public function_ `virtual bool IsEnginePreset() const override`
- L105 _public function_ `virtual void Save(const TArray<TSharedPtr<TraceTools::ITraceObject>>& InObjects) override`
- L106 _public function_ `virtual void Save() override`
- L109 _protected member_ `FTraceFilterData& FilterData;`

#### struct `UE::TraceTools::FEngineFilterPreset`  
`struct FEngineFilterPreset : public FFilterPresetBase`  
_L113-135_
- inherits: `FFilterPresetBase`
- desc: The Engine presets don't use USTRUCT so they can be shared with FTraceAuxiliary.
- L116 _public function_ `FEngineFilterPreset(const FString& InName, const TArray<FString>& InAllowListedNames) : FFilterPresetBase(InName), AllowListedNames(InAllowListedNames)`
- L119 _public function_ `virtual FString GetName() const override` — Begin ITraceFilterPreset overrides
- L120 _public function_ `virtual FText GetDisplayText() const`
- L121 _public prototype_ `virtual void GetAllowlistedNames(TArray<FString>& OutNames) const override;`
- L122 _public function_ `virtual bool CanDelete() const override`
- L123 _public function_ `virtual void Rename(const FString& InNewName) override`
- L124 _public function_ `virtual bool Delete() override`
- L125 _public function_ `virtual bool MakeShared() override`
- L126 _public function_ `virtual bool MakeLocal() override`
- L127 _public function_ `virtual bool IsLocal() const override`
- L128 _public function_ `virtual bool IsEnginePreset() const override`
- L129 _public function_ `virtual void Save(const TArray<TSharedPtr<TraceTools::ITraceObject>>& InObjects) override`
- L130 _public function_ `virtual void Save() override`
- L134 _protected member_ `TArray<FString> AllowListedNames;`

#### struct `UE::TraceTools::FUserFilterPreset`  
`struct FUserFilterPreset : public FFilterPreset`  
_L138-154_
- inherits: `FFilterPreset`
- desc: User filter preset, allows for deletion / transitioning INI ownership
- L141 _public function_ `FUserFilterPreset(const FString& InName, FTraceFilterData& InFilterData, bool bInLocal = false) : FFilterPreset(InName, InFilterData), bIsLocalPreset(bInLocal)`
- L144 _public prototype_ `virtual bool CanDelete() const override;` — Begin ITraceFilterPreset overrides
- L145 _public prototype_ `virtual bool Delete() override;`
- L146 _public prototype_ `virtual bool MakeShared() override;`
- L147 _public prototype_ `virtual bool MakeLocal() override;`
- L148 _public prototype_ `virtual bool IsLocal() const override;`
- L149 _public prototype_ `virtual void Save(const TArray<TSharedPtr<TraceTools::ITraceObject>>& InObjects) override;`
- L150 _public prototype_ `virtual void Save() override;`
- L153 _protected member_ `bool bIsLocalPreset;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace TraceTools` (scope `UE`)
- L75 _namespace_ `namespace UE`
- L75 _namespace_ `namespace TraceTools` (scope `UE`)

### `Source/Developer/TraceTools/Private/Services/ISessionTraceFilterService.h` (Private)


#### struct `UE::TraceTools::FTraceObjectInfo`  
`struct FTraceObjectInfo`  
_L17-29_
- L19 _public member_ `FString Name;`
- L20 _public member_ `FString Description;`
- L21 _public member_ `bool bEnabled;`
- L22 _public member_ `bool bReadOnly;`
- L23 _public member_ `uint32 Id;`
- L25 _public function_ `bool operator<(const FTraceObjectInfo& Other) const`

#### struct `UE::TraceTools::FTraceStats`  
`struct FTraceStats`  
_L31-38_
- L33 _public member_ `FTraceStatus::FStats StandardStats;`
- L36 _public member_ `uint64 BytesSentPerSecond = 0;` — Computed stats
- L37 _public member_ `uint64 BytesTracedPerSecond = 0;`

#### class `UE::TraceTools::ISessionTraceFilterService`  
`class ISessionTraceFilterService : public TSharedFromThis<ISessionTraceFilterService>`  
_L41-84_
- inherits: `TSharedFromThis<ISessionTraceFilterService>`
- desc: Filtering service, representing the state and data for a specific TraceServices::IAnalysisSession
- L44 _public prototype_ `virtual ~ISessionTraceFilterService() = default;`
- L47 _public prototype_ `virtual void GetRootObjects(TArray<FTraceObjectInfo>& OutObjects) const = 0;` — Returns the root level set of objects.
- L50 _public prototype_ `virtual const FTraceObjectInfo* GetObject(const FString& Name ) const = 0;` — Returns the object with the specified name.
- L53 _public prototype_ `virtual void SetObjectFilterState(const FString& InObjectName, const bool bFilterState) = 0;` — Set the filtered state for an individual object by its hash.
- L56 _public prototype_ `virtual const FDateTime& GetChannelsUpdateTimestamp() const = 0;` — Get the timestamp for the last channel data update.
- L59 _public prototype_ `virtual void UpdateFilterPreset(const TSharedPtr<ITraceFilterPreset> InPreset, bool IsEnabled) = 0;` — Update filter preset
- L62 _public prototype_ `virtual bool HasSettings() const = 0 ;` — Returns true if settings are available for the selected session.
- L65 _public prototype_ `virtual const FTraceStatus::FSettings& GetSettings() const = 0;` — Get the settings of the selected session.
- L68 _public prototype_ `virtual bool HasStats() const = 0;` — Returns true if stats are available for the selected session.
- L71 _public prototype_ `virtual const FTraceStats& GetStats() const = 0;` — Get the stats of the selected session.
- L74 _public prototype_ `virtual const FString& GetTraceEndpoint() const = 0;` — Get the endpoint of the current running trace.
- L77 _public prototype_ `virtual FTraceStatus::ETraceSystemStatus GetTraceSystemStatus() const = 0;` — Get the current status of the trace system.
- L80 _public prototype_ `virtual void SetInstanceId(const FGuid& Id) = 0;` — Sets the InstanceId to control. Supports invalid guid value for disabled state.
- L83 _public prototype_ `virtual bool HasAvailableInstance() const = 0;` — Returns true if the session with the currently set InstanceId is available for communication.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace TraceTools` (scope `UE`)

### `Source/Developer/TraceTools/Private/Services/SessionTraceControllerFilterService.h` (Private)


#### class `UE::TraceTools::FSessionTraceControllerFilterService`  
`class FSessionTraceControllerFilterService : public ISessionTraceFilterService`  
_L20-91_
- inherits: `ISessionTraceFilterService`
- desc: Implementation of ISessionTraceFilterService to query and set channels using the TraceController (MessageBus).
- L23 _public prototype_ `FSessionTraceControllerFilterService(TSharedPtr<ITraceController> InTraceController);`
- L24 _public prototype_ `virtual ~FSessionTraceControllerFilterService();`
- L27 _public prototype_ `virtual void GetRootObjects(TArray<FTraceObjectInfo>& OutObjects) const override;` — Begin ISessionTraceFilterService overrides
- L28 _public prototype_ `virtual const FTraceObjectInfo* GetObject(const FString& Name) const override;`
- L30 _public prototype_ `virtual const FDateTime& GetChannelsUpdateTimestamp() const override;`
- L31 _public prototype_ `virtual void SetObjectFilterState(const FString& InObjectName, const bool bFilterState) override;`
- L32 _public prototype_ `virtual void UpdateFilterPreset(const TSharedPtr<ITraceFilterPreset> InPreset, bool IsEnabled) override;`
- L34 _public prototype_ `virtual bool HasSettings() const override;`
- L35 _public prototype_ `virtual const FTraceStatus::FSettings& GetSettings() const override;`
- L37 _public prototype_ `virtual bool HasStats() const override;`
- L38 _public prototype_ `virtual const FTraceStats& GetStats() const override;`
- L40 _public function_ `virtual const FString& GetTraceEndpoint() const override`
- L41 _public function_ `virtual FTraceStatus::ETraceSystemStatus GetTraceSystemStatus() const`
- L43 _public prototype_ `void SetInstanceId(const FGuid& Id) override;`
- L44 _public prototype_ `bool HasAvailableInstance() const override;`
- L50 _protected prototype_ `void OnApplyChannelChanges();` — Callback at end of engine frame, used to dispatch all enabled/disabled channels
- L53 _protected prototype_ `void DisableAllChannels();` — Retrieves channels names from provider and marks them all as disabled
- L55 _protected prototype_ `void OnTraceStatusUpdated(const FTraceStatus& InStatus, FTraceStatus::EUpdateType InUpdateType, ITraceControllerCommands& Commands);`
- L57 _protected prototype_ `void UpdateChannels(const FTraceStatus& InStatus);`
- L59 _protected prototype_ `void Reset();`
- L62 _protected member_ `TSharedPtr<ITraceController> TraceController;`
- L65 _protected member_ `TMap<uint64, FTraceObjectInfo> Objects;` — A map with the key formed by hashing the object name and the object as the value.
- L68 _protected member_ `TSet<FString> FrameEnabledChannels;` — Names of channels that were either enabled or disabled during the duration of this frame
- L69 _protected member_ `TSet<FString> FrameDisabledChannels;`
- L72 _protected member_ `FDateTime StatusTimestamp;` — Timestamp at which the trace status was last updated
- L75 _protected member_ `FDateTime ChannelsTimestamp;` — Timestamp at which the trace channels were last updated
- L77 _protected member_ `bool bChannelsReceived = false;`
- L79 _protected member_ `FTraceStatus::FSettings Settings;`
- L80 _protected member_ `bool bHasSettings = false;`
- L82 _protected member_ `FTraceStats Stats;`
- L83 _protected member_ `bool bHasStats = false;`
- L85 _protected member_ `FString TraceEndpoint;`
- L86 _protected member_ `FTraceStatus::ETraceSystemStatus TraceSystemStatus;`
- L88 _protected member_ `FGuid InstanceId;`
- L90 _protected member_ `bool bHasPendingChannelChanges = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L11 _typedef_ `typedef uint64 FSessionHandle;` (scope `TraceServices`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace TraceTools` (scope `UE`)

### `Source/Developer/TraceTools/Private/TraceToolsModule.h` (Private)


#### class `FTraceToolsModule`  
`class FTraceToolsModule : public UE::TraceTools::ITraceToolsModule`  
_L13-26_
- inherits: `UE::TraceTools::ITraceToolsModule`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public prototype_ `virtual TSharedRef<SWidget> CreateTraceControlWidget(TSharedPtr<ITraceController> InTraceController) override;`
- L21 _public prototype_ `virtual TSharedRef<SWidget> CreateTraceControlWidget(TSharedPtr<ITraceController> InTraceController, FGuid InstanceId) override;`
- L23 _public prototype_ `virtual void SetTraceControlWidgetInstanceId(TSharedRef<SWidget> Widget, FGuid InstanceId) override;`
- L25 _public member_ `static FString TraceFiltersIni;`

### `Source/Developer/TraceTools/Private/TraceToolsStyle.h` (Private)


#### class `UE::TraceTools::FTraceToolsStyle`  
`class FTraceToolsStyle`  
_L13-31_
- L16 _public prototype_ `static void Initialize();`
- L17 _public prototype_ `static void Shutdown();`
- L19 _public prototype_ `static const ISlateStyle& Get();`
- L20 _public prototype_ `static const FName& GetStyleSetName();`
- L21 _public function_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL)`
- L29 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;` — Singleton instances of this style.
- L30 _private member_ `static FTextBlockStyle NormalText;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace TraceTools` (scope `UE`)

### `Source/Developer/TraceTools/Private/Widgets/SFilterPreset.h` (Private)


#### class `UE::TraceTools::SFilterPresetCheckBox`  
`class SFilterPresetCheckBox : public SCheckBox`  
_L17-81_
- inherits: `SCheckBox`
- desc: A class for check boxes in the preset list. If you double click the checkbox, you will enable it and disable all others
- L21 _public function_ `void SetOnFilterCtrlClicked(const FOnClicked& NewFilterCtrlClicked)`
- L26 _public function_ `void SetOnFilterAltClicked(const FOnClicked& NewFilteAltClicked)`
- L31 _public function_ `void SetOnFilterDoubleClicked(const FOnClicked& NewFilterDoubleClicked)`
- L36 _public function_ `void SetOnFilterMiddleButtonClicked(const FOnClicked& NewFilterMiddleButtonClicked)`
- L41 _public function_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override`
- L54 _public function_ `virtual FReply OnMouseButtonUp(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override`
- L77 _private member_ `FOnClicked OnFilterCtrlClicked;`
- L78 _private member_ `FOnClicked OnFilterAltClicked;`
- L79 _private member_ `FOnClicked OnFilterDoubleClicked;`
- L80 _private member_ `FOnClicked OnFilterMiddleButtonClicked;`

#### class `UE::TraceTools::SFilterPreset`  
`class SFilterPreset : public SCompoundWidget`  
_L86-232_
- inherits: `SCompoundWidget`
- desc: A single filtering preset in the preset list. Can be removed by clicking the remove button on it.
- L89 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnRequestRemove, const TSharedRef<SFilterPreset>& );`
- L90 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnRequestEnableOnly, const TSharedRef<SFilterPreset>& );`
- L91 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnRequestDelete, const TSharedRef<SFilterPreset>& );`
- L92 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnRequestSave, const TSharedRef<SFilterPreset>& );`
- L93 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnHighlightPreset, const TSharedPtr<ITraceFilterPreset>& );`
- L94 _public prototype_ `DECLARE_DELEGATE(FOnRequestEnableAll);`
- L95 _public prototype_ `DECLARE_DELEGATE(FOnRequestDisableAll);`
- L96 _public prototype_ `DECLARE_DELEGATE(FOnRequestRemoveAll);`
- L98 _public function_ `SLATE_BEGIN_ARGS(SFilterPreset)`
- L100 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<ITraceFilterPreset>, FilterPreset) SLATE_EVENT(FOnPresetChanged, OnPresetChanged) SLATE_EVENT(FOnRequestRemove, OnRequestRemove) SLATE_EVENT(FOnRequestEnableOnly, OnRequestEnableOnly) SLATE_EVENT(FOnRequestDelete, OnRequestDelete);` — Filter preset this widget represents
- L115 _public prototype_ `SLATE_EVENT(FOnRequestSave, OnRequestSave);` — Invoked when a request to save the current filtering state as this preset originated from within this widget
- L118 _public prototype_ `SLATE_EVENT(FOnHighlightPreset, OnHighlightPreset) SLATE_EVENT(FOnRequestEnableAll, OnRequestEnableAll) SLATE_EVENT(FOnRequestDisableAll, OnRequestDisableAll) SLATE_EVENT(FOnRequestRemoveAll, OnRequestRemoveAll) SLATE_END_ARGS() virtual ~SFilterPreset();` — Invoked when a request to highlight this preset originated from within this widget
- L133 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget with InArgs
- L136 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;` — Begin SCompoundWidget overrides
- L137 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L141 _public prototype_ `void MarkAsEnabled(bool InEnabled);` — Sets the enabled state but doesn't call the callback that changes the channel's state
- L144 _public prototype_ `void SetEnabled(bool InEnabled);` — Sets whether or not this preset is applied to the combined filtering state
- L147 _public prototype_ `bool IsEnabled() const;` — Returns true if this preset contributes to the combined filtering state
- L150 _public prototype_ `const TSharedPtr<ITraceFilterPreset>& GetFilterPreset() const;` — Get the preset object this widget represents
- L153 _private prototype_ `void PresetToggled(ECheckBoxState NewState);` — Handler for when the preset checkbox is clicked
- L156 _private prototype_ `FReply FilterCtrlClicked();` — Handler for when the preset checkbox is clicked and a control key is pressed
- L159 _private prototype_ `FReply FilterAltClicked();` — Handler for when the preset checkbox is clicked and an alt key is pressed
- L162 _private prototype_ `FReply FilterDoubleClicked();` — Handler for when the preset checkbox is double clicked
- L165 _private prototype_ `FReply FilterMiddleButtonClicked();` — Handler for when the preset checkbox is middle button clicked
- L167 _private prototype_ `FText GetToolTipText() const;`
- L170 _private prototype_ `TSharedRef<SWidget> GetRightClickMenuContent();` — Handler to create a right click menu
- L173 _private prototype_ `void RemovePreset();` — Removes this preset from the presets list
- L176 _private prototype_ `void EnableOnly();` — Enables only this preset from the presets list
- L179 _private prototype_ `void EnableAllPresets();` — Enables all presets in the list
- L182 _private prototype_ `void DisableAllPresets();` — Disables all active presets in the list
- L185 _private prototype_ `void RemoveAllPresets();` — Removes all presets in the list
- L188 _private prototype_ `void SavePreset();` — Saves the current filtering state as this preset
- L191 _private prototype_ `void DeletePreset();` — Deletes this preset
- L194 _private prototype_ `ECheckBoxState IsChecked() const;` — Handler to determine the "checked" state of the preset checkbox
- L197 _private prototype_ `FSlateColor GetPresetForegroundColor() const;` — Handler to determine the color of the checkbox when it is checked
- L200 _private prototype_ `FMargin GetNameLabelPadding() const;` — Handler to determine the padding of the checkbox text when it is pressed
- L203 _private prototype_ `FSlateColor GetNameLabelColorAndOpacity() const;` — Handler to determine the color of the checkbox text when it is hovered
- L206 _private prototype_ `FText GetPresetName() const;` — Returns the display name for this filter
- L209 _private member_ `TSharedPtr<ITraceFilterPreset> FilterPreset;`
- L211 _private member_ `FOnPresetChanged OnPresetChanged;`
- L212 _private member_ `FOnRequestRemove OnRequestRemove;`
- L213 _private member_ `FOnRequestDelete OnRequestDelete;`
- L214 _private member_ `FOnRequestSave OnRequestSave;`
- L215 _private member_ `FOnHighlightPreset OnHighlightPreset;`
- L216 _private member_ `FOnRequestEnableOnly OnRequestEnableOnly;`
- L217 _private member_ `FOnRequestEnableAll OnRequestEnableAll;`
- L218 _private member_ `FOnRequestDisableAll OnRequestDisableAll;`
- L219 _private member_ `FOnRequestDisableAll OnRequestRemoveAll;`
- L222 _private member_ `bool bEnabled;` — True when this preset should be applied to filtering state
- L225 _private member_ `TSharedPtr<SFilterPresetCheckBox> ToggleButtonPtr;` — The button to toggle the preset on or off
- L228 _private member_ `FLinearColor FilterColor;` — The color of the checkbox for this preset
- L231 _private member_ `bool bHighlighted;` — True when this preset its filtering state is currently set to being highlighted

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace TraceTools` (scope `UE`)
- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPresetChanged, const class SFilterPreset&);`
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPresetChanged, const class SFilterPreset&);` (scope `UE::TraceTools`)
- L89 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRequestRemove, const TSharedRef<SFilterPreset>& );`
- L90 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRequestEnableOnly, const TSharedRef<SFilterPreset>& );`
- L91 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRequestDelete, const TSharedRef<SFilterPreset>& );`
- L92 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRequestSave, const TSharedRef<SFilterPreset>& );`
- L93 _delegate_ `DECLARE_DELEGATE_OneParam(FOnHighlightPreset, const TSharedPtr<ITraceFilterPreset>& );`
- L94 _delegate_ `DECLARE_DELEGATE(FOnRequestEnableAll);`
- L95 _delegate_ `DECLARE_DELEGATE(FOnRequestDisableAll);`
- L96 _delegate_ `DECLARE_DELEGATE(FOnRequestRemoveAll);`

### `Source/Developer/TraceTools/Private/Widgets/SFilterPresetList.h` (Private)


#### class `UE::TraceTools::SFilterPresetList`  
`class SFilterPresetList : public SCompoundWidget`  
_L22-138_
- inherits: `SCompoundWidget`
- desc: A list of presets currently applied to insights filtering window
- L25 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSavePreset, const TSharedPtr<ITraceFilterPreset>& );`
- L26 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnHighlightPreset, const TSharedPtr<ITraceFilterPreset>& );`
- L28 _public function_ `SLATE_BEGIN_ARGS( SFilterPresetList )`
- L30 _public prototype_ `SLATE_EVENT(FOnPresetChanged, OnPresetChanged) SLATE_EVENT(FOnSavePreset, OnSavePreset) SLATE_EVENT(FOnHighlightPreset, OnHighlightPreset) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedPtr<ISessionTraceFilterService> InSessionFilterService);` — Delegate for when the selected presets have changed
- L40 _public prototype_ `virtual ~SFilterPresetList();`
- L43 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Begin SCompoundWidget overrides
- L47 _public prototype_ `void GetAllEnabledPresets(TArray<TSharedPtr<ITraceFilterPreset>>& OutPresets) const;` — Returns all filter presets currently set as enabled within this widget
- L50 _public prototype_ `TSharedRef<SWidget> ExternalMakeFilterPresetsMenu();` — Returns the context menu widget generated by MakeFilterPresetsMenu
- L53 _public prototype_ `void RefreshPresetEnabledState();` — Sets channels as enabled/disabled based on the current object list
- L56 _public prototype_ `void RefreshFilterPresets();` — Refreshes the filter preset objects and child widgets
- L60 _private prototype_ `bool HasAnyPresets() const;` — Returns true if any Presets are applied
- L63 _private prototype_ `void EnableAllPresets();` — Enables all Presets
- L66 _private prototype_ `void DisableAllPresets();` — Disables any applied Presets
- L69 _private prototype_ `void RemoveAllPresets();` — Removes all Presets in the list
- L72 _private prototype_ `TSharedRef<SFilterPreset> AddFilterPreset(const TSharedPtr<ITraceFilterPreset> FilterPreset);` — Adds a child widget for the specified filter preset object
- L75 _private prototype_ `void RemoveFilterPresetAndUpdate(const TSharedRef<SFilterPreset>& PresetToRemove);` — Removes the child widget, and calls OnPresetsChanged to ensure the state is updated outside of this widget
- L78 _private prototype_ `void EnableOnlyThisPreset(const TSharedRef<SFilterPreset>& PresetWidgetToEnable);` — Handler for when the enable only this button was clicked on a single preset
- L80 _private prototype_ `void TogglePreset(const TSharedPtr<ITraceFilterPreset> InPreset);`
- L81 _private prototype_ `bool IsPresetEnabled(const TSharedPtr<ITraceFilterPreset> InPreset) const;`
- L84 _private prototype_ `void SaveSettings(const FString& IniFilename) const;` — Saves any settings to config that should be persistent between editor sessions
- L87 _private prototype_ `void LoadSettings(const FString& IniFilename);` — Loads any settings to config that should be persistent between editor sessions
- L89 _private prototype_ `TSharedRef<SWidget> MakeFilterPresetsMenu();`
- L90 _private prototype_ `void GenerateEnginePresetsMenu(FMenuBuilder& InMenuBuilder);`
- L91 _private prototype_ `void GenerateLocalUserPresetsMenu(FMenuBuilder& InMenuBuilder);`
- L92 _private prototype_ `void GenerateCommonPresetEntries(FMenuBuilder& InSubMenuBuilder, const TSharedPtr<ITraceFilterPreset>& UserPreset);`
- L93 _private prototype_ `void GenerateSharedUserPresetsMenu(FMenuBuilder& InMenuBuilder);`
- L96 _private prototype_ `void DeletePreset(const TSharedRef<SFilterPreset>& PresetToDelete);` — Delete the preset object contained by the widget
- L98 _private prototype_ `void SavePreset(const TSharedRef<SFilterPreset>& PresetToSave);` — Save the preset object contained by the widget
- L101 _private prototype_ `void LoadEnginePresets();` — Engine presets have a custom loading so they can be shared with the console commands from FTraceAuxiliary.
- L105 _private member_ `TSharedPtr<SWrapBox> FilterBox;` — The horizontal box which contains all the Presets
- L108 _private member_ `TArray<TSharedRef<SFilterPreset>> Presets;` — All SFilterPreset in the list
- L111 _private member_ `TArray<TSharedPtr<ITraceFilterPreset>> AllFilterPresets;` — All Filter Preset objects
- L114 _private member_ `TArray<TSharedPtr<ITraceFilterPreset>> UserFilterPresets;` — All User Filter Preset objects
- L116 _private member_ `TArray<TSharedPtr<ITraceFilterPreset>> SharedUserFilterPresets;` — All Shared User Filter Preset objects
- L118 _private member_ `TArray<TSharedPtr<ITraceFilterPreset>> EngineFilterPresets;` — All Engine Preset objects
- L121 _private member_ `TWeakObjectPtr<ULocalTraceFilterPresetContainer> PresetContainer;` — Weak pointers to filter preset containers
- L122 _private member_ `TWeakObjectPtr<USharedTraceFilterPresetContainer> SharedPresetContainer;`
- L125 _private member_ `FOnPresetChanged OnPresetChanged;` — Delegate for when Presets have changed
- L128 _private member_ `FOnSavePreset OnSavePreset;` — Delegate for when a Preset is to be saved
- L131 _private member_ `FOnHighlightPreset OnHighlightPreset;` — Delegate for when a Preset is to be highlighted
- L134 _private member_ `TArray<FString> CurrentActiveFilterNames;` — Cached array of currently active filter names, used for saving/restoring state during refreshes
- L137 _private member_ `TSharedPtr<ISessionTraceFilterService> SessionFilterService;` — A pointer to the SessionFilterService to autodetect enabled presets.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TraceTools` (scope `UE`)
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSavePreset, const TSharedPtr<ITraceFilterPreset>& );`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnHighlightPreset, const TSharedPtr<ITraceFilterPreset>& );`

### `Source/Developer/TraceTools/Private/Widgets/STraceControl.h` (Private)


#### class `UE::TraceTools::STraceControl`  
`class STraceControl : public SCompoundWidget`  
_L19-70_
- inherits: `SCompoundWidget`
- L23 _public prototype_ `STraceControl();` — Default constructor.
- L26 _public prototype_ `virtual ~STraceControl();` — Virtual destructor.
- L28 _public function_ `SLATE_BEGIN_ARGS(STraceControl) : _AutoDetectSelectedSession(false)`
- L33 _public prototype_ `SLATE_ARGUMENT(bool, AutoDetectSelectedSession) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<ITraceController> InTraceController);` — Specifies if the widget should autodetect the selected session in Session Browser. If false, the SessionId will need to be set manually.
- L41 _public prototype_ `void SetInstanceId(const FGuid& Id);` — Sets the InstanceId to control. Supports invalid guid value for disabled state.
- L43 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L46 _protected prototype_ `void OnInstanceSelectionChanged(const TSharedPtr<class ISessionInstanceInfo>&, bool);`
- L49 _private member_ `TSharedPtr<ITraceController> TraceController;`
- L51 _private member_ `TSharedPtr<FUICommandList> UICommandList;`
- L54 _private member_ `FGuid InstanceId;` — The InstanceId to control.
- L56 _private member_ `TSharedPtr<STraceControlToolbar> Toolbar;`
- L58 _private member_ `TSharedPtr<STraceDataFilterWidget> TraceDataFilterWidget;`
- L61 _private member_ `TSharedPtr<ISessionManager> SessionManager;` — Session manager used for selecting sessions
- L63 _private member_ `TSharedPtr<ISessionTraceFilterService> SessionFilterService;`
- L65 _private member_ `TSet<FGuid> SelectedSessionsIds;`
- L67 _private member_ `bool bAutoDetectSelectedSession;`
- L69 _private member_ `double AccumulatedTime = 0.0f;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace TraceTools` (scope `UE`)

### `Source/Developer/TraceTools/Private/Widgets/STraceControlToolbar.h` (Private)


#### enum `UE::TraceTools::ETraceTarget`  
`enum ETraceTarget : uint8`  
_L19-23_
- L21 _public enumerator_ `Server = 0`
- L22 _public enumerator_ `File = 1`

#### class `UE::TraceTools::STraceControlToolbar`  
`class STraceControlToolbar : public SCompoundWidget`  
_L28-97_
- inherits: `SCompoundWidget`
- desc: Implements the trace control toolbar widget.
- L33 _public function_ `SLATE_BEGIN_ARGS(STraceControlToolbar)`
- L38 _public prototype_ `STraceControlToolbar();`
- L39 _public prototype_ `~STraceControlToolbar();`
- L41 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FUICommandList>& CommandList, TSharedPtr<ITraceController> InTraceController);`
- L43 _public prototype_ `void SetInstanceId(const FGuid& Id);`
- L46 _private prototype_ `void BindCommands(const TSharedRef<FUICommandList>& CommandList);`
- L48 _private prototype_ `TSharedRef<SWidget> BuildTraceTargetMenu(const TSharedRef<FUICommandList> CommandList);`
- L49 _private prototype_ `FText GetTraceTargetLabelText() const;`
- L50 _private prototype_ `FText GetTraceTargetTooltipText() const;`
- L51 _private prototype_ `FSlateIcon GetTraceTargetIcon() const;`
- L53 _private prototype_ `void OnTraceStatusUpdated(const FTraceStatus& InStatus, FTraceStatus::EUpdateType InUpdateType, ITraceControllerCommands& Commands);`
- L54 _private prototype_ `void InitializeSettings();`
- L56 _private prototype_ `bool SetTraceTarget_CanExecute() const;`
- L57 _private prototype_ `void SetTraceTarget_Execute(ETraceTarget InTraceTarget);`
- L59 _private prototype_ `bool ToggleTrace_CanExecute() const;`
- L60 _private prototype_ `void ToggleTrace_Execute();`
- L62 _private prototype_ `bool TraceSnapshot_CanExecute() const;`
- L63 _private prototype_ `void TraceSnapshot_Execute();`
- L65 _private prototype_ `bool TraceBookmark_CanExecute() const;`
- L66 _private prototype_ `void TraceBookmark_Execute();`
- L68 _private prototype_ `bool TraceScreenshot_CanExecute() const;`
- L69 _private prototype_ `void TraceScreenshot_Execute();`
- L71 _private prototype_ `bool ToggleStatNamedEvents_CanExecute() const;`
- L72 _private prototype_ `bool ToggleStatNamedEvents_IsChecked() const;`
- L73 _private prototype_ `void ToggleStatNamedEvents_Execute();`
- L75 _private prototype_ `FReply TogglePauseResume_OnClicked();`
- L76 _private prototype_ `bool TogglePauseResume_CanExecute() const;`
- L77 _private prototype_ `FText TogglePauseResume_GetTooltip() const;`
- L79 _private prototype_ `const FSlateBrush* GetPauseResumeBrush() const;`
- L81 _private prototype_ `bool IsInstanceAvailable() const;`
- L83 _private prototype_ `void Reset();`
- L86 _private member_ `TSharedPtr<ITraceController> TraceController;`
- L88 _private member_ `ETraceTarget TraceTarget = ETraceTarget::Server;`
- L89 _private member_ `bool bIsTracing = false;`
- L90 _private member_ `bool bIsPaused = false;`
- L91 _private member_ `bool bAreStatNamedEventsEnabled = false;`
- L92 _private member_ `bool bIsTracingAvailable = false;`
- L93 _private member_ `FString TraceHostAddr;`
- L94 _private member_ `FGuid InstanceId;`
- L96 _private member_ `FDelegateHandle OnStatusReceivedDelegate;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace TraceTools` (scope `UE`)

### `Source/Developer/TraceTools/Private/Widgets/STraceDataFilterWidget.h` (Private)


#### class `UE::TraceTools::STraceDataFilterWidget`  
`class STraceDataFilterWidget : public SCompoundWidget`  
_L29-134_
- inherits: `SCompoundWidget`
- L33 _public prototype_ `STraceDataFilterWidget();` — Default constructor.
- L36 _public prototype_ `virtual ~STraceDataFilterWidget();` — Virtual destructor.
- L38 _public function_ `SLATE_BEGIN_ARGS(STraceDataFilterWidget)`
- L39 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<ITraceController> InTraceController, TSharedPtr<ISessionTraceFilterService> InSessionFilterService);`
- L44 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L46 _public function_ `void SetWarningBannerText(const FText& InText)`
- L50 _protected prototype_ `void OnSavePreset(const TSharedPtr<ITraceFilterPreset>& Preset);` — Callback from SFilterPresetList, should save the current tileview filter state as the specified preset
- L52 _protected prototype_ `void OnPresetChanged(const class SFilterPreset& Preset);` — Callback from SFilterPresetList, should update filtering state according to currently active Filter Presets
- L54 _protected prototype_ `void OnHighlightPreset(const TSharedPtr<ITraceFilterPreset>& Preset);` — Callback from SFilterPresetList, should highlight the tileview items encompassed by the specified preset
- L56 _protected prototype_ `void OnSearchboxTextChanged(const FText& FilterText);`
- L57 _protected prototype_ `void OnItemDoubleClicked(TSharedPtr<ITraceObject> InObject) const;`
- L60 _protected prototype_ `void ConstructTileView();` — Constructing various widgets
- L61 _protected prototype_ `void ConstructSearchBoxFilter();`
- L63 _protected prototype_ `bool HasValidData() const;`
- L64 _protected prototype_ `bool ShouldShowBanner() const;`
- L66 _protected prototype_ `void RefreshTileViewData();`
- L69 _protected prototype_ `void EnumerateSelectedItems(TFunction<void(TSharedPtr<ITraceObject> InItem)> InFunction) const;` — Enumerates the (currently selected) tileview items and calls InFunction for each entry
- L70 _protected prototype_ `void EnumerateAllItems(TFunction<void(TSharedPtr<ITraceObject> InItem)> InFunction) const;`
- L71 _protected prototype_ `bool EnumerateAllItems(TFunction<bool(TSharedPtr<ITraceObject> InItem)> InFunction) const;`
- L72 _protected prototype_ `bool EnumerateSelectedItems(TFunction<bool(TSharedPtr<ITraceObject> InItem)> InFunction) const;`
- L75 _protected prototype_ `TSharedRef<ITraceObject> AddFilterableObject(const FTraceObjectInfo& Event, FString ParentName);` — Creates and adds a new tileview object entry, given the specified data
- L78 _protected prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<ITraceObject> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — TileView callbacks
- L79 _protected prototype_ `TSharedPtr<SWidget> OnContextMenuOpening() const;`
- L82 _protected prototype_ `TSharedRef<SWidget> MakeAddFilterMenu();` — Presets dropdown button callback
- L85 _protected prototype_ `void SaveItemSelection();` — (Re) storing item selection state
- L86 _protected prototype_ `void RestoreItemSelection();`
- L88 _protected prototype_ `void OnSessionSelectionChanged();`
- L90 _protected prototype_ `FText GetWarningBannerText() const;`
- L94 _protected member_ `TArray<TSharedPtr<ITraceObject>> ListItems;` — Flat list of contained items
- L96 _protected member_ `TArray<TSharedPtr<ITraceObject>> FilteredListItems;` — Dynamically generated array by filtering
- L99 _protected member_ `TSharedPtr<ISessionTraceFilterService> SessionFilterService;` — Analysis filter service for the current analysis session this window is currently representing
- L101 _protected member_ `FDateTime SyncTimeStamp = 0;` — Timestamp used for refreshing cached filter data
- L104 _protected member_ `TSharedPtr<SHorizontalBox> OptionsWidget;` — Wrapper for presets drop down button
- L107 _protected member_ `TSharedPtr<STileView<TSharedPtr<ITraceObject>>> TileView;` — TileView widget, represents the currently connected analysis session its filtering state
- L110 _protected member_ `bool bNeedsListRefresh;` — Flag indicating the tileview should be refreshed
- L113 _protected member_ `TSharedPtr<SSearchBox> SearchBoxWidget;` — Search box for filtering the tileview items
- L115 _protected member_ `TSharedPtr<TTextFilter<TSharedPtr<ITraceObject>>> SearchBoxWidgetFilter;` — The text filter used by the search box
- L118 _protected member_ `TSharedPtr<SFilterPresetList> FilterPresetsListWidget;` — Filter presets bar widget
- L121 _protected member_ `bool bHighlightingPreset;` — Whether or not we a currently highlighting a preset
- L124 _protected member_ `TSet<FString> SelectedObjectNames;` — Cached state of which named entries were selected
- L126 _protected member_ `TSharedPtr<SScrollBar> ExternalScrollbar;`
- L128 _protected member_ `TSharedPtr<ITraceController> TraceController;`
- L130 _protected member_ `bool bHasChannelData = false;`
- L131 _protected member_ `bool bHasSettings = false;`
- L133 _protected member_ `FText WarningBannerText;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace TraceTools` (scope `UE`)

### `Source/Developer/TraceTools/Private/Widgets/STraceObjectRowWidget.h` (Private)


#### class `UE::TraceTools::STraceObjectRowWidget`  
`class STraceObjectRowWidget : public STableRow<TSharedPtr<ITraceObject>>`  
_L14-29_
- inherits: `STableRow<TSharedPtr<ITraceObject>>`
- L16 _private function_ `SLATE_BEGIN_ARGS(STraceObjectRowWidget)`
- L18 _private prototype_ `SLATE_ATTRIBUTE(FText, HighlightText) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedPtr<ITraceObject> InObject);` — The current text to highlight
- L22 _private prototype_ `virtual ~STraceObjectRowWidget() = default;`
- L26 _protected member_ `TSharedPtr<ITraceObject> Object;` — The trace object that this tree item represents
- L27 _protected member_ `TAttribute<FText> HighlightTextAttribute;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace TraceTools` (scope `UE`)

### `Source/Developer/TraceTools/Private/Widgets/STraceStatistics.h` (Private)


#### class `UE::TraceTools::STraceStatistics`  
`class STraceStatistics : public SCompoundWidget`  
_L21-49_
- inherits: `SCompoundWidget`
- desc: A widget that displays trace settings and trace statistics
- L25 _public function_ `SLATE_BEGIN_ARGS(STraceStatistics)`
- L29 _public prototype_ `STraceStatistics();`
- L30 _public prototype_ `virtual ~STraceStatistics();`
- L32 _public prototype_ `void Construct( const FArguments& InArgs, TSharedPtr<ISessionTraceFilterService> SessionFilterService);`
- L35 _private prototype_ `FText GetSettingsOnOffText(bool InValue) const;`
- L36 _private prototype_ `FText GetSettingsMemoryValueText(uint64 InValue) const;`
- L37 _private prototype_ `FText GetStatsMemoryValueText(uint64 InValue) const;`
- L38 _private prototype_ `FText GetStatsBandwidthText(uint64 InValue) const;`
- L39 _private prototype_ `FText GetStatsCacheText() const;`
- L40 _private prototype_ `FText GetTraceEndpointText() const;`
- L41 _private prototype_ `FText GetTraceSystemStateText() const;`
- L42 _private prototype_ `FText GetTraceSystemStateTooltipText() const;`
- L44 _private prototype_ `FReply CopyEndpoint_OnClicked() const;`
- L45 _private prototype_ `EVisibility GetCopyEndpointVisibility() const;`
- L48 _private member_ `TSharedPtr<ISessionTraceFilterService> SessionFilterService;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TraceTools` (scope `UE`)

### `Source/Developer/TraceTools/Public/TraceTools/Interfaces/ITraceToolsModule.h` (Public)


#### class `UE::TraceTools::ITraceToolsModule`  
`class ITraceToolsModule : public IModuleInterface`  
_L21-49_
- inherits: `IModuleInterface`
- desc: Interface for a trace tools module.
- L30 _public prototype_ `virtual TSharedRef<SWidget> CreateTraceControlWidget(TSharedPtr<ITraceController> InTraceController) = 0;` — Creates a trace control widget that auto detects the session selected in Session Browser and can be used to control it. @return The new widget
- L37 _public prototype_ `virtual TSharedRef<SWidget> CreateTraceControlWidget(TSharedPtr<ITraceController> InTraceController, FGuid InstanceId) = 0;` — Creates a trace control widget that controls a specific Instance Id. @return The new widget
- L42 _public prototype_ `virtual void SetTraceControlWidgetInstanceId(TSharedRef<SWidget> Widget, FGuid InstanceId) = 0;` — Sets the InstanceId to control for the provided widget, which must be a widget returned by CreateTraceControlWidget.
- L48 _public prototype_ `virtual ~ITraceToolsModule( ) = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace TraceTools` (scope `UE`)

### `Source/Developer/TraceTools/Public/TraceTools/Widgets/SToggleTraceButton.h` (Public)


#### class `UE::TraceTools::SToggleTraceButton`  
`class SToggleTraceButton : public SCompoundWidget`  
_L17-88_
- inherits: `SCompoundWidget`
- desc: A dynamic button that can start/stop trace. When tracing is started the button turns red and has a pulse animation.
- L29 _public prototype_ `DECLARE_DELEGATE(FOnToggleTraceRequested);`
- L31 _public function_ `SLATE_BEGIN_ARGS(SToggleTraceButton) : _ButtonSize(EButtonSize::StatusBar) , _ShowStopButton(true)`
- L57 _public prototype_ `SToggleTraceButton();`
- L58 _public prototype_ `virtual ~SToggleTraceButton();`
- L60 _public prototype_ `void Construct( const FArguments& InArgs);`
- L63 _private prototype_ `FSlateColor GetRecordingButtonColor() const;`
- L64 _private prototype_ `FSlateColor GetRecordingButtonOutlineColor() const;`
- L65 _private prototype_ `FText GetRecordingButtonTooltipText() const;`
- L66 _private prototype_ `FText GetRecordingButtonLabelText() const;`
- L68 _private prototype_ `EVisibility GetStartTraceIconVisibility() const;`
- L69 _private prototype_ `EVisibility GetStopTraceIconVisibility() const;`
- L71 _private prototype_ `void ToggleTrace_OnClicked() const;`
- L73 _private prototype_ `const FSlateBrush* GetToggleTraceCenterBrush() const;`
- L74 _private prototype_ `const FSlateBrush* GetToggleTraceOutlineBrush() const;`
- L75 _private prototype_ `const FSlateBrush* GetToggleTraceStopBrush() const;`
- L78 _private member_ `FOnToggleTraceRequested OnToggleTraceRequested;`
- L80 _private member_ `bool bIsTraceRecordButtonHovered = false;`
- L81 _private member_ `mutable double ConnectionStartTime = 0.0f;`
- L83 _private member_ `TSlateAttribute<bool> IsTraceRunningAttribute;`
- L84 _private member_ `TSlateAttribute<FText> DynamicToolTipTextAttribute;`
- L85 _private member_ `TSlateAttribute<FText> LabelTextAttribute;`
- L86 _private member_ `EButtonSize ButtonSize;`
- L87 _private member_ `bool bShowStopButton;`

#### enum `UE::TraceTools::SToggleTraceButton::EButtonSize`  
`enum class EButtonSize : uint32`  
_L23-27_
- L25 _public enumerator_ `StatusBar = 0` — 16x16
- L26 _public enumerator_ `SlimToolbar = 1` — 20x20

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace TraceTools` (scope `UE`)
- L29 _delegate_ `DECLARE_DELEGATE(FOnToggleTraceRequested);`
