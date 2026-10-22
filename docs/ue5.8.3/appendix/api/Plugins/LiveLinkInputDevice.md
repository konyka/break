# Plugins / LiveLinkInputDevice

- module root: `Plugins/VirtualProduction/LiveLinkInputDevice/Source/LiveLinkInputDevice`
- headers: 7; symbols: 74
- symbol kinds: class=6, delegate=2, function=9, member=21, prototype=35, struct=1
- PrivateDependencyModuleNames: ApplicationCore, CoreUObject, Engine, InputDevice, Slate, SlateCore
- PublicDependencyModuleNames: Core, LiveLinkInterface

### `Plugins/VirtualProduction/LiveLinkInputDevice/Source/LiveLinkInputDevice/Private/LiveLinkInputDeviceMessageHandler.h` (Private)


#### class `FLiveLinkInputDeviceMessageHandler`  
`class FLiveLinkInputDeviceMessageHandler : public FGenericApplicationMessageHandler`  
_L10-27_
- inherits: `FGenericApplicationMessageHandler`
- L13 _public prototype_ `virtual ~FLiveLinkInputDeviceMessageHandler() = default;`
- L15 _public prototype_ `virtual bool OnControllerAnalog(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, float AnalogValue) override;`
- L16 _public prototype_ `virtual bool OnControllerButtonPressed(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, bool IsRepeat) override;`
- L17 _public prototype_ `virtual bool OnControllerButtonReleased(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, bool IsRepeat) override;`
- L20 _public prototype_ `FLiveLinkGamepadInputDeviceFrameData GetLatestValue(FInputDeviceId InDeviceId) const;` — For the given device id, which maps the the controller id, get the latest frame values for that device.
- L23 _public prototype_ `TSet<FInputDeviceId> GetDeviceIds() const;` — Return the current known list of devices
- L26 _private member_ `TMap<FInputDeviceId, FLiveLinkGamepadInputDeviceFrameData> CurrentFrameDataValues;`

### `Plugins/VirtualProduction/LiveLinkInputDevice/Source/LiveLinkInputDevice/Private/SLiveLinkInputDeviceSourceFactory.h` (Private)


#### class `SLiveLinkInputDeviceSourceFactory`  
`class SLiveLinkInputDeviceSourceFactory : public SCompoundWidget`  
_L19-39_
- inherits: `SCompoundWidget`
- L21 _private function_ `SLATE_BEGIN_ARGS(SLiveLinkInputDeviceSourceFactory)`
- L23 _private prototype_ `SLATE_EVENT(FOnLiveLinkInputDeviceConnectionSettingsAccepted, OnConnectionSettingsAccepted) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L30 _private member_ `FLiveLinkInputDeviceConnectionSettings ConnectionSettings;`
- L33 _private member_ `TSharedPtr<FStructOnScope> StructOnScope;`
- L34 _private member_ `TSharedPtr<IStructureDetailsView> StructureDetailsView;`
- L37 _private prototype_ `FReply OnSettingsAccepted();`
- L38 _private member_ `FOnLiveLinkInputDeviceConnectionSettingsAccepted OnConnectionSettingsAccepted;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLiveLinkInputDeviceConnectionSettingsAccepted, FLiveLinkInputDeviceConnectionSettings);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLiveLinkInputDeviceConnectionSettingsAccepted, FLiveLinkInputDeviceConnectionSettings);`

### `Plugins/VirtualProduction/LiveLinkInputDevice/Source/LiveLinkInputDevice/Public/LiveLinkInputDevice.h` (Public)


#### class `FLiveLinkInputDeviceModule`  
`class FLiveLinkInputDeviceModule : public IModuleInterface`  
_L14-26_
- inherits: `IModuleInterface`
- desc: This module provides access to a restricted set of the InputDevice system over Live Link without using the Game Input Device Subsystem. This allows us to poll / query the input devices from another thread for recording and animating purposes.
- L18 _public function_ `static FLiveLinkInputDeviceModule& Get()`
- L24 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L25 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkInputDevice, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkInputDevice, Log, All);`

### `Plugins/VirtualProduction/LiveLinkInputDevice/Source/LiveLinkInputDevice/Public/LiveLinkInputDeviceConnectionSettings.h` (Public)


#### struct `FLiveLinkInputDeviceConnectionSettings`  
`struct FLiveLinkInputDeviceConnectionSettings`  
_L8-11_
- reflection: `USTRUCT()`

### `Plugins/VirtualProduction/LiveLinkInputDevice/Source/LiveLinkInputDevice/Public/LiveLinkInputDeviceSource.h` (Public)


