# Plugins / GitSourceControl

- module root: `Plugins/Developer/GitSourceControl/Source/GitSourceControl`
- headers: 10; symbols: 313
- symbol kinds: class=18, delegate=1, enum=1, enumerator=11, function=33, member=70, namespace=3, prototype=173, struct=1, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopWidgets, EditorFramework, InputCore, Slate, SlateCore, SourceControl, UnrealEd

### `Plugins/Developer/GitSourceControl/Source/GitSourceControl/Private/GitSourceControlCommand.h` (Private)


#### class `FGitSourceControlCommand`  
`class FGitSourceControlCommand : public IQueuedWork`  
_L11-76_
- inherits: `IQueuedWork`
- desc: Used to execute Git commands multi-threaded.
- L15 _public prototype_ `FGitSourceControlCommand(const TSharedRef<class ISourceControlOperation, ESPMode::ThreadSafe>& InOperation, const TSharedRef<class IGitSourceControlWorker, ESPMode::ThreadSafe>& InWorker, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() );`
- L21 _public prototype_ `bool DoWork();` — This is where the real thread work is done. All work that is done for this queued object should be done from within the call to this function.
- L29 _public prototype_ `virtual void Abandon() override;` — Tells the queued work that it is being abandoned so that it can do per object clean up as needed. This will only be called if it is being abandoned before completion. NOTE: This requires the object to delete itself using whatever heap it was allocated in.
- L35 _public prototype_ `virtual void DoThreadedWork() override;` — This method is also used to tell the object to cleanup but not before the object has finished it's work.
- L38 _public prototype_ `ECommandResult::Type ReturnResults();` — Save any results and call any registered callbacks.
- L42 _public member_ `FString PathToGitBinary;` — Path to the Git binary
- L45 _public member_ `FString PathToRepositoryRoot;` — Path to the root of the Git repository: can be the ProjectDir itself, or any parent directory (found by the "Connect" operation)
- L48 _public member_ `TSharedRef<class ISourceControlOperation, ESPMode::ThreadSafe> Operation;` — Operation we want to perform - contains outward-facing parameters & results
- L51 _public member_ `TSharedRef<class IGitSourceControlWorker, ESPMode::ThreadSafe> Worker;` — The object that will actually do the work
- L54 _public member_ `FSourceControlOperationComplete OperationCompleteDelegate;` — Delegate to notify when this operation completes
- L57 _public member_ `volatile int32 bExecuteProcessed;` — If true, this command has been processed by the source control thread
- L60 _public member_ `bool bCommandSuccessful;` — If true, the source control command succeeded
- L63 _public member_ `bool bAutoDelete;` — If true, this command will be automatically cleaned up in Tick()
- L66 _public member_ `EConcurrency::Type Concurrency;` — Whether we are running multi-treaded or not
- L69 _public member_ `TArray< FString > Files;` — Files to perform this operation on
- L72 _public member_ `TArray< FString > InfoMessages;` — Info and/or warning message message storage
- L75 _public member_ `TArray< FString > ErrorMessages;` — Potential error message storage

### `Plugins/Developer/GitSourceControl/Source/GitSourceControl/Private/GitSourceControlModule.h` (Private)


#### class `FGitSourceControlModule`  
`class FGitSourceControlModule : public IModuleInterface`  
_L52-80_
- inherits: `IModuleInterface`
- desc: UEGitPlugin is a simple Git Source Control Plugin for Unreal Engine Written and contributed by Sebastien Rombauts (sebastien.rombauts@gmail.com) ### Supported features - initialize a new Git local repository ('git init') to manage your UE Game Project. - create an appropriate .gitignore file as part as initialization - can also make the initial commit - display status icons to show modified/added/deleted/untracked files - show history of a file - visual diff of a blueprint against depot or between previous versions of a file - revert modifications of a file - add, delete, rename a file - checkin/commit a file (cannot handle atomically more than 20 files) - migrate an asset between to projects if both are using Git - solve a merge conflict on a blueprint - show current branch name in status text - Sync to Pull the current branch if there is no local modified files - git LFS (Github & Gitlab), git-annex and/or git-media are working under Windows - Windows, Mac and Linux ### What *cannot* be done presently - tags: implement ISourceControlLabel to manage git tags - Branch is not in the current Editor workflow (but on Epic Roadmap) - Pull/Fetch/Push are not in the current Editor workflow - Amend a commit is not in the current Editor workflow - configure user name & email ('git config user.name' & git config user.email') ### Known issues: - the Editor does not show deleted files (only when deleted externaly?) - the Editor does not show missing files - the Editor does not show .upro
- L56 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L57 _public prototype_ `virtual void ShutdownModule() override;`
- L60 _public function_ `FGitSourceControlSettings& AccessSettings()` — Access the Git source control settings
- L66 _public prototype_ `void SaveSettings();` — Save the Git source control settings
- L69 _public function_ `FGitSourceControlProvider& GetProvider()` — Access the Git source control provider
- L76 _private member_ `FGitSourceControlProvider GitSourceControlProvider;` — The Git source control provider
- L79 _private member_ `FGitSourceControlSettings GitSourceControlSettings;` — The settings for Git source control

### `Plugins/Developer/GitSourceControl/Source/GitSourceControl/Private/GitSourceControlOperations.h` (Private)


