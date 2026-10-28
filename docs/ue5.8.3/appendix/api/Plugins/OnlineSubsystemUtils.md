# Plugins / OnlineSubsystemUtils

- module root: `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils`
- headers: 58; symbols: 1728
- symbol kinds: class=60, delegate=36, enum=17, enumerator=103, externvar=5, function=154, macro=31, member=493, namespace=31, prototype=770, struct=21, typedef=7
- PrivateDependencyModuleNames: AudioMixer, AudioMixerCore, DeveloperSettings, ImageCore, Json, OnlineServicesInterface, PacketHandler, SignalProcessing, Sockets, UnrealEd, Voice
- PublicDependencyModuleNames: Core, CoreOnline, CoreUObject, Engine, NetCore, OnlineSubsystem

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/AchievementBlueprintLibrary.h` (Public)


#### class `UAchievementBlueprintLibrary`  
`class UAchievementBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L14-40_
- reflection: `UCLASS(MinimalAPI, meta=(ScriptName="AchievementLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Library of synchronous achievement calls
- L26 _private prototype_ `static void GetCachedAchievementProgress(UObject* WorldContextObject, APlayerController* PlayerController, FName AchievementID, bool& bFoundID, float& Progress);` — `UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"), Category = "Online|Achievements")` — Gets the status of an achievement ID (you must call CacheAchievements first to cache them) @param AchievementID - The id of the achievement we are looking up @param bFoundID - If the ID was found in the cache (if not, none of the other values are meaningful) @param Progress - The progress amount of the achievement
- L39 _private prototype_ `static void GetCachedAchievementDescription(UObject* WorldContextObject, APlayerController* PlayerController, FName AchievementID, bool& bFoundID, FText& Title, FText& LockedDescription, FText& UnlockedDescription, bool& bHidden);` — `UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"), Category="Online|Achievements")` — Get the description for an achievement ID (you must call CacheAchievementDescriptions first to cache them) @param AchievementID - The id of the achievement we are searching for data of @param bFoundID - If the ID was found in the cache (if not, none of the other values are meaningful) @param Title - The localized title of the achievement @param LockedDescription - The localized locked description of the achievement @param UnlockedDescription - The localized unlocked description of the achievement @param bHidden - Whether the achievement is hidden

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/AchievementQueryCallbackProxy.h` (Public)


#### class `UAchievementQueryCallbackProxy`  
`class UAchievementQueryCallbackProxy : public UOnlineBlueprintCallProxyBase`  
_L11-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOnlineBlueprintCallProxyBase`
- L17 _private member_ `FEmptyOnlineDelegate OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful query
- L21 _private member_ `FEmptyOnlineDelegate OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful query
- L25 _private prototype_ `static UAchievementQueryCallbackProxy* CacheAchievements(UObject* WorldContextObject, class APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"), Category = "Online|Achievements")` — Fetches and caches achievement progress from the default online subsystem
- L29 _private prototype_ `static UAchievementQueryCallbackProxy* CacheAchievementDescriptions(UObject* WorldContextObject, class APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"), Category = "Online|Achievements")` — Fetches and caches achievement descriptions from the default online subsystem
- L32 _private prototype_ `virtual void Activate() override;` — UOnlineBlueprintCallProxyBase interface
- L37 _private prototype_ `void OnQueryCompleted(const FUniqueNetId& UserID, bool bSuccess);` — Internal callback when the achievement query completes, calls out to the public success/failure callbacks
- L41 _private member_ `TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;` — The player controller triggering things
- L44 _private member_ `bool bFetchDescriptions;` — Are we querying achievement progress or achievement descriptions?
- L47 _private member_ `UObject* WorldContextObject;` — The world context object in which this call is taking place

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/AchievementWriteCallbackProxy.h` (Public)


#### class `UAchievementWriteCallbackProxy`  
`class UAchievementWriteCallbackProxy : public UOnlineBlueprintCallProxyBase`  
_L14-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOnlineBlueprintCallProxyBase`
- L20 _private member_ `FAchievementWriteCompleteDelegate OnWriteSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful achievement write
- L24 _private member_ `FAchievementWriteCompleteDelegate OnWriteFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful achievement write
- L27 _private prototype_ `static UAchievementWriteCallbackProxy* WriteProgress(UObject* WorldContextObject, APlayerController* PlayerController, FString AchievementName, float Progress = 100.0f, int32 UserTag = 0);` — `UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"), Category="Online|Achievements")`
- L30 _private prototype_ `virtual void Activate() override;` — UOnlineBlueprintCallProxyBase interface
- L34 _private prototype_ `virtual void BeginDestroy() override;` — UObject interface
- L39 _private prototype_ `void OnAchievementWritten(const FUniqueNetId& UserID, bool bSuccess);` — Internal callback when the achievement is written, calls out to the public success/failure callbacks
- L43 _private member_ `TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;` — The player controller triggering things
- L46 _private member_ `FOnlineAchievementsWritePtr WriteObject;` — The achievements write object
- L49 _private member_ `FString AchievementName;` — The achievement name
- L52 _private member_ `float AchievementProgress;` — The amount of progress made towards the achievement
- L55 _private member_ `int32 UserTag;` — The specified user tag
- L58 _private member_ `UObject* WorldContextObject;` — The world context object in which this call is taking place

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAchievementWriteDelegate, FName, WrittenAchievementName, float, WrittenProgress, int32, WrittenUserTag);`
- L10 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAchievementWriteDelegate, FName, WrittenAchievementName, float, WrittenProgress, int32, WrittenUserTag);`
- L11 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAchievementWriteCompleteDelegate, FString, WrittenAchievementName, float, WrittenProgress, int32, WrittenUserTag);`
- L11 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAchievementWriteCompleteDelegate, FString, WrittenAchievementName, float, WrittenProgress, int32, WrittenUserTag);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/ConnectionCallbackProxy.h` (Public)


#### class `UConnectionCallbackProxy`  
`class UConnectionCallbackProxy : public UOnlineBlueprintCallProxyBase`  
_L16-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOnlineBlueprintCallProxyBase`
- L22 _private member_ `FOnlineConnectionResult OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful query
- L26 _private member_ `FOnlineConnectionResult OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful query
- L30 _private prototype_ `static UConnectionCallbackProxy* ConnectToService(UObject* WorldContextObject, class APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage="Please use Show External Login UI instead", BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"), Category = "Online|Achievements")` — Connects to an online service such as Google Play
- L33 _private prototype_ `virtual void Activate() override;` — UOnlineBlueprintCallProxyBase interface
- L38 _private prototype_ `void OnLoginCompleted(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);` — Internal callback when the achievement query completes, calls out to the public success/failure callbacks
- L42 _private member_ `TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;` — The player controller triggering things
- L45 _private member_ `FOnLoginCompleteDelegate OnLoginCompleteDelegate;` — Connection callback delegate
- L48 _private member_ `FDelegateHandle OnLoginCompleteDelegateHandle;` — OnLoginComplete delegate handle
- L51 _private member_ `UObject* WorldContextObject;` — The world context object in which this call is taking place

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnlineConnectionResult, int32, ErrorCode);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnlineConnectionResult, int32, ErrorCode);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/CreateSessionCallbackProxy.h` (Public)


#### class `UCreateSessionCallbackProxy`  
`class UCreateSessionCallbackProxy : public UOnlineBlueprintCallProxyBase`  
_L11-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOnlineBlueprintCallProxyBase`
- L17 _private member_ `FEmptyOnlineDelegate OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when the session was created successfully
- L21 _private member_ `FEmptyOnlineDelegate OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there was an error creating the session
- L25 _private prototype_ `static UCreateSessionCallbackProxy* CreateSession(UObject* WorldContextObject, class APlayerController* PlayerController, int32 PublicConnections, bool bUseLAN, bool bUseLobbiesIfAvailable = true);` — `UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"), Category = "Online|Session")` — Creates a session with the default online subsystem
- L28 _private prototype_ `virtual void Activate() override;` — UOnlineBlueprintCallProxyBase interface
- L33 _private prototype_ `void OnCreateCompleted(FName SessionName, bool bWasSuccessful);` — Internal callback when session creation completes, calls StartSession
- L36 _private prototype_ `void OnStartCompleted(FName SessionName, bool bWasSuccessful);` — Internal callback when session creation completes, calls StartSession
- L39 _private member_ `TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;` — The player controller triggering things
- L42 _private member_ `FOnCreateSessionCompleteDelegate CreateCompleteDelegate;` — The delegate executed by the online subsystem
- L45 _private member_ `FOnStartSessionCompleteDelegate StartCompleteDelegate;` — The delegate executed by the online subsystem
- L48 _private member_ `FDelegateHandle CreateCompleteDelegateHandle;` — Handles to the registered delegates above
- L49 _private member_ `FDelegateHandle StartCompleteDelegateHandle;`
- L52 _private member_ `int NumPublicConnections;` — Number of public connections
- L55 _private member_ `bool bUseLAN;` — Whether or not to search LAN
- L58 _private member_ `bool bUseLobbiesIfAvailable;` — Whether or not to use lobbies (as opposed to using a raw server list)
- L61 _private member_ `UObject* WorldContextObject;` — The world context object in which this call is taking place

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/DestroySessionCallbackProxy.h` (Public)


#### class `UDestroySessionCallbackProxy`  
`class UDestroySessionCallbackProxy : public UOnlineBlueprintCallProxyBase`  
_L11-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOnlineBlueprintCallProxyBase`
- L17 _private member_ `FEmptyOnlineDelegate OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful destroy
- L21 _private member_ `FEmptyOnlineDelegate OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful destroy
- L25 _private prototype_ `static UDestroySessionCallbackProxy* DestroySession(UObject* WorldContextObject, class APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"), Category = "Online|Session")` — Destroys a session previously created by the default online subsystem
- L28 _private prototype_ `virtual void Activate() override;` — UOnlineBlueprintCallProxyBase interface
- L33 _private prototype_ `void OnCompleted(FName SessionName, bool bWasSuccessful);` — Internal callback when the operation completes, calls out to the public success/failure callbacks
- L37 _private member_ `TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;` — The player controller triggering things
- L40 _private member_ `FOnDestroySessionCompleteDelegate Delegate;` — The delegate executed by the online subsystem
- L43 _private member_ `FDelegateHandle DelegateHandle;` — Handle to the registered OnDestroySessionComplete delegate
- L46 _private member_ `UObject* WorldContextObject;` — The world context object in which this call is taking place

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/EndMatchCallbackProxy.h` (Public)


#### class `UEndMatchCallbackProxy`  
`class UEndMatchCallbackProxy : public UOnlineBlueprintCallProxyBase`  
_L16-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOnlineBlueprintCallProxyBase`
- L20 _private prototype_ `virtual ~UEndMatchCallbackProxy();`
- L24 _private member_ `FEmptyOnlineDelegate OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when the match ends successfully
- L28 _private member_ `FEmptyOnlineDelegate OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when ending the match fails
- L32 _private prototype_ `static UEndMatchCallbackProxy* EndMatch(UObject* WorldContextObject, class APlayerController* PlayerController, TScriptInterface<ITurnBasedMatchInterface> MatchActor, FString MatchID, EMPMatchOutcome::Outcome LocalPlayerOutcome, EMPMatchOutcome::Outcome OtherPlayersOutcome);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Online|TurnBased")`
- L35 _private prototype_ `virtual void Activate() override;` — UOnlineBlueprintCallProxyBase interface
- L38 _private function_ `UTurnBasedMatchInterface* GetTurnBasedMatchInterfaceObject()`
- L40 _private prototype_ `void EndMatchDelegate(FString MatchID, bool Succeeded);`
- L44 _private member_ `TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;` — The player controller triggering things
- L47 _private member_ `UObject* WorldContextObject;` — The world context object in which this call is taking place
- L50 _private member_ `UTurnBasedMatchInterface* TurnBasedMatchInterface;` — TurnBasedMatchInterface object, used to set the match data after a match is found
- L53 _private member_ `FString MatchID;` — ID of the match to end
- L56 _private member_ `EMPMatchOutcome::Outcome LocalPlayerOutcome;` — Match outcome for the current player (win/loss/tie)
- L59 _private member_ `EMPMatchOutcome::Outcome OtherPlayersOutcome;` — Match outcome for all other players (win/loss/tie)

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace EMPMatchOutcome`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/EndTurnCallbackProxy.h` (Public)


#### class `UEndTurnCallbackProxy`  
`class UEndTurnCallbackProxy : public UOnlineBlueprintCallProxyBase`  
_L15-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOnlineBlueprintCallProxyBase`
- L19 _private prototype_ `virtual ~UEndTurnCallbackProxy();`
- L23 _private member_ `FEmptyOnlineDelegate OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful query
- L27 _private member_ `FEmptyOnlineDelegate OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful query
- L31 _private prototype_ `static UEndTurnCallbackProxy* EndTurn(UObject* WorldContextObject, class APlayerController* PlayerController, FString MatchID, TScriptInterface<ITurnBasedMatchInterface> TurnBasedMatchInterface);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Online|TurnBased")` — Ends the turn for the current player
- L34 _private prototype_ `virtual void Activate() override;` — UOnlineBlueprintCallProxyBase interface
- L37 _private prototype_ `void UploadMatchDataDelegate(FString MatchID, bool Succeeded);`
- L41 _private member_ `TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;` — The player controller triggering things
- L44 _private member_ `UObject* WorldContextObject;` — The world context object in which this call is taking place
- L47 _private member_ `FString MatchID;` — The MatchID of the active match
- L50 _private member_ `UTurnBasedMatchInterface* TurnBasedMatchInterface;` — Object that is inheriting from UTurnBasedMatchInterface. Replicated properties will be serialize into the platform specific match data object.

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/FindSessionsCallbackProxy.h` (Public)


#### struct `FBlueprintSessionResult`  
`struct FBlueprintSessionResult`  
_L12-17_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public member_ `FOnlineSessionSearchResult OnlineResult;`

#### class `UFindSessionsCallbackProxy`  
`class UFindSessionsCallbackProxy : public UOnlineBlueprintCallProxyBase`  
_L22-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOnlineBlueprintCallProxyBase`
- L28 _private member_ `FBlueprintFindSessionsResultDelegate OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful query
- L32 _private member_ `FBlueprintFindSessionsResultDelegate OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful query
- L36 _private prototype_ `static UFindSessionsCallbackProxy* FindSessions(UObject* WorldContextObject, class APlayerController* PlayerController, int32 MaxResults, bool bUseLAN, bool bUseLobbies);` — `UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"), Category = "Online|Session")` — Searches for advertised sessions with the default online subsystem
- L39 _private prototype_ `static int32 GetPingInMs(const FBlueprintSessionResult& Result);` — `UFUNCTION(BlueprintPure, Category = "Online|Session")`
- L42 _private prototype_ `static FString GetServerName(const FBlueprintSessionResult& Result);` — `UFUNCTION(BlueprintPure, Category = "Online|Session")`
- L45 _private prototype_ `static int32 GetCurrentPlayers(const FBlueprintSessionResult& Result);` — `UFUNCTION(BlueprintPure, Category = "Online|Session")`
- L48 _private prototype_ `static int32 GetMaxPlayers(const FBlueprintSessionResult& Result);` — `UFUNCTION(BlueprintPure, Category = "Online|Session")`
- L51 _private prototype_ `virtual void Activate() override;` — UOnlineBlueprintCallProxyBase interface
- L56 _private prototype_ `void OnCompleted(bool bSuccess);` — Internal callback when the session search completes, calls out to the public success/failure callbacks
- L60 _private member_ `TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;` — The player controller triggering things
- L63 _private member_ `FOnFindSessionsCompleteDelegate Delegate;` — The delegate executed by the online subsystem
- L66 _private member_ `FDelegateHandle DelegateHandle;` — Handle to the registered OnFindSessionsComplete delegate
- L69 _private member_ `TSharedPtr<FOnlineSessionSearch> SearchObject;` — Object to track search results
- L72 _private member_ `bool bUseLAN;` — Whether or not to search LAN
- L75 _private member_ `bool bUseLobbies;` — Whether or not to search for Lobbies instead of Sessions
- L78 _private member_ `int MaxResults;` — Maximum number of results to return
- L81 _private member_ `UObject* WorldContextObject;` — The world context object in which this call is taking place

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBlueprintFindSessionsResultDelegate, const TArray<FBlueprintSessionResult>&, Results);`
- L19 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBlueprintFindSessionsResultDelegate, const TArray<FBlueprintSessionResult>&, Results);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/FindTurnBasedMatchCallbackProxy.h` (Public)


#### class `FFindTurnBasedMatchCallbackProxyMatchmakerDelegate`  
`class FFindTurnBasedMatchCallbackProxyMatchmakerDelegate : public FTurnBasedMatchmakerDelegate, public TSharedFromThis<FTurnBasedMatchmakerDelegate>`  
_L18-34_
- inherits: `FTurnBasedMatchmakerDelegate,TSharedFromThis<FTurnBasedMatchmakerDelegate>`
- L22 _public prototype_ `FFindTurnBasedMatchCallbackProxyMatchmakerDelegate();`
- L23 _public prototype_ `virtual ~FFindTurnBasedMatchCallbackProxyMatchmakerDelegate();`
- L25 _public prototype_ `virtual void OnMatchmakerCancelled() override;`
- L26 _public prototype_ `virtual void OnMatchmakerFailed() override;`
- L27 _public prototype_ `virtual void OnMatchFound(FTurnBasedMatchRef Match) override;`
- L29 _public function_ `void SetFindTurnBasedMatchCallbackProxy(UFindTurnBasedMatchCallbackProxy* InFindTurnBasedMatchCallbackProxy)`
- L30 _public function_ `void SetTurnBasedInterface(IOnlineTurnBasedPtr InTurnBasedInterface)`
- L32 _private member_ `UFindTurnBasedMatchCallbackProxy* FindTurnBasedMatchCallbackProxy;`
- L33 _private member_ `IOnlineTurnBasedPtr TurnBasedInterface;`

#### class `UFindTurnBasedMatchCallbackProxy`  
`class UFindTurnBasedMatchCallbackProxy : public UOnlineBlueprintCallProxyBase`  
_L37-84_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOnlineBlueprintCallProxyBase`
- L41 _private prototype_ `virtual ~UFindTurnBasedMatchCallbackProxy();`
- L45 _private member_ `FOnlineTurnBasedMatchResult OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when matchmaking succeeded.
- L49 _private member_ `FOnlineTurnBasedMatchResult OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when matchmaking failed
- L53 _private prototype_ `static UFindTurnBasedMatchCallbackProxy* FindTurnBasedMatch(UObject* WorldContextObject, class APlayerController* PlayerController, TScriptInterface<ITurnBasedMatchInterface> MatchActor, int32 MinPlayers, int32 MaxPlayers, int32 PlayerGroup, bool ShowExistingMatches);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Online|TurnBased")` — Use the platform matchmaking service (like Game Center) to find a match.
- L56 _private prototype_ `virtual void Activate() override;` — UOnlineBlueprintCallProxyBase interface
- L59 _private function_ `UTurnBasedMatchInterface* GetTurnBasedMatchInterfaceObject()`
- L63 _private member_ `TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;` — The player controller triggering things
- L66 _private member_ `UObject* WorldContextObject;` — The world context object in which this call is taking place
- L69 _private member_ `UTurnBasedMatchInterface* TurnBasedMatchInterface;` — TurnBasedMatchInterface object, used to set the match data after a match is found
- L72 _private member_ `uint32 MinPlayers;` — Minimum number of players needed for the match if a match is created
- L75 _private member_ `uint32 MaxPlayers;` — Maximum number of players needed for the match if a match is created
- L78 _private member_ `uint32 PlayerGroup;` — Another matchmaking parameter that must be the same for players to matchmake together - for example, this could be the game mode (1 for deathmatch, 2 for capture the flag, etc.)
- L81 _private member_ `bool ShowExistingMatches;` — Show matches that the player is already a part of in the matchmaking interface
- L83 _private member_ `TSharedPtr<FFindTurnBasedMatchCallbackProxyMatchmakerDelegate, ESPMode::ThreadSafe> Delegate;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnlineTurnBasedMatchResult, FString, MatchID);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnlineTurnBasedMatchResult, FString, MatchID);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/InAppPurchaseCallbackProxy2.h` (Public)


#### struct `FInAppPurchaseProductInfo2`  
`struct FInAppPurchaseProductInfo2`  
_L13-64_
- reflection: `USTRUCT(BlueprintType)`
- desc: Micro-transaction purchase information
- L19 _public member_ `FString Identifier;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — The unique product identifier
- L23 _public member_ `FString TransactionIdentifier;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — the unique transaction identifier
- L27 _public member_ `FString DisplayName;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — The localized display name
- L31 _public member_ `FString DisplayDescription;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — The localized display description name
- L35 _public member_ `FString DisplayPrice;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — The localized display price name
- L39 _public member_ `float RawPrice = 0.0f;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Raw price without currency code and symbol
- L43 _public member_ `FString CurrencyCode;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — The localized currency code of the price
- L47 _public member_ `FString CurrencySymbol;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — The localized currency symbol of the price
- L51 _public member_ `FString DecimalSeparator;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — The localized decimal separator used in the price
- L55 _public member_ `FString GroupingSeparator;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — The localized grouping separator of the price
- L59 _public member_ `FString ReceiptData;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Opaque receipt data for the transaction
- L63 _public member_ `TMap<FString, FString> DynamicFields;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Dynamic fields from raw Json data.

#### class `UInAppPurchaseCallbackProxy2`  
`class UInAppPurchaseCallbackProxy2 : public UObject`  
_L69-136_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L75 _private member_ `FInAppPurchaseResult2 OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful In-App Purchase transaction
- L79 _private member_ `FInAppPurchaseResult2 OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful In-App Purchase transaction
- L83 _private prototype_ `static UInAppPurchaseCallbackProxy2* CreateProxyObjectForInAppPurchase(class APlayerController* PlayerController, const FInAppPurchaseProductRequest2& ProductRequest);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Make an In-App Purchase v2", DeprecatedFunction, DeprecationMessage = "Please use 'Start an In-App Purchase' and remember to pass the output receipts to 'Finalize In-App Purchase Transaction' after being validated and processed"), Category = "Online|InAppPurchase")` — Kicks off a transaction for the provided product identifier
- L86 _private prototype_ `static UInAppPurchaseCallbackProxy2* CreateProxyObjectForInAppPurchaseUnprocessedPurchases(class APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Process any New Unprocessed Purchases v2", DeprecatedFunction, DeprecationMessage = "Please use 'Get known In-App Receipts' and remember to pass the output receipts to 'Finalize In-App Purchase Transaction' after being validated and processed"), Category = "Online|InAppPurchase")`
- L89 _private prototype_ `static UInAppPurchaseCallbackProxy2* CreateProxyObjectForInAppPurchaseQueryOwned(class APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Query for Owned Purchases", DeprecatedFunction, DeprecationMessage = "Please use 'Query for Owned In-App Products' and remember to pass the output receipts to 'Finalize In-App Purchase Transaction' after being validated and processed"), Category = "Online|InAppPurchase")`
- L94 _public prototype_ `virtual void BeginDestroy() override;`
- L100 _private prototype_ `void OnInAppPurchaseComplete_Delayed();` — Called by the InAppPurchase system when the transaction has finished
- L101 _private prototype_ `void OnCheckoutComplete(const FOnlineError& Result, const TSharedRef<FPurchaseReceipt>& Receipt);`
- L102 _private prototype_ `void OnPurchaseComplete();`
- L103 _private prototype_ `void OnQueryReceiptsComplete(const FOnlineError& Result);`
- L106 _private prototype_ `void Trigger(class APlayerController* PlayerController, const FInAppPurchaseProductRequest2& ProductRequest);` — Triggers the In-App Purchase Transaction for the specifed user; the Purchase Request object must already be set up
- L108 _private prototype_ `void TriggerGetUnprocessedPurchases(APlayerController* PlayerController);` — Triggers the In-App Purchase processing for unprocessed receipts
- L110 _private prototype_ `void TriggerGetOwnedPurchases(APlayerController* PlayerController);` — Triggers the In-App Purchase processing for unprocessed receipts
- L115 _private member_ `FOnPurchaseCheckoutComplete InAppPurchaseCompleteDelegate;` — Delegate called when a InAppPurchase has been successfully read
- L118 _private member_ `FDelegateHandle InAppPurchaseCompleteDelegateHandle;` — Handle to the registered InAppPurchaseCompleteDelegate
- L121 _private member_ `bool bFailedToEvenSubmit;` — Did we fail immediately?
- L124 _private member_ `TWeakObjectPtr<UWorld> WorldPtr;` — Pointer to the world, needed to delay the results slightly
- L127 _private member_ `bool bWasSuccessful = false;` — Did the purchase succeed?
- L129 _private member_ `TArray<FInAppPurchaseReceiptInfo2> SavedReceipts;`
- L131 _private member_ `FUniqueNetIdPtr PurchasingPlayer;`
- L133 _private member_ `IOnlinePurchasePtr PurchaseInterface;`
- L135 _private member_ `EInAppPurchaseStatus SavedPurchaseStatus;`

#### Free symbols / members of external scopes

- L66 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInAppPurchaseResult2, EInAppPurchaseStatus, PurchaseStatus, const TArray<FInAppPurchaseReceiptInfo2>&, InAppPurchaseReceipts);`
- L66 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInAppPurchaseResult2, EInAppPurchaseStatus, PurchaseStatus, const TArray<FInAppPurchaseReceiptInfo2>&, InAppPurchaseReceipts);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/InAppPurchaseCheckoutCallbackProxy.h` (Public)


#### class `UInAppPurchaseCheckoutCallbackProxy`  
`class UInAppPurchaseCheckoutCallbackProxy : public UObject`  
_L13-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L19 _private member_ `FOnlineProxyInAppCheckoutResult OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful In-App Purchase transaction
- L23 _private member_ `FOnlineProxyInAppCheckoutResult OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful In-App Purchase transaction
- L27 _private prototype_ `static UInAppPurchaseCheckoutCallbackProxy* CreateProxyObjectForInAppPurchaseCheckout(class APlayerController* PlayerController, const FInAppPurchaseProductRequest2& ProductRequest);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Start an In-App Purchase"), Category = "Online|InAppPurchase")` — Kicks off a transaction for the provided product identifier
- L32 _private prototype_ `void OnCheckoutComplete(const FOnlineError& Result, const TSharedRef<FPurchaseReceipt>& Receipt);` — Called by the InAppPurchase system when the transaction has finished
- L33 _private prototype_ `void OnPurchaseComplete();`
- L36 _private prototype_ `void TriggerCheckout(class APlayerController* PlayerController, const FInAppPurchaseProductRequest2& ProductRequest);` — Triggers the In-App Purchase Transaction for the specifed user; the Purchase Request object must already be set up
- L38 _private prototype_ `void ClearPreviousResult();`
- L41 _private member_ `TWeakObjectPtr<UWorld> WorldPtr;` — Pointer to the world, needed to delay the results slightly
- L44 _private member_ `TOptional<FInAppPurchaseReceiptInfo2> SavedReceipt;` — Receipt in case of a succsessful purchase
- L47 _private member_ `EInAppPurchaseStatus SavedPurchaseStatus = EInAppPurchaseStatus::Failed;` — Received purchase status

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlineProxyInAppCheckoutResult, EInAppPurchaseStatus, PurchaseStatus, const FInAppPurchaseReceiptInfo2&, InAppPurchaseReceipt);`
- L10 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlineProxyInAppCheckoutResult, EInAppPurchaseStatus, PurchaseStatus, const FInAppPurchaseReceiptInfo2&, InAppPurchaseReceipt);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/InAppPurchaseDataTypes.h` (Public)


#### struct `FInAppPurchaseProductRequest2`  
`struct FInAppPurchaseProductRequest2`  
_L13-24_
- reflection: `USTRUCT(BlueprintType)`
- desc: Micro-transaction request information
- L19 _public member_ `FString ProductIdentifier;` — `UPROPERTY(BlueprintReadWrite, Category = ProductInfo)` — The unique product identifier that matches the one from your targeted store.
- L23 _public member_ `bool bIsConsumable = false;` — `UPROPERTY(BlueprintReadWrite, Category = ProductInfo)` — Flag to determine whether this is a consumable purchase, or not.

#### enum `EInAppPurchaseStatus`  
`enum class EInAppPurchaseStatus : uint8`  
_L30-43_
- reflection: `UENUM(BlueprintType)`
- desc: State of a purchase transaction
- L32 _public enumerator_ `Invalid = 0 UMETA(DisplayName = "Invalid")`
- L34 _public enumerator_ `Failed UMETA(DisplayName = "Failed")` — purchase completed but failed
- L36 _public enumerator_ `Deferred UMETA(DisplayName = "Deferred")` — purchase has been deferred (neither failed nor completed)
- L38 _public enumerator_ `Canceled UMETA(DisplayName = "Canceled")` — purchase canceled by user
- L40 _public enumerator_ `Purchased UMETA(DisplayName = "Purchased")` — purchase succeeded
- L42 _public enumerator_ `Restored UMETA(DisplayName = "Restored")` — restore succeeded

#### struct `FInAppPurchaseReceiptInfo2`  
`struct FInAppPurchaseReceiptInfo2`  
_L51-70_
- reflection: `USTRUCT(BlueprintType)`
- desc: Micro-transaction purchase information
- L57 _public member_ `FString ItemName;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — The item name
- L61 _public member_ `FString ItemId;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — The unique product identifier
- L65 _public member_ `FString ValidationInfo;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — the purchase validation information
- L69 _public member_ `FString TransactionIdentifier;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — the unique transaction identifier

#### Free symbols / members of external scopes

- L45 _prototype_ `EInAppPurchaseStatus PurchaseStatusFromOnlineError(const FOnlineError& OnlineError);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/InAppPurchaseFinalizeProxy.h` (Public)


