# Plugins / WinDualShock

- module root: `Plugins/Runtime/Windows/WinDualShock/Source/WinDualShock`
- headers: 5; symbols: 73
- symbol kinds: class=9, enum=2, enumerator=9, function=29, member=17, namespace=1, prototype=4, struct=1, typedef=1
- PublicDependencyModuleNames: ApplicationCore, AudioExtensions, AudioMixer, AudioMixerCore, Core, CoreUObject, Engine, InputDevice, Projects, Slate

### `Plugins/Runtime/Windows/WinDualShock/Source/WinDualShock/Private/WinDualShock.h` (Private)


#### enum `EWinDualShockPortType`  
`enum EWinDualShockPortType`  
_L20-25_
- desc: Supported endpoint types
- L22 _public enumerator_ `PadSpeakers`
- L23 _public enumerator_ `Vibration` — ignored on DualShock controllers
- L24 _public enumerator_ `WinDualShockPortType_Count`

#### struct `FDeviceKey`  
`struct FDeviceKey`  
_L30-39_
- desc: Unique DeviceID,UserIndex pair
- L32 _public member_ `Audio::FDeviceId DeviceID;`
- L33 _public member_ `int32 UserIndex;`
- L35 _public function_ `inline bool operator ==(const FDeviceKey& Other) const`

#### class `IWinDualShockAudioDevice`  
`class IWinDualShockAudioDevice`  
_L52-102_
- desc: Interface to audio device in a DualShock or DualSense controller. One of these created for each active FAudioDevice::DeviceID since endpoints will be created for each of those devices that will ultimately be routed here.
- L55 _public function_ `IWinDualShockAudioDevice(const FDeviceKey& InDeviceKey) : DeviceKey(InDeviceKey)`
- L63 _public prototype_ `virtual void SetupAudio(ESonyControllerType ControllerType) = 0;` — Initialize an audio device for the controller type specified
- L68 _public prototype_ `virtual void TearDownAudio() = 0;` — Destroy audio device
- L73 _public prototype_ `virtual void PushAudio(EWinDualShockPortType PortType, const TArrayView<const float>& InAudio, const int32& NumChannels) = 0;` — Push audio frame to endpoint on device
- L79 _public function_ `bool AddEndpoint(EWinDualShockPortType PortType)` — Endpoint reference counting to know when device is no longer needed Returns true only for the first endpoint of a port type, to avoid multiple audio sends interleaving
- L84 _public function_ `void RemoveEndpoint(EWinDualShockPortType PortType)`
- L88 _public function_ `int GetEndpointCount() const`
- L94 _public function_ `FDeviceKey GetDeviceKey() const`
- L100 _protected member_ `FDeviceKey DeviceKey;`
- L101 _protected member_ `std::atomic<int> EndpointCount[WinDualShockPortType_Count]{ 0 };`

#### enum `EWinDualShockDefaults`  
`enum EWinDualShockDefaults`  
_L105-113_
- L107 _public enumerator_ `SampleRate = 48000`
- L108 _public enumerator_ `NumFrames = 256`
- L109 _public enumerator_ `PadSpeakerChannels = 2`
- L110 _public enumerator_ `VibrationChannels = 2`
- L111 _public enumerator_ `MicrophoneChannels = 2`
- L112 _public enumerator_ `QueueDepth = 4`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L14 _typedef_ `using FDeviceId = uint32;` (scope `Audio`) — Typed identifier for Audio Device Id
- L41 _function_ `static inline uint32 GetTypeHash(const FDeviceKey& InKey)`

### `Plugins/Runtime/Windows/WinDualShock/Source/WinDualShock/Private/WinDualShockControllers.h` (Private)


#### class `FWinDualShockControllers`  
`class FWinDualShockControllers : public FPlatformControllers`  
_L17-110_
- inherits: `FPlatformControllers`
- L21 _public function_ `FWinDualShockControllers() : FPlatformControllers()`
- L26 _public prototype_ `virtual ~FWinDualShockControllers() = default;`
- L28 _public function_ `void SetAudioGain(float InPadSpeakerGain, float InHeadphonesGain, float InMicrophoneGain, float InOutputGain)`
- L40 _public function_ `float GetOutputGain()`
- L45 _public function_ `bool GetSupportsAudio(int32 UserIndex) const`
- L50 _public function_ `void RefreshControllerType(int32 UserIndex)`
- L59 _public function_ `bool OwnsMostRecentlyUsedDevice(int32 ControllerId) const` — Returns true if the most recently used FInputDeviceId for the given ControllerId is "owned" by this input interface.
- L84 _public function_ `virtual void SetForceFeedbackChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override`
- L95 _public function_ `virtual void SetForceFeedbackChannelValues(int32 ControllerId, const FForceFeedbackValues &Values) override`
- L109 _private member_ `float OutputGain = 1.0f;`

