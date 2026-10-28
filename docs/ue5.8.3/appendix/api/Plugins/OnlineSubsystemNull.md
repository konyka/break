# Plugins / OnlineSubsystemNull

- module root: `Plugins/Online/OnlineSubsystemNull/Source`
- headers: 17; symbols: 364
- symbol kinds: class=18, function=41, macro=6, member=64, prototype=208, struct=3, typedef=24
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Json, OnlineBase, OnlineSubsystem, Sockets
- PublicDependencyModuleNames: OnlineSubsystemUtils

### `Plugins/Online/OnlineSubsystemNull/Source/Private/NboSerializerNull.h` (Private)


#### class `FNboSerializeToBufferNull`  
`class FNboSerializeToBufferNull : public FNboSerializeToBufferOSS`  
_L11-46_
- inherits: `FNboSerializeToBufferOSS`
- desc: Serializes data in network byte order form into a buffer
- L15 _public function_ `FNboSerializeToBufferNull() : FNboSerializeToBufferOSS(512)` — Default constructor zeros num bytes
- L21 _public function_ `FNboSerializeToBufferNull(uint32 Size) : FNboSerializeToBufferOSS(Size)` — Constructor specifying the size to use

#### class `FNboSerializeFromBufferNull`  
`class FNboSerializeFromBufferNull : public FNboSerializeFromBufferOSS`  
_L51-83_
- inherits: `FNboSerializeFromBufferOSS`
- desc: Class used to write data into packets for sending via system link
- L57 _public function_ `FNboSerializeFromBufferNull(uint8* Packet,int32 Length) : FNboSerializeFromBufferOSS(Packet,Length)` — Initializes the buffer, size, and zeros the read offset

#### Free symbols / members of external scopes

- L29 _function_ `friend inline FNboSerializeToBufferNull& operator<<(FNboSerializeToBufferNull& Ar, const FOnlineSessionInfoNull& SessionInfo)` — Adds Null session info to the buffer
- L41 _function_ `friend inline FNboSerializeToBufferNull& operator<<(FNboSerializeToBufferNull& Ar, const FUniqueNetIdNull& UniqueId)` — Adds Null Unique Id to the buffer
- L65 _function_ `friend inline FNboSerializeFromBufferNull& operator>>(FNboSerializeFromBufferNull& Ar, FOnlineSessionInfoNull& SessionInfo)` — Reads Null session info from the buffer
- L78 _function_ `friend inline FNboSerializeFromBufferNull& operator>>(FNboSerializeFromBufferNull& Ar, FUniqueNetIdNull& UniqueId)` — Reads Null Unique Id from the buffer

### `Plugins/Online/OnlineSubsystemNull/Source/Private/OnlineAchievementsInterfaceNull.h` (Private)


#### class `FOnlineAchievementsNull`  
`class FOnlineAchievementsNull : public IOnlineAchievements`  
_L11-125_
- inherits: `IOnlineAchievements`
- desc: IOnlineAchievements - Interface class for acheivements
- L83 _private member_ `class FOnlineSubsystemNull* NullSubsystem;` — Reference to the owning subsystem
- L86 _private function_ `FOnlineAchievementsNull()` — hide the default constructor, we need a reference to our OSS
- L89 _private member_ `TUniqueNetIdMap<TArray<FOnlineAchievement>> PlayerAchievements;` — Mapping of players to their achievements
- L92 _private member_ `TMap<FString, FOnlineAchievementDesc> AchievementDescriptions;` — Cached achievement descriptions for an Id
- L95 _private member_ `TArray<FOnlineAchievementNull> Achievements;` — Cached achievements (not player-specific)
- L98 _private prototype_ `bool ReadAchievementsFromConfig();` — Initializes achievements from config. Returns true if there is at least one achievement
- L107 _public prototype_ `FOnlineAchievementsNull(class FOnlineSubsystemNull* InSubsystem);` — Constructor @param InSubsystem - A reference to the owning subsystem
- L112 _public prototype_ `virtual ~FOnlineAchievementsNull()= default;` — Default destructor
- L115 _public prototype_ `virtual void WriteAchievements(const FUniqueNetId& PlayerId, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& Delegate = FOnAchievementsWrittenDelegate()) override;`
- L116 _public prototype_ `virtual void QueryAchievements(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate()) override;`
- L117 _public prototype_ `virtual void QueryAchievementDescriptions( const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate() ) override;`
- L118 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievement(const FUniqueNetId& PlayerId, const FString& AchievementId, FOnlineAchievement& OutAchievement) override;`
- L119 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievements(const FUniqueNetId& PlayerId, TArray<FOnlineAchievement> & OutAchievements) override;`
- L120 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievementDescription(const FString& AchievementId, FOnlineAchievementDesc& OutAchievementDesc) override;`
- L122 _public prototype_ `virtual bool ResetAchievements( const FUniqueNetId& PlayerId ) override;`

#### struct `FOnlineAchievementsNull::FOnlineAchievementNull`  
`struct FOnlineAchievementNull : public FOnlineAchievement, public FOnlineAchievementDesc`  
_L16-18_
- inherits: `FOnlineAchievement,FOnlineAchievementDesc`
- desc: Structure describing a Null achievement

#### struct `FOnlineAchievementsNull::NullAchievementsConfig`  
`struct NullAchievementsConfig`  
_L23-80_
- desc: A helper class for configuring achievements in ini
- L29 _public function_ `NullAchievementsConfig() : IniName(GEngineIni) , SectionName(TEXT("OnlineSubsystemNull"))` — Create a config using the default values: IniName - GEngineIni
- L36 _public function_ `FString GetKey(const FString& KeyName)` — Returns empty string if couldn't read
- L46 _public function_ `bool ReadAchievements(TArray<FOnlineAchievementNull> & OutArray)`
- L77 _public member_ `FString IniName;` — Ini file name to find the config values
- L79 _public member_ `FString SectionName;` — Section name for Null

### `Plugins/Online/OnlineSubsystemNull/Source/Private/OnlineAsyncTaskManagerNull.h` (Private)


#### class `FOnlineAsyncTaskManagerNull`  
`class FOnlineAsyncTaskManagerNull : public FOnlineAsyncTaskManager`  
_L10-28_
- inherits: `FOnlineAsyncTaskManager`
- desc: Null version of the async task manager to register the various Null callbacks with the engine
- L15 _protected member_ `class FOnlineSubsystemNull* NullSubsystem;` — Cached reference to the main online subsystem
- L19 _public function_ `FOnlineAsyncTaskManagerNull(class FOnlineSubsystemNull* InOnlineSubsystem) : NullSubsystem(InOnlineSubsystem)`
- L24 _public prototype_ `~FOnlineAsyncTaskManagerNull() = default;`
- L27 _public prototype_ `virtual void OnlineTick() override;` — FOnlineAsyncTaskManager

### `Plugins/Online/OnlineSubsystemNull/Source/Private/OnlineExternalUINull.h` (Private)


#### class `FOnlineExternalUINull`  
`class FOnlineExternalUINull : public IOnlineExternalUI`  
_L16-51_
- inherits: `IOnlineExternalUI`
- desc: Null implementation to allow testing
- L24 _public prototype_ `FOnlineExternalUINull(FOnlineSubsystemNull* InSubsystem);` — Constructor @param InSubsystem The owner of this external UI interface.
- L29 _public prototype_ `virtual ~FOnlineExternalUINull();` — Destructor.
- L32 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;` — IOnlineExternalUI
- L33 _public prototype_ `virtual bool ShowAccountCreationUI(const int ControllerIndex, const FOnAccountCreationUIClosedDelegate& Delegate = FOnAccountCreationUIClosedDelegate()) override;`
- L34 _public prototype_ `virtual bool ShowFriendsUI(int32 LocalUserNum) override;`
- L35 _public prototype_ `virtual bool ShowInviteUI(int32 LocalUserNum, FName SessionName = NAME_GameSession) override;`
- L36 _public prototype_ `virtual bool ShowAchievementsUI(int32 LocalUserNum) override;`
- L37 _public prototype_ `virtual bool ShowLeaderboardUI(const FString& LeaderboardName) override;`
- L38 _public prototype_ `virtual bool ShowWebURL(const FString& Url, const FShowWebUrlParams& ShowParams, const FOnShowWebUrlClosedDelegate& Delegate = FOnShowWebUrlClosedDelegate()) override;`
- L39 _public prototype_ `virtual bool CloseWebURL() override;`
- L40 _public prototype_ `virtual bool ShowProfileUI(const FUniqueNetId& Requestor, const FUniqueNetId& Requestee, const FOnProfileUIClosedDelegate& Delegate = FOnProfileUIClosedDelegate()) override;`
- L41 _public prototype_ `virtual bool ShowAccountUpgradeUI(const FUniqueNetId& UniqueId) override;`
- L42 _public prototype_ `virtual bool ShowStoreUI(int32 LocalUserNum, const FShowStoreParams& ShowParams, const FOnShowStoreUIClosedDelegate& Delegate = FOnShowStoreUIClosedDelegate()) override;`
- L43 _public prototype_ `virtual bool ShowSendMessageUI(int32 LocalUserNum, const FShowSendMessageParams& ShowParams, const FOnShowSendMessageUIClosedDelegate& Delegate = FOnShowSendMessageUIClosedDelegate()) override;`
- L48 _private member_ `FOnlineSubsystemNull *NullSubsystem;` — Reference to the owning subsystem
- L50 _private prototype_ `void OnIdentityLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error, FOnLoginUIClosedDelegate Delegate);`

