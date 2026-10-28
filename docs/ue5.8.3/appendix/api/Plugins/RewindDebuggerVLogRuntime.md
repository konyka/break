# Plugins / RewindDebuggerVLogRuntime

- module root: `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLogRuntime`
- headers: 3; symbols: 41
- symbol kinds: class=2, function=2, member=18, namespace=4, prototype=6, struct=8, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, RewindDebuggerRuntimeInterface, TraceBasedDebuggers, TraceLog

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLogRuntime/Private/RewindDebuggerVLogRuntime.h` (Private)


#### class `UE::RewindDebugger::FRewindDebuggerVLogRuntime`  
`class FRewindDebuggerVLogRuntime : public IRewindDebuggerRuntimeExtension`  
_L15-25_
- inherits: `IRewindDebuggerRuntimeExtension`
- L18 _public prototype_ `virtual void RecordingStarted() override;`
- L19 _public prototype_ `virtual void RecordingStopped() override;`
- L20 _public prototype_ `virtual void RegisterMessageHandlers(const TSharedPtr<TraceBasedDebuggers::FRemoteSessionsManager>&, FMessageEndpointBuilder&) override;`
- L21 _public prototype_ `virtual void RegisterMessageTypes(const TSharedPtr<TraceBasedDebuggers::FRemoteSessionsManager>&, FMessageEndpoint&) override;`
- L24 _private member_ `bool bWasRecording = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RewindDebugger` (scope `UE`)

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLogRuntime/Private/RewindDebuggerVLogRuntimeModule.h` (Private)


#### class `FRewindDebuggerVLogRuntimeModule`  
`class FRewindDebuggerVLogRuntimeModule : public IModuleInterface`  
_L12-23_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;`
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _private member_ `UE::RewindDebugger::FRewindDebuggerVLogRuntime VLogExtension;`

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLogRuntime/Public/RewindDebuggerVLogRuntimeTypes.h` (Public)


#### struct `UE::RewindDebugger::FLogCategoryVerbosity`  
`struct FLogCategoryVerbosity`  
_L19-33_
- reflection: `USTRUCT()`
- L24 _public member_ `FName CategoryName;` — `UPROPERTY()`
- L27 _public member_ `uint8 Verbosity = 0;` — `UPROPERTY()`
- L29 _public function_ `ELogVerbosity::Type GetVerbosity() const`

#### struct `UE::RewindDebugger::FVerbosityFilteringStateChangeCommandMessage`  
`struct FVerbosityFilteringStateChangeCommandMessage`  
_L36-42_
- reflection: `USTRUCT()`
- L41 _public member_ `bool bEnableFiltering = false;` — `UPROPERTY()`

#### struct `UE::RewindDebugger::FVerbosityFilteringStateChangeResponseMessage`  
`struct FVerbosityFilteringStateChangeResponseMessage`  
_L45-54_
- reflection: `USTRUCT()`
- L50 _public member_ `FGuid InstanceID = FGuid();` — `UPROPERTY()`
- L53 _public member_ `bool bFilteringEnabled = false;` — `UPROPERTY()`

#### struct `UE::RewindDebugger::FLogCategoryStateChangeCommandMessage`  
`struct FLogCategoryStateChangeCommandMessage`  
_L57-63_
- reflection: `USTRUCT()`
- L62 _public member_ `FLogCategoryVerbosity NewState;` — `UPROPERTY()`

#### struct `UE::RewindDebugger::FLogCategoryStateChangeResponseMessage`  
`struct FLogCategoryStateChangeResponseMessage`  
_L66-75_
- reflection: `USTRUCT()`
- L71 _public member_ `FGuid InstanceID = FGuid();` — `UPROPERTY()`
- L74 _public member_ `FLogCategoryVerbosity NewState;` — `UPROPERTY()`

#### struct `UE::RewindDebugger::FLogCategoryStatusQueryMessage`  
`struct FLogCategoryStatusQueryMessage`  
_L78-84_
- reflection: `USTRUCT()`
- L83 _public member_ `TArray<FLogCategoryVerbosity> Categories;` — `UPROPERTY()`

#### struct `UE::RewindDebugger::FLogCategoryStatusQueryResponseMessage`  
`struct FLogCategoryStatusQueryResponseMessage`  
_L87-99_
- reflection: `USTRUCT()`
- L92 _public member_ `FGuid InstanceID = FGuid();` — `UPROPERTY()`
- L95 _public member_ `bool bUsingVerbosityFilterWhenRecording = false;` — `UPROPERTY()`
- L98 _public member_ `TArray<FLogCategoryVerbosity> Categories;` — `UPROPERTY()`

#### struct `UE::RewindDebugger::FVLogExtensionSessionData`  
`struct FVLogExtensionSessionData`  
_L107-122_
- reflection: `USTRUCT()`
- desc: Structure specific to RewindDebugger VLog extension to store the states of the log categories in the session info struct. The struct is stored as a DebuggerSpecificSessionData inside UE::TraceBasedDebuggers::FSessionInfo and get be retrieved using GetDebuggerData<UE::RewindDebugger::FVLogExtensionSessionData>().
- L111 _public member_ `TMap<FName, FLogCategoryVerbosity> LogCategoriesStatesByName;`
- L113 _public member_ `FSimpleDelegate OnDataUpdated;`
- L114 _public member_ `bool bUsingVerbosityFilterWhenRecording = false;`
- L115 _public member_ `bool bPendingRefresh = false;`
- L117 _public function_ `void NotifyDataUpdated()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RewindDebugger` (scope `UE`)
- L16 _variable_ `constexpr ELogVerbosity::Type UnknownVerbosity = ELogVerbosity::NumVerbosity;` (scope `UE::RewindDebugger`) — Specific value for category verbosity levels waiting for their status provided by the remote process or for categories not found by the remote process (edge case for now, but will be useful when allowing users to type manually a category)