#### class `UInAppPurchaseFinalizeProxy`  
`class UInAppPurchaseFinalizeProxy : public UObject`  
_L10-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L16 _private prototype_ `static UInAppPurchaseFinalizeProxy* CreateProxyObjectForInAppPurchaseFinalize(const FInAppPurchaseReceiptInfo2& InAppPurchaseReceipt, class APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName="Finalize In-App Purchase Transaction"), Category="Online|InAppPurchase")` — Finalizes a transaction for the provided transaction identifier
- L21 _private prototype_ `void Trigger(const FInAppPurchaseReceiptInfo2& InAppPurchaseReceipt, class APlayerController* PlayerController);` — Triggers the In-App Purchase Finalize Transaction for the specifed user

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/InAppPurchaseQueryCallbackProxy2.h` (Public)


#### enum `EOnlineProxyStoreOfferDiscountType`  
`enum class EOnlineProxyStoreOfferDiscountType : uint8`  
_L8-18_
- reflection: `UENUM(BlueprintType)`
- L11 _public enumerator_ `NotOnSale = 0 UMETA(DisplayName = "NotOnSale")` — Offer isn't on sale
- L13 _public enumerator_ `Percentage UMETA(DisplayName = "Percentage")` — Offer price should be displayed as a percentage of regular price
- L15 _public enumerator_ `DiscountAmount UMETA(DisplayName = "DiscountAmount")` — Offer price should be displayed as an amount off regular price
- L17 _public enumerator_ `PayAmount UMETA(DisplayName = "PayAmount")` — Offer price should be displayed as a new price

#### struct `FOnlineProxyStoreOffer`  
`struct FOnlineProxyStoreOffer`  
_L24-71_
- reflection: `USTRUCT(BlueprintType)`
- desc: Offer entry for display from online store
- L30 _public member_ `FString OfferId;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Unique offer identifier
- L34 _public member_ `FText Title;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Title for display
- L37 _public member_ `FText Description;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Short description for display
- L40 _public member_ `FText LongDescription;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Full description for display
- L44 _public member_ `FText RegularPriceText;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Regular non-sale price as text for display
- L47 _public member_ `int32 RegularPrice = 0;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Regular non-sale price in numeric form for comparison/sorting
- L51 _public member_ `FText PriceText;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Final-Pricing (Post-Sales/Discounts) as text for display
- L54 _public member_ `int32 NumericPrice = 0;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Final-Price (Post-Sales/Discounts) in numeric form for comparison/sorting
- L58 _public member_ `FString CurrencyCode;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Price currency code
- L62 _public member_ `FDateTime ReleaseDate = FDateTime::MinValue();` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Date the offer was released
- L65 _public member_ `FDateTime ExpirationDate = FDateTime::MinValue();` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Date this information is no longer valid (maybe due to sale ending, etc)
- L68 _public member_ `EOnlineProxyStoreOfferDiscountType DiscountType = EOnlineProxyStoreOfferDiscountType::NotOnSale;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — Type of discount currently running on this offer (if any)
- L70 _public member_ `TMap<FString, FString> DynamicFields;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)`

#### class `UInAppPurchaseQueryCallbackProxy2`  
`class UInAppPurchaseQueryCallbackProxy2 : public UObject`  
_L76-114_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L82 _private member_ `FInAppPurchaseQuery2Result OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful InAppPurchase query
- L86 _private member_ `FInAppPurchaseQuery2Result OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful InAppPurchase query
- L90 _private prototype_ `static UInAppPurchaseQueryCallbackProxy2* CreateProxyObjectForInAppPurchaseQuery(class APlayerController* PlayerController, const TArray<FString>& ProductIdentifiers);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName="Read In App Purchase Information2"), Category="Online|InAppPurchase")` — Queries a InAppPurchase for an integer value
- L94 _public prototype_ `virtual void BeginDestroy() override;`
- L99 _private prototype_ `void OnInAppPurchaseRead_Delayed();` — Called by the InAppPurchase system when the read is finished
- L100 _private prototype_ `void OnInAppPurchaseRead(bool bWasSuccessful, const TArray<FUniqueOfferId>& OfferIds, const FString& Error);`
- L102 _private prototype_ `void CreateProxyProductInformation(TArray<FOnlineStoreOfferRef>& SourceArray, TArray<FOnlineProxyStoreOffer>& TargetArray);`
- L105 _private prototype_ `void TriggerQuery(class APlayerController* PlayerController, const TArray<FString>& ProductIdentifiers);` — Triggers the query for a specifed user
- L109 _private member_ `TWeakObjectPtr<UWorld> WorldPtr;` — Pointer to the world, needed to delay the results slightly
- L112 _private member_ `bool bSavedWasSuccessful;` — Did the read succeed?
- L113 _private member_ `TArray<FOnlineProxyStoreOffer> SavedProductInformation;`

#### Free symbols / members of external scopes

- L73 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInAppPurchaseQuery2Result, const TArray<FOnlineProxyStoreOffer>&, InAppOfferInformation);`
- L73 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInAppPurchaseQuery2Result, const TArray<FOnlineProxyStoreOffer>&, InAppOfferInformation);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/InAppPurchaseReceiptsCallbackProxy.h` (Public)


#### class `UInAppPurchaseReceiptsCallbackProxy`  
`class UInAppPurchaseReceiptsCallbackProxy : public UObject`  
_L12-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L18 _private member_ `FOnlineProxyInAppReceiptsResult OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful In-App Purchase transaction
- L22 _private member_ `FOnlineProxyInAppReceiptsResult OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful In-App Purchase transaction
- L25 _private prototype_ `static UInAppPurchaseReceiptsCallbackProxy* CreateProxyObjectForInAppPurchaseGetKnownReceipts(class APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get known In-App Receipts"), Category = "Online|InAppPurchase")`
- L28 _private prototype_ `static UInAppPurchaseReceiptsCallbackProxy* CreateProxyObjectForInAppPurchaseQueryOwnedProducts(class APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Query for Owned In-App Products"), Category = "Online|InAppPurchase")`
- L31 _private prototype_ `static UInAppPurchaseReceiptsCallbackProxy* CreateProxyObjectForInAppPurchaseRestoreOwnedProducts(class APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Restore Owned In-App Products"), Category = "Online|InAppPurchase")`
- L33 _private prototype_ `void ClearPreviousResult();`
- L36 _private prototype_ `void OnQueryComplete();` — Called by the InAppPurchase system when the transaction has finished
- L37 _private prototype_ `void OnQueryReceiptsComplete(const FOnlineError& Resul, FUniqueNetIdWeakPtr PurchasingPlayerWeak);`
- L40 _private prototype_ `void TriggerGetKnownReceipts(APlayerController* PlayerController);` — Triggers the In-App Purchase processing for unprocessed receipts
- L42 _private prototype_ `void TriggerGetOwnedProducts(APlayerController* PlayerController, bool bRestorePurchases);` — Triggers the In-App Purchase processing for unprocessed receipts
- L47 _private member_ `FOnlineProxyInAppReceiptsResult InAppPurchaseCompleteDelegate;` — Delegate called when a InAppPurchase has been successfully read
- L50 _private member_ `FDelegateHandle InAppPurchaseCompleteDelegateHandle;` — Handle to the registered InAppPurchaseCompleteDelegate
- L53 _private member_ `TWeakObjectPtr<UWorld> WorldPtr;` — Pointer to the world, needed to delay the results slightly
- L56 _private member_ `bool bWasSuccessful = false;` — Did the purchase succeed?
- L58 _private member_ `TArray<FInAppPurchaseReceiptInfo2> SavedReceipts;`
- L60 _private member_ `EInAppPurchaseStatus SavedPurchaseStatus = EInAppPurchaseStatus::Failed;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlineProxyInAppReceiptsResult, EInAppPurchaseStatus, PurchaseStatus, const TArray<FInAppPurchaseReceiptInfo2>&, InAppPurchaseReceipts);`
- L9 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlineProxyInAppReceiptsResult, EInAppPurchaseStatus, PurchaseStatus, const TArray<FInAppPurchaseReceiptInfo2>&, InAppPurchaseReceipts);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/InAppPurchaseRestoreCallbackProxy2.h` (Public)


#### struct `FInAppPurchaseRestoreInfo2`  
`struct FInAppPurchaseRestoreInfo2`  
_L16-31_
- reflection: `USTRUCT(BlueprintType)`
- desc: Micro-transaction purchase information
- L22 _public member_ `FString ItemName;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — The item name
- L26 _public member_ `FString ItemId;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — The unique product identifier
- L30 _public member_ `FString ValidationInfo;` — `UPROPERTY(BlueprintReadOnly, Category = ProductInfo)` — the unique transaction identifier

#### class `UInAppPurchaseRestoreCallbackProxy2`  
`class UInAppPurchaseRestoreCallbackProxy2 : public UObject`  
_L36-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L42 _private member_ `FInAppPurchaseRestoreResult2 OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful In-App Purchase transaction
- L46 _private member_ `FInAppPurchaseRestoreResult2 OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful In-App Purchase transaction
- L50 _private prototype_ `static UInAppPurchaseRestoreCallbackProxy2* CreateProxyObjectForInAppPurchaseRestore(const TArray<FInAppPurchaseProductRequest2>& ConsumableProductFlags, class APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName="Restore In-App Purchases2", DeprecatedFunction, DeprecationMessage = "Please use 'Restore Owned In-App Products' and remember to pass the output receipts to 'Finalize In-App Purchase Transaction' after being validated and processed"), Category="Online|InAppPurchase")` — Kicks off a transaction for the provided product identifier
- L55 _public prototype_ `virtual void BeginDestroy() override;`
- L61 _private prototype_ `void OnInAppPurchaseRestoreComplete_Delayed();` — Called by the InAppPurchase system when the transaction has finished
- L62 _private prototype_ `void OnInAppPurchaseRestoreComplete();`
- L64 _private prototype_ `void OnQueryReceiptsComplete(const FOnlineError& Result);`
- L67 _private prototype_ `void Trigger(const TArray<FInAppPurchaseProductRequest2>& ConsumableProductFlags, class APlayerController* PlayerController);` — Triggers the In-App Purchase Restore Transaction for the specifed user
- L71 _private member_ `bool bWasSuccessful;`
- L73 _private member_ `TWeakObjectPtr<UWorld> WorldPtr;` — Pointer to the world, needed to delay the results slightly
- L75 _private member_ `TArray<FInAppPurchaseRestoreInfo2> SavedReceipts;`
- L77 _private member_ `IOnlinePurchasePtr PurchaseInterface;`
- L79 _private member_ `FUniqueNetIdRepl PurchasingPlayer;`
- L81 _private member_ `EInAppPurchaseStatus SavedPurchaseStatus;`

#### Free symbols / members of external scopes

- L33 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInAppPurchaseRestoreResult2, EInAppPurchaseStatus, PurchaseStatus, const TArray<FInAppPurchaseRestoreInfo2>&, InAppPurchaseRestoreInfo);`
- L33 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInAppPurchaseRestoreResult2, EInAppPurchaseStatus, PurchaseStatus, const TArray<FInAppPurchaseRestoreInfo2>&, InAppPurchaseRestoreInfo);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/IpConnection.h` (Public)


#### class `UIpConnection`  
`class UIpConnection : public UNetConnection`  
_L26-153_
- reflection: `UCLASS(MinimalAPI, transient, config=Engine)`
- inherits: `UNetConnection`
- L35 _public prototype_ `virtual void InitBase(UNetDriver* InDriver, class FSocket* InSocket, const FURL& InURL, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`
- L36 _public prototype_ `virtual void InitRemoteConnection(UNetDriver* InDriver, class FSocket* InSocket, const FURL& InURL, const class FInternetAddr& InRemoteAddr, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`
- L37 _public prototype_ `virtual void InitLocalConnection(UNetDriver* InDriver, class FSocket* InSocket, const FURL& InURL, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`
- L38 _public prototype_ `virtual void LowLevelSend(void* Data, int32 CountBits, FOutPacketTraits& Traits) override;`
- L39 _public prototype_ `FString LowLevelGetRemoteAddress(bool bAppendPort=false) override;`
- L40 _public prototype_ `FString LowLevelDescribe() override;`
- L41 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L42 _public prototype_ `virtual void CleanUp() override;`
- L43 _public prototype_ `virtual void ReceivedRawPacket(void* Data, int32 Count) override;`
- L44 _public prototype_ `virtual float GetTimeoutValue() override;`
- L51 _public prototype_ `void WaitForSendTasks();` — If CVarNetIpConnectionUseSendTasks is true, blocks until there are no outstanding send tasks. Since these tasks need to access the socket, this is called before the net driver closes the socket.
- L58 _public function_ `FSocket* GetSocket() const` — Gets the cached socket for this connection. @return	The cached socket for this connection
- L75 _private member_ `FCriticalSection SocketSendResultsCriticalSection;` — Critical section to protect SocketSendResults
- L78 _private member_ `TArray<FSocketSendResult> SocketSendResults;` — Socket SendTo results from send tasks if net.IpConnectionUseSendTasks is true
- L84 _private member_ `FGraphEventRef LastSendTask;` — If net.IpConnectionUseSendTasks is true, reference to the last send task used as a prerequisite for the next send task. Also, CleanUp() blocks until this task is complete.
- L87 _private member_ `TSharedPtr<FSocket> SocketPrivate;` — The socket used for communication (typically shared between NetConnection's, Net Address Resolution, and the NetDriver)
- L90 _private member_ `TArray<TSharedPtr<FSocket>> DeferredCleanupSockets;` — List of previously active sockets for this connection, whose cleanup is deferred for multithreaded safety and to prevent remote ICMP errors
- L93 _private member_ `double DeferredCleanupTimeCheck = 0.0;` — The time at which a socket was last queued for deferred cleanup
- L96 _private member_ `std::atomic<int32> DeferredCleanupReadyCount = 0;` — The number of 'DeferredCleanupSockets' entries ready for cleanup (may be set by async send tasks)
- L100 _private member_ `float SocketErrorDisconnectDelay;` — `UPROPERTY(Config)` — Instead of disconnecting immediately on a socket error, wait for some time to see if we can recover. Specified in Seconds.
- L103 _private member_ `double SocketError_SendDelayStartTime;` — Cached time of the first send socket error that will be used to compute disconnect delay.
- L106 _private member_ `double SocketError_RecvDelayStartTime;` — Cached time of the first recv socket error that will be used to compute disconnect delay.
- L110 _private member_ `int32 InitialConnectSocketSendCount = 0;` — The number of socket-level sends that have occurred during initial connect
- L113 _private member_ `double InitialConnectLastLogTime = 0.0;` — The last time initial connect diagnostics put out a log
- L116 _private member_ `int32 InitialConnectLastLogSocketSendCount = 0;` — The value of 'InitialConnectSocketSendCount' the last time there was an initial connect diagnostic log
- L121 _private prototype_ `void SendToRemote(uint8* Data, int32 CountBits, FOutPacketTraits& Traits);` — Performs the work of LowLevelSend once we have confirmed that we want to send data to remote.
- L124 _private prototype_ `void SetSocket_Local(const TSharedPtr<FSocket>& InSocket);` — Sets the local socket pointer, and safely cleans up any references to old sockets
- L127 _private prototype_ `void SafeDeferredSocketCleanup(const TSharedPtr<FSocket>& InSocket);` — Safe/non-blocking cleanup of a shared socket, which may be in use by async sends, or may be at risk of triggering ICMP unreachable errors
- L130 _private prototype_ `void HandleSocketSendResult(const FSocketSendResult& Result, ISocketSubsystem* SocketSubsystem);` — Handles any SendTo errors on the game thread.
- L133 _private prototype_ `void HandleSocketRecvError(class UNetDriver* NetDriver, const FString& ErrorString);` — Notifies us that we've encountered an error while receiving a packet.
- L136 _private member_ `TPimplPtr<UE::Net::Private::FNetConnectionAddressResolution> Resolver;` — NetDriver level early address resolution (may pass work on to NetConnection level address resolution)
- L139 _private prototype_ `bool TryConsumeAddressResolution(const TCHAR* LogSuffix = TEXT(""));` — If address resolution has results ready, assigns the resolved socket and RemoteAddr. Returns true if socket was assigned.
- L145 _protected prototype_ `void DisableAddressResolution();` — Disables address resolution by pushing the disabled flag into the status field.
- L152 _protected prototype_ `virtual void HandleConnectionTimeout(const FString& ErrorStr) override;` — Handles a NetConnection timeout. Overridden in order to handle parsing multiple GAI results during resolution. @param ErrorStr A string containing the current error message for either usage or writing into.

#### struct `UIpConnection::FSocketSendResult`  
`struct FSocketSendResult`  
_L68-72_
- desc: Struct to hold the result of a socket SendTo call. If net.IpConnectionUseSendTasks is true, these are communicated back to the game thread via SocketSendResults.
- L70 _public member_ `int32 BytesSent = 0;`
- L71 _public member_ `ESocketErrors Error = SE_NO_ERROR;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Net` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::Net`)

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/IpNetDriver.h` (Public)


#### enum `UE::Net::ERecreateSocketResult`  
`enum class ERecreateSocketResult : uint8`  
_L45-52_
- desc: Results for UIpNetDriver::RecreateSocket
- L47 _public enumerator_ `NoAction` — No action taken - this is either a replay, called on the server, or the NetDriver doesn't support socket recreation
- L48 _public enumerator_ `NotReady` — Net Address Resolution is in the middle of resolving, so no socket recreation can take place
- L49 _public enumerator_ `AlreadyInProgress` — Socket recreation is already in progress
- L50 _public enumerator_ `BeganRecreate` — Socket recreation was successfully kicked off
- L51 _public enumerator_ `Error` — There was an error

#### class `UIpNetDriver`  
`class UIpNetDriver : public UNetDriver`  
_L65-467_
- reflection: `UCLASS(MinimalAPI, transient, config=Engine)`
- inherits: `UNetDriver`
- L74 _public member_ `uint32 LogPortUnreach:1;` — `UPROPERTY(Config)` — Should port unreachable messages be logged
- L78 _public member_ `uint32 AllowPlayerPortUnreach:1;` — `UPROPERTY(Config)` — Does the game allow clients to remain after receiving ICMP port unreachable errors (handles flakey connections)
- L82 _public member_ `uint32 bExitOnBindFailure:1;` — `UPROPERTY(Config)` — Whether to exit if binding a port failed.
- L86 _public member_ `uint32 MaxPortCountToTry;` — `UPROPERTY(Config)` — Number of ports which will be tried if current one is not available for binding (i.e. if told to bind to port N, will try from N to N+MaxPortCountToTry inclusive)
- L89 _public member_ `float PauseReceiveEnd;` — If pausing socket receives, the time at which this should end
- L92 _public prototype_ `UIpNetDriver(const FObjectInitializer& ObjectInitializer);` — Base constructor
- L95 _public prototype_ `virtual bool IsAvailable() const override;`
- L96 _public prototype_ `virtual bool InitBase(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL, bool bReuseAddressAndPort, FString& Error) override;`
- L97 _public prototype_ `virtual bool InitConnect( FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error ) override;`
- L98 _public prototype_ `virtual bool InitListen( FNetworkNotify* InNotify, FURL& LocalURL, bool bReuseAddressAndPort, FString& Error ) override;`
- L99 _public prototype_ `virtual void TickDispatch( float DeltaTime ) override;`
- L100 _public prototype_ `virtual void LowLevelSend(TSharedPtr<const FInternetAddr> Address, void* Data, int32 CountBits, FOutPacketTraits& Traits) override;`
- L101 _public prototype_ `virtual FString LowLevelGetNetworkNumber() override;`
- L102 _public prototype_ `virtual void LowLevelDestroy() override;`
- L103 _public prototype_ `virtual class ISocketSubsystem* GetSocketSubsystem() override;`
- L104 _public function_ `virtual bool IsNetResourceValid(void) override`
- L118 _private prototype_ `UNetConnection* ProcessConnectionlessPacket(FReceivedPacketView& PacketRef, const FPacketBufferView& WorkingBuffer);` — Process packets not associated with a NetConnection, performing handshaking and NetConnection creation or remapping as necessary. @param PacketRef			A view of the received packet (may output a new packet view, possibly using WorkingBuffer) @param WorkingBuffer		A buffer for storing processed packet data (may be the buffer the input ReceivedPacketRef points to) @return					If a new NetConnection is created, returns the net connection
- L121 _private prototype_ `void ClearSockets();` — Clears all references to sockets held by this net driver.
- L132 _public prototype_ `virtual FSocket* GetSocket();` — Returns the current FSocket to be used with this NetDriver. This is useful in the cases of resolution as it will always point to the Socket that's currently being used with the current resolution attempt. @return a pointer to the socket to use.
- L140 _public prototype_ `void SetSocketAndLocalAddress(const TSharedPtr<FSocket>& SharedSocket);` — Set the current NetDriver's Socket/LocalAddr to the given socket (typically after Net Address Resolution). This will automatically pass the socket back through all NetConnection's, and trigger safe/deferred cleanup of the old socket. @param NewSocket	The socket pointer to set this NetDriver's socket to
- L149 _public prototype_ `virtual int GetClientPort();` — Returns the port number to use when a client is creating a socket. Platforms that can't use the default of 0 (system-selected port) may override this function. @return The port number to use for client sockets. Base implementation returns 0.
- L161 _public prototype_ `UE::Net::ERecreateSocketResult RecreateSocket(int32 OverridePort = INDEX_NONE);` — Creates a new Socket for the NetDriver/NetConnection's, based on the address/binding of the existing socket, with a new ephemeral port. Used to attempt recovery for 'half-broken' connections, where (for whatever reason) only one side of the connection is receiving packets. Also usable to test the 'restart handshake' feature, using the 'net RecreateSocket' command. @param OverridePort		optional port number to use with the new socket, otherwise falls back to GetClientPort() @return	Returns the action taken (e.g. successfully kicked off recreation, or whether this failed or is already in progress etc.)
- L164 _public function_ `double GetLastRecreateSocketTime() const` — Returns the last time socket recreation was kicked off or completed
- L176 _protected prototype_ `virtual FUniqueSocket CreateSocketForProtocol(const FName& ProtocolType);` — Creates a socket set up for communication using the given protocol. This allows for explicit creation instead of inferring type for you. @param ProtocolType	an FName that represents the protocol to allocate the new socket under. Typically set to None or a value in FNetworkProtocolTypes @return				an FSocket if creation succeeded, nullptr if creation failed.
- L190 _protected prototype_ `virtual FUniqueSocket CreateAndBindSocket(TSharedRef<FInternetAddr> BindAddr, int32 Port, bool bReuseAddressAndPort, int32 DesiredRecvSize, int32 DesiredSendSize, FString& Error);` — Creates, initializes and binds a socket using the given bind address information. @param BindAddr				the address to bind the new socket to, will also create the socket using the address protocol using CreateSocketForProtocol @param Port					the port number to use with the given bind address. @param bReuseAddressAndPort	if true, will set the socket to be bound even if the address is in use @param DesiredRecvSize		the max size of the recv buffer for the socket @param DesiredSendSize		the max size of the sending buffer for the socket @param Error					a string reference that will be populated with any error messages should an error occur @return if the socket could be created and bound with all the appropriate options, a pointer to the new socket is given, otherwise null
- L194 _protected function_ `void SetSupportsRecreateSocket(bool bInSupportsRecreateSocket)` — Called by NetDriver subclasses, to specify whether or not they support recreating the active socket
- L202 _public prototype_ `virtual bool Exec( UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar=*GLog ) override;`
- L209 _public prototype_ `bool HandleSocketsCommand(const TCHAR* Cmd, FOutputDevice& Ar, UWorld* InWorld);`
- L210 _public prototype_ `bool HandlePauseReceiveCommand(const TCHAR* Cmd, FOutputDevice& Ar, UWorld* InWorld);`
- L211 _public prototype_ `bool HandleRecreateSocketCommand(const TCHAR* Cmd, FOutputDevice& Ar, UWorld* InWorld);`
- L220 _public prototype_ `void TestSuddenPortChange(uint32 NumConnections);` — Tests a scenario where a connected client suddenly starts sending traffic on a different port (can happen due to a rare router bug. @param NumConnections - number of connections to test sending traffic on a different port.
- L225 _public prototype_ `class UIpConnection* GetServerConnection();` — @return IP connection to server
- L228 _public function_ `float GetResolutionTimeoutValue() const` — @return The address resolution timeout value
- L234 _private function_ `static inline bool IsRecvFailBlocking(ESocketErrors Error)` — Whether or not a socket receive failure Error indicates a blocking error, which should 'break;' the receive loop
- L245 _private prototype_ `void TrackAndLogNewIP(const FInternetAddr& InAddr);` — When a new pre-connection IP is encountered, do rate-limited logging/tracking for it. @param InAddr	The IP address to log/track
- L252 _private prototype_ `void RemoveFromNewIPTracking(const FInternetAddr& InAddr);` — Removes an IP from new IP tracking, after successful connection. @param InAddr	The IP address to remove from tracking
- L257 _private prototype_ `void ResetNewIPTracking();` — Resets new pre-connection IP tracking and timers.
- L264 _private prototype_ `void TickNewIPTracking(float DeltaTime);` — When new pre-connection IP tracking is enabled, ticks the tracking @param DeltaTime		The time since the last global tick
- L281 _private function_ `ESocketState GetSocketState() const` — Returns the current state of the NetDriver socket
- L289 _private prototype_ `void OnRecreateSocketComplete();` — Triggered when socket recreation completes (which may occur after a delay, due to e.g. updating the Receive Thread socket)
- L297 _private prototype_ `void SetSocket_Internal(const TSharedPtr<FSocket>& InSocket, UE::Net::Private::FSetSocketComplete InSetCallback=nullptr);` — Internal function for setting a socket and propagating it to all NetConnection's and the Receive Thread etc.. @param InSocket			The new socket @param InSetCallback		Callback triggered when the new socket is fully set
- L303 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnNetworkProcessingCausingSlowFrame);` — Callback for platform handling when networking is taking a long time in a single frame (by default over 1 second). It may get called multiple times in a single frame if additional processing after a previous alert exceeds the threshold again
- L304 _public member_ `static FOnNetworkProcessingCausingSlowFrame OnNetworkProcessingCausingSlowFrame;`
- L309 _private member_ `uint32 ServerDesiredSocketReceiveBufferBytes;` — `UPROPERTY(Config)` — Number of bytes that will be passed to FSocket::SetReceiveBufferSize when initializing a server.
- L313 _private member_ `uint32 ServerDesiredSocketSendBufferBytes;` — `UPROPERTY(Config)` — Number of bytes that will be passed to FSocket::SetSendBufferSize when initializing a server.
- L317 _private member_ `uint32 ClientDesiredSocketReceiveBufferBytes;` — `UPROPERTY(Config)` — Number of bytes that will be passed to FSocket::SetReceiveBufferSize when initializing a client.
- L321 _private member_ `uint32 ClientDesiredSocketSendBufferBytes;` — `UPROPERTY(Config)` — Number of bytes that will be passed to FSocket::SetSendBufferSize when initializing a client.
- L325 _private member_ `double MaxSecondsInReceive = 0.0;` — `UPROPERTY(Config)` — Maximum time in seconds the TickDispatch can loop on received socket data
- L329 _private member_ `int32 NbPacketsBetweenReceiveTimeTest = 0;` — `UPROPERTY(Config)` — Nb of packets to wait before testing if the receive time went over MaxSecondsInReceive
- L333 _private member_ `float ResolutionConnectionTimeout;` — `UPROPERTY(Config)` — The amount of time to wait in seconds until we consider a connection to a resolution result as timed out
- L419 _private member_ `TUniquePtr<FReceiveThreadRunnable> SocketReceiveThreadRunnable;` — Receive thread runnable object.
- L422 _private member_ `TUniquePtr<FRunnableThread> SocketReceiveThread;` — Receive thread object.
- L425 _private member_ `TUniquePtr<FRecvMulti> RecvMultiState;` — The preallocated state/buffers, for efficiently executing RecvMulti
- L428 _private member_ `TSharedPtr<FSocket> SocketPrivate;` — Underlying socket communication
- L431 _private member_ `ESocketState SocketState = ESocketState::None;` — The state of the NetDriver socket (e.g. ready, resolving, recreating etc.)
- L434 _private member_ `bool bSupportsRecreateSocket = true;` — Whether or not this NetDriver supports recreating the socket
- L437 _private member_ `double LastRecreateSocketTime = 0.0;` — The last time socket recreation was kicked off or completed.
- L451 _private member_ `TArray<uint32> NewIPHashes;` — Hashes for new pre-connection IP's that are being tracked
- L454 _private member_ `TArray<uint32> NewIPHitCount;` — Number of times each 'NewIPHashes' IP was encountered, in the current tracking period
- L457 _private member_ `TArray<FAggregatedIP> AggregatedIPsToLog;` — List of IP's queued for aggregated logging
- L460 _private member_ `bool bExceededIPAggregationLimit = false;` — Whether or not IP hash tracking or aggregated IP limits have been reached. Disables all further IP logging, for the current tracking period
- L463 _private member_ `double NextAggregateIPLogCountdown = 0.0;` — Countdown timer for the current IP aggregation tracking period
- L466 _private member_ `TPimplPtr<UE::Net::Private::FNetDriverAddressResolution> Resolver;` — NetConnection specific address resolution

#### enum `UIpNetDriver::ESocketState`  
`enum class ESocketState : uint8`  
_L270-277_
- desc: The current state of the NetDriver socket
- L272 _public enumerator_ `None`
- L273 _public enumerator_ `Resolving` — Net Address Resolution is in the middle of resolving a working socket
- L274 _public enumerator_ `Recreating` — Socket Recreation is in the middle of creating a new socket
- L275 _public enumerator_ `Ready` — The current socket is fully ready to use
- L276 _public enumerator_ `Error` — The current socket is in an error state

#### struct `UIpNetDriver::FReceivedPacket`  
`struct FReceivedPacket`  
_L336-355_
- desc: Represents a packet received and/or error encountered by the receive thread, if enabled, queued for the game thread to process.
- L339 _public member_ `TArray<uint8> PacketBytes;` — The content of the packet as received from the socket.
- L342 _public member_ `TSharedPtr<FInternetAddr> FromAddress;` — Address from which the packet was received.
- L345 _public member_ `ESocketErrors Error;` — The error triggered by the socket RecvFrom call.
- L348 _public member_ `double PlatformTimeSeconds;` — FPlatformTime::Seconds() at which this packet and/or error was received. Can be used for more accurate ping calculations.
- L350 _public function_ `FReceivedPacket() : Error(SE_NO_ERROR) , PlatformTimeSeconds(0.0)`

#### class `UIpNetDriver::FReceiveThreadRunnable`  
`class FReceiveThreadRunnable : public FRunnable`  
_L358-416_
- inherits: `FRunnable`
- desc: Runnable object representing the receive thread, if enabled.
- L361 _public prototype_ `FReceiveThreadRunnable(UIpNetDriver* InOwningNetDriver);`
- L363 _public prototype_ `virtual uint32 Run() override;`
- L368 _public prototype_ `void PumpOwnerEventQueue();` — Execute commands in OwnerEventQueue on the Game Thread
- L376 _public prototype_ `void SetSocket(const TSharedPtr<FSocket>& InGameThreadSocket, UE::Net::Private::FSetSocketComplete InGameThreadSetCallback=nullptr);` — Sets the socket for the Receive Thread, and triggers a callback (if specified) on the Game Thread when this is complete. @param InGameThreadSocket		The socket specified by the Game Thread @param InGameThreadSetCallback	The callback to trigger on the Game Thread when the socket is set
- L380 _public member_ `TCircularQueue<FReceivedPacket> ReceiveQueue;` — Thread-safe queue of received packets. The Run() function is the producer, UIpNetDriver::TickDispatch on the game thread is the consumer.
- L383 _public member_ `TAtomic<bool> bIsRunning;` — Running flag. The Run() function will return shortly after setting this to false.
- L386 _private prototype_ `bool DispatchPacket(FReceivedPacket&& IncomingPacket, int32 NbBytesRead);`
- L391 _private prototype_ `void PumpCommandQueue();` — Execute commands in CommandQueue on the Receive Thread
- L394 _private prototype_ `void SetSocketImpl(const TSharedPtr<FSocket>& InGameThreadSocket, UE::Net::Private::FSetSocketComplete InGameThreadSetCallback=nullptr);` — Receive Thread implementation for 'SetSocket'
- L399 _private prototype_ `void ClearSocket();` — Clears the Receive Thread socket, and resets the shared socket pointer on the Game Thread.
- L403 _private member_ `TSpscQueue<TUniqueFunction<void()>> CommandQueue;` — Command queue from Game Thread to Receive Thread
- L406 _private member_ `TSpscQueue<TUniqueFunction<void()>> OwnerEventQueue;` — Event queue from the Receive Thread to the Game Thread (may be generalized to 'Owning' thread in future)
- L409 _private member_ `UIpNetDriver* OwningNetDriver;` — The NetDriver which owns the receive thread
- L412 _private member_ `ISocketSubsystem* SocketSubsystem;` — The socket subsystem used by the receive thread
- L415 _private member_ `TSharedPtr<FSocket> Socket;` — Shared pointer for the socket, owned by the Game Thread

#### struct `UIpNetDriver::FAggregatedIP`  
`struct FAggregatedIP`  
_L441-448_
- desc: New IP aggregated logging entry
- L444 _public member_ `uint32 IPHash;` — Hash of the IP
- L447 _public member_ `FString IPStr;` — IP:Port converted to string

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Net` (scope `UE`)
- L30 _namespace_ `namespace Private` (scope `UE::Net`)
- L38 _externvar_ `extern TSharedPtr<FInternetAddr> GCurrentDuplicateIP;`
- L42 _namespace_ `namespace UE`
- L42 _namespace_ `namespace Net` (scope `UE`)
- L54 _prototype_ `const TCHAR* LexToString(ERecreateSocketResult Value);` (scope `UE::Net`)
- L57 _namespace_ `namespace UE`
- L57 _namespace_ `namespace Net` (scope `UE`)
- L57 _namespace_ `namespace Private` (scope `UE::Net`)
- L60 _typedef_ `using FSetSocketComplete = TUniqueFunction<void()>;` (scope `UE::Net::Private`) — Callback triggered when setting a new socket has completed (which may not return immediately, due to multithreading)
- L303 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnNetworkProcessingCausingSlowFrame);` — Callback for platform handling when networking is taking a long time in a single frame (by default over 1 second). It may get called multiple times in a single frame if additional processing after a previous alert exceeds the threshold again

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/JoinSessionCallbackProxy.h` (Public)


#### class `UJoinSessionCallbackProxy`  
`class UJoinSessionCallbackProxy : public UOnlineBlueprintCallProxyBase`  
_L14-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOnlineBlueprintCallProxyBase`
- L20 _private member_ `FEmptyOnlineDelegate OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful join
- L24 _private member_ `FEmptyOnlineDelegate OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful join
- L28 _private prototype_ `static UJoinSessionCallbackProxy* JoinSession(UObject* WorldContextObject, class APlayerController* PlayerController, const FBlueprintSessionResult& SearchResult);` — `UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"), Category = "Online|Session")` — Joins a remote session with the default online subsystem
- L31 _private prototype_ `virtual void Activate() override;` — UOnlineBlueprintCallProxyBase interface
- L36 _private prototype_ `void OnCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);` — Internal callback when the join completes, calls out to the public success/failure callbacks
- L40 _private member_ `TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;` — The player controller triggering things
- L43 _private member_ `FOnlineSessionSearchResult OnlineSearchResult;` — The search result we are sttempting to join
- L46 _private member_ `FOnJoinSessionCompleteDelegate Delegate;` — The delegate executed by the online subsystem
- L49 _private member_ `FDelegateHandle DelegateHandle;` — Handle to the registered FOnJoinSessionComplete delegate
- L52 _private member_ `UObject* WorldContextObject;` — The world context object in which this call is taking place

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/LeaderboardBlueprintLibrary.h` (Public)


#### class `ULeaderboardBlueprintLibrary`  
`class ULeaderboardBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L16-26_
- reflection: `UCLASS(MinimalAPI, meta=(ScriptName="LeaderboardLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: A beacon host used for taking reservations for an existing game session
- L22 _private prototype_ `static bool WriteLeaderboardInteger(APlayerController* PlayerController, FName StatName, int32 StatValue);` — `UFUNCTION(BlueprintCallable, Category = "Online|Leaderboard")` — Writes an integer value to the specified leaderboard
- L25 _private prototype_ `static bool WriteLeaderboardObject(APlayerController* PlayerController, class FOnlineLeaderboardWrite& WriteObject);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/LeaderboardFlushCallbackProxy.h` (Public)


#### class `ULeaderboardFlushCallbackProxy`  
`class ULeaderboardFlushCallbackProxy : public UObject`  
_L10-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L16 _private member_ `FOnLeaderboardFlushed OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful leaderboard flush
- L20 _private member_ `FOnLeaderboardFlushed OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful leaderboard flush
- L24 _private prototype_ `static ULeaderboardFlushCallbackProxy* CreateProxyObjectForFlush(class APlayerController* PlayerController, FName SessionName);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))` — Called to perform the query internally
- L28 _public prototype_ `virtual void BeginDestroy() override;`
- L33 _private prototype_ `void OnFlushCompleted(FName SessionName, bool bWasSuccessful);` — Called by the leaderboard system when the flush is finished
- L36 _private prototype_ `void RemoveDelegate();` — Unregisters our delegate from the leaderboard system
- L39 _private prototype_ `void TriggerFlush(class APlayerController* PlayerController, FName InSessionName);` — Triggers the flush for the specified session
- L43 _private member_ `FOnLeaderboardFlushCompleteDelegate LeaderboardFlushCompleteDelegate;` — Delegate called when a leaderboard has been successfully flushed
- L46 _private member_ `FDelegateHandle LeaderboardFlushCompleteDelegateHandle;` — OnLeaderboardFlushComplete delegate handle
- L49 _private member_ `bool bFailedToEvenSubmit;` — Did we fail immediately?

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeaderboardFlushed, FName, SessionName);`
- L7 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeaderboardFlushed, FName, SessionName);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/LeaderboardQueryCallbackProxy.h` (Public)


#### class `ULeaderboardQueryCallbackProxy`  
`class ULeaderboardQueryCallbackProxy : public UObject`  
_L11-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L17 _private member_ `FLeaderboardQueryResult OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful leaderboard query
- L21 _private member_ `FLeaderboardQueryResult OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful leaderboard query
- L25 _private prototype_ `static ULeaderboardQueryCallbackProxy* CreateProxyObjectForIntQuery(class APlayerController* PlayerController, const FString& StatName);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", DisplayName="Read Leaderboard Integer"), Category="Online|Leaderboard")` — Queries a leaderboard for an integer value
- L29 _public prototype_ `virtual void BeginDestroy() override;`
- L34 _private prototype_ `void OnStatsRead_Delayed();` — Called by the leaderboard system when the read is finished
- L35 _private prototype_ `void OnStatsRead(bool bWasSuccessful);`
- L38 _private prototype_ `void RemoveDelegate();` — Unregisters our delegate from the leaderboard system
- L41 _private prototype_ `void TriggerQuery(class APlayerController* PlayerController, const FString& InStatName, EOnlineKeyValuePairDataType::Type StatType);` — Triggers the query for a specifed user; the ReadObject must already be set up
- L45 _private member_ `FOnLeaderboardReadCompleteDelegate LeaderboardReadCompleteDelegate;` — Delegate called when a leaderboard has been successfully read
- L48 _private member_ `FDelegateHandle LeaderboardReadCompleteDelegateHandle;` — LeaderboardReadComplete delegate handle
- L51 _private member_ `TSharedPtr<class FOnlineLeaderboardRead, ESPMode::ThreadSafe> ReadObject;` — The leaderboard read request
- L54 _private member_ `bool bFailedToEvenSubmit;` — Did we fail immediately?
- L57 _private member_ `FString StatName;` — Name of the stat being queried
- L60 _private member_ `TWeakObjectPtr<UWorld> WorldPtr;` — Pointer to the world, needed to delay the results slightly
- L63 _private member_ `bool bSavedWasSuccessful;` — Did the read succeed?
- L64 _private member_ `int32 SavedValue;`
- L66 _private member_ `FTimerHandle OnStatsRead_DelayedTimerHandle;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLeaderboardQueryResult, int32, LeaderboardValue);`
- L8 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLeaderboardQueryResult, int32, LeaderboardValue);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/LogoutCallbackProxy.h` (Public)


#### class `ULogoutCallbackProxy`  
`class ULogoutCallbackProxy : public UBlueprintAsyncActionBase`  
_L13-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintAsyncActionBase`
- L18 _public prototype_ `ULogoutCallbackProxy(const FObjectInitializer& ObjectInitializer);`
- L22 _public member_ `FOnlineLogoutResult OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when the logout completed successfully
- L26 _public member_ `FOnlineLogoutResult OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when the logout completed unsuccessfully
- L30 _public prototype_ `static ULogoutCallbackProxy* Logout(UObject* WorldContextObject, class APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"), Category = "Online")` — Logs out of the online service
- L33 _public prototype_ `virtual void Activate() override;` — UBlueprintAsyncActionBase interface
- L38 _private prototype_ `void OnLogoutCompleted(int LocalUserNum, bool bWasSuccessful);` — Internal callback when the login UI closes, calls out to the public success/failure callbacks
- L41 _private member_ `TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;` — The player controller triggering things
- L43 _private member_ `FDelegateHandle OnLogoutCompleteDelegateHandle;`
- L46 _private member_ `UObject* WorldContextObject;` — The world context object in which this call is taking place

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnlineLogoutResult, APlayerController*, PlayerController);`
- L10 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnlineLogoutResult, APlayerController*, PlayerController);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/OnlineSessionClient.h` (Public)


