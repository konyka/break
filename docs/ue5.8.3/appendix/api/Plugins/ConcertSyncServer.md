# Plugins / ConcertSyncServer

- module root: `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer`
- headers: 34; symbols: 614
- symbol kinds: class=27, delegate=12, enum=5, enumerator=16, externvar=2, function=76, member=108, namespace=76, prototype=275, struct=9, typedef=8
- PrivateDependencyModuleNames: ConcertTransport, JsonUtilities, Serialization
- PublicDependencyModuleNames: Concert, ConcertServer, ConcertSyncCore, Core, CoreUObject

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/ConcertServerDataStore.h` (Private)


#### class `FConcertServerDataStore`  
`class FConcertServerDataStore`  
_L24-56_
- desc: Handles data store requests from one or more clients connected to the same Concert session. The store hooks itself up as a request handler in the specified session. @remarks The implementation is not thread safe. The concert server application is expected to pump and dispatch session requests serially to the data store.
- L39 _public prototype_ `FConcertServerDataStore(TSharedRef<FConcertSyncServerLiveSession> LiveSession, bool bIsContentReplicationEnabled = true);` — Constructs a server-side data store. @param LiveSession The session owning the data store. @param bIsContentReplicationEnabled If true, the servers will pushes the entire store content to newly connected clients and continue updating each of them as keys get added or updated. In normal utilization this is expected to be true, but for unit tests, it is useful to be able to turn this feature off.
- L40 _public prototype_ `virtual ~FConcertServerDataStore();`
- L43 _private prototype_ `void OnSessionClientChanged(IConcertServerSession&, EConcertClientStatus, const FConcertSessionClientInfo&);`
- L44 _private prototype_ `EConcertSessionResponseCode OnFetchOrAdd(const FConcertSessionContext& Context, const FConcertDataStore_FetchOrAddRequest& Request, FConcertDataStore_Response& Response);`
- L45 _private prototype_ `EConcertSessionResponseCode OnCompareExchange(const FConcertSessionContext& Context, const FConcertDataStore_CompareExchangeRequest& Request, FConcertDataStore_Response& Response);`
- L46 _private prototype_ `void FireContentReplicationEvent(const FGuid& SourceEndPoint, const FName& Key, const FConcertDataStore_StoreValue& Value);`
- L49 _private member_ `FConcertDataStore DataStore;` — Maps the property name to an arbitrary blob value that can be memory compared.
- L52 _private member_ `TSharedPtr<FConcertSyncServerLiveSession> LiveSession;` — The concert live session owning the store and through which the requests/responses are dispatched.
- L55 _private member_ `bool bContentReplicationEnabled;` — True if the server should perform initial sync and push further modifications to the clients.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/ConcertServerEventForwardingSink.h` (Private)


#### class `TConcertServerEventForwardingSink`  
`template<typename TDerived> class TConcertServerEventForwardingSink : public IConcertServerEventSink`  
_L15-106_
- inherits: `IConcertServerEventSink`
- desc: Uses CRTP to call IConcertServerEventSink::FooImpl and calls the equivalent event in ConcertServerEvents with the result. Example: TDerived must implement GetSessionsFromPathImpl.
- L17 _private function_ `TDerived* This()`
- L18 _private function_ `const TDerived* This() const`
- L22 _public function_ `virtual void GetSessionsFromPath(const IConcertServer& InServer, const FString& InPath, TArray<FConcertSessionInfo>& OutSessionInfos, TArray<FDateTime>* OutSessionCreationTimes = nullptr) final`
- L27 _public function_ `virtual bool OnLiveSessionCreated(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession, const FInternalLiveSessionCreationParams& AdditionalParams) final`
- L35 _public function_ `virtual void OnLiveSessionDestroyed(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession) final`
- L41 _public function_ `virtual bool OnArchivedSessionCreated(const IConcertServer& InServer, const FString& InArchivedSessionRoot, const FConcertSessionInfo& InArchivedSessionInfo) final`
- L48 _public function_ `virtual void OnArchivedSessionDestroyed(const IConcertServer& InServer, const FGuid& InArchivedSessionId) final`
- L54 _public function_ `virtual bool ArchiveSession(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession, const FString& InArchivedSessionRoot, const FConcertSessionInfo& InArchivedSessionInfo, const FConcertSessionFilter& InSessionFilter) final`
- L61 _public function_ `virtual bool ArchiveSession(const IConcertServer& InServer, const FString& InLiveSessionWorkingDir, const FString& InArchivedSessionRoot, const FConcertSessionInfo& InArchivedSessionInfo, const FConcertSessionFilter& InSessionFilter) final`
- L68 _public function_ `virtual bool CopySession(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession, const FString& NewSessionRoot, const FConcertSessionFilter& InSessionFilter) final`
- L75 _public function_ `virtual bool ExportSession(const IConcertServer& InServer, const FGuid& InSessionId, const FString& DestDir, const FConcertSessionFilter& InSessionFilter, bool bAnonymizeData) final`
- L82 _public function_ `virtual bool RestoreSession(const IConcertServer& InServer, const FGuid& InArchivedSessionId, const FString& InLiveSessionRoot, const FConcertSessionInfo& InLiveSessionInfo, const FConcertSessionFilter& InSessionFilter) final`
- L89 _public function_ `virtual bool GetUnmutedSessionActivities(const IConcertServer& InServer, const FGuid& SessionId, int64 FromActivityId, int64 ActivityCount, TArray<FConcertSessionSerializedPayload>& OutActivities, TMap<FGuid, FConcertClientInfo>& OutEndpointClientInfoMap, bool bIncludeDetails) final`
- L94 _public function_ `virtual void OnLiveSessionRenamed(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession) final`
- L100 _public function_ `virtual void OnArchivedSessionRenamed(const IConcertServer& InServer, const FString& InArchivedSessionRoot, const FConcertSessionInfo& InArchivedSessionInfo) final`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/ConcertServerSequencerManager.h` (Private)


#### class `FConcertServerSequencerManager`  
`class FConcertServerSequencerManager`  
_L14-87_
- L17 _public prototype_ `explicit FConcertServerSequencerManager(const TSharedRef<FConcertSyncServerLiveSession>& InLiveSession);`
- L18 _public prototype_ `~FConcertServerSequencerManager();`
- L21 _public prototype_ `void BindSession(const TSharedRef<FConcertSyncServerLiveSession>& InLiveSession);` — Bind this manager to the server session.
- L24 _public prototype_ `void UnbindSession();` — Unbind the manager from its currently bound session.
- L28 _private prototype_ `void HandleSequencerStateEvent(const FConcertSessionContext& InEventContext, const FConcertSequencerStateEvent& InEvent);` — Handler for the sequencer state updated event.
- L31 _private prototype_ `void HandleSequencerOpenEvent(const FConcertSessionContext& InEventContext, const FConcertSequencerOpenEvent& InEvent);` — Handler for the sequencer open event.
- L34 _private prototype_ `void HandleSequencerCloseEvent(const FConcertSessionContext& InEventContext, const FConcertSequencerCloseEvent& InEvent);` — Handler for the sequencer close event.
- L37 _private prototype_ `void HandleSequencerTimeAdjustmentEvent(const FConcertSessionContext& InEventContext, const FConcertSequencerTimeAdjustmentEvent& InEvent);` — Handler for the sequencer time adjustment event.
- L40 _private prototype_ `void HandleSequencerPreloadRequestEvent(const FConcertSessionContext& InEventContext, const FConcertSequencerPreloadRequest& InEvent);` — Handler for sequence preloading requests.
- L43 _private prototype_ `void HandleSequencerPreloadStatusEvent(const FConcertSessionContext& InEventContext, const FConcertSequencerPreloadAssetStatusMap& InEvent);` — Handler for sequence preloading status updates.
- L46 _private prototype_ `void HandleWorkspaceSyncAndFinalizeCompletedEvent(const FConcertSessionContext& InEventContext, const FConcertWorkspaceSyncAndFinalizeCompletedEvent& InEvent);` — Handler for the workspace sync and finalize completed event.
- L49 _private prototype_ `void HandleSessionClientChanged(IConcertServerSession& InSession, EConcertClientStatus InClientStatus, const FConcertSessionClientInfo& InClientInfo);` — Handler for the session clients changed event.
- L53 _private prototype_ `bool AddSequencePreloadForClient(const FGuid& RequestClient, const FTopLevelAssetPath& SequenceObjectPath);` — Adds the specified client endpoint as a referencer for the specified sequence, and returns true if that was the first reference for that sequence.
- L56 _private prototype_ `bool RemoveSequencePreloadForClient(const FGuid& RequestClient, const FTopLevelAssetPath& SequenceObjectPath);` — Adds the specified client endpoint as a referencer for the specified sequence, and returns true if that was the last remaining reference for that sequence.
- L77 _private member_ `TMap<FName, FConcertOpenSequencerState> SequencerStates;` — Map of all currently opened Sequencer in a session, locally opened or not.
- L80 _private member_ `TSharedPtr<FConcertSyncServerLiveSession> LiveSession;` — Live session tracked by this manager.
- L83 _private member_ `TMap<FTopLevelAssetPath, TSet<FGuid>> PreloadRequesters;` — Map of level sequences indicating which client endpoints have requested preloading for them.
- L86 _private member_ `FConcertSequencerPreloadClientStatusMap ClientPreloadStatuses;` — Map of clients' individual progress preloading specific sequences.

#### struct `FConcertServerSequencerManager::FConcertOpenSequencerState`  
`struct FConcertOpenSequencerState`  
_L59-74_
- L62 _public member_ `TArray<FGuid> ClientEndpointIds;` — Client Endpoints that have this Sequence opened.
- L65 _public member_ `FConcertSequencerState State;` — Current state of the Sequence.
- L73 _public member_ `FConcertByteArray TakeData;` — `UPROPERTY()` — In the case that the SequenceObjectPath points to a take preset. We capture the preset data into a payload that can be applied to take that we are going to open. We store it in the state so that we can play it back when new users join.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/ConcertServerSyncCommandQueue.h` (Private)


#### class `FConcertServerSyncCommandQueue`  
`class FConcertServerSyncCommandQueue`  
_L12-129_
- desc: Queue of ordered events that need to be synced to another client.
- L48 _public typedef_ `typedef TFunction<void(const FSyncCommandContext&, const FGuid&)> FSyncCommand;` — Function representing a sync command. Is passed the endpoint ID of the target.
- L53 _public prototype_ `FConcertServerSyncCommandQueue();` — Constructor
- L58 _public prototype_ `FConcertServerSyncCommandQueue(const FConcertServerSyncCommandQueue&) = delete;` — Non-copyable.
- L59 _public prototype_ `FConcertServerSyncCommandQueue& operator=(const FConcertServerSyncCommandQueue&) = delete;`
- L65 _public prototype_ `void RegisterEndpoint(const FGuid& InEndpointId);` — Register this endpoint with the queue. @note This must be called before assigning work or properties to the endpoint.
- L70 _public prototype_ `void UnregisterEndpoint(const FGuid& InEndpointId);` — Unregister this endpoint from the queue.
- L75 _public prototype_ `void SetCommandProcessingMethod(const FGuid& InEndpointId, const ESyncCommandProcessingMethod InProcessingMethod);` — Set the command processing method for the given endpoint.
- L81 _public prototype_ `void QueueCommand(const FSyncCommand& InCommand);` — Queue a command to be run that is not attached to any particular endpoint. the endpoint is handled within the FSyncCommand.
- L86 _public prototype_ `void QueueCommand(const FGuid& InEndpointId, const FSyncCommand& InCommand);` — Queue a command to process for the given endpoint.
- L91 _public prototype_ `void QueueCommand(TArrayView<const FGuid> InEndpointIds, const FSyncCommand& InCommand);` — Queue a command to process for the given endpoints.
- L97 _public prototype_ `void ProcessQueue(const double InTimeLimitSeconds = 0.0);` — Process the queue, attempting to limit time-sliced endpoints to the given time limit. @note Will always process at least one command for each time-sliced endpoint.
- L102 _public prototype_ `bool IsQueueEmpty(const FGuid& InEndpointId) const;` — Check whether the queue for the given endpoint is empty.
- L107 _public prototype_ `void ClearQueue(const FGuid& InEndpointId);` — Clear the queue for the given endpoint.
- L112 _public prototype_ `void ClearQueue();` — Clear the queue for all endpoints.
- L117 _public prototype_ `void ResetQueue();` — Reset the queue back to its empty state with no endpoints registered.
- L119 _public member_ `const FGuid GlobalGuid = FGuid::NewGuid();`
- L128 _private member_ `TMap<FGuid, FEndpointSyncCommandQueue> QueuedSyncCommands;`

#### enum `FConcertServerSyncCommandQueue::ESyncCommandProcessingMethod`  
`enum ESyncCommandProcessingMethod : uint8`  
_L18-24_
- desc: Methods by which queued commands can be processed during ProcessQueue.
- L21 _public enumerator_ `ProcessAll` — Process all queued commands, regardless of how long it takes
- L23 _public enumerator_ `ProcessTimeSliced` — Process queued commands up-to the given time limit (will always process at least one command per-client)

#### struct `FConcertServerSyncCommandQueue::FSyncCommandContext`  
`struct FSyncCommandContext`  
_L29-42_
- desc: Context object passed to FSyncCommand.
- L32 _public member_ `int32 CommandIndex;` — Index of this command in its queue
- L35 _public member_ `int32 NumCommands;` — Total number of commands in this queue
- L38 _public function_ `int32 GetNumRemainingCommands() const` — Get the number remaining commands in the queue

