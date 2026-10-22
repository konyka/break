# Plugins / MultiUserClientLibrary

- module root: `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClientLibrary`
- headers: 11; symbols: 263
- symbol kinds: class=11, delegate=8, enum=10, enumerator=52, function=9, member=61, namespace=10, prototype=84, struct=18
- PrivateDependencyModuleNames: Concert, ConcertClient, ConcertSyncCore, ConcertTransport, MultiUserClient
- PrivateIncludePathModuleNames: Concert, ConcertSyncClient, ConcertSyncCore
- PublicDependencyModuleNames: ConcertReplicationScripting, Core, CoreUObject, Engine

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClientLibrary/Private/MultiUserSubsystemMessages.h` (Private)


#### struct `FConcertBlueprintEvent`  
`struct FConcertBlueprintEvent`  
_L10-16_
- reflection: `USTRUCT()`
- L15 _public member_ `FConcertSessionSerializedPayload Data;` — `UPROPERTY()`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClientLibrary/Private/Replication/MultiUserReplicationRegistrationContextImpl.h` (Private)


#### class `UMultiUserReplicationRegistrationContextImpl`  
`class UMultiUserReplicationRegistrationContextImpl : public UObject , public IMultiUserReplicationRegistrationContext`  
_L21-37_
- reflection: `UCLASS()`
- inherits: `UObject,IMultiUserReplicationRegistrationContext`
- desc: Instantiated once and passed to IMultiUserReplicationRegistration. Needed because TScriptInterface, which is passed via FMultiUserReplicationRegistrationParams, requires an UObject to bind to. @see FUObjectAdapterReplicationDiscoverer
- L29 _public member_ `UE::MultiUserClient::IReplicationDiscoveryContext* NativeContext = nullptr;` — Set by FUObjectAdapterReplicationDiscoverer for the duration of the registation
- L33 _public prototype_ `virtual void AddPropertiesToObject(UObject* Object, const TArray<FConcertPropertyChainWrapper>& PropertiesToAdd) override;` — `UFUNCTION(BlueprintCallable, Category = "Multi-user")`
- L35 _public prototype_ `virtual void AddAdditionalObject(UObject* Object) override;` — `UFUNCTION(BlueprintCallable, Category = "Multi-user")`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClientLibrary/Private/Replication/UObjectAdapterReplicationDiscoverer.h` (Private)


#### class `UE::MultiUserClientLibrary::FUObjectAdapterReplicationDiscoverer`  
`class FUObjectAdapterReplicationDiscoverer : public MultiUserClient::IReplicationDiscoverer , public FGCObject`  
_L17-38_
- inherits: `MultiUserClient::IReplicationDiscoverer,FGCObject`
- desc: This discovery implementation checks whether the target UObject implements IConcertReplicationRegistration, and calls the equivalent functions on it. @see IMultiUserReplicationRegistration
- L23 _public prototype_ `FUObjectAdapterReplicationDiscoverer();`
- L26 _public prototype_ `virtual void DiscoverReplicationSettings(const MultiUserClient::FReplicationDiscoveryParams& Params) override;`
- L30 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L31 _public prototype_ `virtual FString GetReferencerName() const override;`
- L37 _private member_ `TObjectPtr<UMultiUserReplicationRegistrationContextImpl> Context;` — Passed to IMultiUserReplicationRegistration. We set the IReplicationDiscoveryContext for every call of DiscoverReplicationSettings.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClientLibrary` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClientLibrary/Public/Data/MultiUserClientDisplayInfo.h` (Public)


#### struct `FMultiUserClientDisplayInfo`  
`struct FMultiUserClientDisplayInfo`  
_L10-22_
- reflection: `USTRUCT(BlueprintType)`
- desc: Blueprint copy of FConcertClientInfo. Can describe offline clients, too.
- L16 _public member_ `FString DisplayName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Client Info")` — Holds the display name of the user that owns this instance.
- L18 _public prototype_ `FMultiUserClientDisplayInfo() = default;`
- L19 _public function_ `explicit FMultiUserClientDisplayInfo(const FConcertClientInfo& ClientInfo) : DisplayName(ClientInfo.DisplayName)`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClientLibrary/Public/MultiUserClientStatics.h` (Public)


#### struct `FMultiUserClientInfo`  
`struct FMultiUserClientInfo`  
_L28-53_
- reflection: `USTRUCT(BlueprintType)`
- desc: BP copy of FConcertSessionClientInfo Holds info on a client connected through multi-user
- L34 _public member_ `FGuid ClientEndpointId;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Client Info")` — Holds the display name of the user that owns this instance.
- L38 _public member_ `FString DisplayName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Client Info")` — Holds the display name of the user that owns this instance.
- L42 _public member_ `FLinearColor AvatarColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Client Info")` — Holds the color of the user avatar in a session.
- L46 _public member_ `TArray<FName> Tags;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = "Client Info")` — Holds an array of tags that can be used for grouping and categorizing.
- L48 _public prototype_ `FMultiUserClientInfo() = default;`
- L50 _public prototype_ `explicit FMultiUserClientInfo(const FConcertSessionClientInfo& ClientInfo);`
- L51 _public prototype_ `explicit FMultiUserClientInfo(const FGuid& ClientId, const FConcertClientInfo& ClientInfo);`

#### struct `FMultiUserSessionInfo`  
`struct FMultiUserSessionInfo`  
_L60-83_
- reflection: `USTRUCT(BlueprintType)`
- desc: BP copy of FConcertSessionInfo Holds info on a connected session.
- L66 _public member_ `FGuid ServerEndpointId;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Session Info")` — Holds the server endpoint id for this session.
- L70 _public member_ `FString SessionName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Session Info")` — Holds the session name current connected.
- L74 _public member_ `FString ServerName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Session Info")` — Holds the server name for the connected session.
- L78 _public member_ `FString EndpointName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Session Info")` — Holds the resolved endpoint name (HostPC) for the connected session.
- L82 _public member_ `bool bValid = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Session Info")` — Indicates if the current session info is valid. If we are connected to a session this is true, otherwise false.

