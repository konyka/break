# Plugins / OnlineSubsystemIOS

- module root: `Plugins/Online/IOS/OnlineSubsystemIOS/Source`
- headers: 21; symbols: 462
- symbol kinds: class=18, delegate=1, function=44, macro=2, member=92, prototype=288, struct=2, typedef=15
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, HTTP, IOSPlatformFeatures, MarketplaceKit, OnlineSubsystem, Sockets

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/OnlineAchievementsInterfaceIOS.h` (Private)


#### class `FOnlineAchievementsIOS`  
`class FOnlineAchievementsIOS : public IOnlineAchievements`  
_L10-54_
- inherits: `IOnlineAchievements`
- desc: IOnlineAchievements - Interface class for acheivements
- L15 _private member_ `class FOnlineSubsystemIOS* IOSSubsystem;` — Reference to the main GameCenter subsystem
- L18 _private function_ `FOnlineAchievementsIOS()` — hide the default constructor, we need a reference to our OSS
- L21 _private member_ `TArray< FOnlineAchievement > Achievements;` — IOS only supports loading achievements for local player. This is where they are cached.
- L24 _private member_ `TMap< FString, FOnlineAchievementDesc > AchievementDescriptions;` — Cached achievement descriptions for an Id
- L30 _public prototype_ `virtual void WriteAchievements(const FUniqueNetId& PlayerId, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& Delegate = FOnAchievementsWrittenDelegate()) override;`
- L31 _public prototype_ `virtual void QueryAchievements(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate()) override;`
- L32 _public prototype_ `virtual void QueryAchievementDescriptions( const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate() ) override;`
- L33 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievement(const FUniqueNetId& PlayerId, const FString& AchievementId, FOnlineAchievement& OutAchievement) override;`
- L34 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievements(const FUniqueNetId& PlayerId, TArray<FOnlineAchievement> & OutAchievements) override;`
- L35 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievementDescription(const FString& AchievementId, FOnlineAchievementDesc& OutAchievementDesc) override;`
- L37 _public prototype_ `virtual bool ResetAchievements( const FUniqueNetId& PlayerId ) override;`
- L47 _public prototype_ `FOnlineAchievementsIOS( class FOnlineSubsystemIOS* InSubsystem );` — Constructor @param InSubsystem - A reference to the owning subsystem
- L53 _public function_ `virtual ~FOnlineAchievementsIOS()` — Default destructor

#### Free symbols / members of external scopes

- L56 _typedef_ `typedef TSharedPtr<FOnlineAchievementsIOS, ESPMode::ThreadSafe> FOnlineAchievementsIOSPtr;`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/OnlineAppStoreUtils.h` (Private)


#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQueryAppBundleIdResponse, NSDictionary* );` — Delegate fires when a query for the app bundle id metadata completes @param ResponseDict dictionary containing the metadata response
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FOnQueryAppBundleIdResponse, NSDictionary* );` — Delegate fires when a query for the app bundle id metadata completes @param ResponseDict dictionary containing the metadata response

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/OnlineExternalUIInterfaceIOS.h` (Private)


#### class `FOnlineExternalUIIOS`  
`class FOnlineExternalUIIOS : public IOnlineExternalUI`  
_L10-39_
- inherits: `IOnlineExternalUI`
- L19 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;`
- L20 _public function_ `virtual bool ShowAccountCreationUI(const int ControllerIndex, const FOnAccountCreationUIClosedDelegate& Delegate = FOnAccountCreationUIClosedDelegate()) override`
- L21 _public prototype_ `virtual bool ShowFriendsUI(int32 LocalUserNum) override;`
- L22 _public prototype_ `virtual bool ShowInviteUI(int32 LocalUserNum, FName SessionName = NAME_GameSession) override;`
- L23 _public prototype_ `virtual bool ShowAchievementsUI(int32 LocalUserNum) override;`
- L24 _public prototype_ `virtual bool ShowLeaderboardUI(const FString& LeaderboardName) override;`
- L25 _public prototype_ `virtual bool ShowWebURL(const FString& Url, const FShowWebUrlParams& ShowParams, const FOnShowWebUrlClosedDelegate& Delegate = FOnShowWebUrlClosedDelegate()) override;`
- L26 _public prototype_ `virtual bool CloseWebURL() override;`
- L27 _public prototype_ `virtual bool ShowProfileUI(const FUniqueNetId& Requestor, const FUniqueNetId& Requestee, const FOnProfileUIClosedDelegate& Delegate = FOnProfileUIClosedDelegate()) override;`
- L28 _public prototype_ `virtual bool ShowAccountUpgradeUI(const FUniqueNetId& UniqueId) override;`
- L29 _public prototype_ `virtual bool ShowStoreUI(int32 LocalUserNum, const FShowStoreParams& ShowParams, const FOnShowStoreUIClosedDelegate& Delegate = FOnShowStoreUIClosedDelegate()) override;`
- L30 _public prototype_ `virtual bool ShowSendMessageUI(int32 LocalUserNum, const FShowSendMessageParams& ShowParams, const FOnShowSendMessageUIClosedDelegate& Delegate = FOnShowSendMessageUIClosedDelegate()) override;`
- L34 _private member_ `FOnlineSubsystemIOS* Subsystem;`
- L35 _private member_ `FDelegateHandle CompleteDelegate;`
- L36 _private member_ `FOnLoginUIClosedDelegate CopiedDelegate;`
- L38 _private prototype_ `void OnLoginComplete(int ControllerIndex, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& ErrorString);`

#### Free symbols / members of external scopes

- L41 _typedef_ `typedef TSharedPtr<FOnlineExternalUIIOS, ESPMode::ThreadSafe> FOnlineExternalUIIOSPtr;`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/OnlineFriendsInterfaceIOS.h` (Private)


