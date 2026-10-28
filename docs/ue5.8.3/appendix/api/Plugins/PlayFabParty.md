# Plugins / PlayFabParty

- module root: `Plugins/Online/Microsoft/PlayFabParty/Source`
- headers: 11; symbols: 274
- symbol kinds: class=7, delegate=1, enum=1, enumerator=3, function=4, macro=1, member=64, namespace=3, prototype=186, struct=3, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, CoreUObject, Engine, GDKRuntime, GRDK, Json, OnlineSubsystem, OnlineSubsystemUtils, Sockets
- PublicDependencyModuleNames: Core

### `Plugins/Online/Microsoft/PlayFabParty/Source/Private/PlayFabParty.h` (Private)


#### Free symbols / members of external scopes

- L15 _prototype_ `FString GetPlayFabPartyErrorMessage(const PartyError ErrorCode);`

### `Plugins/Online/Microsoft/PlayFabParty/Source/Private/PlayFabPartyInternetAddr.h` (Private)


#### class `FPlayFabPartyInternetAddr`  
`class FPlayFabPartyInternetAddr : public FInternetAddr`  
_L16-63_
- inherits: `FInternetAddr`
- L20 _public prototype_ `FPlayFabPartyInternetAddr();`
- L21 _public prototype_ `explicit FPlayFabPartyInternetAddr(const FString& SerializedNetworkDescriptor);`
- L22 _public prototype_ `explicit FPlayFabPartyInternetAddr(const Party::PartyEndpoint& PlayFabEndpoint);`
- L24 _public prototype_ `FPlayFabPartyInternetAddr(const FPlayFabPartyInternetAddr& Other);`
- L25 _public prototype_ `FPlayFabPartyInternetAddr(FPlayFabPartyInternetAddr&& Other) = default;`
- L26 _public prototype_ `FPlayFabPartyInternetAddr& operator=(const FPlayFabPartyInternetAddr& Other);`
- L27 _public prototype_ `FPlayFabPartyInternetAddr& operator=(FPlayFabPartyInternetAddr&& Other) = default;`
- L28 _public prototype_ `virtual ~FPlayFabPartyInternetAddr() = default;`
- L31 _public prototype_ `virtual void SetIp(uint32 InAddr) override;`
- L32 _public prototype_ `virtual void SetIp(const TCHAR* InAddr, bool& bIsValid) override;`
- L33 _public prototype_ `virtual void GetIp(uint32& OutAddr) const override;`
- L34 _public prototype_ `virtual void SetPort(int32 InPort) override;`
- L35 _public prototype_ `virtual int32 GetPort() const override;`
- L36 _public prototype_ `virtual void SetRawIp(const TArray<uint8>& RawAddr) override;`
- L37 _public prototype_ `virtual TArray<uint8> GetRawIp() const override;`
- L38 _public prototype_ `virtual void SetAnyAddress() override;`
- L39 _public prototype_ `virtual void SetBroadcastAddress() override;`
- L40 _public prototype_ `virtual void SetLoopbackAddress() override;`
- L41 _public prototype_ `virtual FString ToString(bool bAppendPort) const override;`
- L42 _public prototype_ `virtual uint32 GetTypeHash() const override;`
- L43 _public prototype_ `virtual bool IsValid() const override;`
- L44 _public prototype_ `virtual TSharedRef<FInternetAddr> Clone() const override;`
- L45 _public prototype_ `virtual FName GetProtocolType() const override;`
- L49 _public prototype_ `const Party::PartyNetworkDescriptor* GetNetworkDescriptor() const;` — Get the Network Descriptor for this internet address
- L51 _public prototype_ `void SetNetworkDescriptor(const Party::PartyNetworkDescriptor& NewNetworkDescriptor);` — Set the Network Descriptor to a new value
- L53 _public prototype_ `void SetNetworkDescriptor(TUniquePtr<Party::PartyNetworkDescriptor>&& NewNetworkDescriptor);` — Set the Network Descriptor to a new value
- L55 _public prototype_ `void Clear();` — Clears all set state of this object
- L59 _protected member_ `TUniquePtr<Party::PartyNetworkDescriptor> NetworkDescriptor;` — The unique address of this network
- L62 _protected member_ `TOptional<uint16> Port;` — The unique identifier for a specific endpoint on this network (or unset if we're not talking about a specific user)

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Party`

### `Plugins/Online/Microsoft/PlayFabParty/Source/Private/PlayFabPartyLive.h` (Private)
_(no declarations extracted)_

### `Plugins/Online/Microsoft/PlayFabParty/Source/Private/PlayFabPartyLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPlayFabParty, VeryVerbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPlayFabParty, VeryVerbose, All);`

### `Plugins/Online/Microsoft/PlayFabParty/Source/Private/PlayFabPartyManager.h` (Private)


#### enum `EPlayFabPartyLoginState`  
`enum class EPlayFabPartyLoginState : uint8`  
_L50-58_
- desc: States of our login state machine
- L53 _public enumerator_ `NeedLogin = 0` — We need to login still
- L55 _public enumerator_ `InProgress = 1` — We are currently logging in
- L57 _public enumerator_ `LoggedIn = 2` — We are successfully logged in

#### struct `FPlayFabPartyEntityId`  
`struct FPlayFabPartyEntityId`  
_L61-70_
- desc: Storage class for a PlayFab Entity ID
- L64 _public prototype_ `explicit FPlayFabPartyEntityId(PartyString EntityId);`
- L66 _public prototype_ `PartyString GetEntityId() const;`
- L69 _private member_ `TArray<char, TFixedAllocator<Party::c_maxEntityIdStringLength + 1>> Data;`

#### struct `FPlayFabPartyEntityToken`  
`struct FPlayFabPartyEntityToken`  
_L73-83_
- desc: Storage class for a PlayFab Entity ID
- L76 _public prototype_ `explicit FPlayFabPartyEntityToken(PartyString EntityToken);`
- L78 _public prototype_ `PartyString GetEntityToken() const;`
- L81 _private member_ `TArray<char, TFixedAllocator<1024>> Data;`

#### class `FPlayFabPartyManager`  
`class FPlayFabPartyManager : public TSharedFromThis<FPlayFabPartyManager, ESPMode::ThreadSafe>`  
_L87-297_
- inherits: `TSharedFromThis<FPlayFabPartyManager,ESPMode::ThreadSafe>`
- desc: Class to manage the status of PlayFabParty and handle its events
- L91 _public prototype_ `virtual ~FPlayFabPartyManager();`
- L94 _public prototype_ `static TSharedPtr<FPlayFabPartyManager, ESPMode::ThreadSafe> CreateManager(FPlayFabPartySocketSubsystem& OwningSocketSubsystem, const FString& AppId, FString& OutError);` — Create an instance of our PlayFabParty manager
- L96 _public prototype_ `static TOptional<FString> GetAppId();` — Get the PlayFabParty AppId specified in the configuration files
- L99 _public prototype_ `bool BindSystemDelegates();` — Bind our system delegates
- L101 _public prototype_ `void UnbindSystemDelegates();` — Unbind our system delegates
- L104 _public prototype_ `bool IsInitialized() const;` — Check if PlayFabParty is Initialized
- L106 _public prototype_ `bool IsReady() const;` — We are ready if PlayFabParty is Initialized and we have a logged in user
- L109 _public prototype_ `Party::PartyLocalUser* GetPartyLocalUser();` — Get our Party Local User instance
- L111 _public prototype_ `const Party::PartyLocalUser* GetPartyLocalUser() const;` — Get our Party Local User instance
- L114 _public prototype_ `Party::PartyXblLocalChatUser* GetPartyXboxLocalChatUser();` — Get our Party Xbox Local Chat User instance
- L116 _public prototype_ `const Party::PartyXblLocalChatUser* GetPartyXboxLocalChatUser() const;` — Get our Party Xbox Local Chat User instance
- L119 _public prototype_ `const TOptional<FString>& GetQOSString() const;` — Get our QOS json string to be sent to Xbox Live
- L122 _public prototype_ `TUniquePtr<Party::PartyNetworkDescriptor> CreateNetwork(const FString& InitialInvitationString, const uint32 MaxPlayers, void* CallbackContext) const;` — Create a new network descriptor with the provided configuration
- L125 _public prototype_ `bool HaveEntityIdForXuid(const uint64 Xuid);` — Do we have a cached Entity ID for the provided Xuid?
- L127 _public prototype_ `PartyString GetEntityIdForXuid(const uint64 Xuid);` — Get the cached Entity ID for the provided Xuid. Asserts if we do not have a value cached!
- L130 _public prototype_ `PartyString GetEntityTokenForXuid(const uint64 Xuid);` — Get the cached Entity ID for the provided Xuid if any!
- L134 _public prototype_ `PFEntityHandle GetEntityHandleForXuid(const uint64 Xuid);` — Get the cached Entity Handle for the provided Xuid if any!
- L138 _public function_ `TSharedPtr<FSocket> GetPlayFabSocketListenServer() const` — Get PlayFab socket of listen server
- L140 _public function_ `void SetPlayFabSocketListenServer(const TSharedPtr<FSocket>& Socket)` — Save PlayFab socket of listen server so to prevent recreating
- L143 _public function_ `bool IsNetworkConnected() const` — Check if PlayFab network is connected
- L146 _protected prototype_ `FPlayFabPartyManager(FPlayFabPartySocketSubsystem& SocketSubsystem, const FString& AppId);`
- L149 _protected prototype_ `void UpdatePlayFabPartyStatus();` — Reprocess our PlayFabParty state after a state change happens and either init, shutdown, or do nothing
- L152 _protected prototype_ `void InitPlayFabParty();` — Attempt to initialize PlayFabParty
- L156 _protected prototype_ `void ShutdownPlayFabCore(bool bForceRunSync = false);` — Shutdown PlayFabCore
- L159 _protected prototype_ `static void CleanupPlayFabPartySingleton();` — Shutdown PlayFabParty manager singleton
- L161 _protected prototype_ `static void CleanupPlayFabPartyXboxSingleton();` — Shutdown PlayFabParty Xbox manager singleton
- L163 _protected prototype_ `void ShutdownPlayFabParty(bool bForceRunSync = false);` — Shutdown PlayFabParty
- L166 _protected prototype_ `void CheckLoginStatus();` — Check if we should login or refresh our auth right now
- L169 _protected prototype_ `void Login(const uint64 XboxUserId);` — Login to PlayFabParty as the specified XUID
- L171 _protected prototype_ `void RefreshLogin();` — Refresh our current login session with new credentials
- L173 _protected prototype_ `void Logout();` — Logout of our current PlayFabParty session
- L176 _protected prototype_ `void HandleAppSuspended();` — Handle the title preparing to suspend
- L178 _protected prototype_ `void HandleAppResume();` — Handle the title preparing to resume from suspension
- L180 _protected prototype_ `void HandleNetworkInitializationChanged(bool bNetworkInitializationStatus);` — Handle the title's network initialization changing
- L183 _protected prototype_ `void HandleQOSDataRequested(FName SessionName);` — Handle QOS data being requested from the OSS
- L186 _protected prototype_ `bool Tick(float DeltaSeconds);` — Handle ticking PlayFabParty
- L189 _protected prototype_ `void ProcessPlayFabPartyEvents();` — Process the PlayFabParty event loop
- L190 _protected prototype_ `void HandleRegionsChanged(const Party::PartyRegionsChangedStateChange* const StateChange);`
- L191 _protected prototype_ `void HandleConnectToNetworkCompleted(const Party::PartyConnectToNetworkCompletedStateChange* const StateChange);`
- L192 _protected prototype_ `void HandleAuthenticateLocalUserCompleted(const Party::PartyAuthenticateLocalUserCompletedStateChange* const StateChange);`
- L193 _protected prototype_ `void HandleCreateEndpointCompleted(const Party::PartyCreateEndpointCompletedStateChange* const StateChange);`
- L194 _protected prototype_ `void HandleEndpointDestroyed(const Party::PartyEndpointDestroyedStateChange* const StateChange);`
- L195 _protected prototype_ `void HandleNetworkDestroyed(const Party::PartyNetworkDestroyedStateChange* const StateChange);`
- L196 _protected prototype_ `void HandleEndpointMessageReceived(const Party::PartyEndpointMessageReceivedStateChange* const StateChange);`
- L197 _protected prototype_ `void HandleCreateInvitationCompleted(const Party::PartyCreateInvitationCompletedStateChange* const StateChange);`
- L198 _protected prototype_ `void HandleLeaveNetworkCompleted(const Party::PartyLeaveNetworkCompletedStateChange* StateChange);`
- L201 _protected prototype_ `void ProcessPlayFabPartyXboxEvents();` — Process the PlayFabParty Xbox event loop
- L202 _protected prototype_ `void HandleXboxCreateLocalChatUserCompleted(const Party::PartyXblCreateLocalChatUserCompletedStateChange* const StateChange);`
- L203 _protected prototype_ `void HandleLoginToPlayFabCompleted(const Party::PartyXblLoginToPlayFabCompletedStateChange* const StateChange);`
- L204 _protected prototype_ `void HandleGetEntityIdsFromXboxLiveUserIdsCompleted(const Party::PartyXblGetEntityIdsFromXboxLiveUserIdsCompletedStateChange* const StateChange);`
- L208 _protected prototype_ `void HandleLocalPlayerCreationWithEntityToken(const Party::PartyXblLoginToPlayFabCompletedStateChange* const);`
- L214 _protected member_ `FPlayFabPartySocketSubsystem& SocketSubsystem;` — Reference to the socket subsystem that created us
- L216 _protected member_ `FString AppId;` — The AppId for this application from PlayFab's website
- L218 _protected member_ `FString PlayFabURL;` — The URL for this application PlayFab's website
- L220 _protected member_ `double LoginFailureDelaySeconds = 15.0;` — The delay in seconds after a login completes (success or failure) before another login may occur
- L224 _protected member_ `double LoginRefreshDelaySeconds = 7200.0;` — The delay in seconds after a successful login complete before we should login again to get a new token
- L229 _protected member_ `std::atomic<bool> bIsPlayFabCoreInit = false;` — Is PlayFabCore currently initialized?
- L232 _protected member_ `std::atomic<bool> bIsPlayFabPartyInit = false;` — Is PlayFabParty currently initialized?
- L234 _protected member_ `std::atomic<bool> bIsPlayFabPartyXboxInit = false;` — Is PlayFabParty Xbox currently initialized?
- L237 _protected member_ `bool bIsAppSuspending = false;` — Is the app currently suspended?
- L239 _protected member_ `bool bIsNetworkReady = false;` — Is the network ready for usage?
- L242 _protected member_ `bool bIsNetworkConnected = false;` — The flag to indicate if the game is connected playfab network. Since it's async operation, we can't create another socket to connect to playfab network, while previous socket hasn't finished leaving playfab network yet
- L246 _protected member_ `std::atomic<PFServiceConfigHandle> PFCoreServiceHandle {};` — Handle to manage PlayFabCore lifecycle
- L250 _protected member_ `FDelegateHandle QOSDataRequestedHandle;` — Handle to our QOS Data binding
- L253 _protected member_ `FTSTicker::FDelegateHandle TickHandle;` — Handle to our tick function binding
- L255 _protected member_ `FDelegateHandle AppSuspendingHandle;` — Handle to our application suspending binding
- L257 _protected member_ `FDelegateHandle AppResumingHandle;` — Handle to our application resuming binding
- L259 _protected member_ `FDelegateHandle NetworkInitializationChangedHandle;` — Handle to our network initialization changed binding
- L262 _protected member_ `uint64 LocalUserXuid = 0;` — The user we are logged in as (if non-zero)
- L264 _protected member_ `EPlayFabPartyLoginState LocalUserLoginState = EPlayFabPartyLoginState::NeedLogin;` — The local users's login state for deciding if we want to login or not
- L266 _protected member_ `double NextLoginTimeSeconds = 0.0;` — The next time we can possibly try logging in again (throttle protection for login requests)
- L270 _protected member_ `double NextLoginRefreshTimeSeconds = 0.0;` — The next time we should refresh our login credentials (to ensure they do not expire while in use)
- L274 _protected member_ `Party::PartyXblLocalChatUser* PartyXboxLocalChatUser = nullptr;` — Our local xbox chat user
- L276 _protected member_ `Party::PartyLocalUser* PartyLocalUser = nullptr;` — Our local user object (only set if we are successfully logged in)
- L279 _protected member_ `TOptional<FString> QOSData;` — Cached QOS ping latency for Azure datacenters (in JSON format) for XboxLive sessions
- L282 _protected member_ `TMap<Party::PartyNetwork*, uint64> PartyToSocketContextMap;` — Map of party networks to the socket contexts that own the network
- L285 _protected member_ `TSharedPtr<FSocket> PlayFabSocketListenServer;` — Hold the PlayFab socket for the listen server, to make sure not create it again(to keep the same listen server url) even if using non-seamless travel
- L288 _protected member_ `TMap<uint64, TUniqueObj<FPlayFabPartyEntityId>> XboxUserIdToPlayFabEntityIdMap;` — Map of Xbox XUIDs to PlayFab Entity IDs
- L291 _protected member_ `TMap<uint64, TUniqueObj<FPlayFabPartyEntityToken>> XboxUserIdToPlayFabEntityTokenMap;` — Map of Xbox XUIDs to PlayFab Entity Tokens
- L295 _protected member_ `TMap<uint64, PFEntityHandle> XboxUserIdToPlayFabEntityHandleMap;` — Map of Xbox XUIDs to PlayFab Entity Handles

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Party`
- L47 _typedef_ `using HANDLE = void*;`