#### Free symbols / members of external scopes

- L53 _typedef_ `typedef TSharedPtr<FOnlineExternalUINull, ESPMode::ThreadSafe> FOnlineExternalUINullPtr;`

### `Plugins/Online/OnlineSubsystemNull/Source/Private/OnlineIdentityNull.h` (Private)


#### class `FUserOnlineAccountNull`  
`class FUserOnlineAccountNull : public FUserOnlineAccount`  
_L13-47_
- inherits: `FUserOnlineAccount`
- desc: Info associated with an user account generated by this online service
- L21 _public function_ `virtual FUniqueNetIdRef GetUserId() const override`
- L22 _public function_ `virtual FString GetRealName() const override`
- L23 _public function_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override`
- L24 _public prototype_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L25 _public prototype_ `virtual bool SetUserAttribute(const FString& AttrName, const FString& AttrValue) override;`
- L29 _public function_ `virtual FString GetAccessToken() const override`
- L30 _public prototype_ `virtual bool GetAuthAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L34 _public function_ `FUserOnlineAccountNull(const FString& InUserId=TEXT("")) : UserIdPtr(FUniqueNetIdNull::Create(InUserId))`
- L38 _public prototype_ `virtual ~FUserOnlineAccountNull() = default;`
- L41 _public member_ `FUniqueNetIdRef UserIdPtr;` — User Id represented as a FUniqueNetId
- L44 _public member_ `TMap<FString, FString> AdditionalAuthData;` — Additional key/value pair data related to auth
- L46 _public member_ `TMap<FString, FString> UserAttributes;` — Additional key/value pair data related to user attribution

#### class `FOnlineIdentityNull`  
`class FOnlineIdentityNull : public IOnlineIdentity`  
_L52-111_
- inherits: `IOnlineIdentity`
- desc: Null service implementation of the online identity interface
- L58 _public prototype_ `virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;`
- L59 _public prototype_ `virtual bool Logout(int32 LocalUserNum) override;`
- L60 _public prototype_ `virtual bool AutoLogin(int32 LocalUserNum) override;`
- L61 _public prototype_ `virtual TSharedPtr<FUserOnlineAccount> GetUserAccount(const FUniqueNetId& UserId) const override;`
- L62 _public prototype_ `virtual TArray<TSharedPtr<FUserOnlineAccount> > GetAllUserAccounts() const override;`
- L63 _public prototype_ `virtual FUniqueNetIdPtr GetUniquePlayerId(int32 LocalUserNum) const override;`
- L64 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(uint8* Bytes, int32 Size) override;`
- L65 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(const FString& Str) override;`
- L66 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(int32 LocalUserNum) const override;`
- L67 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(const FUniqueNetId& UserId) const override;`
- L68 _public prototype_ `virtual FString GetPlayerNickname(int32 LocalUserNum) const override;`
- L69 _public prototype_ `virtual FString GetPlayerNickname(const FUniqueNetId& UserId) const override;`
- L70 _public prototype_ `virtual FString GetAuthToken(int32 LocalUserNum) const override;`
- L71 _public prototype_ `virtual void RevokeAuthToken(const FUniqueNetId& UserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate) override;`
- L72 _public prototype_ `virtual void GetUserPrivilege(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate, EShowPrivilegeResolveUI ShowResolveUI=EShowPrivilegeResolveUI::Default) override;`
- L73 _public prototype_ `virtual FPlatformUserId GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& UniqueNetId) const override;`
- L74 _public prototype_ `virtual FString GetAuthType() const override;`
- L83 _public prototype_ `FOnlineIdentityNull(FOnlineSubsystemNull* InSubsystem);` — Constructor @param InSubsystem online subsystem being used
- L88 _public prototype_ `virtual ~FOnlineIdentityNull();` — Destructor
- L91 _public prototype_ `bool LoginInternal(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials, const FOnLoginCompleteDelegate& InCompletionDelegate);` — Login and call arbitrary callback instead of registered one
- L94 _public prototype_ `FString GenerateRandomUserId(int32 LocalUserNum);` — Creates a unique id for a user, may be stable based on config/command line
- L101 _private prototype_ `FOnlineIdentityNull() = delete;` — Should use the initialization constructor instead
- L104 _private member_ `FOnlineSubsystemNull* NullSubsystem;` — Cached pointer to owning subsystem
- L107 _private member_ `TMap<int32, FUniqueNetIdPtr> UserIds;` — Ids mapped to locally registered users
- L110 _private member_ `TUniqueNetIdMap<TSharedRef<FUserOnlineAccountNull>> UserAccounts;` — Ids mapped to locally registered users