#### class `FOnlineFriendIOS`  
`class FOnlineFriendIOS : public FOnlineFriend`  
_L16-75_
- inherits: `FOnlineFriend`
- desc: Info associated with an online friend on the ios gamecenter service
- L23 _public prototype_ `virtual FUniqueNetIdRef GetUserId() const override;`
- L24 _public prototype_ `virtual FString GetRealName() const override;`
- L25 _public prototype_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override;`
- L26 _public prototype_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L30 _public prototype_ `virtual EInviteStatus::Type GetInviteStatus() const override;`
- L31 _public prototype_ `virtual const FOnlineUserPresence& GetPresence() const override;`
- L38 _public function_ `FOnlineFriendIOS(const FString& InUserId=TEXT("")) : UserId(FUniqueNetIdIOS::Create(InUserId))` — Init/default constructor
- L46 _public function_ `virtual ~FOnlineFriendIOS()` — Destructor
- L58 _public function_ `inline bool GetAccountData(const FString& Key, FString& OutVal) const` — Get account data attribute @param Key account data entry key @param OutVal [out] value that was found @return true if entry was found
- L70 _public member_ `FUniqueNetIdRef UserId;` — User Id represented as a FUniqueNetId
- L72 _public member_ `TMap<FString, FString> AccountData;` — Any addition account data associated with the friend
- L74 _public member_ `FOnlineUserPresence Presence;` — @temp presence info

#### class `FOnlineFriendsIOS`  
`class FOnlineFriendsIOS : public IOnlineFriends`  
_L77-129_
- inherits: `IOnlineFriends`
- L83 _private member_ `class FOnlineIdentityIOS* IdentityInterface;` — Reference to the main IOS identity
- L86 _private member_ `TArray< TSharedRef<FOnlineFriendIOS> > CachedFriends;` — The collection of game center friends received through the GK callbacks in ReadFriendsList
- L88 _private member_ `FOnlineSubsystemIOS * IOSSubsystem;`
- L94 _public prototype_ `virtual bool ReadFriendsList(int32 LocalUserNum, const FString& ListName, const FOnReadFriendsListComplete& Delegate = FOnReadFriendsListComplete()) override;`
- L95 _public prototype_ `virtual bool DeleteFriendsList(int32 LocalUserNum, const FString& ListName, const FOnDeleteFriendsListComplete& Delegate = FOnDeleteFriendsListComplete()) override;`
- L96 _public prototype_ `virtual bool SendInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnSendInviteComplete& Delegate = FOnSendInviteComplete()) override;`
- L97 _public prototype_ `virtual bool AcceptInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnAcceptInviteComplete& Delegate = FOnAcceptInviteComplete()) override;`
- L98 _public prototype_ `virtual bool RejectInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L99 _public prototype_ `virtual void SetFriendAlias(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FString& Alias, const FOnSetFriendAliasComplete& Delegate = FOnSetFriendAliasComplete()) override;`
- L100 _public prototype_ `virtual void DeleteFriendAlias(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnDeleteFriendAliasComplete& Delegate = FOnDeleteFriendAliasComplete()) override;`
- L101 _public prototype_ `virtual bool DeleteFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L102 _public prototype_ `virtual bool GetFriendsList(int32 LocalUserNum, const FString& ListName, TArray< TSharedRef<FOnlineFriend> >& OutFriends) override;`
- L103 _public prototype_ `virtual TSharedPtr<FOnlineFriend> GetFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L104 _public prototype_ `virtual bool IsFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L105 _public prototype_ `virtual bool QueryRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace) override;`
- L106 _public prototype_ `virtual bool GetRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace, TArray< TSharedRef<FOnlineRecentPlayer> >& OutRecentPlayers) override;`
- L107 _public prototype_ `virtual void DumpRecentPlayers() const override;`
- L108 _public prototype_ `virtual bool BlockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId) override;`
- L109 _public prototype_ `virtual bool UnblockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId) override;`
- L110 _public prototype_ `virtual bool QueryBlockedPlayers(const FUniqueNetId& UserId) override;`
- L111 _public prototype_ `virtual bool GetBlockedPlayers(const FUniqueNetId& UserId, TArray< TSharedRef<FOnlineBlockedPlayer> >& OutBlockedPlayers) override;`
- L112 _public prototype_ `virtual void DumpBlockedPlayers() const override;`
- L119 _public function_ `virtual ~FOnlineFriendsIOS()` — Destructor

#### Free symbols / members of external scopes

- L131 _typedef_ `typedef TSharedPtr<FOnlineFriendsIOS, ESPMode::ThreadSafe> FOnlineFriendsIOSPtr;`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/OnlineIdentityInterfaceIOS.h` (Private)


#### class `FOnlineIdentityIOS`  
`class FOnlineIdentityIOS : public IOnlineIdentity`  
_L14-75_
- inherits: `IOnlineIdentity`
- L19 _private member_ `FUniqueNetIdIOSPtr UniqueNetId;` — UID for this identity
- L20 _private member_ `FOnlineSubsystemIOS* Subsystem;`
- L23 _private member_ `bool bLoginInProgress = false;`
- L25 _private prototype_ `FOnlineIdentityIOS();`
- L27 _private typedef_ `using FGamCenterEvent = TValueOrError<FUniqueNetIdIOSPtr, FString>;`
- L29 _private prototype_ `static FGamCenterEvent GetCurrentGameCenterEvent(NSError* Error);`
- L30 _private prototype_ `void HandleGamCenterEvent(const FGamCenterEvent& LoginResult, bool bTriggerLoginComplete);`
- L42 _public prototype_ `virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;`
- L43 _public prototype_ `virtual bool Logout(int32 LocalUserNum) override;`
- L44 _public prototype_ `virtual bool AutoLogin(int32 LocalUserNum) override;`
- L45 _public prototype_ `virtual TSharedPtr<FUserOnlineAccount> GetUserAccount(const FUniqueNetId& UserId) const override;`
- L46 _public prototype_ `virtual TArray<TSharedPtr<FUserOnlineAccount> > GetAllUserAccounts() const override;`
- L47 _public prototype_ `virtual FUniqueNetIdPtr GetUniquePlayerId(int32 LocalUserNum) const override;`
- L48 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(uint8* Bytes, int32 Size) override;`
- L49 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(const FString& Str) override;`
- L50 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(int32 LocalUserNum) const override;`
- L51 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(const FUniqueNetId& UserId) const override;`
- L52 _public prototype_ `virtual FString GetPlayerNickname(int32 LocalUserNum) const override;`
- L53 _public prototype_ `virtual FString GetPlayerNickname(const FUniqueNetId& UserId) const override;`
- L54 _public prototype_ `virtual FString GetAuthToken(int32 LocalUserNum) const override;`
- L55 _public prototype_ `virtual void RevokeAuthToken(const FUniqueNetId& UserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate) override;`
- L56 _public prototype_ `virtual void GetUserPrivilege(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate, EShowPrivilegeResolveUI ShowResolveUI=EShowPrivilegeResolveUI::Default) override;`
- L57 _public prototype_ `virtual FPlatformUserId GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& UniqueNetId) const override;`
- L58 _public prototype_ `virtual FString GetAuthType() const override;`
- L66 _public function_ `virtual ~FOnlineIdentityIOS()` — Destructor
- L74 _public prototype_ `GKLocalPlayer* GetLocalGameCenterUser() const;` — Get a reference to the GKLocalPlayer @return - The game center local player

#### Free symbols / members of external scopes

- L78 _typedef_ `typedef TSharedPtr<FOnlineIdentityIOS, ESPMode::ThreadSafe> FOnlineIdentityIOSPtr;`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/OnlineLeaderboardsInterfaceIOS.h` (Private)


#### class `FOnlineLeaderboardsIOS`  
`class FOnlineLeaderboardsIOS : public IOnlineLeaderboards`  
_L11-44_
- inherits: `IOnlineLeaderboards`
- L14 _private member_ `class FOnlineIdentityIOS* IdentityInterface;`
- L16 _private member_ `class FOnlineFriendsIOS* FriendsInterface;`
- L18 _private member_ `NSMutableArray *UnreportedScores;`
- L19 _private member_ `GKPlayer *LeaderboardPlayer;`
- L20 _private member_ `GKLeaderboard *CachedLeaderboard;`
- L21 _private member_ `bool bReadLeaderboardFinished;`
- L23 _private prototype_ `bool ReadLeaderboardCompletionDelegate(NSArray* players, FOnlineLeaderboardReadRef& ReadObject);`
- L31 _public prototype_ `virtual ~FOnlineLeaderboardsIOS();`
- L34 _public prototype_ `virtual bool ReadLeaderboards(const TArray< FUniqueNetIdRef >& Players, FOnlineLeaderboardReadRef& ReadObject) override;`
- L35 _public prototype_ `virtual bool ReadLeaderboardsForFriends(int32 LocalUserNum, FOnlineLeaderboardReadRef& ReadObject) override;`
- L36 _public prototype_ `virtual bool ReadLeaderboardsAroundRank(int32 Rank, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) override;`
- L37 _public prototype_ `virtual bool ReadLeaderboardsAroundUser(FUniqueNetIdRef Player, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) override;`
- L38 _public prototype_ `virtual void FreeStats(FOnlineLeaderboardRead& ReadObject) override;`
- L39 _public prototype_ `virtual bool WriteLeaderboards(const FName& SessionName, const FUniqueNetId& Player, FOnlineLeaderboardWrite& WriteObject) override;`
- L40 _public prototype_ `virtual bool FlushLeaderboards(const FName& SessionName) override;`
- L41 _public prototype_ `virtual bool WriteOnlinePlayerRatings(const FName& SessionName, int32 LeaderboardId, const TArray<FOnlinePlayerScore>& PlayerScores) override;`

#### Free symbols / members of external scopes

- L46 _typedef_ `typedef TSharedPtr<FOnlineLeaderboardsIOS, ESPMode::ThreadSafe> FOnlineLeaderboardsIOSPtr;`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/OnlineSessionInterfaceIOS.h` (Private)


