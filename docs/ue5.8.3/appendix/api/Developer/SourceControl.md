# Developer / SourceControl

- module root: `Source/Developer/SourceControl`
- headers: 27; symbols: 1163
- symbol kinds: class=57, delegate=21, enum=19, enumerator=57, externvar=7, function=289, macro=5, member=218, namespace=8, prototype=453, struct=14, typedef=15
- DynamicallyLoadedModuleNames: AssetTools
- PrivateDependencyModuleNames: AssetRegistry, EditorFramework, Engine, MessageLog, RHI, RenderCore, Slate, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, SlateCore

### `Source/Developer/SourceControl/Private/DefaultSourceControlProvider.h` (Private)


#### class `FDefaultSourceControlProvider`  
`class FDefaultSourceControlProvider : public ISourceControlProvider`  
_L13-53_
- inherits: `ISourceControlProvider`
- desc: Default source control provider implementation - "None"
- L17 _public prototype_ `virtual void Init(bool bForceConnection = true) override;` — ISourceControlProvider implementation
- L18 _public prototype_ `virtual void Close() override;`
- L19 _public prototype_ `virtual FText GetStatusText() const override;`
- L20 _public prototype_ `virtual TMap<EStatus, FString> GetStatus() const override;`
- L21 _public prototype_ `virtual bool IsAvailable() const override;`
- L22 _public prototype_ `virtual bool IsEnabled() const override;`
- L23 _public prototype_ `virtual const FName& GetName(void) const override;`
- L24 _public function_ `virtual bool QueryStateBranchConfig(const FString& ConfigSrc, const FString& ConfigDest) override`
- L25 _public function_ `virtual void RegisterStateBranches(const TArray<FString>& BranchNames, const FString& ContentRoot) override`
- L26 _public function_ `virtual int32 GetStateBranchIndex(const FString& BranchName) const override`
- L27 _public function_ `virtual bool GetStateBranchAtIndex(int32 BranchIndex, FString& OutBranchName) const override`
- L28 _public prototype_ `virtual ECommandResult::Type GetState( const TArray<FString>& InFiles, TArray<FSourceControlStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage ) override;`
- L29 _public prototype_ `virtual ECommandResult::Type GetState(const TArray<FSourceControlChangelistRef>& InChangelists, TArray<FSourceControlChangelistStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage) override;`
- L30 _public prototype_ `virtual TArray<FSourceControlStateRef> GetCachedStateByPredicate(TFunctionRef<bool(const FSourceControlStateRef&)> Predicate) const override;`
- L31 _public prototype_ `virtual FDelegateHandle RegisterSourceControlStateChanged_Handle( const FSourceControlStateChanged::FDelegate& SourceControlStateChanged ) override;`
- L32 _public prototype_ `virtual void UnregisterSourceControlStateChanged_Handle( FDelegateHandle Handle ) override;`
- L33 _public prototype_ `virtual ECommandResult::Type Execute( const FSourceControlOperationRef& InOperation, FSourceControlChangelistPtr InChangelist, const TArray<FString>& InFiles, EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() ) override;`
- L34 _public prototype_ `virtual bool CanExecuteOperation( const FSourceControlOperationRef& InOperation ) const override;`
- L35 _public prototype_ `virtual bool CanCancelOperation( const FSourceControlOperationRef& InOperation ) const override;`
- L36 _public prototype_ `virtual void CancelOperation( const FSourceControlOperationRef& InOperation ) override;`
- L37 _public prototype_ `virtual bool UsesLocalReadOnlyState() const override;`
- L38 _public prototype_ `virtual bool UsesChangelists() const override;`
- L39 _public prototype_ `virtual bool UsesUncontrolledChangelists() const override;`
- L40 _public prototype_ `virtual bool UsesCheckout() const override;`
- L41 _public prototype_ `virtual bool UsesFileRevisions() const override;`
- L42 _public prototype_ `virtual bool UsesSnapshots() const override;`
- L43 _public prototype_ `virtual bool UsesSoftRevertOnDelete() const override;`
- L44 _public prototype_ `virtual bool AllowsDiffAgainstDepot() const override;`
- L45 _public prototype_ `virtual TOptional<bool> HasChangesToSync() const override;`
- L46 _public prototype_ `virtual TOptional<bool> HasChangesToCheckIn() const override;`
- L47 _public prototype_ `virtual void Tick() override;`
- L48 _public prototype_ `virtual TArray< TSharedRef<class ISourceControlLabel> > GetLabels( const FString& InMatchingSpec ) const override;`
- L49 _public prototype_ `virtual TArray<FSourceControlChangelistRef> GetChangelists( EStateCacheUsage::Type InStateCacheUsage ) override;`
- L51 _public prototype_ `virtual TSharedRef<class SWidget> MakeSettingsWidget() const override;`

### `Source/Developer/SourceControl/Private/SSourceControlLogin.h` (Private)


#### enum `ELoginConnectionState::Type`  
`enum Type`  
_L22-27_
- L24 _public enumerator_ `Disconnected`
- L25 _public enumerator_ `Connecting`
- L26 _public enumerator_ `Connected`

#### class `SSourceControlLogin`  
`class SSourceControlLogin : public SCompoundWidget`  
_L30-115_
- inherits: `SCompoundWidget`
- L34 _public function_ `SLATE_BEGIN_ARGS(SSourceControlLogin)`
- L46 _public prototype_ `void Construct(const FArguments& InArgs);`
- L51 _public prototype_ `void RefreshSettings();` — Refresh the displayed settings. Usually called when a provider is changed.
- L56 _private prototype_ `EActiveTimerReturnType TickSourceControlModule( double InCurrentTime, float InDeltaTime );` — Ticks the source control module (only necessary if the login window is modal)
- L59 _private prototype_ `FReply OnAcceptSettings();` — Delegate called when the user clicks the 'Accept Settings' button
- L62 _private prototype_ `FReply OnDisableSourceControl();` — Delegate called when the user clicks the 'Disable Source Control' button
- L65 _private prototype_ `void DisplayConnectionError(const FText& InErrorText = FText());` — Called when a connection attempt fails
- L68 _private prototype_ `void DisplayConnectionSuccess() const;` — Called when a connection attempt succeeds
- L71 _private prototype_ `void SourceControlOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Delegate called form the source control system when a login attempt has completed
- L74 _private prototype_ `bool AreControlsEnabled() const;` — Delegate to determine control enabled state
- L77 _private prototype_ `bool IsAcceptSettingsEnabled() const;` — Delegate to determine 'accept settings' button enabled state
- L80 _private prototype_ `EVisibility GetThrobberVisibility() const;` — Delegate to determine visibility of the throbber
- L83 _private prototype_ `EVisibility GetSettingsVisibility() const;` — Delegate to determine visibility of the settings widget
- L86 _private prototype_ `EVisibility GetDisabledTextVisibility() const;` — Delegate to determine visibility of the disabled text widget
- L89 _private prototype_ `bool ConfirmDisableSourceControl() const;` — Requests confirmation of disabling source control
- L92 _private prototype_ `void SaveSettingsToDisk() const;` — Flushes all current revision control settings to disk
- L96 _private member_ `static const float RefreshFrequency;` — The frequency at which to tick to scc module when inside a modal window
- L99 _private member_ `TWeakPtr<SWindow> ParentWindowPtr;` — The parent window of this widget
- L102 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Holds the details view.
- L105 _private member_ `ELoginConnectionState::Type ConnectionState;` — Current connection state
- L108 _private member_ `FSourceControlLoginClosed SourceControlLoginClosed;` — Delegate called when the window is closed
- L111 _private member_ `TSharedPtr<SBox> SettingsBorder;` — The currently displayed settings widget container
- L114 _private member_ `TWeakPtr<FActiveTimerHandle> ActiveTimerHandle;` — The handle to the active scc module tick

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace ELoginConnectionState`

### `Source/Developer/SourceControl/Private/SSourceControlPicker.h` (Private)


#### class `SSourceControlPicker`  
`class SSourceControlPicker : public SCompoundWidget`  
_L17-48_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SSourceControlPicker)`
- L27 _public prototype_ `void Construct(const FArguments& InArgs);`
- L32 _private prototype_ `void ChangeSourceControlProvider(int32 ProviderIndex) const;` — Delegate called when changing source control providers
- L35 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();` — Get the content for the drop-down menu for picking providers
- L38 _private prototype_ `FText OnGetButtonText() const;` — Get the button text for the drop-down
- L41 _private prototype_ `FText GetProviderText(const FName& InName) const;` — Get the text to be displayed given the name of the provider
- L44 _private prototype_ `bool ConfirmProviderChanging() const;` — Requests confirmation for the change of provider
- L47 _private member_ `int CurrentProviderIndex = -1;` — The index of the currently active provider

### `Source/Developer/SourceControl/Private/SourceControlCVars.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace SourceControlCVars`
- L10 _externvar_ `extern TAutoConsoleVariable<bool> CVarSourceControlEnableRevertFromSceneOutliner;` (scope `SourceControlCVars`)
- L11 _externvar_ `extern TAutoConsoleVariable<bool> CVarSourceControlEnableRevertFromSubmitWidget;` (scope `SourceControlCVars`)
- L12 _externvar_ `extern TAutoConsoleVariable<bool> CVarSourceControlEnableRevertUnsaved;` (scope `SourceControlCVars`)
- L13 _externvar_ `extern TAutoConsoleVariable<bool> CVarSourceControlEnableLoginDialogModal;` (scope `SourceControlCVars`)
- L15 _externvar_ `extern TAutoConsoleVariable<int32> CVarSourceControlIntervalBatchStatusUpdate;` (scope `SourceControlCVars`)
- L17 _externvar_ `extern TAutoConsoleVariable<bool> CVarSourceControlDisplaySyncStatus;` (scope `SourceControlCVars`)
- L18 _externvar_ `extern TAutoConsoleVariable<bool> CVarSourceControlDisplayCheckInStatus;` (scope `SourceControlCVars`)

### `Source/Developer/SourceControl/Private/SourceControlModule.h` (Private)


#### class `FSourceControlModule`  
`class FSourceControlModule final : public ISourceControlModule`  
_L22-197_
- inherits: `ISourceControlModule`
- L25 _public prototype_ `FSourceControlModule();`
- L28 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L29 _public prototype_ `virtual void ShutdownModule() override;`
- L32 _public prototype_ `virtual void GetProviderNames(TArray<FName>& OutProviderNames) override;` — ISourceControlModule implementation
- L33 _public prototype_ `virtual void Tick() override;`
- L34 _public prototype_ `virtual void QueueStatusUpdate(const TArray<UPackage*>& InPackages) override;`
- L35 _public prototype_ `virtual void QueueStatusUpdate(const TArray<FString>& InFilenames) override;`
- L36 _public prototype_ `virtual void QueueStatusUpdate(UPackage* InPackage) override;`
- L37 _public prototype_ `virtual void QueueStatusUpdate(const FString& InFilename) override;`
- L38 _public prototype_ `virtual bool IsEnabled() const override;`
- L39 _public prototype_ `virtual ISourceControlProvider& GetProvider() const override;`
- L40 _public prototype_ `virtual TUniquePtr<ISourceControlProvider> CreateProvider(const FName& ProviderName, const FStringView& OwnerName, const FSourceControlInitSettings& InitialSettings) const override;`
- L41 _public prototype_ `virtual FSourceControlAssetDataCache& GetAssetDataCache() override;`
- L42 _public prototype_ `virtual void SetProvider( const FName& InName ) override;`
- L43 _public prototype_ `virtual void ShowLoginDialog(const FSourceControlLoginClosed& InOnSourceControlLoginClosed, ELoginWindowMode::Type InLoginWindowMode, EOnLoginWindowStartup::Type InOnLoginWindowStartup = EOnLoginWindowStartup::ResetProviderToNone) override;`
- L44 _public prototype_ `virtual bool GetUseGlobalSettings() const override;`
- L45 _public prototype_ `virtual void SetUseGlobalSettings(bool bIsUseGlobalSettings) override;`
- L46 _public prototype_ `virtual FSourceControlProviderChanging& GetSourceControlProviderChanging() override;`
- L47 _public prototype_ `virtual FDelegateHandle RegisterProviderChanged(const FSourceControlProviderChanged::FDelegate& SourceControlProviderChanged) override;`
- L48 _public prototype_ `virtual void UnregisterProviderChanged(FDelegateHandle Handle) override;`
- L50 _public prototype_ `virtual void RegisterPreSubmitChangelistValidationEx(const FSourceControlPreSubmitChangelistValidationExDelegate& PreSubmitChangelistValidationDelegate) override;`
- L51 _public prototype_ `virtual void UnregisterPreSubmitChangelistValidation() override;`
- L52 _public prototype_ `virtual FSourceControlPreSubmitChangelistValidationExDelegate GetRegisteredPreSubmitChangelistValidationEx() override;`
- L54 _public prototype_ `virtual void RegisterPreSubmitFilesValidationEx(const FSourceControlPreSubmitFilesValidationExDelegate& PreSubmitFilesValidationDelegate) override;`
- L55 _public prototype_ `virtual void UnregisterPreSubmitFilesValidation() override;`
- L56 _public prototype_ `virtual FSourceControlPreSubmitFilesValidationExDelegate GetRegisteredPreSubmitFilesValidationEx() override;`
- L58 _public prototype_ `virtual FDelegateHandle RegisterPreSubmitFinalize(const FSourceControlPreSubmitFinalizeDelegate::FDelegate& Delegate) override;`
- L59 _public prototype_ `virtual void UnregisterPreSubmitFinalize(FDelegateHandle Handle) override;`
- L60 _public prototype_ `virtual const FSourceControlPreSubmitFinalizeDelegate& GetOnPreSubmitFinalize() const override;`
- L62 _public prototype_ `virtual FDelegateHandle RegisterFilesDeleted(const FSourceControlFilesDeletedDelegate::FDelegate& InDelegate) override;`
- L63 _public prototype_ `virtual void UnregisterFilesDeleted(FDelegateHandle InHandle) override;`
- L64 _public prototype_ `virtual const FSourceControlFilesDeletedDelegate& GetOnFilesDeleted() const override;`
- L66 _public prototype_ `virtual void RegisterCustomProjectsDelegate(FSourceControlCustomProjectsDelegate InCustomProjectsDelegate) override;`
- L67 _public prototype_ `virtual void UnregisterCustomProjectsDelegate() override;`
- L68 _public prototype_ `virtual TArray<FSourceControlProjectInfo> GetCustomProjects() const override;`
- L69 _public prototype_ `virtual FSimpleMulticastDelegate& OnCustomProjectsChanged() override;`
- L70 _public prototype_ `virtual FString GetSourceControlProjectDir() const override;`
- L73 _public prototype_ `virtual void RegisterSourceControlProjectDirDelegate(const FSourceControlProjectDirDelegate& SourceControlProjectDirDelegate) override;` — `UE_DEPRECATED(5.5, "Use RegisterCustomProjectsDelegate instead.")`
- L75 _public prototype_ `virtual void UnregisterSourceControlProjectDirDelegate() override;` — `UE_DEPRECATED(5.5, "Use UnregisterCustomProjectsDelegate instead.")`
- L77 _public prototype_ `virtual bool UsesCustomProjectDir() const override;` — `UE_DEPRECATED(5.5, "Use !GetCustomProjects().IsEmpty() instead.")`
- L79 _public prototype_ `virtual FSourceControlFileStatusMonitor& GetSourceControlFileStatusMonitor() override;`
- L82 _public prototype_ `void SaveSettings();` — Save the settings to the ini file
- L87 _public prototype_ `int32 GetNumSourceControlProviders();` — Get the number of currently registered source control providers.
- L92 _public prototype_ `void SetCurrentSourceControlProvider(int32 ProviderIndex);` — Set the current source control provider by index.
- L97 _public prototype_ `FName GetSourceControlProviderName(int32 ProviderIndex);` — Get the name of the source control provider at the specified index.
- L102 _public prototype_ `TSharedPtr<class SSourceControlLogin> GetLoginWidget() const;` — Get the one and only login widget, if any.
- L109 _public function_ `static FSourceControlModule& Get()` — Gets a reference to the source control module instance. @return A reference to the source control module.
- L116 _private prototype_ `void InitializeSourceControlProviders();` — Refresh & initialize the current source control provider
- L119 _private prototype_ `void ClearCurrentSourceControlProvider();` — Close the current source control provider & set the current to default - 'None'
- L122 _private prototype_ `void SetCurrentSourceControlProvider(ISourceControlProvider& InProvider);` — Set the current source control provider to the passed-in value
- L125 _private prototype_ `void OnSourceControlDialogClosed(const TSharedRef<class SWindow>& InWindow);` — Delegate called when the source control window is closed
- L128 _private prototype_ `void HandleModularFeatureRegistered(const FName& Type, IModularFeature* ModularFeature);` — Delegate handling when source control features are registered
- L131 _private prototype_ `void HandleModularFeatureUnregistered(const FName& Type, IModularFeature* ModularFeature);` — Delegate handling when source control features are unregistered
- L135 _private prototype_ `void OnAssetsCanDelete(const TArray<UObject*>& InObjects, FCanDeleteAssetResult& OutCanDeleteAssetResult) const;` — Delegate called when trying to delete asset(s) to verify that it is allowed by the SourceControl
- L139 _private member_ `FSourceControlSettings SourceControlSettings;` — The settings object
- L142 _private member_ `ISourceControlProvider* CurrentSourceControlProvider;` — Current source control provider
- L145 _private member_ `FDefaultSourceControlProvider DefaultSourceControlProvider;` — Source control provider we use if there are none registered
- L148 _private member_ `TSharedPtr<SWindow> SourceControlLoginWindowPtr;` — The login window we may be using
- L151 _private member_ `TSharedPtr<class SSourceControlLogin> SourceControlLoginPtr;` — The login window control we may be using
- L154 _private member_ `TSharedPtr<class FSourceControlFileStatusMonitor> SourceControlFileStatusMonitor;` — Monitor the source control status of a collection of files.
- L157 _private member_ `TArray<FString> PendingStatusUpdateFiles;` — Files pending a status update
- L160 _private member_ `FDateTime PendingStatusUpdateQueuedTime;` — Time last status update got queued
- L163 _private member_ `uint8 TemporarilyDisabledCount;` — Flag to disable source control - used temporarily when login is in progress
- L166 _private member_ `FString ActiveProviderName;` — Active Provider name to track source control provider changes
- L169 _private member_ `FSourceControlProviderChanging OnSourceControlProviderChanging;` — For notifying when the source provider is about to change
- L172 _private member_ `FSourceControlProviderChanged OnSourceControlProviderChanged;` — For notifying when the source provider is changed
- L175 _private member_ `FSourceControlPreSubmitChangelistValidationExDelegate OnSourceControlPreSubmitChangelistValidation;` — To call when doing pre-submit changelist validation
- L178 _private member_ `FSourceControlPreSubmitFilesValidationExDelegate OnSourceControlPreSubmitFilesValidation;` — To call when doing pre-submit files validation
- L181 _private member_ `FSourceControlPreSubmitFinalizeDelegate OnPresubmitFinalize;` — To be called right before files are submitted, allowing for additional last minute validation. @see FSourceControlPreSubmitFinalizeDelegate
- L184 _private member_ `FSourceControlFilesDeletedDelegate OnFilesDeleted;` — To be called after a source control operations deleted files
- L187 _private member_ `FSourceControlAssetDataCache AssetDataCache;` — Used to cache source controlled AssetData information
- L190 _private member_ `FSourceControlProjectDirDelegate SourceControlProjectDirDelegate;` — `UE_DEPRECATED(5.5, "Use CustomProjectsDelegate instead.")`
- L193 _private member_ `FSourceControlCustomProjectsDelegate CustomProjectsDelegate;` — Delegate used to return information on custom projects under source control
- L194 _private member_ `FSimpleMulticastDelegate CustomProjectsChangedDelegate;`

### `Source/Developer/SourceControl/Private/SourceControlPrivate.h` (Private)
_(no declarations extracted)_

### `Source/Developer/SourceControl/Private/SourceControlSettings.h` (Private)