#### Free symbols / members of external scopes

- L113 _typedef_ `typedef TSharedPtr<FOnlineIdentityNull, ESPMode::ThreadSafe> FOnlineIdentityNullPtr;`

### `Plugins/Online/OnlineSubsystemNull/Source/Private/OnlineLeaderboardInterfaceNull.h` (Private)


#### class `FOnlineLeaderboardsNull`  
`class FOnlineLeaderboardsNull : public IOnlineLeaderboards`  
_L13-83_
- inherits: `IOnlineLeaderboards`
- desc: Interface definition for the online services leaderboard services
- L43 _private member_ `class FOnlineSubsystemNull* NullSubsystem;` — Reference to the main Null subsystem
- L46 _private member_ `TMap<FString, FLeaderboardNull> Leaderboards;` — Leaderboards maintained by the subsystem
- L48 _private function_ `FOnlineLeaderboardsNull() : NullSubsystem(NULL)`
- L61 _private prototype_ `FLeaderboardNull* FindOrCreateLeaderboard(const FString& LeaderboardName, ELeaderboardSort::Type SortMethod, ELeaderboardFormat::Type DisplayFormat);` — Creates a Null leaderboard If the leaderboard already exists, the leaderboard data will still be retrieved @param LeaderboardName name of leaderboard to create @param SortMethod method the leaderboard scores will be sorted, ignored if leaderboard exists @param DisplayFormat type of data the leaderboard represents, ignored if leaderboard exists
- L72 _public prototype_ `virtual ~FOnlineLeaderboardsNull() = default;`
- L75 _public prototype_ `virtual bool ReadLeaderboards(const TArray< FUniqueNetIdRef >& Players, FOnlineLeaderboardReadRef& ReadObject) override;` — IOnlineLeaderboards
- L76 _public prototype_ `virtual bool ReadLeaderboardsForFriends(int32 LocalUserNum, FOnlineLeaderboardReadRef& ReadObject) override;`
- L77 _public prototype_ `virtual bool ReadLeaderboardsAroundRank(int32 Rank, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) override;`
- L78 _public prototype_ `virtual bool ReadLeaderboardsAroundUser(FUniqueNetIdRef Player, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) override;`
- L79 _public prototype_ `virtual void FreeStats(FOnlineLeaderboardRead& ReadObject) override;`
- L80 _public prototype_ `virtual bool WriteLeaderboards(const FName& SessionName, const FUniqueNetId& Player, FOnlineLeaderboardWrite& WriteObject) override;`
- L81 _public prototype_ `virtual bool FlushLeaderboards(const FName& SessionName) override;`
- L82 _public prototype_ `virtual bool WriteOnlinePlayerRatings(const FName& SessionName, int32 LeaderboardId, const TArray<FOnlinePlayerScore>& PlayerScores) override;`

#### struct `FOnlineLeaderboardsNull::FLeaderboardNull`  
`struct FLeaderboardNull : public FOnlineLeaderboardRead`  
_L18-40_
- inherits: `FOnlineLeaderboardRead`
- desc: Internal representation of a leadboard
- L26 _public function_ `FOnlineStatsRow* FindOrCreatePlayerRecord(const FUniqueNetId& UserId)` — Retrieve a single record from the leaderboard for a given user @param UserId user id to retrieve a record for @return the requested user row or NULL if not found

#### Free symbols / members of external scopes

- L85 _typedef_ `typedef TSharedPtr<FOnlineLeaderboardsNull, ESPMode::ThreadSafe> FOnlineLeaderboardsNullPtr;`

### `Plugins/Online/OnlineSubsystemNull/Source/Private/OnlineMessageSanitizerNull.h` (Private)


#### class `FMessageSanitizerNull`  
`class FMessageSanitizerNull : public IMessageSanitizer`  
_L11-31_
- inherits: `IMessageSanitizer`
- desc: Implements a degenerate/dummy interface chat message sanitization system for testing
- L17 _public prototype_ `virtual void SanitizeDisplayName(const FString& DisplayName, const FOnMessageProcessed& CompletionDelegate) override;` — IMessageSanitizer
- L18 _public prototype_ `virtual void SanitizeDisplayNames(const TArray<FString>& DisplayNames, const FOnMessageArrayProcessed& CompletionDelegate) override;`
- L19 _public prototype_ `virtual void QueryBlockedUser(int32 LocalUserNum, const FString& FromUserIdStr, const FString& FromPlatform, const FOnQueryUserBlockedResponse& InCompletionDelegate) override;`
- L20 _public prototype_ `virtual void ResetBlockedUserCache() override;`
- L23 _public prototype_ `FMessageSanitizerNull();`
- L24 _public prototype_ `virtual ~FMessageSanitizerNull();`
- L27 _private member_ `int32 RequestId;`
- L29 _private prototype_ `void PerformSanitize(const FString& RawString, FString& OutCleanString) const;`
- L30 _private member_ `TMap<int32, FTSTicker::FDelegateHandle> RequestIdHandleMap;`

### `Plugins/Online/OnlineSubsystemNull/Source/Private/OnlinePurchaseInterfaceNull.h` (Private)


