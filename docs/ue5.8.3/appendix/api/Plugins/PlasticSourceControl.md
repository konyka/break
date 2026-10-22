# Plugins / PlasticSourceControl

- module root: `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl`
- headers: 40; symbols: 1350
- symbol kinds: class=85, delegate=1, enum=2, enumerator=16, function=110, member=332, namespace=30, prototype=722, struct=3, typedef=39, variable=10
- PrivateDependencyModuleNames: AssetRegistry, ContentBrowser, Core, CoreUObject, DesktopPlatform, DeveloperSettings, Engine, InputCore, LevelEditor, Projects, Slate, SlateCore, SourceControl, SourceControlWindows, ToolMenus, UnrealEd, XmlParser

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/IPlasticSourceControlWorker.h` (Private)


#### class `IPlasticSourceControlWorker`  
`class IPlasticSourceControlWorker`  
_L9-51_
- L13 _public prototype_ `static void RegisterWorkers(FPlasticSourceControlProvider& PlasticSourceControlProvider);` — Implemented in PlasticSourceControlOperations.cpp with all the code for the workers
- L16 _public function_ `explicit IPlasticSourceControlWorker(FPlasticSourceControlProvider& InSourceControlProvider) : PlasticSourceControlProvider(InSourceControlProvider)`
- L21 _public prototype_ `virtual ~IPlasticSourceControlWorker() = default;`
- L23 _public function_ `FPlasticSourceControlProvider& GetProvider()`
- L28 _public function_ `const FPlasticSourceControlProvider& GetProvider() const`
- L36 _public prototype_ `virtual FName GetName() const = 0;` — Name describing the work that this worker does. Used for factory method hookup.
- L41 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) = 0;` — Function that actually does the work. Can be executed on another thread.
- L47 _public prototype_ `virtual bool UpdateStates() = 0;` — Updates the state of any items after completion (if necessary). This is always executed on the main thread. @returns true if states were updated
- L50 _private member_ `FPlasticSourceControlProvider& PlasticSourceControlProvider;`

#### Free symbols / members of external scopes

- L53 _typedef_ `typedef TSharedRef<IPlasticSourceControlWorker, ESPMode::ThreadSafe> FPlasticSourceControlWorkerRef;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/Notification.h` (Private)


#### class `FNotification`  
`class FNotification`  
_L12-39_
- L17 _public prototype_ `void DisplayInProgress(const FText& InOperationInProgressString);` — Create and display (resp. expire and remove) an in-progress notification for a long-running operation Note: UI main thread only
- L18 _public prototype_ `void RemoveInProgress();`
- L20 _public function_ `bool IsInProgress() const`
- L27 _public prototype_ `static void DisplayResult(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Display a short fire-and-forget notification Note: thread safe methods of queuing a notification from any thread
- L28 _public prototype_ `static void DisplayResult(const FSourceControlOperationBase& InOperation, ECommandResult::Type InResult);`
- L30 _public prototype_ `static void DisplaySuccess(const FSourceControlOperationBase& InOperation);`
- L31 _public prototype_ `static void DisplaySuccess(const FText& InNotificationText);`
- L33 _public prototype_ `static void DisplayFailure(const FSourceControlOperationBase& InOperation);`
- L34 _public prototype_ `static void DisplayFailure(const FText& InNotificationText);`
- L38 _private member_ `TWeakPtr<class SNotificationItem> OperationInProgress;` — Current long-running notification if any

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PackageUtils.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace PackageUtils`
- L10 _prototype_ `TArray<FString> AssetDataToFileNames(const TArray<FAssetData>& InAssetObjectPaths);` (scope `PackageUtils`)
- L12 _prototype_ `bool SaveDirtyPackages();` (scope `PackageUtils`)
- L13 _prototype_ `TArray<FString> ListAllPackages();` (scope `PackageUtils`)
- L15 _prototype_ `void UnlinkPackages(const TArray<FString>& InFiles);` (scope `PackageUtils`)
- L16 _prototype_ `void UnlinkPackagesInMainThread(const TArray<FString>& InFiles);` (scope `PackageUtils`)
- L18 _prototype_ `void ReloadPackages(const TArray<FString>& InFiles);` (scope `PackageUtils`)
- L19 _prototype_ `void ReloadPackagesInMainThread(const TArray<FString>& InFiles);` (scope `PackageUtils`)

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlBranch.h` (Private)


#### class `FPlasticSourceControlBranch`  
`class FPlasticSourceControlBranch`  
_L7-22_
- L10 _public member_ `FString Name;`
- L11 _public member_ `FString Repository;`
- L12 _public member_ `FString CreatedBy;`
- L13 _public member_ `FDateTime Date;`
- L14 _public member_ `FString Comment;`
- L16 _public function_ `void PopulateSearchString(TArray<FString>& OutStrings) const`

#### Free symbols / members of external scopes

- L24 _typedef_ `typedef TSharedRef<class FPlasticSourceControlBranch, ESPMode::ThreadSafe> FPlasticSourceControlBranchRef;`
- L25 _typedef_ `typedef TSharedPtr<class FPlasticSourceControlBranch, ESPMode::ThreadSafe> FPlasticSourceControlBranchPtr;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlBranchesWindow.h` (Private)


#### class `FPlasticSourceControlBranchesWindow`  
`class FPlasticSourceControlBranchesWindow`  
_L8-20_
- desc: Nomad tab window to hold the widget with the list of branches, see SPlasticSourceControlBranchesWidget
- L11 _public prototype_ `void Register();`
- L12 _public prototype_ `void Unregister();`
- L14 _public prototype_ `void OpenTab();`
- L17 _private prototype_ `TSharedRef<class SDockTab> OnSpawnTab(const class FSpawnTabArgs& SpawnTabArgs);`
- L19 _private prototype_ `TSharedPtr<class SWidget> CreateBranchesWidget();`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlChangelist.h` (Private)


#### class `FPlasticSourceControlChangelist`  
`class FPlasticSourceControlChangelist : public ISourceControlChangelist`  
_L12-80_
- inherits: `ISourceControlChangelist`
- desc: Unique Identifier of a changelist under source control: a "name" in Unity Version Control
- L15 _public prototype_ `FPlasticSourceControlChangelist() = default;`
- L17 _public function_ `explicit FPlasticSourceControlChangelist(FString&& InChangelistName, const bool bInInitialized = false) : ChangelistName(MoveTemp(InChangelistName)) , bInitialized(bInInitialized)`
- L23 _public function_ `virtual bool CanDelete() const override`
- L28 _public function_ `bool operator==(const FPlasticSourceControlChangelist& InOther) const`
- L33 _public function_ `bool operator!=(const FPlasticSourceControlChangelist& InOther) const`
- L38 _public function_ `virtual bool IsDefault() const override`
- L43 _public function_ `void SetInitialized()`
- L48 _public function_ `bool IsInitialized() const`
- L53 _public function_ `void Reset()`
- L64 _public function_ `FString GetName() const`
- L69 _public function_ `virtual FString GetIdentifier() const override`
- L75 _public member_ `static const FPlasticSourceControlChangelist DefaultChangelist;`
- L78 _private member_ `FString ChangelistName;`
- L79 _private member_ `bool bInitialized = false;`

#### Free symbols / members of external scopes

- L59 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FPlasticSourceControlChangelist& InPlasticChangelist)`
- L82 _typedef_ `typedef TSharedRef<class FPlasticSourceControlChangelist, ESPMode::ThreadSafe> FPlasticSourceControlChangelistRef;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlChangelistState.h` (Private)


#### class `FPlasticSourceControlChangelistState`  
`class FPlasticSourceControlChangelistState : public ISourceControlChangelistState`  
_L15-88_
- inherits: `ISourceControlChangelistState`
- desc: The state of a pending changelist under source control: description and list of files
- L18 _public function_ `explicit FPlasticSourceControlChangelistState(const FPlasticSourceControlChangelist& InChangelist, const FString& InDescription = FString()) : Changelist(InChangelist) , Description(InDescription)`
- L24 _public function_ `explicit FPlasticSourceControlChangelistState(FPlasticSourceControlChangelist&& InChangelist, FString&& InDescription) : Changelist(MoveTemp(InChangelist)) , Description(MoveTemp(InDescription))`
- L34 _public prototype_ `virtual FName GetIconName() const override;` — Get the name of the icon graphic we should use to display the state in a UI. @returns the name of the icon to display
- L40 _public prototype_ `virtual FName GetSmallIconName() const override;` — Get the name of the small icon graphic we should use to display the state in a UI. @returns the name of the icon to display
- L46 _public prototype_ `virtual FText GetDisplayText() const override;` — Get a text representation of the state @returns	the text to display for this state
- L52 _public prototype_ `virtual FText GetDescriptionText() const override;` — Get a text representation of the state @returns	the text to display for this state
- L58 _public prototype_ `virtual FText GetDisplayTooltip() const override;` — Get a tooltip to describe this state @returns	the text to display for this states tooltip
- L64 _public prototype_ `virtual const FDateTime& GetTimeStamp() const override;` — Get the timestamp of the last update that was made to this state. @returns	the timestamp of the last update
- L66 _public prototype_ `virtual const TArray<FSourceControlStateRef> GetFilesStates() const override;`
- L67 _public prototype_ `virtual int32 GetFilesStatesNum() const override;`
- L69 _public prototype_ `virtual const TArray<FSourceControlStateRef> GetShelvedFilesStates() const override;`
- L70 _public prototype_ `virtual int32 GetShelvedFilesStatesNum() const override;`
- L72 _public prototype_ `virtual FSourceControlChangelistRef GetChangelist() const override;`
- L75 _public member_ `FPlasticSourceControlChangelist Changelist;`
- L77 _public member_ `FString Description;`
- L79 _public member_ `TArray<FSourceControlStateRef> Files;`
- L81 _public member_ `int32 ShelveId = ISourceControlState::INVALID_REVISION;`
- L82 _public member_ `FDateTime ShelveDate;`
- L84 _public member_ `TArray<FSourceControlStateRef> ShelvedFiles;`
- L87 _public member_ `FDateTime TimeStamp;` — The timestamp of the last update

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlChangeset.h` (Private)


#### class `FPlasticSourceControlChangeset`  
`class FPlasticSourceControlChangeset`  
_L9-26_
- L12 _public member_ `int32 ChangesetId;`
- L13 _public member_ `FString CreatedBy;`
- L14 _public member_ `FDateTime Date;`
- L15 _public member_ `FString Comment;`
- L16 _public member_ `FString Branch;`
- L18 _public member_ `TArray<FPlasticSourceControlStateRef> Files;` — Note: array of file States, each with one Revision for Diffing (like for Files and ShelvedFiles in FPlasticSourceControlChangelist)
- L20 _public function_ `void PopulateSearchString(TArray<FString>& OutStrings) const`

#### Free symbols / members of external scopes

- L28 _typedef_ `typedef TSharedRef<class FPlasticSourceControlChangeset, ESPMode::ThreadSafe> FPlasticSourceControlChangesetRef;`
- L29 _typedef_ `typedef TSharedPtr<class FPlasticSourceControlChangeset, ESPMode::ThreadSafe> FPlasticSourceControlChangesetPtr;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlChangesetsWindow.h` (Private)


#### class `FPlasticSourceControlChangesetsWindow`  
`class FPlasticSourceControlChangesetsWindow`  
_L8-20_
- desc: Nomad tab window to hold the widget with the list of Changesets, see SPlasticSourceControlChangesetsWidget
- L11 _public prototype_ `void Register();`
- L12 _public prototype_ `void Unregister();`
- L14 _public prototype_ `void OpenTab();`
- L17 _private prototype_ `TSharedRef<class SDockTab> OnSpawnTab(const class FSpawnTabArgs& SpawnTabArgs);`
- L19 _private prototype_ `TSharedPtr<class SWidget> CreateChangesetsWidget();`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlCommand.h` (Private)


#### class `FPlasticSourceControlCommand`  
`class FPlasticSourceControlCommand : public IQueuedWork`  
_L15-103_
- inherits: `IQueuedWork`
- desc: Used to execute Plastic commands multi-threaded.
- L18 _public prototype_ `FPlasticSourceControlCommand(const FSourceControlOperationRef& InOperation, const FPlasticSourceControlWorkerRef& InWorker, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() );`
- L24 _public prototype_ `bool DoWork();` — This is where the real thread work is done. All work that is done for this queued object should be done from within the call to this function.
- L32 _public prototype_ `virtual void Abandon() override;` — Tells the queued work that it is being abandoned so that it can do per object clean up as needed. This will only be called if it is being abandoned before completion. NOTE: This requires the object to delete itself using whatever heap it was allocated in.
- L38 _public prototype_ `virtual void DoThreadedWork() override;` — This method is also used to tell the object to cleanup but not before the object has finished it's work.
- L41 _public prototype_ `ECommandResult::Type ReturnResults();` — Save any results and call any registered callbacks.
- L45 _public member_ `FString PathToWorkspaceRoot;` — Path to the root of the Plastic workspace: can be the GameDir itself, or any parent directory (found by the "Connect" operation)
- L48 _public member_ `FSourceControlOperationRef Operation;` — Operation we want to perform - contains outward-facing parameters & results
- L51 _public member_ `FPlasticSourceControlWorkerRef Worker;` — The object that will actually do the work
- L54 _public member_ `FSourceControlOperationComplete OperationCompleteDelegate;` — Delegate to notify when this operation completes
- L57 _public member_ `volatile int32 bExecuteProcessed;` — If true, this command has been processed by the source control thread
- L60 _public member_ `bool bCommandSuccessful;` — If true, the source control command succeeded
- L63 _public member_ `bool bConnectionDropped;` — If true, the source control connection was dropped while this command was being executed
- L66 _public member_ `FString WorkspaceName;` — Plastic current workspace
- L69 _public member_ `FString RepositoryName;` — Plastic current repository
- L72 _public member_ `FString ServerUrl;` — Plastic current server URL
- L75 _public member_ `FString BranchName;` — Name of the current branch
- L78 _public member_ `FString WorkspaceSelector;` — Name of the object that the workspace is switched to: usually the branch, sometimes a changeset or a label
- L81 _public member_ `int32 ChangesetNumber;` — Current Changeset Number
- L84 _public member_ `bool bAutoDelete;` — If true, this command will be automatically cleaned up in Tick()
- L87 _public member_ `EConcurrency::Type Concurrency;` — Whether we are running multi-treaded in the background, or blocking the main thread
- L90 _public member_ `const double StartTimestamp;` — Timestamp of when the command was issued
- L93 _public member_ `TArray<FString> Files;` — Files to perform this operation on
- L96 _public member_ `FPlasticSourceControlChangelist Changelist;` — Changelist to perform this operation on
- L99 _public member_ `TArray<FString> InfoMessages;` — Info and/or warning message storage
- L102 _public member_ `TArray<FString> ErrorMessages;` — Potential error message storage

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlConsole.h` (Private)


#### class `FPlasticSourceControlConsole`  
`class FPlasticSourceControlConsole`  
_L14-26_
- desc: Editor only console commands. Such commands can be executed from the editor output log window, but also from command line arguments, from Editor Blueprints utilities, or from C++ Code using. eg. GEngine->Exec("cm status");
- L17 _public prototype_ `void Register();`
- L18 _public prototype_ `void Unregister();`
- L22 _private prototype_ `void ExecutePlasticConsoleCommand(const TArray<FString>& a_args);` — Unity Version Control Command Line Interface: Run 'cm' commands directly from the Unreal Editor Console.
- L25 _private member_ `TUniquePtr<FAutoConsoleCommand> CmConsoleCommand;` — Console command for interacting with 'cm' CLI directly

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlLock.h` (Private)


#### class `FPlasticSourceControlLock`  
`class FPlasticSourceControlLock`  
_L9-29_
- L12 _public member_ `int32 ItemId = ISourceControlState::INVALID_REVISION;`
- L13 _public member_ `FString Path;`
- L14 _public member_ `FString Status;`
- L15 _public member_ `bool bIsLocked = false;`
- L16 _public member_ `FDateTime Date;`
- L17 _public member_ `FString Owner;`
- L18 _public member_ `FString DestinationBranch;`
- L19 _public member_ `FString Branch;`
- L20 _public member_ `FString Workspace;`
- L22 _public function_ `void PopulateSearchString(TArray<FString>& OutStrings) const`

#### Free symbols / members of external scopes

- L31 _typedef_ `typedef TSharedRef<class FPlasticSourceControlLock, ESPMode::ThreadSafe> FPlasticSourceControlLockRef;`
- L32 _typedef_ `typedef TSharedPtr<class FPlasticSourceControlLock, ESPMode::ThreadSafe> FPlasticSourceControlLockPtr;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlLocksWindow.h` (Private)


#### class `FPlasticSourceControlLocksWindow`  
`class FPlasticSourceControlLocksWindow`  
_L8-20_
- desc: Nomad tab window to hold the widget with the list of Locks, see SPlasticSourceControlLocksWidget
- L11 _public prototype_ `void Register();`
- L12 _public prototype_ `void Unregister();`
- L14 _public prototype_ `void OpenTab();`
- L17 _private prototype_ `TSharedRef<class SDockTab> OnSpawnTab(const class FSpawnTabArgs& SpawnTabArgs);`
- L19 _private prototype_ `TSharedPtr<class SWidget> CreateLocksWidget();`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlMenu.h` (Private)


