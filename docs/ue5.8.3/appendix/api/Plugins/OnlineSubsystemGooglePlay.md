# Plugins / OnlineSubsystemGooglePlay

- module root: `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source`
- headers: 21; symbols: 381
- symbol kinds: class=16, delegate=4, enum=4, enumerator=20, function=45, macro=2, member=83, namespace=4, prototype=174, struct=6, typedef=21, variable=2
- PrivateDependencyModuleNames: AndroidRuntimeSettings, Core, CoreOnline, Engine, Launch, OnlineSubsystem

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/GooglePlayGamesWrapper.h` (Private)


#### class `FGooglePlayGamesWrapper`  
`class FGooglePlayGamesWrapper`  
_L20-48_
- L23 _public prototype_ `FGooglePlayGamesWrapper() = default;`
- L24 _public prototype_ `FGooglePlayGamesWrapper(const FGooglePlayGamesWrapper& Other) = delete;`
- L25 _public prototype_ `FGooglePlayGamesWrapper& operator=(const FGooglePlayGamesWrapper& Other) = delete;`
- L26 _public prototype_ `~FGooglePlayGamesWrapper();`
- L28 _public prototype_ `void Init();`
- L29 _public prototype_ `void Reset();`
- L31 _public prototype_ `bool Login(FOnlineAsyncTaskGooglePlayLogin* Task, const FString& InAuthCodeClientId, bool InForceRefreshToken);`
- L32 _public prototype_ `bool RequestLeaderboardScore(FOnlineAsyncTaskGooglePlayReadLeaderboard* Task, const FString& LeaderboardId);`
- L33 _public prototype_ `bool FlushLeaderboardsScores(FOnlineAsyncTaskGooglePlayFlushLeaderboards* Task, const TArray<FGooglePlayLeaderboardScore>& Scores);`
- L34 _public prototype_ `bool QueryAchievements(FOnlineAsyncTaskGooglePlayQueryAchievements* Task);`
- L35 _public prototype_ `bool WriteAchievements(FOnlineAsyncTaskGooglePlayWriteAchievements* Task, const TArray<FGooglePlayAchievementWriteData>& WriteAchievementsData);`
- L36 _public prototype_ `bool ShowAchievementsUI();`
- L37 _public prototype_ `bool ShowLeaderboardUI(const FString& LeaderboardName);`
- L40 _private member_ `jclass PlayGamesWrapperClass = nullptr;`
- L41 _private member_ `jmethodID LoginMethodId = nullptr;`
- L42 _private member_ `jmethodID RequestLeaderboardScoreId = nullptr;`
- L43 _private member_ `jmethodID SubmitLeaderboardsScoresId = nullptr;`
- L44 _private member_ `jmethodID QueryAchievementsId = nullptr;`
- L45 _private member_ `jmethodID WriteAchievementsId = nullptr;`
- L46 _private member_ `jmethodID ShowAchievementsUIId = nullptr;`
- L47 _private member_ `jmethodID ShowLeaderboardUIId = nullptr;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineAchievementGooglePlayCommon.h` (Private)


#### enum `FGooglePlayAchievementWriteAction`  
`enum class FGooglePlayAchievementWriteAction : int32`  
_L7-11_
- L9 _public enumerator_ `Unlock = 0` — Unlock the achievement
- L10 _public enumerator_ `WriteSteps = 1` — Update achievement steps accomplished

#### struct `FGooglePlayAchievementWriteData`  
`struct FGooglePlayAchievementWriteData`  
_L13-21_
- L16 _public member_ `FString GooglePlayAchievementId;` — Achievement Id as shown in GooglePlay Console
- L18 _public member_ `FGooglePlayAchievementWriteAction Action = FGooglePlayAchievementWriteAction::Unlock;` — Action to perform
- L20 _public member_ `int32 Steps = 0;` — Value to set in cas ethe action requires it

#### enum `EGooglePlayAchievementType`  
`enum class EGooglePlayAchievementType`  
_L23-27_
- L25 _public enumerator_ `Incremental` — Allows setting a number of steps until completion
- L26 _public enumerator_ `Standard` — Just allows unlocking

#### struct `FOnlineAchievementGooglePlay`  
`struct FOnlineAchievementGooglePlay: FOnlineAchievement`  
_L29-35_
- inherits: `FOnlineAchievement`
- L32 _public member_ `EGooglePlayAchievementType Type = EGooglePlayAchievementType::Standard;` — Achievement type
- L34 _public member_ `int32 TotalSteps = 0;` — Total number of steps needed to complete in case Type is EGooglePlayAchievementType::Incremental

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineAchievementsInterfaceGooglePlay.h` (Private)