#### class `FOnlinePurchaseNull`  
`class FOnlinePurchaseNull : public IOnlinePurchase , public TSharedFromThis<FOnlinePurchaseNull, ESPMode::ThreadSafe>`  
_L12-52_
- inherits: `IOnlinePurchase,TSharedFromThis<FOnlinePurchaseNull,ESPMode::ThreadSafe>`
- L17 _public prototype_ `FOnlinePurchaseNull(FOnlineSubsystemNull& InNullSubsystem);`
- L18 _public prototype_ `virtual ~FOnlinePurchaseNull();`
- L20 _public prototype_ `void Tick();`
- L24 _public prototype_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId) override;`
- L25 _public prototype_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId, FOnlineError& Error) override;`
- L26 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseCheckoutComplete& Delegate) override;`
- L27 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseReceiptlessCheckoutComplete& Delegate) override;`
- L28 _public prototype_ `virtual void FinalizePurchase(const FUniqueNetId& UserId, const FString& ReceiptId) override;`
- L29 _public prototype_ `virtual void RedeemCode(const FUniqueNetId& UserId, const FRedeemCodeRequest& RedeemCodeRequest, const FOnPurchaseRedeemCodeComplete& Delegate) override;`
- L30 _public prototype_ `virtual void QueryReceipts(const FUniqueNetId& UserId, bool bRestoreReceipts, const FOnQueryReceiptsComplete& Delegate) override;`
- L31 _public prototype_ `virtual void GetReceipts(const FUniqueNetId& UserId, TArray<FPurchaseReceipt>& OutReceipts) const override;`
- L32 _public prototype_ `virtual void FinalizeReceiptValidationInfo(const FUniqueNetId& UserId, FString& InReceiptValidationInfo, const FOnFinalizeReceiptValidationInfoComplete& Delegate) override;`
- L37 _public prototype_ `void CheckoutSuccessfully(const FUniqueNetIdNull& UserId, FOnPurchaseReceiptlessCheckoutComplete Delegate);`
- L44 _public member_ `TMap<FUniqueNetIdNull, TArray<FPurchaseReceipt> > UserFakeReceipts;` — Cached receipts information per user
- L47 _public member_ `TOptional<FOnPurchaseCheckoutComplete> PendingPurchaseDelegate;` — Do we have a purchase currently in progress?
- L49 _public member_ `TOptional<double> PendingPurchaseFailTime;`
- L51 _public member_ `FDelegateHandle PendingPurchaseHandle;`

#### Free symbols / members of external scopes

- L54 _typedef_ `using FOnlinePurchaseNullPtr = TSharedPtr<FOnlinePurchaseNull, ESPMode::ThreadSafe>;`
- L55 _typedef_ `using FOnlinePurchaseNullRef = TSharedRef<FOnlinePurchaseNull, ESPMode::ThreadSafe>;`

### `Plugins/Online/OnlineSubsystemNull/Source/Private/OnlineSessionInterfaceNull.h` (Private)