#### class `UMultiUserClientSyncDatabase`  
`class UMultiUserClientSyncDatabase : public UObject`  
_L86-93_
- reflection: `UCLASS()`
- inherits: `UObject`
- L92 _public member_ `FOnPackageSavedSignature OnPackageSaved;` — `UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category="Save Package Delegate")`

#### enum `EMultiUserConnectionError`  
`enum class EMultiUserConnectionError`  
_L100-112_
- reflection: `UENUM(meta=(ScriptName="MultiUserConnectionErrorType"))`
- desc: Enum of the known Multi-User connection error, their value needs to match the internally returned error code. @see FConcertConnectionError
- L102 _public enumerator_ `None = 0`
- L103 _public enumerator_ `Canceled = 1`
- L104 _public enumerator_ `ConnectionAttemptAborted = 2`
- L105 _public enumerator_ `ServerNotResponding = 3`
- L106 _public enumerator_ `ServerError = 4`
- L107 _public enumerator_ `WorkspaceValidationUnknown = 100`
- L108 _public enumerator_ `SourceControlValidationUnknown = 110`
- L109 _public enumerator_ `SourceControlValidationCanceled = 111`
- L110 _public enumerator_ `SourceControlValidationError = 112`
- L111 _public enumerator_ `DirtyPackageValidationError = 113`

#### struct `FMultiUserConnectionError`  
`struct FMultiUserConnectionError`  
_L115-124_
- reflection: `USTRUCT(BlueprintType)`
- L120 _public member_ `EMultiUserConnectionError ErrorCode = EMultiUserConnectionError::None;` — `UPROPERTY(BlueprintReadOnly, Category = "Connection Error")`
- L123 _public member_ `FText ErrorMessage;` — `UPROPERTY(BlueprintReadOnly, Category = "Connection Error")`

#### enum `EMultiUserSourceValidationMode`  
`enum class EMultiUserSourceValidationMode : uint8`  
_L127-139_
- reflection: `UENUM(BlueprintType)`
- L130 _public enumerator_ `Hard = 0` — Source control validation will fail on any changes when connecting to a Multi-User Session.
- L136 _public enumerator_ `Soft` — Source control validation will warn and prompt on any changes when connecting to a Multi-User session. In Memory changes will be hot-reloaded. Source control changes aren't affected but will be stashed/shelved in the future.
- L138 _public enumerator_ `SoftAutoProceed` — Soft validation mode with auto proceed on prompts.

#### struct `FMultiUserClientConfig`  
`struct FMultiUserClientConfig`  
_L142-157_
- reflection: `USTRUCT(BlueprintType)`
- L147 _public member_ `FString DefaultServerURL;` — `UPROPERTY(BlueprintReadWrite, Category = "Client Settings")`
- L150 _public member_ `FString DefaultSessionName;` — `UPROPERTY(BlueprintReadWrite, Category = "Client Settings")`
- L153 _public member_ `FString DefaultSessionToRestore;` — `UPROPERTY(BlueprintReadWrite, Category = "Client Settings")`
- L156 _public member_ `EMultiUserSourceValidationMode ValidationMode = EMultiUserSourceValidationMode::Hard;` — `UPROPERTY(BlueprintReadWrite, Category = "Revision Control Settings", meta = (Keywords = "Source Control"))`

#### enum `EMultiUserConnectionStatus`  
`enum class EMultiUserConnectionStatus : uint8`  
_L161-171_
- reflection: `UENUM(BlueprintType)`
- desc: Connection status for Multi-User client sessions
- L164 _public enumerator_ `Connecting` — Currently establishing connection to the server session
- L166 _public enumerator_ `Connected` — Connection established and alive
- L168 _public enumerator_ `Disconnecting` — Currently severing connection to the server session gracefully
- L170 _public enumerator_ `Disconnected` — Disconnected

#### enum `EMultiUserClientStatus`  
`enum class EMultiUserClientStatus : uint8`  
_L175-183_
- reflection: `UENUM(BlueprintType)`
- desc: Exposes EConcertClientStatus
- L178 _public enumerator_ `Connected` — Client connected
- L180 _public enumerator_ `Disconnected` — Client disconnected
- L182 _public enumerator_ `Updated` — Client state updated

