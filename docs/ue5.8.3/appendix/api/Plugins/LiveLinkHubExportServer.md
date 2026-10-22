# Plugins / LiveLinkHubExportServer

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/LiveLinkHubExportServer`
- headers: 2; symbols: 40
- symbol kinds: class=2, delegate=1, enum=1, enumerator=3, macro=2, member=9, namespace=2, prototype=19, struct=1
- PrivateDependencyModuleNames: LiveLinkHubCaptureMessaging, Sockets
- PublicDependencyModuleNames: CaptureUtils, Core, CoreUObject, Engine

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/LiveLinkHubExportServer/Public/LiveLinkHubExportServer.h` (Public)


#### class `FLiveLinkHubExportServer`  
`class FLiveLinkHubExportServer`  
_L15-62_
- L34 _public prototype_ `FLiveLinkHubExportServer();`
- L35 _public prototype_ `~FLiveLinkHubExportServer();`
- L37 _public prototype_ `bool Start();`
- L38 _public prototype_ `bool Start(uint16 InPort);`
- L39 _public prototype_ `bool Stop();`
- L41 _public prototype_ `bool IsRunning() const;`
- L43 _public prototype_ `TValueOrError<FServerInfo, EServerError> GetServerInfo() const;`
- L45 _public prototype_ `void RegisterFileDownloadHandler(FString InClientId, FFileDataHandler InFileDataHandler);`
- L46 _public prototype_ `void UnregisterFileDownloadHandler(FString InClientId);`
- L52 _private prototype_ `void OnConnectionChanged(TWeakPtr<UE::CaptureManager::FTcpClientHandler> InClient, bool bIsConnected);`
- L53 _private prototype_ `bool HandleFileData(TSharedPtr<UE::CaptureManager::FTcpClientHandler> InClient, FUploadDataHeader Header);`
- L55 _private member_ `TSharedPtr<UE::CaptureManager::FTcpServer> TcpServer;`
- L57 _private member_ `FCriticalSection Mutex;`
- L58 _private member_ `FCriticalSection HandlersMutex;`
- L59 _private member_ `TMap<FString, FFileDataHandler> Handlers;` — The key is stringified FGuid
- L60 _private member_ `TMap<FString, TUniquePtr<FLiveLinkHubClientExportRunner>> Runners;`
- L61 _private member_ `TMap<FString, TUniquePtr<FRunnableThread>> Threads;`

#### struct `FLiveLinkHubExportServer::FServerInfo`  
`struct FServerInfo`  
_L21-25_
- L23 _public member_ `FString IPAddress;`
- L24 _public member_ `uint16 Port = 0;`

#### enum `FLiveLinkHubExportServer::EServerError`  
`enum class EServerError`  
_L27-32_
- L29 _public enumerator_ `NotRunning`
- L30 _public enumerator_ `InvalidPort`
- L31 _public enumerator_ `InvalidIPAddress`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LIVELINKHUBEXPORTSERVER_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FFileDataHandler, FUploadDataHeader, TSharedPtr<UE::CaptureManager::FTcpClientHandler>) struct FServerInfo { FString IPAddress; uint16 Port = 0; };`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/LiveLinkHubExportServer/Public/LiveLinkHubExportServerModule.h` (Public)


#### class `FLiveLinkHubExportServerModule`  
`class FLiveLinkHubExportServerModule : public IModuleInterface`  
_L11-31_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `bool StartExportServer(uint16 InPort);`
- L20 _public prototype_ `bool StopExportServer();`
- L21 _public prototype_ `bool IsExportServerRunning() const;`
- L23 _public prototype_ `TValueOrError<FLiveLinkHubExportServer::FServerInfo, FLiveLinkHubExportServer::EServerError> GetExportServerInfo() const;`
- L25 _public prototype_ `void RegisterExportServerHandler(FString InClientId, FLiveLinkHubExportServer::FFileDataHandler InFileDataHandler);`
- L26 _public prototype_ `void UnregisterExportServerHandler(FString InClientId);`
- L30 _private member_ `TSharedPtr<FLiveLinkHubExportServer> ExportServer;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINKHUBEXPORTSERVER_API`
