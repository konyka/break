# Plugins / Party

- module root: `Plugins/Online/OnlineFramework/Source/Party`
- headers: 31; symbols: 1877
- symbol kinds: class=44, delegate=70, enum=15, enumerator=146, externvar=12, function=302, macro=43, member=365, namespace=11, prototype=832, struct=25, typedef=12
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, OnlineFrameworkCommon, OnlineServicesInterface, OnlineServicesOSSAdapter, OnlineSubsystemGDK
- PublicDependencyModuleNames: CoreOnline, OnlineSubsystem, OnlineSubsystemUtils

### `Plugins/Online/OnlineFramework/Source/Party/Private/Microsoft/SocialSettingsXbl.h` (Private)


#### class `USocialSettingsXbl`  
`class USocialSettingsXbl : public UObject`  
_L14-35_
- reflection: `UCLASS(Config = Game)`
- inherits: `UObject`
- desc: Config-driven settings object for the social framework. Only the CDO is ever expected to be used, no instance is ever expected to be created.
- L19 _public prototype_ `USocialSettingsXbl();`
- L22 _public prototype_ `static bool ShouldApplyPlatformInvitePermissionsLive();` — Should GDK permissions be checked for invites received from other xbl users
- L24 _public prototype_ `static bool ShouldApplyPlatformInvitePermissionsCrossplay();` — Should GDK permissions be checked for invites received from non-xbl users
- L30 _private member_ `bool bApplyPlatformInvitePermissionsLive = true;` — `UPROPERTY(config)` — Should GDK permissions be checked for invites received from other xbl users
- L34 _private member_ `bool bApplyPlatformInvitePermissionsCrossplay = false;` — `UPROPERTY(config)` — Should GDK permissions be checked for invites received from non-xbl users

### `Plugins/Online/OnlineFramework/Source/Party/Private/Party/PartyPlatformSessionMonitor.h` (Private)


#### class `FPartyPlatformSessionManager`  
`class FPartyPlatformSessionManager : public TSharedFromThis<FPartyPlatformSessionManager>`  
_L23-60_
- inherits: `TSharedFromThis<FPartyPlatformSessionManager>`
- L26 _public prototype_ `static bool DoesOssNeedPartySession(FName OssName);`
- L27 _public prototype_ `static TOptional<FString> GetOssPartySessionType(FName OssName);`
- L28 _public prototype_ `static TSharedRef<FPartyPlatformSessionManager> Create(USocialManager& InSocialManager);`
- L30 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnFindSessionAttemptComplete, bool, const FOnlineSessionSearchResult&);`
- L31 _public prototype_ `bool FindSession(const USocialUser& User, const FOnFindSessionAttemptComplete& OnAttemptComplete);`
- L32 _public prototype_ `bool FindSession(const FPartyPlatformSessionInfo& SessionInfo, const FOnFindSessionAttemptComplete& OnAttemptComplete);`
- L34 _public prototype_ `IOnlineSessionPtr GetSessionInterface();`
- L35 _public prototype_ `IOnlineFriendsPtr GetFriendsInterface();`
- L36 _public prototype_ `FUniqueNetIdRepl GetLocalUserPlatformId() const;`
- L39 _private prototype_ `FPartyPlatformSessionManager(USocialManager& InSocialManager);`
- L40 _private prototype_ `void InitSessionManager();`
- L41 _private prototype_ `void CreateMonitor(USocialParty& Party);`
- L43 _private prototype_ `bool FindSessionInternal(const FSessionId& SessionId, const FUniqueNetIdRepl& SessionOwnerId, const FOnFindSessionAttemptComplete& OnAttemptComplete);`
- L44 _private prototype_ `void ProcessCompletedSessionSearch(int32 LocalUserNum, bool bWasSuccessful, const FOnlineSessionSearchResult& FoundSession, const FSessionId& SessionId, const FUniqueNetIdRepl& SessionOwnerId, const FOnFindSessionAttemptComplete& OnAttemptComplete);`
- L46 _private prototype_ `void HandleFindSessionByIdComplete(int32 LocalUserNum, bool bWasSuccessful, const FOnlineSessionSearchResult& FoundSession, FSessionId SessionId, FUniqueNetIdRepl SessionOwnerId, FOnFindSessionAttemptComplete OnAttemptComplete);`
- L47 _private prototype_ `void HandleFindFriendSessionsComplete(int32 LocalUserNum, bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& FoundSessions, FSessionId SessionId, FUniqueNetIdRepl SessionOwnerId, FOnFindSessionAttemptComplete OnAttemptComplete);`
- L49 _private prototype_ `void HandlePartyJoined(USocialParty& NewParty);`
- L50 _private prototype_ `void HandleMonitorShutdownComplete(TSharedRef<FPartyPlatformSessionMonitor> Monitor);`
- L53 _private member_ `bool bHasAlreadyRequeriedPSNFriends = false;`
- L54 _private prototype_ `void HandleReadPSNFriendsListComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr, FSessionId OriginalSessionId, FUniqueNetIdRepl SessionOwnerId, FOnFindSessionAttemptComplete OnAttemptComplete);`
- L57 _private member_ `USocialManager& SocialManager;`
- L58 _private member_ `const FName PlatformOssName;`
- L59 _private member_ `TArray<TSharedRef<FPartyPlatformSessionMonitor>> ActiveMonitors;`

#### class `FPartyPlatformSessionMonitor`  
`class FPartyPlatformSessionMonitor : public TSharedFromThis<FPartyPlatformSessionMonitor>`  
_L63-153_
- inherits: `TSharedFromThis<FPartyPlatformSessionMonitor>`
- desc: Util class to maintain ideal platform session membership during the lifetime of the owning party
- L66 _public prototype_ `static TSharedRef<FPartyPlatformSessionMonitor> Create(const TSharedRef<FPartyPlatformSessionManager>& InSessionManager, USocialParty& PartyToMonitor);`
- L68 _public prototype_ `void ShutdownMonitor();`
- L69 _public prototype_ `~FPartyPlatformSessionMonitor();`
- L71 _public prototype_ `const FOnlinePartyTypeId& GetMonitoredPartyTypeId() const;`
- L72 _public prototype_ `EOnlineSessionState::Type GetOssSessionState() const;`
- L73 _public member_ `FSimpleDelegate OnSessionEstablished;`
- L75 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnShutdownComplete, TSharedRef<FPartyPlatformSessionMonitor>);`
- L76 _public member_ `FOnShutdownComplete OnShutdownComplete;`
- L79 _private prototype_ `FPartyPlatformSessionMonitor(const TSharedRef<FPartyPlatformSessionManager>& InSessionManager, USocialParty& PartyToMonitor);`
- L80 _private prototype_ `void Initialize();`
- L81 _private prototype_ `void ShutdownInternal();`
- L83 _private prototype_ `void CreateSession(const FUniqueNetIdRepl& LocalUserPlatformId);`
- L84 _private prototype_ `void AddLocalPlayerToSession(UPartyMember* InitializedMember);`
- L85 _private prototype_ `void RemoveLocalPlayerFromSession(UPartyMember* PartyMember);`
- L86 _private prototype_ `void FindSession(const FPartyPlatformSessionInfo& SessionInfo);`
- L87 _private prototype_ `void JoinSession(const FOnlineSessionSearchResult& SessionSearchResult);`
- L88 _private prototype_ `void LeaveSession();`
- L90 _private prototype_ `void EvaluateCurrentSession();`
- L91 _private prototype_ `void QueuePlatformSessionUpdate();`
- L92 _private prototype_ `bool ConfigurePlatformSessionSettings(FOnlineSessionSettings& SessionSettings) const;`
- L94 _private prototype_ `const FPartyPlatformSessionInfo* FindLocalPlatformSessionInfo() const;`
- L95 _private prototype_ `bool DoesLocalUserOwnPlatformSession();`
- L96 _private prototype_ `void SetIsSessionMissing(bool bIsMissing);`
- L98 _private prototype_ `void ProcessJoinFailure();`
- L100 _private prototype_ `bool ShouldAlwaysCreateLocalPlatformSession() const;`
- L101 _private prototype_ `bool ShouldRecordAsRecentPlayer(const FUniqueNetId& LocalUserId, const UPartyMember* PartyMember);`
- L102 _private prototype_ `void UpdateRecentPlayersOfLocalMembers(const TArray<UPartyMember*>& RecentPlayers);`
- L103 _private prototype_ `void UpdateRecentPlayersOfLocalUser(const FUniqueNetId& LocalUserId, const TArray<UPartyMember*>& Members);`
- L106 _private prototype_ `void HandlePlatformSessionsChanged();`
- L107 _private prototype_ `void HandlePartyConfigurationChanged(const FPartyConfiguration& NewConfig);`
- L108 _private prototype_ `void HandlePartyLeft(EMemberExitedReason Reason);`
- L109 _private prototype_ `void HandlePartyMemberCreated(UPartyMember& NewMember);`
- L110 _private prototype_ `void HandlePartyMemberInitialized(UPartyMember* InitializedMember);`
- L111 _private prototype_ `void HandlePartyMemberLeft(UPartyMember* OldMember, const EMemberExitedReason Reason);`
- L113 _private prototype_ `void HandleCreateSessionComplete(const FName SessionName, bool bWasSuccessful);`
- L114 _private prototype_ `void HandleFindSessionComplete(bool bWasSuccessful, const FOnlineSessionSearchResult& FoundSession);`
- L115 _private prototype_ `void HandleJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type JoinSessionResult);`
- L116 _private prototype_ `void HandleDestroySessionComplete(FName SessionName, bool bWasSuccessful);`
- L117 _private prototype_ `bool HandleRetryEstablishingSession(float);`
- L118 _private prototype_ `void HandleSessionFailure(const FUniqueNetId& LocalUserId, ESessionFailure::Type FailureType);`
- L120 _private prototype_ `bool HandleQueuedSessionUpdate(float);`
- L123 _private member_ `TSharedRef<FPartyPlatformSessionManager> SessionManager;`
- L124 _private member_ `TWeakObjectPtr<USocialParty> MonitoredParty;`
- L125 _private member_ `FOnlinePartyTypeId PartyTypeId;`
- L127 _private member_ `FSessionId TargetSessionId;`
- L130 _private member_ `TOptional<FSessionId> LastAttemptedFindSessionId;` — Last session id we attempted to find to prevent repeated failures to find the same session
- L133 _private member_ `bool bHasQueuedSessionUpdate = false;` — Do we have a console session update queued?
- L136 _private member_ `bool bMissedSessionUpdateDuringCreate = false;` — Did we miss a session update while we were creating?
- L138 _private member_ `static const FName Step_FindSession;`
- L139 _private member_ `static const FName Step_JoinSession;`
- L140 _private member_ `static const FName Step_CreateSession;`
- L141 _private member_ `FSocialActionTimeTracker SessionInitTracker;`
- L149 _private member_ `} ShutdownState = EMonitorShutdownState::None;`
- L151 _private member_ `FTSTicker::FDelegateHandle RetryTickerHandle;`
- L152 _private member_ `FDelegateHandle UpdateOssSessionHandle;`

#### enum `FPartyPlatformSessionMonitor::EMonitorShutdownState`  
`enum class EMonitorShutdownState : uint8`  
_L143-149_
- L145 _public enumerator_ `None`
- L146 _public enumerator_ `Requested`
- L147 _public enumerator_ `InProgress`
- L148 _public enumerator_ `Complete`

#### Free symbols / members of external scopes

- L30 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnFindSessionAttemptComplete, bool, const FOnlineSessionSearchResult&);`
- L75 _delegate_ `DECLARE_DELEGATE_OneParam(FOnShutdownComplete, TSharedRef<FPartyPlatformSessionMonitor>);`

### `Plugins/Online/OnlineFramework/Source/Party/Private/User/SocialUserList.h` (Private)


#### class `FSocialUserList`  
`class FSocialUserList : public ISocialUserList, public TSharedFromThis<FSocialUserList>`  
_L19-108_
- inherits: `ISocialUserList,TSharedFromThis<FSocialUserList>`
- L23 _public prototype_ `static TSharedRef<FSocialUserList> CreateUserList(const USocialToolkit& InOwnerToolkit, const FSocialUserListConfig& Config);`
- L25 _public function_ `FOnUserAdded& OnUserAdded() const override`
- L26 _public function_ `FOnUserRemoved& OnUserRemoved() const override`
- L27 _public function_ `FOnUpdateComplete& OnUpdateComplete() const override`
- L29 _public function_ `virtual FString GetListName() const override`
- L31 _public prototype_ `virtual void UpdateNow() override;`
- L32 _public prototype_ `virtual void SetAllowAutoUpdate(bool bIsEnabled) override;`
- L33 _public prototype_ `virtual void SetAllowSortDuringUpdate(bool bIsEnabled) override;`
- L34 _public function_ `virtual const TArray<TWeakObjectPtr<USocialUser>>& GetUsers() const override`
- L36 _public prototype_ `bool HasPresenceFilters() const;`
- L39 _protected function_ `const FSocialUserListConfig& GetListConfig() const`
- L40 _protected prototype_ `virtual void MarkUserAsDirty(USocialUser& User) override;`
- L43 _private prototype_ `void HandleOwnerToolkitReset();`
- L45 _private prototype_ `void HandlePartyInviteReceived(USocialUser& InvitingUser);`
- L46 _private prototype_ `void HandlePartyInviteRemoved(USocialUser& InvitingUser);`
- L47 _private prototype_ `void HandlePartyInviteHandled(USocialUser* InvitingUser);`
- L49 _private prototype_ `void HandleFriendInviteReceived(USocialUser& User, ESocialSubsystem SubsystemType);`
- L50 _private prototype_ `void HandleFriendInviteRemoved(ESocialSubsystem SubsystemType, USocialUser* User);`
- L52 _private prototype_ `void HandleFriendshipEstablished(USocialUser& NewFriend, ESocialSubsystem SubsystemType, bool bIsNewRelationship);`
- L53 _private prototype_ `void HandleFriendRemoved(ESocialSubsystem SubsystemType, USocialUser* User);`
- L55 _private prototype_ `void HandleUserBlocked(USocialUser& BlockedUser, ESocialSubsystem SubsystemType, bool bIsNewRelationship);`
- L56 _private prototype_ `void HandleUserBlockStatusChanged(ESocialSubsystem SubsystemType, bool bIsBlocked, USocialUser* User);`
- L58 _private prototype_ `void HandleRecentPlayerAdded(USocialUser& AddedUser, ESocialSubsystem SubsystemType, bool bIsNewRelationship);`
- L59 _private prototype_ `void HandleRecentPlayerRemoved(USocialUser& RemovedUser, ESocialSubsystem SubsystemType);`
- L61 _private prototype_ `void HandleUserPresenceChanged(ESocialSubsystem SubsystemType, USocialUser* User);`
- L62 _private prototype_ `void HandleUserGameSpecificStatusChanged(USocialUser* User);`
- L64 _private prototype_ `void HandleRequestToJoinReceived(USocialUser& SocialUser, IOnlinePartyRequestToJoinInfoConstRef Request);`
- L65 _private prototype_ `void HandleRequestToJoinRemoved(USocialUser& SocialUser, IOnlinePartyRequestToJoinInfoConstRef Request, EPartyRequestToJoinRemovedReason Reason);`
- L67 _private prototype_ `void TryAddUser(USocialUser& User);`
- L68 _private prototype_ `void TryAddUserFast(USocialUser& User);`
- L70 _private prototype_ `void TryRemoveUser(USocialUser& User);`
- L71 _private prototype_ `void TryRemoveUserFast(USocialUser& User);`
- L73 _private prototype_ `bool EvaluateUserPresence(const USocialUser& User, ESocialSubsystem SubsystemType);`
- L74 _private prototype_ `bool EvaluatePresenceFlag(bool bPresenceValue, ESocialUserStateFlags Flag) const;`
- L76 _private prototype_ `bool HandleAutoUpdateList(float);`
- L77 _private prototype_ `void UpdateListInternal();`
- L79 _private prototype_ `void HandlePartyJoined(USocialParty& Party);`
- L80 _private prototype_ `void HandlePartyLeft(EMemberExitedReason Reason, USocialParty* LeftParty);`
- L81 _private prototype_ `void HandlePartyMemberCreated(UPartyMember& Member);`
- L82 _private prototype_ `void HandlePartyMemberLeft(EMemberExitedReason Reason, UPartyMember* Member, bool bUpdateNow);`
- L84 _private prototype_ `USocialUser* FindOwnersRelationshipTo(UPartyMember& TargetPartyMember) const;`
- L85 _private prototype_ `void MarkPartyMemberAsDirty(UPartyMember& PartyMember);`
- L88 _private prototype_ `FSocialUserList(const USocialToolkit& InOwnerToolkit, const FSocialUserListConfig& Config);`
- L89 _private prototype_ `void InitializeList();`
- L91 _private member_ `TWeakObjectPtr<const USocialToolkit> OwnerToolkit;`
- L92 _private member_ `TArray<TWeakObjectPtr<USocialUser>> Users;`
- L93 _private member_ `TArray<TWeakObjectPtr<USocialUser>> PendingAdds;`
- L95 _private member_ `TSet<TWeakObjectPtr<USocialUser>> UsersWithDirtyPresence;`
- L96 _private member_ `TArray<TWeakObjectPtr<const USocialUser>> PendingRemovals;`
- L98 _private member_ `FSocialUserListConfig ListConfig;`
- L100 _private member_ `bool bNeedsSort = false;`
- L101 _private member_ `int32 AutoUpdateRequests = 0;`
- L102 _private member_ `float AutoUpdatePeriod = .5f;`
- L103 _private member_ `FTSTicker::FDelegateHandle UpdateTickerHandle;`
- L105 _private member_ `mutable FOnUserAdded OnUserAddedEvent;`
- L106 _private member_ `mutable FOnUserRemoved OnUserRemovedEvent;`
- L107 _private member_ `mutable FOnUpdateComplete OnUpdateCompleteEvent;`

#### Free symbols / members of external scopes

- L17 _typedef_ `typedef TSharedRef<const IOnlinePartyRequestToJoinInfo> IOnlinePartyRequestToJoinInfoConstRef;`

### `Plugins/Online/OnlineFramework/Source/Party/Public/Chat/ChatSlashCommands.h` (Public)


#### struct `FAutoCompleteStruct`  
`struct FAutoCompleteStruct`  
_L25-35_
- L27 _public prototype_ `FAutoCompleteStruct(const FString& InFullString, const TWeakPtr<const FChatSlashCommand>& InCmd, TWeakObjectPtr<USocialUser> InOptionalTargetUser);`
- L31 _public member_ `FString FullString;` — Cacheing data with strings is tricky because they will become invalid when the user changes their localization but a user can't change this while typing a command, so it is okay in this case.
- L32 _public member_ `TWeakPtr<const FChatSlashCommand> SlashCommand;`
- L33 _public member_ `TWeakObjectPtr<USocialUser> OptionalTargetUser;`
- L34 _public member_ `TArray<FString> Tokens;`

#### class `FRegisteredSlashCommands`  
`class FRegisteredSlashCommands : public TSharedFromThis<FRegisteredSlashCommands>`  
_L39-78_
- inherits: `TSharedFromThis<FRegisteredSlashCommands>`
- desc: Slash Command Component
- L42 _public prototype_ `static void TokenizeMessage(const FString& InChatText, TArray<FString>& Tokens);`
- L43 _public prototype_ `static bool TokensExactMatch(TArray<FString>& TokensLHS, TArray<FString>& TokensRHS);`
- L44 _public prototype_ `static bool CmdMatchesFirstToken(const FString& CmdString, const TArray<FString>& Tokens);`
- L46 _public prototype_ `FRegisteredSlashCommands() = default;`
- L47 _public prototype_ `void Init(USocialToolkit& Toolkit);`
- L50 _public prototype_ `bool NotifyUserTextChanged(const FText& InText);` — main entry point for class encapsulated behavior; returns true if command executed
- L52 _public prototype_ `bool TryExecuteCommandByMatchingText(const FString& UserTypedText);`
- L53 _public function_ `bool HasAutoCompleteSuggestions()`
- L54 _public function_ `const TArray<TSharedPtr<FAutoCompleteStruct>>& GetAutoCompleteStrings() const`
- L55 _public prototype_ `void RegisterCommand(const TSharedPtr<FChatSlashCommand>& NewSlashCommand);`
- L56 _public prototype_ `bool IsEnabled();`
- L59 _private prototype_ `void PrepareInteractionAutocompleteStrings(const TArray<FString>& StringTokens);`
- L60 _private prototype_ `void HandleCultureChanged() const;`
- L62 _private member_ `uint32 LastQueryTextLen = 0;`
- L63 _private member_ `bool bValidUsersCached = false;`
- L64 _private prototype_ `bool SpaceWasJustTyped(const FString& NewUserText);`
- L67 _private member_ `TArray<TSharedPtr<FChatSlashCommand>> RegisteredCustomSlashCommands;`
- L68 _private member_ `TArray<TSharedPtr<FInteractionCommandWrapper>> RegisteredInteractionSlashCommands;`
- L71 _private member_ `TWeakObjectPtr<USocialToolkit> MyToolkit;` — once set, this should always be valid since lifetime of SocialManager is tied to game instance
- L72 _private member_ `mutable TArray<TSharedPtr<FAutoCompleteStruct>> AutoCompleteData;`
- L74 _private prototype_ `FRegisteredSlashCommands(const FRegisteredSlashCommands& copy) = delete;`
- L75 _private prototype_ `FRegisteredSlashCommands(FRegisteredSlashCommands&& move) = delete;`
- L76 _private prototype_ `FRegisteredSlashCommands& operator=(const FRegisteredSlashCommands& copy) = delete;`
- L77 _private prototype_ `FRegisteredSlashCommands& operator=(FRegisteredSlashCommands&& move) = delete;`

#### class `FChatSlashCommand`  
`class FChatSlashCommand : public TSharedFromThis<FChatSlashCommand>`  
_L84-115_
- inherits: `TSharedFromThis<FChatSlashCommand>`
- L88 _public prototype_ `explicit FChatSlashCommand(const FText& InCommandName);` — @param InCommandName Command name including / prefix. eg "/party".
- L89 _public prototype_ `virtual ~FChatSlashCommand() = default;`
- L91 _public prototype_ `virtual void Init(USocialToolkit& InToolkit);`
- L92 _public prototype_ `virtual bool IsEnabled() const = 0;`
- L93 _public prototype_ `virtual void ExecuteSlashCommand(USocialUser* OptionalTargetUser) const = 0;`
- L95 _public prototype_ `virtual void GetAutoCompleteStrings(TArray< TSharedPtr<FAutoCompleteStruct> >& OutStringContainer, const TArray<FString>& UserTextTokens) const;`
- L96 _public function_ `virtual bool CanExecuteSpacebarFromPartialTokens(const TArray<FString>& UserTextTokens) const`
- L97 _public function_ `virtual bool HasSpacebarExecuteFunctionality() const`
- L98 _public function_ `virtual bool RequiresUserForExecution() const`
- L99 _public prototype_ `virtual void RecacheForLocalization() const;`
- L101 _public function_ `const FString& GetCommandNameString() const`
- L104 _protected function_ `USocialToolkit* GetToolkit() const`
- L105 _protected member_ `mutable FString CommandNameString;`
- L108 _private member_ `const FText CommandNameTextSrc;`
- L109 _private member_ `TWeakObjectPtr<USocialToolkit> MyToolkit;`
- L111 _private prototype_ `FChatSlashCommand(const FChatSlashCommand& copy) = delete;`
- L112 _private prototype_ `FChatSlashCommand(FChatSlashCommand&& move) = delete;`
- L113 _private prototype_ `FChatSlashCommand& operator=(const FChatSlashCommand& copy) = delete;`
- L114 _private prototype_ `FChatSlashCommand& operator=(FChatSlashCommand&& move) = delete;`

#### class `FInteractionCommandWrapper`  
`class FInteractionCommandWrapper: public FChatSlashCommand`  
_L119-146_
- inherits: `FChatSlashCommand`
- L123 _public prototype_ `FInteractionCommandWrapper(FSocialInteractionHandle Interaction);` — Interaction tokens will have / prefix appended.
- L125 _public prototype_ `virtual void ExecuteSlashCommand(USocialUser* OptionalTargetUser) const override;`
- L126 _public function_ `virtual bool IsEnabled() const override`
- L127 _public function_ `virtual bool HasSpacebarExecuteFunctionality() const`
- L128 _public function_ `virtual bool RequiresUserForExecution() const override`
- L129 _public function_ `virtual bool CanExecuteSpacebarFromPartialTokens(const TArray<FString>& UserTextTokens) const`
- L131 _public prototype_ `void ResetUserCache();`
- L132 _public prototype_ `inline void TryCacheValidAutoCompleteUser(USocialUser& User, const TArray<FString>& StringTokens);`
- L133 _public prototype_ `virtual void GetAutoCompleteStrings(TArray< TSharedPtr<FAutoCompleteStruct> >& OutStringContainer, const TArray<FString>& UserTextTokens) const override;`
- L134 _public prototype_ `virtual void RecacheForLocalization() const override;`
- L137 _private member_ `FSocialInteractionHandle WrappedInteraction;`
- L138 _private member_ `mutable FString CachedCommandToken;`
- L139 _private member_ `TArray<TWeakObjectPtr<USocialUser>> CachedValidUsers;`
- L145 _private prototype_ `void CacheStringDataForLocalization() const;` — NOTE: we cannot simply cache the FText long term because localization changes while running will invalidate cache. So, there exists the following function to re-query the localization

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PARTY_API`

### `Plugins/Online/OnlineFramework/Source/Party/Public/Chat/CommonSlashCommands.h` (Public)


#### class `FChannelChangeSlashCommand`  
`class FChannelChangeSlashCommand : public FChatSlashCommand`  
_L17-30_
- inherits: `FChatSlashCommand`
- L20 _public prototype_ `FChannelChangeSlashCommand(const FText& CommandText, ESocialChannelType InChannelType);`
- L22 _public prototype_ `virtual void ExecuteSlashCommand(USocialUser* OptionalTargetUser) const override;`
- L23 _public prototype_ `virtual bool IsEnabled() const override;`
- L24 _public prototype_ `virtual bool CanExecuteSpacebarFromPartialTokens(const TArray<FString>& UserTextTokens) const override;`
- L25 _public function_ `virtual bool HasSpacebarExecuteFunctionality() const`
- L28 _private member_ `ESocialChannelType ChannelType;`

#### class `FPartyChannelSlashCommand`  
`class FPartyChannelSlashCommand : public FChannelChangeSlashCommand`  
_L32-36_
- inherits: `FChannelChangeSlashCommand`
- L35 _public prototype_ `FPartyChannelSlashCommand();`

#### class `FGlobalChannelSlashCommand`  
`class FGlobalChannelSlashCommand : public FChannelChangeSlashCommand`  
_L38-42_
- inherits: `FChannelChangeSlashCommand`
- L41 _public prototype_ `FGlobalChannelSlashCommand();`

#### class `FTeamChannelSlashCommand`  
`class FTeamChannelSlashCommand : public FChannelChangeSlashCommand`  
_L44-48_
- inherits: `FChannelChangeSlashCommand`
- L47 _public prototype_ `FTeamChannelSlashCommand();`

#### class `FFounderChannelSlashCommand`  
`class FFounderChannelSlashCommand : public FChannelChangeSlashCommand`  
_L50-54_
- inherits: `FChannelChangeSlashCommand`
- L53 _public prototype_ `FFounderChannelSlashCommand();`

#### class `FReplySlashCommand`  
`class FReplySlashCommand: public FChatSlashCommand`  
_L58-70_
- inherits: `FChatSlashCommand`
- L61 _public prototype_ `FReplySlashCommand();`
- L62 _public prototype_ `virtual void Init(USocialToolkit& InToolkit) override;`
- L63 _public prototype_ `virtual void ExecuteSlashCommand(USocialUser* OptionalTargetUser) const override;`
- L64 _public prototype_ `virtual bool IsEnabled() const override;`
- L65 _public member_ `TWeakObjectPtr<USocialChatChannel> LastUserChannel = nullptr;`
- L68 _private prototype_ `void HandleChannelCreated(USocialChatChannel& NewChannel);`
- L69 _private prototype_ `void HandleChannelLeft(USocialChatChannel& LeavingChannel);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PARTY_API`

### `Plugins/Online/OnlineFramework/Source/Party/Public/Chat/SocialChatChannel.h` (Public)


#### enum `ESocialChannelType`  
`enum class ESocialChannelType : uint8`  
_L18-26_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `General`
- L21 _public enumerator_ `Founder`
- L22 _public enumerator_ `Party`
- L23 _public enumerator_ `Team`
- L24 _public enumerator_ `System`
- L25 _public enumerator_ `Private`