#### class `FOnlineAchievementsGooglePlay`  
`class FOnlineAchievementsGooglePlay : public IOnlineAchievements`  
_L13-74_
- inherits: `IOnlineAchievements`
- desc: IOnlineAchievements - Interface class for Achievements
- L18 _private member_ `class FOnlineSubsystemGooglePlay* Subsystem;` — Reference to the main subsystem
- L21 _private member_ `TArray<FOnlineAchievementGooglePlay> Achievements;` — Cached achievements retrieved from Google Play
- L24 _private member_ `TMap<FString, FOnlineAchievementDesc> AchievementDescriptions;` — Cached achievement descriptions retrieved from Google Play
- L26 _private prototype_ `static TOptional<FString> GetUnrealAchievementIdFromGoogleAchievementId(const class UAndroidRuntimeSettings* Settings, const FString& GoogleId);`
- L27 _private prototype_ `static TOptional<FString> GetGoogleAchievementIdFromUnrealAchievementId(const class UAndroidRuntimeSettings* Settings, const FString& UnrealId);`
- L37 _private prototype_ `void FinishAchievementWrite( const FUniqueNetId& PlayerId, const bool bWasSuccessful, FOnlineAchievementsWriteRef WriteObject, FOnAchievementsWrittenDelegate Delegate);` — Using the WriteObject, fires off achievement progress calls to the Google Java backend. Non-blocking. @param PlayerId the id of the player who's making progress @param bWasSuccessful whether a previous QueryAchievements call was successful @param WriteObject achievement write object provided by the user @param Delegate delegate to execute when the write operation is finished
- L44 _private prototype_ `bool IsLocalPlayer(const FUniqueNetId& PlayerId) const;` — Asks the identity interface it this PlayerId refers to the local player. We can only get information about the local player from GooglePlay
- L50 _private prototype_ `void UpdateCache(TArray<FOnlineAchievementGooglePlay>&& Results, TArray<FOnlineAchievementDesc>&& Descriptions);` — Called from the query achievements task to fill in the cache.
- L53 _private prototype_ `void UpdateCacheAfterWrite(const TArray<FGooglePlayAchievementWriteData>& WrittenData);` — Called from the write achievements task to update cache with written data.
- L57 _public prototype_ `virtual void WriteAchievements(const FUniqueNetId& PlayerId, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& Delegate = FOnAchievementsWrittenDelegate()) override;`
- L58 _public prototype_ `virtual void QueryAchievements(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate()) override;`
- L59 _public prototype_ `virtual void QueryAchievementDescriptions(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate()) override ;`
- L60 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievement(const FUniqueNetId& PlayerId, const FString& AchievementId, FOnlineAchievement& OutAchievement) override;`
- L61 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievements(const FUniqueNetId& PlayerId, TArray<FOnlineAchievement>& OutAchievements) override;`
- L62 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievementDescription(const FString& AchievementId, FOnlineAchievementDesc& OutAchievementDesc) override;`
- L64 _public prototype_ `virtual bool ResetAchievements( const FUniqueNetId& PlayerId ) override;`
- L73 _public prototype_ `FOnlineAchievementsGooglePlay( class FOnlineSubsystemGooglePlay* InSubsystem );` — Constructor @param InSubsystem - A reference to the owning subsystem

#### Free symbols / members of external scopes

- L76 _typedef_ `typedef TSharedPtr<FOnlineAchievementsGooglePlay, ESPMode::ThreadSafe> FOnlineAchievementsGooglePlayPtr;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineAsyncTaskGooglePlayFlushLeaderboards.h` (Private)


#### class `FOnlineAsyncTaskGooglePlayFlushLeaderboards`  
`class FOnlineAsyncTaskGooglePlayFlushLeaderboards : public FOnlineAsyncTaskBasic<FOnlineSubsystemGooglePlay>`  
_L16-42_
- inherits: `FOnlineAsyncTaskBasic<FOnlineSubsystemGooglePlay>`
- desc: Task object to keep track of writing achievement score data Objects of this type are associated with a GooglePlayGamesWrapper method call that routes operations to the Java backend. The GooglePlayGamesWrapper implementation will adapt and set the task result and mark the task as completed when the Java operation is finished
- L26 _public prototype_ `FOnlineAsyncTaskGooglePlayFlushLeaderboards( FOnlineSubsystemGooglePlay* InSubsystem, FName InSessionName, TArray<FGooglePlayLeaderboardScore>&& LeaderboardScores);` — @brief Construct a new FOnlineAsyncTaskGooglePlayFlushLeaderboards object @param InSubsystem Owning subsystem @param InSessionName Session name to report using in the delegate @param LeaderboardScores Achievement data to submit
- L32 _public prototype_ `virtual void Tick() override;` — FOnlineAsyncTask
- L33 _public prototype_ `virtual void TriggerDelegates() override;`
- L36 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L39 _private member_ `TArray<FGooglePlayLeaderboardScore> LeaderboardScores;`
- L40 _private member_ `FName SessionName;`
- L41 _private member_ `bool bStarted = false;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineAsyncTaskGooglePlayLogin.h` (Private)


#### class `FOnlineAsyncTaskGooglePlayLogin`  
`class FOnlineAsyncTaskGooglePlayLogin : public FOnlineAsyncTaskBasic<FOnlineSubsystemGooglePlay>`  
_L16-49_
- inherits: `FOnlineAsyncTaskBasic<FOnlineSubsystemGooglePlay>`
- desc: Task object to keep track of writing achievement score data Objects of this type are associated with a GooglePlayGamesWrapper method call that routes operations to the Java backend. The GooglePlayGamesWrapper implementation will adapt and set the task result and mark the task as completed when the Java operation is finished
- L26 _public prototype_ `FOnlineAsyncTaskGooglePlayLogin( FOnlineSubsystemGooglePlay* InSubsystem, const FString& InAuthCodeClientId, bool InForceRefreshToken);` — @brief Construct a new FOnlineAsyncTaskGooglePlayLogin object @param InSubsystem Owning subsystem @param InAuthCodeClientId The client ID of the server that will perform the authorization code flow exchange. Won't request authorization code if empty @param InForceRefreshToken If true a refresh token will be included in addition to the access token when the authorization code is exchanged
- L32 _public prototype_ `virtual void Tick() override;` — FOnlineAsyncTask
- L33 _public prototype_ `void Finalize() override;`
- L34 _public prototype_ `void TriggerDelegates() override;`
- L37 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L40 _public prototype_ `void SetLoginData(FString&& PlayerId, FString&& PlayerDisplayName, FString&& AuthCode);` — Set task result data. Accessed trhough GooglePlayGamesWrapper implementation
- L42 _private member_ `FString AuthCodeClientId;`
- L43 _private member_ `bool ForceRefreshToken;`
- L44 _private member_ `bool bStarted = false;`
- L45 _private member_ `bool bWasLoggedIn = false;`
- L46 _private member_ `FUniqueNetIdGooglePlayPtr ReceivedPlayerNetId;`
- L47 _private member_ `FString ReceivedDisplayName;`
- L48 _private member_ `FString ReceivedAuthCode;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineAsyncTaskGooglePlayQueryAchievements.h` (Private)


#### class `FOnlineAsyncTaskGooglePlayQueryAchievements`  
`class FOnlineAsyncTaskGooglePlayQueryAchievements : public FOnlineAsyncTaskBasic<FOnlineSubsystemGooglePlay>`  
_L17-48_
- inherits: `FOnlineAsyncTaskBasic<FOnlineSubsystemGooglePlay>`
- desc: Task object to keep track of writing achievement score data Objects of this type are associated with a GooglePlayGamesWrapper method call that routes operations to the Java backend. The GooglePlayGamesWrapper implementation will adapt and set the task result and mark the task as completed when the Java operation is finished
- L27 _public prototype_ `FOnlineAsyncTaskGooglePlayQueryAchievements( FOnlineSubsystemGooglePlay* InSubsystem, const FUniqueNetIdPtr& PlayerId, const FOnQueryAchievementsCompleteDelegate& InDelegate);` — @brief Construct a new FOnlineAsyncTaskGooglePlayQueryAchievements object @param InSubsystem Owning subsystem @param PlayerId PlayerId to report in the delegate. Only data for local player can be received from GooglePlay @param InDelegate Delegate to invoke on task completion
- L33 _public prototype_ `virtual void Tick() override;` — FOnlineAsyncTask
- L34 _public prototype_ `virtual void Finalize() override;`
- L35 _public prototype_ `virtual void TriggerDelegates() override;`
- L38 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L41 _public prototype_ `void SetAchievementsData(TArray<FOnlineAchievementGooglePlay>&& InAchievementsData, TArray<FOnlineAchievementDesc>&& InAchievementsDesc);` — Set task result data. Accessed trhough GooglePlayGamesWrapper implementation
- L43 _private member_ `FUniqueNetIdPtr PlayerId;`
- L44 _private member_ `FOnQueryAchievementsCompleteDelegate Delegate;`
- L45 _private member_ `TArray<FOnlineAchievementGooglePlay> AchievementsData;`
- L46 _private member_ `TArray<FOnlineAchievementDesc> AchievementsDesc;`
- L47 _private member_ `bool bStarted = false;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineAsyncTaskGooglePlayReadLeaderboard.h` (Private)


#### class `FOnlineAsyncTaskGooglePlayReadLeaderboard`  
`class FOnlineAsyncTaskGooglePlayReadLeaderboard : public FOnlineAsyncTaskBasic<FOnlineSubsystemGooglePlay>`  
_L16-45_
- inherits: `FOnlineAsyncTaskBasic<FOnlineSubsystemGooglePlay>`
- desc: Task object to keep track of writing achievement score data Objects of this type are associated with a GooglePlayGamesWrapper method call that routes operations to the Java backend. The GooglePlayGamesWrapper implementation will adapt and set the task result and mark the task as completed when the Java operation is finished
- L26 _public prototype_ `FOnlineAsyncTaskGooglePlayReadLeaderboard( FOnlineSubsystemGooglePlay* InSubsystem, const FOnlineLeaderboardReadRef& InReadObject, const FString& InLeaderboardId);` — @brief Construct a new FOnlineAsyncTaskGooglePlayReadLeaderboard object @param InSubsystem Owning subsystem @param InReadObject Destination object for the leaderboard information received @param InLeaderboardId GooglePlay leaderboard id to request
- L32 _public prototype_ `virtual void Tick() override;` — FOnlineAsyncTask
- L33 _public prototype_ `void Finalize() override;`
- L34 _public prototype_ `void TriggerDelegates() override;`
- L37 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L40 _public prototype_ `void AddScore(const FString& DisplayName, const FString& PlayerId, int64 Rank, int64 RawScore);` — Set task result data. Accessed trhough GooglePlayGamesWrapper implementation
- L42 _private member_ `FString LeaderboardId;`
- L43 _private member_ `bool bStarted = false;`
- L44 _private member_ `FOnlineLeaderboardReadRef ReadObject;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineAsyncTaskGooglePlayWriteAchievements.h` (Private)


#### class `FOnlineAsyncTaskGooglePlayWriteAchievements`  
`class FOnlineAsyncTaskGooglePlayWriteAchievements : public FOnlineAsyncTaskBasic<FOnlineSubsystemGooglePlay>`  
_L17-56_
- inherits: `FOnlineAsyncTaskBasic<FOnlineSubsystemGooglePlay>`
- desc: Task object to keep track of writing achievement score data Objects of this type are associated with a GooglePlayGamesWrapper method call that routes operations to the Java backend. The GooglePlayGamesWrapper implementation will adapt and set the task result and mark the task as completed when the Java operation is finished
- L28 _public prototype_ `FOnlineAsyncTaskGooglePlayWriteAchievements( FOnlineSubsystemGooglePlay* InSubsystem, const FUniqueNetIdPtr& PlayerId, TArray<FGooglePlayAchievementWriteData>&& InWriteAchievements, const FOnAchievementsWrittenDelegate& Delegate);` — @brief Construct a new FOnlineAsyncTaskGooglePlayWriteAchievements object @param InSubsystem Owning subsystem @param PlayerId PlayerId to report in the delegate. Only data for local player can be received from GooglePlay @param InWriteAchievements Achievement data to send @param Delegate Delegate to invoke on task completion
- L41 _public prototype_ `bool SetSucceeded(const TArray<FString>& SucceededIds);` — @brief Notifies the list of achievement writes that succeeded @param SucceededIds @return true If all achievements expected to be written succeeded @return false Otherwise
- L44 _public prototype_ `virtual void Tick() override;` — FOnlineAsyncTask
- L45 _public prototype_ `virtual void Finalize() override;`
- L46 _public prototype_ `virtual void TriggerDelegates() override;`
- L49 _public function_ `virtual FString ToString() const override` — FOnlineAsyncItem
- L52 _private member_ `FUniqueNetIdPtr PlayerId;`
- L53 _private member_ `TArray<FGooglePlayAchievementWriteData> WriteAchievementsData;`
- L54 _private member_ `FOnAchievementsWrittenDelegate Delegate;`
- L55 _private member_ `bool bStarted = false;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineAsyncTaskManagerGooglePlay.h` (Private)


#### class `FOnlineAsyncTaskManagerGooglePlay`  
`class FOnlineAsyncTaskManagerGooglePlay : public FOnlineAsyncTaskManager`  
_L12-20_
- inherits: `FOnlineAsyncTaskManager`
- desc: Google Play version of the async task manager
- L16 _public function_ `FOnlineAsyncTaskManagerGooglePlay()`
- L19 _public function_ `virtual void OnlineTick() override` — FOnlineAsyncTaskManager

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineExternalUIInterfaceGooglePlay.h` (Private)


