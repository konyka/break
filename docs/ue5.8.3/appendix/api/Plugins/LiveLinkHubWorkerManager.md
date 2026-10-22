# Plugins / LiveLinkHubWorkerManager

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/LiveLinkHubWorkerManager`
- headers: 6; symbols: 54
- symbol kinds: class=4, delegate=2, macro=2, member=12, namespace=3, prototype=27, struct=3, typedef=1
- PrivateDependencyModuleNames: CaptureDataCore, CaptureDataUtils, CaptureManagerEditorSettings, CaptureManagerTakeMetadata, ContentBrowserData, DataIngestCore, DataIngestCoreEditor, DeveloperSettings, LiveLinkHubCaptureMessaging, LiveLinkHubExportServer, MessagingCommon, NamingTokens, Settings, UnrealEd
- PublicDependencyModuleNames: CaptureUtils, Core, CoreUObject, Engine

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/LiveLinkHubWorkerManager/Private/IngestProcess/IngestCaptureDataProcess.h` (Private)


#### class `FIngestCaptureDataProcess`  
`class FIngestCaptureDataProcess`  
_L13-25_
- L16 _public prototype_ `static TValueOrError<FIngestProcessResult, FText> StartIngestProcess(const FString& InTakeStoragePath, const FString& InDeviceName, const FGuid& InTakeUploadId);`
- L22 _private prototype_ `static UE::CaptureManager::FCreateAssetsData PrepareAssetsData(const FGuid& InTakeUploadId, const FString& InDeviceName, const FIngestCaptureData& InIngestCaptureData);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/LiveLinkHubWorkerManager/Private/IngestProcess/IngestProcessData.h` (Private)


#### struct `FIngestProcessResult`  
`struct FIngestProcessResult`  
_L7-12_
- L9 _public member_ `FString TakeIngestPackagePath;`
- L10 _public member_ `UE::CaptureManager::FCaptureDataTakeInfo CaptureDataTakeInfo;`
- L11 _public member_ `TArray<UE::CaptureManager::FCreateAssetsData> AssetsData;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/LiveLinkHubWorkerManager/Private/LiveLinkHubWorkerLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkHubWorker, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkHubWorker, Log, All);`
- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkHubWorkerManager, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkHubWorkerManager, Log, All);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/LiveLinkHubWorkerManager/Public/LiveLinkHubWorker.h` (Public)


#### class `UE::CaptureManager::Private::FLiveLinkHubImportWorker`  
`class FLiveLinkHubImportWorker : public TSharedFromThis<FLiveLinkHubImportWorker>`  
_L23-64_
- inherits: `TSharedFromThis<FLiveLinkHubImportWorker>`
- L30 _public typedef_ `using FEditorMessenger = FMessenger<FConnectAcceptor, FUploadStateSender>;`
- L32 _public prototype_ `static TSharedPtr<FLiveLinkHubImportWorker> Create(TWeakPtr<FEditorMessenger> InEditorMessenger);`
- L34 _public prototype_ `explicit FLiveLinkHubImportWorker(TWeakPtr<FEditorMessenger> InEditorMessenger, FPrivateToken);`
- L35 _public prototype_ `~FLiveLinkHubImportWorker();`
- L47 _private prototype_ `FString EvaluateSettings(const FUploadDataHeader& InHeader);`
- L48 _private prototype_ `bool HandleTakeDownload(FUploadDataHeader InHeader, TSharedPtr<UE::CaptureManager::FTcpClientHandler> InClient);`
- L49 _private prototype_ `FUploadVoidResult HandleFileDownload(const FString& InTakeStoragePath, const FUploadFileDataHeader& InFileHeader, FTakeFileContext& InContext, TSharedPtr<UE::CaptureManager::FTcpClientHandler> InClient, UE::CaptureManager::FTaskProgress::FTask& InTask);`
- L54 _private prototype_ `void DeleteDownloadedData(const FString& InTakeStoragePath);`
- L56 _private prototype_ `static void SpawnIngestTask(TSharedPtr<FEditorMessenger> InMessenger, const FString& InDataStorage, const FGuid& InCaptureSourceId, const FString& InCaptureSourceName, const FGuid& InTakeUploadId, TSharedPtr<UE::CaptureManager::FTaskProgress> InTaskProgress);`
- L63 _private member_ `TWeakPtr<FEditorMessenger> Messenger;`

#### struct `UE::CaptureManager::Private::FLiveLinkHubImportWorker::FPrivateToken`  
`struct FPrivateToken`  
_L27-27_

#### struct `UE::CaptureManager::Private::FLiveLinkHubImportWorker::FTakeFileContext`  
`struct FTakeFileContext`  
_L39-44_
- L41 _public member_ `uint64 TotalLength = 0;`
- L42 _public member_ `uint64 RemainingLength = 0;`
- L43 _public member_ `float Progress = 0.f;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace CaptureManager` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::CaptureManager`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/LiveLinkHubWorkerManager/Public/LiveLinkHubWorkerManager.h` (Public)


#### class `FLiveLinkHubWorkerManager`  
`class FLiveLinkHubWorkerManager`  
_L10-34_
- L14 _public prototype_ `FLiveLinkHubWorkerManager();`
- L15 _public prototype_ `~FLiveLinkHubWorkerManager();`
- L17 _public prototype_ `void Disconnect();`
- L18 _public prototype_ `bool IsConnected() const;`
- L19 _public prototype_ `void SendDiscoveryResponse(FDiscoveryResponse* Response, FMessageAddress Receiver);`
- L23 _private prototype_ `TWeakPtr<UE::CaptureManager::Private::FLiveLinkHubImportWorker> AddWorker(FMessageAddress InServer);`
- L25 _private prototype_ `void RemoveWorker(FMessageAddress InServer);`
- L27 _private prototype_ `FConnectResponse* ConnectAccepted(const FConnectRequest& InRequest, const FMessageAddress& InAddress);`
- L28 _private prototype_ `void ConnectionLost(const FMessageAddress& InAddress);`
- L30 _private member_ `TSharedPtr<UE::CaptureManager::Private::FLiveLinkHubImportWorker::FEditorMessenger> Messenger;`
- L32 _private member_ `FCriticalSection Mutex;`
- L33 _private member_ `TMap<FString, TSharedPtr<UE::CaptureManager::Private::FLiveLinkHubImportWorker>> Workers;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LIVELINKHUBWORKERMANAGER_API`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/LiveLinkHubWorkerManager/Public/LiveLinkHubWorkerManagerModule.h` (Public)


#### class `FLiveLinkHubWorkerManagerModule`  
`class FLiveLinkHubWorkerManagerModule : public IModuleInterface`  
_L11-29_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `TSharedRef<FLiveLinkHubWorkerManager> GetManager();`
- L22 _private prototype_ `void PostEngineInit();`
- L23 _private prototype_ `void EnginePreExit();`
- L25 _private prototype_ `bool CheckExportServerAvailability(float InDelay);`
- L27 _private member_ `TSharedPtr<FLiveLinkHubWorkerManager> Manager;`
- L28 _private member_ `FTSTicker::FDelegateHandle Delegate;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINKHUBWORKERMANAGER_API`
