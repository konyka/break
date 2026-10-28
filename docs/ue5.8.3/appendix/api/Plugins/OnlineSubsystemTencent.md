# Plugins / OnlineSubsystemTencent

- module root: `Plugins/Online/OnlineSubsystemTencent/Source`
- headers: 22; symbols: 1117
- symbol kinds: class=64, delegate=21, function=160, macro=15, member=223, prototype=573, struct=26, typedef=35
- PrivateDependencyModuleNames: Engine, HTTP, Json, OnlineSubsystem, OnlineSubsystemUtils, PacketHandler, PlayTimeLimit, Sockets
- PublicDependencyModuleNames: Core, CoreUObject
- PublicIncludePathModuleNames: Tencent, WeGame

### `Plugins/Online/OnlineSubsystemTencent/Source/Private/OnlineAsyncTaskManagerTencent.h` (Private)


#### class `FOnlineAsyncTaskManagerTencent`  
`class FOnlineAsyncTaskManagerTencent : public FOnlineAsyncTaskManager, public rail::IRailEvent #else class FOnlineAsyncTaskManagerTencent : public FOnlineAsyncTaskManager #endif`  
_L21-79_
- inherits: `FOnlineAsyncTaskManager,rail::IRailEvent`
- L29 _protected member_ `FOnlineSubsystemTencent* Subsystem;` — Cached reference to the main online subsystem
- L31 _protected prototype_ `FOnlineAsyncTaskManagerTencent();`
- L35 _public prototype_ `FOnlineAsyncTaskManagerTencent(FOnlineSubsystemTencent* InSubsystem);`
- L36 _public prototype_ `~FOnlineAsyncTaskManagerTencent();`
- L44 _public prototype_ `virtual void OnlineTick() override;` — ** CALL ONLY FROM ONLINE THREAD ** Give the online service a chance to do work
- L47 _public prototype_ `void RegisterRailEvents();`
- L48 _public prototype_ `void UnregisterRailEvents();`
- L50 _public prototype_ `void OnRailSystemStateChanged(const rail::rail_event::RailSystemStateChanged* param);`
- L52 _public prototype_ `void OnRailShowFloatingWindow(const rail::rail_event::ShowFloatingWindowResult* param);` — Event notification that any of the floating windows have been opened or closed
- L53 _public prototype_ `void OnRailShowFloatingNotifyWindow(const rail::rail_event::ShowNotifyWindow* param);`
- L54 _public prototype_ `void OnRailInviteSentNotification(const rail::rail_event::RailUsersNotifyInviter* param);`
- L55 _public prototype_ `void OnRailInviteUsersResult(const rail::rail_event::RailUsersInviteUsersResult* param);`
- L56 _public prototype_ `void OnRailInviteJoinGameResult(const rail::rail_event::RailUsersInviteJoinGameResult* param);`
- L57 _public prototype_ `void OnRailFriendsInviteRespondInvitation(const rail::rail_event::RailUsersRespondInvitation* param);`
- L58 _public prototype_ `void OnRailFriendsJoinGameByUser(const rail::rail_event::RailPlatformNotifyEventJoinGameByUser* param);`
- L59 _public prototype_ `void OnRailAssetsChanged(const rail::rail_event::RailAssetsChanged* param);`
- L60 _public prototype_ `void OnRailGetUsersInfo(const rail::rail_event::RailUsersInfoData* param);`
- L61 _public prototype_ `void OnRailGetFriendPlayedGamesResult(const rail::rail_event::RailFriendsQueryFriendPlayedGamesResult* param);`
- L62 _public prototype_ `void OnRailInviteCommandline(const rail::rail_event::RailFriendsGetInviteCommandLine* param);`
- L63 _public prototype_ `void OnRailCancelInviteResult(const rail::rail_event::RailUsersCancelInviteResult* param);`
- L64 _public prototype_ `void OnRailFriendsSetMetadataResult(const rail::rail_event::RailFriendsSetMetadataResult* param);`
- L65 _public prototype_ `void OnRailEventFriendsAddFriendResult(const rail::rail_event::RailFriendsAddFriendResult* param);`
- L66 _public prototype_ `void OnRailFriendsListChanged(const rail::rail_event::RailFriendsListChanged* param);`
- L68 _public prototype_ `void OnRailFriendsOnlineStateChanged(const rail::rail_event::RailFriendsOnlineStateChanged* param);` — Event notification that remote friend online state has changed
- L70 _public prototype_ `void OnRailFriendsMetadataChanged(const rail::rail_event::RailFriendsMetadataChanged* param);` — Event notification that remote friend metadata keys/values have changed
- L73 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L76 _public member_ `TSet<rail::RAIL_EVENT_ID> RegisteredRailEvents;`

### `Plugins/Online/OnlineSubsystemTencent/Source/Private/OnlineAsyncTasksTencent.h` (Private)


#### class `FOnlineAsyncTaskRail`  
`class FOnlineAsyncTaskRail : public FOnlineAsyncTaskBasic<FOnlineSubsystemTencent>, public rail::IRailEvent`  
_L32-78_
- inherits: `FOnlineAsyncTaskBasic<FOnlineSubsystemTencent>,rail::IRailEvent`
- desc: Base class that holds a delegate to fire when a given async task is complete
- L37 _public prototype_ `FOnlineAsyncTaskRail() = delete;`
- L38 _public function_ `FOnlineAsyncTaskRail(FOnlineSubsystemTencent* InSubsystem, TSet<rail::RAIL_EVENT_ID> InRegisteredRailEvents) : FOnlineAsyncTaskBasic(InSubsystem) , RegisteredRailEvents(InRegisteredRailEvents)`
- L44 _public prototype_ `virtual ~FOnlineAsyncTaskRail() = default;`
- L47 _public prototype_ `virtual void Initialize() override;`
- L48 _public prototype_ `virtual void Finalize() override;`
- L49 _public prototype_ `virtual void Tick() override;`
- L60 _protected prototype_ `void ParseRailResult(rail::RailResult InResult, FOnlineError& OutOnlineError) const;` — Convert a raw Rail result into something resembling an FOnlineError @param InResult any rail result @param OutOnlineError the converted error result
- L68 _protected prototype_ `void ParseRailResult(const rail::EventBase* InResult, FOnlineError& OutOnlineError) const;` — Parse a Rail event into something resembling an FOnlineError @param InResult any rail event @param OutOnlineError the converted error result
- L74 _protected member_ `bool bCanTimeout = true;` — Can this task timeout? Most tasks are able to timeout.
- L77 _protected member_ `TSet<rail::RAIL_EVENT_ID> RegisteredRailEvents;` — Events registered with this task

#### class `FOnlineAsyncEventRail`  
`class FOnlineAsyncEventRail : public FOnlineAsyncEvent<FOnlineSubsystemTencent>`  
_L80-108_
- inherits: `FOnlineAsyncEvent<FOnlineSubsystemTencent>`
- L85 _public prototype_ `FOnlineAsyncEventRail() = delete;`
- L86 _public function_ `FOnlineAsyncEventRail(FOnlineSubsystemTencent* InSubsystem) : FOnlineAsyncEvent(InSubsystem)`
- L91 _public prototype_ `virtual ~FOnlineAsyncEventRail() = default;`
- L99 _public prototype_ `void ParseRailResult(rail::RailResult InResult, FOnlineError& OutOnlineError) const;` — Convert a raw Rail result into something resembling an FOnlineError @param InResult any rail result @param OutOnlineError the converted error result
- L107 _public prototype_ `void ParseRailResult(const rail::EventBase* InResult, FOnlineError& OutOnlineError) const;` — Parse a Rail event into something resembling an FOnlineError @param InResult any rail event @param OutOnlineError the converted error result