#### class `USocialChatChannel`  
`class USocialChatChannel : public UObject`  
_L30-115_
- reflection: `UCLASS(MinimalAPI, Abstract, Within=SocialChatManager)`
- inherits: `UObject`
- desc: Base SocialCore chat channel class (partial ISocialChatChannel implementation)
- L35 _public function_ `USocialChatChannel()`
- L37 _public prototype_ `DECLARE_EVENT_OneParam(USocialChatChannel, FOnChannelUserChanged, USocialUser&);`
- L38 _public function_ `virtual FOnChannelUserChanged& OnUserJoinedChannel() const`
- L39 _public function_ `virtual FOnChannelUserChanged& OnUserLeftChannel() const`
- L40 _public function_ `virtual FOnChannelUserChanged& OnChannelUserChanged() const`
- L42 _public prototype_ `DECLARE_EVENT_OneParam(USocialChatChannel, FOnMessageReceived, const FSocialChatMessageRef&);`
- L43 _public function_ `virtual FOnMessageReceived& OnMessageReceived() const`
- L45 _public prototype_ `DECLARE_EVENT_OneParam(USocialChatChannel, FOnChannelDisplayNameChanged, const FText&);`
- L46 _public function_ `virtual FOnChannelDisplayNameChanged& OnChannelDisplayNameChanged() const`
- L48 _public prototype_ `virtual void Initialize(USocialUser* InSocialUser, const FChatRoomId& InChannelId, ESocialChannelType InSourceChannelType) PURE_VIRTUAL(USocialChatChannel::Initialize, return;);`
- L54 _public prototype_ `virtual void InjectLocalMessage(const TSharedRef<FSocialLocalChatMessage>& LocalMessage);` — Manually adds the given message to the channel's log locally. Representations of this channel on other clients will not receive the message. Useful for adding custom messages that did not originate from a user.
- L55 _public function_ `virtual const FText& GetChannelDisplayName() const`
- L56 _public function_ `virtual const TArray<FSocialChatMessageRef>& GetMessageHistory() const`
- L58 _public function_ `virtual void UpdateNow()`
- L59 _public function_ `virtual void SetAutoUpdatePeriod(float)`
- L65 _public prototype_ `virtual bool SendMessage(const FString& Message) PURE_VIRTUAL(USocialChatChannel::SendMessage, return false;) void SetChannelDisplayName(const FText& InDisplayName);` — Sends a text message to all other users in this channel. @return True if the message was sent successfully
- L69 _public prototype_ `void NotifyUserJoinedChannel(USocialUser& InUser);`
- L70 _public prototype_ `void NotifyUserLeftChannel(USocialUser& InUser);`
- L71 _public prototype_ `void NotifyChannelUserChanged(USocialUser& InUser);`
- L72 _public prototype_ `void NotifyMessageReceived(const TSharedRef<FChatMessage>& InChatMessage);`
- L74 _public prototype_ `virtual void ListenToChannel(USocialChatChannel& Channel);`
- L76 _public prototype_ `virtual void HandleListenedChannelMessageReceived(const FSocialChatMessageRef& Message, USocialChatChannel* SourceChannel);`
- L78 _public function_ `ESocialChannelType GetChannelType() const`
- L79 _public function_ `void SetChannelType(ESocialChannelType InType)`
- L81 _public function_ `virtual bool SupportsMessageSending() const`
- L83 _public prototype_ `DECLARE_EVENT_OneParam(USocialChatChannel, FOnHiddenChanged, bool);`
- L84 _public function_ `FOnHiddenChanged& OnHiddenChanged()`
- L85 _public function_ `bool GetIsHidden() const`
- L86 _public prototype_ `void SetIsHidden(bool InValue);`
- L89 _public prototype_ `void AddMirroredMessage(FSocialChatMessageRef NewMessage);` — used by external classes to duplicate a message into a channel that didn't otherwise receive it
- L90 _public prototype_ `void AddSystemMessage(const FText& MessageBody);`
- L93 _protected prototype_ `IOnlineChatPtr GetChatInterface() const;`
- L94 _protected prototype_ `void SanitizeMessage(FString& RawMessage) const;`
- L96 _protected prototype_ `void AddMessageInternal(FSocialChatMessageRef NewMessage);`
- L98 _protected member_ `FText ChannelDisplayName;`
- L99 _protected member_ `ESocialChannelType ChannelType;`
- L101 _protected prototype_ `USocialToolkit& GetOwningToolkit() const;`
- L104 _private member_ `bool bIsHidden = false;`
- L105 _private member_ `FOnHiddenChanged OnHiddenChangedEvent;`
- L107 _private member_ `TArray<FSocialChatMessageRef> MessageHistory;`
- L109 _private member_ `mutable FOnChannelUserChanged OnUserJoinedEvent;`
- L110 _private member_ `mutable FOnChannelUserChanged OnUserLeftEvent;`
- L111 _private member_ `mutable FOnChannelUserChanged OnUserChangedEvent;`
- L112 _private member_ `mutable FOnMessageReceived OnMessageReceivedEvent;`
- L113 _private member_ `mutable FOnChannelDisplayNameChanged OnChannelDisplayNameChangedEvent;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PARTY_API`
- L37 _delegate_ `DECLARE_EVENT_OneParam(USocialChatChannel, FOnChannelUserChanged, USocialUser&);`
- L42 _delegate_ `DECLARE_EVENT_OneParam(USocialChatChannel, FOnMessageReceived, const FSocialChatMessageRef&);`
- L45 _delegate_ `DECLARE_EVENT_OneParam(USocialChatChannel, FOnChannelDisplayNameChanged, const FText&);`
- L83 _delegate_ `DECLARE_EVENT_OneParam(USocialChatChannel, FOnHiddenChanged, bool);`

### `Plugins/Online/OnlineFramework/Source/Party/Public/Chat/SocialChatManager.h` (Public)


#### struct `FSocialChatChannelConfig`  
`struct FSocialChatChannelConfig`  
_L23-45_
- reflection: `USTRUCT()`
- L27 _public function_ `FSocialChatChannelConfig()`
- L29 _public function_ `FSocialChatChannelConfig(class USocialUser* InSocialUser, FString InRoomId, FText InDisplayName, TArray<USocialChatChannel*> InListenChannels = TArray<USocialChatChannel*>()) : SocialUser(InSocialUser) , RoomId(InRoomId) , DisplayName(InDisplayName)`
- L38 _public member_ `TObjectPtr<USocialUser> SocialUser;` — `UPROPERTY()`
- L40 _public member_ `FString RoomId;`
- L43 _public member_ `TArray<TObjectPtr<USocialChatChannel>> ListenChannels;` — `UPROPERTY()`
- L44 _public member_ `FText DisplayName;`

#### class `USocialChatManager`  
`class USocialChatManager : public UObject`  
_L49-195_
- reflection: `UCLASS(MinimalAPI, Within=SocialToolkit, Config=Game)`
- inherits: `UObject`
- desc: The chat manager is a fully passive construct that watches for creation of chat rooms and message activity therein
- L54 _public prototype_ `static USocialChatManager* CreateChatManager(USocialToolkit& InOwnerToolkit);`
- L56 _public prototype_ `USocialChatRoom* GetChatRoom(const FChatRoomId& ChannelId) const;`
- L57 _public prototype_ `virtual void GetJoinedChannels(TArray<USocialChatChannel*>& JoinedChannels) const;`
- L69 _public prototype_ `virtual void JoinChatRoomPublic(const FChatRoomId& RoomId, const FChatRoomConfig& InChatRoomConfig = FChatRoomConfig(), ESocialSubsystem InSocialSubsystem = ESocialSubsystem::Primary);`
- L70 _public prototype_ `virtual void JoinChatRoomPrivate(const FChatRoomId& RoomId, const FChatRoomConfig& InChatRoomConfig = FChatRoomConfig(), ESocialSubsystem InSocialSubsystem = ESocialSubsystem::Primary);`
- L72 _public prototype_ `virtual void ExitChatRoom(const FChatRoomId& RoomId, ESocialSubsystem InSocialSubsystem = ESocialSubsystem::Primary);`
- L74 _public prototype_ `DECLARE_EVENT_OneParam(USocialChatManager, FOnChatChannelCreated, USocialChatChannel&);`
- L75 _public function_ `virtual FOnChatChannelCreated& OnChannelCreated() const`
- L77 _public prototype_ `DECLARE_EVENT_OneParam(USocialChatManager, FOnChatChannelLeft, USocialChatChannel&);`
- L78 _public function_ `virtual FOnChatChannelLeft& OnChannelLeft() const`
- L85 _public prototype_ `virtual USocialChatChannel& CreateChatChannel(USocialUser& InRecipient);` — TODO - Deubanks - Move to Protected here (public version in UFortChatManager once it exists)
- L86 _public prototype_ `virtual USocialChatChannel* CreateChatChannel(FSocialChatChannelConfig& InConfig);`
- L88 _public prototype_ `DECLARE_EVENT_OneParam(USocialChatManager, FOnChatChannelFocusRequested, USocialChatChannel&);`
- L89 _public prototype_ `DECLARE_EVENT_OneParam(USocialChatManager, FOnChatChannelDisplayRequested, USocialChatChannel&);`
- L90 _public function_ `FOnChatChannelFocusRequested& OnChannelFocusRequested() const`
- L91 _public function_ `FOnChatChannelDisplayRequested& OnChannelDisplayRequested() const`
- L93 _public prototype_ `virtual void FocusChatChannel(USocialUser& InChannelUser);`
- L94 _public prototype_ `virtual void FocusChatChannel(USocialChatChannel& InChannel);`
- L95 _public prototype_ `virtual void DisplayChatChannel(USocialChatChannel& InChannel);`
- L97 _public prototype_ `virtual TSubclassOf<USocialChatRoom> GetClassForChatRoom(ESocialChannelType Type) const;`
- L98 _public function_ `virtual TSubclassOf<USocialChatChannel> GetClassForPrivateMessage() const`
- L101 _public function_ `virtual TSubclassOf<USocialChatChannel> GetClassForReadOnlyChannel() const` — @todo - don.eubanks - Maybe move this down into Fort level?
- L103 _public prototype_ `virtual bool IsChatRestricted() const;`
- L104 _public function_ `virtual TSubclassOf<USocialGroupChannel> GetClassForGroupChannel() const`
- L106 _public prototype_ `USocialToolkit& GetOwningToolkit() const;`
- L108 _public function_ `bool AreSlashCommandsEnabled()`
- L110 _public prototype_ `USocialChatChannel* GetChatRoomForType(ESocialChannelType Key);`
- L120 _public prototype_ `virtual void GetGroupChannels(TArray<USocialGroupChannel*>& JoinedChannels) const;`
- L126 _protected prototype_ `virtual void InitializeGroupChannels();`
- L127 _protected prototype_ `void LocalUserInitialized(USocialUser& LocalUser);`
- L128 _protected prototype_ `void RefreshGroupsRequestCompleted(FGroupsResult Result);`
- L130 _protected prototype_ `IOnlineGroupsPtr GetOnlineGroupInterface(ESocialSubsystem InSocialSubsystem = ESocialSubsystem::Primary) const;`
- L131 _protected prototype_ `USocialGroupChannel& FindOrCreateGroupChannel(IOnlineGroupsPtr InGroupInterface, const FUniqueNetId& GroupId);`
- L133 _protected prototype_ `void OnGroupUpdated(const FUniqueNetId& GroupId);`
- L135 _protected prototype_ `bool IsUniqueIdOfOwner(const FUniqueNetId& LocalUserId) const;`
- L141 _protected prototype_ `IOnlineChatPtr GetOnlineChatInterface(ESocialSubsystem InSocialSubsystem = ESocialSubsystem::Primary) const;`
- L142 _protected prototype_ `virtual void InitializeChatManager();`
- L143 _protected prototype_ `virtual ESocialChannelType TryChannelTypeLookupByRoomId(const FChatRoomId& RoomID);`
- L145 _protected prototype_ `virtual void HandleChatRoomMessageSent(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, bool bWasSuccessful, const FString& Error);`
- L146 _protected prototype_ `virtual void HandleChatRoomMessageReceived(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, const TSharedRef<FChatMessage>& ChatMessage);`
- L147 _protected prototype_ `virtual void HandleChatPrivateMessageSent(const FUniqueNetId& LocalUserId, const FUniqueNetId& RecipientId, bool bWasSuccessful, const FString& Error);`
- L148 _protected prototype_ `virtual void HandleChatPrivateMessageReceived(const FUniqueNetId& LocalUserId, const TSharedRef<FChatMessage>& ChatMessage);`
- L150 _protected prototype_ `virtual void OnChannelCreatedInternal(USocialChatChannel& CreatedChannel);`
- L151 _protected prototype_ `virtual void OnChannelLeftInternal(USocialChatChannel& ChannelLeft);`
- L153 _protected member_ `TMap < ESocialChannelType, TWeakObjectPtr<USocialChatChannel>> ChannelsByType;`
- L155 _protected prototype_ `USocialChatRoom& FindOrCreateRoom(const FChatRoomId& RoomId);`
- L156 _protected prototype_ `USocialChatChannel& FindOrCreateChannel(USocialUser& SocialUser);`
- L157 _protected prototype_ `USocialChatChannel& FindOrCreateChannel(const FText& DisplayName);`
- L159 _protected prototype_ `void HandleChatRoomCreated(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, bool bWasSuccessful, const FString& Error);`
- L160 _protected prototype_ `void HandleChatRoomConfigured(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, bool bWasSuccessful, const FString& Error);`
- L161 _protected prototype_ `void HandleChatRoomJoinPublic(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, bool bWasSuccessful, const FString& Error);`
- L162 _protected prototype_ `void HandleChatRoomJoinPrivate(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, bool bWasSuccessful, const FString& Error);`
- L163 _protected prototype_ `void HandleChatRoomExit(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, bool bWasSuccessful, const FString& Error);`
- L164 _protected prototype_ `void HandleChatRoomMemberJoin(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, const FUniqueNetId& MemberId);`
- L165 _protected prototype_ `void HandleChatRoomMemberExit(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, const FUniqueNetId& MemberId);`
- L166 _protected prototype_ `void HandleChatRoomMemberUpdate(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, const FUniqueNetId& MemberId);`
- L169 _protected function_ `virtual void HandleChatRoomCreatedFailure(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, const FString& Error)` — Failure handlers (called by HandleXXX functions above)
- L170 _protected function_ `virtual void HandleChatRoomConfiguredFailure(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, const FString& Error)`
- L171 _protected function_ `virtual void HandleChatRoomJoinPublicFailure(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, const FString& Error)`
- L172 _protected function_ `virtual void HandleChatRoomJoinPrivateFailure(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, const FString& Error)`
- L173 _protected function_ `virtual void HandleChatRoomExitFailure(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, const FString& Error)`
- L177 _protected member_ `TMap<TWeakObjectPtr<USocialUser>, TObjectPtr<USocialPrivateMessageChannel>> DirectChannelsByTargetUser;` — `UPROPERTY()`
- L180 _protected member_ `TMap<FString, TObjectPtr<USocialChatRoom>> ChatRoomsById;` — `UPROPERTY()`
- L183 _protected member_ `TMap<FString, TObjectPtr<USocialReadOnlyChatChannel>> ReadOnlyChannelsByDisplayName;` — `UPROPERTY()`
- L186 _protected member_ `bool bEnableChatSlashCommands = true;` — `UPROPERTY(config)`
- L189 _protected member_ `TMap<FUniqueNetIdRepl, TObjectPtr<USocialGroupChannel>> GroupChannels;` — `UPROPERTY()`
- L191 _protected member_ `mutable FOnChatChannelCreated OnChannelCreatedEvent;`
- L192 _protected member_ `mutable FOnChatChannelLeft OnChannelLeftEvent;`
- L193 _protected member_ `mutable FOnChatChannelFocusRequested OnChannelFocusRequestedEvent;`
- L194 _protected member_ `mutable FOnChatChannelDisplayRequested OnChannelDisplayRequestedEvent;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PARTY_API`
- L74 _delegate_ `DECLARE_EVENT_OneParam(USocialChatManager, FOnChatChannelCreated, USocialChatChannel&);`
- L77 _delegate_ `DECLARE_EVENT_OneParam(USocialChatManager, FOnChatChannelLeft, USocialChatChannel&);`
- L88 _delegate_ `DECLARE_EVENT_OneParam(USocialChatManager, FOnChatChannelFocusRequested, USocialChatChannel&);`
- L89 _delegate_ `DECLARE_EVENT_OneParam(USocialChatManager, FOnChatChannelDisplayRequested, USocialChatChannel&);`

### `Plugins/Online/OnlineFramework/Source/Party/Public/Chat/SocialChatMessage.h` (Public)


#### class `FSocialChatMessage`  
`class FSocialChatMessage : public TSharedFromThis<FSocialChatMessage>`  
_L23-68_
- inherits: `TSharedFromThis<FSocialChatMessage>`
- desc: Represents a single message sent within a chat channel
- L26 _public prototype_ `virtual ~FSocialChatMessage() = default;`
- L28 _public function_ `const FString& GetMessageBody() const`
- L29 _public function_ `const FDateTime& GetTimestamp() const`
- L32 _public function_ `template <typename ChatMessageT> ChatMessageT* AsTypedMessage()`
- L41 _public function_ `void SetPreviousMessage(TSharedPtr<FSocialChatMessage> InPrevious)`
- L42 _public function_ `TSharedPtr<FSocialChatMessage> GetPreviousMessage()`
- L44 _public prototype_ `virtual FString GetSourceName() const PURE_VIRTUAL(FSocialChatMessage::GetSourceName, return TEXT(""););`
- L45 _public function_ `ESocialChannelType GetSourceChannelType() const`
- L48 _protected function_ `FSocialChatMessage(const FString& InMessageBody, ESocialChannelType InSourceChannelType) : MessageBody(InMessageBody) , Timestamp(FDateTime::UtcNow()) , SourceChannelType(InSourceChannelType)`
- L54 _protected function_ `FSocialChatMessage(const FChatMessage& ChatMessage, ESocialChannelType InSourceChannelType) : MessageBody(ChatMessage.GetBody()) , Timestamp(ChatMessage.GetTimestamp()) , SourceChannelType(InSourceChannelType)`
- L60 _protected function_ `static FName StaticMessageType()`
- L61 _protected function_ `virtual bool IsDerivedFrom(FName MessageTypeName) const`
- L64 _private member_ `FString MessageBody;`
- L65 _private member_ `FDateTime Timestamp;`
- L66 _private member_ `TSharedPtr<FSocialChatMessage> PreviousMessage;`
- L67 _private member_ `ESocialChannelType SourceChannelType;`

#### class `FSocialUserChatMessage`  
`class FSocialUserChatMessage : public FSocialChatMessage`  
_L72-109_
- inherits: `FSocialChatMessage`
- desc: A chat message that originated from a particular SocialUser - by far the most common type of message
- L77 _public function_ `static FSocialChatMessageRef Create(USocialUser& Sender, const FChatMessage& Message, ESocialChannelType SourceChannelType)`
- L82 _public function_ `static FSocialChatMessageRef Create(USocialUser& Sender, const FString& MessageBody, ESocialChannelType SourceChannelType)`
- L87 _public prototype_ `virtual FString GetSourceName() const override;`
- L88 _public function_ `USocialUser* GetSender() const`
- L91 _protected function_ `FSocialUserChatMessage(USocialUser& Sender, const FChatMessage& Message, ESocialChannelType InSourceChannelType) : FSocialChatMessage(Message, InSourceChannelType) , FromUser(&Sender)`
- L96 _protected function_ `FSocialUserChatMessage(USocialUser& Sender, const FString& MessageBody, ESocialChannelType InSourceChannelType) : FSocialChatMessage(MessageBody, InSourceChannelType) , FromUser(&Sender)`
- L102 _protected function_ `FSocialUserChatMessage(const FString& MessageBody, ESocialChannelType InSourceChannelType) : FSocialChatMessage(MessageBody, InSourceChannelType) , FromUser(nullptr)`
- L108 _protected member_ `TWeakObjectPtr<USocialUser> FromUser;`

#### class `FSocialLocalChatMessage`  
`class FSocialLocalChatMessage : public FSocialChatMessage`  
_L115-129_
- inherits: `FSocialChatMessage`
- desc: A locally generated chat message that was not sent by a particular user. Use cases include server admin messages, in-game notifications, etc.
- L120 _public function_ `virtual FString GetSourceName() const override`
- L123 _protected function_ `FSocialLocalChatMessage(const FString& InSourceName, const FString& MessageBody, ESocialChannelType SourceChannelType) : FSocialChatMessage(MessageBody, SourceChannelType) , SourceName(InSourceName)`
- L128 _protected member_ `FString SourceName;`

#### enum `EChatSystemMessagePurpose`  
`enum class EChatSystemMessagePurpose : uint8`  
_L131-136_
- L133 _public enumerator_ `Info`
- L134 _public enumerator_ `Warning`
- L135 _public enumerator_ `Error`

#### class `FSocialSystemChatMessage`  
`class FSocialSystemChatMessage : public FSocialLocalChatMessage`  
_L138-155_
- inherits: `FSocialLocalChatMessage`
- L143 _public function_ `static FSocialChatMessageRef Create(const FString& InSourceName, const FString& InMessageBody, ESocialChannelType InSourceChannelType, EChatSystemMessagePurpose InPurpose)`
- L149 _protected function_ `FSocialSystemChatMessage(const FString& InSourceName, const FString& InMessageBody, ESocialChannelType InSourceChannelType, EChatSystemMessagePurpose InPurpose) : FSocialLocalChatMessage(InSourceName, InMessageBody, InSourceChannelType) , Purpose(InPurpose)`
- L154 _protected member_ `EChatSystemMessagePurpose Purpose;`

#### class `FDesignerPreviewSocialUserChatMessage`  
`class FDesignerPreviewSocialUserChatMessage : public FSocialUserChatMessage`  
_L158-177_
- inherits: `FSocialUserChatMessage`
- L163 _public function_ `static FSocialChatMessageRef Create(FString& InSenderName, const FString& MessageBody, ESocialChannelType SourceChannelType)`
- L168 _public function_ `virtual FString GetSourceName() const override`
- L171 _protected function_ `FDesignerPreviewSocialUserChatMessage(FString& InSenderName, const FString& InMessage, ESocialChannelType InSourceChannelType) : FSocialUserChatMessage(InMessage, InSourceChannelType) , SenderName(InSenderName)`
- L176 _protected member_ `FString SenderName;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PARTY_API`
- L16 _macro_ `#define DERIVED_CHAT_MESSAGE(MessageType, ParentMessageType) \` — Barebones RTTI for chat messages to allow games to generate messages of custom types. The alternative is to make them UObjects, but for the potential quantity of objects in play with messages, that feels unwise

### `Plugins/Online/OnlineFramework/Source/Party/Public/Chat/SocialChatRoom.h` (Public)


#### class `USocialChatRoom`  
`class USocialChatRoom : public USocialChatChannel`  
_L14-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USocialChatChannel`
- desc: A multi-user chat room channel. Used for all chat situations outside of private user-to-user direct messages.
- L19 _public prototype_ `virtual void Initialize(USocialUser* InSocialUser, const FChatRoomId& InChannelId, ESocialChannelType InSourceChannelType);`
- L25 _public prototype_ `virtual bool SendMessage(const FString& InMessage) override;`
- L26 _public function_ `const FChatRoomId& GetChatRoomId() const`
- L34 _public prototype_ `virtual const FText DetermineChannelDisplayName(ESocialChannelType InSourceChannelType, const FChatRoomId& InRoomId);` — virtual bool HasUnreadMessages() const override;
- L37 _private function_ `void SetRoomId(const FChatRoomId& Id)`
- L39 _private member_ `FChatRoomId RoomId;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PARTY_API`

### `Plugins/Online/OnlineFramework/Source/Party/Public/Chat/SocialGroupChannel.h` (Public)


#### class `USocialGroupChannel`  
`class USocialGroupChannel : public UObject`  
_L17-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L22 _public prototype_ `USocialGroupChannel();`
- L24 _public prototype_ `void Initialize(IOnlineGroupsPtr InGroupInterface, USocialUser& InSocialUser, const FUniqueNetId& InGroupId);`
- L26 _public function_ `void SetDisplayName(const FText& InDisplayName)`
- L27 _public function_ `FText GetDisplayName() const`
- L29 _public function_ `const TArray<USocialUser*>& GetMembers() const`
- L32 _private prototype_ `void RefreshCompleted_GroupInfo(FGroupsResult Result);`
- L33 _private prototype_ `void RefreshCompleted_Roster(FGroupsResult Result);`
- L37 _private member_ `TObjectPtr<USocialUser> SocialUser;` — `UPROPERTY()`
- L40 _private member_ `FUniqueNetIdRepl GroupId;` — `UPROPERTY()`
- L43 _private member_ `FText DisplayName;` — `UPROPERTY()`
- L46 _private member_ `TArray<TObjectPtr<USocialUser>> Members;` — `UPROPERTY()`
- L48 _private member_ `TWeakPtr<IOnlineGroups, ESPMode::ThreadSafe> GroupInterfacePtr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PARTY_API`

### `Plugins/Online/OnlineFramework/Source/Party/Public/Chat/SocialPartyChatRoom.h` (Public)


#### class `USocialPartyChatRoom`  
`class USocialPartyChatRoom : public USocialChatRoom`  
_L18-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USocialChatRoom`
- desc: A multi-user chat room channel. Used for all chat situations outside of private user-to-user direct messages.
- L23 _public prototype_ `virtual void Initialize(USocialUser* InSocialUser, const FChatRoomId& InChannelId, ESocialChannelType InSourceChannelType);`
- L26 _protected prototype_ `virtual void HandlePartyMemberLeft(EMemberExitedReason Reason);`
- L27 _protected prototype_ `virtual void HandlePartyMemberJoined(UPartyMember& NewMember);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PARTY_API`

### `Plugins/Online/OnlineFramework/Source/Party/Public/Chat/SocialPrivateMessageChannel.h` (Public)


#### class `USocialPrivateMessageChannel`  
`class USocialPrivateMessageChannel : public USocialChatChannel`  
_L15-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USocialChatChannel`
- desc: A modified version of a chat room that only contains two participants - the current user and a private recipient of their messages. This is equivalent to sending a "whisper".
- L20 _public prototype_ `virtual void Initialize(USocialUser* InSocialUser, const FChatRoomId& InChannelId, ESocialChannelType InSourceChannelType) override;`
- L22 _public prototype_ `virtual bool SendMessage(const FString& InMessage) override;`
- L24 _public prototype_ `USocialUser& GetTargetUser() const;`
- L27 _private prototype_ `void SetTargetUser(USocialUser& InTargetUser);`
- L31 _private member_ `TObjectPtr<USocialUser> TargetUser;` — `UPROPERTY()` — The recipient of the current user's messages

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PARTY_API`

### `Plugins/Online/OnlineFramework/Source/Party/Public/Chat/SocialReadOnlyChatChannel.h` (Public)


#### class `USocialReadOnlyChatChannel`  
`class USocialReadOnlyChatChannel : public USocialChatChannel`  
_L16-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USocialChatChannel`
- desc: A strawman chat channel that relies exclusively on other channels messages for content, does not support sending messages
- L21 _public prototype_ `virtual void Initialize(USocialUser* InSocialUser, const FChatRoomId& InChannelId, ESocialChannelType InSourceChannelType) override;`
- L23 _public prototype_ `virtual bool SendMessage(const FString& InMessage) override;`
- L25 _public function_ `virtual bool SupportsMessageSending() const override`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PARTY_API`

### `Plugins/Online/OnlineFramework/Source/Party/Public/Chatroom.h` (Public)


#### class `UChatroom`  
`class UChatroom : public UObject`  
_L33-134_
- reflection: `UCLASS(MinimalAPI, Config = Game)`
- inherits: `UObject`
- desc: Helper class for maintaining a single chat room at the game level
- L40 _public prototype_ `UChatroom();` — Ctor
- L57 _public prototype_ `void CreateOrJoinChatRoom(FUniqueNetIdRepl LocalUserId, FChatRoomId ChatRoomId, FOnChatRoomCreatedOrJoined CompletionDelegate, FChatRoomConfig RoomConfig = FChatRoomConfig());` — Try to join a chat room by calling CreateRoom, will either create or join if it already exists @param LocalUserId local user that will be joining the room @param ChatRoomId chat room id to connect with @param CompletionDelegate delegate fired when operation completes @param RoomConfig optional room configuration NOTE: All parameters are by value because ClearTimer/SetTimer can destroy the internal lambda function
- L65 _public prototype_ `void LeaveChatRoom(const FUniqueNetIdRepl& LocalUserId, const FOnChatRoomLeft& CompletionDelegate);` — Leave the joined chat room @param LocalUserId user leaving the chat room @param CompletionDelegate delegate fired when operation completes
- L79 _private prototype_ `void OnChatRoomCreatedOrJoined(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, bool bWasSuccessful, const FString& Error, FOnChatRoomCreatedOrJoined CompletionDelegate, FChatRoomConfig RoomConfig);` — Delegate fired after CreateOrJoinChatRoom completes @param LocalUserId user joining the chat room @param RoomId id of room joined @param bWasSuccessful was the join successful @param Error error string if not successful @param CompletionDelegate user passed in delegate @param RoomConfig room configuration from previous call if needed on retry
- L91 _private prototype_ `void OnChatRoomLeft(const FUniqueNetId& LocalUserId, const FChatRoomId& RoomId, bool bWasSuccessful, const FString& Error, FChatRoomId ChatRoomIdCopy, FOnChatRoomLeft CompletionDelegate);` — Delegate fired after LeaveChatRoom completes @param LocalUserId user leaving the chat room @param RoomId id of room left @param bWasSuccessful was the leave successful @param Error error string if not successful @param ChatRoomIdCopy room we are trying to leave @param CompletionDelegate user passed in delegate
- L99 _private prototype_ `void ChatRoomLeftInternal(const FChatRoomId& RoomId, const FOnChatRoomLeft& CompletionDelegate);` — Common code called at the end of chat room cleanup @param RoomId id of the room let @param CompletionDelegate delegate to fire to notify that the room has been left
- L105 _private member_ `FString CurrentChatRoomId;` — `UPROPERTY()` — Current chat room associated with this object (FString so UPROPERTY works)
- L109 _private member_ `int32 MaxChatRoomRetries;` — `UPROPERTY()` — Max number of retries before giving up on chat
- L113 _private member_ `int32 NumChatRoomRetries;` — `UPROPERTY()` — Current number of retries on a chat room
- L116 _private member_ `FTimerHandle ChatRoomRetryTimerHandle;` — Handle on chat room retry timer
- L119 _private member_ `FDelegateHandle ChatRoomCreatedDelegateHandle;` — OSS delegate handles
- L120 _private member_ `FDelegateHandle ChatRoomLeftDelegateHandle;`
- L124 _protected prototype_ `void UnregisterDelegates();`
- L127 _protected prototype_ `virtual bool IsOnline() const;` — @return true if the local player is signed in, false otherwise
- L130 _protected prototype_ `bool IsAlreadyInChatRoom(const FUniqueNetIdRepl& LocalUserId, const FChatRoomId& ChatRoomId) const;` — @return true if the user is already logged as being a part of a given chat room, false otherwise
- L132 _protected prototype_ `UWorld* GetWorld() const;`
- L133 _protected prototype_ `FTimerManager& GetTimerManager() const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PARTY_API`
- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnChatRoomCreatedOrJoined, const FChatRoomId& , bool );` — Delegate fired when chat room attempt has completed @param ChatRoomId id of room joined @param bAvailable has a chat room been joined
- L20 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnChatRoomCreatedOrJoined, const FChatRoomId& , bool );` — Delegate fired when chat room attempt has completed @param ChatRoomId id of room joined @param bAvailable has a chat room been joined
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnChatRoomLeft, const FChatRoomId& );` — Delegate fired when chat room has been left @param ChatRoomId id of room left
- L27 _prototype_ `DECLARE_DELEGATE_OneParam(FOnChatRoomLeft, const FChatRoomId& );` — Delegate fired when chat room has been left @param ChatRoomId id of room left

