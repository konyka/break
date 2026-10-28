# Plugins / OnlineSubsystemGDK

- module root: `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source`
- headers: 89; symbols: 2375
- symbol kinds: class=114, delegate=39, enum=6, enumerator=25, function=233, macro=21, member=702, namespace=14, prototype=1129, struct=16, typedef=73, union=1, variable=2
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, Engine, GDKNetDriver, HTTP, Json, OnlineSubsystemUtils, Sockets, UnrealEd, Voice
- PublicDependencyModuleNames: GDKRuntime, GRDK, OnlineSubsystem, PlayFabParty, XCurl, XSAPI

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKCancelMatchmaking.h` (Private)


#### class `FOnlineAsyncTaskGDKCancelMatchmaking`  
`class FOnlineAsyncTaskGDKCancelMatchmaking : public FOnlineAsyncTaskGDK`  
_L23-45_
- inherits: `FOnlineAsyncTaskGDK`
- L26 _public prototype_ `FOnlineAsyncTaskGDKCancelMatchmaking( class FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InUserContext, FName InSessionName, FOnlineMatchTicketInfoPtr InTicketInfo);`
- L32 _public prototype_ `virtual ~FOnlineAsyncTaskGDKCancelMatchmaking() = default;`
- L34 _public prototype_ `virtual void Initialize() override;`
- L35 _public prototype_ `virtual void ProcessResults() override;`
- L36 _public function_ `virtual FString ToString() const override`
- L37 _public prototype_ `virtual void TriggerDelegates() override;`
- L40 _private member_ `FName SessionName;`
- L41 _private member_ `FGDKContextHandle GDKContext;`
- L43 _private member_ `FOnlineMatchTicketInfoPtr TicketInfo;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKCheckForPackageUpdate.h` (Private)


#### enum `ECheckForPackageUpdateResult`  
`enum class ECheckForPackageUpdateResult : uint8`  
_L9-14_
- L11 _public enumerator_ `NoUpdateAvailable`
- L12 _public enumerator_ `OptionalUpdateAvailable`
- L13 _public enumerator_ `MandatoryUpdateAvailable`

#### class `FOnlineAsyncTaskGDKCheckForPackageUpdate`  
`class FOnlineAsyncTaskGDKCheckForPackageUpdate : public FOnlineAsyncTaskGDK`  
_L42-65_
- inherits: `FOnlineAsyncTaskGDK`
- L46 _public prototype_ `FOnlineAsyncTaskGDKCheckForPackageUpdate( class FOnlineSubsystemGDK* const InGDKSubsystem, FGDKUserHandle InLocalUser, const FOnCheckForPackageUpdateCompleteDelegate& CompletionDelegate);`
- L51 _public prototype_ `virtual ~FOnlineAsyncTaskGDKCheckForPackageUpdate() = default;`
- L53 _public function_ `virtual FString ToString() const override`
- L55 _public prototype_ `virtual void Tick() override;`
- L56 _public prototype_ `virtual void ProcessResults() override;`
- L57 _public prototype_ `virtual void TriggerDelegates() override;`
- L60 _private member_ `FOnCheckForPackageUpdateCompleteDelegate TaskCompletionDelegate;`
- L61 _private member_ `FGDKUserHandle LocalUser;`
- L62 _private member_ `FOnlineError ErrorResult;`
- L63 _private member_ `TOptional<ECheckForPackageUpdateResult> PackageUpdateResult;`
- L64 _private member_ `bool bTaskStarted = false;`

#### Free symbols / members of external scopes

- L16 _function_ `inline const TCHAR* const LexToString(const TOptional<ECheckForPackageUpdateResult> Value)`
- L40 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnCheckForPackageUpdateCompleteDelegate, const FOnlineError& , const TOptional<ECheckForPackageUpdateResult> );` — Delegate for after determining whether the package needs an update.
- L40 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnCheckForPackageUpdateCompleteDelegate, const FOnlineError& , const TOptional<ECheckForPackageUpdateResult> );` — Delegate for after determining whether the package needs an update.

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKClearSessionActivity.h` (Private)


#### class `FOnlineAsyncTaskGDKClearSessionActivity`  
`class FOnlineAsyncTaskGDKClearSessionActivity : public FOnlineAsyncTaskGDK`  
_L13-34_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to clear the current session activity for a user
- L17 _public prototype_ `FOnlineAsyncTaskGDKClearSessionActivity(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InLiveContext, XblMultiplayerSessionReference* InSessionReference);`
- L20 _public prototype_ `virtual ~FOnlineAsyncTaskGDKClearSessionActivity() = default;`
- L23 _public function_ `virtual FString ToString() const override`
- L25 _public prototype_ `virtual void Initialize() override;`
- L26 _public prototype_ `virtual void ProcessResults() override;`
- L28 _public prototype_ `virtual void TriggerDelegates() override;`
- L32 _protected member_ `ANSICHAR ServiceConfigurationId[XBL_SCID_LENGTH];` — Service Configuration ID to clear for this user
- L33 _protected member_ `FGDKContextHandle GDKContext;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKCreateMatchSession.h` (Private)


#### class `FOnlineAsyncTaskGDKCreateMatchSession`  
`class FOnlineAsyncTaskGDKCreateMatchSession : public FOnlineAsyncTaskGDKSessionBase`  
_L15-50_
- inherits: `FOnlineAsyncTaskGDKSessionBase`
- L19 _public prototype_ `FOnlineAsyncTaskGDKCreateMatchSession( FOnlineSubsystemGDK* InLiveSubsystem, const TArray<FUniqueNetIdRef>& InSearchingUserIds, const FName InSessionName, const FOnlineSessionSettings& InSessionSettings, const TSharedRef<FOnlineSessionSearch>& InSearchSettings );` — . Regular Matchmaking should use this constructor
- L27 _public prototype_ `virtual ~FOnlineAsyncTaskGDKCreateMatchSession();`
- L29 _public prototype_ `virtual void Initialize() override;`
- L31 _public function_ `virtual FString ToString() const override`
- L32 _public prototype_ `virtual void Finalize() override;`
- L33 _public prototype_ `virtual void TriggerDelegates() override;`
- L34 _public prototype_ `virtual void ProcessResult(bool bWasSuccessful, FName ResultSessionName);`
- L38 _private member_ `TArray<FUniqueNetIdRef> SearchingUserIds;` — Store array of users
- L40 _private member_ `XblMultiplayerSessionReference* CurrentMatchSessionRef;`
- L42 _private member_ `FGDKUserHandle SearchingUser;`
- L43 _private member_ `TSharedPtr<FInternetAddr> HostAddr;`
- L46 _private member_ `bool bSessionCreated;` — Used to track completion of tasks that add local users to match session
- L47 _private member_ `FThreadSafeCounter NumOtherLocalPlayersToAdd;`
- L49 _private prototype_ `void OnAddLocalPlayerComplete(const FUniqueNetId& PlayerId, EOnJoinSessionCompleteResult::Type Result);`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKCreateSearchHandle.h` (Private)


#### class `FOnlineAsyncTaskGDKCreateSearchHandle`  
`class FOnlineAsyncTaskGDKCreateSearchHandle : public FOnlineAsyncTaskGDK`  
_L18-42_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to clear the current session activity for a user
- L22 _public prototype_ `FOnlineAsyncTaskGDKCreateSearchHandle(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InLiveContext, const XblMultiplayerSessionReference& InSessionReference, const FOnlineSessionSettings& SessionSettings, const FOnCreateSearchHandleCompleteDelegate& InTaskCompletionDelegate);`
- L27 _public prototype_ `virtual ~FOnlineAsyncTaskGDKCreateSearchHandle() = default;`
- L30 _public function_ `virtual FString ToString() const override`
- L32 _public prototype_ `virtual void Initialize() override;`
- L33 _public prototype_ `virtual void ProcessResults() override;`
- L35 _public prototype_ `virtual void TriggerDelegates() override;`
- L38 _protected member_ `FGDKContextHandle GDKContext;`
- L39 _protected member_ `XblMultiplayerSessionReference SessionReference;`
- L40 _protected member_ `FOnlineSessionSettings SessionSettings;`
- L41 _protected member_ `FOnCreateSearchHandleCompleteDelegate TaskCompletionDelegate;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCreateSearchHandleCompleteDelegate, bool);` — Delegate fired when search handle has been created
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCreateSearchHandleCompleteDelegate, bool);` — Delegate fired when search handle has been created

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKCreateSession.h` (Private)


#### class `FOnlineAsyncTaskGDKCreateSession`  
`class FOnlineAsyncTaskGDKCreateSession : public FOnlineAsyncTaskGDKSafeWriteSession`  
_L15-59_
- inherits: `FOnlineAsyncTaskGDKSafeWriteSession`
- desc: Async task for creating an GDK session
- L18 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnGDKCreateSessionComplete, bool , FName );`
- L22 _private member_ `FUniqueNetIdRef UserId;` — The id of the user hosting the session
- L25 _private member_ `bool bSetActivity;` — Whether to set this session as our activity upon completion or not
- L28 _private member_ `bool bWriteSession;` — Whether to write the GDK session to the backend or not
- L30 _private member_ `FOnGDKCreateSessionComplete TaskCompletionDelegate;`
- L42 _public prototype_ `FOnlineAsyncTaskGDKCreateSession( FOnlineSubsystemGDK* const InSubsystem, FGDKContextHandle InGDKContext, const FUniqueNetIdRef InUserId, const FName InSessionName, FGDKMultiplayerSessionHandle InGDKSession, const bool bInWriteSession, const bool bInSetActivity, FOnGDKCreateSessionComplete InTaskCompletionDelegate);` — Constructor @param InSessionInterface The session that created this task @param InUserIndex Index of the user who created this task @param InCreator User who created this task @param InSessionName Name of the session to create
- L53 _public prototype_ `virtual void Initialize();` — FOnlineAsyncItem
- L54 _public function_ `virtual FString ToString() const override`
- L55 _public prototype_ `virtual void Finalize() override;`
- L56 _public prototype_ `virtual void ProcessWriteSessionResult() override;`
- L57 _public prototype_ `virtual void TriggerDelegates() override;`
- L58 _public function_ `virtual bool UpdateSession(FGDKMultiplayerSessionHandle Session) override`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGDKCreateSessionComplete, bool , FName );`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKDestroySession.h` (Private)


#### class `FOnlineAsyncTaskGDKDestroySessionBase`  
`class FOnlineAsyncTaskGDKDestroySessionBase : public FOnlineAsyncTaskGDKSafeWriteSession`  
_L13-53_
- inherits: `FOnlineAsyncTaskGDKSafeWriteSession`
- desc: Async task used to have every local player Leave() the Live session.
- L25 _public function_ `FOnlineAsyncTaskGDKDestroySessionBase( FOnlineSubsystemGDK* const InSubsystem, const FString& AsyncTaskName, FGDKContextHandle InContext, const FName InSessionName, FGDKMultiplayerSessionHandle InGDKSession ) : FOnlineAsyncTaskGDKSafeWriteSession(InSubsystem, AsyncTaskName, InContext, InSessionName, InGDKSession)` — This constructor takes the GDK Session directly and is safe to call in non-game threads. @param InSubsystem the owning Live online subsystem @param InContext the Live context of the user who's updating the session @param InSessionName the name of the session to destroy @param InGDKSession the GDK session we're writing to
- L37 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L40 _public prototype_ `static void RemoveAndCleanupSession( FOnlineSubsystemGDK* const Subsystem, const FName SessionName);` — Triggers the appropriate delegate based on DelegateType
- L47 _private prototype_ `virtual bool UpdateSession(FGDKMultiplayerSessionHandle Session);` — FOnlineAsyncTaskLiveSafeWriteSession
- L52 _protected member_ `bool bLeaveSuccessful = false;` — Whether the session leave command was processed successfully or not in UpdateSession.

#### class `FOnlineAsyncTaskGDKDestroyMatchmakingSession`  
`class FOnlineAsyncTaskGDKDestroyMatchmakingSession : public FOnlineAsyncTaskGDKDestroySessionBase`  
_L55-81_
- inherits: `FOnlineAsyncTaskGDKDestroySessionBase`
- L67 _public function_ `FOnlineAsyncTaskGDKDestroyMatchmakingSession( FOnlineSubsystemGDK* const InSubsystem, FGDKContextHandle InContext, const FName InSessionName, FGDKMultiplayerSessionHandle InGDKSession ) : FOnlineAsyncTaskGDKDestroySessionBase(InSubsystem, TEXT("FOnlineAsyncTaskGDKDestroyMatchmakingSession"), InContext, InSessionName, InGDKSession)` — This constructor takes the GDK Session directly and is safe to call in non-game threads. @param InSubsystem the owning GDK online subsystem @param InContext the Live context of the user who's updating the session @param InSessionName the name of the session to destroy @param InGDKSession the GDK session we're writing to
- L78 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L79 _public prototype_ `virtual void Finalize() override;`

#### class `FOnlineAsyncTaskGDKDestroySession`  
`class FOnlineAsyncTaskGDKDestroySession : public FOnlineAsyncTaskGDKDestroySessionBase`  
_L83-114_
- inherits: `FOnlineAsyncTaskGDKDestroySessionBase`
- L96 _public function_ `FOnlineAsyncTaskGDKDestroySession( FOnlineSubsystemGDK* const InSubsystem, FGDKContextHandle InContext, const FName InSessionName, FGDKMultiplayerSessionHandle InGDKSession, const FOnDestroySessionCompleteDelegate& InCompletionDelegate ) : FOnlineAsyncTaskGDKDestroySessionBase(InSubsystem, TEXT("FOnlineAsyncTaskGDKDestroySession"), InContext, InSessionName, InGDKSession) , CompletionDelegate(InCompletionDelegate)` — This constructor takes the GDK Session directly and is safe to call in non-game threads. @param InSubsystem the owning GDK online subsystem @param InContext the GDK context of the user who's updating the session @param InSessionName the name of the session to update @param InGDKSession the GDK session we're writing to @param InCompletionDelegate the delegate to call once we're finished
- L109 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L110 _public prototype_ `virtual void Finalize() override;`
- L113 _private member_ `FOnDestroySessionCompleteDelegate CompletionDelegate;`

#### Free symbols / members of external scopes

- L116 _prototype_ `void CreateDestroyMatchmakingCompleteTask(FName SessionName, FGDKMultiplayerSessionHandle Session, FOnlineSubsystemGDK* Subsystem, bool bWasSuccessful);`
- L121 _prototype_ `void CreateDestroyTask(FName SessionName, FGDKMultiplayerSessionHandle Session, FOnlineSubsystemGDK* Subsystem, bool bWasSuccessful, const FOnDestroySessionCompleteDelegate& CompletionDelegate);`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKFindSessionById.h` (Private)


#### class `FOnlineAsyncTaskGDKFindSessionById`  
`class FOnlineAsyncTaskGDKFindSessionById : public FOnlineAsyncTaskGDK`  
_L15-64_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to find the session for a session id
- L19 _public prototype_ `FOnlineAsyncTaskGDKFindSessionById(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InGDKContext, const int32 InLocalUserNum, FString&& InSessionIdString, const FOnSingleSessionResultCompleteDelegate& InDelegate);`
- L25 _public prototype_ `FOnlineAsyncTaskGDKFindSessionById(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InGDKContext, const int32 InLocalUserNum, const XblMultiplayerSessionReference* InSessionReference, const FOnSingleSessionResultCompleteDelegate& InDelegate);`
- L31 _public prototype_ `FOnlineAsyncTaskGDKFindSessionById(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InGDKContext, const int32 InLocalUserNum, XblMultiplayerInviteHandle InInviteHandle, const FOnSingleSessionResultCompleteDelegate& InDelegate);`
- L37 _public prototype_ `FOnlineAsyncTaskGDKFindSessionById(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InGDKContext, const int32 InLocalUserNum, const char* InSessionHandleId, const FOnSingleSessionResultCompleteDelegate& InDelegate);`
- L43 _public prototype_ `virtual ~FOnlineAsyncTaskGDKFindSessionById() = default;`
- L46 _public function_ `virtual FString ToString() const override`
- L48 _public prototype_ `virtual void Initialize() override;`
- L49 _public prototype_ `virtual void ProcessResults() override;`
- L51 _public prototype_ `virtual void TriggerDelegates();`
- L54 _protected member_ `TArray<FUniqueNetIdRef> UsersToQuery;`
- L55 _protected member_ `int32 LocalUserNum;`
- L56 _protected member_ `FString SessionIdString;`
- L57 _protected member_ `FOnSingleSessionResultCompleteDelegate Delegate;`
- L58 _protected member_ `FOnlineError OnlineError;`
- L59 _protected member_ `FOnlineSessionSearchResult SearchResult;`
- L60 _protected member_ `FGDKContextHandle GDKContext;`
- L61 _protected member_ `XblMultiplayerSessionReference SessionReference;`
- L62 _protected member_ `XblMultiplayerInviteHandle InviteHandle;`
- L63 _protected member_ `bool bFindByHandle;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKFindSessionsBySearchHandle.h` (Private)


#### class `FOnlineAsyncTaskGDKFindSessionsBySearchHandle`  
`class FOnlineAsyncTaskGDKFindSessionsBySearchHandle : public FOnlineAsyncTaskGDK`  
_L13-46_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async item used to marshal search results from the system callback thread to the game thread.
- L17 _private member_ `TSharedPtr<FOnlineSessionSearch> SearchSettings;` — Pointer to the settings used for this search.
- L20 _private member_ `TArray<XblMultiplayerSessionHandle> SearchResults;` — All the results returned from the MPSD.
- L23 _private member_ `TArray<XblUserProfile*> Profiles;` — Parallel vector of profiles of the host of each session, used to get the GameDisplayName
- L26 _private member_ `FOnlineSessionGDK* SessionInterface;` — The session that created this task
- L28 _private member_ `FGDKContextHandle GDKContext;`
- L30 _private member_ `uint64 NumExpectedResults;`
- L33 _public prototype_ `FOnlineAsyncTaskGDKFindSessionsBySearchHandle( FOnlineSubsystemGDK* InSubsystemGDK, FOnlineSessionGDK* InSessionInterface, FGDKContextHandle GDKContext, TSharedPtr<FOnlineSessionSearch> InSearchSettings);`
- L40 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L41 _public prototype_ `virtual void Initialize() override;`
- L42 _public prototype_ `virtual void ProcessResults() override;`
- L43 _public prototype_ `virtual void Finalize() override;`
- L44 _public prototype_ `virtual void TriggerDelegates() override;`
- L45 _public prototype_ `void OnGetSingleSessionComplete(int32 LocalUserNum, bool bSucceeded, const FOnlineSessionSearchResult& SearchResult);`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKGameSessionReady.h` (Private)


#### class `FOnlineAsyncTaskGDKGameSessionReady`  
`class FOnlineAsyncTaskGDKGameSessionReady : public FOnlineAsyncTaskGDK`  
_L15-39_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to connect to users in a session after matchmaking and initialization/QoS is complete.
- L18 _public prototype_ `FOnlineAsyncTaskGDKGameSessionReady( FOnlineSubsystemGDK* InSubsystem, FGDKContextHandle InContext, FName InSessionName, const XblMultiplayerSessionReference* InGameSessionRef);`
- L24 _public prototype_ `virtual void Initialize() override;`
- L25 _public prototype_ `virtual void ProcessResults() override;`
- L26 _public function_ `virtual FString ToString() const override`
- L27 _public prototype_ `virtual void Finalize() override;`
- L28 _public prototype_ `virtual void TriggerDelegates() override;`
- L31 _private member_ `FGDKContextHandle LiveContext;`
- L32 _private member_ `FName SessionName;`
- L33 _private member_ `const XblMultiplayerSessionReference* GameSessionRef;`
- L34 _private member_ `FGDKMultiplayerSessionHandle GDKSession;`
- L35 _private member_ `FGDKContextHandle GDKContext;`
- L37 _private member_ `TSharedPtr<FInternetAddr> HostAddr;`
- L38 _private member_ `bool bWaitAndTryAgain = false;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKGetActivitiesForUsers.h` (Private)


#### class `FOnlineAsyncTaskGDKGetActivitiesForUsers`  
`class FOnlineAsyncTaskGDKGetActivitiesForUsers : public FOnlineAsyncTaskGDK`  
_L14-44_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to write achievements
- L18 _public prototype_ `FOnlineAsyncTaskGDKGetActivitiesForUsers( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, const TArray<uint64>& InUserArray, const FOnGetActivitiesForUsersCompleteDelegate& InTaskCompletionDelegate );`
- L25 _public prototype_ `virtual ~FOnlineAsyncTaskGDKGetActivitiesForUsers() = default;`
- L28 _public function_ `virtual FString ToString() const override`
- L31 _public prototype_ `virtual void Initialize() override;` — Starts in Game Thread
- L33 _public prototype_ `virtual void ProcessResults() override;` — Process in Online Thread
- L36 _public prototype_ `virtual void TriggerDelegates() override;` — Move results and trigger delegates in Game Thread
- L39 _protected member_ `FGDKContextHandle GDKContext;`
- L40 _protected member_ `const FOnGetActivitiesForUsersCompleteDelegate TaskCompletionDelegate;`
- L41 _protected member_ `const FString AchievementIdString;`
- L42 _protected member_ `const TArray<uint64> UserArray;`
- L43 _protected member_ `TArray<XblMultiplayerActivityDetails> ActivityDetails;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKGetLeaderboard.h` (Private)


#### class `FOnlineAsyncTaskGDKGetLeaderboard`  
`class FOnlineAsyncTaskGDKGetLeaderboard : public FOnlineAsyncTaskGDK`  
_L17-93_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to retrieve a single user's leaderboard from Live
- L28 _public prototype_ `FOnlineAsyncTaskGDKGetLeaderboard( FOnlineSubsystemGDK* InGDKSubsystem,` — Constructor @param InGDKSubsystem - The GDKOnlineSubsystem used to retrieve the leaderboards interface @param InResults - The leaderboard data returned from Live @param InReadObject - The storage location for the returned leaderboard data @param InFireDelegates - Whether or not to fire the OnLeaderboardReadComplete delegate
- L44 _public prototype_ `void Initialize();` — Get a human readable description of task
- L45 _public prototype_ `virtual void ProcessResults() override;`
- L46 _public function_ `virtual FString ToString() const override`
- L47 _public prototype_ `virtual void Finalize() override;`
- L48 _public prototype_ `virtual void TriggerDelegates() override;`
- L53 _private member_ `XblLeaderboardResult* Results;` — Pointer to the leaderboard returned by the async request
- L55 _private member_ `const FGDKContextHandle GDKContext;`
- L58 _private member_ `FOnlineLeaderboardReadPtr ReadObject;` — Handle to the read object where the data will be stored
- L60 _private member_ `const FString LeaderboardName;`
- L61 _private member_ `uint64 PlayerId;`
- L62 _private member_ `XblSocialGroupType SocialGroupType;`
- L65 _private member_ `bool bFireDelegates;` — Whether or not to fire the OnLeaderboardReadCompleteDelegates on completion
- L67 _private member_ `bool bSkipToUser;`
- L68 _private member_ `FString StatName;`
- L71 _private member_ `TArray<uint8> BufferArray;` — Holds raw result info from leaderboard query
- L73 _private member_ `XblLeaderboardResult* LeaderboardResult = nullptr;` — Points to BufferArray's memory after successfully completing leaderboard query
- L75 _private member_ `FOnGetLeaderboardCompleteDelegate Delegate;`
- L84 _private prototype_ `FVariantData ConvertLeaderboardRowDataToRequestedType(const TCHAR* RowData, XblLeaderboardStatType FromType, EOnlineKeyValuePairDataType::Type ToType);` — Converts the LeaderboardResult string data to the type requested in the LeaderboardRead metadata @param RowData - The string containing the value to be parsed @param FromType - The value type of the column in the leaderboard result. This is compared to the ToType to verify the conversion is appropriate. @param ToType - The type of data to parse from the string and return @return An FVariantData containing the requested datatype parsed from the RowData string
- L92 _private prototype_ `void ReportTypeMismatchWarning(XblLeaderboardStatType FromType, EOnlineKeyValuePairDataType::Type ToType);` — Reports a warning that the FromType and the ToType are mismatched and the conversion from one to the other may not be accurate @param FromType - The GDK Leaderboard PropertyType that is being converted from @param ToType - The EOnlineKeyValuePairDataType that is being converted to

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKGetLeaderboardForUsers.h` (Private)


#### class `FOnlineAsyncTaskGDKGetLeaderboardForUsers`  
`class FOnlineAsyncTaskGDKGetLeaderboardForUsers : public FOnlineAsyncTaskBasic<FOnlineSubsystemGDK>`  
_L12-40_
- inherits: `FOnlineAsyncTaskBasic<FOnlineSubsystemGDK>`
- desc: Async task to retrieve a leaderboard containing a list of users from Live
- L22 _public prototype_ `FOnlineAsyncTaskGDKGetLeaderboardForUsers( FOnlineSubsystemGDK* InGDKSubsystem, TArray<FOnlineLeaderboardReadRef> InLeaderboardReads, const FOnlineLeaderboardReadRef& InReadObject);` — Constructor @param InGDKSubsystem - The GDKOnlineSubsystem used to retrieve the leaderboards interface @param InLeaderboardReads - The array of LeaderboardReads to consolidate into the ReadObject @param InReadObject - The storage location for the returned leaderboard data
- L30 _public function_ `virtual FString ToString() const` — Get a human readable description of task
- L31 _public prototype_ `virtual void Tick();`
- L32 _public prototype_ `virtual void Finalize();`
- L33 _public prototype_ `virtual void TriggerDelegates();`
- L37 _private member_ `TArray<FOnlineLeaderboardReadRef> LeaderboardReads;` — List of ReadObjects to be populated by single user leaderboard requests
- L39 _private member_ `FOnlineLeaderboardReadPtr ReadObject;` — Handle to the read object where the data will be stored

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKGetOverallReputation.h` (Private)


#### class `FOnlineAsyncTaskGDKGetOverallReputation`  
`class FOnlineAsyncTaskGDKGetOverallReputation : public FOnlineAsyncTaskGDK`  
_L16-59_
- inherits: `FOnlineAsyncTaskGDK`
- L21 _public prototype_ `FOnlineAsyncTaskGDKGetOverallReputation(FOnlineSubsystemGDK* const InGDKSubsystem , FGDKContextHandle InGDKContext , TArray<FUniqueNetIdGDKRef>&& InUserIDs , const FOnGetOverallReputationCompleteDelegate& InCompletionDelegate );`
- L27 _public prototype_ `FOnlineAsyncTaskGDKGetOverallReputation(FOnlineSubsystemGDK* const InGDKSubsystem , FGDKContextHandle InLiveContext , const FUniqueNetIdGDKRef& InUserID , const FOnGetOverallReputationCompleteDelegate& InCompletionDelegate );`
- L33 _public prototype_ `virtual FString ToString() const override;`
- L41 _private prototype_ `virtual void Initialize() override;` — Handles creating an AsyncOperation.  The task should be created and returned in this method @Return The AsyncOperation to run, or nullptr if there was a failure
- L49 _private prototype_ `virtual void ProcessResults() override;` — Handles processing of an async result.  Any processed data should be stored on the task until Finalize is called on the Game thread. @Param CompletedTask The finished task to call get() on @Return Whether or not our task was successful and is stored in bWasSuccessful
- L51 _private prototype_ `virtual void TriggerDelegates() override;`
- L54 _private member_ `FGDKContextHandle GDKContext;`
- L55 _private member_ `FOnGetOverallReputationCompleteDelegate CompletionDelegate;`
- L57 _private member_ `TArray<FUniqueNetIdGDKRef > UserIds;`
- L58 _private member_ `UserReputationMap UsersWithBadReputations;`

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef TUniqueNetIdMap<bool> UserReputationMap;`
- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetOverallReputationCompleteDelegate, const UserReputationMap& );`
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FOnGetOverallReputationCompleteDelegate, const UserReputationMap& );`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKGetReadLeaderboards.h` (Private)


#### class `FOnlineAsyncTaskGDKGetLeaderboardForUsers`  
`class FOnlineAsyncTaskGDKGetLeaderboardForUsers : public FOnlineAsyncTaskBasic<FOnlineSubsystemGDK>`  
_L12-40_
- inherits: `FOnlineAsyncTaskBasic<FOnlineSubsystemGDK>`
- desc: Async task to retrieve a leaderboard containing a list of users from Live
- L22 _public prototype_ `FOnlineAsyncTaskGDKGetLeaderboardForUsers( FOnlineSubsystemGDK* InGDKSubsystem, TArray<FOnlineLeaderboardReadRef> InLeaderboardReads, const FOnlineLeaderboardReadRef& InReadObject);` — Constructor @param InGDKSubsystem - The GDKOnlineSubsystem used to retrieve the leaderboards interface @param InLeaderboardReads - The array of LeaderboardReads to consolidate into the ReadObject @param InReadObject - The storage location for the returned leaderboard data
- L30 _public function_ `virtual FString ToString() const` — Get a human readable description of task
- L31 _public prototype_ `virtual void Tick();`
- L32 _public prototype_ `virtual void Finalize();`
- L33 _public prototype_ `virtual void TriggerDelegates();`
- L37 _private member_ `TArray<FOnlineLeaderboardReadRef> LeaderboardReads;` — List of ReadObjects to be populated by single user leaderboard requests
- L39 _private member_ `FOnlineLeaderboardReadPtr ReadObject;` — Handle to the read object where the data will be stored

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKGetUserCollectionsId.h` (Private)


#### class `FOnlineAsyncTaskGetUserCollectionsId`  
`class FOnlineAsyncTaskGetUserCollectionsId : public FOnlineAsyncTaskGDK`  
_L19-41_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async item used to marshal user collections id results from the GDK system thread to the game thread.
- L22 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnCompleteDelegate, const FString& , const FOnlineError& );`
- L24 _public prototype_ `FOnlineAsyncTaskGetUserCollectionsId(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InGDKContext, const FString& InServiceTicket, const FString& InPublisherUserId, const FOnCompleteDelegate& InDelegate);`
- L25 _public prototype_ `virtual ~FOnlineAsyncTaskGetUserCollectionsId();`
- L27 _public prototype_ `virtual void Tick() override;`
- L28 _public prototype_ `virtual void ProcessResults() override;`
- L30 _public function_ `virtual FString ToString() const override`
- L31 _public prototype_ `virtual void Finalize() override;`
- L32 _public prototype_ `virtual void TriggerDelegates() override;`
- L34 _protected member_ `FString ServiceTicket;`
- L35 _protected member_ `FString PublisherUserId;`
- L36 _protected member_ `FString CollectionsId;`
- L37 _protected member_ `FOnlineError ErrorResponse;`
- L38 _protected member_ `FOnCompleteDelegate Delegate;`
- L39 _protected member_ `FGDKContextHandle GDKContext;`
- L40 _protected member_ `bool bTaskStarted = false;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnCompleteDelegate, const FString& , const FOnlineError& );`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKGetUserPrivilege.h` (Private)


#### class `FOnlineAsyncTaskGDKGetUserPrivilege`  
`class FOnlineAsyncTaskGDKGetUserPrivilege : public FOnlineAsyncTaskGDK`  
_L14-55_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to write achievements
- L18 _public prototype_ `FOnlineAsyncTaskGDKGetUserPrivilege( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, const FUniqueNetIdGDKRef& InUserId, EUserPrivileges::Type InPrivilege, const IOnlineIdentity::FOnGetUserPrivilegeCompleteDelegate& InTaskCompleteionDelegate, EShowPrivilegeResolveUI InShowResolveUI);`
- L26 _public prototype_ `virtual ~FOnlineAsyncTaskGDKGetUserPrivilege() = default;`
- L29 _public function_ `virtual FString ToString() const override`
- L32 _public prototype_ `virtual void Initialize() override;` — Starts in Game Thread
- L34 _public prototype_ `void InitializeInternal();`
- L37 _public prototype_ `void ResolvePrivilegeWithUIComplete(bool bWasSuccessful);`
- L38 _public prototype_ `void CheckForGDKPackageUpdate();`
- L39 _public prototype_ `void PatchCheckCompletion(const FOnlineError& ErrorResult, const TOptional<ECheckForPackageUpdateResult> OptionalPatchCheckResult);`
- L42 _public prototype_ `virtual void TriggerDelegates() override;` — Move results and trigger delegates in Game Thread
- L45 _protected member_ `FGDKContextHandle GDKContext;`
- L46 _protected member_ `const IOnlineIdentity::FOnGetUserPrivilegeCompleteDelegate TaskCompletionDelegate;`
- L47 _protected member_ `FGDKUserHandle GDKUser;`
- L48 _protected member_ `const FUniqueNetIdGDKRef GDKUserId;`
- L49 _protected member_ `EUserPrivileges::Type Privilege;`
- L50 _protected member_ `IOnlineIdentity::EPrivilegeResults PrivilegeResult = IOnlineIdentity::EPrivilegeResults::GenericFailure;`
- L51 _protected member_ `bool bHasPrivilege = false;`
- L52 _protected member_ `XUserPrivilegeDenyReason DenyReason = XUserPrivilegeDenyReason::None;`
- L53 _protected member_ `XUserPrivilege KnownPrivilege = XUserPrivilege::Sessions;`
- L54 _protected member_ `EShowPrivilegeResolveUI ShowResolveUI;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKGetUserProfile.h` (Private)


#### class `FOnlineAsyncTaskGDKGetUserProfile`  
`class FOnlineAsyncTaskGDKGetUserProfile : public FOnlineAsyncTaskGDK`  
_L14-47_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to get user profile
- L21 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnGetUserProfileCompleteDelegate, bool, const XblUserProfile&);` — Delegate fired when GetUserProfile Task is complete.
- L23 _public prototype_ `FOnlineAsyncTaskGDKGetUserProfile( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, uint64 InUserId, const FOnGetUserProfileCompleteDelegate& InTaskCompletionDelegate);`
- L29 _public prototype_ `virtual ~FOnlineAsyncTaskGDKGetUserProfile() = default;`
- L32 _public function_ `virtual FString ToString() const override`
- L35 _public prototype_ `virtual void Initialize() override;` — Starts in Game Thread
- L37 _public prototype_ `virtual void ProcessResults() override;`
- L40 _public prototype_ `virtual void TriggerDelegates() override;` — Move results and trigger delegates in Game Thread
- L43 _protected member_ `FGDKContextHandle GDKContext;`
- L44 _protected member_ `const FOnGetUserProfileCompleteDelegate TaskCompletionDelegate;`
- L45 _protected member_ `uint64 GDKUserId;`
- L46 _protected member_ `XblUserProfile Profile;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGetUserProfileCompleteDelegate, bool, const XblUserProfile&);` — Delegate fired when GetUserProfile Task is complete.

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKGetUserPurchaseId.h` (Private)


#### class `FOnlineAsyncTaskGetUserPurchaseId`  
`class FOnlineAsyncTaskGetUserPurchaseId : public FOnlineAsyncTaskGDK`  
_L19-41_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async item used to marshal user purchase id results from the GDK system thread to the game thread.
- L22 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnCompleteDelegate, const FString& , const FOnlineError& );`
- L24 _public prototype_ `FOnlineAsyncTaskGetUserPurchaseId(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InGDKContext, const FString& InServiceTicket, const FString& InPublisherUserId, const FOnCompleteDelegate& InDelegate);`
- L25 _public prototype_ `virtual ~FOnlineAsyncTaskGetUserPurchaseId();`
- L27 _public prototype_ `virtual void Tick() override;`
- L28 _public prototype_ `virtual void ProcessResults() override;`
- L30 _public function_ `virtual FString ToString() const override`
- L31 _public prototype_ `virtual void Finalize() override;`
- L32 _public prototype_ `virtual void TriggerDelegates() override;`
- L34 _protected member_ `FString ServiceTicket;`
- L35 _protected member_ `FString PublisherUserId;`
- L36 _protected member_ `FString PurchaseId;`
- L37 _protected member_ `FOnlineError ErrorResponse;`
- L38 _protected member_ `FOnCompleteDelegate Delegate;`
- L39 _protected member_ `FGDKContextHandle GDKContext;`
- L40 _protected member_ `bool bTaskStarted = false;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnCompleteDelegate, const FString& , const FOnlineError& );`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKGetXSTSToken.h` (Private)


#### class `FOnlineAsyncTaskGDKGetXSTSToken`  
`class FOnlineAsyncTaskGDKGetXSTSToken : public FOnlineAsyncTaskGDK`  
_L14-45_
- inherits: `FOnlineAsyncTaskGDK`
- L18 _public prototype_ `FOnlineAsyncTaskGDKGetXSTSToken( class FOnlineSubsystemGDK* const InGDKSubsystem, FGDKUserHandle InLocalUser, int32 InLocalUserNum, const FString& InEndPointURL, const FOnXSTSTokenCompleteDelegate& CompletionDelegate);`
- L25 _public prototype_ `virtual ~FOnlineAsyncTaskGDKGetXSTSToken() = default;`
- L27 _public function_ `virtual FString ToString() const override`
- L29 _public prototype_ `virtual void Initialize() override;`
- L30 _public prototype_ `virtual void ProcessResults() override;`
- L32 _public prototype_ `virtual void Finalize() override;`
- L33 _public prototype_ `virtual void TriggerDelegates() override;`
- L36 _private member_ `int32 LocalUserNum;`
- L37 _private member_ `FGDKUserHandle LocalUser;`
- L38 _private member_ `FString RequestEndPointURL;`
- L39 _private member_ `FOnXSTSTokenCompleteDelegate TaskCompletionDelegate;`
- L41 _private member_ `FUniqueNetIdGDKPtr GDKUserId;`
- L42 _private member_ `FString ResultToken;`
- L43 _private member_ `FString ResultSignature;`
- L44 _private member_ `TArray<uint8> BufferArray;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_FiveParams(FOnXSTSTokenCompleteDelegate, const FOnlineError& , int32 , const FUniqueNetIdGDKRef& , const FString& , const FString& );` — Delegate for after receiving an XSTS auth token.
- L12 _prototype_ `DECLARE_DELEGATE_FiveParams(FOnXSTSTokenCompleteDelegate, const FOnlineError& , int32 , const FUniqueNetIdGDKRef& , const FString& , const FString& );` — Delegate for after receiving an XSTS auth token.

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKJoinSession.h` (Private)