#### struct `FConcertServerSyncCommandQueue::FEndpointSyncCommandQueue`  
`struct FEndpointSyncCommandQueue`  
_L122-126_
- L124 _public member_ `ESyncCommandProcessingMethod ProcessingMethod = ESyncCommandProcessingMethod::ProcessAll;`
- L125 _public member_ `TArray<FSyncCommand> CommandQueue;`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/ConcertServerWorkspace.h` (Private)


#### enum `EConcertLockFlags`  
`enum class EConcertLockFlags : uint8`  
_L26-32_
- L28 _public enumerator_ `None = 0`
- L29 _public enumerator_ `Explicit = 1 << 0`
- L30 _public enumerator_ `Force = 1 << 1`
- L31 _public enumerator_ `Temporary = 1 << 2`

#### class `FConcertServerWorkspace`  
`class FConcertServerWorkspace`  
_L35-357_
- L39 _public prototype_ `explicit FConcertServerWorkspace(const TSharedRef<FConcertSyncServerLiveSession>& InLiveSession, TSharedPtr<IConcertFileSharingService> InFileSharingService);`
- L40 _public prototype_ `~FConcertServerWorkspace();`
- L43 _public function_ `UE::ConcertSyncServer::Replication::IReplicationWorkspace& GetReplicationWorkspace()` — @return Gets the portion of the workspace that manages replication data.
- L48 _private prototype_ `static FGuid HashEndpointIdAndActivityId(const FGuid& TargetEndpointId, FActivityID ActivityID);` — Creates an ID from the given data through an simple hash function. The ID only depends on the input, allowing us to reconstruct IDs later in time.
- L58 _private prototype_ `TOptional<FConcertWorkspaceSyncActivityEvent> SyncTransactionActivityEvent(const int64 InSyncActivityId, const int32 InNumRemainingSyncEvents, const bool InLiveOnly = true) const;` — Get the sync event for a transaction activity in the session database. @param InSyncActivityId			The ID of the activity to send the sync event for. @param InNumRemainingSyncEvents	The number of items left in the sync queue. @param InLiveOnly				True if the bulk of the transaction data should only be sent if this transaction is live. Returns the transaction activity event for the given activity id.
- L67 _private prototype_ `TOptional<FConcertWorkspaceSyncActivityEvent> MakeSyncActivityEvent(const int64 InSyncActivityId, const bool bInHeadOnly = true) const;` — Get the sync event for a package activity in the session database. @param InSyncActivityId			The ID of the activity to send the sync event for. @param InHeadOnly				True if we are only interested in the head revision Returns the package activity event for the given activity id.
- L70 _private prototype_ `void BindSession(const TSharedRef<FConcertSyncServerLiveSession>& InLiveSession);` — Bind the workspace to this session.
- L73 _private prototype_ `void UnbindSession();` — Unbind the workspace to its bound session.
- L76 _private prototype_ `void HandleTick(IConcertServerSession& InSession, float InDeltaTime);`
- L79 _private prototype_ `void HandleSessionClientChanged(IConcertServerSession& InSession, EConcertClientStatus InClientStatus, const FConcertSessionClientInfo& InClientInfo);`
- L82 _private prototype_ `void HandleSessionAcknowledgementReceived(const FConcertEndpointContext& LocalEndpoint, const FConcertEndpointContext& RemoteEndpoint, const TSharedRef<IConcertMessage>& AckedMessage, const FConcertMessageContext& MessageContext) const;`
- L85 _private prototype_ `void HandleSyncRequestedEvent(const FConcertSessionContext& Context, const FConcertWorkspaceSyncRequestedEvent& Event);`
- L88 _private prototype_ `void HandlePackageTransmissionStartEvent(const FConcertSessionContext& Context, const FConcertPackageTransmissionStartEvent& Event);`
- L91 _private prototype_ `void HandlePackageUpdateEvent(const FConcertSessionContext& Context, const FConcertPackageUpdateEvent& Event);`
- L94 _private prototype_ `void HandleTransactionFinalizedEvent(const FConcertSessionContext& InEventContext, const FConcertTransactionFinalizedEvent& InEvent);`
- L97 _private prototype_ `void HandleTransactionSnapshotEvent(const FConcertSessionContext& InEventContext, const FConcertTransactionSnapshotEvent& InEvent);`
- L100 _private prototype_ `void HandlePlaySessionEvent(const FConcertSessionContext& Context, const FConcertPlaySessionEvent& Event);`
- L103 _private prototype_ `EConcertSessionResponseCode HandleSyncEventRequest(const FConcertSessionContext& Context, const FConcertSyncEventRequest& Request, FConcertSyncEventResponse& Response);`
- L106 _private prototype_ `EConcertSessionResponseCode HandleResourceLockRequest(const FConcertSessionContext& Context, const FConcertResourceLockRequest& Request, FConcertResourceLockResponse& Response);`
- L109 _private prototype_ `void HandleIgnoredActivityStateChanged(const FConcertSessionContext& Context, const FConcertIgnoreActivityStateChangedEvent& Event);`
- L112 _private prototype_ `void HandleBeginPlaySession(const FName InPlayPackageName, const FGuid& InEndpointId, bool bIsSimulating);` — Invoked when the client corresponding to the specified endpoint begins to "Play" in a mode such as PIE or SIE.
- L115 _private prototype_ `void HandleEndPlaySession(const FName InPlayPackageName, const FGuid& InEndpointId);` — Invoked when the client corresponding to the specified endpoint exits a "Play" mode such as PIE or SIE.
- L118 _private prototype_ `void HandleSwitchPlaySession(const FName InPlayPackageName, const FGuid& InEndpointId);` — Invoked when the client corresponding to specified endpoint toggles between PIE and SIE play mode.
- L121 _private prototype_ `void HandleEndPlaySessions(const FGuid& InEndpointId);` — Invoked when the cient corresponding to the specified endpoint exits a "Play" mode such as PIE or SIE.
- L124 _private prototype_ `void HandleServerLoggingEvent(const FConcertSessionContext& Context, const FConcertServerLogging& Event);` — A special event sent from the client to enable / disable additional logging on the server.
- L127 _private prototype_ `FName FindPlaySession(const FGuid& InEndpointId);` — Returns the package name being played (PIE/SIE) by the specified client endpoint if that endpoint is in such play mode, otherwise, returns an empty name.
- L134 _private prototype_ `bool LockWorkspaceResource(const FName InResourceName, const FGuid& InLockEndpointId, EConcertLockFlags InLockFlags);` — Attempt to lock the given resource to the given endpoint. @note Passing force will always assign the lock to the given endpoint, even if currently locked by another. @return True if the resource was locked (or already locked by the given endpoint), false otherwise.
- L145 _private prototype_ `bool LockWorkspaceResources(const TArray<FName>& InResourceNames, const FGuid& InLockEndpointId, EConcertLockFlags InLockFlags, TMap<FName, FGuid>* OutFailedRessources = nullptr);` — Attempt to lock a list of resources to the given endpoint. @param InResourceNames The list of resource to lock @param InLockEndpointId The client id trying to acquire the lock @param InExplicit mark the lock as explicit @param InForce steal locks if true @param OutFailedResources Pointer to an array to gather resources on which acquiring the lock failed. @return true if the lock was successfully acquired on all InResourceNames
- L152 _private prototype_ `bool UnlockWorkspaceResource(const FName InResourceName, const FGuid& InLockEndpointId, EConcertLockFlags InLockFlags);` — Attempt to unlock the given resource from the given endpoint. @note Passing force will always clear, even if currently locked by another endpoint. @return True if the resource was unlocked, false otherwise.
- L163 _private prototype_ `bool UnlockWorkspaceResources(const TArray<FName>& InResourceNames, const FGuid& InLockEndpointId, EConcertLockFlags InLockFlags, TMap<FName, FGuid>* OutFailedRessources = nullptr);` — Attempt to unlock a list of resources from the given endpoint. @param InResourceNames The list of resource to unlock @param InLockEndpointId The client id trying to releasing the lock @param InExplicit mark the unlock as explicit, implicit unlock won't unlock explicit lock @param InForce release locks even of not owned if true @param OutFailedResources Pointer to an array to gather resources on which releasing the lock failed. @return true if the lock was successfully released on all InResourceNames
- L169 _private prototype_ `void UnlockAllWorkspaceResources(const FGuid& InLockEndpointId);` — Unlock all resource locks held by a client. @param InLockEndpointId the client endpoint id releasing the lock on resources.
- L174 _private prototype_ `bool IsWorkspaceResourceLocked(const FName InResourceName, const FGuid& InLockEndpointId) const;` — Check to see if the given resource is locked by the given endpoint.
- L182 _private prototype_ `void SetEndpoint(const FGuid& InEndpointId, const FConcertSyncEndpointData& InEndpointData);` — Set an endpoint in the session database, creating or replacing it, and sync the result back to all clients. @param InEndpointId				The ID of the endpoint to set. @param InEndpointData			The endpoint data to set.
- L191 _private prototype_ `void SendSyncEndpointEvent(const FGuid& InTargetEndpointId, const FGuid& InSyncEndpointId, const int32 InNumRemainingSyncEvents) const;` — Send a sync event for an endpoint in the session database. @param InTargetEndpointId		The ID of the endpoint to send the sync event to. @param InSyncEndpointId			The ID of the endpoint to send the sync event for. @param InNumRemainingSyncEvents	The number of items left in the sync queue.
- L199 _private prototype_ `void AddConnectionActivity(const FConcertSyncConnectionActivity& InConnectionActivity);` — Add a new connection activity to the session database, assigning it both an activity and connection event ID, and sync the result back to all clients. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @param InConnectionActivity		The connection activity to add (the ActivityId, EventTime, EventType, and EventId members are ignored).
- L208 _private prototype_ `void SendSyncConnectionActivityEvent(const FGuid& InTargetEndpointId, const int64 InSyncActivityId, const int32 InNumRemainingSyncEvents) const;` — Send a sync event for a connection activity in the session database. @param InTargetEndpointId		The ID of the endpoint to send the sync event to. @param InSyncActivityId			The ID of the activity to send the sync event for. @param InNumRemainingSyncEvents	The number of items left in the sync queue.
- L216 _private prototype_ `void AddLockActivity(const FConcertSyncLockActivity& InLockActivity);` — Add a new lock activity to the session database, assigning it both an activity and lock event ID, and sync the result back to all clients. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @param InLockActivity			The lock activity to add (the ActivityId, EventTime, EventType, and EventId members are ignored).
- L225 _private prototype_ `void SendSyncLockActivityEvent(const FGuid& InTargetEndpointId, const int64 InSyncActivityId, const int32 InNumRemainingSyncEvents) const;` — Send a sync event for a lock activity in the session database. @param InTargetEndpointId		The ID of the endpoint to send the sync event to. @param InSyncActivityId			The ID of the activity to send the sync event for. @param InNumRemainingSyncEvents	The number of items left in the sync queue.
- L233 _private prototype_ `void AddTransactionActivity(const FConcertSyncTransactionActivity& InTransactionActivity);` — Add a new transaction activity to the session database, assigning it both an activity and transaction event ID, and sync the result back to all clients. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @param InTransactionActivity		The transaction activity to add (the ActivityId, EventTime, EventType, and EventId members are ignored).
- L243 _private prototype_ `void SendSyncTransactionActivityEvent(const FGuid& InTargetEndpointId, const int64 InSyncActivityId, const int32 InNumRemainingSyncEvents, const bool InLiveOnly = true) const;` — Send a sync event for a transaction activity in the session database. @param InTargetEndpointId		The ID of the endpoint to send the sync event to. @param InSyncActivityId			The ID of the activity to send the sync event for. @param InNumRemainingSyncEvents	The number of items left in the sync queue. @param InLiveOnly				True if the bulk of the transaction data should only be sent if this transaction is live.
- L251 _private prototype_ `void AddPackageActivity(const FConcertSyncActivity& InPackageActivityBasePart, const FConcertPackageInfo& PackageInfo, FConcertPackageDataStream& InPackageDataStream);` — Add a new package activity to the session database, assigning it both an activity and package event ID, and sync the result back to all clients. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @param InPackageActivity			The package activity to add (the ActivityId, EventTime, EventType, EventId, and PackageRevision members are ignored).
- L259 _private prototype_ `void SendSyncPackageActivityEvent(const FConcertWorkspaceSyncActivityEvent& SyncEvent, const FGuid& InTargetEndpointId) const;` — Send a sync event for a package activity in the session database. @param SyncEvent				The ID of the endpoint to send the sync event to. @param InSyncActivityId		The ID of the activity to send the sync event for.
- L268 _private prototype_ `void OnAddReplicationActivity(const int64 ActivityId, const bool bSuccess);` — Called when the replication workspace attempted to add a FConcertSyncReplicationActivity to the database. This syncs the result back to all clients. @param ActivityId	The identifier of the activity that was attempted to be added @param bSuccess		Whether the activity was actually added to the database (i.e. false means the attempt failed).
- L277 _private prototype_ `void SendSyncReplicationActivityEvent(const FGuid& InTargetEndpointId, const int64 InSyncActivityId, const int32 InNumRemainingSyncEvents);` — Send a sync event for a replication activity in the session database. @param InTargetEndpointId		The ID of the endpoint to send the sync event to. @param InSyncActivityId			The ID of the activity to send the sync event for. @param InNumRemainingSyncEvents	The number of items left in the sync queue.
- L284 _private prototype_ `void PostActivityAdded(const int64 InActivityId);` — Called after any activity is added to the session database. @param InActivityId				The ID of the activity that was added.
- L291 _private function_ `bool ShouldIgnoreClientActivityOnRestore(const FGuid& ClientEndpoint) const` — Check if a given client was configured to prevent restoring the activities being recorded. @param ClientEndpoint The client for which the check must be done. @return True if the activity should be flagged as 'ignored on restore'.
- L298 _private prototype_ `bool CanExchangePackageDataAsByteArray(int64 PackageDataSize) const;` — Returns true if the package data is small enough to be exchanged using a single TArray<> data structure. If the package data is too big according to a configuration (or a hard limit) the package data will be exchanged through other means like file stream or file sharing.
- L301 _private prototype_ `bool IsFileSharingEnabled() const;` — Returns true if the file sharing service is enabled.
- L306 _private prototype_ `EConcertSessionResponseCode FillPackageEvent(FConcertSyncPackageEventData& InPackageEventSrc, FConcertSyncPackageEvent& OutPackageEvent) const;` — Write all package event fields from the event and decide if the package data should be directly embedded in the event or linked to a shared file.
- L311 _private prototype_ `TSharedPtr<FArchive> GetPackageDataStream(const FConcertPackage& Package);` — Open a stream on the package data, depending if the package data was directly embedded in the object (in memory) or linked as a shared file.
- L314 _private member_ `TSharedPtr<FConcertSyncServerLiveSession> LiveSession;` — Live session tracked by this workspace
- L317 _private member_ `TArray<FGuid> LiveSyncEndpoints;` — Array of endpoints that are subscribed to live-sync (server automatically pushes updates)
- L320 _private member_ `TArray<FGuid> ManualSyncEndpoints;` — Array of endpoints that are currently undergoing a manual sync (client explicitly request data)
- L323 _private member_ `TSharedPtr<FConcertServerSyncCommandQueue> SyncCommandQueue;`
- L334 _private member_ `TMap<FName, TArray<FPlaySessionInfo>> ActivePlaySessions;` — Tracks endpoints that are in a play session (package name -> {endpoint IDs, bSimulating})
- L343 _private typedef_ `typedef TMap<FName, FLockOwner> FLockedResources;`
- L344 _private member_ `TUniquePtr<FLockedResources> LockedResources;`
- L347 _private member_ `TUniquePtr<FConcertServerDataStore> DataStore;` — The data store shared by all clients connected to the server tracked by this workspace.
- L350 _private member_ `TSet<FGuid> IgnoredActivityClients;` — Contains the list of clients for which activities should be marked as 'ignore on restore'. @see FConcertIgnoreActivityStateChangedEvent.
- L353 _private member_ `TUniquePtr<IConcertFileSharingService> FileSharingService;` — Optional side channel to exchange large blobs (package data) with the client in a scalable way (ex. the request/response transport layer is not designed and doesn't support exchanging 3GB packages).
- L356 _private member_ `UE::ConcertSyncServer::FReplicationWorkspace ReplicationWorkspace;` — Manages replication data for the database.

#### struct `FConcertServerWorkspace::FPlaySessionInfo`  
`struct FPlaySessionInfo`  
_L326-331_
- desc: Contains the play state (PIE/SIE) of a client endpoint.
- L328 _public member_ `FGuid EndpointId;`
- L329 _public member_ `bool bIsSimulating;`
- L330 _public function_ `bool operator==(const FPlaySessionInfo& Other) const`

#### struct `FConcertServerWorkspace::FLockOwner`  
`struct FLockOwner`  
_L337-342_
- desc: Tracks locked transaction resources (resource ID -> Lock owner)
- L339 _public member_ `FGuid EndpointId;`
- L340 _public member_ `bool bExplicit = false;`
- L341 _public member_ `bool bTemporary = false;`

#### Free symbols / members of external scopes

- L33 _prototype_ `ENUM_CLASS_FLAGS(EConcertLockFlags);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/ConcertSyncServer.h` (Private)


#### class `FConcertSyncServer`  
`class FConcertSyncServer : public IConcertSyncServer, public TConcertServerEventForwardingSink<FConcertSyncServer>`  
_L29-117_
- inherits: `IConcertSyncServer,TConcertServerEventForwardingSink<FConcertSyncServer>`
- desc: Implementation for a Concert Sync Server.
- L33 _public prototype_ `FConcertSyncServer(const FString& InRole, const FConcertSessionFilter& InAutoArchiveSessionFilter);`
- L34 _public prototype_ `virtual ~FConcertSyncServer();`
- L37 _public prototype_ `virtual void Startup(const UConcertServerConfig* InServerConfig, const EConcertSyncSessionFlags InSessionFlags) override;`
- L38 _public prototype_ `virtual void Shutdown() override;`
- L39 _public prototype_ `virtual IConcertServerRef GetConcertServer() const override;`
- L40 _public prototype_ `virtual void SetFileSharingService(TSharedPtr<IConcertFileSharingService> InFileSharingService) override;`
- L41 _public prototype_ `virtual TOptional<FConcertSyncSessionDatabaseNonNullPtr> GetLiveSessionDatabase(const FGuid& SessionId) override;`
- L42 _public prototype_ `virtual TOptional<FConcertSyncSessionDatabaseNonNullPtr> GetArchivedSessionDatabase(const FGuid& SessionId) override;`
- L45 _public prototype_ `void GetSessionsFromPathImpl(const IConcertServer& InServer, const FString& InPath, TArray<FConcertSessionInfo>& OutSessionInfos, TArray<FDateTime>* OutSessionCreationTimes = nullptr);`
- L46 _public prototype_ `bool OnLiveSessionCreatedImpl(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession, const FInternalLiveSessionCreationParams& AdditionalParams);`
- L47 _public prototype_ `void OnLiveSessionDestroyedImpl(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession);`
- L48 _public prototype_ `bool OnArchivedSessionCreatedImpl(const IConcertServer& InServer, const FString& InArchivedSessionRoot, const FConcertSessionInfo& InArchivedSessionInfo);`
- L49 _public prototype_ `void OnArchivedSessionDestroyedImpl(const IConcertServer& InServer, const FGuid& InArchivedSessionId);`
- L50 _public prototype_ `bool ArchiveSessionImpl(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession, const FString& InArchivedSessionRoot, const FConcertSessionInfo& InArchivedSessionInfo, const FConcertSessionFilter& InSessionFilter);`
- L51 _public prototype_ `bool ArchiveSessionImpl(const IConcertServer& InServer, const FString& InLiveSessionWorkingDir, const FString& InArchivedSessionRoot, const FConcertSessionInfo& InArchivedSessionInfo, const FConcertSessionFilter& InSessionFilter);`
- L52 _public prototype_ `bool CopySessionImpl(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession, const FString& NewSessionRoot, const FConcertSessionFilter& InSessionFilter);`
- L53 _public prototype_ `bool ExportSessionImpl(const IConcertServer& InServer, const FGuid& InSessionId, const FString& DestDir, const FConcertSessionFilter& InSessionFilter, bool bAnonymizeData);`
- L54 _public prototype_ `bool RestoreSessionImpl(const IConcertServer& InServer, const FGuid& InArchivedSessionId, const FString& InLiveSessionRoot, const FConcertSessionInfo& InLiveSessionInfo, const FConcertSessionFilter& InSessionFilter);`
- L55 _public prototype_ `bool GetSessionActivitiesImpl(const IConcertServer& InServer, const FGuid& SessionId, int64 FromActivityId, int64 ActivityCount, TArray<FConcertSessionSerializedPayload>& OutActivities, TMap<FGuid, FConcertClientInfo>& OutEndpointClientInfoMap, bool bIncludeDetails);`
- L56 _public prototype_ `void OnLiveSessionRenamedImpl(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession);`
- L57 _public prototype_ `void OnArchivedSessionRenamedImpl(const IConcertServer& InServer, const FString& InArchivedSessionRoot, const FConcertSessionInfo& InArchivedSessionInfo);`
- L61 _private prototype_ `TSharedRef<FConcertServerWorkspace> CreateWorkspace(const TSharedRef<FConcertSyncServerLiveSession>& InLiveSession);`
- L62 _private prototype_ `void DestroyWorkspace(const TSharedRef<FConcertSyncServerLiveSession>& InLiveSession);`
- L64 _private prototype_ `void CreateSequencerManager(const TSharedRef<FConcertSyncServerLiveSession>& InLiveSession);`
- L65 _private prototype_ `void DestroySequencerManager(const TSharedRef<FConcertSyncServerLiveSession>& InLiveSession);`
- L73 _private prototype_ `void CreateReplicationManager( const TSharedRef<IConcertServerSession>& InSession, UE::ConcertSyncServer::Replication::IReplicationWorkspace& InWorkspace, EConcertSyncSessionFlags InSessionFlags );` — Initializes the replication manager for the given session. @param InSession The session to bind the manager to @param InWorkspace The database interface that manager interacts with. The caller ensures it outlives the lifetime of the widget. @param InSessionFlags Session flags, which determine optional features.
- L77 _private prototype_ `void DestroyReplicationManager(const FGuid& SessionId);`
- L79 _private prototype_ `bool CreateLiveSession(const TSharedRef<IConcertServerSession>& InSession, const FInternalLiveSessionCreationParams& AdditionalParams);`
- L80 _private prototype_ `void DestroyLiveSession(const TSharedRef<IConcertServerSession>& InSession);`
- L82 _private prototype_ `bool CreateArchivedSession(const FString& InArchivedSessionRoot, const FConcertSessionInfo& InArchivedSessionInfo);`
- L83 _private prototype_ `void DestroyArchivedSession(const FGuid& InArchivedSessionId);`
- L85 _private prototype_ `bool GetSessionActivitiesInternal(const FConcertSyncSessionDatabase& Database, int64 FromActivityId, int64 ActivityCount, TArray<FConcertSessionSerializedPayload>& OutActivities, TMap<FGuid, FConcertClientInfo>& OutEndpointClientInfoMap, bool bIncludeDetails);`
- L88 _private member_ `IConcertServerRef ConcertServer;` — Server for Concert
- L91 _private member_ `EConcertSyncSessionFlags SessionFlags;` — Flags controlling what features are enabled for sessions within this server
- L94 _private member_ `TMap<FGuid, TSharedPtr<FConcertServerWorkspace>> LiveSessionWorkspaces;` — Map of live session IDs to their associated workspaces
- L97 _private member_ `TMap<FGuid, TSharedPtr<FConcertServerSequencerManager>> LiveSessionSequencerManagers;` — Map of live session IDs to their associated sequencer managers
- L100 _private member_ `TMap<FGuid, TSharedRef<UE::ConcertSyncServer::Replication::FConcertServerReplicationManager>> LiveSessionReplicationManagers;` — Map of live session IDs to their associated replication managers
- L103 _private member_ `TMap<FGuid, TSharedPtr<FConcertSyncServerLiveSession>> LiveSessions;` — Map of live session IDs to their associated session data
- L106 _private member_ `TMap<FGuid, TSharedPtr<FConcertSyncServerArchivedSession>> ArchivedSessions;` — Map of archived session IDs to their associated session data
- L109 _private member_ `FAutoConsoleCommand LogReplicationStreamsConsoleCommand;` — Logs the replication streams registered by all clients
- L111 _private member_ `FAutoConsoleCommand LogReplicationAuthorityConsoleCommand;` — Logs the replication authority of the clients
- L114 _private prototype_ `void LogReplicationStreams() const;` — Logs the replication streams registered by all clients
- L116 _private prototype_ `void LogReplicationAuthority() const;` — Logs the replication authority of the clients

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L18 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/ConcertSyncServerArchivedSession.h` (Private)