#### class `FOnlineAsyncTaskRailAcquireSessionTicket`  
`class FOnlineAsyncTaskRailAcquireSessionTicket : public FOnlineAsyncTaskRail`  
_L110-151_
- inherits: `FOnlineAsyncTaskRail`
- L115 _public prototype_ `DECLARE_DELEGATE_TwoParams(FCompletionDelegate, const FOnlineError& , const FString& );`
- L117 _public prototype_ `FOnlineAsyncTaskRailAcquireSessionTicket() = delete;`
- L118 _public function_ `FOnlineAsyncTaskRailAcquireSessionTicket(FOnlineSubsystemTencent* InSubsystem, rail::RailID InPlayerId, const FCompletionDelegate& InCompletionDelegate) : FOnlineAsyncTaskRail(InSubsystem, {rail::kRailEventSessionTicketGetSessionTicket}) , PlayerId(InPlayerId) , CompletionDelegate(InCompletionDelegate)`
- L125 _public function_ `virtual ~FOnlineAsyncTaskRailAcquireSessionTicket()`
- L130 _public prototype_ `virtual void Initialize() override;`
- L131 _public prototype_ `virtual void TriggerDelegates() override;`
- L132 _public function_ `virtual FString ToString() const override`
- L136 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID EventId, rail::EventBase* Param) override;`
- L141 _protected prototype_ `void OnRailGetSessionTicket(const rail::rail_event::AcquireSessionTicketResponse* SessionTicketResponse);`
- L144 _protected member_ `rail::RailID PlayerId;` — Player id we are obtaining the auth session for
- L146 _protected member_ `FOnlineError OnlineError;` — The result
- L148 _protected member_ `FString SessionTicket;` — The acquired session ticket
- L150 _protected member_ `FCompletionDelegate CompletionDelegate;` — Function to fire when complete

#### struct `FFloatingWindowTaskResult`  
`struct FFloatingWindowTaskResult`  
_L156-167_
- desc: Result structure after opening/closing a floating window
- L158 _public function_ `FFloatingWindowTaskResult() : bOpened(false)`
- L164 _public member_ `FOnlineError Error;` — Error information
- L166 _public member_ `bool bOpened;` — State of the floating window

#### class `FOnlineAsyncTaskRailShowFloatingWindow`  
`class FOnlineAsyncTaskRailShowFloatingWindow : public FOnlineAsyncTaskRail`  
_L169-205_
- inherits: `FOnlineAsyncTaskRail`
- L175 _public prototype_ `FOnlineAsyncTaskRailShowFloatingWindow() = delete;`
- L176 _public function_ `FOnlineAsyncTaskRailShowFloatingWindow(FOnlineSubsystemTencent* InSubsystem, rail::EnumRailWindowType InWindowType) : FOnlineAsyncTaskRail(InSubsystem, {rail::kRailEventShowFloatingWindow}) , WindowType(InWindowType)`
- L182 _public function_ `virtual ~FOnlineAsyncTaskRailShowFloatingWindow()`
- L187 _public prototype_ `virtual void Initialize() override;`
- L188 _public prototype_ `virtual void Finalize() override;`
- L189 _public prototype_ `virtual void TriggerDelegates() override;`
- L190 _public function_ `virtual FString ToString() const override`
- L194 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L199 _protected prototype_ `void OnRailShowFloatingWindow(rail::rail_event::ShowFloatingWindowResult* param);`
- L202 _protected member_ `FFloatingWindowTaskResult TaskResult;` — Result of the task
- L204 _protected member_ `rail::EnumRailWindowType WindowType;` — Type of window to open

#### struct `FSetUserMetadataTaskResult`  
`struct FSetUserMetadataTaskResult`  
_L210-216_
- desc: Result structure after setting user metadata / presence
- L213 _public member_ `FOnlineError Error;` — Error information
- L215 _public member_ `TMap<FString, FString> FinalData;` — Key/Value pairs in string form used with this task

#### class `FOnlineAsyncTaskRailSetUserMetadata`  
`class FOnlineAsyncTaskRailSetUserMetadata : public FOnlineAsyncTaskRail`  
_L225-272_
- inherits: `FOnlineAsyncTaskRail`
- L231 _public prototype_ `FOnlineAsyncTaskRailSetUserMetadata() = delete;`
- L232 _public function_ `FOnlineAsyncTaskRailSetUserMetadata(FOnlineSubsystemTencent* InSubsystem, const FMetadataPropertiesRail& InMetdata, const FOnOnlineAsyncTaskRailSetUserMetadataComplete& InCompletionDelegate) : FOnlineAsyncTaskRail(InSubsystem, {rail::kRailEventFriendsSetMetadataResult}) , Metadata(InMetdata) , CompletionDelegate(InCompletionDelegate)`
- L239 _public function_ `virtual ~FOnlineAsyncTaskRailSetUserMetadata()`
- L244 _public prototype_ `virtual void Initialize() override;`
- L245 _public prototype_ `virtual void Finalize() override;`
- L246 _public prototype_ `virtual void TriggerDelegates() override;`
- L247 _public function_ `virtual FString ToString() const override`
- L251 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L263 _protected prototype_ `virtual bool GenerateRailMetadata(FMetadataPropertiesRail& InMetadata, TMap<FString, FString>& OutFinalData, rail::RailArray<rail::RailKeyValue>& OutRailKeyValuePairs);` — Given an input of local metadata, populate a list of key value pairs for consumption by RailSDK @param InMetadata local metadata to convert to RailSDK @param OutFinalData map of data in final format @param OutRailKeyValuePairs list of keys and their values
- L264 _protected prototype_ `void OnRailEventFriendsSetMetadataResult(const rail::rail_event::RailFriendsSetMetadataResult* MetadataResult);`
- L267 _protected member_ `FMetadataPropertiesRail Metadata;` — Input metadata information
- L269 _protected member_ `FSetUserMetadataTaskResult TaskResult;` — Output presence result
- L271 _protected member_ `FOnOnlineAsyncTaskRailSetUserMetadataComplete CompletionDelegate;` — Delegate to fire on completion

#### class `FOnlineAsyncTaskRailSetUserPresence`  
`class FOnlineAsyncTaskRailSetUserPresence : public FOnlineAsyncTaskRailSetUserMetadata`  
_L278-303_
- inherits: `FOnlineAsyncTaskRailSetUserMetadata`
- desc: Builds on FOnlineAsyncTaskRailSetUserMetadata to provide the ability to dynamically store multiple keys by storing an additional key with a list of the others
- L284 _public prototype_ `FOnlineAsyncTaskRailSetUserPresence() = delete;`
- L285 _public function_ `FOnlineAsyncTaskRailSetUserPresence(FOnlineSubsystemTencent* InSubsystem, const FMetadataPropertiesRail& InMetdata, const FOnOnlineAsyncTaskRailSetUserMetadataComplete& InCompletionDelegate) : FOnlineAsyncTaskRailSetUserMetadata(InSubsystem, InMetdata, InCompletionDelegate)`
- L290 _public function_ `virtual ~FOnlineAsyncTaskRailSetUserPresence()`
- L295 _public function_ `virtual FString ToString() const override`
- L301 _protected prototype_ `virtual bool GenerateRailMetadata(FMetadataPropertiesRail& InMetadata, TMap<FString, FString>& OutFinalData, rail::RailArray<rail::RailKeyValue>& OutRailKeyValuePairs) override;`

#### class `FOnlineAsyncTaskRailSetSessionMetadata`  
`class FOnlineAsyncTaskRailSetSessionMetadata : public FOnlineAsyncTaskRailSetUserMetadata`  
_L305-326_
- inherits: `FOnlineAsyncTaskRailSetUserMetadata`
- L311 _public prototype_ `FOnlineAsyncTaskRailSetSessionMetadata() = delete;`
- L312 _public function_ `FOnlineAsyncTaskRailSetSessionMetadata(FOnlineSubsystemTencent* InSubsystem, const FMetadataPropertiesRail& InMetdata, const FOnOnlineAsyncTaskRailSetUserMetadataComplete& InCompletionDelegate) : FOnlineAsyncTaskRailSetUserMetadata(InSubsystem, InMetdata, InCompletionDelegate)`
- L317 _public function_ `virtual ~FOnlineAsyncTaskRailSetSessionMetadata()`
- L322 _public prototype_ `virtual void Initialize() override;`
- L323 _public prototype_ `virtual void Finalize() override;`
- L324 _public function_ `virtual FString ToString() const override`

#### class `FOnlineAsyncTaskRailSetInviteCommandline`  
`class FOnlineAsyncTaskRailSetInviteCommandline : public FOnlineAsyncTaskRail`  
_L330-369_
- inherits: `FOnlineAsyncTaskRail`
- L336 _public prototype_ `FOnlineAsyncTaskRailSetInviteCommandline() = delete;`
- L337 _public function_ `FOnlineAsyncTaskRailSetInviteCommandline(FOnlineSubsystemTencent* InSubsystem, const FString& InCmdline, const FOnOnlineAsyncTaskRailSetInviteCommandlineComplete& InCompletionDelegate) : FOnlineAsyncTaskRail(InSubsystem, {rail::kRailEventFriendsSetMetadataResult}) , Cmdline(InCmdline) , CompletionDelegate(InCompletionDelegate)`
- L344 _public function_ `virtual ~FOnlineAsyncTaskRailSetInviteCommandline()`
- L349 _public prototype_ `virtual void Initialize() override;`
- L350 _public prototype_ `virtual void Finalize() override;`
- L351 _public prototype_ `virtual void TriggerDelegates() override;`
- L352 _public function_ `virtual FString ToString() const override`
- L356 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L361 _protected prototype_ `void OnRailEventFriendsSetMetadataResult(const rail::rail_event::RailFriendsSetMetadataResult* MetadataResult);`
- L364 _protected member_ `FString Cmdline;` — Command line to store with the backend
- L366 _protected member_ `FSetUserMetadataTaskResult TaskResult;` — Output result of this call
- L368 _protected member_ `FOnOnlineAsyncTaskRailSetInviteCommandlineComplete CompletionDelegate;` — Delegate to fire on completion

#### struct `FGetUserMetadataTaskResult`  
`struct FGetUserMetadataTaskResult`  
_L374-382_
- desc: Result structure after getting user metadata / presence
- L377 _public member_ `FOnlineError Error;` — Error information
- L379 _public member_ `FUniqueNetIdRailPtr UserId;` — User whose presence was retrieved
- L381 _public member_ `FMetadataPropertiesRail Metadata;` — Retrieved presence information

#### class `FOnlineAsyncTaskRailGetUserMetadata`  
`class FOnlineAsyncTaskRailGetUserMetadata : public FOnlineAsyncTaskRail`  
_L391-430_
- inherits: `FOnlineAsyncTaskRail`
- L397 _public prototype_ `FOnlineAsyncTaskRailGetUserMetadata() = delete;`
- L398 _public prototype_ `FOnlineAsyncTaskRailGetUserMetadata(FOnlineSubsystemTencent* InSubsystem, const FUniqueNetIdRail& InUserId, const TArray<FString>& InMetadataKeys, const FOnOnlineAsyncTaskRailGetUserMetadataComplete& InCompletionDelegate);`
- L399 _public prototype_ `virtual ~FOnlineAsyncTaskRailGetUserMetadata();`
- L402 _public prototype_ `virtual void Initialize() override;`
- L403 _public prototype_ `virtual void Finalize() override;`
- L404 _public prototype_ `virtual void TriggerDelegates() override;`
- L405 _public prototype_ `virtual FString ToString() const override;`
- L409 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L419 _protected prototype_ `rail::RailResult QueryMetadata(const TArray<FString>& InMetadata);` — Retrieve a list of metadata key value pairs @param InMetadata list of keys to retrieve from the user specified by this task
- L420 _protected prototype_ `virtual void OnRailEventFriendsGetMetadataResult(const rail::rail_event::RailFriendsGetMetadataResult* MetadataResult);`
- L423 _protected member_ `rail::RailID RailUserId;` — User to query presence for
- L425 _protected member_ `TArray<FString> MetadataKeys;` — Presence retrieved for this user
- L427 _protected member_ `FGetUserMetadataTaskResult TaskResult;` — Output result from the task
- L429 _protected member_ `FOnOnlineAsyncTaskRailGetUserMetadataComplete CompletionDelegate;` — Delegate to fire when this task is completed

#### class `FOnlineAsyncTaskRailGetUserPresence`  
`class FOnlineAsyncTaskRailGetUserPresence : public FOnlineAsyncTaskRailGetUserMetadata`  
_L436-456_
- inherits: `FOnlineAsyncTaskRailGetUserMetadata`
- desc: Builds on FOnlineAsyncTaskRailGetUserMetadata to provide the ability to dynamically retrieve multiple keys from an additional key with a list of the others
- L442 _public prototype_ `FOnlineAsyncTaskRailGetUserPresence() = delete;`
- L443 _public prototype_ `FOnlineAsyncTaskRailGetUserPresence(FOnlineSubsystemTencent* InSubsystem, const FUniqueNetIdRail& InUserId, const FOnOnlineAsyncTaskRailGetUserMetadataComplete& InCompletionDelegate);`
- L444 _public prototype_ `virtual ~FOnlineAsyncTaskRailGetUserPresence();`
- L447 _public prototype_ `virtual void Initialize() override;`
- L448 _public prototype_ `virtual FString ToString() const override;`
- L454 _protected member_ `bool bKeysQueried;` — Has the list of keys been queried
- L455 _protected prototype_ `virtual void OnRailEventFriendsGetMetadataResult(const rail::rail_event::RailFriendsGetMetadataResult* MetadataResult) override;`

#### struct `FGetInviteCommandLineTaskResult`  
`struct FGetInviteCommandLineTaskResult`  
_L461-469_
- desc: Result structure after getting a user command line invite
- L464 _public member_ `FOnlineError Error;` — Error information
- L466 _public member_ `FUniqueNetIdRailPtr UserId;` — User whose command line invite was retrieved
- L468 _public member_ `FString Commandline;` — Retrieved command line

#### class `FOnlineAsyncTaskRailGetInviteCommandline`  
`class FOnlineAsyncTaskRailGetInviteCommandline : public FOnlineAsyncTaskRail`  
_L473-504_
- inherits: `FOnlineAsyncTaskRail`
- L479 _public prototype_ `FOnlineAsyncTaskRailGetInviteCommandline() = delete;`
- L480 _public prototype_ `FOnlineAsyncTaskRailGetInviteCommandline(FOnlineSubsystemTencent* InSubsystem, const FUniqueNetIdRail& InUserId, const FOnOnlineAsyncTaskRailGetInviteCommandLineComplete& InCompletionDelegate);`
- L481 _public prototype_ `virtual ~FOnlineAsyncTaskRailGetInviteCommandline();`
- L484 _public prototype_ `virtual void Initialize() override;`
- L485 _public prototype_ `virtual void Finalize() override;`
- L486 _public prototype_ `virtual void TriggerDelegates() override;`
- L487 _public function_ `virtual FString ToString() const override`
- L491 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L496 _protected prototype_ `void OnRailEventFriendsGetInviteCommandLine(const rail::rail_event::RailFriendsGetInviteCommandLine* InviteResult);`
- L499 _protected member_ `rail::RailID RailUserId;` — User to query presence for
- L501 _protected member_ `FGetInviteCommandLineTaskResult TaskResult;` — Output result from the task
- L503 _protected member_ `FOnOnlineAsyncTaskRailGetInviteCommandLineComplete CompletionDelegate;` — Delegate to fire when this task is completed

#### struct `FGetUserInviteTaskResult`  
`struct FGetUserInviteTaskResult`  
_L509-519_
- desc: Result structure after getting a complete user invite
- L512 _public member_ `FOnlineError Error;` — Error information
- L514 _public member_ `FUniqueNetIdRailPtr UserId;` — User whose invite was retrieved
- L516 _public member_ `FMetadataPropertiesRail Metadata;` — Retrieved presence information
- L518 _public member_ `FString Commandline;` — Retrieved presence information

#### class `FOnlineAsyncTaskRailGetUserInvite`  
`class FOnlineAsyncTaskRailGetUserInvite : public FOnlineAsyncTaskRail`  
_L523-575_
- inherits: `FOnlineAsyncTaskRail`
- L529 _public prototype_ `FOnlineAsyncTaskRailGetUserInvite() = delete;`
- L530 _public prototype_ `FOnlineAsyncTaskRailGetUserInvite(FOnlineSubsystemTencent* InSubsystem, const FUniqueNetIdRail& InUserId, const FOnOnlineAsyncTaskRailGetUserInviteComplete& InCompletionDelegate);`
- L531 _public prototype_ `virtual ~FOnlineAsyncTaskRailGetUserInvite();`
- L534 _public prototype_ `virtual void Initialize() override;`
- L535 _public prototype_ `virtual void Finalize() override;`
- L536 _public prototype_ `virtual void TriggerDelegates() override;`
- L537 _public function_ `virtual FString ToString() const override`
- L541 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L546 _protected prototype_ `void OnRailEventFriendsGetMetadataResult(const rail::rail_event::RailFriendsGetMetadataResult* MetadataResult);`
- L547 _protected prototype_ `void OnRailEventFriendsGetInviteCommandLine(const rail::rail_event::RailFriendsGetInviteCommandLine* InviteResult);`
- L549 _protected prototype_ `void OnEventComplete();` — Called when each event completes to check for total completion
- L556 _protected prototype_ `void RetrieveFromInviteCommandLine(const FString& InviteCommandline);` — Get the session invite keys out of the command line @param InviteCommandLine string containing a list of session invite related keys to retrieve from a remote user
- L559 _protected member_ `bool bMetadataReceived;` — Has the metadata callback fired
- L561 _protected member_ `rail::RailResult MetadataReceivedResult;` — Result of the metadata callback
- L563 _protected member_ `bool bCommandLineReceived;` — Has the command line callback fired
- L565 _protected member_ `rail::RailResult CommandLineResult;` — Result of the command line callback
- L568 _protected member_ `rail::RailID RailUserId;` — User to query invite from (Inviter)
- L570 _protected member_ `TArray<FString> MetadataKeys;` — Presence retrieved for this user used to build session search result
- L572 _protected member_ `FGetUserInviteTaskResult TaskResult;` — Output result from the task
- L574 _protected member_ `FOnOnlineAsyncTaskRailGetUserInviteComplete CompletionDelegate;` — Delegate to fire when this task is completed

#### class `FOnlineAsyncTaskRailClearAllMetadata`  
`class FOnlineAsyncTaskRailClearAllMetadata : public FOnlineAsyncTaskRail`  
_L577-605_
- inherits: `FOnlineAsyncTaskRail`
- L583 _public prototype_ `FOnlineAsyncTaskRailClearAllMetadata() = delete;`
- L584 _public prototype_ `FOnlineAsyncTaskRailClearAllMetadata(FOnlineSubsystemTencent* InSubsystem, const FUniqueNetIdRail& InUserId);`
- L585 _public prototype_ `virtual ~FOnlineAsyncTaskRailClearAllMetadata();`
- L588 _public prototype_ `virtual void Initialize() override;`
- L589 _public prototype_ `virtual void Finalize() override;`
- L590 _public prototype_ `virtual void TriggerDelegates() override;`
- L591 _public function_ `virtual FString ToString() const override`
- L595 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L600 _protected prototype_ `void OnRailEventFriendsClearAllMetadataResult(const rail::rail_event::RailFriendsClearMetadataResult* MetadataResult);`
- L603 _protected member_ `rail::RailID RailUserId;` — User to clear metadata for
- L604 _protected member_ `FOnlineError TaskResult;`

#### class `FOnlineAsyncTaskRailAddFriend`  
`class FOnlineAsyncTaskRailAddFriend : public FOnlineAsyncTaskRail`  
_L614-650_
- inherits: `FOnlineAsyncTaskRail`
- L620 _public prototype_ `FOnlineAsyncTaskRailAddFriend() = delete;`
- L627 _public prototype_ `FOnlineAsyncTaskRailAddFriend(FOnlineSubsystemTencent* InSubsystem, const FUniqueNetIdRail& InUserId, const FOnOnlineAsyncTaskRailAddFriendComplete& InCompletionDelegate);` — Constructor @param InSubsystem the owning subsystem @param InUserId the rail id of the player you want to friend @param InCompletionDelegate the delegate to trigger when this request has completed
- L628 _public prototype_ `virtual ~FOnlineAsyncTaskRailAddFriend();`
- L631 _public prototype_ `virtual void Initialize() override;`
- L632 _public prototype_ `virtual void TriggerDelegates() override;`
- L633 _public function_ `virtual FString ToString() const override`
- L637 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L642 _protected prototype_ `void OnRailEventFriendsAddFriendResult(const rail::rail_event::RailFriendsAddFriendResult* AddFriendResult);`
- L645 _protected member_ `rail::RailID RailUserId;` — User to friend
- L647 _protected member_ `FOnlineError TaskResult;` — The result of the add friend request
- L649 _protected member_ `FOnOnlineAsyncTaskRailAddFriendComplete CompletionDelegate;` — Delegate to trigger on completion

#### struct `FGetUsersInfoTaskResult`  
`struct FGetUsersInfoTaskResult`  
_L655-661_
- desc: Result structure after getting users info
- L658 _public member_ `FOnlineError Error;` — Error information
- L660 _public member_ `TArray<TSharedRef<FOnlineUserInfoTencent>> UserInfos;` — Users successfully queried

#### class `FOnlineAsyncTaskRailGetUsersInfo`  
`class FOnlineAsyncTaskRailGetUsersInfo : public FOnlineAsyncTaskRail`  
_L670-702_
- inherits: `FOnlineAsyncTaskRail`
- L675 _public prototype_ `FOnlineAsyncTaskRailGetUsersInfo() = delete;`
- L676 _public prototype_ `FOnlineAsyncTaskRailGetUsersInfo(FOnlineSubsystemTencent* InSubsystem, const TArray<FUniqueNetIdRef>& InUserIds, const FOnOnlineAsyncTaskRailGetUsersInfoComplete& InCompletionDelegate);`
- L677 _public prototype_ `virtual ~FOnlineAsyncTaskRailGetUsersInfo() = default;`
- L680 _public prototype_ `virtual void Initialize() override;`
- L681 _public prototype_ `virtual void TriggerDelegates() override;`
- L682 _public function_ `virtual FString ToString() const override`
- L686 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L690 _protected prototype_ `void OnRailEventUsersGetUsersInfo(const rail::rail_event::RailUsersInfoData* UsersInfoData);`
- L693 _protected member_ `static FThreadSafeCounter RequestIdCounter;` — Request id counter so we can map rail responses to the correct requests
- L695 _protected member_ `int32 RequestId;` — Our request id
- L697 _protected member_ `TArray<FUniqueNetIdRef> UserIds;` — User to get data for
- L699 _protected member_ `FGetUsersInfoTaskResult TaskResult;` — Result of the task
- L701 _protected member_ `FOnOnlineAsyncTaskRailGetUsersInfoComplete CompletionDelegate;` — Delegate to fire on completion

#### class `FOnlineAsyncEventRailSystemStateChanged`  
`class FOnlineAsyncEventRailSystemStateChanged : public FOnlineAsyncEventRail`  
_L704-731_
- inherits: `FOnlineAsyncEventRail`
- L710 _public prototype_ `FOnlineAsyncEventRailSystemStateChanged() = delete;`
- L711 _public function_ `FOnlineAsyncEventRailSystemStateChanged(FOnlineSubsystemTencent* InSubsystem, const rail::rail_event::RailSystemStateChanged* InParams) : FOnlineAsyncEventRail(InSubsystem) , State(InParams ? InParams->state : rail::RailSystemState::kSystemStateUnknown)`
- L717 _public prototype_ `virtual ~FOnlineAsyncEventRailSystemStateChanged() = default;`
- L720 _public prototype_ `virtual void Finalize() override;`
- L721 _public prototype_ `virtual void TriggerDelegates() override;`
- L722 _public function_ `virtual FString ToString() const override`
- L730 _protected member_ `rail::RailSystemState State;`

#### class `FOnlineAsyncEventRailShowFloatingWindow`  
`class FOnlineAsyncEventRailShowFloatingWindow : public FOnlineAsyncEventRail`  
_L733-756_
- inherits: `FOnlineAsyncEventRail`
- L739 _public prototype_ `FOnlineAsyncEventRailShowFloatingWindow() = delete;`
- L740 _public prototype_ `FOnlineAsyncEventRailShowFloatingWindow(FOnlineSubsystemTencent* InSubsystem, const rail::rail_event::ShowFloatingWindowResult* InParams);`
- L742 _public function_ `virtual ~FOnlineAsyncEventRailShowFloatingWindow()`
- L747 _public prototype_ `virtual void Finalize() override;`
- L748 _public prototype_ `virtual void TriggerDelegates() override;`
- L749 _public function_ `virtual FString ToString() const override`
- L755 _protected member_ `FFloatingWindowTaskResult TaskResult;` — Result of the task

#### struct `FOnlineAsyncEventRailShowFloatingNotifyWindowPayload`  
`struct FOnlineAsyncEventRailShowFloatingNotifyWindowPayload : public FJsonSerializable`  
_L758-775_
- inherits: `FJsonSerializable`
- L763 _public member_ `FString DialogTitle;` — Title of dialog to display
- L765 _public member_ `FString DialogText;` — Text of dialog to display
- L767 _public member_ `FString ButtonText;` — Text to display in OK button

#### class `FOnlineAsyncEventRailShowFloatingNotifyWindow`  
`class FOnlineAsyncEventRailShowFloatingNotifyWindow : public FOnlineAsyncEventRail`  
_L777-798_
- inherits: `FOnlineAsyncEventRail`
- L783 _public prototype_ `FOnlineAsyncEventRailShowFloatingNotifyWindow() = delete;`
- L784 _public prototype_ `FOnlineAsyncEventRailShowFloatingNotifyWindow(FOnlineSubsystemTencent* InSubsystem, const rail::rail_event::ShowNotifyWindow* InParams);`
- L786 _public function_ `virtual ~FOnlineAsyncEventRailShowFloatingNotifyWindow()`
- L791 _public prototype_ `virtual void TriggerDelegates() override;`
- L792 _public function_ `virtual FString ToString() const override`
- L795 _public member_ `bool bShowAntiAddictionMessage;`
- L796 _public member_ `FOnlineAsyncEventRailShowFloatingNotifyWindowPayload Payload;`

#### class `FOnlineAsyncEventRailInviteSent`  
`class FOnlineAsyncEventRailInviteSent : public FOnlineAsyncEventRail`  
_L800-836_
- inherits: `FOnlineAsyncEventRail`
- L806 _public prototype_ `FOnlineAsyncEventRailInviteSent() = delete;`
- L807 _public function_ `FOnlineAsyncEventRailInviteSent(FOnlineSubsystemTencent* InSubsystem, const rail::rail_event::RailUsersNotifyInviter* InParams) : FOnlineAsyncEventRail(InSubsystem) , Result(InParams ? InParams->get_result() : rail::kErrorUnknown) , InviterId(InParams ? InParams->rail_id : rail::kInvalidRailId) , InviteeId(InParams ? InParams->invitee_id : rail::kInvalidRailId) , UserData(InParams ? InParams->user_data : rail::RailString())`
- L816 _public function_ `virtual ~FOnlineAsyncEventRailInviteSent()`
- L821 _public prototype_ `virtual void Finalize() override;`
- L822 _public prototype_ `virtual void TriggerDelegates() override;`
- L823 _public function_ `virtual FString ToString() const override`
- L829 _protected member_ `rail::RailResult Result;` — Result of the invite sent event
- L831 _protected member_ `rail::RailID InviterId;` — User id who sent the invite
- L833 _protected member_ `rail::RailID InviteeId;` — User id who will receive the invite
- L835 _protected member_ `rail::RailString UserData;` — User data returned with the call

#### class `FOnlineAsyncEventRailInviteSentEx`  
`class FOnlineAsyncEventRailInviteSentEx : public FOnlineAsyncEventRail`  
_L838-871_
- inherits: `FOnlineAsyncEventRail`
- L844 _public prototype_ `FOnlineAsyncEventRailInviteSentEx() = delete;`
- L845 _public function_ `FOnlineAsyncEventRailInviteSentEx(FOnlineSubsystemTencent* InSubsystem, const rail::rail_event::RailUsersInviteUsersResult* InParams) : FOnlineAsyncEventRail(InSubsystem) , Result(InParams ? InParams->get_result() : rail::kErrorUnknown) , InviteType(InParams ? InParams->invite_type : rail::kRailUsersInviteTypeGame) , UserData(InParams ? InParams->user_data : rail::RailString())`
- L853 _public function_ `virtual ~FOnlineAsyncEventRailInviteSentEx()`
- L858 _public prototype_ `virtual void Finalize() override;`
- L859 _public prototype_ `virtual void TriggerDelegates() override;`
- L860 _public function_ `virtual FString ToString() const override`
- L866 _protected member_ `rail::RailResult Result;` — Result of the invite sent event
- L868 _protected member_ `rail::EnumRailUsersInviteType InviteType;` — Type of invite
- L870 _protected member_ `rail::RailString UserData;` — User data returned with the call

#### class `FOnlineAsyncEventRailInviteResponse`  
`class FOnlineAsyncEventRailInviteResponse : public FOnlineAsyncEventRail`  
_L873-912_
- inherits: `FOnlineAsyncEventRail`
- L879 _public prototype_ `FOnlineAsyncEventRailInviteResponse() = delete;`
- L880 _public function_ `FOnlineAsyncEventRailInviteResponse(FOnlineSubsystemTencent* InSubsystem, const rail::rail_event::RailUsersRespondInvitation* InParams) : FOnlineAsyncEventRail(InSubsystem) , Result(InParams ? InParams->get_result() : rail::kErrorUnknown) , InviterId(InParams ? InParams->inviter_id : rail::kInvalidRailId) , InviteeId(InParams ? InParams->rail_id : rail::kInvalidRailId) , UserData(InParams ? InParams->user_data : rail::RailString()) , Response(InParams ? InParams->response : rail::kRailInviteResponseTypeUnknown)`
- L890 _public function_ `virtual ~FOnlineAsyncEventRailInviteResponse()`
- L895 _public prototype_ `virtual void Finalize() override;`
- L896 _public prototype_ `virtual void TriggerDelegates() override;`
- L897 _public function_ `virtual FString ToString() const override`
- L903 _protected member_ `rail::RailResult Result;` — Result of the invite response event
- L905 _protected member_ `rail::RailID InviterId;` — User id who sent the invite
- L907 _protected member_ `rail::RailID InviteeId;` — User id who received the invite
- L909 _protected member_ `rail::RailString UserData;` — User data returned with the call
- L911 _protected member_ `rail::EnumRailUsersInviteResponseType Response;` — Invitees response to the invite

#### class `FOnlineAsyncEventRailJoinGameByUser`  
`class FOnlineAsyncEventRailJoinGameByUser : public FOnlineAsyncEventRail`  
_L914-947_
- inherits: `FOnlineAsyncEventRail`
- L920 _public prototype_ `FOnlineAsyncEventRailJoinGameByUser() = delete;`
- L921 _public function_ `FOnlineAsyncEventRailJoinGameByUser(FOnlineSubsystemTencent* InSubsystem, const rail::rail_event::RailPlatformNotifyEventJoinGameByUser* InParams) : FOnlineAsyncEventRail(InSubsystem) , Result(InParams ? InParams->get_result() : rail::kErrorUnknown) , UserToJoin(InParams ? InParams->rail_id_to_join : rail::kInvalidRailId) , CommandLine(InParams ? InParams->commandline_info : rail::RailString())`
- L929 _public function_ `virtual ~FOnlineAsyncEventRailJoinGameByUser()`
- L934 _public prototype_ `virtual void Finalize() override;`
- L935 _public prototype_ `virtual void TriggerDelegates() override;`
- L936 _public function_ `virtual FString ToString() const override`
- L942 _protected member_ `rail::RailResult Result;` — Result of the invite response event
- L944 _protected member_ `rail::RailID UserToJoin;` — Remote user to join
- L946 _protected member_ `rail::RailString CommandLine;` — Commandline invite of remote user

#### class `FOnlineAsyncEventRailJoinGameResult`  
`class FOnlineAsyncEventRailJoinGameResult : public FOnlineAsyncEventRail`  
_L949-991_
- inherits: `FOnlineAsyncEventRail`
- L955 _public prototype_ `FOnlineAsyncEventRailJoinGameResult() = delete;`
- L956 _public function_ `FOnlineAsyncEventRailJoinGameResult(FOnlineSubsystemTencent* InSubsystem, const rail::rail_event::RailUsersInviteJoinGameResult* InParams) : FOnlineAsyncEventRail(InSubsystem) , Result(InParams ? InParams->get_result() : rail::kErrorUnknown) , InviterId(InParams ? InParams->rail_id : rail::kInvalidRailId) , InviteeId(InParams ? InParams->invitee_id : rail::kInvalidRailId) , UserData(InParams ? InParams->user_data : rail::RailString()) , Response(InParams ? InParams->response_value : rail::kRailInviteResponseTypeUnknown) , InviteType(InParams ? InParams->invite_type : rail::kRailUsersInviteTypeGame)`
- L967 _public function_ `virtual ~FOnlineAsyncEventRailJoinGameResult()`
- L972 _public prototype_ `virtual void Finalize() override;`
- L973 _public prototype_ `virtual void TriggerDelegates() override;`
- L974 _public function_ `virtual FString ToString() const override`
- L980 _protected member_ `rail::RailResult Result;` — Result of the join game event
- L982 _protected member_ `rail::RailID InviterId;` — User id who sent the invite
- L984 _protected member_ `rail::RailID InviteeId;` — User id who received the invite
- L986 _protected member_ `rail::RailString UserData;` — User data returned with the call
- L988 _protected member_ `rail::EnumRailUsersInviteResponseType Response;` — Invitees response to the invite
- L990 _protected member_ `rail::EnumRailUsersInviteType InviteType;` — Type of invite sent

#### class `FOnlineAsyncEventRailFriendsListChanged`  
`class FOnlineAsyncEventRailFriendsListChanged : public FOnlineAsyncEventRail`  
_L993-1018_
- inherits: `FOnlineAsyncEventRail`
- L998 _public prototype_ `FOnlineAsyncEventRailFriendsListChanged() = delete;`
- L999 _public function_ `FOnlineAsyncEventRailFriendsListChanged(FOnlineSubsystemTencent* InSubsystem, const rail::rail_event::RailFriendsListChanged* InParams) : FOnlineAsyncEventRail(InSubsystem) , UserId(InParams->rail_id)`
- L1005 _public prototype_ `virtual ~FOnlineAsyncEventRailFriendsListChanged() = default;`
- L1008 _public prototype_ `virtual void TriggerDelegates() override;`
- L1009 _public function_ `virtual FString ToString() const override`
- L1017 _private member_ `rail::RailID UserId;` — The user id whose list has changed

#### class `FOnlineAsyncEventRailFriendsOnlineStateChanged`  
`class FOnlineAsyncEventRailFriendsOnlineStateChanged : public FOnlineAsyncEventRail`  
_L1020-1046_
- inherits: `FOnlineAsyncEventRail`
- L1025 _public prototype_ `FOnlineAsyncEventRailFriendsOnlineStateChanged() = delete;`
- L1026 _public function_ `FOnlineAsyncEventRailFriendsOnlineStateChanged(FOnlineSubsystemTencent* InSubsystem, const rail::rail_event::RailFriendsOnlineStateChanged* InParams) : FOnlineAsyncEventRail(InSubsystem) , OnlineState(InParams ? InParams->friend_online_state : rail::RailFriendOnLineState())`
- L1032 _public prototype_ `virtual ~FOnlineAsyncEventRailFriendsOnlineStateChanged() = default;`
- L1035 _public prototype_ `virtual void Finalize() override;`
- L1036 _public function_ `virtual FString ToString() const override`
- L1045 _private member_ `rail::RailFriendOnLineState OnlineState;` — Data related to the online state change

#### class `FOnlineAsyncEventRailFriendsMetadataChanged`  
`class FOnlineAsyncEventRailFriendsMetadataChanged : public FOnlineAsyncEventRail`  
_L1048-1069_
- inherits: `FOnlineAsyncEventRail`
- L1053 _public prototype_ `FOnlineAsyncEventRailFriendsMetadataChanged() = delete;`
- L1054 _public prototype_ `FOnlineAsyncEventRailFriendsMetadataChanged(FOnlineSubsystemTencent* InSubsystem, const rail::rail_event::RailFriendsMetadataChanged* InParams);`
- L1056 _public prototype_ `virtual ~FOnlineAsyncEventRailFriendsMetadataChanged() = default;`
- L1059 _public prototype_ `virtual void TriggerDelegates() override;`
- L1060 _public function_ `virtual FString ToString() const override`
- L1068 _private member_ `TUniqueNetIdMap<FMetadataPropertiesRail> ChangedMetadata;` — Data related to the metadata change

#### struct `FQueryUserPresenceTaskResult`  
`struct FQueryUserPresenceTaskResult`  
_L1074-1087_
- desc: Result structure after getting users presence
- L1076 _public function_ `FQueryUserPresenceTaskResult() : QueryCount(0) , SuccessCount(0)`
- L1082 _public member_ `FOnlineError Error;` — Error information
- L1084 _public member_ `int32 QueryCount;` — Number of completed queries
- L1086 _public member_ `int32 SuccessCount;` — Number of successful queries

#### class `FOnlineAsyncTaskRailQueryFriendsPresence`  
`class FOnlineAsyncTaskRailQueryFriendsPresence : public FOnlineAsyncTaskBasic<FOnlineSubsystemTencent>`  
_L1092-1128_
- inherits: `FOnlineAsyncTaskBasic<FOnlineSubsystemTencent>`
- desc: Query a list of friends presence to prime the presence cache
- L1099 _public prototype_ `DECLARE_DELEGATE_OneParam(FCompletionDelegate, const FQueryUserPresenceTaskResult& );` — Delegate fired when this task completed
- L1101 _public prototype_ `FOnlineAsyncTaskRailQueryFriendsPresence() = delete;`
- L1102 _public function_ `FOnlineAsyncTaskRailQueryFriendsPresence(FOnlineSubsystemTencent* InSubsystem, TArray<FUniqueNetIdRef>& InFriends, const FCompletionDelegate& InCompletionDelegate) : FOnlineAsyncTaskBasic(InSubsystem) , CompletionDelegate(InCompletionDelegate) , FriendsList(InFriends)`
- L1109 _public function_ `virtual ~FOnlineAsyncTaskRailQueryFriendsPresence()`
- L1114 _public prototype_ `virtual void Initialize() override;`
- L1115 _public prototype_ `virtual void Finalize() override;`
- L1116 _public prototype_ `virtual void TriggerDelegates() override;`
- L1117 _public function_ `virtual FString ToString() const override`
- L1123 _protected member_ `FCompletionDelegate CompletionDelegate;` — Completion delegate to fire
- L1125 _protected member_ `TArray<FUniqueNetIdRef> FriendsList;` — List of friends whose presence data is requested
- L1127 _protected member_ `FQueryUserPresenceTaskResult TaskResult;` — Result of operation

#### struct `FSendInviteTaskResult`  
`struct FSendInviteTaskResult`  
_L1133-1144_
- desc: Result structure after sending an invite
- L1135 _public prototype_ `FSendInviteTaskResult() = delete;`
- L1136 _public function_ `FSendInviteTaskResult(const FString& InInviteStr) : InviteStr(InInviteStr)`
- L1141 _public member_ `FString InviteStr;` — Invite command line
- L1143 _public member_ `FOnlineError Error;` — Error information

#### class `FOnlineAsyncTaskRailSendInvite`  
`class FOnlineAsyncTaskRailSendInvite : public FOnlineAsyncTaskRail`  
_L1157-1197_
- inherits: `FOnlineAsyncTaskRail`
- desc: Send an invite to a list of friends Contains a string with the various metadata keys to query relating to the invite
- L1163 _public prototype_ `FOnlineAsyncTaskRailSendInvite() = delete;`
- L1164 _public function_ `FOnlineAsyncTaskRailSendInvite(FOnlineSubsystemTencent* InSubsystem, const FString& InInviteStr, const TArray<FUniqueNetIdRef>& InUserIds, const FOnOnlineAsyncTaskRailSendInviteComplete& InCompletionDelegate) : FOnlineAsyncTaskRail(InSubsystem, {rail::kRailEventUsersInviteUsersResult}) , UserIds(InUserIds) , CompletionDelegate(InCompletionDelegate) , TaskResult(InInviteStr)`
- L1172 _public function_ `virtual ~FOnlineAsyncTaskRailSendInvite()`
- L1177 _public prototype_ `virtual void Initialize() override;`
- L1178 _public prototype_ `virtual void Finalize() override;`
- L1179 _public prototype_ `virtual void TriggerDelegates() override;`
- L1180 _public function_ `virtual FString ToString() const override`
- L1184 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L1189 _protected prototype_ `void OnRailEventFriendsSendInviteResult(const rail::rail_event::RailUsersInviteUsersResult* InviteResult);`
- L1192 _protected member_ `TArray<FUniqueNetIdRef> UserIds;` — List of users to send invite to
- L1194 _protected member_ `FOnOnlineAsyncTaskRailSendInviteComplete CompletionDelegate;` — Delegate to fire on completion
- L1196 _protected member_ `FSendInviteTaskResult TaskResult;` — Task Result

#### struct `FGetInviteDetailsTaskResult`  
`struct FGetInviteDetailsTaskResult`  
_L1202-1208_
- desc: Result structure after retrieving details about an invite
- L1205 _public member_ `FOnlineError Error;` — Error information
- L1207 _public member_ `FString InviteString;` — Invite Details

#### class `FOnlineAsyncTaskRailGetInviteDetails`  
`class FOnlineAsyncTaskRailGetInviteDetails : public FOnlineAsyncTaskRail`  
_L1220-1254_
- inherits: `FOnlineAsyncTaskRail`
- desc: Get the details related to an invite sent by a remote user
- L1226 _public prototype_ `FOnlineAsyncTaskRailGetInviteDetails() = delete;`
- L1227 _public prototype_ `FOnlineAsyncTaskRailGetInviteDetails(FOnlineSubsystemTencent* InSubsystem, const FUniqueNetIdRail& InUserId, const FOnOnlineAsyncTaskRailGetInviteDetailsComplete& InCompletionDelegate);`
- L1229 _public function_ `virtual ~FOnlineAsyncTaskRailGetInviteDetails()`
- L1234 _public prototype_ `virtual void Initialize() override;`
- L1235 _public prototype_ `virtual void Finalize() override;`
- L1236 _public prototype_ `virtual void TriggerDelegates() override;`
- L1237 _public function_ `virtual FString ToString() const override`
- L1241 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L1246 _protected prototype_ `void OnRailEventFriendsGetInviteDetailsResult(const rail::rail_event::RailUsersGetInviteDetailResult* InviteDetails);`
- L1249 _protected member_ `rail::RailID RailUserId;` — User to query presence for
- L1251 _protected member_ `FOnOnlineAsyncTaskRailGetInviteDetailsComplete CompletionDelegate;` — Delegate to fire on completion
- L1253 _protected member_ `FGetInviteDetailsTaskResult TaskResult;` — Task Result

#### struct `FQueryFriendPlayedGamesTaskResult`  
`struct FQueryFriendPlayedGamesTaskResult`  
_L1259-1284_
- desc: Result structure containing details about friends playing games on the platform
- L1262 _public member_ `FOnlineError Error;` — Error information
- L1264 _public member_ `FUniqueNetIdRailPtr FriendId;` — Friend queried
- L1283 _public member_ `TArray<FRailGamePlayedInfo> GameInfos;` — Array of games being played on the platform

#### struct `FQueryFriendPlayedGamesTaskResult::FRailGamePlayedInfo`  
`struct FRailGamePlayedInfo`  
_L1266-1280_
- L1269 _public member_ `bool bInServer;` — Are we in a Rail Server (not implemented)
- L1271 _public member_ `bool bInRoom;` — Are we in a Rail Room (not implemented)
- L1277 _public member_ `rail::RailGameID GameId;` — Id of the game being played
- L1279 _public member_ `rail::RailFriendPlayedGamePlayState GamePlayState;` — Game state of the user

#### class `FOnlineAsyncTaskRailQueryFriendPlayedGamesInfo`  
`class FOnlineAsyncTaskRailQueryFriendPlayedGamesInfo : public FOnlineAsyncTaskRail`  
_L1297-1329_
- inherits: `FOnlineAsyncTaskRail`
- desc: Get details about a friend playing games on the RailSDK May contain an array of games information if the user has more than one open at the same time
- L1303 _public prototype_ `FOnlineAsyncTaskRailQueryFriendPlayedGamesInfo() = delete;`
- L1304 _public prototype_ `FOnlineAsyncTaskRailQueryFriendPlayedGamesInfo(FOnlineSubsystemTencent* InSubsystem, const FUniqueNetIdRail& InUserId, const FOnOnlineAsyncTaskRailQueryFriendPlayedGamesComplete& InCompletionDelegate);`
- L1306 _public function_ `virtual ~FOnlineAsyncTaskRailQueryFriendPlayedGamesInfo()`
- L1311 _public prototype_ `virtual void Initialize() override;`
- L1312 _public prototype_ `virtual void Finalize() override;`
- L1313 _public prototype_ `virtual void TriggerDelegates() override;`
- L1314 _public function_ `virtual FString ToString() const override`
- L1318 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L1323 _protected prototype_ `void OnRailEventQueryFriendPlayedGamesResult(const rail::rail_event::RailFriendsQueryFriendPlayedGamesResult* PlayedGamesDetail);`
- L1326 _protected member_ `FOnOnlineAsyncTaskRailQueryFriendPlayedGamesComplete CompletionDelegate;` — Delegate to fire on completion
- L1328 _protected member_ `FQueryFriendPlayedGamesTaskResult TaskResult;` — Task Result

#### struct `FReportPlayedWithUsersTaskResult`  
`struct FReportPlayedWithUsersTaskResult`  
_L1334-1340_
- desc: Result structure containing details reporting players that were played with
- L1337 _public member_ `FOnlineError Error;` — Error information
- L1339 _public member_ `TArray<FReportPlayedWithUser> UsersReported;` — Users reported

#### class `FOnlineAsyncTaskRailReportPlayedWithUsers`  
`class FOnlineAsyncTaskRailReportPlayedWithUsers : public FOnlineAsyncTaskRail`  
_L1352-1384_
- inherits: `FOnlineAsyncTaskRail`
- desc: Report details about a players that have been seen over the course of a game
- L1358 _public prototype_ `FOnlineAsyncTaskRailReportPlayedWithUsers() = delete;`
- L1359 _public prototype_ `FOnlineAsyncTaskRailReportPlayedWithUsers(FOnlineSubsystemTencent* InSubsystem, const TArray<FReportPlayedWithUser>& InUsersReported, const FOnOnlineAsyncTaskRailReportPlayedWithUsersComplete& InCompletionDelegate);`
- L1361 _public function_ `virtual ~FOnlineAsyncTaskRailReportPlayedWithUsers()`
- L1366 _public prototype_ `virtual void Initialize() override;`
- L1367 _public prototype_ `virtual void Finalize() override;`
- L1368 _public prototype_ `virtual void TriggerDelegates() override;`
- L1369 _public function_ `virtual FString ToString() const override`
- L1373 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L1378 _protected prototype_ `void OnRailEventReportPlayedWithUsers(const rail::rail_event::RailFriendsReportPlayedWithUserListResult* PlayedGamesDetail);`
- L1381 _protected member_ `FOnOnlineAsyncTaskRailReportPlayedWithUsersComplete CompletionDelegate;` — Delegate to fire on completion
- L1383 _protected member_ `FReportPlayedWithUsersTaskResult TaskResult;` — Task Result

#### struct `FQueryPlayedWithFriendsListTaskResult`  
`struct FQueryPlayedWithFriendsListTaskResult`  
_L1389-1395_
- desc: Result structure containing details of users last played with (not just friends)
- L1392 _public member_ `FOnlineError Error;` — Error information
- L1394 _public member_ `TArray<FUniqueNetIdRef> UsersPlayedWith;` — Users reported

#### class `FOnlineAsyncTaskRailQueryPlayedWithFriendsList`  
`class FOnlineAsyncTaskRailQueryPlayedWithFriendsList : public FOnlineAsyncTaskRail`  
_L1407-1439_
- inherits: `FOnlineAsyncTaskRail`
- desc: Report details about users the local user has played with
- L1413 _public prototype_ `FOnlineAsyncTaskRailQueryPlayedWithFriendsList() = delete;`
- L1414 _public prototype_ `FOnlineAsyncTaskRailQueryPlayedWithFriendsList(FOnlineSubsystemTencent* InSubsystem, const FOnOnlineAsyncTaskRailQueryPlayedWithFriendsListComplete& InCompletionDelegate);`
- L1416 _public function_ `virtual ~FOnlineAsyncTaskRailQueryPlayedWithFriendsList()`
- L1421 _public prototype_ `virtual void Initialize() override;`
- L1422 _public prototype_ `virtual void Finalize() override;`
- L1423 _public prototype_ `virtual void TriggerDelegates() override;`
- L1424 _public function_ `virtual FString ToString() const override`
- L1428 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L1433 _protected prototype_ `void OnRailEventPlayedWithFriendsList(const rail::rail_event::RailFriendsQueryPlayedWithFriendsListResult* PlayedFriendsList);`
- L1436 _protected member_ `FOnOnlineAsyncTaskRailQueryPlayedWithFriendsListComplete CompletionDelegate;` — Delegate to fire on completion
- L1438 _protected member_ `FQueryPlayedWithFriendsListTaskResult TaskResult;` — Task Result

#### struct `FQueryPlayedWithFriendsTimeTaskResult`  
`struct FQueryPlayedWithFriendsTimeTaskResult`  
_L1444-1465_
- desc: Result structure containing details of the time a user was last seen
- L1447 _public member_ `FOnlineError Error;` — Error information
- L1449 _public member_ `TArray<FUniqueNetIdRef> UserIds;` — List of users to query
- L1464 _public member_ `TArray<FRecentPlayers> LastPlayedWithUsers;` — All users reported as being seen by this user

#### struct `FQueryPlayedWithFriendsTimeTaskResult::FRecentPlayers`  
`struct FRecentPlayers`  
_L1451-1462_
- desc: Last seen info for a single player
- L1453 _public prototype_ `FRecentPlayers() = delete;`
- L1454 _public function_ `FRecentPlayers(const FUniqueNetIdRef InUserId, const FDateTime& InLastPlayed) : UserId(InUserId) , LastPlayed(InLastPlayed)`
- L1460 _public member_ `FUniqueNetIdRef UserId;`
- L1461 _public member_ `FDateTime LastPlayed;`

#### class `FOnlineAsyncTaskRailQueryPlayedWithFriendsTime`  
`class FOnlineAsyncTaskRailQueryPlayedWithFriendsTime : public FOnlineAsyncTaskRail`  
_L1477-1509_
- inherits: `FOnlineAsyncTaskRail`
- desc: Report details about users the local user has played with
- L1483 _public prototype_ `FOnlineAsyncTaskRailQueryPlayedWithFriendsTime() = delete;`
- L1484 _public prototype_ `FOnlineAsyncTaskRailQueryPlayedWithFriendsTime(FOnlineSubsystemTencent* InSubsystem, const TArray<FUniqueNetIdRef>& InUserIds, const FOnOnlineAsyncTaskRailQueryPlayedWithFriendsTimeComplete& InCompletionDelegate);`
- L1486 _public function_ `virtual ~FOnlineAsyncTaskRailQueryPlayedWithFriendsTime()`
- L1491 _public prototype_ `virtual void Initialize() override;`
- L1492 _public prototype_ `virtual void Finalize() override;`
- L1493 _public prototype_ `virtual void TriggerDelegates() override;`
- L1494 _public function_ `virtual FString ToString() const override`
- L1498 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) override;`
- L1503 _protected prototype_ `void OnRailEventPlayedWithFriendsTime(const rail::rail_event::RailFriendsQueryPlayedWithFriendsTimeResult* PlayedTimeResult);`
- L1506 _protected member_ `FOnOnlineAsyncTaskRailQueryPlayedWithFriendsTimeComplete CompletionDelegate;` — Delegate to fire on completion
- L1508 _protected member_ `FQueryPlayedWithFriendsTimeTaskResult TaskResult;` — Task Result

