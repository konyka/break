# Runtime / StageDataCore

- module root: `Source/Runtime/VirtualProduction/StageDataCore`
- headers: 2; symbols: 66
- symbol kinds: class=1, enum=4, enumerator=9, function=10, macro=2, member=16, namespace=2, prototype=9, struct=12, variable=1
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/VirtualProduction/StageDataCore/Public/IStageDataProvider.h` (Public)


#### class `IStageDataProvider`  
`class IStageDataProvider : public IModularFeature`  
_L23-110_
- inherits: `IModularFeature`
- desc: Interface for the data provider modular feature used in engine. Also contains methods for modules that would like to send data about stage status
- L26 _public function_ `virtual ~IStageDataProvider()`
- L28 _public member_ `static FName ModularFeatureName;`
- L36 _public function_ `template<typename MessageType, typename... Args> static bool SendMessage(EStageMessageFlags Flags, Args&&... args)` — Generic send message to support constructor parameters directly and temp object created
- L48 _public function_ `template<typename MessageType, typename... Args> static bool SendMessage(EStageMessageFlags Flags, MessageType& Message)` — Specialized send message for lvalue type without a temp object
- L59 _public function_ `template<typename MessageType, typename... Args> static bool SendMessage(EStageMessageFlags Flags, MessageType&& Message)` — Specialized send message for rvalue type without a temp object
- L72 _private function_ `template<typename MessageType> static bool SendMessage(MessageType&& Message, EStageMessageFlags InFlags)` — Internal method where all send messages are funneled before being sent to the data provider instance
- L109 _protected prototype_ `virtual bool SendMessageInternal(FStageDataBaseMessage* Payload, UScriptStruct* Type, EStageMessageFlags InFlags) = 0;` — Method to actually send message from a data provider to monitors

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace StageProviderUtils` (scope `UE`)
- L14 _variable_ `static const FQualifiedFrameTime InvalidTime = FQualifiedFrameTime(FFrameTime(FFrameNumber(-1)), FFrameRate(-1, -1));` (scope `UE::StageProviderUtils`)

### `Source/Runtime/VirtualProduction/StageDataCore/Public/StageMessages.h` (Public)


#### enum `EStageMessageFlags`  
`enum class EStageMessageFlags : uint8`  
_L26-32_
- reflection: `UENUM()`
- desc: Message flags configuring how a message is sent
- L28 _public enumerator_ `None = 0`
- L31 _public enumerator_ `Reliable = 1 << 0` — Sends this message as reliable, to make sure it's received by the receivers

#### enum `EStageDataProviderState`  
`enum class EStageDataProviderState : uint8`  
_L37-45_
- reflection: `UENUM()`
- desc: States that a DataProvider can be in
- L40 _public enumerator_ `Active` — Actively receiving messages from
- L42 _public enumerator_ `Inactive` — Timeout intervaled occured between provider messages
- L44 _public enumerator_ `Closed` — Provider closed

#### enum `EStageCriticalStateEvent`  
`enum class EStageCriticalStateEvent : uint8`  
_L50-56_
- reflection: `UENUM()`
- desc: Different events associated with stage critical state
- L53 _public enumerator_ `Enter` — Critical state has been entered
- L55 _public enumerator_ `Exit` — Critical state has been exited

#### enum `EStageLoadingState`  
`enum class EStageLoadingState : uint8`  
_L60-66_
- reflection: `UENUM()`
- desc: Different events associated with stage critical state
- L63 _public enumerator_ `PreLoad` — Asset loading has started.
- L65 _public enumerator_ `PostLoad` — Asset loading has finished.

#### struct `FStageInstanceDescriptor`  
`struct FStageInstanceDescriptor`  
_L74-101_
- reflection: `USTRUCT(MinimalAPI)`
- desc: Holds descriptive information about that data providers. Information that won't change for a session Used when monitor and provider connects
- L84 _public member_ `FString MachineName;` — `UPROPERTY()` — Machine name read from FPlatformProcess::ComputerName()
- L88 _public member_ `uint32 ProcessId = 0;` — `UPROPERTY()` — ProcessId read from FPlatformProcess::GetCurrentProcessId
- L92 _public member_ `FString RolesStringified;` — `UPROPERTY()` — Simple stringified view of the roles of that instance
- L96 _public member_ `FName FriendlyName;` — `UPROPERTY()` — Friendly name for this Unreal instance. If empty, this will be MachineName - ProcessId
- L100 _public member_ `int32 SessionId = INDEX_NONE;` — `UPROPERTY()` — Session Id that may be used to differentiate different sessions on the network

#### struct `FStageDataBaseMessage`  
`struct FStageDataBaseMessage`  
_L107-127_
- reflection: `USTRUCT(MinimalAPI)`
- desc: Base structure for all stage monitoring messages
- L112 _public prototype_ `virtual ~FStageDataBaseMessage() = default;`
- L122 _public member_ `int32 StageMessageVersion = 1;` — `UPROPERTY()` — Provision for versioning if we need to differentiate version of messages. All stage machines should be running the same version of Unreal but if it's not the case, having a version in the message will be useful to know about it.
- L126 _public member_ `FGuid Identifier;` — `UPROPERTY()` — Identifier of this instance