#### class `FOnlineAsyncTaskGDKJoinSession`  
`class FOnlineAsyncTaskGDKJoinSession : public FOnlineAsyncTaskBasic<FOnlineSubsystemGDK>`  
_L14-140_
- inherits: `FOnlineAsyncTaskBasic<FOnlineSubsystemGDK>`
- L30 _public prototype_ `FOnlineAsyncTaskGDKJoinSession( FOnlineSubsystemGDK* const InSubsystem, FGDKContextHandle InContext, FGDKMultiplayerSessionHandle InSession, FNamedOnlineSessionRef InNamedSession, const int32 InMaxRetryCount, const bool bInSessionIsMatchmakingResult, const bool bInSetActivity, const TOptional<FString>& InSessionInviteHandle);` — This constructor takes the GDK Session directly and is safe to call in non-game threads. @param InSubsystem the owning GDK online subsystem @param InContext the GDK context of the user who's updating the session @param InSession the session we're writing to @param InNamedSession The named session to join @param InMaxRetryCount number of times to retry the session write @param bInSessionIsMatchmakingResult Is this a matchmaking result? @param bInSetActivity Should we set this as our presence session? @param InSessionInviteHandle Secret session key in case of invites to private parties
- L55 _public prototype_ `FOnlineAsyncTaskGDKJoinSession( FOnlineSubsystemGDK* const InSubsystem, FGDKContextHandle InContext, const XblMultiplayerSessionReference* InGDKSessionReference, FNamedOnlineSessionRef InNamedSession, const int32 InMaxRetryCount, const bool bInSessionIsMatchmakingResult, const bool bInSetActivity, const TOptional<FString>& InSessionInviteHandle);` — This constructor takes a GDK Session Reference and is safe to call in non-game threads.  We will download the current session object from the provided reference. @param InSubsystem the owning GDK online subsystem @param InContext the GDK context of the user who's updating the session @param InSessionReference the session reference we need to read to get the session we need to join @param InNamedSession The named session to join @param InMaxRetryCount number of times to retry the session write @param bInSessionIsMatchmakingResult Is this a matchmaking result? @param bInSetActivity Should we set this as our presence session? @param InSessionInviteHandle Secret session key in case of invites to private parties
- L66 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L72 _public prototype_ `virtual void Initialize() override;`
- L73 _public prototype_ `virtual void Finalize() override;`
- L74 _public prototype_ `virtual void TriggerDelegates() override;`
- L76 _public prototype_ `void ProcessGetSessionResultCommon(HRESULT Result);`
- L77 _public prototype_ `void ProcessGetSessionResult();`
- L78 _public prototype_ `void ProcessGetSessionByHandleResult();`
- L79 _public prototype_ `void ProcessJoinSessionResultCommon(FGDKMultiplayerSessionHandle NewSessionHandle, HRESULT Result);`
- L80 _public prototype_ `void ProcessJoinSessionByHandleResult();`
- L82 _private prototype_ `void OnSuccess();`
- L83 _private prototype_ `void OnFailed(EOnJoinSessionCompleteResult::Type Result);`
- L84 _private prototype_ `void Retry();`
- L85 _private prototype_ `void TryJoinSession();`
- L86 _private prototype_ `void TryJoinSessionFromMatchmaking(const TArray<const XblMultiplayerSessionMember*>& LocalMembers);`
- L87 _private prototype_ `void TryJoinSessionFromDedicated();`
- L88 _private prototype_ `void TryJoinSessionFromPeer(const XblMultiplayerSessionMember* Host);`
- L91 _private prototype_ `void OnAddLocalPlayerComplete(const FUniqueNetId& PlayerId, EOnJoinSessionCompleteResult::Type Result);` — Callback when other local players are added to session in matchmaking case
- L94 _private member_ `FNamedOnlineSessionRef NamedSession;` — Named session backing this object
- L97 _private member_ `FGDKMultiplayerSessionHandle GDKSession;` — GDK session object we're writing to to join (may be null)
- L99 _private member_ `const XblMultiplayerSessionReference* GDKSessionReference;` — GDK session reference object used to obtain an GDKSession (MUST not be null)
- L103 _private member_ `XblMultiplayerSessionReference GDKSessionReferenceInternal;` — GDK session reference object used to obtain an GDKSession. Internal copy made when joining via transient reference
- L106 _private member_ `FGDKContextHandle GDKContext;` — GDK context for the user initiating the join of this session
- L109 _private member_ `EOnJoinSessionCompleteResult::Type JoinResult;` — The result of this join
- L112 _private member_ `const int32 MaxRetryCount;` — Maximum amount of times to try writing upon write-conflicts
- L115 _private member_ `int32 TotalRetryAttempts;` — Maximum amount of times to attempt our read/write flow
- L118 _private member_ `int32 TotalSessionWrites;` — Total amount of times we sent a write request for this session
- L121 _private member_ `int32 TotalSessionReads;` — Total amount of times we downloaded a new copy of the session document
- L124 _private member_ `const bool bSessionIsMatchmakingResult;` — Are we joining an GDK matchmaking session?
- L127 _private member_ `FThreadSafeCounter OtherLocalPlayersToAdd;` — Count of other local-players are still queued to be added when we join the session (splitscreen cases)
- L130 _private member_ `const bool bSetActivity;` — Should we set this session as our presence-advertised session?
- L133 _private member_ `const TOptional<FString> SessionInviteHandle;` — Session invite handle to be used if we are joining a private session by invite
- L136 _private member_ `XAsyncBlock AsyncBlock;` — Struct that GDK uses to manage async tasks
- L139 _private member_ `TArray<const XblMultiplayerSessionMember*> LocalMembers;` — Array of multiplayer session members associated with local users on this device

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKMeasureAndUploadQos.h` (Private)


#### class `FOnlineAsyncTaskGDKMeasureAndUploadQos`  
`class FOnlineAsyncTaskGDKMeasureAndUploadQos : public FOnlineAsyncTaskGDK`  
_L17-39_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task used to measure QoS to peers during session initialization, then upload the results to the session document.
- L20 _public prototype_ `FOnlineAsyncTaskGDKMeasureAndUploadQos( FOnlineSubsystemGDK* InSubsystem, FGDKContextHandle InContext, FNamedOnlineSessionRef InNamedSession, FGDKMultiplayerSessionHandle InSession, int32 RetryCount, int32 InQosTimeoutMs, int32 InQosProbeCount);`
- L29 _public prototype_ `virtual void Initialize() override;`
- L30 _public function_ `virtual FString ToString() const override`
- L31 _public prototype_ `virtual void TriggerDelegates() override;`
- L32 _public prototype_ `virtual void Tick() override;`
- L36 _private member_ `FNamedOnlineSessionRef NamedSession;`
- L37 _private member_ `FGDKMultiplayerSessionHandle GDKSession;`
- L38 _private member_ `FGDKContextHandle GDKContext;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKMpaDeleteActivity.h` (Private)


#### class `FOnlineAsyncTaskGDKMpaDeleteActivity`  
`class FOnlineAsyncTaskGDKMpaDeleteActivity : public FOnlineAsyncTaskGDK`  
_L10-33_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to delete MPA activity
- L14 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnComplete, bool );`
- L16 _public prototype_ `FOnlineAsyncTaskGDKMpaDeleteActivity( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, const FUniqueNetIdGDKRef& InUserIdGDK, FOnComplete InTaskCompletionDelegate );`
- L23 _public function_ `virtual FString ToString() const override`
- L25 _public prototype_ `virtual void Initialize() override;`
- L26 _public prototype_ `virtual void ProcessResults() override;`
- L27 _public prototype_ `virtual void TriggerDelegates() override;`
- L30 _protected member_ `FGDKContextHandle GDKContext;`
- L31 _protected member_ `FUniqueNetIdGDKPtr UserIdGDK;`
- L32 _protected member_ `FOnComplete TaskCompletionDelegate;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnComplete, bool );`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKMpaGetActivities.h` (Private)


#### class `FOnlineAsyncTaskGDKMpaGetActivities`  
`class FOnlineAsyncTaskGDKMpaGetActivities : public FOnlineAsyncTaskGDK`  
_L10-34_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to get activities of users which was set by MPA
- L14 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnComplete, bool , TArray<FOnlineSession> );`
- L16 _public prototype_ `FOnlineAsyncTaskGDKMpaGetActivities( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, const TArray<uint64>& InGDKUserIds, FOnComplete InTaskCompletionDelegate );`
- L23 _public function_ `virtual FString ToString() const override`
- L25 _public prototype_ `virtual void Initialize() override;`
- L26 _public prototype_ `virtual void ProcessResults() override;`
- L27 _public prototype_ `virtual void TriggerDelegates() override;`
- L30 _protected member_ `FGDKContextHandle GDKContext;`
- L31 _protected member_ `TArray<uint64> GDKUserIds;`
- L32 _protected member_ `TArray<FOnlineSession> OnlineSessions;`
- L33 _protected member_ `FOnComplete TaskCompletionDelegate;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnComplete, bool , TArray<FOnlineSession> );`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKMpaSendInvites.h` (Private)


#### class `FOnlineAsyncTaskGDKMpaSendInvites`  
`class FOnlineAsyncTaskGDKMpaSendInvites : public FOnlineAsyncTaskGDK`  
_L10-32_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to send MPA invites
- L14 _public prototype_ `FOnlineAsyncTaskGDKMpaSendInvites( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, const TArray<uint64>& InGDKUserIds, bool InAllowCrossPlatformJoin, const FString& InConnectionString );`
- L22 _public function_ `virtual FString ToString() const override`
- L24 _public prototype_ `virtual void Initialize() override;`
- L25 _public prototype_ `virtual void ProcessResults() override;`
- L28 _protected member_ `FGDKContextHandle GDKContext;`
- L29 _protected member_ `TArray<uint64> GDKUserIds;`
- L30 _protected member_ `bool AllowCrossPlatformJoin;`
- L31 _protected member_ `FString ConnectionString;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKMpaSendInvitesWithUI.h` (Private)


#### class `FOnlineAsyncTaskGDKMpaSendInvitesWithUI`  
`class FOnlineAsyncTaskGDKMpaSendInvitesWithUI : public FOnlineAsyncTaskGDK`  
_L10-28_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to send MPA invites by showing xbox UI to select invitees
- L14 _public prototype_ `FOnlineAsyncTaskGDKMpaSendInvitesWithUI( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, FGDKUserHandle InGDKUser );`
- L20 _public function_ `virtual FString ToString() const override`
- L22 _public prototype_ `virtual void Initialize() override;`
- L23 _public prototype_ `virtual void ProcessResults() override;`
- L26 _protected member_ `FGDKContextHandle GDKContext;`
- L27 _protected member_ `FGDKUserHandle GDKUser;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKMpaSetActivity.h` (Private)


#### class `FOnlineAsyncTaskGDKMpaSetActivity`  
`class FOnlineAsyncTaskGDKMpaSetActivity : public FOnlineAsyncTaskGDK`  
_L11-50_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to set MPA activity
- L15 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnComplete, bool , FName );`
- L17 _public prototype_ `FOnlineAsyncTaskGDKMpaSetActivity( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, const FUniqueNetIdGDKRef& InUserIdGDK, const FName& InSessionName, const FString& InConnectionString, const FString& InGroupId, uint32 InCurrentPlayers, bool InAllowCrossPlatformJoin, const FOnlineSessionSettings& InOnlineSessionSettings, FOnComplete InTaskCompletionDelegate );`
- L30 _public function_ `virtual FString ToString() const override`
- L32 _public prototype_ `virtual void Initialize() override;`
- L33 _public prototype_ `virtual void ProcessResults() override;`
- L34 _public prototype_ `virtual void TriggerDelegates() override;`
- L35 _public prototype_ `virtual void Finalize() override;`
- L39 _protected member_ `FGDKContextHandle GDKContext;`
- L40 _protected member_ `FUniqueNetIdGDKPtr UserIdGDK;`
- L41 _protected member_ `FName SessionName;`
- L42 _protected member_ `std::string ConnectionString;`
- L43 _protected member_ `std::string GroupId;`
- L44 _protected member_ `uint32 CurrentPlayers;`
- L45 _protected member_ `bool AllowCrossPlatformJoin;`
- L46 _protected member_ `FOnlineSessionSettings OnlineSessionSettings;`
- L47 _protected member_ `bool bSetLocalActivty = false;`
- L49 _protected member_ `FOnComplete TaskCompletionDelegate;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnComplete, bool , FName );`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKMpaUpdateRecentPlayers.h` (Private)


#### class `FOnlineAsyncTaskGDKMpaUpdateRecentPlayers`  
`class FOnlineAsyncTaskGDKMpaUpdateRecentPlayers : public FOnlineAsyncTaskGDK`  
_L11-33_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to update MPA recent players
- L15 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnComplete, bool );`
- L17 _public prototype_ `FOnlineAsyncTaskGDKMpaUpdateRecentPlayers( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, const TArray<FReportPlayedWithUser>& InRecentPlayers, FOnComplete InDelegate );`
- L24 _public function_ `virtual FString ToString() const override`
- L26 _public prototype_ `virtual void Initialize() override;`
- L27 _public prototype_ `virtual void TriggerDelegates() override;`
- L30 _protected member_ `FGDKContextHandle GDKContext;`
- L31 _protected member_ `TArray<FReportPlayedWithUser> RecentPlayers;`
- L32 _protected member_ `FOnComplete TaskCompletionDelegate;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnComplete, bool );`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKPurchaseOffer.h` (Private)


#### class `FOnlineAsyncTaskGDKPurchaseOfferBase`  
`class FOnlineAsyncTaskGDKPurchaseOfferBase : public FOnlineAsyncTaskGDK`  
_L13-36_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Base Async task to purchase an offer
- L17 _public prototype_ `FOnlineAsyncTaskGDKPurchaseOfferBase(FOnlineSubsystemGDK* const InLiveInterface, const FString& InStoreId, FGDKUserHandle InGDKUser, FGDKContextHandle InGDKContext, const FUniqueNetIdGDKRef& InNetIdLive, const FString& SubClassName);`
- L18 _public prototype_ `virtual ~FOnlineAsyncTaskGDKPurchaseOfferBase() = default;`
- L20 _public prototype_ `virtual void ProcessResults() override;`
- L23 _public prototype_ `virtual FString ToString() const override;` — FOnlineAsyncItem Interface
- L26 _public prototype_ `virtual void Tick() override;` — FOnlineAsyncTask Interface
- L29 _protected member_ `FString StoreId;`
- L30 _protected member_ `FUniqueNetIdGDKRef NetIdGDK;`
- L31 _protected member_ `FOnlineError ErrorResult;`
- L33 _protected member_ `FGDKContextHandle GDKContext;`
- L34 _protected member_ `FGDKUserHandle GDKUser;`
- L35 _protected member_ `bool bTaskStarted = false;`

#### class `FOnlineAsyncTaskGDKPurchaseOffer`  
`class FOnlineAsyncTaskGDKPurchaseOffer : public FOnlineAsyncTaskGDKPurchaseOfferBase`  
_L41-57_
- inherits: `FOnlineAsyncTaskGDKPurchaseOfferBase`
- desc: Async task to purchase an offer and queries receipts to return via Delegate
- L45 _public prototype_ `FOnlineAsyncTaskGDKPurchaseOffer(FOnlineSubsystemGDK* const InLiveInterface, const FString& InStoreId, FGDKUserHandle InGDKUser, FGDKContextHandle InGDKContext, const FUniqueNetIdGDKRef& InNetIdLive, const FOnPurchaseCheckoutComplete& InDelegate);`
- L46 _public prototype_ `virtual ~FOnlineAsyncTaskGDKPurchaseOffer() = default;`
- L49 _public prototype_ `virtual FString ToString() const override;` — FOnlineAsyncItem Interface
- L52 _public prototype_ `virtual void Finalize() override;` — Move results and trigger delegates in Game Thread
- L53 _public prototype_ `virtual void TriggerDelegates() override;`
- L56 _protected member_ `FOnPurchaseCheckoutComplete Delegate;`

#### class `FOnlineAsyncTaskGDKPurchaseOfferNoEntitlements`  
`class FOnlineAsyncTaskGDKPurchaseOfferNoEntitlements : public FOnlineAsyncTaskGDKPurchaseOfferBase`  
_L62-78_
- inherits: `FOnlineAsyncTaskGDKPurchaseOfferBase`
- desc: Async task to purchase an offer and triggers the delegate with only result, doesn't query receipts
- L66 _public prototype_ `FOnlineAsyncTaskGDKPurchaseOfferNoEntitlements(FOnlineSubsystemGDK* const InLiveInterface, const FString& InStoreId, FGDKUserHandle InGDKUser, FGDKContextHandle InGDKContext, const FUniqueNetIdGDKRef& InNetIdLive, const FOnPurchaseReceiptlessCheckoutComplete& InDelegate);`
- L67 _public prototype_ `virtual ~FOnlineAsyncTaskGDKPurchaseOfferNoEntitlements() = default;`
- L70 _public prototype_ `virtual FString ToString() const override;` — FOnlineAsyncItem Interface
- L73 _public prototype_ `virtual void Finalize() override;` — Move results and trigger delegates in Game Thread
- L74 _public prototype_ `virtual void TriggerDelegates() override;`
- L77 _protected member_ `FOnPurchaseReceiptlessCheckoutComplete Delegate;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKQueryAchievements.h` (Private)


#### class `FOnlineAsyncTaskGDKQueryAchievements`  
`class FOnlineAsyncTaskGDKQueryAchievements : public FOnlineAsyncTaskGDK`  
_L14-52_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to write achievements
- L18 _public prototype_ `FOnlineAsyncTaskGDKQueryAchievements( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, const FUniqueNetIdGDKRef& InUserIdGDK, const FOnQueryGDKAchievementCompleteDelegate& InDelegate );`
- L25 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryAchievements() = default;`
- L28 _public function_ `virtual FString ToString() const override`
- L31 _public prototype_ `virtual void Initialize() override;` — Starts in Game Thread
- L34 _public prototype_ `void ProcessResults();` — Processes in Online Thread
- L37 _public prototype_ `void ProcessNextResult();` — Processes in Online Thread
- L40 _public prototype_ `void ProcessResultInternal(XblAchievementsResultHandle ResultHandle);` — Processes in Online Thread
- L43 _public prototype_ `virtual void TriggerDelegates() override;` — Trigger delegates in Game Thread
- L46 _protected member_ `FUniqueNetIdGDKRef UserIdGDK;`
- L47 _protected member_ `FGDKContextHandle GDKContext;`
- L48 _protected member_ `const FOnQueryGDKAchievementCompleteDelegate TaskCompletionDelegate;`
- L50 _protected member_ `TArray<XblAchievement> AchievementArray;`
- L51 _protected member_ `FGDKAsyncBlockPtr NextResultAsyncBlock;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKQueryActivitiesForUsers.h` (Private)


#### class `FOnlineAsyncTaskGDKQueryActivitiesForUsers`  
`class FOnlineAsyncTaskGDKQueryActivitiesForUsers : public FOnlineAsyncTaskGDK`  
_L17-41_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to query the session details of friends
- L21 _public prototype_ `FOnlineAsyncTaskGDKQueryActivitiesForUsers(FOnlineSubsystemGDK* const InGDKInterface, FGDKContextHandle InGDKContext, const TArray<uint64>& InXUIDs, const FOnGDKQueryActivitiesForUsersComplete& InCompletionDelegate);`
- L25 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryActivitiesForUsers() = default;`
- L28 _public function_ `virtual FString ToString() const override`
- L30 _public prototype_ `virtual void Initialize() override;`
- L31 _public prototype_ `virtual void ProcessResults() override;`
- L33 _public prototype_ `virtual void TriggerDelegates() override;`
- L36 _protected member_ `TArray<uint64> XUIDs;`
- L37 _protected member_ `FOnGDKQueryActivitiesForUsersComplete CompletionDelegate;`
- L38 _protected member_ `FOnlineError ErrorResponse;`
- L39 _protected member_ `FOnlineGDKActivitiesResultMap Results;`
- L40 _protected member_ `FGDKContextHandle GDKContext;`

#### Free symbols / members of external scopes

- L11 _typedef_ `using FOnlineGDKActivitiesResultMap = TUniqueNetIdMap<FUniqueNetIdPtr >;`
- L12 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGDKQueryActivitiesForUsersComplete, const FOnlineError& , const FOnlineGDKActivitiesResultMap& );`
- L12 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnGDKQueryActivitiesForUsersComplete, const FOnlineError& , const FOnlineGDKActivitiesResultMap& );`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKQueryAllOffers.h` (Private)


#### class `FOnlineAsyncTaskGDKQueryAllOffers`  
`class FOnlineAsyncTaskGDKQueryAllOffers : public FOnlineAsyncTaskGDK`  
_L19-42_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async item used to marshal store offer results from the GDK system thread to the game thread.
- L22 _public prototype_ `FOnlineAsyncTaskGDKQueryAllOffers(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InGDKContext, const FOnQueryOnlineStoreOffersComplete& InDelegate);`
- L23 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryAllOffers();`
- L25 _public prototype_ `virtual void Tick() override;`
- L26 _public prototype_ `virtual void ProcessResults() override;`
- L28 _public function_ `virtual FString ToString() const override`
- L29 _public prototype_ `virtual void Finalize() override;`
- L30 _public prototype_ `virtual void TriggerDelegates() override;`
- L31 _public prototype_ `void StartQuery();`
- L32 _public prototype_ `bool EnumerateProductResults(const XStoreProduct* Product);`
- L35 _protected member_ `TArray<FOnlineStoreOfferRef> OffersData;`
- L36 _protected member_ `FOnlineError ErrorResponse;`
- L37 _protected member_ `FOnQueryOnlineStoreOffersComplete Delegate;`
- L38 _protected member_ `FGDKContextHandle GDKContext;`
- L39 _protected member_ `FGDKUserHandle GDKUserHandle;`
- L40 _protected member_ `bool bHasMoreToQuery;`
- L41 _protected member_ `bool bTaskStarted = false;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKQueryAnonymousUserPrivacyPermissions.h` (Private)


#### class `FOnlineAsyncTaskGDKQueryAnonymousUserPrivacyPermissions`  
`class FOnlineAsyncTaskGDKQueryAnonymousUserPrivacyPermissions : public FOnlineAsyncTaskGDK`  
_L29-57_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to query the account details of a user
- L33 _public prototype_ `FOnlineAsyncTaskGDKQueryAnonymousUserPrivacyPermissions(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InGDKContext, const TArray<XblAnonymousUserType>& InUserTypesToQuery, const TArray<XblPermission>& InPermissionsToQuery, const FOnGDKAnonymousUserPrivacyPermissionsQueryComplete& InDelegate);`
- L38 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryAnonymousUserPrivacyPermissions() = default;`
- L41 _public function_ `virtual FString ToString() const override`
- L43 _public prototype_ `virtual void Initialize() override;`
- L45 _public prototype_ `virtual void TriggerDelegates();`
- L48 _protected member_ `TArray<XblAnonymousUserType> UserTypesToQuery;`
- L49 _protected member_ `TArray<XblPermission> PermissionsToQuery;`
- L50 _protected member_ `FOnGDKAnonymousUserPrivacyPermissionsQueryComplete Delegate;`
- L51 _protected member_ `FOnlineError OnlineError;`
- L52 _protected member_ `FAnonymousUserPrivacyPermissionsResultsMap ResultPermissionsMap;`
- L53 _protected member_ `FGDKContextHandle GDKContext;`
- L55 _protected member_ `int NumTasksRemaining = 0;`
- L56 _protected member_ `int NumTasksFailed = 0;`

#### Free symbols / members of external scopes

- L16 _typedef_ `using FAnonymousUserPrivacyPermissionsResultsMap = TMap<XblAnonymousUserType, TMap<XblPermission, bool> >;` — Map of Class's Permission's Allowed status
- L24 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGDKAnonymousUserPrivacyPermissionsQueryComplete, const FOnlineError& , const FAnonymousUserPrivacyPermissionsResultsMap& );` — Delegate used when the class's privacy permissions request has completed @param RequestStatus If this request was successful or not @param Results A Map of Users to permission results
- L24 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnGDKAnonymousUserPrivacyPermissionsQueryComplete, const FOnlineError& , const FAnonymousUserPrivacyPermissionsResultsMap& );` — Delegate used when the class's privacy permissions request has completed @param RequestStatus If this request was successful or not @param Results A Map of Users to permission results

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKQueryAvoidList.h` (Private)


#### class `FOnlineAsyncTaskGDKQueryAvoidList`  
`class FOnlineAsyncTaskGDKQueryAvoidList : public FOnlineAsyncTaskGDK`  
_L18-43_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to query our avoid list
- L22 _public prototype_ `FOnlineAsyncTaskGDKQueryAvoidList(FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, const FUniqueNetIdGDKRef& InUserIdGDK);`
- L23 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryAvoidList() = default;`
- L26 _public function_ `virtual FString ToString() const override`
- L29 _public prototype_ `virtual void Initialize() override;` — Starts in Game Thread
- L31 _public prototype_ `virtual void ProcessResults() override;` — Process in Online Thread
- L34 _public prototype_ `virtual void Finalize() override;` — Move results and trigger delegates in Game Thread
- L35 _public prototype_ `virtual void TriggerDelegates() override;`
- L38 _protected member_ `FUniqueNetIdGDKRef UserIdGDK;`
- L40 _protected member_ `TArray<TSharedRef<FOnlineBlockedPlayerGDK>> AvoidList;`
- L41 _protected member_ `FString OutError;`
- L42 _protected member_ `FGDKContextHandle GDKContext;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKQueryFriends.h` (Private)


#### class `FOnlineAsyncTaskGDKQueryFriends`  
`class FOnlineAsyncTaskGDKQueryFriends : public FOnlineAsyncTaskGDK`  
_L14-50_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to query our friends list
- L18 _public prototype_ `FOnlineAsyncTaskGDKQueryFriends(FOnlineSubsystemGDK* const InGDKInterface, FGDKContextHandle InGDKContext, const int32 InLocalUserNum, const FUniqueNetIdGDKRef& InGDKUniqueNetId, const FString& InListName);`
- L19 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryFriends() = default;`
- L22 _public function_ `virtual FString ToString() const override`
- L25 _public prototype_ `virtual void Initialize() override;` — Start in Game Thread
- L27 _public prototype_ `virtual void ProcessResults() override;` — Process in Online Thread
- L30 _public prototype_ `virtual void Finalize() override;` — Move results and trigger delegates in Game Thread
- L31 _public prototype_ `virtual void TriggerDelegates() override;`
- L35 _protected prototype_ `virtual void GetNextPage(XblSocialRelationshipResultHandle RelationshipHandle);`
- L36 _protected prototype_ `virtual void ProcessNextPage(XblSocialRelationshipResultHandle RelationshipHandle);`
- L38 _protected member_ `int32 LocalUserNum;`
- L39 _protected member_ `FUniqueNetIdGDKRef GDKUniqueNetId;`
- L40 _protected member_ `FString ListName;`
- L42 _protected member_ `volatile int32 FoundItemCount;`
- L43 _protected member_ `FString OutError;`
- L45 _protected member_ `FOnlineFriendsListGDKMap FriendsListMap;`
- L46 _protected member_ `FGDKContextHandle GDKContext;`
- L47 _protected member_ `TArray<uint64> XUIDs;`
- L49 _protected member_ `FGDKAsyncBlockPtr PagesAsyncBlock;`

#### class `FOnlineAsyncTaskGDKQueryFriendManagerTask`  
`class FOnlineAsyncTaskGDKQueryFriendManagerTask : public FOnlineAsyncTaskGDK`  
_L55-93_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to manage calling delegates and updating the local cache after the other friends-list tasks are completed
- L62 _public function_ `FOnlineAsyncTaskGDKQueryFriendManagerTask(FOnlineSubsystemGDK* const InSubsystem, FOnlineFriendsListGDKMap&& InFriendsListMap, const int32 InLocalUserNum, const FUniqueNetIdGDKRef& InGDKUniqueNetId, FString&& InListName) : FOnlineAsyncTaskGDK(InSubsystem, TEXT("FOnlineAsyncTaskGDKQueryFriendManagerTask"), InLocalUserNum) , FriendsListMap(MoveTemp(InFriendsListMap)) , LocalUserNum(InLocalUserNum) , GDKUniqueNetId(InGDKUniqueNetId) , ListName(MoveTemp(InListName)) , AccountDetailsStatus(EOnlineAsyncTaskState::NotStarted) , PresenceDetailsStatus(EOnlineAsyncTaskState::NotStarted) , PresenceStatsStatus(EOnlineAsyncTaskState::NotStarted) , SessionDetailsStatus(EOnlineAsyncTaskState::NotStarted)`
- L75 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryFriendManagerTask() = default;`
- L77 _public function_ `virtual FString ToString() const override`
- L79 _public prototype_ `virtual void Tick() override;`
- L80 _public prototype_ `virtual void Finalize() override;`
- L81 _public prototype_ `virtual void TriggerDelegates() override;`
- L85 _public member_ `int32 LocalUserNum;`
- L86 _public member_ `FUniqueNetIdGDKRef GDKUniqueNetId;`
- L87 _public member_ `FString ListName;`
- L89 _public member_ `volatile EOnlineAsyncTaskState::Type AccountDetailsStatus;`
- L90 _public member_ `volatile EOnlineAsyncTaskState::Type PresenceDetailsStatus;`
- L91 _public member_ `volatile EOnlineAsyncTaskState::Type PresenceStatsStatus;`
- L92 _public member_ `volatile EOnlineAsyncTaskState::Type SessionDetailsStatus;`

#### class `FOnlineAsyncTaskGDKQueryFriendAccountDetails`  
`class FOnlineAsyncTaskGDKQueryFriendAccountDetails : public FOnlineAsyncTaskGDK`  
_L98-120_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to query the account details of friends
- L102 _public prototype_ `FOnlineAsyncTaskGDKQueryFriendAccountDetails(FOnlineSubsystemGDK* const InGDKInterface, FGDKContextHandle InGDKContext, const TArray<uint64> InXUIDs, FOnlineAsyncTaskGDKQueryFriendManagerTask& InManagerTask);`
- L106 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryFriendAccountDetails() = default;`
- L109 _public function_ `virtual FString ToString() const override`
- L111 _public prototype_ `virtual void Initialize() override;`
- L112 _public prototype_ `virtual void ProcessResults() override;`
- L114 _public prototype_ `virtual void Finalize();`
- L117 _protected member_ `const TArray<uint64> XUIDs;`
- L118 _protected member_ `FOnlineAsyncTaskGDKQueryFriendManagerTask& ManagerTask;`
- L119 _protected member_ `FGDKContextHandle GDKContext;`

#### class `FOnlineAsyncTaskGDKQueryFriendPresenceDetails`  
`class FOnlineAsyncTaskGDKQueryFriendPresenceDetails : public FOnlineAsyncTaskGDK`  
_L125-148_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to query the presence details of friends
- L129 _public prototype_ `FOnlineAsyncTaskGDKQueryFriendPresenceDetails(FOnlineSubsystemGDK* const InGDKInterface, FGDKContextHandle InGDKContext, const TArray<uint64> InXUIDs, FOnlineAsyncTaskGDKQueryFriendManagerTask& InManagerTask);`
- L133 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryFriendPresenceDetails() = default;`
- L136 _public function_ `virtual FString ToString() const override`
- L138 _public prototype_ `virtual void Initialize() override;`
- L139 _public prototype_ `virtual void ProcessResults() override;`
- L141 _public prototype_ `virtual void Finalize();`
- L144 _protected member_ `const TArray<uint64> XUIDs;`
- L145 _protected member_ `FOnlineAsyncTaskGDKQueryFriendManagerTask& ManagerTask;`
- L146 _protected member_ `FGDKContextHandle GDKContext;`
- L147 _protected member_ `XblPresenceQueryFilters Filter{};`

#### class `FOnlineAsyncTaskGDKQueryFriendPresenceStats`  
`class FOnlineAsyncTaskGDKQueryFriendPresenceStats : public FOnlineAsyncTaskGDK`  
_L153-195_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to query additional stats used for presence of friends
- L157 _public prototype_ `FOnlineAsyncTaskGDKQueryFriendPresenceStats(FOnlineSubsystemGDK* const InGDKInterface, FGDKContextHandle InGDKContext, const TArray<uint64> InXUIDs, const int32 InStartIndex, const TArray<FString>&& InPresenceStatNames, FOnlineAsyncTaskGDKQueryFriendManagerTask& InManagerTask);`
- L163 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryFriendPresenceStats() = default;`
- L166 _public function_ `virtual FString ToString() const override`
- L168 _public prototype_ `virtual void Initialize() override;`
- L169 _public prototype_ `virtual void ProcessResults() override;`
- L171 _public prototype_ `virtual void Finalize();`
- L175 _private member_ `static const int32 MAX_USER_QUERY_COUNT = 50;` — Maximum amount of user's to request stats from at a time
- L178 _private member_ `int32 StartIndex;` — Index to start processing users from
- L180 _private member_ `int32 NextRequestIndex;` — Index of next request's start; used to signal we're finished if this is >= the user vector size
- L182 _private member_ `const TArray<uint64> XUIDs;` — Vector view of all friends to query
- L184 _private member_ `TArray<FString> PresenceStatNames;` — List of stats needing queried from the above users
- L186 _private member_ `FOnlineAsyncTaskGDKQueryFriendManagerTask& ManagerTask;` — Manager task tracking completion of all friends requests
- L188 _private member_ `FGDKContextHandle GDKContext;`
- L191 _private member_ `TArray<TArray<ANSICHAR>> PresenceStatNamesAnsiChar;` — Array to store Ansi strings for presence stat names that will be cleaned up when task is destroyed (Avoiding explicit mallocs)
- L194 _private member_ `TArray<const ANSICHAR*> PresenceStatNamesCharPtr;` — Array to store char* that we can pass to GDK API (Points to data in PresenceStatNamesAnsiChar)

#### class `FOnlineAsyncTaskGDKQueryFriendSessionDetails`  
`class FOnlineAsyncTaskGDKQueryFriendSessionDetails : public FOnlineAsyncTaskGDK`  
_L200-222_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to query the session details of friends
- L204 _public prototype_ `FOnlineAsyncTaskGDKQueryFriendSessionDetails(FOnlineSubsystemGDK* const InGDKInterface, FGDKContextHandle InGDKContext, const TArray<uint64> InXUIDs, FOnlineAsyncTaskGDKQueryFriendManagerTask& InManagerTask);`
- L208 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryFriendSessionDetails() = default;`
- L211 _public function_ `virtual FString ToString() const override`
- L213 _public prototype_ `virtual void Initialize() override;`
- L214 _public prototype_ `virtual void ProcessResults() override;`
- L216 _public prototype_ `virtual void Finalize();`
- L219 _protected member_ `const TArray<uint64> XUIDs;`
- L220 _protected member_ `FOnlineAsyncTaskGDKQueryFriendManagerTask& ManagerTask;`
- L221 _protected member_ `FGDKContextHandle GDKContext;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKQueryOffers.h` (Private)


#### class `FOnlineAsyncTaskGDKQueryOffers`  
`class FOnlineAsyncTaskGDKQueryOffers : public FOnlineAsyncTaskGDK`  
_L19-44_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async item used to marshal store offer results from the GDK system thread to the game thread.
- L22 _public prototype_ `FOnlineAsyncTaskGDKQueryOffers(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InGDKContext, const TArray<FUniqueOfferId>& InOfferIds, const FOnQueryOnlineStoreOffersComplete& InDelegate);`
- L23 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryOffers();`
- L25 _public prototype_ `virtual void Tick() override;`
- L26 _public prototype_ `virtual void ProcessResults() override;`
- L28 _public function_ `virtual FString ToString() const override`
- L29 _public prototype_ `virtual void Finalize() override;`
- L30 _public prototype_ `virtual void TriggerDelegates() override;`
- L31 _public prototype_ `void StartQuery();`
- L32 _public prototype_ `bool EnumerateProductResults(const XStoreProduct* Product);`
- L34 _protected member_ `TArray<FUniqueOfferId> OfferIds;`
- L35 _protected member_ `TArray<FOnlineStoreOfferRef> OffersData;`
- L36 _protected member_ `FOnlineError ErrorResponse;`
- L37 _protected member_ `FOnQueryOnlineStoreOffersComplete Delegate;`
- L38 _protected member_ `int32 OfferQueriedIndex;`
- L39 _protected member_ `FGDKContextHandle GDKContext;`
- L40 _protected member_ `TArray<TArray<ANSICHAR>> OfferIdsAnsiChar;`
- L41 _protected member_ `TArray<const ANSICHAR*> OfferIdsCharPtr;`
- L42 _protected member_ `FGDKUserHandle GDKUserHandle;`
- L43 _protected member_ `bool bTaskStarted = false;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKQueryPreferredLocalUdpMultiplayerPort.h` (Private)


#### class `FOnlineAsyncTaskGDKQueryPreferredLocalUdpMultiplayerPort`  
`class FOnlineAsyncTaskGDKQueryPreferredLocalUdpMultiplayerPort : public FOnlineAsyncTaskGDK`  
_L13-42_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to query the preferred local udp multiplayer port
- L20 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnQueryPreferredLocalUdpMultiplayerPortCompleteDelegate, bool, uint16_t );` — Delegate fired when GetUserProfile Task is complete.
- L22 _public prototype_ `FOnlineAsyncTaskGDKQueryPreferredLocalUdpMultiplayerPort( FOnlineSubsystemGDK* InGDKInterface, const FOnQueryPreferredLocalUdpMultiplayerPortCompleteDelegate& InTaskCompletionDelegate);`
- L26 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryPreferredLocalUdpMultiplayerPort() = default;`
- L29 _public function_ `virtual FString ToString() const override`
- L32 _public prototype_ `virtual void Initialize() override;` — Starts in Game Thread
- L34 _public prototype_ `virtual void ProcessResults() override;`
- L37 _public prototype_ `virtual void TriggerDelegates() override;` — Move results and trigger delegates in Game Thread
- L40 _protected member_ `uint16_t GDKPort;`
- L41 _protected member_ `const FOnQueryPreferredLocalUdpMultiplayerPortCompleteDelegate TaskCompletionDelegate;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnQueryPreferredLocalUdpMultiplayerPortCompleteDelegate, bool, uint16_t );` — Delegate fired when GetUserProfile Task is complete.

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKQueryPresence.h` (Private)


