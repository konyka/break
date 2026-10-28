# Plugins / SubversionSourceControl

- module root: `Plugins/Developer/SubversionSourceControl/Source/SubversionSourceControl`
- headers: 11; symbols: 312
- symbol kinds: class=20, delegate=1, enum=2, enumerator=19, function=26, member=66, namespace=4, prototype=172, typedef=2
- PrivateDependencyModuleNames: Core, Slate, SlateCore, SourceControl, XmlParser

### `Plugins/Developer/SubversionSourceControl/Source/SubversionSourceControl/Private/ISubversionSourceControlWorker.h` (Private)


#### class `ISubversionSourceControlWorker`  
`class ISubversionSourceControlWorker`  
_L7-25_
- L13 _public prototype_ `virtual FName GetName() const = 0;` — Name describing the work that this worker does. Used for factory method hookup.
- L18 _public prototype_ `virtual bool Execute( class FSubversionSourceControlCommand& InCommand ) = 0;` — Function that actually does the work. Can be executed on another thread.
- L24 _public prototype_ `virtual bool UpdateStates() const = 0;` — Updates the state of any items after completion (if necessary). This is always executed on the main thread. @returns true if states were updated

#### Free symbols / members of external scopes

- L27 _typedef_ `typedef TSharedRef<ISubversionSourceControlWorker, ESPMode::ThreadSafe> FSubversionSourceControlWorkerRef;`

### `Plugins/Developer/SubversionSourceControl/Source/SubversionSourceControl/Private/SSubversionSourceControlSettings.h` (Private)


#### class `SSubversionSourceControlSettings`  
`class SSubversionSourceControlSettings : public SCompoundWidget`  
_L9-48_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SSubversionSourceControlSettings)`
- L19 _public prototype_ `void Construct(const FArguments& InArgs);`
- L22 _public prototype_ `static FString GetPassword();` — Get the currently entered password
- L27 _private prototype_ `FText GetRepositoryText() const;` — Delegate to get repository text from settings
- L30 _private prototype_ `void OnRepositoryTextCommited(const FText& InText, ETextCommit::Type InCommitType) const;` — Delegate to commit repository text to settings
- L33 _private prototype_ `FText GetUserNameText() const;` — Delegate to get user name text from settings
- L36 _private prototype_ `void OnUserNameTextCommited(const FText& InText, ETextCommit::Type InCommitType) const;` — Delegate to commit user name text to settings
- L39 _private prototype_ `FText GetLabelsRootText() const;` — Delegate to get labels root text from settings
- L42 _private prototype_ `void OnLabelsRootTextCommited(const FText& InText, ETextCommit::Type InCommitType) const;` — Delegate to commit labels root text to settings
- L47 _private member_ `static TWeakPtr<class SEditableTextBox> PasswordTextBox;` — Pointer to the password text box widget

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ETextCommit`

### `Plugins/Developer/SubversionSourceControl/Source/SubversionSourceControl/Private/SubversionSourceControlCommand.h` (Private)


#### class `FSubversionSourceControlCommand`  
`class FSubversionSourceControlCommand : public IQueuedWork`  
_L11-77_
- inherits: `IQueuedWork`
- desc: Used to execute Subversion commands multi-threaded.
- L15 _public prototype_ `FSubversionSourceControlCommand(const TSharedRef<class ISourceControlOperation, ESPMode::ThreadSafe>& InOperation, const TSharedRef<class ISubversionSourceControlWorker, ESPMode::ThreadSafe>& InWorker, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() );`
- L21 _public prototype_ `bool DoWork();` — This is where the real thread work is done. All work that is done for this queued object should be done from within the call to this function.
- L29 _public prototype_ `virtual void Abandon() override;` — Tells the queued work that it is being abandoned so that it can do per object clean up as needed. This will only be called if it is being abandoned before completion. NOTE: This requires the object to delete itself using whatever heap it was allocated in.
- L35 _public prototype_ `virtual void DoThreadedWork() override;` — This method is also used to tell the object to cleanup but not before the object has finished it's work.
- L38 _public prototype_ `ECommandResult::Type ReturnResults();` — Save any results and call any registered callbacks.
- L42 _public member_ `FString RepositoryName;` — Connection parameters, reproduced here because if is not safe to access the provider's settings from another thread
- L43 _public member_ `FString UserName;`
- L44 _public member_ `FString Password;`
- L45 _public member_ `FString WorkingCopyRoot;`
- L46 _public member_ `FString RepositoryRoot;`
- L49 _public member_ `TSharedRef<class ISourceControlOperation, ESPMode::ThreadSafe> Operation;` — Operation we want to perform - contains outward-facing parameters & results
- L52 _public member_ `TSharedRef<class ISubversionSourceControlWorker, ESPMode::ThreadSafe> Worker;` — The object that will actually do the work
- L55 _public member_ `FSourceControlOperationComplete OperationCompleteDelegate;` — Delegate to notify when this operation completes
- L58 _public member_ `volatile int32 bExecuteProcessed;` — If true, this command has been processed by the source control thread
- L61 _public member_ `bool bCommandSuccessful;` — If true, the source control command succeeded
- L64 _public member_ `bool bAutoDelete;` — If true, this command will be automatically cleaned up in Tick()
- L67 _public member_ `EConcurrency::Type Concurrency;` — Whether we are running multi-treaded or not
- L70 _public member_ `TArray< FString > Files;` — Files to perform this operation on
- L73 _public member_ `TArray< FString > InfoMessages;` — Info and/or warning message message storage
- L76 _public member_ `TArray< FString > ErrorMessages;` — Potential error message storage