#### class `FOnlineSessionNull`  
`class FOnlineSessionNull : public IOnlineSession`  
_L18-322_
- inherits: `IOnlineSession`
- desc: Interface definition for the online services session services Session services are defined as anything related managing a session and its state within a platform service
- L23 _private member_ `class FOnlineSubsystemNull* NullSubsystem;` — Reference to the main Null subsystem
- L26 _private member_ `FLANSession LANSessionManager;` — Handles advertising sessions over LAN and client searches
- L29 _private function_ `FOnlineSessionNull() : NullSubsystem(NULL), CurrentSessionSearch(NULL)` — Hidden on purpose
- L39 _private prototype_ `void TickLanTasks(float DeltaTime);` — Ticks any lan beacon background tasks @param DeltaTime the time since the last tick
- L46 _private prototype_ `bool NeedsToAdvertise();` — Checks whether there are any sessions that need to be advertised (over LAN) @return true if there is at least one
- L53 _private prototype_ `bool NeedsToAdvertise( FNamedOnlineSession& Session );` — Determines whether this particular session should be advertised (over LAN) @return true if yes
- L60 _private prototype_ `bool IsSessionJoinable( const FNamedOnlineSession& Session) const;` — Determines whether this particular session is joinable. @return true if yes
- L67 _private prototype_ `uint32 UpdateLANStatus();` — Updates the status of LAN session (creates it if needed, shuts down if not) @return ONLINE_SUCCESS if everything went successful, an error code otherwise
- L78 _private prototype_ `uint32 JoinLANSession(int32 PlayerNum, class FNamedOnlineSession* Session, const class FOnlineSession* SearchSession);` — Join a LAN session @param PlayerNum local index of the user initiating the request @param Session newly allocated session with join information @param SearchSession the desired session to join @return ONLINE_SUCCESS if successful, an error code otherwise
- L85 _private prototype_ `uint32 FindLANSession();` — Builds a LAN search query and broadcasts it @return ONLINE_SUCCESS if successful, an error code otherwise
- L92 _private prototype_ `uint32 FinalizeLANSearch();` — Finishes searching over LAN and returns to hosting (if needed) @return ONLINE_SUCCESS if successful, an error code otherwise
- L101 _private prototype_ `void AppendSessionToPacket(class FNboSerializeToBufferNull& Packet, class FOnlineSession* Session);` — Adds the game session data to the packet that is sent by the host in response to a server query @param Packet the writer object that will encode the data @param Session the session to add to the packet
- L110 _private prototype_ `void AppendSessionSettingsToPacket(class FNboSerializeToBufferNull& Packet, FOnlineSessionSettings* SessionSettings);` — Adds the game settings data to the packet that is sent by the host in response to a server query @param Packet the writer object that will encode the data @param SessionSettings the session settings to add to the packet
- L119 _private prototype_ `void ReadSessionFromPacket(class FNboSerializeFromBufferNull& Packet, class FOnlineSession* Session);` — Reads the settings data from the packet and applies it to the specified object @param Packet the reader object that will read the data @param SessionSettings the session settings to copy the data to
- L128 _private prototype_ `void ReadSettingsFromPacket(class FNboSerializeFromBufferNull& Packet, FOnlineSessionSettings& SessionSettings);` — Reads the settings data from the packet and applies it to the specified object @param Packet the reader object that will read the data @param SessionSettings the session settings to copy the data to
- L137 _private prototype_ `void OnValidQueryPacketReceived(uint8* PacketData, int32 PacketLength, uint64 ClientNonce);` — Delegate triggered when the LAN beacon has detected a valid client request has been received @param PacketData packet data sent by the requesting client with header information removed @param PacketLength length of the packet not including header size @param ClientNonce the nonce returned by the client to return with the server packet
- L145 _private prototype_ `void OnValidResponsePacketReceived(uint8* PacketData, int32 PacketLength);` — Delegate triggered when the LAN beacon has detected a valid host response to a client request has been received @param PacketData packet data sent by the requesting client with header information removed @param PacketLength length of the packet not including header size
- L150 _private prototype_ `void OnLANSearchTimeout();` — Delegate triggered when the LAN beacon has finished searching (some time after last received host packet)
- L155 _private prototype_ `static void SetPortFromNetDriver(const FOnlineSubsystemNull& Subsystem, const TSharedPtr<FOnlineSessionInfo>& SessionInfo);` — Attempt to set the host port in the session info based on the actual port the netdriver is using.
- L160 _private prototype_ `bool IsHost(const FNamedOnlineSession& Session) const;` — Returns true if the session owner is also the host.
- L168 _private member_ `TArray<FNamedOnlineSession> Sessions;` — Current session settings
- L171 _private member_ `TSharedPtr<FOnlineSessionSearch> CurrentSessionSearch;` — Current search object
- L174 _private member_ `double SessionSearchStartInSeconds;` — Current search start time.
- L176 _private function_ `FOnlineSessionNull(class FOnlineSubsystemNull* InSubsystem) : NullSubsystem(InSubsystem), CurrentSessionSearch(NULL), SessionSearchStartInSeconds(0)`
- L185 _private prototype_ `void Tick(float DeltaTime);` — Session tick for various background tasks
- L188 _private function_ `class FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSessionSettings& SessionSettings) override` — IOnlineSession
- L194 _private function_ `class FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSession& Session) override`
- L203 _private prototype_ `void CheckPendingSessionInvite();` — Parse the command line for invite/join information at launch
- L210 _private prototype_ `void RegisterVoice(const FUniqueNetId& PlayerId);` — Registers and updates voice data for the given player id @param PlayerId player to register with the voice subsystem
- L217 _private prototype_ `void UnregisterVoice(const FUniqueNetId& PlayerId);` — Unregisters a given player id from the voice subsystem @param PlayerId player to unregister with the voice subsystem
- L224 _private prototype_ `void RegisterLocalPlayers(class FNamedOnlineSession* Session);` — Registers all local players with the current session @param Session the session that they are registering in
- L228 _public prototype_ `virtual ~FOnlineSessionNull() = default;`
- L230 _public prototype_ `virtual FUniqueNetIdPtr CreateSessionIdFromString(const FString& SessionIdStr) override;`
- L232 _public function_ `FNamedOnlineSession* GetNamedSession(FName SessionName) override`
- L245 _public function_ `virtual void RemoveNamedSession(FName SessionName) override`
- L258 _public function_ `virtual EOnlineSessionState::Type GetSessionState(FName SessionName) const override`
- L272 _public function_ `virtual bool HasPresenceSession() override`
- L287 _public prototype_ `virtual bool CreateSession(int32 HostingPlayerNum, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;` — IOnlineSession
- L288 _public prototype_ `virtual bool CreateSession(const FUniqueNetId& HostingPlayerId, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;`
- L289 _public prototype_ `virtual bool StartSession(FName SessionName) override;`
- L290 _public prototype_ `virtual bool UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings, bool bShouldRefreshOnlineData = true) override;`
- L291 _public prototype_ `virtual bool EndSession(FName SessionName) override;`
- L292 _public prototype_ `virtual bool DestroySession(FName SessionName, const FOnDestroySessionCompleteDelegate& CompletionDelegate = FOnDestroySessionCompleteDelegate()) override;`
- L293 _public prototype_ `virtual bool IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId) override;`
- L294 _public prototype_ `virtual bool StartMatchmaking(const TArray< FUniqueNetIdRef >& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L295 _public prototype_ `virtual bool CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName) override;`
- L296 _public prototype_ `virtual bool CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, FName SessionName) override;`
- L297 _public prototype_ `virtual bool FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L298 _public prototype_ `virtual bool FindSessions(const FUniqueNetId& SearchingPlayerId, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L299 _public prototype_ `virtual bool FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId, const FUniqueNetId& FriendId, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate) override;`
- L300 _public prototype_ `virtual bool CancelFindSessions() override;`
- L301 _public prototype_ `virtual bool PingSearchResults(const FOnlineSessionSearchResult& SearchResult) override;`
- L302 _public prototype_ `virtual bool JoinSession(int32 PlayerNum, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;`
- L303 _public prototype_ `virtual bool JoinSession(const FUniqueNetId& PlayerId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;`
- L304 _public prototype_ `virtual bool FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend) override;`
- L305 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend) override;`
- L306 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& FriendList) override;`
- L307 _public prototype_ `virtual bool SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend) override;`
- L308 _public prototype_ `virtual bool SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName, const FUniqueNetId& Friend) override;`
- L309 _public prototype_ `virtual bool SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) override;`
- L310 _public prototype_ `virtual bool SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) override;`
- L311 _public prototype_ `virtual bool GetResolvedConnectString(FName SessionName, FString& ConnectInfo, FName PortType) override;`
- L312 _public prototype_ `virtual bool GetResolvedConnectString(const FOnlineSessionSearchResult& SearchResult, FName PortType, FString& ConnectInfo) override;`
- L313 _public prototype_ `virtual FOnlineSessionSettings* GetSessionSettings(FName SessionName) override;`
- L314 _public prototype_ `virtual bool RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited) override;`
- L315 _public prototype_ `virtual bool RegisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players, bool bWasInvited = false) override;`
- L316 _public prototype_ `virtual bool UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId) override;`
- L317 _public prototype_ `virtual bool UnregisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players) override;`
- L318 _public prototype_ `virtual void RegisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnRegisterLocalPlayerCompleteDelegate& Delegate) override;`
- L319 _public prototype_ `virtual void UnregisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnUnregisterLocalPlayerCompleteDelegate& Delegate) override;`
- L320 _public prototype_ `virtual int32 GetNumSessions() override;`
- L321 _public prototype_ `virtual void DumpSessionState() override;`

#### Free symbols / members of external scopes

- L324 _typedef_ `typedef TSharedPtr<FOnlineSessionNull, ESPMode::ThreadSafe> FOnlineSessionNullPtr;`

### `Plugins/Online/OnlineSubsystemNull/Source/Private/OnlineStoreV2InterfaceNull.h` (Private)


#### class `FOnlineStoreV2Null`  
`class FOnlineStoreV2Null : public IOnlineStoreV2, public TSharedFromThis<FOnlineStoreV2Null, ESPMode::ThreadSafe>`  
_L14-37_
- inherits: `IOnlineStoreV2,TSharedFromThis<FOnlineStoreV2Null,ESPMode::ThreadSafe>`
- desc: Implementation for online store via Null interface
- L17 _public prototype_ `FOnlineStoreV2Null(FOnlineSubsystemNull& InNullSubsystem);`
- L18 _public prototype_ `virtual ~FOnlineStoreV2Null() = default;`
- L21 _public prototype_ `virtual void QueryCategories(const FUniqueNetId& UserId, const FOnQueryOnlineStoreCategoriesComplete& Delegate) override;`
- L22 _public prototype_ `virtual void GetCategories(TArray<FOnlineStoreCategory>& OutCategories) const override;`
- L23 _public prototype_ `virtual void QueryOffersByFilter(const FUniqueNetId& UserId, const FOnlineStoreFilter& Filter, const FOnQueryOnlineStoreOffersComplete& Delegate) override;`
- L24 _public prototype_ `virtual void QueryOffersById(const FUniqueNetId& UserId, const TArray<FUniqueOfferId>& OfferIds, const FOnQueryOnlineStoreOffersComplete& Delegate) override;`
- L25 _public prototype_ `virtual void GetOffers(TArray<FOnlineStoreOfferRef>& OutOffers) const override;`
- L26 _public prototype_ `virtual TSharedPtr<FOnlineStoreOffer> GetOffer(const FUniqueOfferId& OfferId) const override;`
- L33 _public member_ `TMap<FUniqueOfferId, FOnlineStoreOfferRef> AvailableOffers;`
- L36 _private prototype_ `void CreateFakeOffer(const FString& Id, const FString& Title, const FString& Description, int32 Price);`

#### Free symbols / members of external scopes

- L39 _typedef_ `using FOnlineStoreNullPtr = TSharedPtr<FOnlineStoreV2Null, ESPMode::ThreadSafe>;`
- L40 _typedef_ `using FOnlineStoreNullRef = TSharedRef<FOnlineStoreV2Null, ESPMode::ThreadSafe>;`

### `Plugins/Online/OnlineSubsystemNull/Source/Private/OnlineSubsystemNullPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define INVALID_INDEX -1`
- L10 _macro_ `#define NULL_URL_PREFIX TEXT("Null.")` — URL Prefix when using Null socket connection
- L14 _macro_ `#define ONLINE_LOG_PREFIX TEXT("NULL: ")`