#### class `FOnlineAsyncTaskGDKQueryPresence`  
`class FOnlineAsyncTaskGDKQueryPresence : public FOnlineAsyncTaskBasic<FOnlineSubsystemGDK>`  
_L12-67_
- inherits: `FOnlineAsyncTaskBasic<FOnlineSubsystemGDK>`
- desc: Custom task class that handles getting presence info as well as configured stats in parallel.
- L15 _public function_ `FOnlineAsyncTaskGDKQueryPresence( FOnlineSubsystemGDK* const InGDKSubsystem, FGDKContextHandle InGDKContext, const FUniqueNetIdGDKRef& InUser, const IOnlinePresence::FOnPresenceTaskCompleteDelegate& InDelegate) : FOnlineAsyncTaskBasic(InGDKSubsystem) , GDKContext(InGDKContext) , User(InUser) , Delegate(InDelegate)`
- L27 _public function_ `virtual FString ToString() const override`
- L32 _public prototype_ `virtual void Initialize() override;`
- L33 _public prototype_ `void ProcessResult();`
- L34 _public prototype_ `virtual void Tick() override;`
- L35 _public prototype_ `void ProcessPresenceResult();`
- L36 _public prototype_ `void ProcessStatsResult();`
- L37 _public prototype_ `virtual void Finalize() override;`
- L38 _public prototype_ `virtual void TriggerDelegates() override;`
- L42 _private member_ `FGDKContextHandle GDKContext;` — The GDK context of the user requesting presence information.
- L45 _private member_ `FUniqueNetIdGDKRef User;` — The user whose presence data is being queried.
- L48 _private member_ `IOnlinePresence::FOnPresenceTaskCompleteDelegate Delegate;` — Stored delegate passed in from IOnlinePesence::QueryPresence, to be triggered in TriggerDelegates().
- L51 _private member_ `FGDKPresenceRecordHandle PresenceResult;` — Result of the async presence query. Used to update cached data in Finalize().
- L54 _private member_ `XblUserStatisticsResult* StatsResult = nullptr;` — Result of the async stats query. Used to update cached data in Finalize().
- L59 _private member_ `bool bPresenceTaskIsDone = false;`
- L60 _private member_ `bool bPresenceTaskSucceeded = false;`
- L61 _private member_ `bool bStatsTaskIsDone = false;`
- L62 _private member_ `bool bStatsTaskSucceeded = false;`
- L64 _private member_ `TArray<uint8> StatsResultBuffer;`
- L65 _private member_ `XblUserStatisticsResult* StatisticsResult = nullptr;`
- L66 _private member_ `FGDKPresenceRecordHandle PresenceRecordHandle;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKQueryReceipts.h` (Private)


#### class `FOnlineAsyncTaskGDKQueryReceipts`  
`class FOnlineAsyncTaskGDKQueryReceipts : public FOnlineAsyncTaskGDK`  
_L21-73_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async item used to query a specific user's receipts
- L25 _public prototype_ `FOnlineAsyncTaskGDKQueryReceipts(FOnlineSubsystemGDK* const InGDKInterface, const FUniqueNetIdGDKRef& InUserId, FGDKContextHandle InGDKContext, const FOnQueryReceiptsComplete& InQueryReceiptsDelegate);`
- L26 _public prototype_ `FOnlineAsyncTaskGDKQueryReceipts(FOnlineSubsystemGDK* const InGDKInterface, const FUniqueNetIdGDKRef& InUserId, FGDKContextHandle InGDKContext, const FOnPurchaseCheckoutComplete& InPurchaseCheckoutDelegate);`
- L28 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryReceipts();`
- L31 _public function_ `virtual FString ToString() const override`
- L33 _public prototype_ `void ProcessTokenResult();`
- L34 _public prototype_ `void ProcessProductsResult();`
- L35 _public prototype_ `void EnumerateProductsResult(XStoreProductQueryHandle QueryHandle);`
- L36 _public prototype_ `void ProcessProductsNextPageResult();`
- L39 _public prototype_ `void Tick();`
- L42 _public prototype_ `virtual void Finalize() override;`
- L43 _public prototype_ `virtual void TriggerDelegates() override;`
- L46 _private prototype_ `void TickStartTask();`
- L47 _private prototype_ `void FailTask_Internal(const bool bSoftFail);`
- L48 _private prototype_ `void FailTask(const bool bSoftFail);`
- L49 _private prototype_ `void FailTask(const FText ErrorMessage, const bool bSoftFail);`
- L50 _private prototype_ `void FailTaskCode(const int32 ErrorCode, const bool bSoftFail);`
- L53 _private member_ `FGDKContextHandle GDKContext;`
- L54 _private member_ `FUniqueNetIdGDKRef UserId;`
- L57 _private member_ `bool bSoftFailReceiptFailures;` — If true, instead of hard-failing on request failures, return success with an error message; this will replace our cached items with partial results
- L59 _private member_ `TArray<FPurchaseReceipt> ReceiptData;`
- L60 _private member_ `FOnlineError ErrorResponse;`
- L62 _private member_ `const FOnQueryReceiptsComplete QueryReceiptsDelegate;`
- L63 _private member_ `const FOnPurchaseCheckoutComplete PurchaseCheckoutDelegate;`
- L64 _private member_ `FGDKAsyncBlockPtr AsyncBlockProducts;`
- L65 _private member_ `FString XSTSToken;`
- L66 _private member_ `bool bXSTSTokenTaskIsSuccessful = false;`
- L67 _private member_ `bool bXSTSTokenTaskIsComplete = false;`
- L68 _private member_ `bool bProductTaskIsSuccessful = false;`
- L69 _private member_ `bool bProductTaskIsComplete = false;`
- L70 _private member_ `bool bTaskStarted = false;`
- L71 _private member_ `TArray<const XStoreProduct*> ProductArray;`
- L72 _private member_ `FGDKUserHandle UserHandle;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKQueryUserPrivacyPermissions.h` (Private)


#### class `FOnlineAsyncTaskGDKQueryUserPrivacyPermissions`  
`class FOnlineAsyncTaskGDKQueryUserPrivacyPermissions : public FOnlineAsyncTaskGDK`  
_L30-57_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to query the account details of a user
- L34 _public prototype_ `FOnlineAsyncTaskGDKQueryUserPrivacyPermissions(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InGDKContext, const TArray<FUniqueNetIdRef>& InUsersToQuery, const TArray<XblPermission>& InPermissionsToQuery, const FOnGDKUserPrivacyPermissionsQueryComplete& InDelegate);`
- L39 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryUserPrivacyPermissions() = default;`
- L42 _public function_ `virtual FString ToString() const override`
- L44 _public prototype_ `virtual void Initialize() override;`
- L45 _public prototype_ `virtual void ProcessResults() override;`
- L47 _public prototype_ `virtual void Finalize();`
- L48 _public prototype_ `virtual void TriggerDelegates();`
- L51 _protected member_ `TArray<FUniqueNetIdRef> UsersToQuery;`
- L52 _protected member_ `TArray<XblPermission> PermissionsToQuery;`
- L53 _protected member_ `FOnGDKUserPrivacyPermissionsQueryComplete Delegate;`
- L54 _protected member_ `FOnlineError OnlineError;`
- L55 _protected member_ `FPrivacyPermissionsResultsMap UserPermissionsMap;`
- L56 _protected member_ `FGDKContextHandle GDKContext;`

#### Free symbols / members of external scopes

- L16 _typedef_ `using FPrivacyPermissionsResultsMap = TUniqueNetIdMap<TMap<XblPermission, bool>>;` — Map of User's Permission's Allowed status
- L25 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnGDKUserPrivacyPermissionsQueryComplete, const FOnlineError& , const FUniqueNetIdRef& , const FPrivacyPermissionsResultsMap& );` — Delegate used when the user's privacy permissions request has completed @param RequestStatus If this request was successful or not @param RequestingUser The user who generated this request @param Results A Map of Users to permission results
- L25 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnGDKUserPrivacyPermissionsQueryComplete, const FOnlineError& , const FUniqueNetIdRef& , const FPrivacyPermissionsResultsMap& );` — Delegate used when the user's privacy permissions request has completed @param RequestStatus If this request was successful or not @param RequestingUser The user who generated this request @param Results A Map of Users to permission results

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKQueryUsers.h` (Private)


#### class `FOnlineAsyncTaskGDKQueryUsers`  
`class FOnlineAsyncTaskGDKQueryUsers : public FOnlineAsyncTaskGDK`  
_L15-42_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to query the account details of a user
- L19 _public prototype_ `FOnlineAsyncTaskGDKQueryUsers(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InGDKContext, const TArray<FUniqueNetIdRef>& InUsersToQuery, int32 InLocalUserNum, const FOnQueryUserInfoComplete& InDelegate);`
- L24 _public prototype_ `virtual ~FOnlineAsyncTaskGDKQueryUsers() = default;`
- L27 _public function_ `virtual FString ToString() const override`
- L29 _public prototype_ `virtual void Initialize() override;`
- L30 _public prototype_ `virtual void ProcessResults() override;`
- L32 _public prototype_ `virtual void Finalize();`
- L33 _public prototype_ `virtual void TriggerDelegates();`
- L36 _protected member_ `TArray<FUniqueNetIdRef> UsersToQuery;`
- L37 _protected member_ `int32 LocalUserNum;`
- L38 _protected member_ `FOnQueryUserInfoComplete Delegate;`
- L39 _protected member_ `FOnlineError OnlineError;`
- L40 _protected member_ `TUniqueNetIdMap<TSharedRef<FOnlineUserInfoGDK>> UserInfoMap;`
- L41 _protected member_ `FGDKContextHandle GDKContext;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKReadLeaderboards.h` (Private)


#### class `FOnlineAsyncTaskGDKReadLeaderboards`  
`class FOnlineAsyncTaskGDKReadLeaderboards : public FOnlineAsyncTaskBasic<FOnlineSubsystemGDK>, public TSharedFromThis<FOnlineAsyncTaskGDKReadLeaderboards, ESPMode::ThreadSafe>`  
_L20-62_
- inherits: `FOnlineAsyncTaskBasic<FOnlineSubsystemGDK>,TSharedFromThis<FOnlineAsyncTaskGDKReadLeaderboards,ESPMode::ThreadSafe>`
- desc: Async task to retrieve a leaderboard containing a list of users from Live
- L30 _public prototype_ `FOnlineAsyncTaskGDKReadLeaderboards( FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InGDKContext, TArray<FOnlineLeaderboardReadRef> InLeaderboardReads, const FOnlineLeaderboardReadRef& InReadObject, const TArray<FUniqueNetIdRef>& InPlayers, XblSocialGroupType InSocialGroupType, const FString& InStatName, bool InSkipToUser, const FOnReadLeaderboardsCompleteDelegate& InDelegate);` — Constructor @param InGDKSubsystem - The GDKOnlineSubsystem used to retrieve the leaderboards interface @param InLeaderboardReads - The array of LeaderboardReads to consolidate into the ReadObject @param InReadObject - The storage location for the returned leaderboard data
- L44 _public function_ `virtual FString ToString() const` — Get a human readable description of task
- L45 _public prototype_ `virtual void Initialize();`
- L46 _public prototype_ `virtual void Tick();`
- L47 _public prototype_ `virtual void Finalize();`
- L48 _public prototype_ `virtual void TriggerDelegates();`
- L49 _public prototype_ `void OnGetLeaderboardComplete(bool bSuccess);`
- L53 _private member_ `TArray<FOnlineLeaderboardReadRef> LeaderboardReads;` — List of ReadObjects to be populated by single user leaderboard requests
- L55 _private member_ `FOnlineLeaderboardReadPtr ReadObject;` — Handle to the read object where the data will be stored
- L56 _private member_ `TArray<FUniqueNetIdRef> Players;`
- L57 _private member_ `FOnReadLeaderboardsCompleteDelegate Delegate;`
- L58 _private member_ `XblSocialGroupType SocialGroupType;`
- L59 _private member_ `bool SkipToUser;`
- L60 _private member_ `FGDKContextHandle GDKContext;`
- L61 _private member_ `FString StatName;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKRedeemCode.h` (Private)


#### class `FOnlineAsyncTaskGDKRedeemCode`  
`class FOnlineAsyncTaskGDKRedeemCode : public FOnlineAsyncTaskGDK`  
_L19-49_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to redeem a code
- L23 _public prototype_ `FOnlineAsyncTaskGDKRedeemCode(FOnlineSubsystemGDK* const InGDKInterface, FGDKUserHandle InGDKUser, FGDKContextHandle InGDKContext, const FUniqueNetIdGDKRef& InNetIdGDK, const FRedeemCodeRequest& InRedeemCodeRequest, const FOnPurchaseRedeemCodeComplete& InDelegate);`
- L24 _public prototype_ `virtual ~FOnlineAsyncTaskGDKRedeemCode() = default;`
- L27 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem Interface
- L30 _public prototype_ `virtual void Tick() override;` — FOnlineAsyncItemBasic
- L32 _public prototype_ `virtual void ProcessResults() override;`
- L36 _public prototype_ `virtual void Finalize() override;` — FOnlineAsyncTask Interface Move results and trigger delegates in Game Thread
- L37 _public prototype_ `virtual void TriggerDelegates() override;`
- L39 _public prototype_ `void OnApplicationReactivated();`
- L42 _protected member_ `FGDKUserHandle LocalUser;`
- L43 _protected member_ `FGDKContextHandle GDKContext;`
- L44 _protected member_ `FUniqueNetIdGDKRef NetIdGDK;`
- L45 _protected member_ `FOnPurchaseRedeemCodeComplete Delegate;`
- L46 _protected member_ `FOnlineError ErrorResult;`
- L47 _protected member_ `FRedeemCodeRequest RedeemCodeRequest;`
- L48 _protected member_ `bool bTaskStarted = false;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKRegisterLocalUser.h` (Private)


#### class `FOnlineAsyncTaskGDKRegisterLocalUser`  
`class FOnlineAsyncTaskGDKRegisterLocalUser : public FOnlineAsyncTaskGDKSafeWriteSession`  
_L12-43_
- inherits: `FOnlineAsyncTaskGDKSafeWriteSession`
- desc: Async task used to have another local user Join() a Live session.
- L15 _public prototype_ `FOnlineAsyncTaskGDKRegisterLocalUser( FOnlineSubsystemGDK* const InSubsystem, FGDKContextHandle InContext, const FName InSessionName, FUniqueNetIdGDKRef InUserId, FGDKMultiplayerSessionHandle InGDKSession, XblMultiplayerSessionChangeTypes InSubscriptionType, const FOnRegisterLocalPlayerCompleteDelegate& InDelegate, TArray<const XblMultiplayerSessionMember*> InInitializationGroup);`
- L26 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L27 _public prototype_ `virtual void TriggerDelegates() override;`
- L28 _public prototype_ `virtual void Finalize() override;`
- L33 _private prototype_ `virtual bool UpdateSession(FGDKMultiplayerSessionHandle Session);` — FOnlineAsyncTaskGDKSafeWriteSession
- L35 _private member_ `FUniqueNetIdGDKRef UserId;`
- L36 _private member_ `XblMultiplayerSessionChangeTypes SubscriptionType;`
- L37 _private member_ `FOnRegisterLocalPlayerCompleteDelegate Delegate;`
- L39 _private member_ `EOnJoinSessionCompleteResult::Type Result;`
- L42 _private member_ `TArray<const XblMultiplayerSessionMember*> InitializationGroup;` — Allow initialization group to be specified, so QoS knows which users are on the same console

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKResolvePrivilegeWithUI.h` (Private)


#### class `FOnlineAsyncTaskGDKResolvePrivilegeWithUI`  
`class FOnlineAsyncTaskGDKResolvePrivilegeWithUI : public FOnlineAsyncTaskGDK`  
_L14-46_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to write achievements
- L18 _public prototype_ `FOnlineAsyncTaskGDKResolvePrivilegeWithUI( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, FGDKUserHandle InGDKUser, XUserPrivilegeOptions InOptions, XUserPrivilege InPrivilege, const FOnQueryGDKResolvePrivilegeWithUICompleteDelegate& InTaskCompletionDelegate );`
- L27 _public prototype_ `virtual ~FOnlineAsyncTaskGDKResolvePrivilegeWithUI() = default;`
- L30 _public function_ `virtual FString ToString() const override`
- L33 _public prototype_ `virtual void Initialize() override;` — Starts in Game Thread
- L35 _public prototype_ `virtual void ProcessResults() override;` — Process in Online Thread
- L38 _public prototype_ `virtual void TriggerDelegates() override;` — Move results and trigger delegates in Game Thread
- L41 _protected member_ `FGDKContextHandle GDKContext;`
- L42 _protected member_ `const FOnQueryGDKShowProfileUICompleteDelegate TaskCompletionDelegate;`
- L43 _protected member_ `FGDKUserHandle GDKUser;`
- L44 _protected member_ `XUserPrivilegeOptions Options;`
- L45 _protected member_ `XUserPrivilege Privilege;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKSafeWriteSession.h` (Private)


#### class `FOnlineAsyncTaskGDKSafeWriteSession`  
`class FOnlineAsyncTaskGDKSafeWriteSession : public FOnlineAsyncTaskGDK`  
_L9-117_
- inherits: `FOnlineAsyncTaskGDK`
- L22 _public prototype_ `FOnlineAsyncTaskGDKSafeWriteSession( FOnlineSubsystemGDK* const InGDKSubsystem, const FString& AsyncTaskName, FGDKContextHandle InGDKContext, const FName InSessionName, FGDKMultiplayerSessionHandle InGDKSession, const int32 InMaxRetryCount = DefaultMaxRetryCount);` — This constructor takes the GDK Session directly and is safe to call in non-game threads. @param InSubsystem the owning GDK online subsystem @param InLiveContext the GDK context of the user who's updating the session @param InSessionName the name of the session to update @param InGDKSession the GDK session object to update @param MaxRetryCount number of times to retry the session write
- L42 _public prototype_ `FOnlineAsyncTaskGDKSafeWriteSession( FOnlineSubsystemGDK* const InGDKSubsystem, const FString& AsyncTaskName, FGDKContextHandle InLiveContext, const FName InSessionName, const int32 InMaxRetryCount);` — This constructor takes the GDK Session directly and is safe to call in non-game threads.  It relies on overloading tasks to have populated at least the GDK Session Reference before Initialize is called in this base class.  In practice, this means tasks must be processed in Serial rather than Parallel, on the async task manager. @param InSubsystem the owning GDK online subsystem @param InGDKContext the GDK context of the user who's updating the session @param InSessionName the name of the session to update @param MaxRetryCount number of times to retry the session write
- L50 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L55 _public function_ `FString GetAsyncSafeWriteTaskInfoString() const`
- L61 _public prototype_ `virtual void Finalize() override;`
- L62 _public prototype_ `virtual void Initialize() override;`
- L63 _public prototype_ `virtual void Tick() override;`
- L64 _public prototype_ `void ProcessGetSessionResult();`
- L65 _public prototype_ `virtual void ProcessWriteSessionResult();`
- L66 _public member_ `static const int32 DefaultMaxRetryCount = 5;`
- L69 _protected function_ `FGDKMultiplayerSessionHandle GetLatestGDKSession() const`
- L70 _protected function_ `FName GetSessionName() const`
- L71 _protected function_ `bool GetDidUpdateSession() const`
- L72 _protected function_ `FGDKContextHandle GetGDKContext() const`
- L73 _protected function_ `const XblMultiplayerSessionReference& GetSessionReference() const`
- L76 _protected prototype_ `void OnFailed();` — Called when a task has failed to mark it complete and as unsuccessful
- L79 _protected prototype_ `void Retry();` — Called to start our write flow
- L84 _private prototype_ `void TryWriteSession();` — Called when we have a LiveSession object to write to
- L92 _private function_ `virtual bool UpdateSession(FGDKMultiplayerSessionHandle Session)` — Overridden by subclasses to perform the update on the local copy of the session document. @param Session The session to update @return true if the session was updated, false if not
- L96 _protected member_ `XblMultiplayerSessionWriteMode SessionWriteMode;` — What method of session write do we wish to use for this update
- L98 _protected member_ `FGDKContextHandle GDKContext;` — Who this session is being written by
- L100 _protected member_ `FName SessionName;` — Saved SessionName for completion delegates, if needed
- L102 _protected member_ `FGDKMultiplayerSessionHandle GDKSession;` — GDK Session object to be written to (may be null)
- L104 _protected member_ `const XblMultiplayerSessionReference* GDKSessionReference;` — GDK Session Reference object (must not be null)
- L106 _protected member_ `int32 MaxRetryCount;` — Maximum amount of times to try writing upon write-conflicts
- L108 _protected member_ `int32 TotalRetryAttempts;` — Maximum amount of times to attempt our read/write flow
- L110 _protected member_ `int32 TotalSessionWrites;` — Total amount of times we sent a write request for this session
- L112 _protected member_ `int32 TotalSessionReads;` — Total amount of times we downloaded a new copy of the session document
- L114 _protected member_ `bool bUpdatedSession;` — Store whether a subclass modified the session, so it can be referred to in Finalize()
- L116 _protected member_ `FGDKAsyncBlockPtr WriteSessionAsyncBlock;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKSanitizeString.h` (Private)


#### class `FOnlineAsyncTaskGDKSanitizeSingleString`  
`class FOnlineAsyncTaskGDKSanitizeSingleString : public FOnlineAsyncTaskGDK`  
_L23-53_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to sanitize profanities in single strings
- L27 _public function_ `FOnlineAsyncTaskGDKSanitizeSingleString(FOnlineSubsystemGDK* const InGDKSubsystem , FGDKContextHandle InGDKContext , const FString& InStringToSanitize , const FOnlineAsyncTaskGDKSanitizeSingleStringComplete& InDelegate) : FOnlineAsyncTaskGDK(InGDKSubsystem, TEXT("FOnlineAsyncTaskGDKSanitizeSingleString")) , GDKContext(InGDKContext) , StringToSanitize(InStringToSanitize) , SanitizedString(InStringToSanitize) , Delegate(InDelegate)`
- L38 _public function_ `virtual FString ToString() const override`
- L43 _public prototype_ `virtual void Initialize() override;`
- L44 _public prototype_ `virtual void ProcessResults() override;`
- L45 _public prototype_ `virtual void TriggerDelegates() override;`
- L48 _private member_ `FGDKContextHandle GDKContext;`
- L49 _private member_ `const FString StringToSanitize;`
- L50 _private member_ `FString SanitizedString;`
- L52 _private member_ `FOnlineAsyncTaskGDKSanitizeSingleStringComplete Delegate;`

#### class `FOnlineAsyncTaskGDKSanitizeMultipleStrings`  
`class FOnlineAsyncTaskGDKSanitizeMultipleStrings : public FOnlineAsyncTaskGDK`  
_L66-95_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to Sanitize profanities in multiple strings
- L70 _public function_ `FOnlineAsyncTaskGDKSanitizeMultipleStrings(FOnlineSubsystemGDK* const InGDKSubsystem , FGDKContextHandle InGDKContext , const TArray<FString>& InStringArrayToSanitize , const FOnlineAsyncTaskGDKSanitizeMultipleStringsComplete& InDelegate) : FOnlineAsyncTaskGDK(InGDKSubsystem, TEXT("FOnlineAsyncTaskGDKSanitizeMultipleStrings")) , GDKContext(InGDKContext) , StringArrayToSanitize(InStringArrayToSanitize) , Delegate(InDelegate)`
- L80 _public function_ `virtual FString ToString() const override`
- L85 _public prototype_ `virtual void Initialize() override;`
- L86 _public prototype_ `virtual void ProcessResults() override;`
- L87 _public prototype_ `virtual void TriggerDelegates() override;`
- L90 _private member_ `FGDKContextHandle GDKContext;`
- L91 _private member_ `const TArray<FString> StringArrayToSanitize;`
- L92 _private member_ `TArray<FString> SanitizedStringArray;`
- L94 _private member_ `FOnlineAsyncTaskGDKSanitizeMultipleStringsComplete Delegate;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnlineAsyncTaskGDKSanitizeSingleStringComplete, bool , const FString& );` — Delegate used when the single string has been sanitized @param bSuccess if this delegate is successful @param SanitizedString The sanitized string returned
- L18 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnlineAsyncTaskGDKSanitizeSingleStringComplete, bool , const FString& );` — Delegate used when the single string has been sanitized @param bSuccess if this delegate is successful @param SanitizedString The sanitized string returned
- L61 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnlineAsyncTaskGDKSanitizeMultipleStringsComplete, bool , const TArray<FString>& );` — Delegate used when the array of strings has been sanitized @param bSuccess if this delegate is successful @param SanitizedStrings The sanitized string's array returned
- L61 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnlineAsyncTaskGDKSanitizeMultipleStringsComplete, bool , const TArray<FString>& );` — Delegate used when the array of strings has been sanitized @param bSuccess if this delegate is successful @param SanitizedStrings The sanitized string's array returned

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKSendSessionInviteToFriends.h` (Private)


#### class `FOnlineAsyncTaskGDKSendSessionInviteToFriends`  
`class FOnlineAsyncTaskGDKSendSessionInviteToFriends : public FOnlineAsyncTaskGDK`  
_L13-33_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to send a session invite to friends
- L17 _public prototype_ `FOnlineAsyncTaskGDKSendSessionInviteToFriends(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InGDKContext, FGDKMultiplayerSessionHandle InGDKSession, const TArray<uint64>& InFriendsToInvite);`
- L21 _public prototype_ `virtual ~FOnlineAsyncTaskGDKSendSessionInviteToFriends() = default;`
- L24 _public function_ `virtual FString ToString() const override`
- L26 _public prototype_ `virtual void Initialize() override;`
- L27 _public prototype_ `virtual void ProcessResults() override;`
- L30 _protected member_ `FGDKMultiplayerSessionHandle GDKSession;`
- L31 _protected member_ `TArray<uint64> FriendsToInvite;`
- L32 _protected member_ `FGDKContextHandle GDKContext;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKSessionBase.h` (Private)


#### class `FOnlineAsyncTaskGDKSessionBase`  
`class FOnlineAsyncTaskGDKSessionBase : public FOnlineAsyncTaskGDK`  
_L16-55_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task base class for session related operations
- L19 _public prototype_ `FOnlineAsyncTaskGDKSessionBase( class FOnlineSubsystemGDK* GDKSubsystem, const FString& AsyncTaskName, int32 InUserIndex, FName SessionName, const FOnlineSessionSettings& NewSessionSettings );`
- L28 _public prototype_ `FOnlineAsyncTaskGDKSessionBase( FOnlineAsyncTaskGDKSessionBase* PreviousTask );` — . Copy constructor for new tasks based on old (e.g. Matchmaking advertisements)
- L30 _public prototype_ `virtual ~FOnlineAsyncTaskGDKSessionBase();`
- L32 _public prototype_ `virtual bool SettingsAreValid();`
- L34 _public function_ `const FName& GetSessionName()`
- L37 _protected prototype_ `void ParseSessionSettings( FOnlineSessionSettings* InSessionSettings );`
- L38 _protected prototype_ `void ParseSearchSettings( const FOnlineSessionSearch* InSearchSettings );`
- L41 _protected member_ `FGDKMultiplayerSessionHandle GDKSession;`
- L42 _protected member_ `FOnlineSessionSettings SessionSettings;`
- L43 _protected member_ `FName SessionName;`
- L44 _protected member_ `FString SessionTemplateName;`
- L45 _protected member_ `uint32 SessionMaxSeats;`
- L47 _protected member_ `FString MatchHopperName;`
- L48 _protected member_ `FString MatchTicketAttributes;`
- L49 _protected member_ `float MatchTimeout;`
- L51 _protected member_ `bool ClientMatchmakingCapable;`
- L52 _protected member_ `bool PartyEnabledSession;`
- L53 _protected member_ `FString CustomConstantsJson;`
- L54 _protected member_ `TArray<uint64> InitiatorUserIds;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKSetPresence.h` (Private)


#### class `FOnlineAsyncTaskGDKSetPresence`  
`class FOnlineAsyncTaskGDKSetPresence : public FOnlineAsyncTaskGDK`  
_L14-44_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to write achievements
- L18 _public prototype_ `FOnlineAsyncTaskGDKSetPresence( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, const FOnlineUserPresenceStatus& InPresenceStatus, const FString& InPresenceIdString, const FOnSetGDKPresenceCompleteDelegate& InTaskCompletionDelegate );`
- L26 _public prototype_ `virtual ~FOnlineAsyncTaskGDKSetPresence() = default;`
- L29 _public function_ `virtual FString ToString() const override`
- L32 _public prototype_ `virtual void Initialize() override;` — Starts in Game Thread
- L34 _public prototype_ `virtual void ProcessResults() override;` — Process in Online Thread
- L37 _public prototype_ `virtual void TriggerDelegates() override;` — Move results and trigger delegates in Game Thread
- L40 _protected member_ `FGDKContextHandle GDKContext;`
- L41 _protected member_ `const FOnSetGDKPresenceCompleteDelegate TaskCompletionDelegate;`
- L42 _protected member_ `const FOnlineUserPresenceStatus PresenceStatus;`
- L43 _protected member_ `const FString PresenceIdString;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKSetSessionActivity.h` (Private)


#### class `FOnlineAsyncTaskGDKSetSessionActivity`  
`class FOnlineAsyncTaskGDKSetSessionActivity : public FOnlineAsyncTaskGDK`  
_L13-34_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to set the current session for a user
- L17 _public prototype_ `FOnlineAsyncTaskGDKSetSessionActivity(FOnlineSubsystemGDK* InGDKSubsystem, FGDKContextHandle InGDKContext, FGDKMultiplayerSessionHandle GDKSession);`
- L21 _public prototype_ `virtual ~FOnlineAsyncTaskGDKSetSessionActivity() = default;`
- L24 _public function_ `virtual FString ToString() const override`
- L26 _public prototype_ `virtual void Initialize() override;`
- L27 _public prototype_ `virtual void ProcessResults() override;`
- L29 _public prototype_ `virtual void TriggerDelegates() override;`
- L32 _protected member_ `FGDKMultiplayerSessionHandle GDKSession;`
- L33 _protected member_ `FGDKContextHandle GDKContext;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKShowAchievementsUI.h` (Private)


#### class `FOnlineAsyncTaskGDKShowAchievementsUI`  
`class FOnlineAsyncTaskGDKShowAchievementsUI : public FOnlineAsyncTaskGDK`  
_L14-42_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to write achievements
- L18 _public prototype_ `FOnlineAsyncTaskGDKShowAchievementsUI( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, FGDKUserHandle InGDKUser, const FOnQueryGDKShowAchievementsUICompleteDelegate& InTaskCompletionDelegate );`
- L25 _public prototype_ `virtual ~FOnlineAsyncTaskGDKShowAchievementsUI() = default;`
- L28 _public function_ `virtual FString ToString() const override`
- L31 _public prototype_ `virtual void Initialize() override;` — Starts in Game Thread
- L33 _public prototype_ `virtual void ProcessResults() override;` — Process in Online Thread
- L36 _public prototype_ `virtual void TriggerDelegates() override;` — Move results and trigger delegates in Game Thread
- L39 _protected member_ `FGDKContextHandle GDKContext;`
- L40 _protected member_ `const FOnQueryGDKShowAchievementsUICompleteDelegate TaskCompletionDelegate;`
- L41 _protected member_ `FGDKUserHandle GDKUser;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKShowLoginUI.h` (Private)


#### class `FOnlineAsyncTaskGDKShowLoginUI`  
`class FOnlineAsyncTaskGDKShowLoginUI : public FOnlineAsyncTaskGDK`  
_L14-39_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to write achievements
- L18 _public prototype_ `FOnlineAsyncTaskGDKShowLoginUI( FOnlineSubsystemGDK* InGDKInterface, bool bAllowGuestLogin, const FOnQueryGDKShowLoginUICompleteDelegate& InTaskCompletionDelegate);`
- L23 _public prototype_ `virtual ~FOnlineAsyncTaskGDKShowLoginUI() = default;`
- L26 _public function_ `virtual FString ToString() const override`
- L29 _public prototype_ `virtual void Initialize() override;` — Starts in Game Thread
- L32 _public prototype_ `virtual void TriggerDelegates() override;` — Move results and trigger delegates in Game Thread
- L35 _protected member_ `const FOnQueryGDKShowLoginUICompleteDelegate TaskCompletionDelegate;`
- L36 _protected member_ `FGDKUserHandle NewUser;`
- L37 _protected member_ `HRESULT hResult;`
- L38 _protected member_ `bool bAllowGuestLogin;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKShowProfileUI.h` (Private)


#### class `FOnlineAsyncTaskGDKShowProfileUI`  
`class FOnlineAsyncTaskGDKShowProfileUI : public FOnlineAsyncTaskGDK`  
_L14-44_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to write achievements
- L18 _public prototype_ `FOnlineAsyncTaskGDKShowProfileUI( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, FGDKUserHandle InGDKUser, uint64 InTargetUser, const FOnQueryGDKShowProfileUICompleteDelegate& InTaskCompletionDelegate );`
- L26 _public prototype_ `virtual ~FOnlineAsyncTaskGDKShowProfileUI() = default;`
- L29 _public function_ `virtual FString ToString() const override`
- L32 _public prototype_ `virtual void Initialize() override;` — Starts in Game Thread
- L34 _public prototype_ `virtual void ProcessResults() override;` — Process in Online Thread
- L37 _public prototype_ `virtual void TriggerDelegates() override;` — Move results and trigger delegates in Game Thread
- L40 _protected member_ `FGDKContextHandle GDKContext;`
- L41 _protected member_ `const FOnQueryGDKShowProfileUICompleteDelegate TaskCompletionDelegate;`
- L42 _protected member_ `FGDKUserHandle GDKUser;`
- L43 _protected member_ `uint64 TargetUser;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKShowSendGameInvitesUI.h` (Private)


#### class `FOnlineAsyncTaskGDKShowSendGameInvitesUI`  
`class FOnlineAsyncTaskGDKShowSendGameInvitesUI : public FOnlineAsyncTaskGDK`  
_L14-42_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to write achievements
- L18 _public prototype_ `FOnlineAsyncTaskGDKShowSendGameInvitesUI( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, FGDKMultiplayerSessionHandle InGDKSession, const FOnQueryGDKShowSendGameInvitesUICompleteDelegate& InTaskCompletionDelegate );`
- L25 _public prototype_ `virtual ~FOnlineAsyncTaskGDKShowSendGameInvitesUI() = default;`
- L28 _public function_ `virtual FString ToString() const override`
- L31 _public prototype_ `virtual void Initialize() override;` — Starts in Game Thread
- L33 _public prototype_ `virtual void ProcessResults() override;` — Process in Online Thread
- L36 _public prototype_ `virtual void TriggerDelegates() override;` — Move results and trigger delegates in Game Thread
- L39 _protected member_ `FGDKContextHandle GDKContext;`
- L40 _protected member_ `const FOnQueryGDKShowAchievementsUICompleteDelegate TaskCompletionDelegate;`
- L41 _protected member_ `FGDKMultiplayerSessionHandle GDKSession;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKShowStoreUI.h` (Private)


#### class `FOnlineAsyncTaskGDKShowStoreUI`  
`class FOnlineAsyncTaskGDKShowStoreUI : public FOnlineAsyncTaskGDK`  
_L21-50_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to write achievements
- L25 _public prototype_ `FOnlineAsyncTaskGDKShowStoreUI( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, const FShowStoreParams& InShowParams, const FOnQueryGDKShowStoreUICompleteDelegate& InTaskCompletionDelegate );`
- L32 _public prototype_ `virtual ~FOnlineAsyncTaskGDKShowStoreUI() = default;`
- L35 _public function_ `virtual FString ToString() const override`
- L38 _public prototype_ `virtual void Tick() override;` — Starts in Game Thread
- L40 _public prototype_ `virtual void ProcessResults() override;` — Process in Online Thread
- L43 _public prototype_ `virtual void TriggerDelegates() override;` — Move results and trigger delegates in Game Thread
- L46 _protected member_ `FGDKContextHandle GDKContext;`
- L47 _protected member_ `const FOnQueryGDKShowStoreUICompleteDelegate TaskCompletionDelegate;`
- L48 _protected member_ `const FShowStoreParams ShowParams;`
- L49 _protected member_ `bool bTaskStarted = false;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKStatsQuery.h` (Private)


#### class `FOnlineAsyncTaskGDKStatsQuery`  
`class FOnlineAsyncTaskGDKStatsQuery : public FOnlineAsyncTaskGDK`  
_L15-34_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to query stats
- L18 _public prototype_ `FOnlineAsyncTaskGDKStatsQuery( FOnlineSubsystemGDK* const InGDKSubsystem, FGDKContextHandle InGDKContext, const int32 InUserIndex, const TUniqueNetIdMap<uint64>& InUserMapping, const FOnlineStatsQueryUserStatsComplete& InDelegate );`
- L19 _public prototype_ `FOnlineAsyncTaskGDKStatsQuery( FOnlineSubsystemGDK* const InGDKSubsystem, FGDKContextHandle InGDKContext, const int32 InUserIndex, const TUniqueNetIdMap<uint64>& InUserMapping, const TArray<FString>& InStatNames, const FOnlineStatsQueryUsersStatsComplete& InDelegate );`
- L20 _public function_ `virtual FString ToString() const override`
- L21 _public prototype_ `virtual void Initialize() override;`
- L22 _public prototype_ `virtual void TriggerDelegates() override;`
- L23 _public prototype_ `virtual void ProcessResults() override;`
- L26 _protected member_ `TUniqueNetIdMap<uint64> UserMapping;`
- L27 _protected member_ `TArray<FString> StatNames;`
- L28 _protected member_ `FGDKContextHandle GDKContext;`
- L30 _protected member_ `TArray<TSharedRef<const FOnlineStatsUserStats>> UserStatsResult;`
- L32 _protected member_ `FOnlineStatsQueryUserStatsComplete SingleUserDelegate;`
- L33 _protected member_ `FOnlineStatsQueryUsersStatsComplete MultipleUsersDelegate;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKStatsUpdate.h` (Private)


#### class `FOnlineAsyncTaskGDKStatsUpdate`  
`class FOnlineAsyncTaskGDKStatsUpdate : public FOnlineAsyncTaskGDK`  
_L14-33_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async Task to upload updated stats to service
- L17 _public prototype_ `FOnlineAsyncTaskGDKStatsUpdate(FOnlineSubsystemGDK* const InGDKSubsystem, FGDKContextHandle InUserContext, const TArray<FOnlineStatsUserUpdatedStats>& InUpdatedUserStats, const FOnlineStatsUpdateStatsComplete& InDelegate, const TMap<FUniqueNetIdGDKRef, uint64>& InGDKUserMapping);`
- L19 _public function_ `virtual FString ToString() const override`
- L21 _public prototype_ `virtual void Initialize() override;`
- L22 _public prototype_ `virtual void ProcessResults() override;`
- L23 _public prototype_ `virtual void TriggerDelegates() override;`
- L26 _private prototype_ `HRESULT UpdateAllUserStats(FUniqueNetIdGDKRef GDKId);`
- L29 _private member_ `FGDKContextHandle GDKContext;`
- L30 _private member_ `const TArray<FOnlineStatsUserUpdatedStats> UpdatedUserStats;`
- L31 _private member_ `TMap<FUniqueNetIdGDKRef, uint64> GDKUserMapping;`
- L32 _private member_ `FOnlineStatsUpdateStatsComplete Delegate;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKSubmitMatchTicket.h` (Private)


