# Plugins / Gauntlet

- module root: `Plugins/Experimental/Gauntlet/Source/Gauntlet`
- headers: 4; symbols: 43
- symbol kinds: class=4, function=7, macro=4, member=5, prototype=22, struct=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine, UnrealEd

### `Plugins/Experimental/Gauntlet/Source/Gauntlet/Public/GauntletModule.h` (Public)


#### struct `FGauntletStates`  
`struct FGauntletStates`  
_L16-19_
- desc: Gauntlet states. Define your own states by inheriting from this or some other form that you see fit.
- L18 _public member_ `static FName Initialized;`

#### class `FGauntletModule`  
`class FGauntletModule : public IModuleInterface`  
_L31-103_
- inherits: `IModuleInterface`
- desc: Main Gauntlet Module. This is module is responsible for managing its underlying controllers and propagating events and state changes to them as necessary. After initialization you should be prepared to feed this module with states that your controllers can respond to. This can be done either manually (BroadcastStateChange), through one of the helpers (e.g. SetGameStateToTestStateMapping), or a combination of both.
- L44 _public prototype_ `virtual void SetGameStateToTestStateMapping(const TMap<UClass*, FName>& Mapping) = 0;` — This is a convenient way of binding a list of AGameState  types to your own state defines. When there is a state change in the world (e.g. from loading a new map) the mapped state type will be broadcast to all controllers. @param: 	Mapping - A map e.g. [AGameStateSomethingClass, StateSomething] @return: void
- L55 _public prototype_ `virtual void SetWorldToTestStateMapping(const TMap<FString, FName>& Mapping) = 0;` — This is a convenient way of binding a list of maps types to your own state defines. When there is a state change in the world (e.g. from loading a new map) the mapped state type will be broadcast to all controllers. @param: 	Mapping - A map e.g. [TEXT("FrontendMap"), StateFrontend] @return: void
- L64 _public prototype_ `virtual void BroadcastStateChange(FName NewState) = 0;` — Manually Broadcasts a state change to all current Gauntlet controllers. This can be used as an alternative or addition to the functions above for broadcasting state changes to running controllers. @param: 	FName		New State @return: void
- L71 _public prototype_ `virtual FName GetCurrentState() const = 0;` — Returns the current  state @return: FName
- L78 _public prototype_ `virtual double GetTimeInCurrentState() const = 0;` — Returns the time spent in the current state @return: double
- L83 _public prototype_ `virtual void SetScreenshotPeriod(float Period) = 0;` — Sets the rate for screenshots to be taken (default = 0)
- L88 _public prototype_ `virtual void MarkHeartbeatActive(const FString& OptionalStatusMessage = FString()) = 0;` — Mark the next heartbeat as active. If a status message is given, immediately log an active heartbeat with that message.
- L93 _public prototype_ `virtual UGauntletTestController* GetTestController(UClass* ControllerClass) = 0;` — Returns the first controller (if any) matching the provided name
- L99 _public function_ `template< class T > inline T* GetTestController()` — Templated casty version of the above

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAUNTLET_API`
- L108 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGauntlet, Log, All);` — Logging category

### `Plugins/Experimental/Gauntlet/Source/Gauntlet/Public/GauntletTestController.h` (Public)


#### class `UGauntletTestController`  
`class UGauntletTestController : public UObject`  
_L23-110_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base class for games to implement test controllers that use the Gauntlet native framework. This is a very thin class that is created automatically based on command line params (-gauntlet=MyControllerName) and provides easily overridden functions that represent state changes and ticking In essence your derived class should implement logic that starts and monitors a test, then calls EndTest(Result) when the desired criteria are met (or not!)
- L32 _public prototype_ `UGauntletTestController(const FObjectInitializer& ObjectInitializer);` — Default constructur
- L33 _public prototype_ `virtual ~UGauntletTestController();`
- L40 _public function_ `virtual void OnInit()` — Called when the controller is first initialized
- L45 _public function_ `virtual void OnPreMapChange()` — Called prior to a map change
- L50 _public function_ `virtual void OnPostMapChange(UWorld* World)` — Called after a map change. GetCurrentMap() will now return the new map
- L55 _public function_ `virtual void OnTick(float TimeDelta)` — Called periodically to let the controller check and control state
- L61 _public function_ `virtual void OnStateChange(FName OldState, FName NewState)` — Called when a state change is applied to the module. States are game-driven. GetCurrentState() == OldState until this function returns
- L66 _public prototype_ `UWorld* GetWorld() const override;` — Return the current world
- L71 _public prototype_ `APlayerController* GetFirstPlayerController() const;` — Helper function that returns the first player controller in the world (may be null depending on when called).
- L78 _protected prototype_ `FName GetCurrentState() const;` — Returns the current state applied to Gauntlet
- L83 _protected prototype_ `double GetTimeInCurrentState() const;` — Return the time since OnStateChange was called with the current state
- L88 _protected prototype_ `FString GetCurrentMap() const;` — Return the name of the current persistent map
- L93 _protected prototype_ `static void EndTest(int32 ExitCode = 0);` — Called to end testing and exit the app with provided code, static to avoid test instance state/lifetime dependency
- L98 _protected prototype_ `FGauntletModule* GetGauntlet();` — Returns the gauntlet module running this test
- L104 _protected prototype_ `void MarkHeartbeatActive(const FString& OptionalStatusMessage = FString());` — Marks the next heartbeat as active and immediately forces a heartbeat with the given status message if one is specified. Test controllers should call this regularly as purposeful actions happens or meaningful states are achieved within the test.
- L108 _private member_ `FGauntletModule* ParentModule;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GAUNTLET_API`

### `Plugins/Experimental/Gauntlet/Source/Gauntlet/Public/GauntletTestControllerBootTest.h` (Public)


#### class `UGauntletTestControllerBootTest`  
`class UGauntletTestControllerBootTest : public UGauntletTestController`  
_L11-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGauntletTestController`
- L17 _protected function_ `virtual bool IsBootProcessComplete() const`
- L18 _protected prototype_ `virtual void OnTick(float TimeDelta) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAUNTLET_API`

### `Plugins/Experimental/Gauntlet/Source/Gauntlet/Public/GauntletTestControllerErrorTest.h` (Public)


#### class `UGauntletTestControllerErrorTest`  
`class UGauntletTestControllerErrorTest : public UGauntletTestController`  
_L11-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGauntletTestController`
- L17 _protected member_ `float ErrorDelay;`
- L18 _protected member_ `FString ErrorType;`
- L19 _protected member_ `bool RunOnServer;`
- L21 _protected prototype_ `void OnInit() override;`
- L22 _protected prototype_ `void OnTick(float TimeDelta) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAUNTLET_API`