### `Plugins/Online/Microsoft/PlayFabParty/Source/Private/PlayFabPartyModule.h` (Private)


#### class `FPlayFabPartyModule`  
`class FPlayFabPartyModule : public IModuleInterface`  
_L14-38_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public prototype_ `virtual bool SupportsDynamicReloading() override;`
- L22 _public prototype_ `virtual bool SupportsAutomaticShutdown() override;`
- L29 _public function_ `static inline FPlayFabPartyModule& Get()` — Singleton-like access to the PlayFab module instance @return Returns FPlayFabPartyModule singleton instance, loading the module on demand if needed
- L36 _public member_ `TUniquePtr<FPlayFabPartySocketSubsystem> PlayFabPartySocketSubsystem;` — Instance of our SocketSubsystem

### `Plugins/Online/Microsoft/PlayFabParty/Source/Private/PlayFabPartyNetConnection.h` (Private)


#### class `UPlayFabPartyNetConnection`  
`class UPlayFabPartyNetConnection : public UIpConnection`  
_L12-24_
- reflection: `UCLASS(Transient, Config=Engine)`
- inherits: `UIpConnection`
- L18 _public prototype_ `explicit UPlayFabPartyNetConnection(const FObjectInitializer& ObjectInitializer);`
- L21 _public prototype_ `virtual void InitLocalConnection(UNetDriver* InDriver, FSocket* InSocket, const FURL& InURL, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`
- L22 _public prototype_ `virtual void InitRemoteConnection(UNetDriver* InDriver, FSocket* InSocket, const FURL& InURL, const FInternetAddr& InRemoteAddr, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`

