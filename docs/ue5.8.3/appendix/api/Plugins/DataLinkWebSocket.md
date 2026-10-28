# Plugins / DataLinkWebSocket

- module root: `Plugins/VirtualProduction/DataLink/Source/DataLinkWebSocket`
- headers: 6; symbols: 49
- symbol kinds: class=3, delegate=1, function=4, macro=2, member=12, namespace=4, prototype=17, struct=4, variable=2
- PrivateDependencyModuleNames: WebSockets
- PublicDependencyModuleNames: Core, CoreUObject, DataLink, Engine

### `Plugins/VirtualProduction/DataLink/Source/DataLinkWebSocket/Private/DataLinkWebSocketLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataLinkWebSocket, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataLinkWebSocket, Log, All);`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkWebSocket/Private/DataLinkWebSocketSubsystem.h` (Private)


#### class `UDataLinkWebSocketSubsystem`  
`class UDataLinkWebSocketSubsystem : public UEngineSubsystem`  
_L14-44_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- L19 _public prototype_ `static UDataLinkWebSocketSubsystem* TryGet();`
- L26 _public prototype_ `bool CreateWebSocket(const FDataLinkWebSocketSettings& InSettings, FCreateWebSocketResult& OutResult);`
- L28 _public prototype_ `void CloseWebSocket(UE::DataLink::FWebSocketHandle InHandle);`
- L31 _public prototype_ `TSharedPtr<IWebSocket> FindWebSocket(UE::DataLink::FWebSocketHandle InHandle) const;` — Returns the web socket mapped to the handle if valid
- L34 _private prototype_ `void CleanupInvalidWebSockets();`
- L37 _private member_ `TMap<UE::DataLink::FWebSocketHandle, TSharedRef<IWebSocket>> WebSockets;` — Registered web sockets
- L40 _private member_ `TArray<TSharedRef<IWebSocket>> InvalidWebSockets;` — Web sockets that have requested closure and are pending kill
- L43 _private member_ `FTSTicker::FDelegateHandle CleanupHandle;` — Handle to the callback to clean up invalid web sockets

#### struct `UDataLinkWebSocketSubsystem::FCreateWebSocketResult`  
`struct FCreateWebSocketResult`  
_L21-25_
- L23 _public member_ `UE::DataLink::FWebSocketHandle Handle;`
- L24 _public member_ `TSharedPtr<IWebSocket> WebSocket;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkWebSocket/Public/DataLinkWebSocket.h` (Public)


#### struct `FDataLinkWebSocketMessages`  
`struct FDataLinkWebSocketMessages`  
_L14-21_
- reflection: `USTRUCT(BlueprintType)`
- desc: The messages to send through web socket
- L20 _public member_ `TArray<FString> ConnectMessages;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link Web Sockets")` — Messages to send

#### struct `FDataLinkWebSocketInstanceData`  
`struct FDataLinkWebSocketInstanceData`  
_L25-38_
- reflection: `USTRUCT()`
- desc: Instance data for the Web Socket Data Link node
- L30 _public member_ `UE::DataLink::FWebSocketHandle WebSocketHandle;` — Handle to the last web socket created for this instance
- L37 _public member_ `FDataLinkWebSocketSettings WebSocketSettings;` — `UPROPERTY()` — Settings used to create the web socket Used to determine if a new web socket has to be created

#### class `UDataLinkWebSocket`  
`class UDataLinkWebSocket : public UDataLinkNode`  
_L41-66_
- reflection: `UCLASS(MinimalAPI, DisplayName="Web Socket", Category="Web Socket")`
- inherits: `UDataLinkNode`
- L45 _private prototype_ `UDataLinkWebSocket();`
- L49 _protected prototype_ `virtual void OnBuildPins(FDataLinkPinBuilder& Inputs, FDataLinkPinBuilder& Outputs) const override;`
- L50 _protected prototype_ `virtual EDataLinkExecutionReply OnExecute(FDataLinkExecutor& InExecutor) const override;`
- L51 _protected prototype_ `virtual void OnStop(const FDataLinkExecutor& InExecutor) const override;`
- L56 _private prototype_ `void OnConnected(TWeakPtr<FDataLinkExecutor> InExecutorWeak) const;` — Called when the web socket has connected
- L59 _private prototype_ `void OnConnectionError(const FString& InError, TWeakPtr<FDataLinkExecutor> InExecutorWeak) const;` — Called when the web socket encountered a connection error
- L62 _private prototype_ `void OnClosed(int32 InStatusCode, const FString& InReason, bool bInWasClean, TWeakPtr<FDataLinkExecutor> InExecutorWeak) const;` — Called when the web socket has closed
- L65 _private prototype_ `void OnMessageReceived(const FString& InMessage, TWeakPtr<FDataLinkExecutor> InExecutorWeak) const;` — Called when the web socket has a received a message

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATALINKWEBSOCKET_API`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkWebSocket/Public/DataLinkWebSocketHandle.h` (Public)


#### class `UE::DataLink::FWebSocketHandle`  
`class FWebSocketHandle`  
_L11-38_
- L14 _public prototype_ `static FWebSocketHandle GenerateNewHandle();`
- L16 _public function_ `void Reset()`
- L21 _public function_ `bool IsValid() const`
- L26 _public function_ `bool operator==(const FWebSocketHandle& InOther) const`
- L37 _private member_ `uint32 Id = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DataLink` (scope `UE`)
- L31 _function_ `friend uint32 GetTypeHash(const FWebSocketHandle& InHandle)` (scope `UE::DataLink`)

### `Plugins/VirtualProduction/DataLink/Source/DataLinkWebSocket/Public/DataLinkWebSocketNames.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DataLink` (scope `UE`)
- L9 _variable_ `const FLazyName InputWebSocketSettings(TEXT("Inpu` (scope `UE::DataLink`)
- L10 _variable_ `const FLazyName InputWebSocketMessages(TEXT("Inpu` (scope `UE::DataLink`)

### `Plugins/VirtualProduction/DataLink/Source/DataLinkWebSocket/Public/DataLinkWebSocketSettings.h` (Public)


#### struct `FDataLinkWebSocketSettings`  
`struct FDataLinkWebSocketSettings`  
_L13-34_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public prototype_ `void Reset();` — Resets all the settings
- L21 _public prototype_ `bool Equals(const FDataLinkWebSocketSettings& InOther) const;` — Returns true if the settings matches the given other settings
- L25 _public member_ `FString URL;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link Web Sockets")` — URL to connect to where the web socket server will respond
- L29 _public member_ `TArray<FString> Protocols;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link Web Sockets")` — List of the protocols to use with the connection
- L33 _public member_ `TMap<FString, FString> UpgradeHeaders;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link Web Sockets")` — The upgrade headers to send with the upgrade request

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATALINKWEBSOCKET_API`