### `Plugins/Online/OnlineSubsystemNull/Source/Private/OnlineSubsystemNullTypes.h` (Private)


#### class `FOnlineSessionInfoNull`  
`class FOnlineSessionInfoNull : public FOnlineSessionInfo`  
_L17-80_
- inherits: `FOnlineSessionInfo`
- desc: Implementation of session information
- L20 _private prototype_ `FOnlineSessionInfoNull(const FOnlineSessionInfoNull& Src) = delete;` — Hidden on purpose
- L21 _private prototype_ `FOnlineSessionInfoNull& operator=(const FOnlineSessionInfoNull& Src) = delete;`
- L32 _private prototype_ `void Init(const FOnlineSubsystemNull& Subsystem);` — Initialize a Null session info with the address of this machine and an id for the session
- L35 _private member_ `TSharedPtr<class FInternetAddr> HostAddr;` — The ip & port that the host is listening on (valid for LAN/GameServer)
- L37 _private member_ `FUniqueNetIdNullRef SessionId;` — Unique Id for this session
- L41 _public prototype_ `virtual ~FOnlineSessionInfoNull() = default;`
- L43 _public function_ `bool operator==(const FOnlineSessionInfoNull& Other) const`
- L48 _public function_ `virtual const uint8* GetBytes() const override`
- L53 _public function_ `virtual int32 GetSize() const override`
- L58 _public function_ `virtual bool IsValid() const override`
- L64 _public function_ `virtual FString ToString() const override`
- L69 _public function_ `virtual FString ToDebugString() const override`
- L76 _public function_ `virtual const FUniqueNetId& GetSessionId() const override`

#### Free symbols / members of external scopes

- L12 _prototype_ `TEMP_UNIQUENETIDSTRING_SUBCLASS(FUniqueNetIdNull, NULL_SUBSYSTEM);` — from OnlineSubsystemTypes.h

### `Plugins/Online/OnlineSubsystemNull/Source/Private/OnlineTitleFileNull.h` (Private)


#### class `FTitleFileNullAsyncLoadLocalDevFile`  
`class FTitleFileNullAsyncLoadLocalDevFile : public FNonAbandonableTask`  
_L10-39_
- inherits: `FNonAbandonableTask`
- L15 _public member_ `TArray<uint8> FileData;` — File data loaded for the async read
- L17 _public member_ `FThreadSafeCounter64 BytesRead;` — Amount of data read from the file to be owned/referenced by the game thread
- L19 _public member_ `const FString LocalDevFileName;` — The original name of the file being read
- L21 _public member_ `const FString LocalDevFilePath;` — The full path file being read
- L23 _public member_ `FString LocalHashStr;` — Hash Calculated after file is loaded
- L25 _public function_ `FTitleFileNullAsyncLoadLocalDevFile(const FString& FileName, const FString& FullPath) : LocalDevFileName(FileName), LocalDevFilePath(FullPath)`
- L32 _public prototype_ `void DoWork();`
- L34 _public function_ `FORCEINLINE TStatId GetStatId() const`