#### class `FPlasticSourceControlMenu`  
`class FPlasticSourceControlMenu`  
_L16-82_
- desc: Unity Version Control extension of the Source Control toolbar menu
- L19 _public prototype_ `void Register();`
- L20 _public prototype_ `void Unregister();`
- L23 _public prototype_ `void SyncProjectClicked();` — This functions will be bound to appropriate Command.
- L24 _public prototype_ `void RevertUnchangedClicked();`
- L25 _public prototype_ `void RevertAllClicked();`
- L26 _public prototype_ `void SwitchToPartialWorkspaceClicked();`
- L27 _public prototype_ `bool CanSwitchToPartialWorkspace() const;`
- L28 _public prototype_ `void ShowSourceControlEditorPreferences() const;`
- L29 _public prototype_ `void ShowSourceControlProjectSettings() const;`
- L30 _public prototype_ `void ShowSourceControlPlasticScmProjectSettings() const;`
- L31 _public prototype_ `void VisitDocsURLClicked() const;`
- L32 _public prototype_ `void VisitSupportURLClicked() const;`
- L33 _public prototype_ `void VisitLockRulesURLClicked(const FString InOrganizationName) const;`
- L34 _public prototype_ `void OpenDesktopApplication() const;`
- L35 _public prototype_ `void OpenBranchesWindow() const;`
- L36 _public prototype_ `void OpenChangesetsWindow() const;`
- L37 _public prototype_ `void OpenLocksWindow() const;`
- L40 _private prototype_ `bool IsSourceControlConnected() const;`
- L42 _private prototype_ `void AddMenuExtension(FToolMenuSection& Menu);`
- L43 _private prototype_ `void AddViewBranches(FToolMenuSection& Menu);`
- L44 _private prototype_ `void AddViewChangesets(FToolMenuSection& Menu);`
- L45 _private prototype_ `void AddViewLocks(FToolMenuSection& Menu);`
- L48 _private prototype_ `void ExtendToolbarWithStatusBarWidget();` — Extends the UE5 toolbar with a status bar widget to display the current branch and open the branch tab
- L51 _private prototype_ `void ExtendRevisionControlMenu();` — Extends the main Revision Control menu from the toolbar at the bottom-right.
- L53 _private prototype_ `void ExtendAssetContextMenu();` — Extends the content browser asset context menu with Admin revision control options.
- L55 _private prototype_ `void GeneratePlasticAssetContextMenu(FMenuBuilder& MenuBuilder, TArray<FAssetData> InAssetObjectPaths);` — Called to generate concert asset context menu.
- L57 _private prototype_ `bool CanRemoveLocks(TArray<FPlasticSourceControlLockRef> InSelectedLocks) const;`
- L58 _private prototype_ `bool CanReleaseLocks(TArray<FPlasticSourceControlLockRef> InSelectedLocks) const;`
- L59 _private prototype_ `void ExecuteRemoveLocks(TArray<FPlasticSourceControlLockRef> InSelectedLocks);`
- L60 _private prototype_ `void ExecuteReleaseLocks(TArray<FPlasticSourceControlLockRef> InSelectedLocks);`
- L61 _private prototype_ `void ExecuteUnlock(TArray<FPlasticSourceControlLockRef>&& InSelectedLocks, const bool bInRemove);`
- L65 _private member_ `bool bHasRegistered = false;` — Tracks if the menu extension has been registered with the editor or not
- L68 _private member_ `FNotification Notification;` — Ongoing notification for a long-running asynchronous source control operation, if any
- L71 _private member_ `static FName UnityVersionControlMainMenuOwnerName;` — Name of the menu extension going into the global Revision Control (on the toolbar at the bottom-right)
- L73 _private member_ `static FName UnityVersionControlAssetContextLocksMenuOwnerName;` — Name of the asset context menu extension for admin actions over Locks
- L75 _private member_ `static FName UnityVersionControlStatusBarMenuOwnerName;` — Name of status bar extension to display the current branch
- L78 _private prototype_ `void OnSyncAllOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Delegates called when a source control operation has completed
- L79 _private prototype_ `void OnRevertAllOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);`
- L81 _private prototype_ `void OnSourceControlOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Generic delegate and notification handler

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef TSharedRef<class FPlasticSourceControlLock, ESPMode::ThreadSafe> FPlasticSourceControlLockRef;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlModule.h` (Private)


#### class `FPlasticSourceControlModule`  
`class FPlasticSourceControlModule : public IModuleInterface`  
_L20-89_
- inherits: `IModuleInterface`
- desc: PlasticSourceControl is the official Unity Version Control Plugin for Unreal Engine Written and contributed by Sebastien Rombauts (sebastien.rombauts@gmail.com) for Codice Software
- L24 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _public function_ `FPlasticSourceControlProvider& GetProvider()` — Access the Plastic source control provider
- L32 _public function_ `const FPlasticSourceControlProvider& GetProvider() const`
- L38 _public function_ `FPlasticSourceControlWorkspaceCreation& GetWorkspaceCreation()` — Access the controller to create a new workspace
- L43 _public function_ `FPlasticSourceControlBranchesWindow& GetBranchesWindow()`
- L48 _public function_ `FPlasticSourceControlChangesetsWindow& GetChangesetsWindow()`
- L53 _public function_ `FPlasticSourceControlLocksWindow& GetLocksWindow()`
- L64 _public prototype_ `static FPlasticSourceControlModule& Get();` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, asserts if the module is not loaded yet or unloaded already.
- L69 _public prototype_ `static bool IsLoaded();` — Checks whether the module is currently loaded.
- L76 _public prototype_ `static const TSharedPtr<class IPlugin> GetPlugin();` — Finds information of the plugin. @return	 Pointer to the plugin's information, or nullptr.
- L80 _private member_ `FPlasticSourceControlProvider PlasticSourceControlProvider;` — The Plastic source control provider
- L83 _private member_ `FPlasticSourceControlBranchesWindow PlasticSourceControlBranchesWindow;` — Dockable windows adding advanced features to the plugin
- L84 _private member_ `FPlasticSourceControlChangesetsWindow PlasticSourceControlChangesetsWindow;`
- L85 _private member_ `FPlasticSourceControlLocksWindow PlasticSourceControlLocksWindow;`
- L88 _private member_ `FPlasticSourceControlWorkspaceCreation PlasticSourceControlWorkspaceCreation;` — Logic to create a new workspace

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlOperations.h` (Private)


#### class `FPlasticRevertUnchanged`  
`class FPlasticRevertUnchanged final : public FSourceControlOperationBase`  
_L29-36_
- inherits: `FSourceControlOperationBase`
- desc: Internal operation used to revert checked-out unchanged files NOTE: added to Engine in Unreal Engine 5 for changelists
- L33 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L35 _public prototype_ `virtual FText GetInProgressString() const override;`

#### class `FPlasticSyncAll`  
`class FPlasticSyncAll final : public FSync`  
_L44-54_
- inherits: `FSync`
- desc: Internal operation used to sync all files in the workspace NOTE: override the standard "Sync" operation to provide a list of updated files and a custom progress string
- L48 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L50 _public prototype_ `virtual FText GetInProgressString() const override;`
- L53 _public member_ `TArray<FString> UpdatedFiles;` — List of files updated by the operation

#### class `FPlasticRevertAll`  
`class FPlasticRevertAll final : public FRevert`  
_L60-70_
- inherits: `FRevert`
- desc: Internal operation used to revert checked-out files
- L64 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L66 _public prototype_ `virtual FText GetInProgressString() const override;`
- L69 _public member_ `TArray<FString> UpdatedFiles;` — List of files updated by the operation

#### class `FPlasticRevertToRevision`  
`class FPlasticRevertToRevision final : public FSourceControlOperationBase`  
_L76-89_
- inherits: `FSourceControlOperationBase`
- desc: Internal operation used to revert files to a previous revision
- L80 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L82 _public prototype_ `virtual FText GetInProgressString() const override;`
- L85 _public member_ `TArray<FString> UpdatedFiles;` — List of files updated by the operation
- L88 _public member_ `int32 ChangesetId = ISourceControlState::INVALID_REVISION;` — Changeset to revert the files to

#### class `FPlasticMakeWorkspace`  
`class FPlasticMakeWorkspace final : public FSourceControlOperationBase`  
_L95-107_
- inherits: `FSourceControlOperationBase`
- desc: Internal operation used to create a new Workspace and a new Repository
- L99 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L101 _public prototype_ `virtual FText GetInProgressString() const override;`
- L103 _public member_ `FString WorkspaceName;`
- L104 _public member_ `FString RepositoryName;`
- L105 _public member_ `FString ServerUrl;`
- L106 _public member_ `bool bPartialWorkspace = false;`

#### class `FPlasticSwitchToPartialWorkspace`  
`class FPlasticSwitchToPartialWorkspace final : public FSourceControlOperationBase`  
_L113-120_
- inherits: `FSourceControlOperationBase`
- desc: Internal operation used to switch to a partial workspace
- L117 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L119 _public prototype_ `virtual FText GetInProgressString() const override;`

#### class `FPlasticGetLocks`  
`class FPlasticGetLocks final : public FSourceControlOperationBase`  
_L126-136_
- inherits: `FSourceControlOperationBase`
- desc: Internal operation to list locks, aka "cm lock list"
- L130 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L132 _public prototype_ `virtual FText GetInProgressString() const override;`
- L135 _public member_ `TArray<FPlasticSourceControlLockRef> Locks;` — List of locks found

#### class `FPlasticUnlock`  
`class FPlasticUnlock final : public FSourceControlOperationBase`  
_L142-155_
- inherits: `FSourceControlOperationBase`
- desc: Internal operation used to release or remove Lock(s) on file(s)
- L146 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L148 _public prototype_ `virtual FText GetInProgressString() const override;`
- L151 _public member_ `TArray<FPlasticSourceControlLockRef> Locks;` — Locks to unlock, including the Item Id and branch name
- L154 _public member_ `bool bRemove = false;` — Release the Lock(s), and optionally remove (delete) them completely

#### class `FPlasticGetBranches`  
`class FPlasticGetBranches final : public FSourceControlOperationBase`  
_L161-174_
- inherits: `FSourceControlOperationBase`
- desc: Internal operation to list branches, aka "cm find branch"
- L165 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L167 _public prototype_ `virtual FText GetInProgressString() const override;`
- L170 _public member_ `FDateTime FromDate;` — Limit the list of branches to ones created from this date (optional, filtering enabled by default)
- L173 _public member_ `TArray<FPlasticSourceControlBranchRef> Branches;` — List of branches found

#### class `FPlasticSwitch`  
`class FPlasticSwitch final : public FSourceControlOperationBase`  
_L180-196_
- inherits: `FSourceControlOperationBase`
- desc: Internal operation used to switch the workspace to a branch or a changeset
- L184 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L186 _public prototype_ `virtual FText GetInProgressString() const override;`
- L189 _public member_ `FString BranchName;` — Branch to switch the workspace to (optional, only apply if ChangesetId is not set)
- L192 _public member_ `int32 ChangesetId = ISourceControlState::INVALID_REVISION;` — Changeset to switch the workspace to (optional, overrides the BranchName if set)
- L195 _public member_ `TArray<FString> UpdatedFiles;` — List of files updated by the operation

#### class `FPlasticMergeBranch`  
`class FPlasticMergeBranch final : public FSourceControlOperationBase`  
_L202-215_
- inherits: `FSourceControlOperationBase`
- desc: Internal operation used to merge a branch into the current branch
- L206 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L208 _public prototype_ `virtual FText GetInProgressString() const override;`
- L211 _public member_ `FString BranchName;` — Branch to switch the workspace to
- L214 _public member_ `TArray<FString> UpdatedFiles;` — List of files updated by the operation

#### class `FPlasticCreateBranch`  
`class FPlasticCreateBranch final : public FSourceControlOperationBase`  
_L221-231_
- inherits: `FSourceControlOperationBase`
- desc: Internal operation used to create a branch
- L225 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L227 _public prototype_ `virtual FText GetInProgressString() const override;`
- L229 _public member_ `FString BranchName;`
- L230 _public member_ `FString Comment;`

#### class `FPlasticRenameBranch`  
`class FPlasticRenameBranch final : public FSourceControlOperationBase`  
_L237-247_
- inherits: `FSourceControlOperationBase`
- desc: Internal operation used to rename a branch
- L241 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L243 _public prototype_ `virtual FText GetInProgressString() const override;`
- L245 _public member_ `FString OldName;`
- L246 _public member_ `FString NewName;`

#### class `FPlasticDeleteBranches`  
`class FPlasticDeleteBranches final : public FSourceControlOperationBase`  
_L253-262_
- inherits: `FSourceControlOperationBase`
- desc: Internal operation used to deletes branches
- L257 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L259 _public prototype_ `virtual FText GetInProgressString() const override;`
- L261 _public member_ `TArray<FString> BranchNames;`

#### class `FPlasticGetChangesets`  
`class FPlasticGetChangesets final : public FSourceControlOperationBase`  
_L268-281_
- inherits: `FSourceControlOperationBase`
- desc: Internal operation to list changesets, aka "cm find changesets"
- L272 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L274 _public prototype_ `virtual FText GetInProgressString() const override;`
- L277 _public member_ `FDateTime FromDate;` — Limit the list of changesets to ones created from this date (optional, filtering enabled by default)
- L280 _public member_ `TArray<FPlasticSourceControlChangesetRef> Changesets;` — List of changesets found

#### class `FPlasticGetChangesetFiles`  
`class FPlasticGetChangesetFiles final : public FSourceControlOperationBase`  
_L287-300_
- inherits: `FSourceControlOperationBase`
- desc: Internal operation to list files in a changeset, using "cm log cs:<ChangesetId>"
- L291 _public prototype_ `virtual FName GetName() const override;` — ISourceControlOperation interface
- L293 _public prototype_ `virtual FText GetInProgressString() const override;`
- L296 _public member_ `FPlasticSourceControlChangesetPtr Changeset;` — Changeset to list files from
- L299 _public member_ `TArray<FPlasticSourceControlStateRef> Files;` — List of files changed in the changeset

#### class `FPlasticConnectWorker`  
`class FPlasticConnectWorker final : public IPlasticSourceControlWorker`  
_L305-320_
- inherits: `IPlasticSourceControlWorker`
- desc: Called when first activated on a project, and then at project load time. Look for the root directory of the Plastic workspace (where the ".plastic/" subdirectory is located).
- L308 _public function_ `explicit FPlasticConnectWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L311 _public prototype_ `virtual ~FPlasticConnectWorker() = default;`
- L313 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L314 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L315 _public prototype_ `virtual bool UpdateStates() override;`
- L319 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results

#### class `FPlasticCheckOutWorker`  
`class FPlasticCheckOutWorker final : public IPlasticSourceControlWorker`  
_L322-341_
- inherits: `IPlasticSourceControlWorker`
- L325 _public function_ `explicit FPlasticCheckOutWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider) , InChangelist(FPlasticSourceControlChangelist::DefaultChangelist)`
- L329 _public prototype_ `virtual ~FPlasticCheckOutWorker() = default;`
- L331 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L332 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L333 _public prototype_ `virtual bool UpdateStates() override;`
- L337 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results
- L340 _public member_ `FPlasticSourceControlChangelist InChangelist;` — Changelist we checked-out files to (defaults to the Default changelist)

#### class `FPlasticCheckInWorker`  
`class FPlasticCheckInWorker final : public IPlasticSourceControlWorker`  
_L344-362_
- inherits: `IPlasticSourceControlWorker`
- desc: Check-in a set of file to the local depot.
- L347 _public function_ `explicit FPlasticCheckInWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L350 _public prototype_ `virtual ~FPlasticCheckInWorker() = default;`
- L352 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L353 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L354 _public prototype_ `virtual bool UpdateStates() override;`
- L358 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results
- L361 _public member_ `FPlasticSourceControlChangelist InChangelist;` — Changelist we submitted

#### class `FPlasticMarkForAddWorker`  
`class FPlasticMarkForAddWorker final : public IPlasticSourceControlWorker`  
_L365-384_
- inherits: `IPlasticSourceControlWorker`
- desc: Add an untracked file to source control (so only a subset of the Plastic add command).
- L368 _public function_ `explicit FPlasticMarkForAddWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider) , InChangelist(FPlasticSourceControlChangelist::DefaultChangelist)`
- L372 _public prototype_ `virtual ~FPlasticMarkForAddWorker() = default;`
- L374 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L375 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L376 _public prototype_ `virtual bool UpdateStates() override;`
- L380 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results
- L383 _public member_ `FPlasticSourceControlChangelist InChangelist;` — Changelist we added files to (defaults to the Default changelist)

#### class `FPlasticDeleteWorker`  
`class FPlasticDeleteWorker final : public IPlasticSourceControlWorker`  
_L387-406_
- inherits: `IPlasticSourceControlWorker`
- desc: Delete a file and remove it from source control.
- L390 _public function_ `explicit FPlasticDeleteWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider) , InChangelist(FPlasticSourceControlChangelist::DefaultChangelist)`
- L394 _public prototype_ `virtual ~FPlasticDeleteWorker() = default;`
- L396 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L397 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L398 _public prototype_ `virtual bool UpdateStates() override;`
- L402 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results
- L405 _public member_ `FPlasticSourceControlChangelist InChangelist;` — Changelist we delete files to (defaults to the Default changelist)

#### class `FPlasticRevertWorker`  
`class FPlasticRevertWorker final : public IPlasticSourceControlWorker`  
_L409-424_
- inherits: `IPlasticSourceControlWorker`
- desc: Revert any change to a file to its state on the local depot.
- L412 _public function_ `explicit FPlasticRevertWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L415 _public prototype_ `virtual ~FPlasticRevertWorker() = default;`
- L417 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L418 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L419 _public prototype_ `virtual bool UpdateStates() override;`
- L423 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results

#### class `FPlasticRevertUnchangedWorker`  
`class FPlasticRevertUnchangedWorker final : public IPlasticSourceControlWorker`  
_L427-442_
- inherits: `IPlasticSourceControlWorker`
- desc: Revert only unchanged file(s) (uncheckout).
- L430 _public function_ `explicit FPlasticRevertUnchangedWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L433 _public prototype_ `virtual ~FPlasticRevertUnchangedWorker() = default;`
- L435 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L436 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L437 _public prototype_ `virtual bool UpdateStates() override;`
- L441 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results

#### class `FPlasticRevertAllWorker`  
`class FPlasticRevertAllWorker final : public IPlasticSourceControlWorker`  
_L445-460_
- inherits: `IPlasticSourceControlWorker`
- desc: Revert all checked-out file(s).
- L448 _public function_ `explicit FPlasticRevertAllWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L451 _public prototype_ `virtual ~FPlasticRevertAllWorker() = default;`
- L453 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L454 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L455 _public prototype_ `virtual bool UpdateStates() override;`
- L459 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results

#### class `FPlasticRevertToRevisionWorker`  
`class FPlasticRevertToRevisionWorker final : public IPlasticSourceControlWorker`  
_L463-478_
- inherits: `IPlasticSourceControlWorker`
- desc: Revert file(s) to selected revision.
- L466 _public function_ `explicit FPlasticRevertToRevisionWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L469 _public prototype_ `virtual ~FPlasticRevertToRevisionWorker() = default;`
- L471 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L472 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L473 _public prototype_ `virtual bool UpdateStates() override;`
- L477 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results

#### class `FPlasticMakeWorkspaceWorker`  
`class FPlasticMakeWorkspaceWorker final : public IPlasticSourceControlWorker`  
_L481-492_
- inherits: `IPlasticSourceControlWorker`
- desc: Create a new Workspace and a new Repository
- L484 _public function_ `explicit FPlasticMakeWorkspaceWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L487 _public prototype_ `virtual ~FPlasticMakeWorkspaceWorker() = default;`
- L489 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L490 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L491 _public prototype_ `virtual bool UpdateStates() override;`

#### class `FPlasticSwitchToPartialWorkspaceWorker`  
`class FPlasticSwitchToPartialWorkspaceWorker final : public IPlasticSourceControlWorker`  
_L495-510_
- inherits: `IPlasticSourceControlWorker`
- desc: Switch to Partial Workspace.
- L498 _public function_ `explicit FPlasticSwitchToPartialWorkspaceWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L501 _public prototype_ `virtual ~FPlasticSwitchToPartialWorkspaceWorker() = default;`
- L503 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L504 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L505 _public prototype_ `virtual bool UpdateStates() override;`
- L509 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results

#### class `FPlasticGetLocksWorker`  
`class FPlasticGetLocksWorker final : public IPlasticSourceControlWorker`  
_L513-524_
- inherits: `IPlasticSourceControlWorker`
- desc: list locks.
- L516 _public function_ `explicit FPlasticGetLocksWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L519 _public prototype_ `virtual ~FPlasticGetLocksWorker() = default;`
- L521 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L522 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L523 _public prototype_ `virtual bool UpdateStates() override;`

#### class `FPlasticUnlockWorker`  
`class FPlasticUnlockWorker final : public IPlasticSourceControlWorker`  
_L527-542_
- inherits: `IPlasticSourceControlWorker`
- desc: release or remove Lock(s) on file(s).
- L530 _public function_ `explicit FPlasticUnlockWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L533 _public prototype_ `virtual ~FPlasticUnlockWorker() = default;`
- L535 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L536 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L537 _public prototype_ `virtual bool UpdateStates() override;`
- L541 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results

#### class `FPlasticGetBranchesWorker`  
`class FPlasticGetBranchesWorker final : public IPlasticSourceControlWorker`  
_L545-556_
- inherits: `IPlasticSourceControlWorker`
- desc: list branches.
- L548 _public function_ `explicit FPlasticGetBranchesWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L551 _public prototype_ `virtual ~FPlasticGetBranchesWorker() = default;`
- L553 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L554 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L555 _public prototype_ `virtual bool UpdateStates() override;`

#### class `FPlasticSwitchWorker`  
`class FPlasticSwitchWorker final : public IPlasticSourceControlWorker`  
_L559-574_
- inherits: `IPlasticSourceControlWorker`
- desc: Switch workspace to another branch.
- L562 _public function_ `explicit FPlasticSwitchWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L565 _public prototype_ `virtual ~FPlasticSwitchWorker() = default;`
- L567 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L568 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L569 _public prototype_ `virtual bool UpdateStates() override;`
- L573 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results

