# Plugins / CPSLiveLinkDevice

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/CPSLiveLinkDevice`
- headers: 6; symbols: 71
- symbol kinds: class=4, function=2, member=15, prototype=48, struct=2
- PrivateDependencyModuleNames: CaptureManagerMediaRW, CaptureManagerSettings, CaptureManagerTakeMetadata, CaptureMetadataExtraction, CoreUObject, DataIngestCore, Engine, IngestLiveLinkDevice, Json, LiveLinkCapabilities, LiveLinkDevice, LiveLinkHub, LiveLinkHubCaptureMessaging, Media, RTSPMedia, Slate, SlateCore, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: CaptureManagerCPSClient, CaptureProtocolStack, CaptureUtils, Core

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/CPSLiveLinkDevice/Public/Customizations/DeviceIpAddressCustomization.h` (Public)


#### struct `FDeviceIpAddress`  
`struct FDeviceIpAddress`  
_L12-18_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public member_ `FString IpAddressString;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeviceAddress, DisplayName="Ip Address")`

#### class `FDeviceIpAddressCustomization`  
`class FDeviceIpAddressCustomization : public IPropertyTypeCustomization`  
_L20-38_
- inherits: `IPropertyTypeCustomization`
- L23 _public prototype_ `FDeviceIpAddressCustomization();`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L28 _public prototype_ `static TOptional<FText> VerifyIpAddress(const FString& InIpAddress, TRange<int32> InIpAddressRange);`
- L31 _private prototype_ `FText OnGetDeviceIpAddress() const;`
- L32 _private prototype_ `bool OnDeviceIpAddressVerify(const FText& InText, FText& OutErrorText);`
- L33 _private prototype_ `void OnDeviceIpAddressCommited(const FText& InText, ETextCommit::Type CommitInfo);`
- L34 _private prototype_ `bool IsReadOnly() const;`
- L36 _private member_ `TSharedPtr<IPropertyHandle> DeviceIpAddressProperty;`
- L37 _private member_ `TRange<int32> IpAddressRange;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/CPSLiveLinkDevice/Public/Customizations/ToggleConnectActionCustomization.h` (Public)


#### struct `FToggleConnectAction`  
`struct FToggleConnectAction`  
_L14-20_
- reflection: `USTRUCT()`
- L19 _public member_ `FGuid DeviceGuid;` — `UPROPERTY()`

#### class `FToggleConnectActionCustomization`  
`class FToggleConnectActionCustomization : public IPropertyTypeCustomization`  
_L22-49_
- inherits: `IPropertyTypeCustomization`
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L29 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L34 _private prototype_ `void OnConnectionStatusChanged(ELiveLinkDeviceConnectionStatus InStatus);`
- L36 _private prototype_ `FText GetButtonName() const;`
- L37 _private prototype_ `FReply OnConnectButtonToggled();`
- L38 _private prototype_ `bool IsConnectButtonEnabled() const;`
- L40 _private prototype_ `EVisibility GetStopActionVisibility() const;`
- L41 _private prototype_ `FReply OnStopActionClicked();`
- L42 _private prototype_ `FText GetStopActionTooltip() const;`
- L44 _private prototype_ `TObjectPtr<ULiveLinkDevice> GetDevice() const;`
- L46 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L47 _private member_ `TObjectPtr<ULiveLinkDevice> Device;`
- L48 _private member_ `std::atomic_bool bIsDisconnecting = false;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/CPSLiveLinkDevice/Public/LiveLinkFaceDevice.h` (Public)


#### class `ULiveLinkFaceDeviceSettings`  
`class ULiveLinkFaceDeviceSettings : public ULiveLinkDeviceSettings`  
_L27-46_
- reflection: `UCLASS(BlueprintType)`
- inherits: `ULiveLinkDeviceSettings`
- L33 _public function_ `ULiveLinkFaceDeviceSettings()`
- L39 _public member_ `FDeviceIpAddress IpAddress;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Live Link Face")`
- L42 _public member_ `int32 Port = 14785;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Live Link Face")`
- L45 _public member_ `FToggleConnectAction ConnectAction;` — `UPROPERTY(VisibleAnywhere, Category = "Live Link Face")`