#### class `UMultiUserClientStatics`  
`class UMultiUserClientStatics : public UBlueprintFunctionLibrary`  
_L199-280_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L207 _public prototype_ `static void SetMultiUserPresenceEnabled(const bool IsEnabled = true);` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Presence", meta=(DevelopmentOnly, DisplayName = "Set Multi-User Presence Enabled"))` — Set whether presence is currently enabled and should be shown (unless hidden by other settings)
- L211 _public prototype_ `static void SetMultiUserPresenceVisibility(const FString& Name, bool Visibility, bool PropagateToAll = false);` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Presence", meta=(DevelopmentOnly, DisplayName = "Set Multi-User Presence Visibility"))` — Set Presence Actor Visibility by display name
- L215 _public prototype_ `static void SetMultiUserPresenceVisibilityById(const FGuid& ClientEndpointId, bool Visibility, bool PropagateToAll = false);` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Presence", meta = (DevelopmentOnly, DisplayName = "Set Multi-User Presence Visibility By Id"))` — Set Presence Actor Visibility by client id
- L219 _public prototype_ `static FTransform GetMultiUserPresenceTransform(const FGuid& ClientEndpointId);` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Presence", meta = (DevelopmentOnly, DisplayName = "Get Multi-User Presence Transform"))` — Get the Presence Actor transform for the specified client endpoint id or identity if the client isn't found
- L223 _public prototype_ `static void JumpToMultiUserPresence(const FString& OtherUserName, FTransform TransformOffset);` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Presence", meta = (DevelopmentOnly, DisplayName = "Jump to Multi-User Presence"))` — Teleport to another Multi-User user's presence.
- L227 _public prototype_ `static void UpdateWorkspaceModifiedPackages();` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Revision Control", meta=(DevelopmentOnly, DeprecatedFunction, DeprecationMessage = "UpdateWorkspaceModifiedPackages is deprecated. Please use PersistMultiUserSessionChanges instead.", Keywords = "Source Control"))` — Update Multi-User Workspace Modified Packages to be in sync for source control submission.
- L231 _public prototype_ `static void PersistMultiUserSessionChanges();` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Revision Control", meta=(DevelopmentOnly, DisplayName = "Persist Multi-User Session Changes", Keywords = "Source Control"))` — Persist the session changes and prepare the files for source control submission.
- L235 _public prototype_ `static void PersistSpecifiedPackages(const TArray<FName>& PackagesToPersist);` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Source Control", meta=(DevelopmentOnly, DsiplayName = "Persist Multi-User Sessions Changes (By Package name)"))` — Persist the specified sessions changes using source control.
- L239 _public prototype_ `static TArray<FName> GatherSessionChanges(bool IgnorePersisted = true);` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Source Control", meta=(DevelopmentOnly, DsiplayName = "Get List of Packages that have changed."))` — Get the list of packages that have changed since the last persist unless ignore persisted is false.
- L243 _public prototype_ `static UMultiUserClientSyncDatabase* GetConcertSyncDatabase();` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Source Control", meta=(DevelopmentOnly, DsiplayName = "Get Multi-user Sync Database."))` — Get the proxy object for the sync database.
- L247 _public prototype_ `static FMultiUserClientInfo GetLocalMultiUserClientInfo();` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Client", meta=(DevelopmentOnly, DisplayName = "Get Local Multi-User Client Info"))` — Get the local ClientInfo. Works when not connected to a session.
- L251 _public prototype_ `static FMultiUserSessionInfo GetMultiUserSessionInfo();` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Client", meta=(DevelopmentOnly, DisplayName = "Get Multi-User Session Info"))` — Get the current SessionInfo. Works when not connected to a session, but returns an empty session info.
- L255 _public prototype_ `static bool GetMultiUserClientInfoByName(const FString& ClientName, FMultiUserClientInfo& ClientInfo);` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Client", meta=(DevelopmentOnly, DisplayName = "Get Multi-User Client Info by Name"))` — Get the ClientInfo for any Multi-User participant by name. The local user is found even when not connected to a session. Returns false is no client was found.
- L259 _public prototype_ `static bool GetRemoteMultiUserClientInfos(TArray<FMultiUserClientInfo>& ClientInfos);` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Client", meta=(DevelopmentOnly, DisplayName = "Get Remote Multi-User Client Infos"))` — Get ClientInfos of current Multi-User participants except for the local user. Returns false is no remote clients were found.
- L263 _public prototype_ `static bool ConfigureMultiUserClient(const FMultiUserClientConfig& ClientConfig);` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Client", meta=(DevelopmentOnly, DisplayName = "Configure Multi-User Client"))` — Configure the Multi-User client.
- L267 _public prototype_ `static bool StartMultiUserDefaultConnection();` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Client", meta=(DevelopmentOnly, DisplayName = "Start Multi-User Default Connection"))` — Start the Multi-User default connection process.
- L271 _public prototype_ `static FMultiUserConnectionError GetLastMultiUserConnectionError();` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Client", meta = (DevelopmentOnly, DisplayName = "Get Last Multi-User Connection Error"))` — Get the last Multi-User connection error that happened, if any
- L275 _public prototype_ `static EMultiUserConnectionStatus GetMultiUserConnectionStatusDetail();` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Client", meta=(DevelopmentOnly, DisplayName = "Get Multi-User Connection Status Detail"))` — Get Multi-User connection status.
- L279 _public prototype_ `static bool GetMultiUserConnectionStatus();` — `UFUNCTION(BlueprintCallable, Category = "Multi-User Client", meta=(DevelopmentOnly, DeprecatedFunction, DeprecationMessage = "'Get Multi-User Connection Status' is deprecated. Please use 'Get Multi-User Connection Status Detail' instead.", DisplayName = "Get Multi-User Connection Status"))` — Get Multi-User connection status.

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPackageSavedSignature, FName, PackageName);` — Delegate that is invoked when a package is saved.
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPackageSavedSignature, FName, PackageName);` — Delegate that is invoked when a package is saved.
- L185 _namespace_ `namespace UE`
- L185 _namespace_ `namespace MultiUserClientLibrary` (scope `UE`)
- L189 _prototype_ `FMultiUserClientInfo ConvertClientInfo(const FGuid& ClientEndpointId, const FConcertClientInfo& ClientInfo);` (scope `UE::MultiUserClientLibrary`) — `UE_DEPRECATED(5.5, "Use FMultiUserClientInfo contructor instead.")`
- L190 _prototype_ `FMultiUserConnectionError ConvertConnectionError(FConcertConnectionError Error);` (scope `UE::MultiUserClientLibrary`)
- L191 _prototype_ `UConcertClientConfig* ModifyClientConfig(const FMultiUserClientConfig& InClientConfig);` (scope `UE::MultiUserClientLibrary`)
- L192 _prototype_ `EMultiUserConnectionStatus ConvertConnectionStatus(EConcertConnectionStatus ConnectionStatus);` (scope `UE::MultiUserClientLibrary`)
- L193 _prototype_ `FMultiUserSessionInfo ConvertSessionInfo(const FConcertSessionInfo& InSessionInfo, const FConcertServerInfo& InServerInfo);` (scope `UE::MultiUserClientLibrary`)
- L194 _prototype_ `EMultiUserClientStatus ConvertClientStatus(EConcertClientStatus Status);` (scope `UE::MultiUserClientLibrary`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClientLibrary/Public/MultiUserSubsystem.h` (Public)


#### struct `FMultiUserBlueprintEventData`  
`struct FMultiUserBlueprintEventData`  
_L22-27_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `TSharedPtr<FConcertBlueprintEvent> SharedEventDataPtr;`

#### class `UMultiUserSubsystem`  
`class UMultiUserSubsystem : public UEngineSubsystem`  
_L32-126_
- reflection: `UCLASS(BlueprintType, Category = "Multi-user", DisplayName = "MultiUserSubsystem")`
- inherits: `UEngineSubsystem`
- L36 _private prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L37 _private prototype_ `virtual void Deinitialize() override;`
- L43 _public member_ `FOnSessionConnected OnSessionConnected;` — `UPROPERTY(BlueprintAssignable, Category = "Multi-user")` — Invoked when the local editor instance has joined a session.
- L47 _public member_ `FOnSessionDisconnected OnSessionDisconnected;` — `UPROPERTY(BlueprintAssignable, Category = "Multi-user")` — Invoked when the local editor instanced has left a session.
- L54 _public member_ `FOnSessionClientChanged OnSessionClientChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Multi-user")` — Invoked when information about a client changes while the local editor instance is in a session. For example: other clients joining and leaving the session.
- L60 _public prototype_ `bool IsConnectedToSession() const;` — `UFUNCTION(BlueprintCallable, Category = "Multi-user")` — Returns true if we are currently in a session.
- L67 _public prototype_ `bool GetLocalClientId(FGuid& OutClientId) const;` — `UFUNCTION(BlueprintPure, Category = "Multi-user")` — If connected to a session, gets the endpoint identifiers of client corresponding to the local editor instance. @return Whether OutClientId contains a valid identifiers.
- L73 _public prototype_ `bool GetRemoteClientIds(TArray<FGuid>& OutRemoteClientIds);` — `UFUNCTION(BlueprintPure, Category = "Multi-user")` — If connected to a session, gets the endpoint identifiers of all remote clients. @return Whether OutRemoteClientIds contains the remote client endpoint identifiers.
- L82 _public prototype_ `void K2_SendCustomEvent(const int32& EventData);` — `UFUNCTION(BlueprintCallable, CustomThunk, Category="Multi-user", meta=(CustomStructureParam="EventData", AllowAbstract="false", DisplayName="Send Custom Event"))` — Send a custom event message over multi-user.  If you a not in an active session, this function does nothing and only reports and warning to the output log. @param EventData			The event data to send. This must be the same type of UScriptStruct expected by the receivers on the registered handler.
- L93 _public prototype_ `void K2_ExtractEventData(UPARAM(ref) FMultiUserBlueprintEventData& EventData, UPARAM(ref) int32& StructOut);` — `UFUNCTION(BlueprintCallable, CustomThunk, Category="Multi-user", meta=(CustomStructureParam="StructOut", AllowAbstract="false", DisplayName="Extract Event Data"))` — Extract event message data. Given a MultiUserBlueprintEventData extract the message contents and put it into the desired struct.  The struct must match the target type. @param StructOut	   The a reference to the structure that will receive the data.
- L106 _public prototype_ `bool RegisterCustomEventHandler(const UStruct* EventType, FCustomEventHandler InEventHandler);` — `UFUNCTION(BlueprintCallable, Category = "Multi-user")` — Register an event handler for the given type. Only one handler per type is allowed. You should register your handler on session connected and remove the handler when the session disconnects. @param EventType   The struct type that we support handling. @return true if the type handler was accepted.
- L116 _public prototype_ `bool UnregisterCustomEventHandler(const UStruct* EventType);` — `UFUNCTION(BlueprintCallable, Category = "Multi-user")` — Unregister an event handler for the given type. @param EventType   The struct type that we support handling. @return true if the type handler was successfully unregistered.
- L119 _public prototype_ `void DispatchEvent(const FConcertBlueprintEvent& InEvent);` — Public interface to send the event to the registered blueprint handler.
- L122 _private member_ `TMap<FName, FCustomEventHandler> CustomEventHandlerTable;` — Table of registered handlers.
- L125 _private prototype_ `void SendCustomEvent(const FConcertBlueprintEvent& EventData);` — Internal send custom event message.

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSessionConnected);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSessionConnected);`
- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSessionDisconnected);`
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSessionDisconnected);`
- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSessionClientChanged, EMultiUserClientStatus, Status, const FMultiUserClientInfo&, ClientInfo);`
- L19 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSessionClientChanged, EMultiUserClientStatus, Status, const FMultiUserClientInfo&, ClientInfo);`
- L29 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FCustomEventHandler, FMultiUserBlueprintEventData, Data);`
- L29 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FCustomEventHandler, FMultiUserBlueprintEventData, Data);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClientLibrary/Public/Replication/Async/ChangeClientAsyncAction.h` (Public)


#### class `UChangeClientAsyncAction`  
`class UChangeClientAsyncAction : public UBlueprintAsyncActionBase`  
_L14-49_
- reflection: `UCLASS()`
- inherits: `UBlueprintAsyncActionBase`
- desc: Enqueues a request for changing a specific client's stream and / or authority. This class exposes IMultiUserReplication::EnqueueChanges.
- L19 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeOperationCompleted, const FMultiUserChangeClientReplicationResult&, Response);`
- L23 _public member_ `FOnChangeOperationCompleted OnCompleted;` — `UPROPERTY(BlueprintAssignable, Category = "Multi-user")` — Event that triggers when the operation completes.
- L36 _public prototype_ `static UChangeClientAsyncAction* ChangeClient(const FGuid& ClientId, FMultiUserChangeClientReplicationRequest Request);` — `UFUNCTION(BlueprintCallable, Category = "Multi-user", meta = (BlueprintInternalUseOnly = "true", Keywords = "Change Client Stream Authority Ownership Replication"))` — Allows changing of a client's stream and authority. A stream is a mapping of objects to properties, i.e. registered objects. A client must request to take authority over objects they have registered previously. If there is no conflict with other clients, the server approves the request and the client starts replicating automatically. @param ClientId The client for which this request is to be sent; can be the local or a remote client. @param Request The request specifying a change to stream, authority, or both.
- L39 _public prototype_ `virtual void Activate() override;`
- L45 _private member_ `FGuid ClientId;` — `UPROPERTY(Transient)`
- L48 _private member_ `FMultiUserChangeClientReplicationRequest ReplicationRequest;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeOperationCompleted, const FMultiUserChangeClientReplicationResult&, Response);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClientLibrary/Public/Replication/Async/ChangeClientBlueprintParams.h` (Public)