#### class `FOnlineExternalUIGooglePlay`  
`class FOnlineExternalUIGooglePlay : public IOnlineExternalUI`  
_L16-37_
- inherits: `IOnlineExternalUI`
- desc: Interface definition for the online services external UIs Any online service that provides extra UI overlays will implement the relevant functions
- L20 _private member_ `FOnlineSubsystemGooglePlay* Subsystem;`
- L23 _public prototype_ `FOnlineExternalUIGooglePlay(FOnlineSubsystemGooglePlay* InSubsystem);`
- L25 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;`
- L26 _public function_ `virtual bool ShowAccountCreationUI(const int ControllerIndex, const FOnAccountCreationUIClosedDelegate& Delegate = FOnAccountCreationUIClosedDelegate()) override`
- L27 _public prototype_ `virtual bool ShowFriendsUI(int32 LocalUserNum) override;`
- L28 _public prototype_ `virtual bool ShowInviteUI(int32 LocalUserNum, FName SessionName) override;`
- L29 _public prototype_ `virtual bool ShowAchievementsUI(int32 LocalUserNum) override;`
- L30 _public prototype_ `virtual bool ShowLeaderboardUI(const FString& LeaderboardName) override;`
- L31 _public prototype_ `virtual bool ShowWebURL(const FString& Url, const FShowWebUrlParams& ShowParams, const FOnShowWebUrlClosedDelegate& Delegate = FOnShowWebUrlClosedDelegate()) override;`
- L32 _public prototype_ `virtual bool CloseWebURL() override;`
- L33 _public prototype_ `virtual bool ShowProfileUI(const FUniqueNetId& Requestor, const FUniqueNetId& Requestee, const FOnProfileUIClosedDelegate& Delegate = FOnProfileUIClosedDelegate()) override;`
- L34 _public prototype_ `virtual bool ShowAccountUpgradeUI(const FUniqueNetId& UniqueId) override;`
- L35 _public prototype_ `virtual bool ShowStoreUI(int32 LocalUserNum, const FShowStoreParams& ShowParams, const FOnShowStoreUIClosedDelegate& Delegate = FOnShowStoreUIClosedDelegate()) override;`
- L36 _public prototype_ `virtual bool ShowSendMessageUI(int32 LocalUserNum, const FShowSendMessageParams& ShowParams, const FOnShowSendMessageUIClosedDelegate& Delegate = FOnShowSendMessageUIClosedDelegate()) override;`

#### Free symbols / members of external scopes

- L39 _typedef_ `typedef TSharedPtr<FOnlineExternalUIGooglePlay, ESPMode::ThreadSafe> FOnlineExternalUIGooglePlayPtr;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineIdentityInterfaceGooglePlay.h` (Private)


#### class `FOnlineIdentityGooglePlay`  
`class FOnlineIdentityGooglePlay : public IOnlineIdentity`  
_L12-50_
- inherits: `IOnlineIdentity`
- L16 _private member_ `TSharedPtr<class FUserOnlineAccountGooglePlay> LocalPlayerAccount;`
- L18 _private member_ `class FOnlineSubsystemGooglePlay* MainSubsystem;`
- L26 _private prototype_ `void SetIdentityData(const FUniqueNetIdGooglePlayPtr& PlayerNetId, FString PlayerAlias, FString AuthCode);`
- L27 _private prototype_ `void ClearIdentity();`
- L32 _public prototype_ `virtual TSharedPtr<FUserOnlineAccount> GetUserAccount(const FUniqueNetId& UserId) const override;`
- L33 _public prototype_ `virtual TArray<TSharedPtr<FUserOnlineAccount> > GetAllUserAccounts() const override;`
- L34 _public prototype_ `virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;`
- L35 _public prototype_ `virtual bool Logout(int32 LocalUserNum) override;`
- L36 _public prototype_ `virtual bool AutoLogin(int32 LocalUserNum) override;`
- L37 _public prototype_ `virtual FUniqueNetIdPtr GetUniquePlayerId(int32 LocalUserNum) const override;`
- L38 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(uint8* Bytes, int32 Size) override;`
- L39 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(const FString& Str) override;`
- L40 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(int32 LocalUserNum) const override;`
- L41 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(const FUniqueNetId& UserId) const override;`
- L42 _public prototype_ `virtual FString GetPlayerNickname(int32 LocalUserNum) const override;`
- L43 _public prototype_ `virtual FString GetPlayerNickname(const FUniqueNetId& UserId) const override;`
- L44 _public prototype_ `virtual FString GetAuthToken(int32 LocalUserNum) const override;`
- L45 _public prototype_ `virtual void RevokeAuthToken(const FUniqueNetId& UserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate) override;`
- L46 _public prototype_ `virtual void GetUserPrivilege(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate, EShowPrivilegeResolveUI ShowResolveUI=EShowPrivilegeResolveUI::Default) override;`
- L47 _public prototype_ `virtual FPlatformUserId GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& NetId) const override;`
- L48 _public prototype_ `virtual FString GetAuthType() const override;`

#### Free symbols / members of external scopes

- L10 _prototype_ `TEMP_UNIQUENETIDSTRING_SUBCLASS(FUniqueNetIdGooglePlay, GOOGLEPLAY_SUBSYSTEM);` — from OnlineSubsystemTypes.h
- L53 _typedef_ `typedef TSharedPtr<FOnlineIdentityGooglePlay, ESPMode::ThreadSafe> FOnlineIdentityGooglePlayPtr;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineJniGooglePlayGamesWrapper.h` (Private)


#### struct `UE::Jni::FGooglePlayGamesWrapper`  
`struct FGooglePlayGamesWrapper: Java::Lang::FObject`  
_L11-37_
- inherits: `Java::Lang::FObject`
- L13 _public member_ `static constexpr bool bIsOptional = true;`
- L15 _public member_ `static constexpr FAnsiStringView ClassName = "co`
- L17 _public prototype_ `static void JNICALL nativeLoginSuccess(JNIEnv* env, jclass clazz, jlong TaskPtr, jstring InPlayerId, jstring InPlayerDisplayName, jstring InAuthCode);`
- L18 _public prototype_ `static void JNICALL nativeLoginFailed(JNIEnv* env, jclass clazz, jlong TaskPtr);`
- L19 _public prototype_ `static void JNICALL nativeLeaderboardRequestSuccess(JNIEnv* env, jclass clazz, jlong TaskPtr, jstring InDisplayName, jstring InPlayerId, jlong InRank, jlong InRawScore);`
- L20 _public prototype_ `static void JNICALL nativeLeaderboardRequestFailed(JNIEnv* env, jclass clazz, jlong TaskPtr);`
- L21 _public prototype_ `static void JNICALL nativeFlushLeaderboardsCompleted(JNIEnv* env, jclass clazz, jlong TaskPtr, jboolean InSuccess);`
- L22 _public prototype_ `static void JNICALL nativeQueryAchievementsSuccess(JNIEnv* env, jclass clazz, jlong TaskPtr, Java::Lang::TArray<jstring>* InAchievementIds, Java::Lang::TArray<jint>* InTypes, Java::Lang::TArray<jint>* InSteps, Java::Lang::TArray<jint>* InTotalSteps, Java::Lang::TArray<jstring>* InTitles, Java::Lang::TArray<jstring>* InDescriptions, Java::Lang::TArray<jboolean>* InIsHidden, Java::Lang::TArray<jlong>* InLastUpdatedTimestamps);`
- L23 _public prototype_ `static void JNICALL nativeQueryAchievementsFailed(JNIEnv* env, jclass clazz, jlong TaskPtr);`
- L24 _public prototype_ `static void JNICALL nativeWriteAchievementsCompleted(JNIEnv* env, jclass clazz, jlong TaskPtr, Java::Lang::TArray<jstring>* InSucceeded);`
- L26 _public member_ `static constexpr FNativeMethod NativeMethods[] { UE_JNI_NATIVE_METHOD(nativeLoginSuccess), UE_JNI_NATIVE_METHOD(nativeLoginFailed), UE_JNI_NATIVE_METHOD(nativeLeaderboardRequestSuccess), UE_JNI_NATIVE_METHOD(nativeLeaderboardRequestFailed), UE_JNI_NATIVE_METHOD(nativeFlushLeaderboardsCompleted), UE_JNI_NATIVE_METHOD(nativeQueryAchievementsSuccess), UE_JNI_NATIVE_METHOD(nativeQueryAchievementsFailed), UE_JNI_NATIVE_METHOD(nativeWriteAchievementsCompleted) };`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Jni` (scope `UE`)
- L39 _variable_ `template struct TInitialize<FGooglePlayGamesWrapper>;` (scope `UE::Jni`)

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineJniGooglePlayStoreHelper.h` (Private)