#### struct `FRequestAllAssetsTaskResult`  
`struct FRequestAllAssetsTaskResult`  
_L1514-1520_
- desc: Result structure for requesting all receipts
- L1517 _public member_ `FOnlineError Error;` — Error information
- L1519 _public member_ `FPurchaseReceipt PurchaseReceipt;` — Purchase receipts

#### class `FOnlineAsyncTaskRailRequestAllAssets`  
`class FOnlineAsyncTaskRailRequestAllAssets : public FOnlineAsyncTaskRail`  
_L1529-1564_
- inherits: `FOnlineAsyncTaskRail`
- L1533 _public prototype_ `FOnlineAsyncTaskRailRequestAllAssets() = delete;`
- L1534 _public function_ `FOnlineAsyncTaskRailRequestAllAssets(FOnlineSubsystemTencent* InSubsystem, const FUniqueNetIdRef& InUserId, const FOnOnlineAsyncTaskRailRequestAllAssetsComplete& InCompletionDelegate) : FOnlineAsyncTaskRail(InSubsystem, {rail::kRailEventAssetsRequestAllAssetsFinished}) , UserId(InUserId) , CompletionDelegate(InCompletionDelegate)`
- L1541 _public function_ `virtual ~FOnlineAsyncTaskRailRequestAllAssets()`
- L1546 _public prototype_ `virtual void Initialize() override;`
- L1547 _public prototype_ `virtual void TriggerDelegates() override;`
- L1548 _public function_ `virtual FString ToString() const override`
- L1552 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID EventId, rail::EventBase* Param) override;`
- L1556 _protected prototype_ `void OnRailRequestAllAssetsFinished(const rail::rail_event::RequestAllAssetsFinished* AssetsResponse);`
- L1559 _protected member_ `const FUniqueNetIdRef UserId;` — User we are requesting assets for
- L1561 _protected member_ `FOnOnlineAsyncTaskRailRequestAllAssetsComplete CompletionDelegate;` — Delegate to fire on completion
- L1563 _protected member_ `FRequestAllAssetsTaskResult TaskResult;` — Task Result

#### class `FOnlineAsyncEventRailAssetsChanged`  
`class FOnlineAsyncEventRailAssetsChanged : public FOnlineAsyncEventRail`  
_L1566-1585_
- inherits: `FOnlineAsyncEventRail`
- L1571 _public prototype_ `FOnlineAsyncEventRailAssetsChanged() = delete;`
- L1572 _public prototype_ `FOnlineAsyncEventRailAssetsChanged(FOnlineSubsystemTencent* InSubsystem, const rail::rail_event::RailAssetsChanged* InParams);`
- L1574 _public prototype_ `virtual ~FOnlineAsyncEventRailAssetsChanged() = default;`
- L1577 _public prototype_ `virtual void TriggerDelegates() override;`
- L1578 _public function_ `virtual FString ToString() const override`

#### struct `FRequestAllPurchasableProductsTaskResult`  
`struct FRequestAllPurchasableProductsTaskResult`  
_L1590-1596_
- desc: Result structure for requesting all purchasable products
- L1593 _public member_ `FOnlineError Error;` — Error information
- L1595 _public member_ `TArray<FOnlineStoreOfferRef> Offers;` — Purchasable products

#### class `FOnlineAsyncTaskRailRequestAllPurchasableProducts`  
`class FOnlineAsyncTaskRailRequestAllPurchasableProducts : public FOnlineAsyncTaskRail`  
_L1605-1640_
- inherits: `FOnlineAsyncTaskRail`
- L1611 _public prototype_ `FOnlineAsyncTaskRailRequestAllPurchasableProducts() = delete;`
- L1612 _public function_ `FOnlineAsyncTaskRailRequestAllPurchasableProducts(FOnlineSubsystemTencent* InSubsystem, const FOnOnlineAsyncTaskRailRequestAllPurchasableProductsComplete& InCompletionDelegate) : FOnlineAsyncTaskRail(InSubsystem, {rail::kRailEventInGamePurchaseAllPurchasableProductsInfoReceived}) , CompletionDelegate(InCompletionDelegate)`
- L1618 _public function_ `virtual ~FOnlineAsyncTaskRailRequestAllPurchasableProducts()`
- L1623 _public prototype_ `virtual void Initialize() override;`
- L1624 _public prototype_ `virtual void TriggerDelegates() override;`
- L1625 _public function_ `virtual FString ToString() const override`
- L1629 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID EventId, rail::EventBase* Param) override;`
- L1634 _protected prototype_ `void OnRailRequestAllPurchasableProductsResponse(rail::rail_event::RailInGamePurchaseRequestAllPurchasableProductsResponse* Response);`
- L1637 _protected member_ `FRequestAllPurchasableProductsTaskResult TaskResult;` — Result of the task
- L1639 _protected member_ `FOnOnlineAsyncTaskRailRequestAllPurchasableProductsComplete CompletionDelegate;` — Delegate to fire on completion

