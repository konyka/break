# Plugins / PerforceSourceControl

- module root: `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl`
- headers: 18; symbols: 671
- symbol kinds: class=47, delegate=1, enum=5, enumerator=22, function=67, member=165, namespace=2, prototype=356, struct=2, typedef=4
- PrivateDependencyModuleNames: Core, CoreUObject, InputCore, Slate, SlateCore, SourceControl, TypedElementFramework

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/IPerforceSourceControlWorker.h` (Private)


#### class `IPerforceSourceControlWorker`  
`class IPerforceSourceControlWorker`  
_L9-48_
- L12 _public prototype_ `static void RegisterWorkers();`
- L13 _public prototype_ `static TSharedPtr<class IPerforceSourceControlWorker, ESPMode::ThreadSafe> CreateWorker(const FName& OperationName, FPerforceSourceControlProvider& SCCProvider);`
- L16 _public function_ `IPerforceSourceControlWorker(FPerforceSourceControlProvider& InSourceControlProvider) : SourceControlProvider(InSourceControlProvider)`
- L22 _public prototype_ `virtual ~IPerforceSourceControlWorker() = default;`
- L27 _public prototype_ `virtual FName GetName() const = 0;` — Name describing the work that this worker does. Used for factory method hookup.
- L32 _public prototype_ `virtual bool Execute( class FPerforceSourceControlCommand& InCommand ) = 0;` — Function that actually does the work. Can be executed on another thread.
- L38 _public prototype_ `virtual bool UpdateStates() const = 0;` — Updates the state of any items after completion (if necessary). This is always executed on the main thread. @returns true if states were updated
- L40 _public function_ `FPerforceSourceControlProvider& GetSCCProvider() const`
- L47 _private member_ `FPerforceSourceControlProvider& SourceControlProvider;`

#### Free symbols / members of external scopes

- L50 _typedef_ `typedef TSharedRef<IPerforceSourceControlWorker, ESPMode::ThreadSafe> FPerforceSourceControlWorkerRef;`

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceConnection.h` (Private)


#### class `FP4Record`  
`class FP4Record : public TMap<FString, FString>`  
_L14-39_
- inherits: `TMap<FString,FString>`
- desc: A map containing result of running Perforce command
- L17 _public prototype_ `virtual ~FP4Record() = default;`
- L19 _public function_ `const FString& operator()(const FString& Key) const`
- L28 _public function_ `const FString& operator()(const TCHAR* Key) const`
- L38 _private member_ `static const FString EmptyStr;`

#### enum `EConnectionOptions`  
`enum class EConnectionOptions : uint8`  
_L44-52_
- desc: Options to be used with FPerforceConnection::EnsureValidConnection
- L47 _public enumerator_ `None = 0` — No options are applied
- L49 _public enumerator_ `WorkspaceOptional = 1 << 0` — The connection does not require a workspace to be considered valid
- L51 _public enumerator_ `SuppressErrorLogging = 1 << 1` — Errors will not be logged but will still be returned to the caller

#### enum `ERunCommandFlags`  
`enum class ERunCommandFlags : uint32`  
_L56-64_
- desc: Optional flags that can be passed in when a command is run
- L59 _public enumerator_ `Default = 0` — No special options selected
- L61 _public enumerator_ `DisableCommandLogging = 1 << 0` — Prevents us writing the full perforce command (once evaluated) to the log file
- L63 _public enumerator_ `Quiet = 1 << 1` — The same as passing -q to a perforce command as part of the g-opts. Prevents info output from being printed to stdout

#### class `FPerforceConnection`  
`class FPerforceConnection`  
_L67-205_
- L72 _public prototype_ `FPerforceConnection(const FPerforceConnectionInfo& InConnectionInfo, FPerforceSourceControlProvider& InSCCProvider, FSourceControlResultInfo* OutResultInfo);` — This constructor is strictly for internal questions to perforce (get client spec list, etc) When OutResultInfo is set, errors encountered will be added to it and when not set (nullptr) errors will be logged immediately
- L74 _public prototype_ `~FPerforceConnection();` — API Specific close of source control project
- L79 _public prototype_ `static bool AutoDetectWorkspace(const FPerforceConnectionInfo& InConnectionInfo, FPerforceSourceControlProvider& SCCProvider, FString& OutWorkspaceName, TArray<FText>& OutErrorMessages);` — Attempts to automatically detect the workspace to use based on the working directory
- L94 _public prototype_ `static bool EnsureValidConnection( const FPerforceConnectionInfo& InSettings, FPerforceSourceControlProvider& SCCProvider, EConnectionOptions Options, FPerforceConnectionInfo& OutSettings, ISourceControlProvider::FInitResult::FConnectionErrors& OutConnectionErrors);` — Set up a connection to the server with the given credentials. The function can attempt to autodetect missing credentials or fix incorrect ones with the final credentials being returned to the caller. @param InSettings			The initial connection credentials. @param SCCProvider			The provider that is setting up the connection. @param Options				Used to specialize initialization behavior, @see EConnectionOptions. @param OutSettings			The finalized connection credentials. If the connection failed then this will contain the credentials that were used for the step that failed. @param OutConnectionErrors	A collection of errors encountered. @return - True if a valid connection was established, otherwise false.
- L105 _public prototype_ `bool GetWorkspaces(const FPerforceConnectionInfo& InConnectionInfo, FOnIsCancelled InOnIsCancelled, TArray<FScWorkspaceInfo>& OutWorkspaceInfos, FSourceControlResultInfo& OutResultInfo);` — Get all Perforce workspaces for the current host @param InConnectionInfo	Connection credentials @param InOnIsCancelled	Delegate called to check for operation cancellation. @param OutWorkspaceInfos	Workspace infos output. @param OutErrorMessages	Any error messages output. @return - True if successful
- L115 _public prototype_ `bool GetProjectWorkspaces(const FPerforceConnectionInfo& InConnectionInfo, FOnIsCancelled InOnIsCancelled, TArray<FString>& OutWorkspaceNames, FSourceControlResultInfo& OutResultInfo);` — Get Perforce workspaces under which of the current project is located @param InConnectionInfo	Connection credentials @param InOnIsCancelled	Delegate called to check for operation cancellation. @param OutWorkspaceNames	Workspace names output. @param OutErrorMessages	Any error messages output. @return - True if successful
- L118 _public prototype_ `bool IsValidConnection();` — Returns true if connection is currently active
- L121 _public prototype_ `bool IsIgnored(const FString& InFile);` — Returns true if file is ignored through p4ignore
- L124 _public prototype_ `void Disconnect();` — If the connection is valid, disconnect from the server
- L127 _public prototype_ `double GetLatestCommuncationTime() const;` — Returns the platform time of the last time the connection successfully communicated with the server
- L132 _public function_ `bool RunCommand(const FString& InCommand, const TArray<FString>& InParameters, FP4RecordSet& OutRecordSet, FSourceControlResultInfo& OutResultInfo, FOnIsCancelled InIsCancelled, bool& OutConnectionDropped)` — Runs internal perforce command, catches exceptions, returns results
- L140 _public prototype_ `bool RunCommand(const FString& InCommand, const TArray<FString>& InParameters, FP4RecordSet& OutRecordSet, TArray<FSharedBuffer>* OutData, FSourceControlResultInfo& OutResultInfo, FOnIsCancelled InIsCancelled, bool& OutConnectionDropped, ERunCommandFlags RunFlags = ERunCommandFlags::Default);` — Runs internal perforce command, catches exceptions, returns results
- L145 _public prototype_ `int32 CreatePendingChangelist(const FText &Description, const TArray<FString>& InFiles, FOnIsCancelled InIsCancelled, FSourceControlResultInfo& OutResultInfo);` — Creates a changelist with the specified description
- L150 _public prototype_ `int32 EditPendingChangelist(const FText& NewDescription, int32 ChangelistNumber, FOnIsCancelled InIsCancelled, FSourceControlResultInfo& OutResultInfo);` — Edits a changelist with a new description
- L161 _public prototype_ `bool CreateWorkspace(FStringView WorkspaceSpec, FOnIsCancelled InIsCancelled, FSourceControlResultInfo& OutResultInfo);` — Creates a workspace based on the spec provided via the WorkspaceSpec. @param WorkspaceSpec		The specification of the workspace to create @param InIsCancelled		Delegate allowing the canceling of the command if needed @param OutResultInfo		Struct that will end up containing info and error messages for the operation @return Returns true if no errors were encountered, otherwise false
- L168 _public prototype_ `bool Login(const FPerforceConnectionInfo& InConnectionInfo);` — Attempt to login - some servers will require this @param	InConnectionInfo		Credentials to use @return true if successful
- L176 _public prototype_ `void EstablishConnection(const FPerforceConnectionInfo& InConnectionInfo, FSourceControlResultInfo* OutResultInfo);` — Make a valid connection if possible @param InConnectionInfo		Connection credentials @param OutResultInfo Optional structure to store errors encountered while establishing the connection. When set to nullptr, errors will be immediately logged.
- L183 _public prototype_ `FString GetUser();` — Return the user of the connection @return The current perforce user, this will be blank if the connect failed.
- L188 _public member_ `ClientApi P4Client;` — Perforce API client object
- L191 _public member_ `FString ClientRoot;` — The current root for the client workspace
- L194 _public member_ `bool bEstablishedConnection;` — true if connection was successfully established
- L197 _public member_ `bool bIsUnicode;` — Is this a connection to a unicode server?
- L200 _public member_ `double LatestCommunicateTime;` — A record of the last time the connection was used
- L204 _private member_ `FPerforceSourceControlProvider& SCCProvider;` — The source control provider that the connection is working from