#### class `FPlasticMergeBranchWorker`  
`class FPlasticMergeBranchWorker final : public IPlasticSourceControlWorker`  
_L577-592_
- inherits: `IPlasticSourceControlWorker`
- desc: Merge a branch to the current branch.
- L580 _public function_ `explicit FPlasticMergeBranchWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L583 _public prototype_ `virtual ~FPlasticMergeBranchWorker() = default;`
- L585 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L586 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L587 _public prototype_ `virtual bool UpdateStates() override;`
- L591 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results

#### class `FPlasticCreateBranchWorker`  
`class FPlasticCreateBranchWorker final : public IPlasticSourceControlWorker`  
_L595-606_
- inherits: `IPlasticSourceControlWorker`
- desc: Create a new child branch.
- L598 _public function_ `explicit FPlasticCreateBranchWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L601 _public prototype_ `virtual ~FPlasticCreateBranchWorker() = default;`
- L603 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L604 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L605 _public prototype_ `virtual bool UpdateStates() override;`

#### class `FPlasticRenameBranchWorker`  
`class FPlasticRenameBranchWorker final : public IPlasticSourceControlWorker`  
_L609-620_
- inherits: `IPlasticSourceControlWorker`
- desc: Rename a branch.
- L612 _public function_ `explicit FPlasticRenameBranchWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L615 _public prototype_ `virtual ~FPlasticRenameBranchWorker() = default;`
- L617 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L618 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L619 _public prototype_ `virtual bool UpdateStates() override;`

#### class `FPlasticDeleteBranchesWorker`  
`class FPlasticDeleteBranchesWorker final : public IPlasticSourceControlWorker`  
_L623-634_
- inherits: `IPlasticSourceControlWorker`
- desc: Delete branches.
- L626 _public function_ `explicit FPlasticDeleteBranchesWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L629 _public prototype_ `virtual ~FPlasticDeleteBranchesWorker() = default;`
- L631 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L632 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L633 _public prototype_ `virtual bool UpdateStates() override;`

#### class `FPlasticGetChangesetsWorker`  
`class FPlasticGetChangesetsWorker final : public IPlasticSourceControlWorker`  
_L637-651_
- inherits: `IPlasticSourceControlWorker`
- desc: list changesets.
- L640 _public function_ `explicit FPlasticGetChangesetsWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L643 _public prototype_ `virtual ~FPlasticGetChangesetsWorker() = default;`
- L645 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L646 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L647 _public prototype_ `virtual bool UpdateStates() override;`
- L650 _public member_ `int32 CurrentChangesetId;` — Current changeset the workspace is on (at the end of the operation)

#### class `FPlasticGetChangesetFilesWorker`  
`class FPlasticGetChangesetFilesWorker final : public IPlasticSourceControlWorker`  
_L654-665_
- inherits: `IPlasticSourceControlWorker`
- desc: list files in changeset.
- L657 _public function_ `explicit FPlasticGetChangesetFilesWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L660 _public prototype_ `virtual ~FPlasticGetChangesetFilesWorker() = default;`
- L662 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L663 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L664 _public prototype_ `virtual bool UpdateStates() override;`

#### class `FPlasticSyncWorker`  
`class FPlasticSyncWorker final : public IPlasticSourceControlWorker`  
_L668-683_
- inherits: `IPlasticSourceControlWorker`
- desc: Plastic update the workspace to latest changes
- L671 _public function_ `explicit FPlasticSyncWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L674 _public prototype_ `virtual ~FPlasticSyncWorker() = default;`
- L676 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L677 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L678 _public prototype_ `virtual bool UpdateStates() override;`
- L682 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results

#### class `FPlasticUpdateStatusWorker`  
`class FPlasticUpdateStatusWorker final : public IPlasticSourceControlWorker`  
_L686-701_
- inherits: `IPlasticSourceControlWorker`
- desc: Get source control status of files on local workspace.
- L689 _public function_ `explicit FPlasticUpdateStatusWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L692 _public prototype_ `virtual ~FPlasticUpdateStatusWorker() = default;`
- L694 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L695 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L696 _public prototype_ `virtual bool UpdateStates() override;`
- L700 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results

#### class `FPlasticCopyWorker`  
`class FPlasticCopyWorker final : public IPlasticSourceControlWorker`  
_L704-719_
- inherits: `IPlasticSourceControlWorker`
- desc: Copy or Move operation on a single file
- L707 _public function_ `explicit FPlasticCopyWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L710 _public prototype_ `virtual ~FPlasticCopyWorker() = default;`
- L712 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L713 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L714 _public prototype_ `virtual bool UpdateStates() override;`
- L718 _public member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results

#### class `FPlasticResolveWorker`  
`class FPlasticResolveWorker final : public IPlasticSourceControlWorker`  
_L722-736_
- inherits: `IPlasticSourceControlWorker`
- desc: Plastic command to mark the conflict as solved
- L725 _public function_ `explicit FPlasticResolveWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L728 _public prototype_ `virtual ~FPlasticResolveWorker() = default;`
- L729 _public prototype_ `virtual FName GetName() const override;`
- L730 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L731 _public prototype_ `virtual bool UpdateStates() override;`
- L735 _private member_ `TArray<FPlasticSourceControlState> States;` — Temporary states for results

#### class `FPlasticGetPendingChangelistsWorker`  
`class FPlasticGetPendingChangelistsWorker final : public IPlasticSourceControlWorker`  
_L738-758_
- inherits: `IPlasticSourceControlWorker`
- L741 _public function_ `explicit FPlasticGetPendingChangelistsWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L744 _public prototype_ `virtual ~FPlasticGetPendingChangelistsWorker() = default;`
- L746 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L747 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L748 _public prototype_ `virtual bool UpdateStates() override;`
- L752 _public member_ `TArray<FPlasticSourceControlChangelistState> OutChangelistsStates;` — Temporary states for results
- L753 _public member_ `TArray<TArray<FPlasticSourceControlState>> OutCLFilesStates;`
- L757 _private member_ `bool bCleanupCache = false;` — Controls whether or not we will remove changelists from the cache after a full update

#### class `FPlasticNewChangelistWorker`  
`class FPlasticNewChangelistWorker final : public IPlasticSourceControlWorker`  
_L760-777_
- inherits: `IPlasticSourceControlWorker`
- L763 _public prototype_ `explicit FPlasticNewChangelistWorker(FPlasticSourceControlProvider& InSourceControlProvider);`
- L764 _public prototype_ `virtual ~FPlasticNewChangelistWorker() = default;`
- L766 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L767 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L768 _public prototype_ `virtual bool UpdateStates() override;`
- L772 _public member_ `FPlasticSourceControlChangelist NewChangelist;` — New changelist information
- L773 _public member_ `FPlasticSourceControlChangelistState NewChangelistState;`
- L776 _public member_ `TArray<FString> MovedFiles;` — Files that were moved

#### class `FPlasticDeleteChangelistWorker`  
`class FPlasticDeleteChangelistWorker final : public IPlasticSourceControlWorker`  
_L779-793_
- inherits: `IPlasticSourceControlWorker`
- L782 _public function_ `explicit FPlasticDeleteChangelistWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L785 _public prototype_ `virtual ~FPlasticDeleteChangelistWorker() = default;`
- L787 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L788 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L789 _public prototype_ `virtual bool UpdateStates() override;`
- L792 _public member_ `FPlasticSourceControlChangelist DeletedChangelist;`

#### class `FPlasticEditChangelistWorker`  
`class FPlasticEditChangelistWorker final : public IPlasticSourceControlWorker`  
_L795-813_
- inherits: `IPlasticSourceControlWorker`
- L798 _public function_ `explicit FPlasticEditChangelistWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L801 _public prototype_ `virtual ~FPlasticEditChangelistWorker() = default;`
- L803 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L804 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L805 _public prototype_ `virtual bool UpdateStates() override;`
- L808 _public member_ `FPlasticSourceControlChangelist EditedChangelist;`
- L809 _public member_ `FString EditedDescription;`
- L812 _public member_ `TArray<FString> ReopenedFiles;` — Reopened files (moved to a new changelist, if any, when editing the Default changelist)

#### class `FPlasticReopenWorker`  
`class FPlasticReopenWorker final : public IPlasticSourceControlWorker`  
_L815-833_
- inherits: `IPlasticSourceControlWorker`
- L818 _public function_ `explicit FPlasticReopenWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L821 _public prototype_ `virtual ~FPlasticReopenWorker() = default;`
- L823 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L824 _public prototype_ `virtual bool Execute(class FPlasticSourceControlCommand& InCommand) override;`
- L825 _public prototype_ `virtual bool UpdateStates() override;`
- L829 _protected member_ `TArray<FString> ReopenedFiles;` — Reopened files (moved to a new changelist)
- L832 _protected member_ `FPlasticSourceControlChangelist DestinationChangelist;` — Destination changelist

#### class `FPlasticShelveWorker`  
`class FPlasticShelveWorker final : public IPlasticSourceControlWorker`  
_L835-862_
- inherits: `IPlasticSourceControlWorker`
- L838 _public function_ `explicit FPlasticShelveWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L841 _public prototype_ `virtual ~FPlasticShelveWorker() = default;`
- L844 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L845 _public prototype_ `virtual bool Execute(FPlasticSourceControlCommand& InCommand) override;`
- L846 _public prototype_ `virtual bool UpdateStates() override;`
- L849 _protected member_ `int32 ShelveId = ISourceControlState::INVALID_REVISION;`
- L851 _protected member_ `TArray<FString> ShelvedFiles;`
- L854 _protected member_ `TArray<FString> MovedFiles;` — Files that were moved to a new changelist if shelving from the Default Changelist
- L857 _protected member_ `FString ChangelistDescription;` — Changelist description if needed
- L860 _protected member_ `FPlasticSourceControlChangelist InChangelistToUpdate;` — Changelist(s) to be updated
- L861 _protected member_ `FPlasticSourceControlChangelist OutChangelistToUpdate;`

#### class `FPlasticUnshelveWorker`  
`class FPlasticUnshelveWorker final : public IPlasticSourceControlWorker`  
_L864-883_
- inherits: `IPlasticSourceControlWorker`
- L867 _public function_ `explicit FPlasticUnshelveWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L870 _public prototype_ `virtual ~FPlasticUnshelveWorker() = default;`
- L873 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L874 _public prototype_ `virtual bool Execute(FPlasticSourceControlCommand& InCommand) override;`
- L875 _public prototype_ `virtual bool UpdateStates() override;`
- L879 _protected member_ `TArray<FPlasticSourceControlState> States;` — List of files states after the unshelve
- L882 _protected member_ `FPlasticSourceControlChangelist ChangelistToUpdate;` — Changelist to be updated

#### class `FPlasticDeleteShelveWorker`  
`class FPlasticDeleteShelveWorker final : public IPlasticSourceControlWorker`  
_L885-907_
- inherits: `IPlasticSourceControlWorker`
- L888 _public function_ `explicit FPlasticDeleteShelveWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L891 _public prototype_ `virtual ~FPlasticDeleteShelveWorker() = default;`
- L894 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L895 _public prototype_ `virtual bool Execute(FPlasticSourceControlCommand& InCommand) override;`
- L896 _public prototype_ `virtual bool UpdateStates() override;`
- L900 _protected member_ `TArray<FString> FilesToRemove;` — List of files to remove from shelved files in changelist state
- L903 _protected member_ `FPlasticSourceControlChangelist ChangelistToUpdate;` — Changelist to be updated
- L906 _protected member_ `int32 ShelveId = ISourceControlState::INVALID_REVISION;` — Id of the new shelve (if only a selection of files are deleted from the shelve)

#### class `FPlasticGetChangelistDetailsWorker`  
`class FPlasticGetChangelistDetailsWorker final : public IPlasticSourceControlWorker`  
_L909-921_
- inherits: `IPlasticSourceControlWorker`
- L912 _public function_ `FPlasticGetChangelistDetailsWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L915 _public prototype_ `virtual ~FPlasticGetChangelistDetailsWorker() = default;`
- L918 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L919 _public prototype_ `virtual bool Execute(FPlasticSourceControlCommand& InCommand) override;`
- L920 _public prototype_ `virtual bool UpdateStates() override;`

#### class `FPlasticGetFileWorker`  
`class FPlasticGetFileWorker final : public IPlasticSourceControlWorker`  
_L923-935_
- inherits: `IPlasticSourceControlWorker`
- L926 _public function_ `FPlasticGetFileWorker(FPlasticSourceControlProvider& InSourceControlProvider) : IPlasticSourceControlWorker(InSourceControlProvider)`
- L929 _public prototype_ `virtual ~FPlasticGetFileWorker() = default;`
- L932 _public prototype_ `virtual FName GetName() const override;` — IPlasticSourceControlWorker interface
- L933 _public prototype_ `virtual bool Execute(FPlasticSourceControlCommand& InCommand) override;`
- L934 _public prototype_ `virtual bool UpdateStates() override;`

#### Free symbols / members of external scopes

- L18 _typedef_ `typedef TSharedRef<class FPlasticSourceControlBranch, ESPMode::ThreadSafe> FPlasticSourceControlBranchRef;`
- L19 _typedef_ `typedef TSharedRef<class FPlasticSourceControlChangeset, ESPMode::ThreadSafe> FPlasticSourceControlChangesetRef;`
- L20 _typedef_ `typedef TSharedPtr<class FPlasticSourceControlChangeset, ESPMode::ThreadSafe> FPlasticSourceControlChangesetPtr;`
- L21 _typedef_ `typedef TSharedRef<class FPlasticSourceControlLock, ESPMode::ThreadSafe> FPlasticSourceControlLockRef;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlParsers.h` (Private)


#### class `PlasticSourceControlParsers::FPlasticMergeConflictParser`  
`class FPlasticMergeConflictParser`  
_L20-28_
- L23 _public prototype_ `explicit FPlasticMergeConflictParser(const FString& InResult);`
- L25 _public member_ `FString Filename;`
- L26 _public member_ `FString BaseChangeset;`
- L27 _public member_ `FString SourceChangeset;`

#### struct `PlasticSourceControlParsers::FRemoveRedundantErrors`  
`struct FRemoveRedundantErrors`  
_L33-52_
- desc: Helper struct for RemoveRedundantErrors()
- L35 _public function_ `explicit FRemoveRedundantErrors(const FString& InFilter) : Filter(InFilter)`
- L40 _public function_ `bool operator()(const FString& String) const`
- L51 _public member_ `FString Filter;` — The filter string we try to identify in the reported error

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TSharedRef<class FPlasticSourceControlBranch, ESPMode::ThreadSafe> FPlasticSourceControlBranchRef;`
- L12 _typedef_ `typedef TSharedRef<class FPlasticSourceControlChangeset, ESPMode::ThreadSafe> FPlasticSourceControlChangesetRef;`
- L13 _typedef_ `typedef TSharedRef<class FPlasticSourceControlState, ESPMode::ThreadSafe> FPlasticSourceControlStateRef;`
- L15 _namespace_ `namespace PlasticSourceControlParsers`
- L18 _prototype_ `FPlasticSourceControlLock ParseLockInfo(const FString& InResult);` (scope `PlasticSourceControlParsers`)
- L54 _prototype_ `bool ParseProfileInfo(TArray<FString>& InResults, const FString& InServerUrl, FString& OutUserName);` (scope `PlasticSourceControlParsers`)
- L56 _prototype_ `bool ParseWorkspaceInfo(TArray<FString>& InResults, FString& OutWorkspaceSelector, FString& OutBranchName, FString& OutRepositoryName, FString& OutServerUrl);` (scope `PlasticSourceControlParsers`)
- L58 _prototype_ `bool GetChangesetFromWorkspaceStatus(const TArray<FString>& InResults, int32& OutChangeset);` (scope `PlasticSourceControlParsers`)
- L60 _prototype_ `void ParseFileStatusResult(TArray<FString>&& InFiles, const TArray<FString>& InResults, TArray<FPlasticSourceControlState>& OutStates);` (scope `PlasticSourceControlParsers`)
- L62 _prototype_ `void ParseDirectoryStatusResult(const FString& InDir, const TArray<FString>& InResults, TArray<FPlasticSourceControlState>& OutStates);` (scope `PlasticSourceControlParsers`)
- L64 _prototype_ `void ParseFileinfoResults(const TArray<FString>& InResults, TArray<FPlasticSourceControlState>& InOutStates);` (scope `PlasticSourceControlParsers`)
- L66 _prototype_ `bool ParseHistoryResults(const bool bInUpdateHistory, const FString& InXmlFilename, TArray<FPlasticSourceControlState>& InOutStates);` (scope `PlasticSourceControlParsers`)
- L68 _prototype_ `bool ParseUpdateResults(const FString& InResults, TArray<FString>& OutFiles);` (scope `PlasticSourceControlParsers`)
- L69 _prototype_ `bool ParseUpdateResults(const TArray<FString>& InResults, TArray<FString>& OutFiles);` (scope `PlasticSourceControlParsers`)
- L71 _prototype_ `FText ParseCheckInResults(const TArray<FString>& InResults);` (scope `PlasticSourceControlParsers`)
- L73 _prototype_ `bool ParseChangelistsResults(const FString& InXmlFilename, TArray<FPlasticSourceControlChangelistState>& OutChangelistsStates, TArray<TArray<FPlasticSourceControlState>>& OutCLFilesStates);` (scope `PlasticSourceControlParsers`)
- L75 _prototype_ `bool ParseShelveDiffResult(const FString InWorkspaceRoot, TArray<FString>&& InResults, FPlasticSourceControlChangelistState& InOutChangelistsState);` (scope `PlasticSourceControlParsers`)
- L76 _prototype_ `bool ParseShelveDiffResults(const FString InWorkspaceRoot, TArray<FString>&& InResults, TArray<FPlasticSourceControlRevision>& OutBaseRevisions);` (scope `PlasticSourceControlParsers`)
- L78 _prototype_ `bool ParseShelvesResults(const FString& InResults, TArray<FPlasticSourceControlChangelistState>& InOutChangelistsStates);` (scope `PlasticSourceControlParsers`)
- L79 _prototype_ `bool ParseShelvesResult(const FString& InResults, FString& OutComment, FDateTime& OutDate, FString& OutOwner);` (scope `PlasticSourceControlParsers`)
- L81 _prototype_ `bool ParseChangesetsResults(const FString& InXmlFilename, TArray<FPlasticSourceControlChangesetRef>& OutChangesets);` (scope `PlasticSourceControlParsers`)
- L82 _prototype_ `bool ParseLogResults(const FString& InXmlFilename, const FPlasticSourceControlChangesetRef& InChangeset, TArray<FPlasticSourceControlStateRef>& OutFiles);` (scope `PlasticSourceControlParsers`)
- L84 _prototype_ `bool ParseBranchesResults(const FString& InXmlFilename, TArray<FPlasticSourceControlBranchRef>& OutBranches);` (scope `PlasticSourceControlParsers`)
- L86 _prototype_ `bool ParseMergeResults(const FString& InResult, TArray<FString>& OutFiles);` (scope `PlasticSourceControlParsers`)

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlProjectSettings.h` (Private)