#### struct `FPurchaseProductsTaskResult`  
`struct FPurchaseProductsTaskResult`  
_L1645-1651_
- desc: Result structure for purchasing products
- L1648 _public member_ `FOnlineError Error;` — Error information
- L1650 _public member_ `TSharedPtr<FPurchaseReceipt> PurchaseReceipt;` — Purchase receipt, if successful

#### class `FOnlineAsyncTaskRailPurchaseProducts`  
`class FOnlineAsyncTaskRailPurchaseProducts : public FOnlineAsyncTaskRail`  
_L1660-1704_
- inherits: `FOnlineAsyncTaskRail`
- L1666 _public prototype_ `FOnlineAsyncTaskRailPurchaseProducts() = delete;`
- L1667 _public function_ `FOnlineAsyncTaskRailPurchaseProducts(FOnlineSubsystemTencent* InSubsystem, const FUniqueNetIdRef& InUserId, const FPurchaseCheckoutRequest& InCheckoutRequest, const FOnOnlineAsyncTaskRailPurchaseProductsComplete& InCompletionDelegate) : FOnlineAsyncTaskRail(InSubsystem, {rail::kRailEventInGamePurchasePurchaseProductsToAssetsResult}) , UserId(InUserId) , CheckoutRequest(InCheckoutRequest) , CompletionDelegate(InCompletionDelegate)`
- L1677 _public function_ `virtual ~FOnlineAsyncTaskRailPurchaseProducts()`
- L1682 _public prototype_ `virtual void Initialize() override;`
- L1683 _public prototype_ `virtual void TriggerDelegates() override;`
- L1684 _public function_ `virtual FString ToString() const override`
- L1688 _public prototype_ `virtual void OnRailEvent(rail::RAIL_EVENT_ID EventId, rail::EventBase* Param) override;`
- L1693 _protected prototype_ `void OnRailPurchaseProductsToAssetsResult(rail::rail_event::RailInGamePurchasePurchaseProductsToAssetsResponse* Response);`
- L1694 _protected prototype_ `void HandlePurchaseProductsResult(const TOptional<rail::RailResult> RailResult);`
- L1697 _protected member_ `const FUniqueNetIdRef UserId;` — User performing the purchase
- L1699 _protected member_ `FPurchaseCheckoutRequest CheckoutRequest;` — Items to purchase
- L1701 _protected member_ `FPurchaseProductsTaskResult TaskResult;` — Result of the task
- L1703 _protected member_ `FOnOnlineAsyncTaskRailPurchaseProductsComplete CompletionDelegate;` — Delegate to fire on completion

#### Free symbols / members of external scopes

- L20 _typedef_ `typedef TSharedRef<class FOnlineStoreOffer> FOnlineStoreOfferRef;`
- L24 _macro_ `#define ASYNC_RAIL_TASK_TIMEOUT 20.0`
- L26 _macro_ `#define ASYNC_RAIL_TASK_TIMEOUT 80.0`
- L115 _delegate_ `DECLARE_DELEGATE_TwoParams(FCompletionDelegate, const FOnlineError& , const FString& );`
- L223 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailSetUserMetadataComplete, const FSetUserMetadataTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailSetUserMetadata completes @param Result the result of the call
- L223 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailSetUserMetadataComplete, const FSetUserMetadataTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailSetUserMetadata completes @param Result the result of the call
- L328 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailSetInviteCommandlineComplete, const FSetUserMetadataTaskResult& );`
- L328 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailSetInviteCommandlineComplete, const FSetUserMetadataTaskResult& );`
- L389 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailGetUserMetadataComplete, const FGetUserMetadataTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailGetUserMetadata completes @param Result the result of the call
- L389 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailGetUserMetadataComplete, const FGetUserMetadataTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailGetUserMetadata completes @param Result the result of the call
- L471 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailGetInviteCommandLineComplete, const FGetInviteCommandLineTaskResult& );`
- L471 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailGetInviteCommandLineComplete, const FGetInviteCommandLineTaskResult& );`
- L521 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailGetUserInviteComplete, const FGetUserInviteTaskResult& );`
- L521 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailGetUserInviteComplete, const FGetUserInviteTaskResult& );`
- L612 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailAddFriendComplete, const FOnlineError& );` — Delegate fired when FOnlineAsyncTaskRailAddFriend completes @param Result the result of the call
- L612 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailAddFriendComplete, const FOnlineError& );` — Delegate fired when FOnlineAsyncTaskRailAddFriend completes @param Result the result of the call
- L668 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailGetUsersInfoComplete, const FGetUsersInfoTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailGetUsersInfo completes @param Result the result of the call
- L668 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailGetUsersInfoComplete, const FGetUsersInfoTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailGetUsersInfo completes @param Result the result of the call
- L1099 _delegate_ `DECLARE_DELEGATE_OneParam(FCompletionDelegate, const FQueryUserPresenceTaskResult& );` — Delegate fired when this task completed
- L1151 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailSendInviteComplete, const FSendInviteTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailSendInvite completes @param Result the result of the call
- L1151 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailSendInviteComplete, const FSendInviteTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailSendInvite completes @param Result the result of the call
- L1215 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailGetInviteDetailsComplete, const FGetInviteDetailsTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailGetInviteDetails completes @param Result the result of the call
- L1215 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailGetInviteDetailsComplete, const FGetInviteDetailsTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailGetInviteDetails completes @param Result the result of the call
- L1291 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailQueryFriendPlayedGamesComplete, const FQueryFriendPlayedGamesTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailQueryFriendPlayedGamesInfo completes @param Result the result of the call
- L1291 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailQueryFriendPlayedGamesComplete, const FQueryFriendPlayedGamesTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailQueryFriendPlayedGamesInfo completes @param Result the result of the call
- L1347 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailReportPlayedWithUsersComplete, const FReportPlayedWithUsersTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailReportPlayedWithUsers completes @param Result the result of the call
- L1347 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailReportPlayedWithUsersComplete, const FReportPlayedWithUsersTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailReportPlayedWithUsers completes @param Result the result of the call
- L1402 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailQueryPlayedWithFriendsListComplete, const FQueryPlayedWithFriendsListTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailQueryPlayedWithFriendsList completes @param Result the result of the call
- L1402 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailQueryPlayedWithFriendsListComplete, const FQueryPlayedWithFriendsListTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailQueryPlayedWithFriendsList completes @param Result the result of the call
- L1472 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailQueryPlayedWithFriendsTimeComplete, const FQueryPlayedWithFriendsTimeTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailQueryPlayedWithFriendsList completes @param Result the result of the call
- L1472 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailQueryPlayedWithFriendsTimeComplete, const FQueryPlayedWithFriendsTimeTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailQueryPlayedWithFriendsList completes @param Result the result of the call
- L1527 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailRequestAllAssetsComplete, const FRequestAllAssetsTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailQueryFriendPlayedGamesInfo completes @param Result the result of the call
- L1527 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailRequestAllAssetsComplete, const FRequestAllAssetsTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailQueryFriendPlayedGamesInfo completes @param Result the result of the call
- L1603 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailRequestAllPurchasableProductsComplete, const FRequestAllPurchasableProductsTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailRequestAllPurchasableProducts completes @param Result the result of the call
- L1603 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailRequestAllPurchasableProductsComplete, const FRequestAllPurchasableProductsTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailRequestAllPurchasableProducts completes @param Result the result of the call
- L1658 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailPurchaseProductsComplete, const FPurchaseProductsTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailPurchaseProducts completes @param Result the result of the call
- L1658 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOnlineAsyncTaskRailPurchaseProductsComplete, const FPurchaseProductsTaskResult& );` — Delegate fired when FOnlineAsyncTaskRailPurchaseProducts completes @param Result the result of the call

### `Plugins/Online/OnlineSubsystemTencent/Source/Private/OnlineFriendsTencent.h` (Private)


#### class `FOnlineFriendTencent`  
`class FOnlineFriendTencent : public FOnlineFriend`  
_L22-75_
- inherits: `FOnlineFriend`
- desc: Info associated with an online friend on the Tencent / Rail service
- L28 _public prototype_ `virtual FUniqueNetIdRef GetUserId() const override;`
- L29 _public prototype_ `virtual FString GetRealName() const override;`
- L30 _public prototype_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override;`
- L31 _public prototype_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L35 _public prototype_ `virtual EInviteStatus::Type GetInviteStatus() const override;`
- L36 _public prototype_ `virtual const FOnlineUserPresence& GetPresence() const override;`
- L41 _public prototype_ `FOnlineFriendTencent(FOnlineSubsystemTencent* InTencentSubsystem, const FUniqueNetIdRailRef InUserId);` — Init constructor
- L46 _public function_ `virtual ~FOnlineFriendTencent()` — Destructor
- L58 _public function_ `inline bool GetAccountData(const FString& Key, FString& OutVal) const` — Get account data attribute @param Key account data entry key @param OutVal [out] value that was found @return true if entry was found
- L70 _public member_ `FOnlineSubsystemTencent* TencentSubsystem;` — Used to access presence data for the friend entry
- L72 _public member_ `FUniqueNetIdRailRef UserId;` — User Id represented as a FUniqueNetId
- L74 _public member_ `TMap<FString, FString> AccountData;` — Any addition account data associated with the friend

