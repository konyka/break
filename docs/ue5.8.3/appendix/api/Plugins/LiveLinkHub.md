# Plugins / LiveLinkHub

- module root: `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub`
- headers: 74; symbols: 1672
- symbol kinds: class=73, delegate=30, enum=5, enumerator=15, externvar=1, function=479, macro=17, member=456, namespace=26, prototype=506, struct=30, typedef=4, variable=30
- DynamicallyLoadedModuleNames: SlateReflector
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, AssetTools, ContentBrowser, ContentBrowserAssetDataSource, ContentBrowserData, EditorStyle, Engine, InputCore, Json, JsonUtilities, LiveLink, LiveLinkEditor, LiveLinkHubMessaging, LiveLinkInterface, LiveLinkMessageBusFramework, MediaAssets, MediaIOCore, MediaProfile, MessageBusTesterEditor, Messaging, NamingTokens, OutputLog, ProjectSettingsViewer, SessionFrontend, SessionServices, Settings, SettingsEditor, SharedSettingsWidgets, Slate, SlateCore, StatusBar, TimeManagement, ToolMenus, ToolWidgets, TraceLog, UnrealEd
- PrivateIncludePathModuleNames: SlateReflector
- PublicDependencyModuleNames: Core, CoreUObject, LiveLinkInterface

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Clients/GameThreadMessageHandler.h` (Private)


#### class `TGameThreadMessageHandler`  
`template<typename MessageType, typename HandlerType> class TGameThreadMessageHandler : public IMessageHandler`  
_L17-73_
- inherits: `IMessageHandler`
- desc: Template for handlers that should handle their message on the game thread. @param MessageType The type of message to handle. @param HandlerType The type of the handler class.
- L23 _public typedef_ `typedef void (HandlerType::* FuncType)(const MessageType&, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>&);` — Type definition for function pointers that are compatible with this TGameThreadMessageHandler.
- L33 _public function_ `TGameThreadMessageHandler(HandlerType* InHandler, FuncType InFunc) : Handler(InHandler) , Func(InFunc)` — Creates and initializes a new message handler. @param InHandler The object that will handle the messages. @param InFunc The object's message handling function.
- L41 _public prototype_ `~TGameThreadMessageHandler() = default;` — Virtual destructor.
- L47 _public function_ `virtual void HandleMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context) override`
- L69 _private member_ `HandlerType* Handler;` — Holds a pointer to the object handling the messages.
- L72 _private member_ `FuncType Func;` — Holds a pointer to the actual handler function.

#### Free symbols / members of external scopes

- L52 _function_ `` (scope `TGameThreadMessageHandler::HandleMessage`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Clients/LiveLinkHubClientsController.h` (Private)


#### class `FLiveLinkHubClientsController`  
`class FLiveLinkHubClientsController`  
_L24-189_
- desc: Controller responsible for holding the list of connected clients and creating the clients view.
- L27 _public function_ `FLiveLinkHubClientsController(const TSharedRef<ILiveLinkHubClientsModel>& InClientsModel) : ClientsModel(InClientsModel)`
- L38 _public function_ `~FLiveLinkHubClientsController()`
- L52 _public function_ `TSharedRef<SWidget> MakeClientsView()` — Create the widget that displays connected UE clients.
- L61 _public function_ `TSharedRef<SWidget> MakeClientDetailsView()` — Create the widget that displays information about a given UE client.
- L83 _private function_ `void OnClientEvent(FLiveLinkHubClientId ClientIdentifier, ILiveLinkHubClientsModel::EClientEventType EventType)` — Update the client info details if we received new info about it.
- L115 _private function_ `void OnActiveSessionChanged(const TSharedRef<ILiveLinkHubSession>& ActiveSession)`
- L126 _private function_ `void UpdateClientDetails(FLiveLinkHubClientId Client)` — Handles updating client details in the client details panel.
- L150 _private function_ `void OnDiscoveredClientPicked(FLiveLinkHubClientId Client)`
- L155 _private function_ `void OnRemoveClientFromSession(FLiveLinkHubClientId Client)`
- L178 _private member_ `TSharedPtr<SLiveLinkHubClientsView> ClientsView;` — List view of UE clients the hub can connect to.
- L180 _private member_ `TSharedPtr<ILiveLinkHubClientsModel> ClientsModel;` — Ptr to the livelink hub.
- L182 _private member_ `TSharedPtr<TStructOnScope<FLiveLinkHubUEClientInfo>> UEClientInfo;` — Holds a struct representing information about the currently selected client.
- L184 _private member_ `FLiveLinkHubClientId DisplayedClientId;` — ID of the client displayed in the panel.
- L186 _private member_ `TSharedPtr<IStructureDetailsView> StructDetailsView;` — Holds the details view created with the property editor module.
- L188 _private member_ `FDelegateHandle ConnectionStatusChangedHandle;` — Delegate called when one of the connection's info has changed.

#### Free symbols / members of external scopes

- L76 _function_ `StructDetailsView->GetDetailsView()->SetIsPropertyReadOnlyDelegate(FIsPropertyReadOnly::CreateLambda([](const FPropertyAndParent&){ return true ;}));` (scope `FLiveLinkHubClientsController::MakeClientDetailsView`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Clients/LiveLinkHubProvider.h` (Private)


#### struct `FLiveLinkHubAddressBookEntry`  
`struct FLiveLinkHubAddressBookEntry`  
_L22-57_
- L25 _public member_ `FMessageAddress ControlEndpoint;` — Address of the MessagingModule endpoint that handles 'control' messages like Disconnect, Timecode and Genlock.
- L30 _public member_ `FMessageAddress DataEndpoint;` — Address of the actual LiveLink source that handles LiveLink data. @note: Only set after we receive a connection message.
- L32 _public member_ `FGuid SourceGuid;` — Id of the message bus source on the client side.
- L34 _public member_ `ELiveLinkTopologyMode TopologyMode = ELiveLinkTopologyMode::UnrealClient;` — TopologyMode of this entry.
- L36 _public member_ `FString IP;` — IP of the client.
- L38 _public member_ `FString Hostname;` — Hostname of the client.
- L40 _public member_ `FString ProjectName;` — Project that the client is in.
- L42 _public member_ `FString LevelName;` — Name of the current level.
- L44 _public member_ `double LastBeaconTimestamp = 0.0;` — Timestamp of the last beacon message received for this client.
- L46 _public member_ `bool bDisableAutoconnect = false;` — This is set when a user removes a client from the session so as to not autoconnect it again.
- L48 _public member_ `bool bConnected = false;` — Whether the provider has connected to it.
- L50 _public member_ `bool bSentDiscoveryRequest = false;` — Whether discovery (connection request) has been sent.
- L52 _public member_ `double LastDiscoveryRequestTimestamp = 0.0;` — Timestamp of the last discovery request messsage that was sent out.
- L54 _public member_ `FLiveLinkHubClientId ClientId = FLiveLinkHubClientId::NewId();` — ID of this client.
- L56 _public member_ `int32 DiscoveryProtocolVersion = 1;` — Version of the discovery protocol. V1 = Before 5.7, V2 = 5.7, after bringing the MBus source control logic to the LLH Messaging module.

#### class `FLiveLinkHubProvider`  
`class FLiveLinkHubProvider : public FLiveLinkProvider, public ILiveLinkHubClientsModel, public TSharedFromThis<FLiveLinkHubProvider>`  
_L62-261_
- inherits: `FLiveLinkProvider,ILiveLinkHubClientsModel,TSharedFromThis<FLiveLinkHubProvider>`
- desc: LiveLink Provider that allows getting more information about a UE client by communicating with a LiveLinkHub MessageBus Source.
- L74 _public function_ `template <typename MessageType> TSharedRef<TGameThreadMessageHandler<MessageType, FLiveLinkHubProvider>> MakeHandler(typename TGameThreadMessageHandler<MessageType, FLiveLinkHubProvider>::FuncType Func)` — Create a message bus handler that will dispatch messages on the game thread. This is useful to receive some messages on AnyThread and delegate others on the game thread (ie. for methods that will trigger UI updates which need to happen on game thread. )
- L79 _public prototype_ `FLiveLinkHubProvider(const TSharedRef<ILiveLinkHubSessionManager>& InSessionManager, const FString& ProviderName);`
- L84 _public prototype_ `virtual bool ShouldTransmitToSubject_AnyThread(FName SubjectName, FMessageAddress Address) const override;`
- L85 _public prototype_ `virtual TOptional<FLiveLinkHubUEClientInfo> GetClientInfo(FLiveLinkHubClientId InClient) const override;`
- L86 _public prototype_ `virtual void OnMessageBusNotification(const FMessageBusNotification& Notification) override;`
- L92 _public prototype_ `void AddRestoredClient(FLiveLinkHubUEClientInfo& InOutRestoredClientInfo);` — Restore a client, calling this will modify the client ID if it matches an existing connection.
- L95 _public function_ `const TMap<FLiveLinkHubClientId, FLiveLinkHubUEClientInfo>& GetClientsMap() const` — Retrieve the existing client map.
- L101 _public prototype_ `void UpdateTimecodeSettings(const FLiveLinkHubTimecodeSettings& InSettings, const FLiveLinkHubClientId& ClientId = FLiveLinkHubClientId{});` — Timecode settings that should be shared to connected editors. @Note If ClientId is not provided or invalid, the message will be broadcast to all connected clients.
- L107 _public prototype_ `void ResetTimecodeSettings(const FLiveLinkHubClientId& ClientId = FLiveLinkHubClientId{});` — Reset timecode settings for all connected clients. @Note If ClientId is not provided or invalid, the message will be broadcast to all connected clients.
- L110 _public prototype_ `void UpdateCustomTimeStepSettings(const FLiveLinkHubCustomTimeStepSettings& InSettings, const FLiveLinkHubClientId& ClientId = FLiveLinkHubClientId{});` — Frame Lock settings that should be shared to connected editors.
- L116 _public prototype_ `void ResetCustomTimeStepSettings(const FLiveLinkHubClientId& ClientId = FLiveLinkHubClientId{});` — Reset Frame Lock settings on connected editors. @Note If ClientId is not provided or invalid, the message will be broadcast to all connected clients.
- L122 _public prototype_ `void UpdateSourceEvaluationMode(ELiveLinkSourceMode Mode, const FLiveLinkHubClientId& ClientId = FLiveLinkHubClientId{});` — Push the hub's preferred evaluation mode to connected Editor clients, overwriting their hub source's local Mode. @Note If ClientId is not provided or invalid, the message will be broadcast to all connected clients.
- L125 _public prototype_ `void ConnectToAllDiscoveredClients();` — Connect to all instances in the address book that are compatible with the host's topology mode.
- L130 _public prototype_ `void DisconnectAll();` — Send a disconnect message to all connected clients.
- L135 _public prototype_ `void DisconnectClient(const FLiveLinkHubClientId& ClientId);` — Send a disconnect message to a single client.
- L139 _private prototype_ `void HandleHubConnectMessage(const FLiveLinkHubConnectMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handle a connection message resulting from a livelink hub message bus source connecting to this provider.
- L142 _private prototype_ `void HandleClientInfoMessage(const FLiveLinkClientInfoMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handle a client info message being received. Happens when new information about a client is received (ie. Client has changed map)
- L145 _private prototype_ `void HandleHubDisconnectMessage(const FLiveLinkHubDisconnectMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handle a client (UE or Hub) sending a disconnect request.
- L148 _private prototype_ `void SendTimecodeSettings(const FLiveLinkHubTimecodeSettings& InSettings, const FLiveLinkHubClientId& ClientId);` — Send timecode settings to connected UE Clients.
- L151 _private prototype_ `void SendCustomTimeStepSettings(const FLiveLinkHubCustomTimeStepSettings& InSettings, const FLiveLinkHubClientId& ClientId);` — Send CustomTimeStep settings to connected UE Clients.
- L154 _private prototype_ `void SendSourceEvaluationMode(ELiveLinkSourceMode Mode, const FLiveLinkHubClientId& ClientId);` — Send a source evaluation mode override to connected UE Clients.
- L158 _private function_ `template<typename MessageType> void SendControlMessageToEnabledClients(MessageType* Message, EMessageFlags Flags = EMessageFlags::None)` — Send a message to clients that are connected and enabled through the hub clients list.
- L176 _private prototype_ `bool ShouldTransmitToClient_AnyThread(const FLiveLinkHubClientId& ClientId, FLiveLinkSubjectName SubjectName = FLiveLinkSubjectName{}) const;` — Whether a message should be transmitted to a particular client. You can specify a SubjectName if you want to know if the session allows transmitting to that subject as well.
- L178 _private prototype_ `void CloseConnections(const TArray<FMessageAddress>& ClosedAddresses);`
- L181 _private prototype_ `void ValidateHubConnections();` — Validate connections and entries in the address book.
- L187 _private prototype_ `FLiveLinkHubClientId AddressToClientId(const FMessageAddress& Address) const;` — Get the client id that corresponds to this address from our cache. May return an invalid ID if the address is not in the cache (ie. If client is disconnecting))
- L190 _private prototype_ `void DisconnectClient(const FLiveLinkHubAddressBookEntry& EntryToDisconnect);` — Disconnect client based on its entry in the address book.
- L193 _private prototype_ `void HandleBeaconMessage(const FLiveLinkHubBeaconMessage& Message, const TSharedRef<class IMessageContext, ESPMode::ThreadSafe>& Context);` — Handle beacon message to add this entry to our discovered clients. Beacons are sent after a pong message with the discovery request annotation is sent.
- L196 _private prototype_ `bool ShouldAutoConnectTo(const FString& RemoteHostname, const FString& IP = FString(), const FString& ProjectName = FString()) const;` — Returns whether we should automatically connect to this client based on our settings.
- L202 _private prototype_ `FLiveLinkHubClientId UpdateAddressBookEntry(const FMessageAddress& ControlEndpointAddress, int32 DiscoveryProtocolVersion, ELiveLinkTopologyMode TopologyMode = ELiveLinkTopologyMode::UnrealClient, const FString& Hostname = FString(), const FString& ProjectName = FString(), const FString& LevelName = FString());` — Update (or creates if needed) an entry for this address. @return the client ID.
- L205 _private prototype_ `FLiveLinkHubDiscoveryMessage* MakeLiveLinkHubDiscoveryMessage() const;` — Utility method that constructs a discovery message.
- L208 _private prototype_ `void OnFiltersModified();` — Invoked when the user modifies the auto-connect filtering options.
- L214 _private prototype_ `void ConnectToClients(const TArray<FLiveLinkHubClientId>& DiscoveredClientIds);` — Connect to a set of clients. @Note The clients must have been discovered before invoking this for the connection message to be sent.
- L218 _protected prototype_ `virtual void OnConnectionsClosed(const TArray<FMessageAddress>& ClosedAddresses) override;`
- L219 _protected prototype_ `virtual TArray<FLiveLinkHubClientId> GetSessionClients() const override;`
- L220 _protected prototype_ `virtual TMap<FName, FString> GetAnnotations() const override;`
- L221 _protected prototype_ `virtual TArray<FLiveLinkHubClientId> GetDiscoveredClients() const override;`
- L222 _protected prototype_ `virtual TOptional<FLiveLinkHubDiscoveredClientInfo> GetDiscoveredClientInfo(FLiveLinkHubClientId InClientId) const override;`
- L223 _protected prototype_ `virtual FText GetClientDisplayName(FLiveLinkHubClientId InAddress) const override;`
- L224 _protected function_ `virtual FOnClientEvent& OnClientEvent() override`
- L228 _protected prototype_ `virtual FText GetClientStatus(FLiveLinkHubClientId Client) const override;`
- L229 _protected prototype_ `virtual bool IsClientEnabled(FLiveLinkHubClientId Client) const override;`
- L230 _protected prototype_ `virtual bool IsClientConnected(FLiveLinkHubClientId Client) const override;`
- L231 _protected prototype_ `virtual void ConnectTo(FLiveLinkHubClientId Client) override;`
- L232 _protected prototype_ `virtual void SetClientEnabled(FLiveLinkHubClientId Client, bool bInEnable) override;`
- L233 _protected prototype_ `virtual bool IsSubjectEnabled(FLiveLinkHubClientId Client, FName SubjectName) const override;`
- L234 _protected prototype_ `virtual void SetSubjectEnabled(FLiveLinkHubClientId Client, FName SubjectName, bool bInEnable) override;`
- L235 _protected prototype_ `virtual void RequestAuxiliaryChannel(FLiveLinkHubClientId InClientId, FMessageEndpoint& InAuxEndpoint, UScriptStruct* InRequestTypeInfo, FLiveLinkHubAuxChannelRequestMessage& InRequest) override;`
- L241 _private member_ `TArray<FLiveLinkHubAddressBookEntry> AddressBook;` — Holds the info and state of all clients have been discovered.
- L243 _private member_ `FTimerHandle ValidateConnectionsTimer;` — Handle to the timer responsible for validating the livelinkprovider's connections.
- L245 _private member_ `TMap<FLiveLinkHubClientId, FLiveLinkHubUEClientInfo> ClientsMap;` — List of information we have on clients we have discovered.
- L247 _private member_ `FOnClientEvent OnClientEventDelegate;` — Delegate called when the provider receives a client change.
- L249 _private member_ `TMap<FName, FString> Annotations;` — Annotations sent with every message from this provider. In our case it's use to disambiguate a livelink hub provider from other livelink providers.
- L251 _private member_ `TWeakPtr<ILiveLinkHubSessionManager> SessionManager;` — LiveLinkHub session manager.
- L253 _private member_ `TMap<FMessageAddress, FLiveLinkHubClientId> AddressToIdCache;` — Cache used to retrieve the client id from a message bus address.
- L255 _private member_ `TOptional<FLiveLinkHubClientId> ClientBeingDisconnected;` — Keeps track of a client being disconnected to avoid sending back a message to disconnect it.
- L257 _private member_ `mutable FTransactionallySafeRWLock ClientsMapLock;` — Lock used to access the clients map from different threads.
- L259 _private member_ `mutable FTransactionallySafeRWLock AddressBookLock;` — Lock used to access the AddressBook from different threads.

#### Free symbols / members of external scopes

- L165 _function_ `Algo::TransformIf(AddressBook, ValidClientAddresses, [this](const FLiveLinkHubAddressBookEntry& Entry) { return Entry.bConnected && ShouldTransmitToClient_AnyThread(Entry.ClientId); }, [](const FLiveLinkHubAddressBookEntry& Entry) { return Entry.ControlEndpoint; });` (scope `FLiveLinkHubProvider::SendControlMessageToEnabledClients`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Clients/LiveLinkHubUEClientInfo.h` (Private)


#### struct `FLiveLinkHubUEClientInfo`  
`struct FLiveLinkHubUEClientInfo`  
_L13-84_
- reflection: `USTRUCT()`
- desc: Wrapper around FLiveLinkClientInfoMessage that adds additional info. Used mainly to display information about a client in the UI.
- L17 _public prototype_ `FLiveLinkHubUEClientInfo() = default;`
- L19 _public function_ `explicit FLiveLinkHubUEClientInfo(const FLiveLinkClientInfoMessage& InClientInfo, FLiveLinkHubClientId InClientId = FLiveLinkHubClientId::NewId()) : Id(InClientId) , LongName(InClientInfo.LongName) , Status(InClientInfo.Status) , IPAddress(TEXT("192.168.0.1 (Placeholder)")) , Hostname(InClientInfo.Hostname) , ProjectName(InClientInfo.ProjectName) , CurrentLevel(InClientInfo.CurrentLevel) , LiveLinkInstanceName(InClientInfo.LiveLinkInstanceName) , TopologyMode(InClientInfo.TopologyMode)`
- L32 _public function_ `void UpdateFromInfoMessage(const FLiveLinkClientInfoMessage& InClientInfo)`
- L44 _public member_ `FLiveLinkHubClientId Id;` — `UPROPERTY()` — Identifier for this client.
- L48 _public member_ `FString LongName;` — `UPROPERTY(VisibleAnywhere, Category = "Client")` — Full name used to identify this client. (ie.UEFN_sessionID_LDN_WSYS_9999)
- L52 _public member_ `ELiveLinkClientStatus Status = ELiveLinkClientStatus::Disconnected;` — `UPROPERTY(transient)` — Status of the client, ie. is it actively doing a take record at the moment?
- L55 _public member_ `FString IPAddress;` — `UPROPERTY(VisibleAnywhere, Category = "Client", meta = (DisplayName = "IP Address"))`
- L59 _public member_ `FString Hostname;` — `UPROPERTY(VisibleAnywhere, Category = "Client")` — Name of the host of the UE client
- L63 _public member_ `FString ProjectName;` — `UPROPERTY(VisibleAnywhere, Category = "Client")` — Name of the current project.
- L67 _public member_ `FString CurrentLevel;` — `UPROPERTY(VisibleAnywhere, Category = "Client")` — Name of the current level opened.
- L71 _public member_ `FString LiveLinkInstanceName;` — `UPROPERTY()` — If this is representing a LiveLinkHub instance in Hub mode, this holds the LiveLink provider name, otherwise it's empty.
- L75 _public member_ `ELiveLinkTopologyMode TopologyMode = ELiveLinkTopologyMode::UnrealClient;` — `UPROPERTY()` — Whether the client is a hub or an unreal instance.
- L79 _public member_ `TSet<FName> DisabledSubjects;` — `UPROPERTY()` — Subjects that should not be transmitted to this client.
- L83 _public member_ `bool bEnabled = true;` — `UPROPERTY()` — Whether this client should receive messages.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Clients/SLiveLinkHubClientFilters.h` (Private)


#### class `SLiveLinkHubClientFilters`  
`class SLiveLinkHubClientFilters : public SCompoundWidget`  
_L11-66_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkHubClientFilters)`
- L15 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L26 _public function_ `TSharedRef<SWidget> CreatePropertyEditor()` — Create a property editor that displays the filters taken from ULiveLinkHubUserSettings.
- L49 _public function_ `bool ShouldDisplayProperty(const FPropertyAndParent& InPropertyAndParent) const` — Hides properties that aren't in the filters category.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Clients/SLiveLinkHubClientsView.h` (Private)


#### struct `FClientTreeViewItem`  
`struct FClientTreeViewItem`  
_L95-153_
- desc: Tree view item that represents either a client or a livelink subject.
- L97 _public function_ `FClientTreeViewItem(FLiveLinkHubClientId InClientId, TSharedRef<ILiveLinkHubClientsModel> InClientsModel) : ClientId(MoveTemp(InClientId)) , ClientsModel(MoveTemp(InClientsModel))`
- L103 _public prototype_ `virtual ~FClientTreeViewItem() = default;`
- L106 _public function_ `virtual const FLiveLinkSubjectKey& GetSubjectKey() const` — Get the subject key for this tree item (Invalid key for client rows).
- L116 _public prototype_ `virtual bool IsEnabled() const = 0;` — For clients, returns if it should receive any livelink data from the hub (except for heartbeat messages). For subjects, returns if the hub transmit this subject's data to the client.
- L119 _public prototype_ `virtual bool IsReadOnly() const = 0;` — Whether the row should be in read only (ie. if the source is disconnected)
- L125 _public prototype_ `virtual void SetEnabled(bool bInEnabled) = 0;` — Set whether this item should be transmitted to the client. @See IsEnabled()
- L128 _public prototype_ `virtual FText GetStatusText() const = 0;` — Get status text for the row.
- L131 _public function_ `void GetFilterText(TArray<FString>& OutStrings) const` — Transform the client item ptr to a string for filtering purpose.
- L137 _public function_ `virtual FText GetLevelName() const` — Get level name for this client.
- L144 _public member_ `TArray<TSharedPtr<FClientTreeViewItem>> Children;` — This item's children, in the case of client rows, these represent the livelink subjects.
- L146 _public member_ `FText Name;` — Name of the tree item (client or subject name).
- L148 _public member_ `FLiveLinkHubClientId ClientId;` — Identifier of the unreal client for this item.
- L150 _public member_ `TWeakPtr<ILiveLinkHubClientsModel> ClientsModel;` — ClientsModel used to retrieve information about clients/subjects.
- L152 _public member_ `bool bFilteredOut = false;` — Whether this client has been filtered out.

#### struct `FClientTreeViewClientItem`  
`struct FClientTreeViewClientItem : public FClientTreeViewItem`  
_L156-216_
- inherits: `FClientTreeViewItem`
- desc: Holds a client row's data.
- L158 _public function_ `FClientTreeViewClientItem(FLiveLinkHubClientId InClientId, TSharedRef<ILiveLinkHubClientsModel> InClientsModel) : FClientTreeViewItem(MoveTemp(InClientId), MoveTemp(InClientsModel))`
- L167 _public function_ `virtual bool IsEnabled() const override`
- L176 _public function_ `virtual bool IsReadOnly() const override`
- L186 _public function_ `virtual void SetEnabled(bool bInEnabled) override`
- L194 _public function_ `virtual FText GetStatusText() const override`
- L204 _public function_ `virtual FText GetLevelName() const override`

#### struct `FClientTreeViewSubjectItem`  
`struct FClientTreeViewSubjectItem : public FClientTreeViewItem`  
_L219-272_
- inherits: `FClientTreeViewItem`
- desc: Holds a subject row's data.
- L221 _public function_ `FClientTreeViewSubjectItem(FLiveLinkHubClientId InClientId, FLiveLinkSubjectKey InLiveLinkSubjectKey, TSharedRef<ILiveLinkHubClientsModel> InClientsModel) : FClientTreeViewItem(MoveTemp(InClientId), MoveTemp(InClientsModel)) , LiveLinkSubjectKey(MoveTemp(InLiveLinkSubjectKey))`
- L230 _public function_ `virtual const FLiveLinkSubjectKey& GetSubjectKey() const override`
- L235 _public function_ `virtual bool IsEnabled() const override`
- L245 _public function_ `virtual bool IsReadOnly() const override`
- L255 _public function_ `virtual void SetEnabled(bool bInEnabled) override`
- L264 _public function_ `virtual FText GetStatusText() const override`
- L271 _public member_ `FLiveLinkSubjectKey LiveLinkSubjectKey;` — Unique key for this item's subject.

#### class `SLiveLinkHubDiscoveredClientRow`  
`class SLiveLinkHubDiscoveredClientRow : public SMultiColumnTableRow<TSharedPtr<FLiveLinkHubClientId>>`  
_L276-339_
- inherits: `SMultiColumnTableRow<TSharedPtr<FLiveLinkHubClientId>>`
- desc: Holds a discovered client row's data.
- L279 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkHubDiscoveredClientRow)`
- L281 _public function_ `SLATE_ARGUMENT(TSharedPtr<FLiveLinkHubClientId>, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedRef<ILiveLinkHubClientsModel> InClientsModel)` — The list item for this row
- L304 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override`
- L338 _private member_ `FLiveLinkHubDiscoveredClientInfo DiscoveredClientInfo;` — Information about this client.

#### class `SLiveLinkHubClientsRow`  
`class SLiveLinkHubClientsRow : public SMultiColumnTableRow<TSharedPtr<FClientTreeViewItem>>`  
_L342-437_
- inherits: `SMultiColumnTableRow<TSharedPtr<FClientTreeViewItem>>`
- desc: Holds a client row's data.
- L345 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkHubClientsRow)`
- L347 _public function_ `SLATE_ARGUMENT(TSharedPtr<FClientTreeViewItem>, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)` — The list item for this row
- L363 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override`
- L406 _private function_ `bool IsCheckboxEnabled() const` — Return whether the enable checkbox should be clickable.
- L412 _private function_ `ECheckBoxState IsItemEnabled() const` — Return whether the enabled checkbox is checked.
- L418 _private function_ `void OnEnabledCheckboxChange(ECheckBoxState State) const` — Handler called when the enabled checkbox is clicked.
- L424 _private function_ `FText GetStatusText() const` — Get the status text from the tree item.
- L429 _private function_ `FText GetLevelName() const`
- L436 _private member_ `TSharedPtr<FClientTreeViewItem> TreeItem;` — The data represented by this row (Either an unreal client or a livelink subject).