### `Plugins/Online/Microsoft/PlayFabParty/Source/Private/PlayFabPartyNetDriver.h` (Private)


#### class `UPlayFabPartyNetDriver`  
`class UPlayFabPartyNetDriver : public UIpNetDriver`  
_L14-44_
- reflection: `UCLASS(Transient, Config=Engine)`
- inherits: `UIpNetDriver`
- L21 _public prototype_ `virtual bool IsAvailable() const override;`
- L22 _public prototype_ `virtual bool InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error) override;`
- L23 _public prototype_ `virtual bool InitListen(FNetworkNotify* InNotify, FURL& LocalURL, bool bReuseAddressAndPort, FString& Error) override;`
- L24 _public prototype_ `virtual ISocketSubsystem* GetSocketSubsystem() override;`
- L25 _public prototype_ `virtual bool IsNetResourceValid() override;`
- L26 _public prototype_ `virtual void TickDispatch(float DeltaTime) override;`
- L27 _public prototype_ `virtual void Shutdown() override;`
- L30 _public prototype_ `bool InitSocket(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL, bool bReuseAddressAndPort, bool bReuseSocket, FString& Error);`
- L35 _protected prototype_ `FPlayFabPartySocket* GetPlayFabSocket();` — Helper to auto-cast and return our socket as a PlayFabParty socket
- L38 _protected prototype_ `FPlayFabPartySocketSubsystem* GetPlayFabSocketSubsystem() const;` — Helper to auto-cast and return our socketsubsystem as a PlayFabParty socketsubsystem
- L43 _protected prototype_ `UWorld* FindWorld() const;` — Get the world this NetDriver belongs to