#### class `UOnlineSessionClient`  
`class UOnlineSessionClient : public UOnlineSession`  
_L23-202_
- reflection: `UCLASS(MinimalAPI, config=Game)`
- inherits: `UOnlineSession`
- L29 _protected member_ `FOnEndSessionCompleteDelegate OnEndForJoinSessionCompleteDelegate;` — Delegate for destroying a session after previously ending it
- L31 _protected member_ `FOnDestroySessionCompleteDelegate OnDestroyForJoinSessionCompleteDelegate;` — Delegate for joining a new session after previously destroying it
- L33 _protected member_ `FOnDestroySessionCompleteDelegate OnDestroyForMainMenuCompleteDelegate;` — Delegate for returning to main menu after cleaning up
- L35 _protected member_ `FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;` — Delegate after joining a session
- L37 _protected member_ `FOnSessionUserInviteAcceptedDelegate OnSessionUserInviteAcceptedDelegate;` — Delegate for accepting session invites
- L40 _protected member_ `FDelegateHandle OnSessionInviteAcceptedDelegateHandle;` — Handles to the above delegates
- L41 _protected member_ `FDelegateHandle OnEndForJoinSessionCompleteDelegateHandle;`
- L42 _protected member_ `FDelegateHandle OnDestroyForJoinSessionCompleteDelegateHandle;`
- L43 _protected member_ `FDelegateHandle OnDestroyForMainMenuCompleteDelegateHandle;`
- L44 _protected member_ `FDelegateHandle OnJoinSessionCompleteDelegateHandle;`
- L47 _protected member_ `FDelegateHandle StartSessionCompleteHandle;` — Handle to outstanding start session call
- L49 _protected member_ `FDelegateHandle EndSessionCompleteHandle;` — Handle to outstanding end session call
- L51 _protected member_ `FDelegateHandle OnSessionUserInviteAcceptedDelegateHandle;` — Delegate handle that stores delegate for when an invite is accepted by a user
- L54 _protected member_ `FOnlineSessionSearchResult CachedSessionResult;` — Cached invite/search result while in the process of tearing down an existing session
- L57 _protected member_ `bool bIsFromInvite;` — `UPROPERTY(Transient)` — Is this join from an invite
- L60 _protected member_ `bool bHandlingDisconnect;` — `UPROPERTY(Transient)` — Have we started returning to main menu already
- L63 _protected prototype_ `virtual UGameInstance* GetGameInstance() const;` — @return the current game instance
- L66 _protected prototype_ `virtual UWorld* GetWorld() const override;` — @return the current game world
- L68 _protected prototype_ `virtual IOnlineSessionPtr GetSessionInt();`
- L78 _protected prototype_ `virtual bool HandleDisconnectInternal(UWorld* World, UNetDriver* NetDriver);` — Chance for the session client to handle the disconnect @param World world involved in disconnect (possibly NULL for pending travel) @param NetDriver netdriver involved in disconnect @return true if disconnect was handled, false for general engine handling
- L86 _protected prototype_ `void OnEndForJoinSessionComplete(FName SessionName, bool bWasSuccessful);` — Transition from ending a session to destroying a session @param SessionName session that just ended @param bWasSuccessful was the end session attempt successful
- L94 _protected prototype_ `void EndExistingSession(FName SessionName, FOnEndSessionCompleteDelegate& Delegate);` — Ends an existing session of a given name @param SessionName name of session to end @param Delegate delegate to call at session end
- L102 _protected prototype_ `virtual void OnStartSessionComplete(FName InSessionName, bool bWasSuccessful);` — Delegate called when StartSession has completed @param InSessionName name of session involved @param bWasSuccessful true if the call was successful, false otherwise
- L110 _protected prototype_ `virtual void OnEndSessionComplete(FName InSessionName, bool bWasSuccessful);` — Delegate called when EndSession has completed @param InSessionName name of session involved @param bWasSuccessful true if the call was successful, false otherwise
- L120 _private prototype_ `FDelegateHandle EndExistingSession_Impl(FName SessionName, FOnEndSessionCompleteDelegate& Delegate);` — Implementation of EndExistingSession @param SessionName name of session to end @param Delegate delegate to call at session end @return Handle to the added delegate.
- L129 _protected prototype_ `void OnDestroyForJoinSessionComplete(FName SessionName, bool bWasSuccessful);` — Transition from destroying a session to joining a new one of the same name @param SessionName name of session recently destroyed @param bWasSuccessful was the destroy attempt successful
- L137 _protected prototype_ `void OnDestroyForMainMenuComplete(FName SessionName, bool bWasSuccessful);` — Transition from destroying a session to returning to the main menu @param SessionName name of session recently destroyed @param bWasSuccessful was the destroy attempt successful
- L145 _protected prototype_ `void DestroyExistingSession(FName SessionName, FOnDestroySessionCompleteDelegate& Delegate);` — Destroys an existing session of a given name @param SessionName name of session to destroy @param Delegate delegate to call at session destruction
- L154 _protected prototype_ `void DestroyExistingSession_Impl(FDelegateHandle& OutResult, FName SessionName, FOnDestroySessionCompleteDelegate& Delegate);` — Implementation of DestroyExistingSession @param OutResult Handle to the added delegate. @param SessionName name of session to destroy @param Delegate delegate to call at session destruction
- L166 _protected prototype_ `void OnSessionUserInviteAccepted(const bool bWasSuccess, const int32 ControllerId, FUniqueNetIdPtr UserId, const FOnlineSessionSearchResult& InviteResult) override;` — Called from GameInstance when the user accepts an invite @param bWasSuccess true if invite was accepted successfully @param ControllerId the controller index of the user being invited @param UserId the user being invited @param InviteResult the search/settings result for the session we're joining via invite
- L174 _protected prototype_ `void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);` — Delegate fired when the joining process for an online session has completed @param SessionName the name of the session this callback is for @param bWasSuccessful true if the async action completed without error, false if there was an error
- L183 _protected prototype_ `virtual void JoinSession(FName SessionName, const FOnlineSessionSearchResult& SearchResult);` — Join a session of a given name after potentially tearing down an existing one @param LocalUserNum local user id @param SessionName name of session to join @param SearchResult the session to join
- L188 _public prototype_ `virtual void RegisterOnlineDelegates() override;` — UOnlineSession interface begin
- L189 _public prototype_ `virtual void ClearOnlineDelegates() override;`
- L190 _public prototype_ `virtual void HandleDisconnect(UWorld *World, UNetDriver *NetDriver) override;`
- L191 _public prototype_ `virtual void StartOnlineSession(FName SessionName) override;`
- L192 _public prototype_ `virtual void EndOnlineSession(FName SessionName) override;`
- L201 _public prototype_ `virtual void SetInviteFlags(UWorld* World, const FJoinabilitySettings& Settings);` — Update the session settings on the client @param World reference to the current world @param Settings settings to apply to the session

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/QuitMatchCallbackProxy.h` (Public)


#### class `UQuitMatchCallbackProxy`  
`class UQuitMatchCallbackProxy : public UOnlineBlueprintCallProxyBase`  
_L13-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOnlineBlueprintCallProxyBase`
- L18 _public prototype_ `virtual ~UQuitMatchCallbackProxy();`
- L22 _public member_ `FEmptyOnlineDelegate OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful query
- L26 _public member_ `FEmptyOnlineDelegate OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful query
- L30 _public prototype_ `static UQuitMatchCallbackProxy* QuitMatch(UObject* WorldContextObject, APlayerController* PlayerController, FString MatchID, EMPMatchOutcome::Outcome Outcome, int32 TurnTimeoutInSeconds);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Online|TurnBased")` — Quits the turn based match
- L33 _public prototype_ `virtual void Activate() override;` — UOnlineBlueprintCallProxyBase interface
- L36 _public prototype_ `void QuitMatchDelegate(FString MatchID, bool Succeeded);`
- L40 _private member_ `TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;` — The player controller triggering things
- L43 _private member_ `UObject* WorldContextObject;` — The world context object in which this call is taking place
- L46 _private member_ `FString MatchID;` — The MatchID of the match to quit
- L49 _private member_ `EMPMatchOutcome::Outcome Outcome;` — The outcome (won/lost/quit/etc.) of the match
- L52 _private member_ `int32 TurnTimeoutInSeconds;` — If the match isn't over, this will be how much time the next player will have to complete their turn

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace EMPMatchOutcome`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/ShowLoginUICallbackProxy.h` (Public)


#### class `UShowLoginUICallbackProxy`  
`class UShowLoginUICallbackProxy : public UBlueprintAsyncActionBase`  
_L15-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintAsyncActionBase`
- L20 _public prototype_ `UShowLoginUICallbackProxy(const FObjectInitializer& ObjectInitializer);`
- L24 _public member_ `FOnlineShowLoginUIResult OnSuccess;` — `UPROPERTY(BlueprintAssignable)` — Called when there is a successful query
- L28 _public member_ `FOnlineShowLoginUIResult OnFailure;` — `UPROPERTY(BlueprintAssignable)` — Called when there is an unsuccessful query
- L32 _public prototype_ `static UShowLoginUICallbackProxy* ShowExternalLoginUI(UObject* WorldContextObject, class APlayerController* InPlayerController);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"), Category = "Online")` — Shows the login UI for the currently active online subsystem, if the subsystem supports a login UI.
- L35 _public prototype_ `virtual void Activate() override;` — UBlueprintAsyncActionBase interface
- L40 _private prototype_ `void OnShowLoginUICompleted(FUniqueNetIdPtr UniqueId, int LocalUserNum, const FOnlineError& Error);` — Internal callback when the login UI closes, calls out to the public success/failure callbacks
- L43 _private member_ `TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;` — The player controller triggering things
- L46 _private member_ `UObject* WorldContextObject;` — The world context object in which this call is taking place

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnlineShowLoginUIResult, APlayerController*, PlayerController);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnlineShowLoginUIResult, APlayerController*, PlayerController);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/TestBeaconClient.h` (Public)


#### class `ATestBeaconClient`  
`class ATestBeaconClient : public AOnlineBeaconClient`  
_L14-29_
- reflection: `UCLASS(MinimalAPI, transient, notplaceable, config=Engine)`
- inherits: `AOnlineBeaconClient`
- desc: A beacon client used for making reservations with an existing game session
- L19 _private prototype_ `virtual void OnFailure() override;`
- L24 _private prototype_ `virtual void ClientPing();` — `UFUNCTION(client, reliable)` — Send a ping RPC to the client
- L28 _private prototype_ `virtual void ServerPong();` — `UFUNCTION(server, reliable, WithValidation)` — Send a pong RPC to the host

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/TestBeaconHost.h` (Public)


#### class `ATestBeaconHost`  
`class ATestBeaconHost : public AOnlineBeaconHostObject`  
_L16-26_
- reflection: `UCLASS(MinimalAPI, transient, notplaceable, config=Engine)`
- inherits: `AOnlineBeaconHostObject`
- desc: A beacon host used for taking reservations for an existing game session
- L21 _private prototype_ `virtual AOnlineBeaconClient* SpawnBeaconActor(class UNetConnection* ClientConnection) override;`
- L22 _private prototype_ `virtual void OnClientConnected(class AOnlineBeaconClient* NewClientActor, class UNetConnection* ClientConnection) override;`
- L25 _private prototype_ `virtual bool Init();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/TurnBasedBlueprintLibrary.h` (Public)


