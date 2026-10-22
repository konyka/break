# Plugins / EditorSysConfigAssistant

- module root: `Plugins/Editor/EditorSysConfigAssistant/Source/EditorSysConfigAssistant`
- headers: 11; symbols: 104
- symbol kinds: class=9, delegate=1, enum=2, enumerator=8, function=16, macro=3, member=13, prototype=51, struct=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, EditorSubsystem, Engine, Slate, SlateCore, ToolWidgets, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, InputCore, InteractiveToolsFramework, UnrealEd

### `Plugins/Editor/EditorSysConfigAssistant/Source/EditorSysConfigAssistant/Private/Widgets/EditorSysConfigAssistantDelegates.h` (Private)


#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnApplySysConfigChange, const TSharedPtr<FEditorSysConfigIssue>&)` — Delegate type for Editor System Configuration Assistant action running. The first parameter is the FEditorSysConfigIssue that you want to resolve issues on.

### `Plugins/Editor/EditorSysConfigAssistant/Source/EditorSysConfigAssistant/Private/Widgets/SEditorSysConfigAssistant.h` (Private)


#### class `SEditorSysConfigAssistant`  
`class SEditorSysConfigAssistant : public SCompoundWidget`  
_L23-59_
- inherits: `SCompoundWidget`
- desc: Implements a Slate widget for the editor system configuration user interface.
- L28 _public function_ `SLATE_BEGIN_ARGS(SEditorSysConfigAssistant)`
- L34 _public prototype_ `SEditorSysConfigAssistant();` — Constructor.
- L37 _public prototype_ `~SEditorSysConfigAssistant();` — Destructor.
- L49 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow);` — Constructs the widget. @param InArgs The Slate argument list. @param ConstructUnderMajorTab The major tab which will contain the session front-end. @param ConstructUnderWindow The window in which this widget is being constructed. @param InModel The view model to use.
- L54 _private prototype_ `void OnApplySysConfigChange(const TSharedPtr<FEditorSysConfigIssue>& Issue);`
- L57 _private member_ `TSharedPtr<SEditorSysConfigAssistantIssueListView> IssueListView;`

### `Plugins/Editor/EditorSysConfigAssistant/Source/EditorSysConfigAssistant/Private/Widgets/SEditorSysConfigAssistantIssueApplyButton.h` (Private)


#### class `SEditorSysConfigAssistantIssueApplyButton`  
`class SEditorSysConfigAssistantIssueApplyButton : public SCompoundWidget`  
_L25-85_
- inherits: `SCompoundWidget`
- desc: Implements a button for applying config changes to resolve a system configuration issue.
- L30 _public function_ `SLATE_BEGIN_ARGS(SEditorSysConfigAssistantIssueApplyButton)`
- L36 _public function_ `void Construct(const FArguments& InArgs, bool InShowText)`
- L61 _public function_ `virtual TSharedPtr<IToolTip> GetToolTip() override`
- L68 _private function_ `bool HasError() const`
- L73 _private function_ `bool ButtonEnabled() const`
- L78 _private function_ `const FSlateBrush* GetApplyIcon() const`

#### Free symbols / members of external scopes

- L20 _macro_ `#define LOCTEXT_NAMESPACE "SEditorSysConfigAssistantIssueApplyButton"`

### `Plugins/Editor/EditorSysConfigAssistant/Source/EditorSysConfigAssistant/Private/Widgets/SEditorSysConfigAssistantIssueListRow.h` (Private)


#### class `SEditorSysConfigAssistantIssueListRow`  
`class SEditorSysConfigAssistantIssueListRow : public STableRow<TSharedPtr<FEditorSysConfigIssue>>`  
_L33-208_
- inherits: `STableRow<TSharedPtr<FEditorSysConfigIssue>>`
- desc: Implements a row widget for the editor's system configuration assistant issue list.
- L38 _public function_ `SLATE_BEGIN_ARGS(SEditorSysConfigAssistantIssueListRow)`
- L53 _public prototype_ `~SEditorSysConfigAssistantIssueListRow() = default;`
- L55 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)`
- L174 _private function_ `FReply OnApplySysConfigChangeClicked()`
- L185 _private function_ `const FSlateBrush* HandleIssueImage( ) const` — Callback for getting the icon image of the issue.
- L191 _private function_ `FText HandleIssueNameText() const` — Callback for getting the friendly name.
- L196 _private function_ `FText HandleIssueDescriptionText() const`
- L204 _private member_ `TSharedPtr<FEditorSysConfigIssue> Issue;` — Holds a reference to the issue that is displayed in this row.
- L207 _private member_ `FOnApplySysConfigChange OnApplySysConfigChange;` — Holds a delegate to be invoked when a change is applied.

#### Free symbols / members of external scopes

- L28 _macro_ `#define LOCTEXT_NAMESPACE "SEditorSysConfigAssistantIssueListRow"`