#### class `FOnlineAsyncTaskGDKSubmitMatchTicket`  
`class FOnlineAsyncTaskGDKSubmitMatchTicket : public FOnlineAsyncTaskGDK`  
_L18-55_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task that creates a matchmaking ticket and submits it.
- L21 _public prototype_ `FOnlineAsyncTaskGDKSubmitMatchTicket( FOnlineSubsystemGDK* InSubsystem, uint64 InSearchingUser, FName InSessionName, FGDKMultiplayerSessionHandle InGDKSession, const FString& InHopperName, const FString& InTicketAttributes, uint64 InTicketTimeout, XblPreserveSessionMode InTicketPreservation, bool InCancelExistingTicket);`
- L32 _public prototype_ `virtual void Initialize() override;`
- L34 _public function_ `virtual FString ToString() const override`
- L35 _public prototype_ `virtual void Finalize() override;`
- L36 _public prototype_ `virtual void TriggerDelegates() override;`
- L37 _public prototype_ `virtual void ProcessResults() override;`
- L39 _private prototype_ `void CreateMatchmakingTicket();`
- L41 _private member_ `uint64 SearchingUser;`
- L42 _private member_ `FName SessionName;`
- L43 _private member_ `FGDKMultiplayerSessionHandle MatchGDKSession;`
- L44 _private member_ `FString HopperName;`
- L45 _private member_ `FString TicketAttributes;`
- L46 _private member_ `uint64 TicketTimeout;`
- L47 _private member_ `XblPreserveSessionMode TicketPreservation;`
- L48 _private member_ `bool CancelExistingTicket;`
- L50 _private member_ `FString TicketIdToCancel;`
- L51 _private member_ `XblCreateMatchTicketResponse* Response = nullptr;`
- L52 _private member_ `XAsyncBlock DeleteAsyncBlock;`
- L53 _private member_ `FString ResultTicketId;`
- L54 _private member_ `float ResultWaitTime;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKUnregisterLocalUser.h` (Private)


#### class `FOnlineAsyncTaskGDKUnregisterLocalUser`  
`class FOnlineAsyncTaskGDKUnregisterLocalUser : public FOnlineAsyncTaskGDKSafeWriteSession`  
_L12-34_
- inherits: `FOnlineAsyncTaskGDKSafeWriteSession`
- desc: Async task used to have another local user Leave() a Live session.
- L15 _public prototype_ `FOnlineAsyncTaskGDKUnregisterLocalUser( FOnlineSubsystemGDK* const InSubsystem, FGDKContextHandle InContext, const FName InSessionName, FGDKMultiplayerSessionHandle InGDKSession, const FUniqueNetIdGDKRef& InUserId, const FOnUnregisterLocalPlayerCompleteDelegate& InDelegate);`
- L24 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L25 _public prototype_ `virtual void TriggerDelegates() override;`
- L30 _private prototype_ `virtual bool UpdateSession(FGDKMultiplayerSessionHandle Session);` — FOnlineAsyncTaskGDKSafeWriteSession
- L32 _private member_ `FUniqueNetIdGDKRef UserId;`
- L33 _private member_ `FOnUnregisterLocalPlayerCompleteDelegate Delegate;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKUpdateSession.h` (Private)


#### class `FOnlineAsyncTaskGDKUpdateSession`  
`class FOnlineAsyncTaskGDKUpdateSession : public FOnlineAsyncTaskGDKSafeWriteSession`  
_L10-42_
- inherits: `FOnlineAsyncTaskGDKSafeWriteSession`
- L23 _public prototype_ `FOnlineAsyncTaskGDKUpdateSession( FOnlineSubsystemGDK* const InSubsystem, FGDKContextHandle InContext, const FName InSessionName, const FOnlineSessionSettings& InUpdatedSessionSettings, const int32 InMaxRetryCount);` — This constructor takes the Live SessionReference directly and is safe to call in non-game threads. @param InSubsystem the owning GDK online subsystem @param InContext the GDK context of the user who's updating the session @param InSessionName the name of the session to update @param InUpdatedSessionSettings the session settings to write to the session object @param InMaxRetryCount Maximum number of times to retry the session write
- L31 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L34 _protected prototype_ `virtual void Initialize() override;`
- L36 _protected prototype_ `virtual bool UpdateSession(FGDKMultiplayerSessionHandle Session) override;`
- L38 _protected prototype_ `virtual void Finalize() override;`
- L39 _protected prototype_ `virtual void TriggerDelegates() override;`
- L41 _protected member_ `FOnlineSessionSettings UpdatedSessionSettings;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKUpdateSessionMember.h` (Private)


#### class `FOnlineAsyncTaskGDKUpdateSessionMember`  
`class FOnlineAsyncTaskGDKUpdateSessionMember : public FOnlineAsyncTaskGDKSafeWriteSession`  
_L7-37_
- inherits: `FOnlineAsyncTaskGDKSafeWriteSession`
- L20 _public prototype_ `FOnlineAsyncTaskGDKUpdateSessionMember( FOnlineSubsystemGDK* const InSubsystem, FGDKContextHandle InContext, const FName InSessionName, FGDKMultiplayerSessionHandle InGDKSession, const int32 InMaxRetryCount);` — This constructor takes the GDK Session directly and is safe to call in non-game threads. @param InSubsystem the owning GDK online subsystem @param InContext the GDK context of the user who's updating the session @param InSessionName the name of the session to update @param InGDKSession the GDK session we're writing to @param InMaxRetryCount number of times to retry the session write
- L28 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L32 _protected prototype_ `virtual bool UpdateSession(FGDKMultiplayerSessionHandle Session) override;`
- L34 _protected prototype_ `virtual void TriggerDelegates();`
- L36 _protected member_ `FName SessionIdentifier;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/AsyncTasks/OnlineAsyncTaskGDKWriteAchievements.h` (Private)


#### class `FOnlineAsyncTaskGDKWriteAchievements`  
`class FOnlineAsyncTaskGDKWriteAchievements : public FOnlineAsyncTaskGDK`  
_L14-53_
- inherits: `FOnlineAsyncTaskGDK`
- desc: Async task to write achievements
- L18 _public prototype_ `FOnlineAsyncTaskGDKWriteAchievements( FOnlineSubsystemGDK* InGDKInterface, FGDKContextHandle InGDKContext, const FUniqueNetIdGDKRef& InUserIdGDK, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& InDelegate );`
- L26 _public prototype_ `virtual ~FOnlineAsyncTaskGDKWriteAchievements() = default;`
- L29 _public function_ `virtual FString ToString() const override`
- L32 _public prototype_ `virtual void Initialize() override;` — Starts in Game Thread
- L35 _public prototype_ `void HandleWriteAchievementComplete(FString AchievementName);` — Process in Online Thread
- L38 _public prototype_ `virtual void Tick() override;` — Tick to check that all subtasks have completed
- L41 _public prototype_ `virtual void TriggerDelegates() override;` — Trigger delegates in Game Thread
- L44 _protected member_ `FUniqueNetIdGDKRef UserIdGDK;`
- L45 _protected member_ `FGDKContextHandle GDKContext;`
- L46 _protected member_ `const FOnAchievementsWrittenDelegate TaskCompletionDelegate;`
- L47 _protected member_ `FOnlineAchievementsWriteRef WriteObjectRef;`
- L48 _protected member_ `FStatPropertyArray AchievementDataArray;`
- L50 _protected member_ `bool bErrorProcessingAPICalls;`
- L51 _protected member_ `uint32 NumOutstandingAPICalls;`
- L52 _protected member_ `TMap<FString, FGDKAsyncBlockPtr> AsyncBlocksByAchievementName;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/HCTraceHandler.h` (Private)


#### struct `FHCTraceHandler`  
`struct FHCTraceHandler`  
_L11-11_
- L23 _public prototype_ `FHCTraceHandler();`
- L24 _public prototype_ `~FHCTraceHandler();`
- L28 _private prototype_ `void OnLogVerbosityChanged(const FLogCategoryName& CategoryName, ELogVerbosity::Type OldVerbosity, ELogVerbosity::Type NewVerbosity);`
- L29 _private prototype_ `static void TraceCallback(const char* AreaName, HCTraceLevel TraceLevel, uint64_t ThreadId, uint64_t Timestamp, const char* Message);`
- L30 _private prototype_ `HCTraceLevel GetTraceLevel(ELogVerbosity::Type Verbosity);`
- L32 _private member_ `FDelegateHandle OnLogVerbosityChangedHandle;`

#### struct `FHCTraceHandler`  
`struct FHCTraceHandler`  
_L21-33_
- L23 _public prototype_ `FHCTraceHandler();`
- L24 _public prototype_ `~FHCTraceHandler();`
- L28 _private prototype_ `void OnLogVerbosityChanged(const FLogCategoryName& CategoryName, ELogVerbosity::Type OldVerbosity, ELogVerbosity::Type NewVerbosity);`
- L29 _private prototype_ `static void TraceCallback(const char* AreaName, HCTraceLevel TraceLevel, uint64_t ThreadId, uint64_t Timestamp, const char* Message);`
- L30 _private prototype_ `HCTraceLevel GetTraceLevel(ELogVerbosity::Type Verbosity);`
- L32 _private member_ `FDelegateHandle OnLogVerbosityChangedHandle;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/MessageSanitizerGDK.h` (Private)


#### class `FMessageSanitizerGDK`  
`class FMessageSanitizerGDK : public IMessageSanitizer`  
_L16-94_
- inherits: `IMessageSanitizer`
- desc: Implements the GDK specific interface chat message sanitization
- L23 _public prototype_ `virtual void SanitizeDisplayName(const FString& DisplayName, const FOnMessageProcessed& CompletionDelegate) override;` — IMessageSanitizer
- L24 _public prototype_ `virtual void SanitizeDisplayNames(const TArray<FString>& DisplayNames, const FOnMessageArrayProcessed& CompletionDelegate) override;`
- L25 _public prototype_ `virtual void QueryBlockedUser(int32 LocalUserNum, const FString& FromUserIdStr, const FString& FromPlatform, const FOnQueryUserBlockedResponse& InCompletionDelegate) override;`
- L26 _public prototype_ `virtual void ResetBlockedUserCache() override;`
- L29 _public prototype_ `explicit FMessageSanitizerGDK(FOnlineSubsystemGDK* InGDKSubsystem);`
- L30 _public prototype_ `virtual ~FMessageSanitizerGDK();`
- L34 _private prototype_ `void HandleAppResume();`
- L35 _private prototype_ `void HandleAppReactivated();`
- L36 _private prototype_ `void OnQueryBlockedUserComplete(const FOnlineError& RequestStatus, const FUniqueNetIdRef& RequestingUser, const FCommunicationPermissionResultsMap& Results, FOnQueryUserBlockedResponse CompletionDelegate);`
- L37 _private prototype_ `void OnQueryCrossPlatformPermissionsComplete(const FOnlineError& RequestStatus, const FAnonymousUserCommunicationPermissionResultsMap& Results, const FUniqueNetIdRef RequestingUser, const TArray<FString> OtherPlatformIds, FOnQueryUserBlockedResponse CompletionDelegate);`
- L39 _private member_ `FDelegateHandle AppResumeDelegateHandle;`
- L40 _private member_ `FDelegateHandle AppReactivatedDelegateHandle;`
- L43 _private member_ `FOnlineSubsystemGDK* GDKSubsystem;` — Reference to the main GDK subsystem
- L83 _private member_ `TMap<FString, FBlockedUserData> UserBlockData;` — Mapping of all local users to the block data for remote users
- L87 _private prototype_ `void HandleMessageSanitized(bool bSuccess, const FString& SanitizedString, FOnMessageProcessed CompletionDelegate, FString UnsanitazedString);` — Handle the sanitized strings and trigger completion delegates
- L88 _private prototype_ `void HandleMessageArraySanitized(bool bSuccess, const TArray<FString>& SanitizedArrayMessage, FOnMessageArrayProcessed CompletionDelegate, TArray<FString> AlreadyProcessedMessages, TArray<int32> AlreadyProcessedIndex, TArray<FString> UnsanitizedArrayMessage);`
- L92 _private member_ `TMap<FString, FString> WordMap;` — Holds a map of sanitized words

#### struct `FMessageSanitizerGDK::FRemoteUserBlockInfo`  
`struct FRemoteUserBlockInfo`  
_L45-72_
- L47 _public function_ `FRemoteUserBlockInfo() : State(EOnlineAsyncTaskState::NotStarted) , bIsBlocked(false) , bIsBlockedNonFriends(false) , bIsSamePlatform(true)`
- L55 _public member_ `FString RemoteUserId;` — Remote user id
- L58 _public member_ `EOnlineAsyncTaskState::Type State;` — State of the query
- L61 _public member_ `bool bIsBlocked;` — Is this user blocked, valid only if bIsComplete is true
- L63 _public member_ `bool bIsBlockedNonFriends;` — Is this user blocked only for non-friends, valid only if bIsComplete is true
- L65 _public member_ `bool bIsSamePlatform;` — True if this user is on the same platform. ie. GDK
- L68 _public member_ `TArray<FOnQueryUserBlockedResponse> Delegates;` — Delegates to fire when the query is complete, should only be filled while bIsComplete is false
- L71 _public prototype_ `void UpdatePermission(bool bSucceeded, bool bInIsBlocked, bool bIsBlockedNonFriends);` — Handle updated permission and trigger delegates

#### struct `FMessageSanitizerGDK::FBlockedUserData`  
`struct FBlockedUserData`  
_L74-80_
- L77 _public member_ `FString LocalUserId;` — Local user id
- L79 _public member_ `TMap<FString, FRemoteUserBlockInfo> RemoteUserData;` — Mapping from remote users to their cached info

#### Free symbols / members of external scopes

- L96 _typedef_ `typedef TSharedPtr<FMessageSanitizerGDK, ESPMode::ThreadSafe> FMessageSanitizerGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlineAchievementsInterfaceGDK.h` (Private)


#### enum `EGDKAchievementMode`  
`enum class EGDKAchievementMode : uint16`  
_L20-29_
- L23 _public enumerator_ `Mode2013 = 2013` — 2013 stats are driven via events
- L25 _public enumerator_ `Mode2017 = 2017` — 2017 stats are title-managed
- L28 _public enumerator_ `Default = Mode2013` — Default mode to use if not specified

#### class `FAchievementsConfig`  
`class FAchievementsConfig : public FJsonSerializable`  
_L31-41_
- inherits: `FJsonSerializable`
- L34 _public member_ `FString AchievementEventName;`
- L35 _public member_ `FJsonSerializableKeyValueMapInt AchievementMap;`

#### class `FOnlineAchievementsGDK`  
`class FOnlineAchievementsGDK : public IOnlineAchievements, public TSharedFromThis< FOnlineAchievementsGDK, ESPMode::ThreadSafe>`  
_L51-193_
- inherits: `IOnlineAchievements,TSharedFromThis<FOnlineAchievementsGDK,ESPMode::ThreadSafe>`
- desc: FOnlineAchievementsGDK - Interface class for achievements (GDK implementation)
- L55 _private prototype_ `void GetAchievementModeFromConfig();`
- L56 _private prototype_ `bool LoadAndInitFromJsonConfig( const TCHAR* JsonConfigName );`
- L57 _private prototype_ `void TestEventsAndAchievements();`
- L60 _private member_ `class FOnlineSubsystemGDK * GDKSubsystem;` — Pointer to owning live subsystem
- L63 _private member_ `FAchievementsConfig AchievementsConfig;` — Config settings initialized from json file
- L66 _private member_ `TUniqueNetIdMap<TArray<FOnlineAchievement>> PlayerAchievements;` — Mapping of players to their achievements
- L69 _private member_ `TMap<FString, FOnlineAchievementDesc> AchievementDescriptions;` — Cached achievement descriptions for an Id
- L71 _private member_ `const FOnAchievementsWrittenDelegate* OnAchievementsWrittenDelegate = nullptr;`
- L72 _private member_ `const FOnAchievementsWrittenDelegate* OnAchievementsQueriedDelegate = nullptr;`
- L80 _public member_ `EGDKAchievementMode AchievementMode;` — What version of achievements do we use for unlocking achievements?
- L84 _public prototype_ `virtual void WriteAchievements(const FUniqueNetId& PlayerId, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& Delegate = FOnAchievementsWrittenDelegate()) override;`
- L85 _public prototype_ `virtual void QueryAchievements(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate()) override;`
- L86 _public prototype_ `virtual void QueryAchievementDescriptions( const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate() ) override;`
- L87 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievement(const FUniqueNetId& PlayerId, const FString& AchievementId, FOnlineAchievement& OutAchievement) override;`
- L88 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievements(const FUniqueNetId& PlayerId, TArray<FOnlineAchievement> & OutAchievements) override;`
- L89 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievementDescription(const FString& AchievementId, FOnlineAchievementDesc& OutAchievementDesc) override;`
- L91 _public prototype_ `virtual bool ResetAchievements( const FUniqueNetId& PlayerId ) override;`
- L100 _public prototype_ `FOnlineAchievementsGDK(class FOnlineSubsystemGDK* InSubsystem);` — Constructor @param InSubsystem - A reference to the owning subsystem
- L106 _public prototype_ `virtual ~FOnlineAchievementsGDK();` — Default destructor
- L108 _public function_ `int32 GetAchievementIdFromName(const FString& AchievementName)`
- L120 _public function_ `const FString& GetAchievementNameFromId(int32 AchievementId)`
- L132 _public function_ `const FString& GetAchievementEventName()`
- L142 _public prototype_ `void HandleQueryGDKAchievementComplete(const FUniqueNetId& PlayerNetId, bool isSuccess, const TArray<XblAchievement>& AchievementArray, FOnQueryAchievementsCompleteDelegate Delegate);`
- L192 _private prototype_ `void ProcessGetAchievementsResults(const TArray<XblAchievement*>& AllAchievements, FUniqueNetIdGDKRef UserGDK, const FOnQueryAchievementsCompleteDelegate Delegate);` — Process the AchievementsResult and query for the next "page" of results if necessary

#### class `FOnlineAchievementsGDK::FAsyncEventQueryCompleted`  
`class FAsyncEventQueryCompleted : public FOnlineAsyncEvent<FOnlineSubsystemGDK>`  
_L148-189_
- inherits: `FOnlineAsyncEvent<FOnlineSubsystemGDK>`
- desc: Async event that notifies when a Query achievements operation has completed.
- L151 _private function_ `FAsyncEventQueryCompleted() : FOnlineAsyncEvent(nullptr) , PlayerId(FUniqueNetIdGDK::EmptyId())` — Hidden on purpose
- L158 _private member_ `FUniqueNetIdGDKRef PlayerId;` — The user who made the request
- L160 _private member_ `TArray<XblAchievement*> Achievements;`
- L163 _private member_ `bool bWasSuccessful;` — True if the set presence operation succeeded, false if it didn't.
- L166 _private member_ `FOnQueryAchievementsCompleteDelegate Delegate;` — Delegate to execute on the game thread to notify it that the operation is complete.
- L177 _public function_ `FAsyncEventQueryCompleted(FOnlineSubsystemGDK* InGDKSubsystem, const FUniqueNetIdGDKRef& InPlayerId, const TArray<XblAchievement*>& InAchievements, bool InWasSuccessful, const FOnQueryAchievementsCompleteDelegate& InDelegate) : FOnlineAsyncEvent(InGDKSubsystem) , PlayerId(InPlayerId) , Achievements(InAchievements) , bWasSuccessful(InWasSuccessful) , Delegate(InDelegate)` — Constructor. @param InGDKSubsystem The owner of the external UI interface that triggered this event. @param InUsers The users whose presence was retrieved. @param InRecord The presence information for the user. @param InWasSuccessful True if the set presence operation succeeded, false if it didn't.
- L186 _public prototype_ `virtual void Finalize() override;`
- L187 _public prototype_ `virtual FString ToString() const override;`
- L188 _public prototype_ `virtual void TriggerDelegates() override;`

#### Free symbols / members of external scopes

- L18 _variable_ `const int32 INVALID_ACHIEVEMENT_ID = -1;`
- L46 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnQueryGDKAchievementCompleteDelegate, const FUniqueNetId&, bool, const TArray<XblAchievement>&);` — Delegate fired when an achievement has been queried
- L46 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnQueryGDKAchievementCompleteDelegate, const FUniqueNetId&, bool, const TArray<XblAchievement>&);` — Delegate fired when an achievement has been queried
- L195 _typedef_ `typedef TSharedPtr<FOnlineAchievementsGDK, ESPMode::ThreadSafe> FOnlineAchievementsGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlineAsyncTaskManagerGDK.h` (Private)


#### class `FOnlineAsyncTaskGDK`  
`class FOnlineAsyncTaskGDK : public FOnlineAsyncTaskBasic<FOnlineSubsystemGDK>, public TSharedFromThis<FOnlineAsyncTaskGDK, ESPMode::ThreadSafe>`  
_L28-108_
- inherits: `FOnlineAsyncTaskBasic<FOnlineSubsystemGDK>,TSharedFromThis<FOnlineAsyncTaskGDK,ESPMode::ThreadSafe>`
- desc: Base class that holds a delegate to fire when a given async task is complete
- L33 _private member_ `TArray<FGDKAsyncBlockPtr> AsyncBlocks;`
- L34 _private member_ `FGDKAsyncBlockPtr AsyncBlock;`
- L35 _private member_ `FString AsyncTaskName;`
- L39 _public prototype_ `FOnlineAsyncTaskGDK() = delete;` — Hidden on purpose
- L41 _public prototype_ `explicit FOnlineAsyncTaskGDK(FOnlineSubsystemGDK* const InGDKSubsystem, const FString& InAsyncTaskName, const int32 InUserIndex = -1);`
- L43 _public prototype_ `virtual ~FOnlineAsyncTaskGDK();`
- L45 _public function_ `virtual void ProcessResults()`
- L50 _public prototype_ `FGDKAsyncBlockPtr CreateAsyncBlock(void* UserData, FGDKAsyncBlockDelegate Delegate);` — Create a new async block for an async GDK call.
- L55 _public function_ `void RemoveAsyncBlock(FGDKAsyncBlockPtr InAsyncBlock)` — Create a new async block for an async GDK call.
- L63 _public function_ `FGDKAsyncBlockPtr FindAsyncBlock(XAsyncBlock* InAsyncBlock)`
- L79 _public function_ `FGDKAsyncBlockPtr CreateAsyncBlock()` — Create a new async block for an async GDK call, with settings set to defaults for OnlineAsyncTaskGDK
- L89 _public function_ `virtual void Initialize() override` — Handle start-up/initialize code here.  This is ran on the Game Thread the tick before the first call to Tick().
- L96 _public function_ `virtual void Tick() override` — Handle processing/updating the task here.  This is ran on the Online Thread.
- L103 _public prototype_ `virtual void CancelWhenTimeout() override;` — Cancel when timeout if timeout is set for this task
- L106 _private member_ `TOptional<double> TimeoutInSeconds;`
- L107 _private member_ `bool bCancelled = false;`

#### class `FOnlineAsyncTaskManagerGDK`  
`class FOnlineAsyncTaskManagerGDK : public FOnlineAsyncTaskManager`  
_L113-135_
- inherits: `FOnlineAsyncTaskManager`
- desc: GDK version of the async task manager to register the various Live callbacks with the engine
- L118 _protected member_ `FOnlineSubsystemGDK* GDKSubsystem;` — Cached reference to the main online subsystem
- L120 _protected member_ `FGDKAsyncTaskQueue OnlineTasksQueue;`
- L124 _public function_ `FOnlineAsyncTaskManagerGDK(FOnlineSubsystemGDK* InOnlineSubsystem) : GDKSubsystem(InOnlineSubsystem)`
- L129 _public function_ `XTaskQueueHandle GetGDKTaskQueue()`
- L131 _public prototype_ `virtual ~FOnlineAsyncTaskManagerGDK();`
- L134 _public prototype_ `virtual void OnlineTick() override;` — FOnlineAsyncTaskManager

#### Free symbols / members of external scopes

- L23 _typedef_ `typedef TSharedPtr<FGDKAsyncBlock> FGDKAsyncBlockPtr;`
- L81 _function_ `return CreateAsyncBlock(nullptr, [this](FGDKAsyncBlock* LambdaAsyncBlock) { ProcessResults(); });` (scope `FOnlineAsyncTaskGDK::CreateAsyncBlock`)

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlineEventsInterfaceGDK.h` (Private)


#### class `FOnlineEventsGDK`  
`class FOnlineEventsGDK : public IOnlineEvents`  
_L15-37_
- inherits: `IOnlineEvents`
- desc: FOnlineEventsGDK - Interface class for events (GDK implementation)
- L18 _public prototype_ `FOnlineEventsGDK(FOnlineSubsystemGDK* InSubsystem);`
- L19 _public prototype_ `virtual ~FOnlineEventsGDK() = default;`
- L28 _public prototype_ `virtual bool TriggerEvent( const FUniqueNetId& PlayerId, const TCHAR* EventName, const FOnlineEventParms& Parms ) override;` — Calls an event @param PlayerId	- Id of the player to call the event on @param Name		- Name of requested event @param Parms		- Parameters that will be passed directly to the event
- L30 _public prototype_ `virtual void SetPlayerSessionId(const FUniqueNetId& PlayerId, const FGuid& PlayerSessionId) override;`
- L34 _private member_ `FOnlineSubsystemGDK* Subsystem;` — The owning subsystem
- L36 _private member_ `TUniqueNetIdMap<FGuid> PlayerSessionIds;`

#### Free symbols / members of external scopes

- L39 _typedef_ `typedef TSharedPtr<FOnlineEventsGDK, ESPMode::ThreadSafe> FOnlineEventsGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlineExternalUIInterfaceGDK.h` (Private)


#### class `FOnlineExternalUIGDK`  
`class FOnlineExternalUIGDK : public IOnlineExternalUI , public TSharedFromThis<FOnlineExternalUIGDK, ESPMode::ThreadSafe>`  
_L49-275_
- inherits: `IOnlineExternalUI,TSharedFromThis<FOnlineExternalUIGDK,ESPMode::ThreadSafe>`
- desc: Implementation for the Live external UIs
- L166 _private prototype_ `void HandleApplicationHasReactivated_WebUrl();`
- L204 _private member_ `FCriticalSection CallbackLock;`
- L215 _private member_ `class FOnlineSubsystemGDK* GDKSubsystem;` — Reference to the owning subsystem
- L218 _private member_ `bool bShouldCallUIDelegate;` — delegates to hold onto for particular callbacks
- L219 _private member_ `FOnShowStoreUIClosedDelegate StoreUIClosedDelegate;`
- L237 _private member_ `FShowWebUrlRequest ShowWebUrlRequest;`
- L239 _private prototype_ `void FinishShowWebUrl(FString&& FinalUrl);`
- L242 _private member_ `bool bAllowGuestLogin;` — CVar to configure if guest accounts will appear in the account picker
- L249 _public function_ `virtual ~FOnlineExternalUIGDK()` — Destructor.
- L254 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;` — IOnlineExternalUI
- L255 _public function_ `virtual bool ShowAccountCreationUI(const int ControllerIndex, const FOnAccountCreationUIClosedDelegate& Delegate = FOnAccountCreationUIClosedDelegate()) override`
- L256 _public prototype_ `virtual bool ShowFriendsUI(int32 LocalUserNum) override;`
- L257 _public prototype_ `virtual bool ShowInviteUI(int32 LocalUserNum, FName SessionName = NAME_GameSession) override;`
- L258 _public prototype_ `virtual bool ShowAchievementsUI(int32 LocalUserNum) override;`
- L259 _public prototype_ `virtual bool ShowLeaderboardUI(const FString& LeaderboardName) override;`
- L260 _public prototype_ `virtual bool ShowWebURL(const FString& Url, const FShowWebUrlParams& ShowParams, const FOnShowWebUrlClosedDelegate& Delegate = FOnShowWebUrlClosedDelegate()) override;`
- L261 _public prototype_ `virtual bool CloseWebURL() override;`
- L262 _public prototype_ `virtual bool ShowProfileUI(const FUniqueNetId& Requestor, const FUniqueNetId& Requestee, const FOnProfileUIClosedDelegate& Delegate = FOnProfileUIClosedDelegate()) override;`
- L263 _public prototype_ `virtual bool ShowAccountUpgradeUI(const FUniqueNetId& UniqueId) override;`
- L264 _public prototype_ `virtual bool ShowStoreUI(int32 LocalUserNum, const FShowStoreParams& ShowParams, const FOnShowStoreUIClosedDelegate& Delegate = FOnShowStoreUIClosedDelegate()) override;`
- L265 _public prototype_ `virtual bool ShowSendMessageUI(int32 LocalUserNum, const FShowSendMessageParams& ShowParams, const FOnShowSendMessageUIClosedDelegate& Delegate = FOnShowSendMessageUIClosedDelegate()) override;`
- L267 _public prototype_ `void HandleShowLoginUIComplete(bool bSuccess, HRESULT hResult, FGDKUserHandle GDKUser, FOnLoginUIClosedDelegate Delegate);`
- L268 _public prototype_ `void HandleGetActivitiesForUsersComplete(const TArray<XblMultiplayerActivityDetails>& ActivityDetails, bool bIsSuccess, FGDKMultiplayerSessionHandle InGDKSession, FGDKContextHandle GDKContext);`
- L269 _public prototype_ `void HandleShowSendGameInvitesUIComplete(bool bIsSuccess);`
- L270 _public prototype_ `void HandleShowAchievementsUIComplete(bool bIsSuccess);`
- L271 _public prototype_ `void HandleShowStoreUIComplete(bool wasPurchaseMade);`
- L272 _public prototype_ `void HandleShowProfileUIComplete(bool bSuccess, const FOnProfileUIClosedDelegate Delegate);`
- L274 _public prototype_ `void Tick(float DeltaTime);`

#### class `FOnlineExternalUIGDK::FAsyncEventAccountPickerClosed`  
`class FAsyncEventAccountPickerClosed : public FOnlineAsyncEvent<FOnlineSubsystemGDK>`  
_L57-95_
- inherits: `FOnlineAsyncEvent<FOnlineSubsystemGDK>`
- desc: Async event that notifies when the GDK account picker has been closed
- L60 _private function_ `FAsyncEventAccountPickerClosed() : FOnlineAsyncEvent(NULL), SignedInUser(nullptr)` — Hidden on purpose
- L67 _private member_ `HRESULT hResult;` — The result of picking user, to decide if the failure was because user cancelled it or something else
- L70 _private member_ `FGDKUserHandle SignedInUser;` — The user that signed in through the account picker. Will be null if no user signed in.
- L73 _private member_ `FOnLoginUIClosedDelegate Delegate;` — The delegate to execute when the account picker is closed.
- L85 _public function_ `FAsyncEventAccountPickerClosed(FOnlineSubsystemGDK* InGDKSubsystem, HRESULT hInResult, FGDKUserHandle InUser, const FOnLoginUIClosedDelegate& InDelegate) : FOnlineAsyncEvent(InGDKSubsystem), hResult(hInResult), SignedInUser(InUser), Delegate(InDelegate)` — Constructor. @param InGDKSubsystem The owner of the external UI interface that triggered this event. @param InUser The user that signed in through the account picker, if any. Can be null. @param InControllerIndex The controller that was used to sign in. @param InDelegate The delegate to execute on the game thread.
- L93 _public prototype_ `virtual FString ToString() const override;`
- L94 _public prototype_ `virtual void TriggerDelegates() override;`

#### class `FOnlineExternalUIGDK::FAsyncEventProfileCardClosed`  
`class FAsyncEventProfileCardClosed : public FOnlineAsyncEvent<FOnlineSubsystemGDK>`  
_L100-127_
- inherits: `FOnlineAsyncEvent<FOnlineSubsystemGDK>`
- desc: Async event that notifies when the profile card has been closed
- L103 _private function_ `FAsyncEventProfileCardClosed() : FOnlineAsyncEvent(NULL)` — Hidden on purpose
- L109 _private member_ `FOnProfileUIClosedDelegate Delegate;` — The delegate to execute when the account picker is closed.
- L119 _public function_ `FAsyncEventProfileCardClosed(FOnlineSubsystemGDK* InGDKSubsystem, const FOnProfileUIClosedDelegate& InDelegate) : FOnlineAsyncEvent(InGDKSubsystem), Delegate(InDelegate)` — Constructor. @param InGDKSubsystem The owner of the external UI interface that triggered this event. @param InDelegate The delegate to execute on the game thread.
- L125 _public prototype_ `virtual FString ToString() const override;`
- L126 _public prototype_ `virtual void TriggerDelegates() override;`

#### class `FOnlineExternalUIGDK::FAsyncEventStoreUIClosed`  
`class FAsyncEventStoreUIClosed : public FOnlineAsyncEvent<FOnlineSubsystemGDK>`  
_L132-164_
- inherits: `FOnlineAsyncEvent<FOnlineSubsystemGDK>`
- desc: Async event that notifies when the store UI has been closed
- L135 _private function_ `FAsyncEventStoreUIClosed() : FOnlineAsyncEvent(NULL)` — Hidden on purpose
- L141 _private member_ `FOnShowStoreUIClosedDelegate Delegate;` — The delegate to execute when the store UI is closed.
- L144 _private member_ `bool bPurchasedProduct;` — Whether a purchase was made
- L155 _public function_ `FAsyncEventStoreUIClosed(FOnlineSubsystemGDK* InGDKSubsystem, const FOnShowStoreUIClosedDelegate& InDelegate, bool PurchasedProduct) : FOnlineAsyncEvent(InGDKSubsystem), Delegate(InDelegate), bPurchasedProduct(PurchasedProduct)` — Constructor. @param InGDKSubsystem The owner of the external UI interface that triggered this event. @param InDelegate The delegate to execute on the game thread. @param PurchasedProduct A flag determining whether a purchase was made.
- L162 _public prototype_ `virtual FString ToString() const override;`
- L163 _public prototype_ `virtual void TriggerDelegates() override;`

#### class `FOnlineExternalUIGDK::FAsyncEventWebUrlUIClosed`  
`class FAsyncEventWebUrlUIClosed : public FOnlineAsyncEvent<FOnlineSubsystemGDK>`  
_L171-202_
- inherits: `FOnlineAsyncEvent<FOnlineSubsystemGDK>`
- desc: Async event that notifies when the Web Url has closed
- L174 _private function_ `FAsyncEventWebUrlUIClosed() : FOnlineAsyncEvent(NULL)` — Hidden on purpose
- L180 _private member_ `FOnShowWebUrlClosedDelegate Delegate;` — The delegate to execute when the WebUrl UI is closed.
- L182 _private member_ `FString WebUrl;`
- L193 _public function_ `FAsyncEventWebUrlUIClosed(FOnlineSubsystemGDK* InGDKSubsystem, FOnShowWebUrlClosedDelegate&& InDelegate, FString&& InWebUrl) : FOnlineAsyncEvent(InGDKSubsystem), Delegate(MoveTemp(InDelegate)), WebUrl(MoveTemp(InWebUrl))` — Constructor. @param InGDKSubsystem The owner of the external UI interface that triggered this event. @param InDelegate The delegate to execute on the game thread. @param InWebUrl The URL that was opened
- L200 _public prototype_ `virtual FString ToString() const override;`
- L201 _public prototype_ `virtual void TriggerDelegates() override;`

#### struct `FOnlineExternalUIGDK::FShowWebUrlRequest`  
`struct FShowWebUrlRequest`  
_L221-236_
- L223 _public function_ `FShowWebUrlRequest()`
- L227 _public function_ `void Reset()`
- L233 _public member_ `FString WebUrlBeingOpened;`
- L234 _public member_ `FOnShowWebUrlClosedDelegate WebUrlClosedDelegate;`
- L235 _public member_ `float WaitForProtocolActivationTimeRemaining;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGetActivitiesForUsersCompleteDelegate, const TArray<XblMultiplayerActivityDetails>&, bool);` — Delegate fired when activities for user has been queried
- L14 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnGetActivitiesForUsersCompleteDelegate, const TArray<XblMultiplayerActivityDetails>&, bool);` — Delegate fired when activities for user has been queried
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQueryGDKShowSendGameInvitesUICompleteDelegate, bool);` — Delegate fired when invite UI has been requested
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FOnQueryGDKShowSendGameInvitesUICompleteDelegate, bool);` — Delegate fired when invite UI has been requested
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQueryGDKShowAchievementsUICompleteDelegate, bool);` — Delegate fired when achievement UI has been requested
- L24 _prototype_ `DECLARE_DELEGATE_OneParam(FOnQueryGDKShowAchievementsUICompleteDelegate, bool);` — Delegate fired when achievement UI has been requested
- L29 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQueryGDKShowProfileUICompleteDelegate, bool);` — Delegate fired when profile UI has been requested
- L29 _prototype_ `DECLARE_DELEGATE_OneParam(FOnQueryGDKShowProfileUICompleteDelegate, bool);` — Delegate fired when profile UI has been requested
- L34 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQueryGDKShowStoreUICompleteDelegate, bool);` — Delegate fired when store UI has been requested
- L34 _prototype_ `DECLARE_DELEGATE_OneParam(FOnQueryGDKShowStoreUICompleteDelegate, bool);` — Delegate fired when store UI has been requested
- L39 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnQueryGDKShowLoginUICompleteDelegate, bool, HRESULT, FGDKUserHandle);` — Delegate fired when login UI has been requested
- L39 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnQueryGDKShowLoginUICompleteDelegate, bool, HRESULT, FGDKUserHandle);` — Delegate fired when login UI has been requested
- L44 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQueryGDKResolvePrivilegeWithUICompleteDelegate, bool);` — Delegate fired when Privilege has been requested, but GDK needs to resolve something with UI
- L44 _prototype_ `DECLARE_DELEGATE_OneParam(FOnQueryGDKResolvePrivilegeWithUICompleteDelegate, bool);` — Delegate fired when Privilege has been requested, but GDK needs to resolve something with UI
- L277 _typedef_ `typedef TSharedPtr<FOnlineExternalUIGDK, ESPMode::ThreadSafe> FOnlineExternalUIGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlineFriendsInterfaceGDK.h` (Private)


