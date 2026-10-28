# Plugins / ConcertClient

- module root: `Plugins/Developer/Concert/ConcertMain/Source/ConcertClient`
- headers: 5; symbols: 287
- symbol kinds: class=7, delegate=3, enum=3, enumerator=8, function=26, macro=1, member=80, namespace=2, prototype=148, struct=7, typedef=2
- PrivateDependencyModuleNames: Engine, GameplayTags
- PublicDependencyModuleNames: Concert, ConcertTransport, Core, CoreUObject, Serialization
- PublicIncludePathModuleNames: Concert, ConcertTransport, GameplayTags

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertClient/Private/ConcertClient.h` (Private)


#### class `FConcertClientPaths`  
`class FConcertClientPaths`  
_L21-41_
- L24 _public prototype_ `explicit FConcertClientPaths(const FString& InRole);`
- L27 _public function_ `const FString& GetWorkingDir() const` — Get the working directory. This is were the active sessions store their files
- L33 _public function_ `FString GetSessionWorkingDir(const FGuid& InSessionId) const` — Return the working directory for a specific session
- L40 _private member_ `const FString WorkingDir;` — Get the working directory. This is were the active sessions store their files

#### class `FConcertClient`  
`class FConcertClient : public IConcertClient`  
_L44-196_
- inherits: `IConcertClient`
- desc: Implements the Concert client
- L47 _public prototype_ `FConcertClient(const FString& InRole, const TSharedPtr<IConcertEndpointProvider>& InEndpointProvider);`
- L48 _public prototype_ `virtual ~FConcertClient();`
- L50 _public prototype_ `virtual const FString& GetRole() const override;`
- L52 _public prototype_ `virtual void Configure(const UConcertClientConfig* InSettings) override;`
- L53 _public prototype_ `virtual bool IsConfigured() const override;`
- L54 _public prototype_ `virtual const UConcertClientConfig* GetConfiguration() const override;`
- L55 _public prototype_ `virtual const FConcertClientInfo& GetClientInfo() const override;`
- L57 _public prototype_ `virtual bool IsStarted() const override;`
- L58 _public prototype_ `virtual void Startup() override;`
- L59 _public prototype_ `virtual void Shutdown() override;`
- L61 _public prototype_ `virtual bool IsDiscoveryEnabled() const override;`
- L62 _public prototype_ `virtual void StartDiscovery() override;`
- L63 _public prototype_ `virtual void StopDiscovery() override;`
- L65 _public prototype_ `virtual bool CanAutoConnect() const override;`
- L66 _public prototype_ `virtual bool IsAutoConnecting() const override;`
- L67 _public prototype_ `virtual void StartAutoConnect() override;`
- L68 _public prototype_ `virtual void StopAutoConnect() override;`
- L69 _public prototype_ `virtual FConcertConnectionError GetLastConnectionError() const override;`
- L71 _public prototype_ `virtual TArray<FConcertServerInfo> GetKnownServers() const override;`
- L72 _public prototype_ `virtual FSimpleMulticastDelegate& OnKnownServersUpdated() override;`
- L74 _public prototype_ `virtual FOnConcertClientSessionStartupOrShutdown& OnSessionStartup() override;`
- L75 _public prototype_ `virtual FOnConcertClientSessionStartupOrShutdown& OnSessionShutdown() override;`
- L77 _public prototype_ `virtual FOnConcertClientSessionGetPreConnectionTasks& OnGetPreConnectionTasks() override;`
- L78 _public prototype_ `virtual FOnConcertClientSessionConnectionChanged& OnSessionConnectionChanged() override;`
- L79 _public prototype_ `virtual void SetFileSharingService(TSharedPtr<IConcertFileSharingService> InFileSharingService) override;`
- L80 _public prototype_ `virtual TSharedPtr<IConcertFileSharingService> GetFileSharingService() const override;`
- L82 _public prototype_ `virtual EConcertConnectionStatus GetSessionConnectionStatus() const override;`
- L83 _public prototype_ `virtual TFuture<EConcertResponseCode> CreateSession(const FGuid& ServerAdminEndpointId, const FConcertCreateSessionArgs& CreateSessionArgs) override;`
- L84 _public prototype_ `virtual TFuture<EConcertResponseCode> JoinSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) override;`
- L85 _public prototype_ `virtual TFuture<EConcertResponseCode> RestoreSession(const FGuid& ServerAdminEndpointId, const FConcertCopySessionArgs& RestoreSessionArgs) override;`
- L86 _public prototype_ `virtual TFuture<EConcertResponseCode> CopySession(const FGuid& ServerAdminEndpointId, const FConcertCopySessionArgs& CopySessionArgs) override;`
- L87 _public prototype_ `virtual TFuture<EConcertResponseCode> ArchiveSession(const FGuid& ServerAdminEndpointId, const FConcertArchiveSessionArgs& ArchiveSessionArgs) override;`
- L88 _public prototype_ `virtual TFuture<EConcertResponseCode> RenameSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& NewName) override;`
- L89 _public prototype_ `virtual TFuture<EConcertResponseCode> DeleteSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) override;`
- L90 _public prototype_ `virtual TFuture<FConcertAdmin_BatchDeleteSessionResponse> BatchDeleteSessions(const FGuid& ServerAdminEndpointId, const FConcertBatchDeleteSessionsArgs& BatchDeletionArgs) override;`
- L91 _public prototype_ `virtual void DisconnectSession() override;`
- L93 _public prototype_ `virtual EConcertSendReceiveState GetSendReceiveState() const override;`
- L94 _public prototype_ `virtual void SetSendReceiveState(EConcertSendReceiveState InSendReceiveState) override;`
- L96 _public prototype_ `virtual bool IsOwnerOf(const FConcertSessionInfo& InSessionInfo) const override;`
- L97 _public prototype_ `virtual TSharedPtr<IConcertClientSession> GetCurrentSession() const override;`
- L99 _public prototype_ `virtual TFuture<FConcertAdmin_MountSessionRepositoryResponse> MountSessionRepository(const FGuid& ServerAdminEndpointId, const FString& RepositoryRootDir, const FGuid& RepositoryId, bool bCreateIfNotExist, bool bAsDefault) const override;`
- L100 _public prototype_ `virtual TFuture<FConcertAdmin_GetSessionRepositoriesResponse> GetSessionRepositories(const FGuid& ServerAdminEndpointId) const override;`
- L101 _public prototype_ `virtual TFuture<FConcertAdmin_DropSessionRepositoriesResponse> DropSessionRepositories(const FGuid& ServerAdminEndpointId, const TArray<FGuid>& RepositoryIds) const override;`
- L102 _public prototype_ `virtual TFuture<FConcertAdmin_GetAllSessionsResponse> GetServerSessions(const FGuid& ServerAdminEndpointId) const override;`
- L103 _public prototype_ `virtual TFuture<FConcertAdmin_GetSessionsResponse> GetLiveSessions(const FGuid& ServerAdminEndpointId) const override;`
- L104 _public prototype_ `virtual TFuture<FConcertAdmin_GetSessionsResponse> GetArchivedSessions(const FGuid& ServerAdminEndpointId) const override;`
- L105 _public prototype_ `virtual TFuture<FConcertAdmin_GetSessionClientsResponse> GetSessionClients(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const override;`
- L106 _public prototype_ `virtual TFuture<FConcertAdmin_GetSessionActivitiesResponse> GetSessionActivities(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, int64 FromActivityId, int64 ActivityCount, bool bIncludeDetails) const override;`
- L117 _private prototype_ `TFuture<EConcertResponseCode> InternalCreateSession(const FGuid& ServerAdminEndpointId, const FConcertCreateSessionArgs& CreateSessionArgs, TUniquePtr<FAsyncTaskNotification> OngoingNotification = nullptr);`
- L118 _private prototype_ `TFuture<EConcertResponseCode> InternalJoinSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, TUniquePtr<FAsyncTaskNotification> OngoingNotification = nullptr);`
- L119 _private prototype_ `TFuture<EConcertResponseCode> InternalCopySession(const FGuid& ServerAdminEndpointId, const FConcertCopySessionArgs& CopySessionArgs, bool bRestoreOnlyConstraint, TUniquePtr<FAsyncTaskNotification> OngoingNotification = nullptr);`
- L120 _private prototype_ `void InternalDisconnectSession();`
- L123 _private prototype_ `void SetLastConnectionError(FConcertConnectionError LastError);` — Set the connection error.
- L126 _private prototype_ `void OnEndFrame();`
- L129 _private prototype_ `TFuture<EConcertResponseCode> CreateClientSession(const FConcertSessionInfo& SessionInfo);` — Create a Concert client session based on the session information provided. The future is set when the client connection is established or has failed.
- L132 _private prototype_ `void HandleSessionConnectionChanged(IConcertClientSession& InSession, EConcertConnectionStatus Status);` — Internal handler bound to the current session (if any) to propagate via our own OnSessionConnectionChanged delegate
- L135 _private member_ `FString Role;` — The role of this client (eg, MultiUser, DisasterRecovery, etc)
- L138 _private member_ `FConcertClientPaths Paths;` — Cached root paths used by this client
- L141 _private member_ `TSharedPtr<IConcertEndpointProvider> EndpointProvider;` — Endpoint provider
- L144 _private member_ `TSharedPtr<IConcertLocalEndpoint> ClientAdminEndpoint;` — Administration endpoint for the client (i.e. creating, joining sessions)
- L147 _private member_ `TSharedPtr<IConcertFileSharingService> FileSharingService;` — Shared pointer to the file sharing service to use.
- L150 _private member_ `uint32 DiscoveryCount;` — Count of the number of times the discovery has been enabled
- L153 _private member_ `FTSTicker::FDelegateHandle DiscoveryTick;` — Ticker for interfacing with the discovery thread.
- L156 _private member_ `TUniquePtr<FConcertClientServerDiscoveryThread> ServerDiscoveryThread;` — Unique pointer to the discovery thread runnable.
- L159 _private member_ `FSimpleMulticastDelegate ServersUpdatedDelegate;` — Holds a delegate to be invoked when the server list was updated.
- L162 _private member_ `FConcertClientInfo ClientInfo;` — Information about this Client
- L165 _private member_ `FOnConcertClientSessionStartupOrShutdown OnSessionStartupDelegate;` — Delegate for client session startup
- L168 _private member_ `FOnConcertClientSessionStartupOrShutdown OnSessionShutdownDelegate;` — Delegate for client session shutdown
- L171 _private member_ `FOnConcertClientSessionGetPreConnectionTasks OnGetPreConnectionTasksDelegate;` — Delegate that is called to get the pre-connection tasks for a client session
- L174 _private member_ `FOnConcertClientSessionConnectionChanged OnSessionConnectionChangedDelegate;` — Delegate for when the session connection state changes
- L177 _private member_ `TSharedPtr<FConcertClientSession> ClientSession;` — Pointer to the Concert Session the client is connected to
- L180 _private member_ `TStrongObjectPtr<const UConcertClientConfig> Settings;` — Client settings object we were configured with
- L183 _private member_ `FConcertConnectionError LastConnectionError;` — The last connection attempt error, if any.
- L186 _private member_ `TUniquePtr<FConcertAutoConnection> AutoConnection;` — Holds the auto connection routine, if any.
- L189 _private member_ `TSharedPtr<FConcertPendingConnection> PendingConnection;` — Holds the pending connection routine, if any (shared as it is used as a weak pointer with UI).
- L192 _private member_ `TUniquePtr<TPromise<EConcertResponseCode>> ConnectionPromise;` — The promise sets when the connection to the current session is confirmed or infirmed.
- L195 _private member_ `bool bClientSessionPendingDestroy;` — True if the client session disconnected this frame and should be fully destroyed at the end of the frame (this is mainly to handle timeouts)

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertClient/Private/ConcertClientSession.h` (Private)