#### class `UPlasticSourceControlProjectSettings`  
`class UPlasticSourceControlProjectSettings : public UDeveloperSettings`  
_L11-79_
- reflection: `UCLASS(config = Editor, defaultconfig, meta = (DisplayName = "Source Control - Unity Version Control"))`
- inherits: `UDeveloperSettings`
- desc: Project Settings for Unity Version Control (formerly Plastic SCM). Saved in Config/DefaultEditor.ini
- L18 _public member_ `TMap<FString, FString> UserNameToDisplayName;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control")` — Map Unity Version Control user names (typically e-mail addresses or company domain names) to display names for brevity.
- L22 _public member_ `bool bHideEmailDomainInUsername = true;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control")` — Hide the domain part of an username e-mail address (eg @gmail.com) if the UserNameToDisplayName map didn't match (enabled by default).
- L26 _public member_ `bool bPromptForCheckoutOnChange = true;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control")` — If enabled, you'll be prompted to check out changed files (enabled by default). Checkout is needed to work with Changelists.
- L30 _public member_ `int32 LimitNumberOfRevisionsInHistory = 50;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control", meta = (ClampMin = 0))` — If a non-null value is set, limit the maximum number of revisions requested to Unity Version Control to display in the "History" window.
- L34 _public member_ `bool bShowBranchRepositoryColumn = false;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control|View Branches window")` — Show the repository where the branch is created (hidden by default)
- L38 _public member_ `bool bShowBranchCreatedByColumn = true;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control|View Branches window")` — Show the name of the creator of the branch
- L42 _public member_ `bool bShowBranchDateColumn = true;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control|View Branches window")` — Show the date of creation of the branch
- L46 _public member_ `bool bShowBranchCommentColumn = true;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control|View Branches window")` — Show the comment of the branch
- L50 _public member_ `bool bShowLockIdColumn = false;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control|View Locks window")` — Show the Id of the lock (hidden by default)
- L54 _public member_ `bool bShowLockWorkspaceColumn = true;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control|View Locks window")` — Show the Workspace of the lock
- L58 _public member_ `bool bShowLockDateColumn = true;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control|View Locks window")` — Show the Date of the lock
- L62 _public member_ `bool bShowLockDestinationBranchColumn = false;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control|View Locks window")` — Show the Destination Branch of the lock (hidden by default)
- L66 _public member_ `bool bShowChangesetCreatedByColumn = true;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control|View Changesets window")` — Show the name of the creator of the changeset
- L70 _public member_ `bool bShowChangesetDateColumn = true;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control|View Changesets window")` — Show the date of creation of the changeset
- L74 _public member_ `bool bShowChangesetCommentColumn = true;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control|View Changesets window")` — Show the comment of the changeset
- L78 _public member_ `bool bShowChangesetBranchColumn = true;` — `UPROPERTY(config, EditAnywhere, Category = "Unity Version Control|View Changesets window")` — Show the branch the changeset was created on

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlProvider.h` (Private)


#### class `FPlasticSourceControlProvider`  
`class FPlasticSourceControlProvider : public ISourceControlProvider`  
_L18-285_
- inherits: `ISourceControlProvider`
- L22 _public prototype_ `FPlasticSourceControlProvider();` — Constructor & destructor
- L23 _public prototype_ `~FPlasticSourceControlProvider();`
- L26 _public prototype_ `virtual void Init(bool bForceConnection = true) override;` — ISourceControlProvider implementation
- L27 _public prototype_ `virtual void Close() override;`
- L28 _public prototype_ `virtual FText GetStatusText() const override;`
- L29 _public prototype_ `virtual TMap<EStatus, FString> GetStatus() const override;`
- L30 _public prototype_ `virtual bool IsEnabled() const override;`
- L31 _public prototype_ `virtual bool IsAvailable() const override;`
- L32 _public prototype_ `virtual const FName& GetName(void) const override;`
- L33 _public function_ `virtual bool QueryStateBranchConfig(const FString& ConfigSrc, const FString& ConfigDest) override`
- L34 _public function_ `virtual void RegisterStateBranches(const TArray<FString>& BranchNames, const FString& ContentRoot) override`
- L35 _public function_ `virtual int32 GetStateBranchIndex(const FString& InBranchName) const override`
- L36 _public function_ `virtual bool GetStateBranchAtIndex(int32 BranchIndex, FString& OutBranchName) const override`
- L37 _public prototype_ `virtual ECommandResult::Type GetState(const TArray<FString>& InFiles, TArray<FSourceControlStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage) override;`
- L38 _public prototype_ `virtual ECommandResult::Type GetState(const TArray<FSourceControlChangelistRef>& InChangelists, TArray<FSourceControlChangelistStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage) override;`
- L39 _public prototype_ `virtual TArray<FSourceControlStateRef> GetCachedStateByPredicate(TFunctionRef<bool(const FSourceControlStateRef&)> Predicate) const override;`
- L40 _public prototype_ `virtual FDelegateHandle RegisterSourceControlStateChanged_Handle(const FSourceControlStateChanged::FDelegate& SourceControlStateChanged) override;`
- L41 _public prototype_ `virtual void UnregisterSourceControlStateChanged_Handle(FDelegateHandle Handle) override;`
- L42 _public prototype_ `virtual ECommandResult::Type Execute(const FSourceControlOperationRef& InOperation, FSourceControlChangelistPtr InChangelist, const TArray<FString>& InFiles, EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() ) override;`
- L43 _public prototype_ `virtual bool CanExecuteOperation(const FSourceControlOperationRef& InOperation) const override;`
- L44 _public prototype_ `virtual bool CanCancelOperation(const FSourceControlOperationRef& InOperation) const override;`
- L45 _public prototype_ `virtual void CancelOperation(const FSourceControlOperationRef& InOperation) override;`
- L46 _public prototype_ `virtual bool UsesLocalReadOnlyState() const override;`
- L47 _public prototype_ `virtual bool UsesChangelists() const override;`
- L48 _public prototype_ `virtual bool UsesUncontrolledChangelists() const override;`
- L49 _public prototype_ `virtual bool UsesCheckout() const override;`
- L50 _public prototype_ `virtual bool UsesFileRevisions() const override;`
- L51 _public prototype_ `virtual bool UsesSnapshots() const override;`
- L52 _public prototype_ `virtual bool UsesSoftRevertOnDelete() const override;`
- L53 _public prototype_ `virtual bool AllowsDiffAgainstDepot() const override;`
- L54 _public prototype_ `virtual TOptional<bool> HasChangesToSync() const override;`
- L55 _public prototype_ `virtual TOptional<bool> HasChangesToCheckIn() const override;`
- L56 _public prototype_ `virtual void Tick() override;`
- L57 _public prototype_ `virtual TArray<TSharedRef<class ISourceControlLabel>> GetLabels(const FString& InMatchingSpec) const override;`
- L58 _public prototype_ `virtual TArray<FSourceControlChangelistRef> GetChangelists(EStateCacheUsage::Type InStateCacheUsage) override;`
- L60 _public prototype_ `virtual TSharedRef<class SWidget> MakeSettingsWidget() const override;`
- L68 _public prototype_ `void CheckPlasticAvailability();` — Run a Plastic "version" command to check the availability of the binary and of the workspace.
- L71 _public function_ `inline bool IsPlasticAvailable() const` — Is Plastic command line working.
- L77 _public function_ `inline bool IsWorkspaceFound() const` — Is Plastic workspace found.
- L83 _public function_ `inline const FString& GetPathToWorkspaceRoot() const` — Get the path to the root of the Plastic workspace: can be the GameDir itself, or any parent directory
- L89 _public function_ `inline const FString& GetUserName() const` — Get the Plastic current user
- L95 _public function_ `inline const FString& GetWorkspaceName() const` — Get the Plastic current workspace
- L101 _public function_ `inline const FString& GetRepositoryName() const` — Get the Plastic current repository
- L107 _public function_ `inline const FString& GetServerUrl() const` — Get the Plastic current server URL. See also GetCloudOrganization()
- L113 _public function_ `inline const FString& GetBranchName() const` — Get the Name of the current branch
- L118 _public function_ `inline const FString& GetWorkspaceSelector() const` — Get the Name of the current selector
- L122 _public function_ `inline void SetWorkspaceSelector(const FString& InWorkspaceSelector, const FString& InBranchName)`
- L129 _public function_ `inline int32 GetChangesetNumber() const` — Get the current Changeset Number
- L135 _public function_ `inline bool IsPartialWorkspace() const` — A partial/Gluon workspace doesn't match with a single changeset, which is identified by -1
- L141 _public function_ `inline const FSoftwareVersion& GetPlasticScmVersion() const` — Version of the Unity Version Control executable used
- L147 _public function_ `const FString& GetPluginVersion() const` — Version of the Unity Version Control plugin
- L153 _public prototype_ `FString GetCloudOrganization() const;` — Return the name of the cloud organization from the ServerUrl if applicable (MyOrganization@cloud) or an empty string
- L156 _public prototype_ `void SetLastErrors(const TArray<FString>& InErrors);` — Set list of error messages that occurred after last Plastic command
- L159 _public prototype_ `TArray<FString> GetLastErrors() const;` — Get list of error messages that occurred after last Plastic command
- L162 _public prototype_ `TSharedRef<class FPlasticSourceControlState, ESPMode::ThreadSafe> GetStateInternal(const FString& InFilename);` — Helper function used to update state cache
- L165 _public prototype_ `TSharedRef<class FPlasticSourceControlChangelistState, ESPMode::ThreadSafe> GetStateInternal(const FPlasticSourceControlChangelist& InChangelist);` — Helper function used to update changelists state cache
- L171 _public prototype_ `void RegisterWorker(const FName& InName, const FGetPlasticSourceControlWorker& InDelegate);` — Register a worker with the provider. This is used internally so the provider can maintain a map of all available operations.
- L174 _public prototype_ `bool RemoveFileFromCache(const FString& Filename);` — Remove a named file from the state cache
- L177 _public prototype_ `bool RemoveChangelistFromCache(const FPlasticSourceControlChangelist& Changelist);` — Remove a changelist from the state cache
- L180 _public prototype_ `TArray<FSourceControlChangelistStateRef> GetCachedStateByPredicate(TFunctionRef<bool(const FSourceControlChangelistStateRef&)> Predicate) const;` — Returns a list of changelists from the cache based on a given predicate
- L183 _public function_ `FPlasticSourceControlSettings& AccessSettings()` — Access the Plastic source control settings
- L187 _public function_ `const FPlasticSourceControlSettings& AccessSettings() const`
- L193 _public function_ `void SaveSettings()` — Save the Plastic source control settings
- L200 _private member_ `bool bPlasticAvailable = false;` — Is Plastic binary found and working.
- L203 _private member_ `bool bWorkspaceFound = false;` — Is Plastic workspace found.
- L206 _private member_ `bool bServerAvailable = false;` — Indicates if source control integration is available or not.
- L209 _private member_ `bool bUsesLocalReadOnlyState = false;` — Whether Unity Version Control is configured to uses local read-only state to signal whether a file is editable ("SetFilesAsReadOnly" in client.conf)
- L212 _private member_ `mutable FCriticalSection LastErrorsCriticalSection;` — Critical section for thread safety of error messages that occurred after last Plastic command
- L215 _private member_ `TArray<FString> LastErrors;` — List of error messages that occurred after last Plastic command
- L218 _private prototype_ `TSharedPtr<class IPlasticSourceControlWorker, ESPMode::ThreadSafe> CreateWorker(const FName& InOperationName);` — Helper function for Execute()
- L221 _private prototype_ `ECommandResult::Type ExecuteSynchronousCommand(class FPlasticSourceControlCommand& InCommand, const FText& Task);` — Helper function for running command synchronously.
- L223 _private prototype_ `ECommandResult::Type IssueCommand(class FPlasticSourceControlCommand& InCommand);` — Issue a command asynchronously if possible.
- L226 _private prototype_ `void OutputCommandMessages(const class FPlasticSourceControlCommand& InCommand) const;` — Output any messages this command holds
- L229 _private prototype_ `void UpdateWorkspaceStatus(const class FPlasticSourceControlCommand& InCommand);` — Update workspace status on Connect and UpdateStatus operations
- L232 _private prototype_ `void HandlePackageSaved(const FString& InPackageFilename, UPackage* InPackage, FObjectPostSaveContext InObjectSaveContext);` — Called after a package has been saved to disk, to update the source control cache
- L235 _private member_ `FSoftwareVersion PlasticScmVersion;` — Version of the Unity Version Control executable used
- L238 _private member_ `FString PluginVersion;` — Version of the Unity Version Control plugin
- L241 _private member_ `FString PathToWorkspaceRoot;` — Path to the root of the Plastic workspace: can be the GameDir itself, or any parent directory (found by the "Connect" operation)
- L244 _private member_ `FString UserName;` — Plastic current user
- L247 _private member_ `FString WorkspaceName;` — Plastic current workspace
- L250 _private member_ `FString RepositoryName;` — Plastic current repository
- L253 _private member_ `FString ServerUrl;` — Plastic current server URL
- L256 _private member_ `FString BranchName;` — Name of the current branch
- L259 _private member_ `FString WorkspaceSelector;` — Name of the object that the workspace is switched to: usually the branch, sometimes a changeset or a label
- L262 _private member_ `int32 ChangesetNumber = 0;` — Current Changeset Number
- L265 _private member_ `TMap<FString, TSharedRef<class FPlasticSourceControlState, ESPMode::ThreadSafe> > StateCache;` — State caches
- L266 _private member_ `TMap<FPlasticSourceControlChangelist, TSharedRef<class FPlasticSourceControlChangelistState, ESPMode::ThreadSafe> > ChangelistsStateCache;`
- L269 _private member_ `TMap<FName, FGetPlasticSourceControlWorker> WorkersMap;` — The currently registered source control operations
- L272 _private member_ `TArray < FPlasticSourceControlCommand* > CommandQueue;` — Queue for commands given by the main thread
- L275 _private member_ `FSourceControlStateChanged OnSourceControlStateChanged;` — For notifying when the source control states in the cache have changed
- L278 _private member_ `FPlasticSourceControlConsole PlasticSourceControlConsole;` — Source Control Console commands
- L281 _private member_ `FPlasticSourceControlMenu PlasticSourceControlMenu;` — Source Control Menu Extension
- L284 _private member_ `FPlasticSourceControlSettings PlasticSourceControlSettings;` — The settings for Plastic source control

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FPlasticSourceControlWorkerRef, FGetPlasticSourceControlWorker, FPlasticSourceControlProvider&) class FPlasticSourceControlProvider : public ISourceControlProvider { public: FPlasticSourceControlProvider(); ~FPlasticSourceControlProvider(); virtual void Init(bool bForceConnection = true) override; virtual void Close() override; virtual FText GetStatusText() const override; virtual TMap<EStatus, FString> GetStatus() const override; virtual bool IsEnabled() const override; virtual bool IsAvailable() const override; virtual const FName& GetName(void) const override; virtual bool QueryStateBranchConfig(const FString& ConfigSrc, const FString& ConfigDest) override { return false; } virtual void RegisterStateBranches(const TArray<FString>& BranchNames, const FString& ContentRoot) override {} virtual int32 GetStateBranchIndex(const FString& InBranchName) const override { return INDEX_NONE; } virtual bool GetStateBranchAtIndex(int32 BranchIndex, FString& OutBranchName) const override { return false; } virtual ECommandResult::Type GetState(const TArray<FString>& InFiles, TArray<FSourceControlStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage) override; virtual ECommandResult::Type GetState(const TArray<FSourceControlChangelistRef>& InChangelists, TArray<FSourceControlChangelistStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage) override; virtual TArray<FSourceControlStateRef> GetCachedStateByPredicate(TFunctionRef<bool(const FSour`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlRevision.h` (Private)


#### class `FPlasticSourceControlRevision`  
`class FPlasticSourceControlRevision : public ISourceControlRevision`  
_L12-78_
- inherits: `ISourceControlRevision`
- desc: Revision of a file, linked to a specific commit
- L15 _public function_ `FPlasticSourceControlRevision() : ChangesetNumber(ISourceControlState::INVALID_REVISION) , RevisionId(ISourceControlState::INVALID_REVISION) , Date(0) , FileSize(0)`
- L24 _public prototype_ `virtual bool Get(FString& InOutFilename, EConcurrency::Type InConcurrency = EConcurrency::Synchronous) const override;` — ISourceControlRevision interface
- L25 _public prototype_ `virtual bool GetAnnotated(TArray<FAnnotationLine>& OutLines) const override;`
- L26 _public prototype_ `virtual bool GetAnnotated(FString& InOutFilename) const override;`
- L27 _public prototype_ `virtual const FString& GetFilename() const override;`
- L28 _public prototype_ `virtual int32 GetRevisionNumber() const override;`
- L29 _public prototype_ `virtual const FString& GetRevision() const override;`
- L30 _public prototype_ `virtual const FString& GetDescription() const override;`
- L31 _public prototype_ `virtual const FString& GetUserName() const override;`
- L32 _public prototype_ `virtual const FString& GetClientSpec() const override;`
- L33 _public prototype_ `virtual const FString& GetAction() const override;`
- L34 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetBranchSource() const override;`
- L35 _public prototype_ `virtual const FDateTime& GetDate() const override;`
- L36 _public prototype_ `virtual int32 GetCheckInIdentifier() const override;`
- L37 _public prototype_ `virtual int32 GetFileSize() const override;`
- L41 _public member_ `FPlasticSourceControlState* State = nullptr;` — Point back to State this Revision is from
- L44 _public member_ `FString Filename;` — The filename this revision refers to
- L47 _public member_ `int32 ChangesetNumber;` — The changeset number of this revision
- L50 _public member_ `int32 RevisionId;` — The internal revision ID of this file
- L53 _public member_ `FString Revision;` — The revision to display to the user: use the changeset number
- L56 _public member_ `int32 ShelveId = ISourceControlState::INVALID_REVISION;` — The Shelve ID instead of Changeset / Revision for case of shelved files
- L59 _public member_ `FString Description;` — The description of this revision
- L62 _public member_ `FString UserName;` — The user that made the change
- L65 _public member_ `FString Branch;` — Branch where the change was made
- L68 _public member_ `FString Action;` — The action (add, edit, branch etc.) performed at this revision
- L71 _public member_ `TSharedPtr<FPlasticSourceControlRevision, ESPMode::ThreadSafe> BranchSource;` — Source of move ("branch" in Perforce term) if any
- L74 _public member_ `FDateTime Date;` — The date this revision was made
- L77 _public member_ `int32 FileSize;` — The size of the file at this revision

#### Free symbols / members of external scopes

- L81 _typedef_ `typedef TArray<TSharedRef<FPlasticSourceControlRevision, ESPMode::ThreadSafe>> TPlasticSourceControlHistory;` — History composed of the last 100 revisions of the file
- L83 _typedef_ `typedef TSharedPtr<FPlasticSourceControlRevision, ESPMode::ThreadSafe> FPlasticSourceControlRevisionPtr;`
- L84 _typedef_ `typedef TSharedRef<FPlasticSourceControlRevision, ESPMode::ThreadSafe> FPlasticSourceControlRevisionRef;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlSettings.h` (Private)