#### class `FOnlineSessionIOS`  
`class FOnlineSessionIOS : public IOnlineSession`  
_L50-176_
- inherits: `IOnlineSession`
- desc: Interface definition for the online services session services Session services are defined as anything related managing a session and its state within a platform service
- L55 _private member_ `class FOnlineSubsystemIOS* IOSSubsystem;` — Reference to the main GameCenter subsystem
- L58 _private prototype_ `FOnlineSessionIOS();` — Hidden on purpose
- L66 _private member_ `TArray<FNamedOnlineSession> Sessions;` — Current session settings
- L69 _private member_ `TMap< FName, FGameCenterSessionDelegate* > GKSessions;`
- L73 _private member_ `TSharedPtr<FOnlineSessionSearch> CurrentSessionSearch;` — Current search object
- L84 _private prototype_ `void Tick(float DeltaTime);` — Session tick for various background tasks
- L88 _private prototype_ `class FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSessionSettings& SessionSettings) override;`
- L90 _private prototype_ `class FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSession& Session) override;`
- L94 _public prototype_ `virtual ~FOnlineSessionIOS();`
- L96 _public prototype_ `virtual FUniqueNetIdPtr CreateSessionIdFromString(const FString& SessionIdStr) override;`
- L98 _public prototype_ `FNamedOnlineSession* GetNamedSession(FName SessionName) override;`
- L100 _public prototype_ `virtual void RemoveNamedSession(FName SessionName) override;`
- L102 _public prototype_ `virtual EOnlineSessionState::Type GetSessionState(FName SessionName) const override;`
- L104 _public prototype_ `virtual bool HasPresenceSession() override;`
- L106 _public prototype_ `virtual bool CreateSession(int32 HostingPlayerNum, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;`
- L108 _public prototype_ `virtual bool CreateSession(const FUniqueNetId& HostingPlayerId, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;`
- L110 _public prototype_ `virtual bool StartSession(FName SessionName) override;`
- L112 _public prototype_ `virtual bool UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings, bool bShouldRefreshOnlineData = false) override;`
- L114 _public prototype_ `virtual bool EndSession(FName SessionName) override;`
- L116 _public prototype_ `virtual bool DestroySession(FName SessionName, const FOnDestroySessionCompleteDelegate& CompletionDelegate = FOnDestroySessionCompleteDelegate()) override;`
- L118 _public prototype_ `virtual bool IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId) override;`
- L120 _public prototype_ `virtual bool StartMatchmaking(const TArray< FUniqueNetIdRef >& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L122 _public prototype_ `virtual bool CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName) override;`
- L124 _public prototype_ `virtual bool CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, FName SessionName) override;`
- L126 _public prototype_ `virtual bool FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L128 _public prototype_ `virtual bool FindSessions(const FUniqueNetId& SearchingPlayerId, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L130 _public prototype_ `virtual bool FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId, const FUniqueNetId& FriendId, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate) override;`
- L132 _public prototype_ `virtual bool CancelFindSessions() override;`
- L134 _public prototype_ `virtual bool PingSearchResults(const FOnlineSessionSearchResult& SearchResult) override;`
- L136 _public prototype_ `virtual bool JoinSession(int32 PlayerNum, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;`
- L138 _public prototype_ `virtual bool JoinSession(const FUniqueNetId& PlayerId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;`
- L140 _public prototype_ `virtual bool FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend) override;`
- L142 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend) override;`
- L144 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& FriendList) override;`
- L146 _public prototype_ `virtual bool SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend) override;`
- L148 _public prototype_ `virtual bool SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName, const FUniqueNetId& Friend) override;`
- L150 _public prototype_ `virtual bool SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) override;`
- L152 _public prototype_ `virtual bool SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) override;`
- L154 _public prototype_ `virtual bool GetResolvedConnectString(FName SessionName, FString& ConnectInfo, FName PortType) override;`
- L156 _public prototype_ `virtual bool GetResolvedConnectString(const class FOnlineSessionSearchResult& SearchResult, FName PortType, FString& ConnectInfo) override;`
- L158 _public prototype_ `virtual FOnlineSessionSettings* GetSessionSettings(FName SessionName) override;`
- L160 _public prototype_ `virtual bool RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited) override;`
- L162 _public prototype_ `virtual bool RegisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players, bool bWasInvited = false) override;`
- L164 _public prototype_ `virtual bool UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId) override;`
- L166 _public prototype_ `virtual bool UnregisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players) override;`
- L168 _public prototype_ `virtual void RegisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnRegisterLocalPlayerCompleteDelegate& Delegate) override;`
- L170 _public prototype_ `virtual void UnregisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnUnregisterLocalPlayerCompleteDelegate& Delegate) override;`
- L172 _public prototype_ `virtual int32 GetNumSessions() override;`
- L174 _public prototype_ `virtual void DumpSessionState() override;`

#### Free symbols / members of external scopes

- L178 _typedef_ `typedef TSharedPtr<FOnlineSessionIOS, ESPMode::ThreadSafe> FOnlineSessionIOSPtr;`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/OnlineSharedCloudInterfaceIOS.h` (Private)


#### class `FSharedContentHandleIOS`  
`class FSharedContentHandleIOS : public FSharedContentHandle`  
_L12-95_
- inherits: `FSharedContentHandle`
- desc: iOS specific implementation of a shared file handle
- L17 _private member_ `const FString SharedContentHandle;` — Holds the handle to the shared content
- L21 _public function_ `FSharedContentHandleIOS() : SharedContentHandle()`
- L31 _public function_ `FSharedContentHandleIOS(const FString& InSharedContentHandle) : SharedContentHandle(InSharedContentHandle)` — Constructs this object with the specified shared content id @param InUniqueNetId the id to set ours to
- L39 _public function_ `bool operator==(const FSharedContentHandleIOS& Other) const` — Comparison operator
- L50 _public function_ `virtual const uint8* GetBytes() const override` — Get the raw byte representation of this shared content handle This data is platform dependent and shouldn't be manipulated directly @return byte array of size GetSize()
- L60 _public function_ `virtual int32 GetSize() const override` — Get the size of this shared content handle @return size in bytes of the id representation
- L70 _public function_ `virtual bool IsValid() const override` — Check the validity of this shared content handle @return true if this is a well formed ID, false otherwise
- L80 _public function_ `virtual FString ToString() const override` — Platform specific conversion to string representation of data @return data in string form
- L91 _public function_ `virtual FString ToDebugString() const override` — Get a human readable representation of this shared content handle Shouldn't be used for anything other than logging/debugging @return handle in string form

#### class `FOnlineSharedCloudInterfaceIOS`  
`class FOnlineSharedCloudInterfaceIOS : public IOnlineSharedCloud`  
_L100-132_
- inherits: `IOnlineSharedCloud`
- desc: Provides the interface for sharing files already on the cloud with other users
- L104 _protected prototype_ `FCloudFile* GetCloudFile(const FString& FileName, bool bCreateIfMissing = false);`
- L105 _protected prototype_ `bool ClearFiles();`
- L106 _protected prototype_ `bool ClearCloudFile(const FString& FileName);`
- L116 _public prototype_ `virtual ~FOnlineSharedCloudInterfaceIOS();`
- L119 _public prototype_ `virtual bool GetSharedFileContents(const FSharedContentHandle& SharedHandle, TArray<uint8>& FileContents) override;` — IOnlineSharedCloud
- L120 _public prototype_ `virtual bool ClearSharedFiles() override;`
- L121 _public prototype_ `virtual bool ClearSharedFile(const FSharedContentHandle& SharedHandle) override;`
- L122 _public prototype_ `virtual bool ReadSharedFile(const FSharedContentHandle& SharedHandle) override;`
- L123 _public prototype_ `virtual bool WriteSharedFile(const FUniqueNetId& UserId, const FString& Filename, TArray<uint8>& FileContents) override;`
- L124 _public prototype_ `virtual void GetDummySharedHandlesForTest(TArray< TSharedRef<FSharedContentHandle> > & OutHandles) override;`
- L128 _private member_ `TArray<struct FCloudFile> CloudFileData;` — File cache
- L131 _private member_ `FCriticalSection CloudDataLock;` — Critical section for thread safe operation on cloud files