#### class `FConcertClientSession`  
`class FConcertClientSession : public IConcertClientSession, private FConcertSessionCommonImpl`  
_L19-216_
- inherits: `IConcertClientSession,FConcertSessionCommonImpl`
- desc: Implementation of a Concert Client session
- L22 _public prototype_ `FConcertClientSession(const FConcertSessionInfo& InSessionInfo, const FConcertClientInfo& InClientInfo, const FConcertClientSettings& InSettings, TSharedPtr<IConcertLocalEndpoint> InClientSessionEndpoint, const FString& InSessionDirectory);`
- L23 _public prototype_ `virtual ~FConcertClientSession();`
- L25 _public prototype_ `virtual void Startup() override;`
- L26 _public prototype_ `virtual void Shutdown() override;`
- L28 _public function_ `virtual const FGuid& GetId() const override`
- L33 _public function_ `virtual const FString& GetName() const override`
- L38 _public function_ `virtual const FConcertSessionInfo& GetSessionInfo() const override`
- L43 _public function_ `virtual TArray<FGuid> GetSessionClientEndpointIds() const override`
- L48 _public function_ `virtual TArray<FConcertSessionClientInfo> GetSessionClients() const override`
- L53 _public function_ `virtual bool FindSessionClient(const FGuid& EndpointId, FConcertSessionClientInfo& OutSessionClientInfo) const override`
- L58 _public function_ `virtual FConcertScratchpadRef GetScratchpad() const override`
- L63 _public function_ `virtual FConcertScratchpadPtr GetClientScratchpad(const FGuid& ClientEndpointId) const override`
- L68 _public function_ `virtual EConcertConnectionStatus GetConnectionStatus() const override`
- L73 _public function_ `virtual FGuid GetSessionClientEndpointId() const override`
- L78 _public function_ `virtual FGuid GetSessionServerEndpointId() const override`
- L83 _public function_ `virtual const FConcertClientInfo& GetLocalClientInfo() const override`
- L88 _public prototype_ `virtual void UpdateLocalClientInfo(const FConcertClientInfoUpdate& UpdatedFields) override;`
- L90 _public prototype_ `virtual void Connect() override;`
- L91 _public prototype_ `virtual void Disconnect() override;`
- L93 _public prototype_ `virtual EConcertSendReceiveState GetSendReceiveState() const override;`
- L94 _public prototype_ `virtual void SetSendReceiveState(EConcertSendReceiveState InSendReceiveState) override;`
- L96 _public prototype_ `virtual FOnConcertClientSessionTick& OnTick() override;`
- L97 _public prototype_ `virtual FOnConcertClientSessionConnectionChanged& OnConnectionChanged() override;`
- L98 _public prototype_ `virtual FOnConcertClientSessionClientChanged& OnSessionClientChanged() override;`
- L99 _public prototype_ `virtual FOnConcertSessionRenamed& OnSessionRenamed() override;`
- L100 _public prototype_ `virtual FString GetSessionWorkingDirectory() const override;`
- L102 _public function_ `virtual FConcertSequencedCustomEventManager& GetSequencedEventManager() override`
- L108 _protected function_ `virtual FDelegateHandle InternalRegisterCustomEventHandler(const FName& EventMessageType, const TSharedRef<IConcertSessionCustomEventHandler>& Handler) override`
- L113 _protected function_ `virtual void InternalUnregisterCustomEventHandler(const FName& EventMessageType, const FDelegateHandle EventHandle) override`
- L118 _protected function_ `virtual void InternalUnregisterCustomEventHandler(const FName& EventMessageType, const void* EventHandler) override`
- L123 _protected function_ `virtual void InternalClearCustomEventHandler(const FName& EventMessageType) override`
- L128 _protected prototype_ `virtual void InternalSendCustomEvent(const UScriptStruct* EventType, const void* EventData, const TArray<FGuid>& DestinationEndpointIds, EConcertMessageFlags Flags, TOptional<FConcertSequencedCustomEvent> InSequencedId = {}) override;`
- L130 _protected function_ `virtual void InternalRegisterCustomRequestHandler(const FName& RequestMessageType, const TSharedRef<IConcertSessionCustomRequestHandler>& Handler) override`
- L135 _protected function_ `virtual void InternalUnregisterCustomRequestHandler(const FName& RequestMessageType) override`
- L140 _protected prototype_ `virtual void InternalSendCustomRequest(const UScriptStruct* RequestType, const void* RequestData, const FGuid& DestinationEndpointId, const TSharedRef<IConcertSessionCustomResponseHandler>& Handler) override;`
- L144 _private prototype_ `void SendNextCustomEvent(const FConcertSequencedCustomEventManager::FPendingCustomEvent& PendingEvent);`
- L147 _private prototype_ `void HandleRemoteConnectionChanged(const FConcertEndpointContext& RemoteEndpointContext, EConcertRemoteEndpointConnection Connection);`
- L150 _private prototype_ `void HandleJoinSessionResultEvent(const FConcertMessageContext& Context);`
- L153 _private prototype_ `void HandleClientListUpdatedEvent(const FConcertMessageContext& Context);`
- L156 _private prototype_ `void HandleSessionRenamedEvent(const FConcertMessageContext& Context);`
- L159 _private prototype_ `void HandleClientInfoUpdatedEvent(const FConcertMessageContext& Context);`
- L162 _private prototype_ `void TickConnection(float DeltaSeconds, const FDateTime& UtcNow);`
- L165 _private prototype_ `void SendConnectionRequest();`
- L168 _private prototype_ `void SendDisconnection();`
- L171 _private prototype_ `void ConnectionAccepted(const TArray<FConcertSessionClientInfo>& InSessionClients);`
- L174 _private prototype_ `void UpdateSessionClients(const TArray<FConcertSessionClientInfo>& InSessionClients);`
- L177 _private prototype_ `EConcertSendReceiveState GetDefaultSendReceiveState();` — Gets the default send receive state from the project settings.
- L180 _private member_ `FConcertClientInfo ClientInfo;` — Information about this Client
- L183 _private member_ `EConcertConnectionStatus ConnectionStatus;` — The connection status to the server counterpart
- L186 _private member_ `IConcertLocalEndpointPtr ClientSessionEndpoint;` — This session endpoint where message are sent and received from.
- L189 _private member_ `EConcertSendReceiveState SendReceiveState = EConcertSendReceiveState::Default;` — State of the connection
- L192 _private member_ `FTSTicker::FDelegateHandle SessionTick;` — Ticker for the session
- L195 _private member_ `FDateTime LastConnectionTick;` — Last connection tick
- L198 _private member_ `FOnConcertClientSessionTick OnTickDelegate;` — Callback for when a connected session ticks
- L201 _private member_ `FOnConcertClientSessionConnectionChanged OnConnectionChangedDelegate;` — Callback for when the session connection state changes
- L204 _private member_ `FOnConcertClientSessionClientChanged OnSessionClientChangedDelegate;` — Callback for when a session client state changes
- L207 _private member_ `FOnConcertSessionRenamed OnSessionRenamedDelegate;` — Callback when the session name changes.
- L209 _private member_ `FConcertSequencedCustomEventManager CustomEventSequenceManager;`
- L212 _private member_ `const FTimespan SessionTickFrequency;` — The timespan at which session updates are processed.
- L215 _private member_ `const FString SessionDirectory;` — The directory where this session will store its files

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertClient/Public/ConcertClientSettings.h` (Public)


#### struct `FConcertClientSettings`  
`struct FConcertClientSettings`  
_L19-108_
- reflection: `USTRUCT()`
- L23 _public function_ `FConcertClientSettings() : DisplayName() , AvatarColor(1.0f, 1.0f, 1.0f, 1.0f) , DesktopAvatarActorClass(TEXT("/ConcertSyncClient/DesktopPresence.DesktopPresence_C")) , VRAvatarActorClass(TEXT("/ConcertSyncClient/VRPresence.VRPresence_C")) , ServerPort(0) , DiscoveryTimeoutSeconds(5) , SessionTickFrequencySeconds(1) , LatencyCompensationMs(0)`
- L39 _public member_ `FString DisplayName;` — `UPROPERTY(config, EditAnywhere, Category="Client Settings")` — The display name to use when in a session. Can be specified on the editor cmd with `-CONCERTDISPLAYNAME=`.
- L43 _public member_ `FLinearColor AvatarColor;` — `UPROPERTY(config, EditAnywhere, Category="Client Settings")` — The color used for the presence avatar in a session.
- L47 _public member_ `FSoftClassPath DesktopAvatarActorClass;` — `UPROPERTY(config, EditAnywhere, NoClear, Category = "Client Settings", meta = (MetaClass = "/Script/ConcertSyncClient.ConcertClientDesktopPresenceActor"))` — The desktop representation of this editor's user to other connected users
- L51 _public member_ `FSoftClassPath VRAvatarActorClass;` — `UPROPERTY(config, EditAnywhere, NoClear, Category = "Client Settings", meta = (MetaClass = "/Script/ConcertSyncClient.ConcertClientVRPresenceActor", DisplayName = "VR Avatar Actor Class"))` — The VR representation of this editor's user to other connected users
- L55 _public member_ `uint16 ServerPort;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Client Settings")` — The port to use to reach the server with static endpoints when launched through the editor. This port will be used over the unicast endpoint port in the UDP Messagging settings if non 0 when transferring the editor settings to the launched server.
- L59 _public member_ `int32 DiscoveryTimeoutSeconds;` — `UPROPERTY(config, EditAnywhere, DisplayName="Discovery Timeout", AdvancedDisplay, Category="Client Settings", meta=(ForceUnits=s))` — The timespan at which discovered Multi-User server are considered stale if they haven't answered back
- L63 _public member_ `int32 SessionTickFrequencySeconds;` — `UPROPERTY(config, EditAnywhere, DisplayName="Session Tick Frequency", AdvancedDisplay, Category="Client Settings", meta=(ForceUnits=s))` — The timespan at which session updates are processed.
- L67 _public member_ `float LatencyCompensationMs;` — `UPROPERTY(config, EditAnywhere, DisplayName="Latency Compensation", AdvancedDisplay, Category="Client Settings", meta=(ForceUnits=ms))` — Amount of latency compensation to apply to time-synchronization sensitive interactions
- L70 _public member_ `bool bReflectLevelEditorInGame_DEPRECATED = false;` — `UPROPERTY()`
- L79 _public member_ `bool bSupportMixedBuildTypes = false;` — `UPROPERTY(config, EditAnywhere, DisplayName="Support Mixed Build Types", AdvancedDisplay, Category="Client Settings")` — Enable extended version support when using Multi-user with precompiled and source builds.  When using Unreal Game Sync, it is possible to have the same engine CL but different engine version due to content changes.	 This setting enables reading engine version CL from the Build.version file produced by UGS to determine engine version information when joining a session.	This only applies when you intend to mix precompiled with source builds.
- L83 _public member_ `TArray<FName> Tags;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Client Settings")` — Array of tags that can be used for grouping and categorizing.
- L87 _public member_ `FString ClientAuthenticationKey;` — `UPROPERTY(config)` — A key used to identify the clients during server discovery. If the server was configured to restrict access, the client key must be know of the server. Can be left empty.
- L94 _public member_ `bool bEnableFileSharing = false;` — `UPROPERTY(Config, EditAnywhere, Category = "File Sharing")` — Specifies if we should use a file sharing service for larger assets that are saved in a Multi-user session. Note the specified folder must be visible to all clients.
- L100 _public member_ `bool bCleanSessionFilesOnDisconnect = true;` — `UPROPERTY(Config, EditAnywhere, meta=(EditCondition="bEnableFileSharing"), Category = "File Sharing")` — Indicates that the file sharing content should be removed on exit. If this is false then it will be left in place and must be removed by the user.
- L107 _public member_ `FDirectoryPath CloudFileSharingPath;` — `UPROPERTY(Config, EditAnywhere, meta=(EditCondition="bEnableFileSharing"), Category = "File Sharing")` — The path for that shares files across clients. This path must be visible to all nodes. A challenge request will be sent to the server to confirm that it can see the path. If the server cannot see the path then it will reject file sharing for this node and it will fallback to a non-fileshare code flow.

