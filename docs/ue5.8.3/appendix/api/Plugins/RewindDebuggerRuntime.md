# Plugins / RewindDebuggerRuntime

- module root: `Plugins/Animation/GameplayInsights/Source/RewindDebuggerRuntime`
- headers: 5; symbols: 65
- symbol kinds: class=4, function=4, macro=3, member=12, namespace=10, prototype=28, struct=3, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, RewindDebuggerRuntimeInterface, TraceBasedDebuggers, TraceLog

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerRuntime/Internal/RewindDebuggerRemoteSessionsHandler.h` (Internal)


#### struct `UE::RewindDebugger::FStartRecordingCommand`  
`struct FStartRecordingCommand : public UE::TraceBasedDebuggers::FStartRecordingCommandMessage`  
_L13-16_
- reflection: `USTRUCT()`
- inherits: `UE::TraceBasedDebuggers::FStartRecordingCommandMessage`

#### struct `UE::RewindDebugger::FStopRecordingCommand`  
`struct FStopRecordingCommand : public UE::TraceBasedDebuggers::FStopRecordingCommandMessage`  
_L20-23_
- reflection: `USTRUCT()`
- inherits: `UE::TraceBasedDebuggers::FStopRecordingCommandMessage`

#### struct `UE::RewindDebugger::FSessionsHandler`  
`struct FSessionsHandler : TraceBasedDebuggers::IRemoteSessionsHandler`  
_L29-35_
- inherits: `TraceBasedDebuggers::IRemoteSessionsHandler`
- desc: Remote sessions handler to handle RewindDebugger specific message types.
- L31 _public prototype_ `virtual void OnCreatingMessageEndpoint(const TSharedPtr<TraceBasedDebuggers::FRemoteSessionsManager>&, FMessageEndpointBuilder&) override;`
- L32 _public prototype_ `virtual void OnSubscribingMessageTypes(const TSharedPtr<TraceBasedDebuggers::FRemoteSessionsManager>&, FMessageEndpoint&) override;`
- L33 _public prototype_ `virtual void OnBuildingFullSessionInfoResponseMessage(TraceBasedDebuggers::FFullSessionInfoResponseMessage&) override;`
- L34 _public prototype_ `virtual void OnHandlingFullSessionInfoResponseMessage(const TraceBasedDebuggers::FFullSessionInfoResponseMessage&, const TSharedPtr<TraceBasedDebuggers::FSessionInfo>&) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API REWINDDEBUGGERRUNTIME_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RewindDebugger` (scope `UE`)

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerRuntime/Private/RewindDebuggerAnimationRuntime.h` (Private)


#### class `RewindDebugger::FRewindDebuggerAnimationRuntime`  
`class FRewindDebuggerAnimationRuntime : public IRewindDebuggerRuntimeExtension`  
_L13-32_
- inherits: `IRewindDebuggerRuntimeExtension`
- L16 _public function_ `virtual void RecordingStarted() override`
- L21 _public function_ `virtual void RecordingStopped() override`
- L26 _public function_ `virtual void Clear() override`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerRuntime/Private/RewindDebuggerRuntimeModule.h` (Private)
_(no declarations extracted)_

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerRuntime/Public/RewindDebuggerEngineEditorBridge.h` (Public)


#### class `UE::RewindDebugger::FRewindDebuggerEngineEditorBridge`  
`class FRewindDebuggerEngineEditorBridge : public TraceBasedDebuggers::FEngineEditorBridge`  
_L21-58_
- inherits: `TraceBasedDebuggers::FEngineEditorBridge`
- desc: Object that bridges the RewindDebugger runtime module and the Engine/Editor. This layer is not strictly necessary for RewindDebugger since its runtime currently has access to the engine module, but we use it to share a common stack of layers with other trace-based debuggers.
- L24 _public prototype_ `FRewindDebuggerEngineEditorBridge();`
- L26 _public prototype_ `~FRewindDebuggerEngineEditorBridge() = default;`
- L28 _public prototype_ `static FRewindDebuggerEngineEditorBridge& Get();`
- L31 _public prototype_ `static bool IsInstantiated();` — @return Whether the static instance has been created (i.e., Get() was called and teardown is required)
- L34 _private prototype_ `virtual void OnInitializeInternal() override;`
- L35 _private prototype_ `virtual void OnTearDownInternal() override;`
- L36 _private prototype_ `virtual void OnRecordingStartedInternal() override;`
- L37 _private prototype_ `virtual void OnRecordingStoppedInternal() override;`
- L38 _private prototype_ `virtual void BuildRecordingStatusInternal(TraceBasedDebuggers::FRecordingStatusMessage& OutStatusMessage) const override;`
- L40 _private prototype_ `bool AddOnScreenRecordingMessage(float DummyDeltaTime = 0.1f);`
- L41 _private prototype_ `void RemoveOnScreenRecordingMessage();`
- L42 _private prototype_ `void HandleRecordingStartFailed(const FText& InFailureReason) const;`
- L43 _private prototype_ `void HandlePIEStarted(UGameInstance* GameInstance);`
- L45 _private prototype_ `void HandleTraceConnectionDetailsUpdated() const;`
- L47 _private member_ `FDelegateHandle RecordingStartedHandle;`
- L48 _private member_ `FDelegateHandle RecordingStoppedHandle;`
- L49 _private member_ `FDelegateHandle RecordingStartFailedHandle;`
- L50 _private member_ `uint64 RecordingMessageKey = 0;`
- L53 _private member_ `FDelegateHandle PIEStartedHandle;`
- L56 _private member_ `FTSTicker::FDelegateHandle DeferredShowMessageOnScreenHandle;`
- L57 _private member_ `static bool bIsInstantiated;`