#### class `FOnlineFriendGDK`  
`class FOnlineFriendGDK : public FOnlineFriend`  
_L28-64_
- inherits: `FOnlineFriend`
- desc: Info associated with an online friend on the GDK service
- L33 _public prototype_ `FOnlineFriendGDK(const XblSocialRelationship& InSocialRelationship);` — FOnlineFriendGDK
- L34 _public prototype_ `virtual ~FOnlineFriendGDK() = default;`
- L37 _public prototype_ `virtual EInviteStatus::Type GetInviteStatus() const override;` — FOnlineFriend
- L38 _public prototype_ `virtual const FOnlineUserPresence& GetPresence() const override;`
- L41 _public prototype_ `virtual FUniqueNetIdRef GetUserId() const override;` — FOnlineUser
- L42 _public prototype_ `virtual FString GetRealName() const override;`
- L43 _public prototype_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override;`
- L44 _public prototype_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L47 _public prototype_ `bool IsFavorite() const;` — Helper to tell if this person has been been Favourited by the user; Favourite users should come first in a friendslist
- L54 _public member_ `FUniqueNetIdGDKRef UniqueNetIdGDK;` — Unique Live Id for the friend
- L57 _public member_ `FOnlineUserPresenceGDK Presence;` — Presence info
- L60 _public member_ `FString DisplayName;` — The Name XBox Live tells us to call this user (May be GamerTag, may be Real Name)
- L63 _public member_ `TMap<FString, FString> UserAttributes;` — Custom attributes store on this user

#### class `FOnlineBlockedPlayerGDK`  
`class FOnlineBlockedPlayerGDK : public FOnlineBlockedPlayer`  
_L66-81_
- inherits: `FOnlineBlockedPlayer`
- L71 _public prototype_ `FOnlineBlockedPlayerGDK(uint64 InXUID);` — FOnlineFriendGDK
- L72 _public prototype_ `virtual ~FOnlineBlockedPlayerGDK() = default;`
- L74 _public prototype_ `virtual FUniqueNetIdRef GetUserId() const override;`
- L75 _public prototype_ `virtual FString GetRealName() const override;`
- L76 _public prototype_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override;`
- L77 _public prototype_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override;`

#### class `FOnlineFriendsGDK`  
`class FOnlineFriendsGDK : public IOnlineFriends, public TSharedFromThis<FOnlineFriendsGDK, ESPMode::ThreadSafe>`  
_L86-144_
- inherits: `IOnlineFriends,TSharedFromThis<FOnlineFriendsGDK,ESPMode::ThreadSafe>`
- desc: Implements the GDK specific interface for friends
- L96 _public prototype_ `virtual bool ReadFriendsList(int32 LocalUserNum, const FString& ListName, const FOnReadFriendsListComplete& Delegate = FOnReadFriendsListComplete()) override;` — IOnlineFriends
- L97 _public prototype_ `virtual bool DeleteFriendsList(int32 LocalUserNum, const FString& ListName, const FOnDeleteFriendsListComplete& Delegate = FOnDeleteFriendsListComplete()) override;`
- L98 _public prototype_ `virtual bool SendInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnSendInviteComplete& Delegate = FOnSendInviteComplete()) override;`
- L99 _public prototype_ `virtual bool AcceptInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnAcceptInviteComplete& Delegate = FOnAcceptInviteComplete()) override;`
- L100 _public prototype_ `virtual bool RejectInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L101 _public prototype_ `virtual void SetFriendAlias(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FString& Alias, const FOnSetFriendAliasComplete& Delegate = FOnSetFriendAliasComplete()) override;`
- L102 _public prototype_ `virtual void DeleteFriendAlias(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnDeleteFriendAliasComplete& Delegate = FOnDeleteFriendAliasComplete()) override;`
- L103 _public prototype_ `virtual bool DeleteFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L104 _public prototype_ `virtual bool GetFriendsList(int32 LocalUserNum, const FString& ListName, TArray< TSharedRef<FOnlineFriend> >& OutFriends) override;`
- L105 _public prototype_ `virtual TSharedPtr<FOnlineFriend> GetFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L106 _public prototype_ `virtual bool IsFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L107 _public prototype_ `virtual void AddRecentPlayers(const FUniqueNetId& LocalUserId, const TArray<FReportPlayedWithUser>& InRecentPlayers, const FString& ListName, const FOnAddRecentPlayersComplete& InCompletionDelegate) override;`
- L108 _public prototype_ `virtual bool QueryRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace) override;`
- L109 _public prototype_ `virtual bool GetRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace, TArray< TSharedRef<FOnlineRecentPlayer> >& OutRecentPlayers) override;`
- L110 _public prototype_ `virtual void DumpRecentPlayers() const override;`
- L111 _public prototype_ `virtual bool BlockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId) override;`
- L112 _public prototype_ `virtual bool UnblockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId) override;`
- L113 _public prototype_ `virtual bool QueryBlockedPlayers(const FUniqueNetId& UserId) override;`
- L114 _public prototype_ `virtual bool GetBlockedPlayers(const FUniqueNetId& UserId, TArray< TSharedRef<FOnlineBlockedPlayer> >& OutBlockedPlayers) override;`
- L115 _public prototype_ `virtual void DumpBlockedPlayers() const override;`
- L118 _public function_ `explicit FOnlineFriendsGDK(class FOnlineSubsystemGDK* const InGDKSubsystem) : GDKSubsystem(InGDKSubsystem)` — FOnlineFriendsGDK
- L124 _public prototype_ `virtual ~FOnlineFriendsGDK() = default;`
- L128 _public prototype_ `void OnUsersSessionPresenceUpdate(const FOnlineGDKActivitiesResultMap& ActivitiesResults);`
- L129 _public prototype_ `void OnUsersSessionPresenceUpdate(TArray<FOnlineSession>& OnlineSessions);`
- L130 _public prototype_ `bool ShowProfileUI(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnSendInviteComplete& Delegate = FOnSendInviteComplete());`
- L131 _public prototype_ `void HandleShowProfileUIComplete(int32 LocalUserNum, FUniqueNetIdGDKRef FriendId, const FString ListName, const FOnSendInviteComplete Delegate);`
- L134 _private member_ `class FOnlineSubsystemGDK* const GDKSubsystem;` — Reference to the main GDK subsystem
- L137 _private member_ `FOnlineUserFriendsListGDKMap FriendsMap;` — Map of local users to map of their friends
- L140 _private member_ `TUniqueNetIdMap<TArray<TSharedRef<FOnlineBlockedPlayerGDK>>> AvoidListMap;` — These are users we have asked not to play with (similar to a blocklist)
- L143 _private member_ `TUniqueNetIdMap<TArray<FOnReadFriendsListComplete>> FriendsListInProgressDelegates;` — Map of players who have friends-reads in progress

#### Free symbols / members of external scopes

- L21 _typedef_ `using FOnlineFriendsListGDKMap = TUniqueNetIdMap<TSharedRef<class FOnlineFriendGDK>>;`
- L22 _typedef_ `using FOnlineUserFriendsListGDKMap = TUniqueNetIdMap<FOnlineFriendsListGDKMap>;`
- L23 _typedef_ `using FOnlineGDKActivitiesResultMap = TUniqueNetIdMap<FUniqueNetIdPtr >;`
- L146 _typedef_ `typedef TSharedPtr<FOnlineFriendsGDK, ESPMode::ThreadSafe> FOnlineFriendsGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlineLeaderboardInterfaceGDK.h` (Private)


#### class `FOnlineLeaderboardsGDK`  
`class FOnlineLeaderboardsGDK : public IOnlineLeaderboards, public TSharedFromThis< FOnlineLeaderboardsGDK, ESPMode::ThreadSafe>`  
_L20-51_
- inherits: `IOnlineLeaderboards,TSharedFromThis<FOnlineLeaderboardsGDK,ESPMode::ThreadSafe>`
- desc: Interface definition for the online services leaderboard services
- L24 _private member_ `class FOnlineSubsystemGDK* GDKSubsystem;` — Reference to the main Live subsystem
- L26 _private member_ `static const TCHAR* SortOrder;` — when requesting a friends leaderboard this is the requested sort order for the leaderboard
- L30 _public function_ `virtual ~FOnlineLeaderboardsGDK()`
- L33 _public prototype_ `virtual bool ReadLeaderboards(const TArray< FUniqueNetIdRef >& Players, FOnlineLeaderboardReadRef& ReadObject) override;` — IOnlineLeaderboards
- L34 _public prototype_ `virtual bool ReadLeaderboardsForFriends(int32 LocalUserNum, FOnlineLeaderboardReadRef& ReadObject) override;`
- L35 _public prototype_ `virtual bool ReadLeaderboardsAroundRank(int32 Rank, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) override;`
- L36 _public prototype_ `virtual bool ReadLeaderboardsAroundUser(FUniqueNetIdRef Player, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) override;`
- L37 _public prototype_ `virtual void FreeStats(FOnlineLeaderboardRead& ReadObject) override;`
- L38 _public prototype_ `virtual bool WriteLeaderboards(const FName& SessionName, const FUniqueNetId& Player, FOnlineLeaderboardWrite& WriteObject) override;`
- L39 _public prototype_ `virtual bool FlushLeaderboards(const FName& SessionName) override;`
- L40 _public prototype_ `virtual bool WriteOnlinePlayerRatings(const FName& SessionName, int32 LeaderboardId, const TArray<FOnlinePlayerScore>& PlayerScores) override;`
- L42 _public prototype_ `void OnReadLeaderboardsComplete(bool bSuccess);`
- L43 _public prototype_ `void OnReadLeaderboardsForFriendsComplete(bool bSuccess);`
- L50 _public prototype_ `explicit FOnlineLeaderboardsGDK(FOnlineSubsystemGDK* InGDKSubsystem);` — Constructor @param InSubsystem - A reference to the owning subsystem

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DELEGATE_OneParam(FOnReadLeaderboardsCompleteDelegate, bool);` — Delegate fired when Read Leaderboards is complete
- L10 _prototype_ `DECLARE_DELEGATE_OneParam(FOnReadLeaderboardsCompleteDelegate, bool);` — Delegate fired when Read Leaderboards is complete
- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetLeaderboardCompleteDelegate, bool);` — Delegate fired when Read Leaderboards is complete
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FOnGetLeaderboardCompleteDelegate, bool);` — Delegate fired when Read Leaderboards is complete
- L53 _typedef_ `typedef TSharedPtr<FOnlineLeaderboardsGDK, ESPMode::ThreadSafe> FOnlineLeaderboardsGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlineMatchmakingInterfaceGDK.h` (Private)


#### class `FOnlineMatchmakingInterfaceGDK`  
`class FOnlineMatchmakingInterfaceGDK`  
_L15-79_
- L18 _public prototype_ `FOnlineMatchmakingInterfaceGDK(FOnlineSubsystemGDK* InSubsystem);`
- L19 _public prototype_ `virtual ~FOnlineMatchmakingInterfaceGDK();`
- L25 _public prototype_ `bool CancelMatchmaking(const int32 SearchingPlayerNum, const FName SessionName);`
- L26 _public prototype_ `bool CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, const FName SessionName);`
- L31 _public prototype_ `void AddMatchmakingTicket(const FName SessionName, const FOnlineMatchTicketInfoPtr TicketInfo);` — Matchmaking related APIs
- L32 _public prototype_ `void RemoveMatchmakingTicket(const FName SessionName );`
- L33 _public prototype_ `bool GetMatchmakingTicket(const FName SessionName, FOnlineMatchTicketInfoPtr& OutTicketInfo) const;`
- L34 _public prototype_ `void SetTicketState(const FName SessionName, const EOnlineGDKMatchmakingState::Type State);`
- L37 _public prototype_ `void SubmitMatchingTicket( FGDKMultiplayerSessionHandle InGDKSession, const FName SessionName, const bool bCancelExistingTicket);` — Resubmit a matchmaking ticket if necessary
- L43 _public prototype_ `FOnlineMatchTicketInfoPtr GetMatchTicketForGDKSessionRef(const XblMultiplayerSessionReference* GDKSessionRef);` — Look up the ticket corresponding to a Live session reference
- L51 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnMatchmakingComplete, FName, bool);` — Delegate fired when the cloud matchmaking has completed @param SessionName The name of the session that was found via matchmaking @param bWasSuccessful true if the async action completed without error, false if there was an error
- L59 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnCancelMatchmakingComplete, FName, bool);` — Delegate fired when the cloud matchmaking has been canceled @param SessionName the name of the session that was canceled @param bWasSuccessful true if the async action completed without error, false if there was an error
- L63 _private prototype_ `EOnlineGDKMatchmakingState::Type GetMatchmakingState(FName SessionName) const;`
- L64 _private prototype_ `void SetMatchmakingState(const FName SessionName, const EOnlineGDKMatchmakingState::Type State);`
- L66 _private prototype_ `void OnSessionChanged(const FName SessionName, XblMultiplayerSessionChangeTypes Diff);`
- L69 _private prototype_ `void OnMatchmakingStatusChanged(const FName SessionName);` — Handle changes to matchmaking status
- L70 _private prototype_ `void OnMemberListChanged(const FName SessionName);`
- L72 _private member_ `FOnSessionChangedDelegate OnSessionChangedDelegate;`
- L74 _private typedef_ `typedef TMap<FName, FOnlineMatchTicketInfoPtr> TicketInfoMap;`
- L75 _private member_ `mutable FCriticalSection TicketsLock;`
- L76 _private member_ `TicketInfoMap MatchmakingTickets;`
- L78 _private member_ `FOnlineSubsystemGDK* GDKSubsystem;`

#### Free symbols / members of external scopes

- L81 _typedef_ `typedef TSharedPtr<FOnlineMatchmakingInterfaceGDK, ESPMode::ThreadSafe> FOnlineMatchmakingInterfaceGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlinePresenceInterfaceGDK.h` (Private)


#### class `FOnlineUserPresenceGDK`  
`class FOnlineUserPresenceGDK : public FOnlineUserPresence`  
_L55-158_
- inherits: `FOnlineUserPresence`
- desc: GDK Presence record to handle constructing from a GDK PresenceRecord
- L63 _private prototype_ `virtual ~FOnlineUserPresenceGDK() = default;`
- L64 _private prototype_ `FOnlineUserPresenceGDK(const FOnlineUserPresenceGDK& Other) = default;`
- L65 _private prototype_ `FOnlineUserPresenceGDK(FOnlineUserPresenceGDK&& Other) = default;`
- L66 _private prototype_ `FOnlineUserPresenceGDK& operator=(const FOnlineUserPresenceGDK& Other) = default;`
- L67 _private prototype_ `FOnlineUserPresenceGDK& operator=(FOnlineUserPresenceGDK&& Other) = default;`
- L72 _private function_ `explicit FOnlineUserPresenceGDK(FGDKPresenceRecordHandle Record)` — Construct our values from an XBox presence record
- L77 _private function_ `void SetPresenceFromPresenceRecord(FGDKPresenceRecordHandle Record)`
- L157 _private prototype_ `void SetStatusPropertiesFromStatistics(const XblUserStatisticsResult& StatsResult);` — Add status key/value properties based on GDK statistics.

#### class `FOnlinePresenceGDK`  
`class FOnlinePresenceGDK : public IOnlinePresence , public TSharedFromThis<FOnlinePresenceGDK, ESPMode::ThreadSafe>`  
_L163-243_
- inherits: `IOnlinePresence,TSharedFromThis<FOnlinePresenceGDK,ESPMode::ThreadSafe>`
- desc: Implementation for the GDK rich presence interface
- L176 _public prototype_ `virtual void SetPresence(const FUniqueNetId& User, const FOnlineUserPresenceStatus& Status, const FOnPresenceTaskCompleteDelegate& Delegate = FOnPresenceTaskCompleteDelegate()) override;` — IOnlinePresence
- L177 _public prototype_ `virtual void QueryPresence(const FUniqueNetId& User, const FOnPresenceTaskCompleteDelegate& Delegate = FOnPresenceTaskCompleteDelegate()) override;`
- L178 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedPresence(const FUniqueNetId& User, TSharedPtr<FOnlineUserPresence>& OutPresence) override;`
- L179 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedPresenceForApp(const FUniqueNetId& LocalUserId, const FUniqueNetId& User, const FString& AppId, TSharedPtr<FOnlineUserPresence>& OutPresence) override;`
- L181 _public prototype_ `void Tick(const float DeltaTime);`
- L183 _public prototype_ `static TArray<FString> GetAutoSubscribePresenceStatNames();`
- L193 _public prototype_ `void OnPresenceDeviceChanged(const FUniqueNetIdGDK& UserGDK, XblPresenceDeviceType DeviceType, bool bIsUserLoggedOnDevice);`
- L194 _public prototype_ `void OnPresenceTitleChanged(const FUniqueNetIdGDK& UserGDK, uint32 TitleId, XblPresenceTitleState TitleState);`
- L196 _public prototype_ `void UnsubscribeFromAllPresenceUpdatesForUser(FGDKContextHandle GDKContext);`
- L197 _public prototype_ `bool IsSubscribedToPresenceUpdates(const FUniqueNetIdGDKRef& GDKUserId) const;`
- L198 _public prototype_ `void AddPresenceUpdateSubscriptions(const TArray<FUniqueNetIdGDKRef>& GDKUserIds);`
- L199 _public prototype_ `void RemovePresenceUpdateSubscriptions(const TArray<FUniqueNetIdGDKRef>& GDKUserIds);`
- L201 _public prototype_ `void OnFriendSessionUpdated(const FOnlineError& ErrorResult, const FOnlineGDKActivitiesResultMap& ActivitiesResults);`
- L202 _public prototype_ `void OnFriendSessionUpdated(bool bWasSuccessful, TArray<FOnlineSession> OnlineSessions);`
- L204 _public prototype_ `void ProcessStatUpdate(const FUniqueNetIdGDKRef& LocalUserId, const FUniqueNetIdGDKRef& UpdatedUserId, const FString& StatName, const FString& StatValue, const FString& StatType);`
- L206 _public prototype_ `void EstablishDefaultPresenceStatSubscriptions(const FUniqueNetIdGDKRef& RequestingPlayerId, const FUniqueNetIdGDKRef& PlayerId);`
- L207 _public prototype_ `void SubscribeToStatUpdates(const FUniqueNetIdGDKRef& RequestingPlayerId, const FUniqueNetIdGDKRef& PlayerId, const FString& StatName);`
- L208 _public prototype_ `bool IsSubscribedToStatUpdates(const FUniqueNetIdGDKRef& RequestingPlayerId, const FUniqueNetIdGDKRef& PlayerId, const FString& StatName) const;`
- L209 _public prototype_ `void ClearAllStatUpdateSubscriptionsForUser(const FUniqueNetIdGDKRef& RequestingPlayerId);`
- L210 _public prototype_ `void ClearStatUpdateSubscriptionsForFriend(const FUniqueNetIdGDKRef& RequestingPlayerId, const FUniqueNetIdGDKRef& TargetPlayerId);`
- L212 _public prototype_ `void HandleSetGDKPresenceComplete(bool bSuccessful, const FOnlineUserPresenceStatus& Status, const FUniqueNetIdGDKRef User, const FString CurrentPresenceIdString, const FOnPresenceTaskCompleteDelegate Delegate);`
- L222 _private member_ `TArray<FDelegateHandle> FriendSessionDelegateHandles;`
- L225 _private member_ `TUniqueNetIdMap<FOnlineUserPresenceStatus> LocalUserPresenceCache;` — Cache of local user's last saved presence to prevent duplicate stores
- L228 _private member_ `TUniqueNetIdMap<TSharedRef<FOnlineUserPresenceGDK>> PresenceCache;` — Cache of presence data. Stores only the most recent results of QueryPresence.
- L231 _private member_ `TUniqueNetIdMap<TUniqueNetIdMap<FStatsSubscriptionSetRef>> AllStatSubscriptionsByLocalUserId;` — Stat updates we are subscribed to for each player on behalf of a given local player
- L234 _private member_ `FUniqueNetIdSet PresenceSubscriptionSet;` — Set of users we're subscribed to for presence updates
- L237 _private prototype_ `static FString GetPresenceIdString(const FOnlineUserPresenceStatus& Status);` — Helper function to get the presence string from presence status
- L240 _private prototype_ `void AddStatSubscriptionIfNeeded(FGDKContextHandle GDKContext, const FUniqueNetIdGDKRef& UserId, FStatsSubscriptionSetRef& StatSubscriptions, const FString& StatName);` — Helper function to launch the async task to track user statistics changes
- L242 _private member_ `float SessionPresencePollDelay = 60.0f;`

#### struct `FOnlinePresenceGDK::FPresenceSubscriptionHandles`  
`struct FPresenceSubscriptionHandles`  
_L187-191_
- L189 _public member_ `XblRealTimeActivitySubscriptionHandle DeviceChangeSubscriptionHandle = nullptr;`
- L190 _public member_ `XblRealTimeActivitySubscriptionHandle TitleChangeSubscriptionHandle = nullptr;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define LOCTEXT_NAMESPACE "OnlineSubsystemGDK"`
- L22 _macro_ `#define ONLINE_ERROR_NAMESPACE "errors.com.epicgames.oss.presence"`
- L24 _namespace_ `namespace OnlinePresenceGDK`
- L28 _namespace_ `namespace Errors` (scope `OnlinePresenceGDK`)
- L30 _function_ `inline FOnlineError HResultError(int32 InCode)` (scope `OnlinePresenceGDK::Errors`)
- L43 _typedef_ `using FOnlineGDKActivitiesResultMap = TUniqueNetIdMap<FUniqueNetIdPtr >;`
- L45 _typedef_ `typedef TSet<FString> FStatsSubscriptionSet;`
- L46 _typedef_ `typedef TSharedRef<FStatsSubscriptionSet, ESPMode::ThreadSafe> FStatsSubscriptionSetRef;`
- L50 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSetGDKPresenceCompleteDelegate, bool , const FOnlineUserPresenceStatus& );` — Delegate fired when SetPresence task has completed
- L50 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSetGDKPresenceCompleteDelegate, bool , const FOnlineUserPresenceStatus& );` — Delegate fired when SetPresence task has completed
- L245 _typedef_ `typedef TSharedPtr<FOnlinePresenceGDK, ESPMode::ThreadSafe> FOnlinePresenceGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlinePurchaseInterfaceGDK.h` (Private)


#### enum `EPurchaseValidationMethod`  
`enum class EPurchaseValidationMethod`  
_L36-55_
- desc: Used to specify the contents of ValidationInfo in receipt line items
- L39 _public enumerator_ `None` — empty ValidationInfo
- L42 _public enumerator_ `XSTSToken` — <UserId>:<XSTSToken> ValidationInfo
- L48 _public enumerator_ `UserCollectionsId` — <UserId>:UserCollectionsId::ServiceTicket: ValidationInfo. Call FinalizeReceiptValidationInfo with an AzureAD token appended to this Optionally, you can append :PublisherUserId:<PublisherUserId> to associate that user id with the UserStoreId See "Collections: Requesting a User Store ID for service-to-service authentication" in the GDK documentation for AzureAD token FinalizeReceiptValidation will return <UserId>:UserCollectionsId:<UserCollectionsId>
- L54 _public enumerator_ `UserPurchaseId` — <UserId>:UserPurchaseId::ServiceTicket: ValidationInfo. Call FinalizeReceiptValidationInfo with an AzureAD token appended to this Optionally, you can append :PublisherUserId:<PublisherUserId> to associate that user id with the UserStoreId See "Collections: Requesting a User Store ID for service-to-service authentication" in the GDK documentation for AzureAD token FinalizeReceiptValidation will return <UserId>:UserPurchaseId:<UserPurchaseId>

#### class `FOnlinePurchaseGDK`  
`class FOnlinePurchaseGDK : public IOnlinePurchase , public TSharedFromThis<FOnlinePurchaseGDK, ESPMode::ThreadSafe>`  
_L57-107_
- inherits: `IOnlinePurchase,TSharedFromThis<FOnlinePurchaseGDK,ESPMode::ThreadSafe>`
- L62 _public prototype_ `FOnlinePurchaseGDK(FOnlineSubsystemGDK* InGDKSubsystem);`
- L63 _public prototype_ `virtual ~FOnlinePurchaseGDK();`
- L67 _public prototype_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId) override;`
- L68 _public prototype_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId, FOnlineError& Error) override;`
- L69 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseCheckoutComplete& Delegate) override;`
- L70 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseReceiptlessCheckoutComplete& Delegate) override;`
- L71 _public prototype_ `virtual void FinalizePurchase(const FUniqueNetId& UserId, const FString& ReceiptId) override;`
- L72 _public prototype_ `virtual void RedeemCode(const FUniqueNetId& UserId, const FRedeemCodeRequest& RedeemCodeRequest, const FOnPurchaseRedeemCodeComplete& Delegate) override;`
- L73 _public prototype_ `virtual void QueryReceipts(const FUniqueNetId& UserId, bool bRestoreReceipts, const FOnQueryReceiptsComplete& Delegate) override;`
- L74 _public prototype_ `virtual void GetReceipts(const FUniqueNetId& UserId, TArray<FPurchaseReceipt>& OutReceipts) const override;`
- L75 _public prototype_ `virtual void FinalizeReceiptValidationInfo(const FUniqueNetId& UserId, FString& InReceiptValidationInfo, const FOnFinalizeReceiptValidationInfoComplete& Delegate) override;`
- L80 _public prototype_ `void UnregisterLivePurchaseHooks();`
- L82 _public prototype_ `EPurchaseValidationMethod GetPurchaseValidationMethod(XStoreProductKind ProductKind) const;`
- L85 _private typedef_ `typedef TFunction<void(const FString& )> TCallDelegateOnError;`
- L86 _private prototype_ `bool GetGDKUserInfoOrCallDelegateOnError(FUniqueNetIdGDKRef OutGDKUserId, FGDKUserHandle& OutGDKUser, FGDKContextHandle& OutUserGDKContext, const TCallDelegateOnError& CallDelegateOnError);`
- L87 _private prototype_ `TOptional<FUniqueOfferId> GetStoreGDKOfferIdOrCallDelegateOnError(const FPurchaseCheckoutRequest& CheckoutRequest, const TCallDelegateOnError& CallDelegateOnError);`
- L93 _private member_ `TUniqueNetIdMap<TArray<FPurchaseReceipt> > UserCachedReceipts;` — Cached receipts/inventory per user
- L95 _private member_ `FString ReceiptsXSTSEndpoint;` — Endpoint to pass during XSTS generation for claiming inventory items
- L97 _private member_ `bool bIsCurrentlyInCheckout;` — Is there a purchase in progress currently?
- L99 _private member_ `bool bSoftFailReceiptFailures;` — Soft-Fail Receipt-Checks (return successful but with an Error Message/Code) if any entitlement succeeds
- L101 _private member_ `EPurchaseValidationMethod ValidationMethod_Consumable;`
- L102 _private member_ `EPurchaseValidationMethod ValidationMethod_Pass;`
- L106 _private member_ `XTaskQueueRegistrationToken GDKEventProductPurchaseHandle;` — Delegate handle for the "User Purchased Something" delegate

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "OnlineSubsystemGDK"`
- L11 _macro_ `#define ONLINE_ERROR_NAMESPACE "errors.com.epicgames.oss.purchase"`
- L13 _namespace_ `namespace OnlinePurchaseGDK`
- L17 _namespace_ `namespace Errors` (scope `OnlinePurchaseGDK`)
- L19 _function_ `inline FOnlineError PurchaseCanceled()` (scope `OnlinePurchaseGDK::Errors`)
- L20 _function_ `inline FOnlineError PurchaseFailureStart(int32 InCode)` (scope `OnlinePurchaseGDK::Errors`)
- L21 _function_ `inline FOnlineError PurchaseFailure(int32 InCode)` (scope `OnlinePurchaseGDK::Errors`)
- L22 _function_ `inline FOnlineError HResultError(int32 InCode)` (scope `OnlinePurchaseGDK::Errors`)
- L23 _function_ `inline FOnlineError HResultError(int32 InCode, const FText& InText)` (scope `OnlinePurchaseGDK::Errors`)
- L109 _typedef_ `typedef TSharedPtr<FOnlinePurchaseGDK, ESPMode::ThreadSafe> FOnlinePurchaseGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlineSessionGDK.h` (Private)


