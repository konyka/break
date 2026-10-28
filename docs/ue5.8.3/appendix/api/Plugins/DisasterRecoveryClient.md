# Plugins / DisasterRecoveryClient

- module root: `Plugins/Developer/Concert/ConcertApp/DisasterRecoveryClient/Source/DisasterRecoveryClient`
- headers: 7; symbols: 227
- symbol kinds: class=13, delegate=4, enum=1, enumerator=5, function=22, member=86, namespace=2, prototype=91, struct=3
- PrivateDependencyModuleNames: Concert, ConcertClient, ConcertSharedSlate, ConcertSyncClient, ConcertSyncCore, ConcertTransport, DesktopPlatform, DirectoryWatcher, EditorFramework, EditorStyle, InputCore, Json, Serialization, Slate, SlateCore, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Developer/Concert/ConcertApp/DisasterRecoveryClient/Source/DisasterRecoveryClient/Private/DisasterRecoverySessionInfo.h` (Private)


#### enum `EDisasterRecoverySessionFlags`  
`enum class EDisasterRecoverySessionFlags : uint8`  
_L8-24_
- desc: Flags describing the type of recovery sessions.
- L11 _public enumerator_ `None = 0` — No flags.
- L14 _public enumerator_ `AbnormalTerminaison = 1 << 0` — The session was terminated abnormally.
- L17 _public enumerator_ `Imported = 1 << 1` — The session was imported.
- L20 _public enumerator_ `Recent = 1 << 2` — The session was processed and moved to the recent list.
- L23 _public enumerator_ `DebuggerAttached = 1 << 3` — Indicate if the debugger was attached when the session was created.

#### struct `FDisasterRecoverySession`  
`struct FDisasterRecoverySession`  
_L29-94_
- reflection: `USTRUCT()`
- desc: Information about a single session info.
- L35 _public member_ `FGuid RepositoryId;` — `UPROPERTY()` — The repository ID created on the server to store that session.
- L39 _public member_ `FString RepositoryRootDir;` — `UPROPERTY()` — The immediate parent directory containing this session repository.
- L43 _public member_ `FString SessionName;` — `UPROPERTY()` — The name of the session.
- L47 _public member_ `uint32 MountedByProcessId = 0;` — `UPROPERTY()` — The client that mounted that session repository.
- L51 _public member_ `uint32 ClientProcessId = 0;` — `UPROPERTY()` — The process ID of the client connected to the session (the session is live and recording transactions for this client process).
- L55 _public member_ `uint8 Flags = static_cast<uint8>(EDisasterRecoverySessionFlags::None);` — `UPROPERTY()` — Information about the session.
- L58 _public function_ `bool IsLive() const` — Returns true if the session is currently in-progress (i.e. the session is live and has a client)
- L61 _public function_ `bool IsRecent() const` — Returns true if the session was moved to the recent list.
- L64 _public function_ `bool IsImported() const` — Returns true if the session was imported for inspection. It can be from any project and likely not recoverable.
- L67 _public function_ `bool WasDebuggerAttached() const` — Returns true if the debugger was attached to this session.
- L70 _public function_ `bool WasAbnormallyTerminated() const` — Session was abnormally terminated
- L73 _public function_ `bool IsUnreviewedCrash() const` — Returns true if the session abnormally terminated and the user did not have the change to inspect/recover it.
- L76 _public function_ `bool IsMounted() const` — Returns true if this session repository is mounted (by any process).
- L79 _public function_ `bool operator==(const FDisasterRecoverySession& Other) const` — Compares if two recovery sessions are equals.
- L90 _public function_ `bool operator!=(const FDisasterRecoverySession& Other) const` — Compares if two recovery sessions are different.

#### struct `FDisasterRecoveryClientInfo`  
`struct FDisasterRecoveryClientInfo`  
_L98-109_
- reflection: `USTRUCT()`
- desc: Information about a disaster recovery client.
- L104 _public member_ `uint32 ClientProcessId = 0;` — `UPROPERTY()` — The client process ID.
- L108 _public member_ `FGuid ClientAppId;` — `UPROPERTY()` — The client app ID.

#### struct `FDisasterRecoveryInfo`  
`struct FDisasterRecoveryInfo`  
_L116-147_
- reflection: `USTRUCT()`
- desc: Hold the information for multiple disaster recovery sessions.
- L122 _public member_ `uint32 Revision = 0;` — `UPROPERTY()` — The revision number of the information. Updated everytime the recovery info file is written.
- L126 _public member_ `TArray<FDisasterRecoverySession> ActiveSessions;` — `UPROPERTY()` — The list of running/crashing/crashed sessions.
- L130 _public member_ `TArray<FDisasterRecoverySession> RecentSessions;` — `UPROPERTY()` — The list of recent sessions (rotated over time).
- L134 _public member_ `TArray<FDisasterRecoverySession> ImportedSessions;` — `UPROPERTY()` — The list of imported sessions (rotated over time).
- L138 _public member_ `TArray<FDisasterRecoverySession> PendingSessions;` — `UPROPERTY()` — The list of session being created, for which the repository was created and mounted, but the session not yet started.
- L142 _public member_ `TArray<FGuid> DiscardedRepositoryIds;` — `UPROPERTY()` — The list of session reporitories ID that are scheduled to be discarded, but kept around until the server confirms the deletion.
- L146 _public member_ `TArray<FDisasterRecoveryClientInfo> Clients;` — `UPROPERTY()` — The list of client currently executing (in different processes).

### `Plugins/Developer/Concert/ConcertApp/DisasterRecoveryClient/Source/DisasterRecoveryClient/Private/DisasterRecoverySessionManager.h` (Private)


#### class `FDisasterRecoverySessionManager`  
`class FDisasterRecoverySessionManager`  
_L26-182_
- desc: Monitors, creates, restores, imports and inspects disaster recovery sessions.
- L35 _public prototype_ `FDisasterRecoverySessionManager(const FString& InRole, TSharedPtr<IConcertSyncClient> InSyncClient);` — Construct the disaster recovery session manager. @param InRole The role as passed to Concert to identify the context in used. @param InSyncClient The disaster recovery sync client that will be used to connect to the server (Expected to be configured and started up) @note The manager resolves the Concert server corresponding the configured property UConcertClientConfig::DefaultServerURL.
- L38 _public prototype_ `~FDisasterRecoverySessionManager();` — Destruct the disaster recovery session manager.
- L46 _public prototype_ `TFuture<bool> HasRecoverableCandidates();` — Evaluates if at least one session is candidate to be recovered at boot time, so that the Recovery UI can be shown to the user. To be candidate, a session must not be mounted by another instance and must have at least one recoverable transactions. @return A future containing the result of the evaluation, true if a candidate exist, false otherwise. @note All evaluated candidates are locked by the process, preventing concurrent instances from loading/deleting the session.
- L53 _public function_ `const TArray<TSharedRef<FDisasterRecoverySession>>& GetSessions() const` — Get the latest known list of sessions currently tracked by the manager. The session list is subject to change when a session is created/deleted/updated by this process or a concurrent one. @return The current session list. @see OnSessionAdded(), OnSessionRemoved(), OnSessionUpdated().
- L56 _public function_ `FOnDisasterRecoverySessionAdded& OnSessionAdded()` — Invoked when a session is added to the session list.
- L59 _public function_ `FOnDisasterRecoverySessionRemoved& OnSessionRemoved()` — Invoked when a session is removed from the session list.
- L62 _public function_ `FOnDisasterRecoverySessionUpdated& OnSessionUpdated()` — Invoked when a session is updated.
- L69 _public prototype_ `TFuture<TVariant<TSharedPtr<FConcertActivityStream>, FText>> LoadSession(TSharedRef<FDisasterRecoverySession> Session);` — Load the specified session activities into an activity stream if the session repository is not already mounted by another process. @param Session The session to load. @return A future containing the activity stream if succeeded or an error message in case of failure.
- L78 _public prototype_ `TVariant<TSharedPtr<FDisasterRecoverySession>, FText> ImportSession(const FString& SessionInfoPathname);` — Import a session from a crash report for inspection. The function expects to find the 'SessionInfo.json' and 'Session.db' files and optionally the 'Transactions' and 'Packages' directory in the same folder. The function will recreate a repository for the session and copy the files. The session activities is not loaded until the user call LoadSession(). @param SessionInfoPathname Path to the 'SessionInfo.json' @return A pointer on the session if the session was imported or an error message in case of failure. @note OnSessionAdded() is invoked on successful import.
- L86 _public prototype_ `TFuture<TPair<bool, FText>> DiscardSession(const FDisasterRecoverySession& Session);` — Discard the specified session, deleting all its files. The session cannot be discarded if it repository is mounted by another process. @param The session to discard. @return True if the session was discarded, false and an error message if it failed. @note OnSessionRemoved() is invoked if the session is discarded successfully.
- L93 _public prototype_ `TFuture<TPair<bool, FText>> CreateAndJoinSession();` — Create a new session and join it. @return True if the session is created and joined successfully, false and an error message if an error occurred. @note OnSessionAdded() is invoked on successful creation.
- L102 _public prototype_ `TFuture<TPair<bool, FText>> RestoreAndJoinSession(TSharedPtr<FDisasterRecoverySession> ArchivedSession, TSharedPtr<FConcertSessionActivity> ThroughActivity);` — Create a new session from an archived session, up to a given point in time in that session. @param ArchivedSession The archived session to restore. @param ThroughActivity Restore the archived session activities up to this point in time (included). @return True if the session was discarded, false and an error message if it failed. @note OnSessionAdded() is invoked if the session is created and the original archived session remains unmodified.
- L105 _public prototype_ `void LeaveSession();` — Leave the current live session, if any. If is safe to call the function even if the user doesn't have a live session in progress.
- L108 _public prototype_ `bool HasInProgressSession() const;` — Check if the client has a live session in progress. This return true as soon as CreateAndJoinSession()/RestoreAndJoinSession() is called and returns false after LeaveSession() returns (or an error occurs provoking the user to not connect/disconnect).
- L111 _public prototype_ `void Refresh();` — Reload the recovery info file, update the session cache and fire delegates accordingly. This detects if a concurrent instance crashed (without updating the itself) and update the state accordingly.
- L115 _private prototype_ `TArray<FGuid> InitAndRotateSessions();` — Rotate and return the list of expired sessions.
- L118 _private prototype_ `void UpdateSessionsCache();` — Reload the recovery info file, update the cached sessions and notify the modifications.
- L121 _private prototype_ `TFuture<TPair<bool, FText>> DiscardRepositories(TArray<FGuid> RepositoryIds);` — Discard one or more session repositories. Discarding a repository is just like discarding the session because this manager always keeps one session per repository.
- L124 _private prototype_ `void OnRecoverySessionStartup(TSharedRef<IConcertClientSession> InSession);` — Invoked when a recovery session is created (from scratch or from a recovery).
- L127 _private prototype_ `void OnRecoverySessionShutdown(TSharedRef<IConcertClientSession> InSession);` — Invoked when a recovery session is shut down normally.
- L130 _private prototype_ `void OnSessionNotFoundInternal(const FGuid& RepositoryId);` — Invokey when a session was not found on the server.
- L133 _private prototype_ `void OnSessionRepositoriesDiscardedInternal(const TArray<FGuid>& RepositoryIds);` — Invoked when a set of repositories were successfully discarded by this process.
- L136 _private prototype_ `void OnSessionRepositoryMountedInternal(const FGuid& RepositoryId);` — Invokey when a repository was successfully mounted by this process.
- L139 _private prototype_ `void OnSessionImportedInternal(const TSharedRef<FDisasterRecoverySession>& ImportedSession);` — Invoked when a session was imported (the expected files found and copied).
- L142 _private prototype_ `FString GetSessionRepositoryRootDir() const;` — Returns this client repository database root dir.
- L145 _private prototype_ `void OnSessionRepositoryFilesModified(const TArray<FFileChangeData>& InFileChanges);` — Invoked when a file in the session repository directory is modified. Monitor changes made to the recovery info file by other processes.
- L148 _private prototype_ `FString GetDisasterRecoveryInfoPath() const;` — Returns the path to the directory contining the recovery info file.
- L151 _private prototype_ `const TCHAR* GetDisasterRecoveryInfoFilename() const;` — Returns the name of the recovery info file.
- L154 _private prototype_ `FString GetDisasterRecoveryInfoPathname() const;` — Returns the pathnname the recovery info file.
- L157 _private prototype_ `int32 GetRecentSessionMaxCount() const;` — Returns the number of 'recent' sessions to keep around for a given project.
- L160 _private prototype_ `int32 GetImportedSessionMaxCount() const;` — Returns the number of 'imported' sessions to keep around for a given project.
- L163 _private member_ `TSharedPtr<IConcertSyncClient> SyncClient;`
- L164 _private member_ `FString Role;`
- L165 _private member_ `FGuid ServerAdminEndpointId;`
- L166 _private member_ `TArray<TSharedRef<FDisasterRecoverySession>> SessionsCache;`
- L167 _private member_ `FOnDisasterRecoverySessionAdded OnDisasterRecoverySessionAddedDelegate;`
- L168 _private member_ `FOnDisasterRecoverySessionRemoved OnDisasterRecoverySessionRemovedDelegate;`
- L169 _private member_ `FOnDisasterRecoverySessionUpdated OnDisasterRecoverySessionUpdatedDelegate;`
- L171 _private member_ `FGuid CurrentSessionRepositoryId;`
- L172 _private member_ `FString CurrentSessionName;`
- L173 _private member_ `FDisasterRecoveryTaskExecutor TaskExecutor;`
- L174 _private member_ `int32 DisasterRecoveryClientCount = 0;`
- L176 _private member_ `FDelegateHandle DirectoryWatcherHandle;`
- L177 _private member_ `FString RecoveryInfoPathname;`
- L179 _private member_ `TArray<int32> CrashingProcessIds;`
- L180 _private member_ `uint32 SessionsCacheRevision = 0;`
- L181 _private member_ `bool bRefreshing = false;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDisasterRecoverySessionAdded, TSharedRef<FDisasterRecoverySession> );` — Invoked when a new disaster recovery session is added to the list of sessions.
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDisasterRecoverySessionAdded, TSharedRef<FDisasterRecoverySession> );` — Invoked when a new disaster recovery session is added to the list of sessions.
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDisasterRecoverySessionRemoved, const FGuid& );` — Invoked when a new disaster recovery session is removed from the list of sessions.
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDisasterRecoverySessionRemoved, const FGuid& );` — Invoked when a new disaster recovery session is removed from the list of sessions.
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDisasterRecoverySessionUpdated, TSharedRef<FDisasterRecoverySession> );` — Invoked when a new disaster recovery session is updated.
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDisasterRecoverySessionUpdated, TSharedRef<FDisasterRecoverySession> );` — Invoked when a new disaster recovery session is updated.