#### Free symbols / members of external scopes

- L134 _typedef_ `typedef TSharedPtr<FOnlineSharedCloudInterfaceIOS, ESPMode::ThreadSafe> FOnlineSharedCloudIOSPtr;`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/OnlineSubsystemIOSTypes.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `TEMP_UNIQUENETIDSTRING_SUBCLASS(FUniqueNetIdIOS, IOS_SUBSYSTEM);` — from OnlineSubsystemTypes.h

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/OnlineTurnBasedInterfaceIOS.h` (Private)


#### class `FTurnBasedMatchIOS`  
`class FTurnBasedMatchIOS : public FTurnBasedMatch`  
_L12-85_
- inherits: `FTurnBasedMatch`
- desc: Wrapper for a Game Center Match
- L15 _public prototype_ `FTurnBasedMatchIOS(GKTurnBasedMatch* _Match, NSArray* PlayerArray);`
- L16 _public prototype_ `virtual ~FTurnBasedMatchIOS();`
- L19 _public prototype_ `virtual int32 GetNumberOfPlayers() const override;` — Returns the number of players currently participating in a match
- L23 _public prototype_ `virtual bool GetPlayerDisplayName(int32 PlayerIndex, FString& Name) const override;` — Takes the index of a player PlayerIndex, and sets the name of that player in Name. Return true if the PlayerIndex is valid, false if not.
- L26 _public prototype_ `virtual void ReloadMatchData(FDownloadMatchDataSignature DownloadCallback) override;` — Reloads the custom data for this match.
- L30 _public prototype_ `virtual bool HasMatchData() const override;` — Accessors for the custom data of this match. Custom match data is application specific and can be anything, up to 8k.
- L31 _public prototype_ `virtual bool GetMatchData(TArray<uint8>& OutMatchData) const override;`
- L32 _public prototype_ `virtual void SetMatchData(const TArray<uint8>& NewMatchData, FUploadMatchDataSignature UploadCallback) override;`
- L35 _public prototype_ `virtual FString GetMatchID() const override;` — Returns the GUID of this match as an FString.
- L38 _public prototype_ `virtual int32 GetLocalPlayerIndex() const override;` — Get the index of the local player in the participants array of this match.
- L41 _public prototype_ `virtual int32 GetCurrentPlayerIndex() const override;` — Get the index of the active player in the participants array of this match.
- L44 _public prototype_ `virtual EMPMatchOutcome::Outcome GetMatchOutcomeForPlayer(int32 PlayerIndex) const override;` — Gets the match outcome for a player (win/loss/quit/etc.)
- L47 _public prototype_ `int32 GetPlayerIndexForPlayer(NSString* PlayerID) const;` — Gets the player index in the participants array of the player with PlayerID.
- L50 _public prototype_ `bool IsGKTurnBasedMatch(GKTurnBasedMatch* Comparison) const;` — Returns true if the match stored in this FTurnBasedMatchIOS object is the same as Comparison.
- L54 _public prototype_ `virtual void EndTurnWithMatchData(const TArray<uint8>& MatchData, int32 TurnTimeoutInSeconds, FUploadMatchDataSignature UploadCallback) override;` — Ends the turn for the current player with updated MatchData. TurnTimeoutInSeconds is how long the next player has for their turn, and UploadCallback will be called when the GameCenter call finishes.
- L58 _public prototype_ `virtual void QuitMatch(EMPMatchOutcome::Outcome Outcome, int32 TurnTimeoutInSeconds, FQuitMatchSignature QuitMatchCallback) override;` — Quits this match with the passed in Outcome. TurnTimeoutInSeconds is how long the next player will have (if the player is quitting early and the match isn't over).
- L61 _public function_ `GKTurnBasedMatch* GetGKMatch() const` — Accessors for the GKTurnBasedMatch object.
- L62 _public prototype_ `void SetGKMatch(GKTurnBasedMatch* GKMatch);`
- L65 _public prototype_ `virtual void EndMatch(FEndMatchSignature QuitMatchCallback, EMPMatchOutcome::Outcome LocalPlayerOutcome, EMPMatchOutcome::Outcome OtherPlayersOutcome);` — Ends the match
- L70 _private prototype_ `void QuitMatchInTurn(GKTurnBasedMatchOutcome Outcome, int32 TurnTimeoutInSeconds, FQuitMatchSignature QuitMatchCallback);` — Helper functions for QuitMatch, depending on whether it is the current player's turn or not.
- L71 _private prototype_ `void QuitMatchOutOfTurn(GKTurnBasedMatchOutcome Outcome, FQuitMatchSignature QuitMatchCallback);`
- L74 _private prototype_ `NSArray* GetNextParticipantArray(bool IncludeLocalPlayer) const;` — Gets a list of players, if IncludeLocalPlayer is true, this player will be in the array
- L77 _private prototype_ `GKTurnBasedMatchOutcome GetGKTurnBasedMatchOutcomeFromMatchOutcome(EMPMatchOutcome::Outcome Outcome) const;` — Conversion functions between EMPMatchOutcome::Outcome and GKTurnBasedMatchOutcome enums.
- L78 _private prototype_ `EMPMatchOutcome::Outcome GetMatchOutcomeFromGKTurnBasedMatchOutcome(GKTurnBasedMatchOutcome GKOutcome) const;`
- L81 _private member_ `TArray<FString> PlayerAliasArray;` — The last of active player GUIDs in the match
- L84 _private member_ `GKTurnBasedMatch* Match;` — The Game Center match object

#### class `FOnlineTurnBasedIOS`  
`class FOnlineTurnBasedIOS : public IOnlineTurnBased, public FTurnBasedMatchmakerDelegate, public FTurnBasedEventDelegate`  
_L90-140_
- inherits: `IOnlineTurnBased,FTurnBasedMatchmakerDelegate,FTurnBasedEventDelegate`
- desc: FOnlineTurnBasedIOS - Implementation of turn based multiplayer for IOS
- L93 _public prototype_ `FOnlineTurnBasedIOS();`
- L94 _public prototype_ `virtual ~FOnlineTurnBasedIOS();`
- L96 _public prototype_ `static NSArray* GetPlayerIdentifierArrayForMatch(GKTurnBasedMatch* match);`
- L99 _public prototype_ `virtual void SetMatchmakerDelegate(FTurnBasedMatchmakerDelegatePtr Delegate) override;` — IOnlineTurnBased
- L100 _public prototype_ `virtual void ShowMatchmaker(const FTurnBasedMatchRequest& MatchRequest) override;`
- L102 _public prototype_ `virtual void SetEventDelegate(FTurnBasedEventDelegateWeakPtr Delegate) override;`
- L103 _public prototype_ `virtual FTurnBasedEventDelegateWeakPtr GetEventDelegate() const override;`
- L105 _public prototype_ `virtual void LoadAllMatches(FLoadTurnBasedMatchesSignature MatchesLoadedCallback) override;`
- L106 _public prototype_ `virtual void LoadMatchWithID(FString MatchID, FLoadTurnBasedMatchWithIDSignature MatchesLoadedCallback) override;`
- L108 _public prototype_ `virtual FTurnBasedMatchPtr GetMatchWithID(FString MatchID) const override;`
- L110 _public prototype_ `virtual void RemoveMatch(FTurnBasedMatchRef Match, FRemoveMatchSignature RemoveMatchCallback) override;`
- L113 _public prototype_ `virtual void OnMatchmakerCancelled() override;` — FTurnBasedMatchmakerDelegate
- L114 _public prototype_ `virtual void OnMatchmakerFailed() override;`
- L115 _public prototype_ `virtual void OnMatchFound(FTurnBasedMatchRef Match) override;`
- L118 _public prototype_ `virtual void OnMatchEnded(FString MatchID) override;` — FTurnBasedEventDelegate
- L119 _public prototype_ `virtual void OnMatchReceivedTurnEvent(FString MatchID, bool BecameActive, void* Match) override;`
- L121 _public prototype_ `virtual void RegisterTurnBasedMatchInterfaceObject(UObject* Object);`
- L122 _public function_ `UObject* GetTurnBasedMatchInterfaceObject()`
- L124 _public function_ `virtual int32 GetMatchDataSize()`
- L127 _private member_ `FTurnBasedMatchmakerIOS Matchmaker;`
- L128 _private member_ `FTurnBasedMatchmakerDelegateWeakPtr MatchmakerDelegate;`
- L130 _private member_ `FTurnBasedEventListenerIOS* EventListener;`
- L131 _private member_ `FTurnBasedEventDelegateWeakPtr EventDelegate;`
- L133 _private member_ `TArray<FTurnBasedMatchRef> MatchArray;`
- L135 _private member_ `int32 NumberOfMatchesBeingLoaded;`
- L137 _private member_ `UObject* TurnBasedMatchInterfaceObject;`
- L139 _private member_ `static const int32 MATCH_DATA_SIZE = 1024 * 8 * 4;`

#### Free symbols / members of external scopes

- L142 _typedef_ `typedef TSharedPtr<FOnlineTurnBasedIOS, ESPMode::ThreadSafe> FOnlineTurnBasedIOSPtr;`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/OnlineUserCloudInterfaceIOS.h` (Private)


