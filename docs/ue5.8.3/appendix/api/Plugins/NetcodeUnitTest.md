# Plugins / NetcodeUnitTest

- module root: `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest`
- headers: 35; symbols: 1226
- symbol kinds: class=55, delegate=26, enum=12, enumerator=111, externvar=13, function=199, macro=32, member=338, namespace=6, prototype=411, struct=21, typedef=2
- PrivateDependencyModuleNames: ApplicationCore, EngineSettings, InputCore, NetCore, PacketHandler, RenderCore, Slate, SlateCore, StandaloneRenderer
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Sockets

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/ClientUnitTest.h` (Public)


#### class `UClientUnitTest`  
`class UClientUnitTest : public UProcessUnitTest`  
_L46-707_
- reflection: `UCLASS(Abstract)`
- inherits: `UProcessUnitTest`
- desc: Base class for all unit tests depending upon a MinimalClient connecting to a server. The MinimalClient handles creation/cleanup of an entire new UWorld, UNetDriver and UNetConnection, for fast unit testing. NOTE: See NUTEnum.h, for important flags for configuring unit tests and the minimal client. In subclasses, implement the unit test within the ExecuteClientUnitTest function (remembering to call parent)
- L61 _protected member_ `EUnitTestFlags UnitTestFlags;` — All of the internal unit test parameters/flags, for controlling state and execution
- L64 _protected member_ `EMinClientFlags MinClientFlags;` — Flags for configuring the minimal client - lots of interdependencies between these and UnitTestFlags
- L67 _protected member_ `TSubclassOf<UMinimalClient> MinClientClass;` — The class to use for the MinimalClient
- L71 _protected member_ `FString BaseServerURL;` — The base URL the server should start with
- L74 _protected member_ `FString BaseServerParameters;` — The (non-URL) commandline parameters the server should be launched with
- L78 _protected member_ `FString ServerBeaconType;` — If connecting to a beacon, the beacon type name we are connecting to
- L81 _protected member_ `FString BaseClientURL;` — The base URL clients should start with
- L84 _protected member_ `FString BaseClientParameters;` — The (non-URL) commandline parameters clients should be launched with
- L88 _protected member_ `TArray<TObjectPtr<UClass>> AllowedClientActors;` — `UPROPERTY()` — Actors the server is allowed replicate to client (requires AllowActors flag). Use NotifyAllowNetActor for conditional allows.
- L91 _protected member_ `TArray<FString> AllowedClientRPCs;` — Clientside RPC's that should be allowed to execute (requires minimal client NotifyProcessNetEvent flag)
- L96 _protected member_ `TWeakPtr<FUnitTestProcess> ServerHandle;` — Reference to the created server process handling struct
- L99 _protected member_ `FString ServerAddress;` — The address of the launched server
- L102 _protected member_ `FString BeaconAddress;` — The address of the server beacon (if UnitTestFlags are set to connect to a beacon)
- L105 _protected member_ `TWeakPtr<FUnitTestProcess> ClientHandle;` — Reference to the created client process handling struct (if enabled)
- L108 _protected member_ `bool bBlockingServerDelay;` — Whether or not there is a blocking event/process preventing setup of the server
- L111 _protected member_ `bool bBlockingClientDelay;` — Whether or not there is a blocking event/process preventing setup of a client
- L114 _protected member_ `bool bBlockingMinClientDelay;` — Whether or not there is a blocking event/process preventing the minimal client from connecting
- L117 _protected member_ `double NextBlockingTimeout;` — When a server is launched after a blocking event/process, this delays the launch of any clients, in case of more blockages
- L122 _protected member_ `TObjectPtr<UMinimalClient> MinClient;` — `UPROPERTY()` — The object which handles implementation of the minimal client
- L125 _protected member_ `bool bTriggerredInitialConnect;` — Whether or not the initial connect of the minimal client was triggered
- L132 _protected member_ `TWeakObjectPtr<APlayerController> UnitPC;` — `UPROPERTY()` — Stores a reference to the replicated PlayerController (if set to wait for this), after NotifyHandleClientPlayer
- L135 _protected member_ `bool bUnitPawnSetup;` — Whether or not the UnitPC Pawn was fully setup (requires EUnitTestFlags::RequirePawn)
- L138 _protected member_ `bool bUnitPlayerStateSetup;` — Whether or not the UnitPC PlayerState was fully setup (requires EUnitTestFlags::RequirePlayerState)
- L142 _protected member_ `TWeakObjectPtr<ANUTActor> UnitNUTActor;` — `UPROPERTY()` — If EUnitTestFlags::RequireNUTActor is set, stores a reference to the replicated NUTActor
- L145 _protected member_ `bool bUnitNUTActorSetup;` — Whether or not UnitNUTActor is fully setup, i.e. has replicated its Owner
- L149 _protected member_ `TWeakObjectPtr<AActor> UnitBeacon;` — `UPROPERTY()` — If EUnitTestFlags::RequireBeacon is set, stores a reference to the replicated beacon
- L152 _protected member_ `bool bReceivedPong;` — If EUnitTestFlags::RequirePing is true, whether or not we have already received the pong
- L155 _protected member_ `bool bPendingNetworkFailure;` — An expected network failure occurred, which will be handled during the next tick instead of immediately
- L161 _private member_ `TObjectPtr<UClass> OnlineBeaconClass_Private;` — `UPROPERTY()` — Cached reference to the OnlineBeaconClient static class
- L164 _private prototype_ `void InitOnlineBeaconClass();`
- L166 _private function_ `UClass* GetOnlineBeaconClass()`
- L186 _public prototype_ `virtual void ExecuteClientUnitTest() PURE_VIRTUAL(UClientUnitTest::ExecuteClientUnitTest,);` — Override this, to implement the client unit test NOTE: Should be called last, in overridden functions IMPORTANT: EndUnitTest should be triggered, upon completion of the unit test (which may be delayed, for many unit tests)
- L194 _public prototype_ `virtual void NotifyAlterMinClient(FMinClientParms& Parms);` — Gives subclass UnitTest's an opportunity to alter the MinimalClient setup parameters @param Parms		Reference to the MinimalClient parameters prior to setup/connection
- L199 _public prototype_ `virtual void NotifyMinClientConnected();` — Notification from the minimal client, that it has fully connected
- L207 _public function_ `virtual void NotifyNUTControl(ENUTControlCommand CmdType, FString Command)` — Override this, to receive notification of NMT_NUTControl messages, from the server @param CmdType		The command type @param Command		The command being received
- L217 _public prototype_ `virtual void NotifyControlMessage(FInBunch& Bunch, uint8 MessageType);` — Override this, to receive notification of all other non-NMT_NUTControl control messages @param Bunch			The bunch containing the control message @param MessageType	The control message type
- L225 _public prototype_ `virtual void NotifyHandleClientPlayer(APlayerController* PC, UNetConnection* Connection);` — Notification that the local net connections PlayerController has been replicated and is being setup @param PC			The new local PlayerController @param Connection	The connection associated with the PlayerController
- L234 _public prototype_ `virtual void NotifyAllowNetActor(UClass* ActorClass, bool bActorChannel, bool& bBlockActor);` — Notification triggered BEFORE a replicated actor has been created (allowing you to block creation, based on class) @param ActorClass	The actor class that is about to be created @param bActorChannel	Whether or not this actor is being created within an actor channel @param bBlockActor	Whether or not to block creation of that actor (defaults to true)
- L242 _public prototype_ `virtual void NotifyNetActor(UActorChannel* ActorChannel, AActor* Actor);` — Override this, to receive notification AFTER an actor channel actor has been created @param ActorChannel	The actor channel associated with the actor @param Actor			The actor that has just been created
- L250 _public prototype_ `virtual void NotifyNetworkFailure(ENetworkFailure::Type FailureType, const FString& ErrorString);` — Triggered upon a network connection failure @param FailureType	The reason for the net failure @param ErrorString	More detailed error information
- L260 _public function_ `virtual void NotifyReceivedRawPacket(void* Data, int32& Count)` — If EUnitTestFlags::CaptureReceiveRaw is set, this is triggered for every packet received from the server NOTE: Data is a uint8 array, of size 'NETWORK_MAX_PACKET', and elements can safely be modified @param Data		The raw data/packet being received (this data can safely be modified, up to length 'NETWORK_MAX_PACKET') @param Count		The amount of data received (if 'Data' is modified, this should be modified to reflect the new length)
- L274 _public function_ `virtual void NotifySocketSendRawPacket(void* Data, int32 Count, bool& bBlockSend)` — Triggered for every packet sent to the server, when LowLevelSend is called. IMPORTANT: This occurs AFTER PacketHandler's have had a chance to modify packet data NOTE: Don't consider data safe to modify (will need to modify the implementation, if that is desired) @param Data			The raw data/packet being sent @param Count			The amount of data being sent @param bBlockSend	Whether or not to block the send (defaults to false)
- L284 _public prototype_ `virtual void ReceivedControlBunch(FInBunch& Bunch);` — Bunches received on the control channel. These need to be parsed manually, because the control channel is intentionally disrupted (otherwise it can affect the main client state) @param Bunch			The bunch being received
- L295 _public function_ `virtual void NotifyProcessEvent(AActor* Actor, UFunction* Function, void* Parameters, bool& bBlockEvent)` — Overridable in subclasses - can be used to control/block any script events, other than receiving of RPC's (see NotifyReceiveRPC) @param Actor			The actor the event is being executed on @param Function		The script function being executed @param Parameters	The raw unparsed parameters, being passed into the function @param bBlockEvent	Whether or not to block the event from executing
- L307 _public prototype_ `virtual void NotifyReceiveRPC(AActor* Actor, UFunction* Function, void* Parameters, bool& bBlockRPC);` — Overridable in subclasses - can be used to control/block receiving of RPC's @param Actor			The actor the RPC is being executed on @param Function		The RPC being executed @param Parameters	The raw unparsed parameters, being passed into the function @param bBlockRPC		Whether or not to block the RPC from executing
- L320 _public function_ `virtual void NotifySendRPC(AActor* Actor, UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack, UObject* SubObject, bool& bBlockSendRPC)` — Overridable in subclasses - can be used to control/block sending of RPC's @param Actor				The actor the RPC will be called in @param Function			The RPC to call @param Parameters		The parameters data blob @param OutParms			Out parameter information (irrelevant for RPC's) @param Stack				The script stack @param SubObject			The sub-object the RPC is being called in (if applicable) @param bBlockSendRPC		Whether or not to allow sending of the RPC
- L326 _public prototype_ `virtual void NotifyProcessLog(TWeakPtr<FUnitTestProcess> InProcess, const TArray<FString>& InLogLines) override;`
- L328 _public prototype_ `virtual void NotifyProcessFinished(TWeakPtr<FUnitTestProcess> InProcess) override;`
- L330 _public prototype_ `virtual void NotifyProcessSuspendState(TWeakPtr<FUnitTestProcess> InProcess, ESuspendState InSuspendState) override;`
- L333 _public prototype_ `virtual void NotifySuspendRequest() override;`
- L335 _public prototype_ `virtual bool NotifyConsoleCommandRequest(FString CommandContext, FString Command) override;`
- L337 _public prototype_ `virtual void GetCommandContextList(TArray<TSharedPtr<FString>>& OutList, FString& OutDefaultContext) override;`
- L351 _public prototype_ `bool SendNUTControl(ENUTControlCommand CommandType, FString Command);` — Sends an NMT_NUTControl control channel message, for the server NUTActor. See NUTActor.h @param CommandType	The type of NUTActor control channel command being sent. @param Command		The command parameters. @return				Whether or not the command was sent successfully.
- L356 _public prototype_ `bool SendRPCChecked(UObject* Target, const TCHAR* FunctionName, void* Parms, int16 ParmsSize, int16 ParmsSizeCorrection=0);` — See UMinimalClient
- L361 _public prototype_ `bool SendRPCChecked(UObject* Target, FFuncReflection& FuncRefl);` — See UMinimalClient
- L375 _public function_ `FORCEINLINE bool SendUnitRPCChecked(FString RPCName)` — As above, except executes a static UFunction in the unit test (must be prefixed with UnitTestServer_), on the unit test server, allowing unit tests to define and contain their own 'pseudo'-RPC's. Functions that you want to call, must match this function template: UFUNCTION() static void UnitTestServer_Func(ANUTActor* InNUTActor); @param RPCName	The name of the pseudo-RPC, which should be executed @return			Whether or not the pseudo-RPC was sent successfully
- L389 _public function_ `template<class TargetClass> FORCEINLINE bool SendUnitRPCChecked(FString RPCName)` — As above, except allows 'UnitTestServer' RPC's to be located in an arbitrary class (e.g. if shared between unit tests), specified as the delegate parameter. @param TargetClass	The class which the 'UnitTestServer' function resides in. @param RPCName		The name of the pseudo-RPC, which should be executed @return				Whether or not the pseudo-RPC was sent successfully
- L398 _private prototype_ `bool SendUnitRPCChecked_Internal(UObject* Target, FString RPCName);` — Internal implementation of the above functions
- L404 _public prototype_ `void OnRPCFailure();` — Callback for when an RPC send fails on the minimal client
- L410 _public function_ `static FORCEINLINE const TCHAR* GetGenericExploitFailLog()` — Gets the generic log message that is used to indicate unit test failure
- L419 _public prototype_ `void SendGenericExploitFailLog();` — Sends a generic log message to the server, which (if successfully logged) indicates unit test failure. This is for use with unit tests that are expecting a crash.
- L437 _protected function_ `template<EUnitTestFlags CompileTimeUnitFlags=EUnitTestFlags::None, EMinClientFlags CompileTimeMinFlags=EMinClientFlags::None> void ValidateUnitFlags(EUnitTestFlags RuntimeUnitFlags=EUnitTestFlags::None, EMinClientFlags RuntimeMinFlags=EMinClientFlags::None)` — Validates, both at compile time (template params) or at runtime (function params), that the specified flags are valid. When specifying the whole flag list in one go, do a compile time check using the template parameters. When modifying a runtime-written flag list, do a runtime check on the final flag variables using the function parameters. @param CompileTimeUnitFlags	The compile-time unit test flag list to be checked @param CompileTimeMinFlags	The compile-time minimal client flag list to be checked @param RuntimeUnitFlags		The runtime unit test flag list to be checked @param RuntimeMinFlags		The runtime minimal client flag list to be checked
- L551 _protected function_ `template<EUnitTestFlags CompileTimeUnitFlags=EUnitTestFlags::None, EMinClientFlags CompileTimeMinFlags=EMinClientFlags::None> void SetFlags()` — Sets and validates at compile time, that the specified flags are valid. NOTE: If your unit test subclasses another, it will have to manually change UnitTestFlags/MinClientFlags at runtime. @param CompileTimeUnitFlags	The compile-time flag list to be checked @param CompileTimeMinFlags	The compile-time flag list to be checked
- L559 _protected prototype_ `virtual bool ValidateUnitTestSettings(bool bCDOCheck=false) override;`
- L561 _protected prototype_ `virtual void ResetTimeout(FString ResetReason, bool bResetConnTimeout=false, uint32 MinDuration=0) override;`
- L567 _protected prototype_ `EUnitTestFlags GetMetRequirements();` — Returns the requirements flags, that this unit test currently meets
- L575 _protected prototype_ `bool HasAllRequirements(bool bIgnoreCustom=false);` — Whether or not all 'requirements' flag conditions have been met @param bIgnoreCustom		If true, checks all requirements other than custom requirements @return					Whether or not all requirements are met
- L586 _public function_ `virtual bool HasAllCustomRequirements()` — Optionally, if the 'RequireCustom' flag is set, this returns whether custom conditions have been met. Only use this if you are mixing multiple 'requirements' flags - if just using 'RequireCustom', trigger 'ExecuteClientUnitTest' manually NOTE: You still have to check 'HasAllRequirements' and trigger 'ExecuteClientUnitTest', at the time the custom conditions are set
- L597 _public prototype_ `virtual ELogType GetExpectedLogTypes() override;` — Returns the type of log entries that this unit expects to output, for setting up log window filters (only needs to return values which affect what tabs are shown) @return		The log type mask, representing the type of log entries this unit test expects to output
- L600 _protected prototype_ `virtual bool ExecuteUnitTest() override;`
- L602 _protected prototype_ `virtual void CleanupUnitTest(EUnitTestResetStage ResetStage) override;`
- L611 _protected prototype_ `virtual bool ConnectMinimalClient(const TCHAR* InNetID=nullptr);` — Connects a minimal client, to the launched/launching server @param InNetID		The unique net id the player should use @return				Whether or not the connection kicked off successfully
- L616 _protected prototype_ `virtual void CleanupMinimalClient();` — Cleans up the minimal client
- L621 _protected prototype_ `void TriggerAutoReconnect();` — Triggers an auto-reconnect (disconnect/reconnect) of the minimal client
- L627 _protected prototype_ `virtual void StartUnitTestServer();` — Starts the server process for a particular unit test
- L634 _protected prototype_ `virtual FString ConstructServerParameters();` — Puts together the commandline parameters the server should use, based upon the unit test settings @return			The final server commandline
- L644 _public prototype_ `static void GetNextServerPorts(int32& OutServerPort, int32& OutBeaconPort, bool bAdvance=true);` — Determine the next unique server ports to use - incremented to a new unique number, internally @param OutServerPort		Outputs the next server port @param OutBeaconPort		Outputs the next beacon port @param bAdvance			Whether to advance the internal unique counter, for ports (to e.g. get ports for unlaunched unit tests)
- L654 _protected prototype_ `virtual TWeakPtr<FUnitTestProcess> StartUnitTestClient(FString ConnectIP, bool bMinimized=true);` — Starts a client process tied to the unit test, and connects to the specified server address @param ConnectIP		The IP address the client should connect to @param bMinimized	Starts the client with the window minimized (some unit tests need this off) @return				Returns a pointer to the client process handling struct
- L662 _protected prototype_ `virtual FString ConstructClientParameters(FString ConnectIP);` — Puts together the commandline parameters clients should use, based upon the unit test settings @param ConnectIP	The IP address the client will be connecting to @return			The final client commandline
- L665 _protected prototype_ `virtual void PrintUnitTestProcessErrors(TSharedPtr<FUnitTestProcess> InHandle) override;`
- L668 _protected prototype_ `virtual void UnitTick(float DeltaTime) override;`
- L670 _protected prototype_ `virtual bool IsTickable() const override;`
- L672 _protected prototype_ `virtual void LogComplete() override;`
- L674 _protected prototype_ `virtual void UnblockEvents(EUnitTaskFlags ReadyEvents) override;`
- L676 _protected prototype_ `virtual bool IsConnectionLogSource(UNetConnection* InConnection) override;`
- L685 _public function_ `FORCEINLINE EUnitTestFlags GetUnitTestFlags()` — Accessor for UnitTestFlags @return	Returns the value of UnitTestFlags
- L695 _public function_ `FORCEINLINE TWeakPtr<FUnitTestProcess> GetServerHandle()` — Accessor for ServerHandle @return	Returns the value of ServerHandle
- L703 _public function_ `FORCEINLINE FString GetBeaconAddress() const` — Accessor for BeaconAddress

#### Free symbols / members of external scopes

- L445 _macro_ `#define FLAG_ASSERT(Condition, Message) \` — Implements the '*Flags' variables within 'Condition', for both static/compile-time checks, and runtime checks

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/MinimalClient.h` (Public)


#### struct `FMinClientParms`  
`struct FMinClientParms`  
_L143-209_
- desc: Parameters for configuring the minimal client - also directly inherited by UMinimalClient
- L149 _public member_ `EMinClientFlags MinClientFlags;` — The flags used for configuring the minimal client
- L152 _public member_ `FString ServerAddress;` — The address of the launched server
- L155 _public member_ `FString BeaconAddress;` — The address of the server beacon (if MinClientFlags are set to connect to a beacon)
- L158 _public member_ `FString URLOptions;` — The URL options to connect with
- L161 _public member_ `FString BeaconType;` — If connecting to a beacon, the beacon type name we are connecting to
- L164 _public member_ `FString JoinUID;` — If overriding the UID used for joining, this specifies it
- L167 _public member_ `TArray<FString> AllowedClientRPCs;` — Clientside RPC's that should be allowed to execute (requires the NotifyProcessNetEvent flag)
- L170 _public member_ `uint32 Timeout;` — The amount of time (in seconds) before the connection should timeout
- L173 _public member_ `FString NetDriverClass;` — The net driver class to use (defaults to IpNetDriver, if not specified)
- L179 _public function_ `FMinClientParms() : MinClientFlags(EMinClientFlags::None) , ServerAddress() , BeaconAddress() , URLOptions() , BeaconType() , JoinUID(TEXT("Dud")) , Timeout(30) , NetDriverClass(TEXT(""))` — Default constructor
- L195 _protected prototype_ `void ValidateParms();` — Verify that the parameters specified to this struct are valid
- L197 _protected function_ `void CopyParms(FMinClientParms& Target)`

#### struct `FMinClientHooks`  
`struct FMinClientHooks`  
_L215-299_
- desc: Delegate hooks for the minimal client - also directly inherited by UMinimalClient
- L221 _public member_ `FOnMinClientConnected ConnectedDel;` — Delegate for notifying of successful minimal client connection
- L224 _public member_ `FOnMinClientNetworkFailure NetworkFailureDel;` — Delegate notifying of network failure
- L227 _public member_ `FOnProcessNetEvent ReceiveRPCDel;` — Delegate for notifying/controlling RPC receives
- L231 _public member_ `FOnSendRPC SendRPCDel;` — Delegate for notifying/controlling RPC sends
- L235 _public member_ `FOnMinClientReceivedControlBunch ReceivedControlBunchDel;` — Delegate for notifying of control channel bunches
- L238 _public member_ `FOnMinClientReceivedRawPacket ReceivedRawPacketDel;` — Delegate for notifying of net connection raw packet receives
- L242 _public member_ `FOnLowLevelSend LowLevelSendDel;` — Delegate for notifying of net connection low level packet sends
- L246 _public member_ `FOnMinClientRepActorSpawn RepActorSpawnDel;` — Delegate for notifying/controlling replicated actor spawning
- L249 _public member_ `FOnMinClientNetActor NetActorDel;` — Delegate for notifying AFTER net actor creation
- L252 _public member_ `FOnHandleClientPlayer HandleClientPlayerDel;` — Delegate for notifying of the net connection HandlerClientPlayer event
- L255 _public member_ `FOnRPCFailure RPCFailureDel;` — Delegate for notifying of failure during call of SendRPCChecked
- L261 _public function_ `FMinClientHooks() : ConnectedDel() , NetworkFailureDel() , ReceiveRPCDel() #if !UE_BUILD_SHIPPING , SendRPCDel() #endif , ReceivedControlBunchDel() , ReceivedRawPacketDel() #if !UE_BUILD_SHIPPING , LowLevelSendDel() #endif , RepActorSpawnDel() , NetActorDel() , HandleClientPlayerDel() , RPCFailureDel()` — Default constructor
- L281 _protected function_ `void CopyHooks(FMinClientHooks& Target)`

#### struct `FProtMinClientParms`  
`struct FProtMinClientParms : protected FMinClientParms`  
_L302-302_
- inherits: `FMinClientParms`
- desc: Sidestep header parser enforcement of 'public' on inheritance below

#### struct `FProtMinClientHooks`  
`struct FProtMinClientHooks : protected FMinClientHooks`  
_L303-303_
- inherits: `FMinClientHooks`