#### class `FScopedPerforceConnection`  
`class FScopedPerforceConnection`  
_L210-255_
- desc: Connection that is used within specific scope
- L219 _public prototype_ `FScopedPerforceConnection( class FPerforceSourceControlCommand& InCommand);` — Constructor - establish a connection. The concurrency of the passed in command determines whether the persistent connection is used or another connection is established (connections cannot safely be used across different threads).
- L226 _public prototype_ `FScopedPerforceConnection( EConcurrency::Type InConcurrency, FPerforceSourceControlProvider& SCCProvider);` — Constructor - establish a connection. The concurrency passed in determines whether the persistent connection is used or another connection is established (connections cannot safely be used across different threads).
- L231 _public prototype_ `~FScopedPerforceConnection();` — Destructor - disconnect if this is a temporary connection
- L234 _public function_ `FPerforceConnection& GetConnection() const` — Get the connection wrapped by this class
- L240 _public function_ `bool IsValid() const` — Check if this connection is valid
- L247 _private prototype_ `void Initialize(const FPerforceConnectionInfo& InConnectionInfo, FPerforceSourceControlProvider& SCCProvider, FSourceControlResultInfo* OutResultInfo);` — Set up the connection
- L251 _private member_ `FPerforceConnection* Connection;` — The perforce connection we are using
- L254 _private member_ `EConcurrency::Type Concurrency;` — The concurrency of this connection

#### Free symbols / members of external scopes

- L41 _typedef_ `typedef TArray<FP4Record> FP4RecordSet;`
- L53 _prototype_ `ENUM_CLASS_FLAGS(EConnectionOptions);`
- L65 _prototype_ `ENUM_CLASS_FLAGS(ERunCommandFlags);`

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceConnectionInfo.h` (Private)


#### struct `FPerforceConnectionInfo`  
`struct FPerforceConnectionInfo`  
_L8-33_
- desc: Helper struct defining parameters we need to establish a connection
- L11 _public member_ `FString Port;` — The host and port for your Perforce server. Usage ServerName:1234
- L14 _public member_ `FString UserName;` — Perforce username
- L17 _public member_ `FString Workspace;` — Perforce workspace
- L20 _public member_ `FString HostOverride;` — Perforce host override - not usually set
- L23 _public member_ `FString Ticket;` — Ticket if in use
- L26 _public member_ `FString Password;` — Password if in use
- L29 _public member_ `FString ChangelistNumber;` — Changelist number
- L32 _public member_ `bool bUseP4Config = false;` — Use P4USER, P4PORT and P4CLIENT from P4 environment if set

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceMessageLog.h` (Private)


#### class `FTSMessageLog`  
`class FTSMessageLog`  
_L19-113_
- desc: A thread safe replacement for FMessageLog which can be called from background threads. It only exposes methods from FMessageLog that we would be able to safely delay, such as messages. We do not provide any functionality to open error dialogs etc. At the moment if we detect a message is being queued when not on the game thread we log it instead of sending to the FMessageLog system. In the future we will store the messages and marshal them to the GameThread so that they can be displayed as originally intended.
- L22 _public prototype_ `FTSMessageLog() = delete;`
- L23 _public function_ `FTSMessageLog(const FName& InLogName) : Log(InLogName)`
- L27 _public prototype_ `FTSMessageLog(FTSMessageLog&&) = default;`
- L28 _public prototype_ `FTSMessageLog& operator = (FTSMessageLog&&) = default;`
- L30 _public prototype_ `FTSMessageLog(const FTSMessageLog&) = delete;`
- L31 _public prototype_ `FTSMessageLog& operator = (const FTSMessageLog&) = delete;`
- L33 _public prototype_ `~FTSMessageLog() = default;`
- L35 _public function_ `TSharedRef<FTokenizedMessage> Message(EMessageSeverity::Type InSeverity, const FText& InMessage = FText())`
- L50 _public function_ `TSharedRef<FTokenizedMessage> Error(const FText& InMessage = FText())`
- L65 _public function_ `TSharedRef<FTokenizedMessage> PerformanceWarning(const FText& InMessage = FText())`
- L80 _public function_ `TSharedRef<FTokenizedMessage> Warning(const FText& InMessage = FText())`
- L95 _public function_ `TSharedRef<FTokenizedMessage> Info(const FText& InMessage = FText())`
- L112 _private member_ `FMessageLog Log;`

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceSourceControlChangelist.h` (Private)


#### class `FPerforceSourceControlChangelist`  
`class FPerforceSourceControlChangelist : public ISourceControlChangelist`  
_L8-76_
- inherits: `ISourceControlChangelist`
- L11 _public prototype_ `FPerforceSourceControlChangelist();`
- L13 _public function_ `explicit FPerforceSourceControlChangelist(int32 InChangelistNumber) : ChangelistNumber(InChangelistNumber) , bInitialized(true)`
- L19 _public function_ `virtual bool CanDelete() const override`
- L24 _public function_ `bool operator==(const FPerforceSourceControlChangelist& InOther) const`
- L29 _public function_ `bool operator!=(const FPerforceSourceControlChangelist& InOther) const`
- L34 _public function_ `virtual bool IsDefault() const override`
- L39 _public function_ `bool IsInitialized() const`
- L44 _public function_ `void Reset()`
- L55 _public function_ `FString ToString() const`
- L60 _public function_ `int32 ToInt() const`
- L65 _public function_ `virtual FString GetIdentifier() const override`
- L71 _public member_ `static const FPerforceSourceControlChangelist DefaultChangelist;`
- L74 _private member_ `int32 ChangelistNumber;`
- L75 _private member_ `bool bInitialized;`

#### Free symbols / members of external scopes

- L50 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FPerforceSourceControlChangelist& PerforceChangelist)`
- L78 _typedef_ `typedef TSharedRef<class FPerforceSourceControlChangelist, ESPMode::ThreadSafe> FPerforceSourceControlChangelistRef;`

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceSourceControlChangelistState.h` (Private)


#### class `FPerforceSourceControlChangelistState`  
`class FPerforceSourceControlChangelistState : public ISourceControlChangelistState`  
_L10-77_
- inherits: `ISourceControlChangelistState`
- L13 _public prototype_ `FPerforceSourceControlChangelistState(const FPerforceSourceControlChangelist& InChangelist);`
- L19 _public prototype_ `virtual FName GetIconName() const override;` — Get the name of the icon graphic we should use to display the state in a UI. @returns the name of the icon to display
- L25 _public prototype_ `virtual FName GetSmallIconName() const override;` — Get the name of the small icon graphic we should use to display the state in a UI. @returns the name of the icon to display
- L31 _public prototype_ `virtual FText GetDisplayText() const override;` — Get a text representation of the state @returns	the text to display for this state
- L37 _public prototype_ `virtual FText GetDescriptionText() const override;` — Get a text representation of the state @returns	the text to display for this state
- L44 _public function_ `virtual bool SupportsPersistentDescription() const override` — Returns whether the change list description can be saved and persisted. Some changelists are special and the description cannot be persisted with the changelist. For example the P4 default changelist description cannot be persisted and the user must create a new changelist.
- L50 _public prototype_ `virtual FText GetDisplayTooltip() const override;` — Get a tooltip to describe this state @returns	the text to display for this states tooltip
- L56 _public prototype_ `virtual const FDateTime& GetTimeStamp() const override;` — Get the timestamp of the last update that was made to this state. @returns	the timestamp of the last update
- L58 _public prototype_ `virtual const TArray<FSourceControlStateRef> GetFilesStates() const override;`
- L59 _public prototype_ `virtual int32 GetFilesStatesNum() const override;`
- L61 _public prototype_ `virtual const TArray<FSourceControlStateRef> GetShelvedFilesStates() const override;`
- L62 _public prototype_ `virtual int32 GetShelvedFilesStatesNum() const override;`
- L64 _public prototype_ `virtual FSourceControlChangelistRef GetChangelist() const override;`
- L67 _public member_ `FPerforceSourceControlChangelist Changelist;`
- L69 _public member_ `FString Description;`
- L70 _public member_ `bool bHasShelvedFiles;`
- L72 _public member_ `TArray<FSourceControlStateRef> Files;`
- L73 _public member_ `TMap<FString, FSourceControlStateRef> ShelvedFiles;`
- L76 _public member_ `FDateTime TimeStamp;` — The timestamp of the last update

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceSourceControlCommand.h` (Private)