#### class `FPlasticSourceControlSettings`  
`class FPlasticSourceControlSettings`  
_L7-57_
- L11 _public prototype_ `FString GetBinaryPath() const;` — Get/Set the Plastic Binary Path
- L12 _public prototype_ `bool SetBinaryPath(const FString& InString);`
- L15 _public prototype_ `bool GetUpdateStatusAtStartup() const;` — Enable an asynchronous "Update Status" at Editor Startup (default is no, can take a long time).
- L16 _public prototype_ `void SetUpdateStatusAtStartup(const bool bInUpdateStatusAtStartup);`
- L19 _public prototype_ `bool GetUpdateStatusOtherBranches() const;` — Enable Update status to call "history" to detect recent changesets on other branches (can be slow).
- L20 _public prototype_ `void SetUpdateStatusOtherBranches(const bool bInUpdateStatusOtherBranches);`
- L23 _public prototype_ `bool GetViewLocalChanges() const;` — Enable the "View Changes" (changelists) window to also display locally Changed and Private files (can be slow).
- L24 _public prototype_ `void SetViewLocalChanges(const bool bInViewLocalChanges);`
- L27 _public prototype_ `bool GetEnableVerboseLogs() const;` — Enable LogSourceControl Verbose logs
- L28 _public prototype_ `void SetEnableVerboseLogs(const bool bInEnableVerboseLogs);`
- L31 _public prototype_ `void LoadSettings();` — Load settings from ini file
- L34 _public prototype_ `void SaveSettings() const;` — Save settings to ini file
- L38 _private member_ `mutable FCriticalSection CriticalSection;` — A critical section for settings access
- L41 _private member_ `FString BinaryPath = TEXT("cm"` — Plastic binary path
- L47 _private member_ `bool bUpdateStatusAtStartup = false;` — Run an asynchronous "Update Status" at Editor Startup (default is no). This does not work well with very big projects where this operation could take dozens of seconds preventing the project to have any source control support during this time.
- L50 _private member_ `bool bUpdateStatusOtherBranches = false;` — Enable Update status to call "history" to detect recent changesets on other branches (can be slow).
- L53 _private member_ `bool bViewLocalChanges = true;` — Enable the "View Changes" (changelists) window to also display Private and locally Changed assets (even though they cannot be moved to other changelists).
- L56 _private member_ `bool bEnableVerboseLogs = false;` — Override LogSourceControl verbosity level to Verbose, and back, if not already VeryVerbose.

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlShell.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PlasticSourceControlShell`
- L10 _variable_ `constexpr const TCHAR* pchDelim = TEXT("\r\` (scope `PlasticSourceControlShell`)
- L23 _prototype_ `bool Launch(const FString& InPathToPlasticBinary, const FString& InWorkspaceRoot);` (scope `PlasticSourceControlShell`) — Launch the Unity Version Control "shell" command line process to run it in the background. @param	InPathToPlasticBinary	The path to the Plastic binary @param	InWorkspaceRoot			The workspace from where to run the command - usually the Game directory @returns true if the command succeeded and returned no errors
- L26 _prototype_ `void Terminate();` (scope `PlasticSourceControlShell`) — Terminate the background 'cm shell' process and associated pipes
- L29 _prototype_ `void SetShellIsWarmedUp();` (scope `PlasticSourceControlShell`) — Mark the current shell process as already warmed up - i.e. we already ran a preliminary 'status' command.
- L36 _prototype_ `bool GetShellIsWarmedUp();` (scope `PlasticSourceControlShell`) — Retrieve whether the current shell process was already warmed up - i.e. we already ran a preliminary 'status' command. @returns true if the shell process was already warmed up
- L49 _prototype_ `bool RunCommand(const FString& InCommand, const TArray<FString>& InParameters, const TArray<FString>& InFiles, FString& OutResults, FString& OutErrors);` (scope `PlasticSourceControlShell`) — Run a Plastic command - the result is the output of cm, as a multi-line string. @param	InCommand			The Plastic command - e.g. commit @param	InParameters		The parameters to the Plastic command @param	InFiles				The files to be operated on @param	OutResults			The results (from StdOut) as a multi-line string. @param	OutErrors			Any errors (from StdErr) as a multi-line string. @returns true if the command succeeded and returned no errors

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlState.h` (Private)


#### enum `EWorkspaceState`  
`enum class EWorkspaceState`  
_L12-28_
- L14 _public enumerator_ `Unknown`
- L15 _public enumerator_ `Ignored`
- L16 _public enumerator_ `Controlled` — called "Pristine" in Perforce, "Unchanged" in Git, "Clean" in SVN
- L17 _public enumerator_ `CheckedOutChanged` — Checked-out, with changes (or without knowing for older version of Unity Version Control)
- L18 _public enumerator_ `CheckedOutUnchanged` — Checked-out with no changes (cannot be checked-in and can be reverted by UndoUnchanged)
- L19 _public enumerator_ `Added`
- L20 _public enumerator_ `Moved` — Renamed
- L21 _public enumerator_ `Copied`
- L22 _public enumerator_ `Replaced` — Replaced / Merged
- L23 _public enumerator_ `Deleted`
- L24 _public enumerator_ `LocallyDeleted` — Missing
- L25 _public enumerator_ `Changed` — Locally Changed but not CheckedOut
- L26 _public enumerator_ `Conflicted`
- L27 _public enumerator_ `Private` — "Not Controlled"/"Not In Depot"/"Untracked"

#### class `FPlasticSourceControlState`  
`class FPlasticSourceControlState : public ISourceControlState`  
_L30-230_
- inherits: `ISourceControlState`
- L33 _public function_ `explicit FPlasticSourceControlState(FString&& InLocalFilename) : LocalFilename(MoveTemp(InLocalFilename))`
- L38 _public function_ `FPlasticSourceControlState(FString&& InLocalFilename, EWorkspaceState InWorkspaceState) : LocalFilename(MoveTemp(InLocalFilename)) , WorkspaceState(InWorkspaceState)`
- L44 _public prototype_ `FPlasticSourceControlState() = delete;`
- L45 _public prototype_ `FPlasticSourceControlState(const FPlasticSourceControlState& InState) = delete;`
- L46 _public prototype_ `const FPlasticSourceControlState& operator=(const FPlasticSourceControlState& InState) = delete;`
- L48 _public function_ `FPlasticSourceControlState(FPlasticSourceControlState&& InState)`
- L54 _public function_ `bool operator==(const FPlasticSourceControlState& InState) const` — Comparison operator designed to detect and report only meaningful changes to the Editor, mainly for the purpose of updating Content Browser overlay icons
- L61 _public function_ `bool operator!=(const FPlasticSourceControlState& InState) const`
- L66 _public function_ `const FPlasticSourceControlState& operator=(FPlasticSourceControlState&& InState)`
- L72 _public function_ `void Move(FPlasticSourceControlState&& InState)`
- L113 _public prototype_ `const TCHAR* ToString() const;` — debug log utility
- L115 _public prototype_ `FText ToText() const;`
- L117 _public function_ `void PopulateSearchString(TArray<FString>& OutStrings) const`
- L123 _public prototype_ `virtual int32 GetHistorySize() const override;` — ISourceControlState interface
- L124 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetHistoryItem(int32 HistoryIndex) const override;`
- L125 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> FindHistoryRevision(int32 RevisionNumber) const override;`
- L126 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> FindHistoryRevision(const FString& InRevision) const override;`
- L127 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetCurrentRevision() const override;`
- L128 _public prototype_ `virtual FResolveInfo GetResolveInfo() const override;`
- L130 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L132 _public prototype_ `virtual FText GetDisplayName() const override;`
- L133 _public prototype_ `virtual FText GetDisplayTooltip() const override;`
- L134 _public prototype_ `virtual const FString& GetFilename() const override;`
- L135 _public prototype_ `virtual const FDateTime& GetTimeStamp() const override;`
- L136 _public prototype_ `virtual bool CanCheckIn() const override;`
- L137 _public prototype_ `virtual bool CanCheckout() const override;`
- L138 _public prototype_ `virtual bool IsCheckedOut() const override;`
- L139 _public prototype_ `virtual bool IsCheckedOutOther(FString* Who = nullptr) const override;`
- L140 _public prototype_ `virtual bool IsCheckedOutInOtherBranch(const FString& CurrentBranch = FString()) const override;`
- L141 _public prototype_ `virtual bool IsModifiedInOtherBranch(const FString& CurrentBranch = FString()) const override;`
- L142 _public function_ `virtual bool IsCheckedOutOrModifiedInOtherBranch(const FString& CurrentBranch = FString()) const override`
- L143 _public function_ `virtual TArray<FString> GetCheckedOutBranches() const override`
- L144 _public function_ `virtual FString GetOtherUserBranchCheckedOuts() const override`
- L145 _public prototype_ `virtual bool GetOtherBranchHeadModification(FString& HeadBranchOut, FString& ActionOut, int32& HeadChangeListOut) const override;`
- L146 _public prototype_ `virtual bool IsCurrent() const override;`
- L147 _public prototype_ `virtual bool IsSourceControlled() const override;`
- L148 _public prototype_ `virtual bool IsAdded() const override;`
- L149 _public prototype_ `virtual bool IsDeleted() const override;`
- L150 _public prototype_ `virtual bool IsIgnored() const override;`
- L151 _public prototype_ `virtual bool CanEdit() const override;`
- L152 _public prototype_ `virtual bool IsUnknown() const override;`
- L153 _public prototype_ `virtual bool IsModified() const override;`
- L154 _public prototype_ `virtual bool CanAdd() const override;`
- L155 _public prototype_ `virtual bool CanDelete() const override;`
- L156 _public prototype_ `virtual bool IsConflicted() const override;`
- L157 _public prototype_ `virtual bool CanRevert() const override;`
- L159 _public prototype_ `bool IsPendingChanges() const;`
- L160 _public prototype_ `bool IsCheckedOutImplementation() const;`
- L161 _public prototype_ `bool IsLocked() const;`
- L162 _public prototype_ `bool IsRetainedInOtherBranch() const;`
- L166 _public member_ `TPlasticSourceControlHistory History;` — History of the item, if any
- L169 _public member_ `FString LocalFilename;` — Filename on disk
- L172 _public member_ `FString RepSpec;` — Depot and Server info (in the form repo@server:port)
- L175 _public member_ `FResolveInfo PendingResolveInfo;` — Pending rev info with which a file must be resolved, invalid if no resolve pending
- L178 _public member_ `TArray<FString> PendingMergeParameters;` — Unity Version Control Parameters of the merge in progress
- L181 _public member_ `FString LockedBy;` — If a user (another or ourself) has this file locked, this contains their name.
- L184 _public member_ `FString LockedWhere;` — Location (Workspace) where the file was exclusively checked-out.
- L187 _public member_ `FString LockedBranch;` — Branch where the file was Locked or is Retained.
- L190 _public member_ `int32 LockedId = INVALID_REVISION;` — Item id of the locked file (for an admin to unlock it).
- L193 _public member_ `FDateTime LockedDate = 0;` — Date when the file was Locked.
- L196 _public member_ `FString RetainedBy;` — If a user (another or ourself) has this file Retained on another branch, this contains their name.
- L199 _public member_ `EWorkspaceState WorkspaceState = EWorkspaceState::Unknown;` — State of the workspace
- L202 _public member_ `int32 DepotRevisionChangeset = INVALID_REVISION;` — Latest revision number of the file in the depot (on the current branch)
- L205 _public member_ `int32 LocalRevisionChangeset = INVALID_REVISION;` — Latest revision number at which a file was synced to before being edited
- L208 _public member_ `FString MovedFrom;` — Original name in case of a Moved/Renamed file
- L211 _public member_ `FPlasticSourceControlChangelist Changelist;` — Changelist containing this file
- L214 _public member_ `FDateTime TimeStamp = 0;` — The timestamp of the last update
- L217 _public member_ `FString HeadBranch;` — The branch with the head change list
- L220 _public member_ `FString HeadAction;` — The type of action of the last modification
- L223 _public member_ `FString HeadUserName;` — The user of the last modification
- L226 _public member_ `int64 HeadModTime;` — The last file modification time
- L229 _public member_ `int32 HeadChangeList;` — The change list of the last modification

#### Free symbols / members of external scopes

- L232 _typedef_ `typedef TSharedRef<FPlasticSourceControlState, ESPMode::ThreadSafe> FPlasticSourceControlStateRef;`
- L233 _typedef_ `typedef TSharedPtr<FPlasticSourceControlState, ESPMode::ThreadSafe> FPlasticSourceControlStatePtr;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlUtils.h` (Private)


#### enum `PlasticSourceControlUtils::EStatusSearchType`  
`enum class EStatusSearchType`  
_L218-222_
- desc: Specify the "search type" for the "status" command
- L220 _public enumerator_ `All` — status --all --ignored (this can take much longer, searching for local changes, especially on the first call)
- L221 _public enumerator_ `ControlledOnly` — status --controlledchanged

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef TSharedRef<class FPlasticSourceControlBranch, ESPMode::ThreadSafe> FPlasticSourceControlBranchRef;`
- L15 _typedef_ `typedef TSharedRef<class FPlasticSourceControlChangeset, ESPMode::ThreadSafe> FPlasticSourceControlChangesetRef;`
- L16 _typedef_ `typedef TSharedRef<class FPlasticSourceControlLock, ESPMode::ThreadSafe> FPlasticSourceControlLockRef;`
- L17 _typedef_ `typedef TSharedRef<class FPlasticSourceControlState, ESPMode::ThreadSafe> FPlasticSourceControlStateRef;`
- L21 _namespace_ `namespace PlasticSourceControlUtils`
- L34 _prototype_ `bool RunCommand(const FString& InCommand, const TArray<FString>& InParameters, const TArray<FString>& InFiles, FString& OutResults, FString& OutErrors);` (scope `PlasticSourceControlUtils`) — Run a Plastic command - the result is the output of cm, as a multi-line string. @param	InCommand			The Plastic command - e.g. commit @param	InParameters		The parameters to the Plastic command @param	InFiles				The files to be operated on @param	OutResults			The results (from StdOut) as a multi-line string. @param	OutErrors			Any errors (from StdErr) as a multi-line string. @returns true if the command succeeded and returned no errors
- L46 _prototype_ `bool RunCommand(const FString& InCommand, const TArray<FString>& InParameters, const TArray<FString>& InFiles, TArray<FString>& OutResults, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Run a Plastic command - the result is parsed in an array of strings. @param	InCommand			The Plastic command - e.g. commit @param	InParameters		The parameters to the Plastic command @param	InFiles				The files to be operated on @param	OutResults			The results (from StdOut) as an array per-line @param	OutErrorMessages	Any errors (from StdErr) as an array per-line @returns true if the command succeeded and returned no errors
- L51 _prototype_ `FString FindPlasticBinaryPath();` (scope `PlasticSourceControlUtils`) — Find the path to the Plastic binary: for now relying on the Path to access the "cm" command.
- L58 _prototype_ `bool OpenDesktopApplication(const bool bInBranchExplorer = false);` (scope `PlasticSourceControlUtils`) — Open the Desktop Application. @param	bInBranchExplorer	Should it open the Branch Explorer instead of the Workspace Explorer (false by default)?
- L65 _prototype_ `bool OpenDesktopApplicationForDiff(const int32 InChangesetId);` (scope `PlasticSourceControlUtils`) — Open the Desktop Application for diffing a Changeset. @param	InChangesetId		Changeset to diff
- L73 _prototype_ `bool OpenDesktopApplicationForDiff(const int32 InChangesetIdSrc, const int32 InChangesetIdDst);` (scope `PlasticSourceControlUtils`) — Open the Desktop Application for diffing a couple of Changesets. @param	InChangesetIdSrc	Source (Left) Changeset to diff @param	InChangesetIdDst	Destination (Right) Changeset to diff
- L80 _prototype_ `bool OpenDesktopApplicationForDiff(const FString& InBranchName);` (scope `PlasticSourceControlUtils`) — Open the Desktop Application for diffing a whole Branch. @param	InBranchName		Name of the Branch to diff
- L87 _prototype_ `void OpenLockRulesInCloudDashboard(const FString& InOrganizationName);` (scope `PlasticSourceControlUtils`) — Open the Unity Cloud Dashboard on the page to show and manage Lock Rules. @param	InOrganizationName	Name of the organization to use, from the server URL
- L95 _prototype_ `bool GetWorkspacePath(const FString& InPathToGameDir, FString& OutWorkspaceRoot);` (scope `PlasticSourceControlUtils`) — Find the root of the Plastic workspace, looking from the GameDir and upward in its parent directories @param InPathToGameDir		The path to the Game Directory @param OutWorkspaceRoot		The path to the root directory of the Plastic workspace if found, else the path to the GameDir @returns true if the command succeeded
- L102 _prototype_ `bool GetPlasticScmVersion(FSoftwareVersion& OutPlasticScmVersion);` (scope `PlasticSourceControlUtils`) — Get Unity Version Control CLI version @param	OutCliVersion		Version of the Unity Version Control Command Line Interface tool @returns true if the command succeeded
- L109 _prototype_ `bool GetCmLocation(FString& OutCmLocation);` (scope `PlasticSourceControlUtils`) — Get Unity Version Control CLI location @param	OutCmLocation		Path to the "cm" executable @returns true if the command succeeded
- L115 _prototype_ `bool GetConfigSetFilesAsReadOnly();` (scope `PlasticSourceControlUtils`) — Checks weather Unity Version Control is configured to set files as read-only on update & checkin @returns true if SetFilesAsReadOnly is enabled in client.conf
- L121 _prototype_ `FString GetConfigDefaultRepServer();` (scope `PlasticSourceControlUtils`) — Get from config the name of the default cloud organization or the url of the default on-prem server @returns Returns the location of the default repository server
- L127 _prototype_ `FString GetDefaultUserName();` (scope `PlasticSourceControlUtils`) — Get Unity Version Control user for the default server @returns	Name of the Unity Version Control user configured globally
- L134 _prototype_ `FString GetProfileUserName(const FString& InServerUrl);` (scope `PlasticSourceControlUtils`) — Get Unity Version Control user for the specified server @param	InServerUrl		Name of the specified server @returns	Name of the Unity Version Control user for the specified server
- L142 _prototype_ `bool GetWorkspaceName(const FString& InWorkspaceRoot, FString& OutWorkspaceName, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Get workspace name @param	InWorkspaceRoot		The workspace from where to run the command - typically the Project path @param	OutWorkspaceName	Name of the current workspace @param	OutErrorMessages	Any errors (from StdErr) as an array per-line
- L153 _prototype_ `bool GetWorkspaceInfo(FString& OutWorkspaceSelector, FString& OutBranchName, FString& OutRepositoryName, FString& OutServerUrl, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Get workspace info: the current branch, repository name, and server URL @param	OutWorkspaceSelector	Name of the current branch, changeset or label depending on the workspace selector @param	OutBranchName		Name of the current branch @param	OutRepositoryName	Name of the repository of the current workspace @param	OutServerUrl		URL/Port of the server of the repository @param	OutErrorMessages	Any errors (from StdErr) as an array per-line
- L162 _prototype_ `bool GetChangesetNumber(int32& OutChangesetNumber, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Get the current changeset number from the workspace (-1 for a partial workspace) @param	OutChangesetNumber	Current changeset number @param	OutErrorMessages	Any errors (from StdErr) as an array per-line
- L174 _prototype_ `bool RunCheckConnection(FString& OutWorkspaceSelector, FString& OutBranchName, FString& OutRepositoryName, FString& OutServerUrl, TArray<FString>& OutInfoMessages, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Get workspace info and check the connection to the server @param	OutWorkspaceSelector	Name of the current branch, changeset or label depending on the workspace selector @param	OutBranchName			Name of the current branch when available @param	OutRepositoryName		Name of the repository of the current workspace @param	OutServerUrl			URL/Port of the server of the repository @param	OutInfoMessages			Result of the connection test @param	OutErrorMessages		Any errors (from StdErr) as an array per-line
- L183 _prototype_ `FString UserNameToDisplayName(const FString& InUserName);` (scope `PlasticSourceControlUtils`) — Use the Project Settings to replace Unity Version Control full username/e-mail by a shorter version for display. Used when retrieving the username of a revision, to display in history and content browser asset tooltip. @param	InUserName			The Unity Version Control username to shorten for display.
- L188 _prototype_ `void InvalidateLocksCache();` (scope `PlasticSourceControlUtils`) — Invalidate the cache of locks so that the next call to RunListLocks() will not use it and actually run the cm lock list command
- L198 _prototype_ `bool RunListLocks(const FPlasticSourceControlProvider& InProvider, const bool bInForAllDestBranches, TArray<FPlasticSourceControlLockRef>& OutLocks);` (scope `PlasticSourceControlUtils`) — Run a Plastic "lock list" command and parse it. @param	InProvider				The source control provider to get the repository and current branch to ask the locks for @param   bInForAllDestBranches	Retrieve locks for all destination branches, or restrict them to only those applying to the working branch @param	OutLocks				The list of locks @returns true if the command succeeded and returned no errors
- L207 _prototype_ `TArray<FPlasticSourceControlLockRef> GetLocksForWorkingBranch(const FPlasticSourceControlProvider& InProvider, const TArray<FString>& InFiles);` (scope `PlasticSourceControlUtils`) — Get locks applying to the working branch for the specified files. @param	InProvider			The source control provider to get the repository and current branch to ask the locks for @param	InFiles				The files to be operated on (server paths) @return	OutLocks			The list of corresponding locks if any
- L215 _prototype_ `TArray<FString> LocksToFileNames(const FString InWorkspaceRoot, const TArray<FPlasticSourceControlLockRef>& InLocks);` (scope `PlasticSourceControlUtils`) — Get the list of filenames from the list of locks @param	InWorkspaceRoot		The workspace from where to run the command - typically the Project path @param	InLocks				Locks to get the file names for @return	List of absolute filenames
- L235 _prototype_ `bool RunUpdateStatus(const TArray<FString>& InFiles, const EStatusSearchType InSearchType, const bool bInUpdateHistory, TArray<FString>& OutErrorMessages, TArray<FPlasticSourceControlState>& OutStates, int32& OutChangeset);` (scope `PlasticSourceControlUtils`) — Run a Plastic "status" command and parse it. @param	InFiles				The files to be operated on @param	InSearchType		Call "status" with "--all", or with just "--controlledchanged" when doing only a quick check following a source control operation @param	bInUpdateHistory	If getting the history of files, force execute the fileinfo command required to do get RepSpec of xlinks (history view or visual diff) @param	OutErrorMessages	Any errors (from StdErr) as an array per-line @param	OutStates			States of the files @param	OutChangeset		The current Changeset Number @returns true if the command succeeded and returned no errors
- L244 _prototype_ `bool RunGetFile(const FString& InRevSpec, const FString& InDumpFileName);` (scope `PlasticSourceControlUtils`) — Run a Plastic "cat" command to dump the binary content of a revision into a file. @param	InRevSpec				The revision specification to get @param	InDumpFileName			The temporary file to dump the revision @returns true if the command succeeded and returned no errors
- L253 _prototype_ `bool RunGetHistory(const bool bInUpdateHistory, TArray<FPlasticSourceControlState>& InOutStates, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Run Plastic "history" and "log" commands and parse their XML results. @param	bInUpdateHistory	If getting the history of files, versus only checking the heads of branches to detect newer commits @param	InOutStates			The file states to update with the history @param	OutErrorMessages	Any errors (from StdErr) as an array per-line
- L264 _prototype_ `bool RunUpdate(const TArray<FString>& InFiles, const bool bInIsPartialWorkspace, const FString& InChangesetId, TArray<FString>& OutUpdatedFiles, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Run a Plastic "update" command to sync the workspace and parse its XML results. @param	InFiles					The files or paths to sync @param	bInIsPartialWorkspace	Whether running on a partial/gluon or regular/full workspace @param	InChangesetId			The optional changeset to sync to (leave empty to sync to the latest in the branch) @param	OutUpdatedFiles			The files that where updated @param	OutErrorMessages		Any errors (from StdErr) as an array per-line
- L272 _prototype_ `bool RunGetChangelists(TArray<FPlasticSourceControlChangelistState>& OutChangelistsStates, TArray<TArray<FPlasticSourceControlState>>& OutCLFilesStates, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Run a Plastic "status --changelist --xml" and parse its XML result. @param	OutChangelistsStates	The list of changelists (without their files) @param	OutCLFilesStates		The list of files per changelist @param	OutErrorMessages		Any errors (from StdErr) as an array per-line
- L279 _prototype_ `bool RunGetShelves(TArray<FPlasticSourceControlChangelistState>& InOutChangelistsStates, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Run find "shelves where owner='me'" and for each shelve matching a changelist a "diff sh:<ShelveId>" and parse their results. @param	InOutChangelistsStates	The list of changelists, filled with their shelved files @param	OutErrorMessages		Any errors (from StdErr) as an array per-line
- L290 _prototype_ `bool RunGetShelve(const int32 InShelveId, FString& OutComment, FDateTime& OutDate, FString& OutOwner, TArray<FPlasticSourceControlRevision>& OutBaseRevisions, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Run find "shelves where ShelveId='NNN'" and a "diff sh:<ShelveId>" and parse their results. @param	InShelveId			Shelve Id @param	OutComment			Shelve Comment @param	OutDate				Shelve Date @param	OutOwner			Shelve Owner @param	OutStates			Files in the shelve and their base revision id @param	OutErrorMessages	Any errors (from StdErr) as an array per-line
- L299 _prototype_ `void AddShelvedFileToChangelist(FPlasticSourceControlChangelistState& InOutChangelistsState, FString&& InFilename, EWorkspaceState InShelveStatus, FString&& InMovedFrom);` (scope `PlasticSourceControlUtils`) — Add a file to the shelve associated with a changelist. @param	InOutChangelistsState	The changelist to add the file to @param	InFilename				The file to add to the shelve @param	InShelveStatus			The status of the file @param	InMovedFrom				If moved, the original filename
- L309 _prototype_ `bool RunGetChangesets(const FDateTime& InFromDate, TArray<FPlasticSourceControlChangesetRef>& OutChangesets, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Run find "changesets where date >= 'YYYY-MM-DD'" and parse the results. @param	InFromDate				The date to search from @param	OutChangesets			The list of changesets, without their files @param	OutErrorMessages		Any errors (from StdErr) as an array per-line @see RunGetChangesetFiles() below used to populated a specific changeset with its list of files
- L317 _prototype_ `bool RunGetChangesetFiles(const FPlasticSourceControlChangesetRef& InChangeset, TArray<FPlasticSourceControlStateRef>& OutFiles, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Run "log cs:<ChangesetId> --xml" and parse the results to populate the files from the specified changeset. @param	InChangeset				The changeset to get the files changed @param	OutFiles				The files changed in the specified changeset @param	OutErrorMessages		Any errors (from StdErr) as an array per-line
- L325 _prototype_ `bool RunGetBranches(const FDateTime& InFromDate, TArray<FPlasticSourceControlBranchRef>& OutBranches, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Run find "branches where date >= 'YYYY-MM-DD' or changesets >= 'YYYY-MM-DD'" and parse the results. @param	InFromDate				The date to search from @param	OutBranches				The list of branches @param	OutErrorMessages		Any errors (from StdErr) as an array per-line
- L335 _prototype_ `bool RunSwitch(const FString& InBranchName, const int32 InChangesetId, const bool bInIsPartialWorkspace, TArray<FString>& OutUpdatedFiles, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Run switch br:/name and parse the results. @param	InBranchName			The name of the branch to switch the workspace to (optional, only used if no InChangesetId) @param	InChangesetId			The name of the changeset to switch the workspace to (optional, overrides InBranchName if set) @param	bInIsPartialWorkspace	Whether running on a partial/gluon or regular/full workspace @param	OutUpdatedFiles			The files that where updated @param	OutErrorMessages		Any errors (from StdErr) as an array per-line
- L343 _prototype_ `bool RunMergeBranch(const FString& InBranchName, TArray<FString>& OutUpdatedFiles, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Run merge br:/name and parse the results. @param	InBranchName			The name of the branch to merge to the current branch @param	OutUpdatedFiles			The files that where updated @param	OutErrorMessages		Any errors (from StdErr) as an array per-line
- L351 _prototype_ `bool RunCreateBranch(const FString& InBranchName, const FString& InComment, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Run branch create <name> --commentsfile @param	InBranchName			The name of the branch to create @param	InComment				The comment for the new branch to create @param	OutErrorMessages		Any errors (from StdErr) as an array per-line
- L359 _prototype_ `bool RunRenameBranch(const FString& InOldName, const FString& InNewName, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Run branch rename <old name> <new name> @param	InOldName				The old name of the branch to rename @param	InNewName				The new name to rename the branch to @param	OutErrorMessages		Any errors (from StdErr) as an array per-line
- L366 _prototype_ `bool RunDeleteBranches(const TArray<FString>& InBranchNames, TArray<FString>& OutErrorMessages);` (scope `PlasticSourceControlUtils`) — Run branch delete <name1> <name2 ...> @param	InBranchNames			The name of the branch(es) to delete @param	OutErrorMessages		Any errors (from StdErr) as an array per-line
- L372 _prototype_ `bool UpdateCachedStates(TArray<FPlasticSourceControlState>&& InStates);` (scope `PlasticSourceControlUtils`) — Helper function for various commands to update cached states. @returns true if any states were updated
- L378 _prototype_ `void RemoveRedundantErrors(FPlasticSourceControlCommand& InCommand, const FString& InFilter);` (scope `PlasticSourceControlUtils`) — Remove redundant errors (that contain a particular string) and also update the commands success status if all errors were removed.
- L385 _prototype_ `void SwitchVerboseLogs(const bool bInEnable);` (scope `PlasticSourceControlUtils`) — Change LogSourceControl verbosity level at startup and when toggled from the Plastic Source Control Settings Override to Verbose or back to Log, but only if the current log verbosity is not already set to VeryVerbose
- L391 _prototype_ `FString FindCommonDirectory(const FString& InPath1, const FString& InPath2);` (scope `PlasticSourceControlUtils`) — Find the best(longest) common directory between two paths, terminated by a slash, returning an empty string if none. Assumes that both input strings are already normalized paths, slash delimited, for performance reason.

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlVersions.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace PlasticSourceControlVersions`
- L18 _variable_ `static FSoftwareVersion OldestSupported(TEXT("9.0.` (scope `PlasticSourceControlVersions`) — Oldest supported version of "cm" 9.0.16.4839 cm changelist 'persistent' flag now contain a '--' prefix. https://plasticscm.com/download/releasenotes/9.0.16.4839 (2021/01/05)
- L22 _variable_ `static const FSoftwareVersion NewChangelistFileArgs(TEXT("11.0` (scope `PlasticSourceControlVersions`) — 11.0.16.7248 add support for --descriptionfile for multi-line descriptions and support for special characters https://plasticscm.com/download/releasenotes/11.0.16.7248 (2022/07/28)
- L26 _variable_ `static const FSoftwareVersion ShelvesetApplySelection(TEXT("11.0` (scope `PlasticSourceControlVersions`) — 11.0.16.7504 add support for 'cm shelveset apply' to only unshelved the desired changes from a shelve https://plasticscm.com/download/releasenotes/11.0.16.7504 (2022/10/13)
- L31 _variable_ `static const FSoftwareVersion NewHistoryLimit(TEXT("11.0` (scope `PlasticSourceControlVersions`) — 11.0.16.7608 add support for history --limit. It displays the N last revisions of the specified items. https://plasticscm.com/download/releasenotes/11.0.16.7608 (2022/11/07) NOTE: this is also the first version aware of Unreal Engine 5 "UnrealEditor.exe"
- L35 _variable_ `static const FSoftwareVersion UndoCheckoutKeepChanges(TEXT("11.0` (scope `PlasticSourceControlVersions`) — 11.0.16.7665 add support for undocheckout --keepchanges. It allows undo checkout and preserve all local changes. https://plasticscm.com/download/releasenotes/11.0.16.7665 (2022/12/01)
- L39 _variable_ `static const FSoftwareVersion StatusIsCheckedOutChanged(TEXT("11.0` (scope `PlasticSourceControlVersions`) — 11.0.16.7709 add support for status --iscochanged. It uses "CO+CH" vs "CO" to distinguish CheckedOut with/without changes. https://plasticscm.com/download/releasenotes/11.0.16.7709 (2023/01/12)
- L43 _variable_ `static const FSoftwareVersion MergeXml(TEXT("11.0` (scope `PlasticSourceControlVersions`) — 11.0.16.7726 add support for merge --xml https://plasticscm.com/download/releasenotes/11.0.16.7726 (2023/01/19)
- L49 _variable_ `static const FSoftwareVersion SmartLocks(TEXT("11.0` (scope `PlasticSourceControlVersions`) — 11.0.16.8101 Introducing Smart Locks https://plasticscm.com/download/releasenotes/11.0.16.8101 (2023/07/06) 11.0.16.8133 add support for non-localized --datetimeformat https://plasticscm.com/download/releasenotes/11.0.16.8133 (2023/08/03)
- L53 _variable_ `static const FSoftwareVersion WorkingBranch(TEXT("11.0` (scope `PlasticSourceControlVersions`) — 11.0.16.8445 lock list new --workingbranch option to only list the locks that apply to the destination branch of the specified branch. https://plasticscm.com/download/releasenotes/11.0.16.8445 (2024/02/22)

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlWorkspaceCreation.h` (Private)


#### class `FPlasticSourceControlWorkspaceCreation`  
`class FPlasticSourceControlWorkspaceCreation`  
_L12-47_
- L25 _public member_ `FParameters WorkspaceParams;`
- L27 _public prototype_ `void MakeWorkspace(const FParameters& InParameters);`
- L31 _private prototype_ `void LaunchMakeWorkspaceOperation();` — Launch initial asynchronous add and commit operations
- L32 _private prototype_ `void LaunchMarkForAddOperation();`
- L33 _private prototype_ `void LaunchCheckInOperation();`
- L36 _private prototype_ `void OnMakeWorkspaceOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Delegates called when a source control operation has completed
- L37 _private prototype_ `void OnMarkForAddOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);`
- L38 _private prototype_ `void OnCheckInOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);`
- L40 _private prototype_ `void OnSourceControlOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Generic notification handler
- L43 _private member_ `FNotification Notification;` — Ongoing notification for a long-running asynchronous source control operation, if any
- L45 _private prototype_ `const FString GetIgnoreFileName() const;`
- L46 _private prototype_ `TArray<FString> GetProjectFiles() const;`

#### struct `FPlasticSourceControlWorkspaceCreation::FParameters`  
`struct FParameters`  
_L15-23_
- L17 _public member_ `FText WorkspaceName;`
- L18 _public member_ `FText RepositoryName;`
- L19 _public member_ `FText ServerUrl;`
- L20 _public member_ `bool bCreatePartialWorkspace = false;`
- L21 _public member_ `bool bAutoInitialCommit = true;`
- L22 _public member_ `FText InitialCommitMessage;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/SPlasticSourceControlBranchRow.h` (Private)


#### class `SPlasticSourceControlBranchRow`  
`class SPlasticSourceControlBranchRow : public SMultiColumnTableRow<FPlasticSourceControlBranchRef>`  
_L61-96_
- inherits: `SMultiColumnTableRow<FPlasticSourceControlBranchRef>`
- L64 _public function_ `SLATE_BEGIN_ARGS(SPlasticSourceControlBranchRow) : _BranchToVisualize(nullptr) , _bIsCurrentBranch(false) , _HighlightText()`
- L82 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwner);` — Construct a row child widgets of the ListView. @param InArgs Parameters including the branch to visualize in this row. @param InOwner The owning ListView.
- L85 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnId) override;` — SMultiColumnTableRow overrides
- L89 _private member_ `FPlasticSourceControlBranch* BranchToVisualize;` — The branch that we are visualizing in this row.
- L92 _private member_ `bool bIsCurrentBranch;` — True if this is the current branch, to be highlighted on the list of branches.
- L95 _private member_ `TAttribute<FText> HighlightText;` — The search text to highlight if any

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef TSharedRef<class FPlasticSourceControlBranch, ESPMode::ThreadSafe> FPlasticSourceControlBranchRef;`
- L13 _typedef_ `typedef TSharedPtr<class FPlasticSourceControlBranch, ESPMode::ThreadSafe> FPlasticSourceControlBranchPtr;`
- L18 _namespace_ `namespace PlasticSourceControlBranchesListViewColumn`
- L21 _namespace_ `namespace Name` (scope `PlasticSourceControlBranchesListViewColumn`)
- L23 _prototype_ `FName Id();` (scope `PlasticSourceControlBranchesListViewColumn::Name`)
- L24 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlBranchesListViewColumn::Name`)
- L25 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlBranchesListViewColumn::Name`)
- L29 _namespace_ `namespace Repository` (scope `PlasticSourceControlBranchesListViewColumn`)
- L31 _prototype_ `FName Id();` (scope `PlasticSourceControlBranchesListViewColumn::Repository`)
- L32 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlBranchesListViewColumn::Repository`)
- L33 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlBranchesListViewColumn::Repository`)
- L37 _namespace_ `namespace CreatedBy` (scope `PlasticSourceControlBranchesListViewColumn`)
- L39 _prototype_ `FName Id();` (scope `PlasticSourceControlBranchesListViewColumn::CreatedBy`)
- L40 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlBranchesListViewColumn::CreatedBy`)
- L41 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlBranchesListViewColumn::CreatedBy`)
- L45 _namespace_ `namespace Date` (scope `PlasticSourceControlBranchesListViewColumn`)
- L47 _prototype_ `FName Id();` (scope `PlasticSourceControlBranchesListViewColumn::Date`)
- L48 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlBranchesListViewColumn::Date`)
- L49 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlBranchesListViewColumn::Date`)
- L53 _namespace_ `namespace Comment` (scope `PlasticSourceControlBranchesListViewColumn`)
- L55 _prototype_ `FName Id();` (scope `PlasticSourceControlBranchesListViewColumn::Comment`)
- L56 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlBranchesListViewColumn::Comment`)
- L57 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlBranchesListViewColumn::Comment`)

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/SPlasticSourceControlBranchesWidget.h` (Private)


#### class `SPlasticSourceControlBranchesWidget`  
`class SPlasticSourceControlBranchesWidget : public SCompoundWidget`  
_L23-140_
- inherits: `SCompoundWidget`
- desc: Widget displaying the list of branches in the tab window, see FPlasticSourceControlBranchesWindow
- L25 _private function_ `SLATE_BEGIN_ARGS(SPlasticSourceControlBranchesWidget)`
- L26 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L32 _private prototype_ `static bool IsBranchNameValid(const FString& InBranchName);`
- L34 _private prototype_ `void CreateBranch(const FString& InParentBranchName, const FString& InNewBranchName, const FString& InNewBranchComment, const bool bInSwitchWorkspace);`
- L35 _private prototype_ `void RenameBranch(const FString& InOldBranchName, const FString& InNewBranchName);`
- L36 _private prototype_ `void DeleteBranches(const TArray<FString>& InBranchNames);`
- L39 _private prototype_ `TSharedRef<SWidget> CreateToolBar();`
- L40 _private prototype_ `TSharedRef<SWidget> CreateContentPanel();`
- L42 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FPlasticSourceControlBranchRef InBranch, const TSharedRef<STableViewBase>& OwnerTable);`
- L43 _private prototype_ `void OnHiddenColumnsListChanged();`
- L45 _private prototype_ `void OnSearchTextChanged(const FText& InFilterText);`
- L46 _private prototype_ `void PopulateItemSearchStrings(const FPlasticSourceControlBranch& InItem, TArray<FString>& OutStrings);`
- L48 _private prototype_ `TSharedRef<SWidget> BuildFromDateDropDownMenu();`
- L49 _private prototype_ `void OnFromDateChanged(int32 InFromDateInDays);`
- L51 _private prototype_ `void OnRefreshUI();`
- L53 _private prototype_ `EColumnSortPriority::Type GetColumnSortPriority(const FName InColumnId) const;`
- L54 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName InColumnId) const;`
- L55 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type InSortPriority, const FName& InColumnId, const EColumnSortMode::Type InSortMode);`
- L57 _private prototype_ `void SortBranchView();`
- L59 _private prototype_ `TArray<FString> GetSelectedBranches();`
- L61 _private prototype_ `TSharedPtr<SWidget> OnOpenContextMenu();`
- L63 _private prototype_ `TSharedPtr<SWindow> CreateDialogWindow(FText&& InTitle);`
- L64 _private prototype_ `void OpenDialogWindow(TSharedPtr<SWindow>& InDialogWindowPtr);`
- L65 _private prototype_ `void OnDialogClosed(const TSharedRef<SWindow>& InWindow);`
- L67 _private prototype_ `void OnCreateBranchClicked(FString InParentBranchName);`
- L68 _private prototype_ `void OnSwitchToBranchClicked(FString InBranchName);`
- L69 _private prototype_ `void OnMergeBranchClicked(FString InBranchName);`
- L70 _private prototype_ `void OnRenameBranchClicked(FString InBranchName);`
- L71 _private prototype_ `void OnDeleteBranchesClicked(TArray<FString> InBranchNames);`
- L73 _private prototype_ `void StartRefreshStatus();`
- L74 _private prototype_ `void TickRefreshStatus(double InDeltaTime);`
- L75 _private prototype_ `void EndRefreshStatus();`
- L77 _private prototype_ `void RequestBranchesRefresh();`
- L80 _private prototype_ `void OnGetBranchesOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Source control callbacks
- L81 _private prototype_ `void OnCreateBranchOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult, const bool bInSwitchWorkspace);`
- L82 _private prototype_ `void OnSwitchToBranchOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);`
- L83 _private prototype_ `void OnMergeBranchOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);`
- L84 _private prototype_ `void OnRenameBranchOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);`
- L85 _private prototype_ `void OnDeleteBranchesOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);`
- L86 _private prototype_ `void OnSourceControlProviderChanged(ISourceControlProvider& OldProvider, ISourceControlProvider& NewProvider);`
- L89 _private prototype_ `void HandleSourceControlStateChanged();` — Delegate handler for when source control state changes
- L91 _private function_ `SListView<FPlasticSourceControlBranchRef>* GetListView() const`
- L96 _private prototype_ `void SwitchToBranchWithConfirmation(const FString& InSelectedBranch);`
- L99 _private prototype_ `void OnItemDoubleClicked(FPlasticSourceControlBranchRef InBranch);` — Double click to switch to the branch
- L102 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Interpret F5, Enter and Delete keys
- L105 _private member_ `TSharedPtr<SSearchBox> BranchSearchBox;`
- L107 _private member_ `FName PrimarySortedColumn;`
- L108 _private member_ `FName SecondarySortedColumn;`
- L109 _private member_ `EColumnSortMode::Type PrimarySortMode = EColumnSortMode::Ascending;`
- L110 _private member_ `EColumnSortMode::Type SecondarySortMode = EColumnSortMode::None;`
- L112 _private member_ `TArray<FName> HiddenColumnsList;`
- L114 _private member_ `bool bShouldRefresh = false;`
- L115 _private member_ `bool bSourceControlAvailable = false;`
- L117 _private member_ `FText RefreshStatus;`
- L118 _private member_ `bool bIsRefreshing = false;`
- L119 _private member_ `double RefreshStatusStartSecs;`
- L121 _private member_ `FString WorkspaceSelector;`
- L124 _private member_ `FNotification Notification;` — Ongoing notification for a long-running asynchronous source control operation, if any
- L126 _private member_ `TSharedPtr<SListView<FPlasticSourceControlBranchRef>> BranchesListView;`
- L127 _private member_ `TSharedPtr<TTextFilter<const FPlasticSourceControlBranch&>> SearchTextFilter;`
- L129 _private member_ `TMap<int32, FText> FromDateInDaysValues;`
- L130 _private member_ `int32 FromDateInDays = 30;`
- L132 _private member_ `TArray<FPlasticSourceControlBranchRef> SourceControlBranches;` — Full list from source (filtered by date)
- L133 _private member_ `TArray<FPlasticSourceControlBranchRef> BranchRows;` — Filtered list to display based on the search text filter
- L136 _private member_ `FDelegateHandle SourceControlStateChangedDelegateHandle;` — Delegate handle for the HandleSourceControlStateChanged function callback
- L139 _private member_ `TSharedPtr<SWindow> DialogWindowPtr;` — The dialog Window that opens when the user click on any context menu entry

#### Free symbols / members of external scopes

- L17 _typedef_ `typedef TSharedRef<class FPlasticSourceControlBranch, ESPMode::ThreadSafe> FPlasticSourceControlBranchRef;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/SPlasticSourceControlChangesetFileRow.h` (Private)


#### class `SPlasticSourceControlChangesetFileRow`  
`class SPlasticSourceControlChangesetFileRow : public SMultiColumnTableRow<FPlasticSourceControlStateRef>`  
_L46-76_
- inherits: `SMultiColumnTableRow<FPlasticSourceControlStateRef>`
- L49 _public function_ `SLATE_BEGIN_ARGS(SPlasticSourceControlChangesetFileRow) : _FileToVisualize(nullptr) , _HighlightText()`
- L65 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwner);` — Construct a row child widgets of the ListView. @param InArgs Parameters including the File to visualize in this row. @param InOwner The owning ListView.
- L68 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnId) override;` — SMultiColumnTableRow overrides
- L72 _private member_ `FPlasticSourceControlState* FileToVisualize;` — The File that we are visualizing in this row.
- L75 _private member_ `TAttribute<FText> HighlightText;` — The search text to highlight if any

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef TSharedRef<class FPlasticSourceControlState, ESPMode::ThreadSafe> FPlasticSourceControlStateRef;`
- L13 _typedef_ `typedef TSharedPtr<class FPlasticSourceControlState, ESPMode::ThreadSafe> FPlasticSourceControlStatePtr;`
- L18 _namespace_ `namespace PlasticSourceControlChangesetFilesListViewColumn`
- L21 _namespace_ `namespace Icon` (scope `PlasticSourceControlChangesetFilesListViewColumn`)
- L23 _prototype_ `FName Id();` (scope `PlasticSourceControlChangesetFilesListViewColumn::Icon`)
- L24 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlChangesetFilesListViewColumn::Icon`)
- L25 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlChangesetFilesListViewColumn::Icon`)
- L29 _namespace_ `namespace Name` (scope `PlasticSourceControlChangesetFilesListViewColumn`)
- L31 _prototype_ `FName Id();` (scope `PlasticSourceControlChangesetFilesListViewColumn::Name`)
- L32 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlChangesetFilesListViewColumn::Name`)
- L33 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlChangesetFilesListViewColumn::Name`)
- L37 _namespace_ `namespace Path` (scope `PlasticSourceControlChangesetFilesListViewColumn`)
- L39 _prototype_ `FName Id();` (scope `PlasticSourceControlChangesetFilesListViewColumn::Path`)
- L40 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlChangesetFilesListViewColumn::Path`)
- L41 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlChangesetFilesListViewColumn::Path`)

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/SPlasticSourceControlChangesetRow.h` (Private)


#### class `SPlasticSourceControlChangesetRow`  
`class SPlasticSourceControlChangesetRow : public SMultiColumnTableRow<FPlasticSourceControlChangesetRef>`  
_L62-97_
- inherits: `SMultiColumnTableRow<FPlasticSourceControlChangesetRef>`
- L65 _public function_ `SLATE_BEGIN_ARGS(SPlasticSourceControlChangesetRow) : _ChangesetToVisualize(nullptr) , _bIsCurrentChangeset(false) , _HighlightText()`
- L83 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwner);` — Construct a row child widgets of the ListView. @param InArgs Parameters including the Changeset to visualize in this row. @param InOwner The owning ListView.
- L86 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnId) override;` — SMultiColumnTableRow overrides
- L90 _private member_ `FPlasticSourceControlChangeset* ChangesetToVisualize;` — The Changeset that we are visualizing in this row.
- L93 _private member_ `bool bIsCurrentChangeset;` — True if this is the current changeset, to be highlighted on the list of changesets.
- L96 _private member_ `TAttribute<FText> HighlightText;` — The search text to highlight if any

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef TSharedRef<class FPlasticSourceControlChangeset, ESPMode::ThreadSafe> FPlasticSourceControlChangesetRef;`
- L13 _typedef_ `typedef TSharedPtr<class FPlasticSourceControlChangeset, ESPMode::ThreadSafe> FPlasticSourceControlChangesetPtr;`
- L18 _namespace_ `namespace PlasticSourceControlChangesetsListViewColumn`
- L21 _namespace_ `namespace ChangesetId` (scope `PlasticSourceControlChangesetsListViewColumn`)
- L23 _prototype_ `FName Id();` (scope `PlasticSourceControlChangesetsListViewColumn::ChangesetId`)
- L24 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlChangesetsListViewColumn::ChangesetId`)
- L25 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlChangesetsListViewColumn::ChangesetId`)
- L29 _namespace_ `namespace CreatedBy` (scope `PlasticSourceControlChangesetsListViewColumn`)
- L31 _prototype_ `FName Id();` (scope `PlasticSourceControlChangesetsListViewColumn::CreatedBy`)
- L32 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlChangesetsListViewColumn::CreatedBy`)
- L33 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlChangesetsListViewColumn::CreatedBy`)
- L37 _namespace_ `namespace Date` (scope `PlasticSourceControlChangesetsListViewColumn`)
- L39 _prototype_ `FName Id();` (scope `PlasticSourceControlChangesetsListViewColumn::Date`)
- L40 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlChangesetsListViewColumn::Date`)
- L41 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlChangesetsListViewColumn::Date`)
- L45 _namespace_ `namespace Comment` (scope `PlasticSourceControlChangesetsListViewColumn`)
- L47 _prototype_ `FName Id();` (scope `PlasticSourceControlChangesetsListViewColumn::Comment`)
- L48 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlChangesetsListViewColumn::Comment`)
- L49 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlChangesetsListViewColumn::Comment`)
- L54 _namespace_ `namespace Branch` (scope `PlasticSourceControlChangesetsListViewColumn`)
- L56 _prototype_ `FName Id();` (scope `PlasticSourceControlChangesetsListViewColumn::Branch`)
- L57 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlChangesetsListViewColumn::Branch`)
- L58 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlChangesetsListViewColumn::Branch`)

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/SPlasticSourceControlChangesetsWidget.h` (Private)


#### class `SPlasticSourceControlChangesetsWidget`  
`class SPlasticSourceControlChangesetsWidget : public SCompoundWidget`  
_L27-158_
- inherits: `SCompoundWidget`
- desc: Widget displaying the list of Changesets in the tab window, see FPlasticSourceControlChangesetsWindow
- L29 _private function_ `SLATE_BEGIN_ARGS(SPlasticSourceControlChangesetsWidget)`
- L30 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L37 _private prototype_ `TSharedRef<SWidget> CreateToolBar();`
- L38 _private prototype_ `TSharedRef<SWidget> CreateChangesetsListView();`
- L39 _private prototype_ `TSharedRef<SWidget> CreateFilesListView();`
- L41 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FPlasticSourceControlChangesetRef InChangeset, const TSharedRef<STableViewBase>& OwnerTable);`
- L42 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FPlasticSourceControlStateRef InChangeset, const TSharedRef<STableViewBase>& OwnerTable);`
- L43 _private prototype_ `void OnHiddenColumnsListChanged();`
- L45 _private prototype_ `void OnChangesetsSearchTextChanged(const FText& InFilterText);`
- L46 _private prototype_ `void OnFilesSearchTextChanged(const FText& InFilterText);`
- L47 _private prototype_ `void PopulateItemSearchStrings(const FPlasticSourceControlChangeset& InItem, TArray<FString>& OutStrings);`
- L48 _private prototype_ `void PopulateItemSearchStrings(const FPlasticSourceControlState& InItem, TArray<FString>& OutStrings);`
- L50 _private prototype_ `TSharedRef<SWidget> BuildFromDateDropDownMenu();`
- L51 _private prototype_ `void OnFromDateChanged(int32 InFromDateInDays);`
- L53 _private prototype_ `void OnChangesetsRefreshUI();`
- L54 _private prototype_ `void OnFilesRefreshUI();`
- L56 _private prototype_ `EColumnSortPriority::Type GetChangesetsColumnSortPriority(const FName InColumnId) const;`
- L57 _private prototype_ `EColumnSortMode::Type GetChangesetsColumnSortMode(const FName InColumnId) const;`
- L58 _private prototype_ `void OnChangesetsColumnSortModeChanged(const EColumnSortPriority::Type InSortPriority, const FName& InColumnId, const EColumnSortMode::Type InSortMode);`
- L60 _private prototype_ `EColumnSortPriority::Type GetFilesColumnSortPriority(const FName InColumnId) const;`
- L61 _private prototype_ `EColumnSortMode::Type GetFilesColumnSortMode(const FName InColumnId) const;`
- L62 _private prototype_ `void OnFilesColumnSortModeChanged(const EColumnSortPriority::Type InSortPriority, const FName& InColumnId, const EColumnSortMode::Type InSortMode);`
- L64 _private prototype_ `void SortChangesetsView();`
- L65 _private prototype_ `void SortFilesView();`
- L67 _private prototype_ `TSharedPtr<SWidget> OnOpenChangesetContextMenu();`
- L68 _private prototype_ `TSharedPtr<SWidget> OnOpenFileContextMenu();`
- L70 _private prototype_ `void OnDiffChangesetClicked(FPlasticSourceControlChangesetPtr InSelectedChangeset);`
- L71 _private prototype_ `void OnDiffChangesetsClicked(TArray<FPlasticSourceControlChangesetRef> InSelectedChangesets);`
- L72 _private prototype_ `void OnDiffBranchClicked(FPlasticSourceControlChangesetPtr InSelectedChangeset);`
- L73 _private prototype_ `void OnSwitchToBranchClicked(FPlasticSourceControlChangesetPtr InSelectedChangeset);`
- L74 _private prototype_ `void OnSwitchToChangesetClicked(FPlasticSourceControlChangesetPtr InSelectedChangeset);`
- L75 _private prototype_ `void OnLocateFileClicked(FPlasticSourceControlStateRef InSelectedFile);`
- L76 _private prototype_ `void OnDiffRevisionClicked(FPlasticSourceControlStateRef InSelectedFile);`
- L77 _private prototype_ `void OnDiffAgainstWorkspaceClicked(FPlasticSourceControlStateRef InSelectedFile);`
- L78 _private prototype_ `void OnSaveRevisionClicked(FPlasticSourceControlStateRef InSelectedFile);`
- L79 _private prototype_ `void OnRevertToRevisionClicked(TArray<FPlasticSourceControlStateRef> InSelectedFiles);`
- L80 _private prototype_ `void OnShowHistoryClicked(TArray<FPlasticSourceControlStateRef> InSelectedFiles);`
- L82 _private prototype_ `void SelectActors(const TArray<FAssetData> ActorsToSelect);`
- L83 _private prototype_ `void FocusActors(const TArray<FAssetData> ActorToFocus);`
- L84 _private prototype_ `void BrowseToAssets(const TArray<FAssetData> Assets);`
- L86 _private prototype_ `void StartRefreshStatus();`
- L87 _private prototype_ `void TickRefreshStatus(double InDeltaTime);`
- L88 _private prototype_ `void EndRefreshStatus();`
- L90 _private prototype_ `void RequestChangesetsRefresh();`
- L91 _private prototype_ `void RequestGetChangesetFiles(const FPlasticSourceControlChangesetPtr& InSelectedChangeset);`
- L94 _private prototype_ `void OnGetChangesetsOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Source control callbacks
- L95 _private prototype_ `void OnGetChangesetFilesOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);`
- L96 _private prototype_ `void OnSwitchToBranchOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);`
- L97 _private prototype_ `void OnSwitchToChangesetOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);`
- L98 _private prototype_ `void OnRevertToRevisionOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);`
- L99 _private prototype_ `void OnSourceControlProviderChanged(ISourceControlProvider& OldProvider, ISourceControlProvider& NewProvider);`
- L102 _private prototype_ `void HandleSourceControlStateChanged();` — Delegate handler for when source control state changes
- L104 _private prototype_ `void OnSelectionChanged(FPlasticSourceControlChangesetPtr InSelectedChangeset, ESelectInfo::Type SelectInfo);`
- L107 _private prototype_ `void OnItemDoubleClicked(FPlasticSourceControlChangesetRef InChangeset);` — Double click to diff the selected changeset
- L110 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Interpret F5 and Enter keys
- L113 _private member_ `TSharedPtr<SSearchBox> ChangesetsSearchBox;`
- L114 _private member_ `TSharedPtr<SSearchBox> FilesSearchBox;`
- L116 _private member_ `FName ChangesetsPrimarySortedColumn;`
- L117 _private member_ `FName ChangesetsSecondarySortedColumn;`
- L118 _private member_ `EColumnSortMode::Type ChangesetsPrimarySortMode = EColumnSortMode::Ascending;`
- L119 _private member_ `EColumnSortMode::Type ChangesetsSecondarySortMode = EColumnSortMode::None;`
- L121 _private member_ `FName FilesPrimarySortedColumn;`
- L122 _private member_ `FName FilesSecondarySortedColumn;`
- L123 _private member_ `EColumnSortMode::Type FilesPrimarySortMode = EColumnSortMode::Ascending;`
- L124 _private member_ `EColumnSortMode::Type FilesSecondarySortMode = EColumnSortMode::None;`
- L126 _private member_ `TArray<FName> ChangesetsHiddenColumnsList;`
- L128 _private member_ `bool bShouldRefresh = false;`
- L129 _private member_ `bool bSourceControlAvailable = false;`
- L131 _private member_ `FText RefreshStatus;`
- L132 _private member_ `bool bIsRefreshing = false;`
- L133 _private member_ `double RefreshStatusStartSecs;`
- L134 _private member_ `double LastRefreshTime = 0.0;`
- L136 _private member_ `int32 CurrentChangesetId;`
- L139 _private member_ `FNotification Notification;` — Ongoing notification for a long-running asynchronous source control operation, if any
- L141 _private member_ `TSharedPtr<SListView<FPlasticSourceControlChangesetRef>> ChangesetsListView;`
- L142 _private member_ `TSharedPtr<TTextFilter<const FPlasticSourceControlChangeset&>> ChangesetsSearchTextFilter;`
- L144 _private member_ `TMap<int32, FText> FromDateInDaysValues;`
- L145 _private member_ `int32 FromDateInDays = 30;`
- L147 _private member_ `TArray<FPlasticSourceControlChangesetRef> SourceControlChangesets;` — Full list from source (filtered by date)
- L148 _private member_ `TArray<FPlasticSourceControlChangesetRef> ChangesetRows;` — Filtered list to display based on the search text filter
- L150 _private member_ `TSharedPtr<SListView<FPlasticSourceControlStateRef>> FilesListView;`
- L151 _private member_ `TSharedPtr<TTextFilter<const FPlasticSourceControlState&>> FilesSearchTextFilter;`
- L153 _private member_ `FPlasticSourceControlChangesetPtr SourceSelectedChangeset;` — Current selected changeset from source control if any, with full list of files
- L154 _private member_ `TArray<FPlasticSourceControlStateRef> FileRows;` — Filtered list to display based on the search text filter
- L157 _private member_ `FDelegateHandle SourceControlStateChangedDelegateHandle;` — Delegate handle for the HandleSourceControlStateChanged function callback