#### class `UMinimalClient`  
`class UMinimalClient : public UObject, public FNetworkNotify, public FProtMinClientParms, public FProtMinClientHooks, public FUnitLogRedirect`  
_L311-568_
- reflection: `UCLASS()`
- inherits: `UObject,FNetworkNotify,FProtMinClientParms,FProtMinClientHooks,FUnitLogRedirect`
- desc: Base class for implementing a barebones/stripped-down game client, capable of connecting to a regular game server, but stripped/locked-down so that the absolute minimum of client/server netcode functionality is executed, for connecting the client.
- L330 _public prototype_ `bool Connect(FMinClientParms Parms, FMinClientHooks Hooks);` — Connects the minimal client to a server, with Parms specifying the server details and minimal client configuration, and passing back the low level netcode events specified by Hooks. @param Parms		The server parameters and minimal client configuration. @param Hooks		The delegates for hooking low level netcode events in the minimal client. @return			Whether or not the connection kicked off successfully.
- L335 _public prototype_ `void Cleanup();` — Disconnects and cleans up the minimal client.
- L345 _public prototype_ `FOutBunch* CreateChannelBunchByName(const FName& ChName, int32 ChIndex=INDEX_NONE);` — Creates a bunch for the specified channel, with the ability to create the channel as well WARNING: Can return nullptr! (e.g. if the control channel is saturated) @param ChName			Specify the type of channel the bunch will be sent on @param ChIndex			Specify the index of the channel to send the bunch on (otherwise, picks the next free/unused channel) @return					Returns the created bunch, or nullptr if it couldn't be created
- L352 _public prototype_ `void DiscardChannelBunch(FOutBunch* Bunch);` — Discards a created bunch, without sending it - don't use this for sent packets @param Bunch		The bunch to discard
- L360 _public prototype_ `bool SendControlBunch(FOutBunch* ControlChanBunch);` — Sends a bunch over the control channel @param ControlChanBunch	The bunch to send over the control channel @return					Whether or not the bunch was sent successfully
- L369 _public prototype_ `bool SendRawBunch(FOutBunch& Bunch, bool bAllowPartial=false);` — Sends a raw packet bunch, directly to the NetConnection, with the option of automatically  splitting into partial bunches. @param Bunch				The bunch to send @param bAllowPartial		Whether to allow automatic splitting of the packet into partial packets, if it exceeds the maximum size @return					Whether or not the bunch was sent successfully
- L384 _public prototype_ `bool SendRPCChecked(UObject* Target, const TCHAR* FunctionName, void* Parms, int16 ParmsSize, int16 ParmsSizeCorrection=0);` — Sends the specified RPC for the specified actor, and verifies that the RPC was sent (triggering RPCFailureDel if not) @param Target				The Actor or ActorComponent which will send the RPC @param FunctionName			The name of the RPC @param Parms					The RPC parameters (same as would be specified to ProcessEvent) @param ParmsSize				The size of the RPC parameters, for verifying binary compatibility @param ParmsSizeCorrection	Some parameters are compressed to a different size. Verify Parms matches, and use this to correct. @return						Whether or not the RPC was sent successfully
- L393 _public prototype_ `bool SendRPCChecked(UObject* Target, FFuncReflection& FuncRefl);` — As above, except optimized for use with reflection @param Target	The Actor or ActorComponent which will send the RPC @param FuncRefl	The function reflection instance, containing the function to be called and its assigned parameters. @return			Whether or not the RPC was sent successfully
- L399 _public prototype_ `void PreSendRPC();` — Internal function, for preparing for a checked RPC call
- L408 _public prototype_ `bool PostSendRPC(FString RPCName, UObject* Target=nullptr);` — Internal function, for handling the aftermath of a checked RPC call @param RPCName	The name of the RPC, for logging purposes @param Target	The Actor or ActorComponent the RPC is being called on (optional - for internal logging/debugging) @return			Whether or not the RPC was sent successfully
- L416 _public prototype_ `void ResetConnTimeout(float Duration);` — Resets the net connection timeout @param Duration	The duration which the timeout reset should last
- L424 _public function_ `FORCEINLINE EMinClientFlags GetMinClientFlags()` — Retrieve the value of MinClientFlags
- L432 _public function_ `FORCEINLINE UWorld* GetUnitWorld()` — Retrieve the value of UnitWorld
- L440 _public function_ `FORCEINLINE UNetConnection* GetConn()` — Retrieve the value of UnitConn
- L448 _public function_ `FORCEINLINE bool IsConnected()` — Whether or not the minimal client is connected to the server
- L457 _public prototype_ `void UnitTick(float DeltaTime);` — Ticks the minimal client, through the owner unit tests UnitTick function
- L462 _public prototype_ `bool IsTickable() const;` — Whether or not the minimal client requires ticking.
- L471 _protected prototype_ `bool ConnectMinimalClient();` — Creates the minimal client state, and connects to the server @return	Whether or not the connection was successfully kicked off
- L476 _protected prototype_ `void CreateNetDriver();` — Creates a net driver for the minimal client
- L481 _protected prototype_ `void SendInitialJoin();` — Sends the packet for triggering the initial join (usually is delayed, by the PacketHandler)
- L486 _protected prototype_ `virtual void WriteControlLogin(FOutBunch* ControlChanBunch);` — Writes the NMT_Login message, as a part of SendInitialJoin (separated to make it overridable)
- L493 _protected prototype_ `void DisconnectMinimalClient();` — Disconnects the minimal client - including destructing the net driver and such (tears down the whole connection) NOTE: Based upon the HandleDisconnect function, except removing parts that are undesired (e.g. which trigger level switch)
- L498 _protected prototype_ `void NotifySocketSend(void* Data, int32 Count, bool& bBlockSend);` — See FOnLowLevelSend
- L503 _protected prototype_ `void NotifyReceivedRawPacket(void* Data, int32 Count, bool& bBlockReceive);` — See FOnReceivedRawPacket
- L508 _protected prototype_ `void NotifyReceiveRPC(AActor* Actor, UFunction* Function, void* Parameters, bool& bBlockRPC);` — See FOnProcessNetEvent
- L514 _protected prototype_ `void NotifySendRPC(AActor* Actor, UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack, UObject* SubObject, bool& bBlockSendRPC);` — See FOnSendRPC
- L519 _protected prototype_ `void InternalNotifyNetworkFailure(UWorld* InWorld, UNetDriver* InNetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);`
- L526 _protected function_ `virtual EAcceptConnection::Type NotifyAcceptingConnection() override`
- L531 _protected function_ `virtual void NotifyAcceptedConnection(UNetConnection* Connection) override`
- L535 _protected prototype_ `virtual bool NotifyAcceptingChannel(UChannel* Channel) override;`
- L537 _protected function_ `virtual void NotifyControlMessage(UNetConnection* Connection, uint8 MessageType, FInBunch& Bunch) override`
- L545 _protected member_ `bool bConnected;` — Whether or not the minimal client is connected
- L549 _protected member_ `TObjectPtr<UWorld> UnitWorld;` — `UPROPERTY()` — Stores a reference to the created empty world, for execution and later cleanup
- L553 _protected member_ `TObjectPtr<UNetDriver> UnitNetDriver;` — `UPROPERTY()` — Stores a reference to the created unit test net driver, for execution and later cleanup
- L557 _protected member_ `TObjectPtr<UNetConnection> UnitConn;` — `UPROPERTY()` — Stores a reference to the server connection
- L560 _protected member_ `TArray<int32> PendingNetActorChans;` — If notifying of net actor creation, this keeps track of new actor channel indexes pending notification
- L563 _protected member_ `bool bSentBunch;` — Whether or not a bunch was successfully sent
- L567 _private member_ `FDelegateHandle InternalNotifyNetworkFailureDelegateHandle;` — Handle to the registered InternalNotifyNetworkFailure delegate

#### Free symbols / members of external scopes

- L83 _delegate_ `DECLARE_DELEGATE(FOnMinClientConnected);` — Delegate for marking the minimal client as having connected fully
- L83 _prototype_ `DECLARE_DELEGATE(FOnMinClientConnected);` — Delegate for marking the minimal client as having connected fully
- L91 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMinClientNetworkFailure, ENetworkFailure::Type , const FString& );` — Delegate for passing back a network connection failure @param FailureType	The reason for the net failure @param ErrorString	More detailed error information
- L91 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnMinClientNetworkFailure, ENetworkFailure::Type , const FString& );` — Delegate for passing back a network connection failure @param FailureType	The reason for the net failure @param ErrorString	More detailed error information
- L98 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMinClientReceivedControlBunch, FInBunch& );` — Delegate for hooking the control channel's 'ReceivedBunch' call @param Bunch		The received bunch
- L98 _prototype_ `DECLARE_DELEGATE_OneParam(FOnMinClientReceivedControlBunch, FInBunch& );` — Delegate for hooking the control channel's 'ReceivedBunch' call @param Bunch		The received bunch
- L107 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMinClientReceivedRawPacket, void* , int32& );` — Delegate for hooking the net connections 'ReceivedRawPacket' @param Data		The data received @param Count		The number of bytes received
- L107 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnMinClientReceivedRawPacket, void* , int32& );` — Delegate for hooking the net connections 'ReceivedRawPacket' @param Data		The data received @param Count		The number of bytes received
- L116 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnMinClientRepActorSpawn, UClass* , bool , bool& );` — Delegate for notifying on (and optionally blocking) replicated actor creation @param ActorClass	The class of the actor being replicated @param bActorChannel	Whether or not this actor creation is from an actor channel @param bBlockActor	Whether or not to block creation of the actor (defaults to true)
- L116 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnMinClientRepActorSpawn, UClass* , bool , bool& );` — Delegate for notifying on (and optionally blocking) replicated actor creation @param ActorClass	The class of the actor being replicated @param bActorChannel	Whether or not this actor creation is from an actor channel @param bBlockActor	Whether or not to block creation of the actor (defaults to true)
- L124 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMinClientNetActor, UActorChannel* , AActor* );` — Delegate for notifying AFTER an actor channel actor has been created @param ActorChannel	The actor channel associated with the actor @param Actor			The actor that has just been created
- L124 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnMinClientNetActor, UActorChannel* , AActor* );` — Delegate for notifying AFTER an actor channel actor has been created @param ActorChannel	The actor channel associated with the actor @param Actor			The actor that has just been created
- L132 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnHandleClientPlayer, APlayerController* , UNetConnection* );` — Delegate for hooking the HandlerClientPlayer event @param PC			The PlayerController being initialized with the net connection @param Connection	The net connection the player is being initialized with
- L132 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnHandleClientPlayer, APlayerController* , UNetConnection* );` — Delegate for hooking the HandlerClientPlayer event @param PC			The PlayerController being initialized with the net connection @param Connection	The net connection the player is being initialized with
- L137 _delegate_ `DECLARE_DELEGATE(FOnRPCFailure);` — Delegate for notifying of failure during call of SendRPCChecked
- L137 _prototype_ `DECLARE_DELEGATE(FOnRPCFailure);` — Delegate for notifying of failure during call of SendRPCChecked

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/NUTActor.h` (Public)


#### enum `ENUTControlCommand`  
`enum class ENUTControlCommand : uint8`  
_L22-34_
- desc: @todo #JohnBDoc: Fully document individually
- L24 _public enumerator_ `Command_NoResult = 0`
- L25 _public enumerator_ `Command_SendResult = 1`
- L26 _public enumerator_ `CommandResult_Failed = 2`
- L27 _public enumerator_ `CommandResult_Success = 3`
- L28 _public enumerator_ `Ping = 4`
- L29 _public enumerator_ `Pong = 5`
- L30 _public enumerator_ `WatchEvent = 6`
- L31 _public enumerator_ `NotifyEvent = 7`
- L32 _public enumerator_ `Summon = 8`
- L33 _public enumerator_ `SuspendProcess = 9`

#### class `ANUTActor`  
`class ANUTActor : public AActor, public FSelfRegisteringExec`  
_L49-186_
- reflection: `UCLASS()`
- inherits: `AActor,FSelfRegisteringExec`
- L55 _private member_ `FName BeaconDriverName;` — The name of the beacon net driver
- L59 _public member_ `double LastAliveTime;` — The value of World.RealTimeSeconds as of the last time the client was marked as still alive
- L63 _public member_ `FExecuteOnServer TempDelegate;` — `UPROPERTY()` — A delegate property, used solely for converting strings to delegates
- L66 _public member_ `bool bMonitorForBeacon;` — Monitors for the creation of the beacon net driver, if -BeaconPort=x was specified on the commandline
- L69 _public prototype_ `virtual void PostActorCreated() override;`
- L71 _public prototype_ `virtual UNetConnection* GetNetConnection() const override;`
- L73 _public prototype_ `bool NotifyControlMessage(UNetConnection* Connection, uint8 MessageType, FInBunch& Bunch);`
- L75 _public prototype_ `static void NotifyPostLoadMap(UWorld* LoadedWorld);`
- L77 _public prototype_ `static bool VerifyEventWatcher();`
- L82 _public prototype_ `void HookNetDriver(UNetDriver* TargetNetDriver);` — Hooks control channel messages for the specified net driver
- L89 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L98 _public prototype_ `void Admin(FString Command);` — `UFUNCTION(exec)` — Executes a console command on the server @param Command	The command to be executed
- L101 _public prototype_ `void ServerAdmin(const FString& Command);` — `UFUNCTION(reliable, server, WithValidation)`
- L110 _public prototype_ `void UnitSeamlessTravel(FString Dest=TEXT(" "))` — `UFUNCTION(exec)` — Triggers seamless travel @param Dest	The travel destination
- L118 _public prototype_ `void UnitTravel(FString Dest=TEXT(" "))` — `UFUNCTION(exec)` — Triggers normal travel @param Dest	The travel destination
- L124 _public prototype_ `void NetFlush();` — `UFUNCTION(exec)` — Flushes all pending net connection packets
- L130 _public prototype_ `void Wait(uint16 Seconds);` — `UFUNCTION(exec)` — Makes the game thread wait for the specified number of seconds
- L137 _public prototype_ `void ServerClientStillAlive();` — `UFUNCTION(reliable, server, WithValidation)` — Notifies the server that the client is still around
- L145 _public prototype_ `void ServerReceiveText(const FText& InText);` — `UFUNCTION(reliable, server, WithValidation)` — Test log function @param InText	The FText passed from the client
- L152 _public prototype_ `void ServerClientPing();` — `UFUNCTION(reliable, server, WithValidation)` — Send a 'ping' RPC to all clients, to make them log a ping, which unit tests then use to verify the presence of a client process
- L160 _public prototype_ `void NetMulticastPing();` — `UFUNCTION(reliable, NetMulticast)` — @todo #JohnBRefactor: When the VM reflection helper is finished, remove NETCODEUNITTEST_API from this, and use reflection instead
- L169 _public prototype_ `void ExecuteOnServer(UObject* InTargetObj, FString InTargetFunc);` — Executes the function specified in the delegate, on the server (used within unit tests) @param InTargetObj	The object the target function is in (automatically resolve to the class default object) @param InTargetFunc	The function to be executed
- L177 _public prototype_ `void ServerExecute(const FString& InDelegate);` — `UFUNCTION(reliable, server, WithValidation)` — Takes a string representing a delegate (can't replicate delegate parameters), and executes that delegate on the server @param InDelegate	A string representing the delegate to be executed
- L180 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L185 _public prototype_ `void UpdateOwner();` — Update the owner for the NUTActor, if the current owner is no longer valid

#### Free symbols / members of external scopes

- L45 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FExecuteOnServer, ANUTActor*, InNUTActor);` — Delegate for executing a unit test function on the server @param InNUTActor	The serverside NUTActor triggering the delegate
- L45 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FExecuteOnServer, ANUTActor*, InNUTActor);` — Delegate for executing a unit test function on the server @param InNUTActor	The serverside NUTActor triggering the delegate

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/NUTGlobals.h` (Public)


#### class `UNUTGlobals`  
`class UNUTGlobals : public UObject`  
_L22-70_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Stores globals/static-variables for NetcodeUnitTest - for compatibility with hot reload
- L30 _public function_ `FORCEINLINE static UNUTGlobals& Get()` — Singleton
- L49 _public member_ `TObjectPtr<UNetConnection> EventWatcher;` — `UPROPERTY()` — For NUTActor - the UNetConnection that 'watch' events will be sent to
- L53 _public member_ `int32 ServerPortOffset;` — `UPROPERTY()` — For ClientUnitTest - the (+10) incremented port number, for each server instance
- L57 _public member_ `int32 UnitTestNetDriverCount;` — `UPROPERTY()` — For MinimalClient - counter for the number of unit test net drivers created
- L61 _public member_ `TArray<FString> DumpRPCMatches;` — `UPROPERTY()` — For the '-DumpRPCs' commandline parameter - limits DumpRPCs to RPC's (partially) matching the specified names
- L65 _public member_ `TArray<FString> UnitTestModules;` — `UPROPERTY()` — List of modules recognized as containing unit tests, plus implementing FNUTModuleInterface for hot reload
- L69 _public member_ `TArray<FString> UnloadedModules;` — `UPROPERTY()` — List of unit test modules that have been unloaded, prior to reloading for Hot Reload

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/Net/UnitTestActorChannel.h` (Public)


#### class `UUnitTestActorChannel`  
`class UUnitTestActorChannel : public UActorChannel`  
_L22-40_
- reflection: `UCLASS(transient)`
- inherits: `UActorChannel`
- desc: An actor net channel override, for hooking ReceivedBunch, to aid in detecting/blocking of remote actors, of a specific class
- L30 _public prototype_ `virtual void ReceivedBunch(FInBunch& Bunch) override;`
- L32 _public prototype_ `virtual void Tick() override;`
- L34 _public prototype_ `virtual void NotifyActorChannelOpen(AActor* InActor, FInBunch& InBunch) override;`
- L39 _private member_ `TObjectPtr<UMinimalClient> MinClient;` — `UPROPERTY()` — Cached referenced to the minimal client that owns this actor channel

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/Net/UnitTestChannel.h` (Public)


#### class `UUnitTestChannel`  
`class UUnitTestChannel : public UChannel`  
_L23-41_
- reflection: `UCLASS(transient)`
- inherits: `UChannel`
- desc: A net channel for overriding the implementation of traditional net channels, for e.g. blocking control channel messages, to enable minimal clients
- L27 _private prototype_ `virtual void Init(UNetConnection* InConnection, int32 InChIndex, EChannelCreateFlags CreateFlags) override;`
- L29 _private prototype_ `virtual void ReceivedBunch(FInBunch& Bunch) override;`
- L31 _private prototype_ `virtual void Tick() override;`
- L37 _public member_ `TObjectPtr<UMinimalClient> MinClient;` — `UPROPERTY()` — The minimal client which may require received bunch notifications
- L40 _public member_ `bool bVerifyOpen;` — Whether or not this channel should verify it has been opened (resends initial packets until acked, like control channel)

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/Net/UnitTestPackageMap.h` (Public)


#### class `UUnitTestPackageMap`  
`class UUnitTestPackageMap : public UPackageMapClient`  
_L37-63_
- reflection: `UCLASS(transient)`
- inherits: `UPackageMapClient`
- desc: Package map override, for blocking the creation of actor channels for specific actors (by detecting the actor class being created)
- L41 _private prototype_ `virtual bool SerializeObject(FArchive& Ar, UClass* InClass, UObject*& Obj, FNetworkGUID* OutNetGUID=nullptr) override;`
- L43 _private prototype_ `virtual bool SerializeName(FArchive& Ar, FName& InName) override;`
- L45 _private prototype_ `virtual bool SerializeNewActor(FArchive& Ar, class UActorChannel* Channel, class AActor*& Actor) override;`
- L50 _public member_ `TObjectPtr<UMinimalClient> MinClient;` — `UPROPERTY()` — Cached reference to the minimal client that owns this package map
- L53 _public member_ `bool bWithinSerializeNewActor;` — Whether or not we are currently within execution of SerializeNewActor
- L56 _public member_ `bool bPendingArchetypeSpawn;` — Whether or not SerializeNewActor is about to spawn an actor, from an archetype
- L59 _public member_ `TMap<UObject*, UObject*> ReplaceObjects;` — Map of objects to watch and replace, in SerializeObject
- L62 _public member_ `FOnSerializeName OnSerializeName;` — Delegate for hooking SerializeName

#### Free symbols / members of external scopes

- L30 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnSerializeName, bool , bool& , FArchive& , FName& );` — Delegate for hooking SerializeName @param bPreSerialize		Whether or not this call is occurring before or after serialization (it happens twice) @param bSerializedName	Whether or not the name has already been serialized @param Ar				The archive to serialize from/to @param InName			The name to serialize to/from
- L30 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnSerializeName, bool , bool& , FArchive& , FName& );` — Delegate for hooking SerializeName @param bPreSerialize		Whether or not this call is occurring before or after serialization (it happens twice) @param bSerializedName	Whether or not the name has already been serialized @param Ar				The archive to serialize from/to @param InName			The name to serialize to/from

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/ProcessUnitTest.h` (Public)


#### enum `EErrorLogStage`  
`enum class EErrorLogStage : uint8`  
_L19-26_
- desc: Enum for different stages of error log parsing (mainly applicable to Unreal Engine processes)
- L21 _public enumerator_ `ELS_NoError` — No error logs have been received/parsed yet
- L22 _public enumerator_ `ELS_ErrorStart` — The text indicating the start of an error log is being parsed
- L23 _public enumerator_ `ELS_ErrorDesc` — The text describing the error is being parsed
- L24 _public enumerator_ `ELS_ErrorCallstack` — The callstack for the error is being parsed
- L25 _public enumerator_ `ELS_ErrorExit` — The post-error exit message is being parsed (error parsing is effectively complete)

#### enum `ESuspendState`  
`enum class ESuspendState : uint8`  
_L31-35_
- desc: Enum for specifying the suspend state of a process (typically the server)
- L33 _public enumerator_ `Active` — Process is currently active/not-suspended
- L34 _public enumerator_ `Suspended` — Process is currently suspended

#### struct `FErrorLog`  
`struct FErrorLog`  
_L43-66_
- desc: Struct used for storing and classifying each log error line
- L46 _public member_ `EErrorLogStage Stage;` — The stage of this error log line
- L49 _public member_ `FString Line;` — The error log line
- L55 _public function_ `FErrorLog() : Stage(EErrorLogStage::ELS_NoError) , Line()` — Base constructor
- L61 _public function_ `FErrorLog(EErrorLogStage InStage, const FString& InLine) : Stage(InStage) , Line(InLine)`

#### struct `FUnitTestProcess`  
`struct FUnitTestProcess`  
_L71-137_
- desc: Struct used for handling a launched UE client/server process
- L76 _public member_ `FProcHandle ProcessHandle;` — Process handle for the launched process
- L79 _public member_ `uint32 ProcessID;` — The process ID
- L82 _public member_ `ESuspendState SuspendState;` — The suspend state of the process (implemented as a part of unit test code, does not relate to OS API)
- L85 _public member_ `FString ProcessTag;` — Human-readable tag given to this process. Processes should be given an easily distinguishable tag, to identify them in code.
- L89 _public member_ `void* ReadPipe;` — Handle to StdOut for the launched process
- L92 _public member_ `void* WritePipe;` — Handle to StdIn for the launched process (unused)
- L96 _public member_ `ELogType BaseLogType;` — The base log type for this process (client? server? process?)
- L99 _public member_ `FString LogPrefix;` — The prefix to use for StdOut log output
- L102 _public member_ `const TCHAR* MainLogColor;` — The OutputDeviceColor string, to use for setting the log output color
- L105 _public member_ `FSlateColor SlateLogColor;` — The log output color to use in the slate log window
- L108 _public member_ `bool bStripErrorLogs;` — Whether or not to strip Error logs for this process (e.g. for unit test servers, when we expect to crash)
- L112 _public member_ `EErrorLogStage ErrorLogStage;` — If this process is outputting an error log, this is the current stage of error parsing (or ELS_NoError if not parsing)
- L115 _public member_ `TArray<FErrorLog> ErrorText;` — Gathered error log text
- L121 _public function_ `FUnitTestProcess() : ProcessHandle() , ProcessID(0) , SuspendState(ESuspendState::Active) , ProcessTag(TEXT("")) , ReadPipe(NULL) , WritePipe(NULL) , BaseLogType(ELogType::None) , LogPrefix(TEXT("")) , MainLogColor(COLOR_NONE) , SlateLogColor(FSlateColor::UseForeground()) , bStripErrorLogs(false) , ErrorLogStage(EErrorLogStage::ELS_NoError) , ErrorText()` — Base constructor

#### class `UProcessUnitTest`  
`class UProcessUnitTest : public UUnitTest`  
_L166-303_
- reflection: `UCLASS(Abstract)`
- inherits: `UUnitTest`
- desc: Base class for all unit tests which launch child processes, whether they be UE child processes, or other arbitrary programs. Handles management of child processes, memory usage tracking, log/stdout output gathering/printing, and crash detection.
- L173 _protected member_ `TArray<TSharedPtr<FUnitTestProcess>> ActiveProcesses;` — Stores a reference to all running child processes tied to this unit test, for housekeeping
- L176 _protected member_ `double LastBlockingProcessCheck;` — Last time there was a check for processes blocking progress
- L180 _public member_ `FOnSuspendStateChange OnSuspendStateChange;` — Delegate for notifying the UI, of a change in the unit test suspend state
- L183 _public member_ `TArray<FProcessLogWatch> ProcessLogWatches;` — Delegates for implementing process log watches
- L198 _public prototype_ `virtual void NotifyProcessLog(TWeakPtr<FUnitTestProcess> InProcess, const TArray<FString>& InLogLines);` — For implementation in subclasses, for helping to verify success/fail upon completion of unit tests NOTE: Not called again once VerificationState is set WARNING: Be careful when iterating InLogLines in multiple different for loops, if the sequence of detected logs is important @param InProcess		The process the log lines are from @param InLogLines	The current log lines being received
- L203 _public function_ `virtual void NotifySuspendRequest()` — Notifies that there was a request to suspend/resume the unit test
- L213 _public prototype_ `virtual void NotifyProcessSuspendState(TWeakPtr<FUnitTestProcess> InProcess, ESuspendState InSuspendState);` — Notifies when the suspend state of a process changes @param InProcess			The process whose suspend state has changed @param InSuspendState	The new suspend state of the process
- L221 _public function_ `virtual void NotifyProcessFinished(TWeakPtr<FUnitTestProcess> InProcess)` — Notifies when a running process is detected as having finished/closed NOTE: This will not get called, when ShutdownUnitTestProcess is used, only when a program ends by itself @param InProcess		The process which has finished
- L235 _protected prototype_ `virtual TWeakPtr<FUnitTestProcess> StartUnitTestProcess(FString Path, FString InCommandline, bool bMinimized=true);` — Starts a child process, tied to the unit test @param Path				The path to the process executable @param InCommandline		The commandline that the child process should use @param bMinimized		Starts the process with the window minimized @return					Returns a pointer to the new processes handling struct
- L245 _protected prototype_ `virtual TWeakPtr<FUnitTestProcess> StartUEUnitTestProcess(FString InCommandline, bool bMinimized=true, EBuildTargetType Type=EBuildTargetType::Game);` — Starts a child UE process, tied to the unit test @param InCommandline		The commandline that the child process should use @param bMinimized		Starts the process with the window minimized @param Type				If we are not in Dev Editor mode, the Game/Server processes are separate - specify which here @return					Returns a pointer to the new processes handling struct
- L253 _protected prototype_ `virtual void ShutdownUnitTestProcess(TSharedPtr<FUnitTestProcess> InHandle);` — Shuts-down/cleans-up a child process tied to the unit test @param InHandle	The handling struct for the process
- L260 _protected prototype_ `virtual void PrintUnitTestProcessErrors(TSharedPtr<FUnitTestProcess> InHandle);` — If any errors logs were detected upon ShutdownUnitTestProcess, this is called to print them out @param InHandle	The handling struct for the process
- L265 _protected prototype_ `void PollProcessOutput();` — Processes the standard output (i.e. log output) for processes
- L270 _protected prototype_ `void UpdateProcessStats();` — Updates (and if necessary, saves) the memory stats for processes
- L278 _protected prototype_ `bool IsBlockingProcessPresent(bool bLogIfFound=false);` — Whether or not a child process indicating a long/blocking task is running @param bLogIfFound	Outputs a log to the unit test window, if a blocking process is found @return				Whether or not a blocking process was found
- L286 _protected prototype_ `virtual void CheckOutputForError(TSharedPtr<FUnitTestProcess> InProcess, const TArray<FString>& InLines);` — Checks incoming process logs, for any indication of a crash/error @param InProcess		The process the log output originates from @param InLines		The incoming log lines
- L290 _protected prototype_ `virtual void CleanupUnitTest(EUnitTestResetStage ResetStage) override;`
- L293 _protected prototype_ `virtual void UnitTick(float DeltaTime) override;`
- L295 _protected prototype_ `virtual void PostUnitTick(float DeltaTime) override;`
- L297 _protected prototype_ `virtual bool IsTickable() const override;`
- L300 _protected prototype_ `virtual void FinishDestroy() override;`
- L302 _protected prototype_ `virtual void ShutdownAfterError() override;`

#### Free symbols / members of external scopes

- L147 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSuspendStateChange, ESuspendState );` — Delegate notifying that a process suspend state has changed @param NewSuspendState	The new process suspend state
- L147 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSuspendStateChange, ESuspendState );` — Delegate notifying that a process suspend state has changed @param NewSuspendState	The new process suspend state
- L156 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FProcessLogWatch, TWeakPtr<FUnitTestProcess> , const TArray<FString>& );` — Delegate for implementing process log watches @param InProcess		The process the log originates from @param InLogLines	The list of log lines to be processed @return				Whether or not the log watch is finished - removes the watch delegate
- L156 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FProcessLogWatch, TWeakPtr<FUnitTestProcess> , const TArray<FString>& );` — Delegate for implementing process log watches @param InProcess		The process the log originates from @param InLogLines	The list of log lines to be processed @return				Whether or not the log watch is finished - removes the watch delegate

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/UnitTask.h` (Public)