#### class `UTurnBasedBlueprintLibrary`  
`class UTurnBasedBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L14-29_
- reflection: `UCLASS(MinimalAPI, meta=(ScriptName="TurnBasedLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Library of synchronous achievement calls
- L19 _private prototype_ `static void GetIsMyTurn(UObject* WorldContextObject, APlayerController* PlayerController, FString MatchID, bool& bIsMyTurn);` — `UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Online|TurnBased")`
- L22 _private prototype_ `static void GetMyPlayerIndex(UObject* WorldContextObject, APlayerController* PlayerController, FString MatchID, int32& PlayerIndex);` — `UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Online|TurnBased")`
- L25 _private prototype_ `static void RegisterTurnBasedMatchInterfaceObject(UObject* WorldContextObject, APlayerController* PlayerController, UObject* Object);` — `UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Online|TurnBased")`
- L28 _private prototype_ `static void GetPlayerDisplayName(UObject* WorldContextObject, APlayerController* PlayerController, FString MatchID, int32 PlayerIndex, FString& PlayerDisplayName);` — `UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Online|TurnBased")`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Private/NetAddressResolution.h` (Private)


#### enum `UE::Net::Private::EInitBindSocketsFlags`  
`enum class EInitBindSocketsFlags : uint16`  
_L37-41_
- desc: Flags specifying the type of call to InitBindSockets
- L39 _public enumerator_ `Client = 0x0001`
- L40 _public enumerator_ `Server = 0x0002`

#### class `UE::Net::Private::FNetDriverAddressResolution`  
`class FNetDriverAddressResolution`  
_L49-115_
- desc: NetDriver level Address Resolution
- L63 _private prototype_ `bool InitBindSockets(FCreateAndBindSocketFunc CreateAndBindSocketFunc, EInitBindSocketsFlags Flags, ISocketSubsystem* SocketSubsystem, FString& Error);` — Creates and binds sockets for each local bind address @param CreateAndBindSocketFunc	The NetDriver callback for creating the actual socket @param Flags						Flags specifying the type of initialization this is (typically Client vs Server) @param SocketSubsystem			The NetDriver socket subsystem @param Error						If there was an error, specifies the error message @return							Whether or not the call was successful
- L75 _private prototype_ `bool InitConnect(UNetConnection* ServerConnection, ISocketSubsystem* SocketSubsystem, const FSocket* ActiveSocket, const FURL& ConnectURL);` — Kicks off NetDriver level address resolution for clients connecting to servers (with resolution passing on to FNetConnectionAddressResolution). @param ServerConnection		The connection to the server @param SocketSubsystem		The NetDriver socket subsystem @param ActiveSocket			Read-only pointer to the active NetDriver socket - in case it is not controlled by address resolution @param ConnectURL			The URL used to connect to the server @return						False if synchronous resolution failed immediately (connection is already closed); true otherwise
- L79 _private function_ `void ClearSockets()` — Clears all references to sockets held by this resolver.
- L89 _private function_ `TSharedPtr<FSocket> GetFirstSocket() const` — Gets the first socket bound by address resolution. @return	The first socket bound by address resolution
- L99 _private prototype_ `void SetRetrieveTimestamp(bool bRetrieveTimestamp);` — Sets the internal socket flag for whether or not timestamps from received packets should be retrieved. @param bRetrieveTimestamp	Whether or not timestamps should be retrieved with received packets
- L107 _private prototype_ `static FNetConnectionAddressResolution* GetConnectionResolver(UIpConnection* Connection);` — Gets the NetConnection specific address resolver, for a connection @param Connection			The connection whose Resolver we want access to @return						Returns a pointer to the connection's Resolver
- L114 _private member_ `TArray<TSharedPtr<FSocket>> BoundSockets;` — An array sockets created for every binding address a machine has in use for performing address resolution. This array empties after connections have been spun up.

#### enum `UE::Net::Private::EAddressResolutionState`  
`enum class EAddressResolutionState : uint8`  
_L119-129_
- desc: A state system of the address resolution functionality.
- L121 _public enumerator_ `None` — Undefined
- L122 _public enumerator_ `Disabled` — Address resolution is explicitly disabled
- L123 _public enumerator_ `WaitingForResolves` — Address resolution is underway and we're awaiting results
- L124 _public enumerator_ `Connecting` — Address resolution for a single address is complete and we're attempting to connect (not complete yet)
- L125 _public enumerator_ `TryNextAddress` — Address resolution for the current address failed, and we're trying the next address on the list
- L126 _public enumerator_ `Connected` — We have successfully connected to the current address - awaiting completion on next state check
- L127 _public enumerator_ `Done` — Address resolution has completed
- L128 _public enumerator_ `Error` — There was an error during address resolution

#### enum `UE::Net::Private::ECheckAddressResolutionResult`  
`enum class ECheckAddressResolutionResult : uint8`  
_L134-142_
- desc: Result for CheckAddressResolution - partially mirrors EAddressResolutionState
- L136 _public enumerator_ `None` — No action needed
- L137 _public enumerator_ `TryFirstAddress` — Trying the first address for address resolution
- L138 _public enumerator_ `TryNextAddress` — Trying a subsequent address for address resolution
- L139 _public enumerator_ `Connected` — Address resolution was just marked as connected to the current address
- L140 _public enumerator_ `Error` — There was an error during address resolution
- L141 _public enumerator_ `FindSocketError` — Unable to find a socket that can be used with the current resolve address

#### enum `UE::Net::Private::EEAddressResolutionHandleResult`  
`enum class EEAddressResolutionHandleResult : uint8`  
_L147-151_
- desc: Specifies whether an Address Resolution 'Handle*' function handled the event internally, or whether it should be handled by the caller instead
- L149 _public enumerator_ `HandledInternally` — The event was handled within the internal address resolution code, and needs no handling by the caller
- L150 _public enumerator_ `CallerShouldHandle` — The event was unhandled, the caller of the 'Handle*' function should handle the event

#### enum `UE::Net::Private::ECleanupResolutionSocketsFlags`  
`enum class ECleanupResolutionSocketsFlags : uint8`  
_L156-160_
- desc: CleanupResolutionSockets parameter flags (implemented as flags for extensibility/multiple flags)
- L158 _public enumerator_ `CleanAll = 0x01` — Clean all sockets, including the active one
- L159 _public enumerator_ `CleanInactive = 0x02` — Clean only inactive sockets

#### class `UE::Net::Private::FNetConnectionAddressResolution`  
`class FNetConnectionAddressResolution`  
_L170-362_
- desc: NetConnection level Address Resolution NOTE: Private interface is accessible to the NetConnection, the public interface is only for the NetDriver
- L181 _public function_ `bool IsAddressResolutionEnabled() const` — Checks to see if the owner NetConnection class can use address resolution @return if address resolution is allowed to continue processing.
- L191 _public function_ `bool IsAddressResolutionComplete() const` — Whether or not address resolution has completed. @return		Whether or not address resolution has completed
- L201 _public function_ `bool HasAddressResolutionFailed() const` — Whether or not address resolution has failed @return	Returns whether or not address resolution has failed
- L213 _public function_ `bool HasPendingAddressResults() const` — Whether or not address resolution has pending results ready to be attempted (i.e., the state machine is in TryNextAddress). CheckAddressResolution() may still fail to yield an address (e.g., FindSocketError if no socket matches the protocol). @return		Whether or not there are pending address results to attempt
- L223 _public prototype_ `void CleanupResolutionSockets(ECleanupResolutionSocketsFlags CleanupFlags=ECleanupResolutionSocketsFlags::CleanAll);` — Cleans up the socket information in use with resolution. This can get called numerous times. @param CleanupFlags		Flags specifying what should be cleaned up
- L234 _private prototype_ `bool InitLocalConnection(ISocketSubsystem* SocketSubsystem, FSocket* InSocket, const FURL& InURL);` — Initializes Address resolution for clients connecting to a server. @param SocketSubsystem	The NetConnection socket subsystem @param InSocket			When address resolution is disabled, the socket being used for connecting. @param InURL				The URL the client is connecting to @return					Whether or not address resolution kicked off successfully
- L241 _private prototype_ `EEAddressResolutionHandleResult NotifyTimeout();` — Gives address resolution a chance to override a NetConnection timeout. @return		Whether or not the timeout was handled internally by address resolution, or whether it should be handled by the NetConnection
- L248 _private prototype_ `EEAddressResolutionHandleResult NotifyReceiveError();` — Gives address resolution a chance to override NetConnection handling of packet/socket receive errors. @return		Whether or not the error was handled internally by address resolution, or whether it should be handled by the NetConnection
- L255 _private prototype_ `EEAddressResolutionHandleResult NotifySendError();` — Gives address resolution a chance to override NetConnection handling of socket send errors. @return		Whether or not the error was handled internally by address resolution, or whether it should be handled by the NetConnection
- L262 _private prototype_ `ECheckAddressResolutionResult CheckAddressResolution();` — Checks the state of address resolution, and kicks off next stage if applicable - returning the result/action taken or current status update. @return		Returns the result/action or the current status update.
- L267 _private prototype_ `void NotifyAddressResolutionConnected();` — Notification from the NetConnection that address resolution has connected (that a packet was sucessfully received)
- L274 _private function_ `bool CanContinueResolution() const` — Determines if we can continue processing resolution results or not based on flags and current flow. @return if resolution is allowed to continue processing.
- L289 _private prototype_ `bool ApplyResolutionResults(const FAddressInfoResult& Results, UIpConnection* Connection, const FURL& ConnectURL, const TCHAR* LogSuffix = TEXT(""));` — Applies resolved addresses to the connection's resolver. On failure, closes the connection. In non-shipping builds, also injects any debug address from net.DebugAppendResolverAddress. @param Results		The address info result from GetAddressInfo/GetAddressInfoAsync @param Connection	The owning connection (used for logging, error handling, and socket subsystem access) @param ConnectURL	The original connection URL @param LogSuffix		Optional suffix for log lines (e.g., " [Sync]") @return				True if results were applied successfully, false on error
- L294 _private function_ `void DisableAddressResolution()` — Disables address resolution by pushing the disabled flag into the status field.
- L304 _private function_ `bool IsAddressResolutionConnecting() const` — Whether or not address resolution is in the process of attempting to connect to the server using the current address @return		Whether or not a connection attempt is underway
- L314 _private function_ `bool ShouldBlockSend() const` — Whether or not address resolution is requesting that packet sends should be blocked. @return		Whether or not to block packet sends
- L325 _private function_ `TSharedPtr<FSocket> GetResolutionSocket() const` — Gets the currently resolved socket (used as the primary NetConnection socket). @return		Returns the currently resolved socket
- L335 _private function_ `TSharedPtr<FInternetAddr> GetRemoteAddr() const` — Gets the remote address of the currently resolved socket. @return		The remote address of the currently resolved socket.
- L343 _private member_ `TArray<TSharedPtr<FSocket>> BindSockets;` — An array of sockets tied to every binding address.
- L346 _private member_ `TSharedPtr<FSocket> ResolutionSocket;` — Holds a refcount to the actual socket to be used from BindSockets.
- L349 _private member_ `TSharedPtr<FInternetAddr> RemoteAddr;` — Stores the remote address from socket resolution
- L352 _private member_ `TArray<TSharedRef<FInternetAddr>> ResolverResults;` — An array containing the address results GAI returns for the current host value. Given to us from the netdriver.
- L355 _private member_ `int32 CurrentAddressIndex = 0;` — The index into the ResolverResults that we're currently attempting
- L361 _private member_ `EAddressResolutionState ResolutionState = EAddressResolutionState::None;` — The connection's current status of where it is in the resolution state machine. If a platform should not use resolution, call DisableAddressResolution() in your constructor

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Net` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::Net`)
- L32 _typedef_ `using FCreateAndBindSocketFunc = TUniqueFunction<FUniqueSocket(TSharedRef<FInternetAddr> , FString& )>;` (scope `UE::Net::Private`) — NetDriver callback creating and binding the NetDriver-specific socket @param BindAddr	The bind address for the socket @param Error		If there was an error, specifies the error message
- L43 _prototype_ `ENUM_CLASS_FLAGS(EInitBindSocketsFlags);` (scope `UE::Net::Private`)
- L162 _prototype_ `ENUM_CLASS_FLAGS(ECleanupResolutionSocketsFlags);` (scope `UE::Net::Private`)

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Private/OnlineEngineInterfaceImpl.h` (Private)


#### class `UOnlineEngineInterfaceImpl`  
`class UOnlineEngineInterfaceImpl : public UOnlineEngineInterface`  
_L18-184_
- reflection: `UCLASS(MinimalAPI, config = Engine)`
- inherits: `UOnlineEngineInterface`
- L23 _public prototype_ `virtual void PostInitProperties() override;`
- L30 _public prototype_ `virtual bool IsLoaded(FName OnlineIdentifier) override;`
- L31 _public prototype_ `virtual FName GetOnlineIdentifier(FWorldContext& WorldContext) override;`
- L32 _public prototype_ `virtual bool DoesInstanceExist(FName OnlineIdentifier) override;`
- L35 _public prototype_ `virtual void ShutdownOnlineSubsystem(FName OnlineIdentifier) override;` — NOTE: In OSSv1 it only shuts down the default type of subsystem instance corresponding to the identifier
- L36 _public prototype_ `virtual void DestroyOnlineSubsystem(FName OnlineIdentifier) override;`
- L37 _public prototype_ `virtual FName GetDefaultOnlineSubsystemName() const override;`
- L38 _public prototype_ `virtual bool IsCompatibleUniqueNetId(const FUniqueNetIdWrapper& InUniqueNetId) const override;`
- L43 _public prototype_ `virtual uint8 GetReplicationHashForSubsystem(FName InSubsystemName) const override;` — Utils
- L44 _public prototype_ `virtual FName GetSubsystemFromReplicationHash(uint8 InHash) const override;`
- L49 _private member_ `TMap<FName, FName> MappedUniqueNetIdTypes;` — `UPROPERTY(config)` — Mapping of unique net ids that should not be treated as foreign ids to the local subsystem.
- L53 _private member_ `TArray<FName> CompatibleUniqueNetIdTypes;` — `UPROPERTY(config)` — Array of unique net ids that are deemed valid when tested against gameplay login checks.
- L57 _private member_ `FName VoiceSubsystemNameOverride;` — `UPROPERTY(config)` — Allow the subsystem used for voice functions to be overridden, in case it needs to be different than the default subsystem. May be useful on console platforms.
- L60 _private prototype_ `FName GetOnlineIdentifier(UWorld* World);` — @return the identifier/context handle associated with a UWorld
- L63 _private prototype_ `FName GetDedicatedServerSubsystemNameForSubsystem(const FName Subsystem) const;` — Returns the name of a corresponding dedicated server subsystem for the given subsystem, or NAME_None if such a system doesn't exist.
- L70 _public prototype_ `virtual FUniqueNetIdWrapper CreateUniquePlayerIdWrapper(const FString& Str, FName Type) override;`
- L71 _public prototype_ `virtual FUniqueNetIdWrapper GetUniquePlayerIdWrapper(UWorld* World, int32 LocalUserNum, FName Type) override;`
- L73 _public prototype_ `virtual FString GetPlayerNickname(UWorld* World, const FUniqueNetIdWrapper& UniqueId) override;`
- L74 _public prototype_ `virtual bool GetPlayerPlatformNickname(UWorld* World, int32 LocalUserNum, FString& OutNickname) override;`
- L76 _public prototype_ `virtual bool AutoLogin(UWorld* World, int32 LocalUserNum, const FOnlineAutoLoginComplete& InCompletionDelegate) override;`
- L77 _public prototype_ `virtual bool IsLoggedIn(UWorld* World, int32 LocalUserNum) override;`
- L81 _private member_ `FDelegateHandle OnLoginCompleteDelegateHandle;`
- L82 _private prototype_ `void OnAutoLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error, FName OnlineIdentifier, FOnlineAutoLoginComplete InCompletionDelegate);`
- L89 _public prototype_ `virtual void StartSession(UWorld* World, FName SessionName, FOnlineSessionStartComplete& InCompletionDelegate) override;`
- L90 _public prototype_ `virtual void EndSession(UWorld* World, FName SessionName, FOnlineSessionEndComplete& InCompletionDelegate) override;`
- L91 _public prototype_ `virtual bool DoesSessionExist(UWorld* World, FName SessionName) override;`
- L93 _public prototype_ `virtual bool GetSessionJoinability(UWorld* World, FName SessionName, FJoinabilitySettings& OutSettings) override;`
- L94 _public prototype_ `virtual void UpdateSessionJoinability(UWorld* World, FName SessionName, bool bPublicSearchable, bool bAllowInvites, bool bJoinViaPresence, bool bJoinViaPresenceFriendsOnly) override;`
- L96 _public prototype_ `virtual void RegisterPlayer(UWorld* World, FName SessionName, const FUniqueNetIdWrapper& UniqueId, bool bWasInvited) override;`
- L97 _public prototype_ `virtual void UnregisterPlayer(UWorld* World, FName SessionName, const FUniqueNetIdWrapper& UniqueId) override;`
- L98 _public prototype_ `virtual void UnregisterPlayers(UWorld* World, FName SessionName, const TArray<FUniqueNetIdWrapper>& Players) override;`
- L100 _public prototype_ `virtual bool GetResolvedConnectString(UWorld* World, FName SessionName, FString& URL) override;`
- L105 _private member_ `TMap<FName, FDelegateHandle> OnStartSessionCompleteDelegateHandles;` — Mapping of delegate handles for each online StartSession() call while in flight
- L106 _private prototype_ `void OnStartSessionComplete(FName SessionName, bool bWasSuccessful, FName OnlineIdentifier, FOnlineSessionStartComplete CompletionDelegate);`
- L109 _private member_ `TMap<FName, FDelegateHandle> OnEndSessionCompleteDelegateHandles;` — Mapping of delegate handles for each online EndSession() call while in flight
- L110 _private prototype_ `void OnEndSessionComplete(FName SessionName, bool bWasSuccessful, FName OnlineIdentifier, FOnlineSessionEndComplete CompletionDelegate);`
- L117 _public prototype_ `virtual TSharedPtr<FVoicePacket> GetLocalPacket(UWorld* World, uint8 LocalUserNum) override;`
- L118 _public prototype_ `virtual TSharedPtr<FVoicePacket> SerializeRemotePacket(UWorld* World, const UNetConnection* const RemoteConnection, FArchive& Ar) override;`
- L120 _public prototype_ `virtual void StartNetworkedVoice(UWorld* World, uint8 LocalUserNum) override;`
- L121 _public prototype_ `virtual void StopNetworkedVoice(UWorld* World, uint8 LocalUserNum) override;`
- L122 _public prototype_ `virtual void ClearVoicePackets(UWorld* World) override;`
- L124 _public prototype_ `virtual bool MuteRemoteTalker(UWorld* World, uint8 LocalUserNum, const FUniqueNetIdWrapper& PlayerId, bool bIsSystemWide) override;`
- L125 _public prototype_ `virtual bool UnmuteRemoteTalker(UWorld* World, uint8 LocalUserNum, const FUniqueNetIdWrapper& PlayerId, bool bIsSystemWide) override;`
- L127 _public prototype_ `virtual int32 GetNumLocalTalkers(UWorld* World) override;`
- L134 _public prototype_ `virtual void ShowLeaderboardUI(UWorld* World, const FString& CategoryName) override;`
- L135 _public prototype_ `virtual void ShowAchievementsUI(UWorld* World, int32 LocalUserNum) override;`
- L136 _public prototype_ `virtual void BindToExternalUIOpening(const FOnlineExternalUIChanged& Delegate) override;`
- L137 _public prototype_ `virtual void ShowWebURL(const FString& CurrentURL, const UOnlineEngineInterface::FShowWebUrlParams& ShowParams, const FOnlineShowWebUrlClosed& CompletionDelegate) override;`
- L138 _public prototype_ `virtual bool CloseWebURL() override;`
- L142 _private prototype_ `void OnExternalUIChange(bool bInIsOpening, FOnlineExternalUIChanged Delegate);`
- L149 _public prototype_ `virtual void DumpSessionState(UWorld* World) override;`
- L150 _public prototype_ `virtual void DumpPartyState(UWorld* World) override;`
- L151 _public prototype_ `virtual void DumpVoiceState(UWorld* World) override;`
- L152 _public prototype_ `virtual void DumpChatState(UWorld* World) override;`
- L160 _public prototype_ `virtual bool SupportsOnlinePIE() override;`
- L161 _public prototype_ `virtual void SetShouldTryOnlinePIE(bool bShouldTry) override;`
- L162 _public prototype_ `virtual int32 GetNumPIELogins() override;`
- L163 _public prototype_ `virtual FString GetPIELoginCommandLineArgs(int32 Index) override;`
- L164 _public prototype_ `virtual void SetForceDedicated(FName OnlineIdentifier, bool bForce) override;`
- L165 _public prototype_ `virtual void LoginPIEInstance(FName OnlineIdentifier, int32 LocalUserNum, int32 PIELoginNum, FOnPIELoginComplete& CompletionDelegate) override;`
- L166 _public prototype_ `virtual void PIEEndCleanup(FName OnlineIdentifier) override;`
- L172 _private member_ `TMap<FName, FDelegateHandle> OnLoginPIECompleteDelegateHandlesForPIEInstances;` — Mapping of delegate handles for each online Login() call while in flight
- L173 _private prototype_ `void OnPIELoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error, FName OnlineIdentifier, FOnlineAutoLoginComplete InCompletionDelegate);`
- L176 _private prototype_ `void InitCompatibilityInterface();`
- L180 _private member_ `bool bOnlineServicesCompatibilityEnabled = false;` — `UPROPERTY(config)` — Whether to enable a compatibility interface for transitioning from OSSv1 to OSSv2.
- L183 _private member_ `TObjectPtr<UOnlineEngineInterface> OnlineServicesCompatibilityInterface;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Private/OnlinePIEConfig.h` (Private)


#### class `UOnlinePIEConfig`  
`class UOnlinePIEConfig : public UObject`  
_L10-19_
- reflection: `UCLASS(config=Editor)`
- inherits: `UObject`
- L14 _public prototype_ `UOnlinePIEConfig(const FObjectInitializer& ObjectInitializer);`
- L18 _public member_ `TArray<FString> LoginTypesAllowingDuplicates;` — `UPROPERTY(config)` — Type types of login credentials which allow duplicate entries.

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Private/OnlinePIESettings.h` (Private)


#### class `UOnlinePIESettings`  
`class UOnlinePIESettings : public UDeveloperSettings`  
_L14-35_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, meta = (DisplayName = "Play Credentials"))`
- inherits: `UDeveloperSettings`
- desc: Setup login credentials for the Play In Editor (PIE) feature
- L19 _public prototype_ `UOnlinePIESettings(const FObjectInitializer& ObjectInitializer);`
- L23 _public member_ `bool bOnlinePIEEnabled;` — `UPROPERTY(config, EditAnywhere, Category = "Logins", meta = (DisplayName = "Enable Logins", Tooltip = "Attempt to login with user credentials on a backend service before launching the PIE instance."))` — Will Play In Editor (PIE) attempt to login to a platform service before launching the instance
- L27 _public member_ `TArray<FOnlineAccountStoredCredentials> Logins;` — `UPROPERTY(config, EditAnywhere, Category = "Logins", meta = (DisplayName = "Credentials", Tooltip = "Login credentials, at least one for each instance of PIE that is intended to be run"))` — Array of credentials to use, one for each Play In Editor (PIE) instance
- L30 _public prototype_ `virtual void PostInitProperties() override;`
- L32 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Private/OnlineServicesEngineInterfaceImpl.h` (Private)


#### class `UOnlineServicesEngineInterfaceImpl`  
`class UOnlineServicesEngineInterfaceImpl : public UOnlineEngineInterface`  
_L21-132_
- reflection: `UCLASS(MinimalAPI, config = Engine)`
- inherits: `UOnlineEngineInterface`
- desc: Implementation of UOnlineEngineInterface that uses Online Services (also known as Online Subsystem v2)
- L30 _public prototype_ `virtual bool IsLoaded(FName OnlineIdentifier) override;`
- L31 _public prototype_ `virtual FName GetOnlineIdentifier(FWorldContext& WorldContext) override;`
- L32 _public prototype_ `virtual bool DoesInstanceExist(FName OnlineIdentifier) override;`
- L34 _public prototype_ `virtual void ShutdownOnlineSubsystem(FName OnlineIdentifier) override;` — NOTE: In OnlineServices it destroys all types of OnlineServices instances which contains this identifier
- L35 _public prototype_ `virtual void DestroyOnlineSubsystem(FName OnlineIdentifier) override;`
- L36 _public prototype_ `virtual FName GetDefaultOnlineSubsystemName() const override;`
- L37 _public prototype_ `virtual bool IsCompatibleUniqueNetId(const FUniqueNetIdWrapper& InUniqueNetId) const override;`
- L42 _public prototype_ `virtual uint8 GetReplicationHashForSubsystem(FName InSubsystemName) const override;` — Utils
- L43 _public prototype_ `virtual FName GetSubsystemFromReplicationHash(uint8 InHash) const override;`
- L47 _private prototype_ `FName GetOnlineIdentifier(UWorld* World) const;` — @return the identifier/context handle associated with a UWorld
- L54 _public prototype_ `virtual FUniqueNetIdWrapper CreateUniquePlayerIdWrapper(const FString& Str, FName Type) override;`
- L55 _public prototype_ `virtual FUniqueNetIdWrapper GetUniquePlayerIdWrapper(UWorld* World, int32 LocalUserNum, FName Type) override;`
- L57 _public prototype_ `virtual FString GetPlayerNickname(UWorld* World, const FUniqueNetIdWrapper& UniqueId) override;`
- L58 _public prototype_ `virtual bool GetPlayerPlatformNickname(UWorld* World, int32 LocalUserNum, FString& OutNickname) override;`
- L60 _public prototype_ `virtual bool AutoLogin(UWorld* World, int32 LocalUserNum, const FOnlineAutoLoginComplete& InCompletionDelegate) override;`
- L61 _public prototype_ `virtual bool IsLoggedIn(UWorld* World, int32 LocalUserNum) override;`
- L68 _public prototype_ `virtual void StartSession(UWorld* World, FName SessionName, FOnlineSessionStartComplete& InCompletionDelegate) override;`
- L69 _public prototype_ `virtual void EndSession(UWorld* World, FName SessionName, FOnlineSessionEndComplete& InCompletionDelegate) override;`
- L70 _public prototype_ `virtual bool DoesSessionExist(UWorld* World, FName SessionName) override;`
- L72 _public prototype_ `virtual bool GetSessionJoinability(UWorld* World, FName SessionName, FJoinabilitySettings& OutSettings) override;`
- L73 _public prototype_ `virtual void UpdateSessionJoinability(UWorld* World, FName SessionName, bool bPublicSearchable, bool bAllowInvites, bool bJoinViaPresence, bool bJoinViaPresenceFriendsOnly) override;`
- L75 _public prototype_ `virtual void RegisterPlayer(UWorld* World, FName SessionName, const FUniqueNetIdWrapper& UniqueId, bool bWasInvited) override;`
- L76 _public prototype_ `virtual void UnregisterPlayer(UWorld* World, FName SessionName, const FUniqueNetIdWrapper& UniqueId) override;`
- L77 _public prototype_ `virtual void UnregisterPlayers(UWorld* World, FName SessionName, const TArray<FUniqueNetIdWrapper>& Players) override;`
- L79 _public prototype_ `virtual bool GetResolvedConnectString(UWorld* World, FName SessionName, FString& URL) override;`
- L86 _public prototype_ `virtual TSharedPtr<FVoicePacket> GetLocalPacket(UWorld* World, uint8 LocalUserNum) override;`
- L87 _public prototype_ `virtual TSharedPtr<FVoicePacket> SerializeRemotePacket(UWorld* World, const UNetConnection* const RemoteConnection, FArchive& Ar) override;`
- L89 _public prototype_ `virtual void StartNetworkedVoice(UWorld* World, uint8 LocalUserNum) override;`
- L90 _public prototype_ `virtual void StopNetworkedVoice(UWorld* World, uint8 LocalUserNum) override;`
- L91 _public prototype_ `virtual void ClearVoicePackets(UWorld* World) override;`
- L93 _public prototype_ `virtual bool MuteRemoteTalker(UWorld* World, uint8 LocalUserNum, const FUniqueNetIdWrapper& PlayerId, bool bIsSystemWide) override;`
- L94 _public prototype_ `virtual bool UnmuteRemoteTalker(UWorld* World, uint8 LocalUserNum, const FUniqueNetIdWrapper& PlayerId, bool bIsSystemWide) override;`
- L96 _public prototype_ `virtual int32 GetNumLocalTalkers(UWorld* World) override;`
- L103 _public prototype_ `virtual void ShowLeaderboardUI(UWorld* World, const FString& CategoryName) override;`
- L104 _public prototype_ `virtual void ShowAchievementsUI(UWorld* World, int32 LocalUserNum) override;`
- L105 _public prototype_ `virtual void BindToExternalUIOpening(const FOnlineExternalUIChanged& Delegate) override;`
- L106 _public prototype_ `virtual void ShowWebURL(const FString& CurrentURL, const UOnlineEngineInterface::FShowWebUrlParams& ShowParams, const FOnlineShowWebUrlClosed& CompletionDelegate) override;`
- L107 _public prototype_ `virtual bool CloseWebURL() override;`
- L114 _public prototype_ `virtual void DumpSessionState(UWorld* World) override;`
- L115 _public prototype_ `virtual void DumpPartyState(UWorld* World) override;`
- L116 _public prototype_ `virtual void DumpVoiceState(UWorld* World) override;`
- L117 _public prototype_ `virtual void DumpChatState(UWorld* World) override;`
- L125 _public prototype_ `virtual bool SupportsOnlinePIE() override;`
- L126 _public prototype_ `virtual void SetShouldTryOnlinePIE(bool bShouldTry) override;`
- L127 _public prototype_ `virtual int32 GetNumPIELogins() override;`
- L128 _public prototype_ `virtual FString GetPIELoginCommandLineArgs(int32 Index) override;`
- L129 _public prototype_ `virtual void SetForceDedicated(FName OnlineIdentifier, bool bForce) override;`
- L130 _public prototype_ `virtual void LoginPIEInstance(FName OnlineIdentifier, int32 LocalUserNum, int32 PIELoginNum, FOnPIELoginComplete& CompletionDelegate) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Private/OnlineServicesEngineUtilsImpl.h` (Private)


#### class `UE::Online::FOnlineServicesEngineUtils`  
`class FOnlineServicesEngineUtils : public IOnlineServicesEngineUtils`  
_L18-57_
- inherits: `IOnlineServicesEngineUtils`
- desc: Concrete implementation of IOnlineServicesEngineUtils interface
- L22 _public function_ `FOnlineServicesEngineUtils() : bShouldTryOnlinePIE(true)`
- L27 _public prototype_ `virtual ~FOnlineServicesEngineUtils();`
- L29 _public prototype_ `virtual FName GetOnlineIdentifier(const FWorldContext& WorldContext) const override;`
- L30 _public prototype_ `virtual FName GetOnlineIdentifier(const UWorld* World) const override;`
- L31 _public prototype_ `virtual void SetEngineExternalUIBinding(const FOnExternalUIChangeDelegate& InOnExternalUIChangeDelegate) override;`
- L34 _public prototype_ `virtual bool SupportsOnlinePIE() const override;`
- L35 _public prototype_ `virtual void SetShouldTryOnlinePIE(bool bShouldTry) override;`
- L36 _public prototype_ `virtual bool IsOnlinePIEEnabled() const override;`
- L37 _public prototype_ `virtual int32 GetNumPIELogins() const override;`
- L38 _public prototype_ `virtual void GetPIELogins(TArray<FAuthLogin::Params>& Logins) const override;`
- L43 _private prototype_ `void Init();`
- L44 _private prototype_ `void OnOnlineServicesCreated(TSharedRef<class IOnlineServices> NewServices);`
- L47 _private member_ `bool bShouldTryOnlinePIE;` — If false it will not try to do online PIE at all
- L50 _private member_ `FOnExternalUIChangeDelegate OnExternalUIChangeDelegate;` — Delegate set by the engine for notification of external UI operations
- L52 _private member_ `TArray<FOnlineEventDelegateHandle> ExternalUIDelegateHandles;` — Array of delegate handles
- L55 _private member_ `FDelegateHandle OnOnlineServicesCreatedDelegateHandle;` — Delegate binding when new online services are created

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Private/OnlineSubsystemBPCallHelper.h` (Private)


#### struct `FOnlineSubsystemBPCallHelper`  
`struct FOnlineSubsystemBPCallHelper`  
_L11-27_
- desc: Helper class for various methods to reduce the call hierarchy
- L14 _public prototype_ `FOnlineSubsystemBPCallHelper(const TCHAR* CallFunctionContext, UObject* WorldContextObject, FName SystemName = NAME_None);`
- L16 _public prototype_ `void QueryIDFromPlayerController(APlayerController* PlayerController);`
- L18 _public function_ `bool IsValid() const`
- L24 _public member_ `FUniqueNetIdPtr UserID;`
- L25 _public member_ `IOnlineSubsystem* const OnlineSub;`
- L26 _public member_ `const TCHAR* FunctionContext;`

#### Free symbols / members of external scopes

- L29 _macro_ `#define INVALID_INDEX -1`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/Online/OnlineServicesEngineUtils.h` (Public)


#### class `UE::Online::IOnlineServicesEngineUtils`  
`class IOnlineServicesEngineUtils`  
_L20-69_
- desc: Interface class for various online utility functions for Engine
- L24 _protected function_ `IOnlineServicesEngineUtils()` — Hidden on purpose
- L27 _public prototype_ `virtual ~IOnlineServicesEngineUtils() = default;`
- L35 _public prototype_ `virtual FName GetOnlineIdentifier(const FWorldContext& WorldContext) const = 0;` — Gets an FName that uniquely identifies an instance of a world to differentiate online services for PIE @param WorldContext the worldcontext @return an FName that can be used with online services
- L43 _public prototype_ `virtual FName GetOnlineIdentifier(const UWorld* World) const = 0;` — Gets an FName that uniquely identifies an instance of a world to differentiate online services for PIE @param World the world to use for context @return an FName that can be used with Online Services
- L51 _public prototype_ `virtual void SetEngineExternalUIBinding(const FOnExternalUIChangeDelegate& OnExternalUIChangeDelegate) = 0;` — Bind a notification delegate when any subsystem external UI is opened/closed *NOTE* there is only meant to be one delegate needed for this, game code should bind manually @param OnExternalUIChangeDelegate delegate fired when the external UI is opened/closed
- L59 _public prototype_ `virtual bool SupportsOnlinePIE() const = 0;` — @return true if the default platform supports logging in for Play In Editor (PIE)
- L61 _public prototype_ `virtual void SetShouldTryOnlinePIE(bool bShouldTry) = 0;` — Enable/Disable online PIE at runtime
- L63 _public prototype_ `virtual bool IsOnlinePIEEnabled() const = 0;` — @return true if the user has enabled logging in for Play In Editor (PIE)
- L65 _public prototype_ `virtual int32 GetNumPIELogins() const = 0;` — @return the number of logins the user has setup for Play In Editor (PIE)
- L67 _public prototype_ `virtual void GetPIELogins(TArray<FAuthLogin::Params>& Logins) const = 0;` — @return the array of valid credentials the user has setup for Play In Editor (PIE)

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnExternalUIChange, bool);`
- L12 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnExternalUIChange, bool);`
- L13 _typedef_ `typedef FOnExternalUIChange::FDelegate FOnExternalUIChangeDelegate;`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Online` (scope `UE`)
- L72 _prototype_ `IOnlineServicesEngineUtils* GetServicesEngineUtils();` (scope `UE::Online`) — @return the single instance of the online services utils interface
- L74 _function_ `inline FName GetServicesInstanceName(const UWorld* World)` (scope `UE::Online`)
- L88 _function_ `inline IOnlineServicesPtr GetServices(const UWorld* World, EOnlineServices OnlineServices = EOnlineServices::Default)` (scope `UE::Online`)

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineAccountStoredCredentials.h` (Public)


#### struct `FOnlineAccountStoredCredentials`  
`struct FOnlineAccountStoredCredentials`  
_L14-48_
- reflection: `USTRUCT()`
- desc: Stores online account login credentials (for editor config data). @note ONLY use this in trusted environments (like a local config file) and NOT for anything that requires actual security/strong encryption. @see FOnlineAccountCredentials.
- L22 _public member_ `FString Id;` — `UPROPERTY(EditAnywhere, Category = "Logins", meta = (DisplayName = "User Id", Tooltip = "Id of the user logging in (email, display name, facebook id, etc)"))` — Id of the user logging in (email, display name, facebook id, etc)
- L25 _public member_ `FString Token;` — `UPROPERTY(EditAnywhere, Transient, Category = "Logins", meta = (DisplayName = "Password", Tooltip = "Credentials of the user logging in (password or auth token)", PasswordField = true))` — Credentials of the user logging in (password or auth token)
- L28 _public member_ `FString Type;` — `UPROPERTY(EditAnywhere, Category = "Logins", meta = (DisplayName = "Type", Tooltip = "Type of account. Needed to identity the auth method to use (epic, internal, facebook, etc)"))` — Type of account. Needed to identity the auth method to use (epic, internal, facebook, etc)
- L31 _public member_ `TArray<uint8> TokenBytes;` — `UPROPERTY()` — Token stored as an array of bytes, encrypted
- L34 _public function_ `bool IsValid() const` — @return true if the credentials are valid, false otherwise
- L42 _public prototype_ `void Encrypt();` — Encrypt the Token field into the TokenBytes field
- L47 _public prototype_ `void Decrypt();` — Decrypt the TokenBytes field into the Token field

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineBeacon.h` (Public)


#### enum `EBeaconState::Type`  
`enum Type`  
_L22-26_
- L24 _public enumerator_ `AllowRequests`
- L25 _public enumerator_ `DenyRequests`

#### enum `EBeaconFailureReason`  
`enum class EBeaconFailureReason : uint8`  
_L29-38_
- L31 _public enumerator_ `Unknown = 0`
- L32 _public enumerator_ `TransportError = 1`
- L33 _public enumerator_ `VersionMismatch = 2`
- L34 _public enumerator_ `InitFailure = 3`
- L35 _public enumerator_ `EncryptionFailure = 4`
- L36 _public enumerator_ `ApplicationError = 5`
- L37 _public enumerator_ `TimeOut`

#### class `AOnlineBeacon`  
`class AOnlineBeacon : public AActor, public FNetworkNotify`  
_L67-170_
- reflection: `UCLASS(MinimalApi, transient, config=Engine, notplaceable)`
- inherits: `AActor,FNetworkNotify`
- desc: Base class for beacon communication (Unreal Networking, but outside normal gameplay traffic)
- L72 _private prototype_ `virtual void OnActorChannelOpen(FInBunch& InBunch, UNetConnection* Connection) override;`
- L73 _private prototype_ `virtual bool IsRelevancyOwnerFor(const AActor* ReplicatedActor, const AActor* ActorOwner, const AActor* ConnectionActor) const override;`
- L74 _private prototype_ `virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;`
- L75 _private function_ `virtual const AActor* GetNetOwner() const override`
- L76 _private function_ `virtual UNetConnection* GetNetConnection() const override`
- L77 _private function_ `virtual bool IsLevelBoundsRelevant() const override`
- L78 _private prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);`
- L82 _private prototype_ `virtual EAcceptConnection::Type NotifyAcceptingConnection() override;`
- L83 _private prototype_ `virtual void NotifyAcceptedConnection(UNetConnection* Connection) override;`
- L84 _private prototype_ `virtual bool NotifyAcceptingChannel(UChannel* Channel) override;`
- L85 _private prototype_ `virtual void NotifyControlMessage(UNetConnection* Connection, uint8 MessageType, FInBunch& Bunch) override;`
- L93 _private function_ `EBeaconState::Type GetBeaconState() const` — Get the current state of the beacon @return state of the beacon
- L103 _private prototype_ `virtual void HandleNetworkFailure(UWorld* World, UNetDriver *NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);` — Notification of network error messages, allows a beacon to handle the failure @param	World associated with failure @param	NetDriver associated with failure @param	FailureType	the type of error @param	ErrorString	additional string detailing the error
- L110 _private function_ `void PauseBeaconRequests(bool bPause)` — Set Beacon state @bPause should the beacon stop accepting requests
- L134 _private prototype_ `virtual void DestroyBeacon();` — Beacon cleanup and net driver destruction
- L138 _protected prototype_ `void CleanupNetDriver();`
- L142 _protected member_ `float BeaconConnectionInitialTimeout;` — `UPROPERTY(Config)` — Time beacon will wait to establish a connection with the beacon host
- L145 _protected member_ `float BeaconConnectionTimeout;` — `UPROPERTY(Config)` — Time beacon will wait for packets after establishing a connection before giving up
- L149 _protected member_ `TObjectPtr<UNetDriver> NetDriver;` — `UPROPERTY()` — Net driver routing network traffic
- L152 _protected member_ `EBeaconState::Type BeaconState;` — State of beacon
- L154 _protected member_ `FDelegateHandle HandleNetworkFailureDelegateHandle;` — Handle to the registered HandleNetworkFailure delegate
- L157 _protected member_ `FName NetDriverDefinitionName;` — Name of definition to use when creating the net driver
- L160 _protected prototype_ `virtual bool InitBase();` — Common initialization for all beacon types
- L164 _protected prototype_ `virtual void OnFailure();` — `UE_DEPRECATED(5.7, "Deprecated - Move to OnFailure(FBeaconFailureContext).")` — Notification that failure needs to be handled
- L166 _protected prototype_ `virtual void OnFailure(EBeaconFailureReason Reason, FStringView ErrorMessage);`
- L169 _protected prototype_ `virtual bool HasNetOwner() const override;` — overridden to return that player controllers are capable of RPCs

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace EEndPlayReason`
- L11 _namespace_ `namespace ENetworkFailure`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBeacon, Log, All);`
- L20 _namespace_ `namespace EBeaconState`
- L40 _function_ `inline const TCHAR* LexToString(EBeaconFailureReason Value)`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineBeaconClient.h` (Public)


#### enum `EBeaconConnectionState`  
`enum class EBeaconConnectionState : uint8`  
_L22-28_
- reflection: `UENUM()`
- desc: State of a connection.
- L24 _public enumerator_ `Invalid = 0` — Connection is invalid, possibly uninitialized.
- L25 _public enumerator_ `Closed = 1` — Connection permanently closed.
- L26 _public enumerator_ `Pending = 2` — Connection is awaiting connection.
- L27 _public enumerator_ `Open = 3` — Connection is open.

#### struct `FOnlineBeaconClientInitParams`  
`struct FOnlineBeaconClientInitParams`  
_L33-37_
- desc: Parameters used when initializing AOnlineBeaconClient.
- L35 _public member_ `FURL URL;`
- L36 _public member_ `bool bReplicateTransactionally = true;`