#### class `SLiveLinkHubClientsView`  
`class SLiveLinkHubClientsView : public SCompoundWidget`  
_L442-1148_
- inherits: `SCompoundWidget`
- desc: Provides the UI that displays the UE clients connected to the hub.
- L445 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkHubClientsView)`
- L451 _public typedef_ `using FClientTreeItemPtr = TSharedPtr<FClientTreeViewItem>;`
- L454 _public function_ `void Construct(const FArguments& InArgs, TSharedRef<ILiveLinkHubClientsModel> InClientsModel)`
- L558 _public function_ `virtual ~SLiveLinkHubClientsView() override`
- L584 _public function_ `void Reinitialize()` — Refresh the data and widgets.
- L591 _public function_ `TArray<FLiveLinkHubClientId> GetSelectedClients() const` — Get the currently selected clients.
- L605 _private function_ `TSharedRef<SWidget> OnGetDiscoveredClientsContent()` — Populates a list widget with the discovered clients.
- L642 _private function_ `TSharedRef<ITableRow> OnGenerateDiscoveredClientsRow(TSharedPtr<FLiveLinkHubClientId> Item, const TSharedRef<STableViewBase>& OwnerTable)` — Handler used to generate a widget for a given client row.
- L649 _private function_ `TSharedRef<ITableRow> OnGenerateClientRow(FClientTreeItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable)` — Handler used to generate a widget for a given client row.
- L656 _private function_ `TSharedPtr<SWidget> OnContextMenuOpening() const` — Handler used to create the context menu widget.
- L685 _private function_ `void OnSelectionChanged(FClientTreeItemPtr InItem, const ESelectInfo::Type InSelectInfoType) const` — Handler called when selection changes in the list view.
- L694 _private function_ `void OnGetChildren(FClientTreeItemPtr Item, TArray<FClientTreeItemPtr>& OutChildren)` — Handler called to fetch a tree row's children.
- L700 _private function_ `FReply OnKeyDownHandler(const FGeometry&, const FKeyEvent& InKeyEvent) const` — Method to handle deleting clients when the delete key is pressed.
- L715 _private function_ `void RemoveSelectedClient() const` — Remove the selected client from the list. This will stop all livelink messages from being transmitted to it.
- L724 _private function_ `void RemoveAllClients() const` — Remove all clients from the list. This will stop all livelink messages from being transmitted to them.
- L739 _private function_ `void OnDiscoveredClientPicked(TSharedPtr<FLiveLinkHubClientId> InItem, const ESelectInfo::Type InSelectInfoType)` — Handler called when a client is picked in the Add Client menu.
- L749 _private function_ `void OnClientEvent(FLiveLinkHubClientId ClientId, ILiveLinkHubClientsModel::EClientEventType EventType)` — Handler called when the client list has changed.
- L784 _private function_ `void OnClientAddedToSession(FLiveLinkHubClientId ClientId)` — Handler called when a client is added to a session.
- L804 _private function_ `void OnClientRemovedFromSession(FLiveLinkHubClientId ClientId)` — Handler called when a client is removed from a session.
- L825 _private function_ `void OnActiveSessionChanged(const TSharedRef<ILiveLinkHubSession>& ActiveSession)` — Refreshes the data when the current session changes.
- L831 _private function_ `void InitializeClientItem(FClientTreeViewClientItem& ClientItem)` — Populate a client item row with its data and children.
- L848 _private function_ `void OnSubjectAdded_AnyThread(FLiveLinkSubjectKey SubjectKey)` — AnyThread handler for the SubjectAdded delegate, dispatches handling on the game thread to avoid asserts in Slate.
- L861 _private function_ `void OnSubjectAdded(const FLiveLinkSubjectKey& SubjectKey)` — Handles updating the tree view when a subject is added.
- L881 _private function_ `void OnSubjectRemoved_AnyThread(FLiveLinkSubjectKey SubjectKey)` — AnyThread handler for the SubjectRemoved delegate, dispatches handling on the game thread to avoid asserts in Slate.
- L894 _private function_ `void OnSubjectRemoved(const FLiveLinkSubjectKey& SubjectKey)` — Handles updating the tree view when a subject is removed.
- L909 _private function_ `void PopulateClients()` — Build the client list.
- L924 _private function_ `TSharedRef<SWidget> GetAutoConnectMenuContent()` — Generate a dropdown to select an autoconnect modes.
- L982 _private function_ `void SetAutoConnectMode(ELiveLinkHubAutoConnectMode AutoConnectMode)` — Configure UE client AutoConnect mode.
- L988 _private function_ `TSharedRef<SWidget> CreateAutoConnectModeSwitcher()` — Create the widget for switching autoconnect mode.
- L1015 _private function_ `void OpenFiltersMenu()` — Open a window that hosts the filters menu.
- L1030 _private function_ `void HandleSaveCurrentPreset()` — Saves the current preset to disk.
- L1037 _private function_ `void HandleSavePreset()` — Open a window that hosts the filters menu.
- L1111 _private function_ `void CreateLoadPresetSubMenu(FMenuBuilder& MenuBuilder)`
- L1119 _private function_ `void CreateDeletePresetSubMenu(FMenuBuilder& MenuBuilder)`
- L1129 _private member_ `FOnClientSelected OnClientSelectedDelegate;` — Delegate called when a client is selected.
- L1131 _private member_ `FOnDiscoveredClientPicked OnDiscoveredClientPickedDelegate;` — Delegate called when a client is selected.
- L1133 _private member_ `FOnRemoveClientFromSession OnRemoveClientFromSessionDelegate;` — Delegate called when a client is deleted.
- L1135 _private member_ `TSharedPtr<STreeView<FClientTreeItemPtr>> TreeView;` — TreeView widget that displays the clients.
- L1137 _private member_ `TArray<FClientTreeItemPtr> Clients;` — List of clients in the current session.
- L1139 _private member_ `TArray<TSharedPtr<FLiveLinkHubClientId>> DiscoveredClients;` — Clients discovered by the hub.
- L1141 _private member_ `TSharedPtr<ILiveLinkHubClientsModel> ClientsModel;` — Model that holds the client data we are displaying.
- L1143 _private member_ `TArray<FClientTreeItemPtr> FilteredList;` — Filtered list resulting from applying the text filter.
- L1145 _private member_ `TSharedPtr<SLiveLinkFilterSearchBox<FClientTreeItemPtr>> FilterSearchBox;` — Filter search box responsible for keeping the filtered list up to date.
- L1147 _private member_ `TSharedPtr<SWindow> FiltersMenuWindow;` — Hosts the filter menu that allows better control over which sources should auto-connect.

#### Free symbols / members of external scopes

- L44 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkHub.ClientsView"`
- L46 _delegate_ `DECLARE_DELEGATE_OneParam(FOnClientSelected, FLiveLinkHubClientId );`
- L46 _prototype_ `DECLARE_DELEGATE_OneParam(FOnClientSelected, FLiveLinkHubClientId );`
- L47 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDiscoveredClientPicked, FLiveLinkHubClientId );`
- L47 _prototype_ `DECLARE_DELEGATE_OneParam(FOnDiscoveredClientPicked, FLiveLinkHubClientId );`
- L48 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRemoveClientFromSession, FLiveLinkHubClientId );`
- L48 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRemoveClientFromSession, FLiveLinkHubClientId );`
- L51 _namespace_ `namespace ClientsView`
- L53 _variable_ `static const FName NameColumnId = "Na` (scope `ClientsView`)
- L54 _variable_ `static const FName StatusColumnId = "St` (scope `ClientsView`)
- L55 _variable_ `static const FName EnabledIconColumnId = "En` (scope `ClientsView`)
- L56 _variable_ `static const FName DisabledIconName = "Li` (scope `ClientsView`)
- L57 _variable_ `static const FName GlobalIconName = "Li` (scope `ClientsView`)
- L58 _variable_ `static const FName LocalOnlyIconName = "Li` (scope `ClientsView`)
- L60 _variable_ `static const FName TopologyModeColumnId = "Mo` (scope `ClientsView`)
- L61 _variable_ `static const FName HostnameColumnId = "Ho` (scope `ClientsView`)
- L62 _variable_ `static const FName IPColumnId = "IP` (scope `ClientsView`)
- L63 _variable_ `static const FName ProjectNameColumnId = "Pr` (scope `ClientsView`)
- L64 _variable_ `static const FName LevelNameColumnId = "Le` (scope `ClientsView`)
- L67 _namespace_ `namespace LiveLinkHubClientsViewUtils`
- L69 _function_ `static FSlateIcon GetAutoConnectIcon(ELiveLinkHubAutoConnectMode Mode)` (scope `LiveLinkHubClientsViewUtils`)
- L314 _function_ `.Text_Lambda([this]() { return FText::FromString(DiscoveredClientInfo.Hostname); });` (scope `SLiveLinkHubDiscoveredClientRow::GenerateWidgetForColumn`)
- L319 _function_ `.Text_Lambda([this]() { return FText::FromString(DiscoveredClientInfo.IP); });` (scope `SLiveLinkHubDiscoveredClientRow::GenerateWidgetForColumn`)
- L324 _function_ `.Text_Lambda([this]() { return FText::FromString(DiscoveredClientInfo.ProjectName); });` (scope `SLiveLinkHubDiscoveredClientRow::GenerateWidgetForColumn`)
- L329 _function_ `.Text_Lambda([this]() { return FText::FromString(DiscoveredClientInfo.LevelName); });` (scope `SLiveLinkHubDiscoveredClientRow::GenerateWidgetForColumn`)
- L487 _function_ `` (scope `SLiveLinkHubClientsView::Construct`)
- L597 _function_ `Algo::TransformIf(SelectedClients, ClientIds, [](const FClientTreeItemPtr& ClientPtr) { return ClientPtr.IsValid(); }, [](const FClientTreeItemPtr& ClientPtr) { return ClientPtr->ClientId; });` (scope `SLiveLinkHubClientsView::GetSelectedClients`)
- L610 _function_ `Algo::Transform(DiscoveredClientList, DiscoveredClients, [](const FLiveLinkHubClientId& Client) { return MakeShared<FLiveLinkHubClientId>(Client); });` (scope `SLiveLinkHubClientsView::OnGetDiscoveredClientsContent`)
- L666 _function_ `FExecuteAction::CreateRaw(this, &SLiveLinkHubClientsView::RemoveSelectedClient), FCanExecuteAction::CreateStatic( [](){ return true; } ) ) );` (scope `SLiveLinkHubClientsView::OnContextMenuOpening`)
- L676 _function_ `FExecuteAction::CreateRaw(this, &SLiveLinkHubClientsView::RemoveAllClients), FCanExecuteAction::CreateStatic([]() { return true; }) ) );` (scope `SLiveLinkHubClientsView::OnContextMenuOpening`)
- L729 _function_ `Algo::TransformIf(Clients, ClientIds, [](FClientTreeItemPtr ClientPtr) { return !!ClientPtr; }, [](FClientTreeItemPtr ClientPtr) { return ClientPtr->ClientId; });` (scope `SLiveLinkHubClientsView::RemoveAllClients`)
- L732 _function_ `` (scope `SLiveLinkHubClientsView::RemoveAllClients`)
- L759 _function_ `int32 ClientIndex = Clients.IndexOfByPredicate([ClientId](const FClientTreeItemPtr& InClient) { return InClient->ClientId == ClientId; });` (scope `SLiveLinkHubClientsView::OnClientEvent`)
- L772 _function_ `` (scope `SLiveLinkHubClientsView::OnClientEvent`)
- L786 _function_ `int32 ClientIndex = DiscoveredClients.IndexOfByPredicate([ClientId](const TSharedPtr<FLiveLinkHubClientId>& InClient) { return *InClient == ClientId; });` (scope `SLiveLinkHubClientsView::OnClientAddedToSession`)
- L792 _function_ `if (!Clients.ContainsByPredicate([ClientId](const FClientTreeItemPtr& Item) { return Item && Item->ClientId == ClientId; }))` (scope `SLiveLinkHubClientsView::OnClientAddedToSession`)
- L806 _function_ `int32 ClientIndex = Clients.IndexOfByPredicate([ClientId](const FClientTreeItemPtr& InClient) { return InClient->ClientId == ClientId; });` (scope `SLiveLinkHubClientsView::OnClientRemovedFromSession`)
- L852 _function_ `` (scope `SLiveLinkHubClientsView::OnSubjectAdded_AnyThread`)
- L869 _function_ `` (scope `SLiveLinkHubClientsView::OnSubjectAdded`)
- L885 _function_ `` (scope `SLiveLinkHubClientsView::OnSubjectRemoved_AnyThread`)
- L898 _function_ `int32 Index = Client->Children.IndexOfByPredicate([SubjectKey](const TSharedPtr<FClientTreeViewItem>& Item) { return Item->GetSubjectKey() == SubjectKey; });` (scope `SLiveLinkHubClientsView::OnSubjectRemoved`)
- L949 _function_ `FExecuteAction::CreateLambda([]() {}), FCanExecuteAction::CreateStatic([]() { return GetDefault<ULiveLinkHubUserSettings>()->GetFilterPresets().Num() > 0; }) );` (scope `SLiveLinkHubClientsView::GetAutoConnectMenuContent`)
- L951 _function_ `` (scope `SLiveLinkHubClientsView::GetAutoConnectMenuContent`)
- L961 _function_ `FExecuteAction::CreateLambda([]() {}), FCanExecuteAction::CreateLambda([]() { return false; }) );` (scope `SLiveLinkHubClientsView::GetAutoConnectMenuContent`)
- L993 _function_ `` (scope `SLiveLinkHubClientsView::CreateAutoConnectModeSwitcher`)
- L1053 _function_ `.GetWidgetToFocusOnActivate(FGetFocusWidget::CreateLambda([&TextBoxWidget]() { return TextBoxWidget; })) .Content() [ SNew(SBox) .MinDesiredWidth(150) [ SNew(SVerticalBox) + SVerticalBox::Slot() .HAlign(HAlign_Center) [ SAssignNew(TextBoxWidget, SEditableTextBox) .Font(FAppStyle::GetFontStyle("PropertyWindow.NormalFont")) .Justification(ETextJustify::Left) .MinDesiredWidth(60.f) .SelectAllTextWhenFocused(true) .OnTextChanged_Lambda([&CurrentText](const FText& NewText) { CurrentText = NewText; }) .HintText(LOCTEXT("PresetNameHint", "Preset Name")) .OnTextCommitted_Lambda([&PresetName, &SaveFilterDialog, &bConfirmedPresetName](const FText& NewText, ETextCommit::Type InTextCommit) { PresetName = NewText.ToString();` (scope `SLiveLinkHubClientsView::HandleSavePreset`)
- L1068 _function_ `.OnTextChanged_Lambda([&CurrentText](const FText& NewText) { CurrentText = NewText; }) .HintText(LOCTEXT("PresetNameHint", "Preset Name")) .OnTextCommitted_Lambda([&PresetName, &SaveFilterDialog, &bConfirmedPresetName](const FText& NewText, ETextCommit::Type InTextCommit) { PresetName = NewText.ToString();` (scope `SLiveLinkHubClientsView::HandleSavePreset`)
- L1071 _function_ `` (scope `SLiveLinkHubClientsView::HandleSavePreset`)
- L1095 _function_ `.SetIsEnabled(TAttribute<bool>::CreateLambda([&CurrentText]() { return !CurrentText.IsEmpty(); })), SCustomDialog::FButton(LOCTEXT("Cancel", "Cancel"), FSimpleDelegate(), SCustomDialog::EButtonRole::Cancel) }) .HAlignButtonBox(HAlign_Center);` (scope `SLiveLinkHubClientsView::HandleSavePreset`)
- L1115 _function_ `MenuBuilder.AddMenuEntry(FText::FromString(Preset.PresetName), FText::GetEmpty(), FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Load"), FExecuteAction::CreateLambda([PresetName = Preset.PresetName]() { GetMutableDefault<ULiveLinkHubUserSettings>()->LoadFilterPreset(PresetN` (scope `SLiveLinkHubClientsView::CreateLoadPresetSubMenu`)
- L1123 _function_ `MenuBuilder.AddMenuEntry(FText::FromString(Preset.PresetName), FText::GetEmpty(), FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Load"), FExecuteAction::CreateLambda([PresetName = Preset.PresetName]() { GetMutableDefault<ULiveLinkHubUserSettings>()->DeleteFilterPreset(PresetN` (scope `SLiveLinkHubClientsView::CreateDeletePresetSubMenu`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Config/LiveLinkHubFileUtilities.h` (Private)


#### struct `UE::LiveLinkHub::FileUtilities::Private::FFilenameTemplateData`  
`struct FFilenameTemplateData`  
_L38-46_
- desc: Evaluated results from a template file string.
- L41 _public member_ `FString FullPath;` — Full original path with evaluated tokens.
- L43 _public member_ `FString FolderPath;` — The evaluated folder(s) without the first forward slash or filename.
- L45 _public member_ `FString FileName;` — The evaluated filename.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace LiveLinkHub` (scope `UE`)
- L11 _namespace_ `namespace FileUtilities` (scope `UE::LiveLinkHub`)
- L11 _namespace_ `namespace Private` (scope `UE::LiveLinkHub::FileUtilities`)
- L14 _variable_ `const FString JsonVersionKey = TEXT("liv` (scope `UE::LiveLinkHub::FileUtilities::Private`) — A key which must be present in json configs and mapped to the saved json version.
- L16 _variable_ `constexpr int32 LiveLinkHubVersion = 1;` (scope `UE::LiveLinkHub::FileUtilities::Private`) — The json version we support.
- L19 _variable_ `const FString ConfigExtension = TEXT("jso` (scope `UE::LiveLinkHub::FileUtilities::Private`) — The extension of the config file.
- L21 _variable_ `const FString ConfigDefaultFileName = TEXT("Liv` (scope `UE::LiveLinkHub::FileUtilities::Private`) — The default name of the config file.
- L23 _variable_ `const FString ConfigDescription = TEXT("Liv` (scope `UE::LiveLinkHub::FileUtilities::Private`) — The description of the config file.
- L26 _prototype_ `void SaveConfig(const ULiveLinkHubSessionData* InConfigData, const FString& InFilePath);` (scope `UE::LiveLinkHub::FileUtilities::Private`) — Save config data to disk.
- L29 _prototype_ `ULiveLinkHubSessionData* LoadConfig(const FString& InFilePath);` (scope `UE::LiveLinkHub::FileUtilities::Private`) — Load config data from disk.
- L32 _prototype_ `TSharedPtr<FJsonObject> ToJson(const ULiveLinkHubSessionData* InConfigData);` (scope `UE::LiveLinkHub::FileUtilities::Private`) — Convert config data to json.
- L35 _prototype_ `ULiveLinkHubSessionData* FromJson(const TSharedPtr<FJsonObject>& InJsonObject);` (scope `UE::LiveLinkHub::FileUtilities::Private`) — Convert config data from json.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Config/LiveLinkHubTemplateTokens.h` (Private)


#### class `ULiveLinkHubNamingTokens`  
`class ULiveLinkHubNamingTokens final: public UNamingTokens`  
_L10-36_
- reflection: `UCLASS(NotBlueprintable)`
- inherits: `UNamingTokens`
- L15 _public prototype_ `ULiveLinkHubNamingTokens();`
- L19 _protected prototype_ `virtual void OnCreateDefaultTokens(TArray<FNamingTokenData>& Tokens) override;`
- L20 _protected prototype_ `virtual void OnPreEvaluate_Implementation(const FNamingTokensEvaluationData& InEvaluationData) override;`
- L21 _protected prototype_ `virtual void OnPostEvaluate_Implementation() override;`
- L26 _private member_ `FString ConfigName;` — The loaded config name.
- L29 _private member_ `FString SessionName;` — The current session.
- L32 _private member_ `FString SlateName;` — Session slate name
- L35 _private member_ `int32 TakeNumber = 0;` — Session take number.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Data/LiveLinkHubBulkData.h` (Private)


#### class `FLiveLinkHubBulkData`  
`class FLiveLinkHubBulkData`  
_L12-89_
- desc: Bulk data for live link hub, automatically tracking the current offset of the bulk data.
- L39 _public prototype_ `~FLiveLinkHubBulkData();`
- L42 _public prototype_ `void CloseFileReader();` — Close the file reader if it is open.
- L45 _public prototype_ `void UnloadBulkData();` — Unloads the bulk data.
- L49 _public function_ `template<typename T> void ReadBulkDataPrimitive(T& InMemory)` — Read data using sizeof(T).
- L55 _public prototype_ `void ReadBulkData(const int64 InBytesToRead, uint8* InMemory);` — Read bulk data at the current offset of the specified byte size and increment the file offset.
- L58 _public prototype_ `TSharedPtr<FScopedBulkDataMemoryReader> CreateBulkDataMemoryReader(const int64 InBytesToRead);` — Create a scoped memory reader consisting of the bulk data bytes read. Increments file offset.
- L61 _public prototype_ `void ResetBulkDataOffset();` — Reset to the initial offset in the file.
- L64 _public prototype_ `void SetBulkDataOffset(const int64 InNewOffset);` — Manually set the bulk data offset.
- L67 _public function_ `int64 GetBulkDataOffset() const` — Retrieve the current bulk data offset.
- L70 _public prototype_ `void Serialize(FArchive& Ar, UObject* Owner);` — Call the serialize method of the bulk data, should be called when serializing the owning asset.
- L73 _public prototype_ `void WriteBulkData(TArray64<uint8>& Data);` — Write to the bulk data file.
- L80 _private prototype_ `int64 ReadBulkDataImpl(int64 InOffset, int64 InBytesToRead, uint8* InMemory);` — Read bulk data at an offset of the specified byte size. @return The new offset after reading in the bytes.
- L84 _private member_ `TUniquePtr<IAsyncReadFileHandle> RecordingFileReader;` — The file reader open to the bulk data.
- L86 _private member_ `FByteBulkData BulkData;` — The bulk data storage.
- L88 _private member_ `int64 BulkDataOffset = 0;` — The current bulk data offset in the owning file.

#### class `FLiveLinkHubBulkData::FScopedBulkDataMemoryReader`  
`class FScopedBulkDataMemoryReader`  
_L19-37_
- desc: Read a section of bulk data to a memory reader - valid only within this scope - allowing bulk data to be used like a typical FArchive. This differs from FBulkDataReader in that it supports only loading a section of bulk data into memory at a time.
- L22 _public prototype_ `FScopedBulkDataMemoryReader(const int64 InOffset, const int64 InBytesToRead, FLiveLinkHubBulkData* InBulkData);`
- L25 _public function_ `FLargeMemoryReader& GetMemoryReader() const` — Retrieve the memory reader.
- L28 _public function_ `int64 GetBulkDataOffset() const` — Retrieve the bulk data offset after having read the bulk data into memory.
- L32 _private member_ `TUniquePtr<FLargeMemoryReader> MemoryReader;` — The memory reader for reading out memory storage.
- L34 _private member_ `TArray64<uint8> Memory;` — The memory storage for loading the bulk data.
- L36 _private member_ `int64 LocalBulkDataOffset = 0;` — The bulk data offset after reading the data into memory.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/LiveLinkHub.h` (Private)


#### class `ILiveLinkHub`  
`class ILiveLinkHub`  
_L37-46_
- desc: Main interface for the live link hub.
- L40 _public prototype_ `virtual ~ILiveLinkHub() = default;`
- L43 _public prototype_ `virtual bool IsInPlayback() const = 0;` — Whether the hub is currently playing a recording.
- L45 _public prototype_ `virtual bool IsRecording() const = 0;` — Whether the hub is currently recording livelink data.

#### class `FLiveLinkHub`  
`class FLiveLinkHub : public ILiveLinkHub, public FLiveLinkHubApplication`  
_L52-228_
- inherits: `ILiveLinkHub,FLiveLinkHubApplication`
- desc: Implementation of the live link hub. Contains the apps' different components and is responsible for handling communication between them.
- L56 _public prototype_ `static TSharedPtr<FLiveLinkHub> Get();` — Get the livelinkhub instance that's held by LiveLinkHubModule. May return a nullptr when the module is shutting down.
- L61 _public prototype_ `virtual bool IsInPlayback() const override;`
- L62 _public prototype_ `virtual bool IsRecording() const override;`
- L69 _public prototype_ `void Initialize(class FLiveLinkHubTicker& Ticker);` — Initialize LiveLinkHub.
- L70 _public function_ `const FLiveLinkHubInstanceId& GetId() const`
- L72 _public prototype_ `TSharedRef<SWindow> GetRootWindow() const;` — Get the root window that hosts the hub's slate application.
- L74 _public prototype_ `TSharedPtr<FLiveLinkHubProvider> GetLiveLinkProvider() const;` — Get the livelink provider used to rebroadcast livelink data to connected UE clients.
- L76 _public prototype_ `TSharedPtr<FLiveLinkHubRecordingController> GetRecordingController() const;` — Get the controller that manages recording livelink data.
- L78 _public prototype_ `TSharedPtr<FLiveLinkHubRecordingListController> GetRecordingListController() const;` — Get the recording list controller, that handles displaying livelink recording assets.
- L80 _public prototype_ `TSharedPtr<FLiveLinkHubPlaybackController> GetPlaybackController() const;` — Get the controller that manages playing back livelink data.
- L82 _public prototype_ `TSharedPtr<FLiveLinkHubClientsController> GetClientsController() const;` — Get the controller that manages clients.
- L84 _public function_ `TSharedPtr<FUICommandList> GetCommandList() const` — Get the live link hub command list.
- L86 _public prototype_ `TSharedPtr<ILiveLinkHubSessionManager> GetSessionManager() const;` — Get the session manager.
- L88 _public prototype_ `TSharedPtr<FLiveLinkHubAutosaveHandler> GetAutosaveHandler() const;` — Get the autosave handler.
- L94 _public prototype_ `ELiveLinkTopologyMode GetTopologyMode() const;` — Get whether the hub should act as a hub or as a spoke. Hubs can receive data from spokes, and transmit it to UE clients. Spokes can only transmit data to Hubs.
- L96 _public prototype_ `void SetTopologyMode(ELiveLinkTopologyMode Mode);` — Set the topology mode for this instance.
- L98 _public prototype_ `void ToggleTopologyMode();` — Toggle the topology mode between Hub and Spoke.
- L100 _public prototype_ `bool CanSetTopologyMode() const;` — Returns whether the topology mode can change for this instance.
- L102 _public function_ `FOnTopologyModeChanged& OnTopologyModeChanged()` — Delegate called when the topology mode changed.
- L107 _public prototype_ `void UpgradeAndSaveRecording(ULiveLinkUAssetRecording* InRecording, bool bUpgradeInPlace = false);` — Upgrade a recording and save to a new file or over the existing file.
- L110 _public function_ `FSimpleDelegate& OnFrameReceived()` — Delegate triggered whenever the Live Link Client receives frame data.
- L113 _public prototype_ `virtual void MapToolkitCommands() override;`
- L114 _public prototype_ `virtual void OnClose() override;`
- L118 _private prototype_ `void InitializePostEngineInit();` — Complete the initialization after core engine systems have been initialized.
- L121 _private prototype_ `void OnEnginePreExit();` — When the engine is about to exit.
- L124 _private prototype_ `void OnStaticDataReceived_AnyThread(const FLiveLinkSubjectKey& InSubjectKey, TSubclassOf<ULiveLinkRole> InRole, const FLiveLinkStaticDataStruct& InStaticDataStruct) const;`
- L125 _private prototype_ `void OnFrameDataReceived_AnyThread(const FLiveLinkSubjectKey& InSubjectKey, const FLiveLinkFrameDataStruct& InFrameDataStruct) const;`
- L126 _private prototype_ `void OnSubjectMarkedPendingKill_AnyThread(const FLiveLinkSubjectKey& InSubjectKey) const;`
- L129 _private prototype_ `void OnLiveLinkFrameDataReceived(const FLiveLinkFrameDataStruct&) const;` — Called whenever LiveLinkClient receives data to wake up the LiveLink Ticker if LiveLinkHub.EnableTriggeredTick is enabled.
- L133 _private prototype_ `void RegisterLiveLinkHubSettings();` — Register settings relevant to the livelink hub.
- L135 _private prototype_ `void UnregisterLiveLinkHubSettings();` — Unregister settings relevant to the livelink hub.
- L138 _private prototype_ `void NewConfig();` — Create a new config.
- L141 _private prototype_ `void SaveConfigAs();` — Save an existing config to a new file.
- L144 _private prototype_ `bool CanSaveConfig() const;` — Whether the Save command can be used.
- L147 _private prototype_ `void SaveConfig();` — Save the config to the current file.
- L150 _private prototype_ `void OpenConfig();` — Open an existing config.
- L153 _private prototype_ `bool CanCreateOrOpenConfig() const;` — If a config can be created or loaded.
- L156 _private prototype_ `void OpenLogsFolder();` — Open the folder containing logs for the app.
- L159 _private prototype_ `void OpenAboutMenu();` — Open the help menu.
- L162 _private prototype_ `void OnModularFeatureRegistered(const FName& Type, class IModularFeature* ModularFeature);` — Handles adding application modes that are registered after LLH has finished initialization.
- L165 _private prototype_ `void OnSubjectOutboundNameModified(const FLiveLinkSubjectKey& SubjectKey, const FString& PreviousOutboundName, const FString& NewOutboundName) const;` — Delegate called when a LiveLinkHubSubjectSettings modifies an outbound name. We need to notify connected clients of this change.
- L168 _private prototype_ `void OnPlaybackReadyForUpgrade(bool bUpgradeInPlace);` — Callback when playback is ready because we are performing an upgrade.
- L172 _private member_ `TSharedPtr<FLiveLinkHubClientsController> ClientsController;` — Implements the logic to manage the clients tabs.
- L174 _private member_ `TSharedPtr<FLiveLinkHubRecordingController> RecordingController;` — Implements the logic for triggering recording.
- L176 _private member_ `TSharedPtr<FLiveLinkHubRecordingListController> RecordingListController;` — Implements the logic for displaying the list of recordings.
- L178 _private member_ `TSharedPtr<FLiveLinkHubPlaybackController> PlaybackController;` — Implements the logic for triggering the playback of a livelink recording.
- L180 _private member_ `TSharedPtr<FLiveLinkHubSubjectController> SubjectController;` — Implements the controller responsible for displaying and managing subject data.
- L182 _private member_ `TSharedPtr<FLiveLinkHubWindowController> WindowController;` — Controller responsible for creating and managing the app's slate windows.
- L184 _private member_ `TSharedPtr<ILiveLinkHubSessionManager> SessionManager;` — Object responsible for managing sessions.
- L186 _private member_ `TSharedPtr<FLiveLinkHubClient> LiveLinkHubClient;` — LiveLinkHub's livelink client.
- L188 _private member_ `TSharedPtr<FLiveLinkHubProvider> LiveLinkProvider;` — LiveLinkProvider used to transfer data to connected UE clients.
- L190 _private member_ `TUniquePtr<FConsoleCommandExecutor> CommandExecutor;` — Handles execution of commands.
- L192 _private member_ `TSharedPtr<FLiveLinkHubAutosaveHandler> AutosaveHandler;` — Handles triggering an autosave.
- L194 _private member_ `TPimplPtr<class FLiveLinkHubCrashRecovery> CrashRecoveryHandler;` — Crash recovery handler.
- L196 _private member_ `FString LastConfigPath;` — The last opened config path.
- L200 _private member_ `TOptional<ELiveLinkTopologyMode> OverrideTopologyMode;` — Override topology mode set through the command line. Cannot be changed at runtime.
- L202 _private member_ `FOnTopologyModeChanged TopologyModeChangedDelegate;` — Delegate called when the topology mode changed.
- L204 _private member_ `FSimpleDelegate OnFrameReceivedDelegate;` — Delegate called whenever LL Client receives a frame.
- L206 _private member_ `FDelegateHandle MediaProfileChangedHandle;` — Handle for media profile changed delegate.
- L208 _private member_ `FDelegateHandle ObjectPropertyChangedHandle;` — Handle for object property changed delegate (to detect edits within the active MediaProfile).
- L210 _private member_ `FDelegateHandle CustomTimeStepChangedHandle;` — Handle for engine custom time step changed delegate (used to keep the Hub off the MediaProfile's genlock).
- L213 _private member_ `TPimplPtr<FLiveLinkHubMediaProfileHandler> MediaProfileHandler;` — Manages the transient MediaProfile and its session serialization.
- L216 _private prototype_ `void OnMediaProfileChanged(UMediaProfile* PreviousProfile, UMediaProfile* NewProfile);` — Called when the active MediaProfile changes. Re-broadcasts timecode/genlock settings to connected clients.
- L219 _private prototype_ `void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);` — Called when any UObject property changes. Filters for the active MediaProfile and its timecode/genlock subobjects.
- L225 _private prototype_ `void OnEngineCustomTimeStepChanged();` — Called when GEngine's custom time step changes. Hub shouldn't ever run with a custom timestep, so when the MediaProfile installs its custom time step we synchronously clear it.

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnTopologyModeChanged, ELiveLinkTopologyMode );`
- L32 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnTopologyModeChanged, ELiveLinkTopologyMode );`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/LiveLinkHubAnimationVirtualSubject.h` (Private)


