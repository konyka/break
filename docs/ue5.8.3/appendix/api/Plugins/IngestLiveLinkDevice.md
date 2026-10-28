# Plugins / IngestLiveLinkDevice

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/IngestLiveLinkDevice`
- headers: 3; symbols: 16
- symbol kinds: class=1, delegate=1, member=1, namespace=2, prototype=11
- PrivateDependencyModuleNames: CaptureDataConverter, CaptureDataUtils, CaptureManagerMediaRW, CaptureManagerSettings, CaptureManagerTakeMetadata, CaptureManagerUnrealEndpoint, CaptureProtocolStack, CaptureUtils, CoreUObject, ElectraPlayerPlugin, Engine, Json, LiveLinkCapabilities, LiveLinkDevice, LiveLinkHub, LiveLinkHubCaptureMessaging, MJPEGDecoderElectra, Media, NamingTokens, Slate, SlateCore, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: CaptureUtils, Core, MediaAssets

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/IngestLiveLinkDevice/Private/Utils/IngestLiveLinkDeviceLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogIngestLiveLinkDevice, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIngestLiveLinkDevice, Log, All);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/IngestLiveLinkDevice/Public/BaseIngestLiveLinkDevice.h` (Public)


#### class `UBaseIngestLiveLinkDevice`  
`class UBaseIngestLiveLinkDevice : public ULiveLinkDevice , public ILiveLinkDeviceCapability_Ingest`  
_L18-99_
- reflection: `UCLASS(Abstract)`
- inherits: `ULiveLinkDevice,ILiveLinkDeviceCapability_Ingest`
- desc: Base class that provides default implementations of core ingest capability functions.
- L31 _public prototype_ `virtual void OnDeviceAdded() override;` — Inherited function from the ULiveLinkDevice that is called when device is added @note Users are required to invoke this function if it is inherited in the users code.
- L37 _public prototype_ `virtual void OnDeviceRemoved() override;` — Inherited function from the ULiveLinkDevice that is called when device is removed @note Users are required to invoke this function if it is inherited in the users code.
- L49 _protected prototype_ `void IngestTake(const UIngestCapability_ProcessHandle* InProcessHandle, const UIngestCapability_Options* InIngestOptions, TSharedPtr<UE::CaptureManager::FTaskProgress> InTaskProgress);` — Function implements the default behavior for conversion and upload to the UE of the take data @params ProcessHandle Pointer to the process handle created for this process @params IngestOptions Ingest options used for conversion process @params TaskProgress Helper class that accumulates progress and reports the progress to the user
- L56 _protected prototype_ `virtual FString GetFullTakePath(UE::CaptureManager::FTakeId InTakeId) const PURE_VIRTUAL(UBaseIngestLiveLinkDevice::GetFullTakePath, return FString(););` — Pure virtual function that returns the full path to the take data. Full path to the take data is required for the conversion step. @params TakeId Take identifier @returns Full path to the take data
- L66 _protected prototype_ `virtual void RunDownloadTake(const UIngestCapability_ProcessHandle* InProcessHandle, const UIngestCapability_Options* InIngestOptions) override;` — Inherited function from the ILiveLinkDeviceCapability_Ingest. The function is required to be implemented. @note In it's implementation, user may choose to call IngestTake function or to implement custom download step @params ProcessHandle Pointer to the process handle created for this process @params IngestOptions Ingest options used for conversion process
- L74 _protected prototype_ `virtual void RunConvertAndUploadTake(const UIngestCapability_ProcessHandle* InProcessHandle, const UIngestCapability_Options* InIngestOptions) override PURE_VIRTUAL(UBaseIngestLiveLinkDevice::RunConvertAndUploadTake);` — Inherited function from the ILiveLinkDeviceCapability_Ingest. The function is required to be implemented. @note In it's implementation, user may choose to call IngestTake function or to implement custom conversion and upload step @params ProcessHandle Pointer to the process handle created for this process @params IngestOptions Ingest options used for conversion process
- L81 _protected prototype_ `virtual void RunUpdateTakeList(UIngestCapability_UpdateTakeListCallback* InCallback) override PURE_VIRTUAL(UBaseIngestLiveLinkDevice::RunUpdateTakeList);` — Inherited function from the ILiveLinkDeviceCapability_Ingest. The function is required to be implemented. @note Runs update take list in the current thread @param Callback to be run
- L90 _protected prototype_ `void CancelIngest(int32 InTakeId);` — Inherited function from the ILiveLinkDeviceCapability_Ingest. The function is required to be implemented. @note In it's default implementation, it will abort the default ingest process. @params TakeId Take identifier
- L95 _private prototype_ `virtual void CancelIngestProcess_Implementation(const UIngestCapability_ProcessHandle* InProcessHandle) override;`
- L98 _private member_ `TSharedPtr<FImpl> Impl;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/IngestLiveLinkDevice/Public/Utils/IngestLiveLinkDeviceUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)
- L10 _prototype_ `FString ErrorOriginToString(FTakeMetadataParserError::EOrigin InOrigin);` (scope `UE::CaptureManager`)
