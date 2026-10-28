# Plugins / ConcertServer

- module root: `Plugins/Developer/Concert/ConcertMain/Source/ConcertServer`
- headers: 7; symbols: 224
- symbol kinds: class=5, delegate=3, function=23, macro=1, member=52, namespace=1, prototype=134, struct=3, typedef=2
- PublicDependencyModuleNames: Concert, ConcertTransport, Core, CoreUObject, Serialization
- PublicIncludePathModuleNames: ConcertTransport

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertServer/Private/ConcertServer.h` (Private)


#### class `FConcertServer`  
`class FConcertServer : public IConcertServer`  
_L16-227_
- inherits: `IConcertServer`
- desc: Implements Concert interface
- L19 _public prototype_ `FConcertServer(const FString& InRole, const FConcertSessionFilter& InAutoArchiveSessionFilter, IConcertServerEventSink* InEventSink, const TSharedPtr<IConcertEndpointProvider>& InEndpointProvider);`
- L20 _public prototype_ `virtual ~FConcertServer();`
- L22 _public prototype_ `virtual const FString& GetRole() const override;`
- L24 _public prototype_ `virtual void Configure(const UConcertServerConfig* InSettings) override;`
- L25 _public prototype_ `virtual bool IsConfigured() const override;`
- L26 _public prototype_ `virtual const UConcertServerConfig* GetConfiguration() const override;`
- L27 _public prototype_ `virtual const FConcertServerInfo& GetServerInfo() const override;`
- L29 _public prototype_ `virtual void SetFileSharingService(TSharedPtr<IConcertFileSharingService> InFileSharingService) override;`
- L30 _public prototype_ `virtual TSharedPtr<IConcertFileSharingService> GetFileSharingService() const override;`
- L32 _public prototype_ `virtual TArray<FConcertEndpointContext> GetRemoteAdminEndpoints() const override;`
- L33 _public prototype_ `virtual FOnConcertRemoteEndpointConnectionChanged& OnRemoteEndpointConnectionChanged() override;`
- L34 _public prototype_ `virtual FMessageAddress GetRemoteAddress(const FGuid& AdminEndpointId) const override;`
- L35 _public prototype_ `virtual FOnConcertMessageAcknowledgementReceivedFromLocalEndpoint& OnConcertMessageAcknowledgementReceived() override;`
- L37 _public prototype_ `virtual bool IsStarted() const override;`
- L38 _public prototype_ `virtual void Startup() override;`
- L39 _public prototype_ `virtual void Shutdown() override;`
- L41 _public prototype_ `virtual FGuid GetLiveSessionIdByName(const FString& InName) const override;`
- L42 _public prototype_ `virtual FGuid GetArchivedSessionIdByName(const FString& InName) const override;`
- L44 _public prototype_ `virtual FConcertSessionInfo CreateSessionInfo() const override;`
- L45 _public prototype_ `virtual TArray<FConcertSessionInfo> GetLiveSessionInfos() const override;`
- L46 _public prototype_ `virtual TArray<FConcertSessionInfo> GetArchivedSessionInfos() const override;`
- L47 _public prototype_ `virtual TArray<TSharedPtr<IConcertServerSession>> GetLiveSessions() const override;`
- L48 _public prototype_ `virtual TSharedPtr<IConcertServerSession> GetLiveSession(const FGuid& SessionId) const override;`
- L49 _public prototype_ `virtual TOptional<FConcertSessionInfo> GetArchivedSessionInfo(const FGuid& SessionId) const override;`
- L50 _public prototype_ `virtual TSharedPtr<IConcertServerSession> CreateSession(const FConcertSessionInfo& SessionInfo, FText& OutFailureReason) override;`
- L51 _public prototype_ `virtual TSharedPtr<IConcertServerSession> RestoreSession(const FGuid& SessionId, const FConcertSessionInfo& SessionInfo, const FConcertSessionFilter& SessionFilter, FText& OutFailureReason) override;`
- L52 _public prototype_ `virtual TSharedPtr<IConcertServerSession> CopySession(const FGuid& SrcSessionId, const FConcertSessionInfo& NewSessionInfo, const FConcertSessionFilter& SessionFilter, FText& OutFailureReason) override;`
- L53 _public prototype_ `virtual FGuid ArchiveSession(const FGuid& SessionId, const FString& ArchiveNameOverride, const FConcertSessionFilter& SessionFilter, FText& OutFailureReason, FGuid ArchiveSessionIdOverride = FGuid::NewGuid()) override;`
- L54 _public prototype_ `virtual bool ExportSession(const FGuid& SessionId, const FConcertSessionFilter& SessionFilter, const FString& DestDir, bool bAnonymizeData, FText& OutFailureReason) override;`
- L55 _public prototype_ `virtual bool RenameSession(const FGuid& SessionId, const FString& NewName, FText& OutFailureReason) override;`
- L56 _public prototype_ `virtual bool DestroySession(const FGuid& SessionId, FText& OutFailureReason) override;`
- L57 _public prototype_ `virtual FOnConcertServerSessionStartup& OnConcertServerSessionStartup() override;`
- L58 _public prototype_ `virtual FOnConcertServerStartup& OnConcertServerStartup() override;`
- L59 _public prototype_ `virtual FOnConcertParticipantCanJoinSession& OnConcertParticipantCanJoinSession() override;`
- L63 _protected member_ `FOnConcertServerSessionStartup OnConcertServerSessionStartupDelegate;`
- L64 _protected member_ `FOnConcertServerStartup OnConcertServerStartupDelegate;`
- L65 _protected member_ `FOnConcertParticipantCanJoinSession OnConcertParticipantCanJoinSessionDelegate;`
- L69 _private prototype_ `const FString& GetSessionRepositoriesRootDir() const;` — Returns the root dir where the servers keeps the its internally created repositories (When the caller doesn't provide the paths).
- L71 _private prototype_ `const FConcertServerSessionRepository& GetSessionRepository(const FGuid& SessionId) const;`
- L72 _private prototype_ `FString GetSessionSavedDir(const FGuid& SessionId) const;`
- L73 _private prototype_ `FString GetSessionWorkingDir(const FGuid& SessionId) const;`
- L75 _private prototype_ `EConcertSessionRepositoryMountResponseCode MountSessionRepository(FConcertServerSessionRepository Repository, bool bCreateIfNotExist, bool bCleanWorkingDir, bool bCleanExpiredSessions, bool bSearchByPaths, bool bAsDefault);`
- L76 _private prototype_ `bool UnmountSessionRepository(const FGuid& RepositoryId, bool bDropped);`
- L77 _private prototype_ `bool MountDefaultSessionRepository(const UConcertServerConfig* ServerConfig);`
- L80 _private prototype_ `void HandleDiscoverServersEvent(const FConcertMessageContext& Context);`
- L83 _private prototype_ `TFuture<FConcertAdmin_MountSessionRepositoryResponse> HandleMountSessionRepositoryRequest(const FConcertMessageContext& Context);`
- L86 _private prototype_ `TFuture<FConcertAdmin_GetSessionRepositoriesResponse> HandleGetSessionRepositoriesRequest(const FConcertMessageContext& Context);`
- L89 _private prototype_ `TFuture<FConcertAdmin_DropSessionRepositoriesResponse> HandleDropSessionRepositoriesRequest(const FConcertMessageContext& Context);`
- L92 _private prototype_ `TFuture<FConcertAdmin_SessionInfoResponse> HandleCreateSessionRequest(const FConcertMessageContext& Context);`
- L95 _private prototype_ `TFuture<FConcertAdmin_SessionInfoResponse> HandleFindSessionRequest(const FConcertMessageContext& Context);`
- L98 _private prototype_ `TFuture<FConcertAdmin_SessionInfoResponse> HandleCopySessionRequest(const FConcertMessageContext& Context);`
- L101 _private prototype_ `TFuture<FConcertAdmin_ArchiveSessionResponse> HandleArchiveSessionRequest(const FConcertMessageContext& Context);`
- L104 _private prototype_ `TFuture<FConcertAdmin_RenameSessionResponse> HandleRenameSessionRequest(const FConcertMessageContext& Context);`
- L107 _private prototype_ `FConcertAdmin_RenameSessionResponse RenameSessionInternal(const FConcertAdmin_RenameSessionRequest& Request, bool bCheckPermission);`
- L110 _private prototype_ `TFuture<FConcertAdmin_BatchDeleteSessionResponse> HandleBatchDeleteSessionRequest(const FConcertMessageContext& Context);`
- L113 _private prototype_ `bool ValidateBatchDeletionRequest(const FConcertAdmin_BatchDeleteSessionRequest& Request, FConcertAdmin_BatchDeleteSessionResponse& OutResponse, TMap<FGuid, FString>& OutPreparedSessionNames) const;` — Checks whether the request is valid to serve. Writes any skipped sessions (if any) and error reasons into OutResponse.
- L116 _private prototype_ `TFuture<FConcertAdmin_DeleteSessionResponse> HandleDeleteSessionRequest(const FConcertMessageContext& Context);`
- L119 _private prototype_ `FConcertAdmin_DeleteSessionResponse DeleteSessionInternal(const FConcertAdmin_DeleteSessionRequest& Request, bool bCheckPermission);`
- L122 _private prototype_ `TFuture<FConcertAdmin_GetAllSessionsResponse> HandleGetAllSessionsRequest(const FConcertMessageContext& Context);`
- L125 _private prototype_ `TFuture<FConcertAdmin_GetSessionsResponse> HandleGetLiveSessionsRequest(const FConcertMessageContext& Context);`
- L128 _private prototype_ `TFuture<FConcertAdmin_GetSessionsResponse> HandleGetArchivedSessionsRequest(const FConcertMessageContext& Context);`
- L131 _private prototype_ `TFuture<FConcertAdmin_GetSessionClientsResponse> HandleGetSessionClientsRequest(const FConcertMessageContext& Context);`
- L134 _private prototype_ `TFuture<FConcertAdmin_GetSessionActivitiesResponse> HandleGetSessionActivitiesRequest(const FConcertMessageContext& Context);`
- L137 _private prototype_ `void RecoverSessions(const FConcertServerSessionRepository& InRepository, bool bCleanupExpiredSessions);` — Recover the sessions found in the working directory into live session, build the list of archived sessions and rotate them, keeping only the N most recent.
- L140 _private prototype_ `void UpdateLastModified(TArray<FConcertSessionInfo>& SessionInfos, const TArray<FDateTime>& SessionCreationTimes);` — Sets each FConcertSessionInfo::LastModified time to the corresponding index in SessionCreationTimes.
- L146 _private prototype_ `void ArchiveOfflineSessions(const FConcertServerSessionRepository& InRepository);` — Migrate the live sessions from the working directory (before sessions being recovered into live one) to the archived directory. Expected to happen at start up, before RecoverSessions(), if UConcertServerConfig::bAutoArchiveOnReboot is true.
- L149 _private prototype_ `bool CanJoinSession(const TSharedPtr<IConcertServerSession>& ServerSession, const FConcertSessionSettings& SessionSettings, const FConcertSessionVersionInfo& SessionVersionInfo, const FGuid& EndpointId, const FConcertClientInfo& ClientInfo, FText* OutFailureReason = nullptr);` — Check whether a connecting participant can join the session.
- L152 _private prototype_ `bool IsRequestFromSessionOwner(const TSharedPtr<IConcertServerSession>& Session, const FString& FromUserName, const FString& FromDeviceName) const;` — Validate that the request to delete or modify a session comes from the owner of that session.
- L154 _private prototype_ `bool IsRequestFromSessionOwner(const FConcertSessionInfo& SessionInfo, const FString& FromUserName, const FString& FromDeviceName) const;` — Validate that the request to delete or modify a session comes from the owner of that session.
- L157 _private prototype_ `TSharedPtr<IConcertServerSession> CreateLiveSession(const FConcertSessionInfo& SessionInfo, const FConcertServerSessionRepository& InRepository);`
- L160 _private prototype_ `bool DestroyLiveSession(const FGuid& LiveSessionId, const bool bDeleteSessionData);`
- L163 _private prototype_ `FGuid ArchiveLiveSession(const FGuid& LiveSessionId, const FString& ArchivedSessionNameOverride, const FConcertSessionFilter& SessionFilter, FGuid ArchiveSessionIdOverride = FGuid::NewGuid());`
- L166 _private prototype_ `bool CreateArchivedSession(const FConcertSessionInfo& SessionInfo);`
- L169 _private prototype_ `bool DestroyArchivedSession(const FGuid& ArchivedSessionId, const bool bDeleteSessionData);`
- L172 _private prototype_ `TSharedPtr<IConcertServerSession> RestoreArchivedSession(const FGuid& ArchivedSessionId, const FConcertSessionInfo& NewSessionInfo, const FConcertSessionFilter& SessionFilter, FText& OutFailureReason);`
- L175 _private prototype_ `EConcertResponseCode ValidateFileSharing(const FConcertSessionFileShare& InRequest, FConcertSessionFileShare& OutFileShare, FText& OutFailureReason);` — Validate a file a session join request for file sharing support.
- L179 _private prototype_ `template<typename TCreateOrJoinMessage> bool FillSessionResponseInfoFromFileShareChallenge(const TCreateOrJoinMessage* Message, FConcertAdmin_SessionInfoResponse& ResponseData, const FConcertSessionInfo& SessionInfo);` — Helper template method that handles the two different message types that are used for joining a session (create / join existing).
- L182 _private member_ `FString Role;` — The role of this server (eg, MultiUser, DisasterRecovery, etc)
- L185 _private member_ `TArray<FConcertServerSessionRepository> MountedSessionRepositories;` — All session repositories used by this server.
- L188 _private member_ `TOptional<FConcertServerSessionRepository> DefaultSessionRepository;` — The default directory(ies) scanned to reload existing sessions or used to store newly created ones.
- L191 _private member_ `FText DefaultSessionRepositoryStatus;` — The status of the default session repository (essentially to know why it not mounted).
- L194 _private member_ `FConcertSessionFilter AutoArchiveSessionFilter;` — The session filter to apply when auto-archiving sessions
- L197 _private member_ `IConcertServerEventSink* EventSink;` — Sink functions for events that this server can emit
- L200 _private member_ `TSharedPtr<IConcertEndpointProvider> EndpointProvider;` — Factory for creating Endpoint
- L203 _private member_ `TSharedPtr<IConcertLocalEndpoint> ServerAdminEndpoint;` — Administration endpoint for the server (i.e. creating, joining sessions)
- L206 _private member_ `TSharedPtr<IConcertFileSharingService> FileSharingService;` — File sharing service that we use to verify reachability to client proof files.
- L209 _private member_ `FOnConcertRemoteEndpointConnectionChanged OnConcertRemoteEndpointConnectionChangedDelegate;` — Called when ServerAdminEndpoint emits IConcertLocalEndpoint::OnConcertRemoteEndpointConnectionChanged
- L212 _private member_ `FConcertServerInfo ServerInfo;` — Server and Instance Info
- L215 _private member_ `TMap<FGuid, TSharedPtr<FConcertServerSession>> LiveSessions;` — Map of Live Sessions
- L218 _private member_ `TMap<FGuid, FConcertSessionInfo> ArchivedSessions;` — Map of Archived Sessions
- L221 _private member_ `TStrongObjectPtr<const UConcertServerConfig> Settings;` — Server settings object we were configured with
- L224 _private member_ `FString SessionRepositoryRootDir;` — The root directory containing the session repositories.
- L226 _private member_ `FOnConcertMessageAcknowledgementReceivedFromLocalEndpoint OnConcertMessageAcknowledgementReceivedFromLocalEndpoint;`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertServer/Private/ConcertServerSession.h` (Private)