#### class `FPerforceSourceControlCommand`  
`class FPerforceSourceControlCommand : public IQueuedWork`  
_L16-115_
- inherits: `IQueuedWork`
- desc: Used to execute Perforce commands multi-threaded.
- L20 _public prototype_ `FPerforceSourceControlCommand(const TSharedRef<class ISourceControlOperation, ESPMode::ThreadSafe>& InOperation, const TSharedRef<class IPerforceSourceControlWorker, ESPMode::ThreadSafe>& InWorker, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() );`
- L26 _public prototype_ `bool DoWork();` — This is where the real thread work is done. All work that is done for this queued object should be done from within the call to this function.
- L34 _public prototype_ `virtual void Abandon() override;` — Tells the queued work that it is being abandoned so that it can do per object clean up as needed. This will only be called if it is being abandoned before completion. NOTE: This requires the object to delete itself using whatever heap it was allocated in.
- L40 _public prototype_ `virtual void DoThreadedWork() override;` — This method is also used to tell the object to cleanup but not before the object has finished it's work.
- L43 _public prototype_ `void Cancel();` — Attempt to cancel the operation
- L46 _public prototype_ `void MarkConnectionAsSuccessful();` — Mark the connection to the server as successful
- L49 _public prototype_ `void CancelWhileTryingToConnect();` — Mark as canceled while trying to connect
- L52 _public prototype_ `bool IsCanceled() const;` — Is the operation canceled?
- L55 _public prototype_ `bool WasConnectionSuccessful() const;` — Was the connection to the server successful?
- L58 _public prototype_ `bool WasCanceledWhileTryingToConnect() const;` — Was the operation canceled while trying to connect?
- L61 _public prototype_ `ECommandResult::Type ReturnResults();` — Save any results and call any registered callbacks.
- L65 _public member_ `FPerforceConnectionInfo ConnectionInfo;` — Connection parameters, reproduced here because if is not safe to access the provider's settings from another thread
- L68 _public member_ `TSharedRef<class ISourceControlOperation, ESPMode::ThreadSafe> Operation;` — Operation we want to perform - contains outward-facing parameters & results
- L71 _public member_ `TSharedRef<class IPerforceSourceControlWorker, ESPMode::ThreadSafe> Worker;` — The object that will actually do the work
- L74 _public member_ `FSourceControlOperationComplete OperationCompleteDelegate;` — Delegate to notify when this operation completes
- L77 _public member_ `volatile int32 bExecuteProcessed;` — If true, this command has been processed by the source control thread
- L80 _public member_ `volatile int32 bCancelled;` — If true, this command has been cancelled
- L83 _public member_ `volatile int32 bConnectionWasSuccessful;` — If true, the source control connection was made successfully
- L86 _public member_ `volatile int32 bCancelledWhileTryingToConnect;` — If true, this command was cancelled while trying to connect
- L89 _public member_ `bool bCommandSuccessful;` — If true, the source control command succeeded
- L92 _public member_ `bool bConnectionDropped;` — If true, the source control connection was dropped while this command was being executed
- L95 _public member_ `bool bAutoDelete;` — If true, this command will be automatically cleaned up in Tick()
- L98 _public member_ `EConcurrency::Type Concurrency;` — Whether we are running multi-treaded or not
- L101 _public member_ `TArray< FString > Files;` — Files to perform this operation on
- L104 _public member_ `FPerforceSourceControlChangelist Changelist;` — Changelist to perform this operation on
- L107 _public member_ `FSourceControlResultInfo ResultInfo;` — Potential error, warning and info message storage
- L110 _public member_ `TArray< FString > StatusBranchNames;` — Branch names for status queries
- L113 _public member_ `TArray<FString> ContentRoots;` — Content roots for branch mapping

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnIsCancelled);`
- L11 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnIsCancelled);`

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceSourceControlInternalOperations.h` (Private)


#### class `FGetProjectWorkspaces`  
`class FGetProjectWorkspaces : public FSourceControlOperationBase`  
_L18-30_
- inherits: `FSourceControlOperationBase`
- L22 _public function_ `virtual FName GetName() const override` — ISourceControlOperation interface
- L29 _public member_ `TArray<FString> Results;` — Results are just an array of workspaces

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceSourceControlLabel.h` (Private)


#### class `FPerforceSourceControlLabel`  
`class FPerforceSourceControlLabel : public ISourceControlLabel`  
_L14-39_
- inherits: `ISourceControlLabel`
- desc: Abstraction of a Perforce label.
- L18 _public prototype_ `FPerforceSourceControlLabel(FPerforceSourceControlProvider& InSCCProvider, const FString& InName);`
- L19 _public prototype_ `virtual ~FPerforceSourceControlLabel() = default;`
- L22 _public prototype_ `virtual const FString& GetName() const override;` — ISourceControlLabel implementation
- L23 _public prototype_ `virtual bool GetFileRevisions( const TArray<FString>& InFiles, TArray< TSharedRef<ISourceControlRevision, ESPMode::ThreadSafe> >& OutRevisions ) const override;`
- L24 _public prototype_ `virtual bool Sync( const TArray<FString>& InFilenames ) const override;`
- L29 _private function_ `FPerforceSourceControlProvider& GetSCCProvider() const` — Internal accessor to the source control provider associated with the object
- L35 _private member_ `FPerforceSourceControlProvider& SCCProvider;` — The source control provider that this object is associated with
- L38 _private member_ `FString Name;` — Label name

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceSourceControlModule.h` (Private)


#### class `FPerforceSourceControlModule`  
`class FPerforceSourceControlModule : public IModuleInterface`  
_L10-20_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private member_ `FPerforceSourceControlProvider PerforceSourceControlProvider;` — The perforce source control provider that will be used by default via ISourceControlModule::Get().GetProvider() etc

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceSourceControlOperations.h` (Private)


#### class `FPerforceConnectWorker`  
`class FPerforceConnectWorker final : public IPerforceSourceControlWorker`  
_L14-26_
- inherits: `IPerforceSourceControlWorker`
- L17 _public function_ `FPerforceConnectWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L20 _public prototype_ `virtual ~FPerforceConnectWorker() = default;`
- L23 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L24 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L25 _public prototype_ `virtual bool UpdateStates() const override;`

#### class `FPerforceCheckOutWorker`  
`class FPerforceCheckOutWorker final : public IPerforceSourceControlWorker`  
_L28-46_
- inherits: `IPerforceSourceControlWorker`
- L31 _public function_ `FPerforceCheckOutWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider) , InChangelist(FPerforceSourceControlChangelist::DefaultChangelist)`
- L35 _public prototype_ `virtual ~FPerforceCheckOutWorker() = default;`
- L38 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L39 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L40 _public prototype_ `virtual bool UpdateStates() const override;`
- L44 _public member_ `TMap<FString, EPerforceState::Type> OutResults;` — Map of filenames to perforce state
- L45 _public member_ `FPerforceSourceControlChangelist InChangelist;`

#### class `FPerforceCheckInWorker`  
`class FPerforceCheckInWorker final : public IPerforceSourceControlWorker`  
_L48-73_
- inherits: `IPerforceSourceControlWorker`
- L51 _public function_ `FPerforceCheckInWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L54 _public prototype_ `virtual ~FPerforceCheckInWorker() = default;`
- L57 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L58 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L59 _public prototype_ `virtual bool UpdateStates() const override;`
- L63 _public member_ `TMap<FString, EPerforceState::Type> OutResults;` — Map of filenames to perforce state
- L66 _public member_ `FPerforceSourceControlChangelist InChangelist;` — Changelist we asked to submit
- L69 _public member_ `FPerforceSourceControlChangelist OutChangelist;` — Changelist we submitted
- L72 _public member_ `TMap<FString, EPerforceState::Type> FilesToKeepCheckedOut;` — List of file to kept in checked out after the submit.

#### class `FPerforceGetFileListWorker`  
`class FPerforceGetFileListWorker final : public IPerforceSourceControlWorker`  
_L75-91_
- inherits: `IPerforceSourceControlWorker`
- L78 _public function_ `FPerforceGetFileListWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L81 _public prototype_ `virtual ~FPerforceGetFileListWorker() = default;`
- L84 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L85 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L86 _public prototype_ `virtual bool UpdateStates() const override;`
- L90 _public member_ `TMap<FString, EPerforceState::Type> OutResults;` — Map of filenames to perforce state

#### class `FPerforceMarkForAddWorker`  
`class FPerforceMarkForAddWorker final : public IPerforceSourceControlWorker`  
_L93-111_
- inherits: `IPerforceSourceControlWorker`
- L96 _public function_ `FPerforceMarkForAddWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider) , InChangelist(FPerforceSourceControlChangelist::DefaultChangelist)`
- L100 _public prototype_ `virtual ~FPerforceMarkForAddWorker() = default;`
- L103 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L104 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L105 _public prototype_ `virtual bool UpdateStates() const override;`
- L109 _public member_ `TMap<FString, EPerforceState::Type> OutResults;` — Map of filenames to perforce state
- L110 _public member_ `FPerforceSourceControlChangelist InChangelist;`

#### class `FPerforceDeleteWorker`  
`class FPerforceDeleteWorker final : public IPerforceSourceControlWorker`  
_L113-131_
- inherits: `IPerforceSourceControlWorker`
- L116 _public function_ `FPerforceDeleteWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider) , Changelist(FPerforceSourceControlChangelist::DefaultChangelist)`
- L120 _public prototype_ `virtual ~FPerforceDeleteWorker() = default;`
- L123 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L124 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L125 _public prototype_ `virtual bool UpdateStates() const override;`
- L129 _public member_ `TMap<FString, EPerforceState::Type> OutResults;` — Map of filenames to perforce state
- L130 _public member_ `FPerforceSourceControlChangelist Changelist;`

#### class `FPerforceRevertWorker`  
`class FPerforceRevertWorker final : public IPerforceSourceControlWorker`  
_L133-152_
- inherits: `IPerforceSourceControlWorker`
- L136 _public function_ `FPerforceRevertWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L139 _public prototype_ `virtual ~FPerforceRevertWorker() = default;`
- L142 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L143 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L144 _public prototype_ `virtual bool UpdateStates() const override;`
- L148 _public member_ `TMap<FString, EPerforceState::Type> OutResults;` — Map of filenames to perforce state
- L151 _public member_ `FPerforceSourceControlChangelist ChangelistToUpdate;` — Changelist to be udpated