#### class `FConcertSyncServerArchivedSession`  
`class FConcertSyncServerArchivedSession`  
_L10-70_
- L13 _public prototype_ `FConcertSyncServerArchivedSession(const FString& InSessionRootPath, const FConcertSessionInfo& InSessionInfo);`
- L14 _public prototype_ `~FConcertSyncServerArchivedSession();`
- L16 _public prototype_ `FConcertSyncServerArchivedSession(const FConcertSyncServerArchivedSession&) = delete;`
- L17 _public prototype_ `FConcertSyncServerArchivedSession& operator=(const FConcertSyncServerArchivedSession&) = delete;`
- L19 _public prototype_ `FConcertSyncServerArchivedSession(FConcertSyncServerArchivedSession&&) = delete;`
- L20 _public prototype_ `FConcertSyncServerArchivedSession& operator=(FConcertSyncServerArchivedSession&&) = delete;`
- L23 _public prototype_ `bool IsValidSession() const;` — Is this a valid session? (ie, has been successfully opened)
- L26 _public function_ `const FGuid& GetId() const` — Get the ID of this archived session
- L32 _public function_ `const FString& GetName() const` — Get the name of this archived session
- L38 _public function_ `const FConcertSessionInfo& GetSessionInfo() const` — Get the information about this archived session
- L44 _public function_ `FString GetSessionWorkingDirectory() const` — Get the root path of this archived session
- L50 _public function_ `FConcertSyncSessionDatabase& GetSessionDatabase()` — Get the database for this archived session (if IsValidSession)
- L56 _public function_ `const FConcertSyncSessionDatabase& GetSessionDatabase() const` — Get the database for this archived session (if IsValidSession)
- L63 _private member_ `FString SessionRootPath;` — Root path of this archived session
- L66 _private member_ `FConcertSessionInfo SessionInfo;` — Information about this archived session
- L69 _private member_ `TUniquePtr<FConcertSyncSessionDatabase> SessionDatabase;` — Database for this archived session

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/ConcertSyncServerLiveSession.h` (Private)


#### class `FConcertSyncServerLiveSession`  
`class FConcertSyncServerLiveSession`  
_L12-66_
- L15 _public prototype_ `FConcertSyncServerLiveSession(const TSharedRef<IConcertServerSession>& InSession, const EConcertSyncSessionFlags InSessionFlags);`
- L16 _public prototype_ `~FConcertSyncServerLiveSession();`
- L18 _public prototype_ `FConcertSyncServerLiveSession(const FConcertSyncServerLiveSession&) = delete;`
- L19 _public prototype_ `FConcertSyncServerLiveSession& operator=(const FConcertSyncServerLiveSession&) = delete;`
- L21 _public prototype_ `FConcertSyncServerLiveSession(FConcertSyncServerLiveSession&&) = delete;`
- L22 _public prototype_ `FConcertSyncServerLiveSession& operator=(FConcertSyncServerLiveSession&&) = delete;`
- L25 _public prototype_ `bool IsValidSession() const;` — Is this a valid session? (ie, has been successfully opened)
- L28 _public function_ `IConcertServerSession& GetSession()` — Get the underlying live session (if IsValidSession)
- L34 _public function_ `const IConcertServerSession& GetSession() const` — Get the underlying live session (if IsValidSession)
- L40 _public function_ `EConcertSyncSessionFlags GetSessionFlags() const` — Get the flags controlling what features are enabled for this live session
- L46 _public function_ `FConcertSyncSessionDatabase& GetSessionDatabase()` — Get the database for this live session (if IsValidSession)
- L52 _public function_ `const FConcertSyncSessionDatabase& GetSessionDatabase() const` — Get the database for this live session (if IsValidSession)
- L59 _private member_ `TSharedRef<IConcertServerSession> Session;` — The underlying live session
- L62 _private member_ `EConcertSyncSessionFlags SessionFlags;` — Flags controlling what features are enabled for this live session
- L65 _private member_ `TUniquePtr<FConcertSyncSessionDatabase> SessionDatabase;` — Database for this live session

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/AuthorityManager.h` (Private)