#### class `FConcertServerSession`  
`class FConcertServerSession : public IConcertServerSession , public TSharedFromThis<FConcertServerSession> , private FConcertSessionCommonImpl`  
_L14-167_
- inherits: `IConcertServerSession,TSharedFromThis<FConcertServerSession>,FConcertSessionCommonImpl`
- desc: Implementation of a Concert Server session
- L20 _public prototype_ `FConcertServerSession(const FConcertSessionInfo& InSessionInfo, const FConcertServerSettings& InSettings, TSharedPtr<IConcertLocalEndpoint> InServerSessionEndpoint, const FString& InSessionDirectory);`
- L21 _public prototype_ `virtual ~FConcertServerSession();`
- L23 _public prototype_ `virtual void Startup() override;`
- L24 _public prototype_ `virtual void Shutdown() override;`
- L26 _public function_ `virtual const FGuid& GetId() const override`
- L31 _public function_ `virtual const FString& GetName() const override`
- L36 _public function_ `virtual void SetName(const FString& NewName) override`
- L42 _public function_ `virtual FMessageAddress GetClientAddress(const FGuid& ClientEndpointId) const override`
- L47 _public function_ `void SetLastModifiedToNow()`
- L52 _public function_ `virtual const FConcertSessionInfo& GetSessionInfo() const override`
- L57 _public function_ `virtual TArray<FGuid> GetSessionClientEndpointIds() const override`
- L62 _public function_ `virtual TArray<FConcertSessionClientInfo> GetSessionClients() const override`
- L67 _public function_ `virtual bool FindSessionClient(const FGuid& EndpointId, FConcertSessionClientInfo& OutSessionClientInfo) const override`
- L72 _public function_ `virtual FConcertScratchpadRef GetScratchpad() const override`
- L77 _public function_ `virtual FConcertScratchpadPtr GetClientScratchpad(const FGuid& ClientEndpointId) const override`
- L82 _public prototype_ `virtual FOnConcertServerSessionTick& OnTick() override;`
- L83 _public prototype_ `virtual FOnConcertServerSessionClientChanged& OnSessionClientChanged() override;`
- L84 _public prototype_ `virtual FOnConcertMessageAcknowledgementReceivedFromLocalEndpoint& OnConcertMessageAcknowledgementReceived() override;`
- L85 _public prototype_ `virtual FString GetSessionWorkingDirectory() const override;`
- L88 _protected function_ `virtual FDelegateHandle InternalRegisterCustomEventHandler(const FName& EventMessageType, const TSharedRef<IConcertSessionCustomEventHandler>& Handler) override`
- L93 _protected function_ `virtual void InternalUnregisterCustomEventHandler(const FName& EventMessageType, const FDelegateHandle EventHandle) override`
- L98 _protected function_ `virtual void InternalUnregisterCustomEventHandler(const FName& EventMessageType, const void* EventHandler) override`
- L103 _protected function_ `virtual void InternalClearCustomEventHandler(const FName& EventMessageType) override`
- L108 _protected prototype_ `virtual void InternalSendCustomEvent(const UScriptStruct* EventType, const void* EventData, const TArray<FGuid>& DestinationEndpointIds, EConcertMessageFlags Flags, TOptional<FConcertSequencedCustomEvent> InSequencedId = {}) override;`
- L110 _protected function_ `virtual void InternalRegisterCustomRequestHandler(const FName& RequestMessageType, const TSharedRef<IConcertSessionCustomRequestHandler>& Handler) override`
- L115 _protected function_ `virtual void InternalUnregisterCustomRequestHandler(const FName& RequestMessageType) override`
- L120 _protected prototype_ `virtual void InternalSendCustomRequest(const UScriptStruct* RequestType, const void* RequestData, const FGuid& DestinationEndpointId, const TSharedRef<IConcertSessionCustomResponseHandler>& Handler) override;`
- L124 _private prototype_ `void HandleRemoteConnectionChanged(const FConcertEndpointContext& RemoteEndpointContext, EConcertRemoteEndpointConnection Connection);`
- L127 _private prototype_ `void HandleDiscoverAndJoinSessionEvent(const FConcertMessageContext& Context);`
- L130 _private prototype_ `void HandleLeaveSessionEvent(const FConcertMessageContext& Context);`
- L133 _private prototype_ `void HandleUpdateClientInfoEvent(const FConcertMessageContext& Context);`
- L136 _private prototype_ `void HandleCustomEvent(const FConcertMessageContext& Context);`
- L139 _private prototype_ `TFuture<FConcertSession_CustomResponse> HandleCustomRequest(const FConcertMessageContext& Context);`
- L142 _private prototype_ `void SendClientListUpdatedEvent();`
- L145 _private prototype_ `void SendSessionNameChanged();`
- L148 _private prototype_ `void TickConnections(float DeltaSeconds);`
- L151 _private member_ `IConcertLocalEndpointPtr ServerSessionEndpoint;` — This session endpoint where message are sent and received from.
- L154 _private member_ `FTSTicker::FDelegateHandle SessionTick;` — Ticker for the session
- L157 _private member_ `FOnConcertServerSessionTick OnTickDelegate;` — Callback for when a server session ticks
- L160 _private member_ `FOnConcertServerSessionClientChanged OnSessionClientChangedDelegate;` — Callback for when a session client state changes
- L163 _private member_ `const FTimespan SessionTickFrequency;` — The timespan at which session updates are processed.
- L166 _private member_ `const FString SessionDirectory;` — The directory where this session will store its files

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertServer/Private/ConcertServerSessionRepositories.h` (Private)


#### struct `FConcertServerSessionRepository`  
`struct FConcertServerSessionRepository`  
_L11-67_
- reflection: `USTRUCT()`
- desc: Keep the information about a the session repository.
- L15 _public prototype_ `FConcertServerSessionRepository() = default;`
- L17 _public function_ `FConcertServerSessionRepository(const FString& InRole, FGuid InRepositoryId, const FString& InWorkingDir, const FString& InSavedDir) : RepositoryId(InRepositoryId) , WorkingDir(InWorkingDir.Len() ? InWorkingDir : FPaths::ProjectIntermediateDir() / InRole) , SavedDir(InSavedDir.Len() ? InSavedDir : FPaths::ProjectSavedDir() / InRole)`
- L24 _public function_ `FConcertServerSessionRepository(const FString& RootPathname, FGuid InRepositoryId) : RepositoryId(InRepositoryId) , RepositoryRootDir(RootPathname) , WorkingDir(RootPathname / InRepositoryId.ToString() / TEXT("Live")) , SavedDir(RootPathname / InRepositoryId.ToString() / TEXT("Archive"))`
- L33 _public function_ `FString GetSessionWorkingDir(const FGuid& InSessionId) const` — Return the working directory for a specific session
- L39 _public function_ `FString GetSessionSavedDir(const FGuid& InSessionId) const` — Return the saved directory for a specific session
- L46 _public member_ `FGuid RepositoryId;` — `UPROPERTY()` — The repository id.
- L50 _public member_ `FString RepositoryRootDir;` — `UPROPERTY()` — The repository root directory. Can be empty is the working/archive dir are not stored in a standard repository.
- L54 _public member_ `FString WorkingDir;` — `UPROPERTY()` — This repository working directory.
- L58 _public member_ `FString SavedDir;` — `UPROPERTY()` — This repository saving directory.
- L62 _public member_ `int32 ProcessId = 0;` — `UPROPERTY()` — The server process ID that mounted the workspace if bMounted is true.
- L66 _public member_ `bool bMounted = false;` — `UPROPERTY()` — Whether the workspace is mounted on a server.

#### struct `FConcertServerSessionRepositoryDatabase`  
`struct FConcertServerSessionRepositoryDatabase`  
_L71-77_
- reflection: `USTRUCT()`
- desc: Tracks the session repositories across the server instances.
- L76 _public member_ `TArray<FConcertServerSessionRepository> Repositories;` — `UPROPERTY()`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertServer/Public/ConcertServerSettings.h` (Public)