#### Free symbols / members of external scopes

- L19 _typedef_ `typedef TSharedRef<class FPlasticSourceControlChangeset, ESPMode::ThreadSafe> FPlasticSourceControlChangesetRef;`
- L20 _typedef_ `typedef TSharedPtr<class FPlasticSourceControlChangeset, ESPMode::ThreadSafe> FPlasticSourceControlChangesetPtr;`
- L21 _typedef_ `typedef TSharedRef<class FPlasticSourceControlState, ESPMode::ThreadSafe> FPlasticSourceControlStateRef;`
- L22 _typedef_ `typedef TSharedPtr<class FPlasticSourceControlState, ESPMode::ThreadSafe> FPlasticSourceControlStatePtr;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/SPlasticSourceControlCreateBranch.h` (Private)


#### class `SPlasticSourceControlCreateBranch`  
`class SPlasticSourceControlCreateBranch : public SCompoundWidget`  
_L16-55_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SPlasticSourceControlCreateBranch) : _BranchesWidget() , _ParentWindow() , _ParentBranchName()`
- L25 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SPlasticSourceControlBranchesWidget>, BranchesWidget) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(FString, ParentBranchName) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _private prototype_ `void OnCheckedSwitchWorkspace(ECheckBoxState InState);`
- L36 _private prototype_ `bool CanCreateBranch() const;`
- L37 _private prototype_ `FText CreateButtonTooltip() const;`
- L39 _private prototype_ `FReply CreateClicked();`
- L40 _private prototype_ `FReply CancelClicked();`
- L43 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Interpret Escape as Cancel
- L46 _private member_ `FString ParentBranchName;`
- L47 _private member_ `FString NewBranchName;`
- L48 _private member_ `FString NewBranchComment;`
- L49 _private member_ `bool bSwitchWorkspace = true;`
- L51 _private member_ `TSharedPtr<SEditableTextBox> BranchNameTextBox;`
- L53 _private member_ `TWeakPtr<SPlasticSourceControlBranchesWidget> BranchesWidget;`
- L54 _private member_ `TWeakPtr<SWindow> ParentWindow;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/SPlasticSourceControlDeleteBranches.h` (Private)


#### class `SPlasticSourceControlDeleteBranches`  
`class SPlasticSourceControlDeleteBranches : public SCompoundWidget`  
_L15-46_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SPlasticSourceControlDeleteBranches) : _BranchesWidget() , _ParentWindow() , _BranchNames()`
- L24 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SPlasticSourceControlBranchesWidget>, BranchesWidget) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(TArray<FString>, BranchNames) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L33 _private prototype_ `FReply DeleteClicked();`
- L34 _private prototype_ `FReply CancelClicked();`
- L37 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Interpret Escape as Cancel
- L40 _private member_ `TArray<FString> BranchNames;`
- L42 _private member_ `TWeakPtr<SPlasticSourceControlBranchesWidget> BranchesWidget;`
- L43 _private member_ `TWeakPtr<SWindow> ParentWindow;`
- L45 _private member_ `TSharedPtr<SButton> DeleteButtonPtr;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/SPlasticSourceControlLockRow.h` (Private)


