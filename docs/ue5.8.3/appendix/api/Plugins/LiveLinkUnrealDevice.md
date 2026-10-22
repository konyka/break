# Plugins / LiveLinkUnrealDevice

- module root: `Plugins/Animation/LiveLinkUnrealDevice/Source/LiveLinkUnrealDevice`
- headers: 3; symbols: 85
- symbol kinds: class=3, delegate=1, function=4, member=29, prototype=38, struct=10
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, LiveLink, LiveLinkDevice, LiveLinkHub, LiveLinkHubMessaging, LiveLinkSequencer, Messaging, Networking, Projects, Slate, SlateCore, TakeRecorder, TakesCore

### `Plugins/Animation/LiveLinkUnrealDevice/Source/LiveLinkUnrealDevice/Private/Devices/LiveLinkUnrealDevice.h` (Private)


#### class `ULiveLinkUnrealDeviceSettings`  
`class ULiveLinkUnrealDeviceSettings : public ULiveLinkDeviceSettings`  
_L23-51_
- reflection: `UCLASS()`
- inherits: `ULiveLinkDeviceSettings`
- desc: Settings for an Unreal device instance.
- L29 _public function_ `ULiveLinkUnrealDeviceSettings()`
- L36 _public member_ `FLiveLinkHubClientId ClientId;` — `UPROPERTY(EditAnywhere, Category="Unreal Device")` — The editor client known to Live Link Hub to connect to.
- L40 _public member_ `bool bHasRecordStartAuthority = true;` — `UPROPERTY(EditAnywhere, Category="Unreal Device", AdvancedDisplay)` — If true, a "recording started" event from this device will also cause Live Link Hub to begin recording.
- L44 _public member_ `bool bHasRecordStopAuthority = true;` — `UPROPERTY(EditAnywhere, Category="Unreal Device", AdvancedDisplay)` — If true, a "recording stopped" event from this device will also cause Live Link Hub to stop recording.
- L50 _public member_ `bool bHasTakeMetadataAuthority = true;` — `UPROPERTY(EditAnywhere, Category="Unreal Device", AdvancedDisplay, DisplayName="Has Slate Name & Take Number Authority")` — If true, slate/take changed events from this device will also cause Live Link Hub to update. If true, this device will not accept updates to the slate/take sent from Live Link Hub.