#### class `FGitConnectWorker`  
`class FGitConnectWorker : public IGitSourceControlWorker`  
_L10-22_
- inherits: `IGitSourceControlWorker`
- desc: Called when first activated on a project, and then at project load time. Look for the root directory of the git repository (where the ".git/" subdirectory is located).
- L13 _public function_ `virtual ~FGitConnectWorker()`
- L15 _public prototype_ `virtual FName GetName() const override;` — IGitSourceControlWorker interface
- L16 _public prototype_ `virtual bool Execute(class FGitSourceControlCommand& InCommand) override;`
- L17 _public prototype_ `virtual bool UpdateStates() const override;`
- L21 _public member_ `TArray<FGitSourceControlState> States;` — Temporary states for results

#### class `FGitCheckInWorker`  
`class FGitCheckInWorker : public IGitSourceControlWorker`  
_L25-37_
- inherits: `IGitSourceControlWorker`
- desc: Commit (check-in) a set of file to the local depot.
- L28 _public function_ `virtual ~FGitCheckInWorker()`
- L30 _public prototype_ `virtual FName GetName() const override;` — IGitSourceControlWorker interface
- L31 _public prototype_ `virtual bool Execute(class FGitSourceControlCommand& InCommand) override;`
- L32 _public prototype_ `virtual bool UpdateStates() const override;`
- L36 _public member_ `TArray<FGitSourceControlState> States;` — Temporary states for results

#### class `FGitMarkForAddWorker`  
`class FGitMarkForAddWorker : public IGitSourceControlWorker`  
_L40-52_
- inherits: `IGitSourceControlWorker`
- desc: Add an untraked file to source control (so only a subset of the git add command).
- L43 _public function_ `virtual ~FGitMarkForAddWorker()`
- L45 _public prototype_ `virtual FName GetName() const override;` — IGitSourceControlWorker interface
- L46 _public prototype_ `virtual bool Execute(class FGitSourceControlCommand& InCommand) override;`
- L47 _public prototype_ `virtual bool UpdateStates() const override;`
- L51 _public member_ `TArray<FGitSourceControlState> States;` — Temporary states for results

#### class `FGitDeleteWorker`  
`class FGitDeleteWorker : public IGitSourceControlWorker`  
_L55-67_
- inherits: `IGitSourceControlWorker`
- desc: Delete a file and remove it from source control.
- L58 _public function_ `virtual ~FGitDeleteWorker()`
- L60 _public prototype_ `virtual FName GetName() const override;` — IGitSourceControlWorker interface
- L61 _public prototype_ `virtual bool Execute(class FGitSourceControlCommand& InCommand) override;`
- L62 _public prototype_ `virtual bool UpdateStates() const override;`
- L66 _public member_ `TArray<FGitSourceControlState> States;` — Map of filenames to Git state

#### class `FGitRevertWorker`  
`class FGitRevertWorker : public IGitSourceControlWorker`  
_L70-82_
- inherits: `IGitSourceControlWorker`
- desc: Revert any change to a file to its state on the local depot.
- L73 _public function_ `virtual ~FGitRevertWorker()`
- L75 _public prototype_ `virtual FName GetName() const override;` — IGitSourceControlWorker interface
- L76 _public prototype_ `virtual bool Execute(class FGitSourceControlCommand& InCommand) override;`
- L77 _public prototype_ `virtual bool UpdateStates() const override;`
- L81 _public member_ `TArray<FGitSourceControlState> States;` — Map of filenames to Git state

#### class `FGitSyncWorker`  
`class FGitSyncWorker : public IGitSourceControlWorker`  
_L85-97_
- inherits: `IGitSourceControlWorker`
- desc: Git pull --rebase to update branch from its configure remote
- L88 _public function_ `virtual ~FGitSyncWorker()`
- L90 _public prototype_ `virtual FName GetName() const override;` — IGitSourceControlWorker interface
- L91 _public prototype_ `virtual bool Execute(class FGitSourceControlCommand& InCommand) override;`
- L92 _public prototype_ `virtual bool UpdateStates() const override;`
- L96 _public member_ `TArray<FGitSourceControlState> States;` — Map of filenames to Git state

#### class `FGitUpdateStatusWorker`  
`class FGitUpdateStatusWorker : public IGitSourceControlWorker`  
_L100-115_
- inherits: `IGitSourceControlWorker`
- desc: Get source control status of files on local working copy.
- L103 _public function_ `virtual ~FGitUpdateStatusWorker()`
- L105 _public prototype_ `virtual FName GetName() const override;` — IGitSourceControlWorker interface
- L106 _public prototype_ `virtual bool Execute(class FGitSourceControlCommand& InCommand) override;`
- L107 _public prototype_ `virtual bool UpdateStates() const override;`
- L111 _public member_ `TArray<FGitSourceControlState> States;` — Temporary states for results
- L114 _public member_ `TMap<FString, TGitSourceControlHistory> Histories;` — Map of filenames to history

#### class `FGitCopyWorker`  
`class FGitCopyWorker : public IGitSourceControlWorker`  
_L118-130_
- inherits: `IGitSourceControlWorker`
- desc: Copy or Move operation on a single file
- L121 _public function_ `virtual ~FGitCopyWorker()`
- L123 _public prototype_ `virtual FName GetName() const override;` — IGitSourceControlWorker interface
- L124 _public prototype_ `virtual bool Execute(class FGitSourceControlCommand& InCommand) override;`
- L125 _public prototype_ `virtual bool UpdateStates() const override;`
- L129 _public member_ `TArray<FGitSourceControlState> OutStates;` — Temporary states for results