#### struct `FConcertServerSettings`  
`struct FConcertServerSettings`  
_L18-29_
- reflection: `USTRUCT()`
- L24 _public member_ `bool bIgnoreSessionSettingsRestriction = false;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category="Server Settings")` — The server will allow client to join potentially incompatible sessions
- L28 _public member_ `int32 SessionTickFrequencySeconds = 1;` — `UPROPERTY(config, EditAnywhere, DisplayName="Session Tick Frequency", AdvancedDisplay, Category="Server Settings", meta=(ForceUnits=s))` — The timespan at which session updates are processed.

#### class `UConcertServerConfig`  
`class UConcertServerConfig : public UObject`  
_L32-144_
- reflection: `UCLASS(MinimalAPI, config=Engine)`
- inherits: `UObject`
- L36 _public prototype_ `UConcertServerConfig();`
- L43 _public member_ `bool bAutoArchiveOnReboot = false;` — `UPROPERTY(config)` — If true, instruct the server to auto-archive sessions that were left in the working directory because the server did not exit properly rather than restoring them as 'live' (the default).
- L49 _public member_ `bool bAutoArchiveOnShutdown = true;` — `UPROPERTY(config)` — If true, instruct the server to auto-archive live sessions on shutdown.
- L56 _public member_ `bool bCleanWorkingDir;` — `UPROPERTY(config, EditAnywhere, Category="Server Settings")` — Clean server sessions working directory when booting Can be specified on the server cmd with `-CONCERTCLEAN`
- L62 _public member_ `int32 NumSessionsToKeep;` — `UPROPERTY(config, EditAnywhere, Category="Server Settings")` — Number of archived sessions to keep when booting, or <0 to keep all archived sessions
- L69 _public member_ `FString ServerName;` — `UPROPERTY(config, EditAnywhere, Category="Server Settings")` — Name of the server, or empty to use the default name. Can be specified on the server cmd with `-CONCERTSERVER=`
- L76 _public member_ `FString DefaultSessionName;` — `UPROPERTY(config, EditAnywhere, Category="Session Settings")` — Name of the default session created on the server. Can be specified on the server cmd with `-CONCERTSESSION=`
- L82 _public member_ `TSet<FString> AuthorizedClientKeys;` — `UPROPERTY(config)` — A set of keys identifying the clients that can discover and access the server. If empty, the server can be discovered and used by any clients.
- L91 _public member_ `FString DefaultSessionToRestore;` — `UPROPERTY(config, EditAnywhere, Category="Session Settings")` — Name of the default session to restore on the server. Set the name of the desired save to restore its content in your session. Leave this blank if you want to create an empty session. Can be specified on the editor cmd with `-CONCERTSESSIONTORESTORE=`.
- L98 _public member_ `FConcertSessionVersionInfo DefaultVersionInfo;` — `UPROPERTY()` — The version string for the default server created. Can be specified on the server cmd with `-CONCERTVERSION=`
- L102 _public member_ `FConcertSessionSettings DefaultSessionSettings;` — `UPROPERTY(config, EditAnywhere, Category="Session Settings")` — Default server session settings
- L106 _public member_ `FConcertServerSettings ServerSettings;` — `UPROPERTY(config, EditAnywhere, Category="Server Settings", meta=(ShowOnlyInnerProperties))` — Server & server session settings
- L110 _public member_ `FConcertEndpointSettings EndpointSettings;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category="Endpoint Settings", meta=(ShowOnlyInnerProperties))` — Endpoint settings passed down to endpoints on creation
- L114 _public member_ `FString WorkingDir;` — `UPROPERTY(config)` — The default directory where the server keeps the live session files. Can be specified on the server command line with `-CONCERTWORKINGDIR=`
- L118 _public member_ `FString ArchiveDir;` — `UPROPERTY(config)` — The default directory where the server keeps the archived session files. Can be specified on the server command line with `-CONCERTSAVEDDIR=`
- L122 _public member_ `FString SessionRepositoryRootDir;` — `UPROPERTY(config)` — The root directory where the server creates new session repositories (unless the client request specifies its own root). If empty or invalid, the server will use a default.
- L126 _public member_ `bool bMountDefaultSessionRepository = true;` — `UPROPERTY(config)` — If neither of WorkingDir and ArchiveDir are set, determine whether the server should mount a standard default session repository where new session will be created.
- L135 _public member_ `bool bEnableFileSharing = false;` — `UPROPERTY(config, EditAnywhere, Category = "File Sharing")` — Specifies if we should use a file sharing service for larger assets that are saved in a Multi-user session. Note the specified folder must be visible to all clients. This can be set on the command line using -CONCERTFILESHARINGENABLED
- L143 _public member_ `FDirectoryPath RootFileSharingPath;` — `UPROPERTY(config, EditAnywhere, meta=(EditCondition="bEnableFileSharing"), Category = "File Sharing")` — The path for that shares files across clients. This path must be visible to all nodes. This can be set on the command line using -CONCERTFILESHAREPATH=<FullPathName>

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API CONCERTSERVER_API`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertServer/Public/ConcertServerUtil.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ConcertUtil`
- L21 _prototype_ `TArray<FConcertSessionClientInfo> GetSessionClients(IConcertServer& Server, const FGuid& SessionId);` (scope `ConcertUtil`) — Get the list of clients for a session @param Server The server to look on @param SessionId The session ID @return A list of clients connected to the session
- L29 _prototype_ `TSharedPtr<IConcertServerSession> GetLiveSessionClientConnectedTo(IConcertServer& Server, const FGuid& ClientEndpointId);` (scope `ConcertUtil`) — Retrieves the server session object from the given connected client. @param Server The server to look on @param ClientEndpointId The client's endpoint ID @return The session the client is connected to if any

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertServer/Public/IConcertServer.h` (Public)


#### class `IConcertServer`  
`class IConcertServer`  
_L18-223_
- desc: Interface for Concert server
- L21 _public prototype_ `virtual ~IConcertServer() = default;`
- L26 _public prototype_ `virtual const FString& GetRole() const = 0;` — Get the role of this server (eg, MultiUser, DisasterRecovery, etc)
- L31 _public prototype_ `virtual void Configure(const UConcertServerConfig* ServerConfig) = 0;` — Configure the Concert settings and its information
- L36 _public prototype_ `virtual bool IsConfigured() const = 0;` — Return true if the server has been configured.
- L41 _public prototype_ `virtual const UConcertServerConfig* GetConfiguration() const = 0;` — Return The configuration of this server, or null if it hasn't been configured.
- L46 _public prototype_ `virtual const FConcertServerInfo& GetServerInfo() const = 0;` — Get the server information set by Configure
- L52 _public prototype_ `virtual void SetFileSharingService(TSharedPtr<IConcertFileSharingService> InFileSharingService) = 0;` — Sets the handle to the file sharing service.  The server needs to verify that it can access the challenge provided by the client to confirm they both have access to the file sharing service.
- L57 _public prototype_ `virtual TSharedPtr<IConcertFileSharingService> GetFileSharingService() const = 0;` — Get the current file sharing service held by the server.
- L63 _public prototype_ `virtual TArray<FConcertEndpointContext> GetRemoteAdminEndpoints() const = 0;` — Gets all remote admin endpoint IDs. A remote admin endpoint is not connected to any session and communicating with the server otherwise, e.g. discovering sessions.
- L66 _public prototype_ `virtual FOnConcertRemoteEndpointConnectionChanged& OnRemoteEndpointConnectionChanged() = 0;` — Callback when a remote admin endpoint connection changes.
- L69 _public prototype_ `virtual FOnConcertParticipantCanJoinSession& OnConcertParticipantCanJoinSession() = 0;` — Callback to check whether a participant should be allowed to join a session.
- L74 _public prototype_ `virtual FMessageAddress GetRemoteAddress(const FGuid& AdminEndpointId) const = 0;` — Gets the address of a remote admin endpoint, i.e. a client that is sending FConcertEndpointDiscoveryEvents.
- L77 _public prototype_ `virtual FOnConcertMessageAcknowledgementReceivedFromLocalEndpoint& OnConcertMessageAcknowledgementReceived() = 0;` — Callback when a message has been acknowledged by a remote endpoint
- L82 _public prototype_ `virtual bool IsStarted() const = 0;` — Returns if the server has already been started up.
- L89 _public prototype_ `virtual void Startup() = 0;` — Startup the server, this can be called multiple time Configure needs to be called before startup @return true if the server was properly started or already was
- L95 _public prototype_ `virtual void Shutdown() = 0;` — Shutdown the server, this can be called multiple time with no ill effect. However it depends on the UObject system so need to be called before its exit.
- L101 _public prototype_ `virtual FGuid GetLiveSessionIdByName(const FString& InName) const = 0;` — Get the ID of a live session from its name. @return The ID of the session, or an invalid GUID if it couldn't be found.
- L107 _public prototype_ `virtual FGuid GetArchivedSessionIdByName(const FString& InName) const = 0;` — Get the ID of an archived session from its name. @return The ID of the session, or an invalid GUID if it couldn't be found.
- L112 _public prototype_ `virtual FConcertSessionInfo CreateSessionInfo() const = 0;` — Create a session description for this server
- L117 _public prototype_ `virtual TArray<FConcertSessionInfo> GetLiveSessionInfos() const = 0;` — Get the live session information list
- L122 _public prototype_ `virtual TArray<FConcertSessionInfo> GetArchivedSessionInfos() const = 0;` — Gets the archived session information list
- L128 _public prototype_ `virtual TArray<TSharedPtr<IConcertServerSession>> GetLiveSessions() const = 0;` — Get all live server sessions @return array of server sessions
- L135 _public prototype_ `virtual TSharedPtr<IConcertServerSession> GetLiveSession(const FGuid& SessionId) const = 0;` — Get a live server session @param SessionId The ID of the session we want @return the server session or an invalid pointer if no session was found
- L142 _public prototype_ `virtual TOptional<FConcertSessionInfo> GetArchivedSessionInfo(const FGuid& SessionId) const = 0;` — Gets an archived session info @param SessionId The ID of the session we want @return The info of the archived session if found
- L150 _public prototype_ `virtual TSharedPtr<IConcertServerSession> CreateSession(const FConcertSessionInfo& SessionInfo, FText& OutFailureReason) = 0;` — Create a new Concert server session based on the passed session info @param SessionInfo The information about the session to create. @param OutFailureReason The reason the operation fails if the function returns false, undefined otherwise. @return the created server session
- L161 _public prototype_ `virtual TSharedPtr<IConcertServerSession> CopySession(const FGuid& SrcSessionId, const FConcertSessionInfo& NewSessionInfo, const FConcertSessionFilter& SessionFilter, FText& OutFailureReason) = 0;` — Create a new live server session from another session. The source session can be an archive or a live session. @param SrcSessionId The ID of the session to copy. If the session is archived, its equivalent to restore it. @param NewSessionInfo The information about the new session to create. @param SessionFilter The filter controlling which activities should be copied over the new session. @param OutFailureReason The reason the operation fails if the function returns null, undefined otherwise. @return the created server session @note This is equivalent to archiving and restoring a session, but faster as it skips one copy of the session (possibly serveral GB).
- L171 _public prototype_ `virtual TSharedPtr<IConcertServerSession> RestoreSession(const FGuid& SessionId, const FConcertSessionInfo& SessionInfo, const FConcertSessionFilter& SessionFilter, FText& OutFailureReason) = 0;` — Restore an archived Concert server session based on the passed session info @param SessionId The ID of the session to restore @param SessionInfo The information about the session to create from the archive. @param SessionFilter The filter controlling which activities from the session should be restored. @param OutFailureReason The reason the operation fails if the function returns false, undefined otherwise. @return the restored server session
- L182 _public prototype_ `virtual FGuid ArchiveSession(const FGuid& SessionId, const FString& ArchiveNameOverride, const FConcertSessionFilter& SessionFilter, FText& OutFailureReason, FGuid ArchiveSessionIdOverride = FGuid::NewGuid()) = 0;` — Archive a Concert session on the server. @param SessionId The ID of the session to archive @param ArchiveNameOverride The name override to give to the archived session. @param SessionFilter The filter controlling which activities from the session should be archived. @param OutFailureReason The reason the operation fails if the function returns false, undefined otherwise. @param ArchiveSessionIdOverride The ID the archived session is supposed to have @return The ID of the archived session on success, or an invalid GUID otherwise.
- L193 _public prototype_ `virtual bool ExportSession(const FGuid& SessionId, const FConcertSessionFilter& SessionFilter, const FString& DestDir, bool bAnonymizeData, FText& OutFailureReason) = 0;` — Copy the session data to a destination folder for external usage. @param SessionId The ID of the session to export. Can be a live or archived session. @param SessionFilter The filter controlling which activities from the session should be archived. @param DestDir The directory where the exported files should be copied. (Must exist) @param bAnonymizeData True to obfuscate the object and package names stored in the database. Ignored if FConcertSessionFilter::bMetaDataOnly is false. @param OutFailureReason The reason why exporting the session would fail. @return True if the session files were exported successfully, false otherwise.
- L203 _public prototype_ `virtual bool RenameSession(const FGuid& SessionId, const FString& NewName, FText& OutFailureReason) = 0;` — Rename a live or archived Concert session on the server. The server automatically detects if the specified session Id is a live or an archived session. @param SessionId The ID of the session to rename @param NewName The new session name. @param OutFailureReason The reason the operation fails if the function returns false, undefined otherwise. @return True if the session was renamed.
- L212 _public prototype_ `virtual bool DestroySession(const FGuid& SessionId, FText& OutFailureReason) = 0;` — Destroy a live or archived Concert server session. The server automatically detects if the specified session Id is a live or an archived session. @param SessionId The name of the session to destroy @param OutFailureReason The reason the operation fails if the function returns false, undefined otherwise. @return true if the session was found and destroyed
- L217 _public prototype_ `virtual FOnConcertServerSessionStartup& OnConcertServerSessionStartup() = 0;` — Callback for when a concert server session has been created.
- L222 _public prototype_ `virtual FOnConcertServerStartup& OnConcertServerStartup() = 0;` — Callback for when a concert server has been created.

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertServerSessionStartup, TWeakPtr<IConcertServerSession>);`
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertServerSessionStartup, TWeakPtr<IConcertServerSession>);`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnConcertServerStartup);`
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnConcertServerStartup);`
- L15 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FOnConcertParticipantCanJoinSession, const FGuid& , const FGuid& , const FConcertClientInfo& , FText* );`
- L15 _prototype_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FOnConcertParticipantCanJoinSession, const FGuid& , const FGuid& , const FConcertClientInfo& , FText* );`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertServer/Public/IConcertServerModule.h` (Public)


#### class `IConcertServerModule`  
`class IConcertServerModule : public IModuleInterface`  
_L19-54_
- inherits: `IModuleInterface`
- desc: Interface for the Main Concert Server module.
- L28 _public function_ `static inline IConcertServerModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L39 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L52 _public prototype_ `virtual IConcertServerRef CreateServer(const FString& InRole, const FConcertSessionFilter& InAutoArchiveSessionFilter, IConcertServerEventSink* InEventSink) = 0;` — Create a server that will perform a certain role (eg, MultiUser, DisasterRecovery, etc) @param InRole The role to create @param InAutoArchiveSessionFilter The session filter to apply when auto-archiving sessions @param InEventSink Sink functions for events that the server can emit @return The server

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef TSharedPtr<IConcertServer, ESPMode::ThreadSafe> IConcertServerPtr;`
- L14 _typedef_ `typedef TSharedRef<IConcertServer, ESPMode::ThreadSafe> IConcertServerRef;`