#### class `FPerforceSyncWorker`  
`class FPerforceSyncWorker final : public IPerforceSourceControlWorker`  
_L154-170_
- inherits: `IPerforceSourceControlWorker`
- L157 _public function_ `FPerforceSyncWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L160 _public prototype_ `virtual ~FPerforceSyncWorker() = default;`
- L163 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L164 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L165 _public prototype_ `virtual bool UpdateStates() const override;`
- L169 _public member_ `TMap<FString, EPerforceState::Type> OutResults;` — Map of filenames to perforce state

#### class `FPerforceUpdateStatusWorker`  
`class FPerforceUpdateStatusWorker final : public IPerforceSourceControlWorker`  
_L172-200_
- inherits: `IPerforceSourceControlWorker`
- L175 _public function_ `FPerforceUpdateStatusWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L178 _public prototype_ `virtual ~FPerforceUpdateStatusWorker() = default;`
- L181 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L182 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L183 _public prototype_ `virtual bool UpdateStates() const override;`
- L187 _public member_ `TArray<FPerforceSourceControlState> OutStates;` — Temporary states for results
- L190 _public member_ `TMap<FString, EPerforceState::Type> OutStateMap;` — Map of filename->state
- L193 _public member_ `FPerforceFileHistoryMap OutHistory;` — Map of filenames to history
- L196 _public member_ `TArray<FString> OutModifiedFiles;` — Map of filenames to modified flag
- L199 _public member_ `bool bForceQuiet = false;` — Override on status update return

#### class `FPerforceGetWorkspacesWorker`  
`class FPerforceGetWorkspacesWorker final : public IPerforceSourceControlWorker`  
_L202-214_
- inherits: `IPerforceSourceControlWorker`
- L205 _public function_ `FPerforceGetWorkspacesWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L208 _public prototype_ `virtual ~FPerforceGetWorkspacesWorker() = default;`
- L211 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L212 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L213 _public prototype_ `virtual bool UpdateStates() const override;`

#### class `FPerforceGetProjectWorkspacesWorker`  
`class FPerforceGetProjectWorkspacesWorker final : public IPerforceSourceControlWorker`  
_L216-228_
- inherits: `IPerforceSourceControlWorker`
- L219 _public function_ `FPerforceGetProjectWorkspacesWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L222 _public prototype_ `virtual ~FPerforceGetProjectWorkspacesWorker() = default;`
- L225 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L226 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L227 _public prototype_ `virtual bool UpdateStates() const override;`

#### class `FPerforceGetPendingChangelistsWorker`  
`class FPerforceGetPendingChangelistsWorker final : public IPerforceSourceControlWorker`  
_L230-253_
- inherits: `IPerforceSourceControlWorker`
- L233 _public function_ `FPerforceGetPendingChangelistsWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L236 _public prototype_ `virtual ~FPerforceGetPendingChangelistsWorker() = default;`
- L239 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L240 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L241 _public prototype_ `virtual bool UpdateStates() const override;`
- L245 _public member_ `TArray<FPerforceSourceControlChangelistState> OutChangelistsStates;` — Temporary states for results
- L246 _public member_ `TArray<TArray<FPerforceSourceControlState>> OutCLFilesStates;`
- L247 _public member_ `TArray<TMap<FString, EPerforceState::Type>> OutCLShelvedFilesStates;`
- L248 _public member_ `TArray<TMap<FString, FString>> OutCLShelvedFilesMap;`
- L252 _private member_ `bool bCleanupCache = false;` — Controls whether or not we will remove changelists from the cache after a full update

#### class `FPerforceCopyWorker`  
`class FPerforceCopyWorker final : public IPerforceSourceControlWorker`  
_L255-271_
- inherits: `IPerforceSourceControlWorker`
- L258 _public function_ `FPerforceCopyWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L261 _public prototype_ `virtual ~FPerforceCopyWorker() = default;`
- L264 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L265 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L266 _public prototype_ `virtual bool UpdateStates() const override;`
- L270 _public member_ `TMap<FString, EPerforceState::Type> OutResults;` — Map of filenames to perforce state

#### class `FPerforceResolveWorker`  
`class FPerforceResolveWorker final : public IPerforceSourceControlWorker`  
_L273-287_
- inherits: `IPerforceSourceControlWorker`
- L276 _public function_ `FPerforceResolveWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L280 _public prototype_ `virtual ~FPerforceResolveWorker() = default;`
- L282 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L283 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L284 _public prototype_ `virtual bool UpdateStates() const override;`
- L286 _private member_ `TArray< FString > UpdatedFiles;`

#### class `FPerforceChangeStatusWorker`  
`class FPerforceChangeStatusWorker final : public IPerforceSourceControlWorker`  
_L289-301_
- inherits: `IPerforceSourceControlWorker`
- L292 _public function_ `FPerforceChangeStatusWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L295 _public prototype_ `virtual ~FPerforceChangeStatusWorker() = default;`
- L298 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L299 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L300 _public prototype_ `virtual bool UpdateStates() const override;`

#### class `FPerforceNewChangelistWorker`  
`class FPerforceNewChangelistWorker final : public IPerforceSourceControlWorker`  
_L303-321_
- inherits: `IPerforceSourceControlWorker`
- L306 _public prototype_ `FPerforceNewChangelistWorker(FPerforceSourceControlProvider& InSourceControlProvider);`
- L307 _public prototype_ `virtual ~FPerforceNewChangelistWorker() = default;`
- L310 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L311 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L312 _public prototype_ `virtual bool UpdateStates() const override;`
- L316 _public member_ `FPerforceSourceControlChangelist NewChangelist;` — New changelist information
- L317 _public member_ `FPerforceSourceControlChangelistState NewChangelistState;`
- L320 _public member_ `TArray<FString> MovedFiles;` — Files that were moved

#### class `FPerforceDeleteChangelistWorker`  
`class FPerforceDeleteChangelistWorker final : public IPerforceSourceControlWorker`  
_L323-338_
- inherits: `IPerforceSourceControlWorker`
- L326 _public function_ `FPerforceDeleteChangelistWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L329 _public prototype_ `virtual ~FPerforceDeleteChangelistWorker() = default;`
- L332 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L333 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L334 _public prototype_ `virtual bool UpdateStates() const override;`
- L337 _public member_ `FPerforceSourceControlChangelist DeletedChangelist;`

#### class `FPerforceEditChangelistWorker`  
`class FPerforceEditChangelistWorker final : public IPerforceSourceControlWorker`  
_L340-356_
- inherits: `IPerforceSourceControlWorker`
- L343 _public function_ `FPerforceEditChangelistWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L346 _public prototype_ `virtual ~FPerforceEditChangelistWorker() = default;`
- L349 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L350 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L351 _public prototype_ `virtual bool UpdateStates() const override;`
- L354 _public member_ `FPerforceSourceControlChangelist EditedChangelist;`
- L355 _public member_ `FText EditedDescription;`

#### class `FPerforceRevertUnchangedWorker`  
`class FPerforceRevertUnchangedWorker final : public IPerforceSourceControlWorker`  
_L358-376_
- inherits: `IPerforceSourceControlWorker`
- L361 _public function_ `FPerforceRevertUnchangedWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L364 _public prototype_ `virtual ~FPerforceRevertUnchangedWorker() = default;`
- L367 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L368 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L369 _public prototype_ `virtual bool UpdateStates() const override;`
- L372 _protected member_ `TMap<FString, EPerforceState::Type> OutResults;` — Map of filenames to perforce state
- L375 _protected member_ `FPerforceSourceControlChangelist ChangelistToUpdate;` — Changelist to be updated

#### class `FPerforceReopenWorker`  
`class FPerforceReopenWorker final : public IPerforceSourceControlWorker`  
_L378-397_
- inherits: `IPerforceSourceControlWorker`
- L381 _public function_ `FPerforceReopenWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L384 _public prototype_ `virtual ~FPerforceReopenWorker() = default;`
- L387 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L388 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L389 _public prototype_ `virtual bool UpdateStates() const override;`
- L393 _protected member_ `TArray<FString> ReopenedFiles;` — Reopened files
- L396 _protected member_ `FPerforceSourceControlChangelist DestinationChangelist;` — Destination changelist

