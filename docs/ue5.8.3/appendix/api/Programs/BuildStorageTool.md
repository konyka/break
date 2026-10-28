# Programs / BuildStorageTool

- module root: `Source/Programs/BuildStorageTool`
- headers: 8; symbols: 112
- symbol kinds: class=6, delegate=2, enum=2, enumerator=7, function=3, macro=12, member=31, namespace=2, prototype=39, struct=7, typedef=1
- PrivateDependencyModuleNames: Analytics, ApplicationCore, Core, DesktopPlatform, Json, OutputLog, PakFile, Projects, Slate, SlateCore, Sockets, StandaloneRenderer, StorageServerWidgets, StudioTelemetry, ToolWidgets, UnixCommonStartup, Zen
- PrivateIncludePathModuleNames: Launch

### `Source/Programs/BuildStorageTool/Private/BuildStorageTool.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBuildStorageTool, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBuildStorageTool, Log, All);`

### `Source/Programs/BuildStorageTool/Private/BuildStorageToolHelpWidget.h` (Private)


#### class `SBuildStorageToolHelpWidget`  
`class SBuildStorageToolHelpWidget final : public SCompoundWidget`  
_L8-18_
- inherits: `SCompoundWidget`
- L11 _public function_ `SLATE_BEGIN_ARGS(SBuildStorageToolHelpWidget)`
- L12 _public prototype_ `SLATE_ATTRIBUTE(const FBuildStorageToolParameters*, ToolParameters) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L17 _private member_ `const FBuildStorageToolParameters* ToolParameters;`

### `Source/Programs/BuildStorageTool/Private/BuildStorageToolIPC.h` (Private)


#### class `UE::BuildStorageTool::IMessage`  
`class IMessage`  
_L21-34_
- L24 _public prototype_ `virtual ~IMessage() = default;`
- L27 _public prototype_ `virtual void Write(FCbWriter& Writer) const = 0;` — Marshall the message to a CompactBinaryObject.
- L29 _public prototype_ `virtual bool TryRead(FCbObjectView Object) = 0;` — Unmarshall the message from a CompactBinaryObject.
- L31 _public prototype_ `virtual FGuid GetMessageType() const = 0;` — Return the Guid that identifies the message to the remote connection.
- L33 _public prototype_ `virtual const TCHAR* GetDebugName() const = 0;` — Return the debugname for diagnostics.

#### class `UE::BuildStorageTool::FMessageListenServer`  
`class FMessageListenServer`  
_L38-95_
- L41 _public prototype_ `FMessageListenServer();`
- L43 _public prototype_ `bool Start();`
- L44 _public prototype_ `void ShutdownJoin();`
- L46 _public member_ `FMessageReceivedDelegate OnMessageReceived;`
- L79 _private prototype_ `void ThreadLoop();`
- L80 _private prototype_ `void TickCommunication();`
- L81 _private prototype_ `EConnectionStatus TryReadPacket(FSocket& Socket, FReceiveBuffer& Buffer, TArray<FMarshalledMessage>& Messages, uint64 MaxPayloadLen);`
- L89 _private member_ `TArray<FClientState> ClientStates;`
- L90 _private member_ `FEventRef ShutdownEvent;`
- L91 _private member_ `FThread WorkerThread;`
- L92 _private member_ `FSocket* ListenSocket = nullptr;`
- L93 _private member_ `uint16 Port = 0;`
- L94 _private member_ `bool bWroteRendezvousFile = false;`

#### enum `UE::BuildStorageTool::FMessageListenServer::EConnectionStatus`  
`enum class EConnectionStatus`  
_L48-60_
- L51 _public enumerator_ `Okay` — Connection is still okay or operation succeeded.
- L53 _public enumerator_ `Terminated` — Connection failed and no further use of the Socket is possible.
- L55 _public enumerator_ `FormatError` — The Socket is still active but the data received was invalid and recovery is not possible.
- L57 _public enumerator_ `Failed` — The operation failed and the Socket is no longer usable.
- L59 _public enumerator_ `Incomplete` — The Socket is busy and the operation needs to be retried later

#### struct `UE::BuildStorageTool::FMessageListenServer::FReceiveBuffer`  
`struct FReceiveBuffer`  
_L62-71_
- L65 _public prototype_ `void Reset();`
- L67 _public member_ `FGuid MessageType;`
- L68 _public member_ `FUniqueBuffer Payload;`
- L69 _public member_ `uint64 BytesRead = 0;`
- L70 _public member_ `bool bParsedHeader = false;`

#### struct `UE::BuildStorageTool::FMessageListenServer::FMarshalledMessage`  
`struct FMarshalledMessage`  
_L73-77_
- L75 _public member_ `FGuid MessageType;`
- L76 _public member_ `FCbObject Object;`

#### struct `UE::BuildStorageTool::FMessageListenServer::FClientState`  
`struct FClientState`  
_L84-88_
- L86 _public member_ `FSocket* Socket = nullptr;`
- L87 _public member_ `FReceiveBuffer ReceiveBuffer;`

#### class `UE::BuildStorageTool::FMessageClient`  
`class FMessageClient`  
_L97-113_
- L100 _public prototype_ `FMessageClient();`
- L102 _public prototype_ `bool Start();`
- L103 _public prototype_ `bool SendSync(const IMessage& Message);`
- L106 _private prototype_ `void ThreadLoop();`
- L108 _private member_ `FEventRef ShutdownEvent;`
- L109 _private member_ `FThread WorkerThread;`
- L110 _private member_ `TUniquePtr<FSocket> Socket;`
- L111 _private member_ `uint16 Port = 0;`
- L112 _private member_ `bool bReady = false;`

#### enum `UE::BuildStorageTool::EUrlAction`  
`enum class EUrlAction : uint8`  
_L115-119_
- L117 _public enumerator_ `Highlight`
- L118 _public enumerator_ `HighlightAndDownload`

#### struct `UE::BuildStorageTool::FUrlMessage`  
`struct FUrlMessage : public IMessage`  
_L128-141_
- inherits: `IMessage`
- L131 _public prototype_ `FUrlMessage();`
- L132 _public prototype_ `virtual void Write(FCbWriter& Writer) const override;`
- L133 _public prototype_ `virtual bool TryRead(FCbObjectView Object) override;`
- L134 _public function_ `virtual FGuid GetMessageType() const override`
- L135 _public function_ `virtual const TCHAR* GetDebugName() const override`
- L138 _public member_ `EUrlAction Action;`
- L139 _public member_ `FString Url;`
- L140 _public member_ `static FGuid MessageType;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace BuildStorageTool` (scope `UE`)
- L17 _prototype_ `FString GetRendezvousFilePath();` (scope `UE::BuildStorageTool`)
- L18 _prototype_ `bool WriteRendezvousFileJson(const uint16 Port);` (scope `UE::BuildStorageTool`)
- L19 _prototype_ `bool ReadRendezvousFileJson(uint16& OutPort);` (scope `UE::BuildStorageTool`)
- L36 _typedef_ `typedef TMulticastDelegate<void(const IMessage& )> FMessageReceivedDelegate;` (scope `UE::BuildStorageTool`)
- L121 _prototype_ `FAnsiStringBuilderBase& operator<<(FAnsiStringBuilderBase& Builder, EUrlAction Action);` (scope `UE::BuildStorageTool`)
- L122 _prototype_ `FWideStringBuilderBase& operator<<(FWideStringBuilderBase& Builder, EUrlAction Action);` (scope `UE::BuildStorageTool`)
- L123 _prototype_ `FUtf8StringBuilderBase& operator<<(FUtf8StringBuilderBase& Builder, EUrlAction Action);` (scope `UE::BuildStorageTool`)
- L125 _prototype_ `bool TryLexFromString(EUrlAction& OutAction, FUtf8StringView String);` (scope `UE::BuildStorageTool`)
- L126 _prototype_ `bool TryLexFromString(EUrlAction& OutAction, FWideStringView String);` (scope `UE::BuildStorageTool`)

### `Source/Programs/BuildStorageTool/Private/BuildStorageToolStyle.h` (Private)


#### class `FBuildStorageToolStyle`  
`class FBuildStorageToolStyle`  
_L8-31_
- L14 _public prototype_ `static void Initialize();` — Set up specific styles for the storage server UI app
- L19 _public prototype_ `static void Shutdown();` — Tidy up on shut-down
- L24 _public prototype_ `static const ISlateStyle& Get();` — Access to singleton style object
- L27 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`
- L30 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;` — Singleton style object

### `Source/Programs/BuildStorageTool/Private/Parameters/BuildStorageToolParameters.h` (Private)


#### struct `FDocumentationLink`  
`struct FDocumentationLink`  
_L8-20_
- reflection: `USTRUCT()`
- L13 _public member_ `FString Text;` — `UPROPERTY()`
- L16 _public member_ `FString Tooltip;` — `UPROPERTY()`
- L19 _public member_ `FString Link;` — `UPROPERTY()`

#### struct `FGeneralParameters`  
`struct FGeneralParameters`  
_L23-29_
- reflection: `USTRUCT()`
- L28 _public member_ `TArray<FDocumentationLink> HelpLinks;` — `UPROPERTY()`

#### struct `FBuildStorageToolParameters`  
`struct FBuildStorageToolParameters`  
_L31-34_
- L33 _public member_ `FGeneralParameters GeneralParameters;`

### `Source/Programs/BuildStorageTool/Private/Parameters/BuildStorageToolParametersBuilder.h` (Private)


#### class `FBuildStorageToolParametersBuilder`  
`class FBuildStorageToolParametersBuilder`  
_L9-21_
- L12 _public prototype_ `FBuildStorageToolParametersBuilder();`
- L13 _public prototype_ `FBuildStorageToolParameters Build();`
- L16 _private member_ `FConfigFile* BuildStorageToolConfig;`
- L18 _private prototype_ `FGeneralParameters BuildGeneralParameters();`
- L20 _private prototype_ `FString SectionToText(const FConfigSection& InSection) const;`

### `Source/Programs/BuildStorageTool/Private/SMessageDialog.h` (Private)


#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMsgDlgResult, const TSharedRef<SWindow>&, EAppReturnType::Type);`
- L14 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnMsgDlgResult, const TSharedRef<SWindow>&, EAppReturnType::Type);`
- L16 _prototype_ `EAppReturnType::Type OpenModalMessageDialog_Internal(EAppMsgCategory InMessageCategory, EAppMsgType::Type InMessageType, const FText& InMessage, const FText& InTitle, const TSharedPtr<const SWidget>& ModalParent);`

### `Source/Programs/BuildStorageTool/Private/Version/AppVersionDefines.h` (Private)


#### Free symbols / members of external scopes

- L6 _macro_ `#define VERSION_TEXT(x) TEXT(x)` — Macros for encoding strings
- L7 _macro_ `#define VERSION_STRINGIFY_2(x) VERSION_TEXT(#x)`
- L8 _macro_ `#define VERSION_STRINGIFY(x) VERSION_STRINGIFY_2(x)`
- L10 _macro_ `#define BUILD_STORAGE_TOOL_VERSION_MAJOR 1`
- L11 _macro_ `#define BUILD_STORAGE_TOOL_VERSION_MINOR 0`
- L12 _macro_ `#define BUILD_STORAGE_TOOL_VERSION_PATCH 0`
- L14 _macro_ `#define BUILD_STORAGE_TOOL_VERSION_STRING "1.00"`
- L16 _macro_ `#define BUILD_STORAGE_TOOL_APPNAME TEXT("BuildStorageTool-Source")`
- L20 _macro_ `#define BUILD_STORAGE_TOOL_APPNAME TEXT("BuildStorageTool-PreRelease")`
- L25 _macro_ `#define BUILD_STORAGE_TOOL_APPNAME TEXT("BuildStorageTool")`
- L29 _macro_ `#define BUILD_STORAGE_TOOL_CHANGELIST_STRING TEXT("NoCL")`
- L33 _macro_ `#define BUILD_STORAGE_TOOL_CHANGELIST_STRING TEXT("CL-") VERSION_STRINGIFY(BUILD_STORAGE_TOOL_CHANGELIST)`
