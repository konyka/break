# Plugins / Rejoin

- module root: `Plugins/Online/OnlineFramework/Source/Rejoin`
- headers: 2; symbols: 65
- symbol kinds: class=2, delegate=3, enum=2, enumerator=12, function=10, macro=1, member=9, prototype=25, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, OnlineSubsystem, OnlineSubsystemUtils

### `Plugins/Online/OnlineFramework/Source/Rejoin/Public/RejoinCheck.h` (Public)


#### enum `ERejoinStatus`  
`enum class ERejoinStatus : uint8`  
_L16-28_
- reflection: `UENUM(BlueprintType)`
- desc: Possible states that a rejoin check can be in at any given time
- L19 _public enumerator_ `NoMatchToRejoin` — There is no match to rejoin.  The user is already in a match or there is no match in progress for the user.
- L21 _public enumerator_ `RejoinAvailable` — There is a rejoin available for the user
- L23 _public enumerator_ `UpdatingStatus` — We are currently updating the status of rejoin
- L25 _public enumerator_ `NeedsRecheck` — We need to recheck the state before allowing any further progress through the UI (e.g right after login or right after leaving a match without it ending normally).
- L27 _public enumerator_ `NoMatchToRejoin_MatchEnded` — Match ended normally, no check required (only set when returning from a match)

#### enum `ERejoinAttemptResult`  
`enum class ERejoinAttemptResult : uint8`  
_L48-64_
- desc: Possible end conditions that a rejoin attempt can be in after a user indicates intent to rejoin a session
- L51 _public enumerator_ `RejoinFailure` — Generic failure
- L53 _public enumerator_ `RejoinInProgress` — Already trying to rejoin
- L55 _public enumerator_ `RejoinSuccess` — Successfully going to travel into match
- L57 _public enumerator_ `NothingToRejoin` — Match disappeared while trying to join it
- L59 _public enumerator_ `InvalidSessionFailure` — Session interface failure
- L61 _public enumerator_ `JoinSessionFailure` — Join Session failure
- L63 _public enumerator_ `RejoinTravelFailure` — Failure trying to travel to session