#### class `FPerforceShelveWorker`  
`class FPerforceShelveWorker final : public IPerforceSourceControlWorker`  
_L399-428_
- inherits: `IPerforceSourceControlWorker`
- L402 _public function_ `FPerforceShelveWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L405 _public prototype_ `virtual ~FPerforceShelveWorker() = default;`
- L408 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L409 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L410 _public prototype_ `virtual bool UpdateStates() const override;`
- L414 _protected member_ `TMap<FString, EPerforceState::Type> OutResults;` — Map of filenames to perforce state
- L417 _protected member_ `TMap<FString, FString> OutFileMap;` — Map depot filenames to local file
- L420 _protected member_ `TArray<FString> MovedFiles;` — Reopened files
- L423 _protected member_ `FString ChangelistDescription;` — Changelist description if needed
- L426 _protected member_ `FPerforceSourceControlChangelist InChangelistToUpdate;` — Changelist(s) to be updated
- L427 _protected member_ `FPerforceSourceControlChangelist OutChangelistToUpdate;`

#### class `FPerforceDeleteShelveWorker`  
`class FPerforceDeleteShelveWorker final : public IPerforceSourceControlWorker`  
_L430-449_
- inherits: `IPerforceSourceControlWorker`
- L433 _public function_ `FPerforceDeleteShelveWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L436 _public prototype_ `virtual ~FPerforceDeleteShelveWorker() = default;`
- L439 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L440 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L441 _public prototype_ `virtual bool UpdateStates() const override;`
- L445 _protected member_ `TArray<FString> FilesToRemove;` — List of files to remove from shelved files in changelist state
- L448 _protected member_ `FPerforceSourceControlChangelist ChangelistToUpdate;` — Changelist to be updated

#### class `FPerforceUnshelveWorker`  
`class FPerforceUnshelveWorker : public IPerforceSourceControlWorker`  
_L451-470_
- inherits: `IPerforceSourceControlWorker`
- L454 _public function_ `FPerforceUnshelveWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L457 _public prototype_ `virtual ~FPerforceUnshelveWorker() = default;`
- L460 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L461 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L462 _public prototype_ `virtual bool UpdateStates() const override;`
- L466 _protected member_ `FPerforceSourceControlChangelist ChangelistToUpdate;` — Changelist to be updated
- L469 _protected member_ `TArray<FPerforceSourceControlState> ChangelistFilesStates;` — List of files states after update

#### class `FPerforceDownloadFileWorker`  
`class FPerforceDownloadFileWorker final : public IPerforceSourceControlWorker`  
_L472-484_
- inherits: `IPerforceSourceControlWorker`
- L475 _public function_ `FPerforceDownloadFileWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L478 _public prototype_ `virtual ~FPerforceDownloadFileWorker() = default;`
- L481 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L482 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L483 _public prototype_ `virtual bool UpdateStates() const override;`

#### class `FPerforceRevisionInfoWorker`  
`class FPerforceRevisionInfoWorker final : public IPerforceSourceControlWorker`  
_L486-498_
- inherits: `IPerforceSourceControlWorker`
- L489 _public function_ `FPerforceRevisionInfoWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L492 _public prototype_ `virtual ~FPerforceRevisionInfoWorker() = default;`
- L495 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L496 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L497 _public prototype_ `virtual bool UpdateStates() const override;`

#### class `FPerforceCreateWorkspaceWorker`  
`class FPerforceCreateWorkspaceWorker final : public IPerforceSourceControlWorker`  
_L500-515_
- inherits: `IPerforceSourceControlWorker`
- L503 _public function_ `FPerforceCreateWorkspaceWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L506 _public prototype_ `virtual ~FPerforceCreateWorkspaceWorker() = default;`
- L509 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L510 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L511 _public prototype_ `virtual bool UpdateStates() const override;`
- L514 _private prototype_ `void AddType(const class FCreateWorkspace& Operation, FStringBuilderBase& ClientDesc);`

#### class `FPerforceDeleteWorkspaceWorker`  
`class FPerforceDeleteWorkspaceWorker final : public IPerforceSourceControlWorker`  
_L517-529_
- inherits: `IPerforceSourceControlWorker`
- L520 _public function_ `FPerforceDeleteWorkspaceWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L523 _public prototype_ `virtual ~FPerforceDeleteWorkspaceWorker() = default;`
- L526 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L527 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L528 _public prototype_ `virtual bool UpdateStates() const override;`

#### class `FPerforceGetChangelistDetailsWorker`  
`class FPerforceGetChangelistDetailsWorker final : public IPerforceSourceControlWorker`  
_L531-543_
- inherits: `IPerforceSourceControlWorker`
- L534 _public function_ `FPerforceGetChangelistDetailsWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L537 _public prototype_ `virtual ~FPerforceGetChangelistDetailsWorker() = default;`
- L540 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L541 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L542 _public prototype_ `virtual bool UpdateStates() const override;`

#### class `FPerforceGetFileWorker`  
`class FPerforceGetFileWorker final : public IPerforceSourceControlWorker`  
_L545-557_
- inherits: `IPerforceSourceControlWorker`
- L548 _public function_ `FPerforceGetFileWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L551 _public prototype_ `virtual ~FPerforceGetFileWorker() = default;`
- L554 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L555 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L556 _public prototype_ `virtual bool UpdateStates() const override;`

#### class `FPerforceWhereWorker`  
`class FPerforceWhereWorker final : public IPerforceSourceControlWorker`  
_L559-571_
- inherits: `IPerforceSourceControlWorker`
- L562 _public function_ `FPerforceWhereWorker(FPerforceSourceControlProvider& InSourceControlProvider) : IPerforceSourceControlWorker(InSourceControlProvider)`
- L565 _public prototype_ `virtual ~FPerforceWhereWorker() = default;`
- L568 _public prototype_ `virtual FName GetName() const override;` — IPerforceSourceControlWorker interface
- L569 _public prototype_ `virtual bool Execute(FPerforceSourceControlCommand& InCommand) override;`
- L570 _public prototype_ `virtual bool UpdateStates() const override;`

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef TMap<FString, TArray< TSharedRef<FPerforceSourceControlRevision, ESPMode::ThreadSafe> > > FPerforceFileHistoryMap;`

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceSourceControlPrivate.h` (Private)
_(no declarations extracted)_

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceSourceControlProvider.h` (Private)