#### class `FOnlineFriendsListTencent`  
`class FOnlineFriendsListTencent`  
_L80-96_
- desc: Named list of friends
- L87 _public function_ `FOnlineFriendsListTencent(const FString& InListName = TEXT("")) : ListName(InListName)` — Init/default constructor
- L93 _public member_ `FString ListName;` — Can have multiple friends lists. Each with its own name
- L95 _public member_ `TArray<TSharedRef<FOnlineFriendTencent> > Friends;` — Array of friends populated by ReadFriendsList

#### class `FOnlineRecentPlayerTencent`  
`class FOnlineRecentPlayerTencent : public FOnlineRecentPlayer`  
_L103-169_
- inherits: `FOnlineRecentPlayer`
- desc: Info associated with a recent player on the Tencent service
- L110 _public prototype_ `virtual FUniqueNetIdRef GetUserId() const override;`
- L111 _public prototype_ `virtual FString GetRealName() const override;`
- L112 _public prototype_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override;`
- L113 _public prototype_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L117 _public prototype_ `virtual FDateTime GetLastSeen() const override;`
- L122 _public function_ `FOnlineRecentPlayerTencent(const FUniqueNetId& InUserId) : UserId(InUserId.AsShared())` — Init/default constructor
- L127 _public function_ `FOnlineRecentPlayerTencent(const FUniqueNetIdRef& InUserId) : UserId(InUserId)`
- L132 _public function_ `FOnlineRecentPlayerTencent(const FString& InUserId = TEXT("")) : UserId(FUniqueNetIdRail::Create(InUserId))`
- L140 _public function_ `virtual ~FOnlineRecentPlayerTencent()` — Destructor
- L152 _public function_ `inline bool GetAccountData(const FString& Key, FString& OutVal) const` — Get account data attribute @param Key account data entry key @param OutVal [out] value that was found @return true if entry was found
- L164 _public member_ `FUniqueNetIdRef UserId;` — User Id represented as a FUniqueNetId
- L166 _public member_ `FDateTime LastSeen;` — last seen in online game
- L168 _public member_ `TMap<FString, FString> AccountData;` — Any addition account data associated with the recent player

#### class `FOnlineFriendsTencent`  
`class FOnlineFriendsTencent : public IOnlineFriends, public TSharedFromThis<FOnlineFriendsTencent, ESPMode::ThreadSafe>`  
_L177-305_
- inherits: `IOnlineFriends,TSharedFromThis<FOnlineFriendsTencent,ESPMode::ThreadSafe>`
- desc: Tencent / Rail implementation of the online friends interface
- L184 _public prototype_ `virtual bool ReadFriendsList(int32 LocalUserNum, const FString& ListName, const FOnReadFriendsListComplete& Delegate = FOnReadFriendsListComplete()) override;`
- L185 _public prototype_ `virtual bool DeleteFriendsList(int32 LocalUserNum, const FString& ListName, const FOnDeleteFriendsListComplete& Delegate = FOnDeleteFriendsListComplete()) override;`
- L186 _public prototype_ `virtual bool SendInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnSendInviteComplete& Delegate = FOnSendInviteComplete()) override;`
- L187 _public prototype_ `virtual bool AcceptInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnAcceptInviteComplete& Delegate = FOnAcceptInviteComplete()) override;`
- L188 _public prototype_ `virtual bool RejectInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L189 _public prototype_ `virtual void SetFriendAlias(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FString& Alias, const FOnSetFriendAliasComplete& Delegate = FOnSetFriendAliasComplete()) override;`
- L190 _public prototype_ `virtual void DeleteFriendAlias(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnDeleteFriendAliasComplete& Delegate = FOnDeleteFriendAliasComplete()) override;`
- L191 _public prototype_ `virtual bool DeleteFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L192 _public prototype_ `virtual bool GetFriendsList(int32 LocalUserNum, const FString& ListName, TArray< TSharedRef<FOnlineFriend> >& OutFriends) override;`
- L193 _public prototype_ `virtual TSharedPtr<FOnlineFriend> GetFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L194 _public prototype_ `virtual bool IsFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L195 _public prototype_ `virtual void AddRecentPlayers(const FUniqueNetId& UserId, const TArray<FReportPlayedWithUser>& InRecentPlayers, const FString& ListName, const FOnAddRecentPlayersComplete& InCompletionDelegate);`
- L196 _public prototype_ `virtual bool QueryRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace) override;`
- L197 _public prototype_ `virtual bool GetRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace, TArray< TSharedRef<FOnlineRecentPlayer> >& OutRecentPlayers) override;`
- L198 _public prototype_ `virtual void DumpRecentPlayers() const override;`
- L199 _public prototype_ `virtual bool BlockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId) override;`
- L200 _public prototype_ `virtual bool UnblockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId) override;`
- L201 _public prototype_ `virtual bool QueryBlockedPlayers(const FUniqueNetId& UserId) override;`
- L202 _public prototype_ `virtual bool GetBlockedPlayers(const FUniqueNetId& UserId, TArray< TSharedRef<FOnlineBlockedPlayer> >& OutBlockedPlayers) override;`
- L203 _public prototype_ `virtual void DumpBlockedPlayers() const override;`
- L213 _public prototype_ `FOnlineFriendsTencent(FOnlineSubsystemTencent* InSubsystem);` — Constructor @param InSubsystem subsystem being used
- L218 _public prototype_ `virtual ~FOnlineFriendsTencent();` — Destructor
- L225 _public prototype_ `bool Init();` — Initialize the interface @return true if successful, false otherwise
- L235 _public prototype_ `bool IsPlayerBlocked(const FUniqueNetId& LocalUserId, const FUniqueNetId& PeerUserId) const;` — Check to see if a single player is blocked.  Used as an alternative to GetBlockedPlayers which involves array copying @param LocalUserId User whose block list we will be checking against @param PeerUserId User who we want to check if they are blocked @return true if the peer user is blocked, false if not
- L240 _public prototype_ `void OnRailFriendsListChanged(const FUniqueNetIdRail& UserId);` — Called when Rail informs us the friends list has changed
- L253 _private prototype_ `void OnQueryUsersForFriendsListComplete(int32 LocalUserNum, bool bWasSuccessful, const TArray<FUniqueNetIdRef>& UserIds, const FString& ErrorStr, FString ListName, TArray<FUniqueNetIdRef> ExpectedFriendIds);` — Delegate fired when query user info is complete for a list of Tencent friends @param LocalUserNum the controller number of the associated user that made the request @param bWasSuccessful true if the async action completed without error, false if there was an error @param UserIds list of user ids that were queried @param ErrorStr string representing the error condition @param ListName name of the friends list to use
- L262 _private prototype_ `void OnQueryFriendsPresenceComplete(const FQueryUserPresenceTaskResult& TaskResult, int32 LocalUserNum, FString ListName);` — Delegate fired when query presence is complete for a list of Tencent friends @param TaskResult result of the async action @param LocalUserNum the controller number of the associated user that made the request @param ListName name of the friends list to use
- L269 _private prototype_ `void OnLoginChanged(int32 LocalUserNum);` — Notification that login status has changed for a user @param LocalUserNum id of local user whose login status has changed
- L280 _private prototype_ `TSharedPtr<FOnlineFriendTencent> FindFriendEntry(int32 LocalUserNum, const FUniqueNetIdRail& FriendId, bool bAddIfMissing);` — Find an existing friend entry that is cached @param LocalUserNum user with friends list to operate on @param FriendId id of friend to find @param bAddIfMissing add new entry to cache if true @return friend entry pointer if found or NULL if not found
- L283 _private prototype_ `void SendInvite_Complete(const FOnlineError& Result, const int32 LocalUserNum, const FUniqueNetIdRef FriendId, const FString ListName, const FOnSendInviteComplete CompletionDelegate);` — Called when the SendInvite async task has completed
- L288 _private prototype_ `FOnlineFriendsTencent() = delete;` — Should use the initialization constructor instead
- L290 _private member_ `FOnlineSubsystemTencent* TencentSubsystem;`
- L293 _private member_ `FOnlineFriendsListTencentMap FriendsLists;` — Cache of all friends lists for all local users
- L296 _private member_ `FDelegateHandle OnLoginChangedHandle;` — Handle to login change events for clearing friends lists
- L298 _private member_ `FDelegateHandle OnQueryUsersForFriendsListCompleteDelegate;` — Handle when a query user info call for reading friends list is complete
- L301 _private member_ `FOnlineRecentPlayersTencentMap RecentPlayersLists;` — Cache of all recent players lists for all local users
- L304 _private member_ `TArray<FOnReadFriendsListComplete> OnReadFriendsListCompleteDelegates;` — Array of delegates for ReadFriendList requests. All will be completed at the same time if there were calls to ReadFriendsList while it was in progress

#### Free symbols / members of external scopes

- L98 _typedef_ `typedef TRailIdMap<FOnlineFriendsListTencent> FOnlineFriendsListTencentMap;` — Mapping from user id to array of friends lists
- L172 _typedef_ `typedef TUniqueNetIdMap<TArray<TSharedRef<FOnlineRecentPlayerTencent>>> FOnlineRecentPlayersTencentMap;` — Mapping from user id to list of recent players
- L307 _typedef_ `typedef TSharedPtr<FOnlineFriendsTencent, ESPMode::ThreadSafe> FOnlineFriendsTencentPtr;`

### `Plugins/Online/OnlineSubsystemTencent/Source/Private/OnlineMessageSanitizerTencent.h` (Private)


#### struct `ISanitizeMessage`  
`struct ISanitizeMessage`  
_L13-19_
- desc: Interface for Message sanitization data
- L15 _public function_ `virtual ~ISanitizeMessage()`
- L17 _public prototype_ `virtual void Filter() = 0;`
- L18 _public prototype_ `virtual void TriggerDelegate(bool bSuccess) = 0;`

#### struct `FSanitizeMessage`  
`struct FSanitizeMessage : public ISanitizeMessage`  
_L22-37_
- inherits: `ISanitizeMessage`
- desc: Sanitization data holding a single string to filter
- L24 _public function_ `FSanitizeMessage(const FString& InRawMessage, FOnMessageProcessed InProcessCompleteDelegate) : CompletionDelegate(InProcessCompleteDelegate) , RawMessage(InRawMessage)`
- L30 _public function_ `virtual ~FSanitizeMessage()`
- L32 _public prototype_ `virtual void Filter() override;`
- L33 _public prototype_ `virtual void TriggerDelegate(bool bSuccess) override;`
- L35 _public member_ `FOnMessageProcessed CompletionDelegate;`
- L36 _public member_ `FString RawMessage;`

#### struct `FSanitizeMessageArray`  
`struct FSanitizeMessageArray : public ISanitizeMessage`  
_L40-55_
- inherits: `ISanitizeMessage`
- desc: Sanitization data holding an array of strings to filter
- L42 _public function_ `FSanitizeMessageArray(TArray<FString>&& InRawMessageArray, FOnMessageArrayProcessed InProcessCompleteDelegate) : CompletionDelegate(InProcessCompleteDelegate) , RawMessageArray(InRawMessageArray)`
- L48 _public function_ `virtual ~FSanitizeMessageArray()`
- L50 _public prototype_ `virtual void Filter() override;`
- L51 _public prototype_ `virtual void TriggerDelegate(bool bSuccess) override;`
- L53 _public member_ `FOnMessageArrayProcessed CompletionDelegate;`
- L54 _public member_ `TArray<FString> RawMessageArray;`

#### struct `FMultiPartMessage`  
`struct FMultiPartMessage`  
_L58-63_
- desc: Structure used to tie the filtered words back to the original request
- L60 _public member_ `TArray<FString> AlreadyProcessedMessages;`
- L61 _public member_ `TArray<int32> AlreadyProcessedIndex;`
- L62 _public member_ `TArray<FString> MessagesToSanitize;`

#### struct `FSanitizerTaskData`  
`struct FSanitizerTaskData`  
_L65-74_
- L67 _public function_ `FSanitizerTaskData(TSharedRef<ISanitizeMessage, ESPMode::ThreadSafe> InMessage) : Message(InMessage) , bSuccess(false)`
- L72 _public member_ `TSharedRef<ISanitizeMessage, ESPMode::ThreadSafe> Message;`
- L73 _public member_ `bool bSuccess;`

#### class `FMessageSanitizerTask`  
`class FMessageSanitizerTask : public FNonAbandonableTask`  
_L77-99_
- inherits: `FNonAbandonableTask`
- desc: worker task
- L82 _public function_ `FMessageSanitizerTask(FOnlineSubsystemTencent * InTencentSubsystem, const FSanitizerTaskData & InData) : TencentSubsystem(InTencentSubsystem), Data(InData)` — Constructor
- L88 _public prototype_ `void DoWork();` — Performs work on thread
- L91 _public function_ `FORCEINLINE TStatId GetStatId() const` — Returns the stat id for this task
- L97 _private member_ `FOnlineSubsystemTencent* TencentSubsystem;`
- L98 _private member_ `FSanitizerTaskData Data;`

#### class `FAsyncEventSanitizerTaskCompleted`  
`class FAsyncEventSanitizerTaskCompleted : public FOnlineAsyncEvent<FOnlineSubsystemTencent>`  
_L103-127_
- inherits: `FOnlineAsyncEvent<FOnlineSubsystemTencent>`
- L106 _private member_ `FSanitizerTaskData Data;`
- L115 _public function_ `FAsyncEventSanitizerTaskCompleted(FOnlineSubsystemTencent* InTencentSubsystem, const FSanitizerTaskData & InData) : FOnlineAsyncEvent(InTencentSubsystem), Data(InData)` — Constructor. @param InTencentSubsystem The owner of the external UI interface that triggered this event. @param InData All the data relating to the task
- L121 _public function_ `virtual FString ToString() const override`
- L126 _public prototype_ `virtual void TriggerDelegates() override;`

#### class `FMessageSanitizerTencent`  
`class FMessageSanitizerTencent : public IMessageSanitizer`  
_L133-180_
- inherits: `IMessageSanitizer`
- desc: Implements the Tencent specific interface chat message sanitization
- L140 _public prototype_ `virtual void SanitizeDisplayName(const FString& DisplayName, const FOnMessageProcessed& CompletionDelegate) override;` — IMessageSanitizer
- L141 _public prototype_ `virtual void SanitizeDisplayNames(const TArray<FString>& DisplayNames, const FOnMessageArrayProcessed& CompletionDelegate) override;`
- L142 _public prototype_ `virtual void QueryBlockedUser(int32 LocalUserNum, const FString& FromUserId, const FString& FromPlatform, const FOnQueryUserBlockedResponse& CompletionDelegate) override;`
- L143 _public function_ `virtual void ResetBlockedUserCache() override`
- L146 _public function_ `explicit FMessageSanitizerTencent(FOnlineSubsystemTencent* InTencentSubsystem) : TencentSubsystem(InTencentSubsystem)`
- L154 _public prototype_ `virtual ~FMessageSanitizerTencent();`
- L157 _private prototype_ `bool HandleTicker(float DeltaTime);`
- L158 _private prototype_ `void CleanTaskList();`
- L159 _private prototype_ `void HandleMessageSanitized(bool bSuccess, const FString& SanitizedMessage, FOnMessageProcessed CompletionDelegate, FString UnsanitizedMessage);`
- L160 _private prototype_ `void HandleMessageArraySanitized(bool bSuccess, const TArray<FString>& SanitizedMessages, FOnMessageArrayProcessed CompletionDelegate, TSharedRef<FMultiPartMessage> MultiPartMessage);`
- L167 _private member_ `TArray<TSharedRef<ISanitizeMessage, ESPMode::ThreadSafe>> ProcessList;` — Holds the list of messages being processed
- L170 _private member_ `TArray<TSharedPtr<MessageSanitizerTask>> CurrentTasks;` — List of current tasks
- L173 _private member_ `TMap<FString, FString> WordMap;` — Holds a map of sanitized words
- L176 _private member_ `FTSTicker::FDelegateHandle TickDelegateHandle;` — Handle to the registered TickDelegate.
- L179 _private member_ `FOnlineSubsystemTencent* TencentSubsystem;` — Reference to the main Tencent subsystem

#### Free symbols / members of external scopes

- L101 _typedef_ `typedef FAsyncTask<FMessageSanitizerTask> MessageSanitizerTask;`
- L182 _typedef_ `typedef TSharedPtr<FMessageSanitizerTencent, ESPMode::ThreadSafe> FMessageSanitizerTencentPtr;`

### `Plugins/Online/OnlineSubsystemTencent/Source/Private/OnlinePlayTimeLimitTencent.h` (Private)


#### class `FOnlinePlayTimeLimitUserTencentRail`  
`class FOnlinePlayTimeLimitUserTencentRail : public FPlayTimeLimitUser`  
_L13-36_
- inherits: `FPlayTimeLimitUser`
- L17 _public function_ `explicit FOnlinePlayTimeLimitUserTencentRail(const FUniqueNetIdRef& InUserId) : FPlayTimeLimitUser(InUserId)`
- L20 _public prototype_ `~FOnlinePlayTimeLimitUserTencentRail();`
- L23 _public prototype_ `virtual bool HasTimeLimit() const override;`
- L24 _public prototype_ `virtual int32 GetPlayTimeMinutes() const override;`
- L25 _public prototype_ `virtual float GetRewardRate() const override;`
- L26 _public prototype_ `virtual void Init() override;`
- L30 _public function_ `virtual void SetNextNotificationTime(const TOptional<double>& InNextNotificationTime) override` — Tencent display times are controlled by Rail SDK events. just clear the existing time if an attempt is made.
- L33 _public prototype_ `void HandleAASDialog(const FString& DialogTitle, const FString& DialogText, const FString& ButtonText);`
- L35 _public member_ `FDelegateHandle AASDelegateHandle;`

### `Plugins/Online/OnlineSubsystemTencent/Source/Private/OnlinePurchaseTencent.h` (Private)


#### class `FOnlinePurchaseTencent`  
`class FOnlinePurchaseTencent : public IOnlinePurchase , public TSharedFromThis<FOnlinePurchaseTencent, ESPMode::ThreadSafe>`  
_L17-68_
- inherits: `IOnlinePurchase,TSharedFromThis<FOnlinePurchaseTencent,ESPMode::ThreadSafe>`
- desc: Implementation of IOnlinePurchase using the Rail SDK
- L23 _public prototype_ `virtual ~FOnlinePurchaseTencent() = default;` — Destructor
- L26 _public prototype_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId) override;`
- L27 _public prototype_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId, FOnlineError& Error) override;`
- L28 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseCheckoutComplete& Delegate) override;`
- L29 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseReceiptlessCheckoutComplete& Delegate) override;`
- L30 _public prototype_ `virtual void FinalizePurchase(const FUniqueNetId& UserId, const FString& ReceiptId) override;`
- L31 _public prototype_ `virtual void RedeemCode(const FUniqueNetId& UserId, const FRedeemCodeRequest& RedeemCodeRequest, const FOnPurchaseRedeemCodeComplete& Delegate) override;`
- L32 _public prototype_ `virtual void QueryReceipts(const FUniqueNetId& UserId, bool bRestoreReceipts, const FOnQueryReceiptsComplete& Delegate) override;`
- L33 _public prototype_ `virtual void GetReceipts(const FUniqueNetId& UserId, TArray<FPurchaseReceipt>& OutReceipts) const override;`
- L34 _public prototype_ `virtual void FinalizeReceiptValidationInfo(const FUniqueNetId& UserId, FString& InReceiptValidationInfo, const FOnFinalizeReceiptValidationInfoComplete& Delegate) override;`
- L47 _public prototype_ `void OnRailAssetsChanged(const FUniqueNetId& UserId);` — Called via an event emitted from the Rail SDK when a user's assets have changed
- L52 _private prototype_ `void QueryReceipts_Complete(const FRequestAllAssetsTaskResult& Result, const FUniqueNetIdRef UserId, const FOnQueryReceiptsComplete Delegate);` — Called when the QueryReceipts async task completes
- L55 _private prototype_ `void Checkout_Complete(const FPurchaseProductsTaskResult& Result, FOnPurchaseCheckoutComplete Delegate);` — Called when the Checkout async task completes
- L58 _private prototype_ `FOnlinePurchaseTencent() = delete;` — Default constructor disabled
- L61 _private member_ `FOnlineSubsystemTencent* const Subsystem;` — Owning subsystem
- L64 _private member_ `TArray<FPurchaseReceipt> PurchaseReceipts;` — Purchase receipts
- L67 _private member_ `bool bCheckoutPending = false;` — Only allow one checkout at a time

#### Free symbols / members of external scopes

- L70 _typedef_ `typedef TSharedPtr<FOnlinePurchaseTencent, ESPMode::ThreadSafe> FOnlinePurchaseTencentPtr;`

### `Plugins/Online/OnlineSubsystemTencent/Source/Private/OnlineSessionTencent.h` (Private)


#### class `FNamedOnlineSessionTencent`  
`class FNamedOnlineSessionTencent : public FNamedOnlineSession`  
_L13-35_
- inherits: `FNamedOnlineSession`
- L17 _private prototype_ `FNamedOnlineSessionTencent() = delete;`
- L21 _public function_ `FNamedOnlineSessionTencent(FName InSessionName, const FOnlineSessionSettings& InSessionSettings) : FNamedOnlineSession(InSessionName, InSessionSettings)` — Constructor used to create a named session directly
- L27 _public function_ `FNamedOnlineSessionTencent(FName InSessionName, const FOnlineSession& Session) : FNamedOnlineSession(InSessionName, Session)` — Constructor used to create a named session directly
- L32 _public function_ `virtual ~FNamedOnlineSessionTencent()`

#### class `FOnlineSessionTencent`  
`class FOnlineSessionTencent : public IOnlineSession, public TSharedFromThis<FOnlineSessionTencent, ESPMode::ThreadSafe>`  
_L40-125_
- inherits: `IOnlineSession,TSharedFromThis<FOnlineSessionTencent,ESPMode::ThreadSafe>`
- L44 _private prototype_ `FOnlineSessionTencent() = delete;` — Hidden on purpose
- L49 _public prototype_ `virtual FUniqueNetIdPtr CreateSessionIdFromString(const FString& SessionIdStr) override;`
- L50 _public prototype_ `virtual class FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSessionSettings& SessionSettings) override;`
- L51 _public prototype_ `virtual class FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSession& Session) override;`
- L52 _public prototype_ `virtual FNamedOnlineSession* GetNamedSession(FName SessionName) override;`
- L53 _public prototype_ `virtual void RemoveNamedSession(FName SessionName) override;`
- L54 _public prototype_ `virtual EOnlineSessionState::Type GetSessionState(FName SessionName) const override;`
- L55 _public prototype_ `virtual bool HasPresenceSession() override;`
- L56 _public prototype_ `virtual bool IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId) override;`
- L57 _public prototype_ `virtual bool StartMatchmaking(const TArray< FUniqueNetIdRef >& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L58 _public prototype_ `virtual bool CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName) override;`
- L59 _public prototype_ `virtual bool CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, FName SessionName) override;`
- L60 _public prototype_ `virtual bool FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L61 _public prototype_ `virtual bool FindSessions(const FUniqueNetId& SearchingPlayerId, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L62 _public prototype_ `virtual bool FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId, const FUniqueNetId& FriendId, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate) override;`
- L63 _public prototype_ `virtual bool CancelFindSessions() override;`
- L64 _public prototype_ `virtual bool PingSearchResults(const FOnlineSessionSearchResult& SearchResult) override;`
- L65 _public prototype_ `virtual bool FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend) override;`
- L66 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend) override;`
- L67 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& FriendList) override;`
- L68 _public prototype_ `virtual bool SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend) override;`
- L69 _public prototype_ `virtual bool SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName, const FUniqueNetId& Friend) override;`
- L70 _public prototype_ `virtual bool SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) override;`
- L71 _public prototype_ `virtual bool SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) override;`
- L72 _public prototype_ `virtual bool GetResolvedConnectString(FName SessionName, FString& ConnectInfo, FName PortType) override;`
- L73 _public prototype_ `virtual bool GetResolvedConnectString(const class FOnlineSessionSearchResult& SearchResult, FName PortType, FString& ConnectInfo) override;`
- L74 _public prototype_ `virtual FOnlineSessionSettings* GetSessionSettings(FName SessionName) override;`
- L75 _public prototype_ `virtual int32 GetNumSessions() override;`
- L76 _public prototype_ `virtual void DumpSessionState() override;`
- L83 _public function_ `FOnlineSessionTencent(FOnlineSubsystemTencent* InSubsystem) : TencentSubsystem(InSubsystem)`
- L88 _public function_ `virtual ~FOnlineSessionTencent()`
- L93 _public function_ `virtual bool Init()` — Initialize the session interface
- L98 _public function_ `virtual void Tick(float DeltaTime)` — Session tick for various background tasks
- L103 _public function_ `virtual void Shutdown()` — Shutdown the session interface
- L108 _public prototype_ `FNamedOnlineSession* GetPresenceSession();` — @return the one session marked as having presence about a user
- L112 _protected function_ `FNamedOnlineSessionTencent* GetNamedSessionTencent(FName SessionName)`
- L117 _protected prototype_ `int32 GetLocalUserIdx(const FUniqueNetId& UserId) const;`
- L120 _protected member_ `mutable FCriticalSection SessionLock;` — Critical sections for thread safe operation of session lists
- L123 _protected member_ `TArray<FNamedOnlineSessionTencent> Sessions;` — Current session settings

#### Free symbols / members of external scopes

- L127 _typedef_ `typedef TSharedPtr<FOnlineSessionTencent, ESPMode::ThreadSafe> FOnlineSessionTencentPtr;`

### `Plugins/Online/OnlineSubsystemTencent/Source/Private/OnlineStoreTencent.h` (Private)


#### class `FOnlineStoreTencent`  
`class FOnlineStoreTencent : public IOnlineStoreV2, public TSharedFromThis<FOnlineStoreTencent, ESPMode::ThreadSafe>`  
_L16-51_
- inherits: `IOnlineStoreV2,TSharedFromThis<FOnlineStoreTencent,ESPMode::ThreadSafe>`
- desc: Implementation for online store via WeGame
- L22 _public prototype_ `virtual ~FOnlineStoreTencent() = default;` — Destructor
- L25 _public prototype_ `virtual void QueryCategories(const FUniqueNetId& UserId, const FOnQueryOnlineStoreCategoriesComplete& Delegate) override;`
- L26 _public prototype_ `virtual void GetCategories(TArray<FOnlineStoreCategory>& OutCategories) const override;`
- L27 _public prototype_ `virtual void QueryOffersByFilter(const FUniqueNetId& UserId, const FOnlineStoreFilter& Filter, const FOnQueryOnlineStoreOffersComplete& Delegate) override;`
- L28 _public prototype_ `virtual void QueryOffersById(const FUniqueNetId& UserId, const TArray<FUniqueOfferId>& OfferIds, const FOnQueryOnlineStoreOffersComplete& Delegate) override;`
- L29 _public prototype_ `virtual void GetOffers(TArray<FOnlineStoreOfferRef>& OutOffers) const override;`
- L30 _public prototype_ `virtual TSharedPtr<FOnlineStoreOffer> GetOffer(const FUniqueOfferId& OfferId) const override;`
- L42 _private prototype_ `FOnlineStoreTencent() = delete;` — Default constructor disabled
- L45 _private member_ `FOnlineSubsystemTencent* const Subsystem;` — Owning subsystem
- L47 _private prototype_ `void QueryOffers_Complete(const FRequestAllPurchasableProductsTaskResult& Result, const TArray<FUniqueOfferId> RequestedOfferIds, FOnQueryOnlineStoreOffersComplete Delegate);`
- L50 _private member_ `TMap<FUniqueOfferId, FOnlineStoreOfferRef> CachedOffers;` — Map of offers queried via QueryOffersById

#### Free symbols / members of external scopes

- L53 _typedef_ `typedef TSharedPtr<FOnlineStoreTencent, ESPMode::ThreadSafe> FOnlineStoreTencentPtr;`

### `Plugins/Online/OnlineSubsystemTencent/Source/Private/OnlineSubsystemTencentPrivate.h` (Private)


#### Free symbols / members of external scopes

- L11 _macro_ `#define RAIL_METADATA_KEY_SEPARATOR TEXT(",")`
- L15 _macro_ `#define ONLINE_LOG_PREFIX TEXT("TENCENT: ")`

### `Plugins/Online/OnlineSubsystemTencent/Source/Private/OnlineUserTencent.h` (Private)


#### class `FOnlineUserInfoTencent`  
`class FOnlineUserInfoTencent : public FOnlineUser`  
_L15-69_
- inherits: `FOnlineUser`
- L18 _public prototype_ `FOnlineUserInfoTencent() = delete;`
- L19 _public function_ `FOnlineUserInfoTencent(const FUniqueNetIdRef& InUserId) : UserId(InUserId)`
- L20 _public prototype_ `virtual ~FOnlineUserInfoTencent() = default;`
- L23 _public function_ `virtual FUniqueNetIdRef GetUserId() const override` — FOnlineUser
- L24 _public function_ `virtual FString GetRealName() const override`
- L30 _public function_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override`
- L36 _public function_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override`
- L45 _public function_ `virtual bool SetUserLocalAttribute(const FString& AttrName, const FString& InAttrValue) override`
- L61 _public prototype_ `UserAttributes.Emplace(MoveTemp(AttrName), MoveTemp(AttrVal));`
- L66 _protected member_ `FUniqueNetIdRef UserId;` — The user's id
- L68 _protected member_ `TMap<FString, FString> UserAttributes;` — User attributes

#### class `FOnlineUserTencent`  
`class FOnlineUserTencent : public IOnlineUser, public TSharedFromThis<FOnlineUserTencent, ESPMode::ThreadSafe>`  
_L80-109_
- inherits: `IOnlineUser,TSharedFromThis<FOnlineUserTencent,ESPMode::ThreadSafe>`
- desc: Tencent service implementation of the online user interface
- L85 _public prototype_ `FOnlineUserTencent() = delete;`
- L86 _public prototype_ `FOnlineUserTencent(FOnlineSubsystemTencent* InSubsystem);`
- L87 _public prototype_ `virtual ~FOnlineUserTencent() = default;`
- L90 _public prototype_ `virtual bool QueryUserInfo(int32 LocalUserNum, const TArray<FUniqueNetIdRef >& UserIds) override;`
- L91 _public prototype_ `virtual bool GetAllUserInfo(int32 LocalUserNum, TArray< TSharedRef<FOnlineUser> >& OutUsers) override;`
- L92 _public prototype_ `virtual TSharedPtr<FOnlineUser> GetUserInfo(int32 LocalUserNum, const FUniqueNetId& UserId) override;`
- L93 _public prototype_ `virtual bool QueryUserIdMapping(const FUniqueNetId& UserId, const FString& DisplayNameOrEmail, const FOnQueryUserMappingComplete& Delegate = FOnQueryUserMappingComplete()) override;`
- L94 _public prototype_ `virtual bool QueryExternalIdMappings(const FUniqueNetId& UserId, const FExternalIdQueryOptions& QueryOptions, const TArray<FString>& ExternalIds, const FOnQueryExternalIdMappingsComplete& Delegate = FOnQueryExternalIdMappingsComplete()) override;`
- L95 _public prototype_ `virtual void GetExternalIdMappings(const FExternalIdQueryOptions& QueryOptions, const TArray<FString>& ExternalIds, TArray<FUniqueNetIdPtr>& OutIds) override;`
- L96 _public prototype_ `virtual FUniqueNetIdPtr GetExternalIdMapping(const FExternalIdQueryOptions& QueryOptions, const FString& ExternalId) override;`
- L100 _private prototype_ `void StartNextQueryUserInfo(int32 LocalUserNum, FUniqueNetIdRef LocalUserId, TArray<FUniqueNetIdRef> UserIds, int32 UserIdsQueriedCount);`
- L101 _private prototype_ `void QueryUserInfo_Complete(const FGetUsersInfoTaskResult& TaskResult, int32 LocalUserNum, FUniqueNetIdRef LocalUserId, TArray<FUniqueNetIdRef> UserIds, int32 UserIdsQueriedCount);`
- L105 _private member_ `FOnlineSubsystemTencent* Subsystem;` — Owning subsystem
- L108 _private member_ `FOnlineUserInfoTencentMap Users;` — Users we have retrieved data for

#### Free symbols / members of external scopes

- L72 _typedef_ `typedef TSharedRef<FOnlineUserInfoTencent> FOnlineUserInfoTencentRef;` — Shared reference to user info
- L75 _typedef_ `typedef TUniqueNetIdMap<TArray<FOnlineUserInfoTencentRef>> FOnlineUserInfoTencentMap;` — Map of local user to online user infos
- L111 _typedef_ `typedef TSharedPtr<FOnlineUserTencent, ESPMode::ThreadSafe> FOnlineUserTencentPtr;`

### `Plugins/Online/OnlineSubsystemTencent/Source/Private/RailSDK.h` (Private)


#### Free symbols / members of external scopes

- L27 _prototype_ `FString LexToString(const rail::RailSystemState State);`
- L28 _prototype_ `FString LexToString(const rail::RailResult Result);`
- L29 _prototype_ `FString LexToString(const rail::EnumRailPlayerOnLineState PlayerOnlineState);`
- L30 _prototype_ `FString LexToString(const rail::EnumRailUsersInviteType InviteType);`
- L31 _prototype_ `FString LexToString(const rail::EnumRailUsersInviteResponseType ResponseType);`
- L32 _prototype_ `FString LexToString(const rail::RailFriendPlayedGamePlayState PlayState);`
- L33 _prototype_ `FString LexToString(const rail::EnumRailAssetState AssetState);`
- L35 _prototype_ `FString LexToString(const rail::RailString& RailString);`
- L37 _prototype_ `void ToRailString(const FString& Str, rail::RailString& OutString);`

### `Plugins/Online/OnlineSubsystemTencent/Source/Private/RailSdkWrapper.h` (Private)


#### class `RailSdkWrapper`  
`class RailSdkWrapper`  
_L14-54_
- desc: Singleton wrapper to manage the Rail SDK usage
- L17 _public prototype_ `virtual ~RailSdkWrapper();`
- L18 _public prototype_ `static RailSdkWrapper& Get();`
- L21 _public prototype_ `bool RailNeedRestartAppForCheckingEnvironment(rail::RailGameID game_id);` — Wrappers for main entry points for Rail SDK
- L22 _public prototype_ `bool RailInitialize();`
- L23 _public prototype_ `void RailFireEvents();`
- L24 _public prototype_ `void RailFinalize();`
- L25 _public prototype_ `void RailRegisterEvent(rail::RAIL_EVENT_ID event_id, rail::IRailEvent* event_handler);`
- L26 _public prototype_ `void RailUnregisterEvent(rail::RAIL_EVENT_ID event_id, rail::IRailEvent* event_handler);`
- L28 _public function_ `bool IsInitialized() const`
- L30 _public prototype_ `rail::IRailFactory* RailFactory() const;`
- L31 _public prototype_ `rail::IRailFriends* RailFriends() const;`
- L32 _public prototype_ `rail::IRailPlayer* RailPlayer() const;`
- L33 _public prototype_ `rail::IRailUtils* RailUtils() const;`
- L34 _public prototype_ `rail::IRailUsersHelper* RailUsersHelper() const;`
- L35 _public prototype_ `rail::IRailInGamePurchase* RailInGamePurchase() const;`
- L36 _public prototype_ `rail::IRailAssets* RailAssets() const;`
- L37 _public prototype_ `rail::IRailGame* RailGame() const;`
- L41 _private prototype_ `RailSdkWrapper();` — Singleton access only
- L44 _private prototype_ `bool Load();` — Load the Rail SDK dlls
- L46 _private prototype_ `void Shutdown();` — Unload the Rail SDK dlls
- L49 _private member_ `bool bIsInitialized;` — Is the DLL loaded and RailInitialize called
- L51 _private member_ `FTencentDll RailSdkDll;` — Dll loaded on init and unloaded and shutdown

### `Plugins/Online/OnlineSubsystemTencent/Source/Private/TencentDllMgr.h` (Private)


#### class `FTencentDll`  
`class FTencentDll`  
_L11-23_
- desc: Singleton wrapper to manage the Tcls proxy connection
- L14 _public prototype_ `FTencentDll();`
- L15 _public prototype_ `virtual ~FTencentDll();`
- L16 _public prototype_ `void* Load(const FString& DllPath, const FString& DllFile);`
- L17 _public prototype_ `void Unload();`
- L18 _public function_ `inline bool IsLoaded() const`
- L19 _public function_ `inline void* GetDllHandle() const`
- L22 _private member_ `void* DllHandle;`

### `Plugins/Online/OnlineSubsystemTencent/Source/Public/MetadataKeysRail.h` (Public)


#### Free symbols / members of external scopes

- L11 _macro_ `#define RAIL_PRESENCE_PRESENCE_KEYS TEXT("PresenceKeys")` — List of all keys that make up a user's presence (FString)
- L13 _macro_ `#define RAIL_PRESENCE_STATUS_KEY TEXT("Status")` — Presence status message (FString)
- L15 _macro_ `#define RAIL_PRESENCE_APPID_KEY TEXT("AppId")` — Running AppId for the user (FString)
- L17 _macro_ `#define RAIL_PRESENCE_SESSION_ID_KEY TEXT("PresenceSessionId")` — GameSession session id, if present (FString)
- L19 _macro_ `#define RAIL_PRESENCE_PRESENCEBITS_KEY TEXT("PresenceBits")` — Basic presence data packed into a bitmask (uint32)
- L26 _macro_ `#define RAIL_SESSION_ID_KEY TEXT("SessionId")` — Presence Session id (FString)
- L28 _macro_ `#define RAIL_SESSION_OWNING_USER_ID_KEY TEXT("OwningUserId")` — Owning user of the presence session (uint64)
- L30 _macro_ `#define RAIL_SESSION_SESSIONBITS_KEY TEXT("SessionBits")` — Bits representing various flags on the session (uint32)
- L32 _macro_ `#define RAIL_SESSION_BUILDUNIQUEID_KEY TEXT("BuildUniqueId")` — Build Id for the running application (int32)

### `Plugins/Online/OnlineSubsystemTencent/Source/Public/OnlineExternalUITencent.h` (Public)


#### class `FOnlineExternalUITencent`  
`class FOnlineExternalUITencent : public IOnlineExternalUI`  
_L16-60_
- inherits: `IOnlineExternalUI`
- desc: Implementation for the Tencent/Rail external UIs
- L27 _private function_ `FOnlineExternalUITencent(FOnlineSubsystemTencent* InSubsystem) : TencentSubsystem(InSubsystem)` — Constructor @param InSubsystem The owner of this external UI interface.
- L37 _public function_ `virtual ~FOnlineExternalUITencent()` — Destructor.
- L42 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;`
- L43 _public function_ `virtual bool ShowAccountCreationUI(const int ControllerIndex, const FOnAccountCreationUIClosedDelegate& Delegate = FOnAccountCreationUIClosedDelegate()) override`
- L44 _public prototype_ `virtual bool ShowFriendsUI(int32 LocalUserNum) override;`
- L45 _public prototype_ `virtual bool ShowInviteUI(int32 LocalUserNum, FName SessionName = NAME_GameSession) override;`
- L46 _public prototype_ `virtual bool ShowAchievementsUI(int32 LocalUserNum) override;`
- L47 _public prototype_ `virtual bool ShowLeaderboardUI(const FString& LeaderboardName) override;`
- L48 _public prototype_ `virtual bool ShowWebURL(const FString& Url, const FShowWebUrlParams& ShowParams, const FOnShowWebUrlClosedDelegate& Delegate = FOnShowWebUrlClosedDelegate()) override;`
- L49 _public prototype_ `virtual bool CloseWebURL() override;`
- L50 _public prototype_ `virtual bool ShowProfileUI(const FUniqueNetId& Requestor, const FUniqueNetId& Requestee, const FOnProfileUIClosedDelegate& Delegate = FOnProfileUIClosedDelegate()) override;`
- L51 _public prototype_ `virtual bool ShowAccountUpgradeUI(const FUniqueNetId& UniqueId) override;`
- L52 _public prototype_ `virtual bool ShowStoreUI(int32 LocalUserNum, const FShowStoreParams& ShowParams, const FOnShowStoreUIClosedDelegate& Delegate = FOnShowStoreUIClosedDelegate()) override;`
- L53 _public prototype_ `virtual bool ShowSendMessageUI(int32 LocalUserNum, const FShowSendMessageParams& ShowParams, const FOnShowSendMessageUIClosedDelegate& Delegate = FOnShowSendMessageUIClosedDelegate()) override;`
- L58 _private member_ `FOnlineSubsystemTencent* TencentSubsystem;`

#### Free symbols / members of external scopes

- L62 _typedef_ `typedef TSharedPtr<FOnlineExternalUITencent, ESPMode::ThreadSafe> FOnlineExternalUITencentPtr;`

### `Plugins/Online/OnlineSubsystemTencent/Source/Public/OnlineIdentityTencent.h` (Public)


#### class `FUserOnlineAccountTencent`  
`class FUserOnlineAccountTencent : public FUserOnlineAccount`  
_L16-92_
- inherits: `FUserOnlineAccount`
- desc: Info associated with a user account generated by signing in to Tencent
- L23 _public prototype_ `virtual FUniqueNetIdRef GetUserId() const override;`
- L24 _public prototype_ `virtual FString GetRealName() const override;`
- L25 _public prototype_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override;`
- L26 _public prototype_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L27 _public prototype_ `virtual bool SetUserAttribute(const FString& AttrName, const FString& AttrValue) override;`
- L31 _public prototype_ `virtual FString GetAccessToken() const override;`
- L32 _public prototype_ `virtual bool GetAuthAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L42 _public function_ `inline bool GetAccountData(const FString& Key, FString& OutVal) const` — Get account data attribute @param Key account data entry key @param OutVal [out] value that was found @return true if entry was found
- L61 _public function_ `inline bool SetAccountData(const FString& Key, const FString& Val)` — Set account data attribute @param Key account data entry key @param Val value that we want to set @return true if entry changed
- L77 _public function_ `FUserOnlineAccountTencent(const FUniqueNetIdRef InUserId) : UserId(InUserId)` — Init/default constructor
- L84 _public prototype_ `virtual ~FUserOnlineAccountTencent() = default;` — Destructor
- L87 _public member_ `FUniqueNetIdRef UserId;` — User Id represented as a FUniqueNetId
- L89 _public member_ `FJsonSerializableKeyValueMap AccountData;` — Any addition account data associated with the user
- L91 _public member_ `FString AuthToken;` — Full auth code which can be exchanged for access

#### class `FOnlineIdentityTencent`  
`class FOnlineIdentityTencent : public IOnlineIdentity, public TSharedFromThis<FOnlineIdentityTencent, ESPMode::ThreadSafe>`  
_L97-168_
- inherits: `IOnlineIdentity,TSharedFromThis<FOnlineIdentityTencent,ESPMode::ThreadSafe>`
- desc: Tencent service implementation of the online identity interface
- L105 _public prototype_ `virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;`
- L106 _public prototype_ `virtual bool Logout(int32 LocalUserNum) override;`
- L107 _public prototype_ `virtual bool AutoLogin(int32 LocalUserNum) override;`
- L108 _public prototype_ `virtual TSharedPtr<FUserOnlineAccount> GetUserAccount(const FUniqueNetId& UserId) const override;`
- L109 _public prototype_ `virtual TArray<TSharedPtr<FUserOnlineAccount> > GetAllUserAccounts() const override;`
- L110 _public prototype_ `virtual FUniqueNetIdPtr GetUniquePlayerId(int32 LocalUserNum) const override;`
- L111 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(uint8* Bytes, int32 Size) override;`
- L112 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(const FString& Str) override;`
- L113 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(int32 LocalUserNum) const override;`
- L114 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(const FUniqueNetId& UserId) const override;`
- L115 _public prototype_ `virtual FString GetPlayerNickname(int32 LocalUserNum) const override;`
- L116 _public prototype_ `virtual FString GetPlayerNickname(const FUniqueNetId& UserId) const override;`
- L117 _public prototype_ `virtual FString GetAuthToken(int32 LocalUserNum) const override;`
- L118 _public prototype_ `virtual void GetUserPrivilege(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate, EShowPrivilegeResolveUI ShowResolveUI=EShowPrivilegeResolveUI::Default) override;`
- L119 _public prototype_ `virtual FPlatformUserId GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& UniqueNetId) const override;`
- L120 _public prototype_ `virtual FString GetAuthType() const override;`
- L121 _public prototype_ `virtual void RevokeAuthToken(const FUniqueNetId& UserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate) override;`
- L137 _public prototype_ `virtual ~FOnlineIdentityTencent();` — Destructor
- L139 _public prototype_ `TSharedPtr<FUserOnlineAccountTencent> GetUserAccountTencent(const FUniqueNetId& UserId) const;`
- L149 _public prototype_ `bool GetLocalUserIdx(const FUniqueNetId& UserId, int32& OutLocalIdx) const;` — Get the local user index for a given user id @param UserId id of logged in user @param OutLocalIdx [out] index of local user @return false if user was not found
- L153 _private prototype_ `void OnRailAcquireSessionTicket(const FOnlineError& OnlineError, const FString& SessionTicket, int32 LocalUserNum, const bool bIsNewUser);`
- L159 _private prototype_ `FOnlineIdentityTencent() = delete;` — Must use the initialization constructor instead
- L162 _private member_ `TSharedPtr<FUserOnlineAccountTencent> UserAccount;` — Users that have been registered. Only one Tencent user can ever be logged in.
- L164 _private member_ `TMap<int32, FUniqueNetIdPtr > UserIds;` — Ids mapped to locally registered users
- L167 _private member_ `FOnlineSubsystemTencent* Subsystem;` — Reference to the main subsystem

#### Free symbols / members of external scopes

- L170 _typedef_ `typedef TSharedPtr<FOnlineIdentityTencent, ESPMode::ThreadSafe> FOnlineIdentityTencentPtr;`

### `Plugins/Online/OnlineSubsystemTencent/Source/Public/OnlinePresenceTencent.h` (Public)


#### class `FOnlineUserPresenceTencent`  
`class FOnlineUserPresenceTencent : public FOnlineUserPresence`  
_L16-22_
- inherits: `FOnlineUserPresence`
- desc: Presence data for a single client logged in by the user

#### class `FOnlinePresenceTencent`  
`class FOnlinePresenceTencent : public IOnlinePresence, public TSharedFromThis<FOnlinePresenceTencent, ESPMode::ThreadSafe>`  
_L29-111_
- inherits: `IOnlinePresence,TSharedFromThis<FOnlinePresenceTencent,ESPMode::ThreadSafe>`
- desc: Tencent/Rail service implementation of the online presence interface
- L36 _public prototype_ `virtual void SetPresence(const FUniqueNetId& User, const FOnlineUserPresenceStatus& Status, const FOnPresenceTaskCompleteDelegate& Delegate = FOnPresenceTaskCompleteDelegate()) override;`
- L37 _public prototype_ `virtual void QueryPresence(const FUniqueNetId& User, const FOnPresenceTaskCompleteDelegate& Delegate = FOnPresenceTaskCompleteDelegate()) override;`
- L38 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedPresence(const FUniqueNetId& User, TSharedPtr<FOnlineUserPresence>& OutPresence) override;`
- L39 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedPresenceForApp(const FUniqueNetId& LocalUserId, const FUniqueNetId& User, const FString& AppId, TSharedPtr<FOnlineUserPresence>& OutPresence) override;`
- L47 _public prototype_ `FOnlinePresenceTencent(FOnlineSubsystemTencent* InSubsystem);` — Constructor @param InSubsystem mcp subsystem being used
- L52 _public prototype_ `virtual ~FOnlinePresenceTencent();` — Destructor
- L59 _public prototype_ `bool Init();` — Initialize the interface @return true if successful, false otherwise
- L64 _public prototype_ `void Shutdown();` — Shutdown the presence interface
- L77 _public prototype_ `void UpdatePresenceFromSessionData();` — Update session related presence keys
- L81 _private prototype_ `FOnlinePresenceTencent() = delete;`
- L84 _private member_ `FOnlineSubsystemTencent* TencentSubsystem;` — Reference to the existing online subsystem
- L86 _private member_ `FOnlineUserPresenceTencentMap CachedPresence;` — Cache of all user presence data received/sent
- L88 _private member_ `TUniqueNetIdMap<EOnlinePresenceState::Type> UserOnlineStatus;` — Cache of online state of various users (in presence or otherwise)
- L90 _private member_ `FDelegateHandle OnLoginChangedHandle;` — Handle to login change events for clearing presence
- L92 _private member_ `FDelegateHandle OnFriendMetadataChangedDelegateHandle;` — Handle to friend metadata change events
- L100 _private prototype_ `void GetGameSessionPresenceData(FMetadataPropertiesRail& InPresenceStatus);` — Fill in the presence data with information from the active game session, if present @param InPresenceStatus presence to fill with data about game session
- L107 _private prototype_ `void OnLoginChanged(int32 LocalUserNum);` — Notification that login status has changed for a user @param LocalUserNum id of local user whose login status has changed
- L110 _private prototype_ `void OnFriendMetadataChangedEvent(const FUniqueNetId& UserId, const FMetadataPropertiesRail& Metadata);` — Delegate fired when platform says friend metadata has changed

#### Free symbols / members of external scopes

- L24 _typedef_ `typedef TUniqueNetIdMap<TSharedRef<FOnlineUserPresenceTencent>> FOnlineUserPresenceTencentMap;`
- L113 _typedef_ `typedef TSharedPtr<FOnlinePresenceTencent, ESPMode::ThreadSafe> FOnlinePresenceTencentPtr;`
- L115 _function_ `inline EOnlinePresenceState::Type RailOnlineStateToOnlinePresence(rail::EnumRailPlayerOnLineState RailState)`

### `Plugins/Online/OnlineSubsystemTencent/Source/Public/OnlineSessionTencentRail.h` (Public)


#### class `FOnlineSessionTencentRail`  
`class FOnlineSessionTencentRail : public FOnlineSessionTencent`  
_L20-227_
- inherits: `FOnlineSessionTencent`
- L24 _private prototype_ `FOnlineSessionTencentRail() = delete;` — Hidden on purpose
- L29 _public prototype_ `virtual bool CreateSession(int32 HostingPlayerNum, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;`
- L30 _public prototype_ `virtual bool CreateSession(const FUniqueNetId& HostingPlayerId, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;`
- L31 _public prototype_ `virtual bool StartSession(FName SessionName) override;`
- L32 _public prototype_ `virtual bool UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings, bool bShouldRefreshOnlineData = true) override;`
- L33 _public prototype_ `virtual bool EndSession(FName SessionName) override;`
- L34 _public prototype_ `virtual bool DestroySession(FName SessionName, const FOnDestroySessionCompleteDelegate& CompletionDelegate = FOnDestroySessionCompleteDelegate()) override;`
- L35 _public prototype_ `virtual bool JoinSession(int32 PlayerNum, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;`
- L36 _public prototype_ `virtual bool JoinSession(const FUniqueNetId& PlayerId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;`
- L37 _public prototype_ `virtual bool FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend) override;`
- L38 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend) override;`
- L39 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& FriendList) override;`
- L40 _public prototype_ `virtual bool SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend) override;`
- L41 _public prototype_ `virtual bool SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName, const FUniqueNetId& Friend) override;`
- L42 _public prototype_ `virtual bool SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) override;`
- L43 _public prototype_ `virtual bool SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) override;`
- L44 _public prototype_ `virtual bool RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited) override;`
- L45 _public prototype_ `virtual bool RegisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players, bool bWasInvited = false) override;`
- L46 _public prototype_ `virtual bool UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId) override;`
- L47 _public prototype_ `virtual bool UnregisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players) override;`
- L48 _public prototype_ `virtual void RegisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnRegisterLocalPlayerCompleteDelegate& Delegate) override;`
- L49 _public prototype_ `virtual void UnregisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnUnregisterLocalPlayerCompleteDelegate& Delegate) override;`
- L50 _public prototype_ `virtual void DumpSessionState() override;`
- L54 _public prototype_ `virtual bool Init() override;`
- L55 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L56 _public prototype_ `virtual void Shutdown() override;`
- L62 _public prototype_ `virtual ~FOnlineSessionTencentRail();`
- L81 _public member_ `FPendingInviteData PendingInvite;` — Contains information about a join/invite parsed from the commandline
- L84 _public function_ `const TArray<FString>& GetCurrentPresenceKeys() const` — @return the last set of keys used to set session presence data
- L93 _public prototype_ `void ParseSearchResult(TSharedPtr<FOnlineSessionSearch> InSearch, const FGetUserInviteTaskResult& InResult);` — Parse a single search result out of a Rail invite (metadata/invite command line) and add the result to current search results @param InSearch search session to add result to @param InResult search result as metadata key/value pairs
- L101 _public prototype_ `void QueryAcceptedUserInvitation(FUniqueNetIdRailRef InLocalUser, FUniqueNetIdRailRef InRemoteUser);` — Retrieve the full details about a remote user session, returning the FOnlineSessionSearchResult via OnSessionUserInviteAccepted @param InLocalUser local user initiating the request @param InRemoteUser remote user to obtain session details for
- L108 _protected prototype_ `void TickPendingInvites(float DeltaTime);` — Waits for the proper time to handle pending invites from the command line
- L113 _protected prototype_ `void CheckPendingSessionInvite();` — Parse the command line for pending session invites
- L120 _protected prototype_ `void RegisterLocalPlayers(FNamedOnlineSession* Session);` — Registers all local players with the current session @param Session the session that they are registering in
- L129 _protected prototype_ `bool OwnsSession(FNamedOnlineSession* Session) const;` — Is the owner of this session local @param Session session of interest @return true if the owner is on this machine, false otherwise
- L139 _protected prototype_ `uint32 CreateInternetSession(int32 HostingPlayerNum, FNamedOnlineSession* Session);` — Create a game server session, advertised on the backend @param HostingPlayerNum local index of the user initiating the request @param Session newly allocated session to create @return ONLINE_SUCCESS if successful, an error code otherwise
- L147 _protected prototype_ `void OnCreateInternetSessionComplete(FName SessionName, const FOnlineError& Error);` — Delegate fired when the session keys have been updated for the CreateSession call @param SessionName name of session that was created @param Error result of the operation
- L158 _protected prototype_ `uint32 JoinInternetSession(int32 PlayerNum, FNamedOnlineSession* Session, const FOnlineSession* SearchSession);` — Join a game server session, advertised on the backend @param PlayerNum local index of the user initiating the request @param Session newly allocated session with join information @param SearchSession the desired session to join @return ONLINE_SUCCESS if successful, an error code otherwise
- L166 _protected prototype_ `void OnJoinInternetSessionComplete(FName SessionName, const FOnlineError& Error);` — Delegate fired when the session keys have been updated for the JoinSession call @param SessionName name of session that was joined @param Error result of the operation
- L174 _protected prototype_ `void OnUpdateSessionComplete(FName SessionName, const FOnlineError& Error);` — Delegate fired when the session keys have been updated for an UpdateSession call @param SessionName name of session that was updated @param Error result of the operation
- L183 _protected prototype_ `uint32 StartInternetSession(FNamedOnlineSession* Session);` — Start an internet session, advertised on the backend @param Session session to end @return ONLINE_SUCCESS if successful, an error code otherwise
- L192 _protected prototype_ `uint32 EndInternetSession(FNamedOnlineSession* Session);` — End an internet session, advertised on the backend @param Session session to end @return ONLINE_SUCCESS if successful, an error code otherwise
- L201 _protected prototype_ `uint32 DestroyInternetSession(FNamedOnlineSession* Session, const FOnDestroySessionCompleteDelegate& CompletionDelegate);` — Destroy an internet session, advertised on the backend @param Session session to destroy @return ONLINE_SUCCESS if successful, an error code otherwise
- L208 _protected prototype_ `DECLARE_DELEGATE_OneParam(FOnUpdateSessionMetadataComplete, const FOnlineError& );` — Delegate fired for each UpdateSessionMetadata call @param Error result of the operation
- L216 _protected prototype_ `void UpdateSessionMetadata(const FNamedOnlineSession& InNamedSession, const FOnUpdateSessionMetadataComplete& InCompletionDelegate);` — Represent a session as a series of key/value pairs Clears all previously known keys from the last call to this function @param InNamedSession session to represent via key/value pairs
- L219 _protected prototype_ `void OnFriendMetadataChangedEvent(const FUniqueNetId& UserId, const FMetadataPropertiesRail& Metadata);` — Delegate fired when platform says friend metadata has changed
- L222 _protected member_ `TArray<FString> CurrentSessionPresenceKeys;` — Last set of keys set by presence
- L224 _protected member_ `FDelegateHandle OnFriendMetadataChangedDelegateHandle;` — Handle to friend metadata change events

#### struct `FOnlineSessionTencentRail::FPendingInviteData`  
`struct FPendingInviteData`  
_L65-78_
- desc: Any invite/join from the command line
- L68 _public member_ `FUniqueNetIdRailPtr InviterUserId;` — User invite information
- L70 _public member_ `FString CommandLineArgs;` — Server invite information
- L72 _public member_ `bool bValidInvite;` — Is this invite valid
- L74 _public function_ `FPendingInviteData() : bValidInvite(false)`

#### Free symbols / members of external scopes

- L208 _delegate_ `DECLARE_DELEGATE_OneParam(FOnUpdateSessionMetadataComplete, const FOnlineError& );` — Delegate fired for each UpdateSessionMetadata call @param Error result of the operation
- L229 _typedef_ `typedef TSharedPtr<FOnlineSessionTencentRail, ESPMode::ThreadSafe> FOnlineSessionTencentRailPtr;`

### `Plugins/Online/OnlineSubsystemTencent/Source/Public/OnlineSubsystemTencent.h` (Public)


#### class `FOnlineSubsystemTencent`  
`class FOnlineSubsystemTencent : public FOnlineSubsystemImpl , public TSharedFromThis<FOnlineSubsystemTencent, ESPMode::ThreadSafe>`  
_L51-200_
- inherits: `FOnlineSubsystemImpl,TSharedFromThis<FOnlineSubsystemTencent,ESPMode::ThreadSafe>`
- desc: Tencent backend services
- L59 _public prototype_ `virtual IOnlineSessionPtr GetSessionInterface() const override;`
- L60 _public prototype_ `virtual IOnlineFriendsPtr GetFriendsInterface() const override;`
- L61 _public prototype_ `virtual IOnlinePartyPtr GetPartyInterface() const override;`
- L62 _public prototype_ `virtual IOnlineGroupsPtr GetGroupsInterface() const override;`
- L63 _public prototype_ `virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override;`
- L64 _public prototype_ `virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;`
- L65 _public prototype_ `virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;`
- L66 _public prototype_ `virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;`
- L67 _public prototype_ `virtual IOnlineVoicePtr GetVoiceInterface() const override;`
- L68 _public prototype_ `virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;`
- L69 _public prototype_ `virtual IOnlineTimePtr GetTimeInterface() const override;`
- L70 _public prototype_ `virtual IOnlineIdentityPtr GetIdentityInterface() const override;`
- L71 _public prototype_ `virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;`
- L72 _public prototype_ `virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override;`
- L73 _public prototype_ `virtual IOnlinePurchasePtr GetPurchaseInterface() const override;`
- L74 _public prototype_ `virtual IOnlineEventsPtr GetEventsInterface() const override;`
- L75 _public prototype_ `virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;`
- L76 _public prototype_ `virtual IOnlineSharingPtr GetSharingInterface() const override;`
- L77 _public prototype_ `virtual IOnlineUserPtr GetUserInterface() const override;`
- L78 _public prototype_ `virtual IOnlineMessagePtr GetMessageInterface() const override;`
- L79 _public prototype_ `virtual IOnlinePresencePtr GetPresenceInterface() const override;`
- L80 _public prototype_ `virtual IOnlineChatPtr GetChatInterface() const override;`
- L81 _public prototype_ `virtual IOnlineStatsPtr GetStatsInterface() const override;`
- L82 _public prototype_ `virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override;`
- L83 _public prototype_ `virtual IOnlineTournamentPtr GetTournamentInterface() const override;`
- L84 _public prototype_ `virtual IMessageSanitizerPtr GetMessageSanitizer(int32 LocalUserNum, FString& OutAuthTypeToExclude) const override;`
- L85 _public prototype_ `virtual FText GetOnlineServiceName() const override;`
- L86 _public prototype_ `virtual FText GetSocialPlatformName() const override;`
- L88 _public prototype_ `virtual bool Init() override;`
- L89 _public prototype_ `virtual void PreUnload() override;`
- L90 _public prototype_ `virtual bool Shutdown() override;`
- L91 _public prototype_ `virtual FString GetAppId() const override;`
- L92 _public prototype_ `virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L96 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L100 _public prototype_ `virtual ~FOnlineSubsystemTencent();`
- L105 _public prototype_ `DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnAASDialog, const FString& , const FString& , const FString& );` — Delegate called when Anti Addiction dialog should be displayed
- L109 _public prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnFriendMetadataChanged, const FUniqueNetId& , const FMetadataPropertiesRail& );` — Delegate fired when platform says friend metadata has changed
- L116 _public prototype_ `void QueueAsyncParallelTask(FOnlineAsyncTask* AsyncTask);`
- L117 _public prototype_ `void QueueAsyncTask(FOnlineAsyncTask* AsyncTask);`
- L118 _public prototype_ `void QueueAsyncOutgoingItem(FOnlineAsyncItem* AsyncItem);`
- L126 _public prototype_ `void AddToMetadataCache(const TMap<FString, FString>& InMetadata);` — Add metadata changes sent to RailSDK to a local cache to prevent unnecessary API calls @param InMetadata data in final form (has _s, _i, etc) known to be succesfully sent to the backend
- L128 _public function_ `const TMap<FString, FString>& GetMetadataCache() const` — @return local cache of metadata set on the RailSDK
- L132 _public prototype_ `FOnlineSubsystemTencent() = delete;` — Only the factory makes instances
- L133 _public prototype_ `explicit FOnlineSubsystemTencent(FName InInstanceName);`
- L137 _private prototype_ `bool HandleAuthExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L138 _private prototype_ `bool HandleSessionExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L139 _private prototype_ `bool HandlePresenceExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L140 _private prototype_ `bool HandleUsersExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L141 _private prototype_ `bool HandleFriendExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L144 _private prototype_ `bool HandleRailSdkWrapperExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);` — Rail SDK exec commands
- L145 _private prototype_ `bool HandleRailSdkWrapperPlayerExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L147 _private prototype_ `void OnLoginChanged(int32 LocalUserNum);`
- L153 _private prototype_ `bool UsesRailSdk() const;` — Check if we should be using the Rail SDK @return true if we should be using the Rail SDK
- L160 _private prototype_ `bool InitRailSdk();` — Initialize Rail SDK @return true if successful
- L165 _private prototype_ `void ShutdownRailSdk();` — Shutdown Rail SDK
- L168 _private member_ `FOnlineIdentityTencentPtr TencentIdentity;` — Interface to the identity registration/auth services (TCLS login support)
- L170 _private member_ `FOnlineSessionTencentPtr TencentSession;` — Interface to the session services (needed for TSS anticheat handling)
- L173 _private member_ `FOnlineFriendsTencentPtr TencentFriends;` — Interface to the friends services
- L175 _private member_ `FOnlinePresenceTencentPtr TencentPresence;` — Interface to the presence services
- L177 _private member_ `FOnlineExternalUITencentPtr TencentExternalUI;` — Interface to the external UI
- L179 _private member_ `FOnlineUserTencentPtr TencentUser;` — Interface to users lookup
- L181 _private member_ `FMessageSanitizerTencentPtr TencentMessageSanitizer;` — Interface to the message sanitizer
- L183 _private member_ `FOnlinePurchaseTencentPtr TencentPurchase;` — Interface for purchasing
- L185 _private member_ `FOnlineStoreTencentPtr TencentStore;` — Interface for store
- L187 _private member_ `uint64 RailGameId;` — Game id for initializing Rail SDK
- L189 _private member_ `TMap<FString, FString> MetadataDataCache;` — Map of all key/value pair data ever attempted to be set on the RailSDK
- L193 _private member_ `FDelegateHandle OnLoginChangedHandle;` — detect login changes from online identity and forward to other services
- L196 _private member_ `FOnlineAsyncTaskManagerTencent* OnlineAsyncTaskThreadRunnable;` — Online async task runnable
- L199 _private member_ `FRunnableThread* OnlineAsyncTaskThread;` — Online async task thread

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAASDialog, const FString& , const FString& , const FString& );` — Delegate called when Tencent requires Anti-Addiction message to be displayed
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAASDialog, const FString& , const FString& , const FString& );` — Delegate called when Tencent requires Anti-Addiction message to be displayed
- L15 _typedef_ `typedef FOnAASDialog::FDelegate FOnAASDialogDelegate;`
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFriendMetadataChanged, const FUniqueNetId& , const FMetadataPropertiesRail& );` — Delegate fired when platform says friend metadata has changed @param UserId the remote user whose data has changed @param Metadata the changed metadata
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFriendMetadataChanged, const FUniqueNetId& , const FMetadataPropertiesRail& );` — Delegate fired when platform says friend metadata has changed @param UserId the remote user whose data has changed @param Metadata the changed metadata
- L25 _typedef_ `typedef FOnFriendMetadataChanged::FDelegate FOnFriendMetadataChangedDelegate;`
- L29 _typedef_ `typedef TSharedPtr<class FOnlineIdentityTencent, ESPMode::ThreadSafe> FOnlineIdentityTencentPtr;` — Forward declarations of all interface classes
- L30 _typedef_ `typedef TSharedPtr<class FOnlineSessionTencent, ESPMode::ThreadSafe> FOnlineSessionTencentPtr;`
- L31 _typedef_ `typedef TSharedPtr<class FOnlineDirectoryTencent, ESPMode::ThreadSafe> FOnlineDirectoryTencentPtr;`
- L32 _typedef_ `typedef TSharedPtr<class FOnlineAsyncTaskManagerTencent, ESPMode::ThreadSafe> FOnlineAsyncTaskManagerTencentPtr;`
- L34 _typedef_ `typedef TSharedPtr<class FOnlineFriendsTencent, ESPMode::ThreadSafe> FOnlineFriendsTencentPtr;`
- L35 _typedef_ `typedef TSharedPtr<class FOnlinePresenceTencent, ESPMode::ThreadSafe> FOnlinePresenceTencentPtr;`
- L36 _typedef_ `typedef TSharedPtr<class FOnlineExternalUITencent, ESPMode::ThreadSafe> FOnlineExternalUITencentPtr;`
- L37 _typedef_ `typedef TSharedPtr<class FOnlineUserTencent, ESPMode::ThreadSafe> FOnlineUserTencentPtr;`
- L38 _typedef_ `typedef TSharedPtr<class FMessageSanitizerTencent, ESPMode::ThreadSafe> FMessageSanitizerTencentPtr;`
- L39 _typedef_ `typedef TSharedPtr<class FOnlinePurchaseTencent, ESPMode::ThreadSafe> FOnlinePurchaseTencentPtr;`
- L40 _typedef_ `typedef TSharedPtr<class FOnlineStoreTencent, ESPMode::ThreadSafe> FOnlineStoreTencentPtr;`
- L202 _typedef_ `typedef TSharedPtr<FOnlineSubsystemTencent, ESPMode::ThreadSafe> FOnlineSubsystemTencentPtr;`

### `Plugins/Online/OnlineSubsystemTencent/Source/Public/OnlineSubsystemTencentModule.h` (Public)


#### class `FOnlineSubsystemTencentModule`  
`class FOnlineSubsystemTencentModule : public IModuleInterface`  
_L10-63_
- inherits: `IModuleInterface`
- desc: Module used for talking with an Tencent service via Http requests
- L15 _private member_ `class FOnlineFactoryTencent* TencentFactory;` — Class responsible for creating instance(s) of the subsystem
- L22 _public function_ `FOnlineSubsystemTencentModule() : TencentFactory(nullptr)` — Constructor
- L29 _public function_ `virtual ~FOnlineSubsystemTencentModule()` — Destructor
- L37 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created
- L42 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed.
- L49 _public function_ `virtual bool SupportsDynamicReloading() override` — Override this to set whether your module is allowed to be unloaded on the fly @return	Whether the module supports shutdown separate from the rest of the engine.
- L59 _public function_ `virtual bool SupportsAutomaticShutdown() override` — Override this to set whether your module would like cleanup on application shutdown @return	Whether the module supports shutdown on application exit

### `Plugins/Online/OnlineSubsystemTencent/Source/Public/OnlineSubsystemTencentPackage.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define PACKAGE_SCOPE public`
- L14 _macro_ `#define PACKAGE_SCOPE protected`