#### struct `UE::Jni::FGooglePlayStoreHelper`  
`struct FGooglePlayStoreHelper: Java::Lang::FObject`  
_L11-33_
- inherits: `Java::Lang::FObject`
- L13 _public member_ `static constexpr bool bIsOptional = true;`
- L15 _public member_ `static constexpr FAnsiStringView ClassName = "co`
- L17 _public prototype_ `static void JNICALL NativeQueryComplete(JNIEnv* env, jobject thiz, jint ResponseCode, Java::Lang::TArray<jstring>* ProductIDs, Java::Lang::TArray<jstring>* Titles, Java::Lang::TArray<jstring>* Descriptions, Java::Lang::TArray<jstring>* Prices, Java::Lang::TArray<jlong>* PriceValuesRaw, Java::Lang::TArray<jstring>* CurrencyCodes, Java::Lang::TArray<jstring>* RegularPrices, Java::Lang::TArray<jlong>* RegularPriceValuesRaw, Java::Lang::TArray<jint>* DiscountTypes);`
- L18 _public prototype_ `static void JNICALL NativeQueryExistingPurchasesComplete(JNIEnv* env, jobject thiz, jint ResponseCode, Java::Lang::TArray<jstring, 2>* ProductIDs, Java::Lang::TArray<jint>* PurchaseStatesArray, Java::Lang::TArray<jstring>* PurchaseTokens, Java::Lang::TArray<jstring>* ReceiptsData, Java::Lang::TArray<jstring>* Signatures);`
- L19 _public prototype_ `static void JNICALL NativePurchaseComplete(JNIEnv* env, jobject thiz, jint JavaResponseCode, Java::Lang::TArray<jstring>* JavaProductIds, jint JavaPurchaseState, jstring JavaPurchaseToken, jstring JavaReceiptData, jstring JavaSignature);`
- L20 _public prototype_ `static void JNICALL NativeConsumeComplete(JNIEnv* env, jobject thiz, jint JavaResponseCode, jstring JavaPurchaseToken);`
- L21 _public prototype_ `static void JNICALL NativeAcknowledgeComplete(JNIEnv* env, jobject thiz, jint JavaResponseCode, jstring JavaPurchaseToken);`
- L22 _public prototype_ `static void JNICALL NativeAlternativeBillingOnlyInformationDialogComplete(JNIEnv* env, jobject thiz, jint JavaResponseCode);`
- L24 _public member_ `static constexpr FNativeMethod NativeMethods[] { UE_JNI_NATIVE_METHOD(NativeQueryComplete), UE_JNI_NATIVE_METHOD(NativeQueryExistingPurchasesComplete), UE_JNI_NATIVE_METHOD(NativePurchaseComplete), UE_JNI_NATIVE_METHOD(NativeConsumeComplete), UE_JNI_NATIVE_METHOD(NativeAcknowledgeComplete), UE_JNI_NATIVE_METHOD(NativeAlternativeBillingOnlyInformationDialogComplete) };`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Jni` (scope `UE`)
- L35 _variable_ `template struct TInitialize<FGooglePlayStoreHelper>;` (scope `UE::Jni`)

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineLeaderboardGooglePlayCommon.h` (Private)