#### class `FOnlineUserCloudInterfaceIOS`  
`class FOnlineUserCloudInterfaceIOS : public IOnlineUserCloud`  
_L35-165_
- inherits: `IOnlineUserCloud`
- desc: FOnlineUserCloudInterfaceIOS - Implementation of user cloud storage for IOS
- L39 _protected prototype_ `FCloudFile* GetCloudFile(const FString& FileName, bool bCreateIfMissing = false);`
- L40 _protected prototype_ `FCloudFileHeader* GetCloudFileHeader(const FString& FileName, bool bCreateIfMissing = false);`
- L41 _protected prototype_ `bool ClearFiles();`
- L42 _protected prototype_ `bool ClearCloudFile(const FString& FileName);`
- L45 _public function_ `FOnlineUserCloudInterfaceIOS() : SaveSystem(NULL), UpdateDictionary(NULL)`
- L46 _public prototype_ `virtual ~FOnlineUserCloudInterfaceIOS();`
- L49 _public prototype_ `virtual bool GetFileContents(const FUniqueNetId& UserId, const FString& FileName, TArray<uint8>& FileContents) override;` — IOnlineUserCloud
- L50 _public prototype_ `virtual bool ClearFiles(const FUniqueNetId& UserId) override;`
- L51 _public prototype_ `virtual bool ClearFile(const FUniqueNetId& UserId, const FString& FileName) override;`
- L52 _public prototype_ `virtual void EnumerateUserFiles(const FUniqueNetId& UserId) override;`
- L53 _public prototype_ `virtual void GetUserFileList(const FUniqueNetId& UserId, TArray<FCloudFileHeader>& UserFiles) override;`
- L54 _public prototype_ `virtual bool ReadUserFile(const FUniqueNetId& UserId, const FString& FileName) override;`
- L55 _public prototype_ `virtual bool WriteUserFile(const FUniqueNetId& UserId, const FString& FileName, TArray<uint8>& FileContents, bool bCompressBeforeUpload = false) override;`
- L56 _public prototype_ `virtual void CancelWriteUserFile(const FUniqueNetId& UserId, const FString& FileName) override;`
- L57 _public prototype_ `virtual bool DeleteUserFile(const FUniqueNetId& UserId, const FString& FileName, bool bShouldCloudDelete, bool bShouldLocallyDelete) override;`
- L58 _public prototype_ `virtual bool RequestUsageInfo(const FUniqueNetId& UserId) override;`
- L59 _public prototype_ `virtual void DumpCloudState(const FUniqueNetId& UserId) override;`
- L60 _public prototype_ `virtual void DumpCloudFileState(const FUniqueNetId& UserId, const FString& FileName) override;`
- L63 _public prototype_ `void InitCloudSave(bool InIOSAlwaysSyncCloudFiles);` — Initialize Cloud saving
- L66 _private member_ `TArray<struct FCloudFileHeader> CloudMetaData;` — File metadata
- L68 _private member_ `EOnlineAsyncTaskState::Type MetaDataState;` — File metadata query state
- L70 _private member_ `TArray<struct FCloudFile> CloudFileData;` — File cache
- L73 _private member_ `FCriticalSection CloudDataLock;` — Critical section for thread safe operation on cloud files
- L76 _private member_ `FIOSSaveGameSystem* SaveSystem;` — Reference to the iOS file save system
- L79 _private member_ `bool bIOSAlwaysSyncCloudFiles;` — Flag from Settings->iOS: Always read from the iCloud on LoadGame
- L85 _private member_ `NSMutableDictionary* UpdateDictionary;` — Store the iCloud sync status for each save file entris of type (string) filename: (bool) synced with iCloud updated by the silent notifications, if enabled
- L88 _private member_ `FOnEnumerateUserFilesCompleteDelegate OnEnumerateUserCloudFilesCompleteDelegate;` — Delegates to various cloud functionality triggered
- L89 _private member_ `FOnReadUserFileCompleteDelegate OnInitialFetchUserCloudFileCompleteDelegate;`
- L90 _private member_ `FOnWriteUserFileCompleteDelegate OnWriteUserCloudFileCompleteDelegate;`
- L91 _private member_ `FOnReadUserFileCompleteDelegate OnReadUserCloudFileCompleteDelegate;`
- L92 _private member_ `FOnDeleteUserFileCompleteDelegate OnDeleteUserCloudFileCompleteDelegate;`
- L95 _private member_ `FDelegateHandle OnEnumerateUserCloudFilesCompleteDelegateHandle;` — Handles to those delegates
- L96 _private member_ `FDelegateHandle OnWriteUserCloudFileCompleteDelegateHandle;`
- L97 _private member_ `FDelegateHandle OnReadUserCloudFileCompleteDelegateHandle;`
- L98 _private member_ `FDelegateHandle OnDeleteUserCloudFileCompleteDelegateHandle;`
- L101 _private member_ `FUniqueNetIdIOSPtr UniqueNetId;` — Cache the UserId
- L108 _private prototype_ `void OnEnumerateUserFilesComplete(bool bWasSuccessful, const FUniqueNetId& UserId);` — Delegate triggered when all user files have been enumerated @param bWasSuccessful did the operation complete successfully @param UserId user that triggered the operation
- L116 _private prototype_ `void OnInitialFetchUserCloudFileComplete(bool bWasSuccessful, const FUniqueNetId& UserId, const FString& FileName);` — Delegate triggered on the init for each user cloud file read - will overwrite the local files @param bWasSuccessful did the operation complete successfully @param UserId user that triggered the operation @param FileName filename read from cloud
- L124 _private prototype_ `void OnWriteUserCloudFileComplete(bool bWasSuccessful, const FUniqueNetId& UserId, const FString& FileName);` — Delegate triggered for each user cloud file written @param bWasSuccessful did the operation complete successfully @param UserId user that triggered the operation @param FileName filename written to cloud
- L132 _private prototype_ `void OnReadUserCloudFileComplete(bool bWasSuccessful, const FUniqueNetId& UserId, const FString& FileName);` — Delegate triggered for each user cloud file read - will overwrite the local files @param bWasSuccessful did the operation complete successfully @param UserId user that triggered the operation @param FileName filename read from cloud
- L140 _private prototype_ `void OnDeleteUserCloudFileComplete(bool bWasSuccessful, const FUniqueNetId& UserId, const FString& FileName);` — Delegate triggered for each user cloud file deleted @param bWasSuccessful did the operation complete successfully @param UserId user that triggered the operation @param FileName filename deleted from cloud
- L146 _private prototype_ `bool OnWriteUserCloudFileBegin(const FString& FileName);` — Delegate in the iOS file save system Called in SaveGame
- L152 _private prototype_ `bool OnReadUserCloudFileBegin(const FString & FileName);` — Delegate in the iOS file save system Called in ReadGame
- L158 _private prototype_ `void OnDeleteUserCloudFileBegin(const FString& FileName);` — Delegate in the iOS file save system Called in DeleteGame
- L163 _private prototype_ `bool ShouldFetchRecordFromCloud(const FString & FileName);` — Returns true if the record must be fetched from the iCloud