### `Plugins/Online/OnlineFramework/Source/Party/Public/Interactions/CoreInteractions.h` (Public)
_(no declarations extracted)_

### `Plugins/Online/OnlineFramework/Source/Party/Public/Interactions/PartyInteractions.h` (Public)
_(no declarations extracted)_

### `Plugins/Online/OnlineFramework/Source/Party/Public/Interactions/SocialInteractionHandle.h` (Public)


#### class `FSocialInteractionHandle`  
`class FSocialInteractionHandle`  
_L19-41_
- desc: Represents a single discrete interaction between a local player and another user. Useful for when you'd like to create some tangible list of interactions to compare/sort/classify/iterate. Not explicitly required if you have a particular known interaction in mind - feel free to access the static API of a given interaction directly.
- L22 _public function_ `FSocialInteractionHandle()`
- L24 _public prototype_ `bool IsValid() const;`
- L25 _public prototype_ `bool operator==(const FSocialInteractionHandle& Other) const;`
- L26 _public function_ `bool operator!=(const FSocialInteractionHandle& Other) const`
- L28 _public prototype_ `FName GetInteractionName() const;`
- L29 _public prototype_ `FText GetDisplayName(const USocialUser& User) const;`
- L30 _public prototype_ `FString GetSlashCommandToken() const;`
- L32 _public prototype_ `bool IsAvailable(const USocialUser& User) const;`
- L33 _public prototype_ `void ExecuteInteraction(USocialUser& User) const;`
- L34 _public prototype_ `void ExecuteInteractionWithContext(USocialUser& User, const TMap<FString, FString>& AnalyticsContext) const;`
- L38 _private prototype_ `template <typename> friend class TSocialInteractionWrapper;`
- L40 _private member_ `const ISocialInteractionWrapper* InteractionWrapper = nullptr;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API PARTY_API`

### `Plugins/Online/OnlineFramework/Source/Party/Public/Interactions/SocialInteractionMacros.h` (Public)


#### class `ISocialInteractionWrapper`  
`class ISocialInteractionWrapper`  
_L14-26_
- desc: Link between the class-polymorphism-based interaction handle and the static template-polymorphism-based interactions. Implementation detail, automatically set up and utilized in the DECLARE_SOCIAL_INTERACTION macros above
- L17 _public prototype_ `virtual ~ISocialInteractionWrapper() = default;`
- L19 _public prototype_ `virtual FName GetInteractionName() const = 0;`
- L20 _public prototype_ `virtual FText GetDisplayName(const USocialUser& User) const = 0;`
- L21 _public prototype_ `virtual FString GetSlashCommandToken() const = 0;`
- L23 _public prototype_ `virtual bool IsAvailable(const USocialUser& User) const = 0;`
- L24 _public prototype_ `virtual void ExecuteInteraction(USocialUser& User) const = 0;`
- L25 _public prototype_ `virtual void ExecuteInteractionWithContext(USocialUser& User, const TMap<FString, FString>& AnalyticsContext) const = 0;`

#### class `TSocialInteractionWrapper`  
`template <typename InteractionT> class TSocialInteractionWrapper : public ISocialInteractionWrapper`  
_L29-45_
- inherits: `ISocialInteractionWrapper`
- L32 _public function_ `virtual FName GetInteractionName() const override final`
- L33 _public function_ `virtual FText GetDisplayName(const USocialUser& User) const override final`
- L34 _public function_ `virtual FString GetSlashCommandToken() const override final`
- L36 _public function_ `virtual bool IsAvailable(const USocialUser& User) const override final`
- L37 _public function_ `virtual void ExecuteInteraction(USocialUser& User) const override final`
- L38 _public function_ `virtual void ExecuteInteractionWithContext(USocialUser& User, const TMap<FString, FString>& AnalyticsContext) const override final`
- L42 _private function_ `TSocialInteractionWrapper()`
- L44 _private function_ `FSocialInteractionHandle GetHandle() const`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnCustomIsInteractionAvailable, const USocialUser&);`
- L8 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnCustomIsInteractionAvailable, const USocialUser&);`
- L51 _macro_ `#define DECLARE_SOCIAL_INTERACTION_EXPORT(APIMacro, InteractionName) \`
- L69 _macro_ `#define DEFINE_SOCIAL_INTERACTION(InteractionName) \`
- L100 _macro_ `#define DECLARE_SOCIAL_INTERACTION(InteractionName) DECLARE_SOCIAL_INTERACTION_EXPORT(, InteractionName)`

### `Plugins/Online/OnlineFramework/Source/Party/Public/Party/PartyDataReplicator.h` (Public)