### `Plugins/Online/OnlineSubsystemTencent/Source/Public/OnlineSubsystemTencentTypes.h` (Public)


#### struct `FRailIdKeyFuncs`  
`template <typename ValueType> struct FRailIdKeyFuncs : public TDefaultMapKeyFuncs<rail::RailID, ValueType, false>`  
_L17-22_
- inherits: `TDefaultMapKeyFuncs<rail::RailID,ValueType,false>`
- L19 _public function_ `static inline rail::RailID GetSetKey(TPair<rail::RailID, ValueType> const& Element)`
- L20 _public function_ `static inline uint32 GetKeyHash(rail::RailID const& Key)`
- L21 _public function_ `static inline bool Matches(rail::RailID const& A, rail::RailID const& B)`

#### class `FUniqueNetIdRail`  
`class FUniqueNetIdRail : public FUniqueNetId`  
_L36-188_
- inherits: `FUniqueNetId`
- desc: Rail specific implementation of the unique net id
- L44 _private prototype_ `FUniqueNetIdRail() = delete;` — Hidden on purpose
- L48 _public function_ `template<typename... TArgs> static FUniqueNetIdRailRef Create(TArgs&&... Args)`
- L53 _public function_ `virtual FName GetType() const override`
- L64 _public function_ `virtual const uint8* GetBytes() const override` — Get the raw byte representation of this net id This data is platform dependent and shouldn't be manipulated directly @return byte array of size GetSize()
- L74 _public function_ `virtual int32 GetSize() const override` — Get the size of the id @return size in bytes of the id representation
- L84 _public function_ `virtual bool IsValid() const override` — Check the validity of the id @return true if this is a well formed ID, false otherwise
- L90 _public function_ `static const FUniqueNetIdRef& EmptyId()` — global static instance of invalid (zero) id
- L101 _public function_ `virtual FString ToString() const override` — Platform specific conversion to string representation of data @return data in string form
- L112 _public function_ `virtual FString ToDebugString() const override` — Get a human readable representation of the net id Shouldn't be used for anything other than logging/debugging @return id in string form
- L125 _public function_ `virtual uint32 GetTypeHash() const override`
- L132 _public function_ `operator rail::RailID() const` — Convenience cast to RailID
- L143 _private function_ `explicit FUniqueNetIdRail(const FUniqueNetIdRail& Src) : RailID(Src.RailID)` — Copy Constructor @param Src the id to copy
- L153 _private function_ `explicit FUniqueNetIdRail(uint64 InUniqueNetId) : RailID(InUniqueNetId)` — Constructs this object with the specified net id @param InUniqueNetId the id to set ours to
- L163 _private function_ `explicit FUniqueNetIdRail(rail::RailID InRailID) : RailID(InRailID)` — Constructs this object with the RailID @param InUniqueNetId the id to set ours to
- L173 _private function_ `explicit FUniqueNetIdRail(const FString& Str) : RailID(FCString::Atoi64(*Str))` — Constructs this object with the specified net id @param String textual representation of an id
- L184 _private function_ `explicit FUniqueNetIdRail(const FUniqueNetId& InUniqueNetId) : RailID(*(uint64*)InUniqueNetId.GetBytes())` — Constructs this object with the specified net id @param InUniqueNetId the id to set ours to (assumed to be FUniqueNetIdRail in fact)