#### class `AOnlineBeaconClient`  
`class AOnlineBeaconClient : public AOnlineBeacon`  
_L52-227_
- reflection: `UCLASS(MinimalAPI, transient, notplaceable, config=Engine)`
- inherits: `AOnlineBeacon`
- desc: Base class for any unique beacon connectivity, paired with an AOnlineBeaconHostObject implementation This is the actual actor that replicates across client/server and where all RPCs occur On the host, the life cycle is managed by an AOnlineBeaconHostObject On the client, the life cycle is managed by the game
- L57 _private prototype_ `virtual void Tick(float DeltaTime) override;`
- L58 _private prototype_ `virtual bool UseShortConnectTimeout() const override;`
- L59 _private prototype_ `virtual void OnNetCleanup(UNetConnection* Connection) override;`
- L60 _private prototype_ `virtual const AActor* GetNetOwner() const override;`
- L61 _private prototype_ `virtual UNetConnection* GetNetConnection() const override;`
- L62 _private prototype_ `virtual bool DestroyNetworkActorHandled() override;`
- L66 _private prototype_ `virtual void NotifyControlMessage(UNetConnection* Connection, uint8 MessageType, FInBunch& Bunch) override;`
- L70 _private prototype_ `virtual void OnFailure() override;`
- L71 _private prototype_ `virtual void DestroyBeacon() override;`
- L82 _private prototype_ `bool InitClient(const FOnlineBeaconClientInitParams& Params);` — Initialize the client beacon with connection endpoint Creates the net driver and attempts to connect with the destination @param Params Parameters used for initialization of the client. @return true if connection is being attempted, false otherwise
- L92 _private prototype_ `bool InitClient(FURL& URL);` — Initialize the client beacon with connection endpoint Creates the net driver and attempts to connect with the destination @param URL destination @return true if connection is being attempted, false otherwise
- L99 _private prototype_ `void SetEncryptionData(const FEncryptionData& InEncryptionData);` — Sets the encryption data that will be used for server connections. @param InEncryptionData the encryption data to use, including key and identifier
- L104 _private prototype_ `void SendInitialJoin();` — Send the packet for triggering the initial join
- L111 _private prototype_ `FString GetBeaconType() const;` — Each beacon must have a unique type identifier @return string representing the type of beacon
- L116 _private function_ `virtual void OnConnected()` — A connection has been made and RPC/replication can begin
- L121 _private function_ `FOnHostConnectionFailure& OnHostConnectionFailure()` — Delegate triggered on failures to connect to a host beacon
- L129 _private prototype_ `void SetConnectionState(EBeaconConnectionState NewConnectionState);` — Set the connection state Higher level than the net connection because of the handshaking of the actors @return connection state of the beacon
- L136 _private prototype_ `const FUniqueNetIdRepl& GetUniqueId() const;` — Get the unique id of the user on this connection (server side only) @return unique id of the user on this connection
- L145 _private prototype_ `virtual FString GetLoginOptions(const FUniqueNetIdRepl& PlayerId);` — Get the login options to send the server during login. Typically this is expected to be in the format that UGameplayStatics::ParseOption can parse, i.e. Key1=Value1?Key2=Value2?Key3=Value3 @param PlayerId unique id of the user on this connection @return Login options value to send to server
- L153 _private prototype_ `EBeaconConnectionState GetConnectionState() const;` — Get the connection state Higher level than the net connection because of the handshaking of the actors @return connection state of the beacon
- L161 _private prototype_ `AOnlineBeaconHostObject* GetBeaconOwner() const;` — Get the owner of this beacon actor, some host that is listening for connections (server side only, clients have no access) @return owning host of this actor
- L169 _private prototype_ `void SetBeaconOwner(AOnlineBeaconHostObject* InBeaconOwner);` — Set the owner of this beacon actor, some host that is listening for connections (server side only, clients have no access) @return owning host of this actor
- L176 _private function_ `virtual void SetNetConnection(UNetConnection* NetConnection)` — Associate this beacon with a network connection @param NetConnection connection that the beacon will communicate over
- L185 _protected member_ `TObjectPtr<AOnlineBeaconHostObject> BeaconOwner;` — `UPROPERTY()` — Owning beacon host of this beacon actor (server only)
- L189 _protected member_ `TObjectPtr<UNetConnection> BeaconConnection;` — `UPROPERTY()` — Network connection associated with this beacon client instance
- L193 _protected member_ `EBeaconConnectionState ConnectionState;` — `UPROPERTY()` — State of the connection
- L196 _protected member_ `FOnHostConnectionFailure HostConnectionFailure;` — Delegate for host beacon connection failures
- L199 _protected member_ `FTimerHandle TimerHandle_OnFailure;` — Handle for efficient management of OnFailure timer
- L204 _private prototype_ `FString GetAuthTicketInternal(const FUniqueNetIdRepl& PlayerId);` — Get the auth ticket from OnlineSubsystem for the specified player id
- L207 _private member_ `FEncryptionData EncryptionData;` — Encryption data used when connecting to servers.
- L216 _private prototype_ `void FinalizeEncryptedConnection(const FEncryptionKeyResponse& Response, TWeakObjectPtr<UNetConnection> WeakConnection);` — Setup the connection for encryption with a given key All future packets are expected to be encrypted @param Response response from the game containing its encryption key or an error message @param WeakConnection the connection related to the encryption request
- L223 _private prototype_ `void ClientOnConnected();` — `UFUNCTION(client, reliable)` — Called on the server side to open up the actor channel that will allow RPCs to occur (DO NOT OVERLOAD, implement OnConnected() instead)

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L42 _delegate_ `DECLARE_DELEGATE(FOnHostConnectionFailure);` — Delegate triggered on failures to connect to a host beacon
- L42 _prototype_ `DECLARE_DELEGATE(FOnHostConnectionFailure);` — Delegate triggered on failures to connect to a host beacon
- L229 _function_ `inline const TCHAR* ToString(EBeaconConnectionState Value)`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineBeaconHost.h` (Public)


#### class `AOnlineBeaconHost`  
`class AOnlineBeaconHost : public AOnlineBeacon`  
_L28-219_
- reflection: `UCLASS(MinimalAPI, transient, notplaceable, config=Engine)`
- inherits: `AOnlineBeacon`
- desc: Main actor that listens for side channel communication from another Unreal Engine application The AOnlineBeaconHost listens for connections to route to a registered AOnlineBeaconHostObject The AOnlineBeaconHostObject is responsible for spawning the server version of the AOnlineBeaconClient The AOnlineBeaconHost pairs the two client actors, verifies the validity of the exchange, and accepts/continues the connection
- L30 _private typedef_ `using FNetCloseResult = UE::Net::FNetCloseResult;`
- L37 _public member_ `int32 ListenPort;` — `UPROPERTY(Config)` — Configured listen port for this beacon host
- L44 _public member_ `bool bReuseAddressAndPort = false;` — `UPROPERTY(Config)` — Whether to configure the listening socket to allow reuse of the address and port. If this is true, be sure no other servers can run on the same port, otherwise this can lead to undefined behavior since packets will go to two servers.
- L47 _public prototype_ `virtual void OnNetCleanup(UNetConnection* Connection) override;`
- L51 _public prototype_ `virtual void HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString) override;`
- L55 _public prototype_ `virtual void NotifyControlMessage(UNetConnection* Connection, uint8 MessageType, FInBunch& Bunch) override;`
- L64 _public prototype_ `virtual bool InitHost();` — Initialize the host beacon on a specified port Creates the net driver and begins listening for connections @return true if host was setup correctly, false otherwise
- L71 _public function_ `virtual int32 GetListenPort()` — Get the listen port for this beacon @return beacon listen port
- L78 _public prototype_ `virtual void RegisterHost(AOnlineBeaconHostObject* NewHostObject);` — Register a beacon host and its client actor factory @param NewHostObject new
- L85 _public prototype_ `virtual void UnregisterHost(const FString& BeaconType);` — Unregister a beacon host, making future connections of a given type unresponsive @param BeaconType type of beacon host to unregister
- L94 _public prototype_ `AOnlineBeaconHostObject* GetHost(const FString& BeaconType);` — Get the host responsible for a given beacon type @param BeaconType type of beacon host @return BeaconHost for the given type or NULL if that type is not registered
- L101 _public prototype_ `void DisconnectClient(AOnlineBeaconClient* ClientActor);` — Disconnect a given client from the host @param ClientActor the beacon client to disconnect
- L110 _public prototype_ `virtual AOnlineBeaconClient* GetClientActor(UNetConnection* Connection);` — Get a client beacon actor for a given connection @param Connection connection of interest @return client beacon actor that owns the connection
- L117 _public prototype_ `virtual void RemoveClientActor(AOnlineBeaconClient* ClientActor);` — Remove a client beacon actor from the list of active connections @param ClientActor client beacon actor to remove
- L122 _protected member_ `bool bAuthRequired = false;` — `UPROPERTY(Config)` — Set this to true if you require clients to negotiate auth prior to joining the beacon
- L125 _protected member_ `uint32 MaxAuthTokenSize = 1024;` — `UPROPERTY(Config)`
- L132 _protected prototype_ `DECLARE_DELEGATE_OneParam(FOnAuthenticationVerificationCompleteDelegate, const FOnlineError& );` — Delegate executed when user authentication has completed. @param OnlineError the result of the operation
- L143 _protected prototype_ `virtual bool StartVerifyAuthentication(const FUniqueNetId& PlayerId, const FString& LoginOptions, const FString& AuthenticationToken, const FOnAuthenticationVerificationCompleteDelegate& OnComplete);` — Start verifying an authentication token for a connection. OnAuthenticationVerificationComplete must be called to complete authentication verification. @param PlayerId net id of player to authenticate. @Param LoginOptions all options passed as part of the Login request. @param AuthenticationToken token to use for verification. @Param OnComplete delegate to call once the request for authentication has completed
- L151 _protected prototype_ `virtual bool VerifyJoinForBeaconType(const FUniqueNetId& PlayerId, const FString& BeaconType);` — Verify user authentication once the beacon type is known. @param PlayerId net id of player to authenticate. @Param BeaconType type of beacon to verify the authentication for.
- L160 _private prototype_ `void OnAuthenticationVerificationComplete(UNetConnection* Connection, const FOnlineError& Error);` — Event which must be signaled to complete an authentication verification request. @param NetConnection network connection associated with the authentication challenge. @param Error result of the operation.
- L163 _protected prototype_ `FString GetDebugName(UNetConnection* Connection = nullptr);`
- L187 _private member_ `TMap<UNetConnection*,FConnectionState> ConnectionState;`
- L191 _private member_ `TArray<TObjectPtr<AOnlineBeaconClient>> ClientActors;` — `UPROPERTY()` — List of all client beacon actors with active connections
- L194 _private prototype_ `void OnHelloSequenceComplete(UNetConnection* Connection);` — Sends the welcome control message to the client. Used as a delegate if encryption is being negotiated.
- L195 _private prototype_ `void OnEncryptionResponse(const FEncryptionKeyResponse& Response, TWeakObjectPtr<UNetConnection> WeakConnection);`
- L196 _private prototype_ `void OnConnectionClosed(UNetConnection* Connection);`
- L198 _private prototype_ `bool HandleControlMessage(UNetConnection* Connection, uint8 MessageType, FInBunch& Bunch);`
- L199 _private prototype_ `void FinishHandshake(UNetConnection* Connection, FString BeaconType);`
- L200 _private prototype_ `void SendFailurePacket(UNetConnection* Connection, FNetCloseResult&& CloseReason, const FText& ErrorText);`
- L202 _private prototype_ `void CloseHandshakeConnection(UNetConnection* Connection);`
- L204 _private prototype_ `bool GetConnectionDataForUniqueNetId(const FUniqueNetId& UniqueNetId, UNetConnection*& OutConnection, FConnectionState*& OutConnectionState);`
- L207 _private prototype_ `DECLARE_DELEGATE_RetVal_OneParam(AOnlineBeaconClient*, FOnBeaconSpawned, UNetConnection*);` — Delegate to route a connection attempt to the appropriate beacon host, by type
- L208 _private prototype_ `FOnBeaconSpawned& OnBeaconSpawned(const FString& BeaconType);`
- L211 _private member_ `TMap<FString, FOnBeaconSpawned> OnBeaconSpawnedMapping;` — Mapping of beacon types to the OnBeaconSpawned delegates
- L214 _private prototype_ `DECLARE_DELEGATE_TwoParams(FOnBeaconConnected, AOnlineBeaconClient*, UNetConnection*);` — Delegate to route a connection event to the appropriate beacon host, by type
- L215 _private prototype_ `FOnBeaconConnected& OnBeaconConnected(const FString& BeaconType);`
- L218 _private member_ `TMap<FString, FOnBeaconConnected> OnBeaconConnectedMapping;` — Mapping of beacon types to the OnBeaconConnected delegates

#### struct `AOnlineBeaconHost::FConnectionState`  
`struct FConnectionState`  
_L167-186_
- desc: Connection states used to check against misbehaving connections.
- L169 _public function_ `FConnectionState(const AOnlineBeaconHost& InBeaconHost) : BeaconHost(InBeaconHost)`
- L174 _public prototype_ `~FConnectionState();`
- L176 _public member_ `const AOnlineBeaconHost& BeaconHost;`
- L177 _public member_ `FTimerHandle FinishHandshakeTimerHandle;`
- L178 _public member_ `bool bHasSentHello = false;`
- L179 _public member_ `bool bHasSentChallenge = false;`
- L180 _public member_ `bool bHasSentLogin = false;`
- L181 _public member_ `bool bHasSentWelcome = false;`
- L182 _public member_ `bool bHasSetNetspeed = false;`
- L183 _public member_ `bool bHasAuthenticated = false;`
- L184 _public member_ `bool bHasJoined = false;`
- L185 _public member_ `bool bHasCompletedAck = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L132 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAuthenticationVerificationCompleteDelegate, const FOnlineError& );` — Delegate executed when user authentication has completed. @param OnlineError the result of the operation
- L207 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(AOnlineBeaconClient*, FOnBeaconSpawned, UNetConnection*);` — Delegate to route a connection attempt to the appropriate beacon host, by type
- L214 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnBeaconConnected, AOnlineBeaconClient*, UNetConnection*);` — Delegate to route a connection event to the appropriate beacon host, by type

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineBeaconHostObject.h` (Public)


#### class `AOnlineBeaconHostObject`  
`class AOnlineBeaconHostObject : public AActor`  
_L20-89_
- reflection: `UCLASS(MinimalAPI, transient, config=Engine, notplaceable)`
- inherits: `AActor`
- desc: Base class for any unique beacon connectivity, paired with an AOnlineBeaconClient implementation By defining a beacon type and implementing the ability to spawn unique AOnlineBeaconClients, any two instances of the engine can communicate with each other without officially connecting through normal Unreal networking
- L25 _private prototype_ `FName GetNetDriverName() const;` — @return the name of the net driver associated with this object
- L28 _private prototype_ `EBeaconState::Type GetBeaconState() const;` — Get the state of the beacon (accepting/rejecting connections)
- L31 _private function_ `const FString& GetBeaconType() const` — Get the type of beacon supported by this host
- L34 _private function_ `TSubclassOf<AOnlineBeaconClient> GetClientBeaconActorClass() const` — Simple accessor for client beacon actor class
- L41 _private prototype_ `virtual AOnlineBeaconClient* SpawnBeaconActor(UNetConnection* ClientConnection);` — Each beacon host must be able to spawn the appropriate client beacon actor to communicate with the initiating client @return new client beacon actor that this beacon host knows how to communicate with
- L49 _private prototype_ `virtual void OnClientConnected(AOnlineBeaconClient* NewClientActor, UNetConnection* ClientConnection);` — Delegate triggered when a new client connection is made @param NewClientActor new client beacon actor @param ClientConnection new connection established
- L56 _private prototype_ `virtual void DisconnectClient(AOnlineBeaconClient* ClientActor);` — Disconnect a given client from the host @param ClientActor the beacon client to disconnect
- L63 _private prototype_ `virtual void NotifyClientDisconnected(AOnlineBeaconClient* LeavingClientActor);` — Notification that a client has been disconnected from the host in some way (timeout, client initiated, etc) @param LeavingClientActor actor that has disconnected
- L69 _private prototype_ `virtual void Unregister();` — Called when this class is unregistered by the beacon host Do any necessary cleanup.
- L74 _private function_ `int32 GetNumClientActors() const` — @return the number of connections currently with this beacon host
- L80 _protected member_ `FString BeaconTypeName;` — `UPROPERTY(Transient)` — Custom name for this beacon
- L84 _protected member_ `TSubclassOf<AOnlineBeaconClient> ClientBeaconActorClass;` — `UPROPERTY()` — Class reference for spawning client beacon actor
- L88 _protected member_ `TArray<TObjectPtr<AOnlineBeaconClient>> ClientActors;` — `UPROPERTY()` — List of all client beacon actors with active connections

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineBeaconReservation.h` (Public)


#### struct `FPlayerReservation`  
`struct FPlayerReservation`  
_L10-38_
- reflection: `USTRUCT()`
- desc: A single player reservation
- L14 _public function_ `FPlayerReservation() : bAllowCrossplay(false) , ElapsedTime(0.0f)`
- L21 _public member_ `FUniqueNetIdRepl UniqueId;` — `UPROPERTY(Transient)` — Unique id for this reservation
- L25 _public member_ `FString ValidationStr;` — `UPROPERTY(Transient)` — Info needed to validate user credentials when joining a server
- L29 _public member_ `FString Platform;` — `UPROPERTY(Transient)` — Platform this user is on
- L33 _public member_ `bool bAllowCrossplay;` — `UPROPERTY(Transient)` — Does this player opt in to crossplay
- L37 _public member_ `float ElapsedTime;` — `UPROPERTY(Transient)` — Elapsed time since player made reservation and was last seen

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineSubsystemUtils.h` (Public)


#### class `IOnlineSubsystemUtils`  
`class IOnlineSubsystemUtils`  
_L73-161_
- desc: Interface class for various online utility functions
- L77 _protected function_ `IOnlineSubsystemUtils()` — Hidden on purpose
- L81 _public prototype_ `virtual ~IOnlineSubsystemUtils() = default;`
- L90 _public prototype_ `virtual FName GetOnlineIdentifier(const FWorldContext& WorldContext, const FName Subsystem = NAME_None) const = 0;` — Gets an FName that uniquely identifies an instance of OSS @param WorldContext the worldcontext associated with a particular subsystem @param Subsystem the name of the subsystem @return an FName of format Subsystem:Context_Id in PlayInEditor or Subsystem everywhere else
- L99 _public prototype_ `virtual FName GetOnlineIdentifier(const UWorld* World, const FName Subsystem = NAME_None) const = 0;` — Gets an FName that uniquely identifies an instance of OSS @param World the world to use for context @param Subsystem the name of the subsystem @return an FName of format Subsystem:Context_Id in PlayInEditor or Subsystem everywhere else
- L111 _public prototype_ `virtual FUniqueNetIdPtr CreateForeignUniqueNetId(const FString& Str, FName Type) const = 0;` — Create a TRANSPORT LAYER unique id NOTE: Do NOT Use this for anything other than replication to non native platforms This is NOT a shortcut for creating unique ids @param Str string form an opaque unique net id @param Type name of the online subsystem this unique id belongs to @return unique net id in "transport" format
- L120 _public prototype_ `virtual uint8 GetReplicationHashForSubsystem(FName SubsystemName) const = 0;` — Return the replication hash for a given subsystem @param InSubsystemName name of subsystem to retrieve hash from @return replication hash, or 0 if invalid/unknown
- L129 _public prototype_ `virtual FName GetSubsystemFromReplicationHash(uint8 InHash) const = 0;` — Return the name of the online subsystem associated with this hash @param InHash replication hash for an online subsystem @return name of subsystem this hash belongs to
- L137 _public prototype_ `virtual void SetEngineExternalUIBinding(const FOnExternalUIChangeDelegate& OnExternalUIChangeDelegate) = 0;` — Bind a notification delegate when any subsystem external UI is opened/closed *NOTE* there is only meant to be one delegate needed for this, game code should bind manually @param OnExternalUIChangeDelegate delegate fired when the external UI is opened/closed
- L145 _public prototype_ `virtual bool SupportsOnlinePIE() const = 0;` — @return true if the default platform supports logging in for Play In Editor (PIE)
- L147 _public prototype_ `virtual void SetShouldTryOnlinePIE(bool bShouldTry) = 0;` — Enable/Disable online PIE at runtime
- L149 _public prototype_ `virtual bool IsOnlinePIEEnabled() const = 0;` — @return true if the user has enabled logging in for Play In Editor (PIE)
- L151 _public prototype_ `virtual int32 GetNumPIELogins() const = 0;` — @return the number of logins the user has setup for Play In Editor (PIE)
- L153 _public prototype_ `virtual void GetPIELogins(TArray<FOnlineAccountCredentials>& Logins) = 0;` — @return the array of valid credentials the user has setup for Play In Editor (PIE)
- L159 _public prototype_ `static bool IsOnlinePIEEnabledStatic();` — Static check for whether online PIE is enabled. Safe to call at any point during startup — uses CDO if UObjectInitialized(), falls back to reading INI + command line auth credentials.

#### Free symbols / members of external scopes

- L24 _prototype_ `UAudioComponent* CreateVoiceAudioComponent(uint32 SampleRate, int32 NumChannels);` — @return an initialized audio component specifically for use with VoIP
- L27 _prototype_ `UVoipListenerSynthComponent* CreateVoiceSynthComponent(UWorld* World, uint32 SampleRate);` — @return an initialized Synth component specifically for use with VoIP
- L30 _prototype_ `void ApplyVoiceSettings(UVoipListenerSynthComponent* InSynthComponent, const FVoiceSettings& InSettings);` — Updates InSynthComponent based on InSettings.
- L33 _prototype_ `UWorld* GetWorldForOnline(FName InstanceName);` — @return the world associated with a named online subsystem instance
- L42 _prototype_ `int32 GetPortFromNetDriver(FName InstanceName);` — Try to retrieve the active listen port for a server session @param InstanceName online subsystem instance to query @return the port number currently associated with the GAME net driver
- L44 _prototype_ `int32 GetClientPeerIp(FName InstanceName, const FUniqueNetId& UserId);`
- L55 _prototype_ `uint64 GetBaseVoiceChatTeamId(const UWorld* World);` — Get a 64bit bit base id for a chat room <32bit IP Addr> | <EmptySpace> | <24bit ProcessId> @param World world for context @return 64bit base id for a voice chat room
- L65 _prototype_ `uint64 GetVoiceChatTeamId(uint64 VoiceChatIdBase, uint8 TeamIndex);` — Get a 64bit bit final id for a chat room <32bit IP Addr> | <8bit team index> | <24bit ProcessId> @param VoiceChatIdBase previously retrieved base id @param TeamIndex index for a given team needing a voice chat id @return 64bit id for a voice chat room
- L164 _macro_ `#define IMPLEMENT_GET_INTERFACE(InterfaceType) \` — Macro to handle the boilerplate of accessing the proper online subsystem and getting the requested interface (UWorld version)
- L179 _namespace_ `namespace Online`
- L182 _function_ `static IOnlineSubsystemUtils* GetUtils()` (scope `Online`) — @return the single instance of the online subsystem utils interface
- L200 _function_ `template< typename TModularFeature > inline TModularFeature* GetModularFeature( const FName Type )` (scope `Online`) — Wrapper for IModularFeatures::IsModularFeatureAvailable and IModularFeatures::GetModularFeature @param Type name of the modular feature @return pointer to the modular feature if it is available
- L218 _function_ `static IOnlineSubsystem* GetSubsystem(const UWorld* World, const FName& SubsystemName = NAME_None)` (scope `Online`) — Get the online subsystem for a given service @param World the world to use for context @param SubsystemName - Name of the requested online service @return pointer to the appropriate online subsystem
- L242 _function_ `static bool IsLoaded(const UWorld* World, const FName& SubsystemName = NAME_None)` (scope `Online`) — Determine if the subsystem module for a given interface is already loaded.  Note that modules do not typically initialize the subsystem when the module is loaded. @param World the world to use for context @param SubsystemName name of the requested online service @return true if module for the subsystem is loaded
- L269 _function_ `static bool DoesInstanceExist(const UWorld* World, const FName& SubsystemName = NAME_None)` (scope `Online`) — Determine if the subsystem for a given interface has been instanced @param World the world to use for context @param SubsystemName name of the requested online service @return true if the subsystem has been instanced
- L289 _prototype_ `IMPLEMENT_GET_INTERFACE(Session);` (scope `Online`) — Reimplement all the interfaces of Online.h with support for UWorld accessors
- L290 _prototype_ `IMPLEMENT_GET_INTERFACE(Party);` (scope `Online`)
- L291 _prototype_ `IMPLEMENT_GET_INTERFACE(Chat);` (scope `Online`)
- L292 _prototype_ `IMPLEMENT_GET_INTERFACE(Friends);` (scope `Online`)
- L293 _prototype_ `IMPLEMENT_GET_INTERFACE(User);` (scope `Online`)
- L294 _prototype_ `IMPLEMENT_GET_INTERFACE(SharedCloud);` (scope `Online`)
- L295 _prototype_ `IMPLEMENT_GET_INTERFACE(UserCloud);` (scope `Online`)
- L296 _prototype_ `IMPLEMENT_GET_INTERFACE(Voice);` (scope `Online`)
- L297 _prototype_ `IMPLEMENT_GET_INTERFACE(ExternalUI);` (scope `Online`)
- L298 _prototype_ `IMPLEMENT_GET_INTERFACE(Time);` (scope `Online`)
- L299 _prototype_ `IMPLEMENT_GET_INTERFACE(Identity);` (scope `Online`)
- L300 _prototype_ `IMPLEMENT_GET_INTERFACE(TitleFile);` (scope `Online`)
- L301 _prototype_ `IMPLEMENT_GET_INTERFACE(Entitlements);` (scope `Online`)
- L302 _prototype_ `IMPLEMENT_GET_INTERFACE(Leaderboards);` (scope `Online`)
- L303 _prototype_ `IMPLEMENT_GET_INTERFACE(Achievements);` (scope `Online`)
- L304 _prototype_ `IMPLEMENT_GET_INTERFACE(Presence);` (scope `Online`)
- L305 _prototype_ `IMPLEMENT_GET_INTERFACE(Events);` (scope `Online`)
- L306 _prototype_ `IMPLEMENT_GET_INTERFACE(Stats);` (scope `Online`)
- L307 _prototype_ `IMPLEMENT_GET_INTERFACE(Purchase);` (scope `Online`)

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineSubsystemUtilsModule.h` (Public)


#### class `FOnlineSubsystemUtilsModule`  
`class FOnlineSubsystemUtilsModule : public IModuleInterface`  
_L17-46_
- inherits: `IModuleInterface`
- desc: Online subsystem utils module class Misc functionality where dependency on the engine code is allowed (OnlineSubsystem is not allowed to require engine dependencies)
- L21 _public prototype_ `FOnlineSubsystemUtilsModule();`
- L22 _public prototype_ `virtual ~FOnlineSubsystemUtilsModule();`
- L25 _public function_ `IOnlineSubsystemUtils* GetUtils() const` — @return the singleton utility interface
- L28 _public function_ `UE::Online::IOnlineServicesEngineUtils* GetServicesUtils() const` — @return the singleton utility interface
- L31 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L32 _public prototype_ `virtual void ShutdownModule() override;`
- L34 _public function_ `virtual bool SupportsDynamicReloading() override`
- L42 _private member_ `TUniquePtr<IOnlineSubsystemUtils> SubsystemUtils;` — Online subsystem utilities singleton
- L45 _private member_ `TUniquePtr<UE::Online::IOnlineServicesEngineUtils> OnlineServicesUtils;` — Online Services (OSSv2) utilities singleton

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineSubsystemUtilsPackage.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define PACKAGE_SCOPE public`
- L14 _macro_ `#define PACKAGE_SCOPE protected`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/PartyBeaconClient.h` (Public)


#### enum `EClientRequestType`  
`enum class EClientRequestType : uint8`  
_L21-39_
- reflection: `UENUM()`
- desc: Types of reservation requests that can be made by this beacon
- L24 _public enumerator_ `NonePending` — None pending
- L26 _public enumerator_ `ExistingSessionReservation` — Make a reservation with an existing session
- L28 _public enumerator_ `ReservationUpdate` — Make an update to an existing reservation
- L30 _public enumerator_ `EmptyServerReservation` — Reservation to configure an empty server
- L32 _public enumerator_ `Reconnect` — Simple reconnect (checks for existing reservation)
- L34 _public enumerator_ `Abandon` — Abandon the reservation beacon (game specific handling)
- L36 _public enumerator_ `ReservationRemoveMembers` — Remove members from an existing reservation
- L38 _public enumerator_ `AddOrUpdateReservation` — Add new reservation or Update existing one