#### class `UE::ConcertSyncServer::Replication::FAuthorityManager`  
`class FAuthorityManager : public FNoncopyable`  
_L31-147_
- inherits: `FNoncopyable`
- desc: Responds to FConcertChangeAuthority_Request and tracks what objects and properties clients have authority over.
- L35 _public typedef_ `using FStreamId = FGuid;`
- L36 _public typedef_ `using FClientId = FGuid;`
- L37 _public typedef_ `using FProcessAuthorityConflict = TFunctionRef<EBreakBehavior(const FClientId& ClientId, const FStreamId& StreamId, const FConcertPropertyChain& WrittenProperties)>;`
- L44 _public prototype_ `FAuthorityManager(IRegistrationEnumerator& InGetters UE_LIFETIMEBOUND, TSharedRef<IConcertSession> InSession);` — @param InGetters Gets information about clients' registered streams @param InSession The session to handle authority requests on @param InGenerateSyncControlDelegate Called to fill the sync control portion of FConcertReplication_ChangeAuthority_Response.
- L45 _public prototype_ `~FAuthorityManager();`
- L51 _public prototype_ `bool HasAuthorityToChange(const FConcertReplicatedObjectId& ObjectChange) const;` — Checks whether the client that sent the identified object had authority to send it. @return Whether the server should process the object change.
- L54 _public prototype_ `void EnumerateAuthority(const FClientId& ClientId, const FStreamId& StreamId, TFunctionRef<EBreakBehavior(const FSoftObjectPath& Object)> Callback) const;` — Utility for iterating authority a client has for a given stream.
- L56 _public prototype_ `TArray<FConcertObjectInStreamID> GetOwnedObjects(const FClientId& ClientId) const;` — Util for getting all client owned objects as array.
- L76 _public prototype_ `EAuthorityResult EnumerateAuthorityConflicts( const FConcertReplicatedObjectId& Object, const FConcertPropertySelection* OverrideProperties = nullptr, FProcessAuthorityConflict ProcessConflict = [](const FClientId&, const FStreamId&, const FConcertPropertyChain&){ return EBreakBehavior::Break; } ) const;` — Enumerates all authority conflicts, if any, that would occur if ObjectChange.SenderEndpointId were to take authority over the identified object. You can optionally supply OverwriteProperties, which is useful if you're about to change the contents of the stream. @param Object Identifies the object, its stream and client that will send the object. Conflicts are checked against this. @param OverrideProperties Optional properties that Object will have and conflicts should be checked against. If not overriden, falls back to the properties registered thus far. @param ProcessConflict Invoked for the potential conflicts @return Whether there were any conflicts
- L79 _public function_ `const FConcertReplicatedObjectId& Object, const FConcertPropertySelection* OverrideProperties = nullptr, FProcessAuthorityConflict ProcessConflict = [](const FClientId&, const FStreamId&, const FConcertPropertyChain&)`
- L82 _public prototype_ `bool CanTakeAuthority(const FConcertReplicatedObjectId& Object) const;` — Whether it is legal for this the client identified by ClientId to take control over the object given the stream the client has registered.
- L96 _public prototype_ `EAuthorityResult EnumerateAuthorityConflictsWithOverrides( const FConcertReplicatedObjectId& Object, const TMap<FGuid, FConcertReplicationStreamArray>& StreamOverrides, const TMap<FGuid, FConcertObjectInStreamArray>& AuthorityOverrides, FProcessAuthorityConflict ProcessConflict = [](const FClientId&, const FStreamId&, const FConcertPropertyChain&){ return EBreakBehavior::Break; } ) const;` — Enumerates all authority conflicts, if any, that would occur if ObjectChange.SenderEndpointId were to take authority over the identified object. This version allows you to override the entire session content (compared to EnumerateAuthorityConflicts, which only allows you to specify OverwriteProperties). @param Object Identifies the object, its stream and client that will send the object. Conflicts are checked against this. @param StreamOverrides Overrides that the stream content of connected clients. If a client is not overriden, falls back to the content registered thus far. The key can be non-existing clients if you want to validate no conflicts were to occur if some other clients were present("injection"). @param AuthorityOverrides Overrides the authority of connected and "injected" clients. If a client is not overriden, falls back to the authority registered thus far. @param ProcessConflict Invoked for the potential conflicts @return Whether there were any conflicts
- L100 _public function_ `const FConcertReplicatedObjectId& Object, const TMap<FGuid, FConcertReplicationStreamArray>& StreamOverrides, const TMap<FGuid, FConcertObjectInStreamArray>& AuthorityOverrides, FProcessAuthorityConflict ProcessConflict = [](const FClientId&, const FStreamId&, const FConcertPropertyChain&)`
- L104 _public prototype_ `void OnPostClientLeft(const FClientId& ClientEndpointId);` — Notifies this manager that the client has left, which means all their authority is now gone.
- L106 _public prototype_ `void RemoveAuthority(const FConcertReplicatedObjectId& Object);` — Takes away authority from the given client from the given object.
- L109 _public function_ `void ApplyChangeAuthorityRequest(const FClientId& EndpointId, const FConcertReplication_ChangeAuthority_Request& Request, TMap<FSoftObjectPath, FConcertStreamArray>& OutRejectedObjects, FConcertReplication_ChangeSyncControl& OutChangedSyncControl)` — Applies a change authority request as if EndpointId had sent it.
- L114 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FConcertReplication_ChangeSyncControl, FGenerateSyncControl, const FGuid& ClientId);`
- L116 _public function_ `FGenerateSyncControl& OnGenerateSyncControl()` — Sets the delegate that is called to fill the sync control portion of FConcertReplication_ChangeAuthority_Response.
- L121 _private member_ `IRegistrationEnumerator& Getters;` — Callbacks required to obtain client info.
- L123 _private member_ `TSharedRef<IConcertSession> Session;` — The session under which this manager operates.
- L130 _private member_ `TMap<FClientId, FClientAuthorityData> ClientAuthorityData;`
- L133 _private member_ `FGenerateSyncControl GenerateSyncControlDelegate;` — Called to fill the sync control portion of FConcertReplication_ChangeAuthority_Response.
- L135 _private prototype_ `EConcertSessionResponseCode HandleChangeAuthorityRequest( const FConcertSessionContext& Context, const FConcertReplication_ChangeAuthority_Request& Request, FConcertReplication_ChangeAuthority_Response& Response );`
- L140 _private prototype_ `void InternalApplyChangeAuthorityRequest( const FClientId& EndpointId, const FConcertReplication_ChangeAuthority_Request& Request, TMap<FSoftObjectPath, FConcertStreamArray>& OutRejectedObjects, FConcertReplication_ChangeSyncControl& OutChangedSyncControl, bool bShouldLog = true );`

#### enum `UE::ConcertSyncServer::Replication::FAuthorityManager::EAuthorityResult`  
`enum class EAuthorityResult : uint8`  
_L58-66_
- L61 _public enumerator_ `Allowed` — The client is allowed to take authority
- L63 _public enumerator_ `Conflict` — There was at least one conflict
- L65 _public enumerator_ `NoRegisteredProperties` — No conflicts were checked because OverwriteProperties was nullptr and the client had not registered any properties to send for the given object.

#### struct `UE::ConcertSyncServer::Replication::FAuthorityManager::FClientAuthorityData`  
`struct FClientAuthorityData`  
_L125-129_
- L128 _public member_ `TMap<FStreamId, TSet<FSoftObjectPath>> OwnedObjects;` — Objects the client has authority over.

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L28 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)
- L114 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FConcertReplication_ChangeSyncControl, FGenerateSyncControl, const FGuid& ClientId);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/ConcertReplicationClient.h` (Private)