#### class `SPlasticSourceControlLockRow`  
`class SPlasticSourceControlLockRow : public SMultiColumnTableRow<FPlasticSourceControlLockRef>`  
_L85-115_
- inherits: `SMultiColumnTableRow<FPlasticSourceControlLockRef>`
- L88 _public function_ `SLATE_BEGIN_ARGS(SPlasticSourceControlLockRow) : _LockToVisualize(nullptr) , _HighlightText()`
- L104 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwner);` — Construct a row child widgets of the ListView. @param InArgs Parameters including the lock to visualize in this row. @param InOwner The owning ListView.
- L107 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnId) override;` — SMultiColumnTableRow overrides
- L111 _private member_ `FPlasticSourceControlLock* LockToVisualize;` — The lock that we are visualizing in this row.
- L114 _private member_ `TAttribute<FText> HighlightText;` — The search text to highlight if any

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef TSharedRef<class FPlasticSourceControlLock, ESPMode::ThreadSafe> FPlasticSourceControlLockRef;`
- L13 _typedef_ `typedef TSharedPtr<class FPlasticSourceControlLock, ESPMode::ThreadSafe> FPlasticSourceControlLockPtr;`
- L18 _namespace_ `namespace PlasticSourceControlLocksListViewColumn`
- L21 _namespace_ `namespace ItemId` (scope `PlasticSourceControlLocksListViewColumn`)
- L23 _prototype_ `FName Id();` (scope `PlasticSourceControlLocksListViewColumn::ItemId`)
- L24 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlLocksListViewColumn::ItemId`)
- L25 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlLocksListViewColumn::ItemId`)
- L29 _namespace_ `namespace Path` (scope `PlasticSourceControlLocksListViewColumn`)
- L31 _prototype_ `FName Id();` (scope `PlasticSourceControlLocksListViewColumn::Path`)
- L32 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlLocksListViewColumn::Path`)
- L33 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlLocksListViewColumn::Path`)
- L37 _namespace_ `namespace Status` (scope `PlasticSourceControlLocksListViewColumn`)
- L39 _prototype_ `FName Id();` (scope `PlasticSourceControlLocksListViewColumn::Status`)
- L40 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlLocksListViewColumn::Status`)
- L41 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlLocksListViewColumn::Status`)
- L45 _namespace_ `namespace Date` (scope `PlasticSourceControlLocksListViewColumn`)
- L47 _prototype_ `FName Id();` (scope `PlasticSourceControlLocksListViewColumn::Date`)
- L48 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlLocksListViewColumn::Date`)
- L49 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlLocksListViewColumn::Date`)
- L53 _namespace_ `namespace Owner` (scope `PlasticSourceControlLocksListViewColumn`)
- L55 _prototype_ `FName Id();` (scope `PlasticSourceControlLocksListViewColumn::Owner`)
- L56 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlLocksListViewColumn::Owner`)
- L57 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlLocksListViewColumn::Owner`)
- L61 _namespace_ `namespace DestinationBranch` (scope `PlasticSourceControlLocksListViewColumn`)
- L63 _prototype_ `FName Id();` (scope `PlasticSourceControlLocksListViewColumn::DestinationBranch`)
- L64 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlLocksListViewColumn::DestinationBranch`)
- L65 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlLocksListViewColumn::DestinationBranch`)
- L69 _namespace_ `namespace Branch` (scope `PlasticSourceControlLocksListViewColumn`)
- L71 _prototype_ `FName Id();` (scope `PlasticSourceControlLocksListViewColumn::Branch`)
- L72 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlLocksListViewColumn::Branch`)
- L73 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlLocksListViewColumn::Branch`)
- L77 _namespace_ `namespace Workspace` (scope `PlasticSourceControlLocksListViewColumn`)
- L79 _prototype_ `FName Id();` (scope `PlasticSourceControlLocksListViewColumn::Workspace`)
- L80 _prototype_ `FText GetDisplayText();` (scope `PlasticSourceControlLocksListViewColumn::Workspace`)
- L81 _prototype_ `FText GetToolTipText();` (scope `PlasticSourceControlLocksListViewColumn::Workspace`)

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/SPlasticSourceControlLocksWidget.h` (Private)