#### enum `EMultiUserChangeStreamOperationResult`  
`enum class EMultiUserChangeStreamOperationResult : uint8`  
_L16-45_
- reflection: `UENUM(BlueprintType)`
- desc: Result of changing a client's stream
- L19 _public enumerator_ `Success` — All changes made or none were requested.
- L21 _public enumerator_ `NoChanges` — No changes were requested to be made
- L26 _public enumerator_ `Rejected` — The changes were rejected by the server.
- L28 _public enumerator_ `Timeout` — Failed because the request timed out.
- L30 _public enumerator_ `Cancelled` — The submission progress was cancelled, e.g. because the target client disconnected.
- L33 _public enumerator_ `FailedToSendRequest` — Unlikely. ISubmissionWorkflow validation rejected the change. See log. Could be e.g. that the remote client does not allow remote editing.
- L38 _public enumerator_ `NotInSession` — No submission took place because the local editor is not in any session.
- L40 _public enumerator_ `UnknownClient` — No submission took place because the client ID was invalid.
- L42 _public enumerator_ `NotOnGameThread` — The request was not made on the game thread.
- L44 _public enumerator_ `NotAvailable` — The MultiUserClient module is not available. Usually when you're in a runtime build but the operation can only be run in editor builds.

#### enum `EMultiUserChangeAuthorityOperationResult`  
`enum class EMultiUserChangeAuthorityOperationResult : uint8`  
_L49-80_
- reflection: `UENUM(BlueprintType)`
- desc: Result of changing a client's authority
- L52 _public enumerator_ `Success` — All changes made or none were requested.
- L54 _public enumerator_ `NoChanges` — No changes were requested to be made
- L59 _public enumerator_ `RejectedFullyOrPartially` — Some of the authority changes were rejected by the server.
- L61 _public enumerator_ `Timeout` — Failed because the request timed out.
- L63 _public enumerator_ `CancelledDueToStreamUpdate` — The authority change was not submitted because the stream change was unsuccessful.
- L65 _public enumerator_ `Cancelled` — The submission progress was cancelled, e.g. because the target client disconnected.
- L68 _public enumerator_ `FailedToSendRequest` — Unlikely. ISubmissionWorkflow validation rejected the change. See log. Could be e.g. that the remote client does not allow remote editing.
- L73 _public enumerator_ `NotInSession` — No submission took place because the local editor is not in any session.
- L75 _public enumerator_ `UnknownClient` — No submission took place because the client ID was invalid.
- L77 _public enumerator_ `NotOnGameThread` — The request was not made on the game thread.
- L79 _public enumerator_ `NotAvailable` — The MultiUserClient module is not available. Usually when you're in a runtime build but the operation can only be run in editor builds.