#### class `UE::ConcertSyncServer::Replication::FConcertReplicationClient`  
`class FConcertReplicationClient : public FNoncopyable`  
_L25-64_
- inherits: `FNoncopyable`
- desc: Server-side representation of a remote replication client.
- L29 _public prototype_ `FConcertReplicationClient( TArray<FConcertReplicationStream> StreamDescriptions, const FGuid& ClientEndpointId, IConcertSession& Session UE_LIFETIMEBOUND, ConcertSyncCore::FObjectReplicationCache& ReplicationCache UE_LIFETIMEBOUND, ConcertSyncCore::FGetObjectFrequencySettings GetObjectFrequencySettingsDelegate );`
- L41 _public prototype_ `void ProcessClient(const ConcertSyncCore::FProcessObjectsParams& Params);` — Process any latent tasks, such as processing pending events that need to be sent to the remote instance. Process given a time budget. The time budget may be exceeded but we'll try not to and to stay as close to the budget as possible.
- L44 _public prototype_ `void ApplyValidatedRequest(const FConcertReplication_ChangeStream_Request& Request);` — Updates the StreamDescriptions array with the changes from Request. The request already passed validation and is valid to apply.
- L46 _public function_ `const FGuid& GetClientEndpointId() const`
- L47 _public function_ `const TArray<FConcertReplicationStream>& GetStreamDescriptions() const`
- L52 _private member_ `TArray<FConcertReplicationStream> StreamDescriptions;` — The streams this client offered to send.
- L55 _private member_ `const FGuid ClientEndpointId;` — This client's endpoint ID.
- L58 _private member_ `TSharedRef<FServerReplicationDataQueuer> EventQueue;` — Queues up replication data and passes it to DataRelay.
- L61 _private typedef_ `using FDataRelayThrottledByFrequency = ConcertSyncCore::TObjectProcessorProxy_Frequency<ConcertSyncCore::FObjectReplicationSender>;` — Sends to remote endpoint and makes sure the objects are replicated at the specified frequency settings.
- L63 _private member_ `FDataRelayThrottledByFrequency DataRelay;` — Sends data to the remote endpoint

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L20 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/ConcertServerReplicationManager.h` (Private)


#### class `UE::ConcertSyncServer::Replication::FConcertServerReplicationManager`  
`class FConcertServerReplicationManager : public IConcertServerReplicationManager , public IRegistrationEnumerator , public FNoncopyable`  
_L58-190_
- inherits: `IConcertServerReplicationManager,IRegistrationEnumerator,FNoncopyable`
- desc: Manages all server-side systems relevant to the Replication features. Primarily responds to client requests to join (handshake) and leave replication delegating the result of the operation to relevant systems.
- L65 _public prototype_ `explicit FConcertServerReplicationManager(TSharedRef<IConcertServerSession> InLiveSession, IReplicationWorkspace& InServerWorkspace UE_LIFETIMEBOUND, EConcertSyncSessionFlags InSessionFlags);`
- L68 _public function_ `const FAuthorityManager& GetAuthorityManager() const`
- L71 _public prototype_ `virtual void ForEachStream(const FGuid& ClientEndpointId, TFunctionRef<EBreakBehavior(const FConcertReplicationStream& Stream)> Callback) const override;`
- L75 _public prototype_ `virtual void ForEachReplicationClient(TFunctionRef<EBreakBehavior(const FGuid& ClientEndpointId)> Callback) const override;`
- L81 _private member_ `const TSharedRef<IConcertServerSession> Session;` — Session instance this manager was created for.
- L83 _private member_ `IReplicationWorkspace& ServerWorkspace;` — Used to produce replication activities.
- L85 _private member_ `const EConcertSyncSessionFlags SessionFlags;` — Used to determine which dynamic features are enabled.
- L88 _private member_ `TUniquePtr<ConcertSyncCore::IObjectReplicationFormat> ReplicationFormat;` — Responsible for analysing received replication data.
- L96 _private member_ `ConcertSyncCore::FReplicatedObjectHierarchyCache ServerObjectCache;` — Holds the outer hierarchy of all objects registered in any stream. This receives join, leave, and change stream events. The events are processed after the mute manager does.
- L99 _private member_ `FAuthorityManager AuthorityManager;` — Responds to client requests to changing authority and can be asked whether an object change is valid to take place.
- L101 _private member_ `FMuteManager MuteManager;` — Responds to client mute requests and stores the mute states.
- L103 _private member_ `FSyncControlManager SyncControlManager;` — Decides whether clients should be replicating. Clients may replicate when they have authority and there are other clients listening for that data.
- L106 _private member_ `const TSharedRef<ConcertSyncCore::FObjectReplicationCache> ReplicationCache;` — Received replication events are put into the ReplicationCache. The cache is used to relay data to clients latently.
- L108 _private member_ `FServerObjectReplicationReceiver ReplicationDataReceiver;` — Receives replication events from all endpoints.
- L114 _private member_ `TMap<FGuid, TUniquePtr<FConcertReplicationClient>> Clients;` — Clients that have requested to join replication. Maps client ID to replication info. Clients are stored in a unique ptr to avoid dealing with reallocations when the map resizes.
- L117 _private prototype_ `EConcertSessionResponseCode HandleJoinReplicationSessionRequest(const FConcertSessionContext& ConcertSessionContext, const FConcertReplication_Join_Request& Request, FConcertReplication_Join_Response& Response);` — Joining
- L118 _private prototype_ `EConcertSessionResponseCode InternalHandleJoinReplicationSessionRequest(const FConcertSessionContext& ConcertSessionContext, const FConcertReplication_Join_Request& Request, FConcertReplication_Join_Response& Response);`
- L121 _private prototype_ `EConcertSessionResponseCode HandleQueryReplicationInfoRequest(const FConcertSessionContext& ConcertSessionContext, const FConcertReplication_QueryReplicationInfo_Request& Request, FConcertReplication_QueryReplicationInfo_Response& Response);` — Querying
- L123 _private prototype_ `static TArray<FConcertBaseStreamInfo> BuildClientStreamInfo(const FConcertReplicationClient& Client, EConcertQueryClientStreamFlags QueryFlags);` — Gets all registered streams and optionally removes the properties.
- L125 _private prototype_ `TArray<FConcertAuthorityClientInfo> BuildClientAuthorityInfo(const FConcertReplicationClient& Client) const;` — Maps the client's streams to the objects in that stream the client has taken authority over.
- L128 _private prototype_ `EConcertSessionResponseCode HandleChangeStreamRequest(const FConcertSessionContext& ConcertSessionContext, const FConcertReplication_ChangeStream_Request& Request, FConcertReplication_ChangeStream_Response& Response);` — Changing streams
- L130 _private prototype_ `void ApplyChangeStreamRequest(const FConcertReplication_ChangeStream_Request& Request, FConcertReplicationClient& Client);` — Applies a validated change stream request.
- L133 _private prototype_ `EConcertSessionResponseCode HandleRestoreContentRequest(const FConcertSessionContext& ConcertSessionContext, const FConcertReplication_RestoreContent_Request& Request, FConcertReplication_RestoreContent_Response& Response);` — Restoring content
- L135 _private prototype_ `TTuple<EConcertReplicationRestoreErrorCode, TOptional<FConcertSyncReplicationPayload_LeaveReplication>> ValidateRestoreContentRequest(const FGuid& RequestingEndpointId, const FConcertReplication_RestoreContent_Request& Request) const;` — @return Response code to return for the request and the payload to apply, if there is anything that should be applied.
- L137 _private prototype_ `void ApplyRestoreContentRequest(const FGuid& RequestingEndpointId, const FConcertReplication_RestoreContent_Request& Request, const FConcertSyncReplicationPayload_LeaveReplication& DataToApply, FConcertReplication_ChangeSyncControl& ChangedSyncControl);` — Applies a validated restore content request.
- L139 _private prototype_ `void RestoreStreamContent(const FConcertReplication_RestoreContent_Request& Request, const FConcertSyncReplicationPayload_LeaveReplication& DataToApply, FConcertReplicationClient& Client, FConcertReplication_ChangeSyncControl& OutChangedSyncControl);` — Restores the stream content in DataToApply to Client according to how Request specifies it.
- L141 _private prototype_ `void RestoreAuthority(const FConcertSyncReplicationPayload_LeaveReplication& DataToApply, const FConcertReplicationClient& Client, FConcertReplication_ChangeSyncControl& OutChangedSyncControl);` — Restores the authority in DataToApply to Client.
- L144 _private prototype_ `void RestoreMuteState(const FConcertReplicationClient& Client, FConcertReplication_ChangeSyncControl& OutChangedSyncControl);` — Restores the mute state of Client.
- L145 _private prototype_ `void ApplyRestoringMuteRequest(const FConcertReplicationClient& Client, const FConcertReplication_ChangeMuteState_Request& AggregatedRequest, FConcertReplication_ChangeSyncControl& OutChangedSyncControl);`
- L148 _private prototype_ `EConcertSessionResponseCode HandlePutStateRequest(const FConcertSessionContext& Context, const FConcertReplication_PutState_Request& Request, FConcertReplication_PutState_Response& Response);` — Changing multiple clients in one go
- L149 _private prototype_ `void ApplyPutStateRequest( const FGuid& RequestingEndpointId, const FConcertReplication_PutState_Request& Request, const TMap<FGuid, FConcertReplication_ChangeStream_Request> StreamRequests, FConcertReplication_PutState_Response& Response );`
- L155 _private prototype_ `void ApplyPutState_Streams( const FGuid& RequestingEndpointId, const TMap<FGuid, FConcertReplication_ChangeStream_Request> StreamRequests, TMap<FGuid, FConcertReplication_ClientChangeData>& ClientChanges );`
- L160 _private prototype_ `void ApplyPutState_Authority( const FGuid& RequestingEndpointId, const TSet<FConcertObjectInStreamID> RequestingClientSyncControlBefore, const FConcertReplication_PutState_Request& Request, FConcertReplication_PutState_Response& Response, TMap<FGuid, FConcertReplication_ClientChangeData>& ClientChanges );`
- L169 _private prototype_ `void HandleLeaveReplicationSessionRequest(const FConcertSessionContext& ConcertSessionContext, const FConcertReplication_LeaveEvent& EventData);` — Leaving
- L170 _private prototype_ `void OnConnectionChanged(IConcertServerSession& ConcertServerSession, EConcertClientStatus ConcertClientStatus, const FConcertSessionClientInfo& ConcertSessionClientInfo);`
- L173 _private prototype_ `void OnClientLeftReplication(const FGuid& EndpointId);` — Cleans up the client's replication state after leaving.
- L175 _private prototype_ `void ProduceClientLeftActivity(const FConcertReplicationClient& Client) const;` — Calls FConcertServerWorkspace::AddReplicationActivity with the current client state, so it can be restored upon re-joining.
- L178 _private prototype_ `void GenerateMuteActivity(const FGuid& EndpointId, const FConcertReplication_ChangeMuteState_Request& Request) const;` — Generates an activity for a mute request
- L186 _private prototype_ `void Tick(IConcertServerSession& InSession, float InDeltaTime);` — Ticks all clients which causes clients to process pending data and send it to the corresponding endpoints. There is an internal time budget to ensure ticks do not starve the server's other tick tasks. This is configured in an .ini. TODO: Add config
- L189 _private prototype_ `FConcertObjectReplicationSettings GetObjectFrequencySettings(const FConcertReplicatedObjectId& Object) const;` — Callback to clients for obtaining an object's frequency settings.

#### Free symbols / members of external scopes

- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L47 _namespace_ `namespace UE`
- L47 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L47 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/Enumeration/IClientEnumerator.h` (Private)


#### class `UE::ConcertSyncServer::Replication::IClientEnumerator`  
`class IClientEnumerator`  
_L14-22_
- desc: Iterates through all clients have registered to send any data.
- L19 _public prototype_ `virtual void ForEachReplicationClient(TFunctionRef<EBreakBehavior(const FGuid& ClientEndpointId)> Callback) const = 0;` — Iterates through all clients have registered to send any data.
- L21 _public prototype_ `virtual ~IClientEnumerator() = default;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/Enumeration/IRegistrationEnumerator.h` (Private)