#### class `FOnlineTitleFileNull`  
`class FOnlineTitleFileNull : public IOnlineTitleFile, public TSharedFromThis<FOnlineTitleFileNull, ESPMode::ThreadSafe>`  
_L41-77_
- inherits: `IOnlineTitleFile,TSharedFromThis<FOnlineTitleFileNull,ESPMode::ThreadSafe>`
- L45 _public prototype_ `FOnlineTitleFileNull();`
- L46 _public prototype_ `virtual ~FOnlineTitleFileNull();`
- L49 _public prototype_ `virtual bool GetFileContents(const FString& FileName, TArray<uint8>& FileContents) override;`
- L50 _public prototype_ `virtual bool ClearFiles() override;`
- L51 _public prototype_ `virtual bool ClearFile(const FString& FileName) override;`
- L52 _public prototype_ `virtual void DeleteCachedFiles(bool bSkipEnumerated) override;`
- L53 _public prototype_ `virtual bool EnumerateFiles(const FPagedQuery& Page) override;`
- L54 _public prototype_ `virtual void GetFileList(TArray<FCloudFileHeader>& OutFiles) override;`
- L55 _public prototype_ `virtual bool ReadFile(const FString& FileName) override;`
- L57 _public prototype_ `void Tick(float DeltaTime);`
- L60 _protected member_ `FString LocalPath;`
- L61 _protected member_ `TArray<FCloudFileHeader> FileHeaders;`
- L62 _protected member_ `TArray<FCloudFile> Files;`
- L63 _protected member_ `bool bShouldDeleteLocalPath;`
- L66 _protected member_ `TArray<FAsyncTask<FTitleFileNullAsyncLoadLocalDevFile>* > AsyncLocalDevReads;` — Holds the outstanding task for hitch free loading of local Dev files.
- L70 _protected prototype_ `FCloudFileHeader* GetCloudFileHeader(const FString& FileName);` — these are all copied from OnlineTitleMcp, and maybe could be shared somehow
- L71 _protected prototype_ `FCloudFile* GetCloudFile(const FString& FileName, bool bCreateIfMissing);`
- L73 _protected prototype_ `void FinishReadFileLocalDevFile(FAsyncTask<FTitleFileNullAsyncLoadLocalDevFile>* Task);` — Completes the async operation for the local dev file read. Similar to above but without any cloud connection.
- L76 _protected prototype_ `void InitializeLocalFilesFromPerforceIfNeeded();` — Special handling for "p4://" title file paths

#### Free symbols / members of external scopes

- L79 _typedef_ `using FOnlineTitleFileNullPtr = TSharedPtr<FOnlineTitleFileNull, ESPMode::ThreadSafe>;`

### `Plugins/Online/OnlineSubsystemNull/Source/Private/VoiceInterfaceNull.h` (Private)


#### class `FOnlineVoiceImplNull`  
`class FOnlineVoiceImplNull : public FOnlineVoiceImpl`  
_L7-20_
- inherits: `FOnlineVoiceImpl`
- L14 _public function_ `FOnlineVoiceImplNull(class IOnlineSubsystem* InOnlineSubsystem) : FOnlineVoiceImpl(InOnlineSubsystem)` — Constructor
- L19 _public prototype_ `virtual ~FOnlineVoiceImplNull() override = default;`

#### Free symbols / members of external scopes

- L22 _typedef_ `typedef TSharedPtr<FOnlineVoiceImpl, ESPMode::ThreadSafe> FOnlineVoiceImplPtr;`

### `Plugins/Online/OnlineSubsystemNull/Source/Public/OnlineSubsystemNull.h` (Public)