#### class `FGitResolveWorker`  
`class FGitResolveWorker : public IGitSourceControlWorker`  
_L133-144_
- inherits: `IGitSourceControlWorker`
- desc: git add to mark a conflict as resolved
- L136 _public function_ `virtual ~FGitResolveWorker()`
- L137 _public prototype_ `virtual FName GetName() const override;`
- L138 _public prototype_ `virtual bool Execute(class FGitSourceControlCommand& InCommand) override;`
- L139 _public prototype_ `virtual bool UpdateStates() const override;`
- L143 _private member_ `TArray<FGitSourceControlState> States;` — Temporary states for results

### `Plugins/Developer/GitSourceControl/Source/GitSourceControl/Private/GitSourceControlProvider.h` (Private)


#### struct `FGitVersion`  
`struct FGitVersion`  
_L14-36_
- L16 _public member_ `int Major;`
- L17 _public member_ `int Minor;`
- L19 _public member_ `uint32 bHasCatFileWithFilters : 1;`
- L20 _public member_ `uint32 bHasGitLfs : 1;`
- L21 _public member_ `uint32 bHasGitLfsLocking : 1;`
- L23 _public function_ `FGitVersion() : Major(0) , Minor(0) , bHasCatFileWithFilters(false) , bHasGitLfs(false) , bHasGitLfsLocking(false)`
- L32 _public function_ `inline bool IsGreaterOrEqualThan(int InMajor, int InMinor) const`