#### Free symbols / members of external scopes

- L167 _typedef_ `typedef TSharedPtr<FOnlineUserCloudInterfaceIOS, ESPMode::ThreadSafe> FOnlineUserCloudIOSPtr;`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/StoreKitSwiftInterop.h` (Private)
_(no declarations extracted)_

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/TurnBasedEventListener.h` (Private)
_(no declarations extracted)_

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/TurnBasedMatchmakerDelegateIOS.h` (Private)
_(no declarations extracted)_

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/TurnBasedMatchmakerIOS.h` (Private)


#### class `FTurnBasedMatchmakerIOS`  
`class FTurnBasedMatchmakerIOS : public FTurnBasedMatchmakerDelegate`  
_L11-32_
- inherits: `FTurnBasedMatchmakerDelegate`
- L14 _public prototype_ `FTurnBasedMatchmakerIOS(FTurnBasedMatchmakerDelegate& _Delegate);`
- L15 _public prototype_ `~FTurnBasedMatchmakerIOS();`
- L17 _public prototype_ `void ShowWithMatchRequest(const FTurnBasedMatchRequest& Request);`
- L19 _public prototype_ `virtual void OnMatchmakerCancelled() override;`
- L20 _public prototype_ `virtual void OnMatchmakerFailed() override;`
- L21 _public prototype_ `virtual void OnMatchFound(FTurnBasedMatchRef Match) override;`
- L24 _private prototype_ `GKMatchRequest* GetGKMatchRequestFromMPMatchRequest(const FTurnBasedMatchRequest& Request) const;`
- L25 _private prototype_ `void DismissMatchmaker();`
- L27 _private member_ `FTurnBasedMatchRequest MatchRequest;`
- L29 _private member_ `GKTurnBasedMatchmakerViewController* MatchmakerViewController;`
- L30 _private member_ `FTurnBasedMatchmakerDelegateIOS* IOSDelegate;`
- L31 _private member_ `FTurnBasedMatchmakerDelegate* Delegate;`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Public/OnlinePurchaseIOS.h` (Public)


#### class `FOnlinePurchaseIOS`  
`class FOnlinePurchaseIOS : public IOnlinePurchase, public TSharedFromThis<FOnlinePurchaseIOS, ESPMode::ThreadSafe>`  
_L19-140_
- inherits: `IOnlinePurchase,TSharedFromThis<FOnlinePurchaseIOS,ESPMode::ThreadSafe>`
- desc: Implementation for online purchase via IOS services
- L28 _public prototype_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId) override;`
- L29 _public prototype_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId, FOnlineError& Error) override;`
- L30 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseCheckoutComplete& Delegate) override;`
- L31 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseReceiptlessCheckoutComplete& Delegate) override;`
- L32 _public prototype_ `virtual void FinalizePurchase(const FUniqueNetId& UserId, const FString& ReceiptId) override;`
- L33 _public prototype_ `virtual void RedeemCode(const FUniqueNetId& UserId, const FRedeemCodeRequest& RedeemCodeRequest, const FOnPurchaseRedeemCodeComplete& Delegate) override;`
- L34 _public prototype_ `virtual void QueryReceipts(const FUniqueNetId& UserId, bool bRestoreReceipts, const FOnQueryReceiptsComplete& Delegate) override;`
- L35 _public prototype_ `virtual void GetReceipts(const FUniqueNetId& UserId, TArray<FPurchaseReceipt>& OutReceipts) const override;`
- L36 _public prototype_ `virtual void FinalizeReceiptValidationInfo(const FUniqueNetId& UserId, FString& InReceiptValidationInfo, const FOnFinalizeReceiptValidationInfoComplete& Delegate) override;`
- L39 _public prototype_ `virtual void RequestExternalPurchaseToken(const FOnRequestExternalPurchaseTokenComplete& Delegate) const override;`
- L50 _public prototype_ `FOnlinePurchaseIOS(class FOnlineSubsystemIOS* InSubsystem);` — Constructor @param InSubsystem IOS subsystem being used
- L55 _public prototype_ `virtual ~FOnlinePurchaseIOS();` — Destructor
- L60 _public prototype_ `void DumpAppReceipt();` — Log App Receipt content
- L65 _public prototype_ `void GetAppReceipt(TFunction<void(const FString&)> OnComplete);` — Asynchronously retrieves the App Store receipt data
- L70 _public prototype_ `void OnUpdatedTransactions(const TArray<FOnlinePurchaseTransactionIOS>& Transactions);` — Method used internally by FStoreKitPurchaseProxy to handle a known transactions. Not meant to be called by user code
- L75 _public prototype_ `void OnRemovedTransactions(const TArray<FOnlinePurchaseTransactionIOS>& Transactions);` — Method used internally by FStoreKitPurchaseProxy to handle finalized transactions. Not meant to be called by user code
- L80 _public prototype_ `void OnQueryReceiptsComplete(bool bSuccess, const TSharedPtr<TArray<FOnlinePurchaseTransactionIOS>>& Transactions);` — Method used internally by FStoreKitPurchaseProxy to notify that transactions were restored. Not meant to be called by user code
- L98 _private prototype_ `static void AddReceiptToCache(TArray<FKnownTransaction>& Cache, const TSharedRef<FPurchaseReceipt>& Receipt, const FOnlinePurchaseTransactionIOS& Transaction);` — Add receipt information for transaction data to intermediate cache avoiding duplicates and return stored receipt
- L103 _private prototype_ `static TSharedRef<FPurchaseReceipt> GenerateFailReceipt(const FPurchaseCheckoutRequest& CheckoutRequest);` — Generate a receipt for a failed purchase
- L108 _private prototype_ `static TSharedRef<FPurchaseReceipt> GenerateOfflineReceipt(const FOnlinePurchaseTransactionIOS& Transaction);` — Generate a receipt for a successful purchase which was received offline
- L113 _private prototype_ `static TSharedRef<FPurchaseReceipt> GenerateReceipt(const FPurchaseCheckoutRequest& CheckoutRequest, const FOnlinePurchaseTransactionIOS& Transaction);` — Generate a final receipt for the purchase currently in progress
- L117 _private member_ `TRetainedObjCInstance<FStoreKitPurchaseProxy*> StoreKitProxy;` — Proxy helper to communicate from/to StoreKit
- L120 _private member_ `bool bQueryingReceipts;` — Are receipts being queried
- L123 _private member_ `FOnQueryReceiptsComplete QueryReceiptsComplete;` — Transient delegate to fire when restoring transactions (QueryReceipts with bRestoreReceipts=true)
- L126 _private member_ `TSharedPtr<const FOnlinePurchaseInProgressTransactionIOS> InProgressTransaction;` — Keeps track of in progress user transaction
- L129 _private member_ `TArray<FKnownTransaction> CachedReceipts;` — Cache of known transactions
- L132 _private member_ `TArray<FKnownTransaction> FinalizingTransactions;` — Transactions in the process of being finalized
- L135 _private member_ `FOnlineSubsystemIOS* Subsystem;` — Reference to the parent subsystem
- L138 _private typedef_ `using FOnTransactionFinalized = TMulticastDelegate<void(const FOnlinePurchaseTransactionIOS&)>;` — Delegate fired when a transaction is finalized
- L139 _private member_ `FOnTransactionFinalized OnTransactionFinalized;`

#### struct `FOnlinePurchaseIOS::FKnownTransaction`  
`struct FKnownTransaction`  
_L83-93_
- desc: Entry data for a known completed transaction (restored or purchased)
- L85 _public function_ `explicit FKnownTransaction(TSharedRef<FPurchaseReceipt> InReceipt, SKPaymentTransaction* InTransaction) : Receipt(InReceipt) , PaymentTransaction(InTransaction)`
- L91 _public member_ `TSharedRef<FPurchaseReceipt> Receipt;`
- L92 _public member_ `TRetainedObjCInstance<SKPaymentTransaction*> PaymentTransaction;`

#### Free symbols / members of external scopes

- L142 _typedef_ `typedef TSharedPtr<FOnlinePurchaseIOS, ESPMode::ThreadSafe> FOnlinePurchaseIOSPtr;`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Public/OnlineStoreIOS.h` (Public)