#### enum `EMultiUserPropertyChangeType`  
`enum class EMultiUserPropertyChangeType : uint8`  
_L83-91_
- reflection: `UENUM(BlueprintType)`
- L86 _public enumerator_ `Put` — Replace all assigned properties with the given properties.
- L88 _public enumerator_ `Add` — Append the given properties, keeping any preexisting properties.
- L90 _public enumerator_ `Remove` — Remove the given properties.

#### struct `FMultiUserPropertyChange`  
`struct FMultiUserPropertyChange`  
_L94-105_
- reflection: `USTRUCT(BlueprintType)`
- L100 _public member_ `TArray<FConcertPropertyChainWrapper> Properties;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-user")` — The properties for the object. See ChangeType for how they are used
- L104 _public member_ `EMultiUserPropertyChangeType ChangeType = EMultiUserPropertyChangeType::Add;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-user")` — How you want Properties to be applied to the object.

#### enum `EMultiUserObjectReplicationMode`  
`enum class EMultiUserObjectReplicationMode : uint8`  
_L108-114_
- reflection: `UENUM(BlueprintType)`
- L111 _public enumerator_ `SpecifiedRate` — Replicate at the rate specified at FMultiUserObjectReplicationSettings::ReplicationRate
- L113 _public enumerator_ `Realtime` — Replicate the object as often as possible: every tick.

#### struct `FMultiUserObjectReplicationSettings`  
`struct FMultiUserObjectReplicationSettings`  
_L118-129_
- reflection: `USTRUCT(BlueprintType)`
- desc: Frequency settings for a particular object
- L124 _public member_ `EMultiUserObjectReplicationMode Mode = EMultiUserObjectReplicationMode::SpecifiedRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-user")` — Determines whether to send a replication event every tick (Realtime) or at the specified rate (SpecifiedRate).
- L128 _public member_ `uint8 ReplicationRate = 30;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-user")` — If Mode == SpecifiedRate, then replicate this many times per second.

#### struct `FMultiUserFrequencyChangeRequest`  
`struct FMultiUserFrequencyChangeRequest`  
_L138-159_
- reflection: `USTRUCT(BlueprintType)`
- desc: Params for changing how often objects replicate. All objects default to a global setting that can be changed by setting bChangeDefaults = true and changing NewDefaults to contain the new defaults. Objects can have overrides mutated via OverridesToAdd and OverridesToRemove. Overrides override the default behavior.
- L144 _public member_ `TSet<FSoftObjectPath> OverridesToRemove;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-user")` — Objects for which to remove overrides.
- L148 _public member_ `TMap<FSoftObjectPath, FMultiUserObjectReplicationSettings> OverridesToAdd;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-user")` — Objects for which to add overrides
- L152 _public member_ `FMultiUserObjectReplicationSettings NewDefaults;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-user")` — Set new frequency defaults for all objects that do not have any overrides.
- L156 _public member_ `bool bChangeDefaults = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-user")` — Whether to replace the defaults currently registered on the server with the ones specified in NewDefaults.
- L158 _public function_ `bool IsEmpty() const`

#### struct `FMultiUserChangeStreamRequest`  
`struct FMultiUserChangeStreamRequest`  
_L163-180_
- reflection: `USTRUCT(BlueprintType)`
- desc: Params for changing a client's stream.
- L169 _public member_ `TMap<TObjectPtr<UObject>, FMultiUserPropertyChange> PropertyChanges;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-user")` — Property changes to make to objects.
- L173 _public member_ `TSet<FSoftObjectPath> ObjectsToRemove;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-user")` — Objects that should be unregistered (they will also stop replicating if added here)
- L177 _public member_ `FMultiUserFrequencyChangeRequest FrequencyChanges;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-user")` — Change how often objects are supposed to be replicated.
- L179 _public function_ `bool IsEmpty() const`