#### class `FGitSourceControlProvider`  
`class FGitSourceControlProvider : public ISourceControlProvider`  
_L38-194_
- inherits: `ISourceControlProvider`
- L42 _public function_ `FGitSourceControlProvider() : bGitAvailable(false) , bGitRepositoryFound(false)` — Constructor
- L49 _public prototype_ `virtual void Init(bool bForceConnection = true) override;` — ISourceControlProvider implementation
- L50 _public prototype_ `virtual void Close() override;`
- L51 _public prototype_ `virtual FText GetStatusText() const override;`
- L52 _public prototype_ `virtual TMap<EStatus, FString> GetStatus() const override;`
- L53 _public prototype_ `virtual bool IsEnabled() const override;`
- L54 _public prototype_ `virtual bool IsAvailable() const override;`
- L55 _public prototype_ `virtual const FName& GetName(void) const override;`
- L56 _public function_ `virtual bool QueryStateBranchConfig(const FString& ConfigSrc, const FString& ConfigDest) override`
- L57 _public function_ `virtual void RegisterStateBranches(const TArray<FString>& BranchNames, const FString& ContentRoot) override`
- L58 _public function_ `virtual int32 GetStateBranchIndex(const FString& InBranchName) const override`
- L59 _public function_ `virtual bool GetStateBranchAtIndex(int32 BranchIndex, FString& OutBranchName) const override`
- L60 _public prototype_ `virtual ECommandResult::Type GetState( const TArray<FString>& InFiles, TArray<FSourceControlStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage ) override;`
- L61 _public prototype_ `virtual ECommandResult::Type GetState(const TArray<FSourceControlChangelistRef>& InChangelists, TArray<FSourceControlChangelistStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage) override;`
- L62 _public prototype_ `virtual TArray<FSourceControlStateRef> GetCachedStateByPredicate(TFunctionRef<bool(const FSourceControlStateRef&)> Predicate) const override;`
- L63 _public prototype_ `virtual FDelegateHandle RegisterSourceControlStateChanged_Handle(const FSourceControlStateChanged::FDelegate& SourceControlStateChanged) override;`
- L64 _public prototype_ `virtual void UnregisterSourceControlStateChanged_Handle(FDelegateHandle Handle) override;`
- L65 _public prototype_ `virtual ECommandResult::Type Execute(const FSourceControlOperationRef& InOperation, FSourceControlChangelistPtr InChangelist, const TArray<FString>& InFiles, EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete()) override;`
- L66 _public prototype_ `virtual bool CanExecuteOperation( const FSourceControlOperationRef& InOperation ) const override;`
- L67 _public prototype_ `virtual bool CanCancelOperation( const FSourceControlOperationRef& InOperation ) const override;`
- L68 _public prototype_ `virtual void CancelOperation( const FSourceControlOperationRef& InOperation ) override;`
- L69 _public prototype_ `virtual bool UsesLocalReadOnlyState() const override;`
- L70 _public prototype_ `virtual bool UsesChangelists() const override;`
- L71 _public prototype_ `virtual bool UsesUncontrolledChangelists() const override;`
- L72 _public prototype_ `virtual bool UsesCheckout() const override;`
- L73 _public prototype_ `virtual bool UsesFileRevisions() const override;`
- L74 _public prototype_ `virtual bool UsesSnapshots() const override;`
- L75 _public prototype_ `virtual bool UsesSoftRevertOnDelete() const override;`
- L76 _public prototype_ `virtual bool AllowsDiffAgainstDepot() const override;`
- L77 _public prototype_ `virtual TOptional<bool> HasChangesToSync() const override;`
- L78 _public prototype_ `virtual TOptional<bool> HasChangesToCheckIn() const override;`
- L79 _public prototype_ `virtual void Tick() override;`
- L80 _public prototype_ `virtual TArray< TSharedRef<class ISourceControlLabel> > GetLabels( const FString& InMatchingSpec ) const override;`
- L81 _public prototype_ `virtual TArray<FSourceControlChangelistRef> GetChangelists( EStateCacheUsage::Type InStateCacheUsage ) override;`
- L83 _public prototype_ `virtual TSharedRef<class SWidget> MakeSettingsWidget() const override;`
- L91 _public prototype_ `void CheckGitAvailability();` — Check configuration, else standard paths, and run a Git "version" command to check the availability of the binary.
- L96 _public prototype_ `void CheckRepositoryStatus(const FString& InPathToGitBinary);` — Find the .git/ repository and check it's status.
- L99 _public function_ `inline bool IsGitAvailable() const` — Is git binary found and working.
- L105 _public function_ `inline const FGitVersion& GetGitVersion()` — Git version for feature checking
- L111 _public function_ `inline const FString& GetPathToRepositoryRoot() const` — Get the path to the root of the Git repository: can be the ProjectDir itself, or any parent directory
- L117 _public function_ `inline const FString& GetUserName() const` — Git config user.name
- L123 _public function_ `inline const FString& GetUserEmail() const` — Git config user.email
- L129 _public function_ `inline const FString& GetRemoteUrl() const` — Git remote origin url
- L135 _public prototype_ `TSharedRef<FGitSourceControlState, ESPMode::ThreadSafe> GetStateInternal(const FString& Filename);` — Helper function used to update state cache
- L141 _public prototype_ `void RegisterWorker( const FName& InName, const FGetGitSourceControlWorker& InDelegate );` — Register a worker with the provider. This is used internally so the provider can maintain a map of all available operations.
- L144 _public prototype_ `bool RemoveFileFromCache(const FString& Filename);` — Remove a named file from the state cache
- L149 _private member_ `bool bGitAvailable;` — Is git binary found and working.
- L152 _private member_ `bool bGitRepositoryFound;` — Is git repository found.
- L155 _private prototype_ `TSharedPtr<class IGitSourceControlWorker, ESPMode::ThreadSafe> CreateWorker(const FName& InOperationName) const;` — Helper function for Execute()
- L158 _private prototype_ `ECommandResult::Type ExecuteSynchronousCommand(class FGitSourceControlCommand& InCommand, const FText& Task);` — Helper function for running command synchronously.
- L160 _private prototype_ `ECommandResult::Type IssueCommand(class FGitSourceControlCommand& InCommand);` — Issue a command asynchronously if possible.
- L163 _private prototype_ `void OutputCommandMessages(const class FGitSourceControlCommand& InCommand) const;` — Output any messages this command holds
- L166 _private member_ `FString PathToRepositoryRoot;` — Path to the root of the Git repository: can be the ProjectDir itself, or any parent directory (found by the "Connect" operation)
- L169 _private member_ `FString UserName;` — Git config user.name (from local repository, else globally)
- L172 _private member_ `FString UserEmail;` — Git config user.email (from local repository, else globally)
- L175 _private member_ `FString BranchName;` — Name of the current branch
- L178 _private member_ `FString RemoteUrl;` — URL of the "origin" defaut remote server
- L181 _private member_ `TMap<FString, TSharedRef<class FGitSourceControlState, ESPMode::ThreadSafe> > StateCache;` — State cache
- L184 _private member_ `TMap<FName, FGetGitSourceControlWorker> WorkersMap;` — The currently registered source control operations
- L187 _private member_ `TArray < FGitSourceControlCommand* > CommandQueue;` — Queue for commands given by the main thread
- L190 _private member_ `FSourceControlStateChanged OnSourceControlStateChanged;` — For notifying when the source control states in the cache have changed
- L193 _private member_ `FGitVersion GitVersion;` — Git version for feature checking

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_RetVal(FGitSourceControlWorkerRef, FGetGitSourceControlWorker) struct FGitVersion { int Major; int Minor; uint32 bHasCatFileWithFilters : 1; uint32 bHasGitLfs : 1; uint32 bHasGitLfsLocking : 1; FGitVersion() : Major(0) , Minor(0) , bHasCatFileWithFilters(false) , bHasGitLfs(false) , bHasGitLfsLocking(false) { } inline bool IsGreaterOrEqualThan(int InMajor, int InMinor) const { return (Major > InMajor) || (Major == InMajor && (Minor >= InMinor)); } };`

### `Plugins/Developer/GitSourceControl/Source/GitSourceControl/Private/GitSourceControlRevision.h` (Private)


#### class `FGitSourceControlRevision`  
`class FGitSourceControlRevision : public ISourceControlRevision`  
_L9-70_
- inherits: `ISourceControlRevision`
- desc: Revision of a file, linked to a specific commit
- L12 _public function_ `FGitSourceControlRevision() : RevisionNumber(0)`
- L18 _public prototype_ `virtual bool Get(FString& InOutFilename, EConcurrency::Type InConcurrency = EConcurrency::Synchronous) const override;` — ISourceControlRevision interface
- L19 _public prototype_ `virtual bool GetAnnotated( TArray<FAnnotationLine>& OutLines ) const override;`
- L20 _public prototype_ `virtual bool GetAnnotated( FString& InOutFilename ) const override;`
- L21 _public prototype_ `virtual const FString& GetFilename() const override;`
- L22 _public prototype_ `virtual int32 GetRevisionNumber() const override;`
- L23 _public prototype_ `virtual const FString& GetRevision() const override;`
- L24 _public prototype_ `virtual const FString& GetDescription() const override;`
- L25 _public prototype_ `virtual const FString& GetUserName() const override;`
- L26 _public prototype_ `virtual const FString& GetClientSpec() const override;`
- L27 _public prototype_ `virtual const FString& GetAction() const override;`
- L28 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetBranchSource() const override;`
- L29 _public prototype_ `virtual const FDateTime& GetDate() const override;`
- L30 _public prototype_ `virtual int32 GetCheckInIdentifier() const override;`
- L31 _public prototype_ `virtual int32 GetFileSize() const override;`
- L36 _public member_ `FString Filename;` — The filename this revision refers to
- L39 _public member_ `FString CommitId;` — The full hexadecimal SHA1 id of the commit this revision refers to
- L42 _public member_ `FString ShortCommitId;` — The short hexadecimal SHA1 id (8 first hex char out of 40) of the commit: the string to display
- L45 _public member_ `int32 CommitIdNumber;` — The numeric value of the short SHA1 (8 first hex char out of 40)
- L48 _public member_ `int32 RevisionNumber;` — The index of the revision in the history (SBlueprintRevisionMenu assumes order for the "Depot" label)
- L51 _public member_ `FString FileHash;` — The SHA1 identifier of the file at this revision
- L54 _public member_ `FString Description;` — The description of this revision
- L57 _public member_ `FString UserName;` — The user that made the change
- L60 _public member_ `FString Action;` — The action (add, edit, branch etc.) performed at this revision
- L63 _public member_ `TSharedPtr<FGitSourceControlRevision, ESPMode::ThreadSafe> BranchSource;` — Source of move ("branch" in Perforce term) if any
- L66 _public member_ `FDateTime Date;` — The date this revision was made
- L69 _public member_ `int32 FileSize;` — The size of the file at this revision