#### class `FPartyDataReplicatorHelper`  
`class FPartyDataReplicatorHelper`  
_L22-26_
- desc: Util exclusively for use by TPartyDataReplicator to circumvent circular include header issues (we can't include SocialParty.h or PartyMember.h here)
- L25 _private prototype_ `template <typename, class> friend class TPartyDataReplicator;`

#### class `TPartyDataReplicator`  
`template <typename RepDataT, class OwningObjectT> class TPartyDataReplicator : public FGCObject`  
_L30-317_
- inherits: `FGCObject`
- desc: Base util class for dealing with data that is replicated to party members
- L36 _public function_ `~TPartyDataReplicator()`
- L41 _public function_ `const RepDataT* operator->() const`
- L42 _public function_ `RepDataT* operator->()`
- L43 _public function_ `const RepDataT& operator*() const`
- L44 _public function_ `RepDataT& operator*()`
- L46 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L51 _public function_ `virtual FString GetReferencerName() const override`
- L56 _public function_ `bool IsValid() const`
- L59 _public function_ `template <typename ChildRepDataT> void EstablishRepDataInstance(ChildRepDataT& RepDataInstance)`
- L73 _public function_ `void Flush()`
- L86 _protected function_ `void ProcessReceivedData(TNotNull<OwningObjectT*> Owner, const FOnlinePartyData& IncomingPartyData, bool bCompareToPrevious = true)`
- L164 _protected function_ `void Reset()`
- L204 _private function_ `void HandleRepDataChanged()`
- L212 _private function_ `bool DeferredHandleReplicateChanges(float)`
- L230 _private function_ `void PostReceiveData(const FOnlineKeyValuePairs<FString, FVariantData>& KeyValueAttrs, bool bCompareToPrevious, TSharedPtr<FStreamableHandle> ResourceHandle = nullptr)`
- L261 _private function_ `void ProcessLoadQueue()`
- L299 _private member_ `TArray<FQueuedRepData> RepDataLoadQueue;` — New rep data that is currently async loading any required assets before it can be applied.
- L302 _private member_ `TObjectPtr<const UScriptStruct> RepDataType = nullptr;` — Reflection data for child USTRUCT
- L308 _private member_ `RepDataT* RepDataPtr = nullptr;` — Pointer to child UStruct that holds the current state of the party. Only modifiable by party leader. To establish a custom state struct, call EstablishPartyState<T> with the desired type within the child class's constructor
- L311 _private member_ `RepDataT* RepDataCopy = nullptr;` — Scratch copy of child UStruct for handling replication comparisons
- L314 _private member_ `RepDataT* PendingRepData = nullptr;` — Scratch copy of child UStruct for storing incoming rep data to query it prior to replication.
- L316 _private member_ `FTSTicker::FDelegateHandle UpdateTickerHandle;`

#### struct `TPartyDataReplicator::FQueuedRepData`  
`struct FQueuedRepData`  
_L290-296_
- L292 _public member_ `TSharedPtr<FStreamableHandle> LoadHandle;`
- L293 _public member_ `FOnlineKeyValuePairs<FString, FVariantData> KeyValueAttrs;`
- L294 _public member_ `int32 Id = 0;`
- L295 _public member_ `bool bCompareToPrevious = false;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Party` (scope `UE`)
- L18 _prototype_ `bool IsRepDataAsyncLoadingEnabled();` (scope `UE::Party`)
- L140 _function_ `` (scope `TPartyDataReplicator::ProcessReceivedData`)

### `Plugins/Online/OnlineFramework/Source/Party/Public/Party/PartyMember.h` (Public)


#### struct `FPartyMemberPlatformData`  
`struct FPartyMemberPlatformData`  
_L22-44_
- reflection: `USTRUCT()`
- desc: Platform data fields for party replication
- L27 _public function_ `bool operator==(const FPartyMemberPlatformData& Other) const`
- L28 _public function_ `bool operator!=(const FPartyMemberPlatformData& Other) const`
- L32 _public member_ `FUserPlatform Platform;` — `UPROPERTY()` — Native platform on which this party member is playing.
- L36 _public member_ `FUniqueNetIdRepl UniqueId;` — `UPROPERTY()` — Net ID for this party member on their native platform. Blank if this member has no Platform SocialSubsystem.
- L43 _public member_ `FString SessionId;` — `UPROPERTY()` — The platform session this member is in. Can be blank for a bit while creating/joining. Only relevant when this member is on a platform that requires a session backing the party.

#### struct `FPartyMemberJoinInProgressRequest`  
`struct FPartyMemberJoinInProgressRequest`  
_L48-63_
- reflection: `USTRUCT()`
- desc: Join in progress request. Represents a request from a local party member to a remote party member to acquire a reservation for the session the remote party member is in.
- L53 _public function_ `bool operator==(const FPartyMemberJoinInProgressRequest& Other) const`
- L54 _public function_ `bool operator!=(const FPartyMemberJoinInProgressRequest& Other) const`
- L58 _public member_ `FUniqueNetIdRepl Target;` — `UPROPERTY()` — Remote member we want to join.
- L62 _public member_ `int64 Time = 0;` — `UPROPERTY()` — Time the request was made.

#### struct `FPartyMemberJoinInProgressResponse`  
`struct FPartyMemberJoinInProgressResponse`  
_L67-99_
- reflection: `USTRUCT()`
- desc: Join in progress response. Represents a response from a local party member to a remote party member that requested to join in progress.
- L72 _public function_ `bool operator==(const FPartyMemberJoinInProgressResponse& Other) const`
- L79 _public function_ `bool operator!=(const FPartyMemberJoinInProgressResponse& Other) const`
- L83 _public member_ `FUniqueNetIdRepl Requester;` — `UPROPERTY()` — Remote member that this response is for.
- L87 _public member_ `int64 RequestTime = 0;` — `UPROPERTY()` — Time the request was made. Matches FPartyMemberJoinInProgressRequest::Time
- L91 _public member_ `int64 ResponseTime = 0;` — `UPROPERTY()` — Time the response was made.
- L98 _public member_ `uint8 DenialReason = 0;` — `UPROPERTY()` — Result of session reservation attempt. @see EPartyJoinDenialReason

#### struct `FPartyMemberJoinInProgressData`  
`struct FPartyMemberJoinInProgressData`  
_L103-119_
- reflection: `USTRUCT()`
- desc: Join in progress data. Holds the current request and any responses. Requests and responses are expected to be cleared in a short amount of time. Combined into one field to reduce field count.
- L109 _public function_ `bool operator==(const FPartyMemberJoinInProgressData& Other) const`
- L110 _public function_ `bool operator!=(const FPartyMemberJoinInProgressData& Other) const`
- L114 _public member_ `FPartyMemberJoinInProgressRequest Request;` — `UPROPERTY()` — Current request for the local member.
- L118 _public member_ `TArray<FPartyMemberJoinInProgressResponse> Responses;` — `UPROPERTY()` — List of responses for other members who requested a reservation.

#### struct `FPartyMemberRepData`  
`struct FPartyMemberRepData : public FOnlinePartyRepDataBase`  
_L123-180_
- reflection: `USTRUCT()`
- inherits: `FOnlinePartyRepDataBase`
- desc: Base struct used to replicate data about the state of a single party member to all members.
- L128 _public function_ `FPartyMemberRepData()`
- L129 _public function_ `FPartyMemberRepData& operator=(const FPartyMemberRepData& Other)`
- L144 _public prototype_ `virtual void SetOwningMember(const class UPartyMember& InOwnerMember);`
- L146 _public prototype_ `void MarkOwnerless();` — Mark the party data as ownerless. This will bypass any "CanEdit" checks. Useful for using this object in a test context.
- L149 _protected prototype_ `virtual bool CanEditData() const override;`
- L150 _protected prototype_ `virtual void CompareAgainst(const FOnlinePartyRepDataBase& OldData) const override;`
- L151 _protected prototype_ `virtual const USocialParty* GetOwnerParty() const override;`
- L152 _protected prototype_ `virtual const UPartyMember* GetOwningMember() const;`
- L155 _private member_ `TWeakObjectPtr<const UPartyMember> OwnerMember;`
- L156 _private member_ `bool bAllowOwnerless = false;`
- L160 _private member_ `FPartyMemberPlatformData PlatformData;` — `UPROPERTY()` — Platform data fields for party replication
- L167 _private member_ `ECrossplayPreference CrossplayPreference = ECrossplayPreference::NoSelection;` — `UPROPERTY()` — The crossplay preference of this user. Only relevant to crossplay party scenarios.
- L168 _private prototype_ `EXPOSE_REP_DATA_PROPERTY(FPartyMemberRepData, ECrossplayPreference, CrossplayPreference);`
- L172 _private member_ `FString JoinMethod;` — `UPROPERTY()` — Method used to join the party
- L173 _private prototype_ `EXPOSE_REP_DATA_PROPERTY(FPartyMemberRepData, FString, JoinMethod);`
- L177 _private member_ `FPartyMemberJoinInProgressData JoinInProgressData;` — `UPROPERTY()` — Data used for join in progress flow.
- L178 _private prototype_ `EXPOSE_USTRUCT_REP_DATA_PROPERTY(FPartyMemberRepData, FPartyMemberJoinInProgressRequest, JoinInProgressData, Request);`
- L179 _private prototype_ `EXPOSE_USTRUCT_REP_DATA_PROPERTY(FPartyMemberRepData, TArray<FPartyMemberJoinInProgressResponse>, JoinInProgressData, Responses);`

#### class `UPartyMember`  
`class UPartyMember : public UObject`  
_L185-295_
- reflection: `UCLASS(MinimalAPI, Abstract, config = Game, Within = SocialParty, Transient)`
- inherits: `UObject`
- L193 _public prototype_ `UPartyMember();`
- L195 _public prototype_ `virtual void BeginDestroy() override;`
- L197 _public prototype_ `bool CanPromoteToLeader(const ULocalPlayer& PerformingPlayer) const;`
- L198 _public prototype_ `bool PromoteToPartyLeader(const ULocalPlayer& PerformingPlayer);`
- L199 _public prototype_ `bool CanKickFromParty(const ULocalPlayer& PerformingPlayer) const;`
- L200 _public prototype_ `bool KickFromParty(const ULocalPlayer& PerformingPlayer);`
- L202 _public prototype_ `bool IsInitialized() const;`
- L203 _public prototype_ `bool IsPartyLeader() const;`
- L204 _public prototype_ `bool IsLocalPlayer() const;`
- L206 _public prototype_ `USocialParty& GetParty() const;`
- L207 _public prototype_ `FUniqueNetIdRepl GetPrimaryNetId() const;`
- L208 _public function_ `const FPartyMemberRepData& GetRepData() const`
- L210 _public prototype_ `USocialUser& GetSocialUser() const;` — Get the default social user. NOTE: This method will be deprecated in the future. Prefer GetSocialUser(InLocalUserId).
- L216 _public prototype_ `USocialUser* GetSocialUser(const FUniqueNetIdRepl& InLocalUserId) const;` — Get the social user for a local player @param InLocalUserId the primary user id of the local user to get the social user for. @return the social user registered for this party member and local user. May be null if InLocalUserId does not map to a social toolkit, otherwise expected to be non-null.
- L218 _public prototype_ `EMemberConnectionStatus GetMemberConnectionStatus() const;`
- L220 _public prototype_ `FString GetDisplayName() const;`
- L221 _public prototype_ `FName GetPlatformOssName() const;`
- L223 _public prototype_ `DECLARE_EVENT(UPartyMember, FOnPartyMemberStateChanged);`
- L224 _public function_ `FOnPartyMemberStateChanged& OnInitializationComplete() const`
- L225 _public function_ `FOnPartyMemberStateChanged& OnPromotedToLeader() const`
- L226 _public function_ `FOnPartyMemberStateChanged& OnDemoted() const`
- L227 _public function_ `FOnPartyMemberStateChanged& OnMemberConnectionStatusChanged() const`
- L228 _public function_ `FOnPartyMemberStateChanged& OnDisplayNameChanged() const`
- L230 _public function_ `DECLARE_EVENT_OneParam(UPartyMember, FOnPartyMemberLeft, EMemberExitedReason) FOnPartyMemberLeft& OnLeftParty() const`
- L233 _public prototype_ `FString ToDebugString(bool bIncludePartyId = true) const;`
- L236 _protected prototype_ `void InitializePartyMember(const FOnlinePartyMemberConstRef& OssMember, FSimpleDelegate&& OnInitComplete);`
- L238 _protected function_ `FPartyMemberRepData& GetMutableRepData()`
- L239 _protected prototype_ `void NotifyMemberDataReceived(const FOnlinePartyData& MemberData);`
- L240 _protected prototype_ `void NotifyMemberPromoted();`
- L241 _protected prototype_ `void NotifyMemberDemoted();`
- L242 _protected prototype_ `void NotifyRemovedFromParty(EMemberExitedReason ExitReason);`
- L245 _protected prototype_ `virtual void FinishInitializing();`
- L246 _protected prototype_ `virtual void InitializeLocalMemberRepData();`
- L248 _protected prototype_ `virtual void OnMemberPromotedInternal();`
- L249 _protected prototype_ `virtual void OnMemberDemotedInternal();`
- L250 _protected prototype_ `virtual void OnRemovedFromPartyInternal(EMemberExitedReason ExitReason);`
- L251 _protected prototype_ `virtual void Shutdown();`
- L253 _protected member_ `FPartyMemberDataReplicator MemberDataReplicator;`
- L255 _protected function_ `TSharedPtr<const FOnlinePartyMember> GetOSSPartyMember() const`
- L258 _private prototype_ `void InitializeSocialUserForToolkit(USocialToolkit& Toolkit);`
- L259 _private prototype_ `void HandleSocialUserInitialized(USocialUser& InitializedUser);`
- L260 _private prototype_ `void HandleMemberConnectionStatusChanged(const FUniqueNetId& ChangedUserId, const EMemberConnectionStatus NewMemberConnectionStatus, const EMemberConnectionStatus PreviousMemberConnectionStatus);`
- L261 _private prototype_ `void HandleMemberAttributeChanged(const FUniqueNetId& ChangedUserId, const FString& Attribute, const FString& NewValue, const FString& OldValue);`
- L262 _private prototype_ `void OnSocialToolkitCreated(USocialToolkit& Toolkit);`
- L263 _private prototype_ `void OnSocialToolkitDestroyed(USocialToolkit& Toolkit);`
- L264 _private prototype_ `void OnSocialToolkitLoggedIn(USocialToolkit& Toolkit);`
- L266 _private member_ `FOnlinePartyMemberConstPtr OssPartyMember;`
- L269 _private member_ `TObjectPtr<USocialUser> DefaultSocialUser = nullptr;` — `UPROPERTY()`
- L278 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(EInitializingFlags);`
- L279 _private member_ `EInitializingFlags InitializingFlags = EInitializingFlags::Done;`
- L282 _private member_ `bool bEnableDebugInitializer = true;` — `UPROPERTY(config)`
- L287 _private member_ `TUniquePtr<FDebugInitializer> DebugInitializer;`
- L289 _private member_ `mutable FOnPartyMemberStateChanged OnMemberConnectionStatusChangedEvent;`
- L290 _private member_ `mutable FOnPartyMemberStateChanged OnDisplayNameChangedEvent;`
- L291 _private member_ `mutable FOnPartyMemberStateChanged OnMemberInitializedEvent;`
- L292 _private member_ `mutable FOnPartyMemberStateChanged OnPromotedToLeaderEvent;`
- L293 _private member_ `mutable FOnPartyMemberStateChanged OnDemotedEvent;`
- L294 _private member_ `mutable FOnPartyMemberLeft OnLeftPartyEvent;`

#### enum `UPartyMember::EInitializingFlags`  
`enum class EInitializingFlags : uint8`  
_L272-277_
- desc: Initializing status
- L274 _public enumerator_ `Done = 0` — Done initializing
- L275 _public enumerator_ `SocialUsers = 1<<0` — Waiting for all social users to initialize
- L276 _public enumerator_ `InitialMemberData = 1<<1` — Waiting to receive initial member data

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PARTY_API`
- L182 _typedef_ `using FPartyMemberDataReplicator = TPartyDataReplicator<FPartyMemberRepData, UPartyMember>;`
- L223 _delegate_ `DECLARE_EVENT(UPartyMember, FOnPartyMemberStateChanged);`
- L230 _delegate_ `DECLARE_EVENT_OneParam(UPartyMember, FOnPartyMemberLeft, EMemberExitedReason) FOnPartyMemberLeft& OnLeftParty() const { return OnLeftPartyEvent; } FString ToDebugString(bool bIncludePartyId = true) const;`
- L297 _namespace_ `namespace UE`
- L297 _namespace_ `namespace OnlineFramework` (scope `UE`)
- L305 _prototype_ `void OnPartyMemberInitializeComplete(UPartyMember& InPartyMember, FSimpleDelegate&& InDelegate);` (scope `UE::OnlineFramework`) — Utility method to trigger a delegate when a party member is initialized, or trigger immediately if already initialized. Avoids needing to use the pattern 'if (Member->IsInitialized()) { DoWork(); } else { Member->OnInitializationComplete().Add...' @param InPartyMember the party member @param InDelegate the delegate to trigger when initialization is complete (or trigger immediately if already initialized)

### `Plugins/Online/OnlineFramework/Source/Party/Public/Party/PartyTypes.h` (Public)


#### enum `EPartyType`  
`enum class EPartyType : uint8`  
_L22-30_
- reflection: `UENUM()`
- L25 _public enumerator_ `Public` — This party is public (not really supported right now)
- L27 _public enumerator_ `FriendsOnly` — This party is joinable by friends
- L29 _public enumerator_ `Private` — This party requires an invite from someone within the party

#### enum `EPartyInviteRestriction`  
`enum class EPartyInviteRestriction : uint8`  
_L33-41_
- reflection: `UENUM()`
- L36 _public enumerator_ `AnyMember` — Any party member can send invites
- L38 _public enumerator_ `LeaderOnly` — Only the leader can send invites
- L40 _public enumerator_ `NoInvites` — Nobody can invite anyone to this party

#### enum `EPartyJoinDenialReason`  
`enum class EPartyJoinDenialReason : uint8`  
_L44-148_
- reflection: `UENUM()`
- L49 _public enumerator_ `NoReason = 0` — No denial, matches success internally
- L51 _public enumerator_ `JoinAttemptAborted` — The local player aborted the join attempt
- L53 _public enumerator_ `Busy` — Party leader is busy or at inopportune time to allow joins - to be used as a fallback when there isn't a more specific reason (more specific reasons are preferred)
- L55 _public enumerator_ `OssUnavailable` — Either the necessary OSS itself or critical element thereof (PartyInterface, SessionInterface, etc.) is missing.
- L57 _public enumerator_ `PartyFull` — Party is full
- L59 _public enumerator_ `GameFull` — Game is full, but not party
- L61 _public enumerator_ `NotPartyLeader` — Asked a non party leader to join game, shouldn't happen
- L63 _public enumerator_ `PartyPrivate` — Party has been marked as private and the join request is revoked
- L65 _public enumerator_ `JoinerCrossplayRestricted` — Player has crossplay restriction that would be violated
- L67 _public enumerator_ `MemberCrossplayRestricted` — Party member has crossplay restriction that would be violated
- L69 _public enumerator_ `GameModeRestricted` — Player is in a game mode that restricts joining
- L71 _public enumerator_ `Banned` — Player is currently banned
- L73 _public enumerator_ `NotLoggedIn` — Player is not yet logged in
- L75 _public enumerator_ `CheckingForRejoin` — Unable to start joining - we are checking for a session to rejoin
- L77 _public enumerator_ `TargetUserMissingPresence` — The target user is missing presence info
- L79 _public enumerator_ `TargetUserUnjoinable` — The target user's presence says the user is unjoinable
- L81 _public enumerator_ `TargetUserAway` — The target user is currently Away
- L83 _public enumerator_ `AlreadyLeaderInPlatformSession` — We found ourself to be the leader of the friend's party according to the console session
- L85 _public enumerator_ `TargetUserPlayingDifferentGame` — The target user is not playing the same game as us
- L87 _public enumerator_ `TargetUserMissingPlatformSession` — The target user's presence does not have any information about their party session (platform friends only)
- L89 _public enumerator_ `PlatformSessionMissingJoinInfo` — There is no party join info available in the target user's platform session
- L91 _public enumerator_ `FailedToStartFindConsoleSession` — We were unable to launch the query to find the platform friend's session (platform friends only)
- L93 _public enumerator_ `MissingPartyClassForTypeId` — The party is of a type that the game does not support (it specified nullptr for the USocialParty class)
- L95 _public enumerator_ `TargetUserBlocked` — The target user is blocked by the local user on one or more of the active subsystems
- L97 _public enumerator_ `InvalidJoinInfo` — Failed to get party join info from target user
- L99 _public enumerator_ `NotFriends` — The join method doesn't support non-friends
- L106 _public enumerator_ `CustomReason0` — Customizable denial reasons. Expected usage is to assign the entries in the custom enum to the arbitrary custom entry placeholders below. App level users of the system can then cast to/from their custom enum as desired.
- L107 _public enumerator_ `CustomReason1`
- L108 _public enumerator_ `CustomReason2`
- L109 _public enumerator_ `CustomReason3`
- L110 _public enumerator_ `CustomReason4`
- L111 _public enumerator_ `CustomReason5`
- L112 _public enumerator_ `CustomReason6`
- L113 _public enumerator_ `CustomReason7`
- L114 _public enumerator_ `CustomReason8`
- L115 _public enumerator_ `CustomReason9`
- L116 _public enumerator_ `CustomReason10`
- L117 _public enumerator_ `CustomReason11`
- L118 _public enumerator_ `CustomReason12`
- L119 _public enumerator_ `CustomReason13`
- L120 _public enumerator_ `CustomReason14`
- L121 _public enumerator_ `CustomReason15`
- L122 _public enumerator_ `CustomReason16`
- L123 _public enumerator_ `CustomReason17`
- L124 _public enumerator_ `CustomReason18`
- L125 _public enumerator_ `CustomReason19`
- L126 _public enumerator_ `CustomReason20`
- L127 _public enumerator_ `CustomReason21`
- L128 _public enumerator_ `CustomReason22`
- L129 _public enumerator_ `CustomReason23`
- L130 _public enumerator_ `CustomReason24`
- L131 _public enumerator_ `CustomReason25`
- L132 _public enumerator_ `CustomReason26`
- L133 _public enumerator_ `CustomReason27`
- L134 _public enumerator_ `CustomReason28`
- L135 _public enumerator_ `CustomReason29`
- L136 _public enumerator_ `CustomReason30`
- L137 _public enumerator_ `CustomReason31`
- L138 _public enumerator_ `CustomReason32`
- L139 _public enumerator_ `CustomReason33`
- L140 _public enumerator_ `CustomReason34`
- L141 _public enumerator_ `CustomReason35`
- L142 _public enumerator_ `CustomReason36`
- L143 _public enumerator_ `CustomReason37`
- L144 _public enumerator_ `CustomReason38`
- L145 _public enumerator_ `CustomReason39`
- L147 _public enumerator_ `MAX`

#### enum `EApprovalAction`  
`enum class EApprovalAction : uint8`  
_L153-159_
- reflection: `UENUM()`
- L155 _public enumerator_ `Approve`
- L156 _public enumerator_ `Enqueue`
- L157 _public enumerator_ `EnqueueAndStartBeacon`
- L158 _public enumerator_ `Deny`

#### enum `ESocialPartyInviteMethod`  
`enum class ESocialPartyInviteMethod : uint8`  
_L162-183_
- reflection: `UENUM()`
- L165 _public enumerator_ `Other = 0` — Default value for try invite
- L167 _public enumerator_ `Notification` — Invite was sent from a toast
- L169 _public enumerator_ `AcceptRequestToJoin` — Invite was sent via accepting "Request To Join"
- L171 _public enumerator_ `Custom0` — Custom methods
- L172 _public enumerator_ `Custom1`
- L173 _public enumerator_ `Custom2`
- L174 _public enumerator_ `Custom3`
- L175 _public enumerator_ `Custom4`
- L176 _public enumerator_ `Custom5`
- L177 _public enumerator_ `Custom6`
- L178 _public enumerator_ `Custom7`
- L179 _public enumerator_ `Custom8`
- L180 _public enumerator_ `Custom9`
- L182 _public enumerator_ `MAX`

#### enum `ESocialPartyInviteFailureReason`  
`enum class ESocialPartyInviteFailureReason : uint8`  
_L186-197_
- reflection: `UENUM()`
- L188 _public enumerator_ `Success = 0`
- L189 _public enumerator_ `NotOnline`
- L190 _public enumerator_ `NotAcceptingMembers`
- L191 _public enumerator_ `NotFriends`
- L192 _public enumerator_ `AlreadyInParty`
- L193 _public enumerator_ `OssValidationFailed`
- L194 _public enumerator_ `PlatformInviteFailed`
- L195 _public enumerator_ `PartyInviteFailed`
- L196 _public enumerator_ `InviteRateLimitExceeded`

#### struct `FPartyPlatformSessionInfo`  
`struct FPartyPlatformSessionInfo`  
_L206-231_
- reflection: `USTRUCT()`
- L214 _public member_ `FString SessionType;` — `UPROPERTY()` — The platform session type (because in a crossplay party, members can be in different session types)
- L218 _public member_ `FString SessionId;` — `UPROPERTY()` — The platform session id. Will be unset if it is not yet available to be joined.
- L222 _public member_ `FUniqueNetIdRepl OwnerPrimaryId;` — `UPROPERTY()` — Primary OSS ID of the player that owns this console session
- L224 _public prototype_ `bool operator==(const FString& InSessionType) const;`
- L225 _public prototype_ `bool operator==(const FPartyPlatformSessionInfo& Other) const;`
- L226 _public function_ `bool operator!=(const FPartyPlatformSessionInfo& Other) const`
- L228 _public prototype_ `FString ToDebugString() const;`
- L229 _public prototype_ `bool IsSessionOwner(const UPartyMember& PartyMember) const;`
- L230 _public prototype_ `bool IsInSession(const UPartyMember& PartyMember) const;`

#### struct `FPartyPrivacySettings`  
`struct FPartyPrivacySettings`  
_L234-255_
- reflection: `USTRUCT()`
- L241 _public member_ `EPartyType PartyType = EPartyType::Private;` — `UPROPERTY()` — The type of party in terms of advertised joinability restrictions
- L245 _public member_ `EPartyInviteRestriction PartyInviteRestriction = EPartyInviteRestriction::NoInvites;` — `UPROPERTY()` — Who is allowed to send invitataions to the party?
- L249 _public member_ `bool bOnlyLeaderFriendsCanJoin = true;` — `UPROPERTY()` — True to restrict the party exclusively to friends of the party leader
- L251 _public prototype_ `bool operator==(const FPartyPrivacySettings& Other) const;`
- L252 _public function_ `bool operator!=(const FPartyPrivacySettings& Other) const`
- L254 _public function_ `FPartyPrivacySettings()`

#### struct `FPartyJoinDenialReason`  
`struct FPartyJoinDenialReason`  
_L259-308_
- desc: Companion to EPartyJoinDenialReason to lessen the hassle of working with a "customized" enum
- L262 _public function_ `FPartyJoinDenialReason()`
- L263 _public function_ `FPartyJoinDenialReason(int32 DenialReasonCode)`
- L272 _public function_ `template <typename CustomReasonEnumT> FPartyJoinDenialReason(CustomReasonEnumT CustomReason) : FPartyJoinDenialReason((int32)CustomReason)`
- L277 _public function_ `bool operator==(const FPartyJoinDenialReason& Other) const`
- L278 _public function_ `bool operator==(int32 ReasonCode) const`
- L281 _public function_ `template <typename CustomReasonEnumT> bool operator==(CustomReasonEnumT CustomReason) const`
- L283 _public function_ `operator int32() const`
- L285 _public function_ `bool HasAnyReason() const`
- L286 _public function_ `bool HasCustomReason() const`
- L287 _public function_ `EPartyJoinDenialReason GetReason() const`
- L290 _public function_ `template <typename CustomReasonEnumT> CustomReasonEnumT GetCustomReason() const`
- L297 _public function_ `template <typename CustomReasonEnumT> const TCHAR* AsString() const`
- L307 _private member_ `EPartyJoinDenialReason DenialReason = EPartyJoinDenialReason::NoReason;`

#### struct `FPartyJoinApproval`  
`struct FPartyJoinApproval`  
_L310-340_
- L312 _public function_ `FPartyJoinApproval()`
- L314 _public function_ `void SetDenialReason(FPartyJoinDenialReason InDenialReason)`
- L323 _public function_ `void SetApprovalAction(EApprovalAction InApprovalAction)`
- L332 _public function_ `EApprovalAction GetApprovalAction() const`
- L333 _public function_ `FPartyJoinDenialReason GetDenialReason() const`
- L335 _public function_ `bool CanJoin() const`
- L338 _private member_ `FPartyJoinDenialReason DenialReason;`
- L339 _private member_ `EApprovalAction ApprovalAction = EApprovalAction::Approve;`

#### struct `FJoinPartyResult`  
`struct FJoinPartyResult`  
_L342-366_
- L345 _public prototype_ `FJoinPartyResult();`
- L346 _public prototype_ `FJoinPartyResult(FPartyJoinDenialReason InDenialReason);`
- L347 _public prototype_ `FJoinPartyResult(EJoinPartyCompletionResult InResult);`
- L348 _public prototype_ `FJoinPartyResult(EJoinPartyCompletionResult InResult, FPartyJoinDenialReason InDenialReason);`
- L349 _public prototype_ `FJoinPartyResult(EJoinPartyCompletionResult InResult, int32 InResultSubCode);`
- L351 _public prototype_ `void SetDenialReason(FPartyJoinDenialReason InDenialReason);`
- L352 _public prototype_ `void SetResult(EJoinPartyCompletionResult InResult);`
- L354 _public prototype_ `bool WasSuccessful() const;`
- L356 _public function_ `EJoinPartyCompletionResult GetResult() const`
- L357 _public function_ `FPartyJoinDenialReason GetDenialReason() const`
- L358 _public function_ `int32 GetResultSubCode() const`
- L361 _private member_ `EJoinPartyCompletionResult Result;`
- L363 _private member_ `FPartyJoinDenialReason DenialReason;` — Denial reason - used if Result is NotApproved
- L365 _private member_ `int32 ResultSubCode = 0;` — Result sub code - used for any other Result type

#### struct `FOnlinePartyRepDataBase`  
`struct FOnlinePartyRepDataBase`  
_L370-408_
- reflection: `USTRUCT()`
- desc: Base for all rep data structs
- L373 _public prototype_ `virtual ~FOnlinePartyRepDataBase() = default;`
- L380 _protected function_ `virtual void GetAssetsToAsyncLoad(TArray<FSoftObjectPath>& OutAssets) const` — Gets any assets that should be async loaded before PostReplication is called. This is only used if Party.ReplicationAsyncLoadingEnabled is enabled.
- L388 _protected function_ `virtual void CompareAgainst(const FOnlinePartyRepDataBase& OldData) const` — Compare this data against the given old data, triggering delegates as appropriate. Intended to be used in concert with EXPOSE_REP_DATA_PROPERTY so that all you need to do is run through each property's CompareX function. If you need to do more complex comparison logic, you're welcome to do that as well/instead. @see FPartyRepData::CompareAgainst for an example
- L395 _protected function_ `virtual void PostReplication(const FOnlinePartyRepDataBase& OldData, TSharedPtr<FStreamableHandle> InResourceHandle)` — Called directly after an updated member state is received and copied into the local state. InResourceHandle will contain any resources returned by GetAssetsToAsyncLoad that were loaded. This handle should be retained to keep these resources in memory.
- L397 _protected function_ `virtual void PostReplication(const FOnlinePartyRepDataBase& OldData)` — `UE_DEPRECATED(5.8, "Please use version taking InResourceHandle")`
- L398 _protected function_ `virtual bool CanEditData() const`
- L399 _protected function_ `virtual const USocialParty* GetOwnerParty() const`
- L400 _protected function_ `virtual const UPartyMember* GetOwningMember() const`
- L402 _protected prototype_ `void LogSetPropertyFailure(const TCHAR* OwningStructTypeName, const TCHAR* PropertyName) const;`
- L403 _protected prototype_ `void LogPropertyChanged(const TCHAR* OwningStructTypeName, const TCHAR* PropertyName, bool bFromReplication) const;`
- L407 _protected member_ `template <typename, class> friend class TPartyDataReplicator;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PARTY_API`
- L150 _prototype_ `const TCHAR* ToString(EPartyJoinDenialReason Type);`
- L200 _prototype_ `const TCHAR* LexToString(ESocialPartyInviteFailureReason Type);`
- L203 _typedef_ `using FSessionId = FString;` — Gives a smidge more meaning to the intended use for the string. These should just be UniqueId's (and are), but not reliably allocated as shared ptrs, so they cannot be replicated via FUniqueNetIdRepl.
- L414 _macro_ `#define EXPOSE_REP_DATA_PROPERTY_NO_SETTER_IMPL(Owner, PropertyType, PropertyName, PropertyAccess, GetterAccess, OnChangedAccess) \`
- L422 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOn##PropertyName##Changed, PropertyName##ArgType );`
- L423 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOn##PropertyName##ChangedDif, PropertyName##ArgType , PropertyName##ArgType );`
- L449 _macro_ `#define EXPOSE_REP_DATA_PROPERTY_NO_SETTER(Owner, PropertyType, PropertyName, PropertyAccess) \` — Simplest option - exposes getter and events, but no default setter
- L452 _macro_ `#define EXPOSE_REP_DATA_PROPERTY_SETTER_ONLY(Owner, PropertyType, PropertyName, PropertyAccess, SetterPrivacy) \`
- L483 _macro_ `#define STRINGIFY_REP_DATA_PROPERTY_REVISION_WARNING_TEXT(WarningText) #WarningText` — Helpers for printing a user-friendly field deprecation warning for replicated data.
- L484 _macro_ `#define REP_DATA_PROPERTY_REVISION_WARNING(DeprecatedName, RevisedName, DeprecatedVersion) UE_DEPRECATED(DeprecatedVersion, STRINGIFY_REP_DATA_PROPERTY_REVISION_WARNING_TEXT(DeprecatedName) " has been replaced by " STRINGIFY_REP_DATA_PROPER`
- L490 _macro_ `#define EXPOSE_REP_DATA_PROPERTY_SETTER_ACCESS(Owner, PropertyType, PropertyName, PropertyAccess, SetterPrivacy) \` — Exposes a rep data property and provides a default property setter. Awkwardly named util - don't bother using directly. Opt for EXPOSE_PRIVATE_REP_DATA_PROPERTY or EXPOSE_REP_DATA_PROPERTY
- L495 _macro_ `#define EXPOSE_PRIVATE_USTRUCT_REP_DATA_PROPERTY_DIRECT(Owner, PropertyType, StructProperty, ChildProperty) \` — Expose ustruct property for access without using StructProperty in the property name.
- L499 _macro_ `#define EXPOSE_USTRUCT_REP_DATA_PROPERTY_DIRECT(Owner, PropertyType, StructProperty, ChildProperty) \` — Expose ustruct property for access without using StructProperty in the property name.
- L507 _macro_ `#define EXPOSE_REVISED_REP_DATA_PROPERTY_NO_SETTER(Owner, PropertyType, PropertyName, PropertyAccess, DeprecatedPropertyName, DeprecatedVersion) \` — Simplest option - exposes getter and events, but no default setter Revised version - allows the preservation of a previous property name for making delegates and accessors which will work along-side the new names. A compile-time deprecation warning will be printed when the old fields are accessed.
- L526 _macro_ `#define EXPOSE_REVISED_REP_DATA_PROPERTY_SETTER_ACCESS(Owner, PropertyType, PropertyName, PropertyAccess, SetterPrivacy, DeprecatedPropertyName, DeprecatedVersion) \` — Exposes a rep data property and provides a default property setter. Awkwardly named util - don't bother using directly. Opt for EXPOSE_PRIVATE_REP_DATA_PROPERTY or EXPOSE_REP_DATA_PROPERTY Revised version - allows the preservation of a previous property name for making delegates and accessors which will work along-side the new names. A compile-time deprecation warning will be printed when the old fields are accessed.
- L541 _macro_ `#define EXPOSE_PRIVATE_REP_DATA_PROPERTY(Owner, PropertyType, Property) \` — Exposes a rep data property with a private setter. The setter only allows modification if the local user has authority to alter the property and will automatically trigger delegates appropriately.
- L548 _macro_ `#define EXPOSE_REP_DATA_PROPERTY(Owner, PropertyType, Property) \` — Fully exposes the rep data property with a public setter. The setter only allows modification if the local user has authority to alter the property and will automatically trigger delegates appropriately
- L555 _macro_ `#define EXPOSE_PRIVATE_USTRUCT_REP_DATA_PROPERTY(Owner, PropertyType, StructProperty, ChildProperty) \` — Exposes a rep data property with a private setter for a member within a USTRUCT parameter. The setter only allows modification if the local user has authority to alter the property and will automatically trigger delegates appropriately.
- L562 _macro_ `#define EXPOSE_USTRUCT_REP_DATA_PROPERTY(Owner, PropertyType, StructProperty, ChildProperty) \` — Fully exposes the rep data property with a public setter for a member within a USTRUCT parameter. The setter only allows modification if the local user has authority to alter the property and will automatically trigger delegates appropriately
- L570 _macro_ `#define EXPOSE_REVISED_PRIVATE_USTRUCT_REP_DATA_PROPERTY(Owner, PropertyType, StructProperty, ChildProperty, DeprecatedPropertyName, DeprecatedVersion) \` — Exposes a rep data property with a private setter for a member within a USTRUCT parameter. The setter only allows modification if the local user has authority to alter the property and will automatically trigger delegates appropriately. The deprecated name is used to preserve existing delegates and accessors until a later time.
- L578 _macro_ `#define EXPOSE_REVISED_USTRUCT_REP_DATA_PROPERTY(Owner, PropertyType, StructProperty, ChildProperty, DeprecatedPropertyName, DeprecatedVersion) \` — Fully exposes the rep data property with a public setter for a member within a USTRUCT parameter. The setter only allows modification if the local user has authority to alter the property and will automatically trigger delegates appropriately The deprecated name is used to preserve existing delegates and accessors until a later time.
- L581 _prototype_ `const TCHAR* ToString(EPartyType Type);`
- L582 _prototype_ `const TCHAR* ToString(EApprovalAction Type);`
- L585 _namespace_ `namespace PartyJoinMethod`
- L588 _externvar_ `extern const FName Creation;` (scope `PartyJoinMethod`) — User has created the party
- L590 _externvar_ `extern const FName Invitation;` (scope `PartyJoinMethod`) — User has joined the party via invitation
- L592 _externvar_ `extern const FName RequestToJoin;` (scope `PartyJoinMethod`) — user has joined after requesting access
- L594 _externvar_ `extern const FName Presence;` (scope `PartyJoinMethod`) — User has joined the party via presence
- L596 _externvar_ `extern const FName PlatformSession;` (scope `PartyJoinMethod`) — User has joined the party using a platform option
- L598 _externvar_ `extern const FName CommandLineJoin;` (scope `PartyJoinMethod`) — User has joined the party via command line
- L600 _externvar_ `extern const FName Unspecified;` (scope `PartyJoinMethod`) — User has joined via unknown/undocumented process

### `Plugins/Online/OnlineFramework/Source/Party/Public/Party/SocialParty.h` (Public)


#### struct `FPartyRepData`  
`struct FPartyRepData : public FOnlinePartyRepDataBase`  
_L36-92_
- reflection: `USTRUCT()`
- inherits: `FOnlinePartyRepDataBase`
- desc: Base struct used to replicate data about the state of the party to all members.
- L41 _public function_ `FPartyRepData()`
- L42 _public function_ `FPartyRepData& operator=(const FPartyRepData& Other)`
- L56 _public prototype_ `virtual void SetOwningParty(const class USocialParty& InOwnerParty);`
- L58 _public prototype_ `void MarkOwnerless();` — Mark the party data as ownerless. This will bypass any "CanEdit" checks. Useful for using this object in a test context.
- L60 _public prototype_ `const FPartyPlatformSessionInfo* FindSessionInfo(const FString& SessionType) const;`
- L61 _public function_ `const TArray<FPartyPlatformSessionInfo>& GetPlatformSessions() const`
- L62 _public function_ `FSimpleMulticastDelegate& OnPlatformSessionsChanged() const`
- L64 _public prototype_ `void UpdatePlatformSessionInfo(FPartyPlatformSessionInfo&& SessionInfo);`
- L65 _public prototype_ `void ClearPlatformSessionInfo(const FString& SessionType);`
- L68 _public function_ `FSimpleMulticastDelegate& OnPostReplicationProcessed() const` — Fires after received rep data has been fully applied
- L71 _protected prototype_ `virtual bool CanEditData() const override;`
- L72 _protected prototype_ `virtual void CompareAgainst(const FOnlinePartyRepDataBase& OldData) const override;`
- L73 _protected prototype_ `virtual const USocialParty* GetOwnerParty() const override;`
- L74 _protected prototype_ `virtual void PostReplication(const FOnlinePartyRepDataBase& OldData, TSharedPtr<FStreamableHandle> InResourceHandle) override;`
- L76 _protected member_ `TWeakObjectPtr<const USocialParty> OwnerParty;`
- L77 _protected member_ `bool bAllowOwnerless = false;`
- L82 _protected member_ `FPartyPrivacySettings PrivacySettings;` — `UPROPERTY()` — The privacy settings for the party
- L83 _protected prototype_ `EXPOSE_REP_DATA_PROPERTY(FPartyRepData, FPartyPrivacySettings, PrivacySettings);`
- L87 _protected member_ `TArray<FPartyPlatformSessionInfo> PlatformSessions;` — `UPROPERTY()` — List of platform sessions for the party. Includes one entry per platform that needs a session and has a member of that session.
- L90 _private member_ `mutable FSimpleMulticastDelegate OnPlatformSessionsChangedEvent;`
- L91 _private member_ `mutable FSimpleMulticastDelegate OnPostReplicationProcessedEvent;`

#### class `USocialParty`  
`class USocialParty : public UObject`  
_L101-550_
- reflection: `UCLASS(MinimalAPI, Abstract, Within=SocialManager, config=Game, Transient)`
- inherits: `UObject`
- desc: Party game state that contains all information relevant to the communication within a party Keeps all players in sync with the state of the party and its individual members
- L110 _public prototype_ `static bool IsJoiningDuringLoadEnabled();`
- L112 _public prototype_ `USocialParty();`
- L115 _public prototype_ `void RefreshPublicJoinability();` — Re-evaluates whether this party is joinable by anyone and, if not, establishes the reason why
- L117 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnLeavePartyAttemptComplete, ELeavePartyCompletionResult) virtual void LeaveParty(const FOnLeavePartyAttemptComplete& OnLeaveAttemptComplete = FOnLeavePartyAttemptComplete());`
- L119 _public prototype_ `virtual void RemoveLocalMember(const FUniqueNetIdRepl& LocalUserId, const FOnLeavePartyAttemptComplete& OnLeaveAttemptComplete = FOnLeavePartyAttemptComplete());`
- L121 _public function_ `const FPartyRepData& GetRepData() const`
- L124 _public function_ `template <typename SocialManagerT = USocialManager> SocialManagerT& GetSocialManager() const`
- L132 _public function_ `template <typename MemberT = UPartyMember> MemberT& GetOwningLocalMember() const`
- L140 _public function_ `template <typename MemberT = UPartyMember> MemberT* GetPartyLeader() const`
- L146 _public function_ `template <typename MemberT = UPartyMember> MemberT* GetPartyMember(const FUniqueNetIdRepl& MemberId) const`
- L151 _public prototype_ `bool ContainsUser(const USocialUser& User) const;`
- L153 _public prototype_ `ULocalPlayer* GetOwningLocalPlayerPtr() const;`
- L154 _public function_ `const FUniqueNetIdRepl& GetOwningLocalUserId() const`
- L155 _public function_ `const FUniqueNetIdRepl& GetPartyLeaderId() const`
- L156 _public prototype_ `bool IsLocalPlayerPartyLeader() const;`
- L157 _public prototype_ `bool IsPartyLeader(const ULocalPlayer& LocalPlayer) const;`
- L158 _public prototype_ `bool IsPartyLeaderLocal() const;`
- L160 _public prototype_ `FChatRoomId GetChatRoomId() const;`
- L161 _public prototype_ `bool IsPersistentParty() const;`
- L162 _public prototype_ `const FOnlinePartyTypeId& GetPartyTypeId() const;`
- L163 _public prototype_ `const FOnlinePartyId& GetPartyId() const;`
- L165 _public prototype_ `EPartyState GetOssPartyState() const;`
- L166 _public prototype_ `EPartyState GetOssPartyPreviousState() const;`
- L168 _public prototype_ `bool IsCurrentlyCrossplaying() const;`
- L169 _public prototype_ `bool IsPartyFunctionalityDegraded() const;`
- L171 _public prototype_ `bool IsPartyFull() const;`
- L172 _public prototype_ `int32 GetNumPartyMembers() const;`
- L173 _public prototype_ `void SetPartyMaxSize(int32 NewSize);`
- L174 _public prototype_ `int32 GetPartyMaxSize() const;`
- L175 _public prototype_ `FPartyJoinDenialReason GetPublicJoinability() const;`
- L176 _public function_ `bool IsLeavingParty() const`
- L179 _public prototype_ `bool IsNetDriverFromReservationBeacon(const UNetDriver* InNetDriver) const;` — Is the specified net driver for our reservation beacon?
- L181 _public prototype_ `virtual void DisconnectParty();`
- L184 _public function_ `template <typename MemberT = UPartyMember> TArray<MemberT*> GetPartyMembers() const`
- L198 _public prototype_ `FString ToDebugString() const;`
- L200 _public prototype_ `DECLARE_EVENT_OneParam(USocialParty, FLeavePartyEvent, EMemberExitedReason);`
- L201 _public function_ `FLeavePartyEvent& OnPartyLeaveBegin() const`
- L202 _public function_ `FLeavePartyEvent& OnPartyLeft() const`
- L204 _public prototype_ `DECLARE_EVENT(USocialParty, FDisconnectPartyEvent);`
- L205 _public function_ `FDisconnectPartyEvent& OnPartyDisconnected() const`
- L207 _public prototype_ `DECLARE_EVENT_OneParam(USocialParty, FOnPartyMemberCreated, UPartyMember&);`
- L208 _public function_ `FOnPartyMemberCreated& OnPartyMemberCreated() const`
- L210 _public prototype_ `DECLARE_EVENT_TwoParams(USocialParty, FOnPartyMemberLeft, UPartyMember*, const EMemberExitedReason);`
- L211 _public function_ `FOnPartyMemberLeft& OnPartyMemberLeft() const`
- L217 _public prototype_ `DECLARE_EVENT_OneParam(USocialParty, FOnPartyLeaderChanged, UPartyMember* );` — Event triggered when the party leader changes. @param NewLeader the new leader. Generally non-null, but there may be race conditions where we get the leader id before we get the leader's data.
- L218 _public function_ `FOnPartyLeaderChanged& OnPartyLeaderChanged() const`
- L220 _public prototype_ `DECLARE_EVENT_OneParam(USocialParty, FOnPartyConfigurationChanged, const FPartyConfiguration&);`
- L221 _public function_ `FOnPartyConfigurationChanged& OnPartyConfigurationChanged() const`
- L223 _public prototype_ `DECLARE_EVENT_TwoParams(USocialParty, FOnPartyStateChanged, EPartyState, EPartyState);`
- L224 _public function_ `FOnPartyStateChanged& OnPartyStateChanged() const`
- L226 _public prototype_ `DECLARE_EVENT_OneParam(USocialParty, FOnPartyFunctionalityDegradedChanged, bool );`
- L227 _public function_ `FOnPartyFunctionalityDegradedChanged& OnPartyFunctionalityDegradedChanged() const`
- L229 _public prototype_ `DECLARE_EVENT_OneParam(USocialParty, FOnInviteSent, const USocialUser&);`
- L230 _public function_ `FOnInviteSent& OnInviteSent() const`
- L232 _public prototype_ `DECLARE_EVENT_TwoParams(USocialParty, FOnPartyMemberConnectionStatusChanged, UPartyMember&, EMemberConnectionStatus);`
- L233 _public function_ `FOnPartyMemberConnectionStatusChanged& OnPartyMemberConnectionStatusChanged() const`
- L235 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnInitializationCompletePreNotify, USocialParty&);`
- L236 _public function_ `FOnInitializationCompletePreNotify& OnInitializationCompletePreNotify() const`
- L238 _public prototype_ `void ResetPrivacySettings();`
- L239 _public prototype_ `const FPartyPrivacySettings& GetPrivacySettings() const;`
- L241 _public prototype_ `virtual bool ShouldAlwaysJoinPlatformSession(const FSessionId& SessionId) const;`
- L244 _public prototype_ `virtual void AugmentPlatformSessionSettings(FOnlineSessionSettings& SessionSettings) const;` — Hook for subclasses to add game-specific keys to NAME_PartySession (default: no-op).
- L247 _public prototype_ `DECLARE_EVENT(USocialParty, FOnPlatformSessionUpdateRequested);` — Fired by subclasses to ask FPartyPlatformSessionMonitor to re-advertise the platform session.
- L248 _public function_ `FOnPlatformSessionUpdateRequested& OnPlatformSessionUpdateRequested() const`
- L250 _public prototype_ `virtual void JoinSessionCompleteAnalytics(const FSessionId& SessionId, const FString& JoinBootableGroupSessionResult);`
- L251 _public prototype_ `bool IsCurrentlyLeaving() const;`
- L253 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnRequestJoinInProgressComplete, const EPartyJoinDenialReason );`
- L254 _public prototype_ `void RequestJoinInProgress(const UPartyMember& TargetMember, const FOnRequestJoinInProgressComplete& CompletionDelegate);`
- L255 _public prototype_ `void CancelJoinInProgressRequest();`
- L256 _public prototype_ `bool IsJoinInProgeressRequestActive() const;`
- L258 _public prototype_ `bool CanInviteUser(const USocialUser& User, const ESocialPartyInviteMethod InviteMethod = ESocialPartyInviteMethod::Other) const;`
- L260 _public prototype_ `bool IsInitialized() const;`
- L263 _protected prototype_ `void InitializeParty(const TSharedRef<const FOnlineParty>& InOssParty);`
- L264 _protected prototype_ `void TryFinishInitialization();`
- L265 _protected prototype_ `void NotifyRepDataProcessed();`
- L267 _protected prototype_ `void SetIsMissingPlatformSession(bool bInIsMissingPlatformSession);`
- L268 _protected function_ `bool IsMissingPlatformSession()`
- L270 _protected function_ `FPartyRepData& GetMutableRepData()`
- L274 _protected prototype_ `bool HasUserBeenInvited(const USocialUser& User) const;` — User/member-specific actions that are best exposed on the individuals themselves, but best handled by the actual party
- L276 _protected prototype_ `bool CanPromoteMember(const ULocalPlayer& PerformingPlayer, const UPartyMember& PartyMember) const;`
- L277 _protected prototype_ `virtual bool CanKickMember(const ULocalPlayer& PerformingPlayer, const UPartyMember& PartyMember) const;`
- L278 _protected prototype_ `bool TryPromoteMember(const ULocalPlayer& PerformingPlayer, const UPartyMember& PartyMember);`
- L279 _protected prototype_ `virtual bool TryKickMember(const ULocalPlayer& PerformingPlayer, const UPartyMember& PartyMember);`
- L281 _protected prototype_ `bool TryInviteUser(const USocialUser& UserToInvite, const ESocialPartyInviteMethod InviteMethod = ESocialPartyInviteMethod::Other, const FString& MetaData = FString());`
- L284 _protected prototype_ `virtual bool AllowJoinInProgressToMember();`
- L287 _protected prototype_ `virtual void InitializePartyInternal();`
- L289 _protected function_ `FPartyConfiguration& GetCurrentConfiguration()`
- L292 _protected prototype_ `virtual void InitializePartyRepData();` — Only called when a new party is being created by the local player and they are responsible for the rep data. Otherwise we just wait to receive it from the leader.
- L293 _protected prototype_ `virtual FPartyPrivacySettings GetDesiredPrivacySettings() const;`
- L294 _protected prototype_ `static FPartyPrivacySettings GetPrivacySettingsForConfig(const FPartyConfiguration& PartyConfig);`
- L295 _protected prototype_ `virtual void OnLocalPlayerIsLeaderChanged(bool bIsLeader);`
- L296 _protected prototype_ `virtual void HandlePrivacySettingsChanged(const FPartyPrivacySettings& NewPrivacySettings);`
- L297 _protected prototype_ `virtual void OnMemberCreatedInternal(UPartyMember& NewMember);`
- L298 _protected prototype_ `virtual void OnLeftPartyInternal(EMemberExitedReason Reason);`
- L301 _protected prototype_ `virtual ESocialPartyInviteFailureReason CanInviteUserInternal(const USocialUser& User, const ESocialPartyInviteMethod InviteMethod) const;` — Virtual versions of the package-scoped "CanX" methods above, as a virtual declared within package scoping cannot link (exported public, imported protected)
- L303 _protected prototype_ `virtual bool CanPromoteMemberInternal(const ULocalPlayer& PerformingPlayer, const UPartyMember& PartyMember) const;`
- L304 _protected prototype_ `virtual bool CanKickMemberInternal(const ULocalPlayer& PerformingPlayer, const UPartyMember& PartyMember) const;`
- L306 _protected prototype_ `virtual void OnInviteSentInternal(ESocialSubsystem SubsystemType, const USocialUser& InvitedUser, bool bWasSuccessful, const ESocialPartyInviteFailureReason FailureReason, const ESocialPartyInviteMethod InviteMethod, const FString& MetaData);`
- L309 _protected function_ `virtual void OnInviteSentInternal(ESocialSubsystem SubsystemType, const USocialUser& InvitedUser, bool bWasSuccessful, const ESocialPartyInviteFailureReason FailureReason, const ESocialPartyInviteMethod InviteMethod)` — `UE_DEPRECATED(5.6, "Override 'void OnInviteSentInternal(ESocialSubsystem SubsystemType, const USocialUser& InvitedUser, bool bWasSuccessful, const ESocialPartyInviteFailureReason FailureReason, const ESocialPartyInviteMethod InviteMethod, const FString& MetaData)' instead")`
- L312 _protected function_ `virtual void OnInviteSentInternal(ESocialSubsystem SubsystemType, const USocialUser& InvitedUser, bool bWasSuccessful)` — `UE_DEPRECATED(5.6, "Override 'void OnInviteSentInternal(ESocialSubsystem SubsystemType, const USocialUser& InvitedUser, bool bWasSuccessful, const ESocialPartyInviteFailureReason FailureReason, const ESocialPartyInviteMethod InviteMethod, const FString& MetaData)' instead")`
- L314 _protected prototype_ `virtual void HandlePartySystemStateChange(EPartySystemState NewState);`
- L317 _protected prototype_ `virtual FPartyJoinApproval EvaluateJoinRequest(const TArray<IOnlinePartyUserPendingJoinRequestInfoConstRef>& Players, bool bFromJoinRequest) const;` — Determines the joinability of this party for a group of users requesting to join
- L322 _protected prototype_ `virtual bool EvaluateJoinRequestAwayCheck(const TArray<IOnlinePartyUserPendingJoinRequestInfoConstRef>& Players, bool bFromJoinRequest) const;` — Perform the Away status check for an incoming join request @return true if the join request passes the away check
- L325 _protected prototype_ `virtual FPartyJoinDenialReason DetermineCurrentJoinability() const;` — Determines the reason why, if at all, this party is currently flat-out unjoinable
- L328 _protected prototype_ `virtual TSubclassOf<UPartyMember> GetDesiredMemberClass(bool bLocalPlayer) const;` — Override in child classes to specify the type of UPartyMember to create
- L331 _protected prototype_ `virtual bool InitializeBeaconEncryptionData(AOnlineBeaconClient& BeaconClient, const FString& SessionId);` — Override in child classes to provide encryption data for party beacon connections.
- L334 _protected prototype_ `virtual TArray<UPartyMember*> GetLocalPartyMembersForJoinInProgress() const;` — The list of party members to send the request for joining in progress.
- L337 _protected prototype_ `virtual FString GetInviteMetadata(const FString& ExistingMetadata);` — Override in child classes to provide extra invite metadata.
- L339 _protected prototype_ `bool IsInviteRateLimited(const USocialUser& User, ESocialSubsystem SubsystemType) const;`
- L341 _protected prototype_ `bool ApplyCrossplayRestriction(FPartyJoinApproval& JoinApproval, const FUserPlatform& Platform, const FOnlinePartyData& JoinData) const;`
- L342 _protected prototype_ `FName GetGameSessionName() const;`
- L343 _protected prototype_ `bool IsInRestrictedGameSession() const;`
- L349 _protected prototype_ `void ConnectToReservationBeacon();` — Create a reservation beacon and connect to the server to get approval for new party members Only relevant while in an active game, not required while pre lobby / game
- L350 _protected prototype_ `void CleanupReservationBeacon();`
- L351 _protected prototype_ `APartyBeaconClient* CreateReservationBeaconClient();`
- L353 _protected function_ `APartyBeaconClient* GetReservationBeaconClient() const`
- L358 _protected prototype_ `void CleanupSpectatorBeacon();` — Create a spectator beacon and connect to the server to get approval for new spectators
- L359 _protected prototype_ `ASpectatorBeaconClient* CreateSpectatorBeaconClient();`
- L361 _protected function_ `ASpectatorBeaconClient* GetSpectatorBeaconClient() const`
- L364 _protected member_ `FPartyDataReplicator PartyDataReplicator;` — Child classes MUST call EstablishRepDataInstance() on this using their member rep data struct instance
- L368 _protected member_ `TSubclassOf<APartyBeaconClient> ReservationBeaconClientClass;` — `UPROPERTY()` — Reservation beacon class for getting server approval for new party members while in a game
- L372 _protected member_ `TSubclassOf<ASpectatorBeaconClient> SpectatorBeaconClientClass;` — `UPROPERTY()` — Spectator beacon class for getting server approval for new spectators while in a game
- L375 _protected prototype_ `void UpdatePartyConfig(bool bResetAccessKey = false);` — Apply local party configuration to the OSS party, optionally resetting the access key to the party in the process
- L378 _private prototype_ `UPartyMember* GetOrCreatePartyMember(const FUniqueNetId& MemberId);`
- L379 _private prototype_ `void PumpApprovalQueue();`
- L380 _private prototype_ `void RejectAllPendingJoinRequests();`
- L381 _private prototype_ `void SetIsMissingXmppConnection(bool bInMissingXmppConnection);`
- L382 _private prototype_ `void BeginLeavingParty(EMemberExitedReason Reason);`
- L383 _private prototype_ `void FinalizePartyLeave(EMemberExitedReason Reason);`
- L385 _private prototype_ `void SetIsRequestingShutdown(bool bInRequestingShutdown);`
- L387 _private prototype_ `void CreatePlatformSession(const FString& SessionType);`
- L388 _private prototype_ `void UpdatePlatformSessionLeader(const FString& SessionType);`
- L390 _private prototype_ `void HandlePreClientTravel(const FString& PendingURL, ETravelType TravelType, bool bIsSeamlessTravel);`
- L392 _private prototype_ `UPartyMember* GetMemberInternal(const FUniqueNetIdRepl& MemberId) const;`
- L395 _protected prototype_ `virtual void HandlePartyStateChanged(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, EPartyState PartyState, EPartyState PreviousPartyState);`
- L397 _private prototype_ `void HandlePartyConfigChanged(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FPartyConfiguration& PartyConfig);`
- L398 _private prototype_ `void HandleUpdatePartyConfigComplete(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, EUpdateConfigCompletionResult Result);`
- L399 _private prototype_ `void HandlePartyDataReceived(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FName& Namespace, const FOnlinePartyData& PartyData);`
- L400 _private prototype_ `void HandleJoinabilityQueryReceived(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const IOnlinePartyPendingJoinRequestInfo& JoinRequestInfo);`
- L401 _private prototype_ `void HandlePartyJoinRequestReceived(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const IOnlinePartyPendingJoinRequestInfo& JoinRequestInfo);`
- L402 _private prototype_ `void HandlePartyLeft(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId);`
- L403 _private prototype_ `void HandlePartyMemberExited(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& MemberId, EMemberExitedReason ExitReason);`
- L404 _private prototype_ `void HandlePartyMemberDataReceived(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& MemberId, const FName& Namespace, const FOnlinePartyData& PartyMemberData);`
- L405 _private prototype_ `void HandlePartyMemberJoined(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& MemberId);`
- L406 _private prototype_ `void HandlePartyMemberPromoted(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& NewLeaderId);`
- L407 _private prototype_ `void HandlePartyPromotionLockoutChanged(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, bool bArePromotionsLocked);`
- L409 _private prototype_ `void HandleMemberInitialized(UPartyMember* Member);`
- L410 _private prototype_ `void HandleMemberPlatformUniqueIdChanged(const FUniqueNetIdRepl& NewPlatformUniqueId, UPartyMember* Member);`
- L411 _private prototype_ `void HandleMemberSessionIdChanged(const FSessionId& NewSessionId, UPartyMember* Member);`
- L413 _private prototype_ `void HandleBeaconHostConnectionFailed();`
- L414 _private prototype_ `void HandleReservationRequestComplete(EPartyReservationResult::Type ReservationResponse);`
- L416 _private prototype_ `void HandleLeavePartyComplete(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, ELeavePartyCompletionResult LeaveResult, FOnLeavePartyAttemptComplete OnAttemptComplete);`
- L417 _private prototype_ `void HandleRemoveLocalPlayerComplete(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, ELeavePartyCompletionResult LeaveResult, FOnLeavePartyAttemptComplete OnAttemptComplete);`
- L419 _private prototype_ `void RemovePlayerFromReservationBeacon(const FUniqueNetId& LocalUserId, const FUniqueNetId& PlayerToRemove);`
- L421 _private prototype_ `void HandleJoinInProgressDataRequestChanged(const FPartyMemberJoinInProgressRequest& Request, UPartyMember* Member);`
- L422 _private prototype_ `void HandleJoinInProgressDataResponsesChanged(const TArray<FPartyMemberJoinInProgressResponse>& Responses, UPartyMember* Member);`
- L425 _private member_ `TSharedPtr<const FOnlineParty> OssParty;`
- L428 _private member_ `FUniqueNetIdRepl OwningLocalUserId;` — `UPROPERTY()`
- L432 _private member_ `FUniqueNetIdRepl CurrentLeaderId;` — `UPROPERTY()` — Tracked explicitly so we know which player was demoted whenever the leader changes
- L435 _private member_ `TMap<FUniqueNetIdRepl, TObjectPtr<UPartyMember>> PartyMembersById;` — `UPROPERTY()`
- L437 _private member_ `TMap<FUniqueNetIdRepl, double> LastInviteSentById;`
- L440 _private member_ `double PlatformUserInviteCooldown = 10.f;` — `UPROPERTY(config)`
- L443 _private member_ `double PrimaryUserInviteCooldown = 0.f;` — `UPROPERTY(config)`
- L445 _private member_ `FPartyConfiguration CurrentConfig;`
- L469 _private member_ `TQueue<FPendingMemberApproval> PendingApprovals;`
- L471 _private member_ `bool bStayWithPartyOnDisconnect = false;`
- L472 _private member_ `bool bIsMemberPromotionPossible = true;`
- L479 _private member_ `FName LastReservationBeaconClientNetDriverName;` — Last known reservation beacon client net driver name Intended to be used to detect network errors related to our current or last reservation beacon client's net driver. Some network error handlers may be called after we cleanup our beacon connection.
- L483 _private member_ `TWeakObjectPtr<APartyBeaconClient> ReservationBeaconClient = nullptr;` — `UPROPERTY()` — Reservation beacon client instance while getting approval for new party members
- L490 _private member_ `FName LastSpectatorBeaconClientNetDriverName;` — Last known spectator beacon client net driver name Intended to be used to detect network errors related to our current or last spectator beacon client's net driver. Some network error handlers may be called after we cleanup our beacon connection.
- L494 _private member_ `TWeakObjectPtr<ASpectatorBeaconClient> SpectatorBeaconClient = nullptr;` — `UPROPERTY()` — Spectator beacon client instance while getting approval for spectator
- L500 _private member_ `TOptional<bool> bIsMissingXmppConnection;` — True when we have limited functionality due to lacking an xmpp connection. Don't set directly, use the private setter to trigger events appropriately.
- L501 _private member_ `bool bIsMissingPlatformSession = false;`
- L503 _private member_ `bool bIsLeavingParty = false;`
- L504 _private member_ `bool bIsInitialized = false;`
- L505 _private member_ `bool bHasReceivedRepData = false;`
- L506 _private member_ `TOptional<bool> bIsRequestingShutdown;`
- L508 _private prototype_ `void RespondToJoinInProgressRequest(const FPendingMemberApproval& PendingApproval, const EPartyJoinDenialReason DenialReason);`
- L509 _private prototype_ `void CallJoinInProgressComplete(const EPartyJoinDenialReason DenialReason);`
- L510 _private prototype_ `void RunJoinInProgressTimer();`
- L513 _private member_ `TOptional<FOnRequestJoinInProgressComplete> RequestJoinInProgressComplete;` — Complete delegate for join in progress requests. This should only have one at a time.
- L515 _private member_ `FTimerHandle JoinInProgressTimerHandle;`
- L519 _private member_ `float JoinInProgressTimerRate = 5.f;` — `UPROPERTY(config)` — How often the timer should check in seconds for stale data when running.
- L523 _private member_ `int32 JoinInProgressRequestTimeout = 30;` — `UPROPERTY(config)` — How long in seconds before join in progress requests timeout and are cleared from member data.
- L527 _private member_ `int32 JoinInProgressResponseTimeout = 60;` — `UPROPERTY(config)` — How long in seconds before join in progress responses are cleared from member data.
- L531 _private member_ `int32 MaxJoinInProgressResponses = 12;` — `UPROPERTY(config)` — Maximum number of join in progress responses to store in member rep data. Oldest responses are removed first.
- L535 _private member_ `int32 MaxJoinInProgressResponsesPerMember = 5;` — `UPROPERTY(config)` — Maximum number of join in progress responses to store per requesting member. Oldest responses are removed first.
- L537 _private member_ `mutable FLeavePartyEvent OnPartyLeaveBeginEvent;`
- L538 _private member_ `mutable FLeavePartyEvent OnPartyLeftEvent;`
- L539 _private member_ `mutable FDisconnectPartyEvent OnPartyDisconnectedEvent;`
- L540 _private member_ `mutable FOnPartyMemberCreated OnPartyMemberCreatedEvent;`
- L541 _private member_ `mutable FOnPartyMemberLeft OnPartyMemberLeftEvent;`
- L542 _private member_ `mutable FOnPartyLeaderChanged OnPartyLeaderChangedEvent;`
- L543 _private member_ `mutable FOnPartyConfigurationChanged OnPartyConfigurationChangedEvent;`
- L544 _private member_ `mutable FOnPartyStateChanged OnPartyStateChangedEvent;`
- L545 _private member_ `mutable FOnPartyMemberConnectionStatusChanged OnPartyMemberConnectionStatusChangedEvent;`
- L546 _private member_ `mutable FOnPartyFunctionalityDegradedChanged OnPartyFunctionalityDegradedChangedEvent;`
- L547 _private member_ `mutable FOnInviteSent OnInviteSentEvent;`
- L548 _private member_ `mutable FOnInitializationCompletePreNotify OnInitializationCompletePreNotifyEvent;`
- L549 _private member_ `mutable FOnPlatformSessionUpdateRequested OnPlatformSessionUpdateRequestedEvent;`