### `Plugins/Editor/EditorSysConfigAssistant/Source/EditorSysConfigAssistant/Private/Widgets/SEditorSysConfigAssistantIssueListView.h` (Private)


#### class `SEditorSysConfigAssistantIssueListView`  
`class SEditorSysConfigAssistantIssueListView : public SCompoundWidget`  
_L21-70_
- inherits: `SCompoundWidget`
- desc: Implements the deployment targets panel.
- L26 _public function_ `SLATE_BEGIN_ARGS(SEditorSysConfigAssistantIssueListView)`
- L33 _public prototype_ `~SEditorSysConfigAssistantIssueListView();` — Destructor.
- L40 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the widget. @param InArgs The Slate argument list.
- L44 _public prototype_ `void RefreshIssueList();` — Refresh the list of issues.
- L49 _private prototype_ `bool HandleIssueListRowIsEnabled(TSharedPtr<FEditorSysConfigIssue> Issue) const;` — Callback for getting the enabled state of a issue list row.
- L52 _private prototype_ `TSharedRef<ITableRow> HandleIssueListViewGenerateRow(TSharedPtr<FEditorSysConfigIssue> InItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Callback for generating a row in the issue view.
- L55 _private prototype_ `void HandleIssueAdded(const TSharedPtr<FEditorSysConfigIssue> AddedIssue);` — Callback for when an issue has been added to the issue list.
- L58 _private prototype_ `void HandleIssueRemoved(const TSharedPtr<FEditorSysConfigIssue> RemovedIssue);` — Callback for when an issue has been added to the issue list.
- L63 _private member_ `TArray<TSharedPtr<FEditorSysConfigIssue>> IssueList;` — Holds the list of available issues.
- L66 _private member_ `TSharedPtr<SListView<TSharedPtr<FEditorSysConfigIssue>> > IssueListView;` — Holds the issue list view .
- L69 _private member_ `FOnApplySysConfigChange OnApplySysConfigChange;` — Holds a delegate to be invoked when an issue applies a config change.

### `Plugins/Editor/EditorSysConfigAssistant/Source/EditorSysConfigAssistant/Private/Windows/EditorSysConfigFeatureLastAccessTime.h` (Private)


#### class `FEditorSysConfigFeatureLastAccessTime`  
`class FEditorSysConfigFeatureLastAccessTime : public IEditorSysConfigFeature`  
_L10-22_
- inherits: `IEditorSysConfigFeature`
- L13 _public prototype_ `virtual ~FEditorSysConfigFeatureLastAccessTime() = default;`
- L15 _public prototype_ `virtual FText GetDisplayName() const override;`
- L16 _public prototype_ `virtual FText GetDisplayDescription() const override;`
- L17 _public prototype_ `virtual FGuid GetVersion() const override;`
- L18 _public prototype_ `virtual EEditorSysConfigFeatureRemediationFlags GetRemediationFlags() const override;`
- L20 _public prototype_ `virtual void StartSystemCheck() override;`
- L21 _public prototype_ `virtual void ApplySysConfigChanges(TArray<FString>& OutElevatedCommands) override;`

### `Plugins/Editor/EditorSysConfigAssistant/Source/EditorSysConfigAssistant/Private/Windows/EditorSysConfigFeatureUSNJournal.h` (Private)


#### class `FEditorSysConfigFeatureUSNJournal`  
`class FEditorSysConfigFeatureUSNJournal : public IEditorSysConfigFeature`  
_L10-25_
- inherits: `IEditorSysConfigFeature`
- L13 _public prototype_ `virtual ~FEditorSysConfigFeatureUSNJournal() = default;`
- L15 _public prototype_ `virtual FText GetDisplayName() const override;`
- L16 _public prototype_ `virtual FText GetDisplayDescription() const override;`
- L17 _public prototype_ `virtual FGuid GetVersion() const override;`
- L18 _public prototype_ `virtual EEditorSysConfigFeatureRemediationFlags GetRemediationFlags() const override;`
- L20 _public prototype_ `virtual void StartSystemCheck() override;`
- L21 _public prototype_ `virtual void ApplySysConfigChanges(TArray<FString>& OutElevatedCommands) override;`
- L24 _private member_ `FString VolumeName;`

### `Plugins/Editor/EditorSysConfigAssistant/Source/EditorSysConfigAssistant/Public/EditorSysConfigAssistantModule.h` (Public)


#### class `IEditorSysConfigAssistantModule`  
`class IEditorSysConfigAssistantModule : public IModuleInterface`  
_L8-21_
- inherits: `IModuleInterface`
- L11 _public function_ `static FORCEINLINE IEditorSysConfigAssistantModule& Get()`
- L17 _public prototype_ `virtual bool CanShowSystemConfigAssistant() = 0;` — Checks if it is possible to show the system configuration assistant UI to the user
- L20 _public prototype_ `virtual void ShowSystemConfigAssistant() = 0;` — Attempts to present the system configuration assistant UI to the user

### `Plugins/Editor/EditorSysConfigAssistant/Source/EditorSysConfigAssistant/Public/EditorSysConfigAssistantSubsystem.h` (Public)


#### class `UEditorSysConfigAssistantSubsystem`  
`class UEditorSysConfigAssistantSubsystem : public UEditorSubsystem`  
_L17-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- L22 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L23 _public prototype_ `virtual void Deinitialize() override;`
- L24 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L27 _public prototype_ `void AddIssue(const FEditorSysConfigIssue& Issue);` — Can be called on any thread
- L29 _public prototype_ `TArray<TSharedPtr<FEditorSysConfigIssue>> GetIssues();` — Can be called on any thread
- L32 _public prototype_ `void ApplySysConfigChanges(TArrayView<const TSharedPtr<FEditorSysConfigIssue>> Issues);` — Must be called on the game thread
- L35 _public prototype_ `void DismissSystemConfigNotification();` — Must be called on the game thread
- L38 _private prototype_ `void HandleModularFeatureRegistered(const FName& InFeatureName, IModularFeature* InFeature);`
- L39 _private prototype_ `void HandleModularFeatureUnregistered(const FName& InFeatureName, IModularFeature* InFeature);`
- L41 _private prototype_ `void HandleAssistantInitializationEvent();`
- L44 _private prototype_ `static void NotifySystemConfigIssues();` — Must be called on the game thread
- L47 _private prototype_ `void NotifyRestart(bool bApplicationOnly);` — Must be called on the game thread
- L49 _private prototype_ `void OnApplicationRestartClicked();`
- L50 _private prototype_ `void OnSystemRestartClicked();`
- L51 _private prototype_ `void OnRestartDismissClicked();`
- L53 _private member_ `FRWLock IssuesLock;`
- L54 _private member_ `TArray<TSharedPtr<FEditorSysConfigIssue>> Issues;`
- L56 _private member_ `TSharedPtr<SNotificationItem> IssueNotificationItem;`
- L57 _private member_ `TWeakPtr<SNotificationItem> RestartNotificationItem;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API EDITORSYSCONFIGASSISTANT_API`

### `Plugins/Editor/EditorSysConfigAssistant/Source/EditorSysConfigAssistant/Public/EditorSysConfigFeature.h` (Public)


#### enum `EEditorSysConfigFeatureRemediationFlags`  
`enum class EEditorSysConfigFeatureRemediationFlags : uint32`  
_L14-24_
- L16 _public enumerator_ `NoAutomatedRemediation = 0`
- L17 _public enumerator_ `HasAutomatedRemediation = 1 << 0`
- L18 _public enumerator_ `RequiresElevation = 1 << 1`
- L19 _public enumerator_ `RequiresApplicationRestart = 1 << 2`
- L22 _public enumerator_ `RequiresSystemRestart = 1 << 3` — Windows specific support for system restart

#### class `IEditorSysConfigFeature`  
`class IEditorSysConfigFeature : public IModularFeature`  
_L27-48_
- inherits: `IModularFeature`
- L30 _public prototype_ `virtual ~IEditorSysConfigFeature() = default;`
- L32 _public function_ `static FName GetModularFeatureName()`
- L38 _public prototype_ `virtual FText GetDisplayName() const = 0;`
- L39 _public prototype_ `virtual FText GetDisplayDescription() const = 0;`
- L40 _public prototype_ `virtual FGuid GetVersion() const = 0;`
- L41 _public prototype_ `virtual EEditorSysConfigFeatureRemediationFlags GetRemediationFlags() const = 0;`
- L44 _public prototype_ `virtual void StartSystemCheck() = 0;` — Called from the game thread, encouraged to perform work asynchronously
- L47 _public prototype_ `virtual void ApplySysConfigChanges(TArray<FString>& OutElevatedCommands) = 0;` — Called from the game thread, must complete synchronously

#### Free symbols / members of external scopes

- L25 _prototype_ `ENUM_CLASS_FLAGS(EEditorSysConfigFeatureRemediationFlags);`

### `Plugins/Editor/EditorSysConfigAssistant/Source/EditorSysConfigAssistant/Public/EditorSysConfigIssue.h` (Public)


#### enum `EEditorSysConfigIssueSeverity`  
`enum class EEditorSysConfigIssueSeverity : uint8`  
_L7-12_
- L9 _public enumerator_ `High`
- L10 _public enumerator_ `Medium`
- L11 _public enumerator_ `Low`

#### struct `FEditorSysConfigIssue`  
`struct FEditorSysConfigIssue`  
_L14-18_
- L16 _public member_ `IEditorSysConfigFeature* Feature;`
- L17 _public member_ `EEditorSysConfigIssueSeverity Severity;`
