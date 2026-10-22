# Plugins / MultiUserClient

- module root: `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient`
- headers: 134; symbols: 2416
- symbol kinds: class=111, delegate=38, enum=28, enumerator=102, externvar=4, function=299, macro=1, member=546, namespace=480, prototype=747, struct=47, typedef=12, variable=1
- PrivateDependencyModuleNames: ApplicationCore, Concert, ConcertClient, ConcertClientSharedSlate, ConcertReplicationScripting, ConcertSharedSlate, ConcertSyncClient, ConcertSyncCore, ConcertTransport, ContentBrowser, Core, DesktopPlatform, EditorFramework, EditorStyle, Engine, FileSandboxUI, InputCore, JsonUtilities, MessageLog, MultiUserReplicationEditor, Projects, PropertyEditor, Sequencer, Settings, Slate, SlateCore, SourceControl, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure, WorldBrowser
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/ConcertWorkspaceUI.h` (Private)


#### class `FConcertWorkspaceUI`  
`class FConcertWorkspaceUI : public TSharedFromThis<FConcertWorkspaceUI>`  
_L26-183_
- inherits: `TSharedFromThis<FConcertWorkspaceUI>`
- desc: Concert Client Workspace UI
- L29 _private member_ `static FName ConcertSourceControlMenuOwnerName;` — Name of menu extensions going into source control (bottom-right)
- L31 _private member_ `static FName ConcertPersistSessionChangesMenuEntryName;` — Name for menu entry in source control that will persist changes
- L34 _private member_ `static FName AssetActionSectionNameToExtend;` — Name of UE section in asset context
- L36 _private member_ `static FName ConcertAssetActionsMenuOwnerName;` — Name of menu extensions going to asset context menu
- L38 _private member_ `static FName ConcertAssetActionsSectionName;` — Name of the new section in the asset action menu
- L40 _private member_ `static FName ConcertAssetActionsDynamicEntryName;` — Name of entry added to asset context menu
- L42 _private member_ `static FName ConcertAssetActionsSubMenuName;` — Name of submenu added by ConcertAssetActionsDynamicEntryName
- L45 _public prototype_ `FConcertWorkspaceUI();`
- L46 _public prototype_ `~FConcertWorkspaceUI();`
- L49 _public prototype_ `void InstallWorkspaceExtensions(TWeakPtr<IConcertClientWorkspace> InClientWorkspace, TWeakPtr<IConcertSyncClient> InSyncClient);` — Install UI extensions for the workspace UI.
- L52 _public prototype_ `void UninstallWorspaceExtensions();` — Uninstall UI extensions for the workspace UI.
- L55 _public prototype_ `bool HasSessionChanges() const;` — Return true if the session contains changes yet to be persisted locally.
- L61 _public prototype_ `bool PromptPersistSessionChanges();` — Prompt User on which workspace file changes should be persisted and prepared for source control submission. @return true if the user accepted to persist, false if it was canceled.
- L71 _private prototype_ `void OnEndFrame();` — On end frame callback.
- L74 _private prototype_ `bool SubmitChangelist(const FConcertPersistCommand& PersistCommand, FText& OperationMessage);` — Check out and optionally submit files to source control.
- L77 _private prototype_ `FText GetUserDescriptionText(const FGuid& ClientId) const;` — Get a text description for the specified client that can be displayed in UI.
- L78 _private prototype_ `FText GetUserDescriptionText(const FConcertClientInfo& ClientInfo) const;`
- L81 _private prototype_ `FLinearColor GetUserAvatarColor(const FGuid& ClientId) const;` — Returns the avatar color corresponding to the specified client Id (including this client).
- L84 _private prototype_ `FGuid GetWorkspaceLockId() const;` — Get the local workspace's lock id.
- L87 _private prototype_ `FGuid GetResourceLockId(const FName InResourceName) const;` — Get the id of the client who owns the lock on a given resource.
- L92 _private prototype_ `bool CanLockResources(TArray<FName> InResourceNames) const;` — @return whether a list of resources can be locked.
- L97 _private prototype_ `bool CanUnlockResources(TArray<FName> InResourceNames) const;` — @return whether a list of resources can be unlocked.
- L100 _private prototype_ `void ExecuteLockResources(TArray<FName> InResourceNames);` — Lock a list of resources.
- L105 _private prototype_ `void ExecuteUnlockResources(TArray<FName> InResourceNames);` — Unlock a list of resources.
- L110 _private prototype_ `void ExecuteViewHistory(TArray<FName> InResourceNames);` — View the history of the specified recourses.
- L119 _private prototype_ `bool IsAssetModifiedByOtherClients(const FName& AssetName, int32* OutOtherClientsWithModifNum = nullptr, TArray<FConcertClientInfo>* OutOtherClientsWithModifInfo = nullptr, int32 OtherClientsWithModifMaxFetchNum = 0) const;` — Returns true if the specified asset was modified by another user than the one associated to this workspace and optionally return the information about the last client who modified the resource. @param[in] AssetName The name of the asset to look up. @param[out] OutOtherClientsWithModifNum If not null, will contain how many other client(s) have modified the specified asset. @param[out] OutOtherClientsWithModifInfo If not null, will contain the other client who modified the asset, up to OtherClientsWithModifMaxFetchNum. @param[in] OtherClientsWithModifMaxFetchNum The maximum number of client info to store in OutOtherClientsWithModifInfo if the latter is not null.
- L122 _private prototype_ `void OnMarkPackageDirty(UPackage* InPackage, bool bDirty);` — Delegate called when a package is marked dirty.
- L125 _private prototype_ `void ExtendToolbarWithSourceControlMenu();` — Extends the toolbar with MU source control options
- L127 _private prototype_ `void ExtendAssetContextMenuOptions();` — Extends the content browser asset context menu with MU options.
- L129 _private prototype_ `void GenerateConcertAssetContextMenu(FMenuBuilder& MenuBuilder, TArray<FName> AssetObjectPaths);` — Called to generate concert asset context menu.
- L132 _private prototype_ `TSharedRef<SWidget> OnGenerateAssetViewLockStateIcons(const FAssetData& AssetData);` — Delegate to generate an extra lock state indicator on content browser assets.
- L135 _private prototype_ `TSharedRef<SWidget> OnGenerateAssetViewLockStateTooltip(const FAssetData& AssetData);` — Delegate to generate extra lock state tooltip on content browser assets.
- L138 _private prototype_ `TSharedRef<SWidget> OnGenerateAssetViewModifiedByOtherIcon(const FAssetData& AssetData);` — Delegate to generate an extra "modified by other" icon on content browser assets.
- L141 _private prototype_ `TSharedRef<SWidget> OnGenerateAssetViewModifiedByOtherTooltip(const FAssetData& AssetData);` — Delegate to generate the "modified by..." tooltip  on content browser assets.
- L149 _private prototype_ `void OnPreSequencerInit(TSharedRef<ISequencer> InSequencer, TSharedRef<ISequencerObjectChangeListener> InObjectChangeListener, const FSequencerInitParams& InitParams);` — Handle the initialization hooks for a new sequencer instance @param InSequencer	The sequencer that has just been created. Should not hold persistent shared references. @param InitParams	The initialization parameters the sequencer is going to be initialized with.
- L152 _private prototype_ `static TSharedRef<SDockTab> CreateHistoryTab(const FName& ResourceName, const TSharedRef<IConcertSyncClient>& SyncClient);` — Create an asset history tab filtered with a resource name.
- L155 _private member_ `TWeakPtr<IConcertClientWorkspace> ClientWorkspace;` — Workspace this is a view of.
- L158 _private member_ `TWeakPtr<SNotificationItem> EditLockedNotificationWeakPtr;` — Ongoing workspace lock notification, if any.
- L161 _private member_ `TWeakPtr<IConcertSyncClient> SyncClient;` — The sync client for this view.
- L164 _private member_ `FDelegateHandle ContentBrowserAssetExtenderDelegateHandle;` — Delegate handle for context menu extension.
- L167 _private member_ `TArray<FDelegateHandle> ContentBrowserAssetExtraStateDelegateHandles;` — Delegate handles for asset lock state indicator extensions.
- L170 _private member_ `FDelegateHandle SourceControlExtensionDelegateHandle;` — Delegate handle for source control menu extension.
- L173 _private member_ `FDelegateHandle OnPreSequencerInitHandle;` — Delegate handle for the global pre sequencer init event registered with the sequencer module
- L176 _private member_ `TSharedPtr<FTabManager::FLayout> AssetHistoryLayout;` — Asset history layout for asset history window tabs.
- L179 _private member_ `TSharedPtr<FExtender> ToolbarExtender;` — Toolbar extender for sequencer toolbar
- L182 _private member_ `TSet<FName> PerFramePackageDirtyList;` — Set to track dirty packages per frame.

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Misc/GameVisibilityColumnToggler.h` (Private)


#### class `UE::MultiUserClient::FGameVisibilityColumnToggler`  
`class FGameVisibilityColumnToggler : FNoncopyable`  
_L20-37_
- inherits: `FNoncopyable`
- desc: Toggles the GameVisibility column in the Levels tab when joining a MU session. This is done to improve the UX of VP users: it allows them to show & hide levels on connected clients launched with -game, such as nDisplay nodes.
- L24 _public prototype_ `FGameVisibilityColumnToggler(TSharedRef<IConcertSyncClient> InMultiUserClient);`
- L25 _public prototype_ `~FGameVisibilityColumnToggler();`
- L30 _private member_ `TSharedRef<IConcertSyncClient> MultiUserClient;` — The client to which we listen for session changes to
- L33 _private member_ `bool bHideVisibilityColumnOnSessionLeave = true;` — This is false if the visibility column had been shown when the client joined the session.
- L35 _private prototype_ `void OnStartSession(const IConcertSyncClient* Client);`
- L36 _private prototype_ `void OnStopSession(const IConcertSyncClient* Client);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/MultiUserClientUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace MultiUserClientUtils`
- L11 _prototype_ `bool HasServerCompatibleCommunicationPluginEnabled();` (scope `MultiUserClientUtils`) — Checks if the client has at least one server compatible transport plugin enabled, for example, 'UdpMessaging'.
- L14 _prototype_ `TArray<FString> GetServerCompatibleCommunicationPlugins();` (scope `MultiUserClientUtils`) — Returns the list of compatible transport plugins usable by the client to communicate with the server, for example 'UdpMessaging'.
- L17 _prototype_ `FText GetNoCompatibleCommunicationPluginEnabledText();` (scope `MultiUserClientUtils`) — Returns a text saying that a communication plugin is missing to get Multi-User working.
- L20 _prototype_ `void LogNoCompatibleCommunicationPluginEnabled();` (scope `MultiUserClientUtils`) — Outputs a log saying that a communication plugin is missing to get Multi-User working.

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/MultiUserReplicationStyle.h` (Private)


#### class `UE::MultiUserClient::FMultiUserReplicationStyle`  
`class FMultiUserReplicationStyle`  
_L17-32_
- desc: Style settings specifically for all replication widgets. Separate class to make it more straight forward to move to a separate module (there are no specific plans for that only future proofing).
- L21 _public prototype_ `static void Initialize();`
- L22 _public prototype_ `static void Shutdown();`
- L24 _public prototype_ `static TSharedPtr<ISlateStyle> Get();`
- L26 _public prototype_ `static FName GetStyleSetName();`
- L30 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L31 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Authority/AuthorityChangeTracker.h` (Private)


#### class `UE::MultiUserClient::Replication::FAuthorityChangeTracker`  
`class FAuthorityChangeTracker`  
_L22-73_
- desc: Keeps track of authority changes the local editor instance makes to a client.
- L30 _public prototype_ `FAuthorityChangeTracker(const FGuid& InClientId, const IClientAuthoritySynchronizer& InAuthoritySynchronizer UE_LIFETIMEBOUND, FGlobalAuthorityCache& InAuthorityCache UE_LIFETIMEBOUND);` — @param InClientId The endpoint ID of the owning client @param InAuthoritySynchronizer Used to get the authority state on the server. The caller ensures it outlives the constructed instance. @param InAuthorityCache Used to predict authority conflicts. The caller ensures it outlives the constructed instance.
- L31 _public prototype_ `~FAuthorityChangeTracker();`
- L34 _public prototype_ `void SetAuthorityIfAllowed(TConstArrayView<FSoftObjectPath> ObjectPaths, bool bNewAuthorityState);` — Marks that the authority should be changed to bNewAuthorityState.
- L36 _public prototype_ `void ClearAuthorityChange(TConstArrayView<FSoftObjectPath> ObjectPaths);` — Reverts any local, unsubmitted changes made for the ObjectPaths.
- L39 _public prototype_ `void RefreshChanges();` — Diffs NewAuthorityStates to the current authority states and removes entries.
- L42 _public prototype_ `bool GetAuthorityStateAfterApplied(const FSoftObjectPath& ObjectPath) const;` — Gets the authority state the object will have if the changes are applied.
- L45 _public prototype_ `bool CanSetAuthorityFor(const FSoftObjectPath& ObjectPath) const;` — @return Whether it is valid to set authority for the given ObjectPath: that is if the object has properties registered.
- L47 _public prototype_ `EAuthorityMutability GetChangeAuthorityMutability(const FSoftObjectPath& ObjectPath) const;` — @return Detailed information why the object's authority can or cannot be changed.
- L50 _public prototype_ `TOptional<FConcertReplication_ChangeAuthority_Request> BuildChangeRequest(const FGuid& StreamId) const;` — Builds a change request from the local changes, if there are changes.
- L53 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAuthorityChangeMade);` — Called entries are added to NewAuthorityStates. NOT called when objects are removed.
- L54 _public function_ `FOnAuthorityChangeMade& OnChangedOwnedObjects()`
- L59 _private member_ `const FGuid ClientId;` — Id of the client this change tracker is tracking.
- L62 _private member_ `const IClientAuthoritySynchronizer& AuthoritySynchronizer;` — Knows the current authority state of the client and determines whether we support changing this client's authority at all.
- L64 _private member_ `FGlobalAuthorityCache& AuthorityCache;` — Used to determine whether other clients have authority over objects.
- L67 _private member_ `TMap<FSoftObjectPath, bool> NewAuthorityStates;` — Object to the authority state it should have.
- L70 _private member_ `FOnAuthorityChangeMade OnChangedOwnedObjectsDelegate;` — Called when NewAuthorityStates is updated.
- L72 _private function_ `void OnClientChanged(const FGuid& Guid)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L9 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L16 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L53 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAuthorityChangeMade);` — Called entries are added to NewAuthorityStates. NOT called when objects are removed.

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Authority/AuthoritySynchronizer_LocalClient.h` (Private)


#### class `UE::MultiUserClient::Replication::FAuthoritySynchronizer_LocalClient`  
`class FAuthoritySynchronizer_LocalClient : public FAuthoritySynchronizer_Base`  
_L12-30_
- inherits: `FAuthoritySynchronizer_Base`
- L16 _public prototype_ `FAuthoritySynchronizer_LocalClient(TSharedRef<IConcertSyncClient> InClient);`
- L20 _public prototype_ `virtual bool HasAuthorityOver(const FSoftObjectPath& ObjectPath) const override;`
- L21 _public prototype_ `virtual bool HasAnyAuthority() const override;`
- L27 _private member_ `TSharedRef<IConcertSyncClient> Client;` — Needed to access IConcertClientReplicationManager
- L29 _private prototype_ `void OnAuthorityChanged() const;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L10 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Authority/AuthoritySynchronizer_RemoteClient.h` (Private)


#### class `UE::MultiUserClient::Replication::FAuthoritySynchronizer_RemoteClient`  
`class FAuthoritySynchronizer_RemoteClient : public FAuthoritySynchronizer_Base`  
_L18-42_
- inherits: `FAuthoritySynchronizer_Base`
- L22 _public prototype_ `FAuthoritySynchronizer_RemoteClient(const FGuid& RemoteEndpointId, FStreamAndAuthorityQueryService& InQueryService UE_LIFETIMEBOUND);`
- L26 _public prototype_ `virtual bool HasAnyAuthority() const override;`
- L27 _public function_ `virtual bool HasAuthorityOver(const FSoftObjectPath& ObjectPath) const override`
- L33 _private member_ `FStreamAndAuthorityQueryService& QueryService;` — Queries the server in regular intervals. This services outlives our object.
- L36 _private member_ `const FDelegateHandle QueryStreamHandle;` — Used to unregister HandleStreamQuery upon destruction.
- L39 _private member_ `TSet<FSoftObjectPath> LastServerState;` — The most up to date server state of the remote client's authority.
- L41 _private prototype_ `void HandleAuthorityQuery(const TArray<FConcertAuthorityClientInfo>& PerStreamAuthority);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Authority/EAuthorityMutability.h` (Private)


#### enum `UE::MultiUserClient::Replication::EAuthorityMutability`  
`enum class EAuthorityMutability : uint8`  
_L10-20_
- desc: Various reasons in which an object can be when considering changing its authority
- L13 _public enumerator_ `NotApplicable` — The object has no registered properties. Cannot take authority.
- L16 _public enumerator_ `Conflict` — There is a conflict with another client
- L19 _public enumerator_ `Allowed` — Authority can be taken

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L7 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Authority/IClientAuthoritySynchronizer.h` (Private)


#### class `UE::MultiUserClient::Replication::IClientAuthoritySynchronizer`  
`class IClientAuthoritySynchronizer`  
_L12-27_
- desc: Synchronizes the a client's authority state with the server.
- L17 _public prototype_ `virtual bool HasAnyAuthority() const = 0;` — @return Whether this client is sending anything at all.
- L20 _public prototype_ `virtual bool HasAuthorityOver(const FSoftObjectPath& ObjectPath) const = 0;` — @return Whether the local instance thinks this client has authority over ObjectPath.
- L22 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnServerStateChanged);`
- L24 _public prototype_ `virtual FOnServerStateChanged& OnServerAuthorityChanged() = 0;` — @return Event executed when authority state has been updated.
- L26 _public prototype_ `virtual ~IClientAuthoritySynchronizer() = default;`

#### class `UE::MultiUserClient::Replication::FAuthoritySynchronizer_Base`  
`class FAuthoritySynchronizer_Base : public IClientAuthoritySynchronizer`  
_L30-43_
- inherits: `IClientAuthoritySynchronizer`
- desc: Util base class for implementing the events
- L36 _public function_ `virtual FOnServerStateChanged& OnServerAuthorityChanged() override`
- L42 _protected member_ `FOnServerStateChanged OnServerStateChangedDelegate;` — Triggered by subclasses when the authority state changes.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L9 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnServerStateChanged);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Client/ClientUtils.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L20 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L20 _namespace_ `namespace ClientUtils` (scope `UE::MultiUserClient::Replication`)
- L29 _prototype_ `FString GetClientDisplayName(const IConcertClient& InLocalClientInstance, const FGuid& InClientEndpointId);` (scope `UE::MultiUserClient::Replication::ClientUtils`) — Gets the display name for a client. Appends (me) if the client is local. @param InLocalClientInstance Used to look up client display info @param InClientEndpointId The endpoint ID of the client whose name to get @return The display name or empty
- L30 _prototype_ `FString GetClientDisplayName(const IConcertClientSession& InSession, const FGuid& InClientEndpointId);` (scope `UE::MultiUserClient::Replication::ClientUtils`)
- L40 _prototype_ `bool GetClientDisplayInfo(const IConcertClient& InLocalClientInstance, const FGuid& InClientEndpointId, FConcertClientInfo& OutClientInfo);` (scope `UE::MultiUserClient::Replication::ClientUtils`) — Gets the display info for a given client @param InLocalClientInstance Used to look up client display info @param InClientEndpointId The endpoint ID of the client whose name to get @param OutClientInfo The client display info to get @return Whether OutClientInfo holds a value
- L41 _prototype_ `bool GetClientDisplayInfo(const IConcertClientSession& InSession, const FGuid& InClientEndpointId, FConcertClientInfo& OutClientInfo);` (scope `UE::MultiUserClient::Replication::ClientUtils`)
- L49 _prototype_ `TArray<const FOnlineClient*> GetSortedClientList(const IConcertClient& InLocalClientInstance, const FOnlineClientManager& InReplicationManager);` (scope `UE::MultiUserClient::Replication::ClientUtils`) — Gets all replication clients in a sorted array. The local client will always be first and then come all remote clients sorted alphabetically. @param InLocalClientInstance Used to look up client display info @param InReplicationManager Used to obtain all clients @return Sorted client array
- L50 _prototype_ `TArray<const FOnlineClient*> GetSortedClientList(const IConcertClientSession& InSession, const FOnlineClientManager& InReplicationManager);` (scope `UE::MultiUserClient::Replication::ClientUtils`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Client/Offline/EndpointCache.h` (Private)


#### class `UE::MultiUserClient::Replication::FEndpointCache`  
`class FEndpointCache`  
_L15-62_
- desc: Goes through activity history and saves all endpoints is encounters.
- L20 _public prototype_ `void UpdateEndpoints(const IConcertClientWorkspace& Workspace);` — Updates the list of endpoints, if needed.
- L23 _public prototype_ `int32 FindClientIndexByEndpointId(const FGuid& EndpointId) const;` — @return An index to GetKnownClients() if a client with EndpointId is known.
- L26 _public function_ `const FGuid& GetLastAssociatedEndpoint(int32 Index) const` — @return The last endpoint that the client at GetKnownClients()[Index] was associated with.
- L29 _public function_ `const TArray<FConcertClientInfo>& GetKnownClients() const` — @return The clients that are known
- L34 _private member_ `int64 NextFirstActivityToFetch = 1;` — The next activity to start fetching from.
- L44 _private member_ `TArray<FConcertClientInfo> KnownClients;` — The clients encountered thus far. Multiple endpoint IDs are associated with a client. Client info is grouped by DeviceName and DisplayName even though they are technically new endpoints. Example: Client1 joins, leaves, then joins again. On the server, this would generate two distinct endpoints with different endpoint IDs, but we'll merge them into one assuming it's the same machine. This will not work if you have two UE instances with the same name on the same machine, which is unsupported by this class.
- L58 _private member_ `TArray<FClientMetaData> EndpointMetaData;` — Additional data about. Each index maps to KnownEndpoints. Array based to make GetKnownEndpoints interface easier.
- L61 _private prototype_ `void MergeEndpointsWith(const TMap<FGuid, FConcertClientInfo>& NewEndpoints);` — Adds NewEndpoints to EndpointMetaData.

#### struct `UE::MultiUserClient::Replication::FEndpointCache::FClientMetaData`  
`struct FClientMetaData`  
_L46-56_
- L49 _public member_ `TArray<FGuid> AssociatedEndpoints;` — All endpoint IDs that are associated with this client.
- L51 _public function_ `const FGuid& GetLastKnownEndpointId() const`
- L53 _public function_ `explicit FClientMetaData(const FGuid& LastKnownEndpointId) : AssociatedEndpoints({ LastKnownEndpointId })`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Client/Offline/OfflineClient.h` (Private)


#### class `UE::MultiUserClient::Replication::FOfflineClient`  
`class FOfflineClient : public FNoncopyable`  
_L19-64_
- inherits: `FNoncopyable`
- desc: Info about a client that had joined the MU session but no are longer is present. This is used to display info about the properties the client would receive if they joined back into the session.
- L23 _public prototype_ `FOfflineClient( IConcertClientWorkspace& InWorkspace UE_LIFETIMEBOUND, FConcertClientInfo InClientInfo, const FGuid& LastAssociatedEndpoint );`
- L29 _public function_ `FORCEINLINE const FConcertClientInfo& GetClientInfo() const`
- L30 _public function_ `FORCEINLINE const FGuid& GetLastAssociatedEndpoint() const`
- L31 _public function_ `FORCEINLINE const FConcertBaseStreamInfo& GetPredictedStream() const`
- L41 _public function_ `TSharedRef<ConcertSharedSlate::IReplicationStreamModel> GetStreamModel() const` — This is used so the UI can construct the IReplicationStreamEditor. @see CreateBaseStreamEditor and FCreateEditorParams. @note You must make sure to release this object when this FReplicationClient is destroyed. Listen for events on the owning FOfflineClientManager::OnDisconnectedClientsChanged. @see FReplicationClientManager and FMultiUserReplicationManager
- L43 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FStreamPredictionChanged);`
- L45 _public function_ `FStreamPredictionChanged& OnStreamPredictionChanged()` — Broadcasts when the stream, which the offline client will get upon rejoining, has changed.
- L50 _private member_ `const FConcertClientInfo ClientInfo;` — The client's last registered display data.
- L52 _private member_ `const FGuid LastAssociatedEndpoint;` — The last endpoint ID this client was associated with-
- L55 _private member_ `FRejoinStreamAndAuthorityPredictor ContentPredictor;` — Predicts the stream as activities are produced.
- L60 _private member_ `const TSharedRef<ConcertSharedSlate::IReplicationStreamModel> StreamModel;` — Read-only model of the state predicted by StreamSynchronizer. TODO DP: In the future, this may be made editable to allow the user to edit the future state in the UI.
- L63 _private member_ `FStreamPredictionChanged OnStreamPredictionChangedDelegate;` — Broadcasts when the stream, which the offline client will get upon rejoining, has changed.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L13 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L43 _delegate_ `DECLARE_MULTICAST_DELEGATE(FStreamPredictionChanged);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Client/Offline/OfflineClientManager.h` (Private)


#### class `UE::MultiUserClient::Replication::FOfflineClientManager`  
`class FOfflineClientManager : public FNoncopyable`  
_L30-99_
- inherits: `FNoncopyable`
- desc: Manages clients that had joined the MU session but no are longer is present. Endpoint IDs are saved in the database. Endpoint IDs with the same DisplayName and DeviceName are associated with single FOfflineClient. While FEndpointCache detects name changes, the rest of the system is not currently set up to handle them, e.g. FindClient.
- L38 _public prototype_ `FOfflineClientManager( IConcertSyncClient& ClientInstance UE_LIFETIMEBOUND, FOnlineClientManager& OnlineClientManager UE_LIFETIMEBOUND );` — @param ClientInstance Used to obtain disconnected endpoint info from the server. The caller ensures it outlives the new object. @param OnlineClientManager Used to determine whether a client should be considered offline. The caller ensures it outlives the new object.
- L42 _public prototype_ `~FOfflineClientManager();`
- L45 _public prototype_ `const FOfflineClient* FindClient(const FGuid& EndpointId) const;` — @return The offline client that was associated with this endpoint ID.
- L47 _public prototype_ `FOfflineClient* FindClient(const FGuid& EndpointId);` — @return The offline client that was associated with this endpoint ID.
- L51 _public prototype_ `template<typename TLambda> requires std::is_invocable_r_v<EBreakBehavior, TLambda, FOfflineClient&> void ForEachClient(TLambda&& Consumer) const;` — Iterates through every offline client.
- L53 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOfflineClientsChanged);`
- L55 _public function_ `FOfflineClientsChanged& OnClientsChanged()` — Broadcasts when Clients is changed.
- L57 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOfflineClientDelegate, FOfflineClient&);`
- L59 _public function_ `FOfflineClientDelegate& OnPostClientAdded()` — Called just after an offline client is has been added. Called before OnClientsChanged.
- L61 _public function_ `FOfflineClientDelegate& OnPreClientRemoved()` — Called just before an offline client is about to be removed. Called before OnClientsChanged.
- L63 _public function_ `FOfflineClientDelegate& OnClientContentChanged()` — Broadcasts after an offline client's stream content has changed. Also called after OnClientsChangedDelegate.
- L68 _private member_ `IConcertSyncClient& ClientInstance;` — The local client connected to the MU session. Used to obtain disconnected endpoint info from the server.
- L70 _private member_ `FOnlineClientManager& OnlineClientManager;` — Used to determine whether a client should be considered offline.
- L73 _private member_ `TArray<TUniquePtr<FOfflineClient>> Clients;` — Info about clients that were once connected but are no longer.
- L76 _private member_ `FEndpointCache EndpointCache;` — Keeps track of all known endpoints.
- L79 _private member_ `FOfflineClientsChanged OnClientsChangedDelegate;` — Broadcasts when Clients is changed.
- L81 _private member_ `FOfflineClientDelegate OnPostClientAddedDelegate;` — Broadcasts just after an offline client is has been added. Called before OnClientsChanged.
- L83 _private member_ `FOfflineClientDelegate OnPreClientRemovedDelegate;` — Broadcasts just before an offline client is about to be removed. Called before OnClientsChanged.
- L85 _private member_ `FOfflineClientDelegate OnClientContentChangedDelegate;` — Broadcasts after an offline client's stream content has changed. Not called as part of OnPostClientAddedDelegate.
- L88 _private prototype_ `void OnActivityAddedOrProduced(const FConcertClientInfo&, const FConcertSyncActivity&, const FStructOnScope&);` — Updates the list of known endpoints in response to an activity being added.
- L91 _private prototype_ `void RefreshOfflineClients();` — Refreshes Clients based on which clients are online.
- L93 _private prototype_ `bool UpdateClientList(IConcertClientWorkspace& Workspace);` — Iterates through EndpointCache and updates Clients.
- L95 _private prototype_ `bool IsClientOnline(const FConcertClientInfo& QueryClientInfo) const;` — @return Whether a client with the given info is online.
- L98 _private prototype_ `int32 FindClientIndexByInfo(const FConcertClientInfo& ClientInfo) const;` — @return Index to Clients that matches ClientInfo.
- L102 _function_ `template <typename TLambda> requires std::is_invocable_r_v<EBreakBehavior, TLambda, FOfflineClient&> void FOfflineClientManager::ForEachClient(TLambda&& Consumer) const`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L20 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L53 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOfflineClientsChanged);`
- L57 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOfflineClientDelegate, FOfflineClient&);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Client/Offline/RejoinStreamAndAuthorityPredictor.h` (Private)


#### class `UE::MultiUserClient::Replication::FRejoinStreamAndAuthorityPredictor`  
`class FRejoinStreamAndAuthorityPredictor : public FStreamSynchronizer_Base , public FAuthoritySynchronizer_Base , public FNoncopyable`  
_L24-72_
- inherits: `FStreamSynchronizer_Base,FAuthoritySynchronizer_Base,FNoncopyable`
- desc: Predicts the stream and authority state a client will have when they rejoin the session. The prediction returns the stream content in the latest EConcertSyncReplicationActivityType::LeaveReplication pertaining to ClientInfo.
- L31 _public prototype_ `FRejoinStreamAndAuthorityPredictor(IConcertClientWorkspace& InWorkspace UE_LIFETIMEBOUND, FConcertClientInfo InClientInfo);`
- L32 _public prototype_ `~FRejoinStreamAndAuthorityPredictor();`
- L34 _public function_ `FORCEINLINE const FConcertBaseStreamInfo& GetPredictedStream() const`
- L37 _public function_ `virtual FGuid GetStreamId() const override`
- L38 _public function_ `virtual const FConcertObjectReplicationMap& GetServerState() const override`
- L39 _public function_ `virtual const FConcertStreamFrequencySettings& GetFrequencySettings() const override`
- L43 _public function_ `virtual bool HasAnyAuthority() const override`
- L44 _public function_ `virtual bool HasAuthorityOver(const FSoftObjectPath& ObjectPath) const override`
- L48 _public function_ `FSimpleMulticastDelegate& OnPredictionChanged()` — Broadcasts when PredictedStream changes.
- L53 _private member_ `IConcertClientWorkspace& Workspace;` — Used to listen for activity changes.
- L55 _private member_ `const FConcertClientInfo ClientInfo;` — Client for which we're predicting the state.
- L58 _private member_ `FConcertBaseStreamInfo PredictedStream;` — The stream content the local client thinks the offline client will have.
- L60 _private member_ `TSet<FSoftObjectPath> PredictedAuthority;` — The most up to date server state of the remote client's authority.
- L63 _private member_ `FSimpleMulticastDelegate OnPredictionChangedDelegate;` — Broadcasts when PredictedStream changes.
- L66 _private prototype_ `void OnActivityAddedOrUpdated( const FConcertClientInfo& ActivityClientInfo, const FConcertSyncActivity& Activity, const FStructOnScope& Summary );` — Refreshes the prediction state if a new leave replication event is produced.
- L71 _private prototype_ `void AnalyzeHistory();` — Refreshes PredicatedStream.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L18 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Client/Online/LocalClient.h` (Private)


#### class `UE::MultiUserClient::Replication::FLocalClient`  
`class FLocalClient : public FOnlineClient`  
_L13-36_
- inherits: `FOnlineClient`
- desc: Holds extra information about a local replication client.
- L24 _public prototype_ `FLocalClient( FReplicationDiscoveryContainer& InDiscoveryContainer, FGlobalAuthorityCache& InAuthorityCache, UMultiUserReplicationStream& InClientStreamContent, TUniquePtr<IClientStreamSynchronizer> InStreamSynchronizer, TSharedRef<IConcertSyncClient> InClient );` — @param InDiscoveryContainer Used for auto-discovering properties added to this client's stream. The caller ensures it outlives the constructed instance. @param InAuthorityCache Caches authority state of all clients. Passed to subsystems. The caller ensures it outlives the constructed instance. @param InClientStreamContent Object that this client's stream changes are to be written into. The caller ensures it outlives the constructed instance. @param InStreamSynchronizer Implementation for obtaining stream registered on server. The constructed instance takes ownership. @param InClient The local editor's running client. Passed to subsystems so they can send messages to the current session. Keeps strong reference.
- L35 _private member_ `FRemoteSubmissionListener RemoteSubmissionListener;` — Listens for and handles for submission request made by remote clients' SubmissionWorkflow.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L8 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Client/Online/OnlineClient.h` (Private)


#### class `UE::MultiUserClient::Replication::FOnlineClient`  
`class FOnlineClient : public FNoncopyable`  
_L39-193_
- inherits: `FNoncopyable`
- desc: Initializes systems that are common for local or remote clients. This class' responsibility is to initialize all systems that exist for the life time of a client in a session.
- L52 _public prototype_ `FOnlineClient( const FGuid& EndpointId, FReplicationDiscoveryContainer& InDiscoveryContainer UE_LIFETIMEBOUND, FGlobalAuthorityCache& InAuthorityCache UE_LIFETIMEBOUND, UMultiUserReplicationStream& InClientStreamContent UE_LIFETIMEBOUND, TUniquePtr<IClientStreamSynchronizer> InStreamSynchronizer, TUniquePtr<IClientAuthoritySynchronizer> InAuthoritySynchronizer, TUniquePtr<ISubmissionWorkflow> InSubmissionWorkflow );` — @param EndpointId The endpoint ID this instance corresponds to. @param InDiscoveryContainer Used for auto-discovering properties added to this client's stream. The caller ensures it outlives the constructed instance. @param InAuthorityCache Caches authority state of all clients. Passed to subsystems. The caller ensures it outlives the constructed instance. @param InClientStreamContent Object that this client's stream changes are to be written into. The caller ensures it outlives the constructed instance. @param InStreamSynchronizer Implementation for obtaining stream registered on server. The constructed instance takes ownership. @param InAuthoritySynchronizer Implementation for obtaining the client's authority state on server. The constructed instance takes ownership. @param InSubmissionWorkflow Implementation for for changing client streams and authority on the server. The constructed instance takes ownership.
- L61 _public prototype_ `~FOnlineClient();`
- L63 _public function_ `UMultiUserReplicationStream* GetClientStreamObject() const`
- L64 _public function_ `FMultiUserStreamExtender& GetStreamExtender()`
- L73 _public function_ `TSharedRef<ConcertSharedSlate::IEditableReplicationStreamModel> GetClientEditModel() const` — This is used so the UI can construct the IReplicationStreamEditor. @see CreateBaseStreamEditor and FCreateEditorParams. @note You must make sure to release this object when this FReplicationClient is destroyed. Listen for events on the owning FReplicationClientManager::OnPreRemoteClientRemoved and FMultiUserReplicationManager::OnLeaveSession @see FReplicationClientManager and FMultiUserReplicationManager
- L74 _public function_ `IClientStreamSynchronizer& GetStreamSynchronizer() const`
- L75 _public function_ `IClientAuthoritySynchronizer& GetAuthoritySynchronizer() const`
- L77 _public function_ `const FStreamChangeTracker& GetStreamDiffer() const`
- L78 _public function_ `FStreamChangeTracker& GetStreamDiffer()`
- L80 _public function_ `const FAuthorityChangeTracker& GetAuthorityDiffer() const`
- L81 _public function_ `FAuthorityChangeTracker& GetAuthorityDiffer()`
- L84 _public function_ `const ISubmissionWorkflow& GetSubmissionWorkflow() const` — @return The object with which you can submit changes. You can use it to listen to general events. If you want to submit changes, you should prefer to use the SubmissionQueue.
- L85 _public function_ `ISubmissionWorkflow& GetSubmissionWorkflow()`
- L87 _public function_ `FSubmissionQueue& GetSubmissionQueue()` — @return Implements simple game-thread based queue for SubmissionWorkflow. Only one submission can be in progress at any given time.
- L89 _public function_ `FExternalClientChangeRequestHandler& GetExternalRequestHandler()` — @return Gets the adapter handling requests received by IMultiUserReplication::EnqueuesChanges
- L92 _public function_ `const FGuid& GetEndpointId() const` — @return The endpoint ID of this client in the Concert session.
- L94 _public prototype_ `bool AllowsEditing() const;` — @return Whether it is allowed to edit the stream and authority for this client.
- L96 _public function_ `bool operator==(const FOnlineClient& Client) const`
- L98 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnModelExternallyChanged);`
- L105 _public function_ `FOnModelExternallyChanged& OnModelChanged()` — Broadcast when the data underlying the model has changed for any reason: - Edited directly by client - Changed by transaction - Server state changed
- L107 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnHiearchyNeedsRefresh);`
- L109 _public function_ `FOnHiearchyNeedsRefresh& OnHierarchyNeedsRefresh()` — Broadcasts when the hierarchy may have changed.
- L114 _private member_ `const FGuid EndpointId;` — This client's Concert Endpoint ID.
- L117 _private member_ `TObjectPtr<UMultiUserReplicationStream> ClientStreamContent;` — The state of the server is synched up with this object and displayed in the UI.
- L120 _private member_ `TUniquePtr<IClientStreamSynchronizer> StreamSynchronizer;` — Keeps the client's stream state on the server in sync.
- L122 _private member_ `TUniquePtr<IClientAuthoritySynchronizer> AuthoritySynchronizer;` — Keeps the client's authority state on the server in sync.
- L124 _private member_ `TUniquePtr<ISubmissionWorkflow> SubmissionWorkflow;` — Handles the logic of submitting and reverting for this client.
- L127 _private member_ `FSubmissionQueue SubmissionQueue;` — Allows systems to queue pending submissions to SubmissionWorkflow in case a submission is in progress.
- L129 _private member_ `FExternalClientChangeRequestHandler ExternalRequestHandler;` — Enqueues external change requests into the SubmissionQueue.
- L132 _private member_ `TSharedRef<FMultiUserStreamExtender> StreamExtender;` — Injected into LocalClientEditModel during construction. Adds additional objects and properties when a new object is added to the stream.
- L143 _private member_ `TSharedRef<ConcertSharedSlate::IEditableReplicationStreamModel> LocalClientEditModel;` — Used to detect changes made to the client's config by the local editor. Those changes can later be applied to the client. The SessionContent UObject must be kept alive as long as this model lives. It should be noted that the UI keeps a strong reference to this model. The UI is destroyed right before FReplicationClient, which is guaranteed by FMultiUserReplicationManager. @see FMultiUserReplicationManager::OnLeaveSession
- L146 _private member_ `FStreamChangeTracker LocalClientStreamDiffer;` — Tracks changes made to server's state of the client's streams and prepares to upload them using StreamSynchronizer.
- L148 _private member_ `FAuthorityChangeTracker LocalAuthorityDiffer;` — Tracks changes made to the client's authority state.
- L150 _private member_ `FFrequencyChangeTracker LocalFrequencyChangeTracker;` — Tracks enqueued local changes to object replication frequency.
- L153 _private member_ `FChangeRequestBuilder ChangeRequestBuilder;` — Shared logic for building stream and authority change requests based on local change made.
- L155 _private member_ `FAutoSubmissionPolicy AutoSubmissionPolicy;` — Automatically submits changes as they are made by the user.
- L158 _private member_ `ConcertClientSharedSlate::FModifyObjectInLevelHandler LevelModificationHandler;` — Handles updating the local client's stream when the level is modified, e.g. when an actor is removed.
- L161 _private member_ `FOnHiearchyNeedsRefresh OnHierarchyNeedsRefreshDelegate;` — Broadcasts when the hierarchy may have changed.
- L169 _private member_ `FOnModelExternallyChanged OnModelChangedDelegate;` — Broadcast when the data underlying the model has changed for any reason: - Edited directly by client - Changed by transaction - Server state changed
- L172 _private member_ `bool bHasDeferredDataChanges = false;` — Whether there are any deferred data changes to process.
- L175 _private prototype_ `void OnObjectsChanged(TConstArrayView<UObject*> AddedObjects, TConstArrayView<FSoftObjectPath> RemovedObjects, ConcertSharedSlate::EReplicatedObjectChangeReason ReplicatedObjectChangeReason);` — Respond to model changing
- L176 _private prototype_ `void OnPropertiesChanged();`
- L178 _private prototype_ `void OnServerStateChanged();`
- L181 _private prototype_ `void DeferOnModelChanged();` — Defers rebuilding operations, such as refreshing state and calling OnModelChanged, in case there are multiple changes in the same frame.
- L183 _private prototype_ `void ProcessOnModelChanged();` — Processes all changes that have happened to the stream this frame.
- L186 _private prototype_ `TArray<UObject*> DetermineAddedObjects() const;` — Determines the objects that were newly added.
- L189 _private prototype_ `void ApplyDefaultFrequencySettings(const TArray<UObject*>& ChangeData);` — Applies default replication frequency settings specified in the Multi User settings
- L192 _private prototype_ `void OnAuthoritySubmissionCompleted(const FSubmitAuthorityChangesRequest& Request, const FSubmitAuthorityChangesResponse& Response);` — Removes authority if request fails

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L29 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L98 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnModelExternallyChanged);`
- L107 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnHiearchyNeedsRefresh);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Client/Online/OnlineClientManager.h` (Private)


#### class `UE::MultiUserClient::Replication::FOnlineClientManager`  
`class FOnlineClientManager : public FGCObject , public FNoncopyable`  
_L36-160_
- inherits: `FGCObject,FNoncopyable`
- desc: Keeps track of clients connected to replication via a MU session. It synchronizes their stream data in a UMultiUserReplicationSessionPreset. This class is instantiated only for as long as the local client is in a Concert session and is owned by FMultiUserReplicationManager, which drives the lifetime.
- L48 _public prototype_ `FOnlineClientManager( const TSharedRef<IConcertSyncClient>& InClient, const TSharedRef<IConcertClientSession>& InSession, FReplicationDiscoveryContainer& InRegisteredExtenders UE_LIFETIMEBOUND, FStreamAndAuthorityQueryService& InQueryService UE_LIFETIMEBOUND );` — @param InClient The local client. The owning FMultiUserReplicationManager ensures it outlives the constructed instance. @param InSession The session to observe. The owning FMultiUserReplicationManager ensures it outlives the constructed instance. @param InRegisteredExtenders Used for auto-discovering properties added to this client's stream. Passed to the clients. The owning FMultiUserReplicationManager ensures it outlives the constructed instance. @param InQueryService Used for querying info about clients' streams. Passed to the clients. The owning FMultiUserReplicationManager ensures it outlives the constructed instance.
- L56 _public function_ `const FLocalClient& GetLocalClient() const`
- L57 _public function_ `FLocalClient& GetLocalClient()`
- L58 _public prototype_ `TArray<TNonNullPtr<const FRemoteClient>> GetRemoteClients() const;`
- L59 _public prototype_ `TArray<TNonNullPtr<FRemoteClient>> GetRemoteClients();`
- L62 _public function_ `TArray<TNonNullPtr<const FOnlineClient>> GetClients(TFunctionRef<bool(const FOnlineClient& Client)> Predicate = [](const auto&){ return true; }) const;` — @return Gets all clients given a predicate
- L62 _public prototype_ `TArray<TNonNullPtr<const FOnlineClient>> GetClients(TFunctionRef<bool(const FOnlineClient& Client)> Predicate = [](const auto&){ return true; }) const;` — @return Gets all clients given a predicate
- L64 _public function_ `const FGlobalAuthorityCache& GetAuthorityCache() const`
- L65 _public function_ `FGlobalAuthorityCache& GetAuthorityCache()`
- L67 _public function_ `const FReassignObjectPropertiesLogic& GetReassignmentLogic() const`
- L68 _public function_ `FReassignObjectPropertiesLogic& GetReassignmentLogic()`
- L71 _public prototype_ `const FRemoteClient* FindRemoteClient(const FGuid& EndpointId) const;` — Util for finding a remote client by its EndpointId.
- L72 _public function_ `FRemoteClient* FindRemoteClient(const FGuid& EndpointId)`
- L79 _public function_ `const FOnlineClient* FindClient(const FGuid& EndpointId) const` — Util for finding a local or remote client by its EndpointId.
- L85 _public function_ `FOnlineClient* FindClient(const FGuid& EndpointId)`
- L92 _public prototype_ `void ForEachClient(TFunctionRef<EBreakBehavior(const FOnlineClient&)> ProcessClient) const;` — Iterates through every client
- L94 _public prototype_ `void ForEachClient(TFunctionRef<EBreakBehavior(FOnlineClient&)> ProcessClient);` — Iterates through every client
- L96 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FRemoteClientsChanged);`
- L98 _public function_ `FRemoteClientsChanged& OnRemoteClientsChanged()` — Called when RemoteClients changes. Called after OnPostRemoteClientAdded.
- L100 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FRemoteClientDelegate, FRemoteClient&);`
- L102 _public function_ `FRemoteClientDelegate& OnPostRemoteClientAdded()` — Called just after a remote client is has been added to RemoteClients. Called before OnRemoteClientsChanged.
- L104 _public function_ `FRemoteClientDelegate& OnPreRemoteClientRemoved()` — Called just before a remote client is about to be removed from RemoteClients.
- L107 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L108 _public function_ `virtual FString GetReferencerName() const override`
- L114 _private member_ `TSharedRef<IConcertSyncClient> ConcertClient;` — The local Concert client
- L121 _private member_ `const TWeakPtr<IConcertClientSession> Session;` — The session the local client is in. This FReplicationClientManager's owner is supposed to make sure this FReplicationClientManager is destroyed when the session shuts down.
- L127 _private member_ `FReplicationDiscoveryContainer& RegisteredExtenders;` — Passed to clients for constructing for the purposes of auto-discovering properties and additional objects when adding properties to the stream. The owning FMultiUserReplicationManager ensures it outlives this FReplicationClientManager instance.
- L133 _private member_ `FStreamAndAuthorityQueryService& QueryService;` — Sends FConcertReplication_QueryReplicationInfo_Request in regular intervals. Shared by all remote clients so all requests are bundled reducing the number of network requests.
- L135 _private member_ `FGlobalAuthorityCache AuthorityCache;` — Keeps a cache of object to owning clients.
- L138 _private member_ `FLocalClient LocalClient;` — Manages the local client
- L143 _private member_ `TArray<TUniquePtr<FRemoteClient>> RemoteClients;` — Manages remote clients. Updated when client connects or disconnects to the active session. UI keeps references to systems inside the client so it is TSharedRef in case TArray is reallocated.
- L146 _private member_ `FRemoteClientsChanged OnRemoteClientsChangedDelegate;` — Called when RemoteClients changes.
- L148 _private member_ `FRemoteClientDelegate OnPostRemoteClientAddedDelegate;` — Called when RemoteClients changes. Called after OnPostRemoteClientAdded.
- L150 _private member_ `FRemoteClientDelegate OnPreRemoteClientRemovedDelegate;` — Called just before a remote client is about to be removed from RemoteClients.
- L153 _private member_ `FReassignObjectPropertiesLogic ReassignmentLogic;` — Used for transferring ownership from multiple clients to one. Used by multi client view.
- L156 _private prototype_ `void OnSessionClientChanged(IConcertClientSession&, EConcertClientStatus NewStatus, const FConcertSessionClientInfo& ClientInfo);` — Updates RemoteClients depending on the change.
- L159 _private prototype_ `void CreateRemoteClient(const FGuid& ClientEndpointId, bool bBroadcastDelegate = true);` — Shared logic for creating a remote client.

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L21 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L96 _delegate_ `DECLARE_MULTICAST_DELEGATE(FRemoteClientsChanged);`
- L100 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FRemoteClientDelegate, FRemoteClient&);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Client/Online/RemoteClient.h` (Private)


#### class `UE::MultiUserClient::Replication::FRemoteClient`  
`class FRemoteClient : public FOnlineClient`  
_L16-36_
- inherits: `FOnlineClient`
- desc: Holds extra information about a remote replication client.
- L28 _public prototype_ `FRemoteClient( const FGuid& InConcertClientId, FReplicationDiscoveryContainer& InDiscoveryContainer UE_LIFETIMEBOUND, TSharedRef<IConcertClient> InClient, FGlobalAuthorityCache& InAuthorityCache UE_LIFETIMEBOUND, UMultiUserReplicationStream& InClientStreamContent UE_LIFETIMEBOUND, FStreamAndAuthorityQueryService& QueryService UE_LIFETIMEBOUND );` — @param InConcertClientId The endpoint ID this instance corresponds to. @param InDiscoveryContainer Used for auto-discovering properties added to this client's stream. The caller ensures it outlives the constructed instance. @param InClient The local editor's running client. Passed to subsystems so they can send messages to the current session. Keeps strong reference. @param InAuthorityCache Caches authority state of all clients. Passed to subsystems. The caller ensures it outlives the constructed instance. @param InClientStreamContent Object that this client's stream changes are to be written into. The caller ensures it outlives the constructed instance. @param QueryService Service shared across remote clients which periodically asks the server about this client's state. The caller ensures it outlives the constructed instance.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Client/UnifiedClientView.h` (Private)


#### enum `UE::MultiUserClient::Replication::EClientType`  
`enum class EClientType : uint8`  
_L26-31_
- L28 _public enumerator_ `Local`
- L29 _public enumerator_ `Remote`
- L30 _public enumerator_ `Offline`

#### class `UE::MultiUserClient::Replication::FUnifiedClientView`  
`class FUnifiedClientView : public FNoncopyable`  
_L42-98_
- inherits: `FNoncopyable`
- desc: Uses FOnlineClientManager and FOfflineClientManager to preset a unified interface of querying client info to the UI. This abstraction effectively implements the Adapter design pattern. This task of this class is not to hide the fact that there are online and offline clients: the goal is to unify the interface and put shared logic that needs to handle online and offline client interactions here.
- L46 _public prototype_ `FUnifiedClientView( IConcertSyncClient& SyncClient UE_LIFETIMEBOUND, FOnlineClientManager& OnlineClientManager UE_LIFETIMEBOUND, FOfflineClientManager& OfflineClientManager UE_LIFETIMEBOUND );`
- L51 _public prototype_ `~FUnifiedClientView();`
- L55 _public prototype_ `template<typename TLambda> requires std::is_invocable_r_v<EBreakBehavior, TLambda, const FGuid&> void ForEachClient(TLambda&& Callback) const;` — Enumerates the endpoint ID of every user; in the case of offline clients, only the latest associated ID is listed..
- L58 _public prototype_ `template<typename TLambda> requires std::is_invocable_r_v<EBreakBehavior, TLambda, const FGuid&> void ForEachOnlineClient(TLambda&& Callback) const;` — Enumerates the endpoint ID of every online client.
- L60 _public prototype_ `TArray<FGuid> GetClients() const;`
- L61 _public prototype_ `TArray<FGuid> GetOnlineClients() const;`
- L62 _public prototype_ `FGuid GetLocalClient() const;`
- L65 _public prototype_ `TOptional<FConcertClientInfo> GetClientInfoByEndpoint(const FGuid& EndpointId) const;` — @return Client info associated with EndpointId.
- L67 _public prototype_ `TOptional<EClientType> GetClientType(const FGuid& EndpointId) const;` — @return Gets the type of client
- L70 _public prototype_ `TSharedPtr<const ConcertSharedSlate::IReplicationStreamModel> GetClientStreamById(const FGuid& EndpointId) const;` — @return The stream model of the client associated with EndpointId.
- L72 _public prototype_ `TSharedPtr<ConcertSharedSlate::IEditableReplicationStreamModel> GetEditableClientStreamById(const FGuid& EndpointId) const;` — @return The editable stream model of the client associated with EndpointId, if EndpointId refers to an online client.
- L74 _public function_ `const FUnifiedStreamCache& GetStreamCache() const`
- L75 _public function_ `FUnifiedStreamCache& GetStreamCache()`
- L78 _public function_ `FSimpleMulticastDelegate OnClientsChanged()` — Broadcasts when the list of online of offline clients has changed.
- L83 _private member_ `IConcertSyncClient& SyncClient;` — Used to look up client info from session.
- L85 _private member_ `FOnlineClientManager& OnlineClientManager;`
- L86 _private member_ `FOfflineClientManager& OfflineClientManager;`
- L89 _private member_ `FSimpleMulticastDelegate OnClientsChangedDelegate;` — Broadcasts when the list of online of offline clients has changed.
- L95 _private member_ `FUnifiedStreamCache StreamCache;` — Unified interface for querying stream content efficiently. Important: Has dependency on OnClientsChangedDelegate hence this must be constructed after.
- L97 _private function_ `void BroadcastOnClientsChanged() const`
- L101 _function_ `template <typename TLambda> requires std::is_invocable_r_v<EBreakBehavior, TLambda, const FGuid&> void FUnifiedClientView::ForEachClient(TLambda&& Callback) const`
- L120 _function_ `template <typename TLambda> requires std::is_invocable_r_v<EBreakBehavior, TLambda, const FGuid&> void FUnifiedClientView::ForEachOnlineClient(TLambda&& Callback) const`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L24 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L32 _function_ `inline bool IsOnlineClient(EClientType Type)` (scope `UE::MultiUserClient::Replication`)
- L33 _function_ `inline bool IsOfflineClient(EClientType Type)` (scope `UE::MultiUserClient::Replication`)
- L105 _function_ `` (scope `UE::MultiUserClient::Replication::FUnifiedClientView::ForEachClient`)
- L123 _function_ `` (scope `UE::MultiUserClient::Replication::FUnifiedClientView::ForEachOnlineClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Client/UnifiedClientViewExtensions.h` (Private)


#### enum `UE::MultiUserClient::Replication::EDisplayStringOption`  
`enum class EDisplayStringOption : uint8`  
_L18-24_
- L21 _public enumerator_ `NameOnly` — E.g. "OfflineUserName", "LocalUserName", and "RemoteUserName".
- L23 _public enumerator_ `NameAndParentheses` — E.g. "OfflineUserName(Offline)", "LocalUserName(Me)", and "RemoteUserName".

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L16 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L27 _prototype_ `FString GetClientDisplayString( const FUnifiedClientView& ClientView, const FGuid& ClientEndpointId, EDisplayStringOption Option = EDisplayStringOption::NameAndParentheses );` (scope `UE::MultiUserClient::Replication`) — @return Gets the display string to use for the given client; use it e.g. for search. Returns empty FString if the client is not found.
- L33 _prototype_ `FText GetClientDisplayText( const FUnifiedClientView& ClientView, const FGuid& ClientEndpointId, EDisplayStringOption Option = EDisplayStringOption::NameAndParentheses );` (scope `UE::MultiUserClient::Replication`) — @return Gets the display text to use for displaying the given client. Returns empty FText if the client is not found.
- L40 _prototype_ `FText GetParenthesesContent(const FUnifiedClientView& ClientView, const FGuid& ClientEndpointId);` (scope `UE::MultiUserClient::Replication`) — @return "You" or "Offline" depending on ClientEndpointId.
- L43 _prototype_ `TOptional<FGuid> FindClientIdByStream(const FUnifiedClientView& ClientView, const ConcertSharedSlate::IReplicationStreamModel& SearchedStream);` (scope `UE::MultiUserClient::Replication`) — @return Endpoint ID of the client that has the given Stream.
- L46 _prototype_ `TArray<FGuid> GetSortedOnlineClients(const FUnifiedClientView& ClientView, EDisplayStringOption Option = EDisplayStringOption::NameAndParentheses);` (scope `UE::MultiUserClient::Replication`) — @return Gets all online clients sorted by display name.
- L49 _function_ `inline ConcertSharedSlate::FGetOptionalClientInfo MakeOnlineThenOfflineClientInfoGetter(const FUnifiedClientView& ClientView UE_LIFETIMEBOUND)` (scope `UE::MultiUserClient::Replication`) — @return Delegate that will get client info from online clients if possible and falls back to offline clients.
- L52 _function_ `` (scope `UE::MultiUserClient::Replication::MakeOnlineThenOfflineClientInfoGetter`)
- L58 _function_ `inline ConcertSharedSlate::FGetClientParenthesesContent MakeLocalAndOfflineParenthesesContentGetter(const FUnifiedClientView& ClientView UE_LIFETIMEBOUND)` (scope `UE::MultiUserClient::Replication`) — @return Delegate that will return (You) or (Offline) for a client.
- L61 _function_ `` (scope `UE::MultiUserClient::Replication::MakeLocalAndOfflineParenthesesContentGetter`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Client/UnifiedStreamCache.h` (Private)


#### enum `UE::MultiUserClient::Replication::EClientEnumerationMode`  
`enum class EClientEnumerationMode : uint8`  
_L21-28_
- L23 _public enumerator_ `All`
- L25 _public enumerator_ `SkipOfflineClientsThatFullyOverlapWithOnlineClients` — Skip offline clients if all their properties are also owned by online clients.
- L27 _public enumerator_ `SkipOfflineClients` — Offline clients are supposed to be skipped completely.

#### class `UE::MultiUserClient::Replication::FUnifiedStreamCache`  
`class FUnifiedStreamCache : public FNoncopyable`  
_L31-80_
- inherits: `FNoncopyable`
- desc: Access point for querying stream content of both online and offline clients through a single interface.
- L35 _public prototype_ `FUnifiedStreamCache( FUnifiedClientView& InOwner UE_LIFETIMEBOUND, FOnlineClientManager& InOnlineClientManager UE_LIFETIMEBOUND, FOfflineClientManager& InOfflineClientManager UE_LIFETIMEBOUND );`
- L40 _public prototype_ `~FUnifiedStreamCache();`
- L43 _public prototype_ `const FConcertObjectReplicationMap* GetReplicationMapFor(const FGuid& ClientId) const;` — @return Gets the replication map for the specified client.
- L49 _public prototype_ `void EnumerateClientsWithObject( const FSoftObjectPath& ObjectPath, const TFunctionRef<EBreakBehavior(const FGuid& ClientId)>& Callback, EClientEnumerationMode Option = EClientEnumerationMode::SkipOfflineClientsThatFullyOverlapWithOnlineClients ) const;` — Lists out all clients that have ObjectPath registered in their stream. Does not mean that they have authority over it.
- L59 _public prototype_ `void EnumerateClientsWithObjectAndProperty( const FSoftObjectPath& ObjectPath, const FConcertPropertyChain& Property, const TFunctionRef<EBreakBehavior(const FGuid& ClientId)>& Callback, EClientEnumerationMode Option = EClientEnumerationMode::SkipOfflineClientsThatFullyOverlapWithOnlineClients ) const;` — Lists out all clients that have ObjectPath with Property assigned to it registered in their stream. Does not mean that they have authority over it.
- L67 _public function_ `FSimpleMulticastDelegate& OnCacheChanged()` — Broadcasts when the content of a client has changed.
- L71 _private member_ `FUnifiedClientView& Owner;`
- L72 _private member_ `FOnlineClientManager& OnlineClientManager;`
- L73 _private member_ `FOfflineClientManager& OfflineClientManager;`
- L76 _private member_ `FSimpleMulticastDelegate OnCacheChangedDelegate;` — Broadcasts when the content of a client has changed.
- L78 _private function_ `void OnOnlineCacheChanged(const FGuid&) const`
- L79 _private function_ `void BroadcastOnCacheChanged() const`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L15 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/IToken.h` (Private)


#### class `UE::MultiUserClient::Replication::FToken`  
`class FToken : public TSharedFromThis<FToken>`  
_L20-24_
- inherits: `TSharedFromThis<FToken>`
- desc: The token "pattern" used by systems that start non-cancellable, latent operations (like TFutures from Concert responses): 1. The system creates a TSharedRef<FToken> and holds on to it for the system's entire lifetime. 2. Latent operation capture a TWeakPtr to the token and the this pointer of the system 3. When the latent operation finishes, it checks whether the token is still valid. - If yes, that means the system is valid, too, so the captured this can be used safely. - If no, discard the operation result. This pattern offers an alternative to forcing the system to be wrapped in a shared pointer itself and forcing it to inherit from TSharedFromThis. Often systems should not care about whether they are heap allocated or not - in such cases using TSharedFromThis would be an anti-pattern.
- L23 _public function_ `static TSharedRef<FToken> Make()`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L7 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/AnalyticsHandler.h` (Private)


#### class `UE::MultiUserClient::Replication::FAnalyticsHandler`  
`class FAnalyticsHandler : public FNoncopyable`  
_L18-40_
- inherits: `FNoncopyable`
- desc: Handles any changes to the replication data model and send an analytics event with session id.
- L21 _public prototype_ `FAnalyticsHandler(IConcertClient& InClient UE_LIFETIMEBOUND, FOnlineClientManager& InReplicationClientManager UE_LIFETIMEBOUND);`
- L23 _public prototype_ `~FAnalyticsHandler();`
- L27 _private member_ `IConcertClient& Client;` — Used to get client session information.
- L30 _private member_ `FOnlineClientManager& OnlineClientManager;` — Used to detect when a client's state changes.
- L33 _private prototype_ `void OnClientAdded(FRemoteClient& InRemoteClient);` — Called when a remote client joins.
- L36 _private prototype_ `void OnClientContentChanged();` — Called when remote client changes the replication model.
- L39 _private member_ `bool bSentReplicationAnalyticsData = false;` — Have we sent our analytics event for replication.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L10 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/ChangeLevelHandler.h` (Private)


#### class `UE::MultiUserClient::Replication::FChangeLevelHandler`  
`class FChangeLevelHandler : public FNoncopyable`  
_L20-52_
- inherits: `FNoncopyable`
- desc: Handles a client opening a new level. Upon leaving a level, all replicated objects assigned to that client in that level are removed.
- L28 _public prototype_ `FChangeLevelHandler(IConcertSyncClient& Client UE_LIFETIMEBOUND, ConcertSharedSlate::IEditableReplicationStreamModel& UpdatedModel UE_LIFETIMEBOUND);` — @param Client The Concert client. Used to get the workspace for checking against hot reloading. The caller ensures that it outlives the constructed object. @param UpdatedModel The client model to update when the local editor changes maps. The caller ensures that it outlives the constructed object.
- L29 _public prototype_ `~FChangeLevelHandler();`
- L34 _private member_ `IConcertSyncClient& Client;` — The Concert client. Used to get the workspace for checking against hot reloading.
- L36 _private member_ `ConcertSharedSlate::IEditableReplicationStreamModel& UpdatedModel;` — The client model to update when the local editor changes maps.
- L39 _private member_ `FSoftObjectPath PreviousWorldPath;` — Path to the previously open world
- L41 _private prototype_ `void OnWorldDestroyed(UWorld* World);`
- L42 _private prototype_ `void OnWorldAdded(UWorld* World) const;`
- L50 _private prototype_ `bool IsConcertHotReloadingWorld() const;` — Hot reload: When a remote user saves the world, Concert will reload the world's package on the other clients. In that case, a temporary world called "Untitled" is created. During hot reload, OnWorldDestroyed and OnWorldAdded calls should be ignored. @return Whether concert is hot reloading the currently open world.
- L51 _private prototype_ `bool IsValidWorldType(UWorld* World) const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/DetailRowExtensionHandler.h` (Private)


#### class `UE::MultiUserClient::Replication::FDetailRowExtensionHandler`  
`class FDetailRowExtensionHandler : public FNoncopyable`  
_L23-77_
- inherits: `FNoncopyable`
- desc: Adds a button to Details panel rows for quickly assigning the property to the local client for replication.
- L27 _public prototype_ `FDetailRowExtensionHandler( const TSharedRef<IConcertSyncClient>& InClient, const TSharedRef<FMultiUserReplicationManager>& InReplicationManager, FGetConcertBrowserWidget InGetOrInvokeBrowserTabDelegate );`
- L32 _public prototype_ `~FDetailRowExtensionHandler();`
- L37 _private member_ `const TWeakPtr<IConcertSyncClient> WeakClient;` — Used to look up client names.
- L39 _private member_ `const TWeakPtr<FMultiUserReplicationManager> WeakReplicationManager;` — Used to get the local client, to which properties will be assigned by default.
- L41 _private member_ `const FGetConcertBrowserWidget GetOrInvokeBrowserTabDelegate;` — Gets the content of the Multi User browser tab invoking it if it is not open.
- L43 _private member_ `const FDelegateHandle OnReplicationConnectionChangedHandle;` — Handle to FMultiUserReplicationManager::OnReplicationConnectionStateChanged.
- L46 _private prototype_ `void RegisterExtensionHandler( const FOnGenerateGlobalRowExtensionArgs& Args, TArray<FPropertyRowExtensionButton>& OutExtensionButtons );` — Adds the assign button to valid property rows.
- L52 _private prototype_ `FText GetToolTipText(TSharedPtr<IPropertyHandle> PropertyHandle) const;` — @return Displays the reason why the property cannot be assigned.
- L55 _private prototype_ `void OnAssignPropertyClicked(TSharedPtr<IPropertyHandle> PropertyHandle) const;` — Assigns the property to the local client.
- L57 _private function_ `bool CanExecuteAssignPropertyClick(TSharedPtr<IPropertyHandle> PropertyHandle) const` — @return Whether the property can be assigned.
- L59 _private prototype_ `bool IsAssignPropertyButtonVisible(TSharedPtr<IPropertyHandle> PropertyHandle) const;` — @return Whether the client is in a MU session and the property can ever be replicated.
- L62 _private prototype_ `bool IsConnectedToReplication() const;` — @return Whether in a MU session and completed the replication handshake.
- L65 _private prototype_ `void SelectObjectsInReplicationUI(TConstArrayView<UObject*> ObjectsToSelect) const;` — Shows the replication UI if hidden and selects Objects.
- L68 _private prototype_ `bool CanAssignPropertyWithReason(TSharedPtr<IPropertyHandle> PropertyHandle, FText* OutReason = nullptr) const;` — @return Whether PropertyHandle can be assigned to its outer objects.
- L69 _private function_ `bool CanAssignProperty(TSharedPtr<IPropertyHandle> PropertyHandle) const`
- L72 _private prototype_ `bool IsPropertyNotYetAssignedWithReason(const UObject& AssignedToObject, const TArray<FName>& PropertyPath, FText* OutReason = nullptr) const;` — @return Whether the property identified by PropertyPath is not yet assigned to AssigedToObject by any client.
- L73 _private function_ `bool IsPropertyNotYetAssigned(const UObject& Object, const TArray<FName>& PropertyChainPath) const`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L18 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/Frequency/FrequencyChangeTracker.h` (Private)


#### class `UE::MultiUserClient::Replication::FFrequencyChangeTracker`  
`class FFrequencyChangeTracker : public FNoncopyable`  
_L19-53_
- inherits: `FNoncopyable`
- desc: Used to queue up local made changes to object frequency settings.
- L23 _public prototype_ `FFrequencyChangeTracker( IClientStreamSynchronizer& InStreamSynchronizer UE_LIFETIMEBOUND );`
- L26 _public prototype_ `~FFrequencyChangeTracker();`
- L29 _public prototype_ `void AddOverride(FSoftObjectPath Object, FConcertObjectReplicationSettings NewSettings);` — Adds a frequency override for the given object.
- L34 _public prototype_ `FFrequencyChangelist BuildForSubmission(const FStreamChangelist& ObjectChanges);` — Compares the recorded changes to about to be submitted ObjectChanges and strips any invalid changes.
- L37 _public prototype_ `void RefreshChanges();` — Compares the local changes against the server state and optionally removes changes.
- L39 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnFrequencySettingsChanged);`
- L41 _public function_ `FOnFrequencySettingsChanged& OnFrequencySettingsChanged()` — Called when frequency settings have changed been recorded that need to be submitted to the server.
- L46 _private member_ `IClientStreamSynchronizer& StreamSynchronizer;` — Tells us when the server state changes so RecordedChanges can be cleansed of applied changes.
- L49 _private member_ `FFrequencyChangelist RecordedChanges;` — The changes recorded thus far.
- L52 _private member_ `FOnFrequencySettingsChanged OnFrequencySettingsChangedDelegate;` — Called when frequency settings have changed been recorded that need to be submitted to the server.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L13 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnFrequencySettingsChanged);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/Frequency/FrequencyUtils.h` (Private)


#### enum `UE::MultiUserClient::Replication::FrequencyUtils::EChangeResult`  
`enum class EChangeResult : uint8`  
_L36-36_
- L36 _public enumerator_ `enum class EChangeResult : uint8 { Success, Failure }; /** * Goes through all clients and sets a FConcertObjectReplicationSettings for ContextObject. The setting is applied by invoking ApplySettingChange. * @return Operations object that informs you when the change operations have completed. */ TSharedPtr<IParallelSubmissionOperation> SetFrequencySettingForClients( const FSoftObjectPath& ContextObject, const FInlineClientArray& Clients,`
- L36 _public enumerator_ `enum class EChangeResult : uint8 { Success, Failure }; /** * Goes through all clients and sets a FConcertObjectReplicationSettings for ContextObject. The setting is applied by invoking ApplySettingChange. * @return Operations object that informs you when the change operations have completed. */ TSharedPtr<IParallelSubmissionOperation> SetFrequencySettingForClients( const FSoftObjectPath& ContextObject, const FInlineClientArray& Clients,`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L16 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L21 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L21 _namespace_ `namespace FrequencyUtils` (scope `UE::MultiUserClient::Replication`)
- L24 _typedef_ `using FInlineClientArray = TArray<FGuid, TInlineAllocator<8>>;` (scope `UE::MultiUserClient::Replication::FrequencyUtils`) — Low effort optimization to minimize heap allocations
- L28 _prototype_ `template<typename TSubSetting, typename TSelectSubSetting> TOptional<TSubSetting> FindSharedFrequencySetting( const FSoftObjectPath& ContextObject, const FInlineClientArray& Clients, const FOnlineClientManager& InClientManager, TSelectSubSetting&& Transform ) requires std::is_invocable_r_v<TSubSetting, TSelectSubSetting, const FConcertObjectReplicationSettings&>;` (scope `UE::MultiUserClient::Replication::FrequencyUtils`) — Gets the shared value from FConcertObjectReplicationSettings, if all clients share the same value. Transform selects the member.
- L41 _prototype_ `TSharedPtr<IParallelSubmissionOperation> SetFrequencySettingForClients( const FSoftObjectPath& ContextObject, const FInlineClientArray& Clients, FOnlineClientManager& InClientManager, TFunctionRef<void(FConcertObjectReplicationSettings&)> ApplySettingChange );` (scope `UE::MultiUserClient::Replication::FrequencyUtils`) — Goes through all clients and sets a FConcertObjectReplicationSettings for ContextObject. The setting is applied by invoking ApplySettingChange. @return Operations object that informs you when the change operations have completed.
- L49 _function_ `inline TOptional<uint8> FindSharedFrequencyRate(const FSoftObjectPath& ContextObject, const FInlineClientArray& Clients, const FOnlineClientManager& InClientManager)` (scope `UE::MultiUserClient::Replication::FrequencyUtils`) — Gets the replication rate of all clients, if they share the same value.
- L54 _function_ `` (scope `UE::MultiUserClient::Replication::FrequencyUtils::FindSharedFrequencyRate`)
- L62 _function_ `inline TOptional<EConcertObjectReplicationMode> FindSharedReplicationMode(const FSoftObjectPath& ContextObject, const FInlineClientArray& Clients, const FOnlineClientManager& InClientManager)` (scope `UE::MultiUserClient::Replication::FrequencyUtils`) — @return The replication mode that all clients are using, if they share the same value.
- L66 _function_ `` (scope `UE::MultiUserClient::Replication::FrequencyUtils::FindSharedReplicationMode`)
- L72 _function_ `inline bool AllClientsHaveMode(const EConcertObjectReplicationMode SearchedMode, const FSoftObjectPath& ContextObject, const FInlineClientArray& Clients, const FOnlineClientManager& InClientManager)` (scope `UE::MultiUserClient::Replication::FrequencyUtils`) — @return Whether all clients have the given replication mode
- L78 _function_ `inline bool CanChangeFrequencySettings(const FSoftObjectPath& ContextObject, const FOnlineClient& Client)` (scope `UE::MultiUserClient::Replication::FrequencyUtils`) — @return Whether ContextObject's frequency settings can be changed for Client.
- L86 _function_ `inline bool CanChangeFrequencySettings(const FSoftObjectPath& ContextObject, const FInlineClientArray& Clients, const FOnlineClientManager& InClientManager)` (scope `UE::MultiUserClient::Replication::FrequencyUtils`) — @return Whether ContextObject's frequency settings can be changed for all given Clients.
- L89 _function_ `` (scope `UE::MultiUserClient::Replication::FrequencyUtils::CanChangeFrequencySettings`)
- L96 _namespace_ `namespace UE`
- L96 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L96 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L96 _namespace_ `namespace FrequencyUtils` (scope `UE::MultiUserClient::Replication`)
- L99 _function_ `template<typename TSubSetting, typename TSelectSubSetting> TOptional<TSubSetting> FindSharedFrequencySetting( const FSoftObjectPath& ContextObject, const FInlineClientArray& Clients, const FOnlineClientManager& InClientManager, TSelectSubSetting&& Transform ) requires std::is_invocable_r_v<TSubSetting, TSelectSubSetting, const FConcertObjectReplicationSettings&>` (scope `UE::MultiUserClient::Replication::FrequencyUtils`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/GlobalAuthorityCache.h` (Private)


#### class `UE::MultiUserClient::Replication::FGlobalAuthorityCache`  
`class FGlobalAuthorityCache : public FNoncopyable , ConcertSyncCore::Replication::IReplicationGroundTruth`  
_L29-141_
- inherits: `FNoncopyable,ConcertSyncCore::Replication::IReplicationGroundTruth`
- desc: Allows efficient look-up of which objects and properties are owned by which clients. This class efficiently answers the question: "Which clients own this object?"
- L35 _public typedef_ `using FProcessPropertyConflict = TFunctionRef<EBreakBehavior(const FGuid& ConflictingClientId, const FConcertPropertyChain& Property)>;`
- L37 _public prototype_ `FGlobalAuthorityCache(FOnlineClientManager& InClientManager);`
- L39 _public prototype_ `void RegisterEvents();` — Called when the local client has been created and it is safe to register client events with FReplicationClientManager.
- L42 _public prototype_ `void ForEachClientWithObjectInStream(const FSoftObjectPath& Object, TFunctionRef<EBreakBehavior(const FGuid& ClientId)> Callback) const;` — Iterates every client that Object in its stream.
- L45 _public prototype_ `bool IsObjectOrChildReferenced(const FSoftObjectPath& Object) const;` — @return Whether the object is referenced by at least one client stream.
- L48 _public prototype_ `void ForEachClientWithAuthorityOverObject(const FSoftObjectPath& Object, TFunctionRef<EBreakBehavior(const FGuid& ClientId)> Callback) const;` — Iterates every client that has authority over Object.
- L50 _public prototype_ `TArray<FGuid> GetClientsWithAuthorityOverObject(const FSoftObjectPath& Object) const;` — Util that uses ForEachClientWithAuthorityOverObject to make an array.
- L52 _public prototype_ `bool HasAuthorityOverObject(const FSoftObjectPath& Object, const FGuid& ClientId) const;` — @return Returns whether the client has (partial) authority over the object.
- L55 _public function_ `EAuthorityMutability CanClientTakeAuthorityAfterSubmission(const FSoftObjectPath& Object, const FGuid& ClientId, FProcessPropertyConflict ProcessConflict = [](auto&, auto&){ return EBreakBehavior::Break; }) const;` — @return Whether the given client can take authority over the object without causing any conflicts. This also considers the changes made to the stream after submission.
- L55 _public prototype_ `EAuthorityMutability CanClientTakeAuthorityAfterSubmission(const FSoftObjectPath& Object, const FGuid& ClientId, FProcessPropertyConflict ProcessConflict = [](auto&, auto&){ return EBreakBehavior::Break; }) const;` — @return Whether the given client can take authority over the object without causing any conflicts. This also considers the changes made to the stream after submission.
- L57 _public prototype_ `bool CanClientAddProperty(const FSoftObjectPath& Object, const FGuid& ClientId, const FConcertPropertyChain& Chain) const;` — @return Whether the given client add the given property to the object without causing any conflicts.
- L60 _public prototype_ `void ForEachClientReferencingProperty(const FSoftObjectPath& Object, const FConcertPropertyChain& Property, TFunctionRef<EBreakBehavior(const FGuid& ClientId)> Callback) const;` — Iterates through every client whose stream is referencing Object's Property.
- L62 _public prototype_ `bool IsPropertyReferencedByAnyClientStream(const FSoftObjectPath& Object, const FConcertPropertyChain& Property) const;` — @return Whether any client is referencing Object in a stream.
- L65 _public function_ `TOptional<FGuid> GetClientWithAuthorityOverProperty(const FSoftObjectPath& Object, const FConcertPropertyChain& Property) const` — Gets the client that has authority over the given property, if there is any.
- L67 _public prototype_ `TOptional<FGuid> GetClientWithAuthorityOverProperty(const FSoftObjectPath& Object, const TArray<FName>& PropertyChain) const;` — Gets the client that has authority over the given property, if there is any.
- L75 _public prototype_ `void CleanseConflictsFromAuthorityRequest(FConcertReplication_ChangeAuthority_Request& Request, const FGuid& SendingClient) const;` — Removes entries from Request that would generate conflicts. @param Request The request to clense @param SendingClient The client that will send the request
- L82 _public prototype_ `void CleanseConflictsFromStreamRequest(FConcertReplication_ChangeStream_Request& Request, const FGuid& SendingClient) const;` — Removes entries from Request that would generate conflicts. @param Request The request to clense @param SendingClient The client that will send the request
- L85 _public function_ `const ConcertSyncCore::FObjectPathHierarchy& GetStreamObjectHierarchy() const` — Allows efficient retrieving of registered child objects.
- L87 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCacheChanged, const FGuid& ClientId);`
- L89 _public function_ `FOnCacheChanged& OnCacheChanged()` — Called when the cache changes for a specific client.
- L94 _private member_ `FOnlineClientManager& ClientManager;` — Used to obtain the clients and their states
- L97 _private member_ `TMap<FSoftObjectPath, TSet<FGuid>> StreamObjectsToClients;` — Maps objects that are owned to the clients that have them in the stream
- L99 _private member_ `TMap<FSoftObjectPath, TSet<FGuid>> AuthorityObjectsToClients;` — Maps objects that are owned to the clients that own them (have authority)
- L101 _private member_ `ConcertSyncCore::FObjectPathHierarchy StreamObjectHierarchy;` — The hierarchy of objects that have been registered by all clients. Allows efficient retrieving of child objects.
- L104 _private member_ `FOnCacheChanged OnCacheChangedDelegate;` — Called when the cache changes for a specific client.
- L107 _private prototype_ `void RegisterForClientEvents(const FOnlineClient& Client);` — Registers for authority and stream changes
- L108 _private prototype_ `void UnregisterFromClientEvents(const FOnlineClient& Client) const;`
- L111 _private prototype_ `void AddClient(const FGuid& ClientId);` — Adds the client to OwnedObjectsToClients
- L112 _private prototype_ `void RemoveClient(const FGuid& ClientId);`
- L115 _private function_ `void OnPostRemoteClientAdded(FRemoteClient& RemoteClient)` — Respond to remote client registration
- L120 _private function_ `void OnPreRemoteClientRemoved(FRemoteClient& RemoteClient)`
- L127 _private function_ `void OnPostAuthorityChanged(const FGuid ClientId)` — Rebuild client when their authority changes
- L128 _private function_ `void OnStreamChanged(const FGuid ClientId)`
- L129 _private function_ `void RebuildClient(const FGuid ClientId)`
- L137 _private prototype_ `virtual void ForEachStream(const FGuid& ClientEndpointId, TFunctionRef<EBreakBehavior(const FGuid& StreamId, const FConcertObjectReplicationMap& ReplicationMap)> Callback) const override;`
- L138 _private prototype_ `virtual void ForEachClient(TFunctionRef<EBreakBehavior(const FGuid& ClientEndpointId)> Callback) const override;`
- L139 _private prototype_ `virtual bool HasAuthority(const FGuid& ClientId, const FGuid& StreamId, const FSoftObjectPath& ObjectPath) const override;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L16 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L23 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L87 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCacheChanged, const FGuid& ClientId);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/Notification/DuplicateUserNotifier.h` (Private)


#### class `UE::MultiUserClient::Replication::FDuplicateUserNotifier`  
`class FDuplicateUserNotifier : public FNoncopyable`  
_L22-47_
- inherits: `FNoncopyable`
- desc: Informs the user if they are using the same name as another client. The message is only shown if the local or other, duplicate client use replication, i.e. register properties. Certain features, like restoring the content that the client had when they last left, will not working correctly with non-unique display names.
- L26 _public prototype_ `FDuplicateUserNotifier( IConcertClient& InClient UE_LIFETIMEBOUND, FOnlineClientManager& InOnlineClientManager UE_LIFETIMEBOUND );`
- L30 _public prototype_ `~FDuplicateUserNotifier();`
- L35 _private member_ `IConcertClient& Client;` — Used to get client display information.
- L37 _private member_ `FOnlineClientManager& OnlineClientManager;` — Used to detect when a client's state changes.
- L40 _private member_ `bool bHasWarnedUser = false;` — Whether the user was already warned in this session (will re-warn if they leave and join another session).
- L43 _private prototype_ `void OnClientContentChanged(const FGuid& ClientId);` — Invokes when any client's content changes.
- L46 _private prototype_ `void ShowWarning();` — Shows the warning and prevents it from being shown again in the active session.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/Notification/MutingNotifier.h` (Private)


#### class `UE::MultiUserClient::Replication::FMutingNotifier`  
`class FMutingNotifier : public FNoncopyable`  
_L17-29_
- inherits: `FNoncopyable`
- desc: Informs the user of things that went wrong with muting requests.
- L20 _public prototype_ `FMutingNotifier(FMuteStateManager& InMuteManager UE_LIFETIMEBOUND);`
- L21 _public prototype_ `~FMutingNotifier();`
- L26 _private member_ `FMuteStateManager& MuteManager;` — Informs us when a request goes wrong.
- L28 _private prototype_ `void OnMuteRequestFailed(const FConcertReplication_ChangeMuteState_Request& Request, const FConcertReplication_ChangeMuteState_Response& Response);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/Notification/ReplicationUserNotifier.h` (Private)


#### class `UE::MultiUserClient::Replication::FReplicationUserNotifier`  
`class FReplicationUserNotifier : public FNoncopyable`  
_L17-36_
- inherits: `FNoncopyable`
- desc: This informs the user of things that went wrong during replication.
- L21 _public prototype_ `FReplicationUserNotifier( IConcertClient& InClient UE_LIFETIMEBOUND, FOnlineClientManager& InReplicationClientManager UE_LIFETIMEBOUND, FMuteStateManager& InMuteManager UE_LIFETIMEBOUND );`
- L30 _private member_ `const FSubmissionNotifier SubmissionNotifier;` — Notifies the user when stream or authority submission to the server fails.
- L33 _private member_ `const FMutingNotifier MutingNotifier;` — Informs the user of things that went wrong with muting requests.
- L35 _private member_ `const FDuplicateUserNotifier DuplicateClientNameNotifier;` — Informs the user if they are using the same name as another client.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/PreventReplicatedPropertyTransaction.h` (Private)


#### class `UE::MultiUserClient::Replication::FPreventReplicatedPropertyTransaction`  
`class FPreventReplicatedPropertyTransaction : public FNoncopyable`  
_L20-42_
- inherits: `FNoncopyable`
- desc: Prevents generating transactions with properties that are being replicated by any other client.
- L24 _public prototype_ `FPreventReplicatedPropertyTransaction( IConcertSyncClient& InSyncClient UE_LIFETIMEBOUND, FOnlineClientManager& InClientManager UE_LIFETIMEBOUND, FMuteStateManager& InMuteManager UE_LIFETIMEBOUND );`
- L29 _public prototype_ `~FPreventReplicatedPropertyTransaction();`
- L34 _private member_ `IConcertSyncClient& SyncClient;` — Used to unsubscribe from the transaction bridge.
- L37 _private member_ `FOnlineClientManager& ClientManager;` — Used to obtain up-to-date registered properties from all clients.
- L39 _private member_ `FMuteStateManager& MuteManager;` — Used to approximate whether remote clients may have sync control
- L41 _private prototype_ `ETransactionFilterResult FilterTransactionAffectedByReplication(const FConcertTransactionFilterArgs& FilterArgs);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/PropertySelection/AutoPropertyOwnershipTaker.h` (Private)


#### class `UE::MultiUserClient::Replication::FAutoPropertyOwnershipTaker`  
`class FAutoPropertyOwnershipTaker : public FNoncopyable`  
_L19-41_
- inherits: `FNoncopyable`
- desc: Automatically takes and releases ownership over properties the user adds to the set of selected properties.
- L23 _public prototype_ `FAutoPropertyOwnershipTaker( FUserPropertySelector& InPropertySelector UE_LIFETIMEBOUND, FLocalClient& InLocalClient UE_LIFETIMEBOUND, FGlobalAuthorityCache& InReplicationCache UE_LIFETIMEBOUND );`
- L28 _public prototype_ `~FAutoPropertyOwnershipTaker();`
- L33 _private member_ `FUserPropertySelector& PropertySelector;` — Used to detect when a property is added or removed from the selected set of properties.
- L35 _private member_ `FLocalClient& LocalClient;` — The property ownership is changed for this client.
- L37 _private member_ `FGlobalAuthorityCache& ReplicationCache;` — Used to quickly check whether user selected properties are already owned.
- L39 _private prototype_ `void OnPropertiesAddedByUser(UObject* Object, TArrayView<const FConcertPropertyChain> Properties) const;`
- L40 _private prototype_ `void OnPropertiesRemovedByUser(UObject* Object, TArrayView<const FConcertPropertyChain> ConcertPropertyChains) const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/PropertySelection/UserPropertySelectionSource.h` (Private)


#### class `UE::MultiUserClient::Replication::FUserPropertySelectionSource`  
`class FUserPropertySelectionSource : public ConcertSharedSlate::IPropertySourceProcessor , public FNoncopyable`  
_L21-45_
- inherits: `ConcertSharedSlate::IPropertySourceProcessor,FNoncopyable`
- desc: Injected into UI causing it to only display the properties that - have been selected by the user - are referenced by any client streams
- L27 _public prototype_ `FUserPropertySelectionSource( const ConcertSharedSlate::IReplicationStreamModel& InUserSelection UE_LIFETIMEBOUND, const FOnlineClientManager& InClientManager UE_LIFETIMEBOUND );`
- L33 _public prototype_ `virtual void ProcessPropertySource( const ConcertSharedSlate::FPropertySourceContext& Context, TFunctionRef<void(const ConcertSharedSlate::IPropertySource& Model)> Processor ) const override;`
- L42 _private member_ `const ConcertSharedSlate::IReplicationStreamModel& UserSelection;` — This is used to read the properties the user has selected, which is represented by a stream.
- L44 _private member_ `const FOnlineClientManager& ClientManager;` — Used to get client stream content and subscribe to changes.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/PropertySelection/UserPropertySelector.h` (Private)


#### class `UE::MultiUserClient::Replication::FUserPropertySelector`  
`class FUserPropertySelector : public FNoncopyable , public FGCObject`  
_L40-119_
- inherits: `FNoncopyable,FGCObject`
- desc: Manages the properties the user is iterating on in the replication session. The bottom-half property section in the replication UI uses this to keep track of which properties the user has selected for which properties. Whenever any client adds a property to its stream, we'll assume the user is iterating on that property. For this reason, we automatically will track the property as user-selected.
- L46 _public prototype_ `FUserPropertySelector( FOnlineClientManager& InOnlineClientManager UE_LIFETIMEBOUND, FOfflineClientManager& InOfflineClientManger UE_LIFETIMEBOUND );`
- L53 _public prototype_ `void AddUserSelectedProperties(UObject* Object, TConstArrayView<FConcertPropertyChain> Properties);` — Add Properties to the user's selection for Object. These properties were purposefully selected added by the user.
- L55 _public prototype_ `void RemoveUserSelectedProperties(UObject* Object, TConstArrayView<FConcertPropertyChain> Properties);` — Removes Properties from the user's selection for Object. These properties were purposefully selected added by the user.
- L57 _public prototype_ `bool IsPropertySelected(const FSoftObjectPath& Object, const FConcertPropertyChain& Property) const;` — @return Whether Property is selected for Object.
- L59 _public prototype_ `TSharedRef<ConcertSharedSlate::IPropertySourceProcessor> GetPropertySourceProcessor() const;`
- L61 _public function_ `DECLARE_MULTICAST_DELEGATE(FOnPropertySelectionChanged) FOnPropertySelectionChanged& OnPropertySelectionChanged()`
- L65 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPropertiesChangedByUser, UObject* , TConstArrayView<FConcertPropertyChain> );`
- L67 _public function_ `FOnPropertiesChangedByUser& OnPropertiesAddedByUser()` — @return Event that broadcasts when the user adds a property manually (through UI).
- L69 _public function_ `FOnPropertiesChangedByUser& OnPropertiesRemovedByUser()` — @return Event that broadcasts when the user removes a property manually (through UI).
- L72 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L73 _public function_ `virtual FString GetReferencerName() const override`
- L79 _private member_ `FOnlineClientManager& OnlineClientManager;` — Used to remove deselected properties from local client's stream and auto-add properties from remote clients to the user selection.
- L84 _private member_ `FOfflineClientManager& OfflineClientManager;` — When an online client turns into an offline client, we need to subscribe to changes made to that client, e.g. preset could change what client gets when it rejoins.
- L87 _private member_ `TObjectPtr<UMultiUserReplicationStream> PropertySelection;` — This underlying object saves the properties that user has selected. It allows for transactions.
- L89 _private member_ `const TSharedRef<ConcertSharedSlate::IEditableReplicationStreamModel> SelectionEditModel;` — This logic modifies PropertySelection.
- L92 _private member_ `const TSharedRef<FUserPropertySelectionSource> PropertyProcessor;` — Getter for UI to determine which properties to display.
- L95 _private member_ `FOnPropertySelectionChanged OnPropertySelectionChangedDelegate;` — Broadcasts when the user property selection changes.
- L97 _private member_ `FOnPropertiesChangedByUser OnPropertiesAddedByUserDelegate;` — Broadcasts when the user adds a property manually (through UI).
- L99 _private member_ `FOnPropertiesChangedByUser OnPropertiesRemovedByUserDelegate;` — Broadcasts when the user removes a property manually (through UI).
- L102 _private prototype_ `void OnClientAdded(FRemoteClient& Client);` — Called when a remote client joins.
- L104 _private prototype_ `void RegisterOnlineClient(FOnlineClient& Client);` — Ensures that whenever the client's server state changes, its properties are tracked as user selected.
- L105 _private prototype_ `void RegisterOfflineClient(FOfflineClient& Client);`
- L108 _private prototype_ `void OnOnlineClientContentChanged(const FGuid ClientId);` — Tracks all properties of the client as user selected.
- L110 _private prototype_ `void OnOfflineClientContentChanged(const TNonNullPtr<const FOfflineClient> Client);` — Tracks all properties the offline client will get upon rejoining as user selected.
- L112 _private prototype_ `void TrackProperties(const FConcertObjectReplicationMap& ReplicationMap);` — Adds all properties in the replication map as user selected.
- L115 _private prototype_ `void OnObjectTransacted(UObject* Object, const FTransactionObjectEvent&) const;` — If PropertySelection is transacted, broadcast OnPropertySelectionChangedDelegate.
- L117 _private prototype_ `void InternalAddSelectedProperties(UObject* Object, TConstArrayView<FConcertPropertyChain> Properties);`
- L118 _private prototype_ `void InternalRemoveSelectedProperties(UObject* Object, TConstArrayView<FConcertPropertyChain> Properties);`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L24 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L61 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPropertySelectionChanged) FOnPropertySelectionChanged& OnPropertySelectionChanged() { return OnPropertySelectionChangedDelegate; } DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPropertiesChangedByUser, UObject* , TConstArrayView<FConcertPropertyChain> );`
- L65 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPropertiesChangedByUser, UObject* , TConstArrayView<FConcertPropertyChain> );`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/Query/MuteStateQueryService.h` (Private)


#### class `UE::MultiUserClient::Replication::FMuteStateQueryService`  
`class FMuteStateQueryService : public FNoncopyable`  
_L20-54_
- inherits: `FNoncopyable`
- desc: Sends regular FConcertReplication_QueryMuteState_Request to endpoints and publishes the results.
- L29 _public prototype_ `FMuteStateQueryService(TWeakPtr<FToken> InToken, const IConcertSyncClient& InOwningClient UE_LIFETIMEBOUND);` — @param InToken Used to check whether this instance was destroyed after a response is received. @param InOwningClient The client through which queries are made. The caller ensures it outlasts the constructed instance.
- L32 _public function_ `void RequestInstantRefresh()` — @return Sends a request to the server immediately
- L34 _public function_ `FOnMuteStateQueried& OnMuteStateQueried()`
- L39 _private member_ `const TWeakPtr<FToken> Token;` — Used to check whether we were destroyed after a response is received.
- L47 _private member_ `const IConcertSyncClient& OwningClient;` — Used to send queries. This FRegularQueryService's owner is supposed to make sure this FRegularQueryService is destroyed when the client shuts down.
- L50 _private member_ `FOnMuteStateQueried OnMuteStateQueriedDelegate;` — Broadcasts when the mute state has been queried.
- L53 _private prototype_ `void SendQueryEvent();` — Queries the server for the client's current state.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L15 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMuteStateQueried, const FConcertReplication_QueryMuteState_Response& NewMuteState);`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMuteStateQueried, const FConcertReplication_QueryMuteState_Response& NewMuteState);` (scope `UE::MultiUserClient::Replication`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/Query/RegularQueryService.h` (Private)


#### class `UE::MultiUserClient::Replication::FRegularQueryService`  
`class FRegularQueryService : public FNoncopyable`  
_L21-60_
- inherits: `FNoncopyable`
- desc: This service manages multiple sub-services that query the server state, e.g. stream, authority, etc. Its responsibility is to tick the sub-services and manage access to them.
- L29 _public prototype_ `FRegularQueryService(const IConcertSyncClient& InOwningClient UE_LIFETIMEBOUND, float InInterval = 1.f);` — @param InOwningClient The client through which queries are made. The caller ensures it outlasts the constructed instance. @param InInterval The interval at which queries are to be made.
- L30 _public prototype_ `~FRegularQueryService();`
- L33 _public function_ `FStreamAndAuthorityQueryService& GetStreamAndAuthorityQueryService()` — @return The service for querying stream and authority state.
- L35 _public function_ `FMuteStateQueryService& GetMuteStateQueryService()` — @return The service for querying global mute state.
- L40 _private member_ `const TSharedRef<FToken> Token = FToken::Make();` — Passed to sub-services to check whether they were destroyed after a response is received.
- L48 _private member_ `const IConcertSyncClient& OwningClient;` — Used to send queries. This FRegularQueryService's owner is supposed to make sure this FRegularQueryService is destroyed when the client shuts down.
- L51 _private member_ `const FTSTicker::FDelegateHandle TickerDelegateHandle;` — Used to unregister the ticker.
- L54 _private member_ `FStreamAndAuthorityQueryService StreamAndAuthorityQueryService;` — Queries stream and authority changes.
- L56 _private member_ `FMuteStateQueryService MuteStateQueryService;` — Queries global mute state at regular intervals.
- L59 _private prototype_ `void Tick();` — Ticks the sub-services when it is time to send a new request.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L15 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/Query/StreamAndAuthorityQueryService.h` (Private)


#### class `UE::MultiUserClient::Replication::FStreamAndAuthorityQueryService`  
`class FStreamAndAuthorityQueryService : public FNoncopyable`  
_L21-80_
- inherits: `FNoncopyable`
- desc: Sends regular FConcertReplication_QueryReplicationInfo_Request to endpoints and publishes the results.
- L30 _public prototype_ `FStreamAndAuthorityQueryService(TWeakPtr<FToken> InToken, const IConcertSyncClient& InOwningClient UE_LIFETIMEBOUND);` — @param InToken Used to check whether this instance was destroyed after a response is received. @param InOwningClient The client through which queries are made. The caller ensures it outlasts the constructed instance.
- L33 _public prototype_ `FDelegateHandle RegisterStreamQuery(const FGuid& EndpointId, FStreamQueryDelegate Delegate);` — Registers a delegate to invoke for querying an endpoint about its registered streams.
- L35 _public prototype_ `FDelegateHandle RegisterAuthorityQuery(const FGuid& EndpointId, FAuthorityQueryDelegate Delegate);` — Registers a delegate to invoke for querying an endpoint about its authority.
- L37 _public prototype_ `void UnregisterStreamQuery(const FDelegateHandle& Handle);`
- L38 _public prototype_ `void UnregisterAuthorityQuery(const FDelegateHandle& Handle);`
- L43 _private member_ `const TWeakPtr<FToken> Token;` — Used to check whether we were destroyed after a response is received.
- L51 _private member_ `const IConcertSyncClient& OwningClient;` — Used to send queries. This FRegularQueryService's owner is supposed to make sure this FRegularQueryService is destroyed when the client shuts down.
- L54 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastStreamQueryDelegate, const TArray<FConcertBaseStreamInfo>&);` — We use a multicast delegate here because it handles unsubscribing while being Broadcast
- L55 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastAuthorityQueryDelegate, const TArray<FConcertAuthorityClientInfo>&);`
- L66 _private member_ `TMap<FGuid, FStreamQueryInfo> StreamQueryInfos;`
- L67 _private member_ `TMap<FGuid, FAuthorityQueryInfo> AuthorityQueryInfos;`
- L69 _private member_ `bool bIsHandlingQueryResponse = false;`
- L72 _private prototype_ `void SendQueryEvent();` — Queries the server for the client's current state.
- L74 _private prototype_ `void BuildStreamRequest(FConcertReplication_QueryReplicationInfo_Request& Request) const;`
- L75 _private prototype_ `void BuildAuthorityRequest(FConcertReplication_QueryReplicationInfo_Request& Request) const;`
- L78 _private prototype_ `void HandleQueryResponse(const FConcertReplication_QueryReplicationInfo_Response& Response);` — Handles the server's response.
- L79 _private prototype_ `void CompactDelegates();`

#### struct `UE::MultiUserClient::Replication::FStreamAndAuthorityQueryService::FStreamQueryInfo`  
`struct FStreamQueryInfo`  
_L56-60_
- L58 _public member_ `TSet<FDelegateHandle> Handles;`
- L59 _public member_ `FMulticastStreamQueryDelegate Delegate;`

#### struct `UE::MultiUserClient::Replication::FStreamAndAuthorityQueryService::FAuthorityQueryInfo`  
`struct FAuthorityQueryInfo`  
_L61-65_
- L63 _public member_ `TSet<FDelegateHandle> Handles;`
- L64 _public member_ `FMulticastAuthorityQueryDelegate Delegate;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L15 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FStreamQueryDelegate, const TArray<FConcertBaseStreamInfo>&);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FStreamQueryDelegate, const TArray<FConcertBaseStreamInfo>&);` (scope `UE::MultiUserClient::Replication`)
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FAuthorityQueryDelegate, const TArray<FConcertAuthorityClientInfo>&);`
- L18 _prototype_ `DECLARE_DELEGATE_OneParam(FAuthorityQueryDelegate, const TArray<FConcertAuthorityClientInfo>&);` (scope `UE::MultiUserClient::Replication`)
- L54 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastStreamQueryDelegate, const TArray<FConcertBaseStreamInfo>&);` — We use a multicast delegate here because it handles unsubscribing while being Broadcast
- L55 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastAuthorityQueryDelegate, const TArray<FConcertAuthorityClientInfo>&);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/Util/StreamRequestUtils.h` (Private)


#### struct `UE::MultiUserClient::Replication::FStreamChangelist`  
`struct FStreamChangelist`  
_L14-18_
- desc: Describes changes that MU clients make to the objects in a stream.
- L16 _public member_ `TSet<FConcertObjectInStreamID> ObjectsToRemove;`
- L17 _public member_ `TMap<FConcertObjectInStreamID, FConcertReplication_ChangeStream_PutObject> ObjectsToPut;`

#### struct `UE::MultiUserClient::Replication::FFrequencyChangelist`  
`struct FFrequencyChangelist`  
_L21-28_
- desc: Describes changes that MU clients make to the frequency settings in a stream.
- L23 _public member_ `TSet<FSoftObjectPath> OverridesToRemove;`
- L24 _public member_ `TMap<FSoftObjectPath, FConcertObjectReplicationSettings> OverridesToAdd;`
- L25 _public member_ `TOptional<FConcertObjectReplicationSettings> NewDefaults;`
- L27 _public function_ `bool IsEmpty() const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L31 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L31 _namespace_ `namespace StreamRequestUtils` (scope `UE::MultiUserClient::Replication`)
- L39 _prototype_ `FConcertReplication_ChangeStream_Request BuildChangeRequest_CreateNewStream( const FGuid& StreamId, const FStreamChangelist& ObjectChanges, FFrequencyChangelist FrequencyChanges = FFrequencyChangelist() );` (scope `UE::MultiUserClient::Replication::StreamRequestUtils`) — Builds a request for creating a new stream. @param StreamId The stream that should be modified @param ObjectChanges The object changes to be made @param FrequencyChanges The frequency changes to be made
- L51 _prototype_ `FConcertReplication_ChangeStream_Request BuildChangeRequest_UpdateExistingStream( const FGuid& StreamId, FStreamChangelist ObjectChanges, FFrequencyChangelist FrequencyChanges = FFrequencyChangelist() );` (scope `UE::MultiUserClient::Replication::StreamRequestUtils`) — Builds a request for updating a preexisting stream. @param StreamId The stream that should be modified @param ObjectChanges The object changes to be made @param FrequencyChanges The frequency changes to be made

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Misc/Util/SynchronizedRequestUtils.h` (Private)


#### struct `UE::MultiUserClient::Replication::FParallelExecutionResult`  
`struct FParallelExecutionResult`  
_L18-27_
- L21 _public member_ `bool bWasCancelled = false;` — True if the TSharedPtr<IParallelSubmissionOperation> was destroyed before completion of submissions.
- L24 _public member_ `TMap<FGuid, FSubmitStreamChangesResponse> StreamResponses;` — Maps client IDs to responses from the submissions. Empty if bWasCancelled.
- L26 _public member_ `TMap<FGuid, FSubmitAuthorityChangesResponse> AuthorityResponses;` — Maps client IDs to responses from the submissions. Empty if bWasCancelled.

#### class `UE::MultiUserClient::Replication::IParallelSubmissionOperation`  
`class IParallelSubmissionOperation`  
_L30-41_
- desc: Result of ExecuteParallelStreamChanges. Handles correctly unregistering when the object is destroyed.
- L38 _public prototype_ `virtual TFuture<FParallelExecutionResult> OnCompletedFuture_AnyThread() = 0;` — @return Future completed when all parallel submissions have been completed. @note This can complete on any thread. Usually this finishes on the game thread but timeouts usually occur on the messaging (UDP) thread.
- L40 _public prototype_ `virtual ~IParallelSubmissionOperation() = default;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L13 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L54 _prototype_ `TSharedPtr<IParallelSubmissionOperation> ExecuteParallelStreamChanges(FOnlineClientManager& ClientManager, TMap<FGuid, FSubmissionParams> ParallelOperations);` (scope `UE::MultiUserClient::Replication`) — Executes the stream changes in parallel on the remote clients. @param ClientManager Used to get the clients to send to @param ParallelOperations The operations to complete @return Object you can get future through. This object also handles correct unregistering from other systems when you destroy it. @note The returned object MUST be destroyed on the game thread.
- L56 _prototype_ `TSharedPtr<IParallelSubmissionOperation> ExecuteParallelStreamChanges(FOnlineClientManager& ClientManager, TMap<FGuid, FConcertReplication_ChangeStream_Request> ParallelOperations);` (scope `UE::MultiUserClient::Replication`) — Util for transforming into FSubmissionParams

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/MultiUserReplicationCVars.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L9 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L12 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogRemoteChangeRequestsAndResponses;` (scope `UE::MultiUserClient::Replication`) — Whether to log FMultiUser_ChangeRemote_Request & FMultiUser_ChangeRemote_Response received from other MU clients.
- L16 _function_ `template<typename TMessage> static void LogNetworkMessage(const TAutoConsoleVariable<bool>& ShouldLog, const TMessage& Message)` (scope `UE::MultiUserClient::Replication`) — `USTRUCT()`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/MultiUserReplicationManager.h` (Private)


#### enum `UE::MultiUserClient::Replication::EMultiUserReplicationConnectionState`  
`enum class EMultiUserReplicationConnectionState : uint8`  
_L36-41_
- L38 _public enumerator_ `Connecting`
- L39 _public enumerator_ `Connected`
- L40 _public enumerator_ `Disconnected`

#### class `UE::MultiUserClient::Replication::FMultiUserReplicationManager`  
`class FMultiUserReplicationManager : public TSharedFromThis<FMultiUserReplicationManager> , public FNoncopyable , public IMultiUserReplication`  
_L49-211_
- inherits: `TSharedFromThis<FMultiUserReplicationManager>,FNoncopyable,IMultiUserReplication`
- desc: Interacts with the replication system on behalf of Multi-User to execute actions specific to Multi-User workflows; this is opposed to other uses of the replication API, e.g. users using the system in a shipped game. This class implements the Fence design pattern. All knowledge Multi-User might need should be encapsulated by this class.
- L56 _public prototype_ `FMultiUserReplicationManager(TSharedRef<IConcertSyncClient> InClient);`
- L66 _public prototype_ `void JoinReplicationSession();` — Joins the replication session. Joining occurs automatically after successful connection to the Concert session. However the request can be rejected by the server. In that case, the user can manually attempt to connect again, which is what this is exposed publicly for.
- L69 _public function_ `FOnlineClientManager* GetOnlineClientManager()` — @note This pointer is only valid while connected and can become stale. Listen for OnReplicationConnectionStateChanged.
- L70 _public function_ `const FOnlineClientManager* GetOnlineClientManager() const`
- L73 _public function_ `FOfflineClientManager* GetOfflineClientManager()` — @note This pointer is only valid while connected and can become stale. Listen for OnReplicationConnectionStateChanged.
- L74 _public function_ `const FOfflineClientManager* GetOfflineClientManager() const`
- L77 _public function_ `FUnifiedClientView* GetUnifiedClientView()` — @note This pointer is only valid while connected and can become stale. Listen for OnReplicationConnectionStateChanged.
- L78 _public function_ `const FUnifiedClientView* GetUnifiedClientView() const`
- L81 _public function_ `FMuteStateManager* GetMuteManager()` — @note This pointer is only valid while connected and can become stale. Listen for OnReplicationConnectionStateChanged.
- L82 _public function_ `const FMuteStateManager* GetMuteManager() const`
- L85 _public function_ `FPresetManager* GetPresetManager()` — @note This pointer is only valid while connected and can become stale. Listen for OnReplicationConnectionStateChanged.
- L86 _public function_ `const FPresetManager* GetPresetManager() const`
- L89 _public function_ `FUserPropertySelector* GetUserPropertySelector()` — @note This pointer is only valid while connected and can become stale. Listen for OnReplicationConnectionStateChanged.
- L90 _public function_ `const FUserPropertySelector* GetUserPropertySelector() const`
- L93 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnReplicationConnectionStateChanged, EMultiUserReplicationConnectionState );` — Called when the connection to the replication system changes.
- L94 _public function_ `FOnReplicationConnectionStateChanged& OnReplicationConnectionStateChanged()`
- L95 _public function_ `EMultiUserReplicationConnectionState GetConnectionState() const`
- L98 _public prototype_ `virtual const FConcertObjectReplicationMap* FindReplicationMapForClient(const FGuid& ClientId) const override;`
- L99 _public prototype_ `virtual const FConcertStreamFrequencySettings* FindReplicationFrequenciesForClient(const FGuid& ClientId) const override;`
- L100 _public prototype_ `virtual bool IsReplicatingObject(const FGuid& ClientId, const FSoftObjectPath& ObjectPath) const override;`
- L101 _public prototype_ `virtual void RegisterReplicationDiscoverer(TSharedRef<IReplicationDiscoverer> Discoverer) override;`
- L102 _public prototype_ `virtual void RemoveReplicationDiscoverer(const TSharedRef<IReplicationDiscoverer>& Discoverer) override;`
- L103 _public prototype_ `virtual TSharedRef<IClientChangeOperation> EnqueueChanges(const FGuid& ClientId, TAttribute<FChangeClientReplicationRequest> SubmissionParams) override;`
- L104 _public prototype_ `virtual void ForEachOfflineClient(TFunctionRef<EBreakBehavior(const IOfflineReplicationClient&)> Callback) const override;`
- L105 _public prototype_ `virtual bool FindOfflineClient(const FGuid& ClientId, TFunctionRef<void(const IOfflineReplicationClient&)> Callback) const override;`
- L106 _public function_ `virtual FOnServerStateChanged& OnStreamServerStateChanged() override`
- L107 _public function_ `virtual FOnServerStateChanged& OnAuthorityServerStateChanged() override`
- L108 _public function_ `virtual FOnOfflineClientsChanged& OnOfflineClientsChanged() override`
- L109 _public function_ `virtual FOnServerStateChanged& OnOfflineClientContentChanged() override`
- L115 _private member_ `const TSharedRef<IConcertSyncClient> Client;` — Client through which the replication bridge is accessed.
- L118 _private member_ `EMultiUserReplicationConnectionState ConnectionState = EMultiUserReplicationConnectionState::Disconnected;` — Reflects the current connection state to the replication system (note: this does not reflect the state to the concert session).
- L172 _private member_ `TOptional<FConnectedState> ConnectedState;` — Set when connected to a replication session.
- L175 _private member_ `FReplicationDiscoveryContainer DiscoveryContainer;` — Allows external modules to register discoverers for adding properties, etc.
- L178 _private member_ `FOnReplicationConnectionStateChanged OnReplicationConnectionStateChangedDelegate;` — Called when ConnectionState changes.
- L181 _private member_ `FOnServerStateChanged OnStreamServerStateChangedDelegate;` — Triggers when a client's known server state has changed.
- L183 _private member_ `FOnServerStateChanged OnAuthorityServerStateChangedDelegate;` — Triggers when a client's known server state has changed.
- L185 _private member_ `FOnOfflineClientsChanged OnOfflineClientsChangedDelegate;` — Triggers when the offline clients have changed.
- L187 _private member_ `FOnServerStateChanged OnOfflineClientContentChangedDelegate;` — Triggers when the content of an offline client has changed. Also triggered as part of OnOfflineClientsChangedDelegate.
- L190 _private prototype_ `void OnSessionConnectionChanged(IConcertClientSession& ConcertClientSession, EConcertConnectionStatus ConcertConnectionStatus);` — Callback into Concert for when client connection has changed.
- L192 _private prototype_ `void OnLeaveSession(IConcertClientSession&);` — Leaves the current replication session
- L195 _private prototype_ `void HandleReplicationSessionJoined(const ConcertSyncClient::Replication::FJoinReplicatedSessionResult& JoinSessionResult);` — Handles server response for joining replication session
- L197 _private prototype_ `void SetConnectionStateAndBroadcast(EMultiUserReplicationConnectionState NewState);` — Sets the current connection state and triggers OnReplicationConnectionStateChangedDelegate.
- L199 _private prototype_ `void RestoreContentFromLastTime();` — Restores the content the client had when they last left the session.
- L202 _private prototype_ `void SetupClientConnectionEvents();` — Sets up delegates for implementing the broadcasting of OnStreamServerStateChangedDelegate and OnAuthorityServerStateChangedDelegate.
- L203 _private function_ `void OnInternalOfflineClientsChanged() const`
- L204 _private function_ `void OnInternalOfflineClientContentChanged(FOfflineClient& OfflineClient) const`
- L205 _private function_ `void OnReplicationClientConnected(FRemoteClient& RemoteClient) const`
- L208 _private prototype_ `void SetupClientDelegates(FOnlineClient& InClient) const;` — Sets up delegates for reacting to content changes.
- L209 _private prototype_ `void OnClientStreamServerStateChanged(const FGuid EndpointId) const;`
- L210 _private prototype_ `void OnClientAuthorityServerStateChanged(const FGuid EndpointId) const;`

#### struct `UE::MultiUserClient::Replication::FMultiUserReplicationManager::FConnectedState`  
`struct FConnectedState`  
_L120-170_
- L126 _public member_ `TSharedRef<IConcertSyncClient> Client;` — Keep the client alive because it is referenced by the lower systems.
- L132 _public member_ `FRegularQueryService QueryService;` — Regularly queries server state (only if a system is subscribed to it), such as remote client streams, authority, and global mute state. Shared by subsystems, such as remote clients. This ensures requests are bundled, reducing the number of network requests.
- L141 _public member_ `FOnlineClientManager OnlineClientManager;` — Synchronizes replication settings of clients connected to the session. Creates UMultiUserReplicationSessionPreset, which is displayed by UI. Keeps the preset in sync with the state on the server. Only valid when ConnectionState == EMultiUserReplicationConnectionState::Connected.
- L143 _public member_ `FOfflineClientManager OfflineClientManager;` — Keeps track of clients that were once in the session but are no longer to be able to display their old settings in the UI.
- L145 _public member_ `FUnifiedClientView UnifiedClientView;` — Adapter abstraction that allows systems to query online and offline clients with a unified interface.
- L148 _public member_ `FMuteStateManager MuteManager;` — Interacts with the mute global server mute system.
- L150 _public member_ `FPresetManager PresetManager;` — Saves and loads presets for the session. Accessed by UI.
- L156 _public member_ `FUserPropertySelector PropertySelector;` — Manages the properties the user is iterating on in the replication session. The bottom-half property section in the replication UI uses this to keep track of which properties the user has selected for which properties.
- L158 _public member_ `FAutoPropertyOwnershipTaker AutoPropertyOwnershipTaker;` — Automatically takes and releases ownership over properties the user adds to the set of selected properties.
- L161 _public member_ `FChangeLevelHandler ChangeLevelHandler;` — Clears local client's registered objects when leaving map.
- L163 _public member_ `FPreventReplicatedPropertyTransaction PreventReplicatedPropertyTransaction;` — Prevents recording of transactions that change properties that are being replicated by a client.
- L165 _public member_ `FReplicationUserNotifier UserNotifier;` — This system notifies users when requests go wrong
- L167 _public member_ `FAnalyticsHandler AnalyticsHandler;` — Sends analytics data about replication use.
- L169 _public prototype_ `FConnectedState(TSharedRef<IConcertSyncClient> InClient, FReplicationDiscoveryContainer& InDiscoveryContainer);`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L32 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L93 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnReplicationConnectionStateChanged, EMultiUserReplicationConnectionState );` — Called when the connection to the replication system changes.

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Muting/MuteChangeTracker.h` (Private)


#### class `UE::MultiUserClient::Replication::FMuteChangeTracker`  
`class FMuteChangeTracker : public FNoncopyable`  
_L20-58_
- inherits: `FNoncopyable`
- desc: Keeps track of changes to the mute state the local application has made but not yet submitted.
- L23 _public prototype_ `FMuteChangeTracker(FMuteStateSynchronizer& InMuteStateSynchronizer UE_LIFETIMEBOUND, const FGlobalAuthorityCache& InAuthorityCache UE_LIFETIMEBOUND);`
- L24 _public prototype_ `~FMuteChangeTracker();`
- L27 _public prototype_ `bool CanChangeMuteState(const FSoftObjectPath& ObjectPath) const;` — @return Whether the mute state of this object can be changed. True if the object is at least in one client stream.
- L29 _public prototype_ `bool IsMuted(const FSoftObjectPath& ObjectPath) const;` — @return Returns whether ObjectPath according to the local, unsubmitted changes or returns the state on the server if no local changes have been made.
- L32 _public prototype_ `void ToggleMuteState(const FSoftObjectPath& ObjectPath);` — Toggles the mute state of ObjectPath if allowed. The mute setting will apply to all subobjects as well (unless they are overriden, too).
- L35 _public function_ `void ClearLocalMuteOverrides()` — Clears all local changes, so they do not show up the next time BuildChangeRequest is called.
- L37 _public prototype_ `void RefreshChanges();` — Compares the local changes against the server state and kicks out any (now) invalid changes.
- L40 _public prototype_ `FConcertReplication_ChangeMuteState_Request BuildChangeRequest() const;` — @return A request contains all the pending local changes.
- L43 _public function_ `FOnLocalMuteStateOverriden& OnLocalMuteStateOverriden()` — Broadcasts when there a local change has been made that can be submitted.
- L48 _private member_ `FMuteStateSynchronizer& MuteStateSynchronizer;` — Knows of the server state. Used to diff state.
- L51 _private member_ `const FGlobalAuthorityCache& AuthorityCache;` — Used to check whether an object is referenced in any stream. Needed so we don't build requests containing objects the server does not know about.
- L54 _private member_ `TMap<FSoftObjectPath, bool> LocalChanges;` — Maps objects to whether they should be muted.
- L57 _private member_ `FOnLocalMuteStateOverriden OnLocalMuteStateOverridenDelegate;` — Broadcasts when there a local change has been made that can be submitted.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnLocalMuteStateOverriden);`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnLocalMuteStateOverriden);` (scope `UE::MultiUserClient::Replication`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Muting/MuteStateManager.h` (Private)


#### class `UE::MultiUserClient::Replication::FMuteStateManager`  
`class FMuteStateManager : public FNoncopyable`  
_L21-62_
- inherits: `FNoncopyable`
- desc: Manages all interaction with the application instance to the server regarding muting.
- L25 _public prototype_ `FMuteStateManager(const IConcertSyncClient& InClient UE_LIFETIMEBOUND, FMuteStateQueryService& InMuteQueryService UE_LIFETIMEBOUND, const FGlobalAuthorityCache& InAuthorityCache UE_LIFETIMEBOUND);`
- L26 _public prototype_ `~FMuteStateManager();`
- L29 _public function_ `FMuteChangeTracker& GetChangeTracker()` — @return Object with which the objects' mute state can be changed and queried.
- L31 _public function_ `const FMuteStateSynchronizer& GetSynchronizer() const` — @return Object with which you can query whether an object is muted.
- L34 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMuteRequestFailure, const FConcertReplication_ChangeMuteState_Request&, const FConcertReplication_ChangeMuteState_Response&);` — Broadcasts when a mute request fails.
- L35 _public function_ `FOnMuteRequestFailure& OnMuteRequestFailure()`
- L40 _private member_ `const TSharedRef<FToken> Token = FToken::Make();` — When the mute request is answered, we use this to detect whether we've been destroyed.
- L43 _private member_ `const IConcertSyncClient& Client;` — Used to send submit mute changes to the server.
- L45 _private member_ `FMuteStateQueryService& MuteQueryService;` — We'll request an instant refresh of the server's mute state after submitting a request..
- L48 _private member_ `FMuteStateSynchronizer MuteStateSynchronizer;` — Knows of the current mute state on the server.
- L50 _private member_ `FMuteChangeTracker ChangeTracker;` — Tracks locally made changes that still need to be submitted to the server.
- L53 _private member_ `FOnMuteRequestFailure OnMuteRequestFailureDelegate;` — Broadcasts when a mute request fails.
- L56 _private member_ `bool bIsMuteChangeInProgress = false;` — Whether we're currently waiting for a response to a mute change.
- L59 _private prototype_ `void OnEndOfFrame();` — When a change is made to ChangeTracker, we subscribe FCoreDelegates::OnEndFrame to this function.
- L61 _private prototype_ `void SendChangeRequest();` — Checks the changes pending in ChangeTracker and sends them to the server, if any.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L15 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMuteRequestFailure, const FConcertReplication_ChangeMuteState_Request&, const FConcertReplication_ChangeMuteState_Response&);` — Broadcasts when a mute request fails.

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Muting/MuteStateSynchronizer.h` (Private)


#### class `UE::MultiUserClient::Replication::FMuteStateSynchronizer`  
`class FMuteStateSynchronizer : public FNoncopyable`  
_L27-66_
- inherits: `FNoncopyable`
- desc: Responsible for answering questions about whether an object is muted. In the future, this may be extended with reasons (e.g. object Actor.Component is muted because Actor is muted).
- L31 _public prototype_ `FMuteStateSynchronizer(FMuteStateQueryService& InMuteQueryService UE_LIFETIMEBOUND);`
- L32 _public prototype_ `~FMuteStateSynchronizer();`
- L35 _public function_ `bool IsMuted(const FSoftObjectPath& ObjectPath) const` — @return Whether ObjectPath is muted.
- L37 _public function_ `const TMap<FSoftObjectPath, FConcertReplication_ObjectMuteSetting>& GetExplicitlyMutedObjects() const`
- L38 _public function_ `const TMap<FSoftObjectPath, FConcertReplication_ObjectMuteSetting>& GetExplicitlyUnmutedObjects() const`
- L44 _public prototype_ `void UpdateStateFromSuccessfulChange(const FConcertReplication_ChangeMuteState_Request& Request);` — Update the mute state after the local application has successfully changed mute state. FMuteStateQueryService will eventually notify us of the change but this applies it instantaneously.
- L47 _public function_ `FOnMuteStateChanged& OnMuteStateChanged()` — Broadcasts whent the mute state changes (either because FMuteStateQueryService received updated state or because the local application has successfully made a change request).
- L52 _private member_ `FMuteStateQueryService& MuteQueryService;` — Updates us with the new mute state from the server regularily.
- L55 _private member_ `TMap<FSoftObjectPath, FConcertReplication_ObjectMuteSetting> ExplicitlyMutedObjects;` — All explicitly muted objects on the server.
- L57 _private member_ `TMap<FSoftObjectPath, FConcertReplication_ObjectMuteSetting> ExplicitlyUnmutedObjects;` — All explicitly unmuted objects on the server.
- L59 _private member_ `TSet<FSoftObjectPath> MutedObjects;` — A cached, final view of muted objects that combines ExplicitlyMutedObjects and ExplicitlyUnmutedObjects.
- L62 _private member_ `FOnMuteStateChanged OnMuteStateChangedDelegate;` — Broadcasts whent the mute state changes (either because FMuteStateQueryService received updated state or because the local application has successfully made a change request).
- L65 _private prototype_ `void UpdateFromServerState(const FConcertReplication_QueryMuteState_Response& NewMuteState);` — Updates MutedObjects from the mute state on the server.

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L17 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMuteStateChanged);`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMuteStateChanged);` (scope `UE::MultiUserClient::Replication`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Preset/PresetManager.h` (Private)


#### class `UE::MultiUserClient::Replication::FPresetManager`  
`class FPresetManager : public FNoncopyable`  
_L30-72_
- inherits: `FNoncopyable`
- desc: Implements all logic for managing presets in the MU session: saving and loading presets. The UI directly interfaces with this class.
- L34 _public prototype_ `FPresetManager( const IConcertSyncClient& SyncClient UE_LIFETIMEBOUND, const FOnlineClientManager& ClientManager UE_LIFETIMEBOUND, const FMuteStateSynchronizer& MuteStateSynchronizer UE_LIFETIMEBOUND );`
- L39 _public prototype_ `~FPresetManager();`
- L42 _public function_ `bool IsPresetChangeInProgress() const` — @return Whether any preset is currently being applied.
- L45 _public prototype_ `TFuture<FReplaceSessionContentResult> ReplaceSessionContentWithPreset(const UMultiUserReplicationSessionPreset& Preset, EApplyPresetFlags Flags = EApplyPresetFlags::None);` — Applies Preset to all clients in the session.
- L48 _public prototype_ `ECanSaveResult CanSavePreset(const FSavePresetOptions& Options = {}) const;` — @return Whether a preset can be saved (i.e. at least one client is included).
- L53 _public prototype_ `UMultiUserReplicationSessionPreset* ExportToPresetAndSaveAs(const FSavePresetOptions& Options = {});` — Exports the current session content to a preset, asks the user where to save it, then saves it. @return A future that finishes when saving has completed.
- L58 _private member_ `const IConcertSyncClient& SyncClient;` — Used to get display information of clients in the session.
- L60 _private member_ `const FOnlineClientManager& ClientManager;` — Used to get the clients' replication content.
- L62 _private member_ `const FMuteStateSynchronizer& MuteStateSynchronizer;` — Used to get the mute state when saving.
- L65 _private member_ `TSharedPtr<TPromise<FReplaceSessionContentResult>> InProgressSessionReplacementOp;` — Non-null for as long as the ReplaceSessionContentWithPreset network request takes.
- L68 _private prototype_ `UMultiUserReplicationSessionPreset* ExportToPreset(const FSavePresetOptions& Options) const;` — Exports the current session content to a preset.
- L71 _private prototype_ `void OnPostRemoteEditApplied(const ConcertSyncClient::Replication::FRemoteEditEvent&) const;` — Called when the local client receives a remote edit.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L19 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L21 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Preset/PresetUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L16 _function_ `template<typename TLambda> requires std::is_invocable_r_v<EBreakBehavior, TLambda, const FSoftObjectPath& , const FString& > void ForEachSavedActorLabel(const UMultiUserReplicationSessionPreset& Preset, TLambda&& Callback)` (scope `UE::MultiUserClient::Replication`) — Lists out all actors saved in the preset.

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Preset/ReplaceSessionContentResult.h` (Private)


#### enum `UE::MultiUserClient::Replication::EReplaceSessionContentErrorCode`  
`enum class EReplaceSessionContentErrorCode : uint8`  
_L9-29_
- L12 _public enumerator_ `Success` — Request completed successfully.
- L14 _public enumerator_ `NoObjectsFound` — The preset did not make any changes because no objects could be found in the world.
- L16 _public enumerator_ `NoWorld` — GWorld was not valid.
- L19 _public enumerator_ `Cancelled` — Request cancelled because FPresetManager was destroyed - probably because the use left the session during the request.
- L21 _public enumerator_ `InProgress` — Another locally initiated operation is already in progress.
- L24 _public enumerator_ `Timeout` — Request timed out
- L26 _public enumerator_ `FeatureDisabled` — The feature is not enabled (i.e. EConcertSyncSessionFlags::ShouldEnableRemoteEditing or EConcertSyncSessionFlags::ShouldAllowGlobalMuting were not set on the server).
- L28 _public enumerator_ `Rejected` — Server rejected the change because it was not valid

#### struct `UE::MultiUserClient::Replication::FReplaceSessionContentResult`  
`struct FReplaceSessionContentResult`  
_L32-41_
- desc: Result of FPresetManager::ReplaceSessionContentWithPreset.
- L34 _public member_ `EReplaceSessionContentErrorCode ErrorCode;`
- L36 _public function_ `FReplaceSessionContentResult(EReplaceSessionContentErrorCode ErrorCode = EReplaceSessionContentErrorCode::Success) : ErrorCode(ErrorCode)`
- L40 _public function_ `bool IsSuccess() const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L7 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Preset/SavePresetOptions.h` (Private)


#### enum `UE::MultiUserClient::Replication::EApplyPresetFlags`  
`enum class EApplyPresetFlags : uint8`  
_L13-18_
- L15 _public enumerator_ `None`
- L17 _public enumerator_ `ClearUnreferencedClients = 1 << 0` — If set clients that were not in the session when the preset was created will get their content reset, too.

#### enum `UE::MultiUserClient::Replication::EFilterResult`  
`enum class EFilterResult : uint8`  
_L21-21_
- L21 _public enumerator_ `enum class EFilterResult : uint8 { Include, Exclude }; DECLARE_DELEGATE_RetVal_OneParam(EFilterResult, FFilterClientForPreset, const FConcertClientInfo&); struct FSavePresetOptions { FFilterClientForPreset ClientFilterDelegate;`
- L21 _public enumerator_ `enum class EFilterResult : uint8 { Include, Exclude }; DECLARE_DELEGATE_RetVal_OneParam(EFilterResult, FFilterClientForPreset, const FConcertClientInfo&); struct FSavePresetOptions { FFilterClientForPreset ClientFilterDelegate;`

#### struct `UE::MultiUserClient::Replication::FSavePresetOptions`  
`struct FSavePresetOptions`  
_L25-29_
- desc: Options for saving a preset
- L28 _public member_ `FFilterClientForPreset ClientFilterDelegate;` — Filter that decides whether a client should be included in the preset.

#### enum `UE::MultiUserClient::Replication::ECanSaveResult`  
`enum class ECanSaveResult : uint8`  
_L31-37_
- L34 _public enumerator_ `Yes` — Yes, a preset can be saved.
- L36 _public enumerator_ `NoClients` — There are no clients to save for

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L19 _prototype_ `ENUM_CLASS_FLAGS(EApplyPresetFlags);` (scope `UE::MultiUserClient::Replication`)
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EFilterResult, FFilterClientForPreset, const FConcertClientInfo&);`
- L22 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(EFilterResult, FFilterClientForPreset, const FConcertClientInfo&);` (scope `UE::MultiUserClient::Replication`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Stream/Discovery/MultiUserStreamExtender.h` (Private)


#### class `UE::MultiUserClient::Replication::FMultiUserStreamExtender`  
`class FMultiUserStreamExtender : public ConcertSharedSlate::IStreamExtender`  
_L24-55_
- inherits: `ConcertSharedSlate::IStreamExtender`
- desc: When the user adds an object, this object handles auto selecting properties and adding additional objects from context. The following sources exist: - Static Settings: user can specify properties & objects in the MU project settings - Dynamic API: by using the IMultiUserReplication, external modules can register dynamic rules for auto-discovery using IReplicationDiscoverer. Every FReplicationClient owns an instance of this and executes it when an object is added for the client by the local editor. Effectively, this is
- L32 _public prototype_ `FMultiUserStreamExtender(const FGuid& InClientId, FReplicationDiscoveryContainer& InRegisteredExtenders);` — @param InClientId The ID of the owning FReplicationClient instance. @param InRegisteredExtenders Holds all IReplicationDiscoverer that were registered to Multi User. The caller ensures it outlives the constructed instance.
- L35 _public function_ `void SetShouldExtend(bool bValue)` — Sets whether the stream should be extended.
- L38 _public prototype_ `virtual void ExtendStream(UObject& ExtendedObject, ConcertSharedSlate::IStreamExtensionContext& Context) override;`
- L44 _private member_ `const FGuid ClientId;` — The client ID to which this extender is adds objects.
- L47 _private member_ `bool bShouldExtend = false;` — Whether this extender is enabled.
- L50 _private member_ `ConcertClientSharedSlate::FStreamExtenderBySettings ExtendBySettings;` — Handles properties from the MU settings.
- L52 _private member_ `FReplicationDiscoveryContainer& RegisteredExtenders;` — Allows generic extenders to extend added objects. These can be added via the IMultiUserReplication interface.
- L54 _private prototype_ `void ExtendStreamWithRegisteredDiscoverers(UObject& ExtendedObject, ConcertSharedSlate::IStreamExtensionContext& Context) const;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L10 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Stream/Discovery/ReplicationDiscoveryContainer.h` (Private)


#### class `UE::MultiUserClient::Replication::FReplicationDiscoveryContainer`  
`class FReplicationDiscoveryContainer : public IReplicationDiscoverer`  
_L20-35_
- inherits: `IReplicationDiscoverer`
- desc: Just holds a bunch of IReplicationDiscoverer and calls forward the function calls to them. @see IReplicationDiscovery for the purpose of IReplicationDiscoverer.
- L24 _public prototype_ `void AddDiscoverer(TSharedRef<IReplicationDiscoverer> Discoverer);`
- L25 _public prototype_ `void RemoveDiscoverer(const TSharedRef<IReplicationDiscoverer>& Discoverer);`
- L28 _public prototype_ `virtual void DiscoverReplicationSettings(const FReplicationDiscoveryParams& Params) override;`
- L34 _private member_ `TArray<TSharedRef<IReplicationDiscoverer>> Discoverers;` — The discoverers to run through

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Stream/IClientStreamSynchronizer.h` (Private)


#### class `UE::MultiUserClient::Replication::IClientStreamSynchronizer`  
`class IClientStreamSynchronizer`  
_L19-37_
- desc: Keeps track of a client's registered streams. Exposes ways for observing and mutating streams. The implementation varies depending on whether the client corresponds to the local or a remote editor.
- L24 _public prototype_ `virtual FGuid GetStreamId() const = 0;` — @return The managed client's stream ID.
- L27 _public prototype_ `virtual const FConcertObjectReplicationMap& GetServerState() const = 0;` — @return What local instance thinks the client's server state is.
- L30 _public prototype_ `virtual const FConcertStreamFrequencySettings& GetFrequencySettings() const = 0;` — @return What the local instance thinks the client's replication frequencies are.
- L32 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnServerStateChanged);`
- L34 _public prototype_ `virtual FOnServerStateChanged& OnServerStreamChanged() = 0;` — @return Event executed when the result of GetServerState has been updated.
- L36 _public prototype_ `virtual ~IClientStreamSynchronizer() = default;`

#### class `UE::MultiUserClient::Replication::FStreamSynchronizer_Base`  
`class FStreamSynchronizer_Base : public IClientStreamSynchronizer`  
_L40-53_
- inherits: `IClientStreamSynchronizer`
- desc: Util base class for implementing the events
- L46 _public function_ `virtual FOnServerStateChanged& OnServerStreamChanged() override`
- L52 _protected member_ `FOnServerStateChanged OnServerStateChangedDelegate;` — Triggered by subclasses when the authority state changes.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnServerStateChanged);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Stream/MultiUserStreamId.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L7 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L10 _variable_ `constexpr FGuid MultiUserStreamID { 0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD };` (scope `UE::MultiUserClient::Replication`) — The stream ID that is used by all Multi-User streams.

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Stream/StreamChangeTracker.h` (Private)


#### class `UE::MultiUserClient::Replication::FStreamChangeTracker`  
`class FStreamChangeTracker : public FNoncopyable`  
_L26-94_
- inherits: `FNoncopyable`
- desc: Knows of the local client's registered replication streams and builds a changelist. The changelist tracks the unconfirmed changes to the client's streams and is updated when the server confirms the change.
- L30 _public prototype_ `DECLARE_DELEGATE(FOnModifyReplicationMap);`
- L31 _public prototype_ `FStreamChangeTracker( IClientStreamSynchronizer& InStreamSynchronizer, TAttribute<FConcertObjectReplicationMap*> InStreamWithInProgressChangesAttribute, FOnModifyReplicationMap InOnModifyReplicationMapDelegate );`
- L36 _public prototype_ `~FStreamChangeTracker();`
- L46 _public prototype_ `void RefreshChangesCache();` — Clears and rebuilds CachedDeltaChange in response to the underlying StreamWithInProgressChangesAttribute having been changed. This iterates through all elements, which is suboptimal. However, this is needed e.g. after an undo & redo command. In the future, we could implement a more efficient version that just responds to the relevant events (like adding an object). While this function does redundant work, it should really not be a big performance bog after all. Also it is called infrequently e.g. in response to a user pressing a button so we should be fine.
- L47 _public function_ `const FStreamChangelist& GetCachedDeltaChange() const`
- L50 _public prototype_ `bool HasChanges() const;` — @return Whether there are any changes that that can be submitted to the server (excludes those with warnings).
- L53 _public prototype_ `bool DoesObjectHavePropertiesAfterSubmit(const FSoftObjectPath& ObjectPath) const;` — @return If changes are submitted, is ObjectPath in the stream?
- L55 _public prototype_ `const FConcertPropertySelection* GetPropertiesAfterSubmit(const FSoftObjectPath& ObjectPath) const;` — @return Gets the final state the object will have after submission.
- L65 _public prototype_ `EObjectChangeType GetObjectChanges(const FSoftObjectPath& Object) const;` — @return Whether this object's local configuration differs from the server version.
- L70 _private member_ `IClientStreamSynchronizer& StreamSynchronizer;` — Keeps track of the edited stream's server state. Outlives the FStreamChangeTracker instance.
- L76 _private member_ `const TAttribute<FConcertObjectReplicationMap*> StreamWithInProgressChangesAttribute;` — Represents ConfirmedServerState with changes made to it. These changes have not been sent to the server, yet. This is cleared when a change is sent to the server.
- L82 _private member_ `FStreamChangelist CachedDeltaChange;` — The changes that if applied to ConfirmedServerState would result in StreamWithInProgressChangesAttribute. This is updated every time the local client makes changes.
- L85 _private member_ `FOnModifyReplicationMap OnModifyReplicationMapDelegate;` — Called when StreamWithInProgressChangesAttribute is about to be modified.
- L87 _private function_ `FStreamChangelist DiffChanges() const`
- L93 _private prototype_ `static FStreamChangelist DiffChanges(const FGuid& StreamId, const FConcertObjectReplicationMap& Base, const FConcertObjectReplicationMap& Changed);` — Builds the changelist to get from Base to Changed.

#### enum `UE::MultiUserClient::Replication::FStreamChangeTracker::EObjectChangeType`  
`enum class EObjectChangeType`  
_L57-63_
- L59 _public enumerator_ `NoChange`
- L60 _public enumerator_ `Added`
- L61 _public enumerator_ `Removed`
- L62 _public enumerator_ `PropertiesModified`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L20 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L30 _delegate_ `DECLARE_DELEGATE(FOnModifyReplicationMap);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Stream/StreamSynchronizer_LocalClient.h` (Private)


#### class `UE::MultiUserClient::Replication::FStreamSynchronizer_LocalClient`  
`class FStreamSynchronizer_LocalClient : public IClientStreamSynchronizer, public FNoncopyable`  
_L15-44_
- inherits: `IClientStreamSynchronizer,FNoncopyable`
- desc: Asks the local client's IConcertClientReplicationManager about the current state of the streams.
- L19 _public prototype_ `FStreamSynchronizer_LocalClient(TSharedRef<IConcertSyncClient> InLocalClient, const FGuid& InLocalClientStreamId);`
- L23 _public function_ `virtual FGuid GetStreamId() const override`
- L24 _public prototype_ `virtual const FConcertObjectReplicationMap& GetServerState() const override;`
- L25 _public prototype_ `virtual const FConcertStreamFrequencySettings& GetFrequencySettings() const override;`
- L26 _public function_ `virtual FOnServerStateChanged& OnServerStreamChanged() override`
- L32 _private member_ `const FConcertBaseStreamInfo EmptyState;` — Returned by GetServerState when there is no registered stream.
- L35 _private member_ `const TSharedRef<IConcertSyncClient> LocalClient;` — Owning client. Used to send change requests to the server.
- L37 _private member_ `const FGuid LocalClientStreamId;` — The ID of the local client's stream this FLocalClientStreamDiffer is managing.
- L40 _private member_ `FOnServerStateChanged OnServerStateChangedDelegate;` — Event executed when the result of GetServerState has been synched.
- L42 _private prototype_ `void OnPostStreamsChanged();`
- L43 _private prototype_ `const FConcertBaseStreamInfo* GetLocalMultiUserStream() const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Stream/StreamSynchronizer_RemoteClient.h` (Private)


#### class `UE::MultiUserClient::Replication::FStreamSynchronizer_RemoteClient`  
`class FStreamSynchronizer_RemoteClient : public IClientStreamSynchronizer, public FNoncopyable`  
_L17-46_
- inherits: `IClientStreamSynchronizer,FNoncopyable`
- desc: Tracks the state of a remote client by querying the client's state in regular intervals.
- L21 _public prototype_ `FStreamSynchronizer_RemoteClient(const FGuid& RemoteEndpointId, FStreamAndAuthorityQueryService& InQueryService UE_LIFETIMEBOUND);`
- L25 _public prototype_ `virtual FGuid GetStreamId() const override;`
- L26 _public function_ `virtual const FConcertObjectReplicationMap& GetServerState() const override`
- L27 _public function_ `virtual const FConcertStreamFrequencySettings& GetFrequencySettings() const override`
- L28 _public function_ `virtual FOnServerStateChanged& OnServerStreamChanged() override`
- L34 _private member_ `FStreamAndAuthorityQueryService& QueryService;` — Queries the server in regular intervals. This services outlives our object.
- L36 _private member_ `const FDelegateHandle QueryStreamHandle;` — Used to unregister HandleStreamQuery upon destruction.
- L39 _private member_ `FConcertBaseStreamInfo LastKnownServerState;` — Represents what the local client thinks the replication map on the server currently looks like.
- L42 _private member_ `FOnServerStateChanged OnServerStateChangedDelegate;` — Event executed when the result of GetServerState has been synched.
- L45 _private prototype_ `void HandleStreamQuery(const TArray<FConcertBaseStreamInfo>& Streams);` — Called in regular intervals with the contents of the remote client.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/AutoSubmissionPolicy.h` (Private)


#### class `UE::MultiUserClient::Replication::FAutoSubmissionPolicy`  
`class FAutoSubmissionPolicy : public FNoncopyable , FSelfUnregisteringDeferredSubmitter`  
_L34-75_
- inherits: `FNoncopyable,FSelfUnregisteringDeferredSubmitter`
- desc: Automatically submits stream and authority changes as the user makes them. If a change is in progress when the change is made, the changes are queued and sent once the pending submission is done. This policy accumulates all changes until the end of frame and then sends them. This means multiple changes are made in the same frame, only one request will be sent containing all changes.
- L40 _public prototype_ `FAutoSubmissionPolicy( FSubmissionQueue& InSubmissionQueue UE_LIFETIMEBOUND, const FChangeRequestBuilder& InRequestBuilder UE_LIFETIMEBOUND, ConcertSharedSlate::IEditableReplicationStreamModel& InStreamEditorModel UE_LIFETIMEBOUND, FAuthorityChangeTracker& InAuthorityChangeTracker UE_LIFETIMEBOUND, FFrequencyChangeTracker& InFrequencyChangeTracker UE_LIFETIMEBOUND );`
- L47 _public prototype_ `~FAutoSubmissionPolicy();`
- L50 _public prototype_ `void ProcessAccumulatedChangesAndSubmit();` — Checks whether any changes have been made since the last call and submits a change request if so.
- L55 _private member_ `FSubmissionQueue& SubmissionQueue;` — Handles performing the submission
- L57 _private member_ `const FChangeRequestBuilder& RequestBuilder;` — Used to building the requests that are passed to SubmissionWorkflow.
- L60 _private member_ `ConcertSharedSlate::IEditableReplicationStreamModel& StreamEditorModel;` — Informs us when the stream is structurally changed by the user.
- L62 _private member_ `FAuthorityChangeTracker& AuthorityChangeTracker;` — Informs us when authority is changed by the user.
- L64 _private member_ `FFrequencyChangeTracker& FrequencyChangeTracker;` — Informs us when frequency settings are changed by the user.
- L67 _private member_ `bool bIsDirty = false;` — Whether any changes were made.
- L70 _private prototype_ `virtual void PerformSubmission_GameThread(ISubmissionWorkflow& Workflow) override;`
- L73 _private function_ `void OnObjectsChanged(TArrayView<UObject* const>, TArrayView<const FSoftObjectPath>, ConcertSharedSlate::EReplicatedObjectChangeReason)`
- L74 _private prototype_ `void OnChangesDetected();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L9 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L19 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/ChangeRequestBuilder.h` (Private)


#### class `UE::MultiUserClient::Replication::FChangeRequestBuilder`  
`class FChangeRequestBuilder`  
_L23-70_
- desc: Util that knows how to build FConcertReplication_ChangeStream_Request and FConcertReplication_ChangeAuthority_Request based on the local client's changes and knowledge of other remote clients.
- L35 _public prototype_ `FChangeRequestBuilder( const FGuid& InLocalClientId, const FGlobalAuthorityCache& InAuthorityCache UE_LIFETIMEBOUND, IClientStreamSynchronizer& InStreamSynchronizer UE_LIFETIMEBOUND, FStreamChangeTracker& InStreamChangeTracker UE_LIFETIMEBOUND, FAuthorityChangeTracker& InAuthorityChangeTracker UE_LIFETIMEBOUND, FFrequencyChangeTracker& InFrequencyChangeTracker UE_LIFETIMEBOUND );` — @param InLocalClientId Endpoint ID of the client for which the request is being generated @param InAuthorityCache Used to predict conflicts. The caller ensures it outlives the constructed instance. @param InStreamSynchronizer Used to determine whether a new stream must be created. The caller ensures it outlives the constructed instance. @param InStreamChangeTracker Builds object part of the stream request. The caller ensures it outlives the constructed instance. @param InAuthorityChangeTracker Builds the authority changing request. The caller ensures it outlives the constructed instance. @param InFrequencyChangeTracker Builds the object replication frequency part of the request. The caller ensures it outlives the constructed instance.
- L45 _public prototype_ `TOptional<FConcertReplication_ChangeStream_Request> BuildStreamChange() const;` — @return Valid request that can be sent to the server, if there are any local changes.
- L48 _public prototype_ `TOptional<FConcertReplication_ChangeAuthority_Request> BuildAuthorityChange() const;` — @return Valid request that can be sent to the server, if there are any local changes.
- L53 _private member_ `const FGuid LocalClientId;` — Id of the local client in the session.
- L56 _private member_ `const FGlobalAuthorityCache& AuthorityCache;` — Used to filter out changes that would cause a conflict when submitted.
- L59 _private member_ `IClientStreamSynchronizer& StreamSynchronizer;` — Used to determine whether a new stream needs to be created when submitting (happens if nothing was previously registered).
- L62 _private member_ `FStreamChangeTracker& StreamChangeTracker;` — Used to get changes made to the stream
- L64 _private member_ `FAuthorityChangeTracker& AuthorityChangeTracker;` — Informs us when authority is changed by the user.
- L66 _private member_ `FFrequencyChangeTracker& FrequencyChangeTracker;` — Used to build the object replication frequency requests.
- L69 _private prototype_ `FGuid GetLocalClientStreamId() const;` — @return The ID MU uses for its single stream.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/Data/AuthoritySubmission.h` (Private)


#### enum `UE::MultiUserClient::Replication::EAuthoritySubmissionRequestErrorCode`  
`enum class EAuthoritySubmissionRequestErrorCode : uint8`  
_L12-25_
- L15 _public enumerator_ `Success` — The operation completed as expected
- L18 _public enumerator_ `NoChange` — No change was sent to the server because there were no local changes.
- L21 _public enumerator_ `CancelledDueToStreamUpdate` — Cancelled because the required stream update could not be made.
- L24 _public enumerator_ `Cancelled` — The request was cancelled (e.g. because client disconnected while operation was in progress)

#### enum `UE::MultiUserClient::Replication::EAuthoritySubmissionResponseErrorCode`  
`enum class EAuthoritySubmissionResponseErrorCode : uint8`  
_L27-43_
- L30 _public enumerator_ `Success` — The operation completed as expected
- L33 _public enumerator_ `NoChange` — No change was sent to the server because there were no local changes.
- L36 _public enumerator_ `Timeout` — The request timed out
- L39 _public enumerator_ `CancelledDueToStreamUpdate` — Cancelled because the required stream update could not be made.
- L42 _public enumerator_ `Cancelled` — The request was cancelled (e.g. because client disconnected while operation was in progress)

#### struct `UE::MultiUserClient::Replication::FSubmitAuthorityChangesRequest`  
`struct FSubmitAuthorityChangesRequest`  
_L47-53_
- L49 _public member_ `EAuthoritySubmissionRequestErrorCode ErrorCode;`
- L52 _public member_ `TOptional<FConcertReplication_ChangeAuthority_Request> Request;` — Only valid if ErrorCode == EAuthoritySubmissionErrorCode::Success

#### struct `UE::MultiUserClient::Replication::FSubmitAuthorityChangesResponse`  
`struct FSubmitAuthorityChangesResponse`  
_L55-61_
- L57 _public member_ `EAuthoritySubmissionResponseErrorCode ErrorCode = EAuthoritySubmissionResponseErrorCode::Cancelled;`
- L60 _public member_ `TOptional<FConcertReplication_ChangeAuthority_Response> Response;` — Only valid if ErrorCode == EAuthoritySubmissionErrorCode::Success

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L8 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L45 _prototype_ `FText LexToText(EAuthoritySubmissionResponseErrorCode ErrorCode);` (scope `UE::MultiUserClient::Replication`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/Data/EChangeUploadability.h` (Private)


#### enum `UE::MultiUserClient::Replication::EChangeUploadability`  
`enum class EChangeUploadability`  
_L7-17_
- L10 _public enumerator_ `Ready` — Can click the upload button
- L13 _public enumerator_ `InProgress` — A previous upload operation is in progress
- L16 _public enumerator_ `NotAvailable` — Changing is generally not available, e.g. remote client does not allow changes.

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L5 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L19 _function_ `inline bool CanEverSubmit(EChangeUploadability Uploadability)` (scope `UE::MultiUserClient::Replication`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/Data/StreamSubmission.h` (Private)


#### enum `UE::MultiUserClient::Replication::EStreamSubmissionErrorCode`  
`enum class EStreamSubmissionErrorCode : uint8`  
_L12-25_
- L15 _public enumerator_ `Success` — Changes were submitted to and processed by the server
- L18 _public enumerator_ `NoChange` — No change was sent to the server because there were no local changes.
- L21 _public enumerator_ `Timeout` — The request timed out
- L24 _public enumerator_ `Cancelled` — The request was cancelled (e.g. because client disconnected while operation was in progress)

#### struct `UE::MultiUserClient::Replication::FCompletedChangeSubmission`  
`struct FCompletedChangeSubmission`  
_L28-32_
- desc: Contains the original request and response of a completed stream change.
- L30 _public member_ `FConcertReplication_ChangeStream_Request Request;`
- L31 _public member_ `FConcertReplication_ChangeStream_Response Response;`

#### struct `UE::MultiUserClient::Replication::FSubmitStreamChangesResponse`  
`struct FSubmitStreamChangesResponse`  
_L35-42_
- desc: Resulting of submitting stream changes
- L38 _public member_ `EStreamSubmissionErrorCode ErrorCode = EStreamSubmissionErrorCode::Cancelled;` — Error code of the submission. Determines whether Response is valid.
- L41 _public member_ `TOptional<FCompletedChangeSubmission> SubmissionInfo;` — Valid if ErrorCode == ESubmitChangesErrorCode::Success.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L8 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/External/ClientChangeConversionUtils.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L21 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L32 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L32 _namespace_ `namespace ClientChangeConversionUtils` (scope `UE::MultiUserClient::Replication`)
- L35 _prototype_ `TOptional<FConcertReplication_ChangeStream_Request> Transform( FChangeStreamRequest Request, const FGuid& ClientStreamId, const FConcertObjectReplicationMap& ClientStreamContent );` (scope `UE::MultiUserClient::Replication::ClientChangeConversionUtils`) — Transforms FChangeStreamRequest to FConcertReplication_ChangeStream_Request, if the request is correctly formatted.
- L42 _prototype_ `TOptional<FConcertReplication_ChangeAuthority_Request> Transform( FChangeAuthorityRequest Request, const FGuid& ClientStreamId );` (scope `UE::MultiUserClient::Replication::ClientChangeConversionUtils`) — Transforms FChangeAuthorityRequest to FConcertReplication_ChangeStream_Request, if the request is correctly formatted.
- L47 _prototype_ `EChangeStreamOperationResult ExtractErrorCode(const FSubmitStreamChangesResponse& Response);` (scope `UE::MultiUserClient::Replication::ClientChangeConversionUtils`)
- L48 _prototype_ `EChangeAuthorityOperationResult ExtractErrorCode(const FSubmitAuthorityChangesResponse& Response);` (scope `UE::MultiUserClient::Replication::ClientChangeConversionUtils`)
- L50 _prototype_ `FChangeClientStreamResponse Transform(const FSubmitStreamChangesResponse& Response);` (scope `UE::MultiUserClient::Replication::ClientChangeConversionUtils`)
- L51 _prototype_ `FChangeClientAuthorityResponse Transform(const FSubmitAuthorityChangesResponse& Response);` (scope `UE::MultiUserClient::Replication::ClientChangeConversionUtils`)
- L53 _prototype_ `EChangeObjectFrequencyErrorCode Transform(EConcertChangeObjectFrequencyErrorCode ErrorCode);` (scope `UE::MultiUserClient::Replication::ClientChangeConversionUtils`)
- L54 _prototype_ `EChangeObjectFrequencyErrorCode Transform(EConcertChangeStreamFrequencyErrorCode ErrorCode);` (scope `UE::MultiUserClient::Replication::ClientChangeConversionUtils`)
- L55 _prototype_ `EPutObjectErrorCode Transform(EConcertPutObjectErrorCode ErrorCode);` (scope `UE::MultiUserClient::Replication::ClientChangeConversionUtils`)
- L57 _function_ `inline TOptional<FConcertReplication_ChangeStream_Request> Transform( TOptional<FChangeStreamRequest> Request, const FGuid& ClientStreamId, const FConcertObjectReplicationMap& ClientStreamContent )` (scope `UE::MultiUserClient::Replication::ClientChangeConversionUtils`)
- L68 _function_ `inline TOptional<FConcertReplication_ChangeAuthority_Request> Transform( TOptional<FChangeAuthorityRequest> Request, const FGuid& ClientStreamId )` (scope `UE::MultiUserClient::Replication::ClientChangeConversionUtils`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/External/ClientChangeOperation.h` (Private)


#### class `UE::MultiUserClient::Replication::FClientChangeOperation`  
`class FClientChangeOperation : public IClientChangeOperation , public IDeferredSubmitter , public TSharedFromThis<FClientChangeOperation>`  
_L25-121_
- inherits: `IClientChangeOperation,IDeferredSubmitter,TSharedFromThis<FClientChangeOperation>`
- desc: Abstracts an operation invoked externally, i.e. IMultiUserReplication::EnqueueChanges part of our public API. It stores all the operation data that was passed to EnqueueChanges and handles enqueuing itself to the replication client's FSubmissionQueue. FClientChangeOperation is created by FExternalClientChangeRequestHandler, which ensures it is kept alive for at least the lifetime of the client the request is made for. Since this operation is exposed to the public API caller, it can outlive the client it was created for.
- L34 _public typedef_ `using FOnOperationCompleted = TUniqueFunction<void()>;`
- L46 _public prototype_ `static TSharedRef<FClientChangeOperation> StartOperation( const FGuid& InStreamId, FGetStreamContent InGetStreamContentDelegate, FSubmissionQueue& InSubmissionQueue, FOnOperationCompleted InOnOperationCompletedFunc, TAttribute<FChangeClientReplicationRequest> InMakeSubmissionParamsAttribute );` — @param InStreamId The stream ID the client uses. @param InGetStreamContentDelegate Delegate for getting the content of the client's stream @param InSubmissionQueue The client's queue, which is used to enqueue this operation. The caller, which is FExternalClientChangeRequestHandler, keeps the constructed operation alive until either it is executed by the queue or the queue is destroyed. The caller handles dequeuing this operation if the client is destroyed. @param InOnOperationCompletedFunc Callback function which let's FExternalClientChangeRequestHandler know when the operation is done. Executing this function causes FExternalClientChangeRequestHandler to stop reference this operation so it may be destroyed immediately when invoked! @param InMakeSubmissionParamsAttribute Callback to build submission params when task is ready to be executed.
- L56 _public function_ `virtual TFuture<FChangeClientStreamResponse> OnChangeStream() override`
- L57 _public function_ `virtual TFuture<FChangeClientAuthorityResponse> OnChangeAuthority() override`
- L58 _public function_ `virtual TFuture<FChangeClientReplicationResult> OnOperationCompleted() override`
- L62 _public prototype_ `virtual void PerformSubmission_GameThread(ISubmissionWorkflow& Workflow) override;`
- L68 _private member_ `const FGuid StreamId;` — The stream ID the client uses.
- L70 _private member_ `const FGetStreamContent GetStreamContentDelegate;` — Delegate for getting the content of the client's stream
- L77 _private member_ `const FOnOperationCompleted OnOperationCompletedFunc;` — Invokes when this operation completes. Causes this instance to no longer be referenced by FExternalClientChangeRequestHandler, which means calling this may invoke the destructor. @important Invoking this function may cause this instance to be destroyed immediately.
- L79 _private member_ `const TAttribute<FChangeClientReplicationRequest> MakeSubmissionParamsAttribute;` — Callback to build submission params when task is ready to be executed.
- L81 _private member_ `TPromise<FChangeClientStreamResponse> ChangeStreamPromise;`
- L82 _private member_ `TPromise<FChangeClientAuthorityResponse> ChangeAuthorityPromise;`
- L83 _private member_ `TPromise<FChangeClientReplicationResult> OperationCompletedPromise;`
- L86 _private member_ `TOptional<FChangeClientStreamResponse> StreamResult;` — Set when ChangeStreamPromise is fulfilled.
- L88 _private member_ `TOptional<FChangeClientAuthorityResponse> AuthorityResult;` — Set when ChangeAuthorityPromise is fulfilled.
- L90 _private prototype_ `FClientChangeOperation( const FGuid& InStreamId, FGetStreamContent InGetStreamContentDelegate, FOnOperationCompleted InOnOperationCompletedFunc, TAttribute<FChangeClientReplicationRequest> InMakeSubmissionParamsAttribute );`
- L97 _private function_ `void EmplaceStreamResult(FChangeClientStreamResponse Result)`
- L105 _private function_ `void EmplaceAuthorityResult(FChangeClientAuthorityResponse Result)`
- L113 _private function_ `void CompleteOperation()`
- L120 _private prototype_ `void SetUpOperation(const TSharedPtr<ISubmissionOperation>& SubmissionOperation);` — Handles an operation received from ISubmissionWorkflow.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L13 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/External/ExternalClientChangeDelegates.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L9 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L11 _delegate_ `DECLARE_DELEGATE_RetVal(const FConcertObjectReplicationMap*, FGetStreamContent);`
- L11 _prototype_ `DECLARE_DELEGATE_RetVal(const FConcertObjectReplicationMap*, FGetStreamContent);` (scope `UE::MultiUserClient::Replication`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/External/ExternalClientChangeRequestHandler.h` (Private)


#### class `UE::MultiUserClient::Replication::FExternalClientChangeRequestHandler`  
`class FExternalClientChangeRequestHandler : public FNoncopyable`  
_L34-96_
- inherits: `FNoncopyable`
- desc: Handles change requests made by external modules via IMultiUserReplication::EnqueueChanges. This is instantiated per client. As such, each instance manages change requests made for a specific client. This class implements the Adapter Pattern: it transforms the public IMultiUserReplication::EnqueueChanges API to our internal API using ISubmissionOperation & ISubmissionWorkflow. This way, the public and private APIs can change independently.
- L39 _public prototype_ `static TSharedRef<IClientChangeOperation> MakeFailedOperation(EChangeStreamOperationResult StreamResult, EChangeAuthorityOperationResult AuthorityResult);` — @return An operation to return when not in any session.
- L46 _public prototype_ `FExternalClientChangeRequestHandler( const FGuid& InStreamId, FGetStreamContent InGetStreamContentDelegate, FSubmissionQueue& InSubmissionQueue );` — @param InStreamId The stream ID the client uses. @param InGetStreamContentDelegate Delegate for getting the content of the client's stream @param InSubmissionQueue Used to enqueue the external requests. The owning FMultiUserReplicationManager ensures it outlives the constructed instance.
- L51 _public prototype_ `~FExternalClientChangeRequestHandler();`
- L54 _public prototype_ `TSharedRef<IClientChangeOperation> HandleRequest(TAttribute<FChangeClientReplicationRequest> SubmissionParams);` — IMultiUserReplication::EnqueueChanges forwards requests to this function.
- L70 _private member_ `const TSharedRef<FToken> LifetimeToken = FToken::Make();` — Detects whether the FExternalClientChangeRequestHandler has been / is being destroyed when processing an operation's completion. Here's what could happen, and is likely: - ~FReplicationClient invokes ~FExternalClientChangeRequestHandler - ~FReplicationClient invokes ~ISubmissionWorkflow, which cancels an operation originally started by FExternalClientChangeRequestHandler. This problem could be solved in a synchronized way (like unsubscribing our OnOperationCompleted), but here's another case albeit unlikely: - ~FReplicationClient invokes ~FExternalClientChangeRequestHandler - Just before ~ISubmissionWorkflow is invoked, the UDP unfortunately decides to timeout one of our operations. TL;DR: OnOperationCompleted checks whether this is valid before doing anything.
- L73 _private member_ `const FGuid StreamId;` — The stream ID the client uses.
- L75 _private member_ `const FGetStreamContent GetStreamContentDelegate;` — Delegate for getting the content of the client's stream
- L81 _private member_ `FSubmissionQueue& SubmissionQueue;` — Used to enqueue the external requests. The owning FMultiUserReplicationManager ensures it outlives the constructed instance.
- L83 _private typedef_ `using FOperationId = uint32;`
- L85 _private member_ `FOperationId NextOperationId = 0;`
- L92 _private member_ `TMap<FOperationId, TSharedRef<FClientChangeOperation>> PendingOperations;` — Each time IMultiUserReplication::EnqueueChanges invokes HandleRequest, an operation is added here and returned by HandleRequest. The operations invoke OnOperationCompleted when the complete, which removes them from this array. This property can only be read & written from the game thread. Relevant to OnOperationCompleted being executed as part of a timeout.
- L95 _private prototype_ `static void OnOperationCompleted(FOperationId OperationId, TWeakPtr<FToken> WeakToken, FExternalClientChangeRequestHandler* GuardedThis);` — Removes the operation from PendingOperations.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L21 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/ISubmissionOperation.h` (Private)


#### enum `UE::MultiUserClient::Replication::ESubmissionOperationCompletedCode`  
`enum class ESubmissionOperationCompletedCode`  
_L11-17_
- L14 _public enumerator_ `Processed` — The operation was processed normally
- L16 _public enumerator_ `Cancelled` — Cancelled, e.g. because the workflow was destroyed

#### class `UE::MultiUserClient::Replication::ISubmissionOperation`  
`class ISubmissionOperation`  
_L25-65_
- desc: Exposes several events that happen as part of submitting to the server. Every time ISubmissionWorkflow::SubmitChanges is called a new instance is created. The events are exposed as futures, which can complete on any thread.
- L30 _public prototype_ `virtual bool IsModifyingStreams() const = 0;` — @return Whether a request for changing streams has been or will be sent.
- L38 _public prototype_ `virtual TFuture<FSubmitStreamChangesResponse> OnCompleteStreamChangesFuture_AnyThread() = 0;` — Completes when the operation of changing streams has completed. @note This can be called at most once; subsequent calls result in an unset future. @note This can complete on any thread. Usually this finishes on the game thread but timeouts usually occur on the messaging (UDP) thread.
- L46 _public prototype_ `virtual TFuture<FSubmitAuthorityChangesRequest> OnRequestAuthorityChangeFuture_AnyThread() = 0;` — Completes when the authority change request has been sent to the server. @note This can be called at most once; subsequent calls result in an unset future. @note This can complete on any thread. Usually this finishes on the game thread but timeouts usually occur on the messaging (UDP) thread.
- L54 _public prototype_ `virtual TFuture<FSubmitAuthorityChangesResponse> OnCompleteAuthorityChangeFuture_AnyThread() = 0;` — Completes when the operation of changing authority has completed. @note This can be called at most once; subsequent calls result in an unset future. @note This can complete on any thread. Usually this finishes on the game thread but timeouts usually occur on the messaging (UDP) thread.
- L62 _public prototype_ `virtual TFuture<ESubmissionOperationCompletedCode> OnCompletedOperation_AnyThread() = 0;` — Completes when the operation is done. No further work will be performed. @note This can be called at most once; subsequent calls result in an unset future. @note This can complete on any thread. Usually this finishes on the game thread but timeouts usually occur on the messaging (UDP) thread.
- L64 _public prototype_ `virtual ~ISubmissionOperation() = default;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L9 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/ISubmissionWorkflow.h` (Private)


#### struct `UE::MultiUserClient::Replication::FSubmissionParams`  
`struct FSubmissionParams`  
_L23-31_
- desc: At least StreamRequest or AuthorityRequest need to be valid to form a valid request
- L25 _public member_ `TOptional<FConcertReplication_ChangeStream_Request> StreamRequest;`
- L26 _public member_ `TOptional<FConcertReplication_ChangeAuthority_Request> AuthorityRequest;`
- L28 _public function_ `bool IsStreamChangeEmpty() const`
- L29 _public function_ `bool IsAuthorityChangeEmpty() const`
- L30 _public function_ `bool IsEmpty() const`

#### class `UE::MultiUserClient::Replication::ISubmissionWorkflow`  
`class ISubmissionWorkflow`  
_L41-80_
- desc: Manages the flow of changing stream and authority on the server. Handles both submitting and reverting. The general flow is as follows: 1. Submit stream changes 2. Submit authority changes
- L55 _public prototype_ `virtual TSharedPtr<ISubmissionOperation> SubmitChanges(FSubmissionParams Params) = 0;` — Synchronizes the server with the locally made changes to streams and authority. This function creates an operation object which emits special events. If there is already an operation in progress, this function fails. @see CanSubmit @note The operation might start and instantly stop before SubmitChanges finishes (e.g. a network request fails to be created instantly). @return The operation object if the operation was started
- L58 _public prototype_ `virtual EChangeUploadability GetUploadability() const = 0;` — @return Detailed information about whether Submit can be called
- L59 _public function_ `bool CanSubmit() const`
- L61 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStreamRequestCompleted, const FSubmitStreamChangesResponse&);`
- L66 _public prototype_ `virtual FOnStreamRequestCompleted& OnStreamRequestCompleted_AnyThread() = 0;` — Broadcasts whenever a submit operation completes the stream change request stage. Useful for accumulating and counting errors. @note No stream changes may have been requested. Check the error code.
- L68 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAuthorityRequestCompleted, const FSubmitAuthorityChangesRequest&, const FSubmitAuthorityChangesResponse&);`
- L73 _public prototype_ `virtual FOnAuthorityRequestCompleted& OnAuthorityRequestCompleted_AnyThread() = 0;` — Broadcasts whenever a submit operation completes the authority change request stage. Useful for accumulating and counting errors. @note No authority changes may have been requested. Check the error code.
- L75 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSubmitOperationCompleted);`
- L77 _public prototype_ `virtual FOnSubmitOperationCompleted& OnSubmitOperationCompleted_AnyThread() = 0;` — Broadcasts whenever a submit operation completes. Useful for enqueuing submit operations.
- L79 _public prototype_ `virtual ~ISubmissionWorkflow() = default;`

#### class `UE::MultiUserClient::Replication::FSubmissionWorkflowBase`  
`class FSubmissionWorkflowBase : public ISubmissionWorkflow`  
_L83-98_
- inherits: `ISubmissionWorkflow`
- desc: Shared implementation for ISubmissionWorkflow.
- L88 _public function_ `virtual FOnStreamRequestCompleted& OnStreamRequestCompleted_AnyThread() override`
- L89 _public function_ `virtual FOnAuthorityRequestCompleted& OnAuthorityRequestCompleted_AnyThread() override`
- L90 _public function_ `virtual FOnSubmitOperationCompleted& OnSubmitOperationCompleted_AnyThread() override`
- L95 _protected member_ `FOnStreamRequestCompleted StreamRequestCompletedDelegate;`
- L96 _protected member_ `FOnAuthorityRequestCompleted AuthorityRequestCompletedDelegate;`
- L97 _protected member_ `FOnSubmitOperationCompleted OnSubmitOperationCompletedDelegate;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L15 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L61 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStreamRequestCompleted, const FSubmitStreamChangesResponse&);`
- L68 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAuthorityRequestCompleted, const FSubmitAuthorityChangesRequest&, const FSubmitAuthorityChangesResponse&);`
- L75 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSubmitOperationCompleted);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/MultiEdit/ReassignObjectPropertiesLogic.h` (Private)


#### class `UE::MultiUserClient::Replication::FReassignObjectPropertiesLogic`  
`class FReassignObjectPropertiesLogic : public FNoncopyable , IDeferredSubmitter`  
_L31-117_
- inherits: `FNoncopyable,IDeferredSubmitter`
- desc: Knows how to transfer object to properties mappings from clients to other clients. Acts as a model for the UI. Currently transfering is implemented using a cooperative peer-to-peer environment. This makes the operation difficult to sync and impossible to make atomic: that is if one client fails, we cannot rollback the changes already done on other clients. TODO UE-201136: In the future UE-201136 is supposed to address this problem by introducing a dedicated server operation. @see SMultiClientView, MultiStreamColumns::ReassignOwnership
- L42 _public typedef_ `using FProcessClientOwnership = TFunctionRef<EBreakBehavior(const FGuid& ClientId, EOwnershipState Ownership)>;`
- L44 _public prototype_ `FReassignObjectPropertiesLogic(FOnlineClientManager& InClientManager);`
- L48 _public prototype_ `bool OwnsAnyOf(TConstArrayView<FSoftObjectPath> Objects, const FGuid& TargetClientId) const;` — @return Whether ClientId has ownership over at least one
- L50 _public prototype_ `bool IsAnyObjectOwned(TConstArrayView<FSoftObjectPath> Objects) const;` — @return Whether any of the following objects has at least one owner
- L53 _public prototype_ `bool CanReassignAnyTo(TConstArrayView<FSoftObjectPath> ObjectsToReassign, const FGuid& ClientId, FText* Reason = nullptr) const;` — @return Whether content can be assigned to this client (not possible if client does not allow remote changing of streams).
- L55 _public prototype_ `void ReassignAllTo(TArray<FSoftObjectPath> ObjectsToReassign, const FGuid& ClientId);` — Reassigns all properties mapped to the objects from other clients to ClientId.
- L58 _public prototype_ `bool IsReassigning(const FSoftObjectPath& ObjectPath) const;` — @return Whether ObjectPath is currently being reassigned by this logic.
- L60 _public prototype_ `TOptional<FDateTime> GetTimeReassignmentWasStarted() const;` — @return The local time at which reassignment operation was started. Useful for UI showing throbber but only if operation takes long.
- L65 _private member_ `const TSharedRef<FToken> DestructionToken = FToken::Make();` — Detects when "this" is destroyed to avoid dereferencing it in latent actions.
- L68 _private member_ `FOnlineClientManager& ClientManager;` — Used to get info about clients and register to client list changing.
- L99 _private member_ `TOptional<FOperationData> InProgressOperation;` — Set whilst an operation is in progress.
- L102 _private member_ `FSimpleMulticastDelegate OnOwnershipChangedDelegate;` — Broadcast when the result of EnumerateClientOwnershipState may have changed.
- L104 _private prototype_ `void OnRemoteClientsChanged();`
- L107 _private prototype_ `void OnAssignedFromClientsCompleted(FParallelExecutionResult ParallelResult);` — Called once all clients being reassigned have remove their object bindings. The target client will now receive all the previous bindings.
- L109 _private prototype_ `FSubmissionQueue* FindSubmissionQueueForTargetClient() const;` — @return Finds the submission queue for the client being reassigned to.
- L112 _private prototype_ `virtual void PerformSubmission_GameThread(ISubmissionWorkflow& Workflow) override;`
- L116 _private prototype_ `void GuardedExecuteOnGameThread(TUniqueFunction<void()> Callback) const;` — Executes an action straight away if on game thread or schedules for it to be executed. Will ensure that "this" is not destroyed if scheduled latently.

#### enum `UE::MultiUserClient::Replication::FReassignObjectPropertiesLogic::EOwnershipState`  
`enum class EOwnershipState`  
_L37-41_
- L39 _public enumerator_ `HasObjectRegistered`
- L40 _public enumerator_ `NoOwnership`

#### struct `UE::MultiUserClient::Replication::FReassignObjectPropertiesLogic::FOperationData`  
`struct FOperationData`  
_L70-97_
- L72 _public typedef_ `using FClientId = FGuid;`
- L74 _public member_ `const TArray<FSoftObjectPath> ObjectsBeingReassigned;`
- L75 _public member_ `const FGuid AssignedToClient;`
- L77 _public member_ `const TMap<FClientId, FConcertObjectReplicationMap> OldRegisteredObjects;` — The objects we tried to remove from all the other clients. If the removal request worked, the (previously) assigned properties will be transferred to the target client.
- L79 _public member_ `const TMap<FClientId, FConcertStreamFrequencySettings> OldFrequencies;` — The frequency settings that clients had at the beginning of the reassign operation.
- L81 _public member_ `const TMap<FClientId, TArray<FSoftObjectPath>> OldAuthority;` — Clients to the objects they had authority over. Used to later to determine which objects to give the target client authority over (do not transfer authority from failed clients).
- L91 _public member_ `TSharedRef<IParallelSubmissionOperation> RemoveObjectsFromClientsStep;` — The first step of reassignment is to remove all object bindings from all other clients. The operation does RAII for cleaning up latent resources, such as dequeuing submission tasks, and handling underlying Concert messages futures completing at some later time. @note This must be destroyed on the game thread (see ExecuteParallelStreamChanges)
- L93 _public member_ `TOptional<FParallelExecutionResult> ParallelIntermediateResult;` — Result from completing RemoveObjectsFromClientsStep once it is completed. Unset until RemoveObjectsFromClientsStep completes.
- L96 _public member_ `const FDateTime StartTime = FDateTime::Now();` — Only exists for GetTimeReassignmentWasStarted.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L16 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/Notification/AccumulatedSubmissionErrors.h` (Private)


#### struct `UE::MultiUserClient::Replication::FAccumulatedStreamErrors`  
`struct FAccumulatedStreamErrors`  
_L11-27_
- L13 _public member_ `int32 NumTimeouts = 0;`
- L19 _public member_ `TMap<FSoftObjectPath, int32> AuthorityConflicts;` — Changing the these objects would cause authority conflicts. Maps to the number of times it was rejected (across multiple submits).
- L24 _public member_ `TMap<FSoftObjectPath, int32> SemanticErrors;` — This should be empty. If not, that means our client code made a bad request. Maps to the number of times it was rejected (across multiple submits).
- L26 _public member_ `bool bFailedStreamCreation = false;` — Should be false. If not, that means our client code made a bad request.

#### struct `UE::MultiUserClient::Replication::FAccumulatedAuthorityErrors`  
`struct FAccumulatedAuthorityErrors`  
_L29-38_
- L31 _public member_ `int32 NumTimeouts = 0;`
- L37 _public member_ `TMap<FSoftObjectPath, int32> Rejected;` — These objects had conflicts. Maps to the number of times it was rejected (across multiple submits).

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L9 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/Notification/SAuthorityRejectedNotification.h` (Private)


#### class `UE::MultiUserClient::Replication::SAuthorityRejectedNotification`  
`class SAuthorityRejectedNotification : public SBaseRejectionNotification`  
_L12-41_
- inherits: `SBaseRejectionNotification`
- desc: Displays FAccumulatedAuthorityErrors.
- L14 _private typedef_ `using Super = SBaseRejectionNotification;`
- L17 _public function_ `SLATE_BEGIN_ARGS(SAuthorityRejectedNotification)`
- L20 _public prototype_ `SLATE_ATTRIBUTE(const FAccumulatedAuthorityErrors*, Errors) SLATE_EVENT(FOnClicked, OnCloseClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The errors to display
- L28 _public prototype_ `void Refresh();` — Rebuilds the UI from the errors.
- L31 _public function_ `virtual void OnSetCompletionState(SNotificationItem::ECompletionState State) override`
- L32 _public function_ `virtual TSharedRef<SWidget> AsWidget() override`
- L37 _private member_ `TAttribute<const FAccumulatedAuthorityErrors*> ErrorsAttribute;`
- L39 _private prototype_ `void AddTimeoutErrorWidget(TSharedRef<SVerticalBox> Result, const FAccumulatedAuthorityErrors& Errors);`
- L40 _private prototype_ `void AddRejectionErrorWidget(TSharedRef<SVerticalBox> Result, const FAccumulatedAuthorityErrors& Errors);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L7 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/Notification/SBaseRejectionNotification.h` (Private)


#### class `UE::MultiUserClient::Replication::SBaseRejectionNotification`  
`class SBaseRejectionNotification : public SCompoundWidget, public INotificationWidget`  
_L15-47_
- inherits: `SCompoundWidget,INotificationWidget`
- desc: Shared base class for rejection notifications. Builds the general UI structure.
- L19 _public function_ `SLATE_BEGIN_ARGS(SBaseRejectionNotification)`
- L22 _public prototype_ `SLATE_ARGUMENT(FText, Message) SLATE_EVENT(FOnClicked, OnCloseClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The main message displayed at the top
- L30 _public prototype_ `virtual void Refresh() = 0;` — Rebuilds the UI from the errors.
- L33 _public function_ `virtual void OnSetCompletionState(SNotificationItem::ECompletionState State) override`
- L34 _public function_ `virtual TSharedRef<SWidget> AsWidget() override`
- L39 _protected prototype_ `void SetErrorContent(const TSharedRef<SWidget>& Widget);`
- L44 _private member_ `TSharedPtr<SBox> ErrorContent;` — Subclasses place their content in this
- L46 _private prototype_ `TSharedRef<SWidget> BuildErrorContent(const FArguments& InArgs);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/Notification/SStreamRejectedNotification.h` (Private)


#### class `UE::MultiUserClient::Replication::SStreamRejectedNotification`  
`class SStreamRejectedNotification : public SBaseRejectionNotification`  
_L12-43_
- inherits: `SBaseRejectionNotification`
- desc: Displays FAccumulatedStreamErrors.
- L14 _private typedef_ `using Super = SBaseRejectionNotification;`
- L17 _public function_ `SLATE_BEGIN_ARGS(SStreamRejectedNotification)`
- L20 _public prototype_ `SLATE_ATTRIBUTE(const FAccumulatedStreamErrors*, Errors) SLATE_EVENT(FOnClicked, OnCloseClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The errors to display
- L28 _public prototype_ `void Refresh();` — Rebuilds the UI from the errors.
- L31 _public function_ `virtual void OnSetCompletionState(SNotificationItem::ECompletionState State) override`
- L32 _public function_ `virtual TSharedRef<SWidget> AsWidget() override`
- L37 _private member_ `TAttribute<const FAccumulatedStreamErrors*> ErrorsAttribute;`
- L39 _private prototype_ `void AddTimeoutErrorWidget(TSharedRef<SVerticalBox> Result, const FAccumulatedStreamErrors& Errors);`
- L40 _private prototype_ `void AddAuthorityConflictErrorWidget(TSharedRef<SVerticalBox> Result, const FAccumulatedStreamErrors& Errors);`
- L41 _private prototype_ `void AddSemanticErrorWidget(TSharedRef<SVerticalBox> Result, const FAccumulatedStreamErrors& Errors);`
- L42 _private prototype_ `void AddStreamCreationErrorWidget(TSharedRef<SVerticalBox> Result, const FAccumulatedStreamErrors& Errors);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L7 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/Notification/SubmissionNotifier.h` (Private)


#### class `UE::MultiUserClient::Replication::FSubmissionNotifier`  
`class FSubmissionNotifier : public FNoncopyable, public FTickableEditorObject`  
_L31-95_
- inherits: `FNoncopyable,FTickableEditorObject`
- desc: Adds a SNotificationItem when ISubmissionWorkflow operations fail. Failing operations are bundled into a single notification item until it is manually dismissed.
- L35 _public prototype_ `FSubmissionNotifier(FOnlineClientManager& InReplicationClientManager);`
- L36 _public prototype_ `~FSubmissionNotifier();`
- L39 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L40 _public prototype_ `virtual TStatId GetStatId() const override;`
- L46 _private member_ `FOnlineClientManager& ReplicationClientManager;` — Emits events when remote clients are discovered.
- L49 _private member_ `TSharedPtr<SNotificationItem> StreamNotificationItem;` — Only valid if changing streams has failed and the user has not yet dismissed the notification.
- L51 _private member_ `TSharedPtr<SNotificationItem> AuthorityNotificationItem;` — Only valid if changing authority has failed and the user has not yet dismissed the notification.
- L54 _private member_ `TSharedPtr<SStreamRejectedNotification> StreamRejectedNotification;` — Wrapped by StreamNotification
- L56 _private member_ `TSharedPtr<SAuthorityRejectedNotification> AuthorityRejectedNotification;` — Wrapped by AuthorityNotification
- L59 _private member_ `FAccumulatedStreamErrors StreamErrors;` — Displayed by StreamRejectedNotification
- L61 _private member_ `FAccumulatedAuthorityErrors AuthorityErrors;` — Displayed by AuthorityRejectedNotification
- L64 _private member_ `TQueue<FSubmitStreamChangesResponse, EQueueMode::Mpsc> StreamRequestQueue;` — Queues stream completed requests since they may be completed from any thread (usually on game thread except if it times out).
- L66 _private member_ `TQueue<TPair<FSubmitAuthorityChangesRequest, FSubmitAuthorityChangesResponse>, EQueueMode::Mpsc> AuthorityRequestQueue;` — Queues authority completed requests since they may be completed from any thread (usually on game thread except if it times out).
- L70 _private prototype_ `void OnPostRemoteClientAdded(FRemoteClient& RemoteReplicationClient);` — Client events
- L71 _private prototype_ `void RegisterClient(FOnlineClient& Client);`
- L72 _private prototype_ `void UnregisterClient(FOnlineClient& Client);`
- L75 _private prototype_ `void OnStreamRequestCompleted_AnyThread(const FSubmitStreamChangesResponse& Response);` — Per-client submission events
- L76 _private prototype_ `void OnAuthorityRequestCompleted_AnyThread(const FSubmitAuthorityChangesRequest& Request, const FSubmitAuthorityChangesResponse& Response);`
- L79 _private prototype_ `void ProcessCompletedStreamChanges();` — Process asynchronously received completions
- L80 _private prototype_ `void ProcessCompletedAuthorityChanges();`
- L83 _private prototype_ `void AccumulateStreamRejections(const FSubmitStreamChangesResponse& CompletedOp);` — Handle rejections
- L84 _private prototype_ `void AccumulateAuthorityRejections(const FSubmitAuthorityChangesRequest& RequestOp, const FSubmitAuthorityChangesResponse& ResponseOp);`
- L85 _private function_ `bool HasStreamRejections() const`
- L86 _private function_ `bool HasAuthorityRejections() const`
- L89 _private prototype_ `void CreateOrUpdateStreamNotification();` — Updating the notifications
- L90 _private prototype_ `void CreateOrUpdateAuthorityNotification();`
- L93 _private prototype_ `FReply CloseStreamNotification();` — Button events
- L94 _private prototype_ `FReply CloseAuthorityNotification();`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/Queue/DeferredSubmitter.h` (Private)


#### class `UE::MultiUserClient::Replication::IDeferredSubmitter`  
`class IDeferredSubmitter`  
_L16-29_
- desc: Implemented by systems that want to generate a submission once the ISubmissionWorkflow is ready. This is an interface instead of a simple callback so the FSubmissionQueue can use the address of this object to avoid double enqueuing.
- L26 _public prototype_ `virtual void PerformSubmission_GameThread(ISubmissionWorkflow& Workflow) = 0;` — Called when the ISubmissionWorkflow is ready. You are expected to call SubmitChanges but the queue handles the case if you don't (by dequeuing) but you should prefer to dequeue once you know no more changes are needed.
- L28 _public prototype_ `virtual ~IDeferredSubmitter() = default;`

#### class `UE::MultiUserClient::Replication::FSelfUnregisteringDeferredSubmitter`  
`class FSelfUnregisteringDeferredSubmitter : public IDeferredSubmitter`  
_L32-46_
- inherits: `IDeferredSubmitter`
- desc: Util for systems to auto-unregister when they are destroyed.
- L35 _protected member_ `FSubmissionQueue& SubmissionQueue;`
- L38 _public function_ `FSelfUnregisteringDeferredSubmitter(FSubmissionQueue& InSubmissionQueue) : SubmissionQueue(InSubmissionQueue)`
- L42 _public function_ `virtual ~FSelfUnregisteringDeferredSubmitter()`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L8 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/Queue/SubmissionQueue.h` (Private)


#### class `UE::MultiUserClient::Replication::FSubmissionQueue`  
`class FSubmissionQueue : public FNoncopyable, public FTickableEditorObject`  
_L25-70_
- inherits: `FNoncopyable,FTickableEditorObject`
- desc: The submission queue is used to enforce a deterministic queue for calling ISubmissionWorkflow::SubmitChanges. ISubmissionWorkflow only allows at most one pending change in progress at a time. Hence, if one is in progress you must wait. This queue implements shared waiting logic. Since submissions are not real-time sensitive and to simplify concurrency design, the queue will always call IDeferredSubmission::PerformSubmission_GameThread on the game thread. This is not a big restriction either: usually requests complete on the game thread. Only timeouts take place on the UDP thread, in which case we synchronize.
- L32 _public prototype_ `FSubmissionQueue(ISubmissionWorkflow& InWorkflow);` — @param InWorkflow Used to dispatch requests. The caller ensures it outlives the constructed instance.
- L33 _public prototype_ `virtual ~FSubmissionQueue();`
- L44 _public prototype_ `void SubmitNowOrEnqueue_GameThread(IDeferredSubmitter& DeferredSubmission);` — Enqueues a submission. For convenience, enqueueing the same object multiple times is ignored. Suppose you call Enqueue(A), Enqueue(B), Enqueue(A), then the queue will look like this A > B. @note You are responsible for calling Dequeue_GameThread when your IDeferredSubmission is destroyed. @see FSelfUnregisteringDeferredSubmission
- L47 _public prototype_ `void Dequeue_GameThread(IDeferredSubmitter& DeferredSubmission);` — Dequeues a latent submission. It does not need to executed anymore.
- L50 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L51 _public prototype_ `virtual TStatId GetStatId() const override;`
- L57 _private member_ `TDoubleLinkedList<IDeferredSubmitter*> Queue;` — Implements the queue. The head is the next to execute. Used instead of TQueue because TQueue does not support removing.
- L63 _private member_ `ISubmissionWorkflow& Workflow;` — The workflow that is being enqueued for. Outlives this object.
- L66 _private member_ `bool bTaskFinishedOutsideGameThread = false;` — Set to true when a task finishes outside of the game thread. Written exactly once by other threads other than game thread. Read by game thread.
- L68 _private prototype_ `void OnSubmissionCompleted();`
- L69 _private prototype_ `void ProcessNextInQueue();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L9 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/Remote/RemoteSubmissionListener.h` (Private)


#### class `UE::MultiUserClient::Replication::FRemoteSubmissionListener`  
`class FRemoteSubmissionListener : public FNoncopyable , FSelfUnregisteringDeferredSubmitter`  
_L37-94_
- inherits: `FNoncopyable,FSelfUnregisteringDeferredSubmitter`
- desc: Handles stream and authority requests made by other clients towards the local client. For security reasons, the server only allows clients to change their own streams. Hence if client 1 wants to change something about client 2, client 1 must kindly ask client 2 to do the change. In this case client 1's FSubmissionWorkflow_RemoteClient does the asking and client 2's FRemoteSubmissionListener the answering. The typical source of such requests is FSubmissionWorkflow_RemoteClient though theoretically the request can from any system with access to a Concert endpoint. @see FSubmissionWorkflow_RemoteClient
- L43 _public prototype_ `FRemoteSubmissionListener(TSharedRef<IConcertClientSession> InConcertSession, IClientStreamSynchronizer& InStreamSynchronizer, FSubmissionQueue& InSubmissionQueue);`
- L44 _public prototype_ `~FRemoteSubmissionListener();`
- L49 _private member_ `const TSharedRef<FToken> LifetimeToken = FToken::Make();` — Latent operations keep a weak reference to this to detect whether this FSubmissionWorkflow_LocalClient was destroyed.
- L52 _private member_ `TSharedRef<IConcertClientSession> ConcertSession;` — Used to register and unregister event handlers. This object's owner is supposed to destroy us before the session is destroyed.
- L55 _private member_ `IClientStreamSynchronizer& StreamSynchronizer;` — Used to validate a request against the client's server state.
- L57 _private member_ `FSubmissionQueue& SubmissionQueue;` — Used to serve the incoming change requests.
- L68 _private member_ `TOptional<FOperationData> InProgressOperation;` — Data for current in progress operation
- L71 _private prototype_ `EConcertSessionResponseCode HandleChangeRemoteRequest(const FConcertSessionContext& Context, const FMultiUser_ChangeRemote_Request& Request, FMultiUser_ChangeRemote_Response& Response);` — Handles remote change event.
- L74 _private prototype_ `void SubmitNowOrWaitUntilReady(int32 NumTriesSoFar = 0);` — Checks whether the local submit operation is ready. If not, we subscribe to it finishing and try again.
- L77 _private prototype_ `virtual void PerformSubmission_GameThread(ISubmissionWorkflow& Workflow) override;`
- L81 _private prototype_ `void SubmitRequest();` — The submission workflow is ready for submission. Do the submission.
- L83 _private prototype_ `void HandleStreamChangeDone(const FSubmitStreamChangesResponse& Response);`
- L84 _private prototype_ `void HandleAuthorityChangeDone(const FSubmitAuthorityChangesResponse& Response);`
- L85 _private prototype_ `void FinishOperationIfDone();`
- L88 _private prototype_ `bool CanProcessRequest(const FMultiUser_ChangeRemote_Request& Request);` — @return Whether this remote request should be processed. Returns false if there are any authority conflicts.
- L91 _private prototype_ `void CancelOperation(EMultiUserCancelRemoteChangeReason Reason);` — Sends a cancel event to the requester and cleans up the operation.
- L93 _private prototype_ `void CleanUpOperation();` — Resets InProgressOperation and does any other clean-up.

#### struct `UE::MultiUserClient::Replication::FRemoteSubmissionListener::FOperationData`  
`struct FOperationData`  
_L59-66_
- L61 _public member_ `const FMultiUser_ChangeRemote_Request Request;`
- L62 _public member_ `const FGuid RequestingEndpointId;`
- L64 _public member_ `bool bFinishedStream = false;`
- L65 _public member_ `bool bFinishedAuthority = false;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L19 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/Remote/RemoteSubmissionMessages.h` (Private)


#### struct `FMultiUser_ChangeRemote_Request`  
`struct FMultiUser_ChangeRemote_Request`  
_L15-26_
- reflection: `USTRUCT()`
- desc: A kind request from one client to another client to change their server registered state. The receiver can reject the request.
- L21 _public member_ `FConcertReplication_ChangeStream_Request StreamChangeRequest;` — `UPROPERTY()` — Stream changes to apply. Applied before authority changes.
- L25 _public member_ `FConcertReplication_ChangeAuthority_Request AuthorityRequest;` — `UPROPERTY()` — Authority changes to apply. Applied after stream changes.

#### enum `EMultiUserChangeRemoteRequestError`  
`enum class EMultiUserChangeRemoteRequestError : uint8`  
_L29-41_
- reflection: `UENUM()`
- L32 _public enumerator_ `Accepted` — The requests will be executed.
- L35 _public enumerator_ `RejectedChange` — The client rejected the change.
- L38 _public enumerator_ `PredictedConflict` — The request was invalid when it was received because the client determined that the change would generate a conflict given the client's known server state.
- L40 _public enumerator_ `OtherInProgress` — The change was rejected because the client was progressing a request from another client.

#### struct `FMultiUser_ChangeRemote_Response`  
`struct FMultiUser_ChangeRemote_Response`  
_L45-56_
- reflection: `USTRUCT()`
- desc: Indicates whether the request was enqueued.
- L51 _public member_ `bool bTimeout = true;` — `UPROPERTY()` — Default result for default constructed response. Concert default constructs timed out responses.
- L55 _public member_ `EMultiUserChangeRemoteRequestError Error = EMultiUserChangeRemoteRequestError::Accepted;` — `UPROPERTY()` — Indicates whether the request was enqueued

#### struct `FMultiUser_ChangeRemote_StreamUpdatedEvent`  
`struct FMultiUser_ChangeRemote_StreamUpdatedEvent`  
_L60-71_
- reflection: `USTRUCT()`
- desc: Sent by serving client to the requesting client to confirm completion of the stream part of the request.
- L66 _public member_ `bool bProcessedSuccessfully = true;` — `UPROPERTY()` — Whether the change was submitted to the server. False indicates that there was some kind of submission failure. True does NOT imply that StreamChangeResponse did not fail.
- L70 _public member_ `FConcertReplication_ChangeStream_Response StreamChangeResponse;` — `UPROPERTY()` — Set if bProcessedSuccessfully == true.

#### struct `FMultiUser_ChangeRemote_AuthorityUpdatedEvent`  
`struct FMultiUser_ChangeRemote_AuthorityUpdatedEvent`  
_L75-86_
- reflection: `USTRUCT()`
- desc: Sent by serving client to the requesting client to confirm completion of the authority part of the request.
- L81 _public member_ `bool bProcessedSuccessfully = true;` — `UPROPERTY()` — Whether the change was submitted to the server. False indicates that there was some kind of submission failure. True does NOT imply that AuthorityChangeResponse did not fail.
- L85 _public member_ `FConcertReplication_ChangeAuthority_Response AuthorityChangeResponse;` — `UPROPERTY()` — Set if bProcessedSuccessfully == true.

#### enum `EMultiUserCancelRemoteChangeReason`  
`enum class EMultiUserCancelRemoteChangeReason : uint8`  
_L89-102_
- reflection: `UENUM()`
- L95 _public enumerator_ `FailedToCreate` — Internal error: SubmitChanges failed. No changes were made.
- L101 _public enumerator_ `PredictedConflict` — The serving client had to wait with executing the event and after so doing determined that the request would a conflict. No changes were made.

#### struct `FMultiUser_ChangeRemote_Cancelled`  
`struct FMultiUser_ChangeRemote_Cancelled`  
_L106-112_
- reflection: `USTRUCT()`
- desc: Send by serving client to the requesting client to cancel the request after it was confirmed.
- L111 _public member_ `EMultiUserCancelRemoteChangeReason Reason = EMultiUserCancelRemoteChangeReason::FailedToCreate;` — `UPROPERTY()`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/Remote/SubmissionWorkflow_RemoteClient.h` (Private)


#### class `UE::MultiUserClient::Replication::FSubmissionWorkflow_RemoteClient`  
`class FSubmissionWorkflow_RemoteClient : public FSubmissionWorkflowBase , public FNoncopyable`  
_L26-85_
- inherits: `FSubmissionWorkflowBase,FNoncopyable`
- desc: Sends change requests to a remote client, whose FRemoteSubmissionListener will handle the requests. @see FRemoteSubmissionListener
- L32 _public prototype_ `FSubmissionWorkflow_RemoteClient(TSharedRef<IConcertClientSession> InConcertSession, const FGuid& InRemoteClientEndpointId);`
- L36 _public prototype_ `virtual TSharedPtr<ISubmissionOperation> SubmitChanges(FSubmissionParams Params) override;`
- L37 _public prototype_ `virtual EChangeUploadability GetUploadability() const override;`
- L43 _private member_ `const TSharedRef<FToken> LifetimeToken = FToken::Make();` — Latent operations keep a weak reference to this to detect whether this FSubmissionWorkflow_LocalClient was destroyed.
- L46 _private member_ `const FGuid RemoteClientEndpointId;` — Id of the remote client that requests are sent to.
- L49 _private member_ `const TSharedRef<IConcertClientSession> ConcertSession;` — Used to sending messages
- L59 _private member_ `TOptional<FOperationData> InProgressOperation;` — Set for as long as there is a SubmitChanges operation in progress.
- L62 _private prototype_ `void ProcessSubmissionResponse(const FMultiUser_ChangeRemote_Response& Response);` — Handles a response from a remote client.
- L65 _private prototype_ `void TimeoutAndClean();` — Handles timeout of submission response.
- L66 _private prototype_ `void TimeoutStreamChangeIfUnset();`
- L67 _private prototype_ `void TimeoutAuthorityChangeIfUnset();`
- L70 _private prototype_ `void HandleFailureResponse(EMultiUserChangeRemoteRequestError ErrorFlags);` — Handles a response from the client that indicates failure.
- L72 _private prototype_ `void CleanUpSubmissionProcess();` — Cleans up side effects from last submission process
- L74 _private function_ `FSingleClientSubmissionOperation& GetOperation()`
- L77 _private prototype_ `void EarlyCompletePromisesForUnchangedData(const FSubmissionParams& Params, const TSharedRef<FSingleClientSubmissionOperation>& OperationResult) const;` — Checks which data is not being changed by Params and completes the corresponding promises on OperationResult.
- L80 _private prototype_ `void OnStreamRemoteChangeEvent(const FConcertSessionContext& Context, const FMultiUser_ChangeRemote_StreamUpdatedEvent& EventData);` — Called by remote client to update us about progress.
- L81 _private prototype_ `void OnAuthorityRemoteChangeEvent(const FConcertSessionContext& Context, const FMultiUser_ChangeRemote_AuthorityUpdatedEvent& EventData);`
- L82 _private prototype_ `void FinishSubmissionIfDone();`
- L84 _private prototype_ `FString GetRemoteClientName() const;`

#### struct `UE::MultiUserClient::Replication::FSubmissionWorkflow_RemoteClient::FOperationData`  
`struct FOperationData`  
_L51-57_
- L54 _public member_ `const FSubmissionParams Parameters;` — Parameters the operation was started with.
- L56 _public member_ `const TSharedRef<FSingleClientSubmissionOperation> ExposedOperation;` — Automatically cancels pending promises when destroyed.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L18 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/SingleClientSubmissionOperation.h` (Private)


#### class `UE::MultiUserClient::Replication::FSingleClientSubmissionOperation`  
`class FSingleClientSubmissionOperation : public ISubmissionOperation , public FNoncopyable`  
_L13-113_
- inherits: `ISubmissionOperation,FNoncopyable`
- desc: Keeps a promise for each relevant event. Handles cancelling them when destroyed.
- L19 _public function_ `FSingleClientSubmissionOperation(bool bInModifiesStreams) : bModifiesStreams(bInModifiesStreams)`
- L23 _public function_ `virtual ~FSingleClientSubmissionOperation() override`
- L43 _public function_ `void EmplaceStreamPromise(FSubmitStreamChangesResponse Result)`
- L50 _public function_ `void EmplaceAuthorityRequestPromise(FSubmitAuthorityChangesRequest Result)`
- L57 _public function_ `void EmplaceAuthorityResponsePromise(FSubmitAuthorityChangesResponse Result)`
- L64 _public function_ `void EmplaceCompleteOperationPromise(ESubmissionOperationCompletedCode Result)`
- L86 _public function_ `bool HasSetStreamPromise() const`
- L87 _public function_ `bool HasSetAuthorityRequestPromise() const`
- L88 _public function_ `bool HasSetAuthorityResponsePromise() const`
- L89 _public function_ `bool HasSetCompleteOperationPromise() const`
- L92 _public function_ `virtual bool IsModifyingStreams() const override`
- L93 _public function_ `virtual TFuture<FSubmitStreamChangesResponse> OnCompleteStreamChangesFuture_AnyThread() override`
- L94 _public function_ `virtual TFuture<FSubmitAuthorityChangesRequest> OnRequestAuthorityChangeFuture_AnyThread() override`
- L95 _public function_ `virtual TFuture<FSubmitAuthorityChangesResponse> OnCompleteAuthorityChangeFuture_AnyThread() override`
- L96 _public function_ `virtual TFuture<ESubmissionOperationCompletedCode> OnCompletedOperation_AnyThread() override`
- L101 _private member_ `const bool bModifiesStreams;`
- L103 _private member_ `bool bStreamPromiseWasSet = false;`
- L104 _private member_ `bool bAuthorityRequestPromiseWasSet = false;`
- L105 _private member_ `bool bAuthorityResponsePromiseWasSet = false;`
- L106 _private member_ `bool bCompleteOperationPromiseWasSet = false;`
- L109 _private member_ `TPromise<FSubmitStreamChangesResponse> StreamChangesPromise;` — All fulfilled by the owning FSingleClientSubmissionWorkflow
- L110 _private member_ `TPromise<FSubmitAuthorityChangesRequest> AuthorityChangeRequestPromise;`
- L111 _private member_ `TPromise<FSubmitAuthorityChangesResponse> AuthorityChangeResponsePromise;`
- L112 _private member_ `TPromise<ESubmissionOperationCompletedCode> CompleteOperationPromise;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L10 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Replication/Submission/SubmissionWorkflow_LocalClient.h` (Private)


#### class `UE::MultiUserClient::Replication::FSubmissionWorkflow_LocalClient`  
`class FSubmissionWorkflow_LocalClient : public FSubmissionWorkflowBase, public FNoncopyable`  
_L24-63_
- inherits: `FSubmissionWorkflowBase,FNoncopyable`
- desc: Handles the submission workflow for a single client.
- L28 _public prototype_ `FSubmissionWorkflow_LocalClient(TSharedRef<IConcertSyncClient> InClient);`
- L31 _public prototype_ `virtual TSharedPtr<ISubmissionOperation> SubmitChanges(FSubmissionParams Params) override;`
- L32 _public prototype_ `virtual EChangeUploadability GetUploadability() const override;`
- L38 _private member_ `const TSharedRef<FToken> LifetimeToken = FToken::Make();` — Latent operations keep a weak reference to this to detect whether this FSubmissionWorkflow_LocalClient was destroyed.
- L41 _private member_ `const TSharedRef<IConcertSyncClient> Client;` — Used to send authority requests to the server.
- L51 _private member_ `TOptional<FOperationData> InProgressOperation;` — Set for as long as there is a SubmitChanges operation in progress. Automatically cancels pending promises when destroyed.
- L54 _private prototype_ `void OnStreamChangeCompleted( const FConcertReplication_ChangeStream_Request& StreamChangeRequest, const FConcertReplication_ChangeStream_Response& ChangeStreamResponse, TOptional<FConcertReplication_ChangeAuthority_Request> AuthorityChangeRequest );` — Advances the request by requesting authority.
- L59 _private prototype_ `void HandlePendingAuthorityChangeRequest(TOptional<FConcertReplication_ChangeAuthority_Request> AuthorityChangeRequest);`
- L61 _private prototype_ `void SkipAuthorityStage(EAuthoritySubmissionRequestErrorCode RequestCode, EAuthoritySubmissionResponseErrorCode ResponseCode);`
- L62 _private prototype_ `void CleanUpSubmissionOperation();`

#### struct `UE::MultiUserClient::Replication::FSubmissionWorkflow_LocalClient::FOperationData`  
`struct FOperationData`  
_L43-46_
- L45 _public member_ `TSharedRef<FSingleClientSubmissionOperation> Operation;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L15 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Sandbox/MultiUserSandboxEntryPoint.h` (Private)


#### class `UE::MultiUserClient::FMultiUserSandboxEntryPoint`  
`class FMultiUserSandboxEntryPoint : public FileSandboxUI::ISandboxEntryPoint`  
_L13-35_
- inherits: `FileSandboxUI::ISandboxEntryPoint`
- desc: Represents Multi User as entry point so it becomes discoverable by other editor systems.
- L17 _public prototype_ `explicit FMultiUserSandboxEntryPoint(const TSharedRef<IConcertSyncClient>& InMultiUserClient);`
- L20 _public prototype_ `virtual void SummonProviderUI() override;`
- L21 _public prototype_ `virtual FText GetEntryPointLabel() const override;`
- L22 _public prototype_ `virtual bool OwnsSandbox(const FileSandboxCore::ISandboxInstance& InSandbox) const override;`
- L26 _public function_ `FSimpleMulticastDelegate& OnSummonProviderUI()` — Event invoked when the UI is supposed to be summoned.
- L31 _private member_ `const TSharedRef<IConcertSyncClient> MultiUserClient;` — Multi User's client instance. Used to get the current session: if client is in a session, we'll report that the sandbox is owned by Multi User.
- L34 _private member_ `FSimpleMulticastDelegate OnSummonProviderUIDelegate;` — Event invoked when the UI is supposed to be summoned.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Sandbox/MultiUserSandboxIntegration.h` (Private)


#### class `UE::MultiUserClient::FMultiUserSandboxIntegration`  
`class FMultiUserSandboxIntegration : public FNoncopyable`  
_L14-31_
- inherits: `FNoncopyable`
- desc: Responsible for registering Multi User with the sandbox system.
- L18 _public prototype_ `FMultiUserSandboxIntegration(const TSharedRef<IConcertSyncClient>& InMultiUserClient);`
- L19 _public prototype_ `~FMultiUserSandboxIntegration();`
- L21 _public function_ `const TSharedRef<FMultiUserSandboxEntryPoint>& GetEntryPoint() const`
- L22 _public function_ `const TSharedRef<FileSandboxUI::IExternalSandboxActiveViewModel>& GetExternalSandboxViewModel() const`
- L27 _private member_ `const TSharedRef<FMultiUserSandboxEntryPoint> EntryPoint;` — Represents Multi User as entry point so it becomes discoverable by other editor systems.
- L30 _private member_ `const TSharedRef<FileSandboxUI::IExternalSandboxActiveViewModel> ExternalSandboxViewModel;` — This view model is used to overlay a widget onto the browser when the engine is already sandboxed.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxUI` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Settings/FrequencyDefaultRules.h` (Private)


#### struct `FMultiUserActorFrequencyStackEntry`  
`struct FMultiUserActorFrequencyStackEntry`  
_L16-50_
- reflection: `USTRUCT()`
- desc: Used to build a stack of rules. The first stack entry that matches an object, is used to determine the object's frequency settings.
- L22 _public member_ `FConcertObjectReplicationSettings ReplicationSettings;` — `UPROPERTY(Category = "Replication Settings|Frequency", EditAnywhere)` — The settings to apply to objects matched via this stack entry.
- L29 _public member_ `TSet<FSoftClassPath> MatchingClasses;` — `UPROPERTY(Category = "Replication Settings|Frequency", EditAnywhere)` — If an object's class is contained in this set, ReplicationSettings are applied to it. @see bAllowRecursiveClassSearch.
- L36 _public member_ `FConcertPerClassSubobjectMatchingRules SubobjectMatchingRules;` — `UPROPERTY(Category = "Replication Settings|Frequency", EditAnywhere)` — These rules are applied only to objects that are not actors, e.g. components. The matching rules are applied to the object's owning actor. If the object is found by these rules, ReplicationSettings are applied to it.
- L46 _public member_ `bool bAllowRecursiveClassSearch = true;` — `UPROPERTY(Category = "Replication Settings|Frequency", EditAnywhere, AdvancedDisplay)` — Determines whether parent classes are included when matching against MatchingClasses. Example: MatchingClasses = UStaticMeshComponent. Object 1 is UStaticMeshComponent > matches. Object 2 is UInstancedStaticMeshComponent > if bAllowRecursiveClassSearch == true, then UInstancedStaticMeshComponent is matched. Otherwise, not.
- L49 _public prototype_ `bool Matches(UObject& Object) const;` — @return Whether Object matches the these rules.

#### struct `FMultiUserFrequencyDefaultRules`  
`struct FMultiUserFrequencyDefaultRules`  
_L56-90_
- reflection: `USTRUCT()`
- desc: Defines rules determining an object's frequency settings.
- L65 _public member_ `FConcertObjectReplicationSettings DefaultObjectFrequencySettings { EConcertObjectReplicationMode::SpecifiedRate, 30 };` — `UPROPERTY(Category = "Replication Settings|Frequency", EditAnywhere)` — Default frequency settings that are used by objects when they do not match any specific rules in FrequencyRuleStack. These are the settings that are set for the Multi User stream's FConcertBaseStreamInfo::FrequencySettings::Defaults member.
- L81 _public member_ `TArray<FMultiUserActorFrequencyStackEntry> FrequencyRuleStack;` — `UPROPERTY(Category = "Replication Settings|Frequency", EditAnywhere)` — Use this to assign specific frequency settings to objects. When an object is added to the replication stream, its frequency settings are looked up as follows: 1. If the object is an actor, 1.1 go through FrequencyRuleStack from top to bottom 1.2 if the entry's MatchingClasses contains the actor's class, use the ReplicationSettings in that entry. 2. If the object is not an actor, 2.1 go through FrequencyRuleStack from top to bottom 2.2 if the entry's MatchingClasses contains the object's class, use the ReplicationSettings in that entry. 2.3 get the object's owning actor 2.4 if the entry's SubobjectMatchingRules finds the object by searching the owning actor, use the ReplicationSettings in that entry.
- L89 _public prototype_ `TOptional<FConcertObjectReplicationSettings> FindOverrideSettings(UObject& Object) const;` — Goes through FrequencyRuleStack and returns the FConcertObjectReplicationSettings of the entry that was matched. If none was matched, the object should not have any frequency override and should default to the stream's FConcertBaseStreamInfo::FrequencySettings::Defaults, which should be set to DefaultObjectFrequencySettings.

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Settings/MultiUserReplicationSettings.h` (Private)


#### class `UMultiUserReplicationSettings`  
`class UMultiUserReplicationSettings : public UObject`  
_L14-37_
- reflection: `UCLASS(config=MultiUserClient)`
- inherits: `UObject`
- L19 _public function_ `static UMultiUserReplicationSettings* Get()`
- L26 _public member_ `FConcertStreamObjectAutoBindingRules ReplicationEditorSettings;` — `UPROPERTY(Config, Category = "Replication Settings", EditAnywhere)` — When you add an object via the stream editor, you may want to automatically bind properties and add additional subobjects. Here you can specify the rules to achieve this.
- L30 _public member_ `FMultiUserFrequencyDefaultRules FrequencyRules;` — `UPROPERTY(Config, Category = "Replication Settings|Frequency", EditAnywhere)` — Determines the frequency settings applied to an object set by default when it is added to the stream.
- L36 _public function_ `TOptional<FConcertObjectReplicationSettings> DetermineObjectFrequencySettings(UObject& Object) const` — Checks Object against these settings and returns override settings to set for this object. @param Object An object that the user just added to the stream

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Overview/SActiveSessionOverviewTab.h` (Private)


#### class `SActiveSessionOverviewTab`  
`class SActiveSessionOverviewTab : public SCompoundWidget`  
_L27-124_
- inherits: `SCompoundWidget`
- desc: Displays the multi-users active session's clients and activities.
- L31 _public function_ `SLATE_BEGIN_ARGS(SActiveSessionOverviewTab)`
- L32 _public prototype_ `SLATE_END_ARGS();`
- L39 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<IConcertSyncClient> InConcertSyncClient);` — Constructs the active session tab. @param InArgs The Slate argument list.
- L41 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L46 _private member_ `TWeakPtr<IConcertSyncClient> WeakConcertSyncClient;` — Pointer on the client sync.
- L49 _private member_ `TWeakPtr<IConcertClientSession> WeakSessionPtr;` — Holds a concert client session.
- L52 _private member_ `TSharedPtr<SListView<TSharedPtr<FConcertSessionClientInfo>>> ClientsListView;` — List view for AvailableClients.
- L55 _private member_ `TArray<TSharedPtr<FConcertSessionClientInfo>> Clients;` — List of clients for the current session.
- L58 _private member_ `TSharedPtr<FConcertSessionClientInfo> ClientInfo;` — Information about the machine's client.
- L61 _private member_ `TSharedPtr<FClientSessionHistoryController> SessionHistoryController;` — Holds a concert activity log.
- L64 _private member_ `TSharedPtr<SExpandableArea> ClientArea;` — The 'Clients' expandable area.
- L67 _private member_ `TSharedPtr<SExpandableArea> HistoryArea;` — The 'History' expandable area.
- L70 _private member_ `TSharedPtr<SCustomDialog> CanReloadDialog;` — Notification handler for hot reload.
- L73 _private member_ `bool bCanHotReload = true;` — Flag to indicate if it is OK to hotreload the packages.
- L76 _private member_ `bool bClientAreaExpanded = true;` — Keeps the status of 'Clients' area expansion.
- L79 _private member_ `bool bHistoryAreaExpanded = true;` — Keep the status of 'History' area expansion.
- L82 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(TSharedPtr<FConcertSessionClientInfo> InClientInfo, const TSharedRef<STableViewBase>& OwnerTable) const;` — Generate a new client row
- L85 _private prototype_ `void HandleSessionStartup(TSharedRef<IConcertClientSession> InClientSession);` — Handle a session startup
- L88 _private prototype_ `void HandleSessionShutdown(TSharedRef<IConcertClientSession> InClientSession);` — Handle a session shutdown
- L91 _private prototype_ `void HandleSessionClientChanged(IConcertClientSession&, EConcertClientStatus ClientStatus, const FConcertSessionClientInfo& ClientInfo);` — Handle a session client change
- L94 _private prototype_ `EActiveTimerReturnType HandleLocalClientInfoChangePollingTimer(double InCurrentTime, float InDeltaTime);` — Polls the local client info and detect if it changed in order to update its representation in real time.
- L97 _private prototype_ `void UpdateSessionClientListView(const FConcertSessionClientInfo* Client = nullptr, EConcertClientStatus Status = EConcertClientStatus::Updated);` — Update the list of clients while keeping the alphabetical sorting
- L100 _private prototype_ `void SetSelectedClient(const FGuid& InClientEndpointId, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Set the selected client in the clients list view
- L103 _private prototype_ `TSharedPtr<FConcertSessionClientInfo> FindAvailableClient(const FGuid& InClientEndpointId) const;` — Find a client with its endpoint id
- L106 _private function_ `SSplitter::ESizeRule GetClientAreaSizeRule() const` — Handles how much space the 'Clients' area uses with respect to its expansion state.
- L107 _private function_ `void OnClientAreaExpansionChanged(bool bExpanded)`
- L110 _private function_ `SSplitter::ESizeRule GetHistoryAreaSizeRule() const` — Handles how much space the 'History' area uses with respect to its expansion state.
- L111 _private function_ `void OnHistoryAreaExpansionChanged(bool bExpanded)`
- L114 _private prototype_ `void OnSendConflict(const FConcertConflictDescriptionBase& ConflictMsg);` — Delegate handler when a conflict between inbound transaction and those stored pending outbound transactions.
- L117 _private prototype_ `void OnPackageChangeActivity();` — Delegate handler on inbound transactions that focus specifically on packages.
- L120 _private prototype_ `bool CanProcessPendingPackages() const;` — Delegate handler to indicate if we can hot reload an inbound package.
- L123 _private prototype_ `void ActivityUpdated(const FConcertClientInfo& InClientInfo, const FConcertSyncActivity& InActivity, const FStructOnScope& );` — Delegate handler invoked when an activity has been received by multi-user.

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Context/ContextMenuUtils.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L17 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L23 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L23 _namespace_ `namespace ContextMenuUtils` (scope `UE::MultiUserClient::Replication`)
- L26 _prototype_ `void AddReassignmentOptions( FMenuBuilder& MenuBuilder, const TSoftObjectPtr<>& ContextObject, const IConcertClient& ConcertClient, const FOnlineClientManager& ReplicationManager, ConcertSharedSlate::IObjectHierarchyModel& ObjectHierarchy, FReassignObjectPropertiesLogic& ReassignmentLogic, ConcertSharedSlate::IMultiReplicationStreamEditor& MultiStreamEditor );` (scope `UE::MultiUserClient::Replication::ContextMenuUtils`) — Adds menu entries for reassigning the object to another client.
- L37 _prototype_ `void AddFrequencyOptionsForMultipleClients(FMenuBuilder& MenuBuilder, const FSoftObjectPath& ContextObjects, FOnlineClientManager& InClientManager);` (scope `UE::MultiUserClient::Replication::ContextMenuUtils`) — Adds an edit box for batch reassigning the select object's frequencies for all replicating clients.
- L39 _function_ `inline void AddFrequencyOptionsIfOneContextObject_MultiClient(FMenuBuilder& MenuBuilder, TConstArrayView<TSoftObjectPtr<>> ContextObjects, FOnlineClientManager& InClientManager)` (scope `UE::MultiUserClient::Replication::ContextMenuUtils`) — Adds an edit box for batch reassigning the select object's frequencies for all replicating clients.

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/FrequencyContextMenuUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L16 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L16 _namespace_ `namespace FrequencyContextMenuUtils` (scope `UE::MultiUserClient::Replication`)
- L19 _prototype_ `void AddFrequencyOptionsForSingleClient(FMenuBuilder& MenuBuilder, const FSoftObjectPath& ContextObjects, const FGuid& ClientId, FOnlineClientManager& InClientManager);` (scope `UE::MultiUserClient::Replication::FrequencyContextMenuUtils`) — Adds an edit box for changing the selected object's frequencies.
- L21 _prototype_ `void AddFrequencyOptionsForMultipleClients(FMenuBuilder& MenuBuilder, const FSoftObjectPath& ContextObjects, FOnlineClientManager& InClientManager);` (scope `UE::MultiUserClient::Replication::FrequencyContextMenuUtils`) — Adds an edit box for batch reassigning the select object's frequencies for all replicating clients.
- L24 _function_ `inline void AddFrequencyOptionsIfOneContextObject_SingleClient(FMenuBuilder& MenuBuilder, TConstArrayView<FSoftObjectPath> ContextObjects, const FGuid& ClientId, FOnlineClientManager& InClientManager)` (scope `UE::MultiUserClient::Replication::FrequencyContextMenuUtils`) — Adds an edit box for changing the selected object's frequencies.
- L32 _function_ `inline void AddFrequencyOptionsIfOneContextObject_MultiClient(FMenuBuilder& MenuBuilder, TConstArrayView<FSoftObjectPath> ContextObjects, FOnlineClientManager& InClientManager)` (scope `UE::MultiUserClient::Replication::FrequencyContextMenuUtils`) — Adds an edit box for batch reassigning the select object's frequencies for all replicating clients.

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/Columns/AssignProperty/AssignPropertyModel.h` (Private)


#### enum `UE::MultiUserClient::Replication::MultiStreamColumns::EPropertyOnObjectsOwnershipState`  
`enum class EPropertyOnObjectsOwnershipState : uint8`  
_L24-32_
- L27 _public enumerator_ `OwnedOnAllObjects` — Clients owns the property on all objects
- L29 _public enumerator_ `NotOwnedOnAllObjects` — does not own the property on any object
- L31 _public enumerator_ `Mixed`

#### class `UE::MultiUserClient::Replication::MultiStreamColumns::FAssignPropertyModel`  
`class FAssignPropertyModel : public FNoncopyable`  
_L35-87_
- inherits: `FNoncopyable`
- desc: Implements the model in the MVC pattern for the property assignment column.
- L40 _public prototype_ `static void AssignPropertyTo( const FUnifiedClientView& ClientView, const FGuid& ClientId, TConstArrayView<TSoftObjectPtr<>> Objects, const FConcertPropertyChain& Property );` — Assigns the property to the given client and unassigns it from all others.
- L47 _public prototype_ `FAssignPropertyModel(FUnifiedClientView& InClientView UE_LIFETIMEBOUND, FMultiViewOptions& InViewOptions UE_LIFETIMEBOUND);`
- L48 _public prototype_ `~FAssignPropertyModel();`
- L51 _public prototype_ `bool CanChangePropertyFor(const FGuid& ClientId, FText* Reason = nullptr) const;` — @return Whether property ownership can be changed for the given client.
- L53 _public prototype_ `bool CanClear(TConstArrayView<TSoftObjectPtr<>> Objects, const FConcertPropertyChain& Property) const;` — @return Whether it is valid to call ClearProperty with this parameters.
- L55 _public prototype_ `EPropertyOnObjectsOwnershipState GetPropertyOwnershipState(const FGuid& ClientId, TConstArrayView<TSoftObjectPtr<>> Objects, const FConcertPropertyChain& Property) const;` — @return How the property is owned by ClientId
- L58 _public prototype_ `void TogglePropertyFor(const FGuid& ClientId, TConstArrayView<TSoftObjectPtr<>> Objects, const FConcertPropertyChain& Property) const;` — Assigns the property to ClientId or unassigns it. Removes the property from all other clients in both cases.
- L60 _public prototype_ `void ClearProperty(TConstArrayView<TSoftObjectPtr<>> Objects, const FConcertPropertyChain& Property) const;` — Removes the property from all clients.
- L63 _public prototype_ `void ForEachAssignedClient( const FConcertPropertyChain& DisplayedProperty, const TArray<TSoftObjectPtr<>>& EditedObjects, TFunctionRef<EBreakBehavior(const FGuid& ClientId)> Callback ) const;` — Iterates every client that has DisplayedProperty assigned for any of EditedObjects.
- L70 _public function_ `FSimpleMulticastDelegate& OnOwnershipChanged()` — Broadcasts when property ownership may have changed.
- L79 _private member_ `FUnifiedClientView& ClientView;` — Used to - get all online clients that can be assigned / reassigned to, - detect changes made to client content for broadcasting OnOwnershipChangedDelegate
- L81 _private member_ `FMultiViewOptions& ViewOptions;` — Controls whether offline clients should be listed by ForEachAssignedClient.
- L84 _private member_ `FSimpleMulticastDelegate OnOwnershipChangedDelegate;` — Broadcasts when property ownership may have changed.
- L86 _private function_ `void BroadcastOnOwnershipChanged() const`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L22 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L22 _namespace_ `namespace MultiStreamColumns` (scope `UE::MultiUserClient::Replication`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/Columns/AssignProperty/SAssignPropertyComboBox.h` (Private)


#### class `UE::MultiUserClient::Replication::MultiStreamColumns::SAssignPropertyComboBox`  
`class SAssignPropertyComboBox : public SCompoundWidget`  
_L29-97_
- inherits: `SCompoundWidget`
- desc: Placed in every property row column to assign properties to clients. Can be used to assign a property to at most one client: multiple clients cannot be assigned because it is an advanced workflow which might confuse basic users.
- L33 _public prototype_ `DECLARE_DELEGATE(FOnPropertyAssignmentChanged);`
- L36 _public prototype_ `static TOptional<FString> GetDisplayString( const FAssignPropertyModel& Model, const FUnifiedClientView& ClientView, const FConcertPropertyChain& DisplayedProperty, const TArray<TSoftObjectPtr<>>& EditedObjects );` — @return The display string this widget would have with the given state. If unset, no clients are displayed in the combobox.
- L43 _public function_ `SLATE_BEGIN_ARGS(SAssignPropertyComboBox)`
- L45 _public prototype_ `SLATE_ARGUMENT(FConcertPropertyChain, DisplayedProperty) SLATE_ARGUMENT(TArray<TSoftObjectPtr<>>, EditedObjects) SLATE_ARGUMENT(TSharedPtr<FText>, HighlightText) SLATE_EVENT(FOnPropertyAssignmentChanged, OnPropertyAssignmentChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FAssignPropertyModel& InModel, FUnifiedClientView& InClientView );`
- L60 _private member_ `FAssignPropertyModel* Model = nullptr;` — The model this view is displaying.
- L62 _private member_ `FUnifiedClientView* ClientView = nullptr;` — Used to obtain display information about clients.
- L65 _private member_ `TArray<TSoftObjectPtr<>> EditedObjects;` — The objects for which the property is being displayed.
- L67 _private member_ `FConcertPropertyChain Property;` — The property assigned to this column.
- L70 _private member_ `TSharedPtr<ConcertSharedSlate::SHorizontalClientList> ClientListWidget;` — The static menu content (when there is no drop-down).
- L72 _private member_ `TSharedPtr<FText> HighlightText;` — Passed to MakeListWidgetDelegate
- L75 _private member_ `FOnPropertyAssignmentChanged OnOptionClickedDelegate;` — Called when the property assignment of any client(s) is changed by this widget.
- L78 _private prototype_ `void RefreshContentBoxContent() const;` — Updates the content of the combo box
- L81 _private prototype_ `TSharedRef<SWidget> GetMenuContent();` — Builds the drop-down menu
- L84 _private prototype_ `void OnClickOption(const FGuid EndpointId) const;` — Called when a client is clicked in the drop-down menu
- L86 _private function_ `bool CanClickOption(const FGuid EndpointId) const` — @return Whether an item in the drop-down menu should be clickable (returns true if the stream is writable)
- L87 _private prototype_ `bool CanClickOptionWithReason(const FGuid& EndpointId, FText* Reason = nullptr) const;`
- L89 _private prototype_ `ECheckBoxState GetOptionCheckState(const FGuid EndpointId) const;` — @return Checkbox state for the item. Handles cases of multiple objects being property edited.
- L92 _private prototype_ `void OnClickClear();` — Called when a client clicks the clear button
- L94 _private prototype_ `bool CanClickClear() const;` — Whether the property is assigned to any client
- L96 _private prototype_ `FText GetComboBoxToolTipText() const;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L17 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L19 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L19 _namespace_ `namespace MultiStreamColumns` (scope `UE::MultiUserClient::Replication`)
- L33 _delegate_ `DECLARE_DELEGATE(FOnPropertyAssignmentChanged);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/Columns/AssignedClients/AssignedClientsModel.h` (Private)


#### class `UE::MultiUserClient::Replication::MultiStreamColumns::FAssignedClientsModel`  
`class FAssignedClientsModel : public FNoncopyable`  
_L26-58_
- inherits: `FNoncopyable`
- desc: Implements the model in the MVC pattern for the assigned clients column.
- L30 _public prototype_ `FAssignedClientsModel( const ConcertSharedSlate::IObjectHierarchyModel& InObjectHierarchy UE_LIFETIMEBOUND, FUnifiedStreamCache& InStreamCache UE_LIFETIMEBOUND, FMultiViewOptions& InViewOptions UE_LIFETIMEBOUND );`
- L35 _public prototype_ `~FAssignedClientsModel();`
- L38 _public prototype_ `TArray<FGuid> GetAssignedClients(const FSoftObjectPath& ObjectPath) const;` — @return The endpoint IDs of clients that have properties assigned to ObjecPath.
- L41 _public function_ `FSimpleMulticastDelegate& OnOwnershipChanged()` — Broadcast when the result of GetAssignedClients may have changed.
- L46 _private member_ `const ConcertSharedSlate::IObjectHierarchyModel& ObjectHierarchy;` — Used to compute clients's recursive ownership of subobjects for a managed object.
- L48 _private member_ `FUnifiedStreamCache& StreamCache;` — Holds the stream content of both online and offline clients.
- L51 _private member_ `FMultiViewOptions& ViewOptions;` — Controls whether offline clients should be considered.
- L54 _private member_ `FSimpleMulticastDelegate OnOwnershipChangedDelegate;` — Broadcast when the result of GetAssignedClients may have changed.
- L56 _private prototype_ `void OnClientChanged(const FGuid&) const;`
- L57 _private prototype_ `void BroadcastOwnershipChanged() const;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L23 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L23 _namespace_ `namespace MultiStreamColumns` (scope `UE::MultiUserClient::Replication`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/Columns/AssignedClients/SAssignedClientsWidget.h` (Private)


#### class `UE::MultiUserClient::Replication::MultiStreamColumns::SAssignedClientsWidget`  
`class SAssignedClientsWidget : public SCompoundWidget`  
_L27-57_
- inherits: `SCompoundWidget`
- desc: Placed into object rows. Display the clients that own it and its children.
- L32 _public function_ `SLATE_BEGIN_ARGS(SAssignedClientsWidget)`
- L33 _public prototype_ `SLATE_ARGUMENT(FSoftObjectPath, ManagedObject) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_END_ARGS() void Construct( const FArguments& InArgs, FAssignedClientsModel& InModel, const FUnifiedClientView& InClientView );`
- L45 _public prototype_ `void RefreshClientList() const;`
- L50 _private member_ `FAssignedClientsModel* Model = nullptr;` — The model this view displays.
- L53 _private member_ `TSharedPtr<ConcertSharedSlate::SHorizontalClientList> ClientList;` — This widget displays the owning clients and is refreshed when the list of owning clients changes.
- L56 _private member_ `FSoftObjectPath ManagedObject;` — The object for which we're displaying the owning clients

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L16 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L22 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L22 _namespace_ `namespace MultiStreamColumns` (scope `UE::MultiUserClient::Replication`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/Columns/MultiStreamColumns.h` (Private)


#### enum `UE::MultiUserClient::Replication::MultiStreamColumns::EColumnSortOrder`  
`enum class EColumnSortOrder`  
_L38-43_
- desc: @see ETopLevelColumnOrder and EReplicationPropertyColumnOrder
- L40 _public enumerator_ `MuteToggle = 0`
- L41 _public enumerator_ `AssignPropertyColumn = 30`
- L42 _public enumerator_ `ReassignOwnership = 40`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L31 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L31 _namespace_ `namespace MultiStreamColumns` (scope `UE::MultiUserClient::Replication`)
- L33 _externvar_ `const extern FName MuteToggleColumnId;` (scope `UE::MultiUserClient::Replication::MultiStreamColumns`)
- L34 _externvar_ `const extern FName AssignedClientsColumnId;` (scope `UE::MultiUserClient::Replication::MultiStreamColumns`)
- L35 _externvar_ `const extern FName AssignPropertyColumnId;` (scope `UE::MultiUserClient::Replication::MultiStreamColumns`)
- L52 _prototype_ `ConcertSharedSlate::FObjectColumnEntry MuteToggleColumn( FMuteChangeTracker& InMuteChangeTracker UE_LIFETIMEBOUND, int32 InColumnsSortPriority = static_cast<int32>(EColumnSortOrder::MuteToggle) );` (scope `UE::MultiUserClient::Replication::MultiStreamColumns`) — Mutes and unmutes the object and its child objects. @param InMuteChangeTracker Tells us the mute state and changes it. @param InColumnsSortPriority The order relative to the other columns @return A checkbox with pause and unpause icons.
- L67 _prototype_ `ConcertSharedSlate::FObjectColumnEntry AssignedClientsColumn( const TSharedRef<IConcertClient>& InConcertClient, TAttribute<TSharedPtr<ConcertSharedSlate::IMultiReplicationStreamEditor>> InMultiStreamModelAttribute, const ConcertSharedSlate::IObjectHierarchyModel& InObjectHierarchy UE_LIFETIMEBOUND, FUnifiedClientView& InClientView UE_LIFETIMEBOUND, FMultiViewOptions& InViewOptions UE_LIFETIMEBOUND, int32 InColumnsSortPriority = static_cast<int32>(EColumnSortOrder::ReassignOwnership) );` (scope `UE::MultiUserClient::Replication::MultiStreamColumns`) — A combo box which displays all current owners for an object and allows bulk reassigning properties. @param InConcertClient Used to look up client names @param InMultiStreamModelAttribute Used for requesting resorting the column @param InObjectHierarchy Used to display clients when a child object is replicated @param InClientView Used to access all clients' stream content for display in the column @param InViewOptions Controls whether offline clients are displayed @param InColumnsSortPriority The order relative to the other columns
- L86 _prototype_ `ConcertSharedSlate::FPropertyColumnEntry AssignPropertyColumn( TAttribute<TSharedPtr<ConcertSharedSlate::IMultiReplicationStreamEditor>> InMultiStreamEditor, FUnifiedClientView& InClientView UE_LIFETIMEBOUND, FMultiViewOptions& InViewOptions UE_LIFETIMEBOUND, const int32 InColumnsSortPriority = static_cast<int32>(EColumnSortOrder::AssignPropertyColumn) );` (scope `UE::MultiUserClient::Replication::MultiStreamColumns`) — Creates a property column which assigns the property to the stream selected in the combo box. @param InMultiStreamEditor Used to determine the selected objects. @param InClientView Used to obtain the clients that can be assigned to and display them @param InViewOptions Controls whether offline clients are displayed @param InColumnsSortPriority The order relative to the other columns @return A column that spawns a combo box for assigning properties

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/Columns/SMuteToggle.h` (Private)


#### class `UE::MultiUserClient::Replication::SMuteToggle`  
`class SMuteToggle : public SCompoundWidget`  
_L19-45_
- inherits: `SCompoundWidget`
- desc: Pauses and resumes replication for an object
- L23 _public function_ `SLATE_BEGIN_ARGS(SMuteToggle)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FSoftObjectPath InObjectPath, FMuteChangeTracker& InMuteChangeTracker);`
- L36 _private member_ `FSoftObjectPath ObjectPath;` — The object that is being muted by this widget.
- L39 _private member_ `FMuteChangeTracker* MuteChangeTracker = nullptr;` — Knows the mute state that should be displayed and is used to change it.
- L41 _private prototype_ `ECheckBoxState IsMuted() const;`
- L42 _private prototype_ `EVisibility GetMuteVisibility() const;`
- L43 _private prototype_ `FText GetToolTipText() const;`
- L44 _private prototype_ `void OnCheckboxStateChanged(ECheckBoxState CheckBoxState);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/MultiStreamModel.h` (Private)


#### class `UE::MultiUserClient::Replication::FMultiStreamModel`  
`class FMultiStreamModel : public ConcertSharedSlate::IEditableMultiReplicationStreamModel`  
_L28-86_
- inherits: `ConcertSharedSlate::IEditableMultiReplicationStreamModel`
- desc: Decides the client streams that are displayed in the multi-view. This model, in turn, uses IOnlineClientSelectionModel and IOfflineClientSelectionModel to decide which online and offline clients are to be displayed.
- L32 _public prototype_ `FMultiStreamModel( IOnlineClientSelectionModel& InOnlineClientSelectionModel UE_LIFETIMEBOUND, IOfflineClientSelectionModel& InOfflineClientSelectionModel UE_LIFETIMEBOUND, FOnlineClientManager& InOnlineClientManager UE_LIFETIMEBOUND, FOfflineClientManager& InOfflineClientManager UE_LIFETIMEBOUND, FMultiViewOptions& InViewOptions UE_LIFETIMEBOUND );`
- L39 _public prototype_ `~FMultiStreamModel();`
- L42 _public prototype_ `void ForEachDisplayedOnlineClient(TFunctionRef<EBreakBehavior(const FOnlineClient*)> ProcessClient) const;` — Enumerates every displayed online client.
- L45 _public prototype_ `virtual TSet<TSharedRef<ConcertSharedSlate::IReplicationStreamModel>> GetReadOnlyStreams() const override;`
- L46 _public prototype_ `virtual TSet<TSharedRef<ConcertSharedSlate::IEditableReplicationStreamModel>> GetEditableStreams() const override;`
- L47 _public function_ `virtual FOnStreamExternallyChanged& OnStreamExternallyChanged() override`
- L48 _public function_ `virtual FOnStreamSetChanged& OnStreamSetChanged() override`
- L54 _private member_ `IOnlineClientSelectionModel& OnlineClientSelectionModel;` — Gets all online clients that are supposed to be displayed.
- L56 _private member_ `IOfflineClientSelectionModel& OfflineClientSelectionModel;` — Gets all offline clients that are supposed to be displayed.
- L59 _private member_ `FOnlineClientManager& OnlineClientManager;` — Used to clean up subscriptions when client list changes.
- L61 _private member_ `FOfflineClientManager& OfflineClientManager;` — Used to clean up subscriptions when client list changes.
- L64 _private member_ `FMultiViewOptions& ViewOptions;` — Determines whether offline clients should be shown.
- L66 _private member_ `TSet<const FOnlineClient*> CachedOnlineClients;`
- L67 _private member_ `TSet<const FOfflineClient*> CachedOfflineClients;`
- L69 _private member_ `FOnStreamExternallyChanged OnStreamsExternallyChanged;`
- L70 _private member_ `FOnStreamSetChanged OnStreamSetChangedDelegate;`
- L72 _private prototype_ `void RebuildOnlineClients();`
- L73 _private prototype_ `void RebuildOfflineClients();`
- L74 _private function_ `void RebuildClients()`
- L80 _private prototype_ `void UnsubscribeFromOnlineClients() const;`
- L81 _private prototype_ `void UnsubscribeFromOfflineClients() const;`
- L84 _private prototype_ `void HandleOnlineClientStreamExternallyChanged(TWeakPtr<ConcertSharedSlate::IEditableReplicationStreamModel> ChangedStream);` — Handle read-only streams changing
- L85 _private prototype_ `void HandleOfflineClientStreamExternallyChanged(TWeakPtr<ConcertSharedSlate::IReplicationStreamModel> ChangedStream);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L15 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/SAllClientsView.h` (Private)


#### class `UE::MultiUserClient::Replication::SAllClientsView`  
`class SAllClientsView : public SCompoundWidget`  
_L22-44_
- inherits: `SCompoundWidget`
- desc: Leverages SMultiClientView to display all online and offline clients.
- L24 _private function_ `SLATE_BEGIN_ARGS(SAllClientsView)`
- L25 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments&, TSharedRef<IConcertClient> InConcertClient, FMultiUserReplicationManager& InMultiUserReplicationManager);`
- L33 _private function_ `const TSharedPtr<SMultiClientView>& GetClientView() const`
- L38 _private member_ `TUniquePtr<FAllOnlineClientsSelectionModel> AllOnlineClientsModel;` — Keeps track of all online clients.
- L40 _private member_ `TUniquePtr<FAllOfflineClientsSelectionModel> AllOfflineClientsModel;` — Keeps track of all offline clients.
- L43 _private member_ `TSharedPtr<SMultiClientView> ClientView;` — Shows the content of all replication clients.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/SMultiClientView.h` (Private)


#### class `UE::MultiUserClient::Replication::SMultiClientView`  
`class SMultiClientView : public SCompoundWidget`  
_L37-123_
- inherits: `SCompoundWidget`
- desc: Displays a selection of clients.
- L40 _private function_ `SLATE_BEGIN_ARGS(SMultiClientView)`
- L41 _private prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<IConcertClient>& InConcertClient, FMultiUserReplicationManager& InMultiUserReplicationManager, IOnlineClientSelectionModel& InOnlineClientSelectionModel, IOfflineClientSelectionModel& InOfflineClientSelectionModel );`
- L51 _private function_ `const TSharedPtr<ConcertSharedSlate::IMultiReplicationStreamEditor>& GetStreamEditor() const`
- L55 _private member_ `TSharedPtr<IConcertClient> ConcertClient;`
- L57 _private member_ `FUserPropertySelector* UserSelectedProperties = nullptr;` — Keeps track of the properties that the user has selected to iterate on.
- L60 _private member_ `FOnlineClientManager* OnlineClientManager = nullptr;` — These are used to know when to refresh the UI.
- L61 _private member_ `FOfflineClientManager* OfflineClientManager = nullptr;`
- L62 _private member_ `IOnlineClientSelectionModel* OnlineClientSelectionModel = nullptr;`
- L63 _private member_ `IOfflineClientSelectionModel* OfflineClientSelectionModel = nullptr;`
- L69 _private member_ `FMultiViewOptions ViewOptions;` — Controls the content shown in the UI. Important: Some systems keep a reference to ViewOptions. Evaluate destruction order if you move the member ordering.
- L72 _private member_ `TSharedPtr<FMultiStreamModel> StreamModel;` — Combines the online and offline clients.
- L74 _private member_ `TSharedPtr<ConcertSharedSlate::IMultiReplicationStreamEditor> StreamEditor;` — Displayed in the UI.
- L76 _private member_ `TSharedPtr<ConcertSharedSlate::IObjectHierarchyModel> ObjectHierarchy;` — Used by widgets in columns.
- L82 _private member_ `TSharedPtr<SPropertySelectionComboButton> PropertySelectionButton;` — This combo button is shown to the left of the search bar in the bottom half of the replication UI. It allows users to specify the properties they want to work on (i.e. these properties should be shown in the property view).
- L84 _private member_ `TSharedPtr<ConcertSharedSlate::IMultiObjectPropertyAssignmentView> PropertyAssignmentView;` — Displays the properties for the objects displayed in the top view.
- L87 _private member_ `ConcertClientSharedSlate::FHideObjectsNotInWorldLogic HideObjectsNotInEditorWorld;` — This logic helps us decide whether an object should be displayed and lets us know that the object list needs to be refreshed (e.g. due to world change).
- L90 _private prototype_ `TSharedRef<SWidget> CreateEditorContent(const TSharedRef<IConcertClient>& InConcertClient, FMultiUserReplicationManager& InMultiUserReplicationManager);` — Creates this widget's editor content
- L91 _private prototype_ `TSharedRef<SWidget> CreateNoPropertiesWarning() const;`
- L92 _private prototype_ `TSharedRef<SWidget> CreateRightOfSearchBarContent(const TSharedRef<IConcertClient>& InConcertClient, FMultiUserReplicationManager& InMultiUserReplicationManager);`
- L96 _private prototype_ `TSet<FGuid> GetReplicatableClientIds() const;` — @return Gets the clients that may be replicating
- L98 _private prototype_ `void EnumerateReplicatedObjectsInStreams(TFunctionRef<void(const FSoftObjectPath&)> Consumer) const;` — Calls Consumer for each object path that is in a stream - independent of whether it is being replicated or not.
- L100 _private prototype_ `void RebuildClientSubscriptions();`
- L101 _private prototype_ `void CleanClientSubscriptions() const;`
- L102 _private prototype_ `void RefreshUI() const;`
- L105 _private prototype_ `void ExtendObjectContextMenu(FMenuBuilder& MenuBuilder, TConstArrayView<TSoftObjectPtr<>> ContextObjects) const;` — Adds additional entries to the context menu for the object tree view.
- L107 _private prototype_ `bool ShouldDisplayObject(const FSoftObjectPath& Object) const;` — Decides whether the object should be displayed: do not show it if it's not in the editor world.
- L110 _private prototype_ `TSharedRef<SWidget> MakeObjectRowOverlayWidget(const ConcertSharedSlate::FReplicatedObjectData& ReplicatedObjectData) const;` — Creates the widget that overlays actor rows.
- L113 _private function_ `void OnPreAddObjectsFromComboButton(TArrayView<const ConcertSharedSlate::FSelectableObjectInfo>) const` — When the user adds using the combo button, automatically add discover relevant objects and properties.
- L114 _private function_ `void OnPostAddObjectsFromComboButton(TArrayView<const ConcertSharedSlate::FSelectableObjectInfo>) const`
- L117 _private prototype_ `void HandleDroppedObjects(TConstArrayView<UObject*> DroppedObjects) const;` — Called when objects are dropped into the view.
- L120 _private prototype_ `void EnableObjectExtensionOnAdd() const;` — Enables adding common properties and subobjects when an object is added to replication.
- L122 _private prototype_ `void DisableObjectExtensionOnAdd() const;` — Stops adding common properties and subobjects when an object is added to replication.

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L25 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/SObjectOverlayRow.h` (Private)


#### class `UE::MultiUserClient::Replication::SObjectOverlayRow`  
`class SObjectOverlayRow : public SCompoundWidget`  
_L16-41_
- inherits: `SCompoundWidget`
- desc: Overlaid on actor rows.
- L20 _public function_ `SLATE_BEGIN_ARGS(SObjectOverlayRow)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const FSoftObjectPath& InRootObject, const TSharedRef<ConcertSharedSlate::IMultiReplicationStreamEditor>& InStreamEditor );`
- L32 _private member_ `FSoftObjectPath RootObject;` — The top-level object that this row is being shown for.
- L34 _private member_ `TSharedPtr<ConcertSharedSlate::IMultiReplicationStreamEditor> StreamEditor;` — Used to delete the object.
- L37 _private prototype_ `FReply OnPressBinIcon() const;` — Called when the delete icon over an actor is pressed. Clears the entire hierarchy.
- L39 _private prototype_ `FText GetBinIconToolTipText() const;`
- L40 _private prototype_ `bool IsBinIconEnabled() const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L13 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/Selection/AllOfflineClientsSelectionModel.h` (Private)


#### class `UE::MultiUserClient::Replication::FAllOfflineClientsSelectionModel`  
`class FAllOfflineClientsSelectionModel : public IOfflineClientSelectionModel`  
_L16-37_
- inherits: `IOfflineClientSelectionModel`
- desc: Exposes all clients and detects when clients disconnect.
- L20 _public prototype_ `FAllOfflineClientsSelectionModel(FOfflineClientManager& InClientManager UE_LIFETIMEBOUND);`
- L24 _public prototype_ `virtual void ForEachItem(TFunctionRef<EBreakBehavior(FOfflineClient&)> ProcessClient) const override;`
- L25 _public function_ `virtual FOnSelectionChanged& OnSelectionChanged() override`
- L31 _private member_ `FOfflineClientManager& ClientManager;` — Informs us when the list of clients changes
- L34 _private member_ `FOnSelectionChanged OnSelectionChangedDelegate;` — Called when the clients ForEachSelectedClient enumerates has changed.
- L36 _private prototype_ `void OnClientsChanged();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/Selection/AllOnlineClientsSelectionModel.h` (Private)


#### class `UE::MultiUserClient::Replication::FAllOnlineClientsSelectionModel`  
`class FAllOnlineClientsSelectionModel : public IOnlineClientSelectionModel`  
_L15-36_
- inherits: `IOnlineClientSelectionModel`
- desc: Exposes all clients and detects when clients disconnect.
- L19 _public prototype_ `FAllOnlineClientsSelectionModel(FOnlineClientManager& InClientManager UE_LIFETIMEBOUND);`
- L23 _public prototype_ `virtual void ForEachItem(TFunctionRef<EBreakBehavior(FOnlineClient&)> ProcessClient) const override;`
- L24 _public function_ `virtual FOnSelectionChanged& OnSelectionChanged() override`
- L30 _private member_ `FOnlineClientManager& ClientManager;` — Informs us when the list of clients changes
- L33 _private member_ `FOnSelectionChanged OnSelectionChangedDelegate;` — Called when the clients ForEachSelectedClient enumerates has changed.
- L35 _private prototype_ `void OnRemoteClientsChanged();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L10 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/Selection/ISelectionModel.h` (Private)


#### class `UE::MultiUserClient::Replication::ISelectionModel`  
`template<typename TItemType> class ISelectionModel`  
_L16-28_
- desc: Abstracts the concept of a client selection.
- L21 _public prototype_ `virtual void ForEachItem(TFunctionRef<EBreakBehavior(TItemType&)> ProcessItem) const = 0;` — Iterates through every client in the selection.
- L23 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSelectionChanged);`
- L25 _public prototype_ `virtual FOnSelectionChanged& OnSelectionChanged() = 0;` — Called when the clients ForEachSelectedClient enumerates has changed.
- L27 _public prototype_ `virtual ~ISelectionModel() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L10 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSelectionChanged);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/Selection/SelectionModelFwd.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L7 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L13 _typedef_ `using IOfflineClientSelectionModel = ISelectionModel<FOfflineClient>;` (scope `UE::MultiUserClient::Replication`)
- L14 _typedef_ `using IOnlineClientSelectionModel = ISelectionModel<FOnlineClient>;` (scope `UE::MultiUserClient::Replication`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/ViewOptions/MultiViewOptions.h` (Private)


#### class `UE::MultiUserClient::Replication::FMultiViewOptions`  
`class FMultiViewOptions`  
_L10-35_
- desc: The view options for the SMultiClientView.
- L14 _public function_ `bool ShouldShowOfflineClients() const`
- L15 _public function_ `void SetShouldShowOfflineClients(bool bValue)`
- L23 _public function_ `void ToggleShouldShowOfflineClients()`
- L26 _public function_ `FSimpleMulticastDelegate& OnOptionsChanged()` — Broadcasts when a view option changes.
- L31 _private member_ `bool bShowOfflineClients = true;` — Whether offline clients should be shown.
- L34 _private member_ `FSimpleMulticastDelegate OnOptionsChangedDelegate;` — Broadcasts when a view option changes.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L7 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/Multi/ViewOptions/SMultiViewOptions.h` (Private)


#### class `UE::MultiUserClient::Replication::SMultiViewOptions`  
`class SMultiViewOptions : public SCompoundWidget`  
_L14-34_
- inherits: `SCompoundWidget`
- desc: Displays FMultiViewOptions in a combo button.
- L18 _public function_ `SLATE_BEGIN_ARGS(SMultiViewOptions)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FMultiViewOptions& InViewOptions);`
- L30 _private member_ `FMultiViewOptions* ViewOptions = nullptr;` — The view options being displayed and mutated by this widget.
- L33 _private prototype_ `TSharedRef<SWidget> GetViewButtonContent() const;` — @return The menu content for the combo button

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L9 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/PropertySelection/AllRootPropertiesSource.h` (Private)


#### class `UE::MultiUserClient::Replication::FAllRootPropertiesSource`  
`class FAllRootPropertiesSource : public IPropertyItemSource , public FNoncopyable`  
_L17-40_
- inherits: `IPropertyItemSource,FNoncopyable`
- desc: Adapts FReplicatablePropertySource.
- L23 _public prototype_ `FAllRootPropertiesSource( ConcertSharedSlate::FBaseDisplayInfo BaseDisplayInfo, const ConcertSharedSlate::FObjectGroup& ObjectGroup, UClass& SharedClass );`
- L29 _public prototype_ `virtual ConcertSharedSlate::FSourceDisplayInfo GetDisplayInfo() const override;`
- L30 _public prototype_ `virtual void EnumerateSelectableItems(TFunctionRef<EBreakBehavior(const FUserSelectableProperty& SelectableOption)> Delegate) const override;`
- L36 _private member_ `const ConcertSharedSlate::FBaseDisplayInfo BaseDisplayInfo;` — Passed in display info about ObjectGroup.
- L39 _private member_ `const TArray<FUserSelectableProperty> Options;` — The options being iterated.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/PropertySelection/IPropertyItemSource.h` (Private)


#### struct `UE::MultiUserClient::Replication::FUserSelectableProperty`  
`struct FUserSelectableProperty`  
_L13-27_
- L16 _public member_ `ConcertSharedSlate::FObjectGroup ObjectGroup;` — The objects for which this property is selected
- L18 _public member_ `FConcertPropertyChain RootProperty;` — The property shown to the user as option.
- L20 _public member_ `TArray<FConcertPropertyChain> PropertiesToAdd;` — The properties that become (un)selected when the user (un)selects RootProperty. Contains RootProperty.
- L22 _public function_ `FUserSelectableProperty(ConcertSharedSlate::FObjectGroup ObjectGroup, FConcertPropertyChain Property, TArray<FConcertPropertyChain> PropertiesToAdd) : ObjectGroup(MoveTemp(ObjectGroup)) , RootProperty(MoveTemp(Property)) , PropertiesToAdd(MoveTemp(PropertiesToAdd))`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L29 _typedef_ `using IPropertyItemSource = ConcertSharedSlate::IItemSourceModel<FUserSelectableProperty>;` (scope `UE::MultiUserClient::Replication`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/PropertySelection/RootPropertySourceModel.h` (Private)


#### class `UE::MultiUserClient::Replication::FRootPropertySourceModel`  
`class FRootPropertySourceModel : public FNoncopyable`  
_L20-39_
- inherits: `FNoncopyable`
- desc: This model is used to build the combo button to the left of the search bar in the bottom half of the replication UI. It allows users to specify the properties they want to work on (i.e. these properties should be shown in the property view).
- L24 _public prototype_ `FRootPropertySourceModel(FGetObjectDisplayString InGetObjectDisplayStringDelegate);`
- L27 _public prototype_ `void RefreshSelectableProperties(TConstArrayView<ConcertSharedSlate::FObjectGroup> DisplayedObjectGroups);` — Refreshes the properties that the user can select given the objects currently displayed in the bottom view.
- L30 _public function_ `const TArray<TSharedRef<IPropertyItemSource>>& GetPerObjectGroup_AllPropertiesSources() const` — Contains one source for each object group. Each source displays all root properties in that class.
- L35 _private member_ `const FGetObjectDisplayString GetObjectDisplayStringDelegate;` — Determines the display string of an object.
- L38 _private member_ `TArray<TSharedRef<IPropertyItemSource>> PerObjectGroup_AllPropertiesSources;` — Contains one source for each object group. Each source displays all root properties in that class.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/PropertySelection/SPropertySelectionComboButton.h` (Private)


#### class `UE::MultiUserClient::Replication::SPropertySelectionComboButton`  
`class SPropertySelectionComboButton : public SCompoundWidget`  
_L25-58_
- inherits: `SCompoundWidget`
- desc: This combo button is shown to the left of the search bar in the bottom half of the replication UI. It allows users to specify the properties they want to work on (i.e. these properties should be shown in the property view).
- L27 _private typedef_ `using FModelBuilder = ConcertSharedSlate::FSourceModelBuilders<FUserSelectableProperty>;`
- L30 _public function_ `SLATE_BEGIN_ARGS(SPropertySelectionComboButton)`
- L32 _public prototype_ `SLATE_EVENT(FGetObjectDisplayString, GetObjectDisplayString) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FUserPropertySelector& InPropertySelector);` — Gets the display string of objects in the drop-down
- L42 _public prototype_ `void RefreshSelectableProperties(TConstArrayView<ConcertSharedSlate::FObjectGroup> DisplayedObjectGroups) const;` — Refreshes the properties that the user can select given the objects currently displayed in the bottom view.
- L47 _private member_ `FUserPropertySelector* PropertySelector = nullptr;` — Manages the user selected properties
- L50 _private member_ `TUniquePtr<FRootPropertySourceModel> PropertySourceModel;` — Manages the button's content.
- L53 _private prototype_ `TSharedRef<SWidget> MakeMenu() const;` — @return The menu to display when the combo button is clicked
- L54 _private prototype_ `FModelBuilder::FItemPickerArgs MakePickerArguments() const;`
- L57 _private prototype_ `void OnItemsSelected(TArray<FUserSelectableProperty> Properties) const;` — Handles the user selecting an option in the combo button.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L16 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/PropertySelection/SelectionDelegates.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L10 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L12 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetObjectDisplayString, const TSoftObjectPtr<>&) }`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/SPresetComboButton.h` (Private)


#### class `UE::MultiUserClient::Replication::SPresetComboButton`  
`class SPresetComboButton : public SCompoundWidget`  
_L26-73_
- inherits: `SCompoundWidget`
- desc: A combo button displayed to the right of the object search bar. Its menu allows the user to save and load replication presets.
- L30 _public function_ `SLATE_BEGIN_ARGS(SPresetComboButton)`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const IConcertClient& InClient, FPresetManager& InPresetManager);`
- L44 _private member_ `const IConcertClient* Client = nullptr;` — Used to get clients in the session (for filtering purposes).
- L46 _private member_ `FPresetManager* PresetManager = nullptr;` — Used to save & load preset.
- L58 _private member_ `} Options;`
- L61 _private prototype_ `TSharedRef<SWidget> CreateMenuContent();` — Creates the Save & Load options for the menu.
- L62 _private prototype_ `void BuildSaveMenuContent(FMenuBuilder& MenuBuilder);`
- L63 _private prototype_ `void BuildExcludedClientSubmenu(FMenuBuilder& MenuBuilder);`
- L64 _private prototype_ `void BuildLoadMenuContent(FMenuBuilder& MenuBuilder);`
- L67 _private prototype_ `void SavePresetAs() const;` — Saves the current session content.
- L69 _private prototype_ `void LoadPreset(const FAssetData& AssetData) const;` — Handles loading the preset.
- L71 _private prototype_ `EApplyPresetFlags BuildFlags() const;`
- L72 _private prototype_ `FSavePresetOptions BuildSaveOptions() const;`

#### struct `UE::MultiUserClient::Replication::SPresetComboButton::FPresetOptions`  
`struct FPresetOptions`  
_L48-58_
- L51 _public member_ `bool bResetAllOtherClients = true;` — Clients not mentioned by the preset will get their content wiped.
- L54 _public member_ `bool bIncludeAllClients = true;` — Whether the user want so to capture all clients in the preset.
- L57 _public member_ `TArray<FConcertClientInfo> IncludedClients;` — The clients that the preset should not be captured for

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L9 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L16 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L18 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/SReplicationStatus.h` (Private)


#### class `UE::MultiUserClient::Replication::SReplicationStatus`  
`class SReplicationStatus : public SCompoundWidget`  
_L26-64_
- inherits: `SCompoundWidget`
- desc: Displays a text "Replicating x Objects for y Actors". This view sums up all objects being replicated and shows the distinct actors being replicated. Example: You are replicating AActor::ActorGuid and USceneComponent::RelativeLocation on an actor called Floor. Result: "Replicating 2 Objects for 1 Actor".
- L30 _public function_ `SLATE_BEGIN_ARGS(SReplicationStatus)`
- L33 _public prototype_ `SLATE_ATTRIBUTE(TSet<FGuid>, ReplicatableClients) SLATE_EVENT(FForEachObjectInStream, ForEachObjectInStream) SLATE_END_ARGS() static void AppendReplicationStatus(SVerticalBox& VerticalBox, FGlobalAuthorityCache& InAuthorityCache, const FArguments& InArgs);` — The clients that may be replicating, for which we show the stats.
- L42 _public prototype_ `void Construct(const FArguments& InArgs, FGlobalAuthorityCache& InAuthorityCache);`
- L46 _public prototype_ `void RefreshStatusText();` — Updates the status text after an external update has occured.
- L51 _private member_ `FGlobalAuthorityCache* AuthorityCache = nullptr;` — Used to get authority state of objects and informs us when authority changes.
- L54 _private member_ `TAttribute<TSet<FGuid>> ReplicatableClientsAttribute;` — The clients that may be replicating, for which we show the stats.
- L56 _private member_ `FForEachObjectInStream ForEachObjectInStreamDelegate;` — Delegate which enumerates every object registered in a stream - independent of whether it is being replicated or not.
- L59 _private member_ `TSharedPtr<STextBlock> ObjectsText;` — Updated when authority changes. Displays subobjects in bold.
- L61 _private member_ `TSharedPtr<STextBlock> ActorsText;` — Updated when authority changes. Displays actors in bold.
- L63 _private function_ `void OnAuthorityCacheChanged(const FGuid&)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L13 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FForEachObjectInStream, TFunctionRef<void(const FSoftObjectPath&)> Consumer);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FForEachObjectInStream, TFunctionRef<void(const FSoftObjectPath&)> Consumer);` (scope `UE::MultiUserClient::Replication`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Client/SWarningIcon.h` (Private)


#### class `UE::MultiUserClient::Replication::SWarningIcon`  
`class SWarningIcon : public SCompoundWidget`  
_L11-20_
- inherits: `SCompoundWidget`
- desc: Displays a warning triangle
- L15 _public function_ `SLATE_BEGIN_ARGS(SWarningIcon)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L8 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Joined/EClientViewType.h` (Private)


#### enum `UE::MultiUserClient::Replication::EClientViewType`  
`enum class EClientViewType`  
_L8-14_
- desc: Describes a type of view that is being displayed in SReplicationJoinedView and can get selected by the combo button.
- L11 _public enumerator_ `AllClients = 0` — When changing this enum, make sure to update the slot order of SReplicationJoinedView's widget switcher
- L12 _public enumerator_ `LocalClient = 1`
- L13 _public enumerator_ `RemoteClient = 2`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L5 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Joined/SReplicationJoinedView.h` (Private)


#### class `UE::MultiUserClient::Replication::SReplicationJoinedView`  
`class SReplicationJoinedView : public SCompoundWidget`  
_L20-45_
- inherits: `SCompoundWidget`
- desc: This widget is displayed by SReplicationRootWidget when the client has joined replication.
- L24 _public function_ `SLATE_BEGIN_ARGS(SReplicationJoinedView)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<FMultiUserReplicationManager>& InReplicationManager, const TSharedRef<IConcertSyncClient>& InClient );`
- L34 _public function_ `const TSharedPtr<SAllClientsView>& GetAllClientsView() const`
- L39 _private member_ `TSharedPtr<IConcertSyncClient> Client;` — The local client this widget is created for.
- L41 _private member_ `TSharedPtr<FMultiUserReplicationManager> ReplicationManager;` — Acts as the model of this view
- L44 _private member_ `TSharedPtr<SAllClientsView> AllClientsView;` — Shows the content of all replication clients.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/Misc/SNoClients.h` (Private)


#### class `UE::MultiUserClient::Replication::SNoClients`  
`class SNoClients : public SCompoundWidget`  
_L14-32_
- inherits: `SCompoundWidget`
- desc: Special widget that indicates no clients in widgets that list clients, like ownership reassignment combo box.
- L18 _public function_ `static FText GetDisplayText()`
- L20 _public function_ `SLATE_BEGIN_ARGS(SNoClients)`
- L22 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "SNoClients"`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/Replication/SReplicationRootWidget.h` (Private)


#### class `UE::MultiUserClient::Replication::SReplicationRootWidget`  
`class SReplicationRootWidget : public SCompoundWidget`  
_L19-47_
- inherits: `SCompoundWidget`
- desc: Root widget for replication in Multi-User session.
- L23 _public function_ `SLATE_BEGIN_ARGS(SReplicationRootWidget)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FMultiUserReplicationManager> InReplicationManager, TSharedRef<IConcertSyncClient> InClient);`
- L29 _public function_ `const TWeakPtr<SReplicationJoinedView>& GetConnectedView() const`
- L34 _private member_ `TSharedPtr<IConcertSyncClient> Client;` — The client this widget was created for.
- L36 _private member_ `TSharedPtr<FMultiUserReplicationManager> ReplicationManager;` — Manages the business logic which we represent.
- L39 _private member_ `TWeakPtr<SReplicationJoinedView> ConnectedView;` — Shown when the replication handshake has been completed. Invalid otherwise.
- L42 _private prototype_ `void OnReplicationConnectionStateChanged(EMultiUserReplicationConnectionState);` — Called when joining replication session state changes.
- L44 _private prototype_ `void ShowWidget_Connecting();`
- L45 _private prototype_ `void ShowWidget_Connected();`
- L46 _private prototype_ `void ShowWidget_Disconnected();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/SActiveSessionRoot.h` (Private)


#### enum `UE::MultiUserClient::EMultiUserTab`  
`enum class EMultiUserTab : uint8`  
_L26-30_
- L28 _public enumerator_ `Overview`
- L29 _public enumerator_ `Replication`

#### class `UE::MultiUserClient::SActiveSessionRoot`  
`class SActiveSessionRoot : public SCompoundWidget`  
_L36-68_
- inherits: `SCompoundWidget`
- desc: Displayed when the client is connected to an active session. Manages the child content in inline tabs.
- L40 _public member_ `static const FName SessionOverviewTabId;`
- L41 _public member_ `static const FName ReplicationTabId;`
- L43 _public function_ `SLATE_BEGIN_ARGS(SActiveSessionRoot)`
- L45 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IConcertSyncClient> InConcertSyncClient, TSharedRef<Replication::FMultiUserReplicationManager> InReplicationManager);`
- L49 _public function_ `const TSharedPtr<SActiveSessionOverviewTab>& GetOverviewContent() const`
- L50 _public function_ `const TSharedPtr<Replication::SReplicationRootWidget>& GetReplicationContent() const`
- L53 _public prototype_ `void OpenTab(EMultiUserTab Tab);` — Opens the specified inline tab.
- L58 _private member_ `TSharedPtr<SWidgetSwitcher> TabSwitcher;` — This switches "tabs" when a button in the "tab" area is changed.
- L60 _private member_ `TSharedPtr<STabArea> TabArea;` — Holds the buttons for switching inline tabs.
- L63 _private member_ `TSharedPtr<SActiveSessionOverviewTab> OverviewContent;` — Shows general stats, like transaction history and other clients.
- L65 _private member_ `TSharedPtr<Replication::SReplicationRootWidget> ReplicationContent;` — Shows content specific to replication.
- L67 _private prototype_ `TSharedRef<SWidget> CreateTabArea();`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L16 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MultiUserClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/SActiveSessionToolbar.h` (Private)


#### class `UE::MultiUserClient::SActiveSessionToolbar`  
`class SActiveSessionToolbar : public SCompoundWidget`  
_L22-72_
- inherits: `SCompoundWidget`
- desc: Displayed on the top of the window when in a session. Enables the client to leave the session, open the same level as another client or teleport to another client presence.
- L37 _public function_ `SLATE_BEGIN_ARGS(SActiveSessionToolbar)`
- L40 _public prototype_ `SLATE_NAMED_SLOT(FArguments, TabArea) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IConcertSyncClient> InConcertSyncClient);` — Contains the "tab" buttons.
- L48 _private member_ `TWeakPtr<IConcertClientSession> WeakSessionPtr;` — Holds a concert client session.
- L51 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FSendReceiveComboItem>>> SendReceiveComboBox;` — Sets whether this client sends or receives.
- L54 _private member_ `TArray<TSharedPtr<FSendReceiveComboItem>> SendReceiveComboList;` — Available states for the SendReceiveComboBox
- L57 _private prototype_ `FSlateFontInfo GetConnectionIconFontInfo() const;` — Status icon and text
- L58 _private prototype_ `FSlateColor GetConnectionIconColor() const;`
- L59 _private prototype_ `const FButtonStyle& GetConnectionIconStyle() const;`
- L60 _private prototype_ `FText GetConnectionStatusText() const;`
- L63 _private prototype_ `int32 GetInitialSendReceiveComboIndex() const;` — Default, Send Only & Receive Only combo box
- L64 _private prototype_ `TSharedRef<SWidget> GenerateSendReceiveComboItem(TSharedPtr<FSendReceiveComboItem> InItem) const;`
- L65 _private prototype_ `void HandleSendReceiveChanged(TSharedPtr<FSendReceiveComboItem> Item, ESelectInfo::Type SelectInfo) const;`
- L66 _private prototype_ `FText GetRequestedSendReceiveComboText() const;`
- L69 _private prototype_ `bool IsStatusBarLeaveSessionVisible() const;` — Handling for leave session button
- L70 _private prototype_ `FReply OnClickLeaveSession() const;`

#### struct `UE::MultiUserClient::SActiveSessionToolbar::FSendReceiveComboItem`  
`struct FSendReceiveComboItem`  
_L27-35_
- desc: Struct to store the current send / receive state.
- L29 _public function_ `FSendReceiveComboItem(FText InName, FText InToolTip, EConcertSendReceiveState InState) : Name(MoveTemp(InName)), ToolTip(MoveTemp(InToolTip)), State(InState)`
- L32 _public member_ `FText Name;`
- L33 _public member_ `FText ToolTip;`
- L34 _public member_ `EConcertSendReceiveState State;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/STabArea.h` (Private)


#### struct `UE::MultiUserClient::FTabEntry`  
`struct FTabEntry`  
_L15-19_
- L17 _public member_ `TAlwaysValidWidget ButtonContent;`
- L18 _public member_ `FSimpleDelegate OnTabSelected;`

#### class `UE::MultiUserClient::STabArea`  
`class STabArea : public SCompoundWidget`  
_L22-50_
- inherits: `SCompoundWidget`
- desc: Manages multiple STabButtons, making sure exactly 1 is active at a time.
- L26 _public function_ `SLATE_BEGIN_ARGS(STabArea) : _Padding(3.f)`
- L30 _public prototype_ `SLATE_ARGUMENT(TArray<FTabEntry>, Tabs) SLATE_ARGUMENT(int32, ActiveTabIndex) SLATE_ARGUMENT(FMargin, Padding) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The tabs to create
- L41 _public prototype_ `void SetButtonActivated(int32 ButtonIndex);` — Informs the owning view has manually changed to the content displayed by ButtonIndex. Make the button appear selected.
- L46 _private member_ `TArray<TSharedRef<STabButton>> TabButtons;` — The buttons in this area.
- L49 _private prototype_ `void OnButtonActivated(int32 ButtonIndex);` — Called when the button at TabButtons[ButtonIndex] is activated.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ActiveSession/STabButton.h` (Private)


#### class `UE::MultiUserClient::STabButton`  
`class STabButton : public SCompoundWidget`  
_L14-42_
- inherits: `SCompoundWidget`
- desc: Used to switch "tabs" in the active session UI. It is a blue button when active and gray when inactive.
- L18 _public function_ `SLATE_BEGIN_ARGS(STabButton)`
- L20 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnActivated) SLATE_DEFAULT_SLOT(FArguments, ButtonContent) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Called when this button is clicked and becomes active. Not trigger if it was already active.
- L28 _public function_ `void Activate()` — Makes the button appear active.
- L30 _public function_ `void Deactivate()` — Makes the button appear inactive.
- L35 _private member_ `bool bIsActive = false;` — Whether the button is active (the tab content is supposed to be shown).
- L38 _private member_ `FSimpleDelegate OnActivatedDelegate;` — Called when this button is clicked and becomes active. Not trigger if it was already active.
- L40 _private prototype_ `ECheckBoxState IsChecked() const;`
- L41 _private prototype_ `void OnButtonClicked(ECheckBoxState NewState);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/ClientSessionHistoryController.h` (Private)


#### class `FClientSessionHistoryController`  
`class FClientSessionHistoryController : public FAbstractSessionHistoryController`  
_L15-47_
- inherits: `FAbstractSessionHistoryController`
- desc: Manages SSessionHistory for IConcertClients
- L19 _public prototype_ `FClientSessionHistoryController(TSharedRef<IConcertSyncClient> Client, FName PackageFilter = EName::None);`
- L25 _protected prototype_ `virtual void GetActivities(int64 MaximumNumberOfActivities, TMap<FGuid, FConcertClientInfo>& EndpointClientInfoMap, TArray<FConcertSessionActivity>& FetchedActivities) const override;`
- L26 _protected prototype_ `virtual bool GetPackageEvent(const FConcertSessionActivity& Activity, FConcertSyncPackageEventMetaData& OutPackageEvent) const override;`
- L27 _protected prototype_ `virtual TFuture<TOptional<FConcertSyncTransactionEvent>> GetTransactionEvent( const FConcertSessionActivity& Activity) const override;`
- L33 _private member_ `TWeakPtr<IConcertSyncClient> Client;` — So we can unsubscribe from events when destroyed
- L36 _private member_ `TWeakPtr<IConcertClientWorkspace> Workspace;` — Holds a weak pointer to the current workspace.
- L38 _private prototype_ `void SubscribeToWorkspaceEvents();`
- L41 _private prototype_ `void RegisterWorkspaceHandler();` — Registers callbacks with the current workspace.
- L44 _private prototype_ `void HandleWorkspaceStartup(const TSharedPtr<IConcertClientWorkspace>& NewWorkspace);` — Workspace events
- L45 _private prototype_ `void HandleWorkspaceShutdown(const TSharedPtr<IConcertClientWorkspace>& WorkspaceShuttingDown);`
- L46 _private prototype_ `void HandleActivityAddedOrUpdated(const FConcertClientInfo& InClientInfo, const FConcertSyncActivity& InActivity, const FStructOnScope& InActivitySummary);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/Disconnected/ConcertClientSessionBrowserController.h` (Private)


#### class `FConcertClientSessionBrowserController`  
`class FConcertClientSessionBrowserController : public IConcertSessionBrowserController`  
_L24-196_
- inherits: `IConcertSessionBrowserController`
- desc: Runs and cache network queries for the UI. In the model-view-controller pattern, this class acts like the controller. Its purpose is to keep the UI code as decoupled as possible from the API used to query it. It encapsulate the asynchronous code and provide a simpler API to the UI.
- L47 _public prototype_ `FConcertClientSessionBrowserController(IConcertClientPtr InConcertClient);`
- L57 _public prototype_ `TPair<uint32, uint32> TickServersAndSessionsDiscovery();` — Fires new requests to retrieve all known server and for each server, their active and archived sessions. The responses are received asynchronously and may not be available right now. When a response is received, if the corresponding list cached is updated, the list version is incremented. @return A (serverListVersion, sessionsListVersion) pair, corresponding the the versions currently cached by this object.
- L66 _public prototype_ `uint32 TickClientsDiscovery(const FGuid& ServerAdminEndpointId, const FGuid& SessionId);` — Fires a new request to retrieve the clients for the selected session. The result is cached and can be retrived by GetClients(). The class caches clients for a single active session determined by this function. If the specified session changes, the cache of the previous session is cleared. @return The version of the client list currently cached by the object.
- L69 _public prototype_ `bool GetAndClearDiscoveryUpdateFlag();` — Returns true if the controller received async responses and updated its cache since the last time the function was called, then clear the flag.
- L72 _public prototype_ `const TArray<FConcertSessionClientInfo>& GetClients(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const;` — Returns the latest list of clients corresponding to the session known to this controller. Ensure to call TickClientsDiscovery() periodically.
- L74 _public prototype_ `void JoinSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId);`
- L77 _public function_ `bool HasReceivedInitialSessionList() const` — The 2 functions below are used to prevent fast UI transition with the 'no session' panel flashing when the session list is empty.
- L78 _public function_ `bool IsCreatingSession() const`
- L80 _public function_ `IConcertClientPtr GetConcertClient() const`
- L83 _public function_ `virtual TArray<FConcertServerInfo> GetServers() const override`
- L85 _public function_ `virtual TArray<FActiveSessionInfo> GetActiveSessions() const override`
- L92 _public function_ `virtual TArray<FArchivedSessionInfo> GetArchivedSessions() const override`
- L99 _public prototype_ `virtual TOptional<FConcertSessionInfo> GetActiveSessionInfo(const FGuid& AdminEndpoint, const FGuid& SessionId) const override;`
- L100 _public prototype_ `virtual TOptional<FConcertSessionInfo> GetArchivedSessionInfo(const FGuid& AdminEndpoint, const FGuid& SessionId) const override;`
- L102 _public prototype_ `virtual void CreateSession(const FGuid& ServerAdminEndpointId, const FString& SessionName, const FString& ProjectName) override;`
- L103 _public prototype_ `virtual void ArchiveSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& ArchiveName, const FConcertSessionFilter& SessionFilter) override;`
- L104 _public prototype_ `virtual void RestoreSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& RestoredName, const FConcertSessionFilter& SessionFilter) override;`
- L105 _public prototype_ `virtual void RenameActiveSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& NewName) override;`
- L106 _public prototype_ `virtual void RenameArchivedSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& NewName) override;`
- L107 _public prototype_ `virtual bool CanRenameActiveSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const override;`
- L108 _public prototype_ `virtual bool CanRenameArchivedSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const override;`
- L109 _public prototype_ `virtual void DeleteSessions(const FGuid& ServerAdminEndpointId, const TArray<FGuid>& SessionIds) override;`
- L110 _public prototype_ `virtual bool CanDeleteActiveSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const override;`
- L111 _public prototype_ `virtual bool CanDeleteArchivedSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const override;`
- L112 _public function_ `virtual bool CanEverCreateSessions() const override`
- L155 _private prototype_ `void UpdateSessionsAsync();`
- L156 _private prototype_ `void UpdateActiveSessionsAsync(const FConcertServerInfo& ServerInfo);`
- L157 _private prototype_ `void UpdateArchivedSessionsAsync(const FConcertServerInfo& ServerInfo);`
- L158 _private prototype_ `void UpdateClientsAsync(const FGuid& ServerAdminEndpointId, const FGuid& SessionId);`
- L160 _private function_ `void OnActiveSessionDiscovered(const FActiveSessionInfo&)`
- L161 _private function_ `void OnActiveSessionDiscarded(const FActiveSessionInfo&)`
- L162 _private function_ `void OnArchivedSessionDiscovered(const FArchivedSessionInfo&)`
- L163 _private function_ `void OnArchivedSessionDiscarded(const FArchivedSessionInfo&)`
- L164 _private function_ `void OnActiveSessionClientsUpdated(const FActiveSessionInfo&)`
- L165 _private function_ `void OnActiveSessionRenamed(const FActiveSessionInfo&, const FString& NewName)`
- L166 _private function_ `void OnArchivedSessionRenamed(const FArchivedSessionInfo&, const FString& NewName)`
- L167 _private function_ `void OnActiveSessionListDirty()` — This will force the UI to refresh its list.
- L168 _private function_ `void OnArchivedSessionListDirty()` — This will force the UI to refresh its list.
- L171 _private member_ `IConcertClientPtr ConcertClient;` — Holds a concert client instance.
- L174 _private member_ `TMap<FGuid, FAsyncRequest> ActiveSessionRequests;` — The list of active/archived async requests (requesting the list of session) per server. There is only one per server as we prevent stacking more than one at the time.
- L175 _private member_ `TMap<FGuid, FAsyncRequest> ArchivedSessionRequests;`
- L178 _private member_ `TArray<FConcertServerInfo> Servers;` — The cached lists.
- L179 _private member_ `TArray<TSharedPtr<FClientActiveSessionInfo>> ActiveSessions;`
- L180 _private member_ `TArray<TSharedPtr<FClientArchivedSessionInfo>> ArchivedSessions;`
- L183 _private member_ `TOptional<FMonitoredSessionInfo> ClientMonitoredSession;` — The session for which the clients are monitored. UI only monitor client of 1 session at the time.
- L186 _private member_ `uint32 ServerListVersion = 0;` — Holds the version of data cached by the controller. The version is updated when an async response is received and implies a change in the cached values.
- L187 _private member_ `uint32 SessionListVersion = 0;`
- L188 _private member_ `uint32 ClientListVersion = 0;`
- L189 _private member_ `bool bCacheUpdated = false;`
- L190 _private member_ `bool bInitialActiveSessionQueryResponded = false;`
- L191 _private member_ `bool bInitialArchivedSessionQueryResponded = false;`
- L193 _private member_ `TArray<FAsyncRequest> CreateSessionRequests;`
- L194 _private member_ `TArray<FPendingSessionDiscovery> ExpectedSessionsToDiscover;`
- L195 _private member_ `TSet<FString> IgnoredServers;` — List of ignored servers (Useful for testing/debugging)

#### struct `FConcertClientSessionBrowserController::FAsyncRequest`  
`struct FAsyncRequest`  
_L29-45_
- desc: Keeps the state of an active async request and provides a tool to cancel its future continuation execution.
- L32 _public function_ `bool IsOngoing() const` — Returns true if there is a registered async request future and if it hasn't executed yet.
- L35 _public function_ `TWeakPtr<uint8, ESPMode::ThreadSafe> ResetExecutionToken()` — Reset the execution token, canceling previous execution (if any) and setting up the token for a new request.
- L38 _public function_ `void Cancel()` — Cancel the execution of request async continuation.
- L41 _public member_ `TFuture<void> Future;` — The future provided by an asynchronous request.
- L44 _public member_ `TSharedPtr<uint8, ESPMode::ThreadSafe> FutureExecutionToken;` — Determines whether or not the async request continuation code should execute. Reset to disarm execution of an async future continuation.

#### struct `FConcertClientSessionBrowserController::FPendingSessionDiscovery`  
`struct FPendingSessionDiscovery`  
_L118-123_
- desc: Hold information about a session created by this client, not yet 'discovered' by a 'list session' query, but expected to be soon.
- L120 _public member_ `FDateTime CreateTimestamp;`
- L121 _public member_ `FGuid ServerEndpoint;`
- L122 _public member_ `FString SessionName;`

#### struct `FConcertClientSessionBrowserController::FMonitoredSessionInfo`  
`struct FMonitoredSessionInfo`  
_L125-133_
- L127 _public member_ `TSharedRef<FActiveSessionInfo> Session;`
- L128 _public member_ `FAsyncRequest ListClientRequest;`
- L130 _public function_ `FMonitoredSessionInfo(TSharedRef<FActiveSessionInfo> Session) : Session(Session)`

#### struct `FConcertClientSessionBrowserController::FClientActiveSessionInfo`  
`struct FClientActiveSessionInfo : public FActiveSessionInfo`  
_L135-143_
- inherits: `FActiveSessionInfo`
- L138 _public member_ `bool bSessionNameDirty = false;` — Raised when the UI and the cache values may be out of sync if a rename failed (UI assumed it succeeded)
- L140 _public function_ `FClientActiveSessionInfo(FConcertServerInfo ServerInfo, FConcertSessionInfo SessionInfo) : FActiveSessionInfo(MoveTemp(ServerInfo), MoveTemp(SessionInfo))`

#### struct `FConcertClientSessionBrowserController::FClientArchivedSessionInfo`  
`struct FClientArchivedSessionInfo : public FArchivedSessionInfo`  
_L145-153_
- inherits: `FArchivedSessionInfo`
- L148 _public member_ `bool bSessionNameDirty = false;` — Raised when the UI and the cache values may be out of sync if a rename failed (UI assumed it succeeded)
- L150 _public function_ `FClientArchivedSessionInfo(FConcertServerInfo ServerInfo, FConcertSessionInfo SessionInfo) : FArchivedSessionInfo(MoveTemp(ServerInfo), MoveTemp(SessionInfo))`

#### Free symbols / members of external scopes

- L88 _function_ `Algo::Transform(ActiveSessions, Result, [](TSharedPtr<FClientActiveSessionInfo> Info) { return *Info; });` (scope `FConcertClientSessionBrowserController::GetActiveSessions`)
- L95 _function_ `Algo::Transform(ArchivedSessions, Result, [](TSharedPtr<FClientArchivedSessionInfo> Info) { return *Info; });` (scope `FConcertClientSessionBrowserController::GetArchivedSessions`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/Disconnected/SConcertClientSessionBrowser.h` (Private)


#### class `SConcertClientSessionBrowser`  
`class SConcertClientSessionBrowser : public SCompoundWidget`  
_L26-113_
- inherits: `SCompoundWidget`
- desc: Enables the user to browse/search/filter/sort active and archived sessions, create new session, archive active sessions, restore archived sessions, join a session and open the settings dialog.
- L30 _public function_ `SLATE_BEGIN_ARGS(SConcertClientSessionBrowser)`
- L31 _public prototype_ `SLATE_END_ARGS();`
- L39 _public prototype_ `void Construct(const FArguments& InArgs, IConcertClientPtr InConcertClient, TSharedPtr<FText> InSearchText);` — Constructs the Browser. @param InArgs The Slate argument list. @param InConcertClient The concert client used to list, join, delete the sessions. @param[in,out] InSearchText The text to set in the search box and to remember (as output). Cannot be null.
- L41 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L46 _private member_ `TSharedPtr<FConcertClientSessionBrowserController> Controller;` — Gives access to the concert data (servers, sessions, clients, etc).
- L48 _private member_ `TSharedPtr<SConcertSessionBrowser> SessionBrowser;`
- L51 _private member_ `bool bRefreshSessionFilter = true;` — Filtering.
- L52 _private member_ `FString DefaultServerURL;`
- L55 _private member_ `TSharedPtr<SBorder> SessionDetailsView;` — Selected Session Details.
- L56 _private member_ `TSharedPtr<SExpandableArea> DetailsArea;`
- L57 _private member_ `TArray<TSharedPtr<FConcertSessionClientInfo>> Clients;`
- L58 _private member_ `TSharedPtr<SExpandableArea> ClientsArea;`
- L59 _private member_ `TSharedPtr<SListView<TSharedPtr<FConcertSessionClientInfo>>> ClientsView;`
- L62 _private member_ `uint32 DisplayedSessionListVersion = 0;` — Used to compare the version used by UI versus the version cached in the controller.
- L63 _private member_ `uint32 DisplayedClientListVersion = 0;`
- L64 _private member_ `uint32 ServerListVersion = 0;`
- L65 _private member_ `bool bLocalServerRunning = false;`
- L67 _private member_ `TSharedPtr<SWidget> ServerDiscoveryPanel;` — Displayed until a server is found.
- L68 _private member_ `TSharedPtr<SWidget> SessionDiscoveryPanel;` — Displayed until a session is found.
- L69 _private member_ `TSharedPtr<SWidget> NoSessionSelectedPanel;` — Displays 'select a session to view details' message in the details section.
- L70 _private member_ `TSharedPtr<SWidget> NoSessionDetailsPanel;` — Displays 'no details available' message in the details section.
- L71 _private member_ `TSharedPtr<SWidget> NoClientPanel;` — Displays the 'no client connected' message in Clients expendable area.
- L74 _private prototype_ `TSharedRef<SWidget> MakeBrowserContent(TSharedPtr<FText> InSearchText, const TSharedRef<IConcertClient>& Client);` — Layout the 'session|details' split view.
- L75 _private prototype_ `void ExtendControlButtons(FExtender& Extender);`
- L76 _private prototype_ `void ExtendSessionContextMenu(const TSharedPtr<FConcertSessionTreeItem>& Item, FExtender& Extender);`
- L77 _private prototype_ `TSharedRef<SWidget> MakeUserAndSettings(TSharedPtr<FText> InSearchText, const TSharedRef<IConcertClient>& Client);`
- L78 _private prototype_ `TSharedRef<SWidget> MakeOverlayedTableView(const TSharedRef<SWidget>& TableView);`
- L81 _private prototype_ `TSharedRef<SWidget> MakeSessionDetails(TSharedPtr<FConcertSessionTreeItem> Item);` — Layouts the session detail panel.
- L82 _private prototype_ `TSharedRef<SWidget> MakeActiveSessionDetails(TSharedPtr<FConcertSessionTreeItem> Item);`
- L83 _private prototype_ `TSharedRef<SWidget> MakeArchivedSessionDetails(TSharedPtr<FConcertSessionTreeItem> Item);`
- L84 _private prototype_ `TSharedRef<ITableRow> OnGenerateClientRowWidget(TSharedPtr<FConcertSessionClientInfo> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L85 _private prototype_ `void PopulateSessionInfoGrid(SGridPanel& Grid, const FConcertSessionInfo& SessionInfo);`
- L88 _private prototype_ `bool IsLaunchServerButtonEnabled() const;` — The buttons in some overlays
- L89 _private prototype_ `bool IsJoinButtonEnabled() const;`
- L90 _private prototype_ `bool IsAutoJoinButtonEnabled() const;`
- L91 _private prototype_ `bool IsCancelAutoJoinButtonEnabled() const;`
- L92 _private prototype_ `FReply OnNewButtonClicked();`
- L93 _private prototype_ `FReply OnLaunchServerButtonClicked();`
- L94 _private prototype_ `FReply OnShutdownServerButtonClicked();`
- L95 _private prototype_ `FReply OnAutoJoinButtonClicked();`
- L96 _private prototype_ `FReply OnCancelAutoJoinButtonClicked();`
- L99 _private prototype_ `FReply OnJoinButtonClicked();` — SConcertSessionBrowser extensions
- L100 _private prototype_ `void RequestJoinSession(const TSharedPtr<FConcertSessionTreeItem>& ActiveItem);`
- L103 _private prototype_ `void OnSessionSelectionChanged(const TSharedPtr<FConcertSessionTreeItem>& SessionItem);` — Manipulates the sessions view (the array and the UI).
- L104 _private prototype_ `void OnSessionDoubleClicked(const TSharedPtr<FConcertSessionTreeItem>& SessionItem);`
- L105 _private prototype_ `bool ConfirmDeleteSessionWithDialog(const TArray<TSharedPtr<FConcertSessionTreeItem>>& SessionItems) const;`
- L108 _private prototype_ `void ScheduleDiscoveryTaskIfPossible(bool bForceTaskStart);` — Update server/session/clients lists.
- L109 _private prototype_ `EActiveTimerReturnType TickDiscovery(double InCurrentTime, float InDeltaTime);`
- L110 _private prototype_ `void UpdateDiscovery();`
- L111 _private prototype_ `void RefreshClientList(const TArray<FConcertSessionClientInfo>& LastestClientList);`
- L112 _private member_ `UE::Tasks::TTask<bool> DiscoveryTask;`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/Disconnected/SConcertDiscovery.h` (Private)


#### class `SConcertDiscovery`  
`class SConcertDiscovery : public SCompoundWidget`  
_L13-40_
- inherits: `SCompoundWidget`
- desc: Widget displayed when discovering multi-user server(s) or session(s).
- L17 _public function_ `SLATE_BEGIN_ARGS(SConcertDiscovery) : _Text() , _ThrobberVisibility(EVisibility::Visible) , _ButtonVisibility(EVisibility::Visible) , _IsButtonEnabled(true) , _ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("FlatButton")) , _ButtonIcon() , _ButtonText() , _ButtonToolTip() , _OnButtonClicked()`
- L28 _public prototype_ `SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(EVisibility, ThrobberVisibility) SLATE_ATTRIBUTE(EVisibility, ButtonVisibility) SLATE_ATTRIBUTE(bool, IsButtonEnabled) SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle) SLATE_ATTRIBUTE(const FSlateBrush*, ButtonIcon) SLATE_ATTRIBUTE(FText, ButtonText) SLATE_ATTRIBUTE(FText, ButtonToolTip) SLATE_EVENT( FOnClicked, OnButtonClicked) SLATE_END_ARGS();`
- L39 _public prototype_ `void Construct(const FArguments& InArgs);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/Disconnected/SConcertNoAvailability.h` (Private)


#### class `SConcertNoAvailability`  
`class SConcertNoAvailability : public SCompoundWidget`  
_L9-18_
- inherits: `SCompoundWidget`
- desc: Displayed when something is not available.
- L13 _public function_ `SLATE_BEGIN_ARGS(SConcertNoAvailability) : _Text()`
- L14 _public prototype_ `SLATE_ATTRIBUTE(FText, Text) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/SConcertBrowser.h` (Private)


#### class `SConcertBrowser`  
`class SConcertBrowser : public SCompoundWidget`  
_L25-71_
- inherits: `SCompoundWidget`
- desc: Displays the multi-users windows enabling the user to browse active and archived sessions, create new session, archive active sessions, restore archived sessions, join a session and open the settings dialog. Once the user joins a session, the browser displays the SActiveSession widget showing the user status, the session clients and the session history (activity feed).
- L28 _public function_ `SLATE_BEGIN_ARGS(SConcertBrowser)`
- L29 _public prototype_ `SLATE_END_ARGS();`
- L38 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<IConcertSyncClient> InSyncClient, TSharedRef<UE::MultiUserClient::Replication::FMultiUserReplicationManager> InReplicationManager, TSharedPtr<UE::FileSandboxUI::IExternalSandboxActiveViewModel> InExternalSandboxViewModel );` — Constructs the Browser. @param InArgs The Slate argument list. @param InSyncClient The sync client. @param InReplicationManager Used to create replication UI when in an active session
- L44 _public function_ `const TWeakPtr<UE::MultiUserClient::SActiveSessionRoot>& GetActiveSessionWidget() const`
- L45 _public function_ `const TWeakPtr<SConcertClientSessionBrowser>& GetSessionBrowser() const`
- L50 _private member_ `TWeakPtr<IConcertSyncClient> WeakConcertSyncClient;` — Keeps the sync client interface.
- L52 _private member_ `TWeakPtr<UE::MultiUserClient::Replication::FMultiUserReplicationManager> WeakReplicationManager;` — Interacts with the replication system on behalf of Multi-User.
- L54 _private member_ `TWeakPtr<UE::FileSandboxUI::IExternalSandboxActiveViewModel> ExternalSandboxViewModel;` — This view model is used to overlay a widget onto the browser when the engine is already sandboxed.
- L57 _private member_ `TWeakPtr<UE::MultiUserClient::SActiveSessionRoot> ActiveSessionWidget;` — Only valid when in session.
- L59 _private member_ `TWeakPtr<SConcertClientSessionBrowser> SessionBrowser;` — Only valid when not in session.
- L62 _private member_ `TSharedPtr<FText> SearchedText;` — Keeps the session browser searched text in memory to reapply it when a user leaves a session and goes back to the session browser.
- L65 _private prototype_ `void HandleSessionConnectionChanged(IConcertClientSession& InSession, EConcertConnectionStatus ConnectionStatus);` — Invoked when the session connection state is changed.
- L68 _private prototype_ `void AttachChildWidget(EConcertConnectionStatus ConnectionStatus);` — Attaches the child widgets according to the connection status.
- L69 _private prototype_ `void AttachActiveWidget(const TSharedRef<IConcertSyncClient>& InConcertSyncClient);`
- L70 _private prototype_ `void AttachBrowserWidget(const TSharedRef<IConcertSyncClient>& InConcertSyncClient);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace FileSandboxUI` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L17 _namespace_ `namespace Replication` (scope `UE::MultiUserClient`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/SConcertSandboxPersistWidget.h` (Private)


#### struct `FConcertPersistCommand`  
`struct FConcertPersistCommand`  
_L18-25_
- L20 _public member_ `TArray<FName> PackagesToPersist;`
- L21 _public member_ `TArray<FString> FilesToPersist;`
- L22 _public member_ `FText ChangelistDescription;`
- L23 _public member_ `bool bShouldSubmit;`
- L24 _public member_ `bool bShouldMakeFilesWritable;`

#### class `FConcertPersistItem`  
`class FConcertPersistItem : public TSharedFromThis<FConcertPersistItem>`  
_L30-80_
- inherits: `TSharedFromThis<FConcertPersistItem>`
- desc: Persist Widget Row Item View Model
- L34 _public function_ `explicit FConcertPersistItem(FName InPackageName, const FSourceControlStateRef& InItem) : Item(InItem) , PackageName(MoveTemp(InPackageName))` — Constructor
- L43 _public function_ `FName GetPackageName() const` — Returns the package name of this persist item
- L46 _public function_ `FString GetFilename() const` — Returns the full path of the item in source control
- L49 _public function_ `FText GetDisplayName() const` — Returns the name of the item as displayed in the widget
- L52 _public function_ `FName GetIconName() const` — Returns the name of the icon to be used in the list item widget
- L55 _public function_ `FSlateIcon GetIcon() const` — Returns the icon to be used in the list item widget
- L58 _public function_ `FText GetIconTooltip() const` — Returns the tooltip text for the icon
- L61 _public function_ `ECheckBoxState GetCheckBoxState() const` — Returns the checkbox state of this item
- L64 _public function_ `void SetCheckBoxState(ECheckBoxState NewState)` — Sets the checkbox state of this item
- L67 _public function_ `bool IsEnabled() const` — true if the item is enabled in the list
- L70 _private member_ `FSourceControlStateRef Item;` — Reference to the source control state
- L73 _private member_ `ECheckBoxState CheckBoxState;` — Checkbox state
- L76 _private member_ `FText DisplayName;` — Cached name to display in the listview
- L79 _private member_ `FName PackageName;` — The associated package name for this persist item.

#### class `SConcertSandboxPersistWidget`  
`class SConcertSandboxPersistWidget : public SCompoundWidget`  
_L85-223_
- inherits: `SCompoundWidget`
- desc: Persist sandbox window
- L88 _public function_ `SLATE_BEGIN_ARGS(SConcertSandboxPersistWidget)`
- L90 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(TArray<TSharedPtr<FConcertPersistItem>>, Items) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The parent window this widget is hosted in.
- L98 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Used to intercept Escape key press, and interpret it as cancel
- L101 _public function_ `bool IsDialogConfirmed() const` — Get dialog result
- L104 _public prototype_ `FConcertPersistCommand GetPersistCommand() const;` — Get the Persist command from the dialog result.
- L108 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FConcertPersistItem> PersistItemData, const TSharedRef<STableViewBase>& OwnerTable);` — Called by SListView to get a widget corresponding to the supplied item
- L114 _private prototype_ `ECheckBoxState GetToggleSelectedState() const;` — @return the desired toggle state for the ToggleSelectedCheckBox. Returns Unchecked, unless all of the selected items are Checked.
- L120 _private prototype_ `void OnToggleSelectedCheckBox(ECheckBoxState InNewState);` — Toggles the highlighted items. If no items are explicitly highlighted, toggles all items in the list.
- L123 _private prototype_ `FReply OKClicked();` — Called when the settings of the dialog are to be accepted
- L126 _private prototype_ `FReply CancelClicked();` — Called when the settings of the dialog are to be ignored
- L129 _private prototype_ `bool IsOKEnabled() const;` — Called to check if the OK button is enabled or not.
- L132 _private prototype_ `FText GetOKButtonText() const;` — Called to set the text of the OK button.
- L135 _private prototype_ `EVisibility IsWarningPanelVisible() const;` — Check if the submit warning panel should be visible.
- L138 _private prototype_ `bool IsSubmitDescriptionReadOnly() const;` — Check if the submit description should be editable.
- L141 _private prototype_ `void OnCheckStateChanged_SubmitToSourceControl(ECheckBoxState InState);` — Called when the SubmitToSourceControl Checkbox is changed
- L144 _private prototype_ `ECheckBoxState GetSubmitToSourceControl() const;` — Get the current state of the SubmitToSourceControl checkbox
- L147 _private prototype_ `bool CanSubmitToSourceControl() const;` — Check if we can actually submit to source control
- L150 _private prototype_ `void OnCheckStateChanged_KeepCheckedOut(ECheckBoxState InState);` — Called when the Keep checked out Checkbox is changed
- L153 _private prototype_ `ECheckBoxState GetKeepCheckedOut() const;` — Get the current state of the Keep Checked Out checkbox
- L156 _private prototype_ `void OnCheckStateChanged_MakeWritable(ECheckBoxState InState);` — Called when the Make Writable checkbox is changed
- L159 _private prototype_ `ECheckBoxState GetMakeWritable() const;` — Get the current state of the Make Writable checkbox
- L162 _private prototype_ `bool CanCheckOut() const;` — Check if Provider can checkout files
- L172 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;` — Returns the current column sort mode (ascending or descending) if the ColumnId parameter matches the current column to be sorted by, otherwise returns EColumnSortMode_None. @param	ColumnId	Column ID to query sort mode for. @return	The sort mode for the column, or EColumnSortMode_None if it is not known.
- L180 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);` — Callback for SHeaderRow::Column::OnSort, called when the column to sort by is changed. @param	ColumnId	The new column to sort by @param	InSortMode	The sort mode (ascending or descending)
- L186 _private prototype_ `void RequestSort();` — Requests that the source list data be sorted according to the current sort column and mode, and refreshes the list view.
- L191 _private prototype_ `void SortTree();` — Sorts the source list data according to the current sort column and mode.
- L194 _private member_ `bool bDialogConfirmed;` — Result confirmation
- L197 _private member_ `TArray<TSharedPtr<FConcertPersistItem>> ListViewItems;` — Collection of objects (Widgets) to display in the List View.
- L200 _private member_ `TSharedPtr<SListView<TSharedPtr<FConcertPersistItem>>> ListView;` — ListBox for selecting which object to consolidate
- L203 _private member_ `TWeakPtr<SWindow> ParentWindow;` — Pointer to the parent modal window
- L206 _private member_ `TSharedPtr<SExpandableArea> SubmitDescriptionExpandable;` — Internal widgets to save having to get in multiple places
- L207 _private member_ `TSharedPtr<SMultiLineEditableTextBox> SubmitDescriptionTextCtrl;`
- L210 _private member_ `ECheckBoxState SubmitToSourceControl;` — State of the "Submit to Revision Control" checkbox
- L213 _private member_ `ECheckBoxState KeepFilesCheckedOut;` — State of the "Keep Files Checked Out" checkbox
- L216 _private member_ `ECheckBoxState MakeWritable;` — State of the "Make Writable" checkbox
- L219 _private member_ `FName SortByColumn;` — Specify which column to sort with
- L222 _private member_ `EColumnSortMode::Type SortMode;` — Currently selected sorting mode

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Widgets/WidgetGetters.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L15 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<SConcertBrowser>, FGetConcertBrowserWidget);`
- L15 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedPtr<SConcertBrowser>, FGetConcertBrowserWidget);` (scope `UE::MultiUserClient`)
- L16 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<SActiveSessionRoot>, FGetActiveSessionWidget);`
- L16 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedPtr<SActiveSessionRoot>, FGetActiveSessionWidget);` (scope `UE::MultiUserClient`)
- L17 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<ConcertSharedSlate::IMultiReplicationStreamEditor>, FGetReplicationStreamEditorWidget);`
- L17 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedPtr<ConcertSharedSlate::IMultiReplicationStreamEditor>, FGetReplicationStreamEditorWidget);` (scope `UE::MultiUserClient`)
- L20 _prototype_ `TSharedPtr<SActiveSessionRoot> GetActiveSessionWidgetFromBrowser(const SConcertBrowser& Browser);` (scope `UE::MultiUserClient`) — Traverses the UI tree to get the SActiveSessionRoot.
- L23 _prototype_ `TSharedPtr<ConcertSharedSlate::IMultiReplicationStreamEditor> GetReplicationStreamEditorWidgetFromBrowser(const SConcertBrowser& Browser);` (scope `UE::MultiUserClient`) — Traverses the UI tree to get the SActiveSessionRoot.

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Public/IMultiUserClientModule.h` (Public)


#### struct `FServerLaunchOverrides`  
`struct FServerLaunchOverrides`  
_L16-20_
- L19 _public member_ `FString ServerName;` — The name of the server upon launch

#### class `IMultiUserClientModule`  
`class IMultiUserClientModule : public IModuleInterface`  
_L30-107_
- inherits: `IModuleInterface`
- desc: Interface for the Multi-User module.
- L39 _public function_ `static inline IMultiUserClientModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L50 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L61 _public prototype_ `virtual TSharedPtr<IConcertSyncClient> GetClient() const = 0;` — Get the sync client that will performing the MultiUser role @param InRole The role to create @return The client
- L67 _public prototype_ `virtual UE::MultiUserClient::IMultiUserReplication* GetReplication() const = 0;` — Gets the interface for interacting with the replication system that Multi User sets-up. Ownership remains in MultiUser. You cannot keep any reference to it: Call this function instead.
- L72 _public prototype_ `virtual void OpenBrowser() = 0;` — Invokes the Multi-User browser tab
- L77 _public prototype_ `virtual void OpenSettings() = 0;` — Hot-links to Concert Settings.
- L83 _public prototype_ `virtual bool DefaultConnect() = 0;` — Connect to the default connection setup @return true if default connection process properly started
- L90 _public prototype_ `virtual bool DisconnectSession(bool bAlwaysAskConfirmation = false) = 0;` — Disconnect from the current session if any, but prompt the user about session changes first. @param bAlwaysAskConfirmation Prompt the user to confirm leaving the session even if they are no changes to persist. @return true if the session is disconnected, false if the user declined.
- L96 _public prototype_ `virtual TOptional<FProcHandle> LaunchConcertServer(TOptional<FServerLaunchOverrides> LaunchOverrides = {}) = 0;` — Launches a server (if none are running) on the local machine. On success, the server is launched and its FProcHandle is returned. On failure, an asynchronous notification (banner) is displayed to the user.
- L101 _public prototype_ `virtual void ShutdownConcertServer() = 0;` — Shuts down all local servers running. Do nothing if no servers are running.
- L106 _public prototype_ `virtual bool IsConcertServerRunning() = 0;` — @return true if the Concert server is running on the local machine.

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MultiUserClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Public/Replication/ChangeOperationTypes.h` (Public)


#### enum `UE::MultiUserClient::EChangeStreamOperationResult`  
`enum class EChangeStreamOperationResult : uint8`  
_L23-53_
- desc: Result of changing a client's stream
- L26 _public enumerator_ `Success` — All changes made or none were requested.
- L28 _public enumerator_ `NoChanges` — No changes were requested to be made
- L33 _public enumerator_ `Rejected` — The changes were rejected by the server.
- L35 _public enumerator_ `Timeout` — Failed because the request timed out.
- L37 _public enumerator_ `Cancelled` — The submission progress was cancelled, e.g. because the target client disconnected.
- L40 _public enumerator_ `FailedToSendRequest` — Unlikely. ISubmissionWorkflow validation rejected the change. See log. Could be e.g. that the remote client does not allow remote editing.
- L45 _public enumerator_ `NotInSession` — No submission took place because the local editor is not in any session.
- L47 _public enumerator_ `UnknownClient` — No submission took place because the client ID was invalid.
- L49 _public enumerator_ `NotOnGameThread` — The request was not made on the game thread.
- L52 _public enumerator_ `Count` — Not an actual return code. Make sure it's always last.

#### enum `UE::MultiUserClient::EChangeAuthorityOperationResult`  
`enum class EChangeAuthorityOperationResult : uint8`  
_L56-88_
- desc: Result of changing a client's authority
- L59 _public enumerator_ `Success` — All changes made or none were requested.
- L61 _public enumerator_ `NoChanges` — No changes were requested to be made
- L66 _public enumerator_ `RejectedFullyOrPartially` — The changes were rejected by the server.
- L68 _public enumerator_ `Timeout` — Failed because the request timed out.
- L70 _public enumerator_ `CancelledDueToStreamUpdate` — The authority change was not submitted because the stream change was unsuccessful.
- L72 _public enumerator_ `Cancelled` — The submission progress was cancelled, e.g. because the target client disconnected.
- L75 _public enumerator_ `FailedToSendRequest` — Unlikely. ISubmissionWorkflow validation rejected the change. See log. Could be e.g. that the remote client does not allow remote editing.
- L80 _public enumerator_ `NotInSession` — No submission took place because the local editor is not in any session.
- L82 _public enumerator_ `UnknownClient` — No submission took place because the client ID was invalid.
- L84 _public enumerator_ `NotOnGameThread` — The request was not made on the game thread.
- L87 _public enumerator_ `Count` — Not an actual return code. Make sure it's always last.

#### enum `UE::MultiUserClient::EPropertyChangeType`  
`enum class EPropertyChangeType : uint8`  
_L90-101_
- L93 _public enumerator_ `Put` — Replace all assigned properties with the given properties.
- L95 _public enumerator_ `Add` — Append the given properties, keeping any preexisting properties.
- L97 _public enumerator_ `Remove` — Remove the given properties.
- L100 _public enumerator_ `Count` — Not an actual parameter. Make sure it's always last.

#### struct `UE::MultiUserClient::FPropertyChange`  
`struct FPropertyChange`  
_L103-109_
- L106 _public member_ `TSet<FConcertPropertyChain> Properties;` — The properties of the operation
- L108 _public member_ `EPropertyChangeType ChangeType;` — How to interpret Properties.

#### struct `UE::MultiUserClient::FChangeStreamRequest`  
`struct FChangeStreamRequest`  
_L112-122_
- desc: Params for changing a client's stream.
- L115 _public member_ `TMap<UObject*, FPropertyChange> PropertyChanges;` — Property changes to make to objects. This can be used to add new objects.
- L118 _public member_ `TSet<FSoftObjectPath> ObjectsToRemove;` — Objects that should be unregistered (they will also stop replicating if added here)
- L121 _public member_ `FConcertReplication_ChangeStream_Frequency FrequencyChanges;` — Changes how often objects are supposed to be replicated.

#### struct `UE::MultiUserClient::FChangeAuthorityRequest`  
`struct FChangeAuthorityRequest`  
_L125-132_
- desc: Params for changing a client's authority (what they're replicating).
- L128 _public member_ `TSet<FSoftObjectPath> ObjectsToStartReplicating;` — Objects that should start replicating. The objects must previously have been registered.
- L131 _public member_ `TSet<FSoftObjectPath> ObjectToStopReplicating;` — Objects that should stop replicating.

#### struct `UE::MultiUserClient::FChangeClientReplicationRequest`  
`struct FChangeClientReplicationRequest`  
_L135-148_
- desc: Params for changing a client's stream or authority.
- L141 _public member_ `TOptional<FChangeStreamRequest> StreamChangeRequest;` — Changes to make to the client's registered objects. Performed before AuthorityChangeRequest. If it fails, AuthorityChangeRequest will also fail.
- L147 _public member_ `TOptional<FChangeAuthorityRequest> AuthorityChangeRequest;` — Changes to make to the objects the client is replicating. Fails if StreamChangeRequest fails.

#### enum `UE::MultiUserClient::EChangeObjectFrequencyErrorCode`  
`enum class EChangeObjectFrequencyErrorCode : uint8`  
_L150-159_
- L153 _public enumerator_ `UnregisteredStream` — The object for which the frequency was being changed was not registered.
- L155 _public enumerator_ `InvalidReplicationRate` — The replication rate parameter was rejected (it cannot be 0).
- L158 _public enumerator_ `Count` — Not an actual parameter. Make sure it's always last.

#### struct `UE::MultiUserClient::FChangeClientStreamFrequencyResponse`  
`struct FChangeClientStreamFrequencyResponse`  
_L162-168_
- desc: Result about changing frequency.
- L165 _public member_ `TMap<FSoftObjectPath, EChangeObjectFrequencyErrorCode> ObjectErrors;` — Errors encountered for specific objects
- L167 _public member_ `TOptional<EChangeObjectFrequencyErrorCode> DefaultChangeErrorCode;` — Error for changing the default replication frequency.

#### enum `UE::MultiUserClient::EPutObjectErrorCode`  
`enum class EPutObjectErrorCode : uint8`  
_L171-183_
- desc: Explains why a change to an object in the stream was invalid.
- L174 _public enumerator_ `UnresolvedStream` — Stream that the object referenced was not registered on the server.
- L179 _public enumerator_ `MissingData` — Either PutObject contained no data to update with (ensure either ClassPath or Properties is set), or it tried to create a new object with insufficient data (make sure ClassPath and Properties are both specified).
- L182 _public enumerator_ `Count` — Not an actual parameter. Make sure it's always last.

#### struct `UE::MultiUserClient::FChangeClientStreamResponse`  
`struct FChangeClientStreamResponse`  
_L186-214_
- desc: Result of processing FChangeStreamRequest.
- L192 _public member_ `EChangeStreamOperationResult ErrorCode;` — Gives general information about what happened to this request. All other fields only make sense if ErrorCode == Success.
- L201 _public member_ `TMap<FSoftObjectPath, FGuid> AuthorityConflicts;` — Dynamic authority errors. The change was rejected because 1. this client is replicating the object already, 2. another client is also replicating the object, 3. this change would cause overlapping properties with the other client.
- L204 _public member_ `TMap<FSoftObjectPath, EPutObjectErrorCode> SemanticErrors;` — Errors made in the format of the request
- L207 _public member_ `FChangeClientStreamFrequencyResponse FrequencyErrors;` — Errors made in the way frequency was changed.
- L213 _public member_ `bool bFailedStreamCreation = false;` — The client attempted to register the Multi-User stream but failed in doing so. This usually indicates an internal error that you cannot do anything about as API user.

#### struct `UE::MultiUserClient::FChangeClientAuthorityResponse`  
`struct FChangeClientAuthorityResponse`  
_L217-227_
- desc: Result of processing FChangeAuthorityRequest
- L223 _public member_ `EChangeAuthorityOperationResult ErrorCode;` — Gives general information about what happened to this request. All other fields only make sense if ErrorCode == Success.
- L226 _public member_ `TSet<FSoftObjectPath> RejectedObjects;` — Objects the client did not get authority over.

#### struct `UE::MultiUserClient::FChangeClientReplicationResult`  
`struct FChangeClientReplicationResult`  
_L230-234_
- desc: Result of processing a FChangeClientReplicationRequest.
- L232 _public member_ `FChangeClientStreamResponse StreamChangeResult;`
- L233 _public member_ `FChangeClientAuthorityResponse AuthorityChangeResult;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MultiUserClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Public/Replication/IClientChangeOperation.h` (Public)


#### class `UE::MultiUserClient::IClientChangeOperation`  
`class IClientChangeOperation`  
_L18-44_
- desc: Exposes events that occur as part of changing a client's stream, authority, or both. This is the result of IMultiUserReplication::EnqueueChanges. IClientChangeOperation wraps ISubmissionOperation, which is internal to Multi-User. This allows the two interface to change independently.
- L27 _public prototype_ `virtual TFuture<FChangeClientStreamResponse> OnChangeStream() = 0;` — Completes when the operation of changing streams has completed. @note This can be called at most once; subsequent calls result in an unset future. @note This future can complete on any thread.
- L34 _public prototype_ `virtual TFuture<FChangeClientAuthorityResponse> OnChangeAuthority() = 0;` — Completes when the operation of changing authority has completed. @note This can be called at most once; subsequent calls result in an unset future. @note This future can complete on any thread.
- L41 _public prototype_ `virtual TFuture<FChangeClientReplicationResult> OnOperationCompleted() = 0;` — Completes all sub-operations have completed. @note This can be called at most once; subsequent calls result in an unset future. @note This future can complete on any thread.
- L43 _public prototype_ `virtual ~IClientChangeOperation() = default;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Public/Replication/IMultiUserReplication.h` (Public)


#### class `UE::MultiUserClient::IMultiUserReplication`  
`class IMultiUserReplication`  
_L25-124_
- desc: Interface for interacting with Multi-User replication, which uses the Concert replication system.
- L36 _public prototype_ `virtual const FConcertObjectReplicationMap* FindReplicationMapForClient(const FGuid& ClientId) const = 0;` — @return Gets the last known server map of objects registered for replication for an online or offline client. This server state is regularly polled whilst the local client state should always be in sync. @note This function must be called from the game thread. @warning Do not keep any latent reference to the returned pointer. The pointed to memory can be reallocated when the client disconnects.
- L45 _public prototype_ `virtual const FConcertStreamFrequencySettings* FindReplicationFrequenciesForClient(const FGuid& ClientId) const = 0;` — @return Gets the last known server object replication frequencies for an online or offline . This server state is regularly polled whilst the local client state should always be in sync. @note This function must be called from the game thread. @warning Do not keep any latent reference to the returned pointer. The pointed to memory can be reallocated when the client disconnects.
- L51 _public prototype_ `virtual bool IsReplicatingObject(const FGuid& ClientId, const FSoftObjectPath& ObjectPath) const = 0;` — @return Whether the local editor instance thinks the client has authority over the properties it has registered to ObjectPath. @note This function must be called from the game thread.
- L62 _public prototype_ `virtual void RegisterReplicationDiscoverer(TSharedRef<IReplicationDiscoverer> Discoverer) = 0;` — Register a discoverer. It is used to automatically configure UObjects for replication when appropriate: - When an user adds an object via Add Actor button - When an UObject is added to the world via a transaction (run on the client machine that adds the UObject) This function must be called from the game thread. @note This function must be called from the game thread.
- L67 _public prototype_ `virtual void RemoveReplicationDiscoverer(const TSharedRef<IReplicationDiscoverer>& Discoverer) = 0;` — Unregisters a previously registered discoverer. @note This function must be called from the game thread.
- L81 _public prototype_ `virtual TSharedRef<IClientChangeOperation> EnqueueChanges(const FGuid& ClientId, TAttribute<FChangeClientReplicationRequest> SubmissionParams) = 0;` — Enqueues a request for changing a client's stream and authority. The request is enqueued with the other requests that Multi-User might have ongoing already (like those triggered by the UI). A stream is the mapping of objects to properties. The authority state specifies which of the registered objects should actually be sending data. The stream change is requested first and is followed by the authority change. @param ClientId The client for which to change authority @param SubmissionParams Once the request is ready to be sent to the server, this attribute is used to generate the change request @note This function must be called from the game thread.
- L96 _public prototype_ `virtual void ForEachOfflineClient(TFunctionRef<EBreakBehavior(const IOfflineReplicationClient&)> Callback) const = 0;` — Iterates over every user who was previously connected to the current session but is now offline. The callback function is invoked for each offline client with the last endpoint ID the user had. Endpoint IDs are associated with the "same" user by matching equal display names and device names. @param Callback The callback function to invoke for each offline client. @warning The client instance is only guaranteed to be valid for the duration of the call - do not keep any reference to it! @note This function must be called from the game thread.
- L106 _public prototype_ `virtual bool FindOfflineClient(const FGuid& ClientId, TFunctionRef<void(const IOfflineReplicationClient&)> Callback) const = 0;` — Finds an offline client by an endpoint Id that was associated with the user in the past. @return Whether Callback was invoked. @warning The client instance is only guaranteed to be valid for the duration of the call - do not keep any reference to it! @note This function must be called from the game thread.
- L110 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnServerStateChanged, const FGuid& );`
- L112 _public prototype_ `virtual FOnServerStateChanged& OnStreamServerStateChanged() = 0;` — @return Delegate that triggers when the given client's known server state has changed.
- L114 _public prototype_ `virtual FOnServerStateChanged& OnAuthorityServerStateChanged() = 0;` — @return Delegate that triggers when the given client's known server state has changed.
- L116 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnOfflineClientsChanged);`
- L118 _public prototype_ `virtual FOnOfflineClientsChanged& OnOfflineClientsChanged() = 0;` — @return Delegate that triggers when the endpoints considered offline have changed.
- L121 _public prototype_ `virtual FOnServerStateChanged& OnOfflineClientContentChanged() = 0;` — @return Delegates that triggers when the content of an offline client has changed. Not called as part of OnOfflineClientsChanged.
- L123 _public prototype_ `virtual ~IMultiUserReplication() = default;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiUserClient` (scope `UE`)
- L110 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnServerStateChanged, const FGuid& );`
- L116 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnOfflineClientsChanged);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Public/Replication/IOfflineReplicationClient.h` (Public)


#### class `UE::MultiUserClient::IOfflineReplicationClient`  
`class IOfflineReplicationClient`  
_L12-24_
- desc: Interface for querying information about an offline replication client.
- L17 _public prototype_ `virtual const FConcertClientInfo& GetClientInfo() const = 0;` — @return The client info this client had when they were last connected.
- L19 _public prototype_ `virtual const FGuid& GetLastAssociatedEndpoint() const = 0;` — @return The endpoint id this client had when they were last connected.
- L21 _public prototype_ `virtual const FConcertBaseStreamInfo& GetPredictedStream() const = 0;` — @return The stream content that is expected to be reclaimed by this client when rejoining the session.
- L23 _public prototype_ `virtual ~IOfflineReplicationClient() = default;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Public/Replication/IReplicationDiscoverer.h` (Public)


#### struct `UE::MultiUserClient::FReplicationDiscoveryParams`  
`struct FReplicationDiscoveryParams`  
_L14-22_
- L17 _public member_ `UObject& ExtendedObject;` — The object that was added to the stream and for which to discover additional settings.
- L19 _public member_ `const FGuid& EndpointId;` — The endpoint ID of the client to whose stream the object is registered
- L21 _public member_ `IReplicationDiscoveryContext& Context;` — Mutate replication settings using this context object.

#### class `UE::MultiUserClient::IReplicationDiscoverer`  
`class IReplicationDiscoverer`  
_L39-50_
- desc: An interface for setting up default replication settings for an object. This is used when Multi-User determines that an object should be automatically owned by a client and e.g. wants to set up a common workflow. For example, if you have a specific actor type for which a user usually wants to replicate the position & rotation, you can use this to set up the workflow automatically for the user. Situations where this is executed: - When a user adds the object to a replication stream using the "Add Actor" button - When the user adds an actor to the world while in a session, they might automatically want to replicate it (TODO UE-202194) This interface is similar to IStreamExtensionContext but the interfaces serve different purposes. IStreamExtensionContext concerns itself with extending general streams. IReplicationDiscoveryContext is specific to Multi User. For example, this interface exposes endpoint IDs for which does not make sense for IStreamExtensionContext.
- L47 _public prototype_ `virtual void DiscoverReplicationSettings(const FReplicationDiscoveryParams& Params) = 0;` — Finds replication settings given the ExtendedObject. Using Context, you can assign properties or add additional objects.
- L49 _public prototype_ `virtual ~IReplicationDiscoverer() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Public/Replication/IReplicationDiscoveryContext.h` (Public)


#### class `UE::MultiUserClient::IReplicationDiscoveryContext`  
`class IReplicationDiscoveryContext`  
_L20-43_
- desc: An interface for discovering replication settings for an object. This interface is very similar to IStreamExtensionContext but the interfaces serve different purposes. IStreamExtensionContext concerns itself with extending general streams. IReplicationDiscoveryContext is specific to Multi User. @see IReplicationDiscoverer
- L31 _public prototype_ `virtual void AddPropertyTo(UObject& Object, FConcertPropertyChain PropertyChain) = 0;` — Extends the stream with the given object, if not yet added, and adds the property to it. If Object was not yet in the stream, IStreamExtender::ExtendStream will be called for Object. @param Object Object to add, if not yet present, and assign a property to @param PropertyChain Property chain to associate with the object
- L40 _public prototype_ `virtual void AddAdditionalObject(UObject& Object) = 0;` — Adds an additional object. If Object was not yet in the stream, IStreamExtender::ExtendStream will be called for Object. @param Object The additional object to add
- L42 _public prototype_ `virtual ~IReplicationDiscoveryContext() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserClient` (scope `UE`)