#### struct `USocialParty::FPendingMemberApproval`  
`struct FPendingMemberApproval`  
_L448-468_
- desc: @todo DanH Party: Rename/reorg this to more clearly call out that this is specific to lobby beacon stuff #suggested
- L463 _public member_ `FUniqueNetIdRepl RecipientId;`
- L464 _public member_ `TArray<FMemberInfo> Members;`
- L465 _public member_ `bool bIsJIPApproval;`
- L466 _public member_ `int64 JoinInProgressRequestTime = 0;`
- L467 _public member_ `bool bIsPlayerRemoval = false;`

#### struct `USocialParty::FPendingMemberApproval::FMemberInfo`  
`struct FMemberInfo`  
_L450-461_
- L452 _public function_ `FMemberInfo(FUniqueNetIdRepl InMemberId, FUserPlatform InPlatform, TSharedPtr<const FOnlinePartyData> InJoinData = TSharedPtr<const FOnlinePartyData>()) : MemberId(InMemberId) , Platform(MoveTemp(InPlatform)) , JoinData(InJoinData)`
- L458 _public member_ `FUniqueNetIdRepl MemberId;`
- L459 _public member_ `FUserPlatform Platform;`
- L460 _public member_ `TSharedPtr<const FOnlinePartyData> JoinData;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API PARTY_API`
- L19 _namespace_ `namespace EPartyReservationResult`
- L94 _typedef_ `using FPartyDataReplicator = TPartyDataReplicator<FPartyRepData, USocialParty>;`
- L117 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLeavePartyAttemptComplete, ELeavePartyCompletionResult) virtual void LeaveParty(const FOnLeavePartyAttemptComplete& OnLeaveAttemptComplete = FOnLeavePartyAttemptComplete());`
- L200 _delegate_ `DECLARE_EVENT_OneParam(USocialParty, FLeavePartyEvent, EMemberExitedReason);`
- L204 _delegate_ `DECLARE_EVENT(USocialParty, FDisconnectPartyEvent);`
- L207 _delegate_ `DECLARE_EVENT_OneParam(USocialParty, FOnPartyMemberCreated, UPartyMember&);`
- L210 _delegate_ `DECLARE_EVENT_TwoParams(USocialParty, FOnPartyMemberLeft, UPartyMember*, const EMemberExitedReason);`
- L217 _delegate_ `DECLARE_EVENT_OneParam(USocialParty, FOnPartyLeaderChanged, UPartyMember* );` — Event triggered when the party leader changes. @param NewLeader the new leader. Generally non-null, but there may be race conditions where we get the leader id before we get the leader's data.
- L220 _delegate_ `DECLARE_EVENT_OneParam(USocialParty, FOnPartyConfigurationChanged, const FPartyConfiguration&);`
- L223 _delegate_ `DECLARE_EVENT_TwoParams(USocialParty, FOnPartyStateChanged, EPartyState, EPartyState);`
- L226 _delegate_ `DECLARE_EVENT_OneParam(USocialParty, FOnPartyFunctionalityDegradedChanged, bool );`
- L229 _delegate_ `DECLARE_EVENT_OneParam(USocialParty, FOnInviteSent, const USocialUser&);`
- L232 _delegate_ `DECLARE_EVENT_TwoParams(USocialParty, FOnPartyMemberConnectionStatusChanged, UPartyMember&, EMemberConnectionStatus);`
- L235 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnInitializationCompletePreNotify, USocialParty&);`
- L247 _delegate_ `DECLARE_EVENT(USocialParty, FOnPlatformSessionUpdateRequested);` — Fired by subclasses to ask FPartyPlatformSessionMonitor to re-advertise the platform session.
- L253 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRequestJoinInProgressComplete, const EPartyJoinDenialReason );`
- L552 _namespace_ `namespace UE`
- L552 _namespace_ `namespace OnlineFramework` (scope `UE`)
- L554 _prototype_ `TArray<FUniqueNetIdRepl> GetPartyMemberIds(const USocialParty& SocialParty);` (scope `UE::OnlineFramework`)
- L555 _prototype_ `TArray<USocialToolkit*> GetLocalPartyMemberToolkits(const USocialParty& SocialParty);` (scope `UE::OnlineFramework`)

### `Plugins/Online/OnlineFramework/Source/Party/Public/PartyModule.h` (Public)


#### class `FPartyModule`  
`class FPartyModule : public IModuleInterface`  
_L19-61_
- inherits: `IModuleInterface`
- desc: Module for the party framework that builds on top of IOnlineParty
- L31 _public function_ `static inline FPartyModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L41 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L54 _private prototype_ `virtual void StartupModule() override;` — Called when party module is loaded Initialize platform specific parts of voice handling
- L60 _private prototype_ `virtual void ShutdownModule() override;` — Called when party module is unloaded Shutdown platform specific parts of voice handling

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogParty, Display, All);` — Logging related to parties
- L12 _delegate_ `DECLARE_STATS_GROUP(TEXT("Party"), STATGROUP_Party, STATCAT_Advan` — Party module stats
- L14 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("PartyStat1"), STAT_PartyStat1, STATGROUP_Party, P` — Total async thread time

### `Plugins/Online/OnlineFramework/Source/Party/Public/SocialDebugTools.h` (Public)


#### class `USocialDebugTools`  
`class USocialDebugTools : public UObject, public FExec`  
_L27-124_
- reflection: `UCLASS(MinimalAPI, Within = SocialManager, Config = Game)`
- inherits: `UObject,FExec`
- L31 _private member_ `static constexpr const int32 LocalUserNum = 0;`
- L34 _public prototype_ `USocialManager& GetSocialManager() const;`
- L38 _public prototype_ `virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out) override;`
- L43 _public prototype_ `USocialDebugTools();`
- L44 _public prototype_ `virtual void Shutdown();`
- L46 _public prototype_ `DECLARE_DELEGATE_OneParam(FLoginComplete, bool);`
- L47 _public prototype_ `virtual void Login(const FString& Instance, const FOnlineAccountCredentials& Credentials, const FLoginComplete& OnComplete);`
- L49 _public prototype_ `DECLARE_DELEGATE_OneParam(FLogoutComplete, bool);`
- L50 _public prototype_ `virtual void Logout(const FString& Instance, const FLogoutComplete& OnComplete);`
- L52 _public prototype_ `DECLARE_DELEGATE_OneParam(FJoinPartyComplete, bool);`
- L53 _public prototype_ `virtual void JoinParty(const FString& Instance, const FString& FriendName, const FJoinPartyComplete& OnComplete);`
- L55 _public prototype_ `DECLARE_DELEGATE_OneParam(FJoinInProgressComplete, EPartyJoinDenialReason);`
- L56 _public prototype_ `virtual void JoinInProgress(const FString& Instance, const FJoinInProgressComplete& OnComplete);`
- L58 _public prototype_ `DECLARE_DELEGATE_OneParam(FLeavePartyComplete, bool);`
- L59 _public prototype_ `virtual void LeaveParty(const FString& Instance, const FLeavePartyComplete& OnComplete);`
- L61 _public prototype_ `DECLARE_DELEGATE_OneParam(FCleanupPartiesComplete, bool);`
- L62 _public prototype_ `virtual void CleanupParties(const FString& Instance, const FCleanupPartiesComplete& OnComplete);`
- L64 _public prototype_ `DECLARE_DELEGATE_OneParam(FSetPartyMemberDataComplete, bool);`
- L65 _public prototype_ `virtual void SetPartyMemberData(const FString& Instance, const UStruct* StructType, const void* StructData, const FSetPartyMemberDataComplete& OnComplete);`
- L66 _public prototype_ `virtual void SetPartyMemberDataJson(const FString& Instance, const FString& JsonStr, const FSetPartyMemberDataComplete& OnComplete);`
- L68 _public function_ `virtual void GetContextNames(TArray<FString>& OutContextNames) const`
- L102 _public prototype_ `FInstanceContext& GetContext(const FString& Instance);`
- L103 _public prototype_ `FInstanceContext* GetContextForUser(const FUniqueNetId& UserId);`
- L106 _protected prototype_ `virtual void PrintExecCommands() const;`
- L107 _protected prototype_ `virtual bool RunCommand(const TCHAR* Cmd, const TArray<FString>& TargetInstances);`
- L108 _protected function_ `virtual void NotifyContextInitialized(const FInstanceContext& Context)`
- L111 _private member_ `bool bAutoAcceptFriendInvites;`
- L112 _private member_ `bool bAutoAcceptPartyInvites;`
- L114 _private member_ `TMap<FString, FInstanceContext> Contexts;`
- L116 _private prototype_ `IOnlinePartyJoinInfoConstPtr GetDefaultPartyJoinInfo() const;`
- L117 _private prototype_ `IOnlineSubsystem* GetDefaultOSS() const;`
- L118 _private prototype_ `void PrintExecUsage() const;`
- L121 _private prototype_ `void HandleFriendInviteReceived(const FUniqueNetId& LocalUserId, const FUniqueNetId& FriendId);` — OSS callback handlers
- L122 _private prototype_ `void HandlePartyInviteReceived(const FUniqueNetId& LocalUserId, const IOnlinePartyJoinInfo& Invitation);`
- L123 _private prototype_ `void HandlePartyJoinRequestReceived(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const IOnlinePartyPendingJoinRequestInfo& JoinRequestInfo);`

#### struct `USocialDebugTools::FInstanceContext`  
`struct FInstanceContext`  
_L70-100_
- L72 _public function_ `FInstanceContext(const FString& InstanceName, USocialDebugTools& SocialDebugTools) : Name(InstanceName) , OnlineSub(nullptr) , Owner(SocialDebugTools)`
- L78 _public prototype_ `void Init();`
- L79 _public prototype_ `void Shutdown();`
- L80 _public function_ `IOnlineSubsystem* GetOSS() const`
- L81 _public function_ `FOnlinePartyDataPtr GetPartyMemberData() const`
- L82 _public prototype_ `FUniqueNetIdPtr GetLocalUserId() const;`
- L83 _public prototype_ `void ModifyPartyField(const FString& FieldName, const class FVariantData& FieldValue);`
- L85 _public prototype_ `bool SetJIPRequest(const FPartyMemberJoinInProgressRequest& InRequest);`
- L87 _public member_ `FString Name;`
- L88 _public member_ `IOnlineSubsystem* OnlineSub;`
- L89 _public member_ `USocialDebugTools& Owner;`
- L90 _public member_ `FOnlinePartyDataPtr PartyMemberData;`
- L93 _public member_ `FDelegateHandle LoginCompleteDelegateHandle;` — delegates
- L94 _public member_ `FDelegateHandle LogoutCompleteDelegateHandle;`
- L95 _public member_ `UE::Online::FOnlineEventDelegateHandle OnPresenceUpdatedHandle;`
- L96 _public member_ `FDelegateHandle PresenceReceivedDelegateHandle;`
- L97 _public member_ `FDelegateHandle FriendInviteReceivedDelegateHandle;`
- L98 _public member_ `FDelegateHandle PartyInviteReceivedDelegateHandle;`
- L99 _public member_ `FDelegateHandle PartyJoinRequestReceivedDelegateHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PARTY_API`
- L20 _typedef_ `typedef TSharedPtr<const class IOnlinePartyJoinInfo> IOnlinePartyJoinInfoConstPtr;`
- L21 _typedef_ `typedef TSharedPtr<class FOnlinePartyData> FOnlinePartyDataPtr;`
- L22 _typedef_ `typedef TSharedPtr<const class FOnlinePartyData> FOnlinePartyDataConstPtr;`
- L23 _typedef_ `using FUniqueNetIdPtr = TSharedPtr<const FUniqueNetId>;`
- L46 _delegate_ `DECLARE_DELEGATE_OneParam(FLoginComplete, bool);`
- L49 _delegate_ `DECLARE_DELEGATE_OneParam(FLogoutComplete, bool);`
- L52 _delegate_ `DECLARE_DELEGATE_OneParam(FJoinPartyComplete, bool);`
- L55 _delegate_ `DECLARE_DELEGATE_OneParam(FJoinInProgressComplete, EPartyJoinDenialReason);`
- L58 _delegate_ `DECLARE_DELEGATE_OneParam(FLeavePartyComplete, bool);`
- L61 _delegate_ `DECLARE_DELEGATE_OneParam(FCleanupPartiesComplete, bool);`
- L64 _delegate_ `DECLARE_DELEGATE_OneParam(FSetPartyMemberDataComplete, bool);`

### `Plugins/Online/OnlineFramework/Source/Party/Public/SocialManager.h` (Public)


#### class `USocialManager`  
`class USocialManager : public UObject, public FExec`  
_L34-310_
- reflection: `UCLASS(MinimalAPI, Within = GameInstance, Config = Game)`
- inherits: `UObject,FExec`
- desc: Singleton manager at the top of the social framework
- L44 _public prototype_ `virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out) override;`
- L47 _public prototype_ `static bool IsSocialSubsystemEnabled(ESocialSubsystem SubsystemType);`
- L48 _public prototype_ `static FName GetSocialOssName(ESocialSubsystem SubsystemType);`
- L49 _public prototype_ `static FText GetSocialOssPlatformName(ESocialSubsystem SubsystemType);`
- L50 _public prototype_ `static IOnlineSubsystem* GetSocialOss(UWorld* World, ESocialSubsystem SubsystemType);`
- L51 _public prototype_ `static FUserPlatform GetLocalUserPlatform();`
- L52 _public function_ `static const TArray<ESocialSubsystem>& GetDefaultSubsystems()`
- L53 _public function_ `static const TArray<FSocialInteractionHandle>& GetRegisteredInteractions()`
- L55 _public prototype_ `USocialManager();`
- L56 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L58 _public prototype_ `static bool ShouldReadPresenceFromOnlineServices();`
- L59 _public prototype_ `static FName GetPresenceFrameworkInstance();`
- L60 _public prototype_ `static FName GetPresenceFrameworkAdapterInstance();`
- L63 _public prototype_ `virtual void InitSocialManager();` — Initializes the manager - call this right after creating the manager object during GameInstance initialization.
- L64 _public prototype_ `virtual void ShutdownSocialManager();`
- L66 _public prototype_ `USocialToolkit& GetSocialToolkit(const ULocalPlayer& LocalPlayer) const;`
- L67 _public prototype_ `USocialToolkit* GetSocialToolkit(int32 LocalPlayerNum) const;`
- L68 _public prototype_ `USocialToolkit* GetSocialToolkit(FUniqueNetIdRepl LocalUserId) const;`
- L69 _public prototype_ `USocialToolkit* GetFirstLocalUserToolkit() const;`
- L70 _public prototype_ `FUniqueNetIdRepl GetFirstLocalUserId(ESocialSubsystem SubsystemType) const;`
- L71 _public prototype_ `bool IsLocalUser(const FUniqueNetIdRepl& LocalUserId, ESocialSubsystem SubsystemType) const;`
- L72 _public prototype_ `int32 GetFirstLocalUserNum() const;`
- L73 _public prototype_ `USocialDebugTools* GetDebugTools() const;`
- L75 _public function_ `DECLARE_EVENT_OneParam(USocialManager, FOnSocialToolkitCreated, USocialToolkit&) FOnSocialToolkitCreated& OnSocialToolkitCreated() const`
- L77 _public function_ `DECLARE_EVENT_OneParam(USocialManager, FOnSocialToolkitDestroyed, USocialToolkit&) FOnSocialToolkitDestroyed& OnSocialToolkitDestroyed() const`
- L81 _public prototype_ `DECLARE_EVENT_OneParam(USocialManager, FOnPartyMembershipChanged, USocialParty&);`
- L82 _public function_ `FOnPartyMembershipChanged& OnPartyJoined() const`
- L84 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnCreatePartyAttemptComplete, ECreatePartyCompletionResult);`
- L85 _public prototype_ `void CreateParty(const FOnlinePartyTypeId& PartyTypeId, const FPartyConfiguration& PartyConfig, const FOnCreatePartyAttemptComplete& OnCreatePartyComplete);`
- L86 _public prototype_ `void CreatePersistentParty(const FOnCreatePartyAttemptComplete& OnCreatePartyComplete = FOnCreatePartyAttemptComplete());`
- L89 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnRestorePartyStateFromPartySystemComplete, bool ) void RestorePartyStateFromPartySystem(const FOnRestorePartyStateFromPartySystemComplete& OnRestoreComplete);` — Attempt to restore our party state from the party system
- L92 _public prototype_ `bool IsPartyJoinInProgress(const FOnlinePartyTypeId& TypeId) const;`
- L93 _public prototype_ `bool IsPersistentPartyJoinInProgress() const;`
- L96 _public function_ `template <typename PartyT = USocialParty> PartyT* GetPersistentParty() const`
- L102 _public function_ `template <typename PartyT = USocialParty> PartyT* GetParty(const FOnlinePartyTypeId& PartyTypeId) const`
- L108 _public function_ `template <typename PartyT = USocialParty> PartyT* GetParty(const FOnlinePartyId& PartyId) const`
- L113 _public prototype_ `bool IsConnectedToPartyService() const;`
- L115 _public prototype_ `void HandlePartyDisconnected(USocialParty* LeavingParty);`
- L122 _public prototype_ `void RegisterSecondaryPlayer(int32 LocalPlayerNum, const FOnJoinPartyComplete& Delegate = FOnJoinPartyComplete());` — Makes an attempt for the target local player to join the primary local player's party @param LocalPlayerNum - ControllerId of the Secondary player that wants to join the party @param Delegate - Delegate run when the join process is finished
- L124 _public prototype_ `virtual void NotifyPartyInitialized(USocialParty& Party);`
- L127 _public prototype_ `virtual FJoinPartyResult ValidateJoinTarget(const USocialUser& UserToJoin, const FOnlinePartyTypeId& PartyTypeId) const;` — `UE_DEPRECATED(5.6, "ValidateJoinTarget has been deprecated, use the overloaded one instead")`
- L129 _public prototype_ `virtual FJoinPartyResult ValidateJoinTarget(const USocialUser& UserToJoin, const FOnlinePartyTypeId& PartyTypeId, bool bCheckPlatformSession) const;` — `UE_DEPRECATED(5.7, "Use ValidateJoinTarget that takes an options struct")`
- L139 _public prototype_ `virtual FJoinPartyResult ValidateJoinTarget(const USocialUser& UserToJoin, const FOnlinePartyTypeId& PartyTypeId, const FValidateJoinTargetOptions& ValidateOptions) const;` — Validates that the target user has valid join info for us to use and that we can join any party of the given type
- L141 _public prototype_ `bool CanAcceptInvitationsFromAwayUsers() const;` — @return true if we can join an away user that has sent us an invitation
- L144 _protected prototype_ `DECLARE_DELEGATE_OneParam(FOnJoinPartyAttemptComplete, const FJoinPartyResult&);`
- L145 _protected prototype_ `void JoinParty(const USocialUser& UserToJoin, const FOnlinePartyTypeId& PartyTypeId, const FOnJoinPartyAttemptComplete& OnJoinPartyComplete, const FName& JoinMethod);`
- L176 _protected prototype_ `virtual void RegisterSocialInteractions();`
- L179 _protected prototype_ `virtual FJoinPartyResult ValidateJoinAttempt(const FOnlinePartyTypeId& PartyTypeId) const;` — Validate that we are clear to try joining a party of the given type. If not, gives the reason why.
- L185 _protected prototype_ `virtual void FillOutJoinRequestData(const FOnlinePartyId& TargetParty, FOnlinePartyData& OutJoinRequestData) const;` — Gives child classes a chance to append any additional data to a join request that's about to be sent to another party. This is where you'll add game-specific information that can affect whether you are eligible for the target party.
- L187 _protected prototype_ `virtual TSubclassOf<USocialParty> GetPartyClassForType(const FOnlinePartyTypeId& PartyTypeId) const;`
- L192 _protected prototype_ `virtual void OnJoinPartyAttemptCompleteInternal(const FJoinPartyAttempt& JoinAttemptInfo, const FJoinPartyResult& Result);`
- L193 _protected function_ `virtual void OnPartyLeftInternal(USocialParty& LeftParty, EMemberExitedReason Reason)`
- L194 _protected prototype_ `virtual void OnToolkitCreatedInternal(USocialToolkit& NewToolkit);`
- L196 _protected prototype_ `virtual bool CanCreateNewPartyObjects() const;`
- L199 _protected prototype_ `virtual ECrossplayPreference GetCrossplayPreference() const;` — Up to the game to decide whether it wants to allow crossplay (generally based on a user setting of some kind)
- L202 _protected function_ `template <typename InteractionT> void RegisterInteraction()`
- L207 _protected prototype_ `void RefreshCanCreatePartyObjects();`
- L209 _protected prototype_ `USocialParty* GetPersistentPartyInternal(bool bEvenIfLeaving = false) const;`
- L212 _public prototype_ `const FJoinPartyAttempt* GetJoinAttemptInProgress(const FOnlinePartyTypeId& PartyTypeId) const;`
- L215 _protected prototype_ `TSharedPtr<const IOnlinePartyJoinInfo> GetJoinInfoFromSession(const FOnlineSessionSearchResult& PlatformSession);`
- L216 _protected prototype_ `void FinishJoinPartyAttempt(FJoinPartyAttempt& JoinAttemptToDestroy, const FJoinPartyResult& JoinResult);`
- L218 _protected prototype_ `virtual TSubclassOf<USocialDebugTools> GetSocialDebugToolsClass() const;`
- L221 _protected member_ `TSubclassOf<USocialToolkit> ToolkitClass;` — The desired type of SocialToolkit to create for each local player
- L224 _protected member_ `bool bShutdownPending = false;` — Set during shutdown, used to early-out of lingering OnlineSubsystem callbacks that are pending
- L226 _protected member_ `TMap<FOnlinePartyTypeId, FJoinPartyAttempt> JoinAttemptsByTypeId;`
- L228 _protected prototype_ `void QueryPartyJoinabilityInternal(FJoinPartyAttempt& JoinAttempt);`
- L230 _protected prototype_ `USocialParty* GetPartyInternal(const FOnlinePartyTypeId& PartyTypeId, bool bIncludeLeavingParties = false) const;`
- L232 _protected prototype_ `virtual void HandleWorldEstablished(UWorld* World);`
- L234 _private prototype_ `UGameInstance& GetGameInstance() const;`
- L235 _private prototype_ `USocialToolkit& CreateSocialToolkit(ULocalPlayer& OwningLocalPlayer, int32 LocalPlayerIndex);`
- L237 _private prototype_ `void JoinPartyInternal(FJoinPartyAttempt& JoinAttempt);`
- L239 _private prototype_ `USocialParty* EstablishNewParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FOnlinePartyTypeId& PartyTypeId);`
- L241 _private prototype_ `USocialParty* GetPartyInternal(const FOnlinePartyId& PartyId, bool bIncludeLeavingParties = false) const;`
- L243 _private prototype_ `void OnCreatePersistentPartyCompleteInternal(ECreatePartyCompletionResult Result, FOnCreatePartyAttemptComplete OnCreatePartyComplete);`
- L244 _private member_ `bool bCreatingPersistentParty = false;`
- L247 _private prototype_ `void HandleGameViewportInitialized();`
- L248 _private prototype_ `void HandlePreClientTravel(const FString& PendingURL, ETravelType TravelType, bool bIsSeamlessTravel);`
- L249 _private prototype_ `void HandleLocalPlayerAdded(int32 LocalUserNum);`
- L250 _private prototype_ `void HandleLocalPlayerRemoved(int32 LocalUserNum);`
- L251 _private prototype_ `void HandleToolkitReset(int32 LocalUserNum);`
- L253 _private prototype_ `void OnRestorePartiesComplete(const FUniqueNetId& LocalUserId, const FOnlineError& Result, const FOnRestorePartyStateFromPartySystemComplete OnRestoreComplete);`
- L254 _private prototype_ `void HandleCreatePartyComplete(const FUniqueNetId& LocalUserId, const TSharedPtr<const FOnlinePartyId>& PartyId, ECreatePartyCompletionResult Result, FOnlinePartyTypeId PartyTypeId, FOnCreatePartyAttemptComplete CompletionDelegate);`
- L255 _private prototype_ `void HandleJoinPartyComplete(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, EJoinPartyCompletionResult Result, int32 NotApprovedReasonCode, FOnlinePartyTypeId PartyTypeId);`
- L257 _private prototype_ `void HandlePersistentPartyStateChanged(EPartyState NewState, EPartyState PreviousState, USocialParty* PersistentParty);`
- L258 _private prototype_ `void HandleLeavePartyForJoinComplete(ELeavePartyCompletionResult LeaveResult, USocialParty* LeftParty);`
- L259 _private prototype_ `void HandlePartyLeaveBegin(EMemberExitedReason Reason, USocialParty* LeavingParty);`
- L260 _private prototype_ `void HandlePartyLeft(EMemberExitedReason Reason, USocialParty* LeftParty);`
- L262 _private prototype_ `void HandleLeavePartyForMissingJoinAttempt(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, ELeavePartyCompletionResult LeaveResult, FOnlinePartyTypeId PartyTypeId);`
- L264 _private prototype_ `void HandleFillPartyJoinRequestData(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, FOnlinePartyData& PartyData);`
- L265 _private prototype_ `void HandleFindSessionForJoinComplete(bool bWasSuccessful, const FOnlineSessionSearchResult& FoundSession, FOnlinePartyTypeId PartyTypeId);`
- L268 _protected prototype_ `virtual void HandleQueryJoinabilityComplete(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FQueryPartyJoinabilityResult& Result, FOnlinePartyTypeId PartyTypeId);`
- L271 _private member_ `static TArray<ESocialSubsystem> DefaultSubsystems;`
- L272 _private member_ `static TArray<FSocialInteractionHandle> RegisteredInteractions;`
- L275 _private member_ `TArray<TObjectPtr<USocialToolkit>> SocialToolkits;` — `UPROPERTY()`
- L278 _private member_ `TObjectPtr<USocialDebugTools> SocialDebugTools;` — `UPROPERTY()`
- L282 _private member_ `FName PresenceFrameworkInstance;` — `UPROPERTY(Config)` — Framework instance name to be used in online services presence functionality
- L286 _private member_ `FName PresenceFrameworkAdapterInstance;` — `UPROPERTY(Config)` — Framework instance name to be used in online services presence functionality where adapter functionality is needed
- L290 _private member_ `bool bAcceptInvitationsFromAwayUsers = true;` — `UPROPERTY(config)` — Can we accept an invitation (ie, join party) from an Away user?
- L292 _private member_ `bool bIsConnectedToPartyService = false;`
- L298 _private member_ `bool bCanCreatePartyObjects = false;` — False during brief windows where the game isn't in a state conducive to creating a new party object and after the manager is completely shut down (prior to being GC'd) Tracked to allow OSS level party activity to execute immediately, but hold off on establishing our local (and replicated) awareness of the party until this client is ready.
- L300 _private member_ `TSharedPtr<FPartyPlatformSessionManager> PartySessionManager;`
- L302 _private member_ `TMap<FOnlinePartyTypeId, TObjectPtr<USocialParty>> JoinedPartiesByTypeId;`
- L303 _private member_ `TMap<FOnlinePartyTypeId, TObjectPtr<USocialParty>> LeavingPartiesByTypeId;`
- L305 _private member_ `FDelegateHandle OnFillJoinRequestInfoHandle;`
- L307 _private member_ `mutable FOnSocialToolkitCreated OnSocialToolkitCreatedEvent;`
- L308 _private member_ `mutable FOnSocialToolkitDestroyed OnSocialToolkitDestroyedEvent;`
- L309 _private member_ `mutable FOnPartyMembershipChanged OnPartyJoinedEvent;`