#### enum `EConcertSourceValidationMode`  
`enum class EConcertSourceValidationMode : uint8`  
_L111-123_
- reflection: `UENUM()`
- L114 _public enumerator_ `Hard = 0` — Source control validation will fail on any changes when connecting to a Multi-User Session.
- L120 _public enumerator_ `Soft` — Source control validation will warn and prompt on any changes when connecting to a Multi-User session. In Memory changes will be hot-reloaded. Source control changes aren't affected but will be stashed/shelved in the future.
- L122 _public enumerator_ `SoftAutoProceed` — Soft validation mode with auto proceed on prompts.

#### struct `FConcertSourceControlSettings`  
`struct FConcertSourceControlSettings`  
_L126-136_
- reflection: `USTRUCT()`
- L130 _public function_ `FConcertSourceControlSettings() : ValidationMode(EConcertSourceValidationMode::Soft)`
- L135 _public member_ `EConcertSourceValidationMode ValidationMode;` — `UPROPERTY(config, EditAnywhere, Category="Revision Control Settings", meta=(Keywords = "Source Control"))`

#### enum `EConcertServerType`  
`enum class EConcertServerType`  
_L139-143_
- reflection: `UENUM()`
- L141 _public enumerator_ `Console`
- L142 _public enumerator_ `Slate`