#### class `UE::RewindDebugger::FRewindDebuggerEngineEditorBridge`  
`class FRewindDebuggerEngineEditorBridge`  
_L67-71_
- L24 _public prototype_ `FRewindDebuggerEngineEditorBridge();`
- L26 _public prototype_ `~FRewindDebuggerEngineEditorBridge() = default;`
- L28 _public prototype_ `static FRewindDebuggerEngineEditorBridge& Get();`
- L31 _public prototype_ `static bool IsInstantiated();` — @return Whether the static instance has been created (i.e., Get() was called and teardown is required)
- L34 _private prototype_ `virtual void OnInitializeInternal() override;`
- L35 _private prototype_ `virtual void OnTearDownInternal() override;`
- L36 _private prototype_ `virtual void OnRecordingStartedInternal() override;`
- L37 _private prototype_ `virtual void OnRecordingStoppedInternal() override;`
- L38 _private prototype_ `virtual void BuildRecordingStatusInternal(TraceBasedDebuggers::FRecordingStatusMessage& OutStatusMessage) const override;`
- L40 _private prototype_ `bool AddOnScreenRecordingMessage(float DummyDeltaTime = 0.1f);`
- L41 _private prototype_ `void RemoveOnScreenRecordingMessage();`
- L42 _private prototype_ `void HandleRecordingStartFailed(const FText& InFailureReason) const;`
- L43 _private prototype_ `void HandlePIEStarted(UGameInstance* GameInstance);`
- L45 _private prototype_ `void HandleTraceConnectionDetailsUpdated() const;`
- L47 _private member_ `FDelegateHandle RecordingStartedHandle;`
- L48 _private member_ `FDelegateHandle RecordingStoppedHandle;`
- L49 _private member_ `FDelegateHandle RecordingStartFailedHandle;`
- L50 _private member_ `uint64 RecordingMessageKey = 0;`
- L53 _private member_ `FDelegateHandle PIEStartedHandle;`
- L56 _private member_ `FTSTicker::FDelegateHandle DeferredShowMessageOnScreenHandle;`
- L57 _private member_ `static bool bIsInstantiated;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API REWINDDEBUGGERRUNTIME_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RewindDebugger` (scope `UE`)
- L65 _namespace_ `namespace UE`
- L65 _namespace_ `namespace RewindDebugger` (scope `UE`)

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerRuntime/Public/RewindDebuggerRuntime/RewindDebuggerRuntime.h` (Public)


#### class `RewindDebugger::FRewindDebuggerRuntime`  
`class FRewindDebuggerRuntime : public UE::TraceBasedDebuggers::FRuntimeModule`  
_L27-59_
- inherits: `UE::TraceBasedDebuggers::FRuntimeModule`
- L30 _public prototype_ `FRewindDebuggerRuntime();`
- L32 _public prototype_ `static void Initialize();`
- L33 _public prototype_ `static void Shutdown();`
- L34 _public function_ `static FRewindDebuggerRuntime* Instance()`
- L39 _public prototype_ `void StartRecording();`
- L44 _public member_ `FSimpleMulticastDelegate ClearRecording;`
- L45 _public member_ `UE::TraceBasedDebuggers::FRecordingStateChangedDelegate RecordingStarted;`
- L46 _public member_ `UE::TraceBasedDebuggers::FRecordingStartFailedDelegate RecordingStartFailed;`
- L47 _public member_ `UE::TraceBasedDebuggers::FRecordingStateChangedDelegate RecordingStopped;`
- L51 _private prototype_ `virtual void OnRecordingStartingInternal() override;`
- L52 _private prototype_ `virtual void OnRecordingStartedInternal() override;`
- L53 _private prototype_ `virtual void OnRecordingStartFailedInternal(const FText& FailureReason) override;`
- L54 _private prototype_ `virtual void OnRecordingStoppedInternal() override;`
- L55 _private prototype_ `virtual void OnEnableRequiredTraceChannelsInternal() override;`
- L58 _private member_ `static FRewindDebuggerRuntime* InternalInstance;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API REWINDDEBUGGERRUNTIME_API`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRewindDebuggerRuntime, Log, All);`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace RewindDebugger` (scope `UE`)
- L20 _variable_ `static constexpr FGuid DebuggerGuid = FGuid(0xC4E4CF24, 0x57DB4959, 0x8EDBD741, 0x673D25EC);` (scope `UE::RewindDebugger`)
- L24 _namespace_ `namespace RewindDebugger`
