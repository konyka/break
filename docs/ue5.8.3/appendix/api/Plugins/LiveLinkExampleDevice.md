# Plugins / LiveLinkExampleDevice

- module root: `Plugins/Animation/LiveLinkExampleDevice/Source/LiveLinkExampleDevice`
- headers: 1; symbols: 21
- symbol kinds: class=2, function=2, member=4, prototype=13
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, LiveLinkDevice, LiveLinkHub, Networking, Projects, Slate, SlateCore

### `Plugins/Animation/LiveLinkExampleDevice/Source/LiveLinkExampleDevice/Private/Devices/LiveLinkExampleDevice.h` (Private)


#### class `ULiveLinkExampleDeviceSettings`  
`class ULiveLinkExampleDeviceSettings : public ULiveLinkDeviceSettings`  
_L12-28_
- reflection: `UCLASS()`
- inherits: `ULiveLinkDeviceSettings`
- L18 _public function_ `ULiveLinkExampleDeviceSettings()`
- L24 _public member_ `FString IpAddress = TEXT("127` — `UPROPERTY(EditAnywhere, Category="Example Device")`
- L27 _public member_ `uint16 Port = 12345;` — `UPROPERTY(EditAnywhere, Category="Example Device")`

#### class `ULiveLinkExampleDevice`  
`class ULiveLinkExampleDevice : public ULiveLinkDevice , public ILiveLinkDeviceCapability_Connection , public ILiveLinkDeviceCapability_Recording`  
_L32-70_
- reflection: `UCLASS()`
- inherits: `ULiveLinkDevice,ILiveLinkDeviceCapability_Connection,ILiveLinkDeviceCapability_Recording`
- L40 _public function_ `virtual TSubclassOf<ULiveLinkDeviceSettings> GetSettingsClass() const override`
- L45 _public prototype_ `virtual EDeviceHealth GetDeviceHealth() const override;`
- L46 _public prototype_ `virtual FText GetHealthText() const override;`
- L48 _public prototype_ `virtual void OnDeviceAdded() override;`
- L49 _public prototype_ `virtual void OnDeviceRemoved() override;`
- L50 _public prototype_ `virtual void OnSettingChanged(const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L54 _public prototype_ `virtual ELiveLinkDeviceConnectionStatus GetConnectionStatus_Implementation() const override;`
- L55 _public prototype_ `virtual FString GetHardwareId_Implementation() const override;`
- L56 _public prototype_ `virtual bool SetHardwareId_Implementation(const FString& HardwareID) override;`
- L57 _public prototype_ `virtual bool Connect_Implementation() override;`
- L58 _public prototype_ `virtual bool Disconnect_Implementation() override;`
- L62 _public prototype_ `virtual bool StartRecording_Implementation() override;`
- L63 _public prototype_ `virtual bool StopRecording_Implementation() override;`
- L64 _public prototype_ `virtual bool IsRecording_Implementation() const override;`
- L68 _private member_ `ELiveLinkDeviceConnectionStatus ConnectionStatus = ELiveLinkDeviceConnectionStatus::Disconnected;`
- L69 _private member_ `bool bIsRecording = false;`
