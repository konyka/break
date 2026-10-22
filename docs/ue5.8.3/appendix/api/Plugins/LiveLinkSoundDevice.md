# Plugins / LiveLinkSoundDevice

- module root: `Plugins/VirtualProduction/LiveLinkSoundDevice/Source/LiveLinkSoundDevice`
- headers: 3; symbols: 69
- symbol kinds: class=3, enum=1, enumerator=3, member=23, prototype=38, struct=1
- PrivateDependencyModuleNames: CoreUObject, Engine, HTTP, Json, JsonUtilities, LiveLinkDevice, LiveLinkInterface, Networking, Projects, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/LiveLinkSoundDevice/Source/LiveLinkSoundDevice/Public/HttpDigestAuth.h` (Public)


#### struct `FDigestChallenge`  
`struct FDigestChallenge`  
_L10-17_
- desc: Challenge data parsed from HTTP Digest WWW-Authenticate header
- L12 _public member_ `FString Realm;`
- L13 _public member_ `FString Nonce;`
- L14 _public member_ `FString Qop;` — Quality of protection (e.g., "auth", "auth-int")
- L15 _public member_ `FString Opaque;`
- L16 _public member_ `FString Algorithm;` — e.g., "MD5", "SHA-256"

#### class `FHttpDigestAuthHelper`  
`class FHttpDigestAuthHelper`  
_L22-71_
- desc: Helper class for HTTP Digest Authentication (RFC 2617)
- L31 _public prototype_ `static bool ParseDigestChallenge(const FString& AuthHeader, FDigestChallenge& OutChallenge);` — Parse WWW-Authenticate header from 401 response @param AuthHeader The WWW-Authenticate header value @param OutChallenge Parsed challenge data @return true if parsing succeeded
- L42 _public prototype_ `static FString GenerateDigestResponse( const FString& Username, const FString& Password, const FString& Method, const FString& URI, const FDigestChallenge& Challenge);` — Generate Authorization header value for authenticated request @param Username Username for authentication @param Password Password for authentication @param Method HTTP method (GET, POST, etc.) @param URI Request URI path @param Challenge Challenge data from server @return Authorization header value (includes "Digest " prefix)
- L55 _private prototype_ `static FString ComputeMD5Hash(const FString& Input);` — Compute MD5 hash of input string @param Input String to hash @return Lowercase hex string of MD5 digest
- L61 _private prototype_ `static FString GenerateNonce();` — Generate random nonce for client @return Hex string nonce
- L70 _private prototype_ `static bool ParseHeaderPair(const FString& Pair, FString& OutKey, FString& OutValue);` — Parse key=value or key="value" pair from header @param Pair String containing key=value @param OutKey Extracted key @param OutValue Extracted value (quotes removed) @return true if parsing succeeded

### `Plugins/VirtualProduction/LiveLinkSoundDevice/Source/LiveLinkSoundDevice/Public/LiveLinkSoundDeviceBase.h` (Public)


#### class `ULiveLinkSoundDeviceBase`  
`class ULiveLinkSoundDeviceBase : public ULiveLinkDevice , public ILiveLinkDeviceCapability_Connection , public ILiveLinkDeviceCapability_Recording`  
_L21-153_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "Sound Devices Recorder", ToolTip = "Support for Sound Devices recorders (MixPre, 888, Scorpio)"))`
- inherits: `ULiveLinkDevice,ILiveLinkDeviceCapability_Connection,ILiveLinkDeviceCapability_Recording`
- desc: Concrete implementation for Sound Devices recording devices Provides both Connection and Recording capabilities via REST API with HTTP Digest Authentication
- L29 _public prototype_ `virtual TSubclassOf<ULiveLinkDeviceSettings> GetSettingsClass() const override;`
- L30 _public prototype_ `virtual EDeviceHealth GetDeviceHealth() const override;`
- L31 _public prototype_ `virtual FText GetHealthText() const override;`
- L32 _public prototype_ `virtual void OnDeviceAdded() override;`
- L33 _public prototype_ `virtual void OnDeviceRemoved() override;`
- L34 _public prototype_ `virtual void OnSettingChanged(const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L38 _public prototype_ `virtual ELiveLinkDeviceConnectionStatus GetConnectionStatus_Implementation() const override;`
- L39 _public prototype_ `virtual FString GetHardwareId_Implementation() const override;`
- L40 _public prototype_ `virtual bool SetHardwareId_Implementation(const FString& HardwareID) override;`
- L41 _public prototype_ `virtual bool CanSetHardwareId_Implementation() override;`
- L42 _public prototype_ `virtual bool Connect_Implementation() override;`
- L43 _public prototype_ `virtual bool Disconnect_Implementation() override;`
- L47 _public prototype_ `virtual bool StartRecording_Implementation() override;`
- L48 _public prototype_ `virtual bool StopRecording_Implementation() override;`
- L49 _public prototype_ `virtual bool IsRecording_Implementation() const override;`
- L54 _private prototype_ `FString GetBaseUrl() const;` — Build base URL for Sound Devices REST API
- L57 _private prototype_ `FString GetCommandUrl(const FString& Command) const;` — Build full command URL
- L60 _private prototype_ `FString GetRequestURI(const FString& Command) const;` — Get URI path for authentication (without host/port)
- L63 _private prototype_ `void SendCommand(const FString& Command, TFunction<void(bool bSuccess, const FString& Response)> OnComplete);` — Send authenticated command to device
- L66 _private prototype_ `TSharedRef<class IHttpRequest> CreateRequest(const FString& Command);` — Create HTTP request for a command
- L69 _private prototype_ `void RetryWithAuth(const FString& Command, const FDigestChallenge& Challenge, TFunction<void(bool, const FString&)> OnComplete);` — Retry request with Digest authentication
- L72 _private prototype_ `void GetTransportState(TFunction<void(bool bSuccess, const FString& StateText)> OnComplete);` — Get transport state from device
- L75 _private prototype_ `void SetSetting(const FString& Key, const FString& Value, TFunction<void(bool bSuccess)> OnComplete);` — Set device parameter (slate, take, etc.)
- L78 _private prototype_ `void ConfigureDrivesForRecording();` — Ensure all drives are in Record mode (not File Transfer)
- L81 _private prototype_ `void PollTransportState();` — Poll transport state until target state is reached
- L84 _private prototype_ `void OnTransportStateReceived(bool bSuccess, const FString& StateText);` — Called when transport state polling completes
- L87 _private prototype_ `void OnRecordingStopped();` — Called when recording stop is confirmed
- L90 _private prototype_ `void RetrieveFileMetadata(const FString& FilePath);` — Retrieve file metadata after recording
- L93 _private prototype_ `static FString NormalizeFilePath(const FString& Path);` — Normalize file path from HD{i} format to Drive_{i} format
- L96 _private prototype_ `bool DeviceTick(float DeltaTime);` — Main device tick function (handles reconnection and polling)
- L99 _private prototype_ `void AttemptReconnection();` — Attempt reconnection if disconnected
- L102 _private prototype_ `void HandleSlateNameChanged(FStringView InSlateName);` — Handle slate name changes from recording session
- L105 _private prototype_ `void HandleTakeNumberChanged(int32 InTakeNumber);` — Handle take number changes from recording session
- L110 _protected member_ `TSubclassOf<ULiveLinkDeviceSettings> SettingsClass;` — `UPROPERTY(EditDefaultsOnly, Category="Live Link Device")` — Settings class to use for Sound Devices
- L114 _protected member_ `ELiveLinkDeviceConnectionStatus ConnectionStatus = ELiveLinkDeviceConnectionStatus::Disconnected;` — `UPROPERTY()` — Current connection status
- L118 _protected member_ `bool bIsRecording = false;` — `UPROPERTY()` — Whether the device is currently recording
- L121 _protected member_ `FTSTicker::FDelegateHandle DeviceTickerHandle;` — Ticker handle for main device tick (reconnection and polling)
- L130 _protected member_ `EPollingOperation CurrentPollingOperation = EPollingOperation::None;`
- L133 _protected member_ `double PollingStartTime = 0.0;` — Time when polling started (for timeout)
- L136 _protected member_ `float ReconnectionTimeAccumulator = 0.0f;` — Time accumulator for reconnection attempts
- L139 _protected member_ `bool bPollingRequestInFlight = false;` — Flag to prevent polling request flood on slow connections
- L142 _protected member_ `FDigestChallenge CachedChallenge;` — Cached Digest challenge for reuse (optimization)
- L143 _protected member_ `bool bHasCachedChallenge = false;`
- L146 _protected member_ `static constexpr double PollingTimeoutSeconds = 4.0;` — Polling timeout in seconds
- L149 _protected member_ `static constexpr float PollingIntervalSeconds = 0.1f;` — Polling interval in seconds
- L152 _protected member_ `static constexpr float ReconnectionIntervalSeconds = 5.0f;` — Reconnection attempt interval in seconds

#### enum `ULiveLinkSoundDeviceBase::EPollingOperation`  
`enum class EPollingOperation`  
_L124-129_
- desc: What operation we're polling for
- L126 _public enumerator_ `None`
- L127 _public enumerator_ `WaitingForRecording` — Polling for "rec" state
- L128 _public enumerator_ `WaitingForIdle` — Polling for "stop" state

### `Plugins/VirtualProduction/LiveLinkSoundDevice/Source/LiveLinkSoundDevice/Public/LiveLinkSoundDeviceSettings.h` (Public)


#### class `ULiveLinkSoundDeviceSettings`  
`class ULiveLinkSoundDeviceSettings : public ULiveLinkDeviceSettings`  
_L13-37_
- reflection: `UCLASS()`
- inherits: `ULiveLinkDeviceSettings`
- desc: Settings for Sound Devices recording device
- L20 _public member_ `FString IpAddress = TEXT("192` — `UPROPERTY(EditAnywhere, Category="Sound Devices", meta=(DisplayName="IP Address"))` — IP address of the Sound Devices device
- L24 _public member_ `uint16 Port = 80;` — `UPROPERTY(EditAnywhere, Category="Sound Devices", AdvancedDisplay)` — HTTP port for REST API communication
- L28 _public member_ `FString Username = TEXT("gue` — `UPROPERTY(EditAnywhere, Category="Sound Devices", AdvancedDisplay)` — Username for HTTP Digest Authentication
- L32 _public member_ `FString Password = TEXT("gue` — `UPROPERTY(EditAnywhere, Category="Sound Devices", AdvancedDisplay)` — Password for HTTP Digest Authentication
- L36 _public member_ `FString DeviceModel;` — `UPROPERTY(VisibleAnywhere, Category="Sound Devices", AdvancedDisplay, meta=(DisplayName="Device Model"))` — Device model retrieved from device (read-only)