#### class `FLiveLinkInputDeviceSource`  
`class FLiveLinkInputDeviceSource : public ILiveLinkSource, public FRunnable, public TSharedFromThis<FLiveLinkInputDeviceSource>`  
_L26-120_
- inherits: `ILiveLinkSource,FRunnable,TSharedFromThis<FLiveLinkInputDeviceSource>`
- L30 _public prototype_ `FLiveLinkInputDeviceSource(const FLiveLinkInputDeviceConnectionSettings& ConnectionSettings);`
- L32 _public prototype_ `virtual ~FLiveLinkInputDeviceSource();`
- L35 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;`
- L36 _public prototype_ `virtual void InitializeSettings(ULiveLinkSourceSettings* Settings) override;`
- L37 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L39 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L41 _public function_ `virtual FText GetSourceType() const override`
- L42 _public function_ `virtual FText GetSourceMachineName() const override`
- L43 _public function_ `virtual FText GetSourceStatus() const override`
- L45 _public function_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const override`
- L49 _public function_ `virtual bool Init() override`
- L50 _public prototype_ `virtual uint32 Run() override;`
- L51 _public prototype_ `void Start();`
- L52 _public prototype_ `virtual void Stop() override;`
- L53 _public function_ `virtual void Exit() override`
- L57 _private prototype_ `TOptional<FLiveLinkStaticDataStruct> PollGamepadStaticData(FInputDeviceId SubjectName);`
- L58 _private prototype_ `TOptional<FLiveLinkFrameDataStruct> PollGamepadFrameData(FInputDeviceId SubjectName);`
- L60 _private prototype_ `void Send(FInputDeviceId DeviceId, FLiveLinkStaticDataStruct FrameDataToSend);`
- L61 _private prototype_ `void Send(FInputDeviceId DeviceId, FLiveLinkFrameDataStruct StaticDataToSend);`
- L64 _private prototype_ `bool TickInputDevices(const double InCurrentTime);` — Ticks each input device and calls SendControllerEvents to update the device with our message handler.
- L67 _private prototype_ `double DevicePollWaitTime() const;` — Time in seconds to wait before polling the device values again.
- L71 _private prototype_ `void HandleGamepadDeviceChange(EInputDeviceConnectionState NewConnectionState, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId);` — This delegate is invoked when a gamepad device is added or removed from the application.
- L74 _private prototype_ `void UpdateGamepadState(const bool bInState);` — Update the our known gamepad state so that it can be reflected back to the LiveLink UI.
- L77 _private prototype_ `void LoadInputPlugins();` — Create load all input devices by calling CreateInputDevice.
- L79 _private member_ `ILiveLinkClient* Client;`
- L82 _private member_ `FGuid SourceGuid;` — Our identifier in LiveLink
- L85 _private member_ `FText SourceType;` — Text objects that are reflected back in the Live Link UI.
- L86 _private member_ `FText SourceMachineName;`
- L87 _private member_ `FText SourceStatus;`
- L90 _private member_ `FThreadSafeBool Stopping;` — Threadsafe Bool for terminating the main thread loop
- L93 _private member_ `TUniquePtr<FRunnableThread> Thread;` — Thread to run updates on
- L96 _private member_ `FString ThreadName;` — Name of the updates thread
- L99 _private member_ `TSet<FInputDeviceId> EncounteredSubjects;` — List of subjects we've already encountered
- L102 _private member_ `FDelegateHandle DeferredStartDelegateHandle;` — Deferred start delegate handle
- L105 _private member_ `uint32 LocalUpdateRateInHz = 100;` — Rate at which we poll the input devices.
- L108 _private member_ `TSharedPtr<class FLiveLinkInputDeviceMessageHandler> MessageHandler;` — Our local message handler.
- L111 _private member_ `TArray<TSharedPtr<IInputDevice>> InputDevices;` — List of known input devices registered with this source.
- L114 _private member_ `bool bHasLoadedInputPlugins = false;` — Bool to track if we have loaded our input plugins.  This should only be done once by querying the input device modular feature.
- L117 _private member_ `bool bIsGamepadConnected = false;` — Indicates if we have ANY gamepads connected and thus are an active device for Live Link.
- L119 _private member_ `std::atomic<bool> bShouldRefreshDeviceList = false;`

### `Plugins/VirtualProduction/LiveLinkInputDevice/Source/LiveLinkInputDevice/Public/LiveLinkInputDeviceSourceFactory.h` (Public)


#### class `ULiveLinkInputDeviceSourceFactory`  
`class ULiveLinkInputDeviceSourceFactory : public ULiveLinkSourceFactory`  
_L10-24_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceFactory`
- L15 _public prototype_ `virtual FText GetSourceDisplayName() const override;`
- L16 _public prototype_ `virtual FText GetSourceTooltip() const override;`
- L18 _public function_ `virtual EMenuType GetMenuType() const override`
- L19 _public prototype_ `virtual TSharedPtr<SWidget> BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const override;`
- L20 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const override;`
- L23 _private prototype_ `void CreateSourceFromSettings(FLiveLinkInputDeviceConnectionSettings ConnectionSettings, FOnLiveLinkSourceCreated OnSourceCreated) const;`

### `Plugins/VirtualProduction/LiveLinkInputDevice/Source/LiveLinkInputDevice/Public/LiveLinkInputDeviceSourceSettings.h` (Public)


#### class `ULiveLinkInputDeviceSourceSettings`  
`class ULiveLinkInputDeviceSourceSettings : public ULiveLinkSourceSettings`  
_L10-13_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceSettings`