### `Plugins/Developer/SubversionSourceControl/Source/SubversionSourceControl/Private/SubversionSourceControlLabel.h` (Private)


#### class `FSubversionSourceControlLabel`  
`class FSubversionSourceControlLabel : public ISourceControlLabel`  
_L27-53_
- inherits: `ISourceControlLabel`
- desc: Abstraction of a 'Subversion label'. Some things to note: Subversion doesn't have 'label' functionality like Perforce, although it is flexible enough to allow us to emulate it. We assume that a standard SVN repository layout is used, i.e.: repo/ repo/branches/ repo/trunk/ repo/tags/ The tags directory (which can be user specified in the UE SVN settings) is the one we are interested in. This implementation assumes that each subdirectory (e.g. repo/tags/LabelName) in the tags dir is an analogue of a Perforce label. That is, the revision of the folder specifies a tagged revision of the repository. For the moment, our 'labels' don't filter the parts of the repo that are under them, so they effectively just act as metadata on a revision number across the whole repo.
- L31 _public function_ `FSubversionSourceControlLabel( const FString& InName, const FString& InDirectory, int32 InRevision ) : Name(InName) , Directory(InDirectory) , Revision(InRevision)`
- L39 _public prototype_ `virtual const FString& GetName() const override;` — ISourceControlLabel implementation
- L40 _public prototype_ `virtual bool GetFileRevisions( const TArray<FString>& InFiles, TArray< TSharedRef<ISourceControlRevision, ESPMode::ThreadSafe> >& OutRevisions ) const override;`
- L41 _public prototype_ `virtual bool Sync( const TArray<FString>& InFilenames ) const override;`
- L46 _private member_ `FString Name;` — Label name
- L49 _private member_ `FString Directory;` — Label directory in the repository
- L52 _private member_ `int32 Revision;` — Repository revision this label was created at

### `Plugins/Developer/SubversionSourceControl/Source/SubversionSourceControl/Private/SubversionSourceControlModule.h` (Private)


#### class `FSubversionSourceControlModule`  
`class FSubversionSourceControlModule : public IModuleInterface`  
_L9-34_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _public prototype_ `FSubversionSourceControlSettings& AccessSettings();` — Access the Subversion source control settings
- L20 _public prototype_ `void SaveSettings();` — Save the Subversion source control settings
- L23 _public function_ `FSubversionSourceControlProvider& GetProvider()` — Access the one and only Subversion provider
- L30 _private member_ `FSubversionSourceControlProvider SubversionSourceControlProvider;` — The one and only Subversion source control provider
- L33 _private member_ `FSubversionSourceControlSettings SubversionSourceControlSettings;` — The settings for Subversion source control

### `Plugins/Developer/SubversionSourceControl/Source/SubversionSourceControl/Private/SubversionSourceControlOperations.h` (Private)


#### class `FSubversionConnectWorker`  
`class FSubversionConnectWorker : public ISubversionSourceControlWorker`  
_L9-24_
- inherits: `ISubversionSourceControlWorker`
- L12 _public function_ `virtual ~FSubversionConnectWorker()`
- L14 _public prototype_ `virtual FName GetName() const override;` — ISubversionSourceControlWorker interface
- L15 _public prototype_ `virtual bool Execute(class FSubversionSourceControlCommand& InCommand) override;`
- L16 _public prototype_ `virtual bool UpdateStates() const override;`
- L20 _private member_ `FString WorkingCopyRoot;` — The root of our working copy
- L23 _private member_ `FString RepositoryRoot;` — The root of our repository

#### class `FSubversionCheckOutWorker`  
`class FSubversionCheckOutWorker : public ISubversionSourceControlWorker`  
_L26-38_
- inherits: `ISubversionSourceControlWorker`
- L29 _public function_ `virtual ~FSubversionCheckOutWorker()`
- L31 _public prototype_ `virtual FName GetName() const override;` — ISubversionSourceControlWorker interface
- L32 _public prototype_ `virtual bool Execute(class FSubversionSourceControlCommand& InCommand) override;`
- L33 _public prototype_ `virtual bool UpdateStates() const override;`
- L37 _public member_ `TArray<FSubversionSourceControlState> OutStates;` — Temporary states for results

