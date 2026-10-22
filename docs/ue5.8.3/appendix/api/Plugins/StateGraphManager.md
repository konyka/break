# Plugins / StateGraphManager

- module root: `Plugins/Experimental/StateGraph/Source/StateGraphManager`
- headers: 5; symbols: 55
- symbol kinds: class=7, delegate=1, externvar=5, function=7, macro=2, member=8, namespace=13, prototype=11, typedef=1
- PrivateDependencyModuleNames: CoreUObject
- PublicDependencyModuleNames: Core, Engine, StateGraph

### `Plugins/Experimental/StateGraph/Source/StateGraphManager/Public/ClientJoinManager.h` (Public)


#### class `UClientJoinManager`  
`class UClientJoinManager : public UGameInstanceSubsystem, public UE::FStateGraphManagerTracked`  
_L21-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameInstanceSubsystem,UE::FStateGraphManagerTracked`
- desc: Subsystem manager that other modules and subsystems can depend on to add ClientJoin state graph delegates with.
- L26 _public function_ `virtual FName GetStateGraphName() const override`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ClientJoin` (scope `UE`)
- L14 _namespace_ `namespace Name` (scope `UE::ClientJoin`)
- L16 _externvar_ `extern const FName StateGraph;` (scope `UE::ClientJoin::Name`)

### `Plugins/Experimental/StateGraph/Source/StateGraphManager/Public/PreLoginAsyncManager.h` (Public)


#### class `UE::PreLoginAsync::FOptions`  
`class FOptions : public UE::FStateGraphNode`  
_L37-66_
- inherits: `UE::FStateGraphNode`
- desc: State graph node that is used to store options that PreLoginAsync was called with.
- L40 _public function_ `static FOptionsPtr Get(UE::FStateGraph& StateGraph)`
- L45 _public function_ `FOptions(TObjectPtr<UPreLoginAsyncManager> InManager, const FString& InOptions, const FString& InAddress, const FUniqueNetIdRepl& InUniqueId, const AGameModeBase::FOnPreLoginCompleteDelegate& InOnComplete) : UE::FStateGraphNode(Name::Options), WeakManager(InManager), Options(InOptions), Address(InAddress), UniqueId(InUniqueId), OnComplete(InOnComplete)`
- L55 _public function_ `virtual void Start() override`
- L61 _public member_ `TWeakObjectPtr<UPreLoginAsyncManager> WeakManager;`
- L62 _public member_ `FString Options;`
- L63 _public member_ `FString Address;`
- L64 _public member_ `FUniqueNetIdRepl UniqueId;`
- L65 _public member_ `AGameModeBase::FOnPreLoginCompleteDelegate OnComplete;`

#### class `UPreLoginAsyncManager`  
`class UPreLoginAsyncManager : public UWorldSubsystem, public UE::FStateGraphManager`  
_L74-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem,UE::FStateGraphManager`
- desc: Subsystem manager that other modules and subsystems can depend on to register PreLoginAsync state graph delegates with.
- L79 _public function_ `virtual FName GetStateGraphName() const override`
- L89 _public prototype_ `void InitializeStateGraph(UE::FStateGraph& StateGraph, const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, const AGameModeBase::FOnPreLoginCompleteDelegate& OnComplete);` — Add the state graph to the map of running requests, detecting and removing conflicts if needed. This also creates the options node from the original PreLoginAsync options. This isn't part of a Create() override so the OnComplete delegate can use the created state graph if needed.
- L95 _public prototype_ `static void CompleteLogin(UE::FStateGraph& StateGraph, const FString& Error);` — Call the OnComplete delegate to finish the PreLoginAsync call and remove the state graph from the map of running requests. As long as no references are kept to the shared pointer, this will free the state graph and all nodes. The state graph should no longer be used after this is called.
- L99 _private member_ `TMap<FUniqueNetIdRepl, UE::FStateGraphRef> RunningStateGraphs;` — Map of pending PreLoginAsync requests currently running. Only one per NetId is allowed.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API STATEGRAPHMANAGER_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace PreLoginAsync` (scope `UE`)
- L25 _namespace_ `namespace Name` (scope `UE::PreLoginAsync`)
- L27 _externvar_ `extern const FName StateGraph;` (scope `UE::PreLoginAsync::Name`)
- L28 _externvar_ `extern const FName Options;` (scope `UE::PreLoginAsync::Name`)
- L34 _typedef_ `using FOptionsPtr = TSharedPtr<FOptions, ESPMode::ThreadSafe>;` (scope `UE::PreLoginAsync`)