#### class `FOnlineStoreIOS`  
`class FOnlineStoreIOS : public IOnlineStoreV2, public TSharedFromThis<FOnlineStoreIOS, ESPMode::ThreadSafe>`  
_L19-121_
- inherits: `IOnlineStoreV2,TSharedFromThis<FOnlineStoreIOS,ESPMode::ThreadSafe>`
- desc: Implementation for online store via IOS services
- L27 _public prototype_ `virtual void QueryCategories(const FUniqueNetId& UserId, const FOnQueryOnlineStoreCategoriesComplete& Delegate) override;`
- L28 _public prototype_ `virtual void GetCategories(TArray<FOnlineStoreCategory>& OutCategories) const override;`
- L29 _public prototype_ `virtual void QueryOffersByFilter(const FUniqueNetId& UserId, const FOnlineStoreFilter& Filter, const FOnQueryOnlineStoreOffersComplete& Delegate) override;`
- L30 _public prototype_ `virtual void QueryOffersById(const FUniqueNetId& UserId, const TArray<FUniqueOfferId>& OfferIds, const FOnQueryOnlineStoreOffersComplete& Delegate) override;`
- L31 _public prototype_ `virtual void GetOffers(TArray<FOnlineStoreOfferRef>& OutOffers) const override;`
- L32 _public prototype_ `virtual TSharedPtr<FOnlineStoreOffer> GetOffer(const FUniqueOfferId& OfferId) const override;`
- L33 _public prototype_ `virtual FString GetStoreCountry() const override;`
- L42 _public prototype_ `FOnlineStoreIOS(class FOnlineSubsystemIOS* InSubsystem);` — Constructor @param InSubsystem Online subsystem being used
- L47 _public prototype_ `virtual ~FOnlineStoreIOS();` — Destructor
- L55 _public prototype_ `SKProduct* GetSKProductByOfferId(const FUniqueOfferId& OfferId);` — Get the production information for a given offer id Must have previously been retrieved by QueryOffers* @return the SKProduct previously queried for product information
- L60 _public prototype_ `void OnProductsRequestResponse(SKProductsResponse* Response, const FOnQueryOnlineStoreOffersComplete& CompletionDelegate);` — Method used internally by FOnlineSubsystemIOS to notify that QueryOffers request finished. Not meant to be called by user code
- L65 _public prototype_ `void QueryStoreCountry();` — Starts an async request to get the store kit country
- L98 _private prototype_ `void AddOffer(const FOnlineStoreOfferIOS& NewOffer);`
- L100 _private prototype_ `bool OffersNotAllowedInLocale(const FString& Locale);`
- L105 _private typedef_ `typedef TMap<FUniqueOfferId, FOnlineStoreOfferIOS> FOnlineOfferDescriptionMap;` — Mapping from offer id to product information
- L108 _private member_ `FOnlineOfferDescriptionMap CachedOffers;` — Mapping of all queried offers to their product information
- L111 _private member_ `TRetainedObjCInstance<FStoreKitStoreProxy*> StoreKitProxy;` — Store kit helper for interfacing with app store
- L114 _private member_ `bool bIsQueryInFlight;` — Is a query already in flight
- L116 _private member_ `FString StoreCountry;`
- L117 _private member_ `TAtomic<bool> bIsStoreCountryInitialized = false;`
- L120 _private member_ `FOnlineSubsystemIOS* Subsystem;` — Reference to the parent subsystem

#### struct `FOnlineStoreIOS::FOnlineStoreOfferIOS`  
`struct FOnlineStoreOfferIOS`  
_L73-96_
- desc: Representation of a single product offer
- L75 _public function_ `FOnlineStoreOfferIOS() : FOnlineStoreOfferIOS(nil, nullptr)`
- L80 _public function_ `FOnlineStoreOfferIOS(SKProduct* InProduct, TSharedPtr<FOnlineStoreOffer>&& InOffer)`
- L87 _public function_ `bool IsValid() const` — @return true if the store offer is valid/proper
- L93 _public member_ `TRetainedObjCInstance<SKProduct*> Product;` — Reference to the app store product information
- L95 _public member_ `TSharedPtr<FOnlineStoreOffer> Offer;` — Product information about this offer

#### Free symbols / members of external scopes