#### Free symbols / members of external scopes

- L73 _typedef_ `typedef TArray< TSharedRef<FGitSourceControlRevision, ESPMode::ThreadSafe> > TGitSourceControlHistory;` — History composed of the last 100 revisions of the file

### `Plugins/Developer/GitSourceControl/Source/GitSourceControl/Private/GitSourceControlSettings.h` (Private)


#### class `FGitSourceControlSettings`  
`class FGitSourceControlSettings`  
_L10-31_
- L14 _public prototype_ `const FString GetBinaryPath() const;` — Get the Git Binary Path
- L17 _public prototype_ `bool SetBinaryPath(const FString& InString);` — Set the Git Binary Path
- L20 _public prototype_ `void LoadSettings();` — Load settings from ini file
- L23 _public prototype_ `void SaveSettings() const;` — Save settings to ini file
- L27 _private member_ `mutable FCriticalSection CriticalSection;` — A critical section for settings access
- L30 _private member_ `FString BinaryPath;` — Git binary path

### `Plugins/Developer/GitSourceControl/Source/GitSourceControl/Private/GitSourceControlState.h` (Private)


#### enum `EWorkingCopyState::Type`  
`enum Type`  
_L9-22_
- L11 _public enumerator_ `Unknown`
- L12 _public enumerator_ `Unchanged` — called "clean" in SVN, "Pristine" in Perforce
- L13 _public enumerator_ `Added`
- L14 _public enumerator_ `Deleted`
- L15 _public enumerator_ `Modified`
- L16 _public enumerator_ `Renamed`
- L17 _public enumerator_ `Copied`
- L18 _public enumerator_ `Missing`
- L19 _public enumerator_ `Conflicted`
- L20 _public enumerator_ `NotControlled`
- L21 _public enumerator_ `Ignored`