#### class `UConcertClientConfig`  
`class UConcertClientConfig : public UObject`  
_L146-261_
- reflection: `UCLASS(MinimalAPI, config=Engine)`
- inherits: `UObject`
- L150 _public prototype_ `UConcertClientConfig();`
- L158 _public function_ `virtual bool IsEditorOnly() const` — Mark this setting object as editor only. This so soft object path reference made by this setting object won't be automatically grabbed by the cooker. @see UPackage::Save, FSoftObjectPathThreadContext::GetSerializationOptions, FSoftObjectPath::ImportTextItem @todo: cooker should have a better way to filter editor only objects for 'unsolicited' references.
- L167 _public member_ `bool bIsHeadless;` — `UPROPERTY(config)` — True if this client should be "headless"? (ie, not display any UI).
- L173 _public member_ `bool bInstallEditorToolbarButton;` — `UPROPERTY(config, EditAnywhere, Category="Client Settings", Meta=(ConfigRestartRequired=true, DisplayName="Enable Multi-User Toolbar Button"))` — True if the Multi-User module should install shortcut button and its drop-down menu in the level editor toolbar.
- L180 _public member_ `bool bAutoConnect;` — `UPROPERTY(config, EditAnywhere, Category="Client Settings")` — Automatically connect or create default session on default server. Can be specified on the editor cmd with `-CONCERTAUTOCONNECT` or `-CONCERTAUTOCONNECT=<true/false>`.
- L187 _public member_ `bool bRetryAutoConnectOnError = false;` — `UPROPERTY(config, EditAnywhere, Category="Client Settings")` — If auto-connect is on, retry connecting to the default server/session until it succeeds or the user cancels. Can be specified on the editor cmd with `-CONCERTRETRYAUTOCONNECTONERROR` or `-CONCERTRETRYAUTOCONNECTONERROR=<true/false>`.
- L195 _public member_ `EConcertServerType ServerType = EConcertServerType::Slate;` — `UPROPERTY(config, EditAnywhere, Category="Client Settings")` — Determines which server executable with be launched: Console -> UnrealMultiUserServer.exe Slate	-> UnrealMultiUserSlateServer.exe
- L202 _public member_ `FString DefaultServerURL;` — `UPROPERTY(config, EditAnywhere, Category="Client Settings")` — Default server url (just a name for now) to look for on auto or default connect. Can be specified on the editor cmd with `-CONCERTSERVER=`.
- L209 _public member_ `FString DefaultSessionName;` — `UPROPERTY(config, EditAnywhere, Category="Client Settings")` — Default session name to look for on auto connect or default connect. Can be specified on the editor cmd with `-CONCERTSESSION=`.
- L218 _public member_ `FString DefaultSessionToRestore;` — `UPROPERTY(config, EditAnywhere, Category = "Client Settings")` — If this client create the default session, should the session restore a saved session. Set the name of the desired save to restore its content in your session. Leave this blank if you want to create an empty session. Can be specified on the editor cmd with `-CONCERTSESSIONTORESTORE=`.
- L227 _public member_ `FString DefaultSaveSessionAs;` — `UPROPERTY(config, EditAnywhere, Category = "Client Settings")` — If this client create the default session, should the session data be saved when it's deleted. Set the name desired for the save and the session data will be moved in that save when the session is deleted Leave this blank if you don't want to save the session data. Can be specified on the editor cmd with `-CONCERTSAVESESSIONAS=`.
- L234 _public member_ `FGameplayTagContainer ReadOnlyAssignment;` — `UPROPERTY(config, EditAnywhere, Category = "Client Settings")` — A list of roles that should enter multi-user in read-only mode. If a role is in both SendOnlyAssignment and ReadOnlyassignment then the client will enter the session as full read/write.
- L241 _public member_ `FGameplayTagContainer SendOnlyAssignment;` — `UPROPERTY(config, EditAnywhere, Category = "Client Settings")` — A list of roles that should enter multi-user in send-only mode. If a role is in both SendOnlyAssignment and ReadOnlyAssignment then the client will enter the session as full read/write.
- L249 _public member_ `bool bShouldPromptForHotReloadOnLevel = false;` — `UPROPERTY(config, EditAnywhere, Category="Client Settings")` — Hot reload of a level happens automatically when level / sublevel is changed. This property allows users to receive a prompt before hot reload occurs so that it does not interrupt the user in the current level. Can be specified on the editor command with `-CONCERTSHOULDPROMPTFORHOTRELOAD`
- L253 _public member_ `FConcertClientSettings ClientSettings;` — `UPROPERTY(config, EditAnywhere, Category="Client Settings", meta=(ShowOnlyInnerProperties))` — Client & client session settings
- L256 _public member_ `FConcertSourceControlSettings SourceControlSettings;` — `UPROPERTY(config, EditAnywhere, Category = "Revision Control Settings", meta=(ShowOnlyInnerProperties, Keywords = "Source Control"))`
- L260 _public member_ `FConcertEndpointSettings EndpointSettings;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category="Endpoint Settings", meta=(ShowOnlyInnerProperties))` — Endpoint settings passed down to endpoints on creation

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API CONCERTCLIENT_API`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertClient/Public/IConcertClient.h` (Public)