#### class `FPerforceSourceControlProvider`  
`class FPerforceSourceControlProvider : public ISourceControlProvider`  
_L21-221_
- inherits: `ISourceControlProvider`
- L25 _public prototype_ `FPerforceSourceControlProvider();`
- L26 _public prototype_ `FPerforceSourceControlProvider(const FStringView& OwnerName, const FSourceControlInitSettings& InitialSettings);`
- L27 _public prototype_ `virtual ~FPerforceSourceControlProvider() = default;`
- L30 _public prototype_ `virtual void Init(bool bForceConnection = true) override;` — ISourceControlProvider implementation
- L31 _public prototype_ `virtual FInitResult Init(EInitFlags Flags) override;`
- L32 _public prototype_ `virtual void Close() override;`
- L33 _public prototype_ `virtual FText GetStatusText() const override;`
- L34 _public prototype_ `virtual TMap<EStatus, FString> GetStatus() const override;`
- L35 _public prototype_ `virtual bool IsEnabled() const override;`
- L36 _public prototype_ `virtual bool IsAvailable() const override;`
- L37 _public prototype_ `virtual const FName& GetName(void) const override;`
- L38 _public prototype_ `virtual bool QueryStateBranchConfig(const FString& ConfigSrc, const FString& ConfigDest) override;`
- L39 _public prototype_ `virtual void RegisterStateBranches(const TArray<FString>& BranchNames, const FString& ContentRootIn) override;`
- L40 _public prototype_ `virtual void RegisterStateBranches(const TArray<FString>& BranchNames, const TArray<FString>& ContentRootsIn) override;`
- L41 _public prototype_ `virtual int32 GetStateBranchIndex(const FString& BranchName) const override;`
- L42 _public prototype_ `virtual bool GetStateBranchAtIndex(int32 BranchIndex, FString& OutBranchName) const override;`
- L43 _public prototype_ `virtual ECommandResult::Type GetState( const TArray<FString>& InFiles, TArray<FSourceControlStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage ) override;`
- L44 _public prototype_ `virtual ECommandResult::Type GetState(const TArray<FSourceControlChangelistRef>& InChangelists, TArray<FSourceControlChangelistStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage) override;`
- L45 _public prototype_ `virtual TArray<FSourceControlStateRef> GetCachedStateByPredicate(TFunctionRef<bool(const FSourceControlStateRef&)> Predicate) const override;`
- L46 _public prototype_ `virtual FDelegateHandle RegisterSourceControlStateChanged_Handle( const FSourceControlStateChanged::FDelegate& SourceControlStateChanged ) override;`
- L47 _public prototype_ `virtual void UnregisterSourceControlStateChanged_Handle( FDelegateHandle Handle ) override;`
- L48 _public prototype_ `virtual ECommandResult::Type Execute( const FSourceControlOperationRef& InOperation, FSourceControlChangelistPtr InChangelist, const TArray<FString>& InFiles, EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() ) override;`
- L49 _public prototype_ `virtual bool CanExecuteOperation( const FSourceControlOperationRef& InOperation ) const override;`
- L50 _public prototype_ `virtual bool CanCancelOperation( const FSourceControlOperationRef& InOperation ) const override;`
- L51 _public prototype_ `virtual void CancelOperation( const FSourceControlOperationRef& InOperation ) override;`
- L52 _public prototype_ `virtual bool UsesLocalReadOnlyState() const override;`
- L53 _public prototype_ `virtual bool UsesChangelists() const override;`
- L54 _public prototype_ `virtual bool UsesUncontrolledChangelists() const override;`
- L55 _public prototype_ `virtual bool UsesCheckout() const override;`
- L56 _public prototype_ `virtual bool UsesFileRevisions() const override;`
- L57 _public prototype_ `virtual bool UsesSnapshots() const override;`
- L58 _public prototype_ `virtual bool UsesSoftRevertOnDelete() const override;`
- L59 _public prototype_ `virtual bool AllowsDiffAgainstDepot() const override;`
- L60 _public prototype_ `virtual TOptional<bool> HasChangesToSync() const override;`
- L61 _public prototype_ `virtual TOptional<bool> HasChangesToCheckIn() const override;`
- L62 _public prototype_ `virtual void Tick() override;`
- L63 _public prototype_ `virtual TArray< TSharedRef<class ISourceControlLabel> > GetLabels( const FString& InMatchingSpec ) const override;`
- L64 _public prototype_ `virtual TArray<FSourceControlChangelistRef> GetChangelists( EStateCacheUsage::Type InStateCacheUsage ) override;`
- L66 _public prototype_ `virtual bool TryToDownloadFileFromBackgroundThread(const TSharedRef<class FDownloadFile>& InOperation, const TArray<FString>& InFiles) override;`
- L67 _public prototype_ `virtual ECommandResult::Type SwitchWorkspace(FStringView NewWorkspaceName, FSourceControlResultInfo& OutResultInfo, FString* OutOldWorkspaceName) override;`
- L70 _public prototype_ `virtual TSharedRef<class SWidget> MakeSettingsWidget() const override;`
- L76 _public prototype_ `const FString& GetTicket() const;` — Get the P4 ticket we will use for connections
- L79 _public prototype_ `const FString& GetOwnerName() const;` — Returns the name of the system that owns the provider
- L82 _public prototype_ `void SetLastErrors(const TArray<FText>& InErrors);` — Set list of error messages that occurred after last perforce command
- L85 _public prototype_ `bool IsLoginError() const;` — Did most recent command generate a login error
- L88 _public prototype_ `void SetIsWorkspaceValidForProject(const bool bInIsWorkspaceValidForProject);` — Sets whether or not the current workspace maps to the current project directory
- L91 _public prototype_ `TArray<FText> GetLastErrors() const;` — Get list of error messages that occurred after last perforce command
- L94 _public prototype_ `int32 GetNumLastErrors() const;` — Get number of error messages seen after running last perforce command
- L97 _public prototype_ `TSharedRef<FPerforceSourceControlState, ESPMode::ThreadSafe> GetStateInternal(const FString& InFilename);` — Helper function used to update state cache
- L100 _public prototype_ `TSharedRef<FPerforceSourceControlChangelistState, ESPMode::ThreadSafe> GetStateInternal(const FPerforceSourceControlChangelist& InChangelist);` — Helper function used to update changelists state cache
- L110 _public prototype_ `bool EstablishPersistentConnection(FSourceControlResultInfo* OutResultInfo);` — Connects to the source control server if the persistent connection is not already established. @param OutResultInfo Optional structure to store errors encountered while creating the connection. When set to nullptr, errors will be immediately logged. @return true if the connection is established or became established and false if the connection failed.
- L112 _public prototype_ `void ResetPersistentConnection();`
- L115 _public function_ `class FPerforceConnection* GetPersistentConnection()` — Get the persistent connection, if any
- L121 _public prototype_ `bool RemoveFileFromCache(const FString& Filename);` — Remove a named file from the state cache
- L124 _public prototype_ `bool RemoveChangelistFromCache(const FPerforceSourceControlChangelist& Changelist);` — Remove a changelist from the state cache
- L127 _public prototype_ `TArray<FSourceControlChangelistStateRef> GetCachedStateByPredicate(TFunctionRef<bool(const FSourceControlChangelistStateRef&)> Predicate) const;` — Returns a list of changelists from the cache based on a given predicate
- L130 _public prototype_ `const FPerforceSourceControlSettings& AccessSettings() const;` — Returns the settings for the current source control provider
- L133 _public prototype_ `FPerforceSourceControlSettings& AccessSettings();` — Returns the settings for the current source control provider
- L137 _private prototype_ `virtual TUniquePtr<ISourceControlProvider> Create(const FStringView& OwnerName, const FSourceControlInitSettings& InitialSettings) const override;` — Instantiates and returns a new FPerforceSourceControlProvider
- L139 _private prototype_ `void SaveConnectionSettings();`
- L142 _private prototype_ `TSharedPtr<class IPerforceSourceControlWorker, ESPMode::ThreadSafe> CreateWorker(const FName& InOperationName);` — Helper function used to create a worker for a particular operation
- L147 _private prototype_ `void OutputCommandMessages(const FPerforceSourceControlCommand& InCommand) const;` — Logs any messages that a command needs to output.
- L153 _private prototype_ `ISourceControlProvider::FInitResult ParseCommandLineSettings(EInitFlags Flags);` — Loads user/SCC information from the INI file and can attempt to make a connection to the server if requested by the Flags parameter.
- L160 _private prototype_ `ECommandResult::Type ExecuteSynchronousCommand(FPerforceSourceControlCommand& InCommand, const FText& Task, bool bSuppressResponseMsg);` — Helper function for running command 'synchronously'. This really doesn't execute synchronously; rather it adds the command to the queue & does not return until the command is completed.
- L165 _private prototype_ `ECommandResult::Type IssueCommand(FPerforceSourceControlCommand& InCommand, const bool bSynchronous);` — Run a command synchronously or asynchronously.
- L170 _private member_ `FPerforceSourceControlSettings PerforceSCCSettings;` — The settings for Perforce source control
- L173 _private member_ `FSourceControlInitSettings InitialSettings;` — The initial settings for the provider. These are used every time ::Init is called
- L176 _private member_ `FString OwnerName;` — Name of the system that owns the provider
- L179 _private member_ `FString Ticket;` — The ticket we use for login.
- L182 _private member_ `FString WorkspaceRoot;` — the root of the workspace we are currently using
- L185 _private member_ `bool bServerAvailable;` — Indicates if source control integration is available or not.
- L188 _private member_ `TAtomic<bool> bIsWorkspaceValidForProject;` — Whether or not the current workspace maps to the current project directory; this is true unless explicitly cleared
- L191 _private member_ `TAtomic<bool> bLoginError;` — Saw login error when running last command.
- L194 _private member_ `mutable FCriticalSection LastErrorsCriticalSection;` — Critical section for thread safety of error messages that occurred after last perforce command
- L197 _private member_ `TArray<FText> LastErrors;` — List of error messages that occurred after last perforce command
- L200 _private member_ `TUniquePtr<FPerforceConnection> PersistentConnection;` — A pointer to the persistent P4 connection for synchronous operations
- L203 _private member_ `TMap<FString, TSharedRef<class FPerforceSourceControlState, ESPMode::ThreadSafe> > StateCache;` — State cache
- L204 _private member_ `mutable FRWLock StateCacheLock;`
- L206 _private member_ `TMap<FPerforceSourceControlChangelist, TSharedRef<class FPerforceSourceControlChangelistState, ESPMode::ThreadSafe> > ChangelistsStateCache;`
- L207 _private member_ `mutable FRWLock ChangelistsStateCacheLock;`
- L210 _private member_ `TArray <FPerforceSourceControlCommand* > CommandQueue;` — Queue for commands given by the main thread
- L213 _private member_ `FSourceControlStateChanged OnSourceControlStateChanged;` — For notifying when the source control states in the cache have changed
- L216 _private member_ `TArray<FString> StatusBranchNames;` — Array of branch names for status queries
- L219 _private member_ `TArray<FString> ContentRoots;` — Content roots for branch status query mapping

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceSourceControlRevision.h` (Private)


#### class `FPerforceSourceControlRevision`  
`class FPerforceSourceControlRevision final : public ISourceControlRevision`  
_L12-84_
- inherits: `ISourceControlRevision`
- L16 _public prototype_ `FPerforceSourceControlRevision(FPerforceSourceControlProvider& InSCCProvider);`
- L17 _public prototype_ `virtual ~FPerforceSourceControlRevision() = default;`
- L19 _public prototype_ `bool Get(FString& InOutFilename, FPerforceConnection& InConnection) const;`
- L22 _public prototype_ `virtual bool Get( FString& InOutFilename, EConcurrency::Type InConcurrency = EConcurrency::Synchronous) const override;` — ISourceControlRevision interface
- L23 _public prototype_ `virtual bool GetAnnotated( TArray<FAnnotationLine>& OutLines ) const override;`
- L24 _public prototype_ `virtual bool GetAnnotated( FString& InOutFilename ) const override;`
- L25 _public prototype_ `virtual const FString& GetFilename() const override;`
- L26 _public prototype_ `virtual int32 GetRevisionNumber() const override;`
- L27 _public prototype_ `virtual const FString& GetRevision() const override;`
- L28 _public prototype_ `virtual const FString& GetDescription() const override;`
- L29 _public prototype_ `virtual const FString& GetUserName() const override;`
- L30 _public prototype_ `virtual const FString& GetClientSpec() const override;`
- L31 _public prototype_ `virtual const FString& GetAction() const override;`
- L32 _public prototype_ `virtual TSharedPtr<ISourceControlRevision, ESPMode::ThreadSafe> GetBranchSource() const override;`
- L33 _public prototype_ `virtual const FDateTime& GetDate() const override;`
- L34 _public prototype_ `virtual int32 GetCheckInIdentifier() const override;`
- L35 _public prototype_ `virtual int32 GetFileSize() const override;`
- L40 _public member_ `FString FileName;` — The local filename the this revision refers to
- L43 _public member_ `int32 RevisionNumber;` — The revision number of this file
- L46 _public member_ `FString Revision;` — The revision to display to the user
- L49 _public member_ `FString Description;` — The changelist description of this revision
- L52 _public member_ `FString UserName;` — THe user that made the change for this revision
- L55 _public member_ `FString ClientSpec;` — The workspace the change was made from
- L58 _public member_ `FString Action;` — The action (edit, add etc.) that was performed for at this revision
- L61 _public member_ `TSharedPtr<FPerforceSourceControlRevision, ESPMode::ThreadSafe> BranchSource;` — Source of branch, if any
- L64 _public member_ `FDateTime Date;` — The date of this revision
- L67 _public member_ `int32 ChangelistNumber;` — The changelist number of this revision
- L70 _public member_ `int32 FileSize;` — The size of the change
- L73 _public member_ `bool bIsShelve;` — Whether this reprensents a revision bound to a shelved file in a changelist
- L77 _private function_ `FPerforceSourceControlProvider& GetSCCProvider() const` — Internal accessor to the source control provider associated with the object
- L83 _private member_ `FPerforceSourceControlProvider& SCCProvider;` — The source control provider that this object is associated with

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceSourceControlSettings.h` (Private)