#### class `ULiveLinkUnrealDevice`  
`class ULiveLinkUnrealDevice : public ULiveLinkDevice , public ILiveLinkDeviceCapability_Connection , public ILiveLinkDeviceCapability_Recording`  
_L60-143_
- reflection: `UCLASS(meta=(DisplayName="Unreal"))`
- inherits: `ULiveLinkDevice,ILiveLinkDeviceCapability_Connection,ILiveLinkDeviceCapability_Recording`
- desc: A device for connecting to a running Unreal Editor instance. Supports sending/receiving Take Recorder events to/from the remote editor session.
- L67 _public function_ `ULiveLinkUnrealDeviceSettings* GetSettings()`
- L68 _public function_ `const ULiveLinkUnrealDeviceSettings* GetSettings() const`
- L72 _public function_ `virtual TSubclassOf<ULiveLinkDeviceSettings> GetSettingsClass() const override`
- L74 _public prototype_ `virtual EDeviceHealth GetDeviceHealth() const override;`
- L75 _public prototype_ `virtual FText GetHealthText() const override;`
- L77 _public prototype_ `virtual void OnDeviceAdded() override;`
- L78 _public prototype_ `virtual void OnDeviceRemoved() override;`
- L79 _public prototype_ `virtual void OnSettingChanged(const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L84 _public prototype_ `virtual ELiveLinkDeviceConnectionStatus GetConnectionStatus_Implementation() const override;`
- L85 _public prototype_ `virtual FString GetHardwareId_Implementation() const override;`
- L86 _public prototype_ `virtual bool SetHardwareId_Implementation(const FString& InHardwareID) override;`
- L87 _public prototype_ `virtual bool Connect_Implementation() override;`
- L88 _public prototype_ `virtual bool Disconnect_Implementation() override;`
- L90 _protected prototype_ `virtual void SetConnectionStatus(ELiveLinkDeviceConnectionStatus InStatus) override;`
- L95 _public prototype_ `virtual bool StartRecording_Implementation() override;`
- L96 _public prototype_ `virtual bool StopRecording_Implementation() override;`
- L97 _public prototype_ `virtual bool IsRecording_Implementation() const override;`
- L101 _private prototype_ `TPair<EDeviceHealth, FText> GetHealth() const;`
- L104 _private prototype_ `void HandleSlateNameChanged(FStringView InSlateName);` — Take Recorder event handlers.
- L105 _private prototype_ `void HandleTakeNumberChanged(int32 InTakeNumber);`
- L108 _private prototype_ `void HandleMessageCatchall(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);` — Message bus event handlers.
- L109 _private prototype_ `void HandleMessageBusNotification(const FMessageBusNotification& InNotification);`
- L112 _private prototype_ `void Connect();` — Attempts to connect to the configured `ClientId`.
- L115 _private prototype_ `void Disconnect();` — Sends a close message connected editor client (if any).
- L118 _private prototype_ `void OnDisconnect();` — Called to perform cleanup and state transitions for both expected and unexpected disconnections.
- L122 _private member_ `ELiveLinkDeviceConnectionStatus ConnectionStatus = ELiveLinkDeviceConnectionStatus::Disconnected;` — Updated in response to internal state transitions, and reflected in the device UI.
- L125 _private member_ `TSharedPtr<FMessageEndpoint> MessageEndpoint;` — The endpoint used for communicating with the editor.
- L128 _private member_ `FMessageAddress DeviceAddress;` — The address that accepted the aux channel request; we Send() here rather than Publish().
- L131 _private member_ `FGuid ChannelId;` — The aux channel identifier.
- L134 _private member_ `bool bIsRecording = false;` — Recording state is updated in response to device event messages.
- L141 _private member_ `bool bSuppressSlateNameSend = false;` — Guards against feedback loops when receiving slate/take changes from UE. Set true while processing an incoming command so that the resulting ILiveLinkRecordingSession delegate doesn't re-send the same command back.
- L142 _private member_ `bool bSuppressTakeNumberSend = false;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkUnrealDevice, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkUnrealDevice, Log, All);`

### `Plugins/Animation/LiveLinkUnrealDevice/Source/LiveLinkUnrealDevice/Private/LiveLinkHubUnrealDeviceAux.h` (Private)


#### class `FLiveLinkHubUnrealDeviceAuxManager`  
`class FLiveLinkHubUnrealDeviceAuxManager`  
_L26-69_
- desc: Configures a Live Link Hub auxiliary message channel for communicating with Unreal devices. Handles incoming Take Recorder commands, and relays events to connected devices.
- L29 _public prototype_ `FLiveLinkHubUnrealDeviceAuxManager();`
- L30 _public prototype_ `~FLiveLinkHubUnrealDeviceAuxManager();`
- L34 _private prototype_ `void RegisterRequestHandler();` — Init helpers
- L35 _private prototype_ `void RegisterTakeRecorderDelegates();`
- L38 _private prototype_ `void OnRecordingStarted(UTakeRecorder* InRecorder);` — Take Recorder event handlers
- L39 _private prototype_ `void OnRecordingStopped(UTakeRecorder* InRecorder);`
- L40 _private prototype_ `void OnSlateNameChanged(const FString& InSlateName, UTakeMetaData* InTakeMetaData);`
- L41 _private prototype_ `void OnTakeNumberChanged(int32 InTakeNumber, UTakeMetaData* InTakeMetaData);`
- L44 _private prototype_ `bool IsKnownSender(const FMessageAddress& InAddress) const;` — Message handlers
- L46 _private prototype_ `void HandleAuxClose(const FLiveLinkHubAuxChannelCloseMessage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L48 _private prototype_ `void HandleSetSlateName(const FLiveLinkTakeRecorderCmd_SetSlateName& InCmd, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L49 _private prototype_ `void HandleSetTakeNumber(const FLiveLinkTakeRecorderCmd_SetTakeNumber& InCmd, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L50 _private prototype_ `void HandleStartRecording(const FLiveLinkTakeRecorderCmd_StartRecording& InCmd, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L51 _private prototype_ `void HandleStopRecording(const FLiveLinkTakeRecorderCmd_StopRecording& InCmd, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L54 _private prototype_ `void BroadcastToChannels(void* InMessage, UScriptStruct* InTypeInfo, const TOptional<FMessageAddress>& InExclude = {});` — Broadcast a message to all connected channels, optionally excluding one address.
- L57 _private member_ `TSharedPtr<FMessageEndpoint> MessageEndpoint;`
- L59 _private member_ `TMap<FGuid, FMessageAddress> ChannelToAddress;`
- L60 _private member_ `TMap<FMessageAddress, FGuid> AddressToChannel;`
- L67 _private member_ `TOptional<FMessageAddress> SlateNameChangeSource;` — When processing an incoming slate/take change from a remote device, we note the sender address here so that the corresponding outgoing broadcast (triggered by the local delegate) can exclude that sender and avoid a feedback loop.
- L68 _private member_ `TOptional<FMessageAddress> TakeNumberChangeSource;`

### `Plugins/Animation/LiveLinkUnrealDevice/Source/LiveLinkUnrealDevice/Private/LiveLinkUnrealDeviceMessages.h` (Private)


#### struct `FLiveLinkUnrealDeviceAuxChannelRequestMessage`  
`struct FLiveLinkUnrealDeviceAuxChannelRequestMessage : public FLiveLinkHubAuxChannelRequestMessage`  
_L12-15_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkHubAuxChannelRequestMessage`

#### struct `FLiveLinkTakeRecorderMessageBase`  
`struct FLiveLinkTakeRecorderMessageBase`  
_L19-30_
- reflection: `USTRUCT()`
- L23 _public member_ `static constexpr uint8 CurrentVersion = 1;`
- L26 _public member_ `uint8 MessageVersion = CurrentVersion;` — `UPROPERTY()`
- L29 _public member_ `FGuid MessageId;` — `UPROPERTY()`

#### struct `FLiveLinkTakeRecorderSlateInfo`  
`struct FLiveLinkTakeRecorderSlateInfo`  
_L34-46_
- reflection: `USTRUCT()`
- L39 _public member_ `TOptional<FString> SlateName;` — `UPROPERTY()`
- L42 _public member_ `TOptional<int32> TakeNumber;` — `UPROPERTY()`
- L45 _public member_ `TOptional<FString> Description;` — `UPROPERTY()`

#### struct `FLiveLinkTakeRecorderCmd_SetSlateName`  
`struct FLiveLinkTakeRecorderCmd_SetSlateName : public FLiveLinkTakeRecorderMessageBase`  
_L53-59_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkTakeRecorderMessageBase`
- L58 _public member_ `FString SlateName;` — `UPROPERTY()`

#### struct `FLiveLinkTakeRecorderCmd_SetTakeNumber`  
`struct FLiveLinkTakeRecorderCmd_SetTakeNumber : public FLiveLinkTakeRecorderMessageBase`  
_L63-69_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkTakeRecorderMessageBase`
- L68 _public member_ `int32 TakeNumber = 0;` — `UPROPERTY()`

#### struct `FLiveLinkTakeRecorderCmd_StartRecording`  
`struct FLiveLinkTakeRecorderCmd_StartRecording : public FLiveLinkTakeRecorderMessageBase`  
_L73-79_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkTakeRecorderMessageBase`
- L78 _public member_ `FLiveLinkTakeRecorderSlateInfo SlateInfo;` — `UPROPERTY()`

#### struct `FLiveLinkTakeRecorderCmd_StopRecording`  
`struct FLiveLinkTakeRecorderCmd_StopRecording : public FLiveLinkTakeRecorderMessageBase`  
_L83-86_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkTakeRecorderMessageBase`

#### struct `FLiveLinkTakeRecorderEvent_RecordingStarting`  
`struct FLiveLinkTakeRecorderEvent_RecordingStarting : public FLiveLinkTakeRecorderMessageBase`  
_L93-99_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkTakeRecorderMessageBase`
- L98 _public member_ `float CountdownSec = 0.0;` — `UPROPERTY()`

#### struct `FLiveLinkTakeRecorderEvent_RecordingStarted`  
`struct FLiveLinkTakeRecorderEvent_RecordingStarted : public FLiveLinkTakeRecorderMessageBase`  
_L103-109_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkTakeRecorderMessageBase`
- L108 _public member_ `FTimecode StartTimecode;` — `UPROPERTY()`

#### struct `FLiveLinkTakeRecorderEvent_RecordingStopped`  
`struct FLiveLinkTakeRecorderEvent_RecordingStopped : public FLiveLinkTakeRecorderMessageBase`  
_L113-122_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkTakeRecorderMessageBase`
- L118 _public member_ `FTimecode EndTimecode;` — `UPROPERTY()`
- L121 _public member_ `bool bCancelled = false;` — `UPROPERTY()`