#### enum `EUnitTaskFlags`  
`enum class EUnitTaskFlags : uint8`  
_L36-65_
- desc: Flags for specifying the required conditions for executing a UnitTask, and what stages of the unit test to block until completion
- L38 _public enumerator_ `None = 0x00` — No flags
- L41 _public enumerator_ `RequireServer = 0x01` — Requirement flags
- L42 _public enumerator_ `RequireMinClient = 0x02` — For ClientUnitTest, wait until the MinimalClient has successfully connected to the server
- L44 _public enumerator_ `RequirementsMask = RequireServer | RequireMinClient`
- L48 _public enumerator_ `BlockUnitTest = 0x04` — Flags for blocking unit test execution
- L49 _public enumerator_ `BlockMinClient = 0x08` — For ClientUnitTest, blocks the creation/connection of the MinimalClient
- L51 _public enumerator_ `BlockMask = BlockUnitTest | BlockMinClient`
- L54 _public enumerator_ `AlterMinClient = 0x10` — Flags for altering stages of unit test execution
- L58 _public enumerator_ `PriorityMask_One = None` — Masks for the sequence UnitTask's should run, with above flags (done like this, in case future flags share same priority)
- L59 _public enumerator_ `PriorityMask_Two = BlockUnitTest`
- L60 _public enumerator_ `PriorityMask_Three = RequireServer`
- L61 _public enumerator_ `PriorityMask_Four = BlockMinClient`
- L62 _public enumerator_ `PriorityMask_Five = AlterMinClient`
- L63 _public enumerator_ `PriorityMask_Six = RequireMinClient`
- L64 _public enumerator_ `PriorityMask_MAX = PriorityMask_Six`

#### class `UUnitTask`  
`class UUnitTask : public UObject, public FUnitLogRedirect`  
_L88-208_
- reflection: `UCLASS(abstract)`
- inherits: `UObject,FUnitLogRedirect`
- desc: UnitTask's are used to implement supporting code for UnitTest's, for handling complex behind-the-scenes setup prior to test execution (e.g. primarily for implementing game-specific server/client environment setup), which is shared between many unit tests, and which is better to abstract-away from visibility in unit tests themselves, for code clarity. For example, some games require authentication negotiation before the game client can connect to a server, and this is the type of task that UnitTask's are designed for. Unit tasks that are added to a unit test, must complete execution before the unit test itself can execute.
- L96 _protected member_ `EUnitTaskFlags UnitTaskFlags;` — Flags for configuring the UnitTask
- L100 _protected member_ `TObjectPtr<UUnitTest> Owner;` — `UPROPERTY()` — The UnitTest that owns this task
- L103 _protected member_ `bool bStarted;` — Whether or not the UnitTask has started
- L111 _public prototype_ `virtual void Attach(UUnitTest* InOwner);` — Attach the task to a unit test @param InOwner	The unit test that will own this task
- L116 _public prototype_ `virtual void ValidateUnitTaskSettings();` — After attaching to a unit test, validate the unit task settings are compatible
- L122 _public function_ `virtual void StartTask()` — Start executing the task
- L131 _public function_ `FORCEINLINE bool HasStarted()` — Whether or not the task has started @return	Whether or not the task has started
- L141 _public prototype_ `virtual bool IsTaskComplete() PURE_VIRTUAL(UUnitTask::IsTaskComplete, return false;);` — Whether or not the task has completed @return	Returns whether the task has completed or not
- L146 _public function_ `virtual void Cleanup()` — Cleanup the task state, after the task completes
- L156 _public function_ `virtual void NotifyAlterMinClient(FMinClientParms& Parms)` — Gives UnitTask's an opportunity to alter the MinimalClient setup parameters @param Parms		Reference to the MinimalClient parameters prior to setup/connection
- L165 _public prototype_ `void TriggerFailure(FString Reason);` — Triggers a failure for the UnitTask and owning UnitTest @param Reason	The reason for the failure (output to log)
- L170 _public prototype_ `virtual void ResetTimeout(FString ResetReason, bool bResetConnTimeout=false, uint32 MinDuration=0);` — See UUnitTest::ResetTimeout
- L178 _public function_ `FORCEINLINE EUnitTaskFlags GetUnitTaskFlags() const` — Retrieves UnitTaskFlags
- L191 _public function_ `virtual void UnitTick(float DeltaTime)` — Main tick function for the unit test @param DeltaTime		The time passed since the previous tick
- L199 _public function_ `virtual void NetTick()` — Tick function that runs at a tickrate of ~60 fps, for interacting with netcode (high UnitTick tickrate, can lead to net buffer overflows)
- L204 _public function_ `virtual bool IsTickable() const` — Must override in subclasses, that need ticking

#### Free symbols / members of external scopes

- L67 _prototype_ `ENUM_CLASS_FLAGS(EUnitTaskFlags);`
- L74 _prototype_ `int32 GetUnitTaskPriority(EUnitTaskFlags InFlags);` — Returns the numeric priority for the specified UnitTask flags @return	The priority for the specified UnitTask flags

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/UnitTest.h` (Public)


#### enum `EUnitTestVerification`  
`enum class EUnitTestVerification : uint8`  
_L37-49_
- reflection: `UENUM()`
- desc: The verification status of the current unit test - normally its execution completes immediately after positive/negative verification
- L40 _public enumerator_ `Unverified` — Unit test is not yet verified
- L42 _public enumerator_ `VerifiedNotFixed` — Unit test is verified as not fixed
- L44 _public enumerator_ `VerifiedFixed` — Unit test is verified as fixed
- L46 _public enumerator_ `VerifiedNeedsUpdate` — Unit test is no longer functioning, needs manual check/update (issue may be fixed, or unit test broken)
- L48 _public enumerator_ `VerifiedUnreliable` — Unit test is verified as having executed unreliably

#### enum `EUnitTestResetStage`  
`enum class EUnitTestResetStage : uint8`  
_L57-67_
- reflection: `UENUM()`
- desc: The different stages that unit tests can be reset to - a global/non-locally-customizable list, for now NOTE: Stages MUST be sequential! (e.g. ResetConnection implies ResetExecute, FullReset implies both ResetConnection and ResetExecute) NOTE: Apart from checking for 'None', all comparisons should be either <= or >=, to support potential enum additions
- L60 _public enumerator_ `None` — No reset stage
- L62 _public enumerator_ `FullReset` — Resets the entire unit test, allowing restart from the beginning
- L64 _public enumerator_ `ResetConnection` — For ClientUnitTest's, resets the net connection and minimal client - but not the server - allowing a restart from connecting
- L66 _public enumerator_ `ResetExecute` — Resets unit tests to the point prior to 'ExecuteUnitTest' - usually implemented individually per unit test

#### struct `FUnitStatusLog`  
`struct FUnitStatusLog`  
_L80-100_
- desc: Used for storing unit-test-specific logs, which are displayed in the status window (upon completion of unit testing, a final summary is printed using this data, but in a more-ordered/easier-to-read fashion)
- L83 _public member_ `ELogType LogType;` — The log type for this status log
- L86 _public member_ `FString LogLine;` — The log line
- L89 _public function_ `FUnitStatusLog() : LogType(ELogType::None) , LogLine(TEXT(""))`
- L95 _public function_ `FUnitStatusLog(ELogType InLogType, const FString& InLogLine) : LogType(InLogType) , LogLine(InLogLine)`

#### class `UUnitTest`  
`class UUnitTest : public UUnitTestBase`  
_L107-531_
- reflection: `UCLASS(Abstract, config=UnitTestStats)`
- inherits: `UUnitTestBase`
- desc: Base class for all unit tests
- L121 _protected member_ `FString UnitTestName;` — The name/command for this unit test (N.B. Must be set in class constructor)
- L124 _protected member_ `FString UnitTestType;` — The type of unit test this is (e.g. bug/exploit) (N.B. Must be set in class constructor)
- L127 _protected member_ `FDateTime UnitTestDate;` — The date this unit test was added to the project (for ordering in help command)
- L131 _protected member_ `TArray<FString> UnitTestBugTrackIDs;` — The bug tracking identifiers related to this unit test (e.g. TTP numbers)
- L134 _protected member_ `TArray<FString> UnitTestCLs;` — Source control changelists relevant to this unit test
- L138 _protected member_ `bool bWorkInProgress;` — Whether or not this unit test is a 'work in progress', and should not be included in automated tests
- L141 _protected member_ `bool bUnreliable;` — Whether or not this unit test is unreliable, i.e. prone to giving incorrect/unexpected results, requiring multiple runs
- L144 _protected member_ `bool bObsolete;` — Whether or not this unit test is obsolete - i.e. based on code no longer present in the game/engine
- L151 _protected member_ `TMap<FString, EUnitTestVerification> ExpectedResult;` — The unit test result we expect for each games codebase, i.e. whether we expect that the problem is fixed yet or not NOTE: Games which don't have an expected result specified here, are considered 'unsupported' and the unit test isn't run for them
- L155 _protected member_ `uint32 UnitTestTimeout;` — The amount of time (in seconds), before the unit test should timeout and be marked as broken
- L162 _public member_ `uint64 PeakMemoryUsage;` — `UPROPERTY(config)` — Stores stats on the highest-ever reported memory usage, for this unit test - for estimating memory usage
- L166 _public member_ `float TimeToPeakMem;` — `UPROPERTY(config)` — The amount of time it takes to reach 'PeakMemoryUsage' (or within 90% of its value)
- L170 _public member_ `float LastExecutionTime;` — `UPROPERTY(config)` — The amount of time it took to execute the unit test the last time it was run
- L177 _protected member_ `static FUnitTestEnvironment* UnitEnv;` — The unit test environment (not set until the current games unit test module is loaded - not set at all, if no such module)
- L180 _protected member_ `static FUnitTestEnvironment* NullUnitEnv;` — The null unit test environment - for unit tests which support all games, due to requiring no game-specific features
- L184 _protected member_ `double LastNetTick;` — The time of the last NetTick event
- L187 _protected member_ `uint64 CurrentMemoryUsage;` — The current realtime memory usage of the unit test
- L191 _protected member_ `double StartTime;` — The time at which execution of the unit test started
- L195 _protected member_ `double TimeoutExpire;` — The time at which the unit test timeout will expire
- L198 _protected member_ `double LastTimeoutReset;` — The last time that the unit test timeout was reset
- L201 _protected member_ `FString LastTimeoutResetEvent;` — Every timeout reset specifies a string to identify/describe the event that triggered it, for tracking
- L204 _protected member_ `bool bDeveloperMode;` — Whether or not developer-mode has been enabled for this unit test (prevents it from ending execution)
- L208 _protected member_ `bool bFirstTimeStats;` — Whether it's the first time this unit test has run, i.e. whether prior memory stats exist (NOTE: Not set until first tick)
- L213 _protected member_ `TArray<TObjectPtr<UUnitTask>> UnitTasks;` — `UPROPERTY()` — UnitTask's which must be run before different stages of the unit test can execute
- L216 _protected member_ `EUnitTaskFlags UnitTaskState;` — Marks the state of met unit task requirement flags and active unit task blocking flags
- L221 _protected member_ `bool bCompleted;` — Whether or not the unit test has completed
- L225 _protected member_ `EUnitTestVerification VerificationState;` — `UPROPERTY()` — Whether or not the success or failure of the current unit test has been verified
- L229 _private member_ `bool bVerificationLogged;` — Whether or not the verification state was already logged (prevent spamming in developer mode)
- L233 _protected member_ `bool bAborted;` — Whether or not the unit test has aborted execution
- L237 _protected member_ `TSharedPtr<SLogWindow> LogWindow;` — The log window associated with this unit test
- L240 _protected member_ `TArray<TSharedPtr<FUnitStatusLog>> StatusLogSummary;` — Collects unit test status logs, that have been printed to the summary window
- L244 _protected member_ `TUniquePtr<FOutputDeviceFile> UnitLog;` — The log file for outputting all log information for the current unit test
- L247 _protected member_ `FString UnitLogDir;` — The log directory for this unit test
- L254 _public function_ `FORCEINLINE FString GetUnitTestName() const` — Returns the name/command, for the current unit test
- L262 _public function_ `FORCEINLINE FString GetUnitTestType() const` — Returns the type of unit test (e.g. bug/exploit)
- L270 _public function_ `FORCEINLINE FDateTime GetUnitTestDate() const` — Returns the date this unit test was first added to the code
- L278 _public function_ `FORCEINLINE uint32 GetUnitTestTimeout() const` — Returns the value of UnitTestTimeout
- L286 _public function_ `FORCEINLINE EUnitTestVerification GetExpectedResult()` — Returns the expected result for the current game
- L307 _public function_ `FORCEINLINE TArray<FString> GetSupportedGames()` — Returns the list of supported games, for this unit test
- L320 _public function_ `FORCEINLINE bool IsFirstTimeStats() const` — Returns whether or not this is the first time the unit test has been run/collecting-stats
- L330 _protected function_ `virtual void InitializeEnvironmentSettings()` — Finishes initializing unit test settings, that rely upon the current unit test environment being loaded
- L341 _protected prototype_ `virtual bool ValidateUnitTestSettings(bool bCDOCheck=false);` — Validate that the unit test settings/flags specified for this unit test, are compatible with one another, and that the engine settings/environment, support running the unit test. @param bCDOCheck		If true, the class default object is being validated before running - don't check class runtime variables @return				Returns true, if all settings etc. check out
- L349 _protected function_ `virtual ELogType GetExpectedLogTypes()` — Returns the type of log entries that this unit expects to output, for setting up log window filters (only needs to return values which affect what tabs are shown) @return		The log type mask, representing the type of log entries this unit test expects to output
- L361 _protected function_ `virtual void ResetTimeout(FString ResetReason, bool bResetConnTimeout=false, uint32 MinDuration=0)` — Resets the unit test timeout code - should be used liberally, within every unit test, when progress is made during execution @param ResetReason			Human-readable reason for resetting the timeout @param bResetConnTimeout		Whether or not to also reset timeouts on unit test connections @param MinDuration			The minimum timeout duration (used in subclasses, to override the timeout duration)
- L373 _protected prototype_ `virtual bool UTStartUnitTest() override final;`
- L378 _protected prototype_ `void InitializeLogs();` — Sets up the log directory and log output device instances.
- L386 _protected function_ `FORCEINLINE bool IsTaskBlocking(EUnitTaskFlags InFlag)` — Determines whether or not a UnitTask is blocking the specified event @return	Whether or not the specified event is being blocked by a UnitTask
- L409 _protected prototype_ `virtual void UnblockEvents(EUnitTaskFlags ReadyEvents);` — When events that were pending but blocked by a UnitTask, are unblocked, this function triggers them. @param ReadyEvents	Blocked events that are ready to be unblocked/triggered
- L417 _protected prototype_ `virtual void NotifyUnitTaskFailure(UUnitTask* InTask, FString Reason);` — Triggered when a UnitTask fails unrecoverably during execution @param InTask	The UnitTask that failed @param Reason	The reason for the failure
- L425 _public function_ `FORCEINLINE bool HasStarted()` — Whether or not the unit test has started @return	Whether or not the unit test has started
- L435 _public prototype_ `void AddTask(UUnitTask* InTask);` — Adds a UnitTask to the unit test, during its configuration stage - to be completed before executing the unit test @param InTask	The task to be added (must already have its flags etc. set)
- L443 _public prototype_ `virtual bool ExecuteUnitTest() PURE_VIRTUAL(UUnitTest::ExecuteUnitTest, return false;) void AbortUnitTest();` — Executes the main unit test @return	Whether or not the unit test kicked off execution successfully
- L454 _public prototype_ `void EndUnitTest();` — Called upon completion of the unit test (may not happen during same tick), for tearing down created worlds/connections/etc. NOTE: Should be called last, in overridden functions, as this triggers deletion of the unit test object
- L461 _public prototype_ `virtual void CleanupUnitTest(EUnitTestResetStage ResetStage=EUnitTestResetStage::None);` — Cleans up all items needing destruction, and removes the unit test from tracking, before deleting the unit test itself @param ResetStage	If called from ResetUnitTest, restricts what is cleaned up based on the current reset stage
- L470 _public prototype_ `void ResetUnitTest(EUnitTestResetStage ResetStage=EUnitTestResetStage::FullReset);` — Resets the unit test to its initial state, allowing it to restart from scratch NOTE: Must be implemented for every unit test that intends to support it, through CleanupUnitTest @param ResetStage	If specified, only partially resets the unit test state, to allow replaying only a portion of the unit test
- L475 _public function_ `virtual bool CanResetUnitTest()` — Whether or not this unit test supports resetting
- L481 _public prototype_ `virtual void NotifyLocalLog(ELogType InLogType, const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category) override;`
- L484 _public prototype_ `virtual void NotifyStatusLog(ELogType InLogType, const TCHAR* Data) override;`
- L486 _public prototype_ `virtual bool IsConnectionLogSource(UNetConnection* InConnection) override;`
- L488 _public prototype_ `virtual bool IsTimerLogSource(UObject* InTimerDelegateObject) override;`
- L496 _public prototype_ `void NotifyDeveloperModeRequest(bool bInDeveloperMode);` — Notifies that there was a request to enable/disable developer mode @param bInDeveloperMode	Whether or not developer mode is being enabled/disabled
- L506 _public prototype_ `virtual bool NotifyConsoleCommandRequest(FString CommandContext, FString Command);` — Notifies that there was a request to execute a console command for the unit test, which can occur in a specific context, e.g. for a unit test server, for a local minimal-client (within the unit test), or for a separate unit test client process @param CommandContext	The context (local/server/client?) for the console command @param Command			The command to be executed @return					Whether or not the command was handled
- L514 _public prototype_ `virtual void GetCommandContextList(TArray<TSharedPtr<FString>>& OutList, FString& OutDefaultContext);` — Outputs the list of console command contexts, that this unit test supports (which can include custom contexts in subclasses) @param OutList				Outputs the list of supported console command contexts @param OutDefaultContext		Outputs the context which should be auto-selected/defaulted-to
- L517 _public prototype_ `virtual void UnitTick(float DeltaTime) override;`
- L519 _public prototype_ `virtual void NetTick() override;`
- L521 _public prototype_ `virtual void PostUnitTick(float DeltaTime) override;`
- L523 _public prototype_ `virtual bool IsTickable() const override;`
- L525 _public prototype_ `virtual void TickIsComplete(float DeltaTime) override;`
- L530 _public prototype_ `virtual void LogComplete();` — Triggered upon unit test completion, for outputting that the unit test has completed - plus other unit test state information

#### Free symbols / members of external scopes

- L69 _prototype_ `FString GetUnitTestResetStageName(EUnitTestResetStage Stage);`

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/UnitTestBase.h` (Public)


#### class `UUnitTestBase`  
`class UUnitTestBase : public UObject, public FUnitLogInterface`  
_L20-75_
- reflection: `UCLASS(abstract)`
- inherits: `UObject,FUnitLogInterface`
- desc: Base class for the unit test framework event implementation (all engine/external-triggered events are wrapped, in order to hook logs triggered during their execution) NOTE: All wrapped functions/events, begin with 'UT'
- L30 _public prototype_ `bool StartUnitTest();` — Adds the unit test to tracking, and starts it @return	Whether or not the unit test was started successfully
- L32 _public prototype_ `virtual bool UTStartUnitTest() PURE_VIRTUAL(UUnitTestBase::UTStartUnitTest, return false;);`
- L40 _public function_ `virtual void UnitTick(float DeltaTime)` — Main tick function for the unit test @param DeltaTime		The time passed since the previous tick
- L48 _public function_ `virtual void NetTick()` — Tick function that runs at a tickrate of ~60 fps, for interacting with netcode (high UnitTick tickrate, can lead to net buffer overflows)
- L57 _public function_ `virtual void PostUnitTick(float DeltaTime)` — For cleanup actions that should occur after the primary tick function is called @param DeltaTime		The time passed since the previous tick
- L66 _public function_ `virtual void TickIsComplete(float DeltaTime)` — Tick function for checking if the unit test is completed (happens after all above tick events) @param DeltaTime		The time passed since the previous tick
- L71 _public function_ `virtual bool IsTickable() const` — Must override in subclasses, that need ticking

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/UnitTestCommandlet.h` (Public)


#### class `UUnitTestCommandlet`  
`class UUnitTestCommandlet : public UCommandlet`  
_L38-46_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: A commandlet for running unit tests, without having to launch the game client. Uses a heavily stripped down game client, with allowances for Slate, and some hacks for enabling proper netcode usage. Usage: "UnrealEditor.exe shootergame -run=NetcodeUnitTest.UnitTestCommandlet" Parameters: -UnitTest=UnitTestName - Launches only the specified unit test -UnitTestNoAutoClose - Sets the default option for the 'AutoClose' button to False -UnitTestServerParms="CommandlineParameters" - Adds additional commandline parameters to unit test server instances (useful for e.g. unsuppressing specific logs) -UnitTestClientParms="CommandlineParameters" - Adds additional commandline parameters to unit test client instances -UnitTestClientDebug - Launches unit test clients with a valid render interface (so you can interact with the client window), and a larger window -UnitTestCap=x - Caps the maximum number of unit tests that can run at the same time
- L43 _public prototype_ `virtual int32 Main(const FString& Params) override;`
- L45 _public prototype_ `virtual void CreateCustomEngine(const FString& Params) override;`

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/UnitTestManager.h` (Public)