#### class `FOnlineSessionGDK`  
`class FOnlineSessionGDK : public IOnlineSession, public TSharedFromThis<FOnlineSessionGDK, ESPMode::ThreadSafe>`  
_L13-98_
- inherits: `IOnlineSession,TSharedFromThis<FOnlineSessionGDK,ESPMode::ThreadSafe>`
- L16 _public prototype_ `~FOnlineSessionGDK();`
- L18 _public prototype_ `FNamedOnlineSessionPtr GetNamedSessionPtr(FName SessionName) const;`
- L21 _public prototype_ `virtual FUniqueNetIdPtr CreateSessionIdFromString(const FString& SessionIdStr) override;` — IOnlineSession interface
- L22 _public prototype_ `virtual FNamedOnlineSession* GetNamedSession(FName SessionName) override;`
- L23 _public prototype_ `virtual void RemoveNamedSession(FName SessionName) override;`
- L24 _public prototype_ `virtual bool HasPresenceSession() override;`
- L25 _public prototype_ `virtual EOnlineSessionState::Type GetSessionState(FName SessionName) const override;`
- L26 _public prototype_ `virtual bool CreateSession(int32 HostingPlayerControllerIndex, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;`
- L27 _public prototype_ `virtual bool CreateSession(const FUniqueNetId& HostingPlayerId, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;`
- L28 _public prototype_ `virtual bool StartSession(FName SessionName) override;`
- L29 _public prototype_ `virtual bool UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings, bool bShouldRefreshOnlineData) override;`
- L30 _public prototype_ `virtual bool EndSession(FName SessionName) override;`
- L31 _public prototype_ `virtual bool DestroySession(FName SessionName, const FOnDestroySessionCompleteDelegate& CompletionDelegate = FOnDestroySessionCompleteDelegate()) override;`
- L32 _public prototype_ `virtual bool IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId) override;`
- L33 _public prototype_ `virtual bool StartMatchmaking(const TArray< FUniqueNetIdRef >& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L34 _public prototype_ `virtual bool CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName) override;`
- L35 _public prototype_ `virtual bool CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, FName SessionName) override;`
- L36 _public prototype_ `virtual bool FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L37 _public prototype_ `virtual bool FindSessions(const FUniqueNetId& SearchingPlayerId, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L38 _public prototype_ `virtual bool FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId, const FUniqueNetId& FriendId, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate) override;`
- L39 _public prototype_ `virtual bool CancelFindSessions() override;`
- L40 _public prototype_ `virtual bool PingSearchResults(const FOnlineSessionSearchResult& SearchResult) override;`
- L41 _public prototype_ `virtual bool JoinSession(int32 ControllerIndex, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;`
- L42 _public prototype_ `virtual bool JoinSession(const FUniqueNetId& UserId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;`
- L43 _public prototype_ `virtual bool FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend) override;`
- L44 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend) override;`
- L45 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& FriendList) override;`
- L46 _public prototype_ `virtual bool SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend) override;`
- L47 _public prototype_ `virtual bool SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName, const FUniqueNetId& Friend) override;`
- L48 _public prototype_ `virtual bool SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) override;`
- L49 _public prototype_ `virtual bool SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) override;`
- L50 _public prototype_ `virtual bool GetResolvedConnectString(FName SessionName, FString& ConnectInfo, FName PortType) override;`
- L51 _public prototype_ `virtual bool GetResolvedConnectString(const class FOnlineSessionSearchResult& SearchResult, FName PortType, FString& ConnectInfo) override;`
- L52 _public prototype_ `virtual FOnlineSessionSettings* GetSessionSettings(FName SessionName) override;`
- L53 _public prototype_ `virtual bool RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited) override;`
- L54 _public prototype_ `virtual bool RegisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players, bool bWasInvited = false) override;`
- L55 _public prototype_ `virtual bool UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId) override;`
- L56 _public prototype_ `virtual bool UnregisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players) override;`
- L57 _public prototype_ `virtual void RegisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnRegisterLocalPlayerCompleteDelegate& Delegate) override;`
- L58 _public prototype_ `virtual void UnregisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnUnregisterLocalPlayerCompleteDelegate& Delegate) override;`
- L59 _public prototype_ `virtual int32 GetNumSessions() override;`
- L60 _public prototype_ `virtual void DumpSessionState() override;`
- L62 _public prototype_ `virtual FDelegateHandle AddOnMatchmakingCompleteDelegate_Handle(const FOnMatchmakingCompleteDelegate& Delegate) override;`
- L63 _public prototype_ `virtual void ClearOnMatchmakingCompleteDelegate_Handle(FDelegateHandle& DelegateHandle) override;`
- L64 _public prototype_ `virtual void TriggerOnMatchmakingCompleteDelegates(FName SessionName, bool bWasSuccessful) override;`
- L66 _public prototype_ `virtual FDelegateHandle AddOnCancelMatchmakingCompleteDelegate_Handle(const FOnCancelMatchmakingCompleteDelegate& Delegate) override;`
- L67 _public prototype_ `virtual void ClearOnCancelMatchmakingCompleteDelegate_Handle(FDelegateHandle& DelegateHandle) override;`
- L68 _public prototype_ `virtual void TriggerOnCancelMatchmakingCompleteDelegates(FName SessionName, bool bWasSuccessful) override;`
- L73 _public prototype_ `bool IsMpaEnabled() const;`
- L75 _public prototype_ `const TSharedPtr<FOnlineSessionMpsdGDK>& GetMpsdImpl() const;`
- L76 _public prototype_ `const TSharedPtr<FOnlineSessionMpaGDK>& GetMpaImpl() const;`
- L78 _public prototype_ `void Tick(float DeltaTime);`
- L80 _public prototype_ `FNamedOnlineSessionRef AddNamedSessionRef(FName SessionName, const FOnlineSessionSettings& SessionSettings);`
- L81 _public prototype_ `FNamedOnlineSessionRef AddNamedSessionRef(FName SessionName, const FOnlineSession& Session);`
- L82 _public prototype_ `virtual FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSessionSettings& SessionSettings) override;`
- L83 _public prototype_ `virtual FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSession& Session) override;`
- L85 _public prototype_ `void ClearSessionState(FGDKContextHandle GDKContext, FUniqueNetIdGDKRef NetID);`
- L87 _public member_ `static const int MAX_RETRIES = 20;`
- L90 _protected prototype_ `void SaveInviteFromActivation(const FString& ActivationUri);`
- L92 _protected member_ `TSharedPtr<FOnlineSessionMpsdGDK> OnlineSessionMpsdGDK;`
- L93 _protected member_ `TSharedPtr<FOnlineSessionMpaGDK> OnlineSessionMpaGDK;`
- L95 _protected member_ `FDelegateHandle InviteAcceptedHandler;`
- L97 _protected member_ `class FOnlineSubsystemGDK* GDKSubsystem;`

#### Free symbols / members of external scopes

- L100 _typedef_ `typedef TSharedPtr<FOnlineSessionGDK, ESPMode::ThreadSafe> FOnlineSessionGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlineSessionInterfaceMpaGDK.h` (Private)


#### struct `FMpaActivity`  
`struct FMpaActivity`  
_L21-39_
- L23 _public member_ `std::string ConnectionString;`
- L24 _public member_ `std::string GroupId;`
- L25 _public member_ `uint32 CurrentPlayers = 0;`
- L26 _public member_ `uint32 MaxPlayers = 0;`
- L27 _public member_ `XblMultiplayerActivityJoinRestriction JoinRestriction = XblMultiplayerActivityJoinRestriction::Followed;`
- L28 _public member_ `bool AllowCrossPlatformJoin = true;`
- L30 _public function_ `bool operator==(const FMpaActivity& Other) const`

#### class `FOnlineSessionMpaGDK`  
`class FOnlineSessionMpaGDK : public TSharedFromThis<FOnlineSessionMpaGDK, ESPMode::ThreadSafe>`  
_L41-206_
- inherits: `TSharedFromThis<FOnlineSessionMpaGDK,ESPMode::ThreadSafe>`
- L46 _public prototype_ `FUniqueNetIdPtr CreateSessionIdFromString(const FString& SessionIdStr);` — IOnlineSession interface
- L47 _public prototype_ `FNamedOnlineSession* GetNamedSession(FName SessionName);`
- L48 _public prototype_ `FNamedOnlineSessionPtr GetNamedSessionPtr(FName SessionName) const;`
- L50 _public prototype_ `void RemoveNamedSession(FName SessionName);`
- L52 _public prototype_ `bool HasPresenceSession() const;`
- L54 _public prototype_ `EOnlineSessionState::Type GetSessionState(FName SessionName) const;`
- L56 _public prototype_ `bool CreateSession(int32 HostingPlayerControllerIndex, FName SessionName, const FOnlineSessionSettings& NewSessionSettings);`
- L57 _public prototype_ `bool CreateSession(const FUniqueNetId& HostingPlayerId, FName SessionName, const FOnlineSessionSettings& NewSessionSettings);`
- L58 _public prototype_ `bool StartSession(FName SessionName);`
- L59 _public prototype_ `bool UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings, bool bShouldRefreshOnlineData);`
- L60 _public prototype_ `bool EndSession(FName SessionName);`
- L61 _public prototype_ `bool DestroySession(FName SessionName, const FOnDestroySessionCompleteDelegate& CompletionDelegate = FOnDestroySessionCompleteDelegate());`
- L62 _public prototype_ `bool IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId);`
- L63 _public prototype_ `bool StartMatchmaking(const TArray< FUniqueNetIdRef >& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings);`
- L64 _public prototype_ `bool CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName);`
- L65 _public prototype_ `bool CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, FName SessionName);`
- L66 _public prototype_ `bool FindSessions(int32 SearchingPlayerControllerIndex, const TSharedRef<FOnlineSessionSearch>& SearchSettings);`
- L67 _public prototype_ `bool FindSessions(const FUniqueNetId& SearchingPlayerId, const TSharedRef<FOnlineSessionSearch>& SearchSettings);`
- L68 _public prototype_ `bool FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId, const FUniqueNetId& FriendId, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate);`
- L69 _public prototype_ `bool CancelFindSessions();`
- L70 _public function_ `bool PingSearchResults(const FOnlineSessionSearchResult& SearchResult)`
- L71 _public prototype_ `bool JoinSession(int32 ControllerIndex, FName SessionName, const FOnlineSessionSearchResult& DesiredSession);`
- L72 _public prototype_ `bool JoinSession(const FUniqueNetId& UserId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession);`
- L73 _public prototype_ `bool FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend);`
- L74 _public prototype_ `bool FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend);`
- L75 _public prototype_ `bool FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& FriendList);`
- L76 _public prototype_ `bool FindFriendSession(int32 LocalUserNum, const TArray<FUniqueNetIdRef>& FriendList);`
- L77 _public prototype_ `bool SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend);`
- L78 _public prototype_ `bool SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName, const FUniqueNetId& Friend);`
- L79 _public prototype_ `bool SendSessionInviteToFriend_Internal(FGDKContextHandle GDKContext, FName SessionName, const FUniqueNetId& Friend);`
- L80 _public prototype_ `bool SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray< FUniqueNetIdRef >& Friends);`
- L81 _public prototype_ `bool SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName, const TArray< FUniqueNetIdRef >& Friends);`
- L82 _public prototype_ `bool SendSessionInviteToFriendsByNetIds(FGDKContextHandle GDKContext, FName SessionName, const TArray<FUniqueNetIdRef>& Friends);`
- L83 _public prototype_ `bool SendSessionInviteToFriendsByXuids(FGDKContextHandle GDKContext, FName SessionName, const TArray<uint64>& FriendXuids);`
- L84 _public prototype_ `bool GetResolvedConnectString(FName SessionName, FString& ConnectInfo, FName PortType);`
- L85 _public prototype_ `bool GetResolvedConnectString(const FOnlineSessionSearchResult& SearchResult, FName PortType, FString& ConnectInfo);`
- L86 _public prototype_ `FOnlineSessionSettings* GetSessionSettings(FName SessionName);`
- L87 _public prototype_ `bool RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited);`
- L88 _public prototype_ `bool RegisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players, bool bWasInvited);`
- L89 _public prototype_ `void RegisterVoice(const FUniqueNetId& PlayerId);`
- L90 _public prototype_ `bool UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId);`
- L91 _public prototype_ `bool UnregisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players);`
- L92 _public prototype_ `void UnregisterVoice(const FUniqueNetId& PlayerId);`
- L93 _public prototype_ `void RegisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnRegisterLocalPlayerCompleteDelegate& Delegate);`
- L94 _public prototype_ `void UnregisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnUnregisterLocalPlayerCompleteDelegate& Delegate);`
- L95 _public prototype_ `void Tick(float DeltaTime);`
- L96 _public prototype_ `void TickPendingSessionUserInvites(float DeltaTime);`
- L97 _public prototype_ `void TickPendingInvites(float DeltaTime);`
- L98 _public prototype_ `FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSessionSettings& SessionSettings);`
- L99 _public prototype_ `FNamedOnlineSessionRef AddNamedSessionRef(FName SessionName, const FOnlineSessionSettings& SessionSettings);`
- L100 _public prototype_ `FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSession& Session);`
- L101 _public prototype_ `FNamedOnlineSessionRef AddNamedSessionRef(FName SessionName, const FOnlineSession& Session);`
- L102 _public function_ `int32 GetNumSessions()`
- L103 _public function_ `void DumpSessionState()`
- L105 _public prototype_ `const FMpaActivity* GetMpaActivity(FUniqueNetIdGDKPtr LocalPlayerID) const;`
- L106 _public prototype_ `void SetMpaActivity(FUniqueNetIdGDKPtr LocalPlayerID, const FMpaActivity& MpaActivity);`
- L107 _public prototype_ `void ClearMpaActivity(FUniqueNetIdGDKPtr LocalPlayerID);`
- L112 _public prototype_ `void SaveInviteFromActivation(const FString& ActivationUri);`
- L114 _public prototype_ `void ClearSessionState(FGDKContextHandle GDKContext, FUniqueNetIdGDKRef NetID);`
- L118 _protected prototype_ `void SaveSessionInvite(uint64 SenderXuid, FGDKUserHandle AcceptingUser, const FString& ConnectionString);`
- L119 _protected prototype_ `void ProcessPendingSessionUserInvite(FGDKUserHandle AcceptingUser, int32 LocalUserIndex, FOnlineSessionSearchResult const& SearchResult);`
- L121 _protected prototype_ `void OnGetActivitiesComplete(bool bWasSuccessful, TArray<FOnlineSession> OnlineSessions, int32 LocalUserNum);`
- L124 _protected prototype_ `bool CreateMatchmakingTicket(const TArray< FUniqueNetIdRef >& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings);`
- L125 _protected prototype_ `void ShareMatchmakingString(FString& ConnectString);`
- L126 _protected prototype_ `void TickMatchmaking();`
- L127 _protected prototype_ `void TickLobby();`
- L128 _protected prototype_ `bool CleanupMatchmaking();`
- L152 _protected member_ `FPendingInviteData PendingInvite;`
- L168 _protected member_ `TOptional<FPendingSessionUserInvite> PendingSessionUserInvite;`
- L170 _protected member_ `const int32 SESSION_INVITE_PROCESSING_LOG_TIMEOUT_SECONDS = 10;`
- L172 _protected member_ `class FOnlineSubsystemGDK* GDKSubsystem;`
- L175 _protected member_ `mutable FCriticalSection SessionLock;` — Critical sections for thread safe operation of session lists
- L178 _protected member_ `TArray<FNamedOnlineSessionRef> Sessions;` — Current sessions
- L180 _protected member_ `TMap<uint64, FMpaActivity> MpaActivitySetByLocalPlayer;`
- L183 _protected member_ `PFMultiplayerHandle PlayfabHandle = nullptr;`
- L202 _protected member_ `MatchmakingState MMState;`

#### struct `FOnlineSessionMpaGDK::FPendingInviteData`  
`struct FPendingInviteData`  
_L131-150_
- L134 _public member_ `bool bHaveInvite = false;` — Whether there is a pending invite or not
- L137 _public member_ `uint64 Sender = 0;` — Cached xuid to the user who send the invite
- L140 _public member_ `FGDKUserHandle AcceptingUser;` — Cached pointer to the user who accepted the invite
- L143 _public member_ `FString ConnectionString;` — Cached connection string to join
- L146 _public member_ `bool bLoggedNotProcessedYet = false;` — Have we logged that we haven't processed this in a timely manner?
- L149 _public member_ `double LoggedNotProcessedYetTime = 0.0;` — Time to log that we haven't processed this yet

#### struct `FOnlineSessionMpaGDK::FPendingSessionUserInvite`  
`struct FPendingSessionUserInvite`  
_L154-166_
- L156 _public function_ `FPendingSessionUserInvite( int32 InAcceptingUserIndex, TSharedRef<FOnlineSessionSearchResult> InSearchResult) : AcceptingUserIndex(InAcceptingUserIndex) , SearchResult(InSearchResult)`
- L164 _public member_ `int32 AcceptingUserIndex;`
- L165 _public member_ `TSharedRef<FOnlineSessionSearchResult> SearchResult;`

#### struct `FOnlineSessionMpaGDK::MatchmakingState`  
`struct MatchmakingState`  
_L184-200_
- L186 _public member_ `const PFMatchmakingTicket* MMticket = nullptr;`
- L187 _public member_ `TArray< FUniqueNetIdRef > MMLocalPlayers;`
- L188 _public member_ `FName MMSessionName;`
- L189 _public member_ `FOnlineSessionSettings MMSessionSettings;`
- L190 _public member_ `PFLobbyHandle MMLobby =nullptr;`
- L191 _public member_ `bool bHost = false;`
- L193 _public function_ `void Reset()`

#### Free symbols / members of external scopes

- L208 _typedef_ `typedef TSharedPtr<FOnlineSessionMpaGDK, ESPMode::ThreadSafe> FOnlineSessionMpaGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlineSessionInterfaceMpsdGDK.h` (Private)


#### class `FOnlineSessionMpsdGDK`  
`class FOnlineSessionMpsdGDK : public TSharedFromThis<FOnlineSessionMpsdGDK, ESPMode::ThreadSafe>`  
_L43-452_
- inherits: `TSharedFromThis<FOnlineSessionMpsdGDK,ESPMode::ThreadSafe>`
- L47 _private member_ `class FOnlineSubsystemGDK* GDKSubsystem;` — Reference to the main GDK subsystem
- L50 _private prototype_ `void Initialize();` — Performs common constructor operations.
- L56 _private prototype_ `void TickPendingInvites(float DeltaTime);` — Tick invites captured from launch URI Waits for a delegate to be listening before triggering
- L61 _private prototype_ `void TickPendingSessionUserInvites(float DeltaTime);` — Waits for OnSessionUserInviteAcceptedDelegate to be bound before triggering, if there is data saved
- L64 _private prototype_ `void OnInitializationStateChanged(const FName& SessionName);` — Handle initialization flow during matchmaking
- L67 _private prototype_ `void OnMemberListChanged(FGDKMultiplayerSessionHandle LiveSession, const FName& SessionName);` — Handle players being added or removed during matchmaking
- L70 _private prototype_ `void OnSessionNeedsInitialState(FName SessionName);` — Read and react to any initial state from the MultiplayerSession after creating/joining
- L72 _private prototype_ `void OnSubscriptionLostDestroyComplete(FName SessionName, bool bWasSuccessful);`
- L85 _private prototype_ `void SaveSessionInvite( FGDKUserHandle AcceptingUser, const XblMultiplayerInviteHandle& SessionHandle );` — Turns a session handle into a Session, then into an FOnlineSessionSearchResult, then triggers the OnSessionInviteAccepted delegates.
- L97 _private prototype_ `void RegisterVoice(const FUniqueNetId& PlayerId);` — Registers and updates voice data for the given player id @param PlayerId player to register with the voice subsystem
- L104 _private prototype_ `void UnregisterVoice(const FUniqueNetId& PlayerId);` — Unregisters a given player id from the voice subsystem @param PlayerId player to unregister with the voice subsystem
- L107 _private prototype_ `void CleanUpOrphanedSessions(FGDKUserHandle User) const;` — Called when signin is complete
- L133 _private member_ `FPendingInviteData PendingInvite;` — Contains information about a join/invite parsed from the protocol activation
- L152 _private member_ `TOptional<FPendingSessionUserInvite> PendingSessionUserInvite;`
- L158 _private prototype_ `int32 GetHostingPlayerNum(const FUniqueNetId& HostNetId) const;` — Get LocalPlayerNum/ControllerId for a Host's netid and -1 on failure
- L163 _private member_ `static const int QOS_PROBE_COUNT = 8;`
- L170 _private prototype_ `FOnlineSessionMpsdGDK(class FOnlineSubsystemGDK* InSubsystem);` — Constructor. @param InSubsystem Pointer to the subsystem that created this object.
- L176 _private prototype_ `void SaveInviteFromActivation(const FString& ActivationUri);` — Parses a protocol activation URI. If it was from an accepted invite, begins the invite accepted flow. @param ActivationUri the protocol activation URI
- L181 _private prototype_ `void Tick(float DeltaTime);` — Session tick for various background tasks
- L189 _private prototype_ `void ReadSettingsFromGDKSessionJson(FGDKMultiplayerSessionHandle GDKSession, FOnlineSession& Session, FGDKContextHandle GDKContext = FGDKContextHandle());` — Read from GDK session document into UE settings @param GDKSession the session object to read settings from @param SessionSettings the settings object to write to
- L197 _private prototype_ `void ReadSettingsFromGDKSearchHandleJson(FGDKMultiplayerSearchHandle SearcHandle, FOnlineSession& Session, FGDKContextHandle GDKContext = FGDKContextHandle());` — Read from GDK session search handle into UE settings @param GDKSession the session object to read settings from @param SessionSettings the settings object to write to
- L198 _private prototype_ `void ReadSettingsFromJson(FString& Json, FOnlineSession& Session, FSessionSettings& NewSettings, FGDKContextHandle GDKContext = FGDKContextHandle());`
- L208 _private prototype_ `static bool WriteSettingsToGDKJson(const FOnlineSessionSettings& UpdatedSessionSettings, FGDKMultiplayerSessionHandle LiveSession, FGDKUserHandle HostUser, FOnlineSubsystemGDK* GDKSubsystem);` — Write from UE settings into Live document (note that this does not write the session back to Live; caller should) @param UpdatedSessionSettings the settings object to read from @param LiveSession the session object to write to @param HostUser the user to mark as the intended host (optional) @param GDKSubsystem the subsystem to use for any necessary operations @return True if the session settings/host were different than the current LiveSession object
- L216 _private prototype_ `static void ExtractJsonMemberSettings(FGDKMultiplayerSessionHandle GDKSession, FString& OutJsonString);` — Extract one FString that contains all the members settings @param LiveSession the session object to read from @param OutJsonString the string to write to
- L219 _private prototype_ `static void UpdateMatchMembersJson(FSessionSettings& UpdatedSettings, FGDKMultiplayerSessionHandle GDKSession);` — Replaces the JSON member list in UpdatedSettings with the latest from MPSDSession
- L222 _private prototype_ `static void UpdateMatchMembers(FOnlineSessionSettings& UpdatedSettings, FGDKMultiplayerSessionHandle GDKSession);` — Replaces the member list in UpdatedSettings with the latest from MPSDSession
- L225 _private prototype_ `void SetCurrentUserActive(FGDKMultiplayerSessionHandle GDKSession, bool bIsActive);` — Mark the user as active within the session
- L228 _private prototype_ `FNamedOnlineSession* GetNamedSessionForGDKSessionRef(const XblMultiplayerSessionReference* GDKSessionRef);` — Look up the NamedSession corresponding to a GDK session reference
- L231 _private prototype_ `TOptional<FName> GetNamedSessionNameForGDKSessionRef(const XblMultiplayerSessionReference* GDKSessionRef);` — Look up the Name of a session corresponding to a GDK session reference
- L234 _private prototype_ `TOptional<FName> GetNamedSessionNameForGDKSessionHandle(const FGDKMultiplayerSessionHandle& GDKSession);` — Look up the Name of a session corresponding to a GDK session handle
- L237 _private prototype_ `FOnlineSessionInfoMpsdGDKPtr GetSessionInfoForGDKSessionRef(const XblMultiplayerSessionReference& GDKSessionRef);` — Look up the SessionInfo corresponding to a GDK session reference
- L240 _private prototype_ `FGDKMultiplayerSessionHandle SetHostDeviceTokenSynchronous(int32 UserNum, FName SessionName, FGDKMultiplayerSessionHandle GDKSession, FGDKContextHandle Context);` — Set me as the host using a host device token, does nothing if token already set. Synchronous, so only use from lambda
- L244 _private prototype_ `static const XblMultiplayerSessionMember* GetCurrentUserFromSession(FGDKMultiplayerSessionHandle GDKSession);` — Get my info from a session
- L247 _private prototype_ `void DetermineSessionHost(FName Session, FGDKMultiplayerSessionHandle GDKSession);` — work out who we want as host and set it in the named session
- L250 _private prototype_ `const XblMultiplayerSessionMember* GetMemberFromDeviceToken(FGDKMultiplayerSessionHandle GDKSession, const FString& DeviceToken);` — Get member from device token
- L253 _private prototype_ `static TSharedPtr<FInternetAddr> GetAddrFromSecureDeviceAddressBase64(const FString& DeviceAddressBase64);` — Turns a base64 secure device address into an FInternetAddr
- L256 _private prototype_ `static FString GetLocalBase64Addr();` — Gets the local ip address and returns as a base64 encoded string.
- L259 _private prototype_ `FOnlineSessionSearchResult CreateSearchResultFromSession( FGDKMultiplayerSessionHandle GDKSession, const FString& HostDisplayName, FGDKContextHandle GDKContext = FGDKContextHandle());` — Uses data from a MultiplayerSession to initialize an FOnlineSessionSearchResult.
- L265 _private prototype_ `FOnlineSessionSearchResult CreateSearchResultFromSearchHandle( FGDKMultiplayerSearchHandle SearchHandle, const FString& HostDisplayName, FGDKContextHandle GDKContext = FGDKContextHandle());` — Uses data from a MultiplayerSession Search handle to initialize an FOnlineSessionSearchResult.
- L271 _private prototype_ `static const XblMultiplayerSessionMember* GetGDKSessionHost( FGDKMultiplayerSessionHandle GDKSession );` — Returns the host of a session, or null if there is no host.
- L275 _private prototype_ `static bool IsConsoleHost( FGDKMultiplayerSessionHandle GDKSession );` — Returns true if the local console is the host of the session
- L277 _private prototype_ `static FString SessionReferenceToUri(const XblMultiplayerSessionReference& MultiplayerReference);`
- L281 _private prototype_ `static bool CanUserJoinSession( FGDKUserHandle JoiningUser, FGDKMultiplayerSessionHandle GDKSession);` — Returns true if the session has either an open slot or a slot reserved for the user.
- L286 _private prototype_ `static XblMultiplayerSessionRestriction GetLiveSessionRestrictionFromSettings(const FOnlineSessionSettings& SessionSettings);` — Returns what the Multiplayer Session restriction should be based on session settings
- L289 _private prototype_ `static bool AreInvitesAndJoinViaPresenceAllowed(const FOnlineSessionSettings& OnlineSessionSettings);` — Returns true if this session allows invites and join in presence
- L292 _private prototype_ `static XblMultiplayerSessionChangeTypes GetSubscriptionType(const FOnlineSessionSettings& SessionSettings);` — Determine the SessionChangeType for the specified settings
- L295 _private prototype_ `void OnMultiplayerConnectionIdChanged();` — Update to new connection id for sessions
- L298 _private prototype_ `void OnMultiplayerSubscriptionsLost();` — On subscription loss, fire appropriate delegate after cleaning up the sessions.
- L301 _private member_ `mutable FCriticalSection SessionLock;` — Critical sections for thread safe operation of session lists
- L304 _private member_ `TSharedPtr<FOnlineSessionSearch> CurrentSessionSearch;` — Current search object
- L307 _private member_ `TArray<FNamedOnlineSessionRef> Sessions;` — Current session settings
- L309 _private member_ `FCriticalSection SessionResultLock;`
- L310 _private member_ `int ExpectedResults;`
- L312 _private member_ `bool bIsDestroyingSessions;` — Synchronization for session changes handlers and destruction on subscription loss
- L313 _private member_ `FOnEndSessionCompleteDelegate OnSubscriptionLostDestroyCompleteDelegate;`
- L314 _private member_ `FDelegateHandle OnSubscriptionLostDestroyCompleteDelegateHandle;`
- L319 _private prototype_ `FNamedOnlineSessionRef AddNamedSessionRef(FName SessionName, const FOnlineSessionSettings& SessionSettings);`
- L320 _private prototype_ `FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSession& Session);`
- L321 _private prototype_ `FNamedOnlineSessionRef AddNamedSessionRef(FName SessionName, const FOnlineSession& Session);`
- L327 _public prototype_ `virtual ~FOnlineSessionMpsdGDK();`
- L330 _public prototype_ `FUniqueNetIdPtr CreateSessionIdFromString(const FString& SessionIdStr);` — IOnlineSession interface
- L331 _public prototype_ `FNamedOnlineSession* GetNamedSession(FName SessionName);`
- L332 _public prototype_ `FNamedOnlineSessionPtr GetNamedSessionPtr(FName SessionName) const;`
- L333 _public prototype_ `void RemoveNamedSession(FName SessionName);`
- L334 _public prototype_ `bool HasPresenceSession() const;`
- L335 _public prototype_ `EOnlineSessionState::Type GetSessionState(FName SessionName) const;`
- L336 _public prototype_ `bool CreateSession(int32 HostingPlayerControllerIndex, FName SessionName, const FOnlineSessionSettings& NewSessionSettings);`
- L337 _public prototype_ `bool CreateSession(const FUniqueNetId& HostingPlayerId, FName SessionName, const FOnlineSessionSettings& NewSessionSettings);`
- L338 _public prototype_ `bool StartSession(FName SessionName);`
- L339 _public prototype_ `bool UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings, bool bShouldRefreshOnlineData = false);`
- L340 _public prototype_ `bool EndSession(FName SessionName);`
- L341 _public prototype_ `bool DestroySession(FName SessionName, const FOnDestroySessionCompleteDelegate& CompletionDelegate = FOnDestroySessionCompleteDelegate());`
- L342 _public prototype_ `bool IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId);`
- L343 _public prototype_ `bool StartMatchmaking(const TArray< FUniqueNetIdRef >& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings);`
- L344 _public prototype_ `bool CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName);`
- L345 _public prototype_ `bool CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, FName SessionName);`
- L346 _public prototype_ `bool FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings);`
- L347 _public prototype_ `bool FindSessions(const FUniqueNetId& SearchingPlayerId, const TSharedRef<FOnlineSessionSearch>& SearchSettings);`
- L348 _public prototype_ `bool FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId, const FUniqueNetId& FriendId, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate);`
- L349 _public prototype_ `bool CancelFindSessions();`
- L350 _public function_ `bool PingSearchResults(const FOnlineSessionSearchResult& SearchResult)`
- L351 _public prototype_ `bool JoinSession(int32 ControllerIndex, FName SessionName, const FOnlineSessionSearchResult& DesiredSession);`
- L352 _public prototype_ `bool JoinSession(const FUniqueNetId& UserId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession);`
- L353 _public prototype_ `bool FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend);`
- L354 _public prototype_ `bool FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend);`
- L355 _public prototype_ `bool FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& FriendList);`
- L356 _public prototype_ `bool SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend);`
- L357 _public prototype_ `bool SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName, const FUniqueNetId& Friend);`
- L358 _public prototype_ `bool SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray< FUniqueNetIdRef >& Friends);`
- L359 _public prototype_ `bool SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName, const TArray< FUniqueNetIdRef >& Friends);`
- L360 _public prototype_ `bool GetResolvedConnectString(FName SessionName, FString& ConnectInfo, FName PortType);`
- L361 _public prototype_ `bool GetResolvedConnectString(const class FOnlineSessionSearchResult& SearchResult, FName PortType, FString& ConnectInfo);`
- L362 _public prototype_ `FOnlineSessionSettings* GetSessionSettings(FName SessionName);`
- L363 _public prototype_ `bool RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited);`
- L364 _public prototype_ `bool RegisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players, bool bWasInvited = false);`
- L365 _public prototype_ `bool UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId);`
- L366 _public prototype_ `bool UnregisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players);`
- L367 _public prototype_ `void RegisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnRegisterLocalPlayerCompleteDelegate& Delegate);`
- L368 _public prototype_ `void UnregisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnUnregisterLocalPlayerCompleteDelegate& Delegate);`
- L369 _public function_ `int32 GetNumSessions()`
- L370 _public function_ `void DumpSessionState()`
- L372 _public prototype_ `void CreateSearchHandle(const FOnlineSessionSettings& SessionSettings, FGDKMultiplayerSessionHandle GDKSession, FGDKContextHandle GDKContext, const FOnCreateSearchHandleCompleteDelegate& Delegate);`
- L375 _public prototype_ `void OnSessionChanged(FName SessionName, XblMultiplayerSessionChangeTypes Diff);` — Use task to get session in response to notification
- L377 _public prototype_ `void OnHostInvalid(const FName& SessionName);`
- L380 _public prototype_ `bool SendSessionInviteToFriends_Internal(FGDKContextHandle GDKContext, FName SessionName, const TArray<uint64>& FriendXuids);` — Handle sending a session invite to friends
- L385 _public prototype_ `void SetUserActiveSessionActivity(const FUniqueNetIdGDK& PlayerId, FGDKMultiplayerSessionHandle GDKSession);` — Set if this user should have an active multiplayer session or not (nullptr for SessionReference)
- L387 _public prototype_ `bool StartCreateSession( const int32 UserIndex, const FOnlineSessionSettings& SessionSettings, const FString& Keyword, const FString& SessionTemplateName, FName SessionName, FOnlineAsyncTaskGDKCreateSession::FOnGDKCreateSessionComplete Delegate);`
- L393 _public prototype_ `bool StartCreateSession( const FUniqueNetId& UserId, const FOnlineSessionSettings& SessionSettings, const FString& Keyword, const FString& SessionTemplateName, FName SessionName, FOnlineAsyncTaskGDKCreateSession::FOnGDKCreateSessionComplete Delegate);`
- L399 _public prototype_ `bool InternalStartCreateSession( FGDKContextHandle GDKContext, const FOnlineSessionSettings& SessionSettings, const FString& Keyword, const FString& SessionTemplateName, FName SessionName, FOnlineAsyncTaskGDKCreateSession::FOnGDKCreateSessionComplete Delegate);`
- L405 _public prototype_ `static const TSharedRef<TArray<XblMultiplayerSessionMember>> GetMemberArray(FGDKMultiplayerSessionHandle Session);`
- L408 _public prototype_ `bool SetHostOnCreatedSession(FGDKMultiplayerSessionHandle GDKSession, uint64 CreatingUserId);` — Sets host on a newly created session
- L410 _public prototype_ `void WriteDTLSCertificatesToService(const TMap<FGuid, TArray<uint8>>& DTLSCertificateDictionary);`
- L412 _public prototype_ `void OnQueryActivitiesComplete(const FOnlineError& ErrorResult, const FOnlineGDKActivitiesResultMap& Results, int32 LocalUserNum, FGDKContextHandle GDKContext);`
- L413 _public prototype_ `void OnQueryFriendSessionDetailsComplete(int32 LocalUserNum, bool bSucceeded, const FOnlineSessionSearchResult& SearchResult, FGDKContextHandle GDKContext);`
- L414 _public prototype_ `static XblMultiplayerSessionRestriction GetGDKSessionRestrictionFromSettings(const FOnlineSessionSettings& SessionSettings);`
- L415 _public prototype_ `void OnGetSessionForInviteComplete(int32 LocalUserNum, bool bWasSuccessful, const FOnlineSessionSearchResult& SearchResult, XblMultiplayerInviteHandle InviteHandle, FUniqueNetIdGDKRef UniqueNetId);`
- L416 _public prototype_ `FNamedOnlineSession* GetNamedSessionForGDKSessionRef(XblMultiplayerSessionReference* GDKSessionRef);`
- L421 _public function_ `void ClearSessionActivityInProgress()` — Clear when finished running queued multiplayer activity async tasks
- L425 _private prototype_ `void SetUserActiveSessionActivity_Impl(const FUniqueNetIdGDK& PlayerId, const bool bWantsToBeInActiveSession, FGDKMultiplayerSessionHandle GDKSession);` — Actually starts a set/clear multiplayer activity async task
- L431 _private member_ `FOnSessionNeedsInitialStateDelegate OnSessionNeedsInitialStateDelegate;` — Initialize session state after create/join
- L433 _private member_ `FOnSessionChangedDelegate OnSessionChangedDelegate;`
- L434 _private member_ `FDelegateHandle OnSubscriptionsLostHandle;`
- L435 _private member_ `FDelegateHandle OnConnectionIdChangedHandle;`
- L438 _private member_ `FString SessionUpdateEventName;` — Event to be called when our session updates
- L441 _private member_ `bool bOnlyHostUpdateSession;` — Whether only the host can update the session or if anyone can
- L444 _private member_ `bool bHandleXblSubscriptionLost;` — Whether to handle the xbl subscription lost
- L447 _private member_ `bool bHasSessionActivityInProgress;` — Do we have a Session Activity Set or Clear in progress?
- L449 _private member_ `TUniqueNetIdMap<TOptional<const FGDKMultiplayerSessionHandle> > QueuedActiveSessionActivities;` — Queued Set/Clear multiplayer session action information
- L451 _private member_ `FUniqueNetIdSet UsersWithActiveSessionActivities;` — List of users who are currently in active sessions

#### struct `FOnlineSessionMpsdGDK::FPendingInviteData`  
`struct FPendingInviteData`  
_L114-130_
- desc: Any join/invite from a protocol activation
- L117 _public member_ `bool bHaveInvite = false;` — Whether there is a pending invite or not
- L120 _public member_ `FGDKUserHandle AcceptingUser;` — Cached pointer to the user who accepted the invite
- L123 _public member_ `XblMultiplayerInviteHandle SessionHandle;` — Cached handle to the session to join
- L126 _public member_ `bool bLoggedNotProcessedYet = false;` — Have we logged that we haven't processed this in a timely manner?
- L129 _public member_ `double LoggedNotProcessedYetTime = 0.0;` — Time to log that we haven't processed this yet

#### struct `FOnlineSessionMpsdGDK::FPendingSessionUserInvite`  
`struct FPendingSessionUserInvite`  
_L138-150_
- desc: We'll use this to store the result of a session search caused by a user invite until the corresponding delegates have been bound
- L140 _public prototype_ `FPendingSessionUserInvite( int32 InAcceptingUserIndex, bool InWasSuccessful, TSharedRef<FOnlineSessionSearchResult> InSearchResult, XblMultiplayerInviteHandle InInviteHandle);`
- L146 _public member_ `int32 AcceptingUserIndex;`
- L147 _public member_ `bool bWasSuccessful;`
- L148 _public member_ `TSharedRef<FOnlineSessionSearchResult> SearchResult;`
- L149 _public member_ `XblMultiplayerInviteHandle InviteHandle;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define LOCTEXT_NAMESPACE "OnlineSubsystemGDK"`
- L23 _macro_ `#define ONLINE_ERROR_NAMESPACE "errors.com.epicgames.oss.session"`
- L25 _typedef_ `using FOnlineGDKActivitiesResultMap = TUniqueNetIdMap<FUniqueNetIdPtr >;`
- L27 _namespace_ `namespace OnlineSessionGDK`
- L31 _namespace_ `namespace Errors` (scope `OnlineSessionGDK`)
- L33 _function_ `inline FOnlineError HResultError(int32 InCode)` (scope `OnlineSessionGDK::Errors`)
- L454 _typedef_ `typedef TSharedPtr<FOnlineSessionMpsdGDK, ESPMode::ThreadSafe> FOnlineSessionMpsdGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlineStatsInterfaceGDK.h` (Private)


#### enum `EGDKStatsMode`  
`enum class EGDKStatsMode : uint16`  
_L12-21_
- L15 _public enumerator_ `Mode2013 = 2013` — 2013 stats are driven via events
- L17 _public enumerator_ `Mode2017 = 2017` — 2017 stats are title-managed
- L20 _public enumerator_ `Default = Mode2013` — Default mode to use if not specified

#### class `FOnlineGDKStatsCache`  
`class FOnlineGDKStatsCache`  
_L24-68_
- desc: Keeps a record of the value of all defined stats per logged in local user
- L30 _private prototype_ `template<typename T> T GetStatValue(FOnlineStatValue* StatValue);` — Template helpers to savely get a stat value
- L33 _private prototype_ `template<> double GetStatValue<double>(FOnlineStatValue* StatValue);`
- L36 _private prototype_ `template<> int64 GetStatValue<int64>(FOnlineStatValue* StatValue);`
- L39 _private prototype_ `template<> uint64 GetStatValue<uint64>(FOnlineStatValue* StatValue);`
- L42 _private prototype_ `template<> FString GetStatValue<FString>(FOnlineStatValue* StatValue);`
- L47 _public prototype_ `template<typename T> void SetStatValueForUser(const FUniqueNetIdRef UserId, const FString& StatNameStr, T Value);` — Template to safely set a stat value for a given user
- L51 _public prototype_ `template<typename T> T GetStatValueForUser(const FUniqueNetIdRef UserId, const FString& StatNameStr);` — Template to safely get a stat value for a given user
- L55 _public prototype_ `template<typename T> bool ApplyStatModification(const FUniqueNetIdRef UserId, const FString& StatName, const FOnlineStatUpdate& StatUpdate, bool& bOutHasUpdatedStat);` — Template to safely apply a stat modification
- L57 _public prototype_ `TArray<FUniqueNetIdRef> GetUsers();`
- L58 _public prototype_ `const FOnlineStatsUserStats* GetStatsForUser(const FUniqueNetIdRef UserId) const;`
- L59 _public prototype_ `void AddUser(const FUniqueNetIdRef UserId);`
- L60 _public prototype_ `void AddStatForUser(const FUniqueNetIdRef UserId, const FString& StatName, const FOnlineStatValue& StatValue);`
- L62 _public prototype_ `void DeleteUser(const FUniqueNetIdRef UserId);`
- L63 _public prototype_ `void DeleteStatForUser(const FUniqueNetIdRef UserId, const FString& StatNameStr);`
- L64 _public prototype_ `void DeleteStatsForUser(const FUniqueNetIdRef UserId);`
- L67 _private member_ `TUniqueNetIdMap<FOnlineStatsUserStats> CachedUserStats;`