#### class `FOnlineSubsystemNull`  
`class FOnlineSubsystemNull : public FOnlineSubsystemImpl`  
_L38-178_
- inherits: `FOnlineSubsystemImpl`
- desc: OnlineSubsystemNull - Implementation of the online subsystem for Null services
- L44 _public prototype_ `virtual ~FOnlineSubsystemNull() = default;`
- L48 _public prototype_ `virtual IOnlineSessionPtr GetSessionInterface() const override;`
- L49 _public prototype_ `virtual IOnlineFriendsPtr GetFriendsInterface() const override;`
- L50 _public prototype_ `virtual IOnlinePartyPtr GetPartyInterface() const override;`
- L51 _public prototype_ `virtual IOnlineGroupsPtr GetGroupsInterface() const override;`
- L52 _public prototype_ `virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override;`
- L53 _public prototype_ `virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;`
- L54 _public prototype_ `virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;`
- L55 _public prototype_ `virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;`
- L56 _public prototype_ `virtual IOnlineVoicePtr GetVoiceInterface() const override;`
- L57 _public prototype_ `virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;`
- L58 _public prototype_ `virtual IOnlineTimePtr GetTimeInterface() const override;`
- L59 _public prototype_ `virtual IOnlineIdentityPtr GetIdentityInterface() const override;`
- L60 _public prototype_ `virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;`
- L61 _public prototype_ `virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override;`
- L62 _public prototype_ `virtual IOnlinePurchasePtr GetPurchaseInterface() const override;`
- L63 _public prototype_ `virtual IOnlineEventsPtr GetEventsInterface() const override;`
- L64 _public prototype_ `virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;`
- L65 _public prototype_ `virtual IOnlineSharingPtr GetSharingInterface() const override;`
- L66 _public prototype_ `virtual IOnlineUserPtr GetUserInterface() const override;`
- L67 _public prototype_ `virtual IOnlineMessagePtr GetMessageInterface() const override;`
- L68 _public prototype_ `virtual IOnlinePresencePtr GetPresenceInterface() const override;`
- L69 _public prototype_ `virtual IOnlineChatPtr GetChatInterface() const override;`
- L70 _public prototype_ `virtual IOnlineStatsPtr GetStatsInterface() const override;`
- L71 _public prototype_ `virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override;`
- L72 _public prototype_ `virtual IOnlineTournamentPtr GetTournamentInterface() const override;`
- L73 _public prototype_ `virtual IMessageSanitizerPtr GetMessageSanitizer(int32 LocalUserNum, FString& OutAuthTypeToExclude) const override;`
- L75 _public prototype_ `virtual bool Init() override;`
- L76 _public prototype_ `virtual bool Shutdown() override;`
- L77 _public prototype_ `virtual FString GetAppId() const override;`
- L78 _public prototype_ `virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L79 _public prototype_ `virtual FText GetOnlineServiceName() const override;`
- L83 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L91 _public function_ `explicit FOnlineSubsystemNull(FName InInstanceName) : FOnlineSubsystemImpl(NULL_SUBSYSTEM, InInstanceName), SessionInterface(nullptr), VoiceInterface(nullptr), bVoiceInterfaceInitialized(false), LeaderboardsInterface(nullptr), IdentityInterface(nullptr), AchievementsInterface(nullptr), StoreV2Interface(nullptr), MessageSanitizerInterface(nullptr), TitleFileInterface(nullptr), OnlineAsyncTaskThreadRunnable(nullptr), OnlineAsyncTaskThread(nullptr)`
- L109 _public member_ `static bool bAutoLoginAtStartup;` — True if it should login the first user at startup like single-user platforms, false to only login when requested
- L112 _public member_ `static bool bSupportExternalUI;` — True if it should support an external UI interface
- L115 _public member_ `static bool bRequireShowLoginUI;` — True if login requires calling ShowLoginUI on the externalUI, depends on SupportExternalUI
- L118 _public member_ `static bool bForceShowLoginUIUserChange;` — True if the user index should change during login UI to emulate a platform user change
- L121 _public member_ `static bool bRequireLoginCredentials;` — True if login should require a user/pass to act like an external service, false to match most platforms and use the default
- L124 _public member_ `static bool bAddUserNumToNullId;` — True if login name should include the local user number, which allows different stable IDs per user num
- L127 _public member_ `static bool bForceStableNullId;` — True if it should use a system-stable null Id for login, same as -StableNullID on command line
- L130 _public member_ `static bool bForceOfflineMode;` — True if it should fail faked network queries and act like an offline system
- L133 _public member_ `static bool bOnlineRequiresSecondLogin;` — True if the first login only counts as local login, a second is required for online access
- L138 _private member_ `FOnlineSessionNullPtr SessionInterface;` — Interface to the session services
- L141 _private member_ `mutable IOnlineVoicePtr VoiceInterface;` — Interface for voice communication
- L144 _private member_ `mutable bool bVoiceInterfaceInitialized;` — Interface for voice communication
- L147 _private member_ `FOnlineLeaderboardsNullPtr LeaderboardsInterface;` — Interface to the leaderboard services
- L150 _private member_ `FOnlineIdentityNullPtr IdentityInterface;` — Interface to the identity registration/auth services
- L153 _private member_ `FOnlineExternalUINullPtr ExternalUIInterface;` — Interface to the identity registration/auth services
- L156 _private member_ `FOnlineAchievementsNullPtr AchievementsInterface;` — Interface for achievements
- L159 _private member_ `FOnlineStoreV2NullPtr StoreV2Interface;` — Interface for store
- L162 _private member_ `FOnlinePurchaseNullPtr PurchaseInterface;` — Interface for purchases
- L165 _private member_ `FMessageSanitizerNullPtr MessageSanitizerInterface;` — Interface for message sanitizing
- L168 _private member_ `FOnlineTitleFileNullPtr TitleFileInterface;` — Interface for title file storage
- L171 _private member_ `class FOnlineAsyncTaskManagerNull* OnlineAsyncTaskThreadRunnable;` — Online async task runnable
- L174 _private member_ `class FRunnableThread* OnlineAsyncTaskThread;` — Online async task thread
- L177 _private member_ `static FThreadSafeCounter TaskCounter;` — task counter, used to generate unique thread names for each task

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEMNULL_API`
- L19 _typedef_ `typedef TSharedPtr<class FOnlineSessionNull, ESPMode::ThreadSafe> FOnlineSessionNullPtr;` — Forward declarations of all interface classes
- L20 _typedef_ `typedef TSharedPtr<class FOnlineProfileNull, ESPMode::ThreadSafe> FOnlineProfileNullPtr;`
- L21 _typedef_ `typedef TSharedPtr<class FOnlineFriendsNull, ESPMode::ThreadSafe> FOnlineFriendsNullPtr;`
- L22 _typedef_ `typedef TSharedPtr<class FOnlineUserCloudNull, ESPMode::ThreadSafe> FOnlineUserCloudNullPtr;`
- L23 _typedef_ `typedef TSharedPtr<class FOnlineLeaderboardsNull, ESPMode::ThreadSafe> FOnlineLeaderboardsNullPtr;`
- L24 _typedef_ `typedef TSharedPtr<class FOnlineExternalUINull, ESPMode::ThreadSafe> FOnlineExternalUINullPtr;`
- L25 _typedef_ `typedef TSharedPtr<class FOnlineIdentityNull, ESPMode::ThreadSafe> FOnlineIdentityNullPtr;`
- L26 _typedef_ `typedef TSharedPtr<class FOnlineAchievementsNull, ESPMode::ThreadSafe> FOnlineAchievementsNullPtr;`
- L27 _typedef_ `typedef TSharedPtr<class FOnlineStoreV2Null, ESPMode::ThreadSafe> FOnlineStoreV2NullPtr;`
- L28 _typedef_ `typedef TSharedPtr<class FOnlinePurchaseNull, ESPMode::ThreadSafe> FOnlinePurchaseNullPtr;`
- L29 _typedef_ `typedef TSharedPtr<class FMessageSanitizerNull, ESPMode::ThreadSafe> FMessageSanitizerNullPtr;`
- L30 _typedef_ `typedef TSharedPtr<class FOnlineTitleFileNull, ESPMode::ThreadSafe> FOnlineTitleFileNullPtr;`
- L32 _typedef_ `typedef TSharedPtr<class FOnlineVoiceImpl, ESPMode::ThreadSafe> FOnlineVoiceImplPtr;`
- L180 _typedef_ `typedef TSharedPtr<FOnlineSubsystemNull, ESPMode::ThreadSafe> FOnlineSubsystemNullPtr;`

### `Plugins/Online/OnlineSubsystemNull/Source/Public/OnlineSubsystemNullModule.h` (Public)


#### class `FOnlineSubsystemNullModule`  
`class FOnlineSubsystemNullModule : public IModuleInterface`  
_L12-40_
- inherits: `IModuleInterface`
- desc: Online subsystem module class  (Null Implementation) Code related to the loading of the Null module
- L17 _private member_ `class FOnlineFactoryNull* NullFactory;` — Class responsible for creating instance(s) of the subsystem
- L21 _public function_ `FOnlineSubsystemNullModule() : NullFactory(NULL)`
- L25 _public prototype_ `virtual ~FOnlineSubsystemNullModule() = default;`
- L29 _public prototype_ `virtual void StartupModule() override;`
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L31 _public function_ `virtual bool SupportsDynamicReloading() override`
- L36 _public function_ `virtual bool SupportsAutomaticShutdown() override`

### `Plugins/Online/OnlineSubsystemNull/Source/Public/OnlineSubsystemNullPackage.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define PACKAGE_SCOPE public`
- L14 _macro_ `#define PACKAGE_SCOPE protected`