### `Plugins/Runtime/Windows/WinDualShock/Source/WinDualShock/Private/WinDualShockExternalEndpoints.h` (Private)


#### class `FExternalWinDualShockEndpoint`  
`template<EWinDualShockPortType PortType> class FExternalWinDualShockEndpoint : public IAudioEndpoint`  
_L16-86_
- inherits: `IAudioEndpoint`
- desc: these endpoints can be used to send audio to arbitrary virtual audio devices supported by the PS5.
- L19 _private member_ `TSharedRef<IWinDualShockAudioDevice> Device;`
- L20 _private member_ `bool bAllowedEndpoint;`
- L23 _public function_ `FExternalWinDualShockEndpoint(TSharedRef<IWinDualShockAudioDevice> InDevice) : Device(InDevice), bAllowedEndpoint(InDevice->AddEndpoint(PortType))`
- L28 _public function_ `virtual ~FExternalWinDualShockEndpoint()`
- L33 _public function_ `bool IsEndpointAllowed() const`
- L39 _protected function_ `virtual float GetSampleRate() const override`
- L44 _protected function_ `virtual int32 GetNumChannels() const override`
- L61 _protected function_ `virtual bool EndpointRequiresCallback() const override`
- L66 _protected function_ `virtual int32 GetDesiredNumFrames() const override`
- L71 _protected function_ `virtual bool OnAudioCallback(const TArrayView<const float>& InAudio, const int32& NumChannels, const IAudioEndpointSettingsProxy* InSettings) override`
- L82 _protected function_ `virtual bool IsImplemented() override`

### `Plugins/Runtime/Windows/WinDualShock/Source/WinDualShock/Public/WinDualShockSettings.h` (Public)


#### class `UDualShockExternalEndpointSettings`  
`class UDualShockExternalEndpointSettings : public UAudioEndpointSettingsBase`  
_L13-28_
- reflection: `UCLASS()`
- inherits: `UAudioEndpointSettingsBase`
- L20 _public member_ `int32 ControllerIndex;` — `UPROPERTY(Category = Output, EditAnywhere)`
- L22 _public function_ `virtual TUniquePtr<IAudioEndpointSettingsProxy> GetProxy() const override`

#### class `UDualShockSoundfieldEndpointSettings`  
`class UDualShockSoundfieldEndpointSettings : public USoundfieldEndpointSettingsBase`  
_L31-46_
- reflection: `UCLASS()`
- inherits: `USoundfieldEndpointSettingsBase`
- L38 _public member_ `int32 ControllerIndex;` — `UPROPERTY(Category = Output, EditAnywhere)`
- L40 _public function_ `virtual TUniquePtr<ISoundfieldEndpointSettingsProxy> GetProxy() const override`

#### class `UDualShockSpatializationSettings`  
`class UDualShockSpatializationSettings : public USoundfieldEncodingSettingsBase`  
_L49-71_
- reflection: `UCLASS()`
- inherits: `USoundfieldEncodingSettingsBase`
- L54 _public member_ `float Spread = 1.0f;` — `UPROPERTY(Category = Output, EditAnywhere, meta=(ClampMin = "0", ClampMax = "6.2831"))`
- L57 _public member_ `int32 Priority = 0;` — `UPROPERTY(Category = Output, EditAnywhere, meta = (ClampMin = "0", ClampMax = "1000"))`
- L60 _public member_ `bool Passthrough = false;` — `UPROPERTY(Category = Output, EditAnywhere)`
- L62 _public function_ `virtual TUniquePtr<ISoundfieldEncodingSettingsProxy> GetProxy() const override`

### `Plugins/Runtime/Windows/WinDualShock/Source/WinDualShock/Public/WinDualShockSettingsProxies.h` (Public)


#### class `FDualShockExternalEndpointSettings`  
`class FDualShockExternalEndpointSettings : public IAudioEndpointSettingsProxy`  
_L10-14_
- inherits: `IAudioEndpointSettingsProxy`
- L13 _public member_ `int32 ControllerIndex = INDEX_NONE;`

#### class `FDualShockSoundfieldEndpointSettings`  
`class FDualShockSoundfieldEndpointSettings : public ISoundfieldEndpointSettingsProxy`  
_L16-20_
- inherits: `ISoundfieldEndpointSettingsProxy`
- L19 _public member_ `int32 ControllerIndex = INDEX_NONE;`

#### class `FDualShockSpatializationSettings`  
`class FDualShockSpatializationSettings : public ISoundfieldEncodingSettingsProxy`  
_L22-40_
- inherits: `ISoundfieldEncodingSettingsProxy`
- L26 _public member_ `float Spread;`
- L27 _public member_ `int32 Priority;`
- L28 _public member_ `bool Passthrough;`
- L30 _public function_ `virtual uint32 GetUniqueId() const override`
- L36 _public function_ `virtual TUniquePtr<ISoundfieldEncodingSettingsProxy> Duplicate() const override`