#### class `UUnitTestManager`  
`class UUnitTestManager : public UObject, public FTickableGameObject, public FOutputDevice`  
_L26-341_
- reflection: `UCLASS(config=UnitTest)`
- inherits: `UObject,FTickableGameObject,FOutputDevice`
- desc: Manages centralized execution and tracking of unit tests, as well as handling console commands, and some misc tasks like local log hooking
- L35 _public member_ `bool bCapUnitTestCount;` — `UPROPERTY(config)` — Whether or not to cap the maximum number of unit tests that can be active at any given time
- L39 _public member_ `uint8 MaxUnitTestCount;` — `UPROPERTY(config)` — Specifies the maximum number of unit tests that can be run at any given time
- L44 _public member_ `bool bCapUnitTestMemory;` — `UPROPERTY(config)` — Whether or not to cap active unit tests, based on memory usage
- L50 _public member_ `uint8 MaxMemoryPercent;` — `UPROPERTY(config)` — When total physical memory usage, as a percentage, reaches this limit, no new unit tests can be started
- L54 _public member_ `uint8 AutoCloseMemoryPercent;` — `UPROPERTY(config)` — As above, but when reaching this limit, recently started unit test(s) will be terminated/re-queued, to get back within limits
- L58 _public member_ `uint8 MaxAutoCloseCount;` — `UPROPERTY(config)` — Limits the number of auto-aborts a particular unit test will allow, before it is no longer accepted for re-queueing
- L63 _public member_ `uint32 UnitTestSessionCount;` — `UPROPERTY(config)` — The number of recorded sessions where UE has run unit tests (max one per each run of the UE process)
- L68 _public member_ `TArray<TObjectPtr<UClass>> PendingUnitTests;` — `UPROPERTY()` — Holds a list of unit tests pending execution
- L72 _public member_ `TArray<TObjectPtr<UUnitTest>> ActiveUnitTests;` — `UPROPERTY()` — Holds a list of currently active unit tests
- L76 _public member_ `TArray<TObjectPtr<UUnitTest>> FinishedUnitTests;` — `UPROPERTY()` — Unit tests which are finished, and are kept around until printing the final summary
- L80 _public member_ `bool bAbortedFirstRunUnitTest;` — If a unit test was aborted on its first run, strictly cap all first-run unit tests to one at a time
- L83 _public member_ `bool bAllowRequeuingUnitTests;` — Whether or not to allow re-queuing of unit tests
- L88 _private member_ `FLogWindowManager* LogWindowManager;` — The log window manager - used for creating and managing the positioning of unit test log windows
- L91 _private member_ `bool bStatusLog;` — Whether the current log line being written, is a status log or not (used to toggle Serialize function between modes)
- L94 _private member_ `FSlateColor StatusColor;` — The colour to use for the current status log
- L97 _private member_ `TMap<TSharedRef<SWindow>, UUnitTest*> DialogWindows;` — Maps open dialog boxes, to unit tests
- L101 _public member_ `TSharedPtr<SLogWindow> StatusWindow;` — The log window which displays the overall status of unit testing
- L104 _public member_ `TSharedPtr<SWindow> AbortAllDialog;` — The 'abort all' dialog
- L108 _public member_ `TUniquePtr<FOutputDeviceFile> StatusLog;` — The log file for outputting overall unit test status
- L113 _private member_ `FString BaseUnitLogDir;` — The base log directory used by unit tests, for this session
- L116 _private member_ `double LastMemoryLimitHit;` — The time at which the memory limit was last hit
- L119 _private member_ `int32 MemoryTickCountdown;` — When a unit test is force-closed, wait a number of ticks for global memory values to update, before closing any more
- L122 _private member_ `SIZE_T MemoryUsageUponCountdown;` — When waiting for restart of unit test auto-closing, note the system memory usage, and end the countdown early if it increases
- L130 _public prototype_ `static UUnitTestManager* Get();` — Static getter for the unit test manager @return	Returns the unit test manager
- L135 _public prototype_ `void Initialize();` — Initialize the unit test manager
- L140 _public prototype_ `void InitializeLogs();` — Initialize unit test log output
- L145 _public function_ `FORCEINLINE const FString GetBaseUnitLogDir()` — Returns the base log directory used by unit tests
- L163 _public prototype_ `bool QueueUnitTest(UClass* UnitTestClass, bool bRequeued=false);` — Queues a unit test for execution @param UnitTestClass	The unit test class to be queued @param bRequeued		Whether the unit test being queued, was aborted and is now being requeued @return				Whether or not queueing was successful
- L168 _public prototype_ `void PollUnitTestQueue();` — Checks to see if we're ready to execute any unit tests in the queue, and if so, begins execution
- L177 _public prototype_ `bool WithinUnitTestLimits(UClass* PendingUnitTest=NULL);` — Tests whether currently active unit tests, and optionally/additionally, a unit test about to be executed, fall within limits/restrictions on unit test counts and memory usage @param PendingUnitTest	Optionally specify a unit test pending execution, to estimate and factor in its resource usage @return					Returns true if within limits, and false if not
- L182 _public function_ `bool IsRunningUnitTests()` — Returns whether or not there are unit tests running (or about to be run)
- L194 _public prototype_ `void NotifyUnitTestComplete(UUnitTest* InUnitTest, bool bAborted);` — Notification that is triggered when a unit test completes @param InUnitTest	The unit test that just completed @param bAborted		Whether or not the unit test was aborted
- L201 _public prototype_ `void NotifyUnitTestCleanup(UUnitTest* InUnitTest);` — Notification that is triggered when a unit test is cleaning up @param InUnitTest	The unit test that is cleaning up
- L208 _public prototype_ `void NotifyLogWindowClosed(const TSharedRef<SWindow>& ClosedWindow);` — Notifies when a log window has closed @param ClosedWindow	The log window that has closed
- L219 _public prototype_ `void NotifyCloseDialogResult(const TSharedRef<SWindow>& DialogWindow, EAppReturnType::Type Result, bool bNoResult);` — When a log window is closed, a dialog pops up asking if the unit test should be aborted - this returns the result NOTE: This dialog is non-modal, i.e. doesn't block the game thread - so the unit test is not guaranteed to still exist @param DialogWindow	The dialog window the result is coming from @param Result		The result (yes/no) for the dialog @param bNoResult		Whether or not the result is invalid, e.g. the dialog was closed instead of a button clicked
- L229 _public prototype_ `void NotifyCloseAllDialogResult(const TSharedRef<SWindow>& DialogWindow, EAppReturnType::Type Result, bool bNoResult);` — When the main status window is closed, a dialog pops up asking if you want to abort all running unit tests; this returns the result @param DialogWindow	The dialog window the result is coming from @param Result		The result (yes/no) for the dialog @param bNoResult		Whether or not the result is invalid, e.g. the dialog was closed instead of a button clicked
- L237 _public prototype_ `void DumpStatus(bool bForce=false);` — Dumps status information for running/pending unit tests, to the status window and log @param bForce	Forces a stats dump
- L246 _public prototype_ `void PrintUnitTestResult(UUnitTest* InUnitTest, bool bFinalSummary=false, bool bUnfinished=false);` — Prints the results information for a single unit test @param InUnitTest		The unit test to print results information for @param bFinalSummary		Whether or not this is the final summary printout (changes the formatting slightly) @param bUnfinished		Whether or not the unit test was aborted and could not be run
- L251 _public prototype_ `void PrintFinalSummary();` — Prints the final unit test summary, when all active/pending unit tests have completed
- L259 _public prototype_ `void OpenUnitTestLogWindow(UUnitTest* InUnitTest);` — Opens the log window, for a unit test @param InUnitTest	The unit test associated with the log window
- L264 _public prototype_ `void OpenStatusWindow();` — Opens the status log window
- L271 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L274 _public function_ `virtual bool IsTickable() const override` — Must override in subclasses, that need ticking
- L280 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L285 _public function_ `virtual TStatId GetStatId() const override`
- L299 _public prototype_ `bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);` — Handles exec commands starting with 'UnitTest' @param InWorld	The world the command was executed from @param Cmd		The command that was executed @param Ar		The archive log results should be sent to @return			True if the command was handled, false if not
- L317 _public prototype_ `virtual void Serialize(const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category) override;` — Write text to the console @param Data		The text to write @param Verbosity	The log level verbosity for the message @param Category	The log category for the message
- L327 _public function_ `FORCEINLINE void SetStatusLog(bool bInStatusLog)`
- L332 _public function_ `FORCEINLINE void SetStatusColor(FSlateColor InStatusColor=GetDefaultStatusColor())`
- L337 _public function_ `static FORCEINLINE FSlateColor GetDefaultStatusColor()`

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/UnitTests/Engine/IPClient.h` (Public)


#### class `UIPClient`  
`class UIPClient : public UClientUnitTest`  
_L17-38_
- reflection: `UCLASS()`
- inherits: `UClientUnitTest`
- desc: Basic unit test for launching a server and connecting a client, while verifying that the correct net driver was used, and that the client connected successfully.
- L23 _protected member_ `const TCHAR* NetDriverLog;` — Log message identifying the expected net driver
- L27 _private member_ `const TCHAR* ConnectSuccessMsg;` — Log message triggered upon successful connect
- L30 _private member_ `bool bDetectedNetDriver;` — Whether or not the correct net driver was detected
- L33 _public prototype_ `virtual void InitializeEnvironmentSettings() override;`
- L35 _public prototype_ `virtual void ExecuteClientUnitTest() override;`
- L37 _public prototype_ `virtual void NotifyProcessLog(TWeakPtr<FUnitTestProcess> InProcess, const TArray<FString>& InLogLines) override;`

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/UnitTests/Engine/PackedVectorTest.h` (Public)


#### class `UPackedVectorTest`  
`class UPackedVectorTest : public UUnitTest`  
_L16-28_
- reflection: `UCLASS()`
- inherits: `UUnitTest`
- desc: Basic unit test for WritePackedValue and ReadPackedValue
- L21 _private prototype_ `virtual bool ExecuteUnitTest() override;`
- L23 _private prototype_ `bool ExecuteFloatTest(TMap<FString,bool>& TestResults);`
- L24 _private prototype_ `bool ExecuteDoubleTest(TMap<FString,bool>& TestResults);`
- L25 _private prototype_ `bool ExecuteWriteDoubleReadFloatTest(TMap<FString,bool>& TestResults);`
- L26 _private prototype_ `bool ExecuteWriteFloatReadDoubleTest(TMap<FString,bool>& TestResults);`
- L27 _private prototype_ `void VerifyTestResults(const TMap<FString,bool>& TestResults);`

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/UnitTests/Engine/SteamClient.h` (Public)


#### class `USteamClient`  
`class USteamClient : public UIPClient`  
_L13-36_
- reflection: `UCLASS()`
- inherits: `UIPClient`
- desc: Basic unit test for verifying simple client connection to a server, using the Steam net driver.
- L19 _protected member_ `FString ServerSteamAddress;` — The server Steam address, parsed from the server log
- L22 _protected member_ `bool bPendingConnect;` — Whether or not ConnectMinimalClient is pending
- L25 _protected prototype_ `virtual bool ValidateUnitTestSettings(bool bCDOCheck) override;`
- L27 _protected prototype_ `virtual void InitializeEnvironmentSettings() override;`
- L29 _protected prototype_ `virtual FString ConstructServerParameters() override;`
- L31 _protected prototype_ `virtual bool ConnectMinimalClient(const TCHAR* InNetID=nullptr) override;`
- L33 _protected prototype_ `virtual void NotifyAlterMinClient(FMinClientParms& Parms) override;`
- L35 _protected prototype_ `virtual void NotifyProcessLog(TWeakPtr<FUnitTestProcess> InProcess, const TArray<FString>& InLogLines) override;`

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/UnitTests/Engine/WebSocketClient.h` (Public)


#### class `UWebSocketClient`  
`class UWebSocketClient : public UIPClient`  
_L13-21_
- reflection: `UCLASS()`
- inherits: `UIPClient`
- desc: Basic unit test for verifying simple client connection to a server, using the WebSocket net driver.
- L18 _protected prototype_ `virtual void InitializeEnvironmentSettings() override;`
- L20 _protected prototype_ `virtual void NotifyAlterMinClient(FMinClientParms& Parms) override;`

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/UnitTests/VMReflection.h` (Public)


#### class `UVMReflection`  
`class UVMReflection : public UUnitTest`  
_L21-27_
- reflection: `UCLASS()`
- inherits: `UUnitTest`
- desc: Internal unit test for verifying the functionality of the UScript/BP VM reflection helper
- L26 _public prototype_ `virtual bool ExecuteUnitTest() override;`

#### class `UVMTestClassA`  
`class UVMTestClassA : public UObject`  
_L34-163_
- reflection: `UCLASS()`
- inherits: `UObject`
- L40 _public member_ `TObjectPtr<UObject> AObjectRef;` — `UPROPERTY()`
- L43 _public member_ `uint8 ByteProp;` — `UPROPERTY()`
- L46 _public member_ `uint16 UInt16Prop;` — `UPROPERTY()`
- L49 _public member_ `uint32 UInt32Prop;` — `UPROPERTY()`
- L52 _public member_ `uint64 UInt64Prop;` — `UPROPERTY()`
- L55 _public member_ `int8 Int8Prop;` — `UPROPERTY()`
- L58 _public member_ `int16 Int16Prop;` — `UPROPERTY()`
- L61 _public member_ `int32 Int32Prop;` — `UPROPERTY()`
- L64 _public member_ `int64 Int64Prop;` — `UPROPERTY()`
- L67 _public member_ `float FloatProp;` — `UPROPERTY()`
- L70 _public member_ `double DoubleProp;` — `UPROPERTY()`
- L73 _public member_ `bool bBoolPropA;` — `UPROPERTY()`
- L76 _public member_ `bool bBoolPropB;` — `UPROPERTY()`
- L79 _public member_ `bool bBoolPropC;` — `UPROPERTY()`
- L82 _public member_ `bool bBoolPropD;` — `UPROPERTY()`
- L85 _public member_ `bool bBoolPropE;` — `UPROPERTY()`
- L88 _public member_ `FName NameProp;` — `UPROPERTY()`
- L91 _public member_ `FString StringProp;` — `UPROPERTY()`
- L94 _public member_ `FText TextProp;` — `UPROPERTY()`
- L98 _public member_ `uint8 BytePropArray[4];` — `UPROPERTY()`
- L101 _public member_ `TObjectPtr<UObject> ObjectPropArray[2];` — `UPROPERTY()`
- L104 _public member_ `TArray<uint8> DynBytePropArray;` — `UPROPERTY()`
- L107 _public member_ `TArray<bool> DynBoolPropArray;` — `UPROPERTY()`
- L110 _public member_ `TArray<TObjectPtr<UObject>> DynObjectPropArray;` — `UPROPERTY()`
- L113 _public member_ `TArray<FName> DynNamePropArray;` — `UPROPERTY()`
- L116 _public member_ `TArray<double> DynDoublePropArray;` — `UPROPERTY()`
- L119 _public member_ `TArray<float> DynFloatPropArray;` — `UPROPERTY()`
- L122 _public member_ `TArray<int16> DynInt16PropArray;` — `UPROPERTY()`
- L125 _public member_ `TArray<int64> DynInt64PropArray;` — `UPROPERTY()`
- L128 _public member_ `TArray<int8> DynInt8PropArray;` — `UPROPERTY()`
- L131 _public member_ `TArray<int32> DynIntPropArray;` — `UPROPERTY()`
- L134 _public member_ `TArray<uint16> DynUInt16PropArray;` — `UPROPERTY()`
- L137 _public member_ `TArray<uint32> DynUIntPropArray;` — `UPROPERTY()`
- L140 _public member_ `TArray<uint64> DynUInt64PropArray;` — `UPROPERTY()`
- L143 _public member_ `TArray<FString> DynStringPropArray;` — `UPROPERTY()`
- L146 _public member_ `TArray<FText> DynTextPropArray;` — `UPROPERTY()`
- L149 _public member_ `TArray<TObjectPtr<UClass>> DynClassPropArray;` — `UPROPERTY()`
- L152 _public member_ `TArray<TObjectPtr<APawn>> DynPawnPropArray;` — `UPROPERTY()`
- L156 _public member_ `FVector StructProp;` — `UPROPERTY()`
- L159 _public member_ `FVector StructPropArray[2];` — `UPROPERTY()`
- L162 _public member_ `TArray<FVector> DynStructPropArray;` — `UPROPERTY()`

#### class `UVMTestClassB`  
`class UVMTestClassB : public UObject`  
_L166-173_
- reflection: `UCLASS()`
- inherits: `UObject`
- L172 _public member_ `TObjectPtr<UObject> BObjectRef;` — `UPROPERTY()`

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/INetcodeUnitTest.h` (Public)


#### class `FNUTModuleInterface`  
`class FNUTModuleInterface : public IModuleInterface`  
_L13-41_
- inherits: `IModuleInterface`
- desc: Module interface that plugins containing unit tests should use - to support hot reload properly
- L19 _private function_ `FNUTModuleInterface() : ModuleName(nullptr)` — Hide the default constructor, to force specification of module name
- L28 _public function_ `FNUTModuleInterface(const TCHAR* InModuleName) : ModuleName(InModuleName)` — Constructor which forces specification of the module name
- L33 _public prototype_ `virtual void StartupModule() override;`
- L35 _public prototype_ `virtual void ShutdownModule() override;`
- L40 _private member_ `const TCHAR* ModuleName;` — The name of the module, specified by subclass

#### class `INetcodeUnitTest`  
`class INetcodeUnitTest : public FNUTModuleInterface`  
_L47-64_
- inherits: `FNUTModuleInterface`
- desc: Public interface for the NetcodeUnitTest module
- L50 _public function_ `INetcodeUnitTest() : FNUTModuleInterface(TEXT("NetcodeUnitTest"))`
- L55 _public function_ `static inline INetcodeUnitTest& Get()`
- L60 _public function_ `static inline bool IsAvailable()`

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/NUTEnum.h` (Public)


#### enum `EMinClientFlags`  
`enum class EMinClientFlags : uint32`  
_L15-36_
- reflection: `UENUM()`
- desc: Flags for configuring the minimal client, what parts of the netcode should be enabled etc.
- L17 _public enumerator_ `None = 0x00000000` — No flags
- L20 _public enumerator_ `AcceptActors = 0x00000001` — Minimal-client netcode functionality
- L21 _public enumerator_ `AcceptRPCs = 0x00000002` — Whether or not to accept execution of any actor RPC's (they are all blocked by default)
- L22 _public enumerator_ `SendRPCs = 0x00000004` — Whether or not to allow RPC sending (NOT blocked by default, @todo JohnB: Add send hook)
- L23 _public enumerator_ `AcceptRepNotifies = 0x00000008` — Whether or not to accept execution of RepNotify's on Actors (blocked by default)
- L24 _public enumerator_ `SkipControlJoin = 0x00000010` — Whether or not to skip sending NMT_Join upon connect (or NMT_BeaconJoin for beacons)
- L25 _public enumerator_ `BeaconConnect = 0x00000020` — Whether or not to connect to the servers beacon (greatly limits the connection)
- L28 _public enumerator_ `NotifyNetActors = 0x00000100` — Minimal-client events
- L29 _public enumerator_ `NotifyProcessNetEvent = 0x00000200` — Whether or not to trigger 'NotifyProcessNetEvent' for every client RPC function
- L32 _public enumerator_ `DumpReceivedRaw = 0x00001000` — Debugging
- L33 _public enumerator_ `DumpSendRaw = 0x00002000` — Whether or not to also hex-dump the raw packet sends to the log/log-window
- L34 _public enumerator_ `DumpReceivedRPC = 0x00004000` — Whether or not to dump RPC receives (with LogNetTraffic, detects ProcessEvent RPC fail)
- L35 _public enumerator_ `DumpSendRPC = 0x00008000` — Whether or not to dump RPC sends

#### enum `EUnitTestFlags`  
`enum class EUnitTestFlags : uint32`  
_L58-98_
- desc: Flags for configuring how individual unit tests make use of the base client unit test framework. NOTE: There is crossover between these flags, and EMinClientFlags. Types of things these flags control: - Types of remote data which are accepted/denied (channel types, actors, RPC's) - IMPORTANT: This includes local setup of e.g. actor channels, and possibly execution of RPC's in local context, which risks undefined behaviour (which is why it is disabled by default - you have to know what you're doing) - The prerequisites needed before executing the unit test (need a valid PlayerController? A particular actor?) - Whether or not a server or another client is automatically launched - Enabling other miscellaneous events, such as capturing raw packet data for debugging
- L60 _public enumerator_ `None = 0x00000000` — No flags
- L63 _public enumerator_ `LaunchServer = 0x00000001` — Sub-process flags
- L64 _public enumerator_ `LaunchClient = 0x00000002` — Whether or not to automatically launch a full game client, which connects to the server
- L67 _public enumerator_ `AcceptPlayerController = 0x00000004` — Minimal-client netcode functionality
- L68 _public enumerator_ `BeaconConnect = 0x00000008` — Whether or not to connect to the servers beacon (greatly limits the connection)
- L69 _public enumerator_ `AutoReconnect = 0x00000010` — Whether or not to auto-reconnect on server disconnect (NOTE: Won't catch all disconnects)
- L72 _public enumerator_ `RequirePlayerController = 0x00000100` — Unit test state-setup/requirements/prerequisites
- L73 _public enumerator_ `RequirePawn = 0x00000200` — Whether or not to wait for PlayerController's pawn, before ExecuteClientUnitTest
- L74 _public enumerator_ `RequirePlayerState = 0x00000400` — Whether or not to wait for PlayerController's PlayerState, before ExecuteClientUnitTest
- L75 _public enumerator_ `RequirePing = 0x00000800` — Whether or not to wait for a ping round-trip, before triggering ExecuteClientUnitTest
- L76 _public enumerator_ `RequireNUTActor = 0x00001000` — Whether or not to wait for the NUTActor, before triggering ExecuteClientUnitTest
- L77 _public enumerator_ `RequireBeacon = 0x00002000` — Whether or not to wait for beacon replication, before triggering ExecuteClientUnitTest
- L78 _public enumerator_ `RequireCustom = 0x00004000` — Whether or not ExecuteClientUnitTest will be executed manually, within the unit test
- L80 _public enumerator_ `RequirementsMask = RequirePlayerController | RequirePawn | RequirePlayerState | RequirePing | RequireNUTActor | RequireBeacon | RequireCustom`
- L84 _public enumerator_ `ExpectServerCrash = 0x00100000` — Unit test error/crash detection
- L85 _public enumerator_ `ExpectDisconnect = 0x00200000` — Whether or not this unit test will intentionally trigger a disconnect from the server
- L88 _public enumerator_ `IgnoreServerCrash = 0x00400000` — Unit test error/crash detection debugging (NOTE: Don't use these in finalized unit tests, unit tests must handle all errors)
- L89 _public enumerator_ `IgnoreClientCrash = 0x00800000` — Whether or not client crashes should be treated as a unit test failure
- L90 _public enumerator_ `IgnoreDisconnect = 0x01000000` — Whether or not MinimalClient disconnects, should be treated as a unit test failure
- L93 _public enumerator_ `NotifyProcessEvent = 0x02000000` — Unit test events
- L96 _public enumerator_ `CaptureReceivedRaw = 0x04000000` — Debugging
- L97 _public enumerator_ `DumpControlMessages = 0x08000000` — Whether or not to dump control channel messages, and their raw hex content

#### Free symbols / members of external scopes

- L39 _prototype_ `ENUM_CLASS_FLAGS(EMinClientFlags);` — Required for bitwise operations with the above enum
- L101 _prototype_ `ENUM_CLASS_FLAGS(EUnitTestFlags);` — Required for bitwise operations with the above enum
- L107 _prototype_ `FString GetUnitTestFlagName(EUnitTestFlags Flag);` — Used to get name values for the above enum
- L112 _prototype_ `EMinClientFlags FromUnitTestFlags(EUnitTestFlags Flags);` — Converts any EUnitTestFlags values, to their EMinClientFlags equivalent
- L126 _function_ `template<EMinClientFlags CompileTimeFlags=EMinClientFlags::None> EMinClientFlags ValidateMinFlags(EMinClientFlags RuntimeFlags=EMinClientFlags::None)` — Validates, both at compile time (template param) or at runtime (function param), that the specified EMinClientFlags flags are valid. When specifying the whole flag list in one assignment, do a compile time check using the template parameter. When modifying a runtime-written flag list, do a runtime check on the final flag variable using the function parameter. @param CompileTimeFlags	The compile-time flag list to be checked @param RuntimeFlags		The runtime flag list to be checked @return					Returns the flags, so that validation can be done as they are assigned to a value
- L129 _macro_ `#define FLAG_ASSERT(Condition, Message) \` — Implements the 'MinClientFlags' variable within 'Condition', for both static/compile-time checks, and runtime checks

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/NUTUtil.h` (Public)


#### class `FDynamicOutputDevice`  
`class FDynamicOutputDevice : public FOutputDevice`  
_L26-59_
- inherits: `FOutputDevice`
- desc: Output device for allowing quick/dynamic creation of a customized output device, using lambda's passed to delegates
- L29 _public function_ `FDynamicOutputDevice()`
- L33 _public function_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override`
- L38 _public function_ `virtual void Flush() override`
- L43 _public function_ `virtual void TearDown() override`
- L49 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSerialize, const TCHAR*, ELogVerbosity::Type, const FName&);`
- L51 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnFlushOrTearDown);`
- L54 _public member_ `FOnSerialize OnSerialize;`
- L56 _public member_ `FOnFlushOrTearDown OnFlush;`
- L58 _public member_ `FOnFlushOrTearDown OnTearDown;`

#### class `FHookOutputDevice`  
`class FHookOutputDevice : public FOutputDeviceError`  
_L65-156_
- inherits: `FOutputDeviceError`
- desc: Output device for hijacking/hooking an existing output device (e.g. to hijack GError, to block specific asserts) Inherit this class, to implement desired hook behaviour in subclass
- L68 _public function_ `FHookOutputDevice() : OriginalDevice(nullptr)`
- L73 _public function_ `void HookDevice(FOutputDeviceError* OldDevice)`
- L80 _public function_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category) override`
- L88 _public function_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category, const double Time) override`
- L96 _public function_ `virtual void Flush() override`
- L104 _public function_ `virtual void TearDown() override`
- L112 _public function_ `virtual void Dump(class FArchive& Ar) override`
- L120 _public function_ `virtual bool IsMemoryOnly() const override`
- L132 _public function_ `virtual bool CanBeUsedOnAnyThread() const override`
- L144 _public function_ `virtual void HandleError() override`
- L155 _private member_ `FOutputDeviceError* OriginalDevice;` — The original output device