#### class `FSubversionCheckInWorker`  
`class FSubversionCheckInWorker : public ISubversionSourceControlWorker`  
_L40-52_
- inherits: `ISubversionSourceControlWorker`
- L43 _public function_ `virtual ~FSubversionCheckInWorker()`
- L45 _public prototype_ `virtual FName GetName() const override;` — ISubversionSourceControlWorker interface
- L46 _public prototype_ `virtual bool Execute(class FSubversionSourceControlCommand& InCommand) override;`
- L47 _public prototype_ `virtual bool UpdateStates() const override;`
- L51 _public member_ `TArray<FSubversionSourceControlState> OutStates;` — Temporary states for results

#### class `FSubversionMarkForAddWorker`  
`class FSubversionMarkForAddWorker : public ISubversionSourceControlWorker`  
_L54-66_
- inherits: `ISubversionSourceControlWorker`
- L57 _public function_ `virtual ~FSubversionMarkForAddWorker()`
- L59 _public prototype_ `virtual FName GetName() const override;` — ISubversionSourceControlWorker interface
- L60 _public prototype_ `virtual bool Execute(class FSubversionSourceControlCommand& InCommand) override;`
- L61 _public prototype_ `virtual bool UpdateStates() const override;`
- L65 _public member_ `TArray<FSubversionSourceControlState> OutStates;` — Temporary states for results

#### class `FSubversionDeleteWorker`  
`class FSubversionDeleteWorker : public ISubversionSourceControlWorker`  
_L68-80_
- inherits: `ISubversionSourceControlWorker`
- L71 _public function_ `virtual ~FSubversionDeleteWorker()`
- L73 _public prototype_ `virtual FName GetName() const override;` — ISubversionSourceControlWorker interface
- L74 _public prototype_ `virtual bool Execute(class FSubversionSourceControlCommand& InCommand) override;`
- L75 _public prototype_ `virtual bool UpdateStates() const override;`
- L79 _public member_ `TArray<FSubversionSourceControlState> OutStates;` — Map of filenames to Subversion state

#### class `FSubversionRevertWorker`  
`class FSubversionRevertWorker : public ISubversionSourceControlWorker`  
_L82-94_
- inherits: `ISubversionSourceControlWorker`
- L85 _public function_ `virtual ~FSubversionRevertWorker()`
- L87 _public prototype_ `virtual FName GetName() const override;` — ISubversionSourceControlWorker interface
- L88 _public prototype_ `virtual bool Execute(class FSubversionSourceControlCommand& InCommand) override;`
- L89 _public prototype_ `virtual bool UpdateStates() const override;`
- L93 _public member_ `TArray<FSubversionSourceControlState> OutStates;` — Map of filenames to Subversion state

#### class `FSubversionSyncWorker`  
`class FSubversionSyncWorker : public ISubversionSourceControlWorker`  
_L96-108_
- inherits: `ISubversionSourceControlWorker`
- L99 _public function_ `virtual ~FSubversionSyncWorker()`
- L101 _public prototype_ `virtual FName GetName() const override;` — ISubversionSourceControlWorker interface
- L102 _public prototype_ `virtual bool Execute(class FSubversionSourceControlCommand& InCommand) override;`
- L103 _public prototype_ `virtual bool UpdateStates() const override;`
- L107 _public member_ `TArray<FSubversionSourceControlState> OutStates;` — Map of filenames to Subversion state

#### class `FSubversionUpdateStatusWorker`  
`class FSubversionUpdateStatusWorker : public ISubversionSourceControlWorker`  
_L110-125_
- inherits: `ISubversionSourceControlWorker`
- L113 _public function_ `virtual ~FSubversionUpdateStatusWorker()`
- L115 _public prototype_ `virtual FName GetName() const override;` — ISubversionSourceControlWorker interface
- L116 _public prototype_ `virtual bool Execute(class FSubversionSourceControlCommand& InCommand) override;`
- L117 _public prototype_ `virtual bool UpdateStates() const override;`
- L121 _public member_ `TArray<FSubversionSourceControlState> OutStates;` — Temporary states for results
- L124 _public member_ `SubversionSourceControlUtils::FHistoryOutput OutHistory;` — Map of filenames to history

#### class `FSubversionCopyWorker`  
`class FSubversionCopyWorker : public ISubversionSourceControlWorker`  
_L127-139_
- inherits: `ISubversionSourceControlWorker`
- L130 _public function_ `virtual ~FSubversionCopyWorker()`
- L132 _public prototype_ `virtual FName GetName() const override;` — ISubversionSourceControlWorker interface
- L133 _public prototype_ `virtual bool Execute(class FSubversionSourceControlCommand& InCommand) override;`
- L134 _public prototype_ `virtual bool UpdateStates() const override;`
- L138 _public member_ `TArray<FSubversionSourceControlState> OutStates;` — Map of filenames to Subversion state