#### enum `EConcertConnectionTaskAction`  
`enum class EConcertConnectionTaskAction : uint8`  
_L30-35_
- desc: Enum to indicate if any action were taken for the connection task
- L32 _public enumerator_ `None = 0`
- L33 _public enumerator_ `Cancel`
- L34 _public enumerator_ `Continue`

#### struct `FConcertConnectionError`  
`struct FConcertConnectionError`  
_L52-58_
- desc: Struct to contain connection error Code is an integer instead of an enum since connection task can be extended, range under 10000 is reserved. Currently used code and their meaning are as follow No Error								= 0:	Success Pre Connection Canceled					= 1:	Pre connection validation was canceled by the user Connection Attempt Aborted				= 2:	Ongoing connection attempt was canceled by the user Server Not Responding					= 3:	Connection request to server timed out Server Request Failure					= 4:	Server refused the session connection request Workspace Validation Unknown Error		= 100:	Workspace validation unknown error Source Control Validation Unknown Error	= 110:	Unknown source control validation error Source Control Validation Canceled		= 111:	Source control validation was canceled by the user Source Control Validation Error			= 112:	Modified files not yet submitted were found in the workspace Dirty Packages Validation Error			= 113:	Dirty Packages were found before connecting to a session
- L55 _public member_ `uint32 ErrorCode = 0;` — Code for the last connection error.
- L57 _public member_ `FText ErrorText;` — Localized text associated with the error.