#### struct `USocialManager::FValidateJoinTargetOptions`  
`struct FValidateJoinTargetOptions`  
_L131-137_
- L134 _public member_ `bool bCheckPlatformSession = true;` — Should we check the platform session for joinability info if the social user is on the same platform as us?
- L136 _public member_ `bool bIsActivelyJoining = true;` — Is this part of an active join flow? There may be stricter checks when this is false (eg, we don't want to show Join UI options), but if we get past that, we may want to continue with a best effort join attempt.

#### struct `USocialManager::FJoinPartyAttempt`  
`struct FJoinPartyAttempt`  
_L148-173_
- L150 _public prototype_ `FJoinPartyAttempt(const USocialUser* InTargetUser, const FOnlinePartyTypeId& InPartyTypeId, const FName& InJoinMethod, const FOnJoinPartyAttemptComplete& InOnJoinComplete);`
- L152 _public prototype_ `FString ToDebugString() const;`
- L154 _public member_ `TWeakObjectPtr<const USocialUser> TargetUser;`
- L155 _public member_ `FOnlinePartyTypeId PartyTypeId;`
- L156 _public member_ `FName JoinMethod = PartyJoinMethod::Unspecified;`
- L157 _public member_ `FUniqueNetIdRepl TargetUserPlatformId;`
- L159 _public member_ `IOnlinePartyJoinInfoConstPtr JoinInfo;`
- L161 _public member_ `FOnJoinPartyAttemptComplete OnJoinComplete;`
- L163 _public member_ `static const FName Step_FindPlatformSession;`
- L164 _public member_ `static const FName Step_QueryJoinability;`
- L165 _public member_ `static const FName Step_LeaveCurrentParty;`
- L166 _public member_ `static const FName Step_JoinParty;`
- L167 _public member_ `static const FName Step_DeferredPartyCreation;`
- L168 _public member_ `static const FName Step_WaitForPersistentPartyCreation;`
- L170 _public member_ `FSocialActionTimeTracker ActionTimeTracker;`
- L172 _public member_ `TMap<FString, FString> AnalyticsContext;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API PARTY_API`
- L30 _macro_ `#define ABORT_DURING_SHUTDOWN() if (IsEngineExitRequested() || bShutdownPending) { UE_LOGF(LogParty, Log, "%ls - Received callback during shutdown: IsEngineExitRequested=%ls, bShutdownPending=%ls.", ANSI_TO_TCHAR(__FUNCTION__), *LexToString`
- L75 _delegate_ `DECLARE_EVENT_OneParam(USocialManager, FOnSocialToolkitCreated, USocialToolkit&) FOnSocialToolkitCreated& OnSocialToolkitCreated() const { return OnSocialToolkitCreatedEvent; } DECLARE_EVENT_OneParam(USocialManager, FOnSocialToolkitDestroyed, USocialToolkit&) FOnSocialToolkitDestroyed& OnSocialToolkitDestroyed() const { return OnSocialToolkitDestroyedEvent; } DECLARE_EVENT_OneParam(USocialManager, FOnPartyMembershipChanged, USocialParty&);`
- L77 _delegate_ `DECLARE_EVENT_OneParam(USocialManager, FOnSocialToolkitDestroyed, USocialToolkit&) FOnSocialToolkitDestroyed& OnSocialToolkitDestroyed() const { return OnSocialToolkitDestroyedEvent; } DECLARE_EVENT_OneParam(USocialManager, FOnPartyMembershipChanged, USocialParty&);`
- L81 _delegate_ `DECLARE_EVENT_OneParam(USocialManager, FOnPartyMembershipChanged, USocialParty&);`
- L84 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCreatePartyAttemptComplete, ECreatePartyCompletionResult);`
- L89 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRestorePartyStateFromPartySystemComplete, bool ) void RestorePartyStateFromPartySystem(const FOnRestorePartyStateFromPartySystemComplete& OnRestoreComplete);` — Attempt to restore our party state from the party system
- L144 _delegate_ `DECLARE_DELEGATE_OneParam(FOnJoinPartyAttemptComplete, const FJoinPartyResult&);`

### `Plugins/Online/OnlineFramework/Source/Party/Public/SocialQuery.h` (Public)


#### class `FSocialQueryBase`  
`class FSocialQueryBase : public TSharedFromThis<FSocialQueryBase>`  
_L9-24_
- inherits: `TSharedFromThis<FSocialQueryBase>`
- L12 _public prototype_ `virtual ~FSocialQueryBase() = default;`
- L13 _public prototype_ `virtual void ExecuteQuery() = 0;`
- L15 _public function_ `bool HasExecuted() const`
- L16 _public function_ `ESocialSubsystem GetSubsystemType() const`
- L17 _public function_ `const USocialToolkit* GetOwningToolkit() const`
- L20 _protected member_ `TWeakObjectPtr<const USocialToolkit> Toolkit;`
- L21 _protected member_ `ESocialSubsystem SubsystemType;`
- L22 _protected member_ `bool bHasExecuted = false;`
- L23 _protected member_ `FOnQueryCompleted OnQueryCompleted;`

#### class `TSocialQuery`  
`template <typename QueryUserIdT, typename... CompletionCallbackArgs> class TSocialQuery : public FSocialQueryBase`  
_L27-67_
- inherits: `FSocialQueryBase`
- L30 _public typedef_ `using FQueryId = QueryUserIdT;`
- L31 _public typedef_ `using FOnQueryComplete = TDelegate<void(ESocialSubsystem, bool, CompletionCallbackArgs...)>;`
- L35 _public prototype_ `static FName GetQueryId();` — All subclasses of TSocialQuery must implement this static method Intentionally not implemented here to catch errors at compile time
- L37 _public function_ `virtual void AddUserId(const QueryUserIdT& UserId, const FOnQueryComplete& QueryCompleteHandler)`
- L43 _public function_ `template <typename OtherQueryT> bool operator==(const TSharedRef<OtherQueryT>& OtherQuery) const`
- L52 _protected function_ `TSocialQuery()`
- L53 _protected function_ `void Initialize(const USocialToolkit& InToolkit, ESocialSubsystem InSubsystemType, const FOnQueryCompleted& InOnQueryCompleted)`
- L60 _protected function_ `inline IOnlineSubsystem* GetOSS() const`
- L65 _protected member_ `static TArray<TSharedRef<TSocialQuery>> CurrentQueries;`
- L66 _protected member_ `TMap<QueryUserIdT, FOnQueryComplete> CompletionCallbacksByUserId;`

