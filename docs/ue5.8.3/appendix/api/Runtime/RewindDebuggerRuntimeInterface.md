# Runtime / RewindDebuggerRuntimeInterface

- module root: `Source/Runtime/RewindDebuggerRuntimeInterface`
- headers: 1; symbols: 13
- symbol kinds: class=1, function=5, macro=1, member=1, namespace=3, prototype=2
- PrivateDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/RewindDebuggerRuntimeInterface/Public/RewindDebuggerRuntimeInterface/IRewindDebuggerRuntimeExtension.h` (Public)


#### class `IRewindDebuggerRuntimeExtension`  
`class IRewindDebuggerRuntimeExtension : public IModularFeature`  
_L38-82_
- inherits: `IModularFeature`
- desc: IRewindDebuggerRuntimeExtension Interface class for extensions which add functionality to the rewind debugger runtime. These get callbacks on recording start/stop, to enable/disable trace channels and on clear to clean up any cached data. They can also register and handle messages for remote sessions debugging.
- L41 _public prototype_ `virtual ~IRewindDebuggerRuntimeExtension() = default;`
- L43 _public member_ `static const FName ModularFeatureName;`
- L50 _public function_ `virtual void RecordingStarted()` — This method is called once the trace connection is established (i.e., FTraceAuxiliary::OnConnection delegate) which can be from any thread. This is the method to override to enable trace channels specific to the extension.
- L55 _public function_ `virtual void RecordingStopped()` — This method is called from the game thread when recording gets stopped
- L60 _public function_ `virtual void Clear()` — This method is called from the game thread before executing the "start recording" command (i.e., FTraceAuxiliary::Start/Relay methods)
- L70 _public function_ `virtual void RegisterMessageHandlers(const TSharedPtr<UE::TraceBasedDebuggers::FRemoteSessionsManager>& InRemoteSessionsManager, FMessageEndpointBuilder& InMessageEndpointBuilder)` — This method allows extensions to register their own message type handlers to the message system and send response using the remote sessions manager. @param InRemoteSessionsManager The remote sessions manager that can be used to send response messages @param InMessageEndpointBuilder The message endpoint builder where message type handlers needs to be registered.
- L79 _public function_ `virtual void RegisterMessageTypes(const TSharedPtr<UE::TraceBasedDebuggers::FRemoteSessionsManager>& InRemoteSessionsManager, FMessageEndpoint& InMessageEndpoint)` — This method allows extensions to register their own message types in the remote sessions manager and subscribe in the message endpoint. @param InRemoteSessionsManager The remote sessions manager that can be used to register supported messages @param InMessageEndpoint The message endpoint to subscribe to specific message types

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API REWINDDEBUGGERRUNTIMEINTERFACE_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L24 _namespace_ `namespace RewindDebugger`
- L26 _prototype_ `extern void IterateExtensions(TFunctionRef<void(IRewindDebuggerRuntimeExtension* Extension)> IteratorFunction);` (scope `RewindDebugger`)