#### class `IConcertClientConnectionTask`  
`class IConcertClientConnectionTask`  
_L61-113_
- desc: Interface for tasks executed during the Concert client connection flow (eg, validation, creation, connection)
- L64 _public prototype_ `virtual ~IConcertClientConnectionTask() = default;`
- L70 _public prototype_ `virtual void Execute() = 0;` — Execute this task. Typically this puts the task into a pending state, however it is possible for the task to immediately complete once executed. Ideally this should not block for a long time!
- L76 _public prototype_ `virtual void Abort() = 0;` — Abort this task immediately, and discard any pending work. @note It is expected that GetStatus and GetError will return some kind of error state after this has been called.
- L81 _public prototype_ `virtual void Tick(EConcertConnectionTaskAction TaskAction) = 0;` — Tick this task, optionally requesting that it should gracefully cancel.
- L86 _public prototype_ `virtual bool CanCancel() const = 0;` — Get whether this task can be gracefully canceled.
- L92 _public prototype_ `virtual EConcertResponseCode GetStatus() const = 0;` — Get the current status of this task. @note It is required that the task return Pending while it is in-progress, and Success when it has finished successfully. Any other status is treated as an error state, and GetError will be called.
- L97 _public prototype_ `virtual FText GetDescription() const = 0;` — Get a description of this task that can be used in the progress notification (if any).
- L102 _public prototype_ `virtual FText GetPrompt() const = 0;` — Get the prompt message of this task to be displayed on prompt button if the task require action.
- L107 _public prototype_ `virtual FConcertConnectionError GetError() const = 0;` — Get the extended error status of this task that can be used in the error notification (if any).
- L112 _public prototype_ `virtual FSimpleDelegate GetErrorDelegate() const = 0;` — Get the delegate to gather more error details for this task error notification (if any).

#### struct `FConcertCreateSessionArgs`  
`struct FConcertCreateSessionArgs`  
_L115-122_
- L118 _public member_ `FString SessionName;` — The desired name for the session
- L121 _public member_ `FString ArchiveNameOverride;` — The override for the name used when archiving this session

#### struct `FConcertCopySessionArgs`  
`struct FConcertCopySessionArgs`  
_L124-140_
- L127 _public member_ `bool bAutoConnect = true;` — True to auto-connect to the session after copying/restoring it
- L130 _public member_ `FGuid SessionId;` — The ID of the session to copy or restore
- L133 _public member_ `FString SessionName;` — The desired name for new session
- L136 _public member_ `FString ArchiveNameOverride;` — The override for the name used when archiving the copied/restored session
- L139 _public member_ `FConcertSessionFilter SessionFilter;` — The filter controlling which activities should be copied from the source session.

#### struct `FConcertArchiveSessionArgs`  
`struct FConcertArchiveSessionArgs`  
_L142-152_
- L145 _public member_ `FGuid SessionId;` — The ID of the archived session to archive
- L148 _public member_ `FString ArchiveNameOverride;` — The override for the name used when archiving the session
- L151 _public member_ `FConcertSessionFilter SessionFilter;` — The filter controlling which activities from the session should be archived

#### struct `FConcertBatchDeleteSessionsArgs`  
`struct FConcertBatchDeleteSessionsArgs`  
_L154-158_
- L156 _public member_ `TSet<FGuid> SessionIds;`
- L157 _public member_ `EBatchSessionDeletionFlags Flags;`