### `Plugins/Developer/Concert/ConcertApp/DisasterRecoveryClient/Source/DisasterRecoveryClient/Private/DisasterRecoverySettings.h` (Private)


#### class `UDisasterRecoverClientConfig`  
`class UDisasterRecoverClientConfig : public UObject`  
_L8-41_
- reflection: `UCLASS(config=Engine)`
- inherits: `UObject`
- L12 _public prototype_ `UDisasterRecoverClientConfig();`
- L18 _public member_ `bool bIsEnabled = true;` — `UPROPERTY(config, EditAnywhere, Category="Client Settings")` — Enables Recovery Hub plugin to create and/or restore a recovery sessions when needed.
- L26 _public member_ `FDirectoryPath RecoverySessionDir;` — `UPROPERTY(config, EditAnywhere, Category="Client Settings")` — The root directory where recovery sessions should be stored. If not set or invalid, the recovery sessions are stored in the project saved directory. The existing sessions are not moved (but remains accessible) when the directory is changed.
- L33 _public member_ `int32 RecentSessionMaxCount = 4;` — `UPROPERTY(config, EditAnywhere, Category="Client Settings", meta=(DisplayName="Session History Size", ClampMin = "0", UIMin = "0", UIMax = "50"))` — The maximum number of recent recovery sessions to keep around. The sessions are rotated at Editor startup and oldest ones are discarded.
- L40 _public member_ `int32 ImportedSessionMaxCount = 4;` — `UPROPERTY(config, EditAnywhere, Category="Client Settings", meta=(DisplayName="Imported Session History Size", ClampMin = "0", UIMin = "0", UIMax = "50"))` — The maximum number of imported recovery session to keep around. The sessions are rotated at Editor startup and oldest imports are discarded.