#### struct `FMultiUserChangeAuthorityRequest`  
`struct FMultiUserChangeAuthorityRequest`  
_L184-197_
- reflection: `USTRUCT(BlueprintType)`
- desc: Params for changing a client's authority (what they're replicating).
- L190 _public member_ `TSet<FSoftObjectPath> ObjectsToStartReplicating;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-user")` — Objects that should start replicating. The objects must previously have been registered.
- L194 _public member_ `TSet<FSoftObjectPath> ObjectToStopReplicating;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-user")` — Objects that should stop replicating.
- L196 _public function_ `bool IsEmpty() const`

#### struct `FMultiUserChangeClientReplicationRequest`  
`struct FMultiUserChangeClientReplicationRequest`  
_L201-218_
- reflection: `USTRUCT(BlueprintType)`
- desc: Params for changing a client's stream or authority.
- L210 _public member_ `FMultiUserChangeStreamRequest StreamChangeRequest;` — `UPROPERTY(BlueprintReadWrite, Category = "Multi-user")` — Changes to make to the client's registered objects. Performed before AuthorityChangeRequest. If it fails, AuthorityChangeRequest will also fail.
- L217 _public member_ `FMultiUserChangeAuthorityRequest AuthorityChangeRequest;` — `UPROPERTY(BlueprintReadWrite, Category = "Multi-user")` — Changes to make to the objects the client is replicating. Fails if StreamChangeRequest fails.

#### enum `EMultiUserChangeFrequencyErrorCode`  
`enum class EMultiUserChangeFrequencyErrorCode : uint8`  
_L221-230_
- reflection: `UENUM(BlueprintType)`
- L224 _public enumerator_ `UnregisteredStream` — The object for which the frequency was being changed was not registered.
- L226 _public enumerator_ `InvalidReplicationRate` — The replication rate parameter was rejected (it cannot be 0).
- L229 _public enumerator_ `Count UMETA(Hidden)` — Not an actual parameter. Make sure it's always last.

#### struct `FChangeClientStreamFrequencyResponse`  
`struct FChangeClientStreamFrequencyResponse`  
_L234-245_
- reflection: `USTRUCT(BlueprintType)`
- desc: Result about changing frequency.
- L240 _public member_ `TMap<FSoftObjectPath, EMultiUserChangeFrequencyErrorCode> ObjectErrors;` — `UPROPERTY(BlueprintReadOnly, Category = "Multi-user")` — Errors encountered for specific objects
- L244 _public member_ `TOptional<EMultiUserChangeFrequencyErrorCode> DefaultChangeErrorCode;` — `UPROPERTY(BlueprintReadOnly, Category = "Multi-user")` — Error for changing the default replication frequency.

#### enum `EMultiUserPutObjectErrorCode`  
`enum class EMultiUserPutObjectErrorCode : uint8`  
_L249-261_
- reflection: `UENUM(BlueprintType)`
- desc: Explains why a change to an object in the stream was invalid.
- L252 _public enumerator_ `UnresolvedStream` — Stream that the object referenced was not registered on the server.
- L257 _public enumerator_ `MissingData` — Either PutObject contained no data to update with (ensure either ClassPath or Properties is set), or it tried to create a new object with insufficient data (make sure ClassPath and Properties are both specified).
- L260 _public enumerator_ `Count UMETA(Hidden)` — Not an actual parameter. Make sure it's always last.

#### struct `FMultiUserChangeClientStreamResponse`  
`struct FMultiUserChangeClientStreamResponse`  
_L264-296_
- reflection: `USTRUCT(BlueprintType)`
- L270 _public member_ `EMultiUserChangeStreamOperationResult ErrorCode = EMultiUserChangeStreamOperationResult::Timeout;` — `UPROPERTY(BlueprintReadOnly, Category = "Multi-user")` — The error code of changing streams.
- L280 _public member_ `TMap<FSoftObjectPath, FGuid> AuthorityConflicts;` — `UPROPERTY(BlueprintReadOnly, Category = "Multi-user")` — Dynamic authority errors. The change was rejected because 1. this client is replicating the object already, 2. another client is also replicating the object, 3. this change would cause overlapping properties with the other client.
- L284 _public member_ `TMap<FSoftObjectPath, EMultiUserPutObjectErrorCode> SemanticErrors;` — `UPROPERTY(BlueprintReadOnly, Category = "Multi-user")` — Errors made in the format of the request
- L288 _public member_ `FChangeClientStreamFrequencyResponse FrequencyErrors;` — `UPROPERTY(BlueprintReadOnly, Category = "Multi-user")` — Errors made in the way frequency was changed.
- L295 _public member_ `bool bFailedStreamCreation = false;` — `UPROPERTY(BlueprintReadOnly, Category = "Multi-user")` — The client attempted to register the Multi-User stream but failed in doing so. This usually indicates an internal error that you cannot do anything about as API user.

#### struct `FMultiUserChangeClientAuthorityResponse`  
`struct FMultiUserChangeClientAuthorityResponse`  
_L299-310_
- reflection: `USTRUCT(BlueprintType)`
- L305 _public member_ `EMultiUserChangeAuthorityOperationResult ErrorCode = EMultiUserChangeAuthorityOperationResult::Timeout;` — `UPROPERTY(BlueprintReadOnly, Category = "Multi-user")` — The error code of changing authority. Fails if StreamChangeResult fails.
- L309 _public member_ `TSet<FSoftObjectPath> RejectedObjects;` — `UPROPERTY(BlueprintReadOnly, Category = "Multi-user")` — Objects the client did not get authority over.

#### struct `FMultiUserChangeClientReplicationResult`  
`struct FMultiUserChangeClientReplicationResult`  
_L314-331_
- reflection: `USTRUCT(BlueprintType)`
- desc: Result of processing a FChangeClientReplicationRequest.
- L323 _public member_ `FMultiUserChangeClientStreamResponse StreamResponse;` — `UPROPERTY(BlueprintReadOnly, Category = "Multi-user")` — The result of changing streams. You can inspect this for why the operation failed.
- L330 _public member_ `FMultiUserChangeClientAuthorityResponse AuthorityResponse;` — `UPROPERTY(BlueprintReadOnly, Category = "Multi-user")` — The result of changing authority. Fails if StreamChangeResult fails. You can inspect this for why the operation failed.