#### class `ULiveLinkHubAnimationVirtualSubject`  
`class ULiveLinkHubAnimationVirtualSubject : public ULiveLinkAnimationVirtualSubject`  
_L21-124_
- reflection: `UCLASS()`
- inherits: `ULiveLinkAnimationVirtualSubject`
- desc: Animation virtual subject used in LiveLinkHub. Shows options for the subject and broadcasts static data when the skeleton is updated.
- L26 _public function_ `virtual void Initialize(FLiveLinkSubjectKey InSubjectKey, TSubclassOf<ULiveLinkRole> InRole, ILiveLinkClient* InLiveLinkClient) override`
- L39 _public function_ `virtual FText GetDisplayName() const override`
- L45 _public function_ `virtual FName GetRebroadcastName() const override`
- L51 _public function_ `virtual bool IsRebroadcasted() const` — Whether this subject is rebroadcasted
- L57 _public function_ `virtual void PostSkeletonRebuild() override`
- L75 _public function_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override`
- L85 _public function_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override`
- L115 _public member_ `FString OutboundName;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")` — Name of the virtual subject.
- L119 _public member_ `FString Source;` — `UPROPERTY(VisibleAnywhere, Category = "LiveLink")` — Source that contains the subject.
- L123 _private member_ `FName PreviousOutboundName;` — Previous outbound name to be used for reverting name changes that aren't valid.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/LiveLinkHubApplication.h` (Private)


#### struct `FLiveLinkHubAppModeInfo`  
`struct FLiveLinkHubAppModeInfo`  
_L13-21_
- desc: Cached information about a given application mode. Used to populate the mode switcher widget.
- L16 _public member_ `FSlateIcon Icon;` — Icon of the mode.
- L18 _public member_ `FText DisplayName;` — Display name for the mode.
- L20 _public member_ `bool bUserLayout = false;` — Whether this is a user layout mode.

#### class `FLiveLinkHubApplication`  
`class FLiveLinkHubApplication : public FLiveLinkHubApplicationBase`  
_L25-150_
- inherits: `FLiveLinkHubApplicationBase`
- L28 _public prototype_ `FLiveLinkHubApplication();`
- L31 _public function_ `FOnApplicationModeChanged& OnApplicationModeChanged()` — Get the delegate called when the app mode has changed.
- L34 _public prototype_ `TOptional<FLiveLinkHubAppModeInfo> GetModeInfo(FName ModeName) const;` — Get information about a given mode. Returns an empty optional if the mode wasn't found or if it wasn't added to the app using AddLiveLinkHubApplicationMode.
- L37 _public prototype_ `FName GetLayoutName(FName ModeName);` — Get the name of the TabLayout for a given mode.
- L40 _public prototype_ `TArray<FName> GetApplicationModes() const;` — Get the list of modes that were registered with the app.
- L43 _public prototype_ `virtual void AddLiveLinkHubApplicationMode(FName ModeName, TSharedRef<FLiveLinkHubApplicationMode> Mode);` — Add a LiveLinkHub application mode.
- L46 _public prototype_ `virtual void PushTabFactories(const FWorkflowAllowedTabSet& FactorySetToPush, TSharedPtr<FLiveLinkHubApplicationMode> ApplicationMode);` — Push tab factories for the given mode.
- L49 _public prototype_ `void PersistUserLayout(const FString& LayoutName, const TSharedPtr<FJsonObject>& JsonLayout);` — Save a user layout to disk.
- L52 _public prototype_ `void SaveLayoutAs();` — Prompt the user to save the current layout file to disk.
- L55 _public prototype_ `void LoadLayout();` — Prompt the user to load a layout file from disk.
- L58 _public prototype_ `void ResetLayout();` — Reset the current layout to its code-defined version. (Only available for non-user layouts)
- L61 _public prototype_ `TArray<FString> GetUserLayouts();` — Get the list of user layouts.
- L64 _public prototype_ `void DeleteUserLayout(const FString& LayoutName);` — Delete a user layout. This will also delete the file on disk.
- L67 _public prototype_ `virtual void SetCurrentMode(FName NewMode) override;`
- L72 _protected function_ `static FString UserSettingsDir()` — Get the path to the user settings.
- L79 _protected function_ `virtual FName GetToolkitFName() const override`
- L80 _protected function_ `virtual FText GetBaseToolkitName() const override`
- L81 _protected function_ `virtual FString GetWorldCentricTabPrefix() const override`
- L82 _protected function_ `FLinearColor GetWorldCentricTabColorScale() const`
- L89 _protected prototype_ `virtual UToolMenu* GenerateCommonActionsToolbar(FToolMenuContext& MenuContext) override;`
- L90 _protected prototype_ `virtual UE::Editor::Toolbars::ECreateStatusBarOptions GetStatusBarCreationOptions() const override;`
- L91 _protected prototype_ `virtual TSharedPtr<SWidget> CreateMenuBar(const TSharedPtr<FTabManager>& InTabManager, const FName InMenuName, FToolMenuContext& InToolMenuContext) override;`
- L92 _protected function_ `virtual void MapToolkitCommands()`
- L93 _protected prototype_ `virtual FText GetToolkitName() const override;`
- L94 _protected prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L95 _protected function_ `virtual FName GetOverrideTabId() const override`
- L99 _protected prototype_ `void DiscoverLayouts();` — Iterate through layout directories to find .llhlayout files.
- L102 _protected prototype_ `bool RegisterUserLayout(const FString& LayoutName, const FString& LayoutFile);` — Creates a user layout app mode from a layout file.
- L106 _private prototype_ `virtual void AddApplicationMode(FName ModeName, TSharedRef<FApplicationMode> Mode) override;` — Don't allow LiveLinkHub to call this directly since it wouldn't register the cached mode info.
- L109 _private prototype_ `void RegisterFileMenu(UToolMenu* Menu);` — Register and populate the file menu with the config commands.
- L111 _private prototype_ `void RegisterMainMenu();` — Create the main menu bar.
- L113 _private prototype_ `void CreateToolsMenu(FMenuBuilder& MenuBuilder, UToolMenu*) const;` — When in dev mode, creates the tool menu that contains the widget reflector and automation window.
- L114 _private prototype_ `void FillWindowMenu(FMenuBuilder& MenuBuilder, UToolMenu*);`
- L117 _private prototype_ `void AddToolbarExtenders(FToolBarBuilder&);` — Used to populate the status toolbar with widgets of the current mode.
- L120 _private prototype_ `void SaveLayoutToFile(const FString& SavePath = TEXT(""), TSharedPtr<FJsonObject> JsonLayout = TSharedPtr<FJsonObject>{});` — Persist layout and save it to the specified path.
- L122 _private prototype_ `TArray<FString> GetLayoutDirectories() const;`
- L125 _private prototype_ `TOptional<struct FLiveLinkHubUserLayout> ParseUserLayout(const FString& LayoutName);` — Read the layout file and convert it to a JsonObject.
- L128 _private prototype_ `TSharedPtr<FLiveLinkHubApplicationMode> FindApplicationMode(const FString& ModeName);` — Get an application mode from
- L130 _private prototype_ `void RemoveLiveLinkHubApplicationMode(FName ModeName);`
- L134 _private member_ `FOnApplicationModeChanged AppModeChangedDelegate;` — Delegate called when the active app mode has changed.
- L137 _private member_ `TMap<FName, FLiveLinkHubAppModeInfo> CachedModeInfo;` — Map of mode name to cached mode info.
- L140 _private member_ `TSharedPtr<FWorkspaceItem> DataViewsWorkspaceCategory;` — Shared workspace menu category for all tabs in the Window menu.
- L143 _private member_ `TMap<FName, TSharedPtr<FWorkspaceItem>> CachedModeWorkspaceCategories;` — Workspace category resolved at registration time for each mode, keyed by mode name.
- L146 _private member_ `FString LastLayoutPath;` — Path to the last saved layout.
- L149 _private member_ `TMap<FString, FString> CachedLayouts;` — Layout name to file path

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnApplicationModeChanged, FName);`
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnApplicationModeChanged, FName);`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/LiveLinkHubClient.h` (Private)


#### class `FLiveLinkHubClient`  
`class FLiveLinkHubClient : public FLiveLinkClient`  
_L22-107_
- inherits: `FLiveLinkClient`
- L25 _public function_ `FLiveLinkHubClient(TSharedPtr<ILiveLinkHub> InLiveLinkHub, FTSSimpleMulticastDelegate& InTickingDelegate) : FLiveLinkClient(InTickingDelegate) , LiveLinkHub(MoveTemp(InLiveLinkHub))`
- L35 _public function_ `FLiveLinkHubClient(TSharedPtr<ILiveLinkHub> InLiveLinkHub) : FLiveLinkClient() , LiveLinkHub(MoveTemp(InLiveLinkHub))`
- L45 _public prototype_ `virtual ~FLiveLinkHubClient();`
- L48 _public function_ `FOnFrameDataReceived_AnyThread& OnFrameDataReceived_AnyThread()` — Get the delegate called when frame data is received.
- L54 _public function_ `FOnStaticDataReceived_AnyThread& OnStaticDataReceived_AnyThread()` — Get the delegate called when static data is received.
- L63 _public function_ `FOnSubjectMarkedPendingKill_AnyThread& OnSubjectMarkedPendingKill_AnyThread()` — Get the delegate called when a subject is marked for deletion. This delegate will fire as soon as the subject is marked for deletion, while the OnSubjectRemovedDelegate may trigger at a later time.
- L69 _public prototype_ `virtual void CacheSubjectSettings(const FLiveLinkSubjectKey& SubjectKey, ULiveLinkSubjectSettings* Settings) const override;` — Cache subject settings for the subject specified by the subject key.
- L73 _public prototype_ `virtual bool CreateSource(const FLiveLinkSourcePreset& InSourcePreset) override;`
- L74 _public prototype_ `virtual FText GetSourceStatus(FGuid InEntryGuid) const override;`
- L75 _public prototype_ `virtual void RemoveSubject_AnyThread(const FLiveLinkSubjectKey& InSubjectKey) override;`
- L76 _public prototype_ `virtual bool AddVirtualSubject(const FLiveLinkSubjectKey& VirtualSubjectKey, TSubclassOf<ULiveLinkVirtualSubject> VirtualSubjectClass) override;`
- L77 _public prototype_ `virtual void RemoveVirtualSubject(const FLiveLinkSubjectKey& VirtualSubjectKey) override;`
- L81 _public prototype_ `virtual TSharedPtr<ILiveLinkProvider> GetRebroadcastLiveLinkProvider() const override;`
- L86 _private prototype_ `void BroadcastStaticDataUpdate(FLiveLinkSubject* InLiveSubject, TSubclassOf<ULiveLinkRole> InRole, const FLiveLinkStaticDataStruct& InStaticData) const;` — Broadcast a static data update to this client's listeners.
- L89 _private prototype_ `void OnStaticDataAdded(FLiveLinkSubjectKey SubjectKey, TSubclassOf<ULiveLinkRole> SubjectRole, const FLiveLinkStaticDataStruct& InStaticData);`
- L90 _private prototype_ `void OnFrameDataAdded(FLiveLinkSubjectKey InSubjectKey, TSubclassOf<ULiveLinkRole> SubjectRole, const FLiveLinkFrameDataStruct& InFrameData);`
- L94 _private member_ `TWeakPtr<ILiveLinkHub> LiveLinkHub;` — Weak pointer to the live link hub.
- L96 _private member_ `FOnFrameDataReceived_AnyThread OnFrameDataReceivedDelegate_AnyThread;` — Delegate called when frame data is received.
- L98 _private member_ `FOnStaticDataReceived_AnyThread OnStaticDataReceivedDelegate_AnyThread;` — Delegate called when static data is received.
- L100 _private member_ `FOnSubjectMarkedPendingKill_AnyThread OnSubjectMarkedPendingKillDelegate_AnyThread;` — Delegate called when a subject is marked for deletion.
- L102 _private member_ `std::atomic<bool> bVirtualSubjectsPresent = false;` — Whether there are virtual subjects at the moment. Used to determine if we should cache frame data for their usage.
- L105 _private member_ `FDelegateHandle StaticDataAddedHandle;`
- L106 _private member_ `FDelegateHandle FrameDataAddedHandle;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnFrameDataReceived_AnyThread, const FLiveLinkSubjectKey&, const FLiveLinkFrameDataStruct&);`
- L17 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnFrameDataReceived_AnyThread, const FLiveLinkSubjectKey&, const FLiveLinkFrameDataStruct&);`
- L18 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnStaticDataReceived_AnyThread, const FLiveLinkSubjectKey&, TSubclassOf<ULiveLinkRole>, const FLiveLinkStaticDataStruct&);`
- L18 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnStaticDataReceived_AnyThread, const FLiveLinkSubjectKey&, TSubclassOf<ULiveLinkRole>, const FLiveLinkStaticDataStruct&);`
- L19 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnSubjectMarkedPendingKill_AnyThread, const FLiveLinkSubjectKey&);`
- L19 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnSubjectMarkedPendingKill_AnyThread, const FLiveLinkSubjectKey&);`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/LiveLinkHubCommands.h` (Private)


#### class `FLiveLinkHubCommands`  
`class FLiveLinkHubCommands : public TCommands<FLiveLinkHubCommands>`  
_L17-58_
- inherits: `TCommands<FLiveLinkHubCommands>`
- desc: The Live Link Hub commands.
- L23 _public function_ `FLiveLinkHubCommands() : TCommands<FLiveLinkHubCommands>( "LiveLinkHub", NSLOCTEXT("Contexts", "LiveLinkHub", "Live Link Hub"), NAME_None, FAppStyle::GetAppStyleSetName() )` — Default constructor.
- L35 _public function_ `virtual void RegisterCommands() override`
- L47 _public member_ `TSharedPtr<FUICommandInfo> NewConfig;` — Start a new config.
- L49 _public member_ `TSharedPtr<FUICommandInfo> OpenConfig;` — Open an existing config.
- L51 _public member_ `TSharedPtr<FUICommandInfo> SaveConfigAs;` — Save the current configuration to a new file.
- L53 _public member_ `TSharedPtr<FUICommandInfo> SaveConfig;` — Save the current configuration to an existing file.
- L55 _public member_ `TSharedPtr<FUICommandInfo> OpenLogsFolder;` — Open the folder containing the logs for live link hub.
- L57 _public member_ `TSharedPtr<FUICommandInfo> OpenAboutMenu;` — Open the About window.

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkHubCommands"`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/LiveLinkHubCrashRecovery.h` (Private)


#### class `FLiveLinkHubCrashRecovery`  
`class FLiveLinkHubCrashRecovery`  
_L17-182_
- desc: Utility class that allows recovering the last autosave file if it detects that the app did not close correctly in its last run.
- L20 _public function_ `FLiveLinkHubCrashRecovery()`
- L35 _public function_ `~FLiveLinkHubCrashRecovery()`
- L45 _private function_ `void ReadCanaryFile()` — Read the canary file from disk and prompt the user for recovering from the last autosave.
- L85 _private function_ `void CreateCanaryFile()` — Create a canary file that contains a PID in case another LiveLinkHub instance launches.
- L112 _private function_ `void DeleteCanaryFile()` — Delete canary file on exit.
- L118 _private function_ `void PromptRecoverLastSave(uint32 ProcessId)` — Prompt user to recover the last save file.
- L153 _private function_ `void RestoreLastAutosave(uint32 CompatibleProcessId)` — Restore the last autosave file that's compatible with the canary file.
- L178 _private member_ `const FString CanaryFilePath = FPaths::Combine(FPlatformProcess::UserSettingsDir(), *FApp::GetEpicProductIdentifier(), TEXT("LiveLinkHub"),` — Default canary file path.
- L181 _private member_ `bool bCreatedCanaryFile = false;` — Whether this instance created a canary file. (If a LiveLinkHub instance is launched while another one is running, we don't create one).

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkHubCrashRecovery"`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/LiveLinkHubCreatorAppMode.h` (Private)


#### struct `FLiveLinkHubDetailsTabSummoner`  
`struct FLiveLinkHubDetailsTabSummoner : public FWorkflowTabFactory`  
_L38-69_
- inherits: `FWorkflowTabFactory`
- L41 _public function_ `FLiveLinkHubDetailsTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, const TSharedPtr<FLiveLinkPanelController>& InPanelController) : FWorkflowTabFactory(UE::LiveLinkHub::SourceDetailsTabId, MoveTemp(InHostingApp)) , WeakPanelController(InPanelController)`
- L51 _public function_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override`
- L62 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`
- L68 _private member_ `TWeakPtr<FLiveLinkPanelController> WeakPanelController;`

#### struct `FLiveLinkHubDataDevicesTabSummoner`  
`struct FLiveLinkHubDataDevicesTabSummoner : public FWorkflowTabFactory`  
_L71-104_
- inherits: `FWorkflowTabFactory`
- L74 _public function_ `FLiveLinkHubDataDevicesTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, const TSharedPtr<FLiveLinkPanelController>& InPanelController) : FWorkflowTabFactory(UE::LiveLinkHub::SubjectsTabId, MoveTemp(InHostingApp)) , WeakPanelController(InPanelController)`
- L84 _public function_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override`
- L96 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`
- L103 _private member_ `TWeakPtr<FLiveLinkPanelController> WeakPanelController;` — Panel controller used to get the list of data devices.

#### struct `FLiveLinkHubRecordingListTabSummoner`  
`struct FLiveLinkHubRecordingListTabSummoner : public FWorkflowTabFactory`  
_L106-127_
- inherits: `FWorkflowTabFactory`
- L109 _public function_ `FLiveLinkHubRecordingListTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp) : FWorkflowTabFactory(UE::LiveLinkHub::RecordingListTabId, MoveTemp(InHostingApp))`
- L118 _public function_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override`
- L123 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### struct `FLiveLinkHubPlaybackTabSummoner`  
`struct FLiveLinkHubPlaybackTabSummoner : public FWorkflowTabFactory`  
_L129-151_
- inherits: `FWorkflowTabFactory`
- L132 _public function_ `FLiveLinkHubPlaybackTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp) : FWorkflowTabFactory(UE::LiveLinkHub::PlaybackTabId, MoveTemp(InHostingApp))`
- L142 _public function_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override`
- L147 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### struct `FLiveLinkHubClientsTabSummoner`  
`struct FLiveLinkHubClientsTabSummoner : public FWorkflowTabFactory`  
_L153-177_
- inherits: `FWorkflowTabFactory`
- L156 _public function_ `FLiveLinkHubClientsTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp) : FWorkflowTabFactory(UE::LiveLinkHub::ClientsTabId, MoveTemp(InHostingApp))`
- L165 _public function_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override`
- L173 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### struct `FLiveLinkHubClientDetailsTabSummoner`  
`struct FLiveLinkHubClientDetailsTabSummoner : public FWorkflowTabFactory`  
_L179-203_
- inherits: `FWorkflowTabFactory`
- L182 _public function_ `FLiveLinkHubClientDetailsTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp) : FWorkflowTabFactory(UE::LiveLinkHub::ClientDetailsTabId, MoveTemp(InHostingApp))`
- L191 _public function_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override`
- L199 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### class `FLiveLinkHubCreatorAppMode`  
`class FLiveLinkHubCreatorAppMode : public FLiveLinkHubApplicationMode`  
_L206-354_
- inherits: `FLiveLinkHubApplicationMode`
- desc: Default application mode for the hub. Hosts the tabs necessary for viewing Sources, Subjects and clients.
- L209 _public function_ `FLiveLinkHubCreatorAppMode(TSharedPtr<FLiveLinkHubApplicationBase> App) : FLiveLinkHubApplicationMode("CreatorMode", LOCTEXT("CreatorModeLabel", "Live Data"), App)`
- L297 _public function_ `virtual ~FLiveLinkHubCreatorAppMode()`
- L308 _public function_ `virtual FSlateIcon GetModeIcon() const`
- L313 _public function_ `virtual TArray<TSharedRef<SWidget>> GetStatusBarWidgets_Impl() override`
- L325 _private function_ `void OnSubjectSelectionChanged(const FLiveLinkSubjectKey& SubjectKey)` — Handles updating the active subject in the subject controller.
- L332 _private function_ `bool IsSourcePanelReadOnly() const` — Returns whether the source panel is read only (such as when we're playing back a recording)
- L339 _private function_ `FText GetLoadedConfigText() const` — Returns the name of the active session.
- L353 _protected member_ `TSharedPtr<FLiveLinkPanelController> PanelController;` — Holds the livelink panel controller responsible for creating sources and subjects tabs.

#### Free symbols / members of external scopes

- L36 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkHubCreatorMode"`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/LiveLinkHubInputProcessor.h` (Private)


#### class `FLiveLinkHubInputProcessor`  
`class FLiveLinkHubInputProcessor : public IInputProcessor`  
_L14-28_
- inherits: `IInputProcessor`
- desc: This class will allow us to suppress gamepad input events for the slate application.
- L17 _public prototype_ `FLiveLinkHubInputProcessor() = default;`
- L18 _public prototype_ `virtual ~FLiveLinkHubInputProcessor() = default;`
- L21 _public prototype_ `virtual bool HandleKeyDownEvent( FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent ) override;`
- L22 _public prototype_ `virtual bool HandleKeyUpEvent( FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent ) override;`
- L23 _public prototype_ `virtual bool HandleAnalogInputEvent( FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent ) override;`
- L25 _public function_ `virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override`
- L27 _public function_ `virtual const TCHAR* GetDebugName() const override`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/LiveLinkHubLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkHub, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkHub, Log, All);`
- L10 _delegate_ `DECLARE_STATS_GROUP(TEXT("Live Link Hub"), STATGROUP_LiveLinkHub, STATC`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/LiveLinkHubModule.h` (Private)


#### class `FLiveLinkHubModule`  
`class FLiveLinkHubModule : public ILiveLinkHubModule`  
_L19-62_
- inherits: `ILiveLinkHubModule`
- L23 _public prototype_ `virtual void StartupModule() override;`
- L24 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _public prototype_ `TSharedPtr<FLiveLinkHub> GetLiveLinkHub() const;` — Get the livelink hub object.
- L30 _public prototype_ `TSharedPtr<FLiveLinkHubProvider> GetLiveLinkProvider() const;` — Get the livelink provider responsible for forwarding livelink data to connected UE clients.
- L32 _public prototype_ `TSharedPtr<FLiveLinkHubRecordingController> GetRecordingController() const;` — Get the recording controller.
- L34 _public prototype_ `TSharedPtr<FLiveLinkHubRecordingListController> GetRecordingListController() const;` — Get the recording list controller.
- L36 _public prototype_ `TSharedPtr<FLiveLinkHubPlaybackController> GetPlaybackController() const;` — Get the playback controller.
- L38 _public prototype_ `TSharedPtr<FLiveLinkHubSubjectController> GetSubjectController() const;` — Get the subject controller.
- L40 _public prototype_ `TSharedPtr<ILiveLinkHubSessionManager> GetSessionManager() const;` — Get the subject controller.
- L42 _public prototype_ `FLiveLinkHubRecordingMountManager* GetRecordingMountManager() const;` — Get the recording mount manager.
- L46 _private member_ `TSharedPtr<FLiveLinkHub> LiveLinkHub;` — LiveLinkHub object responsible for initializing the different controllers.
- L49 _private member_ `FLiveLinkHubTicker Ticker;` — Utility object used to tick LiveLink outside of the game thread.
- L52 _private member_ `TUniquePtr<FLiveLinkHubRecordingMountManager> RecordingMountManager;` — Manages custom mount points for recording directories.
- L55 _private member_ `bool bUseSubjectSettingsDetailsCustomization = false;` — Config-driven. True in LiveLink Hub standalone application, false in UE.
- L58 _private member_ `bool bUseSettingsDetailCustomization = false;` — Overrides standard livelink settings customization. Config-driven. True in LiveLink Hub standalone application, false in UE.
- L61 _private member_ `bool bCreateLiveLinkHubInstance = false;` — Whether or not to create a LiveLinkHub instance (false in editor).

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/LiveLinkHubPlaybackAppMode.h` (Private)


#### class `FLiveLinkHubPlaybackAppMode`  
`class FLiveLinkHubPlaybackAppMode : public FLiveLinkHubApplicationMode`  
_L20-79_
- inherits: `FLiveLinkHubApplicationMode`
- desc: Compact mode focused exclusively on playing back recordings.
- L23 _public function_ `FLiveLinkHubPlaybackAppMode(TSharedPtr<FLiveLinkHubApplicationBase> App) : FLiveLinkHubApplicationMode("PlaybackMode", LOCTEXT("PlaybackModeLabel", "Playback"), App)`
- L42 _public function_ `virtual void PostActivateMode() override`
- L58 _public function_ `virtual void PreDeactivateMode() override`
- L71 _public function_ `virtual FSlateIcon GetModeIcon() const`
- L78 _private member_ `FVector2d PreviousWindowSize;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkHubPlaybackMode"`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/LiveLinkHubSubjectSettingsUtils.h` (Private)


#### class `FLiveLinkHubSubjectSettingsUtils`  
`class FLiveLinkHubSubjectSettingsUtils`  
_L11-61_
- L15 _public function_ `static bool ValidateOutboundName(const FString& SubjectName, FName PreviousOutboundName, const FString& InOutboundNameCandidate)` — Notify connected clients that this subject's name has changed.
- L34 _public function_ `static void NotifyRename(FName PreviousOutboundName, const FString& OutboundName, const FLiveLinkSubjectKey& SubjectKey)` — Returns whether a new name candidate for the outbound name is valid.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/LiveLinkHubTicker.h` (Private)


#### class `FLiveLinkHubTicker`  
`class FLiveLinkHubTicker : public FRunnable`  
_L12-94_
- inherits: `FRunnable`
- desc: Object used to tick LiveLinkHub outside of the game thread.
- L15 _public function_ `void StartTick()`
- L27 _public function_ `virtual uint32 Run() override`
- L48 _public function_ `virtual void Exit() override`
- L72 _public function_ `void TriggerUpdate()`
- L84 _public function_ `FTSSimpleMulticastDelegate& OnTick()` — Get the delegate called whenever this object ticks.
- L87 _private member_ `std::atomic<bool> bIsRunning = false;`
- L90 _private member_ `FTSSimpleMulticastDelegate OnTickDelegate;` — Delegate called when this ticks.
- L92 _private member_ `FEvent* TickEvent = nullptr;`
- L93 _private member_ `TUniquePtr<FRunnableThread> Thread;`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/LiveLinkHubUserLayoutMode.h` (Private)


#### class `FLiveLinkHubUserLayoutMode`  
`class FLiveLinkHubUserLayoutMode : public FLiveLinkHubApplicationMode`  
_L10-50_
- inherits: `FLiveLinkHubApplicationMode`
- desc: ApplicationMode that represents a user layout. It acts as a proxy for its parent mode.
- L13 _public prototype_ `FLiveLinkHubUserLayoutMode(FName InLayoutName, TSharedRef<FJsonObject> UserLayout, TSharedPtr<FLiveLinkHubApplicationMode> InParentMode);`
- L16 _public function_ `const TSharedPtr<FLiveLinkHubApplicationMode>& GetParentMode() const` — Get the parent mode that holds the actual functionality (ie. Creator mode, Capture Manager)
- L22 _public function_ `virtual FSlateIcon GetModeIcon() const override`
- L27 _public function_ `virtual bool IsUserLayout() const override`
- L32 _public function_ `virtual TArray<TSharedRef<SWidget>> GetStatusBarWidgets_Impl() override`
- L37 _public function_ `virtual TArray<TSharedRef<SWidget>> GetToolbarWidgets_Impl() override`
- L42 _public prototype_ `virtual void PreDeactivateMode() override;`
- L47 _private member_ `TSharedPtr<FLiveLinkHubApplicationMode> ParentMode;` — The mode that holds the functionality and tab spawners for this mode.
- L49 _private member_ `FString ParentLayoutName;` — Layout name of the parent mode (ie. LiveLinkHubCreatorMode_V1.0)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/Implementations/LiveLinkFrameData.h` (Private)


#### struct `UE::LiveLinkHub::FrameData::Private::FFrameBufferCache`  
`struct FFrameBufferCache`  
_L12-34_
- desc: Data manager for frames which have been loaded.
- L15 _public member_ `TArray<FLiveLinkRecordingBaseDataContainer> FrameData;` — Loaded frame data.
- L18 _public prototype_ `void TrimCache();` — Ensure the size of the cache is limited, removing older entries.
- L21 _public prototype_ `void CleanCache(const TRange<int32>& InActiveRange);` — Remove data from the cache that is no longer needed.
- L27 _public prototype_ `RangeHelpers::Private::TRangeArray<int32> GetCacheBufferRanges(bool bIncludeOffset = false) const;` — Return all ranges contained within the cache. @param bIncludeOffset If the local frame time-to-frame index offset used should be added to the ranges.
- L30 _public prototype_ `TSharedPtr<FInstancedStruct> TryGetCachedFrame(const int32 InFrame, double& OutTimestamp);` — Look through the cache for a loaded frame.
- L33 _public prototype_ `bool ContainsFrame(const int32 InFrame) const;` — Checks if a frame is contained within the cache.

#### struct `UE::LiveLinkHub::FrameData::Private::FFrameBufferIterationData`  
`struct FFrameBufferIterationData`  
_L37-94_
- desc: Keeps track of current frame iterations while buffering.
- L66 _public member_ `int32 LastLoadedLeftFrame;` — The last loaded left frame.
- L68 _public member_ `int32 LastLoadedRightFrame;` — The last loaded right frame.
- L70 _public member_ `bool bLoadRight;` — If we are loading to the right.
- L72 _public member_ `ECompletionStatus Status;` — Current status of this iteration.
- L75 _public member_ `FTemporaryData ForwardData;` — Forward-looking frame data.
- L77 _public member_ `FTemporaryData ReverseData;` — Reverse looking frame data.
- L79 _public function_ `FFrameBufferIterationData()`
- L85 _public function_ `void Reset()` — Resets the iteration to a new iteration, clearing all storage.

#### enum `UE::LiveLinkHub::FrameData::Private::FFrameBufferIterationData::ECompletionStatus`  
`enum ECompletionStatus`  
_L39-49_
- L42 _public enumerator_ `New` — New iteration, no processing has performed yet.
- L44 _public enumerator_ `Active` — Iteration is currently active.
- L46 _public enumerator_ `Canceled` — Iteration has been canceled for any reason.
- L48 _public enumerator_ `Complete` — Iteration has fully completed, buffering all available requested frames.

#### struct `UE::LiveLinkHub::FrameData::Private::FFrameBufferIterationData::FTemporaryData`  
`struct FTemporaryData`  
_L52-63_
- desc: Temporary storage for loaded frames, which gets moved to data containers after loading.
- L55 _public member_ `TArray<TSharedPtr<FInstancedStruct>> RecordedData;` — Fully processed frame data.
- L57 _public member_ `TArray<double> Timestamps;` — Timestamps corresponding to the frame data.
- L58 _public function_ `void Reset()`