### `Plugins/Developer/Concert/ConcertApp/DisasterRecoveryClient/Source/DisasterRecoveryClient/Private/DisasterRecoveryTasks.h` (Private)


#### class `FDisasterRecoveryTask`  
`class FDisasterRecoveryTask`  
_L26-39_
- desc: Represents a task the disaster recovery executor can run.
- L29 _public prototype_ `virtual ~FDisasterRecoveryTask() = default;`
- L32 _public function_ `virtual void Start()` — Invoked once by the task executor to starts the task.
- L35 _public function_ `virtual bool Tick()` — Invoked every frame by the task executor until the function returns true to signal this task completion.
- L38 _public prototype_ `virtual void Abort() = 0;` — Invoked by the task executor to abort the task.

#### class `FDisasterRecoveryTaskExecutor`  
`class FDisasterRecoveryTaskExecutor`  
_L45-67_
- desc: Schedules and executes disaster recovery tasks serially. Using the task graph was ruled out because of the nature of some tasks that needs to be ticked over many frames on the game thread.
- L49 _public prototype_ `FDisasterRecoveryTaskExecutor();` — Construct the executor.
- L52 _public prototype_ `~FDisasterRecoveryTaskExecutor();` — Destruct the executor and abort all tasks.
- L55 _public prototype_ `void Enqueue(TSharedPtr<FDisasterRecoveryTask> Task);` — Schedule a task for execution, addind it at the end of the queue. The task will start only when previous tasks completed.
- L58 _public prototype_ `void Abort();` — Abort all executor tasks.
- L62 _private prototype_ `bool Tick(float);` — Tick the executor tasks.
- L65 _private member_ `TArray<TPair<TSharedPtr<FDisasterRecoveryTask>, bool >> Tasks;`
- L66 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`

#### class `FLookupDisasterRecoveryServerTask`  
`class FLookupDisasterRecoveryServerTask : public FDisasterRecoveryTask`  
_L72-86_
- inherits: `FDisasterRecoveryTask`
- desc: Lookup the specified recovery server.
- L75 _public prototype_ `FLookupDisasterRecoveryServerTask(IConcertClientRef InClient, FString InServerName, TFunction<void(const FGuid&)> InServerFoundFn, TFunction<void(const FText&)> InErrorOccurredFn);` — TODO: Consider adding a timeout.
- L76 _public prototype_ `virtual ~FLookupDisasterRecoveryServerTask();`
- L77 _public prototype_ `virtual void Start() override;`
- L78 _public prototype_ `virtual bool Tick() override;`
- L79 _public prototype_ `virtual void Abort() override;`
- L82 _private member_ `IConcertClientRef Client;`
- L83 _private member_ `FString ServerName;`
- L84 _private member_ `TFunction<void(const FGuid&)> OnServerFoundFn;`
- L85 _private member_ `TFunction<void(const FText&)> OnErrorFn;`

#### class `FDisasterRecoveryFutureExecTask`  
`class FDisasterRecoveryFutureExecTask : public FDisasterRecoveryTask`  
_L92-103_
- inherits: `FDisasterRecoveryTask`
- desc: Base task that start by executing a function returing a future and wait until the future returns. This class is expected to be extended to override the Start() function.
- L95 _public prototype_ `FDisasterRecoveryFutureExecTask(TFunction<void(const FText&)> InErrorOccurredFn);`
- L96 _public prototype_ `virtual bool Tick() override;`
- L97 _public prototype_ `virtual void Abort() override;`
- L100 _protected member_ `TFunction<void(const FText&)> OnErrorFn;`
- L101 _protected member_ `TSharedPtr<uint8> FutureContinuationToken;`
- L102 _protected member_ `bool bDone = false;`

#### class `FMountDisasterRecoverySessionRepositoryTask`  
`class FMountDisasterRecoverySessionRepositoryTask : public FDisasterRecoveryFutureExecTask`  
_L108-117_
- inherits: `FDisasterRecoveryFutureExecTask`
- desc: Mount a session repository.
- L111 _public prototype_ `FMountDisasterRecoverySessionRepositoryTask(TFunction<TFuture<FConcertAdmin_MountSessionRepositoryResponse>()> InMountFn, TFunction<void()> InRepositoryMountedFn, TFunction<void(const FText&)> InErrorOccurredFn);`
- L112 _public prototype_ `virtual void Start() override;`
- L115 _private member_ `TFunction<TFuture<FConcertAdmin_MountSessionRepositoryResponse>()> MountFn;`
- L116 _private member_ `TFunction<void()> OnRepositoryMountedFn;`

#### class `FDiscardDisasterRecoveryRepositoriesTask`  
`class FDiscardDisasterRecoveryRepositoriesTask : public FDisasterRecoveryFutureExecTask`  
_L122-131_
- inherits: `FDisasterRecoveryFutureExecTask`
- desc: Discards a set of session reporitories.
- L125 _public prototype_ `FDiscardDisasterRecoveryRepositoriesTask(TFunction<TFuture<FConcertAdmin_DropSessionRepositoriesResponse>()> InDropRepositoryFn, TFunction<void(const TArray<FGuid>&)> InRepositoriesDiscardedFn, TFunction<void(const FText&)> InErrorOccurredFn);`
- L126 _public prototype_ `virtual void Start() override;`
- L129 _private member_ `TFunction<TFuture<FConcertAdmin_DropSessionRepositoriesResponse>()> DropRepositoryFn;`
- L130 _private member_ `TFunction<void(const TArray<FGuid>&)> OnRepositoriesDiscardedFn;`

#### class `FLookupDisasterRecoverySessionIdTask`  
`class FLookupDisasterRecoverySessionIdTask : public FDisasterRecoveryFutureExecTask`  
_L136-146_
- inherits: `FDisasterRecoveryFutureExecTask`
- desc: Lookup a specific session ID by name.
- L139 _public prototype_ `FLookupDisasterRecoverySessionIdTask(TFunction<TFuture<FConcertAdmin_GetAllSessionsResponse>()> InGetSessionsFn, FString SessionName, TFunction<void(const FGuid&)> OnResultFn, TFunction<void(const FText&)> InErrorOccurredFn);`
- L140 _public prototype_ `virtual void Start() override;`
- L143 _private member_ `TFunction<TFuture<FConcertAdmin_GetAllSessionsResponse>()> GetSessionsFn;`
- L144 _private member_ `TFunction<void(const FGuid&)> OnResultFn;`
- L145 _private member_ `FString SessionName;`

#### class `FCreateAndJoinDisasterRecoverySessionTask`  
`class FCreateAndJoinDisasterRecoverySessionTask : public FDisasterRecoveryFutureExecTask`  
_L151-178_
- inherits: `FDisasterRecoveryFutureExecTask`
- desc: Creates a new session (restoring from an archive or not) and join that session.
- L162 _public prototype_ `FCreateAndJoinDisasterRecoverySessionTask(TFunction<TFuture<EConcertResponseCode>()> InCreateAndJoinFn, TSharedPtr<IConcertSyncClient> InSyncClient, FString InSessionName, TFunction<void()> InOnSessionJoined, TFunction<void(const FText& )> InOnErrorFn);` — Constructs the task. @param InCreateAndJoinFn The opaque function invoked on Start() to create the session. Expected to be IConcertClient::CreateSession() or IConcertClient::RestoreSession(). @param InSyncClient The disaster recovery sync client used to create/restore the session. @param InSessionName The session name to create. @param InOnSessionJoined Callback invoked when the session is created and joined. @param InOnErrorFn The callback invoked if an error occurred (with the corresponding message) during the execution of the task or if it was aborted.
- L163 _public prototype_ `virtual ~FCreateAndJoinDisasterRecoverySessionTask();`
- L164 _public prototype_ `virtual void Start() override;`
- L165 _public prototype_ `virtual bool Tick() override;`
- L168 _private prototype_ `void OnSessionConnectionChanged(IConcertClientSession& Session, EConcertConnectionStatus Status);`
- L169 _private prototype_ `void OnWorkspaceSynchronized();`
- L172 _private member_ `TFunction<TFuture<EConcertResponseCode>()> CreateAndJoinFn;`
- L173 _private member_ `TSharedPtr<IConcertSyncClient> SyncClient;`
- L174 _private member_ `FString SessionName;`
- L175 _private member_ `TFunction<void()> OnSessionJoinedFn;`
- L176 _private member_ `int32 LoopCountSinceWorkspaceSync = 0;`
- L177 _private member_ `bool bWorkspaceSynchronized = false;`

#### class `FFindRecoverableDisasterRecoverySessionTask`  
`class FFindRecoverableDisasterRecoverySessionTask : public FDisasterRecoveryTask`  
_L184-214_
- inherits: `FDisasterRecoveryTask`
- desc: Evaluates the list of disaster recovery candidates to find a session that can be recovered. A candidate is found when the its repository can be mounted, its archive loaded and if it contains at least one recoverable activity.
- L195 _public prototype_ `FFindRecoverableDisasterRecoverySessionTask(IConcertClientRef InClient, TFunction<FGuid()> InGetServerAdminEndpointId, TArray<TSharedPtr<FDisasterRecoverySession>> InCandidates, TFunction<void(TSharedPtr<FDisasterRecoverySession> )> InOnResult, TFunction<void(const FText& )> InOnErrorFn);` — Constructs the task. @param InClient The disaster recovery Concert sync client. @param InGetServerAdminEndpointId A function returing the disaster recovery server admin endpoint ID. @param InCandidates The list of candidate sessions to evaluate. @param InOnResult The callback invoked when a candidate if found (parameter not null) or when all candidates were eliminated (parameter null). @param InOnErrorFn The callback invoked if an error occurred (with the corresponding message) during the execution of the task or if it was aborted.
- L196 _public prototype_ `virtual void Start() override;`
- L197 _public prototype_ `virtual bool Tick() override;`
- L198 _public prototype_ `virtual void Abort() override;`
- L201 _private member_ `IConcertClientRef Client;`
- L202 _private member_ `TFunction<FGuid()> GetServerAdminEndpointIdFn;`
- L203 _private member_ `TArray<TSharedPtr<FDisasterRecoverySession>> Candidates;`
- L204 _private member_ `TSharedPtr<FDisasterRecoverySession> CurrentCandidate;`
- L205 _private member_ `TFunction<void(TSharedPtr<FDisasterRecoverySession>)> OnCandidateSearchResultFn;`
- L206 _private member_ `TFunction<void(const FText&)> OnErrorFn;`
- L207 _private member_ `TSharedPtr<FConcertActivityStream> ActivityStream;`
- L208 _private member_ `TArray<TSharedPtr<FConcertSessionActivity>> Activities;`
- L209 _private member_ `TUniquePtr<FMountDisasterRecoverySessionRepositoryTask> MountingTask;`
- L210 _private member_ `TUniquePtr<FLookupDisasterRecoverySessionIdTask> SearchingSessionIdTask;`
- L211 _private member_ `FGuid SessionId;`
- L212 _private member_ `bool bMounted = false;`
- L213 _private member_ `TSharedPtr<uint8> ExecutionToken;`

### `Plugins/Developer/Concert/ConcertApp/DisasterRecoveryClient/Source/DisasterRecoveryClient/Private/DisasterRecoveryUtil.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace DisasterRecoveryUtil`
- L10 _function_ `static inline FName GetSettingsContainerName()` (scope `DisasterRecoveryUtil`) — Returns the container name for the settings.
- L13 _function_ `static inline FName GetSettingsCategoryName()` (scope `DisasterRecoveryUtil`) — Returns the category name for the settings.
- L16 _function_ `static inline FName GetSettingsSectionName()` (scope `DisasterRecoveryUtil`) — Returns the section name for the settings.

### `Plugins/Developer/Concert/ConcertApp/DisasterRecoveryClient/Source/DisasterRecoveryClient/Private/SDisasterRecoveryHub.h` (Private)


#### class `SDisasterRecoveryHub`  
`class SDisasterRecoveryHub : public SCompoundWidget`  
_L24-109_
- inherits: `SCompoundWidget`
- desc: Displays, imports, inspects and restores disaster recovery sessions.
- L27 _public function_ `SLATE_BEGIN_ARGS(SDisasterRecoveryHub) : _IsRecoveryMode(false)`
- L32 _public prototype_ `SLATE_ARGUMENT(FText, IntroductionText) SLATE_ARGUMENT(bool, IsRecoveryMode) SLATE_END_ARGS();` — A short text explaining why this UI is presented to the user.
- L46 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow, TSharedPtr<FDisasterRecoverySessionManager> InSessionManager);` — Constructs the recovery hup. @param InArgs The Slate argument list. @param ConstructUnderMajorTab The major tab which will contain the session front-end. @param ConstructUnderWindow The window in which this widget is being constructed. @param InSyncClient The sync client.
- L48 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L52 _private prototype_ `TSharedRef<SWidget> MakeToolbarWidget();` — Toolbar buttons.
- L53 _private prototype_ `bool IsDeleteButtonEnabled() const;`
- L54 _private prototype_ `FReply OnDeleteClicked();`
- L55 _private prototype_ `FReply OnConfigClicked();`
- L56 _private prototype_ `FReply OnImportClicked();`
- L59 _private prototype_ `TSharedRef<SWidget> MakeSessionTreeView();` — Sessions tree view.
- L60 _private prototype_ `void OnSessionAdded(TSharedRef<FDisasterRecoverySession> InAddedSession);`
- L61 _private prototype_ `void OnSessionUpdated(TSharedRef<FDisasterRecoverySession> InUpdatedSession);`
- L62 _private prototype_ `void OnSessionRemoved(const FGuid& SessionRepositoryId);`
- L63 _private prototype_ `void OnSessionSelectionChanged(TSharedPtr<FDisasterRecoverySessionTreeNode> SelectedNode, ESelectInfo::Type SelectInfo);`
- L64 _private prototype_ `TSharedRef<ITableRow> OnGenerateSessionTreeNodeWidget(TSharedPtr<FDisasterRecoverySessionTreeNode> TreeNode, const TSharedRef<STableViewBase>& OwnerTable);`
- L65 _private prototype_ `void OnGetSessionTreeNodeChildren(TSharedPtr<FDisasterRecoverySessionTreeNode> InParent, TArray<TSharedPtr<FDisasterRecoverySessionTreeNode>>& OutChildren) const;`
- L66 _private prototype_ `void OnSetSessionTreeExpansionRecursive(TSharedPtr<FDisasterRecoverySessionTreeNode> InTreeNode, bool bInIsItemExpanded);`
- L69 _private prototype_ `TSharedRef<SWidget> MakeSessionActivityView();` — Selected session activities.
- L70 _private function_ `bool ShouldDisplayActivityDetails() const`
- L71 _private prototype_ `bool FetchActivities(TArray<TSharedPtr<FConcertSessionActivity>>& InOutActivities, int32& OutFetchedCount, FText& ErrorMsg);`
- L72 _private prototype_ `FText GetNoActivityDisplayedReason() const;`
- L75 _private prototype_ `FText GetRecoverAllButtonTooltip() const;` — Recover buttons.
- L76 _private prototype_ `FReply OnRecoverAllButtonClicked();`
- L77 _private prototype_ `void OnRecoverThroughButtonClicked(TSharedPtr<FConcertSessionActivity> ThroughActivity);`
- L78 _private prototype_ `FReply RecoverThrough(TSharedPtr<FConcertSessionActivity> ThroughActivity);`
- L79 _private prototype_ `bool IsRecoverAllButtonEnabled() const;`
- L80 _private prototype_ `bool IsRecoverThroughButtonVisible() const;`
- L83 _private prototype_ `FReply OnCancelButtonClicked();` — Cancel/Dismiss.
- L84 _private prototype_ `FReply DismissWidget();`
- L88 _private member_ `TSharedPtr<FDisasterRecoverySessionManager> SessionManager;` — The session manager.
- L91 _private member_ `TSharedPtr<STreeView<TSharedPtr<FDisasterRecoverySessionTreeNode>>> SessionTreeView;` — The widget displaying the list of sessions.
- L92 _private member_ `TSharedPtr<FDisasterRecoverySessionTreeNode> LiveCategoryRootNode;`
- L93 _private member_ `TSharedPtr<FDisasterRecoverySessionTreeNode> UnreviewedCrashCategoryRootNode;`
- L94 _private member_ `TSharedPtr<FDisasterRecoverySessionTreeNode> RecentCategoryRootNode;`
- L95 _private member_ `TSharedPtr<FDisasterRecoverySessionTreeNode> ImportedCategoryRootNode;`
- L96 _private member_ `TSharedPtr<FDisasterRecoverySessionTreeNode> SelectedSessionNode;`
- L97 _private member_ `TArray<TSharedPtr<FDisasterRecoverySessionTreeNode>> SessionTreeRootNodes;`
- L100 _private member_ `TSharedPtr<SConcertSessionRecovery> ActivityView;` — The widget displaying the activities of currently selected session.
- L101 _private member_ `TSharedPtr<FConcertActivityStream> SelectedSessionActivityStream;`
- L102 _private member_ `TSharedPtr<SWidget> NoActivityPanel;`
- L103 _private member_ `FText LoadingSessionErrorMsg;`
- L104 _private member_ `bool bLoadingActivities = false;`
- L106 _private member_ `TWeakPtr<SDockTab> OwnerTab;`
- L107 _private member_ `TWeakPtr<SWindow> OwnerWindow;`
- L108 _private member_ `FDateTime NextRefreshTime;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ESelectInfo`

### `Plugins/Developer/Concert/ConcertApp/DisasterRecoveryClient/Source/DisasterRecoveryClient/Public/IDisasterRecoveryClientModule.h` (Public)


#### class `IDisasterRecoveryClientModule`  
`class IDisasterRecoveryClientModule : public IModuleInterface`  
_L17-48_
- inherits: `IModuleInterface`
- desc: Interface for the Disaster Recovery module.
- L26 _public function_ `static inline IDisasterRecoveryClientModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L37 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L47 _public prototype_ `virtual TSharedPtr<IConcertSyncClient> GetClient() const = 0;` — Get the sync client that will performing the DisasterRecovery role @return The client

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisasterRecovery, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisasterRecovery, Log, All);`