### `Plugins/Experimental/StateGraph/Source/StateGraphManager/Public/RegisterServerManager.h` (Public)


#### class `URegisterServerManager`  
`class URegisterServerManager : public UWorldSubsystem, public UE::FStateGraphManagerTracked`  
_L21-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem,UE::FStateGraphManagerTracked`
- desc: Subsystem manager that other modules and subsystems can depend on to add RegisterServer state graph delegates with.
- L26 _public function_ `virtual FName GetStateGraphName() const override`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RegisterServer` (scope `UE`)
- L14 _namespace_ `namespace Name` (scope `UE::RegisterServer`)
- L16 _externvar_ `extern const FName StateGraph;` (scope `UE::RegisterServer::Name`)

### `Plugins/Experimental/StateGraph/Source/StateGraphManager/Public/RestartServerManager.h` (Public)


#### class `URestartServerManager`  
`class URestartServerManager : public UWorldSubsystem, public UE::FStateGraphManagerTracked`  
_L21-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem,UE::FStateGraphManagerTracked`
- desc: Subsystem manager that other modules and subsystems can depend on to add RestartServer state graph delegates with.
- L26 _public function_ `virtual FName GetStateGraphName() const override`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RestartServer` (scope `UE`)
- L14 _namespace_ `namespace Name` (scope `UE::RestartServer`)
- L16 _externvar_ `extern const FName StateGraph;` (scope `UE::RestartServer::Name`)

### `Plugins/Experimental/StateGraph/Source/StateGraphManager/Public/StateGraphManager.h` (Public)


#### class `UE::FStateGraphManager`  
`class FStateGraphManager`  
_L24-39_
- L27 _public prototype_ `virtual ~FStateGraphManager();`
- L28 _public prototype_ `virtual FName GetStateGraphName() const = 0;`
- L31 _public prototype_ `virtual void AddCreateDelegate(const FStateGraphManagerCreateDelegate& Delegate);` — Add a delegate to be called when creating a new state graph instance. These are called in the order they were added.
- L34 _public prototype_ `virtual UE::FStateGraphPtr Create(const FString& ContextName = FString());` — Create an untracked state graph instance.
- L38 _protected member_ `TArray<FStateGraphManagerCreateDelegate> CreateDelegates;` — Array of registered delegates that are called in order when creating a new state graph instance.

#### class `UE::FStateGraphManagerTracked`  
`class FStateGraphManagerTracked : public FStateGraphManager`  
_L41-58_
- inherits: `FStateGraphManager`
- L44 _public prototype_ `virtual ~FStateGraphManagerTracked();`
- L47 _public prototype_ `virtual UE::FStateGraphPtr Create(const FString& ContextName = FString()) override;` — Create a tracked state graph instance by ContextName. Only one instance per context is allowed, so the context should be a unique ID representing that instance.
- L50 _public prototype_ `virtual UE::FStateGraphPtr Find(const FString& ContextName = FString()) const;` — Find a tracked state graph instance by ContextName.
- L53 _public prototype_ `virtual void Remove(const FString& ContextName = FString());` — Remove a tracked state graph instance by ContextName, if one exists.
- L57 _protected member_ `TMap<FString, UE::FStateGraphRef> StateGraphs;` — Map of state graphs currently tracked by context name.

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API STATEGRAPHMANAGER_API`
- L19 _namespace_ `namespace UE`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FStateGraphManagerCreateDelegate, UE::FStateGraph& );`
- L22 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FStateGraphManagerCreateDelegate, UE::FStateGraph& );` (scope `UE`)
