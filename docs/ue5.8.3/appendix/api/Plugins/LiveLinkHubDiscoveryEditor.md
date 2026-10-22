# Plugins / LiveLinkHubDiscoveryEditor

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/LiveLinkHubDiscoveryEditor`
- headers: 2; symbols: 21
- symbol kinds: class=2, delegate=1, member=6, namespace=4, prototype=8
- PrivateDependencyModuleNames: CaptureUtils, Core, CoreUObject, LiveLinkHubCaptureMessaging, LiveLinkHubExportServer, LiveLinkHubWorkerManager, Messaging, Sockets

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/LiveLinkHubDiscoveryEditor/Private/DiscoveryResponder.h` (Private)


#### class `UE::CaptureManager::FDiscoveryResponder`  
`class FDiscoveryResponder`  
_L18-44_
- L21 _public prototype_ `FDiscoveryResponder();`
- L22 _public prototype_ `~FDiscoveryResponder();`
- L26 _private prototype_ `static TValueOrError<FLiveLinkHubExportServer::FServerInfo, FLiveLinkHubExportServer::EServerError> GetExportServerInfo();`
- L27 _private prototype_ `static TSharedRef<FLiveLinkHubWorkerManager> GetWorkerManager();`
- L29 _private prototype_ `void HandleDiscoveryRequest( const FDiscoveryRequest& InRequest, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext );`
- L34 _private prototype_ `void StartDiscoveryResponder();`
- L36 _private member_ `TSharedRef<FLiveLinkHubWorkerManager> Manager;`
- L38 _private member_ `FString HostName;`
- L39 _private member_ `TOptional<FLiveLinkHubExportServer::FServerInfo> CachedServerInfo;`
- L41 _private member_ `TSharedPtr<FMessageEndpoint> MessageEndpoint;`
- L43 _private member_ `std::atomic_bool bStarted = false;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkHubDiscoveryEditor, Log, All) namespace UE::CaptureManager { class FDiscoveryResponder { public: FDiscoveryResponder(); ~FDiscoveryResponder(); private: static TValueOrError<FLiveLinkHubExportServer::FServerInfo, FLiveLinkHubExportServer::EServerError> GetExportServerInfo(); static TSharedRef<FLiveLinkHubWorkerManager> GetWorkerManager(); void HandleDiscoveryRequest( const FDiscoveryRequest& InRequest, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext ); void StartDiscoveryResponder(); TSharedRef<FLiveLinkHubWorkerManager> Manager; FString HostName; TOptional<FLiveLinkHubExportServer::FServerInfo> CachedServerInfo; TSharedPtr<FMessageEndpoint> MessageEndpoint; std::atomic_bool bStarted = false; }; }`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/LiveLinkHubDiscoveryEditor/Private/LiveLinkHubDiscoveryEditorModule.h` (Private)


#### class `FLiveLinkHubDiscoveryEditor`  
`class FLiveLinkHubDiscoveryEditor : public IModuleInterface`  
_L12-20_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private member_ `TUniquePtr<UE::CaptureManager::FDiscoveryResponder> DiscoveryResponder;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)