#### struct `UE::LiveLinkHub::FrameData::Private::FFrameMetaData`  
`struct FFrameMetaData`  
_L97-218_
- desc: Frame data information when loading from a recording file.
- L100 _public member_ `TSharedPtr<FLiveLinkSubjectKey> FrameDataSubjectKey;` — The subject key used for the frame data.
- L102 _public member_ `TWeakObjectPtr<UScriptStruct> LoadedStruct;` — The struct for this frame data.
- L104 _public member_ `int64 RecordingStartFrameFilePosition = 0;` — The position in the file recording where frame data begins.
- L106 _public member_ `int32 MaxFrames = 0;` — Maximum number of frames.
- L108 _public member_ `TArray<TTuple<int64, int32>> FrameDiskSizes;` — Frame offsets and sizes. [FrameOffsetBytes, FrameSizeBytes]
- L110 _public member_ `TArray<double> Timestamps;` — All timestamps for the track, whether the frame is loaded or not.
- L112 _public member_ `bool bHasConsistentFrameSize = false;` — Whether the frame size is consistent throughout this animation.
- L114 _public member_ `double LastTimestamp = 0.f;` — The last timestamp for this frame data.
- L116 _public member_ `FFrameRate LocalFrameRate;` — The frame rate, based only off of number of frames and the last timestamp.
- L118 _public member_ `FFrameBufferCache BufferedCache;` — Cache of previously buffered frames, which are not currently active.
- L120 _public member_ `FFrameBufferIterationData BufferIterationData;` — Current iteration data while buffering.
- L122 _public member_ `FName CompressionMethodName;` — Name of the compression method used on the frame data.
- L129 _public function_ `int32 FindFrameFromTimestamp(const double InTimestamp, const int32 InIndexHint) const` — Find the closest frame matching the given timestamp. @param InTimestamp The timestamp of the frame. @param InIndexHint A hint to where the index might be, allowing quicker search times.
- L200 _public function_ `int32 GetFrameDiskSize(const int32 InFrameIdx) const` — The size in bytes of an animation frame.
- L207 _public function_ `int64 GetFrameFilePosition(const int32 InFrameIdx) const` — Find the correct file offset based on the frame index.
- L213 _public function_ `int64 GetRelativeFrameFilePosition(const int32 InFrameIdx) const` — Find the offset relative to local storage only, not accounting for disk position.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace LiveLinkHub` (scope `UE`)
- L9 _namespace_ `namespace FrameData` (scope `UE::LiveLinkHub`)
- L9 _namespace_ `namespace Private` (scope `UE::LiveLinkHub::FrameData`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/Implementations/LiveLinkRecordingDataContainer.h` (Private)


#### struct `FLiveLinkRecordingBaseDataContainer`  
`struct FLiveLinkRecordingBaseDataContainer`  
_L13-96_
- reflection: `USTRUCT()`
- desc: Base data container for a recording track.
- L18 _public member_ `TArray<double> Timestamps;` — SERIALIZED DATA - Timestamps for the recorded data. Each entry matches an entry in the RecordedData array.
- L25 _public member_ `TArray<TSharedPtr<FInstancedStruct>> RecordedData;` — SERIALIZED DATA - Array of either static or frame recorded for a given timestamp. TSharedPtr used as streaming the data in may require shared access. FSharedStruct is not used because it doesn't implement Serialize().
- L28 _public member_ `int32 RecordedDataStartFrame = 0;` — The current start frame for RecordedData.
- L31 _public member_ `int32 LocalFrameOffset = 0;` — Offset which was applied locally during frame rate conversions to find the correct timestamp.
- L34 _public prototype_ `bool IsEmpty() const;` — If this container contains no data.
- L37 _public prototype_ `void ClearData();` — Empty all data.
- L43 _public prototype_ `TRange<int32> GetBufferedFrames(bool bIncludeOffset = false) const;` — Retrieve the total buffered frames. @param bIncludeOffset If the local frame time-to-frame index offset used should be added to the ranges.
- L52 _public prototype_ `TSharedPtr<FInstancedStruct> TryGetFrame(const int32 InFrame) const;` — Retrieve a loaded frame. @param InFrame The absolute frame index to load. @return The frame if it exists.
- L62 _public prototype_ `TSharedPtr<FInstancedStruct> TryGetFrame(const int32 InFrame, double& OutTimestamp) const;` — Retrieve a loaded frame. @param InFrame The absolute frame index to load. @param OutTimestamp Return the timestamp, if it exists. @return The frame if it exists.
- L68 _public prototype_ `void RemoveFramesBefore(const int32 InEndFrame);` — Remove all frames before, and including, the input frame. @param InEndFrame The final frame to remove, inclusive.
- L74 _public prototype_ `void RemoveFramesAfter(const int32 InStartFrame);` — Remove all frames including and after the input frame. @param InStartFrame The first frame to remove, inclusive.
- L77 _public function_ `int32 GetRelativeFrameIndex(const int32 InFrame) const` — Convert the absolute frame to the relative index for this data container.
- L89 _public function_ `bool IsFrameLoaded(const int32 InFrame) const` — Checks if a frame is currently loaded. @param InFrame The absolute frame index to check. @return True if the frame index exists within the frame array.
- L95 _public prototype_ `void ValidateData() const;` — Check data memory is valid and expected.

#### struct `FLiveLinkRecordingStaticDataContainer`  
`struct FLiveLinkRecordingStaticDataContainer : public FLiveLinkRecordingBaseDataContainer`  
_L100-107_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkRecordingBaseDataContainer`
- desc: Container for static data.
- L106 _public member_ `TSubclassOf<ULiveLinkRole> Role;` — `UPROPERTY()` — The role of the static data being recorded.

#### struct `FLiveLinkUAssetRecordingData`  
`struct FLiveLinkUAssetRecordingData`  
_L110-125_
- reflection: `USTRUCT()`
- L116 _public member_ `double LengthInSeconds = 0;` — `UPROPERTY()` — Length of the recording in seconds.
- L120 _public member_ `TMap<FLiveLinkSubjectKey, FLiveLinkRecordingStaticDataContainer> StaticData;` — `UPROPERTY()` — Static data encountered while recording.
- L124 _public member_ `TMap<FLiveLinkSubjectKey, FLiveLinkRecordingBaseDataContainer> FrameData;` — `UPROPERTY()` — Frame data encountered while recording.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/Implementations/LiveLinkUAssetRecorder.h` (Private)


#### class `FLiveLinkUAssetRecorder`  
`class FLiveLinkUAssetRecorder : public ILiveLinkRecorder`  
_L17-91_
- inherits: `ILiveLinkRecorder`
- desc: UAsset implementation for serializing recorded livelink data.
- L22 _public prototype_ `virtual void StartRecording() override;`
- L23 _public prototype_ `virtual void StopRecording() override;`
- L24 _public prototype_ `virtual void RecordStaticData(const FLiveLinkSubjectKey& SubjectKey, TSubclassOf<ULiveLinkRole> Role, const FLiveLinkStaticDataStruct& StaticData) override;`
- L25 _public prototype_ `virtual void RecordFrameData(const FLiveLinkSubjectKey& SubjectKey, const FLiveLinkFrameDataStruct& FrameData) override;`
- L26 _public prototype_ `virtual bool IsRecording() const override;`
- L27 _public prototype_ `virtual bool CanRecord(FText* OutErrorMessage) const override;`
- L28 _public prototype_ `virtual void SaveFromExistingRecording(ULiveLinkRecording* InRecording, const FString& InFilePath, bool bUpgradeInPlace) override;`
- L29 _public prototype_ `virtual bool GetSavePresetPackageName(FString& OutName, const FString& InDefaultName = FString(), bool bAlwaysOpenSaveAsDialog = false) const override;`
- L34 _private prototype_ `bool OpenSaveDialog(const FString& InDefaultPath, const FString& InNewNameSuggestion, FString& OutPackageName) const;` — Prompt the user for a destination path for the recording.
- L36 _private prototype_ `void SaveRecording(FLiveLinkUAssetRecordingData&& InRecordingData, double InRecordingLength, bool bIncrementTake, const TObjectPtr<ULiveLinkPreset>& InPreset = nullptr, const FFrameRate* InFrameRate = nullptr, const FString& InFilePath = FString());` — Create a recording package and save it.
- L39 _private prototype_ `void SaveRecordingInPlace(ULiveLinkUAssetRecording* InRecording);`
- L41 _private prototype_ `void RecordBaseData(FLiveLinkRecordingBaseDataContainer& StaticDataContainer, TSharedPtr<FInstancedStruct>&& DataToRecord);` — Record data to a ULiveLinkRecording object.
- L43 _private prototype_ `void RecordInitialStaticData();` — Record initial data for all livelink subjects. (Useful when static data was sent before the recording started).
- L77 _private prototype_ `void OnRecordingDataSaved_GameThread(FLiveLinkSaveRecordingAsyncTask* InTask);` — Called on the game thread after the recording data has been saved.
- L79 _private prototype_ `void OnRecordingSaveThreadFinished_GameThread(FLiveLinkSaveRecordingAsyncTask* InTask);` — Called when the async save thread has finished.
- L82 _private member_ `TMap<TStrongObjectPtr<ULiveLinkUAssetRecording>, TUniquePtr<FAsyncTask<FLiveLinkSaveRecordingAsyncTask>>> AsyncSaveTasks;` — Current async save tasks.
- L84 _private member_ `TPimplPtr<FLiveLinkUAssetRecordingData> CurrentRecording;` — Holds metadata and recording data.
- L86 _private member_ `bool bIsRecording = false;` — Whether we're currently recording livelink data.
- L88 _private member_ `double TimeRecordingStarted = 0.0;` — Timestamp in seconds of when the recording was started.
- L90 _private member_ `double TimeRecordingEnded = 0.0;` — Timestamp in seconds of when the recording ended.

#### class `FLiveLinkUAssetRecorder::FLiveLinkSaveRecordingAsyncTask`  
`class FLiveLinkSaveRecordingAsyncTask : public FNonAbandonableTask`  
_L46-74_
- inherits: `FNonAbandonableTask`
- L49 _public function_ `FLiveLinkSaveRecordingAsyncTask(ULiveLinkUAssetRecording* InLiveLinkRecording, FLiveLinkUAssetRecorder* InRecorder)`
- L55 _public function_ `TStatId GetStatId() const`
- L60 _public prototype_ `void DoWork();`
- L63 _public function_ `void NotifyPackageSaveStarted()` — Notify we have started saving the package.
- L65 _public function_ `TWeakObjectPtr<ULiveLinkUAssetRecording> GetRecording() const` — The recording being saved by this task.
- L69 _private member_ `TWeakObjectPtr<ULiveLinkUAssetRecording> LiveLinkRecording;` — The recording being saved.
- L71 _private member_ `FLiveLinkUAssetRecorder* Recorder = nullptr;` — The recorder owner.
- L73 _private member_ `FEventRef PackageSaveStartedEvent;` — If the game thread has started to save the package.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/Implementations/LiveLinkUAssetRecording.h` (Private)


#### class `ULiveLinkUAssetRecording`  
`class ULiveLinkUAssetRecording : public ULiveLinkRecording`  
_L25-297_
- reflection: `UCLASS()`
- inherits: `ULiveLinkRecording`
- desc: Asset containing all animation data stored as bulk data. This is loaded async in chunks dependent on the playhead position. Overall recording length, framerate, and frame indices are based on the maximum track length and farthest timestamp. When locating frames by indices the track will localize the frame index based on its internal framerate. All frame rates are based strictly on the number of frames and the last timestamp of the track. True frame rate is up to the client.
- L32 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L34 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L35 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L37 _public function_ `virtual bool IsFullyLoaded() const override`
- L38 _public function_ `virtual bool IsSavingRecordingData() const override`
- L39 _public function_ `virtual int32 GetMaxFrames() const override`
- L40 _public function_ `virtual double GetLastTimestamp() const override`
- L41 _public prototype_ `virtual FQualifiedFrameTime GetLastFrameTime() const override;`
- L42 _public prototype_ `virtual FFrameRate GetGlobalFrameRate() const override;`
- L43 _public prototype_ `virtual void LoadEntireRecording() override;`
- L44 _public function_ `virtual bool IsLoadingEntireRecording() const override`
- L47 _public prototype_ `void SaveRecordingData();` — Save recording data to disk.
- L50 _public prototype_ `void LoadRecordingData(int32 InInitialFrame, int32 InNumFramesToLoad);` — Load recording data from disk.
- L53 _public prototype_ `void LoadEntireRecordingForUpgrade();` — Load the entire recording and notify this is for an upgrade.
- L56 _public prototype_ `void UnloadRecordingData();` — Free memory and close file reader.
- L59 _public prototype_ `bool WaitForBufferedFrames(int32 InMinFrame, int32 InMaxFrame);` — Block until frames are loaded.
- L62 _public function_ `int32 GetFrameDiskSize() const` — The size in bytes of each animation frame.
- L68 _public prototype_ `UE::LiveLinkHub::RangeHelpers::Private::TRangeArray<int32> GetBufferedFrameRanges(bool bIncludeInactive = true) const;` — Return all buffered frame ranges. @param bIncludeInactive If buffer ranges that are considered inactive should be included in the result.
- L71 _public prototype_ `bool IsFrameRangeBuffered(const TRange<int32>& InRange) const;` — Checks if a specific frame range is buffered.
- L74 _public function_ `bool IsUpgrading() const` — If the recording is currently upgrading.
- L77 _public prototype_ `void CopyRecordingData(FLiveLinkPlaybackTracks& InOutLiveLinkPlaybackTracks) const;` — Copy the asset's loaded recording data to a format suitable for playback in live link.
- L80 _public prototype_ `void InitializeNewRecordingData(FLiveLinkUAssetRecordingData&& InRecordingData, double InRecordingLengthSeconds);` — Initial setup of new recording data.
- L83 _public function_ `bool HasPerformedInitialLoad() const` — If the recording has performed its initial load.
- L86 _public prototype_ `static FFrameRate CalculateFrameRate(const int32 InMaxFrames, const double InTime);` — Calculate the framerate.
- L88 _public prototype_ `DECLARE_DELEGATE(FOnRecordingInitialLoad);`
- L90 _public function_ `FOnRecordingInitialLoad& GetOnRecordingInitialLoad()` — Delegate fired when the recording has performed an initial load.
- L92 _public prototype_ `DECLARE_DELEGATE(FOnRecordingFullyLoaded);`
- L94 _public function_ `FOnRecordingFullyLoaded& GetOnRecordingFullyLoaded()` — Delegate fired when a recording has fully loaded.
- L98 _private prototype_ `void SaveFrameData(FArchive* InFileWriter, const FLiveLinkSubjectKey& InSubjectKey, FLiveLinkRecordingBaseDataContainer& InBaseDataContainer);` — Serialize the number of frames (array size) of the BaseDataContainer to the archive.
- L101 _private prototype_ `void LoadRecordingAsync(int32 InStartFrame, int32 InCurrentFrame, int32 InNumFramesToLoad);` — Initialize or update an async load.
- L104 _private prototype_ `bool LoadInitialFrameData(UE::LiveLinkHub::FrameData::Private::FFrameMetaData& OutFrameData);` — Initial processing on a frame, finding the correct struct and offsets. The RecordingFileReader is assumed to be at the correct position.
- L117 _private prototype_ `void LoadFrameData(UE::LiveLinkHub::FrameData::Private::FFrameMetaData& InFrameData, FLiveLinkRecordingBaseDataContainer& InDataContainer, int32 RequestedStartFrame, int32 RequestedInitialFrame, int32 RequestedFramesToLoad, bool bForceSequential = false);` — Load frame data to a data container. By default, it loads frames from the initial frame and then alternates in batches right then left. @param InFrameData The meta frame data being read and updated. @param InDataContainer The data container for loaded frames to be stored. @param RequestedStartFrame The farthest left start frame to load. @param RequestedInitialFrame The first frame to be loaded, such as the midpoint, or the start frame. @param RequestedFramesToLoad The total frames to try to load. @param bForceSequential Whether to force a sequential load, left to right, rather than alternating. In this case all frames from RequestedStartFrame to RequestedFramesToLoad are loaded.
- L128 _private prototype_ `bool LoadFrameFromDisk(const int32 InFrame, const UE::LiveLinkHub::FrameData::Private::FFrameMetaData& InFrameData, TSharedPtr<FInstancedStruct>& OutFrame, double& OutTimestamp, const TSharedPtr<FLiveLinkHubBulkData::FScopedBulkDataMemoryReader>& InMemory = nullptr);` — Attempt to load a frame from bulk data. @param InFrame The frame number to process. @param InFrameData The frame data containing relevant information about this frame. @param OutFrame The deserialized frame. @param OutTimestamp The deserialized timestamp. @param InMemory [Optional] If we are reading from memory rather than bulk data directly.
- L134 _private prototype_ `bool LoadTimestampFromDisk(const int32 InFrame, const UE::LiveLinkHub::FrameData::Private::FFrameMetaData& InFrameData, double& OutTimestamp);` — Only load the timestamp from disk.
- L137 _private prototype_ `TSharedPtr<FLiveLinkHubBulkData::FScopedBulkDataMemoryReader> LoadRawFramesFromDisk(const int32 InFrame, const int32 InNumFrames, const UE::LiveLinkHub::FrameData::Private::FFrameMetaData& InFrameData);` — Load multiple frames as raw data from bulk data. They still need to be passed to LoadFrameFromDisk, so they can be deserialized.
- L141 _private prototype_ `void EjectAndUnload();` — Eject this recording and make sure it is unloaded.
- L144 _private prototype_ `void MoveFrameDataToContainer(FLiveLinkRecordingBaseDataContainer& InDataContainer, UE::LiveLinkHub::FrameData::Private::FFrameMetaData& InFrameData) const;` — Move frame iteration data to the data container.
- L148 _private prototype_ `void MoveRangeToCache(const TRange<int32>& InRange, FLiveLinkRecordingBaseDataContainer& InDataContainer, UE::LiveLinkHub::FrameData::Private::FFrameMetaData& InFrameData) const;` — Moves a range of frames from the container to the frame data cache.
- L152 _private prototype_ `void UpdateBufferedFrames();` — Update the buffered frame range.
- L155 _private prototype_ `void WaitIfPaused_AsyncThread();` — Make the thread wait if we are paused.
- L158 _private function_ `bool StreamingFrameChangedRequested() const` — If the requested streaming frame has been changed.
- L161 _private prototype_ `void PauseStream();` — Signal and wait for the stream to be paused.
- L164 _private prototype_ `void UnpauseStream();` — Signal the stream can be resumed.
- L167 _private prototype_ `void OnPreGarbageCollect();` — Called before garbage collection.
- L170 _private prototype_ `void OnPostGarbageCollect();` — Called after garbage collection.
- L174 _public member_ `FLiveLinkUAssetRecordingData RecordingData;` — `UPROPERTY()` — Recorded static and frame data.
- L206 _private member_ `FLiveLinkHubBulkData AnimationData;` — The animation data -- bulk data stored within this uasset.
- L209 _private member_ `TMap<FLiveLinkSubjectKey, UE::LiveLinkHub::FrameData::Private::FFrameMetaData> FrameFileData;` — The loaded frame data keys and position. Mapped by FLiveLinkSubjectKey to allow easy retrieval.
- L212 _private member_ `std::atomic<int32> RecordingMaxFrames = 0;` — The maximum frames for this recording.
- L215 _private member_ `std::atomic<double> RecordingLastTimestamp = 0.0;` — The last time stamp of the recording.
- L222 _private member_ `FFrameRate RecordingLastTimestampFramerate;` — The framerate of the track the last timestamp belongs to. We store this because we need to calculate all frames conversion between tracks to this "global" rate.
- L225 _private member_ `UE::LiveLinkHub::RangeHelpers::Private::TRangeArray<int32> BufferedFrameRanges;` — Frames buffered, divided into ranges.
- L227 _private member_ `UE::LiveLinkHub::RangeHelpers::Private::TRangeArray<int32> InactiveBufferedFrameRanges;` — Ranges that are buffered but considered inactive.
- L230 _private member_ `int32 EarliestFrameToStream = 0;` — The first (left most) frame to stream.
- L233 _private member_ `int32 InitialFrameToStream = 0;` — The initial frame to start streaming (the current playhead position).
- L236 _private member_ `int32 TotalFramesToStream = 0;` — Total frames which should be streamed.
- L239 _private member_ `std::atomic<int32> StreamingFrameChangeFromFrame = INDEX_NONE;` — When the streaming frame has changed, signalling the current stream task should restart.
- L242 _private member_ `std::atomic<bool> bCancelStream = false;` — Signal that the stream should be canceled.
- L245 _private member_ `std::atomic<bool> bPauseStream = false;` — Signal that the stream should be paused.
- L248 _private member_ `std::atomic<bool> bPerformedInitialLoad = false;` — True once a full initial load has been performed -- static + frame data.
- L251 _private member_ `std::atomic<bool> bIsSavingRecordingData = false;` — If we are currently saving recording frame data to disk.
- L254 _private member_ `std::atomic<bool> bIsPerformingFullLoad = false;` — If we are currently loading all data from disk.
- L257 _private member_ `std::atomic<int32> MaxFrameDiskSize = 0;` — The maximum frame disk size across frame data.
- L260 _private member_ `mutable FCriticalSection BufferedFrameMutex;` — Mutex for accessing the buffered frames.
- L263 _private member_ `mutable FCriticalSection DataContainerMutex;` — Mutex for accessing the data container from multiple threads.
- L266 _private member_ `TUniquePtr<FAsyncTask<FLiveLinkStreamAsyncTask>> AsyncStreamTask;` — The thread streaming data from disk.
- L269 _private member_ `FDelegateHandle OnPreGarbageCollectHandle;` — Handle for when gc is about to run.
- L272 _private member_ `FDelegateHandle OnPostGarbageCollectHandle;` — Handle for when gc has finished.
- L275 _private member_ `FEventRef OnStreamPausedEvent = FEventRef(EEventMode::ManualReset);` — Signalled when the stream is successfully paused.
- L278 _private member_ `FEventRef OnStreamUnpausedEvent = FEventRef(EEventMode::ManualReset);` — Signalled when the stream has been unpaused.
- L281 _private member_ `bool bIsFullyLoaded = false;` — If the recording is fully loaded into memory.
- L284 _private member_ `bool bIsUpgrading = false;` — Upgrade in progress.
- L287 _private member_ `FOnRecordingFullyLoaded OnRecordingInitialLoadEvent;` — Called on the main thread when the recording has performed an initial load.
- L290 _private member_ `FOnRecordingFullyLoaded OnRecordingFullyLoadedEvent;` — Called on the main thread when the recording has fully loaded.
- L293 _private member_ `const int32 CurrentRecordingVersion = UE::LiveLinkHub::Private::RecordingVersions::Latest;` — The current version of the recording.
- L296 _private member_ `int32 RecordingVersionBeingLoaded = 0;` — The version being currently loaded.

#### class `ULiveLinkUAssetRecording::FLiveLinkStreamAsyncTask`  
`class FLiveLinkStreamAsyncTask : public FNonAbandonableTask`  
_L177-203_
- inherits: `FNonAbandonableTask`
- L180 _public function_ `FLiveLinkStreamAsyncTask(ULiveLinkUAssetRecording* InLiveLinkRecording)`
- L185 _public function_ `~FLiveLinkStreamAsyncTask()`
- L194 _public function_ `TStatId GetStatId() const`
- L199 _public prototype_ `void DoWork();`
- L202 _private member_ `TObjectPtr<ULiveLinkUAssetRecording> LiveLinkRecording;`

#### Free symbols / members of external scopes

- L88 _delegate_ `DECLARE_DELEGATE(FOnRecordingInitialLoad);`
- L92 _delegate_ `DECLARE_DELEGATE(FOnRecordingFullyLoaded);`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/Implementations/LiveLinkUAssetRecordingPlayer.h` (Private)


#### struct `FLiveLinkPlaybackTrack`  
`struct FLiveLinkPlaybackTrack`  
_L10-65_
- desc: Playback track that holds recorded data for a given subject.
- L13 _public prototype_ `void GetFramesUntil(const FQualifiedFrameTime& InFrameTime, TArray<FLiveLinkRecordedFrame>& OutFrames);` — Retrieve all frames from the last read index to the new frame time, forward-looking.
- L16 _public prototype_ `void GetFramesUntilReverse(const FQualifiedFrameTime& InFrameTime, TArray<FLiveLinkRecordedFrame>& OutFrames);` — Retrieve all frames from the last read index to the new frame time, reverse-looking.
- L19 _public prototype_ `bool TryGetFrame(const FQualifiedFrameTime& InFrameTime, FLiveLinkRecordedFrame& OutFrame);` — Retrieve the frame at the read index.
- L26 _public prototype_ `int32 ConvertFrameTimeToFrameIndex(const FQualifiedFrameTime& InFrameTime);` — Given a frame time, find the closest index with a matching timestamp without going over. @param InFrameTime The frame time to convert to a frame index. @return The frame index or INDEX_NONE
- L29 _public function_ `void Restart(int32 NewIndex = INDEX_NONE)` — Reset the LastReadIndex.
- L36 _public function_ `int32 GetRelativeIndex(int32 InAbsoluteIndex) const` — Convert an absolute frame index to a relative frame index.
- L44 _public member_ `TArray<TSharedPtr<FInstancedStruct>> FrameData;` — Frame data to read.
- L46 _public member_ `TConstArrayView<double> Timestamps;` — Timestamps for the frames in the track.
- L48 _public member_ `TSubclassOf<ULiveLinkRole> LiveLinkRole;` — Used for static data.
- L50 _public member_ `FLiveLinkSubjectKey SubjectKey;` — Subject key.
- L52 _public member_ `int32 LastReadRelativeIndex = -1;` — Index of the last relative frame that was read by the GetFrames method.
- L54 _public member_ `int32 LastReadAbsoluteIndex = -1;` — Index of the last absolute frame that was read by the GetFrames method.
- L56 _public member_ `int32 StartIndexOffset = 0;` — The true index FrameData starts at. IE, if it starts at 5, then there are 5 prior frames [0..4] that aren't loaded.
- L58 _public member_ `FFrameRate LocalFrameRate = FFrameRate(0, 0);` — The frame rate of this track. Based only on the total frames and the final timestamp.
- L62 _private member_ `double LastTimeStamp = -1.f;` — The last timestamp recorded.

#### struct `FLiveLinkPlaybackTracks`  
`struct FLiveLinkPlaybackTracks`  
_L68-88_
- desc: Reorganized recording data to facilitate playback.
- L71 _public prototype_ `TArray<FLiveLinkRecordedFrame> FetchNextFrames(const FQualifiedFrameTime& InFrameTime);` — Get the next frames
- L74 _public prototype_ `TArray<FLiveLinkRecordedFrame> FetchPreviousFrames(const FQualifiedFrameTime& InFrameTime);` — Get the previous frames as if going in reverse
- L77 _public prototype_ `TArray<FLiveLinkRecordedFrame> FetchNextFramesAtIndex(const FQualifiedFrameTime& InFrameTime);` — Get the next frame(s) at the index
- L80 _public prototype_ `void Restart(int32 InIndex);` — Restart all tracks.
- L83 _public prototype_ `FFrameRate GetInitialFrameRate() const;` — Retrieve the framerate of the first frame
- L87 _public member_ `TMap<FLiveLinkSubjectKey, FLiveLinkPlaybackTrack> Tracks;` — LiveLink tracks to playback.

#### class `FLiveLinkUAssetRecordingPlayer`  
`class FLiveLinkUAssetRecordingPlayer : public ILiveLinkRecordingPlayer`  
_L90-152_
- inherits: `ILiveLinkRecordingPlayer`
- L93 _public prototype_ `virtual bool PreparePlayback(class ULiveLinkRecording* CurrentRecording) override;`
- L95 _public prototype_ `virtual void ShutdownPlayback() override;`
- L97 _public function_ `virtual TArray<FLiveLinkRecordedFrame> FetchNextFramesAtTimestamp(const FQualifiedFrameTime& InFrameTime) override`
- L106 _public function_ `virtual TArray<FLiveLinkRecordedFrame> FetchPreviousFramesAtTimestamp(const FQualifiedFrameTime& InFrameTime) override`
- L115 _public function_ `virtual TArray<FLiveLinkRecordedFrame> FetchNextFramesAtIndex(const FQualifiedFrameTime& InFrameTime) override`
- L124 _public function_ `virtual void RestartPlayback(int32 InIndex) override`
- L129 _public function_ `virtual FFrameRate GetInitialFramerate() override`
- L134 _public function_ `virtual UE::LiveLinkHub::RangeHelpers::Private::TRangeArray<int32> GetBufferedFrameRanges() override`
- L141 _private prototype_ `bool StreamPlayback(int32 InFromFrame);` — Buffer playback around a given frame.
- L144 _private prototype_ `int32 GetNumFramesToBuffer() const;` — Retrieve the total frames to buffer, based on the size the user specified in the config file.
- L148 _private member_ `FLiveLinkPlaybackTracks CurrentRecordingPlayback;` — All tracks for the current recording.
- L151 _private member_ `TWeakObjectPtr<ULiveLinkUAssetRecording> LoadedRecording;` — The recording currently loaded.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/LiveLinkHubPlaybackController.h` (Private)


#### class `FLiveLinkHubPlaybackController`  
`class FLiveLinkHubPlaybackController : public FRunnable`  
_L28-322_
- inherits: `FRunnable`
- L31 _public prototype_ `FLiveLinkHubPlaybackController();`
- L35 _public prototype_ `TSharedRef<SWidget> GetPlaybackWidget();` — Get the playback widget and create it if it doesn't exists.
- L38 _public prototype_ `void PreparePlayback(ULiveLinkRecording* InLiveLinkRecording);` — Apply the recording's preset then prepare the data needed to playback.
- L41 _public prototype_ `void PlayRecording(ULiveLinkRecording* InLiveLinkRecording);` — Start playing a livelink recording.
- L44 _public function_ `const TStrongObjectPtr<ULiveLinkRecording>& GetRecording() const` — The current recording.
- L47 _public prototype_ `void BeginPlayback(bool bInReverse);` — Start playing the currently prepared recording.
- L50 _public prototype_ `void RestartPlayback();` — Prepare to restart the playback.
- L53 _public prototype_ `void PausePlayback();` — Pause playback.
- L56 _public prototype_ `void StopPlayback();` — Stop playing a livelink recording.
- L59 _public prototype_ `void Eject(TFunction<void()> CompletionCallback = nullptr);` — Stop playback and restore the previous settings.
- L66 _public prototype_ `void EjectAndUnload(const TFunction<void()>& EjectCompletionCallback = nullptr, const ULiveLinkRecording* InRecording = nullptr, bool bClosePlaybackTab = true);` — Eject this recording and make sure it is unloaded. @param EjectCompletionCallback Callback after ejection occurs. @param InRecording The specific recording to eject and unload. If null, the RecordingToPlay is used.
- L79 _public prototype_ `void UnloadRecordingPackage(const TWeakObjectPtr<UPackage>& InPackage, bool bUnloadNextTick = false);` — Completely unload a recording package. Optionally allow the package to be unloaded on the next tick. This is to help with ensuring the package is fully unloaded, such as if the unload was requested during a multistep operation, like renaming the asset. When the asset is saved, the bulk data file archive is lost, and a reload is needed to reattach it. @param InPackage The package of the recording. @param bUnloadNextTick Whether the package should unload on the next tick or now.
- L82 _public prototype_ `void OnSelectRecording();` — Create a pop up window that shows available recordings to play.
- L85 _public prototype_ `void GoToTime(FQualifiedFrameTime InTime);` — Go to a specific time.
- L88 _public prototype_ `FQualifiedFrameTime GetSelectionStartTime() const;` — Retrieve the selection start time.
- L91 _public prototype_ `void SetSelectionStartTime(FQualifiedFrameTime InTime);` — Set the selection start time.
- L94 _public prototype_ `FQualifiedFrameTime GetSelectionEndTime() const;` — Retrieve the selection end time.
- L97 _public prototype_ `void SetSelectionEndTime(FQualifiedFrameTime InTime);` — Set the selection end time.
- L100 _public prototype_ `FQualifiedFrameTime GetLength() const;` — Retrieve the length of the recording.
- L103 _public prototype_ `FQualifiedFrameTime GetCurrentTime() const;` — Retrieve the playhead.
- L106 _public prototype_ `FFrameNumber GetCurrentFrame() const;` — Retrieve the current frame of the animation.
- L109 _public prototype_ `FFrameRate GetFrameRate() const;` — Retrieve the current framerate.
- L112 _public prototype_ `UE::LiveLinkHub::RangeHelpers::Private::TRangeArray<int32> GetBufferedFrameRanges() const;` — Retrieve buffered frame range.
- L115 _public function_ `bool IsReady() const` — If the controller is ready for commands.
- L121 _public function_ `bool IsInPlayback() const` — If a recording is loaded into the controller.
- L127 _public function_ `bool IsPlaying() const` — Returns whether we've started or are actively playing a recording.
- L133 _public function_ `bool IsPaused() const` — If playback is paused.
- L139 _public function_ `bool IsPlayingInReverse() const` — If playback is playing in reverse.
- L145 _public function_ `bool IsLooping() const` — Returns whether the recording is set to loop.
- L151 _public function_ `void SetLooping(bool bInLoop)` — Set whether a recording should loop.
- L157 _public function_ `void SetPlayRate(float InPlayRate)` — Sets the play rate (time dilation multiplier) of playback.
- L169 _public prototype_ `FString GetRecordingName() const;` — Retrieve the current recording's name.
- L172 _public function_ `FTSSimpleMulticastDelegate& OnPlaybackFinished()` — Delegate called when playback is finished (if recording is not set to loop).
- L178 _public function_ `FTSSimpleMulticastDelegate& OnPlaybackReady()` — Delegate called when recording playback is ready.
- L184 _public function_ `void SetClosePlaybackTabOnEject(bool bCloseOnEject)` — Set whether the playback tab should be closed when the eject button is pressed.
- L190 _public prototype_ `void Start();` — Create the playback thread.
- L193 _public function_ `virtual bool Init() override`
- L194 _public prototype_ `virtual uint32 Run() override;`
- L195 _public prototype_ `virtual void Stop() override;`
- L196 _public function_ `virtual void Exit() override`
- L201 _private prototype_ `void StartPlayback();` — Trigger the playback thread to start reading data.
- L203 _private prototype_ `void ResumePlayback();` — Resume on the playback thread.
- L206 _private prototype_ `void OnPlaybackFinished_Internal();` — Handler called when playback is finished on the playback thread. Is responsible for resetting the livelink state to what it was before we started playback.
- L213 _private prototype_ `void PushSubjectData(const FLiveLinkRecordedFrame& NextFrame, bool bForceSync = false);` — Send data to the client. @param NextFrame The frame to push. @param bForceSync Force the client to sync directly to this frame, discarding all other frames.
- L220 _private prototype_ `bool SyncToPlayhead();` — Sync the animation to the current playhead value. @return true if any frames were pushed.
- L223 _private prototype_ `bool SyncToFrame(const FQualifiedFrameTime& InFrameTime);` — Force sync to a specific frame.
- L226 _private prototype_ `bool ShouldRestart() const;` — Checks if the current playback settings indicates the recording should restart.
- L229 _private prototype_ `void OnResumePlayback();` — Handles the user clicking the play button to resume playback.
- L232 _private prototype_ `void OnPausePlayback();` — Handles the user clicking the pause button to resume playback.
- L235 _private prototype_ `void OnScrubbingStart();` — Handles pausing the recording while we're scrubbing.
- L238 _private prototype_ `void OnScrubbingEnd();` — Handles resuming the recording when we end scrubbing.
- L241 _private prototype_ `TArray<FLiveLinkSubjectKey> GetPlaybackSubjects() const;` — Get all playback subjects.
- L244 _private prototype_ `void PausePlaybackSubjects() const;` — Pauses all playback subjects.
- L247 _private prototype_ `void UnpausePlaybackSubjects() const;` — Unpauses all playback subjects.
- L251 _private member_ `TWeakPtr<SWidget> PlaybackWidget;` — Cached pointer to the playback widget.
- L253 _private member_ `bool bIsReady = false;` — If the system has established a connection with the client.
- L255 _private member_ `std::atomic<bool> Stopping = false;` — Flag for terminating the thread loop
- L257 _private member_ `TUniquePtr<FRunnableThread> Thread;` — Thread to do playback on
- L259 _private member_ `FEventRef PlaybackEvent = FEventRef();` — Event signaling that a recording is available for playback.
- L261 _private member_ `std::atomic<bool> bIsPlaybackWaiting = false;` — If the playback thread is waiting.
- L263 _private member_ `std::atomic<bool> bIsPlaying = false;` — Whether a recording is playing.
- L265 _private member_ `std::atomic<bool> bIsStopping = false;` — Stop requested.
- L267 _private member_ `std::atomic<bool> bIsPaused = false;` — Whether we're currently paused.
- L269 _private member_ `std::atomic<bool> bIsReverse = false;` — If the recording is playing in reverse.
- L271 _private member_ `std::atomic<bool> bIsDestructing = false;` — If the controller is destructing.
- L273 _private member_ `std::atomic<double> StartTimestamp = 0.f;` — The timestamp of the animation when first playing. Can be > 0 when running in reverse.
- L275 _private member_ `bool bIsPreparingPlayback = false;` — Indicates that we're in the process of preparing the playback. Used by the OnSourceRemoved callback to make sure we don't eject during the PreparePlayback step.
- L277 _private member_ `TStrongObjectPtr<ULiveLinkRecording> RecordingToPlay;` — LiveLinkRecording to play.
- L279 _private member_ `FTSSimpleMulticastDelegate PlaybackFinishedDelegate;` — Delegate called when a recording playback is finished (if it's not looping).
- L281 _private member_ `FTSSimpleMulticastDelegate PlaybackReadyDelegate;` — Delegate called when recording playback is ready.
- L283 _private member_ `TStrongObjectPtr<ULiveLinkPreset> RollbackPreset;` — Preset used to rollback the hub to its previous state after playing a recording.
- L285 _private member_ `std::atomic<bool> bLoopPlayback = true;` — Atomic bool keeping track of whether we should loop the playback.
- L287 _private member_ `TUniquePtr<ILiveLinkRecordingPlayer> RecordingPlayer;` — Implementation of the playback functionality.
- L290 _private member_ `ILiveLinkClient* Client = nullptr;` — LiveLinkClient used to transmit the data to connected clients.
- L292 _private member_ `double PlaybackStartTime = 0.0;` — Time that the playback started.
- L293 _private member_ `double TimeDilationAdjustedCurrentTime = 0.0;`
- L294 _private member_ `std::atomic<float> PlayRate = 1;`
- L297 _private member_ `TSharedPtr<FLiveLinkHubAtomicQualifiedFrameTime, ESPMode::ThreadSafe> Playhead;` — Playhead for the current playback.
- L300 _private member_ `TRange<double> SliderViewRange = TRange<double>(0.f, 0.f);` — The view range of the slider, defaults to start/end time.
- L303 _private member_ `FQualifiedFrameTime SelectionStartTime;` — The playback selection start time.
- L306 _private member_ `FQualifiedFrameTime SelectionEndTime;` — The playback selection end time.
- L309 _private member_ `TSet<TWeakObjectPtr<UPackage>> PackagesUnloading;` — Packages in the process of unloading.
- L312 _private member_ `TMap<FLiveLinkSubjectKey, int32> LastStaticFrameIndex;` — The last sent static frame index. Used to ensure we only send static data when necessary.
- L315 _private member_ `TSharedPtr<class SWindow> RecordingPickerWindow;` — Window that displays the list of recordings that can be played back.
- L318 _private member_ `bool bStartedScrubbingPaused = false;` — Keeps track of whether the recording was paused when starting to scrub to ensure we don't pause if we scrub while playing.
- L321 _private member_ `bool bClosePlaybackTabOnEject = false;` — Whether to close the playback tab when ejecting a recording.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/LiveLinkHubPlaybackSourceFactory.h` (Private)


#### class `ULiveLinkHubPlaybackSourceFactory`  
`class ULiveLinkHubPlaybackSourceFactory : public ULiveLinkSourceFactory`  
_L16-42_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceFactory`
- desc: Factory used to create playback sources when we're playing back a livelink recording.
- L22 _public function_ `virtual FText GetSourceDisplayName() const override`
- L27 _public function_ `virtual FText GetSourceTooltip() const`
- L32 _public function_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const`
- L37 _public function_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FLiveLinkSourcePreset& SourcePreset)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkHubPlaybackSourceFactory"`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/LiveLinkHubPlaybackSourceSettings.h` (Private)


#### class `ULiveLinkHubPlaybackSourceSettings`  
`class ULiveLinkHubPlaybackSourceSettings : public ULiveLinkSourceSettings`  
_L11-19_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceSettings`
- desc: Settings class for playback sources, which provides the factory class for them.
- L16 _public prototype_ `ULiveLinkHubPlaybackSourceSettings();`
- L18 _public prototype_ `virtual FText GetSourceNameOverride(class ULiveLinkSubjectSettings* SubjectSettings, FText SourceType) override;`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/LiveLinkHubRecordingController.h` (Private)


#### class `FLiveLinkHubRecordingController`  
`class FLiveLinkHubRecordingController`  
_L14-54_
- L17 _public prototype_ `FLiveLinkHubRecordingController();`
- L20 _public prototype_ `TSharedRef<SWidget> MakeRecordToolbarEntry();` — Create the toolbar entry for starting/stopping recordings.
- L23 _public prototype_ `void StartRecording();` — Start recording livelink data.
- L26 _public prototype_ `void StopRecording();` — Stop recording livelink data and prompt the user for a save location.
- L29 _public prototype_ `bool IsRecording() const;` — Returns whether we're currently recording.
- L32 _public prototype_ `bool CanRecord() const;` — Returns whether we can begin recording.
- L35 _public prototype_ `FText GetRecordingButtonTooltip() const;` — The tool tip to display on the recording button.
- L38 _public prototype_ `void RecordStaticData(const FLiveLinkSubjectKey& SubjectKey, TSubclassOf<class ULiveLinkRole> Role, const FLiveLinkStaticDataStruct& StaticData);` — Record static data in the current recording.
- L41 _public prototype_ `void RecordFrameData(const FLiveLinkSubjectKey& SubjectKey, const FLiveLinkFrameDataStruct& FrameData);` — Record frame data in the current recording.
- L44 _public prototype_ `void RecordFromExistingAndSave(ULiveLinkRecording* InRecording, const FString& InFilePath, bool bUpgradeInPlace = false);` — Record from an existing recording.
- L47 _public prototype_ `bool OpenSaveAsPrompt(FString& OutName, const FString& InInitialName) const;` — Open a save as window and retrieve a file path.
- L50 _private member_ `TSharedPtr<ILiveLinkRecorder> RecorderImplementation;` — Recorder used to serialize livelink data into a given format.
- L53 _private member_ `mutable FText ErrorMessage;` — Any error text associated with the recording, for display on the recording button tooltip.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/LiveLinkHubRecordingListController.h` (Private)


#### class `FLiveLinkHubRecordingListController`  
`class FLiveLinkHubRecordingListController`  
_L21-140_
- L24 _public function_ `FLiveLinkHubRecordingListController(const TSharedRef<FLiveLinkHub>& InLiveLinkHub) : LiveLinkHub(InLiveLinkHub)`
- L48 _public function_ `~FLiveLinkHubRecordingListController()`
- L64 _public function_ `TSharedRef<SWidget> MakeRecordingList()` — Create the list's widget.
- L72 _private function_ `void OnImportRecording(const FAssetData& AssetData)` — Handler called when a recording is clicked which will start the recording.
- L102 _private function_ `void OnContentDirectoryChanged(const TArray<struct FFileChangeData>& FileChangeData)` — Reacts to changes in the content directory to rescan it to update the recording list.
- L132 _private member_ `TWeakPtr<FLiveLinkHub> LiveLinkHub;` — LiveLinkHub object that holds the different controllers.
- L134 _private member_ `FDelegateHandle DirectoryChangedHandle;` — Delegate handle for the RegisterDirectoryChangedCallback_Handle callback.
- L136 _private member_ `FString ContentDirectory;` — Path to the content directory. Used to react to changes to that directory, such as new files being added.
- L139 _private member_ `FTimerHandle DirectoryScanTimerHandle;` — Timer handle used for scanning directory changes.

#### Free symbols / members of external scopes

- L19 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkHub.RecordingList"`
- L105 _function_ `` (scope `FLiveLinkHubRecordingListController::OnContentDirectoryChanged`)
- L114 _function_ `Algo::Transform(FileChangeData, FilePaths, [](const FFileChangeData& Data) { return Data.Filename; });` (scope `FLiveLinkHubRecordingListController::OnContentDirectoryChanged::__anon6d88bf940102`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/LiveLinkHubRecordingMountManager.h` (Private)


#### class `FLiveLinkHubRecordingMountManager`  
`class FLiveLinkHubRecordingMountManager`  
_L12-81_
- desc: Manages custom mount points for LiveLink Hub recordings. Allows users to record to folders outside the default Content directory.
- L15 _public prototype_ `FLiveLinkHubRecordingMountManager();`
- L16 _public prototype_ `~FLiveLinkHubRecordingMountManager();`
- L25 _public prototype_ `bool MountCustomDirectory(const FString& InDirectoryPath, FString& OutMountPoint, FText& OutErrorText);` — Mount a custom directory for recordings. @param InDirectoryPath Absolute path to the directory to mount @param OutMountPoint The generated mount point path (e.g., /Game/LiveLinkRecordings_eeaf31) @param OutErrorText Error message if mounting fails @return true if mounting succeeded
- L32 _public prototype_ `bool UnmountCustomDirectory(FText& OutErrorText);` — Unmount the currently active custom directory. @param OutErrorText Error message if unmounting fails @return true if unmounting succeeded or no mount point was active
- L37 _public function_ `bool IsCustomDirectoryMounted() const` — Check if a custom directory is currently mounted.
- L43 _public function_ `const FString& GetMountPoint() const` — Get the current mount point path (e.g., /Game/LiveLinkRecordings_eeaf31). Empty if no custom directory is mounted.
- L49 _public function_ `const FString& GetMountedDirectory() const` — Get the current mounted directory absolute path. Empty if no custom directory is mounted.
- L58 _private prototype_ `bool ValidateDirectory(const FString& InDirectoryPath, FText& OutErrorText) const;` — Validate that a directory path is valid for mounting. @param InDirectoryPath Absolute path to validate @param OutErrorText Error message if validation fails @return true if valid
- L65 _private prototype_ `FString GenerateUniqueMountPoint(const FString& InDirectoryPath) const;` — Generate a unique mount point name that doesn't conflict with existing /Game paths. @param InDirectoryPath The directory being mounted (used for base name) @return Mount point path like /Game/LiveLinkRecordings_eeaf31
- L71 _private prototype_ `bool IsInsideProjectContent(const FString& InDirectoryPath) const;` — Check if the directory is inside FPaths::ProjectContentDir(). If true, no mounting is needed.
- L74 _private member_ `bool bIsMounted = false;` — Whether a custom directory is currently mounted
- L77 _private member_ `FString CurrentMountPoint;` — Current mount point (e.g., /Game/LiveLinkRecordings_eeaf31)
- L80 _private member_ `FString CurrentMountedDirectory;` — Current mounted directory absolute path

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/LiveLinkHubRecordingVersions.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace LiveLinkHub` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::LiveLinkHub`)
- L7 _namespace_ `namespace RecordingVersions` (scope `UE::LiveLinkHub::Private`)
- L9 _variable_ `constexpr int32 InitialVersion = 1;` (scope `UE::LiveLinkHub::Private::RecordingVersions`)
- L11 _variable_ `constexpr int32 DynamicFrameSizes = 2;` (scope `UE::LiveLinkHub::Private::RecordingVersions`) — Account for varying frame sizes and offsets.
- L13 _variable_ `constexpr int32 BulkTimestamps = 3;` (scope `UE::LiveLinkHub::Private::RecordingVersions`) — Timestamps serialized in bulk.
- L15 _variable_ `constexpr int32 CompressionSupport = 4;` (scope `UE::LiveLinkHub::Private::RecordingVersions`) — Added oodle compression to serialized frame data.
- L18 _variable_ `constexpr int32 Latest = CompressionSupport;` (scope `UE::LiveLinkHub::Private::RecordingVersions`) — The latest recording version. UPDATE IF ADDING NEW VERSIONS!

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/LiveLinkPlaybackSource.h` (Private)


#### class `FLiveLinkPlaybackSource`  
`class FLiveLinkPlaybackSource : public ILiveLinkSource`  
_L14-97_
- inherits: `ILiveLinkSource`
- desc: Completely empty "source" displayed in the UI when playing back a recording.
- L17 _public prototype_ `FLiveLinkPlaybackSource() = default;`
- L19 _public function_ `FLiveLinkPlaybackSource(const FString& OriginalSourceName)`
- L47 _public prototype_ `virtual ~FLiveLinkPlaybackSource() = default;`
- L50 _public function_ `virtual bool CanBeDisplayedInUI() const override`
- L55 _public function_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override`
- L59 _public function_ `virtual void InitializeSettings(ULiveLinkSourceSettings* Settings) override`
- L63 _public function_ `virtual bool IsSourceStillValid() const override`
- L68 _public function_ `virtual bool RequestSourceShutdown() override`
- L73 _public function_ `virtual FText GetSourceType() const override`
- L78 _public function_ `virtual FText GetSourceMachineName() const override`
- L83 _public function_ `virtual FText GetSourceStatus() const override`
- L88 _public function_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const`
- L96 _protected member_ `FName SourceName;` — Source name.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/LiveLinkRecorder.h` (Private)


#### class `ILiveLinkRecorder`  
`class ILiveLinkRecorder`  
_L12-33_
- desc: Interface for handling serialization of livelink data.
- L15 _public prototype_ `virtual ~ILiveLinkRecorder() = default;`
- L18 _public prototype_ `virtual void StartRecording() = 0;` — Start recording livelink data.
- L20 _public prototype_ `virtual void StopRecording() = 0;` — Stop recording livelink data and prompt the user for a save location.
- L22 _public prototype_ `virtual void RecordStaticData(const FLiveLinkSubjectKey& SubjectKey, TSubclassOf<ULiveLinkRole> Role, const FLiveLinkStaticDataStruct& StaticData) = 0;` — Record static data in the current recording.
- L24 _public prototype_ `virtual void RecordFrameData(const FLiveLinkSubjectKey& SubjectKey, const FLiveLinkFrameDataStruct& FrameData) = 0;` — Record frame data in the current recording.
- L26 _public prototype_ `virtual bool IsRecording() const = 0;` — Return whether we are currently recording livelink data.
- L28 _public prototype_ `virtual bool CanRecord(FText* OutErrorMessage = nullptr) const = 0;` — Returns whether we can begin recording.
- L30 _public prototype_ `virtual void SaveFromExistingRecording(ULiveLinkRecording* InRecording, const FString& InFilePath, bool bUpgradeInPlace) = 0;` — Directly provide the recording and save it.
- L32 _public prototype_ `virtual bool GetSavePresetPackageName(FString& OutName, const FString& InDefaultName, bool bAlwaysOpenSaveAsDialog = false) const = 0;` — Creates a unique asset name and prompts the user for the recording name.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/LiveLinkRecording.h` (Private)


#### class `ULiveLinkRecording`  
`class ULiveLinkRecording : public UObject`  
_L13-62_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- L18 _public function_ `ULiveLinkRecording()`
- L24 _public function_ `virtual bool IsFullyLoaded() const` — True if this asset has all data loaded.
- L27 _public function_ `virtual bool IsSavingRecordingData() const` — True while recording data is being written to bulk data.
- L30 _public function_ `virtual int32 GetMaxFrames() const` — Return the maximum frames for this recording.
- L33 _public function_ `virtual double GetLastTimestamp() const` — Return the last timestamp of the recording.
- L36 _public function_ `virtual FQualifiedFrameTime GetLastFrameTime() const` — Return the last frame time.
- L39 _public function_ `virtual FFrameRate GetGlobalFrameRate() const` — Retrieve the generalized framerate of this recording.
- L42 _public function_ `virtual void LoadEntireRecording()` — Load the entire recording into memory.
- L45 _public function_ `virtual bool IsLoadingEntireRecording() const` — If the entire recording is in the process of being loaded into memory.
- L49 _public member_ `TObjectPtr<ULiveLinkPreset> RecordingPreset = nullptr;` — `UPROPERTY(Instanced)` — LiveLink Preset used to save the initial state of the sources and subjects at the time of recording.
- L53 _public member_ `double LengthInSeconds = 0.0;` — `UPROPERTY()` — Length of the recording.
- L57 _public member_ `FFrameRate FrameRate;` — `UPROPERTY()` — The framerate of the recording.
- L61 _public member_ `int32 SavedRecordingVersion;` — `UPROPERTY(AssetRegistrySearchable)` — The saved version of this recording.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/LiveLinkRecordingPlayer.h` (Private)


#### struct `FLiveLinkRecordedFrame`  
`struct FLiveLinkRecordedFrame`  
_L14-24_
- desc: Frame that was read by the recording player
- L17 _public member_ `FConstStructView Data;` — Recorded frame or static data.
- L19 _public member_ `FLiveLinkSubjectKey SubjectKey;` — Subject that originally sent the data.
- L21 _public member_ `TSubclassOf<ULiveLinkRole> LiveLinkRole;` — Role used to interpret the data (Only present with recorded static data).
- L23 _public member_ `int32 FrameIndex;` — The frame index of this frame within a track.

#### class `ILiveLinkRecordingPlayer`  
`class ILiveLinkRecordingPlayer`  
_L27-55_
- desc: Object responsible for reading a livelink recording and providing the frames to the LiveLinkPlaybackController.
- L30 _public prototype_ `virtual ~ILiveLinkRecordingPlayer() = default;`
- L33 _public prototype_ `virtual bool PreparePlayback(ULiveLinkRecording* Recording) = 0;` — Initialize internal structures needed for playback of the recorded data.
- L36 _public prototype_ `virtual void ShutdownPlayback() = 0;` — Preform cleanup when exiting playback.
- L39 _public prototype_ `virtual TArray<FLiveLinkRecordedFrame> FetchNextFramesAtTimestamp(const FQualifiedFrameTime& InFrameTime) = 0;` — Fetch next frames at the provided playhead position.
- L42 _public prototype_ `virtual TArray<FLiveLinkRecordedFrame> FetchPreviousFramesAtTimestamp(const FQualifiedFrameTime& InFrameTime) = 0;` — Fetch previous frames at the provided playhead position.
- L45 _public prototype_ `virtual TArray<FLiveLinkRecordedFrame> FetchNextFramesAtIndex(const FQualifiedFrameTime& InFrameTime) = 0;` — Fetch next frames at the provided frame index.
- L48 _public prototype_ `virtual void RestartPlayback(int32 InIndex = INDEX_NONE) = 0;` — Restart the recording from the beginning.
- L51 _public prototype_ `virtual FFrameRate GetInitialFramerate() = 0;` — Retrieve the first frame's frame rate information.
- L54 _public prototype_ `virtual UE::LiveLinkHub::RangeHelpers::Private::TRangeArray<int32> GetBufferedFrameRanges() = 0;` — Retrieve the currently buffered frames.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/LiveLinkRecordingRangeHelpers.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace LiveLinkHub` (scope `UE`)
- L10 _namespace_ `namespace RangeHelpers` (scope `UE::LiveLinkHub`)
- L10 _namespace_ `namespace Private` (scope `UE::LiveLinkHub::RangeHelpers`)
- L14 _typedef_ `template<typename T> using TRangeArray = TArray<TRange<T>>;` (scope `UE::LiveLinkHub::RangeHelpers::Private`) — TArray<TRange<T>>
- L18 _function_ `template<typename T> T GetRangeLength(const TRange<T>& InRange)` (scope `UE::LiveLinkHub::RangeHelpers::Private`) — Gets the length of the range, accounting for exclusive or inclusive ranges.
- L32 _function_ `template<typename T> T GetRangeLength(const TRangeArray<T>& InRangeArray)` (scope `UE::LiveLinkHub::RangeHelpers::Private`) — Gets the length of the range array. Does not account for inclusive ranges.
- L55 _function_ `template<typename T> TRange<T> MakeInclusiveRange(const T InStart, const T InEnd)` (scope `UE::LiveLinkHub::RangeHelpers::Private`) — Makes an inclusive range.
- L62 _function_ `template<typename T> TRange<T> ConvertRangeFrameRate(const TRange<T>& InRange, const FFrameRate& InFromFrameRate, const FFrameRate& InToFrameRate)` (scope `UE::LiveLinkHub::RangeHelpers::Private`) — Convert a range from one frame rate to another.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/SLiveLinkHubRecordingListView.h` (Private)


#### class `SLiveLinkHubRecordingListView`  
`class SLiveLinkHubRecordingListView : public SCompoundWidget`  
_L38-852_
- inherits: `SCompoundWidget`
- L41 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnImportRecording, const struct FAssetData&);`
- L43 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkHubRecordingListView)`
- L45 _public function_ `SLATE_EVENT(FOnImportRecording, OnImportRecording) SLATE_END_ARGS() SLiveLinkHubRecordingListView()`
- L55 _public function_ `virtual ~SLiveLinkHubRecordingListView() override`
- L72 _public function_ `void Construct(const FArguments& InArgs)`
- L188 _private function_ `void OnImportRecording(const FAssetData& AssetData) const` — Callback to notice the hub that we've selected a recording to play.
- L194 _private function_ `void OnAssetAdded(const FAssetData& InAssetData)` — When an asset is added to the asset registry.
- L210 _private function_ `void OnAssetRemoved(const FAssetData& InAssetData)` — When an asset is removed from the asset registry.
- L221 _private function_ `EVisibility GetRecordingPickerVisibility() const` — The visibility status of the recording picker.
- L243 _private function_ `TArray<FAssetViewCustomColumn> GetCustomColumns() const`
- L316 _private function_ `TSharedRef<SWidget> CreateRecordingPicker(TOptional<FAssetData> AssetData = {})` — Creates the asset picker widget for selecting a recording.
- L373 _private function_ `FARFilter MakeAssetFilter() const` — Create a filter for available recording assets.
- L385 _private function_ `bool ShouldFilterAsset(const FAssetData& AssetData) const` — Filter out assets not directly in the current mount point (excludes subfolders).
- L392 _private function_ `TSharedPtr<SWidget> GetAssetContextMenu(const TArray<FAssetData>& SelectedAssets)`
- L619 _private function_ `static FText GetNoAssetsWarningText()` — The text to display when no assets are found.
- L625 _private function_ `FString GetRecordingMountPoint() const` — Get the current recording mount point (custom or default /Game)
- L649 _private function_ `FString GetCustomRecordingDirectory() const` — Get the user-selected custom recording directory (absolute filesystem path). SessionData is the source of truth: it covers both the registered-mount case and the content-subdirectory case (where the mount manager doesn't register a mount point).
- L669 _private function_ `FText GetCurrentRecordingPath() const` — Get the current recording directory as text for display
- L682 _private function_ `bool IsCustomFolderActive() const` — Check if a custom folder is currently active
- L688 _private function_ `bool CanChangeMountPoint() const` — Check if the mount point can be changed (not during playback or recording)
- L709 _private function_ `bool CanResetMountPoint() const` — Check if the mount point can be reset (custom folder active and not during playback or recording)
- L715 _private function_ `FReply OnChooseRecordingFolder()` — Choose a custom recording folder
- L769 _private function_ `FReply OnResetRecordingFolder()` — Reset to default recording folder
- L811 _private function_ `FReply OnOpenRecordingsFolder()` — Open the current recordings folder in explorer
- L826 _private function_ `FReply OnRefreshRecordings()` — Refresh recordings by rescanning the current mount point
- L837 _private member_ `FOnImportRecording OnImportRecordingDelegate;` — Delegate used for noticing the hub that a recording was selected for playback.
- L839 _private member_ `TSharedPtr<SWidget> AssetPicker;` — The asset picker used for selecting recordings.
- L841 _private member_ `FDelegateHandle OnAssetAddedHandle;` — Handle for when an asset is added to the asset registry.
- L843 _private member_ `FDelegateHandle OnAssetRemovedHandle;` — Handle for when an asset is removed from the asset registry.
- L845 _private member_ `TSharedPtr<SBox> BoxWidget;` — Box widget used to hold the asset picker.
- L847 _private member_ `FTimerHandle TimerHandle;` — Timer handle used for triggering a rename after duplicating a recording.
- L849 _private member_ `FRefreshAssetViewDelegate RefreshAssetViewDelegate;` — Delegate used to refresh the asset view.
- L851 _private member_ `mutable TOptional<bool> bAssetsAvailableCached;` — True if there are recording assets that exist.

#### Free symbols / members of external scopes

- L36 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkHub.RecordingListView"`
- L41 _delegate_ `DECLARE_DELEGATE_OneParam(FOnImportRecording, const struct FAssetData&);`
- L112 _function_ `.WidgetIndex_Lambda([this]() { return GetRecordingPickerVisibility() == EVisibility::Visible ? 0 : 1; }) + SWidgetSwitcher::Slot() .VAlign(VAlign_Fill) [ SAssignNew(BoxWidget, SBox) [ CreateRecordingPicker() ] ] + SWidgetSwitcher::Slot() .VAlign(VAlign_Center) .HAlign(HAlign_Center) [ SNew(SVerticalBox) + SVerticalBox::Slot() .HAlign(HAlign_Center) .AutoHeight() [ SNew(STextBlock) .Text(GetNoAssetsWarningText()) ] + SVerticalBox::Slot() .Padding(FMargin(4, 4)) .HAlign(HAlign_Center) .AutoHeight() [ SNew(SHorizontalBox) + SHorizontalBox::Slot() .Padding(FMargin(4.0, 2.0)) .AutoWidth() [ SNew(SButton) .Text(LOCTEXT("RecordingsFolderButton", "Open Recordings Folder")) .OnClicked(this, &SLiveLinkHubRecordingListView::OnOpenRecordingsFolder) ] + SHorizontalBox::Slot() .Padding(FMargin(4.0, 2.0)) .AutoWidth() [ SNew(SButton)` (scope `SLiveLinkHubRecordingListView::Construct`)
- L233 _function_ `` (scope `SLiveLinkHubRecordingListView::GetRecordingPickerVisibility`)
- L253 _function_ `` (scope `SLiveLinkHubRecordingListView::GetCustomColumns`)
- L417 _function_ `` (scope `SLiveLinkHubRecordingListView::GetAssetContextMenu`)
- L424 _function_ `}), FCanExecuteAction::CreateLambda([] ()` (scope `SLiveLinkHubRecordingListView::GetAssetContextMenu`)
- L449 _function_ `` (scope `SLiveLinkHubRecordingListView::GetAssetContextMenu::__anon40c821fe0b02`)
- L502 _function_ `` (scope `SLiveLinkHubRecordingListView::GetAssetContextMenu::__anon40c821fe0e02`)
- L536 _function_ `}), FCanExecuteAction::CreateLambda([SelectedAssetObject] ()` (scope `SLiveLinkHubRecordingListView::GetAssetContextMenu`)
- L578 _function_ `` (scope `SLiveLinkHubRecordingListView::GetAssetContextMenu::__anon40c821fe1502`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Recording/SLiveLinkHubRecordingView.h` (Private)


#### class `SLiveLinkHubRecordingView`  
`class SLiveLinkHubRecordingView : public SCompoundWidget`  
_L27-122_
- inherits: `SCompoundWidget`
- desc: Utility base class for all content that is displayed in an entire major tab.
- L30 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FSimplePredicate);`
- L32 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkHubRecordingView)`
- L33 _public function_ `SLATE_EVENT(FSimplePredicate, CanRecord) SLATE_EVENT(FSimplePredicate, IsRecording) SLATE_EVENT(FSimpleDelegate, OnStartRecording) SLATE_EVENT(FSimpleDelegate, OnStopRecording) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L80 _public function_ `FText GetRecordingText() const` — Get the text shown in the Record button in the toolbar.
- L88 _public function_ `FReply OnClickRecordButton()` — Handler called when record button is clicked
- L103 _public function_ `bool IsRecording() const` — Returns whether we're currently recording.
- L108 _public function_ `bool CanRecord() const`
- L115 _private member_ `FSimplePredicate CanRecordDelegate;` — Delegate used to know if the hub can begin recording.
- L117 _private member_ `FSimplePredicate IsRecordingDelegate;` — Delegate used to know if the hub is currently recording.
- L119 _private member_ `FSimpleDelegate OnStartRecordingDelegate;` — Delegate used to notice the hub that we should start recording.
- L121 _private member_ `FSimpleDelegate OnStopRecordingDelegate;` — Delegate used to notice the hub that we should stop recording.