#### class `FGitSourceControlState`  
`class FGitSourceControlState : public ISourceControlState`  
_L25-95_
- inherits: `ISourceControlState`
- L28 _public function_ `FGitSourceControlState( const FString& InLocalFilename ) : LocalFilename(InLocalFilename) , WorkingCopyState(EWorkingCopyState::Unknown) , TimeStamp(0)`
- L35 _public prototype_ `FGitSourceControlState(const FGitSourceControlState& Other);`
- L36 _public prototype_ `FGitSourceControlState(FGitSourceControlState&& Other) noexcept;`
- L37 _public prototype_ `FGitSourceControlState& operator=(const FGitSourceControlState& Other);`
- L38 _public prototype_ `FGitSourceControlState& operator=(FGitSourceControlState&& Other) noexcept;`
- L41 _public prototype_ `virtual int32 GetHistorySize() const override;` — ISourceControlState interface
- L42 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetHistoryItem(int32 HistoryIndex) const override;`
- L43 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> FindHistoryRevision(int32 RevisionNumber) const override;`
- L44 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> FindHistoryRevision(const FString& InRevision) const override;`
- L45 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetCurrentRevision() const override;`
- L46 _public prototype_ `virtual FResolveInfo GetResolveInfo() const override;`
- L48 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L50 _public prototype_ `virtual FText GetDisplayName() const override;`
- L51 _public prototype_ `virtual FText GetDisplayTooltip() const override;`
- L52 _public prototype_ `virtual const FString& GetFilename() const override;`
- L53 _public prototype_ `virtual const FDateTime& GetTimeStamp() const override;`
- L54 _public prototype_ `virtual bool CanCheckIn() const override;`
- L55 _public prototype_ `virtual bool CanCheckout() const override;`
- L56 _public prototype_ `virtual bool IsCheckedOut() const override;`
- L57 _public prototype_ `virtual bool IsCheckedOutOther(FString* Who = nullptr) const override;`
- L58 _public function_ `virtual bool IsCheckedOutInOtherBranch(const FString& CurrentBranch = FString()) const override`
- L59 _public function_ `virtual bool IsModifiedInOtherBranch(const FString& CurrentBranch = FString()) const override`
- L60 _public function_ `virtual bool IsCheckedOutOrModifiedInOtherBranch(const FString& CurrentBranch = FString()) const override`
- L61 _public function_ `virtual TArray<FString> GetCheckedOutBranches() const override`
- L62 _public function_ `virtual FString GetOtherUserBranchCheckedOuts() const override`
- L63 _public function_ `virtual bool GetOtherBranchHeadModification(FString& HeadBranchOut, FString& ActionOut, int32& HeadChangeListOut) const override`
- L64 _public prototype_ `virtual bool IsCurrent() const override;`
- L65 _public prototype_ `virtual bool IsSourceControlled() const override;`
- L66 _public prototype_ `virtual bool IsAdded() const override;`
- L67 _public prototype_ `virtual bool IsDeleted() const override;`
- L68 _public prototype_ `virtual bool IsIgnored() const override;`
- L69 _public prototype_ `virtual bool CanEdit() const override;`
- L70 _public prototype_ `virtual bool IsUnknown() const override;`
- L71 _public prototype_ `virtual bool IsModified() const override;`
- L72 _public prototype_ `virtual bool CanAdd() const override;`
- L73 _public prototype_ `virtual bool CanDelete() const override;`
- L74 _public prototype_ `virtual bool IsConflicted() const override;`
- L75 _public prototype_ `virtual bool CanRevert() const override;`
- L79 _public member_ `TGitSourceControlHistory History;` — History of the item, if any
- L82 _public member_ `FString LocalFilename;` — Filename on disk
- L85 _public member_ `FResolveInfo PendingResolveInfo;` — Pending rev info with which a file must be resolved, invalid if no resolve pending
- L88 _public member_ `FString PendingMergeBaseFileHash;` — `UE_DEPRECATED(5.3, "Use PendingResolveInfo.BaseRevision instead")`
- L91 _public member_ `EWorkingCopyState::Type WorkingCopyState;` — State of the working copy
- L94 _public member_ `FDateTime TimeStamp;` — The timestamp of the last update

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace EWorkingCopyState`

### `Plugins/Developer/GitSourceControl/Source/GitSourceControl/Private/GitSourceControlUtils.h` (Private)


#### class `FGitScopedTempFile`  
`class FGitScopedTempFile`  
_L14-30_
- desc: Helper struct for maintaining temporary files for passing to commands
- L19 _public prototype_ `FGitScopedTempFile(const FText& InText);` — Constructor - open & write string to temp file
- L22 _public prototype_ `~FGitScopedTempFile();` — Destructor - delete temp file
- L25 _public prototype_ `const FString& GetFilename() const;` — Get the filename of this temp file - empty if it failed to be created
- L29 _private member_ `FString Filename;` — The filename we are writing to

#### Free symbols / members of external scopes

- L34 _namespace_ `namespace GitSourceControlUtils`
- L41 _prototype_ `FString FindGitBinaryPath();` (scope `GitSourceControlUtils`) — Find the path to the Git binary, looking into a few places (standalone Git install, and other common tools embedding Git) @returns the path to the Git binary if found, or an empty string.
- L49 _prototype_ `bool CheckGitAvailability(const FString& InPathToGitBinary, FGitVersion* OutVersion = nullptr);` (scope `GitSourceControlUtils`) — Run a Git "version" command to check the availability of the binary. @param InPathToGitBinary		The path to the Git binary @param OutGitVersion         If provided, populate with the git version parsed from "version" command @returns true if the command succeeded and returned no errors
- L56 _prototype_ `void ParseGitVersion(const FString& InVersionString, FGitVersion* OutVersion);` (scope `GitSourceControlUtils`) — Parse the output from the "version" command into GitMajorVersion and GitMinorVersion. @param InVersionString       The version string returned by `git --version` @param OutVersion            The FGitVersion to populate
- L63 _prototype_ `void FindGitCapabilities(const FString& InPathToGitBinary, FGitVersion *OutVersion);` (scope `GitSourceControlUtils`) — Check git for various optional capabilities by various means. @param InPathToGitBinary		The path to the Git binary @param OutGitVersion			If provided, populate with the git version parsed from "version" command
- L70 _prototype_ `void FindGitLfsCapabilities(const FString& InPathToGitBinary, FGitVersion *OutVersion);` (scope `GitSourceControlUtils`) — Run a Git "lfs" command to check the availability of the "Large File System" extension. @param InPathToGitBinary		The path to the Git binary @param OutGitVersion			If provided, populate with the git version parsed from "version" command
- L78 _prototype_ `bool FindRootDirectory(const FString& InPath, FString& OutRepositoryRoot);` (scope `GitSourceControlUtils`) — Find the root of the Git repository, looking from the provided path and upward in its parent directories @param InPath				The path to the Game Directory (or any path or file in any git repository) @param OutRepositoryRoot		The path to the root directory of the Git repository if found, else the path to the ProjectDir @returns true if the command succeeded and returned no errors
- L87 _prototype_ `void GetUserConfig(const FString& InPathToGitBinary, const FString& InRepositoryRoot, FString& OutUserName, FString& OutUserEmail);` (scope `GitSourceControlUtils`) — Get Git config user.name & user.email @param	InPathToGitBinary	The path to the Git binary @param	InRepositoryRoot	The Git repository from where to run the command - usually the Game directory (can be empty) @param	OutUserName			Name of the Git user configured for this repository (or globaly) @param	OutEmailName		E-mail of the Git user configured for this repository (or globaly)
- L96 _prototype_ `bool GetBranchName(const FString& InPathToGitBinary, const FString& InRepositoryRoot, FString& OutBranchName);` (scope `GitSourceControlUtils`) — Get Git current checked-out branch @param	InPathToGitBinary	The path to the Git binary @param	InRepositoryRoot	The Git repository from where to run the command - usually the Game directory @param	OutBranchName		Name of the current checked-out branch (if any, ie. not in detached HEAD) @returns true if the command succeeded and returned no errors
- L105 _prototype_ `bool GetRemoteUrl(const FString& InPathToGitBinary, const FString& InRepositoryRoot, FString& OutRemoteUrl);` (scope `GitSourceControlUtils`) — Get the URL of the "origin" defaut remote server @param	InPathToGitBinary	The path to the Git binary @param	InRepositoryRoot	The Git repository from where to run the command - usually the Game directory @param	OutRemoteUrl		URL of "origin" defaut remote server @returns true if the command succeeded and returned no errors
- L119 _prototype_ `bool RunCommand(const FString& InCommand, const FString& InPathToGitBinary, const FString& InRepositoryRoot, const TArray<FString>& InParameters, const TArray<FString>& InFiles, TArray<FString>& OutResults, TArray<FString>& OutErrorMessages);` (scope `GitSourceControlUtils`) — Run a Git command - output is a string TArray. @param	InCommand			The Git command - e.g. commit @param	InPathToGitBinary	The path to the Git binary @param	InRepositoryRoot	The Git repository from where to run the command - usually the Game directory (can be empty) @param	InParameters		The parameters to the Git command @param	InFiles				The files to be operated on @param	OutResults			The results (from StdOut) as an array per-line @param	OutErrorMessages	Any errors (from StdErr) as an array per-line @returns true if the command succeeded and returned no errors
- L131 _prototype_ `bool RunCommit(const FString& InPathToGitBinary, const FString& InRepositoryRoot, const TArray<FString>& InParameters, const TArray<FString>& InFiles, TArray<FString>& OutResults, TArray<FString>& OutErrorMessages);` (scope `GitSourceControlUtils`) — Run a Git "commit" command by batches. @param	InPathToGitBinary	The path to the Git binary @param	InRepositoryRoot	The Git repository from where to run the command - usually the Game directory @param	InParameter			The parameters to the Git commit command @param	InFiles				The files to be operated on @param	OutErrorMessages	Any errors (from StdErr) as an array per-line @returns true if the command succeeded and returned no errors
- L142 _prototype_ `bool RunUpdateStatus(const FString& InPathToGitBinary, const FString& InRepositoryRoot, const TArray<FString>& InFiles, TArray<FString>& OutErrorMessages, TArray<FGitSourceControlState>& OutStates);` (scope `GitSourceControlUtils`) — Run a Git "status" command and parse it. @param	InPathToGitBinary	The path to the Git binary @param	InRepositoryRoot	The Git repository from where to run the command - usually the Game directory (can be empty) @param	InFiles				The files to be operated on @param	OutErrorMessages	Any errors (from StdErr) as an array per-line @returns true if the command succeeded and returned no errors
- L153 _prototype_ `bool RunDumpToFile(const FString& InPathToGitBinary, const FString& InRepositoryRoot, const FString& InParameter, const FString& InDumpFileName);` (scope `GitSourceControlUtils`) — Run a Git "cat-file" command to dump the binary content of a revision into a file. @param	InPathToGitBinary	The path to the Git binary @param	InRepositoryRoot	The Git repository from where to run the command - usually the Game directory @param	InParameter			The parameters to the Git show command (rev:path) @param	InDumpFileName		The temporary file to dump the revision @returns true if the command succeeded and returned no errors
- L165 _prototype_ `bool RunGetHistory(const FString& InPathToGitBinary, const FString& InRepositoryRoot, const FString& InFile, bool bMergeConflict, TArray<FString>& OutErrorMessages, TGitSourceControlHistory& OutHistory);` (scope `GitSourceControlUtils`) — Run a Git "log" command and parse it. @param	InPathToGitBinary	The path to the Git binary @param	InRepositoryRoot	The Git repository from where to run the command - usually the Game directory @param	InFile				The file to be operated on @param	bMergeConflict		In case of a merge conflict, we also need to get the tip of the "remote branch" (MERGE_HEAD) before the log of the "current branch" (HEAD) @param	OutErrorMessages	Any errors (from StdErr) as an array per-line @param	OutHistory			The history of the file
- L171 _prototype_ `bool UpdateCachedStates(const TArray<FGitSourceControlState>& InStates);` (scope `GitSourceControlUtils`) — Helper function for various commands to update cached states. @returns true if any states were updated
- L177 _prototype_ `void RemoveRedundantErrors(FGitSourceControlCommand& InCommand, const FString& InFilter);` (scope `GitSourceControlUtils`) — Remove redundant errors (that contain a particular string) and also update the commands success status if all errors were removed.

### `Plugins/Developer/GitSourceControl/Source/GitSourceControl/Private/IGitSourceControlWorker.h` (Private)


#### class `IGitSourceControlWorker`  
`class IGitSourceControlWorker`  
_L7-25_
- L13 _public prototype_ `virtual FName GetName() const = 0;` — Name describing the work that this worker does. Used for factory method hookup.
- L18 _public prototype_ `virtual bool Execute( class FGitSourceControlCommand& InCommand ) = 0;` — Function that actually does the work. Can be executed on another thread.
- L24 _public prototype_ `virtual bool UpdateStates() const = 0;` — Updates the state of any items after completion (if necessary). This is always executed on the main thread. @returns true if states were updated

#### Free symbols / members of external scopes

- L27 _typedef_ `typedef TSharedRef<IGitSourceControlWorker, ESPMode::ThreadSafe> FGitSourceControlWorkerRef;`

### `Plugins/Developer/GitSourceControl/Source/GitSourceControl/Private/SGitSourceControlSettings.h` (Private)


#### class `SGitSourceControlSettings`  
`class SGitSourceControlSettings : public SCompoundWidget`  
_L13-82_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SGitSourceControlSettings)`
- L23 _public prototype_ `void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `~SGitSourceControlSettings();`
- L30 _private prototype_ `FString GetBinaryPathString() const;` — Delegates to get Git binary path from/to settings
- L31 _private prototype_ `void OnBinaryPathPicked(const FString & PickedPath) const;`
- L34 _private prototype_ `FText GetPathToRepositoryRoot() const;` — Delegate to get repository root, user name and email from provider
- L35 _private prototype_ `FText GetUserName() const;`
- L36 _private prototype_ `FText GetUserEmail() const;`
- L38 _private prototype_ `EVisibility CanInitializeGitRepository() const;`
- L39 _private prototype_ `bool CanInitializeGitLfs() const;`
- L42 _private prototype_ `FReply OnClickedInitializeGitRepository();` — Delegate to initialize a new Git repository
- L44 _private prototype_ `void OnCheckedCreateGitIgnore(ECheckBoxState NewCheckedState);`
- L45 _private member_ `bool bAutoCreateGitIgnore;`
- L48 _private prototype_ `void OnCheckedCreateReadme(ECheckBoxState NewCheckedState);` — Delegates to create a README.md file
- L49 _private prototype_ `bool GetAutoCreateReadme() const;`
- L50 _private member_ `bool bAutoCreateReadme;`
- L51 _private prototype_ `void OnReadmeContentCommited(const FText& InText, ETextCommit::Type InCommitType);`
- L52 _private prototype_ `FText GetReadmeContent() const;`
- L53 _private member_ `FText ReadmeContent;`
- L55 _private prototype_ `void OnCheckedCreateGitAttributes(ECheckBoxState NewCheckedState);`
- L56 _private member_ `bool bAutoCreateGitAttributes;`
- L58 _private prototype_ `void OnCheckedInitialCommit(ECheckBoxState NewCheckedState);`
- L59 _private member_ `bool bAutoInitialCommit;`
- L60 _private prototype_ `void OnInitialCommitMessageCommited(const FText& InText, ETextCommit::Type InCommitType);`
- L61 _private prototype_ `FText GetInitialCommitMessage() const;`
- L62 _private member_ `FText InitialCommitMessage;`
- L64 _private prototype_ `void OnRemoteUrlCommited(const FText& InText, ETextCommit::Type InCommitType);`
- L65 _private prototype_ `FText GetRemoteUrl() const;`
- L66 _private member_ `FText RemoteUrl;`
- L69 _private prototype_ `void LaunchMarkForAddOperation(const TArray<FString>& InFiles);` — Launch initial asynchronous add and commit operations
- L70 _private prototype_ `void LaunchCheckInOperation();`
- L73 _private prototype_ `void OnSourceControlOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Delegate called when a source control operation has completed
- L76 _private member_ `TWeakPtr<SNotificationItem> OperationInProgressNotification;` — Asynchronous operation progress notifications
- L78 _private prototype_ `void DisplayInProgressNotification(const FSourceControlOperationRef& InOperation);`
- L79 _private prototype_ `void RemoveInProgressNotification();`
- L80 _private prototype_ `void DisplaySuccessNotification(const FSourceControlOperationRef& InOperation);`
- L81 _private prototype_ `void DisplayFailureNotification(const FSourceControlOperationRef& InOperation);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ETextCommit`