#### class `FPerforceSourceControlSettings`  
`class FPerforceSourceControlSettings`  
_L10-92_
- L13 _public prototype_ `FPerforceSourceControlSettings(const FPerforceSourceControlProvider& InSCCProvider, const FStringView& OwnerName);`
- L14 _public prototype_ `~FPerforceSourceControlSettings() = default;`
- L17 _public prototype_ `const FString& GetPort() const;` — Get the Perforce port
- L20 _public prototype_ `void SetPort(const FString& InString);` — Set the Perforce port
- L23 _public prototype_ `const FString& GetUserName() const;` — Get the Perforce username
- L26 _public prototype_ `void SetUserName(const FString& InString);` — Set the Perforce username
- L29 _public prototype_ `const FString& GetWorkspace() const;` — Get the Perforce workspace
- L32 _public prototype_ `void SetWorkspace(const FString& InString);` — Set the Perforce workspace
- L35 _public prototype_ `const FString& GetHostOverride() const;` — Get the Perforce host override
- L38 _public prototype_ `void SetHostOverride(const FString& InString);` — Set the Perforce host override
- L41 _public prototype_ `const FString& GetChangelistNumber() const;` — Get the perforce cl we should use for this run (useful in commandlets) returns empty string if there is no cl
- L43 _public prototype_ `void SetChangelistNumber(const FString& InString);`
- L46 _public prototype_ `bool GetUseP4Config() const;` — Import the P4USER, P4PORT, P4CLIENT from the P4 environment if set.
- L48 _public prototype_ `void SetUseP4Config(bool bInUseP4Config);`
- L51 _public prototype_ `void SetAllowSave(bool bFlag);` — When set to true the settings can be saved to an ini file, when false nothing will be saved
- L54 _public prototype_ `void SetAllowLoad(bool bFlag);` — When set to true the settings can be read from an ini file, when false nothing will be read
- L57 _public prototype_ `void LoadSettings();` — Load settings from ini file
- L60 _public prototype_ `void SaveSettings() const;` — Save settings to ini file
- L63 _public prototype_ `FPerforceConnectionInfo GetConnectionInfo() const;` — Get the credentials we use to access the server - only call on the game thread
- L67 _private prototype_ `void ImportP4Config();`
- L70 _private member_ `mutable FCriticalSection CriticalSection;` — A critical section for settings access
- L73 _private member_ `FPerforceConnectionInfo ConnectionInfo;` — The credentials we use to access the server
- L76 _private member_ `FString SettingsSection;` — The section of the ini file we load our settings from
- L79 _private function_ `const FPerforceSourceControlProvider& GetSCCProvider() const` — Internal accessor to the source control provider associated with the object
- L85 _private member_ `const FPerforceSourceControlProvider& SCCProvider;` — The source control provider that this object is associated with
- L88 _private member_ `bool bCanSaveToIniFile;` — Controls whether the settings can be saved to an ini file or not
- L91 _private member_ `bool bCanLoadFromIniFile;` — Controls whether the settings can be read from an ini file or not

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/PerforceSourceControlState.h` (Private)


#### enum `EPerforceState::Type`  
`enum Type`  
_L15-46_
- L18 _public enumerator_ `DontCare = 0` — Don't know or don't care.
- L21 _public enumerator_ `CheckedOut = 1` — File is checked out to current user.
- L24 _public enumerator_ `ReadOnly = 2` — File is not checked out (but IS controlled by the source control system).
- L27 _public enumerator_ `NotInDepot = 4` — File is new and not in the depot - needs to be added.
- L30 _public enumerator_ `CheckedOutOther = 5` — File is checked out by another user and cannot be checked out locally.
- L33 _public enumerator_ `Ignore = 6` — Certain packages are best ignored by the SCC system (MyLevel, Transient, etc).
- L36 _public enumerator_ `OpenForAdd = 7` — File is marked for add
- L39 _public enumerator_ `MarkedForDelete = 8` — File is marked for delete
- L42 _public enumerator_ `NotUnderClientRoot = 9` — Not under client root or in client view
- L45 _public enumerator_ `Branched = 10` — Opened for branch

#### class `FPerforceSourceControlState`  
`class FPerforceSourceControlState : public ISourceControlState`  
_L49-185_
- inherits: `ISourceControlState`
- L52 _public function_ `FPerforceSourceControlState( const FString& InLocalFilename, EPerforceState::Type InState = EPerforceState::DontCare ) : LocalFilename(InLocalFilename) , State(InState) , DepotRevNumber(INVALID_REVISION) , LocalRevNumber(INVALID_REVISION) , bModifed(false) , bBinary(false) , bExclusiveCheckout(false) , TimeStamp(0) , HeadModTime(0) , HeadChangeList(0)`
- L66 _public prototype_ `FPerforceSourceControlState();`
- L67 _public prototype_ `FPerforceSourceControlState(const FPerforceSourceControlState& Other);`
- L68 _public prototype_ `FPerforceSourceControlState(FPerforceSourceControlState&& Other) noexcept;`
- L69 _public prototype_ `FPerforceSourceControlState& operator=(const FPerforceSourceControlState& Other);`
- L70 _public prototype_ `FPerforceSourceControlState& operator=(FPerforceSourceControlState&& Other) noexcept;`
- L73 _public prototype_ `virtual int32 GetHistorySize() const override;` — ISourceControlState interface
- L74 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetHistoryItem( int32 HistoryIndex ) const override;`
- L75 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> FindHistoryRevision( int32 RevisionNumber ) const override;`
- L76 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> FindHistoryRevision( const FString& InRevision ) const override;`
- L77 _public prototype_ `virtual FResolveInfo GetResolveInfo() const override;`
- L78 _public prototype_ `virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetCurrentRevision() const override;`
- L80 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L82 _public prototype_ `virtual FText GetDisplayName() const override;`
- L83 _public prototype_ `virtual FText GetDisplayTooltip() const override;`
- L84 _public prototype_ `virtual const FString& GetFilename() const override;`
- L85 _public prototype_ `virtual const FDateTime& GetTimeStamp() const override;`
- L86 _public prototype_ `virtual bool CanCheckIn() const override;`
- L87 _public prototype_ `virtual bool CanCheckout() const override;`
- L88 _public prototype_ `virtual bool IsCheckedOut() const override;`
- L89 _public prototype_ `virtual bool IsCheckedOutOther(FString* Who = nullptr) const override;`
- L90 _public prototype_ `virtual bool IsCheckedOutInOtherBranch(const FString& CurrentBranch = FString()) const override;`
- L91 _public prototype_ `virtual bool IsModifiedInOtherBranch(const FString& CurrentBranch = FString()) const override;`
- L92 _public function_ `virtual bool IsCheckedOutOrModifiedInOtherBranch(const FString& CurrentBranch = FString()) const override`
- L93 _public function_ `virtual TArray<FString> GetCheckedOutBranches() const override`
- L94 _public function_ `virtual FString GetOtherUserBranchCheckedOuts() const override`
- L95 _public prototype_ `virtual bool GetOtherBranchHeadModification(FString& HeadBranchOut, FString& ActionOut, int32& HeadChangeListOut) const override;`
- L96 _public prototype_ `virtual FSourceControlChangelistPtr GetCheckInIdentifier() const override;`
- L97 _public prototype_ `virtual bool IsCurrent() const override;`
- L98 _public prototype_ `virtual bool IsSourceControlled() const override;`
- L99 _public prototype_ `virtual bool IsAdded() const override;`
- L100 _public prototype_ `virtual bool IsDeleted() const override;`
- L101 _public prototype_ `virtual bool IsIgnored() const override;`
- L102 _public prototype_ `virtual bool CanEdit() const override;`
- L103 _public prototype_ `virtual bool IsUnknown() const override;`
- L104 _public prototype_ `virtual bool IsModified() const override;`
- L105 _public prototype_ `virtual bool CanAdd() const override;`
- L106 _public prototype_ `virtual bool CanDelete() const override;`
- L107 _public prototype_ `virtual bool CanRevert() const override;`
- L110 _public function_ `EPerforceState::Type GetState() const` — Get the state of a file
- L116 _public function_ `void SetState( EPerforceState::Type InState )` — Set the state of the file
- L122 _public prototype_ `void Update(const FPerforceSourceControlState& InOther, const FDateTime* TimeStamp = nullptr);` — Fills in missing information from other state
- L126 _public member_ `TArray< TSharedRef<FPerforceSourceControlRevision, ESPMode::ThreadSafe> > History;` — History of the item, if any
- L129 _public member_ `FString LocalFilename;` — Filename on disk
- L132 _public member_ `FString DepotFilename;` — Filename in the Perforce depot
- L135 _public member_ `FString OtherUserCheckedOut;` — If another user has this file checked out, this contains their name(s). Multiple users are comma-delimited
- L138 _public member_ `EPerforceState::Type State;` — Status of the file
- L141 _public member_ `int DepotRevNumber;` — Latest revision number of the file in the depot
- L144 _public member_ `int LocalRevNumber;` — Latest rev number at which a file was synced to before being edited
- L147 _public member_ `FResolveInfo PendingResolveInfo;` — Pending rev info with which a file must be resolved, invalid if no resolve pending
- L150 _public member_ `int PendingResolveRevNumber;` — `UE_DEPRECATED(5.3, "Use PendingResolveInfo.BaseRevision instead")`
- L153 _public member_ `FPerforceSourceControlChangelist Changelist;` — Changelist containing this file
- L156 _public member_ `bool bModifed;` — Modified from depot version
- L159 _public member_ `bool bBinary;` — Whether the file is a binary file or not
- L162 _public member_ `bool bExclusiveCheckout;` — Whether the file is a marked for exclusive checkout or not
- L165 _public member_ `FDateTime TimeStamp;` — The timestamp of the last update
- L168 _public member_ `FString HeadBranch;` — The branch with the head change list
- L171 _public member_ `FString HeadAction;` — The action within the head branch
- L174 _public member_ `int64 HeadModTime;` — The last file modification time, note that P4 delete actions have a modification time of 0
- L177 _public member_ `int32 HeadChangeList;` — The change list the last modification
- L180 _public member_ `TArray<FString> CheckedOutBranches;` — Branches the file is checked out in
- L183 _public member_ `FString OtherUserBranchCheckedOuts;` — Amalgamated information of users who have file checked out in another branch

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace EPerforceState`

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Private/SPerforceSourceControlSettings.h` (Private)