#### class `SPlasticSourceControlLocksWidget`  
`class SPlasticSourceControlLocksWidget : public SCompoundWidget`  
_L22-110_
- inherits: `SCompoundWidget`
- desc: Widget displaying the list of locks in the tab window, see FPlasticSourceControlLocksWindow
- L24 _private function_ `SLATE_BEGIN_ARGS(SPlasticSourceControlLocksWidget)`
- L25 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L32 _private prototype_ `TSharedRef<SWidget> CreateToolBar();`
- L33 _private prototype_ `TSharedRef<SWidget> CreateContentPanel();`
- L35 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FPlasticSourceControlLockRef InLock, const TSharedRef<STableViewBase>& OwnerTable);`
- L36 _private prototype_ `void OnHiddenColumnsListChanged();`
- L38 _private prototype_ `void OnSearchTextChanged(const FText& InFilterText);`
- L39 _private prototype_ `void PopulateItemSearchStrings(const FPlasticSourceControlLock& InItem, TArray<FString>& OutStrings);`
- L41 _private prototype_ `void OnRefreshUI();`
- L43 _private prototype_ `EColumnSortPriority::Type GetColumnSortPriority(const FName InColumnId) const;`
- L44 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName InColumnId) const;`
- L45 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type InSortPriority, const FName& InColumnId, const EColumnSortMode::Type InSortMode);`
- L47 _private prototype_ `void SortLockView();`
- L49 _private prototype_ `TSharedPtr<SWidget> OnOpenContextMenu();`
- L51 _private prototype_ `FReply OnConfigureLockRulesClicked(const FString InOrganizationName);`
- L53 _private prototype_ `void OnReleaseLocksClicked(TArray<FPlasticSourceControlLockRef> InSelectedLocks);`
- L54 _private prototype_ `void OnRemoveLocksClicked(TArray<FPlasticSourceControlLockRef> InSelectedLocks);`
- L55 _private prototype_ `void ExecuteUnlock(TArray<FPlasticSourceControlLockRef>&& InSelectedLocks, const bool bInRemove);`
- L57 _private prototype_ `void StartRefreshStatus();`
- L58 _private prototype_ `void TickRefreshStatus(double InDeltaTime);`
- L59 _private prototype_ `void EndRefreshStatus();`
- L61 _private prototype_ `void RequestLocksRefresh(const bool bInInvalidateLocksCache);`
- L64 _private prototype_ `void OnGetLocksOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Source control callbacks
- L65 _private prototype_ `void OnUnlockOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);`
- L66 _private prototype_ `void OnSourceControlProviderChanged(ISourceControlProvider& OldProvider, ISourceControlProvider& NewProvider);`
- L69 _private prototype_ `void HandleSourceControlStateChanged();` — Delegate handler for when source control state changes
- L71 _private function_ `SListView<FPlasticSourceControlLockRef>* GetListView() const`
- L77 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Interpret F5, Enter and Delete keys
- L80 _private member_ `TSharedPtr<SSearchBox> LockSearchBox;`
- L82 _private member_ `FName PrimarySortedColumn;`
- L83 _private member_ `FName SecondarySortedColumn;`
- L84 _private member_ `EColumnSortMode::Type PrimarySortMode = EColumnSortMode::Ascending;`
- L85 _private member_ `EColumnSortMode::Type SecondarySortMode = EColumnSortMode::None;`
- L87 _private member_ `TArray<FName> HiddenColumnsList;`
- L89 _private member_ `bool bShouldRefresh = false;`
- L90 _private member_ `bool bShouldInvalidateLocksCache = false;`
- L91 _private member_ `bool bSourceControlAvailable = false;`
- L93 _private member_ `FText RefreshStatus;`
- L94 _private member_ `bool bIsRefreshing = false;`
- L95 _private member_ `double RefreshStatusStartSecs;`
- L97 _private member_ `FString WorkspaceSelector;`
- L100 _private member_ `FNotification Notification;` — Ongoing notification for a long-running asynchronous source control operation, if any
- L102 _private member_ `TSharedPtr<SListView<FPlasticSourceControlLockRef>> LocksListView;`
- L103 _private member_ `TSharedPtr<TTextFilter<const FPlasticSourceControlLock&>> SearchTextFilter;`
- L105 _private member_ `TArray<FPlasticSourceControlLockRef> SourceControlLocks;` — Full list from source (filtered by date)
- L106 _private member_ `TArray<FPlasticSourceControlLockRef> LockRows;` — Filtered list to display based on the search text filter
- L109 _private member_ `FDelegateHandle SourceControlStateChangedDelegateHandle;` — Delegate handle for the HandleSourceControlStateChanged function callback

#### Free symbols / members of external scopes

- L17 _typedef_ `typedef TSharedRef<class FPlasticSourceControlLock, ESPMode::ThreadSafe> FPlasticSourceControlLockRef;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/SPlasticSourceControlRenameBranch.h` (Private)


#### class `SPlasticSourceControlRenameBranch`  
`class SPlasticSourceControlRenameBranch : public SCompoundWidget`  
_L15-50_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SPlasticSourceControlRenameBranch) : _BranchesWidget() , _ParentWindow() , _OldBranchName()`
- L24 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SPlasticSourceControlBranchesWidget>, BranchesWidget) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(FString, OldBranchName) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L33 _private prototype_ `bool CanRenameBranch() const;`
- L34 _private prototype_ `FText RenameButtonTooltip() const;`
- L36 _private prototype_ `FReply RenamedClicked();`
- L37 _private prototype_ `FReply CancelClicked();`
- L40 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Interpret Escape as Cancel
- L43 _private member_ `FString OldBranchName;`
- L44 _private member_ `FString NewBranchName;`
- L46 _private member_ `TSharedPtr<SEditableTextBox> BranchNameTextBox;`
- L48 _private member_ `TWeakPtr<SPlasticSourceControlBranchesWidget> BranchesWidget;`
- L49 _private member_ `TWeakPtr<SWindow> ParentWindow;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/SPlasticSourceControlSettings.h` (Private)


#### class `SPlasticSourceControlSettings`  
`class SPlasticSourceControlSettings : public SCompoundWidget`  
_L14-80_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SPlasticSourceControlSettings)`
- L22 _public prototype_ `void Construct(const FArguments& InArgs);`
- L25 _private prototype_ `EVisibility PlasticNotAvailable() const;`
- L28 _private prototype_ `FText GetBinaryPathText() const;` — Delegate to get cm binary path from settings
- L31 _private prototype_ `void OnBinaryPathTextCommited(const FText& InText, ETextCommit::Type InCommitType) const;` — Delegate to commit cm binary path to settings
- L34 _private prototype_ `FText GetVersions() const;` — Delegate to get workspace root and user name from provider
- L35 _private prototype_ `FText GetPathToWorkspaceRoot() const;`
- L36 _private prototype_ `FText GetUserName() const;`
- L39 _private prototype_ `EVisibility CanCreatePlasticWorkspace() const;` — Delegate to create a new Plastic workspace and repository
- L40 _private prototype_ `bool IsReadyToCreatePlasticWorkspace() const;`
- L41 _private prototype_ `void OnWorkspaceNameCommited(const FText& InText, ETextCommit::Type InCommitType);`
- L42 _private prototype_ `FText GetWorkspaceName() const;`
- L43 _private prototype_ `void OnRepositoryNameCommited(const FText& InText, ETextCommit::Type InCommitType);`
- L44 _private prototype_ `FText GetRepositoryName() const;`
- L45 _private prototype_ `void OnServerUrlCommited(const FText& InText, ETextCommit::Type InCommitType);`
- L46 _private prototype_ `FText GetServerUrl() const;`
- L47 _private prototype_ `bool CreatePartialWorkspace() const;`
- L48 _private prototype_ `void OnCheckedCreatePartialWorkspace(ECheckBoxState NewCheckedState);`
- L49 _private prototype_ `bool CanAutoCreateIgnoreFile() const;`
- L50 _private prototype_ `void OnCheckedCreateIgnoreFile(ECheckBoxState NewCheckedState);`
- L51 _private member_ `bool bAutoCreateIgnoreFile;`
- L53 _private prototype_ `void OnCheckedUpdateStatusAtStartup(ECheckBoxState NewCheckedState);`
- L54 _private prototype_ `ECheckBoxState IsUpdateStatusAtStartupChecked() const;`
- L56 _private prototype_ `void OnCheckedUpdateStatusOtherBranches(ECheckBoxState NewCheckedState);`
- L57 _private prototype_ `ECheckBoxState IsUpdateStatusOtherBranchesChecked() const;`
- L59 _private prototype_ `void OnCheckedViewLocalChanges(ECheckBoxState NewCheckedState);`
- L60 _private prototype_ `ECheckBoxState IsViewLocalChangesChecked() const;`
- L62 _private prototype_ `void OnCheckedEnableVerboseLogs(ECheckBoxState NewCheckedState);`
- L63 _private prototype_ `ECheckBoxState IsEnableVerboseLogsChecked() const;`
- L65 _private prototype_ `void OnCheckedInitialCommit(ECheckBoxState NewCheckedState);`
- L66 _private prototype_ `void OnInitialCommitMessageCommited(const FText& InText, ETextCommit::Type InCommitType);`
- L67 _private prototype_ `FText GetInitialCommitMessage() const;`
- L69 _private prototype_ `FReply OnClickedCreatePlasticWorkspace();`
- L72 _private member_ `FPlasticSourceControlWorkspaceCreation::FParameters WorkspaceParams;` — Parameters for the workspace creation
- L75 _private prototype_ `EVisibility CanAddIgnoreFile() const;` — Delegate to add a Plastic ignore.conf file to an existing Plastic workspace
- L76 _private prototype_ `FReply OnClickedAddIgnoreFile() const;`
- L78 _private prototype_ `const FString GetIgnoreFileName() const;`
- L79 _private prototype_ `bool CreateIgnoreFile() const;`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/SPlasticSourceControlStatusBar.h` (Private)


#### class `SPlasticSourceControlStatusBar`  
`class SPlasticSourceControlStatusBar : public SCompoundWidget`  
_L14-26_
- inherits: `SCompoundWidget`
- desc: Status bar displaying the name of the current branch
- L17 _public function_ `SLATE_BEGIN_ARGS(SPlasticSourceControlStatusBar)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L23 _private prototype_ `FText GetStatusBarText() const;`
- L25 _private prototype_ `FReply OnClicked();`

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/ScopedTempFile.h` (Private)


#### class `FScopedTempFile`  
`class FScopedTempFile`  
_L10-30_
- desc: Helper for temporary files to pass as arguments to some commands (typically for checkin multi-line text message)
- L14 _public prototype_ `FScopedTempFile();` — Default constructor - only hold a temp filename
- L15 _public prototype_ `FScopedTempFile(const FString& InPrefix, const FString& InExtension);`
- L18 _public prototype_ `explicit FScopedTempFile(const FString& InText);` — Constructor - open & write string to temp file
- L19 _public prototype_ `explicit FScopedTempFile(const FText& InText);`
- L22 _public prototype_ `~FScopedTempFile();` — Destructor - delete temp file
- L25 _public prototype_ `const FString& GetFilename() const;` — Get the filename of this temp file - empty if it failed to be created
- L29 _private member_ `FString Filename;` — The filename we are writing to

### `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/SoftwareVersion.h` (Private)


#### struct `FSoftwareVersion`  
`struct FSoftwareVersion`  
_L10-22_
- desc: Software version string in the form "X.Y.Z.C", ie Major.Minor.Patch.Changeset (as returned by GetPlasticScmVersion)
- L12 _public function_ `FSoftwareVersion() : String(TEXT("<unk`
- L14 _public prototype_ `explicit FSoftwareVersion(FString&& InVersionString);`
- L16 _public member_ `FString String;`
- L18 _public member_ `int32 Major = 0;`
- L19 _public member_ `int32 Minor = 0;`
- L20 _public member_ `int32 Patch = 0;`
- L21 _public member_ `int32 Changeset = 0;`

#### Free symbols / members of external scopes

- L24 _prototype_ `bool operator==(const FSoftwareVersion& Rhs, const FSoftwareVersion& Lhs);`
- L25 _prototype_ `bool operator<(const FSoftwareVersion& Rhs, const FSoftwareVersion& Lhs);`
- L26 _prototype_ `bool operator>=(const FSoftwareVersion& Rhs, const FSoftwareVersion& Lhs);`