#### Free symbols / members of external scopes

- L21 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkHub.RecordingView"`
- L30 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FSimplePredicate);`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Session/LiveLinkHubAutosaveHandler.h` (Private)


#### class `FLiveLinkHubAutosaveHandler`  
`class FLiveLinkHubAutosaveHandler`  
_L14-137_
- desc: Utility class to trigger autosaves periodically.
- L17 _public member_ `inline static const FString AutosaveFileExtension = TEXT(".au`
- L19 _public function_ `FLiveLinkHubAutosaveHandler()`
- L27 _public function_ `~FLiveLinkHubAutosaveHandler()`
- L40 _public function_ `void Autosave()` — Forcefully perform autosave.
- L79 _public function_ `void RestoreAutosave(const FString& File)` — Restore an autosave based on a file path.
- L85 _public function_ `TArray<FLiveLinkHubSessionFile> GetAutosaveFiles() const` — Get the list of autosave files, sorted from most recent to oldest.
- L101 _private function_ `void AttemptAutosave()` — Attempts to save the current session if enough time has passed since the last one.
- L113 _private function_ `void OnActiveSessionChanged(const TSharedRef<ILiveLinkHubSession>&)` — Trigger an autosave when we change session.
- L119 _private function_ `void OnBeginFrame_GameThread()` — Game thread tick used to check if we need to autosave.
- L125 _private function_ `void OnApplicationWillTerminate()` — Try to do a last autosave when the app crashes.
- L132 _private member_ `const FString AutosaveDirectory = FPaths::Combine(FPlatformProcess::UserSettingsDir(), *FApp::GetEpicProductIdentifier(), TEXT("LiveLinkHub"),` — Base directory for autosave files.
- L134 _private member_ `FString FileName = FDateTime::Now().ToString() + AutosaveFileExtension;` — Filename for auto-saves, based on the time the hub was opened.
- L136 _private member_ `double LastAutosaveTimestamp = FPlatformTime::Seconds();` — Timestamp of the last auto-save.

#### Free symbols / members of external scopes

- L92 _function_ `Algo::Transform(Files, Autosaves, [this](const FString& InFile) { return FLiveLinkHubSessionFile{ FPaths::Combine(AutosaveDirectory, InFile) }; });` (scope `FLiveLinkHubAutosaveHandler::GetAutosaveFiles`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Session/LiveLinkHubSession.h` (Private)


#### struct `FLiveLinkHubSessionFile`  
`struct FLiveLinkHubSessionFile`  
_L32-51_
- L35 _public member_ `FString FileName;` — Session name.
- L37 _public member_ `FString FilePath;` — Full file path to this config file.
- L39 _public member_ `FDateTime LastModificationDate;` — When the file was last modified.
- L41 _public member_ `bool bWasAutosaved = false;` — Whether this is an autosave.
- L43 _public function_ `FLiveLinkHubSessionFile(const FString& InFile) : FileName(FPaths::GetBaseFilename(InFile)) , FilePath(InFile) , LastModificationDate(IFileManager::Get().GetTimeStamp(*InFile))`

#### class `ILiveLinkHubSession`  
`class ILiveLinkHubSession`  
_L56-87_
- desc: Holds the state of the hub for an active session, can be swapped out with a different session using the session manager.
- L59 _public prototype_ `virtual ~ILiveLinkHubSession() = default;`
- L62 _public prototype_ `virtual void AddClient(const FLiveLinkHubClientId& Client) = 0;` — Add a client to this session. Note: Must be called from game thread.
- L65 _public prototype_ `virtual void RemoveClient(const FLiveLinkHubClientId& Client) = 0;` — Remove a client from this session. Note: Must be called from game thread.
- L68 _public prototype_ `virtual void RemoveAllClients() = 0;` — Remove all clients from this session. Note: Must be called from game thread.
- L71 _public prototype_ `virtual bool IsClientInSession(const FLiveLinkHubClientId& Client) const = 0;` — Returns whether a client is in this session.
- L74 _public prototype_ `virtual TArray<FLiveLinkHubClientId> GetSessionClients() const = 0;` — Get the list of clients in this session (The list of clients that can receive data from the hub)
- L77 _public prototype_ `virtual ELiveLinkTopologyMode GetTopologyMode() const = 0;` — Get the topology mode for this instance.
- L80 _public prototype_ `virtual void SetTopologyMode(ELiveLinkTopologyMode Mode) = 0;` — Set the topology mode for this instance.
- L83 _public prototype_ `virtual bool ShouldTransmitToClient(const FLiveLinkHubClientId& Client, FLiveLinkSubjectName Subject = FLiveLinkSubjectName{}) const = 0;` — Returns whether the session config allows sending data to this client, and optionally to a specific subject.
- L86 _public prototype_ `virtual ULiveLinkHubSessionData* GetSessionData() const = 0;` — Get the session data object.

#### class `FLiveLinkHubSession`  
`class FLiveLinkHubSession : public ILiveLinkHubSession, public TSharedFromThis<FLiveLinkHubSession>`  
_L89-295_
- inherits: `ILiveLinkHubSession,TSharedFromThis<FLiveLinkHubSession>`
- L92 _public function_ `FLiveLinkHubSession(FOnClientAddedToSession& OnClientAddedToSession, FOnClientRemovedFromSession& OnClientRemovedFromSession) : OnClientAddedToSessionDelegate(OnClientAddedToSession) , OnClientRemovedFromSessionDelegate(OnClientRemovedFromSession)`
- L99 _public function_ `FLiveLinkHubSession(ULiveLinkHubSessionData* InSessionData, FOnClientAddedToSession& OnClientAddedToSession, FOnClientRemovedFromSession& OnClientRemovedFromSession) : OnClientAddedToSessionDelegate(OnClientAddedToSession) , OnClientRemovedFromSessionDelegate(OnClientRemovedFromSession)`
- L106 _public function_ `virtual TArray<FLiveLinkHubClientId> GetSessionClients() const override`
- L112 _public function_ `virtual void AddClient(const FLiveLinkHubClientId& Client) override`
- L142 _public function_ `virtual void RemoveClient(const FLiveLinkHubClientId& Client) override`
- L161 _public function_ `virtual void RemoveAllClients() override`
- L209 _public function_ `virtual bool IsClientInSession(const FLiveLinkHubClientId& Client) const override`
- L215 _public function_ `virtual ELiveLinkTopologyMode GetTopologyMode() const override`
- L221 _public function_ `virtual void SetTopologyMode(ELiveLinkTopologyMode Mode) override`
- L236 _public function_ `virtual bool ShouldTransmitToClient(const FLiveLinkHubClientId& Client, FLiveLinkSubjectName Subject = FLiveLinkSubjectName{}) const override`
- L257 _public function_ `virtual ULiveLinkHubSessionData* GetSessionData() const override`
- L263 _public function_ `void AddRestoredClient(FLiveLinkHubUEClientInfo& InOutRestoredClientInfo)`
- L280 _private member_ `TSet<FLiveLinkHubClientId> CachedSessionClients;` — List of clients in the current session. These represent the unreal instances than can receive data from the hub.
- L283 _private member_ `TStrongObjectPtr<ULiveLinkHubSessionData> SessionData;` — Holds data for this session.
- L286 _private member_ `FOnClientAddedToSession& OnClientAddedToSessionDelegate;` — Delegate used to notice the hub about clients being added to this session.
- L289 _private member_ `FOnClientRemovedFromSession& OnClientRemovedFromSessionDelegate;` — Delegate used to notice the hub about clients being removed from this session.
- L292 _private member_ `mutable FRWLock SessionDataLock;` — Lock used to access the client config from different threads.

#### Free symbols / members of external scopes

- L26 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkHubSession"`
- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClientAddedToSession, FLiveLinkHubClientId);`
- L28 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClientAddedToSession, FLiveLinkHubClientId);`
- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClientRemovedFromSession, FLiveLinkHubClientId);`
- L29 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClientRemovedFromSession, FLiveLinkHubClientId);`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Session/LiveLinkHubSessionData.h` (Private)


#### class `ULiveLinkHubSessionData`  
`class ULiveLinkHubSessionData : public UObject`  
_L17-100_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Live link hub session data that can be saved to disk.
- L22 _public function_ `ULiveLinkHubSessionData()`
- L31 _public member_ `TArray<FLiveLinkSourcePreset> Sources;` — `UPROPERTY()` — Live link hub sources.
- L35 _public member_ `TArray<FLiveLinkSubjectPreset> Subjects;` — `UPROPERTY()` — Live link hub subjects.
- L39 _public member_ `TArray<FLiveLinkHubUEClientInfo> Clients;` — `UPROPERTY()` — Live link hub client info.
- L43 _public member_ `FString RecordingSessionName;` — `UPROPERTY()` — Recording metadata - session name
- L47 _public member_ `FString RecordingSlateName;` — `UPROPERTY()` — Recording metadata - slate name
- L51 _public member_ `int32 RecordingTakeNumber;` — `UPROPERTY()` — Recording metadata - take number
- L55 _public member_ `bool bUseCustomRecordingDirectory = false;` — `UPROPERTY()` — Whether to use a custom recording directory instead of the default project content folder
- L59 _public member_ `FString CustomRecordingDirectory;` — `UPROPERTY()` — Custom recording directory absolute path (only used if bUseCustomRecordingDirectory is true)
- L63 _public member_ `FString CustomRecordingMountPoint;` — `UPROPERTY()` — Mount point for custom recording directory (e.g., /Game/LiveLinkRecordings_eeaf31)
- L67 _public member_ `ELiveLinkTopologyMode TopologyMode = ELiveLinkTopologyMode::Hub;` — `UPROPERTY()` — If the hub should be a hub or a spoke. Hubs can only connect to UE instances, while spokes can connect to other hubs.
- L71 _public member_ `TMap<TSubclassOf<ULiveLinkHubSessionExtraData>, TObjectPtr<ULiveLinkHubSessionExtraData>> ExtraDatas;` — `UPROPERTY(Instanced)` — Generic / extensible storage for additional fields to be serialized with the session.
- L75 _public member_ `uint32 ProcessId = 0;` — `UPROPERTY()` — ID of the process that created this session. Used by LiveLinkHub's CrashRecovery system to know which autosave files to consider.
- L78 _public function_ `ULiveLinkHubSessionExtraData* GetExtraData(TSubclassOf<ULiveLinkHubSessionExtraData> InExtraDataClass)`
- L89 _public function_ `ULiveLinkHubSessionExtraData* GetOrCreateExtraData(TSubclassOf<ULiveLinkHubSessionExtraData> InExtraDataClass)`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Session/LiveLinkHubSessionManager.h` (Private)


#### class `ILiveLinkHubSessionManager`  
`class ILiveLinkHubSessionManager`  
_L38-81_
- L41 _public prototype_ `virtual ~ILiveLinkHubSessionManager() = default;`
- L44 _public prototype_ `virtual FOnClientAddedToSession& OnClientAddedToSession() = 0;` — Delegate called when a UE client is added to the current session, enabling it to receive data from the hub.
- L47 _public prototype_ `virtual FOnClientRemovedFromSession& OnClientRemovedFromSession() = 0;` — Delegate called when a UE client is removed from the current session, returning it to the list of discovered clients.
- L50 _public prototype_ `virtual FOnActiveSessionChanged& OnActiveSessionChanged() = 0;` — Delegate called when the active session changes, which will change the list of sources, subjects and clients.
- L53 _public prototype_ `virtual FSimpleMulticastDelegate& OnSessionSaved() = 0;` — Delegate called when the active session is saved. (Not triggered for autosaves)
- L56 _public prototype_ `virtual TSharedPtr<ILiveLinkHubSession> GetCurrentSession() const = 0;` — Get the current session, which holds information about which sources, subjects and clients that should be enabled in the hub at the moment.
- L59 _public prototype_ `virtual void NewSession() = 0;` — Clear out the current session data and stat a new empty session.
- L62 _public prototype_ `virtual void SaveSessionAs() = 0;` — Prompt the user to save the current session in a given directory.
- L65 _public prototype_ `virtual void RestoreSession(FStringView InSessionPath = {}) = 0;` — Restore a session from file. If not provided, will prompt the user to browse for the file.
- L68 _public prototype_ `virtual void RestoreSession(ULiveLinkHubSessionData* RestoreSession) = 0;` — Restore a session from an object in memory.
- L71 _public prototype_ `virtual TStrongObjectPtr<ULiveLinkHubSessionData> ReadSessionFile(FStringView InSessionPath) = 0;` — Read a session file and deserialize it to a UObject.
- L74 _public prototype_ `virtual void SaveCurrentSession(FString SavePath = TEXT("")) = 0;` — Save the current session. If not path is specified, the last save path will be used.
- L77 _public prototype_ `virtual bool CanSaveCurrentSession() const = 0;` — Returns whether the current session has as already been saved to disk before.
- L80 _public prototype_ `virtual const FString& GetLastConfigPath() const = 0;` — Returns the last used config path.

#### class `FLiveLinkHubSessionManager`  
`class FLiveLinkHubSessionManager : public ILiveLinkHubSessionManager , public ILiveLinkRecordingSession`  
_L83-711_
- inherits: `ILiveLinkHubSessionManager,ILiveLinkRecordingSession`
- L87 _public function_ `FLiveLinkHubSessionManager()`
- L95 _public function_ `virtual ~FLiveLinkHubSessionManager() override`
- L101 _public function_ `virtual FOnClientAddedToSession& OnClientAddedToSession() override`
- L107 _public function_ `virtual FOnClientRemovedFromSession& OnClientRemovedFromSession() override`
- L113 _public function_ `virtual FOnActiveSessionChanged& OnActiveSessionChanged() override`
- L119 _public function_ `virtual FSimpleMulticastDelegate& OnSessionSaved() override`
- L125 _public function_ `virtual void NewSession() override`
- L131 _public function_ `virtual void SaveSessionAs() override`
- L159 _public function_ `virtual TSharedPtr<ILiveLinkHubSession> GetCurrentSession() const override`
- L165 _public function_ `virtual void SaveCurrentSession(FString SavePath = TEXT("")) override`
- L259 _public function_ `virtual void RestoreSession(FStringView InSessionPath ) override`
- L321 _public function_ `virtual void RestoreSession(ULiveLinkHubSessionData* SessionData)`
- L429 _public function_ `virtual TStrongObjectPtr<ULiveLinkHubSessionData> ReadSessionFile(FStringView InSessionPath) override`
- L441 _public function_ `virtual bool CanSaveCurrentSession() const override`
- L446 _public function_ `virtual const FString& GetLastConfigPath() const override`
- L453 _public function_ `virtual FString GetSessionName() const override`
- L464 _public function_ `virtual FString GetSlateName() const override`
- L475 _public function_ `virtual int32 GetTakeNumber() const override`
- L486 _public function_ `virtual bool SetSessionName(FStringView InSessionName) override`
- L499 _public function_ `virtual bool SetSlateName(FStringView InSlateName) override`
- L512 _public function_ `virtual bool SetTakeNumber(int32 InTakeNumber) override`
- L525 _public function_ `virtual FOnSessionStringChanged& OnSessionNameChanged() override`
- L530 _public function_ `virtual FOnSessionStringChanged& OnSlateNameChanged() override`
- L535 _public function_ `virtual FOnSessionIntChanged& OnTakeNumberChanged() override`
- L540 _public function_ `virtual bool IsRecording() const override`
- L553 _public function_ `virtual FSimpleMulticastDelegate& OnRecordingStarted() override`
- L558 _public function_ `virtual FSimpleMulticastDelegate& OnRecordingStopped() override`
- L563 _public function_ `virtual bool CanRecord() const override`
- L575 _public function_ `virtual bool StartRecording() override`
- L588 _public function_ `virtual bool StopRecording() override`
- L607 _private function_ `void ClearSession(bool bWaitForSourceRemoval = false)` — Clear the hub data contained in the current session, resetting the hub to its default state.
- L652 _private function_ `void CullUnresponsiveSubjects()` — Remove subjects that haven't received data in a while.
- L674 _private member_ `TSharedPtr<FLiveLinkHubSession> CurrentSession;` — Session that holds the current configuration of the hub (Clients, sources, subjects).
- L677 _private member_ `FString LastConfigPath;` — Last path where we saved a session config file.
- L680 _private member_ `FOnClientAddedToSession OnClientAddedToSessionDelegate;` — Delegate triggered when a client is added to the current session.
- L683 _private member_ `FOnClientRemovedFromSession OnClientRemovedFromSessionDelegate;` — Delegate triggered when a client is removed from the current session.
- L686 _private member_ `FOnActiveSessionChanged OnActiveSessionChangedDelegate;` — Delegate triggered when the current session is changed.
- L689 _private member_ `FSimpleMulticastDelegate OnSessionSavedDelegate;` — Delegate called when the session is saved.
- L692 _private member_ `FOnSessionStringChanged OnSessionNameChangedDelegate;` — Delegate triggered when the recording session name is changed.
- L695 _private member_ `FOnSessionStringChanged OnSlateNameChangedDelegate;` — Delegate triggered when the recording slate name is changed.
- L698 _private member_ `FOnSessionIntChanged OnTakeNumberChangedDelegate;` — Delegate triggered when the recording take number is changed.
- L701 _private member_ `FSimpleMulticastDelegate OnRecordingStartedDelegate;` — Delegate triggered when recording begins.
- L704 _private member_ `FSimpleMulticastDelegate OnRecordingStoppedDelegate;` — Delegate triggered when recording ends.
- L707 _private member_ `double OpenSessionTimestampsSeconds = 0.0;` — Timestamp of when the open session button was clicked.
- L710 _private member_ `mutable FCriticalSection CurrentSessionCS;` — Critical section used to synchronize access to the current session.

#### Free symbols / members of external scopes

- L24 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkHub.SessionManager"`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Private` (scope `UE`)
- L26 _namespace_ `namespace SessionManagerUtils` (scope `UE::Private`)
- L29 _function_ `inline static bool IsAutosave(const FString& FilePath)` (scope `UE::Private::SessionManagerUtils`) — Returns whether the give filepath is pointing to a LiveLinkHub autosave file.
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveSessionChanged, const TSharedRef<ILiveLinkHubSession>& );`
- L36 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveSessionChanged, const TSharedRef<ILiveLinkHubSession>& );`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Settings/LiveLinkHubClientTextFilterCustomization.h` (Private)


#### class `FLiveLinkHubClientTextFilterCustomization`  
`class FLiveLinkHubClientTextFilterCustomization : public IPropertyTypeCustomization`  
_L19-98_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for the CustomTimeStep settings.
- L22 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L27 _public function_ `virtual bool ShouldInlineKey() const override`
- L32 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)`
- L94 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)`

#### Free symbols / members of external scopes

- L45 _function_ `PropertyHandle->SetOnChildPropertyValueChanged(FSimpleDelegate::CreateLambda([]() { GetMutableDefault<ULiveLinkHubUserSettings>()->PostUpdateClientFilters(); }));` (scope `FLiveLinkHubClientTextFilterCustomization::CustomizeHeader`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Settings/LiveLinkHubMediaProfileHandler.h` (Private)


#### class `FLiveLinkHubMediaProfileHandler`  
`class FLiveLinkHubMediaProfileHandler : public ILiveLinkHubSessionExtraDataHandler`  
_L28-61_
- inherits: `ILiveLinkHubSessionExtraDataHandler`
- desc: Manages the transient UMediaProfile lifecycle for Live Link Hub. Transient profiles can be created by two paths: - Session restore (OnExtraDataSessionLoaded) creates one from saved preset data. - MediaProfileMenus creates one when the user clicks the toolbar button. This handler adopts any transient profile set as current via OnMediaProfileChanged, tracking it in a TStrongObjectPtr to prevent GC and ensuring default timecode/genlock instances are populated. Session save/load is handled via the ExtraData system. NOTE: This handler has an implicit ordering dependency with other ExtraData handlers. During session restore, this handler creates the transient UMediaProfile and sets it as the current profile via IMediaProfileManager. Other handlers (e.g. LiveLinkDevice streaming) may inject their own media sources into the active profile during or after their own restore. The current design is order-independent because device sources are injected via the device subsystem's own initialization path, not during OnExtraDataSessionLoaded. If that changes, handler ordering (determined by modular feature registration order) may need to be explicit.
- L31 _public prototype_ `FLiveLinkHubMediaProfileHandler();`
- L32 _public prototype_ `virtual ~FLiveLinkHubMediaProfileHandler();`
- L35 _public prototype_ `virtual TSubclassOf<ULiveLinkHubSessionExtraData> GetExtraDataClass() const override;`
- L36 _public prototype_ `virtual void OnExtraDataSessionSaving(ULiveLinkHubSessionExtraData* InExtraData) override;`
- L37 _public prototype_ `virtual void OnExtraDataSessionLoaded(const ULiveLinkHubSessionExtraData* InExtraData) override;`
- L42 _private prototype_ `UMediaProfile* CreateTransientMediaProfile();` — Create a fresh transient UMediaProfile in the transient package with default TC/CTS.
- L45 _private prototype_ `void EnsureDefaultTimingInstances(UMediaProfile* Profile);` — Populates default timecode provider and custom time step on a profile if they are null.
- L48 _private prototype_ `void RestoreDefaultProfile();` — Recreate a fresh default transient profile when no saved state is available.
- L51 _private prototype_ `void OnMediaProfileChanged(UMediaProfile* PreviousProfile, UMediaProfile* NewProfile);` — Called when the active MediaProfile changes. Adopts externally-created transient profiles.
- L54 _private member_ `TStrongObjectPtr<UMediaProfile> TransientMediaProfile;` — The transient media profile managed by this handler. Kept alive via TStrongObjectPtr.
- L57 _private member_ `bool bEditorWasOpenBeforeClear = false;` — Tracks whether the editor was open when the profile was cleared, so we can reopen on restore.
- L60 _private member_ `FDelegateHandle MediaProfileChangedHandle;` — Handle for the OnMediaProfileChanged delegate.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Settings/LiveLinkHubSessionExtraData_MediaProfile.h` (Private)


#### struct `FLiveLinkHubMediaProfilePreset`  
`struct FLiveLinkHubMediaProfilePreset`  
_L20-55_
- reflection: `USTRUCT()`
- desc: Preset struct that captures the state of a UMediaProfile for session serialization. FJsonObjectConverter handles the Instanced polymorphic subobjects automatically.
- L26 _public member_ `TArray<TObjectPtr<UMediaSource>> MediaSources;` — `UPROPERTY(Instanced)` — Media sources configured in the profile.
- L30 _public member_ `TArray<FString> MediaSourceLabels;` — `UPROPERTY()` — User-defined labels for media sources (parallel array to MediaSources).
- L34 _public member_ `TArray<TObjectPtr<UMediaOutput>> MediaOutputs;` — `UPROPERTY(Instanced)` — Media outputs configured in the profile.
- L38 _public member_ `TArray<FString> MediaOutputLabels;` — `UPROPERTY()` — User-defined labels for media outputs (parallel array to MediaOutputs).
- L42 _public member_ `bool bOverrideTimecodeProvider = false;` — `UPROPERTY()` — Whether the profile overrides the engine's timecode provider.
- L46 _public member_ `TObjectPtr<UTimecodeProvider> TimecodeProvider;` — `UPROPERTY(Instanced)` — Timecode provider instance (only relevant if bOverrideTimecodeProvider is true).
- L50 _public member_ `bool bOverrideCustomTimeStep = false;` — `UPROPERTY()` — Whether the profile overrides the engine's custom time step.
- L54 _public member_ `TObjectPtr<UEngineCustomTimeStep> CustomTimeStep;` — `UPROPERTY(Instanced)` — Custom time step instance (only relevant if bOverrideCustomTimeStep is true).

#### class `ULiveLinkHubSessionExtraData_MediaProfile`  
`class ULiveLinkHubSessionExtraData_MediaProfile : public ULiveLinkHubSessionExtraData`  
_L62-69_
- reflection: `UCLASS()`
- inherits: `ULiveLinkHubSessionExtraData`
- desc: Session extra data for persisting the transient MediaProfile state in LLH config files. Follows the same pattern as ULiveLinkHubSessionExtraData_Device.
- L68 _public member_ `FLiveLinkHubMediaProfilePreset MediaProfilePreset;` — `UPROPERTY()`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Settings/LiveLinkHubSettings.h` (Private)


#### class `ULiveLinkHubSettings`  
`class ULiveLinkHubSettings : public UObject`  
_L24-147_
- reflection: `UCLASS(MinimalAPI, config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Settings for LiveLinkHub.
- L29 _public prototype_ `ULiveLinkHubSettings();`
- L31 _public prototype_ `virtual void PostInitProperties() override;`
- L34 _public prototype_ `void CalculateExampleOutput();` — Parse templates and set example output fields.
- L37 _public prototype_ `TObjectPtr<ULiveLinkHubNamingTokens> GetNamingTokens() const;` — Get the naming tokens for Live Link Hub.
- L41 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L47 _public member_ `FFilePath StartupConfig;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkHub")` — Config to apply when starting LiveLinkHub.
- L51 _public member_ `int32 PlaybackFrameBufferSizeMB = 100;` — `UPROPERTY(config, EditAnywhere, Category="LiveLinkHub", meta = (ClampMin = "1", UIMin = "1"))` — The size in megabytes to buffer when streaming a recording.
- L55 _public member_ `int32 PlaybackBufferBatchSize = 5;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category="LiveLinkHub", meta = (ClampMin = "2", UIMin = "2"))` — Number of frames to buffer at once.
- L59 _public member_ `int32 PlaybackMaxBufferRangeHistory = 25;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category="LiveLinkHub")` — Maximum number of frame ranges to store in history while scrubbing. Increasing can make scrubbing faster but temporarily use more memory.
- L62 _public member_ `bool bAllowModifyingSourceSettingsInPlayback = false;` — `UPROPERTY(EditAnywhere, Config, Category = "LiveLinkHub")`
- L66 _public member_ `TArray<FName> ProjectSettingsToDisplay;` — `UPROPERTY(config)` — Which project settings sections to display when opening the settings viewer.
- L70 _public member_ `bool bRemoveInvalidSubjectsAfterLoadingSession = false;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkHub")` — If this is enabled, invalid subjects will be removed after loading a session.
- L74 _public member_ `bool bConfirmClose = true;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkHub")` — If enabled, you'll be asked to confirm if you really want to close the hub.
- L78 _public member_ `bool bEnableCrashRecovery = true;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkHub")` — Whether to enable Live Link Hub's crash recovery system.
- L82 _public member_ `bool bShowFrameRate = false;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkHub")` — Whether to show the app's frame rate in the top right corner.
- L86 _public member_ `bool bShowMemoryUsage = true;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkHub")` — Whether to show memory usage in the top right corner.
- L90 _public member_ `float ShowMemoryWarningThresholdMB = 8000.0;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkHub", DisplayName = "Memory Warning Threshold (MB)")` — How much RAM (in MB) the program can use before showing a warning.
- L98 _public member_ `bool bTickOnGameThread = false;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkHub", meta = (ConfigRestartRequired = true))` — - Experimental - If this is disabled, LiveLinkHub's LiveLink Client will tick outside of the game thread. This allows processing LiveLink frame snapshots without the risk of being blocked by the game / ui thread. Note that this should only be relevant for virtual subjects since data is already forwarded to UE outside of the game thread.
- L102 _public member_ `float TargetFrameRate = 60.0f;` — `UPROPERTY(config, EditAnywhere, Category="LiveLinkHub", meta = (ConfigRestartRequired = true, ClampMin="15.0"))` — Target framerate for ticking LiveLinkHub.
- L106 _public member_ `bool bPromptSaveAsOnRecord = false;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkHub")` — Whether to prompt the user to pick a save directory after doing a recording.
- L110 _public member_ `bool bIncrementTakeOnRecordingEnd = true;` — `UPROPERTY(config, EditAnywhere, Category = "Templates")` — Whether to increment take number when stopping a recording.
- L114 _public member_ `bool bEnableAutosave = true;` — `UPROPERTY(config, EditAnywhere, Category = "Autosave")` — Whether to enable auto-save of Live Link Hub configs.
- L118 _public member_ `uint32 MinutesBetweenAutosave = 5;` — `UPROPERTY(config, EditAnywhere, Category = "Autosave", meta=(ClampMin="1", ClampMax="120", EditCondition="bEnableAutosave", EditConditionHides))` — How often should we trigger a config autosave.
- L122 _public member_ `int32 NumberOfAutosaveFilesToRetain = 5;` — `UPROPERTY(config, EditAnywhere, Category = "Autosave", meta = (ClampMin = "1", ClampMax = "10", EditCondition = "bEnableAutosave", EditConditionHides))` — How many autosave file should we retain on disk.
- L126 _public member_ `float SourceMaxCleanupTime = 0.25f;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category="LiveLinkHub", meta = (ClampMin="0.0"))` — Maximum time in seconds to wait for sources to clean up. Increase this value if you notice that some sources are incorrectly cleaned up when switching a config.
- L130 _public member_ `FString FilenameTemplate = TEXT("{se` — `UPROPERTY(config, EditAnywhere, Category="Templates")` — The filename template to use when creating recordings.
- L134 _public member_ `FString FilenameOutput;` — `UPROPERTY(VisibleAnywhere, Category="Templates", DisplayName="Output")` — Example parsed output of the template.
- L138 _public member_ `FText AutomaticTokens;` — `UPROPERTY(VisibleAnywhere, Category="Templates")` — Placeholder for a list of the automatic tokens, set from the customization.
- L146 _private member_ `mutable TObjectPtr<ULiveLinkHubNamingTokens> NamingTokens;` — `UPROPERTY(Instanced, Transient)` — Naming tokens for Live Link, instantiated each load based on the naming tokens class. This isn't serialized to the config file, and exists here for singleton-like access.

