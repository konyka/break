# Plugins / LiveLinkOBSDevice

- module root: `Plugins/VirtualProduction/LiveLinkOBSDevice/Source/LiveLinkOBSDevice`
- headers: 2; symbols: 76
- symbol kinds: class=3, delegate=1, function=5, member=23, prototype=43, typedef=1
- PrivateDependencyModuleNames: CaptureManagerSettings, CaptureManagerTakeMetadata, CaptureUtils, Core, CoreUObject, Engine, IngestLiveLinkDevice, Json, LiveLinkCapabilities, LiveLinkDevice, LiveLinkHub, LiveLinkInterface, NamingTokens, NamingTokensUI, PropertyEditor, Slate, SlateCore, VideoLiveLinkDeviceCommon, WebSockets

### `Plugins/VirtualProduction/LiveLinkOBSDevice/Source/LiveLinkOBSDevice/Private/Customization/LiveLinkOBSDeviceSettingsCustomization.h` (Private)


#### class `FLiveLinkOBSDeviceSettingsCustomization`  
`class FLiveLinkOBSDeviceSettingsCustomization : public IDetailCustomization`  
_L10-18_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/VirtualProduction/LiveLinkOBSDevice/Source/LiveLinkOBSDevice/Private/Devices/LiveLinkOBSDevice.h` (Private)


#### class `ULiveLinkOBSDeviceSettings`  
`class ULiveLinkOBSDeviceSettings : public ULiveLinkDeviceSettings`  
_L21-58_
- reflection: `UCLASS()`
- inherits: `ULiveLinkDeviceSettings`
- desc: Persisted settings for an OBS device instance.
- L27 _public function_ `ULiveLinkOBSDeviceSettings()`
- L34 _public member_ `FString Host = TEXT("127` — `UPROPERTY(EditAnywhere, Category="OBS Device")` — Host running OBS WebSocket server (e.g. 127.0.0.1 or a remote IP).
- L38 _public member_ `int32 Port = 4455;` — `UPROPERTY(EditAnywhere, Category="OBS Device")` — Port configured in OBS Tools > WebSocket Server Settings (default 4455).
- L42 _public member_ `FString Password;` — `UPROPERTY(EditAnywhere, Category="OBS Device", meta=(PasswordField=true))` — Password set in OBS WebSocket Server Settings. Leave empty if authentication is disabled.
- L57 _public member_ `FString FilenameFormat = TEXT("{se` — `UPROPERTY(EditAnywhere, Category="OBS Device", meta=(NamingTokens))` — Format string for the OBS recording filename. Uses NamingTokens syntax; wrap token names in curly braces. LLH tokens (namespace "llh"): {slate}, {take}, {session}, {config} Global tokens: {project}, {user}, {yyyy}, {mm}, {Ddd}, etc. This format is also used to identify and parse takes when browsing the OBS recording directory. For example, {slate}-{take} will correctly extract the slate name and take number from "MySlate-01.mp4". Recordings that don't match the current format are still discovered, using the full filename as the slate name.

#### class `ULiveLinkOBSDevice`  
`class ULiveLinkOBSDevice : public UBaseIngestLiveLinkDevice , public ILiveLinkDeviceCapability_Connection , public ILiveLinkDeviceCapability_Recording`  
_L74-287_
- reflection: `UCLASS(BlueprintType, meta=(DisplayName="OBS Studio"))`
- inherits: `UBaseIngestLiveLinkDevice,ILiveLinkDeviceCapability_Connection,ILiveLinkDeviceCapability_Recording`
- desc: Live Link Hub device that controls OBS Studio recording via the OBS WebSocket v5 protocol. Supports: - Start / Stop recording (driven by the Live Link Hub recording session) - Setting the recording filename (driven by the Hub slate name) - Ingest of recorded video files as mono takes into Capture Manager
- L81 _public function_ `ULiveLinkOBSDeviceSettings* GetSettings()`
- L82 _public function_ `const ULiveLinkOBSDeviceSettings* GetSettings() const`
- L85 _public function_ `virtual TSubclassOf<ULiveLinkDeviceSettings> GetSettingsClass() const override`
- L86 _public prototype_ `virtual EDeviceHealth GetDeviceHealth() const override;`
- L87 _public prototype_ `virtual FText GetHealthText() const override;`
- L88 _public prototype_ `virtual void OnDeviceAdded() override;`
- L89 _public prototype_ `virtual void OnDeviceRemoved() override;`
- L90 _public prototype_ `virtual void OnSettingChanged(const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L94 _public prototype_ `virtual ELiveLinkDeviceConnectionStatus GetConnectionStatus_Implementation() const override;`
- L95 _public prototype_ `virtual FString GetHardwareId_Implementation() const override;`
- L96 _public function_ `virtual bool SetHardwareId_Implementation(const FString& InHardwareID) override`
- L97 _public prototype_ `virtual bool Connect_Implementation() override;`
- L98 _public prototype_ `virtual bool Disconnect_Implementation() override;`
- L100 _protected prototype_ `virtual void SetConnectionStatus(ELiveLinkDeviceConnectionStatus InStatus) override;`
- L105 _public prototype_ `virtual bool StartRecording_Implementation() override;`
- L106 _public prototype_ `virtual bool StopRecording_Implementation() override;`
- L107 _public prototype_ `virtual bool IsRecording_Implementation() const override;`
- L112 _private prototype_ `virtual FString GetFullTakePath(UE::CaptureManager::FTakeId InTakeId) const override;`
- L113 _private prototype_ `virtual void RunConvertAndUploadTake(const UIngestCapability_ProcessHandle* InProcessHandle, const UIngestCapability_Options* InIngestOptions) override;`
- L114 _private prototype_ `virtual void RunUpdateTakeList(UIngestCapability_UpdateTakeListCallback* InCallback) override;`
- L122 _private prototype_ `void Connect();` — Open the WebSocket connection to OBS.
- L125 _private prototype_ `void Disconnect();` — Close the WebSocket connection gracefully.
- L128 _private prototype_ `void OnDisconnect();` — Reset transient state (called on any disconnect path).
- L135 _private prototype_ `void HandleConnected();` — Called when the WebSocket connects. OBS sends a Hello immediately after.
- L138 _private prototype_ `void HandleMessage(const FString& InMessage);` — Called when the WebSocket receives a text message from OBS.
- L141 _private prototype_ `void HandleClosed(int32 StatusCode, const FString& Reason, bool bWasClean);` — Called when the WebSocket connection is lost.
- L144 _private prototype_ `void HandleError(const FString& Error);` — Called when the WebSocket encounters an error.
- L151 _private prototype_ `void HandleHello(const TSharedRef<FJsonObject>& InPayload);` — Op 0 (Hello): OBS announces its version and optional auth challenge.
- L154 _private prototype_ `void HandleEvent(const TSharedRef<FJsonObject>& InPayload);` — Op 5 (Event): OBS pushed an event (e.g. RecordStateChanged).
- L157 _private prototype_ `void HandleResponse(const TSharedRef<FJsonObject>& InPayload);` — Op 7 (Response): OBS is responding to a request we sent.
- L164 _private prototype_ `void SendIdentify(const FString& InAuthResponse);` — Send an Identify (op 1) message. Pass the computed auth response, or empty string if auth is not required.
- L167 _private typedef_ `using FResponseCallback = TFunction<void(const TSharedRef<FJsonObject>& ResponseData, bool bSuccess)>;` — Callback type for handling async OBS request responses.
- L173 _private prototype_ `FString SendRequest(const FString& InRequestType, TSharedPtr<FJsonObject> InRequestData = nullptr, FResponseCallback InCallback = nullptr);` — Send a request (op 6) to OBS. Returns the request ID used. If a callback is provided, it will be invoked when the response arrives.
- L176 _private prototype_ `void SendRaw(const FString& InJson);` — Build and send a raw JSON string over the WebSocket.
- L181 _private prototype_ `void HandleSlateNameChanged(FStringView InSlateName);`
- L182 _private prototype_ `void HandleTakeNumberChanged(int32 InTakeNumber);`
- L185 _private prototype_ `FString EvaluateFilenameFormat() const;` — Evaluate the FilenameFormat naming-tokens template and return the result.
- L192 _private prototype_ `void QueryOriginalFilenameFormatting();` — Query the original FilenameFormatting value from OBS and cache it. Called after identification. Also sent as part of the recording start sequence so the cached value is always fresh when we restore.
- L195 _private prototype_ `void RestoreOriginalFilenameFormatting();` — Restore the original OBS FilenameFormatting that was cached.
- L202 _private prototype_ `void QueryRecordDirectory();` — Query OBS for its configured record directory and cache the result.
- L205 _private prototype_ `void AddTakeFromRecording(const FString& InOutputPath);` — Build a take from a completed recording (real-time path, known slate/take).
- L208 _private prototype_ `TOptional<FTakeMetadata> ReadTakeFromFile(const FString& InVideoFilePath, const FString& InDiscoveryExpression) const;` — Build a take from a discovered video file (directory scan path, parsed naming).
- L211 _private prototype_ `static bool IsOBSVideoFile(const FString& InFilePath);` — Returns true if the file extension is a video format OBS can produce.
- L217 _private prototype_ `static FString DeriveDiscoveryExpression(const FString& InFilenameFormat);` — Convert a FilenameFormat (NamingTokens syntax) to a TakeDiscoveryExpression. E.g. "{slate}-{take}" -> "<Slate>-<Take>", "{slate}_{take}_{yyyy}" -> "<Slate>_<Take>_<Any>"
- L224 _private prototype_ `static FString ComputeAuthResponse(const FString& InPassword, const FString& InChallenge, const FString& InSalt);` — Compute the OBS WebSocket v5 auth response string.
- L230 _private member_ `ELiveLinkDeviceConnectionStatus ConnectionStatus = ELiveLinkDeviceConnectionStatus::Disconnected;`
- L232 _private member_ `TSharedPtr<IWebSocket> WebSocket;`
- L235 _private member_ `bool bIdentified = false;` — True once OBS has accepted our Identify message (op 2 Identified received).
- L238 _private member_ `bool bIsRecording = false;` — Current recording state as reported by OBS events.
- L241 _private member_ `uint32 RequestCounter = 0;` — Counter for generating unique request IDs.
- L244 _private member_ `bool bIntentionalDisconnect = false;` — True when Disconnect() was called deliberately; suppresses the auto-reconnect.
- L247 _private member_ `bool bAuthFailed = false;` — True when OBS rejected our authentication (close code 4009); suppresses reconnect and shows an error.
- L250 _private member_ `bool bPasswordRequired = false;` — True when OBS requires authentication but the password field is blank.
- L253 _private member_ `bool bReconnectAfterSettingsChange = false;` — True when a connection setting changed while connected; triggers a reconnect once the current disconnect completes.
- L256 _private member_ `FTSTicker::FDelegateHandle ReconnectTickerHandle;` — Handle for the pending reconnect ticker. Valid only while a reconnect is scheduled.
- L259 _private member_ `static constexpr float ReconnectDelay = 5.f;` — Seconds to wait before attempting to reconnect after an unexpected disconnect.
- L262 _private member_ `TMap<FString, FResponseCallback> PendingCallbacks;` — Pending response callbacks keyed by request ID.
- L265 _private member_ `FString CachedRecordDirectory;` — Cached OBS record directory, queried via GetRecordDirectory after identification.
- L271 _private member_ `FString OriginalFilenameFormatting;` — The user's original FilenameFormatting value from the OBS profile, captured at connect time. Restored after each Hub-driven recording so manual OBS recordings use the user's own format.
- L274 _private member_ `bool bOriginalFilenameCached = false;` — True once OriginalFilenameFormatting has been successfully read from OBS.
- L277 _private member_ `TMap<int32, FString> FullTakePaths;` — Maps TakeId -> full file path on disk. Guarded by FullTakePathsMutex.
- L280 _private member_ `mutable FCriticalSection FullTakePathsMutex;` — Protects FullTakePaths — accessed from game thread and background ingest tasks.
- L283 _private member_ `FString RecordingSlateName;` — Slate name captured at StartRecording time (for accurate auto-add).
- L286 _private member_ `int32 RecordingTakeNumber = INDEX_NONE;` — Take number captured at StartRecording time (for accurate auto-add).

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkOBSDevice, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkOBSDevice, Log, All);`
