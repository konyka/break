# Developer / TurnkeyIO

- module root: `Source/Developer/TurnkeyIO`
- headers: 3; symbols: 44
- symbol kinds: class=4, delegate=1, function=3, macro=1, member=14, prototype=21
- PrivateDependencyModuleNames: Core, CoreUObject, Json, Slate, SlateCore, Sockets, ToolWidgets

### `Source/Developer/TurnkeyIO/Private/STurnkeyIOWidgets.h` (Private)


#### class `STurnkeyReadInputModal`  
`class STurnkeyReadInputModal : public SCompoundWidget`  
_L14-32_
- inherits: `SCompoundWidget`
- L16 _private function_ `SLATE_BEGIN_ARGS( STurnkeyReadInputModal )`
- L17 _private prototype_ `SLATE_ARGUMENT( FString, Prompt );`
- L18 _private prototype_ `SLATE_ARGUMENT( FString, Default );`
- L19 _private prototype_ `SLATE_EVENT( FOnTurnkeyActionComplete, OnFinished );`
- L20 _private prototype_ `SLATE_END_ARGS();`
- L23 _public prototype_ `void Construct( const FArguments& InArgs );`
- L26 _private prototype_ `void FinishAction();`
- L28 _private member_ `FOnTurnkeyActionComplete OnFinished;`
- L29 _private member_ `FString Prompt;`
- L30 _private member_ `FString Default;`
- L31 _private member_ `FString Value;`

#### class `STurnkeyReadInputIntModal`  
`class STurnkeyReadInputIntModal : public SCompoundWidget`  
_L36-58_
- inherits: `SCompoundWidget`
- L38 _private function_ `SLATE_BEGIN_ARGS( STurnkeyReadInputIntModal )`
- L39 _private prototype_ `SLATE_ARGUMENT( FString, Prompt );`
- L40 _private prototype_ `SLATE_ARGUMENT( TArray<FString>, Options );`
- L41 _private prototype_ `SLATE_ARGUMENT( bool, IsCancellable );`
- L42 _private prototype_ `SLATE_ARGUMENT( int, DefaultValue );`
- L43 _private prototype_ `SLATE_EVENT( FOnTurnkeyActionComplete, OnFinished );`
- L44 _private prototype_ `SLATE_END_ARGS();`
- L47 _public prototype_ `void Construct( const FArguments& InArgs );`
- L50 _private prototype_ `void FinishAction();`
- L52 _private member_ `FString Prompt;`
- L53 _private member_ `TArray<FString> Options;`
- L54 _private member_ `bool bIsCancellable;`
- L55 _private member_ `int DefaultValue;`
- L56 _private member_ `int Value;`
- L57 _private member_ `FOnTurnkeyActionComplete OnFinished;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam( FOnTurnkeyActionComplete, TSharedPtr<class FJsonObject> );`
- L11 _prototype_ `DECLARE_DELEGATE_OneParam( FOnTurnkeyActionComplete, TSharedPtr<class FJsonObject> );`

### `Source/Developer/TurnkeyIO/Private/TurnkeyEditorIOServer.h` (Private)


#### class `FTurnkeyEditorIOServer`  
`class FTurnkeyEditorIOServer : public TSharedFromThis<FTurnkeyEditorIOServer>`  
_L15-32_
- inherits: `TSharedFromThis<FTurnkeyEditorIOServer>`
- L18 _public prototype_ `FTurnkeyEditorIOServer();`
- L19 _public prototype_ `~FTurnkeyEditorIOServer();`
- L21 _public prototype_ `FString GetUATParams() const;`
- L24 _private prototype_ `bool Start();`
- L25 _private prototype_ `void Stop();`
- L27 _private member_ `int Port;`
- L28 _private member_ `class FTurnkeyEditorIOServerRunnable* Runnable;`
- L29 _private member_ `class FRunnableThread* Thread;`
- L30 _private member_ `TSharedPtr<class FSocket> Socket;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define WITH_TURNKEY_EDITOR_IO_SERVER 1 // for IntelliSense`

### `Source/Developer/TurnkeyIO/Public/ITurnkeyIOModule.h` (Public)


#### class `ITurnkeyIOModule`  
`class ITurnkeyIOModule : public IModuleInterface`  
_L11-27_
- inherits: `IModuleInterface`
- desc: Interface for Turnkey IO module, used for when Turnkey requires user input
- L17 _public prototype_ `virtual FString GetUATParams() const = 0;` — Returns the command line arguments for passing to UAT
- L22 _public function_ `static ITurnkeyIOModule& Get()` — Returns a reference to the Turnkey IO module instance