#### class `APartyBeaconClient`  
`class APartyBeaconClient : public AOnlineBeaconClient`  
_L94-348_
- reflection: `UCLASS(MinimalAPI, transient, notplaceable, config=Engine)`
- inherits: `AOnlineBeaconClient`
- desc: A beacon client used for making reservations with an existing game session
- L99 _private prototype_ `virtual void BeginDestroy() override;`
- L103 _private prototype_ `virtual void OnConnected() override;`
- L104 _private prototype_ `virtual void OnFailure() override;`
- L118 _private prototype_ `virtual bool RequestReservation(const FString& ConnectInfoStr, const FString& InSessionId, const FUniqueNetIdRepl& RequestingPartyLeader, const TArray<FPlayerReservation>& PartyMembers);` — Sends a request to the remote host to allow the specified members to reserve space in the host's session. Note this request is async. @param ConnectInfoStr the URL of the server that the connection will be made to @param InSessionId Id of the session expected to be found at this destination @param RequestingPartyLeader the leader of this party that will be joining @param PartyMembers the list of players that want to reserve space @return true if the request able to be sent, false if it failed to send
- L130 _private prototype_ `virtual bool RequestReservation(const FOnlineSessionSearchResult& DesiredHost, const FUniqueNetIdRepl& RequestingPartyLeader, const TArray<FPlayerReservation>& PartyMembers);` — Sends a request to the remote host to allow the specified members to reserve space in the host's session. Note this request is async. @param DesiredHost a search result describing the server that the connection will be made to @param RequestingPartyLeader the leader of this party that will be joining @param PartyMembers the list of players that want to reserve space @return true if the request able to be sent, false if it failed to send
- L143 _private prototype_ `virtual bool RequestReservationUpdate(const FUniqueNetIdRepl& RequestingPartyLeader, const TArray<FPlayerReservation>& PlayersToAdd, bool bRemovePlayers = false);` — Sends an update request to the remote host to append additional members to an existing party in the host's session. Note this request is async. ** This version is for existing / established connections only, it will not actually attempt a connection ** @param RequestingPartyLeader the leader of the party that will be updated @param PlayersToAdd the list of players that will be added to the party @return true if the request able to be sent, false if it failed to send
- L156 _private prototype_ `virtual bool RequestReservationUpdate(const FString& ConnectInfoStr, const FString& InSessionId, const FUniqueNetIdRepl& RequestingPartyLeader, const TArray<FPlayerReservation>& PlayersToAdd, bool bRemovePlayers = false);` — Sends an update request to the remote host to append additional members to an existing party in the host's session. Note this request is async. @param ConnectInfoStr the URL of the server that the connection will be made to @param InSessionId Id of the session expected to be found at this destination @param RequestingPartyLeader the leader of the party that will be updated @param PlayersToAdd the list of players that will be added to the party @return true if the request able to be sent, false if it failed to send
- L168 _private prototype_ `virtual bool RequestReservationUpdate(const FOnlineSessionSearchResult& DesiredHost, const FUniqueNetIdRepl& RequestingPartyLeader, const TArray<FPlayerReservation>& PlayersToAdd, bool bRemovePlayers = false);` — Sends an update request to the remote host to append additional members to an existing party in the host's session. Note this request is async. @param DesiredHost a search result describing the server that the connection will be made to @param RequestingPartyLeader the leader of the party that will be updated @param PlayersToAdd the list of players that will be added to the party @return true if the request able to be sent, false if it failed to send
- L183 _private prototype_ `virtual bool RequestAddOrUpdateReservation(const FString& ConnectInfoStr, const FString& InSessionId, const FUniqueNetIdRepl& RequestingPartyLeader, const TArray<FPlayerReservation>& PartyMembers);` — Sends a request to the remote host. If there is an existing reservation it will update it in the host's session. Otherwise it will allow the specified members to reserve space in the host's session. Note this request is async. @param ConnectInfoStr the URL of the server that the connection will be made to @param InSessionId Id of the session expected to be found at this destination @param RequestingPartyLeader the leader of the party that will be updated @param PartyMembers the list of players that will be added to the party @return true if the request able to be sent, false if it failed to send
- L189 _private prototype_ `virtual void CancelReservation();` — Cancel an existing request to the remote host to revoke allocated space on the server. Note this request is async.
- L197 _private prototype_ `virtual void ClientReservationResponse(EPartyReservationResult::Type ReservationResponse);` — `UFUNCTION(client, reliable)` — Response from the host session after making a reservation request @param ReservationResponse response from server
- L205 _private prototype_ `virtual void ClientCancelReservationResponse(EPartyReservationResult::Type ReservationResponse);` — `UFUNCTION(client, reliable)` — Response from the host session after making a cancellation request @param ReservationResponse response from server
- L213 _private prototype_ `virtual void ClientSendReservationUpdates(int32 NumRemainingReservations);` — `UFUNCTION(client, reliable)` — Response from the host session that the reservation count has changed @param NumRemainingReservations number of slots remaining until a full session
- L217 _private prototype_ `virtual void ClientSendReservationFull();` — `UFUNCTION(client, reliable)` — Response from the host session that the reservation is full
- L224 _private function_ `FOnReservationRequestComplete& OnReservationRequestComplete()` — Delegate triggered when a response from the party beacon host has been received @return delegate to handle response from the server
- L231 _private function_ `FOnReservationCountUpdate& OnReservationCountUpdate()` — Delegate triggered when the host indicated a reservation count has changed @param NumRemaining number of slots remaining in the session
- L234 _private function_ `FOnReservationFull& OnReservationFull()` — Delegate triggered when the host indicated the reservation is full
- L239 _private function_ `const FPartyReservation& GetPendingReservation() const` — @return the pending reservation associated with this beacon client
- L244 _protected member_ `FOnReservationRequestComplete ReservationRequestComplete;` — Delegate for reservation request responses
- L246 _protected member_ `FOnReservationCountUpdate ReservationCountUpdate;` — Delegate for reservation count updates
- L249 _protected member_ `FOnReservationFull ReservationFull;` — Delegate for reservation full
- L253 _protected member_ `FString DestSessionId;` — `UPROPERTY()` — Session Id of the destination host
- L256 _protected member_ `FPartyReservation PendingReservation;` — `UPROPERTY()` — Pending reservation that will be sent upon connection with the intended host
- L260 _protected member_ `EClientRequestType RequestType;` — `UPROPERTY()` — Type of request currently being handled by this client beacon
- L264 _protected member_ `bool bPendingReservationSent;` — `UPROPERTY()` — Has the reservation request been delivered
- L267 _protected member_ `bool bCancelReservation;` — `UPROPERTY()` — Has the reservation request been canceled
- L270 _protected member_ `FTimerHandle CancelRPCFailsafe;` — Timer to trigger a cancel reservation request if the server doesn't respond in time
- L273 _protected member_ `FTimerHandle PendingResponseTimerHandle;` — Timers for delaying various responses (debug)
- L274 _protected member_ `FTimerHandle PendingCancelResponseTimerHandle;`
- L275 _protected member_ `FTimerHandle PendingReservationUpdateTimerHandle;`
- L276 _protected member_ `FTimerHandle PendingReservationFullTimerHandle;`
- L279 _protected prototype_ `void ClearTimers(bool bCallFailSafeIfNeeded);` — Clear out all the timer handles listed above
- L281 _protected prototype_ `void OnCancelledFailsafe();` — Delegate triggered if the client doesn't hear from the server in time
- L283 _protected prototype_ `void OnCancelledComplete();` — Delegate triggered when a cancel reservation request is complete
- L286 _protected prototype_ `void ProcessReservationResponse(EPartyReservationResult::Type ReservationResponse);` — Process a response to our RequestReservation request to the server
- L288 _protected prototype_ `void ProcessCancelReservationResponse(EPartyReservationResult::Type ReservationResponse);` — Process a response to our CancelReservation request to the server
- L290 _protected prototype_ `void ProcessReservationUpdate(int32 NumRemainingReservations);` — Process a response from the server with an update to the number of consumed reservations
- L292 _protected prototype_ `void ProcessReservationFull();` — Process a response from the server that the reservation beacon is full
- L301 _protected prototype_ `virtual void ServerReservationRequest(const FString& SessionId, const FPartyReservation& Reservation);` — `UFUNCTION(server, reliable, WithValidation)` — Tell the server about the reservation request being made @param SessionId expected session id on the other end (must match) @param Reservation pending reservation request to make with server
- L310 _protected prototype_ `virtual void ServerUpdateReservationRequest(const FString& SessionId, const FPartyReservation& ReservationUpdate);` — `UFUNCTION(server, reliable, WithValidation)` — Tell the server about the reservation update request being made @param SessionId expected session id on the other end (must match) @param ReservationUpdate pending reservation request to make with server
- L320 _protected prototype_ `virtual void ServerAddOrUpdateReservationRequest(const FString& SessionId, const FPartyReservation& Reservation);` — `UFUNCTION(server, reliable, WithValidation)`
- L329 _protected prototype_ `virtual void ServerRemoveMemberFromReservationRequest(const FString& SessionId, const FPartyReservation& ReservationUpdate);` — `UFUNCTION(server, reliable, WithValidation)` — Tell the server that we are removing members from our reservation @param SessionId expected session id on the other end (must match) @param ReservationUpdate pending reservation request to make with server
- L337 _protected prototype_ `virtual void ServerCancelReservationRequest(const FUniqueNetIdRepl& PartyLeader);` — `UFUNCTION(server, reliable, WithValidation)` — Tell the server to cancel a pending or existing reservation @param PartyLeader id of the party leader for the reservation to cancel
- L347 _protected prototype_ `FTimerHandle DelayResponse(FTimerDelegate& Delegate, float Delay);` — Trigger the given delegate at a later time @param Delegate function to call at a later date @param Delay time to wait before calling function @return handle in the timer system for this entry

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L41 _function_ `inline const TCHAR* ToString(EClientRequestType RequestType)`
- L78 _delegate_ `DECLARE_DELEGATE_OneParam(FOnReservationRequestComplete, EPartyReservationResult::Type );` — Delegate triggered when a response from the party beacon host has been received @param ReservationResponse response from the server
- L78 _prototype_ `DECLARE_DELEGATE_OneParam(FOnReservationRequestComplete, EPartyReservationResult::Type );` — Delegate triggered when a response from the party beacon host has been received @param ReservationResponse response from the server
- L85 _delegate_ `DECLARE_DELEGATE_OneParam(FOnReservationCountUpdate, int32 );` — Delegate triggered when the host indicated a reservation count has changed @param NumRemaining number of slots remaining in the session
- L85 _prototype_ `DECLARE_DELEGATE_OneParam(FOnReservationCountUpdate, int32 );` — Delegate triggered when the host indicated a reservation count has changed @param NumRemaining number of slots remaining in the session
- L88 _delegate_ `DECLARE_DELEGATE(FOnReservationFull);` — Delegate triggered when the host indicated the reservation is full
- L88 _prototype_ `DECLARE_DELEGATE(FOnReservationFull);` — Delegate triggered when the host indicated the reservation is full

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/PartyBeaconHost.h` (Public)


#### class `APartyBeaconHost`  
`class APartyBeaconHost : public AOnlineBeaconHostObject`  
_L54-474_
- reflection: `UCLASS(MinimalAPI, transient, notplaceable, config=Engine)`
- inherits: `AOnlineBeaconHostObject`
- desc: A beacon host used for taking reservations for an existing game session
- L59 _private prototype_ `virtual void PostInitProperties() override;`
- L63 _private prototype_ `virtual void Tick(float DeltaTime) override;`
- L81 _private prototype_ `virtual bool InitHostBeacon(int32 InTeamCount, int32 InTeamSize, int32 InMaxReservations, FName InSessionName, int32 InForceTeamNum = 0, bool bInEnableRemovalRequests = true);` — Initialize the party host beacon @param InTeamCount number of teams to make room for @param InTeamSize size of each team @param InMaxReservation max number of reservations allowed @param InSessionName name of session related to the beacon @param InForceTeamNum team to force players on if applicable (usually only 1 team games) @param bInEnableRemovalRequests allow clients to remove players from beacon. @return true if successful created, false otherwise
- L89 _private prototype_ `virtual bool InitFromBeaconState(UPartyBeaconState* PrevState);` — Initialize the party host beacon from a previous state/configuration all existing reservations and configuration values are preserved @return true if successful created, false otherwise
- L100 _private prototype_ `virtual bool ReconfigureTeamAndPlayerCount(int32 InNumTeams, int32 InNumPlayersPerTeam, int32 InNumReservations);` — Reconfigures the beacon for a different team/player count configuration Allows dedicated server to change beacon parameters after a playlist configuration has been made Does no real checking against current reservations because we assume the UI wouldn't let this party start a gametype if they were too big to fit on a team together @param InNumTeams the number of teams that are expected to join @param InNumPlayersPerTeam the number of players that are allowed to be on each team @param InNumReservations the total number of players to allow to join (if different than team * players)
- L107 _private prototype_ `virtual void SetCompetitiveIntegrity(bool bNewCompetitiveIntegrity);` — Competitive integrity represents how "fair" we need to keep the game. So no friends on other teams, no cross team chat, etc. @param bNewCompetitiveIntegrity The new value for Competitive Integrity
- L114 _private prototype_ `virtual void SetTeamAssignmentMethod(FName NewAssignmentMethod);` — Define the method for assignment new reservations to teams @param NewAssignmentMethod name of the assignment method to use (@see ETeamAssignmentMethod for descriptions)
- L119 _private function_ `UPartyBeaconState* GetState() const` — @return reference to the state of the PartyBeacon
- L126 _private prototype_ `virtual void HandlePlayerLogout(const FUniqueNetIdRepl& PlayerId);` — Notify the beacon of a player logout @param PlayerId UniqueId of player logging out
- L134 _private function_ `virtual int32 GetReservationCount() const` — Get the current reservation count inside the beacon NOTE: This is *NOT* the same as the number of consumed reservations across all parties, just the total number of reservations! @return number of reservations inside the beacon (*NOT* number of consumed reservations)
- L141 _private function_ `virtual int32 GetNumConsumedReservations() const` — Get the number of reservations actually used/consumed across all parties inside the beacon @return the number of actually used reservations across all parties inside the beacon
- L148 _private function_ `virtual int32 GetMaxReservations() const` — Get the maximum number of reservations allowed inside the beacon @return The maximum number of reservations allowed inside the beacon
- L157 _private prototype_ `int32 GetNumPlayersOnTeam(int32 TeamIdx) const;` — Get the number of players on a team across all existing reservations @param TeamIdx team to query @return number of players on the given team
- L166 _private prototype_ `int32 GetTeamForCurrentPlayer(const FUniqueNetId& PlayerId) const;` — Finds the current team assignment of the given player net id. Looks at the reservation entries to find the player. @param PlayerId net id of player to find @return index of team assignment for the given player, INDEX_NONE if not found
- L176 _private prototype_ `int32 GetPlayersOnTeam(int32 TeamIndex, TArray<FUniqueNetIdRepl>& TeamMembers) const;` — Get all the known players on a given team @param TeamIndex valid team index to query @param TeamMembers [out] array of unique ids found to be on the given team @return number of players on team, 0 if invalid
- L183 _private function_ `int32 GetNumTeams() const` — Get the number of teams. @return The number of teams.
- L190 _private function_ `virtual int32 GetMaxPlayersPerTeam() const` — Get the max number of players per team @return The number of players per team
- L197 _private function_ `virtual bool ShouldRespectCompetitiveIntegrity() const` — Competitive integrity represents how "fair" we need to keep the game. So no friends on other teams, no cross team chat, etc. @return Whether or not we should respect competitive integrity
- L205 _private function_ `virtual int32 GetMaxAvailableTeamSize() const` — Determine the maximum team size that can be accommodated based on the current reservation slots occupied. @return maximum team size that is currently available
- L215 _private prototype_ `virtual bool SwapTeams(const FUniqueNetIdRepl& PartyLeader, const FUniqueNetIdRepl& OtherPartyLeader);` — Swap the parties between teams, parties must be of same size @param PartyLeader party 1 to swap @param OtherPartyLeader party 2 to swap @return true if successful, false otherwise
- L225 _private prototype_ `virtual bool ChangeTeam(const FUniqueNetIdRepl& PartyLeader, int32 NewTeamNum);` — Place a party on a new team, party must fit and team must exist @param PartyLeader party to change teams @param NewTeamNum team to change to @return true if successful, false otherwise
- L234 _private prototype_ `virtual bool PlayerHasReservation(const FUniqueNetId& PlayerId) const;` — Does a given player id have an existing reservation @param PlayerId uniqueid of the player to check @return true if a reservation exists, false otherwise
- L245 _private prototype_ `virtual bool GetPlayerValidation(const FUniqueNetId& PlayerId, FString& OutValidation) const;` — Obtain player validation string from party reservation entry @param PlayerId unique id of player to find validation in an existing reservation @param OutValidation [out] validation string used when player requested a reservation @return true if reservation exists for player
- L254 _private prototype_ `virtual float GetSessionTimeoutSecs(const FUniqueNetIdRepl& PlayerId) const;` — Get the session timeout value to use for the target player @param PlayerId unique id of player to find session timeout for @return The value to sue as the session timeout
- L264 _private prototype_ `bool GetPartyLeader(const FUniqueNetIdRepl& InPartyMemberId, FUniqueNetIdRepl& OutPartyLeaderId) const;` — Get the party leader for a given unique id @param InPartyMemberId valid party member of some reservation looking for its leader @param OutPartyLeaderId valid party leader id for the given party member if found, invalid if function returns false @return true if a party leader was found for a given user id, false otherwise
- L273 _private prototype_ `virtual EPartyReservationResult::Type AddPartyReservation(const FPartyReservation& ReservationRequest);` — Attempts to add a party reservation to the beacon @param ReservationRequest reservation attempt @return add attempt result
- L284 _private prototype_ `virtual EPartyReservationResult::Type UpdatePartyReservation(const FPartyReservation& ReservationUpdateRequest, bool bIsRemovingMembers);` — Updates an existing party reservation on the beacon An existing reservation for this party leader must already exist @param ReservationUpdateRequest reservation update information (doesn't need existing party members, simply a delta) @param bIsRemovingMembers set to true if we wish to remove these members from the reservation instead of adding) @return update attempt result
- L291 _private prototype_ `virtual EPartyReservationResult::Type RemovePartyReservation(const FUniqueNetIdRepl& PartyLeader);` — Attempts to remove a party reservation from the beacon @param PartyLeader reservation leader
- L300 _private prototype_ `void RegisterAuthTicket(const FUniqueNetIdRepl& InPartyMemberId, const FString& InAuthTicket);` — Register user auth ticket with the reservation system Must have an existing reservation entry @param InPartyMemberId id of player logging in @param InAuthTicket auth ticket reported by the user
- L309 _private prototype_ `virtual void UpdatePartyLeader(const FUniqueNetIdRepl& InPartyMemberId, const FUniqueNetIdRepl& NewPartyLeaderId);` — Update party leader for a given player with the reservation beacon (needed when party leader leaves, reservation beacon is in a temp/bad state until someone updates this) @param InPartyMemberId party member making the update @param NewPartyLeaderId id of new leader
- L318 _private prototype_ `virtual void ProcessReservationRequest(APartyBeaconClient* Client, const FString& SessionId, const FPartyReservation& ReservationRequest);` — Handle a reservation request received from an incoming client @param Client client beacon making the request @param SessionId id of the session that is being checked @param ReservationRequest payload of request
- L328 _private prototype_ `virtual void ProcessReservationUpdateRequest(APartyBeaconClient* Client, const FString& SessionId, const FPartyReservation& ReservationUpdateRequest, bool bIsRemovingMember);` — Handle a reservation update request received from an incoming client @param Client client beacon making the request @param SessionId id of the session that is being checked @param ReservationRequest payload of the update request (existing reservation for party leader required) @param bRemovingMembers true if this update is removing members, false if adding members.
- L338 _private prototype_ `virtual void ProcessReservationAddOrUpdateRequest(APartyBeaconClient* Client, const FString& SessionId, const FPartyReservation& ReservationRequest);` — Handle a reservation add or update request depending on reservation existance received from an incoming client @param Client client beacon making the request @param SessionId id of the session that is being checked @param ReservationRequest payload of the update request (existing reservation for party leader required)
- L345 _private prototype_ `virtual void ProcessCancelReservationRequest(APartyBeaconClient* Client, const FUniqueNetIdRepl& PartyLeader);` — Handle a reservation cancellation request received from an incoming client @param Client client beacon making the request @param PartyLeader reservation leader
- L354 _private prototype_ `virtual bool HasCrossplayOptOutReservation() const;` — @return true if there are cross play restrictions, false otherwise
- L364 _private prototype_ `virtual int32 GetReservationPlatformCount(const FString& InPlatform, bool bIncludeMappedPlatforms = false) const;` — Get a count of all players for a given platform @param InPlatform platform to get a count for @param bIncludeMappedPlatforms true if we should include platforms that map to InPlatform (See FPartyBeaconCrossplayPlatformMapping) @return number of players for a given platform
- L369 _private function_ `FOnReservationUpdate& OnReservationsFull()` — Delegate fired when a the beacon host detects that all reservations are full
- L374 _private function_ `FOnReservationUpdate& OnReservationChanged()` — Delegate fired when a the beacon host detects a reservation addition/removal
- L379 _private function_ `FOnNewPlayerAdded& OnNewPlayerAdded()` — Delegate fired when the beacon host adds a new player
- L384 _private function_ `FOnCancelationReceived& OnCancelationReceived()` — Delegate fired when a the beacon host cancels a reservation
- L389 _private function_ `FOnDuplicateReservation& OnDuplicateReservation()` — Delegate fired when a the beacon detects a duplicate reservation
- L394 _private function_ `FOnValidatePlayers& OnValidatePlayers()` — Delegate called when the beacon gets any request, allowing the owner to validate players at a higher level (bans,etc)
- L399 _private prototype_ `virtual void DumpReservations() const;` — Output current state of reservations to log
- L404 _private function_ `bool IsValidationStrRequired() const` — Do party members require validation strings.
- L406 _private prototype_ `virtual bool IsPlayerActive(const FUniqueNetIdRepl& PlayerId) const;`
- L412 _protected member_ `TObjectPtr<UPartyBeaconState> State;` — `UPROPERTY()` — State of the beacon
- L415 _protected member_ `FOnReservationUpdate ReservationsFull;` — Delegate fired when the beacon indicates all reservations are taken
- L417 _protected member_ `FOnReservationUpdate ReservationChanged;` — Delegate fired when the beacon indicates a reservation add/remove
- L419 _protected member_ `FOnCancelationReceived CancelationReceived;` — Delegate fired when the beacon indicates a reservation cancellation
- L421 _protected member_ `FOnDuplicateReservation DuplicateReservation;` — Delegate fired when the beacon detects a duplicate reservation
- L423 _protected member_ `FOnNewPlayerAdded NewPlayerAddedDelegate;` — Delegate fired when reservation has been added
- L425 _protected member_ `FOnValidatePlayers ValidatePlayers;` — Delegate fired when asking the beacon owner if this reservation is legit
- L429 _protected member_ `bool bLogoutOnSessionTimeout;` — `UPROPERTY(Config)` — Do the timeouts below cause a player to be removed from the reservation list
- L432 _protected member_ `bool bIsValidationStrRequired;` — `UPROPERTY(Config)` — Do party members require validation strings.
- L435 _protected member_ `float SessionTimeoutSecs;` — `UPROPERTY(Transient, Config)` — Seconds that can elapse before a reservation is removed due to player not being registered with the session
- L438 _protected member_ `float TravelSessionTimeoutSecs;` — `UPROPERTY(Transient, Config)` — Seconds that can elapse before a reservation is removed due to player not being registered with the session during a travel
- L443 _protected function_ `virtual TSubclassOf<UPartyBeaconState> GetPartyBeaconHostClass() const` — @return the class of the state object inside this beacon
- L448 _protected prototype_ `void SendReservationUpdates();` — Update clients with current reservation information
- L455 _protected prototype_ `void NewPlayerAdded(const FPlayerReservation& NewPlayer);` — Handle a newly added player @param NewPlayer reservation of newly joining player
- L462 _protected prototype_ `void PlayerRemoved(const FPlayerReservation& RemovedPlayer);` — Handle a newly removed player @param NewPlayer reservation of newly removed player
- L471 _protected prototype_ `bool DoesSessionMatch(const FString& SessionId) const;` — Does the session match the one associated with this beacon @param SessionId session to compare @return true if the session matches, false otherwise
- L473 _protected prototype_ `void NotifyReservationEventNextFrame(FOnReservationUpdate& ReservationEvent);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L19 _delegate_ `DECLARE_DELEGATE(FOnReservationUpdate);` — Delegate type for handling reservation additions/removals, or full events
- L19 _prototype_ `DECLARE_DELEGATE(FOnReservationUpdate);` — Delegate type for handling reservation additions/removals, or full events
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCancelationReceived, const FUniqueNetId&);` — Delegate fired when a the beacon host has been told to cancel a reservation @param PartyLeader leader of the canceled reservation
- L26 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCancelationReceived, const FUniqueNetId&);` — Delegate fired when a the beacon host has been told to cancel a reservation @param PartyLeader leader of the canceled reservation
- L33 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNewPlayerAdded, const FPlayerReservation&);` — Delegate fired when a the beacon host has added a new player @param PlayerId Player who reservation has been made for.
- L33 _prototype_ `DECLARE_DELEGATE_OneParam(FOnNewPlayerAdded, const FPlayerReservation&);` — Delegate fired when a the beacon host has added a new player @param PlayerId Player who reservation has been made for.
- L41 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnValidatePlayers, const TArray<FPlayerReservation>&);` — Delegate called when the beacon gets any request, allowing the owner to validate players at a higher level (bans,etc) @param PartyMembers players making up the reservation @return true if these players are ok to join
- L41 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnValidatePlayers, const TArray<FPlayerReservation>&);` — Delegate called when the beacon gets any request, allowing the owner to validate players at a higher level (bans,etc) @param PartyMembers players making up the reservation @return true if these players are ok to join
- L48 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDuplicateReservation, const FPartyReservation&);` — Delegate fired when a the beacon host detects a duplicate reservation @param PartyReservation reservation that is found to be duplicated
- L48 _prototype_ `DECLARE_DELEGATE_OneParam(FOnDuplicateReservation, const FPartyReservation&);` — Delegate fired when a the beacon host detects a duplicate reservation @param PartyReservation reservation that is found to be duplicated

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/PartyBeaconState.h` (Public)


#### enum `EPartyReservationResult::Type`  
`enum Type : int`  
_L16-52_
- L19 _public enumerator_ `NoResult` — Empty state.
- L21 _public enumerator_ `RequestPending` — Pending request due to async operation, server will contact client shortly.
- L23 _public enumerator_ `GeneralError` — An unknown error happened.
- L25 _public enumerator_ `PartyLimitReached` — All available reservations are booked.
- L27 _public enumerator_ `IncorrectPlayerCount` — Wrong number of players to join the session.
- L29 _public enumerator_ `RequestTimedOut` — No response from the host.
- L31 _public enumerator_ `ReservationDuplicate` — Already have a reservation entry for the requesting party leader.
- L33 _public enumerator_ `ReservationNotFound` — Couldn't find the party leader specified for a reservation update request.
- L35 _public enumerator_ `ReservationAccepted` — Space was available and it's time to join.
- L37 _public enumerator_ `ReservationDenied` — The beacon is paused and not accepting new connections.
- L39 _public enumerator_ `ReservationDenied_CrossPlayRestriction` — Some kind of cross play restriction prevents this party from joining
- L41 _public enumerator_ `ReservationDenied_Banned` — This player is banned.
- L43 _public enumerator_ `ReservationRequestCanceled` — The reservation request was canceled before being sent.
- L45 _public enumerator_ `ReservationInvalid` — The reservation was rejected because it was badly formed
- L47 _public enumerator_ `BadSessionId` — The reservation was rejected because this was the wrong session
- L49 _public enumerator_ `ReservationDenied_ContainsExistingPlayers` — The reservation contains players already in this game
- L51 _public enumerator_ `ReservationDenied_ValidationFailed` — The reservation was rejected because it failed additional, project-specific validation

#### struct `FPartyReservation`  
`struct FPartyReservation`  
_L177-218_
- reflection: `USTRUCT()`
- desc: A whole party reservation
- L181 _public function_ `FPartyReservation() : TeamNum(INDEX_NONE)`
- L187 _public member_ `int32 TeamNum;` — `UPROPERTY(Transient)` — Team assigned to this party
- L191 _public member_ `FUniqueNetIdRepl PartyLeader;` — `UPROPERTY(Transient)` — Player initiating the request
- L195 _public member_ `TArray<FPlayerReservation> PartyMembers;` — `UPROPERTY(Transient)` — All party members (including party leader) in the reservation
- L199 _public member_ `TArray<FPlayerReservation> RemovedPartyMembers;` — `UPROPERTY(Transient)` — Keeping a record of all logged out players from this reservation.
- L200 _public prototype_ `void RemovePartyMemberAtIndex(int32 Idx);`
- L201 _public prototype_ `int32 RemoveAllPartyMembers(const FPlayerReservation& OtherRes);`
- L204 _public prototype_ `bool IsValid(bool bIsValidationStrRequired=true) const;` — Is this data well formed
- L207 _public prototype_ `void Dump() const;` — Dump this reservation to log
- L208 _public prototype_ `void DumpUniqueIdsOnly() const;`
- L217 _public prototype_ `bool CanPlayerMigrateFromReservation(const FPartyReservation& Other) const;` — Checks if a player from a different reservation can migrate to this reservation For example, TeamNum must match @param Other the other reservation the player is in @return true if the player can migrate, false if not

#### struct `FPartyBeaconCrossplayPlatformMapping`  
`struct FPartyBeaconCrossplayPlatformMapping`  
_L222-234_
- reflection: `USTRUCT()`
- desc: Platform mapping for crossplay checks
- L228 _public member_ `FString PlatformName;` — `UPROPERTY()` — Platform name (eg WIN)
- L231 _public member_ `FString PlatformType;` — `UPROPERTY()` — Platform type the name is mapped to (eg PlatformName=Win, PlatformType=OTHER)
- L233 _public function_ `bool operator==(const FString& InPlatformName)`

#### class `UPartyBeaconState`  
`class UPartyBeaconState : public UObject`  
_L240-650_
- reflection: `UCLASS(MinimalAPI, transient, config=Engine)`
- inherits: `UObject`
- desc: A beacon host used for taking reservations for an existing game session
- L255 _private prototype_ `virtual bool InitState(int32 InTeamCount, int32 InTeamSize, int32 InMaxReservations, FName InSessionName, int32 InForceTeamNum, bool bEnableRemovalRequests);` — Initialize this state object @param InTeamCount number of teams to make room for @param InTeamSize size of each team @param InMaxReservation max number of reservations allowed @param InSessionName name of session related to the beacon @param InForceTeamNum team to force players on if applicable (usually only 1 team games) @return true if successful created, false otherwise
- L267 _private prototype_ `virtual bool ReconfigureTeamAndPlayerCount(int32 InNumTeams, int32 InNumPlayersPerTeam, int32 InNumReservations);` — Reconfigures the beacon for a different team/player count configuration Allows dedicated server to change beacon parameters after a playlist configuration has been made Does no real checking against current reservations because we assume the UI wouldn't let this party start a gametype if they were too big to fit on a team together @param InNumTeams the number of teams that are expected to join @param InNumPlayersPerTeam the number of players that are allowed to be on each team @param InNumReservations the total number of players to allow to join (if different than team * players)
- L274 _private prototype_ `virtual void SetCompetitiveIntegrity(bool bNewCompetitiveIntegrity);` — Competitive integrity represents how "fair" we need to keep the game. So no friends on other teams, no cross team chat, etc. @param bNewCompetitiveIntegrity New value for Competitive integrity
- L281 _private prototype_ `virtual void SetTeamAssignmentMethod(FName NewAssignmentMethod);` — Define the method for assignment new reservations to teams @param NewAssignmentMethod name of the assignment method to use (@see ETeamAssignmentMethod for descriptions)
- L290 _private prototype_ `virtual bool AddReservation(const FPartyReservation& ReservationRequest);` — Add a reservation to the beacon state, tries to assign a team @param ReservationRequest reservation to possibly add to this state @return true if successful, false otherwise
- L299 _private prototype_ `virtual bool RemoveReservation(const FUniqueNetIdRepl& PartyLeader);` — Remove an entire reservation from this state object @param PartyLeader leader holding the reservation for the party @return true if successful, false if reservation not found
- L308 _private prototype_ `void RegisterAuthTicket(const FUniqueNetIdRepl& InPartyMemberId, const FString& InAuthTicket);` — Register user auth ticket with the reservation system Must have an existing reservation entry @param InPartyMemberId id of player logging in @param InAuthTicket auth ticket reported by the user
- L317 _private prototype_ `virtual void UpdatePartyLeader(const FUniqueNetIdRepl& InPartyMemberId, const FUniqueNetIdRepl& NewPartyLeaderId);` — Update party leader for a given player with the reservation beacon (needed when party leader leaves, reservation beacon is in a temp/bad state until someone updates this) @param InPartyMemberId party member making the update @param PartyLeaderId id of new leader
- L327 _private prototype_ `virtual bool SwapTeams(const FUniqueNetIdRepl& PartyLeader, const FUniqueNetIdRepl& OtherPartyLeader);` — Swap the parties between teams, parties must be able to fit on other team after swap @param PartyLeader party 1 to swap @param OtherPartyLeader party 2 to swap @return true if successful, false otherwise
- L337 _private prototype_ `virtual bool ChangeTeam(const FUniqueNetIdRepl& PartyLeader, int32 NewTeamNum);` — Place a party on a new team, party must fit and team must exist @param PartyLeader party to change teams @param NewTeamNum team to change to @return true if successful, false otherwise
- L346 _private prototype_ `virtual bool RemovePlayer(const FUniqueNetIdRepl& PlayerId);` — Remove a single player from their party's reservation PlayerId player to remove @return true if player found and removed, false otherwise
- L351 _private function_ `virtual FName GetSessionName() const` — @return the name of the session associated with this beacon state
- L356 _private function_ `virtual TArray<FPartyReservation>& GetReservations()` — @return all reservations in this beacon state
- L365 _private prototype_ `virtual int32 GetExistingReservation(const FUniqueNetIdRepl& PartyLeader) const;` — Get an existing reservation for a given party @param PartyLeader UniqueId of party leader for a reservation @return index of reservation, INDEX_NONE otherwise
- L374 _private prototype_ `virtual int32 GetExistingReservationContainingMember(const FUniqueNetIdRepl& PartyMember) const;` — Get an existing reservation containing a given party member @param PartyMember UniqueId of party member for a reservation @return index of reservation, INDEX_NONE otherwise
- L382 _private function_ `virtual int32 GetReservationCount() const` — Get the current reservation count inside the beacon this is NOT the number of players in the game @return number of consumed reservations
- L387 _private function_ `virtual int32 GetMaxReservations() const` — @return the total number of reservations allowed
- L392 _private function_ `virtual int32 GetRemainingReservations() const` — @return the amount of space left in the beacon
- L397 _private function_ `virtual int32 GetNumConsumedReservations() const` — @return the number of actually used reservations across all parties
- L406 _private prototype_ `virtual bool DoesReservationFit(const FPartyReservation& ReservationRequest) const;` — Determine if this reservation fits all rules for fitting in the game @param ReservationRequest reservation to test for @return true if reservation can be added to this state, false otherwise
- L416 _private prototype_ `virtual bool DoesModifiedReservationFit(const FPartyReservation& ExistingReservation, const TArray<FPlayerReservation>& NewPlayers) const;` — Determine if this reservation fits all rules for fitting in the game @param ExistingReservation reservation to test for @param NewPlayers players requested to be added @return true if reservation can be modified to fit this state, false otherwise
- L421 _private function_ `virtual bool IsBeaconFull() const` — @return true if the beacon is currently at max capacity
- L428 _private function_ `virtual int32 GetNumTeams() const` — Get the number of teams. @return The number of teams.
- L435 _private function_ `virtual int32 GetMaxPlayersPerTeam() const` — Get the max number of players per team @return The number of player per team
- L442 _private function_ `virtual bool ShouldRespectCompetitiveIntegrity() const` — Competitive integrity represents how "fair" we need to keep the game. So no friends on other teams, no cross team chat, etc. @return Whether we should respect competitive integrity
- L450 _private prototype_ `virtual int32 GetMaxAvailableTeamSize() const;` — Determine the maximum team size that can be accommodated based on the current reservation slots occupied. @return maximum team size that is currently available
- L459 _private prototype_ `virtual int32 GetNumPlayersOnTeam(int32 TeamIdx) const;` — Get the number of current players on a given team. @param TeamIdx team of interest @return The number of teams.
- L468 _private prototype_ `virtual int32 GetTeamForCurrentPlayer(const FUniqueNetId& PlayerId) const;` — Get the team index for a given player @param PlayerId uniqueid for the player of interest @return team index for the given player, INDEX_NONE otherwise
- L475 _private prototype_ `virtual int32 GetReservationTeamCount() const;` — Get the amount of teams used by reservations @return The number of teams that are used by reservations
- L485 _private prototype_ `int32 GetPlayersOnTeam(int32 TeamIndex, TArray<FUniqueNetIdRepl>& TeamMembers) const;` — Get all the known players on a given team @param TeamIndex valid team index to query @param TeamMembers [out] array of unique ids found to be on the given team @return number of players on team, 0 if invalid
- L494 _private prototype_ `virtual bool PlayerHasReservation(const FUniqueNetId& PlayerId) const;` — Does a given player id have an existing reservation @param PlayerId uniqueid of the player to check @return true if a reservation exists, false otherwise
- L505 _private prototype_ `virtual bool UpdateMemberPlatform(const FUniqueNetIdRepl& PartyMember, const FString& PlatformName);` — Updates the platform on an existing reservation (Used when MMS does not set a platform when handing out a match assignment) @param PlayerId uniqueid of the player to update @param PlatformName platform to set new player as using @return true if a reservation exists, false otherwise
- L516 _private prototype_ `virtual bool GetPlayerValidation(const FUniqueNetId& PlayerId, FString& OutValidation) const;` — Obtain player validation string from party reservation entry @param PlayerId unique id of player to find validation in an existing reservation @param OutValidation [out] validation string used when player requested a reservation @return true if reservation exists for player
- L526 _private prototype_ `virtual bool GetPartyLeader(const FUniqueNetIdRepl& InPartyMemberId, FUniqueNetIdRepl& OutPartyLeaderId) const;` — Get the party leader for a given unique id @param InPartyMemberId valid party member of some reservation looking for its leader @param OutPartyLeaderId valid party leader id for the given party member if found, invalid if function returns false @return true if a party leader was found for a given user id, false otherwise
- L531 _private prototype_ `virtual void InitTeamArray();` — Randomly assign a team for the reservation configuring the beacon
- L539 _private prototype_ `virtual bool AreTeamsAvailable(const FPartyReservation& ReservationRequest) const;` — Determine if there are any teams that can fit the current party request. @param ReservationRequest reservation request to fit @return true if there are teams available, false otherwise
- L548 _private prototype_ `virtual bool CrossPlayAllowed(const FPartyReservation& ReservationRequest) const;` — Perform a cross play compatible check for the new reservation against existing reservations @param ReservationRequest new reservation to compare @return true if there are no cross play restrictions, false otherwise
- L553 _private prototype_ `virtual bool HasCrossplayOptOutReservation() const;` — @return true if there are cross play restrictions, false otherwise
- L563 _private prototype_ `virtual int32 GetReservationPlatformCount(const FString& InPlatform, bool bIncludeMappedPlatforms) const;` — Get a count of all players for a given platform @param InPlatform platform to get a count for @param bIncludeMappedPlatforms true if we should include platforms that map to InPlatform (See FPartyBeaconCrossplayPlatformMapping) @return number of players for a given platform
- L572 _private prototype_ `virtual int32 GetTeamAssignment(const FPartyReservation& Party);` — Determine the team number for the given party reservation request. Uses the list of current reservations to determine what teams have open slots. @param PartyRequest the party reservation request received from the client beacon @return index of the team to assign to all members of this party
- L577 _private prototype_ `virtual void DumpReservations() const;` — Output current state of reservations to log
- L587 _private function_ `virtual bool ValidateNewPartyReservation(const FPartyReservation& ReservationRequest)` — Allows child classes to add extra validation when a new reservation request comes in, for example to validate the new players are allowed in based on privacy settings @param ReservationRequest The new reservation that will be added to the beacon's list of reservations @return True if the players in the reservation are allowed in the session
- L593 _protected member_ `FName SessionName;` — `UPROPERTY(Transient)` — Session tied to the beacon
- L596 _protected member_ `int32 NumConsumedReservations;` — `UPROPERTY(Transient)` — Number of currently consumed reservations
- L599 _protected member_ `int32 MaxReservations;` — `UPROPERTY(Transient)` — Maximum allowed reservations
- L602 _protected member_ `int32 NumTeams;` — `UPROPERTY(Transient)` — Number of teams in the game
- L605 _protected member_ `int32 NumPlayersPerTeam;` — `UPROPERTY(Transient)` — Number of players on each team for balancing
- L608 _protected member_ `FName TeamAssignmentMethod;` — `UPROPERTY(Transient)` — Team assignment method
- L611 _protected member_ `int32 ReservedHostTeamNum;` — `UPROPERTY(Transient)` — Team that the host has been assigned to
- L614 _protected member_ `int32 ForceTeamNum;` — `UPROPERTY(Transient)` — Team that everyone is forced to in single team games
- L617 _protected member_ `bool bRestrictCrossConsole;` — `UPROPERTY(Config)` — Are multiple consoles types allowed to play together
- L620 _protected member_ `TArray<FString> PlatformCrossplayRestrictions;` — `UPROPERTY(Config)` — Platform crossplay restrictions.  Expected in the format "Plat1=Plat2,Plat3" to indicate Plat1 is considered crossplay with Plat2 and Plat3
- L622 _protected member_ `TArray<FPartyBeaconCrossplayPlatformMapping> PlatformTypeMapping;` — `UPROPERTY(Config)`
- L625 _protected member_ `bool bEnableRemovalRequests;` — `UPROPERTY(Transient)` — Process requests from clients to remove players from beacon
- L628 _protected member_ `bool bRespectCompetitiveIntegrity;` — `UPROPERTY(Transient)` — Competitive integrity represents how "fair" we need to keep the game. So no friends on other teams, no cross team chat, etc.
- L632 _protected member_ `TArray<FPartyReservation> Reservations;` — `UPROPERTY(Transient)` — Current reservations in the system
- L634 _protected member_ `TArray< FUniqueNetIdPtr > PlayersPendingJoin;` — Players that are expected to join shortly
- L641 _protected prototype_ `virtual void BestFitTeamAssignmentJiggle();` — Arrange reservations to make the most room available on a single team allowing larger parties to fit into this session Since teams change, this shouldn't be used after the teams have been set in the game logic
- L647 _protected prototype_ `void SanityCheckReservations(const bool bIgnoreEmptyReservations) const;` — Check that our reservations are in a good state @param bIgnoreEmptyReservations Whether we want to ignore empty reservations or not (because we intend to clean them up later)

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPartyBeacon, Log, All);`
- L14 _namespace_ `namespace EPartyReservationResult`
- L55 _namespace_ `namespace EPartyReservationResult`
- L58 _function_ `inline const TCHAR* ToString(EPartyReservationResult::Type SessionType)` (scope `EPartyReservationResult`) — @return the stringified version of the enum passed in
- L130 _function_ `inline FText GetDisplayString(EPartyReservationResult::Type Response)` (scope `EPartyReservationResult`)
- L163 _namespace_ `namespace ETeamAssignmentMethod`
- L166 _externvar_ `extern const FName Smallest;` (scope `ETeamAssignmentMethod`) — Fill smallest team first
- L168 _externvar_ `extern const FName BestFit;` (scope `ETeamAssignmentMethod`) — Optimize for best fit within the number of available reservations
- L170 _externvar_ `extern const FName Random;` (scope `ETeamAssignmentMethod`) — Assign random team
- L172 _externvar_ `extern const FName Manual;` (scope `ETeamAssignmentMethod`) — Manually assign the team

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/SpectatorBeaconClient.h` (Public)


#### enum `ESpectatorClientRequestType`  
`enum class ESpectatorClientRequestType : uint8`  
_L21-35_
- reflection: `UENUM()`
- desc: Types of reservation requests that can be made by this beacon
- L24 _public enumerator_ `NonePending` — None pending
- L26 _public enumerator_ `ExistingSessionReservation` — Make a reservation with an existing session
- L28 _public enumerator_ `ReservationUpdate` — Make an update to an existing reservation
- L30 _public enumerator_ `EmptyServerReservation` — Reservation to configure an empty server
- L32 _public enumerator_ `Reconnect` — Simple reconnect (checks for existing reservation)
- L34 _public enumerator_ `Abandon` — Abandon the reservation beacon (game specific handling)

#### class `ASpectatorBeaconClient`  
`class ASpectatorBeaconClient : public AOnlineBeaconClient`  
_L86-259_
- reflection: `UCLASS(MinimalAPI, transient, notplaceable, config = Engine)`
- inherits: `AOnlineBeaconClient`
- desc: A beacon client used for making reservations with an existing game session
- L91 _private prototype_ `virtual void BeginDestroy() override;`
- L95 _private prototype_ `virtual void OnConnected() override;`
- L96 _private prototype_ `virtual void OnFailure() override;`
- L110 _private prototype_ `virtual bool RequestReservation(const FString& ConnectInfoStr, const FString& InSessionId, const FUniqueNetIdRepl& RequestingSpectator, const FPlayerReservation& Reservation);` — Sends a request to the remote host to allow the specified members to reserve space in the host's session. Note this request is async. @param ConnectInfoStr the URL of the server that the connection will be made to @param InSessionId Id of the session expected to be found at this destination @param RequestingSpectator the spectator that will be joining @param Reservation the reservation for the spectator who wants to reserve space @return true if the request able to be sent, false if it failed to send
- L122 _private prototype_ `virtual bool RequestReservation(const FOnlineSessionSearchResult& DesiredHost, const FUniqueNetIdRepl& RequestingSpectator, const FPlayerReservation& Reservation);` — Sends a request to the remote host to allow the specified members to reserve space in the host's session. Note this request is async. @param DesiredHost a search result describing the server that the connection will be made to @param RequestingSpectator the spectator that will be joining @param Reservation the reservation for the spectator who wants to reserve space @return true if the request able to be sent, false if it failed to send
- L128 _private prototype_ `virtual void CancelReservation();` — Cancel an existing request to the remote host to revoke allocated space on the server. Note this request is async.
- L136 _private prototype_ `virtual void ClientReservationResponse(ESpectatorReservationResult::Type ReservationResponse);` — `UFUNCTION(client, reliable)` — Response from the host session after making a reservation request @param ReservationResponse response from server
- L144 _private prototype_ `virtual void ClientCancelReservationResponse(ESpectatorReservationResult::Type ReservationResponse);` — `UFUNCTION(client, reliable)` — Response from the host session after making a cancellation request @param ReservationResponse response from server
- L152 _private prototype_ `virtual void ClientSendReservationUpdates(int32 NumRemainingReservations);` — `UFUNCTION(client, reliable)` — Response from the host session that the reservation count has changed @param NumRemainingReservations number of slots remaining until a full session
- L156 _private prototype_ `virtual void ClientSendReservationFull();` — `UFUNCTION(client, reliable)` — Response from the host session that the reservation is full
- L163 _private function_ `FOnSpectatorReservationRequestComplete& OnReservationRequestComplete()` — Delegate triggered when a response from the spectator beacon host has been received @return delegate to handle response from the server
- L170 _private function_ `FOnReservationCountUpdate& OnReservationCountUpdate()` — Delegate triggered when the host indicated a reservation count has changed @param NumRemaining number of slots remaining in the session
- L173 _private function_ `FOnReservationFull& OnReservationFull()` — Delegate triggered when the host indicated the reservation is full
- L178 _private function_ `const FSpectatorReservation& GetPendingReservation() const` — @return the pending reservation associated with this beacon client
- L183 _protected member_ `FOnSpectatorReservationRequestComplete ReservationRequestComplete;` — Delegate for reservation request responses
- L185 _protected member_ `FOnReservationCountUpdate ReservationCountUpdate;` — Delegate for reservation count updates
- L188 _protected member_ `FOnReservationFull ReservationFull;` — Delegate for reservation full
- L192 _protected member_ `FString DestSessionId;` — `UPROPERTY()` — Session Id of the destination host
- L195 _protected member_ `FSpectatorReservation PendingReservation;` — `UPROPERTY()` — Pending reservation that will be sent upon connection with the intended host
- L199 _protected member_ `ESpectatorClientRequestType RequestType;` — `UPROPERTY()` — Type of request currently being handled by this client beacon
- L203 _protected member_ `bool bPendingReservationSent;` — `UPROPERTY()` — Has the reservation request been delivered
- L206 _protected member_ `bool bCancelReservation;` — `UPROPERTY()` — Has the reservation request been canceled
- L209 _protected member_ `FTimerHandle CancelRPCFailsafe;` — Timer to trigger a cancel reservation request if the server doesn't respond in time
- L212 _protected member_ `FTimerHandle PendingResponseTimerHandle;` — Timers for delaying various responses (debug)
- L213 _protected member_ `FTimerHandle PendingCancelResponseTimerHandle;`
- L214 _protected member_ `FTimerHandle PendingReservationUpdateTimerHandle;`
- L215 _protected member_ `FTimerHandle PendingReservationFullTimerHandle;`
- L218 _protected prototype_ `void ClearTimers(bool bCallFailSafeIfNeeded);` — Clear out all the timer handles listed above
- L220 _protected prototype_ `void OnCancelledFailsafe();` — Delegate triggered if the client doesn't hear from the server in time
- L222 _protected prototype_ `void OnCancelledComplete();` — Delegate triggered when a cancel reservation request is complete
- L225 _protected prototype_ `void ProcessReservationResponse(ESpectatorReservationResult::Type ReservationResponse);` — Process a response to our RequestReservation request to the server
- L227 _protected prototype_ `void ProcessCancelReservationResponse(ESpectatorReservationResult::Type ReservationResponse);` — Process a response to our CancelReservation request to the server
- L229 _protected prototype_ `void ProcessReservationUpdate(int32 NumRemainingReservations);` — Process a response from the server with an update to the number of consumed reservations
- L231 _protected prototype_ `void ProcessReservationFull();` — Process a response from the server that the reservation beacon is full
- L240 _protected prototype_ `virtual void ServerReservationRequest(const FString& SessionId, const FSpectatorReservation& Reservation);` — `UFUNCTION(server, reliable, WithValidation)` — Tell the server about the reservation request being made @param SessionId expected session id on the other end (must match) @param Reservation pending reservation request to make with server
- L248 _protected prototype_ `virtual void ServerCancelReservationRequest(const FUniqueNetIdRepl& Spectator);` — `UFUNCTION(server, reliable, WithValidation)` — Tell the server to cancel a pending or existing reservation @param Spectator id of the spectator for the reservation to cancel
- L258 _protected prototype_ `FTimerHandle DelayResponse(FTimerDelegate& Delegate, float Delay);` — Trigger the given delegate at a later time @param Delegate function to call at a later date @param Delay time to wait before calling function @return handle in the timer system for this entry

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L37 _function_ `inline const TCHAR* ToString(ESpectatorClientRequestType RequestType)`
- L70 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSpectatorReservationRequestComplete, ESpectatorReservationResult::Type );` — Delegate triggered when a response from the spectator beacon host has been received @param ReservationResponse response from the server
- L70 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSpectatorReservationRequestComplete, ESpectatorReservationResult::Type );` — Delegate triggered when a response from the spectator beacon host has been received @param ReservationResponse response from the server
- L77 _delegate_ `DECLARE_DELEGATE_OneParam(FOnReservationCountUpdate, int32 );` — Delegate triggered when the host indicated a reservation count has changed @param NumRemaining number of slots remaining in the session
- L77 _prototype_ `DECLARE_DELEGATE_OneParam(FOnReservationCountUpdate, int32 );` — Delegate triggered when the host indicated a reservation count has changed @param NumRemaining number of slots remaining in the session
- L80 _delegate_ `DECLARE_DELEGATE(FOnReservationFull);` — Delegate triggered when the host indicated the reservation is full
- L80 _prototype_ `DECLARE_DELEGATE(FOnReservationFull);` — Delegate triggered when the host indicated the reservation is full

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/SpectatorBeaconHost.h` (Public)