- L123 _typedef_ `typedef TSharedPtr<FOnlineStoreIOS, ESPMode::ThreadSafe> FOnlineStoreIOSPtr;`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Public/OnlineSubsystemIOS.h` (Public)


#### class `FOnlineSubsystemIOS`  
`class FOnlineSubsystemIOS : public FOnlineSubsystemImpl`  
_L28-151_
- inherits: `FOnlineSubsystemImpl`
- desc: OnlineSubsystemIOS - Implementation of the online subsystem for IOS services
- L34 _public prototype_ `virtual ~FOnlineSubsystemIOS() = default;`
- L37 _public prototype_ `virtual IOnlineSessionPtr GetSessionInterface() const override;`
- L38 _public prototype_ `virtual IOnlineFriendsPtr GetFriendsInterface() const override;`
- L39 _public prototype_ `virtual IOnlinePartyPtr GetPartyInterface() const override;`
- L40 _public prototype_ `virtual IOnlineGroupsPtr GetGroupsInterface() const override;`
- L41 _public prototype_ `virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override;`
- L42 _public prototype_ `virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;`
- L43 _public prototype_ `virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;`
- L44 _public prototype_ `virtual IOnlineVoicePtr GetVoiceInterface() const override;`
- L45 _public prototype_ `virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;`
- L46 _public prototype_ `virtual IOnlineTimePtr GetTimeInterface() const override;`
- L47 _public prototype_ `virtual IOnlineIdentityPtr GetIdentityInterface() const override;`
- L48 _public prototype_ `virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;`
- L49 _public prototype_ `virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;`
- L50 _public prototype_ `virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override;`
- L51 _public prototype_ `virtual IOnlinePurchasePtr GetPurchaseInterface() const override;`
- L52 _public prototype_ `virtual IOnlineEventsPtr GetEventsInterface() const override;`
- L53 _public prototype_ `virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;`
- L54 _public prototype_ `virtual IOnlineSharingPtr GetSharingInterface() const override;`
- L55 _public prototype_ `virtual IOnlineUserPtr GetUserInterface() const override;`
- L56 _public prototype_ `virtual IOnlineMessagePtr GetMessageInterface() const override;`
- L57 _public prototype_ `virtual IOnlinePresencePtr GetPresenceInterface() const override;`
- L58 _public prototype_ `virtual IOnlineChatPtr GetChatInterface() const override;`
- L59 _public prototype_ `virtual IOnlineStatsPtr GetStatsInterface() const override;`
- L60 _public prototype_ `virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override;`
- L61 _public prototype_ `virtual IOnlineTournamentPtr GetTournamentInterface() const override;`
- L62 _public prototype_ `virtual bool Init() override;`
- L63 _public prototype_ `virtual bool Shutdown() override;`
- L64 _public prototype_ `virtual FString GetAppId() const override;`
- L65 _public prototype_ `virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L66 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L67 _public prototype_ `virtual FText GetOnlineServiceName() const override;`
- L68 _public prototype_ `virtual bool IsEnabled() const override;`
- L75 _public prototype_ `explicit FOnlineSubsystemIOS(FName InInstanceName);`
- L81 _public prototype_ `static bool IsInAppPurchasingEnabled();` — Is IAP available for use @return true if IAP should be available, false otherwise
- L87 _public prototype_ `static bool IsGameCenterEnabled();` — Is GameCenter enabled @return true if enabled, false otherwise
- L93 _public prototype_ `static bool IsCloudKitEnabled();` — Is CloudKit enabled @return true if enabled, false otherwise
- L98 _public prototype_ `FAppStoreUtils* GetAppStoreUtils();` — @return access to the app store utility class
- L101 _public prototype_ `static NSString* GetPlayerId(GKPlayer* Player);`
- L102 _public prototype_ `static NSString* GetPlayerId(GKLocalPlayer* Player);`
- L106 _private prototype_ `void InitAppStoreHelper();`
- L107 _private prototype_ `void CleanupAppStoreHelper();`
- L110 _private prototype_ `bool HandlePurchaseExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);` — Handle purchase command cheat codes
- L113 _private member_ `class FRunnableThread* OnlineAsyncTaskThread;` — Online async task thread
- L116 _private member_ `FAppStoreUtils* AppStoreHelper;` — App store util helper
- L119 _private member_ `FOnlineSessionIOSPtr SessionInterface;` — Interface to the session services
- L122 _private member_ `FOnlineIdentityIOSPtr IdentityInterface;` — Interface to the Identity information
- L125 _private member_ `FOnlineFriendsIOSPtr FriendsInterface;` — Interface to the friends services
- L128 _private member_ `FOnlineLeaderboardsIOSPtr LeaderboardsInterface;` — Interface to the profile information
- L132 _private member_ `FOnlineStoreIOSPtr StoreV2Interface;` — Interface to the online catalog
- L135 _private member_ `FOnlinePurchaseIOSPtr PurchaseInterface;` — Interface to the store purchasing
- L138 _private member_ `FOnlineAchievementsIOSPtr AchievementsInterface;` — Interface to the online achievements
- L141 _private member_ `FOnlineExternalUIIOSPtr ExternalUIInterface;` — Interface to the external UI services
- L144 _private member_ `FOnlineTurnBasedIOSPtr TurnBasedInterface;` — Interface to the turnbased multiplayer services
- L147 _private member_ `FOnlineUserCloudIOSPtr UserCloudInterface;` — Interface to the user cloud storage
- L150 _private member_ `FOnlineSharedCloudIOSPtr SharedCloudInterface;` — Interface to the shared cloud storage

#### Free symbols / members of external scopes

- L153 _typedef_ `typedef TSharedPtr<FOnlineSubsystemIOS, ESPMode::ThreadSafe> FOnlineSubsystemIOSPtr;`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Public/OnlineSubsystemIOSModule.h` (Public)


#### class `FOnlineSubsystemIOSModule`  
`class FOnlineSubsystemIOSModule : public IModuleInterface`  
_L12-42_
- inherits: `IModuleInterface`
- desc: Online subsystem module class (GameCenter Implementation) Code related to the loading and handling of the GameCenter module.
- L17 _private member_ `class FOnlineFactoryIOS* IOSFactory;` — Class responsible for creating instance(s) of the subsystem
- L21 _public function_ `FOnlineSubsystemIOSModule() : IOSFactory(NULL)`
- L26 _public function_ `virtual ~FOnlineSubsystemIOSModule()`
- L29 _public prototype_ `virtual void StartupModule() override;`
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L32 _public function_ `virtual bool SupportsDynamicReloading() override`
- L37 _public function_ `virtual bool SupportsAutomaticShutdown() override`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Public/OnlineSubsystemIOSPackage.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define PACKAGE_SCOPE public`
- L12 _macro_ `#define PACKAGE_SCOPE protected`

### `Plugins/Online/IOS/OnlineSubsystemIOS/Source/Public/RetainedObjCInstance.h` (Public)


#### class `TRetainedObjCInstance`  
`template <typename T> class TRetainedObjCInstance`  
_L17-151_
- L24 _public function_ `TRetainedObjCInstance() :Ptr(nil)` — Default constructor, initializes to nil.
- L32 _public function_ `TRetainedObjCInstance(T InPtr) :Ptr(InPtr?[InPtr retain]:nil)` — Constructor, initializes instance and increases reference count if not nil.
- L42 _public function_ `TRetainedObjCInstance(const TRetainedObjCInstance& Other) :TRetainedObjCInstance(Other.Ptr)` — Copy constructor, initializes instance and increases reference count if not nil. @param Other The Other object to copy from.
- L52 _public function_ `TRetainedObjCInstance(TRetainedObjCInstance&& Other) :Ptr(Other.Ptr)` — Move constructor, initializes instance. Sets other to nil without updating reference counting. @param Other The Other object to move from.
- L63 _public function_ `TRetainedObjCInstance& operator=(const TRetainedObjCInstance& Other)` — Copy assignment, releases owned instance and retains received one. @param Other The Other object to copy from.
- L78 _public function_ `TRetainedObjCInstance operator=(TRetainedObjCInstance&& Other)` — Move assignment, releases owned instance, updates owned instance and clears Other. @param Other The Other object to move from.
- L92 _public function_ `~TRetainedObjCInstance()` — Destructor, releases owned instance if needed
- L100 _public function_ `operator T()` — Conversion operator to underlying instance. Useful to invoke Objective-C methods transparently
- L105 _public function_ `operator T() const` — Conversion operator to underlying instance. Useful to invoke Objective-C methods transparently
- L110 _public function_ `void Reset()` — Releases ownership on Objective-C instance
- L150 _private member_ `T Ptr;` — Owned Objective-C instance

#### Free symbols / members of external scopes

- L119 _function_ `friend bool operator==(const TRetainedObjCInstance<T>& Lhs, const TRetainedObjCInstance<T>& Rhs)`
- L124 _function_ `friend bool operator==(const TRetainedObjCInstance<T>& Lhs, T Rhs)`
- L129 _function_ `friend bool operator==(T Lhs,const TRetainedObjCInstance<T>& Rhs)`
- L134 _function_ `friend bool operator!=(const TRetainedObjCInstance<T>& Lhs, const TRetainedObjCInstance<T>& Rhs)`
- L139 _function_ `friend bool operator!=(const TRetainedObjCInstance<T>& Lhs, T Rhs)`
- L144 _function_ `friend bool operator!=(T Lhs, const TRetainedObjCInstance<T>& Rhs)`
