# Plugins / LiveLinkKiProDevice

- module root: `Plugins/VirtualProduction/LiveLinkKiProDevice/Source/LiveLinkKiProDevice`
- headers: 2; symbols: 55
- symbol kinds: class=2, enum=1, enumerator=4, member=16, prototype=32
- PrivateDependencyModuleNames: CoreUObject, Engine, HTTP, Json, JsonUtilities, LiveLinkDevice, LiveLinkInterface, Networking, Projects, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/LiveLinkKiProDevice/Source/LiveLinkKiProDevice/Public/LiveLinkKiProDeviceBase.h` (Public)


#### class `ULiveLinkKiProDeviceBase`  
`class ULiveLinkKiProDeviceBase : public ULiveLinkDevice , public ILiveLinkDeviceCapability_Connection , public ILiveLinkDeviceCapability_Recording`  
_L20-149_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "KiPro Device", ToolTip = "Support for AJA KiPro"))`
- inherits: `ULiveLinkDevice,ILiveLinkDeviceCapability_Connection,ILiveLinkDeviceCapability_Recording`
- desc: Concrete implementation for AJA Ki Pro recording devices Provides both Connection and Recording capabilities via REST API
- L28 _public prototype_ `virtual TSubclassOf<ULiveLinkDeviceSettings> GetSettingsClass() const override;`
- L29 _public prototype_ `virtual EDeviceHealth GetDeviceHealth() const override;`
- L30 _public prototype_ `virtual FText GetHealthText() const override;`
- L31 _public prototype_ `virtual void OnDeviceAdded() override;`
- L32 _public prototype_ `virtual void OnDeviceRemoved() override;`
- L33 _public prototype_ `virtual void OnSettingChanged(const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L37 _public prototype_ `virtual ELiveLinkDeviceConnectionStatus GetConnectionStatus_Implementation() const override;`
- L38 _public prototype_ `virtual FString GetHardwareId_Implementation() const override;`
- L39 _public prototype_ `virtual bool SetHardwareId_Implementation(const FString& HardwareID) override;`
- L40 _public prototype_ `virtual bool CanSetHardwareId_Implementation() override;`
- L41 _public prototype_ `virtual bool Connect_Implementation() override;`
- L42 _public prototype_ `virtual bool Disconnect_Implementation() override;`
- L46 _public prototype_ `virtual bool StartRecording_Implementation() override;`
- L47 _public prototype_ `virtual bool StopRecording_Implementation() override;`
- L48 _public prototype_ `virtual bool IsRecording_Implementation() const override;`
- L53 _private prototype_ `FString GetBaseUrl() const;` — Build URL for Ki Pro REST API
- L56 _private prototype_ `static FString DecodeFirmwareVersion(int32 VersionBits);` — Decode firmware version from 32-bit integer to dotted string (e.g., 67239937 -> "4.2.0.1")
- L59 _private prototype_ `void GetParameter(const FString& ParamId, TFunction<void(bool bSuccess, const FString& Value, const FString& Text)> OnComplete);` — Get a parameter from the Ki Pro device
- L62 _private prototype_ `void SetParameter(const FString& ParamId, const FString& Value, TFunction<void(bool bSuccess)> OnComplete);` — Set a parameter on the Ki Pro device
- L65 _private prototype_ `void GetTransportState(TFunction<void(bool bSuccess, const FString& StateText)> OnComplete);` — Get the transport state
- L68 _private prototype_ `void SendTransportCommand(const FString& CommandText);` — Send a transport command using the cached value for the given command text
- L71 _private prototype_ `void QueryTransportCommands(TFunction<void(bool bSuccess)> OnComplete);` — Query the device for available transport commands and cache their values
- L74 _private prototype_ `void SetMediaStateForRecordPlay();` — Ensure device is in Record-Play mode (not Data-LAN)
- L77 _private prototype_ `void PollTransportState();` — Poll transport state until target state is reached
- L80 _private prototype_ `void OnTransportStateReceived(bool bSuccess, const FString& StateText);` — Called when transport state polling completes
- L83 _private prototype_ `void OnRecordingStopped();` — Called when recording stop is confirmed
- L86 _private prototype_ `static void HandleGetParameterResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, TFunction<void(bool, const FString&, const FString&)> OnComplete);` — Handle HTTP request completion for GetParameter
- L89 _private prototype_ `static void HandleSetParameterResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, TFunction<void(bool)> OnComplete);` — Handle HTTP request completion for SetParameter
- L92 _private prototype_ `bool DeviceTick(float DeltaTime);` — Main device tick function (handles reconnection and polling)
- L95 _private prototype_ `void AttemptReconnection();` — Attempt reconnection if disconnected
- L98 _private prototype_ `void HandleSlateNameChanged(FStringView InSlateName);` — Handle slate name changes from recording session
- L101 _private prototype_ `void HandleTakeNumberChanged(int32 InTakeNumber);` — Handle take number changes from recording session
- L106 _protected member_ `TSubclassOf<ULiveLinkDeviceSettings> SettingsClass;` — `UPROPERTY(EditDefaultsOnly, Category="Live Link Device")` — Settings class to use for Ki Pro devices
- L110 _protected member_ `ELiveLinkDeviceConnectionStatus ConnectionStatus = ELiveLinkDeviceConnectionStatus::Disconnected;` — `UPROPERTY()` — Current connection status
- L114 _protected member_ `bool bIsRecording = false;` — `UPROPERTY()` — Whether the device is currently recording
- L117 _protected member_ `FTSTicker::FDelegateHandle DeviceTickerHandle;` — Ticker handle for main device tick (reconnection and polling)
- L127 _protected member_ `EPollingOperation CurrentPollingOperation = EPollingOperation::None;`
- L130 _protected member_ `double PollingStartTime = 0.0;` — Time when polling started (for timeout)
- L133 _protected member_ `float ReconnectionTimeAccumulator = 0.0f;` — Time accumulator for reconnection attempts
- L136 _protected member_ `bool bPollingRequestInFlight = false;` — Flag to prevent polling request flood on slow connections
- L139 _protected member_ `TMap<FString, int32> TransportCommandValues;` — Cached transport command text -> numeric value mapping, queried from the device
- L142 _protected member_ `static constexpr double PollingTimeoutSeconds = 4.0;` — Polling timeout in seconds
- L145 _protected member_ `static constexpr float PollingIntervalSeconds = 0.1f;` — Polling interval in seconds
- L148 _protected member_ `static constexpr float ReconnectionIntervalSeconds = 5.0f;` — Reconnection attempt interval in seconds

#### enum `ULiveLinkKiProDeviceBase::EPollingOperation`  
`enum class EPollingOperation`  
_L120-126_
- desc: What operation we're polling for
- L122 _public enumerator_ `None`
- L123 _public enumerator_ `WaitingForRecording`
- L124 _public enumerator_ `WaitingForIdle`
- L125 _public enumerator_ `WaitingForPlay`

### `Plugins/VirtualProduction/LiveLinkKiProDevice/Source/LiveLinkKiProDevice/Public/LiveLinkKiProDeviceSettings.h` (Public)


#### class `ULiveLinkKiProDeviceSettings`  
`class ULiveLinkKiProDeviceSettings : public ULiveLinkDeviceSettings`  
_L13-33_
- reflection: `UCLASS()`
- inherits: `ULiveLinkDeviceSettings`
- desc: Settings for AJA Ki Pro recording device
- L20 _public member_ `FString IpAddress = TEXT("192` — `UPROPERTY(EditAnywhere, Category="Ki Pro", meta=(DisplayName="IP Address"))` — IP address of the Ki Pro device
- L24 _public member_ `uint16 Port = 80;` — `UPROPERTY(EditAnywhere, Category="Ki Pro", AdvancedDisplay)` — HTTP port for REST API communication
- L28 _public member_ `bool bAutoPlayAfterStop = false;` — `UPROPERTY(EditAnywhere, Category="Ki Pro", meta=(DisplayName="Auto Play After Stop Recording"))` — Automatically start playback after recording stops
- L32 _public member_ `FString FirmwareVersion;` — `UPROPERTY(VisibleAnywhere, Category="Ki Pro", AdvancedDisplay, meta=(DisplayName="Firmware Version"))` — Firmware version retrieved from device (read-only)