#### class `IConcertClient`  
`class IConcertClient`  
_L161-464_
- desc: Interface for Concert client
- L164 _public prototype_ `virtual ~IConcertClient() = default;`
- L169 _public prototype_ `virtual const FString& GetRole() const = 0;` — Get the role of this client (eg, MultiUser, DisasterRecovery, etc)
- L175 _public prototype_ `virtual void Configure(const UConcertClientConfig* InSettings) = 0;` — Configure the client settings and its information. @note If Configure() is called while the client is in a session, some settings may be applied only once the client leave the session.
- L180 _public prototype_ `virtual bool IsConfigured() const = 0;` — Return true if the client has been configured.
- L185 _public prototype_ `virtual const UConcertClientConfig* GetConfiguration() const = 0;` — Return The configuration of this client, or null if it hasn't been configured.
- L191 _public prototype_ `virtual const FConcertClientInfo& GetClientInfo() const = 0;` — Get the client information passed to Configure() if the client is not in a session, otherwise, returns the current session client info as returned by IConcertClientSession::GetLocalClientInfo().
- L196 _public prototype_ `virtual bool IsStarted() const = 0;` — Returns if the client has already been started up.
- L202 _public prototype_ `virtual void Startup() = 0;` — Startup the client, this can be called multiple time Configure needs to be called before startup
- L209 _public prototype_ `virtual void Shutdown() = 0;` — Shutdown the client, its discovery and session, if any. This can be called multiple time with no ill effect. However it depends on the UObject system so need to be called before its exit.
- L214 _public prototype_ `virtual bool IsDiscoveryEnabled() const = 0;` — Returns true if server discovery is enabled.
- L221 _public prototype_ `virtual void StartDiscovery() = 0;` — Start the discovery service for the client This will look for Concert server and populate the known servers list @see GetKnownServers
- L226 _public prototype_ `virtual void StopDiscovery() = 0;` — Stop the discovery service for the client
- L231 _public prototype_ `virtual bool CanAutoConnect() const = 0;` — Returns true if the client is configured for auto connection.
- L236 _public prototype_ `virtual bool IsAutoConnecting() const = 0;` — Returns true if the client has an active auto connection routine.
- L241 _public prototype_ `virtual void StartAutoConnect() = 0;` — Start attempting to auto connect the client to the default session on the default server.
- L246 _public prototype_ `virtual void StopAutoConnect() = 0;` — Stop the current auto connection if currently enabled.
- L252 _public prototype_ `virtual FConcertConnectionError GetLastConnectionError() const = 0;` — Get the last connection error @return an error code along with a text description of the last connection error.
- L257 _public prototype_ `virtual TArray<FConcertServerInfo> GetKnownServers() const = 0;` — Get the list of discovered server information
- L262 _public prototype_ `virtual FSimpleMulticastDelegate& OnKnownServersUpdated() = 0;` — Get the delegate callback for when the known server list is updated
- L267 _public prototype_ `virtual FOnConcertClientSessionStartupOrShutdown& OnSessionStartup() = 0;` — Get the delegate that is called right before the client session startup
- L272 _public prototype_ `virtual FOnConcertClientSessionStartupOrShutdown& OnSessionShutdown() = 0;` — Get the delegate that is called right before the client session shutdown
- L277 _public prototype_ `virtual FOnConcertClientSessionGetPreConnectionTasks& OnGetPreConnectionTasks() = 0;` — Get the delegate that is called to get the pre-connection tasks for a client session
- L282 _public prototype_ `virtual FOnConcertClientSessionConnectionChanged& OnSessionConnectionChanged() = 0;` — Get the delegate that is called when the session connection state changes
- L288 _public prototype_ `virtual void SetFileSharingService(TSharedPtr<IConcertFileSharingService> InFileSharingService) = 0;` — Sets the handle to the file sharing service.  The client needs to prove to the server that they both can see the service.  This file sharing service will ultimate get promoted to the workspace to be used during a working session.
- L293 _public prototype_ `virtual TSharedPtr<IConcertFileSharingService> GetFileSharingService() const = 0;` — Get the current file sharing service held by the client.
- L299 _public prototype_ `virtual EConcertConnectionStatus GetSessionConnectionStatus() const = 0;` — Get the connection status of client session or disconnected if no session is present @see EConcertConnectionStatus
- L308 _public prototype_ `virtual TFuture<EConcertResponseCode> CreateSession(const FGuid& ServerAdminEndpointId, const FConcertCreateSessionArgs& CreateSessionArgs) = 0;` — Create a session on the server, matching the client configured settings. This also initiates the connection handshake for that session with the client. @param ServerAdminEndpointId	The Id of the Concert Server query endpoint @param CreateSessionArgs		The arguments that will be use for the creation of the session @return A future that will contains the final response code of the request
- L317 _public prototype_ `virtual TFuture<EConcertResponseCode> JoinSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) = 0;` — Join a session on the server, the settings of the sessions needs to be compatible with the client settings or the connection will be refused. @param ServerAdminEndpointId	The Id of the Concert Server query endpoint @param SessionId				The Id of the session @return  A future that will contains the final response code of the request
- L326 _public prototype_ `virtual TFuture<EConcertResponseCode> RestoreSession(const FGuid& ServerAdminEndpointId, const FConcertCopySessionArgs& RestoreSessionArgs) = 0;` — Copy an archived session into a new live session on the server, matching the client configured settings. This also initiates the connection handshake for that session with the client when bAutoConnect is true in the RestoreSessionArgs. @param ServerAdminEndpointId	The Id of the Concert Server query endpoint @param RestoreSessionArgs	The arguments that will be use for the restoration of the session @return A future that will contains the final response code of the request
- L336 _public prototype_ `virtual TFuture<EConcertResponseCode> CopySession(const FGuid& ServerAdminEndpointId, const FConcertCopySessionArgs& CopySessionArgs) = 0;` — Copy a live or and archived session into a new live session on server, matching the configured settings. If the session is archived, this is equivalent to restoring it (because copying an archive into another archive is not useful). This also initiates the connection handshake for that session with the server when bAutoConnect is true in the CopySessionArgs. @param ServerAdminEndpointId	The Id of the Concert Server query endpoint @param CopySessionArgs	The arguments that will be use to copy the session @return A future that will contains the final response code of the request
- L344 _public prototype_ `virtual TFuture<EConcertResponseCode> ArchiveSession(const FGuid& ServerAdminEndpointId, const FConcertArchiveSessionArgs& ArchiveSessionArgs) = 0;` — Archive a live session on the server hosting the session. @param ServerAdminEndpointId	The Id of the Concert Server hosting the session (and where the archive will be created) @param ArchiveSessionArgs	The arguments that will be use for the archiving of the session @return A future that will contains the final response code of the request
- L354 _public prototype_ `virtual TFuture<EConcertResponseCode> RenameSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& NewName) = 0;` — Rename a live or archived session if the client has the permission. The server automatically detects if the session is live or archived. If the client is not the owner the request will be refused. @param ServerAdminEndpointId	The Id of the Concert Server query endpoint @param SessionId				The Id of the live session to rename @param NewName				The new session name @return A future that will contains the final response code of the request
- L363 _public prototype_ `virtual TFuture<EConcertResponseCode> DeleteSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) = 0;` — Delete a live or archived session from the server if the client is the owner of the session. The server automatically detects if the session is live or archived. If the client is not the owner the request will be refused. @param ServerAdminEndpointId	The Id of the Concert Server query endpoint @param SessionId				The Id of the session to delete @return A future that will contains the final response code of the request
- L372 _public prototype_ `virtual TFuture<FConcertAdmin_BatchDeleteSessionResponse> BatchDeleteSessions(const FGuid& ServerAdminEndpointId, const FConcertBatchDeleteSessionsArgs& BatchDeletionArgs) = 0;` — Deletes several live or archives sessions from the server. If the client is not sure whether the client has permission for it, it can set the SkipForbiddenSessions - the server will skip disallowed sessions instead of rejecting the entire operation. @param ServerAdminEndpointId	The Id of the Concert Server query endpoint @param BatchDeletionArgs		The arguments that will be used for batch deleting the session(s) @return A future that will contain the server's response (and optionally which sessions were skipped due to permissions)
- L377 _public prototype_ `virtual void DisconnectSession() = 0;` — Disconnect from the current session.
- L380 _public prototype_ `virtual EConcertSendReceiveState GetSendReceiveState() const = 0;` — Get the send/receive state for this session.
- L383 _public prototype_ `virtual void SetSendReceiveState(EConcertSendReceiveState InSendReceiveState) = 0;` — Set the send/receive state for this session.
- L388 _public prototype_ `virtual bool IsOwnerOf(const FConcertSessionInfo& InSessionInfo) const = 0;` — Does the client think it is the owner of the session?
- L393 _public prototype_ `virtual TSharedPtr<IConcertClientSession> GetCurrentSession() const = 0;` — Get the current client session (if any).
- L408 _public prototype_ `virtual TFuture<FConcertAdmin_MountSessionRepositoryResponse> MountSessionRepository(const FGuid& ServerAdminEndpointId, const FString& RepositoryRootDir, const FGuid& RepositoryId, bool bCreateIfNotExist, bool bAsDefault = false) const = 0;` — Create or load a repository (directory structure) containing sessions. The server internally maps the ID to its directories. If the server finds the repository, it will scan the corresponding directories, discover the sessions, process them and make them visible to the other clients. If the repository is not found, but bCreateIfNotExist is true, a new repository will be created. Repositories are persistent and visible to all server instances until dropped by the clients. Any server instance can mount a repository unless it is already mounted by another instance. @note Usually, a client would create a new empty repository and set it as default to populate it, then keep the ID to reload/drop it later. @param ServerAdminEndpointId The server for which the workspace must be mounted. @param RepositoryRootDir The base directory containing the repository to create or load. Can hold several repositories. Leave it empty to use the server one if the client/server are not running on the same machine. @param RepositoryId A unique Id for the repository. Must be valid. @param bCreateIfNotExist Create a new repository if the specified one doesn't exist. @param bAsDefault Whether this repository should be set as the default one to store newly created sessions.
- L413 _public prototype_ `virtual TFuture<FConcertAdmin_GetSessionRepositoriesResponse> GetSessionRepositories(const FGuid& ServerAdminEndpointId) const = 0;` — Request the list of existing session repositories from the server.
- L419 _public prototype_ `virtual TFuture<FConcertAdmin_DropSessionRepositoriesResponse> DropSessionRepositories(const FGuid& ServerAdminEndpointId, const TArray<FGuid>& RepositoryIds) const = 0;` — Drop a set of repositories (and delete the files) from the server. All sessions stored in the unmounted repository will be unloaded and unreachable. The server can only drop the repository if it is not mounted or has mounted it itself.
- L426 _public prototype_ `virtual TFuture<FConcertAdmin_GetAllSessionsResponse> GetServerSessions(const FGuid& ServerAdminEndpointId) const = 0;` — Get the list of sessions available on a server @param ServerAdminEndpointId The Id of the Concert server admin endpoint @return A future for FConcertAdmin_GetAllSessionsResponse which contains a list of sessions
- L433 _public prototype_ `virtual TFuture<FConcertAdmin_GetSessionsResponse> GetLiveSessions(const FGuid& ServerAdminEndpointId) const = 0;` — Get the list of the live sessions data from a server @param ServerAdminEndpointId	The Id of the concert sever admin endpoint @return A future for FConcertAdmin_GetSessionsResponse which contains the list of the archived sessions.
- L440 _public prototype_ `virtual TFuture<FConcertAdmin_GetSessionsResponse> GetArchivedSessions(const FGuid& ServerAdminEndpointId) const = 0;` — Get the list of the archived sessions data from a server @param ServerAdminEndpointId	The Id of the concert sever admin endpoint @return A future for FConcertAdmin_GetSessionsResponse which contains the list of the archived sessions.
- L448 _public prototype_ `virtual TFuture<FConcertAdmin_GetSessionClientsResponse> GetSessionClients(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const = 0;` — Get the list of clients connected to a session on the server @param ServerAdminEndpointId	The Id of the Concert server admin endpoint @param SessionId				The Id of the session @return A future for FConcertAdmin_GetSessionClientsResponse which contains a list of session clients
- L463 _public prototype_ `virtual TFuture<FConcertAdmin_GetSessionActivitiesResponse> GetSessionActivities(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, int64 FromActivityId, int64 ActivityCount, bool bIncludeDetails) const = 0;` — Get the specified session activities, ordered by Activity ID (ascending) from a live or archived session without being connected to it. The function is used to explore the history of a session, for example to implement the disaster recovery scenario. It is possible to get the total number of activities in a session using -1 as ActivityCount. The response will contain the last Activity and its ID. To get the N last activities, set ActivityCount = -N. @param ServerAdminEndpointId	The Id of the Concert server admin endpoint @param SessionId				The Id of the session @param FromActivityId		The first activity ID to fetch (1-based) if ActivityCount is positive. Ignored if ActivityCount is negative. @param ActivityCount			If positive, request \a ActivityCount starting from \a FromActivityId. If negative, request the Abs(\a ActivityCount) last activities. @param bIncludeDetails		If true, includes extra information for package and transaction activity types. See the return type for more info. @return A future for FConcertAdmin_GetSessionActivitiesResponse which contains up to Abs(ActivityCount) activities or an error if it fails. The array of payload in the response can always be decoded as FConcertSyncActivity objects. If bIncludeDetails is true, 'package' and 'transaction' can be decoded respectively as FConcertSyncPackageActivity and FConcertSyncTransactionActivity, providing extra information. The transaction event will contains the full transaction data. The package event contains

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertClientSessionStartupOrShutdown, TSharedRef<IConcertClientSession>);`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertClientSessionStartupOrShutdown, TSharedRef<IConcertClientSession>);`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertClientSessionGetPreConnectionTasks, const IConcertClient&, TArray<TUniquePtr<IConcertClientConnectionTask>>&);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertClientSessionGetPreConnectionTasks, const IConcertClient&, TArray<TUniquePtr<IConcertClientConnectionTask>>&);`
- L21 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnConcertEvaluateHasRole, const FGameplayTagContainer&);`
- L21 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnConcertEvaluateHasRole, const FGameplayTagContainer&);`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace ConcertClient` (scope `UE`)
- L25 _prototype_ `FOnConcertEvaluateHasRole& VPRoleEvaluator();` (scope `UE::ConcertClient`)

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertClient/Public/IConcertClientModule.h` (Public)


#### class `IConcertClientModule`  
`class IConcertClientModule : public IModuleInterface`  
_L17-49_
- inherits: `IModuleInterface`
- desc: Interface for the Main Concert Server module.
- L26 _public function_ `static inline IConcertClientModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L37 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L48 _public prototype_ `virtual IConcertClientRef CreateClient(const FString& InRole) = 0;` — Create a client that will perform a certain role (eg, MultiUser, DisasterRecovery, etc) @param InRole The role to create @return The client

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TSharedPtr<IConcertClient, ESPMode::ThreadSafe> IConcertClientPtr;`
- L12 _typedef_ `typedef TSharedRef<IConcertClient, ESPMode::ThreadSafe> IConcertClientRef;`