#### class `FOnlineStatsGDK`  
`class FOnlineStatsGDK : public IOnlineStats, public TSharedFromThis< FOnlineStatsGDK, ESPMode::ThreadSafe>`  
_L73-147_
- inherits: `IOnlineStats,TSharedFromThis<FOnlineStatsGDK,ESPMode::ThreadSafe>`
- desc: FOnlineStatsGDK - Interface class for stats (GDK implementation)
- L81 _private prototype_ `bool InitFromConfig();`
- L84 _private member_ `class FOnlineSubsystemGDK* GDKSubsystem;` — Pointer to owning live subsystem
- L87 _private member_ `EGDKStatsMode StatsMode = EGDKStatsMode::Default;` — Stats mode used if no mode is specified in the config file
- L89 _private member_ `FOnlineGDKStatsCache StatsCache;`
- L91 _private member_ `FDelegateHandle AppInitComplete;`
- L92 _private member_ `TArray<FDelegateHandle> UserChanged;`
- L95 _private member_ `FDelegateHandle IdentityPIEUsersRefreshedHandle;`
- L103 _public prototype_ `virtual void QueryStats(const FUniqueNetIdRef LocalUserId, const FUniqueNetIdRef StatsUser, const FOnlineStatsQueryUserStatsComplete& Delegate) override;`
- L104 _public prototype_ `virtual void QueryStats(const FUniqueNetIdRef LocalUserId, const TArray<FUniqueNetIdRef>& StatUsers, const TArray<FString>& StatNames, const FOnlineStatsQueryUsersStatsComplete& Delegate) override;`
- L105 _public prototype_ `virtual TSharedPtr<const FOnlineStatsUserStats> GetStats(const FUniqueNetIdRef StatsUserId) const override;`
- L106 _public prototype_ `virtual void UpdateStats(const FUniqueNetIdRef LocalUserId, const TArray<FOnlineStatsUserUpdatedStats>& UpdatedUserStats, const FOnlineStatsUpdateStatsComplete& Delegate) override;`
- L109 _public prototype_ `virtual void ResetStats( const FUniqueNetIdRef StatsUserId ) override;`
- L118 _public prototype_ `FOnlineStatsGDK(class FOnlineSubsystemGDK* InSubsystem);` — Constructor @param InSubsystem - A reference to the owning subsystem
- L123 _public prototype_ `virtual ~FOnlineStatsGDK();` — Default destructor
- L125 _public prototype_ `bool HandleExec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L128 _private prototype_ `bool CopyStatValue(FOnlineStatValue& OutOnlineStatValue, const char* InStatisticValue, const char* InStatisticType) const;`
- L129 _private prototype_ `bool ApplyStatUpdate(const FUniqueNetIdRef& User, const FString& StatName, const FOnlineStatUpdate& StatUpdate);`
- L131 _private prototype_ `FGDKUserHandle GetUser(const FUniqueNetId& LocalUserId) const;`
- L133 _private prototype_ `void HookEvents();`
- L134 _private prototype_ `void UnhookEvents();`
- L136 _private prototype_ `void OnEngineInitComplete();`
- L137 _private prototype_ `void OnUserChanged(int32 GameUserIndex, ELoginStatus::Type PreviousLoginStatus, ELoginStatus::Type LoginStatus, const FUniqueNetId& UserId);`
- L138 _private prototype_ `void OnQueryStatsComplete(const FOnlineError& ResultState, const TSharedPtr<const FOnlineStatsUserStats>& QueriedStats);`
- L139 _private prototype_ `void OnQueryStatsComplete(const FOnlineError& ResultState, const TArray<TSharedRef<const FOnlineStatsUserStats>>& QueriedStats);`
- L142 _private prototype_ `void HandleDumpStatsExecCommand( FUniqueNetIdRef LocalUserId );`
- L143 _private prototype_ `void HandleSetStatExecCommand( FUniqueNetIdRef LocalUserId, const FString& StatName, const FString& Value );`
- L144 _private prototype_ `void HandleDeleteStatExecCommand( FUniqueNetIdRef LocalUserId, const FString& StatName );`
- L145 _private prototype_ `void HandleUsersExecCommand();`

#### Free symbols / members of external scopes

- L149 _typedef_ `typedef TSharedPtr<FOnlineStatsGDK, ESPMode::ThreadSafe> FOnlineStatsGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlineStoreInterfaceGDK.h` (Private)


#### class `FOnlineStoreOfferGDK`  
`class FOnlineStoreOfferGDK : public FOnlineStoreOffer`  
_L18-24_
- inherits: `FOnlineStoreOffer`
- L23 _public member_ `FString SignedOffer;` — Signed value to pass to XBox when purchasing this offer

#### class `FOnlineStoreGDK`  
`class FOnlineStoreGDK : public IOnlineStoreV2 , public TSharedFromThis<FOnlineStoreGDK, ESPMode::ThreadSafe>`  
_L28-70_
- inherits: `IOnlineStoreV2,TSharedFromThis<FOnlineStoreGDK,ESPMode::ThreadSafe>`
- L33 _public prototype_ `FOnlineStoreGDK(FOnlineSubsystemGDK* InGDKSubsystem);`
- L34 _public prototype_ `virtual ~FOnlineStoreGDK();`
- L38 _public prototype_ `virtual void QueryCategories(const FUniqueNetId& UserId, const FOnQueryOnlineStoreCategoriesComplete& Delegate = FOnQueryOnlineStoreCategoriesComplete()) override;`
- L39 _public prototype_ `virtual void GetCategories(TArray<FOnlineStoreCategory>& OutCategories) const override;`
- L40 _public prototype_ `virtual void QueryOffersByFilter(const FUniqueNetId& UserId, const FOnlineStoreFilter& Filter, const FOnQueryOnlineStoreOffersComplete& Delegate = FOnQueryOnlineStoreOffersComplete()) override;`
- L41 _public prototype_ `virtual void QueryOffersById(const FUniqueNetId& UserId, const TArray<FUniqueOfferId>& OfferIds, const FOnQueryOnlineStoreOffersComplete& Delegate = FOnQueryOnlineStoreOffersComplete()) override;`
- L42 _public prototype_ `virtual void GetOffers(TArray<FOnlineStoreOfferRef>& OutOffers) const override;`
- L43 _public prototype_ `virtual TSharedPtr<FOnlineStoreOffer> GetOffer(const FUniqueOfferId& OfferId) const override;`
- L46 _public prototype_ `XStoreContextHandle GetStoreContextHandle(FGDKUserHandle GDKUser);`
- L47 _public prototype_ `bool BlockMismatchedStoreUser(const FGDKUserHandle GDKUser);`
- L52 _public prototype_ `void HandleAppSuspend();`
- L53 _public prototype_ `void HandleAppResume();`
- L55 _public prototype_ `void OnConsoleLoginStatusChanged(int32 LocalUserNum, ELoginStatus::Type OldStatus, ELoginStatus::Type NewStatus, const FUniqueNetId& NewId);`
- L60 _public member_ `TMap<FUniqueOfferId, FOnlineStoreOfferRef> CachedOffers;`
- L62 _public member_ `TMap<FGDKUserHandle, XStoreContextHandle> StoreContexts;`
- L63 _public member_ `mutable FCriticalSection StoreContextsLock;`
- L65 _public member_ `std::atomic<bool> bStoreContextHandlesInvalidated = false;`
- L69 _private member_ `bool bBlockOnStoreIDMismatch;` — Should we block store interaction if the title and MSstore IDs do not match?

#### Free symbols / members of external scopes

- L26 _typedef_ `using FOnlineStoreOfferGDKRef = TSharedRef<FOnlineStoreOfferGDK>;`
- L72 _typedef_ `typedef TSharedPtr<FOnlineStoreGDK, ESPMode::ThreadSafe> FOnlineStoreGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlineSubsystemGDKPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define INVALID_INDEX -1`
- L10 _macro_ `#define GDK_URL_PREFIX TEXT("GDK.")` — URL Prefix when using Live socket connection
- L14 _macro_ `#define ONLINE_LOG_PREFIX TEXT("GDK: ")`
- L17 _macro_ `#define GDK_GLOBAL_SCID TEXT("7492baca-c1b4-440d-a391-b7ef364a8d40")` — global SCID used for non-title-specific queries (e.g. user reputation)
- L20 _macro_ `#define BAD_REPUTATION_ATTRIBUTE TEXT("BadReputation")` — Attribute to use to read the IsBadReputation attribute off a local-user

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/OnlineVoiceInterfaceGDK.h` (Private)


#### struct `FRemoteTalkerGDK`  
`struct FRemoteTalkerGDK : public FRemoteTalker`  
_L31-52_
- inherits: `FRemoteTalker`
- L34 _public member_ `xbox::services::game_chat_2::chat_user* ChatUser;`
- L35 _public member_ `uint64 ConsoleId;`
- L36 _public member_ `bool bReceivedData;`
- L37 _public member_ `uint32 LastPacketIndex;`
- L41 _public function_ `FRemoteTalkerGDK(const FUniqueNetIdRef InGDKId, xbox::services::game_chat_2::chat_user* InRemoteChatUser, const uint64 InConsoleId) : ChatUser(InRemoteChatUser) , ConsoleId(InConsoleId) , bReceivedData(false) , LastPacketIndex(0u)` — Constructor to take reference to remote chat user
- L51 _private prototype_ `FRemoteTalkerGDK() = delete;`

#### struct `FLocalTalkerGDK`  
`struct FLocalTalkerGDK : public FLocalTalker`  
_L54-71_
- inherits: `FLocalTalker`
- L58 _public member_ `const FUniqueNetIdRef LocalTalkerId;` — GDK Net ID of this local user
- L60 _public member_ `xbox::services::game_chat_2::chat_user* ChatUser;` — Microsoft Chat User object
- L64 _public function_ `FLocalTalkerGDK(const FUniqueNetIdRef& InTalkerId, xbox::services::game_chat_2::chat_user* InChatUser) : LocalTalkerId(InTalkerId) , ChatUser(InChatUser)` — Constructor

#### class `FOnlineVoiceGDK`  
`class FOnlineVoiceGDK : public IOnlineVoice , public TSharedFromThis<FOnlineVoiceGDK, ESPMode::ThreadSafe>`  
_L76-252_
- inherits: `IOnlineVoice,TSharedFromThis<FOnlineVoiceGDK,ESPMode::ThreadSafe>`
- desc: The GDK implementation of the voice interface
- L81 _private member_ `class FOnlineSubsystemGDK* const GDKSubsystem;` — Reference to the main GDK subsystem
- L84 _private member_ `xbox::services::game_chat_2::chat_manager& ChatManager;` — Reference to chat manager
- L87 _private member_ `int32 MaxLocalTalkers;` — Maximum permitted local talkers
- L89 _private member_ `int32 MaxRemoteTalkers;` — Maximum permitted remote talkers
- L92 _private member_ `TArray<TSharedRef<FLocalTalkerGDK> > LocalTalkers;` — State of all possible local talkers
- L94 _private member_ `TArray<TSharedRef<FRemoteTalkerGDK> > RemoteTalkers;` — State of all possible remote talkers
- L97 _private member_ `float VoiceNotificationDelta;` — Time to wait for new data before triggering "not talking"
- L100 _private member_ `FGDKVoicePacketArray PendingLocalPackets;` — Buffered voice data I/O
- L101 _private member_ `FGDKVoicePacketArray LocalPackets;`
- L102 _private member_ `FGDKVoicePacketArray RemotePackets;`
- L105 _private member_ `FCriticalSection LocalPacketsCS;` — Critical sections for threadsafeness
- L106 _private member_ `FCriticalSection RemotePacketsCS;`
- L110 _private member_ `bool DebugDisplayEnabled;` — Turn on or off debug display/verbose output
- L114 _private member_ `uint32 LocalPacketIndex;` — Next packet index to send. Only used to track dropped/misordered packets
- L117 _private member_ `bool bChatManagerInitialized;` — Is the chat manager currently initialized?
- L123 _private prototype_ `void InitializeChatManager();` — Hook up the XBL callbacks
- L129 _private prototype_ `void CleanupChatManager();` — Clean up the XBL Callbacks
- L134 _private prototype_ `void TryRemoveChatUserFromChatManager(xbox::services::game_chat_2::chat_user* ChatUser);` — Check if the ChatUser is part of the ChatManager, then remove it
- L143 _private prototype_ `bool MuteRemoteTalkerGDK(const FUniqueNetId& LocalPlayerId, const FUniqueNetId& RemotePlayerId, const bool bNewMutedState);` — Tell GDK to mute/unmute a remote player @param LocalPlayerId Local player to mute for @param RemotePlayerId Remote player to mute @param bNewMutedState true to mute, false to unmute
- L150 _private prototype_ `void SetLocalPlayerIsTalking(FUniqueNetIdPtr talker);` — Mark a local player as being talking @param NewTalkerId player who is talking
- L157 _private prototype_ `FUniqueNetIdPtr GetFirstRegisteredLocalPlayer();` — Get the first registered local player @return First registered local player
- L166 _private prototype_ `bool UnregisterLocalTalkerByUniqueId(const FUniqueNetId& UniqueId);` — Unregister a local talker using their unique net id @param UniqueId player to unregister @return True if the player was unregistered
- L172 _private prototype_ `void DisplayDebugText(TMultiMap<FCoreDelegates::EOnScreenMessageSeverity, FText>& OutMessages);` — Display all talkers and their status
- L177 _private prototype_ `void DisplayUserStatus(const xbox::services::game_chat_2::chat_user* ChatUser, TMultiMap<FCoreDelegates::EOnScreenMessageSeverity, FText>& OutMessages);` — Display an individual user
- L189 _private prototype_ `void ProcessLocalVoicePackets();` — Submits voice packets from the local users to the network
- L192 _private prototype_ `void ProcessLocalVoicePacket(const xbox::services::game_chat_2::game_chat_data_frame& VoiceFrame);` — Process a specific voice packet
- L197 _private prototype_ `void ProcessRemoteVoicePackets();` — Submits network packets to audio system for playback
- L202 _private prototype_ `void ProcessMuteChangeNotification() override;` — Re-evaluates the muting list for all local talkers
- L207 _private prototype_ `virtual bool Init() override;` — Initialize the voice interface
- L210 _private prototype_ `TSharedPtr<FLocalTalkerGDK> GetLocalTalker(const int32 LocalUserNum) const;` — Get our cached local talker if there is one for this user
- L211 _private prototype_ `TSharedPtr<FLocalTalkerGDK> GetLocalTalker(const FUniqueNetId& NetId) const;`
- L214 _private prototype_ `TSharedPtr<FRemoteTalkerGDK> GetRemoteTalker(const FUniqueNetId& NetId) const;` — Get our cached remote talker if this is one for this user
- L218 _public prototype_ `FOnlineVoiceGDK() = delete;` — Constructors
- L219 _public prototype_ `FOnlineVoiceGDK(class FOnlineSubsystemGDK* const InGDKSubsystem);`
- L222 _public prototype_ `virtual ~FOnlineVoiceGDK();` — Virtual destructor to force proper child cleanup
- L224 _public prototype_ `virtual void StartNetworkedVoice(uint8 LocalUserNum) override;`
- L225 _public prototype_ `virtual void StopNetworkedVoice(uint8 LocalUserNum) override;`
- L226 _public prototype_ `virtual bool RegisterLocalTalker(uint32 LocalUserNum) override;`
- L227 _public prototype_ `bool RegisterLocalTalker(const FUniqueNetId& LocalPlayer);`
- L228 _public prototype_ `virtual void RegisterLocalTalkers() override;`
- L229 _public prototype_ `virtual bool UnregisterLocalTalker(uint32 LocalUserNum) override;`
- L230 _public prototype_ `virtual void UnregisterLocalTalkers() override;`
- L231 _public prototype_ `virtual bool RegisterRemoteTalker(const FUniqueNetId& UniqueId) override;`
- L232 _public prototype_ `virtual bool UnregisterRemoteTalker(const FUniqueNetId& UniqueId) override;`
- L233 _public prototype_ `virtual void RemoveAllRemoteTalkers() override;`
- L234 _public prototype_ `virtual bool IsHeadsetPresent(uint32 LocalUserNum) override;`
- L235 _public prototype_ `virtual bool IsLocalPlayerTalking(uint32 LocalUserNum) override;`
- L236 _public prototype_ `virtual bool IsRemotePlayerTalking(const FUniqueNetId& UniqueId) override;`
- L237 _public prototype_ `bool IsMuted(uint32 LocalUserNum, const FUniqueNetId& UniqueId) const override;`
- L238 _public prototype_ `bool MuteRemoteTalker(uint8 LocalUserNum, const FUniqueNetId& PlayerId, bool bIsSystemWide) override;`
- L239 _public prototype_ `bool UnmuteRemoteTalker(uint8 LocalUserNum, const FUniqueNetId& PlayerId, bool bIsSystemWide) override;`
- L240 _public prototype_ `virtual TSharedPtr<class FVoicePacket> SerializeRemotePacket(FArchive& Ar) override;`
- L241 _public prototype_ `virtual TSharedPtr<class FVoicePacket> GetLocalPacket(uint32 LocalUserNum) override;`
- L242 _public prototype_ `virtual int32 GetNumLocalTalkers() override;`
- L243 _public prototype_ `virtual void ClearVoicePackets() override;`
- L244 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L245 _public prototype_ `virtual FString GetVoiceDebugState() const override;`
- L247 _protected prototype_ `void OnApplicationWillEnterBackground();`
- L248 _protected prototype_ `void OnApplicationHasEnteredForeground();`
- L250 _protected prototype_ `virtual IVoiceEnginePtr CreateVoiceEngine() override;`

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef TArray< TSharedRef<FVoicePacketGDK> > FGDKVoicePacketArray;` — WMM TODO - This is shared with the live implementation.. Find a way to use the same class?
- L16 _namespace_ `namespace xbox`
- L18 _namespace_ `namespace services` (scope `xbox`)
- L20 _namespace_ `namespace game_chat_2` (scope `xbox::services`)
- L254 _typedef_ `typedef TSharedPtr<FOnlineVoiceGDK, ESPMode::ThreadSafe> FOnlineVoiceGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/SessionMessageRouter.h` (Private)


#### class `FSessionMessageRouter`  
`class FSessionMessageRouter : public TSharedFromThis<FSessionMessageRouter, ESPMode::ThreadSafe>`  
_L31-111_
- inherits: `TSharedFromThis<FSessionMessageRouter,ESPMode::ThreadSafe>`
- L55 _private typedef_ `typedef TDoubleLinkedList<FSessionChangedDelegatePair> DelegateList;`
- L56 _private member_ `DelegateList RegisteredDelegates;`
- L57 _private member_ `mutable FCriticalSection DelegateLock;`
- L60 _public prototype_ `FSessionMessageRouter(class FOnlineSubsystemGDK* InSubsystem);`
- L61 _public prototype_ `virtual ~FSessionMessageRouter() = default;`
- L63 _public prototype_ `void TriggerOnSessionChangedDelegates( const XblMultiplayerSessionReference* SessionReference, FName SessionName, XblMultiplayerSessionChangeTypes Diff) const;`
- L68 _public prototype_ `void AddOnSessionChangedDelegate(const FOnSessionChangedDelegate& Delegate, const XblMultiplayerSessionReference* SessionReference);`
- L69 _public prototype_ `void ClearOnSessionChangedDelegate(const FOnSessionChangedDelegate& Delegate, const XblMultiplayerSessionReference* SessionReference);`
- L73 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnSessionNeedsInitialState, FName);` — Delegates
- L74 _public prototype_ `DEFINE_ONLINE_DELEGATE(OnConnectionIdChanged);`
- L75 _public prototype_ `DEFINE_ONLINE_DELEGATE(OnSubscriptionsLost);`
- L77 _public prototype_ `void SyncInitialSessionState(FName SessionName, FGDKMultiplayerSessionHandle Session);`
- L81 _public prototype_ `void SetLastProcessedChangeNumber(const FString& Branch, uint64 ChangeNumber);`
- L84 _public prototype_ `void OnMultiplayerSessionChanged(const XblMultiplayerSessionChangeEventArgs& EventArgs);` — Handle changes to the game session
- L85 _public prototype_ `void GetUpdatedSessionAndCompare(const XblMultiplayerSessionChangeEventArgs& EventArgs);`
- L86 _public prototype_ `void OnGetSessionForCompareComplete(int32 UserIndex, bool bSuccessful, const FOnlineSessionSearchResult& SearchResult, const XblMultiplayerSessionChangeEventArgs EventArgs, FName SessionName);`
- L88 _public prototype_ `void OnMultiplayerConnectionIdChanged();`
- L89 _public prototype_ `void OnMultiplayerSubscriptionLost();`
- L92 _private prototype_ `const XblMultiplayerSessionReference* GetGDKSessionRefForSessionName(const FName& SessionName) const;`
- L93 _private prototype_ `FName GetSessionNameForGDKSessionRef(const XblMultiplayerSessionReference& LiveSessionRef);`
- L96 _private prototype_ `FSessionMessageRouter(const FSessionMessageRouter&) = delete;` — Prevent copies
- L97 _private prototype_ `FSessionMessageRouter& operator=(const FSessionMessageRouter&) = delete;`
- L100 _private prototype_ `void OnMultiplayerSubscriptionsLost(FGDKUserHandle User);` — Detect a loss of connection to the subscription service and exit multiplayer.
- L103 _private prototype_ `void OnMultiplayerSessionChanged(XblMultiplayerSessionChangeEventArgs& EventArgs);` — Handle changes to the game session
- L106 _private member_ `class FOnlineSubsystemGDK* GDKSubsystem;`
- L108 _private member_ `TMap<FString, uint64> LastSeenChangeNumberMap, LastProcessedChangeNumberMap;`
- L108 _private member_ `TMap<FString, uint64> LastSeenChangeNumberMap, LastProcessedChangeNumberMap;`
- L109 _private member_ `FCriticalSection LastSeenChangeNumberMapLock, LastProcessedChangeNumberMapLock;`
- L109 _private member_ `FCriticalSection LastSeenChangeNumberMapLock, LastProcessedChangeNumberMapLock;`

#### struct `FSessionMessageRouter::FSessionChangedDelegatePair`  
`struct FSessionChangedDelegatePair`  
_L33-53_
- L35 _public member_ `XblMultiplayerSessionReference SessionReference;`
- L36 _public member_ `const FOnSessionChangedDelegate& Delegate;`
- L38 _public function_ `FSessionChangedDelegatePair(const FOnSessionChangedDelegate& InDelegate, const XblMultiplayerSessionReference& InSessionReference) : SessionReference(InSessionReference) , Delegate(InDelegate)`
- L45 _public prototype_ `bool BoundTo(const XblMultiplayerSessionReference& SessionReference) const;`
- L47 _public prototype_ `bool Equals(const FSessionChangedDelegatePair& Other) const;`
- L49 _public function_ `bool operator== (const FSessionChangedDelegatePair& Other) const`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSessionNeedsInitialState, FName);`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSessionNeedsInitialState, FName);`
- L20 _typedef_ `typedef FOnSessionNeedsInitialState::FDelegate FOnSessionNeedsInitialStateDelegate;`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSessionChanged, FName, XblMultiplayerSessionChangeTypes);`
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSessionChanged, FName, XblMultiplayerSessionChangeTypes);`
- L23 _typedef_ `typedef FOnSessionChanged::FDelegate FOnSessionChangedDelegate;`
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnConnectionIdChanged);`
- L25 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnConnectionIdChanged);`
- L26 _typedef_ `typedef FOnConnectionIdChanged::FDelegate FOnConnectionIdChangedDelegate;`
- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSubscriptionsLost);`
- L28 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSubscriptionsLost);`
- L29 _typedef_ `typedef FOnSubscriptionsLost::FDelegate FOnSubscriptionsLostDelegate;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/SimpleTokenParser.h` (Private)


#### enum `ESimpleTokenType`  
`enum ESimpleTokenType`  
_L11-18_
- desc: ESimpleTokenType
- L13 _public enumerator_ `TOKEN_None = 0x00` — No token.
- L14 _public enumerator_ `TOKEN_Identifier = 0x01` — Alphanumeric identifier.
- L15 _public enumerator_ `TOKEN_Symbol = 0x02` — Symbol.
- L16 _public enumerator_ `TOKEN_Const = 0x03` — A constant.
- L17 _public enumerator_ `TOKEN_Max = 0x0D`

#### class `FSimpleToken`  
`class FSimpleToken`  
_L23-111_
- desc: FSimpleToken - Information about a token that was just parsed.
- L27 _public member_ `EPropertyType PropertyType;` — PropertyType of token.
- L30 _public member_ `ESimpleTokenType TokenType;` — Type of token.
- L33 _public member_ `int32 StartPos;` — Starting position in script where this token came from.
- L37 _public member_ `int32 StartLine;`
- L40 _public member_ `TCHAR Identifier[NAME_SIZE];` — Always valid.
- L52 _public function_ `FSimpleToken()` — Constructors.
- L55 _public function_ `void InitToken( EPropertyType InType )` — Inlines.
- L64 _public function_ `bool Matches( const TCHAR* Str, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase ) const`
- L68 _public function_ `bool StartsWith( const TCHAR* Str, bool bCaseSensitive = false ) const`
- L73 _public function_ `bool IsBool() const`
- L80 _public function_ `void SetConstInt( int32 InInt )`
- L87 _public function_ `void SetConstBool( bool InBool )`
- L94 _public function_ `void SetConstFloat( float InFloat )`
- L101 _public function_ `void SetConstString( TCHAR* InString, int32 MaxLength=MAX_STRING_CONST_SIZE )`

#### union `FSimpleToken::(anonymous)`  
``  
_L43-49_

#### class `FSimpleTokenParser`  
`class FSimpleTokenParser`  
_L116-152_
- desc: FSimpleTokenParser - Parser logic ripped from BaseParser.cpp
- L119 _public prototype_ `FSimpleTokenParser();`
- L121 _public prototype_ `void ResetParser( const TCHAR* SourceBuffer, int32 StartingLineNumber );`
- L122 _public prototype_ `TCHAR PeekChar();`
- L123 _public prototype_ `void UngetChar();`
- L124 _public prototype_ `bool IsEOL( TCHAR c );`
- L125 _public prototype_ `bool IsWhitespace( TCHAR c );`
- L126 _public prototype_ `TCHAR GetChar( bool bLiteral = false );`
- L127 _public prototype_ `TCHAR GetLeadingChar();`
- L128 _public prototype_ `void ClearComment();`
- L129 _public prototype_ `bool GetToken( FSimpleToken & Token, bool bNoConsts = false );`
- L130 _public prototype_ `bool ExpectToken( FSimpleToken & Token, TCHAR* Expected );`
- L133 _public member_ `const TCHAR* Input;` — Input text.
- L136 _public member_ `int32 InputLen;` — Length of input text.
- L139 _public member_ `int32 InputPos;` — Current position in text.
- L142 _public member_ `int32 InputLine;` — Current line in text.
- L145 _public member_ `int32 PrevPos;` — Position previous to last GetChar() call.
- L148 _public member_ `int32 PrevLine;` — Line previous to last GetChar() call.
- L151 _public member_ `FString PrevComment;` — Previous comment parsed by GetChar() call.

#### Free symbols / members of external scopes

- L45 _member_ `int32 Int;` (scope `FSimpleToken::__anon3bb5d491010a`) — TOKEN_Const values.
- L46 _member_ `bool NativeBool;` (scope `FSimpleToken::__anon3bb5d491010a`) — if CPT_Bool
- L47 _member_ `float Float;` (scope `FSimpleToken::__anon3bb5d491010a`) — If CPT_Float.
- L48 _member_ `TCHAR String[MAX_STRING_CONST_SIZE];` (scope `FSimpleToken::__anon3bb5d491010a`) — If CPT_String

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Private/VoicePacketGDK.h` (Private)


#### class `FVoicePacketGDK`  
`class FVoicePacketGDK : public FVoicePacket`  
_L10-64_
- inherits: `FVoicePacket`
- desc: Defines the data involved in a Live voice packet
- L16 _private member_ `TArray<FUniqueNetIdRef > TargetList;` — The unique net id of the machine we're sending the data to, empty if a broadcast message
- L18 _private member_ `TArray<uint8> Buffer;` — The data that is to be sent/processed
- L20 _private member_ `uint16 Length;` — The current amount of space used in the buffer for this packet
- L22 _private member_ `uint32 PacketIndex;` — What index is this packet?
- L24 _private member_ `bool bIsReliable;` — Is this packet reliable (MUST be sent)?
- L28 _public function_ `FVoicePacketGDK() : Length(0u) , PacketIndex(0u) , bIsReliable(false)` — Zeros members and validates the assumptions
- L37 _public prototype_ `virtual ~FVoicePacketGDK() = default;` — Should only be used by TSharedPtr and FVoiceData
- L45 _public prototype_ `FVoicePacketGDK(const FVoicePacketGDK& Other);` — Copies another packet and inits the ref count @param Other packet to copy @param InRefCount the starting ref count to use
- L48 _public prototype_ `virtual uint16 GetTotalPacketSize() override;` — Returns the amount of space this packet will consume in a buffer
- L51 _public prototype_ `virtual uint16 GetBufferSize() override;` — @return the amount of space used by the internal voice buffer
- L54 _public prototype_ `virtual FUniqueNetIdPtr GetSender() override;` — @return the sender of this voice packet
- L56 _public function_ `virtual bool IsReliable() override`
- L63 _public prototype_ `virtual void Serialize(class FArchive& Ar) override;` — Serialize the voice packet data to a buffer @param Ar buffer to write into

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Public/OnlineIdentityInterfaceGDK.h` (Public)


#### class `FOnlineIdentityGDK`  
`class FOnlineIdentityGDK : public IOnlineIdentity , public TSharedFromThis<FOnlineIdentityGDK, ESPMode::ThreadSafe>`  
_L37-258_
- inherits: `IOnlineIdentity,TSharedFromThis<FOnlineIdentityGDK,ESPMode::ThreadSafe>`
- L50 _private member_ `class FOnlineSubsystemGDK* GDKSubsystem;` — Reference to the owning subsystem
- L54 _public prototype_ `virtual ~FOnlineIdentityGDK();`
- L58 _public prototype_ `virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;`
- L59 _public prototype_ `virtual bool Logout(int32 LocalUserNum) override;`
- L60 _public prototype_ `virtual bool AutoLogin(int32 LocalUserNum) override;`
- L61 _public prototype_ `virtual TSharedPtr<FUserOnlineAccount> GetUserAccount(const FUniqueNetId& UserId) const override;`
- L62 _public prototype_ `virtual TArray<TSharedPtr<FUserOnlineAccount> > GetAllUserAccounts() const override;`
- L63 _public prototype_ `virtual FUniqueNetIdPtr GetUniquePlayerId(int32 LocalUserNum) const override;`
- L65 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(uint8* Bytes, int32 Size) override;` — virtual FUniqueNetIdPtr GetSponsorUniquePlayerId(int32 LocalUserNum) const override;
- L66 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(const FString& Str) override;`
- L67 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(int32 LocalUserNum) const override;`
- L68 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(const FUniqueNetId& UserId) const override;`
- L69 _public prototype_ `virtual FString GetPlayerNickname(int32 LocalUserNum) const override;`
- L70 _public prototype_ `virtual FString GetPlayerNickname(const FUniqueNetId& UserId) const override;`
- L71 _public prototype_ `virtual FString GetAuthToken(int32 LocalUserNum) const override;`
- L72 _public prototype_ `virtual void RevokeAuthToken(const FUniqueNetId& UserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate) override;`
- L73 _public prototype_ `virtual void GetUserPrivilege(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate, EShowPrivilegeResolveUI ShowResolveUI = EShowPrivilegeResolveUI::Default) override;`
- L74 _public prototype_ `virtual FPlatformUserId GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& UniqueNetId) const override;`
- L75 _public prototype_ `virtual FString GetAuthType() const override;`
- L76 _public prototype_ `virtual void GetLinkedAccountAuthToken(int32 LocalUserNum, const FString& TokenType, const FOnGetLinkedAccountAuthTokenCompleteDelegate& Delegate) const override;`
- L81 _public prototype_ `void SetUserXSTSToken(FGDKUserHandle User, const FString& AuthToken);` — Sets a user's XSTS token (adding the user to the internal map if they're not already in it)
- L83 _public prototype_ `void ResolvePrivilegeWithUIComplete(bool bWasSuccessful, const FUniqueNetIdGDKRef GDKUserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate Delegate);`
- L84 _public prototype_ `void CheckForGDKPackageUpdate(XUserPrivilegeDenyReason DenyReason, const FUniqueNetIdGDKRef& GDKUserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate);`
- L85 _public prototype_ `void PatchCheckCompletion(const FOnlineError& ErrorResult, const TOptional<ECheckForPackageUpdateResult> OptionalPatchCheckResult, const FUniqueNetIdGDKRef GDKUserId, EUserPrivileges::Type Privilege, XUserPrivilegeDenyReason DenyReason, const FOnGetUserPrivilegeCompleteDelegate Delegate);`
- L87 _public function_ `float GetPrivilegeCheckDelay()`
- L88 _public prototype_ `void Tick(const float DeltaTime);`
- L91 _public prototype_ `DEFINE_ONLINE_DELEGATE(OnPIEUsersRefreshed);`
- L100 _private prototype_ `void HookGDKEvents();` — Sets up event handlers for Xbox system events about users changing so that the user cache is updated accordingly
- L105 _private prototype_ `void UnhookGDKEvents();` — Removes the event handlers that were set up in HookGDKEvents()
- L110 _private prototype_ `void HandleAppResume();` — Delegate called when app resumes from suspend.
- L120 _public prototype_ `FGDKUserHandle GetUserForUniqueNetId(const FUniqueNetIdGDK& UniqueId) const;` — Searches the cache of Users for one that matches the UniqueId and returns it if found. @param UniqueId The unique net id to look for. @return A FGDKUserHandle* matching UniqueId if found, nullptr if a user was not found.
- L129 _public prototype_ `FGDKUserHandle GetUserForPlatformUserId(int32 ControllerIndex) const;` — Helper method to translate Controller Index request to User @param ControllerIndex the controller index to use @return The FGDKUserHandle* associated with the controller index, or nullptr if no users are found
- L138 _public prototype_ `FPlatformUserId GetPlatformUserIdFromGDKUser(FGDKUserHandle InUser) const;` — Helper method to translate an GDK User to PlatformUserId @param InUser the user to look up @return The platform user id associated with the user, or PLATFORMUSERID_NONE if not found.
- L147 _public prototype_ `FString GetPlayerNickname(const FGDKUserHandle RequestedUser) const;` — Helper method to get a player's nickname from an FGDKUserHandle @param RequestedUser the user to look up @return The platform user id associated with the user, or PLATFORMUSERID_NONE if not found.
- L158 _public prototype_ `void RefreshGamepadsAndUsers();` — Refresh cached Gamepads and Users when GDK events fire
- L166 _public prototype_ `TArray<FGDKUserHandle>& GetCachedUsers();` — Windows::Foundation::Collections::IVectorView<FGDKUserHandle*>^ GetCachedUsers() const;
- L172 _private prototype_ `void OnEngineInitComplete();` — Hook into engine initialization completion to add input delegates
- L178 _private prototype_ `void OnPostPIEStarted(bool bIsSimulatingInEditor);` — Hook into the editor's post PIE started event
- L182 _private prototype_ `bool AddUserAccount(FGDKUserHandle InUser);` — Create an FUserOnlineAccount for a GDK User
- L185 _private prototype_ `bool RemoveUserAccount(FGDKUserHandle InUser);` — Remove an FUserOnlineAccount for a GDK User
- L192 _private prototype_ `void OnUserAdded(FGDKUserHandle InUserAdded);` — Delegate fired when the input system adds a new user @param InUserAdded pointer to GDK user added to the system
- L199 _private prototype_ `void OnUserRemoved(FGDKUserHandle InUserRemoved);` — Delegate fired when the input system adds a new user @param InUserRemoved pointer to GDK user removed from the system
- L208 _private prototype_ `void OnInputDeviceConnectionChange(EInputDeviceConnectionState NewConnectionState, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId);` — Callback for handling an Input Device's connection state change. @param NewConnectionState	The new connection state of this device @param FPlatformUserId		The User ID whose input device has changed @param FInputDeviceId		The Input Device ID that has changed connection
- L219 _private prototype_ `void OnInputDevicePairingChange(FInputDeviceId InputDeviceId, FPlatformUserId NewUserPlatformId, FPlatformUserId OldUserPlatformId);` — Delegate fired when the input system notes a controller pairing change Can be multiple firings for one "action"  (olduser->null) then (null->newuser) User can be the same user (when connecting the USB cable for instance) @param FInputDeviceId	Input device ID @param FPlatformUserId	The NewUserPlatformId @param FPlatformUserId	The OldUserPlatformId
- L227 _private prototype_ `void OnReputationQueryComplete(const TUniqueNetIdMap<bool>& UserIsBadMap);` — Callback for querying the bOverallReputationIsBad state for our local users. If the user's bool is true, they are considered a bad user. @param UserIsBadMap A Map of GDK net ids to a bool if they are bad or not
- L230 _private member_ `TArray<FGDKUserHandle > CachedUsers;` — Cached list of users
- L233 _private member_ `mutable FCriticalSection CachedUsersLock;` — Lock for updating/reading CachedUsers vector
- L236 _private member_ `FDelegateHandle AppInitComplete;` — Stored delegate handle to remove the task later
- L237 _private member_ `FDelegateHandle InputDeviceConnectionChanged;`
- L238 _private member_ `FDelegateHandle InputDevicePairingChanged;`
- L239 _private member_ `FDelegateHandle UserLoginChanged;`
- L241 _private member_ `FDelegateHandle PostPIEStartedHandle;`
- L249 _private member_ `FDelegateHandle AppResumeDelegateHandle;`
- L252 _private typedef_ `typedef TUniqueNetIdMap<TSharedRef<FUserOnlineAccountGDK>> GDKUserAccountMap;` — Map of online user accounts (using user id as key)
- L253 _private member_ `GDKUserAccountMap OnlineUsers;`
- L255 _private member_ `float PrivilegeCheckDelayOnResume = 2.5f;`
- L256 _private member_ `float PendingPrivilegeCheckDelay = PrivilegeCheckDelayOnResume;`

#### class `FUserOnlineAccountGDK`  
`class FUserOnlineAccountGDK : public FUserOnlineAccount`  
_L260-326_
- inherits: `FUserOnlineAccount`
- L269 _public prototype_ `virtual FString GetAccessToken() const override;` — @return Access token which is provided to user once authenticated by the online service
- L273 _public prototype_ `virtual bool GetAuthAttribute(const FString& AttrName, FString& OutAttrValue) const override;` — @return Any additional auth data associated with a registered user
- L277 _public prototype_ `virtual bool SetUserAttribute(const FString& AttrName, const FString& AttrValue) override;` — @return True, if the data has been changed
- L281 _public prototype_ `virtual FUniqueNetIdRef GetUserId() const override;` — Id associated with the user account provided by the online service during registration
- L283 _public prototype_ `virtual FString GetRealName() const override;` — Real name for the user if known
- L285 _public prototype_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override;` — Nickname of the user if known
- L287 _public prototype_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override;` — Additional user data associated with a registered user
- L289 _public prototype_ `void SetAccessToken(const FString& AuthToken);` — Sets the user's access token, used to verify their authentication
- L292 _public prototype_ `void SetBadReputation(const bool bIsBadReputation);` — Set if this user has bad reputation or not
- L295 _public prototype_ `TOptional<bool> GetIsBadReputation() const;` — Check if this user has their reputation state set, and if so, what the value is
- L297 _public function_ `FGDKUserHandle GetUserHandle()`
- L302 _public function_ `FUserOnlineAccountGDK(FGDKUserHandle InUser, TSharedPtr<FOnlineIdentityGDK> InIdentityInterface) : UserData(InUser) , IdentityInterfaceWeakPtr(InIdentityInterface)` — Init/default constructor
- L318 _public prototype_ `virtual ~FUserOnlineAccountGDK() = default;` — Destructor
- L321 _private member_ `FGDKUserHandle UserData;`
- L322 _private member_ `TMap<FString, FString> UserAttributes;`
- L323 _private member_ `FUniqueNetIdGDKPtr UserId;`
- L324 _private member_ `FString UserXSTSToken;`
- L325 _private member_ `const TWeakPtr<FOnlineIdentityGDK> IdentityInterfaceWeakPtr;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "OnlineSubsystemGDK"`
- L13 _macro_ `#define ONLINE_ERROR_NAMESPACE "errors.com.epicgames.oss.identity"`
- L15 _namespace_ `namespace OnlineIdentityGDK`
- L19 _namespace_ `namespace Errors` (scope `OnlineIdentityGDK`)
- L21 _function_ `inline FOnlineError HResultError(int32 InCode)` (scope `OnlineIdentityGDK::Errors`)
- L33 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPIEUsersRefreshed);`
- L33 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPIEUsersRefreshed);`
- L34 _typedef_ `typedef FOnPIEUsersRefreshed::FDelegate FOnPIEUsersRefreshedDelegate;`
- L328 _typedef_ `typedef TSharedPtr<class FOnlineIdentityGDK, ESPMode::ThreadSafe> FOnlineIdentityGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Public/OnlineSubsystemGDK.h` (Public)


#### class `UserContextWrapper`  
`class UserContextWrapper : public TSharedFromThis<UserContextWrapper, ESPMode::ThreadSafe>`  
_L64-75_
- inherits: `TSharedFromThis<UserContextWrapper,ESPMode::ThreadSafe>`
- desc: Wrapper class representing a GDK user context. Required as XblStatisticChangedHandler doesn't admit variable capture, and we can only pass a single pointer in to the delegate, when we need both OSS and User Id.
- L67 _public function_ `UserContextWrapper(TWeakPtr<FOnlineSubsystemGDK, ESPMode::ThreadSafe> InSys, uint64 InUserId)`
- L73 _public member_ `TWeakPtr<FOnlineSubsystemGDK, ESPMode::ThreadSafe> Sys;`
- L74 _public member_ `uint64 UserId = 0;`

