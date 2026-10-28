# Plugins / ExampleLiveLinkDevices

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/ExampleLiveLinkDevices`
- headers: 1; symbols: 25
- symbol kinds: class=2, function=1, member=2, prototype=20
- PrivateDependencyModuleNames: CaptureManagerTakeMetadata, CoreUObject, IngestLiveLinkDevice, LiveLinkCapabilities, LiveLinkDevice
- PublicDependencyModuleNames: CaptureUtils, Core

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/ExampleLiveLinkDevices/Private/NetworkIngest/ExampleNetworkIngestDevice.h` (Private)


#### class `UExampleNetworkIngestDeviceSettings`  
`class UExampleNetworkIngestDeviceSettings : public ULiveLinkDeviceSettings`  
_L18-34_
- reflection: `UCLASS()`
- inherits: `ULiveLinkDeviceSettings`
- L24 _public function_ `UExampleNetworkIngestDeviceSettings()`
- L30 _public member_ `FString IpAddress;` — `UPROPERTY(EditAnywhere, Category = "Example Network Ingest Device")`
- L33 _public member_ `uint16 Port = 14785;` — `UPROPERTY(EditAnywhere, Category = "Example Network Ingest Device")`

#### class `UExampleNetworkIngestDevice`  
`class UExampleNetworkIngestDevice : public UBaseIngestLiveLinkDevice , public ILiveLinkDeviceCapability_Connection , public ILiveLinkDeviceCapability_Recording`  
_L38-81_
- reflection: `UCLASS()`
- inherits: `UBaseIngestLiveLinkDevice,ILiveLinkDeviceCapability_Connection,ILiveLinkDeviceCapability_Recording`
- L45 _public prototype_ `const UExampleNetworkIngestDeviceSettings* GetSettings() const;`
- L48 _public prototype_ `virtual TSubclassOf<ULiveLinkDeviceSettings> GetSettingsClass() const override;`
- L49 _public prototype_ `virtual FText GetDisplayName() const override;`
- L50 _public prototype_ `virtual EDeviceHealth GetDeviceHealth() const override;`
- L51 _public prototype_ `virtual FText GetHealthText() const override;`
- L53 _public prototype_ `virtual void OnDeviceAdded() override;`
- L54 _public prototype_ `virtual void OnDeviceRemoved() override;`
- L55 _public prototype_ `virtual void OnSettingChanged(const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L59 _private prototype_ `virtual FString GetFullTakePath(UE::CaptureManager::FTakeId InTakeId) const override;`
- L62 _private prototype_ `virtual void RunUpdateTakeList(UIngestCapability_UpdateTakeListCallback* InCallback) override;`
- L63 _private prototype_ `virtual void RunConvertAndUploadTake(const UIngestCapability_ProcessHandle* InProcessHandle, const UIngestCapability_Options* InIngestOptions) override;`
- L65 _private prototype_ `virtual void CancelIngestProcess_Implementation(const UIngestCapability_ProcessHandle* InProcessHandle) override;`
- L69 _private prototype_ `virtual ELiveLinkDeviceConnectionStatus GetConnectionStatus_Implementation() const override;`
- L70 _private prototype_ `virtual FString GetHardwareId_Implementation() const override;`
- L71 _private prototype_ `virtual bool SetHardwareId_Implementation(const FString& HardwareID) override;`
- L72 _private prototype_ `virtual bool Connect_Implementation() override;`
- L73 _private prototype_ `virtual bool Disconnect_Implementation() override;`
- L77 _private prototype_ `virtual bool StartRecording_Implementation() override;`
- L78 _private prototype_ `virtual bool StopRecording_Implementation() override;`
- L79 _private prototype_ `virtual bool IsRecording_Implementation() const override;`
