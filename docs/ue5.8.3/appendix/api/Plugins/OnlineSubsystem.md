# Plugins / OnlineSubsystem

- module root: `Plugins/Online/OnlineSubsystem/Source`
- headers: 66; symbols: 3848
- symbol kinds: class=126, delegate=245, enum=69, enumerator=412, externvar=36, function=488, macro=172, member=512, namespace=36, prototype=1413, struct=87, typedef=251, union=1
- PrivateDependencyModuleNames: Core, CoreUObject, JsonUtilities
- PublicDependencyModuleNames: CoreOnline, Json, OnlineBase, SignalProcessing
- PublicIncludePathModuleNames: CoreOnline

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/IMessageSanitizerInterface.h` (Public)


#### struct `FBlockedQueryResult`  
`struct FBlockedQueryResult`  
_L7-21_
- L9 _public function_ `FBlockedQueryResult(bool InIsBlocked=false, bool InIsBlockedNonFriends=false, const FString& InUserId = FString()) : bIsBlocked(InIsBlocked) , bIsBlockedNonFriends(InIsBlockedNonFriends) , UserId(InUserId)`
- L16 _public member_ `bool bIsBlocked;` — Is this user blocked
- L18 _public member_ `bool bIsBlockedNonFriends;` — Is this user blocked for non-friends
- L20 _public member_ `FString UserId;` — Platform specific unique id

#### class `IMessageSanitizer`  
`class IMessageSanitizer : public TSharedFromThis<IMessageSanitizer, ESPMode::ThreadSafe>`  
_L27-51_
- inherits: `TSharedFromThis<IMessageSanitizer,ESPMode::ThreadSafe>`
- L30 _protected function_ `IMessageSanitizer()`
- L33 _public prototype_ `virtual ~IMessageSanitizer() = default;`
- L34 _public prototype_ `virtual void SanitizeDisplayName(const FString& DisplayName, const FOnMessageProcessed& CompletionDelegate) = 0;`
- L35 _public prototype_ `virtual void SanitizeDisplayNames(const TArray<FString>& DisplayNames, const FOnMessageArrayProcessed& CompletionDelegate) = 0;`
- L45 _public prototype_ `virtual void QueryBlockedUser(int32 LocalUserNum, const FString& FromUserId, const FString& FromPlatform, const FOnQueryUserBlockedResponse& CompletionDelegate) = 0;` — Query for a blocked user status between a local and remote user @param LocalUserNum local user making the query @param FromUserId platform specific user id of the remote user @param FromPlatform platform for remote user @param CompletionDelegate delegate to fire on completion
- L48 _public prototype_ `virtual void ResetBlockedUserCache() = 0;` — Invalidate all previously queried blocked users state
- L50 _public member_ `const FString MessageArraySeparator = TEXT("\u2`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMessageProcessed, bool , const FString& );`
- L23 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnMessageProcessed, bool , const FString& );`
- L24 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMessageArrayProcessed, bool , const TArray<FString>& );`
- L24 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnMessageArrayProcessed, bool , const TArray<FString>& );`
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQueryUserBlockedResponse, const FBlockedQueryResult& );`
- L25 _prototype_ `DECLARE_DELEGATE_OneParam(FOnQueryUserBlockedResponse, const FBlockedQueryResult& );`
- L53 _typedef_ `typedef TSharedPtr<IMessageSanitizer, ESPMode::ThreadSafe> IMessageSanitizerPtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/IVoiceChatRoom.h` (Public)


#### struct `FVoiceChatRoomEntered`  
`struct FVoiceChatRoomEntered`  
_L17-29_
- desc: Payload for a room entered callback
- L21 _public function_ `FVoiceChatRoomEntered(VoiceChatRoomId InRoomId) : RoomId(InRoomId)`
- L24 _public prototype_ `FVoiceChatRoomEntered() = delete;`
- L25 _public prototype_ `~FVoiceChatRoomEntered() = default;`
- L28 _public member_ `VoiceChatRoomId RoomId;` — Room entered

#### struct `FVoiceChatRoomExited`  
`struct FVoiceChatRoomExited`  
_L34-46_
- desc: Payload for a room exited callback
- L38 _public function_ `FVoiceChatRoomExited(VoiceChatRoomId InRoomId) : RoomId(InRoomId)`
- L41 _public prototype_ `FVoiceChatRoomExited() = delete;`
- L42 _public prototype_ `~FVoiceChatRoomExited() = default;`
- L45 _public member_ `VoiceChatRoomId RoomId;` — Room exited

#### enum `EVoiceChatRoomState`  
`enum class EVoiceChatRoomState : uint8`  
_L52-62_
- L55 _public enumerator_ `Invalid` — Default, invalid room state
- L57 _public enumerator_ `Entering` — Entering chat room
- L59 _public enumerator_ `Entered` — Room successfully entered
- L61 _public enumerator_ `Leaving` — Exiting chat room, will be removed shortly

#### class `FVoiceChatRoomMember`  
`class FVoiceChatRoomMember`  
_L88-98_
- desc: Representation of a user inside of a voice chat room
- L93 _public prototype_ `FVoiceChatRoomMember() = default;`
- L94 _public prototype_ `virtual ~FVoiceChatRoomMember() = default;`
- L97 _public prototype_ `virtual FString ToDebugString() const = 0;` — @return debug information about this chat room suitable for output

#### class `FVoiceChatRoomInfo`  
`class FVoiceChatRoomInfo`  
_L103-118_
- desc: Basic information about a voice chat room in various possible states
- L107 _public prototype_ `FVoiceChatRoomInfo() = default;`
- L108 _public prototype_ `virtual ~FVoiceChatRoomInfo() = default;`
- L111 _public prototype_ `virtual VoiceChatRoomId GetRoomId() const = 0;` — @return the room id for this chat room
- L113 _public prototype_ `virtual EVoiceChatRoomState GetState() const = 0;` — @return the state this chat room is in
- L115 _public prototype_ `virtual void GetMembers(TArray<TSharedRef<FVoiceChatRoomMember>>& OutMembers) const = 0;` — @return all currently known members of this chat room
- L117 _public prototype_ `virtual FString ToDebugString() const = 0;` — @return debug information about this chat room suitable for output

#### class `IVoiceChatRoom`  
`class IVoiceChatRoom : public IModularFeature`  
_L120-173_
- inherits: `IModularFeature`
- L124 _public prototype_ `IVoiceChatRoom() = default;`
- L125 _public prototype_ `virtual ~IVoiceChatRoom() = default;`
- L127 _public function_ `static FName GetModularFeatureName()`
- L139 _public prototype_ `virtual void EnterRoom(VoiceChatRoomId InRoomId, const FOnVoiceChatRoomEntered& OnChatRoomEntered) = 0;` — Enter a voice chat room @param InRoomId 64 bit room id to enter @param OnChatRoomEntered delegate to fire when request is complete
- L146 _public prototype_ `virtual void SwitchRoom(VoiceChatRoomId InRoomId, const FOnVoiceChatRoomEntered& OnChatRoomEntered) = 0;` — Switch between voice chat rooms @param InRoomId 64 bit room id to switch to, leaving previous room @param OnChatRoomEntered delegate to fire when request is complete
- L153 _public prototype_ `virtual void ExitRoom(VoiceChatRoomId InRoomId, const FOnVoiceChatRoomExited& OnChatRoomExited) = 0;` — Exit a voice chat room @param InRoomId 64 bit room id to exit @param OnChatRoomExited delegate to fire when request is complete
- L160 _public prototype_ `virtual void ShowUI(bool bShow, const FOnShowVoiceChatUI& OnShowChatUI) = 0;` — Show or hide the UI related to the voice chat system @param bShow true to show, false to hide the UI @param OnShowChatUI delegate to fire when request is complete
- L166 _public prototype_ `virtual void GetRooms(TArray<TSharedRef<FVoiceChatRoomInfo>>& OutRooms) const = 0;` — Get all known voice chat rooms @param OutRooms array to fill with known chat rooms
- L172 _public prototype_ `virtual void SetDisplayName(const FString& InDisplayName) = 0;` — Set a display name for the chat room, if applicable @param InDisplayName desired display name for chat room UI

#### Free symbols / members of external scopes

- L10 _typedef_ `typedef uint64 VoiceChatRoomId;`
- L12 _macro_ `#define INVALID_VOICE_CHATROOM -1`
- L48 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnVoiceChatRoomEntered, const FVoiceChatRoomEntered& , const FOnlineError& );`
- L48 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnVoiceChatRoomEntered, const FVoiceChatRoomEntered& , const FOnlineError& );`
- L49 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnVoiceChatRoomExited, const FVoiceChatRoomExited& , const FOnlineError& );`
- L49 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnVoiceChatRoomExited, const FVoiceChatRoomExited& , const FOnlineError& );`
- L50 _delegate_ `DECLARE_DELEGATE_OneParam(FOnShowVoiceChatUI, const FOnlineError& );`
- L50 _prototype_ `DECLARE_DELEGATE_OneParam(FOnShowVoiceChatUI, const FOnlineError& );`
- L64 _function_ `inline const TCHAR* LexToString(EVoiceChatRoomState InState)`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineAchievementsInterface.h` (Public)


#### struct `FOnlineAchievement`  
`struct FOnlineAchievement`  
_L42-58_
- desc: FOnlineAchievement - Interface class for accessing the common achievement information
- L45 _public member_ `FString Id;` — The id of the achievement
- L48 _public member_ `double Progress;` — The progress towards completing this achievement: 0.0-100.0
- L51 _public function_ `FString ToDebugString() const` — Returns debugging string to print out achievement info

#### struct `FOnlineAchievementDesc`  
`struct FOnlineAchievementDesc`  
_L64-92_
- desc: FOnlineAchievementDesc - Interface class for accessing the common achievement description information
- L67 _public member_ `FText Title;` — The localized title of the achievement
- L70 _public member_ `FText LockedDesc;` — The localized locked description of the achievement
- L73 _public member_ `FText UnlockedDesc;` — The localized unlocked description of the achievement
- L76 _public member_ `bool bIsHidden;` — Flag for whether the achievement is hidden
- L79 _public member_ `FDateTime UnlockTime;` — The date/time the achievement was unlocked
- L82 _public function_ `FString ToDebugString() const` — Returns debugging string to print out achievement info

#### class `IOnlineAchievements`  
`class IOnlineAchievements`  
_L98-182_
- desc: IOnlineAchievements - Interface class for achievements
- L101 _public prototype_ `virtual ~IOnlineAchievements() = default;`
- L110 _public prototype_ `virtual void WriteAchievements(const FUniqueNetId& PlayerId, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& Delegate = FOnAchievementsWrittenDelegate()) = 0;` — Write the achievements provided to the server @param PlayerId - The uid of the player we are writing achievements for @param WriteObject - The stats holder containing the achievements we are writing. @param Delegate - The delegate to call when the write has completed or failed.
- L123 _public prototype_ `virtual void QueryAchievements(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate()) = 0;` — Read achievement ids and progress from the server You must use QueryAchievementDescriptions to get more information about the achievements @see FOnlineAchievement @see QueryAchievementDescriptions @param PlayerId the id of the player we are reading achievements for @param Delegate the delegate to trigger when the query is complete @return Whether we have kicked off a read attempt
- L134 _public prototype_ `virtual void QueryAchievementDescriptions( const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate() ) = 0;` — Read achievement descriptions from the server for displaying achievements in game @see FOnlineAchievementDesc @param PlayerId the id of the player we are reading achievements for @param Delegate the delegate to trigger when the query is complete @return Whether we have kicked off a read attempt
- L145 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievement( const FUniqueNetId& PlayerId, const FString& AchievementId, FOnlineAchievement& OutAchievement) = 0;` — Get an achievement object which was previously synced from the server @param PlayerId - The uid of the player we are reading achievements for @param AchievementId - The id of the achievement we are looking up @param OutAchievement - The achievement object we are searching for @return Whether achievements were obtained
- L155 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievements(const FUniqueNetId& PlayerId, TArray<FOnlineAchievement>& OutAchievements) = 0;` — Get all the achievement objects for the specified player @param PlayerId - The uid of the player we are reading achievements for @param OutAchievements - The collection of achievements obtained from the server for the given player @return Whether achievements were obtained
- L165 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievementDescription(const FString& AchievementId, FOnlineAchievementDesc& OutAchievementDesc) = 0;` — Get all the achievement description object for the specified achievement id @param AchievementId - The id of the achievement we are searching for data of @param OutAchievementDesc - The description object for the achievement id we seek @return Whether achievements were obtained
- L175 _public prototype_ `virtual bool ResetAchievements( const FUniqueNetId& PlayerId ) = 0;` — Resets achievements for a given player @param PlayerId - The uid of the player @return Whether we kicked off the clear request
- L181 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnAchievementUnlocked, const FUniqueNetId&, const FString&);` — Delegate fired when an achievement on the server was unlocked

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineAchievements, Log, All);`
- L10 _macro_ `#define UE_LOG_ONLINE_ACHIEVEMENTS(Verbosity, Format, ...) \`
- L15 _macro_ `#define UE_CLOG_ONLINE_ACHIEVEMENTS(Conditional, Verbosity, Format, ...) \`
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAchievementsWritten, const FUniqueNetId&, bool );` — Delegate fired when achievements have been written to the server
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAchievementsWritten, const FUniqueNetId&, bool );` — Delegate fired when achievements have been written to the server
- L24 _typedef_ `typedef FOnAchievementsWritten::FDelegate FOnAchievementsWrittenDelegate;`
- L30 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAchievementUnlocked, const FUniqueNetId&, const FString& );` — Delegate fired when an achievement has been unlocked
- L30 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAchievementUnlocked, const FUniqueNetId&, const FString& );` — Delegate fired when an achievement has been unlocked
- L31 _typedef_ `typedef FOnAchievementUnlocked::FDelegate FOnAchievementUnlockedDelegate;`
- L37 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnQueryAchievementsCompleteDelegate, const FUniqueNetId&, const bool);` — Delegate fired when an achievement has been queried
- L37 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnQueryAchievementsCompleteDelegate, const FUniqueNetId&, const bool);` — Delegate fired when an achievement has been queried

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineChatInterface.h` (Public)


#### class `FChatRoomInfo`  
`class FChatRoomInfo`  
_L31-44_
- desc: Info for a joined/created chat room
- L34 _public prototype_ `virtual ~FChatRoomInfo() = default;`
- L36 _public prototype_ `virtual const FChatRoomId& GetRoomId() const = 0;`
- L37 _public prototype_ `virtual const FUniqueNetIdRef& GetOwnerId() const = 0;`
- L38 _public prototype_ `virtual const FString& GetSubject() const = 0;`
- L39 _public prototype_ `virtual bool IsPrivate() const = 0;`
- L40 _public prototype_ `virtual bool IsJoined() const = 0;`
- L41 _public prototype_ `virtual const class FChatRoomConfig& GetRoomConfig() const = 0;`
- L42 _public prototype_ `virtual FString ToDebugString() const = 0;`
- L43 _public prototype_ `virtual void SetChatInfo(const TSharedRef<class FJsonObject>& JsonInfo) = 0;`

#### class `FChatRoomConfig`  
`class FChatRoomConfig`  
_L49-85_
- desc: Configuration for creating/joining a chat room
- L52 _public function_ `FChatRoomConfig() : bRejoinOnDisconnect(false) , bPasswordRequired(false) , bAnnounceMembers(true)`
- L59 _public member_ `bool bRejoinOnDisconnect;` — Should this room be rejoined on disconnection
- L61 _public member_ `bool bPasswordRequired;` — Is there a password required to join the room (owner only)
- L63 _public member_ `FString Password;` — Password to join the room (owner only)
- L68 _public member_ `bool bAnnounceMembers;` — Should we announce members joining and leaving? This may incur a performance cost if members need to be validated.
- L70 _public function_ `FString ToDebugString() const`
- L77 _private member_ `bool bMembersOnly;` — Below are unused, move to public when hooking up to functionality
- L78 _private member_ `bool bHidden;`
- L79 _private member_ `bool bPersistent;`
- L80 _private member_ `bool bAllowMemberInvites;`
- L81 _private member_ `bool bLoggingEnabled;`
- L82 _private member_ `int32 MessageHistory;`
- L83 _private member_ `int32 MaxMembers;`
- L84 _private member_ `FString PubSubNode;`

#### class `FChatRoomMember`  
`class FChatRoomMember`  
_L90-97_
- desc: Member of a chat room
- L93 _public prototype_ `virtual ~FChatRoomMember() = default;`
- L95 _public prototype_ `virtual const FUniqueNetIdRef& GetUserId() const = 0;`
- L96 _public prototype_ `virtual const FString& GetNickname() const = 0;`

#### class `FChatMessage`  
`class FChatMessage`  
_L102-115_
- desc: Chat message received from user/room
- L105 _public prototype_ `virtual ~FChatMessage() = default;`
- L108 _public prototype_ `virtual const FUniqueNetIdRef& GetUserId() const = 0;` — @return the user id the message is from
- L110 _public prototype_ `virtual const FString& GetNickname() const = 0;` — @return the nickname of the user the message is from
- L112 _public prototype_ `virtual const FString& GetBody() const = 0;` — @return the body of the message
- L114 _public prototype_ `virtual const FDateTime& GetTimestamp() const = 0;` — @return the timestamp for the message

#### class `IOnlineChat`  
`class IOnlineChat`  
_L246-422_
- desc: Interface class for user-user and user-room chat
- L249 _public prototype_ `virtual ~IOnlineChat() = default;`
- L261 _public prototype_ `virtual bool CreateRoom(const FUniqueNetId& UserId, const FChatRoomId& RoomId, const FString& Nickname, const FChatRoomConfig& ChatRoomConfig) = 0;` — Kick off request for creating a chat room with a provided configuration @param UserId id of user that is creating the room @param RoomId name of room to create @param Nickname display name for the chat room. Name must be unique and is reserved for duration of join @param RoomConfig configuration for the room @return if successfully started the async operation
- L272 _public prototype_ `virtual bool ConfigureRoom(const FUniqueNetId& UserId, const FChatRoomId& RoomId, const FChatRoomConfig& ChatRoomConfig) = 0;` — Kick off request for configuring a chat room with a provided configuration @param UserId id of user that is creating the room @param RoomId name of room to create @param RoomConfig configuration for the room @return if successfully started the async operation
- L284 _public prototype_ `virtual bool JoinPublicRoom(const FUniqueNetId& UserId, const FChatRoomId& RoomId, const FString& Nickname, const FChatRoomConfig& ChatRoomConfig) = 0;` — Kick off request for joining a public chat room @param UserId id of user that is joining @param RoomId name of room to join @param Nickname display name for the chat room. Name must be unique and is reserved for duration of join @param ChatRoomConfig configuration parameters needed to join @return if successfully started the async operation
- L296 _public prototype_ `virtual bool JoinPrivateRoom(const FUniqueNetId& UserId, const FChatRoomId& RoomId, const FString& Nickname, const FChatRoomConfig& ChatRoomConfig) = 0;` — Kick off request for joining a private chat room @param UserId id of user that is joining @param RoomId name of room to join @param Nickname display name for the chat room. Name must be unique and is reserved for duration of join @param ChatRoomConfig configuration parameters needed to join @return if successfully started the async operation
- L306 _public prototype_ `virtual bool ExitRoom(const FUniqueNetId& UserId, const FChatRoomId& RoomId) = 0;` — Kick off request for exiting a previously joined chat room @param UserId id of user that is exiting @param RoomId name of room to exit @return if successfully started the async operation
- L317 _public prototype_ `virtual bool SendRoomChat(const FUniqueNetId& UserId, const FChatRoomId& RoomId, const FString& MsgBody) = 0;` — Kick off request for sending a chat message to a joined chat room @param UserId id of user that is sending the message @param RoomId name of room to send message to @param MsgBody plain text of message body @return if successfully started the async operation
- L328 _public prototype_ `virtual bool SendPrivateChat(const FUniqueNetId& UserId, const FUniqueNetId& RecipientId, const FString& MsgBody) = 0;` — Kick off request for sending a chat message privately between users @param UserId id of user that is sending the message @param RecipientId id of user to send the chat to @param MsgBody plain text of message body @return if successfully started the async operation
- L338 _public prototype_ `virtual bool IsChatAllowed(const FUniqueNetId& UserId, const FUniqueNetId& RecipientId) const = 0;` — Determine if chat is allowed for a given user @param UserId id of user that is sending the message @param RecipientId id of user to send the chat to @return if chat is allowed
- L347 _public prototype_ `virtual void GetJoinedRooms(const FUniqueNetId& UserId, TArray<FChatRoomId>& OutRooms) = 0;` — Get cached list of rooms that have been joined @param UserId id of user to find @param OutRooms [out] list of room ids or empty if not found
- L357 _public prototype_ `virtual TSharedPtr<FChatRoomInfo> GetRoomInfo(const FUniqueNetId& UserId, const FChatRoomId& RoomId) = 0;` — Get cached room info for a room @param UserId id of user to find @param RoomId id of room to find @return RoomInfo information about a chat room or NULL if not found
- L368 _public prototype_ `virtual bool GetMembers(const FUniqueNetId& UserId, const FChatRoomId& RoomId, TArray< TSharedRef<FChatRoomMember> >& OutMembers) = 0;` — Get cached list of members currently joined in a chat room @param UserId id of user to find @param RoomId id of room to find @param OutRoomMembers [out] list of current members in the chat room @return true if found
- L379 _public prototype_ `virtual TSharedPtr<FChatRoomMember> GetMember(const FUniqueNetId& UserId, const FChatRoomId& RoomId, const FUniqueNetId& MemberId) = 0;` — Get cached member currently joined in a chat room @param UserId id of user to find @param RoomId id of room to find @param MemberId id of member to find @return member in room or NULL if not found
- L391 _public prototype_ `virtual bool GetLastMessages(const FUniqueNetId& UserId, const FChatRoomId& RoomId, int32 NumMessages, TArray< TSharedRef<FChatMessage> >& OutMessages) = 0;` — Get cached list of chat messages for a currently joined chat room @param UserId id of user to find @param RoomId id of room to find @param NumMessages max number of messages to fetch from history (-1 for all cached messages) @param OutMessages [out] list of messages from the chat room history @return true if found
- L402 _public prototype_ `virtual bool IsMessageFromLocalUser(const FUniqueNetId& UserId, const FChatMessage& Message, const bool bIncludeExternalInstances) = 0;` — Check if a message is from the local user @param UserId local user id @param Message message to check @param bIncludeExternalInstances relevant when multiple logins on the same account name are possible.  Use false if we want to restrict to the current (this) instance of the game, true if we want to include instances running in other processes @return true if the message is from the local user, false if not
- L407 _public prototype_ `virtual void DumpChatState() const = 0;` — Dump state information about chat rooms
- L410 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnChatRoomCreated, const FUniqueNetId&, const FChatRoomId&, bool, const FString&);` — delegate callbacks (see declarations above)
- L411 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnChatRoomConfigured, const FUniqueNetId&, const FChatRoomId&, bool, const FString&);`
- L412 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnChatRoomJoinPublic, const FUniqueNetId&, const FChatRoomId&, bool, const FString&);`
- L413 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnChatRoomJoinPrivate, const FUniqueNetId&, const FChatRoomId&, bool, const FString&);`
- L414 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnChatRoomExit, const FUniqueNetId&, const FChatRoomId&, bool, const FString&);`
- L415 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnChatRoomMemberJoin, const FUniqueNetId&, const FChatRoomId&, const FUniqueNetId&);`
- L416 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnChatRoomMemberExit, const FUniqueNetId&, const FChatRoomId&, const FUniqueNetId&);`
- L417 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnChatRoomMemberUpdate, const FUniqueNetId&, const FChatRoomId&, const FUniqueNetId&);`
- L418 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnChatRoomMessageSent, const FUniqueNetId&, const FChatRoomId&, bool, const FString&);`
- L419 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnChatRoomMessageReceived, const FUniqueNetId&, const FChatRoomId&, const TSharedRef<FChatMessage>&);`
- L420 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnChatPrivateMessageSent, const FUniqueNetId&, const FUniqueNetId&, bool, const FString&);`
- L421 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnChatPrivateMessageReceived, const FUniqueNetId&, const TSharedRef<FChatMessage>&);`

#### Free symbols / members of external scopes

- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineChat, Log, All);`
- L13 _macro_ `#define UE_LOG_ONLINE_CHAT(Verbosity, Format, ...) \`
- L18 _macro_ `#define UE_CLOG_ONLINE_CHAT(Conditional, Verbosity, Format, ...) \`
- L26 _typedef_ `typedef FString FChatRoomId;` — Id of a chat room
- L125 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnChatRoomCreated, const FUniqueNetId& , const FChatRoomId& , bool , const FString& );` — Delegate used when creating a new chat room @param UserId the user that made the request @param RoomId room that was requested @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L125 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnChatRoomCreated, const FUniqueNetId& , const FChatRoomId& , bool , const FString& );` — Delegate used when creating a new chat room @param UserId the user that made the request @param RoomId room that was requested @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L126 _typedef_ `typedef FOnChatRoomCreated::FDelegate FOnChatRoomCreatedDelegate;`
- L136 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnChatRoomConfigured, const FUniqueNetId& , const FChatRoomId& , bool , const FString& );` — Delegate used when configuring a chat room @param UserId the user that made the request @param RoomId room that was requested @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L136 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnChatRoomConfigured, const FUniqueNetId& , const FChatRoomId& , bool , const FString& );` — Delegate used when configuring a chat room @param UserId the user that made the request @param RoomId room that was requested @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L137 _typedef_ `typedef FOnChatRoomConfigured::FDelegate FOnChatRoomConfiguredDelegate;`
- L147 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnChatRoomJoinPublic, const FUniqueNetId& , const FChatRoomId& , bool , const FString& );` — Delegate used when joining a public chat room @param UserId the user that made the request @param RoomId room that was requested @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L147 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnChatRoomJoinPublic, const FUniqueNetId& , const FChatRoomId& , bool , const FString& );` — Delegate used when joining a public chat room @param UserId the user that made the request @param RoomId room that was requested @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L148 _typedef_ `typedef FOnChatRoomJoinPublic::FDelegate FOnChatRoomJoinPublicDelegate;`
- L158 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnChatRoomJoinPrivate, const FUniqueNetId& , const FChatRoomId& , bool , const FString& );` — Delegate used when joining a private chat room @param UserId the user that made the request @param RoomId room that was requested @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L158 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnChatRoomJoinPrivate, const FUniqueNetId& , const FChatRoomId& , bool , const FString& );` — Delegate used when joining a private chat room @param UserId the user that made the request @param RoomId room that was requested @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L159 _typedef_ `typedef FOnChatRoomJoinPrivate::FDelegate FOnChatRoomJoinPrivateDelegate;`
- L169 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnChatRoomExit, const FUniqueNetId& , const FChatRoomId& , bool , const FString& );` — Delegate used when exiting a chat room @param UserId the user that made the request @param RoomId room that was requested @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L169 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnChatRoomExit, const FUniqueNetId& , const FChatRoomId& , bool , const FString& );` — Delegate used when exiting a chat room @param UserId the user that made the request @param RoomId room that was requested @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L170 _typedef_ `typedef FOnChatRoomExit::FDelegate FOnChatRoomExitDelegate;`
- L179 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChatRoomMemberJoin, const FUniqueNetId& , const FChatRoomId& , const FUniqueNetId& );` — Delegate used when another chat room member enters/joins @param UserId user currently in the room @param RoomId room that member is in @param MemberId the user that entered
- L179 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChatRoomMemberJoin, const FUniqueNetId& , const FChatRoomId& , const FUniqueNetId& );` — Delegate used when another chat room member enters/joins @param UserId user currently in the room @param RoomId room that member is in @param MemberId the user that entered
- L180 _typedef_ `typedef FOnChatRoomMemberJoin::FDelegate FOnChatRoomMemberJoinDelegate;`
- L189 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChatRoomMemberExit, const FUniqueNetId& , const FChatRoomId& , const FUniqueNetId& );` — Delegate used when another chat room member exits @param UserId user currently in the room @param RoomId room that member is in @param MemberId the user that exited
- L189 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChatRoomMemberExit, const FUniqueNetId& , const FChatRoomId& , const FUniqueNetId& );` — Delegate used when another chat room member exits @param UserId user currently in the room @param RoomId room that member is in @param MemberId the user that exited
- L190 _typedef_ `typedef FOnChatRoomMemberExit::FDelegate FOnChatRoomMemberExitDelegate;`
- L199 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChatRoomMemberUpdate, const FUniqueNetId& , const FChatRoomId& , const FUniqueNetId& );` — Delegate used when another chat room member is updated @param UserId user currently in the room @param RoomId room that member is in @param MemberId the user that updated
- L199 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChatRoomMemberUpdate, const FUniqueNetId& , const FChatRoomId& , const FUniqueNetId& );` — Delegate used when another chat room member is updated @param UserId user currently in the room @param RoomId room that member is in @param MemberId the user that updated
- L200 _typedef_ `typedef FOnChatRoomMemberUpdate::FDelegate FOnChatRoomMemberUpdateDelegate;`
- L210 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnChatRoomMessageSent, const FUniqueNetId& , const FChatRoomId& , bool , const FString& );` — Delegate used when a chat message is sent to a chat room @param UserId the user that made the request @param RoomId room that was requested @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L210 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnChatRoomMessageSent, const FUniqueNetId& , const FChatRoomId& , bool , const FString& );` — Delegate used when a chat message is sent to a chat room @param UserId the user that made the request @param RoomId room that was requested @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L211 _typedef_ `typedef FOnChatRoomMessageSent::FDelegate FOnChatRoomMessageSentDelegate;`
- L220 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChatRoomMessageReceived, const FUniqueNetId& , const FChatRoomId& , const TSharedRef<FChatMessage>& );` — Delegate used when a chat message is received from a chat room @param UserId user currently in the room @param RoomId room that member is in @param ChatMessage the message that was received
- L220 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChatRoomMessageReceived, const FUniqueNetId& , const FChatRoomId& , const TSharedRef<FChatMessage>& );` — Delegate used when a chat message is received from a chat room @param UserId user currently in the room @param RoomId room that member is in @param ChatMessage the message that was received
- L221 _typedef_ `typedef FOnChatRoomMessageReceived::FDelegate FOnChatRoomMessageReceivedDelegate;`
- L231 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnChatPrivateMessageSent, const FUniqueNetId& , const FUniqueNetId& , bool , const FString& );` — Delegate used when a private chat message is sent to another user @param UserId the user that made the request @param RecipientId the user the message was sent to @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L231 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnChatPrivateMessageSent, const FUniqueNetId& , const FUniqueNetId& , bool , const FString& );` — Delegate used when a private chat message is sent to another user @param UserId the user that made the request @param RecipientId the user the message was sent to @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L232 _typedef_ `typedef FOnChatPrivateMessageSent::FDelegate FOnChatPrivateMessageSentDelegate;`
- L240 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChatPrivateMessageReceived, const FUniqueNetId& , const TSharedRef<FChatMessage>& );` — Delegate used when a private chat message is received from another user @param UserId user that received the message @param ChatMessage the message that was received
- L240 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChatPrivateMessageReceived, const FUniqueNetId& , const TSharedRef<FChatMessage>& );` — Delegate used when a private chat message is received from another user @param UserId user that received the message @param ChatMessage the message that was received
- L241 _typedef_ `typedef FOnChatPrivateMessageReceived::FDelegate FOnChatPrivateMessageReceivedDelegate;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineCodeRedemptionInterface.h` (Public)


#### class `FCodeLockInfo`  
`class FCodeLockInfo`  
_L10-17_
- L13 _public member_ `FString CodeType;`
- L14 _public member_ `FString CodeId;`
- L15 _public member_ `FString CodeUseId;`
- L16 _public member_ `FString OfferId;`

#### class `FCodeEvaluationInfo`  
`class FCodeEvaluationInfo`  
_L19-26_
- L22 _public member_ `FString CodeType;`
- L23 _public member_ `FString CodeId;`
- L24 _public member_ `FString CodeStatus;`
- L25 _public member_ `FString OfferId;`

#### class `IOnlineCodeRedemption`  
`class IOnlineCodeRedemption`  
_L54-85_
- desc: IOnlineCodeRedemption - Interface for locking, unlocking, and evaluating codes. Use IOnlineFulfillment to redeem it.
- L57 _public prototype_ `virtual ~IOnlineCodeRedemption() = default;`
- L66 _public prototype_ `virtual void LockCode(const FString& CodeId, int32 LockTimeoutSeconds, const FOnProductCodeLockedComplete& Delegate) = 0;` — Initiate the lock code process for reserving a product redemption @param CodeId The Redemption code to lock @param LockTimeoutSeconds The duration in seconds to keep the code locked for @param Delegate completion callback (guaranteed to be called)
- L75 _public prototype_ `virtual void UnlockCode(const FString& CodeId, const FString& CodeUseId, const FOnProductCodeUnlockedComplete& Delegate) = 0;` — Initiate the Release code process to clear reservation on a product code @param CodeId The Redemption code to unlock @param CodeUseId The in use Code Id that was returned from LockCode @param Delegate completion callback (guaranteed to be called)
- L84 _public prototype_ `virtual void EvaluateCode(const FUniqueNetId& UserId, const FString& CodeId, const FOnProductCodeEvaluateComplete& Delegate) = 0;` — Initiate the Evaluation Code process for checking if a code is valid and what product information it relates too @param UserId User initiating the request @param CodeId The Redemption code to evaluate @param Delegate completion callback (guaranteed to be called)

#### Free symbols / members of external scopes

- L34 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnProductCodeLockedComplete, const FOnlineError& , const TSharedRef<FCodeLockInfo>&);` — Delegate used when the a lock code request is completed @param FOnlineError The Result of the HttpRequest @param TSharedRef<FCodeLockInfo> Data From a successful Request
- L34 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnProductCodeLockedComplete, const FOnlineError& , const TSharedRef<FCodeLockInfo>&);` — Delegate used when the a lock code request is completed @param FOnlineError The Result of the HttpRequest @param TSharedRef<FCodeLockInfo> Data From a successful Request
- L41 _delegate_ `DECLARE_DELEGATE_OneParam(FOnProductCodeUnlockedComplete, const FOnlineError& );` — Delegate used when the an evaluate code request is completed @param FOnlineError The Result of the HttpRequest
- L41 _prototype_ `DECLARE_DELEGATE_OneParam(FOnProductCodeUnlockedComplete, const FOnlineError& );` — Delegate used when the an evaluate code request is completed @param FOnlineError The Result of the HttpRequest
- L49 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnProductCodeEvaluateComplete, const FOnlineError& , const TSharedRef<FCodeEvaluationInfo>&);` — Delegate used when the an evaluate code request is completed @param FOnlineError The Result of the HttpRequest @param TSharedRef<FCodeEvaluationInfo> Data From a successful Request
- L49 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnProductCodeEvaluateComplete, const FOnlineError& , const TSharedRef<FCodeEvaluationInfo>&);` — Delegate used when the an evaluate code request is completed @param FOnlineError The Result of the HttpRequest @param TSharedRef<FCodeEvaluationInfo> Data From a successful Request

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineContentRestrictionInterface.h` (Public)


#### class `IOnlineContentAgeRestriction`  
`class IOnlineContentAgeRestriction`  
_L23-36_
- desc: IOnlineContentAgeRestriction - Interface class for managing a user's content age restriction status
- L26 _public prototype_ `virtual ~IOnlineContentAgeRestriction() = default;`
- L35 _public prototype_ `virtual void QueryContentAgeRestriction(const FUniqueNetId& LocalUserId, const TArray<FString>& RatingBoards, FOnQueryContentAgeRestictionComplete CompletionDelegate) = 0;` — Query the content age restriction status for an account @param LocalUserId - Id of the player to check the content age restriction status for @param RatingBoards - Array of rating boards defined to query status with @param CompletionDelegate - Completion delegate called when the QueryContentAgeRestriction call is complete

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnQueryContentAgeRestictionComplete, const FUniqueNetId& , const bool , const FOnlineError& );` — Delegate fired when content age restriction check is completed @param LocalUserId the id of the player that this callback is intended for @param bAgeRestricted the restriction result (is or is not restricted) @param Result whether or not the process completed successfully
- L18 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnQueryContentAgeRestictionComplete, const FUniqueNetId& , const bool , const FOnlineError& );` — Delegate fired when content age restriction check is completed @param LocalUserId the id of the player that this callback is intended for @param bAgeRestricted the restriction result (is or is not restricted) @param Result whether or not the process completed successfully

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineDeviceNotificationInterface.h` (Public)


#### class `IOnlineDeviceNotification`  
`class IOnlineDeviceNotification`  
_L29-53_
- desc: IOnlineDeviceNotification - Interface for communications service
- L32 _public prototype_ `virtual ~IOnlineDeviceNotification() = default;`
- L42 _public prototype_ `virtual void RegisterDevice(const FUniqueNetId& LocalUserId, const FString& InstanceId, const FString& ChannelType, const FOnRegisterDeviceComplete& Delegate) = 0;` — Initiate the create/register device process @param LocalUserId user making the request @param InstanceId the device registration token generated on the device @param ChannelType the channel being registered (for example: fcm) @param Delegate completion callback (guaranteed to be called)
- L52 _public prototype_ `virtual void UnregisterDeviceByChannelType(const FUniqueNetId& LocalUserId, const FString& InstanceId, const FString& ChannelType, const FOnUnregisterDeviceByChannelTypeComplete& Delegate) = 0;` — Initiate the unregister device by channel type process @param LocalUserId user making the request @param InstanceId the device registration token generated on the device @param ChannelType the channel being unregistered (for example: fcm) @param Delegate completion callback (guaranteed to be called)

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRegisterDeviceComplete, const FOnlineError& );` — Delegate used when the register device request is completed @param FOnlineError The Result of the Request
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRegisterDeviceComplete, const FOnlineError& );` — Delegate used when the register device request is completed @param FOnlineError The Result of the Request
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnUnregisterDeviceByChannelTypeComplete, const FOnlineError& );` — Delegate used when the unregister device by channel type request is completed @param FOnlineError The Result of the Request
- L24 _prototype_ `DECLARE_DELEGATE_OneParam(FOnUnregisterDeviceByChannelTypeComplete, const FOnlineError& );` — Delegate used when the unregister device by channel type request is completed @param FOnlineError The Result of the Request

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineEntitlementsInterface.h` (Public)


#### struct `FOnlineEntitlement`  
`struct FOnlineEntitlement`  
_L28-74_
- desc: Details of an entitlement
- L31 _public member_ `FUniqueEntitlementId Id;` — Unique Entitlement Id associated with this entitlement
- L33 _public member_ `FString Name;` — Display name for the entitlement
- L35 _public member_ `FString ItemId;` — Id for the item that this entitlement is associated with
- L37 _public member_ `FString Namespace;` — Namespace of the entitlement
- L39 _public member_ `bool bIsConsumable;` — True if the entitlement is a consumable
- L41 _public member_ `int32 RemainingCount;` — Number of uses still available for a consumable
- L43 _public member_ `int32 ConsumedCount;` — Number of prior uses for a consumable
- L45 _public member_ `FString StartDate;` — When the entitlement started
- L47 _public member_ `FString EndDate;` — When the entitlement will expire
- L49 _public member_ `FString Status;` — Current Status of the entitlement e.g. Active, Subscribe, Expire ...
- L51 _public function_ `FOnlineEntitlement() : bIsConsumable(false) , RemainingCount(1) , ConsumedCount(0)`
- L57 _public prototype_ `virtual ~FOnlineEntitlement() = default;`
- L62 _public function_ `virtual bool GetAttribute(const FString& AttrName, FString& OutAttrValue) const` — @return Any additional data associated with the entitlement
- L70 _public function_ `bool operator==(const FOnlineEntitlement& Other) const` — Equality operator

#### class `IOnlineEntitlements`  
`class IOnlineEntitlements`  
_L91-144_
- desc: Interface for retrieving user entitlements
- L94 _public prototype_ `virtual ~IOnlineEntitlements() = default;`
- L104 _public prototype_ `virtual TSharedPtr<FOnlineEntitlement> GetEntitlement(const FUniqueNetId& UserId, const FUniqueEntitlementId& EntitlementId) = 0;` — Checks for and retrieves a single cached entitlement for a user @param UserId the ID of the user to get this entitlement for @param EntitlementId the ID of the entitlement to retrieve @return entitlement entry if found, null otherwise
- L114 _public prototype_ `virtual TSharedPtr<FOnlineEntitlement> GetItemEntitlement(const FUniqueNetId& UserId, const FString& ItemId) = 0;` — Checks for and retrieves a single cached entitlement for a user @param UserId the ID of the user to get this entitlement for @param ItemId the ID of the item to retrieve an entitlement for @return entitlement entry if found, null otherwise
- L123 _public prototype_ `virtual void GetAllEntitlements(const FUniqueNetId& UserId, const FString& Namespace, TArray<TSharedRef<FOnlineEntitlement>>& OutUserEntitlements) = 0;` — Gets the cached entitlement set for the requested user @param UserId the ID of the user to get entitlements for @param Namespace optional namespace to filter on @param OutUserEntitlements out parameter to copy the user's entitlements into
- L133 _public prototype_ `virtual bool QueryEntitlements(const FUniqueNetId& UserId, const FString& Namespace, const FPagedQuery& Page = FPagedQuery()) = 0;` — Contacts server and retrieves the list of the user's entitlements, caching them locally @param UserId the ID of the user to act on @param Namespace optional namespace to filter on @return true if the operation started successfully
- L143 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnQueryEntitlementsComplete, bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate instanced called when enumerating entitlements has completed @param bWasSuccessful true if server was contacted and a valid result received @param UserId of the user who was granted entitlements in this callback @param Namespace optional namespace that was used to query. Empty means all entitlements were queried @param Error string representing the error condition

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineEntitlement, Log, All);`
- L10 _macro_ `#define UE_LOG_ONLINE_ENTITLEMENT(Verbosity, Format, ...) \`
- L15 _macro_ `#define UE_CLOG_ONLINE_ENTITLEMENT(Conditional, Verbosity, Format, ...) \`
- L23 _typedef_ `typedef FString FUniqueEntitlementId;` — unique identifier for entitlements
- L85 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnQueryEntitlementsComplete, bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate declaration for when entitlements are enumerated @param bWasSuccessful true if server was contacted and a valid result received @param UserId of the user who was granted entitlements in this callback @param Namespace optional namespace that was used to query. Empty means all entitlements were queried @param Error string representing the error condition
- L85 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnQueryEntitlementsComplete, bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate declaration for when entitlements are enumerated @param bWasSuccessful true if server was contacted and a valid result received @param UserId of the user who was granted entitlements in this callback @param Namespace optional namespace that was used to query. Empty means all entitlements were queried @param Error string representing the error condition
- L86 _typedef_ `typedef FOnQueryEntitlementsComplete::FDelegate FOnQueryEntitlementsCompleteDelegate;`
- L146 _typedef_ `typedef TSharedPtr<IOnlineEntitlements, ESPMode::ThreadSafe> IOnlineEntitlementsPtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineEventsInterface.h` (Public)


#### class `FOnlineEventParms`  
`class FOnlineEventParms : public FOnlineKeyValuePairs<FString, FVariantData>`  
_L20-20_
- inherits: `FOnlineKeyValuePairs<FString,FVariantData>`

#### class `IOnlineEvents`  
`class IOnlineEvents`  
_L25-47_
- desc: IOnlineEvents - Interface class for events
- L38 _public prototype_ `virtual bool TriggerEvent( const FUniqueNetId& PlayerId, const TCHAR* EventName, const FOnlineEventParms& Parms ) = 0;` — Trigger an event by name @param PlayerId	- Player to trigger the event for @param EventName - Name of the event @param Parms		- The parameter list to be passed into the event @return Whether the event was successfully triggered
- L46 _public prototype_ `virtual void SetPlayerSessionId(const FUniqueNetId& PlayerId, const FGuid& PlayerSessionId) = 0;` — Quick way to send a valid PlayerSessionId with every event, required for Xbox One @param PlayerId the unique id of the player this session is associated with @param PlayerSessionId A GUID unique to this player session

#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineEvents, Log, All);`
- L8 _macro_ `#define UE_LOG_ONLINE_EVENTS(Verbosity, Format, ...) \`
- L13 _macro_ `#define UE_CLOG_ONLINE_EVENTS(Conditional, Verbosity, Format, ...) \`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineExternalUIInterface.h` (Public)


#### struct `FLoginFlowResult`  
`struct FLoginFlowResult`  
_L45-78_
- desc: A single login flow result
- L47 _public function_ `FLoginFlowResult() : Error(EOnlineErrorResult::Unknown) , NumericErrorCode(0)`
- L53 _public member_ `FString Token;` — Token returned by the login flow (platform dependent)
- L55 _public member_ `FOnlineError Error;` — Errors generated during login flow
- L57 _public member_ `int32 NumericErrorCode;` — Numeric error code provided by the backend expected to correspond to error stored in ErrorCode
- L60 _public function_ `bool IsValid() const` — @return true if this result is usable for further login steps
- L63 _public function_ `bool IsComplete() const` — @return true if this result has reached a finished state
- L70 _public function_ `FString ToDebugString() const`

#### struct `FShowWebUrlParams`  
`struct FShowWebUrlParams`  
_L166-220_
- desc: Parameters used to show a web UI
- L169 _public member_ `bool bEmbedded;` — presented without a frame if embedded enabled
- L171 _public member_ `bool bShowCloseButton;` — Show the built in close button
- L173 _public member_ `bool bShowBackground;` — Show the built in background
- L175 _public member_ `bool bHideCursor;` — Hide the mouse cursor
- L177 _public member_ `bool bResetCookies;` — Rest cookies before invoking web browser
- L179 _public member_ `int32 OffsetX;` — x offset in pixels from top left
- L181 _public member_ `int32 OffsetY;` — y offset in pixels from top left
- L183 _public member_ `int32 SizeX;` — x size in pixels
- L185 _public member_ `int32 SizeY;` — y size in pixels
- L187 _public member_ `TArray<FString> AllowedDomains;` — if specified then restricted to only navigate within these domains
- L189 _public member_ `FString CallbackPath;` — portion of url for detecting callback.  Eg. "&code=", "redirect=", etc
- L194 _public function_ `FShowWebUrlParams(bool InbEmbedded, int32 InOffsetX, int32 InOffsetY, int32 InSizeX, int32 InSizeY) : bEmbedded(InbEmbedded) , bShowCloseButton(false) , bShowBackground(false) , bHideCursor(false) , bResetCookies(false) , OffsetX(InOffsetX) , OffsetY(InOffsetY) , SizeX(InSizeX) , SizeY(InSizeY)` — Constructor
- L209 _public function_ `FShowWebUrlParams() : bEmbedded(false) , bShowCloseButton(false) , bShowBackground(false) , bHideCursor(false) , bResetCookies(false) , OffsetX(0) , OffsetY(0) , SizeX(0) , SizeY(0)` — Default Constructor

#### struct `FShowStoreParams`  
`struct FShowStoreParams`  
_L224-242_
- L227 _public member_ `FString Category;` — Category filter for products to browse
- L230 _public member_ `FUniqueOfferId ProductId;` — Product to show directly instead of the whole store
- L233 _public member_ `bool bAddToCart;` — If the specific product id should be added to the user's cart automatically
- L238 _public function_ `FShowStoreParams(const FString& InCategory = FString()) : Category(InCategory) , bAddToCart(false)` — Constructor

#### struct `FShowSendMessageParams`  
`struct FShowSendMessageParams`  
_L244-263_
- L246 _public member_ `FText DisplayTitle;`
- L248 _public member_ `TMap<FString, FString> DisplayTitle_Loc;` — Map of language to text so the recipient's platform OS can display the localized string
- L249 _public member_ `FText DisplayMessage;`
- L250 _public member_ `FText DisplayDetails;`
- L252 _public member_ `TMap<FString, FString> DisplayDetails_Loc;` — Map of language to text so the recipient's platform OS can display the localized string
- L253 _public member_ `TArray<uint8> DisplayThumbnail;`
- L254 _public member_ `FOnlineMessagePayload DataPayload;`
- L255 _public member_ `int32 MaxRecipients;`
- L260 _public function_ `FShowSendMessageParams() : MaxRecipients(1)` — Constructor

#### enum `EPlatformMessageType`  
`enum class EPlatformMessageType`  
_L268-273_
- desc: Union of all the platform informational message types we handle (some may be handled by more than one platform)
- L270 _public enumerator_ `EmptyStore`
- L271 _public enumerator_ `ChatRestricted`
- L272 _public enumerator_ `UGCRestricted`

#### class `IOnlineExternalUI`  
`class IOnlineExternalUI`  
_L287-463_
- desc: Interface definition for the online services external UIs Any online service that provides extra UI overlays will implement the relevant functions
- L290 _protected function_ `IOnlineExternalUI()`
- L293 _public prototype_ `virtual ~IOnlineExternalUI() = default;`
- L307 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) = 0;` — Displays the UI that prompts the user for their login credentials. Each platform handles the authentication of the user's data. @param ControllerIndex The controller that prompted showing the login UI. If the platform supports it, it will pair the signed-in user with this controller. @param bShowOnlineOnly whether to only display online enabled profiles or not @param bShowSkipButton On platforms that support it, display the "Skip" button @param Delegate The delegate to execute when the user closes the login UI. @return true if it was able to show the UI, false if it failed
- L318 _public prototype_ `virtual bool ShowAccountCreationUI(const int ControllerIndex, const FOnAccountCreationUIClosedDelegate& Delegate = FOnAccountCreationUIClosedDelegate()) = 0;` — Displays the UI that prompts the user to create an account @param ControllerIndex The controller that prompted showing the account creation UI. If the platform supports it, it will pair the signed-in user with this controller. @param Delegate The delegate to execute when the user closes the account creation UI. @return true if it was able to show the UI, false if it failed
- L327 _public prototype_ `virtual bool ShowFriendsUI(int32 LocalUserNum) = 0;` — Displays the UI that shows a user's list of friends @param LocalUserNum the controller number of the associated user @return true if it was able to show the UI, false if it failed
- L337 _public prototype_ `virtual bool ShowInviteUI(int32 LocalUserNum, FName SessionName = NAME_GameSession) = 0;` — Displays the UI that shows a user's list of friends to invite @param LocalUserNum the controller number of the associated user @param SessionName name of session associated with the invite @return true if it was able to show the UI, false if it failed
- L346 _public prototype_ `virtual bool ShowAchievementsUI(int32 LocalUserNum) = 0;` — Displays the UI that shows a user's list of achievements @param LocalUserNum the controller number of the associated user @return true if it was able to show the UI, false if it failed
- L355 _public prototype_ `virtual bool ShowLeaderboardUI(const FString& LeaderboardName) = 0;` — Displays the UI that shows a specific leaderboard @param LeaderboardName the name of the leaderboard to show @return true if it was able to show the UI, false if it failed
- L365 _public prototype_ `virtual bool ShowWebURL(const FString& Url, const FShowWebUrlParams& ShowParams, const FOnShowWebUrlClosedDelegate& Delegate = FOnShowWebUrlClosedDelegate()) = 0;` — Displays a web page in the external UI @param WebURL fully formed web address (http://www.google.com) @param ShowParams configuration for the UI display @return true if it was able to show the UI, false if it failed
- L372 _public prototype_ `virtual bool CloseWebURL() = 0;` — Closes the currently active web external UI @return true if it was able to show the UI, false if it failed
- L382 _public prototype_ `virtual bool ShowProfileUI(const FUniqueNetId& Requestor, const FUniqueNetId& Requestee, const FOnProfileUIClosedDelegate& Delegate = FOnProfileUIClosedDelegate()) = 0;` — Displays a user's profile card. @param Requestor The user requesting the profile. @param Requestee The user for whom to show the profile. @return true if it was able to show the UI, false if it failed
- L391 _public prototype_ `virtual bool ShowAccountUpgradeUI(const FUniqueNetId& UniqueId) = 0;` — Displays a system dialog to purchase user account upgrades.  e.g. PlaystationPlus, XboxLive GOLD, etc. @param UniqueID of the user to show the dialog for @return true if it was able to show the UI, false if it failed
- L401 _public prototype_ `virtual bool ShowStoreUI(int32 LocalUserNum, const FShowStoreParams& ShowParams, const FOnShowStoreUIClosedDelegate& Delegate = FOnShowStoreUIClosedDelegate()) = 0;` — Display the platform UI for browsing available products for purchase @param LocalUserNum the controller number of the associated user @param ShowParams configuration for the UI display @return true if it was able to show the UI, false if it failed
- L411 _public prototype_ `virtual bool ShowSendMessageUI(int32 LocalUserNum, const FShowSendMessageParams& ShowParams, const FOnShowSendMessageUIClosedDelegate& Delegate = FOnShowSendMessageUIClosedDelegate()) = 0;` — Display the platform UI for sending a mailbox message to another user @param LocalUserNum the controller number of the associated user @param ShowParams configuration for the UI display @return true if it was able to show the UI, false if it failed
- L423 _public function_ `virtual bool ShowSendMessageToUserUI(int32 LocalUserNum, const FUniqueNetId& Recipient, const FShowSendMessageParams& ShowParams, const FOnShowSendMessageUIClosedDelegate& Delegate = FOnShowSendMessageUIClosedDelegate())` — Display the platform UI for sending a mailbox message to the specified user. Will attempt to automatically send the message if the platform allows for it. @param LocalUserNum the controller number of the associated user @param Recipient the user that should receive this message @param ShowParams configuration for the UI display @return true if it was able to send the message and show the UI, false if it failed
- L436 _public function_ `virtual bool ShowPlatformMessageBox(const FUniqueNetId& UserId, EPlatformMessageType MessageType)` — Displays an informational system dialog. @param UserId Who to show this dialog for. @param MessageId Platform-specific identifier for the message box to display.
- L441 _public function_ `virtual void ReportEnterInGameStoreUI()` — Tell the system that you've entered into a screen considered in-game store.
- L446 _public function_ `virtual void ReportExitInGameStoreUI()` — Tell the system that you've entered into a screen considered in-game store.
- L453 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnExternalUIChange, bool);` — Delegate called when the external UI is opened or closed @param bIsOpening state of the external UI
- L458 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnLoginFlowUIRequired, const FString& , const FOnLoginRedirectURL& , const FOnLoginFlowComplete& , bool& );` — Delegate called when the online subsystem requires an external UI to handle login flow
- L462 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnCreateAccountFlowUIRequired, const FString& , const FOnLoginRedirectURL& , const FOnLoginFlowComplete& , bool& );` — Delegate called when the online subsystem requires an external UI to handle account creation

#### Free symbols / members of external scopes

- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineExternalUI, Log, All);`
- L12 _macro_ `#define UE_LOG_ONLINE_EXTERNALUI(Verbosity, Format, ...) \`
- L17 _macro_ `#define UE_CLOG_ONLINE_EXTERNALUI(Conditional, Verbosity, Format, ...) \`
- L25 _macro_ `#define LOGIN_TOKEN_FOUND FString()` — FLoginFlowResult codes
- L26 _macro_ `#define LOGIN_ERROR_UNKNOWN TEXT("com.epicgames.login.unknown")`
- L27 _macro_ `#define LOGIN_ERROR_AUTH_FAILURE TEXT("com.epicgames.login.auth_failure")`
- L28 _macro_ `#define LOGIN_ERROR_NO_EXTERNAL_ACCOUNT TEXT("com.epicgames.login.no_account_found_for_external_auth")`
- L29 _macro_ `#define LOGIN_CANCELLED TEXT("com.epicgames.login.canceled")`
- L30 _macro_ `#define LOGIN_PAGELOADFAILED TEXT("com.epicgames.login.pageloadfailed")`
- L31 _macro_ `#define LOGIN_CEFLOADFAILED TEXT("com.epicgames.login.cefloadfailed")`
- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnExternalUIChange, bool);` — Delegate called when the external UI is opened or closed @param bIsOpening state of the external UI
- L38 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnExternalUIChange, bool);` — Delegate called when the external UI is opened or closed @param bIsOpening state of the external UI
- L39 _typedef_ `typedef FOnExternalUIChange::FDelegate FOnExternalUIChangeDelegate;`
- L85 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLoginFlowComplete, const FLoginFlowResult& );` — Delegate executed with a login flow has completed @Param Result the result of the login process
- L85 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLoginFlowComplete, const FLoginFlowResult& );` — Delegate executed with a login flow has completed @Param Result the result of the login process
- L94 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FLoginFlowResult, FOnLoginRedirectURL, const FString& );` — Delegate executed when a redirect URL request has been received by the internal browser window @param URL location of the next page @return the result of processing this URL.  Result.IsComplete() should return true if the login flow is expected to terminate
- L94 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FLoginFlowResult, FOnLoginRedirectURL, const FString& );` — Delegate executed when a redirect URL request has been received by the internal browser window @param URL location of the next page @return the result of processing this URL.  Result.IsComplete() should return true if the login flow is expected to terminate
- L104 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnLoginFlowUIRequired, const FString& , const FOnLoginRedirectURL& , const FOnLoginFlowComplete& , bool& );` — Delegate executed by the requesting system when a supporting login flow browser window is asked to handle the request @param RequestedURL destination to fulfill the login request @param OnLoginRedirect delegate to fire when URL redirects are detected @param OnLoginFlowComplete delegate to fire when the login flow code has reached flow conclusion @param bOutShouldContinueLogin true if the login flow code can proceed with the information given, false the caller should handle login failure
- L104 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnLoginFlowUIRequired, const FString& , const FOnLoginRedirectURL& , const FOnLoginFlowComplete& , bool& );` — Delegate executed by the requesting system when a supporting login flow browser window is asked to handle the request @param RequestedURL destination to fulfill the login request @param OnLoginRedirect delegate to fire when URL redirects are detected @param OnLoginFlowComplete delegate to fire when the login flow code has reached flow conclusion @param bOutShouldContinueLogin true if the login flow code can proceed with the information given, false the caller should handle login failure
- L105 _typedef_ `typedef FOnLoginFlowUIRequired::FDelegate FOnLoginFlowUIRequiredDelegate;`
- L118 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnCreateAccountFlowUIRequired, const FString& , const FOnLoginRedirectURL& , const FOnLoginFlowComplete& , bool& );` — Delegate executed by the requesting system when a supporting account creation flow browser window is asked to handle the request @param RequestedURL destination to fulfill the creation request @param OnLoginRedirect delegate to fire when URL redirects are detected @param OnLoginFlowComplete delegate to fire when the creation flow code has reached flow conclusion @param bOutShouldContinueLogin true if the creation flow code can proceed with the information given, false the caller should handle creation failure
- L118 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnCreateAccountFlowUIRequired, const FString& , const FOnLoginRedirectURL& , const FOnLoginFlowComplete& , bool& );` — Delegate executed by the requesting system when a supporting account creation flow browser window is asked to handle the request @param RequestedURL destination to fulfill the creation request @param OnLoginRedirect delegate to fire when URL redirects are detected @param OnLoginFlowComplete delegate to fire when the creation flow code has reached flow conclusion @param bOutShouldContinueLogin true if the creation flow code can proceed with the information given, false the caller should handle creation failure
- L119 _typedef_ `typedef FOnCreateAccountFlowUIRequired::FDelegate FOnCreateAccountFlowUIRequiredDelegate;`
- L128 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnLoginUIClosedDelegate, FUniqueNetIdPtr , const int , const FOnlineError& );` — Delegate executed when the external login UI has been closed. @param UniqueId The unique id of the user who signed in. Null if no user signed in. @param ControllerIndex The controller index of the controller that activated the login UI. @param Error any errors related to closing the UI
- L128 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnLoginUIClosedDelegate, FUniqueNetIdPtr , const int , const FOnlineError& );` — Delegate executed when the external login UI has been closed. @param UniqueId The unique id of the user who signed in. Null if no user signed in. @param ControllerIndex The controller index of the controller that activated the login UI. @param Error any errors related to closing the UI
- L137 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnAccountCreationUIClosedDelegate, const int , const FOnlineAccountCredentials& , const FOnlineError& );` — Delegate executed when the external account creation UI has been closed. @param ControllerIndex The controller index of the controller that activated the account creation UI. @param AccountCredentials Account credentials created for use by login if successful, invalid otherwiseS @param Error any errors related to closing the UI
- L137 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnAccountCreationUIClosedDelegate, const int , const FOnlineAccountCredentials& , const FOnlineError& );` — Delegate executed when the external account creation UI has been closed. @param ControllerIndex The controller index of the controller that activated the account creation UI. @param AccountCredentials Account credentials created for use by login if successful, invalid otherwiseS @param Error any errors related to closing the UI
- L144 _delegate_ `DECLARE_DELEGATE_OneParam(FOnShowWebUrlClosedDelegate, const FString& );` — Delegate executed when the web url UI has been closed @param FinalUrl the url that was used as the final redirect before closing
- L144 _prototype_ `DECLARE_DELEGATE_OneParam(FOnShowWebUrlClosedDelegate, const FString& );` — Delegate executed when the web url UI has been closed @param FinalUrl the url that was used as the final redirect before closing
- L151 _delegate_ `DECLARE_DELEGATE_OneParam(FOnShowStoreUIClosedDelegate, bool );` — Delegate executed when the store UI has been closed @param bPurchased true if a purchase occurred via the store ui
- L151 _prototype_ `DECLARE_DELEGATE_OneParam(FOnShowStoreUIClosedDelegate, bool );` — Delegate executed when the store UI has been closed @param bPurchased true if a purchase occurred via the store ui
- L158 _delegate_ `DECLARE_DELEGATE_OneParam(FOnShowSendMessageUIClosedDelegate, bool );` — Delegate executed when the send message UI has been closed @param bMessageSent if the user chose to send the message
- L158 _prototype_ `DECLARE_DELEGATE_OneParam(FOnShowSendMessageUIClosedDelegate, bool );` — Delegate executed when the send message UI has been closed @param bMessageSent if the user chose to send the message
- L163 _delegate_ `DECLARE_DELEGATE(FOnProfileUIClosedDelegate);` — Delegate executed when the user profile UI has been closed.
- L163 _prototype_ `DECLARE_DELEGATE(FOnProfileUIClosedDelegate);` — Delegate executed when the user profile UI has been closed.
- L222 _typedef_ `typedef FString FUniqueOfferId;`
- L278 _macro_ `#define SHOP_PURCHASABLE_APPLICATION TEXT("Application")` — Shop Purchasable types
- L279 _macro_ `#define SHOP_PURCHASABLE_ADDON TEXT("AddOnContent")`
- L280 _macro_ `#define SHOP_PURCHASABLE_CONSUMABLE TEXT("ConsumableContent")`
- L281 _macro_ `#define SHOP_PURCHASABLE_SUBSCRIPTION TEXT("SubscriptionContent")`
- L465 _typedef_ `typedef TSharedPtr<IOnlineExternalUI, ESPMode::ThreadSafe> IOnlineExternalUIPtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineFriendsInterface.h` (Public)


#### enum `EFriendsLists::Type`  
`enum Type`  
_L26-36_
- L29 _public enumerator_ `Default` — default friends list
- L31 _public enumerator_ `OnlinePlayers` — online players friends list
- L33 _public enumerator_ `InGamePlayers` — list of players running the same title/game
- L35 _public enumerator_ `InGameAndSessionPlayers` — list of players running the same title/game and in a session that has started

#### struct `FFriendSettings`  
`struct FFriendSettings`  
_L87-110_
- desc: Stores a generic list of settings for the Query/UpdateSettings calls
- L89 _public function_ `FFriendSettings()`
- L91 _public prototype_ `virtual ~FFriendSettings() = default;`
- L93 _public function_ `virtual bool GetSettingValue(const FString& SettingName, FString& Value) const`
- L104 _public function_ `virtual void SetSettingValue(const FString& SettingName, const FString& Value)`
- L109 _public member_ `TMap<FString, FString> SettingsMap;`

#### enum `ERecentPlayerEncounterType`  
`enum class ERecentPlayerEncounterType : uint8`  
_L115-120_
- desc: Encounter type of recent player
- L117 _public enumerator_ `Default`
- L118 _public enumerator_ `Teammate`
- L119 _public enumerator_ `Opponent`

#### struct `FReportPlayedWithUser`  
`struct FReportPlayedWithUser`  
_L125-141_
- desc: Stores information about a recent player
- L127 _public prototype_ `FReportPlayedWithUser() = delete;`
- L128 _public function_ `FReportPlayedWithUser(const FUniqueNetIdRef& InUserId, const FString& InPresenceStr, ERecentPlayerEncounterType InEncounterType=ERecentPlayerEncounterType::Default) : UserId(InUserId) , PresenceStr(InPresenceStr) , EncounterType(InEncounterType)`
- L136 _public member_ `FUniqueNetIdRef UserId;` — UserId to report played with
- L138 _public member_ `FString PresenceStr;` — Optional presence string
- L140 _public member_ `ERecentPlayerEncounterType EncounterType;` — Encounter type of this user

#### class `IOnlineFriends`  
`class IOnlineFriends`  
_L402-807_
- desc: Interface definition for the online services friends services Friends services are anything related to the maintenance of friends and friends lists
- L405 _protected function_ `IOnlineFriends()`
- L408 _public prototype_ `virtual ~IOnlineFriends() = default;`
- L413 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE(MAX_LOCAL_PLAYERS, OnFriendsChange);` — Delegate used in friends list change notifications
- L418 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE(MAX_LOCAL_PLAYERS, OnOutgoingInviteSent);` — Delegate used in outgoing invite list change notifications
- L426 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnInviteReceived, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when remote friend sends an invite @param UserId id of the local user that received the invite @param FriendId remote friend id that sent the invite
- L434 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnInviteAccepted, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when a remote friend accepts an invite @param UserId id of the local user that had sent the invite @param FriendId friend id that accepted the invite
- L442 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnInviteRejected, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when a remote friend rejects an invite @param UserId id of the local user that had sent the invite @param FriendId friend id that rejected the invite
- L450 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnInviteAborted, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when a remote friend cancels/aborts an sent invite @param UserId id of the local user that had received the invite @param FriendId friend id that canceled that invite
- L458 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnFriendRemoved, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when a remote friend removes user from friends list @param UserId id of the local user that had the friendship @param FriendId friend id that removed themself from the friendship
- L468 _public prototype_ `virtual bool ReadFriendsList(int32 LocalUserNum, const FString& ListName, const FOnReadFriendsListComplete& Delegate = FOnReadFriendsListComplete()) = 0;` — Starts an async task that reads the named friends list for the player @param LocalUserNum the user to read the friends list of @param ListName name of the friends list to read @return true if the read request was started successfully, false otherwise
- L478 _public prototype_ `virtual bool DeleteFriendsList(int32 LocalUserNum, const FString& ListName, const FOnDeleteFriendsListComplete& Delegate = FOnDeleteFriendsListComplete()) = 0;` — Starts an async task that deletes the named friends list for the player @param LocalUserNum the user to delete the friends list for @param ListName name of the friends list to delete @return true if the delete request was started successfully, false otherwise
- L489 _public prototype_ `virtual bool SendInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnSendInviteComplete& Delegate = FOnSendInviteComplete()) = 0;` — Starts an async task that sends an invite to another player. @param LocalUserNum the user that is sending the invite @param FriendId player that is receiving the invite @param ListName name of the friends list to invite to @return true if the request was started successfully, false otherwise
- L500 _public prototype_ `virtual bool AcceptInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnAcceptInviteComplete& Delegate = FOnAcceptInviteComplete()) = 0;` — Starts an async task that accepts an invite from another player. @param LocalUserNum the user that is accepting the invite @param FriendId player that had sent the pending invite @param ListName name of the friends list to operate on @return true if the request was started successfully, false otherwise
- L511 _public prototype_ `virtual bool RejectInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) = 0;` — Starts an async task that rejects an invite from another player. @param LocalUserNum the user that is rejecting the invite @param FriendId player that had sent the pending invite @param ListName name of the friends list to operate on @return true if the request was started successfully, false otherwise
- L522 _public prototype_ `virtual void SetFriendAlias(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FString& Alias, const FOnSetFriendAliasComplete& Delegate = FOnSetFriendAliasComplete()) = 0;` — Starts an async task that sets an alias a to friend. @param LocalUserNum the user that is setting the alias @param FriendId player that will have the alias associated @param ListName name of the friends list to operate on @param Alias the alias associated to the player
- L532 _public prototype_ `virtual void DeleteFriendAlias(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnDeleteFriendAliasComplete& Delegate = FOnDeleteFriendAliasComplete()) = 0;` — Starts an async task that delete an alias from a friend. @param LocalUserNum the user that is setting the alias @param FriendId player that will have the alias deleted from @param ListName name of the friends list to operate on
- L543 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_FOUR_PARAM(MAX_LOCAL_PLAYERS, OnRejectInviteComplete, bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when an invite reject request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param FriendId player that invited us @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L554 _public prototype_ `virtual bool DeleteFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) = 0;` — Starts an async task that deletes a friend from the named friends list @param LocalUserNum the user that is making the request @param FriendId player that will be deleted @param ListName name of the friends list to operate on @return true if the request was started successfully, false otherwise
- L565 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_FOUR_PARAM(MAX_LOCAL_PLAYERS, OnDeleteFriendComplete, bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when an friend delete request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param FriendId player that was deleted @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L576 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_FOUR_PARAM(MAX_LOCAL_PLAYERS, OnBlockedPlayerComplete, bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when a block player request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param UniqueId player that was blocked @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L587 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_FOUR_PARAM(MAX_LOCAL_PLAYERS, OnUnblockedPlayerComplete, bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when an unblock player request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param UniqueId player that was unblocked @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L594 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_ONE_PARAM(MAX_LOCAL_PLAYERS, OnBlockListChange, const FString& );` — Delegate used in block list change notifications @param ListName name of friends list that was operated on
- L605 _public prototype_ `virtual bool GetFriendsList(int32 LocalUserNum, const FString& ListName, TArray< TSharedRef<FOnlineFriend> >& OutFriends) = 0;` — Copies the list of friends for the player previously retrieved from the online service @param LocalUserNum the user to read the friends list of @param ListName name of the friends list to read @param OutFriends [out] array that receives the copied data @return true if friends list was found
- L616 _public prototype_ `virtual TSharedPtr<FOnlineFriend> GetFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) = 0;` — Get the cached friend entry if found @param LocalUserNum the user to read the friends list of @param ListName name of the friends list to read @param OutFriends [out] array that receives the copied data @return null ptr if not found
- L627 _public prototype_ `virtual bool IsFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) = 0;` — Checks that a unique player id is part of the specified user's friends list @param LocalUserNum the controller number of the associated user that made the request @param FriendId the id of the player being checked for friendship @param ListName name of the friends list to read @return true if friends list was found and the friend was valid
- L637 _public function_ `virtual void AddRecentPlayers(const FUniqueNetId& UserId, const TArray<FReportPlayedWithUser>& InRecentPlayers, const FString& ListName, const FOnAddRecentPlayersComplete& InCompletionDelegate)` — Add a list of players to a user's recent players list @param UserId user to query recent players for @param InRecentPlayers list of players to report @param Namespace the recent players namespace to list players under @param InCompletionDelegate delegate to fire on completion
- L647 _public prototype_ `virtual bool QueryRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace) = 0;` — Query for recent players of the current user @param UserId user to query recent players for @param Namespace the recent players namespace to retrieve @return true if query was started
- L657 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnQueryRecentPlayersComplete, const FUniqueNetId& , const FString& , bool , const FString& );` — Delegate used when the query for recent players has completed @param UserId the id of the user that made the request @param Namespace the recent players namespace @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L666 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnQueryBlockedPlayersComplete, const FUniqueNetId& , bool , const FString& );` — Delegate used when the query for blocked players has completed @param UserId the id of the user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param Error string representing the error condition
- L677 _public prototype_ `virtual bool GetRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace, TArray< TSharedRef<FOnlineRecentPlayer> >& OutRecentPlayers) = 0;` — Copies the cached list of recent players for a given user @param UserId user to retrieve recent players for @param Namespace the recent players namespace to retrieve (if empty retrieve all namespaces) @param OutRecentPlayers [out] array that receives the copied data @return true if recent players list was found for the given user
- L682 _public prototype_ `virtual void DumpRecentPlayers() const = 0;` — Dump state information about blocked players
- L690 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnRecentPlayersAdded, const FUniqueNetId& , const TArray<TSharedRef<FOnlineRecentPlayer>>& );` — Delegate used when recent players have been added @param UserId the id of the user recieving new recent players @param AddedPlayers players that were added to the recent players list
- L700 _public prototype_ `virtual bool BlockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId) = 0;` — Block a player @param LocalUserNum The user to check for @param PlayerId The player to block @return true if query was started
- L710 _public prototype_ `virtual bool UnblockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId) = 0;` — Unblock a player @param LocalUserNum The user to check for @param PlayerId The player to unblock @return true if query was started
- L719 _public prototype_ `virtual bool QueryBlockedPlayers(const FUniqueNetId& UserId) = 0;` — Query for blocked players @param UserId user to query blocked players for @return true if query was started
- L729 _public prototype_ `virtual bool GetBlockedPlayers(const FUniqueNetId& UserId, TArray< TSharedRef<FOnlineBlockedPlayer> >& OutBlockedPlayers) = 0;` — Get the list of blocked players @param UserId user to retrieve blocked players for @param OuBlockedPlayers [out] array that receives the copied data @return true if blocked players list was found for the given user
- L734 _public prototype_ `virtual void DumpBlockedPlayers() const = 0;` — Dump state information about blocked players
- L745 _public prototype_ `DEFINE_ONLINE_DELEGATE_FIVE_PARAM(OnFriendSettingsUpdated, const FUniqueNetId& , bool , bool , const FFriendSettings& , const FString& );` — Delegate used when the friends settings are updated @param UserId id of the local user that had their settings updated @param bWasSuccessful true if the async action completed without error, false if there was an error @param bWasUpdate true if the operation was an "update" operation (vs a passive read) @param Settings settings updated @param ErrorStr string representing the error condition
- L754 _public function_ `virtual void QueryFriendSettings(const FUniqueNetId& LocalUserId, FOnSettingsOperationComplete Delegate)` — Query the current friend settings @param LocalUserId user to retrieve friend settings for @param Delegate Delegate to call when operation has been completed
- L765 _public function_ `virtual void UpdateFriendInvitePolicySettings(const FUniqueNetId& LocalUserId, const EFriendInvitePolicy FriendInvitePolicy, const bool bAffectsExistingInvites, FOnSettingsOperationComplete Delegate)` — Update the current friend settings @param LocalUserId user to retrieve friend settings for @param FriendInvitePolicy invite policy to change designated user to @param bAffectsExistingInvites boolean to determine if existing friend invites are affected by this change @param Delegate Delegate to call when operation has been completed
- L775 _public function_ `virtual bool QueryFriendSettings(const FUniqueNetId& UserId, const FString& Source, const FOnQueryFriendSettingsComplete& Delegate = FOnQueryFriendSettingsComplete())` — Queries the settings we have stored for a third party source @param UserId user to retrieve settings for @param The source the settings relate to i.e. steam @return true if query was started
- L785 _public function_ `virtual bool GetFriendSettings(const FUniqueNetId& UserId, TMap<FString, TSharedRef<FOnlineFriendSettingsSourceData> >& OutSettings)` — Gets the cached information we have stored from a third party source @param UserId user to retrieve settings for @param OutSettings [out] Map that receives the copied data @return true if blocked players list was found for the given user
- L794 _public function_ `virtual EFriendInvitePolicy GetFriendInvitePolicy(const FUniqueNetId& UserId) const` — Gets the FriendInvitePolicy info that defines who can send friend invites to the user. (Public = Anyone, Friends_of_Friends = Only mutual friends, Private = No one) @param LocalUserId user to retrieve friendInvitePolicy settings for @return the permission setting from the UserState
- L805 _public function_ `virtual bool SetFriendSettings(const FUniqueNetId& UserId, const FString& Source, bool bNeverShowAgain, const FOnSetFriendSettingsComplete& Delegate = FOnSetFriendSettingsComplete())` — Set information we want to store for a third party source @param UserId user to retrieve settings for @param The source the settings relate to i.e. steam @param bNeverShowAgain A bool for if we should stop showing call outs for this source, (currently the only setting we store) @return true if query was started

#### Free symbols / members of external scopes

- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineFriend, Log, All);`
- L13 _macro_ `#define UE_LOG_ONLINE_FRIEND(Verbosity, Format, ...) \`
- L18 _macro_ `#define UE_CLOG_ONLINE_FRIEND(Conditional, Verbosity, Format, ...) \`
- L24 _namespace_ `namespace EFriendsLists`
- L39 _function_ `inline const TCHAR* ToString(EFriendsLists::Type EnumVal)` (scope `EFriendsLists`) — @return the stringified version of the enum passed in
- L56 _function_ `inline bool FromString(EFriendsLists::Type& OutEnum, const TCHAR* InString)` (scope `EFriendsLists`) — @return whether or not the passed string was successfully converted to a valid enum value
- L146 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnFriendsChange);` — Delegate used in friends list change notifications
- L146 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnFriendsChange);` — Delegate used in friends list change notifications
- L147 _typedef_ `typedef FOnFriendsChange::FDelegate FOnFriendsChangeDelegate;`
- L152 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnOutgoingInviteSent);` — Delegate used in outgoing invite list change notifications
- L152 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnOutgoingInviteSent);` — Delegate used in outgoing invite list change notifications
- L153 _typedef_ `typedef FOnOutgoingInviteSent::FDelegate FOnOutgoingInviteSentDelegate;`
- L163 _delegate_ `DECLARE_DELEGATE_FourParams(FOnReadFriendsListComplete, int32 , bool , const FString& , const FString& );` — Delegate used when the friends read request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L163 _prototype_ `DECLARE_DELEGATE_FourParams(FOnReadFriendsListComplete, int32 , bool , const FString& , const FString& );` — Delegate used when the friends read request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L173 _delegate_ `DECLARE_DELEGATE_FourParams(FOnDeleteFriendsListComplete, int32 , bool , const FString& , const FString& );` — Delegate used when the friends list delete request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L173 _prototype_ `DECLARE_DELEGATE_FourParams(FOnDeleteFriendsListComplete, int32 , bool , const FString& , const FString& );` — Delegate used when the friends list delete request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L184 _delegate_ `DECLARE_DELEGATE_FiveParams(FOnSendInviteComplete, int32 , bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when an invite send request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param FriendId player that was invited @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L184 _prototype_ `DECLARE_DELEGATE_FiveParams(FOnSendInviteComplete, int32 , bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when an invite send request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param FriendId player that was invited @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L195 _delegate_ `DECLARE_DELEGATE_FiveParams(FOnAcceptInviteComplete, int32 , bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when an invite accept request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param FriendId player that invited us @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L195 _prototype_ `DECLARE_DELEGATE_FiveParams(FOnAcceptInviteComplete, int32 , bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when an invite accept request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param FriendId player that invited us @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L206 _delegate_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FOnRejectInviteComplete, int32 , bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when an invite reject request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param FriendId player that invited us @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L206 _prototype_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FOnRejectInviteComplete, int32 , bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when an invite reject request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param FriendId player that invited us @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L207 _typedef_ `typedef FOnRejectInviteComplete::FDelegate FOnRejectInviteCompleteDelegate;`
- L217 _delegate_ `DECLARE_DELEGATE_FourParams(FOnSetFriendAliasComplete, int32 , const FUniqueNetId& , const FString& , const FOnlineError& );` — Delegate used when a set alias request has completed @param LocalUserNum the controller number of the associated user that made the request @param FriendId player that we set alias for @param ListName name of the friends list that was operated on @param Error error information on failure
- L217 _prototype_ `DECLARE_DELEGATE_FourParams(FOnSetFriendAliasComplete, int32 , const FUniqueNetId& , const FString& , const FOnlineError& );` — Delegate used when a set alias request has completed @param LocalUserNum the controller number of the associated user that made the request @param FriendId player that we set alias for @param ListName name of the friends list that was operated on @param Error error information on failure
- L227 _delegate_ `DECLARE_DELEGATE_FourParams(FOnDeleteFriendAliasComplete, int32 , const FUniqueNetId& , const FString& , const FOnlineError& );` — Delegate used when a delete friend alias request has completed @param LocalUserNum the controller number of the associated user that made the request @param FriendId player that we delete alias from @param ListName name of the friends list that was operated on @param Error error information on failure
- L227 _prototype_ `DECLARE_DELEGATE_FourParams(FOnDeleteFriendAliasComplete, int32 , const FUniqueNetId& , const FString& , const FOnlineError& );` — Delegate used when a delete friend alias request has completed @param LocalUserNum the controller number of the associated user that made the request @param FriendId player that we delete alias from @param ListName name of the friends list that was operated on @param Error error information on failure
- L238 _delegate_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FOnDeleteFriendComplete, int32 , bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when an friend delete request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param FriendId player that was deleted @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L238 _prototype_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FOnDeleteFriendComplete, int32 , bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when an friend delete request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param FriendId player that was deleted @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L239 _typedef_ `typedef FOnDeleteFriendComplete::FDelegate FOnDeleteFriendCompleteDelegate;`
- L250 _delegate_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FOnBlockedPlayerComplete, int32 , bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when a block request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param UniqueID Player blocked @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L250 _prototype_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FOnBlockedPlayerComplete, int32 , bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when a block request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param UniqueID Player blocked @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L251 _typedef_ `typedef FOnBlockedPlayerComplete::FDelegate FOnBlockedPlayerCompleteDelegate;`
- L262 _delegate_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FOnUnblockedPlayerComplete, int32 , bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when an unblock request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param UniqueID Player unblocked @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L262 _prototype_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FOnUnblockedPlayerComplete, int32 , bool , const FUniqueNetId& , const FString& , const FString& );` — Delegate used when an unblock request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param UniqueID Player unblocked @param ListName name of the friends list that was operated on @param ErrorStr string representing the error condition
- L263 _typedef_ `typedef FOnUnblockedPlayerComplete::FDelegate FOnUnblockedPlayerCompleteDelegate;`
- L271 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBlockListChange, int32 , const FString& );` — Delegate used in block list change notifications @param LocalUserNum the controller number of the associated user that made the request @param ListName name of the friends list that was operated on
- L271 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBlockListChange, int32 , const FString& );` — Delegate used in block list change notifications @param LocalUserNum the controller number of the associated user that made the request @param ListName name of the friends list that was operated on
- L272 _typedef_ `typedef FOnBlockListChange::FDelegate FOnBlockListChangeDelegate;`
- L282 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnQueryRecentPlayersComplete, const FUniqueNetId& , const FString& , bool , const FString& );` — Delegate used when the query for recent players has completed @param UserId the id of the user that made the request @param Namespace the recent players namespace @param bWasSuccessful true if the async action completed without error, false if there was an error @param ErrorStr string representing the error condition
- L282 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnQueryRecentPlayersComplete, const FUniqueNetId& , const FString& , bool , const FString& );` — Delegate used when the query for recent players has completed @param UserId the id of the user that made the request @param Namespace the recent players namespace @param bWasSuccessful true if the async action completed without error, false if there was an error @param ErrorStr string representing the error condition
- L283 _typedef_ `typedef FOnQueryRecentPlayersComplete::FDelegate FOnQueryRecentPlayersCompleteDelegate;`
- L291 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnAddRecentPlayersComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate used when adding a group of recent players has completed @param UserId the id of the user that made the request @param Error error information on failure
- L291 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnAddRecentPlayersComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate used when adding a group of recent players has completed @param UserId the id of the user that made the request @param Error error information on failure
- L299 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRecentPlayersAdded, const FUniqueNetId& , const TArray<TSharedRef<FOnlineRecentPlayer>>& );` — Delegate used when recent players have been added @param UserId the id of the user recieving new recent players @param AddedPlayers players that were added to the recent players list
- L299 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRecentPlayersAdded, const FUniqueNetId& , const TArray<TSharedRef<FOnlineRecentPlayer>>& );` — Delegate used when recent players have been added @param UserId the id of the user recieving new recent players @param AddedPlayers players that were added to the recent players list
- L300 _typedef_ `typedef FOnRecentPlayersAdded::FDelegate FOnRecentPlayersAddedDelegate;`
- L309 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnQueryBlockedPlayersComplete, const FUniqueNetId& , bool , const FString& );` — Delegate used when the query for blocked players has completed @param UserId the id of the user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param ErrorStr string representing the error condition
- L309 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnQueryBlockedPlayersComplete, const FUniqueNetId& , bool , const FString& );` — Delegate used when the query for blocked players has completed @param UserId the id of the user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param ErrorStr string representing the error condition
- L310 _typedef_ `typedef FOnQueryBlockedPlayersComplete::FDelegate FOnQueryBlockedPlayersCompleteDelegate;`
- L319 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnQueryFriendSettingsComplete, const FUniqueNetId&, bool, const FString&);` — Delegate used when the query for friends settings has completed @param UserId the id of the user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param ErrorStr string representing the error condition
- L319 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnQueryFriendSettingsComplete, const FUniqueNetId&, bool, const FString&);` — Delegate used when the query for friends settings has completed @param UserId the id of the user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param ErrorStr string representing the error condition
- L328 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnSetFriendSettingsComplete, const FUniqueNetId&, bool, const FString&);` — Delegate used when the query for friends settings has completed @param UserId the id of the user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param ErrorStr string representing the error condition
- L328 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnSetFriendSettingsComplete, const FUniqueNetId&, bool, const FString&);` — Delegate used when the query for friends settings has completed @param UserId the id of the user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param ErrorStr string representing the error condition
- L336 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInviteReceived, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when remote friend sends an invite @param UserId id of the local user that received the invite @param FriendId remote friend id that sent the invite
- L336 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInviteReceived, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when remote friend sends an invite @param UserId id of the local user that received the invite @param FriendId remote friend id that sent the invite
- L337 _typedef_ `typedef FOnInviteReceived::FDelegate FOnInviteReceivedDelegate;`
- L345 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInviteAccepted, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when a remote friend accepts an invite @param UserId id of the local user that had sent the invite @param FriendId friend id that accepted the invite
- L345 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInviteAccepted, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when a remote friend accepts an invite @param UserId id of the local user that had sent the invite @param FriendId friend id that accepted the invite
- L346 _typedef_ `typedef FOnInviteAccepted::FDelegate FOnInviteAcceptedDelegate;`
- L354 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInviteRejected, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when a remote friend rejects an invite @param UserId id of the local user that had sent the invite @param FriendId friend id that rejected the invite
- L354 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInviteRejected, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when a remote friend rejects an invite @param UserId id of the local user that had sent the invite @param FriendId friend id that rejected the invite
- L355 _typedef_ `typedef FOnInviteRejected::FDelegate FOnInviteRejectedDelegate;`
- L363 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInviteAborted, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when a remote friend cancels/aborts an invite @param UserId id of the local user that had received the invite @param FriendId friend id that canceled that invite
- L363 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInviteAborted, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when a remote friend cancels/aborts an invite @param UserId id of the local user that had received the invite @param FriendId friend id that canceled that invite
- L364 _typedef_ `typedef FOnInviteAborted::FDelegate FOnInviteAbortedDelegate;`
- L372 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFriendRemoved, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when a remote friend removes user from friends list @param UserId id of the local user that had the friendship @param FriendId friend id that removed themself from the friendship
- L372 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFriendRemoved, const FUniqueNetId& , const FUniqueNetId& );` — Delegate called when a remote friend removes user from friends list @param UserId id of the local user that had the friendship @param FriendId friend id that removed themself from the friendship
- L373 _typedef_ `typedef FOnFriendRemoved::FDelegate FOnFriendRemovedDelegate;`
- L384 _delegate_ `DECLARE_DELEGATE_FiveParams(FOnSettingsOperationComplete, const FUniqueNetId& , bool , bool , const FFriendSettings& , const FString& );` — Delegate used when the friends settings are read @param UserId id of the local user that requested settings operation @param bWasSuccessful true if the async action completed without error, false if there was an error @param bWasUpdate true if the operation was an "update" operation (vs a passive read) @param Settings settings retrieved @param ErrorStr string representing the error condition
- L384 _prototype_ `DECLARE_DELEGATE_FiveParams(FOnSettingsOperationComplete, const FUniqueNetId& , bool , bool , const FFriendSettings& , const FString& );` — Delegate used when the friends settings are read @param UserId id of the local user that requested settings operation @param bWasSuccessful true if the async action completed without error, false if there was an error @param bWasUpdate true if the operation was an "update" operation (vs a passive read) @param Settings settings retrieved @param ErrorStr string representing the error condition
- L395 _delegate_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FOnFriendSettingsUpdated, const FUniqueNetId& , bool , bool , const FFriendSettings& , const FString& );` — Delegate used when the friends settings are updated @param UserId id of the local user that had their settings updated @param bWasSuccessful true if the async action completed without error, false if there was an error @param bWasUpdate true if the operation was an "update" operation (vs a passive read) @param Settings settings updated @param ErrorStr string representing the error condition
- L395 _prototype_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FOnFriendSettingsUpdated, const FUniqueNetId& , bool , bool , const FFriendSettings& , const FString& );` — Delegate used when the friends settings are updated @param UserId id of the local user that had their settings updated @param bWasSuccessful true if the async action completed without error, false if there was an error @param bWasUpdate true if the operation was an "update" operation (vs a passive read) @param Settings settings updated @param ErrorStr string representing the error condition
- L396 _typedef_ `typedef FOnFriendSettingsUpdated::FDelegate FOnFriendSettingsUpdatedDelegate;`
- L809 _typedef_ `typedef TSharedPtr<IOnlineFriends, ESPMode::ThreadSafe> IOnlineFriendsPtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineFulfillmentInterface.h` (Public)


#### class `IOnlineFulfillment`  
`class IOnlineFulfillment`  
_L10-23_
- desc: IOnlineFulfillment - Interface for redeeming codes.
- L13 _public prototype_ `virtual ~IOnlineFulfillment() = default;`
- L22 _public prototype_ `virtual void RedeemCode(const FUniqueNetId& UserId, const FRedeemCodeRequest& RedeemCodeRequest, const FOnPurchaseRedeemCodeComplete& Delegate) = 0;` — Initiate the checkout process for obtaining offers via code redemption @param UserId user initiating the request @param RedeemCodeRequest info needed for the redeem request @param Delegate completion callback (guaranteed to be called)

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineGameActivityInterface.h` (Public)


#### struct `FOnlineActivityPlayerLocation`  
`struct FOnlineActivityPlayerLocation`  
_L19-33_
- desc: Players location information for the activity service
- L22 _public member_ `FString ZoneId;` — Current reported zone
- L24 _public member_ `FVector Coordinates;` — Coordinates

#### enum `EOnlineActivityOutcome`  
`enum class EOnlineActivityOutcome`  
_L38-46_
- desc: Outcome representation of ending an activity.
- L41 _public enumerator_ `Completed` — Activity has been completed successfully
- L43 _public enumerator_ `Failed` — Activity attempt failed to be completed
- L45 _public enumerator_ `Cancelled` — The activity was cancelled

#### struct `FOnlineActivityTasksToReset`  
`struct FOnlineActivityTasksToReset`  
_L51-55_
- desc: Task ids for in progress and completed activity tasks to be reset
- L53 _public member_ `TArray<FString> InProgressTasks;`
- L54 _public member_ `TArray<FString> CompletedTasks;`

#### struct `FOnlineActivityInformation`  
`struct FOnlineActivityInformation`  
_L60-70_
- desc: Information about a game activity
- L63 _public member_ `FString ActivityId;` — Activity Id
- L65 _public member_ `FString ActivityName;` — Activity Name
- L67 _public member_ `bool bIsGameActivityHidden = false;` — Is the activity hidden
- L69 _public member_ `FString GameMatchId;` — game match id

#### struct `FUsersOnlineActivities`  
`struct FUsersOnlineActivities`  
_L75-81_
- desc: Requested friend's activity information
- L78 _public member_ `FString AccountId;` — The requesting account id
- L80 _public member_ `TArray<FOnlineActivityInformation> Activities;` — Activity information

#### class `IOnlineGameActivity`  
`class IOnlineGameActivity`  
_L157-251_
- desc: IOnlineGameActivity - Interface class for managing a user's activity state
- L160 _public prototype_ `virtual ~IOnlineGameActivity() = default;`
- L170 _public prototype_ `virtual void StartActivity(const FUniqueNetId& LocalUserId, const FString& ActivityId, const FOnlineEventParms& Parms, FOnStartActivityComplete CompletionDelegate) = 0;` — Start an activity @param LocalUserId - Id of the user starting the activity @param ActivityId - Id of the activity to start @param Parms - Additional data to include with the start activity request @param CompletionDelegate - Completion delegate called when StartActivity is complete
- L181 _public prototype_ `virtual void EndActivity(const FUniqueNetId& LocalUserId, const FString& ActivityId, EOnlineActivityOutcome ActivityOutcome, const FOnlineEventParms& Parms, FOnEndActivityComplete CompletionDelegate) = 0;` — End an activity @param LocalUserId - Id of the player stopping the activity @param ActivityId - Task to end by activity ID @param ActivityOutcome - The outcome of the activity (completed, failed, or abandoned) @param Parms - Additional data to include with the stop activity request @param CompletionDelegate - Completion delegate called when the EndActivity call is complete
- L189 _public prototype_ `virtual void ResetAllActiveActivities(const FUniqueNetId& LocalUserId, const FOnResetAllActiveActivitiesComplete& CompletionDelegate) = 0;` — resets all in-progress and completed activities. @param LocalUserId - Id of the player resetting their active activities @param CompletionDelegate - Completion delegate called when ResetAllActiveActivities call is complete
- L200 _public prototype_ `virtual void ResumeActivity(const FUniqueNetId& LocalUserId, const FString& ActivityId, const TOptional<FOnlineActivityTasksToReset>& TasksToReset, const FOnResumeActivityComplete& CompletionDelegate) = 0;` — Resume an activity.  Different from StartActivity in that resume continues from current progress where StartActivity will set progress back to 0 before activating the activity @param LocalUserId - Id of the player resuming the activity @param ActivityId - Task to resume by activity ID @param TasksToReset - Optional argument to specify which in-progress and completed tasks of an activity to reset.  Leaving this empty will reset all tasks @param CompletionDelegate - Completion delegate called when the ResumeActivity call is complete
- L210 _public prototype_ `virtual void SetActivityAvailability(const FUniqueNetId& LocalUserId, const FString& ActivityId, const bool bEnabled, FOnSetActivityAvailabilityComplete CompletionDelegate) = 0;` — Set an activity's availability @param LocalUserId - Id of user setting the activity availability @param ActivityId - Id of the activity to set availability on @param bEnabled - Boolean to set availability of the specified activity @param CompletionDelegate - Completion delegate called when SetActivityAvailability call is complete
- L219 _public prototype_ `virtual void SetActivityPriority(const FUniqueNetId& LocalUserId, const TMap<FString, int32>& PrioritizedActivities, FOnSetActivityPriorityComplete CompletionDelegate) = 0;` — Set the activity priority @param LocalUserId - Id of user setting the activity priority @param PrioritizedActivities - Array of activities with their activity id and priority @param CompletionDelegate - Completion delegate called when SetActivityPriority call is complete
- L229 _public prototype_ `virtual bool QueryActivitiesForUsers(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& UserAccounts, TOptional<int32> MaxUserActivitiesReturned, const FOnQueryUserActivitiesComplete& CompletionDelegate) = 0;` — Query user's activities @param LocalUserId - Id of user requesting activities of other users @param FriendAccountIds - Array of friend ids to get activity information on @param MaxUserActivitiesReturned - Optional maximum number of activities to return per user @param CompletionDelegate - Completion delegate called when QueryUserActivities call is complete
- L238 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnGameActivityActivationRequested, const FUniqueNetId& , const FString& , const FOnlineSessionSearchResult* );` — Called when an activity is requested @param LocalUserId the id of the player this callback is for @param ActivityId the id of the activity for activation @param SessionInfo the session search results for the the activity
- L250 _public prototype_ `virtual void UpdatePlayerLocation(const FUniqueNetId& LocalUserId, TOptional<FOnlineActivityPlayerLocation>& ActivityPlayerLocation) = 0;` — Update player location Note:  The game is expected to call this function periodically. ZoneId/Coordinates are also used when starting and stopping an activity @param LocalUserId - Id of user calling update on the player location @param ActivityPlayerLocation - zone id and player map coordinates (X and Y values)

#### Free symbols / members of external scopes

- L29 _function_ `friend inline bool operator==(const FOnlineActivityPlayerLocation& Location1, const FOnlineActivityPlayerLocation& Location2)` — Equals operator for comparing FOnlineActivityPlayerLocation objects
- L90 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnGameActivityActivationRequested, const FUniqueNetId& , const FString& , const FOnlineSessionSearchResult* );` — Multicast delegate fired when an activity request has happened @param LocalUserId the id of the player this callback is for @param ActivityId the id of the activity for activation @param SessionInfo the session search results for the the activity
- L90 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnGameActivityActivationRequested, const FUniqueNetId& , const FString& , const FOnlineSessionSearchResult* );` — Multicast delegate fired when an activity request has happened @param LocalUserId the id of the player this callback is for @param ActivityId the id of the activity for activation @param SessionInfo the session search results for the the activity
- L91 _typedef_ `typedef FOnGameActivityActivationRequested::FDelegate FOnGameActivityActivationRequestedDelegate;`
- L100 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnStartActivityComplete, const FUniqueNetId& , const FString& , const FOnlineError& );` — Delegate fired when a start activity call has completed @param LocalUserId the id of the player this callback is for @param ActivityId the id of the activity that was started @param Status of whether async action completed successfully or with error
- L100 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnStartActivityComplete, const FUniqueNetId& , const FString& , const FOnlineError& );` — Delegate fired when a start activity call has completed @param LocalUserId the id of the player this callback is for @param ActivityId the id of the activity that was started @param Status of whether async action completed successfully or with error
- L110 _delegate_ `DECLARE_DELEGATE_FourParams(FOnEndActivityComplete, const FUniqueNetId& , const FString& , const EOnlineActivityOutcome& , const FOnlineError& );` — Delegate fired when an end activity call has completed @param LocalUserId the id of the player this callback is for @param ActivityId the id of the activity that was ended @param Outcome the outcome of the activity @param Status of whether async action completed successfully or with error
- L110 _prototype_ `DECLARE_DELEGATE_FourParams(FOnEndActivityComplete, const FUniqueNetId& , const FString& , const EOnlineActivityOutcome& , const FOnlineError& );` — Delegate fired when an end activity call has completed @param LocalUserId the id of the player this callback is for @param ActivityId the id of the activity that was ended @param Outcome the outcome of the activity @param Status of whether async action completed successfully or with error
- L118 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnResetAllActiveActivitiesComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when the reset all active activities call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L118 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnResetAllActiveActivitiesComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when the reset all active activities call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L127 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnResumeActivityComplete, const FUniqueNetId& , const FString& , const FOnlineError& );` — Delegate fired when the resume activity call has completed @param LocalUserId the id of the player this callback is for @param ActivityId the id of the activity that was ended @param Status of whether async action completed successfully or with error
- L127 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnResumeActivityComplete, const FUniqueNetId& , const FString& , const FOnlineError& );` — Delegate fired when the resume activity call has completed @param LocalUserId the id of the player this callback is for @param ActivityId the id of the activity that was ended @param Status of whether async action completed successfully or with error
- L135 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSetActivityAvailabilityComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a set activity availability call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L135 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSetActivityAvailabilityComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a set activity availability call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L143 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSetActivityPriorityComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a set activity priority call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L143 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSetActivityPriorityComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a set activity priority call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L152 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnQueryUserActivitiesComplete, const FUniqueNetId& , const TArray<FUsersOnlineActivities>& , const FOnlineError& );` — Delegate fired when querying remote user activities call has completed @param LocalUserId the id of the player this callback is for @param UserActivities returned activity array for requested users @param Status of whether async action completed successfully or with error
- L152 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnQueryUserActivitiesComplete, const FUniqueNetId& , const TArray<FUsersOnlineActivities>& , const FOnlineError& );` — Delegate fired when querying remote user activities call has completed @param LocalUserId the id of the player this callback is for @param UserActivities returned activity array for requested users @param Status of whether async action completed successfully or with error

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineGameItemStatsInterface.h` (Public)


#### class `IOnlineGameItemStats`  
`class IOnlineGameItemStats`  
_L59-125_
- L62 _public prototype_ `virtual ~IOnlineGameItemStats() = default;`
- L72 _public prototype_ `virtual void ItemUsage(const FUniqueNetId& LocalUserId, const FString& ItemUsedBy, const TArray<FString>& ItemsUsed, FOnItemUsageComplete CompletionDelegate) = 0;` — Updates items used and by who @param LocalUserId -  Id of the player to report the game stat for @param ItemUsedBy - Who the item was used by. This can be LocalUserId, another actor, or blank if no actor used the item. @param ItemsUsed - Array of item IDs that were used @param CompletionDelegate - Item usage completion delegate called when ItemUsage call is complete
- L83 _public prototype_ `virtual void ItemImpact(const FUniqueNetId& LocalUserId, const TArray<FString>& TargetActors, const FString& ImpactInitiatedBy, const TArray<FString>& ItemsUsed, FOnItemImpactComplete CompletionDelegate) = 0;` — Items used to make impact and who the impact target is @param LocalUserId - User Id of the player using the item @param TargetActors - Who was impacted by the item @param ImpactInitiatedBy - Who initiated the impact @param ItemsUsed - A string array of item IDs that were used @param CompletionDelegate - Item impact completion delegate called when ItemImpact call is complete
- L94 _public prototype_ `virtual void ItemMitigation(const FUniqueNetId& LocalUserId, const TArray<FString>& ItemsUsed, const TArray<FString>& ImpactItemsMitigated, const FString& ItemUsedBy, FOnItemMitigationComplete CompletionDelegate) = 0;` — Items the player effectively used to mitigate an item used by the game on the player @param LocalUserId - User Id of the player using the item @param ItemsUsed - Who activated the mitigation @param ImpactItemsMitigated - Array of items that were mitigated @param ItemUsedBy - Array of item IDs that were used @param CompletionDelegate - Item mitigation completion delegate called when ItemMitigation call is complete
- L104 _public prototype_ `virtual void ItemAvailabilityChange(const FUniqueNetId& LocalUserId, const TArray<FString>& AvailableItems, const TArray<FString>& UnavailableItems, FOnItemAvailabilityChangeComplete CompletionDelegate) = 0;` — Updates the lists of available and unavailable items @param LocalUserId - User Id of the player @param AvailableItems - Array of available items @param UnavailableItems - Array of unavailable items @param CompletionDelegate - Item availability change completion delegate called when ItemAvailabilityChange call is complete
- L114 _public prototype_ `virtual void ItemInventoryChange(const FUniqueNetId& LocalUserId, const TArray<FString>& ItemsToAdd, const TArray<FString>& ItemsToRemove, FOnItemInventoryChangeComplete CompletionDelegate) = 0;` — Updates the lists of available and unavailable items in the player's inventory @param LocalUserId - User Id of the player using the item @param ItemsToAdd - Array of available items @param ItemsToRemove - Array of unavailable items @param CompletionDelegate - Item inventory change completion delegate called when ItemInventoryChange call is complete
- L124 _public prototype_ `virtual void ItemLoadoutChange(const FUniqueNetId& LocalUserId, const TArray<FString>& EquippedItems, const TArray<FString>& UnequippedItems, FOnItemLoadoutChangeComplete CompletionDelegate) = 0;` — Updates the loadout of the player's configuration @param LocalUserId - User Id of the player using the item @param EquippedItems - Array of equipped items @param UnequippedItems - Array of unequipped items @param CompletionDelegate - Item loadout change completion delegate called when ItemLoadoutChange call is complete

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnItemUsageComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a item usage call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L17 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnItemUsageComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a item usage call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnItemImpactComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a item impact call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L25 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnItemImpactComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a item impact call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L33 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnItemMitigationComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a item mitigation call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L33 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnItemMitigationComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a item mitigation call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L41 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnItemAvailabilityChangeComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a item availability change call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L41 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnItemAvailabilityChangeComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a item availability change call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L49 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnItemInventoryChangeComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a item inventory change call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L49 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnItemInventoryChangeComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a item inventory change call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L57 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnItemLoadoutChangeComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a item loadout change call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error
- L57 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnItemLoadoutChangeComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when a item loadout change call has completed @param LocalUserId the id of the player this callback is for @param Status of whether async action completed successfully or with error

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineGameMatchesInterface.h` (Public)


#### enum `EMatchGroupType`  
`enum class EMatchGroupType`  
_L17-25_
- desc: Options available for match grouping
- L20 _public enumerator_ `Invalid` — Default option
- L22 _public enumerator_ `Teams` — Team grouping
- L24 _public enumerator_ `NonTeams` — Non team grouping (solos)

#### enum `EUpdateGameMatchStatus`  
`enum class EUpdateGameMatchStatus`  
_L30-40_
- desc: Options available for updating game match status
- L33 _public enumerator_ `Invalid` — Default option
- L35 _public enumerator_ `InProgress` — Used for when the match state should be set to in progress
- L37 _public enumerator_ `Paused` — Indicates the match was put paused
- L39 _public enumerator_ `Aborted` — The match was aborted before completion

#### enum `ELeaveReason`  
`enum class ELeaveReason`  
_L45-55_
- desc: Options available when leaving a game match
- L48 _public enumerator_ `Invalid` — Default option
- L50 _public enumerator_ `Disconnect` — Player has disconnected (IE timeout)
- L52 _public enumerator_ `Finished` — The match was completed
- L54 _public enumerator_ `Quit` — The player quit before the match was completed

#### struct `FLeaveGameMatchPlayer`  
`struct FLeaveGameMatchPlayer`  
_L60-66_
- desc: Data required to leave a game match
- L63 _public member_ `FUniqueNetIdPtr PlayerId;` — Id of the player leaving the match
- L65 _public member_ `ELeaveReason LeaveReason = ELeaveReason::Invalid;` — Reason for leaving the match

#### struct `FJoinGameMatchPlayer`  
`struct FJoinGameMatchPlayer`  
_L71-79_
- desc: Player information needed to join a game match
- L74 _public member_ `FUniqueNetIdPtr PlayerId;` — Player account id
- L76 _public member_ `FString PlayerName;` — Player name
- L78 _public member_ `FString TeamId;` — The id of the team this player will belong to

#### struct `FGameMatchPlayer`  
`struct FGameMatchPlayer`  
_L84-96_
- desc: Player information needed when creating a new game match
- L87 _public member_ `FUniqueNetIdPtr PlayerId;` — Player account id
- L89 _public member_ `FString PlayerName;` — Player name
- L91 _public member_ `FString TeamName;` — Team name this player belongs to
- L93 _public member_ `bool bJoinMatch = false;` — Should the player join the match on creation
- L95 _public member_ `bool bIsNpc = false;` — Is the player an NPC?

#### struct `FGameMatchTeam`  
`struct FGameMatchTeam`  
_L101-109_
- desc: Data needed to construct a team
- L104 _public member_ `FString TeamName;` — Name of the team
- L106 _public member_ `FString TeamId;` — Id of the team
- L108 _public member_ `TArray<FUniqueNetIdRef> TeamMemberIds;` — Members belonging to the team

#### struct `FGameMatchPlayerResult`  
`struct FGameMatchPlayerResult`  
_L114-122_
- desc: Player game match results
- L117 _public member_ `FUniqueNetIdPtr PlayerId;` — Id of the player
- L119 _public member_ `int32 Rank = -1;` — Player's rank
- L121 _public member_ `float Score = 0.0f;` — Player's score

#### struct `FGameMatchTeamResult`  
`struct FGameMatchTeamResult`  
_L127-137_
- desc: Game match results for the team
- L130 _public member_ `FString TeamId;` — Team id
- L132 _public member_ `int32 Rank = -1;` — Team's rank
- L134 _public member_ `double Score = 0.0;` — Team's score
- L136 _public member_ `TArray<FGameMatchPlayerResult> MembersResult;` — The members on the team

#### enum `EMatchCoopResults`  
`enum class EMatchCoopResults`  
_L142-152_
- desc: Coop game match results
- L145 _public enumerator_ `Invalid` — Default option
- L147 _public enumerator_ `Complete` — The players completed the match
- L149 _public enumerator_ `NotComplete` — The match has not yet been completed
- L151 _public enumerator_ `Failed` — The players did not successfully complete the match

#### struct `FGameMatchCompetitiveResults`  
`struct FGameMatchCompetitiveResults`  
_L157-163_
- desc: Results of the competitive game match
- L160 _public member_ `TArray<FGameMatchPlayerResult> PlayersResult;` — Per player results
- L162 _public member_ `TArray<FGameMatchTeamResult> TeamsResult;` — Per team results

#### struct `FGameMatchResult`  
`struct FGameMatchResult`  
_L168-174_
- desc: Overall game match results container to house coop and competitive game match data
- L171 _public member_ `EMatchCoopResults CoopResult = EMatchCoopResults::Invalid;` — Results of a coop game match
- L173 _public member_ `FGameMatchCompetitiveResults CompetitiveResult;` — Results of a competitive game match

#### struct `FGameMatchStatsData`  
`struct FGameMatchStatsData`  
_L179-185_
- desc: Stats container
- L182 _public member_ `FString StatsKey;` — Key
- L184 _public member_ `FVariantData StatsValue;` — Value

#### struct `FGameMatchPlayerStats`  
`struct FGameMatchPlayerStats`  
_L190-196_
- desc: Per player stats
- L193 _public member_ `FUniqueNetIdPtr PlayerId;` — Player id
- L195 _public member_ `TArray<FGameMatchStatsData> PlayerStats;` — The player's stats

#### struct `FGameMatchTeamStats`  
`struct FGameMatchTeamStats`  
_L201-209_
- desc: Complete team stats with players
- L204 _public member_ `FString TeamId;` — Team id
- L206 _public member_ `TArray<FGameMatchStatsData> TeamStats;` — Team stats
- L208 _public member_ `TArray<FGameMatchPlayerStats> TeamMemberStats;` — Team member stats

#### struct `FGameMatchStats`  
`struct FGameMatchStats`  
_L214-220_
- desc: Complete team and player game match stats
- L217 _public member_ `TArray<FGameMatchPlayerStats> PlayerStats;` — Per player game match stats
- L219 _public member_ `TArray<FGameMatchTeamStats> TeamStats;` — Per team game match stats

#### struct `FGameMatchRoster`  
`struct FGameMatchRoster`  
_L225-235_
- desc: Game match roster
- L228 _public member_ `TArray<FGameMatchPlayer> Players;` — Array of players
- L230 _public member_ `TArray<FGameMatchTeam> Teams;` — Array of teams
- L232 _public member_ `FGameMatchResult Results;` — End game match results
- L234 _public member_ `FGameMatchStats Stats;` — Game match stats for players and teams

#### struct `FGameMatchesData`  
`struct FGameMatchesData`  
_L240-251_
- desc: Top most container that contains all game match data
- L243 _public member_ `FString ActivityId;` — Game activity id
- L245 _public member_ `FString ZoneId;` — zone id
- L247 _public member_ `TOptional<int32> InactivityExpirationTimeSeconds;` — The amount of time of no updates before the game match is automatically expired
- L250 _public member_ `FGameMatchRoster MatchesRoster;` — The roster of the match

#### struct `FFinalGameMatchReport`  
`struct FFinalGameMatchReport`  
_L256-268_
- desc: Final match report container.  Holds all information to close out the game match
- L259 _public member_ `EMatchGroupType GroupType = EMatchGroupType::Invalid;` — Group type
- L261 _public member_ `FString MatchType;` — Match type
- L263 _public member_ `bool bLeaveGameFeedback = false;` — Can leave game feedback?
- L265 _public member_ `FGameMatchResult Results;` — Results of the game match
- L267 _public member_ `FGameMatchStats Stats;` — Stats of the game match

#### class `IOnlineGameMatches`  
`class IOnlineGameMatches`  
_L332-395_
- desc: IOnlineGameMatches - Interface class for managing a user's game matches
- L335 _public prototype_ `virtual ~IOnlineGameMatches() = default;`
- L344 _public prototype_ `virtual void CreateGameMatch(const FUniqueNetId& UserId, const FGameMatchesData& MatchesData, const FOnCreateGameMatchComplete& CompletionDelegate) = 0;` — Create a game match @param UserId - Id of the user creating the match @param MatchesData - Game match data required to start a new match @param CompletionDelegate - Completion delegate called when CreateGameMatch is complete
- L354 _public prototype_ `virtual void JoinGameMatch(const FUniqueNetId& UserId, const FString& MatchId, const TArray<FJoinGameMatchPlayer>& GameMatchJoinPlayerData, const FOnJoinGameMatchComplete& CompletionDelegate) = 0;` — Joins a player to an existing match @param UserId - Id of the user updating the match (not to be confused with the id of the player being added to the match) @param MatchId - The id of the match in which the new player will join @param GameMatchJoinPlayerData - Game match data required to add a player to the existing match @param CompletionDelegate - Completion delegate called when JoinGameMatch is complete
- L364 _public prototype_ `virtual void LeaveGameMatch(const FUniqueNetId& UserId, const FString& MatchId, const TArray<FLeaveGameMatchPlayer>& GameMatchLeavePlayerData, const FOnLeaveGameMatchComplete& CompletionDelegate) = 0;` — Removes a player from an existing match @param UserId - Id of the user updating the match (not to be confused with the id of the player being removed from the match) @param MatchId - The id of the match in which the player will be removed from @param GameMatchLeavePlayerData - Game match data required to remove a player from the existing match @param CompletionDelegate - Completion delegate called when LeaveGameMatch is complete
- L374 _public prototype_ `virtual void UpdateGameMatchStatus(const FUniqueNetId& UserId, const FString& MatchId, const EUpdateGameMatchStatus& Status, const FOnGameMatchStatusUpdateComplete& CompletionDelegate) = 0;` — Updates the status of a created match @param UserId - Id of the user updating the match state @param MatchId - The id of the match to update @param Status - The new status to update the match to @param CompletionDelegate - Completion delegate called when UpdateGameMatchStatus is complete
- L384 _public prototype_ `virtual void UpdateGameMatchDetails(const FUniqueNetId& UserId, const FString& MatchId, const FGameMatchRoster& MatchRoster, const FOnUpdateGameMatchDetailsComplete& CompletionDelegate) = 0;` — Updates game match information while match is still in progress @param UserId - Id of the user updating the match information @param MatchId - The id of the match to be updated @param MatchRoster - Information on players and teams that have changed during the match (such as scores, etc) @param CompletionDelegate - Completion delegate called when UpdateGameMatchDetails is complete
- L394 _public prototype_ `virtual void ReportGameMatchResults(const FUniqueNetId& UserId, const FString& MatchId, const FFinalGameMatchReport& FinalReport, const FOnGameMatchReportComplete& CompletionDelegate) = 0;` — Sends final data of the match and closes the match out @param UserId - Id of the user closing out the match @param MatchId - The id of the match to close @param FinalReport - Final data to send with the closing of the match (includes team and player data) @param CompletionDelegate - Completion delegate called when ReportGameMatchResults is complete

#### Free symbols / members of external scopes

- L11 _macro_ `#define GAME_MATCH_TYPE_COOPERATIVE TEXT("Cooperative")`
- L12 _macro_ `#define GAME_MATCH_TYPE_COMPETITIVE TEXT("Competitive")`
- L277 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnCreateGameMatchComplete, const FUniqueNetId& , const FString& , const FOnlineError& );` — Delegate fired when the CreateGameMatch call has completed @param LocalUserId the id of the player this callback is for @param MatchId the id of the match that was created @param Result of whether async action completed successfully or with error
- L277 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnCreateGameMatchComplete, const FUniqueNetId& , const FString& , const FOnlineError& );` — Delegate fired when the CreateGameMatch call has completed @param LocalUserId the id of the player this callback is for @param MatchId the id of the match that was created @param Result of whether async action completed successfully or with error
- L285 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnJoinGameMatchComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when the JoinGameMatch call has completed @param LocalUserId the id of the player this callback is for @param Result of whether async action completed successfully or with error
- L285 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnJoinGameMatchComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when the JoinGameMatch call has completed @param LocalUserId the id of the player this callback is for @param Result of whether async action completed successfully or with error
- L294 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnLeaveGameMatchComplete, const FUniqueNetId& , const TArray<FString>& , const FOnlineError& );` — Delegate fired when the LeaveGameMatch match call has completed @param LocalUserId the id of the player this callback is for @param PlayerNames the player names that left the match @param Result of whether async action completed successfully or with error
- L294 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnLeaveGameMatchComplete, const FUniqueNetId& , const TArray<FString>& , const FOnlineError& );` — Delegate fired when the LeaveGameMatch match call has completed @param LocalUserId the id of the player this callback is for @param PlayerNames the player names that left the match @param Result of whether async action completed successfully or with error
- L303 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnGameMatchStatusUpdateComplete, const FUniqueNetId& , const EUpdateGameMatchStatus& , const FOnlineError& );` — Delegate fired when the UpdateGameMatchStatus call has completed @param LocalUserId the id of the player this callback is for @param Status the new status set when the operation is successful @param Result of whether async action completed successfully or with error
- L303 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnGameMatchStatusUpdateComplete, const FUniqueNetId& , const EUpdateGameMatchStatus& , const FOnlineError& );` — Delegate fired when the UpdateGameMatchStatus call has completed @param LocalUserId the id of the player this callback is for @param Status the new status set when the operation is successful @param Result of whether async action completed successfully or with error
- L311 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGameMatchReportComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when the ReportGameMatchResults call has completed @param LocalUserId the id of the player this callback is for @param Result of whether async action completed successfully or with error
- L311 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnGameMatchReportComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when the ReportGameMatchResults call has completed @param LocalUserId the id of the player this callback is for @param Result of whether async action completed successfully or with error
- L319 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnUpdateGameMatchDetailsComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when the UpdateGameMatchStatus request has completed @param LocalUserId the id of the player this callback is for @param Result of whether async action completed successfully or with error
- L319 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnUpdateGameMatchDetailsComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when the UpdateGameMatchStatus request has completed @param LocalUserId the id of the player this callback is for @param Result of whether async action completed successfully or with error
- L327 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGameMatchFeedbackComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when the game match feedback call has completed @param LocalUserId the id of the player this callback is for @param Result of whether async action completed successfully or with error
- L327 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnGameMatchFeedbackComplete, const FUniqueNetId& , const FOnlineError& );` — Delegate fired when the game match feedback call has completed @param LocalUserId the id of the player this callback is for @param Result of whether async action completed successfully or with error

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineGroupsInterface.h` (Public)


#### struct `FGroupDisplayInfo`  
`struct FGroupDisplayInfo`  
_L12-41_
- desc: Data about the group that is used for display
- L14 _public function_ `FGroupDisplayInfo()`
- L18 _public function_ `FGroupDisplayInfo(const FGroupDisplayInfo& Other) : Name(Other.Name) , Description(Other.Description) , Motto(Other.Motto) , Language(Other.Language) , InviteOnly(Other.InviteOnly)`
- L28 _public member_ `FText Name;` — The human readable name of this guild
- L31 _public member_ `FText Description;` — User entered guild description text
- L34 _public member_ `FText Motto;` — A one-line motto or catch phrase for the group
- L37 _public member_ `FString Language;` — The main language of the team
- L40 _public member_ `bool InviteOnly;` — Is the group PUBLIC (anyone can join) or not?

#### class `IGroupInfo`  
`class IGroupInfo`  
_L46-70_
- desc: This struct describes metadata about a group.
- L51 _public prototype_ `virtual FUniqueNetIdRef GetGroupId() const = 0;` — Get the group
- L54 _public prototype_ `virtual const FString& GetNamespace() const = 0;` — Arbitrary namespace string used to filter group groups in some queries or client side. Usually this would be the game codename
- L57 _public prototype_ `virtual const FGroupDisplayInfo& GetDisplayInfo() const = 0;` — All fields in this struct are group admin/owner entered
- L60 _public prototype_ `virtual FUniqueNetIdRef GetOwner() const = 0;` — GUID of the user account that holds the owner role for this group (will only be one)
- L63 _public prototype_ `virtual uint32 GetSize() const = 0;` — The current size of the group
- L66 _public prototype_ `virtual const FDateTime& GetCreatedAt() const = 0;` — When was this group created
- L69 _public prototype_ `virtual const FDateTime& GetLastUpdated() const = 0;` — When was this group last updated (according to the server)

#### struct `FGroupMember`  
`struct FGroupMember`  
_L75-83_
- desc: An entry in a group member list.
- L77 _public function_ `FUniqueNetIdPtr GetId() const`
- L79 _public member_ `FUniqueNetIdPtr AccountId;`
- L80 _public member_ `bool bAdmin;`
- L81 _public member_ `bool bIsOwner;`
- L82 _public member_ `FDateTime JoinedAt;`

#### struct `FGroupMemberInvite`  
`struct FGroupMemberInvite`  
_L88-95_
- desc: An entry in a pending invite list.
- L90 _public function_ `FUniqueNetIdPtr GetId() const`
- L92 _public member_ `FUniqueNetIdPtr AccountId;`
- L93 _public member_ `FUniqueNetIdPtr GroupHostId;`
- L94 _public member_ `FDateTime SentAt;`

#### struct `FGroupMemberRequest`  
`struct FGroupMemberRequest`  
_L100-106_
- desc: An entry in a pending application list.
- L102 _public function_ `FUniqueNetIdPtr GetId() const`
- L104 _public member_ `FUniqueNetIdPtr AccountId;`
- L105 _public member_ `FDateTime SentAt;`

#### struct `FGroupDenylistEntry`  
`struct FGroupDenylistEntry`  
_L111-117_
- desc: An entry in a group denylist
- L113 _public function_ `FUniqueNetIdPtr GetId() const`
- L115 _public member_ `FUniqueNetIdPtr AccountId;`
- L116 _public member_ `bool bIsApplicant;`

#### struct `FUserMembershipEntry`  
`struct FUserMembershipEntry`  
_L122-149_
- desc: An entry in a group member list.
- L124 _public function_ `FUniqueNetIdPtr GetId() const`
- L127 _public member_ `FUniqueNetIdPtr AccountId;` — AccountId of the member
- L130 _public member_ `bool bAdmin;` — Does the user have admin rights for this group.
- L133 _public member_ `bool bIsOwner;` — Is the user the owner of this group.
- L136 _public member_ `FDateTime JoinedAt;` — When did the user join this group
- L139 _public member_ `FString Namespace;` — Arbitrary namespace string used to filter group groups in some queries or client side. Usually this would be the game codename
- L142 _public member_ `FUniqueNetIdPtr GroupId;` — GroupId
- L145 _public member_ `FText Name;` — The display name of the group
- L148 _public member_ `FUniqueNetIdPtr Owner;` — AccountId of the group owner

#### struct `FApplicationEntry`  
`struct FApplicationEntry`  
_L154-172_
- desc: An entry in the list of user pending membership applications.
- L156 _public function_ `FUniqueNetIdPtr GetId() const`
- L159 _public member_ `FUniqueNetIdPtr AccountId;` — AccountId of the user who applied for group membership.
- L162 _public member_ `FDateTime SentAt;` — Timestamp of when the application was sent.
- L165 _public member_ `FUniqueNetIdPtr GroupId;` — GroupId of the group for which membership was applied.
- L168 _public member_ `FString Namespace;` — Namespace in which the application exists.
- L171 _public member_ `FText Name;` — Name of the group.

#### struct `FInvitationEntry`  
`struct FInvitationEntry`  
_L177-198_
- desc: An entry in a user's list of groups to which they are invited.
- L179 _public function_ `FUniqueNetIdPtr GetId() const`
- L182 _public member_ `FUniqueNetIdPtr AccountId;` — AccountId of the user invited to group membership.
- L185 _public member_ `FUniqueNetIdPtr GroupHostId;` — AccountId of the group user that did the inviting.
- L188 _public member_ `FDateTime SentAt;` — Timestamp of when the application was sent.
- L191 _public member_ `FUniqueNetIdPtr GroupId;` — The GroupId for the group.
- L194 _public member_ `FString Namespace;` — The Namespace for the invitation.
- L197 _public member_ `FText Name;` — The Name of the group.

#### struct `TGroupConfigEntry`  
`template <typename EntryType> struct TGroupConfigEntry`  
_L201-213_
- L203 _public function_ `FUniqueNetIdPtr GetId() const`
- L206 _public member_ `FUniqueNetIdPtr AccountId;` — Context AccountId.
- L209 _public member_ `FString Key;` — The max number of members in any group.
- L212 _public member_ `EntryType Value;` — The max number of groups in which a user may be a member.

#### struct `IGroupUserCollection`  
`template <typename EntryType> struct IGroupUserCollection`  
_L219-225_
- L221 _public prototype_ `virtual const EntryType* GetEntry(const FUniqueNetId& EntryId) const =0;`
- L222 _public prototype_ `virtual EntryType* GetEntry(const FUniqueNetId& EntryId) =0;`
- L223 _public prototype_ `virtual FUniqueNetIdRef GetCollectionId() const =0;`
- L224 _public prototype_ `virtual void CopyEntries(TArray<EntryType>& Out) const =0;`

#### struct `FGroupSearchOptions`  
`struct FGroupSearchOptions`  
_L275-291_
- desc: Group search options
- L278 _public member_ `FString Query;` — case insensitive group name keyword for search group, should itself be a valid team name
- L281 _public member_ `TOptional<FString> Language;` — language filter
- L284 _public member_ `TArray<FString> Tags;` — tags filter
- L287 _public member_ `TOptional<uint32> MinSize;` — minimal group size threshold - a size group should have to show up in results
- L290 _public member_ `TOptional<FPagedQuery> Paging;` — Offset and size for the query.

#### enum `EGroupSortOrder`  
`enum class EGroupSortOrder`  
_L293-299_
- L295 _public enumerator_ `CreatedDescending`
- L296 _public enumerator_ `SizeDescending`
- L297 _public enumerator_ `NameAscending`
- L298 _public enumerator_ `NameDescending`

#### struct `FGroupsResult`  
`struct FGroupsResult`  
_L304-325_
- desc: Structure to encapsulate the result of a call to the server. This only contains enough information to check for errors
- L306 _public member_ `int32 HttpStatus;`
- L307 _public member_ `FUniqueNetIdPtr PrimaryId;`
- L308 _public member_ `FString ErrorContent;`
- L310 _public function_ `inline bool DidSucceed() const`
- L312 _public function_ `FGroupsResult(int32 InHttpStatus = 0, FUniqueNetIdPtr InPrimaryId = nullptr) : HttpStatus(InHttpStatus) , PrimaryId(InPrimaryId) , ErrorContent()`
- L319 _public function_ `FGroupsResult(int32 InHttpStatus, const FString& Error, FUniqueNetIdPtr InPrimaryId = nullptr) : HttpStatus(InHttpStatus) , PrimaryId(InPrimaryId) , ErrorContent(Error)`

#### struct `FFindGroupsResult`  
`struct FFindGroupsResult`  
_L338-349_
- desc: Specialized result for FindGroups
- L340 _public member_ `bool bDidSucceed;`
- L341 _public member_ `TArray< TSharedPtr<const IGroupInfo> > MatchingGroups;`
- L342 _public member_ `FPagedQuery Paging;`
- L343 _public member_ `FString ErrorContent;`
- L345 _public function_ `FFindGroupsResult() : bDidSucceed(false)`

#### class `IOnlineGroups`  
`class IOnlineGroups`  
_L356-854_
- desc: Interface definition for the online teams (groups) service Groups are collections of users with an owner and a set of administrators
- L366 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGroupUpdated, const FUniqueNetId&);` — Delegate fired when a group is updated. We only receive notifications for groups for which one of the logged-in players is a member. @param GroupId The GUID of the group.
- L367 _public member_ `FOnGroupUpdated OnGroupUpdated;`
- L381 _public prototype_ `virtual void CreateGroup(const FUniqueNetId& ContextUserId, const FGroupDisplayInfo& GroupInfo, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Create a new group using the specified GroupInfo. FGroupsResult::GroupId can be used to identify the newly created group once the callback executes (FGroupsResult being a param to the callback). @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupInfo The display info to use for the new group. Name, description, etc @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L391 _public prototype_ `virtual void FindGroups(const FUniqueNetId& ContextUserId, const FGroupSearchOptions& SearchOptions, const FOnFindGroupsCompleted& OnCompleted) = 0;` — Find all groups matching the specified search string @param ContextUserId The ID of the user whose credentials are being used to make this call @param SearchOptions A collections of search parameters passed to the search. @param OnCompleted Callback delegate which will receive the results of the search. Any GroupInfo from the search will also be available from GetCachedGroupInfo.
- L403 _public prototype_ `virtual void QueryGroupInfo(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Ask the server for GroupInfo corresponding to the provided group ID. If this completes successfully, you can call GetCachedGroupInfo to get the full group information. Even if the group info is currently cached, this function will contact the server (ostensibly to refresh the cache). @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID to query @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L415 _public prototype_ `virtual void QueryGroupNameExist(const FUniqueNetId& ContextUserId, const FString& GroupName, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Ask the server if the given group name currently exists. If it completes successfully, you can call GetCachedGroupNameExist to get the result. Even if the result is currently cached, this function will contact the server (ostensibly to refresh the cache). @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupName The group name to query @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L427 _public prototype_ `virtual TSharedPtr<const IGroupInfo> GetCachedGroupInfo(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId) = 0;` — Get the group info for a group that has been previously queried. The shared pointer will be empty if the group has not been successfully queried (or if it was purged from the cache). From time to time, the cache may be cleaned up. Keep a shared pointer to groups you care about or be willing to re-query. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @return Shared pointer to the cached group info structure if one exists.
- L439 _public prototype_ `virtual void JoinGroup(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Submit a request to join the specified group. This is done on behalf of the context user (provided when you request this IOnlineGroups interface) and also updates the their cached membership info. You can call GetCachedUserMembership afterwards to see if they are a full member or petitioner. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L451 _public prototype_ `virtual void LeaveGroup(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Tells the server to remove the context user from the specified group. Should always result in the user's role for that group becoming Unaffiliated. Owners cannot leave their group, use TransferGroup (followed by LeaveGroup) or DeleteGroup instead. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L461 _public prototype_ `virtual void CancelRequest(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Cancel pending request to join the given group. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L473 _public prototype_ `virtual void AcceptInvite(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Accept a pending invite to join a group. This is done on behalf of the context user (provided when you request this IOnlineGroups interface) and also updates the their cached membership info. You can call GetCachedUserMembership afterwards to see if they are a full member or petitioner. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L485 _public prototype_ `virtual void DeclineInvite(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Decline a pending invite to join a group. This is done on behalf of the context user (provided when you request this IOnlineGroups interface) and also updates the their cached membership info. You can call GetCachedUserMembership afterwards to see if they are a full member or petitioner. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L497 _public prototype_ `virtual void QueryGroupRoster(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Get the list of members for a group and their role info. When the OnCompleted callback fires, if it succeeded you can use GetCachedGroupRoster to retrieve the membership information. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L508 _public prototype_ `virtual TSharedPtr<const IGroupRoster> GetCachedGroupRoster(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId) = 0;` — Get the cached Roster (membership) information for a group. If the information is not cached locally, call QueryGroupRoster to request it from the server. If the context user is a member of this group, the cached roster information will include petitioners and invitees, otherwise it will not. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @return Shared pointer to the cached roster structure if one exists
- L519 _public prototype_ `virtual void QueryUserMembership(const FUniqueNetId& ContextUserId, const FUniqueNetId& UserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Queries the server for updated membership information for a particular user. This retrieves which groups they are members of. If the callback reports success, use GetCachedUserMembership to retrieve details. @param ContextUserId The ID of the user whose credentials are being used to make this call @param UserId The user to query for membership information. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L532 _public prototype_ `virtual TSharedPtr<const IUserMembership> GetCachedUserMembership(const FUniqueNetId& ContextUserId, const FUniqueNetId& UserId) = 0;` — Get cached user membership information (if it exists). This retrieves which groups they are members of. If UserId is the ID of the context user, then this list will include groups to which the user has been invited (use JoinGroup to accept, LeaveGroup to decline) or groups they have petitioned but haven't received a response for yet. @param ContextUserId The ID of the user whose credentials are being used to make this call @param UserId The ID of the user to query. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L543 _public prototype_ `virtual void QueryOutgoingApplications(const FUniqueNetId& ContextUserId, const FUniqueNetId& UserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Queries the server for a list of groups to which the user has applied for membership. If the callback reports success, use GetCachedApplications to retrieve details. @param ContextUserId The ID of the user whose credentials are being used to make this call @param UserId The user to query for pending membership application information. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L554 _public prototype_ `virtual TSharedPtr<const IApplications> GetCachedApplications(const FUniqueNetId& ContextUserId, const FUniqueNetId& UserId) = 0;` — Get cached pending application information (if it exists). This retrieves a list of membership applications that the user has created (outgoing) or to which the user can respond as admin (incoming). @param ContextUserId The ID of the user whose credentials are being used to make this call @param UserId The ID of the user to query. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L565 _public prototype_ `virtual void QueryOutgoingInvitations(const FUniqueNetId& ContextUserId, const FUniqueNetId& UserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Queries the server for a list of group invitations the user has sent. If the callback reports success, use GetCachedApplications to retrieve details. @param ContextUserId The ID of the user whose credentials are being used to make this call @param UserId The user to query for pending membership invitation information. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L576 _public prototype_ `virtual void QueryIncomingInvitations(const FUniqueNetId& ContextUserId, const FUniqueNetId& UserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Queries the server for a list of groups to which the user has been invited. If the callback reports success, use GetCachedApplications to retrieve details. @param ContextUserId The ID of the user whose credentials are being used to make this call @param UserId The user to query for pending membership invitation information. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L587 _public prototype_ `virtual TSharedPtr<const IInvitations> GetCachedInvitations(const FUniqueNetId& ContextUserId, const FUniqueNetId& UserId) = 0;` — Get cached pending invitation information (if it exists). This retrieves a list of membership invitations that the user's admin clans have created (outgoing) or to which the user can respond (incoming). @param ContextUserId The ID of the user whose credentials are being used to make this call @param UserId The ID of the user to query. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L601 _public prototype_ `virtual void UpdateGroupInfo(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FGroupDisplayInfo& GroupInfo, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Update the user specified fields of the group such as name, description, etc. This call may fail if the name changes and the new name is already in use within this namespace. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param GroupInfo The new group display info structure. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L612 _public prototype_ `virtual void AcceptUser(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FUniqueNetId& UserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Accept a user request to join the group. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param UserId The user to add to the group. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L623 _public prototype_ `virtual void DeclineUser(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FUniqueNetId& UserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Decline a user request to join the group. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param UserId The user to add to the group. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L635 _public prototype_ `virtual void InviteUser(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FUniqueNetId& UserId, bool bAllowBlocked, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Invite a user to join the specified group. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param UserId The user to add to the group. @param bAllowBlocked If true, if the user is on the group's denylist, the user will be unblocked before creating the invite. Otherwise adding a blocked user will fail. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L646 _public function_ `virtual void InviteUser(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FUniqueNetId& UserId, const FOnGroupsRequestCompleted& OnCompleted)` — Invite a user to join the specified group. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param UserId The user to add to the group. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L660 _public prototype_ `virtual void CancelInvite(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FUniqueNetId& UserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Cancels an invitation to join the group. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param UserId The user whose invite to remove. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L671 _public prototype_ `virtual void RemoveUser(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FUniqueNetId& UserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Kick a user from the group OR decline a petition OR rescind an invitation (success always results in the user's role becoming Unaffiliated). @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param UserId The user to remove from the group. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L682 _public prototype_ `virtual void PromoteUser(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FUniqueNetId& UserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Promote a Member to an Admin within the specified group. Fails if the user's role is not Member. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param UserId The member to promote. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L693 _public prototype_ `virtual void DemoteUser(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FUniqueNetId& UserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Demote an Admin to a Member within the specified group. Fails if the user's role is not Admin (Owner != Admin). @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param UserId The user to demote to regular member. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L708 _public prototype_ `virtual void BlockUser(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FUniqueNetId& UserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Ban a user from joining the specified group. Any user but team owner can be denylisted including member, invitee, applicant and/or any other user unrelated to the team. Blocking follows "ignore" logic: blocked users shouldn't know for sure that they've been blocked. Blocked user will still be able to apply for membership and cancel pending application even while blocked. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param UserId The user to denylist. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L719 _public prototype_ `virtual void UnblockUser(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FUniqueNetId& UserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Remove a user from the group's denylist list. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param UserId The user to allow back into the group. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L731 _public prototype_ `virtual void QueryGroupInvites(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Get the list of outstanding invites to a group. When the OnCompleted callback fires, if it succeeded you can use GetCachedGroupInvites to retrieve the membership information. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L741 _public prototype_ `virtual TSharedPtr<const IGroupInvites> GetCachedGroupInvites(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId) = 0;` — Get the cached list of outstanding invites to a group. If the information is not cached locally, call QueryGroupInvites to request it from the server. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @return Shared pointer to the cached roster structure if one exists
- L753 _public prototype_ `virtual void QueryGroupRequests(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Get the list of users requesting to becoming members of a group. When the OnCompleted callback fires, if it succeeded you can use GetCachedGroupRequests to retrieve the membership information. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L763 _public prototype_ `virtual TSharedPtr<const IGroupRequests> GetCachedGroupRequests(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId) = 0;` — Get the cached list of  users requesting to becoming members of a group. If the information is not cached locally, call QueryGroupRequests to request it from the server. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @return Shared pointer to the cached roster structure if one exists
- L775 _public prototype_ `virtual void QueryGroupDenylist(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Get the list of users banned from this group. When the OnCompleted callback fires, if it succeeded you can use GetCachedGroupDenylist to retrieve the information. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L785 _public prototype_ `virtual TSharedPtr<const IGroupDenylist> GetCachedGroupDenylist(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId) = 0;` — Get the cached list of users banned from this group. If the information is not cached locally, call QueryGroupDenylist to request it from the server. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @return Shared pointer to the cached roster structure if one exists
- L796 _public prototype_ `virtual void QueryIncomingApplications(const FUniqueNetId& ContextUserId, const FUniqueNetId& UserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Queries the server for a list of membership applications that UserId can process (accept, reject, or block) as group admin. If the callback reports success, use GetCachedApplications to retrieve details. @param ContextUserId The ID of the user whose credentials are being used to make this call @param UserId The user to query for pending group membership application information. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L803 _public prototype_ `virtual void QueryConfigHeadcount(const FUniqueNetId& ContextUserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Queries the system configuration for system-wide group max membership headcount.
- L808 _public prototype_ `virtual void QueryConfigMembership(const FUniqueNetId& ContextUserId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Queries the system configuration for system-wide user max membership count.
- L814 _public prototype_ `virtual TSharedPtr<const FGroupConfigEntryInt> GetCachedConfigInt(const FString& Key) = 0;` — Get the result of a previous configuration query. Only the member queried for will be valid.
- L820 _public prototype_ `virtual TSharedPtr<const FGroupConfigEntryBool> GetCachedConfigBool(const FString& Key) = 0;` — Get the result of a previous configuration query. Only the member queried for will be valid.
- L835 _public prototype_ `virtual void TransferGroup(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FUniqueNetId& NewOwnerId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Promote an existing Admin to be the new Owner and simultaneously demotes the context user to Admin. Fails if the new owner is not currently an Admin of the group. Also fails if the new owner cannot own the group (due to owning too many other groups, as determined by the namespace config, perhaps). @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param UserId The user who should become the new group owner. This user must already be an Admin or the call fails. @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L845 _public prototype_ `virtual void DeleteGroup(const FUniqueNetId& ContextUserId, const FUniqueNetId& GroupId, const FOnGroupsRequestCompleted& OnCompleted) = 0;` — Delete a group entirely. @param ContextUserId The ID of the user whose credentials are being used to make this call @param GroupId The group's globally unique ID @param OnCompleted This callback is invoked after contacting the server. It is guaranteed to occur (regardless of success/fail) and will not be called before this function returns.
- L848 _protected function_ `IOnlineGroups()`
- L850 _public prototype_ `virtual ~IOnlineGroups() = default;`
- L852 _public prototype_ `virtual void SetNamespace(const FString& Ns) = 0;`
- L853 _public prototype_ `virtual const FString& GetNamespace() const = 0;`

#### Free symbols / members of external scopes

- L215 _typedef_ `typedef TGroupConfigEntry<int32> FGroupConfigEntryInt;`
- L216 _typedef_ `typedef TGroupConfigEntry<bool> FGroupConfigEntryBool;`
- L230 _typedef_ `typedef IGroupUserCollection<FGroupMember> IGroupRoster;` — A structure for caching a list of people in the group and their roles
- L235 _typedef_ `typedef IGroupUserCollection<FGroupMemberInvite> IGroupInvites;` — A structure for caching a list of people that have been invited to join a group
- L240 _typedef_ `typedef IGroupUserCollection<FGroupMemberRequest> IGroupRequests;` — A structure for caching a list of people who have requested to join the group
- L245 _typedef_ `typedef IGroupUserCollection<FGroupDenylistEntry> IGroupDenylist;` — A structure for caching a list of people who have been banned from a group
- L250 _typedef_ `typedef IGroupUserCollection<FUserMembershipEntry> IUserMembership;` — What groups does a particular user currently belong to and what roles do they fill
- L255 _typedef_ `typedef IGroupUserCollection<FApplicationEntry> IApplications;` — A list of pending membership applications for a given user.
- L260 _typedef_ `typedef IGroupUserCollection<FInvitationEntry> IInvitations;` — A list of pending membership invitations for a given user.
- L265 _typedef_ `typedef TMap<FString, TSharedPtr<const FGroupConfigEntryInt>> IGroupConfigInt;` — Configuration key->values (int)
- L270 _typedef_ `typedef TMap<FString, TSharedPtr<const FGroupConfigEntryBool>> IGroupConfigBool;` — Configuration key->values (boolean)
- L333 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGroupsRequestCompleted, FGroupsResult);` — Generic delegate used for when an asynchronous query completes @param Result A structure containing information about whether the query succeeded or failed. Use the GetCached* related function once this delegate has been called to retrieve the result payload.
- L333 _prototype_ `DECLARE_DELEGATE_OneParam(FOnGroupsRequestCompleted, FGroupsResult);` — Generic delegate used for when an asynchronous query completes @param Result A structure containing information about whether the query succeeded or failed. Use the GetCached* related function once this delegate has been called to retrieve the result payload.
- L350 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFindGroupsCompleted, FFindGroupsResult);`
- L350 _prototype_ `DECLARE_DELEGATE_OneParam(FOnFindGroupsCompleted, FFindGroupsResult);`
- L366 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGroupUpdated, const FUniqueNetId&);` — Delegate fired when a group is updated. We only receive notifications for groups for which one of the logged-in players is a member. @param GroupId The GUID of the group.
- L856 _typedef_ `typedef TSharedPtr<IOnlineGroups, ESPMode::ThreadSafe> IOnlineGroupsPtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineIdentityInterface.h` (Public)


#### class `FOnlineAccountCredentials`  
`class FOnlineAccountCredentials`  
_L27-68_
- desc: Account credentials needed to sign in to an online service
- L32 _public member_ `FString Type;` — Type of account. Needed to identity the auth method to use (epic, internal, facebook, etc)
- L34 _public member_ `FString Id;` — Id of the user logging in (email, display name, facebook id, etc)
- L36 _public member_ `FString Token;` — Credentials of the user logging in (password or auth token)
- L41 _public function_ `bool operator==(const FOnlineAccountCredentials& Other) const` — Equality operator
- L50 _public function_ `FOnlineAccountCredentials(const FString& InType, const FString& InId, const FString& InToken) : Type(InType), Id(InId), Token(InToken)` — Constructor
- L60 _public function_ `FOnlineAccountCredentials()` — Constructor
- L64 _public function_ `FString ToDebugString() const`

#### enum `EUserPrivileges::Type`  
`enum Type`  
_L72-84_
- L75 _public enumerator_ `CanPlay` — Whether the user can play at all, online or offline - may be age restricted
- L77 _public enumerator_ `CanPlayOnline` — Whether the user can play in online modes
- L79 _public enumerator_ `CanCommunicateOnline` — Whether the user can use voice and text chat
- L81 _public enumerator_ `CanUseUserGeneratedContent` — Whether the user can use content generated by other users
- L83 _public enumerator_ `CanUserCrossPlay` — Whether the user can ever participate in cross-play due to age restrictions

#### enum `EShowPrivilegeResolveUI`  
`enum class EShowPrivilegeResolveUI : uint8`  
_L88-96_
- desc: Whether to show UI to resolve the privilege if there is no access when GetUserPrivilege
- L91 _public enumerator_ `Default` — Use default behavior, which preserved the behaviour prior to the introduction of this.
- L93 _public enumerator_ `Show` — Show UI to resolve privilege
- L95 _public enumerator_ `NotShow` — Not show UI to resolve privilege

#### struct `FControllerPairingChangedUserInfo`  
`struct FControllerPairingChangedUserInfo`  
_L102-121_
- desc: This struct will be broadcast with the FOnControllerPairingChanged event. This event is not broadcast on all OnlineIdentity platforms. There will be a struct for the previous user on the controller and for the new user on the controller.
- L108 _public member_ `const FUniqueNetId& User;` — One of the users involved (the one who had the controller or the one who now has the controller). This may be nobody (e.g. if the controller was assigned to a User, and now is assigned to nobody)
- L113 _public member_ `int32 ControllersRemaining;` — The number of controllers now associated with User. If User is nobody, this number will be 0
- L115 _public function_ `FControllerPairingChangedUserInfo(const FUniqueNetId& InUser, int32 InControllersRemaining) : User(InUser) , ControllersRemaining(InControllersRemaining)`

#### struct `FExternalAuthToken`  
`struct FExternalAuthToken`  
_L201-220_
- desc: A struct for the external account token in case we need per platform fields
- L203 _public member_ `TArray<uint8> TokenData;`
- L204 _public member_ `FString TokenString;`
- L206 _public function_ `inline bool HasTokenData() const`
- L211 _public function_ `inline bool HasTokenString() const`
- L216 _public function_ `inline bool IsValid() const`

#### class `IOnlineIdentity`  
`class IOnlineIdentity`  
_L225-550_
- desc: Interface for registration/authentication of user identities
- L229 _protected function_ `IOnlineIdentity()`
- L261 _public prototype_ `virtual ~IOnlineIdentity() = default;`
- L268 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnLoginChanged, int32 );` — Delegate called when a player logs in/out @param LocalUserNum the player that logged in/out
- L278 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_THREE_PARAM(MAX_LOCAL_PLAYERS, OnLoginStatusChanged, ELoginStatus::Type , ELoginStatus::Type , const FUniqueNetId& );` — Delegate called when a player's login status changes but doesn't change identity @param LocalUserNum the controller number of the associated user @param OldStatus the previous status of the user @param NewStatus the new login status for the user @param NewId the new id to associate with the user
- L286 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnAuthAboutToExpire, int32 );` — Delegate called when an auth session is about to expire and a new auth token is needed. The code bound to it is expected to respond by getting a new auth token and use it to re-call Login to refresh auth and keep the player logged in. param LocalUserNum the controller number of the user whose auth is about to expire
- L295 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnControllerPairingChanged, int , FControllerPairingChangedUserInfo , FControllerPairingChangedUserInfo );` — Delegate called when a controller-user pairing changes @param LocalUserNum the controller number whose pairing changed @param PreviousUser the previous user associated with the controller @param NewUser the new user associated with the controller
- L306 _public prototype_ `virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) = 0;` — Login/Authenticate with user credentials. Will call OnLoginComplete() delegate when async task completes @param LocalUserNum the controller number of the associated user @param AccountCredentials user account credentials needed to sign in to the online service @return true if login task was started
- L316 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_THREE_PARAM(MAX_LOCAL_PLAYERS, OnLoginComplete, bool , const FUniqueNetId& , const FString& );` — Called when user account login has completed after calling Login() or AutoLogin() @param LocalUserNum the controller number of the associated user @param bWasSuccessful true if server was contacted and a valid result received @param UserId the user id received from the server on successful login @param Error string representing the error condition
- L326 _public prototype_ `virtual bool Logout(int32 LocalUserNum) = 0;` — Signs the player out of the online service Will call OnLogoutComplete() delegate when async task completes @param LocalUserNum the controller number of the associated user @return true if logout task was started
- L334 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_ONE_PARAM(MAX_LOCAL_PLAYERS, OnLogoutComplete, bool );` — Delegate used in notifying the that manual logout completed @param LocalUserNum the controller number of the associated user @param bWasSuccessful whether the async call completed properly or not
- L341 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnLoginFlowLogout, const TArray<FString>& );` — Delegate called when the online subsystem requires the login flow to logout and cleanup @param LoginDomains login domains to be cleaned up
- L353 _public prototype_ `virtual bool AutoLogin(int32 LocalUserNum) = 0;` — Logs the player into the online service using parameters passed on the command line. Expects -AUTH_LOGIN=<UserName> -AUTH_PASSWORD=<password>. If either are missing, the function returns false and doesn't start the login process @param LocalUserNum the controller number of the associated user @return true if the async call started ok, false otherwise
- L362 _public prototype_ `virtual TSharedPtr<FUserOnlineAccount> GetUserAccount(const FUniqueNetId& UserId) const = 0;` — Obtain online account info for a user that has been registered @param UserId user to search for @return info about the user if found, NULL otherwise
- L369 _public prototype_ `virtual TArray<TSharedPtr<FUserOnlineAccount> > GetAllUserAccounts() const = 0;` — Obtain list of all known/registered user accounts @return info about the users if found, NULL otherwise
- L378 _public prototype_ `virtual FUniqueNetIdPtr GetUniquePlayerId(int32 LocalUserNum) const = 0;` — Gets the platform specific unique id for the specified player @param LocalUserNum the controller number of the associated user @return Valid player id object if the call succeeded, NULL otherwise
- L387 _public function_ `virtual FUniqueNetIdPtr GetSponsorUniquePlayerId(int32 LocalUserNum) const` — Gets the platform specific unique id for the sponsor of the specified player @param LocalUserNum the controller number of the associated user @return Valid player id object if the sponsor exists, NULL otherwise
- L397 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(uint8* Bytes, int32 Size) = 0;` — Create a unique id from binary data (used during replication) @param Bytes opaque data from appropriate platform @param Size size of opaque data @return UniqueId from the given data, NULL otherwise
- L406 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(const FString& Str) = 0;` — Create a unique id from string @param Str string holding textual representation of an Id @return UniqueId from the given data, NULL otherwise
- L415 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(int32 LocalUserNum) const = 0;` — Fetches the login status for a given player @param LocalUserNum the controller number of the associated user @return the enum value of their status
- L424 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(const FUniqueNetId& UserId) const = 0;` — Fetches the login status for a given player @param UserId the unique net id of the associated user @return the enum value of their status
- L434 _public prototype_ `virtual FString GetPlayerNickname(int32 LocalUserNum) const = 0;` — @todo - move to user interface
- L444 _public prototype_ `virtual FString GetPlayerNickname(const FUniqueNetId& UserId) const = 0;` — @todo - move to user interface
- L454 _public prototype_ `virtual FString GetAuthToken(int32 LocalUserNum) const = 0;` — @todo - remove and use GetUserAccount instead
- L462 _public prototype_ `virtual void RevokeAuthToken(const FUniqueNetId& LocalUserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate) = 0;` — Revoke the user's registered auth token. @param LocalUserId the unique net of the associated user @param Delegate delegate to execute when the async task completes
- L474 _public function_ `virtual void ClearCachedAuthToken(const FUniqueNetId& UserId)` — Clear an auth token associated with the user, if one was cached. If an auth token is obtained for some other purpose than user account login, it would be ignored an replaced with another when an actual login attempt is made, wasting the previously obtained one.  Caching avoids that potential waste, but must be manually cleared client-side when the login completes due to the remote side has consuming it. @param UserId the unique net of the associated user
- L483 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnGetLinkedAccountAuthTokenCompleteDelegate, int32 , bool , const FExternalAuthToken& );` — Delegate executed when the user's auth ticket has arrived @param LocalUserNum the controller number of the associated user @param bWasSuccessful whether the ticket was successfully retrieved or not @param AuthToken the token to use with linked auth
- L492 _public function_ `virtual void GetLinkedAccountAuthToken(int32 LocalUserNum, const FString& TokenType, const FOnGetLinkedAccountAuthTokenCompleteDelegate& Delegate) const` — Gets a user's platform specific authentication ticket used to sign into linked account(s) @param LocalUserNum the controller number of the associated user @param TokenType the platform specific token type you are requesting. @param Delegate delegate to execute when the async task completes
- L505 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnGetUserPrivilegeCompleteDelegate, const FUniqueNetId& , EUserPrivileges::Type , uint32 );` — Delegate executed when we get a user privilege result. @param LocalUserId The unique id of the user who was queried @param Privilege the privilege that was queried @param PrivilegeResult bitwise OR of any privilege failures. 0 is success.
- L515 _public prototype_ `virtual void GetUserPrivilege(const FUniqueNetId& LocalUserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate, EShowPrivilegeResolveUI ShowResolveUI = EShowPrivilegeResolveUI::Default) = 0;` — Gets the status of a user's privilege. @param LocalUserId the unique id of the user to query @param Privilege the privilege you want to know about @param Delegate delegate to execute when the async task completes @param ShowResolveUI whether to show UI to resolve if user don't have the privilege
- L524 _public prototype_ `virtual FPlatformUserId GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& UniqueNetId) const = 0;` — Converts from an online unique id to a PlatformUserId used by application code @param UniqueNetId The unique id to look up @return The corresponding id or PLATFORMID_NONE if not found
- L533 _public prototype_ `virtual FPlatformUserId GetPlatformUserIdFromLocalUserNum(int32 LocalUserNum) const;` — Converts from a local user num used by the online system to a PlatformUserId used by application code @param LocalUserNum the controller number of the associated user @return The corresponding id or PLATFORMID_NONE if invalid
- L542 _public prototype_ `virtual int32 GetLocalUserNumFromPlatformUserId(FPlatformUserId PlatformUserId) const;` — Converts from a PlatformUserId used by application code to a local user num used by the online system @param PlatformUserId The application-level platform user id @return The corresponding user number of INDEX_NONE if invalid
- L549 _public prototype_ `virtual FString GetAuthType() const = 0;` — Get the auth type associated with accounts for this platform @return The auth type associated with accounts for this platform

#### enum `IOnlineIdentity::EPrivilegeResults`  
`enum class EPrivilegeResults : uint32`  
_L233-259_
- L236 _public enumerator_ `NoFailures = 0` — The user has the requested privilege
- L238 _public enumerator_ `RequiredPatchAvailable = 1 << 0` — Patch required before the user can use the privilege
- L240 _public enumerator_ `RequiredSystemUpdate = 1 << 1` — System update required before the user can use the privilege
- L242 _public enumerator_ `AgeRestrictionFailure = 1 << 2` — Parental control failure usually
- L244 _public enumerator_ `AccountTypeFailure = 1 << 3` — XboxLive Gold / PSPlus required but not available
- L246 _public enumerator_ `UserNotFound = 1 << 4` — Invalid user
- L248 _public enumerator_ `UserNotLoggedIn = 1 << 5` — User must be logged in
- L250 _public enumerator_ `ChatRestriction = 1 << 6` — User restricted from chat
- L252 _public enumerator_ `UGCRestriction = 1 << 7` — User restricted from User Generated Content
- L254 _public enumerator_ `GenericFailure = 1 << 8` — Platform failed for unknown reason and handles its own dialogs
- L256 _public enumerator_ `OnlinePlayRestricted = 1 << 9` — Online play is restricted
- L258 _public enumerator_ `NetworkConnectionUnavailable = 1 << 10` — Check failed because network is unavailable

#### Free symbols / members of external scopes

- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineIdentity, Log, All);`
- L14 _macro_ `#define UE_LOG_ONLINE_IDENTITY(Verbosity, Format, ...) \`
- L19 _macro_ `#define UE_CLOG_ONLINE_IDENTITY(Conditional, Verbosity, Format, ...) \`
- L70 _namespace_ `namespace EUserPrivileges`
- L128 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoginChanged, int32 );` — Delegate called when a player logs in/out @param LocalUserNum the controller number of the associated user
- L128 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoginChanged, int32 );` — Delegate called when a player logs in/out @param LocalUserNum the controller number of the associated user
- L129 _typedef_ `typedef FOnLoginChanged::FDelegate FOnLoginChangedDelegate;`
- L139 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnLoginStatusChanged, int32 , ELoginStatus::Type , ELoginStatus::Type , const FUniqueNetId& );` — Delegate called when a player's status changes but doesn't change profiles @param LocalUserNum the controller number of the associated user @param OldStatus the old login status for the user @param NewStatus the new login status for the user @param NewId the new id to associate with the user
- L139 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnLoginStatusChanged, int32 , ELoginStatus::Type , ELoginStatus::Type , const FUniqueNetId& );` — Delegate called when a player's status changes but doesn't change profiles @param LocalUserNum the controller number of the associated user @param OldStatus the old login status for the user @param NewStatus the new login status for the user @param NewId the new id to associate with the user
- L140 _typedef_ `typedef FOnLoginStatusChanged::FDelegate FOnLoginStatusChangedDelegate;`
- L148 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAuthAboutToExpire, int32 );` — Delegate called when an auth session is about to expire and a new auth token is needed. The code bound to it is expected to respond by getting a new auth token and use it to re-call Login to refresh auth and keep the player logged in. param LocalUserNum the controller number of the user whose auth is about to expire
- L148 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAuthAboutToExpire, int32 );` — Delegate called when an auth session is about to expire and a new auth token is needed. The code bound to it is expected to respond by getting a new auth token and use it to re-call Login to refresh auth and keep the player logged in. param LocalUserNum the controller number of the user whose auth is about to expire
- L149 _typedef_ `typedef FOnAuthAboutToExpire::FDelegate FOnAuthAboutToExpireDelegate;`
- L158 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnControllerPairingChanged, int , FControllerPairingChangedUserInfo , FControllerPairingChangedUserInfo );` — Delegate called when a controller-user pairing changes @param LocalUserNum the logged-in user number of the user who owned the device whose pairing changed. If no previous owner, the user number of the new owner. @param PreviousUser the user that used to be paired with this controller @param NewUser the user that is currently paired with this controller
- L158 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnControllerPairingChanged, int , FControllerPairingChangedUserInfo , FControllerPairingChangedUserInfo );` — Delegate called when a controller-user pairing changes @param LocalUserNum the logged-in user number of the user who owned the device whose pairing changed. If no previous owner, the user number of the new owner. @param PreviousUser the user that used to be paired with this controller @param NewUser the user that is currently paired with this controller
- L159 _typedef_ `typedef FOnControllerPairingChanged::FDelegate FOnControllerPairingChangedDelegate;`
- L169 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnLoginComplete, int32 , bool , const FUniqueNetId& , const FString& );` — Called when user account login has completed after calling Login() or AutoLogin() @param LocalUserNum the controller number of the associated user @param bWasSuccessful true if server was contacted and a valid result received @param UserId the user id received from the server on successful login @param Error string representing the error condition
- L169 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnLoginComplete, int32 , bool , const FUniqueNetId& , const FString& );` — Called when user account login has completed after calling Login() or AutoLogin() @param LocalUserNum the controller number of the associated user @param bWasSuccessful true if server was contacted and a valid result received @param UserId the user id received from the server on successful login @param Error string representing the error condition
- L170 _typedef_ `typedef FOnLoginComplete::FDelegate FOnLoginCompleteDelegate;`
- L179 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLogoutComplete, int32 , bool );` — Delegate used in notifying the UI/game that the manual logout completed @param LocalUserNum the controller number of the associated user @param bWasSuccessful whether the async call completed properly or not
- L179 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLogoutComplete, int32 , bool );` — Delegate used in notifying the UI/game that the manual logout completed @param LocalUserNum the controller number of the associated user @param bWasSuccessful whether the async call completed properly or not
- L180 _typedef_ `typedef FOnLogoutComplete::FDelegate FOnLogoutCompleteDelegate;`
- L187 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoginFlowLogout, const TArray<FString>& );` — Delegate called when logout requires login flow to cleanup @param LoginDomains the login domains to clean up
- L187 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoginFlowLogout, const TArray<FString>& );` — Delegate called when logout requires login flow to cleanup @param LoginDomains the login domains to clean up
- L188 _typedef_ `typedef FOnLoginFlowLogout::FDelegate FOnLoginFlowLogoutDelegate;`
- L196 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRevokeAuthTokenCompleteDelegate, const FUniqueNetId& , const FOnlineError& );` — Delegate executed when we get a user privilege result. @param UserId The unique id of the user who was queried @param OnlineError the result of the operation
- L196 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnRevokeAuthTokenCompleteDelegate, const FUniqueNetId& , const FOnlineError& );` — Delegate executed when we get a user privilege result. @param UserId The unique id of the user who was queried @param OnlineError the result of the operation
- L483 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnGetLinkedAccountAuthTokenCompleteDelegate, int32 , bool , const FExternalAuthToken& );` — Delegate executed when the user's auth ticket has arrived @param LocalUserNum the controller number of the associated user @param bWasSuccessful whether the ticket was successfully retrieved or not @param AuthToken the token to use with linked auth
- L505 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnGetUserPrivilegeCompleteDelegate, const FUniqueNetId& , EUserPrivileges::Type , uint32 );` — Delegate executed when we get a user privilege result. @param LocalUserId The unique id of the user who was queried @param Privilege the privilege that was queried @param PrivilegeResult bitwise OR of any privilege failures. 0 is success.
- L552 _typedef_ `typedef TSharedPtr<IOnlineIdentity, ESPMode::ThreadSafe> IOnlineIdentityPtr;`
- L554 _prototype_ `FString ToDebugString(IOnlineIdentity::EPrivilegeResults PrivilegeResult);`
- L556 _prototype_ `FString ToDebugString(EUserPrivileges::Type UserPrivilege);`
- L558 _prototype_ `FString ToDebugString(const FControllerPairingChangedUserInfo& ControllerPairingChangedUserInfo);`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineLeaderboardInterface.h` (Public)


#### class `IOnlineLeaderboards`  
`class IOnlineLeaderboards`  
_L40-155_
- desc: Interface definition for the online services leaderboard services
- L43 _protected function_ `IOnlineLeaderboards()`
- L46 _public prototype_ `virtual ~IOnlineLeaderboards() = default;`
- L57 _public prototype_ `virtual bool ReadLeaderboards(const TArray< FUniqueNetIdRef >& Players, FOnlineLeaderboardReadRef& ReadObject) = 0;` — Reads a set of stats for the specified list of players @param Players the array of unique ids to read stats for @param ReadObject holds the definitions of the tables to read the data from and results are copied into the specified object @return true if the call is successful, false otherwise
- L70 _public prototype_ `virtual bool ReadLeaderboardsForFriends(int32 LocalUserNum, FOnlineLeaderboardReadRef& ReadObject) = 0;` — Reads a player's stats and all of that player's friends stats for the specified set of stat views. This allows you to easily compare a player's stats to their friends. @param LocalUserNum the local player having their stats and friend's stats read for @param ReadObject holds the definitions of the tables to read the data from and results are copied into the specified object @return true if the call is successful, false otherwise
- L83 _public prototype_ `virtual bool ReadLeaderboardsAroundRank(int32 Rank, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) = 0;` — Reads stats for a given rank in the leaderboard, as well as a range of stats above and below that rank. For example, if Rank = 100 and Range = 10, entries for ranks 90-110 will be returned. @param Rank the rank for which stats should be returned @Param Range the range above and below Rank to return as well @param ReadObject holds the definitions of the tables to read the data from and results are copied into the specified object @return true if the call is successful, false otherwise
- L96 _public prototype_ `virtual bool ReadLeaderboardsAroundUser(FUniqueNetIdRef Player, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) = 0;` — Reads stats for a given player in the leaderboard, as well as a range of stats above and below that user. For example, if the player is 100th in the leaderboard and Range = 10, entries for ranks 90-110 will be returned. @param Player the player for which stats should be returned @Param Range the range above and below the player's rank to return as well @param ReadObject holds the definitions of the tables to read the data from and results are copied into the specified object @return true if the call is successful, false otherwise
- L103 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnLeaderboardReadComplete, bool);` — Notifies the interested party that the last stats read has completed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L110 _public prototype_ `virtual void FreeStats(FOnlineLeaderboardRead& ReadObject) = 0;` — Cleans up any platform specific allocated data contained in the stats data @param ReadObject the object to handle per platform clean up on
- L125 _public prototype_ `virtual bool WriteLeaderboards(const FName& SessionName, const FUniqueNetId& Player, FOnlineLeaderboardWrite& WriteObject) = 0;` — Writes out the stats contained within the stats write object to the online subsystem's cache of stats data. Note the new data replaces the old. Stats cannot be written without a session or the write request is ignored. No more than 5 stats views can be written to at a time or the write request is ignored. @param SessionName the name of the session to write stats for @param Player the player to write stats for @param WriteObject the object containing the information to write @return true if the call is successful, false otherwise
- L134 _public prototype_ `virtual bool FlushLeaderboards(const FName& SessionName) = 0;` — Commits any changes in the online stats cache to the permanent storage @param SessionName the name of the session that stats are being flushed for @return true if the call is successful, false otherwise
- L142 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnLeaderboardFlushComplete, const FName&, bool);` — Delegate called when the stats flush operation has completed @param SessionName the name of the session having stats flushed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L153 _public prototype_ `virtual bool WriteOnlinePlayerRatings(const FName& SessionName, int32 LeaderboardId, const TArray<FOnlinePlayerScore>& PlayerScores) = 0;` — Writes the score data for the match, used for rankings/ratings @param SessionName the name of the session to write scores for @param LeaderboardId the leaderboard to write the score information to @param PlayerScores the list of players, teams, and scores they earned @return true if the call is successful, false otherwise

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineLeaderboard, Log, All);`
- L10 _macro_ `#define UE_LOG_ONLINE_LEADERBOARD(Verbosity, Format, ...) \`
- L15 _macro_ `#define UE_CLOG_ONLINE_LEADERBOARD(Conditional, Verbosity, Format, ...) \`
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLeaderboardReadComplete, bool);` — Delegate called when the last leaderboard read is complete @param bWasSuccessful was the leaderboard read successful or not
- L25 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLeaderboardReadComplete, bool);` — Delegate called when the last leaderboard read is complete @param bWasSuccessful was the leaderboard read successful or not
- L26 _typedef_ `typedef FOnLeaderboardReadComplete::FDelegate FOnLeaderboardReadCompleteDelegate;`
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLeaderboardFlushComplete, const FName, bool);` — Delegate called when the stats flush operation has completed @param SessionName the name of the session having stats flushed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L34 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLeaderboardFlushComplete, const FName, bool);` — Delegate called when the stats flush operation has completed @param SessionName the name of the session having stats flushed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L35 _typedef_ `typedef FOnLeaderboardFlushComplete::FDelegate FOnLeaderboardFlushCompleteDelegate;`
- L157 _typedef_ `typedef TSharedPtr<IOnlineLeaderboards, ESPMode::ThreadSafe> IOnlineLeaderboardsPtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineMessageInterface.h` (Public)


#### class `FOnlineMessagePayload`  
`class FOnlineMessagePayload`  
_L24-101_
- desc: Message payload that stores key value pairs for variant type data
- L28 _public member_ `static const int32 MaxPayloadSize = 4 * 1024;` — Max size of buffer when serializing payloads
- L33 _public function_ `FOnlineMessagePayload()` — Constructor
- L42 _public prototype_ `void ToBytes(TArray<uint8>& OutBytes) const;` — Convert the key value data to byte array @param OutBytes [out] array of bytes to serialize to
- L49 _public prototype_ `void FromBytes(const TArray<uint8>& InBytes);` — Convert byte array to key value data @param InBytes array of bytes to serialize from
- L56 _public prototype_ `void ToJson(FJsonObject& OutJsonObject) const;` — Convert key/val properties to json @param OutJsonObject resulting json object
- L63 _public prototype_ `FString ToJsonStr() const;` — Convert key/val properties to json str @return resulting json string
- L70 _public prototype_ `void FromJson(const FJsonObject& JsonObject);` — Convert json to key/val properties @param JsonObject json object to convert
- L77 _public prototype_ `void FromJsonStr(const FString& JsonStr);` — Convert json string to key/val properties @param JsonStr json string to convert
- L87 _public prototype_ `bool GetAttribute(const FString& AttrName, FVariantData& OutAttrValue) const;` — Find an attribute by name and get its value @param AttrName name of attribute entry to find @param OutAttrValue [out] attribute value to write to @return true if attribute was found
- L95 _public prototype_ `void SetAttribute(const FString& AttrName, const FVariantData& AttrValue);` — Set an attribute value by name @param AttrName name of attribute entry to set @param AttrValue attribute value to set
- L100 _private member_ `FOnlineKeyValuePairs<FString, FVariantData> KeyValData;` — key value attributes to store variant type data

#### class `FOnlineMessageHeader`  
`class FOnlineMessageHeader`  
_L107-130_
- desc: Message header obtained via EnumerateMessages Represents an inbox message that can be downloaded
- L114 _public function_ `FOnlineMessageHeader(const FUniqueNetIdRef& InFromUserId, const FUniqueMessageIdRef& InMessageId) : FromUserId(InFromUserId) , MessageId(InMessageId)` — Constructor
- L121 _public member_ `FUniqueNetIdRef FromUserId;` — Unique id of user that sent the message
- L123 _public member_ `FString FromName;` — Name of user that sent the message
- L125 _public member_ `FUniqueMessageIdRef MessageId;` — Unique id of the message. Needed to download the message payload
- L127 _public member_ `FString Type;` — Type of message
- L129 _public member_ `FString TimeStamp;` — UTC timestamp when message was sent

#### class `FOnlineMessage`  
`class FOnlineMessage`  
_L135-150_
- desc: Downloaded message obtained via passing message id to ReadMessage
- L141 _public function_ `FOnlineMessage(FUniqueMessageIdRef InMessageId) : MessageId(InMessageId)` — Constructor
- L147 _public member_ `FUniqueMessageIdRef MessageId;` — Unique id of the message
- L149 _public member_ `FOnlineMessagePayload Payload;` — Payload containing the body of the message

#### class `IOnlineMessage`  
`class IOnlineMessage`  
_L200-332_
- desc: Interface class for enumerating/sending/receiving messages between users
- L205 _public prototype_ `virtual ~IOnlineMessage() = default;`
- L214 _public prototype_ `virtual bool EnumerateMessages(int32 LocalUserNum) = 0;` — Enumerate list of available message headers from user's inbox @param LocalUserNum the controller number of the associated user that made the request @return true if request was started
- L223 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_TWO_PARAM(MAX_LOCAL_PLAYERS, OnEnumerateMessagesComplete, bool, const FString&);` — Delegate used when the enumeration of message headers has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param ErrorStr string representing the error condition
- L233 _public prototype_ `virtual bool GetMessageHeaders(int32 LocalUserNum, TArray< TSharedRef<class FOnlineMessageHeader> >& OutHeaders) = 0;` — Get the cached list of message headers for a user. Cache is populated by calling EnumerateMessages @param LocalUserNum the controller number of the associated user that made the request @param OutHeaders [out] array of message headers that were found @return true if cached entry was found
- L242 _public prototype_ `virtual bool ClearMessageHeaders(int32 LocalUserNum) = 0;` — Clear the cached list of message headers @param LocalUserNum the controller number of the associated user that made the request @return true if messages were clear, false if there was a problem
- L252 _public prototype_ `virtual bool ReadMessage(int32 LocalUserNum, const FUniqueMessageId& MessageId) = 0;` — Download a message and its payload from user's inbox @param LocalUserNum the controller number of the associated user that made the request @param MessageId unique id of the message to download. Obtained from message header list @return true if request was started
- L262 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_THREE_PARAM(MAX_LOCAL_PLAYERS, OnReadMessageComplete, bool, const FUniqueMessageId&, const FString&);` — Delegate used when downloading of message contents has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param MessageId unique id of the message downloaded @param ErrorStr string representing the error condition
- L272 _public prototype_ `virtual TSharedPtr<class FOnlineMessage> GetMessage(int32 LocalUserNum, const FUniqueMessageId& MessageId) = 0;` — Get the cached message and its contents for a user. Cache is populated by calling ReadMessage with a message id @param LocalUserNum the controller number of the associated user that made the request @param MessageId unique id of the message downloaded to find @return pointer to message entry if found or NULL
- L281 _public prototype_ `virtual bool ClearMessage(int32 LocalUserNum, const FUniqueMessageId& MessageId) = 0;` — Clear the given cached message @param LocalUserNum the controller number of the associated user that made the request @return true if messages were clear, false if there was a problem
- L290 _public prototype_ `virtual bool ClearMessages(int32 LocalUserNum) = 0;` — Clear all the cached messages @param LocalUserNum the controller number of the associated user that made the request @return true if messages were clear, false if there was a problem
- L302 _public prototype_ `virtual bool SendMessage(int32 LocalUserNum, const TArray< FUniqueNetIdRef >& RecipientIds, const FString& MessageType, const FOnlineMessagePayload& Payload) = 0;` — Send a message from the currently logged in user to a list of recipients @param LocalUserNum the controller number of the associated user that made the request @param RecipientIds unique ids of users to send this message to @param MessageType string representing the type of message @param Payload the body/content of the message @return true if request was started
- L311 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_TWO_PARAM(MAX_LOCAL_PLAYERS, OnSendMessageComplete, bool, const FString&);` — Delegate used when sending of message has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param ErrorStr string representing the error condition
- L321 _public prototype_ `virtual bool DeleteMessage(int32 LocalUserNum, const FUniqueMessageId& MessageId) = 0;` — Delete a message from currently logged in user's inbox @param LocalUserNum the controller number of the associated user that made the request @param MessageId unique id of the message to delete. Obtained from message header list @return true if request was started
- L331 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_THREE_PARAM(MAX_LOCAL_PLAYERS, OnDeleteMessageComplete, bool, const FUniqueMessageId&, const FString&);` — Delegate used when deleting a message has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param MessageId unique id of the message deleted @param ErrorStr string representing the error condition

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESUBSYSTEM_API`
- L16 _typedef_ `typedef FUniqueNetId FUniqueMessageId;` — unique identifier for messages
- L17 _typedef_ `typedef FUniqueNetIdRef FUniqueMessageIdRef;`
- L18 _typedef_ `typedef FUniqueNetIdPtr FUniqueMessageIdPtr;`
- L19 _typedef_ `typedef FUniqueNetIdSet FUniqueMessageIdSet;`
- L159 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnEnumerateMessagesComplete, int32, bool, const FString&);` — Delegate used when the enumeration of message headers has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param ErrorStr string representing the error condition
- L159 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnEnumerateMessagesComplete, int32, bool, const FString&);` — Delegate used when the enumeration of message headers has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param ErrorStr string representing the error condition
- L160 _typedef_ `typedef FOnEnumerateMessagesComplete::FDelegate FOnEnumerateMessagesCompleteDelegate;`
- L170 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnReadMessageComplete, int32, bool, const FUniqueMessageId&, const FString&);` — Delegate used when downloading of message contents has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param MessageId unique id of the message downloaded @param ErrorStr string representing the error condition
- L170 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnReadMessageComplete, int32, bool, const FUniqueMessageId&, const FString&);` — Delegate used when downloading of message contents has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param MessageId unique id of the message downloaded @param ErrorStr string representing the error condition
- L171 _typedef_ `typedef FOnReadMessageComplete::FDelegate FOnReadMessageCompleteDelegate;`
- L183 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSendMessageComplete, int32, bool, const FString&);` — Send a message from the currently logged in user to a list of recipients @param LocalUserNum the controller number of the associated user that made the request @param RecipientIds unique ids of users to send this message to @param MessageType string representing the type of message @param Payload the body/content of the message @return true if request was started
- L183 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSendMessageComplete, int32, bool, const FString&);` — Send a message from the currently logged in user to a list of recipients @param LocalUserNum the controller number of the associated user that made the request @param RecipientIds unique ids of users to send this message to @param MessageType string representing the type of message @param Payload the body/content of the message @return true if request was started
- L184 _typedef_ `typedef FOnSendMessageComplete::FDelegate FOnSendMessageCompleteDelegate;`
- L194 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnDeleteMessageComplete, int32, bool, const FUniqueMessageId&, const FString&);` — Delegate used when deleting a message has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param MessageId unique id of the message deleted @param ErrorStr string representing the error condition
- L194 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnDeleteMessageComplete, int32, bool, const FUniqueMessageId&, const FString&);` — Delegate used when deleting a message has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param MessageId unique id of the message deleted @param ErrorStr string representing the error condition
- L195 _typedef_ `typedef FOnDeleteMessageComplete::FDelegate FOnDeleteMessageCompleteDelegate;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineNotificationTransportInterface.h` (Public)


#### class `IOnlineNotificationTransportMessage`  
`class IOnlineNotificationTransportMessage`  
_L11-14_
- desc: abstract base class for messages of the type understood by the specific transport mechanism, eg. xmpp

#### class `IOnlineNotificationTransport`  
`class IOnlineNotificationTransport`  
_L20-61_
- desc: Interface for notification transport mechanisms
- L24 _protected function_ `IOnlineNotificationTransport(IOnlineSubsystem* InOnlineSubsystemInstance, FNotificationTransportId InTransportId) : OnlineSubsystemInstance(InOnlineSubsystemInstance),Id(InTransportId)` — Constructor
- L29 _protected prototype_ `virtual ~IOnlineNotificationTransport() = default;`
- L32 _protected member_ `IOnlineSubsystem* OnlineSubsystemInstance;` — The OSS associated with this transport, used for accessing the notification handler and transport manager
- L35 _protected member_ `FNotificationTransportId Id;` — Unique notification transport id associated with this transport
- L39 _public function_ `const FNotificationTransportId& GetNotificationTransportId() const`
- L47 _public function_ `bool operator==(const IOnlineNotificationTransport& Other) const` — Equality operator
- L52 _public prototype_ `virtual const IOnlineNotificationTransportMessage* Convert(const FOnlineNotification& Notification) = 0;`
- L54 _public prototype_ `virtual const FOnlineNotification& Convert(const IOnlineNotificationTransportMessage* TransportMessage) = 0;`
- L57 _public prototype_ `virtual bool SendNotification(const FOnlineNotification& Notification) = 0;` — Send a notification out using this transport mechanism
- L60 _public prototype_ `virtual bool ReceiveNotification(const IOnlineNotificationTransportMessage& TransportMessage) = 0;` — Receive a transport-specific notification in from this transport mechanism and pass along to be delivered

#### class `FOnlineTransportTapHandle`  
`class FOnlineTransportTapHandle`  
_L69-92_
- L73 _public function_ `FOnlineTransportTapHandle()`
- L75 _public function_ `explicit operator bool() const`
- L91 _private member_ `int Handle = -1;`

#### struct `FOnlineTransportTap`  
`struct FOnlineTransportTap`  
_L97-101_
- desc: A pattern used to open a tap and associated event handlers
- L99 _public member_ `FString AddressPattern;`
- L100 _public member_ `FOnTapStateChanged StateChangeHandler;`

#### Free symbols / members of external scopes

- L63 _typedef_ `typedef TSharedPtr<IOnlineNotificationTransport, ESPMode::ThreadSafe> IOnlineNotificationTransportPtr;`
- L80 _function_ `friend bool operator==(FOnlineTransportTapHandle Lhs, FOnlineTransportTapHandle Rhs)`
- L85 _function_ `friend bool operator!=(FOnlineTransportTapHandle Lhs, FOnlineTransportTapHandle Rhs)`
- L94 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTapStateChanged, bool );`
- L94 _prototype_ `DECLARE_DELEGATE_OneParam(FOnTapStateChanged, bool );`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlinePartyInterface.h` (Public)


#### enum `EMemberConnectionStatus`  
`enum class EMemberConnectionStatus : uint8`  
_L48-54_
- L50 _public enumerator_ `Uninitialized`
- L51 _public enumerator_ `Disconnected`
- L52 _public enumerator_ `Initializing`
- L53 _public enumerator_ `Connected`

#### class `FOnlinePartyMember`  
`class FOnlinePartyMember : public FOnlineUser`  
_L59-101_
- inherits: `FOnlineUser`
- desc: Party member user info returned by IOnlineParty interface
- L63 _public member_ `EMemberConnectionStatus MemberConnectionStatus = EMemberConnectionStatus::Uninitialized;`
- L64 _public member_ `EMemberConnectionStatus PreviousMemberConnectionStatus = EMemberConnectionStatus::Uninitialized;`
- L74 _public prototype_ `DECLARE_EVENT_FourParams(FOnlinePartyMember, FOnMemberAttributeChanged, const FUniqueNetId& , const FString& , const FString& , const FString& );` — Event when a party member's attribute has changed @see FOnlineUser::GetUserAttribute @param ChangedUserId id associated with this notification @param Attribute attribute that changed @param NewValue the new value for the attribute @param PreviousValue the previous value for the attribute
- L75 _public function_ `FOnMemberAttributeChanged& OnMemberAttributeChanged() const`
- L83 _public prototype_ `DECLARE_EVENT_ThreeParams(FOnlinePartyMember, FOnMemberConnectionStatusChanged, const FUniqueNetId& , const EMemberConnectionStatus , const EMemberConnectionStatus );` — Event when a party member's connection status has changed @param ChangedUserId - id associated with this notification @param NewMemberConnectionStatus - new member data status @param PreviousMemberConnectionStatus - previous member data status
- L84 _public function_ `FOnMemberConnectionStatusChanged& OnMemberConnectionStatusChanged() const`
- L86 _public function_ `void SetMemberConnectionStatus(EMemberConnectionStatus NewMemberConnectionStatus)`
- L98 _private member_ `mutable FOnMemberConnectionStatusChanged OnMemberConnectionStatusChangedEvent;` — Event fired when connection status changes
- L100 _private member_ `mutable FOnMemberAttributeChanged OnMemberAttributeChangedEvent;` — Event fired when an attribute changes

#### class `FOnlinePartyData`  
`class FOnlinePartyData : public TSharedFromThis<FOnlinePartyData>`  
_L109-326_
- inherits: `TSharedFromThis<FOnlinePartyData>`
- desc: Data associated with the entire party
- L113 _public prototype_ `FOnlinePartyData() = default;`
- L114 _public prototype_ `virtual ~FOnlinePartyData() = default;`
- L116 _public prototype_ `FOnlinePartyData(const FOnlinePartyData&) = default;`
- L117 _public prototype_ `FOnlinePartyData& operator=(const FOnlinePartyData&) = default;`
- L119 _public prototype_ `FOnlinePartyData(FOnlinePartyData&&) = default;`
- L120 _public prototype_ `FOnlinePartyData& operator=(FOnlinePartyData&&) = default;`
- L128 _public prototype_ `bool operator==(const FOnlinePartyData& Other) const;` — Equality operator @param Other the FOnlinePartyData to compare against @return true if considered equal, false otherwise
- L135 _public prototype_ `bool operator!=(const FOnlinePartyData& Other) const;` — Inequality operator @param Other the FOnlinePartyData to compare against @return true if considered not equal, false otherwise
- L145 _public function_ `bool GetAttribute(const FString& AttrName, FVariantData& OutAttrValue) const` — Get an attribute from the party data @param AttrName - key for the attribute @param OutAttrValue - [out] value for the attribute if found @return true if the attribute was found
- L165 _public function_ `inline void SetAttribute(const FString& AttrName, const FVariantData& AttrValue)` — Set an attribute from the party data @param AttrName - key for the attribute @param AttrValue - value to set the attribute to
- L176 _public function_ `virtual void SetAttribute(FString&& AttrName, FVariantData&& AttrValue)` — Set an attribute from the party data @param AttrName - key for the attribute @param AttrValue - value to set the attribute to
- L191 _public function_ `inline void RemoveAttribute(const FString& AttrName)` — Remove an attribute from the party data @param AttrName - key for the attribute
- L201 _public function_ `virtual void RemoveAttribute(FString&& AttrName)` — Remove an attribute from the party data @param AttrName - key for the attribute
- L214 _public function_ `virtual void MarkAttributeDirty(FString&& AttrName)` — Mark an attribute as dirty so it can be rebroadcasted @param AttrName - key for the attribute to mark dirty
- L224 _public function_ `bool HasDirtyKeys() const` — Check if there are any dirty keys @return true if there are any dirty keys
- L235 _public prototype_ `void GetDirtyKeyValAttrs(FOnlineKeyValuePairs<FString, FVariantData>& OutDirtyAttrs, TArray<FString>& OutRemovedAttrs) const;` — Get the dirty and removed key-value attributes @param OutDirtyAttrs the dirty attributes @param OutRemovedAttrs the removed attributes
- L240 _public function_ `virtual void ClearAttributes()` — Clear the attributes map
- L249 _public function_ `virtual void ClearDirty()` — Clear the dirty keys set, called after successfully sending an update of the dirty elements
- L261 _public function_ `void OnPacketSent(int32 PacketSize, int32 NumRecipients, bool bIncrementRevision) const` — Increment the stat tracking variables on packet sent @param PacketSize - size of the packet generated @param NumRecipients - number of recipients the packet was sent to @param bIncrementRevision - this packet was a dirty packet update so we should increment the revision
- L277 _public prototype_ `void ToJsonFull(FString& JsonString) const;` — Generate a JSON packet containing all key-value attributes @param JsonString - [out] string containing the resulting JSON output
- L284 _public prototype_ `void ToJsonDirty(FString& JsonString) const;` — Generate a JSON packet containing only the dirty key-value attributes for a delta update @param JsonString - [out] string containing the resulting JSON output
- L290 _public prototype_ `TSharedRef<FJsonObject> GetAllAttributesAsJsonObject() const;` — Create a JSON object containing all key-value attributes @return a JSON object containing all key-value attributes
- L296 _public prototype_ `FString GetAllAttributesAsJsonObjectString() const;` — Create a string representing a JSON object containing all key-value attributes @return a string representing a JSON object containing all key-value attributes
- L303 _public prototype_ `void FromJson(const FString& JsonString);` — Update attributes from a JSON packet @param JsonString - string containing the JSON packet
- L306 _public function_ `FOnlineKeyValuePairs<FString, FVariantData>& GetKeyValAttrs()` — Accessor functions for KeyValAttrs map
- L307 _public function_ `const FOnlineKeyValuePairs<FString, FVariantData>& GetKeyValAttrs() const`
- L311 _public member_ `mutable int32 TotalBytes = 0;` — Total number of bytes generated by calls to ToJsonFull and ToJsonDirty
- L313 _public member_ `mutable int32 TotalEffectiveBytes = 0;` — Total number of bytes generated by calls to ToJsonFull and ToJsonDirty, multiplied by the number of recipients the packet was sent to
- L315 _public member_ `mutable int32 TotalPackets = 0;` — Total number of packets generated by calls to ToJsonFull and ToJsonDirty
- L318 _public member_ `mutable int32 RevisionCount = 0;` — Id representing number of updates sent, useful for determining if a client has missed an update
- L322 _private member_ `FOnlineKeyValuePairs<FString, FVariantData> KeyValAttrs;` — map of key/val attributes that represents the data
- L325 _private member_ `TSet<FString> DirtyKeys;` — set of which fields are dirty and need to transmitted

#### class `IOnlinePartyUserPendingJoinRequestInfo`  
`class IOnlinePartyUserPendingJoinRequestInfo`  
_L336-364_
- desc: Info about a user requesting to join a party
- L339 _public prototype_ `virtual ~IOnlinePartyUserPendingJoinRequestInfo() = default;`
- L345 _public prototype_ `virtual const FUniqueNetIdRef& GetUserId() const = 0;` — Get the id of the user requesting to join @return the id of the user requesting to join
- L351 _public prototype_ `virtual const FString& GetDisplayName() const = 0;` — Get the display name of the user requesting to join @return the display name of the user requesting to join
- L357 _public prototype_ `virtual const FString& GetPlatform() const = 0;` — Get the platform of the user requesting to join @return the platform of the user requesting to join
- L363 _public prototype_ `virtual TSharedRef<const FOnlinePartyData> GetJoinData() const = 0;` — Get the join data of the user requesting to join @return the join data of the user requesting to join

#### class `IOnlinePartyPendingJoinRequestInfo`  
`class IOnlinePartyPendingJoinRequestInfo : public TSharedFromThis<IOnlinePartyPendingJoinRequestInfo>`  
_L372-432_
- inherits: `TSharedFromThis<IOnlinePartyPendingJoinRequestInfo>`
- desc: Info about a group of users requesting to join a party
- L376 _public prototype_ `IOnlinePartyPendingJoinRequestInfo() = default;`
- L377 _public prototype_ `virtual ~IOnlinePartyPendingJoinRequestInfo() = default;`
- L383 _public function_ `virtual const FUniqueNetIdRef& GetSenderId() const` — Get the primary user's id @return id of the primary user of this join request
- L395 _public function_ `virtual const FString& GetSenderDisplayName() const` — Get the primary user's display name @return display name of the primary user of this join request
- L407 _public function_ `virtual const FString& GetSenderPlatform() const` — Get the primary user's platform @return platform of the primary user of this join request
- L419 _public function_ `virtual TSharedRef<const FOnlinePartyData> GetSenderJoinData() const` — Get the primary user's join data @return join data provided by the primary user for this join request
- L431 _public prototype_ `virtual void GetUsers(TArray<IOnlinePartyUserPendingJoinRequestInfoConstRef>& OutUsers) const = 0;` — Get the list of users requesting to join @return array of users requesting to join

#### class `IOnlinePartyJoinInfo`  
`class IOnlinePartyJoinInfo : public TSharedFromThis<IOnlinePartyJoinInfo>`  
_L440-531_
- inherits: `TSharedFromThis<IOnlinePartyJoinInfo>`
- desc: Info needed to join a party
- L444 _public function_ `IOnlinePartyJoinInfo()`
- L445 _public prototype_ `virtual ~IOnlinePartyJoinInfo() = default;`
- L447 _public prototype_ `virtual bool IsValid() const = 0;`
- L452 _public prototype_ `virtual TSharedRef<const FOnlinePartyId> GetPartyId() const = 0;` — @return party id of party associated with this join invite
- L457 _public prototype_ `virtual FOnlinePartyTypeId GetPartyTypeId() const = 0;` — @return party id of party associated with this join invite
- L462 _public prototype_ `virtual FUniqueNetIdRef GetSourceUserId() const = 0;` — @return user id of where this join info came from
- L467 _public prototype_ `virtual const FString& GetSourceDisplayName() const = 0;` — @return user id of where this join info came from
- L472 _public prototype_ `virtual const FString& GetSourcePlatform() const = 0;` — @return source platform string
- L477 _public prototype_ `virtual const FString& GetPlatformData() const = 0;` — @return the PlatformData included in the join info
- L482 _public prototype_ `virtual bool HasKey() const = 0;` — @return true if the join info has some form of key(does not guarantee the validity of that key)
- L487 _public prototype_ `virtual bool HasPassword() const = 0;` — @return true if a password can be used to bypass generated access key
- L492 _public prototype_ `virtual bool IsAcceptingMembers() const = 0;` — @return true if the party is known to be accepting members
- L497 _public prototype_ `virtual bool IsPartyOfOne() const = 0;` — @return true if this is a party of one
- L502 _public prototype_ `virtual int32 GetNotAcceptingReason() const = 0;` — @return why the party is not accepting members
- L507 _public prototype_ `virtual const FString& GetAppId() const = 0;` — @return id of the client app associated with the sender of the party invite
- L512 _public prototype_ `virtual const FString& GetBuildId() const = 0;` — @return id of the build associated with the sender of the party invite
- L517 _public prototype_ `virtual bool CanJoin() const = 0;` — @return whether or not the join info can be used to join
- L522 _public prototype_ `virtual bool CanJoinWithPassword() const = 0;` — @return whether or not the join info can be used to join with a password
- L527 _public prototype_ `virtual bool CanRequestAnInvite() const = 0;` — @return whether or not the join info has the info to request an invite
- L529 _public prototype_ `virtual FString ToDebugString() const;`

#### enum `PartySystemPermissions::EPermissionType`  
`enum class EPermissionType : uint8`  
_L544-554_
- desc: Who has permissions to perform party actions
- L547 _public enumerator_ `Noone` — Noone has access to do that action
- L549 _public enumerator_ `Leader` — Available to the leader only
- L551 _public enumerator_ `Friends` — Available to the leader and friends of the leader only
- L553 _public enumerator_ `Anyone` — Available to anyone

#### enum `EJoinRequestAction`  
`enum class EJoinRequestAction : uint8`  
_L557-562_
- L559 _public enumerator_ `Manual`
- L560 _public enumerator_ `AutoApprove`
- L561 _public enumerator_ `AutoReject`

#### struct `FPartyConfiguration`  
`struct FPartyConfiguration : public TSharedFromThis<FPartyConfiguration>`  
_L566-617_
- inherits: `TSharedFromThis<FPartyConfiguration>`
- desc: Options for configuring a new party or for updating an existing party
- L569 _public function_ `FPartyConfiguration() : JoinRequestAction(EJoinRequestAction::Manual) , PresencePermissions(PartySystemPermissions::EPermissionType::Anyone) , InvitePermissions(PartySystemPermissions::EPermissionType::Leader) , bChatEnabled(true) , bShouldRemoveOnDisconnection(false) , bIsAcceptingMembers(false) , NotAcceptingMembersReason(0) , MaxMembers(0)`
- L586 _public prototype_ `bool operator==(const FPartyConfiguration& Other) const;` — Equality operator @param Other the FPartyConfiguration to compare against @return true if considered equal, false otherwise
- L593 _public prototype_ `bool operator!=(const FPartyConfiguration& Other) const;` — Inequality operator @param Other the FPartyConfiguration to compare against @return true if considered not equal, false otherwise
- L596 _public member_ `EJoinRequestAction JoinRequestAction;` — should publish info to presence
- L598 _public member_ `PartySystemPermissions::EPermissionType PresencePermissions;` — Permission for how the party can be
- L600 _public member_ `PartySystemPermissions::EPermissionType InvitePermissions;` — Permission who can send invites
- L602 _public member_ `bool bChatEnabled;` — should have a muc room
- L604 _public member_ `bool bShouldRemoveOnDisconnection;` — should remove on disconnection
- L606 _public member_ `bool bIsAcceptingMembers;` — is accepting members
- L608 _public member_ `int32 NotAcceptingMembersReason;` — not accepting members reason
- L610 _public member_ `int32 MaxMembers;` — Maximum active members allowed. 0 means no maximum.
- L612 _public member_ `FString Nickname;` — Human readable nickname
- L614 _public member_ `FString Description;` — Human readable description
- L616 _public member_ `FString Password;` — Human readable password for party.

#### enum `EPartyState`  
`enum class EPartyState : uint8`  
_L621-630_
- L623 _public enumerator_ `None`
- L624 _public enumerator_ `CreatePending`
- L625 _public enumerator_ `JoinPending`
- L626 _public enumerator_ `LeavePending`
- L627 _public enumerator_ `Active`
- L628 _public enumerator_ `Disconnected`
- L629 _public enumerator_ `CleanUp`

#### class `FOnlineParty`  
`class FOnlineParty : public TSharedFromThis<FOnlineParty>`  
_L635-689_
- inherits: `TSharedFromThis<FOnlineParty>`
- desc: Current state associated with a party
- L638 _private prototype_ `FOnlineParty() = delete;`
- L640 _protected function_ `FOnlineParty(const TSharedRef<const FOnlinePartyId>& InPartyId, const FOnlinePartyTypeId InPartyTypeId) : PartyId(InPartyId) , PartyTypeId(InPartyTypeId) , State(EPartyState::None) , PreviousState(EPartyState::None)`
- L648 _public prototype_ `virtual ~FOnlineParty() = default;`
- L656 _public prototype_ `virtual bool CanLocalUserInvite(const FUniqueNetId& LocalUserId) const = 0;` — Check if the local user has invite permissions in this party. Based on configuration permissions and party state. @param LocalUserId the local user's id @return true if the local user can invite, false if not
- L663 _public prototype_ `virtual bool IsJoinable() const = 0;` — Is this party joinable? @return true if this party is joinable, false if not
- L664 _public function_ `virtual void SetState(EPartyState InState)`
- L675 _public prototype_ `virtual TSharedRef<const FPartyConfiguration> GetConfiguration() const = 0;` — Get the party's configuration @return the party's configuration
- L678 _public member_ `TSharedRef<const FOnlinePartyId> PartyId;` — Unique id of the party
- L680 _public member_ `const FOnlinePartyTypeId PartyTypeId;` — Type of party (e.g., Primary)
- L682 _public member_ `FUniqueNetIdPtr LeaderId;` — Unique id of the leader
- L684 _public member_ `EPartyState State;` — The current state of the party
- L686 _public member_ `EPartyState PreviousState;` — The previous state of the party
- L688 _public member_ `FChatRoomId RoomId;` — id of chat room associated with the party

#### enum `EMemberExitedReason`  
`enum class EMemberExitedReason : uint8`  
_L694-700_
- L696 _public enumerator_ `Unknown`
- L697 _public enumerator_ `Left`
- L698 _public enumerator_ `Removed`
- L699 _public enumerator_ `Kicked`

#### enum `EPartyInvitationRemovedReason`  
`enum class EPartyInvitationRemovedReason : uint8`  
_L702-716_
- L705 _public enumerator_ `Unknown` — Unknown or undefined reason
- L707 _public enumerator_ `Accepted` — User accepted the invitation
- L709 _public enumerator_ `Declined` — User declined the invitation
- L711 _public enumerator_ `Cleared` — ClearInvitations was called, the invitation should no longer be displayed
- L713 _public enumerator_ `Expired` — Expired
- L715 _public enumerator_ `Invalidated` — Became invalid (for example, party was destroyed)

#### struct `FPartyInvitationRecipient`  
`struct FPartyInvitationRecipient`  
_L719-744_
- desc: Recipient information for SendInvitation
- L722 _public function_ `FPartyInvitationRecipient(const FUniqueNetIdRef& InId) : Id(InId)` — Constructor
- L727 _public function_ `FPartyInvitationRecipient(const FUniqueNetId& InId) : Id(InId.AsShared())` — Constructor
- L732 _public function_ `FPartyInvitationRecipient(const FUniqueNetId& InId, const FString& InMetaData) : Id(InId.AsShared()) , PlatformData(InMetaData)` — Constructor
- L738 _public member_ `FUniqueNetIdRef Id;` — Id of the user to send the invitation to
- L740 _public member_ `FString PlatformData;` — Additional data to provide context for the invitee
- L743 _public prototype_ `FString ToDebugString() const;` — Get a string representation suitable for logging

#### enum `EPartySystemState`  
`enum class EPartySystemState : uint8`  
_L746-752_
- L748 _public enumerator_ `Initializing = 0`
- L749 _public enumerator_ `Initialized`
- L750 _public enumerator_ `RequestingShutdown`
- L751 _public enumerator_ `ShutDown`

#### enum `EPartyRequestToJoinRemovedReason`  
`enum class EPartyRequestToJoinRemovedReason : uint8`  
_L754-766_
- L757 _public enumerator_ `Unknown` — Unknown or undefined reason
- L759 _public enumerator_ `Cancelled` — Cancelled
- L761 _public enumerator_ `Expired` — Expired
- L763 _public enumerator_ `Dismissed` — Dismissed
- L765 _public enumerator_ `Accepted` — Accepted

#### class `IOnlinePartyRequestToJoinInfo`  
`class IOnlinePartyRequestToJoinInfo : public TSharedFromThis<IOnlinePartyRequestToJoinInfo>`  
_L771-807_
- inherits: `TSharedFromThis<IOnlinePartyRequestToJoinInfo>`
- desc: Info about a request to join a local user's party
- L775 _public prototype_ `IOnlinePartyRequestToJoinInfo() = default;`
- L776 _public prototype_ `virtual ~IOnlinePartyRequestToJoinInfo() = default;`
- L782 _public prototype_ `virtual const FUniqueNetIdPtr GetUserId() const = 0;` — Get the id of the user requesting to join @return the id of the user requesting to join
- L788 _public prototype_ `virtual const FString& GetDisplayName() const = 0;` — Get the display name of the user requesting to join @return the display name of the user requesting to join
- L794 _public prototype_ `virtual const FString& GetPlatformData() const = 0;` — Get the platform data associated with this request @return the platform data associated with this request
- L800 _public prototype_ `virtual const FDateTime& GetExpirationTime() const = 0;` — Get the expiration time of the request to join @return the expiration time of the request to join
- L806 _public prototype_ `virtual const FOnlinePartyTypeId GetPartyTypeId() const = 0;` — Get the GetPartyTypeId of the request to join @return the GetPartyTypeId of the request to join

#### class `IOnlinePartySystem`  
`class IOnlinePartySystem`  
_L1162-1823_
- desc: Interface definition for the online party services Allows for forming a party and communicating with party members
- L1165 _protected prototype_ `IOnlinePartySystem() = default;`
- L1168 _public prototype_ `virtual ~IOnlinePartySystem() = default;`
- L1176 _public prototype_ `virtual void RestoreParties(const FUniqueNetId& LocalUserId, const FOnRestorePartiesComplete& CompletionDelegate) = 0;` — Restore party memberships. Intended to be called once during login to restore state from other running instances. @param LocalUserId the user to restore the party membership for @param CompletionDelegate the delegate to trigger on completion
- L1184 _public prototype_ `virtual void RestoreInvites(const FUniqueNetId& LocalUserId, const FOnRestoreInvitesComplete& CompletionDelegate) = 0;` — Restore party invites. Intended to be called once during login to restore state from other running instances. @param LocalUserId the user to restore the pings for @param CompletionDelegate the delegate to trigger on completion
- L1192 _public prototype_ `virtual void CleanupParties(const FUniqueNetId& LocalUserId, const FOnCleanupPartiesComplete& CompletionDelegate) = 0;` — Cleanup party state. This will cleanup the local party state and attempt to cleanup party memberships on an external service if possible.  Intended to be called for development purposes. @param LocalUserId the user to cleanup the parties for @param CompletionDelegate the delegate to trigger on completion
- L1204 _public prototype_ `virtual bool CreateParty(const FUniqueNetId& LocalUserId, const FOnlinePartyTypeId PartyTypeId, const FPartyConfiguration& PartyConfig, const FOnCreatePartyComplete& Delegate = FOnCreatePartyComplete()) = 0;` — Create a new party @param LocalUserId - user making the request @param PartyConfig - configuration for the party (can be updated later) @param Delegate - called on completion @param UserRoomId - this forces the name of the room to be this value @return true if task was started
- L1215 _public prototype_ `virtual bool UpdateParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FPartyConfiguration& PartyConfig, bool bShouldRegenerateReservationKey = false, const FOnUpdatePartyComplete& Delegate = FOnUpdatePartyComplete()) = 0;` — Update an existing party with new configuration @param LocalUserId - user making the request @param PartyConfig - configuration for the party @param Delegate - called on completion @return true if task was started
- L1226 _public prototype_ `virtual bool JoinParty(const FUniqueNetId& LocalUserId, const IOnlinePartyJoinInfo& OnlinePartyJoinInfo, const FOnJoinPartyComplete& Delegate = FOnJoinPartyComplete()) = 0;` — Join an existing party @param LocalUserId - user making the request @param OnlinePartyJoinInfo - join information containing data such as party id, leader id @param Delegate - called on completion @return true if task was started
- L1236 _public prototype_ `virtual void RequestToJoinParty(const FUniqueNetId& LocalUserId, const FOnlinePartyTypeId PartyTypeId, const FPartyInvitationRecipient& Recipient, const FOnRequestToJoinPartyComplete& Delegate = FOnRequestToJoinPartyComplete()) = 0;` — Request to join an existing party @param LocalUserId - user making the request @param PartyTypeId - type id of the party you want join @param Recipient - structure specifying the party leader receiving the request @param Delegate - called on completion
- L1246 _public prototype_ `virtual void ClearRequestToJoinParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& Sender, EPartyRequestToJoinRemovedReason Reason) = 0;` — Clear a received request to join your party @param LocalUserId - user clearing the request @param PartyId - id of the party the request was made to @param Sender - user who sent the request @param Reason - reason why the request was cleared
- L1257 _public prototype_ `virtual void QueryPartyJoinability(const FUniqueNetId& LocalUserId, const IOnlinePartyJoinInfo& OnlinePartyJoinInfo, const FOnQueryPartyJoinabilityCompleteEx& Delegate) = 0;` — Query a party to check it's current joinability Intended to be used before a call to LeaveParty (to leave your existing party, which would then be followed by JoinParty) Note that the party's joinability can change from moment to moment so a successful response for this does not guarantee a successful JoinParty @param LocalUserId - user making the request @param OnlinePartyJoinInfo - join information containing data such as party id, leader id @param Delegate - called on completion
- L1270 _public prototype_ `virtual bool LeaveParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, bool bSynchronizeLeave, const FOnLeavePartyComplete& Delegate = FOnLeavePartyComplete()) = 0;` — Leave an existing party All existing party members notified of member leaving (see FOnPartyMemberLeft) @param LocalUserId - user making the request @param PartyId - id of an existing party @param bSynchronizeLeave - Whether we synchronize the leave with remote server/clients or only do a local cleanup @param Delegate - called on completion @return true if task was started
- L1283 _public prototype_ `virtual bool ApproveJoinRequest(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& RecipientId, bool bIsApproved, int32 DeniedResultCode = 0) = 0;` — Approve a request to join a party @param LocalUserId - user making the request @param PartyId - id of an existing party @param RecipientId - id of the user being invited @param bIsApproved - whether the join request was approved or not @param DeniedResultCode - used when bIsApproved is false - client defined value to return when leader denies approval @return true if task was started
- L1295 _public prototype_ `virtual void RespondToQueryJoinability(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& RecipientId, bool bCanJoin, int32 DeniedResultCode, FOnlinePartyDataConstPtr PartyData) = 0;` — Respond to a query joinability request.  This reflects the current party's joinability state and can change from moment to moment, and therefore does not guarantee a successful join. @param LocalUserId - user making the request @param PartyId - id of an existing party @param RecipientId - id of the user being invited @param bCanJoin - whether the player can attempt to join or not @param DeniedResultCode - used when bCanJoin is false - client defined value to return when leader denies approval @param PartyData - data to send back to the querying user
- L1308 _public prototype_ `virtual bool SendInvitation(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FPartyInvitationRecipient& Recipient, const FOnSendPartyInvitationComplete& Delegate = FOnSendPartyInvitationComplete()) = 0;` — sends an invitation to a user that could not otherwise join a party if the player accepts the invite they will be sent the data needed to trigger a call to RequestReservation @param LocalUserId - user making the request @param PartyId - id of an existing party @param Recipient - structure specifying the recipient of the invitation @param Delegate - called on completion @return true if task was started
- L1318 _public prototype_ `virtual void CancelInvitation(const FUniqueNetId& LocalUserId, const FUniqueNetId& TargetUserId, const FOnlinePartyId& PartyId, const FOnCancelPartyInvitationComplete& Delegate = FOnCancelPartyInvitationComplete()) = 0;` — Cancel an invitation sent to a user @param LocalUserId - user making the cancellation @param TargetUserId - previously invited user @param PartyId - id of an existing party @param Delegate - called on completion
- L1328 _public prototype_ `virtual bool RejectInvitation(const FUniqueNetId& LocalUserId, const FUniqueNetId& SenderId) = 0;` — Reject an invite to a party @param LocalUserId - user making the request @param SenderId - id of the sender @return true if task was started
- L1339 _public prototype_ `virtual void ClearInvitations(const FUniqueNetId& LocalUserId, const FUniqueNetId& SenderId, const FOnlinePartyId* PartyId = nullptr) = 0;` — Clear invitations from a user because the invitations were handled by the application @param LocalUserId - user making the request @param SenderId - id of the sender @param PartyId - optional, if specified will clear only the one invitation, if blank all invitations from the sender will be cleared @return true if task was started
- L1352 _public prototype_ `virtual bool KickMember(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& TargetMemberId, const FOnKickPartyMemberComplete& Delegate = FOnKickPartyMemberComplete()) = 0;` — Kick a user from an existing party Only admin can kick a party member @param LocalUserId - user making the request @param PartyId - id of an existing party @param MemberId - id of the user being kicked @param Delegate - called on completion @return true if task was started
- L1365 _public prototype_ `virtual bool PromoteMember(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& TargetMemberId, const FOnPromotePartyMemberComplete& Delegate = FOnPromotePartyMemberComplete()) = 0;` — Promote a user from an existing party to be admin All existing party members notified of promoted member (see FOnPartyMemberPromoted) @param LocalUserId - user making the request @param PartyId - id of an existing party @param MemberId - id of the user being promoted @param Delegate - called on completion @return true if task was started
- L1380 _public prototype_ `virtual bool UpdatePartyData(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FName& Namespace, const FOnlinePartyData& PartyData) = 0;` — Set party data and broadcast to all members Only current data can be set and no history of past party data is preserved Party members notified of new data (see FOnPartyDataReceived) @param LocalUserId - user making the request @param PartyId - id of an existing party @param Namespace - namespace for the data @param PartyData - data to send to all party members @param Delegate - called on completion @return true if task was started
- L1395 _public prototype_ `virtual bool UpdatePartyMemberData(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FName& Namespace, const FOnlinePartyData& PartyMemberData) = 0;` — Set party data for a single party member and broadcast to all members Only current data can be set and no history of past party member data is preserved Party members notified of new data (see FOnPartyMemberDataReceived) @param LocalUserId - user making the request @param PartyId - id of an existing party @param Namespace - namespace for the data @param PartyMemberData - member data to send to all party members @param Delegate - called on completion @return true if task was started
- L1405 _public prototype_ `virtual bool IsMemberLeader(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& MemberId) const = 0;` — returns true if the user specified by MemberId is the leader of the party specified by PartyId @param LocalUserId - user making the request @param PartyId     - id of an existing party @param MemberId    - id of member to test
- L1414 _public prototype_ `virtual uint32 GetPartyMemberCount(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId) const = 0;` — returns the number of players in a given party @param LocalUserId - user making the request @param PartyId     - id of an existing party
- L1424 _public prototype_ `virtual FOnlinePartyConstPtr GetParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId) const = 0;` — Get info associated with a party @param LocalUserId - user making the request @param PartyId     - id of an existing party @return party info or nullptr if not found
- L1434 _public prototype_ `virtual FOnlinePartyConstPtr GetParty(const FUniqueNetId& LocalUserId, const FOnlinePartyTypeId& PartyTypeId) const = 0;` — Get info associated with a party @param LocalUserId - user making the request @param PartyTypeId - type of an existing party @return party info or nullptr if not found
- L1445 _public prototype_ `virtual FOnlinePartyMemberConstPtr GetPartyMember(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& MemberId) const = 0;` — Get a party member by id @param LocalUserId - user making the request @param PartyId     - id of an existing party @param MemberId    - id of member to find @return party member info or nullptr if not found
- L1457 _public prototype_ `virtual FOnlinePartyDataConstPtr GetPartyData(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FName& Namespace) const = 0;` — Get current cached data associated with a party FOnPartyDataReceived notification called whenever this data changes @param LocalUserId - user making the request @param PartyId     - id of an existing party @param Namespace   - namespace of data @return party data or nullptr if not found
- L1470 _public prototype_ `virtual FOnlinePartyDataConstPtr GetPartyMemberData(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& MemberId, const FName& Namespace) const = 0;` — Get current cached data associated with a party member FOnPartyMemberDataReceived notification called whenever this data changes @param LocalUserId - user making the request @param PartyId     - id of an existing party @param MemberId    - id of member to find data for @param Namespace   - namespace of data @return party member data or nullptr if not found
- L1481 _public prototype_ `virtual IOnlinePartyJoinInfoConstPtr GetAdvertisedParty(const FUniqueNetId& LocalUserId, const FUniqueNetId& UserId, const FOnlinePartyTypeId PartyTypeId) const = 0;` — Get the join info of the specified user and party type @param LocalUserId       - user making the request @param UserId            - user to check @param PartyTypeId       - type of party to query @return shared pointer to the join info if the user is advertising for that party type
- L1491 _public prototype_ `virtual bool GetJoinedParties(const FUniqueNetId& LocalUserId, TArray<TSharedRef<const FOnlinePartyId>>& OutPartyIdArray) const = 0;` — Get a list of currently joined parties for the user @param LocalUserId     - user making the request @param OutPartyIdArray - list of party ids joined by the current user @return true if entries found
- L1502 _public prototype_ `virtual bool GetPartyMembers(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, TArray<FOnlinePartyMemberConstRef>& OutPartyMembersArray) const = 0;` — Get list of current party members @param LocalUserId          - user making the request @param PartyId              - id of an existing party @param OutPartyMembersArray - list of party members currently in the party @return true if entries found
- L1512 _public prototype_ `virtual bool GetPendingInvites(const FUniqueNetId& LocalUserId, TArray<IOnlinePartyJoinInfoConstRef>& OutPendingInvitesArray) const = 0;` — Get a list of parties the user has been invited to @param LocalUserId            - user making the request @param OutPendingInvitesArray - list of party info needed to join the party @return true if entries found
- L1523 _public prototype_ `virtual bool GetPendingJoinRequests(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, TArray<IOnlinePartyPendingJoinRequestInfoConstRef>& OutPendingJoinRequestArray) const = 0;` — Get list of users requesting to join the party @param LocalUserId           - user making the request @param PartyId               - id of an existing party @param OutPendingUserIdArray - list of pending party members @return true if entries found
- L1534 _public prototype_ `virtual bool GetPendingInvitedUsers(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, TArray<FUniqueNetIdRef>& OutPendingInvitedUserArray) const = 0;` — Get list of users invited to a party that have not yet responded @param LocalUserId                - user making the request @param PartyId                    - id of an existing party @param OutPendingInvitedUserArray - list of user that have pending invites @return true if entries found
- L1544 _public prototype_ `virtual bool GetPendingRequestsToJoin(const FUniqueNetId& LocalUserId, TArray<IOnlinePartyRequestToJoinInfoConstRef>& OutRequestsToJoin) const = 0;` — Get a list of users requesting to join the party. These are not requests for a reservation, but permission (e.g. locked party). @param LocalUserId       - user making the request @param OutRequestsToJoin - list of requests to join @return true if entries found
- L1546 _public member_ `static const FOnlinePartyTypeId::TInternalType PrimaryPartyTypeIdValue = 0x11111111;`
- L1550 _public function_ `static const FOnlinePartyTypeId GetPrimaryPartyTypeId()` — @return party type id for the primary party - the primary party is the party that will be addressable via the social panel
- L1555 _public function_ `static const FOnlinePartyTypeId MakePartyTypeId(const FOnlinePartyTypeId::TInternalType InTypeId)` — @return party type id for the specified party
- L1564 _public prototype_ `virtual FString MakeJoinInfoJson(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId) = 0;` — returns the json version of a join info for a current party @param LocalUserId       - user making the request @param PartyId           - party to make the json from
- L1572 _public prototype_ `virtual IOnlinePartyJoinInfoConstPtr MakeJoinInfoFromJson(const FString& JoinInfoJson) = 0;` — returns a valid join info object from a json blob @param JoinInfoJson       - json blob to convert
- L1581 _public prototype_ `virtual FString MakeTokenFromJoinInfo(const IOnlinePartyJoinInfo& JoinInfo) const = 0;` — Creates a command line token from a IOnlinePartyJoinInfo object @param JoinInfo - the IOnlinePartyJoinInfo object to convert return the new IOnlinePartyJoinInfo object
- L1590 _public prototype_ `virtual IOnlinePartyJoinInfoConstPtr MakeJoinInfo(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId) = 0;` — returns the join info for current party @param LocalUserId       - user making the request @param PartyId           - party to make the json from
- L1599 _public prototype_ `virtual IOnlinePartyJoinInfoConstPtr MakeJoinInfoFromToken(const FString& Token) const = 0;` — Creates a IOnlinePartyJoinInfo object from a command line token @param Token - the token string return the new IOnlinePartyJoinInfo object
- L1606 _public prototype_ `virtual IOnlinePartyJoinInfoConstPtr ConsumePendingCommandLineInvite() = 0;` — Checks to see if there is a pending command line invite and consumes it return the pending IOnlinePartyJoinInfo object
- L1640 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnPartyJoined, const FUniqueNetId& , const FOnlinePartyId& );` — notification of when a party is joined @param LocalUserId - id associated with this notification @param PartyId - id associated with the party
- L1647 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnPartyExited, const FUniqueNetId& , const FOnlinePartyId& );` — notification of when a party is exited @param LocalUserId - id associated with this notification @param PartyId - id associated with the party
- L1656 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnPartyStateChanged, const FUniqueNetId& , const FOnlinePartyId& , EPartyState , EPartyState );` — Notification when a party's state has changed @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param State - state of the party @param PreviousState - previous state of the party
- L1664 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnPartyPromotionLockoutChanged, const FUniqueNetId& , const FOnlinePartyId& , const bool );` — Notification when player promotion is locked out. @param PartyId - id associated with the party @param bLockoutState - if promotion is currently locked out
- L1672 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnPartyConfigChanged, const FUniqueNetId& , const FOnlinePartyId& , const FPartyConfiguration& );` — Notification when party data is updated @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param PartyConfig - party whose config was updated
- L1681 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnPartyDataReceived, const FUniqueNetId& , const FOnlinePartyId& , const FName& , const FOnlinePartyData& );` — Notification when party data is updated @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param Namespace - namespace the party data is associated with @param PartyData - party data that was updated
- L1689 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnPartyMemberPromoted, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& );` — Notification when a member is promoted in a party @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param NewLeaderId - id of member that was promoted
- L1698 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnPartyMemberExited, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const EMemberExitedReason );` — Notification when a member exits a party @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param MemberId - id of member that joined @param Reason - why the member was removed
- L1706 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnPartyMemberJoined, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& );` — Notification when a member joins the party @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param MemberId - id of member that joined
- L1716 _public prototype_ `DEFINE_ONLINE_DELEGATE_FIVE_PARAM(OnPartyMemberDataReceived, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const FName& , const FOnlinePartyData& );` — Notification when party member data is updated @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param MemberId - id of member that had updated data @param Namespace - namespace the party data is associated with @param PartyMemberData - party member data that was updated
- L1722 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnPartyInvitesChanged, const FUniqueNetId& );` — Notification when an invite list has changed for a party @param LocalUserId - user that is associated with this notification
- L1731 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnPartyInviteRequestReceived, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const FUniqueNetId& );` — Notification when a request for an invite has been received @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param SenderId - id of user that sent the invite @param RequestForId - id of user that sender is requesting the invite for - invalid if the sender is requesting the invite
- L1738 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnPartyInviteReceivedEx, const FUniqueNetId& , const IOnlinePartyJoinInfo& );` — Notification when a new invite is received @param LocalUserId - id associated with this notification @param Invitation - the invitation that was received
- L1746 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnPartyInviteRemovedEx, const FUniqueNetId& , const IOnlinePartyJoinInfo& , EPartyInvitationRemovedReason );` — Notification when an invite has been removed @param LocalUserId id associated with this notification @param Invitation the invitation that was removed @param Reason reason the invitation was removed
- L1755 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnPartyInviteResponseReceived, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const EInvitationResponse );` — Notification when an invitation response is received @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param SenderId - id of user that responded to an invite @param Response - the response
- L1764 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnPartyJoinRequestReceived, const FUniqueNetId& , const FOnlinePartyId& , const IOnlinePartyPendingJoinRequestInfo& );` — Notification when a new reservation request is received Subscriber is expected to call ApproveJoinRequest @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param JoinRequestInfo - data about users that are joining
- L1773 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnQueryPartyJoinabilityReceived, const FUniqueNetId& , const FOnlinePartyId& , const IOnlinePartyPendingJoinRequestInfo& );` — Notification when a player wants to know if the party is in a joinable state Subscriber is expected to call RespondToQueryJoinability @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param JoinRequestInfo - data about users that are joining
- L1782 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnFillPartyJoinRequestData, const FUniqueNetId& , const FOnlinePartyId& , FOnlinePartyData& );` — Notification when a player wants to know if the party is in a joinable state Subscriber is expected to call RespondToQueryJoinability @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param PartyData - data provided by the sender for the leader to use to determine joinability
- L1791 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnPartyAnalyticsEvent, const FUniqueNetId& , const FString& , const TArray<FAnalyticsEventAttribute>& );` — Notification when an analytics event needs to be recorded Subscriber is expected to record the event @param LocalUserId - id associated with this event @param EventName - name of the event @param Attributes - attributes for the event
- L1797 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnPartySystemStateChange, EPartySystemState );` — Notification of party system state change @param NewState - new state this partysystem is in
- L1806 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnPartyRequestToJoinReceived, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const IOnlinePartyRequestToJoinInfo& );` — Notification when a new party join request is received @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param RequesterId - id of player who requested to join @param Request - request to join information
- L1816 _public prototype_ `DEFINE_ONLINE_DELEGATE_FIVE_PARAM(OnPartyRequestToJoinRemoved, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const IOnlinePartyRequestToJoinInfo& , EPartyRequestToJoinRemovedReason );` — Notification when a new party join request is removed @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param RequesterId - id of player who requested to join @param Request - request to join information @param Reason - the reason why the request was removed
- L1821 _public prototype_ `virtual void DumpPartyState() = 0;` — Dump out party state for all known parties

#### enum `ECreatePartyCompletionResult`  
`enum class ECreatePartyCompletionResult : int8`  
_L1825-1837_
- L1827 _public enumerator_ `UnknownClientFailure = -100`
- L1828 _public enumerator_ `AlreadyInPartyOfSpecifiedType`
- L1829 _public enumerator_ `AlreadyCreatingParty`
- L1830 _public enumerator_ `AlreadyInParty`
- L1831 _public enumerator_ `FailedToCreateMucRoom`
- L1832 _public enumerator_ `NoResponse`
- L1833 _public enumerator_ `LoggedOut`
- L1834 _public enumerator_ `NotPrimaryUser`
- L1835 _public enumerator_ `UnknownInternalFailure = 0`
- L1836 _public enumerator_ `Succeeded = 1`

#### enum `EJoinPartyCompletionResult`  
`enum class EJoinPartyCompletionResult : int8`  
_L1839-1888_
- L1842 _public enumerator_ `UnknownClientFailure = -100` — Unspecified error.  No message sent to party leader.
- L1844 _public enumerator_ `BadBuild` — Your build id does not match the build id of the party
- L1846 _public enumerator_ `InvalidAccessKey` — Your provided access key does not match the party's access key
- L1848 _public enumerator_ `AlreadyInLeadersJoiningList` — The party leader already has you in the joining players list
- L1850 _public enumerator_ `AlreadyInLeadersPartyRoster` — The party leader already has you in the party members list
- L1852 _public enumerator_ `NoSpace` — The party leader rejected your join request because the party is full
- L1854 _public enumerator_ `NotApproved` — The party leader rejected your join request for a game specific reason, indicated by the NotApprovedReason parameter
- L1856 _public enumerator_ `RequesteeNotMember` — The player you send the join request to is not a member of the specified party
- L1858 _public enumerator_ `RequesteeNotLeader` — The player you send the join request to is not the leader of the specified party
- L1860 _public enumerator_ `NoResponse` — A response was not received from the party leader in a timely manner, the join attempt is considered failed
- L1862 _public enumerator_ `LoggedOut` — You were logged out while attempting to join the party
- L1864 _public enumerator_ `IncompatiblePlatform` — Your platform is not compatible with the party
- L1867 _public enumerator_ `AlreadyJoiningParty` — We are currently waiting for a response for a previous join request for the specified party.  No message sent to party leader.
- L1869 _public enumerator_ `AlreadyInParty` — We are already in the party that you are attempting to join.  No message sent to the party leader.
- L1871 _public enumerator_ `JoinInfoInvalid` — The party join info is invalid.  No message sent to the party leader.
- L1873 _public enumerator_ `AlreadyInPartyOfSpecifiedType` — We are already in a party of the specified type.  No message sent to the party leader.
- L1875 _public enumerator_ `MessagingFailure` — Failed to send a message to the party leader.  No message sent to the party leader.
- L1878 _public enumerator_ `GameSpecificReason` — Game specific reason, indicated by the NotApprovedReason parameter.  Message might or might not have been sent to party leader.
- L1881 _public enumerator_ `MismatchedApp` — Your app id does not match the app id of the party
- L1884 _public enumerator_ `UnknownInternalFailure = 0` — DEPRECATED
- L1887 _public enumerator_ `Succeeded = 1` — Successully joined the party

#### enum `ELeavePartyCompletionResult`  
`enum class ELeavePartyCompletionResult : int8`  
_L1890-1917_
- L1893 _public enumerator_ `UnknownClientFailure = -100` — Unspecified error.  No message sent.
- L1895 _public enumerator_ `NoResponse` — Timed out waiting for a response to the message.  Party has been left.
- L1897 _public enumerator_ `LoggedOut` — You were logged out while attempting to leave the party.  Party has been left.
- L1900 _public enumerator_ `UnknownParty` — You are not in the specified party.  No message sent.
- L1902 _public enumerator_ `LeavePending` — You are already leaving the party.  No message sent.
- L1905 _public enumerator_ `UnknownLocalUser` — DEPRECATED!
- L1907 _public enumerator_ `NotMember` — DEPRECATED!
- L1909 _public enumerator_ `MessagingFailure` — DEPRECATED!
- L1911 _public enumerator_ `UnknownTransportFailure` — DEPRECATED!
- L1913 _public enumerator_ `UnknownInternalFailure = 0` — DEPRECATED!
- L1916 _public enumerator_ `Succeeded = 1` — Successfully left the party

#### enum `EUpdateConfigCompletionResult`  
`enum class EUpdateConfigCompletionResult : int8`  
_L1919-1930_
- L1921 _public enumerator_ `UnknownClientFailure = -100`
- L1922 _public enumerator_ `UnknownParty`
- L1923 _public enumerator_ `LocalMemberNotMember`
- L1924 _public enumerator_ `LocalMemberNotLeader`
- L1925 _public enumerator_ `RemoteMemberNotMember`
- L1926 _public enumerator_ `MessagingFailure`
- L1927 _public enumerator_ `NoResponse`
- L1928 _public enumerator_ `UnknownInternalFailure = 0`
- L1929 _public enumerator_ `Succeeded = 1`

#### enum `ERequestPartyInvitationCompletionResult`  
`enum class ERequestPartyInvitationCompletionResult : int8`  
_L1932-1941_
- L1934 _public enumerator_ `NotLoggedIn = -100`
- L1935 _public enumerator_ `InvitePending`
- L1936 _public enumerator_ `AlreadyInParty`
- L1937 _public enumerator_ `PartyFull`
- L1938 _public enumerator_ `NoPermission`
- L1939 _public enumerator_ `UnknownInternalFailure = 0`
- L1940 _public enumerator_ `Succeeded = 1`

#### enum `ESendPartyInvitationCompletionResult`  
`enum class ESendPartyInvitationCompletionResult : int8`  
_L1943-1953_
- L1945 _public enumerator_ `NotLoggedIn = -100`
- L1946 _public enumerator_ `InvitePending`
- L1947 _public enumerator_ `AlreadyInParty`
- L1948 _public enumerator_ `PartyFull`
- L1949 _public enumerator_ `NoPermission`
- L1950 _public enumerator_ `RateLimited`
- L1951 _public enumerator_ `UnknownInternalFailure = 0`
- L1952 _public enumerator_ `Succeeded = 1`

#### enum `EAcceptPartyInvitationCompletionResult`  
`enum class EAcceptPartyInvitationCompletionResult : int8`  
_L1955-1964_
- L1957 _public enumerator_ `NotLoggedIn = -100`
- L1958 _public enumerator_ `InvitePending`
- L1959 _public enumerator_ `AlreadyInParty`
- L1960 _public enumerator_ `PartyFull`
- L1961 _public enumerator_ `NoPermission`
- L1962 _public enumerator_ `UnknownInternalFailure = 0`
- L1963 _public enumerator_ `Succeeded = 1`

#### enum `ERejectPartyInvitationCompletionResult`  
`enum class ERejectPartyInvitationCompletionResult : int8`  
_L1966-1975_
- L1968 _public enumerator_ `NotLoggedIn = -100`
- L1969 _public enumerator_ `InvitePending`
- L1970 _public enumerator_ `AlreadyInParty`
- L1971 _public enumerator_ `PartyFull`
- L1972 _public enumerator_ `NoPermission`
- L1973 _public enumerator_ `UnknownInternalFailure = 0`
- L1974 _public enumerator_ `Succeeded = 1`

#### enum `EKickMemberCompletionResult`  
`enum class EKickMemberCompletionResult : int8`  
_L1977-1989_
- L1979 _public enumerator_ `UnknownClientFailure = -100`
- L1980 _public enumerator_ `UnknownParty`
- L1981 _public enumerator_ `LocalMemberNotMember`
- L1982 _public enumerator_ `LocalMemberNotLeader`
- L1983 _public enumerator_ `RemoteMemberNotMember`
- L1984 _public enumerator_ `MessagingFailure`
- L1985 _public enumerator_ `NoResponse`
- L1986 _public enumerator_ `LoggedOut`
- L1987 _public enumerator_ `UnknownInternalFailure = 0`
- L1988 _public enumerator_ `Succeeded = 1`

#### enum `EPromoteMemberCompletionResult`  
`enum class EPromoteMemberCompletionResult : int8`  
_L1991-2006_
- L1993 _public enumerator_ `UnknownClientFailure = -100`
- L1994 _public enumerator_ `UnknownServiceFailure`
- L1995 _public enumerator_ `UnknownParty`
- L1996 _public enumerator_ `LocalMemberNotMember`
- L1997 _public enumerator_ `LocalMemberNotLeader`
- L1998 _public enumerator_ `PromotionAlreadyPending`
- L1999 _public enumerator_ `TargetIsSelf`
- L2000 _public enumerator_ `TargetNotMember`
- L2001 _public enumerator_ `MessagingFailure`
- L2002 _public enumerator_ `NoResponse`
- L2003 _public enumerator_ `LoggedOut`
- L2004 _public enumerator_ `UnknownInternalFailure = 0`
- L2005 _public enumerator_ `Succeeded = 1`

#### enum `EInvitationResponse`  
`enum class EInvitationResponse : uint8`  
_L2008-2014_
- L2010 _public enumerator_ `UnknownFailure`
- L2011 _public enumerator_ `BadBuild`
- L2012 _public enumerator_ `Rejected`
- L2013 _public enumerator_ `Accepted`

#### enum `ERequestToJoinPartyCompletionResult`  
`enum class ERequestToJoinPartyCompletionResult : int8`  
_L2016-2026_
- L2018 _public enumerator_ `ValidationFailure = -100`
- L2019 _public enumerator_ `NotAuthorized`
- L2020 _public enumerator_ `Forbidden`
- L2021 _public enumerator_ `UserNotFound`
- L2022 _public enumerator_ `AlreadyExists`
- L2023 _public enumerator_ `RateLimited`
- L2024 _public enumerator_ `UnknownInternalFailure`
- L2025 _public enumerator_ `Succeeded = 1`

#### struct `FQueryPartyJoinabilityResult`  
`struct FQueryPartyJoinabilityResult`  
_L2031-2041_
- desc: QueryPartyJoinability result
- L2034 _public member_ `FOnlineError Result;` — Online error representing the result of the operation
- L2036 _public member_ `EJoinPartyCompletionResult EnumResult = EJoinPartyCompletionResult::UnknownClientFailure;` — Enum result
- L2038 _public member_ `int32 SubCode = 0;` — Subcode for the EnumResult
- L2040 _public member_ `FOnlinePartyDataConstPtr PartyData;` — If successful, the party's data

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ONLINESUBSYSTEM_API`
- L12 _typedef_ `typedef FString FChatRoomId;`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineParty, Log, All);`
- L16 _macro_ `#define UE_LOG_ONLINE_PARTY(Verbosity, Format, ...) \`
- L21 _macro_ `#define UE_CLOG_ONLINE_PARTY(Conditional, Verbosity, Format, ...) \`
- L26 _macro_ `#define F_PREFIX(TypeToPrefix) F##TypeToPrefix`
- L27 _macro_ `#define PARTY_DECLARE_DELEGATETYPE(Type) typedef F##Type::FDelegate F##Type##Delegate`
- L29 _externvar_ `extern FName DefaultPartyDataNamespace;`
- L74 _delegate_ `DECLARE_EVENT_FourParams(FOnlinePartyMember, FOnMemberAttributeChanged, const FUniqueNetId& , const FString& , const FString& , const FString& );` — Event when a party member's attribute has changed @see FOnlineUser::GetUserAttribute @param ChangedUserId id associated with this notification @param Attribute attribute that changed @param NewValue the new value for the attribute @param PreviousValue the previous value for the attribute
- L83 _delegate_ `DECLARE_EVENT_ThreeParams(FOnlinePartyMember, FOnMemberConnectionStatusChanged, const FUniqueNetId& , const EMemberConnectionStatus , const EMemberConnectionStatus );` — Event when a party member's connection status has changed @param ChangedUserId - id associated with this notification @param NewMemberConnectionStatus - new member data status @param PreviousMemberConnectionStatus - previous member data status
- L103 _typedef_ `typedef TSharedRef<const FOnlinePartyMember> FOnlinePartyMemberConstRef;`
- L104 _typedef_ `typedef TSharedPtr<const FOnlinePartyMember> FOnlinePartyMemberConstPtr;`
- L328 _typedef_ `typedef TSharedRef<FOnlinePartyData> FOnlinePartyDataRef;`
- L329 _typedef_ `typedef TSharedPtr<FOnlinePartyData> FOnlinePartyDataPtr;`
- L330 _typedef_ `typedef TSharedRef<const FOnlinePartyData> FOnlinePartyDataConstRef;`
- L331 _typedef_ `typedef TSharedPtr<const FOnlinePartyData> FOnlinePartyDataConstPtr;`
- L366 _typedef_ `typedef TSharedRef<const IOnlinePartyUserPendingJoinRequestInfo> IOnlinePartyUserPendingJoinRequestInfoConstRef;`
- L367 _typedef_ `typedef TSharedPtr<const IOnlinePartyUserPendingJoinRequestInfo> IOnlinePartyUserPendingJoinRequestInfoConstPtr;`
- L434 _typedef_ `typedef TSharedRef<const IOnlinePartyPendingJoinRequestInfo> IOnlinePartyPendingJoinRequestInfoConstRef;`
- L435 _typedef_ `typedef TSharedPtr<const IOnlinePartyPendingJoinRequestInfo> IOnlinePartyPendingJoinRequestInfoConstPtr;`
- L533 _typedef_ `typedef TSharedRef<const IOnlinePartyJoinInfo> IOnlinePartyJoinInfoConstRef;`
- L534 _typedef_ `typedef TSharedPtr<const IOnlinePartyJoinInfo> IOnlinePartyJoinInfoConstPtr;`
- L539 _namespace_ `namespace PartySystemPermissions`
- L619 _typedef_ `typedef TSharedRef<const FPartyConfiguration> FPartyConfigurationConstRef;`
- L691 _typedef_ `typedef TSharedRef<const FOnlineParty> FOnlinePartyConstRef;`
- L692 _typedef_ `typedef TSharedPtr<const FOnlineParty> FOnlinePartyConstPtr;`
- L809 _typedef_ `typedef TSharedRef<const IOnlinePartyRequestToJoinInfo> IOnlinePartyRequestToJoinInfoConstRef;`
- L810 _typedef_ `typedef TSharedPtr<const IOnlinePartyRequestToJoinInfo> IOnlinePartyRequestToJoinInfoConstPtr;`
- L822 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRestorePartiesComplete, const FUniqueNetId& , const FOnlineError& );` — Restore parties async task completed callback @param LocalUserId id of user that initiated the request @param Result Result of the operation
- L822 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnRestorePartiesComplete, const FUniqueNetId& , const FOnlineError& );` — Restore parties async task completed callback @param LocalUserId id of user that initiated the request @param Result Result of the operation
- L829 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRestoreInvitesComplete, const FUniqueNetId& , const FOnlineError& );` — Restore invites async task completed callback @param LocalUserId id of user that initiated the request @param Result Result of the operation
- L829 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnRestoreInvitesComplete, const FUniqueNetId& , const FOnlineError& );` — Restore invites async task completed callback @param LocalUserId id of user that initiated the request @param Result Result of the operation
- L836 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnCleanupPartiesComplete, const FUniqueNetId& , const FOnlineError& );` — Cleanup parties async task completed callback @param LocalUserId id of user that initiated the request @param Result Result of the operation
- L836 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnCleanupPartiesComplete, const FUniqueNetId& , const FOnlineError& );` — Cleanup parties async task completed callback @param LocalUserId id of user that initiated the request @param Result Result of the operation
- L844 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnCreatePartyComplete, const FUniqueNetId& , const TSharedPtr<const FOnlinePartyId>& , const ECreatePartyCompletionResult );` — Party creation async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param Result - result of the operation
- L844 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnCreatePartyComplete, const FUniqueNetId& , const TSharedPtr<const FOnlinePartyId>& , const ECreatePartyCompletionResult );` — Party creation async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param Result - result of the operation
- L853 _delegate_ `DECLARE_DELEGATE_FourParams(FOnJoinPartyComplete, const FUniqueNetId& , const FOnlinePartyId& , const EJoinPartyCompletionResult , const int32 );` — Party join async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param Result - result of the operation @param NotApprovedReason - client defined value describing why you were not approved
- L853 _prototype_ `DECLARE_DELEGATE_FourParams(FOnJoinPartyComplete, const FUniqueNetId& , const FOnlinePartyId& , const EJoinPartyCompletionResult , const int32 );` — Party join async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param Result - result of the operation @param NotApprovedReason - client defined value describing why you were not approved
- L861 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnQueryPartyJoinabilityCompleteEx, const FUniqueNetId& , const FOnlinePartyId& , const FQueryPartyJoinabilityResult& );` — Party query joinability async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param Result - result of the operation
- L861 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnQueryPartyJoinabilityCompleteEx, const FUniqueNetId& , const FOnlinePartyId& , const FQueryPartyJoinabilityResult& );` — Party query joinability async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param Result - result of the operation
- L869 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnLeavePartyComplete, const FUniqueNetId& , const FOnlinePartyId& , const ELeavePartyCompletionResult );` — Party leave async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param Result - result of the operation
- L869 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnLeavePartyComplete, const FUniqueNetId& , const FOnlinePartyId& , const ELeavePartyCompletionResult );` — Party leave async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param Result - result of the operation
- L877 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnUpdatePartyComplete, const FUniqueNetId& , const FOnlinePartyId& , const EUpdateConfigCompletionResult );` — Party update async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param Result - result of the operation
- L877 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnUpdatePartyComplete, const FUniqueNetId& , const FOnlinePartyId& , const EUpdateConfigCompletionResult );` — Party update async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param Result - result of the operation
- L885 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnRequestPartyInvitationComplete, const FUniqueNetId& , const FOnlinePartyId& , const ERequestPartyInvitationCompletionResult );` — Party update async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param Result - result of the operation
- L885 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnRequestPartyInvitationComplete, const FUniqueNetId& , const FOnlinePartyId& , const ERequestPartyInvitationCompletionResult );` — Party update async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param Result - result of the operation
- L894 _delegate_ `DECLARE_DELEGATE_FourParams(FOnSendPartyInvitationComplete, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const ESendPartyInvitationCompletionResult );` — Party invitation sent completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param RecipientId - user invite was sent to @param Result - result of the send operation
- L894 _prototype_ `DECLARE_DELEGATE_FourParams(FOnSendPartyInvitationComplete, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const ESendPartyInvitationCompletionResult );` — Party invitation sent completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param RecipientId - user invite was sent to @param Result - result of the send operation
- L903 _delegate_ `DECLARE_DELEGATE_FourParams(FOnCancelPartyInvitationComplete, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const FOnlineError& );` — Party invitation cancel completed callback @param SenderUserId - id of user that initiated the request @param PartyId - id associated with the party @param TargetUserId - user invite was sent to @param Result - result of the cancel operation
- L903 _prototype_ `DECLARE_DELEGATE_FourParams(FOnCancelPartyInvitationComplete, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const FOnlineError& );` — Party invitation cancel completed callback @param SenderUserId - id of user that initiated the request @param PartyId - id associated with the party @param TargetUserId - user invite was sent to @param Result - result of the cancel operation
- L911 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnAcceptPartyInvitationComplete, const FUniqueNetId& , const FOnlinePartyId& , const EAcceptPartyInvitationCompletionResult );` — Accepting an invite to a user to join party async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param Result - string with error info if any
- L911 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnAcceptPartyInvitationComplete, const FUniqueNetId& , const FOnlinePartyId& , const EAcceptPartyInvitationCompletionResult );` — Accepting an invite to a user to join party async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param Result - string with error info if any
- L920 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnRejectPartyInvitationComplete, const FUniqueNetId& , const FOnlinePartyId& , const ERejectPartyInvitationCompletionResult );` — Rejecting an invite to a user to join party async task completed callback @param LocalUserId - id of user that initiated the request @param bWasSuccessful - true if successfully sent invite @param PartyId - id associated with the party @param Result - string with error info if any
- L920 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnRejectPartyInvitationComplete, const FUniqueNetId& , const FOnlinePartyId& , const ERejectPartyInvitationCompletionResult );` — Rejecting an invite to a user to join party async task completed callback @param LocalUserId - id of user that initiated the request @param bWasSuccessful - true if successfully sent invite @param PartyId - id associated with the party @param Result - string with error info if any
- L929 _delegate_ `DECLARE_DELEGATE_FourParams(FOnKickPartyMemberComplete, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const EKickMemberCompletionResult );` — Kicking a member of a party async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param MemberId - id of member being kicked @param Result - string with error info if any
- L929 _prototype_ `DECLARE_DELEGATE_FourParams(FOnKickPartyMemberComplete, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const EKickMemberCompletionResult );` — Kicking a member of a party async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param MemberId - id of member being kicked @param Result - string with error info if any
- L938 _delegate_ `DECLARE_DELEGATE_FourParams(FOnPromotePartyMemberComplete, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const EPromoteMemberCompletionResult );` — Promoting a member of a party async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param MemberId - id of member being promoted to leader @param Result - string with error info if any
- L938 _prototype_ `DECLARE_DELEGATE_FourParams(FOnPromotePartyMemberComplete, const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const EPromoteMemberCompletionResult );` — Promoting a member of a party async task completed callback @param LocalUserId - id of user that initiated the request @param PartyId - id associated with the party @param MemberId - id of member being promoted to leader @param Result - string with error info if any
- L947 _delegate_ `DECLARE_DELEGATE_FourParams(FOnRequestToJoinPartyComplete, const FUniqueNetId& , const FUniqueNetId& , const FDateTime& , const ERequestToJoinPartyCompletionResult );` — Request to join party async task completed callback @param LocalUserId - id of user that initiated the request @param PartyLeaderId - id of party leader receiving the request @param ExpiresAt - if successful, the time the request expires @param Result - result of the operation
- L947 _prototype_ `DECLARE_DELEGATE_FourParams(FOnRequestToJoinPartyComplete, const FUniqueNetId& , const FUniqueNetId& , const FDateTime& , const ERequestToJoinPartyCompletionResult );` — Request to join party async task completed callback @param LocalUserId - id of user that initiated the request @param PartyLeaderId - id of party leader receiving the request @param ExpiresAt - if successful, the time the request expires @param Result - result of the operation
- L962 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(F_PREFIX(OnPartyJoined), const FUniqueNetId& , const FOnlinePartyId& );` — notification when a party is joined @param LocalUserId - id associated with this notification @param PartyId - id associated with the party
- L962 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(F_PREFIX(OnPartyJoined), const FUniqueNetId& , const FOnlinePartyId& );` — notification when a party is joined @param LocalUserId - id associated with this notification @param PartyId - id associated with the party
- L963 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyJoined);`
- L970 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(F_PREFIX(OnPartyExited), const FUniqueNetId& , const FOnlinePartyId& );` — notification when a party is joined @param LocalUserId - id associated with this notification @param PartyId - id associated with the party
- L970 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(F_PREFIX(OnPartyExited), const FUniqueNetId& , const FOnlinePartyId& );` — notification when a party is joined @param LocalUserId - id associated with this notification @param PartyId - id associated with the party
- L971 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyExited);`
- L980 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(F_PREFIX(OnPartyStateChanged), const FUniqueNetId& , const FOnlinePartyId& , EPartyState , EPartyState );` — Notification when a party's state has changed @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param State - state of the party @param PreviousState - previous state of the party
- L980 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(F_PREFIX(OnPartyStateChanged), const FUniqueNetId& , const FOnlinePartyId& , EPartyState , EPartyState );` — Notification when a party's state has changed @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param State - state of the party @param PreviousState - previous state of the party
- L981 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyStateChanged);`
- L989 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyPromotionLockoutChanged), const FUniqueNetId& , const FOnlinePartyId& , const bool );` — Notification when player promotion is locked out. @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param bLockoutState - if promotion is currently locked out
- L989 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyPromotionLockoutChanged), const FUniqueNetId& , const FOnlinePartyId& , const bool );` — Notification when player promotion is locked out. @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param bLockoutState - if promotion is currently locked out
- L990 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyPromotionLockoutChanged);`
- L998 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyConfigChanged), const FUniqueNetId& , const FOnlinePartyId& , const FPartyConfiguration& );` — Notification when party config is updated @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param PartyConfig - party whose config was updated
- L998 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyConfigChanged), const FUniqueNetId& , const FOnlinePartyId& , const FPartyConfiguration& );` — Notification when party config is updated @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param PartyConfig - party whose config was updated
- L999 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyConfigChanged);`
- L1008 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(F_PREFIX(OnPartyDataReceived), const FUniqueNetId& , const FOnlinePartyId& , const FName& , const FOnlinePartyData& );` — Notification when party data is updated @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param Namespace - namespace the party data is associated with @param PartyData - party data that was updated
- L1008 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(F_PREFIX(OnPartyDataReceived), const FUniqueNetId& , const FOnlinePartyId& , const FName& , const FOnlinePartyData& );` — Notification when party data is updated @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param Namespace - namespace the party data is associated with @param PartyData - party data that was updated
- L1009 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyDataReceived);`
- L1017 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyMemberPromoted), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& );` — Notification when a member is promoted in a party @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param NewLeaderId - id of member that was promoted
- L1017 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyMemberPromoted), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& );` — Notification when a member is promoted in a party @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param NewLeaderId - id of member that was promoted
- L1018 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyMemberPromoted);`
- L1027 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(F_PREFIX(OnPartyMemberExited), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const EMemberExitedReason );` — Notification when a member exits a party @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param MemberId - id of member that joined @param Reason - why the member was removed
- L1027 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(F_PREFIX(OnPartyMemberExited), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const EMemberExitedReason );` — Notification when a member exits a party @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param MemberId - id of member that joined @param Reason - why the member was removed
- L1028 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyMemberExited);`
- L1036 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyMemberJoined), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& );` — Notification when a member joins the party @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param MemberId - id of member that joined
- L1036 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyMemberJoined), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& );` — Notification when a member joins the party @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param MemberId - id of member that joined
- L1037 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyMemberJoined);`
- L1047 _delegate_ `DECLARE_MULTICAST_DELEGATE_FiveParams(F_PREFIX(OnPartyMemberDataReceived), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const FName& , const FOnlinePartyData& );` — Notification when party member data is updated @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param MemberId - id of member that had updated data @param Namespace - namespace the party data is associated with @param PartyMemberData - party member data that was updated
- L1047 _prototype_ `DECLARE_MULTICAST_DELEGATE_FiveParams(F_PREFIX(OnPartyMemberDataReceived), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const FName& , const FOnlinePartyData& );` — Notification when party member data is updated @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param MemberId - id of member that had updated data @param Namespace - namespace the party data is associated with @param PartyMemberData - party member data that was updated
- L1048 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyMemberDataReceived);`
- L1054 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(F_PREFIX(OnPartyInvitesChanged), const FUniqueNetId& );` — Notification when an invite list has changed for a party the user is in @param LocalUserId - user that is associated with this notification
- L1054 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(F_PREFIX(OnPartyInvitesChanged), const FUniqueNetId& );` — Notification when an invite list has changed for a party the user is in @param LocalUserId - user that is associated with this notification
- L1055 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyInvitesChanged);`
- L1064 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(F_PREFIX(OnPartyInviteRequestReceived), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const FUniqueNetId& );` — Notification when a request for an invite has been received @param LocalUserId id associated with this notification @param PartyId id associated with the party @param SenderId id of user that sent the invite @param RequestForId id of user that sender is requesting the invite for - invalid if the sender is requesting the invite
- L1064 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(F_PREFIX(OnPartyInviteRequestReceived), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const FUniqueNetId& );` — Notification when a request for an invite has been received @param LocalUserId id associated with this notification @param PartyId id associated with the party @param SenderId id of user that sent the invite @param RequestForId id of user that sender is requesting the invite for - invalid if the sender is requesting the invite
- L1065 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyInviteRequestReceived);`
- L1072 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(F_PREFIX(OnPartyInviteReceivedEx), const FUniqueNetId& , const IOnlinePartyJoinInfo& );` — Notification when a new invite is received @param LocalUserId id associated with this notification @param Invitation the invitation that was received
- L1072 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(F_PREFIX(OnPartyInviteReceivedEx), const FUniqueNetId& , const IOnlinePartyJoinInfo& );` — Notification when a new invite is received @param LocalUserId id associated with this notification @param Invitation the invitation that was received
- L1073 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyInviteReceivedEx);`
- L1081 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyInviteRemovedEx), const FUniqueNetId& , const IOnlinePartyJoinInfo& , EPartyInvitationRemovedReason );` — Notification when an invite has been removed @param LocalUserId id associated with this notification @param Invitation the invitation that was removed @param Reason reason the invite has been removed
- L1081 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyInviteRemovedEx), const FUniqueNetId& , const IOnlinePartyJoinInfo& , EPartyInvitationRemovedReason );` — Notification when an invite has been removed @param LocalUserId id associated with this notification @param Invitation the invitation that was removed @param Reason reason the invite has been removed
- L1082 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyInviteRemovedEx);`
- L1091 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(F_PREFIX(OnPartyInviteResponseReceived), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const EInvitationResponse );` — Notification when a new invite is received @param LocalUserId id associated with this notification @param PartyId id associated with the party @param SenderId id of user that sent the invite @param bWasAccepted whether or not the invite was accepted
- L1091 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(F_PREFIX(OnPartyInviteResponseReceived), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const EInvitationResponse );` — Notification when a new invite is received @param LocalUserId id associated with this notification @param PartyId id associated with the party @param SenderId id of user that sent the invite @param bWasAccepted whether or not the invite was accepted
- L1092 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyInviteResponseReceived);`
- L1100 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyJoinRequestReceived), const FUniqueNetId& , const FOnlinePartyId& , const IOnlinePartyPendingJoinRequestInfo& );` — Notification when a new reservation request is received @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param JoinRequestInfo - data about users that are joining
- L1100 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyJoinRequestReceived), const FUniqueNetId& , const FOnlinePartyId& , const IOnlinePartyPendingJoinRequestInfo& );` — Notification when a new reservation request is received @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param JoinRequestInfo - data about users that are joining
- L1101 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyJoinRequestReceived);`
- L1109 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnQueryPartyJoinabilityReceived), const FUniqueNetId& , const FOnlinePartyId& , const IOnlinePartyPendingJoinRequestInfo& );` — Notification when a player wants to know if the party is in a joinable state @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param JoinRequestInfo - data about users that are joining
- L1109 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnQueryPartyJoinabilityReceived), const FUniqueNetId& , const FOnlinePartyId& , const IOnlinePartyPendingJoinRequestInfo& );` — Notification when a player wants to know if the party is in a joinable state @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param JoinRequestInfo - data about users that are joining
- L1110 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnQueryPartyJoinabilityReceived);`
- L1118 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnFillPartyJoinRequestData), const FUniqueNetId& , const FOnlinePartyId& , FOnlinePartyData& );` — Request for the game to fill in data to be sent with the join request for the leader to make an informed decision based on the joiner's state @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param PartyData - data for the game to populate
- L1118 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnFillPartyJoinRequestData), const FUniqueNetId& , const FOnlinePartyId& , FOnlinePartyData& );` — Request for the game to fill in data to be sent with the join request for the leader to make an informed decision based on the joiner's state @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param PartyData - data for the game to populate
- L1119 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnFillPartyJoinRequestData);`
- L1127 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyAnalyticsEvent), const FUniqueNetId& , const FString& , const TArray<FAnalyticsEventAttribute>& );` — Notification when an analytics event needs to be recorded @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param PartyData - data for the game to populate
- L1127 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyAnalyticsEvent), const FUniqueNetId& , const FString& , const TArray<FAnalyticsEventAttribute>& );` — Notification when an analytics event needs to be recorded @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param PartyData - data for the game to populate
- L1128 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyAnalyticsEvent);`
- L1134 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(F_PREFIX(OnPartySystemStateChange), EPartySystemState );` — Notification of party system state change @param NewState - new state this partysystem is in
- L1134 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(F_PREFIX(OnPartySystemStateChange), EPartySystemState );` — Notification of party system state change @param NewState - new state this partysystem is in
- L1135 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartySystemStateChange);`
- L1144 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(F_PREFIX(OnPartyRequestToJoinReceived), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const IOnlinePartyRequestToJoinInfo& );` — Notification when a new party join request is received @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param RequesterId - id of player who requested to join @param Request - information regarding the request
- L1144 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(F_PREFIX(OnPartyRequestToJoinReceived), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const IOnlinePartyRequestToJoinInfo& );` — Notification when a new party join request is received @param LocalUserId - id associated with this notification @param PartyId - id associated with the party @param RequesterId - id of player who requested to join @param Request - information regarding the request
- L1145 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyRequestToJoinReceived);`
- L1155 _delegate_ `DECLARE_MULTICAST_DELEGATE_FiveParams(F_PREFIX(OnPartyRequestToJoinRemoved), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const IOnlinePartyRequestToJoinInfo& , EPartyRequestToJoinRemovedReason );` — Notification when a request to join has been removed @param LocalUserId id associated with this notification @param PartyId id associated with the party @param RequesterId - id of player who requested to join @param Request - information regarding the request @param Reason reason the request has been removed
- L1155 _prototype_ `DECLARE_MULTICAST_DELEGATE_FiveParams(F_PREFIX(OnPartyRequestToJoinRemoved), const FUniqueNetId& , const FOnlinePartyId& , const FUniqueNetId& , const IOnlinePartyRequestToJoinInfo& , EPartyRequestToJoinRemovedReason );` — Notification when a request to join has been removed @param LocalUserId id associated with this notification @param PartyId id associated with the party @param RequesterId - id of player who requested to join @param Request - information regarding the request @param Reason reason the request has been removed
- L1156 _prototype_ `PARTY_DECLARE_DELEGATETYPE(OnPartyRequestToJoinRemoved);`
- L2044 _prototype_ `const TCHAR* ToString(const EPartyState Value);` — @return the stringified version of the enum passed in
- L2046 _prototype_ `EPartyState EPartyStateFromString(const TCHAR* Value);` — @return the enum version of the string passed in
- L2049 _prototype_ `const TCHAR* ToString(const EMemberConnectionStatus Value);` — @return the stringified version of the enum passed in
- L2051 _prototype_ `const TCHAR* ToString(const EMemberExitedReason Value);` — @return the stringified version of the enum passed in
- L2053 _prototype_ `const TCHAR* ToString(const EPartyInvitationRemovedReason Value);` — @return the stringified version of the enum passed in
- L2055 _prototype_ `const TCHAR* ToString(const EPartyRequestToJoinRemovedReason Value);` — @return the stringified version of the enum passed in
- L2057 _prototype_ `const TCHAR* ToString(const ECreatePartyCompletionResult Value);` — @return the stringified version of the enum passed in
- L2059 _prototype_ `const TCHAR* ToString(const ESendPartyInvitationCompletionResult Value);` — @return the stringified version of the enum passed in
- L2061 _prototype_ `const TCHAR* ToString(const EJoinPartyCompletionResult Value);` — @return the stringified version of the enum passed in
- L2063 _prototype_ `const TCHAR* ToString(const ELeavePartyCompletionResult Value);` — @return the stringified version of the enum passed in
- L2065 _prototype_ `const TCHAR* ToString(const EUpdateConfigCompletionResult Value);` — @return the stringified version of the enum passed in
- L2067 _prototype_ `const TCHAR* ToString(const EKickMemberCompletionResult Value);` — @return the stringified version of the enum passed in
- L2069 _prototype_ `const TCHAR* ToString(const EPromoteMemberCompletionResult Value);` — @return the stringified version of the enum passed in
- L2071 _prototype_ `const TCHAR* ToString(const EInvitationResponse Value);` — @return the stringified version of the enum passed in
- L2073 _prototype_ `const TCHAR* ToString(const ERequestToJoinPartyCompletionResult Value);` — @return the stringified version of the enum passed in
- L2076 _prototype_ `const TCHAR* ToString(const PartySystemPermissions::EPermissionType Value);` — @return the stringified version of the enum passed in
- L2078 _prototype_ `PartySystemPermissions::EPermissionType PartySystemPermissionTypeFromString(const TCHAR* Value);` — @return the enum version of the string passed in
- L2081 _prototype_ `const TCHAR* ToString(const EJoinRequestAction Value);` — @return the stringified version of the enum passed in
- L2083 _prototype_ `EJoinRequestAction JoinRequestActionFromString(const TCHAR* Value);` — @return the enum version of the string passed in
- L2086 _prototype_ `FString ToDebugString(const FPartyConfiguration& PartyConfiguration);` — Dump party configuration for debugging
- L2088 _prototype_ `FString ToDebugString(const IOnlinePartyJoinInfo& JoinInfo);` — Dump join info for debugging
- L2090 _prototype_ `FString ToDebugString(const FOnlineKeyValuePairs<FString, FVariantData>& KeyValAttrs);` — Dump key/value pairs for debugging
- L2092 _prototype_ `FString ToDebugString(const FOnlinePartyData& PartyData);` — Dump state about the party data for debugging

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlinePlayTimeLimit.h` (Public)


#### class `IOnlinePlayTimeLimit`  
`class IOnlinePlayTimeLimit : public IModularFeature`  
_L24-66_
- inherits: `IModularFeature`
- desc: Interface to provide play time limits
- L28 _public prototype_ `virtual ~IOnlinePlayTimeLimit() = default;` — Destructor
- L34 _public function_ `static FName GetModularFeatureName()` — Get the name of the modular feature, to be used to get the implementations @return name of the modular feature
- L45 _public prototype_ `virtual bool HasTimeLimit(const FUniqueNetId& UserId) = 0;` — Does the user have a play time limit? @param UserId the id of the user to check @return true if the user has a play time limit
- L52 _public prototype_ `virtual int32 GetPlayTimeMinutes(const FUniqueNetId& UserId) = 0;` — Get the play time in minutes for the user @param UserId the id of the user to check @return the play time in minutes for the user
- L60 _public prototype_ `virtual float GetRewardRate(const FUniqueNetId& UserId) = 0;` — Get the reward amount multiplier for the user Expected to start at 1.0 (full rewards), and is reduced based on their play time @param UserId the id of the user to check @return the reward amount multiplier
- L65 _public prototype_ `virtual FWarnUserPlayTime& GetWarnUserPlayTimeDelegate() = 0;` — Delegate called when a warning should be displayed to the user. See FWarnUserPlayTimeDelegate

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_SixParams(FWarnUserPlayTime, const FUniqueNetId& , int32 , float , const FString& , const FString& , const FString& );` — Delegate called to warn a user of their play time amount This is called when RewardRate changes, and periodically to remind the user of their play time @param LocalUserNum the controller number of the associated user @param MinutesPlayed number of minutes the user has played @param RewardRate current rate of rewards for the user
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_SixParams(FWarnUserPlayTime, const FUniqueNetId& , int32 , float , const FString& , const FString& , const FString& );` — Delegate called to warn a user of their play time amount This is called when RewardRate changes, and periodically to remind the user of their play time @param LocalUserNum the controller number of the associated user @param MinutesPlayed number of minutes the user has played @param RewardRate current rate of rewards for the user
- L19 _typedef_ `typedef FWarnUserPlayTime::FDelegate FWarnUserPlayTimeDelegate;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlinePresenceInterface.h` (Public)


#### enum `EOnlinePresenceState::Type`  
`enum Type : uint8`  
_L57-65_
- L59 _public enumerator_ `Online`
- L60 _public enumerator_ `Offline`
- L61 _public enumerator_ `Away`
- L62 _public enumerator_ `ExtendedAway`
- L63 _public enumerator_ `DoNotDisturb`
- L64 _public enumerator_ `Chat`

#### class `FOnlineUserPresenceStatus`  
`class FOnlineUserPresenceStatus`  
_L94-115_
- L97 _public member_ `FString StatusStr;`
- L98 _public member_ `EOnlinePresenceState::Type State;`
- L99 _public member_ `FPresenceProperties Properties;`
- L101 _public function_ `FOnlineUserPresenceStatus() : State(EOnlinePresenceState::Offline)`
- L106 _public function_ `FString ToDebugString() const`

#### struct `FOnlinePresenceSetPresenceParameters`  
`struct FOnlinePresenceSetPresenceParameters`  
_L120-149_
- desc: Parameters to IOnlinePresence::SetPresence. Similar to FOnlineUserPresenceStatus, but fields requesting update must be explicitly set.
- L124 _public member_ `TOptional<FString> StatusStr;` — Updated status string
- L126 _public member_ `TOptional<EOnlinePresenceState::Type> State;` — Updated state
- L128 _public member_ `TOptional<FPresenceProperties> Properties;` — Updated properties. Note that this will update all properties, not just the subset specified in Properties.
- L130 _public function_ `FString ToDebugString() const`

#### class `FOnlineUserPresence`  
`class FOnlineUserPresence`  
_L154-215_
- desc: Presence info for an online user returned via IOnlinePresence interface
- L157 _public member_ `FUniqueNetIdPtr SessionId;`
- L158 _public member_ `uint32 bIsOnline:1;`
- L159 _public member_ `uint32 bIsPlaying:1;`
- L160 _public member_ `uint32 bIsPlayingThisGame:1;`
- L161 _public member_ `uint32 bIsJoinable:1;`
- L162 _public member_ `uint32 bHasVoiceSupport:1;`
- L163 _public member_ `FDateTime LastOnline;`
- L164 _public member_ `FOnlineUserPresenceStatus Status;`
- L167 _public function_ `FOnlineUserPresence()` — Constructor
- L172 _public function_ `void Reset()`
- L184 _public function_ `const FString GetPlatform() const`
- L195 _public function_ `const FString GetAppId() const`
- L211 _public function_ `FString ToDebugString() const`

#### class `IOnlinePresence`  
`class IOnlinePresence`  
_L238-324_
- desc: Interface class for getting and setting rich presence information.
- L242 _public prototype_ `virtual ~IOnlinePresence() = default;` — Virtual destructor to force proper child cleanup
- L250 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnPresenceTaskCompleteDelegate, const class FUniqueNetId& , const bool );` — Delegate executed when setting or querying presence for a user has completed. @param UserId The unique id of the user whose presence was set. @param bWasSuccessful true if the async action completed without error, false if there was an error.
- L259 _public prototype_ `virtual void SetPresence(const FUniqueNetId& User, const FOnlineUserPresenceStatus& Status, const FOnPresenceTaskCompleteDelegate& Delegate = FOnPresenceTaskCompleteDelegate()) = 0;` — Starts an async task that sets presence information for the user. @param User The unique id of the user whose presence is being set. @param Status The collection of state and key/value pairs to set as the user's presence data. @param Delegate The delegate to be executed when the potentially asynchronous set operation completes.
- L268 _public prototype_ `virtual void SetPresence(const FUniqueNetId& User, FOnlinePresenceSetPresenceParameters&& Parameters, const FOnPresenceTaskCompleteDelegate& Delegate = FOnPresenceTaskCompleteDelegate());` — Starts an async task that sets presence information for the user. @param User The unique id of the user whose presence is being set. @param Status The collection of state and key/value pairs to set as the user's presence data. @param Delegate The delegate to be executed when the potentially asynchronous set operation completes.
- L277 _public prototype_ `virtual void QueryPresence(const FUniqueNetId& User, const FOnPresenceTaskCompleteDelegate& Delegate = FOnPresenceTaskCompleteDelegate()) = 0;` — Starts an async operation that will update the cache with presence data from all users in the Users array. On platforms that support multiple keys, this function will query all keys. @param Users The list of unique ids of the users to query for presence information. @param Delegate The delegate to be executed when the potentially asynchronous query operation completes.
- L287 _public function_ `virtual void QueryPresence(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& UserIds, const FOnPresenceTaskCompleteDelegate& Delegate)` — Starts an async operation that will update the cache with presence data from all users in the Users array. On platforms that support multiple keys, this function will query all keys. @param Users The unique id of the user initiating the query for presence information. @param UserIds The list of unique ids of the users to query for presence information. @param Delegate The delegate to be executed when the potentially asynchronous query operation completes.
- L295 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnPresenceReceived, const class FUniqueNetId& , const TSharedRef<FOnlineUserPresence>& );` — Delegate executed when new presence data is available for a user. @param UserId The unique id of the user whose presence was received. @param Presence The presence that was received.
- L303 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnPresenceArrayUpdated, const class FUniqueNetId& , const TArray<TSharedRef<FOnlineUserPresence> >& );` — Delegate executed when the array of presence data for a user changes. @param UserId The unique id of the user whose presence was received. @param PresenceArray The updated presence array
- L312 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedPresence(const FUniqueNetId& User, TSharedPtr<FOnlineUserPresence>& OutPresence) = 0;` — Gets the cached presence information for a user. @param User The unique id of the user from which to get presence information. @param OutPresence If found, a shared pointer to the cached presence data for User will be stored here. @return Whether the data was found or not.
- L323 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedPresenceForApp(const FUniqueNetId& LocalUserId, const FUniqueNetId& User, const FString& AppId, TSharedPtr<FOnlineUserPresence>& OutPresence) = 0;` — Gets the cached presence information for a user. @param LocalUserId The unique id of the local user @param User The unique id of the user from which to get presence information. @param AppId The id of the application you want to get the presence of @param OutPresence If found, a shared pointer to the cached presence data for User will be stored here. @return Whether the data was found or not.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ONLINESUBSYSTEM_API`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlinePresence, Log, All);`
- L15 _macro_ `#define UE_LOG_ONLINE_PRESENCE(Verbosity, Format, ...) \`
- L20 _macro_ `#define UE_CLOG_ONLINE_PRESENCE(Conditional, Verbosity, Format, ...) \`
- L26 _typedef_ `typedef FString FPresenceKey;` — Type of presence keys
- L29 _typedef_ `typedef FOnlineKeyValuePairs<FPresenceKey, FVariantData> FPresenceProperties;` — Type of presence properties - a key/value map
- L32 _externvar_ `extern const FString DefaultPresenceKey;` — The default key that will update presence text in the platform's UI
- L35 _externvar_ `extern const FString CustomPresenceDataKey;` — Custom presence data that is not seen by users but can be polled
- L38 _externvar_ `extern const FString DefaultAppIdKey;` — Name of the client that sent the presence update
- L41 _externvar_ `extern const FString DefaultProductNameKey;` — User friendly name of the client that sent the presence update
- L44 _externvar_ `extern const FString DefaultPlatformKey;` — Platform of the client that sent the presence update
- L47 _externvar_ `extern const FString OverrideAppIdKey;` — Override Id of the client to set the presence state to
- L50 _externvar_ `extern const FString DefaultSessionIdKey;` — Id of the session for the presence update. @todo samz - SessionId on presence data should be FUniqueNetId not uint64
- L53 _externvar_ `extern const FString PresenceResourceKey;` — Resource the client is logged in with
- L55 _namespace_ `namespace EOnlinePresenceState`
- L70 _prototype_ `const TCHAR* ToString(EOnlinePresenceState::Type EnumVal);` (scope `EOnlinePresenceState`) — @return the stringified version of the enum passed in
- L75 _prototype_ `EOnlinePresenceState::Type FromString(const TCHAR* StringVal);` (scope `EOnlinePresenceState`) — @return EOnlinePresenceState from the string passed in
- L78 _externvar_ `extern const FText OnlineText;` (scope `EOnlinePresenceState`) — `UE_DEPRECATED(5.8, "Use ToLocText(EOnlinePresenceState::Online)")`
- L80 _externvar_ `extern const FText OfflineText;` (scope `EOnlinePresenceState`) — `UE_DEPRECATED(5.8, "Use ToLocText(EOnlinePresenceState::Offline)")`
- L82 _externvar_ `extern const FText AwayText;` (scope `EOnlinePresenceState`) — `UE_DEPRECATED(5.8, "Use ToLocText(EOnlinePresenceState::Away)")`
- L84 _externvar_ `extern const FText DoNotDisturbText;` (scope `EOnlinePresenceState`) — `UE_DEPRECATED(5.8, "Use ToLocText(EOnlinePresenceState::DoNotDisturb)")`
- L86 _externvar_ `extern const FText ChatText;` (scope `EOnlinePresenceState`) — `UE_DEPRECATED(5.8, "Use ToLocText(EOnlinePresenceState::Chat)")`
- L91 _prototype_ `const FText ToLocText(EOnlinePresenceState::Type EnumVal);` (scope `EOnlinePresenceState`) — @return the loc text version of the enum passed in
- L223 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresenceReceived, const class FUniqueNetId& , const TSharedRef<FOnlineUserPresence>& );` — Delegate executed when new presence data is available for a user. @param UserId The unique id of the user whose presence was received. @param Presence The received presence
- L223 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresenceReceived, const class FUniqueNetId& , const TSharedRef<FOnlineUserPresence>& );` — Delegate executed when new presence data is available for a user. @param UserId The unique id of the user whose presence was received. @param Presence The received presence
- L224 _typedef_ `typedef FOnPresenceReceived::FDelegate FOnPresenceReceivedDelegate;`
- L232 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresenceArrayUpdated, const class FUniqueNetId& , const TArray<TSharedRef<FOnlineUserPresence> >& );` — Delegate executed when the array of presence data for a user changes. @param UserId The unique id of the user whose presence was received. @param PresenceArray The updated presence array
- L232 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresenceArrayUpdated, const class FUniqueNetId& , const TArray<TSharedRef<FOnlineUserPresence> >& );` — Delegate executed when the array of presence data for a user changes. @param UserId The unique id of the user whose presence was received. @param PresenceArray The updated presence array
- L233 _typedef_ `typedef FOnPresenceArrayUpdated::FDelegate FOnPresenceArrayUpdatedDelegate;`
- L250 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnPresenceTaskCompleteDelegate, const class FUniqueNetId& , const bool );` — Delegate executed when setting or querying presence for a user has completed. @param UserId The unique id of the user whose presence was set. @param bWasSuccessful true if the async action completed without error, false if there was an error.

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlinePurchaseInterface.h` (Public)


#### class `FPurchaseCheckoutRequest`  
`class FPurchaseCheckoutRequest`  
_L30-72_
- desc: Info needed for checkout
- L41 _public function_ `void AddPurchaseOffer(const FOfferNamespace& InNamespace, const FUniqueOfferId& InOfferId, int32 InQuantity, bool bInIsConsumable = true)` — Add a offer entry for purchase @param InNamespace namespace of offer to be purchased @param InOfferId id of offer to be purchased @param InQuantity number to purchase @param bInIsConsumable is the offer consumable or one time purchase
- L64 _public member_ `TArray<FPurchaseOfferEntry> PurchaseOffers;` — List of offers being purchased
- L67 _public member_ `TOptional<FString> AccountId;` — Optional AccountId to include with the purchase request (if supported)
- L70 _public member_ `TMap<FString, FString> AdditionalCheckoutProperties;` — Key - value pair properties for passing to the checkout.

#### struct `FPurchaseCheckoutRequest::FPurchaseOfferEntry`  
`struct FPurchaseOfferEntry`  
_L48-62_
- desc: Single offer entry for purchase
- L50 _public function_ `FPurchaseOfferEntry(const FOfferNamespace& InOfferNamespace, const FUniqueOfferId& InOfferId, int32 InQuantity, bool bInIsConsumable) : OfferNamespace(InOfferNamespace) , OfferId(InOfferId) , Quantity(InQuantity)`
- L57 _public member_ `FOfferNamespace OfferNamespace;` — Namespace in which the offer resides
- L59 _public member_ `FUniqueOfferId OfferId;` — Platform specific offer id (defined on backend)
- L61 _public member_ `int32 Quantity;` — Number of offers of this type to purchase

#### enum `EPurchaseTransactionState`  
`enum class EPurchaseTransactionState : uint8`  
_L77-97_
- desc: State of a purchase transaction
- L80 _public enumerator_ `NotStarted` — processing has not started on the purchase
- L82 _public enumerator_ `Processing` — currently processing the purchase
- L84 _public enumerator_ `Purchased` — purchase completed successfully
- L86 _public enumerator_ `Failed` — purchase completed but failed
- L88 _public enumerator_ `Deferred` — purchase has been deferred (neither failed nor completed)
- L90 _public enumerator_ `Canceled` — purchase canceled by user
- L92 _public enumerator_ `Restored` — prior purchase that has been restored
- L94 _public enumerator_ `NotAllowed` — purchase failed as not allowed
- L96 _public enumerator_ `Invalid` — purchase failed as invalid

#### class `FPurchaseReceipt`  
`class FPurchaseReceipt : public FJsonSerializable`  
_L102-200_
- inherits: `FJsonSerializable`
- desc: Receipt result from checkout
- L106 _public function_ `FPurchaseReceipt() : TransactionState(EPurchaseTransactionState::NotStarted)`
- L172 _public function_ `void AddReceiptOffer(const FOfferNamespace& InNamespace, const FUniqueOfferId& InOfferId, int32 InQuantity)` — Add a offer entry that has been purchased @param InNamespace of the offer that has been purchased @param InOfferId id of offer that has been purchased @param InQuantity number purchased
- L177 _public function_ `void AddReceiptOffer(const FReceiptOfferEntry& ReceiptOffer)`
- L182 _public function_ `void AddReceiptOffer(FReceiptOfferEntry&& ReceiptOffer)`
- L194 _public member_ `FString TransactionId;` — Unique Id for this transaction/order
- L196 _public member_ `EPurchaseTransactionState TransactionState;` — Current state of the purchase
- L199 _public member_ `TArray<FReceiptOfferEntry> ReceiptOffers;` — List of offers that were purchased

#### struct `FPurchaseReceipt::FLineItemInfo`  
`struct FLineItemInfo : public FJsonSerializable`  
_L111-130_
- inherits: `FJsonSerializable`
- L115 _public member_ `FString ItemName;` — The platform identifier of this purchase type
- L118 _public member_ `FUniqueEntitlementId UniqueId;` — unique identifier representing this purchased item (the specific instance owned by this account)
- L121 _public member_ `FString ValidationInfo;` — platform-specific opaque validation info (required to verify UniqueId belongs to this account)
- L123 _public function_ `inline bool IsRedeemable() const`

#### struct `FPurchaseReceipt::FReceiptOfferEntry`  
`struct FReceiptOfferEntry : public FJsonSerializable`  
_L135-163_
- inherits: `FJsonSerializable`
- desc: Single purchased offer offer
- L138 _public function_ `FReceiptOfferEntry() : Quantity(0)`
- L143 _public function_ `FReceiptOfferEntry(const FOfferNamespace& InNamespace, const FUniqueOfferId& InOfferId, int32 InQuantity) : Namespace(InNamespace) , OfferId(InOfferId) , Quantity(InQuantity)`
- L150 _public member_ `FOfferNamespace Namespace;`
- L151 _public member_ `FUniqueOfferId OfferId;`
- L152 _public member_ `int32 Quantity;`
- L155 _public member_ `TArray<FLineItemInfo> LineItems;` — Information about the individual items purchased

#### class `FRedeemCodeRequest`  
`class FRedeemCodeRequest`  
_L205-216_
- desc: Info needed for code redemption
- L209 _public member_ `FString Code;` — Code to redeem
- L212 _public member_ `FString CodeUseId;` — Optional CodeUseId that was given if code was previously locked before redeeming - See IOnlineCodeRedemption::LockCode
- L215 _public member_ `FString FulfillmentSource;` — Where this code is being fulfilled from - e.g. Launcher, GameName

#### class `IOnlinePurchase`  
`class IOnlinePurchase`  
_L264-387_
- desc: IOnlinePurchase - Interface for IAP (In App Purchases) services
- L267 _public prototype_ `virtual ~IOnlinePurchase() = default;`
- L276 _public prototype_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId) = 0;` — Determine if user is allowed to purchase on this platform from a policy or permission perspective @param UserId user initiating the request @return true if user is allowed to make a purchase
- L287 _public prototype_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId, FOnlineError& Error) = 0;` — Determine if user is allowed to purchase from store on this platform from a policy or permission perspective @param UserId user initiating the request @param Error an error result indicating why the the user isn't allowed when relevant and available. @return true if user is allowed to make a purchase
- L296 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseCheckoutComplete& Delegate) = 0;` — Initiate the checkout process for purchasing offers via payment @param UserId user initiating the request @param CheckoutRequest info needed for the checkout request @param Delegate completion callback (guaranteed to be called)
- L307 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseReceiptlessCheckoutComplete& Delegate) = 0;` — Initiate the checkout process for purchasing offers via payment without receipts returned Recommended for use when the entitlement or receipt information of the purchase is not needed by the caller @param UserId user initiating the request @param CheckoutRequest info needed for the checkout request @param Delegate completion callback (guaranteed to be called)
- L316 _public prototype_ `virtual void FinalizePurchase(const FUniqueNetId& UserId, const FString& ReceiptId) = 0;` — Finalizes a purchase with the supporting platform Acknowledges that the purchase has been properly redeemed by the application @param UserId user where the purchase was made @param ReceiptId purchase id for this platform
- L326 _public function_ `virtual void FinalizePurchase(const FUniqueNetId& UserId, const FString& ReceiptId, const FString& ReceiptInfo)` — Finalizes a purchase with the supporting platform Acknowledges that the purchase has been properly redeemed by the application. Prefer this overload whenever the validation info is available. @param UserId user where the purchase was made @param ReceiptId purchase id for this platform @param ReceiptInfo the receipt validation info for this platform
- L339 _public prototype_ `virtual void RedeemCode(const FUniqueNetId& UserId, const FRedeemCodeRequest& RedeemCodeRequest, const FOnPurchaseRedeemCodeComplete& Delegate) = 0;` — Initiate the checkout process for obtaining offers via code redemption @param UserId user initiating the request @param RedeemCodeRequest info needed for the redeem request @param Delegate completion callback (guaranteed to be called)
- L348 _public prototype_ `virtual void QueryReceipts(const FUniqueNetId& UserId, bool bRestoreReceipts, const FOnQueryReceiptsComplete& Delegate) = 0;` — Query for all of the user's receipts from prior purchases @param UserId user initiating the request @param bRestoreReceipts initiate recovery of any receipts on the specific platform @param Delegate completion callback (guaranteed to be called)
- L356 _public prototype_ `virtual void GetReceipts(const FUniqueNetId& UserId, TArray<FPurchaseReceipt>& OutReceipts) const = 0;` — Get list of cached receipts for user (includes transactions currently being processed) @param UserId user initiating the request @param OutReceipts [out] list of receipts for the user
- L358 _public prototype_ `virtual void FinalizeReceiptValidationInfo(const FUniqueNetId& UserId, FString& InReceiptValidationInfo, const FOnFinalizeReceiptValidationInfoComplete& Delegate) = 0;`
- L365 _public function_ `virtual void ShowAlternativeBillingInformationDialog(const FOnShowAlternativeBillingInformationDialogComplete& Delegate)` — If the underlying IAP service requires an informational dialog to be shown, show it and trigger the delegate on completion with the status @param Delegate completion callback (guaranteed to be called)
- L373 _public function_ `virtual void RequestExternalPurchaseToken(const FOnRequestExternalPurchaseTokenComplete& Delegate) const` — If the underlying IAP service supports external purchase tokens, request external purchase token @param Delegate completion callback
- L383 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnUnexpectedPurchaseReceipt, const FUniqueNetId& );` — Delegate fired when the local system tells us of a new completed purchase we may not have initiated in-game. Use this to know about new pending receipts in instances the local client did not start a purchase, such as when the application is in the background. @param UserId The beneficiary of this new receipt
- L386 _private prototype_ `void OnRedirectToCheckoutComplete(const FOnlineError& ErrorResult, const TSharedRef<FPurchaseReceipt>& Receipt, const FOnPurchaseReceiptlessCheckoutComplete Delegate);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define PURCHASE_REDEMPTION_CODE_USED "errors.com.epicgames.coderedemption.code_used"`
- L12 _macro_ `#define PURCHASE_REDEMPTION_CODE_NOT_FOUND "errors.com.epicgames.coderedemption.code_not_found"`
- L13 _macro_ `#define PURCHASE_REDEMPTION_NOT_ELIGIBLE "errors.com.epicgames.ecommerce.fulfillment.code.criteria.reject"`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlinePurchase, Log, All);`
- L17 _macro_ `#define UE_LOG_ONLINE_PURCHASE(Verbosity, Format, ...) \`
- L22 _macro_ `#define UE_CLOG_ONLINE_PURCHASE(Conditional, Verbosity, Format, ...) \`
- L221 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnPurchaseCheckoutComplete, const FOnlineError& , const TSharedRef<FPurchaseReceipt>& );` — Delegate called when checkout process completes
- L221 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnPurchaseCheckoutComplete, const FOnlineError& , const TSharedRef<FPurchaseReceipt>& );` — Delegate called when checkout process completes
- L226 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPurchaseReceiptlessCheckoutComplete, const FOnlineError& );` — Delegate called when checkout process completes, this delegate is used when the entitlement or receipt information of the purchase is not needed by the caller.
- L226 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPurchaseReceiptlessCheckoutComplete, const FOnlineError& );` — Delegate called when checkout process completes, this delegate is used when the entitlement or receipt information of the purchase is not needed by the caller.
- L231 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnPurchaseRedeemCodeComplete, const FOnlineError& , const TSharedRef<FPurchaseReceipt>& );` — Delegate called when code redemption process completes
- L231 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnPurchaseRedeemCodeComplete, const FOnlineError& , const TSharedRef<FPurchaseReceipt>& );` — Delegate called when code redemption process completes
- L236 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQueryReceiptsComplete, const FOnlineError& );` — Delegate called when query receipt process completes
- L236 _prototype_ `DECLARE_DELEGATE_OneParam(FOnQueryReceiptsComplete, const FOnlineError& );` — Delegate called when query receipt process completes
- L241 _delegate_ `DECLARE_DELEGATE_OneParam(FOnShowAlternativeBillingInformationDialogComplete, const FOnlineError& );` — Delegate called when the information dialog shows and completes
- L241 _prototype_ `DECLARE_DELEGATE_OneParam(FOnShowAlternativeBillingInformationDialogComplete, const FOnlineError& );` — Delegate called when the information dialog shows and completes
- L246 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnFinalizeReceiptValidationInfoComplete, const FOnlineError& , const FString& );` — Delegate called when receipt validation completes
- L246 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnFinalizeReceiptValidationInfoComplete, const FOnlineError& , const FString& );` — Delegate called when receipt validation completes
- L251 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnexpectedPurchaseReceipt, const FUniqueNetId& );` — Delegate called when we are informed of a new receipt we did not initiate in-game
- L251 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnexpectedPurchaseReceipt, const FUniqueNetId& );` — Delegate called when we are informed of a new receipt we did not initiate in-game
- L252 _typedef_ `typedef FOnUnexpectedPurchaseReceipt::FDelegate FOnUnexpectedPurchaseReceiptDelegate;`
- L258 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRequestExternalPurchaseTokenComplete, bool , FString );` — If the underlying store supports it, delegate which is executed when external purchase token request completes
- L258 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnRequestExternalPurchaseTokenComplete, bool , FString );` — If the underlying store supports it, delegate which is executed when external purchase token request completes
- L389 _function_ `inline const TCHAR* LexToString(EPurchaseTransactionState State)`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineSessionDelegates.h` (Public)


#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCreateSessionComplete, FName, bool);` — Delegate fired when a session create request has completed @param SessionName the name of the session this callback is for @param bWasSuccessful true if the async action completed without error, false if there was an error
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCreateSessionComplete, FName, bool);` — Delegate fired when a session create request has completed @param SessionName the name of the session this callback is for @param bWasSuccessful true if the async action completed without error, false if there was an error
- L14 _typedef_ `typedef FOnCreateSessionComplete::FDelegate FOnCreateSessionCompleteDelegate;`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStartSessionComplete, FName, bool);` — Delegate fired when the online session has transitioned to the started state @param SessionName the name of the session the that has transitioned to started @param bWasSuccessful true if the async action completed without error, false if there was an error
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStartSessionComplete, FName, bool);` — Delegate fired when the online session has transitioned to the started state @param SessionName the name of the session the that has transitioned to started @param bWasSuccessful true if the async action completed without error, false if there was an error
- L23 _typedef_ `typedef FOnStartSessionComplete::FDelegate FOnStartSessionCompleteDelegate;`
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdateSessionComplete, FName, bool);` — Delegate fired when a update session request has completed @param SessionName the name of the session this callback is for @param bWasSuccessful true if the async action completed without error, false if there was an error
- L31 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdateSessionComplete, FName, bool);` — Delegate fired when a update session request has completed @param SessionName the name of the session this callback is for @param bWasSuccessful true if the async action completed without error, false if there was an error
- L32 _typedef_ `typedef FOnUpdateSessionComplete::FDelegate FOnUpdateSessionCompleteDelegate;`
- L40 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEndSessionComplete, FName, bool);` — Delegate fired when the online session has transitioned to the ending state @param SessionName the name of the session the that was ended @param bWasSuccessful true if the async action completed without error, false if there was an error
- L40 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEndSessionComplete, FName, bool);` — Delegate fired when the online session has transitioned to the ending state @param SessionName the name of the session the that was ended @param bWasSuccessful true if the async action completed without error, false if there was an error
- L41 _typedef_ `typedef FOnEndSessionComplete::FDelegate FOnEndSessionCompleteDelegate;`
- L49 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroySessionComplete, FName, bool);` — Delegate fired when a destroying an online session has completed @param SessionName the name of the session this callback is for @param bWasSuccessful true if the async action completed without error, false if there was an error
- L49 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroySessionComplete, FName, bool);` — Delegate fired when a destroying an online session has completed @param SessionName the name of the session this callback is for @param bWasSuccessful true if the async action completed without error, false if there was an error
- L50 _typedef_ `typedef FOnDestroySessionComplete::FDelegate FOnDestroySessionCompleteDelegate;`
- L58 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMatchmakingComplete, FName, bool);` — Broadcast delegate fired when the Matchmaking for an online session has completed @param SessionName the name of the session the that can now be joined (on success) @param bWasSuccessful true if the async action completed without error, false if there was an error
- L58 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMatchmakingComplete, FName, bool);` — Broadcast delegate fired when the Matchmaking for an online session has completed @param SessionName the name of the session the that can now be joined (on success) @param bWasSuccessful true if the async action completed without error, false if there was an error
- L59 _typedef_ `typedef FOnMatchmakingComplete::FDelegate FOnMatchmakingCompleteDelegate;`
- L69 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnStartMatchmakingComplete, FName , const struct FOnlineError& , const struct FSessionMatchmakingResults& );` — Delegate fired when StartMatchmaking completes Related to FOnMatchmakingComplete, but this is not a broadcast delegate @param SessionName the name of the session that was passed to StartMatchmaking @param ErrorDetails extended details of the failure (if failed) @param Results results of matchmaking (if succeeded)
- L69 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnStartMatchmakingComplete, FName , const struct FOnlineError& , const struct FSessionMatchmakingResults& );` — Delegate fired when StartMatchmaking completes Related to FOnMatchmakingComplete, but this is not a broadcast delegate @param SessionName the name of the session that was passed to StartMatchmaking @param ErrorDetails extended details of the failure (if failed) @param Results results of matchmaking (if succeeded)
- L77 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCancelMatchmakingComplete, FName, bool);` — Delegate fired when the Matchmaking request has been canceled @param SessionName the name of the session that was passed to CancelMatchmaking @param bWasSuccessful true if the async action completed without error, false if there was an error
- L77 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCancelMatchmakingComplete, FName, bool);` — Delegate fired when the Matchmaking request has been canceled @param SessionName the name of the session that was passed to CancelMatchmaking @param bWasSuccessful true if the async action completed without error, false if there was an error
- L78 _typedef_ `typedef FOnCancelMatchmakingComplete::FDelegate FOnCancelMatchmakingCompleteDelegate;`
- L85 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFindSessionsComplete, bool);` — Delegate fired when the search for an online session has completed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L85 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFindSessionsComplete, bool);` — Delegate fired when the search for an online session has completed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L86 _typedef_ `typedef FOnFindSessionsComplete::FDelegate FOnFindSessionsCompleteDelegate;`
- L93 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCancelFindSessionsComplete, bool);` — Delegate fired when the cancellation of a search for an online session has completed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L93 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCancelFindSessionsComplete, bool);` — Delegate fired when the cancellation of a search for an online session has completed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L94 _typedef_ `typedef FOnCancelFindSessionsComplete::FDelegate FOnCancelFindSessionsCompleteDelegate;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineSessionInterface.h` (Public)


#### enum `EOnJoinSessionCompleteResult::Type`  
`enum Type`  
_L30-44_
- L33 _public enumerator_ `Success` — The join worked as expected
- L35 _public enumerator_ `SessionIsFull` — There are no open slots to join
- L37 _public enumerator_ `SessionDoesNotExist` — The session couldn't be found on the service
- L39 _public enumerator_ `CouldNotRetrieveAddress` — There was an error getting the session server's address
- L41 _public enumerator_ `AlreadyInSession` — The user attempting to join is already a member of the session
- L43 _public enumerator_ `UnknownError` — An error not covered above occurred

#### enum `EOnSessionParticipantLeftReason`  
`enum class EOnSessionParticipantLeftReason : uint8`  
_L88-98_
- desc: Possible motives for a participant leaving an online session
- L91 _public enumerator_ `Left` — The participant left the session of their own accord
- L93 _public enumerator_ `Disconnected` — The participant got disconnected from a session that is still active
- L95 _public enumerator_ `Kicked` — The participant was forcefully removed from the session
- L97 _public enumerator_ `Closed` — The session ended and the participant got removed from it

#### enum `ESessionFailure::Type`  
`enum Type`  
_L224-228_
- L227 _public enumerator_ `ServiceConnectionLost` — General loss of connection

#### struct `FSessionMatchmakingUser`  
`struct FSessionMatchmakingUser`  
_L263-269_
- desc: Attributes for a matchmaking user
- L266 _public member_ `FUniqueNetIdRef UserId;` — Id of the user
- L268 _public member_ `FOnlineKeyValuePairs<FString, FVariantData> Attributes;` — Attributes for the user

#### struct `FSessionMatchmakingResults`  
`struct FSessionMatchmakingResults`  
_L272-275_
- desc: Matchmaking results

#### class `IOnlineSession`  
`class IOnlineSession`  
_L282-931_
- desc: Interface definition for the online services session services Session services are defined as anything related managing a session and its state within a platform service
- L287 _protected function_ `IOnlineSession()` — Hidden on purpose
- L297 _protected prototype_ `virtual class FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSessionSettings& SessionSettings) = 0;` — Adds a new named session to the list (new session) @param SessionName the name to search for @param GameSettings the game settings to add @return a pointer to the struct that was added
- L307 _protected prototype_ `virtual class FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSession& Session) = 0;` — Adds a new named session to the list (from existing session data) @param SessionName the name to search for @param GameSettings the game settings to add @return a pointer to the struct that was added
- L310 _public prototype_ `virtual ~IOnlineSession() = default;`
- L317 _public prototype_ `virtual FUniqueNetIdPtr CreateSessionIdFromString(const FString& SessionIdStr) = 0;` — Create a session id from a string @param SessionIdStr the string representation of the session id @return a session id, or nullptr if SessionIdStr is invalid
- L326 _public prototype_ `virtual class FNamedOnlineSession* GetNamedSession(FName SessionName) = 0;` — Searches the named session array for the specified session @param SessionName the name to search for @return pointer to the struct if found, NULL otherwise
- L333 _public prototype_ `virtual void RemoveNamedSession(FName SessionName) = 0;` — Searches the named session array for the specified session and removes it @param SessionName the name to search for
- L338 _public prototype_ `virtual bool HasPresenceSession() = 0;` — Searches the named session array for any presence enabled session
- L347 _public prototype_ `virtual EOnlineSessionState::Type GetSessionState(FName SessionName) const = 0;` — Get the current state of a named session @param SessionName name of session to query @return State of specified session
- L360 _public prototype_ `virtual bool CreateSession(int32 HostingPlayerNum, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) = 0;` — Creates an online session based upon the settings object specified. NOTE: online session registration is an async process and does not complete until the OnCreateSessionComplete delegate is called. @param HostingPlayerNum the index of the player hosting the session @param SessionName the name to use for this session so that multiple sessions can exist at the same time @param NewSessionSettings the settings to use for the new session @return true if successful creating the session, false otherwise
- L373 _public prototype_ `virtual bool CreateSession(const FUniqueNetId& HostingPlayerId, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) = 0;` — Creates an online session based upon the settings object specified. NOTE: online session registration is an async process and does not complete until the OnCreateSessionComplete delegate is called. @param HostingPlayerId the index of the player hosting the session @param SessionName the name to use for this session so that multiple sessions can exist at the same time @param NewSessionSettings the settings to use for the new session @return true if successful creating the session, false otherwise
- L381 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnCreateSessionComplete, FName, bool);` — Delegate fired when a session create request has completed @param SessionName the name of the session this callback is for @param bWasSuccessful true if the async action completed without error, false if there was an error
- L390 _public prototype_ `virtual bool StartSession(FName SessionName) = 0;` — Marks an online session as in progress (as opposed to being in lobby or pending) @param SessionName the name of the session that is being started @return true if the call succeeds, false otherwise
- L398 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnStartSessionComplete, FName, bool);` — Delegate fired when the online session has transitioned to the started state @param SessionName the name of the session the that has transitioned to started @param bWasSuccessful true if the async action completed without error, false if there was an error
- L409 _public prototype_ `virtual bool UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings, bool bShouldRefreshOnlineData = true) = 0;` — Updates the localized settings/properties for the session in question @param SessionName the name of the session to update @param UpdatedSessionSettings the object to update the session settings with @param bShouldRefreshOnlineData whether to submit the data to the backend or not @return true if successful creating the session, false otherwise
- L417 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnUpdateSessionComplete, FName, bool);` — Delegate fired when a update request has completed @param SessionName the name of the session this callback is for @param bWasSuccessful true if the async action completed without error, false if there was an error
- L426 _public prototype_ `virtual bool EndSession(FName SessionName) = 0;` — Marks an online session as having been ended @param SessionName the name of the session the to end @return true if the call succeeds, false otherwise
- L434 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnEndSessionComplete, FName, bool);` — Delegate fired when the online session has transitioned to the ending state @param SessionName the name of the session the that was ended @param bWasSuccessful true if the async action completed without error, false if there was an error
- L445 _public prototype_ `virtual bool DestroySession(FName SessionName, const FOnDestroySessionCompleteDelegate& CompletionDelegate = FOnDestroySessionCompleteDelegate()) = 0;` — Destroys the specified online session NOTE: online session de-registration is an async process and does not complete until the OnDestroySessionComplete delegate is called. @param SessionName the name of the session to delete @return true if successful destroying the session, false otherwise
- L453 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnDestroySessionComplete, FName, bool);` — Delegate fired when a destroying an online session has completed @param SessionName the name of the session this callback is for @param bWasSuccessful true if the async action completed without error, false if there was an error
- L461 _public prototype_ `virtual bool IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId) = 0;` — Determine if the player is registered in the specified session @param UniqueId the player to check if in session or not @return true if the player is registered in the session
- L473 _public prototype_ `virtual bool StartMatchmaking(const TArray< FUniqueNetIdRef >& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings) = 0;` — Begins cloud based matchmaking for a session @param LocalPlayers the ids of all local players that will participate in the match @param SessionName the name of the session to use, usually will be GAME_SESSION_NAME @param NewSessionSettings the desired settings to match against or create with when forming new sessions @param SearchSettings the desired settings that the matched session will have @return true if successful searching for sessions, false otherwise
- L485 _public prototype_ `virtual bool StartMatchmaking(const TArray<FSessionMatchmakingUser>& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings, const FOnStartMatchmakingComplete& CompletionDelegate);` — Begins cloud based matchmaking for a session @param LocalPlayers the ids of all local players that will participate in the match @param SessionName the name of the session to use, usually will be GAME_SESSION_NAME @param NewSessionSettings the desired settings to match against or create with when forming new sessions @param SearchSettings the desired settings that the matched session will have @return true if successful searching for sessions, false otherwise
- L493 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnMatchmakingComplete, FName, bool);` — Delegate fired when the cloud matchmaking has completed @param SessionName The name of the session that was found via matchmaking @param bWasSuccessful true if the async action completed without error, false if there was an error
- L501 _public prototype_ `virtual bool CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName) = 0;` — Cancel a Matchmaking request for a given session name @param SearchingPlayerNum the index of the player canceling the search @param SessionName the name of the session that was passed to StartMatchmaking (or CreateSession)
- L509 _public prototype_ `virtual bool CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, FName SessionName) = 0;` — Cancel a Matchmaking request for a given session name @param SearchingPlayerId the id of the player canceling the search @param SessionName the name of the session that was passed to StartMatchmaking (or CreateSession)
- L517 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnCancelMatchmakingComplete, FName, bool);` — Delegate fired when the cloud matchmaking has been canceled @param SessionName the name of the session that was canceled @param bWasSuccessful true if the async action completed without error, false if there was an error
- L527 _public prototype_ `virtual bool FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings) = 0;` — Searches for sessions matching the settings specified @param SearchingPlayerNum the index of the player searching for a match @param SearchSettings the desired settings that the returned sessions will have @return true if successful searching for sessions, false otherwise
- L537 _public prototype_ `virtual bool FindSessions(const FUniqueNetId& SearchingPlayerId, const TSharedRef<FOnlineSessionSearch>& SearchSettings) = 0;` — Searches for sessions matching the settings specified @param SearchingPlayerId the id of the player searching for a match @param SearchSettings the desired settings that the returned sessions will have @return true if successful searching for sessions, false otherwise
- L544 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnFindSessionsComplete, bool);` — Delegate fired when the search for an online session has completed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L557 _public prototype_ `virtual bool FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId, const FUniqueNetId& FriendId, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate) = 0;` — Find a single advertised session by session id @param SearchingUserId user initiating the request @param Platform platform the session is on @param SessionId session id to search for @param FriendId optional id of user to verify in session @param CompletionDelegate delegate to call on completion @return true on success, false otherwise
- L571 _public function_ `virtual bool FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId, const FUniqueNetId& FriendId, const FString& UserData, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate)` — Find a single advertised session by session id (with userdata) @param SearchingUserId user initiating the request @param Platform platform the session is on @param SessionId session id to search for @param FriendId optional id of user to verify in session @param UserData optional data that may be required by search @param CompletionDelegate delegate to call on completion @return true on success, false otherwise
- L581 _public prototype_ `virtual bool CancelFindSessions() = 0;` — Cancels the current search in progress if possible for that search type @return true if successful searching for sessions, false otherwise
- L588 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnCancelFindSessionsComplete, bool);` — Delegate fired when the cancellation of a search for an online session has completed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L598 _public prototype_ `virtual bool PingSearchResults(const FOnlineSessionSearchResult& SearchResult) = 0;` — Fetches the additional data a session exposes outside of the online service. NOTE: notifications will come from the OnPingSearchResultsComplete delegate @param SearchResult the specific search result to query @return true if the query was started, false otherwise
- L605 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnPingSearchResultsComplete, bool);` — Delegate fired when an individual server's query has completed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L616 _public prototype_ `virtual bool JoinSession(int32 LocalUserNum, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) = 0;` — Joins the session specified @param LocalUserNum the index of the player searching for a match @param SessionName the name of the session to join @param DesiredSession the desired session to join @return true if the call completed successfully, false otherwise
- L627 _public prototype_ `virtual bool JoinSession(const FUniqueNetId& LocalUserId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) = 0;` — Joins the session specified @param LocalUserId the id of the player searching for a match @param SessionName the name of the session to join @param DesiredSession the desired session to join @return true if the call completed successfully, false otherwise
- L636 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnJoinSessionComplete, FName, EOnJoinSessionCompleteResult::Type);` — Delegate fired when the process for a local user joining an online session has completed @param SessionName the name of the session this callback is for @param Result EOnJoinSessionCompleteResult describing the outcome of the call
- L643 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnSessionParticipantJoined, FName, const FUniqueNetId&);` — Delegate fired when a player joins a session @param SessionName The name of the session @param UniqueId The ID of the user who joined
- L651 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnSessionParticipantLeft, FName, const FUniqueNetId&, EOnSessionParticipantLeftReason);` — Delegate fired when a player leaves a session @param SessionName The name of the session @param UniqueId The ID of the user who left @param LeaveReason An enum defining the motive for the participant's leave
- L657 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnQosDataRequested, FName);` — Delegate fired when session is requesting QOS measurements @param The name of the session for which the measurements need to be made
- L665 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnSessionSettingsUpdated, FName, const FOnlineSessionSettings&);` — Delegate fired when a session's settings have changed @param SessionName The name of the session that had its settings changed @param SessionSettings The updated session settings
- L674 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnSessionParticipantSettingsUpdated, FName, const FUniqueNetId&, const FOnlineSessionSettings&);` — Delegate fired when a session's member settings have changed @param SessionName The name of the session that had a member's settings changed @param TargetUniqueNetId The UniqueNetId of the member whose settings changed @param SessionSettings The updated member settings
- L684 _public prototype_ `virtual bool FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend) = 0;` — Allows the local player to follow a friend into a session @param LocalUserNum the local player wanting to join @param Friend the player that is being followed @return true if the async call worked, false otherwise
- L694 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend) = 0;` — Allows the local player to follow a friend into a session @param LocalUserId the local player wanting to join @param Friend the player that is being followed @return true if the async call worked, false otherwise
- L704 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& FriendList) = 0;` — Allows the local player to retrieve the session of multiple friends @param LocalUserId the local player wanting to join @param FriendList the potential players to follow @return true if the async call worked, false otherwise
- L714 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_TWO_PARAM(MAX_LOCAL_PLAYERS, OnFindFriendSessionComplete, bool, const TArray<FOnlineSessionSearchResult>&);` — Delegate fired once the find friend task has completed Session has not been joined at this point, and still requires a call to JoinSession() @param LocalUserNum the controller number of the accepting user @param bWasSuccessful the session was found and is joinable, false otherwise @param FriendSearchResult the search/settings for the session we're attempting to join
- L725 _public prototype_ `virtual bool SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend) = 0;` — Sends an invitation to play in the player's current session @param LocalUserNum the user that is sending the invite @param SessionName session to invite them to @param Friend the player to send the invite to @return true if successful, false otherwise
- L736 _public prototype_ `virtual bool SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName, const FUniqueNetId& Friend) = 0;` — Sends an invitation to play in the player's current session @param LocalUserId the user that is sending the invite @param SessionName session to invite them to @param Friend the player to send the invite to @return true if successful, false otherwise
- L747 _public prototype_ `virtual bool SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) = 0;` — Sends invitations to play in the player's current session @param LocalUserNum the user that is sending the invite @param SessionName session to invite them to @param Friends the player to send the invite to @return true if successful, false otherwise
- L758 _public prototype_ `virtual bool SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) = 0;` — Sends invitations to play in the player's current session @param LocalUserId the user that is sending the invite @param SessionName session to invite them to @param Friends the player to send the invite to @return true if successful, false otherwise
- L770 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnSessionUserInviteAccepted, const bool , const int32 , FUniqueNetIdPtr , const FOnlineSessionSearchResult& );` — Called when a user accepts a session invitation. Allows the game code a chance to clean up any existing state before accepting the invite. The invite must be accepted by calling JoinSession() after clean up has completed @param bWasSuccessful true if the async action completed without error, false if there was an error @param ControllerId the controller number of the accepting user @param UserId the user being invited @param InviteResult the search/settings for the session we're joining via invite
- L781 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnSessionInviteReceived, const FUniqueNetId& , const FUniqueNetId& , const FString& , const FOnlineSessionSearchResult& );` — Called when a user receives a session invitation. Allows the game code to decide on accepting the invite. The invite can be accepted by calling JoinSession() @param UserId the user being invited @param FromId the user that sent the invite @param AppId the id of the client/app user was in when sending hte game invite @param InviteResult the search/settings for the session we're joining via invite
- L793 _public prototype_ `virtual bool GetResolvedConnectString(FName SessionName, FString& ConnectInfo, FName PortType = NAME_GamePort) = 0;` — Returns the platform specific connection information for joining the match. Call this function from the delegate of join completion @param SessionName the name of the session to resolve @param ConnectInfo the string containing the platform specific connection information @param PortType type of port to append to result (Game, Beacon, etc) @return true if the call was successful, false otherwise
- L804 _public prototype_ `virtual bool GetResolvedConnectString(const class FOnlineSessionSearchResult& SearchResult, FName PortType, FString& ConnectInfo) = 0;` — Returns the platform specific connection information for joining a search result. @param SearchResult the search result to get connection info from @param PortType type of port to append to result (Game, Beacon, etc) @param ConnectInfo the string containing the platform specific connection information @return true if the call was successful, false otherwise
- L813 _public prototype_ `virtual FOnlineSessionSettings* GetSessionSettings(FName SessionName) = 0;` — Returns the session settings object for the session with a matching name @param SessionName the name of the session to return @return the settings for this session name
- L823 _public prototype_ `virtual FString GetVoiceChatRoomName(int32 LocalUserNum, const FName& SessionName);` — Returns the name for the Voice Chat room, if any were created by setting bUseLobbiesVoiceChatIfAvailable to true during session creation @param LocalUserNum the user asking for the room name @param SessionName the name of the related session @return the name for the corresponding Voice Chat room, or an empty FString if there is none
- L834 _public prototype_ `virtual bool RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited) = 0;` — Registers a player with the online service as being part of the online session @param SessionName the name of the session the player is joining @param UniquePlayerId the player to register with the online service @param bWasInvited whether the player was invited to the session or searched for it @return true if the call succeeds, false otherwise
- L845 _public prototype_ `virtual bool RegisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players, bool bWasInvited = false) = 0;` — Registers a group of players with the online service as being part of the online session @param SessionName the name of the session the player is joining @param Players the list of players to register with the online service @param bWasInvited was this list of players invited @return true if the call succeeds, false otherwise
- L854 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnRegisterPlayersComplete, FName, const TArray< FUniqueNetIdRef >&, bool);` — Delegate fired when the session registration process has completed @param SessionName the name of the session the player joined or not @param PlayerId the player that was registered in the online service @param bWasSuccessful true if the async action completed without error, false if there was an error
- L864 _public prototype_ `virtual bool UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId) = 0;` — Unregisters a player with the online service as being part of the online session @param SessionName the name of the session the player is leaving @param PlayerId the player to unregister with the online service @return true if the call succeeds, false otherwise
- L874 _public prototype_ `virtual bool UnregisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players) = 0;` — Unregisters a group of players with the online service as being part of the online session @param SessionName the name of the session the player is joining @param Players the list of players to unregister with the online service @return true if the call succeeds, false otherwise
- L883 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnUnregisterPlayersComplete, FName, const TArray< FUniqueNetIdRef >&, bool);` — Delegate fired when the un-registration process has completed @param SessionName the name of the session the player left @param PlayerId the player that was unregistered from the online service @param bWasSuccessful true if the async action completed without error, false if there was an error
- L892 _public prototype_ `virtual void RegisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnRegisterLocalPlayerCompleteDelegate& Delegate) = 0;` — Registers a local player with a session. @param PlayerId the player to register @param SessionName the session in which to register the player @param Delegate the delegate executed when the asynchronous operation completes
- L901 _public prototype_ `virtual void UnregisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnUnregisterLocalPlayerCompleteDelegate& Delegate) = 0;` — Unregisters a local player with a session. @param PlayerId the player to unregister @param SessionName the session in which to unregister the player @param Delegate the delegate executed when the asynchronous operation completes
- L910 _public prototype_ `virtual void RemovePlayerFromSession(int32 LocalUserNum, FName SessionName, const FUniqueNetId& TargetPlayerId);` — Removes a player from the session. @param LocalUserNum the user that is starting the removal @param SessionName the session in which to unregister the player @param TargetPlayerId the player to remove
- L918 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnSessionFailure, const FUniqueNetId&, ESessionFailure::Type);` — Delegate fired when an unexpected error occurs that impacts session connectivity or use @param PlayerId The player impacted by the failure (may be empty if unknown, or if all players are affected) @param FailureType What kind of failure occured
- L920 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnDestroySessionRequested, int32 , FName );`
- L925 _public prototype_ `virtual int32 GetNumSessions() = 0;` — Gets the number of known sessions registered with the interface
- L930 _public prototype_ `virtual void DumpSessionState() = 0;` — Dumps out the session state for all known sessions

#### Free symbols / members of external scopes

- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineSession, Log, All);`
- L17 _macro_ `#define UE_LOG_ONLINE_SESSION(Verbosity, Format, ...) \`
- L22 _macro_ `#define UE_CLOG_ONLINE_SESSION(Conditional, Verbosity, Format, ...) \`
- L28 _namespace_ `namespace EOnJoinSessionCompleteResult`
- L48 _function_ `inline const TCHAR* LexToString(const EOnJoinSessionCompleteResult::Type Value)` — Convert a EOnJoinSessionCompleteResult into a string
- L75 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnJoinSessionComplete, FName, EOnJoinSessionCompleteResult::Type);` — Delegate fired when the joining process for an online session has completed @param SessionName the name of the session this callback is for @param bWasSuccessful true if the async action completed without error, false if there was an error
- L75 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnJoinSessionComplete, FName, EOnJoinSessionCompleteResult::Type);` — Delegate fired when the joining process for an online session has completed @param SessionName the name of the session this callback is for @param bWasSuccessful true if the async action completed without error, false if there was an error
- L76 _typedef_ `typedef FOnJoinSessionComplete::FDelegate FOnJoinSessionCompleteDelegate;`
- L84 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSessionParticipantJoined, FName, const FUniqueNetId&);` — Delegate fired when a player has joined a session @param SessionName The name of the session that changed @param UniqueId The ID of the user who joined
- L84 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSessionParticipantJoined, FName, const FUniqueNetId&);` — Delegate fired when a player has joined a session @param SessionName The name of the session that changed @param UniqueId The ID of the user who joined
- L85 _typedef_ `typedef FOnSessionParticipantJoined::FDelegate FOnSessionParticipantJoinedDelegate;`
- L100 _prototype_ `const TCHAR* ToLogString(EOnSessionParticipantLeftReason LeaveReason);`
- L109 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSessionParticipantLeft, FName, const FUniqueNetId&, EOnSessionParticipantLeftReason);` — Delegate fired when a player has left a session @param SessionName The name of the session that changed @param UniqueId The ID of the user who left @param LeaveReason An enum defining the motive for the participant's leave
- L109 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSessionParticipantLeft, FName, const FUniqueNetId&, EOnSessionParticipantLeftReason);` — Delegate fired when a player has left a session @param SessionName The name of the session that changed @param UniqueId The ID of the user who left @param LeaveReason An enum defining the motive for the participant's leave
- L110 _typedef_ `typedef FOnSessionParticipantLeft::FDelegate FOnSessionParticipantLeftDelegate;`
- L116 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnQosDataRequested, FName);` — Delegate fired when session is requesting QOS measurements @param The name of the session for which the measurements need to be made
- L116 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnQosDataRequested, FName);` — Delegate fired when session is requesting QOS measurements @param The name of the session for which the measurements need to be made
- L117 _typedef_ `typedef FOnQosDataRequested::FDelegate FOnQosDataRequestedDelegate;`
- L124 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSessionSettingsUpdated, FName, const FOnlineSessionSettings&);` — Delegate fired when a session's settings have changed @param The name of the session that had its settings changed @param The updated session settings
- L124 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSessionSettingsUpdated, FName, const FOnlineSessionSettings&);` — Delegate fired when a session's settings have changed @param The name of the session that had its settings changed @param The updated session settings
- L125 _typedef_ `typedef FOnSessionSettingsUpdated::FDelegate FOnSessionSettingsUpdatedDelegate;`
- L133 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSessionParticipantSettingsUpdated, FName, const FUniqueNetId&, const FOnlineSessionSettings&);` — Delegate fired when a session's member settings have changed @param The name of the session that had a member's settings changed @param The UniqueNetId of the member whose settings changed @param The updated member settings
- L133 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSessionParticipantSettingsUpdated, FName, const FUniqueNetId&, const FOnlineSessionSettings&);` — Delegate fired when a session's member settings have changed @param The name of the session that had a member's settings changed @param The UniqueNetId of the member whose settings changed @param The updated member settings
- L134 _typedef_ `typedef FOnSessionParticipantSettingsUpdated::FDelegate FOnSessionParticipantSettingsUpdatedDelegate;`
- L144 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSingleSessionResultComplete, int32, bool, const FOnlineSessionSearchResult&);` — Delegate fired once a single search result is returned (ie friend invite / join) Session has not been joined at this point, and requires a call to JoinSession() @param LocalUserNum the controller number of the accepting user @param bWasSuccessful the session was found and is joinable, false otherwise @param SearchResult the search/settings for the session result we've been given
- L144 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSingleSessionResultComplete, int32, bool, const FOnlineSessionSearchResult&);` — Delegate fired once a single search result is returned (ie friend invite / join) Session has not been joined at this point, and requires a call to JoinSession() @param LocalUserNum the controller number of the accepting user @param bWasSuccessful the session was found and is joinable, false otherwise @param SearchResult the search/settings for the session result we've been given
- L145 _typedef_ `typedef FOnSingleSessionResultComplete::FDelegate FOnSingleSessionResultCompleteDelegate;`
- L155 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnFindFriendSessionComplete, int32, bool, const TArray<FOnlineSessionSearchResult>&);` — Delegate fired once a single search result is returned (ie friend invite / join) Session has not been joined at this point, and requires a call to JoinSession() @param LocalUserNum the controller number of the accepting user @param bWasSuccessful the session was found and is joinable, false otherwise @param SearchResult the search/settings for the session result we've been given
- L155 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnFindFriendSessionComplete, int32, bool, const TArray<FOnlineSessionSearchResult>&);` — Delegate fired once a single search result is returned (ie friend invite / join) Session has not been joined at this point, and requires a call to JoinSession() @param LocalUserNum the controller number of the accepting user @param bWasSuccessful the session was found and is joinable, false otherwise @param SearchResult the search/settings for the session result we've been given
- L156 _typedef_ `typedef FOnFindFriendSessionComplete::FDelegate FOnFindFriendSessionCompleteDelegate;`
- L163 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPingSearchResultsComplete, bool);` — Delegate fired when an individual server's query has completed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L163 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPingSearchResultsComplete, bool);` — Delegate fired when an individual server's query has completed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L164 _typedef_ `typedef FOnPingSearchResultsComplete::FDelegate FOnPingSearchResultsCompleteDelegate;`
- L176 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnSessionUserInviteAccepted, const bool, const int32, FUniqueNetIdPtr, const FOnlineSessionSearchResult&);` — Called when a user accepts a session invitation. Allows the game code a chance to clean up any existing state before accepting the invite. The invite must be accepted by calling JoinSession() after clean up has completed @param bWasSuccessful true if the async action completed without error, false if there was an error @param ControllerId the controller number of the accepting user @param UserId the user being invited @param InviteResult the search/settings for the session we're joining via invite
- L176 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnSessionUserInviteAccepted, const bool, const int32, FUniqueNetIdPtr, const FOnlineSessionSearchResult&);` — Called when a user accepts a session invitation. Allows the game code a chance to clean up any existing state before accepting the invite. The invite must be accepted by calling JoinSession() after clean up has completed @param bWasSuccessful true if the async action completed without error, false if there was an error @param ControllerId the controller number of the accepting user @param UserId the user being invited @param InviteResult the search/settings for the session we're joining via invite
- L177 _typedef_ `typedef FOnSessionUserInviteAccepted::FDelegate FOnSessionUserInviteAcceptedDelegate;`
- L188 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnSessionInviteReceived, const FUniqueNetId& , const FUniqueNetId& , const FString& , const FOnlineSessionSearchResult& );` — Called when a user receives a session invitation. Allows the game code to decide on accepting the invite. The invite can be accepted by calling JoinSession() @param UserId the user being invited @param FromId the user that sent the invite @param AppId the id of the client/app user was in when sending hte game invite @param InviteResult the search/settings for the session we're joining via invite
- L188 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnSessionInviteReceived, const FUniqueNetId& , const FUniqueNetId& , const FString& , const FOnlineSessionSearchResult& );` — Called when a user receives a session invitation. Allows the game code to decide on accepting the invite. The invite can be accepted by calling JoinSession() @param UserId the user being invited @param FromId the user that sent the invite @param AppId the id of the client/app user was in when sending hte game invite @param InviteResult the search/settings for the session we're joining via invite
- L189 _typedef_ `typedef FOnSessionInviteReceived::FDelegate FOnSessionInviteReceivedDelegate;`
- L198 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnRegisterPlayersComplete, FName, const TArray< FUniqueNetIdRef >&, bool);` — Delegate fired when the session registration process has completed @param SessionName the name of the session the player joined or not @param Players the players that were registered from the online service @param bWasSuccessful true if the async action completed without error, false if there was an error
- L198 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnRegisterPlayersComplete, FName, const TArray< FUniqueNetIdRef >&, bool);` — Delegate fired when the session registration process has completed @param SessionName the name of the session the player joined or not @param Players the players that were registered from the online service @param bWasSuccessful true if the async action completed without error, false if there was an error
- L199 _typedef_ `typedef FOnRegisterPlayersComplete::FDelegate FOnRegisterPlayersCompleteDelegate;`
- L208 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUnregisterPlayersComplete, FName, const TArray< FUniqueNetIdRef >&, bool);` — Delegate fired when the un-registration process has completed @param SessionName the name of the session the player left @param PlayerId the players that were unregistered from the online service @param bWasSuccessful true if the async action completed without error, false if there was an error
- L208 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUnregisterPlayersComplete, FName, const TArray< FUniqueNetIdRef >&, bool);` — Delegate fired when the un-registration process has completed @param SessionName the name of the session the player left @param PlayerId the players that were unregistered from the online service @param bWasSuccessful true if the async action completed without error, false if there was an error
- L209 _typedef_ `typedef FOnUnregisterPlayersComplete::FDelegate FOnUnregisterPlayersCompleteDelegate;`
- L214 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRegisterLocalPlayerCompleteDelegate, const FUniqueNetId&, EOnJoinSessionCompleteResult::Type);` — Delegate fired when local player registration has completed
- L214 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnRegisterLocalPlayerCompleteDelegate, const FUniqueNetId&, EOnJoinSessionCompleteResult::Type);` — Delegate fired when local player registration has completed
- L219 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnUnregisterLocalPlayerCompleteDelegate, const FUniqueNetId&, const bool);` — Delegate fired when local player unregistration has completed
- L219 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnUnregisterLocalPlayerCompleteDelegate, const FUniqueNetId&, const bool);` — Delegate fired when local player unregistration has completed
- L222 _namespace_ `namespace ESessionFailure`
- L232 _function_ `inline const TCHAR* LexToString(const ESessionFailure::Type Value)` — Convert a ESessionFailure into a string
- L249 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSessionFailure, const FUniqueNetId&, ESessionFailure::Type);` — Delegate fired when an unexpected error occurs that impacts session connectivity or use @param PlayerId The player impacted by the failure (may be empty if unknown, or if all players are affected) @param FailureType What kind of failure occurred
- L249 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSessionFailure, const FUniqueNetId&, ESessionFailure::Type);` — Delegate fired when an unexpected error occurs that impacts session connectivity or use @param PlayerId The player impacted by the failure (may be empty if unknown, or if all players are affected) @param FailureType What kind of failure occurred
- L250 _typedef_ `typedef FOnSessionFailure::FDelegate FOnSessionFailureDelegate;`
- L259 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroySessionRequested, int32 , FName );` — Delegate called when the service requests that we destroy the session. The game should react by cleaning up any state associated with the session (leaving the match, etc), and calling DestroySession. @param LocalUserNum The index for the player that made the request @param SessionName The identifier for the session to be destroyed
- L259 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroySessionRequested, int32 , FName );` — Delegate called when the service requests that we destroy the session. The game should react by cleaning up any state associated with the session (leaving the match, etc), and calling DestroySession. @param LocalUserNum The index for the player that made the request @param SessionName The identifier for the session to be destroyed
- L260 _typedef_ `typedef FOnDestroySessionRequested::FDelegate FOnDestroySessionRequestedDelegate;`
- L933 _typedef_ `typedef TSharedPtr<IOnlineSession, ESPMode::ThreadSafe> IOnlineSessionPtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineSharedCloudInterface.h` (Public)


#### class `IOnlineSharedCloud`  
`class IOnlineSharedCloud`  
_L35-109_
- desc: Provides the interface for sharing files already on the cloud with other users
- L38 _protected function_ `IOnlineSharedCloud()`
- L41 _public prototype_ `virtual ~IOnlineSharedCloud() = default;`
- L51 _public prototype_ `virtual bool GetSharedFileContents(const FSharedContentHandle& SharedHandle, TArray<uint8>& FileContents) = 0;` — Copies the shared data into the specified buffer for the specified file @param SharedHandle the name of the file to read @param FileContents the out buffer to copy the data into @return true if the data was copied, false otherwise
- L58 _public prototype_ `virtual bool ClearSharedFiles() = 0;` — Empties the set of all downloaded files if possible (no async tasks outstanding) @return true if they could be deleted, false if they could not
- L67 _public prototype_ `virtual bool ClearSharedFile(const FSharedContentHandle& SharedHandle) = 0;` — Empties the cached data for this file if it is not being downloaded currently @param SharedHandle the name of the file to read @return true if it could be deleted, false if it could not
- L76 _public prototype_ `virtual bool ReadSharedFile(const FSharedContentHandle& SharedHandle) = 0;` — Starts an asynchronous read of the specified shared file from the network platform's file store @param SharedHandle the name of the file to read @return true if the calls starts successfully, false otherwise
- L84 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnReadSharedFileComplete, bool, const FSharedContentHandle&);` — Delegate fired when a shared file read from the network platform's storage is complete @param bWasSuccessful whether the content read was successful or not @param SharedHandle the handle of the read content
- L95 _public prototype_ `virtual bool WriteSharedFile(const FUniqueNetId& UserId, const FString& Filename, TArray<uint8>& Contents) = 0;` — Starts an asynchronous write of the specified shared file to the network platform's file store @param UserId User owning the storage @param Filename the name of the file to write @param Contents data to write to the file @return true if the calls starts successfully, false otherwise
- L105 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnWriteSharedFileComplete, bool, const FUniqueNetId&, const FString&, const TSharedRef<FSharedContentHandle>&);` — Delegate fired when a shared file write to the network platform's storage is complete @param bWasSuccessful whether the file Write was successful or not @param UserId User owning the storage @param Filename the name of the file this was for @param SharedHandle the handle to the shared file, may be platform dependent
- L108 _public prototype_ `virtual void GetDummySharedHandlesForTest(TArray< TSharedRef<FSharedContentHandle> > & OutHandles) = 0;` — Interface to get some test content handles

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReadSharedFileComplete, bool, const FSharedContentHandle&);` — Delegate fired when a shared file read from the network platform's storage is complete @param bWasSuccessful whether the file read was successful or not @param SharedHandle the handle of the read content
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReadSharedFileComplete, bool, const FSharedContentHandle&);` — Delegate fired when a shared file read from the network platform's storage is complete @param bWasSuccessful whether the file read was successful or not @param SharedHandle the handle of the read content
- L18 _typedef_ `typedef FOnReadSharedFileComplete::FDelegate FOnReadSharedFileCompleteDelegate;`
- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnWriteSharedFileComplete, bool, const FUniqueNetId&, const FString&, const TSharedRef<FSharedContentHandle>&);` — Delegate fired when a shared file write to the network platform's storage is complete @param bWasSuccessful whether the file Write was successful or not @param UserId User owning the storage @param Filename the name of the file this was for @param SharedHandle the handle to the shared file, may be platform dependent
- L28 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnWriteSharedFileComplete, bool, const FUniqueNetId&, const FString&, const TSharedRef<FSharedContentHandle>&);` — Delegate fired when a shared file write to the network platform's storage is complete @param bWasSuccessful whether the file Write was successful or not @param UserId User owning the storage @param Filename the name of the file this was for @param SharedHandle the handle to the shared file, may be platform dependent
- L29 _typedef_ `typedef FOnWriteSharedFileComplete::FDelegate FOnWriteSharedFileCompleteDelegate;`
- L111 _typedef_ `typedef TSharedPtr<IOnlineSharedCloud, ESPMode::ThreadSafe> IOnlineSharedCloudPtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineSharingInterface.h` (Public)


#### struct `FOnlineStatusUpdate`  
`struct FOnlineStatusUpdate`  
_L63-88_
- desc: FOnlineStatusUpdate - Object which hosts all the content we will post to a news feed
- L66 _public member_ `FString Type;` — Which type of status update for this post. May be ignored for some platforms
- L69 _public member_ `FString Message;` — The text which forms this post
- L72 _public member_ `struct FImage* Image;` — An accompanying image for this post, if desired
- L75 _public member_ `TArray<FUniqueNetIdRef > TaggedFriends;` — A list of friends which are included in the post
- L78 _public member_ `EOnlineStatusUpdatePrivacy PostPrivacy;` — The privacy of this post
- L83 _public function_ `FOnlineStatusUpdate() : Type(TEXT("Default")) , Image(NULL) , PostPrivacy(EOnlineStatusUpdatePrivacy::OnlyMe)` — Default Constructor

#### struct `FSharingPermission`  
`struct FSharingPermission`  
_L93-122_
- desc: Contains information about a single permission granted by a backend service
- L99 _public member_ `FString Name;` — Name of the platform specific permission
- L101 _public member_ `EOnlineSharingCategory Type;` — Type of permission
- L103 _public member_ `EOnlineSharingPermissionState Status;` — Status of the permission (granted/declined)
- L105 _public function_ `FSharingPermission() : Type(EOnlineSharingCategory::None) , Status(EOnlineSharingPermissionState::Unknown)`
- L111 _public function_ `explicit FSharingPermission(const FString& InName, EOnlineSharingCategory InType) : Name(InName) , Type(InType) , Status(EOnlineSharingPermissionState::Unknown)`
- L118 _public function_ `inline bool operator==(const FSharingPermission& Other) const`

#### class `IOnlineSharing`  
`class IOnlineSharing`  
_L136-262_
- desc: IOnlineSharing - Interface class for sharing.
- L139 _public prototype_ `virtual ~IOnlineSharing() = default;`
- L150 _public prototype_ `virtual void RequestCurrentPermissions(int32 LocalUserNum, FOnRequestCurrentPermissionsComplete& CompletionDelegate) = 0;` — Request the current set of permissions across all sharing @param LocalUserNum the controller number of the associated user @param CompletionDelegate the delegate to fire when the operation is completed
- L155 _public prototype_ `virtual void GetCurrentPermissions(int32 LocalUserNum, TArray<FSharingPermission>& OutPermissions) = 0;` — @return the currently cached permissions for a given user
- L163 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_ONE_PARAM(MAX_LOCAL_PLAYERS, OnRequestNewReadPermissionsComplete, bool);` — Called when we have successfully/failed to read a news feed from the server @param LocalUserNum the controller number of the associated user @param bWasSuccessful true if server was contacted and the feed was read
- L172 _public prototype_ `virtual bool RequestNewReadPermissions(int32 LocalUserNum, EOnlineSharingCategory NewPermissions) = 0;` — Request a new set of read permissions from our OSS @param LocalUserNum		- The controller number of the associated user @param NewPermissions	- The read permissions we are requesting authorization for.
- L180 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_ONE_PARAM(MAX_LOCAL_PLAYERS, OnRequestNewPublishPermissionsComplete, bool);` — Called when we have successfully/failed to read a news feed from the server @param LocalUserNum the controller number of the associated user @param bWasSuccessful true if server was contacted and the feed was read
- L189 _public prototype_ `virtual bool RequestNewPublishPermissions(int32 LocalUserNum, EOnlineSharingCategory NewPermissions, EOnlineStatusUpdatePrivacy Privacy) = 0;` — Request a new set of publish permissions from our OSS @param LocalUserNum		- The controller number of the associated user @param NewPermissions	- The publish permissions we are requesting authorization for.
- L203 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_ONE_PARAM(MAX_LOCAL_PLAYERS, OnReadNewsFeedComplete, bool);` — Called when we have successfully/failed to read a news feed from the server @param LocalUserNum the controller number of the associated user @param bWasSuccessful true if server was contacted and the feed was read
- L213 _public prototype_ `virtual bool ReadNewsFeed(int32 LocalUserNum, int32 NumPostsToRead = 50) = 0;` — Read the status feed of the user specified. @param LocalUserNum the controller number of the associated user @return - Whether a server request was executed
- L225 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedNewsFeed(int32 LocalUserNum, int32 NewsFeedIdx, FOnlineStatusUpdate& OutNewsFeed) = 0;` — Get a news feed object which was previously synced from the server @param LocalUserId - The id of the user we are reading news feeds for @param NewsFeedIdx - The index of the news feed we are looking up @param OutNewsFeed - The news feed object we are searching for @return Whether the news feed was obtained
- L236 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedNewsFeeds(int32 LocalUserNum, TArray<FOnlineStatusUpdate>& OutNewsFeeds) = 0;` — Get all the status update objects for the specified local user @param LocalUserId - The local user Id of the user we are obtaining status updates for @param OutNewsFeeds - The collection of news feeds obtained from the server for the given player @return Whether news feeds were obtained
- L250 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_ONE_PARAM(MAX_LOCAL_PLAYERS, OnSharePostComplete, bool);` — Called when we have successfully/failed to post a status update to the server @param LocalUserNum		- The controller number of the associated user @param bWasSuccessful	- True if a post was successfully added to the server
- L261 _public prototype_ `virtual bool ShareStatusUpdate(int32 LocalUserNum, const FOnlineStatusUpdate& StatusUpdate) = 0;` — Set the online permissions for reading a users data. @param LocalUserNum	- The controller number of the associated user @param StatusUpdate	- The message we are posting to the feed. @return - Whether a server request was executed

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineSharing, Log, All);`
- L10 _macro_ `#define UE_LOG_ONLINE_SHARING(Verbosity, Format, ...) \`
- L15 _macro_ `#define UE_CLOG_ONLINE_SHARING(Conditional, Verbosity, Format, ...) \`
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSharePostComplete, int32, bool);` — Called to notify of a post being shared on the server @param LocalUserNum		- The controller number of the associated user @param bWasSuccessful	- True if a post was successfully uploaded
- L26 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSharePostComplete, int32, bool);` — Called to notify of a post being shared on the server @param LocalUserNum		- The controller number of the associated user @param bWasSuccessful	- True if a post was successfully uploaded
- L27 _typedef_ `typedef FOnSharePostComplete::FDelegate FOnSharePostCompleteDelegate;`
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReadNewsFeedComplete, int32, bool);` — Called to notify that a read request for a news feed has completed. @param LocalUserNum		- The controller number of the associated user @param bWasSuccessful	- True if the read request completed successfully
- L36 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReadNewsFeedComplete, int32, bool);` — Called to notify that a read request for a news feed has completed. @param LocalUserNum		- The controller number of the associated user @param bWasSuccessful	- True if the read request completed successfully
- L37 _typedef_ `typedef FOnReadNewsFeedComplete::FDelegate FOnReadNewsFeedCompleteDelegate;`
- L45 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRequestNewReadPermissionsComplete, int32, bool);` — Called to notify that read permissions have been updated on the server @param LocalUserNum		- The controller number of the associated user @param bWasSuccessful	- True if the read permissions updated successfully
- L45 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRequestNewReadPermissionsComplete, int32, bool);` — Called to notify that read permissions have been updated on the server @param LocalUserNum		- The controller number of the associated user @param bWasSuccessful	- True if the read permissions updated successfully
- L46 _typedef_ `typedef FOnRequestNewReadPermissionsComplete::FDelegate FOnRequestNewReadPermissionsCompleteDelegate;`
- L56 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRequestNewPublishPermissionsComplete, int32, bool);` — Called to notify that publish permissions have been updated on the server @param LocalUserNum		- The controller number of the associated user @param bWasSuccessful	- True if the publish permissions updated successfully
- L56 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRequestNewPublishPermissionsComplete, int32, bool);` — Called to notify that publish permissions have been updated on the server @param LocalUserNum		- The controller number of the associated user @param bWasSuccessful	- True if the publish permissions updated successfully
- L57 _typedef_ `typedef FOnRequestNewPublishPermissionsComplete::FDelegate FOnRequestNewPublishPermissionsCompleteDelegate;`
- L131 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnRequestCurrentPermissionsComplete, int32 , bool , const TArray<FSharingPermission>& );` — Called when a current permissions query has completed @param LocalUserNum		- The controller number of the associated user @param bWasSuccessful	- True if the query completed successfully @param Permissions		- Current state of permissions
- L131 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnRequestCurrentPermissionsComplete, int32 , bool , const TArray<FSharingPermission>& );` — Called when a current permissions query has completed @param LocalUserNum		- The controller number of the associated user @param bWasSuccessful	- True if the query completed successfully @param Permissions		- Current state of permissions

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineStatsInterface.h` (Public)


#### struct `FOnlineStatUpdate`  
`struct FOnlineStatUpdate`  
_L19-208_
- desc: Object to represent a new stat value and how to use it in relation to previous values
- L38 _public function_ `FOnlineStatUpdate() : NewValue(0) , ModificationType(EOnlineStatModificationType::Unknown)` — Construct an empty FOnlineStatUpdate
- L45 _public function_ `FOnlineStatUpdate(const FOnlineStatValue& InNewValue, const EOnlineStatModificationType InModificationType) : NewValue(InNewValue) , ModificationType(InModificationType)` — Construct a new FOnlineStatUpdate from a value
- L51 _public function_ `FOnlineStatUpdate(FOnlineStatValue&& InNewValue, const EOnlineStatModificationType InModificationType) : NewValue(MoveTemp(InNewValue)) , ModificationType(InModificationType)`
- L58 _public prototype_ `FOnlineStatUpdate(FOnlineStatUpdate&& Other) = default;` — Copy/Assignment construction
- L59 _public prototype_ `FOnlineStatUpdate(const FOnlineStatUpdate& Other) = default;`
- L60 _public prototype_ `FOnlineStatUpdate& operator=(FOnlineStatUpdate&& Other) = default;`
- L61 _public prototype_ `FOnlineStatUpdate& operator=(const FOnlineStatUpdate& Other) = default;`
- L64 _public function_ `void Set(const FOnlineStatValue& InNewValue, const EOnlineStatModificationType InModificationType)` — Set this stat update to a new value/modification type
- L70 _public function_ `void Set(FOnlineStatValue&& InNewValue, const EOnlineStatModificationType InModificationType)`
- L77 _public function_ `const FOnlineStatValue& GetValue() const` — Get the current value
- L83 _public function_ `EOnlineStatModificationType GetModificationType() const` — Get the current modification type
- L89 _public function_ `EOnlineKeyValuePairDataType::Type GetType() const` — Get the current type of stat (int32, float, etc)
- L95 _public function_ `FString ToString() const` — Get the value of this stat as a string
- L101 _public function_ `bool IsNumeric() const` — Returns true if this stat is numeric
- L108 _private function_ `template<typename T> T SwitchOnNumeric(const T& Left, const T& Right, EOnlineStatModificationType ModType) const`
- L128 _public function_ `FOnlineStatValue GetResult(const FOnlineStatValue& Other) const` — Takes the value saved here and its corresponding ModificationType and outputs the new final value. New final value should be directly set onto the preexisting value
- L206 _private member_ `FOnlineStatValue NewValue;`
- L207 _private member_ `EOnlineStatModificationType ModificationType;`

#### enum `FOnlineStatUpdate::EOnlineStatModificationType`  
`enum class EOnlineStatModificationType : uint8`  
_L23-35_
- desc: How should we modify this stat in relation to previous values?
- L26 _public enumerator_ `Unknown` — Let the backend decide how to update this value (or set to new value if backend does not decide)
- L28 _public enumerator_ `Sum` — Add the new value to the previous value
- L30 _public enumerator_ `Set` — Overwrite previous value with the new value
- L32 _public enumerator_ `Largest` — Only replace previous value if new value is larger
- L34 _public enumerator_ `Smallest` — Only replace previous value if new value is smaller

#### struct `FOnlineUserStatsPair`  
`template <class TStatType> struct FOnlineUserStatsPair`  
_L211-239_
- L214 _public function_ `FOnlineUserStatsPair(const FUniqueNetIdRef InAccount) : Account(InAccount)`
- L220 _public function_ `FOnlineUserStatsPair(const FUniqueNetIdRef InAccount, const TMap<FString, TStatType>& InStats) : Account(InAccount) , Stats(InStats)`
- L227 _public function_ `FOnlineUserStatsPair(const FUniqueNetIdRef InAccount, TMap<FString, TStatType>&& InStats) : Account(InAccount) , Stats(MoveTemp(InStats))`
- L235 _public member_ `FUniqueNetIdRef Account;`
- L236 _public member_ `TMap<FString, TStatType> Stats;`
- L238 _public typedef_ `using StatType = TStatType;`

#### class `IOnlineStats`  
`class IOnlineStats`  
_L257-309_
- desc: An interface to update stat backends with
- L261 _public prototype_ `virtual ~IOnlineStats() = default;`
- L271 _public prototype_ `virtual void QueryStats(const FUniqueNetIdRef LocalUserId, const FUniqueNetIdRef StatsUser, const FOnlineStatsQueryUserStatsComplete& Delegate) = 0;` — Query a specific user's stats @param LocalUserId User to query as (if applicable) @param StatsUser User to get stats for @param Delegate Called when the user's stats have finished being requested and are now available, or when we fail to retrieve the user's stats
- L281 _public prototype_ `virtual void QueryStats(const FUniqueNetIdRef LocalUserId, const TArray<FUniqueNetIdRef>& StatUsers, const TArray<FString>& StatNames, const FOnlineStatsQueryUsersStatsComplete& Delegate) = 0;` — Query a one or more user's stats @param LocalUserId User to query as (if applicable) @param StatsUser Users to get stats for @param StatNames Stats to get stats for all specified users @param Delegate Called when the user's stats have finished being requested and are now available, or when we fail to retrieve the user's stats
- L289 _public prototype_ `virtual TSharedPtr<const FOnlineStatsUserStats> GetStats(const FUniqueNetIdRef StatsUserId) const = 0;` — Get a user's cached stats object @param StatsUserId The user to get stats for @return The results if cached, else a null pointer
- L298 _public prototype_ `virtual void UpdateStats(const FUniqueNetIdRef LocalUserId, const TArray<FOnlineStatsUserUpdatedStats>& UpdatedUserStats, const FOnlineStatsUpdateStatsComplete& Delegate) = 0;` — Asynchronous update one or more user's stats @param LocalUserId The user to update the stats as (if applicable) @param UpdatedStats The array of user to stats pairs to update the backend with @param Delegate Called when update has completed
- L306 _public prototype_ `virtual void ResetStats( const FUniqueNetIdRef StatsUserId ) = 0;` — Request the stats reset, for debugging purposes @param StatsUserId The user who's stats are to be deleted

#### Free symbols / members of external scopes

- L9 _typedef_ `using FOnlineStatValue = FVariantData;`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineStats, Log, All);`
- L13 _macro_ `#define UE_LOG_ONLINE_STATS(Verbosity, Format, ...) \`
- L242 _delegate_ `DECLARE_DELEGATE_OneParam(FOnlineStatsUpdateStatsComplete, const FOnlineError& );` — Delegate called when a stat update has completed, with a ResultState parameter to represent success or failure
- L242 _prototype_ `DECLARE_DELEGATE_OneParam(FOnlineStatsUpdateStatsComplete, const FOnlineError& );` — Delegate called when a stat update has completed, with a ResultState parameter to represent success or failure
- L245 _typedef_ `using FOnlineStatsUserStats = FOnlineUserStatsPair<FOnlineStatValue>;` — A pair of a user and an array of their stats
- L248 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnlineStatsQueryUserStatsComplete, const FOnlineError& , const TSharedPtr<const FOnlineStatsUserStats>& );` — Delegate called when a user's stats have finished being queried, with a ResultState parameter to represent success or failure
- L248 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnlineStatsQueryUserStatsComplete, const FOnlineError& , const TSharedPtr<const FOnlineStatsUserStats>& );` — Delegate called when a user's stats have finished being queried, with a ResultState parameter to represent success or failure
- L251 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnlineStatsQueryUsersStatsComplete, const FOnlineError& , const TArray<TSharedRef<const FOnlineStatsUserStats>>& );` — Delegate called when multiple users' stats have finished being queried, with a ResultState parameter to represent success or failure
- L251 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnlineStatsQueryUsersStatsComplete, const FOnlineError& , const TArray<TSharedRef<const FOnlineStatsUserStats>>& );` — Delegate called when multiple users' stats have finished being queried, with a ResultState parameter to represent success or failure
- L254 _typedef_ `using FOnlineStatsUserUpdatedStats = FOnlineUserStatsPair<FOnlineStatUpdate>;` — A pair of a user and an array of their stats to be updated

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineStoreInterfaceV2.h` (Public)


#### enum `EInAppPurchaseState::Type`  
`enum Type : int`  
_L33-43_
- L35 _public enumerator_ `Unknown = 0 UMETA(DisplayName = "Unknown")`
- L36 _public enumerator_ `Success UMETA(DisplayName = "Success")`
- L37 _public enumerator_ `Failed UMETA(DisplayName = "Failed")`
- L38 _public enumerator_ `Cancelled UMETA(DisplayName = "Cancelled")`
- L39 _public enumerator_ `Invalid UMETA(DisplayName = "Invalid")`
- L40 _public enumerator_ `NotAllowed UMETA(DisplayName = "NotAllowed")`
- L41 _public enumerator_ `Restored UMETA(DisplayName = "Restored")`
- L42 _public enumerator_ `AlreadyOwned UMETA(DisplayName = "AlreadyOwned")`

#### enum `EOnlineStoreOfferDiscountType`  
`enum class EOnlineStoreOfferDiscountType : uint8`  
_L46-56_
- L49 _public enumerator_ `NotOnSale = 0u` — Offer isn't on sale
- L51 _public enumerator_ `Percentage` — Offer price should be displayed as a percentage of regular price
- L53 _public enumerator_ `DiscountAmount` — Offer price should be displayed as an amount off regular price
- L55 _public enumerator_ `PayAmount` — Offer price should be displayed as a new price

#### class `FOnlineStoreOffer`  
`class FOnlineStoreOffer`  
_L84-161_
- desc: Offer entry for display from online store
- L87 _public function_ `FOnlineStoreOffer() : RegularPrice(-1) , NumericPrice(-1) , ReleaseDate(0) , ExpirationDate(FDateTime::MaxValue()) , DiscountType(EOnlineStoreOfferDiscountType::NotOnSale)`
- L96 _public prototype_ `virtual ~FOnlineStoreOffer() = default;`
- L99 _public member_ `FUniqueOfferId OfferId;` — Unique offer identifier
- L102 _public member_ `FText Title;` — Title for display
- L104 _public member_ `FText Description;` — Short description for display
- L106 _public member_ `FText LongDescription;` — Full description for display
- L109 _public member_ `FText RegularPriceText;` — Regular non-sale price as text for display
- L111 _public member_ `int64 RegularPrice;` — Regular non-sale price in numeric form for comparison/sorting
- L114 _public member_ `FText PriceText;` — Final-Pricing (Post-Sales/Discounts) as text for display
- L116 _public member_ `int64 NumericPrice;` — Final-Price (Post-Sales/Discounts) in numeric form for comparison/sorting
- L119 _public member_ `FString CurrencyCode;` — Price currency code
- L122 _public member_ `FDateTime ReleaseDate;` — Date the offer was released
- L124 _public member_ `FDateTime ExpirationDate;` — Date this information is no longer valid (maybe due to sale ending, etc)
- L126 _public member_ `EOnlineStoreOfferDiscountType DiscountType;` — Type of discount currently running on this offer (if any)
- L128 _public member_ `TMap<FString, FString> DynamicFields;`
- L131 _public function_ `virtual FText GetDisplayRegularPrice() const` — @return FText suitable for localized display
- L144 _public function_ `virtual FText GetDisplayPrice() const` — @return FText suitable for localized display
- L157 _public function_ `virtual bool IsPurchaseable() const` — @return True if offer can be purchased

#### class `FOnlineStoreCategory`  
`class FOnlineStoreCategory`  
_L167-176_
- desc: Category used to organize offers in the online store
- L171 _public member_ `FUniqueCategoryId Id;` — Unique identifier for this category
- L173 _public member_ `FText Description;` — Description for display
- L175 _public member_ `TArray<FOnlineStoreCategory> SubCategories;` — List of optional sub categories

#### class `FOnlineStoreFilter`  
`class FOnlineStoreFilter`  
_L181-190_
- desc: Filter for querying a subset of offers from the online store
- L185 _public member_ `TArray<FString> Keywords;` — Keyword strings to match when filtering items/offers
- L187 _public member_ `TArray<FOnlineStoreCategory> IncludeCategories;` — Category paths to match when filtering offers
- L189 _public member_ `TArray<FOnlineStoreCategory> ExcludeCategories;` — Category paths to exclude when filtering offers

#### class `IOnlineStoreV2`  
`class IOnlineStoreV2`  
_L214-280_
- desc: Access to available offers for purchase
- L218 _public prototype_ `virtual ~IOnlineStoreV2()= default;`
- L223 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnQueryForAvailablePurchasesComplete, bool);` — Delegate which is executed when QueryForAvailablePurchases completes
- L231 _public prototype_ `virtual void QueryCategories(const FUniqueNetId& UserId, const FOnQueryOnlineStoreCategoriesComplete& Delegate = FOnQueryOnlineStoreCategoriesComplete()) = 0;` — Query for available store categories. Delegate callback is guaranteed. @param UserId user initiating the request @param Delegate completion callback
- L238 _public prototype_ `virtual void GetCategories(TArray<FOnlineStoreCategory>& OutCategories) const = 0;` — Get currently cached store categories @param OutCategories [out] list of categories previously queried
- L247 _public prototype_ `virtual void QueryOffersByFilter(const FUniqueNetId& UserId, const FOnlineStoreFilter& Filter, const FOnQueryOnlineStoreOffersComplete& Delegate = FOnQueryOnlineStoreOffersComplete()) = 0;` — Query for available store offers using a filter. Delegate callback is guaranteed. @param UserId user initiating the request @param Filter only return offers matching the filter @param Delegate completion callback
- L258 _public prototype_ `virtual void QueryOffersById(const FUniqueNetId& UserId, const TArray<FUniqueOfferId>& OfferIds, const FOnQueryOnlineStoreOffersComplete& Delegate = FOnQueryOnlineStoreOffersComplete()) = 0;` — Query for available store offers matching the given ids. Delegate callback is guaranteed. @param UserId user initiating the request @param OfferIds only return offers matching these ids @param Delegate completion callback @return true if async operation started
- L265 _public prototype_ `virtual void GetOffers(TArray<FOnlineStoreOfferRef>& OutOffers) const = 0;` — Get currently cached store offers @param OutOffers [out] list of offers previously queried
- L274 _public prototype_ `virtual TSharedPtr<FOnlineStoreOffer> GetOffer(const FUniqueOfferId& OfferId) const = 0;` — Get currently cached store offer entry @param OfferId id of offer to find @return offer if found or null
- L279 _public function_ `virtual FString GetStoreCountry() const` — Return store country if it has been fetched.

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineStoreV2, Log, All);`
- L11 _macro_ `#define UE_LOG_ONLINE_STOREV2(Verbosity, Format, ...) \`
- L16 _macro_ `#define UE_CLOG_ONLINE_STOREV2(Conditional, Verbosity, Format, ...) \`
- L23 _typedef_ `typedef FString FUniqueOfferId;`
- L24 _typedef_ `typedef FString FOfferNamespace;`
- L25 _typedef_ `typedef FString FUniqueCategoryId;`
- L31 _namespace_ `namespace EInAppPurchaseState`
- L58 _namespace_ `namespace EOnlineStoreOfferDiscount`
- L60 _function_ `inline EOnlineStoreOfferDiscountType FromString(const TCHAR* const String)` (scope `EOnlineStoreOfferDiscount`)
- L162 _typedef_ `typedef TSharedRef<FOnlineStoreOffer> FOnlineStoreOfferRef;`
- L195 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnQueryOnlineStoreCategoriesComplete, bool , const FString& );` — Delegate called when available online categories have been queried
- L195 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnQueryOnlineStoreCategoriesComplete, bool , const FString& );` — Delegate called when available online categories have been queried
- L200 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnQueryOnlineStoreOffersComplete, bool , const TArray<FUniqueOfferId>& , const FString& );` — Delegate called when online store query completes
- L200 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnQueryOnlineStoreOffersComplete, bool , const TArray<FUniqueOfferId>& , const FString& );` — Delegate called when online store query completes
- L208 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnQueryForAvailablePurchasesComplete, bool);` — Delegate fired when a session create request has completed @param SessionName the name of the session this callback is for @param bWasSuccessful true if the async action completed without error, false if there was an error
- L208 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnQueryForAvailablePurchasesComplete, bool);` — Delegate fired when a session create request has completed @param SessionName the name of the session this callback is for @param bWasSuccessful true if the async action completed without error, false if there was an error
- L209 _typedef_ `typedef FOnQueryForAvailablePurchasesComplete::FDelegate FOnQueryForAvailablePurchasesCompleteDelegate;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineTimeInterface.h` (Public)


#### class `IOnlineTime`  
`class IOnlineTime`  
_L21-52_
- desc: Interface for querying server time from an online service
- L25 _protected function_ `IOnlineTime()`
- L28 _public prototype_ `virtual ~IOnlineTime() = default;`
- L35 _public prototype_ `virtual bool QueryServerUtcTime() = 0;` — Send request for current UTC time from the server @return true if the query was started
- L44 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnQueryServerUtcTimeComplete, bool, const FString&, const FString&);` — Called when the time request from the server is complete @param bWasSuccessful true if server was contacted and a valid result received @param DateTimeStr string representing UTC server time (yyyy.MM.dd-HH.mm.ss) @param Error string representing the error condition
- L51 _public prototype_ `virtual FString GetLastServerUtcTime() = 0;` — Retrieve cached timestamp from last server time query @return string representation of time (yyyy.MM.dd-HH.mm.ss)

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnQueryServerUtcTimeComplete, bool, const FString&, const FString&);` — Called when the time request from the server is complete @param bWasSuccessful true if server was contacted and a valid result received @param DateTimeStr string representing UTC server time (yyyy.MM.dd-HH.mm.ss) @param Error string representing the error condition
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnQueryServerUtcTimeComplete, bool, const FString&, const FString&);` — Called when the time request from the server is complete @param bWasSuccessful true if server was contacted and a valid result received @param DateTimeStr string representing UTC server time (yyyy.MM.dd-HH.mm.ss) @param Error string representing the error condition
- L16 _typedef_ `typedef FOnQueryServerUtcTimeComplete::FDelegate FOnQueryServerUtcTimeCompleteDelegate;`
- L54 _typedef_ `typedef TSharedPtr<IOnlineTime, ESPMode::ThreadSafe> IOnlineTimePtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineTitleFileInterface.h` (Public)


#### class `IOnlineTitleFile`  
`class IOnlineTitleFile`  
_L60-160_
- L63 _protected function_ `IOnlineTitleFile()`
- L66 _public prototype_ `virtual ~IOnlineTitleFile() = default;`
- L76 _public prototype_ `virtual bool GetFileContents(const FString& FileName, TArray<uint8>& FileContents) = 0;` — Copies the file data into the specified buffer for the specified file @param FileName the name of the file to read @param FileContents the out buffer to copy the data into @return true if the data was copied, false otherwise
- L83 _public prototype_ `virtual bool ClearFiles() = 0;` — Empties the set of downloaded files if possible (no async tasks outstanding) @return true if they could be deleted, false if they could not
- L92 _public prototype_ `virtual bool ClearFile(const FString& FileName) = 0;` — Empties the cached data for this file if it is not being downloaded currently @param FileName the name of the file to remove from the cache @return true if it could be deleted, false if it could not
- L99 _public prototype_ `virtual void DeleteCachedFiles(bool bSkipEnumerated) = 0;` — Delete cached files on disk @param bSkipEnumerated if true then only non-enumerated files are deleted
- L108 _public prototype_ `virtual bool EnumerateFiles(const FPagedQuery& Page = FPagedQuery()) = 0;` — Requests a list of available files from the network store @param Page paging info to use for query @return true if the request has started, false if not
- L117 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnEnumerateFilesComplete, bool, const FString&);` — Delegate fired when the list of files has been returned from the network store @param bWasSuccessful whether the file list was successful or not @param Error string representing the error condition
- L125 _public prototype_ `virtual void GetFileList(TArray<FCloudFileHeader>& Files) = 0;` — Returns the list of files that was returned by the network store @param Files out array of file metadata
- L134 _public prototype_ `virtual bool ReadFile(const FString& FileName) = 0;` — Starts an asynchronous read of the specified file from the network platform's file store @param FileToRead the name of the file to read @return true if the calls starts successfully, false otherwise
- L143 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnReadFileComplete, bool, const FString&);` — Delegate fired when a file read from the network platform's storage is complete @param bWasSuccessful whether the file read was successful or not @param FileName the name of the file this was for
- L151 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnReadFileProgress, const FString&, uint64);` — Delegate fired when as file read from the network platform's storage progresses @param FileName the name of the file this was for @param NumBytes the number of bytes read so far

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineTitleFile, Log, All);`
- L10 _macro_ `#define UE_LOG_ONLINE_TITLEFILE(Verbosity, Format, ...) \`
- L15 _macro_ `#define UE_CLOG_ONLINE_TITLEFILE(Conditional, Verbosity, Format, ...) \`
- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEnumerateFilesComplete, bool, const FString&);` — Delegate fired when the list of files has been returned from the network store @param bWasSuccessful whether the file list was successful or not @param Error string representing the error condition
- L29 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEnumerateFilesComplete, bool, const FString&);` — Delegate fired when the list of files has been returned from the network store @param bWasSuccessful whether the file list was successful or not @param Error string representing the error condition
- L30 _typedef_ `typedef FOnEnumerateFilesComplete::FDelegate FOnEnumerateFilesCompleteDelegate;`
- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReadFileProgress, const FString&, uint64);` — Delegate fired when as file read from the network platform's storage progresses @param FileName the name of the file this was for @param NumBytes the number of bytes read so far
- L38 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReadFileProgress, const FString&, uint64);` — Delegate fired when as file read from the network platform's storage progresses @param FileName the name of the file this was for @param NumBytes the number of bytes read so far
- L39 _typedef_ `typedef FOnReadFileProgress::FDelegate FOnReadFileProgressDelegate;`
- L48 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReadFileComplete, bool, const FString&);` — Delegate fired when a file read from the network platform's storage is complete @param bWasSuccessful whether the file read was successful or not @param FileName the name of the file this was for
- L48 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReadFileComplete, bool, const FString&);` — Delegate fired when a file read from the network platform's storage is complete @param bWasSuccessful whether the file read was successful or not @param FileName the name of the file this was for
- L49 _typedef_ `typedef FOnReadFileComplete::FDelegate FOnReadFileCompleteDelegate;`
- L57 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTitleFileAnalyticsEvent, const FString& , const TArray<FAnalyticsEventAttribute>& ) typedef FOnTitleFileAnalyticsEvent::FDelegate FOnTitleFileAnalyticsEventDelegate;` — Delegate fired when we would like to report an event to an analytics provider. @param EventName the name of the event @param Attributes the key/value pairs of analytics event attributes to include with the event
- L58 _typedef_ `typedef FOnTitleFileAnalyticsEvent::FDelegate FOnTitleFileAnalyticsEventDelegate;`
- L162 _typedef_ `typedef TSharedPtr<IOnlineTitleFile, ESPMode::ThreadSafe> IOnlineTitleFilePtr;`
- L163 _typedef_ `typedef TSharedRef<IOnlineTitleFile, ESPMode::ThreadSafe> IOnlineTitleFileRef;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineTournamentInterface.h` (Public)


#### enum `EOnlineTournamentFormat`  
`enum class EOnlineTournamentFormat : uint8`  
_L49-61_
- desc: What format the tournament is being run as
- L52 _public enumerator_ `SingleElimination` — The tournament is being run in the single elimination format
- L54 _public enumerator_ `DoubleElimination` — The tournament is being run in the double elimination format
- L56 _public enumerator_ `Swiss` — The tournament is being run in the swiss format
- L58 _public enumerator_ `RoundRobin` — The tournament is being run in the round-robin format
- L60 _public enumerator_ `Custom` — The tournament is being run in a custom format

#### enum `EOnlineTournamentState`  
`enum class EOnlineTournamentState : uint8`  
_L114-128_
- desc: What state the tournament is currently in
- L117 _public enumerator_ `Created` — The tournament has been created, but participants may not be registered yet
- L119 _public enumerator_ `OpenRegistration` — The tournament is now open for registration
- L121 _public enumerator_ `ClosedRegistration` — The tournament registration has now closed, but the tournament has not started yet
- L123 _public enumerator_ `InProgress` — The tournament is now in progress
- L125 _public enumerator_ `Finished` — The tournament has now finished and all results are finalized
- L127 _public enumerator_ `Cancelled` — The tournament was cancelled

#### enum `EOnlineTournamentParticipantType`  
`enum class EOnlineTournamentParticipantType : uint8`  
_L187-193_
- desc: What participant format does this tournament support?
- L190 _public enumerator_ `Individual` — The tournament has individual players facing each other
- L192 _public enumerator_ `Team` — The tournament has teams facing other teams

#### struct `FOnlineTournamentQueryFilter`  
`struct FOnlineTournamentQueryFilter`  
_L231-256_
- desc: Filters to use when querying for tournament information. Some of these fields may be required, depending on the backing online system.  Some fields may not be specified if other fields are specified, depending on the backing online system.
- L243 _public member_ `TOptional<EOnlineTournamentParticipantType> ParticipantType;` — Filter tournament information that does not match this participant type
- L245 _public member_ `TOptional<EOnlineTournamentFormat> Format;` — Filter tournament information that does not match this tournament format
- L247 _public member_ `TOptional<FOnlineTournamentTeamIdRef> TeamId;` — Only include tournament information that includes this team (on team tournaments)
- L249 _public member_ `TOptional<FUniqueNetIdRef> PlayerId;` — Only include tournament information that includes this player
- L251 _public member_ `TOptional<uint32> Limit;` — Limit the results to this many entries
- L253 _public member_ `TOptional<uint32> Offset;` — Start the results this many entries in
- L255 _public member_ `TOptional<EOnlineTournamentSortDirection> SortDirection;` — Sort the results in this direction

#### enum `FOnlineTournamentQueryFilter::EOnlineTournamentSortDirection`  
`enum class EOnlineTournamentSortDirection : uint8`  
_L234-240_
- desc: What direction to sort these results by (useful when specifying limits and offsetts)
- L237 _public enumerator_ `Ascending` — Results will be sorted in Ascending order
- L239 _public enumerator_ `Descending` — Results will be sorted in Descending order

#### struct `FOnlineTournamentScore`  
`struct FOnlineTournamentScore`  
_L261-278_
- desc: Details about a participant and their current score
- L263 _public prototype_ `virtual ~FOnlineTournamentScore() = default;`
- L265 _public function_ `FOnlineTournamentScore(const FOnlineTournamentParticipantIdRef& InParticipantId, const EOnlineTournamentParticipantType InParticipantType, const FVariantData& InScore) : ParticipantId(InParticipantId) , ParticipantType(InParticipantType) , Score(InScore)`
- L273 _public member_ `FOnlineTournamentParticipantIdRef ParticipantId;` — The ParticipantId who achieved Score
- L275 _public member_ `EOnlineTournamentParticipantType ParticipantType;` — The type of participant this is
- L277 _public member_ `FVariantData Score;` — The score for this participant

#### struct `FOnlineTournamentMatchResults`  
`struct FOnlineTournamentMatchResults`  
_L283-312_
- desc: The results of a match
- L306 _public member_ `TArray<FOnlineTournamentScore> ScoresToSubmit;` — Score data to submit
- L309 _public member_ `TOptional<FString> Notes;` — Optiona notes about a score
- L311 _public member_ `TOptional<FOnlineTournamentScreenshotData> Screenshot;` — Optional screenshot data for proof of a score

#### struct `FOnlineTournamentMatchResults::FOnlineTournamentScreenshotData`  
`struct FOnlineTournamentScreenshotData`  
_L285-303_
- L287 _public function_ `FOnlineTournamentScreenshotData(const FString& InScreenshotFormat, const TArray<uint8>& InScreenshotData) : ScreenshotFormat(InScreenshotFormat) , ScreenshotData(InScreenshotData)`
- L293 _public function_ `FOnlineTournamentScreenshotData(FString&& InScreenshotFormat, TArray<uint8>&& InScreenshotData) : ScreenshotFormat(MoveTemp(InScreenshotFormat)) , ScreenshotData(MoveTemp(InScreenshotData))`
- L300 _public member_ `FString ScreenshotFormat;` — The format of the screenshot stored in ScreenshotData
- L302 _public member_ `TArray<uint8> ScreenshotData;` — Raw bytes of a screenshot in the ScreenshotFormat format

#### struct `IOnlineTournamentTeamDetails`  
`struct IOnlineTournamentTeamDetails : public TSharedFromThis<IOnlineTournamentTeamDetails>`  
_L317-330_
- inherits: `TSharedFromThis<IOnlineTournamentTeamDetails>`
- desc: The details of a team in a tournament
- L320 _public prototype_ `virtual ~IOnlineTournamentTeamDetails() = default;`
- L323 _public prototype_ `virtual FOnlineTournamentTeamIdRef GetTeamId() const = 0;` — Get the TeamId of this team
- L325 _public prototype_ `virtual TOptional<TArray<FUniqueNetIdRef>> GetPlayerIds() const = 0;` — Get the player ids of this team (if they are known)
- L327 _public prototype_ `virtual FString GetDisplayName() const = 0;` — Get the display name of this Team
- L329 _public prototype_ `virtual TOptional<FVariantData> GetAttribute(const FName AttributeName) const = 0;` — Get an attribute for this team (varies by online platform)

#### struct `FOnlineTournamentParticipantQueryFilter`  
`struct FOnlineTournamentParticipantQueryFilter`  
_L335-345_
- desc: Filters to use when querying for participant information.
- L337 _public function_ `FOnlineTournamentParticipantQueryFilter(const EOnlineTournamentParticipantType InParticipantType) : ParticipantType(InParticipantType)`
- L342 _public member_ `EOnlineTournamentParticipantType ParticipantType;`
- L343 _public member_ `TOptional<uint32> Limit;`
- L344 _public member_ `TOptional<uint32> Offset;`

#### enum `EOnlineTournamentParticipantState`  
`enum class EOnlineTournamentParticipantState : uint8`  
_L347-357_
- L350 _public enumerator_ `Registered` — The participant has registered for the upcoming event
- L352 _public enumerator_ `CheckedIn` — The participant has checked into the event and are ready to play
- L354 _public enumerator_ `Present` — The participant was present for the past event
- L356 _public enumerator_ `Absent` — The participant was not present for the past event

#### struct `IOnlineTournamentParticipantDetails`  
`struct IOnlineTournamentParticipantDetails : public TSharedFromThis<IOnlineTournamentParticipantDetails>`  
_L404-425_
- inherits: `TSharedFromThis<IOnlineTournamentParticipantDetails>`
- desc: The tournament-specific details of a participant in a tournament
- L407 _public prototype_ `virtual ~IOnlineTournamentParticipantDetails() = default;`
- L410 _public prototype_ `virtual FOnlineTournamentIdRef GetTournamentId() const = 0;` — Get the Tournament ID this participant is from
- L412 _public prototype_ `virtual FUniqueNetIdPtr GetPlayerId() const = 0;` — Get the Player ID of this tournament participant (if applicable)
- L414 _public prototype_ `virtual FOnlineTournamentTeamIdPtr GetTeamId() const = 0;` — Get the Team ID of this tournament participant (if applicable)
- L416 _public prototype_ `virtual const FString& GetDisplayName() const = 0;` — Get the display name of this participant
- L418 _public prototype_ `virtual EOnlineTournamentParticipantState GetState() const = 0;` — Get the current state of the tournament participant
- L420 _public prototype_ `virtual TOptional<int32> GetPosition() const = 0;` — Get the current position of this tournament participant (if applicable)
- L422 _public prototype_ `virtual TOptional<FVariantData> GetScore() const = 0;` — Get the current score of this tournament participant (if applicable)
- L424 _public prototype_ `virtual TOptional<FVariantData> GetAttribute(const FName AttributeName) const = 0;` — Get meta-data for this participant (varies based on online platform)

#### enum `EOnlineTournamentMatchState`  
`enum class EOnlineTournamentMatchState : uint8`  
_L430-435_
- desc: States this match can be in
- L432 _public enumerator_ `Created`
- L433 _public enumerator_ `InProgress`
- L434 _public enumerator_ `Finished`

#### struct `IOnlineTournamentMatchDetails`  
`struct IOnlineTournamentMatchDetails : public TSharedFromThis<IOnlineTournamentMatchDetails>`  
_L476-497_
- inherits: `TSharedFromThis<IOnlineTournamentMatchDetails>`
- desc: The details of a match
- L479 _public prototype_ `virtual ~IOnlineTournamentMatchDetails() = default;`
- L482 _public prototype_ `virtual FOnlineTournamentMatchIdRef GetMatchId() const = 0;` — Get the MatchId for this match
- L484 _public prototype_ `virtual EOnlineTournamentParticipantType GetParticipantType() const = 0;` — Get the type of participants for this match
- L486 _public prototype_ `virtual EOnlineTournamentMatchState GetMatchState() const = 0;` — Get the current state of this match
- L488 _public prototype_ `virtual TOptional<FString> GetBracket() const = 0;` — Get the bracket of this match
- L490 _public prototype_ `virtual TOptional<int32> GetRound() const = 0;` — Get the round of this match
- L492 _public prototype_ `virtual TOptional<FDateTime> GetStartDateUTC() const = 0;` — Get the start time of this match in UTC
- L494 _public prototype_ `virtual TArray<TSharedRef<const IOnlineTournamentParticipantDetails>> GetParticipants() const = 0;` — Get the array of participants for this match
- L496 _public prototype_ `virtual TOptional<FVariantData> GetAttribute(const FName AttributeName) const = 0;` — Get meta-data for this match (varies based on online platform)

#### struct `IOnlineTournamentDetails`  
`struct IOnlineTournamentDetails : public TSharedFromThis<IOnlineTournamentDetails>`  
_L502-537_
- inherits: `TSharedFromThis<IOnlineTournamentDetails>`
- desc: The details of a tournament
- L505 _public prototype_ `virtual ~IOnlineTournamentDetails() = default;`
- L508 _public prototype_ `virtual FOnlineTournamentIdRef GetTournamentId() const = 0;` — Get the Tournament ID for this tournament
- L510 _public prototype_ `virtual const FString& GetTitle() const = 0;` — Get the Title for this tournament
- L512 _public prototype_ `virtual const FString& GetDescription() const = 0;` — Get the Description for this tournament
- L514 _public prototype_ `virtual EOnlineTournamentState GetState() const = 0;` — Get the current state of this tournament
- L516 _public prototype_ `virtual EOnlineTournamentFormat GetFormat() const = 0;` — Get the the format of this tournament
- L518 _public prototype_ `virtual EOnlineTournamentParticipantType GetParticipantType() const = 0;` — Get the type of participants that are involved in this tournament
- L520 _public prototype_ `virtual const TArray<TSharedRef<const IOnlineTournamentParticipantDetails>>& GetParticipants() const = 0;` — Get the list of Participant IDs for this tournament if known
- L522 _public prototype_ `virtual TOptional<FDateTime> GetRegistrationStartDateUTC() const = 0;` — Get the registration start time of this tournament in UTC
- L524 _public prototype_ `virtual TOptional<FDateTime> GetRegistrationEndDateUTC() const = 0;` — Get the registration end time of this tournament in UTC
- L526 _public prototype_ `virtual TOptional<FDateTime> GetStartDateUTC() const = 0;` — Get the start time of this tournament in UTC
- L528 _public prototype_ `virtual TOptional<FTimespan> GetCheckInTimespan() const = 0;` — Get the check-in time of this tournament in UTC
- L530 _public prototype_ `virtual TOptional<FDateTime> GetEndDateUTC() const = 0;` — Get the end time of this tournament in UTC
- L532 _public prototype_ `virtual TOptional<FDateTime> GetLastUpdatedDateUTC() const = 0;` — Get the last time in UTC this tournament's details were updated
- L534 _public prototype_ `virtual TOptional<bool> RequiresPremiumSubscription() const = 0;` — Does this tournament require a premium subscription to participate in?
- L536 _public prototype_ `virtual TOptional<FVariantData> GetAttribute(const FName AttributeName) const = 0;` — Get meta-data for this tournament (varies based on online platform)

#### class `IOnlineTournament`  
`class IOnlineTournament : public TSharedFromThis<IOnlineTournament, ESPMode::ThreadSafe>`  
_L621-813_
- inherits: `TSharedFromThis<IOnlineTournament,ESPMode::ThreadSafe>`
- desc: Interface to handle requesting and submitting information related to tournaments
- L625 _public prototype_ `virtual ~IOnlineTournament() = default;`
- L634 _public prototype_ `virtual void QueryTournamentList(const FUniqueNetIdRef UserId, const FOnlineTournamentQueryFilter& QueryFilter, const FOnlineTournamentQueryTournamentListComplete& Delegate) = 0;` — Query a list of tournaments available for a user using specified filters. @param UserId The User to query tournaments as @param QueryFilter The filter to user to include/exclude tournaments from the list.  One or more options MAY be required, depending on the online platform. @param Delegate A delegate that is called when our tournament list query is complete
- L642 _public prototype_ `virtual TArray<FOnlineTournamentIdRef> GetTournamentList(const FUniqueNetIdRef UserId) const = 0;` — Get a list of all Tournament IDs that have been queried by the specified user. @param UserId A User who previously queried tournaments @return If previously queried by this user, an array of results from the query.
- L651 _public prototype_ `virtual void QueryTournamentDetails(const FUniqueNetIdRef UserId, const TArray<FOnlineTournamentIdRef>& TournamentIds, const FOnlineTournamentQueryTournamentDetailsComplete& Delegate) = 0;` — Query tournament details from the perspective of the specified user. @param UserId A User to query tournament details as @param TournamentIds An array of Tournament IDs to get more information about @param Delegate A delegate that is called when our tournament details query is complete
- L660 _public prototype_ `virtual TSharedPtr<const IOnlineTournamentDetails> GetTournamentDetails(const FUniqueNetIdRef UserId, const FOnlineTournamentIdRef TournamentId) const = 0;` — Get a tournament details result for a tournament that had been previously queried by the specified user. @param UserId A User who previously queried the tournament @param TournamentId The Tournament ID that previously had details queried by UserId @return If this tournament was previously queried by this user, the result from the query.
- L669 _public prototype_ `virtual TArray<TSharedPtr<const IOnlineTournamentDetails>> GetTournamentDetails(const FUniqueNetIdRef UserId, const TArray<FOnlineTournamentIdRef>& TournamentIds) const = 0;` — Get tournament detail results for specified tournaments that have been previously queried by the specified user. @param UserId A User who previously queried tournaments @param TournamentId The Tournament ID that previously had details queried by UserId @return If tournaments have been previously queried by this user, any matching tournaments from the results are of those queries.
- L678 _public prototype_ `virtual void QueryMatchList(const FUniqueNetIdRef UserId, const FOnlineTournamentIdRef TournamentId, const FOnlineTournamentQueryMatchListComplete& Delegate) = 0;` — Query a list of matches for a tournament from the perspective of the specified user. @param UserId A User to query match details as @param TournamentId The Tournament ID to get Match IDs from @param Delegate A delegate that is called when our match list query is complete
- L687 _public prototype_ `virtual TArray<FOnlineTournamentMatchIdRef> GetMatchList(const FUniqueNetIdRef UserId, const FOnlineTournamentIdRef TournamentId) const = 0;` — Get match detail results for that have been previously queried by the specified user. @param UserId A User who previously queried match results @param TournamentId The Tournament ID that previously had match results queried by UserId @return If tournaments have been previously queried by this user, all results of those queries.
- L696 _public prototype_ `virtual void QueryMatchDetails(const FUniqueNetIdRef UserId, const TArray<FOnlineTournamentMatchIdRef>& MatchIds, const FOnlineTournamentQueryMatchDetailsComplete& Delegate) = 0;` — Query match details for a tournament from the perspective of the specified user. @param UserId The User to query match details @param MatchId The Match IDs to get more information about @param Delegate A delegate that is called when our match details query is complete
- L705 _public prototype_ `virtual TSharedPtr<const IOnlineTournamentMatchDetails> GetMatchDetails(const FUniqueNetIdRef UserId, const FOnlineTournamentMatchIdRef MatchId) const = 0;` — Get a match's details that have been previously queried by the specified user. @param UserId A User who previously queried the match @param MatchId The Match ID that previously had details queried by UserId @return If this match has been previously queried by this user, the result is of that query.
- L714 _public prototype_ `virtual TArray<TSharedPtr<const IOnlineTournamentMatchDetails>> GetMatchDetails(const FUniqueNetIdRef UserId, const TArray<FOnlineTournamentMatchIdRef>& MatchIds) const = 0;` — Get match details that have been previously queried by the specified user. @param UserId A User who previously queried matches @param MatchIds Match ids that previously had details queried by UserId @return If matches have been previously queried by this user, any matching matches from the results are of those queries.
- L726 _public prototype_ `virtual void QueryParticipantList(const FUniqueNetIdRef UserId, const FOnlineTournamentIdRef TournamentId, const FOnlineTournamentParticipantQueryFilter& QueryFilter, const FOnlineTournamentQueryParticipantListComplete& Delegate) = 0;` — Query a list of participants for a tournament from the perspective of the specified user. It is valid to request Team IDs or Player IDs from a Team tournament, and it is only valid to request Player IDs from an Individual tournament. @param UserId A User to query Participant IDs as @param TournamentId The Tournament ID to get Participant IDs from @param QueryFilter Filter to use to query participants. @param Delegate A delegate that is called when our match list query is complete
- L736 _public prototype_ `virtual TArray<TSharedRef<const IOnlineTournamentParticipantDetails>> GetParticipantList(const FUniqueNetIdRef UserId, const FOnlineTournamentIdRef TournamentId, const EOnlineTournamentParticipantType ParticipantType) const = 0;` — Get Participant details that have been previously queried by the specified user. @param UserId A User who previously queried participants @param TournamentId The Tournament ID that previously had participants queried by UserId @param ParticipantType The type of IDs to return from this tournament.  This type must have been previously queried. @return If results have previously previously been queried by this user, the results of that query.
- L745 _public prototype_ `virtual void QueryTeamDetails(const FUniqueNetIdRef UserId, const TArray<FOnlineTournamentTeamIdRef>& TeamIds, const FOnlineTournamentQueryTeamDetailsComplete& Delegate) = 0;` — Query team details from the perspective of the specified user. @param UserId A User to query team details as @param TeamId The Team IDs to get more information about @param Delegate A delegate that is called when our team details query is complete
- L754 _public prototype_ `virtual TSharedPtr<const IOnlineTournamentTeamDetails> GetTeamDetails(const FUniqueNetIdRef UserId, const FOnlineTournamentTeamIdRef TeamId) const = 0;` — Get a teams's details that have been previously queried by the specified user. @param UserId A User who previously queried the team @param TeamId The Team ID that previously had details queried by UserId @return If this team has been previously queried by this user, the result is of that query.
- L763 _public prototype_ `virtual TArray<TSharedPtr<const IOnlineTournamentTeamDetails>> GetTeamDetails(const FUniqueNetIdRef UserId, const TArray<FOnlineTournamentTeamIdRef>& TeamIds) const = 0;` — Get team details that have been previously queried by the specified user. @param UserId A User who previously queried teams @param TeamIds The Team ID that previously had details queried by UserId @return If teams have been previously queried by this user, any matching teams from the results are of those queries.
- L773 _public prototype_ `virtual void SubmitMatchResults(const FUniqueNetIdRef UserId, const FOnlineTournamentMatchIdRef MatchId, const FOnlineTournamentMatchResults& MatchResults, const FOnlineTournamentSubmitMatchResultsComplete& Delegate) = 0;` — Submit match results for a tournament match. @param UserId The User to report match results for @param MatchId The Match Id to report match results for @param MatchResults The results of the match @param Delegate A delegate that is called when our match stats submissions is complete
- L780 _public prototype_ `virtual FDelegateHandle AddOnOnlineTournamentTournamentJoined(const FOnOnlineTournamentTournamentJoinedDelegate& Delegate) = 0;` — Register for updates when a tournament has been joined @param Delegate Delegate to be called when a tournament has been joined
- L787 _public prototype_ `virtual void RemoveOnOnlineTournamentTournamentJoined(const FDelegateHandle& DelegateHandle) = 0;` — Unregister for tournament join updates using a previously-registered delegate handle @param DelegateHandle Delegate handle that was previously registered
- L794 _public prototype_ `virtual FDelegateHandle AddOnOnlineTournamentMatchJoinedDelegate(const FOnOnlineTournamentMatchJoinedDelegate& Delegate) = 0;` — Register for updates when a tournament match has been joined @param Delegate Delegate to be called when a tournament match has been joined
- L801 _public prototype_ `virtual void RemoveOnOnlineTournamentMatchJoinedDelegate(const FDelegateHandle& DelegateHandle) = 0;` — Unregister for tournament match join updates using a previously-registered delegate handle @param DelegateHandle Delegate handle that was previously registered
- L805 _public prototype_ `virtual void DumpCachedTournamentInfo(const FUniqueNetIdRef UserId) const = 0;` — Print all cached tournament information into the logs
- L807 _public prototype_ `virtual void DumpCachedMatchInfo(const FUniqueNetIdRef UserId) const = 0;` — Print all cached match information into the logs
- L809 _public prototype_ `virtual void DumpCachedParticipantInfo(const FUniqueNetIdRef UserId) const = 0;` — Print all cached participant information into the logs
- L811 _public prototype_ `virtual void DumpCachedTeamInfo(const FUniqueNetIdRef UserId) const = 0;` — Print all cached team information into the logs

#### Free symbols / members of external scopes

- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineTournament, Display, All);`
- L14 _macro_ `#define UE_LOG_ONLINE_TOURNAMENT(Verbosity, Format, ...) \`
- L19 _macro_ `#define UE_CLOG_ONLINE_TOURNAMENT(Conditional, Verbosity, Format, ...) \`
- L27 _typedef_ `using FOnlineTournamentId = FUniqueNetId;` — UniqueNetId of a tournament
- L28 _typedef_ `using FOnlineTournamentIdRef = FUniqueNetIdRef;`
- L29 _typedef_ `using FOnlineTournamentIdPtr = FUniqueNetIdPtr;`
- L32 _typedef_ `using FOnlineTournamentMatchId = FUniqueNetId;` — UniqueNetId of a match in a tournament
- L33 _typedef_ `using FOnlineTournamentMatchIdRef = FUniqueNetIdRef;`
- L34 _typedef_ `using FOnlineTournamentMatchIdPtr = FUniqueNetIdPtr;`
- L37 _typedef_ `using FOnlineTournamentParticipantId = FUniqueNetId;` — UniqueNetId of a participant (Player or team) in a tournament
- L38 _typedef_ `using FOnlineTournamentParticipantIdRef = FUniqueNetIdRef;`
- L39 _typedef_ `using FOnlineTournamentParticipantIdPtr = FUniqueNetIdPtr;`
- L42 _typedef_ `using FOnlineTournamentTeamId = FUniqueNetId;` — UniqueNetId of a team in a tournament
- L43 _typedef_ `using FOnlineTournamentTeamIdRef = FUniqueNetIdRef;`
- L44 _typedef_ `using FOnlineTournamentTeamIdPtr = FUniqueNetIdPtr;`
- L63 _function_ `inline void LexFromString(TOptional<EOnlineTournamentFormat>& Format, const TCHAR* const String)`
- L91 _function_ `inline FString LexToString(const EOnlineTournamentFormat Format)`
- L130 _function_ `inline void LexFromString(TOptional<EOnlineTournamentState>& State, const TCHAR* const String)`
- L162 _function_ `inline FString LexToString(const EOnlineTournamentState State)`
- L195 _function_ `inline void LexFromString(TOptional<EOnlineTournamentParticipantType>& State, const TCHAR* const String)`
- L211 _function_ `inline FString LexToString(const EOnlineTournamentParticipantType ParticipantType)`
- L359 _function_ `inline void LexFromString(TOptional<EOnlineTournamentParticipantState>& State, const TCHAR* const String)`
- L383 _function_ `inline FString LexToString(const EOnlineTournamentParticipantState ParticipantType)`
- L437 _function_ `inline void LexFromString(TOptional<EOnlineTournamentMatchState>& State, const TCHAR* const String)`
- L457 _function_ `inline FString LexToString(const EOnlineTournamentMatchState ParticipantType)`
- L545 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnlineTournamentQueryTournamentListComplete, const FOnlineError& , const TOptional<TArray<FOnlineTournamentIdRef>>& );` — A delegate for when a tournament list has finished being queried. @param ResultStatus The result of the query @param TournamentIds An optional array of Tournament IDs
- L545 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnlineTournamentQueryTournamentListComplete, const FOnlineError& , const TOptional<TArray<FOnlineTournamentIdRef>>& );` — A delegate for when a tournament list has finished being queried. @param ResultStatus The result of the query @param TournamentIds An optional array of Tournament IDs
- L553 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnlineTournamentQueryTournamentDetailsComplete, const FOnlineError& , const TOptional<TArray<TSharedRef<const IOnlineTournamentDetails>>>& );` — A delegate for when tournament details have finished being queried. @param ResultStatus The result of the query @param TournamentDetails An optional array of Tournament Details
- L553 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnlineTournamentQueryTournamentDetailsComplete, const FOnlineError& , const TOptional<TArray<TSharedRef<const IOnlineTournamentDetails>>>& );` — A delegate for when tournament details have finished being queried. @param ResultStatus The result of the query @param TournamentDetails An optional array of Tournament Details
- L561 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnlineTournamentQueryMatchListComplete, const FOnlineError& , const TOptional<TArray<FOnlineTournamentMatchIdRef>>& );` — A delegate for when a match list has finished being queried. @param ResultStatus The result of the query @param MatchIds An optional array of Match Ids
- L561 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnlineTournamentQueryMatchListComplete, const FOnlineError& , const TOptional<TArray<FOnlineTournamentMatchIdRef>>& );` — A delegate for when a match list has finished being queried. @param ResultStatus The result of the query @param MatchIds An optional array of Match Ids
- L569 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnlineTournamentQueryMatchDetailsComplete, const FOnlineError& , const TOptional<TArray<TSharedRef<const IOnlineTournamentMatchDetails>>>& );` — A delegate for when match details have finished being queried. @param ResultStatus The result of the query @param MatchDetails An optional array of Match Details
- L569 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnlineTournamentQueryMatchDetailsComplete, const FOnlineError& , const TOptional<TArray<TSharedRef<const IOnlineTournamentMatchDetails>>>& );` — A delegate for when match details have finished being queried. @param ResultStatus The result of the query @param MatchDetails An optional array of Match Details
- L578 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnlineTournamentQueryParticipantListComplete, const FOnlineError& , const TOptional<uint32> , const TOptional<TArray<TSharedRef<const IOnlineTournamentParticipantDetails>>>& );` — A delegate for when participant lists have finished being queried. @param ResultStatus The result of the query @param TotalResults Total possible results there are to be queried @param ParticipantList An optional array of Participant Details
- L578 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnlineTournamentQueryParticipantListComplete, const FOnlineError& , const TOptional<uint32> , const TOptional<TArray<TSharedRef<const IOnlineTournamentParticipantDetails>>>& );` — A delegate for when participant lists have finished being queried. @param ResultStatus The result of the query @param TotalResults Total possible results there are to be queried @param ParticipantList An optional array of Participant Details
- L586 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnlineTournamentQueryTeamDetailsComplete, const FOnlineError& , const TOptional<TArray<TSharedRef<const IOnlineTournamentTeamDetails>>>& );` — A delegate for when team details have finished being queried. @param ResultStatus The result of the query @param TeamDetails An optional array of Team Details
- L586 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnlineTournamentQueryTeamDetailsComplete, const FOnlineError& , const TOptional<TArray<TSharedRef<const IOnlineTournamentTeamDetails>>>& );` — A delegate for when team details have finished being queried. @param ResultStatus The result of the query @param TeamDetails An optional array of Team Details
- L593 _delegate_ `DECLARE_DELEGATE_OneParam(FOnlineTournamentSubmitMatchResultsComplete, const FOnlineError& );` — A delegate for when match results have finished being submitted. @param ResultStatus The result of the query
- L593 _prototype_ `DECLARE_DELEGATE_OneParam(FOnlineTournamentSubmitMatchResultsComplete, const FOnlineError& );` — A delegate for when match results have finished being submitted. @param ResultStatus The result of the query
- L596 _typedef_ `using FAdditionalMetaDataMap = TMap<FName, FString>;`
- L605 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnOnlineTournamentTournamentJoined, const FUniqueNetIdRef , const FOnlineTournamentIdRef , const FAdditionalMetaDataMap& );` — A delegate for when a tournament has been joined @param UserId The user who joined the tournament @param TournamentId The ID of the tournament joined @param AdditonalData A map of additional platform-specific data that was provided when this event was triggered
- L605 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnOnlineTournamentTournamentJoined, const FUniqueNetIdRef , const FOnlineTournamentIdRef , const FAdditionalMetaDataMap& );` — A delegate for when a tournament has been joined @param UserId The user who joined the tournament @param TournamentId The ID of the tournament joined @param AdditonalData A map of additional platform-specific data that was provided when this event was triggered
- L606 _typedef_ `using FOnOnlineTournamentTournamentJoinedDelegate = FOnOnlineTournamentTournamentJoined::FDelegate;`
- L615 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnOnlineTournamentMatchJoined, const FUniqueNetIdRef , const FOnlineTournamentMatchIdRef , const FAdditionalMetaDataMap& );` — A delegate for when a tournament has been joined @param UserId The user who joined the tournament @param MatchId The ID of the match joined @param AdditonalData A map of additional platform-specific data that was provided when this event was triggered
- L615 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnOnlineTournamentMatchJoined, const FUniqueNetIdRef , const FOnlineTournamentMatchIdRef , const FAdditionalMetaDataMap& );` — A delegate for when a tournament has been joined @param UserId The user who joined the tournament @param MatchId The ID of the match joined @param AdditonalData A map of additional platform-specific data that was provided when this event was triggered
- L616 _typedef_ `using FOnOnlineTournamentMatchJoinedDelegate = FOnOnlineTournamentMatchJoined::FDelegate;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineTracingInterface.h` (Public)


#### class `IOnlineTracing`  
`class IOnlineTracing : public IModularFeature`  
_L17-46_
- inherits: `IModularFeature`
- desc: Online Tracing Interface
- L27 _public prototype_ `static void StartContext(FName ContextName);`
- L34 _public prototype_ `static void EndContext(FName ContextName);` — Ends a context @param ContextName user-specified context name.
- L36 _public prototype_ `virtual bool GetUncompressedTracingLog(TArray<uint8>& OutLog) = 0;`
- L38 _public prototype_ `virtual FString GetFilename() = 0;`
- L40 _public prototype_ `static IOnlineTracing* GetTracingHelper();`
- L43 _protected prototype_ `virtual void StartContextImpl(FName ContextName) = 0;`
- L45 _protected prototype_ `virtual void EndContextImpl(FName ContextName) = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEM_API`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineTurnBasedInterface.h` (Public)


#### class `FTurnBasedMatchRequest`  
`class FTurnBasedMatchRequest`  
_L10-53_
- desc: FTurnBasedMatchRequest contains all of the information required for a matchmaker to create an FTurnBasedMatch
- L13 _public function_ `FTurnBasedMatchRequest() : MinNumberOfPlayers(0) , MaxNumberOfPlayers(0) , PlayerGroup(0) , ShowExistingMatches(false)`
- L20 _public function_ `FTurnBasedMatchRequest(int32 InMinNumberOfPlayers, int32 InMaxNumberOfPlayers, uint32 InPlayerGroup, bool InShowExistingMatches) : MinNumberOfPlayers(InMinNumberOfPlayers) , MaxNumberOfPlayers(InMaxNumberOfPlayers) , PlayerGroup(InPlayerGroup) , ShowExistingMatches(InShowExistingMatches)`
- L27 _public function_ `void SetMinNumberOfPlayers(int32 InMinNumberOfPlayers)`
- L28 _public function_ `int32 GetMinNumberOfPlayers() const`
- L30 _public function_ `void SetMaxNumberOfPlayers(int32 InMaxNumberOfPlayers)`
- L31 _public function_ `int32 GetMaxNumberOfPlayers() const`
- L33 _public function_ `void SetPlayerGroup(uint32 InPlayerGroup)`
- L34 _public function_ `uint32 GetPlayerGroup() const`
- L36 _public function_ `void SetShowExistingMatches(bool InShowExistingMatches)`
- L37 _public function_ `bool GetShowExistingMatches() const`
- L42 _private member_ `int32 MinNumberOfPlayers;` — The minimum number of players needed for this match
- L45 _private member_ `int32 MaxNumberOfPlayers;` — The maximum number of players needed for this match
- L49 _private member_ `uint32 PlayerGroup;` — The player group represents another parameter to pass in to matchmaking. For example, 1 could be Deathmatch, 2 could be Capture the Flag, etc. Only players with the same player group will be matched together.
- L52 _private member_ `bool ShowExistingMatches;` — If true, the native matchmaking interface will show matches the player is in already

#### enum `EMPMatchOutcome::Outcome`  
`enum Outcome : int`  
_L67-79_
- L69 _public enumerator_ `None`
- L70 _public enumerator_ `Quit`
- L71 _public enumerator_ `Won`
- L72 _public enumerator_ `Lost`
- L73 _public enumerator_ `Tied`
- L74 _public enumerator_ `TimeExpired`
- L75 _public enumerator_ `First`
- L76 _public enumerator_ `Second`
- L77 _public enumerator_ `Third`
- L78 _public enumerator_ `Fourth`

#### class `FTurnBasedMatch`  
`class FTurnBasedMatch`  
_L85-128_
- desc: FTurnBasedMatch contains all of the information about an in-progress turn based match
- L88 _public prototype_ `virtual ~FTurnBasedMatch() = default;`
- L91 _public function_ `virtual int32 GetNumberOfPlayers() const` — Get the number of players in the match
- L94 _public function_ `virtual bool GetPlayerDisplayName(int32 PlayerIndex, FString& Name) const` — Get the user-friendly display name for the given player.  Can return false if the name of the associated player has not been loaded
- L97 _public function_ `virtual void ReloadMatchData(FDownloadMatchDataSignature DownloadCallback)` — Request a reload of the match's data.  Once the callback has been called, use GetMatchData to get the data
- L100 _public function_ `virtual bool HasMatchData() const` — HasMatchData is for when you want to know if the match has data, without getting at the data
- L103 _public function_ `virtual bool GetMatchData(TArray<uint8>& OutMatchData) const` — Put the match data into OutMatchData, returning whether or not the operation was successful
- L106 _public function_ `virtual void SetMatchData(const TArray<uint8>& NewMatchData, FUploadMatchDataSignature EndTurnCallback)` — Update the data for the match with the data provided
- L109 _public function_ `virtual FString GetMatchID() const` — Returns the Match ID for this match
- L112 _public function_ `virtual int32 GetLocalPlayerIndex() const` — Get the index of the local player in the match's list of participants
- L115 _public function_ `virtual int32 GetCurrentPlayerIndex() const` — Get the index of the current player in the match's list of participants
- L118 _public function_ `virtual EMPMatchOutcome::Outcome GetMatchOutcomeForPlayer(int32 PlayerIndex) const` — Get the outcome of the match (won/lost/quit/etc.) for the player with PlayerIndex
- L121 _public function_ `virtual void EndTurnWithMatchData(const TArray<uint8>& MatchData, int32 TurnTimeoutInSeconds, FUploadMatchDataSignature EndTurnCallback)` — End the turn and upload MatchData. EndTurnCallback is called once the data is uploaded (or failed), with a (bool) Success parameter
- L124 _public function_ `virtual void QuitMatch(EMPMatchOutcome::Outcome Outcome, int32 TurnTimeoutInSeconds, FQuitMatchSignature QuitMatchCallback)` — Leave the match, providing an outcome for the player
- L127 _public function_ `virtual void EndMatch(FEndMatchSignature QuitMatchCallback, EMPMatchOutcome::Outcome LocalPlayerOutcome, EMPMatchOutcome::Outcome OtherPlayersOutcome)` — Ends the match while setting the match outcome (win/loss/tie) for all players

#### class `FTurnBasedMatchmakerDelegate`  
`class FTurnBasedMatchmakerDelegate`  
_L136-149_
- desc: FTurnBasedMatchmakerDelegate provides the interface for all turn based matchmaking callbacks
- L139 _public prototype_ `virtual ~FTurnBasedMatchmakerDelegate() = default;`
- L142 _public function_ `virtual void OnMatchmakerCancelled()` — This is triggered if the player cancelled the matchmaking process
- L145 _public function_ `virtual void OnMatchmakerFailed()` — This is triggered if matchmaking failed for any reason
- L148 _public function_ `virtual void OnMatchFound(FTurnBasedMatchRef Match)` — This is triggered once a match has been successfully found

#### class `FTurnBasedEventDelegate`  
`class FTurnBasedEventDelegate`  
_L158-168_
- desc: FTurnBasedEventDelegate provides the interface for responding to events in turn based games
- L161 _public prototype_ `virtual ~FTurnBasedEventDelegate() = default;`
- L164 _public function_ `virtual void OnMatchEnded(FString MatchID)` — This is triggered when the match has ended for any reason
- L167 _public function_ `virtual void OnMatchReceivedTurnEvent(FString MatchID, bool BecameActive, void* Match)` — This is triggered when it is the current player's turn

#### class `IOnlineTurnBased`  
`class IOnlineTurnBased`  
_L180-214_
- desc: IOnlineTurnBased - Interface class for turn based multiplayer matches
- L183 _public prototype_ `virtual ~IOnlineTurnBased() = default;`
- L186 _public function_ `virtual void SetMatchmakerDelegate(FTurnBasedMatchmakerDelegatePtr Delegate)` — Set a delegate to be called when matchmaking succeeds, fails, or is canceled
- L189 _public function_ `virtual void ShowMatchmaker(const FTurnBasedMatchRequest& MatchRequest)` — Show the platform specific matchmaker interface with the parameters given in FTurnBasedMatchRequest
- L192 _public function_ `virtual void SetEventDelegate(FTurnBasedEventDelegateWeakPtr Delegate)` — Accessors for a delegate that gets called when match-specific events happen (such as the match ending or it is now the current players turn)
- L193 _public function_ `virtual FTurnBasedEventDelegateWeakPtr GetEventDelegate() const`
- L196 _public function_ `virtual void LoadAllMatches(FLoadTurnBasedMatchesSignature MatchesLoadedCallback)` — Load all matches the current player is participating in
- L199 _public function_ `virtual void LoadMatchWithID(FString MatchID, FLoadTurnBasedMatchWithIDSignature MatchesLoadedCallback)` — Reload a match with the given MatchID
- L202 _public function_ `virtual FTurnBasedMatchPtr GetMatchWithID(FString MatchID) const` — Returns the match object with the given MatchID
- L205 _public function_ `virtual void RemoveMatch(FTurnBasedMatchRef Match, FRemoveMatchSignature RemoveMatchCallback)` — Deletes a match entirely from the platform specific service
- L209 _public function_ `virtual void RegisterTurnBasedMatchInterfaceObject(UObject* Object)` — Accessors referring to an object that inherits from UTurnBasedMatchInterface that acts like an FTurnBasedEventDelegate (needed for blueprints)
- L210 _public function_ `virtual UObject* GetTurnBasedMatchInterfaceObject()`
- L213 _public function_ `virtual int32 GetMatchDataSize()` — The size of the game specific data stored per match

#### Free symbols / members of external scopes

- L55 _delegate_ `DECLARE_DELEGATE_TwoParams(FQuitMatchSignature, FString, bool);`
- L55 _prototype_ `DECLARE_DELEGATE_TwoParams(FQuitMatchSignature, FString, bool);` — bool Success
- L56 _delegate_ `DECLARE_DELEGATE_TwoParams(FRemoveMatchSignature, FString, bool);`
- L56 _prototype_ `DECLARE_DELEGATE_TwoParams(FRemoveMatchSignature, FString, bool);` — bool Success
- L57 _delegate_ `DECLARE_DELEGATE_TwoParams(FUploadMatchDataSignature, FString, bool);`
- L57 _prototype_ `DECLARE_DELEGATE_TwoParams(FUploadMatchDataSignature, FString, bool);` — bool Success
- L58 _delegate_ `DECLARE_DELEGATE_TwoParams(FDownloadMatchDataSignature, FString, bool);`
- L58 _prototype_ `DECLARE_DELEGATE_TwoParams(FDownloadMatchDataSignature, FString, bool);` — bool Success
- L59 _delegate_ `DECLARE_DELEGATE_TwoParams(FEndMatchSignature, FString, bool);`
- L59 _prototype_ `DECLARE_DELEGATE_TwoParams(FEndMatchSignature, FString, bool);` — bool Success
- L65 _namespace_ `namespace EMPMatchOutcome`
- L130 _typedef_ `typedef TSharedRef<FTurnBasedMatch, ESPMode::ThreadSafe> FTurnBasedMatchRef;`
- L131 _typedef_ `typedef TSharedPtr<FTurnBasedMatch, ESPMode::ThreadSafe> FTurnBasedMatchPtr;`
- L151 _typedef_ `typedef TSharedRef<FTurnBasedMatchmakerDelegate, ESPMode::ThreadSafe> FTurnBasedMatchmakerDelegateRef;`
- L152 _typedef_ `typedef TSharedPtr<FTurnBasedMatchmakerDelegate, ESPMode::ThreadSafe> FTurnBasedMatchmakerDelegatePtr;`
- L153 _typedef_ `typedef TWeakPtr<FTurnBasedMatchmakerDelegate, ESPMode::ThreadSafe> FTurnBasedMatchmakerDelegateWeakPtr;`
- L170 _delegate_ `DECLARE_DELEGATE_TwoParams(FLoadTurnBasedMatchesSignature, const TArray<FString>&, bool);`
- L170 _prototype_ `DECLARE_DELEGATE_TwoParams(FLoadTurnBasedMatchesSignature, const TArray<FString>&, bool);` — bool Success, TArray MatchArray
- L171 _delegate_ `DECLARE_DELEGATE_TwoParams(FLoadTurnBasedMatchWithIDSignature, FString, bool);`
- L171 _prototype_ `DECLARE_DELEGATE_TwoParams(FLoadTurnBasedMatchWithIDSignature, FString, bool);` — bool Success
- L173 _typedef_ `typedef TSharedRef<FTurnBasedEventDelegate, ESPMode::ThreadSafe> FTurnBasedEventDelegateRef;`
- L174 _typedef_ `typedef TSharedPtr<FTurnBasedEventDelegate, ESPMode::ThreadSafe> FTurnBasedEventDelegatePtr;`
- L175 _typedef_ `typedef TWeakPtr<FTurnBasedEventDelegate, ESPMode::ThreadSafe> FTurnBasedEventDelegateWeakPtr;`
- L216 _typedef_ `typedef TSharedPtr<class IOnlineTurnBased, ESPMode::ThreadSafe> IOnlineTurnBasedPtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineUserCloudInterface.h` (Public)


#### class `IOnlineUserCloud`  
`class IOnlineUserCloud`  
_L114-311_
- desc: Provides access to per user cloud file storage
- L118 _protected prototype_ `IOnlineUserCloud();`
- L121 _public prototype_ `virtual ~IOnlineUserCloud();`
- L132 _public prototype_ `virtual bool GetFileContents(const FUniqueNetId& UserId, const FString& FileName, TArray<uint8>& FileContents) = 0;` — Copies the file data into the specified buffer for the specified file @param UserId User owning the storage @param FileName the name of the file to read @param FileContents the out buffer to copy the data into @return true if the data was copied, false otherwise
- L141 _public prototype_ `virtual bool ClearFiles(const FUniqueNetId& UserId) = 0;` — Empties the set of downloaded files if possible (no async tasks outstanding) @param UserId User owning the storage @return true if they could be deleted, false if they could not
- L151 _public prototype_ `virtual bool ClearFile(const FUniqueNetId& UserId, const FString& FileName) = 0;` — Empties the cached data for this file if it is not being downloaded currently @param UserId User owning the storage @param FileName the name of the file to remove from the cache @return true if it could be deleted, false if it could not
- L159 _public prototype_ `virtual void EnumerateUserFiles(const FUniqueNetId& UserId) = 0;` — Requests a list of available User files from the network store @param UserId User owning the storage
- L168 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnEnumerateUserFilesComplete, bool, const FUniqueNetId&);` — Delegate fired when the list of files has been returned from the network store @param bWasSuccessful whether the file list was successful or not @param UserId User owning the storage
- L177 _public prototype_ `virtual void GetUserFileList(const FUniqueNetId& UserId, TArray<FCloudFileHeader>& UserFiles) = 0;` — Returns the list of User files that was returned by the network store @param UserId User owning the storage @param UserFiles out array of file metadata
- L187 _public prototype_ `virtual bool ReadUserFile(const FUniqueNetId& UserId, const FString& FileName) = 0;` — Starts an asynchronous read of the specified user file from the network platform's file store @param UserId User owning the storage @param FileToRead the name of the file to read @return true if the calls starts successfully, false otherwise
- L197 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnReadUserFileComplete, bool, const FUniqueNetId&, const FString&);` — Delegate fired when a user file read from the network platform's storage is complete @param bWasSuccessful whether the file read was successful or not @param UserId User owning the storage @param FileName the name of the file this was for
- L209 _public prototype_ `virtual bool WriteUserFile(const FUniqueNetId& UserId, const FString& FileName, TArray<uint8>& FileContents, bool bCompressBeforeUpload = false) = 0;` — Starts an asynchronous write of the specified user file to the network platform's file store @param UserId User owning the storage @param FileToWrite the name of the file to write @param FileContents the out buffer to copy the data into @param CompressBeforeUpload Whether the file will be compressed before upload. Defaulted to false. Use of this parameter isn't implemented in all platforms. @return true if the calls starts successfully, false otherwise
- L219 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnWriteUserFileProgress64, uint64, const FUniqueNetId&, const FString&);` — Delegate fired at intervals during a user file write to the network platform's storage @param BytesWritten the number of bytes written so far @param UserId User owning the storage @param FileName the name of the file this was for
- L229 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnWriteUserFileComplete, bool, const FUniqueNetId&, const FString&);` — Delegate fired when a user file write to the network platform's storage is complete @param bWasSuccessful whether the file Write was successful or not @param UserId User owning the storage @param FileName the name of the file this was for
- L237 _public prototype_ `virtual void CancelWriteUserFile(const FUniqueNetId& UserId, const FString& FileName) = 0;` — Cancel the ongoing upload of the specified file, if it is in progress @param UserId User owning the storage @param FileNam the name of the file to cancel
- L247 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnWriteUserFileCanceled, bool, const FUniqueNetId&, const FString&);` — Delegate fired when a user file write to the network platform's storage is canceled @param bWasSuccessful whether the file upload cancellations was successful or not @param UserId User owning the storage @param FileName the name of the file this was for
- L259 _public prototype_ `virtual bool DeleteUserFile(const FUniqueNetId& UserId, const FString& FileName, bool bShouldCloudDelete, bool bShouldLocallyDelete) = 0;` — Starts an asynchronous delete of the specified user file from the network platform's file store @param UserId User owning the storage @param FileName the name of the file to delete @param bShouldCloudDelete whether to delete the file from the cloud @param bShouldLocallyDelete whether to delete the file locally @return true if the call starts successfully, false otherwise
- L268 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnDeleteUserFileComplete, bool, const FUniqueNetId&, const FString&);` — Delegate fired when a user file delete from the network platform's storage is complete @param bWasSuccessful whether the file delete was successful or not @param UserId User owning the storage @param FileName the name of the file this was for
- L277 _public prototype_ `virtual bool RequestUsageInfo(const FUniqueNetId& UserId) = 0;` — Starts an asynchronous request to get the usage statistics from the cloud storage service @param UserId      IN      User owning the storage @return true if the call starts successfully, false otherwise
- L287 _public prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnRequestUsageInfoComplete, bool, const FUniqueNetId&, int64, const TOptional<int64>&);` — Delegate fired when getting usage statistics from the network platform's storage is complete @param bWasSuccessful  Whether the operation was successful or not @param UserId          User owning the storage @param BytesUsed       Will be set to the total number of bytes used by the user @param TotalQuota      The total number of bytes the user is entitled to write
- L294 _public prototype_ `virtual void DumpCloudState(const FUniqueNetId& UserId) = 0;` — Print out the state of the cloud for this service @param UserId user to get state for
- L302 _public prototype_ `virtual void DumpCloudFileState(const FUniqueNetId& UserId, const FString& FileName) = 0;` — Print out the state of a file in the cloud for this service @param UserId user to get state for @param FileName filename to get state for
- L310 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnUserCloudAnalyticsEvent, const FString& , const TArray<FAnalyticsEventAttribute>& );` — Delegate fired when we would like to report an event to an analytics provider. @param EventName the name of the event @param Attributes the key/value pairs of analytics event attributes to include with the event

#### Free symbols / members of external scopes

- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineCloud, Log, All);`
- L14 _macro_ `#define UE_LOG_ONLINE_CLOUD(Verbosity, Format, ...) \`
- L19 _macro_ `#define UE_CLOG_ONLINE_CLOUD(Conditional, Verbosity, Format, ...) \`
- L33 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEnumerateUserFilesComplete, bool, const FUniqueNetId&);` — Delegate fired when the list of files has been returned from the network store @param bWasSuccessful whether the file list was successful or not @param UserId User owning the storage
- L33 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEnumerateUserFilesComplete, bool, const FUniqueNetId&);` — Delegate fired when the list of files has been returned from the network store @param bWasSuccessful whether the file list was successful or not @param UserId User owning the storage
- L34 _typedef_ `typedef FOnEnumerateUserFilesComplete::FDelegate FOnEnumerateUserFilesCompleteDelegate;`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnWriteUserFileProgress64, uint64, const FUniqueNetId&, const FString&);` — Delegate fired at intervals during a user file write to the network platform's storage @param BytesWritten the number of bytes written so far @param UserId User owning the storage @param FileName the name of the file this was for
- L44 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnWriteUserFileProgress64, uint64, const FUniqueNetId&, const FString&);` — Delegate fired at intervals during a user file write to the network platform's storage @param BytesWritten the number of bytes written so far @param UserId User owning the storage @param FileName the name of the file this was for
- L45 _typedef_ `typedef FOnWriteUserFileProgress64::FDelegate FOnWriteUserFileProgress64Delegate;`
- L55 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnWriteUserFileComplete, bool, const FUniqueNetId&, const FString&);` — Delegate fired when a user file write to the network platform's storage is complete @param bWasSuccessful whether the file Write was successful or not @param UserId User owning the storage @param FileName the name of the file this was for
- L55 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnWriteUserFileComplete, bool, const FUniqueNetId&, const FString&);` — Delegate fired when a user file write to the network platform's storage is complete @param bWasSuccessful whether the file Write was successful or not @param UserId User owning the storage @param FileName the name of the file this was for
- L56 _typedef_ `typedef FOnWriteUserFileComplete::FDelegate FOnWriteUserFileCompleteDelegate;`
- L66 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnWriteUserFileCanceled, bool, const FUniqueNetId&, const FString&);` — Delegate fired when a user file write to the network platform's storage is canceled @param bWasSuccessful whether the cancellation was successful or not @param UserId User owning the storage @param FileName the name of the file this was for
- L66 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnWriteUserFileCanceled, bool, const FUniqueNetId&, const FString&);` — Delegate fired when a user file write to the network platform's storage is canceled @param bWasSuccessful whether the cancellation was successful or not @param UserId User owning the storage @param FileName the name of the file this was for
- L67 _typedef_ `typedef FOnWriteUserFileCanceled::FDelegate FOnWriteUserFileCanceledDelegate;`
- L77 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnReadUserFileComplete, bool, const FUniqueNetId&, const FString&);` — Delegate fired when a user file read from the network platform's storage is complete @param bWasSuccessful whether the file read was successful or not @param UserId User owning the storage @param FileName the name of the file this was for
- L77 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnReadUserFileComplete, bool, const FUniqueNetId&, const FString&);` — Delegate fired when a user file read from the network platform's storage is complete @param bWasSuccessful whether the file read was successful or not @param UserId User owning the storage @param FileName the name of the file this was for
- L78 _typedef_ `typedef FOnReadUserFileComplete::FDelegate FOnReadUserFileCompleteDelegate;`
- L87 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnDeleteUserFileComplete, bool, const FUniqueNetId&, const FString&);` — Delegate fired when a user file delete from the network platform's storage is complete @param bWasSuccessful whether the file read was successful or not @param UserId User owning the storage @param FileName the name of the file this was for
- L87 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnDeleteUserFileComplete, bool, const FUniqueNetId&, const FString&);` — Delegate fired when a user file delete from the network platform's storage is complete @param bWasSuccessful whether the file read was successful or not @param UserId User owning the storage @param FileName the name of the file this was for
- L88 _typedef_ `typedef FOnDeleteUserFileComplete::FDelegate FOnDeleteUserFileCompleteDelegate;`
- L98 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnRequestUsageInfoComplete, bool, const FUniqueNetId&, int64, const TOptional<int64>&);` — Delegate fired when getting usage statistics from the network platform's storage is complete @param bWasSuccessful  Whether the operation was successful or not @param UserId          User owning the storage @param BytesUsed       Will be set to the total number of bytes used by the user @param TotalQuota      The total number of bytes the user is entitled to write
- L98 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnRequestUsageInfoComplete, bool, const FUniqueNetId&, int64, const TOptional<int64>&);` — Delegate fired when getting usage statistics from the network platform's storage is complete @param bWasSuccessful  Whether the operation was successful or not @param UserId          User owning the storage @param BytesUsed       Will be set to the total number of bytes used by the user @param TotalQuota      The total number of bytes the user is entitled to write
- L99 _typedef_ `typedef FOnRequestUsageInfoComplete::FDelegate FOnRequestUsageInfoCompleteDelegate;`
- L107 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUserCloudAnalyticsEvent, const FString& , const TArray<FAnalyticsEventAttribute>& ) typedef FOnUserCloudAnalyticsEvent::FDelegate FOnUserCloudAnalyticsEventDelegate;` — Delegate fired when we would like to report an event to an analytics provider. @param EventName the name of the event @param Attributes the key/value pairs of analytics event attributes to include with the event
- L108 _typedef_ `typedef FOnUserCloudAnalyticsEvent::FDelegate FOnUserCloudAnalyticsEventDelegate;`
- L313 _typedef_ `typedef TSharedPtr<IOnlineUserCloud, ESPMode::ThreadSafe> IOnlineUserCloudPtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineUserInterface.h` (Public)


#### struct `FExternalIdQueryOptions`  
`struct FExternalIdQueryOptions`  
_L32-53_
- L34 _public function_ `FExternalIdQueryOptions() : bLookupByDisplayName(false)`
- L39 _public function_ `FExternalIdQueryOptions(const FString& InAuthType, const bool bInLookupByDisplayName) : AuthType(InAuthType) , bLookupByDisplayName(bInLookupByDisplayName)`
- L45 _public function_ `FExternalIdQueryOptions(FString&& InAuthType, const bool bInLookupByDisplayName) : AuthType(MoveTemp(InAuthType)) , bLookupByDisplayName(bInLookupByDisplayName)`
- L51 _public member_ `FString AuthType;`
- L52 _public member_ `bool bLookupByDisplayName;` — Lookup by external display name as opposed to external id

#### class `IOnlineUser`  
`class IOnlineUser`  
_L58-166_
- desc: Interface class for obtaining online User info
- L63 _public prototype_ `virtual ~IOnlineUser() = default;`
- L73 _public prototype_ `virtual bool QueryUserInfo(int32 LocalUserNum, const TArray<FUniqueNetIdRef >& UserIds) = 0;` — Starts an async task that queries/reads the info for a list of users @param LocalUserNum the user requesting the query @param UserIds list of users to read info about @return true if the read request was started successfully, false otherwise
- L83 _public prototype_ `DEFINE_ONLINE_PLAYER_DELEGATE_THREE_PARAM(MAX_LOCAL_PLAYERS, OnQueryUserInfoComplete, bool, const TArray< FUniqueNetIdRef >&, const FString&);` — Delegate used when the user query request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param UserIds list of user ids that were queried @param ErrorStr string representing the error condition
- L93 _public prototype_ `virtual bool GetAllUserInfo(int32 LocalUserNum, TArray< TSharedRef<class FOnlineUser> >& OutUsers) = 0;` — Obtains the cached list of online user info @param LocalUserNum the local user that queried for online user data @param OutUsers [out] array that receives the copied data @return true if user info was found
- L103 _public prototype_ `virtual TSharedPtr<FOnlineUser> GetUserInfo(int32 LocalUserNum, const class FUniqueNetId& UserId) = 0;` — Get the cached user entry for a specific user id if found @param LocalUserNum the local user that queried for online user data @param UserId id to use for finding the cached online user @return user info or null ptr if not found
- L114 _public prototype_ `DECLARE_DELEGATE_FiveParams(FOnQueryUserMappingComplete, bool , const FUniqueNetId& , const FString& , const FUniqueNetId& , const FString& );` — Called when done querying for a UserId mapping from a requested display name @param bWasSuccessful true if server was contacted and a valid result received @param UserId user id initiating the request @param DisplayNameOrEmail the name string that was being queried @param FoundUserId the user id matched for the passed name string @param Error string representing the error condition
- L124 _public prototype_ `virtual bool QueryUserIdMapping(const FUniqueNetId& UserId, const FString& DisplayNameOrEmail, const FOnQueryUserMappingComplete& Delegate = FOnQueryUserMappingComplete()) = 0;` — Contacts server to obtain a user id from an arbitrary user-entered name string, eg. display name @param UserId id of the user that is requesting the name string lookup @param DisplayNameOrEmail a string of a display name or email to attempt to map to a user id @return true if the operation was started successfully
- L135 _public prototype_ `DECLARE_DELEGATE_FiveParams(FOnQueryExternalIdMappingsComplete, bool , const FUniqueNetId& , const FExternalIdQueryOptions& , const TArray<FString>& , const FString& );` — Called when done querying for UserId mappings from external ids @param bWasSuccessful true if server was contacted and a valid result received @param UserId user id initiating the request @param QueryOptions Options specifying how to treat the External IDs and other query-related settings @param ExternalIds array of external ids to attempt to map to user ids @param Error string representing the error condition
- L146 _public prototype_ `virtual bool QueryExternalIdMappings(const FUniqueNetId& UserId, const FExternalIdQueryOptions& QueryOptions, const TArray<FString>& ExternalIds, const FOnQueryExternalIdMappingsComplete& Delegate = FOnQueryExternalIdMappingsComplete()) = 0;` — Contacts server to obtain user ids from external ids @param UserId id of the user that is requesting the name string lookup @param QueryOptions Options specifying how to treat the External IDs and other query-related settings @param ExternalIds array of external ids to attempt to map to user ids @return true if the operation was started successfully
- L155 _public prototype_ `virtual void GetExternalIdMappings(const FExternalIdQueryOptions& QueryOptions, const TArray<FString>& ExternalIds, TArray<FUniqueNetIdPtr>& OutIds) = 0;` — Get the cached user ids for the specified external ids @param QueryOptions Options specifying how to treat the External IDs and other query-related settings @param ExternalIds array of external ids to map to user ids @param OutIds array of user ids that map to the specified external ids (can contain null entries)
- L165 _public prototype_ `virtual FUniqueNetIdPtr GetExternalIdMapping(const FExternalIdQueryOptions& QueryOptions, const FString& ExternalId) = 0;` — Get the cached user id for the specified external id @param QueryOptions Options specifying how to treat the External IDs and other query-related settings @param ExternalId external id to obtain user id for @return user info or null ptr if not found

#### Free symbols / members of external scopes

- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineUser, Log, All);`
- L11 _macro_ `#define UE_LOG_ONLINE_USER(Verbosity, Format, ...) \`
- L16 _macro_ `#define UE_CLOG_ONLINE_USER(Conditional, Verbosity, Format, ...) \`
- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnQueryUserInfoComplete, int32, bool, const TArray< FUniqueNetIdRef >&, const FString&);` — Delegate used when the user query request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param UserIds list of user ids that were queried @param ErrorStr string representing the error condition
- L29 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnQueryUserInfoComplete, int32, bool, const TArray< FUniqueNetIdRef >&, const FString&);` — Delegate used when the user query request has completed @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param UserIds list of user ids that were queried @param ErrorStr string representing the error condition
- L30 _typedef_ `typedef FOnQueryUserInfoComplete::FDelegate FOnQueryUserInfoCompleteDelegate;`
- L114 _delegate_ `DECLARE_DELEGATE_FiveParams(FOnQueryUserMappingComplete, bool , const FUniqueNetId& , const FString& , const FUniqueNetId& , const FString& );` — Called when done querying for a UserId mapping from a requested display name @param bWasSuccessful true if server was contacted and a valid result received @param UserId user id initiating the request @param DisplayNameOrEmail the name string that was being queried @param FoundUserId the user id matched for the passed name string @param Error string representing the error condition
- L135 _delegate_ `DECLARE_DELEGATE_FiveParams(FOnQueryExternalIdMappingsComplete, bool , const FUniqueNetId& , const FExternalIdQueryOptions& , const TArray<FString>& , const FString& );` — Called when done querying for UserId mappings from external ids @param bWasSuccessful true if server was contacted and a valid result received @param UserId user id initiating the request @param QueryOptions Options specifying how to treat the External IDs and other query-related settings @param ExternalIds array of external ids to attempt to map to user ids @param Error string representing the error condition

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/TurnBasedMatchInterface.h` (Public)


#### class `UTurnBasedMatchInterface`  
`class UTurnBasedMatchInterface : public UInterface`  
_L9-12_
- reflection: `UINTERFACE(Blueprintable)`
- inherits: `UInterface`

#### class `ITurnBasedMatchInterface`  
`class ITurnBasedMatchInterface`  
_L14-24_
- L20 _public prototype_ `void OnMatchReceivedTurn(const FString& Match, bool bDidBecomeActive);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Online|TurnBased")`
- L23 _public prototype_ `void OnMatchEnded(const FString& Match);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Online|TurnBased")`

### `Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/VoiceInterface.h` (Public)


#### class `IVoiceEngine`  
`class IVoiceEngine`  
_L52-310_
- desc: This interface is an abstract mechanism for acquiring voice data from a hardware source. Each platform implements a specific version of this interface.
- L63 _private prototype_ `virtual bool Init(int32 MaxLocalTalkers, int32 MaxRemoteTalkers) = 0;` — Initialize the voice engine @param MaxLocalTalkers maximum number of local talkers to support @param MaxRemoteTalkers maximum number of remote talkers to support
- L67 _public prototype_ `virtual ~IVoiceEngine() = default;` — Virtual destructor to force proper child cleanup
- L76 _public prototype_ `virtual uint32 StartLocalVoiceProcessing(uint32 LocalUserNum) = 0;` — Starts local voice processing for the specified user index @param UserIndex the user to start processing for @return 0 upon success, an error code otherwise
- L85 _public prototype_ `virtual uint32 StopLocalVoiceProcessing(uint32 LocalUserNum) = 0;` — Stops local voice processing for the specified user index @param UserIndex the user to stop processing of @return 0 upon success, an error code otherwise
- L94 _public prototype_ `virtual uint32 StartRemoteVoiceProcessing(const FUniqueNetId& UniqueId) = 0;` — Starts remote voice processing for the specified user @param UniqueId the unique id of the user that will be talking @return 0 upon success, an error code otherwise
- L103 _public prototype_ `virtual uint32 StopRemoteVoiceProcessing(const FUniqueNetId& UniqueId) = 0;` — Stops remote voice processing for the specified user @param UniqueId the unique id of the user that will no longer be talking @return 0 upon success, an error code otherwise
- L112 _public prototype_ `virtual uint32 RegisterLocalTalker(uint32 LocalUserNum) = 0;` — Registers the user index as a local talker (interested in voice data) @param UserIndex the user index that is going to be a talker @return 0 upon success, an error code otherwise
- L121 _public prototype_ `virtual uint32 UnregisterLocalTalker(uint32 LocalUserNum) = 0;` — Unregisters the user index as a local talker (not interested in voice data) @param UserIndex the user index that is no longer a talker @return 0 upon success, an error code otherwise
- L130 _public prototype_ `virtual uint32 RegisterRemoteTalker(const FUniqueNetId& UniqueId) = 0;` — Registers the unique player id as a remote talker (submitted voice data only) @param UniqueId the id of the remote talker @return 0 upon success, an error code otherwise
- L139 _public prototype_ `virtual uint32 UnregisterRemoteTalker(const FUniqueNetId& UniqueId) = 0;` — Unregisters the unique player id as a remote talker @param UniqueId the id of the remote talker @return 0 upon success, an error code otherwise
- L148 _public prototype_ `virtual bool IsHeadsetPresent(uint32 LocalUserNum) = 0;` — Checks whether a local user index has a headset present or not @param UserIndex the user to check status for @return true if there is a headset, false otherwise
- L157 _public prototype_ `virtual bool IsLocalPlayerTalking(uint32 LocalUserNum) = 0;` — Determines whether a local user index is currently talking or not @param UserIndex the user to check status for @return true if the user is talking, false otherwise
- L166 _public prototype_ `virtual bool IsRemotePlayerTalking(const FUniqueNetId& UniqueId) = 0;` — Determines whether a remote talker is currently talking or not @param UniqueId the unique id of the talker to check status on @return true if the user is talking, false otherwise
- L173 _public prototype_ `virtual uint32 GetVoiceDataReadyFlags() const = 0;` — Returns which local talkers have data ready to be read from the voice system @return Bit mask of talkers that have data to be read (1 << UserIndex)
- L187 _public prototype_ `virtual uint32 SetPlaybackPriority(uint32 LocalUserNum, const FUniqueNetId& RemoteTalkerId, uint32 Priority) = 0;` — Sets the playback priority of a remote talker for the given user. A priority of 0xFFFFFFFF indicates that the player is muted. All other priorities sorted from zero being most important to higher numbers being less important. @param UserIndex the local talker that is setting the priority @param UniqueId the id of the remote talker that is having priority changed @param Priority the new priority to apply to the talker @return 0 upon success, an error code otherwise
- L202 _public prototype_ `virtual uint32 ReadLocalVoiceData(uint32 LocalUserNum, uint8* Data, uint32* Size) = 0;` — Reads local voice data for the specified local talker. The size field contains the buffer size on the way in and contains the amount read on the way out @param UserIndex the local talker that is having their data read @param Data the buffer to copy the voice data into @param Size in: the size of the buffer, out: the amount of data copied @param OutSampleCount: Optional parameter for the starting sample of this voice data. Used for sorting packets received out of order. @return 0 upon success, an error code otherwise
- L203 _public function_ `virtual uint32 ReadLocalVoiceData(uint32 LocalUserNum, uint8* Data, uint32* Size, uint64* OutSampleCount)`
- L219 _public prototype_ `virtual uint32 SubmitRemoteVoiceData(const FUniqueNetId& RemoteTalkerId, uint8* Data, uint32* Size) = 0;` — Submits remote voice data for playback by the voice system. No playback occurs if the priority for this remote talker is 0xFFFFFFFF. Size indicates how much data to submit for processing. It's also an out value in case the system could only process a smaller portion of the data @param RemoteTalkerId the remote talker that sent this data @param Data the buffer to copy the voice data into @param Size in: the size of the buffer, out: the amount of data copied @param InSampleCount optional parameter for the starting sample of this voice packet. Used for sorting packets received out of order. @return 0 upon success, an error code otherwise
- L220 _public function_ `virtual uint32 SubmitRemoteVoiceData(const FUniqueNetIdWrapper& RemoteTalkerId, uint8* Data, uint32* Size, uint64& InSampleCount)`
- L230 _public function_ `virtual uint32 SetRemoteVoiceAmplitude(const FUniqueNetIdWrapper& RemoteTalkerId, float InAmplitude)` — Used when receiving remote voice data to set the amplitude of a remote talker's incoming audio. @param RemoteTalkerId the remote talker that sent the audio we are tracking the amplitude of. @param InAmplitude Current loudness of a given remote talker. @return 0 upon success, an error code otherwise
- L237 _public prototype_ `virtual void Tick(float DeltaTime) = 0;` — Allows for platform specific servicing of devices, etc. @param DeltaTime the amount of time that has elapsed since the last update
- L242 _public prototype_ `virtual FString GetVoiceDebugState() const = 0;` — Get information about the voice state for display
- L250 _public function_ `virtual Audio::FPatchOutputStrongPtr GetMicrophoneOutput()` — This can be used to get arbitrarily tap outgoing microphone audio from local players to use elsewhere in your application. for information on usage, see MultithreadedPatching.h. @return nullptr if the VoiceEngine implementation being used does not support tapping audio output from the microphone.
- L261 _public function_ `virtual Audio::FPatchOutputStrongPtr GetRemoteTalkerOutput()` — This can be used to get arbitrarily tap incoming VOIP audio from remote players to use elsewhere in your application. for information on usage, see MultithreadedPatching.h. @return nullptr if the VoiceEngine implementation being used does not support tapping incoming audio.
- L270 _public function_ `virtual float GetMicrophoneAmplitude(int32 LocalUserNum)` — This can be used to get how loud the given microphone input is, typically on a scale between 0.0 and 1.0. @return -1.0 if getting the mic amplitude is not supported on this platform or LocalUserNum was invalid, 0.0-1.0 otherwise.
- L279 _public function_ `virtual float GetIncomingAudioAmplitude(const FUniqueNetIdWrapper& RemoteUserId)` — This can be used to get how loud the given microphone input is, typically on a scale between 0.0 and 1.0. @return -1.0 if getting the mic amplitude is not supported on this platform or RemoteUserId is invalid, 0.0-1.0 otherwise.
- L289 _public function_ `virtual bool PatchRemoteTalkerOutputToEndpoint(const FString& InDeviceName, bool bMuteInGameOutput = true)` — This can be used to patch incoming audio to a different audio device. @param InDeviceName- name of the device to patch to. @param bMuteInGameOutput- if set to true, the audio going out to the game will be muted.
- L298 _public function_ `virtual bool PatchLocalTalkerOutputToEndpoint(const FString& InDeviceName)` — This can be used to patch outgoing audio to a different audio device. @param InDeviceName- name of the device to patch to.
- L306 _public function_ `virtual void DisconnectAllEndpoints()` — When called, disconnects all additional audio endpoints we patched to using PatchVoiceOutputToDevice().

#### class `IOnlineVoice`  
`class IOnlineVoice`  
_L318-575_
- desc: This interface is an abstract mechanism for managing voice data. Each platform implements a specific version of this interface.
- L321 _protected function_ `IOnlineVoice()`
- L331 _protected prototype_ `virtual void ProcessMuteChangeNotification() = 0;` — Re-evaluates the muting list for all local talkers
- L334 _public function_ `virtual void Shutdown()`
- L339 _public function_ `virtual bool Init()` — Initialize the voice interface
- L342 _public prototype_ `virtual ~IOnlineVoice() = default;` — Virtual destructor to force proper child cleanup
- L350 _public prototype_ `virtual void StartNetworkedVoice(uint8 LocalUserNum) = 0;` — Tells the voice layer that networked processing of the voice data is allowed for the specified player. This allows for push-to-talk style voice communication @param LocalUserNum the local user to allow network transmission for
- L358 _public prototype_ `virtual void StopNetworkedVoice(uint8 LocalUserNum) = 0;` — Tells the voice layer to stop processing networked voice support for the specified player. This allows for push-to-talk style voice communication @param LocalUserNum the local user to disallow network transmission for
- L367 _public prototype_ `virtual bool RegisterLocalTalker(uint32 LocalUserNum) = 0;` — Registers the user index as a local talker (interested in voice data) @param UserIndex the user index that is going to be a talker @return true if the call succeeded, false otherwise
- L372 _public prototype_ `virtual void RegisterLocalTalkers() = 0;` — Registers all signed in local talkers
- L381 _public prototype_ `virtual bool UnregisterLocalTalker(uint32 LocalUserNum) = 0;` — Unregisters the user index as a local talker (not interested in voice data) @param UserIndex the user index that is no longer a talker @return true if the call succeeded, false otherwise
- L386 _public prototype_ `virtual void UnregisterLocalTalkers() = 0;` — Unregisters all signed in local talkers
- L395 _public prototype_ `virtual bool RegisterRemoteTalker(const FUniqueNetId& UniqueId) = 0;` — Registers the unique player id as a remote talker (submitted voice data only) @param UniqueId the id of the remote talker @return true if the call succeeded, false otherwise
- L404 _public prototype_ `virtual bool UnregisterRemoteTalker(const FUniqueNetId& UniqueId) = 0;` — Unregisters the unique player id as a remote talker @param UniqueId the id of the remote talker @return true if the call succeeded, false otherwise
- L410 _public prototype_ `virtual void RemoveAllRemoteTalkers() = 0;` — Iterates the current remote talker list unregistering them with the voice engine and our internal state
- L419 _public prototype_ `virtual bool IsHeadsetPresent(uint32 LocalUserNum) = 0;` — Checks whether a local user index has a headset present or not @param UserIndex the user to check status for @return true if there is a headset, false otherwise
- L428 _public prototype_ `virtual bool IsLocalPlayerTalking(uint32 LocalUserNum) = 0;` — Determines whether a local user index is currently talking or not @param UserIndex the user to check status for @return true if the user is talking, false otherwise
- L437 _public prototype_ `virtual bool IsRemotePlayerTalking(const FUniqueNetId& UniqueId) = 0;` — Determines whether a remote talker is currently talking or not @param UniqueId the unique id of the talker to check status on @return true if the user is talking, false otherwise
- L446 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnPlayerTalkingStateChanged, FUniqueNetIdRef, bool);` — Delegate called when a player is talking either remotely or locally Called once for each active talker each frame @param TalkerId the player whose talking state has changed @param bIsTalking if true, player is now talking, otherwise they have now stopped
- L456 _public prototype_ `virtual bool IsMuted(uint32 LocalUserNum, const FUniqueNetId& UniqueId) const = 0;` — Checks that a unique player id is on the specified user's mute list @param LocalUserNum the controller number of the associated user @param UniqueId the id of the player being checked @return true if the specified user is muted, false otherwise
- L468 _public prototype_ `virtual bool MuteRemoteTalker(uint8 LocalUserNum, const FUniqueNetId& PlayerId, bool bIsSystemWide) = 0;` — Mutes a remote talker for the specified local player. NOTE: This only mutes them in the game unless the bIsSystemWide flag is true, which attempts to mute them globally @param LocalUserNum the user that is muting the remote talker @param PlayerId the remote talker that is being muted @param bIsSystemWide whether to try to mute them globally or not @return true if the function succeeds, false otherwise
- L480 _public prototype_ `virtual bool UnmuteRemoteTalker(uint8 LocalUserNum, const FUniqueNetId& PlayerId, bool bIsSystemWide) = 0;` — Allows a remote talker to talk to the specified local player. NOTE: This only unmutes them in the game unless the bIsSystemWide flag is true, which attempts to unmute them globally @param LocalUserNum the user that is allowing the remote talker to talk @param PlayerId the remote talker that is being restored to talking @param bIsSystemWide whether to try to unmute them globally or not @return TRUE if the function succeeds, FALSE otherwise
- L487 _public prototype_ `virtual TSharedPtr<class FVoicePacket> SerializeRemotePacket(FArchive& Ar) = 0;` — Convert generic network packet data back into voice data @param Ar archive to read data from
- L494 _public prototype_ `virtual TSharedPtr<class FVoicePacket> GetLocalPacket(uint32 LocalUserNum) = 0;` — Get the local voice packet intended for send @param LocalUserNum user index voice packet to retrieve
- L499 _public prototype_ `virtual int32 GetNumLocalTalkers() = 0;` — @return total number of local talkers on this system
- L504 _public prototype_ `virtual void ClearVoicePackets() = 0;` — Clears all voice packets currently queued for send
- L511 _public prototype_ `virtual void Tick(float DeltaTime) = 0;` — Allows for platform specific servicing of devices, etc. @param DeltaTime the amount of time that has elapsed since the last update
- L516 _public prototype_ `virtual FString GetVoiceDebugState() const = 0;` — Get information about the voice state for display
- L524 _public function_ `virtual Audio::FPatchOutputStrongPtr GetMicrophoneOutput()` — This can be used to get arbitrarily tap outgoing microphone audio from local players to use elsewhere in your application. for information on usage, see MultithreadedPatching.h. @return nullptr if the VoiceEngine implementation being used does not support tapping audio output from the microphone.
- L535 _public function_ `virtual Audio::FPatchOutputStrongPtr GetRemoteTalkerOutput()` — This can be used to get arbitrarily tap incoming VOIP audio from remote players to use elsewhere in your application. for information on usage, see MultithreadedPatching.h. @return nullptr if the VoiceEngine implementation being used does not support tapping incoming audio.
- L544 _public function_ `virtual float GetAmplitudeOfRemoteTalker(const FUniqueNetId& PlayerId)` — This returns the current amplitude of a given player's incoming audio. @return -1.0 if the PlayerId was not found or if this isn't supported with the current Voice Interface, and a value from 0.0 to 1.0 otherwise.
- L554 _public function_ `virtual bool PatchRemoteTalkerOutputToEndpoint(const FString& InDeviceName, bool bMuteInGameOutput = true)` — This can be used to patch incoming audio to a different audio device. @param InDeviceName- name of the device to patch to. @param bMuteInGameOutput- if set to true, the audio going out to the game will be muted.
- L563 _public function_ `virtual bool PatchLocalTalkerOutputToEndpoint(const FString& InDeviceName)` — This can be used to patch outgoing audio to a different audio device. @param InDeviceName- name of the device to patch to.
- L572 _public function_ `virtual void DisconnectAllEndpoints()` — When called, disconnects all additional audio endpoints we patched to using PatchRemoteTalkerOutputToEndpoint().

#### struct `FLocalTalker`  
`struct FLocalTalker`  
_L582-603_
- desc: Definition of a local player's talking state
- L585 _public member_ `bool bIsRegistered;` — Whether this player was already registered with the voice interface or not
- L587 _public member_ `bool bHasNetworkedVoice;` — Whether the talker should send network data
- L589 _public member_ `float LastNotificationTime;` — Used to trigger talking delegates only after a certain period of time has passed
- L591 _public member_ `bool bWasTalking;` — Whether the local talker was speaking last frame
- L593 _public member_ `bool bIsTalking;` — Whether the local talker is speaking this frame
- L596 _public function_ `FLocalTalker() : bIsRegistered(false), bHasNetworkedVoice(false), LastNotificationTime(0.0f), bWasTalking(false), bIsTalking(false)` — Constructors

#### struct `FRemoteTalker`  
`struct FRemoteTalker`  
_L608-626_
- desc: Definition of a remote player's talking state
- L611 _public member_ `FUniqueNetIdPtr TalkerId;` — The unique id for this talker
- L613 _public member_ `float LastNotificationTime;` — Used to trigger talking delegates only after a certain period of time has passed
- L615 _public member_ `bool bWasTalking;` — Whether the remote talker was speaking last frame
- L617 _public member_ `bool bIsTalking;` — Whether the remote talker is speaking this frame
- L620 _public function_ `FRemoteTalker() : TalkerId(NULL), LastNotificationTime(0.0f), bWasTalking(false), bIsTalking(false)` — Constructors

#### Free symbols / members of external scopes

- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVoiceEngine, Log, All);`
- L13 _macro_ `#define UE_LOG_ONLINE_VOICEENGINE(Verbosity, Format, ...) \`
- L18 _macro_ `#define UE_CLOG_ONLINE_VOICEENGINE(Conditional, Verbosity, Format, ...) \`
- L23 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineVoice, Log, All);`
- L25 _macro_ `#define UE_LOG_ONLINE_VOICE(Verbosity, Format, ...) \`
- L30 _macro_ `#define UE_CLOG_ONLINE_VOICE(Conditional, Verbosity, Format, ...) \`
- L36 _macro_ `#define VOICE_LOOPBACK !UE_BUILD_SHIPPING` — Enable to pipe local voice data back to this client as remote data
- L45 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerTalkingStateChanged, FUniqueNetIdRef, bool);` — Delegate called when a player is talking either remotely or locally Called once for each active talker each frame @param TalkerId the player whose talking state has changed @param bIsTalking if true, player is now talking, otherwise they have now stopped
- L45 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerTalkingStateChanged, FUniqueNetIdRef, bool);` — Delegate called when a player is talking either remotely or locally Called once for each active talker each frame @param TalkerId the player whose talking state has changed @param bIsTalking if true, player is now talking, otherwise they have now stopped
- L46 _typedef_ `typedef FOnPlayerTalkingStateChanged::FDelegate FOnPlayerTalkingStateChangedDelegate;`
- L312 _typedef_ `typedef TSharedPtr<IVoiceEngine, ESPMode::ThreadSafe> IVoiceEnginePtr;`
- L577 _typedef_ `typedef TSharedPtr<IOnlineVoice, ESPMode::ThreadSafe> IOnlineVoicePtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/NamedInterfaces.h` (Public)


#### struct `FNamedInterface`  
`struct FNamedInterface`  
_L13-29_
- reflection: `USTRUCT()`
- desc: Holds a named object interface for dynamically bound interfaces
- L17 _public function_ `FNamedInterface() : InterfaceName(NAME_None), InterfaceObject(NULL)`
- L25 _public member_ `FName InterfaceName;` — `UPROPERTY()` — The name to bind this object to
- L28 _public member_ `TObjectPtr<UObject> InterfaceObject;` — `UPROPERTY()` — The object to store at this location

#### struct `FNamedInterfaceDef`  
`struct FNamedInterfaceDef`  
_L33-48_
- reflection: `USTRUCT()`
- desc: Holds a name to class name mapping for adding the named interfaces automatically
- L37 _public function_ `FNamedInterfaceDef() : InterfaceName(NAME_None)`
- L44 _public member_ `FName InterfaceName;` — `UPROPERTY()` — The name to bind this object to
- L47 _public member_ `FString InterfaceClassName;` — `UPROPERTY()` — The class to load and create for the named interface

#### class `UNamedInterfaces`  
`class UNamedInterfaces: public UObject`  
_L54-95_
- reflection: `UCLASS(transient, config=Engine)`
- inherits: `UObject`
- desc: Named interfaces are a registry of UObjects accessible by an FName key that will persist for the lifetime of the process
- L61 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnCleanup);` — Cleanup delegate fired on destruction
- L64 _private prototype_ `virtual void BeginDestroy() override;` — UObject interface begin
- L70 _private prototype_ `void Initialize();` — Initialize the named interface and create any predefined interfaces
- L73 _private prototype_ `class UObject* GetNamedInterface(FName InterfaceName) const;` — @return an interface stored by name
- L76 _private prototype_ `void SetNamedInterface(FName InterfaceName, class UObject* NewInterface);` — set an interface stored by name, replacing any existing
- L79 _private function_ `int32 GetNumInterfaces()` — get number of current named interfaces
- L82 _private function_ `FOnCleanup& OnCleanup()` — @return delegate fired on cleanup
- L88 _private member_ `TArray<FNamedInterface> NamedInterfaces;` — `UPROPERTY()` — Holds the set of registered named interfaces
- L92 _private member_ `TArray<FNamedInterfaceDef> NamedInterfaceDefs;` — `UPROPERTY(config)` — The list of named interfaces to automatically create and store
- L94 _private member_ `FOnCleanup CleanupDelegates;`

#### Free symbols / members of external scopes

- L61 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCleanup);` — Cleanup delegate fired on destruction

### `Plugins/Online/OnlineSubsystem/Source/Public/NboSerializerOSS.h` (Public)


#### class `FNboSerializeToBufferOSS`  
`class FNboSerializeToBufferOSS : public FNboSerializeToBuffer`  
_L12-131_
- inherits: `FNboSerializeToBuffer`
- desc: Serializes data in network byte order form into a buffer
- L16 _public function_ `FNboSerializeToBufferOSS() : FNboSerializeToBuffer(512)` — Default constructor zeros num bytes
- L22 _public function_ `FNboSerializeToBufferOSS(uint32 Size) : FNboSerializeToBuffer(Size)` — Constructor specifying the size to use

#### class `FNboSerializeFromBufferOSS`  
`class FNboSerializeFromBufferOSS : public FNboSerializeFromBuffer`  
_L136-269_
- inherits: `FNboSerializeFromBuffer`
- desc: Class used to read data from a NBO data buffer
- L142 _public function_ `FNboSerializeFromBufferOSS(const uint8* Packet,int32 Length) : FNboSerializeFromBuffer(Packet,Length)` — Initializes the buffer, size, and zeros the read offset

#### Free symbols / members of external scopes

- L31 _function_ `template<class KeyType, class ValueType> friend inline FNboSerializeToBufferOSS& operator<<(FNboSerializeToBufferOSS& Ar, const FOnlineKeyValuePairs<KeyType,ValueType>& KeyValuePairs)` — Writes a list of key value pairs to buffer
- L45 _function_ `friend inline FNboSerializeToBufferOSS& operator<<(FNboSerializeToBufferOSS& Ar,const FVariantData& KeyValuePair)` — Adds a key value pair to the buffer
- L121 _function_ `friend inline FNboSerializeToBufferOSS& operator<<(FNboSerializeToBufferOSS& Ar,const FOnlineSessionSetting& Setting)` — Adds a single online session setting to the buffer
- L151 _function_ `template<class KeyType, class ValueType> friend inline FNboSerializeFromBufferOSS& operator>>(FNboSerializeFromBufferOSS& Ar, FOnlineKeyValuePairs<KeyType,ValueType>& KeyValuePairs)` — Reads a list of key value pairs from the buffer
- L170 _function_ `friend inline FNboSerializeFromBufferOSS& operator>>(FNboSerializeFromBufferOSS& Ar,FVariantData& KeyValuePair)` — Reads a key value pair from the buffer
- L256 _function_ `friend inline FNboSerializeFromBufferOSS& operator>>(FNboSerializeFromBufferOSS& Ar,FOnlineSessionSetting& Setting)` — Reads a single session setting from the buffer

### `Plugins/Online/OnlineSubsystem/Source/Public/Online.h` (Public)


#### Free symbols / members of external scopes

- L17 _macro_ `#define IMPLEMENT_GET_INTERFACE(InterfaceType) \` — Macro to handle the boilerplate of accessing the proper online subsystem and getting the requested interface
- L33 _namespace_ `namespace Online`
- L40 _prototype_ `IMPLEMENT_GET_INTERFACE(Session);` (scope `Online`) — Get the interface for accessing the session services @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate session service
- L47 _prototype_ `IMPLEMENT_GET_INTERFACE(Party);` (scope `Online`) — Get the interface for accessing the party services @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate party service
- L54 _prototype_ `IMPLEMENT_GET_INTERFACE(Chat);` (scope `Online`) — Get the interface for accessing the chat services @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate party service
- L61 _prototype_ `IMPLEMENT_GET_INTERFACE(Friends);` (scope `Online`) — Get the interface for accessing the player friends services @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate friend service
- L68 _prototype_ `IMPLEMENT_GET_INTERFACE(User);` (scope `Online`) — Get the interface for accessing user information by uniqueid @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate user service
- L74 _prototype_ `IMPLEMENT_GET_INTERFACE(SharedCloud);` (scope `Online`) — Get the interface for sharing user files in the cloud @return Interface pointer for the appropriate cloud service
- L80 _prototype_ `IMPLEMENT_GET_INTERFACE(UserCloud);` (scope `Online`) — Get the interface for accessing user files in the cloud @return Interface pointer for the appropriate cloud service
- L87 _prototype_ `IMPLEMENT_GET_INTERFACE(Voice);` (scope `Online`) — Get the interface for accessing voice services @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate voice service
- L94 _prototype_ `IMPLEMENT_GET_INTERFACE(ExternalUI);` (scope `Online`) — Get the interface for accessing the external UIs of a service @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate external UI service
- L101 _prototype_ `IMPLEMENT_GET_INTERFACE(Time);` (scope `Online`) — Get the interface for accessing the server time from an online service @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate server time service
- L108 _prototype_ `IMPLEMENT_GET_INTERFACE(Identity);` (scope `Online`) — Get the interface for accessing identity online services @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate identity service
- L115 _prototype_ `IMPLEMENT_GET_INTERFACE(TitleFile);` (scope `Online`) — Get the interface for accessing title file online services @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate service
- L122 _prototype_ `IMPLEMENT_GET_INTERFACE(Entitlements);` (scope `Online`) — Get the interface for accessing entitlements online services @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate service
- L129 _prototype_ `IMPLEMENT_GET_INTERFACE(Leaderboards);` (scope `Online`) — Get the interface for accessing platform leaderboards @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate leaderboard service
- L136 _prototype_ `IMPLEMENT_GET_INTERFACE(Achievements);` (scope `Online`) — Get the interface for accessing entitlements online services @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate service
- L143 _prototype_ `IMPLEMENT_GET_INTERFACE(Events);` (scope `Online`) — Get the interface for accessing online events @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate service
- L150 _prototype_ `IMPLEMENT_GET_INTERFACE(Presence);` (scope `Online`) — Get the interface for accessing rich presence online services @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate service
- L157 _prototype_ `IMPLEMENT_GET_INTERFACE(Stats);` (scope `Online`) — Get the interface for accessing the stats services @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate party service
- L164 _prototype_ `IMPLEMENT_GET_INTERFACE(Purchase);` (scope `Online`) — Get the interface for accessing the purchasing services @param SubsystemName - Name of the requested online service @return Interface pointer for the appropriate party service

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineAsyncTaskManager.h` (Public)


#### class `FOnlineAsyncItem`  
`class FOnlineAsyncItem`  
_L21-68_
- desc: Base class of any async task that can be returned to the game thread by the async task manager May originate on the game thread, or generated by an external platform service callback from the online thread itself
- L25 _protected member_ `double StartTime;` — Time the task was created
- L28 _protected function_ `FOnlineAsyncItem()` — Hidden on purpose
- L35 _public prototype_ `virtual ~FOnlineAsyncItem() = default;`
- L40 _public prototype_ `virtual FString ToString() const = 0;` — Get a human readable description of task
- L45 _public function_ `double GetElapsedTime()` — Updates the amount of elapsed time this task has taken
- L54 _public function_ `virtual void Finalize()` — Give the async task a chance to marshal its data back to the game thread Can only be called on the game thread by the async task manager
- L63 _public function_ `virtual void TriggerDelegates()` — Async task is given a chance to trigger it's delegates

#### class `FOnlineAsyncEvent`  
`template<class T> class FOnlineAsyncEvent : public FOnlineAsyncItem`  
_L75-94_
- inherits: `FOnlineAsyncItem`
- desc: An event triggered by the online subsystem to be routed to the game thread for processing Originates on the online thread
- L83 _private function_ `FOnlineAsyncEvent() : Subsystem(nullptr)` — Hidden on purpose
- L90 _public function_ `FOnlineAsyncEvent(T* InSubsystem) : Subsystem(InSubsystem)`

#### class `FOnlineAsyncTask`  
`class FOnlineAsyncTask : public FOnlineAsyncItem`  
_L100-145_
- inherits: `FOnlineAsyncItem`
- desc: A single task for an online service to be queued with the async task manager Originates on the game thread
- L105 _protected function_ `FOnlineAsyncTask()` — Hidden on purpose
- L111 _public prototype_ `virtual ~FOnlineAsyncTask() = default;`
- L116 _public function_ `virtual void Initialize()` — Initialize the task - called on game thread when queued
- L122 _public prototype_ `virtual bool IsDone() const = 0;` — Check the state of the async task @return true if complete, false otherwise
- L128 _public prototype_ `virtual bool WasSuccessful() const = 0;` — Check the success of the async task @return true if successful, false otherwise
- L134 _public function_ `virtual void Tick()` — Give the async task time to do its work Can only be called on the async task manager thread
- L144 _public function_ `virtual void CancelWhenTimeout()` — If cancel is supported, cancel when timeout if timeout is set for this task Not putting this in Tick directly because existing subclasses could be overriding Tick without calling super::Tick

#### class `FOnlineAsyncTaskGenericCallable`  
`template<class CallableType> class FOnlineAsyncTaskGenericCallable : public FOnlineAsyncTask`  
_L155-179_
- inherits: `FOnlineAsyncTask`
- desc: An async task that can execute any callable type with no parameters. For example, l lambda, or an object with an operator(). Useful for calling simple functions that need to run on the game thread, but are invoked from an online service thread.
- L163 _public function_ `explicit FOnlineAsyncTaskGenericCallable(const CallableType& InCallable) : CallableObject(InCallable)` — Constructor. @param InCallable any object that can be called with no parameters, usually a lambda
- L166 _public function_ `virtual void Finalize() override`
- L171 _public function_ `virtual FString ToString() const override`
- L173 _public function_ `virtual bool IsDone() const override`
- L174 _public function_ `virtual bool WasSuccessful() const override`
- L178 _private member_ `CallableType CallableObject;` — Stored copy of the object to invoke on the game thread.

#### class `FOnlineAsyncTaskThreadedGenericCallable`  
`template<class CallableType> class FOnlineAsyncTaskThreadedGenericCallable : public FOnlineAsyncTask`  
_L187-220_
- inherits: `FOnlineAsyncTask`
- desc: An async task that can execute any callable type with no parameters. For example, l lambda, or an object with an operator(). Useful for calling simple functions that need to run on the ONLINE thread.
- L195 _public function_ `explicit FOnlineAsyncTaskThreadedGenericCallable(const FString& InCallableName, const CallableType& InCallable) : bHasTicked(false) , CallableObject(InCallable) , CallableName(InCallableName)` — Constructor. @param InCallable any object that can be called with no parameters, usually a lambda
- L202 _public function_ `virtual void Tick() override`
- L208 _public function_ `virtual FString ToString() const override`
- L210 _public function_ `virtual bool IsDone() const override`
- L211 _public function_ `virtual bool WasSuccessful() const override`
- L215 _private member_ `bool bHasTicked;` — True after it has ticked once and run the Callable on the online thread
- L217 _private member_ `CallableType CallableObject;` — Stored copy of the object to invoke on the game thread.
- L219 _private member_ `FString CallableName;` — Name of the task to help logging

#### class `FOnlineAsyncTaskBasic`  
`template<class T> class FOnlineAsyncTaskBasic : public FOnlineAsyncTask`  
_L223-286_
- inherits: `FOnlineAsyncTask`
- L230 _private member_ `FThreadSafeBool bIsComplete;` — Has the task completed
- L232 _private member_ `FThreadSafeBool bWasSuccessful;` — Has the task complete successfully
- L235 _private function_ `FOnlineAsyncTaskBasic() : Subsystem(nullptr) , bIsComplete(false) , bWasSuccessful(false)` — Hidden on purpose
- L244 _public function_ `FOnlineAsyncTaskBasic(T* const InSubsystem) : Subsystem(InSubsystem) , bIsComplete(false) , bWasSuccessful(false)`
- L251 _public prototype_ `virtual ~FOnlineAsyncTaskBasic() = default;`
- L257 _public function_ `FOnlineAsyncTaskBasic& operator= (const FOnlineAsyncTaskBasic& Other)` — Copies the contents of this task to another Use sparingly, it is not atomic.
- L273 _public function_ `virtual bool IsDone() const override` — Check the state of the async task @return true if complete, false otherwise
- L282 _public function_ `virtual bool WasSuccessful() const override` — Check the success of the async task @return true if successful, false otherwise

#### class `FOnlineAsyncTaskManager`  
`class FOnlineAsyncTaskManager : public FRunnable, FSingleThreadRunnable`  
_L304-502_
- inherits: `FRunnable,FSingleThreadRunnable`
- desc: The foundation of all async operations in every online subsystem A task manager ticks on its own thread, managing both a serial and parallel queue of FOnlineAsyncTasks Each task works through the serial queue in the following manner GameThread - Initialize() OnlineThread -- Tick() until IsDone() -- Add task to OutQueue GameThread - Finalize() - TriggerDelegates() Parallel task queue works in a similar flow, except the tasks don't wait for any previous tasks to complete
- L309 _private member_ `FOnlineAsyncTask* ActiveSerialTask = nullptr;` — The current active task processed serially by the async task manager
- L311 _private member_ `FCriticalSection ActiveSerialTaskLock;` — Critical section for modifying the active serial task
- L313 _private member_ `double ActiveSerialTaskStartTime = 0.0;` — When the active serial task was started on the game thread
- L315 _private member_ `std::atomic<bool> bActiveSerialTaskBreachReported = false;` — Has a breach been reported for the active task
- L329 _private member_ `FOnlineThreadTickInfo OnlineThreadTickInfo;` — Info on what the online thread is currently doing
- L331 _private member_ `FCriticalSection OnlineThreadTickInfoLock;` — Critical section for modifying this tick info
- L334 _private member_ `bool bEnableReportBreach = false;` — Should we report a breach or not
- L336 _private member_ `float ConfigBreachTimeSeconds = 60.0;` — Time to allow a serial task / the online thread tick to run before reporting
- L341 _protected member_ `TArray<FOnlineAsyncTask*> QueuedSerialTasks;` — Game thread async tasks are queued up here for processing on the online thread
- L343 _protected member_ `FTransactionallySafeCriticalSection QueuedSerialTasksLock;` — Critical section for thread safe operation of the event in queue
- L346 _protected member_ `int32 MaxParallelTasks;` — Number of tasks that can run in parallel
- L348 _protected member_ `std::atomic<bool> bReloadMaxParallelTasksConfig;` — Signal game thread to reload the MaxParallelTasks value from config
- L350 _protected member_ `TQueue<FOnlineAsyncTask*, EQueueMode::Mpsc> QueuedParallelTasks;` — This queue is for tasks that are safe to run in parallel with one another
- L352 _protected member_ `TArray<FOnlineAsyncTask*> ParallelTasks;` — Tasks that are running in parallel
- L354 _protected member_ `FCriticalSection ParallelTasksLock;` — Critical section for thread safe operation of the list
- L357 _protected member_ `TArray<FOnlineAsyncItem*> OutQueue;` — Completed online requests are queued up here for processing on the game thread
- L359 _protected member_ `FTransactionallySafeCriticalSection OutQueueLock;` — Critical section for thread safe operation of the out queue
- L362 _protected member_ `FEvent* WorkEvent;` — Trigger event to signal the queue has tasks that need processing
- L365 _protected member_ `uint32 PollingInterval;` — Min amount of time to poll for the current task to complete
- L368 _protected member_ `FThreadSafeBool bRequestingExit;` — Should this manager and the thread exit
- L371 _protected member_ `static int32 InvocationCount;` — Number of async task managers running currently
- L377 _protected prototype_ `void RemoveFromParallelTasks(FOnlineAsyncTask* OldTask);` — Remove a parallel async task from the parallel queue @param OldTask - some request of the online services
- L386 _public prototype_ `FOnlineAsyncTaskManager();`
- L387 _public prototype_ `virtual ~FOnlineAsyncTaskManager();`
- L394 _public prototype_ `virtual bool Init();` — Init the online async task manager @return True if initialization was successful, false otherwise
- L402 _public prototype_ `virtual uint32 Run();` — This is where all per object thread work is done. This is only called if the initialization was successful. @return The exit code of the runnable object
- L407 _public prototype_ `virtual void Stop();` — This is called if a thread is requested to terminate early
- L412 _public prototype_ `virtual void Exit();` — Called in the context of the aggregating thread to perform any cleanup.
- L418 _public function_ `virtual class FSingleThreadRunnable* GetSingleThreadInterface()` — FSingleThreadRunnable accessor for ticking this FRunnable when multi-threading is disabled. @return FSingleThreadRunnable Interface for this FRunnable object.
- L424 _public prototype_ `void AddToInQueue(FOnlineAsyncTask* NewTask);` — Add online async tasks that need processing onto the incoming queue @param NewTask - some request of the online services
- L430 _public prototype_ `void AddToOutQueue(FOnlineAsyncItem* CompletedItem);` — Add completed online async tasks that need processing onto the queue @param CompletedItem - some finished request of the online services
- L440 _public function_ `template<class CallableType> void AddGenericToOutQueue(const CallableType& InCallable)` — Add a new item to the out queue that will call InCallable on the game thread. Very useful when passing in lambdas as parameters, since this function will automatically deduce the template parameter type for FOnlineAsyncItemGenericCallable. @param InCallable the callable object to execute on the game thread.
- L456 _public function_ `template<class CallableType> void AddGenericToInQueue(const CallableType& InCallable)` — Add a new item to the in queue that will call InCallable on the game thread. Very useful when passing in lambdas as parameters, since this function will automatically deduce the template parameter type for FOnlineAsyncItemGenericCallable. Unlike AddGenericToOutQueue, this version is useful when you want to ensure that the callable will only execute after any existing tasks in the queue are complete. @param InCallable the callable object to execute on the game thread.
- L472 _public function_ `template<class CallableType> void AddGenericToInQueueOnlineThread(const FString& CallableName, const CallableType& InCallable)` — Add a new item to the in queue that will call InCallable on the ONLINE thread. Very useful when passing in lambdas as parameters, since this function will automatically deduce the template parameter type for FOnlineAsyncItemGenericCallable. Unlike AddGenericToInQueue, this version runs the task on the online thread in Tick(), instead of Finalize on the game thread. @param InCallable the callable object to execute on the game thread.
- L481 _public prototype_ `void AddToParallelTasks(FOnlineAsyncTask* NewTask);` — Add a new online async task that is safe to run in parallel @param NewTask - some request of the online services
- L488 _public prototype_ `void GameTick();` — ** CALL ONLY FROM GAME THREAD ** Give the completed async tasks a chance to marshal their data back onto the game thread Calling delegates where appropriate
- L494 _public prototype_ `virtual void OnlineTick() = 0;` — ** CALL ONLY FROM ONLINE THREAD ** Give the online service a chance to do work
- L500 _public prototype_ `virtual void Tick();` — Tick() is called by both multithreaded and single threaded runnable

#### struct `FOnlineAsyncTaskManager::FOnlineThreadTickInfo`  
`struct FOnlineThreadTickInfo`  
_L317-327_
- L320 _public member_ `bool bIsTicking = false;` — Is the online thread currently ticking
- L322 _public member_ `double TickStartTime = 0.0;` — Time the online thread began this tick
- L324 _public member_ `FOnlineAsyncTask* CurrentTask = nullptr;` — Task the online thread is currently ticking
- L326 _public member_ `bool bBreachReported = false;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API ONLINESUBSYSTEM_API`

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineDelegateMacros.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define DEFINE_ONLINE_DELEGATE_BASE(DelegateName) \`
- L25 _macro_ `#define DEFINE_ONLINE_DELEGATE(DelegateName) \`
- L32 _macro_ `#define DEFINE_ONLINE_DELEGATE_ONE_PARAM(DelegateName, Param1Type) \`
- L39 _macro_ `#define DEFINE_ONLINE_DELEGATE_TWO_PARAM(DelegateName, Param1Type, Param2Type) \`
- L46 _macro_ `#define DEFINE_ONLINE_DELEGATE_THREE_PARAM(DelegateName, Param1Type, Param2Type, Param3Type) \`
- L53 _macro_ `#define DEFINE_ONLINE_DELEGATE_FOUR_PARAM(DelegateName, Param1Type, Param2Type, Param3Type, Param4Type) \`
- L60 _macro_ `#define DEFINE_ONLINE_DELEGATE_FIVE_PARAM(DelegateName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type) \`
- L67 _macro_ `#define DEFINE_ONLINE_DELEGATE_SIX_PARAM(DelegateName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type) \`
- L74 _macro_ `#define DEFINE_ONLINE_DELEGATE_SEVEN_PARAM(DelegateName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type) \`
- L82 _macro_ `#define DEFINE_ONLINE_PLAYER_DELEGATE_BASE(MaxPlayers, DelegateName) \`
- L111 _macro_ `#define DEFINE_ONLINE_PLAYER_DELEGATE(MaxPlayers, DelegateName) \`
- L121 _macro_ `#define DEFINE_ONLINE_PLAYER_DELEGATE_ONE_PARAM(MaxPlayers, DelegateName, Param1Type) \`
- L131 _macro_ `#define DEFINE_ONLINE_PLAYER_DELEGATE_TWO_PARAM(MaxPlayers, DelegateName, Param1Type, Param2Type) \`
- L141 _macro_ `#define DEFINE_ONLINE_PLAYER_DELEGATE_THREE_PARAM(MaxPlayers, DelegateName, Param1Type, Param2Type, Param3Type) \`
- L151 _macro_ `#define DEFINE_ONLINE_PLAYER_DELEGATE_FOUR_PARAM(MaxPlayers, DelegateName, Param1Type, Param2Type, Param3Type, Param4Type) \`
- L161 _macro_ `#define DEFINE_ONLINE_PLAYER_DELEGATE_FIVE_PARAM(MaxPlayers, DelegateName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type) \`
- L171 _macro_ `#define DEFINE_ONLINE_PLAYER_DELEGATE_SIX_PARAM(MaxPlayers, DelegateName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type) \`
- L181 _macro_ `#define DEFINE_ONLINE_PLAYER_DELEGATE_SEVEN_PARAM(MaxPlayers, DelegateName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type) \`

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineDelegates.h` (Public)


#### class `FOnlineSubsystemDelegates`  
`class FOnlineSubsystemDelegates`  
_L13-33_
- desc: Online subsystem delegates that are more external to the online subsystems themselves This is NOT to replace the individual interfaces that have the Add/Clear/Trigger syntax
- L23 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlineSubsystemCreated, class IOnlineSubsystem* );` — Notification that a new online subsystem instance has been created @param NewSubsystem the new instance created
- L24 _public member_ `static FOnOnlineSubsystemCreated OnOnlineSubsystemCreated;`
- L31 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDefaultOnlineSubsystemPreReloaded, class IOnlineSubsystem* );` — Notification that the default subsystem instance is going to be deleted and reinstantiated @param SubsystemToBeReloaded the instance to be destroyed
- L32 _public member_ `static FOnDefaultOnlineSubsystemPreReloaded OnDefaultOnlineSubsystemPreReloaded;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ONLINESUBSYSTEM_API`
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlineSubsystemCreated, class IOnlineSubsystem* );` — Notification that a new online subsystem instance has been created @param NewSubsystem the new instance created
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDefaultOnlineSubsystemPreReloaded, class IOnlineSubsystem* );` — Notification that the default subsystem instance is going to be deleted and reinstantiated @param SubsystemToBeReloaded the instance to be destroyed

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineError.h` (Public)


#### enum `EOnlineErrorResult`  
`enum class EOnlineErrorResult : uint8`  
_L18-64_
- desc: Common error results
- L21 _public enumerator_ `Success` — Successful result. no further error processing needed
- L24 _public enumerator_ `NoConnection` — Failed due to no connection
- L26 _public enumerator_ `RequestFailure`
- L28 _public enumerator_ `InvalidCreds`
- L30 _public enumerator_ `InvalidUser` — Failed due to invalid or missing user
- L32 _public enumerator_ `InvalidAuth` — Failed due to invalid or missing auth for user
- L34 _public enumerator_ `AccessDenied` — Failed due to invalid access
- L36 _public enumerator_ `TooManyRequests` — Throttled due to too many requests
- L38 _public enumerator_ `AlreadyPending` — Async request was already pending
- L40 _public enumerator_ `InvalidParams` — Invalid parameters specified for request
- L42 _public enumerator_ `CantParse` — Data could not be parsed for processing
- L44 _public enumerator_ `InvalidResults` — Invalid results returned from the request. Parsed but unexpected results
- L46 _public enumerator_ `IncompatibleVersion` — Incompatible client for backend version
- L48 _public enumerator_ `NotConfigured` — Not configured correctly for use
- L50 _public enumerator_ `NotImplemented` — Feature not available on this implementation
- L52 _public enumerator_ `MissingInterface` — Interface is missing
- L54 _public enumerator_ `Canceled` — Operation was canceled (likely by user)
- L56 _public enumerator_ `FailExtended` — Extended error. More info can be found in the results or by looking at the ErrorCode
- L58 _public enumerator_ `NoGameSession` — No game session found
- L60 _public enumerator_ `MismatchedUser` — Failed due to mismatched or missing user between title and store
- L63 _public enumerator_ `Unknown` — Default state

#### struct `FOnlineError`  
`struct FOnlineError`  
_L69-196_
- desc: Generic Error response for OSS calls
- L76 _private prototype_ `explicit FOnlineError(EOnlineErrorResult InResult, const FString& InErrorCode, const FText& InErrorMessage);`
- L81 _public prototype_ `explicit FOnlineError(const TCHAR* const ErrorCode);`
- L82 _public prototype_ `explicit FOnlineError(const int32 ErrorCode);`
- L83 _public prototype_ `void SetFromErrorCode(const int32 ErrorCode);`
- L84 _public prototype_ `void SetFromErrorMessage(const FText& ErrorMessage, const int32 ErrorCode);`
- L87 _public prototype_ `explicit FOnlineError(EOnlineErrorResult InResult = EOnlineErrorResult::Unknown);`
- L90 _public prototype_ `static FOnlineError CreateError(const FString& ErrorNamespace, EOnlineErrorResult Result, const FString& ErrorCode, const FText& ErrorMessage = FText::GetEmpty());` — Create factory for proper namespacing. Use ONLINE_ERROR macro
- L93 _public prototype_ `static FOnlineError CreateError(const FString& ErrorNamespace, EOnlineErrorResult Result);` — Use a default error code / display text
- L96 _public prototype_ `static const FOnlineError& Success();` — helpers for the most common error types
- L98 _public prototype_ `explicit FOnlineError(bool bSucceeded);`
- L99 _public prototype_ `explicit FOnlineError(const FString& ErrorCode);`
- L100 _public prototype_ `explicit FOnlineError(FString&& ErrorCode);`
- L101 _public prototype_ `explicit FOnlineError(const FText& ErrorMessage);`
- L104 _public prototype_ `void SetFromErrorCode(const FString& ErrorCode);` — Same as the Ctors but can be called any time (does NOT set bSucceeded to false)
- L105 _public prototype_ `void SetFromErrorCode(FString&& ErrorCode);`
- L106 _public prototype_ `void SetFromErrorMessage(const FText& ErrorMessage);`
- L109 _public function_ `inline EOnlineErrorResult GetErrorResult() const` — Accessors
- L110 _public function_ `inline const FText& GetErrorMessage() const`
- L111 _public function_ `inline const FString& GetErrorRaw() const`
- L112 _public function_ `inline const FString& GetErrorCode() const`
- L113 _public function_ `inline bool WasSuccessful() const`
- L116 _public function_ `inline FOnlineError& SetErrorRaw(const FString& Val)` — Setters for adding the raw error
- L119 _public prototype_ `static const FString GetGenericErrorCode();` — Code useful when all you have is raw error info from old APIs
- L122 _public prototype_ `FString GetErrorLegacy();` — prints out everything, need something like this!!!
- L124 _public prototype_ `FString ToLogString() const;` — Call this if you want to log this out (will pick the best string representation)
- L126 _public function_ `bool operator==(const FOnlineError& Other) const`
- L131 _public function_ `bool operator!=(const FOnlineError& Other) const`
- L136 _public function_ `FOnlineError operator+ (const FOnlineError& RHS) const`
- L143 _public function_ `FOnlineError operator+ (const FString& RHS) const`
- L150 _public function_ `FOnlineError& operator+= (const FOnlineError& RHS)`
- L157 _public function_ `FOnlineError& operator+= (const FString& RHS)`
- L165 _public member_ `bool bSucceeded;` — Did the request succeed fully. If this is true the rest of the struct probably doesn't matter
- L168 _public member_ `FString ErrorRaw;` — The raw unparsed error message from server. Used for pass-through error processing by other systems.
- L171 _public member_ `FString ErrorCode;` — Intended to be interpreted by code.
- L174 _public member_ `FText ErrorMessage;` — Suitable for display to end user. Guaranteed to be in the current locale (or empty)
- L178 _protected prototype_ `static FString DefaultErrorCode(EOnlineErrorResult Result);`
- L180 _protected prototype_ `static FText DefaultErrorMsg(EOnlineErrorResult Result);` — Default messaging for common errors
- L182 _protected prototype_ `static const FString& GetDefaultErrorNamespace();` — Default namespace for online errors
- L185 _protected function_ `inline FOnlineError& SetResult(EOnlineErrorResult Val)` — Setters for updating individual values directly
- L186 _protected function_ `inline FOnlineError& SetErrorCode(const FString& Val)`
- L187 _protected function_ `inline FOnlineError& SetErrorMessage(const FText& Val)`
- L190 _protected prototype_ `void SetFromErrorCode(EOnlineErrorResult InResult);` — Helpers for constructing errors
- L191 _protected prototype_ `void SetFromErrorCode(EOnlineErrorResult InResult, const FString& InErrorCode);`
- L192 _protected prototype_ `void SetFromErrorCode(EOnlineErrorResult InResult, const FString& InErrorCode, const FText& InErrorText);`
- L195 _protected member_ `EOnlineErrorResult Result;` — If successful result then the rest of the struct probably doesn't matter

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ONLINESUBSYSTEM_API`
- L9 _macro_ `#define ONLINE_ERROR_LEGACY 1`
- L11 _namespace_ `namespace EOnlineServerConnectionStatus`
- L66 _macro_ `#define ONLINE_ERROR_CONTEXT_SEPARATOR TEXT(":")`
- L200 _macro_ `#define ONLINE_ERROR(...) FOnlineError::CreateError(TEXT(ONLINE_ERROR_NAMESPACE), __VA_ARGS__)`

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineErrorMacros.inl` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Errors`
- L17 _function_ `inline const TCHAR* BaseNamespace()` (scope `Errors`) — Configured namspace
- L20 _function_ `inline FOnlineError NotConfigured()` (scope `Errors`) — Configuration
- L23 _function_ `inline FOnlineError InvalidUser()` (scope `Errors`) — Input validation
- L24 _function_ `inline FOnlineError InvalidParams()` (scope `Errors`)
- L27 _function_ `inline FOnlineError MissingInterface()` (scope `Errors`) — System failures
- L28 _function_ `inline FOnlineError MissingSubsystem()` (scope `Errors`)
- L31 _function_ `inline FOnlineError RequestFailure()` (scope `Errors`) — Failures
- L34 _function_ `inline FOnlineError ParseError()` (scope `Errors`) — Response failures
- L35 _function_ `inline FOnlineError ResultsError()` (scope `Errors`)
- L36 _function_ `inline FOnlineError AccessDenied()` (scope `Errors`)

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineFriendErrors.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define LOCTEXT_NAMESPACE "OnlineFriend"`
- L8 _macro_ `#define ONLINE_ERROR_NAMESPACE "errors.com.epicgames.oss.friend"`
- L10 _namespace_ `namespace OnlineFriend`
- L14 _namespace_ `namespace Errors` (scope `OnlineFriend`)
- L16 _function_ `inline FOnlineError InvalidResult()` (scope `OnlineFriend::Errors`)

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineIdentityErrors.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define LOCTEXT_NAMESPACE "OnlineIdentity"`
- L8 _macro_ `#define ONLINE_ERROR_NAMESPACE "errors.com.epicgames.oss.identity"`
- L10 _namespace_ `namespace OnlineIdentity`
- L14 _namespace_ `namespace Errors` (scope `OnlineIdentity`)
- L16 _function_ `inline FOnlineError InvalidCreds()` (scope `OnlineIdentity::Errors`)
- L17 _function_ `inline FOnlineError InvalidAuth()` (scope `OnlineIdentity::Errors`)
- L19 _function_ `inline FOnlineError UserNotFound()` (scope `OnlineIdentity::Errors`)
- L21 _function_ `inline FOnlineError LoginPending()` (scope `OnlineIdentity::Errors`)
- L23 _function_ `inline FOnlineError InvalidResult()` (scope `OnlineIdentity::Errors`)
- L25 _function_ `inline FOnlineError PinGrantFailure()` (scope `OnlineIdentity::Errors`)
- L26 _function_ `inline FOnlineError PinGrantTimeout()` (scope `OnlineIdentity::Errors`)
- L28 _function_ `inline FOnlineError Canceled()` (scope `OnlineIdentity::Errors`)
- L37 _macro_ `#define UE_ONLINE_ERROR_PARAM_IDENTITY_AUTH_LOGIN TEXT("auth_login")`
- L38 _macro_ `#define UE_ONLINE_ERROR_PARAM_IDENTITY_AUTH_TYPE TEXT("auth_type")`
- L39 _macro_ `#define UE_ONLINE_ERROR_PARAM_IDENTITY_AUTH_PASSWORD TEXT("auth_password")`
- L41 _macro_ `#define UE_ONLINE_ERROR_PARAM_IDENTITY_NO_USER_ID TEXT("no_user_id")`
- L42 _macro_ `#define UE_ONLINE_ERROR_PARAM_IDENTITY_NO_AUTH_TOKEN TEXT("no_auth_token")`
- L43 _macro_ `#define UE_ONLINE_ERROR_PARAM_IDENTITY_NO_AUTH_TYPE TEXT("no_auth_type")`

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineJsonSerializer.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define BEGIN_ONLINE_JSON_SERIALIZER BEGIN_JSON_SERIALIZER`
- L13 _macro_ `#define END_ONLINE_JSON_SERIALIZER END_JSON_SERIALIZER`
- L14 _macro_ `#define ONLINE_JSON_SERIALIZE(JsonName, JsonValue) JSON_SERIALIZE(JsonName, JsonValue)`
- L15 _macro_ `#define ONLINE_JSON_SERIALIZE_OPTIONAL(JsonName, OptionalJsonValue) JSON_SERIALIZE_OPTIONAL(JsonName, OptionalJsonValue)`
- L16 _macro_ `#define ONLINE_JSON_SERIALIZE_ARRAY(JsonName, JsonArray) JSON_SERIALIZE_ARRAY(JsonName, JsonArray)`
- L17 _macro_ `#define ONLINE_JSON_SERIALIZE_MAP(JsonName, JsonMap) JSON_SERIALIZE_MAP(JsonName, JsonMap)`
- L18 _macro_ `#define ONLINE_JSON_SERIALIZE_SIMPLE_COPY(JsonMap) JSON_SERIALIZE_SIMPLECOPY(JsonMap)`
- L19 _macro_ `#define ONLINE_JSON_SERIALIZE_SERIALIZABLE(JsonName, JsonValue) UE_DEPRECATED_MACRO(5.6, "ONLINE_JSON_SERIALIZE_SERIALIZABLE has been deprecated, use JSON_SERIALIZE_MEMBERS_OF instead") JSON_SERIALIZE_MEMBERS_OF(JsonValue)`
- L20 _macro_ `#define ONLINE_JSON_SERIALIZE_RAW_JSON_STRING(JsonName, JsonValue) JSON_SERIALIZE_RAW_JSON_STRING(JsonName, JsonValue)`
- L21 _macro_ `#define ONLINE_JSON_SERIALIZE_ARRAY_SERIALIZABLE(JsonName, JsonArray, ElementType) JSON_SERIALIZE_ARRAY_SERIALIZABLE(JsonName, JsonArray, ElementType)`
- L22 _macro_ `#define ONLINE_JSON_SERIALIZE_OPTIONAL_ARRAY_SERIALIZABLE(JsonName, OptionalJsonArray, ElementType) JSON_SERIALIZE_OPTIONAL_ARRAY_SERIALIZABLE(JsonName, OptionalJsonArray, ElementType)`
- L23 _macro_ `#define ONLINE_JSON_SERIALIZE_MAP_SERIALIZABLE(JsonName, JsonMap, ElementType) JSON_SERIALIZE_MAP_SERIALIZABLE(JsonName, JsonMap, ElementType)`
- L24 _macro_ `#define ONLINE_JSON_SERIALIZE_MAP_ARRAY_SERIALIZABLE(JsonName, JsonMap, ElementType) JSON_SERIALIZE_MAP_ARRAY_SERIALIZABLE(JsonName, JsonMap, ElementType)`
- L25 _macro_ `#define ONLINE_JSON_SERIALIZE_OBJECT_SERIALIZABLE(JsonName, JsonSerializableObject) JSON_SERIALIZE_OBJECT_SERIALIZABLE(JsonName, JsonSerializableObject)`
- L26 _macro_ `#define ONLINE_JSON_SERIALIZE_DATETIME_UNIX_TIMESTAMP(JsonName, JsonDateTime) JSON_SERIALIZE_DATETIME_UNIX_TIMESTAMP(JsonName, JsonDateTime)`
- L27 _macro_ `#define ONLINE_JSON_SERIALIZE_ENUM(JsonName, JsonEnum) JSON_SERIALIZE_ENUM(JsonName, JsonEnum)`
- L28 _macro_ `#define ONLINE_JSON_SERIALIZE_DATETIME_UNIX_TIMESTAMP_MILLISECONDS(JsonName, JsonDateTime) JSON_SERIALIZE_DATETIME_UNIX_TIMESTAMP_MILLISECONDS(JsonName, JsonDateTime)`
- L30 _typedef_ `typedef FJsonSerializable FOnlineJsonSerializable;`
- L31 _typedef_ `typedef FJsonSerializerWriter<> FOnlineJsonSerializerWriter;`
- L33 _typedef_ `typedef TMap<FString, FVariantData> FJsonSerializeableKeyValueMapVariant;`

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineKeyValuePair.h` (Public)


#### enum `EOnlineKeyValuePairDataType::Type`  
`enum Type : uint8`  
_L13-38_
- L16 _public enumerator_ `Empty` — Means the data in the OnlineData value fields should be ignored
- L18 _public enumerator_ `Int32` — 32 bit integer
- L20 _public enumerator_ `UInt32` — 32 bit unsigned integer
- L22 _public enumerator_ `Int64` — 64 bit integer
- L24 _public enumerator_ `UInt64` — 64 bit unsigned integer
- L26 _public enumerator_ `Double` — Double (8 byte)
- L28 _public enumerator_ `String` — Unicode string
- L30 _public enumerator_ `Float` — Float (4 byte)
- L32 _public enumerator_ `Blob` — Binary data
- L34 _public enumerator_ `Bool` — bool data (1 byte)
- L36 _public enumerator_ `Json` — Serialized json text
- L37 _public enumerator_ `MAX`

#### class `FOnlineKeyValuePairs`  
`template<class KeyType, class ValueType> class FOnlineKeyValuePairs : public TMap<KeyType,ValueType>`  
_L130-142_
- inherits: `TMap<KeyType,ValueType>`
- desc: Associative container for key value pairs
- L132 _private typedef_ `typedef TMap<KeyType, ValueType> Super;`
- L136 _public function_ `inline FOnlineKeyValuePairs()`
- L137 _public function_ `inline FOnlineKeyValuePairs(FOnlineKeyValuePairs&& Other) : Super(MoveTemp(Other))`
- L138 _public function_ `inline FOnlineKeyValuePairs(const FOnlineKeyValuePairs& Other) : Super(Other)`
- L139 _public function_ `inline FOnlineKeyValuePairs& operator=(FOnlineKeyValuePairs&& Other)`
- L140 _public function_ `inline FOnlineKeyValuePairs& operator=(const FOnlineKeyValuePairs& Other)`

#### class `FVariantData`  
`class FVariantData`  
_L147-543_
- desc: Container for storing data of variable type
- L153 _private member_ `EOnlineKeyValuePairDataType::Type Type;` — Current data type
- L172 _private member_ `} Value;`
- L175 _private member_ `mutable int CachedEstimatedMaxEscapedStringSize = 0;` — Cached estimated maximum size of the value when encoded as an escaped string.
- L180 _public function_ `FVariantData() : Type(EOnlineKeyValuePairDataType::Empty)` — Constructor
- L187 _public function_ `template<typename ValueType> FVariantData(const ValueType& InData) : Type(EOnlineKeyValuePairDataType::Empty)` — Constructor starting with an initialized value/type
- L198 _public prototype_ `FVariantData(const FVariantData& Other);` — Copy constructor. Copies the other into this object @param Other the other structure to copy
- L205 _public prototype_ `FVariantData(FVariantData&& Other);` — Move constructor. Moves the other into this object @param Other the other structure to move
- L212 _public prototype_ `FVariantData& operator=(const FVariantData& Other);` — Assignment operator. Copies the other into this object @param Other the other structure to copy
- L219 _public prototype_ `FVariantData& operator=(FVariantData&& Other);` — Move Assignment operator. Moves the other into this object @param Other the other structure to move
- L224 _public function_ `~FVariantData()` — Cleans up the data to prevent leaks
- L232 _public prototype_ `void Empty();` — Cleans up the existing data and sets the type to ODT_Empty
- L237 _public function_ `const EOnlineKeyValuePairDataType::Type GetType() const` — Get the key for this key value pair
- L247 _public prototype_ `void SetValue(const FString& InData);` — Copies the data and sets the type @param InData the new data to assign
- L254 _public prototype_ `void SetValue(const TCHAR* InData);` — Copies the data and sets the type @param InData the new data to assign
- L261 _public prototype_ `void SetValue(int32 InData);` — Copies the data and sets the type @param InData the new data to assign
- L268 _public prototype_ `void SetValue(uint32 InData);` — Copies the data and sets the type @param InData the new data to assign
- L275 _public prototype_ `void SetValue(bool InData);` — Copies the data and sets the type @param InData the new data to assign
- L282 _public prototype_ `void SetValue(double InData);` — Copies the data and sets the type @param InData the new data to assign
- L289 _public prototype_ `void SetValue(float InData);` — Copies the data and sets the type @param InData the new data to assign
- L296 _public prototype_ `void SetValue(const TArray<uint8>& InData);` — Copies the data and sets the type @param InData the new data to assign
- L304 _public prototype_ `void SetValue(uint32 Size, const uint8* InData);` — Copies the data and sets the type @param Size the length of the buffer to copy @param InData the new data to assign
- L311 _public prototype_ `void SetValue(int64 InData);` — Copies the data and sets the type @param InData the new data to assign
- L318 _public prototype_ `void SetValue(uint64 InData);` — Copies the data and sets the type @param InData the new data to assign
- L325 _public prototype_ `void SetValue(const TSharedRef<class FJsonObject>& InData);` — Copies the data and sets the type @param InData the new data to assign
- L332 _public prototype_ `void SetJsonValueFromString(const FString& InData);` — Copies the data and sets the type @param InData the new data to assign
- L339 _public prototype_ `void GetValue(FString& OutData) const;` — Copies the data after verifying the type @param OutData out value that receives the copied data
- L346 _public prototype_ `void GetValue(int32& OutData) const;` — Copies the data after verifying the type @param OutData out value that receives the copied data
- L353 _public prototype_ `void GetValue(uint32& OutData) const;` — Copies the data after verifying the type @param OutData out value that receives the copied data
- L360 _public prototype_ `void GetValue(bool& OutData) const;` — Copies the data after verifying the type @param OutData out value that receives the copied data
- L367 _public prototype_ `void GetValue(int64& OutData) const;` — Copies the data after verifying the type @param OutData out value that receives the copied data
- L374 _public prototype_ `void GetValue(uint64& OutData) const;` — Copies the data after verifying the type @param OutData out value that receives the copied data
- L381 _public prototype_ `void GetValue(float& OutData) const;` — Copies the data after verifying the type @param OutData out value that receives the copied data
- L388 _public prototype_ `void GetValue(TArray<uint8>& OutData) const;` — Copies the data after verifying the type @param OutData out value that receives the copied data
- L397 _public prototype_ `void GetValue(uint32& OutSize,uint8** OutData) const;` — Copies the data after verifying the type. NOTE: Performs a deep copy so you are responsible for freeing the data @param OutSize out value that receives the size of the copied data @param OutData out value that receives the copied data
- L404 _public prototype_ `void GetValue(double& OutData) const;` — Copies the data after verifying the type @param OutData out value that receives the copied data
- L411 _public prototype_ `void GetValue(TSharedPtr<class FJsonObject>& OutData) const;` — Copies the data after verifying the type @param OutData out value that receives the copied data
- L418 _public prototype_ `void GetValue(TArray<TSharedPtr<class FJsonValue>>& OutData) const;` — Copies the data after verifying the type @param OutData out value that receives the copied data
- L421 _public prototype_ `int GetEstimatedMaxEscapedStringSize() const;` — Returns the estimated maximum size of the value when encoded as an escaped string.
- L426 _public function_ `bool IsNumeric() const` — Returns true if Type is numeric
- L439 _public function_ `template<typename TYPE, EOnlineKeyValuePairDataType::Type ENUM_TYPE> inline void Increment(TYPE IncBy)` — Increments the value by the specified amount @param IncBy the amount to increment by
- L451 _public prototype_ `void Increment();` — Increments the numeric value by 1
- L459 _public function_ `template<typename TYPE, EOnlineKeyValuePairDataType::Type ENUM_TYPE> inline void Decrement(TYPE DecBy)` — Decrements the value by the specified amount @param DecBy the amount to decrement by
- L471 _public prototype_ `void Decrement();` — Decrements the numeric value by 1
- L476 _public prototype_ `FString ToString() const;` — Converts the data into a string representation
- L485 _public prototype_ `bool FromString(const FString& NewValue);` — Converts the string to the specified type of data for this setting @param NewValue the string value to convert @return true if it was converted, false otherwise
- L488 _public function_ `const TCHAR* GetTypeString() const` — @return The type as a string
- L498 _public prototype_ `TSharedRef<class FJsonObject> ToJson() const;` — Convert variant data to json object with "type,value" fields @return json object representation
- L506 _public prototype_ `bool FromJson(const TSharedRef<class FJsonObject>& JsonObject);` — Convert json object to variant data from "type,value" fields @param JsonObject json to convert from @return true if conversion was successful
- L513 _public prototype_ `FString GetTypeSuffix() const;` — Combine the type suffix given this variant's type @return the the type suffix
- L522 _public prototype_ `void AddToJsonObject(const TSharedRef<FJsonObject>& JsonObject, const FString& Name, const bool bWithTypeSuffix = true) const;` — Insert variant data into json object @param JsonObject json object to insert data into @param Name field name for value @param bWithTypeSuffix True if you would like the type suffix appended to the name
- L532 _public prototype_ `bool FromJsonValue(FStringView Name, const TSharedRef<class FJsonValue>& JsonValue, FString& OutName);` — Convert json object to variant data from Name_ @param Name name of json field that includes the type suffix @param JsonValue json value to convert from @param OutName returns the name with the type suffix stripped @return true if conversion was successful
- L541 _public prototype_ `bool operator==(const FVariantData& Other) const;` — Comparison of two settings data classes @param Other the other settings data to compare against @return true if they are equal, false otherwise
- L542 _public prototype_ `bool operator!=(const FVariantData& Other) const;`

#### union `FVariantData::ValueUnion`  
`union ValueUnion`  
_L155-172_
- desc: Union of all possible types that can be stored
- L157 _public member_ `bool AsBool;`
- L158 _public member_ `int32 AsInt;`
- L159 _public member_ `uint32 AsUInt;`
- L160 _public member_ `float AsFloat;`
- L161 _public member_ `int64 AsInt64;`
- L162 _public member_ `uint64 AsUInt64;`
- L163 _public member_ `double AsDouble;`
- L164 _public member_ `TCHAR* AsTCHAR;`
- L169 _public member_ `} AsBlob;`
- L171 _public function_ `ValueUnion()`

#### struct `FVariantData::ValueUnion::(anonymous)`  
``  
_L166-169_

#### class `FVariantDataConverter`  
`class FVariantDataConverter`  
_L549-647_
- desc: Helper class for converting from UStruct to FVariantData and back only very basic flat UStructs with POD types are supported
- L563 _public prototype_ `static bool UStructToVariantMap(const UStruct* StructDefinition, const void* Struct, FOnlineKeyValuePairs<FString, FVariantData>& OutVariantMap, int64 CheckFlags, int64 SkipFlags);` — Convert a UStruct into a variant mapping table @param StructDefinition layout of the UStruct @param Struct actual UStruct data @param OutVariantMap container for outgoing data @param CheckFlags property must have this flag to be serialized @param SkipFlags property cannot have this flag to be serialized @return true if it was successful, false otherwise
- L576 _public prototype_ `static bool FPropertyToVariantData(FProperty* Property, const void* Value, int64 CheckFlags, int64 SkipFlags, FVariantData& OutVariantData);` — Convert a single FProperty to an FVariantData @param Property definition of the property @param Value actual property data @param CheckFlags property must have this flag to be serialized @param SkipFlags property cannot have this flag to be serialized @param OutVariantData container for outgoing data @return true if it was successful, false otherwise
- L591 _public prototype_ `static bool VariantMapToUStruct(const FOnlineKeyValuePairs<FString, FVariantData>& VariantMap, const UStruct* StructDefinition, void* OutStruct, int64 CheckFlags, int64 SkipFlags);` — Convert a map of FVariantData elements to a UStruct @param VariantMap Input variant data @param StructDefinition layout of the UStruct @param OutStruct output container for UStruct data @param CheckFlags property must have this flag to be serialized @param SkipFlags property cannot have this flag to be serialized @return true if it was successful, false otherwise
- L605 _public prototype_ `static bool ApplyVariantMapToUnchangedProperties(const FOnlineKeyValuePairs<FString, FVariantData>& VariantMap, const UStruct* StructDefinition, void* OutStruct, const void* CompareStruct, int64 CheckFlags, int64 SkipFlags);` — Apply FVariantData elements to properties of a UStruct that are identical with the previous value. @param VariantMap Input variant data @param StructDefinition layout of the UStruct @param OutStruct output container for UStruct data @param CompareStruct the struct to compare OutStruct to when deciding if a property should be updated. @param CheckFlags property must have this flag to be serialized @param SkipFlags property cannot have this flag to be serialized @return true if it was successful, false otherwise
- L618 _public prototype_ `static bool VariantDataToFProperty(const FVariantData* Variant, FProperty* Property, void* OutValue, int64 CheckFlags, int64 SkipFlags);` — Convert an FVariantData to a FProperty @param Variant Input variant data @param Property definition of the property @param OutValue outgoing property data container @param CheckFlags property must have this flag to be serialized @param SkipFlags property cannot have this flag to be serialized @return true if it was successful, false otherwise
- L633 _private prototype_ `static bool ConvertScalarFPropertyToVariant(FProperty* Property, const void* Value, FVariantData& OutVariantData, int64 CheckFlags, int64 SkipFlags);` — Convert a single FProperty to an FVariantData @param Property definition of the property @param Value actual property data @param OutVariantData container for outgoing data @param CheckFlags property must have this flag to be serialized @param SkipFlags property cannot have this flag to be serialized @return true if it was successful, false otherwise
- L646 _private prototype_ `static bool ConvertScalarVariantToFProperty(const FVariantData* Variant, FProperty* Property, void* OutValue, int64 CheckFlags, int64 SkipFlags);` — Convert an FVariantData to a FProperty @param Variant Input variant data @param Property definition of the property @param OutValue outgoing property data container @param CheckFlags property must have this flag to be serialized @param SkipFlags property cannot have this flag to be serialized @return true if it was successful, false otherwise

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API ONLINESUBSYSTEM_API`
- L11 _namespace_ `namespace EOnlineKeyValuePairDataType`
- L41 _function_ `inline const TCHAR* ToString(EOnlineKeyValuePairDataType::Type EnumVal)` (scope `EOnlineKeyValuePairDataType`) — @return the stringified version of the enum passed in
- L73 _function_ `inline EOnlineKeyValuePairDataType::Type FromString(const FString& EnumStr)` (scope `EOnlineKeyValuePairDataType`) — @return the correspondent enum for the stringified version passed in
- L167 _member_ `uint8* BlobData;` (scope `FVariantData::ValueUnion::__anon6dfe24590108`)
- L168 _member_ `uint32 BlobSize;` (scope `FVariantData::ValueUnion::__anon6dfe24590108`)

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineNotification.h` (Public)


#### struct `FOnlineNotification`  
`struct FOnlineNotification`  
_L15-102_
- desc: Notification object, used to send messages between systems
- L20 _public function_ `FOnlineNotification()` — Default constructor
- L28 _public prototype_ `FOnlineNotification( const FString& InTypeStr, const TSharedPtr<FJsonValue>& InPayload, FUniqueNetIdPtr InToUserId = nullptr, FUniqueNetIdPtr InFromUserId = nullptr, const FString & InClientRequestIdStr = TEXT("") );` — Constructor from type and FJsonValue System message unless ToUserId is specified; FromUserId optional
- L40 _public function_ `FOnlineNotification( const FString& InTypeStr, const TSharedPtr<FJsonObject>& InPayload, FUniqueNetIdPtr InToUserId = nullptr, FUniqueNetIdPtr InFromUserId = nullptr, const FString& InClientRequestIdStr = TEXT("") ) : TypeStr(InTypeStr) , Payload(InPayload) , ToUserId(InToUserId) , FromUserId(InFromUserId) , ClientRequestIdStr(InClientRequestIdStr)` — Constructor from type and FJsonObject System message unless ToUserId is specified; FromUserId optional
- L60 _public function_ `template <class FStruct> bool ParsePayload(FStruct& PayloadOut) const` — Parse a payload and assume there is a static const TypeStr member to use
- L68 _public prototype_ `bool ParsePayload(UStruct* StructType, void* StructPtr) const;` — Parse out Payload into the provided UStruct
- L73 _public function_ `explicit operator bool() const` — Does this notification have a valid payload?
- L81 _public prototype_ `void SetTypeFromPayload();` — Set up the type string for the case where the type is embedded in the payload
- L86 _public prototype_ `void SetClientRequestIdFromPayload();` — Set up the ClientRequestIdStr for the case where it is embedded in the payload
- L89 _public member_ `FString TypeStr;` — A string defining the type of this notification, used to determine how to parse the payload
- L92 _public member_ `TSharedPtr<FJsonObject> Payload;` — The payload of this notification
- L95 _public member_ `FUniqueNetIdPtr ToUserId;` — User to deliver the notification to.  Can be null for system notifications.
- L98 _public member_ `FUniqueNetIdPtr FromUserId;` — User who sent the notification, optional.
- L101 _public member_ `FString ClientRequestIdStr;` — String representing the client_request_id for this notification. Used to tie a server request back to the client. Can be empty.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ONLINESUBSYSTEM_API`

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineNotificationHandler.h` (Public)


#### enum `EOnlineNotificationResult`  
`enum class EOnlineNotificationResult`  
_L13-17_
- desc: Whether a handler function handled a particular notification
- L15 _public enumerator_ `None` — No handling occurred
- L16 _public enumerator_ `Handled` — Notification was handled

#### struct `FOnlineNotificationBinding`  
`struct FOnlineNotificationBinding`  
_L29-40_
- desc: Struct to keep track of bindings
- L32 _public member_ `FHandleOnlineNotificationSignature NotificationDelegate;` — Delegate to call when this binding is activated
- L34 _public function_ `FOnlineNotificationBinding()`
- L37 _public function_ `FOnlineNotificationBinding(const FHandleOnlineNotificationSignature& InNotificationDelegate) : NotificationDelegate(InNotificationDelegate)`

#### class `FOnlineNotificationHandler`  
`class FOnlineNotificationHandler`  
_L43-92_
- desc: This class is a static manager used to track notification transports and map the delivered notifications to subscribed notification handlers
- L48 _protected typedef_ `typedef TMap< FString, TArray<FOnlineNotificationBinding> > NotificationTypeBindingsMap;`
- L51 _protected member_ `NotificationTypeBindingsMap SystemBindingMap;` — Map from type of notification to the delegate to call
- L54 _protected member_ `TMap< FString, NotificationTypeBindingsMap > PlayerBindingMap;` — Map from player and type of notification to the delegate to call
- L59 _public function_ `FOnlineNotificationHandler()` — Lifecycle is managed by OnlineSubSystem, all access should be made through there
- L66 _public prototype_ `FDelegateHandle AddSystemNotificationBinding_Handle(FString NotificationType, const FOnlineNotificationBinding& NewBinding);` — Add a notification binding for a type
- L69 _public prototype_ `void RemoveSystemNotificationBinding(FString NotificationType, FDelegateHandle RemoveHandle);` — Remove the notification handler for a type
- L72 _public prototype_ `void ResetSystemNotificationBindings();` — Resets all system notification handlers
- L77 _public prototype_ `FDelegateHandle AddPlayerNotificationBinding_Handle(const FUniqueNetId& PlayerId, FString NotificationType, const FOnlineNotificationBinding& NewBinding);` — Add a notification binding for a type
- L80 _public prototype_ `void RemovePlayerNotificationBinding(const FUniqueNetId& PlayerId, FString NotificationType, FDelegateHandle RemoveHandle);` — Remove the player notification handler for a type
- L83 _public prototype_ `void ResetPlayerNotificationBindings(const FUniqueNetId& PlayerId);` — Resets a player's notification handlers
- L86 _public prototype_ `void ResetAllPlayerNotificationBindings();` — Resets all player notification handlers
- L91 _public prototype_ `void DeliverNotification(const FOnlineNotification& Notification);` — Deliver a notification to the appropriate handler for that player/msg type.  Called by NotificationTransport implementations.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ONLINESUBSYSTEM_API`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EOnlineNotificationResult, FHandleOnlineNotificationSignature, const FOnlineNotification&);` — Delegate type for handling a notification The first parameter is a notification structure Return result code to indicate if notification has been handled
- L25 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(EOnlineNotificationResult, FHandleOnlineNotificationSignature, const FOnlineNotification&);` — Delegate type for handling a notification The first parameter is a notification structure Return result code to indicate if notification has been handled
- L94 _typedef_ `typedef TSharedPtr<FOnlineNotificationHandler, ESPMode::ThreadSafe> FOnlineNotificationHandlerPtr;`
- L95 _typedef_ `typedef TSharedRef<FOnlineNotificationHandler, ESPMode::ThreadSafe> FOnlineNotificationHandlerRef;`
- L96 _typedef_ `typedef TWeakPtr<FOnlineNotificationHandler, ESPMode::ThreadSafe> FOnlineNotificationHandlerWeakPtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineNotificationTransportManager.h` (Public)


#### class `FOnlineNotificationTransportManager`  
`class FOnlineNotificationTransportManager`  
_L18-65_
- desc: This class is a static manager used to track notification transports and map the delivered notifications to subscribed notification handlers
- L24 _protected member_ `TMap< FNotificationTransportId, IOnlineNotificationTransportPtr > TransportMap;` — Map from a transport type to the transport object
- L29 _public function_ `FOnlineNotificationTransportManager()` — Lifecycle is managed by OnlineSubSystem, all access should be through there
- L33 _public prototype_ `virtual ~FOnlineNotificationTransportManager();`
- L36 _public prototype_ `bool SendNotification(FNotificationTransportId TransportType, const FOnlineNotification& Notification);` — Send a notification using a specific transport
- L39 _public prototype_ `bool ReceiveTransportMessage(FNotificationTransportId TransportType, const IOnlineNotificationTransportMessage& TransportMessage);` — Receive a message from a specific transport, convert to notification, and pass on for delivery
- L44 _public prototype_ `IOnlineNotificationTransportPtr GetNotificationTransport(FNotificationTransportId TransportType);` — Get a notification transport of a specific type
- L47 _public prototype_ `void AddNotificationTransport(IOnlineNotificationTransportPtr Transport);` — Add a notification transport
- L50 _public prototype_ `void RemoveNotificationTransport(FNotificationTransportId TransportType);` — Remove a notification transport
- L53 _public prototype_ `void ResetNotificationTransports();` — Resets all transports
- L56 _public function_ `virtual FOnlineTransportTapHandle OpenTap(const FUniqueNetId& User, const FOnlineTransportTap& Tap)` — Base function for letting the notifications flow
- L62 _public function_ `virtual void CloseTap(FOnlineTransportTapHandle TapHandle)` — Base function for stanching the notifications

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ONLINESUBSYSTEM_API`
- L12 _typedef_ `typedef TSharedPtr<class IOnlineNotificationTransport, ESPMode::ThreadSafe> IOnlineNotificationTransportPtr;` — forward declare
- L67 _typedef_ `typedef TSharedPtr<FOnlineNotificationTransportManager, ESPMode::ThreadSafe> FOnlineNotificationTransportManagerPtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlinePresenceErrors.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define LOCTEXT_NAMESPACE "OnlinePresence"`
- L7 _macro_ `#define ONLINE_ERROR_NAMESPACE "errors.com.epicgames.oss.presence"`
- L9 _namespace_ `namespace OnlinePresence`
- L13 _namespace_ `namespace Errors` (scope `OnlinePresence`)
- L15 _function_ `inline FOnlineError InvalidResult()` (scope `OnlinePresence::Errors`)

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlinePurchaseErrors.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define LOCTEXT_NAMESPACE "OnlinePurchase"`
- L7 _macro_ `#define ONLINE_ERROR_NAMESPACE "errors.com.epicgames.oss.purchase"`
- L9 _namespace_ `namespace OnlinePurchase`
- L13 _namespace_ `namespace Errors` (scope `OnlinePurchase`)
- L15 _function_ `inline FOnlineError InvalidResult()` (scope `OnlinePurchase::Errors`)

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineSessionSettings.h` (Public)


#### struct `FOnlineSessionSetting`  
`struct FOnlineSessionSetting`  
_L18-88_
- desc: One setting describing an online session contains a key, value and how this setting is advertised to others, if at all
- L22 _public member_ `FVariantData Data;` — Settings value
- L24 _public member_ `EOnlineDataAdvertisementType::Type AdvertisementType;` — How is this session setting advertised with the backend or searches
- L26 _public member_ `int32 ID;` — Optional ID used in some platforms as the index instead of the session name
- L30 _public function_ `FOnlineSessionSetting() : AdvertisementType(EOnlineDataAdvertisementType::DontAdvertise) , ID(INVALID_SESSION_SETTING_ID)` — Default constructor, used when serializing a network packet
- L38 _public function_ `template<typename Type> FOnlineSessionSetting(Type&& InData) : Data(Forward<Type>(InData)) , AdvertisementType(EOnlineDataAdvertisementType::DontAdvertise) , ID(INVALID_SESSION_SETTING_ID)` — Constructor for settings created/defined on the host for a session
- L47 _public function_ `template<typename Type> FOnlineSessionSetting(Type&& InData, EOnlineDataAdvertisementType::Type InAdvertisementType) : Data(Forward<Type>(InData)) , AdvertisementType(InAdvertisementType) , ID(INVALID_SESSION_SETTING_ID)` — Constructor for settings created/defined on the host for a session
- L56 _public function_ `template<typename Type> FOnlineSessionSetting(Type&& InData, EOnlineDataAdvertisementType::Type InAdvertisementType, int32 InID) : Data(Forward<Type>(InData)) , AdvertisementType(InAdvertisementType) , ID(InID)` — Constructor for settings created/defined on the host for a session
- L66 _public function_ `bool operator==(const FOnlineSessionSetting& Other) const` — Comparison operator
- L72 _public function_ `bool operator!=(const FOnlineSessionSetting& Other) const`
- L77 _public function_ `FString ToString() const`

#### class `FOnlineSessionSearchParam`  
`class FOnlineSessionSearchParam`  
_L97-157_
- desc: One search parameter in an online session query contains a value and how this setting is compared
- L101 _private prototype_ `FOnlineSessionSearchParam() = delete;` — Hidden on purpose
- L105 _public member_ `FVariantData Data;` — Search value
- L107 _public member_ `EOnlineComparisonOp::Type ComparisonOp;` — How is this session setting compared on the backend searches
- L109 _public member_ `int32 ID;` — Optional ID used on some platform to index the session setting
- L114 _public function_ `template<typename Type> FOnlineSessionSearchParam(Type&& InData) : Data(Forward<Type>(InData)) , ComparisonOp(EOnlineComparisonOp::Equals) , ID(INVALID_SESSION_SETTING_ID)` — Constructor for setting search parameters in a query
- L123 _public function_ `template<typename Type> FOnlineSessionSearchParam(Type&& InData, EOnlineComparisonOp::Type InComparisonOp) : Data(Forward<Type>(InData)) , ComparisonOp(InComparisonOp) , ID(INVALID_SESSION_SETTING_ID)` — Constructor for setting search parameters in a query
- L132 _public function_ `template<typename Type> FOnlineSessionSearchParam(Type&& InData, EOnlineComparisonOp::Type InComparisonOp, int32 InID) : Data(Forward<Type>(InData)) , ComparisonOp(InComparisonOp) , ID(InID)` — Constructor for setting search parameters in a query
- L142 _public function_ `bool operator==(const FOnlineSessionSearchParam& Other) const` — Comparison operator
- L148 _public function_ `bool operator!=(const FOnlineSessionSearchParam& Other) const`
- L153 _public function_ `FString ToString() const`

#### class `FOnlineSearchSettings`  
`class FOnlineSearchSettings`  
_L165-221_
- desc: Container for all parameters describing a single session search
- L169 _public member_ `FSearchParams SearchParams;` — Array of custom search settings
- L172 _public prototype_ `FOnlineSearchSettings() = default;`
- L174 _public prototype_ `FOnlineSearchSettings(FOnlineSearchSettings&&) = default;`
- L175 _public prototype_ `FOnlineSearchSettings(const FOnlineSearchSettings&) = default;`
- L176 _public prototype_ `FOnlineSearchSettings& operator=(FOnlineSearchSettings&&) = default;`
- L177 _public prototype_ `FOnlineSearchSettings& operator=(const FOnlineSearchSettings&) = default;`
- L179 _public prototype_ `virtual ~FOnlineSearchSettings() = default;`
- L190 _public prototype_ `template<typename ValueType> void Set(FName Key, const ValueType& Value, EOnlineComparisonOp::Type InType, int32 ID);` — Sets a key value pair combination that defines a search parameter @param Key key for the setting @param Value value of the setting @param InType type of comparison @param ID ID of comparison
- L200 _public prototype_ `template<typename ValueType> void Set(FName Key, const ValueType& Value, EOnlineComparisonOp::Type InType);` — Sets a key value pair combination that defines a search parameter @param Key key for the setting @param Value value of the setting @param InType type of comparison
- L211 _public prototype_ `template<typename ValueType> bool Get(FName Key, ValueType& Value) const;` — Gets a key value pair combination that defines a search parameter @param Key key for the setting @param Value value of the setting @return true if found, false otherwise
- L220 _public prototype_ `EOnlineComparisonOp::Type GetComparisonOp(FName Key) const;` — Retrieve a search parameter comparison op @param Key key of the setting @return the comparison op for the setting

#### class `FOnlineSessionSettings`  
`class FOnlineSessionSettings`  
_L226-368_
- desc: Container for all settings describing a single online session
- L230 _public member_ `int32 NumPublicConnections;` — The number of publicly available connections advertised
- L232 _public member_ `int32 NumPrivateConnections;` — The number of connections that are private (invite/password) only
- L234 _public member_ `bool bShouldAdvertise;` — Whether this match is publicly advertised on the online service
- L236 _public member_ `bool bAllowJoinInProgress;` — Whether joining in progress is allowed or not
- L238 _public member_ `bool bIsLANMatch;` — This game will be lan only and not be visible to external players
- L240 _public member_ `bool bIsDedicated;` — Whether the server is dedicated or player hosted
- L242 _public member_ `bool bUsesStats;` — Whether the match should gather stats or not
- L244 _public member_ `bool bAllowInvites;` — Whether the match allows invitations for this session or not
- L246 _public member_ `bool bUsesPresence;` — Whether to display user presence information or not
- L248 _public member_ `bool bAllowJoinViaPresence;` — Whether joining via player presence is allowed or not
- L250 _public member_ `bool bAllowJoinViaPresenceFriendsOnly;` — Whether joining via player presence is allowed for friends only or not
- L252 _public member_ `bool bAntiCheatProtected;` — Whether the server employs anti-cheat (punkbuster, vac, etc)
- L254 _public member_ `bool bUseLobbiesIfAvailable;` — Whether to prefer lobbies APIs if the platform supports them
- L256 _public member_ `bool bUseLobbiesVoiceChatIfAvailable;` — Whether to create (and auto join) a voice chat room for the lobby, if the platform supports it
- L258 _public member_ `FString SessionIdOverride;` — Manual override for the Session Id instead of having one assigned by the backend. Its size may be restricted depending on the platform
- L261 _public member_ `int32 BuildUniqueId;` — Used to keep different builds from seeing each other during searches
- L263 _public member_ `FSessionSettings Settings;` — Array of custom session settings
- L266 _public member_ `TUniqueNetIdMap<FSessionSettings> MemberSettings;` — Map of custom settings per session member (Not currently used by every OSS)
- L270 _public function_ `FOnlineSessionSettings() : NumPublicConnections(0) , NumPrivateConnections(0) , bShouldAdvertise(false) , bAllowJoinInProgress(false) , bIsLANMatch(false) , bIsDedicated(false) , bUsesStats(false) , bAllowInvites(false) , bUsesPresence(false) , bAllowJoinViaPresence(false) , bAllowJoinViaPresenceFriendsOnly(false) , bAntiCheatProtected(false) , bUseLobbiesIfAvailable(false) , bUseLobbiesVoiceChatIfAvailable(false) , BuildUniqueId(GetBuildUniqueId())` — Default constructor, used when serializing a network packet
- L293 _public prototype_ `virtual ~FOnlineSessionSettings() = default;`
- L295 _public prototype_ `FOnlineSessionSettings(FOnlineSessionSettings&&) = default;`
- L296 _public prototype_ `FOnlineSessionSettings(const FOnlineSessionSettings&) = default;`
- L297 _public prototype_ `FOnlineSessionSettings& operator=(FOnlineSessionSettings&&) = default;`
- L298 _public prototype_ `FOnlineSessionSettings& operator=(const FOnlineSessionSettings&) = default;`
- L309 _public prototype_ `template<typename ValueType> void Set(FName Key, const ValueType& Value, EOnlineDataAdvertisementType::Type InType, int32 InID);` — Sets a key value pair combination that defines a session setting with an ID @param Key key for the setting @param Value value of the setting @param InType type of online advertisement @param ID ID for this session setting
- L319 _public prototype_ `template<typename ValueType> void Set(FName Key, const ValueType& Value, EOnlineDataAdvertisementType::Type InType);` — Sets a key value pair combination that defines a session setting @param Key key for the setting @param Value value of the setting @param InType type of online advertisement
- L328 _public prototype_ `void Set(FName Key, const FOnlineSessionSetting& SrcSetting);` — Sets a key value pair combination that defines a session setting from an existing session setting @param Key key for the setting @param SrcSetting setting values
- L339 _public prototype_ `template<typename ValueType> bool Get(FName Key, ValueType& Value) const;` — Gets a key value pair combination that defines a session setting @param Key key for the setting @param Value value of the setting @return true if found, false otherwise
- L348 _public prototype_ `bool Remove(FName Key);` — Removes a key value pair combination @param Key key to remove @return true if found and removed, false otherwise
- L357 _public prototype_ `EOnlineDataAdvertisementType::Type GetAdvertisementType(FName Key) const;` — Retrieve a session setting's advertisement type @param Key key of the setting @return the advertisement type for the setting
- L366 _public prototype_ `int32 GetID(FName Key) const;` — Retrieve a session setting's ID @param Key key of the setting @return the ID for the setting

#### class `FOnlineSession`  
`class FOnlineSession`  
_L371-424_
- desc: Basic session information serializable into a NamedSession or SearchResults
- L375 _public member_ `FUniqueNetIdPtr OwningUserId;` — Owner of the session
- L377 _public member_ `FString OwningUserName;` — Owner name of the session
- L379 _public member_ `FOnlineSessionSettings SessionSettings;` — The settings associated with this session
- L381 _public member_ `TSharedPtr<class FOnlineSessionInfo> SessionInfo;` — The platform specific session information
- L383 _public member_ `int32 NumOpenPrivateConnections;` — The number of private connections that are available (read only)
- L385 _public member_ `int32 NumOpenPublicConnections;` — The number of publicly available connections that are available (read only)
- L389 _public function_ `FOnlineSession() : OwningUserId(nullptr), SessionInfo(nullptr), NumOpenPrivateConnections(0), NumOpenPublicConnections(0)` — Default constructor, used when serializing a network packet
- L398 _public function_ `FOnlineSession(const FOnlineSessionSettings& InSessionSettings) : OwningUserId(nullptr), SessionSettings(InSessionSettings), SessionInfo(nullptr), NumOpenPrivateConnections(0), NumOpenPublicConnections(0)` — Constructor
- L407 _public prototype_ `FOnlineSession(FOnlineSession&&) = default;`
- L408 _public prototype_ `FOnlineSession(const FOnlineSession&) = default;`
- L409 _public prototype_ `FOnlineSession& operator=(FOnlineSession&&) = default;`
- L410 _public prototype_ `FOnlineSession& operator=(const FOnlineSession&) = default;`
- L412 _public prototype_ `virtual ~FOnlineSession() = default;`
- L415 _public function_ `FString GetSessionIdStr() const` — @return the session id for the session as a string

#### class `FNamedOnlineSession`  
`class FNamedOnlineSession : public FOnlineSession`  
_L427-521_
- inherits: `FOnlineSession`
- desc: Holds the per session information for named sessions
- L430 _protected function_ `FNamedOnlineSession() : SessionName(NAME_None), HostingPlayerNum(INDEX_NONE), SessionState(EOnlineSessionState::NoSession)`
- L439 _public member_ `const FName SessionName;` — The name of the session
- L441 _public member_ `int32 HostingPlayerNum;` — Index of the player who created the session [host] or joined it [client]
- L443 _public member_ `bool bHosting;` — Whether or not the local player is hosting this session
- L446 _public member_ `FUniqueNetIdPtr LocalOwnerId;` — NetId of the local player that created this named session.  Could be the host, or a player joining a session. Will entirely replace HostingPlayerNum
- L449 _public member_ `TArray< FUniqueNetIdRef > RegisteredPlayers;` — List of players registered in the session
- L451 _public member_ `EOnlineSessionState::Type SessionState;` — State of the session (game thread write only)
- L454 _public function_ `FNamedOnlineSession(FName InSessionName, const FOnlineSessionSettings& InSessionSettings) : FOnlineSession(InSessionSettings) , SessionName(InSessionName) , HostingPlayerNum(INDEX_NONE) , bHosting(false) , SessionState(EOnlineSessionState::NoSession)` — Constructor used to create a named session directly
- L464 _public function_ `FNamedOnlineSession(FName InSessionName, const FOnlineSession& Session) : FOnlineSession(Session) , SessionName(InSessionName) , HostingPlayerNum(INDEX_NONE) , bHosting(false) , SessionState(EOnlineSessionState::NoSession)` — Constructor used to create a named session directly
- L473 _public prototype_ `virtual ~FNamedOnlineSession() = default;`
- L475 _public prototype_ `FNamedOnlineSession(const FNamedOnlineSession& Other) = default;`
- L476 _public prototype_ `FNamedOnlineSession(FNamedOnlineSession&& Other) = default;`
- L479 _public prototype_ `FNamedOnlineSession& operator=(const FNamedOnlineSession& Other) = delete;` — We delete the equals operator as SessionName is immutable
- L480 _public prototype_ `FNamedOnlineSession& operator=(FNamedOnlineSession&& Other) = delete;`
- L493 _public function_ `bool GetJoinability(bool& bPublicJoinable, bool& bFriendJoinable, bool& bInviteOnly, bool& bAllowInvites) const` — Calculate the possible joinability state of this session check the values from left to right in order of precedence @param bPublicJoinable [out] is the game joinable by anyone at all @param bFriendJoinable [out] is the game joinable by friends via presence (doesn't require invite) @param bInviteOnly [out] is the game joinable via explicit invites @param bAllowInvites [out] are invites possible (use with bInviteOnly to determine if invites are available right now) @return true if the out params are valid, false otherwise

#### class `FOnlineSessionSearchResult`  
`class FOnlineSessionSearchResult`  
_L530-565_
- desc: Representation of a single search result from a FindSession() call
- L534 _public member_ `FOnlineSession Session;` — All advertised session information
- L536 _public member_ `int32 PingInMs;` — Ping to the search result, MAX_QUERY_PING is unreachable
- L538 _public function_ `FOnlineSessionSearchResult() : PingInMs(MAX_QUERY_PING)`
- L546 _public function_ `bool IsValid() const` — @return true if the search result is valid, false otherwise
- L555 _public function_ `bool IsSessionInfoValid() const` — Check if the session info is valid, for cases where we don't need the OwningUserId @return true if the session info is valid, false otherwise
- L561 _public function_ `FString GetSessionIdStr() const` — @return the session id for a given session search result

#### class `FOnlineSessionSearch`  
`class FOnlineSessionSearch`  
_L573-634_
- desc: Encapsulation of a search for sessions request. Contains all the search parameters and any search results returned after the OnFindSessionsCompleteDelegate has triggered Check the SearchState for Done/Failed state before using the data
- L577 _public member_ `TArray<FOnlineSessionSearchResult> SearchResults;` — Array of all sessions found when searching for the given criteria
- L579 _public member_ `EOnlineAsyncTaskState::Type SearchState;` — State of the search
- L581 _public member_ `int32 MaxSearchResults;` — Max number of queries returned by the matchmaking service
- L583 _public member_ `FOnlineSearchSettings QuerySettings;` — The query to use for finding matching servers
- L585 _public member_ `bool bIsLanQuery;` — Whether the query is intended for LAN matches or not
- L590 _public member_ `int32 PingBucketSize;` — Used to sort games into buckets since a the difference in terms of feel for ping in the same bucket is often not a useful comparison and skill is better
- L592 _public member_ `int32 PlatformHash;` — Search hash used by the online subsystem to disambiguate search queries, stamped every time FindSession is called
- L594 _public member_ `float TimeoutInSeconds;` — Amount of time to wait for the search results. May not apply to all platforms.
- L598 _public function_ `FOnlineSessionSearch() : SearchState(EOnlineAsyncTaskState::NotStarted) , MaxSearchResults(1) , bIsLanQuery(false) , PingBucketSize(0) , PlatformHash(0) , TimeoutInSeconds(0.0f)` — Constructor
- L613 _public prototype_ `virtual ~FOnlineSessionSearch() = default;`
- L615 _public prototype_ `FOnlineSessionSearch(FOnlineSessionSearch&&) = default;`
- L616 _public prototype_ `FOnlineSessionSearch(const FOnlineSessionSearch&) = default;`
- L617 _public prototype_ `FOnlineSessionSearch& operator=(FOnlineSessionSearch&&) = default;`
- L618 _public prototype_ `FOnlineSessionSearch& operator=(const FOnlineSessionSearch&) = default;`
- L623 _public function_ `virtual void SortSearchResults()` — Give the game a chance to sort the returned results
- L630 _public function_ `virtual TSharedPtr<FOnlineSessionSettings> GetDefaultSessionSettings() const` — Get the default session settings for this search type Allows games to set reasonable defaults that aren't advertised but would be setup for each instantiated search result

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEM_API`
- L12 _macro_ `#define INVALID_SESSION_SETTING_ID -1`
- L91 _typedef_ `typedef FOnlineKeyValuePairs<FName, FOnlineSessionSetting> FSessionSettings;` — Type defining an array of session settings accessible by key
- L160 _typedef_ `typedef FOnlineKeyValuePairs<FName, FOnlineSessionSearchParam> FSearchParams;` — Type defining an array of search parameters accessible by key
- L523 _typedef_ `using FNamedOnlineSessionPtr = TSharedPtr<FNamedOnlineSession, ESPMode::ThreadSafe>;`
- L524 _typedef_ `using FNamedOnlineSessionRef = TSharedRef<FNamedOnlineSession, ESPMode::ThreadSafe>;`
- L527 _macro_ `#define MAX_QUERY_PING 9999` — Value returned on unreachable or otherwise bad search results
- L641 _prototype_ `void DumpNamedSession(const FNamedOnlineSession* NamedSession);` — Logs session properties used from the session settings @param NamedSession the session to log the information for
- L648 _prototype_ `void DumpSession(const FOnlineSession* Session);` — Logs session properties used from the session settings @param Session the session to log the information for
- L655 _prototype_ `void DumpSessionSettings(const FOnlineSessionSettings* SessionSettings);` — Logs session properties used from the session settings @param SessionSettings the session to log the information for

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineStats.h` (Public)


#### class `FStatsColumnArray`  
`class FStatsColumnArray : public FOnlineKeyValuePairs<FString, FVariantData>`  
_L13-23_
- inherits: `FOnlineKeyValuePairs<FString,FVariantData>`
- desc: Representation of a single column and its data
- L15 _private typedef_ `typedef FOnlineKeyValuePairs<FString, FVariantData> Super;`
- L18 _public function_ `inline FStatsColumnArray()`
- L19 _public function_ `inline FStatsColumnArray(FStatsColumnArray&& Other) : Super(MoveTemp(Other))`
- L20 _public function_ `inline FStatsColumnArray(const FStatsColumnArray& Other) : Super(Other)`
- L21 _public function_ `inline FStatsColumnArray& operator=(FStatsColumnArray&& Other)`
- L22 _public function_ `inline FStatsColumnArray& operator=(const FStatsColumnArray& Other)`

#### class `FStatPropertyArray`  
`class FStatPropertyArray : public FOnlineKeyValuePairs<FString, FVariantData>`  
_L29-39_
- inherits: `FOnlineKeyValuePairs<FString,FVariantData>`
- desc: Representation of a single stat value to post to the backend
- L31 _private typedef_ `typedef FOnlineKeyValuePairs<FString, FVariantData> Super;`
- L34 _public function_ `inline FStatPropertyArray()`
- L35 _public function_ `inline FStatPropertyArray(FStatPropertyArray&& Other) : Super(MoveTemp(Other))`
- L36 _public function_ `inline FStatPropertyArray(const FStatPropertyArray& Other) : Super(Other)`
- L37 _public function_ `inline FStatPropertyArray& operator=(FStatPropertyArray&& Other)`
- L38 _public function_ `inline FStatPropertyArray& operator=(const FStatPropertyArray& Other)`

#### class `FNameArrayDeprecationWrapper`  
`class FNameArrayDeprecationWrapper : public TArray<FString>`  
_L41-56_
- inherits: `TArray<FString>`
- L43 _private typedef_ `typedef TArray<FString> Super;`
- L46 _public function_ `inline FNameArrayDeprecationWrapper()`
- L47 _public function_ `inline FNameArrayDeprecationWrapper(FNameArrayDeprecationWrapper&& Other) : Super(MoveTemp(Other))`
- L48 _public function_ `inline FNameArrayDeprecationWrapper(const FNameArrayDeprecationWrapper& Other) : Super(Other)`
- L49 _public function_ `inline FNameArrayDeprecationWrapper& operator=(FNameArrayDeprecationWrapper&& Other)`
- L50 _public function_ `inline FNameArrayDeprecationWrapper& operator=(const FNameArrayDeprecationWrapper& Other)`
- L52 _public function_ `inline FNameArrayDeprecationWrapper(TArray<FString>&& Other) : Super(MoveTemp(Other))`
- L53 _public function_ `inline FNameArrayDeprecationWrapper(const TArray<FString>& Other) : Super(Other)`
- L54 _public function_ `inline FNameArrayDeprecationWrapper& operator=(TArray<FString>&& Other)`
- L55 _public function_ `inline FNameArrayDeprecationWrapper& operator=(const TArray<FString>& Other)`

#### class `FNameDeprecationWrapper`  
`class FNameDeprecationWrapper : public FString`  
_L58-73_
- inherits: `FString`
- L60 _private typedef_ `typedef FString Super;`
- L63 _public function_ `inline FNameDeprecationWrapper()`
- L64 _public function_ `inline FNameDeprecationWrapper(FNameDeprecationWrapper&& Other) : Super(MoveTemp(Other))`
- L65 _public function_ `inline FNameDeprecationWrapper(const FNameDeprecationWrapper& Other) : Super(Other)`
- L66 _public function_ `inline FNameDeprecationWrapper& operator=(FNameDeprecationWrapper&& Other)`
- L67 _public function_ `inline FNameDeprecationWrapper& operator=(const FNameDeprecationWrapper& Other)`
- L69 _public function_ `inline FNameDeprecationWrapper(FString&& Other) : Super(MoveTemp(Other))`
- L70 _public function_ `inline FNameDeprecationWrapper(const FString& Other) : Super(Other)`
- L71 _public function_ `inline FNameDeprecationWrapper& operator=(FString&& Other)`
- L72 _public function_ `inline FNameDeprecationWrapper& operator=(const FString& Other)`

#### class `FOnlineStats`  
`class FOnlineStats`  
_L78-150_
- desc: An interface used to collect and manage online stats
- L83 _public member_ `FStatPropertyArray Properties;` — Array of stats we are gathering
- L90 _public prototype_ `class FVariantData* FindStatByName(const FString& StatName);` — Get a key value pair by key name @param StatName key name to search for @return KeyValuePair if found, NULL otherwise
- L99 _public prototype_ `virtual void SetFloatStat(const FString& StatName, float Value);` — Sets a stat of type SDT_Float to the value specified. Does nothing if the stat is not of the right type. @param StatName the stat to change the value of @param Value the new value to assign to the stat
- L108 _public prototype_ `virtual void SetIntStat(const FString& StatName, int32 Value);` — Sets a stat of type SDT_Int to the value specified. Does nothing if the stat is not of the right type. @param StatName the stat to change the value of @param Value the new value to assign to the stat
- L117 _public prototype_ `virtual void IncrementFloatStat(const FString& StatName, float IncBy = 1.0f);` — Increments a stat of type float by the value specified. Does nothing if the stat is not of the right type. @param StatName the stat to increment @param IncBy the value to increment by
- L126 _public prototype_ `virtual void IncrementIntStat(const FString& StatName, int32 IncBy = 1);` — Increments a stat of type int32 by the value specified. Does nothing if the stat is not of the right type. @param StatName the stat to increment @param IncBy the value to increment by
- L135 _public prototype_ `virtual void DecrementFloatStat(const FString& StatName, float DecBy = 1.0f);` — Decrements a stat of type float by the value specified. Does nothing if the stat is not of the right type. @param StatName the stat to decrement @param DecBy the value to decrement by
- L144 _public prototype_ `virtual void DecrementIntStat(const FString& StatName, int32 DecBy = 1);` — Decrements a stat of type int32 by the value specified. Does nothing if the stat is not of the right type. @param StatName the stat to decrement @param DecBy the value to decrement by
- L149 _public prototype_ `virtual ~FOnlineStats() = default;` — Destructor

#### class `FOnlineLeaderboardWrite`  
`class FOnlineLeaderboardWrite : public FOnlineStats`  
_L155-178_
- inherits: `FOnlineStats`
- desc: Interface for storing/writing data to a leaderboard
- L160 _public member_ `ELeaderboardSort::Type SortMethod;` — Sort Method
- L162 _public member_ `ELeaderboardFormat::Type DisplayFormat;` — Display Type
- L164 _public member_ `ELeaderboardUpdateMethod::Type UpdateMethod;` — Update Method
- L167 _public member_ `FNameArrayDeprecationWrapper LeaderboardNames;` — Names of the leaderboards to write to
- L170 _public member_ `FNameDeprecationWrapper RatedStat;` — Name of the stat that the leaderboard is rated by
- L172 _public function_ `FOnlineLeaderboardWrite() : SortMethod(ELeaderboardSort::None), DisplayFormat(ELeaderboardFormat::Number), UpdateMethod(ELeaderboardUpdateMethod::KeepBest)`

#### struct `FOnlineStatsRow`  
`struct FOnlineStatsRow`  
_L183-206_
- desc: Representation of a single row in a retrieved leaderboard
- L187 _private function_ `FOnlineStatsRow() : NickName()` — Hidden on purpose
- L191 _public member_ `const FString NickName;` — Name of player in this row
- L193 _public member_ `const FUniqueNetIdPtr PlayerId;` — Unique Id for the player in this row
- L195 _public member_ `int32 Rank;` — Player's rank in this leaderboard
- L197 _public member_ `FStatsColumnArray Columns;` — All requested data on the leaderboard for this player
- L199 _public function_ `FOnlineStatsRow(const FString& InNickname, const FUniqueNetIdRef& InPlayerId) : NickName(InNickname), PlayerId(InPlayerId)`
- L205 _public prototype_ `FString ToLogString() const;`

#### struct `FColumnMetaData`  
`struct FColumnMetaData`  
_L211-230_
- desc: Representation of a single column of data in a leaderboard
- L214 _private function_ `FColumnMetaData() : DataType(EOnlineKeyValuePairDataType::Empty)`
- L221 _public member_ `const FNameDeprecationWrapper ColumnName;` — Name of the column to retrieve
- L223 _public member_ `const EOnlineKeyValuePairDataType::Type DataType;` — Type of data this column represents
- L225 _public function_ `FColumnMetaData(const FString& InColumnName, EOnlineKeyValuePairDataType::Type InDataType) : ColumnName(InColumnName), DataType(InDataType)`

#### class `FOnlineLeaderboardRead`  
`class FOnlineLeaderboardRead`  
_L235-274_
- desc: Interface for reading data from a leaderboard service
- L239 _public member_ `FNameDeprecationWrapper LeaderboardName;` — Name of the leaderboard read
- L241 _public member_ `FNameDeprecationWrapper SortedColumn;` — Column this leaderboard is sorted by
- L243 _public member_ `TArray<FColumnMetaData> ColumnMetadata;` — Column metadata for this leaderboard
- L245 _public member_ `TArray<FOnlineStatsRow> Rows;` — Array of ranked users retrieved (not necessarily sorted yet)
- L247 _public member_ `EOnlineAsyncTaskState::Type ReadState;` — Indicates an error reading data occurred while processing
- L249 _public function_ `FOnlineLeaderboardRead() : ReadState(EOnlineAsyncTaskState::NotStarted)`
- L260 _public function_ `FOnlineStatsRow* FindPlayerRecord(const FUniqueNetId& UserId)` — Retrieve a single record from the leaderboard for a given user @param UserId user id to retrieve a record for @return the requested user row or NULL if not found
- L273 _public prototype_ `FString ToLogString() const;`

#### class `FOnlinePlayerScore`  
`class FOnlinePlayerScore`  
_L280-283_
- desc: TODO ONLINE

#### class `FOnlineAchievementsWrite`  
`class FOnlineAchievementsWrite : public FOnlineStats`  
_L288-302_
- inherits: `FOnlineStats`
- desc: The interface for writing achievement stats to the server.
- L294 _public function_ `FOnlineAchievementsWrite() : WriteState(EOnlineAsyncTaskState::NotStarted)` — Constructor
- L301 _public member_ `EOnlineAsyncTaskState::Type WriteState;` — Indicates an error reading data occurred while processing

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEM_API`
- L276 _typedef_ `typedef TSharedRef<FOnlineLeaderboardRead, ESPMode::ThreadSafe> FOnlineLeaderboardReadRef;`
- L277 _typedef_ `typedef TSharedPtr<FOnlineLeaderboardRead, ESPMode::ThreadSafe> FOnlineLeaderboardReadPtr;`
- L304 _typedef_ `typedef TSharedRef<FOnlineAchievementsWrite, ESPMode::ThreadSafe> FOnlineAchievementsWriteRef;`
- L305 _typedef_ `typedef TSharedPtr<FOnlineAchievementsWrite, ESPMode::ThreadSafe> FOnlineAchievementsWritePtr;`

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h` (Public)


#### class `IOnlineSubsystem`  
`class IOnlineSubsystem`  
_L150-640_
- desc: OnlineSubsystem - Series of interfaces to support communicating with various web/platform layer services
- L154 _protected function_ `IOnlineSubsystem()` — Hidden on purpose
- L156 _protected member_ `FOnlineNotificationHandlerPtr OnlineNotificationHandler;`
- L157 _protected member_ `FOnlineNotificationTransportManagerPtr OnlineNotificationTransportManager;`
- L161 _public prototype_ `virtual ~IOnlineSubsystem() = default;`
- L168 _public function_ `static IOnlineSubsystem* Get(const FName& SubsystemName = NAME_None)` — Get the online subsystem for a given service @param SubsystemName - Name of the requested online service @return pointer to the appropriate online subsystem
- L182 _public function_ `static IOnlineSubsystem* GetByPlatform(bool bAutoLoad=true)` — Get the online subsystem native to the current hardware @param bAutoLoad - load the module if not already loaded @return pointer to the appropriate online subsystem
- L201 _public function_ `static IOnlineSubsystem* GetByConfig(const FString& ConfigString, bool bAutoLoad = true)` — Get the online subsystem associated with the given config string @param ConfigString - Key to query for @param bAutoLoad - load the module if not already loaded @return pointer to the appropriate online subsystem
- L216 _public function_ `static void Destroy(FName SubsystemName)` — Destroy a single online subsystem instance @param SubsystemName - Name of the online service to destroy
- L230 _public function_ `static void ReloadDefaultSubsystem()` — Unload the current default subsystem and attempt to reload the configured default subsystem May be different if the fallback subsystem was created an startup **NOTE** This is intended for editor use only, attempting to use this at the wrong time can result in unexpected crashes/behavior
- L242 _public function_ `FORCENOINLINE static bool DoesInstanceExist(const FName& SubsystemName = NAME_None)` — Determine if an instance of the subsystem already exists @param SubsystemName - Name of the requested online service @return true if instance exists, false otherwise
- L257 _public function_ `static bool IsLoaded(const FName& SubsystemName = NAME_None)` — Determine if the subsystem for a given interface is already loaded @param SubsystemName - Name of the requested online service @return true if module for the subsystem is loaded
- L272 _public prototype_ `static bool IsEnabled(const FName& SubsystemName, const FName& InstanceName = NAME_None);` — Determine if the subsystem for a given interface is enabled by config and command line @param SubsystemName - Name of the requested online service @return true if the subsystem is enabled by config
- L279 _public prototype_ `virtual FName GetSubsystemName() const = 0;` — Return the name of the subsystem @see OnlineSubsystemNames.h @return the name of the subsystem, as used in calls to IOnlineSubsystem::Get()
- L288 _public prototype_ `virtual FName GetInstanceName() const = 0;` — Get the instance name, which is typically "default" or "none" but distinguishes one instance from another in "Play In Editor" mode.  Most platforms can't do this because of third party requirements that only allow one login per machine instance @return the instance name of this subsystem
- L295 _public prototype_ `static FString GetLocalPlatformName();` — Get the local online platform based on compile time determination of hardware. @see OnlineSubsystemNames.h OSS_PLATFORM_NAME_* @return string representation of online platform name
- L298 _public prototype_ `virtual bool IsEnabled() const = 0;` — @return true if the subsystem is enabled, false otherwise
- L304 _public prototype_ `virtual IOnlineSessionPtr GetSessionInterface() const = 0;` — Get the interface for accessing the session management services @return Interface pointer for the appropriate session service
- L310 _public prototype_ `virtual IOnlineFriendsPtr GetFriendsInterface() const = 0;` — Get the interface for accessing the player friends services @return Interface pointer for the appropriate friend service
- L318 _public prototype_ `virtual IMessageSanitizerPtr GetMessageSanitizer(int32 LocalUserNum, FString& OutAuthTypeToExclude) const = 0;` — Get the interface for accessing the message sanitizer service @param LocalUserNum the controller number of the associated user @param OutAuthTypeToExclude platform to exclude in sanitization requests @return Interface pointer for the appropriate sanitizer service
- L324 _public prototype_ `virtual IOnlineGroupsPtr GetGroupsInterface() const = 0;` — Get the interface for accessing the groups services @return Interface pointer for appropriate groups service
- L330 _public prototype_ `virtual IOnlinePartyPtr GetPartyInterface() const = 0;` — Get the interface for accessing the player party services @return Interface pointer for the appropriate party service
- L336 _public prototype_ `virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const = 0;` — Get the interface for sharing user files in the cloud @return Interface pointer for the appropriate cloud service
- L342 _public prototype_ `virtual IOnlineUserCloudPtr GetUserCloudInterface() const = 0;` — Get the interface for accessing user files in the cloud @return Interface pointer for the appropriate cloud service
- L348 _public prototype_ `virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const = 0;` — Get the interface for accessing user entitlements @return Interface pointer for the appropriate entitlements service
- L354 _public prototype_ `virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const = 0;` — Get the interface for accessing leaderboards/rankings of a service @return Interface pointer for the appropriate leaderboard service
- L360 _public prototype_ `virtual IOnlineVoicePtr GetVoiceInterface() const = 0;` — Get the interface for accessing voice related data @return Interface pointer for the appropriate voice service
- L366 _public prototype_ `virtual IOnlineExternalUIPtr GetExternalUIInterface() const = 0;` — Get the interface for accessing the external UIs of a service @return Interface pointer for the appropriate external UI service
- L372 _public prototype_ `virtual IOnlineTimePtr GetTimeInterface() const = 0;` — Get the interface for accessing the server time from an online service @return Interface pointer for the appropriate server time service
- L378 _public prototype_ `virtual IOnlineIdentityPtr GetIdentityInterface() const = 0;` — Get the interface for accessing identity online services @return Interface pointer for the appropriate identity service
- L384 _public prototype_ `virtual IOnlineTitleFilePtr GetTitleFileInterface() const = 0;` — Get the interface for accessing title file online services @return Interface pointer for the appropriate title file service
- L390 _public prototype_ `virtual IOnlineStoreV2Ptr GetStoreV2Interface() const = 0;` — Get the interface for accessing an online store @return Interface pointer for the appropriate online store service
- L396 _public prototype_ `virtual IOnlinePurchasePtr GetPurchaseInterface() const = 0;` — Get the interface for purchasing @return Interface pointer for the appropriate purchase service
- L402 _public prototype_ `virtual IOnlineEventsPtr GetEventsInterface() const = 0;` — Get the interface for accessing online achievements @return Interface pointer for the appropriate online achievements service
- L408 _public prototype_ `virtual IOnlineAchievementsPtr GetAchievementsInterface() const = 0;` — Get the interface for accessing online achievements @return Interface pointer for the appropriate online achievements service
- L414 _public prototype_ `virtual IOnlineSharingPtr GetSharingInterface() const = 0;` — Get the interface for accessing online sharing @return Interface pointer for the appropriate online sharing service
- L420 _public prototype_ `virtual IOnlineUserPtr GetUserInterface() const = 0;` — Get the interface for accessing online user information @return Interface pointer for the appropriate online user service
- L426 _public prototype_ `virtual IOnlineMessagePtr GetMessageInterface() const = 0;` — Get the interface for accessing online messages @return Interface pointer for the appropriate online message service
- L432 _public prototype_ `virtual IOnlinePresencePtr GetPresenceInterface() const = 0;` — Get the interface for managing rich presence information @return Interface pointer for the appropriate online presence service
- L438 _public prototype_ `virtual IOnlineChatPtr GetChatInterface() const = 0;` — Get the interface for user-user and user-room chat functionality @return Interface pointer for the appropriate online chat service
- L444 _public prototype_ `virtual IOnlineStatsPtr GetStatsInterface() const = 0;` — Get the interface for accessing online stats @return Interface pointer for the appropriate online stat service
- L450 _public prototype_ `virtual IOnlineGameActivityPtr GetGameActivityInterface() const = 0;` — Get interface for accessing the game activity @return Interface pointer for the game activity interface
- L456 _public prototype_ `virtual IOnlineGameItemStatsPtr GetGameItemStatsInterface() const = 0;` — Get interface for accessing the game item stats @return Interface pointer for the game item stats interface
- L462 _public prototype_ `virtual IOnlineGameMatchesPtr GetGameMatchesInterface() const = 0;` — Get interface for accessing game matches @return Interface pointer for the game matches interface
- L468 _public prototype_ `virtual IOnlineContentAgeRestrictionPtr GetOnlineContentAgeRestrictionInterface() const = 0;` — Get interface for accessing the online content age restriction @return Interface pointer for online content age restriction
- L474 _public function_ `FOnlineNotificationHandlerPtr GetOnlineNotificationHandler() const` — Get the notification handler instance for this subsystem @return Pointer for the appropriate notification handler
- L483 _public prototype_ `virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const = 0;` — Get the interface for managing turn based multiplayer games @return Interface pointer for the appropriate online turn-based service
- L489 _public prototype_ `virtual IOnlineTournamentPtr GetTournamentInterface() const = 0;` — Get the interface for managing tournament information @return Interface pointer for the appropriate online tournament service
- L495 _public function_ `FOnlineNotificationTransportManagerPtr GetOnlineNotificationTransportManager() const` — Get the transport manager instance for this subsystem @return Pointer for the appropriate transport manager
- L505 _public prototype_ `virtual class UObject* GetNamedInterface(FName InterfaceName) = 0;` — Get custom UObject data preserved by the online subsystem @param InterfaceName key to the custom data
- L513 _public prototype_ `virtual void SetNamedInterface(FName InterfaceName, class UObject* NewInterface) = 0;` — Set a custom UObject to be preserved by the online subsystem @param InterfaceName key to the custom data @param NewInterface object to preserve
- L522 _public prototype_ `virtual bool IsDedicated() const = 0;` — Is the online subsystem associated with the game/editor/engine running as dedicated. May be forced into this mode by EditorPIE, but basically asks if the OSS is serving in a dedicated capacity @return true if the online subsystem is in dedicated server mode, false otherwise
- L530 _public prototype_ `virtual bool IsServer() const = 0;` — Is this instance of the game running as a server (dedicated OR listen) checks the Engine if possible for netmode status @return true if this is the server, false otherwise
- L537 _public prototype_ `virtual void SetForceDedicated(bool bForce) = 0;` — Force the online subsystem to behave as if it's associated with running a dedicated server @param bForce force dedicated mode if true
- L546 _public prototype_ `virtual bool IsLocalPlayer(const FUniqueNetId& UniqueId) const = 0;` — Is a player local to this machine by unique id @param UniqueId UniqueId of the player @return true if unique id is local to this machine, false otherwise
- L552 _public prototype_ `virtual bool Init() = 0;` — Initialize the underlying subsystem APIs @return true if the subsystem was successfully initialized, false otherwise
- L557 _public prototype_ `virtual void PreUnload() = 0;` — Perform any shutdown actions prior to any other modules being unloaded/shutdown
- L563 _public prototype_ `virtual bool Shutdown() = 0;` — Shutdown the underlying subsystem APIs @return true if the subsystem shutdown successfully, false otherwise
- L570 _public prototype_ `virtual FString GetAppId() const = 0;` — Each online subsystem has a global id for the app @return the app id for this app
- L581 _public prototype_ `virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) = 0;` — Exec handler that allows the online subsystem to process exec commands @param InWorld world @param Cmd the exec command being executed @param Ar the archive to log results to @return true if the handler consumed the input, false to continue searching handlers
- L586 _public prototype_ `virtual void SetUsingMultiplayerFeatures(const FUniqueNetId& UniqueId, bool bUsingMP) = 0;` — Some platforms must know when the game is using Multiplayer features so they can do recurring authorization checks.
- L595 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnConnectionStatusChanged, const FString& , EOnlineServerConnectionStatus::Type , EOnlineServerConnectionStatus::Type );` — Called when the connection state as reported by the online platform changes @param ServiceName the name of the service that is reporting (platform dependent) @param LastConnectionState last state of the connection @param ConnectionState current state of the connection
- L600 _public prototype_ `virtual EOnlineEnvironment::Type GetOnlineEnvironment() const = 0;` — @return the current environment being used for the online platform
- L605 _public prototype_ `virtual FString GetOnlineEnvironmentName() const = 0;` — @return the current environment being used for the online platform as defined by the platform (not necessarily EOnlineEnvironment::ToString)
- L613 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnOnlineEnvironmentChanged, EOnlineEnvironment::Type , EOnlineEnvironment::Type );` — Delegate fired when the online environment changes @param LastEnvironment - old online environment @param Environment - current online environment
- L618 _public prototype_ `virtual FText GetOnlineServiceName() const = 0;` — @return The name of the online service this platform uses
- L623 _public prototype_ `virtual FText GetSocialPlatformName() const = 0;` — @return The name of the social platform for this subsystem
- L632 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnConfigChanged, const TSet<FString>& );` — Delegate fired when a configuration change was detected as a result of ReloadConfigs being called. Allows application code to inject custom configuration data before the new configuration is used. @param ConfigSections list of ini sections that need to be reloaded
- L639 _public prototype_ `virtual void ReloadConfigs(const TSet<FString>& ConfigSections) = 0;` — Reload the configuration if it is relevant for this OSS instance @param ConfigSections list of ini sections that need to be reloaded

#### class `IOnlineFactory`  
`class IOnlineFactory`  
_L649-663_
- desc: Interface for creating the actual online subsystem instance for a given platform all modules must implement this
- L653 _public function_ `IOnlineFactory()`
- L654 _public prototype_ `virtual ~IOnlineFactory() = default;`
- L662 _public prototype_ `virtual IOnlineSubsystemPtr CreateSubsystem(FName InstanceName) = 0;` — Create an instance of the platform subsystem @param InstanceName name of this single instance of the subsystem @return newly created and initialized online subsystem, NULL if failure

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ONLINESUBSYSTEM_API`
- L49 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnline, Log, All);`
- L50 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineGame, Log, All);`
- L53 _delegate_ `DECLARE_STATS_GROUP(TEXT("Online"), STATGROUP_Online, STATCAT_Adva` — Online subsystem stats
- L55 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("OnlineAsync"), STAT_Online_Async, STATGROUP_Online, ONLINESUBS` — Total async thread time
- L57 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("NumTasks"), STAT_Online_AsyncTasks, STATGROUP_Online, ONLINESUBSYST` — Number of async tasks in queue
- L59 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("SessionInt"), STAT_Session_Interface, STATGROUP_Online, ONLINESUBSY` — Total time to process session interface
- L61 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("VoiceInt"), STAT_Voice_Interface, STATGROUP_Online, ONLINESUBSYST` — Total time to process both local/remote voice
- L64 _macro_ `#define ONLINE_LOG_PREFIX TEXT("OSS: ")`
- L67 _macro_ `#define UE_LOG_ONLINE(Verbosity, Format, ...) \`
- L72 _macro_ `#define UE_CLOG_ONLINE(Conditional, Verbosity, Format, ...) \`
- L77 _macro_ `#define UE_LOG_ONLINE_ONCE(Verbosity, Format, ...) \`
- L85 _typedef_ `typedef TSharedPtr<class IOnlineSession, ESPMode::ThreadSafe> IOnlineSessionPtr;` — Forward declarations of all interface classes
- L86 _typedef_ `typedef TSharedPtr<class IOnlineFriends, ESPMode::ThreadSafe> IOnlineFriendsPtr;`
- L87 _typedef_ `typedef TSharedPtr<class IOnlinePartySystem, ESPMode::ThreadSafe> IOnlinePartyPtr;`
- L88 _typedef_ `typedef TSharedPtr<class IMessageSanitizer, ESPMode::ThreadSafe> IMessageSanitizerPtr;`
- L89 _typedef_ `typedef TSharedPtr<class IOnlineGroups, ESPMode::ThreadSafe> IOnlineGroupsPtr;`
- L90 _typedef_ `typedef TSharedPtr<class IOnlineSharedCloud, ESPMode::ThreadSafe> IOnlineSharedCloudPtr;`
- L91 _typedef_ `typedef TSharedPtr<class IOnlineUserCloud, ESPMode::ThreadSafe> IOnlineUserCloudPtr;`
- L92 _typedef_ `typedef TSharedPtr<class IOnlineEntitlements, ESPMode::ThreadSafe> IOnlineEntitlementsPtr;`
- L93 _typedef_ `typedef TSharedPtr<class IOnlineLeaderboards, ESPMode::ThreadSafe> IOnlineLeaderboardsPtr;`
- L94 _typedef_ `typedef TSharedPtr<class IOnlineVoice, ESPMode::ThreadSafe> IOnlineVoicePtr;`
- L95 _typedef_ `typedef TSharedPtr<class IOnlineExternalUI, ESPMode::ThreadSafe> IOnlineExternalUIPtr;`
- L96 _typedef_ `typedef TSharedPtr<class IOnlineTime, ESPMode::ThreadSafe> IOnlineTimePtr;`
- L97 _typedef_ `typedef TSharedPtr<class IOnlineIdentity, ESPMode::ThreadSafe> IOnlineIdentityPtr;`
- L98 _typedef_ `typedef TSharedPtr<class IOnlineTitleFile, ESPMode::ThreadSafe> IOnlineTitleFilePtr;`
- L99 _typedef_ `typedef TSharedPtr<class IOnlineStoreV2, ESPMode::ThreadSafe> IOnlineStoreV2Ptr;`
- L100 _typedef_ `typedef TSharedPtr<class IOnlinePurchase, ESPMode::ThreadSafe> IOnlinePurchasePtr;`
- L101 _typedef_ `typedef TSharedPtr<class IOnlineEvents, ESPMode::ThreadSafe> IOnlineEventsPtr;`
- L102 _typedef_ `typedef TSharedPtr<class IOnlineAchievements, ESPMode::ThreadSafe> IOnlineAchievementsPtr;`
- L103 _typedef_ `typedef TSharedPtr<class IOnlineSharing, ESPMode::ThreadSafe> IOnlineSharingPtr;`
- L104 _typedef_ `typedef TSharedPtr<class IOnlineUser, ESPMode::ThreadSafe> IOnlineUserPtr;`
- L105 _typedef_ `typedef TSharedPtr<class IOnlineMessage, ESPMode::ThreadSafe> IOnlineMessagePtr;`
- L106 _typedef_ `typedef TSharedPtr<class IOnlinePresence, ESPMode::ThreadSafe> IOnlinePresencePtr;`
- L107 _typedef_ `typedef TSharedPtr<class IOnlineChat, ESPMode::ThreadSafe> IOnlineChatPtr;`
- L108 _typedef_ `typedef TSharedPtr<class IOnlineTurnBased, ESPMode::ThreadSafe> IOnlineTurnBasedPtr;`
- L109 _typedef_ `typedef TSharedPtr<class IOnlineTournament, ESPMode::ThreadSafe> IOnlineTournamentPtr;`
- L110 _typedef_ `typedef TSharedPtr<class FOnlineNotificationHandler, ESPMode::ThreadSafe> FOnlineNotificationHandlerPtr;`
- L111 _typedef_ `typedef TSharedPtr<class FOnlineNotificationTransportManager, ESPMode::ThreadSafe> FOnlineNotificationTransportManagerPtr;`
- L112 _typedef_ `typedef TSharedPtr<class IOnlineStats, ESPMode::ThreadSafe> IOnlineStatsPtr;`
- L113 _typedef_ `typedef TSharedPtr<IOnlineGameActivity, ESPMode::ThreadSafe> IOnlineGameActivityPtr;`
- L114 _typedef_ `typedef TSharedPtr<IOnlineGameItemStats, ESPMode::ThreadSafe> IOnlineGameItemStatsPtr;`
- L115 _typedef_ `typedef TSharedPtr<IOnlineGameMatches, ESPMode::ThreadSafe> IOnlineGameMatchesPtr;`
- L116 _typedef_ `typedef TSharedPtr<IOnlineContentAgeRestriction, ESPMode::ThreadSafe> IOnlineContentAgeRestrictionPtr;`
- L125 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConnectionStatusChanged, const FString& , EOnlineServerConnectionStatus::Type , EOnlineServerConnectionStatus::Type );` — Called when the connection state as reported by the online platform changes @param ServiceName the name of the service that is reporting (platform dependent) @param LastConnectionState last state of the connection @param ConnectionState current state of the connection
- L125 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConnectionStatusChanged, const FString& , EOnlineServerConnectionStatus::Type , EOnlineServerConnectionStatus::Type );` — Called when the connection state as reported by the online platform changes @param ServiceName the name of the service that is reporting (platform dependent) @param LastConnectionState last state of the connection @param ConnectionState current state of the connection
- L126 _typedef_ `typedef FOnConnectionStatusChanged::FDelegate FOnConnectionStatusChangedDelegate;`
- L134 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOnlineEnvironmentChanged, EOnlineEnvironment::Type , EOnlineEnvironment::Type );` — Delegate fired when the PSN environment changes @param LastEnvironment - old online environment @param Environment - current online environment
- L134 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOnlineEnvironmentChanged, EOnlineEnvironment::Type , EOnlineEnvironment::Type );` — Delegate fired when the PSN environment changes @param LastEnvironment - old online environment @param Environment - current online environment
- L135 _typedef_ `typedef FOnOnlineEnvironmentChanged::FDelegate FOnOnlineEnvironmentChangedDelegate;`
- L144 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfigChanged, const TSet<FString>& );` — Delegate fired when a configuration change was detected as a result of ReloadConfigs being called. Allows application code to inject custom configuration data before the new configuration is used. @param ConfigSections list of ini sections that need to be reloaded
- L144 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfigChanged, const TSet<FString>& );` — Delegate fired when a configuration change was detected as a result of ReloadConfigs being called. Allows application code to inject custom configuration data before the new configuration is used. @param ConfigSections list of ini sections that need to be reloaded
- L145 _typedef_ `typedef FOnConfigChanged::FDelegate FOnConfigChangedDelegate;`
- L643 _typedef_ `typedef TSharedPtr<IOnlineSubsystem, ESPMode::ThreadSafe> IOnlineSubsystemPtr;` — Public references to the online subsystem pointer should use this
- L670 _prototype_ `int32 GetBuildUniqueId();` — Generates a unique number based off of the current engine package @return the unique number from the current engine package
- L681 _prototype_ `bool IsPlayerInSessionImpl(class IOnlineSession* SessionInt, FName SessionName, const FUniqueNetId& UniqueId);` — Common implementation for finding a player in a session @param SessionInt Session interface to use @param SessionName Session name to check for player @param UniqueId UniqueId of the player @return true if unique id found in session, false otherwise
- L690 _prototype_ `bool IsUniqueIdLocal(const FUniqueNetId& UniqueId);` — Is the unique id local to this instance @param UniqueId unique to query @return true if unique id is found and logged in locally, false otherwise
- L699 _prototype_ `int32 GetBeaconPortFromSessionSettings(const class FOnlineSessionSettings& SessionSettings);` — Retrieve the beacon port from the specified session settings @param SessionSettings the session settings that contains the BEACON_PORT setting @return the port if found, otherwise DEFAULT_BEACON_PORT
- L702 _prototype_ `FUniqueNetIdPtr GetFirstSignedInUser(IOnlineIdentityPtr IdentityInt);` — Temp solution for some hardcoded access to logged in user 0, please avoid using this

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystemFeatureFlags.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define ONLINE_SUBSYSTEM_FEATURE_RUNTIMECHECKS UE_EDITOR`
- L28 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnlineSubsystemFeatureCheck);`
- L28 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnlineSubsystemFeatureCheck);`
- L32 _macro_ `#define UE_REGISTER_ONLINE_SUBSYSTEM_FEATURE_RUNTIMECHECK(FeatureName, CheckFunction) \`
- L35 _macro_ `#define UE_UNREGISTER_ONLINE_SUBSYSTEM_FEATURE_RUNTIMECHECK(FeatureName) \`
- L38 _macro_ `#define UE_DECLARE_ONLINE_SUBSYSTEM_FEATURE(StorageClass, FeatureName) \`
- L44 _macro_ `#define UE_DEFINE_ONLINE_SUBSYSTEM_FEATURE(FeatureName) \`
- L61 _macro_ `#define UE_ONLINE_SUBSYSTEM_FEATURE_ENABLED(FeatureName) \`
- L67 _macro_ `#define UE_REGISTER_ONLINE_SUBSYSTEM_FEATURE_RUNTIMECHECK(FeatureName, CheckFunction)` — No-op implementation.
- L68 _macro_ `#define UE_UNREGISTER_ONLINE_SUBSYSTEM_FEATURE_RUNTIMECHECK(FeatureName)`
- L69 _macro_ `#define UE_DECLARE_ONLINE_SUBSYSTEM_FEATURE(StorageClass, FeatureName)`
- L70 _macro_ `#define UE_DEFINE_ONLINE_SUBSYSTEM_FEATURE(FeatureName)`

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystemImpl.h` (Public)


#### class `FOnlineSubsystemImpl`  
`class FOnlineSubsystemImpl : public IOnlineSubsystem , public FTSTickerObjectBase`  
_L24-175_
- inherits: `IOnlineSubsystem,FTSTickerObjectBase`
- desc: FOnlineSubsystemImpl - common functionality to share across online platforms, not intended for direct use
- L33 _private prototype_ `bool HandleFriendExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);` — Exec function handling for Exec() call
- L34 _private prototype_ `bool HandleIdentityExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L35 _private prototype_ `bool HandleSessionExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L36 _private prototype_ `bool HandlePresenceExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L37 _private prototype_ `bool HandlePurchaseExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L38 _private prototype_ `bool HandleStoreExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L41 _private prototype_ `void OnQueryReceiptsComplete(const FOnlineError& Result, FUniqueNetIdPtr UserId);` — Delegate fired when exec cheat related to receipts completes
- L44 _private prototype_ `void DumpReceipts(const FUniqueNetId& UserId);` — Dump purchase receipts for a given user id
- L46 _private prototype_ `void FinalizeReceipts(const FUniqueNetId& UserId);` — Finalize purchases known to the client, will wipe real money purchases without fulfillment
- L51 _protected prototype_ `FOnlineSubsystemImpl() = delete;` — Hidden on purpose
- L53 _protected prototype_ `FOnlineSubsystemImpl(FName InSubsystemName, FName InInstanceName);`
- L54 _protected prototype_ `FOnlineSubsystemImpl(FName InSubsystemName, FName InInstanceName, FTSTicker& Ticker);`
- L57 _protected member_ `FName SubsystemName;` — Name of the subsystem @see OnlineSubsystemNames.h
- L59 _protected member_ `FName InstanceName;` — Instance name (disambiguates PIE instances for example)
- L62 _protected member_ `bool bForceDedicated;` — Whether or not the online subsystem is in forced dedicated server mode
- L65 _protected member_ `mutable class UNamedInterfaces* NamedInterfaces;` — Holds all currently named interfaces
- L68 _protected prototype_ `void InitNamedInterfaces();` — Load in any named interfaces specified by the ini configuration
- L71 _protected prototype_ `void OnNamedInterfaceCleanup();` — Delegate fired when named interfaces are cleaned up at exit
- L74 _protected member_ `TQueue<FNextTickDelegate, EQueueMode::Mpsc> NextTickQueue;` — Queue to hold callbacks scheduled for next tick using ExecuteNextTick
- L77 _protected member_ `TArray<FNextTickDelegate> CurrentTickBuffer;` — Buffer to hold callbacks for the current tick (so it's safe to call ExecuteNextTick within a tick callback)
- L80 _protected prototype_ `void StartTicker();` — Start Ticker
- L83 _protected prototype_ `void StopTicker();` — Stop Ticker
- L86 _protected member_ `bool bTickerStarted;` — Is the ticker started
- L90 _public prototype_ `virtual ~FOnlineSubsystemImpl();`
- L93 _public prototype_ `virtual IOnlineGroupsPtr GetGroupsInterface() const override;` — IOnlineSubsystem
- L94 _public prototype_ `virtual IOnlinePartyPtr GetPartyInterface() const override;`
- L95 _public prototype_ `virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override;`
- L96 _public prototype_ `virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;`
- L97 _public prototype_ `virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;`
- L98 _public prototype_ `virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;`
- L99 _public prototype_ `virtual IOnlineVoicePtr GetVoiceInterface() const override;`
- L100 _public prototype_ `virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;`
- L101 _public prototype_ `virtual IOnlineTimePtr GetTimeInterface() const override;`
- L102 _public prototype_ `virtual IOnlineIdentityPtr GetIdentityInterface() const override;`
- L103 _public prototype_ `virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;`
- L104 _public prototype_ `virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override;`
- L105 _public prototype_ `virtual IOnlinePurchasePtr GetPurchaseInterface() const override;`
- L106 _public prototype_ `virtual IOnlineEventsPtr GetEventsInterface() const override;`
- L107 _public prototype_ `virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;`
- L108 _public prototype_ `virtual IOnlineSharingPtr GetSharingInterface() const override;`
- L109 _public prototype_ `virtual IOnlineUserPtr GetUserInterface() const override;`
- L110 _public prototype_ `virtual IOnlineMessagePtr GetMessageInterface() const override;`
- L111 _public prototype_ `virtual IOnlinePresencePtr GetPresenceInterface() const override;`
- L112 _public prototype_ `virtual IOnlineChatPtr GetChatInterface() const override;`
- L113 _public prototype_ `virtual IOnlineStatsPtr GetStatsInterface() const override;`
- L114 _public prototype_ `virtual IOnlineGameActivityPtr GetGameActivityInterface() const override;`
- L115 _public prototype_ `virtual IOnlineGameItemStatsPtr GetGameItemStatsInterface() const override;`
- L116 _public prototype_ `virtual IOnlineGameMatchesPtr GetGameMatchesInterface() const override;`
- L117 _public prototype_ `virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override;`
- L118 _public prototype_ `virtual IOnlineTournamentPtr GetTournamentInterface() const override;`
- L119 _public prototype_ `virtual IOnlineContentAgeRestrictionPtr GetOnlineContentAgeRestrictionInterface() const override;`
- L120 _public prototype_ `virtual void PreUnload() override;`
- L121 _public prototype_ `virtual bool Shutdown() override;`
- L122 _public prototype_ `virtual bool IsServer() const override;`
- L123 _public function_ `virtual bool IsDedicated() const override`
- L124 _public function_ `virtual void SetForceDedicated(bool bForce) override`
- L125 _public prototype_ `virtual class UObject* GetNamedInterface(FName InterfaceName) override;`
- L126 _public prototype_ `virtual void SetNamedInterface(FName InterfaceName, class UObject* NewInterface) override;`
- L127 _public prototype_ `virtual bool IsLocalPlayer(const FUniqueNetId& UniqueId) const override;`
- L128 _public function_ `virtual void SetUsingMultiplayerFeatures(const FUniqueNetId& UniqueId, bool bUsingMP) override`
- L129 _public function_ `virtual EOnlineEnvironment::Type GetOnlineEnvironment() const override`
- L130 _public function_ `virtual FString GetOnlineEnvironmentName() const override`
- L131 _public prototype_ `virtual IMessageSanitizerPtr GetMessageSanitizer(int32 LocalUserNum, FString& OutAuthTypeToExclude) const override;`
- L132 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L133 _public function_ `virtual FName GetSubsystemName() const override`
- L134 _public function_ `virtual FName GetInstanceName() const override`
- L135 _public prototype_ `virtual bool IsEnabled() const override;`
- L136 _public function_ `virtual void ReloadConfigs(const TSet<FString>& ) override`
- L137 _public prototype_ `virtual FText GetSocialPlatformName() const override;`
- L140 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L143 _public prototype_ `void PIEEndCleanup();` — Performs cleanup tasks for editor teardown
- L152 _public prototype_ `static FString FilterResponseStr(const FString& ResponseStr, const TArray<FString>& RedactFields = TArray<FString>());` — Modify a response string so that it can be logged cleanly @param ResponseStr - The JSONObject string we want to sanitize @param RedactFields - The fields we want to specifically omit (optional, only supports EJson::String), if nothing specified everything is redacted @return the modified version of the response string
- L157 _public prototype_ `void ExecuteDelegateNextTick(const FNextTickDelegate& Callback);` — Queue a delegate to be executed on the next tick
- L163 _public function_ `template<typename LAMBDA_TYPE> inline void ExecuteNextTick(LAMBDA_TYPE&& Callback)` — Templated helper for calling ExecuteDelegateNextTick with a lambda function
- L171 _public prototype_ `virtual void OnConfigSectionsChanged(const FString& IniFilename, const TSet<FString>& SectionNames);` — Delegate for config file changes.
- L174 _public member_ `static const FName DefaultInstanceName;` — Name given to default OSS instances (disambiguates for PIE)

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ONLINESUBSYSTEM_API`
- L14 _delegate_ `DECLARE_DELEGATE(FNextTickDelegate);`
- L14 _prototype_ `DECLARE_DELEGATE(FNextTickDelegate);`
- L16 _namespace_ `namespace OSSConsoleVariables`
- L18 _externvar_ `extern TAutoConsoleVariable<int32> CVarVoiceLoopback;` (scope `OSSConsoleVariables`)

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystemModule.h` (Public)


#### class `FOnlineSubsystemModule`  
`class FOnlineSubsystemModule : public IModuleInterface`  
_L17-251_
- inherits: `IModuleInterface`
- desc: Online subsystem module class Wraps the loading of an online subsystem by name and allows new services to register themselves for use
- L26 _private member_ `FName DefaultPlatformService;` — Name of the default online service requested Specified in DefaultEngine.ini [OnlineSubsystem] DefaultPlatformService
- L34 _private member_ `FName NativePlatformService;` — Name of the online service associated with the native platform Specified in Base<Platform>Engine.ini [OnlineSubsystem] NativePlatformService
- L42 _private member_ `TMap<FString, FName> ConfigDefinedSubsystems;` — Name of the online service associated with User Defined strings Specified in Base<Platform>Engine.ini [OnlineSubsystem] ConfigDefinedPlatformServices
- L45 _private member_ `TMap<FName, IOnlineFactory*> OnlineFactories;` — Existing instances of any online subsystems created <PlatformName:InstanceName>
- L48 _private member_ `TMap<FName, IOnlineSubsystemPtr> OnlineSubsystems;` — Mapping of all currently loaded platform service subsystems to their name
- L55 _private member_ `mutable FTransactionallySafeCriticalSection OnlineSubsystemsLock;` — Lock for access to OnlineSubsystems array to allow for multiple threads to be able to create/get online subsystems simultaneously. The intent is OnlineSubsystems can have elements added on separate threads through normal gameplay, though this is expected to be very rare and only once per subsystem type. OnlineSubsystems is not expected to remove elements except in very controlled scenarios.  In that case, the lock is only limiting access to the OnlineSubsystems array, but the result may be invalidated.
- L58 _private member_ `TSet<FName> OnlineSubsystemFailureNotes;` — Have we warned already for a given online subsystem creation failure
- L61 _private member_ `TMap<FString, FName> ModuleRedirects;` — Config driven override of module name for online subsystem
- L79 _private prototype_ `FName ParseOnlineSubsystemName(const FName& FullName, FName& SubsystemName, FName& InstanceName) const;` — Transform an online subsystem identifier into its Subsystem and Instance constituents accepts the following forms: <subsystem name>:<instance name> -> subsystem name / instance name :<instance name>					-> default subsystem / instance name <subsystem name>:				-> subsystem name / default instance <subsystem name>					-> subsystem name / default instance <nothing>						-> default subsystem / default instance @param FullName full name of the subsystem and instance that is being referenced @param SubsystemName parsed out value or default subsystem name @param InstanceName parsed out value or default instance name @return Properly formatted key name for accessing the online subsystem in the TMap
- L84 _private prototype_ `void ProcessConfigDefinedSubsystems();` — Read any config defined subsystems from the configuration file
- L89 _private prototype_ `void ProcessConfigDefinedModuleRedirects();` — Read any config defined subsystem module overrides from the configuration file
- L94 _private prototype_ `bool TryLoadSubsystemAndSetDefault(FName ModuleName);` — Attempt to load the default subsystem specified in the configuration file
- L99 _private prototype_ `void LoadDefaultSubsystem();` — Attempt to load the default subsystem specified in the configuration file
- L104 _private prototype_ `virtual void PreUnloadOnlineSubsystem();` — Called before ShutdownOnlineSubsystem, before other modules have been unloaded
- L109 _private prototype_ `virtual void ShutdownOnlineSubsystem();` — Shuts down all registered online subsystem platforms and unloads their modules
- L113 _public function_ `FOnlineSubsystemModule() : DefaultPlatformService(NAME_None)`
- L116 _public prototype_ `virtual ~FOnlineSubsystemModule() = default;`
- L127 _public prototype_ `virtual IOnlineSubsystem* GetOnlineSubsystem(const FName InSubsystemName = NAME_None);` — Main entry point for accessing an online subsystem by name Will load the appropriate module if the subsystem isn't currently loaded It's possible that the subsystem doesn't exist and therefore can return NULL @param InSubsystemName - name of subsystem as referenced by consumers @return Requested online subsystem, or NULL if that subsystem was unable to load or doesn't exist
- L136 _public prototype_ `virtual IOnlineSubsystem* GetNativeSubsystem(bool bAutoLoad);` — Get the online subsystem native to the current hardware @param bAutoLoad - load the module if not already loaded @return pointer to the appropriate online subsystem
- L146 _public prototype_ `virtual IOnlineSubsystem* GetSubsystemByConfig(const FString& ConfigString, bool bAutoLoad);` — Get the online subsystem associated with the given config string @param ConfigString - Key to query for @param bAutoLoad - load the module if not already loaded @return pointer to the appropriate online subsystem
- L155 _public prototype_ `virtual void DestroyOnlineSubsystem(const FName InSubsystemName);` — Destroys an online subsystem created internally via access with GetOnlineSubsystem Typically destruction of the subsystem is handled at application exit, but there may be rare instances where the subsystem is destroyed by request @param InSubsystemName - name of subsystem as referenced by consumers
- L162 _public prototype_ `bool DoesInstanceExist(const FName InSubsystemName) const;` — Does an instance of subsystem with the given name exist @return true if the instance exists, false otherwise
- L170 _public prototype_ `virtual bool IsOnlineSubsystemLoaded(const FName InSubsystemName) const;` — Determine if a subsystem is loaded by the OSS module @param SubsystemName - name of subsystem as referenced by consumers @return true if module for the subsystem is loaded
- L177 _public prototype_ `virtual void RegisterPlatformService(const FName FactoryName, class IOnlineFactory* Factory);` — Register a new online subsystem interface with the base level factory provider @param FactoryName - name of subsystem as referenced by consumers @param Factory - instantiation of the online subsystem interface, this will take ownership
- L183 _public prototype_ `virtual void UnregisterPlatformService(const FName FactoryName);` — Unregister an existing online subsystem interface from the base level factory provider @param FactoryName - name of subsystem as referenced by consumers
- L190 _public typedef_ `typedef TFunction<void(IOnlineSubsystem*)> FEnumerateOnlineSubsystemCb;` — Enumerate all loaded online subsystems @param EnumCb functor to call for each online subsystem
- L191 _public prototype_ `void EnumerateOnlineSubsystems(FEnumerateOnlineSubsystemCb& EnumCb);`
- L200 _public prototype_ `void ReloadDefaultSubsystem();` — Shutdown the current default subsystem (may be the fallback) and attempt to reload the one specified in the configuration file **NOTE** This is intended for editor use only, attempting to use this at the wrong time can result in unexpected crashes/behavior
- L208 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created Overloaded to allow the default subsystem a chance to load
- L214 _public prototype_ `virtual void PreUnloadCallback() override;` — Called before the module has been unloaded Overloaded to allow online subsystems to cancel any outstanding http requests
- L220 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed. Overloaded to shut down all loaded online subsystems
- L227 _public function_ `virtual bool SupportsDynamicReloading() override` — Override this to set whether your module is allowed to be unloaded on the fly @return	Whether the module supports shutdown separate from the rest of the engine.
- L237 _public function_ `virtual bool SupportsAutomaticShutdown() override` — Override this to set whether your module would like cleanup on application shutdown @return	Whether the module supports shutdown on application exit
- L250 _private member_ `mutable TMap<FName, FInstanceNameEntry> InstanceNames;`

#### struct `FOnlineSubsystemModule::FInstanceNameEntry`  
`struct FInstanceNameEntry`  
_L244-249_
- desc: Cached instance names for efficient lookup in ParseOnlineSubsystemName
- L246 _public member_ `FName SubsystemName;`
- L247 _public member_ `FName InstanceName;`
- L248 _public member_ `FName FullPath;`

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TSharedPtr<class IOnlineSubsystem, ESPMode::ThreadSafe> IOnlineSubsystemPtr;`
- L254 _typedef_ `typedef TSharedPtr<FOnlineSubsystemModule, ESPMode::ThreadSafe> FOnlineSubsystemModulePtr;` — Public references to the online subsystem module pointer should use this

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystemNames.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define OSS_PLATFORM_NAME_PS4 TEXT("PSN")`
- L9 _macro_ `#define OSS_PLATFORM_NAME_XBOX TEXT("XBL")`
- L10 _macro_ `#define OSS_PLATFORM_NAME_WINDOWS TEXT("WIN")`
- L11 _macro_ `#define OSS_PLATFORM_NAME_MAC TEXT("MAC")`
- L12 _macro_ `#define OSS_PLATFORM_NAME_LINUX TEXT("LNX")`
- L13 _macro_ `#define OSS_PLATFORM_NAME_IOS TEXT("IOS")`
- L14 _macro_ `#define OSS_PLATFORM_NAME_ANDROID TEXT("AND")`
- L15 _macro_ `#define OSS_PLATFORM_NAME_SWITCH TEXT("SWT")`
- L16 _macro_ `#define OSS_PLATFORM_NAME_SWITCH2 TEXT("SWT2")`
- L17 _macro_ `#define OSS_PLATFORM_NAME_OTHER TEXT("OTHER")`
- L22 _externvar_ `extern const FName NULL_SUBSYSTEM;`
- L26 _externvar_ `extern const FName GOOGLEPLAY_SUBSYSTEM;`
- L30 _externvar_ `extern const FName IOS_SUBSYSTEM;`
- L34 _externvar_ `extern const FName APPLE_SUBSYSTEM;`
- L38 _externvar_ `extern const FName AMAZON_SUBSYSTEM;`
- L42 _externvar_ `extern const FName GOOGLE_SUBSYSTEM;`
- L46 _externvar_ `extern const FName FACEBOOK_SUBSYSTEM;`
- L50 _externvar_ `extern const FName GAMECIRCLE_SUBSYSTEM;`
- L54 _externvar_ `extern const FName STEAM_SUBSYSTEM;`
- L58 _externvar_ `extern const FName PS4_SUBSYSTEM;`
- L62 _externvar_ `extern const FName PS4SERVER_SUBSYSTEM;`
- L66 _externvar_ `extern const FName PS5_SUBSYSTEM;`
- L70 _externvar_ `extern const FName GDK_SUBSYSTEM;`
- L74 _externvar_ `extern const FName THUNDERHEAD_SUBSYSTEM;`
- L78 _externvar_ `extern const FName MCP_SUBSYSTEM;`
- L82 _externvar_ `extern const FName TENCENT_SUBSYSTEM;`
- L86 _externvar_ `extern const FName NINTENDO_SUBSYSTEM;`
- L90 _externvar_ `extern const FName SAMSUNG_SUBSYSTEM;`
- L94 _externvar_ `extern const FName ONESTORE_SUBSYSTEM;`
- L98 _externvar_ `extern const FName EOS_SUBSYSTEM;`

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystemPackage.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define PACKAGE_SCOPE public`
- L14 _macro_ `#define PACKAGE_SCOPE protected`

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystemSessionSettings.h` (Public)
_(no declarations extracted)_

### `Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystemTypes.h` (Public)


#### enum `EOnlineEnvironment::Type`  
`enum Type`  
_L31-41_
- L34 _public enumerator_ `Development` — Dev environment
- L36 _public enumerator_ `Certification` — Cert environment
- L38 _public enumerator_ `Production` — Prod environment
- L40 _public enumerator_ `Unknown` — Not determined yet

#### enum `ELoginStatus::Type`  
`enum Type`  
_L50-58_
- L53 _public enumerator_ `NotLoggedIn` — Player has not logged in or chosen a local profile
- L55 _public enumerator_ `UsingLocalProfile` — Player is using a local profile but is not logged in
- L57 _public enumerator_ `LoggedIn` — Player has been validated by the platform specific authentication service

#### enum `EOnlineServerConnectionStatus::Type`  
`enum Type : uint8`  
_L67-93_
- L70 _public enumerator_ `Normal = 0` — System normal (used for default state)
- L72 _public enumerator_ `NotConnected` — Gracefully disconnected from the online servers
- L74 _public enumerator_ `Connected` — Connected to the online servers just fine
- L76 _public enumerator_ `ConnectionDropped` — Connection was lost for some reason
- L78 _public enumerator_ `NoNetworkConnection` — Can't connect because of missing network connection
- L80 _public enumerator_ `ServiceUnavailable` — Service is temporarily unavailable
- L82 _public enumerator_ `UpdateRequired` — An update is required before connecting is possible
- L84 _public enumerator_ `ServersTooBusy` — Servers are too busy to handle the request right now
- L86 _public enumerator_ `DuplicateLoginDetected` — Disconnected due to duplicate login
- L88 _public enumerator_ `InvalidUser` — Can't connect because of an invalid/unknown user
- L90 _public enumerator_ `NotAuthorized` — Not authorized
- L92 _public enumerator_ `InvalidSession` — Session has been lost on the backend

#### enum `EFeaturePrivilegeLevel::Type`  
`enum Type`  
_L102-112_
- L105 _public enumerator_ `Undefined` — Not defined for the platform service
- L107 _public enumerator_ `Disabled` — Parental controls have disabled this feature
- L109 _public enumerator_ `EnabledFriendsOnly` — Parental controls allow this feature only with people on their friends list
- L111 _public enumerator_ `Enabled` — Parental controls allow this feature everywhere

#### enum `EOnlineAsyncTaskState::Type`  
`enum Type : int`  
_L121-131_
- L124 _public enumerator_ `NotStarted` — The task has not been started
- L126 _public enumerator_ `InProgress` — The task is currently being processed
- L128 _public enumerator_ `Done` — The task has completed successfully
- L130 _public enumerator_ `Failed` — The task failed to complete

#### enum `EOnlineFriendState::Type`  
`enum Type`  
_L140-150_
- L143 _public enumerator_ `Offline` — Not currently online
- L145 _public enumerator_ `Online` — Signed in and online
- L147 _public enumerator_ `Away` — Signed in, online, and idle
- L149 _public enumerator_ `Busy` — Signed in, online, and asks to be left alone

#### enum `ELeaderboardSort::Type`  
`enum Type`  
_L159-167_
- L162 _public enumerator_ `None` — Don't sort at all
- L164 _public enumerator_ `Ascending` — Sort ascending
- L166 _public enumerator_ `Descending` — Sort descending

#### enum `ELeaderboardFormat::Type`  
`enum Type`  
_L176-184_
- L179 _public enumerator_ `Number` — A raw number
- L181 _public enumerator_ `Seconds` — Time, in seconds
- L183 _public enumerator_ `Milliseconds` — Time, in milliseconds

#### enum `ELeaderboardUpdateMethod::Type`  
`enum Type`  
_L193-199_
- L196 _public enumerator_ `KeepBest` — If current leaderboard score is better than the uploaded one, keep the current one
- L198 _public enumerator_ `Force` — Leaderboard score is always replaced with uploaded value

#### enum `EOnlineSessionState::Type`  
`enum Type`  
_L208-226_
- L211 _public enumerator_ `NoSession` — An online session has not been created yet
- L213 _public enumerator_ `Creating` — An online session is in the process of being created
- L215 _public enumerator_ `Pending` — Session has been created but the session hasn't started (pre match lobby)
- L217 _public enumerator_ `Starting` — Session has been asked to start (may take time due to communication with backend)
- L219 _public enumerator_ `InProgress` — The current session has started. Sessions with join in progress disabled are no longer joinable
- L221 _public enumerator_ `Ending` — The session is still valid, but the session is no longer being played (post match lobby)
- L223 _public enumerator_ `Ended` — The session is closed and any stats committed
- L225 _public enumerator_ `Destroying` — The session is being destroyed

#### enum `EOnlineDataAdvertisementType::Type`  
`enum Type : uint8`  
_L235-245_
- L238 _public enumerator_ `DontAdvertise` — Don't advertise via the online service or QoS data
- L240 _public enumerator_ `ViaPingOnly` — Advertise via the server ping data only
- L242 _public enumerator_ `ViaOnlineService` — Advertise via the online service only
- L244 _public enumerator_ `ViaOnlineServiceAndPing` — Advertise via the online service and via the ping data

#### enum `EOnlineComparisonOp::Type`  
`enum Type`  
_L254-265_
- L256 _public enumerator_ `Equals`
- L257 _public enumerator_ `NotEquals`
- L258 _public enumerator_ `GreaterThan`
- L259 _public enumerator_ `GreaterThanEquals`
- L260 _public enumerator_ `LessThan`
- L261 _public enumerator_ `LessThanEquals`
- L262 _public enumerator_ `Near`
- L263 _public enumerator_ `In`
- L264 _public enumerator_ `NotIn`

#### enum `EOnlineCachedResult::Type`  
`enum Type`  
_L274-278_
- L276 _public enumerator_ `Success`
- L277 _public enumerator_ `NotFound` — Success,   The requested data was found and returned successfully.

#### enum `EFriendInvitePolicy`  
`enum class EFriendInvitePolicy : uint8`  
_L288-298_
- desc: Permissions for who can send invites to a user.
- L291 _public enumerator_ `Public` — Anyone can send a friend invite.
- L293 _public enumerator_ `Friends_of_Friends` — Only friends of friends can send a friend invite.
- L295 _public enumerator_ `Private` — No one can send a friend invite.
- L297 _public enumerator_ `InvalidOrMax` — Invalid enum type, may be used as a number of enumerations.

#### class `IOnlinePlatformData`  
`class IOnlinePlatformData`  
_L309-384_
- desc: Base class for anything meant to be opaque so that the data can be passed around without consideration for the data it contains. A human readable version of the data is available via the ToString() function Otherwise, nothing but platform code should try to operate directly on the data
- L314 _protected function_ `IOnlinePlatformData()` — Hidden on purpose
- L319 _protected function_ `IOnlinePlatformData(const IOnlinePlatformData& Src)` — Hidden on purpose
- L324 _protected function_ `IOnlinePlatformData& operator=(const IOnlinePlatformData& Src)` — Hidden on purpose
- L329 _protected prototype_ `virtual bool Compare(const IOnlinePlatformData& Other) const;`
- L333 _public prototype_ `virtual ~IOnlinePlatformData() = default;`
- L338 _public function_ `bool operator==(const IOnlinePlatformData& Other) const` — Comparison operator
- L343 _public function_ `bool operator!=(const IOnlinePlatformData& Other) const`
- L354 _public prototype_ `virtual const uint8* GetBytes() const = 0;` — Get the raw byte representation of this opaque data This data is platform dependent and shouldn't be manipulated directly @return byte array of size GetSize()
- L361 _public prototype_ `virtual int32 GetSize() const = 0;` — Get the size of the opaque data @return size in bytes of the data representation
- L368 _public prototype_ `virtual bool IsValid() const = 0;` — Check the validity of the opaque data @return true if this is well formed data, false otherwise
- L375 _public prototype_ `virtual FString ToString() const = 0;` — Platform specific conversion to string representation of data @return data in string form
- L383 _public prototype_ `virtual FString ToDebugString() const = 0;` — Get a human readable representation of the opaque data Shouldn't be used for anything other than logging/debugging @return data in string form

#### struct `FUniqueNetIdMatcher`  
`struct FUniqueNetIdMatcher`  
_L389-430_
- desc: TArray helper for IndexOfByPredicate() function
- L393 _private member_ `const FUniqueNetId& UniqueIdTarget;` — Target for comparison in the TArray
- L396 _public function_ `FUniqueNetIdMatcher(const FUniqueNetId& InUniqueIdTarget) : UniqueIdTarget(InUniqueIdTarget)`
- L406 _public function_ `bool operator()(const FUniqueNetId& Candidate) const` — Match a given unique Id against the one stored in this struct @return true if they are an exact match, false otherwise
- L416 _public function_ `bool operator()(const FUniqueNetIdPtr& Candidate) const` — Match a given unique Id against the one stored in this struct @return true if they are an exact match, false otherwise
- L426 _public function_ `bool operator()(const FUniqueNetIdRef& Candidate) const` — Match a given unique Id against the one stored in this struct @return true if they are an exact match, false otherwise

#### class `FUniqueNetIdString`  
`class FUniqueNetIdString : public FUniqueNetId`  
_L441-561_
- inherits: `FUniqueNetId`
- desc: Unique net id wrapper for a string
- L445 _public member_ `FString UniqueNetIdStr;` — Holds the net id for a player
- L447 _public member_ `FName Type = NAME_Unset;`
- L449 _public function_ `static FUniqueNetIdStringRef Create(const FString& InUniqueNetId, const FName InType)`
- L454 _public function_ `static FUniqueNetIdStringRef Create(FString&& InUniqueNetId, const FName InType)`
- L459 _public function_ `static FUniqueNetIdStringRef& EmptyId()`
- L465 _public prototype_ `virtual ~FUniqueNetIdString() = default;`
- L469 _public function_ `virtual FName GetType() const override`
- L474 _public function_ `virtual const uint8* GetBytes() const override`
- L479 _public function_ `virtual int32 GetSize() const override`
- L484 _public function_ `virtual bool IsValid() const override`
- L489 _public function_ `virtual FString ToString() const override`
- L494 _public function_ `virtual FString ToDebugString() const override`
- L506 _public function_ `virtual uint32 GetTypeHash() const override`
- L512 _protected prototype_ `FUniqueNetIdString() = default;`
- L519 _protected function_ `explicit FUniqueNetIdString(const FString& InUniqueNetId) : UniqueNetIdStr(InUniqueNetId) , Type(NAME_Unset)` — Constructs this object with the specified net id @param InUniqueNetId the id to set ours to
- L530 _protected function_ `explicit FUniqueNetIdString(FString&& InUniqueNetId) : UniqueNetIdStr(MoveTemp(InUniqueNetId)) , Type(NAME_Unset)` — Constructs this object with the specified net id @param InUniqueNetId the id to set ours to
- L541 _protected function_ `explicit FUniqueNetIdString(const FUniqueNetId& Src) : UniqueNetIdStr(Src.ToString()) , Type(Src.GetType())` — Constructs this object with the string value of the specified net id @param Src the id to copy
- L550 _protected function_ `FUniqueNetIdString(const FString& InUniqueNetId, const FName InType) : UniqueNetIdStr(InUniqueNetId) , Type(InType)` — don.eubanks - Including a constructor that allows for type passing to make transitioning easier, if we determine we want to abstract-ify this class, this constructor will be removed
- L556 _protected function_ `FUniqueNetIdString(FString&& InUniqueNetId, const FName InType) : UniqueNetIdStr(MoveTemp(InUniqueNetId)) , Type(InType)`

#### class `FSharedContentHandle`  
`class FSharedContentHandle : public IOnlinePlatformData`  
_L632-655_
- inherits: `IOnlinePlatformData`
- desc: Abstraction of a profile service shared file handle The class is meant to be opaque (see IOnlinePlatformData)
- L637 _protected function_ `FSharedContentHandle()` — Hidden on purpose
- L642 _protected function_ `FSharedContentHandle(const FSharedContentHandle& Src)` — Hidden on purpose
- L647 _protected function_ `FSharedContentHandle& operator=(const FSharedContentHandle& Src)` — Hidden on purpose
- L654 _public prototype_ `virtual ~FSharedContentHandle() = default;`

#### class `FOnlineSessionInfo`  
`class FOnlineSessionInfo : public IOnlinePlatformData`  
_L661-691_
- inherits: `IOnlinePlatformData`
- desc: Abstraction of a session's platform specific info The class is meant to be opaque (see IOnlinePlatformData)
- L666 _protected function_ `FOnlineSessionInfo()` — Hidden on purpose
- L671 _protected function_ `FOnlineSessionInfo(const FOnlineSessionInfo& Src)` — Hidden on purpose
- L676 _protected function_ `FOnlineSessionInfo& operator=(const FOnlineSessionInfo& Src)` — Hidden on purpose
- L683 _public prototype_ `virtual ~FOnlineSessionInfo() = default;`
- L690 _public prototype_ `virtual const FUniqueNetId& GetSessionId() const = 0;` — Get the session id associated with this session @return session id for this session

#### class `FPagedQuery`  
`class FPagedQuery`  
_L696-719_
- desc: Paging info needed for a request that can return paged results
- L699 _public function_ `FPagedQuery(int32 InStart = 0, int32 InCount = -1) : Start(InStart) , Count(InCount)`
- L705 _public function_ `bool IsValidRange() const` — @return true if valid range
- L710 _public function_ `bool operator==(const FPagedQuery& Other) const`
- L716 _public member_ `int32 Start;` — first entry to fetch
- L718 _public member_ `int32 Count;` — total entries to fetch. -1 means ALL

#### class `FOnlinePagedResult`  
`class FOnlinePagedResult`  
_L724-740_
- desc: Info for a response with paged results
- L727 _public function_ `FOnlinePagedResult() : Start(0) , Count(0) , Total(0)`
- L732 _public prototype_ `virtual ~FOnlinePagedResult() = default;`
- L735 _public member_ `int32 Start;` — Starting entry
- L737 _public member_ `int32 Count;` — Number returned
- L739 _public member_ `int32 Total;` — Total available

#### class `FRegionInfo`  
`class FRegionInfo`  
_L743-756_
- desc: Locale and country code
- L747 _public function_ `FRegionInfo(const FString& InCountry = FString(), const FString& InLocale = FString()) : Country(InCountry) , Locale(InLocale)`
- L753 _public member_ `FString Country;` — country code used for configuring things like currency/pricing specific to a country. eg. US
- L755 _public member_ `FString Locale;` — local code used to select the localization language. eg. en_US

#### struct `FCloudFileHeader`  
`struct FCloudFileHeader`  
_L759-807_
- desc: Holds metadata about a given downloadable file
- L762 _public member_ `FString Hash;` — Hash value, if applicable, of the given file contents
- L764 _public member_ `FName HashType;` — The hash algorithm used to sign this file
- L766 _public member_ `FString DLName;` — Filename as downloaded
- L768 _public member_ `FString FileName;` — Logical filename, maps to the downloaded filename
- L770 _public member_ `int32 FileSize;` — File size
- L772 _public member_ `FString URL;` — The full URL to download the file if it is stored in a CDN or separate host site
- L774 _public member_ `uint32 ChunkID;` — The chunk id this file represents
- L776 _public member_ `TMap<FString, FString> ExternalStorageIds;` — Pointers to externally-accessible representations of this file
- L779 _public function_ `FCloudFileHeader() : FileSize(0), ChunkID(0)` — Constructors
- L784 _public function_ `FCloudFileHeader(const FString& InFileName, const FString& InDLName, int32 InFileSize) : DLName(InDLName), FileName(InFileName), FileSize(InFileSize), ChunkID(0)`
- L791 _public function_ `bool operator==(const FCloudFileHeader& Other) const`
- L803 _public function_ `bool operator<(const FCloudFileHeader& Other) const`

#### struct `FCloudFile`  
`struct FCloudFile`  
_L810-832_
- desc: Holds the data used in downloading a file asynchronously from the online service
- L813 _public member_ `FString FileName;` — The name of the file as requested
- L815 _public member_ `EOnlineAsyncTaskState::Type AsyncState;` — The async state the file download is in
- L817 _public member_ `TArray<uint8> Data;` — The buffer of data for the file
- L820 _public function_ `FCloudFile() : AsyncState(EOnlineAsyncTaskState::NotStarted)` — Constructors
- L825 _public function_ `FCloudFile(const FString& InFileName) : FileName(InFileName), AsyncState(EOnlineAsyncTaskState::NotStarted)`
- L831 _public prototype_ `virtual ~FCloudFile() = default;`

#### class `FOnlineUser`  
`class FOnlineUser`  
_L847-876_
- desc: Base for all online user info
- L853 _public prototype_ `virtual ~FOnlineUser() = default;` — destructor
- L858 _public prototype_ `virtual FUniqueNetIdRef GetUserId() const = 0;` — @return Id associated with the user account provided by the online service during registration
- L862 _public prototype_ `virtual FString GetRealName() const = 0;` — @return the real name for the user if known
- L866 _public prototype_ `virtual FString GetDisplayName(const FString& Platform = FString()) const = 0;` — @return the nickname of the user if known
- L870 _public prototype_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const = 0;` — @return Any additional user data associated with a registered user
- L875 _public function_ `virtual bool SetUserLocalAttribute(const FString& AttrName, const FString& InAttrValue)` — @return Whether a local attribute for a user was successfully set.

#### class `FUserOnlineAccount`  
`class FUserOnlineAccount : public FOnlineUser`  
_L888-908_
- inherits: `FOnlineUser`
- desc: User account information returned via IOnlineIdentity interface
- L894 _public prototype_ `virtual FString GetAccessToken() const = 0;` — @return Access token which is provided to user once authenticated by the online service
- L899 _public function_ `virtual bool HasAccessTokenExpired(const FDateTime& Time) const` — Tests if token has exceeded its time-to-live, when applicable.  Default is true, i.e. always expire. @return True, if access token has expired.
- L903 _public prototype_ `virtual bool GetAuthAttribute(const FString& AttrName, FString& OutAttrValue) const = 0;` — @return Any additional auth data associated with a registered user
- L907 _public prototype_ `virtual bool SetUserAttribute(const FString& AttrName, const FString& AttrValue) = 0;` — @return True, if the data has been changed

#### enum `EInviteStatus::Type`  
`enum Type`  
_L915-929_
- L918 _public enumerator_ `Unknown` — unknown state
- L920 _public enumerator_ `Accepted` — Friend has accepted the invite
- L922 _public enumerator_ `PendingInbound` — Friend has sent player an invite, but it has not been accepted/rejected
- L924 _public enumerator_ `PendingOutbound` — Player has sent friend an invite, but it has not been accepted/rejected
- L926 _public enumerator_ `Blocked` — Player has been blocked
- L928 _public enumerator_ `Suggested` — Suggested friend

#### class `FOnlineFriend`  
`class FOnlineFriend : public FOnlineUser`  
_L940-953_
- inherits: `FOnlineUser`
- desc: Friend user info returned via IOnlineFriends interface
- L947 _public prototype_ `virtual EInviteStatus::Type GetInviteStatus() const = 0;` — @return the current invite status of a friend wrt to user that queried
- L952 _public prototype_ `virtual const class FOnlineUserPresence& GetPresence() const = 0;` — @return presence info for an online friend

#### class `FOnlineRecentPlayer`  
`class FOnlineRecentPlayer : public FOnlineUser`  
_L958-966_
- inherits: `FOnlineUser`
- desc: Recent player user info returned via IOnlineFriends interface
- L965 _public prototype_ `virtual FDateTime GetLastSeen() const = 0;` — @return last time the player was seen by the current user

#### class `FOnlineBlockedPlayer`  
`class FOnlineBlockedPlayer : public FOnlineUser`  
_L971-973_
- inherits: `FOnlineUser`
- desc: Blocked user info returned via IOnlineFriends interface

#### enum `EOnlineSharingPermissionState`  
`enum class EOnlineSharingPermissionState : uint8`  
_L976-984_
- desc: Valid states for user facing permissions
- L979 _public enumerator_ `Unknown = 0` — Permission has not been requested yet
- L981 _public enumerator_ `Declined = 1` — Permission has been requested but declined by the user
- L983 _public enumerator_ `Granted = 2` — Permission has been granted by the user

#### enum `EOnlineSharingCategory`  
`enum class EOnlineSharingCategory : uint32`  
_L990-1022_
- desc: First 16 bits are reading permissions Second 16 bits are writing/publishing permissions
- L992 _public enumerator_ `None = 0x00`
- L994 _public enumerator_ `ReadPosts = 0x01` — Read access to posts on the users feeds
- L996 _public enumerator_ `Friends = 0x02` — Read access for a users friend information, and all data about those friends. e.g. Friends List and Individual Friends Birthday
- L998 _public enumerator_ `Email = 0x04` — Read access to a user's email address
- L1000 _public enumerator_ `Mailbox = 0x08` — Read access to a users mailbox
- L1002 _public enumerator_ `OnlineStatus = 0x10` — Read the current online status of a user
- L1004 _public enumerator_ `ProfileInfo = 0x20` — Read a users profile information, e.g. Users Birthday
- L1006 _public enumerator_ `LocationInfo = 0x40` — Read information about the users locations and location history
- L1008 _public enumerator_ `ReadPermissionMask = 0x0000FFFF`
- L1009 _public enumerator_ `DefaultRead = ProfileInfo | LocationInfo`
- L1012 _public enumerator_ `SubmitPosts = 0x010000` — Permission to post to a users news feed
- L1014 _public enumerator_ `ManageFriends = 0x020000` — Permission to manage a users friends list. Add/Remove contacts
- L1016 _public enumerator_ `AccountAdmin = 0x040000` — Manage a users account settings, such as pages they subscribe to, or which notifications they receive
- L1018 _public enumerator_ `Events = 0x080000` — Manage a users events. This features the capacity to create events as well as respond to events.
- L1020 _public enumerator_ `PublishPermissionMask = 0xFFFF0000`
- L1021 _public enumerator_ `DefaultPublish = None`

#### enum `EOnlineStatusUpdatePrivacy`  
`enum class EOnlineStatusUpdatePrivacy : uint8`  
_L1029-1037_
- desc: Privacy permissions used for Online Status updates
- L1032 _public enumerator_ `OnlyMe` — Post will only be visible to the user alone
- L1034 _public enumerator_ `OnlyFriends` — Post will only be visible to the user and the users friends
- L1036 _public enumerator_ `Everyone` — Post will be visible to everyone

#### class `FOnlinePartyId`  
`class FOnlinePartyId : public IOnlinePlatformData, public TSharedFromThis<FOnlinePartyId>`  
_L1049-1070_
- inherits: `IOnlinePlatformData,TSharedFromThis<FOnlinePartyId>`
- desc: Id of a party instance
- L1053 _protected function_ `FOnlinePartyId()` — Hidden on purpose
- L1058 _protected function_ `FOnlinePartyId(const FOnlinePartyId& Src)` — Hidden on purpose
- L1063 _protected function_ `FOnlinePartyId& operator=(const FOnlinePartyId& Src)` — Hidden on purpose
- L1069 _public prototype_ `virtual ~FOnlinePartyId() = default;`

#### struct `TOnlinePartyIdMapKeyFuncs`  
`template <typename ValueType> struct TOnlinePartyIdMapKeyFuncs : public TDefaultMapKeyFuncs<TSharedRef<const FOnlinePartyId>, ValueType, false>`  
_L1075-1080_
- inherits: `TDefaultMapKeyFuncs<TSharedRef<constFOnlinePartyId>,ValueType,false>`
- L1077 _public function_ `static TSharedRef<const FOnlinePartyId> GetSetKey(TPair<TSharedRef<const FOnlinePartyId>, ValueType> const& Element)`
- L1078 _public function_ `static uint32 GetKeyHash(TSharedRef<const FOnlinePartyId> const& Key)`
- L1079 _public function_ `static bool Matches(TSharedRef<const FOnlinePartyId> const& A, TSharedRef<const FOnlinePartyId> const& B)`

#### class `FOnlinePartyTypeId`  
`class FOnlinePartyTypeId`  
_L1088-1108_
- desc: Id of a party's type
- L1091 _public typedef_ `typedef uint32 TInternalType;`
- L1092 _public function_ `explicit FOnlinePartyTypeId(const TInternalType InValue = 0) : Value(InValue)`
- L1094 _public function_ `bool operator==(const FOnlinePartyTypeId Rhs) const`
- L1095 _public function_ `bool operator!=(const FOnlinePartyTypeId Rhs) const`
- L1097 _public function_ `TInternalType GetValue() const`
- L1102 _protected member_ `TInternalType Value;`

#### class `FOnlineFriendSettingsSourceData`  
`class FOnlineFriendSettingsSourceData`  
_L1112-1131_
- L1116 _public prototype_ `virtual ~FOnlineFriendSettingsSourceData() = default;`
- L1119 _public function_ `FOnlineFriendSettingsSourceData() : bNeverShowAgain(false)` — Constructors
- L1124 _public function_ `explicit FOnlineFriendSettingsSourceData( bool bInNeverShowAgain) : bNeverShowAgain(bInNeverShowAgain)`
- L1130 _public member_ `bool bNeverShowAgain;`

#### Free symbols / members of external scopes

- L10 _prototype_ `extern bool IsUniqueIdLocal(const FUniqueNetId& UniqueId);`
- L11 _macro_ `#define OSS_UNIQUEID_REDACT(UniqueId, x) ( !IsUniqueIdLocal(UniqueId) ? ((x.Len() > 10) ? (x.Left(5) + TEXT("...") + x.Right(5)) : FString(TEXT("<Redacted>"))) : x)`
- L15 _macro_ `#define OSS_UNIQUEID_REDACT(UniqueId, x) (x)`
- L19 _macro_ `#define OSS_REDACT(x) TEXT("<Redacted>")`
- L21 _macro_ `#define OSS_REDACT(x) (x)`
- L24 _macro_ `#define DEDICATED_SERVER_USER_INDEX 0`
- L29 _namespace_ `namespace EOnlineEnvironment`
- L44 _prototype_ `const TCHAR* ToString(EOnlineEnvironment::Type EnvironmentType);` (scope `EOnlineEnvironment`) — @return the stringified version of the enum passed in
- L48 _namespace_ `namespace ELoginStatus`
- L61 _prototype_ `const TCHAR* ToString(ELoginStatus::Type EnumVal);` (scope `ELoginStatus`) — @return the stringified version of the enum passed in
- L65 _namespace_ `namespace EOnlineServerConnectionStatus`
- L96 _prototype_ `const TCHAR* ToString(EOnlineServerConnectionStatus::Type EnumVal);` (scope `EOnlineServerConnectionStatus`) — @return the stringified version of the enum passed in
- L100 _namespace_ `namespace EFeaturePrivilegeLevel`
- L115 _prototype_ `const TCHAR* ToString(EFeaturePrivilegeLevel::Type EnumVal);` (scope `EFeaturePrivilegeLevel`) — @return the stringified version of the enum passed in
- L119 _namespace_ `namespace EOnlineAsyncTaskState`
- L134 _prototype_ `const TCHAR* ToString(EOnlineAsyncTaskState::Type EnumVal);` (scope `EOnlineAsyncTaskState`) — @return the stringified version of the enum passed in
- L138 _namespace_ `namespace EOnlineFriendState`
- L153 _prototype_ `const TCHAR* ToString(EOnlineFriendState::Type EnumVal);` (scope `EOnlineFriendState`) — @return the stringified version of the enum passed in
- L157 _namespace_ `namespace ELeaderboardSort`
- L170 _prototype_ `const TCHAR* ToString(ELeaderboardSort::Type EnumVal);` (scope `ELeaderboardSort`) — @return the stringified version of the enum passed in
- L174 _namespace_ `namespace ELeaderboardFormat`
- L187 _prototype_ `const TCHAR* ToString(ELeaderboardFormat::Type EnumVal);` (scope `ELeaderboardFormat`) — @return the stringified version of the enum passed in
- L191 _namespace_ `namespace ELeaderboardUpdateMethod`
- L202 _prototype_ `const TCHAR* ToString(ELeaderboardUpdateMethod::Type EnumVal);` (scope `ELeaderboardUpdateMethod`) — @return the stringified version of the enum passed in
- L206 _namespace_ `namespace EOnlineSessionState`
- L229 _prototype_ `const TCHAR* ToString(EOnlineSessionState::Type EnumVal);` (scope `EOnlineSessionState`) — @return the stringified version of the enum passed in
- L233 _namespace_ `namespace EOnlineDataAdvertisementType`
- L248 _prototype_ `const TCHAR* ToString(EOnlineDataAdvertisementType::Type EnumVal);` (scope `EOnlineDataAdvertisementType`) — @return the stringified version of the enum passed in
- L252 _namespace_ `namespace EOnlineComparisonOp`
- L268 _prototype_ `const TCHAR* ToString(EOnlineComparisonOp::Type EnumVal);` (scope `EOnlineComparisonOp`) — @return the stringified version of the enum passed in
- L272 _namespace_ `namespace EOnlineCachedResult`
- L284 _prototype_ `const TCHAR* ToString(EOnlineCachedResult::Type EnumVal);` (scope `EOnlineCachedResult`) — @param EnumVal the enum to convert to a string @return the stringified version of the enum passed in
- L300 _prototype_ `const TCHAR* LexToString(EFriendInvitePolicy EnumVal);`
- L301 _prototype_ `void LexFromString(EFriendInvitePolicy& Value, const TCHAR* String);`
- L433 _externvar_ `extern FName NAME_Unset;` — placeholder "type" until we can make FUniqueNetIdString sufficiently abstract
- L435 _typedef_ `using FUniqueNetIdStringRef = TSharedRef<const class FUniqueNetIdString>;`
- L436 _typedef_ `using FUniqueNetIdStringPtr = TSharedPtr<const class FUniqueNetIdString>;`
- L564 _macro_ `#define TEMP_UNIQUENETIDSTRING_SUBCLASS(SUBCLASSNAME, TYPE) \`
- L837 _macro_ `#define USER_ATTR_REALNAME TEXT("realName")` — User attribution constants for GetUserAttribute()
- L838 _macro_ `#define USER_ATTR_DISPLAYNAME TEXT("displayName")`
- L839 _macro_ `#define USER_ATTR_PREFERRED_DISPLAYNAME TEXT("prefDisplayName")`
- L840 _macro_ `#define USER_ATTR_ID TEXT("id")`
- L841 _macro_ `#define USER_ATTR_EMAIL TEXT("email")`
- L842 _macro_ `#define USER_ATTR_ALIAS TEXT("alias")`
- L881 _macro_ `#define AUTH_ATTR_REFRESH_TOKEN TEXT("refresh_token")` — Auth attribution constants for GetAuthAttribute()
- L882 _macro_ `#define AUTH_ATTR_ID_TOKEN TEXT("id_token")`
- L883 _macro_ `#define AUTH_ATTR_AUTHORIZATION_CODE TEXT("authorization_code")`
- L913 _namespace_ `namespace EInviteStatus`
- L934 _prototype_ `const TCHAR* ToString(EInviteStatus::Type EnumVal);` (scope `EInviteStatus`) — @return the stringified version of the enum passed in
- L1024 _prototype_ `ENUM_CLASS_FLAGS(EOnlineSharingCategory);`
- L1026 _prototype_ `const TCHAR* ToString(EOnlineSharingCategory CategoryType);`
- L1039 _prototype_ `const TCHAR* ToString(EOnlineStatusUpdatePrivacy PrivacyType);`
- L1044 _typedef_ `typedef FString FNotificationTransportId;` — unique identifier for notification transports
- L1072 _prototype_ `uint32 GetTypeHash(const FOnlinePartyId& Value);`
- L1083 _typedef_ `template <typename ValueType> using TOnlinePartyIdMap = TMap<TSharedRef<const FOnlinePartyId>, ValueType, FDefaultSetAllocator, TOnlinePartyIdMapKeyFuncs<ValueType>>;`
- L1104 _function_ `friend inline uint32 GetTypeHash(const FOnlinePartyTypeId Id)`
- L1110 _function_ `inline bool IsValid(const FOnlinePartyTypeId Id)`
- L1139 _prototype_ `void ParseOnlineSubsystemConfigPairs(TArrayView<const FString> InEntries, TArray<TPair<FString, FString>>& OutPairs);` — Parse an array of strings in the format (Key=Value) into an array of pairs of those keys and values @param InEntries array of strings in the format (Key=Value) @param OutPairs the split key/value pairs