#### class `URejoinCheck`  
`class URejoinCheck : public UObject`  
_L77-263_
- reflection: `UCLASS(MinimalAPI, abstract, Config=Engine)`
- inherits: `UObject`
- desc: Class responsible for maintaining the status/availability of a session already in progress for a client to join
- L83 _public prototype_ `URejoinCheck();`
- L91 _public prototype_ `virtual void CheckRejoinStatus(const FOnRejoinCheckComplete& CompletionDelegate = FOnRejoinCheckComplete());` — Check the backend for the existence of game session that the local player is registered with It will continue to return a valid value until that session is complete @param CompletionDelegate delegate called after the check for possible rejoin is complete
- L99 _public prototype_ `void RejoinLastSession(const FOnRejoinLastSessionComplete& InCompletionDelegate);` — Rejoin the last session if one is found.  One final call to CheckRejoinStatus is made to verify the session still exists @param InCompletionDelegate delegate called after the rejoin attempt is complete
- L106 _public prototype_ `void SetStatus(ERejoinStatus NewStatus);` — Manually set the status of rejoins.  Used when entering/leaving a map as a hint for future check requirements @param NewStatus change current status to a new value
- L111 _public function_ `FOnRejoinCheckStatusChanged& OnRejoinCheckStatusChanged()` — Access to the multicast delegate fired when a rejoin check status update is given
- L116 _public prototype_ `virtual bool IsRejoinCheckEnabled() const;`
- L121 _public prototype_ `virtual void Reset();` — Reset the rejoin state. Sets status to NeedsRecheck, clears the cached search result, timer, and flags.
- L128 _public function_ `ERejoinStatus GetStatus() const`
- L130 _public prototype_ `ERejoinStatus GetStatus() const;`
- L134 _public prototype_ `bool HasCompletedCheck() const;` — @return True if the rejoin check has completed and does not need to be rerun.
- L137 _public prototype_ `bool IsRejoinAvailable() const;` — @return True if it's possible that there's a match to rejoin
- L146 _protected prototype_ `virtual void OnRejoinFailure(ERejoinAttemptResult Result);` — Called any time there is a failure to complete the attempted rejoin @param Result rejoin failure reason
- L152 _protected prototype_ `void TravelToSession();` — Use the search result to travel to the given server session Called after a session has been joined by the online platform
- L159 _protected function_ `const FOnlineSessionSearchResult& GetSearchResult() const` — @return the search result that is currently associated with a rejoin
- L161 _protected function_ `bool IsAttemptingRejoin() const` — @return true if a rejoin attempt is in progress
- L163 _protected prototype_ `UWorld* GetWorld() const;`
- L166 _protected function_ `template<typename T> T* GetGameInstance() const`
- L172 _protected prototype_ `void ClearTimers();` — Clear all timers associated with rejoin
- L176 _protected member_ `ERejoinStatus LastKnownStatus;` — `UPROPERTY()` — Rejoin status
- L182 _private member_ `bool bRejoinAfterCheck;` — `UPROPERTY()` — Flag set during a possible brief period where the user hit rejoin but the check was already in flight
- L185 _private member_ `bool bAttemptingRejoin;` — `UPROPERTY()` — Is a rejoin attempt in progress, prevents reentry
- L189 _private member_ `bool bShouldRecheckIfRejoinCheckUnsuccessful = true;` — `UPROPERTY(Config)` — Defines our default behavior if a rejoin check is unsuccessful, namely, should we recheck?
- L192 _private member_ `FOnlineSessionSearchResult SearchResult;` — Cached value of the last session expected to rejoin
- L195 _private member_ `FOnRejoinCheckStatusChanged RejoinCheckStatusChanged;` — Delegate fired when rejoin check status changes
- L198 _private member_ `FDelegateHandle FindFriendSessionCompleteDelegateHandle;` — FindFriendSession delegate handle if a call is in flight
- L200 _private member_ `FTimerHandle RejoinCheckTimerHandle;` — Handle to the possibly active timer for another rejoin check
- L203 _private member_ `FOnRejoinLastSessionComplete RejoinLastSessionCompleteDelegate;` — Delegate fired when a rejoin attempt completed
- L204 _private function_ `FOnRejoinLastSessionComplete& OnRejoinLastSessionComplete()`
- L213 _private prototype_ `virtual ERejoinStatus GetRejoinStateFromSearchResult(const FOnlineSessionSearchResult& InSearchResult) const PURE_VIRTUAL(URejoinCheck::GetRejoinStateFromSearchResult, return ERejoinStatus::NeedsRecheck;);` — Interpret a given search result for the possible need to rejoin an existing session @param InSearchResult search result discovered to be related to the locally logged in user @return a rejoin status code that indicates whether or not this result should be pursued
- L223 _private prototype_ `void OnCheckRejoinComplete(int32 ControllerId, bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& InSearchResults, FOnRejoinCheckComplete InCompletionDelegate);` — Delegate fired when a rejoin check has completed @param ControllerId controller id of the calling user @param bWasSuccessful did the call reach the backend and return with a valid result @param InSearchSearch possibly valid search result to rejoin depending on the success of the call @param InCompletionDelegate external delegate to call after finishing internal code
- L232 _private prototype_ `void ProcessRejoinCheck(bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& InSearchResults, const FOnRejoinCheckComplete& InCompletionDelegate);` — Common function for handling the result of a rejoin check @param bWasSuccessful did the call reach the backend and return with a valid result @param InSearchSearch possibly valid search result to rejoin depending on the success of the call @param InCompletionDelegate external delegate to call after finishing internal code
- L239 _private prototype_ `void OnFinalRejoinCheckComplete(ERejoinStatus Result);` — Delegate fired after the last rejoin check completed with the intention of joining a search result if valid @param Result final result of the rejoin check
- L245 _private prototype_ `virtual void RejoinViaSession() PURE_VIRTUAL(URejoinCheck::RejoinViaSession, );` — Game specific method to rejoin the last session in progress Use OnRejoinFailure to communicate with base class the state of the rejoin
- L250 _private prototype_ `void StartRejoinChecks();` — Set the timer for another rejoin search after a given time period
- L255 _private prototype_ `void RejoinCheckTimer();` — Called after the rejoin check timer expires to make another backend request
- L261 _private function_ `virtual void Analytics_RecordRejoinDetected(const FOnlineSessionSearchResult& InSearchResult) const`
- L262 _private function_ `virtual void Analytics_RecordRejoinAttempt(const FOnlineSessionSearchResult& InSearchResult, ERejoinAttemptResult InAttemptResult) const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API REJOIN_API`
- L35 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRejoinCheckComplete, ERejoinStatus );` — Delegate fired when a rejoin check has completed against the backend @param RejoinStatus status of the rejoin check attempt
- L35 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRejoinCheckComplete, ERejoinStatus );` — Delegate fired when a rejoin check has completed against the backend @param RejoinStatus status of the rejoin check attempt
- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRejoinCheckStatusChanged, ERejoinStatus );` — Multicast delegate fired when a rejoin check state has changed @param NewStatus newest status of the rejoin check attempt
- L42 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRejoinCheckStatusChanged, ERejoinStatus );` — Multicast delegate fired when a rejoin check state has changed @param NewStatus newest status of the rejoin check attempt
- L43 _typedef_ `typedef FOnRejoinCheckStatusChanged::FDelegate FOnRejoinCheckStatusChangedDelegate;`
- L71 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRejoinLastSessionComplete, ERejoinAttemptResult );` — Delegate fired at the completion of an attempt to rejoin a session @param RejoinResult status of the rejoin attempt
- L71 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRejoinLastSessionComplete, ERejoinAttemptResult );` — Delegate fired at the completion of an attempt to rejoin a session @param RejoinResult status of the rejoin attempt
- L265 _function_ `inline const TCHAR* ToString(ERejoinStatus Result)`
- L294 _function_ `inline const TCHAR* ToString(ERejoinAttemptResult Result)`

### `Plugins/Online/OnlineFramework/Source/Rejoin/Public/RejoinModule.h` (Public)


#### class `FRejoinModule`  
`class FRejoinModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- desc: Module for Rejoin base implementation
- L15 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L16 _private prototype_ `virtual void ShutdownModule() override;`
