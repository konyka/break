# Plugins / CaptureManagerCPSClient

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerCPSClient`
- headers: 3; symbols: 109
- symbol kinds: class=3, delegate=3, enum=1, enumerator=4, macro=3, member=28, namespace=6, prototype=53, struct=5, typedef=3
- PublicDependencyModuleNames: CaptureProtocolStack, CaptureUtils, Core

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerCPSClient/Public/CPSDataStream.h` (Public)


#### class `UE::CaptureManager::FCPSDataStream`  
`class FCPSDataStream : public UE::CaptureManager::FBaseStream`  
_L13-35_
- inherits: `UE::CaptureManager::FBaseStream`
- L16 _public typedef_ `using FData = TArray<uint8>;`
- L17 _public typedef_ `using FResults = TMap<FString, TMap<FString, UE::CaptureManager::TProtocolResult<FData>>>;`
- L19 _public prototype_ `DECLARE_DELEGATE_OneParam(FFileExportFinished, FResults InExportResults);`
- L21 _public prototype_ `FCPSDataStream(FFileExportFinished InFileExportFinished);`
- L22 _public prototype_ `~FCPSDataStream();`
- L24 _public prototype_ `TProtocolResult<void> StartFile(const FString& InTakeName, const FString& InFileName) override;`
- L25 _public prototype_ `TProtocolResult<void> ProcessData(const FString& InTakeName, const FString& InFileName, const TConstArrayView<uint8>& InData) override;`
- L26 _public prototype_ `TProtocolResult<void> FinishFile(const FString& InTakeName, const FString& InFileName, const TStaticArray<uint8, 16>& InHash) override;`
- L28 _public prototype_ `void Finalize(UE::CaptureManager::TProtocolResult<void> InResult) override;`
- L31 _private member_ `FData Data;`
- L32 _private member_ `FFileExportFinished FileExportFinished;`
- L34 _private member_ `FResults ExportResults;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CAPTUREMANAGERCPSCLIENT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CaptureManager` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FFileExportFinished, FResults InExportResults);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerCPSClient/Public/CPSDevice.h` (Public)


#### struct `UE::CaptureManager::FConnectionStateChangedEvent`  
`struct FConnectionStateChangedEvent : public FCaptureEvent`  
_L21-37_
- inherits: `FCaptureEvent`
- L23 _public member_ `inline static const FString Name = TEXT("Con`
- L33 _public prototype_ `FConnectionStateChangedEvent(EState InConnectionState);`
- L34 _public prototype_ `~FConnectionStateChangedEvent();`
- L36 _public member_ `EState ConnectionState;`

#### enum `UE::CaptureManager::FConnectionStateChangedEvent::EState`  
`enum class EState`  
_L25-31_
- L27 _public enumerator_ `Unknown = 0`
- L28 _public enumerator_ `Connecting`
- L29 _public enumerator_ `Connected`
- L30 _public enumerator_ `Disconnected`

#### struct `UE::CaptureManager::FCPSEvent`  
`struct FCPSEvent : public FCaptureEvent`  
_L39-47_
- inherits: `FCaptureEvent`
- L41 _public member_ `inline static const FString Name = TEXT("CPS`
- L43 _public prototype_ `FCPSEvent(TSharedPtr<FControlUpdate> InUpdateMessage);`
- L44 _public prototype_ `~FCPSEvent();`
- L46 _public member_ `TSharedPtr<FControlUpdate> UpdateMessage;`

#### struct `UE::CaptureManager::FCPSStateEvent`  
`struct FCPSStateEvent : public FCaptureEvent`  
_L49-57_
- inherits: `FCaptureEvent`
- L51 _public member_ `inline static const FString Name = TEXT("CPS`
- L53 _public prototype_ `FCPSStateEvent(FGetStateResponse InGetStateResponse);`
- L54 _public prototype_ `~FCPSStateEvent();`
- L56 _public member_ `FGetStateResponse GetStateResponse;`

#### class `UE::CaptureManager::FCPSDevice`  
`class FCPSDevice : public FCaptureEventSource, public TSharedFromThis<FCPSDevice>`  
_L59-154_
- inherits: `FCaptureEventSource,TSharedFromThis<FCPSDevice>`
- L72 _public prototype_ `static TSharedPtr<FCPSDevice> MakeCPSDevice(FString InDeviceIpAddress, uint16 InDevicePort);`
- L74 _public prototype_ `FCPSDevice(FPrivateToken, FString InDeviceIpAddress, uint16 InDevicePort);`
- L80 _public prototype_ `void InitiateConnect();`
- L81 _public prototype_ `void Stop();`
- L83 _public prototype_ `bool IsConnected() const;`
- L85 _public prototype_ `TProtocolResult<void> StartRecording(FString SlateName, uint16 TakeNumber, TOptional<FString> Subject = TOptional<FString>(), TOptional<FString> Scenario = TOptional<FString>(), TOptional<TArray<FString>> Tags = TOptional<TArray<FString>>());`
- L91 _public prototype_ `TProtocolResult<void> StopRecording();`
- L93 _public prototype_ `TProtocolResult<TArray<FGetTakeMetadataResponse::FTakeObject>> FetchTakeList();`
- L94 _public prototype_ `TProtocolResult<FGetTakeMetadataResponse::FTakeObject> FetchTake(const FString& InTakeName);`
- L96 _public prototype_ `void AddTakeMetadata(FTakeId InId, FGetTakeMetadataResponse::FTakeObject InTake);`
- L97 _public prototype_ `void RemoveTakeMetadata(FTakeId InId);`
- L98 _public prototype_ `FGetTakeMetadataResponse::FTakeObject GetTake(FTakeId InId);`
- L99 _public prototype_ `FTakeId GetTakeId(const FString& InTakeName);`
- L101 _public prototype_ `void StartExport(FTakeId InTakeId, TUniquePtr<FBaseStream> InStream);`
- L102 _public prototype_ `void CancelExport(FTakeId InTakeId);`
- L103 _public prototype_ `void CancelAllExports();`
- L106 _public prototype_ `void FetchThumbnailForTake(FTakeId InTakeId, TUniquePtr<FBaseStream> InStream);` — Fetches the thumbnail for a single take.
- L108 _public prototype_ `void FetchThumbnails(TUniquePtr<FBaseStream> InStream);` — Fetches the thumbnails for all takes.
- L111 _public prototype_ `void FetchFileForTake(FTakeId InTakeId, TUniquePtr<FBaseStream> InStream, const FString& InFileName);` — Fetches the specified file for a single take.
- L113 _public prototype_ `void FetchFiles(TUniquePtr<FBaseStream> InStream, TArray<FString> InFileNames);` — Fetches the specified files for all takes.
- L117 _private member_ `inline static const float ConnectInterval = 5.0f;`
- L119 _private prototype_ `void InitializeDelegates();`
- L125 _private prototype_ `void ConnectControlClient(FEmpty);`
- L127 _private prototype_ `void RegisterForAllEvents();`
- L128 _private prototype_ `void OnCPSEvent(TSharedPtr<FControlUpdate> InUpdateMessage);`
- L130 _private prototype_ `void StartConnectTimer(float InDelay = 0.0f);`
- L131 _private prototype_ `void OnConnectTick();`
- L132 _private prototype_ `void OnDisconnect(const FString& InCause);`
- L134 _private prototype_ `static TSharedRef<FCaptureTimerManager> GetTimerManager();`
- L136 _private member_ `TSharedRef<FCaptureTimerManager> TimerManager;`
- L138 _private member_ `FString DeviceIpAddress;`
- L139 _private member_ `uint16 DeviceControlPort;`
- L141 _private member_ `std::atomic_bool bIsConnected;`
- L143 _private typedef_ `using FConnectionThread = TQueueRunner<FEmpty>;`
- L144 _private member_ `TUniquePtr<FConnectionThread> ConnThread;`
- L145 _private member_ `FControlMessenger ControlMessenger;`
- L146 _private member_ `FCaptureTimerManager::FTimerHandle ConnectTimerHandle;`
- L148 _private member_ `TUniquePtr<FExportClient> ExportClient;`
- L150 _private member_ `FCriticalSection Mutex;`
- L151 _private member_ `TMap<FTakeId, FGetTakeMetadataResponse::FTakeObject> TakeMetadata;`
- L153 _private member_ `TMap<FTakeId, FExportClient::FTaskId> IdMap;`

#### struct `UE::CaptureManager::FCPSDevice::FPrivateToken`  
`struct FPrivateToken`  
_L65-68_
- L67 _public prototype_ `explicit FPrivateToken() = default;`

#### struct `UE::CaptureManager::FCPSDevice::FEmpty`  
`struct FEmpty`  
_L121-123_

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API CAPTUREMANAGERCPSCLIENT_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerCPSClient/Public/CPSFileStream.h` (Public)


#### class `UE::CaptureManager::FCPSFileStream`  
`class FCPSFileStream : public UE::CaptureManager::FBaseStream`  
_L12-45_
- inherits: `UE::CaptureManager::FBaseStream`
- L16 _public prototype_ `DECLARE_DELEGATE_OneParam(FReportProgress, float InProgress);`
- L17 _public prototype_ `DECLARE_DELEGATE_OneParam(FExportFinished, UE::CaptureManager::TProtocolResult<void> InResult);`
- L19 _public prototype_ `FCPSFileStream(FString InBaseDir, uint64 InSize);`
- L20 _public prototype_ `~FCPSFileStream();`
- L22 _public prototype_ `virtual TProtocolResult<void> StartFile(const FString& InTakeName, const FString& InFileName) override;`
- L24 _public prototype_ `virtual TProtocolResult<void> ProcessData(const FString& InTakeName, const FString& InFileName, const TConstArrayView<uint8>& InData) override;`
- L25 _public prototype_ `virtual TProtocolResult<void> FinishFile(const FString& InTakeName, const FString& InFileName, const TStaticArray<uint8, 16>& InHash) override;`
- L27 _public prototype_ `virtual void Finalize(UE::CaptureManager::TProtocolResult<void> InResult) override;`
- L29 _public prototype_ `void SetExportFinished(FExportFinished InExportFinished);`
- L30 _public prototype_ `void SetProgressHandler(FReportProgress InReportProgress);`
- L34 _private prototype_ `void ReportProgressStep(const FString& InFileName, const uint32 InArrivedSize);`
- L36 _private member_ `FString BaseDir;`
- L37 _private member_ `TUniquePtr<FArchive> Writer;`
- L38 _private member_ `TUniquePtr<FMD5> MD5Generator;`
- L40 _private member_ `uint64 TotalExportExpectedSize;`
- L41 _private member_ `uint64 TotalExportArrivedSize;`
- L43 _private member_ `FExportFinished OnExportFinished;`
- L44 _private member_ `FReportProgress OnReportProgress;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CAPTUREMANAGERCPSCLIENT_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FReportProgress, float InProgress);`
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FExportFinished, UE::CaptureManager::TProtocolResult<void> InResult);`