#### class `FSourceControlSettings`  
`class FSourceControlSettings`  
_L7-39_
- L10 _public function_ `FSourceControlSettings() : bUseGlobalSettings(false)`
- L16 _public prototype_ `const FString& GetProvider() const;` — Get the provider we want to use
- L19 _public prototype_ `void SetProvider(const FString& InString);` — Set the provider we want to use
- L22 _public prototype_ `bool GetUseGlobalSettings() const;` — Get whether we should use global or per-project settings
- L25 _public prototype_ `void SetUseGlobalSettings(bool bInUseGlobalSettings);` — Set whether we should use global or per-project settings
- L28 _public prototype_ `void LoadSettings();` — Load settings from ini file
- L31 _public prototype_ `void SaveSettings() const;` — Save settings to ini file
- L35 _private member_ `FString Provider;` — The preferred source control provider
- L38 _private member_ `bool bUseGlobalSettings;` — Whether we should use global or per-project settings

### `Source/Developer/SourceControl/Public/ISourceControlChangelist.h` (Public)


#### class `ISourceControlChangelist`  
`class ISourceControlChangelist : public TSharedFromThis<ISourceControlChangelist, ESPMode::ThreadSafe>`  
_L15-38_
- inherits: `TSharedFromThis<ISourceControlChangelist,ESPMode::ThreadSafe>`
- desc: An abstraction of a changelist under source control
- L21 _public prototype_ `virtual ~ISourceControlChangelist() = default;` — Virtual destructor
- L27 _public function_ `virtual bool CanDelete() const` — Returns true if the changelist is deletable. Some special changelist might not be deletable like the default Perforce changelist.
- L32 _public function_ `virtual FString GetIdentifier() const` — Get source control specific identifier for this changelist, for example CL number in Perforce.
- L37 _public function_ `virtual bool IsDefault() const` — Returns true if this changelist is a default changelist.

#### Free symbols / members of external scopes

- L9 _typedef_ `typedef TSharedRef<class ISourceControlChangelist, ESPMode::ThreadSafe> FSourceControlChangelistRef;`
- L10 _typedef_ `typedef TSharedPtr<class ISourceControlChangelist, ESPMode::ThreadSafe> FSourceControlChangelistPtr;`

### `Source/Developer/SourceControl/Public/ISourceControlChangelistState.h` (Public)


#### class `ISourceControlChangelistState`  
`class ISourceControlChangelistState : public TSharedFromThis<ISourceControlChangelistState, ESPMode::ThreadSafe>`  
_L16-78_
- inherits: `TSharedFromThis<ISourceControlChangelistState,ESPMode::ThreadSafe>`
- desc: An abstraction of the state of a pending changelist under source control
- L22 _public prototype_ `virtual ~ISourceControlChangelistState() = default;` — Virtual destructor
- L28 _public prototype_ `virtual FName GetIconName() const = 0;` — Get the name of the icon graphic we should use to display the state in a UI. @returns the name of the icon to display
- L34 _public prototype_ `virtual FName GetSmallIconName() const = 0;` — Get the name of the small icon graphic we should use to display the state in a UI. @returns the name of the icon to display
- L40 _public prototype_ `virtual FText GetDisplayText() const = 0;` — Get a text representation of the state @returns	the text to display for this state
- L46 _public prototype_ `virtual FText GetDescriptionText() const = 0;` — Get a text representation of the state @returns	the text to display for this state
- L53 _public function_ `virtual bool SupportsPersistentDescription() const` — Returns whether the change list description can be saved and persisted. Some changelists are special and the description cannot be persisted with the changelist. For example the P4 default changelist description cannot be persisted and the user must create a new changelist.
- L59 _public prototype_ `virtual FText GetDisplayTooltip() const = 0;` — Get a tooltip to describe this state @returns	the text to display for this states tooltip
- L65 _public prototype_ `virtual const FDateTime& GetTimeStamp() const = 0;` — Get the timestamp of the last update that was made to this state. @returns	the timestamp of the last update
- L67 _public prototype_ `virtual const TArray<FSourceControlStateRef> GetFilesStates() const = 0;`
- L68 _public prototype_ `virtual int32 GetFilesStatesNum() const = 0;`
- L70 _public prototype_ `virtual const TArray<FSourceControlStateRef> GetShelvedFilesStates() const = 0;`
- L71 _public prototype_ `virtual int32 GetShelvedFilesStatesNum() const = 0;`
- L77 _public prototype_ `virtual FSourceControlChangelistRef GetChangelist() const = 0;` — Returns the object on which this state was constructed @returns the changelist associated to this state

#### Free symbols / members of external scopes

- L10 _typedef_ `typedef TSharedRef<class ISourceControlChangelistState, ESPMode::ThreadSafe> FSourceControlChangelistStateRef;`
- L11 _typedef_ `typedef TSharedPtr<class ISourceControlChangelistState, ESPMode::ThreadSafe> FSourceControlChangelistStatePtr;`

### `Source/Developer/SourceControl/Public/ISourceControlLabel.h` (Public)


#### class `ISourceControlLabel`  
`class ISourceControlLabel : public TSharedFromThis<ISourceControlLabel>`  
_L10-59_
- inherits: `TSharedFromThis<ISourceControlLabel>`
- desc: Abstraction of a source control label/tag.
- L17 _public prototype_ `virtual ~ISourceControlLabel() = default;` — Virtual destructor
- L22 _public prototype_ `virtual const FString& GetName() const = 0;` — Get the name of this label
- L29 _public function_ `virtual bool GetFileRevisions( const FString& InFile, TArray< TSharedRef<class ISourceControlRevision, ESPMode::ThreadSafe> >& OutRevisions ) const` — Get a list of file revisions at this label. @param	InFile			The file/directory to get @param	OutRevisions	The revisions retrieved by the operation
- L41 _public prototype_ `virtual bool GetFileRevisions( const TArray<FString>& InFiles, TArray< TSharedRef<class ISourceControlRevision, ESPMode::ThreadSafe> >& OutRevisions ) const = 0;` — Get a list of file revisions at this label. @param	InFiles			The files/directories to get @param	OutRevisions	The revisions retrieved by the operation
- L47 _public function_ `virtual bool Sync( const FString& InFilename ) const` — Sync a path/filename to this label @param	InFilename	The path or filename to sync
- L58 _public prototype_ `virtual bool Sync( const TArray<FString>& InFilenames ) const = 0;` — Sync a list of paths/filenames to this label @param	InFilenames	The paths or filenames to sync

### `Source/Developer/SourceControl/Public/ISourceControlModule.h` (Public)


#### struct `FSourceControlProjectInfo`  
`struct FSourceControlProjectInfo`  
_L23-48_
- desc: Describes a custom project that is under source control
- L25 _public function_ `FSourceControlProjectInfo()`
- L28 _public function_ `FSourceControlProjectInfo(FString InProjectDirectory) : ProjectDirectory(MoveTemp(InProjectDirectory))`
- L44 _public member_ `FString ProjectDirectory;` — Directory that contains project files
- L47 _public member_ `TArray<FString> ContentDirectories;` — Content directories that contain asset files

#### struct `FSourceControlValidationDelegateResult`  
`struct FSourceControlValidationDelegateResult`  
_L67-77_
- desc: Structure to hold result of pre-submit data validation.
- L70 _public member_ `EDataValidationResult Result = EDataValidationResult::NotValidated;` — Validation result.
- L72 _public member_ `TArray<FText> Errors;` — Error messages output during validation.
- L74 _public member_ `TArray<FText> Warnings;` — Warning messages output during validation.
- L76 _public member_ `TArray<FText> AllMessages;` — All messages (including error and warnings output during validation.

#### enum `ELoginWindowMode::Type`  
`enum Type`  
_L112-116_
- L114 _public enumerator_ `Modal`
- L115 _public enumerator_ `Modeless`

#### enum `EOnLoginWindowStartup::Type`  
`enum Type`  
_L125-129_
- L127 _public enumerator_ `ResetProviderToNone`
- L128 _public enumerator_ `PreserveProvider`

#### struct `FScopedDisableSourceControl`  
`struct FScopedDisableSourceControl`  
_L138-148_
- desc: Temporarily disable source control for the lifetime of this scoped object @note While this is on scope, ISourceControlModule::IsEnabled() will return false, but ISourceControlModule::GetProvider() will still return the current provider
- L141 _public prototype_ `explicit FScopedDisableSourceControl(const bool InDisable = true);`
- L142 _public prototype_ `~FScopedDisableSourceControl();`
- L147 _private member_ `bool bDisabled;`

#### class `ISourceControlModule`  
`class ISourceControlModule : public IModuleInterface`  
_L153-410_
- inherits: `IModuleInterface`
- desc: Interface for talking to source control providers
- L160 _public prototype_ `virtual void GetProviderNames(TArray<FName>& OutProviderNames) = 0;` — Returns a list of the registered source control providers
- L166 _public prototype_ `virtual void Tick() = 0;` — Tick the source control module. This is responsible for dispatching batched/queued status requests & for calling ISourceControlProvider::Tick()
- L172 _public prototype_ `virtual void QueueStatusUpdate(const TArray<UPackage*>& InPackages) = 0;` — Queues a file to have its source control status updated in the background. @param	InPackages	The packages to queue.
- L178 _public prototype_ `virtual void QueueStatusUpdate(const TArray<FString>& InFilenames) = 0;` — Queues a file to have its source control status updated in the background. @param	InFilenames	The files to queue.
- L184 _public prototype_ `virtual void QueueStatusUpdate(UPackage* InPackage) = 0;` — Queues a file to have its source control status updated in the background. @param	InPackage	The package to queue.
- L190 _public prototype_ `virtual void QueueStatusUpdate(const FString& InFilename) = 0;` — Queues a file to have its source control status updated in the background. @param	InFilename	The file to queue.
- L195 _public prototype_ `virtual bool IsEnabled() const = 0;` — Check whether source control is enabled.	Specifically, it returns true if a source control provider is set (regardless of whether the provider is available) and false if no provider is set.
- L200 _public prototype_ `virtual ISourceControlProvider& GetProvider() const = 0;` — Get the source control provider that is currently in use.
- L219 _public prototype_ `virtual TUniquePtr<ISourceControlProvider> CreateProvider(const FName& Name, const FStringView& OwningSystem, const FSourceControlInitSettings& InitialSettings) const = 0;` — Creates and returns a unique source control provider that will be owned by the caller. This allows subsystems to own their own source control connection in addition to the general connection used by the rest of the process. This could be to avoid the user changing settings that the subsystem needs, or so that it can open a connection with an entirely different source control type if required. @param	Name			The name of the type of provider to create. @param	OwningSystem	The name of the system that will own the provider. This is used to customize things, like the config section that that providers settings will be saved to etc. @return	A pointer to the newly created provider, this can be null if creating the name is invalid or if the provider type does not support unique connection creation.
- L224 _public prototype_ `virtual FSourceControlAssetDataCache& GetAssetDataCache() = 0;` — Get the source control AssetData information cache.
- L231 _public prototype_ `virtual void SetProvider( const FName& InName ) = 0;` — Set the current source control provider to the one specified here by name. This will assert if the provider does not exist. @param	InName	The name of the provider
- L239 _public prototype_ `virtual void ShowLoginDialog(const FSourceControlLoginClosed& InOnSourceControlLoginClosed, ELoginWindowMode::Type InLoginWindowMode, EOnLoginWindowStartup::Type InOnLoginWindowStartup = EOnLoginWindowStartup::ResetProviderToNone) = 0;` — Show the source control login dialog @param	InOnWindowClosed		Delegate to be called when the login window is closed. @param	InLoginWindowMode		Whether the dialog should be presented modally or not. Note that this function blocks if the modality is Modal. @param	InOnLoginWindowStartup	Whether the provider should be set to 'None' on dialog startup
- L245 _public prototype_ `virtual bool GetUseGlobalSettings() const = 0;` — Get whether we should use global or per-project settings @return true if we should use global settings
- L251 _public prototype_ `virtual void SetUseGlobalSettings(bool bIsUseGlobalSettings) = 0;` — Set whether we should use global or per-project settings @param bIsUseGlobalSettings	Whether we should use global settings
- L256 _public prototype_ `virtual FSourceControlProviderChanging& GetSourceControlProviderChanging() = 0;` — Retrieve a reference to a delegate to be called before the source control provider changes
- L261 _public prototype_ `virtual FDelegateHandle RegisterProviderChanged(const FSourceControlProviderChanged::FDelegate& SourceControlProviderChanged) = 0;` — Register a delegate to be called when the source control provider changes
- L266 _public prototype_ `virtual void UnregisterProviderChanged(FDelegateHandle Handle) = 0;` — Unregister a delegate to be called when the source control provider changes
- L270 _public function_ `virtual void RegisterPreSubmitDataValidation(const FSourceControlPreSubmitDataValidationDelegate& PreSubmitDataValidationDelegate) final` — `UE_DEPRECATED(5.7, "Use RegisterPreSubmitChangelistValidationEx instead.")` — Deprecating pure virtuals using final keyword to catch derived implementations.
- L272 _public function_ `virtual void RegisterPreSubmitChangelistValidation(const FSourceControlPreSubmitChangelistValidationDelegate& PreSubmitChangelistValidationDelegate) final` — `UE_DEPRECATED(5.8, "Use RegisterPreSubmitChangelistValidationEx instead.")`
- L274 _public function_ `virtual void RegisterPreSubmitFilesValidation(const FSourceControlPreSubmitFilesValidationDelegate& PreSubmitFilesValidationDelegate) final` — `UE_DEPRECATED(5.8, "Use RegisterPreSubmitFilesValidationEx instead.")`
- L276 _public function_ `virtual void UnregisterPreSubmitDataValidation() final` — `UE_DEPRECATED(5.7, "Use UnregisterPreSubmitChangelistValidation instead.")`
- L278 _public function_ `virtual FSourceControlPreSubmitDataValidationDelegate GetRegisteredPreSubmitDataValidation() final` — `UE_DEPRECATED(5.7, "Use GetRegisteredPreSubmitChangelistValidation instead.")`
- L280 _public function_ `virtual FSourceControlPreSubmitChangelistValidationDelegate GetRegisteredPreSubmitChangelistValidation() final` — `UE_DEPRECATED(5.8, "Use GetRegisteredPreSubmitChangelistValidationEx instead.")`
- L282 _public function_ `virtual FSourceControlPreSubmitFilesValidationDelegate GetRegisteredPreSubmitFilesValidation() final` — `UE_DEPRECATED(5.8, "Use GetRegisteredPreSubmitFilesValidationEx instead.")`
- L287 _public prototype_ `virtual void RegisterPreSubmitChangelistValidationEx(const FSourceControlPreSubmitChangelistValidationExDelegate& PreSubmitChangelistValidationDelegate) = 0;` — Register a delegate to be called to validate asset changes by changelist before submitting changes
- L292 _public prototype_ `virtual void UnregisterPreSubmitChangelistValidation() = 0;` — Unregister a delegate called before submitting changes
- L297 _public prototype_ `virtual FSourceControlPreSubmitChangelistValidationExDelegate GetRegisteredPreSubmitChangelistValidationEx() = 0;` — Gets currently registered delegates for pre-submit changelist validation
- L302 _public prototype_ `virtual void RegisterPreSubmitFilesValidationEx(const FSourceControlPreSubmitFilesValidationExDelegate& PreSubmitFilesValidationDelegate) = 0;` — Register a delegate to be called to validate asset changes by files before submitting changes
- L307 _public prototype_ `virtual void UnregisterPreSubmitFilesValidation() = 0;` — Unregister a delegate called before submitting changes
- L312 _public prototype_ `virtual FSourceControlPreSubmitFilesValidationExDelegate GetRegisteredPreSubmitFilesValidationEx() = 0;` — Gets currently registered delegates for pre-submit files validation
- L318 _public prototype_ `virtual FDelegateHandle RegisterPreSubmitFinalize(const FSourceControlPreSubmitFinalizeDelegate::FDelegate& Delegate) = 0;` — `UE_DEPRECATED(5.1, "ISourceControlModule::RegisterPreSubmitFinalize is deprecated, the functionality will be removed")` — Register a delegate that is invokes right before files are submitted to source control. @see FSourceControlPreSubmitFinalizeDelegate
- L324 _public prototype_ `virtual void UnregisterPreSubmitFinalize(FDelegateHandle Handle) = 0;` — `UE_DEPRECATED(5.1, "ISourceControlModule::UnregisterPreSubmitFinalize is deprecated, the functionality will be removed")` — Unregister a previously registered delegate. @see FSourceControlPreSubmitFinalizeDelegate
- L330 _public prototype_ `virtual const FSourceControlPreSubmitFinalizeDelegate& GetOnPreSubmitFinalize() const = 0;` — `UE_DEPRECATED(5.1, "ISourceControlModule::GetOnPreSubmitFinalize is deprecated, the functionality will be removed")` — Returns access to the delegate so that it can be broadcast as needed. @see FSourceControlPreSubmitFinalizeDelegate
- L335 _public prototype_ `virtual FDelegateHandle RegisterFilesDeleted(const FSourceControlFilesDeletedDelegate::FDelegate& InDelegate) = 0;` — Registers a delegate that is invoked after source control operation deleted files.  @see FSourceControlFilesDeletedDelegate
- L340 _public prototype_ `virtual void UnregisterFilesDeleted(FDelegateHandle InHandle) = 0;` — Unregister a previously registered delegate. @see FSourceControlFilesDeletedDelegate
- L345 _public prototype_ `virtual const FSourceControlFilesDeletedDelegate& GetOnFilesDeleted() const = 0;` — Returns access to the delegate so that it can be broadcast as needed. @see FSourceControlFilesDeletedDelegate
- L350 _public prototype_ `virtual void RegisterCustomProjectsDelegate(FSourceControlCustomProjectsDelegate InCustomProjectsDelegate) = 0;` — Register a delegate that returns information on custom projects under source control
- L355 _public prototype_ `virtual void UnregisterCustomProjectsDelegate() = 0;` — Unregister the FSourceControlCustomProjectsDelegate delegate
- L361 _public prototype_ `virtual TArray<FSourceControlProjectInfo> GetCustomProjects() const = 0;` — Return information on custom projects under source control @note The first entry is considered to be the main project
- L368 _public prototype_ `virtual FSimpleMulticastDelegate& OnCustomProjectsChanged() = 0;` — Delegate called whenever the list of projects that GetCustomProjects returns has changed. @note It is called automatically for RegisterCustomProjectsDelegate and UnregisterCustomProjectsDelegate, but outside of that it is the responsibility of the code that registered FSourceControlCustomProjectsDelegate to handle change notifications.
- L373 _public prototype_ `virtual FString GetSourceControlProjectDir() const = 0;` — Return the main custom project under source control or the uproject dir (FPaths::ProjectDir) if there's no custom project
- L376 _public prototype_ `virtual void RegisterSourceControlProjectDirDelegate(const FSourceControlProjectDirDelegate& SourceControlProjectDirDelegate) = 0;` — `UE_DEPRECATED(5.5, "Use RegisterCustomProjectsDelegate instead.")`
- L379 _public prototype_ `virtual void UnregisterSourceControlProjectDirDelegate() = 0;` — `UE_DEPRECATED(5.5, "Use UnregisterCustomProjectsDelegate instead.")`
- L382 _public prototype_ `virtual bool UsesCustomProjectDir() const = 0;` — `UE_DEPRECATED(5.5, "Use !GetCustomProjects().IsEmpty() instead.")`
- L387 _public prototype_ `virtual FSourceControlFileStatusMonitor& GetSourceControlFileStatusMonitor() = 0;` — Returns the object used to monitor the source control status of a collection of files.
- L394 _public function_ `static inline ISourceControlModule& Get()` — Gets a reference to the source control module instance. @return A reference to the source control module.
- L405 _public function_ `static inline ISourceControlModule* GetPtr()` — Gets a pointer to the source control module instance, if loaded. @return A pointer to the source control module, or null if not loaded.

#### Free symbols / members of external scopes

- L17 _typedef_ `typedef TSharedPtr<class ISourceControlChangelist, ESPMode::ThreadSafe> FSourceControlChangelistPtr;`
- L18 _typedef_ `typedef TSharedRef<class ISourceControlState, ESPMode::ThreadSafe> FSourceControlStateRef;`
- L32 _function_ `friend bool operator==(const FSourceControlProjectInfo& A, const FSourceControlProjectInfo& B)`
- L38 _function_ `friend bool operator!=(const FSourceControlProjectInfo& A, const FSourceControlProjectInfo& B)`
- L50 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSourceControl, Log, All);`
- L53 _delegate_ `DECLARE_DELEGATE_OneParam( FSourceControlLoginClosed, bool );` — Delegate called when the source control login window is closed. Parameter determines if source control is enabled or not
- L53 _prototype_ `DECLARE_DELEGATE_OneParam( FSourceControlLoginClosed, bool );` — Delegate called when the source control login window is closed. Parameter determines if source control is enabled or not
- L56 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FSourceControlProviderChanging);` — Delegate called when the active source control provider is changing. Returns false if the operation is to be aborted
- L56 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FSourceControlProviderChanging);` — Delegate called when the active source control provider is changing. Returns false if the operation is to be aborted
- L59 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams( FSourceControlProviderChanged, ISourceControlProvider& , ISourceControlProvider& );` — Delegate called when the active source control provider is changed
- L59 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams( FSourceControlProviderChanged, ISourceControlProvider& , ISourceControlProvider& );` — Delegate called when the active source control provider is changed
- L62 _delegate_ `DECLARE_DELEGATE_FourParams(FSourceControlPreSubmitDataValidationDelegate, FSourceControlChangelistPtr , EDataValidationResult& , TArray<FText>& , TArray<FText>& );` — Deprecated delegates called on pre-submit for data validation
- L62 _prototype_ `DECLARE_DELEGATE_FourParams(FSourceControlPreSubmitDataValidationDelegate, FSourceControlChangelistPtr , EDataValidationResult& , TArray<FText>& , TArray<FText>& );` — Deprecated delegates called on pre-submit for data validation
- L63 _delegate_ `DECLARE_DELEGATE_FourParams(FSourceControlPreSubmitChangelistValidationDelegate, FSourceControlChangelistPtr , EDataValidationResult& , TArray<FText>& , TArray<FText>& );`
- L63 _prototype_ `DECLARE_DELEGATE_FourParams(FSourceControlPreSubmitChangelistValidationDelegate, FSourceControlChangelistPtr , EDataValidationResult& , TArray<FText>& , TArray<FText>& );`
- L64 _delegate_ `DECLARE_DELEGATE_FourParams(FSourceControlPreSubmitFilesValidationDelegate, TArray<FSourceControlStateRef>& , EDataValidationResult& , TArray<FText>& , TArray<FText>& );`
- L64 _prototype_ `DECLARE_DELEGATE_FourParams(FSourceControlPreSubmitFilesValidationDelegate, TArray<FSourceControlStateRef>& , EDataValidationResult& , TArray<FText>& , TArray<FText>& );`
- L80 _delegate_ `DECLARE_DELEGATE_TwoParams(FSourceControlPreSubmitChangelistValidationExDelegate, FSourceControlChangelistPtr , FSourceControlValidationDelegateResult& );` — Delegates called on pre-submit for data validation.
- L80 _prototype_ `DECLARE_DELEGATE_TwoParams(FSourceControlPreSubmitChangelistValidationExDelegate, FSourceControlChangelistPtr , FSourceControlValidationDelegateResult& );` — Delegates called on pre-submit for data validation.
- L81 _delegate_ `DECLARE_DELEGATE_TwoParams(FSourceControlPreSubmitFilesValidationExDelegate, TArray<FSourceControlStateRef>& , FSourceControlValidationDelegateResult& );`
- L81 _prototype_ `DECLARE_DELEGATE_TwoParams(FSourceControlPreSubmitFilesValidationExDelegate, TArray<FSourceControlStateRef>& , FSourceControlValidationDelegateResult& );`
- L84 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<FSourceControlProjectInfo>, FSourceControlCustomProjectsDelegate);` — Delegate that returns directory information on custom projects under source control (first entry is the main project)
- L84 _prototype_ `DECLARE_DELEGATE_RetVal(TArray<FSourceControlProjectInfo>, FSourceControlCustomProjectsDelegate);` — Delegate that returns directory information on custom projects under source control (first entry is the main project)
- L87 _delegate_ `DECLARE_DELEGATE_RetVal(FString, FSourceControlProjectDirDelegate);` — Delegate used to specify the project base directory to be used by the source control
- L87 _prototype_ `DECLARE_DELEGATE_RetVal(FString, FSourceControlProjectDirDelegate);` — Delegate used to specify the project base directory to be used by the source control
- L98 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FSourceControlPreSubmitFinalizeDelegate, const TArray<FString>& , TArray<FText>& , TArray<FText>& );` — Delegate called once the user has confirmed that they want to submit files to source control BUT before the files are actually submitted. It is intended for last minute checks that can only run once there is no chance of the user canceling the actual submit. At this point the only way to prevent the files from being submitted is for this delegate to return errors. @param FilesToSubmit			The absolute file paths of the files being submitted @param OutDescriptionTags	Lines of text to be appending to the submit description @param OutErrors				Errors encountered while the delegate is invoked. If the array contains entries then files will not be submitted and the user given the errors instead
- L98 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FSourceControlPreSubmitFinalizeDelegate, const TArray<FString>& , TArray<FText>& , TArray<FText>& );` — Delegate called once the user has confirmed that they want to submit files to source control BUT before the files are actually submitted. It is intended for last minute checks that can only run once there is no chance of the user canceling the actual submit. At this point the only way to prevent the files from being submitted is for this delegate to return errors. @param FilesToSubmit			The absolute file paths of the files being submitted @param OutDescriptionTags	Lines of text to be appending to the submit description @param OutErrors				Errors encountered while the delegate is invoked. If the array contains entries then files will not be submitted and the user given the errors instead
- L105 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSourceControlFilesDeletedDelegate, const TArray<FString>& );` — Delegate called after source control operations deleted files. @param DeletedFiles			The absolute file paths of the deleted files
- L105 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSourceControlFilesDeletedDelegate, const TArray<FString>& );` — Delegate called after source control operations deleted files. @param DeletedFiles			The absolute file paths of the deleted files
- L110 _namespace_ `namespace ELoginWindowMode`
- L123 _namespace_ `namespace EOnLoginWindowStartup`

### `Source/Developer/SourceControl/Public/ISourceControlOperation.h` (Public)


#### class `ISourceControlOperation`  
`class ISourceControlOperation : public TSharedFromThis<ISourceControlOperation, ESPMode::ThreadSafe>`  
_L8-92_
- inherits: `TSharedFromThis<ISourceControlOperation,ESPMode::ThreadSafe>`
- L14 _public prototype_ `virtual ~ISourceControlOperation() = default;` — Virtual destructor
- L17 _public prototype_ `virtual FName GetName() const = 0;` — Get the name of this operation, used as a unique identifier
- L20 _public function_ `virtual FText GetInProgressString() const` — Get the string to display when this operation is in progress
- L26 _public function_ `virtual const FSourceControlResultInfo& GetResultInfo() const` — Retrieve any info or error messages that may have accumulated during the operation.
- L34 _public function_ `virtual void AddInfoMessge(const FText& InInfo)` — Add info/warning message.
- L40 _public function_ `virtual void AddErrorMessge(const FText& InError)` — Add error message.
- L46 _public function_ `virtual void AddTag(const FString& InTag)` — Add tag.
- L55 _public function_ `virtual void AppendResultInfo(const FSourceControlResultInfo& InResultInfo)` — Append any info or error messages that may have accumulated during the operation prior to returning a result, ensuring to keep any already accumulated info.
- L65 _public function_ `virtual bool CanBeCalledFromBackgroundThreads() const` — This will return true if the operation can be safely called from a background thread. Currently it is assumed to only the operation 'FDownloadFile' will return true at least until the API is made thread safe.
- L73 _public function_ `virtual bool ShouldLogErrors() const` — Returns true when the operation is allowed to log errors immediately when they are encountered.
- L81 _public function_ `virtual bool ShouldLogInfos() const` — Returns true when the operation is allowed to log info messages immediately when they are encountered.
- L88 _public function_ `template<typename Type, typename... TArgs> static TSharedRef<Type, ESPMode::ThreadSafe> Create(TArgs&&... Args)` — Factory method for easier operation creation

#### Free symbols / members of external scopes

- L94 _typedef_ `typedef TSharedRef<class ISourceControlOperation, ESPMode::ThreadSafe> FSourceControlOperationRef;`

### `Source/Developer/SourceControl/Public/ISourceControlProvider.h` (Public)


#### enum `EConcurrency::Type`  
`enum Type`  
_L37-43_
- L40 _public enumerator_ `Synchronous` — Force the operation to be issued on the same thread, blocking until complete.
- L42 _public enumerator_ `Asynchronous` — Run the command on another thread, returning immediately.

#### enum `EStateCacheUsage::Type`  
`enum Type`  
_L51-57_
- L54 _public enumerator_ `ForceUpdate` — Force a synchronous update of the state of the file.
- L56 _public enumerator_ `Use` — Use the cached state if possible

#### enum `ECommandResult::Type`  
`enum Type`  
_L65-73_
- L68 _public enumerator_ `Failed` — Command failed to execute correctly or was not supported by the provider.
- L70 _public enumerator_ `Succeeded` — Command executed successfully
- L72 _public enumerator_ `Cancelled` — Command was canceled before completion

#### class `ISourceControlProvider`  
`class ISourceControlProvider : public IModularFeature`  
_L88-505_
- inherits: `IModularFeature`
- desc: Interface to talking with source control providers.
- L160 _public prototype_ `virtual ~ISourceControlProvider() = default;` — Virtual destructor
- L166 _public prototype_ `virtual void Init(bool bForceConnection = true) = 0;` — Initialize source control provider. @param	bForceConnection	If set, this flag forces the provider to attempt a connection to its server.
- L174 _public prototype_ `virtual FInitResult Init(EInitFlags Flags);` — Initialize source control provider. @param Flags		Used to specialize initialization behavior, @see EInitFlags @return			A structure containing the result as well as any errors. @see FInitResult
- L179 _public prototype_ `virtual void Close() = 0;` — Shut down source control provider.
- L182 _public prototype_ `virtual const FName& GetName() const = 0;` — Get the source control provider name
- L185 _public prototype_ `virtual FText GetStatusText() const = 0;` — Get the source control status as plain, human-readable text
- L188 _public prototype_ `virtual TMap<EStatus, FString> GetStatus() const = 0;` — Get the source control status as a series of key value pairs
- L191 _public prototype_ `virtual bool IsEnabled() const = 0;` — Quick check if source control is enabled. Specifically, it returns true if a source control provider is set (regardless of whether the provider is available) and false if no provider is set. So all providers except the stub defaultSourceProvider will return true.
- L199 _public prototype_ `virtual bool IsAvailable() const = 0;` — Quick check if source control is available for use (server-based providers can use this to return whether the server is available or not) @return	true if source control is available, false if it is not
- L209 _public prototype_ `virtual ECommandResult::Type Login( const FString& InPassword = FString(), EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() );` — Login to the source control server (if any). This is just a wrapper around Execute(). @param	InPassword						The password (if required) to use when logging in. @param	InConcurrency					How to execute the operation, blocking or asynchronously on another thread. @param	InOperationCompleteDelegate		Delegate to call when the operation is completed. This is called back internal to this call when executed on the main thread, or from Tick() when queued for asynchronous execution. If the provider is not enabled or if the command is not suported the delegate is immediately called with ECommandResult::Failed. @return the result of the operation.
- L216 _public prototype_ `virtual bool QueryStateBranchConfig(const FString& ConfigSrc, const FString& ConfigDest) = 0;` — Queries branch configuration from source control @param	ConfigSrc			The source path to the branch configuration file in source control @param	ConfigDest			The destination path to save the configuration to for parsing
- L223 _public prototype_ `virtual void RegisterStateBranches(const TArray<FString>& BranchNames, const FString& ContentRoot) = 0;` — Register branches to query for state in addition to the current branch @param	BranchNames			Names of the branches to query @param	ContentRoot			Path to the content root for branch mapping
- L230 _public prototype_ `virtual void RegisterStateBranches( const TArray<FString>& BranchNames, const TArray<FString>& ContentRoots );` — Register branches to query for state in addition to the current branch @param	BranchNames			Names of the branches to query @param	ContentRoots			Paths to the content roots for branch mapping
- L237 _public prototype_ `virtual int32 GetStateBranchIndex(const FString& BranchName) const = 0;` — Gets the state index of the specified branch, higher index branches are generally closer to releases @param	BranchName			Name of the branch to query @return	the index of the specified branch
- L245 _public prototype_ `virtual bool GetStateBranchAtIndex(int32 BranchIndex, FString& OutBranchName) const = 0;` — Gets the name of the state branch at the given index, higher index branches are generally closer to releases @param	BranchIndex			Index of the branch to retrieve @param	OutBrancheName[out] Name of the branch, if successful @return true if the branch name could be retrieved, false otherwise.
- L254 _public prototype_ `virtual ECommandResult::Type GetState( const TArray<FString>& InFiles, TArray<FSourceControlStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage ) = 0;` — Get the state of each of the passed-in files. State may be cached for faster queries. Note states can be NULL! @param	InFiles				The files to retrieve state for. @param	OutState			The states of the files. This will be empty if the operation fails. Note states can be NULL! @param	InStateCacheUsage	Whether to use the state cache or to force a (synchronous) state retrieval. @return the result of the operation.
- L259 _public prototype_ `virtual ECommandResult::Type GetState( const TArray<UPackage*>& InPackages, TArray<FSourceControlStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage );` — Helper overload for state retrieval, see GetState().
- L264 _public prototype_ `virtual FSourceControlStatePtr GetState( const FString& InFile, EStateCacheUsage::Type InStateCacheUsage );` — Helper overload for state retrieval, see GetState().
- L269 _public prototype_ `virtual FSourceControlStatePtr GetState( const UPackage* InPackage, EStateCacheUsage::Type InStateCacheUsage );` — Helper overload for state retrieval, see GetState().
- L278 _public prototype_ `virtual ECommandResult::Type GetState( const TArray<FSourceControlChangelistRef>& InChangelists, TArray<FSourceControlChangelistStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage ) = 0;` — Get the state of each of the passed-in changelists. State may be cached for faster queries. Note states can be NULL! @param	InChangelists		The changelists to retrieve state for. @param	OutState			The states of the changelists. This will be empty if the operation fails. Note states can be NULL! @param	InStateCacheUsage	Whether to use the state cache or to force a (synchronous) state retrieval. @return the result of the operation.
- L283 _public prototype_ `virtual FSourceControlChangelistStatePtr GetState( const FSourceControlChangelistRef& InChangelist, EStateCacheUsage::Type InStateCacheUsage );` — Helper overload for state retrieval, see GetState().
- L288 _public prototype_ `virtual TArray<FSourceControlStateRef> GetCachedStateByPredicate(TFunctionRef<bool(const FSourceControlStateRef&)> Predicate) const = 0;` — Get all cached source control state objects for which the supplied predicate returns true
- L293 _public prototype_ `virtual FDelegateHandle RegisterSourceControlStateChanged_Handle( const FSourceControlStateChanged::FDelegate& SourceControlStateChanged ) = 0;` — Register a delegate to be called when source control state(s) change
- L298 _public prototype_ `virtual void UnregisterSourceControlStateChanged_Handle( FDelegateHandle Handle ) = 0;` — Unregister a delegate to be called when source control state(s) change
- L309 _public prototype_ `virtual ECommandResult::Type Execute( const FSourceControlOperationRef& InOperation, FSourceControlChangelistPtr InChangelist, const TArray<FString>& InFiles, EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() ) = 0;` — Attempt to execute an operation on the passed-in files (if any are required). @param	InOperation						The operation to perform. @param	InChangelist                    The changelist to operate on, can be null. @param	InFiles							The files to operate on. @param	InConcurrency					How to execute the operation, blocking or asynchronously on another thread. @param	InOperationCompleteDelegate		Delegate to call when the operation is completed. This is called back internal to this call when executed on the main thread, or from Tick() when queued for asynchronous execution. If the provider is not enabled or if the command is not suported the delegate is immediately called with ECommandResult::Failed. @return the result of the operation.
- L314 _public prototype_ `virtual ECommandResult::Type Execute(const FSourceControlOperationRef& InOperation, const TArray<FString>& InFiles, EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete());` — Helper overload for operation execution, see Execute().
- L319 _public prototype_ `virtual ECommandResult::Type Execute( const FSourceControlOperationRef& InOperation, const EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() );` — Helper overload for operation execution, see Execute().
- L324 _public prototype_ `virtual ECommandResult::Type Execute( const FSourceControlOperationRef& InOperation, const UPackage* InPackage, const EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() );` — Helper overload for operation execution, see Execute().
- L329 _public prototype_ `virtual ECommandResult::Type Execute( const FSourceControlOperationRef& InOperation, const FString& InFile, const EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() );` — Helper overload for operation execution, see Execute().
- L334 _public prototype_ `virtual ECommandResult::Type Execute( const FSourceControlOperationRef& InOperation, const TArray<UPackage*>& InPackages, const EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() );` — Helper overload for operation execution, see Execute().
- L339 _public prototype_ `virtual ECommandResult::Type Execute( const FSourceControlOperationRef& InOperation, FSourceControlChangelistPtr InChangelist, const EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete());` — Helper overload for operation execution, see Execute().
- L346 _public prototype_ `virtual bool CanExecuteOperation( const FSourceControlOperationRef& InOperation ) const = 0;` — Check to see if we can execute an operation. @param	InOperation		The operation to check. @return true if the operation can be executed.
- L353 _public prototype_ `virtual bool CanCancelOperation( const FSourceControlOperationRef& InOperation ) const = 0;` — Check to see if we can cancel an operation. @param	InOperation		The operation to check. @return true if the operation was cancelled.
- L359 _public prototype_ `virtual void CancelOperation( const FSourceControlOperationRef& InOperation ) = 0;` — Attempt to cancel an operation in progress. @param	InOperation		The operation to attempt to cancel.
- L366 _public prototype_ `virtual TSharedPtr<class ISourceControlLabel> GetLabel( const FString& InLabelName ) const;` — Get a label matching the passed-in name. @param	InLabelName	String specifying the label name @return the label, if any
- L373 _public prototype_ `virtual TArray< TSharedRef<class ISourceControlLabel> > GetLabels( const FString& InMatchingSpec ) const = 0;` — Get an array of labels matching the passed-in spec. @param	InMatchingSpec	String specifying the label spec. @return an array of labels matching the spec.
- L380 _public prototype_ `virtual TArray<FSourceControlChangelistRef> GetChangelists(EStateCacheUsage::Type InStateCacheUsage) = 0;` — Returns the list of available changelists if the underlying source control supports the 'changelist' concept. @param InStateCacheUsage True to retrieve the list from a local cache, false to request it from the server (if any).
- L393 _public prototype_ `bool TryToDownloadFileFromBackgroundThread(const TSharedRef<class FDownloadFile>& InOperation, const FString& InFile);` — Executes the FDownloadFile operation, but unlike the ::Execute method this can be called from a background thread, this works because FDownloadFile is thread safe and it does not change the state of source control. NOTE: This is only intended for use by the virtualization module and will be deprecated at some point in the future when thread safety is built into the system. NOTE: This is only implemented for the perforce source control provider with no plans to extend this to other providers. @param InOperation The download operation to be executed. @param InFile The depot path of a file to download. @return True if the operation was a success, otherwise false.
- L406 _public prototype_ `virtual bool TryToDownloadFileFromBackgroundThread(const TSharedRef<class FDownloadFile>& InOperation, const TArray<FString>& InFiles);` — Executes the FDownloadFile operation, but unlike the ::Execute method this can be called from a background thread, this works because FDownloadFile is thread safe and it does not change the state of source control. NOTE: This is only intended for use by the virtualization module and will be deprecated at some point in the future when thread safety is built into the system. NOTE: This is only implemented for the perforce source control provider with no plans to extend this to other providers. @param InOperation The download operation to be executed. @param InFile An array of depot paths for the files to download. @return True if the operation was a success, otherwise false.
- L418 _public prototype_ `virtual ECommandResult::Type SwitchWorkspace(FStringView NewWorkspaceName, FSourceControlResultInfo& OutResultInfo, FString* OutOldWorkspaceName);` — Used to switch the provider from one workspace to another. NOTE: This concept is currently only implemented for the perforce source control provider. @param NewWorkspaceName			The name of the workspace to switch to @param ResultInfo[out]			Errors and info messages generated will be written here @param OutOldWorkspaceName[out]	The name of the previous workspace will be written to this FString if the pointer is valid (optional) @return The result of the operation.
- L423 _public prototype_ `virtual bool UsesLocalReadOnlyState() const = 0;` — Whether the provider uses local read-only state to signal whether a file is editable.
- L428 _public prototype_ `virtual bool UsesChangelists() const = 0;` — Whether the provider uses changelists to identify commits/revisions
- L433 _public prototype_ `virtual bool UsesUncontrolledChangelists() const = 0;` — Whether the provider supports uncontrolled changelists to allow work offline
- L438 _public prototype_ `virtual bool UsesCheckout() const = 0;` — Whether the provider uses the checkout workflow
- L443 _public prototype_ `virtual bool UsesFileRevisions() const = 0;` — Whether the provider uses individual file revisions
- L448 _public prototype_ `virtual bool UsesSnapshots() const = 0;` — Whether the provider uses snapshots
- L453 _public prototype_ `virtual bool UsesSoftRevertOnDelete() const = 0;` — Whether the provider uses soft revert before delete
- L458 _public prototype_ `virtual bool AllowsDiffAgainstDepot() const = 0;` — Whether the provider allow a diff between a changed file and the depot
- L463 _public prototype_ `virtual TOptional<bool> HasChangesToSync() const = 0;` — Whether there is anything to sync
- L468 _public prototype_ `virtual TOptional<bool> HasChangesToCheckIn() const = 0;` — Whether there is anything to check-in
- L471 _public function_ `virtual TOptional<bool> IsAtLatestRevision() const final` — `UE_DEPRECATED(5.8, "This function is no longer used.")`
- L474 _public function_ `virtual TOptional<int> GetNumLocalChanges() const final` — `UE_DEPRECATED(5.8, "This function is no longer used.")`
- L479 _public prototype_ `virtual void Tick() = 0;` — Called every update.
- L486 _public prototype_ `virtual TSharedRef<class SWidget> MakeSettingsWidget() const = 0;` — Create a settings widget for display in the login window. @returns a widget used to edit the providers settings required prior to connection.
- L504 _protected function_ `virtual TUniquePtr<ISourceControlProvider> Create(const FStringView& OwnerName, const FSourceControlInitSettings& InitialSettings) const` — Creates a new instance of the source control provider type. Derived providers should implement this if they can more than one provider of the same type existing. @see ISourceControlModule::CreateProvider

#### enum `ISourceControlProvider::EStatus`  
`enum class EStatus`  
_L93-109_
- desc: Key value for common source control provider statuses
- L95 _public enumerator_ `Enabled`
- L96 _public enumerator_ `Connected`
- L97 _public enumerator_ `Port`
- L98 _public enumerator_ `User`
- L99 _public enumerator_ `Client`
- L100 _public enumerator_ `Repository`
- L101 _public enumerator_ `Remote`
- L102 _public enumerator_ `Branch`
- L103 _public enumerator_ `Email`
- L104 _public enumerator_ `ScmVersion`
- L105 _public enumerator_ `PluginVersion`
- L106 _public enumerator_ `Workspace`
- L107 _public enumerator_ `WorkspacePath`
- L108 _public enumerator_ `Changeset`

#### enum `ISourceControlProvider::EInitFlags`  
`enum class EInitFlags : uint32`  
_L112-121_
- desc: Flags used when calling ISourceControlProvider::Init
- L115 _public enumerator_ `None = 0` — No flags set
- L117 _public enumerator_ `AttemptConnection = 1 << 0` — A connection attempt to the provider will be made as part of the initialization
- L119 _public enumerator_ `SuppressErrorLogging = 1 << 1` — Errors will not be logged but will still be returned to the caller
- L120 _public enumerator_ `SupressErrorLogging UE_DEPRECATED(5.8, "Spelling typo, please use ISourceControlProvider::EInitFlags::SuppressErrorLogging instead") = 1 << 1`

#### struct `ISourceControlProvider::FInitResult`  
`struct FInitResult`  
_L124-154_
- desc: The result info returned form calls to  ISourceControlProvider::Init
- L127 _public member_ `bool bIsAvailable = false;` — True if the provider is ready for use, otherwise false. This value should match calling ISourceControlProvider::IsAvailable.
- L135 _public member_ `TMap<EStatus, FString> ConnectionSettings;` — Contains the important settings used when trying to make a server connection. This will only contain entries if Init is called with the EInitFlags::AttemptConnection flag. This map should still contain entries if the connection failed.
- L153 _public member_ `} Errors;`

#### struct `ISourceControlProvider::FInitResult::FConnectionErrors`  
`struct FConnectionErrors`  
_L138-153_
- desc: Contains errors encountered during initialization
- L141 _public member_ `FText ErrorMessage;` — A higher level error message describing at what point in the connection something went wrong.
- L144 _public member_ `TArray<FText> AdditionalErrors;` — A collection of lower level error messages usually from the source revision api itself.
- L146 _public prototype_ `FConnectionErrors() = default;`
- L147 _public function_ `FConnectionErrors(const FText& InErrorMessage, const TArray<FText>& InAdditionalErrors) : ErrorMessage(InErrorMessage), AdditionalErrors(InAdditionalErrors)`
- L152 _public prototype_ `~FConnectionErrors() = default;`

#### Free symbols / members of external scopes

- L35 _namespace_ `namespace EConcurrency`
- L49 _namespace_ `namespace EStateCacheUsage`
- L63 _namespace_ `namespace ECommandResult`
- L77 _delegate_ `DECLARE_DELEGATE_TwoParams(FSourceControlOperationComplete, const FSourceControlOperationRef&, ECommandResult::Type);` — Delegate used by providers for when operations finish
- L77 _prototype_ `DECLARE_DELEGATE_TwoParams(FSourceControlOperationComplete, const FSourceControlOperationRef&, ECommandResult::Type);` — Delegate used by providers for when operations finish
- L80 _delegate_ `DECLARE_DELEGATE_RetVal(FSourceControlOperationRef, FGetSourceControlOperation);` — Delegate used by providers to create source control operations
- L80 _prototype_ `DECLARE_DELEGATE_RetVal(FSourceControlOperationRef, FGetSourceControlOperation);` — Delegate used by providers to create source control operations
- L83 _delegate_ `DECLARE_MULTICAST_DELEGATE(FSourceControlStateChanged);` — Delegate called when the state of an item (or group of items) has changed.
- L83 _prototype_ `DECLARE_MULTICAST_DELEGATE(FSourceControlStateChanged);` — Delegate called when the state of an item (or group of items) has changed.
- L507 _prototype_ `ENUM_CLASS_FLAGS(ISourceControlProvider::EInitFlags);`

### `Source/Developer/SourceControl/Public/ISourceControlRevision.h` (Public)


#### class `FAnnotationLine`  
`class FAnnotationLine`  
_L12-25_
- desc: A single line of an annotated file
- L15 _public function_ `FAnnotationLine(int32 InChangeNumber, const FString& InUserName, const FString& InLine) : ChangeNumber(InChangeNumber) , UserName(InUserName) , Line(InLine)`
- L22 _public member_ `int32 ChangeNumber;`
- L23 _public member_ `FString UserName;`
- L24 _public member_ `FString Line;`

#### class `ISourceControlRevision`  
`class ISourceControlRevision : public TSharedFromThis<ISourceControlRevision, ESPMode::ThreadSafe>`  
_L30-92_
- inherits: `TSharedFromThis<ISourceControlRevision,ESPMode::ThreadSafe>`
- desc: Abstraction of a source control revision.
- L36 _public prototype_ `virtual ~ISourceControlRevision() = default;` — Virtual destructor
- L44 _public prototype_ `virtual bool Get(FString& InOutFilename, EConcurrency::Type InConcurrency = EConcurrency::Synchronous) const = 0;` — Get this revision of the file & store it in a temp file. @param	InOutFilename		The filename that the revision will be written to. If this is empty a temp filename will be generated and returned in this string. @param	InConcurrency		The concurrency type of the get operation. Should be used when the revision is not requested from the main thread. @return true if the operation succeeded.
- L51 _public prototype_ `virtual bool GetAnnotated( TArray<FAnnotationLine>& OutLines ) const = 0;` — Get an annotated revision of the file & store it in a temp file. @param	OutLines		Array of lines representing the contents of the file. @return true if the operation succeeded.
- L58 _public prototype_ `virtual bool GetAnnotated( FString& InOutFilename ) const = 0;` — Get an annotated revision of the file & store it in a temp file. @param	InOutFilename		The filename that the revision will be written to. If this is empty a temp filename will be generated and returned in this string. @return true if the operation succeeded.
- L61 _public prototype_ `virtual const FString& GetFilename() const = 0;` — Get the local filename of this file.
- L64 _public prototype_ `virtual int32 GetRevisionNumber() const = 0;` — Number of the revision
- L67 _public prototype_ `virtual const FString& GetRevision() const = 0;` — String representation of the revision
- L70 _public prototype_ `virtual const FString& GetDescription() const = 0;` — Changelist/Commit description
- L73 _public prototype_ `virtual const FString& GetUserName() const = 0;` — User name of the submitter
- L76 _public prototype_ `virtual const FString& GetClientSpec() const = 0;` — Workspace/Clientspec of the submitter (if any)
- L79 _public prototype_ `virtual const FString& GetAction() const = 0;` — Action taken to the file this revision (branch/integrate/edit/etc.)
- L82 _public prototype_ `virtual TSharedPtr<ISourceControlRevision, ESPMode::ThreadSafe> GetBranchSource() const = 0;` — Source of branch, if any
- L85 _public prototype_ `virtual const FDateTime& GetDate() const = 0;` — Date of the revision
- L88 _public prototype_ `virtual int32 GetCheckInIdentifier() const = 0;` — Changelist number/revision number of the revision - an identifier for the check-in
- L91 _public prototype_ `virtual int32 GetFileSize() const = 0;` — File size of the revision (0 if the file was deleted)

### `Source/Developer/SourceControl/Public/ISourceControlState.h` (Public)


#### class `ISourceControlState`  
`class ISourceControlState : public TSharedFromThis<ISourceControlState, ESPMode::ThreadSafe>`  
_L25-252_
- inherits: `TSharedFromThis<ISourceControlState,ESPMode::ThreadSafe>`
- desc: An abstraction of the state of a file under source control
- L51 _public prototype_ `virtual ~ISourceControlState() = default;` — Virtual destructor
- L59 _public prototype_ `virtual int32 GetHistorySize() const = 0;` — Get the size of the history. If an FUpdateStatus operation has been called with the ShouldUpdateHistory() set, there should be history present if the file has been committed to source control. @returns the number of items in the history
- L66 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetHistoryItem( int32 HistoryIndex ) const = 0;` — Get an item from the history @param	HistoryIndex	the index of the history item @returns a history item or NULL if none exist
- L73 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> FindHistoryRevision( int32 RevisionNumber ) const = 0;` — Find an item from the history with the specified revision number. @param	RevisionNumber	the revision number to look for @returns a history item or NULL if the item could not be found
- L80 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> FindHistoryRevision( const FString& InRevision ) const = 0;` — Find an item from the history with the specified revision. @param	InRevision	the revision identifier to look for @returns a history item or NULL if the item could not be found
- L87 _public function_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetBaseRevForMerge() const final` — `UE_DEPRECATED(5.3, "Use GetResolveInfo() and FindHistoryRevision() instead")` — Get the revision that we should use as a base when performing a three way merge, does not refresh source control state @returns a revision identifier or NULL if none exist
- L93 _public function_ `virtual FResolveInfo GetResolveInfo() const` — Get the file and revision number of the base and remote assets considered in a merge resolve @returns a valid FResolveInfo if the asset is being resolved, otherwise FResolveInfo::IsValid() will return false
- L99 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetCurrentRevision() const = 0;` — Get the revision that we are currently synced to @returns a revision identifier or NULL if none exist
- L105 _public prototype_ `virtual FSlateIcon GetIcon() const = 0;` — Gets the icon we should use to display the state in a UI.
- L113 _public function_ `virtual FName GetIconName() const` — `UE_DEPRECATED(5.0, "GetIconName has been replaced by GetIcon.")` — Get the name of the icon graphic we should use to display the state in a UI. @returns the name of the icon to display
- L120 _public function_ `virtual FName GetSmallIconName() const` — `UE_DEPRECATED(5.0, "GetSmallIconName has been replaced by GetIcon.")` — Get the name of the small icon graphic we should use to display the state in a UI. @returns the name of the icon to display
- L126 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Get a text representation of the state @returns	the text to display for this state
- L132 _public prototype_ `virtual FText GetDisplayTooltip() const = 0;` — Get a tooltip to describe this state @returns	the text to display for this states tooltip
- L138 _public prototype_ `virtual const FString& GetFilename() const = 0;` — Get the local filename that this state represents @returns	the filename
- L144 _public prototype_ `virtual const FDateTime& GetTimeStamp() const = 0;` — Get the timestamp of the last update that was made to this state. @returns	the timestamp of the last update
- L147 _public prototype_ `virtual bool CanCheckIn() const = 0;` — Get whether this file can be checked in.
- L150 _public prototype_ `virtual bool CanCheckout() const = 0;` — Get whether this file can be checked out
- L153 _public prototype_ `virtual bool IsCheckedOut() const = 0;` — Get whether this file is checked out by the current user
- L156 _public prototype_ `virtual bool IsCheckedOutOther(FString* Who = NULL) const = 0;` — Get whether this file is checked out by someone else in the current branch
- L159 _public prototype_ `virtual bool IsCheckedOutInOtherBranch(const FString& CurrentBranch = FString()) const = 0;` — Get whether this file is checked out in a different branch, if no branch is specified defaults to FEngineVerion current branch
- L162 _public prototype_ `virtual bool IsModifiedInOtherBranch(const FString& CurrentBranch = FString()) const = 0;` — Get whether this file is modified in a different branch, if no branch is specified defaults to FEngineVerion current branch
- L165 _public prototype_ `virtual bool IsCheckedOutOrModifiedInOtherBranch(const FString& CurrentBranch = FString()) const = 0;` — Get whether this file is checked out or modified in a different branch, if no branch is specified defaults to FEngineVerion current branch
- L168 _public prototype_ `virtual TArray<FString> GetCheckedOutBranches() const = 0;` — Get the other branches this file is checked out in
- L171 _public prototype_ `virtual FString GetOtherUserBranchCheckedOuts() const = 0;` — Get the user info for checkouts on other branches
- L176 _public prototype_ `virtual bool GetOtherBranchHeadModification(FString& HeadBranchOut, FString& ActionOut, int32& HeadChangeListOut) const = 0;` — Get head modification information for other branches @returns true with parameters populated if there is a branch with a newer modification (edit/delete/etc)
- L178 _public prototype_ `virtual FSourceControlChangelistPtr GetCheckInIdentifier() const;`
- L181 _public prototype_ `virtual bool IsCurrent() const = 0;` — Get whether this file is up-to-date with the version in source control
- L184 _public prototype_ `virtual bool IsSourceControlled() const = 0;` — Get whether this file is under source control
- L187 _public function_ `virtual bool IsLocal() const` — Get whether this file is local to the current user (ie, has never been pushed to anyone else)
- L193 _public prototype_ `virtual bool IsAdded() const = 0;` — Get whether this file is marked for add
- L196 _public prototype_ `virtual bool IsDeleted() const = 0;` — Get whether this file is marked for delete
- L199 _public prototype_ `virtual bool IsIgnored() const = 0;` — Get whether this file is ignored by source control
- L202 _public prototype_ `virtual bool CanEdit() const = 0;` — Get whether source control allows this file to be edited
- L205 _public prototype_ `virtual bool CanDelete() const = 0;` — Get whether source control allows this file to be deleted.
- L208 _public prototype_ `virtual bool IsUnknown() const = 0;` — Get whether we know anything about this files source control state
- L211 _public prototype_ `virtual bool IsModified() const = 0;` — Get whether this file is modified compared to the version we have from source control
- L217 _public prototype_ `virtual bool CanAdd() const = 0;` — Get whether this file can be added to source control (i.e. is part of the directory structure currently under source control)
- L220 _public function_ `virtual bool IsConflicted() const` — Get whether this file is in a conflicted state
- L226 _public prototype_ `virtual bool CanRevert() const = 0;` — Get whether this file can be reverted, i.e. its changes are discarded and the file will no longer be checked-out.
- L229 _public function_ `virtual TOptional<FText> GetWarningText() const` — Gets the warnings messages associated with this state, if any. Ex 'checkout by other', 'out of date', etc).
- L243 _public function_ `virtual TOptional<FText> GetStatusText() const` — Gets the status message associated with this state, if any. This is a superset of the GetWarningText that also includes IsCheckedOut.
- L254 _function_ `inline FSourceControlChangelistPtr ISourceControlState::GetCheckInIdentifier() const`

#### enum `ISourceControlState::(anonymous)`  
`enum`  
_L28-28_

#### struct `ISourceControlState::FResolveInfo`  
`struct FResolveInfo`  
_L30-46_
- L32 _public member_ `FString RemoteFile;`
- L33 _public member_ `FString BaseFile;`
- L34 _public member_ `FString RemoteRevision;`
- L35 _public member_ `FString BaseRevision;`
- L37 _public function_ `bool IsValid() const`
- L42 _public function_ `operator bool() const`

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef TSharedRef<class ISourceControlState, ESPMode::ThreadSafe> FSourceControlStateRef;`
- L15 _typedef_ `typedef TSharedPtr<class ISourceControlState, ESPMode::ThreadSafe> FSourceControlStatePtr;`
- L19 _typedef_ `typedef TSharedRef<class ISourceControlChangelist, ESPMode::ThreadSafe> FSourceControlChangelistRef;`
- L20 _typedef_ `typedef TSharedPtr<class ISourceControlChangelist, ESPMode::ThreadSafe> FSourceControlChangelistPtr;`
- L28 _enumerator_ `enum { INVALID_REVISION = -1 }; struct FResolveInfo { FString RemoteFile; FString BaseFile; FString RemoteRevision; FString BaseRevision;` (scope `ISourceControlState::__anon8debacec0103`)

### `Source/Developer/SourceControl/Public/RevisionControlStyle/RevisionControlStyle.h` (Public)


#### class `FRevisionControlStyleManager`  
`class FRevisionControlStyleManager`  
_L13-41_
- desc: The style manager that is used to access the currently active revision control style. Use FRevisionControlStyleManager::Get() to access and use any revision control icons/styles
- L17 _public prototype_ `~FRevisionControlStyleManager();`
- L20 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L23 _public prototype_ `static const ISlateStyle& Get();` — @return The current revision control style being used
- L26 _public prototype_ `static FName GetStyleSetName();` — @return The name of the current revision control style being used
- L29 _public prototype_ `static void SetActiveRevisionControlStyle(FName InNewActiveRevisionControlStyleName);` — Set the active revision control style to the input style name
- L32 _public prototype_ `static void ResetToDefaultRevisionControlStyle();` — Set the active revision control style to the default style
- L37 _private member_ `static TSharedPtr< class ISlateStyle > DefaultRevisionControlStyleInstance;` — The default revision control style instance
- L40 _private member_ `static FName CurrentRevisionControlStyleName;` — The currently active revision control style

#### class `FDefaultRevisionControlStyle`  
`class FDefaultRevisionControlStyle : public FSlateStyleSet`  
_L48-74_
- inherits: `FSlateStyleSet`
- desc: The default revision control style the editor ships with. Inherit from this to create a custom revision controls style Use FRevisionControlStyleManager::SetActiveRevisionControlStyle to change the currently active revision control style Edit the defaults in the constructor here to change any revision control icons in the editor
- L52 _public prototype_ `FDefaultRevisionControlStyle();`
- L55 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L60 _protected member_ `FSlateColor BranchedColor;` — The specific color we use for all the "Branched" icons
- L63 _protected member_ `FSlateColor StatusCheckedOutColor;` — The specific colors we use for all the "Status" icons
- L64 _protected member_ `FSlateColor StatusCheckedOutByOtherUserColor;`
- L65 _protected member_ `FSlateColor StatusNotAtHeadRevisionColor;`
- L68 _protected member_ `FSlateColor SnapshotHistoryAdded;` — The specific colors we use for all the "Snapshot History" state icons
- L69 _protected member_ `FSlateColor SnapshotHistoryModified;`
- L70 _protected member_ `FSlateColor SnapshotHistoryRemoved;`
- L73 _private member_ `static FName StyleName;`

### `Source/Developer/SourceControl/Public/SSourceControlControls.h` (Public)


#### class `SSourceControlControls`  
`class SSourceControlControls : public SCompoundWidget`  
_L20-103_
- inherits: `SCompoundWidget`
- desc: Widget for displaying Source Control Check in Changes and Sync Latest buttons
- L23 _public function_ `SLATE_BEGIN_ARGS(SSourceControlControls)`
- L31 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget
- L35 _public prototype_ `EVisibility GetSourceControlMiddleSeparatorVisibility() const;` — Separators
- L36 _public prototype_ `EVisibility GetSourceControlRightSeparatorVisibility() const;`
- L39 _public prototype_ `static bool IsSourceControlSyncEnabled();` — Sync button
- L40 _public prototype_ `static bool HasSourceControlChangesToSync();`
- L41 _public prototype_ `static EVisibility GetSourceControlSyncStatusVisibility();`
- L42 _public prototype_ `static FText GetSourceControlSyncStatusText();`
- L43 _public prototype_ `static FText GetSourceControlSyncStatusToolTipText();`
- L44 _public prototype_ `static const FSlateBrush* GetSourceControlSyncStatusIcon();`
- L45 _public prototype_ `static FReply OnSourceControlSyncClicked();`
- L48 _public prototype_ `static bool IsSourceControlCheckInEnabled();` — Check-in button
- L49 _public prototype_ `static bool HasSourceControlChangesToCheckIn();`
- L50 _public prototype_ `static EVisibility GetSourceControlCheckInStatusVisibility();`
- L51 _public prototype_ `static FText GetSourceControlCheckInStatusText();`
- L52 _public prototype_ `static FText GetSourceControlCheckInStatusToolTipText();`
- L53 _public prototype_ `static const FSlateBrush* GetSourceControlCheckInStatusIcon();`
- L54 _public prototype_ `static FReply OnSourceControlCheckInChangesClicked();`
- L57 _public prototype_ `static bool IsSourceControlRestoreAsLatestEnabled();` — Restore as latest button
- L58 _public prototype_ `static EVisibility GetSourceControlRestoreAsLatestVisibility();`
- L59 _public prototype_ `static FText GetSourceControlRestoreAsLatestText();`
- L60 _public prototype_ `static FText GetSourceControlRestoreAsLatestToolTipText();`
- L61 _public prototype_ `static const FSlateBrush* GetSourceControlRestoreAsLatestStatusIcon();`
- L62 _public prototype_ `static FReply OnSourceControlRestoreAsLatestClicked();`
- L65 _public prototype_ `static int32 GetNumConflictsRemaining();`
- L66 _public prototype_ `static int32 GetNumConflictsUpcoming();`
- L69 _public function_ `static void SetNumConflictsRemaining(const FNumConflicts& InNumConflictsRemaining)`
- L70 _public function_ `static void SetNumConflictsUpcoming(const FNumConflicts& InNumConflictsUpcoming)`
- L72 _public function_ `static void SetIsSyncLatestEnabled(const FIsEnabled& InSyncLatestEnabled)`
- L73 _public function_ `static void SetIsCheckInChangesEnabled(const FIsEnabled& InCheckInChangesEnabled)`
- L74 _public function_ `static void SetIsRestoreAsLatestEnabled(const FIsEnabled& InRestoreAsLatestEnabled)`
- L76 _public function_ `static void SetIsSyncLatestVisible(const FIsVisible& InSyncLatestVisible)`
- L77 _public function_ `static void SetIsCheckInChangesVisible(const FIsVisible& InCheckInChangesVisible)`
- L78 _public function_ `static void SetIsRestoreAsLatestVisible(const FIsVisible& InRestoreAsLatestVisible)`
- L80 _public function_ `static void SetOnSyncLatestClicked(const FOnClicked& InSyncLatestClicked)`
- L81 _public function_ `static void SetOnCheckInChangesClicked(const FOnClicked& InCheckInChangesClicked)`
- L82 _public function_ `static void SetOnRestoreAsLatestClicked(const FOnClicked& InRestoreAsLatestClicked)`
- L86 _private member_ `TAttribute<bool> IsMiddleSeparatorEnabled;`
- L87 _private member_ `TAttribute<bool> IsRightSeparatorEnabled;`
- L89 _private member_ `static FNumConflicts NumConflictsRemaining;`
- L90 _private member_ `static FNumConflicts NumConflictsUpcoming;`
- L92 _private member_ `static FIsEnabled IsSyncLatestEnabled;`
- L93 _private member_ `static FIsEnabled IsCheckInChangesEnabled;`
- L94 _private member_ `static FIsEnabled IsRestoreAsLatestEnabled;`
- L96 _private member_ `static FIsVisible IsSyncLatestVisible;`
- L97 _private member_ `static FIsVisible IsCheckInChangesVisible;`
- L98 _private member_ `static FIsVisible IsRestoreAsLatestVisible;`
- L100 _private member_ `static FOnClicked OnSyncLatestClicked;`
- L101 _private member_ `static FOnClicked OnCheckInChangesClicked;`
- L102 _private member_ `static FOnClicked OnRestoreAsLatestClicked;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_RetVal(int32, FNumConflicts);`
- L14 _prototype_ `DECLARE_DELEGATE_RetVal(int32, FNumConflicts);`
- L16 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FIsVisible);`
- L16 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FIsVisible);`
- L17 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FIsEnabled);`
- L17 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FIsEnabled);`

### `Source/Developer/SourceControl/Public/ScopedSourceControlProgress.h` (Public)


#### class `FScopedSourceControlProgress`  
`class FScopedSourceControlProgress`  
_L9-31_
- L19 _public prototype_ `FScopedSourceControlProgress(const FText& InText, const FSimpleDelegate& InOnCancelled = FSimpleDelegate());` — Constructor. Progress dialog is shown immediately (if possible) and is closed when this object goes out of scope. @param	InText			The text to display in the progress dialog. If this is empty the dialog will not be shown. @param	InOnCancelled	The delegate to call when the cancel button is clicked.
- L22 _public prototype_ `~FScopedSourceControlProgress();` — Destructor - closes the dialog
- L25 _public prototype_ `void Tick();` — Makes sure the dialog is ticked
- L30 _private member_ `TWeakPtr<class SWindow> WindowPtr;` — The window containing this progress window

### `Source/Developer/SourceControl/Public/SourceControlAssetDataCache.h` (Public)


#### struct `FSourceControlAssetDataEntry`  
`struct FSourceControlAssetDataEntry`  
_L25-30_
- L27 _public member_ `FAssetDataArrayPtr AssetDataArrayPtr;`
- L28 _public member_ `TFuture<void> FetchAssetDataTask;`
- L29 _public member_ `bool bInitialized;`

#### struct `FAssetDataToLoad`  
`struct FAssetDataToLoad`  
_L32-36_
- L34 _public member_ `FString TempFilename;`
- L35 _public member_ `FString Filename;`

#### class `FSourceControlAssetDataCache`  
`class FSourceControlAssetDataCache`  
_L38-131_
- L40 _private typedef_ `typedef TMap<FString, FSourceControlAssetDataEntry> FAssetDataCache;`
- L44 _public prototype_ `void Startup();` — Called when SourceControl module is starting up.
- L47 _public prototype_ `void Shutdown();` — Called when SourceControl module is shutting down.
- L55 _public prototype_ `bool GetAssetDataArray(FSourceControlStateRef InFileState, FAssetDataArrayPtr& OutAssetDataArrayPtr);` — Attempt to get AssetData for the provided SourceControlled file. @param	InFileState				The asset to retrieve AssetData for. @param	OutAssetDataArrayPtr	If retrieved, the AssetData will be returned in this argument. @return True if processing is complete for the requested asset. False if the process is incomplete and AssetData could still be updated in the future.
- L60 _public prototype_ `void Tick();` — Called every update.
- L63 _public prototype_ `void OnSourceControlDialogShown();` — Called when Source Control Dialog is shown. Prevents tasks to run while the dialog is opened.
- L66 _public prototype_ `void OnSourceControlDialogClosed();` — Called when Source Control Dialog is closed. Allow work to be resumed.
- L75 _private prototype_ `FSourceControlAssetDataEntry* AddAssetInformationEntry(FSourceControlStateRef InFileState);` — Adds a new entry to the AssetData information cache. Retrieving possible informations from SourceControl. AssetData retrieval process is asynchronous, meaning it could not be available right after this call. @param	InFileState				The asset to retrieve AssetData for. @return A pointer to the newly created entry.
- L78 _private prototype_ `void DispatchDownloadFile();` — Executes the FDownloadFile fast path for files in FilesToDownload. Game thread only.
- L84 _private prototype_ `void OnDownloadFileComplete(const TArray<FString>& InDispatchedFiles, const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Called when the asynchronous FDownloadFile operation launched by DispatchDownloadFile completes. Runs on the game thread.
- L87 _private prototype_ `void DispatchUpdateHistory();` — Executes Source Control Operation to retrieve History for files in FileHistoryToUpdate
- L95 _private prototype_ `void OnUpdateHistoryComplete(const TArray<FString>& InUpdatedFiles, const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Called when the asynchronous Source Control Operation launched by GetFileHistory completes. @param	InUpdatedFiles	An array representing the updated files. @param	Operation		The Source Control operation used. @param	InResult		The result of the operation.
- L98 _private prototype_ `void DispatchFetchAssetData();` — Launches AssetData retrieval tasks for files contained in AssetDataToFetch
- L101 _private prototype_ `void FetchAssetData(FSourceControlStateRef InFileState);` — The payload executed by AssetData retrieval tasks
- L104 _private prototype_ `void OnFetchAssetDataComplete();` — Called after a FetchAssetData retrieval task has been executed
- L107 _private prototype_ `void UpdatePendingAssetData();` — Updates the AssetData information cache with the information retrieved from Source Control
- L110 _private prototype_ `void OnSourceControlProviderChanged(ISourceControlProvider& OldProvider, ISourceControlProvider& NewProvider);` — Callback called when the SourceControlProvider is changed
- L113 _private prototype_ `void ClearPendingTasks();` — Wait for the currently running tasks to finish and clears all queues.
- L116 _private prototype_ `void ClearAssetData(const FString& InFilename);` — Clears the asset data associated with it
- L119 _private member_ `FAssetDataCache AssetDataCache;`
- L120 _private member_ `TArray<FString> FileHistoryToUpdate;`
- L121 _private member_ `TArray<FString> FilesToDownload;`
- L122 _private member_ `TQueue<FSourceControlStatePtr, EQueueMode::Spsc> AssetDataToFetch;`
- L123 _private member_ `TQueue<FAssetDataToLoad, EQueueMode::Mpsc> AssetDataToLoad;`
- L124 _private member_ `FDelegateHandle ProviderChangedDelegateHandle;`
- L125 _private member_ `FDelegateHandle ActorLabelChangedDelegateHandle;`
- L126 _private member_ `FDelegateHandle AssetUpdatedDelegateHandle;`
- L127 _private member_ `std::atomic<uint32> CurrentAsyncTask = 0;`
- L128 _private member_ `bool bIsSourceControlDialogShown = false;`
- L129 _private member_ `bool bIsUpdateHistoryInFlight = false;`
- L130 _private member_ `bool bIsDownloadFileInFlight = false;`

#### Free symbols / members of external scopes

- L23 _typedef_ `typedef TSharedPtr<TArray<FAssetData>> FAssetDataArrayPtr;`

### `Source/Developer/SourceControl/Public/SourceControlFileStatusMonitor.h` (Public)


#### class `FSourceControlFileStatusMonitor`  
`class FSourceControlFileStatusMonitor : public TSharedFromThis<FSourceControlFileStatusMonitor>`  
_L24-210_
- inherits: `TSharedFromThis<FSourceControlFileStatusMonitor>`
- desc: Periodically monitors the source controlled status of a collection of files and notifies the latest status, including potential warnings such as 'out of date', 'locked by other', etc. This service is meant to throttle and batch non-time sensitive FUpdateStatus requests to the source control provider because those requests are expensive and can add an undesired load on the provider server.
- L28 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnSourceControlFileStatus, const FString& , const ISourceControlState* );` — Invoked when the status of a source controlled files is updated. The state can be null when the source control provider is changed.
- L31 _public prototype_ `FSourceControlFileStatusMonitor();`
- L32 _public prototype_ `virtual ~FSourceControlFileStatusMonitor();`
- L52 _public prototype_ `void StartMonitoringFile(uintptr_t OwnerId, const FString& AbsPathname, FOnSourceControlFileStatus OnSourceControlledFileStatus);` — Starts monitoring the source control status of the specified file. If the status is already known (the file is already monitored by another party), the know status is returned right away, otherwise a request is sent to the source control provider to get the status. The request is subject to the probation period policy to allow batching requests. The file status is refreshed according to the refresh period policy. The caller must be sure to call StopMonitoringFile() when the files status is not desired anymore. It is ok to call StopMonitoringFile() within the callback OnSourceControlledFileStatus(). @param Owner The unique Id of the caller, typically the caller memory address. @param AbsPathname The absolute path and filname of the file to monitor. @param OnSourceControlledFileStatus Delegate invoked whe the status of the file is updated. @see SetNewRequestProbationPeriod() @see SetUpdateStatusPeriod() @see SetSuspendMonitoringPolicy() @see GetStatusAge()
- L53 _public prototype_ `void StartMonitoringFiles(uintptr_t OwnerId, const TArray<FString>& AbsPathnames, FOnSourceControlFileStatus OnSourceControlledFileStatus);`
- L54 _public prototype_ `void StartMonitoringFiles(uintptr_t OwnerId, const TSet<FString>& AbsPathnames, FOnSourceControlFileStatus OnSourceControlledFileStatus);`
- L65 _public prototype_ `void StopMonitoringFile(uintptr_t OwnerId, const FString& AbsPathname);` — Stops monitoring the source control status of the specified file. If the specified file is not monitored, the function returns successfully. @param OwnerId The unique Id of the caller, typically the caller memory address. @param AbsPathname The absolute path and filname of the file to stop monitoring. @note This can be called fron the FOnSourceControlFileStatus callback passed to StartMonitoringFile().
- L66 _public prototype_ `void StopMonitoringFiles(uintptr_t OwnerId, const TArray<FString>& AbsPathnames);`
- L67 _public prototype_ `void StopMonitoringFiles(uintptr_t OwnerId, const TSet<FString>& AbsPathnames);`
- L72 _public prototype_ `void StopMonitoringFiles(uintptr_t OwnerId);` — Stops monitoring all the files that were registered by the specified owner Id.
- L82 _public prototype_ `void SetMonitoringFiles(uintptr_t OwnerId, TSet<FString>&& AbsPathnames, FOnSourceControlFileStatus OnSourceControlledFileStatus);` — Starts monitoring files that weren't monitored yet by the specified owner, stops monitoring those that were monitored by the owner but are not in the updated list and keep monitoring files that were monitored before and still in the updated list. @param OwnerId The unique Id of the caller, typically the caller memory address. @param AbsPathnames The list of absolute file pathnames that must be monitored. (The set is modified during the operation) @param OnSourceControlledFileStatus Delegate invoked whe the status of the file is updated.
- L87 _public prototype_ `TSet<FString> GetMonitoredFiles(uintptr_t OwnerId);` — Returns the set of files being monitored by the specifed owner.
- L94 _public prototype_ `TOptional<FTimespan> GetStatusAge(const FString& AbsPathname) const;` — Returns the file status age, i.e. (now - last_status_update) if the file is monitored. If the initial status request hasn't been received yet, returns zero.
- L102 _public function_ `void SetNewRequestProbationPeriodPolicy(const FTimespan& InPropbationPeriod)` — Set the times waited before a newly added file status request is sent to the source control provider. This is used batch several status for file added closed in time into a single server request, for example if StartMonitoringFile() is called in a loop or when the user scroll a long list of files for which the status needs to be updated. Setting a value of 0 remove the probation period. By default, the propbation period is 1 second.
- L103 _public function_ `FTimespan GetNewRequestProbationPeriodPolicy() const`
- L112 _public function_ `void SetUpdateStatusPeriodPolicy(const FTimespan& InRefreshPeriod)` — Set the status refresh period. By default, the monitored files are refreshed every 5 minutes, providing the monitor is it suspended according to the suspend monitor policy. The refresh period has an impact on the load of the source control provider. A short period may overload the provider service. @see SetSuspendMonitoringPolicy
- L113 _public function_ `FTimespan GetUpdateStatusPeriodPolicy() const`
- L119 _public function_ `void SetMaxFilePerRequestPolicy(int32 MaxNum)` — Sets the maximum number of files to batch into a single request. By default, a maximum of 100 files status is requested.
- L120 _public function_ `int32 GetMaxFilePerRequestPolicy() const`
- L128 _public function_ `void SetSuspendMonitoringPolicy(TFunction<bool()> IsMonitoringSuspended)` — Sets a function invoked to detect if the monitor should suspend its activities, for example, if no user is currently interacting with the application, it may not worth checking the file status periodically. By default, the monitor will suspends  if there are not Slate interaction within 5 minutes and resume at the next user interaction.
- L154 _private prototype_ `void OnSourceControlStatusUpdate(const TSharedRef<ISourceControlOperation>& InOperation, ECommandResult::Type InType);` — Invoked when the source control has updated the status for the requested files.
- L157 _private prototype_ `void OnSourceControlProviderChanged(ISourceControlProvider& OldProvider, ISourceControlProvider& NewProvider);` — Invoked when the source control provider changes.
- L160 _private prototype_ `bool Tick(float DeltaTime);` — Invoked by the main loop ticker to fire source control requests.
- L163 _private prototype_ `TSharedPtr<FSourceControlFileStatus> FindFileStatus(const FString& Pathname) const;` — Returns the specified files status or null if not found.
- L166 _private function_ `bool HasOngoingRequest() const` — Whethers the monitor has an in-flight request with the source control provider.
- L170 _private member_ `TMap<FString, TSharedPtr<FSourceControlFileStatus>> MonitoredFiles;` — The files currently monitored, mapping absolute file pathname to the monitored information.
- L173 _private member_ `TArray<FString> RequestedStatusFiles;` — The list of files for which a request to the source control provider is currently in-flight/ongoing.
- L176 _private member_ `FTimespan ProbationPeriodPolicy;` — The newly added files probation period. Time left to batch several files into the same requests.
- L179 _private member_ `FTimespan RemainingPeriodPolicy;` — The remaining files retry period. Time left until we retry a file's CanQuerySourceControl status.
- L182 _private member_ `FTimespan RefreshPeriodPolicy;` — The status refresh period. Time left until we re-request a file status.
- L185 _private member_ `TFunction<bool()> SuspendMonitoringPolicy;` — Invoked to detect wheter the monitoring is paused/suspended (no request to source control provider).
- L188 _private member_ `int32 MaxFileNumPerRequestPolicy = 100;` — The maximum number of files allowed to be batched together for a request to the provider.
- L191 _private member_ `double LastSourceControlCheckSecs = 0.0;` — Last time a request to the source control provider was issued.
- L194 _private member_ `double LastAddedFileTimeSecs = 0.0;` — Last time a file was added to the list of monitored files.
- L197 _private member_ `double LastRemainingFileTimeSecs = 0.0;` — Last time some files were left remaining after inspection.
- L200 _private member_ `double OldestFileStatusTimeSecs = 0.0;` — The oldest status update time.
- L203 _private member_ `int32 NewAddedFileCount = 0;` — Number of files newly added that are in probation.
- L206 _private member_ `FTSTicker::FDelegateHandle TickerHandle;` — Handle for the tick.
- L209 _private member_ `FDelegateHandle SourceControlProviderChangedDelegateHandle;` — Handle of the registered source provider change delegate.

#### struct `FSourceControlFileStatusMonitor::FUintptrHash`  
`struct FUintptrHash : public TDefaultMapKeyFuncs<uintptr_t, FOnSourceControlFileStatus, false>`  
_L132-138_
- inherits: `TDefaultMapKeyFuncs<uintptr_t,FOnSourceControlFileStatus,false>`
- desc: Some compilers were ambigous when picking a Hash function for uintprt_t, provide a custom one.
- L134 _public function_ `static uint32 GetKeyHash(const uintptr_t& Key)`

#### struct `FSourceControlFileStatusMonitor::FSourceControlFileStatus`  
`struct FSourceControlFileStatus`  
_L140-150_
- L142 _public function_ `FSourceControlFileStatus(uintptr_t OriginalOwnerId, FOnSourceControlFileStatus InFileStatusUpdateDelegate)`
- L147 _public member_ `TSharedPtr<ISourceControlState> FileState;`
- L148 _public member_ `double LastStatusCheckTimestampSecs = 0.0;`
- L149 _public member_ `TMap<uintptr_t, FOnSourceControlFileStatus, FDefaultSetAllocator, FUintptrHash> OwnerDelegateMap;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SOURCECONTROL_API`
- L28 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSourceControlFileStatus, const FString& , const ISourceControlState* );` — Invoked when the status of a source controlled files is updated. The state can be null when the source control provider is changed.

### `Source/Developer/SourceControl/Public/SourceControlHelpers.h` (Public)


#### struct `FSourceControlState`  
`struct FSourceControlState`  
_L37-212_
- reflection: `USTRUCT(BlueprintType)`
- desc: Snapshot of source control state of a file @see	USourceControlHelpers::QueryFileState()
- L43 _public function_ `FSourceControlState() : bIsValid(false), bIsUnknown(false), bCanCheckIn(false), bCanCheckOut(false), bIsCheckedOut(false), bIsCurrent(false), bIsSourceControlled(false), bIsAdded(false), bIsDeleted(false), bIsIgnored(false), bCanEdit(false), bCanDelete(false), bIsModified(false), bCanAdd(false), bIsConflicted(false), bCanRevert(false), bIsCheckedOutOther(false)`
- L63 _public function_ `void SetFromStatus(const FSourceControlStatePtr& InStatus)`
- L119 _public member_ `FString Filename;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Get the local filename that this state represents
- L123 _public member_ `bool bIsValid = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Indicates whether this source control state has valid information (true) or not (false)
- L127 _public member_ `bool bIsUnknown = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if we know anything about the source control state of this file
- L131 _public member_ `bool bCanCheckIn = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file can be checked in.
- L135 _public member_ `bool bCanCheckOut = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file can be checked out
- L139 _public member_ `bool bIsCheckedOut = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file is checked out
- L143 _public member_ `bool bIsCurrent = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file is up-to-date with the version in source control
- L147 _public member_ `bool bIsSourceControlled = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file is under source control
- L154 _public member_ `bool bIsAdded = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file is marked for add @note	if already checked in then not considered mid add
- L158 _public member_ `bool bIsDeleted = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file is marked for delete
- L162 _public member_ `bool bIsIgnored = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file is ignored by source control
- L166 _public member_ `bool bCanEdit = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if source control allows this file to be edited
- L170 _public member_ `bool bCanDelete = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if source control allows this file to be deleted.
- L174 _public member_ `bool bIsModified = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file is modified compared to the version in source control.
- L181 _public member_ `bool bCanAdd = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file can be added to source control (i.e. is part of the directory structure currently under source control)
- L185 _public member_ `bool bIsConflicted = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file is in a conflicted state
- L189 _public member_ `bool bCanRevert = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file can be reverted, i.e. discard changes and the file will no longer be checked-out.
- L193 _public member_ `bool bIsCheckedOutOther = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file is checked out by someone else
- L199 _public member_ `FString CheckedOutOther;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Get name of other user who this file already checked out or "" if no other user has it checked out
- L203 _public member_ `bool bIsCheckedOutInOtherBranch = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file is checked out by someone else in another branch
- L207 _public member_ `bool bIsModifiedInOtherBranch = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if this file is modified by someone in another branch
- L211 _public member_ `FString PreviousUser;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — The username of the previous user to modify this file

#### class `USourceControlHelpers`  
`class USourceControlHelpers : public UObject`  
_L245-724_
- reflection: `UCLASS(MinimalAPI, Abstract, Transient, meta = (ScriptName = "SourceControl"))`
- inherits: `UObject`
- desc: Editor source control common functionality. @note Many of these source control methods use *smart* file strings which can be one of: - fully qualified path - relative path - long package name - asset path - export text path (often stored on clipboard) For example: - D:\Epic\Dev-Ent\Projects\Python3rdBP\Content\Mannequin\Animations\ThirdPersonIdle.uasset - Content\Mannequin\Animations\ThirdPersonIdle.uasset - /Game/Mannequin/Animations/ThirdPersonIdle - /Game/Mannequin/Animations/ThirdPersonIdle.ThirdPersonIdle - AnimSequence'/Game/Mannequin/Animations/ThirdPersonIdle.ThirdPersonIdle'
- L257 _public prototype_ `static FString CurrentProvider();` — `UFUNCTION(BlueprintPure, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine the name of the current source control provider. @return	the name of the current source control provider. If one is not set then "None" is returned.
- L264 _public prototype_ `static bool IsEnabled();` — `UFUNCTION(BlueprintPure, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Determine if there is a source control system enabled @return	true if enabled, false if not
- L273 _public prototype_ `static bool IsAvailable();` — `UFUNCTION(BlueprintPure, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Quick check if currently set source control provider is enabled and available for use (server-based providers can use this to return whether the server is available or not) @return	true if source control is available, false if it is not
- L280 _public prototype_ `static FText LastErrorMsg();` — `UFUNCTION(BlueprintPure, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Get status text set by SourceControl system if an error occurs regardless whether bSilent is set or not. Only set if there was an error.
- L291 _public prototype_ `static bool SyncFile(const FString& InFile, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to sync a file or directory to the head revision. @note	Blocks until action is complete. @param	InFile	The file or directory to sync - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent	if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L302 _public prototype_ `static bool SyncFiles(const TArray<FString>& InFiles, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to sync files or directories to the head revision. @note	Blocks until action is complete. @param	InFiles	Files or directories to sync - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent	if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L313 _public prototype_ `static bool CheckOutFile(const FString& InFile, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to check out a file. @note	Blocks until action is complete. @param	InFile		The file to check out - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent		if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L324 _public prototype_ `static bool CheckOutFiles(const TArray<FString>& InFiles, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to check out specified files. @note	Blocks until action is complete. @param	InFiles		Files to check out - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent		if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L335 _public prototype_ `static bool CheckOutOrAddFile(const FString& InFile, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to check out file or mark it for add. @note	Blocks until action is complete. @param	InFile		The file to check out/add - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent		if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L346 _public prototype_ `static bool CheckOutOrAddFiles(const TArray<FString>& InFiles, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to check out files or mark them for add. @note	Blocks until action is complete. @param	InFiles		The files to check out/add - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent		if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L359 _public prototype_ `static bool CheckoutOrMarkForAdd(const FString& InDestFile, const FText& InFileDescription, const FOnPostCheckOut& OnPostCheckOut, FText& OutFailReason);` — Helper function perform an operation on files in our 'source controlled' directories, handling checkout/add etc. @note	Blocks until action is complete. Older C++ only version of CheckOutOrAddFile(). @param	InDestFile			The path to the destination file @param	InFileDescription	Description of the file to display to the user, e.g. "Text" or "Image" @param	OnPostCheckOut		Delegate used for performing operation on files that may need a checkout, but before they are added to source control @param	OutFailReason		Text describing why the operation failed @return	Success or failure of the operation @see     CheckOutOrAddFile()
- L370 _public prototype_ `static bool MarkFileForAdd(const FString& InFile, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to mark a file for add. Does nothing (and returns true) if the file is already under SC @note	Blocks until action is complete. @param	InFile		The file to add - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent		if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L381 _public prototype_ `static bool MarkFilesForAdd(const TArray<FString>& InFiles, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to mark files for add. Does nothing (and returns true) for any file that is already under SC @note	Blocks until action is complete. @param	InFiles		Files to check out - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent		if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L393 _public prototype_ `static bool MarkFileForDelete(const FString& InFile, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to remove file from source control and delete the file. @note	Blocks until action is complete. @param	InFile		The file to delete - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent		if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L404 _public prototype_ `static bool MarkFilesForDelete(const TArray<FString>& InFiles, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to remove files from source control and delete the files. @note	Blocks until action is complete. @param	InFile		The file to delete - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent		if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L415 _public prototype_ `static bool RevertFile(const FString& InFile, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to revert a file regardless whether any changes will be lost or not. @note	Blocks until action is complete. @param	InFile	The file to revert - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent	if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L427 _public prototype_ `static bool ApplyOperationAndReloadPackages(const TArray<FString>& InPackagesToApplyOperation, const TFunctionRef<bool(const TArray<FString>&)>& InOperation, bool bReloadWorld = false, bool bInteractive = true);` — Applies the provided function and optionally reloads the world @param	InPackagesToApplyOperation			The files/packages to apply the operation @param	InOperation							The function to apply @param	bReloadWorld						Reload the world @param	bInteractive						Whether to prompt user when discarding changes @return true if succeeded.
- L438 _public prototype_ `static bool RevertAndReloadPackages(const TArray<FString>& InPackagesToRevert, bool bRevertAll = false, bool bReloadWorld = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Reverts the provided files then reloads packages. @param	InPackagesToRevert					The packages to revert @param	bRevertAll							Whether to revert all files @param	bReloadWorld						Reload the world @return true if succeeded.
- L444 _public prototype_ `static bool RevertAllChangesAndReloadWorld();` — Reverts all changes and then reloads the world. @return true if succeeded.
- L457 _public prototype_ `static bool RevertFiles(const TArray<FString>& InFiles, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to revert files regardless whether any changes will be lost or not. @note	Blocks until action is complete. @param	InFiles	Files to revert - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent	if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L468 _public prototype_ `static bool RevertUnchangedFile(const FString& InFile, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to revert a file provided no changes have been made. @note	Blocks until action is complete. @param	InFile	File to check out - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent	if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L479 _public prototype_ `static bool RevertUnchangedFiles(const TArray<FString>& InFiles, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to revert files provided no changes have been made. @note	Blocks until action is complete. @param	InFiles	Files to check out - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent	if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L489 _public prototype_ `static void RevertUnchangedFiles(ISourceControlProvider& InProvider, const TArray<FString>& InFiles);` — Helper function to get a list of files that are unchanged & revert them. This runs synchronous commands. @note	Older C++ only version of RevertFiles(Files, false). @see		RevertFiles() @param	InProvider	The provider to use @param	InFiles		The files to operate on
- L502 _public prototype_ `static bool CheckInFile(const FString& InFile, const FString& InDescription, bool bSilent = false, bool bKeepCheckedOut = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to check in a file. @note	Blocks until action is complete. @param	InFile			The file to check in - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	InDescription	Description for check in @param	bSilent			if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @param	bKeepCheckedOut Keep files checked-out after checking in. This is helpful for maintaining "ownership" of files if further operations are needed. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L515 _public prototype_ `static bool CheckInFiles(const TArray<FString>& InFiles, const FString& InDescription, bool bSilent = false, bool bKeepCheckedOut = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to check in specified files. @note	Blocks until action is complete. @param	InFiles			Files to check out - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	InDescription	Description for check in @param	bSilent			if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @param	bKeepCheckedOut Keep files checked-out after checking in. This is helpful for maintaining "ownership" of files if further operations are needed. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L527 _public prototype_ `static bool CopyFile(const FString& InSourceFile, const FString& InDestFile, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to copy a file. @note	Blocks until action is complete. @param	InSourceFile	Source file string to copy from - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	InDestFile		Source file string to copy to - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard). If package, then uses same extension as source file. @param	bSilent			if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
- L539 _public prototype_ `static bool CopyFileUnderSourceControl(const FString& InDestFile, const FString& InSourceFile, const FText& InFileDescription, FText& OutFailReason);` — Helper function to copy a file into our 'source controlled' directories, handling checkout/add etc. @note	Blocks until action is complete. Older C++ only version of CopyFile(). @param	InDestFile			The path to the destination file @param	InSourceFile		The path to the source file @param	InFileDescription	Description of the file to display to the user, e.g. "Text" or "Image" @param	OutFailReason		Text describing why the operation failed @return	Success or failure of the operation
- L551 _public prototype_ `static FSourceControlState QueryFileState(const FString& InFile, bool bSilent = false, bool bUseSourceControlStateCache = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Use currently set source control provider to query a file's source control state. @note	Blocks until action is complete. @param	InFile			The file to query - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent			if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @return	Source control state - see USourceControlState. It will have bIsValid set to false if it could not have its values set.
- L554 _public prototype_ `static TArray<FSourceControlState> QueryFileStates(TArray<FString> InFiles, bool bSilent = false, bool bUseSourceControlStateCache = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))`
- L557 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FQueryFileStateDelegate, FSourceControlState, FileStateOut);` — Delegate to broadcast FileState upon AsyncQueryFileState completion
- L566 _public prototype_ `static void AsyncQueryFileState(FQueryFileStateDelegate FileStateCallback, const FString& InFile, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))` — Query the source control state of the specified file, asynchronously. @param	FileStateCallback Source control state - see USourceControlState. It will have bIsValid set to false if it could not have its values set. @param	InFile			  The file to query - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard) @param	bSilent			  if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless.
- L568 _public prototype_ `static void AsyncQueryFileStates(FQueryFileStateDelegate FileStateCallback, TArray<FString> InFiles, bool bSilent = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Editor Revision Control Helpers", meta = (Keywords = "Source Control"))`
- L581 _public prototype_ `static bool GetFilesInDepotAtPath(const FString& Path, TArray<FString>& OutFilesList, bool bIncludeDeleted = false, bool bSilent = false, bool bIsFileRegexSearch = false);` — Use currently set source control provider to query the list of files in the depot under a certain path. @note	Blocks until action is complete. @param	Path				The path which we want to query the list of files from. @param	OutFilesList		An array containing the list of files under the queried path. @param	bIncludeDeleted		Include files that have been deleted from the depot. @param	bSilent				If false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @param	bIsFileRegexSearch	If false, it is a folder search. If true, it is a file regex search @return	Success or failure of the operation
- L594 _public prototype_ `static bool GetFilesInDepotAtPaths(const TArray<FString>& Paths, TArray<FString>& OutFilesList, bool bIncludeDeleted = false, bool bSilent = false, bool bIsFileRegexSearch = false);` — Use currently set source control provider to query the list of files in the depot under a list of paths. @note	Blocks until action is complete. @param	Paths				The paths which we want to query the list of files from. @param	OutFilesList		An array containing the list of files under the queried path. @param	bIncludeDeleted		Include files that have been deleted from the depot. @param	bSilent				If false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless. @param	bIsFileRegexSearch	If false, it is a folder search. If true, it is a file regex search @return	Success or failure of the operation
- L601 _public prototype_ `static FString PackageFilename(const FString& InPackageName);` — Helper function to get a filename for a package name. @param	InPackageName	The package name to get the filename for @return the filename
- L608 _public prototype_ `static FString PackageFilename(const UPackage* InPackage);` — Helper function to get a filename for a package. @param	InPackage	The package to get the filename for @return the filename
- L615 _public prototype_ `static TArray<FString> PackageFilenames(const TArray<FString>& InPackageNames);` — Helper function to convert package name array into a filename array. @param	InPackageNames	The package name array @return an array of filenames
- L622 _public prototype_ `static TArray<FString> PackageFilenames(const TArray<UPackage*>& InPackages);` — Helper function to convert package array into filename array. @param	InPackages	The package array @return an array of filenames
- L629 _public prototype_ `static TArray<FString> AbsoluteFilenames(const TArray<FString>& InFileNames);` — Helper function to convert a filename array to absolute paths. @param	InFileNames	The filename array @return an array of filenames, transformed into absolute paths
- L639 _public prototype_ `static bool AnnotateFile(ISourceControlProvider& InProvider, const FString& InLabel, const FString& InFile, TArray<FAnnotationLine>& OutLines);` — Helper function to annotate a file using a label @param	InProvider	The provider to use @param	InLabel		The label to use to retrieve the file @param	InFile		The file to annotate @param	OutLines	Output array of annotated lines @returns true if successful
- L649 _public prototype_ `static bool AnnotateFile(ISourceControlProvider& InProvider, int32 InCheckInIdentifier, const FString& InFile, TArray<FAnnotationLine>& OutLines);` — Helper function to annotate a file using a changelist/checkin identifier @param	InProvider				The provider to use @param	InCheckInIdentifier		The changelist/checkin identifier to use to retrieve the file @param	InFile					The file to annotate @param	OutLines				Output array of annotated lines @returns true if successful
- L659 _public prototype_ `static bool BranchPackage(UPackage* DestPackage, UPackage* SourcePackage, EStateCacheUsage::Type StateCacheUsage = EStateCacheUsage::ForceUpdate);` — Helper function to branch/integrate packages from one location to another maintaining a relationship between the files in source control (when possible) @param	DestPackage			The destination package @param	SourcePackage		The source package @Param	StateCacheUsage		Whether to use the source control state cache @return true if the file packages were successfully branched.
- L668 _public prototype_ `static bool CopyPackage(UPackage* DestPackage, UPackage* SourcePackage, EStateCacheUsage::Type StateCacheUsage = EStateCacheUsage::ForceUpdate);` — Helper function to copy a package from one location to another @param	DestPackage             The destination package @param	SourcePackage           The source package @Param	StateCacheUsage         Whether to use the source control state cache @return true if the file packages were successfully branched.
- L674 _public prototype_ `static const FString& GetSettingsIni();` — Helper function to get the ini filename for storing source control settings @return the filename
- L680 _public prototype_ `static const FString& GetGlobalSettingsIni();` — Helper function to get the ini filename for storing global source control settings @return the filename
- L686 _public prototype_ `static bool GetAssetData(const FString& InFileName, const FString& InPackageName, TArray<FAssetData>& OutAssets, TArray<FName>* OutDependencies = nullptr);` — Helper function to retrieve the FAssetData associated with a given file @return Whether the asset data could be retrieved or not
- L692 _public prototype_ `static bool GetAssetData(const FString& InFileName, TArray<FAssetData>& OutAssets, TArray<FName>* OutDependencies = nullptr);` — Helper function to retrieve the FAssetData associated with a given file @return Whether the asset data could be retrieved or not
- L698 _public prototype_ `static bool GetAssetDataFromPackage(const FString& InPackageName, TArray<FAssetData>& OutAssets, TArray<FName>* OutDependencies = nullptr);` — Helper function to retrieve the FAssetData associated with a given package name @return Whether the asset data could be retrieved or not
- L704 _public prototype_ `static bool GetAssetDataFromFileHistory(const FString& InFileName, TArray<FAssetData>& OutAssets, TArray<FName>* OutDependencies = nullptr, int64 MaxFetchSize = -1);` — Helper function to get the asset data from a file's history Note: will not query history to prevent recursion
- L710 _public prototype_ `static bool GetAssetDataFromFileHistory(FSourceControlStatePtr InSourceControlState, TArray<FAssetData>& OutAssets, TArray<FName>* OutDependencies = nullptr, int64 MaxFetchSize = -1);` — Helper function to get the asset data from a file's history Note: will not query history to prevent recursion
- L715 _public prototype_ `static bool ListRevertablePackages(TArray<FString>& OutRevertablePackageNames);` — Find packages that can be reverted in Source Control locations
- L722 _public prototype_ `static TArray<FString> GetSourceControlLocations(const bool bContentOnly = false);` — Get the list of files and directories that source control should check when looking for changes. @param	bContentOnly	True to only include content directories.

#### class `FScopedSourceControl`  
`class FScopedSourceControl`  
_L731-745_
- desc: Helper class that ensures FSourceControl is properly initialized and shutdown by calling Init/Close in its constructor/destructor respectively.
- L735 _public prototype_ `FScopedSourceControl();` — Constructor; Initializes Source Control Provider
- L738 _public prototype_ `~FScopedSourceControl();` — Destructor; Closes Source Control Provider
- L741 _public prototype_ `ISourceControlProvider& GetProvider();` — Get the provider we are using
- L744 _private member_ `bool bInitSourceControl = false;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API SOURCECONTROL_API`
- L222 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnPostCheckOut, const FString& , const FText& , FText& );` — Delegate used for performing operation on files that may need a checkout, but before they are added to source control @param	InDestFile			The filename that was potentially checked out @param	InFileDescription	Description of the file to display to the user, e.g. "Text" or "Image" @param	OutFailReason		Text describing why the operation failed @return true if the operation was successful
- L222 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnPostCheckOut, const FString& , const FText& , FText& );` — Delegate used for performing operation on files that may need a checkout, but before they are added to source control @param	InDestFile			The filename that was potentially checked out @param	InFileDescription	Description of the file to display to the user, e.g. "Text" or "Image" @param	OutFailReason		Text describing why the operation failed @return true if the operation was successful
- L225 _typedef_ `typedef class USourceControlHelpers SourceControlHelpers;` — For backwards compatibility
- L557 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FQueryFileStateDelegate, FSourceControlState, FileStateOut);` — Delegate to broadcast FileState upon AsyncQueryFileState completion

### `Source/Developer/SourceControl/Public/SourceControlInitSettings.h` (Public)


#### class `FSourceControlInitSettings`  
`class FSourceControlInitSettings`  
_L13-67_
- L42 _public prototype_ `FSourceControlInitSettings(EBehavior Behavior);`
- L43 _public prototype_ `FSourceControlInitSettings(EBehavior Behavior, ECmdLineFlags CmdLineFlags);`
- L44 _public prototype_ `~FSourceControlInitSettings() = default;`
- L46 _public prototype_ `void SetConfigBehavior(EConfigBehavior Behavior);`
- L48 _public prototype_ `bool CanWriteToConfigFile() const;`
- L49 _public prototype_ `bool CanReadFromConfigFile() const;`
- L51 _public prototype_ `void AddSetting(FStringView SettingName, FStringView SettingValue);`
- L52 _public prototype_ `void OverrideSetting(FStringView SettingName, FString& InOutSettingValue);`
- L54 _public prototype_ `bool HasOverrides() const;`
- L55 _public prototype_ `bool IsOverridden(FStringView SettingName) const;`
- L57 _public prototype_ `void SetCmdLineFlags(ECmdLineFlags Flags);`
- L58 _public prototype_ `bool ShouldReadFromCmdLine() const;`
- L62 _private member_ `EBehavior OverrideBehavior = EBehavior::OverrideAll;`
- L63 _private member_ `ECmdLineFlags CmdLineFlags = ECmdLineFlags::None;`
- L64 _private member_ `EConfigBehavior ConfigBehavior = EConfigBehavior::ReadWrite;`
- L66 _private member_ `TMap<FString, FString> Settings;`

#### enum `FSourceControlInitSettings::EBehavior`  
`enum class EBehavior`  
_L16-22_
- L19 _public enumerator_ `OverrideAll` — All existing settings will be overridden via the contents of FSourceControlInitSettings. Settings that are not found will be reset to default states
- L21 _public enumerator_ `OverrideExisting` — Only the settings found in FSourceControlInitSettings will be overridden. Settings not found will be left with their current values.

#### enum `FSourceControlInitSettings::ECmdLineFlags`  
`enum class ECmdLineFlags : uint8`  
_L24-30_
- L27 _public enumerator_ `None` — Do not read any settings from the commandline
- L29 _public enumerator_ `ReadAll` — Read all available settings from the commandline

#### enum `FSourceControlInitSettings::EConfigBehavior`  
`enum class EConfigBehavior : uint8`  
_L32-40_
- L35 _public enumerator_ `ReadWrite` — Can both read from, and save to the ini file
- L37 _public enumerator_ `ReadOnly` — Will only read settings from the ini file, settings determined at runtime will not be saved to the ini file
- L39 _public enumerator_ `None` — The settings will not be saved to the ini file, nor will they be read from the ini file

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SOURCECONTROL_API`

### `Source/Developer/SourceControl/Public/SourceControlOperationBase.h` (Public)


#### class `FSourceControlOperationBase`  
`class FSourceControlOperationBase : public ISourceControlOperation`  
_L8-96_
- inherits: `ISourceControlOperation`
- desc: Adds some common functionality to source control operations.
- L22 _public prototype_ `FSourceControlOperationBase() = default;`
- L23 _public prototype_ `virtual ~FSourceControlOperationBase() = default;`
- L26 _public function_ `virtual const FSourceControlResultInfo& GetResultInfo() const override` — Retrieve any info or error messages that may have accumulated during the operation.
- L32 _public function_ `virtual void AddInfoMessge(const FText& InInfo)` — Add info/warning message.
- L38 _public function_ `virtual void AddErrorMessge(const FText& InError)` — Add error message.
- L44 _public function_ `virtual void AddTag(const FString& InTag)` — Add tag.
- L53 _public function_ `virtual void AppendResultInfo(const FSourceControlResultInfo& InResultInfo) override` — Append any info or error messages that may have accumulated during the operation prior to returning a result, ensuring to keep any already accumulated info.
- L58 _public function_ `void SetEnableErrorLogging(bool bEnabled)`
- L70 _public function_ `virtual bool ShouldLogErrors() const override`
- L75 _public function_ `void SetEnableInfoLogging(bool bEnabled)`
- L87 _public function_ `virtual bool ShouldLogInfos() const override`
- L92 _public member_ `FSourceControlResultInfo ResultInfo;`
- L95 _protected member_ `EFlags Flags = EFlags::None;`

#### enum `FSourceControlOperationBase::EFlags`  
`enum class EFlags`  
_L11-19_
- L14 _public enumerator_ `None = 0` — No specialization applied
- L16 _public enumerator_ `DisableErrorLogging = 1 << 0` — When set the operation should not log any errors but should continue to store them in the ResultInfo member
- L18 _public enumerator_ `DisableInfoLogging = 1 << 1` — When set the operation should not log any info messages but should continue to store them in the ResultInfo member

#### Free symbols / members of external scopes

- L98 _prototype_ `ENUM_CLASS_FLAGS(FSourceControlOperationBase::EFlags);`

### `Source/Developer/SourceControl/Public/SourceControlOperations.h` (Public)


#### class `FConnect`  
`class FConnect : public FSourceControlOperationBase`  
_L28-68_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to connect (or test a connection) to source control
- L32 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L37 _public function_ `virtual FText GetInProgressString() const override`
- L42 _public function_ `const FString& GetPassword() const`
- L47 _public function_ `void SetPassword(const FString& InPassword)`
- L52 _public function_ `const FText& GetErrorText() const`
- L57 _public function_ `void SetErrorText(const FText& InErrorText)`
- L64 _protected member_ `FString Password;` — Password we use for this operation
- L67 _protected member_ `FText OutErrorText;` — Error text for easy diagnosis

#### class `FCheckIn`  
`class FCheckIn : public FSourceControlOperationBase`  
_L73-126_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to check files into source control
- L77 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L82 _public function_ `virtual FText GetInProgressString() const override`
- L87 _public function_ `void SetDescription( const FText& InDescription )`
- L92 _public function_ `const FText& GetDescription() const`
- L97 _public function_ `void SetSuccessMessage( const FText& InSuccessMessage )`
- L102 _public function_ `const FText& GetSuccessMessage() const`
- L107 _public function_ `void SetKeepCheckedOut( const bool bInKeepCheckedOut )`
- L112 _public function_ `bool GetKeepCheckedOut()`
- L119 _protected member_ `FText Description;` — Description of the checkin
- L122 _protected member_ `FText SuccessMessage;` — A short message listing changelist/revision we submitted, if successful
- L125 _protected member_ `bool bKeepCheckedOut = false;` — Keep files checked-out after checking in

#### class `FCheckOut`  
`class FCheckOut : public FSourceControlOperationBase`  
_L131-144_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to check files out of source control
- L135 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L140 _public function_ `virtual FText GetInProgressString() const override`

#### class `FGetFileList`  
`class FGetFileList : public FSourceControlOperationBase`  
_L149-234_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to get a file list out of source control
- L159 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L164 _public function_ `virtual FText GetInProgressString() const override`
- L169 _public function_ `void SetIncludeDeleted( const bool bInIncludeDeleted )`
- L174 _public function_ `bool GetIncludeDeleted()`
- L179 _public function_ `void SetQuiet(bool bInQuiet)`
- L184 _public function_ `bool ShouldBeQuiet() const`
- L189 _public function_ `void SetMethodUsed(const EGetFileListMethod& InMethodUsed)`
- L194 _public function_ `EGetFileListMethod GetMethodUsed()`
- L199 _public function_ `const TArray<FString>& GetFilesList() const`
- L204 _public function_ `void SetFilesList(TArray<FString>&& InFilesList)`
- L209 _public function_ `const TArray<FString>& GetSearchPatterns() const`
- L214 _public function_ `void SetSearchPattern(const TArray<FString>& InSearchPatterns)`
- L221 _protected member_ `EGetFileListMethod MethodUsed = EGetFileListMethod::FolderSearch;` — Method used to get file list
- L224 _protected member_ `bool bIncludeDeleted = false;` — Include deleted files in the list.
- L227 _protected member_ `bool bForceQuiet = false;` — Force disable any logs generated by that operation.
- L230 _protected member_ `TArray<FString> FilesList;` — Stored result of the operation
- L233 _protected member_ `TArray<FString> SearchPatterns;` — The search patterns for the file list

#### enum `FGetFileList::EGetFileListMethod`  
`enum EGetFileListMethod`  
_L152-156_
- L154 _public enumerator_ `FolderSearch`
- L155 _public enumerator_ `FileRegexSearch` — Note: Only works for Perforce for now

#### class `FMarkForAdd`  
`class FMarkForAdd : public FSourceControlOperationBase`  
_L239-252_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to mark files for add in source control
- L243 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L248 _public function_ `virtual FText GetInProgressString() const override`

#### class `FDelete`  
`class FDelete : public FSourceControlOperationBase`  
_L257-270_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to mark files for delete in source control
- L261 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L266 _public function_ `virtual FText GetInProgressString() const override`

#### class `FRevert`  
`class FRevert : public FSourceControlOperationBase`  
_L275-325_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to revert changes made back to the state they are in source control
- L279 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L284 _public function_ `virtual FText GetInProgressString() const override`
- L289 _public function_ `void SetSoftRevert(const bool bInSoftRevert)`
- L294 _public function_ `bool IsSoftRevert() const`
- L299 _public function_ `void SetRevertAll(const bool bInRevertAll)`
- L304 _public function_ `bool IsRevertAll() const`
- L309 _public function_ `bool ShouldDeleteNewFiles() const`
- L314 _public function_ `const TArray<FString>& GetDeletedFiles() const`
- L316 _public function_ `void AddDeletedFile(const FString& InDeletedFile)`
- L322 _protected member_ `bool bIsSoftRevert = false;`
- L323 _protected member_ `bool bIsRevertAll = false;`
- L324 _protected member_ `TArray<FString> DeletedFiles;`

#### class `FSyncPreview`  
`class FSyncPreview : public FSourceControlOperationBase`  
_L330-396_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to determine the files that would be affected by a sync operation
- L334 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L339 _public function_ `virtual FText GetInProgressString() const override`
- L344 _public function_ `void SetRevision(const FString& InRevision)`
- L349 _public function_ `const FString& GetRevision() const`
- L354 _public function_ `void SetHeadRevisionFlag(const bool bInHeadRevision)`
- L359 _public function_ `bool IsHeadRevisionFlagSet() const`
- L364 _public function_ `void SetTransferSize(const int64 InTransferSize)`
- L369 _public function_ `int64 GetTransferSize() const`
- L374 _public function_ `void SetAffectedFiles(TArray<FString>&& InAffectedFiles)`
- L379 _public function_ `const TArray<FString>& GetAffectedFiles() const`
- L386 _protected member_ `FString Revision;` — Target Revision to which the sync preview refers to
- L389 _protected member_ `bool bHeadRevision = false;` — Flag abstracting if the operation aims to preview a sync to head
- L392 _protected member_ `int64 TransferSize = 0;` — Number of bytes that need to be transferred for the sync operation
- L395 _protected member_ `TArray<FString> AffectedFiles;` — Array of files that would be affected by the sync operation

#### class `FSync`  
`class FSync : public FSourceControlOperationBase`  
_L401-472_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to sync files to the state they are in source control
- L405 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L410 _public function_ `virtual FText GetInProgressString() const override`
- L416 _public function_ `void SetRevisionNumber(int32 InRevisionNumber)` — `UE_DEPRECATED(4.26, "FSync::SetRevisionNumber(int32) has been deprecated. Please update to Fsync::SetRevision(const FString&).")`
- L420 _public function_ `void SetRevision( const FString& InRevision )`
- L425 _public function_ `const FString& GetRevision() const`
- L430 _public function_ `void SetHeadRevisionFlag(const bool bInHeadRevision)`
- L435 _public function_ `bool IsHeadRevisionFlagSet() const`
- L440 _public function_ `void SetForce(const bool bInForce)`
- L445 _public function_ `bool IsForced() const`
- L450 _public function_ `void SetLastSyncedFlag(const bool bInLastSynced)`
- L455 _public function_ `bool IsLastSyncedFlagSet() const`
- L462 _protected member_ `FString Revision;` — Revision to sync to
- L465 _protected member_ `bool bHeadRevision = false;` — Flag abstracting if the operation aims to sync to head
- L468 _protected member_ `bool bLastSynced = false;` — Flag abstracting if the operation aims to force sync to last synced revision
- L471 _protected member_ `bool bForce = false;` — Forces operation, even if the file is already at the wanted revision.

#### class `FUpdateStatus`  
`class FUpdateStatus : public FSourceControlOperationBase`  
_L477-626_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to update the source control status of files
- L480 _public function_ `FUpdateStatus() : bUpdateHistory(false) , bGetOpenedOnly(false) , bUpdateModifiedState(false) , bUpdateModifiedStateToLocalRevision(false) , bCheckingAllFiles(false) , bForceQuiet(false) , bForceUpdate(false) , bSetRequireDirPathEndWithSeparator(false)`
- L493 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L498 _public function_ `virtual FText GetInProgressString() const override`
- L503 _public function_ `void SetUpdateHistory( bool bInUpdateHistory )`
- L508 _public function_ `void SetGetOpenedOnly( bool bInGetOpenedOnly )`
- L513 _public function_ `void SetUpdateModifiedState( bool bInUpdateModifiedState )`
- L518 _public function_ `void SetUpdateModifiedStateToLocalRevision(bool bInUpdateModifiedStateToLocalRevision)`
- L523 _public function_ `void SetCheckingAllFiles( bool bInCheckingAllFiles )`
- L528 _public function_ `void SetQuiet(bool bInQuiet)`
- L544 _public function_ `void SetRequireDirPathEndWithSeparator(bool bFlag)` — Sets the method that the operation will use to determine if a path references a file or a directory. For more details @see IsDirectoryPath() @param bFlag When true the operation will check the path and assume that it is a directory if the path ends with '/' or '\' and a file if it does not. When false (the default) the operation will poll the file system with the path to see if it is a file or a directory.
- L549 _public function_ `void SetForceUpdate(const bool bInForceUpdate)`
- L554 _public function_ `bool ShouldUpdateHistory() const`
- L559 _public function_ `bool ShouldGetOpenedOnly() const`
- L564 _public function_ `bool ShouldUpdateModifiedState() const`
- L569 _public function_ `bool ShouldUpdateModifiedStateToLocalRevision() const`
- L574 _public function_ `bool ShouldCheckAllFiles() const`
- L579 _public function_ `bool ShouldBeQuiet() const`
- L584 _public function_ `bool ShouldForceUpdate() const`
- L600 _public prototype_ `bool IsDirectoryPath(const FString& Path) const;` — Returns if the given path should be considered a directory or not. If bSetRequireDirPathEndWithSeparator is not set (the default) then we will poll the file system. However in some cases this can be very slow, in which case bSetRequireDirPathEndWithSeparator can be set to true and we require that any directory path must be terminated by a path separator (/ or \) so that we can tell by simply looking at the path itself. This is opt in behavior to avoid breaking existing 3rd party code that relies on the default behavior.
- L604 _protected member_ `bool bUpdateHistory;` — Whether to update history
- L607 _protected member_ `bool bGetOpenedOnly;` — Whether to just get files that are opened/edited
- L610 _protected member_ `bool bUpdateModifiedState;` — Whether to update the modified state - expensive
- L613 _protected member_ `bool bUpdateModifiedStateToLocalRevision;` — Whether to update the modified state against local revision - only used when bUpdateModifiedState is true
- L616 _protected member_ `bool bCheckingAllFiles;` — Hint that we are intending on checking all files in the project - some providers can optimize for this
- L619 _protected member_ `bool bForceQuiet;` — Controls whether the operation will trigger an update or not
- L622 _protected member_ `bool bForceUpdate;` — Forces the verification for provided files - providers can ignore files not opened/edited without it
- L625 _protected member_ `bool bSetRequireDirPathEndWithSeparator;` — If we should assume paths ending in a separator are directory paths or do we need to check with the file system?

#### class `FCopy`  
`class FCopy : public FSourceControlOperationBase`  
_L631-681_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to copy a file or directory from one location to another
- L635 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L640 _public function_ `virtual FText GetInProgressString() const override`
- L645 _public function_ `void SetDestination(const FString& InDestination)`
- L650 _public function_ `void SetDestination(FString&& InDestination)`
- L655 _public function_ `const FString& GetDestination() const`
- L673 _public member_ `ECopyMethod CopyMethod = ECopyMethod::Branch;` — Whether a relationship to the original file should be maintained
- L676 _public member_ `EResolveMethod ResolveMethod = EResolveMethod::AcceptTarget;` — The current state of the destination file
- L680 _protected member_ `FString Destination;` — Destination path of the copy operation

#### enum `FCopy::ECopyMethod`  
`enum class ECopyMethod`  
_L660-664_
- L662 _public enumerator_ `Branch` — The new file is branched from the original file
- L663 _public enumerator_ `Add` — The new file has no relation to the original file

#### enum `FCopy::EResolveMethod`  
`enum class EResolveMethod`  
_L666-670_
- L668 _public enumerator_ `AcceptTarget` — Resolve by accepting the destination file from the copy operation
- L669 _public enumerator_ `AcceptSource` — Resolve by accepting the source file from the copy operation

#### class `FResolve`  
`class FResolve : public FSourceControlOperationBase`  
_L686-699_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to resolve a file that is in a conflicted state.
- L690 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L695 _public function_ `virtual FText GetInProgressString() const override`

#### class `FGetPendingChangelists`  
`class FGetPendingChangelists : public FSourceControlOperationBase`  
_L704-717_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to retrieve pending changelist(s).
- L708 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L713 _public function_ `virtual FText GetInProgressString() const override`

#### class `FGetSubmittedChangelists`  
`class FGetSubmittedChangelists : public FSourceControlOperationBase`  
_L722-841_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to retrieve submitted changelist(s).
- L726 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L731 _public function_ `virtual FText GetInProgressString() const override`
- L737 _public function_ `void SetDateFromFilter(const FDateTime& InDateFrom)`
- L742 _public function_ `void SetDateToFilter(const FDateTime& InDateTo)`
- L747 _public function_ `void SetOwnedFilter(bool InOwned)`
- L752 _public function_ `void SetPaginationLimit(int32 InLimit)`
- L760 _public function_ `void SetPaginationOffset(int32 InOffset)`
- L768 _public function_ `bool ShouldFilterByDateFrom(FDateTime& OutDateFrom)`
- L778 _public function_ `bool ShouldFilterByDateTo(FDateTime& OutDateTo)`
- L788 _public function_ `bool ShouldFilterByOwned()`
- L793 _public function_ `bool ShouldUsePaginationLimit(int32& OutPaginationLimit)`
- L803 _public function_ `bool ShouldUsePaginationOffset(int32& OutPaginationOffset)`
- L814 _public function_ `void SetBranch(const FString& InBranch)`
- L819 _public function_ `const FString& GetBranch()`
- L824 _public function_ `const TArray<FSourceControlChangelistRef>& GetSubmittedChangelists() const`
- L826 _public function_ `void AddSubmittedChangelist(FSourceControlChangelistRef Changelist)`
- L832 _private member_ `FDateTime DateFrom = FDateTime::MinValue();`
- L833 _private member_ `FDateTime DateTo = FDateTime::MinValue();`
- L834 _private member_ `bool Owned = false;`
- L835 _private member_ `FString Branch;`
- L837 _private member_ `int32 PaginationLimit = -1;`
- L838 _private member_ `int32 PaginationOffset = -1;`
- L840 _private member_ `TArray<FSourceControlChangelistRef> Changelists;`

#### class `FGetChangelistDetails`  
`class FGetChangelistDetails : public FSourceControlOperationBase`  
_L847-894_
- inherits: `FSourceControlOperationBase`
- desc: This operations query the source control to extract all the details available for a given changelist. The operations returns a collection of key/value corresponding to the details available. The list of key/value is specific to the source control implementation.
- L850 _public prototype_ `FGetChangelistDetails() = default;`
- L852 _public function_ `explicit FGetChangelistDetails(FString&& InChangelistNumber) : ChangelistNumber(MoveTemp(InChangelistNumber))`
- L858 _public function_ `explicit FGetChangelistDetails(FStringView InChangelistNumber) : ChangelistNumber(InChangelistNumber)`
- L864 _public prototype_ `virtual ~FGetChangelistDetails() = default;`
- L867 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L872 _public function_ `virtual FText GetInProgressString() const override`
- L877 _public function_ `const FString& GetChangelistNumber()`
- L879 _public function_ `const TArray<TMap<FString, FString>>& GetChangelistDetails()`
- L881 _public function_ `void SetChangelistNumber(const FString& InChangelistNumber)`
- L886 _public function_ `void SetChangelistDetails(TArray<TMap<FString, FString>>&& InChangelistDetails)`
- L892 _private member_ `FString ChangelistNumber;`
- L893 _private member_ `TArray<TMap<FString, FString>> OutChangelistDetails;`

#### class `FUpdatePendingChangelistsStatus`  
`class FUpdatePendingChangelistsStatus : public FSourceControlOperationBase`  
_L899-967_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to update the source control status of changelist(s)
- L902 _public function_ `void SetUpdateFilesStates(bool bInUpdateFilesStates)`
- L907 _public function_ `bool ShouldUpdateFilesStates() const`
- L912 _public function_ `void SetUpdateShelvedFilesStates(bool bInUpdateShelvedFilesStates)`
- L917 _public function_ `bool ShouldUpdateShelvedFilesStates() const`
- L922 _public function_ `void SetUpdateAllChangelists(bool bInUpdateAllChangelists)`
- L928 _public function_ `bool ShouldUpdateAllChangelists() const`
- L933 _public function_ `void SetChangelistsToUpdate(const TArray<FSourceControlChangelistRef>& InChangelistsToUpdate)`
- L939 _public function_ `void SetChangelistsToUpdate(const TArrayView<FSourceControlChangelistRef>& InChangelistsToUpdate)`
- L945 _public function_ `const TArray<FSourceControlChangelistRef>& GetChangelistsToUpdate() const`
- L951 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L956 _public function_ `virtual FText GetInProgressString() const override`
- L962 _private member_ `bool bUpdateFilesStates = false;`
- L963 _private member_ `bool bUpdateShelvedFilesStates = false;`
- L964 _private member_ `bool bUpdateAllChangelists = false;`
- L966 _private member_ `TArray<FSourceControlChangelistRef> ChangelistsToUpdate;`

#### class `FNewChangelist`  
`class FNewChangelist : public FSourceControlOperationBase`  
_L972-1009_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to create a new changelist
- L975 _public function_ `virtual FName GetName() const override`
- L980 _public function_ `virtual FText GetInProgressString() const override`
- L985 _public function_ `void SetDescription(const FText& InDescription)`
- L990 _public function_ `const FText& GetDescription() const`
- L995 _public function_ `void SetNewChangelist(FSourceControlChangelistPtr InNewChangelist)`
- L1000 _public function_ `const FSourceControlChangelistPtr& GetNewChangelist() const`
- L1007 _protected member_ `FText Description;` — Description of the changelist
- L1008 _protected member_ `FSourceControlChangelistPtr NewChangelist;`

#### class `FDeleteChangelist`  
`class FDeleteChangelist : public FSourceControlOperationBase`  
_L1014-1026_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to delete an empty changelist
- L1017 _public function_ `virtual FName GetName() const override`
- L1022 _public function_ `virtual FText GetInProgressString() const override`

#### class `FEditChangelist`  
`class FEditChangelist : public FSourceControlOperationBase`  
_L1031-1057_
- inherits: `FSourceControlOperationBase`
- desc: Operation to change the description of a changelist
- L1034 _public function_ `virtual FName GetName() const override`
- L1039 _public function_ `virtual FText GetInProgressString() const override`
- L1044 _public function_ `void SetDescription(const FText& InDescription)`
- L1049 _public function_ `const FText& GetDescription() const`
- L1056 _protected member_ `FText Description;` — Description of the changelist

#### class `FRevertUnchanged`  
`class FRevertUnchanged : public FSourceControlOperationBase`  
_L1062-1074_
- inherits: `FSourceControlOperationBase`
- desc: Operation to revert unchanged file(s) or all unchanged files in a changelist
- L1065 _public function_ `virtual FName GetName() const override`
- L1070 _public function_ `virtual FText GetInProgressString() const override`

#### class `FMoveToChangelist`  
`class FMoveToChangelist : public FSourceControlOperationBase`  
_L1079-1092_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to move files between changelists
- L1083 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L1088 _public function_ `virtual FText GetInProgressString() const override`

#### class `FShelve`  
`class FShelve : public FSourceControlOperationBase`  
_L1097-1124_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to shelve files in a changelist
- L1101 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L1106 _public function_ `virtual FText GetInProgressString() const override`
- L1111 _public function_ `void SetDescription(const FText& InDescription)`
- L1116 _public function_ `const FText& GetDescription() const`
- L1123 _private member_ `FText Description;` — Description of the changelist, will be used only to create a new changelist when needed

#### class `FUnshelve`  
`class FUnshelve : public FSourceControlOperationBase`  
_L1129-1142_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to unshelve files from a changelist
- L1133 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L1138 _public function_ `virtual FText GetInProgressString() const override`

#### class `FDeleteShelved`  
`class FDeleteShelved : public FSourceControlOperationBase`  
_L1147-1160_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to delete shelved files from a changelist
- L1151 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L1156 _public function_ `virtual FText GetInProgressString() const override`

#### class `FDownloadFile`  
`class FDownloadFile : public FSourceControlOperationBase`  
_L1166-1261_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to download a file from the source control server directly rather than sync it. This should not change the state of anything locally on the client.
- L1181 _public prototype_ `FDownloadFile() = default;` — This version of FDownloadFile will download the files and keep them in memory, which can then be accessed by calling ::GetFileData.
- L1184 _public function_ `FDownloadFile(EVerbosity InVerbosity)`
- L1194 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L1200 _public function_ `virtual FText GetInProgressString() const override` — ISourceControlOperation interface
- L1206 _public function_ `virtual bool CanBeCalledFromBackgroundThreads() const override` — ISourceControlOperation interface
- L1213 _public prototype_ `FDownloadFile(FStringView InTargetDirectory, EVerbosity InVerbosity);` — `UE_DEPRECATED(5.6, "Enum has been removed, use the overload without InVerbosity instead")`
- L1217 _public prototype_ `FDownloadFile(FStringView InTargetDirectory);` — This version of FDownloadFile will download the files to the given target directory
- L1224 _public function_ `FString GetTargetDirectory() const` — Returns the directory that the files will (or have) been downloaded to. This path will be empty if no target directory was given, in which case the files can be accessed via the ::GetFileData method.
- L1234 _public prototype_ `FSharedBuffer GetFileData(const FStringView& Filename);` — If no target directory was given to download the files too then the command will keep the files in memory which can be accessed via this method. If the file failed to download then a null FSharedBuffer will be returned.
- L1237 _public function_ `bool ShouldLogToStdOutput() const` — Return true if the command should log its operations, otherwise false
- L1246 _public function_ `void __Internal_AddFileData(const FString& Filename, FSharedBuffer FileData)` — Do not call outside of source control implementations. Used to add the file in memory once downloaded so that the caller can get access to it.
- L1252 _public function_ `void AddFileData(const FString& Filename, FSharedBuffer FileData)` — `UE_DEPRECATED(5.3, "Replaced by __Internal_AddFileData but you shouldn't be calling this anyway")`
- L1259 _private member_ `FString TargetDirectory;`
- L1260 _private member_ `TMap<FString, FSharedBuffer> FileDataMap;`

#### enum `FDownloadFile::EVerbosity`  
`enum class UE_DEPRECATED(5.6, "Enum has been removed, call FSourceControlOperationBase::SetEnableErrorLogging directly instead") EVerbosity`  
_L1169-1175_
- L1172 _public enumerator_ `None` — No logging when the command is run.
- L1174 _public enumerator_ `Full` — Log the full cmdline when the command is run.

#### class `FGetSourceControlRevisionInfo`  
`class FGetSourceControlRevisionInfo : public FSourceControlOperationBase`  
_L1266-1326_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to get info about file(s) at a revision. CL number, datetime, and author will be returned.
- L1270 _public prototype_ `FGetSourceControlRevisionInfo() = default;`
- L1273 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L1279 _public function_ `virtual FText GetInProgressString() const override` — ISourceControlOperation interface
- L1285 _public function_ `virtual bool CanBeCalledFromBackgroundThreads() const override` — ISourceControlOperation interface
- L1291 _public function_ `bool ShouldLogToStdOutput() const` — Return true if the command should log its operations, otherwise false
- L1296 _public function_ `FString GetChangelist() const`
- L1301 _public function_ `FDateTime GetDateTime() const`
- L1306 _public function_ `FString GetAuthor() const`
- L1315 _public function_ `void InternalSetResults(const FString& InChangelist, const FDateTime& InDateTime, const FString& InAuthor)` — Do not call outside of source control implementations. Used to add the results so that the caller can get access to it.
- L1323 _private member_ `FString Changelist;`
- L1324 _private member_ `FDateTime DateTime;`
- L1325 _private member_ `FString Author;`

#### class `FCreateWorkspace`  
`class FCreateWorkspace : public FSourceControlOperationBase`  
_L1331-1445_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to create a new workspace if the source control system supports this functionality.
- L1344 _public typedef_ `using FClientViewMapping = TPair<FString,FString>;`
- L1346 _public prototype_ `FCreateWorkspace() = delete;`
- L1354 _public prototype_ `FCreateWorkspace(FStringView WorkspaceName, FStringView WorkspaceRoot);` — Constructor @param WorkspaceName	The name of the workspace to create @param WorkspaceRoom	The file path to the workspace root (can be relative to the project)
- L1357 _public function_ `void SetDescription(FStringView Desciption)` — Set the description to be used by the workspace, if left unset then the default description will be used
- L1363 _public function_ `void SetStream(FStringView Stream)` — Set the stream to be used by the workspace, if left unset then a classic depot with ClientView will be used
- L1375 _public function_ `void AddNativeClientViewMapping(FStringView DepotPath, FStringView ClientPath)` — Add a new mapping for the client spec in the native format of the current source control provider. These will be written to the client spec in the order that they are added. @param DepotPath		The path in the source control depot to map from @param ClientPath	The path on the local client to map too
- L1381 _public function_ `void ClearClientViewMappings()` — Remove all currently set client-view mappings
- L1387 _public function_ `void SetType(EType InType)` — Set the type of workspace to be created. @see FCreateWorkspace::EType
- L1392 _public function_ `const FString& GetWorkspaceName() const`
- L1397 _public function_ `const FString& GetWorkspaceRoot() const`
- L1402 _public function_ `const FString& GetWorkspaceDescription() const`
- L1407 _public function_ `const FString& GetWorkspaceStream() const`
- L1412 _public function_ `const TArray<FClientViewMapping> GetClientView() const`
- L1417 _public function_ `EType GetType() const`
- L1424 _public function_ `virtual FName GetName() const override`
- L1429 _public function_ `virtual FText GetInProgressString() const override`
- L1436 _protected member_ `FString WorkspaceName;`
- L1437 _protected member_ `FString WorkspaceRoot;`
- L1439 _protected member_ `FString WorkspaceDescription;`
- L1440 _protected member_ `FString WorkspaceStream;`
- L1442 _protected member_ `EType Type = EType::Writeable;`
- L1444 _protected member_ `TArray<FClientViewMapping> ClientView;`

#### enum `FCreateWorkspace::EType`  
`enum class EType`  
_L1334-1342_
- L1337 _public enumerator_ `Writeable = 0` — Default
- L1339 _public enumerator_ `ReadOnly` — Has a short life span and can only query/read/sync files
- L1341 _public enumerator_ `Partitioned` — Has a short life span but is allowed full functionality

#### class `FDeleteWorkspace`  
`class FDeleteWorkspace : public FSourceControlOperationBase`  
_L1448-1484_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to delete a workspace
- L1451 _public prototype_ `FDeleteWorkspace() = delete;`
- L1458 _public function_ `FDeleteWorkspace(FStringView InWorkspaceName) : WorkspaceName(InWorkspaceName)` — Constructor @param InWorkspaceName The name of the workspace to be deleted
- L1464 _public function_ `const FString& GetWorkspaceName() const`
- L1471 _public function_ `virtual FName GetName() const override`
- L1476 _public function_ `virtual FText GetInProgressString() const override`
- L1483 _protected member_ `FString WorkspaceName;`

#### struct `FScWorkspaceInfo`  
`struct FScWorkspaceInfo`  
_L1487-1491_
- desc: Information on a source control workspace
- L1489 _public member_ `FString Name;`
- L1490 _public member_ `FString RootDir;`

#### class `FGetWorkspaces`  
`class FGetWorkspaces : public FSourceControlOperationBase`  
_L1496-1508_
- inherits: `FSourceControlOperationBase`
- desc: Operation used to get all workspaces for the current host if the source control system supports this functionality.
- L1500 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L1507 _public member_ `TArray<FScWorkspaceInfo> Results;` — Output array of workspace info

#### class `FGetFile`  
`class FGetFile : public FSourceControlOperationBase`  
_L1513-1558_
- inherits: `FSourceControlOperationBase`
- desc: This operation uses p4v print command to get file from specified depot by shelved changelist or file revision returns a package filename
- L1517 _public function_ `FGetFile(const FString& InChangelistNumber, const FString& InRevisionNumber, const FString& InDepotFilePath, bool bInIsShelve = false) : ChangelistNumber(InChangelistNumber) , RevisionNumber(InRevisionNumber) , DepotFilePath(InDepotFilePath) , bIsShelve(bInIsShelve)`
- L1525 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L1530 _public function_ `virtual FText GetInProgressString() const override`
- L1535 _public function_ `const FString& GetChangelistNumber() const`
- L1537 _public function_ `const FString& GetRevisionNumber() const`
- L1539 _public function_ `const FString& GetDepotFilePath() const`
- L1541 _public function_ `bool IsShelve() const`
- L1543 _public function_ `const FString& GetOutPackageFilename() const`
- L1545 _public function_ `void SetOutPackageFilename(const FString& InOutPackageFilename)`
- L1552 _private member_ `FString ChangelistNumber;`
- L1553 _private member_ `FString RevisionNumber;`
- L1554 _private member_ `FString DepotFilePath;`
- L1555 _private member_ `bool bIsShelve;`
- L1557 _private member_ `FString OutPackageFilename;`

#### class `FWhere`  
`class FWhere : public FSourceControlOperationBase`  
_L1564-1589_
- inherits: `FSourceControlOperationBase`
- desc: This operation will get info about the location of a file within a source control provider. The input can be a local or remote path and the result contain both local and remote paths
- L1574 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L1579 _public function_ `virtual FText GetInProgressString() const override`
- L1584 _public function_ `void SetFiles(TArray<FileInfo>&& InFiles)`
- L1585 _public function_ `const TArray<FileInfo>& GetFiles() const`
- L1588 _private member_ `TArray<FileInfo> Files;`

#### struct `FWhere::FileInfo`  
`struct FileInfo`  
_L1567-1571_
- L1569 _public member_ `FString LocalPath;`
- L1570 _public member_ `FString RemotePath;`

#### class `FSave`  
`class FSave : public FSourceControlOperationBase`  
_L1594-1607_
- inherits: `FSourceControlOperationBase`
- desc: This operation will save files into revision control without actually doing a check-in
- L1598 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L1603 _public function_ `virtual FText GetInProgressString() const override`

#### Free symbols / members of external scopes

- L23 _macro_ `#define LOCTEXT_NAMESPACE "SourceControl"`

### `Source/Developer/SourceControl/Public/SourceControlPreferences.h` (Public)


#### class `USourceControlPreferences`  
`class USourceControlPreferences : public UDeveloperSettings`  
_L23-64_
- reflection: `UCLASS(MinimalAPI, config = Editor, defaultconfig, meta = (DisplayName = "Revision Control", Keywords = "Source Control"))`
- inherits: `UDeveloperSettings`
- desc: Settings for the Source Control Integration
- L29 _public prototype_ `static bool IsValidationTagEnabled();` — Helper to access easily Enable Validation Tag setting
- L32 _public prototype_ `static bool ShouldDeleteNewFilesOnRevert();` — Helper to access easily Should Delete New Files On Revert setting
- L35 _public prototype_ `static bool AreUncontrolledChangelistsEnabled();` — Helper to access easily Enable Uncontrolled Changelists setting
- L38 _public prototype_ `static bool RequiresRevisionControlToRenameLocalizableAssets();` — Helper to access easily Requires Revision Control To Rename Localizable Assets setting
- L43 _public member_ `bool bEnableValidationTag = true;` — `UPROPERTY(config, EditAnywhere, Category = SourceControl, meta = (ToolTip = "Adds validation tag to changelist description on submit."))` — If enabled, adds a tag in changelist descriptions when they are validated
- L47 _public member_ `bool bShouldDeleteNewFilesOnRevert = true;` — `UPROPERTY(config, EditAnywhere, Category = SourceControl, meta = (ToolTip = "Deletes new files when reverted."))` — If enabled, deletes new files when reverted.
- L51 _public member_ `bool bEnableUncontrolledChangelists = true;` — `UPROPERTY(config, EditAnywhere, Category = SourceControl, meta = (ToolTip = "Enables Uncontrolled Changelists features. The editor must be restarted for the change to be fully taken into account.", ConfigRestartRequired = true))` — Enables Uncontrolled Changelists features.
- L55 _public member_ `TArray<FString> CollectionChangelistTags;` — `UPROPERTY(config, EditAnywhere, Category = SourceControl)` — List of lines to add to any collection on checkin
- L59 _public member_ `TMap<FName, FString> SpecificCollectionChangelistTags;` — `UPROPERTY(config, EditAnywhere, Category = SourceControl, meta=(MultiLine=true))` — Map of collection names and additional text to apply to changelist descriptions when checking them in
- L63 _public member_ `bool bRequiresRevisionControlToRenameLocalizableAssets = false;` — `UPROPERTY(config, EditAnywhere, DisplayName = "Requires Revision Control To Manage Localizable Assets", Category = Internationalization, meta = (ToolTip = "If the project uses Localization and its localized content might not be on disk (but still in your Revision Control), then enabling this feature will require a Revision Control Provider to be configured to move/rename/delete files to be sure no localized variants become orphaned. (Works only with Perforce for now)"))` — Revision Control is a requirement to move/rename/delete localizable assets

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API SOURCECONTROL_API`

### `Source/Developer/SourceControl/Public/SourceControlProviders.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace SourceControlProviders`
- L10 _function_ `static const TCHAR* GetDefaultProviderName()` (scope `SourceControlProviders`) — Returns the default SourceControl provider name, which is the one indicating 'disabled'.
- L16 _function_ `static const TCHAR* GetUrcProviderName()` (scope `SourceControlProviders`) — Returns the URC SourceControl provider name
- L22 _function_ `static const TCHAR* GetLegacySkeinProviderName()` (scope `SourceControlProviders`) — Returns the old Skein SourceControl provider name
- L28 _function_ `static const TCHAR* GetPerforceProviderName()` (scope `SourceControlProviders`) — Returns the Perforce SourceControl provider name

### `Source/Developer/SourceControl/Public/SourceControlResultInfo.h` (Public)


#### struct `FSourceControlResultInfo`  
`struct FSourceControlResultInfo`  
_L12-57_
- desc: Accumulated error and info messages for a source control operation.
- L23 _public prototype_ `FRIEND_ENUM_CLASS_FLAGS(EAdditionalErrorContext);`
- L26 _public function_ `void Append(const FSourceControlResultInfo& InResultInfo)` — Append any messages from another FSourceControlResultInfo, ensuring to keep any already accumulated info.
- L35 _public prototype_ `void OnConnectionFailed();`
- L36 _public prototype_ `void OnConnectionDroped();`
- L38 _public prototype_ `bool DidConnectionFail() const;`
- L40 _public function_ `bool HasErrors() const`
- L46 _public member_ `TArray<FText> InfoMessages;` — Info and/or warning message storage
- L49 _public member_ `TArray<FText> ErrorMessages;` — Potential error message storage
- L52 _public member_ `TArray<FString> Tags;` — Additional arbitrary information attached to the command
- L56 _private member_ `EAdditionalErrorContext AdditionalErrorContext = EAdditionalErrorContext::None;` — Contains additional info about any errors encountered

#### enum `FSourceControlResultInfo::EAdditionalErrorContext`  
`enum class EAdditionalErrorContext : uint32`  
_L14-21_
- L16 _public enumerator_ `None = 0`
- L18 _public enumerator_ `ConnectionFailed = 1 << 0` — A connection to the server could not be established
- L20 _public enumerator_ `ConnectionDropped = 1 << 1` — The connection to the server dropped before the operation could be completed

#### Free symbols / members of external scopes

- L59 _prototype_ `ENUM_CLASS_FLAGS(FSourceControlResultInfo::EAdditionalErrorContext);`