#### class `ULiveLinkFaceDevice`  
`class ULiveLinkFaceDevice : public UBaseIngestLiveLinkDevice , public ILiveLinkDeviceCapability_Connection , public ILiveLinkDeviceCapability_Recording , public ILiveLinkDeviceCapability_Streaming`  
_L50-127_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "Live Link Face Device", ToolTip = "Use for ingest from the Live Link Face app and control recording"))`
- inherits: `UBaseIngestLiveLinkDevice,ILiveLinkDeviceCapability_Connection,ILiveLinkDeviceCapability_Recording,ILiveLinkDeviceCapability_Streaming`
- L59 _public prototype_ `const ULiveLinkFaceDeviceSettings* GetSettings() const;` — `UFUNCTION(BlueprintCallable, Category = "LiveLinkFaceDeviceSettings")`
- L62 _public prototype_ `virtual TSubclassOf<ULiveLinkDeviceSettings> GetSettingsClass() const override;`
- L63 _public prototype_ `virtual EDeviceHealth GetDeviceHealth() const override;`
- L64 _public prototype_ `virtual FText GetHealthText() const override;`
- L66 _public prototype_ `virtual void OnDeviceAdded() override;`
- L67 _public prototype_ `virtual void OnDeviceRemoved() override;`
- L68 _public prototype_ `virtual void OnSettingChanged(const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L70 _public prototype_ `virtual TMap<TSubclassOf<ULiveLinkDeviceCapability>, TObjectPtr<UObject>> OnSaveDeviceCapabilityData() const override;`
- L71 _public prototype_ `virtual void OnLoadDeviceCapabilityData(TMap<TSubclassOf<ULiveLinkDeviceCapability>, TObjectPtr<UObject>> InCapabilityDataMap) override;`
- L75 _private prototype_ `virtual FString GetFullTakePath(UE::CaptureManager::FTakeId InTakeId) const override;`
- L78 _private prototype_ `virtual void RunUpdateTakeList(UIngestCapability_UpdateTakeListCallback* InCallback) override;`
- L79 _private prototype_ `virtual void RunDownloadTake(const UIngestCapability_ProcessHandle* InProcessHandle, const UIngestCapability_Options* InIngestOptions) override;`
- L80 _private prototype_ `virtual void RunConvertAndUploadTake(const UIngestCapability_ProcessHandle* InProcessHandle, const UIngestCapability_Options* InIngestOptions) override;`
- L81 _private prototype_ `virtual void CancelIngestProcess_Implementation(const UIngestCapability_ProcessHandle* InProcessHandle) override;`
- L85 _private prototype_ `virtual ELiveLinkDeviceConnectionStatus GetConnectionStatus_Implementation() const override;`
- L86 _private prototype_ `virtual FString GetHardwareId_Implementation() const override;`
- L87 _private prototype_ `virtual bool SetHardwareId_Implementation(const FString& HardwareID) override;`
- L90 _protected prototype_ `virtual bool Connect_Implementation() override;`
- L91 _protected prototype_ `virtual bool Disconnect_Implementation() override;`
- L95 _protected function_ `virtual void ConfigureMediaSource(URtspMediaSource* InMediaSource)` — Override to configure device-specific properties on the RTSP media source (e.g. Path). Called during source creation.
- L99 _private prototype_ `virtual bool StartRecording_Implementation() override;`
- L100 _private prototype_ `virtual bool StopRecording_Implementation() override;`
- L101 _private prototype_ `virtual bool IsRecording_Implementation() const override;`
- L104 _private prototype_ `void HandleConnectionChanged(TSharedPtr<const UE::CaptureManager::FCaptureEvent> InEvent);`
- L105 _private prototype_ `void HandleCPSStateUpdate(TSharedPtr<const UE::CaptureManager::FCaptureEvent> InEvent);`
- L106 _private prototype_ `void HandleCPSEvent(TSharedPtr<const UE::CaptureManager::FCaptureEvent> InEvent);`
- L108 _private prototype_ `void OnExportProgressReport(float InProgress, TStrongObjectPtr<const UIngestCapability_ProcessHandle> InProcessHandle);`
- L109 _private prototype_ `void OnExportFinished(UE::CaptureManager::TProtocolResult<void> InResult, FString InTakeName, TStrongObjectPtr<const UIngestCapability_ProcessHandle> InProcessHandle, TStrongObjectPtr<const UIngestCapability_Options> InIngestOptions);`
- L114 _private prototype_ `FTakeMetadata ParseTakeMetadata(const UE::CaptureManager::FGetTakeMetadataResponse::FTakeObject& InTake);`
- L116 _private prototype_ `void FetchPreIngestFiles(TMap<FString, UE::CaptureManager::FTakeId> InNameToIdMap);`
- L118 _private prototype_ `void RemoveDownloadedTakeData(const UE::CaptureManager::FTakeId InTakeId);`
- L120 _private member_ `TSharedPtr<UE::CaptureManager::FCPSDevice> Device;`
- L122 _private member_ `mutable FCriticalSection DownloadedTakesMutex;`
- L123 _private member_ `TMap<UE::CaptureManager::FTakeId, FString> DownloadedTakes;`
- L125 _private member_ `std::atomic_bool bIsRecording = false;`
- L126 _private member_ `std::atomic_bool bIsConnecting = false;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/CPSLiveLinkDevice/Public/Protocol/CPSDataStream.h` (Public)
_(no declarations extracted)_

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/CPSLiveLinkDevice/Public/Protocol/CPSDevice.h` (Public)
_(no declarations extracted)_

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/CPSLiveLinkDevice/Public/Protocol/CPSFileStream.h` (Public)
_(no declarations extracted)_