#### class `FAssertHookDevice`  
`class FAssertHookDevice : public FHookOutputDevice`  
_L162-214_
- inherits: `FHookOutputDevice`
- desc: Output device for replacing GError, and catching specific asserts so they don't crash the game.
- L165 _public function_ `FAssertHookDevice()`
- L172 _public prototype_ `static void AddAssertHook(FString Assert);` — Adds a string to the list of disabled asserts - does a partial match when watching for the disabled assert
- L174 _public function_ `FORCEINLINE bool IsAssertDisabled(const TCHAR* V)`
- L195 _public function_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category) override`
- L203 _public function_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category, const double Time) override`
- L213 _public member_ `TArray<FString> DisabledAsserts;` — List of disabled asserts

#### struct `AccessPrivate`  
`template<typename Accessor, typename Accessor::Member Member> struct AccessPrivate`  
_L220-226_
- desc: This template, is used to link an arbitrary class member, to the GetPrivate function

#### struct `NUTUtil`  
`struct NUTUtil`  
_L358-601_
- desc: General utility functions
- L365 _public function_ `static inline UNetDriver* GetActiveNetDriver(UWorld* InWorld)` — Returns the currently active net driver (either pending or one for current level) @return	The active net driver
- L382 _public function_ `static inline UWorld* GetPrimaryWorld()`
- L408 _public prototype_ `static void GetUnitTestClassDefList(TArray<UUnitTest*>& OutUnitTestClassDefaults);` — Outputs a full list of valid unit test class defaults, representing all unit tests which can be executed @param OutUnitTestClassDefaults	The array that unit test class defaults should be output to
- L415 _public prototype_ `static void SortUnitTestClassDefList(TArray<UUnitTest*>& InUnitTestClassDefaults);` — Takes a list of unit test class defaults, and reorders them in a more readable way, based on type and implementation date @param InUnitTestClassDefaults	The array of unit test class defaults to reorder
- L421 _public function_ `static bool ParseValue(const TCHAR* Stream, const TCHAR* Match, TCHAR* Value, int32 MaxLen, bool bShouldStopOnComma=true)` — Overridden parse function, for supporting escaped quotes, e.g: -UnitTestServerParms="-LogCmds=\"LogNet all\""
- L552 _public function_ `static bool ParseValue(const TCHAR* Stream, const TCHAR* Match, FString& Value, bool bShouldStopOnComma=true)` — Overridden parse function, for supporting escaped quotes
- L575 _public prototype_ `static bool ParseEnum(const TCHAR* Stream, const TCHAR* Match, const TCHAR* EnumName, uint64& Value);` — Parses the value of specific enum, from the specified commandline stream @param Stream	The stream to parse from (typically FCommandline::Get()) @param Match		The commandline option to match as the key specifying the value @param EnumName	The name of the enum type @param Value		Outputs the integer value of the enum, as specified on the commandline @return			Whether or not an enum value was parsed successfully
- L590 _public prototype_ `static void SpecialLog(FOutputDeviceFile* Ar, const TCHAR* SpecialCategory, const TCHAR* Data, ELogVerbosity::Type Verbosity, const FName& Category);` — Puts out a log message to FOutputDeviceFile, with a special category prefix added. For example: [2017.02.27-15.09.15:999][  0][SpecialCategory]LogUnitTest: LogMessage @param Ar				The FOutputDeviceFile archive to write to @param SpecialCategory	The special category prefix to be added to the log message @param Data				The log message @param Verbosity			The verbosity of the log message @param Category			The category of the log message
- L600 _public prototype_ `static FString GetPackageModule(UPackage* Package, bool bVerifyModule=true);` — Get a module name from any UPackage - if it has one @param Package			The package to be linked to a module @param bVerifyModule		Whether or not to verify that the module is loaded (specify false, when using with Hot Reload code) @return					The name of the module

#### Free symbols / members of external scopes

- L49 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSerialize, const TCHAR*, ELogVerbosity::Type, const FName&);`
- L51 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnFlushOrTearDown);`
- L222 _function_ `friend typename Accessor::Member GetPrivate(Accessor InAccessor)`
- L267 _macro_ `#define IMPLEMENT_GET_PRIVATE_VAR(InClass, VarName, VarType) \` — Defines a class and template specialization, for a variable, needed for use with the GET_PRIVATE hook below @param InClass		The class being accessed (not a string, just the class, i.e. FStackTracker) @param VarName		Name of the variable being accessed (again, not a string) @param VarType		The type of the variable being accessed
- L313 _macro_ `#define GET_PRIVATE(InClass, InObj, MemberName) (*InObj).*GetPrivate(InClass##MemberName##Accessor())` — A macro for tidying up accessing of private members, through the above code @param InClass		The class being accessed (not a string, just the class, i.e. FStackTracker) @param InObj			Pointer to an instance of the specified class @param MemberName	Name of the member being accessed (again, not a string) @return				The value of the member
- L318 _macro_ `#define GET_PRIVATE_REF(InClass, InObj, MemberName) GET_PRIVATE(InClass, InObj, MemberName)` — Redundant version of the above, for emphasizing the ability to assign a writable reference which can modify the original value
- L338 _macro_ `#define IMPLEMENT_GET_PROTECTED_FUNC_CONST(InClass, FuncName, FuncRet, FuncParms, FuncParmNames, FuncModifier) \` — Defines a class used for hack-accessing protected functions, through the CALL_PROTECTED macro below @param InClass		The class being accessed (not a string, just the class, i.e. FStackTracker) @param FuncName		Name of the function being accessed (again, not a string) @param FuncRet		The return type of the function @param FuncParms		The function parameters @param FuncParmNames	The names of the function parameters, as passed from one function to another @param FuncModifier	(Optional) Modifier placed after the function - usually 'const'
- L347 _macro_ `#define IMPLEMENT_GET_PROTECTED_FUNC(InClass, FuncName, FuncRet, FuncParms, FuncParmNames) \`
- L351 _macro_ `#define CALL_PROTECTED(InClass, InObj, MemberName) ((InClass##MemberName##Accessor*)&(*InObj))->MemberName##Accessor` — Version of GET_PRIVATE, for calling protected functions

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/NUTUtilDebug.h` (Public)


#### class `FScopedLog`  
`class FScopedLog`  
_L87-141_
- desc: A class for enabling verbose log message categories, within a particular code scope (disabled when going out of scope). NOTE: If you are logging any kind of net-related log messages, specify a unit test (even if you aren't doing remote logging) Also supports remote (server) logging, for net functions executed within the current code scope (causes net packets to be flushed both upon entering the current scope, and when exiting it - required for correct log timing). NOTE: If you are trying to catch remote log messages deep within the internal game netcode, then this class may not be appropriate, as remote logging passes through the netcode (YMMV)
- L90 _protected function_ `FScopedLog() : LogCategories() , UnitTest(nullptr) , bRemoteLogging(false) , bSuppressLogging(false)`
- L106 _public function_ `FORCEINLINE FScopedLog(const TArray<FString>& InLogCategories, UClientUnitTest* InUnitTest=nullptr, bool bInRemoteLogging=false) : FScopedLog()` — Constructor used for setting up the type of logging that is done. @param InLogCategories	The list of log categories to be enabled @param InUnitTest		When tracking netcode-related logs, or doing remote logging, specify the client unit test here @param bInRemoteLogging	Whether or not to enable logging on the remote server
- L113 _public function_ `FORCEINLINE FScopedLog(const FString InLogCategory, UClientUnitTest* InUnitTest=nullptr, bool bInRemoteLogging=false) : FScopedLog()` — As above, but for a single log category
- L123 _protected prototype_ `void InternalConstruct(const TArray<FString>& InLogCategories, UClientUnitTest* InUnitTest, bool bInRemoteLogging);`
- L126 _public prototype_ `~FScopedLog();`
- L131 _protected member_ `TArray<FString> LogCategories;` — The list of unsuppressed log messages
- L134 _protected member_ `UClientUnitTest* UnitTest;` — Stores a reference to the unit test doing the logging, if specified
- L137 _protected member_ `bool bRemoteLogging;` — Whether or not this is also controlling remote logging as well
- L140 _protected member_ `bool bSuppressLogging;` — Whether or not to suppress instead of enable logging

#### class `FScopedLogSuppress`  
`class FScopedLogSuppress : public FScopedLog`  
_L146-168_
- inherits: `FScopedLog`
- desc: Version of FScopedLog, for suppressing instead of enabling log entries
- L149 _public function_ `FORCEINLINE FScopedLogSuppress(const TArray<FString>& InLogCategories, UClientUnitTest* InUnitTest=nullptr, bool bInRemoteLogging=false) : FScopedLog()`
- L158 _public function_ `FORCEINLINE FScopedLogSuppress(const FString InLogCategory, UClientUnitTest* InUnitTest=nullptr, bool bInRemoteLogging=false) : FScopedLog()`

#### class `FScopedLogNet`  
`class FScopedLogNet : public FScopedLog`  
_L173-193_
- inherits: `FScopedLog`
- desc: Version of FScopedLog, for scoped logging of all netcode-related logs
- L176 _public function_ `FORCEINLINE FScopedLogNet(UClientUnitTest* InUnitTest, bool bInRemoteLogging=false)`

#### class `FNUTStackTrace`  
`class FNUTStackTrace`  
_L255-317_
- desc: A class for dumping a stack trace, upon encountering a specific piece of code
- L266 _public prototype_ `FNUTStackTrace(FString InTraceName);` — Constructs the debug stack trace @param InTraceName	A human readable trace name for logging/debugging/tracking
- L271 _public prototype_ `~FNUTStackTrace();` — Destructor
- L277 _public prototype_ `void Enable();` — Enable stack tracking
- L282 _public prototype_ `void Disable();` — Disable stack tracking (past traces are still kept in tracking, but no new ones are added until re-enabled)
- L289 _public prototype_ `void AddTrace(bool bLogAdd=false);` — Adds a new trace to the stack tracker (optionally dumping to log at the same time) @param bLogAdd	Whether or not to also log this new trace being added
- L296 _public prototype_ `void Dump(bool bKeepTraceHistory=false);` — Dumps accumulated stack traces @param bKeepTraceHistory		Whether or not to keep the trace history after dumping it (defaults to false)
- L302 _public function_ `FORCEINLINE bool IsTrackingEnabled()` — Whether or not the stack tracker, is currently tracking
- L309 _protected member_ `FString TraceName;` — The human-readable name to provide for this stack trace
- L312 _protected member_ `FStackTracker Tracker;` — The stack tracker associated with this debug trace
- L316 _private member_ `int32 IgnoreDepthOffset;` — Additional increment for the stack trace ignore depth, as set by FScopedIncrementTraceIgnoreDepth

#### class `FStackTraceManager`  
`class FStackTraceManager`  
_L333-468_
- desc: Manager for handling multiple debug stack traces on-the-fly, and allowing abstraction of stack traces, so you don't have to manually handle FNUTStackTrace objects (which can be complicated/bug-prone). This is a more intuitive way of handling tracing, you just use a call to 'GTraceManager->AddTrace' wherever needed, and add calls to 'Enable'/'Disable' whenever you want to accept/ignore AddTrace calls - then 'Dump' to see the results. No messing with managing instances of above objects. This also hooks into console commands as well, allowing it to be used throughout the engine, instead of depending on this module. See the documentation for the 'StackTrace' command in UnitTestManager.cpp.
- L341 _public prototype_ `FStackTraceManager();` — Base constructor
- L346 _public prototype_ `~FStackTraceManager();` — Destructor
- L354 _public prototype_ `void Enable(FString TraceName);` — Passes on an 'Enable' call, to the specified stack trace @param TraceName		The name of the trace
- L361 _public prototype_ `void Disable(FString TraceName);` — Passes on a 'Disable' call, to the specified stack trace (if it exists) @param TraceName		The name of the trace
- L370 _public prototype_ `void AddTrace(FString TraceName, bool bLogAdd=false, bool bDump=false, bool bStartDisabled=false);` — Adds a new stack trace, to the specified trace, optionally logging/dumping in the process @param TraceName			The name of the trace @param bDump				Whether or not to dump the trace as well (does not remove trace from tracking, unlike 'Dump' function) @param bStartDisabled	Whether or not this trace should start as disabled, until 'Enable' is called for it
- L379 _public prototype_ `void Dump(FString TraceName, bool bKeepTraceHistory=false, bool bKeepTracking=true);` — Dumps accumulated stack traces, and removes from tracking (unless otherwise specified) @param TraceName				The name of the trace @param bKeepTraceHistory		Whether or not to keep the trace history after dumping it (defaults to false) @param bKeepTracking			Whether or not to keep on tracking this particular trace name (defaults to true)
- L386 _public prototype_ `void Clear(FString TraceName);` — Clears the specified trace from tracking @param TraceName		The name of the trace
- L394 _public prototype_ `void DumpAll(bool bKeepTraceHistory=false, bool bKeepTracking=true);` — Dumps accumulated stack traces, for all tracked traces @param bKeepTraceHistory		Whether or not to keep the trace history after dumping (defaults to false) @param bKeepTracking			Whether or not to keep on tracking dumped traces (defaults to true)
- L403 _public prototype_ `void TraceAndDump(FString TraceName);` — Performs a once-off stack trace, with no tracking (but if there is already a trace active with this name, respect its 'enabled' status) @param TraceName		The name of the trace
- L411 _public function_ `FORCEINLINE bool ContainsTrace(FString TraceName)` — Whether or not a trace of this name is present @param TraceName		The name of the trace
- L423 _protected function_ `FORCEINLINE FNUTStackTrace* GetTrace(FString TraceName)` — Gets the trace of the specified name, or NULL if it doesn't exist @param TraceName		The name of the trace @return				The trace or NULL if it doesn't exist
- L436 _protected function_ `FORCEINLINE FNUTStackTrace* GetOrCreateTrace(FString TraceName, bool* bOutNewTrace=NULL)` — Gets or creates a trace, of the specified name @param TraceName		The name of the trace @param bOutNewTrace	Optionally, specifies whether this trace is newly created
- L463 _protected member_ `TMap<FString, FNUTStackTrace*> Traces;` — A map of active debug stack traces
- L467 _private member_ `int32 IgnoreDepthOffset;` — Additional increment for the stack trace ignore depth, as set by FScopedIncrementTraceIgnoreDepth

#### class `UE::NUT::FScopedIncrementTraceIgnoreDepth`  
`class FScopedIncrementTraceIgnoreDepth final`  
_L477-494_
- desc: Used for adjusting the depth of ignore stack trace lines in FStackTraceManager
- L486 _public prototype_ `FScopedIncrementTraceIgnoreDepth(FStackTraceManager* InManager, int32 InIgnoreIncrement);` — Base constructor @param InManager				The stack trace manager whose ignore depth is being adjusted @param InIgnoreIncrement		The amount by which the stack trace managers ignore deoth should be incremented
- L488 _public prototype_ `~FScopedIncrementTraceIgnoreDepth();`
- L491 _private member_ `FStackTraceManager* Manager = nullptr;`
- L493 _private member_ `int32 IgnoreIncrement = 0;`

#### enum `UE::NUT::ELogHookType`  
`enum class ELogHookType : uint8`  
_L499-503_
- desc: Specifies the type of log hook (e.g. type of string matching to use)
- L501 _public enumerator_ `Full = 0x0001` — Full string match against log line (excluding category and verbosity level)
- L502 _public enumerator_ `Partial = 0x0002` — Partial string match against log line

#### class `UE::NUT::FLogHookManager`  
`class FLogHookManager final : protected FOutputDevice`  
_L514-584_
- inherits: `FOutputDevice`
- desc: Generic log hook, for calling a hook function upon detecting a specific log entry
- L533 _public prototype_ `FLogHookManager() = default;`
- L545 _public prototype_ `FLogHookID AddLogHook(FLogHook&& InHookFunc, FString InMatchStr, ELogHookType InHookType=ELogHookType::Partial);` — Adds a log hook, with the specified matching @param InHookFunc	The log hook function to call upon match @param InMatchStr	The string to use for matching against log entries @param InHookType	The type of matching to use for the match string @return				Returns a unique id for the newly added log hook entry, which should be used to remove it later
- L552 _public prototype_ `void RemoveLogHook(FLogHookID InHookID);` — Removes a log hook using its unique id @param InHookID		The unique id for the log hook entry
- L566 _private prototype_ `virtual void Serialize(const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category) override;` — Detects log entries @param Data		The text to write @param Verbosity	The log level verbosity for the message @param Category	The log category for the message
- L571 _private prototype_ `void EnableLogHook();`
- L573 _private prototype_ `void DisableLogHook();`
- L577 _private member_ `TArray<FLogHookEntry> LogHooks;` — List of active log hooks
- L580 _private member_ `FLogHookID NextHookID = 0;` — Incrementing log hook ID
- L583 _private member_ `bool bWithinLogSerialize = false;` — Guard bool for preventing recursive calls to Serialize

#### struct `UE::NUT::FLogHookManager::FLogHookEntry`  
`struct FLogHookEntry`  
_L517-530_
- L520 _public member_ `FLogHook HookFunc;` — The log hook function to execute
- L523 _public member_ `FString LogMatch;` — The log string to match on
- L526 _public member_ `ELogHookType HookType;` — Flags specifying how to match against the log line
- L529 _public member_ `FLogHookID HookID;` — Simple ID for identifying the entry later

#### class `UE::NUT::FLogTraceManager`  
`class FLogTraceManager final`  
_L591-632_
- desc: A log hook, which watches the log for specified log entries, and ties them into the stack trace manager Most easily used through the LogTrace console command, as documented in UnitTestManager.cpp
- L594 _public prototype_ `FLogTraceManager() = default;`
- L596 _public prototype_ `~FLogTraceManager();`
- L606 _public prototype_ `void AddLogTrace(FString LogLine, ELogTraceFlags TraceFlags);` — Adds a log line for log trace tracking NOTE: The LogLine does NOT match the category or verbosity (e.g. LogNet or Warning/Verbose) of logs NOTE: Partial matches, will output to log when encountered, so matched logs can be identified @param LogLine		The line to be tracked @param TraceFlags	Flags for the type of trace to perform
- L614 _public prototype_ `void ClearLogTrace(FString LogLine, bool bDump=true);` — Removes a log line from trace tracking @param LogLine	The log line that was being tracked @param bDump		Whether or not to dump from the trace manager as well (defaults to true); cleared from trace manager either way
- L621 _public prototype_ `void ClearAll(bool bDump=false);` — Clears all log tracing @param bDump		Whether or not to dump all cleared log trace entries
- L624 _private prototype_ `void ClearHooks();`
- L628 _private member_ `TArray<FLogHookID> HookIDs;` — Active log hook ID's, for later cleanup
- L631 _private member_ `TMap<FString, FLogHookID> HookMap;` — Active log matching strings and their ID, for tracking and cleanup

#### class `UE::NUT::FLogCommandManager`  
`class FLogCommandManager final`  
_L639-679_
- desc: Log hook which executes console commands upon detecting certain log entries. Used by the LogCommand console command and commandline parameters.
- L642 _public prototype_ `FLogCommandManager() = default;`
- L644 _public prototype_ `~FLogCommandManager();`
- L652 _public prototype_ `void AddLogCommand(FString LogLine, FString Command);` — Adds a new log command @param LogLine	The log line to do a partial match on @param Command	The console command to execute
- L659 _public prototype_ `void RemoveByLog(FString LogLine);` — Removes a log command based on the log line used for matching @param LogLine	The log line used for matching
- L664 _public prototype_ `void RemoveByCommand(FString Command);` — Removes a log command based on the console command it executes
- L667 _private prototype_ `void ClearHooks();`
- L678 _private member_ `TArray<FLogCommandEntry> LogCommands;`

#### struct `UE::NUT::FLogCommandManager::FLogCommandEntry`  
`struct FLogCommandEntry`  
_L671-676_
- L673 _public member_ `FString LogLine;`
- L674 _public member_ `FString Command;`
- L675 _public member_ `FLogHookID HookID = INDEX_NONE;`

#### enum `ELogTraceFlags`  
`enum class ELogTraceFlags : uint16`  
_L687-693_
- desc: Flags specifying the type of log trace
- L689 _public enumerator_ `Full = 0x0001` — Full string match log trace (excluding category and verbosity level)
- L690 _public enumerator_ `Partial = 0x0002` — Partial string match log trace
- L691 _public enumerator_ `DumpTrace = 0x0004` — Dump a stack trace every time there's a match
- L692 _public enumerator_ `Debug = 0x0008` — Start debugging on match (if debugger attached)

#### class `FLogStackTraceManager`  
`class UE_DEPRECATED(5.1, "FLogStackTraceManager is deprecated, use FLogTraceManager/GLogTrace now, instead.") FLogStackTraceManager : public FOutputDevice`  
_L703-796_
- inherits: `FOutputDevice`
- desc: A log hook, which watches the log for specified log entries, and ties them into the stack trace manager Most easily used through the LogTrace console command, as documented in UnitTestManager.cpp
- L720 _public prototype_ `FLogStackTraceManager() = default;`
- L734 _public function_ `void AddLogTrace(FString LogLine, bool bPartial=true, bool bDump=true)` — `UE_DEPRECATED(5.1, "Use AddLogTrace with ELogTraceFlags now, instead.")` — Adds a log line for log trace tracking NOTE: The LogLine does NOT match the category or verbosity (e.g. LogNet or Warning/Verbose) of logs NOTE: Partial matches, will output to log when encountered, so matched logs can be identified @param LogLine	The line to be tracked @param bPartial	Whether or not to do partial matches for this line (case insensitive, and matches substrings) @param bDump		Whether or not to dump traces as they are encountered
- L754 _public prototype_ `void AddLogTrace(FString LogLine, ELogTraceFlags TraceFlags);` — Adds a log line for log trace tracking NOTE: The LogLine does NOT match the category or verbosity (e.g. LogNet or Warning/Verbose) of logs NOTE: Partial matches, will output to log when encountered, so matched logs can be identified @param LogLine		The line to be tracked @param TraceFlags	Flags for the type of trace to perform
- L762 _public prototype_ `void ClearLogTrace(FString LogLine, bool bDump=true);` — Removes a log line from trace tracking @param LogLine	The log line that was being tracked @param bDump		Whether or not to dump from the trace manager as well (defaults to true); cleared from trace manager either way
- L769 _public prototype_ `void ClearAll(bool bDump=false);` — Clears all log tracing @param bDump		Whether or not to dump all cleared log trace entries
- L784 _public prototype_ `virtual void Serialize(const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category) override;` — Detects log entries @param Data		The text to write @param Verbosity	The log level verbosity for the message @param Category	The log category for the message
- L792 _public member_ `TArray<FLogTraceEntry> ExactMatches;` — List of exact log entries to watch for
- L795 _public member_ `TArray<FLogTraceEntry> PartialMatches;` — List of partial log entries to watch for

#### struct `FLogStackTraceManager::FLogTraceEntry`  
`struct FLogTraceEntry`  
_L710-717_
- desc: Log trace entry
- L713 _public member_ `FString LogLine;` — The log line being to watch for
- L716 _public member_ `ELogTraceFlags TraceFlags;` — Flags specifying the type of log trace

#### struct `NUTDebug`  
`struct NUTDebug`  
_L828-1016_
- desc: General debug functions
- L841 _public function_ `static inline void StringToBytes(const FString& InString, TArray<uint8>& OutBytes)` — Quick conversion of a string to a hex-dumpable byte array @param InString		The string to convert @param OutBytes		The byte array to output to
- L866 _public prototype_ `static FString HexDump(const TArray<uint8>& InBytes, bool bDumpASCII=true, bool bDumpOffset=true);` — Takes an array of bytes, and generates a hex dump string out of them, optionally including an ASCII dump and dumping byte offsets also (intended for debugging in the log window) @param InBytes		The array of bytes to be dumped @param bDumpASCII	Whether or not to dump ASCII along with the hex @param bDumpOffset	Whether or not to dump offset margins for hex rows/columns @return				Returns the hex dump, including line terminators
- L871 _public function_ `static inline FString HexDump(const uint8* InBytes, const uint32 InBytesLen, bool bDumpASCII=true, bool bDumpOffset=true)` — Version of the above hex-dump function, which takes a byte pointer and length as input
- L884 _public function_ `static inline FString HexDump(const FString& InString, bool bDumpASCII=true, bool bDumpOffset=false)` — Version of the above hex-dump function, which takes a string as input
- L897 _public function_ `static inline void LogHexDump(const TArray<uint8>& InBytes, bool bDumpASCII=true, bool bDumpOffset=false, FOutputDevice* OutLog=GLog)` — Version of the above hex-dump function, which dumps in a format more friendly/readable in log text files
- L914 _public function_ `static inline void LogHexDump(const uint8* InBytes, const uint32 InBytesLen, bool bDumpASCII=true, bool bDumpOffset=false, FOutputDevice* OutLog=GLog)` — Version of the above hex-dump logging function, which takes a byte pointer and length as input
- L928 _public function_ `static inline void LogHexDump(const FString& InString, bool bDumpASCII=true, bool bDumpOffset=false, FOutputDevice* OutLog=GLog)` — Version of the above, which takes a string as input
- L946 _public prototype_ `static FString BitDump(const TArray<uint8>& InBytes, bool bDumpOffset=true, bool bLSBFirst=false);` — Takes an array of bytes, and generates a bit-based/binary dump string out of them, optionally including byte offsets also (intended for debugging in the log window) @param InBytes		The array of bytes to be dumped @param bDumpOffset	Whether or not to dump offset margins for bit rows/columns @param bLSBFirst		Whether or not the Least Significant Bit should be printed first, instead of last @return				Returns the hex dump, including line terminators
- L952 _public function_ `static inline FString BitDump(const uint8* InBytes, const uint32 InBytesLen, bool bDumpOffset=true, bool bLSBFirst=false)` — Version of the above bit-dump function, which takes a byte pointer and length as input
- L965 _public function_ `static inline FString BitDump(const FString& InString, bool bDumpOffset=false, bool bLSBFirst=false)` — Version of the above bit-dump function, which takes a string as input
- L978 _public function_ `static inline void LogBitDump(const TArray<uint8>& InBytes, bool bDumpOffset=false, bool bLSBFirst=false, FOutputDevice* OutLog=GLog)` — Version of the above bit-dump function, which dumps in a format more friendly/readable in log text files
- L995 _public function_ `static inline void LogBitDump(const uint8* InBytes, const uint32 InBytesLen, bool bDumpOffset=false, bool bLSBFirst=false, FOutputDevice* OutLog=GLog)` — Version of the above bit-dump logging function, which takes a byte pointer and length as input
- L1009 _public function_ `static inline void LogBitDump(const FString& InString, bool bDumpOffset=false, bool bLSBFirst=false, FOutputDevice* OutLog=GLog)` — Version of the above, which takes a string as input

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace NUT` (scope `UE`)
- L29 _externvar_ `extern FStackTraceManager* GTraceManager;` — Provides a globally accessible trace manager, for easy access to stack trace debugging
- L33 _externvar_ `extern FLogStackTraceManager* GLogTraceManager;` — Log hook for managing tying of log entry detection to the trace manager
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace NUT` (scope `UE`)
- L39 _externvar_ `extern UE::NUT::FLogHookManager* GLogHookManager;` (scope `UE::NUT`) — Generic string matching log hook, for executing code upon certain log entries
- L42 _externvar_ `extern UE::NUT::FLogTraceManager* GLogTrace;` (scope `UE::NUT`) — Log hook for managing tying of log entry detection to the trace manager
- L45 _externvar_ `extern UE::NUT::FLogCommandManager* GLogCommandManager;` (scope `UE::NUT`) — Log hook for executing console commands for certain log entries
- L50 _prototype_ `IMPLEMENT_GET_PRIVATE_VAR(FStackTracker, bIsEnabled, bool);` — Enable access to FStackTracker.bIsEnabled
- L53 _macro_ `#define TRACE_IGNORE_DEPTH 7` — The depth of stack traces, which the stack tracker should ignore by default
- L61 _prototype_ `extern "C" DLLEXPORT bool GGlobalExec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)`
- L471 _namespace_ `namespace UE`
- L471 _namespace_ `namespace NUT` (scope `UE`)
- L506 _typedef_ `using FLogHook = TUniqueFunction<void(const TCHAR* , ELogVerbosity::Type , const class FName& )>;` (scope `UE::NUT`) — Function to call as the log hook
- L509 _typedef_ `using FLogHookID = int32;` (scope `UE::NUT`) — Log hook ID, for removing later if desired
- L695 _prototype_ `ENUM_CLASS_FLAGS(ELogTraceFlags);`

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/NUTUtilProfiler.h` (Public)


#### class `FFrameProfiler`  
`class FFrameProfiler`  
_L19-85_
- desc: Uses the inbuilt UE profiler, to probe the specified profiling events performance, and to detect if the event uses up more than the specified percentage of frame time. NOTE: Only works with SCOPE_CYCLE_COUNTER stats NOTE: Only supports game thread stats, at the moment
- L28 _public function_ `FFrameProfiler(FName InTargetEvent, int32 InFramePercentThreshold) : TargetEvent(InTargetEvent) , FramePercentThreshold(InFramePercentThreshold) , bActive(false)` — Base constructor @param InTargetEvent				The event to be targeted/probed @param InFramePercentThreshold	The percentage of frame time used by the event, needed to trigger detection
- L38 _public function_ `virtual ~FFrameProfiler()` — Base destructor - for ending profiling upon destruct
- L50 _public prototype_ `void Start();` — Begins profiling/detection
- L55 _public prototype_ `void Stop();` — Ends profiling/detection
- L62 _public prototype_ `virtual void OnNewFrame(int64 Frame);` — Profiler hook for notification of new frame data @param Frame		The new frame number
- L65 _public function_ `bool IsActive() const`
- L73 _public member_ `FName TargetEvent;` — The event to be targeted/probed
- L76 _public member_ `int32 FramePercentThreshold;` — The percentage of frame time used by the event needed to trigger detection
- L81 _protected member_ `bool bActive;` — Whether or not profiling is active
- L84 _protected member_ `FDelegateHandle OnNewFrameDelegateHandle;` — Handle to the registered OnNewFrame delegate

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/NUTUtilReflection.h` (Public)