#### class `FSocialQueryManager`  
`class FSocialQueryManager`  
_L69-162_
- L73 _public function_ `template <typename SocialQueryT> static TSharedRef<SocialQueryT> GetQuery(const USocialToolkit& Toolkit, ESocialSubsystem SubsystemType)`
- L79 _public function_ `template <typename SocialQueryT> static void AddUserId(const USocialToolkit& Toolkit, ESocialSubsystem InSubsystem, const typename SocialQueryT::FQueryId& InQueryId, const typename SocialQueryT::FOnQueryComplete& OnQueryCompleteHandler)`
- L87 _public function_ `bool HandleExecuteQueries(float)`
- L112 _private function_ `FSocialQueryManager()`
- L114 _private function_ `static FSocialQueryManager& Get()`
- L121 _private function_ `template <typename SocialQueryT> TSharedRef<SocialQueryT> GetQueryInternal(const USocialToolkit& Toolkit, ESocialSubsystem SubsystemType)`
- L152 _private function_ `void HandleQueryComplete(FName QueryId, const TSharedRef<FSocialQueryBase>& Query)`
- L160 _private member_ `FTSTicker::FDelegateHandle TickExecuteHandle;`
- L161 _private member_ `TMap<FName, TArray<TSharedRef<FSocialQueryBase>>> CurrentQueriesById;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnQueryCompleted, FName, const TSharedRef<class FSocialQueryBase>&);`
- L7 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnQueryCompleted, FName, const TSharedRef<class FSocialQueryBase>&);`

### `Plugins/Online/OnlineFramework/Source/Party/Public/SocialSettings.h` (Public)


#### struct `FSocialPlatformDescription`  
`struct FSocialPlatformDescription`  
_L13-45_
- reflection: `USTRUCT()`
- L17 _public function_ `FSocialPlatformDescription()`
- L24 _public member_ `FString Name;` — `UPROPERTY()` — The name of this platform @see IOnlineSubsystem::GetLocalPlatformName
- L28 _public member_ `FString PlatformType;` — `UPROPERTY()` — The type of this platform.  For example DESKTOP or MOBILE
- L32 _public member_ `FName OnlineSubsystem;` — `UPROPERTY()` — The online subsystem this platform uses
- L36 _public member_ `FString SessionType;` — `UPROPERTY()` — The session type this platform uses
- L40 _public member_ `FString ExternalAccountType;` — `UPROPERTY()` — The external association type for this platform
- L44 _public member_ `FString CrossplayPool;` — `UPROPERTY()` — The crossplay pool this platform belongs to

#### class `USocialSettings`  
`class USocialSettings : public UObject`  
_L52-132_
- reflection: `UCLASS(MinimalAPI, Config = Game)`
- inherits: `UObject`
- desc: Config-driven settings object for the social framework. Only the CDO is ever expected to be used, no instance is ever expected to be created.
- L57 _public prototype_ `USocialSettings();`
- L59 _public prototype_ `static FString GetUniqueIdEnvironmentPrefix(ESocialSubsystem SubsystemType);`
- L60 _public prototype_ `static int32 GetDefaultMaxPartySize();`
- L61 _public prototype_ `static bool ShouldPreferPlatformInvites();`
- L62 _public prototype_ `static bool MustSendPrimaryInvites();`
- L63 _public prototype_ `static bool MustAlwaysSendPlatformSessionInvites();`
- L64 _public prototype_ `static bool ShouldLeavePartyOnDisconnect();`
- L65 _public prototype_ `static bool ShouldSetDesiredPrivacyOnLocalPlayerBecomesLeader();`
- L66 _public prototype_ `static float GetUserListAutoUpdateRate();`
- L67 _public prototype_ `static int32 GetMinNicknameLength();`
- L68 _public prototype_ `static int32 GetMaxNicknameLength();`
- L69 _public prototype_ `static const TArray<FSocialPlatformDescription>& GetSocialPlatformDescriptions();`
- L72 _public prototype_ `static bool IsSonyOSS(const FName& OSSName);` — Checks if current OnlineSubsystem name is Sony specific
- L79 _public prototype_ `static const FSocialPlatformDescription* GetSocialPlatformDescriptionForOnlineSubsystem(const FName& OnlineSubsystemName);` — Get a platform description (from GetSocialPlatformDescriptions) for a specific OnlineSubsystem. @param OnlineSubsystemName the online subsystem name to search for @return the social platform description for that online subsystem. May return null if it is not found.
- L90 _private member_ `TArray<FName> OssNamesWithEnvironmentIdPrefix;` — `UPROPERTY(config)` — The specific OSS' that have their IDs stored with an additional prefix for the environment to which they pertain. This is only necessary for OSS' (ex: Switch) that do not have separate environments, just one big pot with both dev and prod users/friendships/etc. For these cases, the linked account ID stored on the Primary UserInfo for this particular OSS will be prefixed with the specific environment in which the linkage exists. Additionally, the prefix must be prepended when mapping the external ID to a primary ID. Overall, it's a major hassle that can hopefully be done away with eventually, but for now is necessary to fake environmental behavior on OSS' without environments.
- L94 _private member_ `int32 DefaultMaxPartySize = 4;` — `UPROPERTY(config)` — How many players are in a party by default
- L98 _private member_ `bool bPreferPlatformInvites = true;` — `UPROPERTY(config)` — If true, prioritize the platform's social system over the publisher's
- L102 _private member_ `bool bMustSendPrimaryInvites = false;` — `UPROPERTY(config)` — If true, always send invites using the publisher's system even if already sent via a platform system
- L106 _private member_ `bool bMustAlwaysSendPlatformInvites=true;` — `UPROPERTY(config)` — Some platforms require a platform invite to be sent along with the in-game invitation, even if the players are not friends in the platform
- L110 _private member_ `bool bLeavePartyOnDisconnect = true;` — `UPROPERTY(config)` — Should we leave a party when it enters the disconnected state?
- L114 _private member_ `bool bSetDesiredPrivacyOnLocalPlayerBecomesLeader = true;` — `UPROPERTY(config)` — How often the user list will update in seconds
- L117 _private member_ `float UserListAutoUpdateRate = 0.5f;` — `UPROPERTY(config)`
- L121 _private member_ `int32 MinNicknameLength = 3;` — `UPROPERTY(Config)` — Shortest possible player nickname
- L125 _private member_ `int32 MaxNicknameLength = 16;` — `UPROPERTY(Config)` — Longest possible player nickname
- L128 _private member_ `TArray<FSocialPlatformDescription> SocialPlatformDescriptions;` — `UPROPERTY(Config)`
- L131 _private member_ `TArray<FName> SonyOSSNames;` — `UPROPERTY(Config)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PARTY_API`

### `Plugins/Online/OnlineFramework/Source/Party/Public/SocialToolkit.h` (Public)


#### class `USocialToolkit`  
`class USocialToolkit : public UObject, public FExec`  
_L49-373_
- reflection: `UCLASS(MinimalAPI, Within = SocialManager, Config = Game)`
- inherits: `UObject,FExec`
- desc: Represents the full suite of social functionality available to a given LocalPlayer
- L59 _public function_ `template <typename ToolkitT = USocialToolkit> static ToolkitT* GetToolkitForPlayer(const ULocalPlayer* LocalPlayer)`
- L65 _public prototype_ `USocialToolkit();`
- L67 _public prototype_ `virtual void InitializeToolkit(ULocalPlayer& InOwningLocalPlayer);`
- L68 _public prototype_ `virtual bool IsOwnerLoggedIn() const;`
- L70 _public prototype_ `USocialChatManager& GetChatManager() const;`
- L72 _public prototype_ `IOnlineSubsystem* GetSocialOss(ESocialSubsystem SubsystemType) const;`
- L74 _public prototype_ `TSharedRef<ISocialUserList> CreateUserList(const FSocialUserListConfig& ListConfig) const;`
- L76 _public prototype_ `USocialUser& GetLocalUser() const;`
- L78 _public prototype_ `FUniqueNetIdRepl GetLocalUserNetId(ESocialSubsystem SubsystemType) const;`
- L79 _public prototype_ `int32 GetLocalUserNum() const;`
- L81 _public prototype_ `const FOnlineUserPresence* GetPresenceInfo(ESocialSubsystem SubsystemType) const;`
- L82 _public prototype_ `const UE::Online::TOnlineResult<UE::Online::FGetCachedPresence> GetPresenceInfoV2(ESocialSubsystem SubsystemType) const;`
- L83 _public prototype_ `virtual void SetLocalUserOnlineState(EOnlinePresenceState::Type OnlineState);`
- L84 _public prototype_ `virtual void SetLocalUserOnlineStateV2(UE::Online::EUserPresenceStatus OnlineState);`
- L87 _public prototype_ `void AddLocalUserOnlineProperties(FPresenceProperties OnlineProperties);` — `UE_DEPRECATED(5.6, "AddLocalUserOnlineProperties is deprecated, please use IOnlinePresence::SetPresence instead.")`
- L89 _public prototype_ `ULocalPlayer* GetOwningLocalPlayerPtr() const;`
- L90 _public prototype_ `USocialManager& GetSocialManager() const;`
- L92 _public function_ `const TArray<USocialUser*>& GetAllUsers() const`
- L95 _public prototype_ `USocialUser* FindUser(const FUniqueNetIdRepl& UserId) const;` — Finds a SocialUser given a unique net ID from any OSS
- L105 _public prototype_ `void QueueUserDependentAction(const FUniqueNetIdRepl& UserId, TFunction<void(USocialUser&)>&& UserActionFunc, bool bExecutePostInit = true);` — Queues an action to be executed when a USocialUser corresponding to the given UniqueId has been established. The process of creating and initializing a user varies in complexity depending on the local user's platform and the OSS the given Id corresponds to. Up to the caller whether they want the action executed immediately upon creation of the USocialUser instance, or after the instance is fully initialized (i.e. has finished discovering all available backend information) Default is to execute after initialization and is generally more appropriate.
- L106 _public prototype_ `void QueueUserDependentAction(const FUniqueNetIdRepl& SubsystemId, FUserDependentAction UserActionDelegate);`
- L112 _public prototype_ `void TrySendFriendInvite(const FString& DisplayNameOrEmail) const;` — Attempts to send a friend invite to another user based on display name or email. Only necessary to use this path when you do not have a known USocialUser for this user already.
- L114 _public prototype_ `virtual bool IsFriendshipRestricted(const USocialUser& SocialUser, ESocialSubsystem SubsystemType) const;`
- L116 _public prototype_ `bool GetAuthAttribute(ESocialSubsystem SubsystemType, const FString& AttributeKey, FString& OutValue) const;`
- L118 _public function_ `const FString& GetRecentPlayerNamespaceToQuery() const`
- L121 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoginChanged, bool );` — Event triggered when the owning local player's login status changes
- L122 _public function_ `FOnLoginChanged& OnLoginChanged() const`
- L124 _public prototype_ `DECLARE_EVENT_OneParam(USocialToolkit, FPartyInviteEvent, USocialUser&);`
- L125 _public function_ `FPartyInviteEvent& OnPartyInviteReceived() const`
- L126 _public function_ `FPartyInviteEvent& OnPartyInviteRemoved() const`
- L128 _public prototype_ `DECLARE_EVENT_TwoParams(USocialToolkit, FFriendInviteEvent, USocialUser&, ESocialSubsystem);`
- L129 _public function_ `FFriendInviteEvent& OnFriendInviteSent() const`
- L130 _public function_ `FFriendInviteEvent& OnFriendInviteReceived() const`
- L132 _public prototype_ `DECLARE_EVENT_ThreeParams(USocialToolkit, FOnRelationshipEstablished, USocialUser&, ESocialSubsystem, bool );`
- L133 _public function_ `FOnRelationshipEstablished& OnFriendshipEstablished() const`
- L134 _public function_ `FOnRelationshipEstablished& OnUserBlocked() const`
- L135 _public function_ `FOnRelationshipEstablished& OnRecentPlayerAdded() const`
- L137 _public prototype_ `DECLARE_EVENT_OneParam(USocialToolkit, FOnKnownUserInitialized, USocialUser&);`
- L138 _public function_ `FOnKnownUserInitialized& OnKnownUserInitialized()`
- L140 _public prototype_ `DECLARE_EVENT_OneParam(USocialToolkit, FOnSocialUserInvalidated, const USocialUser&);`
- L141 _public function_ `FOnSocialUserInvalidated& OnSocialUserInvalidated()`
- L143 _public prototype_ `DECLARE_EVENT(USocialToolkit, FBasicToolkitEvent);`
- L144 _public function_ `FBasicToolkitEvent& OnToolkitReset() const`
- L146 _public prototype_ `DECLARE_EVENT_OneParam(USocialToolkit, FOnPartyRequestToJoinSentEvent, const USocialUser&);`
- L147 _public function_ `FOnPartyRequestToJoinSentEvent& OnPartyRequestToJoinSent() const`
- L149 _public prototype_ `DECLARE_EVENT_TwoParams(USocialToolkit, FOnPartyRequestToJoinReceivedEvent, USocialUser& , IOnlinePartyRequestToJoinInfoConstRef );`
- L150 _public function_ `FOnPartyRequestToJoinReceivedEvent& OnPartyRequestToJoinReceived() const`
- L152 _public prototype_ `DECLARE_EVENT_ThreeParams(USocialToolkit, FOnPartyRequestToJoinRemovedEvent, USocialUser& , IOnlinePartyRequestToJoinInfoConstRef , EPartyRequestToJoinRemovedReason );`
- L153 _public function_ `FOnPartyRequestToJoinRemovedEvent& OnPartyRequestToJoinRemoved() const`
- L155 _public prototype_ `virtual void NotifyPartyInviteReceived(USocialUser& SocialUser, const IOnlinePartyJoinInfo& Invite);`
- L156 _public prototype_ `virtual void NotifyPartyInviteRemoved(USocialUser& SocialUser, const IOnlinePartyJoinInfo& Invite);`
- L164 _public function_ `virtual bool CanAutoRecreatePersistentParty() const` — Can we automatically re-create a persistent party, for example on party join failure or on party kick? Typically you will want to, so the user always has a party, but there may be scenarios where you want to delay creating a new party until the client is in a better state. @return true if we can automatically recreate a persistent party
- L167 _public function_ `bool Debug_IsRandomlyChangingPresence() const`
- L171 _protected prototype_ `void NotifySubsystemIdEstablished(USocialUser& SocialUser, ESocialSubsystem SubsystemType, const FUniqueNetIdRepl& SubsystemId);`
- L172 _protected function_ `TSubclassOf<USocialChatManager> GetChatManagerClass()`
- L174 _protected prototype_ `bool TrySendFriendInvite(USocialUser& SocialUser, ESocialSubsystem SubsystemType) const;`
- L176 _protected prototype_ `bool AcceptFriendInvite(const USocialUser& SocialUser, ESocialSubsystem SubsystemType) const;`
- L178 _protected prototype_ `void HandleUserInvalidated(USocialUser& InvalidUser);`
- L181 _protected prototype_ `void NotifyPSNFriendsListRebuilt();`
- L186 _protected prototype_ `virtual bool SendFriendInviteInternal(USocialUser& SocialUser, ESocialSubsystem SubsystemType) const;` — only handles sending a friend request via the friends interface, assumes all checks are handled previously
- L188 _protected prototype_ `virtual bool AcceptFriendInviteInternal(const USocialUser& SocialUser, ESocialSubsystem SubsystemType) const;` — only handles accepting a friend request via the friends interface, assumes all checks are handled previously
- L190 _protected prototype_ `virtual void OnOwnerLoggedIn();`
- L191 _protected prototype_ `virtual void OnOwnerLoggedOut();`
- L193 _protected function_ `virtual void OnSendFriendInviteComplete(const FUniqueNetId& InvitedUserId, const FString& InviteeName, bool bInviteSuceeded, const FString& InviteError)`
- L194 _protected function_ `virtual void OnAcceptFriendInviteComplete(const FUniqueNetId& InviterUserId, bool bInviteSucceeded, const FString& InviteError)`
- L195 _protected function_ `virtual void OnReadFriendsListComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr, ESocialSubsystem SubsystemType)`
- L196 _protected function_ `virtual void OnQueryBlockedPlayersComplete(const FUniqueNetId& UserId, bool bWasSuccessful, const FString& ErrorStr, ESocialSubsystem SubsystemType)`
- L197 _protected function_ `virtual void OnQueryRecentPlayersComplete(const FUniqueNetId& UserId, const FString& Namespace, bool bWasSuccessful, const FString& ErrorStr, ESocialSubsystem SubsystemType)`
- L198 _protected function_ `virtual void OnDeleteFriendComplete(int32 LocalPlayer, bool bWasSuccessful, const FUniqueNetId& FormerFriendId, const FString& ListName, const FString& ErrorStr, ESocialSubsystem SubsystemType)`
- L199 _protected function_ `virtual void OnBlockPlayerComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& BlockedPlayerID, const FString& ListName, const FString& ErrorStr, ESocialSubsystem SubsystemType)`
- L200 _protected function_ `virtual void OnUnblockPlayerComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UnblockedPlayerID, const FString& ListName, const FString& ErrorStr, ESocialSubsystem SubsystemType)`
- L204 _protected function_ `virtual void OnFriendPresenceDidChange(const USocialUser& FriendSocialUser, const TSharedRef<FOnlineUserPresence>& NewPresence, ESocialSubsystem SubsystemType)` — Called when a Friend's presence did change
- L205 _protected function_ `virtual void OnFriendPresenceDidChangeV2(const USocialUser& FriendSocialUser, const TSharedRef<const UE::Online::FUserPresence>& NewPresence, ESocialSubsystem SubsystemType)`
- L207 _protected prototype_ `void QueryFriendsLists();`
- L208 _protected prototype_ `void QueryBlockedPlayers();`
- L209 _protected prototype_ `void QueryRecentPlayers();`
- L211 _protected function_ `virtual void OnQueryFriendsListSuccess(ESocialSubsystem SubsystemType, const TArray<TSharedRef<FOnlineFriend>>& FriendsList)`
- L212 _protected function_ `virtual void OnQueryBlockedPlayersSuccess(ESocialSubsystem SubsystemType, const TArray<TSharedRef<FOnlineBlockedPlayer>>& BlockedPlayers)`
- L213 _protected function_ `virtual void OnQueryRecentPlayersSuccess(ESocialSubsystem SubsystemType, const TArray<TSharedRef<FOnlineRecentPlayer>>& FriendsList)`
- L216 _protected prototype_ `void HandleSendFriendInviteComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& InvitedUserId, const FString& ListName, const FString& ErrorStr, ESocialSubsystem SubsystemType, FString DisplayName);` — handle result of TrySendFriendInviteInternal
- L218 _protected prototype_ `void HandleAcceptFriendInviteComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& InviterUserId, const FString& ListName, const FString& ErrorStr);` — handle result of AcceptFriendInvite
- L221 _protected member_ `TSubclassOf<USocialUser> SocialUserClass;` — The type of SocialUser to create to represent known users
- L224 _protected member_ `TSubclassOf<USocialChatManager> ChatManagerClass;` — Class to use when creating the ChatManager
- L227 _protected member_ `FString FriendListToQuery = TEXT("def` — The name of the friends list to query
- L230 _protected member_ `FString RecentPlayerNamespaceToQuery;` — The name of the recent player namespace to query
- L234 _protected member_ `bool bQueryFriendsOnStartup = true;` — @todo DanH: Basic idea here is that the toolkit may not want to query all of these things up-front for scalability reasons, some it may want to wait on until some requirement is met Something nicer is definitely possible and worth revisiting
- L235 _protected member_ `bool bQueryBlockedPlayersOnStartup = true;`
- L236 _protected member_ `bool bQueryRecentPlayersOnStartup = true;`
- L239 _protected prototype_ `virtual const bool IsInviteAllowedFromUser(const USocialUser& User, const TSharedRef<const IOnlinePartyJoinInfo>& InviteRef) const;` — Whether we allow other users to send us invites
- L242 _private prototype_ `void QueueUserDependentActionInternal(const FUniqueNetIdRepl& SubsystemId, ESocialSubsystem SubsystemType, TFunction<void(USocialUser&)>&& UserActionFunc, bool bExecutePostInit = true);`
- L245 _private function_ `template <typename OnlineUserT> void ProcessUserList(const TArray<TSharedRef<OnlineUserT>>& OssUserList, ESocialSubsystem SubsystemType, FOnRelationshipEstablished& RelationshipEvent)`
- L264 _private prototype_ `void HandleControllerIdChanged(int32 NewId, int32 OldId);`
- L265 _private prototype_ `void HandlePlayerLoginStatusChanged(int32 LocalUserNum, ELoginStatus::Type OldStatus, ELoginStatus::Type NewStatus, const FUniqueNetId& NewId);`
- L267 _private prototype_ `void HandleReadFriendsListComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr, ESocialSubsystem SubsystemType);`
- L268 _private prototype_ `void HandleQueryBlockedPlayersComplete(const FUniqueNetId& UserId, bool bWasSuccessful, const FString& ErrorStr, ESocialSubsystem SubsystemType);`
- L269 _private prototype_ `void HandleQueryRecentPlayersComplete(const FUniqueNetId& UserId, const FString& Namespace, bool bWasSuccessful, const FString& ErrorStr, ESocialSubsystem SubsystemType);`
- L271 _private prototype_ `void HandleRecentPlayersAdded(const FUniqueNetId& LocalUserId, const TArray<TSharedRef<FOnlineRecentPlayer>>& NewRecentPlayers, ESocialSubsystem SubsystemType);`
- L273 _private prototype_ `void HandleMapExternalIdComplete(ESocialSubsystem SubsystemType, bool bWasSuccessful, const FUniqueNetIdRepl& MappedPrimaryId, FUniqueNetIdRepl ExternalId, TFunction<void(USocialUser&)> UserActionFunc, bool bExecutePostInit);`
- L274 _private prototype_ `void HandlePresenceReceived(const FUniqueNetId& UserId, const TSharedRef<FOnlineUserPresence>& NewPresence, ESocialSubsystem SubsystemType);`
- L275 _private prototype_ `void HandleServicesPresenceUpdated(const UE::Online::FPresenceUpdated& Event, ESocialSubsystem SubsystemType);`
- L276 _private prototype_ `void HandlePresenceReadCVarChanged(IConsoleVariable*);`
- L278 _private prototype_ `void HandleFriendInviteReceived(const FUniqueNetId& LocalUserId, const FUniqueNetId& SenderId, ESocialSubsystem SubsystemType);`
- L279 _private prototype_ `void HandleFriendInviteAccepted(const FUniqueNetId& LocalUserId, const FUniqueNetId& NewFriendId, ESocialSubsystem SubsystemType);`
- L280 _private prototype_ `void HandleFriendInviteRejected(const FUniqueNetId& LocalUserId, const FUniqueNetId& RejecterId, ESocialSubsystem SubsystemType);`
- L281 _private prototype_ `void HandleFriendRemoved(const FUniqueNetId& LocalUserId, const FUniqueNetId& FormerFriendId, ESocialSubsystem SubsystemType);`
- L283 _private prototype_ `void HandleDeleteFriendComplete(int32 LocalPlayer, bool bWasSuccessful, const FUniqueNetId& FormerFriendId, const FString& ListName, const FString& ErrorStr, ESocialSubsystem SubsystemType);`
- L284 _private prototype_ `void HandleFriendsChanged(ESocialSubsystem SubsystemType);`
- L286 _private prototype_ `void HandlePartyInviteReceived(const FUniqueNetId& LocalUserId, const IOnlinePartyJoinInfo& Invite);`
- L287 _private prototype_ `void HandlePartyInviteRemoved(const FUniqueNetId& LocalUserId, const IOnlinePartyJoinInfo& Invite, EPartyInvitationRemovedReason Reason);`
- L288 _private prototype_ `void HandlePartyDataReceived(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FName& Namespace, const FOnlinePartyData& PartyData);`
- L291 _private prototype_ `void CanReceiveInviteFrom(USocialUser& SocialUser, const IOnlinePartyJoinInfoConstRef& Invite, TFunction<void(const bool )>&& CompletionFunc);`
- L294 _private prototype_ `void HandleBlockPlayerComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& BlockedPlayerID, const FString& ListName, const FString& ErrorStr, ESocialSubsystem SubsystemType);`
- L295 _private prototype_ `void HandleUnblockPlayerComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UnblockedPlayerID, const FString& ListName, const FString& ErrorStr, ESocialSubsystem SubsystemType);`
- L297 _private prototype_ `void HandleBlockListChanged(int32 LocalUserNum, const FString& ListName, ESocialSubsystem SubsystemType);`
- L299 _private prototype_ `void HandleQueryPrimaryUserIdMappingComplete(bool bWasSuccessful, const FUniqueNetId& RequestingUserId, const FString& DisplayName, const FUniqueNetId& IdentifiedUserId, const FString& Error);`
- L301 _private prototype_ `void HandlePartyMemberExited(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& MemberId, const EMemberExitedReason Reason);`
- L302 _private prototype_ `void HandleGameDestroyed(const FName SessionName, bool bWasSuccessful);`
- L304 _private prototype_ `void HandleExistingPartyInvites(ESocialSubsystem SubsystemType);`
- L306 _private prototype_ `void HandlePartyRequestToJoinReceived(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& RequesterId, const IOnlinePartyRequestToJoinInfo& Request);`
- L307 _private prototype_ `void HandlePartyRequestToJoinRemoved(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& RequesterId, const IOnlinePartyRequestToJoinInfo& Request, EPartyRequestToJoinRemovedReason Reason);`
- L310 _private prototype_ `void Debug_OnStartRandomizeUserPresence(uint8 NumRandomUser, float TickerTimer);`
- L311 _private prototype_ `void Debug_OnStopRandomizeUserPresence(bool bClearGeneratedPresence);`
- L312 _private prototype_ `bool Debug_HandleRandomizeUserPresenceTick(float DeltaTime, uint8 NumRandomUser);`
- L313 _private prototype_ `void Debug_ChangeRandomUserPresence(uint8 NumRandomUser);`
- L314 _private member_ `bool bDebug_IsRandomlyChangingUserPresence = false;`
- L315 _private member_ `FTSTicker::FDelegateHandle Debug_PresenceTickerHandle;`
- L318 _private member_ `TMap<ESocialSubsystem, UE::Online::FOnlineEventDelegateHandle> OnPresenceUpdatedHandles;`
- L319 _private member_ `FDelegateHandle OnReadPresenceV2CVarChanged;`
- L323 _protected member_ `TObjectPtr<USocialChatManager> SocialChatManager;` — `UPROPERTY()`
- L326 _private prototype_ `static USocialToolkit* GetToolkitForPlayerInternal(const ULocalPlayer* LocalPlayer);`
- L327 _private member_ `static TMap<TWeakObjectPtr<const ULocalPlayer>, TWeakObjectPtr<USocialToolkit>> AllToolkitsByOwningPlayer;`
- L330 _private member_ `TObjectPtr<USocialUser> LocalUser;` — `UPROPERTY()`
- L333 _private member_ `TArray<TObjectPtr<USocialUser>> AllUsers;` — `UPROPERTY()`
- L335 _private prototype_ `void ProcessOSSBlockedPlayers(ESocialSubsystem SubsystemType, const TArray<TSharedRef<FOnlineBlockedPlayer>>& BlockedPlayers);`
- L336 _private member_ `TMap<ESocialSubsystem, TSet<FUniqueNetIdRepl>> BlockedUsers;`
- L338 _private member_ `TMap<FUniqueNetIdRepl, TWeakObjectPtr<USocialUser>> UsersBySubsystemIds;`
- L341 _private member_ `bool bRemoveInvalidatedUserFromMaps = true;` — `UPROPERTY(config)`
- L344 _private member_ `TWeakObjectPtr<ULocalPlayer> LocalPlayerOwner = nullptr;` — `UPROPERTY()`
- L346 _private member_ `TSet<UE::Online::FAccountId> NonReadPresencesReceivedV2;`
- L347 _private member_ `FUniqueNetIdSet NonReadPresencesReceivedV1;`
- L349 _private member_ `TSet<IOnlinePartyJoinInfoConstRef> PartyInvitations;`
- L350 _private member_ `mutable TArray<TWeakPtr<FSocialUserList>> CachedSocialUserLists;`
- L352 _private member_ `mutable FOnLoginChanged OnLoginChangedEvent;`
- L354 _private member_ `mutable FPartyInviteEvent OnPartyInviteReceivedEvent;`
- L355 _private member_ `mutable FPartyInviteEvent OnPartyInviteAcceptedEvent;`
- L356 _private member_ `mutable FPartyInviteEvent OnPartyInviteRejectedEvent;`
- L357 _private member_ `mutable FPartyInviteEvent OnPartyInviteRemovedEvent;`
- L359 _private member_ `mutable FFriendInviteEvent OnFriendInviteReceivedEvent;`
- L360 _private member_ `mutable FFriendInviteEvent OnFriendInviteSentEvent;`
- L362 _private member_ `mutable FOnRelationshipEstablished OnFriendshipEstablishedEvent;`
- L363 _private member_ `mutable FOnRelationshipEstablished OnUserBlockedEvent;`
- L364 _private member_ `mutable FOnRelationshipEstablished OnRecentPlayerAddedEvent;`
- L366 _private member_ `mutable FOnKnownUserInitialized OnKnownUserInitializedEvent;`
- L367 _private member_ `mutable FOnSocialUserInvalidated OnSocialUserInvalidatedEvent;`
- L368 _private member_ `mutable FBasicToolkitEvent OnToolkitResetEvent;`
- L370 _private member_ `mutable FOnPartyRequestToJoinSentEvent OnPartyRequestToJoinSentEvent;`
- L371 _private member_ `mutable FOnPartyRequestToJoinReceivedEvent OnPartyRequestToJoinReceivedEvent;`
- L372 _private member_ `mutable FOnPartyRequestToJoinRemovedEvent OnPartyRequestToJoinRemovedEvent;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API PARTY_API`
- L33 _namespace_ `namespace FriendInviteFailureReason`
- L35 _externvar_ `extern const FString InviteFailReason_NotFound;` (scope `FriendInviteFailureReason`)
- L36 _externvar_ `extern const FString InviteFailReason_AddingSelfFail;` (scope `FriendInviteFailureReason`)
- L37 _externvar_ `extern const FString InviteFailReason_AddingBlockedFail;` (scope `FriendInviteFailureReason`)
- L38 _externvar_ `extern const FString InviteFailReason_AlreadyFriends;` (scope `FriendInviteFailureReason`)
- L40 _namespace_ `namespace FriendAcceptFailureReason`
- L42 _externvar_ `extern const FString AcceptFailReason_NotPendingInbound;` (scope `FriendAcceptFailureReason`)
- L45 _delegate_ `DECLARE_DELEGATE_OneParam(FUserDependentAction, USocialUser&);`
- L45 _prototype_ `DECLARE_DELEGATE_OneParam(FUserDependentAction, USocialUser&);`
- L121 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoginChanged, bool );` — Event triggered when the owning local player's login status changes
- L124 _delegate_ `DECLARE_EVENT_OneParam(USocialToolkit, FPartyInviteEvent, USocialUser&);`
- L128 _delegate_ `DECLARE_EVENT_TwoParams(USocialToolkit, FFriendInviteEvent, USocialUser&, ESocialSubsystem);`
- L132 _delegate_ `DECLARE_EVENT_ThreeParams(USocialToolkit, FOnRelationshipEstablished, USocialUser&, ESocialSubsystem, bool );`
- L137 _delegate_ `DECLARE_EVENT_OneParam(USocialToolkit, FOnKnownUserInitialized, USocialUser&);`
- L140 _delegate_ `DECLARE_EVENT_OneParam(USocialToolkit, FOnSocialUserInvalidated, const USocialUser&);`
- L143 _delegate_ `DECLARE_EVENT(USocialToolkit, FBasicToolkitEvent);`
- L146 _delegate_ `DECLARE_EVENT_OneParam(USocialToolkit, FOnPartyRequestToJoinSentEvent, const USocialUser&);`
- L149 _delegate_ `DECLARE_EVENT_TwoParams(USocialToolkit, FOnPartyRequestToJoinReceivedEvent, USocialUser& , IOnlinePartyRequestToJoinInfoConstRef );`
- L152 _delegate_ `DECLARE_EVENT_ThreeParams(USocialToolkit, FOnPartyRequestToJoinRemovedEvent, USocialUser& , IOnlinePartyRequestToJoinInfoConstRef , EPartyRequestToJoinRemovedReason );`
- L252 _function_ `` (scope `USocialToolkit::ProcessUserList`)

### `Plugins/Online/OnlineFramework/Source/Party/Public/SocialTypes.h` (Public)


#### enum `ESocialSubsystem`  
`enum class ESocialSubsystem : uint8`  
_L17-29_
- reflection: `UENUM()`
- desc: All supported subsystems
- L20 _public enumerator_ `Primary` — Publisher-level cross-platform OSS
- L22 _public enumerator_ `Platform` — OSS specific to the platform on which we're running (PSN, XBL, GameCenter, etc.)
- L28 _public enumerator_ `MAX` — Facebook, Google, Twitch,

#### enum `ESocialRelationship`  
`enum class ESocialRelationship : uint8`  
_L46-59_
- reflection: `UENUM()`
- desc: Per-OSS relationship types
- L48 _public enumerator_ `Any`
- L49 _public enumerator_ `FriendInviteReceived`
- L50 _public enumerator_ `FriendInviteSent`
- L51 _public enumerator_ `PartyInvite`
- L52 _public enumerator_ `Friend`
- L53 _public enumerator_ `BlockedPlayer`
- L54 _public enumerator_ `SuggestedFriend`
- L55 _public enumerator_ `RecentPlayer`
- L56 _public enumerator_ `JoinRequest`
- L57 _public enumerator_ `AnyWithLocal`

#### enum `ECrossplayPreference`  
`enum class ECrossplayPreference : uint8`  
_L81-87_
- reflection: `UENUM()`
- L83 _public enumerator_ `NoSelection`
- L84 _public enumerator_ `OptedIn`
- L85 _public enumerator_ `OptedOut`
- L86 _public enumerator_ `OptedOutRestricted`

#### struct `FUserPlatform`  
`struct FUserPlatform`  
_L91-120_
- reflection: `USTRUCT()`
- desc: Thin wrapper to infuse a raw platform string with some meaning
- L96 _public prototype_ `FUserPlatform();`
- L97 _public prototype_ `FUserPlatform(const FString& InPlatform);`
- L99 _public function_ `operator const FString&() const`
- L100 _public function_ `const FString& ToString() const`
- L101 _public function_ `const FString& GetTypeName() const`
- L102 _public function_ `const FSocialPlatformDescription& GetPlatformDescription() const`
- L104 _public prototype_ `bool operator==(const FString& OtherStr) const;`
- L105 _public function_ `bool operator!=(const FString& OtherStr) const`
- L106 _public prototype_ `bool operator==(const FUserPlatform& Other) const;`
- L107 _public function_ `bool operator!=(const FUserPlatform& Other) const`
- L109 _public prototype_ `bool IsValid() const;`
- L110 _public prototype_ `bool IsDesktop() const;`
- L111 _public prototype_ `bool IsMobile() const;`
- L112 _public prototype_ `bool IsConsole() const;`
- L113 _public prototype_ `bool IsCrossplayWith(const FString& OtherPlatformStr) const;`
- L114 _public prototype_ `bool IsCrossplayWith(const FUserPlatform& OtherPlatform) const;`
- L115 _public prototype_ `bool IsCrossplayWithLocalPlatform() const;`
- L119 _private member_ `FSocialPlatformDescription PlatformDescription;` — `UPROPERTY()`

#### struct `FSocialActionTimeTracker`  
`struct FSocialActionTimeTracker`  
_L133-156_
- L135 _public prototype_ `void BeginStep(FName StepName);`
- L136 _public prototype_ `void CompleteStep(FName StepName);`
- L138 _public prototype_ `double GetActionStartTime() const;`
- L139 _public prototype_ `double GetTotalDurationMs() const;`
- L141 _public prototype_ `FName GetCurrentStepName() const;`
- L142 _public prototype_ `double GetStepDurationMs(FName StepName) const;`
- L155 _private member_ `TArray<FSocialActionStep> ActionSteps;`

#### struct `FSocialActionTimeTracker::FSocialActionStep`  
`struct FSocialActionStep`  
_L145-153_
- L147 _public member_ `FName StepName;`
- L148 _public member_ `double StartTime = FPlatformTime::Seconds();`
- L149 _public member_ `double EndTime = 0.0;`
- L151 _public prototype_ `double GetDurationMs() const;`
- L152 _public function_ `bool operator==(FName OtherStepName) const`

#### enum `EPlatformIconDisplayRule`  
`enum class EPlatformIconDisplayRule : uint8`  
_L159-166_
- reflection: `UENUM()`
- L161 _public enumerator_ `Always` — always show the platform icon
- L162 _public enumerator_ `AlwaysIfDifferent` — always show the icon if it's a different platform from my own
- L163 _public enumerator_ `AlwaysWhenInCrossplayParty` — always show the icon if I'm in a crossplay party
- L164 _public enumerator_ `AlwaysIfDifferentWhenInCrossplayParty` — only show the icon if it's different from my own and I'm in a crossplay party
- L165 _public enumerator_ `Never` — never show the icon

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PARTY_API`
- L31 _function_ `inline const TCHAR* LexToString(ESocialSubsystem InSubsystem)`
- L61 _function_ `inline const TCHAR* LexToString(ESocialRelationship Relationship)`
- L122 _function_ `inline bool OptedOutOfCrossplay(ECrossplayPreference InPreference)`
- L168 _macro_ `#define DECLARE_SHARED_PTR_ALIASES(Type) \`
- L175 _prototype_ `DECLARE_SHARED_PTR_ALIASES(ISocialUserList);`
- L176 _prototype_ `DECLARE_SHARED_PTR_ALIASES(FSocialChatMessage);`
- L178 _function_ `inline const TCHAR* ToString(ESocialSubsystem SocialSubsystem)`
- L188 _function_ `inline const TCHAR* LexToString(ECrossplayPreference Preference)`

### `Plugins/Online/OnlineFramework/Source/Party/Public/User/ISocialUserList.h` (Public)


#### enum `ESocialUserStateFlags`  
`enum class ESocialUserStateFlags`  
_L13-23_
- desc: OSS-agnostic user state filters (presence info generally required). Some of these do imply others and some conflict. Up to consumers to responsibly choose appropriate combinations.
- L15 _public enumerator_ `None = 0`
- L16 _public enumerator_ `Online = 1`
- L17 _public enumerator_ `Joinable = 1 << 1`
- L18 _public enumerator_ `LookingForGroup = 1 << 2`
- L19 _public enumerator_ `SamePlatform = 1 << 3`
- L20 _public enumerator_ `InGame = 1 << 4`
- L21 _public enumerator_ `SameApp = 1 << 5`
- L22 _public enumerator_ `SameParty = 1 << 6`

#### class `FSocialUserListConfig`  
`class FSocialUserListConfig`  
_L28-78_
- desc: Configuration of ISocialUserList properties that are immutable once the list is created.
- L31 _public function_ `FSocialUserListConfig()`
- L33 _public member_ `FString Name = TEXT("");`
- L34 _public member_ `ESocialRelationship RelationshipType = ESocialRelationship::Friend;`
- L35 _public member_ `TArray<ESocialSubsystem> RelevantSubsystems;`
- L36 _public member_ `TArray<ESocialSubsystem> ForbiddenSubsystems;`
- L37 _public member_ `ESocialUserStateFlags RequiredPresenceFlags = ESocialUserStateFlags::None;`
- L38 _public member_ `ESocialUserStateFlags ForbiddenPresenceFlags = ESocialUserStateFlags::None;`
- L41 _public member_ `FOnCustomFilterUser OnCustomFilterUser;` — Delegate that is evaluated every time we test a user for inclusion/exclusion
- L44 _public member_ `TArray<TFunction<bool(const USocialUser&)>> GameSpecificStatusFilters;` — These functions run whenever the User broadcasts OnGameSpecificStatusChanged and if they all return true will trigger a full re-evaluation of this user for list eligibility
- L47 _public member_ `bool bAutoUpdate = false;` — Whether or not the list should be polled regularly for updates (as opposed to manually having UpdateNow triggered)
- L49 _public member_ `bool bSortDuringUpdate = true;`
- L51 _public function_ `bool operator==(const FSocialUserListConfig& OtherConfig) const`
- L69 _private function_ `uint8 CompoundSubsystemEnum(const TArray<ESocialSubsystem>& Subsystems ) const`

#### class `ISocialUserList`  
`class ISocialUserList`  
_L80-107_
- L83 _public prototype_ `virtual ~ISocialUserList() = default;`
- L85 _public prototype_ `DECLARE_EVENT_OneParam(ISocialUserList, FOnUserAdded, USocialUser&) virtual FOnUserAdded& OnUserAdded() const = 0;`
- L88 _public prototype_ `DECLARE_EVENT_OneParam(ISocialUserList, FOnUserRemoved, const USocialUser&) virtual FOnUserRemoved& OnUserRemoved() const = 0;`
- L92 _public prototype_ `DECLARE_EVENT(ISocialUserList, FOnUpdateComplete) virtual FOnUpdateComplete& OnUpdateComplete() const = 0;` — Fires one time whenever an update results in some kind of change
- L95 _public prototype_ `virtual const TArray<TWeakObjectPtr<USocialUser>>& GetUsers() const = 0;`
- L96 _public prototype_ `virtual FString GetListName() const = 0;`
- L99 _public prototype_ `virtual void UpdateNow() = 0;` — Trigger an update of the list immediately, regardless of auto update period
- L102 _public prototype_ `virtual void SetAllowAutoUpdate(bool bIsEnabled) = 0;` — Give external overwrite to disable list auto update for perf
- L104 _public prototype_ `virtual void SetAllowSortDuringUpdate(bool bIsEnabled) = 0;`
- L106 _public prototype_ `virtual void MarkUserAsDirty(USocialUser& User) = 0;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnCustomFilterUser, const USocialUser&);`
- L10 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnCustomFilterUser, const USocialUser&);`
- L25 _prototype_ `ENUM_CLASS_FLAGS(ESocialUserStateFlags);`
- L85 _delegate_ `DECLARE_EVENT_OneParam(ISocialUserList, FOnUserAdded, USocialUser&) virtual FOnUserAdded& OnUserAdded() const = 0;`
- L88 _delegate_ `DECLARE_EVENT_OneParam(ISocialUserList, FOnUserRemoved, const USocialUser&) virtual FOnUserRemoved& OnUserRemoved() const = 0;`
- L92 _delegate_ `DECLARE_EVENT(ISocialUserList, FOnUpdateComplete) virtual FOnUpdateComplete& OnUpdateComplete() const = 0;` — Fires one time whenever an update results in some kind of change