#### class `ASpectatorBeaconHost`  
`class ASpectatorBeaconHost : public AOnlineBeaconHostObject`  
_L54-282_
- reflection: `UCLASS(MinimalAPI, transient, notplaceable, config = Engine)`
- inherits: `AOnlineBeaconHostObject`
- desc: A beacon host used for taking reservations for an existing game session
- L59 _private prototype_ `virtual void PostInitProperties() override;`
- L63 _private prototype_ `virtual void Tick(float DeltaTime) override;`
- L77 _private prototype_ `virtual bool InitHostBeacon(int32 InMaxReservations, FName InSessionName);` — Initialize the spectator host beacon @param InMaxReservation max number of reservations allowed @param InSessionName name of session related to the beacon @return true if successful created, false otherwise
- L85 _private prototype_ `virtual bool InitFromBeaconState(USpectatorBeaconState* PrevState);` — Initialize the spectator host beacon from a previous state/configuration all existing reservations and configuration values are preserved @return true if successful created, false otherwise
- L90 _private function_ `USpectatorBeaconState* GetState() const` — @return reference to the state of the SpectatorBeacon
- L97 _private prototype_ `virtual void HandlePlayerLogout(const FUniqueNetIdRepl& PlayerId);` — Notify the beacon of a player logout @param PlayerId UniqueId of player logging out
- L105 _private function_ `virtual int32 GetReservationCount() const` — Get the current reservation count inside the beacon NOTE: This is *NOT* the same as the number of consumed reservations across all parties, just the total number of reservations! @return number of reservations inside the beacon (*NOT* number of consumed reservations)
- L112 _private function_ `virtual int32 GetNumConsumedReservations() const` — Get the number of reservations actually used/consumed across all parties inside the beacon @return the number of actually used reservations across all parties inside the beacon
- L119 _private function_ `virtual int32 GetMaxReservations() const` — Get the maximum number of reservations allowed inside the beacon @return The maximum number of reservations allowed inside the beacon
- L128 _private prototype_ `virtual bool PlayerHasReservation(const FUniqueNetId& PlayerId) const;` — Does a given player id have an existing reservation @param PlayerId uniqueid of the player to check @return true if a reservation exists, false otherwise
- L139 _private prototype_ `virtual bool GetPlayerValidation(const FUniqueNetId& PlayerId, FString& OutValidation) const;` — Obtain player validation string from spectator reservation entry @param PlayerId unique id of player to find validation in an existing reservation @param OutValidation [out] validation string used when player requested a reservation @return true if reservation exists for player
- L148 _private prototype_ `virtual ESpectatorReservationResult::Type AddSpectatorReservation(const FSpectatorReservation& ReservationRequest);` — Attempts to add a spectator reservation to the beacon @param ReservationRequest reservation attempt @return add attempt result
- L155 _private prototype_ `virtual ESpectatorReservationResult::Type RemoveSpectatorReservation(const FUniqueNetIdRepl& Spectator);` — Attempts to remove a spectator reservation from the beacon @param Spectator reservation owner
- L164 _private prototype_ `void RegisterAuthTicket(const FUniqueNetIdRepl& InSpectatorId, const FString& InAuthTicket);` — Register user auth ticket with the reservation system Must have an existing reservation entry @param InSpectatorId id of player logging in @param InAuthTicket auth ticket reported by the user
- L173 _private prototype_ `virtual void ProcessReservationRequest(ASpectatorBeaconClient* Client, const FString& SessionId, const FSpectatorReservation& ReservationRequest);` — Handle a reservation request received from an incoming client @param Client client beacon making the request @param SessionId id of the session that is being checked @param ReservationRequest payload of request
- L181 _private prototype_ `virtual void ProcessCancelReservationRequest(ASpectatorBeaconClient* Client, const FUniqueNetIdRepl& Spectator);` — Handle a reservation cancellation request received from an incoming client @param Client client beacon making the request @param Spectator reservation owner
- L191 _private function_ `FOnReservationUpdate& OnReservationsFull()` — Delegate fired when a the beacon host detects a reservation addition/removal
- L196 _private function_ `FOnReservationUpdate& OnReservationChanged()` — Delegate fired when a the beacon host detects that all reservations are full
- L201 _private function_ `FOnNewPlayerAdded& OnNewPlayerAdded()` — Delegate fired when the beacon host adds a new player
- L206 _private function_ `FOnCancelationReceived& OnCancelationReceived()` — Delegate fired when a the beacon host cancels a reservation
- L211 _private function_ `FOnSpectatorDuplicateReservation& OnDuplicateReservation()` — Delegate fired when a the beacon detects a duplicate reservation
- L216 _private function_ `FOnSpectatorValidatePlayers& OnValidatePlayers()` — Delegate called when the beacon gets any request, allowing the owner to validate players at a higher level (bans,etc)
- L221 _private prototype_ `virtual void DumpReservations() const;` — Output current state of reservations to log
- L227 _protected member_ `TObjectPtr<USpectatorBeaconState> State;` — `UPROPERTY()` — State of the beacon
- L230 _protected member_ `FOnReservationUpdate ReservationsFull;` — Delegate fired when the beacon indicates all reservations are taken
- L232 _protected member_ `FOnReservationUpdate ReservationChanged;` — Delegate fired when the beacon indicates a reservation add/remove
- L234 _protected member_ `FOnCancelationReceived CancelationReceived;` — Delegate fired when the beacon indicates a reservation cancellation
- L236 _protected member_ `FOnSpectatorDuplicateReservation DuplicateReservation;` — Delegate fired when the beacon detects a duplicate reservation
- L238 _protected member_ `FOnNewPlayerAdded NewPlayerAddedDelegate;` — Delegate fired when reservation has been added
- L240 _protected member_ `FOnSpectatorValidatePlayers ValidatePlayers;` — Delegate fired when asking the beacon owner if this reservation is legit
- L244 _protected member_ `bool bLogoutOnSessionTimeout;` — `UPROPERTY(Config)` — Do the timeouts below cause a player to be removed from the reservation list
- L247 _protected member_ `bool bIsValidationStrRequired;` — `UPROPERTY(Config)` — Do spectators require validation strings.
- L250 _protected member_ `float SessionTimeoutSecs;` — `UPROPERTY(Transient, Config)` — Seconds that can elapse before a reservation is removed due to player not being registered with the session
- L253 _protected member_ `float TravelSessionTimeoutSecs;` — `UPROPERTY(Transient, Config)` — Seconds that can elapse before a reservation is removed due to player not being registered with the session during a travel
- L258 _protected function_ `virtual TSubclassOf<USpectatorBeaconState> GetSpectatorBeaconHostClass() const` — @return the class of the state object inside this beacon
- L263 _protected prototype_ `void SendReservationUpdates();` — Update clients with current reservation information
- L270 _protected prototype_ `void NewPlayerAdded(const FPlayerReservation& NewPlayer);` — Handle a newly added player @param NewPlayer reservation of newly joining player
- L279 _protected prototype_ `bool DoesSessionMatch(const FString& SessionId) const;` — Does the session match the one associated with this beacon @param SessionId session to compare @return true if the session matches, false otherwise
- L281 _protected prototype_ `void NotifyReservationEventNextFrame(FOnReservationUpdate& ReservationEvent);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L19 _delegate_ `DECLARE_DELEGATE(FOnReservationUpdate);` — Delegate type for handling reservation additions/removals, or full events
- L19 _prototype_ `DECLARE_DELEGATE(FOnReservationUpdate);` — Delegate type for handling reservation additions/removals, or full events
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCancelationReceived, const FUniqueNetId&);` — Delegate fired when a the beacon host has been told to cancel a reservation @param Spectator spectator cancelling reservation
- L26 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCancelationReceived, const FUniqueNetId&);` — Delegate fired when a the beacon host has been told to cancel a reservation @param Spectator spectator cancelling reservation
- L33 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNewPlayerAdded, const FPlayerReservation&);` — Delegate fired when a the beacon host has added a new player @param PlayerId Player who reservation has been made for.
- L33 _prototype_ `DECLARE_DELEGATE_OneParam(FOnNewPlayerAdded, const FPlayerReservation&);` — Delegate fired when a the beacon host has added a new player @param PlayerId Player who reservation has been made for.
- L41 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnSpectatorValidatePlayers, const FPlayerReservation&);` — Delegate called when the beacon gets any request, allowing the owner to validate players at a higher level (bans,etc) @param Spectator player making up the reservation @return true if these players are ok to join
- L41 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnSpectatorValidatePlayers, const FPlayerReservation&);` — Delegate called when the beacon gets any request, allowing the owner to validate players at a higher level (bans,etc) @param Spectator player making up the reservation @return true if these players are ok to join
- L48 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSpectatorDuplicateReservation, const FSpectatorReservation&);` — Delegate fired when a the beacon host detects a duplicate reservation @param SpectatorReservation reservation that is found to be duplicated
- L48 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSpectatorDuplicateReservation, const FSpectatorReservation&);` — Delegate fired when a the beacon host detects a duplicate reservation @param SpectatorReservation reservation that is found to be duplicated

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/SpectatorBeaconState.h` (Public)


#### enum `ESpectatorReservationResult::Type`  
`enum Type : int`  
_L16-50_
- L19 _public enumerator_ `NoResult` — Empty state.
- L21 _public enumerator_ `RequestPending` — Pending request due to async operation, server will contact client shortly.
- L23 _public enumerator_ `GeneralError` — An unknown error happened.
- L25 _public enumerator_ `SpectatorLimitReached` — All available reservations are booked.
- L27 _public enumerator_ `IncorrectPlayerCount` — Wrong number of players to join the session.
- L29 _public enumerator_ `RequestTimedOut` — No response from the host.
- L31 _public enumerator_ `ReservationDuplicate` — Already have a reservation entry for the requesting spectator.
- L33 _public enumerator_ `ReservationNotFound` — Couldn't find the spectator specified for a reservation update request.
- L35 _public enumerator_ `ReservationAccepted` — Space was available and it's time to join.
- L37 _public enumerator_ `ReservationDenied` — The beacon is paused and not accepting new connections.
- L39 _public enumerator_ `ReservationDenied_CrossPlayRestriction` — Some kind of cross play restriction prevents this spectator from joining
- L41 _public enumerator_ `ReservationDenied_Banned` — This player is banned.
- L43 _public enumerator_ `ReservationRequestCanceled` — The reservation request was canceled before being sent.
- L45 _public enumerator_ `ReservationInvalid` — The reservation was rejected because it was badly formed
- L47 _public enumerator_ `BadSessionId` — The reservation was rejected because this was the wrong session
- L49 _public enumerator_ `ReservationDenied_ContainsExistingPlayers` — The reservation contains players already in this game

#### struct `FSpectatorReservation`  
`struct FSpectatorReservation`  
_L163-184_
- reflection: `USTRUCT()`
- desc: A whole Spectator reservation
- L167 _public function_ `FSpectatorReservation()`
- L173 _public member_ `FUniqueNetIdRepl SpectatorId;` — `UPROPERTY(Transient)` — Player initiating the request
- L177 _public member_ `FPlayerReservation Spectator;` — `UPROPERTY(Transient)` — Spectator reservation
- L180 _public prototype_ `bool IsValid(bool bIsValidationStrRequired=true) const;` — Is this data well formed
- L183 _public prototype_ `void Dump() const;` — Dump this reservation to log

#### class `USpectatorBeaconState`  
`class USpectatorBeaconState : public UObject`  
_L190-386_
- reflection: `UCLASS(MinimalAPI, transient, config = Engine)`
- inherits: `UObject`
- desc: A beacon host used for taking reservations for an existing game session
- L205 _private prototype_ `virtual bool InitState(int32 InMaxReservations, FName InSessionName);` — Initialize this state object @param InTeamCount number of teams to make room for @param InTeamSize size of each team @param InMaxReservation max number of reservations allowed @param InSessionName name of session related to the beacon @param InForceTeamNum team to force players on if applicable (usually only 1 team games) @return true if successful created, false otherwise
- L214 _private prototype_ `virtual bool AddReservation(const FSpectatorReservation& ReservationRequest);` — Add a reservation to the beacon state, tries to assign a team @param ReservationRequest reservation to possibly add to this state @return true if successful, false otherwise
- L223 _private prototype_ `virtual bool RemoveReservation(const FUniqueNetIdRepl& Spectator);` — Remove an entire reservation from this state object @param Spectator player holding reservation @return true if successful, false if reservation not found
- L232 _private prototype_ `void RegisterAuthTicket(const FUniqueNetIdRepl& InSpectatorId, const FString& InAuthTicket);` — Register user auth ticket with the reservation system Must have an existing reservation entry @param InSpectatorId id of player logging in @param InAuthTicket auth ticket reported by the user
- L241 _private prototype_ `virtual bool RemovePlayer(const FUniqueNetIdRepl& PlayerId);` — Remove a single player from their reservation PlayerId player to remove @return true if player found and removed, false otherwise
- L246 _private function_ `virtual FName GetSessionName() const` — @return the name of the session associated with this beacon state
- L251 _private function_ `virtual TArray<FSpectatorReservation>& GetReservations()` — @return all reservations in this beacon state
- L260 _private prototype_ `virtual int32 GetExistingReservation(const FUniqueNetIdRepl& Spectator) const;` — Get an existing reservation for a given spectator @param Spectator UniqueId of spectator for a reservation @return index of reservation, INDEX_NONE otherwise
- L268 _private function_ `virtual int32 GetReservationCount() const` — Get the current reservation count inside the beacon this is NOT the number of players in the game @return number of consumed reservations
- L273 _private function_ `virtual int32 GetMaxReservations() const` — @return the total number of reservations allowed
- L278 _private function_ `virtual int32 GetRemainingReservations() const` — @return the amount of space left in the beacon
- L283 _private function_ `virtual int32 GetNumConsumedReservations() const` — @return the number of actually used reservations across all parties
- L292 _private prototype_ `virtual bool DoesReservationFit(const FSpectatorReservation& ReservationRequest) const;` — Determine if this reservation fits all rules for fitting in the game @param ReservationRequest reservation to test for @return true if reservation can be added to this state, false otherwise
- L297 _private function_ `virtual bool IsBeaconFull() const` — @return true if the beacon is currently at max capacity
- L306 _private prototype_ `virtual bool PlayerHasReservation(const FUniqueNetId& PlayerId) const;` — Does a given player id have an existing reservation @param PlayerId uniqueid of the player to check @return true if a reservation exists, false otherwise
- L317 _private prototype_ `virtual bool UpdateMemberPlatform(const FUniqueNetIdRepl& Spectator, const FString& PlatformName);` — Updates the platform on an existing reservation (Used when MMS does not set a platform when handing out a match assignment) @param PlayerId uniqueid of the player to update @param PlatformName platform to set new player as using @return true if a reservation exists, false otherwise
- L328 _private prototype_ `virtual bool GetPlayerValidation(const FUniqueNetId& PlayerId, FString& OutValidation) const;` — Obtain player validation string from spectator reservation entry @param PlayerId unique id of player to find validation in an existing reservation @param OutValidation [out] validation string used when player requested a reservation @return true if reservation exists for player
- L337 _private prototype_ `virtual bool CrossPlayAllowed(const FSpectatorReservation& ReservationRequest) const;` — Perform a cross play compatible check for the new reservation against existing reservations @param ReservationRequest new reservation to compare @return true if there are no cross play restrictions, false otherwise
- L342 _private prototype_ `virtual bool HasCrossplayOptOutReservation() const;` — @return true if there are cross play restrictions, false otherwise
- L351 _private prototype_ `virtual int32 GetReservationPlatformCount(const FString& InPlatform) const;` — Get a count of all players for a given platform @param InPlatform platform to get a count for @return number of players for a given platform
- L356 _private prototype_ `virtual void DumpReservations() const;` — Output current state of reservations to log
- L362 _protected member_ `FName SessionName;` — `UPROPERTY(Transient)` — Session tied to the beacon
- L365 _protected member_ `int32 NumConsumedReservations;` — `UPROPERTY(Transient)` — Number of currently consumed reservations
- L368 _protected member_ `int32 MaxReservations;` — `UPROPERTY(Transient)` — Maximum allowed reservations
- L371 _protected member_ `bool bRestrictCrossConsole;` — `UPROPERTY(Config)` — Are multiple consoles types allowed to play together
- L375 _protected member_ `TArray<FSpectatorReservation> Reservations;` — `UPROPERTY(Transient)` — Current reservations in the system
- L377 _protected member_ `TArray< FUniqueNetIdPtr > PlayersPendingJoin;` — Players that are expected to join shortly
- L383 _protected prototype_ `void SanityCheckReservations(const bool bIgnoreEmptyReservations) const;` — Check that our reservations are in a good state @param bIgnoreEmptyReservations Whether we want to ignore empty reservations or not (because we intend to clean them up later)

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSpectatorBeacon, Log, All);`
- L14 _namespace_ `namespace ESpectatorReservationResult`
- L53 _namespace_ `namespace ESpectatorReservationResult`
- L56 _function_ `inline const TCHAR* ToString(ESpectatorReservationResult::Type SessionType)` (scope `ESpectatorReservationResult`) — @return the stringified version of the enum passed in
- L128 _function_ `inline FText GetDisplayString(ESpectatorReservationResult::Type Response)` (scope `ESpectatorReservationResult`)

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/VoiceEngineImpl.h` (Public)


#### struct `FLocalVoiceData`  
`struct FLocalVoiceData`  
_L29-42_
- desc: Container for unprocessed voice data
- L31 _public function_ `FLocalVoiceData() : VoiceRemainderSize(0)`
- L37 _public member_ `uint32 VoiceRemainderSize;` — Amount of voice data not encoded last time
- L39 _public member_ `TArray<uint8> VoiceRemainder;` — Voice sample data not encoded last time
- L41 _public member_ `Audio::FPatchSplitter LocalVoiceOutput;` — Output for a local talker.

#### struct `FVoiceAmplitudeData`  
`struct FVoiceAmplitudeData`  
_L47-51_
- desc: Container for voice amplitude data
- L49 _public member_ `float Amplitude = 0.0;`
- L50 _public member_ `double LastSeen = 0.0;`

#### class `FRemoteTalkerDataImpl`  
`class FRemoteTalkerDataImpl`  
_L56-99_
- desc: Remote voice data playing on a single client
- L60 _public prototype_ `FRemoteTalkerDataImpl();`
- L62 _public prototype_ `FRemoteTalkerDataImpl(const FRemoteTalkerDataImpl& Other);` — Required for TMap FindOrAdd()
- L63 _public prototype_ `FRemoteTalkerDataImpl(FRemoteTalkerDataImpl&& Other);`
- L64 _public prototype_ `~FRemoteTalkerDataImpl();`
- L67 _public prototype_ `void Reset();` — Reset the talker after long periods of silence
- L69 _public prototype_ `void Cleanup();` — Cleanup the talker before unregistration
- L72 _public member_ `int32 MaxUncompressedDataSize;` — Maximum size of a single decoded packet
- L74 _public member_ `int32 MaxUncompressedDataQueueSize;` — Maximum size of the outgoing playback queue
- L76 _public member_ `int32 CurrentUncompressedDataQueueSize;` — Amount of data currently in the outgoing playback queue
- L79 _public member_ `double LastSeen;` — Receive side timestamp since last voice packet fragment
- L81 _public member_ `int32 NumFramesStarved;` — Number of frames starved of audio
- L83 _public member_ `TWeakObjectPtr<UVoipListenerSynthComponent> VoipSynthComponent;` — Synth component playing this buffer (only valid on remote instances)
- L85 _public member_ `UVOIPTalker* CachedTalkerPtr;` — Cached Talker Ptr. Is checked against map before use to ensure it has not been destroyed.
- L87 _public member_ `bool bIsEnvelopeBound;` — Boolean used to ensure that we only bind the VOIP talker to the SynthComponent's corresponding envelope delegate once.
- L89 _public member_ `bool bIsActive;` — Boolean flag used to tell whether this synth component is currently consuming incoming voice packets.
- L91 _public member_ `mutable FCriticalSection QueueLock;` — Buffer for outgoing audio intended for procedural streaming
- L92 _public member_ `TArray<uint8> UncompressedDataQueue;`
- L94 _public member_ `TSharedPtr<IVoiceDecoder> VoiceDecoder;` — Per remote talker voice decoding state
- L96 _public member_ `Audio::FPatchSplitter RemoteVoiceOutput;` — Patch splitter to expose incoming audio to multiple outputs.
- L98 _public member_ `float MicrophoneAmplitude;` — Loudness of the incoming audio, computed on the remote machine using the microphonei input audio and serialized into the packet.

#### class `FVoiceEndpoint`  
`class FVoiceEndpoint : Audio::IAudioMixer`  
_L104-129_
- inherits: `Audio::IAudioMixer`
- desc: Small class that manages an audio endpoint. Used in FVoiceEngineImpl.
- L107 _public prototype_ `FVoiceEndpoint(const FString& InEndpointName, float InSampleRate, int32 InNumChannels);`
- L108 _public prototype_ `virtual ~FVoiceEndpoint();`
- L110 _public prototype_ `void PatchInOutput(Audio::FPatchOutputStrongPtr& InOutput);`
- L114 _public prototype_ `bool OnProcessAudioStream(Audio::AlignedFloatBuffer& OutputBuffer) override;`
- L115 _public prototype_ `void OnAudioStreamShutdown() override;`
- L119 _private member_ `int32 NumChannelsComingIn;`
- L120 _private member_ `Audio::FAlignedFloatBuffer DownmixBuffer;`
- L122 _private member_ `TUniquePtr<Audio::IAudioMixerPlatformInterface> PlatformEndpoint;`
- L124 _private member_ `Audio::FAudioMixerOpenStreamParams OpenParams;`
- L125 _private member_ `Audio::FAudioPlatformDeviceInfo PlatformDeviceInfo;`
- L127 _private member_ `Audio::FPatchOutputStrongPtr OutputPatch;`
- L128 _private member_ `FCriticalSection OutputPatchCriticalSection;`

#### class `FVoiceEngineImpl`  
`class FVoiceEngineImpl : public IVoiceEngine, public FSelfRegisteringExec, public IDeviceChangedListener`  
_L135-391_
- inherits: `IVoiceEngine,FSelfRegisteringExec,IDeviceChangedListener`
- desc: Generic implementation of voice engine, using Voice module for capture/codec
- L174 _private typedef_ `typedef TMap<FUniqueNetIdWrapper, FRemoteTalkerDataImpl> FRemoteTalkerData;` — Mapping of UniqueIds to the incoming voice data and their audio component
- L177 _private member_ `FName OnlineInstanceName;` — Instance name of associated online subsystem
- L179 _private member_ `FLocalVoiceData PlayerVoiceData[MAX_SPLITSCREEN_TALKERS];`
- L181 _private member_ `TSharedPtr<IVoiceCapture> VoiceCapture;` — Reference to voice capture device
- L183 _private member_ `TSharedPtr<IVoiceEncoder> VoiceEncoder;` — Reference to voice encoding object
- L186 _private member_ `int32 OwningUserIndex;` — User index currently holding onto the voice interface
- L188 _private member_ `uint32 UncompressedBytesAvailable;` — Amount of uncompressed data available this frame
- L190 _private member_ `uint32 CompressedBytesAvailable;` — Amount of compressed data available this frame
- L192 _private member_ `EVoiceCaptureState::Type AvailableVoiceResult;` — Current frame state of voice capture
- L194 _private member_ `mutable bool bPendingFinalCapture;` — Have we stopped capturing voice but are waiting for its completion
- L196 _private member_ `bool bIsCapturing;` — State of voice recording
- L199 _private member_ `TArray<uint8> CompressedVoiceBuffer;` — Data from voice codec, waiting to send to network.
- L201 _private member_ `FRemoteTalkerData RemoteTalkerBuffers;` — Data from network playing on an audio component.
- L203 _private member_ `TArray<uint8> DecompressedVoiceBuffer;` — Voice decompression buffer, shared by all talkers, valid during SubmitRemoteVoiceData
- L205 _private member_ `FVoiceSerializeHelper* SerializeHelper;` — Serialization helper
- L208 _private member_ `TMap<FUniqueNetIdWrapper, FVoiceAmplitudeData> VoiceAmplitudes;` — Voice Amplitude data to prevent using FRemoteTalkerData if we don't actually require voice
- L211 _private member_ `Audio::FPatchMixerSplitter AllRemoteTalkerAudio;` — Audio taps for the full mixdown of all remote players.
- L218 _private member_ `TArray<TUniquePtr<FVoiceEndpoint>> ExternalEndpoints;` — Collection of external endpoints that we are sending local or remote audio to. Note that we need to wrap each FVoiceEndpoint in a unique pointer to ensure the FVoiceEndpoint itself isn't moved elsewhere. Otherwise, this will cause a crash in FOutputBuffer::MixNextBuffer(), due to AudioMixer->OnProcessAudioStream(); being called on a stale pointer.
- L228 _protected function_ `inline virtual bool IsOwningUser(uint32 UserIndex)` — Determines if the specified index is the owner or not @param InIndex the index being tested @return true if this is the owner, false otherwise
- L234 _protected prototype_ `virtual void StartRecording() const;` — Start capturing voice data
- L237 _protected prototype_ `virtual void StopRecording() const;` — Stop capturing voice data
- L240 _protected prototype_ `virtual void StoppedRecording() const;` — Called when "last half second" is over
- L243 _protected function_ `virtual bool IsRecording() const` — @return is active recording occurring at the moment
- L250 _private prototype_ `void VoiceCaptureUpdate() const;` — Update the internal state of the voice capturing state Handles possible continuation waiting for capture stop event
- L259 _private prototype_ `void GenerateVoiceData(USoundWaveProcedural* InProceduralWave, int32 SamplesRequired, const FUniqueNetId& TalkerId);` — Callback from streaming audio when data is requested for playback @param InProceduralWave SoundWave requesting more data @param SamplesRequired number of samples needed for immediate playback @param TalkerId id of the remote talker to allocate voice data for
- L267 _private prototype_ `virtual bool Init(int32 MaxLocalTalkers, int32 MaxRemoteTalkers) override;` — IVoiceEngine
- L271 _public prototype_ `FVoiceEngineImpl(IOnlineSubsystem* InSubsystem);`
- L272 _public prototype_ `virtual ~FVoiceEngineImpl();`
- L275 _public prototype_ `virtual uint32 StartLocalVoiceProcessing(uint32 LocalUserNum) override;` — IVoiceEngine
- L276 _public prototype_ `virtual uint32 StopLocalVoiceProcessing(uint32 LocalUserNum) override;`
- L278 _public function_ `virtual uint32 StartRemoteVoiceProcessing(const FUniqueNetId& UniqueId) override`
- L284 _public function_ `virtual uint32 StopRemoteVoiceProcessing(const FUniqueNetId& UniqueId) override`
- L290 _public prototype_ `virtual uint32 RegisterLocalTalker(uint32 LocalUserNum) override;`
- L291 _public prototype_ `virtual uint32 UnregisterLocalTalker(uint32 LocalUserNum) override;`
- L293 _public function_ `virtual uint32 RegisterRemoteTalker(const FUniqueNetId& UniqueId) override`
- L299 _public prototype_ `virtual uint32 UnregisterRemoteTalker(const FUniqueNetId& UniqueId) override;`
- L301 _public function_ `virtual bool IsHeadsetPresent(uint32 LocalUserNum) override`
- L306 _public function_ `virtual bool IsLocalPlayerTalking(uint32 LocalUserNum) override`
- L311 _public function_ `virtual bool IsRemotePlayerTalking(const FUniqueNetId& UniqueId) override`
- L316 _public prototype_ `virtual uint32 GetVoiceDataReadyFlags() const override;`
- L317 _public function_ `virtual uint32 SetPlaybackPriority(uint32 LocalUserNum, const FUniqueNetId& RemoteTalkerId, uint32 Priority) override`
- L323 _public function_ `virtual uint32 ReadLocalVoiceData(uint32 LocalUserNum, uint8* Data, uint32* Size) override`
- L324 _public prototype_ `virtual uint32 ReadLocalVoiceData(uint32 LocalUserNum, uint8* Data, uint32* Size, uint64* OutSampleCount) override;`
- L326 _public function_ `virtual uint32 SubmitRemoteVoiceData(const FUniqueNetId& RemoteTalkerId, uint8* Data, uint32* Size)`
- L331 _public prototype_ `virtual uint32 SubmitRemoteVoiceData(const FUniqueNetIdWrapper& RemoteTalkerId, uint8* Data, uint32* Size, uint64& InSampleCount) override;`
- L333 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L334 _public prototype_ `FString GetVoiceDebugState() const override;`
- L336 _public function_ `virtual void GetVoiceSettingsOverride(const FUniqueNetIdWrapper& RemoteTalkerId, FVoiceSettings& VoiceSettings)`
- L339 _public prototype_ `virtual Audio::FPatchOutputStrongPtr GetMicrophoneOutput() override;`
- L340 _public prototype_ `virtual Audio::FPatchOutputStrongPtr GetRemoteTalkerOutput() override;`
- L341 _public prototype_ `virtual float GetMicrophoneAmplitude(int32 LocalUserNum) override;`
- L342 _public prototype_ `virtual float GetIncomingAudioAmplitude(const FUniqueNetIdWrapper& RemoteUserId) override;`
- L343 _public prototype_ `virtual uint32 SetRemoteVoiceAmplitude(const FUniqueNetIdWrapper& RemoteTalkerId, float InAmplitude) override;`
- L346 _public prototype_ `virtual bool PatchRemoteTalkerOutputToEndpoint(const FString& InDeviceName, bool bMuteInGameOutput = true) override;`
- L349 _public prototype_ `virtual void DisconnectAllEndpoints() override;`
- L352 _public prototype_ `virtual bool PatchLocalTalkerOutputToEndpoint(const FString& InDeviceName) override;`
- L356 _protected prototype_ `virtual bool Exec_Runtime(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — FSelfRegisteringExec
- L363 _private prototype_ `void TickTalkers(float DeltaTime);` — Update the state of all remote talkers, possibly dropping data or the talker entirely
- L368 _private prototype_ `void OnAudioFinished();` — Delegate triggered when an audio component Stop() function is called
- L373 _private prototype_ `void OnPostLoadMap(UWorld*);` — Delegate that fixes up remote audio components when the level changes
- L376 _protected prototype_ `virtual IOnlineSubsystem* GetOnlineSubSystem();`
- L377 _protected function_ `virtual const TSharedPtr<IVoiceCapture>& GetVoiceCapture() const`
- L378 _protected function_ `virtual TSharedPtr<IVoiceCapture>& GetVoiceCapture()`
- L379 _protected function_ `virtual const TSharedPtr<IVoiceEncoder>& GetVoiceEncoder() const`
- L380 _protected function_ `virtual TSharedPtr<IVoiceEncoder>& GetVoiceEncoder()`
- L381 _protected function_ `virtual FRemoteTalkerData& GetRemoteTalkerBuffers()`
- L382 _protected function_ `virtual TArray<uint8>& GetCompressedVoiceBuffer()`
- L383 _protected function_ `virtual TArray<uint8>& GetDecompressedVoiceBuffer()`
- L384 _protected function_ `virtual FLocalVoiceData* GetLocalPlayerVoiceData()`
- L385 _protected prototype_ `virtual int32 GetMaxVoiceRemainderSize();`
- L386 _protected prototype_ `virtual void CreateSerializeHelper();`
- L388 _protected function_ `virtual void OnDefaultDeviceChanged() override`
- L389 _protected function_ `virtual void OnDeviceRemoved(FString DeviceID) override`

#### class `FVoiceEngineImpl::FVoiceSerializeHelper`  
`class FVoiceSerializeHelper : public FGCObject`  
_L137-169_
- inherits: `FGCObject`
- L140 _private member_ `FVoiceEngineImpl* VoiceEngine;` — Reference to audio components
- L141 _private function_ `FVoiceSerializeHelper() : VoiceEngine(nullptr)`
- L147 _public function_ `FVoiceSerializeHelper(FVoiceEngineImpl* InVoiceEngine) : VoiceEngine(InVoiceEngine)`
- L150 _public prototype_ `~FVoiceSerializeHelper() = default;`
- L153 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override` — FGCObject interface
- L165 _public function_ `virtual FString GetReferencerName() const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L393 _typedef_ `typedef TSharedPtr<FVoiceEngineImpl, ESPMode::ThreadSafe> FVoiceEngineImplPtr;`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/VoiceInterfaceImpl.h` (Public)


#### class `FOnlineVoiceImpl`  
`class FOnlineVoiceImpl : public IOnlineVoice`  
_L14-158_
- inherits: `IOnlineVoice`
- L17 _protected member_ `class IOnlineSubsystem* OnlineSubsystem;` — Reference to the main online subsystem
- L19 _protected member_ `class IOnlineSession* SessionInt;` — Reference to the sessions interface
- L21 _protected member_ `class IOnlineIdentity* IdentityInt;` — Reference to the profile interface
- L23 _protected member_ `IVoiceEnginePtr VoiceEngine;` — Reference to the voice engine for acquiring voice data
- L26 _protected member_ `int32 MaxLocalTalkers;` — Maximum permitted local talkers
- L28 _protected member_ `int32 MaxRemoteTalkers;` — Maximum permitted remote talkers
- L31 _protected member_ `TArray<FLocalTalker> LocalTalkers;` — State of all possible local talkers
- L33 _protected member_ `TArray<FRemoteTalker> RemoteTalkers;` — State of all possible remote talkers
- L36 _protected member_ `TArray<FUniqueNetIdWrapper> SystemMuteList;`
- L38 _protected member_ `TArray<FUniqueNetIdWrapper> MuteList;` — All remote players locally muted (super set of SystemMuteList)
- L41 _protected member_ `float VoiceNotificationDelta;` — Time to wait for new data before triggering "not talking"
- L44 _protected member_ `FVoiceDataImpl VoiceData;` — Buffered voice data I/O
- L53 _protected prototype_ `virtual struct FRemoteTalker* FindRemoteTalker(const FUniqueNetId& UniqueId);` — Finds a remote talker in the cached list @param UniqueId the net id of the player to search for @return pointer to the remote talker or NULL if not found
- L62 _protected prototype_ `virtual bool IsLocallyMuted(const FUniqueNetId& UniqueId) const;` — Is a given id presently muted (either by system mute or game server) @param UniqueId the net id to query @return true if the net id is muted at all, false otherwise
- L71 _protected prototype_ `virtual bool IsSystemWideMuted(const FUniqueNetId& UniqueId) const;` — Does a given id exist in the system wide mute list @param UniqueId the net id to query @return true if the net id is on the system wide mute list, false otherwise
- L86 _protected prototype_ `virtual bool Init() override;` — IOnlineVoice
- L87 _protected prototype_ `virtual void ProcessMuteChangeNotification() override;`
- L89 _protected prototype_ `virtual IVoiceEnginePtr CreateVoiceEngine() override;`
- L94 _protected prototype_ `virtual void Shutdown();` — Cleanup voice interface
- L101 _protected prototype_ `virtual void ProcessTalkingDelegates(float DeltaTime);` — Processes any talking delegates that need to be fired off @param DeltaTime the amount of time that has elapsed since the last tick
- L106 _protected prototype_ `virtual void ProcessLocalVoicePackets();` — Reads any data that is currently queued
- L111 _protected prototype_ `virtual void ProcessRemoteVoicePackets();` — Submits network packets to audio system for playback
- L119 _protected prototype_ `virtual void UpdateMuteListForLocalTalker(int32 TalkerIndex);` — Figures out which remote talkers need to be muted for a given local talker @param TalkerIndex the talker that needs the mute list checked for @param PlayerController the player controller associated with this talker
- L124 _public prototype_ `FOnlineVoiceImpl(class IOnlineSubsystem* InOnlineSubsystem);` — Constructor
- L127 _public prototype_ `virtual ~FOnlineVoiceImpl();` — Virtual destructor to force proper child cleanup
- L130 _public prototype_ `virtual void StartNetworkedVoice(uint8 LocalUserNum) override;` — IOnlineVoice
- L131 _public prototype_ `virtual void StopNetworkedVoice(uint8 LocalUserNum) override;`
- L132 _public prototype_ `virtual bool RegisterLocalTalker(uint32 LocalUserNum) override;`
- L133 _public prototype_ `virtual void RegisterLocalTalkers() override;`
- L134 _public prototype_ `virtual bool UnregisterLocalTalker(uint32 LocalUserNum) override;`
- L135 _public prototype_ `virtual void UnregisterLocalTalkers() override;`
- L136 _public prototype_ `virtual bool RegisterRemoteTalker(const FUniqueNetId& UniqueId) override;`
- L137 _public prototype_ `virtual bool UnregisterRemoteTalker(const FUniqueNetId& UniqueId) override;`
- L138 _public prototype_ `virtual void RemoveAllRemoteTalkers() override;`
- L139 _public prototype_ `virtual bool IsHeadsetPresent(uint32 LocalUserNum) override;`
- L140 _public prototype_ `virtual bool IsLocalPlayerTalking(uint32 LocalUserNum) override;`
- L141 _public prototype_ `virtual bool IsRemotePlayerTalking(const FUniqueNetId& UniqueId) override;`
- L142 _public prototype_ `bool IsMuted(uint32 LocalUserNum, const FUniqueNetId& UniqueId) const override;`
- L143 _public prototype_ `bool MuteRemoteTalker(uint8 LocalUserNum, const FUniqueNetId& PlayerId, bool bIsSystemWide) override;`
- L144 _public prototype_ `bool UnmuteRemoteTalker(uint8 LocalUserNum, const FUniqueNetId& PlayerId, bool bIsSystemWide) override;`
- L145 _public prototype_ `virtual TSharedPtr<class FVoicePacket> SerializeRemotePacket(FArchive& Ar) override;`
- L146 _public prototype_ `virtual TSharedPtr<class FVoicePacket> GetLocalPacket(uint32 LocalUserNum) override;`
- L147 _public function_ `virtual int32 GetNumLocalTalkers() override`
- L148 _public prototype_ `virtual void ClearVoicePackets() override;`
- L149 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L150 _public prototype_ `virtual FString GetVoiceDebugState() const override;`
- L151 _public prototype_ `virtual Audio::FPatchOutputStrongPtr GetMicrophoneOutput() override;`
- L152 _public prototype_ `virtual Audio::FPatchOutputStrongPtr GetRemoteTalkerOutput() override;`
- L153 _public prototype_ `virtual float GetAmplitudeOfRemoteTalker(const FUniqueNetId& PlayerId) override;`
- L154 _public prototype_ `virtual bool PatchRemoteTalkerOutputToEndpoint(const FString& InDeviceName, bool bMuteInGameOutput = true) override;`
- L155 _public prototype_ `virtual bool PatchLocalTalkerOutputToEndpoint(const FString& InDeviceName) override;`
- L156 _public prototype_ `virtual void DisconnectAllEndpoints() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L160 _typedef_ `typedef TSharedPtr<FOnlineVoiceImpl, ESPMode::ThreadSafe> FOnlineVoiceImplPtr;`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/VoicePacketBuffer.h` (Public)


#### enum `EVoipStreamDataFormat`  
`enum class EVoipStreamDataFormat : uint8`  
_L15-20_
- L17 _public enumerator_ `Float`
- L18 _public enumerator_ `Int16`
- L19 _public enumerator_ `Unknown`

#### struct `FSortedVoicePacketNode`  
`struct FSortedVoicePacketNode`  
_L27-109_
- desc: /
- L30 _public member_ `TArray<float> AudioBufferMem;` — The actual resulting audio data. allocated ahead of time to minimize memory churn.
- L33 _public member_ `int32 BufferNumSamples;` — Number of samples.
- L36 _public member_ `int32 SamplesLeft;` — updated on every call of PopAudio to keep track of where we are mid-packet.
- L41 _public member_ `FSortedVoicePacketNode* NextPacket;` — used for sorting packet nodes. While the packets exist in a contiguous memory pool in the FVoicePacketBuffer. However, the packet buffer is traversed like a singly linked list to allow for fast middle insertion.
- L45 _public member_ `int32 IndexInPacketBuffer;` — This is used when we are done with this packet. The index is enqueued so that when the FVoicePacketBuffer gets a new packet, they can Initialize this one.
- L48 _public member_ `uint64 StartSample;` — Actual sample start time for this sample.
- L51 _public function_ `FSortedVoicePacketNode() : BufferNumSamples(0) , SamplesLeft(0) , NextPacket(nullptr) , IndexInPacketBuffer(INDEX_NONE) , StartSample(0)` — Default constructor.
- L61 _public function_ `void Initialize(const void* InBuffer, uint32 NumBytes, int64 InStartSample, EVoipStreamDataFormat InFormat)` — This function is called when a new packet is pushed to avoid reallocating memory.

#### class `FVoicePacketBuffer`  
`class FVoicePacketBuffer`  
_L117-200_
- desc: /
- L121 _public prototype_ `FVoicePacketBuffer(int32 BufferSize, int32 InNumSamplesUntilIdling, uint64 InStartSample);` — This is the only constructor that should be used with FVoicePacketBuffer.
- L125 _public prototype_ `void PushPacket(const void* InBuffer, int32 NumBytes, uint64 InStartSample, EVoipStreamDataFormat Format);` — Push a new packet of decompressed audio onto the buffer to be consumed. This should be called on the voice engine thread.
- L130 _public prototype_ `int32 PopAudio(float* DestBuffer, uint32 RequestedSamples);` — Pop RequestedSamples of float samples into DestBuffer. Returns the number of "non-silent" samples copied into the buffer- the remainder of the buffer will be filled with silence. This should be called on the audio render thread.
- L133 _public function_ `bool IsIdle()` — Whether we have idled out. This is used to automatically close the audio stream and free resources when unused.
- L136 _public function_ `uint64 GetCurrentSample()` — Get whatever the most recent sample processed is for buffer-accurate timing.
- L139 _public prototype_ `int32 GetNumBufferedSamples();` — This will return the current amount of samples buffered here.
- L143 _public prototype_ `uint32 DropOldestAudio(uint32 InNumSamples);` — When called, will seek forward in the buffer by the requested number of samples, skipping and removing the audio we seek past. This will return the number of samples we were able to seek forward by.
- L146 _public prototype_ `void Reset(int32 InStartSample);` — Clears the buffer.
- L150 _private function_ `static int32 SizeOfSample(EVoipStreamDataFormat InFormat)`
- L171 _private prototype_ `FVoicePacketBuffer();` — Default constructor. Hidden on purpose.
- L174 _private member_ `FSortedVoicePacketNode* ListHead;` — Current packet that the buffer is popping audio from.
- L177 _private member_ `uint64 SampleCounter;` — Sample counter used to track silences when buffers are dropped, etc.
- L180 _private member_ `uint32 IdleSampleCounter;` — This tracks the number of samples of silence we've popped since we last had a viable packet of audio.
- L183 _private member_ `FThreadSafeBool bIsIdle;` — bool set when IdleSampleCounter is above NumSamplesUntilIdling.
- L186 _private member_ `uint32 NumSamplesUntilIdling;` — number of samples until we raise the bIsIdle flag.
- L189 _private member_ `TArray<FSortedVoicePacketNode> PacketBuffer;` — This is treated as an unsorted memory pool for packets. Packets are overwritten after they are used.
- L192 _private member_ `TQueue<int32> FreedIndicesQueue;` — After a packet is used, we push its index on the PacketBuffer so that we can Initialize it.
- L195 _private member_ `FThreadSafeCounter NumBufferedSamples;` — The amount of samples of audio we currently have buffered.
- L198 _private member_ `FCriticalSection ListHeadCriticalSection;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L13 _macro_ `#define SCOPELOCK_VOICE_PACKET_BUFFER 0` — Set this to 1 to enforce a critical section between FVoicePacketBuffer::PopAudio and FVoicePacketBuffer::SubmitPacket.

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/VoicePacketImpl.h` (Public)


#### class `FVoicePacketImpl`  
`class FVoicePacketImpl : public FVoicePacket`  
_L14-60_
- inherits: `FVoicePacket`
- desc: Defines the data involved in a voice packet
- L22 _private member_ `TArray<uint8> Buffer;` — The data that is to be sent/processed
- L24 _private member_ `uint16 Length;` — The current amount of space used in the buffer for this packet
- L25 _private member_ `uint64 SampleCount;` — this is a "sample accurate" representation of the audio data, used for interleaving silent buffers, etc.
- L27 _private member_ `int16 MicrophoneAmplitude;` — Current loudness of the given microphone, in Q15.
- L31 _public function_ `FVoicePacketImpl() : Sender(NULL), Length(0), MicrophoneAmplitude(0)` — Zeros members and validates the assumptions
- L41 _public prototype_ `virtual ~FVoicePacketImpl() = default;` — Should only be used by TSharedPtr and FVoiceData
- L48 _public prototype_ `FVoicePacketImpl(const FVoicePacketImpl& Other);` — Copies another packet @param Other packet to copy
- L50 _public prototype_ `virtual void ResetData();`
- L53 _public prototype_ `virtual uint16 GetTotalPacketSize() override;`
- L54 _public prototype_ `virtual uint16 GetBufferSize() override;`
- L55 _public prototype_ `virtual FUniqueNetIdPtr GetSender() override;`
- L56 _public function_ `virtual bool IsReliable() override`
- L57 _public prototype_ `virtual void Serialize(class FArchive& Ar) override;`
- L58 _public function_ `virtual uint64 GetSampleCounter() const override`

#### struct `FVoiceDataImpl`  
`struct FVoiceDataImpl`  
_L63-72_
- desc: Holds the current voice packet data state
- L66 _public member_ `FVoicePacketImpl LocalPackets[MAX_SPLITSCREEN_TALKERS];` — Data used by the local talkers before sent
- L68 _public member_ `FVoicePacketList RemotePackets;` — Holds the set of received packets that need to be processed
- L70 _public function_ `FVoiceDataImpl()`
- L71 _public prototype_ `~FVoiceDataImpl() = default;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L11 _macro_ `#define DEBUG_VOICE_PACKET_ENCODING 0`

### `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/VoipListenerSynthComponent.h` (Public)


#### class `FDebugFMTone`  
`class FDebugFMTone`  
_L17-34_
- L20 _public prototype_ `FDebugFMTone() = default;`
- L21 _public prototype_ `FDebugFMTone(float InSampleRate, float InCarrierFreq, float InModFreq, float InCarrierAmp, float InModAmp);`
- L23 _public prototype_ `void Generate(int16* BufferPtr, int32 NumSamples);`
- L26 _private member_ `float SampleRate;`
- L27 _private member_ `float CarrierFreq;`
- L28 _private member_ `float CarrierAmp;`
- L30 _private member_ `float ModFreq;`
- L31 _private member_ `float ModAmp;`
- L33 _private member_ `int32 n;`

#### class `UVoipListenerSynthComponent`  
`class UVoipListenerSynthComponent : public USynthComponent`  
_L38-132_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USynthComponent`
- L44 _private prototype_ `virtual bool Init(int32& SampleRate) override;` — Called when synth is created
- L47 _private prototype_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;` — Called to generate more audio
- L50 _public prototype_ `~UVoipListenerSynthComponent();`
- L59 _public prototype_ `void OpenPacketStream(uint64 BeginningSampleCount, int32 BufferSize, float JitterDelay);` — Start accepting packets with a given delay for buffering. @param BeginningSampleCount The expected sample count of the first packet buffered. after this function is called. @param BufferSize that amount of packets we should reserve memory for. @param JitterDelay the amount of time we wait before we start playing audio from submitted packets.
- L64 _public prototype_ `void ClosePacketStream();` — Close an open packet stream and start outputting silence.
- L71 _public prototype_ `void ResetBuffer(int32 InStartSample, float JitterDelay);` — Reset the packet stream buffer if it's already open. Using this call prevents memory churn. @param InStartSample The expected sample count of the first packet buffered after this function is called. @param JitterDelay The amount of time we wait before we start playing audio from submitted packets.
- L80 _public prototype_ `void SubmitPacket(void* InBuffer, int32 NumBytes, int64 InStartSample, EVoipStreamDataFormat DataFormat);` — Submit a packet to be enqueued for playback. This should be called AFTER a the stream is opened with OpenPacketStream(). @param InBuffer pointer to a single channel buffer of audio samples. @param NumBytes the number of bytes referenced by InBuffer. @param InStartSample the Starting Sample associated with this packet. @param DataFormat the format of this sample (float, fixed16, etc.)
- L85 _public prototype_ `void ConnectToSplitter(Audio::FPatchMixerSplitter& InSplitter);` — Optionally connect this VOIP Synth Component to a splitter.
- L95 _public prototype_ `bool IsIdling();` — `UFUNCTION(BlueprintCallable, Category = "Audio|Voice|Sender")` — Thread safe way to get whether this synth component still has buffered packets of audio to play back. This function is used by the Voice Engine to clean up voice sounds when they are not playing back audio to make space for other sounds to be rendered. @returns true if this synth component is out of audio to play.
- L102 _public prototype_ `uint64 GetSampleCounter();` — This function returns the more recent sample counter of the packet currently getting played. This may prove useful for strongly timing events off of VOIP playback, since VOIP playback has a highly variable amount of delay.
- L105 _public prototype_ `virtual void BeginDestroy() override;`
- L111 _private prototype_ `void ForceResync();` — This call will check how much audio we have buffered and drop the oldest audio if necessary.
- L115 _private member_ `Audio::FPatchInput ExternalSend;` — This patch input can optionally be set
- L118 _private member_ `TUniquePtr<FVoicePacketBuffer> PacketBuffer;` — This is allocated on OpenPacketStream()
- L119 _private member_ `FCriticalSection PacketBufferCriticalSection;`
- L121 _private member_ `float MySampleRate;`
- L123 _private member_ `int32 PreDelaySampleCounter;`
- L126 _private member_ `float JitterDelayInSeconds;` — The amount of audio we keep buffered to reduce underruns.
- L129 _private member_ `FDebugFMTone FMToneGenerator;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESUBSYSTEMUTILS_API`
- L14 _macro_ `#define DEBUG_BUFFERING 0`
