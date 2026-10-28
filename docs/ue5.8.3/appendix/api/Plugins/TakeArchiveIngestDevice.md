# Plugins / TakeArchiveIngestDevice

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/TakeArchiveIngestDevice`
- headers: 2; symbols: 20
- symbol kinds: class=2, delegate=1, function=1, member=2, prototype=14
- PrivateDependencyModuleNames: CaptureManagerMediaRW, CaptureManagerSettings, CaptureManagerTakeMetadata, CaptureMetadataExtraction, CoreUObject, DataIngestCore, Engine, IngestLiveLinkDevice, Json, LiveLinkCapabilities, LiveLinkDevice, LiveLinkHub, LiveLinkHubCaptureMessaging, Media, Slate, SlateCore, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: CaptureUtils, Core

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/TakeArchiveIngestDevice/Private/TakeArchiveIngestDevice.h` (Private)


#### class `UTakeArchiveIngestDeviceSettings`  
`class UTakeArchiveIngestDeviceSettings : public ULiveLinkDeviceSettings`  
_L20-34_
- reflection: `UCLASS(BlueprintType)`
- inherits: `ULiveLinkDeviceSettings`
- L26 _public function_ `UTakeArchiveIngestDeviceSettings()`
- L33 _public member_ `FDirectoryPath TakeDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Take Archive Ingest")` — Path to a directory containing the take(s) data

#### class `UTakeArchiveIngestDevice`  
`class UTakeArchiveIngestDevice final : public UBaseIngestLiveLinkDevice , public ILiveLinkDeviceCapability_Connection`  
_L38-72_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "Take Archive Ingest", ToolTip = "Ingest take archives (described by .cptake files) and legacy Capture Manager takes"))`
- inherits: `UBaseIngestLiveLinkDevice,ILiveLinkDeviceCapability_Connection`
- L45 _public prototype_ `const UTakeArchiveIngestDeviceSettings* GetSettings() const;` — `UFUNCTION(BlueprintCallable, Category = "TakeArchiveIngestDeviceSettings")`
- L48 _public prototype_ `virtual TSubclassOf<ULiveLinkDeviceSettings> GetSettingsClass() const override;`
- L49 _public prototype_ `virtual EDeviceHealth GetDeviceHealth() const override;`
- L50 _public prototype_ `virtual FText GetHealthText() const override;`
- L52 _public prototype_ `virtual void OnSettingChanged(const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L56 _private prototype_ `virtual FString GetFullTakePath(UE::CaptureManager::FTakeId InTakeId) const override;`
- L59 _private prototype_ `virtual void RunConvertAndUploadTake(const UIngestCapability_ProcessHandle* InProcessHandle, const UIngestCapability_Options* InIngestOptions) override;`
- L60 _private prototype_ `virtual void RunUpdateTakeList(UIngestCapability_UpdateTakeListCallback* InCallback) override;`
- L64 _private prototype_ `virtual ELiveLinkDeviceConnectionStatus GetConnectionStatus_Implementation() const override;`
- L65 _private prototype_ `virtual FString GetHardwareId_Implementation() const override;`
- L66 _private prototype_ `virtual bool SetHardwareId_Implementation(const FString& HardwareID) override;`
- L67 _private prototype_ `virtual bool Connect_Implementation() override;`
- L68 _private prototype_ `virtual bool Disconnect_Implementation() override;`
- L71 _private member_ `TMap<int32, FString> RelativeTakePaths;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/TakeArchiveIngestDevice/Private/Utils/TakeArchiveIngestDeviceLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTakeArchiveIngestDevice, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTakeArchiveIngestDevice, Log, All);`