#### enum `ESourceControlOperationState::Type`  
`enum Type`  
_L29-34_
- L31 _public enumerator_ `NotQueried`
- L32 _public enumerator_ `Querying`
- L33 _public enumerator_ `Queried`

#### class `SPerforceSourceControlSettings`  
`class SPerforceSourceControlSettings : public SCompoundWidget`  
_L37-154_
- inherits: `SCompoundWidget`
- L41 _public function_ `SLATE_BEGIN_ARGS(SPerforceSourceControlSettings)`
- L46 _public prototype_ `void Construct(const FArguments& InArgs, FPerforceSourceControlProvider* InSCCProvider);`
- L49 _public prototype_ `static FString GetPassword();` — Get the currently entered password
- L51 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime );`
- L55 _private prototype_ `void QueryWorkspaces();` — Fire off a source control operation to see what workspaces we have
- L58 _private prototype_ `ECheckBoxState IsP4ConfigChecked() const;` — Delegate to check if we should use P4 Config from settings
- L61 _private prototype_ `void OnP4ConfigCheckStatusChanged(ECheckBoxState NewState) const;` — Delegate to enable or disable P4 Config
- L64 _private prototype_ `bool IsP4ConfigDisabled() const;` — Delegate to enable Port, Username and input when P4 Config is not used
- L67 _private prototype_ `FText GetPortText() const;` — Delegate to get port text from settings
- L70 _private prototype_ `void OnPortTextCommitted(const FText& InText, ETextCommit::Type InCommitType) const;` — Delegate to commit port text to settings
- L73 _private prototype_ `FText GetUserNameText() const;` — Delegate to get user name text from settings
- L76 _private prototype_ `void OnUserNameTextCommitted(const FText& InText, ETextCommit::Type InCommitType) const;` — Delegate to commit user name text to settings
- L79 _private prototype_ `FText GetWorkspaceText() const;` — Delegate to get workspace text from settings
- L82 _private prototype_ `void OnWorkspaceTextCommitted(const FText& InText, ETextCommit::Type InCommitType) const;` — Delegate to commit workspace text to settings
- L85 _private prototype_ `FText GetHostText() const;` — Delegate to get host text from settings
- L88 _private prototype_ `void OnHostTextCommitted(const FText& InText, ETextCommit::Type InCommitType) const;` — Delegate to commit host text to settings
- L91 _private prototype_ `void OnSourceControlOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Delegate called when a source control operation has completed
- L94 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();` — Delegate for the auto workspaces dropdown menu content
- L97 _private prototype_ `EVisibility GetThrobberVisibility() const;` — Delegate controlling the visibility of the throbber
- L100 _private prototype_ `EVisibility GetNoWorkspacesVisibility() const;` — Delegate controlling the visibility 'no workspaces' message
- L103 _private prototype_ `EVisibility GetWorkspaceListVisibility() const;` — Delegate controlling the visibility of the workspace list
- L106 _private prototype_ `TSharedRef<class ITableRow> OnGenerateWorkspaceRow(TSharedRef<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Delegate to generate a row in the workspace list
- L109 _private prototype_ `void OnWorkspaceSelected(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectInfo);` — Delegate for when a workspace item is clicked
- L112 _private prototype_ `FText OnGetButtonText() const;` — Delegate for the auto workspaces dropdown button text
- L115 _private prototype_ `FReply OnCancelWorkspacesRequest() const;` — Delegate that cancels the workspace request in progress
- L118 _private prototype_ `const FSlateBrush* GetAdvancedPulldownImage() const;` — Get the image to display on the advanced pulldown
- L121 _private prototype_ `EVisibility GetAdvancedSettingsVisibility() const;` — Get the visibility of the advanced settings
- L124 _private prototype_ `FReply OnAdvancedSettingsClicked();` — Toggle advanced settings
- L126 _private prototype_ `FPerforceSourceControlProvider& GetSCCProvider() const;`
- L129 _private member_ `FPerforceSourceControlProvider* SCCProvider;`
- L132 _private member_ `ESourceControlOperationState::Type State;` — State of the source control operation
- L135 _private member_ `FString CurrentWorkspace;` — The currently selected workspace
- L138 _private member_ `TArray<TSharedRef<FString>> Workspaces;` — Workspaces we have received
- L141 _private member_ `TSharedPtr<SComboButton> WorkspaceCombo;` — The combo button use to display the workspaces
- L144 _private member_ `TSharedPtr<FGetProjectWorkspaces, ESPMode::ThreadSafe> GetWorkspacesOperation;` — The source control operation in progress
- L147 _private member_ `static TWeakPtr<SEditableTextBox> PasswordTextBox;` — Pointer to the password text box widget
- L150 _private member_ `TSharedPtr<SButton> ExpanderButton;` — Expander button for advanced settings
- L153 _private member_ `bool bAreAdvancedSettingsExpanded;` — Whether to expand advanced settings

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace ESourceControlOperationState`

### `Plugins/Developer/PerforceSourceControl/Source/PerforceSourceControl/Public/PerforceSourceControlChangeStatusOperation.h` (Public)


#### enum `EChangelistStatus`  
`enum class EChangelistStatus`  
_L8-13_
- L10 _public enumerator_ `Have`
- L11 _public enumerator_ `Need`
- L12 _public enumerator_ `Partial`

#### struct `FChangelistStatusEntry`  
`struct FChangelistStatusEntry`  
_L15-19_
- L17 _public member_ `FString ChangelistNumber;`
- L18 _public member_ `EChangelistStatus Status;`

#### class `FPerforceSourceControlChangeStatusOperation`  
`class FPerforceSourceControlChangeStatusOperation : public FSourceControlOperationBase`  
_L27-36_
- inherits: `FSourceControlOperationBase`
- desc: This operation wraps the p4 cstat command which returns a list of all changelists for a given path and whether they are synced (have), will need to be synced (need) or partially synced. As this is somewhat specific to Perforce it can only be used directly, it is not part of the shared operation interfaces in SourceControlOperations.h
- L30 _public prototype_ `virtual ~FPerforceSourceControlChangeStatusOperation() = default;`
- L32 _public function_ `virtual FName GetName() const override`
- L35 _public member_ `TArray<FChangelistStatusEntry> OutResults;` — Entries will be in the order they were reported in by perforce