#### enum `ELiveLinkHubClientFilterBehavior`  
`enum class ELiveLinkHubClientFilterBehavior`  
_L151-155_
- reflection: `UENUM()`
- desc: Whether a filter should include or exlude the client that matches the filter.
- L153 _public enumerator_ `Include`
- L154 _public enumerator_ `Exclude`

#### enum `ELiveLinkHubClientFilterType`  
`enum class ELiveLinkHubClientFilterType`  
_L159-163_
- reflection: `UENUM()`
- desc: Whether we're filtering on IP or a hostname.
- L161 _public enumerator_ `IP`
- L162 _public enumerator_ `Host`

#### struct `FLiveLinkHubClientTextFilter`  
`struct FLiveLinkHubClientTextFilter`  
_L167-186_
- reflection: `USTRUCT()`
- desc: Basic text filter that includes or excludes IPs/Hostnames.
- L173 _public member_ `FString Project;` — `UPROPERTY(config, EditAnywhere, Category = "Filters")` — Optional project name filter. Will match any project if empty or *.
- L177 _public member_ `FString Text;` — `UPROPERTY(config, EditAnywhere, Category = "Filters")` — Text that will be used to match the filter.
- L181 _public member_ `ELiveLinkHubClientFilterType Type = ELiveLinkHubClientFilterType::IP;` — `UPROPERTY(config, EditAnywhere, Category = "Filters")` — Type of the filter.
- L185 _public member_ `ELiveLinkHubClientFilterBehavior Behavior = ELiveLinkHubClientFilterBehavior::Include;` — `UPROPERTY(config, EditAnywhere, Category = "Filters")` — Behavior of the filter.

#### struct `FLiveLinkHubClientFilterPreset`  
`struct FLiveLinkHubClientFilterPreset`  
_L190-205_
- reflection: `USTRUCT()`
- desc: A collection of filters, used to restore and save filters on disk.
- L196 _public member_ `FString PresetName;` — `UPROPERTY(config, DisplayName="Name")` — Name of this preset.
- L200 _public member_ `ELiveLinkHubAutoConnectMode AutoConnectClients = ELiveLinkHubAutoConnectMode::LocalOnly;` — `UPROPERTY(config)` — General autoconnect mode of the app.
- L204 _public member_ `TArray<FLiveLinkHubClientTextFilter> Filters;` — `UPROPERTY(config, EditAnywhere, Category = "Filters")` — List of filters in the preset.

#### class `ULiveLinkHubUserSettings`  
`class ULiveLinkHubUserSettings : public UObject`  
_L212-325_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: User Settings for LiveLinkHub.
- L218 _public prototype_ `virtual void PostInitProperties() override;`
- L222 _public member_ `uint8 MaxNumberOfRecentConfigs = 5;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkHub")` — Number of recent configs to keep track.
- L226 _public member_ `TArray<FString> RecentConfigs;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkHub")` — File paths to recent configs that were saved/loaded.
- L230 _public member_ `TArray<FString> LayoutDirectories;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkHub")` — Which directories to scan to discover layouts
- L234 _public member_ `FString LastConfigDirectory;` — `UPROPERTY(config)` — The last directory of the a config that was saved or loaded.
- L237 _public member_ `FLiveLinkHubClientFilterPreset CurrentPreset;` — `UPROPERTY(config, EditAnywhere, Category = "Filters", meta=(ShowOnlyInnerProperties))`
- L241 _public prototype_ `void CacheRecentConfig(const FString& SavePath);` — Call after an explicit config save or load to save it in the recent config file list.
- L244 _public prototype_ `TArray<struct FLiveLinkHubSessionFile> GetRecentConfigFiles();` — Get the most recent config / session files that were used in LiveLinkHub.
- L247 _public function_ `void PostUpdateClientFilters()` — Invoked through post-edit change, but can be invoked manually to copy the filters data to a thread-safe copy.
- L260 _public function_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)`
- L267 _public function_ `ELiveLinkHubAutoConnectMode GetAutoConnectMode() const` — Get the AutoConnect mode from the current preset.
- L274 _public function_ `void SetAutoConnectMode(ELiveLinkHubAutoConnectMode Mode)` — Sets the autoconnect mode.
- L282 _public prototype_ `void SaveCurrentPreset();` — Save the current preset to the settings ini.
- L285 _public prototype_ `void SavePresetAs(const FString& PresetName);` — Save the current filters configuration as a new preset in the settings ini.
- L288 _public prototype_ `void SaveClientsToPreset(const FString& InPresetName);` — Creates a preset of filters from the list of clients that are currently in the session.
- L291 _public function_ `const TArray<FLiveLinkHubClientFilterPreset>& GetFilterPresets() const` — Get all filter presets.
- L297 _public prototype_ `void LoadFilterPreset(const FString& PresetName);` — Applies a filter preset.
- L300 _public prototype_ `void DeleteFilterPreset(const FString& PresetName);` — Deletes a filter preset.
- L303 _public function_ `FLiveLinkHubClientFilterPreset GetClientFiltersData_AnyThread()` — Get a copy of the client filters data in a thread-safe way.
- L309 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FOnFiltersModified);`
- L310 _public member_ `FOnFiltersModified OnFiltersModifiedDelegate;`
- L317 _private member_ `FLiveLinkHubClientFilterPreset CurrentFilterPreset_ThreadSafe;` — Shadow variable needed to access the current filter preset from outside the game thread. Used to avoid excessive locking from widgets ticking on the game thread and accessing CurrentPreset.
- L321 _private member_ `TArray<FLiveLinkHubClientFilterPreset> FilterPresets;` — `UPROPERTY(config)` — List of filter presets serialized to the user config.
- L324 _private member_ `mutable FTransactionallySafeRWLock FiltersLock;` — Lock used to access CurrentFilterPreset_ThreadSafe.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API LIVELINKHUB_API`
- L309 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FOnFiltersModified);`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Settings/LiveLinkHubSettingsCustomization.h` (Private)


#### class `FLiveLinkHubSettingsCustomization`  
`class FLiveLinkHubSettingsCustomization : public IDetailCustomization`  
_L11-19_
- inherits: `IDetailCustomization`
- desc: Customization for the live link hub settings.
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L18 _private prototype_ `FText GetDisplayTokenText() const;`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Settings/LiveLinkHubTimeAndSyncSettings.h` (Private)


#### class `ULiveLinkHubTimeAndSyncSettings`  
`class ULiveLinkHubTimeAndSyncSettings : public UObject`  
_L22-113_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for LiveLinkHub's timecode and genlock broadcasting. Timecode and genlock source configuration is defined in the active MediaProfile. This class controls whether LiveLinkHub broadcasts those settings to connected clients.
- L29 _public member_ `FLiveLinkHubTimecodeSettings TimecodeSettings;` — `UE_DEPRECATED(5.8,"Property will be removed in a future version")` — `UPROPERTY(config, meta=(DeprecatedProperty, DeprecationMessage="This property is deprecated"))`
- L33 _public member_ `bool bUseLiveLinkHubAsTimecodeSource = false;` — `UPROPERTY(config, EditAnywhere, Category = "Timecode", DisplayName = "Enable")` — Whether the hub should be used as a timecode source for connected clients.
- L38 _public member_ `FLiveLinkHubCustomTimeStepSettings CustomTimeStepSettings;` — `UPROPERTY(config, meta=(DeprecatedProperty, DeprecationMessage="This property is deprecated"))` — Custom time step
- L42 _public member_ `bool bUseLiveLinkHubAsCustomTimeStepSource = false;` — `UPROPERTY(config, EditAnywhere, Category = "Frame Lock", DisplayName = "Enable")` — Whether the hub should be used as a CustomTimeStep source for connected clients.
- L49 _public member_ `ELiveLinkSourceMode PreferredClientEvaluationMode = ELiveLinkSourceMode::EngineTime;` — `UPROPERTY(config, EditAnywhere, Category = "Evaluation", DisplayName = "Preferred Client Evaluation Mode")` — Evaluation mode that connected Editor clients should apply to their Live Link Hub source. Pushed to every connected client when changed and when a client connects. Overwrites the client's local setting.
- L54 _public function_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override`
- L81 _public function_ `void OnToggleTimecodeSettings()` — Handles broadcasting timecode settings when they're enabled/disabled.
- L98 _public function_ `void OnToggleCustomTimeStepSettings()` — Handles broadcasting custom time step settings when they're enabled/disabled.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Settings/LiveLinkHubTimingUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace LiveLinkHubTimingUtils` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::LiveLinkHubTimingUtils`)
- L16 _prototype_ `FLiveLinkHubTimecodeSettings GetTimecodeSettingsFromActiveProfile();` (scope `UE::LiveLinkHubTimingUtils::Private`) — Read the active MediaProfile's timecode provider and convert to message settings. Returns NotDefined if no profile is active.
- L19 _prototype_ `FLiveLinkHubCustomTimeStepSettings GetCustomTimeStepSettingsFromActiveProfile();` (scope `UE::LiveLinkHubTimingUtils::Private`) — Read the active MediaProfile's custom time step and convert to message settings. Returns reset settings if no profile is active.
- L22 _prototype_ `void BroadcastCurrentSettings();` (scope `UE::LiveLinkHubTimingUtils::Private`) — Broadcasts current timecode settings to all connected clients if broadcasting is enabled. Called when the MediaProfile changes.
- L27 _prototype_ `void ClearMediaProfileCustomTimeStepFromEngine();` (scope `UE::LiveLinkHubTimingUtils::Private`) — Clear GEngine's custom time step if it matches the one defined in the active MediaProfile.
- L33 _externvar_ `extern TOptional<ELiveLinkTimecodeProviderEvaluationType> PlaybackEvaluationOverride;` (scope `UE::LiveLinkHubTimingUtils::Private`) — Transient override for the timecode evaluation type during playback. When set, this overrides the EvaluationType in the settings returned by GetTimecodeSettingsFromActiveProfile().

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Settings/LiveLinkSettingsCustomization.h` (Private)


#### class `FLiveLinkSettingsCustomization`  
`class FLiveLinkSettingsCustomization final : public IDetailCustomization`  
_L13-18_
- inherits: `IDetailCustomization`
- desc: Customization for the standard Live Link settings, specifically for Live Link Hub. If we ever need to customize these core settings under the LiveLink plugin, then this class may need to be moved there, and either extended here or made configurable to allow certain properties hidden by LLH.
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Subjects/LiveLinkHubSubjectController.h` (Private)


#### class `FLiveLinkHubSubjectController`  
`class FLiveLinkHubSubjectController`  
_L14-61_
- desc: Controller responsible for handling the hub's subjects and creating the subject view.
- L17 _public function_ `FLiveLinkHubSubjectController()`
- L23 _public function_ `~FLiveLinkHubSubjectController()`
- L35 _public function_ `TSharedRef<SWidget> MakeSubjectView()` — Create the widget for displaying a subject's settings.
- L41 _public function_ `void SetSubject(const FLiveLinkSubjectKey& Subject) const` — Set the displayed subject in the subject view.
- L50 _public function_ `void OnActiveSessionChanged(const TSharedRef<ILiveLinkHubSession>& ActiveSession) const` — Handle updating the subject details when the session has been swapped out for a different one.
- L60 _private member_ `TSharedPtr<SLiveLinkHubSubjectView> SubjectsView;` — View widget for the selected subject.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Subjects/SLiveLinkHubSubjectView.h` (Private)


#### class `SLiveLinkHubSubjectView`  
`class SLiveLinkHubSubjectView : public SCompoundWidget`  
_L17-77_
- inherits: `SCompoundWidget`
- desc: Provides the UI that displays information about a livelink hub subject.
- L21 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkHubSubjectView)`
- L22 _public function_ `SLATE_ARGUMENT(FLiveLinkSubjectKey, SubjectKey) SLATE_END_ARGS()`
- L40 _public function_ `virtual ~SLiveLinkHubSubjectView() override`
- L50 _public function_ `void RefreshSubjectDetails(const TSharedPtr<class ILiveLinkHubSession>& ActiveSession)` — Clear the subject details.
- L56 _public function_ `void SetSubject(const FLiveLinkSubjectKey& InSubjectKey)` — Set the subject to be displayed in the details view.
- L62 _public function_ `void OnSubjectRemoved(FLiveLinkSubjectKey InSubjectKey)`
- L72 _private member_ `TSharedPtr<IDetailsView> SettingsObjectDetailsView;` — Details for the selected subject.
- L74 _private member_ `FLiveLinkSubjectKey SubjectKey;` — Subject being shown.
- L76 _private member_ `TSharedPtr<SLiveLinkDataView> SubjectView;`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/UI/Widgets/SApplicationModeSwitcher.h` (Private)


#### class `SApplicationModeSwitcher`  
`class SApplicationModeSwitcher : public SCompoundWidget`  
_L19-213_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SApplicationModeSwitcher)`
- L24 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L63 _public function_ `virtual ~SApplicationModeSwitcher()`
- L73 _private function_ `TSharedRef<SWidget> GetModeSwitcherContent()` — Create the content of the layout button when it's oppened.
- L164 _private function_ `void SetActiveMode(FName ModeName)` — Set the current application mode.
- L173 _private function_ `void OnAppModeChanged(FName NewModeName) const` — Handle app mode changing.
- L186 _private function_ `void CreateDeleteLayoutMenu(FMenuBuilder& MenuBuilder)` — Populate the Delete Layout menu with the list of user layouts.
- L210 _private member_ `TSharedPtr<SImage> ActiveModeImage;` — Holds the icon of the current mode.
- L212 _private member_ `TSharedPtr<STextBlock> ActiveModeDisplayName;` — Holds the display name of the current mode.

#### Free symbols / members of external scopes

- L17 _macro_ `#define LOCTEXT_NAMESPACE "ApplicationModeSwitcher"`
- L120 _function_ `INVTEXT("Save Layout As"), TAttribute<FText>(), FSlateIcon(), FUIAction(FExecuteAction::CreateLambda([]() { FLiveLinkHub::Get()->SaveLayoutAs(); })), NAME_None, EUserInterfaceActionType::Button );` (scope `SApplicationModeSwitcher::GetModeSwitcherContent`)
- L129 _function_ `INVTEXT("Load Layout"), TAttribute<FText>(), FSlateIcon(), FUIAction(FExecuteAction::CreateLambda([]() { FLiveLinkHub::Get()->LoadLayout(); })), NAME_None, EUserInterfaceActionType::Button );` (scope `SApplicationModeSwitcher::GetModeSwitcherContent`)
- L142 _function_ `INVTEXT("Reset Current Layout"), TAttribute<FText>(), FSlateIcon(), FUIAction(FExecuteAction::CreateLambda([]() { FLiveLinkHub::Get()->ResetLayout(); })), NAME_None, EUserInterfaceActionType::Button );` (scope `SApplicationModeSwitcher::GetModeSwitcherContent`)
- L200 _function_ `FText::FromString(Layout), TAttribute<FText>(), FSlateIcon(), FUIAction(FExecuteAction::CreateLambda([Layout]() { FLiveLinkHub::Get()->DeleteUserLayout(Layout); })), NAME_None, EUserInterfaceActionType::Button );` (scope `SApplicationModeSwitcher::CreateDeleteLayoutMenu`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/UI/Widgets/SLiveLinkHubMemoryStats.h` (Private)


#### class `SLiveLinkHubMemoryStats`  
`class SLiveLinkHubMemoryStats : public SCompoundWidget`  
_L21-280_
- inherits: `SCompoundWidget`
- desc: Widget that displays the current memory usage of the program and shows a warning if the memory usage falls above a threshold defined in the LiveLinkHub settings.
- L24 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkHubMemoryStats)`
- L26 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L100 _public function_ `virtual void Tick(const FGeometry & AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override`
- L119 _private function_ `void UpdateFrameRate()` — Update the cached frame rate text
- L133 _private function_ `void UpdateFrameTime()` — Update the cached frame time text.
- L148 _private function_ `void UpdateMemoryStats()` — Update our cached memory stats.
- L178 _private function_ `void WarnUser()` — Open a toast notification to warn the user that memory consumption is unusually high.
- L197 _private function_ `FReply OnClickMemoryWarning()` — Handles clicking on the warning button to create a trace snapshot.
- L205 _private function_ `void GenerateTraceSnapshot()` — Handles creating a snapshot tracefile.
- L238 _private function_ `void CloseNotification()` — Closes the current memory usage notification.
- L245 _private function_ `EVisibility OnGetWarningVisibility() const` — Determines whether the warning icon should be visible.
- L255 _private function_ `FText CreateWarningText()` — Generate the warning message for current memory usage.
- L263 _private member_ `float CachedTotalPhysicalUsedMB = 0.f;` — Cached memory used in this process.
- L265 _private member_ `FText CachedFrameRateText;` — Cached text representation of the current app frame rate.
- L267 _private member_ `FText CachedFrameTimeText;` — Cached text representation of the current app frame time.
- L269 _private member_ `FText CachedMemoryText;` — Cached text representation of our total physical memory used.
- L271 _private member_ `FString LastTracePath;` — Stores the path to the last trace snapshot that was generated.
- L273 _private member_ `bool bCreatingTrace = false;` — Whether the hub is currently generating a report.
- L275 _private member_ `bool bWarnedUser = false;` — Whether the user was warned about high memory usage (will reset once it goes below threshold again.
- L277 _private member_ `TSharedPtr<SNotificationItem> CurrentNotification;` — Pointer to the current notification shown on screen.
- L279 _private member_ `const int32 FramesBetweenPlatformQueries = 120;` — Number of frames to wait between calls to FPlatformMemory::GetStats

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkHubMemoryStats"`
- L39 _function_ `.Visibility_Lambda([]() { return GetDefault<ULiveLinkHubSettings>()->bShowFrameRate ? EVisibility::Visible : EVisibility::Collapsed; }) + SHorizontalBox::Slot() .VAlign(VAlign_Bottom) .AutoWidth() [ SNew(STextBlock) .Font(FAppStyle::GetFontStyle(TEXT("MainFrame.DebugTools.LabelFont"))) .ColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f)) .Text(LOCTEXT("FrameRateLabel", "FPS: ")) ] + SHorizontalBox::Slot() .VAlign(VAlign_Bottom) .AutoWidth() [ SNew(STextBlock) .Text(TAttribute<FText>::CreateLambda([this]() { return FText::Format(INVTEXT("{0} / {1}"), CachedFrameRateText, CachedFrameTimeText); })) ] ] + SHorizontalBox::Slot() .VAlign(VAlign_Center) .AutoWidth() [ SNew(SHorizontalBox) .Visibility_Lambda([]() { return GetDefault<ULiveLinkHubSettings>()->bShowMemoryUsage ? EVisibility::Visible : EVisibility::Collapsed; }) + SHorizontalBox::Slot() .VAlign(VAlign_Bottom) .AutoWidth() [ SNew(STextBlock) .Font(FAppStyle::GetFontStyle(TEXT("MainFrame.DebugTools.LabelFont"))) .ColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f)) .Text(LOCTEXT("MemoryLabel", "Mem: ")) ] + SHorizontalBox::Slot() .VAlign(VAlign_Bottom) .AutoWidth() [ SNew(STextBlock) .Text(TAttribute<FText>::CreateLambda([this]() { return CachedMemoryText; })) ]` (scope `SLiveLinkHubMemoryStats::SLATE_END_ARGS`)
- L54 _function_ `.Text(TAttribute<FText>::CreateLambda([this]() { return FText::Format(INVTEXT("{0} / {1}"), CachedFrameRateText, CachedFrameTimeText); })) ] ] + SHorizontalBox::Slot() .VAlign(VAlign_Center) .AutoWidth() [ SNew(SHorizontalBox) .Visibility_Lambda([]()` (scope `SLiveLinkHubMemoryStats::SLATE_END_ARGS`)
- L62 _function_ `.Visibility_Lambda([]() { return GetDefault<ULiveLinkHubSettings>()->bShowMemoryUsage ? EVisibility::Visible : EVisibility::Collapsed; }) + SHorizontalBox::Slot() .VAlign(VAlign_Bottom) .AutoWidth() [ SNew(STextBlock) .Font(FAppStyle::GetFontStyle(TEXT("MainFrame.DebugTools.LabelFont"))) .ColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f)) .Text(LOCTEXT("MemoryLabel", "Mem: ")) ] + SHorizontalBox::Slot() .VAlign(VAlign_Bottom) .AutoWidth() [ SNew(STextBlock) .Text(TAttribute<FText>::CreateLambda([this]() { return CachedMemoryText; })) ] + SHorizontalBox::Slot() .AutoWidth() .Padding(2.0f, 0.0f) .VAlign(VAlign_Bottom) [ SNew(SButton) .ContentPadding(FMargin(0, 2.0)) .ToolTipText(LOCTEXT("MemoryWarningTooltip", "Live Link Hub is using an unusual amount of RAM. Click here to collect a memory trace.")) .Visibility(this, &SLiveLinkHubMemoryStats::OnGetWarningVisibility) .OnClicked(this, &SLiveLinkHubMemoryStats::OnClickMemoryWarning) .IsEnabled_Lambda([this]() { return !bCreatingTrace; }) [ SNew(SImage) .ColorAndOpacity(FLinearColor::Red) .Image(FCoreStyle::Get().GetBrush("Icons.Warning")) ] ] ] ];` (scope `SLiveLinkHubMemoryStats::SLATE_END_ARGS`)
- L77 _function_ `.Text(TAttribute<FText>::CreateLambda([this]() { return CachedMemoryText; })) ] + SHorizontalBox::Slot() .AutoWidth() .Padding(2.0f, 0.0f) .VAlign(VAlign_Bottom) [ SNew(SButton) .ContentPadding(FMargin(0, 2.0)) .ToolTipText(LOCTEXT("MemoryWarningTooltip", "Live Link Hub is using an unusual amount of RAM. Click here to collect a memory trace.")) .Visibility(this, &SLiveLinkHubMemoryStats::OnGetWarningVisibility) .OnClicked(this, &SLiveLinkHubMemoryStats::OnClickMemoryWarning) .IsEnabled_Lambda([this]() { return !bCreatingTrace; }) [ SNew(SImage) .ColorAndOpacity(FLinearColor::Red) .Image(FCoreStyle::Get().GetBrush("Icons.Warning")) ] ] ] ];` (scope `SLiveLinkHubMemoryStats::SLATE_END_ARGS`)
- L89 _function_ `.IsEnabled_Lambda([this]() { return !bCreatingTrace; }) [ SNew(SImage) .ColorAndOpacity(FLinearColor::Red) .Image(FCoreStyle::Get().GetBrush("Icons.Warning")) ] ] ] ];` (scope `SLiveLinkHubMemoryStats::SLATE_END_ARGS`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/UI/Widgets/SLiveLinkHubPlaybackWidget.h` (Private)


#### class `SLiveLinkHubPlaybackWidget`  
`class SLiveLinkHubPlaybackWidget : public SCompoundWidget`  
_L18-342_
- inherits: `SCompoundWidget`
- desc: The playback widget for controlling live link hub animations.
- L21 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnGetChecked);`
- L22 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSetChecked, bool);`
- L23 _public prototype_ `DECLARE_DELEGATE_RetVal(FQualifiedFrameTime, FOnGetTime);`
- L24 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSetTime, FQualifiedFrameTime);`
- L25 _public prototype_ `DECLARE_DELEGATE_RetVal(FFrameRate, FOnGetFrame);`
- L26 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSetDoubleRange, const TRange<double>&) DECLARE_DELEGATE_RetVal(TRange<double>, FOnGetDoubleRange) DECLARE_DELEGATE_RetVal(UE::LiveLinkHub::RangeHelpers::Private::TRangeArray<int32>, FOnGetIntArrayRange) DECLARE_DELEGATE_RetVal(float, FOnGetFloat) DECLARE_DELEGATE_OneParam(FOnSetFloat, float) DECLARE_DELEGATE(FOnButtonPressed);`
- L34 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkHubPlaybackWidget)`
- L36 _public prototype_ `SLATE_EVENT(FOnButtonPressed, OnPlayForward) SLATE_EVENT(FOnButtonPressed, OnPlayReverse) SLATE_EVENT(FOnButtonPressed, OnFirstFrame) SLATE_EVENT(FOnButtonPressed, OnLastFrame) SLATE_EVENT(FOnButtonPressed, OnPreviousFrame) SLATE_EVENT(FOnButtonPressed, OnNextFrame) SLATE_EVENT(FOnSetFloat, OnSetPlayRate) SLATE_EVENT(FOnButtonPressed, OnExitPlayback) SLATE_EVENT(FOnButtonPressed, OnSelectRecording) SLATE_EVENT(FOnGetChecked, IsLooping) SLATE_EVENT(FOnSetChecked, OnSetLooping) SLATE_EVENT(FOnGetChecked, IsPlaybackEnabled) SLATE_EVENT(FOnGetChecked, IsUpgrading) SLATE_EVENT(FOnGetFloat, OnGetUpgradePercent) SLATE_EVENT(FOnGetChecked, IsPaused) SLATE_EVENT(FOnGetChecked, IsInReverse) SLATE_EVENT(FOnGetTime, GetCurrentTime) SLATE_EVENT(FOnSetTime, SetCurrentTime) SLATE_EVENT(FOnGetTime, GetTotalLength) SLATE_EVENT(FOnGetTime, GetSelectionStartTime)` — When forward play is pressed.
- L105 _protected function_ `virtual bool SupportsKeyboardFocus() const`
- L106 _protected prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L107 _protected prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L108 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L109 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L110 _protected prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L115 _private prototype_ `FReply OnPlayForwardPressed();` — When play forward is pressed.
- L117 _private prototype_ `FReply OnPlayReversePressed();` — When play reverse is pressed.
- L119 _private prototype_ `FReply OnFirstFramePressed();` — When first frame is pressed.
- L121 _private prototype_ `FReply OnLastFramePressed();` — When last frame is pressed.
- L123 _private prototype_ `FReply OnPreviousFramePressed();` — When previous frame is pressed.
- L125 _private prototype_ `FReply OnNextFramePressed();` — When next frame is pressed.
- L127 _private prototype_ `FReply OnLoopPressed();` — When loop recording is pressed.
- L129 _private prototype_ `FReply OnSelectRecordingPressed();` — When using wishes to select a recording to play.
- L131 _private prototype_ `FReply OnExitPlaybackPressed();` — When recording is exited.
- L134 _private prototype_ `void SetCurrentTime(double InTime);` — Sets the current playhead time.
- L137 _private prototype_ `double GetCurrentTimeDouble() const;` — The current playhead time.
- L138 _private prototype_ `FQualifiedFrameTime GetCurrentTime() const;`
- L140 _private prototype_ `double GetTotalLength() const;` — The total length of the recording.
- L143 _private prototype_ `double GetSelectionStartTime() const;` — Retrieve the selection start time.
- L145 _private prototype_ `void SetSelectionStartTime(double InTime);` — Set the selection start time.
- L148 _private prototype_ `double GetSelectionEndTime() const;` — Retrieve the selection end time.
- L150 _private prototype_ `void SetSelectionEndTime(double InTime);` — Set the selection end time.
- L153 _private prototype_ `TRange<double> GetViewRange() const;` — Retrieve the visible range of the scrubber.
- L155 _private prototype_ `void SetViewRange(TRange<double> InRange);` — Set the visible range of the scrubber.
- L158 _private prototype_ `TRange<double> GetClampRange() const;` — Retrieve the range to clamp playback to (the selection).
- L161 _private prototype_ `UE::LiveLinkHub::RangeHelpers::Private::TRangeArray<double> GetBufferRanges() const;` — Retrieve the buffered frame range.
- L164 _private prototype_ `bool IsPaused() const;` — Is playback paused?
- L166 _private prototype_ `bool IsPlayingInReverse() const;` — Is playback in reverse?
- L169 _private prototype_ `double GetSpinboxDelta() const;` — Retrieve the delta used when dragging the spinbox.
- L172 _private prototype_ `EFrameNumberDisplayFormats GetDisplayFormat() const;` — Frame or seconds to display for text and input.
- L175 _private prototype_ `void SetDisplayFormat(EFrameNumberDisplayFormats InDisplayFormat);` — Sets the display format.
- L178 _private prototype_ `bool CompareDisplayFormat(EFrameNumberDisplayFormats InDisplayFormat) const;` — Validates the current display format is set to the given format.
- L181 _private prototype_ `void SetPlayRate(float InPlayRate);` — Set the play rate (time dilation multiplier).
- L184 _private prototype_ `FText GetDisplayFormatAsText() const;` — Retrieve the text version of the display format.
- L187 _private prototype_ `FFrameRate GetFrameRate() const;` — The frame rate, used for number inputs.
- L190 _private prototype_ `FQualifiedFrameTime SecondsToFrameTime(double InTime) const;` — Convert raw seconds to frame time.
- L193 _private prototype_ `const FSlateBrush* GetPlayForwardIcon() const;` — The forward icon to use for the play forward button.
- L195 _private prototype_ `const FSlateBrush* GetPlayReverseIcon() const;` — The reverse icon to use for the play reverse button.
- L197 _private prototype_ `const FSlateBrush* GetLoopIcon() const;` — The loop icon to use for the loop button.
- L199 _private prototype_ `FText GetLoopTooltip() const;` — The tooltip for the loop button.
- L202 _private prototype_ `TSharedRef<SWidget> MakePlaybackSettingsDropdown();` — Create the dropdown box for playback settings.
- L205 _private prototype_ `TSharedRef<SWidget> MakePlayRateMenuContent();` — Make the menu content that allows picking a play rate.
- L208 _private prototype_ `TSharedRef<SWidget> MakeUpgradingWidget();` — The widget used for displaying upgrade notifications.
- L211 _private prototype_ `FText GetUpgradeText() const;` — Get the text displayed in the upgrade notification.
- L214 _private prototype_ `float GetUpgradePercent() const;` — The percent the upgrade has finished.
- L217 _private prototype_ `bool IsPlaybackEnabled() const;` — Returns whether the playback widgets should be enabled or not by calling the IsPlaybackEnabledDelegate delegate.
- L220 _private prototype_ `FReply HandleAndFocusTimeSlider() const;` — Returns a FReply::Handled() and focuses the time slider. Useful so the user can click the play button but scrub using left and right keys.
- L223 _private member_ `FOnButtonPressed OnPlayForwardDelegate;` — Delegate for pressing play forward.
- L226 _private member_ `FOnButtonPressed OnPlayReverseDelegate;` — Delegate for pressing play reverse.
- L229 _private member_ `FOnButtonPressed OnFirstFrameDelegate;` — Delegate for pressing go to first frame.
- L232 _private member_ `FOnButtonPressed OnLastFrameDelegate;` — Delegate for pressing go to last frame.
- L235 _private member_ `FOnButtonPressed OnPreviousFrameDelegate;` — Delegate for going to the previous frame.
- L238 _private member_ `FOnButtonPressed OnNextFrameDelegate;` — Delegate for going to the next frame.
- L241 _private member_ `FOnSetFloat OnSetPlayRateDelegate;` — Delegate for setting the play rate.
- L244 _private member_ `FOnButtonPressed OnExitPlaybackDelegate;` — Delegate for exiting the current recording.
- L247 _private member_ `FOnButtonPressed OnSelectRecordingDelegate;` — Delegate for selecting a recording to play.
- L250 _private member_ `FOnGetChecked IsPlaybackEnabledDelegate;` — Delegate checking if the recording playback is enabled
- L253 _private member_ `FOnGetChecked IsUpgradingDelegate;` — Delegate if recording is upgrading.
- L256 _private member_ `FOnGetFloat OnGetUpgradePercentDelegate;` — Delegate for upgrade percent.
- L259 _private member_ `FOnGetChecked OnGetPausedDelegate;` — Delegate for checking if the recording playback is paused.
- L262 _private member_ `FOnGetChecked OnGetIsInReverseDelegate;` — Delegate for checking if the recording playback is playing in reverse.
- L265 _private member_ `FOnGetChecked OnGetLoopingDelegate;` — Delegate for checking if the recording playback should loop.
- L268 _private member_ `FOnSetChecked OnSetLoopingDelegate;` — Delegate to set the looping option.
- L271 _private member_ `FOnGetTime OnGetTotalLengthDelegate;` — Delegate for getting the total length of the recording.
- L274 _private member_ `FOnGetTime OnGetCurrentTimeDelegate;` — Delegate for checking the playhead time.
- L277 _private member_ `FOnSetTime OnSetCurrentTimeDelegate;` — Delegate for setting the current playhead time.
- L280 _private member_ `FOnGetDoubleRange OnGetViewRangeDelegate;` — Delegate for getting the view range.
- L283 _private member_ `FOnSetDoubleRange OnSetViewRangeDelegate;` — Delegate for setting the view range.
- L286 _private member_ `FOnGetIntArrayRange OnGetFrameBufferRanges;` — Retrieve the buffered frame range.
- L289 _private member_ `FOnGetTime OnGetSelectionStartTimeDelegate;` — Delegate for getting the selection start.
- L292 _private member_ `FOnSetTime OnSetSelectionStartTimeDelegate;` — Delegate for setting the selection start.
- L295 _private member_ `FOnGetTime OnGetSelectionEndTimeDelegate;` — Delegate for getting the selection end.
- L298 _private member_ `FOnSetTime OnSetSelectionEndTimeDelegate;` — Delegate for setting the selection start.
- L301 _private member_ `FOnGetFrame OnGetFrameRate;` — Retrieve the frame rate.
- L304 _private member_ `FSimpleDelegate OnScrubbingStartDelegate;` — Delegate triggered when scrubbing starts.
- L307 _private member_ `FSimpleDelegate OnScrubbingEndDelegate;` — Delegate triggered when scrubbing stops.
- L310 _private member_ `TSharedPtr<FFrameNumberInterface> NumberInterface;` — The number interface for displaying the correct frame format.
- L313 _private member_ `EFrameNumberDisplayFormats DisplayFormat = EFrameNumberDisplayFormats::NonDropFrameTimecode;` — The format to display/edit values in.
- L316 _private member_ `TSharedPtr<SWidget> TimeSlider;` — Holds the LiveLinkHubTimeSlider widget.
- L326 _private member_ `uint32 KeyDownCounter[2] = { 0, 0 };` — Keeps track of how many frames since the left and right key have been pressed.
- L329 _private member_ `bool KeyDown[2] = { 0, 0 };` — Keeps track of whether the left or right key is being pressed.
- L332 _private member_ `uint8 KeyDownScrubCounter = 0;` — Counter used to advance the recording while holding down left or right key.
- L335 _private member_ `float CachedPlayRate = 1.0f;` — Cached value of the recording playback rate.
- L338 _private member_ `static constexpr uint8 FramesBetweenKeyDownScrub = 3;` — Number of frames to wait between advancing the frame while a key is held down.
- L341 _private member_ `static constexpr uint8 MinFramesToBeginScrubbing = 30;` — Minimum number of frames to consider a frame pressed as being held down for scrubbing (vs. tapping it for a single frame jump).

#### enum `SLiveLinkHubPlaybackWidget::EScrubDirection`  
`enum class EScrubDirection : uint8`  
_L319-323_
- desc: Helper enum to track KeyDown state.
- L321 _public enumerator_ `Left`
- L322 _public enumerator_ `Right`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnGetChecked);`
- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetChecked, bool);`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal(FQualifiedFrameTime, FOnGetTime);`
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetTime, FQualifiedFrameTime);`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal(FFrameRate, FOnGetFrame);`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetDoubleRange, const TRange<double>&) DECLARE_DELEGATE_RetVal(TRange<double>, FOnGetDoubleRange) DECLARE_DELEGATE_RetVal(UE::LiveLinkHub::RangeHelpers::Private::TRangeArray<int32>, FOnGetIntArrayRange) DECLARE_DELEGATE_RetVal(float, FOnGetFloat) DECLARE_DELEGATE_OneParam(FOnSetFloat, float) DECLARE_DELEGATE(FOnButtonPressed);`
- L27 _delegate_ `DECLARE_DELEGATE_RetVal(TRange<double>, FOnGetDoubleRange) DECLARE_DELEGATE_RetVal(UE::LiveLinkHub::RangeHelpers::Private::TRangeArray<int32>, FOnGetIntArrayRange) DECLARE_DELEGATE_RetVal(float, FOnGetFloat) DECLARE_DELEGATE_OneParam(FOnSetFloat, float) DECLARE_DELEGATE(FOnButtonPressed);`
- L28 _delegate_ `DECLARE_DELEGATE_RetVal(UE::LiveLinkHub::RangeHelpers::Private::TRangeArray<int32>, FOnGetIntArrayRange) DECLARE_DELEGATE_RetVal(float, FOnGetFloat) DECLARE_DELEGATE_OneParam(FOnSetFloat, float) DECLARE_DELEGATE(FOnButtonPressed);`
- L29 _delegate_ `DECLARE_DELEGATE_RetVal(float, FOnGetFloat) DECLARE_DELEGATE_OneParam(FOnSetFloat, float) DECLARE_DELEGATE(FOnButtonPressed);`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetFloat, float) DECLARE_DELEGATE(FOnButtonPressed);`
- L32 _delegate_ `DECLARE_DELEGATE(FOnButtonPressed);`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/UI/Widgets/SLiveLinkHubSettings.h` (Private)