#### enum `EVMRefWarning`  
`enum class EVMRefWarning : uint8`  
_L200-204_
- desc: Used for specifying the warning level, for reflection helpers
- L202 _public enumerator_ `Warn` — Any errors during reflection are printed to log (default)
- L203 _public enumerator_ `NoWarn` — No errors during reflection are printed to log

#### class `FVMReflection`  
`class FVMReflection`  
_L209-823_
- desc: FVMReflection
- L215 _private prototype_ `FVMReflection();` — Private base constructor - should never be used externally
- L224 _public prototype_ `explicit FVMReflection(UObject* InBaseObject, EVMRefWarning InWarnLevel=EVMRefWarning::Warn);` — UObject constructor - Initializing from a UObject @param InBaseObject	The object the reflection helper should be initialized with @param InWarnLevel	Whether or not reflection failures (e.g. something major like missing properties) should be logged
- L232 _public prototype_ `explicit FVMReflection(FStructOnScope& InStruct, EVMRefWarning InWarnLevel=EVMRefWarning::Warn);` — Struct constructor - initializing from a scoped struct (allows you to use reflection, to work with unknown structs) @param InStruct		The scoped struct the reflection helper should be initialized with @param InWarnLevel	Whether or not reflection failures (e.g. something major like missing properties) should be logged
- L241 _public prototype_ `explicit FVMReflection(const FVMReflection& ToCopy);` — Copy constructor - used regularly to copy reflection states, but without passing on history or temporary variables (such as error return) @param ToCopy		The reflection helper to copy
- L249 _public prototype_ `explicit FVMReflection(FFuncReflection& InFuncRefl, EVMRefWarning InWarnLevel=EVMRefWarning::Warn);` — FFuncReflection copy constructor - initializing from a function reflection struct instance (shortcut to reference its parameters) @param InFuncRefl	The function reflection struct to initialize from @param InWarnLevel	Whether or not reflection failures (e.g. something major like missing properties) should be logged
- L256 _private prototype_ `FVMReflection& operator = (const FVMReflection& ToCopy);` — Copy assignment operator - not supported
- L261 _private function_ `FVMReflection* operator ->()` — Member access operator - not used, use ->* instead
- L273 _public prototype_ `FVMReflection& operator ->*(FString PropertyName);` — Member access operator. Used to access object/struct properties. @param PropertyName	The name of the property being accessed @return				Returns this VM reflector, for operator chaining
- L275 _public function_ `FORCEINLINE FVMReflection& operator ->*(const ANSICHAR* PropertyName)`
- L291 _public prototype_ `FVMReflection& operator [](int32 ArrayElement);` — Array subscript operator, used to access static/dynamic array elements NOTE: Due to operator precedence, you MUST wrap the accessed property in brackets, like so (FVMReflectior(blah)->*"ArrayProp")["Type"][Element]->*"etc" @param ArrayElement	The array element to access @return				Returns this VM reflector, for operator chaining
- L311 _public prototype_ `FVMReflection& operator [](const ANSICHAR* InFieldType);` — Array subscript operator, which takes a string for verifying that an array is of a particular type, e.g. ["uint8"]. This is mandatory, and must be specified before the array element subscript, like so: ByteArray["uint8"][0]. NOTE: This also works for structs, but should only be used when using (void*) to cast a struct to a pointer. The primary purpose of this, is for casting arrays to an (FScriptArray*), and then to (TArray<Type>*); without type verification with this operator, casting like this would be unsafe, as you would be assuming a type which may have later changed as the codebase evolves. Object arrays should be specified in the format ["U?*"], e.g. ["UObject*"], Actor arrays should be specified in the format ["A?*"], e.g. ["APawn*"], and Struct and struct arrays should be specified in the format ["F?"], e.g. ["FVector"]. @param InFieldType	The expected field type @return				Returns this VM reflector, for operator chaining
- L318 _private prototype_ `void ProcessObjectProperty();` — When an operator finishes, and is pointing to an object property, this changes the VM reflector context to that object
- L323 _private prototype_ `void ProcessStructProperty();` — As above, but for struct properties
- L330 _private prototype_ `template<typename InType, class InTypeClass> InType* GetWritableCast(const TCHAR* InTypeStr, bool bDoingUpCast=false);` — Internal template for defining simple pointer cast operators, for basic (e.g. numeric) types
- L338 _private prototype_ `template<typename InType, class InTypeClass> FORCEINLINE InType GetNumericTypeCast(const TCHAR* InTypeStr, const TArray<FFieldClass*>& SupportedUpCasts);` — Internal template for defining a readonly cast operator, for basic (e.g. numeric) types, with support for casting between types @param SupportedUpCasts		Types which support upcasting to InType
- L344 _private prototype_ `template<typename InType> FORCEINLINE InType GetTypeCast(const TCHAR* InTypeStr);` — Base version of above, for types with no upcasts
- L378 _public prototype_ `NUMERIC_POINTER_CAST_ASSIGN(uint8);` — Declare numeric pointer casts
- L379 _public prototype_ `NUMERIC_POINTER_CAST_ASSIGN(uint16);`
- L380 _public prototype_ `NUMERIC_POINTER_CAST_ASSIGN(uint32);`
- L381 _public prototype_ `NUMERIC_POINTER_CAST_ASSIGN(uint64);`
- L382 _public prototype_ `NUMERIC_POINTER_CAST_ASSIGN(int8);`
- L383 _public prototype_ `NUMERIC_POINTER_CAST_ASSIGN(int16);`
- L384 _public prototype_ `NUMERIC_POINTER_CAST_ASSIGN(int32);`
- L385 _public prototype_ `NUMERIC_POINTER_CAST_ASSIGN(int64);`
- L386 _public prototype_ `NUMERIC_POINTER_CAST_ASSIGN(float);`
- L387 _public prototype_ `NUMERIC_POINTER_CAST_ASSIGN(double);`
- L390 _public prototype_ `NUMERIC_CAST_ASSIGN_BASIC(uint8);` — Declare readonly numeric casts
- L391 _public prototype_ `NUMERIC_CAST_ASSIGN(uint16);`
- L392 _public prototype_ `NUMERIC_CAST_ASSIGN(uint32);`
- L393 _public prototype_ `NUMERIC_CAST_ASSIGN(uint64);`
- L394 _public prototype_ `NUMERIC_CAST_ASSIGN_BASIC(int8);`
- L395 _public prototype_ `NUMERIC_CAST_ASSIGN(int16);`
- L396 _public prototype_ `NUMERIC_CAST_ASSIGN(int32);`
- L397 _public prototype_ `NUMERIC_CAST_ASSIGN(int64);`
- L398 _public prototype_ `NUMERIC_CAST_ASSIGN_BASIC(float);`
- L399 _public prototype_ `NUMERIC_CAST_ASSIGN(double);`
- L403 _public prototype_ `GENERIC_POINTER_CAST_ASSIGN(FName);` — Declare generic pointer casts
- L404 _public prototype_ `GENERIC_POINTER_CAST_ASSIGN(FString);`
- L405 _public prototype_ `GENERIC_POINTER_CAST_ASSIGN(FText);`
- L414 _public prototype_ `explicit operator bool();` — Cast to bool
- L419 _public prototype_ `explicit operator FName();` — Cast to FName
- L424 _public prototype_ `explicit operator FString();` — Cast to FString
- L429 _public prototype_ `explicit operator FText();` — Cast to FText
- L434 _public prototype_ `explicit operator UObject**();` — Cast to writable UObject* pointer (only valid for object properties)
- L439 _public prototype_ `explicit operator UObject*();` — Cast to UObject*
- L445 _public prototype_ `explicit operator FSoftObjectPtr*();` — Cast to writable FSoftObjectPtr* (where write actions should be performed through FSoftObjectPrr methods, not by pointer assignment). For FSoftObjectProperty
- L453 _public prototype_ `explicit operator FScriptArray*();` — Cast to FScriptArray* pointer (only valid for dynamic arrays), then cast to TArray<Type*> NOTE: There is no FScriptArray** operator, as that should never be writable NOTE: Use the TSharedPtr<FScriptArrayHelper> operator, if you need to modify an array of uncertain/undefined type
- L459 _public prototype_ `explicit operator TSharedPtr<FScriptArrayHelper>();` — Cast to an FScriptArrayHelper, which is useful for performing operations on arrays of an uncertain/undefined type NOTE: Useful specifically in cases where you need to add to an array, less so for array iteration.
- L468 _public prototype_ `explicit operator void*();` — Cast operator for structs in general - cast to void*, then cast to StructType*
- L475 _public function_ `template<typename T> FORCEINLINE T* GetStructRef()` — Gets a reference to the struct being pointed to, with compile-time and runtime checks on the validity of the struct type NOTE: This alters the state of the reflection object.
- L490 _public prototype_ `FVMReflection& operator = (bool Value);` — Assign a value to a bool property
- L495 _public prototype_ `FVMReflection& operator = (UObject* Value);` — Assign a value to an object property
- L501 _public prototype_ `FVMReflection& operator = (TCHAR* Value);` — Assign a value to either a string or an enum property (autodetects enums) NOTE: Enums must be specified in format: EEnumName::EnumValueName
- L515 _public prototype_ `TValueOrError<FString, FString> GetValueAsString();` — Converts the value of whatever the reflection helper is pointing to, into a human readable string. @return	A human readable representation of what the reflection helper is pointing to
- L522 _public function_ `FORCEINLINE int32 GetArrayNum() const` — If pointing to an array, returns the array size. Cache the value, instead of using it directly in a for loop @return	Returns the size of the array
- L546 _public prototype_ `FVMReflection& operator ,(bool* bErrorPointer);` — Allows an inline method of returning the error status - the comma operator has the lowest precedence, so is executed last. This also allows you to test for errors at every stage of reflection (although it's a bit ugly if done this way), e.g: UObject* Result = (UObject*)(((FVMReflection(TestObjA), &bError)->*"AObjectRef", &bErrorA)->*"BObjectRef", &bErrorB); Since the operator specifies a bool pointer though, we don't want to hold onto this pointer longer than necessary (in case it becomes a dangling pointer), so it is unset every time an operator returns (with the exception of this operator). This means both, that you can use error bools to catch errors from within specific parts of a statement, while also avoiding invalid memory access: (Cast)((->*"Blah", &bError)->*"Boo"):	Returns errors accessing 'Blah', but not 'Boo' or 'Cast' It also means, that if you specify a bool right at the end of a reflection statement, before casting to a return type, that you can use this last reflection statement to detect casting errors too: (Cast)(->*"Blah"->*"Boo", &bError):		Returns errors accessing Blah, Boo, or with Cast
- L553 _public prototype_ `FVMReflection& operator ,(FString* OutHistory);` — As above, but returns the complete reflection history so far, including any errors @param OutHistory	Takes and stores a temporary reference, to the a string for outputting the reflection history
- L561 _public function_ `FORCEINLINE bool IsError() const` — Returns the current error status @return Whether or not the reflection helper encountered an error
- L569 _public function_ `FORCEINLINE void DisableFieldVerification()` — Disables the need to verify field types before accessing structs etc., to e.g. make use of the 'reflect' console command easier.
- L580 _public function_ `FORCEINLINE FString GetHistory() const` — Returns the reflection helper history as a string @return	Returns the history
- L596 _public prototype_ `void DebugDump();` — Does a complete debug dump of the state of this reflection instance, and disables further use
- L608 _private function_ `FORCEINLINE bool IsPropertyArray() const` — Whether or not a property is an array (static or dynamic) @return	Returns whether or not the property is an array (static or dynamic)
- L620 _private function_ `FORCEINLINE bool IsPropertyObject() const` — Whether or not a property is an object @return	Returns whether or not the object is an object
- L631 _private function_ `FORCEINLINE bool CanCastProperty() const` — Whether or not the VM reflector points to a property that is ready for casting @return	Whether or not the VM reflector is ready for casting
- L644 _private function_ `template<typename PropertyClass> FORCEINLINE bool CanCastObject() const` — Whether or not the VM reflector points to an object that is ready for casting @param PropertyClass		The UObject property to check for @return					Whether or not the VM reflector is ready for casting
- L671 _private function_ `FORCEINLINE bool CanCastArray() const` — Whether or not the VM reflector points to an array that is ready for casting to an array pointer @return	Whether or not the VM reflector is ready for casting
- L682 _private function_ `FORCEINLINE bool CanCastStruct() const` — Whether or not the VM reflector points to a struct that is ready for casting to a pointer @return	Whether or not the VM reflector is ready for casting
- L696 _private function_ `FORCEINLINE void NotifyOperator(FString Operation)` — Called early within non-cast operators, to unset error pointers
- L711 _private function_ `FORCEINLINE void NotifyCastReturn()` — Notification of a cast return, to unset error pointers
- L725 _private prototype_ `void SetFieldAddress(void* InFieldAddress, bool bSettingArrayElement=false);` — Encapsulates code that sets the field address @param InFieldAddress		The new field address @param bSettingArrayElement	Whether or not the new field address is for an array element
- L732 _private function_ `FORCEINLINE void AddHistory(FString InHistory)` — Adds a new operation to the reflection helper history @param InHistory		The line to be added to the history
- L752 _private function_ `FORCEINLINE void AddCastHistory(FString InHistory)` — Adds the final casting operation to the reflection helper history @param InHistory		The line to be added to the history
- L773 _private prototype_ `void SetError(FString InError, bool bCastError=false);` — Sets the error status, and relays it to the error/history output pointers, if set @param InError		The error description @param bCastError	Whether or not this was a casting error
- L775 _private function_ `FORCEINLINE void SetCastError(FString InHistory)`
- L784 _private member_ `void* BaseAddress;` — The current base object (or struct) address location
- L788 _private member_ `FFieldVariant FieldInstance;` — The current field instance (e.g. a UPROPERTY within AActor or such)
- L791 _private member_ `void* FieldAddress;` — The address of the current field - OR, if bSetArrayElement - the address of the current array element
- L794 _private member_ `bool bVerifiedFieldType : 1;` — Whether or not the array or struct type has been specified for verification
- L797 _private member_ `bool bSkipFieldVerification : 1;` — Whether or not to skip field verification (e.g. when using the 'reflect' console command)
- L800 _private member_ `bool bSetArrayElement : 1;` — Whether or not the array element has been set, for an array
- L803 _private member_ `bool bNextActionMustBeCast : 1;` — The ->* operator tried to step into an object/struct which was NULL. If the next action is not a cast, it is an error.
- L807 _private member_ `bool bIsError : 1;` — Whether or not there was an error during reflection
- L810 _private member_ `FString NextActionError;` — Tied with 'bNextActionMustBeCast', this is the error that will be logged if an action other than cast is tried.
- L813 _private member_ `bool* bOutError;` — Holds a temporary pointer, for outputting errors - regularly reset to NULL, to avoid potential invalid memory access
- L816 _private member_ `TArray<FString> History;` — The history of reflection operations
- L819 _private member_ `FString* OutHistoryPtr;` — Holds a temporary pointer, for outputting error history - regularly reset to NULL, like bOutError
- L822 _private member_ `EVMRefWarning WarnLevel;` — Controls whether or not errors are printed to log

#### class `FFuncReflection`  
`class FFuncReflection`  
_L832-914_
- desc: FFuncReflection - helper for quickly/concisely setting function parameters through reflection
- L835 _private function_ `FFuncReflection(UFunction* InFunction, const TCHAR* InFuncName) : FunctionName(InFuncName) , Function(InFunction) , ParmsMemory(Function) , ParmsRefl(ParmsMemory)`
- L843 _private function_ `FFuncReflection(UFunction* InFunction, const TCHAR* InFuncName, void* InParmsMemory) : FunctionName(InFuncName) , Function(InFunction) , ParmsMemory(Function, (uint8*)InParmsMemory) , ParmsRefl(ParmsMemory)`
- L858 _public function_ `FFuncReflection(const TCHAR* InClassName, const TCHAR* InFuncName) : FFuncReflection(FindUField<UFunction>(UClass::TryFindTypeSlow<UClass>(InClassName), InFuncName), InFuncName)` — Constructor for creating a function instance and (optionally) filling in its parameters @param InClassName	The name of the class the function is in @param InFuncName	The name of the function
- L869 _public function_ `FFuncReflection(UObject* TargetObj, const TCHAR* InFuncName) : FFuncReflection((TargetObj != nullptr ? TargetObj->FindFunction(InFuncName) : nullptr), InFuncName)` — Constructor for creating a function instance and (optionally) filling in its parameters @param TargetObj		The object the function is in @param InFuncName	The name of the function
- L880 _public function_ `FFuncReflection(UFunction* InFunction, void* InParms) : FFuncReflection(InFunction, *InFunction->GetName(), InParms)` — Constructor for reading (and optionally modifying) an existing functions parameters (e.g. from received RPC's) @param InFunction	The function whose parameters we want to read/modify @param InParms		The function parameters memory pointer
- L885 _public function_ `FORCEINLINE bool IsValid() const`
- L890 _public function_ `FORCEINLINE UFunction* GetFunc()`
- L895 _public function_ `FORCEINLINE void* GetParms() const`
- L902 _public member_ `const TCHAR* FunctionName;` — The name of the function
- L905 _public member_ `UFunction* Function;` — Reference to the function
- L909 _private member_ `FStructOnScope ParmsMemory;` — The function parameters in memory
- L913 _public member_ `const FVMReflection ParmsRefl;` — Reflection instance, for writing the function parameters - initialize a new instance from this, e.g. FVMReflection(ParmsRefl)

#### struct `NUTUtilRefl`  
`struct NUTUtilRefl`  
_L920-932_
- desc: NUTUtilRefl - general reflection helper utility functions
- L931 _public prototype_ `static FString FunctionParmsToString(UFunction* InFunction, void* Parms);` — Iterates a functions parameters, and converts them to a human readable string NOTE: Can not be passed back to functions that read parameters from a string, e.g. 'CallFunctionByNameWithArguments' @todo #JohnB: This would be a good goal though @param InFunction	The function template whose parameters are being parsed @param Parms			The parameter data to be parsed @return				Returns the parsed parameter data

#### Free symbols / members of external scopes

- L348 _macro_ `#define GENERIC_POINTER_CAST_ASSIGN(InType) \` — Some macros for declaring casts, which are implemented using correspondingly named macros, in the .cpp
- L364 _macro_ `#define NUMERIC_POINTER_CAST_ASSIGN(InType) GENERIC_POINTER_CAST_ASSIGN(InType)`
- L366 _macro_ `#define NUMERIC_CAST_ASSIGN_BASIC(InType) \`
- L369 _macro_ `#define NUMERIC_CAST_ASSIGN(InType) NUMERIC_CAST_ASSIGN_BASIC(InType)`

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/NUTUtilReflectionParser.h` (Public)


#### struct `FReflEvaluationContext`  
`struct FReflEvaluationContext`  
_L23-35_
- desc: Provides a context for evaluating expressions, where the FVMReflection object is initialized/passed-on
- L26 _public member_ `TSharedPtr<FVMReflection> Refl;` — The reflection handler containing the current state of reflection
- L31 _public function_ `FReflEvaluationContext() : Refl(nullptr)` — Default constructor

#### struct `FContextPointer`  
`struct FContextPointer`  
_L44-52_
- desc: There is a problem with the parser API, where the Context you pass into the Evaluate function is marked: const ContextType* Context This means you can not modify Context (which I need to do, to pass state information within the parser), but there is a loophole, where you are able to modify anything Context points to, so I use this struct to wrap the REAL context (FReflEvaluationContext), as a pointer in a dud struct.
- L46 _public member_ `FReflEvaluationContext* Context;`
- L48 _public function_ `FContextPointer(FReflEvaluationContext* InContext) : Context(InContext)`

#### struct `FTestResultPointer`  
`struct FTestResultPointer`  
_L55-63_
- L57 _public member_ `struct FTestResult* Result;`
- L59 _public function_ `FTestResultPointer(FTestResult* InResult) : Result(InResult)`

#### class `FVMReflectionParser`  
`class FVMReflectionParser`  
_L70-147_
- desc: FVMReflectionParser
- L76 _public prototype_ `FVMReflectionParser();` — Base constructor
- L86 _public prototype_ `TValueOrError<TSharedPtr<FVMReflection>, FExpressionError> Evaluate(const TCHAR* InExpression, UObject* InTargetObj=nullptr) const;` — Evaluate the given reflection expression, into an FVMReflection instance @param InExpression	The expression to evaluate @param InTargetObj	Optionally, the target object to perform reflection on @return				Returns either a shared pointer to an FVMReflection instance, or an error
- L95 _public prototype_ `TValueOrError<FString, FExpressionError> EvaluateString(const TCHAR* InExpression, UObject* InTargetObj=nullptr) const;` — As above, except converts whatever the final reflection state points to, into a human readable string @param InExpression	The expression to evaluate @param InTargetObj	Optionally, the target object to perform reflection on @return				Returns either a string representing the final reflection state, or an error
- L105 _protected prototype_ `static TOptional<FStringToken> ParseIdentifier(const FTokenStream& InStream, FStringToken* Accumulate=nullptr);` — Attempts to parse an identifier token (variable/function name) from the stream @param InStream		The stream to attempt token parsing on @param Accumulate	Optionally specify an existing string token, to append the parsed token to @return				If successful, returns the parsed string token, if false, returns nothing and IsSet will be false.
- L114 _protected prototype_ `static TOptional<FStringToken> ParseArraySubscript(const FTokenStream& InStream, FStringToken* Accumulate=nullptr);` — Attempts to parse an array subscript operator, Array[Num], from the stream @param InStream		The stream to attempt token parsing on @param Accumulate	Optionally specify an existing string token, to append the parsed token to @return				If successful, returns the parsed string token, if false, returns nothing and IsSet will be false.
- L122 _public prototype_ `void TestConstruct();` — Initializes automated testing parser parameters.
- L130 _public prototype_ `TValueOrError<FString, FExpressionError> TestEvaluate(const TCHAR* InExpression) const;` — Evaluates a test expression @param InExpression	The expression to evaluate @return				Returns the result of the test
- L135 _protected member_ `FTokenDefinitions TokenDefinitions;` — A dictionary used for defining how tokens are lexed
- L138 _protected member_ `FExpressionGrammar Grammar;` — Used to define the lexical grammar for how an expression should be parsed, e.g. defining operators/preoperators etc.
- L141 _protected member_ `TOperatorJumpTable<FContextPointer> OpJumpTable;` — Table for mapping operator definitions, to a function which should evaluate the operator
- L145 _protected member_ `TOperatorJumpTable<FTestResultPointer> TestOpJumpTable;` — Table for test operators

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/Net/NUTUtilNet.h` (Public)


#### class `FProcessEventHook`  
`class FProcessEventHook`  
_L60-179_
- desc: Class for encapsulating ProcessEvent and general RPC hooks, implemented globally for each UWorld NOTE: Presently, all RPC hooks tied to UWorld's only hook client RPC's - global RPC hooks, hook both client and server RPC's
- L66 _public function_ `static FProcessEventHook& Get()` — Get a reference to the net event hook singular
- L82 _public function_ `FProcessEventHook() : NetEventHooks() , EventHooks() , GlobalNetEventHooks() , GlobalEventHooks()` — Default constructor
- L96 _public prototype_ `void AddRPCHook(UWorld* InWorld, FOnProcessNetEvent InHook);` — Adds an RPC hook for the specified UWorld. @param InWorld	The UWorld whose RPC's should be hooked @param InHook	The delegate for handling the hooked RPC's
- L103 _public prototype_ `void RemoveRPCHook(UWorld* InWorld);` — Removes the RPC hook for the specified UWorld. @param InWorld	The UWorld whose RPC hook should be cleared.
- L111 _public prototype_ `void AddEventHook(UWorld* InWorld, FOnProcessNetEvent InHook);` — Adds a non-RPC hook for the specified UWorld. @param InWorld	The UWorld whose RPC's should be hooked @param InHook	The delegate for handling the hooked events
- L118 _public prototype_ `void RemoveEventHook(UWorld* InWorld);` — Removes the hook for the specified UWorld. @param InWorld	The UWorld whose RPC hook should be cleared.
- L126 _public prototype_ `FDelegateHandle AddGlobalRPCHook(FOnProcessNetEvent InHook);` — Adds a global RPC hook. @param InHook	The delegate for handling the hooked RPC's @return			Returns a delegate handle, used for removing the hook later
- L133 _public prototype_ `void RemoveGlobalRPCHook(FDelegateHandle InHandle);` — Removes the specified global RPC hook @param InHandle	The handle to the global RPC hook to remove
- L141 _public prototype_ `FDelegateHandle AddGlobalEventHook(FOnProcessNetEvent InHook);` — Adds a global non-RPC hook. @param InHook	The delegate for handling the hooked events @return			Returns a delegate handle, used for removing the hook later
- L148 _public prototype_ `void RemoveGlobalEventHook(FDelegateHandle InHandle);` — Removes the specified global non-RPC hook @param InHandle	The handle to the global non-RPC hook to remove
- L155 _private prototype_ `void PreAddHook();` — Checks performed prior to adding any hooks
- L160 _private prototype_ `void PostRemoveHook();` — Checks performed after removing any hooks
- L165 _private prototype_ `bool HandleProcessEvent(AActor* Actor, UFunction* Function, void* Parameters);` — Base hook for AActor::ProcessEventDelegate - responsible for filtering based on RPC events and Actor UWorld
- L169 _private member_ `TMap<UWorld*, FOnProcessNetEvent> NetEventHooks;` — The global list of RPC hooks, and the UWorld they are associated with
- L172 _private member_ `TMap<UWorld*, FOnProcessNetEvent> EventHooks;` — The global list of ProcessEvent hooks, and the UWorld they are associated with
- L175 _private member_ `TArray<FOnProcessNetEvent> GlobalNetEventHooks;` — The global list of RPC hooks, which aren't associated with a specific UWorld
- L178 _private member_ `TArray<FOnProcessNetEvent> GlobalEventHooks;` — The global list of ProcessEvent hooks, which aren't associated with a specific UWorld

#### class `FNetworkNotifyHook`  
`class FNetworkNotifyHook : public FNetworkNotify`  
_L188-249_
- inherits: `FNetworkNotify`
- desc: A delegate network notify class, to allow for easy inline-hooking. NOTE: This will memory leak upon level change and re-hooking (if used as a hook), because there is no consistent way to handle deleting it.
- L194 _public function_ `FNetworkNotifyHook() : FNetworkNotify() , NotifyAcceptingConnectionDelegate() , NotifyAcceptedConnectionDelegate() , NotifyAcceptingChannelDelegate() , NotifyControlMessageDelegate() , HookedNotify(NULL)` — Base constructor
- L207 _public function_ `FNetworkNotifyHook(FNetworkNotify* InHookNotify) : FNetworkNotify() , HookedNotify(InHookNotify)` — Constructor which hooks an existing network notify
- L216 _public function_ `virtual ~FNetworkNotifyHook()` — Virtual destructor
- L226 _protected prototype_ `virtual EAcceptConnection::Type NotifyAcceptingConnection() override;`
- L228 _protected prototype_ `virtual void NotifyAcceptedConnection(UNetConnection* Connection) override;`
- L230 _protected prototype_ `virtual bool NotifyAcceptingChannel(UChannel* Channel) override;`
- L232 _protected prototype_ `virtual void NotifyControlMessage(UNetConnection* Connection, uint8 MessageType, FInBunch& Bunch) override;`
- L235 _protected prototype_ `DECLARE_DELEGATE_RetVal(EAcceptConnection::Type, FNotifyAcceptingConnectionDelegate);`
- L236 _protected prototype_ `DECLARE_DELEGATE_OneParam(FNotifyAcceptedConnectionDelegate, UNetConnection* );`
- L237 _protected prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FNotifyAcceptingChannelDelegate, UChannel* );`
- L238 _protected prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FNotifyControlMessageDelegate, UNetConnection* , uint8 , FInBunch& );`
- L242 _public member_ `FNotifyAcceptingConnectionDelegate NotifyAcceptingConnectionDelegate;`
- L243 _public member_ `FNotifyAcceptedConnectionDelegate NotifyAcceptedConnectionDelegate;`
- L244 _public member_ `FNotifyAcceptingChannelDelegate NotifyAcceptingChannelDelegate;`
- L245 _public member_ `FNotifyControlMessageDelegate NotifyControlMessageDelegate;`
- L248 _public member_ `FNetworkNotify* HookedNotify;` — If this is hooking an existing network notify, save a reference

#### class `FWorldTickHook`  
`class FWorldTickHook`  
_L255-305_
- desc: Class for hooking world tick events, and setting globals for log hooking
- L277 _public function_ `FWorldTickHook(UWorld* InWorld) : AttachedWorld(InWorld) , InternalGC(this)`
- L283 _public prototype_ `void Init();`
- L285 _public prototype_ `void Cleanup();`
- L288 _private prototype_ `void TickDispatch(float DeltaTime);`
- L290 _private prototype_ `void PostTickFlush();`
- L294 _public member_ `TObjectPtr<UWorld> AttachedWorld;` — The world this is attached to
- L298 _private member_ `FDelegateHandle TickDispatchDelegateHandle;` — Handle for Tick dispatch delegate
- L301 _private member_ `FDelegateHandle PostTickFlushDelegateHandle;` — Handle for PostTick dispatch delegate
- L304 _private member_ `FInternalGCObject InternalGC;` — Internal GC

#### class `FWorldTickHook::FInternalGCObject`  
`class FInternalGCObject : public FGCObject`  
_L259-274_
- inherits: `FGCObject`
- desc: Internal GC hook, due to 'Init' function name conflict
- L262 _public prototype_ `FInternalGCObject() = delete;`
- L264 _public function_ `FInternalGCObject(FWorldTickHook* InOwner) : Owner(InOwner)`
- L269 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L270 _public prototype_ `virtual FString GetReferencerName() const override;`
- L273 _private member_ `FWorldTickHook* Owner;`

#### class `FScopedNetObjectReplace`  
`class FScopedNetObjectReplace`  
_L313-325_
- desc: Hooks netcode object serialization, in order to replace replication of a specific object, with another specified object, for the lifetime of the scoped instance
- L316 _public prototype_ `FScopedNetObjectReplace(UClientUnitTest* InUnitTest, UObject* InObjToReplace, UObject* InObjReplacement);`
- L318 _public prototype_ `~FScopedNetObjectReplace();`
- L322 _private member_ `UClientUnitTest* UnitTest;`
- L324 _private member_ `UObject* ObjToReplace;`

#### class `FScopedNetNameReplace`  
`class FScopedNetNameReplace`  
_L331-345_
- desc: Hooks netcode name serialization, in order to replace replication of a specific name, with another specified name, for the lifetime of the scoped instance
- L334 _public prototype_ `FScopedNetNameReplace(UMinimalClient* InMinClient, const FOnSerializeName::FDelegate& InDelegate);`
- L337 _public prototype_ `FScopedNetNameReplace(UMinimalClient* InMinClient, FName InNameToReplace, FName InNameReplacement);` — @todo #JohnB: This variation is not tested
- L339 _public prototype_ `~FScopedNetNameReplace();`
- L342 _private member_ `UMinimalClient* MinClient;`
- L344 _private member_ `FDelegateHandle Handle;`

#### class `FScopedRPCParamReplace`  
`class FScopedRPCParamReplace`  
_L350-362_
- desc: Hooks the netcode serialization of a specific RPC parameter, in order to override the raw serialized param data with something else
- L353 _public prototype_ `FScopedRPCParamReplace(UMinimalClient* InMinClient, UFunction* InTargetRPC, FString InParamName, const FOnNetSerializeItem& InSerializeHook);`
- L356 _public prototype_ `~FScopedRPCParamReplace();`
- L359 _private member_ `FRepLayoutCmd* ParamRepCmd;`
- L361 _private member_ `FProperty* OriginalParam;`

#### class `FNetPropertyHook`  
`class FNetPropertyHook : public FProperty`  
_L367-381_
- inherits: `FProperty`
- desc: Implements the actual hook for the above class
- L372 _private prototype_ `virtual bool NetSerializeItem(FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8>* MetaData ) const override;`
- L376 _public function_ `FNetPropertyHook(FFieldVariant InOwner, const FName& InName) : FProperty(InOwner, InName)`
- L380 _public member_ `FOnNetSerializeItem SerializeHook;`

#### struct `NUTNet`  
`struct NUTNet`  
_L387-425_
- desc: Netcode based utility functions
- L397 _public prototype_ `static void HandleBeaconReplicate(AActor* InBeacon, UNetConnection* InConnection);` — Handles setting up the client beacon once it is replicated, so that it can properly send RPC's (normally the serverside client beacon links up with the pre-existing beacon on the clientside, but with unit tests there is no pre-existing clientside beacon) @param InBeacon		The beacon that should be setup @param InConnection	The connection associated with the beacon
- L406 _public prototype_ `static UWorld* CreateUnitTestWorld(bool bHookTick=true);` — Creates a barebones/minimal UWorld, for setting up minimal client connections, and as a container for objects in the unit test commandlet @return	Returns the created UWorld object
- L414 _public prototype_ `static void MarkUnitTestWorldForCleanup(UWorld* CleanupWorld, bool bImmediate=false);` — Marks the specified unit test world for cleanup @param CleanupWorld	The unit test world to be marked for cleanup @param bImmediate	If true, all unit test worlds pending cleanup, are immediately cleaned up
- L419 _public prototype_ `static void CleanupUnitTestWorlds();` — Cleans up unit test worlds queued for cleanup
- L424 _public prototype_ `static bool IsUnitTestWorld(UWorld* InWorld);` — Returns true, if the specified world is a unit test world

#### Free symbols / members of external scopes

- L42 _delegate_ `DECLARE_DELEGATE_FourParams(FOnProcessNetEvent, AActor* , UFunction* , void* , bool& );` — Delegate used to control/block receiving of RPC's @param Actor			The actor the RPC will be called on @param Function		The RPC to call @param Parameters	The parameters data blob @param bBlockRPC		Whether or not to block execution of the RPC
- L42 _prototype_ `DECLARE_DELEGATE_FourParams(FOnProcessNetEvent, AActor* , UFunction* , void* , bool& );` — Delegate used to control/block receiving of RPC's @param Actor			The actor the RPC will be called on @param Function		The RPC to call @param Parameters	The parameters data blob @param bBlockRPC		Whether or not to block execution of the RPC
- L52 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FOnNetSerializeItem, FArchive& , UPackageMap* , void* , TArray<uint8>* );` — Delegate used to control hooked serialization of RPC parameters @param Ar			The archive being serialized to @param Map			The PackageMap for the net connection @param Data			The raw property data @param MetaData		The meta data for the property
- L52 _prototype_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FOnNetSerializeItem, FArchive& , UPackageMap* , void* , TArray<uint8>* );` — Delegate used to control hooked serialization of RPC parameters @param Ar			The archive being serialized to @param Map			The PackageMap for the net connection @param Data			The raw property data @param MetaData		The meta data for the property
- L235 _delegate_ `DECLARE_DELEGATE_RetVal(EAcceptConnection::Type, FNotifyAcceptingConnectionDelegate);`
- L236 _delegate_ `DECLARE_DELEGATE_OneParam(FNotifyAcceptedConnectionDelegate, UNetConnection* );`
- L237 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FNotifyAcceptingChannelDelegate, UChannel* );`
- L238 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FNotifyControlMessageDelegate, UNetConnection* , uint8 , FInBunch& );`

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/NetcodeUnitTest.h` (Public)


#### Free symbols / members of external scopes

- L19 _externvar_ `extern UUnitTestManager* GUnitTestManager;` — Holds a reference to the object in charge of managing unit tests
- L22 _externvar_ `extern bool GIsInitializingActorChan;` — Whether not an actor channel, is in the process of initializing the remote actor
- L29 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUnitTest, Log, All);`
- L32 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(NetCodeTestNone, Log, All);` — Hack to allow log entries to print without the category (specify log type of 'none')
- L32 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(NetCodeTestNone, Log, All);` — Hack to allow log entries to print without the category (specify log type of 'none')
- L43 _macro_ `#define NUT_SUSPEND_PIPE TEXT("\\\\.\\Pipe\\NetcodeUnitTest_SuspendResume")` — The IPC pipe used for resuming a suspended server NOTE: You must append the process ID of the server to this string
- L52 _macro_ `#define UNIT_ASSERT(Condition) \` — Actual asserts (not optimized out, like almost all other engine assert macros) @todo #JohnBLowPri: Try to get this to show up a message box, or some other notification, rather than just exiting immediately

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/UI/LogWidgetCommands.h` (Public)


#### class `FLogWidgetCommands`  
`class FLogWidgetCommands : public TCommands<FLogWidgetCommands>`  
_L12-35_
- inherits: `TCommands<FLogWidgetCommands>`
- desc: Defines a set of commands used by the unit test log window
- L15 _public function_ `FLogWidgetCommands() : TCommands<FLogWidgetCommands>("NUTLogWidget", FText::FromString(TEXT("Unit Test Log")), NAME_None, FCoreStyle::Get().GetStyleSetName()) , CopyLogLines(NULL) , FindLogText(NULL)`
- L26 _public prototype_ `void RegisterCommands() override;` — Register commands
- L31 _public member_ `TSharedPtr<FUICommandInfo> CopyLogLines;` — Command for copying the currently selected log line(s)
- L34 _public member_ `TSharedPtr<FUICommandInfo> FindLogText;` — Command for finding text within the current log window tab

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/UI/LogWindowManager.h` (Public)


#### struct `FLogGridEntry`  
`struct FLogGridEntry`  
_L48-67_
- desc: Struct representing a grid location for a log window
- L50 _public function_ `FLogGridEntry() : LogWindow(NULL) , Top(0.f) , Bottom(0.f) , Left(0.f) , Right(0.f)`
- L60 _public member_ `TSharedPtr<SLogWindow> LogWindow;` — A reference to the log window inhabiting this grid space (if any)
- L63 _public member_ `float Top;` — The dimensions of the grid entry
- L64 _public member_ `float Bottom;`
- L65 _public member_ `float Left;`
- L66 _public member_ `float Right;`

#### class `FLogWindowManager`  
`class FLogWindowManager`  
_L77-152_
- desc: Basic window manager, for handling tiling of unit test log windows. How this works: Upon initialization, takes the average dimensions of a log window, and of the desktop working area, and maps out a grid for fitting the log windows onto the desktop - nothing more complicated than that
- L80 _public function_ `FLogWindowManager() : bInitialized(false) , GridSpaces() , LastLogWindowPos(-1) , OverflowWindows() , LogWidth(0) , LogHeight(0)`
- L93 _public prototype_ `~FLogWindowManager();` — Base destructor
- L101 _public prototype_ `void Initialize(int InLogWidth, int InLogHeight);` — Initializes the log window manager @param InLogWidth	The width that log windows will have @param InLogHeight	The height that log windows will have
- L111 _public prototype_ `TSharedPtr<SLogWindow> CreateLogWindow(FString Title=TEXT(""), ELogType ExpectedFilters=ELogType::None, bool bStatusWindow=false);` — Creates a new log window, and returns a reference @param Title				The title to give the long window @param ExpectedFilters	The type of log output that is expected - used for setting up tabs @param bStatusWindow		Whether or not the window being created is the status window @return					A reference to the created log window
- L119 _public prototype_ `void OnWindowClosed(const TSharedRef<SWindow>& ClosedWindow);` — Monitor for closed log windows @param ClosedWindow	The window that was closed
- L127 _protected prototype_ `int FindFreeGridPos();` — Finds the next free grid position for the log window NOTE: Instead of searching for the first empty space, tries to create log windows in a row pattern based upon the grid
- L132 _protected member_ `bool bInitialized;` — Whether or not the log window manager has been initialized
- L136 _protected member_ `TArray<FLogGridEntry> GridSpaces;` — An array of currently open log windows
- L139 _protected member_ `int LastLogWindowPos;` — The last grid entry where a log window was placed
- L142 _protected member_ `TArray<TSharedPtr<SLogWindow>> OverflowWindows;` — A list of windows that have overflowed the grid (these start minimized, waiting for a space in the grid)
- L146 _protected member_ `int LogWidth;` — The dimensions log windows should have
- L147 _protected member_ `int LogHeight;`
- L151 _protected member_ `TMap<SLogWindow*, FDelegateHandle> OnWindowClosedDelegateHandles;` — Handles to registered OnWindowClosed delegates for particular windows

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/UI/SLogDialog.h` (Public)


#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnLogDialogResult, const TSharedRef<SWindow>& , EAppReturnType::Type , bool );` — Result callback delegate, for below function @param DialogWindow	The dialog returning a response @param Result		The result/response @param bNoResult		Whether or not the result is invalid, e.g. the dialog was closed instead of a button clicked
- L26 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnLogDialogResult, const TSharedRef<SWindow>& , EAppReturnType::Type , bool );` — Result callback delegate, for below function @param DialogWindow	The dialog returning a response @param Result		The result/response @param bNoResult		Whether or not the result is invalid, e.g. the dialog was closed instead of a button clicked
- L39 _prototype_ `TSharedRef<SWindow> OpenLogDialog_NonModal(EAppMsgType::Type InMessageType, const FText& InMessage, const FText& InTitle, FOnLogDialogResult ResultCallback=NULL);` — Opens a non-modal/non-blocking message box, which returns its result through a delegate/callback, using a reference to the created window, to identify which dialog has returned a result (in case there are multiple dialog windows) @param InMessageType		The type of message box to display (e.g. 'ok', or 'yes'/'no' etc.) @param InMessage			The message to display in the message box @param InTitle			The title to display for the message box @param ResultCallback	Optionally, specify a delegate/callback instance, where results should be returned @return					Returns the dialog window reference, which the calling code should store, to identify which dialog returned
- L42 _function_ `FORCEINLINE TSharedRef<SWindow> OpenLogDialog_NonModal(EAppMsgType::Type InMessageType, const FString& InMessage, const FString& InTitle, FOnLogDialogResult ResultCallback=NULL)`

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/UI/SLogWidget.h` (Public)


#### struct `FLogLine`  
`struct FLogLine`  
_L52-74_
- desc: Struct representing a log line
- L55 _public member_ `ELogType LogType;` — The unit test log type
- L58 _public member_ `TSharedRef<FString> LogLine;` — The raw log line string
- L61 _public member_ `FSlateColor LogColor;` — The color of the log line
- L64 _public member_ `FString LogHighlight;` — The text within the log line, to highlight (from searches)
- L67 _public function_ `FLogLine(ELogType InLogType, TSharedRef<FString> InLogLine, FSlateColor InLogColor) : LogType(InLogType) , LogLine(InLogLine) , LogColor(InLogColor) , LogHighlight()`

#### struct `FLogTabInfo`  
`struct FLogTabInfo`  
_L79-160_
- desc: Struct containing tab-specific information
- L82 _public member_ `FString Label;` — The label to apply to the tab
- L85 _public member_ `FString ToolTip;` — The tooltip/description to apply to the tab
- L88 _public member_ `ELogType Filter;` — The log line filter the tab should use
- L91 _public member_ `uint8 Priority;` — When a logged line requests focus, this determines the priority for selecting what tab to focus (lower = higher priority)
- L94 _public member_ `bool bTabOpen;` — Whether or not the tab is presently open (some tabs, such as the 'debug' tab, start off closed if not explicitly enabled)
- L98 _public member_ `TArray<TSharedRef<FLogLine>> TabLogLines;` — The list of log lines for this particular tab
- L101 _public member_ `TSharedPtr<SListView<TSharedRef<FLogLine>>> LogListView;` — Reference to the log list view for the tab
- L105 _public member_ `TArray<TSharedPtr<SWidget>> FindWidgets;` — The list of widgets for the 'Find' bar
- L108 _public member_ `TSharedPtr<SEditableTextBox> FindBox;` — The text box for the 'Find' bar
- L111 _public member_ `TSharedPtr<SBorder> FindErrorLabel;` — The label that's displayed when there's an error searching, or searching past the start/end of the list
- L114 _public member_ `TSharedPtr<STextBlock> FindErrorText;` — The text block for the above label
- L117 _public member_ `FString LastFind;` — Caches the text of the last search
- L120 _public member_ `bool bLastFindWasUp;` — Whether or not the last search direction was upwards
- L123 _public member_ `bool bHighlightFind;` — Whether or not to highlight text, from searches
- L127 _public member_ `FName TabIdName;` — Automatically generated name given to the tab
- L132 _public member_ `TWeakPtr<SDockTab> TabWidget;` — @todo JohnB: Convert to shared pointer, once/if you implement closing of tabs - the closing code, should then unset this value
- L138 _public function_ `FLogTabInfo(FString InLabel, FString InToolTip, ELogType InFilter=ELogType::All, uint8 InPriority=255, bool bInTabOpen=true) : Label(InLabel) , ToolTip(InToolTip) , Filter(InFilter) , Priority(InPriority) , bTabOpen(bInTabOpen) , TabLogLines() , LogListView() , FindWidgets() , FindBox() , FindErrorLabel() , FindErrorText() , LastFind() , bLastFindWasUp(false) , bHighlightFind(true) , TabWidget()`

#### class `SLogWidget`  
`class SLogWidget : public SCompoundWidget`  
_L163-367_
- inherits: `SCompoundWidget`
- L166 _public function_ `SLATE_BEGIN_ARGS(SLogWidget) : _bStatusWidget(false) , _ExpectedFilters(ELogType::None)`
- L172 _public function_ `SLATE_ARGUMENT(bool, bStatusWidget) SLATE_ARGUMENT(ELogType, ExpectedFilters) SLATE_END_ARGS() SLogWidget() : SCompoundWidget() , LogLines() , LogTabs() , SuspendButtonText() , ConsoleContextList() , DefaultConsoleContext(TEXT("")) , ConsoleComboBox() , ConsoleTextBox() , LogWidgetCommands(NULL) , bAutoScroll(true) , OnSuspendClicked() , OnDeveloperClicked() , OnConsoleCommand()` — Whether or not this is the unit-test-status window
- L199 _public prototype_ `void Construct(const FArguments& Args);` — Widget constructor
- L208 _protected prototype_ `TSharedRef<FTabManager::FLayout> InitializeTabLayout(const FArguments& Args);` — Initializes the LogTabInfo array and tab formatting, and returns the log tab formatting layout @param Args	The widget constructions args @return		The layout to be used for initializing the tab widgets
- L213 _protected prototype_ `TSharedRef<SDockTab> SpawnLogTab(const FSpawnTabArgs& InSpawnTabArgs);` — Spawns an individual tab for the log list view
- L220 _protected prototype_ `TSharedPtr<FLogTabInfo> GetActiveTabInfo() const;` — Returns a reference to the LogTabs entry, for the currently active tab @return		The LogTabs entry, for the currently active tab
- L231 _public prototype_ `void AddLine(ELogType InLogType, TSharedRef<FString> LogLine, FSlateColor LogColor=FSlateColor::UseForeground(), bool bTakeTabFocus=false);` — Adds a log line to the log window @param InLogType			The type of log output this is (for filtering) @param LogLine			The log line @param LogColor			The colour to apply to the log line @param bTakeTabFocus		If this log line isn't displayed on the currently focused tab, switch focus to a tab that does show it
- L240 _public prototype_ `void OnSuspendStateChanged(ESuspendState InSuspendState);` — Notification from the unit test (through a delegate), that the server suspend state has changed (for the button text) @param InSuspendState	The new server suspend state
- L251 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyboardEvent) override;` — Called after a key is pressed when this widget has keyboard focus @param	MyGeometry The Geometry of the widget receiving the event @param	InKeyboardEvent  Keyboard event @return  Returns whether the event was handled, along with other possible actions
- L256 _protected prototype_ `void OnCopy();` — Called when the 'Copy' context button is clicked
- L263 _protected prototype_ `bool CanCopy() const;` — Used to determine whether 'Copy' is currently a valid action @return	Whether or not a copy can be performed right now
- L268 _protected prototype_ `void OnFind();` — Called when the 'Find' context button is clicked
- L275 _protected prototype_ `bool CanFind() const;` — Used to determine whether 'Find' is currently a valid action @return	Whether or not find can be performed right now
- L283 _protected prototype_ `void ScrollToEnd(TSharedRef<FLogTabInfo> InTab);` — Scrolls the specified tab to the last entry @param InTab		The tab which should scroll to the end
- L292 _protected prototype_ `void ScrollToText(TSharedRef<FLogTabInfo> InTab, FString FindText, bool bSearchUp=false);` — Scrolls to the specified text, in the specified tab (starting from the currently selected line) @param InTab			The tab that the search is being performed in @param FindText		The text to find @param bSearchUp		Whether or not to search up instead of down
- L301 _protected prototype_ `bool CanAutoScroll(TSharedPtr<FLogTabInfo> InTab);` — Whether or not auto-scrolling is presently possible for the specified tab NOTE: Does NOT determine whether or not it is presently enabled though @param InTab		The tab to check @return			Whether or not auto-scrolling is possible
- L310 _protected prototype_ `void UpdateFindHighlight(TSharedPtr<FLogTabInfo> InTab, bool bHighlight, FString HighlightText=TEXT(""));` — Updates the find text highlighting for a tab @param InTab				The tab to update @param bHighlight		Whether or not highlighting has been enabled (NOTE: This often differs from the tabs bHighlightFind value) @param HighlightText		The text to highlight, if any
- L313 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L318 _protected member_ `TSharedPtr<FTabManager> LogTabManager;` — The log window tab manager
- L322 _protected member_ `TArray<TSharedRef<FLogLine>> LogLines;` — @todo JohnB: Don't get rid of this - will need it later on, to initialize tabs added on-the-fly
- L325 _protected member_ `TArray<TSharedRef<FLogTabInfo>> LogTabs;` — Holds information necessary for initializing and handling the state of each tab
- L330 _public member_ `TSharedPtr<STextBlock> SuspendButtonText;` — Reference to the suspend buttons text, so the text can be modified
- L334 _public member_ `TArray<TSharedPtr<FString>> ConsoleContextList;` — The list of available console command contexts (for the combo box)
- L337 _public member_ `FString DefaultConsoleContext;` — The default console command context (for the combo box)
- L341 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> ConsoleComboBox;` — The combo box for selecting the console command context
- L344 _protected member_ `TSharedPtr<SEditableTextBox> ConsoleTextBox;` — The console command text box
- L348 _protected member_ `TSharedPtr<FUICommandList> LogWidgetCommands;` — Log widget context-menu/shortcut-key commands
- L352 _protected member_ `bool bAutoScroll;` — Whether or not auto-scrolling is currently enabled
- L356 _public member_ `bool bAutoClose;` — Whether or not auto-closing the current window is enabled
- L360 _public member_ `FOnSuspendClicked OnSuspendClicked;` — Notification for suspend/resume button click
- L363 _public member_ `FOnDeveloperClicked OnDeveloperClicked;` — Notification for developer checkbox click
- L366 _public member_ `FOnConsoleCommand OnConsoleCommand;` — Delegate for handling UI-triggered console commands

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_DELEGATE(FOnSuspendClicked);` — Delegate for neatly passing on suspend/resume button click
- L28 _prototype_ `DECLARE_DELEGATE(FOnSuspendClicked);` — Delegate for neatly passing on suspend/resume button click
- L35 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDeveloperClicked, bool ) DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnConsoleCommand, FString , FString );` — Delegate for passing on 'developer' mode checkbox clicks @param bDeveloperMode	Whether developer mode has been enabled/disabled
- L35 _prototype_ `DECLARE_DELEGATE_OneParam(FOnDeveloperClicked, bool ) DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnConsoleCommand, FString , FString );` — Delegate for passing on 'developer' mode checkbox clicks @param bDeveloperMode	Whether developer mode has been enabled/disabled
- L44 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnConsoleCommand, FString , FString );` — Delegate for passing on console commands from the UI, to the unit test @param CommandContext	The context (local/server/client?) for the console command @param Command			The command to be executed @return					Whether or not the command was handled - determines if the UI wipes the command textbox

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/UI/SLogWindow.h` (Public)


#### class `SLogWindow`  
`class SLogWindow : public SWindow`  
_L25-69_
- inherits: `SWindow`
- L28 _public function_ `SLATE_BEGIN_ARGS(SLogWindow) : _bStatusWindow(false) , _ExpectedFilters(ELogType::None)`
- L33 _public function_ `SLATE_ARGUMENT(bool, bStatusWindow) SLATE_ARGUMENT(ELogType, ExpectedFilters) SLATE_END_ARGS() SLogWindow() : LogWidget(NULL) , MultiOnWindowClosed() , bHasMoved(false)`
- L45 _public prototype_ `void Construct(const FArguments& InArgs, FString InTitle, float WindowPosX, float WindowPosY, float WindowWidth, float WindowHeight);`
- L48 _public prototype_ `void NotifyWindowClosed(const TSharedRef<SWindow>& ClosedWindow);`
- L50 _public prototype_ `void NotifyWindowMoved(const TSharedRef<SWindow>& MovedWindow);`
- L58 _public prototype_ `FReply NotifySuspendClicked();` — Event notification for the 'SUSPEND/RESUME' button @return	Returns whether the event was handled or not
- L62 _public member_ `TSharedPtr<SLogWidget> LogWidget;` — The log widget, which is the primary widget contained in this window
- L65 _public member_ `FMultiOnWindowClosed MultiOnWindowClosed;` — Multicast OnWindowClosed notifications
- L68 _public member_ `bool bHasMoved;` — Whether or not the window has moved, since creation (used to detect windows coming out of minimize state)

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMultiOnWindowClosed, const TSharedRef<SWindow>& );` — Setup a multicast version of the standard OnWindowClosed delegate @param ClosedWindow	The window that has closed
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMultiOnWindowClosed, const TSharedRef<SWindow>& );` — Setup a multicast version of the standard OnWindowClosed delegate @param ClosedWindow	The window that has closed

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/UI/SMultiSelectTableRow.h` (Public)


#### class `SMultiSelectTableRow`  
`template <typename ItemType> class SMultiSelectTableRow : public STableRow<ItemType>`  
_L19-67_
- inherits: `STableRow<ItemType>`
- desc: SMultiSelectTableRow Implements a SListView row, that supports selection of multiple rows, using just the mouse
- L22 _public function_ `SMultiSelectTableRow() : STableRow<ItemType>()`
- L27 _public function_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L51 _public function_ `virtual void OnDragEnter(FGeometry const& MyGeometry, FDragDropEvent const& DragDropEvent) override`

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/UnitLogging.h` (Public)


#### enum `ELogType`  
`enum class ELogType : uint32`  
_L31-78_
- desc: Used to help identify what type of log is being processed NOTE: This enum is not compatible with UENUM (that requires uint8)
- L33 _public enumerator_ `None = 0x00000000` — Not set
- L36 _public enumerator_ `OriginUnitTest = 0x00000001` — What part of the engine the log message originates from locally (may not be set)
- L37 _public enumerator_ `OriginEngine = 0x00000002` — Log originating from an engine event in the unit test (e.g. unit test Tick)
- L38 _public enumerator_ `OriginNet = 0x00000004` — Log originating from netcode for current unit test (specifically net receive)
- L39 _public enumerator_ `OriginConsole = 0x00000008` — Log originating from a console command (typically from the unit test window)
- L40 _public enumerator_ `OriginVoid = 0x00000010` — Log which should have no origin, and which should be ignored by log capturing
- L42 _public enumerator_ `OriginMask = OriginUnitTest | OriginEngine | OriginNet | OriginConsole | OriginVoid`
- L46 _public enumerator_ `Local = 0x00000080` — What class of unit test log this is
- L47 _public enumerator_ `Server = 0x00000100` — Log from a server instance (displayed in 'Server' tab)
- L48 _public enumerator_ `Client = 0x00000200` — Log from a client instance (displayed in 'Client' tab)
- L52 _public enumerator_ `GlobalStatus = 0x00000400` — What class of unit test status log this is (UNIT_LOG vs UNIT_STATUS_LOG/STATUS_LOG)
- L53 _public enumerator_ `UnitStatus = 0x00000800` — Status placed within the unit test window
- L56 _public enumerator_ `StatusImportant = 0x00001000` — Status log modifiers (used with the UNIT_LOG and UNIT_STATUS_LOG/STATUS_LOG macro's)
- L57 _public enumerator_ `StatusSuccess = 0x00002000 | StatusImportant` — Success event status
- L58 _public enumerator_ `StatusWarning = 0x00004000 | StatusImportant` — Warning event status
- L59 _public enumerator_ `StatusFailure = 0x00008000 | StatusImportant` — Failure event status
- L60 _public enumerator_ `StatusError = 0x00010000 | StatusFailure` — Error/Failure event status, that triggers an overall unit test failure
- L61 _public enumerator_ `StatusDebug = 0x00020000` — Debug status (displayed in the 'Debug' tab)
- L62 _public enumerator_ `StatusAdvanced = 0x00040000` — Status event containing advanced/technical information
- L63 _public enumerator_ `StatusVerbose = 0x00080000` — Status event containing verbose information
- L64 _public enumerator_ `StatusAutomation = 0x00100000` — Status event which should be printed out to the automation tool
- L68 _public enumerator_ `StyleBold = 0x00200000` — Log output style modifiers
- L69 _public enumerator_ `StyleItalic = 0x00400000` — Output text in italic
- L70 _public enumerator_ `StyleUnderline = 0x00800000` — Output pseudo-underline text (add newline and --- chars; UE can't underline)
- L71 _public enumerator_ `StyleMonospace = 0x01000000` — Output monospaced text (e.g. for list tab formatting); can't use bold/italic
- L73 _public enumerator_ `All = 0xFFFFFFFF`
- L77 _public enumerator_ `FocusMask = OriginConsole` — Log lines that should request focus when logged (i.e. if not displayed in the current tab, switch to a tab that does display)

#### class `FUnitLogInterface`  
`class FUnitLogInterface`  
_L304-402_
- desc: Implements an interface for using the UNIT_LOG etc. macros above, within a class
- L310 _public function_ `FUnitLogInterface() : LogColor(FSlateColor::UseForeground())` — Base constructor
- L315 _public function_ `virtual ~FUnitLogInterface()`
- L326 _public function_ `virtual bool IsConnectionLogSource(UNetConnection* InConnection)` — Whether or not this log interface is the source of a UNetConnection - used for deciding where to direct, UNetConnection log hooks @param InConnection	The connection to check @return				Whether or not the connection is associated with this log interface
- L338 _public function_ `virtual bool IsTimerLogSource(UObject* InTimerDelegateObject)` — Whether or not this log interface is the source of an FTimerManager delegate object, used for hooking logs triggered during global timer manager delegates. @param InTimerDelegateObject		The UObject that a timer delegate is tied to @return							Whether or not the object is associated with this log interface
- L357 _public function_ `virtual void NotifyLocalLog(ELogType InLogType, const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category)` — For implementation in subclasses, for helping to track local log entries related to a unit test. This covers logs from within the unit test, and (for UClientUnitTest) from processing net packets related to a unit test. NOTE: The parameters are the same as the unprocessed log 'serialize' parameters, to convert to a string, use: FOutputDeviceHelper::FormatLogLine(Verbosity, Category, Data, GPrintLogTimes) NOTE: Verbosity ELogVerbosity::SetColor is a special category, whose log messages can be ignored. @param InLogType		The type of local log message this is @param Data			The base log message being written @param Verbosity		The warning/filter level for the log message @param Category		The log message category (LogNet, LogNetTraffic etc.)
- L367 _public function_ `virtual void NotifyStatusLog(ELogType InLogType, const TCHAR* Data)` — As above, except for log entries directed towards the Unit Test Status window. @param InLogType		The type of local log message this is @param Data			The base log message being written
- L377 _public function_ `virtual void SetLogColor(FSlateColor InLogColor)` — Override the default log color @param InLogColor	The new log color to use
- L385 _public function_ `FORCEINLINE void ClearLogColor()` — Resets the log color to default
- L396 _public prototype_ `virtual UUnitTest* GetUnitTest();` — If the log interface is tied to a unit test, this matches it up to an active unit test @return	Returns the unit test pointer, or nullptr if this isn't a unit test
- L401 _protected member_ `FSlateColor LogColor;` — Overrides the colour of UNIT_LOG log messages

#### class `FUnitLogRedirect`  
`class FUnitLogRedirect : public FUnitLogInterface`  
_L408-472_
- inherits: `FUnitLogInterface`
- desc: Implements a UNIT_LOG interface, which redirects to another unit log interface (e.g. redirect MinimalClient UNIT_LOG's to a UnitTest)
- L414 _public function_ `FUnitLogRedirect() : FUnitLogInterface() , TargetInterface(nullptr)` — Base constructor
- L425 _public function_ `void SetInterface(FUnitLogInterface* InInterface)` — Sets the interface we should redirect to @param InInterface	The interface to redirect to
- L439 _public function_ `virtual void NotifyLocalLog(ELogType InLogType, const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category) override`
- L448 _public function_ `virtual void NotifyStatusLog(ELogType InLogType, const TCHAR* Data) override`
- L456 _public function_ `virtual UUnitTest* GetUnitTest() override`
- L461 _public function_ `virtual void SetLogColor(FSlateColor InLogColor)`
- L471 _private member_ `FUnitLogInterface* TargetInterface;` — The interface to redirect to

#### Free symbols / members of external scopes

- L80 _prototype_ `ENUM_CLASS_FLAGS(ELogType);`
- L90 _externvar_ `extern FUnitLogInterface* GActiveLogInterface;` — Used by to aid in hooking log messages triggered by unit tests
- L93 _externvar_ `extern ELogType GActiveLogTypeFlags;` — The current ELogType flag modifiers, associated with a UNIT_LOG or UNIT_STATUS_LOG/STATUS_LOG call
- L97 _externvar_ `extern FUnitLogInterface* GActiveLogEngineEvent;` — @todo #JohnB: See if this needs updating @todo #JohnB: Document
- L98 _externvar_ `extern UWorld* GActiveLogWorld;` — @todo #JohnBReview: Does this make other log hooks redundant?
- L101 _externvar_ `extern UNetConnection* GActiveReceiveUnitConnection;` — Keeps track of the UUnitTestNetConnection, currently processing received data (to aid with selective log hooking)
- L112 _function_ `inline ELogType OptionalFlags(ELogType InFlags=ELogType::None)` — Helper function, for macro defines - allows the 'UnitLogTypeFlags' macro parameters below, to be optional
- L119 _macro_ `#define UNIT_LOG_BEGIN(UnitLogObj, UnitLogTypeFlags) \`
- L125 _macro_ `#define UNIT_LOG_END() \`
- L130 _macro_ `#define UNIT_LOG_VOID_START() \`
- L133 _macro_ `#define UNIT_LOG_VOID_END() \`
- L145 _macro_ `#define UNIT_LOG_OBJ(UnitLogObj, UnitLogTypeFlags, Format, ...) \` — Special log macro for unit tests, to aid in hooking logs from these unit tests NOTE: These logs are scoped @param UnitLogObj		Reference to the unit test this log message is originating from @param UnitLogTypeFlags	(Optional) The additional ELogFlags flags, to be applied to this log @param Format			The format of the log message
- L178 _macro_ `#define UNIT_LOG(UnitLogTypeFlags, Format, ...) \`
- L185 _macro_ `#define STATUS_LOG_BASE(UnitLogTypeFlags, Format, ...) \` — Special log macro, for messages that should be printed to the unit test status window
- L201 _macro_ `#define STATUS_LOG_OBJ(UnitLogObj, UnitLogTypeFlags, Format, ...) \`
- L244 _macro_ `#define STATUS_LOG(UnitLogTypeFlags, Format, ...) STATUS_LOG_OBJ(nullptr, UnitLogTypeFlags, Format, ##__VA_ARGS__)`
- L249 _macro_ `#define UNIT_STATUS_LOG_OBJ(UnitLogObj, UnitLogTypeFlags, Format, ...) \` — Version of the above, for unit test status window entries, which are from specific unit tests
- L254 _macro_ `#define UNIT_STATUS_LOG(UnitLogTypeFlags, Format, ...) \`
- L261 _macro_ `#define STATUS_SET_COLOR(InColor) \` — Changes/resets the colour of messages printed to the unit test status window
- L267 _macro_ `#define STATUS_RESET_COLOR() \`
- L276 _macro_ `#define UNIT_EVENT_BEGIN(UnitLogObj) \`
- L280 _macro_ `#define UNIT_EVENT_END \`
- L287 _macro_ `#define UNIT_EVENT_CLEAR \` — Stores and then clears all engine-log-capture events (in order to prevent capture of a new log entry) NOTE: Do not clear GActiveLogUnitTest here, as some macros that use this, rely upon that
- L296 _macro_ `#define UNIT_EVENT_RESTORE \` — Restores all stored/cleared engine-log-capture events

### `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Public/UnitTestEnvironment.h` (Public)


#### class `FUnitTestEnvironment`  
`class FUnitTestEnvironment`  
_L27-226_
- desc: Class for handling per-game implementation of unit test environmental defaults
- L34 _public function_ `FUnitTestEnvironment() : UnitTest(nullptr)`
- L43 _public function_ `static void Register()` — Registers the unit test environment, with the environment list IMPORTANT: This MUST be implemented in every subclass, and the subclass version MUST called, within your modules 'StartupModule'
- L55 _public prototype_ `static void AddUnitTestEnvironment(FString Game, FUnitTestEnvironment* Env);` — Adds a new environment to the unit test environment list @param Game	The game the unit test environment is for @param Env	The environment being added
- L57 _public function_ `virtual ~FUnitTestEnvironment()`
- L65 _private function_ `static void Unregister()` — Winds-down the UnitTestEnvironments map; does not need implementation in subclasses
- L88 _public function_ `virtual uint32 GetDefaultUnitTestTimeout()` — Returns the default/minimum timeout that unit tests should use, for the current game @return	The default unit test timeout for the current game
- L99 _public prototype_ `virtual FString GetDefaultMap(EUnitTestFlags UnitTestFlags);` — Returns the default map name, that should be used with unit tests, for the current game @param UnitTestFlags		The flags for the current unit test - affects chosen map in some games @return					Returns the default map name
- L108 _public prototype_ `FString GetDefaultServerParameters(FString InLogCmds=TEXT(""), FString InExecCmds=TEXT(""));` — Returns the default parameters for launched servers @param InLogCmds		Used to pass in -LogCmds= entries, which need special parsing (don't specify the -LogCmds= part) @param InExecCmds	Used to pass in -ExecCmds= entries, which need special parsing (don't specify the -ExecCmds= part) @return				Returns the default parameters
- L117 _public function_ `virtual void SetupDefaultServerParameters(FString& OutCommandline, FString& OutLogCmds, FString& OutExecCmds)` — Sets up the default server parameters, specifying commandline and '-*Cmds=x' separately (combined within parent function above) @param OutCommandline	Passes in the current state of the commandline, for modification @param OutLogCmds		Passes in the current LogCmds list, for modification @param OutExecCmds		Passes in the current ExecCmds list, for modification
- L126 _public prototype_ `FString GetDefaultClientParameters();` — Returns the default parameters for launched clients @return	Returns the default parameters
- L133 _public function_ `virtual void SetupDefaultClientParameters(FString& OutCommandline)` — Sets up the default client parameters, specifying a (potentially already modified) commandline for modification @param OutCommandline	Passes in the current state of the commandline, for modification
- L142 _public prototype_ `virtual FString GetDefaultClientConnectURL();` — Returns the default URL that minimal clients should use, when connecting to a server, for the current game @return	Returns the default URL
- L151 _public prototype_ `void GetServerProgressLogs(const TArray<FString>*& OutStartProgressLogs, const TArray<FString>*& OutReadyLogs, const TArray<FString>*& OutTimeoutResetLogs);` — Returns server log messages, for the current game, that indicate progress in starting up @param OutStartProgressLogs	Outputs partial server log messages that indicate progress starting up @param OutReadyLogs			Outputs partial server log messages that indicate startup is complete @param OutTimeoutResetLogs	Outputs partial server log messages that indicate resetting unit-test/connection timeout is required
- L161 _public function_ `virtual void InitializeServerProgressLogs(TArray<FString>& StartProgressLogs, TArray<FString>& ReadyLogs, TArray<FString>& TimeoutResetLogs)` — Called when initializing the static arrays, containing the server progress logs @param StartProgressLogs		The static array containing logs indicating progress starting up @param ReadyLogs				The static array containing logs indicating startup is complete @param TimeoutResetLogs		The static array containing logs indicating resetting of unit-test/connection timeout is required
- L172 _public prototype_ `void GetClientProgressLogs(const TArray<FString>*& OutTimeoutResetLogs);` — Returns client log messages, for the current game, that indicate progress logs for resetting unit test timeout @param OutTimeoutResetLogs	Outputs partial client log messages that indicate resetting unit-test/connection timeout is required
- L179 _public function_ `virtual void InitializeClientProgressLogs(TArray<FString>& TimeoutResetLogs)` — Called when initializing the static arrays, containing the client progress logs @param TimeoutResetLogs		The static array containing logs indicating resetting of unit-test/connection timeout is required
- L190 _public prototype_ `void GetProgressBlockingProcesses(const TArray<FString>*& OutBlockingProcesses);` — Returns child process names, that indicate progress blockers in starting up (e.g. shader compiler) All child processes, including server/client child processes (and their children) are checked. @param OutBlockingProcesses	Outputs process names, for processes which indicate a blocking task, which is blocking progression
- L197 _public function_ `virtual void InitializeProgressBlockingProcesses(TArray<FString>& BlockingProcesses)` — Called when initializing the static arrays, containing the progress blocking processes @param BlockingProcesses		The static array containing processes indicating a blocking task
- L208 _public function_ `virtual void HandleClientPlayer(EUnitTestFlags UnitTestFlags, APlayerController* PC)` — Executes game-specific handling, upon client unit tests initializing the client PlayerController @param UnitTestFlags	The flags for the current unit test - affects handling, depending upon game @param PC			The PlayerController being initialized
- L216 _public function_ `virtual void InitializeUnitTasks()` — If the game environment requires special/complex setup (e.g. player auth before join), then UnitTask's for handling complex setup, are added here.
- L225 _protected member_ `UUnitTest* UnitTest;` — The unit test being initialized using the current environment (WARNING: Will be nullptr for legacy unit tests)

#### Free symbols / members of external scopes

- L21 _externvar_ `extern TMap<FString, FUnitTestEnvironment*> UnitTestEnvironments;` — The list of registered unit test environments, mapped to game name (unit test modules should add to this, within StartupModule)