### `Plugins/Online/OnlineFramework/Source/Party/Public/User/SocialUser.h` (Public)


#### class `USocialUser`  
`class USocialUser : public UObject`  
_L39-301_
- reflection: `UCLASS(MinimalAPI, Within = SocialToolkit)`
- inherits: `UObject`
- L46 _public prototype_ `USocialUser();`
- L47 _public prototype_ `~USocialUser();`
- L49 _public prototype_ `void RegisterInitCompleteHandler(const FOnNewSocialUserInitialized& OnInitializationComplete);`
- L50 _public function_ `bool IsInitialized() const`
- L52 _public prototype_ `void ValidateFriendInfo(ESocialSubsystem SubsystemType);`
- L53 _public prototype_ `TArray<ESocialSubsystem> GetRelationshipSubsystems(ESocialRelationship Relationship) const;`
- L54 _public prototype_ `TArray<ESocialSubsystem> GetRelevantSubsystems() const;`
- L55 _public prototype_ `bool HasSubsystemInfo(ESocialSubsystem Subsystem) const;`
- L56 _public prototype_ `bool HasSubsystemInfo(const TSet<ESocialSubsystem>& SubsystemTypes, bool bRequireAll = false);`
- L58 _public prototype_ `bool IsLocalUser() const;`
- L59 _public prototype_ `bool HasNetId(const FUniqueNetIdRepl& UniqueId) const;`
- L60 _public prototype_ `USocialToolkit& GetOwningToolkit() const;`
- L61 _public prototype_ `EOnlinePresenceState::Type GetOnlineStatus() const;`
- L62 _public prototype_ `UE::Online::EUserPresenceStatus GetOnlineStatusV2() const;`
- L64 _public prototype_ `FUniqueNetIdRepl GetUserId(ESocialSubsystem SubsystemType) const;`
- L65 _public prototype_ `FString GetDisplayName() const;`
- L66 _public prototype_ `FString GetDisplayName(ESocialSubsystem SubsystemType) const;`
- L67 _public prototype_ `virtual FString GetNickname() const;`
- L68 _public prototype_ `virtual bool SetNickname(const FString& InNickName);`
- L70 _public prototype_ `EInviteStatus::Type GetFriendInviteStatus(ESocialSubsystem SubsystemType) const;`
- L71 _public prototype_ `bool IsFriend() const;`
- L72 _public prototype_ `bool IsFriend(ESocialSubsystem SubsystemType) const;`
- L73 _public prototype_ `bool IsFriendshipPending(ESocialSubsystem SubsystemType) const;`
- L74 _public prototype_ `bool IsAnyInboundFriendshipPending() const;`
- L75 _public prototype_ `const FOnlineUserPresence* GetFriendPresenceInfo(ESocialSubsystem SubsystemType) const;`
- L76 _public prototype_ `UE::Online::TOnlineResult<UE::Online::FGetCachedPresence> GetFriendPresenceInfoV2(ESocialSubsystem SubsystemType) const;`
- L77 _public prototype_ `FDateTime GetFriendshipCreationDate() const;`
- L78 _public prototype_ `virtual FDateTime GetLastOnlineDate() const;`
- L79 _public prototype_ `FText GetSocialName() const;`
- L80 _public prototype_ `virtual FUserPlatform GetCurrentPlatform() const;`
- L82 _public prototype_ `FString GetPlatformIconMarkupTag(EPlatformIconDisplayRule DisplayRule) const;`
- L83 _public prototype_ `virtual FString GetPlatformIconMarkupTag(EPlatformIconDisplayRule DisplayRule, FString& OutLegacyString) const;`
- L84 _public function_ `virtual FString GetMarkupTagForPlatform(const FUserPlatform& RemoteUserPlatform) const`
- L86 _public prototype_ `virtual void GetRichPresenceText(FText& OutRichPresence) const;`
- L88 _public prototype_ `bool IsRecentPlayer() const;`
- L89 _public prototype_ `bool IsRecentPlayer(ESocialSubsystem SubsystemType) const;`
- L91 _public prototype_ `bool IsBlocked() const;`
- L92 _public prototype_ `bool IsBlocked(ESocialSubsystem SubsystemType) const;`
- L94 _public prototype_ `bool IsOnline() const;`
- L95 _public prototype_ `bool IsPlayingThisGame() const;`
- L97 _public function_ `virtual bool CanReceiveOfflineInvite() const`
- L98 _public function_ `virtual int64 GetInteractionScore() const`
- L99 _public function_ `virtual int64 GetCustomSortValuePrimary() const`
- L100 _public function_ `virtual int64 GetCustomSortValueSecondary() const`
- L101 _public function_ `virtual int64 GetCustomSortValueTertiary() const`
- L104 _public prototype_ `virtual void PopulateSortParameterList(TArray<int64>& OutSortParams) const;` — Populate list with sort values in order of priority
- L106 _public prototype_ `bool SetUserLocalAttribute(ESocialSubsystem SubsystemType, const FString& AttrName, const FString& AttrValue);`
- L107 _public prototype_ `bool GetUserAttribute(ESocialSubsystem SubsystemType, const FString& AttrName, FString& OutAttrValue) const;`
- L109 _public prototype_ `virtual bool HasAnyInteractionsAvailable() const;`
- L110 _public prototype_ `virtual TArray<FSocialInteractionHandle> GetAllAvailableInteractions() const;`
- L112 _public prototype_ `virtual bool CanSendFriendInvite(ESocialSubsystem SubsystemType) const;`
- L113 _public prototype_ `virtual bool SendFriendInvite(ESocialSubsystem SubsystemType);`
- L114 _public prototype_ `virtual bool AcceptFriendInvite(ESocialSubsystem SocialSubsystem) const;`
- L115 _public prototype_ `virtual bool RejectFriendInvite(ESocialSubsystem SocialSubsystem) const;`
- L116 _public prototype_ `virtual bool EndFriendship(ESocialSubsystem SocialSubsystem) const;`
- L118 _public function_ `TMap<FString, FString> GetAnalyticsContext() const`
- L119 _public prototype_ `void WithContext(const TMap<FString, FString>& InAnalyticsContext, void(*Func)(USocialUser&));`
- L121 _public prototype_ `bool ShowPlatformProfile();`
- L123 _public prototype_ `void HandlePartyInviteReceived(const IOnlinePartyJoinInfo& Invite);`
- L124 _public prototype_ `void HandlePartyInviteRemoved(const IOnlinePartyJoinInfo& Invite, EPartyInvitationRemovedReason Reason);`
- L126 _public function_ `virtual bool CanRequestToJoin() const`
- L127 _public function_ `virtual bool HasRequestedToJoinUs() const`
- L128 _public prototype_ `void HandleRequestToJoinReceived(const IOnlinePartyRequestToJoinInfo& Request);`
- L129 _public prototype_ `void HandleRequestToJoinRemoved(const IOnlinePartyRequestToJoinInfo& Request, EPartyRequestToJoinRemovedReason Reason);`
- L131 _public prototype_ `virtual void RequestToJoinParty(const FName& JoinMethod);`
- L132 _public prototype_ `void AcceptRequestToJoinParty() const;`
- L133 _public prototype_ `void DismissRequestToJoinParty() const;`
- L135 _public prototype_ `virtual void HandlePartyRequestToJoinSent(const FUniqueNetId& LocalUserId, const FUniqueNetId& PartyLeaderId, const FDateTime& ExpiresAt, const ERequestToJoinPartyCompletionResult Result, FName JoinMethod, FString Metadata);`
- L138 _public prototype_ `virtual void HandlePartyRequestToJoinSent(const FUniqueNetId& LocalUserId, const FUniqueNetId& PartyLeaderId, const FDateTime& ExpiresAt, const ERequestToJoinPartyCompletionResult Result, FName JoinMethod);` — `UE_DEPRECATED(5.6, "Use the overload above that also receives metadata")`
- L140 _public prototype_ `virtual IOnlinePartyJoinInfoConstPtr GetPartyJoinInfo(const FOnlinePartyTypeId& PartyTypeId) const;`
- L142 _public prototype_ `bool HasSentPartyInvite(const FOnlinePartyTypeId& PartyTypeId) const;`
- L143 _public prototype_ `FJoinPartyResult CheckPartyJoinability(const FOnlinePartyTypeId& PartyTypeId, bool bCheckPlatformSession = true) const;`
- L145 _public prototype_ `virtual void JoinParty(const FOnlinePartyTypeId& PartyTypeId, const FName& JoinMethod) const;`
- L146 _public prototype_ `virtual void RejectPartyInvite(const FOnlinePartyTypeId& PartyTypeId);`
- L148 _public prototype_ `virtual bool HasBeenInvitedToParty(const FOnlinePartyTypeId& PartyTypeId) const;`
- L149 _public prototype_ `bool CanInviteToParty(const FOnlinePartyTypeId& PartyTypeId) const;`
- L150 _public prototype_ `virtual bool InviteToParty(const FOnlinePartyTypeId& PartyTypeId, const ESocialPartyInviteMethod InviteMethod = ESocialPartyInviteMethod::Other, const FString& MetaData = FString()) const;`
- L152 _public prototype_ `virtual bool BlockUser(ESocialSubsystem Subsystem) const;`
- L153 _public prototype_ `virtual bool UnblockUser(ESocialSubsystem Subsystem) const;`
- L155 _public prototype_ `UPartyMember* GetPartyMember(const FOnlinePartyTypeId& PartyTypeId) const;`
- L157 _public prototype_ `DECLARE_EVENT_OneParam(USocialUser, FOnNicknameChanged, const FText&);`
- L158 _public function_ `FOnNicknameChanged& OnSetNicknameCompleted() const`
- L160 _public prototype_ `DECLARE_EVENT(USocialUser, FPartyInviteResponseEvent);`
- L161 _public function_ `FPartyInviteResponseEvent& OnPartyInviteAccepted() const`
- L162 _public function_ `FPartyInviteResponseEvent& OnPartyInviteRejected() const`
- L164 _public function_ `DECLARE_EVENT_OneParam(USocialUser, FOnUserPresenceChanged, ESocialSubsystem) FOnUserPresenceChanged& OnUserPresenceChanged() const`
- L169 _public function_ `DECLARE_EVENT(USocialUser, FOnUserGameSpecificStatusChanged) FOnUserGameSpecificStatusChanged& OnUserGameSpecificStatusChanged() const` — provided so that lists with custom game-specific filtering (and any other listeners) can potentially re-evaluate a user the pattern here is similar to OnUserPresenceChanged but not subsystem-specific
- L172 _public function_ `DECLARE_EVENT_OneParam(USocialUser, FOnFriendRemoved, ESocialSubsystem) FOnFriendRemoved& OnFriendRemoved() const`
- L174 _public function_ `FOnFriendRemoved& OnFriendInviteRemoved() const`
- L176 _public function_ `DECLARE_EVENT_TwoParams(USocialUser, FOnBlockedStatusChanged, ESocialSubsystem, bool) FOnBlockedStatusChanged& OnBlockedStatusChanged() const`
- L179 _public function_ `DECLARE_EVENT_ThreeParams(USocialUser, FOnSubsystemIdEstablished, USocialUser&, ESocialSubsystem, const FUniqueNetIdRepl&) FOnSubsystemIdEstablished& OnSubsystemIdEstablished() const`
- L184 _public prototype_ `FString ToDebugString() const;`
- L186 _public prototype_ `void EstablishOssInfo(const TSharedRef<FOnlineFriend>& FriendInfo, ESocialSubsystem SubsystemType);`
- L187 _public prototype_ `void EstablishOssInfo(const TSharedRef<FOnlineBlockedPlayer>& BlockedPlayerInfo, ESocialSubsystem SubsystemType);`
- L188 _public prototype_ `void EstablishOssInfo(const TSharedRef<FOnlineRecentPlayer>& RecentPlayerInfo, ESocialSubsystem SubsystemType);`
- L191 _protected prototype_ `void InitLocalUser();`
- L192 _protected prototype_ `void Initialize(const FUniqueNetIdRepl& PrimaryId);`
- L194 _protected prototype_ `void NotifyPresenceChanged(ESocialSubsystem SubsystemType);`
- L195 _protected prototype_ `void NotifyUserUnblocked(ESocialSubsystem SubsystemType);`
- L196 _protected prototype_ `void NotifyFriendInviteRemoved(ESocialSubsystem SubsystemType);`
- L197 _protected prototype_ `void NotifyUserUnfriended(ESocialSubsystem SubsystemType);`
- L200 _protected prototype_ `void Debug_RandomizePresence();`
- L201 _protected member_ `bool bDebug_IsPresenceArtificial = false;`
- L202 _protected member_ `EOnlinePresenceState::Type Debug_RandomPresence;`
- L203 _protected member_ `UE::Online::EUserPresenceStatus Debug_RandomPresenceV2;`
- L207 _protected prototype_ `virtual void OnPresenceChangedInternalV2(ESocialSubsystem SubsystemType);`
- L208 _protected prototype_ `virtual void OnPresenceChangedInternal(ESocialSubsystem SubsystemType);`
- L209 _protected prototype_ `virtual void OnPartyInviteAcceptedInternal(const FOnlinePartyTypeId& PartyTypeId, const IOnlinePartyJoinInfo& Invite) const;`
- L210 _protected prototype_ `virtual void OnPartyInviteRejectedInternal(const FOnlinePartyTypeId& PartyTypeId) const;`
- L211 _protected prototype_ `virtual void HandleSetNicknameComplete(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnlineError& Error);`
- L212 _protected prototype_ `virtual void SetSubsystemId(ESocialSubsystem SubsystemType, const FUniqueNetIdRepl& SubsystemId);`
- L215 _protected function_ `virtual void OnPartyInviteAcceptedInternal(const FOnlinePartyTypeId& PartyTypeId) const` — `UE_DEPRECATED(5.6, "Override 'void OnPartyInviteAcceptedInternal(const FOnlinePartyTypeId& PartyTypeId, const FString& InviteMetadata) const' instead")`
- L217 _protected prototype_ `virtual FString GetRequestToJoinMetadata(const FString& ExistingMetadata);`
- L218 _protected function_ `virtual void NotifyRequestToJoinReceived(const IOnlinePartyRequestToJoinInfo& Request)`
- L219 _protected function_ `virtual void NotifyRequestToJoinRemoved(const IOnlinePartyRequestToJoinInfo& Request, EPartyRequestToJoinRemovedReason Reason)`
- L220 _protected member_ `int32 NumPendingQueries = 0;`
- L221 _protected member_ `TMap<FString, FString> AnalyticsContext;`
- L223 _protected prototype_ `IOnlinePartyJoinInfoConstPtr GetSentPartyInvite(const FOnlinePartyTypeId& PartyTypeId) const;`
- L224 _protected prototype_ `void TryBroadcastInitializationComplete();`
- L249 _protected function_ `const FSubsystemUserInfo* GetSubsystemUserInfo(ESocialSubsystem Subsystem) const`
- L251 _protected prototype_ `void SetUserInfo(ESocialSubsystem SubsystemType, const TSharedRef<FOnlineUser>& UserInfo);`
- L254 _protected prototype_ `virtual TFuture<void> SetupCommonAccount();` — This method should be extended in derived classes to asynchronously set up the correct CommonAccount state for the given social user.
- L256 _protected prototype_ `virtual bool ShouldSpecifyDisplayNameServicesProvider(const FSubsystemUserInfo* SubsystemInfo) const;` — This method should be extended in derived classes to make any additional subsystem user info checks needed that might modify the services provider used in GetDisplayName
- L257 _protected prototype_ `virtual UE::Online::EOnlinePlatformType GetDisplayNameOnlinePlatformTypeFromUserPlatform(const FString& UserCurrentPlatformStr) const;`
- L259 _protected prototype_ `bool ShouldReadUserInfoFromOnlineServices() const;`
- L262 _private prototype_ `void HandleQueryUserInfoComplete(ESocialSubsystem SubsystemType, bool bWasSuccessful, const TSharedPtr<FOnlineUser>& UserInfo);`
- L263 _private prototype_ `void HandleQueryUserInfoV2Complete(ESocialSubsystem SubsystemType, bool bWasSuccessful, const TValueOrError<TSharedRef<UE::Online::FUserInfo>, UE::Online::FOnlineError>& Result);`
- L265 _private prototype_ `virtual FString SanitizePresenceString(FString InString) const;`
- L269 _private prototype_ `FSubsystemUserInfo& FindOrCreateSubsystemInfo(const FUniqueNetIdRepl& SubsystemId, ESocialSubsystem SubsystemType);`
- L271 _private member_ `bool bIsInitialized = false;`
- L272 _private prototype_ `void FinishInitialization();`
- L274 _private prototype_ `void OnJoinPartyComplete(const FJoinPartyResult& JoinPartyResult, FOnlinePartyTypeId PartyTypeId, IOnlinePartyJoinInfoConstPtr SentInvite) const;`
- L280 _private member_ `TUniquePtr<FDebugInitializer> DebugInitializer;`
- L283 _private member_ `TMap<ESocialSubsystem, FSubsystemUserInfo> SubsystemInfoByType;`
- L285 _private member_ `TArray<IOnlinePartyJoinInfoConstRef> ReceivedPartyInvites;`
- L287 _private member_ `FDelegateHandle OnReadUserInfoV2CVarChanged;`
- L290 _private member_ `TArray<FOnNewSocialUserInitialized> UserInitializedEvents;` — Initialization delegates that fire only when a specific user has finishing initializing
- L292 _private member_ `mutable FOnNicknameChanged OnSetNicknameCompletedEvent;`
- L293 _private member_ `mutable FPartyInviteResponseEvent OnPartyInviteAcceptedEvent;`
- L294 _private member_ `mutable FPartyInviteResponseEvent OnPartyInviteRejectedEvent;`
- L295 _private member_ `mutable FOnUserPresenceChanged OnUserPresenceChangedEvent;`
- L296 _private member_ `mutable FOnFriendRemoved OnFriendRemovedEvent;`
- L297 _private member_ `mutable FOnFriendRemoved OnFriendInviteRemovedEvent;`
- L298 _private member_ `mutable FOnBlockedStatusChanged OnBlockedStatusChangedEvent;`
- L299 _private member_ `mutable FOnSubsystemIdEstablished OnSubsystemIdEstablishedEvent;`
- L300 _private member_ `mutable FOnUserGameSpecificStatusChanged OnUserGameSpecificStatusChangedEvent;`

#### struct `USocialUser::FSubsystemUserInfo`  
`struct FSubsystemUserInfo`  
_L226-248_
- L228 _public function_ `FSubsystemUserInfo(const FUniqueNetIdRepl& InUserId) : UserId(InUserId)`
- L232 _public prototype_ `bool IsValid() const;`
- L233 _public function_ `const FUniqueNetIdRepl& GetUserId() const`
- L234 _public function_ `FString GetDisplayName() const`
- L235 _public function_ `bool IsFriend() const`
- L236 _public function_ `bool IsBlocked() const`
- L237 _public function_ `EInviteStatus::Type GetFriendInviteStatus() const`
- L238 _public function_ `bool HasValidPresenceInfo() const`
- L239 _public prototype_ `const FOnlineUserPresence* GetPresenceInfo() const;`
- L242 _public member_ `FUniqueNetIdRepl UserId;` — On the fence about caching this locally. We don't care about where it came from if we do, and we can cache it independent from any of the info structs (which will play nice with external mapping queries before querying the user info itself)
- L244 _public member_ `TWeakPtr<FOnlineUser> UserInfo;`
- L245 _public member_ `TWeakPtr<FOnlineFriend> FriendInfo;`
- L246 _public member_ `TWeakPtr<FOnlineRecentPlayer> RecentPlayerInfo;`
- L247 _public member_ `TWeakPtr<FOnlineBlockedPlayer> BlockedPlayerInfo;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API PARTY_API`
- L31 _typedef_ `typedef TSharedRef<const IOnlinePartyJoinInfo> IOnlinePartyJoinInfoConstRef;`
- L32 _typedef_ `typedef TSharedPtr<const IOnlinePartyJoinInfo> IOnlinePartyJoinInfoConstPtr;`
- L34 _namespace_ `namespace EOnlinePresenceState`
- L36 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNewSocialUserInitialized, USocialUser&);`
- L36 _prototype_ `DECLARE_DELEGATE_OneParam(FOnNewSocialUserInitialized, USocialUser&);`
- L157 _delegate_ `DECLARE_EVENT_OneParam(USocialUser, FOnNicknameChanged, const FText&);`
- L160 _delegate_ `DECLARE_EVENT(USocialUser, FPartyInviteResponseEvent);`
- L164 _delegate_ `DECLARE_EVENT_OneParam(USocialUser, FOnUserPresenceChanged, ESocialSubsystem) FOnUserPresenceChanged& OnUserPresenceChanged() const { return OnUserPresenceChangedEvent; }`
- L169 _delegate_ `DECLARE_EVENT(USocialUser, FOnUserGameSpecificStatusChanged) FOnUserGameSpecificStatusChanged& OnUserGameSpecificStatusChanged() const { return OnUserGameSpecificStatusChangedEvent; } DECLARE_EVENT_OneParam(USocialUser, FOnFriendRemoved, ESocialSubsystem) FOnFriendRemoved& OnFriendRemoved() const { return OnFriendRemovedEvent; } FOnFriendRemoved& OnFriendInviteRemoved() const { return OnFriendInviteRemovedEvent; } DECLARE_EVENT_TwoParams(USocialUser, FOnBlockedStatusChanged, ESocialSubsystem, bool) FOnBlockedStatusChanged& OnBlockedStatusChanged() const { return OnBlockedStatusChangedEvent; } DECLARE_EVENT_ThreeParams(USocialUser, FOnSubsystemIdEstablished, USocialUser&, ESocialSubsystem, const FUniqueNetIdRepl&) FOnSubsystemIdEstablished& OnSubsystemIdEstablished() const { return OnSubsystemIdEstablishedEvent; }` — provided so that lists with custom game-specific filtering (and any other listeners) can potentially re-evaluate a user the pattern here is similar to OnUserPresenceChanged but not subsystem-specific
- L172 _delegate_ `DECLARE_EVENT_OneParam(USocialUser, FOnFriendRemoved, ESocialSubsystem) FOnFriendRemoved& OnFriendRemoved() const { return OnFriendRemovedEvent; } FOnFriendRemoved& OnFriendInviteRemoved() const { return OnFriendInviteRemovedEvent; } DECLARE_EVENT_TwoParams(USocialUser, FOnBlockedStatusChanged, ESocialSubsystem, bool) FOnBlockedStatusChanged& OnBlockedStatusChanged() const { return OnBlockedStatusChangedEvent; } DECLARE_EVENT_ThreeParams(USocialUser, FOnSubsystemIdEstablished, USocialUser&, ESocialSubsystem, const FUniqueNetIdRepl&) FOnSubsystemIdEstablished& OnSubsystemIdEstablished() const { return OnSubsystemIdEstablishedEvent; }`
- L176 _delegate_ `DECLARE_EVENT_TwoParams(USocialUser, FOnBlockedStatusChanged, ESocialSubsystem, bool) FOnBlockedStatusChanged& OnBlockedStatusChanged() const { return OnBlockedStatusChangedEvent; } DECLARE_EVENT_ThreeParams(USocialUser, FOnSubsystemIdEstablished, USocialUser&, ESocialSubsystem, const FUniqueNetIdRepl&) FOnSubsystemIdEstablished& OnSubsystemIdEstablished() const { return OnSubsystemIdEstablishedEvent; }`
- L179 _delegate_ `DECLARE_EVENT_ThreeParams(USocialUser, FOnSubsystemIdEstablished, USocialUser&, ESocialSubsystem, const FUniqueNetIdRepl&) FOnSubsystemIdEstablished& OnSubsystemIdEstablished() const { return OnSubsystemIdEstablishedEvent; }`