#### struct `FGooglePlayLeaderboardScore`  
`struct FGooglePlayLeaderboardScore`  
_L7-13_
- L10 _public member_ `FString GooglePlayLeaderboardId;` — Leaderboard ID as shown in GooglePlay Console
- L12 _public member_ `int64 Score = 0;` — Leaderboard score

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineLeaderboardInterfaceGooglePlay.h` (Private)


#### class `FOnlineLeaderboardsGooglePlay`  
`class FOnlineLeaderboardsGooglePlay : public IOnlineLeaderboards`  
_L13-38_
- inherits: `IOnlineLeaderboards`
- desc: Interface definition for the online services leaderboard services
- L16 _public prototype_ `FOnlineLeaderboardsGooglePlay(class FOnlineSubsystemGooglePlay* InSubsystem);`
- L18 _public prototype_ `virtual bool ReadLeaderboards(const TArray< FUniqueNetIdRef >& Players, FOnlineLeaderboardReadRef& ReadObject) override;`
- L19 _public prototype_ `virtual bool ReadLeaderboardsForFriends(int32 LocalUserNum, FOnlineLeaderboardReadRef& ReadObject) override;`
- L20 _public prototype_ `virtual bool ReadLeaderboardsAroundRank(int32 Rank, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) override;`
- L21 _public prototype_ `virtual bool ReadLeaderboardsAroundUser(FUniqueNetIdRef Player, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) override;`
- L22 _public prototype_ `virtual void FreeStats(FOnlineLeaderboardRead& ReadObject) override;`
- L23 _public prototype_ `virtual bool WriteLeaderboards(const FName& SessionName, const FUniqueNetId& Player, FOnlineLeaderboardWrite& WriteObject) override;`
- L24 _public prototype_ `virtual bool FlushLeaderboards(const FName& SessionName) override;`
- L25 _public prototype_ `virtual bool WriteOnlinePlayerRatings(const FName& SessionName, int32 LeaderboardId, const TArray<FOnlinePlayerScore>& PlayerScores) override;`
- L29 _private member_ `FOnlineSubsystemGooglePlay* Subsystem;` — Pointer to owning subsystem
- L31 _private prototype_ `FString GetLeaderboardID(const FString& LeaderboardName);`
- L34 _private member_ `TArray<FGooglePlayLeaderboardScore> UnreportedScores;` — Scores are cached here in WriteLeaderboards until FlushLeaderboards is called
- L37 _private prototype_ `bool IsLocalPlayer(const FUniqueNetId& PlayerId) const;` — Asks the identity interface it this PlayerId refers to the local player. We can only get information about the local player from GooglePlay

#### Free symbols / members of external scopes

- L40 _typedef_ `typedef TSharedPtr<FOnlineLeaderboardsGooglePlay, ESPMode::ThreadSafe> FOnlineLeaderboardsGooglePlayPtr;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Private/OnlineStoreGooglePlayCommon.h` (Private)


#### enum `EGooglePlayBillingResponseCode`  
`enum class EGooglePlayBillingResponseCode : int8`  
_L14-29_
- desc: Possible responses returned from the Java GooglePlay billing interface. CustomLogicError is a custom Unreal Engine error to represent logic errors on the Java side
- L16 _public enumerator_ `CustomLogicError = -127` — Custom value. Should match with GooglePlayStoreHelper.CustomLogicErrorResponse on GooglePlayStoreHelper.java
- L17 _public enumerator_ `FeatureNotSupported = -2`
- L18 _public enumerator_ `ServiceDisconnected = -1`
- L19 _public enumerator_ `Ok = 0`
- L20 _public enumerator_ `UserCancelled = 1`
- L21 _public enumerator_ `ServiceUnavailable = 2`
- L22 _public enumerator_ `BillingUnavailable = 3`
- L23 _public enumerator_ `ItemUnavailable = 4`
- L24 _public enumerator_ `DeveloperError = 5`
- L25 _public enumerator_ `Error = 6`
- L26 _public enumerator_ `ItemAlreadyOwned = 7`
- L27 _public enumerator_ `ItemNotOwned = 8`
- L28 _public enumerator_ `NetworkError = 12`

#### enum `EGooglePlayPurchaseState`  
`enum class EGooglePlayPurchaseState : uint8`  
_L32-37_
- desc: Possible transaction states returned from the Java GooglePlay billing interface.
- L34 _public enumerator_ `UnspecifiedState = 0`
- L35 _public enumerator_ `Purchased = 1`
- L36 _public enumerator_ `Pending = 2`

#### Free symbols / members of external scopes

- L39 _function_ `inline const TCHAR* const LexToString(EGooglePlayBillingResponseCode InResponseCode)`
- L74 _function_ `inline const TCHAR* const LexToString(EGooglePlayPurchaseState InTransactionState)`
- L89 _function_ `inline EInAppPurchaseState::Type ConvertGPResponseCodeToIAPState(const EGooglePlayBillingResponseCode InResponseCode)`
- L114 _function_ `inline EPurchaseTransactionState ConvertGPPurchaseStateToPurchaseTransactionState(const EGooglePlayPurchaseState InTransactionState)`
- L127 _function_ `inline EPurchaseTransactionState ConvertGPResponseToPurchaseTransactionState(const EGooglePlayBillingResponseCode InResponseCode, const EGooglePlayPurchaseState InPurchaseState)`
- L153 _typedef_ `typedef FOnlineStoreOffer FProvidedProductInformation;`
- L161 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGooglePlayAvailableIAPQueryComplete, EGooglePlayBillingResponseCode , const TArray<FProvidedProductInformation>& );` — Delegate fired when an IAP query for available offers has completed @param Response response from GooglePlay backend @param ProvidedProductInformation list of offers returned in response to a query on available offer ids
- L161 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGooglePlayAvailableIAPQueryComplete, EGooglePlayBillingResponseCode , const TArray<FProvidedProductInformation>& );` — Delegate fired when an IAP query for available offers has completed @param Response response from GooglePlay backend @param ProvidedProductInformation list of offers returned in response to a query on available offer ids
- L162 _typedef_ `typedef FOnGooglePlayAvailableIAPQueryComplete::FDelegate FOnGooglePlayAvailableIAPQueryCompleteDelegate;`
- L170 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGooglePlayProcessPurchaseComplete, EGooglePlayBillingResponseCode , const FGoogleTransactionData& );` — Delegate fired when an IAP has completed @param InResponseCode response from the GooglePlay backend @param InTransactionData transaction data for the completed purchase
- L170 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGooglePlayProcessPurchaseComplete, EGooglePlayBillingResponseCode , const FGoogleTransactionData& );` — Delegate fired when an IAP has completed @param InResponseCode response from the GooglePlay backend @param InTransactionData transaction data for the completed purchase
- L171 _typedef_ `typedef FOnGooglePlayProcessPurchaseComplete::FDelegate FOnGooglePlayProcessPurchaseCompleteDelegate;`
- L179 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGooglePlayQueryExistingPurchasesComplete, EGooglePlayBillingResponseCode , const TArray<FGoogleTransactionData>& );` — Delegate fired internally when an existing purchases query has completed @param InResponseCode response from the GooglePlay backend @param InExistingPurchases known purchases for the user (non consumed or permanent)
- L179 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGooglePlayQueryExistingPurchasesComplete, EGooglePlayBillingResponseCode , const TArray<FGoogleTransactionData>& );` — Delegate fired internally when an existing purchases query has completed @param InResponseCode response from the GooglePlay backend @param InExistingPurchases known purchases for the user (non consumed or permanent)
- L180 _typedef_ `typedef FOnGooglePlayQueryExistingPurchasesComplete::FDelegate FOnGooglePlayQueryExistingPurchasesCompleteDelegate;`
- L188 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGooglePlayConsumePurchaseComplete, EGooglePlayBillingResponseCode , const FString& );` — Delegate fired internally when a consume purchase query has completed @param InResponseCode response from the GooglePlay backend @param InPurchaseToken purchase token for consumed purchase
- L188 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGooglePlayConsumePurchaseComplete, EGooglePlayBillingResponseCode , const FString& );` — Delegate fired internally when a consume purchase query has completed @param InResponseCode response from the GooglePlay backend @param InPurchaseToken purchase token for consumed purchase
- L189 _typedef_ `typedef FOnGooglePlayConsumePurchaseComplete::FDelegate FOnGooglePlayConsumePurchaseCompleteDelegate;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Public/OnlinePurchaseGooglePlay.h` (Public)


#### struct `FGoogleTransactionData`  
`struct FGoogleTransactionData`  
_L16-78_
- desc: Holds in a common format the data that comes out of a Google purchase transaction
- L18 _public prototype_ `FGoogleTransactionData(const TArray<FString>& InOfferIds, const FString& InPurchaseToken, const FString& InReceiptData, const FString& InSignature, EGooglePlayPurchaseState InPurchaseState);`
- L21 _public prototype_ `FString ToDebugString() const;` — @return a string that prints useful debug information about this transaction
- L23 _public function_ `const FString& GetOfferId() const` — @return offer id for this transaction
- L25 _public function_ `const TArray<FString>& GetOfferIds() const` — @return all offer ids for this transaction
- L27 _public function_ `FString GetCombinedReceiptData() const` — @return receipt data for this transaction
- L29 _public function_ `const FString& GetReceiptData() const` — @return receipt data for this transaction
- L31 _public function_ `const FString& GetSignature() const` — @return signature for this transaction
- L33 _public function_ `const FString& GetErrorStr() const` — @return error string for this transaction, if applicable
- L35 _public function_ `const FString& GetTransactionIdentifier() const` — @return the purchase transaction id
- L37 _public function_ `EGooglePlayPurchaseState GetPurchaseState() const` — @return the purchase state
- L39 _public prototype_ `bool IsMatchingRequest(const FPurchaseCheckoutRequest& Request) const;` — Checks if all items reported in the transaction are present in the request
- L41 _public member_ `inline static const TCHAR* SubscriptionReceiptMarker = TEXT("isS` — marker found in the receipt data to indicate it refers to a subscription
- L69 _private member_ `TArray<FString> OfferIds;` — GooglePlay offer id
- L71 _private member_ `FString PurchaseToken;` — PurchaseToken for the transaction
- L73 _private member_ `FString ErrorStr;` — Error on the transaction, if applicable
- L75 _private member_ `FJsonReceiptData CombinedTransactionData;` — Combined receipt with signature in JSON
- L77 _private member_ `EGooglePlayPurchaseState PurchaseState;` — Reported GooglePlay transaction state

#### class `FGoogleTransactionData::FJsonReceiptData`  
`class FJsonReceiptData : public FJsonSerializable`  
_L45-66_
- inherits: `FJsonSerializable`
- desc: Easy access to transmission of data required for backend validation
- L50 _public function_ `FJsonReceiptData()`
- L51 _public prototype_ `FJsonReceiptData(const TArray<FString>& InOfferIds, const FString& InReceiptData, const FString& InSignature);`
- L54 _public member_ `TOptional<bool> IsSubscription;` — Opaque store receipt data
- L56 _public member_ `FString ReceiptData;` — Opaque store receipt data
- L58 _public member_ `FString Signature;` — Signature associated with the transaction

#### class `FOnlinePurchaseGooglePlay`  
`class FOnlinePurchaseGooglePlay : public IOnlinePurchase, public TSharedFromThis<FOnlinePurchaseGooglePlay, ESPMode::ThreadSafe>`  
_L83-175_
- inherits: `IOnlinePurchase,TSharedFromThis<FOnlinePurchaseGooglePlay,ESPMode::ThreadSafe>`
- desc: Implementation for online purchase via GooglePlay services
- L92 _public prototype_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId) override;`
- L93 _public prototype_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId, FOnlineError& Error) override;`
- L94 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseCheckoutComplete& Delegate) override;`
- L95 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseReceiptlessCheckoutComplete& Delegate) override;`
- L96 _public prototype_ `virtual void FinalizePurchase(const FUniqueNetId& UserId, const FString& ReceiptId) override;`
- L97 _public prototype_ `virtual void FinalizePurchase(const FUniqueNetId& UserId, const FString& ReceiptId, const FString& ReceiptInfo) override;`
- L98 _public prototype_ `virtual void RedeemCode(const FUniqueNetId& UserId, const FRedeemCodeRequest& RedeemCodeRequest, const FOnPurchaseRedeemCodeComplete& Delegate) override;`
- L99 _public prototype_ `virtual void QueryReceipts(const FUniqueNetId& UserId, bool bRestoreReceipts, const FOnQueryReceiptsComplete& Delegate) override;`
- L100 _public prototype_ `virtual void GetReceipts(const FUniqueNetId& UserId, TArray<FPurchaseReceipt>& OutReceipts) const override;`
- L101 _public prototype_ `virtual void FinalizeReceiptValidationInfo(const FUniqueNetId& UserId, FString& InReceiptValidationInfo, const FOnFinalizeReceiptValidationInfoComplete& Delegate) override;`
- L110 _public prototype_ `FOnlinePurchaseGooglePlay(class FOnlineSubsystemGooglePlay* InSubsystem);` — Constructor @param InSubsystem GooglePlay subsystem being used
- L115 _public prototype_ `virtual ~FOnlinePurchaseGooglePlay();` — Destructor
- L118 _public prototype_ `void Init();` — Initialize the interface
- L121 _public prototype_ `virtual void ShowAlternativeBillingInformationDialog(const FOnShowAlternativeBillingInformationDialogComplete& Delegate) override;` — Show the required Google Play system alternative billing informational dialog
- L124 _public prototype_ `void OnAlternativeBillingOnlyInformationDialogComplete(EGooglePlayBillingResponseCode InResponseCode);` — Handle response from showing the Google Play alternative billing only information dialog
- L127 _public prototype_ `void OnTransactionCompleteResponse(EGooglePlayBillingResponseCode InResponseCode, const FGoogleTransactionData& InTransactionData);` — Handle Java side transaction completed notification
- L130 _public prototype_ `void OnQueryExistingPurchasesComplete(EGooglePlayBillingResponseCode InResponseCode, const TArray<FGoogleTransactionData>& InExistingPurchases);` — Handle Java side query purchases completed notification
- L132 _public prototype_ `static bool IsSubscriptionProductId(const FString& ProductId);`
- L136 _private prototype_ `bool IsBillingClientConnected();` — Returns true if the Billing Client is connected and ready
- L144 _private typedef_ `using FOnlinePurchasePurchasedTransactions = TArray< TSharedRef<FPurchaseReceipt> >;` — Complete transactions
- L153 _private member_ `bool bDisableLocalAcknowledgeAndConsume = false;` — Acknoledge and consume are not invoked when calling FinishPurchase If this is set to 'true' acknowledge and consume should be invoked using server to server calls after validation to avoid refunds
- L156 _private member_ `bool bQueryingReceipts = false;` — Are receipts being queried
- L159 _private member_ `FOnQueryReceiptsComplete QueryReceiptsComplete;` — Transient delegate to fire when query receipts has completed
- L162 _private member_ `bool bRequestedAlternativeBillingOnlyInformationDialog = false;` — Is the system dialog already being shown
- L165 _private member_ `FOnShowAlternativeBillingInformationDialogComplete AlternativeBillingOnlyInformationDialogComplete;` — Delegate to call when the system dialog is finished
- L168 _private member_ `TSharedPtr<FOnlinePurchaseInProgressTransaction> InProgressTransaction;` — Keeps track of pending user transactions
- L171 _private member_ `FOnlinePurchasePurchasedTransactions KnownTransactions;` — Cache of known transactions
- L174 _private member_ `FOnlineSubsystemGooglePlay* Subsystem = nullptr;` — Reference to the parent subsystem