#### struct `FStageMonitorBaseMessage`  
`struct FStageMonitorBaseMessage : public FStageDataBaseMessage`  
_L136-139_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FStageDataBaseMessage`
- desc: Base structure for all monitor messages

#### struct `FStageProviderDiscoveryMessage`  
`struct FStageProviderDiscoveryMessage : public FStageMonitorBaseMessage`  
_L145-160_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FStageMonitorBaseMessage`
- desc: Message broadcasted periodically by the monitor to discover new providers
- L150 _public prototype_ `FStageProviderDiscoveryMessage() = default;`
- L151 _public function_ `FStageProviderDiscoveryMessage(FStageInstanceDescriptor&& InDescriptor) : Descriptor(MoveTemp(InDescriptor))`
- L159 _public member_ `FStageInstanceDescriptor Descriptor;` — `UPROPERTY()` — Detailed description of that monitor

#### struct `FStageMonitorCloseMessage`  
`struct FStageMonitorCloseMessage : public FStageMonitorBaseMessage`  
_L166-169_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FStageMonitorBaseMessage`
- desc: Message sent when monitor is going down to let know linked providers

#### struct `FStageProviderMessage`  
`struct FStageProviderMessage : public FStageDataBaseMessage`  
_L175-192_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FStageDataBaseMessage`
- desc: Base Provider messages listened by monitors
- L181 _public function_ `virtual FString ToString() const` — Method to override if a detailed description is desired in the monitor event viewer
- L187 _public member_ `FQualifiedFrameTime FrameTime;` — `UPROPERTY()` — FrameTime of the sender. It's expected to have all stage machines using the same timecode provider to play in the same referential
- L191 _public member_ `FDateTime DateTime;` — `UPROPERTY()` — DateTime of the sender. Used to keep track of messages order through Timecode rollover.

#### struct `FStageProviderEventMessage`  
`struct FStageProviderEventMessage : public FStageProviderMessage`  
_L198-201_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FStageProviderMessage`
- desc: Base Provider messages that are events

#### struct `FStageProviderPeriodicMessage`  
`struct FStageProviderPeriodicMessage : public FStageProviderMessage`  
_L207-210_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FStageProviderMessage`
- desc: Base Provider messages that are periodic

#### struct `FStageProviderCloseMessage`  
`struct FStageProviderCloseMessage : public FStageProviderEventMessage`  
_L216-219_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FStageProviderEventMessage`
- desc: Message sent by Providers to notify monitors they are closing down

#### struct `FStageProviderDiscoveryResponseMessage`  
`struct FStageProviderDiscoveryResponseMessage : public FStageProviderEventMessage`  
_L225-241_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FStageProviderEventMessage`
- desc: Response to a received discovery message sent by providers
- L230 _public prototype_ `FStageProviderDiscoveryResponseMessage() = default;`
- L231 _public function_ `FStageProviderDiscoveryResponseMessage(FStageInstanceDescriptor&& InDescriptor) : Descriptor(MoveTemp(InDescriptor))`
- L240 _public member_ `FStageInstanceDescriptor Descriptor;` — `UPROPERTY()` — Detailed description of that provider

#### struct `FCriticalStateProviderMessage`  
`struct FCriticalStateProviderMessage : public FStageProviderEventMessage`  
_L247-269_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FStageProviderEventMessage`
- desc: Message sent to notify about critical state change.
- L253 _public prototype_ `FCriticalStateProviderMessage() = default;`
- L255 _public function_ `FCriticalStateProviderMessage(EStageCriticalStateEvent InEvent, FName InSourceName) : State(InEvent), SourceName(InSourceName)`
- L260 _public prototype_ `virtual FString ToString() const override;`
- L264 _public member_ `EStageCriticalStateEvent State = EStageCriticalStateEvent::Enter;` — `UPROPERTY(VisibleAnywhere, Category = "CriticalState")` — Event for this critical state
- L268 _public member_ `FName SourceName;` — `UPROPERTY(VisibleAnywhere, Category = "CriticalState")` — Source of the critical state. i.e. TakeName, CustomRecorder, etc...

#### struct `FAssetLoadingStateProviderMessage`  
`struct FAssetLoadingStateProviderMessage : public FStageProviderEventMessage`  
_L275-295_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FStageProviderEventMessage`
- desc: Message sent to indicate that the node has entered or exited a loading state.
- L280 _public prototype_ `FAssetLoadingStateProviderMessage() = default;`
- L282 _public function_ `FAssetLoadingStateProviderMessage(EStageLoadingState InState, const FString& InAssetName) : LoadingState(InState), AssetName(InAssetName)`
- L286 _public prototype_ `virtual FString ToString() const override;`
- L290 _public member_ `EStageLoadingState LoadingState = EStageLoadingState::PreLoad;` — `UPROPERTY(VisibleAnywhere, Category = "AssetLoading")` — Event for this critical state
- L294 _public member_ `FString AssetName;` — `UPROPERTY(VisibleAnywhere, Category = "AssetLoading")` — Name of the asset currently loading.

#### Free symbols / members of external scopes

- L19 _macro_ `#define ENABLE_STAGEMONITOR_LOGGING (1 && !NO_LOGGING && !(UE_BUILD_SHIPPING || UE_BUILD_TEST))` — Global define to disable any data provider sending logic
- L21 _macro_ `#define UE_API STAGEDATACORE_API`
- L33 _prototype_ `ENUM_CLASS_FLAGS(EStageMessageFlags);`