#### Free symbols / members of external scopes

- L333 _namespace_ `namespace UE`
- L333 _namespace_ `namespace MultiUserClientLibrary` (scope `UE`)
- L336 _prototype_ `EMultiUserChangeStreamOperationResult Transform(MultiUserClient::EChangeStreamOperationResult Data);` (scope `UE::MultiUserClientLibrary`)
- L337 _prototype_ `EMultiUserChangeAuthorityOperationResult Transform(MultiUserClient::EChangeAuthorityOperationResult Data);` (scope `UE::MultiUserClientLibrary`)
- L338 _prototype_ `EMultiUserChangeFrequencyErrorCode Transform(MultiUserClient::EChangeObjectFrequencyErrorCode Data);` (scope `UE::MultiUserClientLibrary`)
- L339 _prototype_ `EMultiUserPutObjectErrorCode Transform(MultiUserClient::EPutObjectErrorCode Data);` (scope `UE::MultiUserClientLibrary`)
- L341 _prototype_ `FMultiUserChangeClientStreamResponse Transform(MultiUserClient::FChangeClientStreamResponse Data);` (scope `UE::MultiUserClientLibrary`)
- L342 _prototype_ `FMultiUserChangeClientAuthorityResponse Transform(MultiUserClient::FChangeClientAuthorityResponse Data);` (scope `UE::MultiUserClientLibrary`)
- L343 _prototype_ `FMultiUserChangeClientReplicationResult Transform(MultiUserClient::FChangeClientReplicationResult Data);` (scope `UE::MultiUserClientLibrary`)
- L345 _prototype_ `MultiUserClient::EPropertyChangeType Transform(EMultiUserPropertyChangeType Data);` (scope `UE::MultiUserClientLibrary`)
- L346 _prototype_ `MultiUserClient::FPropertyChange Transform(FMultiUserPropertyChange Data);` (scope `UE::MultiUserClientLibrary`)
- L348 _prototype_ `EConcertObjectReplicationMode Transform(EMultiUserObjectReplicationMode Data);` (scope `UE::MultiUserClientLibrary`)
- L349 _prototype_ `EMultiUserObjectReplicationMode Transform(EConcertObjectReplicationMode Data);` (scope `UE::MultiUserClientLibrary`)
- L350 _prototype_ `FConcertObjectReplicationSettings Transform(const FMultiUserObjectReplicationSettings& Data);` (scope `UE::MultiUserClientLibrary`)
- L351 _prototype_ `FMultiUserObjectReplicationSettings Transform(const FConcertObjectReplicationSettings& Data);` (scope `UE::MultiUserClientLibrary`)
- L353 _prototype_ `MultiUserClient::FChangeStreamRequest Transform(FMultiUserChangeStreamRequest Data);` (scope `UE::MultiUserClientLibrary`)
- L354 _prototype_ `MultiUserClient::FChangeAuthorityRequest Transform(FMultiUserChangeAuthorityRequest Data);` (scope `UE::MultiUserClientLibrary`)
- L355 _prototype_ `MultiUserClient::FChangeClientReplicationRequest Transform(FMultiUserChangeClientReplicationRequest Data);` (scope `UE::MultiUserClientLibrary`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClientLibrary/Public/Replication/IMultiUserReplicationRegistration.h` (Public)


#### class `UMultiUserReplicationRegistration`  
`class UMultiUserReplicationRegistration : public UInterface`  
_L16-19_
- reflection: `UINTERFACE()`
- inherits: `UInterface`

#### struct `FMultiUserReplicationRegistrationParams`  
`struct FMultiUserReplicationRegistrationParams`  
_L22-33_
- reflection: `USTRUCT(BlueprintType)`
- L28 _public member_ `FGuid ClientEndpointId;` — `UPROPERTY(BlueprintReadOnly, Category = "Multi-user")` — The client for which the objects and properties are being registered.
- L32 _public member_ `TScriptInterface<IMultiUserReplicationRegistrationContext> Context;` — `UPROPERTY(BlueprintReadOnly, Category = "Multi-user")` — Uses this to register properties and add additional objects for discovery.

#### class `IMultiUserReplicationRegistration`  
`class IMultiUserReplicationRegistration`  
_L41-49_
- desc: Exposes IReplicationDiscoverer to Blueprints. FUObjectAdapterReplicationDiscoverer is used to adapt this interface to the native IReplicationDiscovery interface. @see FUObjectAdapterReplicationDiscoverer
- L48 _public prototype_ `void DiscoverReplicationSettings(const FMultiUserReplicationRegistrationParams& Params);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Multi-user|Replication")` — Registers properties and additional objects that must be replicated.

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClientLibrary/Public/Replication/IMultiUserReplicationRegistrationContext.h` (Public)


#### class `UMultiUserReplicationRegistrationContext`  
`class UMultiUserReplicationRegistrationContext : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(NotBlueprintable)`
- inherits: `UInterface`

#### class `IMultiUserReplicationRegistrationContext`  
`class IMultiUserReplicationRegistrationContext`  
_L20-47_
- desc: Given to IMultiUserReplicationRegistration to register properties and objects. @see IMultiUserReplicationRegistration
- L35 _public prototype_ `virtual void AddPropertiesToObject(UObject* Object, const TArray<FConcertPropertyChainWrapper>& PropertiesToAdd) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Multi-user")` — Extends the stream with the given object, if not yet added, and adds the properties to it. Properties will be automatically discovered for Object, as well. If the object implements IMultiUserReplicationRegistrationContext, it will be invoked on Object recursively. @param Object Object to add, if not yet present, and assign a property to @param PropertiesToAdd Property chain to associate with the object
- L46 _public prototype_ `virtual void AddAdditionalObject(UObject* Object) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Multi-user")` — Adds an additional object. Properties will be automatically discovered for Object, as well. If the object implements IMultiUserReplicationRegistrationContext, it will be invoked on Object recursively. @param Object The additional object to add

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClientLibrary/Public/Replication/MultiUserReplicationSubsystem.h` (Public)


#### class `UMultiUserReplicationSubsystem`  
`class UMultiUserReplicationSubsystem : public UEngineSubsystem`  
_L18-145_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: Exposes ways to interact with the Multi-user replication system via Blueprints.
- L25 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnServerStateChanged, const FGuid&, EndpointId);`
- L26 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOfflineClientsChanged);`
- L34 _public prototype_ `bool IsReplicatingObject(const FGuid& ClientId, const FSoftObjectPath& ObjectPath) const;` — `UFUNCTION(BlueprintPure, Category = "Multi-user")` — @return Whether the client is replicating the object. @note An object can be registered but not replicated. @see UMultiUserSubsystem::GetLocalClientId and UMultiUserSubsystem::GetRemoteClientIds
- L42 _public prototype_ `bool GetObjectReplicationFrequency(const FGuid& ClientId, const FSoftObjectPath& ObjectPath, FMultiUserObjectReplicationSettings& OutFrequency);` — `UFUNCTION(BlueprintPure, Category = "Multi-user")` — @return Whether OutFrequency was modified. @note An object can be registered but not replicated. @see UMultiUserSubsystem::GetLocalClientId and UMultiUserSubsystem::GetRemoteClientIds
- L50 _public prototype_ `TArray<FConcertPropertyChainWrapper> GetPropertiesRegisteredToObject(const FGuid& ClientId, const FSoftObjectPath& ObjectPath) const;` — `UFUNCTION(BlueprintPure, Category = "Multi-user")` — @return The properties the client has registered for replication for the object. @note An object can be registered but not replicated. Use IsReplicatingObject to find out whether the client is replicating the returned properties. @see UMultiUserSubsystem::GetLocalClientId and UMultiUserSubsystem::GetRemoteClientIds.
- L67 _public prototype_ `TArray<FSoftObjectPath> GetRegisteredObjects(const FGuid& ClientId) const;` — `UFUNCTION(BlueprintPure, Category = "Multi-user")` — Gets the objects the online or offline client has registered with the server. Just because an object is returned here, it does not mean that the object is being replicated: - If ClientId is an offline client, then the object is not being replicated by that client. - If ClientId is an online client, then the object(s) may only be registered with the server. To find out which objects are actually being replicated, use GetReplicatedObjects(), which will always contain GetRegisteredObjects(). @param ClientId The client of which to get the registered objects. @return The objects the client has @see UMultiUserSubsystem::GetLocalClientId and UMultiUserSubsystem::GetRemoteClientIds
- L81 _public prototype_ `TArray<FSoftObjectPath> GetReplicatedObjects(const FGuid& ClientId) const;` — `UFUNCTION(BlueprintPure, Category = "Multi-user")` — Gets the objects that are currently being replicated by the client. @note There is a difference between registered and replicated objects! Objects are registered with the server first and later the client can attempt to start replicating them. GetReplicatedObjects() will always contain GetRegisteredObjects(). @param ClientId The client of which to get the replicated objects. @return The objects being replicated by the client @see UMultiUserSubsystem::GetLocalClientId and UMultiUserSubsystem::GetRemoteClientIds
- L94 _public prototype_ `TArray<FGuid> GetOwningOfflineClients(const FSoftObjectPath& ObjectPath) const;` — `UFUNCTION(BlueprintPure, Category = "Multi-user", meta = (Keywords = "Owning Offline Disconnected Reclaim Join Rejoin Client Find Stream Registered"))` — A list of offline clients that, upon rejoining a session, will attempt to reclaim properties they previously registered for an object, regardless of whether the client left gracefully or due to a crash. By default, when a client disconnects (either gracefully or due to a crash) and later rejoins a session, the client attempts to re-register the properties it had previously registered for the object. @return A list of client descriptions representing offline clients that will attempt to reclaim properties associated with the object when they rejoin.
- L98 _public function_ `bool IsOwnedByOfflineClient(const FSoftObjectPath& ObjectPath) const` — `UFUNCTION(BlueprintPure, Category = "Multi-user", meta = (Keywords = "Owning Offline Disconnected Reclaim Join Rejoin Client Find Stream Registered"))` — @return Whether any offline clients will try to register properties for ObjectPath upon rejoining.
- L102 _public prototype_ `TArray<FGuid> GetOfflineClientIds() const;` — `UFUNCTION(BlueprintPure, Category = "Multi-user", meta = (Keywords = "Get Offline Disconnected Clients"))` — @return The list of offline clients. Each entry is an endpoint ID that a user had in the past.
- L105 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L106 _public prototype_ `virtual void Deinitialize() override;`
- L117 _private member_ `FOnServerStateChanged OnClientStreamServerStateChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Multi-user")` — Event triggered when the following changes about a client: - The registered object to properties bindings - The registered replication frequency setting of an object
- L121 _private member_ `FOnServerStateChanged OnClientAuthorityServerStateChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Multi-user")` — Event triggered a client changes the objects it is replicating.
- L125 _private member_ `FOnOfflineClientsChanged OnOfflineClientsChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Multi-user")` — Event triggered when the local list of offline clients has changed.
- L129 _private member_ `FOnServerStateChanged OnOfflineClientContentChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Multi-user")` — Event triggered when the content that an offline client will attempt to re-claim changes.
- L139 _private member_ `TSharedPtr<UE::MultiUserClientLibrary::FUObjectAdapterReplicationDiscoverer> UObjectAdapter;` — This is used only for when the adds an object through the Add button in the UI. This allows UObjects, the target being Blueprints, to implement the IConcertReplicationRegistration interface through which MU will use to auto-add properties when registering an object to a client's replication stream. Registered when this subsystem is initialized.
- L141 _private function_ `void BroadcastStreamsChanged(const FGuid& EndpointId) const`
- L142 _private function_ `void BroadcastAuthorityChanged(const FGuid& EndpointId) const`
- L143 _private function_ `void BroadcastOfflineClientsChanged() const`
- L144 _private function_ `void BroadcastOfflineClientContentChanged(const FGuid& EndpointId) const`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClientLibrary` (scope `UE`)
- L25 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnServerStateChanged, const FGuid&, EndpointId);`
- L26 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOfflineClientsChanged);`