#### Free symbols / members of external scopes

- L177 _typedef_ `typedef TSharedPtr<FOnlinePurchaseGooglePlay, ESPMode::ThreadSafe> FOnlinePurchaseGooglePlayPtr;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Public/OnlineStoreGooglePlay.h` (Public)


#### class `FOnlineStoreGooglePlayV2`  
`class FOnlineStoreGooglePlayV2 : public IOnlineStoreV2, public TSharedFromThis<FOnlineStoreGooglePlayV2, ESPMode::ThreadSafe>`  
_L14-74_
- inherits: `IOnlineStoreV2,TSharedFromThis<FOnlineStoreGooglePlayV2,ESPMode::ThreadSafe>`
- desc: Implementation for online store via GooglePlay services
- L22 _public prototype_ `virtual void QueryCategories(const FUniqueNetId& UserId, const FOnQueryOnlineStoreCategoriesComplete& Delegate) override;`
- L23 _public prototype_ `virtual void GetCategories(TArray<FOnlineStoreCategory>& OutCategories) const override;`
- L24 _public prototype_ `virtual void QueryOffersByFilter(const FUniqueNetId& UserId, const FOnlineStoreFilter& Filter, const FOnQueryOnlineStoreOffersComplete& Delegate) override;`
- L25 _public prototype_ `virtual void QueryOffersById(const FUniqueNetId& UserId, const TArray<FUniqueOfferId>& OfferIds, const FOnQueryOnlineStoreOffersComplete& Delegate) override;`
- L26 _public prototype_ `virtual void GetOffers(TArray<FOnlineStoreOfferRef>& OutOffers) const override;`
- L27 _public prototype_ `virtual TSharedPtr<FOnlineStoreOffer> GetOffer(const FUniqueOfferId& OfferId) const override;`
- L36 _public prototype_ `FOnlineStoreGooglePlayV2(FOnlineSubsystemGooglePlay* InSubsystem);` — Constructor @param InSubsystem Online subsystem being used
- L41 _public prototype_ `FOnlineStoreGooglePlayV2();` — Constructor
- L46 _public prototype_ `virtual ~FOnlineStoreGooglePlayV2();` — Destructor
- L49 _public prototype_ `void OnGooglePlayAvailableIAPQueryComplete(EGooglePlayBillingResponseCode InResponse, const TArray<FProvidedProductInformation>& InProvidedProductInformation);` — Handle Java side query available iap completed notification
- L53 _private prototype_ `void AddOffer(const TSharedRef<FOnlineStoreOffer>& NewOffer);`
- L58 _private typedef_ `typedef TMap<FUniqueOfferId, TSharedRef<FOnlineStoreOffer>> FOnlineOfferDescriptionMap;` — Mapping from offer id to product information
- L61 _private member_ `FOnlineOfferDescriptionMap CachedOffers;` — Mapping of all queried offers to their product information
- L64 _private member_ `FOnQueryOnlineStoreOffersComplete QueryOnlineStoreOffersCompleteDelegate;` — The delegate to call for current query
- L67 _private member_ `bool bIsQueryInFlight;` — Is a query already in flight
- L70 _private member_ `FOnlineSubsystemGooglePlay* Subsystem;` — Reference to the parent subsystem
- L73 _private member_ `FOnQueryForAvailablePurchasesComplete OnQueryForAvailablePurchasesCompleteDelegate;` — Delegate fired when a query for purchases has completed, whether successful or unsuccessful