#### class `UE::ConcertSyncServer::Replication::IRegistrationEnumerator`  
`class IRegistrationEnumerator : public IStreamEnumerator, public IClientEnumerator`  
_L10-11_
- inherits: `IStreamEnumerator,IClientEnumerator`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L8 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/Enumeration/IStreamEnumerator.h` (Private)


#### class `UE::ConcertSyncServer::Replication::IStreamEnumerator`  
`class IStreamEnumerator`  
_L14-22_
- desc: Provides a way to extract all streams registered to a given client.
- L19 _public prototype_ `virtual void ForEachStream(const FGuid& ClientEndpointId, TFunctionRef<EBreakBehavior(const FConcertReplicationStream& Stream)> Callback) const = 0;` — Provides a way to extract all streams registered to a given client.
- L21 _public prototype_ `virtual ~IStreamEnumerator() = default;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/Muting/IMuteValidationObjectHierarchy.h` (Private)


#### class `UE::ConcertSyncServer::Replication::IMuteValidationObjectHierarchy`  
`class IMuteValidationObjectHierarchy`  
_L20-44_
- desc: Interface required by FMuteManager to validate a FConcertReplication_ChangeMuteState_Request. This encapsulates the server's knowledge of replicated objects. It is useful if you have a complicated series of requests that will mutate the server state if applied, but you want to first validate that a mute request is valid to apply on that state. In that case, you can implement this to return the future server state.
- L35 _public prototype_ `virtual bool IsObjectReferencedDirectly(const FSoftObjectPath& ObjectPath, TConstArrayView<FGuid> IgnoredClients = {}) const = 0;` — Checks whether the object is registered by any client (except for this in IgnoredClients). This function ignores implicit knowledge of the hierarchy. For example if you register ONLY /Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent0, then - IsObjectReferencedDirectly(/Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent0) == true, - IsObjectReferencedDirectly(/Game/Maps.Map:PersistentLevel.Cube) == false but e.g. TraverseTopToBottom would list both paths. @see FReplicatedObjectHierarchyCache::IsObjectReferencedDirectly
- L41 _public prototype_ `virtual bool HasChildren(const FSoftObjectPath& Object) const = 0;` — @return Whether Object has any subobjects in the hierarchy. @see FObjectPathHierarchy::HasChildren
- L43 _public prototype_ `virtual ~IMuteValidationObjectHierarchy() = default;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/Muting/MuteManager.h` (Private)


#### class `UE::ConcertSyncServer::Replication::FMuteManager`  
`class FMuteManager : public FNoncopyable`  
_L43-210_
- inherits: `FNoncopyable`
- desc: Manages the session's replication mute state. Handles FConcertReplication_ChangeMuteState_Request and FConcertReplication_QueryMuteState_Request requets.
- L47 _public typedef_ `using FOnSyncControlChange = TFunctionRef<void(const FGuid& ClientId, FConcertReplication_ChangeSyncControl&& SyncControlChange)>;`
- L49 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnMuteStateChangedByClient, const FGuid& ClientId);`
- L50 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FConcertReplication_ChangeSyncControl, FRefreshSyncControlForMuteChange, const FGuid& ClientId);`
- L51 _public prototype_ `DECLARE_DELEGATE_OneParam(FRefreshSyncControlForClients, const FOnSyncControlChange& OnSyncControlChange);`
- L54 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMuteRequestApplied, const FGuid& ClientId, const FConcertReplication_ChangeMuteState_Request& Request);` — Notifies manager about applied event. Generates mute activity.
- L69 _public prototype_ `FMuteManager( IConcertSession& InSession UE_LIFETIMEBOUND, const ConcertSyncCore::FReplicatedObjectHierarchyCache& ServerObjectCache UE_LIFETIMEBOUND, EConcertSyncSessionFlags InSessionFlags );`
- L74 _public prototype_ `~FMuteManager();`
- L77 _public prototype_ `bool IsMuted(const FSoftObjectPath& Object) const;` — @return Whether the object is globally muted.
- L80 _public prototype_ `TOptional<EMuteState> GetMuteState(const FSoftObjectPath& Object) const;` — @return The mute state of Object. If it was not explicitly muted and no parent object affects this subobject, then the optional is unset.
- L82 _public prototype_ `TOptional<FConcertReplication_ObjectMuteSetting> GetExplicitMuteSetting(const FSoftObjectPath& Object) const;` — @return The mute setting of Object, if it is explicitly set (i.e. not affected by a parent object).
- L90 _public prototype_ `bool ValidateRequest( const FConcertReplication_ChangeMuteState_Request& Request, const IMuteValidationObjectHierarchy* OverrideServerObjectCache = nullptr, TFunctionRef<void(const FSoftObjectPath& ObjectPath)> OnRejection = [](const FSoftObjectPath&){} ) const;` — Checks whether Request would be valid to apply, optionally providing a future server state. @param Request The request to validate @param OverrideServerObjectCache The server cache to use. Defaults to the internal one if left nullptr. Useful for passing in a future server state. @param OnRejection Called for every rejected object.
- L93 _public function_ `const FConcertReplication_ChangeMuteState_Request& Request, const IMuteValidationObjectHierarchy* OverrideServerObjectCache = nullptr, TFunctionRef<void(const FSoftObjectPath& ObjectPath)> OnRejection = [](const FSoftObjectPath&)`
- L104 _public prototype_ `bool ApplyRequestAndEnumerateSyncControl( const FConcertReplication_ChangeMuteState_Request& Request, const FOnSyncControlChange& OnSyncControlChange );` — This validates and then applies Request. This version does not send any sync control updates to other clients. You must update them yourself. @param Request The request to apply @param OnSyncControlChange Called for every sync control change that is made. @return Whether the request was applied.
- L112 _public prototype_ `FConcertReplication_ChangeSyncControl ApplyManualRequest(const FGuid& EndpointId, const FConcertReplication_ChangeMuteState_Request& Request);` — Applies Request as if it was sent by EndpointId. @return The sync control that the client identified by EndpointId has gained. Does NOT include the sync control they lost.
- L115 _public prototype_ `void PostApplyStreamChange(const FGuid& ClientId, TConstArrayView<FConcertObjectInStreamID> AddedObjects, TConstArrayView<FConcertObjectInStreamID> RemovedObjects);` — Called right after objects have been unregistered from ClientId's streams.
- L117 _public prototype_ `void OnPostClientLeft(const TArray<FConcertReplicationStream>& ClientStreams);` — Called by FConcertServerReplicationManager when client leaves replication.
- L120 _public function_ `FOnMuteStateChangedByClient& OnRefreshSyncControlForIndirectMuteChange()` — Updates sync control if needed in response to a client changing their mute state indirectly (e.g. because client removed object from their stream).
- L122 _public function_ `FRefreshSyncControlForMuteChange& OnRefreshSyncControlAndSendToAllClientsExcept()` — Updates sync control for all clients, sends an update to all clients but ClientId, and returns the sync control to embed into the mute response.
- L124 _public function_ `FRefreshSyncControlForClients& OnRefreshSyncControlButSkipSendingToClients()` — Updates sync control for all clients but does not send any update to any clients. The passed in callback receives all sync control changes for the clients.
- L126 _public function_ `FOnMuteRequestApplied& OnMuteRequestApplied()`
- L131 _private member_ `IConcertSession& Session;` — The session to receive requests on.
- L133 _private member_ `const ConcertSyncCore::FReplicatedObjectHierarchyCache& ServerObjectCache;` — Keeps track of all objects that are in client streams. Allows efficient traversing of subobject hierarchy.
- L136 _private member_ `const EConcertSyncSessionFlags SessionFlags;` — If ShouldAllowGlobalMuting is not set, the requests are not served.
- L139 _private member_ `FOnMuteStateChangedByClient OnMuteStateChangedDelegate;` — Broadcasts after the mute state has been changed.
- L146 _private member_ `FRefreshSyncControlForMuteChange OnRefreshSyncControlAndSendToAllClientsExceptDelegate;` — Delegate into FSyncControlManager Updates sync control for all clients, sends an update to all clients but ClientId, and returns the sync control to embed into the mute response. The sync control will only contain RestrictToObjects.
- L148 _private member_ `FRefreshSyncControlForClients OnRefreshSyncControlButSkipSendingToClientsDelegate;` — Delegate into FSyncControlManager.
- L151 _private member_ `FOnMuteRequestApplied OnMuteRequestAppliedDelegate;` — Broadcasts after a mute request has been applied.
- L172 _private member_ `TMap<FSoftObjectPath, FMuteData> MuteState;` — Holds the mute state of all objects. Objects only show up in this map if they are either explicitly or implicitly affected by a mute setting: - explicit means that a request listed them to be muted / unmuted - implicit means that a parent object (i.e. an outer) is explicitly muted or unmuted. Hence, if an object is not in this map it means that neither it nor any of its parents are explicitly/implicitly muted nor unmuted.
- L175 _private prototype_ `void TrackAddedSubobjectsForImplicitMuting(TConstArrayView<FConcertObjectInStreamID> AddedObjects);` — For each added object, checks whether it is a subobject of an object that is muted with the EConcertReplicationMuteFlags::ObjectAndSubobjects setting.
- L177 _private prototype_ `void UnmuteObjectsIfUnreferenced(TConstArrayView<FConcertObjectInStreamID> RemovedObjects);` — Calls RemoveMuteState on every object that is unreferenced by client streams (directly or indirectly via a subobject).
- L180 _private prototype_ `template<CObjectProcessable TCallback> void UnmuteObjectIfUnreferenced(const FSoftObjectPath& RemovedObject, TCallback&& OnRemoved);` — Calls RemoveMuteState if RemovedObject is unreferenced by client streams (directly or indirectly via a subobject).
- L181 _private function_ `void UnmuteObjectIfUnreferenced(const FSoftObjectPath& RemovedObject)`
- L184 _private prototype_ `EConcertSessionResponseCode HandleQueryMuteStateRequest(const FConcertSessionContext& Context, const FConcertReplication_QueryMuteState_Request& Request, FConcertReplication_QueryMuteState_Response& Response);` — Handles requests to query mute states.
- L186 _private prototype_ `EConcertSessionResponseCode HandleChangeMuteStateRequest(const FConcertSessionContext& Context, const FConcertReplication_ChangeMuteState_Request& Request, FConcertReplication_ChangeMuteState_Response& Response);` — Handles requests to change the mute states
- L189 _private prototype_ `bool ValidateRequestInternal(const FConcertReplication_ChangeMuteState_Request& Request, FConcertReplication_ChangeMuteState_Response& Response) const;` — Checks whether Request is valid to apply.
- L191 _private prototype_ `bool ValidateRequestInternal(const FConcertReplication_ChangeMuteState_Request& Request, const IMuteValidationObjectHierarchy& ObjectCache, TFunctionRef<void(const FSoftObjectPath& ObjectPath)> OnRejection) const;` — Checks whether Request is valid to apply.
- L193 _private prototype_ `void ApplyRequestInternal(const FConcertReplication_ChangeMuteState_Request& Request);` — Updates the internal state (assuming it is a valid request - call ValidateRequest before).
- L197 _private prototype_ `template<CObjectProcessable TCallback> void RemoveMuteState(const FSoftObjectPath& Object, TCallback&& OnRemoved);` — Removes all mute state for Object and transitively updates subobjects if applicable.
- L198 _private function_ `void RemoveMuteState(const FSoftObjectPath& Object)`
- L201 _private prototype_ `void UpdateImplicitStateUnder(const FSoftObjectPath& Parent, EMuteState NewImplicitState);` — Sets the mute state of all subobjects of Parent until reaching a subobject that also has EConcertReplicationMuteFlags::ObjectAndSubobjects set.
- L205 _private prototype_ `template<CObjectProcessable TCallback> void ClearAllChildStateUnder(const FSoftObjectPath& ParentObject, TCallback&& OnRemoved);` — Removes all subobject mute state affected by Parent's mute state assuming that ParentObject has no parents with the EConcertReplicationMuteFlags::ObjectAndSubobjects.
- L206 _private function_ `void ClearAllChildStateUnder(const FSoftObjectPath& ParentObject)`
- L209 _private prototype_ `TPair<FSoftObjectPath, const FMuteData*> FindAffectingParentState(const FSoftObjectPath& Subobject) const;` — Walks up the object hierarchy and returns the parent that affects ObjectPath, if any.

#### enum `UE::ConcertSyncServer::Replication::FMuteManager::EMuteState`  
`enum class EMuteState : uint8`  
_L56-67_
- L59 _public enumerator_ `ExplicitlyMuted` — Object is muted
- L61 _public enumerator_ `ExplicitlyUnmuted` — A parent object is ExplicitlyMuted and has EConcertReplicationMuteFlags::ObjectAndSubobjects set but is object and its children are supposed to be implicitly unmuted.
- L64 _public enumerator_ `ImplicitlyMuted` — Object is muted because one of its parent objects is ExplicitlyMuted and EConcertReplicationMuteFlags::ObjectAndSubobjects set.
- L66 _public enumerator_ `ImplicitlyUnmuted` — Object is unmuted because one of its parent objects is ExplicitlyUnmuted and has EConcertReplicationMuteFlags::ObjectAndSubobjects set.

#### struct `UE::ConcertSyncServer::Replication::FMuteManager::FMuteData`  
`struct FMuteData`  
_L153-163_
- L156 _public member_ `TOptional<FConcertReplication_ObjectMuteSetting> MuteSetting;` — Only set if the object was explicitly muted or unmuted.
- L158 _public member_ `EMuteState State;`
- L160 _public function_ `bool IsExplicit() const`
- L161 _public function_ `bool IsImplicit() const`
- L162 _public function_ `bool AffectsSubobjects() const`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L22 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L26 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)
- L32 _function_ `EnumerateObjects([](const FConcertObjectInStreamID&){});` (scope `UE::ConcertSyncServer::Replication`)
- L49 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMuteStateChangedByClient, const FGuid& ClientId);`
- L50 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FConcertReplication_ChangeSyncControl, FRefreshSyncControlForMuteChange, const FGuid& ClientId);`
- L51 _delegate_ `DECLARE_DELEGATE_OneParam(FRefreshSyncControlForClients, const FOnSyncControlChange& OnSyncControlChange);`
- L54 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMuteRequestApplied, const FGuid& ClientId, const FConcertReplication_ChangeMuteState_Request& Request);` — Notifies manager about applied event. Generates mute activity.
- L181 _function_ `void UnmuteObjectIfUnreferenced(const FSoftObjectPath& RemovedObject)` (scope `UE::ConcertSyncServer::Replication::FMuteManager::UnmuteObjectIfUnreferenced`)
- L198 _function_ `void RemoveMuteState(const FSoftObjectPath& Object)` (scope `UE::ConcertSyncServer::Replication::FMuteManager::RemoveMuteState`)
- L206 _function_ `void ClearAllChildStateUnder(const FSoftObjectPath& ParentObject)` (scope `UE::ConcertSyncServer::Replication::FMuteManager::ClearAllChildStateUnder`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/Muting/ObjectHierarchyAdapter.h` (Private)


#### class `UE::ConcertSyncServer::Replication::FObjectHierarchyAdapter`  
`class FObjectHierarchyAdapter : public IMuteValidationObjectHierarchy`  
_L13-26_
- inherits: `IMuteValidationObjectHierarchy`
- desc: Simple adapter implementation that uses the server's current FReplicatedObjectHierarchyCache state.
- L15 _private member_ `const ConcertSyncCore::FReplicatedObjectHierarchyCache& ServerCache;`
- L18 _public function_ `FObjectHierarchyAdapter(const ConcertSyncCore::FReplicatedObjectHierarchyCache& ServerCache UE_LIFETIMEBOUND) : ServerCache(ServerCache)`
- L23 _public function_ `virtual bool IsObjectReferencedDirectly(const FSoftObjectPath& ObjectPath, TConstArrayView<FGuid> IgnoredClients) const override`
- L24 _public function_ `virtual bool HasChildren(const FSoftObjectPath& Object) const override`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L10 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/Muting/PredictedStateObjectHierarchy.h` (Private)


#### class `UE::ConcertSyncServer::Replication::FPredictedStateObjectHierarchy`  
`class FPredictedStateObjectHierarchy : public IMuteValidationObjectHierarchy`  
_L23-48_
- inherits: `IMuteValidationObjectHierarchy`
- desc: Implementation of IMuteValidationObjectHierarchy which allows you to add arbitrary client state. Primarily used to validate a hierarchy that clients WILL have in the future.
- L28 _public prototype_ `void AddClients(const TMap<FGuid, FConcertReplicationStreamArray>& Clients);` — Adds clients from a map binding client id to stream content.
- L31 _public prototype_ `template<typename TFilterLambda> requires std::is_invocable_r_v<bool, TFilterLambda, const FGuid&> void AddClients(const TMap<FGuid, TUniquePtr<FConcertReplicationClient>>& Clients, TFilterLambda&& ShouldIncludeFilter);` — Adds only those entries that pass ShouldIncludeFilter returns true on.
- L34 _public prototype_ `void AddClientData(const FGuid& ClientId, TConstArrayView<FConcertReplicationStream> Streams);` — Adds the streams a client will have.
- L37 _public prototype_ `virtual bool IsObjectReferencedDirectly(const FSoftObjectPath& ObjectPath, TConstArrayView<FGuid> IgnoredClients) const override;`
- L38 _public prototype_ `virtual bool HasChildren(const FSoftObjectPath& Object) const override;`
- L44 _private member_ `ConcertSyncCore::FObjectPathHierarchy Hierarchy;` — The hierarchy built during construction.
- L47 _private member_ `TMap<FSoftObjectPath, TArray<FGuid>> ObjectReferencingClients;` — Maps objects to the clients referencing them.
- L51 _function_ `template <typename TFilterLambda> requires std::is_invocable_r_v<bool, TFilterLambda, const FGuid&> void FPredictedStateObjectHierarchy::AddClients(const TMap<FGuid, TUniquePtr<FConcertReplicationClient>>& Clients, TFilterLambda&& ShouldIncludeFilter)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L15 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/Processing/ServerObjectReplicationReceiver.h` (Private)


#### class `UE::ConcertSyncServer::Replication::FServerObjectReplicationReceiver`  
`class FServerObjectReplicationReceiver : public ConcertSyncCore::FObjectReplicationReceiver`  
_L15-38_
- inherits: `ConcertSyncCore::FObjectReplicationReceiver`
- desc: Rejects changes to objects that the sending client does not have authority over.
- L19 _public prototype_ `FServerObjectReplicationReceiver( const FAuthorityManager& AuthorityManager UE_LIFETIMEBOUND, const FSyncControlManager& SyncControlManager UE_LIFETIMEBOUND, IConcertSession& Session UE_LIFETIMEBOUND, ConcertSyncCore::FObjectReplicationCache& ReplicationCache UE_LIFETIMEBOUND );`
- L29 _protected prototype_ `virtual bool ShouldAcceptObject(const FConcertSessionContext& SessionContext, const FConcertReplication_StreamReplicationEvent& StreamEvent, const FConcertReplication_ObjectReplicationEvent& ObjectEvent) const override;`
- L35 _private member_ `const FAuthorityManager& AuthorityManager;` — Used to determine whether a client has authority over objects.
- L37 _private member_ `const FSyncControlManager& SyncControlManager;` — Used to determine whether any client is listening to an incoming object.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L9 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/Processing/ServerReplicationDataQueuer.h` (Private)