#### class `FOnlineSessionInfoTencent`  
`class FOnlineSessionInfoTencent : public FOnlineSessionInfo`  
_L192-267_
- inherits: `FOnlineSessionInfo`
- L196 _private prototype_ `FOnlineSessionInfoTencent(const FOnlineSessionInfoTencent& Src) = delete;` — Hidden on purpose
- L197 _private prototype_ `FOnlineSessionInfoTencent& operator=(const FOnlineSessionInfoTencent& Src) = delete;`
- L208 _public prototype_ `FOnlineSessionInfoTencent();` — Default constructor (for LAN and soon to be serialized values)
- L210 _public prototype_ `FOnlineSessionInfoTencent(const FUniqueNetIdStringPtr& InSessionId);` — Constructor for sessions that represent an advertised session
- L212 _public prototype_ `~FOnlineSessionInfoTencent() = default;`
- L217 _public prototype_ `void Init();` — Initialize a session info with the address of this machine
- L225 _public function_ `static bool IsSessionIdValid(const FString& InSessionId)` — Checks if a session id is valid @param InSessionId the session id to check @return true if InSessionId is a valid session id, false if not
- L236 _public function_ `virtual const uint8* GetBytes() const override`
- L241 _public function_ `virtual int32 GetSize() const override`
- L246 _public function_ `virtual bool IsValid() const override`
- L251 _public function_ `virtual FString ToString() const override`
- L256 _public function_ `virtual FString ToDebugString() const override`
- L262 _public function_ `virtual const FUniqueNetId& GetSessionId() const override`

#### Free symbols / members of external scopes

- L25 _typedef_ `template <typename ValueType> using TRailIdMap = TMap<rail::RailID, ValueType, FDefaultSetAllocator, FRailIdKeyFuncs<ValueType>>;`
- L28 _typedef_ `using FMetadataPropertiesRail = FOnlineKeyValuePairs<FString, FVariantData>;` — Key/Value pairs stored per user on the Rail platform
- L30 _typedef_ `using FUniqueNetIdRailRef = TSharedRef<const class FUniqueNetIdRail>;`
- L31 _typedef_ `using FUniqueNetIdRailPtr = TSharedPtr<const class FUniqueNetIdRail>;`