#### Free symbols / members of external scopes

- L76 _typedef_ `typedef TSharedPtr<FOnlineStoreGooglePlayV2, ESPMode::ThreadSafe> FOnlineStoreGooglePlayV2Ptr;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Public/OnlineSubsystemGooglePlay.h` (Public)


#### class `FOnlineSubsystemGooglePlay`  
`class FOnlineSubsystemGooglePlay : public FOnlineSubsystemImpl`  
_L29-138_
- inherits: `FOnlineSubsystemImpl`
- desc: OnlineSubsystemGooglePlay - Implementation of the online subsystem for Google Play services
- L34 _public prototype_ `virtual ~FOnlineSubsystemGooglePlay() = default;`
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
- L52 _public function_ `virtual IOnlineEventsPtr GetEventsInterface() const override`
- L53 _public function_ `virtual IOnlineMessagePtr GetMessageInterface() const override`
- L54 _public function_ `virtual IOnlineSharingPtr GetSharingInterface() const override`
- L55 _public function_ `virtual IOnlineUserPtr GetUserInterface() const override`
- L56 _public prototype_ `virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;`
- L57 _public function_ `virtual IOnlinePresencePtr GetPresenceInterface() const override`
- L58 _public function_ `virtual IOnlineChatPtr GetChatInterface() const override`
- L59 _public function_ `virtual IOnlineStatsPtr GetStatsInterface() const override`
- L60 _public function_ `virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override`
- L61 _public function_ `virtual IOnlineTournamentPtr GetTournamentInterface() const override`
- L63 _public function_ `virtual class UObject* GetNamedInterface(FName InterfaceName) override`
- L64 _public function_ `virtual void SetNamedInterface(FName InterfaceName, class UObject* NewInterface) override`
- L65 _public function_ `virtual bool IsDedicated() const override`
- L66 _public function_ `virtual bool IsServer() const override`
- L67 _public function_ `virtual void SetForceDedicated(bool bForce) override`
- L68 _public function_ `virtual bool IsLocalPlayer(const FUniqueNetId& UniqueId) const override`
- L70 _public prototype_ `virtual bool Init() override;`
- L71 _public prototype_ `virtual bool Shutdown() override;`
- L72 _public prototype_ `virtual FString GetAppId() const override;`
- L73 _public prototype_ `virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L74 _public prototype_ `virtual bool IsEnabled() const override;`
- L75 _public prototype_ `virtual FText GetOnlineServiceName() const override;`
- L78 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L83 _public prototype_ `explicit FOnlineSubsystemGooglePlay(FName InInstanceName);`
- L86 _public function_ `class FOnlineAsyncTaskManagerGooglePlay* GetAsyncTaskManager()` — Return the async task manager owned by this subsystem
- L92 _public prototype_ `void QueueAsyncTask(class FOnlineAsyncTask* AsyncTask);` — Add an async task onto the task queue for processing @param AsyncTask - new heap allocated task to process on the async task thread
- L94 _public function_ `FGooglePlayGamesWrapper& GetGooglePlayGamesWrapper()`
- L97 _public function_ `FOnlineIdentityGooglePlayPtr GetIdentityGooglePlay() const` — Returns the Google Play-specific version of Identity, useful to avoid unnecessary casting
- L100 _public function_ `FOnlineLeaderboardsGooglePlayPtr GetLeaderboardsGooglePlay() const` — Returns the Google Play-specific version of Leaderboards, useful to avoid unnecessary casting
- L103 _public function_ `FOnlineAchievementsGooglePlayPtr GetAchievementsGooglePlay() const` — Returns the Google Play-specific version of Achievements, useful to avoid unnecessary casting
- L109 _public prototype_ `bool IsInAppPurchasingEnabled();` — Is IAP available for use @return true if IAP should be available, false otherwise
- L114 _private member_ `TUniquePtr<class FOnlineAsyncTaskManagerGooglePlay> OnlineAsyncTaskThreadRunnable;` — Online async task runnable
- L117 _private member_ `TUniquePtr<FRunnableThread> OnlineAsyncTaskThread;` — Online async task thread
- L119 _private member_ `FGooglePlayGamesWrapper GooglePlayGamesWrapper;`
- L122 _private member_ `FOnlineIdentityGooglePlayPtr IdentityInterface;` — Interface to the online identity system
- L125 _private member_ `FOnlineStoreGooglePlayV2Ptr StoreV2Interface;` — Interface to the online catalog
- L128 _private member_ `FOnlinePurchaseGooglePlayPtr PurchaseInterface;` — Interface to the store purchasing
- L131 _private member_ `FOnlineLeaderboardsGooglePlayPtr LeaderboardsInterface;` — Interface to the online leaderboards
- L134 _private member_ `FOnlineAchievementsGooglePlayPtr AchievementsInterface;` — Interface to the online achievements
- L137 _private member_ `FOnlineExternalUIGooglePlayPtr ExternalUIInterface;` — Interface to the external UI services

#### Free symbols / members of external scopes

- L17 _typedef_ `typedef TSharedPtr<class FOnlineIdentityGooglePlay, ESPMode::ThreadSafe> FOnlineIdentityGooglePlayPtr;` — Forward declarations of all interface classes
- L18 _typedef_ `typedef TSharedPtr<class FOnlineStoreGooglePlayV2, ESPMode::ThreadSafe> FOnlineStoreGooglePlayV2Ptr;`
- L19 _typedef_ `typedef TSharedPtr<class FOnlinePurchaseGooglePlay, ESPMode::ThreadSafe> FOnlinePurchaseGooglePlayPtr;`
- L20 _typedef_ `typedef TSharedPtr<class FOnlineLeaderboardsGooglePlay, ESPMode::ThreadSafe> FOnlineLeaderboardsGooglePlayPtr;`
- L21 _typedef_ `typedef TSharedPtr<class FOnlineAchievementsGooglePlay, ESPMode::ThreadSafe> FOnlineAchievementsGooglePlayPtr;`
- L22 _typedef_ `typedef TSharedPtr<class FOnlineExternalUIGooglePlay, ESPMode::ThreadSafe> FOnlineExternalUIGooglePlayPtr;`
- L140 _typedef_ `typedef TSharedPtr<FOnlineSubsystemGooglePlay, ESPMode::ThreadSafe> FOnlineSubsystemGooglePlayPtr;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Public/OnlineSubsystemGooglePlayModule.h` (Public)


#### class `FOnlineSubsystemGooglePlayModule`  
`class FOnlineSubsystemGooglePlayModule : public IModuleInterface`  
_L12-35_
- inherits: `IModuleInterface`
- desc: Online subsystem module class (Google Play Implementation) Code related to the loading and handling of the Amdroid Google Play module.
- L17 _private member_ `class FOnlineFactoryGooglePlay* GooglePlayFactory;` — Class responsible for creating instance(s) of the subsystem
- L19 _private function_ `virtual ~FOnlineSubsystemGooglePlayModule()`
- L22 _private prototype_ `virtual void StartupModule() override;`
- L23 _private prototype_ `virtual void ShutdownModule() override;`
- L25 _private function_ `virtual bool SupportsDynamicReloading() override`
- L30 _private function_ `virtual bool SupportsAutomaticShutdown() override`

#### Free symbols / members of external scopes

- L37 _typedef_ `typedef TSharedPtr<FOnlineSubsystemGooglePlayModule> FOnlineSubsystemGooglePlayModulePtr;`

### `Plugins/Online/Android/OnlineSubsystemGooglePlay/Source/Public/OnlineSubsystemGooglePlayPackage.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define PACKAGE_SCOPE public`
- L12 _macro_ `#define PACKAGE_SCOPE protected`