#### class `UE::ConcertSyncServer::Replication::FServerReplicationDataQueuer`  
`class FServerReplicationDataQueuer : public ConcertSyncCore::FReplicationDataQueuer`  
_L18-36_
- inherits: `ConcertSyncCore::FReplicationDataQueuer`
- desc: Queues events for a specific client. TODO: Filters events by matching client and stream attributes.
- L24 _public prototype_ `static TSharedRef<FServerReplicationDataQueuer> Make(const FGuid& OwningClientEndpointId, ConcertSyncCore::FObjectReplicationCache& InReplicationCache UE_LIFETIMEBOUND);`
- L27 _public prototype_ `virtual bool WantsToAcceptObject(const FConcertReplicatedObjectId& Object) const override;`
- L32 _private prototype_ `FServerReplicationDataQueuer(const FGuid& OwningClientEndpointId);`
- L35 _private member_ `const FGuid OwningClientEndpointId;` — The client for which this FServerReplicationDataQueuer exists.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L10 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/ReplicationWorkspace.h` (Private)


#### class `UE::ConcertSyncServer::FReplicationWorkspace`  
`class FReplicationWorkspace : public Replication::IReplicationWorkspace`  
_L25-56_
- inherits: `Replication::IReplicationWorkspace`
- desc: Implements the replication workspace server-side. At runtime, this is created by FConcertServerWorkspace. This exists as independent class so it can be unit-tested.
- L29 _public prototype_ `FReplicationWorkspace( FConcertSyncSessionDatabase& Database UE_LIFETIMEBOUND, FFindSessionClient InFindSessionClientDelegate, FShouldIgnoreClientActivityOnRestore InShouldIgnoreClientActivityOnRestoreDelegate );`
- L36 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAddReplicationActivity, int64 ActivityId, bool bSuccess);` — Called when an activity is added to the database.
- L37 _public function_ `FOnAddReplicationActivity& OnAddReplicationActivity()`
- L40 _public prototype_ `virtual TOptional<int64> ProduceReplicationActivity(const FGuid& EndpointId, const FConcertSyncReplicationEvent& EventData) override;`
- L41 _public prototype_ `virtual bool GetLastReplicationActivityByClient(const FConcertSessionClientInfo& InClientInfo, EConcertSyncReplicationActivityType ActivityType, FConcertSyncReplicationActivity& OutActivity) const override;`
- L42 _public prototype_ `virtual bool GetReplicationEventById(const int64 ActivityId, FConcertSyncReplicationEvent& OutEvent) const override;`
- L43 _public prototype_ `virtual void EnumerateReplicationActivities(TFunctionRef<EBreakBehavior(const FConcertSyncReplicationActivity& Activity)> Callback) const override;`
- L49 _private member_ `FConcertSyncSessionDatabase& Database;` — Needed to get replication data.
- L51 _private member_ `const FFindSessionClient FindSessionClientDelegate;` — Needed by GetLastLeaveReplicationActivityByClient to get the most appropriate activity data.
- L53 _private member_ `const FShouldIgnoreClientActivityOnRestore ShouldIgnoreClientActivityOnRestoreDelegate;` — Needed by ProduceClientLeaveReplicationActivity to correctly build the activity data.
- L55 _private member_ `FOnAddReplicationActivity OnAddReplicationActivityDelegate;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L16 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<FConcertSessionClientInfo>, FFindSessionClient, const FGuid& EndpointId);`
- L16 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<FConcertSessionClientInfo>, FFindSessionClient, const FGuid& EndpointId);` (scope `UE::ConcertSyncServer`)
- L17 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldIgnoreClientActivityOnRestore, const FGuid& ClientId);`
- L17 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldIgnoreClientActivityOnRestore, const FGuid& ClientId);` (scope `UE::ConcertSyncServer`)
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAddReplicationActivity, int64 ActivityId, bool bSuccess);` — Called when an activity is added to the database.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/SyncControlManager.h` (Private)


#### class `UE::ConcertSyncServer::Replication::FSyncControlManager`  
`class FSyncControlManager : public FNoncopyable`  
_L33-116_
- inherits: `FNoncopyable`
- desc: Decides whether clients should be replicating. Clients may replicate when they have authority and there are other clients listening for that data. For now, sync control just checks whether there is another client in the session. TODO: In the future, we should consider whether there is another client in the same world, as well.
- L37 _public prototype_ `FSyncControlManager( IConcertServerSession& Session UE_LIFETIMEBOUND, FAuthorityManager& AuthorityManager UE_LIFETIMEBOUND, FMuteManager& MuteManager UE_LIFETIMEBOUND, const IRegistrationEnumerator& Getters UE_LIFETIMEBOUND );`
- L43 _public prototype_ `~FSyncControlManager();`
- L46 _public prototype_ `bool HasSyncControl(const FConcertReplicatedObjectId& Object) const;` — @return Whether this Object is allowed to processed.
- L48 _public prototype_ `const TSet<FConcertObjectInStreamID>* GetClientControlledObjects(const FGuid& ClientId) const;` — @return If the client has any controlled objects, returns a valid pointer to the set of objects they own.
- L51 _public prototype_ `FConcertReplication_ChangeSyncControl OnGenerateSyncControlForClientJoin(const FGuid& ClientId);` — Called by FConcertServerReplicationManager when client completes replication handshake.
- L54 _public function_ `void OnPostClientLeft(const FGuid& ClientId)` — Called by FConcertServerReplicationManager when client completes leaves replication.
- L59 _private member_ `IConcertServerSession& Session;` — Used to send sync control messages to clients, which notifies them to start / stop replicating.
- L61 _private member_ `FAuthorityManager& AuthorityManager;` — Used to detect whether a client has authority.
- L63 _private member_ `FMuteManager& MuteManager;` — Used to detect whether objects are globally muted.
- L66 _private member_ `const IRegistrationEnumerator& Getters;` — Callbacks for retrieving more info about client replication registration.
- L74 _private member_ `TMap<FGuid, FClientData> PerClientData;` — Maps client ID to client sync control data.
- L77 _private prototype_ `FConcertReplication_ChangeSyncControl OnGenerateSyncControlForAuthorityResponse(const FGuid& ClientId);` — Generates new sync control for client that is explicitly changing their authority.
- L83 _private function_ `void OnRefreshSyncControlForIndirectMuteChange(const FGuid& ClientId)` — Called when a client has caused mute state to change (e.g. due to removing object from stream, or explicitly muting it). Called via delegate by FMuteManager.
- L94 _private prototype_ `FConcertReplication_ChangeSyncControl OnRefreshSyncControlForClientMuteChange(const FGuid& ClientId);` — Updates sync control for all clients, sends an update to all clients but ClientId, and returns the sync control to embed into the mute response. Called via delegate by FMuteManager.
- L96 _private prototype_ `void OnRefreshSyncControlAndEnumerateWithoutSending(const FMuteManager::FOnSyncControlChange& OnSyncControlChange);` — Updates sync control for all clients and enumerates the sync control instead of sending it. The callback handles updating the remote client machines.
- L99 _private prototype_ `void HandleClientLeave(const FGuid& LeftClientId);` — Cleans up the associated client data and updates sync control for all other clients.
- L102 _private prototype_ `FConcertReplication_ChangeSyncControl RefreshClientSyncControl( const FGuid& ClientId, TFunctionRef<bool(const FConcertObjectInStreamID& Object, bool bNewValue)> ShouldSkipInMessage = [](auto&, auto){ return false; } );` — Compares the client's current sync control against the new sync control it should have and returns the delta to be sent to the client.
- L104 _private function_ `const FGuid& ClientId, TFunctionRef<bool(const FConcertObjectInStreamID& Object, bool bNewValue)> ShouldSkipInMessage = [](auto&, auto)`
- L108 _private prototype_ `void RefreshAndSendToAllClientsExcept(const FGuid& SkippedClient);` — Except for SkippedClient, checks all clients' sync control has changed and conditionally updates the remote endpoints.
- L110 _private prototype_ `void RefreshAndSendSyncControl(const FGuid& ClientId);` — Checks whether client sync control has changed and conditionally updates the remote endpoint.
- L113 _private prototype_ `bool IsAnyoneInterestedIn(const FConcertReplicatedObjectId& Object) const;` — @return Whether any client wants to receive Object.
- L115 _private prototype_ `bool IsClientInterestedIn(const FConcertReplicatedObjectId& Object, const FGuid& Client) const;` — @return Whether Client is interested in receiving Object.

#### struct `UE::ConcertSyncServer::Replication::FSyncControlManager::FClientData`  
`struct FClientData`  
_L68-72_
- L71 _public member_ `TSet<FConcertObjectInStreamID> ObjectsWithSyncControl;` — Contains all objects that are allowed to be replicated for this client.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L21 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/Util/GroundTruthOverride.h` (Private)


#### class `UE::ConcertSyncServer::Replication::FGroundTruthOverride`  
`class FGroundTruthOverride : public ConcertSyncCore::Replication::IReplicationGroundTruth , public FNoncopyable`  
_L30-63_
- inherits: `ConcertSyncCore::Replication::IReplicationGroundTruth,FNoncopyable`
- desc: Pretends that the ground truth is the client overrides it was given. If a setting is not overriden, then it defaults back to the server state. StreamOverrides can contain clients that are not actually connected ("injection"). This is useful if you want to validate i.e. that no authority conflicts happen if the injected clients were present.
- L36 _public function_ `FGroundTruthOverride( const TMap<FGuid, FConcertReplicationStreamArray>& StreamOverrides UE_LIFETIMEBOUND, const TMap<FGuid, FConcertObjectInStreamArray>& AuthorityOverrides UE_LIFETIMEBOUND, const IRegistrationEnumerator& NoOverrideStreamFallback UE_LIFETIMEBOUND, const FAuthorityManager& NoOverrideAuthorityFallback UE_LIFETIMEBOUND ) : StreamOverrides(StreamOverrides) , AuthorityOverrides(AuthorityOverrides) , NoOverrideStreamFallback(NoOverrideStreamFallback) , NoOverrideAuthorityFallback(NoOverrideAuthorityFallback)`
- L49 _public prototype_ `virtual void ForEachStream(const FGuid& ClientEndpointId, TFunctionRef<EBreakBehavior(const FGuid& StreamId, const FConcertObjectReplicationMap& ReplicationMap)> Callback) const override;`
- L50 _public prototype_ `virtual void ForEachClient(TFunctionRef<EBreakBehavior(const FGuid& ClientEndpointId)> Callback) const override;`
- L51 _public prototype_ `virtual bool HasAuthority(const FGuid& ClientId, const FGuid& StreamId, const FSoftObjectPath& ObjectPath) const override;`
- L56 _private member_ `const TMap<FGuid, FConcertReplicationStreamArray>& StreamOverrides;`
- L57 _private member_ `const TMap<FGuid, FConcertObjectInStreamArray>& AuthorityOverrides;`
- L60 _private member_ `const IRegistrationEnumerator& NoOverrideStreamFallback;` — Gives us the stream content when no override was specified.
- L62 _private member_ `const FAuthorityManager& NoOverrideAuthorityFallback;` — Gives us the authority when no override was specified.

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L17 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/Util/JoinRequestValidation.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)
- L27 _prototype_ `TTuple<EJoinReplicationErrorCode, FString, TArray<FConcertReplicationStream>> ValidateRequest(const FConcertReplication_Join_Request& Request);` (scope `UE::ConcertSyncServer::Replication`) — Attempts to unpack the request and validates it. Constraints: - All stream IDs must be unique (within request and clients) - No overlapping properties (however, multiple streams can replicate the same object) - The stream descriptions must unpack successfully (i.e. the attributes must be known) @param Request The request to validate @param Clients Clients that are already connected @param GetClientNameFunc Callback for getting a client's display name for error reporting purposes. @return The error code for the request and the unpacked stream descriptions

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/Util/LogUtils.h` (Private)


#### enum `UE::ConcertSyncServer::EClientNameFlags`  
`enum class EClientNameFlags`  
_L15-20_
- L17 _public enumerator_ `None`
- L18 _public enumerator_ `IncludeName = 1 << 0`
- L19 _public enumerator_ `IncludeEndpointId = 1 << 1`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L21 _prototype_ `ENUM_CLASS_FLAGS(EClientNameFlags);` (scope `UE::ConcertSyncServer`)
- L23 _function_ `inline TOptional<FString> GetClientName(IConcertSession& Session, const FGuid& EndpointId, EClientNameFlags Flags = EClientNameFlags::IncludeName | EClientNameFlags::IncludeEndpointId)` (scope `UE::ConcertSyncServer`)
- L45 _function_ `template<typename TMessage, typename TGetClientName> requires std::is_invocable_r_v<TOptional<FString>, TGetClientName> void LogNetworkMessage(const TMessage& Message, TGetClientName GetClientName = [](){ return TOptional<FString>{}; })` (scope `UE::ConcertSyncServer`)
- L45 _function_ `template<typename TMessage, typename TGetClientName> requires std::is_invocable_r_v<TOptional<FString>, TGetClientName> void LogNetworkMessage(const TMessage& Message, TGetClientName GetClientName = [](){ return TOptional<FString>{}; })` (scope `UE::ConcertSyncServer`)
- L61 _function_ `template<typename TMessage, typename TGetClientName> requires std::is_invocable_r_v<TOptional<FString>, TGetClientName> void LogNetworkMessage(const TAutoConsoleVariable<bool>& ShouldLog, const TMessage& Message, TGetClientName GetClientName = [](){ return TOptional<FString>{}; })` (scope `UE::ConcertSyncServer`)
- L61 _function_ `template<typename TMessage, typename TGetClientName> requires std::is_invocable_r_v<TOptional<FString>, TGetClientName> void LogNetworkMessage(const TAutoConsoleVariable<bool>& ShouldLog, const TMessage& Message, TGetClientName GetClientName = [](){ return TOptional<FString>{}; })` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/Util/ReplicationCVars.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L7 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)
- L10 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogStreamRequestsAndResponsesOnServer;` (scope `UE::ConcertSyncServer::Replication`) — Whether to log requests and responses to streams on the server.
- L13 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogAuthorityRequestsAndResponsesOnServer;` (scope `UE::ConcertSyncServer::Replication`) — Whether to log requests and responses to authority on the server.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Private/Replication/Util/StreamChangeValidation.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)
- L21 _prototype_ `bool ValidateStreamChangeRequest( const FGuid& ClientEndpointId, const TConstArrayView<FConcertReplicationStream>& Streams, const FAuthorityManager& AuthorityManager, const FConcertReplication_ChangeStream_Request& Request, FConcertReplication_ChangeStream_Response& OutResponse );` (scope `UE::ConcertSyncServer::Replication`) — Checks whether the stream change is valid to make and puts all errors into OutResponse. @return Whether the request is valid.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Public/ConcertSyncServerLoop.h` (Public)


