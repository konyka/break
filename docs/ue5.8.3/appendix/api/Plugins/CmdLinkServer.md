# Plugins / CmdLinkServer

- module root: `Plugins/CmdLinkServer/Source/CmdLinkServer`
- headers: 1; symbols: 28
- symbol kinds: class=1, function=5, member=10, prototype=11, struct=1
- PrivateDependencyModuleNames: CoreUObject, Engine, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/CmdLinkServer/Source/CmdLinkServer/Public/CmdLinkServer.h` (Public)


#### class `FCmdLinkServerModule`  
`class FCmdLinkServerModule : public IModuleInterface`  
_L10-57_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _public prototype_ `void Enable();`
- L17 _public prototype_ `void Disable();`
- L18 _public prototype_ `void OnKeyChanged(const FString& NewKey);`
- L19 _public function_ `static FCmdLinkServerModule* Get()`
- L26 _public prototype_ `void BeginAsyncCommand(const FString& CommandName, const TArray<FString>& Params);` — call this from a command that will take more than one frame to complete this forces the CmdLink to wait until EndAsyncCommand is called before shutting down
- L29 _public prototype_ `void EndAsyncCommand(const FString& CommandName, const TArray<FString>& Params);` — call this at the end of a command that took more than one frame to complete
- L31 _private prototype_ `bool Read();`
- L32 _private prototype_ `bool Execute(FString& Response);`
- L33 _private prototype_ `void InitStateMachine();`
- L34 _private prototype_ `int32 OnPipeClosed();`
- L48 _private member_ `bool bEnabled = false;`
- L49 _private member_ `FPlatformNamedPipe NamedPipe;`
- L50 _private member_ `TSharedPtr<FTickStateMachine> StateMachine;`
- L51 _private member_ `int32 ArgC = 0;`
- L52 _private member_ `TArray<FAnsiStringBuffer> ArgV;`
- L53 _private member_ `int32 NextStringSize = 0;`
- L54 _private member_ `bool bAwaitAsyncCommand = false;`
- L55 _private member_ `TQueue<TArray<uint8>> PendingReply;`
- L56 _private member_ `float SleepConnectTimer = -1.f;`

#### struct `FCmdLinkServerModule::FAnsiStringBuffer`  
`struct FAnsiStringBuffer`  
_L37-45_
- desc: scoped ANSICHAR c-string buffer that auto-casts to an FString
- L39 _public function_ `FAnsiStringBuffer(int32 Size) : Data(new ANSICHAR[Size]{0})`
- L40 _public function_ `~FAnsiStringBuffer()`
- L41 _public function_ `operator FString() const`
- L42 _public function_ `operator ANSICHAR*() const`
- L44 _public member_ `ANSICHAR* Data;`