#### class `FOnlineSubsystemGDK`  
`class FOnlineSubsystemGDK : public FOnlineSubsystemImpl , public TSharedFromThis<FOnlineSubsystemGDK, ESPMode::ThreadSafe>`  
_L82-389_
- inherits: `FOnlineSubsystemImpl,TSharedFromThis<FOnlineSubsystemGDK,ESPMode::ThreadSafe>`
- desc: OnlineSubsystemGDK - Implementation of the online subsystem for GDK services
- L89 _public prototype_ `virtual IOnlineSessionPtr GetSessionInterface() const override;` — IOnlineSubsystem
- L90 _public prototype_ `virtual IOnlineFriendsPtr GetFriendsInterface() const override;`
- L91 _public prototype_ `virtual IMessageSanitizerPtr GetMessageSanitizer(int32 LocalUserNum, FString& OutAuthTypeToExclude) const override;`
- L92 _public prototype_ `virtual IOnlinePartyPtr GetPartyInterface() const override;`
- L93 _public prototype_ `virtual IOnlineGroupsPtr GetGroupsInterface() const override;`
- L94 _public prototype_ `virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override;`
- L95 _public prototype_ `virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;`
- L96 _public prototype_ `virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;`
- L97 _public prototype_ `virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;`
- L98 _public prototype_ `virtual IOnlineVoicePtr GetVoiceInterface() const override;`
- L99 _public prototype_ `virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;`
- L100 _public prototype_ `virtual IOnlineTimePtr GetTimeInterface() const override;`
- L101 _public prototype_ `virtual IOnlineIdentityPtr GetIdentityInterface() const override;`
- L102 _public prototype_ `virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;`
- L103 _public prototype_ `virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override;`
- L104 _public prototype_ `virtual IOnlinePurchasePtr GetPurchaseInterface() const override;`
- L105 _public prototype_ `virtual IOnlineEventsPtr GetEventsInterface() const override;`
- L106 _public prototype_ `virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;`
- L107 _public prototype_ `virtual IOnlineSharingPtr GetSharingInterface() const override;`
- L108 _public prototype_ `virtual IOnlineUserPtr GetUserInterface() const override;`
- L109 _public prototype_ `virtual IOnlineMessagePtr GetMessageInterface() const override;`
- L110 _public prototype_ `virtual IOnlinePresencePtr GetPresenceInterface() const override;`
- L111 _public prototype_ `virtual IOnlineChatPtr GetChatInterface() const override;`
- L112 _public prototype_ `virtual IOnlineStatsPtr GetStatsInterface() const override;`
- L113 _public prototype_ `virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override;`
- L114 _public prototype_ `virtual FOnlineMatchmakingInterfaceGDKPtr GetMatchmakingInterface() const;`
- L115 _public prototype_ `virtual IOnlineTournamentPtr GetTournamentInterface() const override;`
- L117 _public prototype_ `virtual EOnlineEnvironment::Type GetOnlineEnvironment() const override;`
- L120 _public function_ `FOnlineSessionGDKPtr GetSessionInterfaceGDK() const` — Helpers to get typed Interface shared pointers
- L121 _public function_ `FOnlineIdentityGDKPtr GetIdentityGDK() const`
- L122 _public function_ `FOnlineStoreGDKPtr GetStoreGDK() const`
- L123 _public function_ `FOnlinePurchaseGDKPtr GetPurchaseGDK() const`
- L124 _public function_ `FOnlinePresenceGDKPtr GetPresenceGDK() const`
- L125 _public function_ `FOnlineLeaderboardsGDKPtr GetLeaderboardsInterfaceGDK() const`
- L126 _public function_ `FOnlineMatchmakingInterfaceGDKPtr GetMatchmakingInterfaceGDK() const`
- L127 _public function_ `FSessionMessageRouterPtr GetSessionMessageRouter() const`
- L128 _public function_ `FOnlineFriendsGDKPtr GetFriendsGDK() const`
- L129 _public function_ `FOnlineUserGDKPtr GetUsersGDK() const`
- L130 _public function_ `FOnlineStatsGDKPtr GetStatsGDK() const`
- L131 _public function_ `FOnlineAchievementsGDKPtr GetAchievementsInterfaceGDK() const`
- L133 _public prototype_ `virtual bool Init() override;`
- L134 _public prototype_ `virtual bool Shutdown() override;`
- L135 _public prototype_ `virtual bool IsEnabled() const override;`
- L136 _public prototype_ `virtual FString GetAppId() const override;`
- L137 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L138 _public prototype_ `virtual FText GetOnlineServiceName() const override;`
- L139 _public prototype_ `virtual FText GetSocialPlatformName() const override;`
- L142 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L147 _public prototype_ `static bool IsXBLGoldRequired();` — @return true if XBox Live Gold is required for online play
- L153 _public function_ `explicit FOnlineSubsystemGDK(FName InInstanceName) : FOnlineSubsystemImpl(GDK_SUBSYSTEM, InInstanceName) , ConvertedNetworkConnectivityLevel(EOnlineServerConnectionStatus::Normal) , bHasCalledNetworkStatusChangedAtLeastOnce(false) , TitleId(0)`
- L161 _public function_ `virtual ~FOnlineSubsystemGDK()`
- L167 _public prototype_ `const FString& GetTitleProductId() const;` — Get title's product id if one is configured
- L169 _public prototype_ `FOnlineAsyncTaskManagerGDK* GetAsyncTaskManager();`
- L172 _public prototype_ `void QueueAsyncTask(FOnlineAsyncTask* const AsyncTask, const bool bCanRunInParallel = false);` — Helpers to manage queuing already created FOnlineAsyncItem
- L173 _public prototype_ `void QueueAsyncEvent(FOnlineAsyncEvent<FOnlineSubsystemGDK>* const AsyncEvent);`
- L177 _public function_ `template <typename TOnlineAsyncTask, typename... TArguments> inline void CreateAndDispatchAsyncTaskParallel(TArguments&&... Arguments)` — Create a new async task with the provided arguments and queue it to be processed in parallel with other tasks
- L190 _public function_ `template <typename TOnlineAsyncTask, typename... TArguments> inline void CreateAndDispatchAsyncTaskSerial(TArguments&&... Arguments)` — Create a new async task with the provided arguments and add it to the serial processing queue
- L203 _public function_ `template <typename TOnlineAsyncEvent, typename... TArguments> inline void CreateAndDispatchAsyncEvent(TArguments&&... Arguments)` — Create a new async event with the provided arguments and queue it to be processed in the OutQueue
- L214 _public prototype_ `FGDKContextHandle CreateGDKContext(FGDKUserHandle GDKUser);`
- L215 _public prototype_ `void DeleteGDKContext(FGDKUserHandle GDKUser);`
- L218 _public prototype_ `FGDKContextHandle GetGDKContext(int32 LocalUserNum);` — Returns the GDK context for the given user, or null if the input could not be found/was invalid.
- L219 _public prototype_ `FGDKContextHandle GetGDKContext(const FUniqueNetId& UserId);`
- L220 _public prototype_ `FGDKContextHandle GetGDKContext(FGDKMultiplayerSessionHandle Session);`
- L221 _public prototype_ `FGDKContextHandle GetGDKContext(uint64 GDKUserId);`
- L224 _public prototype_ `FGDKContextHandle GetGDKContext(FGDKUserHandle GDKUser);` — Returns the cached GDK context for the given user. Creates and caches a new one if necessary. Session subscriptions require that you preserve the context.
- L226 _public prototype_ `FGDKContextHandle GetFirstValidContext();`
- L232 _public prototype_ `void CacheGDKSession(const FName& SessionName, FGDKMultiplayerSessionHandle LatestSession);` — Updates our local caches with updated session info
- L235 _public prototype_ `void SetLastDiffedSession(const FName& SessionName, FGDKMultiplayerSessionHandle LatestSession);` — Updates our local caches to specify this session was the latest seen
- L238 _public prototype_ `FGDKMultiplayerSessionHandle GetLastDiffedSession(const FName& SessionName);` — Return the last seen session by a provided Name
- L241 _public prototype_ `static bool AreSessionReferencesEqual(const XblMultiplayerSessionReference* First, const XblMultiplayerSessionReference* Second);` — Helper to compare two sessions to see if they're the same underlying session
- L243 _public prototype_ `void RefreshNetworkConnectivityLevel();`
- L244 _public prototype_ `void OnNetworkConnectivityHintChanged(const XNetworkingConnectivityHint& ConnectivityHint);`
- L245 _public prototype_ `void ApplyNetworkConnectivityLevel(const XNetworkingConnectivityHint& ConnectivityHint);`
- L246 _public prototype_ `void OnUserLoginChange(bool bIsSignIn, int32 PlatformUserId, int32 UserIndex );`
- L247 _public prototype_ `void HandleAppResume();`
- L248 _public prototype_ `void HandleNetworkRequestDTLSCertificate(FGuid ConnectionId, FOnDTLSCertificateReceived Delegate);`
- L249 _public prototype_ `void HandleNetworkGeneratedDTLSCertificate(FGuid ConnectionId, const TArray<uint8> Thumbprint, bool WriteToService);`
- L250 _public prototype_ `void HandleNetworkRecievedDTLSCertificate(FGuid ConnectionId, const TArray<uint8> Thumbprint);`
- L251 _public prototype_ `TMap<FGuid, TArray<uint8>> GetCertificateDictionary() const;`
- L253 _public prototype_ `void RecreateGDKContextOnSubscriptionLost();`
- L255 _public prototype_ `void EnableSessionEventHandlers(FGDKContextHandle& GDKContext);`
- L260 _public member_ `bool bHasCalledNetworkStatusChangedAtLeastOnce;`
- L263 _public member_ `uint32 TitleId;` — Title Id for our current application
- L269 _private prototype_ `bool HandleSanitizeStringExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);` — Exec function handling for Exec() call above
- L270 _private prototype_ `bool HandleSanitizeStringsExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L272 _private prototype_ `void InitializeXblByConfig();`
- L274 _private prototype_ `void CleanupGDKContextForNetworkConnectivityLoss();`
- L275 _private prototype_ `void ReinitializeGDKContextForNetworkConnectivityRestored();`
- L278 _private member_ `FOnlineSessionGDKPtr SessionInterface;` — Interface to the session services
- L281 _private member_ `FOnlineExternalUIGDKPtr ExternalUIInterface;` — Interface to the external UI services
- L284 _private member_ `FOnlineIdentityGDKPtr IdentityInterface;` — Interface to the identity registration/auth services
- L287 _private member_ `FOnlineStoreGDKPtr StoreInterface;` — Interface to the store services
- L290 _private member_ `FOnlinePurchaseGDKPtr PurchaseInterface;` — Interface to the purchase services
- L293 _private member_ `FOnlineVoiceGDKPtr VoiceInterface;` — Interface to the voice chat services
- L296 _private member_ `FOnlineEventsGDKPtr EventsInterface;` — Interface to the events services
- L299 _private member_ `FOnlineAchievementsGDKPtr AchievementInterface;` — Interface to the achievement services
- L302 _private member_ `FOnlineStatsGDKPtr StatsInterface;` — Interface to the stats services
- L305 _private member_ `FOnlinePresenceGDKPtr PresenceInterface;` — Interface to the rich presence services
- L308 _private member_ `FOnlineLeaderboardsGDKPtr LeaderboardsInterface;` — Interface to the leaderboard services
- L311 _private member_ `FOnlineMatchmakingInterfaceGDKPtr MatchmakingInterfaceGDK;` — Interface to the matchmaking services
- L314 _private member_ `FSessionMessageRouterPtr SessionMessageRouterInterface;` — Interface to the mpsd shouldertap services
- L317 _private member_ `FOnlineFriendsGDKPtr FriendInterface;` — Interface to the Friends services
- L320 _private member_ `FMessageSanitizerGDKPtr MessageSanitizer;` — Interface to the message sanitizer
- L323 _private member_ `FOnlineUserGDKPtr UserInterface;` — Interface to the Users services
- L326 _private member_ `TUniquePtr<FOnlineAsyncTaskManagerGDK> OnlineAsyncTaskThreadRunnable;` — Online async task runnable
- L329 _private member_ `TUniquePtr<FRunnableThread> OnlineAsyncTaskThread;` — Online async task thread
- L331 _private member_ `static const XblFunctionContext INVALID_XBL_FUNCTION_CONTEXT = 0;`
- L346 _private member_ `TMap<uint64, FGDKContextInfo> CachedGDKContexts;`
- L348 _private prototype_ `void DeleteGDKContextInternal(uint64 Xuid, FGDKContextInfo& GDKContext) const;`
- L350 _private prototype_ `void EnableSessionEventHandlers(FGDKContextInfo& ContextInfo);`
- L351 _private prototype_ `void DisableSessionEventHandlers(FGDKContextInfo& ContextInfo) const;`
- L353 _private member_ `TArray<UserContextWrapperPtr> UserContextWrappers;`
- L355 _private member_ `mutable FCriticalSection GDKContextsLock;`
- L358 _private member_ `TUniquePtr<FGDKAsyncTaskQueue> XblTaskQueue;` — task queue used for background Xal and Xbl operations
- L362 _private member_ `ANSICHAR SandboxId[XSystemXboxLiveSandboxIdMaxBytes];`
- L364 _private member_ `HANDLE NetworkConnectivityChangedHandle;`
- L366 _private member_ `XalRegistrationToken OnUserStateChanged;`
- L367 _private member_ `XblFunctionContext ServiceCallRoutedHandlerContext = INVALID_XBL_FUNCTION_CONTEXT;`
- L369 _private member_ `mutable FCriticalSection DTLSDictionariesLock;`
- L370 _private member_ `TMap<FGuid, TArray<uint8>> DTLSCertificateDictionary;`
- L371 _private member_ `TMap<FGuid, FOnDTLSCertificateReceived> PendingDTLSCertificateRequests;`
- L373 _private member_ `FOnNetworkRequestDTLSCertificate OnNetworkRequestDTLSCertificate;`
- L374 _private member_ `FOnNetworkGeneratedDTLSCertificate OnNetworkGeneratedDTLSCertificate;`
- L377 _private member_ `FDelegateHandle AppInitComplete;` — Stored delegate handle to remove the task later
- L378 _private member_ `FDelegateHandle UserLoginChanged;`
- L380 _private member_ `FDelegateHandle OnOnlineSubsystemCreated;`
- L383 _private member_ `TOptional<XTaskQueueRegistrationToken> NetworkConnectivityHandle;`
- L384 _private member_ `bool bShouldRestoreConnectivity = false;`
- L387 _private member_ `bool bIsInitialized = false;`

#### struct `FOnlineSubsystemGDK::FGDKContextInfo`  
`struct FGDKContextInfo`  
_L334-345_
- desc: Store single XboxGDKContext per user
- L336 _public function_ `FGDKContextInfo( FGDKContextHandle& InHandle ) : Handle(InHandle)`
- L337 _public member_ `FGDKContextHandle Handle;`
- L338 _public member_ `XblFunctionContext SessionChangedContext = INVALID_XBL_FUNCTION_CONTEXT;`
- L339 _public member_ `XblFunctionContext RelationshipChangedContext = INVALID_XBL_FUNCTION_CONTEXT;`
- L340 _public member_ `XblFunctionContext DevicePresenceChangedContext = INVALID_XBL_FUNCTION_CONTEXT;`
- L341 _public member_ `XblFunctionContext TitlePresenceChangedContext = INVALID_XBL_FUNCTION_CONTEXT;`
- L342 _public member_ `XblFunctionContext StatisticChangedContext = INVALID_XBL_FUNCTION_CONTEXT;`
- L343 _public member_ `XblFunctionContext ConnectionIdChangedContext = INVALID_XBL_FUNCTION_CONTEXT;`
- L344 _public member_ `XblFunctionContext SubscriptionLostContext = INVALID_XBL_FUNCTION_CONTEXT;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API ONLINESUBSYSTEMGDK_API`
- L20 _typedef_ `typedef TSharedPtr<class FOnlineSessionGDK, ESPMode::ThreadSafe> FOnlineSessionGDKPtr;` — Forward declarations of all interface classes
- L21 _typedef_ `typedef TSharedPtr<class FOnlineProfileGDK, ESPMode::ThreadSafe> FOnlineProfileGDKPtr;`
- L22 _typedef_ `typedef TSharedPtr<class FOnlineFriendsGDK, ESPMode::ThreadSafe> FOnlineFriendsGDKPtr;`
- L23 _typedef_ `typedef TSharedPtr<class FMessageSanitizerGDK, ESPMode::ThreadSafe> FMessageSanitizerGDKPtr;`
- L24 _typedef_ `typedef TSharedPtr<class FOnlineUserCloudGDK, ESPMode::ThreadSafe> FOnlineUserCloudGDKPtr;`
- L25 _typedef_ `typedef TSharedPtr<class FOnlineLeaderboardsGDK, ESPMode::ThreadSafe> FOnlineLeaderboardsGDKPtr;`
- L26 _typedef_ `typedef TSharedPtr<class FOnlineVoiceGDK, ESPMode::ThreadSafe> FOnlineVoiceGDKPtr;`
- L27 _typedef_ `typedef TSharedPtr<class FOnlineExternalUIGDK, ESPMode::ThreadSafe> FOnlineExternalUIGDKPtr;`
- L28 _typedef_ `typedef TSharedPtr<class FOnlineIdentityGDK, ESPMode::ThreadSafe> FOnlineIdentityGDKPtr;`
- L29 _typedef_ `typedef TSharedPtr<class FOnlinePurchaseGDK, ESPMode::ThreadSafe> FOnlinePurchaseGDKPtr;`
- L30 _typedef_ `typedef TSharedPtr<class FOnlineStoreGDK, ESPMode::ThreadSafe> FOnlineStoreGDKPtr;`
- L31 _typedef_ `typedef TSharedPtr<class FOnlineAchievementsGDK, ESPMode::ThreadSafe> FOnlineAchievementsGDKPtr;`
- L32 _typedef_ `typedef TSharedPtr<class FOnlineStatsGDK, ESPMode::ThreadSafe> FOnlineStatsGDKPtr;`
- L33 _typedef_ `typedef TSharedPtr<class FOnlineEventsGDK, ESPMode::ThreadSafe> FOnlineEventsGDKPtr;`
- L34 _typedef_ `typedef TSharedPtr<class FOnlinePresenceGDK, ESPMode::ThreadSafe> FOnlinePresenceGDKPtr;`
- L35 _typedef_ `typedef TSharedPtr<class FOnlineUserGDK, ESPMode::ThreadSafe> FOnlineUserGDKPtr;`
- L36 _typedef_ `typedef TSharedPtr<class FOnlineMatchmakingInterfaceGDK, ESPMode::ThreadSafe> FOnlineMatchmakingInterfaceGDKPtr;`
- L37 _typedef_ `typedef TSharedPtr<class FSessionMessageRouter, ESPMode::ThreadSafe> FSessionMessageRouterPtr;`
- L46 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnDTLSCertificateReceived, FGuid , const TArray<uint8> );` — Delegate fired when we have recieved a DTLS Certificate
- L46 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnDTLSCertificateReceived, FGuid , const TArray<uint8> );` — Delegate fired when we have recieved a DTLS Certificate
- L51 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnNetworkRequestDTLSCertificate, FGuid , const FOnDTLSCertificateReceived );` — Delegate fired when network has requested DTLS Cert
- L51 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnNetworkRequestDTLSCertificate, FGuid , const FOnDTLSCertificateReceived );` — Delegate fired when network has requested DTLS Cert
- L56 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnNetworkGeneratedDTLSCertificate, FGuid , const TArray<uint8> );` — Delegate fired when we have recieved a DTLS Certificate
- L56 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnNetworkGeneratedDTLSCertificate, FGuid , const TArray<uint8> );` — Delegate fired when we have recieved a DTLS Certificate
- L77 _typedef_ `typedef TSharedPtr<UserContextWrapper, ESPMode::ThreadSafe> UserContextWrapperPtr;`
- L391 _typedef_ `typedef TSharedPtr<FOnlineSubsystemGDK, ESPMode::ThreadSafe> FOnlineSubsystemGDKPtr;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Public/OnlineSubsystemGDKPackage.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define PACKAGE_SCOPE public`
- L12 _macro_ `#define PACKAGE_SCOPE protected`
- L16 _macro_ `#define ONLINESUBSYSTEMGDK_API`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Public/OnlineSubsystemGDKTypes.h` (Public)


#### class `FUniqueNetIdGDK`  
`class FUniqueNetIdGDK : public FUniqueNetId`  
_L59-254_
- inherits: `FUniqueNetId`
- desc: GDK Unique Id implementation - wrapping XUID
- L63 _protected member_ `uint64 UniqueNetId;` — Holds the net id for a player
- L66 _protected function_ `FUniqueNetIdGDK() : UniqueNetId(0)` — Hidden on purpose
- L76 _protected function_ `explicit FUniqueNetIdGDK(const FUniqueNetIdGDK& Src) : UniqueNetId(Src.UniqueNetId)` — Copy Constructor @param Src the id to copy
- L86 _protected function_ `explicit FUniqueNetIdGDK(uint64 InUniqueNetId) : UniqueNetId(InUniqueNetId)` — Constructs this object with the specified net id @param InUniqueNetId the id to set ours to
- L96 _protected function_ `explicit FUniqueNetIdGDK(const FString& Str) : UniqueNetId(FCString::Atoi64(*Str))` — Constructs this object with the specified net id @param String textual representation of an id
- L107 _protected function_ `explicit FUniqueNetIdGDK(const FUniqueNetId& InUniqueNetId)` — Constructs this object with the specified net id @param InUniqueNetId the id to set ours to
- L117 _protected function_ `explicit FUniqueNetIdGDK( const FGDKUserHandle& InUserHandle )` — Constructs this object for the given user handle @param User handle
- L132 _protected function_ `explicit FUniqueNetIdGDK( const FGDKContextHandle& InContextHandle )` — Constructs this object for the given context handle @param Context handle
- L145 _public function_ `template<typename... TArgs> static FUniqueNetIdGDKRef Create(TArgs&&... Args)`
- L150 _public function_ `static FUniqueNetIdGDKRef Cast(const FUniqueNetId& InUniqueNetId)`
- L159 _public function_ `virtual FName GetType() const override`
- L170 _public function_ `virtual const uint8* GetBytes() const override` — Get the raw byte representation of this net id This data is platform dependent and shouldn't be manipulated directly @return byte array of size GetSize()
- L180 _public function_ `virtual int32 GetSize() const override` — Get the size of the id @return size in bytes of the id representation
- L186 _public function_ `virtual bool IsValid() const override` — Is our structure currently pointing to a valid XUID?
- L196 _public function_ `virtual FString ToString() const override` — Platform specific conversion to string representation of data @return data in string form
- L206 _public function_ `virtual uint64 ToUint64() const` — Platform specific conversion to string representation of data @return data in uint64 form
- L218 _public function_ `virtual FString ToDebugString() const override` — Get a human readable representation of the net id Shouldn't be used for anything other than logging/debugging @return id in string form
- L231 _public function_ `virtual uint32 GetTypeHash() const override`
- L237 _public function_ `static const FUniqueNetIdGDKRef& EmptyId()` — global static instance of invalid id
- L243 _public function_ `bool operator==(uint64 RawGDKId) const`
- L248 _public prototype_ `virtual ~FUniqueNetIdGDK() = default;`

#### enum `EOnlineGDKMatchmakingState::Type`  
`enum Type`  
_L259-268_
- L261 _public enumerator_ `None`
- L262 _public enumerator_ `CreatingMatchSession`
- L263 _public enumerator_ `SubmittingInitialTicket`
- L264 _public enumerator_ `WaitingForGameSession`
- L265 _public enumerator_ `JoiningGameSession`
- L266 _public enumerator_ `Active`
- L267 _public enumerator_ `UserCancelled`

#### class `FOnlineMatchTicketInfo`  
`class FOnlineMatchTicketInfo`  
_L274-375_
- desc: GDK Match ticket wrapper
- L277 _public function_ `FOnlineMatchTicketInfo() : EstimatedWaitTimeInSeconds(0.0f) , SessionReference(nullptr)`
- L283 _public function_ `FOnlineMatchTicketInfo( const FString& InHopperName, const FString& InTicketID, float InWaitTimeInSeconds ) : HopperName( InHopperName ) , TicketId( InTicketID ) , EstimatedWaitTimeInSeconds( InWaitTimeInSeconds ) , SessionReference(nullptr) , MatchmakingState(EOnlineGDKMatchmakingState::None)`
- L296 _public member_ `FString HopperName;`
- L297 _public member_ `FString TicketId;`
- L298 _public member_ `float EstimatedWaitTimeInSeconds;`
- L301 _private member_ `const XblMultiplayerSessionReference* SessionReference;`
- L302 _private member_ `FGDKMultiplayerSessionHandle GDKSession;`
- L303 _private member_ `FGDKMultiplayerSessionHandle LastDiffedGDKSession;`
- L306 _private member_ `FGDKUserHandle HostUser;` — Easy access to the hosting User of this session (will be null on clients)
- L309 _public member_ `FName SessionName;`
- L310 _public member_ `FOnlineSessionSettings SessionSettings;`
- L313 _public member_ `EOnlineGDKMatchmakingState::Type MatchmakingState;` — The state of the matchmaking process, will be None for non-matchmaking (custom) sessions
- L316 _public member_ `TSharedPtr<FOnlineSessionSearch> SessionSearch;` — Search settings are used during match ticket resubmission
- L319 _public function_ `FGDKUserHandle GetHostUser() const`
- L324 _public function_ `void SetHostUser(FGDKUserHandle InHostUser)`
- L330 _public function_ `const FGDKMultiplayerSessionHandle GetGDKSession() const` — Returns the Xbox-specific match session pointer.
- L336 _public function_ `const XblMultiplayerSessionReference* GetGDKSessionRef() const` — Returns the Xbox-specific match session reference pointer.
- L341 _public function_ `const FGDKMultiplayerSessionHandle GetLastDiffedSession() const`
- L347 _public function_ `void SetLastDiffedSession(FGDKMultiplayerSessionHandle LatestSession)` — Stores the last game session seen in OnSessionChanged.
- L352 _public function_ `void RefreshGDKInfo(FGDKMultiplayerSessionHandle LatestSession)`
- L366 _public function_ `void RefreshGDKInfo(const XblMultiplayerSessionReference* LatestSessionRef)`

#### class `FOnlineSessionInfoMpsdGDK`  
`class FOnlineSessionInfoMpsdGDK : public FOnlineSessionInfo`  
_L382-647_
- inherits: `FOnlineSessionInfo`
- desc: GDK Session information wrapper, as well as convenient place to store Host Addr as well as map of xuid-FOnlineAssociateGDK
- L389 _public function_ `FOnlineSessionInfoMpsdGDK() : IsReady(false) , GDKSession(nullptr) , GDKSessionRef(nullptr) , LastDiffedGameSession(nullptr) , SessionId(FUniqueNetIdString::Create(TEXT(""), GDK_SUBSYSTEM))` — Constructor
- L403 _public function_ `FOnlineSessionInfoMpsdGDK(FGDKMultiplayerSearchHandle InGDKSearchResult) : IsReady(false) , GDKSession(nullptr) , GDKSearchResult(InGDKSearchResult) , LastDiffedGameSession(nullptr) , SessionId(FUniqueNetIdString::Create(TEXT(""), GDK_SUBSYSTEM))` — Constructor @param InSearchResult The GDK search result corresponding to this object
- L432 _public function_ `FOnlineSessionInfoMpsdGDK(FGDKMultiplayerSessionHandle InGDKSession) : IsReady(false) , GDKSession(InGDKSession) , LastDiffedGameSession(InGDKSession) , SessionId(FUniqueNetIdString::Create(TEXT(""), GDK_SUBSYSTEM))` — Constructor @param InGDKSession The session corresponding to this object
- L455 _public prototype_ `virtual ~FOnlineSessionInfoMpsdGDK() = default;` — Destructor
- L457 _public function_ `virtual const uint8* GetBytes() const override`
- L463 _public function_ `virtual int32 GetSize() const override`
- L468 _public function_ `virtual bool IsValid() const override`
- L473 _public function_ `virtual FString ToString() const override`
- L479 _public function_ `virtual FString ToDebugString() const override`
- L485 _public function_ `virtual const FUniqueNetId& GetSessionId() const override`
- L495 _public function_ `const FGDKMultiplayerSessionHandle GetGDKMultiplayerSession() const` — Returns the GDK-specific session pointer.
- L501 _public function_ `const FGDKMultiplayerSearchHandle GetGDKMultiplayerSearchHandle() const` — Returns the GDK-specific search handle.
- L507 _public function_ `const XblMultiplayerSessionReference* GetGDKMultiplayerSessionRef() const` — Returns the GDK-specific session reference pointer.
- L518 _public function_ `void RefreshGDKInfo(FGDKMultiplayerSessionHandle LatestSession)` — Updates the cached session and session reference pointers with a new session. Useful after WriteSessionAsync operations because the old sessions are no longer valid. @param LatestSession The new session to replace the cached version with.
- L554 _public function_ `const FGDKMultiplayerSessionHandle GetLastDiffedMultiplayerSession() const` — Returns the last game session seen in OnSessionChanged.
- L560 _public function_ `void SetLastDiffedMultiplayerSession(FGDKMultiplayerSessionHandle LatestSession)` — Stores the last game session seen in OnSessionChanged.
- L566 _public function_ `TSharedPtr<class FInternetAddr> GetHostAddr() const` — Returns the address of the host of this session.
- L572 _public function_ `void SetHostAddr(TSharedPtr<class FInternetAddr> InAddr)` — Sets the address of the host of this session.
- L577 _public function_ `FGuid GetRoundId() const`
- L582 _public function_ `void SetRoundId(const FGuid& InRoundId)`
- L587 _public function_ `bool IsSessionReady() const`
- L592 _public function_ `void SetSessionReady()`
- L597 _public function_ `void SetSessionInviteHandle(const XblMultiplayerInviteHandle& InSessionHandle)`
- L602 _public function_ `const TOptional<XblMultiplayerInviteHandle>& GetSessionInviteHandle() const`
- L607 _public function_ `const TOptional<FString> GetSessionInviteHandleString() const`
- L619 _private member_ `bool IsReady;`
- L622 _private member_ `FGDKMultiplayerSessionHandle GDKSession;` — Wrapped GDK session
- L625 _private member_ `FGDKMultiplayerSearchHandle GDKSearchResult;` — Wrapped GDK Search result
- L629 _private member_ `const XblMultiplayerSessionReference* GDKSessionRef;` — pointer to GDK session reference. Should be associated with SessionHandle above or, the internal struct below that is associated with a SearchHandle Pointer target memory is NOT managed by this class
- L631 _private member_ `XblMultiplayerSessionReference GDKSessionRefInternal;`
- L634 _private member_ `FGDKMultiplayerSessionHandle LastDiffedGameSession;` — Last version of GDK game session compared in OnSessionChanged
- L637 _private member_ `TSharedPtr<class FInternetAddr> HostAddr;` — Host address
- L640 _private member_ `FUniqueNetIdStringRef SessionId;` — Placeholder unique id
- L643 _private member_ `FGuid RoundId;` — Stored RoundId, used when triggering Xbox events
- L646 _private member_ `TOptional<XblMultiplayerInviteHandle> SessionInviteHandle;` — Session handle if this session is from an to-be-joined invite

#### class `FOnlineUserInfoGDK`  
`class FOnlineUserInfoGDK : public FOnlineUser`  
_L653-759_
- inherits: `FOnlineUser`
- L657 _public function_ `virtual FUniqueNetIdRef GetUserId() const override`
- L662 _public function_ `virtual FString GetRealName() const override`
- L667 _public function_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override`
- L672 _public function_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override`
- L699 _public prototype_ `virtual ~FOnlineUserInfoGDK() = default;`
- L701 _public function_ `static FString FilterPlayerName(const FString& InPlayerName)`
- L728 _public function_ `static FString GetGamertag(const XblUserProfile& InUserProfile)`
- L757 _public member_ `FUniqueNetIdGDKRef UserId;`
- L758 _public member_ `TMap<FString, FString> UserAttributes;`

#### Free symbols / members of external scopes

- L35 _prototype_ `SETHANDLETYPETRAITS(XblContextHandle, XblContextDuplicateHandle, XblContextCloseHandle);`
- L36 _prototype_ `SETHANDLETYPETRAITS(XblPresenceRecordHandle, XblPresenceRecordDuplicateHandle, XblPresenceRecordCloseHandle);`
- L37 _prototype_ `SETHANDLETYPETRAITS(XblMultiplayerSessionHandle, XblMultiplayerSessionDuplicateHandle, XblMultiplayerSessionCloseHandle);`
- L38 _prototype_ `SETHANDLETYPETRAITS(XblMultiplayerSearchHandle, XblMultiplayerSearchHandleDuplicateHandle, XblMultiplayerSearchHandleCloseHandle);`
- L40 _typedef_ `typedef TGDKHandle<XblContextHandle> FGDKContextHandle;`
- L41 _typedef_ `typedef TGDKHandle<XblPresenceRecordHandle> FGDKPresenceRecordHandle;`
- L42 _typedef_ `typedef TGDKHandle<XblMultiplayerSessionHandle> FGDKMultiplayerSessionHandle;`
- L43 _typedef_ `typedef TGDKHandle<XblMultiplayerSearchHandle> FGDKMultiplayerSearchHandle;`
- L45 _macro_ `#define COMMUNICATE_USING_TEXT XblPermission::CommunicateUsingText`
- L46 _macro_ `#define COMMUNICATE_USING_VOICE XblPermission::CommunicateUsingVoice`
- L53 _typedef_ `using FUniqueNetIdGDKRef = TSharedRef<const class FUniqueNetIdGDK>;`
- L54 _typedef_ `using FUniqueNetIdGDKPtr = TSharedPtr<const class FUniqueNetIdGDK>;`
- L250 _function_ `friend FArchive& operator<<(FArchive& Ar, FUniqueNetIdGDK& UserId)`
- L257 _namespace_ `namespace EOnlineGDKMatchmakingState`
- L377 _typedef_ `typedef TSharedPtr<FOnlineMatchTicketInfo> FOnlineMatchTicketInfoPtr;`
- L649 _typedef_ `typedef TSharedPtr<FOnlineSessionInfoMpsdGDK> FOnlineSessionInfoMpsdGDKPtr;`
- L651 _variable_ `static const int32 GDK_MAX_PLAYER_NAME_LENGTH = 16;`

### `Plugins/Online/Microsoft/OnlineSubsystemGDK/Source/Public/OnlineUserInterfaceGDK.h` (Public)


#### class `FOnlineUserGDK`  
`class FOnlineUserGDK : public IOnlineUser , public TSharedFromThis<FOnlineUserGDK, ESPMode::ThreadSafe>`  
_L71-130_
- inherits: `IOnlineUser,TSharedFromThis<FOnlineUserGDK,ESPMode::ThreadSafe>`
- desc: Implements the GDK specific interface for friends
- L80 _public prototype_ `virtual bool QueryUserInfo(int32 LocalUserNum, const TArray<FUniqueNetIdRef>& UserIds) override;` — IOnlineUser
- L81 _public prototype_ `virtual bool GetAllUserInfo(int32 LocalUserNum, TArray<TSharedRef<class FOnlineUser>>& OutUsers) override;`
- L82 _public prototype_ `virtual TSharedPtr<FOnlineUser> GetUserInfo(int32 LocalUserNum, const class FUniqueNetId& UserId) override;`
- L83 _public prototype_ `virtual bool QueryUserIdMapping(const FUniqueNetId& UserId, const FString& DisplayNameOrEmail, const FOnQueryUserMappingComplete& Delegate = FOnQueryUserMappingComplete()) override;`
- L84 _public prototype_ `virtual bool QueryExternalIdMappings(const FUniqueNetId& UserId, const FExternalIdQueryOptions& QueryOptions, const TArray<FString>& ExternalIds, const FOnQueryExternalIdMappingsComplete& Delegate = FOnQueryExternalIdMappingsComplete()) override;`
- L85 _public prototype_ `virtual void GetExternalIdMappings(const FExternalIdQueryOptions& QueryOptions, const TArray<FString>& ExternalIds, TArray<FUniqueNetIdPtr>& OutIds) override;`
- L86 _public prototype_ `virtual FUniqueNetIdPtr GetExternalIdMapping(const FExternalIdQueryOptions& QueryOptions, const FString& ExternalId) override;`
- L89 _public function_ `explicit FOnlineUserGDK(FOnlineSubsystemGDK* const InGDKSubsystem) : GDKSubsystem(InGDKSubsystem)` — FOnlineFriendsGDK
- L95 _public prototype_ `virtual ~FOnlineUserGDK() = default;`
- L106 _public prototype_ `void QueryUserCommunicationPermissions(const FUniqueNetId& UserId, const TArray<FUniqueNetIdRef >& UsersToQuery, const TArray<XblPermission>& PermissionsToQuery, const FOnGDKCommunicationPermissionsQueryComplete& CompletionDelegate);` — Query GDK for permission status between a local user and a list of remote GDK users @param UserId local user to query status @param UsersToQuery array of remote users to query relationship with @param PermissionsToQuery types of permissions to query @param CompletionDelegate delegate to fire when query is complete
- L117 _public prototype_ `void QueryAnonymousUserCommunicationPermissions(const FUniqueNetId& UserId, const TArray<XblAnonymousUserType>& UserTypesToQuery, const TArray<XblPermission>& PermissionsToQuery, const FOnGDKAnonymousUserCommunicationPermissionsQueryComplete& CompletionDelegate);` — Query GDK for permission status between a local user and types of remote crossplay users @param UserId local user to query status @param UserTypesToQuery array of user types to query relationship with @param PermissionsToQuery types of permissions to query @param CompletionDelegate delegate to fire when query is complete
- L120 _private prototype_ `void OnQueryUserCommunicationPermissionsComplete(const FOnlineError& RequestStatus, const FUniqueNetIdRef& RequestingUser, const FPrivacyPermissionsResultsMap& Results, const FOnGDKCommunicationPermissionsQueryComplete CompletionDelegate, const TArray<XblPermission> PermissionsToQuery);`
- L122 _private prototype_ `void OnQueryAnonymousUserCommunicationPermissionsComplete(const FOnlineError& RequestStatus, const FAnonymousUserPrivacyPermissionsResultsMap& Results, const FOnGDKAnonymousUserCommunicationPermissionsQueryComplete CompletionDelegate, const TArray<XblPermission> PermissionsToQuery);`
- L126 _private member_ `FOnlineSubsystemGDK* const GDKSubsystem;` — Reference to the main GDK subsystem
- L129 _private member_ `FOnlineUserListGDKMap UsersMap;` — Map of known user information

#### Free symbols / members of external scopes

- L17 _macro_ `#define LOCTEXT_NAMESPACE "OnlineSubsystemGDK"`
- L18 _macro_ `#define ONLINE_ERROR_NAMESPACE "errors.com.epicgames.oss.user"`
- L20 _namespace_ `namespace OnlineUserGDK`
- L24 _namespace_ `namespace Errors` (scope `OnlineUserGDK`)
- L26 _function_ `inline FOnlineError NoGDKContext()` (scope `OnlineUserGDK::Errors`)
- L37 _typedef_ `using FOnlineUserListGDKMap = TUniqueNetIdMap<TSharedRef<FOnlineUserInfoGDK>>;`
- L40 _typedef_ `using FCommunicationPermissionResultsMap = TUniqueNetIdMap<bool>;` — Map of User's permission to communicate to other users
- L43 _typedef_ `using FPrivacyPermissionsResultsMap = TUniqueNetIdMap<TMap<XblPermission, bool>>;` — Map of User's privacy permissions
- L46 _typedef_ `using FAnonymousUserCommunicationPermissionResultsMap = TMap<XblAnonymousUserType, bool>;` — Map of anonymous user type's permission to communicate to other users
- L49 _typedef_ `using FAnonymousUserPrivacyPermissionsResultsMap = TMap<XblAnonymousUserType, TMap<XblPermission, bool> >;` — Map of anonymous user type's privacy permissions
- L58 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnGDKCommunicationPermissionsQueryComplete, const FOnlineError& , const FUniqueNetIdRef& , const FCommunicationPermissionResultsMap& );` — Delegate used when the user communication permissions query has completed @param RequestStatus If this request was successful or not @param RequestingUser The user who generated this request @param Results A map of users to communication results
- L58 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnGDKCommunicationPermissionsQueryComplete, const FOnlineError& , const FUniqueNetIdRef& , const FCommunicationPermissionResultsMap& );` — Delegate used when the user communication permissions query has completed @param RequestStatus If this request was successful or not @param RequestingUser The user who generated this request @param Results A map of users to communication results
- L66 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGDKAnonymousUserCommunicationPermissionsQueryComplete, const FOnlineError& , const FAnonymousUserCommunicationPermissionResultsMap& );` — Delegate used when the class communication permissions query has completed @param RequestStatus If this request was successful or not @param Results A map of user types to communication results
- L66 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnGDKAnonymousUserCommunicationPermissionsQueryComplete, const FOnlineError& , const FAnonymousUserCommunicationPermissionResultsMap& );` — Delegate used when the class communication permissions query has completed @param RequestStatus If this request was successful or not @param Results A map of user types to communication results
- L132 _typedef_ `typedef TSharedPtr<FOnlineUserGDK, ESPMode::ThreadSafe> FOnlineUserGDKPtr;`