#### class `FSubversionResolveWorker`  
`class FSubversionResolveWorker : public ISubversionSourceControlWorker`  
_L141-152_
- inherits: `ISubversionSourceControlWorker`
- L144 _public function_ `virtual ~FSubversionResolveWorker()`
- L145 _public prototype_ `virtual FName GetName() const override;`
- L146 _public prototype_ `virtual bool Execute( class FSubversionSourceControlCommand& InCommand ) override;`
- L147 _public prototype_ `virtual bool UpdateStates() const override;`
- L151 _private member_ `TArray<FSubversionSourceControlState> OutStates;` — Map of filenames to Subversion state

### `Plugins/Developer/SubversionSourceControl/Source/SubversionSourceControl/Private/SubversionSourceControlProvider.h` (Private)


#### class `FSubversionSourceControlProvider`  
`class FSubversionSourceControlProvider : public ISourceControlProvider`  
_L14-159_
- inherits: `ISourceControlProvider`
- L18 _public function_ `FSubversionSourceControlProvider() : bWorkingOffline(true)` — Constructor
- L24 _public prototype_ `virtual void Init(bool bForceConnection = true) override;` — ISourceControlProvider implementation
- L25 _public prototype_ `virtual void Close() override;`
- L26 _public prototype_ `virtual FText GetStatusText() const override;`
- L27 _public prototype_ `virtual TMap<EStatus, FString> GetStatus() const override;`
- L28 _public prototype_ `virtual bool IsEnabled() const override;`
- L29 _public prototype_ `virtual bool IsAvailable() const override;`
- L30 _public prototype_ `virtual const FName& GetName(void) const override;`
- L31 _public function_ `virtual bool QueryStateBranchConfig(const FString& ConfigSrc, const FString& ConfigDest) override`
- L32 _public function_ `virtual void RegisterStateBranches(const TArray<FString>& BranchNames, const FString& ContentRoot) override`
- L33 _public function_ `virtual int32 GetStateBranchIndex(const FString& BranchName) const override`
- L34 _public function_ `virtual bool GetStateBranchAtIndex(int32 BranchIndex, FString& OutBranchName) const override`
- L35 _public prototype_ `virtual ECommandResult::Type GetState( const TArray<FString>& InFiles, TArray<FSourceControlStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage ) override;`
- L36 _public prototype_ `virtual ECommandResult::Type GetState(const TArray<FSourceControlChangelistRef>& InChangelists, TArray<FSourceControlChangelistStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage) override;`
- L37 _public prototype_ `virtual TArray<FSourceControlStateRef> GetCachedStateByPredicate(TFunctionRef<bool(const FSourceControlStateRef&)> Predicate) const override;`
- L38 _public prototype_ `virtual FDelegateHandle RegisterSourceControlStateChanged_Handle( const FSourceControlStateChanged::FDelegate& SourceControlStateChanged ) override;`
- L39 _public prototype_ `virtual void UnregisterSourceControlStateChanged_Handle( FDelegateHandle Handle ) override;`
- L40 _public prototype_ `virtual ECommandResult::Type Execute( const FSourceControlOperationRef& InOperation, FSourceControlChangelistPtr InChangelist, const TArray<FString>& InFiles, EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() ) override;`
- L41 _public prototype_ `virtual bool CanExecuteOperation( const FSourceControlOperationRef& InOperation ) const override;`
- L42 _public prototype_ `virtual bool CanCancelOperation( const FSourceControlOperationRef& InOperation ) const override;`
- L43 _public prototype_ `virtual void CancelOperation( const FSourceControlOperationRef& InOperation ) override;`
- L44 _public prototype_ `virtual bool UsesLocalReadOnlyState() const override;`
- L45 _public prototype_ `virtual bool UsesChangelists() const override;`
- L46 _public prototype_ `virtual bool UsesUncontrolledChangelists() const override;`
- L47 _public prototype_ `virtual bool UsesCheckout() const override;`
- L48 _public prototype_ `virtual bool UsesFileRevisions() const override;`
- L49 _public prototype_ `virtual bool UsesSnapshots() const override;`
- L50 _public prototype_ `virtual bool UsesSoftRevertOnDelete() const override;`
- L51 _public prototype_ `virtual bool AllowsDiffAgainstDepot() const override;`
- L52 _public prototype_ `virtual TOptional<bool> HasChangesToSync() const override;`
- L53 _public prototype_ `virtual TOptional<bool> HasChangesToCheckIn() const override;`
- L54 _public prototype_ `virtual void Tick() override;`
- L55 _public prototype_ `virtual TArray< TSharedRef<class ISourceControlLabel> > GetLabels( const FString& InMatchingSpec ) const override;`
- L56 _public prototype_ `virtual TArray<FSourceControlChangelistRef> GetChangelists( EStateCacheUsage::Type InStateCacheUsage ) override;`
- L58 _public prototype_ `virtual TSharedRef<class SWidget> MakeSettingsWidget() const override;`
- L64 _public prototype_ `const FString& GetRepositoryName() const;` — Get the address of the repository
- L67 _public prototype_ `const FString& GetUserName() const;` — Get the username we use to access the repository
- L70 _public prototype_ `const FString& GetWorkingCopyRoot() const;` — Get the root of our working copy
- L73 _public prototype_ `void SetWorkingCopyRoot(const FString& InWorkingCopyRoot);` — Set the root of our working copy
- L76 _public prototype_ `const FString& GetRepositoryRoot() const;` — Get the root of our repository
- L79 _public prototype_ `void SetRepositoryRoot(const FString& InRepositoryRoot);` — Set the root of our repository
- L82 _public prototype_ `TSharedRef<FSubversionSourceControlState, ESPMode::ThreadSafe> GetStateInternal(const FString& Filename);` — Helper function used to update state cache
- L85 _public prototype_ `bool RemoveFileFromCache(const FString& Filename);` — Remove a named file from the state cache
- L91 _public prototype_ `void RegisterWorker( const FName& InName, const FGetSubversionSourceControlWorker& InDelegate );` — Register a worker with the provider. This is used internally so the provider can maintain a map of all available operations.
- L96 _private prototype_ `TSharedPtr<class ISubversionSourceControlWorker, ESPMode::ThreadSafe> CreateWorker(const FName& InOperationName) const;` — Helper function for Execute()
- L105 _private prototype_ `void AutoAcceptNonTrustedSSL(const FString& Password);` — In the case that a non-trusted SSL certificate came from a hostname other than the issuing server (say you are accessing the server via its IP rather than its DNS entry), we need to do some command-line trickery to auto-accept the SSL certificate. @param	Password	The password to use when attempting to auto-accept the SSL certificate
- L110 _private prototype_ `void ParseCommandLineSettings(bool bForceConnection);` — Loads user/SCC information from the INI file.
- L115 _private prototype_ `ECommandResult::Type ExecuteSynchronousCommand(class FSubversionSourceControlCommand& InCommand, const FText& Task, bool bSuppressResponseMsg);` — Helper function for running command synchronously.
- L120 _private prototype_ `ECommandResult::Type IssueCommand(class FSubversionSourceControlCommand& InCommand, const bool bSynchronous);` — Run a command synchronously or asynchronously.
- L125 _private prototype_ `bool TestConnection(const FString& RepositoryName, const FString& UserName, const FString& Password = FString());` — Test the connection to the repository.
- L130 _private prototype_ `void OutputCommandMessages(const class FSubversionSourceControlCommand& InCommand) const;` — Output any messages this command holds
- L135 _private prototype_ `void UpdateConnectionState(class FSubversionSourceControlCommand& InCommand);` — Update the connection state according to the results of this command.
- L140 _private member_ `FString WorkingCopyRoot;` — Cached working copy root
- L143 _private member_ `FString RepositoryRoot;` — Cached repository root
- L146 _private member_ `bool bWorkingOffline;` — Flag for working offline - i.e. we haven't been able to connect to a server yet
- L149 _private member_ `TMap<FString, TSharedRef<class FSubversionSourceControlState, ESPMode::ThreadSafe> > StateCache;` — State cache
- L152 _private member_ `TMap<FName, FGetSubversionSourceControlWorker> WorkersMap;` — The currently registered source control operations
- L155 _private member_ `TArray < FSubversionSourceControlCommand* > CommandQueue;` — Queue for commands given by the main thread
- L158 _private member_ `FSourceControlStateChanged OnSourceControlStateChanged;` — For notifying when the source control states in the cache have changed

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_RetVal(FSubversionSourceControlWorkerRef, FGetSubversionSourceControlWorker) class FSubversionSourceControlProvider : public ISourceControlProvider { public: FSubversionSourceControlProvider() : bWorkingOffline(true) { } virtual void Init(bool bForceConnection = true) override; virtual void Close() override; virtual FText GetStatusText() const override; virtual TMap<EStatus, FString> GetStatus() const override; virtual bool IsEnabled() const override; virtual bool IsAvailable() const override; virtual const FName& GetName(void) const override; virtual bool QueryStateBranchConfig(const FString& ConfigSrc, const FString& ConfigDest) override { return false; } virtual void RegisterStateBranches(const TArray<FString>& BranchNames, const FString& ContentRoot) override {} virtual int32 GetStateBranchIndex(const FString& BranchName) const override { return INDEX_NONE; } virtual bool GetStateBranchAtIndex(int32 BranchIndex, FString& OutBranchName) const override { return false; } virtual ECommandResult::Type GetState( const TArray<FString>& InFiles, TArray<FSourceControlStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage ) override; virtual ECommandResult::Type GetState(const TArray<FSourceControlChangelistRef>& InChangelists, TArray<FSourceControlChangelistStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage) override; virtual TArray<FSourceControlStateRef> GetCachedStateByPredicate(TFunctionRef<bool(const FSourceControlStateRef&)> Predicate) cons`

### `Plugins/Developer/SubversionSourceControl/Source/SubversionSourceControl/Private/SubversionSourceControlRevision.h` (Private)


#### class `FSubversionSourceControlRevision`  
`class FSubversionSourceControlRevision : public ISourceControlRevision`  
_L8-61_
- inherits: `ISourceControlRevision`
- L11 _public function_ `FSubversionSourceControlRevision() : RevisionNumber(0) , Date(0)`
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
- L28 _public prototype_ `virtual TSharedPtr<ISourceControlRevision, ESPMode::ThreadSafe> GetBranchSource() const override;`
- L29 _public prototype_ `virtual const FDateTime& GetDate() const override;`
- L30 _public prototype_ `virtual int32 GetCheckInIdentifier() const override;`
- L31 _public prototype_ `virtual int32 GetFileSize() const override;`
- L36 _public member_ `FString Filename;` — The filename this revision refers to
- L39 _public member_ `int32 RevisionNumber;` — The revision number
- L42 _public member_ `FString Revision;` — The revision to display to users
- L45 _public member_ `FString Description;` — The description of this revision
- L48 _public member_ `FString UserName;` — The user that made the change
- L51 _public member_ `FString Action;` — The action (add, edit etc.) performed at this revision
- L54 _public member_ `TSharedPtr<FSubversionSourceControlRevision, ESPMode::ThreadSafe> BranchSource;` — Source of branch, if any
- L57 _public member_ `FDateTime Date;` — The date this revision was made
- L60 _public member_ `FString RepoFilename;` — The repo URL

### `Plugins/Developer/SubversionSourceControl/Source/SubversionSourceControl/Private/SubversionSourceControlSettings.h` (Private)


#### class `FSubversionSourceControlSettings`  
`class FSubversionSourceControlSettings`  
_L10-55_
- L14 _public prototype_ `const FString& GetRepository() const;` — Get the Subversion Repository
- L17 _public prototype_ `void SetRepository(const FString& InString);` — Set the Subversion host
- L20 _public prototype_ `const FString& GetUserName() const;` — Get the Subversion username
- L23 _public prototype_ `void SetUserName(const FString& InString);` — Set the Subversion username
- L26 _public prototype_ `const FString& GetLabelsRoot() const;` — Get the Subversion labels root
- L29 _public prototype_ `void SetLabelsRoot(const FString& InString);` — Set the Subversion labels root
- L32 _public prototype_ `FString GetExecutableOverride() const;` — Get the svn executable location override
- L35 _public prototype_ `void LoadSettings();` — Load settings from ini file
- L38 _public prototype_ `void SaveSettings() const;` — Save settings to ini file
- L42 _private member_ `mutable FCriticalSection CriticalSection;` — A critical section for settings access
- L45 _private member_ `FString Repository;` — Address of SVN repository
- L48 _private member_ `FString UserName;` — SVN username
- L51 _private member_ `FString LabelsRoot;` — Relative path to repository root where labels/tags are stored. For example, if the labels/tags were to be stored in 'http://repo-name/tags/', then the path here would be 'tags/'
- L54 _private member_ `FString ExecutableLocation;` — Advanced: Location of the svn executable to use. Used to explicitly override the default detection path / fallback executable

### `Plugins/Developer/SubversionSourceControl/Source/SubversionSourceControl/Private/SubversionSourceControlState.h` (Private)


#### enum `EWorkingCopyState::Type`  
`enum Type`  
_L12-29_
- L14 _public enumerator_ `Unknown`
- L15 _public enumerator_ `Pristine`
- L16 _public enumerator_ `Added`
- L17 _public enumerator_ `Deleted`
- L18 _public enumerator_ `Modified`
- L19 _public enumerator_ `Replaced`
- L20 _public enumerator_ `Conflicted`
- L21 _public enumerator_ `External`
- L22 _public enumerator_ `Ignored`
- L23 _public enumerator_ `Incomplete`
- L24 _public enumerator_ `Merged`
- L25 _public enumerator_ `NotControlled`
- L26 _public enumerator_ `Obstructed`
- L27 _public enumerator_ `Missing`
- L28 _public enumerator_ `NotAWorkingCopy`

#### enum `ELockState::Type`  
`enum Type`  
_L34-40_
- L36 _public enumerator_ `Unknown`
- L37 _public enumerator_ `NotLocked`
- L38 _public enumerator_ `Locked`
- L39 _public enumerator_ `LockedOther`

#### class `FSubversionSourceControlState`  
`class FSubversionSourceControlState : public ISourceControlState`  
_L43-133_
- inherits: `ISourceControlState`
- L46 _public function_ `FSubversionSourceControlState( const FString& InLocalFilename ) : LocalFilename(InLocalFilename) , LocalRevNumber(INVALID_REVISION) , PendingMergeBaseFileRevNumber(INVALID_REVISION) , bNewerVersionOnServer(false) , WorkingCopyState(EWorkingCopyState::Unknown) , LockState(ELockState::Unknown) , TimeStamp(0) , bCopied(false)`
- L58 _public prototype_ `FSubversionSourceControlState();`
- L59 _public prototype_ `FSubversionSourceControlState(const FSubversionSourceControlState& Other);`
- L60 _public prototype_ `FSubversionSourceControlState(FSubversionSourceControlState&& Other) noexcept;`
- L61 _public prototype_ `FSubversionSourceControlState& operator=(const FSubversionSourceControlState& Other);`
- L62 _public prototype_ `FSubversionSourceControlState& operator=(FSubversionSourceControlState&& Other) noexcept;`
- L65 _public prototype_ `virtual int32 GetHistorySize() const override;` — ISourceControlState interface
- L66 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetHistoryItem( int32 HistoryIndex ) const override;`
- L67 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> FindHistoryRevision( int32 RevisionNumber ) const override;`
- L68 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> FindHistoryRevision( const FString& InRevision ) const override;`
- L69 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetCurrentRevision() const override;`
- L70 _public prototype_ `virtual FResolveInfo GetResolveInfo() const override;`
- L72 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L74 _public prototype_ `virtual FText GetDisplayName() const override;`
- L75 _public prototype_ `virtual FText GetDisplayTooltip() const override;`
- L76 _public prototype_ `virtual const FString& GetFilename() const override;`
- L77 _public prototype_ `virtual const FDateTime& GetTimeStamp() const override;`
- L78 _public prototype_ `virtual bool CanCheckIn() const override;`
- L79 _public prototype_ `virtual bool CanCheckout() const override;`
- L80 _public prototype_ `virtual bool IsCheckedOut() const override;`
- L81 _public prototype_ `virtual bool IsCheckedOutOther(FString* Who = NULL) const override;`
- L82 _public function_ `virtual bool IsCheckedOutInOtherBranch(const FString& CurrentBranch = FString()) const override`
- L83 _public function_ `virtual bool IsModifiedInOtherBranch(const FString& CurrentBranch = FString()) const override`
- L84 _public function_ `virtual bool IsCheckedOutOrModifiedInOtherBranch(const FString& CurrentBranch = FString()) const override`
- L85 _public function_ `virtual TArray<FString> GetCheckedOutBranches() const override`
- L86 _public function_ `virtual FString GetOtherUserBranchCheckedOuts() const override`
- L87 _public function_ `virtual bool GetOtherBranchHeadModification(FString& HeadBranchOut, FString& ActionOut, int32& HeadChangeListOut) const override`
- L88 _public prototype_ `virtual bool IsCurrent() const override;`
- L89 _public prototype_ `virtual bool IsSourceControlled() const override;`
- L90 _public prototype_ `virtual bool IsAdded() const override;`
- L91 _public prototype_ `virtual bool IsDeleted() const override;`
- L92 _public prototype_ `virtual bool IsIgnored() const override;`
- L93 _public prototype_ `virtual bool CanEdit() const override;`
- L94 _public prototype_ `virtual bool IsUnknown() const override;`
- L95 _public prototype_ `virtual bool IsModified() const override;`
- L96 _public prototype_ `virtual bool CanAdd() const override;`
- L97 _public prototype_ `virtual bool CanDelete() const override;`
- L98 _public prototype_ `virtual bool CanRevert() const override;`
- L102 _public member_ `TArray< TSharedRef<FSubversionSourceControlRevision, ESPMode::ThreadSafe> > History;` — History of the item, if any
- L105 _public member_ `FString LocalFilename;` — Filename on disk
- L108 _public member_ `int LocalRevNumber;` — Revision number currently synced
- L111 _public member_ `FResolveInfo PendingResolveInfo;` — Pending rev info with which a file must be resolved, invalid if no resolve pending
- L114 _public member_ `int PendingMergeBaseFileRevNumber;` — `UE_DEPRECATED(5.3, "Use PendingResolveInfo.BaseRevisionNumber instead")`
- L117 _public member_ `bool bNewerVersionOnServer;` — Whether a newer version exists on the server
- L120 _public member_ `EWorkingCopyState::Type WorkingCopyState;` — State of the working copy
- L123 _public member_ `ELockState::Type LockState;` — Lock state
- L126 _public member_ `FString LockUser;` — Name of other user who has file locked
- L129 _public member_ `FDateTime TimeStamp;` — The timestamp of the last update
- L132 _public member_ `bool bCopied;` — Flagged as a copy/branch

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace EWorkingCopyState`
- L32 _namespace_ `namespace ELockState`

### `Plugins/Developer/SubversionSourceControl/Source/SubversionSourceControl/Private/SubversionSourceControlUtils.h` (Private)


#### class `FSVNScopedTempFile`  
`class FSVNScopedTempFile`  
_L16-34_
- desc: Helper struct for maintaining temporary files for passing to commands
- L21 _public prototype_ `FSVNScopedTempFile(const FString& InText);` — Constructor - open & write string to temp file
- L23 _public prototype_ `FSVNScopedTempFile(const FText& InText);`
- L26 _public prototype_ `~FSVNScopedTempFile();` — Destructor - delete temp file
- L29 _public prototype_ `const FString& GetFilename() const;` — Get the filename of this temp file - empty if it failed to be created
- L33 _private member_ `FString Filename;` — The filename we are writing to

#### Free symbols / members of external scopes

- L40 _namespace_ `namespace SubversionSourceControlUtils`
- L57 _prototype_ `bool RunCommand(const FString& InCommand, const TArray<FString>& InFiles, const TArray<FString>& InParameters, TArray<class FXmlFile>& OutXmlResults, TArray<FString>& OutErrorMessages, const FString& UserName, const FString& Password = FString());` (scope `SubversionSourceControlUtils`) — Run an svn command - output is either a string or an FXmlFile. @param	InCommand			The svn command - e.g. info @param	InFiles				The files to be operated on @param	InParameters		The parameters to the svn command @param	OutResults			The results (from StdOut) as an array per-line @param	OutXmlResults		The results output as XML, potentially from multiple commands @param	OutErrorMessages	Any errors (from StdErr) @param	UserName			The username too use with this command @param	Password			The password (if any) we should use when accessing svn. Note that the password is stored by the system after the first successful use. @returns true if the command succeeded and returned no errors - note some svn commands return 0 but output errors anyway!
- L58 _prototype_ `bool RunCommand(const FString& InCommand, const TArray<FString>& InFiles, const TArray<FString>& InParameters, TArray<FString>& OutResults, TArray<FString>& OutErrorMessages, const FString& UserName, const FString& Password = FString());` (scope `SubversionSourceControlUtils`)
- L73 _prototype_ `bool RunAtomicCommand(const FString& InCommand, const TArray<FString>& InFiles, const TArray<FString>& InParameters, TArray<FString>& OutResults, TArray<FString>& OutErrorMessages, const FString& UserName, const FString& Password = FString());` (scope `SubversionSourceControlUtils`) — Run an atomic svn command - don't split it into multiple commands if there are too many files, assert instead. @param	InCommand			The svn command - e.g. info @param	InFiles				The files to be operated on @param	InParameters		The parameters to the svn command @param	OutResults			The results (from StdOut) as an array per-line @param	OutErrorMessages	Any errors (from StdErr) @param	UserName			The username too use with this command @param	Password			The password (if any) we should use when accessing svn. Note that the password is stored by the system after the first successful use. @returns true if the command succeeded and returned no errors - note some svn commands return 0 but output errors anyway!
- L75 _typedef_ `typedef TMap<FString, TArray< TSharedRef<FSubversionSourceControlRevision, ESPMode::ThreadSafe> > > FHistoryOutput;` (scope `SubversionSourceControlUtils`)
- L80 _prototype_ `FString TranslateAction(const FString& InAction);` (scope `SubversionSourceControlUtils`) — Translate SVN action strings into actions that more closely resemble old-style Perforce actions.
- L85 _prototype_ `FDateTime GetDate(const FString& InDateString);` (scope `SubversionSourceControlUtils`) — Parse a date string as output from SVN commands.
- L90 _prototype_ `void ParseLogResults(const FString& InFilename, const TArray<FXmlFile>& ResultsXml, const FString& UserName, SubversionSourceControlUtils::FHistoryOutput& OutHistory);` (scope `SubversionSourceControlUtils`) — Parse the xml results of an 'svn log' command
- L95 _prototype_ `void ParseInfoResults(const TArray<FXmlFile>& ResultsXml, FString& OutWorkingCopyRoot, FString& OutRepoRoot);` (scope `SubversionSourceControlUtils`) — Parse the xml results of an 'svn info' command
- L100 _prototype_ `void ParseStatusResults(const TArray<FXmlFile>& ResultsXml, const TArray<FString>& InErrorMessages, const FString& InUserName, const FString& InWorkingCopyRoot, TArray<FSubversionSourceControlState>& OutStates);` (scope `SubversionSourceControlUtils`) — Parse the xml results of an 'svn status' command
- L106 _prototype_ `bool UpdateCachedStates(const TArray<FSubversionSourceControlState>& InStates);` (scope `SubversionSourceControlUtils`) — Helper function for various commands to update cached states. @returns true if any states were updated
- L111 _prototype_ `bool CheckFilename(const FString& InString);` (scope `SubversionSourceControlUtils`) — Checks a filename for 'Perforce-style' wildcards, as SVN does not support this.
- L116 _prototype_ `bool CheckFilenames(const TArray<FString>& InStrings);` (scope `SubversionSourceControlUtils`) — Checks filenames for 'Perforce-style' wildcards, as SVN does not support this.
- L122 _prototype_ `void RemoveRedundantErrors(FSubversionSourceControlCommand& InCommand, const FString& InFilter);` (scope `SubversionSourceControlUtils`) — Remove redundant errors (that contain a particular string) and also update the commands success status if all errors were removed.
- L127 _prototype_ `void QuoteFilename(FString& InString);` (scope `SubversionSourceControlUtils`) — Surround input filename with quotes, for sending to a command-line.
- L132 _prototype_ `void QuoteFilenames(TArray<FString>& InStrings);` (scope `SubversionSourceControlUtils`) — Surround input filenames with quotes, for sending to a command-line.