#### class `SLiveLinkHubSettings`  
`class SLiveLinkHubSettings : public SCompoundWidget`  
_L27-184_
- inherits: `SCompoundWidget`
- desc: LiveLinkHub Settings widget.
- L31 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkHubSettings)`
- L32 _public prototype_ `SLATE_END_ARGS() const FName SettingsTabId = "Li`
- L40 _public function_ `void Construct(const FArguments& InArgs)` — Create the settings combo button.
- L79 _public function_ `~SLiveLinkHubSettings()`
- L85 _public function_ `void UnregisterSettings()` — Unregister all settings except the ones that are relevant to the hub.
- L120 _public function_ `TSharedRef<SWidget> OnSettingsComboBoxOpen() const` — Handler called when the combo button is clicked.
- L156 _public function_ `TSharedRef<SDockTab> SpawnSettingsTab(const FSpawnTabArgs& SpawnTabArgs)` — Creates the settings viewer tab.
- L183 _private member_ `TSharedPtr<ISettingsEditorModel> SettingsEditorModel;` — Holds the view state for the settings.

#### Free symbols / members of external scopes

- L22 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkHubSettings"`
- L46 _function_ `SettingsEditorModule->SetShouldRegisterSettingCallback(FShouldRegisterSettingsDelegate::CreateLambda([](UDeveloperSettings* Settings) { return false; }));` (scope `SLiveLinkHubSettings::Construct`)
- L124 _function_ `` (scope `SLiveLinkHubSettings::OnSettingsComboBoxOpen`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/UI/Widgets/SLiveLinkHubTimeSlider.h` (Private)


#### class `SLiveLinkHubTimeSlider`  
`class SLiveLinkHubTimeSlider : public SSimpleTimeSlider`  
_L12-40_
- inherits: `SSimpleTimeSlider`
- desc: Live link hub slider for scrubbing playback and reporting the playhead position. Additionally, it supports displaying currently buffered frames.
- L16 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkHubTimeSlider)`
- L19 _public prototype_ `SLATE_ATTRIBUTE(UE::LiveLinkHub::RangeHelpers::Private::TRangeArray<double>, BufferRange) SLATE_ARGUMENT(SSimpleTimeSlider::FArguments, BaseArgs) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The buffered frame size.
- L32 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L35 _protected prototype_ `void OnPaintExtendedSlider(bool bMirrorLabels, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const;` — Paint live link hub specific slider details.
- L39 _private member_ `TAttribute<UE::LiveLinkHub::RangeHelpers::Private::TRangeArray<double>> BufferRanges;` — The frame buffer range to render.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/UI/Widgets/SLiveLinkHubTopologyModeSwitcher.h` (Private)


#### class `SLiveLinkHubTopologyModeSwitcher`  
`class SLiveLinkHubTopologyModeSwitcher : public SCompoundWidget`  
_L18-186_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkHubTopologyModeSwitcher)`
- L23 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L80 _public function_ `virtual ~SLiveLinkHubTopologyModeSwitcher()`
- L90 _private function_ `FReply OnModeClicked()` — Handles toggling the topology mode.
- L97 _private function_ `void OnModeChanged(ELiveLinkTopologyMode Mode)` — Handles updating the button's text and tooltip when the topology mode changed.
- L111 _private function_ `const FSlateBrush* GetModeIcon() const`
- L124 _private function_ `TSharedRef<SWidget> OnGetMenuContent() const`
- L170 _private function_ `static FText GetModeTooltip(ELiveLinkTopologyMode InMode)` — Returns the tooltip for a mode.
- L179 _private member_ `TSharedPtr<SComboButton> ModeButton;` — Button that's responsible for switching the topology mode of the app.
- L181 _private member_ `TSharedPtr<STextBlock> ButtonContent;` — Text indicating the current mode.
- L183 _private member_ `const FSlateBrush* HubModeIcon = nullptr;` — Icon for Hub mode.
- L185 _private member_ `const FSlateBrush* SpokeModeIcon = nullptr;` — Icon for Spoke mode.

#### Free symbols / members of external scopes

- L16 _macro_ `#define LOCTEXT_NAMESPACE "LiveLinkHubTopologyModeSwitcher"`
- L136 _function_ `` (scope `SLiveLinkHubTopologyModeSwitcher::OnGetMenuContent`)
- L141 _function_ `SpokeAction.CanExecuteAction = FCanExecuteAction::CreateLambda([bCanSetSpokeMode]() { return bCanSetSpokeMode; });` (scope `SLiveLinkHubTopologyModeSwitcher::OnGetMenuContent`)
- L145 _function_ `HubAction.CanExecuteAction = FCanExecuteAction::CreateLambda([bCanSetHubMode]() { return bCanSetHubMode; });` (scope `SLiveLinkHubTopologyModeSwitcher::OnGetMenuContent`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/UI/Widgets/SLiveLinkRecordingSessionInfo.h` (Private)


#### class `SLiveLinkRecordingSessionInfo`  
`class SLiveLinkRecordingSessionInfo : public SCompoundWidget`  
_L9-16_
- inherits: `SCompoundWidget`
- desc: Display and edit the session name, slate name, take number.
- L12 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkRecordingSessionInfo)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/UI/Widgets/SLiveLinkTimecode.h` (Private)


#### class `SLiveLinkTimecode`  
`class SLiveLinkTimecode : public SCompoundWidget`  
_L12-37_
- inherits: `SCompoundWidget`
- desc: Utility class to display timecode status on the menu bar. Provides user with a drop down of supported time code values including subjects that are in the Live Link session.
- L16 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkTimecode)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The tab's content
- L27 _private prototype_ `FSlateColor GetIconColor() const;` — Returns the color of the icon depending on whether timecode and genlock is set up correctly.
- L30 _private prototype_ `FSlateColor GetStatusColor() const;` — Indicate the status of the time code send status
- L33 _private prototype_ `FText GetTimecodeTooltip() const;` — Gets the tooltip text for the time code widget
- L36 _private prototype_ `FReply OnClickOpenSettings() const;` — Open project settings to the Time & Sync section.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/UI/Window/LiveLinkHubWindowController.h` (Private)


#### class `FLiveLinkHubWindowController`  
`class FLiveLinkHubWindowController : public TSharedFromThis<FLiveLinkHubWindowController>, public IEditorMainFrameProvider`  
_L13-44_
- inherits: `TSharedFromThis<FLiveLinkHubWindowController>,IEditorMainFrameProvider`
- desc: Responsible for creating the Slate window for the hub.
- L16 _public prototype_ `FLiveLinkHubWindowController();`
- L17 _public prototype_ `~FLiveLinkHubWindowController();`
- L20 _public function_ `TSharedPtr<SWindow> GetRootWindow() const` — Get the root window.
- L22 _public prototype_ `void RestoreLayout(TSharedPtr<FAssetEditorToolkit> AssetEditorToolkit);` — Restore the window's layout from a config.
- L25 _public function_ `virtual bool IsRequestingMainFrameControl() const`
- L26 _public prototype_ `virtual FMainFrameWindowOverrides GetDesiredWindowConfiguration() const;`
- L27 _public prototype_ `virtual TSharedRef<SWidget> CreateMainFrameContentWidget() const;`
- L32 _private prototype_ `TSharedRef<SWindow> CreateWindow();` — Create the main window.
- L34 _private prototype_ `void CloseRootWindowOverride(const TSharedRef<SWindow>& Window);` — Override to handle confirming if the user wants to quit.
- L36 _private prototype_ `void OnWindowClosed(const TSharedRef<SWindow>& Window);` — Window closed handler.
- L39 _private member_ `TSharedPtr<SWindow> RootWindow;` — The main window being managed
- L41 _private member_ `TSharedPtr<FTabManager::FLayout> DefaultLayout;` — Default layout for the app.
- L43 _private member_ `static const FName LiveLinkHubTabId;` — Tab ID of the main LiveLinkHub

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/UI/Window/ModalWindowManager.h` (Private)


#### class `FModalWindowManager`  
`class FModalWindowManager`  
_L15-45_
- desc: Manages "fake" modal windows because the hub cannot use "true" modal windows. True modal windows block the main thread which is not an option because the hub must remain responsive.
- L19 _public prototype_ `FModalWindowManager(const TSharedRef<SWindow>& InMainWindow);`
- L20 _public prototype_ `~FModalWindowManager();`
- L23 _public prototype_ `void ShowFakeModalWindow(const TSharedRef<SCustomDialog>& Dialog);` — Show a modal window and add it to our window stack.
- L25 _public prototype_ `void PushWindow(const TSharedRef<SWindow>& Window);` — Called when a new fake modal window should be tracked on top of all windows.
- L27 _public prototype_ `void PopWindow();` — Called when a fake modal window should no longer be tracked, i.e. when it is closed.
- L31 _private member_ `TArray<TWeakPtr<SWindow>> WindowStack;` — Holds the modal windows.
- L34 _private member_ `bool bRootWindowIsValid = true;` — Modal windows can only be added when this is true
- L37 _private prototype_ `void OnMainWindowActivated();` — Handler called when the main window is activated.
- L40 _private prototype_ `void OnWindowClosed(const TSharedRef<SWindow>& InWindow);` — Handler called when the main window is closed, used for destroying all windows in the stack.
- L44 _private member_ `TWeakPtr<SWindow> MainWindow;` — Weak pointer to the main window of the app.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Public/ILiveLinkHubClientsModel.h` (Public)


#### struct `FLiveLinkHubDiscoveredClientInfo`  
`struct FLiveLinkHubDiscoveredClientInfo`  
_L20-32_
- desc: Information about a discovered client.
- L23 _public member_ `ELiveLinkTopologyMode TopologyMode = ELiveLinkTopologyMode::UnrealClient;` — Topology of the Client.
- L25 _public member_ `FString IP;` — IP of the client.
- L27 _public member_ `FString Hostname;` — Hostname of the client.
- L29 _public member_ `FString LevelName;` — Current level.
- L31 _public member_ `FString ProjectName;` — Project that the client is in.

#### struct `FLiveLinkHubClientId`  
`struct FLiveLinkHubClientId`  
_L38-77_
- reflection: `USTRUCT()`
- desc: Identifier for a UE client receiving data from the hub.
- L43 _public prototype_ `FLiveLinkHubClientId() = default;` — Default constructor, should only be used by the reflection code.
- L45 _public function_ `static FLiveLinkHubClientId NewId()`
- L52 _public function_ `bool IsValid() const`
- L63 _public function_ `bool operator==(const FLiveLinkHubClientId& Other) const`
- L68 _public function_ `FString ToString() const`
- L76 _private member_ `FGuid Guid;` — `UPROPERTY()` — Unique identifier for this client.

#### class `ILiveLinkHubClientsModel`  
`class ILiveLinkHubClientsModel : public IModularFeature`  
_L81-177_
- inherits: `IModularFeature`
- desc: Exposes queries and operations for Unreal Editor clients connected to the local LLH instance.
- L94 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnClientEvent, FLiveLinkHubClientId, EClientEventType);`
- L97 _public function_ `static FName GetModularFeatureName()` — Name of the modular feature.
- L104 _public function_ `static ILiveLinkHubClientsModel* Get()` — Convenience accessor for modular feature implementation.
- L114 _public function_ `static ILiveLinkHubClientsModel& GetChecked()` — Convenience accessor for modular feature implementation.
- L122 _public prototype_ `virtual ~ILiveLinkHubClientsModel() = default;`
- L125 _public prototype_ `virtual FOnClientEvent& OnClientEvent() = 0;` — Delegate used to get noticed about changes to the client list.
- L128 _public prototype_ `virtual FText GetClientStatus(FLiveLinkHubClientId Client) const = 0;` — Get the status text of a client.
- L131 _public prototype_ `virtual TArray<FLiveLinkHubClientId> GetSessionClients() const = 0;` — Get the list of clients that should be displayed in the clients panel according to the current session config.
- L134 _public prototype_ `virtual TArray<FLiveLinkHubClientId> GetDiscoveredClients() const = 0;` — Get the list of clients discovered by the hub.
- L137 _public prototype_ `virtual TOptional<FLiveLinkHubDiscoveredClientInfo> GetDiscoveredClientInfo(FLiveLinkHubClientId InClient) const = 0;` — Get information about a discovered client.
- L140 _public prototype_ `virtual TOptional<FLiveLinkHubUEClientInfo> GetClientInfo(FLiveLinkHubClientId InClient) const = 0;` — Get information about a given client given its address.
- L143 _public prototype_ `virtual FText GetClientDisplayName(FLiveLinkHubClientId InClient) const = 0;` — Get the name of a client.
- L146 _public prototype_ `virtual void ConnectTo(FLiveLinkHubClientId InClient) = 0;` — Send a connection message to this discovered client.
- L149 _public prototype_ `virtual bool IsClientEnabled(FLiveLinkHubClientId InClient) const = 0;` — Get whether a client should receive livelink data.
- L152 _public prototype_ `virtual bool IsClientConnected(FLiveLinkHubClientId InClient) const = 0;` — Get whether a client is connected to the hub.
- L155 _public prototype_ `virtual void SetClientEnabled(FLiveLinkHubClientId InClient, bool bInEnable) = 0;` — Set whether a client should receive livelink data.
- L158 _public prototype_ `virtual bool IsSubjectEnabled(FLiveLinkHubClientId InClient, FName SubjectName) const = 0;` — Get whether a subject is enabled on a given client.
- L161 _public prototype_ `virtual void SetSubjectEnabled(FLiveLinkHubClientId InClient, FName SubjectName, bool bInEnable) = 0;` — Set whether a subject should receive livelink data.
- L164 _public prototype_ `virtual void RequestAuxiliaryChannel( FLiveLinkHubClientId InClientId, FMessageEndpoint& InAuxEndpoint, UScriptStruct* InRequestTypeInfo, FLiveLinkHubAuxChannelRequestMessage& InRequest ) = 0;` — Request to open an auxiliary endpoint with a client.
- L173 _public function_ `template<typename RequestType UE_REQUIRES(std::is_base_of_v<FLiveLinkHubAuxChannelRequestMessage, RequestType>)> void RequestAuxiliaryChannel(FLiveLinkHubClientId InClientId, FMessageEndpoint& InAuxEndpoint, RequestType& InRequest)` — Request to open an auxiliary endpoint with a client.

#### enum `ILiveLinkHubClientsModel::EClientEventType`  
`enum class EClientEventType`  
_L85-92_
- desc: Types of client updates.
- L87 _public enumerator_ `Discovered` — UE client was discovered by the hub.
- L88 _public enumerator_ `Disconnected` — Connection was lost with a client.
- L89 _public enumerator_ `Connected` — Client goes from Discovered -> Connected
- L90 _public enumerator_ `Reestablished` — Connection was restored with a previously disconnected client.
- L91 _public enumerator_ `Modified` — Information about a given client has changed (ie. level has changed).

#### Free symbols / members of external scopes

- L58 _function_ `friend uint32 GetTypeHash(FLiveLinkHubClientId Id)` — Get the hash of this ID.
- L94 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnClientEvent, FLiveLinkHubClientId, EClientEventType);`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Public/ILiveLinkHubComponent.h` (Public)


#### struct `FLiveLinkHubComponentInitParams`  
`struct UE_DEPRECATED(5.6, "Customize LiveLinkHub by adding layouts instead.") FLiveLinkHubComponentInitParams`  
_L11-23_
- L14 _public member_ `TSharedRef<SWindow> Window;` — LiveLinkHub's main Window.
- L17 _public member_ `TSharedRef<FTabManager::FStack> MainStack;` — The root area of the main window layout. Add tabs to this.
- L19 _public function_ `FLiveLinkHubComponentInitParams(TSharedRef<SWindow> InWindow, TSharedRef<FTabManager::FStack> InMainStack) : Window(MoveTemp(InWindow)) , MainStack(MoveTemp(InMainStack))`

#### class `ILiveLinkHubComponent`  
`class UE_DEPRECATED(5.6, "Customize LiveLinkHub by adding layouts instead.") ILiveLinkHubComponent : public IModularFeature`  
_L27-39_
- inherits: `IModularFeature`
- desc: Provides an interface for elements that wish to add additional content (tabs) to LiveLinkHub.
- L31 _public member_ `static const FName ModularFeatureName;` — Name of the modular feature.
- L33 _public prototype_ `virtual ~ILiveLinkHubComponent() = default;`
- L37 _public prototype_ `virtual void Init(const FLiveLinkHubComponentInitParams& Params) = 0;` — Initialises the component, e.g. registering tab spawners, etc.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Public/ILiveLinkHubModule.h` (Public)


#### class `ILiveLinkHubModule`  
`class ILiveLinkHubModule : public IModuleInterface`  
_L8-16_
- inherits: `IModuleInterface`
- L12 _public function_ `static FString GetLiveLinkHubNamingTokensNamespace()` — Retrieve the namespace for Live Link Hub naming tokens.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Public/ILiveLinkRecordingSession.h` (Public)
_(no declarations extracted)_

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Public/ILiveLinkRecordingSessionInfo.h` (Public)


#### Free symbols / members of external scopes

- L10 _typedef_ `using ILiveLinkRecordingSessionInfo = ILiveLinkRecordingSession;` — `UE_DEPRECATED(5.8, "Use ILiveLinkRecordingSession directly instead.")`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Public/LiveLinkHubApplicationBase.h` (Public)


#### class `FLiveLinkHubApplicationBase`  
`class FLiveLinkHubApplicationBase : public FWorkflowCentricApplication`  
_L26-36_
- inherits: `FWorkflowCentricApplication`
- desc: Base class for the live link hub application, meant to expose a limited interface to modes that extend FLiveLinkHubApplicationMode.
- L29 _public prototype_ `virtual ~FLiveLinkHubApplicationBase() = default;`
- L32 _public prototype_ `virtual void AddLiveLinkHubApplicationMode(FName ModeName, TSharedRef<FLiveLinkHubApplicationMode> Mode) = 0;` — Add a LiveLinkHub application mode.
- L35 _public prototype_ `virtual void PushTabFactories(const class FWorkflowAllowedTabSet& FactorySetToPush, TSharedPtr<FLiveLinkHubApplicationMode> ApplicationMode) = 0;` — Push tab factories for the given mode.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LiveLinkHub` (scope `UE`)
- L10 _variable_ `static const FName LiveLinkStyleName = "Li` (scope `UE::LiveLinkHub`)
- L13 _variable_ `static const FName SourcesTabId = "So` (scope `UE::LiveLinkHub`)
- L14 _variable_ `static const FName SourceDetailsTabId = "So` (scope `UE::LiveLinkHub`)
- L15 _variable_ `static const FName SubjectsTabId = "Su` (scope `UE::LiveLinkHub`)
- L16 _variable_ `static const FName SubjectDetailsTabId = "Su` (scope `UE::LiveLinkHub`)
- L17 _variable_ `static const FName PlaybackTabId = "Pl` (scope `UE::LiveLinkHub`)
- L18 _variable_ `static const FName RecordingListTabId = "Re` (scope `UE::LiveLinkHub`)
- L19 _variable_ `static const FName ClientsTabId = "Cl` (scope `UE::LiveLinkHub`)
- L20 _variable_ `static const FName ClientDetailsTabId = "Cl` (scope `UE::LiveLinkHub`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Public/LiveLinkHubApplicationMode.h` (Public)


#### class `ILiveLinkHubApplicationModeFactory`  
`class ILiveLinkHubApplicationModeFactory : public IModularFeature`  
_L20-28_
- inherits: `IModularFeature`
- desc: Factory used by external plugins to register custom LiveLinkHub layouts.
- L24 _public member_ `static const FName ModularFeatureName;` — Name of the modular feature.
- L27 _public prototype_ `virtual TSharedRef<class FLiveLinkHubApplicationMode> CreateLiveLinkHubAppMode(TSharedPtr<FLiveLinkHubApplicationBase> InApp) = 0;` — Instantiate an application mode so LiveLinkHub can register it and display it in its Layout Selector.

#### class `FLiveLinkHubApplicationMode`  
`class FLiveLinkHubApplicationMode : public FApplicationMode`  
_L30-113_
- inherits: `FApplicationMode`
- L34 _public member_ `static const FName FileMenuExtensionPoint;` — Name of the File menu extension point. Can be used to insert menus before/after in the main menu bar.
- L37 _public function_ `virtual FSlateIcon GetModeIcon() const` — Get the icon for this mode.
- L40 _public function_ `const FText& GetDisplayName() const` — Get the display name for this mode
- L43 _public prototype_ `TArray<TSharedRef<SWidget>> GetToolbarWidgets();` — Method used to gather the toolbar widgets that should be visible when this mode is active.
- L46 _public function_ `FName GetLayoutName()` — Get the name of this layout.
- L52 _public function_ `FString GetLayoutIni() const` — Get the filename of this mode's layout ini.
- L58 _public function_ `TSharedPtr<FTabManager::FLayout> GetTabLayout() const` — Get the tab manager layout ptr.
- L64 _public function_ `virtual bool IsUserLayout() const` — Returns whether this mode is a user layout.
- L71 _public function_ `virtual TSharedPtr<FWorkspaceItem> GetCustomWindowMenuCategory() const` — Override to provide a custom Window menu section for this mode's tabs instead of the shared "Live Link Hub" section. Return nullptr to use the shared section (default behaviour).
- L74 _public function_ `virtual TArray<TSharedRef<SWidget>> GetToolbarWidgets_Impl()` — Implement in a child class in order to have status bar extensions show up when the mode is active.
- L78 _public function_ `virtual TArray<TSharedRef<SWidget>> GetStatusBarWidgets_Impl()` — Get widgets that should appear in the status bar.
- L81 _protected prototype_ `FLiveLinkHubApplicationMode(FName InApplicationMode, FText InDisplayName, TSharedPtr<FLiveLinkHubApplicationBase> InApp);`
- L84 _protected prototype_ `virtual void PostActivateMode() override;`
- L85 _protected prototype_ `virtual void PreDeactivateMode() override;`
- L86 _protected function_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override`
- L102 _protected member_ `TWeakPtr<FLiveLinkHubApplicationBase> WeakApp;` — The application that hosts this app mode.
- L105 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — Set of spawnable tabs in the mode
- L109 _private member_ `FText DisplayName;` — Display name for this mode.
- L112 _private member_ `bool bRegisteredTabFactories = false;` — Keeps track of whether or not the tab factories were registered, so we don't end up with duplicate tab spawners for this mode.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LIVELINKHUB_API`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Public/LiveLinkHubSessionExtraData.h` (Public)
_(no declarations extracted)_