#### Free symbols / members of external scopes

- L11 _prototype_ `void ShutdownConcertSyncServer(const FString& ServiceFriendlyName);` — Utility method to shutdown the ConcertSyncServer.
- L16 _prototype_ `int32 ConcertSyncServerLoop(const TCHAR* CommandLine, const FConcertSyncServerLoopInitArgs& InitArgs);` — Blocking main loop for running a Concert Sync server application.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Public/ConcertSyncServerLoop.inl` (Public)


#### Free symbols / members of external scopes

- L24 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogSyncServer, Log, All);`
- L26 _function_ `void ShutdownConcertSyncServer(const FString& ServiceFriendlyName)`
- L45 _function_ `int32 ConcertSyncServerLoop(const TCHAR* CommandLine, const FConcertSyncServerLoopInitArgs& InitArgs)`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Public/ConcertSyncServerLoopInitArgs.h` (Public)


#### struct `FConcertSyncServerLoopInitArgs`  
`struct FConcertSyncServerLoopInitArgs`  
_L13-61_
- L15 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FMultiUserServerLoopInitEvent);`
- L16 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMultiUserServerInitServerEvent, TSharedRef<IConcertSyncServer>);`
- L17 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMultiUserServerLoopTickEvent, double );`
- L20 _public member_ `int32 IdealFramerate = 60;` — Framerate that the main loop should try to Tick at
- L23 _public member_ `EConcertSyncSessionFlags SessionFlags = EConcertSyncSessionFlags::None;` — Flags controlling what features are enabled for sessions within this server
- L26 _public member_ `FString ServiceRole;` — The role that this server will perform (eg, MultiUser, DisasterRecovery, etc)
- L29 _public member_ `FString ServiceFriendlyName;` — Friendly name to use for this service (when showing it to a user in log messages, etc)
- L32 _public member_ `FConcertSessionFilter ServiceAutoArchiveSessionFilter;` — The session filter to apply when auto-archiving sessions on this server
- L35 _public member_ `TSharedPtr<IConcertFileSharingService> FileSharingService;` — The optional file sharing server to exchange large files. Can be null.
- L38 _public member_ `TFunction<TSharedPtr<IConcertFileSharingService>()> GetFileSharingServiceFunc;` — Function to get the file sharing service during initialization of concert server. f this is defined then it takes precedence over FileSharingService member.
- L41 _public member_ `TFunction<const UConcertServerConfig*()> GetServerConfigFunc;` — Function to get the server settings object to configure the server with with, or unbound to parse the default settings
- L44 _public member_ `FMultiUserServerLoopInitEvent PreInitServerLoop;` — Called before Multi User Server is initialized: no modules have yet been loaded.
- L52 _public member_ `FMultiUserServerInitServerEvent PostInitServerLoop;` — Called while initilializing Multi User server loop. External services can perform custom initialization here. Called just before entering the server loop. LoadModulesForEnabledPlugins will have been called with PreDefault and Default and the multi user session created.
- L57 _public member_ `FMultiUserServerLoopTickEvent TickPostGameThread;` — Called after the game thread's tick and before FTSTicker::GetCoreTicker.
- L60 _public member_ `bool bShowConsole = true;` — Whether the service should show the log console.

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE(FMultiUserServerLoopInitEvent);`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMultiUserServerInitServerEvent, TSharedRef<IConcertSyncServer>);`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMultiUserServerLoopTickEvent, double );`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Public/IConcertSyncServer.h` (Public)


#### class `IConcertSyncServer`  
`class IConcertSyncServer`  
_L20-42_
- desc: Interface for a Concert Sync Server.
- L23 _public prototype_ `virtual ~IConcertSyncServer() = default;`
- L26 _public prototype_ `virtual void Startup(const UConcertServerConfig* InServerConfig, const EConcertSyncSessionFlags InSessionFlags) = 0;` — Start this Concert Sync Server using the given config
- L29 _public prototype_ `virtual void Shutdown() = 0;` — Stop this Concert Sync Server
- L32 _public prototype_ `virtual IConcertServerRef GetConcertServer() const = 0;` — Get the current server
- L35 _public prototype_ `virtual void SetFileSharingService(TSharedPtr<IConcertFileSharingService> InFileSharingService) = 0;` — Set the file sharing service, enabling the server to work with large files. The server sharing service must be compatible with the client one.
- L38 _public prototype_ `virtual TOptional<FConcertSyncSessionDatabaseNonNullPtr> GetLiveSessionDatabase(const FGuid& SessionId) = 0;` — Gets the session data base for the given live session if it exists
- L41 _public prototype_ `virtual TOptional<FConcertSyncSessionDatabaseNonNullPtr> GetArchivedSessionDatabase(const FGuid& SessionId) = 0;` — Gets the session data base for the given archived session if it exists

#### Free symbols / members of external scopes

- L15 _typedef_ `using FConcertSyncSessionDatabaseNonNullPtr = TNonNullPtr<FConcertSyncSessionDatabase>;`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Public/IConcertSyncServerModule.h` (Public)


#### class `IConcertSyncServerModule`  
`class IConcertSyncServerModule : public IModuleInterface`  
_L21-73_
- inherits: `IModuleInterface`
- desc: Interface for the Concert Sync Server module.
- L30 _public function_ `static inline IConcertSyncServerModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L41 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L52 _public prototype_ `virtual UConcertServerConfig* ParseServerSettings(const TCHAR* CommandLine) = 0;` — Parse command line server settings and apply them @param CommandLine the application command line arguments @return The server settings, modified or not by the command line
- L60 _public prototype_ `virtual TSharedRef<IConcertSyncServer> CreateServer(const FString& InRole, const FConcertSessionFilter& InAutoArchiveSessionFilter) = 0;` — Create a sync server that will perform a certain role (eg, MultiUser, DisasterRecovery, etc) @param InRole The role to create @param InAutoArchiveSessionFilter The session filter to apply when auto-archiving sessions @return The server
- L67 _public prototype_ `virtual TSharedRef<IConcertFileSharingService> CreateFileSharingService(const FString& InRole) = 0;` — Creates a shared reference to the file sharing service to be used by concert. @return a non-null shared reference to the file sharing service.
- L72 _public prototype_ `virtual FOnConcertSyncServerCreated& OnServerCreated() = 0;` — Callback for when a ConcertSyncServer has been created.

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertSyncServerCreated, TWeakPtr<IConcertSyncServer>);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertSyncServerCreated, TWeakPtr<IConcertSyncServer>);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Public/Replication/IConcertServerReplicationManager.h` (Public)


#### class `UE::ConcertSyncServer::Replication::IConcertServerReplicationManager`  
`class IConcertServerReplicationManager`  
_L13-18_
- desc: Handles all communication with clients regarding replication. Negotiates replicated properties with clients, decides who is the authority (which is the first client to register properties), and replicates received data to other clients.
- L17 _public prototype_ `virtual ~IConcertServerReplicationManager() = default;`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L5 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncServer/Source/ConcertSyncServer/Public/Replication/IReplicationWorkspace.h` (Public)


#### class `UE::ConcertSyncServer::Replication::IReplicationWorkspace`  
`class IReplicationWorkspace`  
_L25-66_
- desc: Interface that FConcertServerReplicationManager uses to interact with the FConcertServerWorkspace. Allows mocking in unit tests, which is the only reason it's in the public module interface.
- L35 _public prototype_ `virtual TOptional<int64> ProduceReplicationActivity(const FGuid& EndpointId, const FConcertSyncReplicationEvent& EventData) = 0;` — Creates a replication activity for the provided client. @param EndpointId The client that produced the activity @param EventData Data associated with the activity - must have ActivityType other than EConcertSyncReplicationActivityType::None. @return The identifier of the produced activity. Unset if activity insertion failed.
- L37 _public prototype_ `TOptional<int64> ProduceClientLeaveReplicationActivity(const FGuid& EndpointId, const FConcertSyncReplicationPayload_LeaveReplication& EventData);` — Creates a replication activity for the client leaving replication.
- L39 _public prototype_ `TOptional<int64> ProduceClientMuteReplicationActivity(const FGuid& EndpointId, const FConcertSyncReplicationPayload_Mute& EventData);` — Creates a replication activity for the client (un)muting objects in the session.
- L51 _public prototype_ `virtual bool GetLastReplicationActivityByClient(const FConcertSessionClientInfo& InClientInfo, EConcertSyncReplicationActivityType ActivityType, FConcertSyncReplicationActivity& OutActivity) const = 0;` — Gets the last replication activity associated with the given client info. As endpoint IDs change every time a client join a session, the look up is done by client display name. If multiple machines joined with the same display name, the tie is broken by also using the device name. @param InClientInfo Info about the client for which to get the activity. @param OutActivity The activity, if present @return Whether OutActivity contains a valid result.
- L53 _public prototype_ `bool GetLastLeaveReplicationActivityByClient(const FConcertSessionClientInfo& InClientInfo, FConcertSyncReplicationPayload_LeaveReplication& OutLeaveReplication) const;` — Gets the last leave replication activity associated with the given client info.
- L56 _public prototype_ `virtual bool GetReplicationEventById(const int64 ActivityId, FConcertSyncReplicationEvent& OutEvent) const = 0;` — Gets the replication leave activity with ActivityId.
- L58 _public prototype_ `bool GetLeaveReplicationEventById(const int64 ActivityId, FConcertSyncReplicationPayload_LeaveReplication& OutLeaveReplication) const;` — Gets the replication leave activity with ActivityId.
- L61 _public prototype_ `virtual void EnumerateReplicationActivities(TFunctionRef<EBreakBehavior(const FConcertSyncReplicationActivity& Activity)> Callback) const = 0;` — Enumerates all activities.
- L63 _public prototype_ `void EnumerateMuteActivities(TFunctionRef<EBreakBehavior(const FConcertSyncReplicationActivity& Activity)> Callback) const;` — Enumerates all mute activities.
- L65 _public prototype_ `virtual ~IReplicationWorkspace() = default;`
- L69 _function_ `inline TOptional<int64> IReplicationWorkspace::ProduceClientLeaveReplicationActivity(const FGuid& EndpointId, const FConcertSyncReplicationPayload_LeaveReplication& EventData)`
- L74 _function_ `inline TOptional<int64> IReplicationWorkspace::ProduceClientMuteReplicationActivity(const FGuid& EndpointId, const FConcertSyncReplicationPayload_Mute& EventData)`
- L79 _function_ `inline bool IReplicationWorkspace::GetLastLeaveReplicationActivityByClient(const FConcertSessionClientInfo& InClientInfo, FConcertSyncReplicationPayload_LeaveReplication& OutLeaveReplication) const`
- L87 _function_ `inline bool IReplicationWorkspace::GetLeaveReplicationEventById(const int64 ActivityId, FConcertSyncReplicationPayload_LeaveReplication& OutLeaveReplication) const`
- L95 _function_ `inline void IReplicationWorkspace::EnumerateMuteActivities(TFunctionRef<EBreakBehavior(const FConcertSyncReplicationActivity& Activity)> Callback) const`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L19 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)
- L98 _function_ `` (scope `UE::ConcertSyncServer::Replication::IReplicationWorkspace::EnumerateMuteActivities`)