### `Plugins/Online/Microsoft/PlayFabParty/Source/Private/PlayFabPartySocket.h` (Private)


#### struct `FPlayFabPartyPendingPacket`  
`struct FPlayFabPartyPendingPacket`  
_L27-32_
- L30 _public member_ `TArray<uint8> Data;`
- L31 _public member_ `FPlayFabPartyInternetAddr Sender;`

#### class `FPlayFabPartySocket`  
`class FPlayFabPartySocket : public FSocket`  
_L34-187_
- inherits: `FSocket`
- L38 _public prototype_ `explicit FPlayFabPartySocket(FPlayFabPartySocketSubsystem& SocketSubsystem, IOnlineSubsystem& OnlineSubsystem, const FName SessionName);`
- L39 _public prototype_ `virtual ~FPlayFabPartySocket();`
- L42 _public prototype_ `virtual bool Shutdown(ESocketShutdownMode Mode) override;`
- L43 _public prototype_ `virtual bool Close() override;`
- L44 _public prototype_ `virtual bool Bind(const FInternetAddr& Addr) override;`
- L45 _public prototype_ `virtual bool Connect(const FInternetAddr& Addr) override;`
- L46 _public prototype_ `virtual bool Listen(int32 MaxBacklog) override;`
- L47 _public prototype_ `virtual bool WaitForPendingConnection(bool& bHasPendingConnection, const FTimespan& WaitTime) override;`
- L48 _public prototype_ `virtual bool HasPendingData(uint32& PendingDataSize) override;`
- L49 _public prototype_ `virtual FSocket* Accept(const FString& InSocketDescription) override;`
- L50 _public prototype_ `virtual FSocket* Accept(FInternetAddr& OutAddr, const FString& InSocketDescription) override;`
- L51 _public prototype_ `virtual bool SendTo(const uint8* Data, int32 Count, int32& BytesSent, const FInternetAddr& Destination) override;`
- L52 _public prototype_ `virtual bool Send(const uint8* Data, int32 Count, int32& BytesSent) override;`
- L53 _public prototype_ `virtual bool RecvFrom(uint8* Data, int32 BufferSize, int32& BytesRead, FInternetAddr& Source, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None) override;`
- L54 _public prototype_ `virtual bool Recv(uint8* Data, int32 BufferSize, int32& BytesRead, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None) override;`
- L55 _public prototype_ `virtual bool Wait(ESocketWaitConditions::Type Condition, FTimespan WaitTime) override;`
- L56 _public prototype_ `virtual ESocketConnectionState GetConnectionState() override;`
- L57 _public prototype_ `virtual void GetAddress(FInternetAddr& OutAddr) override;`
- L58 _public prototype_ `virtual bool GetPeerAddress(FInternetAddr& OutAddr) override;`
- L59 _public prototype_ `virtual bool SetNonBlocking(bool bIsNonBlocking = true) override;`
- L60 _public prototype_ `virtual bool SetBroadcast(bool bAllowBroadcast = true) override;`
- L61 _public prototype_ `virtual bool SetNoDelay(bool bIsNoDelay = true) override;`
- L62 _public prototype_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress) override;`
- L63 _public prototype_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) override;`
- L64 _public prototype_ `virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress) override;`
- L65 _public prototype_ `virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) override;`
- L66 _public prototype_ `virtual bool SetMulticastLoopback(bool bLoopback) override;`
- L67 _public prototype_ `virtual bool SetMulticastTtl(uint8 TimeToLive) override;`
- L68 _public prototype_ `virtual bool SetMulticastInterface(const FInternetAddr& InterfaceAddress) override;`
- L69 _public prototype_ `virtual bool SetReuseAddr(bool bAllowReuse = true) override;`
- L70 _public prototype_ `virtual bool SetLinger(bool bShouldLinger = true, int32 Timeout = 0) override;`
- L71 _public prototype_ `virtual bool SetRecvErr(bool bUseErrorQueue = true) override;`
- L72 _public prototype_ `virtual bool SetSendBufferSize(int32 Size, int32& NewSize) override;`
- L73 _public prototype_ `virtual bool SetReceiveBufferSize(int32 Size, int32& NewSize) override;`
- L74 _public prototype_ `virtual int32 GetPortNo() override;`
- L77 _public prototype_ `void TickDispatch(float DeltaTime);`
- L80 _public prototype_ `uint64 GetContext() const;` — Get the socket context used for mapping PlayFab async events to this socket
- L83 _public prototype_ `bool IsServer() const;` — True if we were started in listen mode, or false if we a client
- L86 _public prototype_ `bool IsNetworkConnected() const;` — True if we are currently fully connected to a network, false otherwise
- L88 _public prototype_ `bool HasAuthenticated() const;` — True if we have authenticated with the network, false otherwise
- L90 _public prototype_ `bool IsEndpointConnected() const;` — True if we have successfully created our endpoint, false otherwise
- L93 _public prototype_ `bool AuthenticateWithNetwork(const FString& NetworkInvitation);` — Authenticate our local user with the network with the provided invitation id
- L95 _public prototype_ `bool CreateLocalEndPoint();` — Create our local endpoint so we can send and receive messages
- L97 _public prototype_ `bool CreateInvitation();` — Attempt to create a new invitation for all members of our session
- L100 _public prototype_ `void HandleConnectToNetworkComplete();` — Handle updating state now that we've connected to the network
- L102 _public prototype_ `void HandleLocalUserAuthenticationComplete();` — Handle updating state now that we've connected to the network
- L104 _public prototype_ `void HandleCreateLocalEndpointComplete();` — Handle updating state now that we've created our local endpoint
- L106 _public prototype_ `void HandleEndpointMessageReceived(FPlayFabPartyPendingPacket&& Message);` — Handle queuing a packet to be read
- L108 _public prototype_ `void HandleCreateInvitationCompleted(Party::PartyInvitation* Invitation, const bool bWasSuccessful);` — Handle writing our new invitation to the session
- L110 _public prototype_ `void HandleGetEntityIdsFromXboxLiveUserIdsCompleted(const bool bWasSuccessful);` — Handle checking if we have entity ids for all of our players and creating our invitation if so
- L113 _public prototype_ `void HandleAuthorizationFailure();` — handle auth failure. If we have already retried once, close the socket.
- L116 _protected prototype_ `Party::PartyLocalUser* GetLocalUser();`
- L118 _protected prototype_ `bool SetNetworkAddress(const FInternetAddr& Addr);`
- L120 _protected prototype_ `bool Connect_Internal();`
- L122 _protected prototype_ `void HandleCreateSessionComplete(FName SessionName, bool bWasSuccessful);`
- L123 _protected prototype_ `void HandleSessionCustomDataChanged(FName SessionName, const FOnlineSessionSettings& SessionSettings);`
- L124 _protected prototype_ `void HandleSessionParticipantJoined(FName SessionName, const FUniqueNetId& UniqueId);`
- L125 _protected prototype_ `void HandleSessionParticipantLeft(FName SessionName, const FUniqueNetId& UniqueId, EOnSessionParticipantLeftReason LeaveReason);`
- L127 _protected prototype_ `bool CloseImpl();`
- L131 _protected member_ `FPlayFabPartySocketSubsystem& SocketSubsystem;` — Reference to our subsystem
- L133 _protected member_ `TWeakPtr<IOnlineSession, ESPMode::ThreadSafe> WeakSessionInterface;` — Weak reference to the online subsystem we're mapped to's session interface
- L135 _protected member_ `FName BoundSessionName;` — What SessionName should we be using from the OSS?
- L137 _protected member_ `uint64 SocketContext = 0;` — Unique ID to refer to this socket by
- L140 _protected member_ `FDelegateHandle CreateSessionCompleteHandle;` — Handle to our OSS CreateSession binding
- L142 _protected member_ `FDelegateHandle SessionCustomDataChangedHandle;` — Handle to our OSS SessionCustomDataChanged binding
- L144 _protected member_ `FDelegateHandle SessionParticipantJoinedHandle;` — Handle to our OSS SessionParticipantJoined binding
- L146 _protected member_ `FDelegateHandle SessionParticipantLeftHandle;` — Handle to our OSS SessionParticipantLeft binding
- L149 _protected member_ `TSharedPtr<FPlayFabPartyInternetAddr> NetworkAddress;` — Address of network be belong to (if one is set)
- L152 _protected member_ `bool bIsServer = false;` — Are we the server?
- L154 _protected member_ `Party::PartyInvitation* PartyInvitation = nullptr;` — The current party invitation (only set on server)
- L156 _protected member_ `TArray<uint64> SessionMembers;` — The XUIDs of the members of our party (except host) (only set on server)
- L159 _protected member_ `Party::PartyNetwork* PartyNetwork = nullptr;` — Network instance of the network we belong to (if we are connected to one)
- L161 _protected member_ `bool bIsNetworkConnected = false;` — Have we successfully connected to the network?
- L164 _protected member_ `TOptional<FString> PendingNetworkInvitation;` — String to use to authenticate with the network when we are fully connected
- L166 _protected member_ `bool bIsLocalUserAuthenticated = false;` — Have we successfully authenticated with the network?
- L169 _protected member_ `Party::PartyLocalEndpoint* PartyLocalEndpoint = nullptr;` — Our local endpoint of the network we belong to (if we are connected to one)
- L171 _protected member_ `bool bIsEndpointConnected = false;` — Has our endpoint successfully joined the network?
- L174 _protected member_ `bool bExpectingLeaveNetworkComplete = false;` — If the previous socket still leaving playfab network, mark this as true, then connect when leave network complete
- L176 _protected member_ `float TimeToWaitForLeaveNetworkComplete = 0.0f;` — If leave network complete event never get notified, timeout after this duration
- L178 _protected member_ `TOptional<ESocketErrors> SocketConnectError;`
- L181 _protected member_ `TQueue<TUniquePtr<FPlayFabPartyPendingPacket>, EQueueMode::Spsc> PacketQueue;` — Received packets that have not been processed yet
- L184 _protected member_ `bool bExpectingNewInvitationData = false;` — If failed to authenticate local user in client, it could be client hasn't get the updated session invitation data, will retry it after receiving it
- L186 _protected member_ `float TimeToWaitForNewInvitationData;` — If custom session data changed event never get notified, timeout after this duration

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Party`

### `Plugins/Online/Microsoft/PlayFabParty/Source/Private/PlayFabPartySocketSubsystem.h` (Private)


#### class `FPlayFabPartySocketSubsystem`  
`class FPlayFabPartySocketSubsystem : public ISocketSubsystem`  
_L17-77_
- inherits: `ISocketSubsystem`
- L20 _public prototype_ `FPlayFabPartySocketSubsystem();`
- L21 _public prototype_ `virtual ~FPlayFabPartySocketSubsystem();`
- L24 _public prototype_ `virtual bool Init(FString& Error) override;`
- L25 _public prototype_ `virtual void Shutdown() override;`
- L26 _public prototype_ `virtual FSocket* CreateSocket(const FName& SocketType, const FString& SocketDescription, const FName& ProtocolName) override;`
- L27 _public prototype_ `virtual void DestroySocket(FSocket* Socket) override;`
- L28 _public prototype_ `virtual FAddressInfoResult GetAddressInfo(const TCHAR* HostName, const TCHAR* ServiceName = nullptr, EAddressInfoFlags QueryFlags = EAddressInfoFlags::Default, const FName ProtocolTypeName = NAME_None, ESocketType SocketType = ESocketType::SOCKTYPE_Unknown) override;`
- L29 _public prototype_ `virtual TSharedPtr<FInternetAddr> GetAddressFromString(const FString& InAddress) override;`
- L30 _public prototype_ `virtual bool RequiresChatDataBeSeparate() override;`
- L31 _public prototype_ `virtual bool RequiresEncryptedPackets() override;`
- L32 _public prototype_ `virtual bool GetHostName(FString& HostName) override;`
- L33 _public prototype_ `virtual TSharedRef<FInternetAddr> CreateInternetAddr() override;`
- L34 _public prototype_ `virtual bool HasNetworkDevice() override;`
- L35 _public prototype_ `virtual const TCHAR* GetSocketAPIName() const override;`
- L36 _public prototype_ `virtual ESocketErrors GetLastErrorCode() override;`
- L37 _public prototype_ `virtual ESocketErrors TranslateErrorCode(int32 Code) override;`
- L38 _public prototype_ `virtual bool IsSocketWaitSupported() const override;`
- L42 _public prototype_ `bool IsPlayFabPartyInitialized() const;` — Is the PlayFabParty initialized
- L44 _public prototype_ `bool IsPlayFabPartyReady() const;` — Is the PlayFabParty ready for use
- L47 _public prototype_ `TSharedPtr<FSocket> CreatePlayFabSocket(IOnlineSubsystem& OnlineSubsystem, const FName SessionName, bool bReuseSocket);` — Create a PlayFabParty socket
- L50 _public prototype_ `uint64 GenerateSocketContext(FPlayFabPartySocket* Socket);` — Generate a new socket context and map it to the provided socket
- L52 _public prototype_ `FPlayFabPartySocket* GetSocketFromContext(const uint64 Context);` — Get the socket that maps to a provided context
- L54 _public prototype_ `void ReleaseSocketContext(const uint64 Context);` — Release the mapping of the provided context to the socket it was mapped to
- L58 _public prototype_ `TSharedPtr<FPlayFabPartyManager, ESPMode::ThreadSafe> GetPlayFabPartyManager() const;` — Get the PlayFabParty manager (only available if it is ready)
- L63 _protected prototype_ `void SetLastSocketError(const ESocketErrors NewSocketError);` — Set the last socket error that occurred
- L67 _protected member_ `TAtomic<uint64> SocketContextGenerator;` — Generator for creating contexts for sockets
- L70 _protected member_ `TSharedPtr<FPlayFabPartyManager, ESPMode::ThreadSafe> PlayFabPartyManager;` — Our PlayFabParty Manager Object Instance
- L73 _protected member_ `ESocketErrors LastSocketError = ESocketErrors::SE_NO_ERROR;` — The last error we received
- L76 _protected member_ `TSortedMap<uint64, FPlayFabPartySocket*> ContextToSocketMap;` — Map to translate socket contexts into sockets from callbacks

#### Free symbols / members of external scopes

- L12 _macro_ `#define PLAYFABPARTY_SOCKETSUBSYSTEM TEXT("PlayFabParty")`

### `Plugins/Online/Microsoft/PlayFabParty/Source/Public/PlayFabInterface.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `bool HaveEntityIdForXuid(const uint64 Xuid);` — Do we have a cached Entity ID for the provided Xuid?
- L10 _prototype_ `const char* GetEntityIdForXuid(const uint64 Xuid);` — Get the cached Entity ID for the provided Xuid. Asserts if we do not have a value cached!
- L12 _prototype_ `const char* GetEntityTokenForXuid(const uint64 Xuid);` — Get the cached Entity Token for the provided Xuid if any.
