# Plugins / GameInputBase

- module root: `Plugins/Runtime/GameInput/Source/GameInputBase`
- headers: 22; symbols: 501
- symbol kinds: class=21, enum=9, enumerator=33, function=17, macro=10, member=195, namespace=4, prototype=195, struct=11, variable=6
- PrivateDependencyModuleNames: AudioMixer, AudioMixerCore, WindowsMMDeviceEnumeration
- PublicDependencyModuleNames: ApplicationCore, AudioExtensions, Core, CoreUObject, DeveloperSettings, Engine, InputCore, InputDevice, Slate, SlateCore

### `Plugins/Runtime/GameInput/Source/GameInputBase/Private/GameInputHapticAudioDevice.h` (Private)


#### enum `UE::GameInput::EHapticAudioDefaults`  
`enum EHapticAudioDefaults : int32`  
_L33-38_
- L35 _public enumerator_ `HapticSampleRate = 48000`
- L36 _public enumerator_ `HapticNumFrames = 256`
- L37 _public enumerator_ `HapticQueueDepth = 4`

#### class `FHapticRenderRunnable`  
`class FHapticRenderRunnable final : public FRunnable`  
_L47-62_
- inherits: `FRunnable`
- L50 _public function_ `explicit FHapticRenderRunnable(FGameInputHapticAudioDevice* InOwner, HANDLE InSampleReadyEvent) : Owner(InOwner) , SampleReadyEvent(InSampleReadyEvent)`
- L55 _public prototype_ `virtual uint32 Run() override;`
- L56 _public prototype_ `virtual void Stop() override;`
- L59 _private member_ `FGameInputHapticAudioDevice* Owner = nullptr;`
- L60 _private member_ `HANDLE SampleReadyEvent = nullptr;`
- L61 _private member_ `std::atomic_bool bIsRunning { false };`

#### class `FGameInputHapticAudioDevice`  
`class FGameInputHapticAudioDevice`  
_L71-158_
- L75 _public prototype_ `FGameInputHapticAudioDevice();`
- L76 _public prototype_ `~FGameInputHapticAudioDevice();`
- L89 _public prototype_ `bool Initialize(const FString& AudioEndpointId, TArrayView<const GUID> InHapticLocations);` — Set up WASAPI targeting the given endpoint using the supplied haptic locations to build a WAVEFORMATEXTENSIBLE channel mask. Safe to call multiple times; re-initializes on repeated calls. @param AudioEndpointId     The WASAPI device ID from GameInputHapticInfo::audioEndpointId. @param InHapticLocations   GameInputHapticLocation GUIDs from GameInputHapticInfo::locations, sized to locationCount. The count also becomes the render-side channel count. @return true if WASAPI was successfully initialized.
- L92 _public prototype_ `void Teardown();` — Shut down WASAPI and release all resources. Safe to call when not initialized.
- L94 _public function_ `bool IsInitialized() const`
- L95 _public function_ `int32 GetNumChannels() const`
- L96 _public function_ `uint32 GetSampleRate() const`
- L102 _public prototype_ `void PushAudio(const TArrayView<const float>& InAudio, int32 InNumChannels);` — Enqueue audio samples. Called from the UE audio thread via FGameInputHapticEndpoint::OnAudioCallback. Handles mono→N-channel upmix and applies platform headroom gain compensation.
- L112 _private prototype_ `bool InitializeInternal();` — Runs the CoCreateInstance → Activate → Initialize → Start sequence using the cached EndpointId + HapticLocations. Called both by Initialize() on the game thread (first boot) and by RecoverFromInvalidation() on the render thread (after AUDCLNT_E_*_INVALIDATED).
- L115 _private prototype_ `void ShutdownInternal();` — Release COM pointers and MixFormat. Does not touch events, threads, or the queue.
- L118 _private prototype_ `HRESULT ServiceRenderCallback();` — Render-thread callback invoked when SampleReadyEvent fires.
- L121 _private prototype_ `void FillRenderBuffer(BYTE* Dst, uint32 FramesToWrite);` — Drain AudioQueue into the WASAPI render buffer; zero-fill on underrun.
- L125 _private prototype_ `void RecoverFromInvalidation();` — Tear down and re-run InitializeInternal(). Called on the render thread when ServiceRenderCallback returns AUDCLNT_E_*_INVALIDATED.
- L128 _private member_ `TComPtr<IMMDevice> MMDevice;` — --- WASAPI COM state ----------------------------------------------------
- L129 _private member_ `TComPtr<IAudioClient2> AudioClient;`
- L130 _private member_ `TComPtr<IAudioRenderClient> RenderClient;`
- L131 _private member_ `WAVEFORMATEX* MixFormat = nullptr;` — CoTaskMemFree on teardown
- L132 _private member_ `uint32 BufferFrames = 0;`
- L133 _private member_ `uint32 FramesPerPeriod = 0;`
- L136 _private member_ `HANDLE SampleReadyEvent = nullptr;` — --- Render worker thread ------------------------------------------------
- L137 _private member_ `TUniquePtr<FRunnableThread> RenderThread;`
- L138 _private member_ `TUniquePtr<FHapticRenderRunnable> RenderRunnable;`
- L141 _private member_ `FString EndpointId;` — --- Cached endpoint config for restart-on-invalidation ------------------
- L142 _private member_ `TArray<GUID> HapticLocations;`
- L149 _private member_ `FCriticalSection StateLock;` — --- Shared state -------------------------------------------------------- Protects AudioQueue access between the UE audio thread (PushAudio) and the game thread (Teardown). The render thread reads AudioQueue only after InitializeInternal succeeds; Teardown joins the render thread before the queue can be destroyed, so the render side does not need StateLock.
- L151 _private member_ `TUniquePtr<TCircularQueue<float>> AudioQueue;`
- L153 _private member_ `int32 NumChannels = 2;`
- L154 _private member_ `uint32 SampleRate = 48000;`
- L155 _private member_ `uint32 BlockAlign = sizeof(float) * 2;`
- L156 _private member_ `float OutputGain = 1.f;`
- L157 _private member_ `std::atomic_bool bIsSetup { false };`

#### class `FGameInputHapticEndpoint`  
`class FGameInputHapticEndpoint : public IAudioEndpoint`  
_L167-222_
- inherits: `IAudioEndpoint`
- L171 _public function_ `explicit FGameInputHapticEndpoint(TSharedRef<FGameInputHapticAudioDevice> InDevice) : Device(MoveTemp(InDevice))`
- L175 _public function_ `virtual float GetSampleRate() const override`
- L184 _public function_ `virtual int32 GetNumChannels() const override`
- L194 _public function_ `virtual bool IsImplemented() override`
- L199 _public function_ `virtual bool EndpointRequiresCallback() const override`
- L204 _public function_ `virtual int32 GetDesiredNumFrames() const override`
- L209 _public function_ `virtual bool OnAudioCallback( const TArrayView<const float>& InAudio, const int32& NumChannels, const IAudioEndpointSettingsProxy* InSettings) override`
- L221 _private member_ `TSharedRef<FGameInputHapticAudioDevice> Device;`

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace GameInput` (scope `UE`)

### `Plugins/Runtime/GameInput/Source/GameInputBase/Private/GameInputHapticEndpointFactory.h` (Private)


#### struct `FHapticDeviceKey`  
`struct FHapticDeviceKey`  
_L25-38_
- L28 _public member_ `Audio::FDeviceId AudioDeviceId = 0;` — UE audio device that owns the endpoint submix (from FAudioPluginInitializationParams).
- L31 _public member_ `APP_LOCAL_DEVICE_ID AppLocalDeviceId = {};` — GameInput physical device. Zero-initialized while awaiting HandleHapticsReady.
- L33 _public function_ `bool operator==(const FHapticDeviceKey& Other) const`

#### class `FGameInputHapticEndpointFactory`  
`class FGameInputHapticEndpointFactory : public IAudioEndpointFactory`  
_L61-120_
- inherits: `IAudioEndpointFactory`
- desc: IAudioEndpointFactory implementation for GameInput haptic audio. Registers as the "Vibration Output" endpoint type so that existing UEndpointSubmix content (created for WinDualShock) routes here on GameInput platforms without requiring asset changes. DeviceMap is keyed by FHapticDeviceKey { AudioDeviceId, InputDeviceId }. CreateNewEndpointInstance (audio thread) stores a placeholder entry with InputDeviceId == INPUTDEVICEID_NONE. InitializeDevice (game thread, fired from HandleHapticsReady_Impl) re-keys all placeholder entries and calls Initialize() on each FGameInputHapticAudioDevice so every live UE audio device's endpoint starts receiving haptic audio. Owned by FGameInputBaseModule. Registered at construction, unregistered at destruction.
- L65 _public prototype_ `FGameInputHapticEndpointFactory();`
- L69 _public prototype_ `virtual FName GetEndpointTypeName() override;`
- L70 _public prototype_ `virtual TUniquePtr<IAudioEndpoint> CreateNewEndpointInstance( const FAudioPluginInitializationParams& InitInfo, const IAudioEndpointSettingsProxy& InitialSettings) override;`
- L73 _public prototype_ `virtual UClass* GetCustomSettingsClass() const override;`
- L74 _public prototype_ `virtual const UAudioEndpointSettingsBase* GetDefaultSettings() const override;`
- L81 _public prototype_ `TSharedRef<FGameInputHapticAudioDevice> GetOrCreatePlaceholder(Audio::FDeviceId AudioDeviceId);` — Finds or creates a placeholder FGameInputHapticAudioDevice for the given UE audio device. Called from CreateNewEndpointInstance on the audio thread.
- L84 _public prototype_ `bool IsDeviceInitialized(const APP_LOCAL_DEVICE_ID& InDeviceId) const;` — Returns true if the given device already has initialized haptic audio endpoints.
- L94 _public prototype_ `void InitializeDevice(const APP_LOCAL_DEVICE_ID& InDeviceId, const FString& AudioEndpointId, TArrayView<const GUID> HapticLocations);` — Called from the game thread (HandleHapticsReady_Impl) when a haptic controller connects. Re-keys all placeholder entries to the real APP_LOCAL_DEVICE_ID and calls Initialize() on each FGameInputHapticAudioDevice. @param HapticLocations  The GameInputHapticLocation GUID array from GameInputHapticInfo, sized to locationCount. Used to build the WASAPI channel mask.
- L100 _public prototype_ `void RemoveDevice(const APP_LOCAL_DEVICE_ID& InDeviceId);` — Called from the game thread on disconnect. Tears down and removes all entries for the given device (across all UE audio devices).
- L105 _private member_ `mutable FCriticalSection DeviceMapCS;` — Guards DeviceMap and active device state — written from game thread and audio thread.
- L107 _private member_ `TMap<FHapticDeviceKey, TSharedRef<FGameInputHapticAudioDevice>> DeviceMap;`
- L117 _private member_ `APP_LOCAL_DEVICE_ID ActiveDeviceId = {};` — Cached endpoint info from the last successful InitializeDevice call. Used to immediately initialize late-arriving audio devices (e.g. PIE starts after the controller is already connected). NOTE: Only one active device is tracked at a time. If multiple haptic controllers connect simultaneously, the last InitializeDevice call wins and RemoveDevice clears the cache unconditionally. Expand these to a TMap<APP_LOCAL_DEVICE_ID, ...> if multi-device haptic audio is needed.
- L118 _private member_ `FString ActiveAudioEndpointId;`
- L119 _private member_ `TArray<GUID> ActiveHapticLocations;`

#### Free symbols / members of external scopes

- L40 _function_ `inline uint32 GetTypeHash(const FHapticDeviceKey& Key)`

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/GameInputBaseIncludes.h` (Public)


#### Free symbols / members of external scopes

- L19 _macro_ `#define GAMEINPUT_API_VERSION 0`
- L45 _macro_ `#define UE_GAMEINPUT_SUPPORTS_RAW 1`
- L46 _macro_ `#define UE_GAMEINPUT_SUPPORTS_TOUCH 1`
- L47 _macro_ `#define UE_GAMEINPUT_SUPPORTS_DEVICE_STATUS 1`
- L48 _macro_ `#define UE_GAMEINPUT_SUPPORTS_TRIGGER_HAPTICS 0`
- L49 _macro_ `#define UE_GAMEINPUT_SUPPORTS_SENSORS 0`

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/GameInputBaseModule.h` (Public)


#### class `FGameInputBaseModule`  
`class FGameInputBaseModule : public IModuleInterface`  
_L16-64_
- inherits: `IModuleInterface`
- L20 _public prototype_ `static FGameInputBaseModule& Get();`
- L23 _public prototype_ `static bool IsAvailable();` — Returns true if this module is loaded (aka available) by the FModuleManager
- L26 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L34 _public prototype_ `static IGameInput* GetGameInput();` — Pointer to the static IGameInput that is created upon module startup.
- L39 _public member_ `TMulticastDelegate<void(IGameInput*)> OnGameInputCreation;` — Delegate which is called after the creation of the IGameInput object from the game input library.
- L47 _public function_ `FGameInputHapticEndpointFactory* GetHapticFactory() const` — Returns the haptic endpoint factory, or null if haptic support is disabled. Created during StartupModule so it is registered before the audio device initializes.
- L52 _protected prototype_ `void InitializeGameInputKeys();`
- L55 _protected member_ `static FCriticalSection GameInputCreationLock;`
- L59 _protected prototype_ `void InitializeHapticAudioFactory();`
- L60 _protected prototype_ `void ShutdownHapticAudioFactory();`
- L62 _protected member_ `TUniquePtr<FGameInputHapticEndpointFactory> HapticAudioFactory;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEINPUTBASE_API`

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/GameInputDeveloperSettings.h` (Public)


#### struct `FGameInputDeviceIdentifier`  
`struct FGameInputDeviceIdentifier`  
_L27-53_
- reflection: `USTRUCT()`
- desc: Represents a single unique device that Microsoft's Game Input API detects. Each device has a Vendor ID and  Product ID. It is possible (and common) for Game Input devices to have the same VendorId's. This is used so that we can easily make a map of each unique device to some metadata about it's controller bindings. If you are unsure about what the vendor or product ID's are, then you can look at the logs and they will be there in the LogGameInput if you search for "VendorId" or "ProductId". You can also place a breakpoint on the device connection status changed to see the value there from the GameInputDeviceInfo.
- L31 _public prototype_ `FGameInputDeviceIdentifier();`
- L32 _public prototype_ `FGameInputDeviceIdentifier(uint16 InVendorId, uint16 InProductId);`
- L36 _public member_ `uint16 VendorId;` — `UPROPERTY(EditAnywhere, Config, Category = "Input Device")` — The Vendor ID of this device
- L40 _public member_ `uint16 ProductId;` — `UPROPERTY(EditAnywhere, Config, Category = "Input Device")` — The unique Product ID of this device
- L43 _public prototype_ `bool operator==(const FGameInputDeviceIdentifier& Other) const;`
- L44 _public prototype_ `bool operator!=(const FGameInputDeviceIdentifier& Other) const;`
- L52 _public prototype_ `FString ToString() const;` — Returns a string representing this Game Input device identifier. For example: "VendorId: XXX ProductId XXX"

#### enum `EGameInputDeviceFamily`  
`enum class EGameInputDeviceFamily : uint32`  
_L59-70_
- reflection: `UENUM(meta = (BitFlags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: UPROP friendly representation of GameInput's GameInputDeviceFamily type.
- L61 _public enumerator_ `None = 0 UMETA(Hidden)`
- L62 _public enumerator_ `Virtual = 1 << 0`
- L63 _public enumerator_ `Unknown = 1 << 1`
- L64 _public enumerator_ `XboxOne = 1 << 2`
- L65 _public enumerator_ `Xbox360 = 1 << 3`
- L66 _public enumerator_ `Hid = 1 << 4`
- L67 _public enumerator_ `I8042 = 1 << 5`
- L68 _public enumerator_ `Aggregate = 1 << 6`
- L69 _public enumerator_ `All = Virtual | Unknown | XboxOne | Xbox360 | Hid | I8042 | Aggregate UMETA(Hidden)`

#### struct `FGameInputControllerAxisData`  
`struct FGameInputControllerAxisData`  
_L82-106_
- reflection: `USTRUCT()`
- desc: Configuration of an individual axis from a Game Input Controller device type. These settings would be used for one individual reading from a "GetControllerAxisState" call. @see FGameInputControllerDeviceProcessor::ProcessControllerAxisState
- L86 _public prototype_ `FGameInputControllerAxisData() = default;`
- L89 _public member_ `FName KeyName = NAME_None;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device")`
- L92 _public member_ `float DeadZone = (7849.0f / 32768.0f);` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device")`
- L96 _public member_ `float Scalar = 1.0f;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device")` — Scalar that the input value will be multiplied by before being reported to the input system.
- L105 _public member_ `bool bIsPackedPositveAndNegative = false;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device")` — Set this to true if this axis represents a positive and negative value packed into one float. For example, a trigger will be a single value between 0.0 and 1.0, where 0.0 is unactuated and 1.0 is full actuated. However, something like a thumb stick may pack both positive and negative values into its range, from -1.0 to +1.0 where -1.0 is all the way to the left, and +1.0 is all the way to the right.

#### enum `ERawDeviceReportTranslationBehavior`  
`enum class ERawDeviceReportTranslationBehavior : uint8`  
_L112-135_
- reflection: `UENUM()`
- desc: Options for how to translate the raw uint8 RawInput report data to the engine.
- L115 _public enumerator_ `TreatAsTrigger = 0` — Treat the value as a trigger, mapping it from 0.0 to +1.0
- L118 _public enumerator_ `TreatAsAnalog = 1` — Treat the value as an analog value, mapping it from -1.0 to +1.0
- L121 _public enumerator_ `TreatAsButton = 2` — Treats the raw value as a button. If the value is 0, consider it not pressed. If the value is non-zero, consider it pressed.
- L126 _public enumerator_ `TreatAsButtonBitmask = 3` — Treat the raw value as a bitmask of different buttons. Treats each bit in the raw uint8 value as its own button. If the bit is 0, then consider it not pressed. If the bit is non-zero (1) then consider it pressed.
- L130 _public enumerator_ `TreatAsPackedAxisPair = 4` — Treat this as two raw values, where one axis is the "lower" bits of an int16 and one is the "higher" bits of the int16.
- L134 _public enumerator_ `TreatAsPackedAxisUint8 = 5` — Treat this raw report index as two values, reporting two different sets of buttons. The lower 4 bits represent one set of buttons, and the upper 4 bits represent another set of buttons.

#### struct `FGameInputRawDeviceReportData`  
`struct FGameInputRawDeviceReportData`  
_L146-225_
- reflection: `USTRUCT()`
- desc: A configuration of a single Raw Device Report index. This information will be used to map the raw device report information of a given index to something that the Unreal Engine can process with its message handler. @see FGameInputRawDeviceProcessor::ProcessInput
- L150 _public prototype_ `FGameInputRawDeviceReportData() = default;`
- L158 _public member_ `FName KeyName = NAME_None;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device", meta=(EditCondition="TranslationBehavior != ERawDeviceReportTranslationBehavior::TreatAsButtonBitmask && TranslationBehavior != ERawDeviceReportTranslationBehavior::TreatAsPackedAxisUint8", EditConditionHides))` — The name of the FKey that this raw device report is associated with when treated as an analog or trigger value Note: This value only matters for Translation Behaviors other then the button bitmask.
- L170 _public member_ `bool bIgnoreAnalogInputDeviceScopeForThisRawReport = false;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device", meta=(EditCondition="TranslationBehavior == ERawDeviceReportTranslationBehavior::TreatAsAnalog || TranslationBehavior == ERawDeviceReportTranslationBehavior::TreatAsTrigger", EditConditionHides))` — If true, then this raw report data will NOT set the FInputDeviceScope. This may be desirable if you have a very sensitive axis value or something which may be constantly reporting that you don't necessarily want to be used to determine things like Common UI icons or other systems who read device scope. Default: False.
- L176 _public member_ `ERawDeviceReportTranslationBehavior TranslationBehavior = ERawDeviceReportTranslationBehavior::TreatAsTrigger;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device")` — Options for how we should interpret the raw uint8 value from RawInput when telling the engine about it
- L184 _public member_ `uint8 AnalogDeadzone = 5;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device", meta=(EditCondition="TranslationBehavior == ERawDeviceReportTranslationBehavior::TreatAsAnalog", EditConditionHides))` — The deadzone to use when translating the value to an analog input between -1.0 and +1.0. Normally a value between 0-10 is about where you want it for most devices.
- L190 _public member_ `float Scalar = 1.0f;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device", meta=(EditCondition="TranslationBehavior == ERawDeviceReportTranslationBehavior::TreatAsAnalog || TranslationBehavior == ERawDeviceReportTranslationBehavior::TreatAsTrigger", EditConditionHides))` — A scalar that gets applied to the raw float value for Analog or trigger values. Most of the time this would be used to simply negate values
- L198 _public member_ `TMap<int32, FName> ButtonBitMaskMappings;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device", meta=(EditCondition="TranslationBehavior == ERawDeviceReportTranslationBehavior::TreatAsButtonBitmask", EditConditionHides))` — When treating this raw input as a button we will map the key value of this map to a bit on the raw input value. I.e. a key value of "1" will look at the first bit to see if it is set. If it is, then send a controller button event for the associated FName
- L201 _public member_ `uint8 LowerBitAxisIndex = 0;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device", meta = (EditCondition = "TranslationBehavior == ERawDeviceReportTranslationBehavior::TreatAsPackedAxisPair", EditConditionHides))`
- L204 _public member_ `uint8 HigherBitAxisIndex = 0;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device", meta = (EditCondition = "TranslationBehavior == ERawDeviceReportTranslationBehavior::TreatAsPackedAxisPair", EditConditionHides))`
- L210 _public member_ `TArray<FName> LowerBitKeys;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device", meta = (EditCondition = "TranslationBehavior == ERawDeviceReportTranslationBehavior::TreatAsPackedAxisUint8", EditConditionHides))` — Array of FKey names to report when the lower bits of this raw value index are detected. Each element of this array will be reported once per-frame, known as an "input chord"
- L216 _public member_ `TArray<FName> UpperBitKeys;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device", meta = (EditCondition = "TranslationBehavior == ERawDeviceReportTranslationBehavior::TreatAsPackedAxisUint8", EditConditionHides))` — Array of FKey names to report when the upper bits of this raw value index are detected. Each element of this array will be reported once per-frame, known as an "input chord"
- L223 _public member_ `bool bTreatValuesAsAnalog = false;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input Device", meta = (EditCondition = "TranslationBehavior == ERawDeviceReportTranslationBehavior::TreatAsPackedAxisUint8", EditConditionHides))` — If true, then this packed bitmask value will be treated as an analog button. This means that it will use "OnControllerAnalog", reporting a float value, instead of "OnControllerButtonPressed" using input events.

#### struct `FGameInputDeviceConfiguration`  
`struct FGameInputDeviceConfiguration`  
_L233-322_
- reflection: `USTRUCT()`
- desc: Configurable data about a unique type of Game Input device. These settings will be used at runtime to determine the behavior of any device whose Vendor and Product ID match this one.
- L237 _public prototype_ `FGameInputDeviceConfiguration();`
- L241 _public member_ `FGameInputDeviceIdentifier DeviceIdentifier;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings")` — The unique device vendor and product ID that can be used to ID this item at runtime.
- L249 _public member_ `FString Description = TEXT("");` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings", meta=(DisplayName="Description (Editor Only)"))` — An editor-only description of this input device. Only used for if you want to describe your device and make the project settings easier to read
- L262 _public member_ `bool bOverrideHardwareDeviceIdString;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings", meta = (InlineEditConditionToggle, ConfigRestartRequired=true))` — If true, then the hardware device Id specific on this configuration will be used instead of whatever the Game Input SDK tells us this device is. Use this if want to get additional messaging from the Input Device Subsystem when this specific device is used. For example, some third party controller might be an "Xbox One" controller type, but it is really some specially manufactured hardware for your game that you would like to have access to at the Gameplay layer in UE.
- L269 _public member_ `FString OverriddenHardwareDeviceId;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings", meta=(EditCondition="bOverrideHardwareDeviceIdString", ConfigRestartRequired=true))` — The name of this device that should be used for FInputDeviceScope's to determine when it has been connected or input events came from it.
- L273 _public member_ `bool bProcessControllerButtons;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings|Controller", meta = (InlineEditConditionToggle))` — If true, this device will attempt to process Game Input Button states.
- L281 _public member_ `bool bProcessControllerSwitchState;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings|Controller")` — If true, this device will attempt to process Game Input Switch (aka DPad) state. If the device has it's DPad being processed as buttons already, you may want to turn this off.
- L287 _public member_ `bool bProcessControllerAxis;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings|Controller", meta = (InlineEditConditionToggle))` — If true, this device will attempt to process Game Input Controller Axis mappings.
- L295 _public member_ `TMap<uint32, FName> ControllerButtonMappingData;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings|Controller", meta=(EditCondition="bProcessControllerButtons"))` — A map of uint32 button index to an associated FName Unreal gamepad key name. These key values should be (1 << [button index]) i.e, powers of two.
- L301 _public member_ `TMap<uint32, FGameInputControllerAxisData> ControllerAxisMappingData;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings|Controller", meta=(EditCondition="bProcessControllerAxis"))` — A map of uint32 button index to some data about how we should treat the raw axis value
- L307 _public member_ `bool bProcessRawReportData;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings|Raw Report")` — If true, this device will attempt to process Game Input Raw Report mappings.
- L315 _public member_ `uint32 RawReportReadingId;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings|Raw Report", meta=(EditCondition="bProcessRawReportData"))` — The raw report reading ID ( GameInputRawDeviceReportInfo::id ). We need to know this value so that we can confirm that the reading we are receiving is for this device configuration.
- L321 _public member_ `TMap<int32, FGameInputRawDeviceReportData> RawReportMappingData;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings|Raw Report", meta=(EditCondition="bProcessRawReportData"))` — A map of uint32 raw report index to some data about how we should treat that raw data.

#### class `UGameInputPlatformSettings`  
`class UGameInputPlatformSettings : public UPlatformSettings`  
_L328-473_
- reflection: `UCLASS(MinimalAPI, config = Input, DefaultConfig)`
- inherits: `UPlatformSettings`
- desc: Settings for Game Input that you may want to set per-platform.
- L336 _protected prototype_ `virtual void InitializePlatformDefaults() override;`
- L341 _public prototype_ `static UGameInputPlatformSettings* Get();` — Returns a pointer to Game Input settings on the current platform.
- L349 _public member_ `bool bProcessController = false;` — `UPROPERTY(Config, EditAnywhere, Category="Processing Options|Require Configuration")` — If true Game Input will process controller axis, button, and switch events Default: False
- L357 _public member_ `bool bProcessRawInput = false;` — `UPROPERTY(Config, EditAnywhere, Category="Processing Options|Require Configuration")` — If true, then we will process the GameInputKindRawDeviceReport type. Default: False
- L366 _public member_ `bool bSpecialDevicesRequireExplicitDeviceConfiguration = true;` — `UPROPERTY(Config, EditAnywhere, Category="Processing Options|Require Configuration", meta=(EditCondition="bProcessController || bProcessRawInput"))` — If true, then we will only process controller devices whose vendor/product ID is in the DeviceConfigurations array. This applies to both Controller and Raw input kinds. Default: True
- L377 _public member_ `bool bProcessGamepad = true;` — `UPROPERTY(Config, EditAnywhere, Category="Processing Options")` — If true, then we will process the GameInputKindGamepad type. Note: If you are using Game Input on Windows where there are other Input Device module plugins (XInput, WinDualShock, etc) you should disable those to use this. Otherwise, there will be "duplicate" gamepad input events. Default: True
- L388 _public member_ `bool bProcessKeyboard = true;` — `UPROPERTY(Config, EditAnywhere, Category="Processing Options")` — If true, then we will process the GameInputKindKeyboard type. Note: You likely do not want this on for Windows targets, as those input events are already processed via the WindowsApplication. This should really only be used for console targets. This is currently disabled on Windows. Default: True
- L399 _public member_ `bool bProcessMouse = true;` — `UPROPERTY(Config, EditAnywhere, Category="Processing Options")` — If true, then we will process the GameInputKindMouse type. Note: You likely do not want this on for Windows targets, as those input events are already processed via the WindowsApplication. This should really only be used for console targets. This is currently disabled on Windows. Default: True
- L422 _public member_ `bool bProcessRacingWheel = false;` — `UPROPERTY(EditAnywhere, Config, Category = "Processing Options|Require Configuration", meta=(DisplayName="Process Racing Wheel (Experimental)"))` — If true, then we will process the GameInputKindRacingWheel type. Racing Wheels often times need to be used in conjunction with the "Controller" or "Gamepad" processors as well in order to handle any "normal" buttons on them. For example, you may have a racing wheel with some ABXY buttons on it that you want to process as well. Note: This is experimental! Default: False
- L425 _public member_ `static constexpr float DefaultRacingWheelDeadzone = (7849.0f / 32768.0f);` — The default racing wheel deadzone
- L433 _public member_ `float RacingWheelDeadzone = DefaultRacingWheelDeadzone;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings|Racing Wheel", meta=(EditCondition="bProcessRacingWheel"))` — The deadzone that should be applied when processing Racing Wheel analog values. @see FGameInputRacingWheelProcessor::ProcessWheelAnalogState
- L443 _public member_ `bool bProcessArcadeStick = false;` — `UPROPERTY(EditAnywhere, Config, Category = "Processing Options", meta=(DisplayName="Process Arcade Sticks (Experimental)"))` — If true, then we will process the GameInputKindArcadeStick type. Note: This is experimental! Default: False
- L453 _public member_ `bool bProcessFlightStick = false;` — `UPROPERTY(EditAnywhere, Config, Category = "Processing Options", meta=(DisplayName="Process Flight Sticks (Experimental)"))` — If true, then we will process the GameInputKindFlightStick type. Note: This is experimental! Default: False
- L456 _public member_ `static constexpr float DefaultFlightStickDeadzone = (7849.0f / 32768.0f);` — The default value of any flight stick deadzone values.
- L460 _public member_ `float FlightStickPitchDeadzone = DefaultFlightStickDeadzone;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings|Flight Stick", meta=(EditCondition="bProcessFlightStick"))` — Deadzone which should be used for Flight Stick Pitch inputs
- L464 _public member_ `float FlightStickRollDeadzone = DefaultFlightStickDeadzone;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings|Flight Stick", meta=(EditCondition="bProcessFlightStick"))` — Deadzone which should be used for Flight Stick Roll inputs
- L468 _public member_ `float FlightStickThrottleDeadzone = DefaultFlightStickDeadzone;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings|Flight Stick", meta=(EditCondition="bProcessFlightStick"))` — Deadzone which should be used for Flight Stick Throttle inputs
- L472 _public member_ `float FlightStickYawDeadzone = DefaultFlightStickDeadzone;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings|Flight Stick", meta=(EditCondition="bProcessFlightStick"))` — Deadzone which should be used for Flight Stick Yaw inputs

#### class `UGameInputDeveloperSettings`  
`class UGameInputDeveloperSettings : public UObject`  
_L482-609_
- reflection: `UCLASS(MinimalAPI, config = Input, DefaultConfig, meta = (DisplayName = "Game Input Plugin Settings"))`
- inherits: `UObject`
- desc: Settings related to the Game Input device interface. These will allow you to enable and disable specific types of input devices within Game Input as well as configure key mappings for generic controller types based on their unique vendor/product ID's.
- L494 _public prototype_ `[[nodiscard]] const FGameInputDeviceConfiguration* FindDeviceConfiguration(const GameInputDeviceInfo* const Info) const;` — Finds unique device configuration data for the given Game Input Device. This is based on the vendor/product ID of the game input device @return Device Configuration for the given Game Input device. Null if it is not configured.
- L499 _public prototype_ `const FGameInputDeviceConfiguration* FindDeviceConfiguration(const FGameInputDeviceIdentifier& HardwareID) const;` — Returns a pointer to the device configuration that may exist for the given hardware ID
- L505 _public prototype_ `bool ShouldIgnoreDevice(const GameInputDeviceInfo* const Info) const;` — Returns true if the gien device should be completely ignored by GameInput processing. If a device is ignored, then it will not even fire connection event delegates.
- L509 _public prototype_ `UGameInputDeveloperSettings(const FObjectInitializer& Initializer);`
- L524 _protected member_ `TArray<FGameInputDeviceConfiguration> DeviceConfigurations;` — `UPROPERTY(EditAnywhere, Config, Category = "Game Input")` — Array of devices that you want to specify the behavior for. These could be some special input devices for your game like racing wheels, instruments, or other "special" peripherals that require some kind of special readings from Game Input. This is typically for GameInputKindController or GameInputKindRawDeviceReport. If bSpecialDevicesRequireExplicitDeviceConfiguration is true, only Controller/Raw device kinds that are within this array will be allowed to be processed.
- L533 _protected member_ `FPerPlatformSettings PlatformSpecificSettings;` — `UPROPERTY(EditAnywhere, Category = "Game Input|Platform Options")` — Settings for Game input that you may want to set per-platform. This is useful to have per-platform because some platforms might already handle the processing of some input devices, so you might want to disable them here.
- L540 _protected member_ `TArray<FGameInputDeviceIdentifier> DevicesToIgnore;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings")` — A list of devices for game input to completely ignore. If a device is connected that is in this list, no processors will ever be created for it at all.
- L549 _protected member_ `uint32 SupportedDeviceFamilies;` — `UPROPERTY(EditAnywhere, Config, Category = "Device Settings", meta = (Bitmask, BitmaskEnum = "/Script/GameInputBase.EGameInputDeviceFamily"))` — A bitmask of which GameInput device families you want to support. If a family is not enabled as a part of this list, it will be ignored. Default: All families are supported.
- L569 _public member_ `bool bDoNotProcessDuplicateCapabilitiesForSingleUser;` — `UPROPERTY(Config, EditAnywhere, Category="Game Input")` — If true, when you have multiple input devices mapped to a single FPlatformUserId, we will only process events from one of them each frame. This makes it impossible for analog input values to "over accumulate" and report values higher than +- 1.0 One example of this issue would be if a user has mapped two game pads to the same platform user and them presses the right analog stick all the way to the right on both of them at the same time. When this setting is on, we will only read the value from one of the sticks, resulting in an input value of +1.0. With this setting off (which is not recommended) then you would receive an input value of +2.0. This could result in having faster rotations around in your game or other non-desirable behaviors. WARNING: Turning this off may result in Slate receiving input events greater than 1.0, which can cause undefined behavior in your if it makes the assumption of input being between -1.0 and +1.0. Default: True
- L575 _public prototype_ `bool IsHapticSupportEnabled() const;` — @return True if this build target supports haptics (UE_GAME_INPUT_SUPPORTS_HAPTICS) and the project setting for enabling haptic support is true.
- L587 _protected member_ `bool bEnableHapticSensorSupport;` — `UPROPERTY(Config, EditAnywhere, Category="Experimental|Game Input")` — If true, then Game Input will listen for the GameInputDeviceHapticInfoReady device status on platforms which UE_GAME_INPUT_SUPPORTS_HAPTICS is true. Haptic sensor support is like a "fancy" force feedback. On supported devices, an audio endpoint is created. You can use audio files to drive sound and vibration on the devices.
- L593 _public member_ `TMulticastDelegate<void()> OnInputSettingChanged;` — A delegate that is called on PostEditChangeProperty with the name of the property that has changed.
- L604 _public prototype_ `static const TArray<uint32>& GetControllerButtonMappingDataKeyOptions();` — `UFUNCTION()` — Returns all known uint32 options for controller button configurations. this is useful for making it easier to select in the editor instead of having to manually type everything in on a UPROPERTY i.e. meta=(GetOptions="GameInput.GameInputDeveloperSettings.GetControllerButtonMappingDataKeyOptions")
- L607 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEINPUTBASE_API`

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/GameInputDeviceContainer.h` (Public)


#### class `FGameInputDeviceContainer`  
`class FGameInputDeviceContainer`  
_L21-138_
- desc: Game Input Device Containers hold any state about a single unique GameInput device. Upon creation, the will create any "Device Processors" that are required based on the IGameInputDevice's supported GameInputKind. They are ticked each frame by the owning IGameInputDeviceInterface who created them. This class is what will actually poll the GameInput SDK for new readings and keep track of it's state across frames.
- L24 _public prototype_ `FGameInputDeviceContainer( const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler, IGameInputDevice* InDevice, GameInputKind InAllowedGameInputKinds, FPlatformUserId InUserId = PLATFORMUSERID_NONE, FInputDeviceId InDeviceId = INPUTDEVICEID_NONE);`
- L31 _public prototype_ `virtual ~FGameInputDeviceContainer() = default;`
- L34 _public prototype_ `void InitalizeDeviceProcessors();` — Create any device processors necessary for this Game Input device to process input and send input events
- L40 _public prototype_ `void RecreateDeviceProcessors(const GameInputKind InAllowedGameInputKinds);` — Clears the state of any device processors and destroyies them. Empties the processors array. Sets the allowed input kind to the new given input kinds
- L43 _public prototype_ `void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);` — Set the message handler that this Device Container should send events through.
- L59 _public prototype_ `const GameInputKind ProcessInput(IGameInput* GameInput, const GameInputKind CurrentSupportedKind, const GameInputKind ProcessedKindsForPlatformUserThisFrame);` — Process any input events from the given reading and send events to a message handler @param 	GameInput								Pointer to the game input instance @param 	CurrentSupportedKind					Currently supported game input reading kinds that we are allowed to process. This will be used to get the current readings from GameInput with GameInput->GetNextReading @param 	ProcessedKindsForPlatformUserThisFrame	A bitmask of any game input kinds that have already been processed by the platform user this frame. If the UGameInputDeveloperSettings::bDoNotProcessDuplicateCapabilitiesForSingleUser flag is true, then will skip processors whose input kind is set in this bitmask. Returns a bitmask of what GameInputKind's were processed this frame.
- L62 _public prototype_ `void ClearInputState(IGameInput* GameInput);` — Reset any input state that is necessary. This would be called when the application is no longer constrained for example
- L69 _public prototype_ `IGameInputDevice* GetGameInputDevice() const;` — Returns a pointer to the IGameInputDevice that this device is associated with If this is null, then this is a container for an input device which has been disconnected.
- L78 _public prototype_ `void SetGameInputDevice(IGameInputDevice* InDevice);` — Update the IGameInputDevice pointer that this container should use. This IGameInputDevice should have the same Local App ID as this container already, otherwise there will be an ensure @param InDevice	The new IGameInputDevice that this container should use.
- L81 _public prototype_ `APP_LOCAL_DEVICE_ID GetGameInputDeviceId() const;` — Returns the unique local device ID of this IGameInputDevice from the GameInput API.
- L83 _public prototype_ `void SetPlatformUserId(const FPlatformUserId InUserId);`
- L84 _public prototype_ `FPlatformUserId GetPlatformUserId() const;`
- L86 _public prototype_ `void SetInputDeviceId(const FInputDeviceId InDeviceId);`
- L87 _public prototype_ `FInputDeviceId GetDeviceId() const;`
- L89 _public prototype_ `uint64 GetLastReadingTimestamp() const;`
- L96 _public prototype_ `const int32 GetNumberOfProcessors() const;` — Returns the number of processors that this device container currently has. Note: If this is zero, then this device can't possibly fire any input events.
- L101 _protected prototype_ `virtual void InitalizeDeviceProcessors_Impl();` — Create any device processors necessary for this Game Input device to process input and send input events
- L104 _protected member_ `TSharedRef<FGenericApplicationMessageHandler> MessageHandler;` — Message handler that we can use to tell the engine about input events
- L107 _protected member_ `IGameInputDevice* Device;` — The owning Game Input device that this device is associated with
- L110 _protected member_ `GameInputKind AllowedGameInputKinds;` — The kinds of Input that are allowed to be created for this device.
- L113 _protected member_ `FPlatformUserId UserId;` — The owning Platform User ID that this device is associated with
- L116 _protected member_ `FInputDeviceId AssignedDeviceId;` — The Input Device ID that this Game Input Device is associated with
- L125 _protected member_ `APP_LOCAL_DEVICE_ID LocalDeviceId;` — The unique ID that is associated with this device from the GameInput API. This will be set only once upon construction of this container. @see IGameInputDeviceInterface::GetDeviceData @see https://learn.microsoft.com/en-us/gaming/gdk/_content/gc/reference/system/xuser/structs/app_local_device_id
- L128 _protected member_ `TArray<TSharedPtr<IGameInputDeviceProcessor>> Processors;` — Input Device processors to handle input for any specific types required (gamepad, racing wheel, KBM, etc)
- L131 _protected member_ `TComPtr<IGameInputReading> LastReading;` — The last reading that was processed by this device
- L134 _protected member_ `uint64 IgnoreReadingTimestamp;` — Timestamp that can be used to check if we should ignore a reading from the past or not
- L137 _protected member_ `uint64 LastReadingTimestamp;` — Timestamp of the last reading processed by this device

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEINPUTBASE_API`

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/GameInputDeviceProcessor.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/GameInputHapticEndpointSettings.h` (Public)


#### struct `FGameInputHapticEndpointSettingsProxy`  
`struct FGameInputHapticEndpointSettingsProxy : public IAudioEndpointSettingsProxy`  
_L18-20_
- inherits: `IAudioEndpointSettingsProxy`
- desc: Thread-safe proxy for UGameInputHapticEndpointSettings, used on the audio thread. Currently empty — the factory binds endpoints to controllers based on connection order at the audio-device level, not via per-submix settings. Kept as a distinct type so additional per-endpoint knobs (e.g. attenuation, channel remap) can be added without changing the factory contract.

#### class `UGameInputHapticEndpointSettings`  
`class UGameInputHapticEndpointSettings : public UAudioEndpointSettingsBase`  
_L32-42_
- reflection: `UCLASS()`
- inherits: `UAudioEndpointSettingsBase`
- desc: Settings asset for the "Vibration Output" audio endpoint. Assign this to a Sound Submix Endpoint asset to route audio to a GameInput haptic-capable controller's haptic motors. The factory currently routes haptic audio to the first connected haptic controller. Multi-controller routing is not yet supported — see FGameInputHapticEndpointFactory if/when per-controller targeting is required.
- L38 _public function_ `virtual TUniquePtr<IAudioEndpointSettingsProxy> GetProxy() const override`

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/GameInputKeyTypes.h` (Public)


#### struct `FGameInputKeys`  
`struct FGameInputKeys`  
_L16-73_
- desc: Key types that are unique to the Game Input plugin These keys are added on module startup of the Game Input module. HEY, LISTEN! If you add or otherwise modify these keys, make sure the change is reflected in FGameInputBaseModule::InitializeGameInputKeys.
- L23 _public member_ `static const FKey RacingWheel_Brake;` — Analog types
- L24 _public member_ `static const FKey RacingWheel_Clutch;`
- L25 _public member_ `static const FKey RacingWheel_Handbrake;`
- L26 _public member_ `static const FKey RacingWheel_Throttle;`
- L27 _public member_ `static const FKey RacingWheel_Wheel;`
- L28 _public member_ `static const FKey RacingWheel_PatternShifterGear;`
- L31 _public member_ `static const FKey RacingWheel_None;` — Button types
- L32 _public member_ `static const FKey RacingWheel_Menu;`
- L33 _public member_ `static const FKey RacingWheel_View;`
- L34 _public member_ `static const FKey RacingWheel_PreviousGear;`
- L35 _public member_ `static const FKey RacingWheel_NextGear;`
- L42 _public member_ `static const FKey FlightStick_Roll;` — Analog types
- L43 _public member_ `static const FKey FlightStick_Pitch;`
- L44 _public member_ `static const FKey FlightStick_Yaw;`
- L45 _public member_ `static const FKey FlightStick_Throttle;`
- L48 _public member_ `static const FKey FlightStick_None;` — Button types
- L49 _public member_ `static const FKey FlightStick_Menu;`
- L50 _public member_ `static const FKey FlightStick_View;`
- L51 _public member_ `static const FKey FlightStick_FirePrimary;`
- L52 _public member_ `static const FKey FlightStick_FireSecondary;`
- L59 _public member_ `static const FKey ArcadeStick_Action1;` — Button Types
- L60 _public member_ `static const FKey ArcadeStick_Action2;`
- L61 _public member_ `static const FKey ArcadeStick_Action3;`
- L62 _public member_ `static const FKey ArcadeStick_Action4;`
- L63 _public member_ `static const FKey ArcadeStick_Action5;`
- L64 _public member_ `static const FKey ArcadeStick_Action6;`
- L65 _public member_ `static const FKey ArcadeStick_Special1;`
- L66 _public member_ `static const FKey ArcadeStick_Special2;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GAMEINPUTBASE_API`

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/GameInputLogging.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameInput, Log, All);`

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/GameInputUtils.h` (Public)


#### enum `UE::GameInput::(anonymous)`  
`enum`  
_L91-91_
- desc: Button flags assigned by GameInput

#### enum `UE::GameInput::EGameInputAuxButton`  
`enum EGameInputAuxButton`  
_L94-106_
- desc: Allocate flags for emulated/extended digital button functionality
- L96 _public enumerator_ `GamepadButtonAux_LeftTrigger = (1 << 22)`
- L97 _public enumerator_ `GamepadButtonAux_RightTrigger = (1 << 23)`
- L98 _public enumerator_ `GamepadButtonAux_LeftStickUp = (1 << 24)`
- L99 _public enumerator_ `GamepadButtonAux_LeftStickDown = (1 << 25)`
- L100 _public enumerator_ `GamepadButtonAux_LeftStickLeft = (1 << 26)`
- L101 _public enumerator_ `GamepadButtonAux_LeftStickRight = (1 << 27)`
- L102 _public enumerator_ `GamepadButtonAux_RightStickUp = (1 << 28)`
- L103 _public enumerator_ `GamepadButtonAux_RightStickDown = (1 << 29)`
- L104 _public enumerator_ `GamepadButtonAux_RightStickLeft = (1 << 30)`
- L105 _public enumerator_ `GamepadButtonAux_RightStickRight = (1 << 31)`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace GameInput` (scope `UE`)
- L21 _prototype_ `bool HasValidVersionOfGameInput();` (scope `UE::GameInput`) — @return True if there is a valid version of Game Input currently available
- L27 _prototype_ `FString GetInstalledGameInputVersionInfoString();` (scope `UE::GameInput`) — Returns a string which represents the version of Game Input that is installed on this machine. "Unknown" will be used if no valid version is found.
- L33 _prototype_ `FString GetMinVersionOfGameInputRedistString();` (scope `UE::GameInput`) — Returns a string which represents the min required version of Game Input needed to run the engine. "Unknown" will be used if no valid version is found.
- L35 _prototype_ `FString LexToString(IGameInputDevice* Device);` (scope `UE::GameInput`)
- L37 _prototype_ `FString LexToString(GameInputDeviceStatus DeviceStatus);` (scope `UE::GameInput`)
- L39 _prototype_ `FString LexToString(GameInputKind InputKind);` (scope `UE::GameInput`)
- L41 _prototype_ `FString LexToString(GameInputSwitchPosition SwitchPos);` (scope `UE::GameInput`)
- L44 _prototype_ `FString LexToString(GameInputSensorsKind SensorKind);` (scope `UE::GameInput`)
- L46 _prototype_ `FString LexToString(GameInputSensorAccuracy SensorKind);` (scope `UE::GameInput`)
- L49 _prototype_ `FString LexToString(const APP_LOCAL_DEVICE_ID& DeviceId);` (scope `UE::GameInput`)
- L51 _prototype_ `const TCHAR* GetMouseButtonName(EMouseButtons::Type MouseButton);` (scope `UE::GameInput`)
- L53 _prototype_ `EInputDeviceConnectionState DeviceStateToConnectionState(GameInputDeviceStatus InCurrentStatus, GameInputDeviceStatus InPreviousStatus);` (scope `UE::GameInput`)
- L61 _prototype_ `bool GameInputButtonToUnrealName(const TMap<uint32, FGamepadKeyNames::Type>& UEButtonMap, uint32 ButtonMask, OUT FGamepadKeyNames::Type& OutKeyName);` (scope `UE::GameInput`) — Populates the OutKeyName with the name of the Unreal Engine FKey that should be used for the given button mask, based on the UE button map that should be used. @return true if a key name was found, false otherwise.
- L64 _prototype_ `const TMap<GameInputSwitchPosition, TArray<FGamepadKeyNames::Type>>& GetSwitchButtonMap();` (scope `UE::GameInput`) — A map of game input switch position enums to Unreal Engine FKey names
- L70 _prototype_ `const TArray<FGamepadKeyNames::Type>* SwitchPositionToUnrealName(const GameInputSwitchPosition ButtonMask);` (scope `UE::GameInput`) — Gets an array of FKeys that are associated with the given switch position. The array can have multiple keys if the GameInput switch state is "Up/Down + Left/Right"
- L72 _prototype_ `const GameInputDeviceInfo* GetDeviceInfo(IGameInputDevice* Device);` (scope `UE::GameInput`)
- L74 _prototype_ `APP_LOCAL_DEVICE_ID GetDeviceAppLocalDeviceId(IGameInputDevice* Device);` (scope `UE::GameInput`)
- L78 _prototype_ `::FGameInputHapticEndpointFactory* GetHapticEndpointFactory();` (scope `UE::GameInput`) — Returns the haptic endpoint factory, or null if haptic support is disabled or GameInput is not the preferred input device.
- L82 _prototype_ `FName GetDeviceScopeClassName();` (scope `UE::GameInput`) — The FName which should be used to construct FInputDeviceScope's for game input devices.
- L88 _prototype_ `FStringView GetHardwareDeviceIdentifierName(IGameInputDevice* Device);` (scope `UE::GameInput`) — Returns the string hardware device identifier for the given input event params that can be used to create an FInputDeviceScope
- L91 _enumerator_ `enum { GamingInputButtonMask = 0x3FFF }; enum EGameInputAuxButton { GamepadButtonAux_LeftTrigger = (1 << 22), GamepadButtonAux_RightTrigger = (1 << 23), GamepadButtonAux_LeftStickUp = (1 << 24),` (scope `UE::GameInput::__anon5fff09a60103`) — Button flags assigned by GameInput
- L110 _variable_ `static constexpr float GamepadLeftStickDeadzone = (7849.0f / 32768.0f);` (scope `UE::GameInput`) — TODO_BH: Move these into a nice settings object instead of being hard coded Values taken from XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, XINPUT_GAMEPAD_TRIGGER_THRESHOLD used by XInput.
- L111 _variable_ `static constexpr float GamepadRightStickDeadzone = (8689.0f / 32768.0f);` (scope `UE::GameInput`)
- L112 _variable_ `static constexpr float GamepadTriggerDeadzone = (30.0f / 255.0f);` (scope `UE::GameInput`)
- L113 _variable_ `static constexpr float SensorMagneticNorthDeadzone = (30.0f / 255.0f);` (scope `UE::GameInput`)
- L115 _variable_ `static constexpr float InitialRepeatDelay = (0.2f);` (scope `UE::GameInput`)
- L116 _variable_ `static constexpr float SubsequentRepeatDelay = (0.1f);` (scope `UE::GameInput`)

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/IGameInputDeviceInterface.h` (Public)


#### class `IGameInputDeviceInterface`  
`class IGameInputDeviceInterface : public IInputDevice`  
_L20-196_
- inherits: `IInputDevice`
- desc: IInputDevice interface for the Game Input library. This is a base class that is intended to be implemented on each platform that supports it (Xbox and PC). This stores all state about every unique Human Interface Device that the GameInput library detects. Any implementors of this interface should be Created in an IInputDevice module's CreateInputDevice function (IInputDeviceModule::CreateInputDevice), and have it's Initialize function called
- L23 _public prototype_ `explicit IGameInputDeviceInterface(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler, struct IGameInput* InGameInput);`
- L30 _public prototype_ `void Initialize();` — Init function that should be called post-construction of this object. This is required for sending controller events and will ensure if not called.
- L36 _protected function_ `virtual EInputDeviceThreadAffinity GetThreadAffinity() const override` — GameInput polling is designed for multi-threaded access per Microsoft docs.
- L37 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L38 _protected prototype_ `virtual void SendControllerEvents() override;`
- L39 _protected prototype_ `virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;`
- L40 _protected prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L41 _protected prototype_ `virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;`
- L42 _protected prototype_ `virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues& values) override;`
- L43 _protected prototype_ `virtual bool IsGamepadAttached() const override;`
- L49 _protected prototype_ `virtual GameInputKind GetCurrentGameInputKindSupport() const;` — Returns a mask of the currently supported Game Input Kind that we want to get the reading of.
- L52 _protected prototype_ `virtual bool BindDeviceStatusCallbacks();` — Binds a listener for device status changes from game input to this class
- L57 _protected prototype_ `virtual void OnDeviceConnectionChanged(GameInputCallbackToken CallbackToken, IGameInputDevice* Device, uint64 Timestamp, GameInputDeviceStatus CurrentStatus, GameInputDeviceStatus PreviousStatus);` — A callback for when an input device connection change has been detected.
- L65 _protected prototype_ `virtual bool IsSupportedDevice(IGameInputDevice* Device) const;` — Returns true if the given IGameInputDevice is one which is allowed to be processed based on the Game Input Developer Settings. This may return false for devices which have specific PID/VID's which this project does not wish GameInput to process, or if the device is within a specific family that we do not want to process.
- L71 _protected prototype_ `virtual void HandleDeviceDisconnected(IGameInputDevice* Device, uint64 Timestamp) = 0;` — Mark this device as disconnected and invalidate the tracked game input device. A disconnected device will stay in the GameInputSourceDevices with a null Device pointer.
- L78 _protected prototype_ `virtual void HandleDeviceConnected(IGameInputDevice* Device, uint64 Timestamp) = 0;` — Map this new input device to a platform user and initialize the known FGameInputDeviceInfo. If this is a new connection, this will request a new FInputDeviceId from the platform input device mapper and add it to the GameInputSourceDevices map.
- L88 _private prototype_ `void HandleHapticsReady(IGameInputDevice* Device, uint64 Timestamp);` — Handle haptics being notified as ready from the given device. This should only be called internally from this device interface in response to a callback from the GameInput api
- L90 _private prototype_ `void TeardownHapticAudio(IGameInputDevice* Device);`
- L100 _protected prototype_ `virtual void HandleHapticsReady_Impl(IGameInputDevice* Device, uint64 Timestamp, struct GameInputHapticInfo& HapticInfo);` — Any platform specific haptic setup can be done here in an override. The base implementation sets up WASAPI-backed audio endpoints for haptic audio. Note: You likely want to wrap the implementation of this function in #if UE_GAME_INPUT_SUPPORTS_HAPTICS.
- L106 _protected prototype_ `virtual void TeardownHapticAudio_Impl(IGameInputDevice* Device);` — Tears down the WASAPI haptic audio device associated with the given GameInput device on disconnect. Only has effect when UE_GAME_INPUT_SUPPORTS_HAPTICS is true.
- L109 _protected prototype_ `void ProcessDeferredDeviceConnectionChanges();` — Process any deferred device connection changes that may have occurred. This should only be called on the game thread.
- L111 _protected prototype_ `void CoalesceDeferredDeviceConnectionChanges();`
- L114 _protected prototype_ `void OnAppConstrained();` — Callbacks for when the app is constrained/unconstrained (i.e. you Alt + Tab out of the window, or open the home menu on a console platform)
- L115 _protected prototype_ `void OnAppUnconstrained();`
- L118 _protected prototype_ `void DetermineStateAfterFirstUnconstrainedUpdate();` — Called on the first update after the was un-constrained.
- L121 _protected prototype_ `FGameInputDeviceContainer* GetDeviceData(IGameInputDevice* InDevice);` — Returns a matching FGameInputDeviceContainer if one exists for the given GameInput device. Nullptr if none exist.
- L128 _protected prototype_ `FGameInputDeviceContainer* GetOrCreateDeviceData(IGameInputDevice* InDevice);` — Returns a pointer to the Device info associated with the given IGameInputDevice. If one doesn't exist, then create a new one and return that.
- L134 _protected prototype_ `virtual FGameInputDeviceContainer* CreateDeviceData(IGameInputDevice* InDevice) = 0;` — Creates a new FGameInputDeviceContainer* and stores it in DeviceData. It is up to each implementing device interface to how that device is mapped to platform users and initialized.
- L139 _protected prototype_ `virtual void EnumerateCurrentlyConnectedDeviceTypes();` — This will update the CurrentlyConnectedDeviceTypes bitmask based on the current set of DeviceData
- L142 _protected member_ `TSharedRef<FGenericApplicationMessageHandler> MessageHandler;` — Message handler that we can use to tell the engine about input events
- L145 _protected member_ `TComPtr<IGameInput> GameInput;` — Pointer to the Game Input interface object
- L148 _protected member_ `FCriticalSection DeviceInfoCS;` — CS for OnDeviceConnectionChanged called from background system thread and PollGameDeviceState called from Main thread
- L151 _protected member_ `GameInputCallbackToken ConnectionChangeCallbackToken;` — Token for when a device connection change happens
- L154 _protected member_ `GameInputKind CurrentlyConnectedDeviceTypes;` — An enumeration of all the currently registered Game input Devices.
- L157 _protected member_ `bool bWasinitialized;` — Set to true if the IGameInputDeviceInterface::Initialize function was called. This is required for sending controller events.
- L160 _protected member_ `bool bIsAppCurrentlyConstrained;` — True if the app is currently constrained this tick
- L163 _protected member_ `bool bWasAppConstrainedLastTick;` — True if the app was constrained last tick
- L166 _protected member_ `TArray<TSharedPtr<FGameInputDeviceContainer>> DeviceData;` — Array of Input Device data for every connected Game Input Device.
- L169 _protected member_ `TMap<FPlatformUserId, TSharedPtr<FGameInputDeviceContainer>> PlatformUserIdToMostRecentDeviceContainer;` — A mapping of a platform user to the most recently used Input Device for that user
- L193 _protected member_ `TArray<FDeferredDeviceConnectionChanges> DeferredDeviceConnectionChanges;` — Array of device connection changed events that will be processed in ProcessDeferredDeviceConnectionChanges.

#### struct `IGameInputDeviceInterface::FDeferredDeviceConnectionChanges`  
`struct FDeferredDeviceConnectionChanges`  
_L172-190_
- desc: Stores some data about when device connection changes happen to be processed later
- L174 _public prototype_ `FDeferredDeviceConnectionChanges() = default;`
- L177 _public member_ `IGameInputDevice* Device = nullptr;` — The GameInput device that has changed
- L180 _public member_ `uint64 Timestamp = 0;` — Timestamp of when the connection state change happened
- L183 _public member_ `EInputDeviceConnectionState Status = EInputDeviceConnectionState::Invalid;` — The evaluated status of the game input device
- L186 _public member_ `GameInputDeviceStatus CurrentStatus = GameInputDeviceStatus::GameInputDeviceNoStatus;` — The current GameInput status of the device
- L189 _public member_ `GameInputDeviceStatus PreviousStatus = GameInputDeviceStatus::GameInputDeviceNoStatus;` — The previous GameInput status of the device

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/Processors/GameInputDeviceProcessor_ArcadeStick.h` (Public)


#### class `FGameInputArcadeStickProcessor`  
`class FGameInputArcadeStickProcessor : public IGameInputDeviceProcessor`  
_L14-34_
- inherits: `IGameInputDeviceProcessor`
- desc: Processor for the GameInputKindArcadeStick type. These are typically accessories to "fighting" style games, or other arcade style games.
- L17 _public prototype_ `FGameInputArcadeStickProcessor();`
- L21 _protected prototype_ `virtual bool ProcessInput(const FGameInputEventParams& Params) override;`
- L22 _protected prototype_ `virtual void ClearState(const FGameInputEventParams& Params) override;`
- L23 _protected prototype_ `virtual GameInputKind GetSupportedReadingKind() const override;`
- L26 _protected member_ `GameInputArcadeStickState PreviousState;` — The previously processed arcade stick state.
- L32 _protected member_ `static constexpr uint32 MaxSupportedButtons = 16;` — Array of repeat times to calculate if a button has been held long enough to receive an IE_REPEAT event.
- L33 _protected member_ `double RepeatTime[MaxSupportedButtons];`

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/Processors/GameInputDeviceProcessor_Controller.h` (Public)


#### class `FGameInputControllerDeviceProcessor`  
`class FGameInputControllerDeviceProcessor : public IGameInputDeviceProcessor`  
_L19-71_
- inherits: `IGameInputDeviceProcessor`
- desc: Processor for Controller Input Types Controllers are very similar to Gamepad types, and often can just be a third party controller type that is not natively supported by the "GamepadInputKind". This can include things like instruments, other platform controller types, or other third party input devices.
- L22 _public prototype_ `FGameInputControllerDeviceProcessor();`
- L25 _protected prototype_ `virtual bool ProcessInput(const FGameInputEventParams& Params) override;`
- L26 _protected prototype_ `virtual bool PostProcessInput(const FGameInputEventParams& Params) override;`
- L27 _protected prototype_ `virtual void ClearState(const FGameInputEventParams& Params) override;`
- L28 _protected prototype_ `virtual GameInputKind GetSupportedReadingKind() const override;`
- L31 _protected prototype_ `bool ProcessControllerButtonState(const FGameInputEventParams& Params, const FGameInputDeviceConfiguration* Config, IGameInputReading* InputReading);` — Processes Controller buttons (often face buttons, like ABXY or Circle/Triangle/Square/X)
- L37 _protected prototype_ `bool ProcessControllerAxisState(const FGameInputEventParams& Params, const FGameInputDeviceConfiguration* Config, IGameInputReading* InputReading);` — Process any axis readings on this controller. This will only process axises that are configured in the given Config.
- L42 _protected prototype_ `bool ProcessControllerSwitchState(const FGameInputEventParams& Params, const FGameInputDeviceConfiguration* Config, IGameInputReading* InputReading);` — Process the controller switch (also known as the DPad) state
- L45 _protected prototype_ `static const TMap<GameInputLabel, FGamepadKeyNames::Type>& GetGameInputButtonLabelToUnrealName();` — A map of GameInputLabel types to Unreal Engine FKey names.
- L48 _protected member_ `uint32 LastButtonHeldMask = 0;` — Bitmask of any held buttons from the last frame
- L54 _protected member_ `double RepeatTime[MaxSupportedButtons];` — Timings of when a key press should be considered a "repeat" key
- L57 _protected member_ `TArray<double> SwitchRepeatTimes;` — Repeat times for when switches are pressed (aka the DPad)
- L60 _protected member_ `TArray<float> PreviousControllerAxisValues;` — Previous frame's axis values
- L63 _protected member_ `TArray<GameInputSwitchPosition> PreviousSwitchPositions;` — Array of switch positions
- L70 _protected member_ `int32 NumReadingsProcessedThisFrame = 0;` — Keeps track of how many times this gamepad has been processed this frame. Every successful processing of button input in ProcessInput will increment this value. This will get reset at the end of the input frame in PostProcessInput.

#### enum `FGameInputControllerDeviceProcessor::(anonymous)`  
`enum`  
_L51-51_
- desc: Max number of buttons this processor supports

#### Free symbols / members of external scopes

- L51 _enumerator_ `enum { MaxSupportedButtons = 32 }; double RepeatTime[MaxSupportedButtons]; TArray<double> SwitchRepeatTimes;` (scope `FGameInputControllerDeviceProcessor::__anon4af3d08a0103`) — Max number of buttons this processor supports

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/Processors/GameInputDeviceProcessor_FlightStick.h` (Public)


#### class `FGameInputFlightStickProcessor`  
`class FGameInputFlightStickProcessor : public IGameInputDeviceProcessor`  
_L12-50_
- inherits: `IGameInputDeviceProcessor`
- desc: Processor for the GameInputKindFlightStick type.
- L15 _public prototype_ `FGameInputFlightStickProcessor();`
- L19 _protected prototype_ `virtual bool ProcessInput(const FGameInputEventParams& Params) override;`
- L20 _protected prototype_ `virtual bool PostProcessInput(const FGameInputEventParams& Params) override;`
- L21 _protected prototype_ `virtual void ClearState(const FGameInputEventParams& Params) override;`
- L22 _protected prototype_ `virtual GameInputKind GetSupportedReadingKind() const override;`
- L27 _protected prototype_ `bool ProcessFlightStickButtons(const FGameInputEventParams& Params, GameInputFlightStickState& State);` — Process Flight stick specific buttons.
- L32 _protected prototype_ `bool ProcessFlightStickAnalog(const FGameInputEventParams& Params, GameInputFlightStickState& State);` — Process the analog values (yaw, pitch, roll, and throttle) of the flight stick
- L39 _protected member_ `int32 NumReadingsProcessedThisFrame = 0;` — Keeps track of how many times this gamepad has been processed this frame. Every successful processing of button input in ProcessInput will increment this value. This will get reset at the end of the input frame in PostProcessInput.
- L42 _protected member_ `GameInputFlightStickState PreviousState = {};` — State of the flight stick from the previous frame
- L45 _protected member_ `static constexpr uint32 MaxSupportedButtons = 32;` — Repeat times for any pressed buttons
- L46 _protected member_ `double RepeatTime[MaxSupportedButtons];`
- L49 _protected member_ `TArray<double> SwitchRepeatTimes;` — Repeat times for when switches are pressed (aka the DPad)

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/Processors/GameInputDeviceProcessor_Gamepad.h` (Public)


#### class `FGameInputGamepadDeviceProcessor`  
`class FGameInputGamepadDeviceProcessor : public IGameInputDeviceProcessor`  
_L12-39_
- inherits: `IGameInputDeviceProcessor`
- desc: Processor for Gamepad Inputs
- L15 _protected prototype_ `virtual bool ProcessInput(const FGameInputEventParams& Params) override;`
- L16 _protected prototype_ `virtual bool PostProcessInput(const FGameInputEventParams& Params) override;`
- L17 _protected prototype_ `virtual void ClearState(const FGameInputEventParams& Params) override;`
- L18 _protected prototype_ `virtual GameInputKind GetSupportedReadingKind() const override;`
- L20 _protected prototype_ `bool ProcessGamepadAnalogState(const FGameInputEventParams& Params, GameInputGamepadState& GamepadState);`
- L21 _protected prototype_ `virtual bool ProcessGamepadButtonState(const FGameInputEventParams& Params, GameInputGamepadState& GamepadState);`
- L23 _protected member_ `GameInputGamepadState PreviousState = {};`
- L25 _protected member_ `uint32 LastButtonHeldMask = 0;`
- L27 _protected member_ `uint32 LastAnalogButtonHeldMask = 0;`
- L31 _protected member_ `double RepeatTime[MaxSupportedButtons] = { };`
- L38 _protected member_ `int32 NumReadingsProcessedThisFrame = 0;` — Keeps track of how many times this gamepad has been processed this frame. Every successful processing of button input in ProcessInput will increment this value. This will get reset at the end of the input frame in PostProcessInput.

#### enum `FGameInputGamepadDeviceProcessor::(anonymous)`  
`enum`  
_L29-29_

#### Free symbols / members of external scopes

- L29 _enumerator_ `enum { MaxSupportedButtons = 32 }; double RepeatTime[MaxSupportedButtons] = { }; /** * Keeps track of how many times this gamepad has been processed this frame. * Every successful processing of button input in ProcessInput will increment this value. * This will get reset at the end of the input frame in PostProcessInput.` (scope `FGameInputGamepadDeviceProcessor::__anonf38495b50103`)

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/Processors/GameInputDeviceProcessor_KeyboardMouse.h` (Public)


#### class `FGameInputKeyboardDeviceProcessor`  
`class FGameInputKeyboardDeviceProcessor : public IGameInputDeviceProcessor`  
_L12-31_
- inherits: `IGameInputDeviceProcessor`
- desc: Processor for Keyboard inputs
- L15 _protected prototype_ `virtual bool ProcessInput(const FGameInputEventParams& Params) override;`
- L16 _protected prototype_ `virtual void ClearState(const FGameInputEventParams& Params) override;`
- L17 _protected prototype_ `virtual GameInputKind GetSupportedReadingKind() const override;`
- L19 _protected prototype_ `virtual void UpdateUnifiedKeyboardState(const FGameInputEventParams& Params, TSet<uint8>& CurrentPressedKeys);`
- L21 _protected prototype_ `bool IsKeyPressed(uint8 VirtualKeyCode) const;`
- L23 _protected prototype_ `virtual void SetSimulatedCapsLock(bool bVal);`
- L25 _protected member_ `TSet<uint8> LastPressedKeys;`
- L27 _protected member_ `TMap<uint8, double> KeyRepeatTime;`
- L30 _protected member_ `bool bSimulatedCapsLock = {};` — cannot read actual caps lock state, so necessary to simulate it as a bool toggle

#### class `FGameInputMouseDeviceProcessor`  
`class FGameInputMouseDeviceProcessor : public IGameInputDeviceProcessor`  
_L37-59_
- inherits: `IGameInputDeviceProcessor`
- desc: Processor for mouse inputs
- L40 _public prototype_ `explicit FGameInputMouseDeviceProcessor(const TSharedPtr<class ICursor>& InCursor);`
- L43 _protected prototype_ `virtual bool ProcessInput(const FGameInputEventParams& Params) override;`
- L44 _protected prototype_ `virtual void ClearState(const FGameInputEventParams& Params) override;`
- L45 _protected prototype_ `virtual GameInputKind GetSupportedReadingKind() const override;`
- L47 _protected prototype_ `virtual bool CanProcessVirtualMouse() const;`
- L49 _protected member_ `TSharedPtr<class ICursor> Cursor = nullptr;`
- L51 _protected member_ `GameInputMouseState PreviousMouseState = {};`
- L53 _protected member_ `FVector2D LastMouseOffset = {};`
- L56 _protected member_ `double RepeatTime[MaxSupportedButtons];`
- L58 _protected member_ `uint32 LastButtonHeldMask = 0;`

#### enum `FGameInputMouseDeviceProcessor::(anonymous)`  
`enum`  
_L55-55_

#### Free symbols / members of external scopes

- L55 _enumerator_ `enum { MaxSupportedButtons = 32 }; double RepeatTime[MaxSupportedButtons]; uint32 LastButtonHeldMask = 0;` (scope `FGameInputMouseDeviceProcessor::__anond4e8cd200103`)

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/Processors/GameInputDeviceProcessor_RacingWheel.h` (Public)


#### class `FGameInputRacingWheelProcessor`  
`class FGameInputRacingWheelProcessor : public IGameInputDeviceProcessor`  
_L15-56_
- inherits: `IGameInputDeviceProcessor`
- desc: Processor for racing wheel types (GameInputKindRacingWheel) Note: Racing wheels are often paired with other device processors like Gamepad/Controller to handle any "normal" buttons that may be on them.
- L18 _public prototype_ `FGameInputRacingWheelProcessor();`
- L20 _protected prototype_ `virtual bool ProcessInput(const FGameInputEventParams& Params) override;`
- L21 _protected prototype_ `virtual bool PostProcessInput(const FGameInputEventParams& Params) override;`
- L22 _protected prototype_ `virtual void ClearState(const FGameInputEventParams& Params) override;`
- L23 _protected prototype_ `virtual GameInputKind GetSupportedReadingKind() const override;`
- L28 _protected prototype_ `static const float GetRacingWheelDeadzone();` — Returns the deadzone that we would like to use for racing wheel analog inputs.
- L33 _protected prototype_ `bool ProcessWheelAnalogState(const FGameInputEventParams& Params, GameInputRacingWheelState& CurrentWheelState);` — Processes the analog inputs of the wheel state (brake/clutch pedals, wheel movement, etc).
- L38 _protected prototype_ `bool ProcessWheelButtonState(const FGameInputEventParams& Params, GameInputRacingWheelState& CurrentWheelState);` — Processes any buttons on the racing wheel (next/previous gears, menu nav, etc);
- L45 _protected member_ `int32 NumReadingsProcessedThisFrame = 0;` — Keeps track of how many times this gamepad has been processed this frame. Every successful processing of button input in ProcessInput will increment this value. This will get reset at the end of the input frame in PostProcessInput.
- L48 _protected member_ `GameInputRacingWheelState PreviousState;` — The previous game input state that was last processed.
- L54 _protected member_ `static const uint32 MaxSupportedButtons = 16;` — Array of repeat times to calculate if a button has been held long enough to receive an IE_REPEAT event.
- L55 _protected member_ `double RepeatTime[MaxSupportedButtons];`

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/Processors/GameInputDeviceProcessor_Raw.h` (Public)


#### class `FGameInputRawDeviceProcessor`  
`class FGameInputRawDeviceProcessor : public IGameInputDeviceProcessor`  
_L21-154_
- inherits: `IGameInputDeviceProcessor`
- desc: Processor for raw input types (GameInputKindRawDeviceReport) Raw input is very customizable and is very different per-input device, so it requires a lot of configuration. Most of the time it is special analog inputs on custom third party devices. A good example is the Whammy bar on a guitar controller, or maybe some special shifter on a racing wheel that the Game Input API does not pick up by default.
- L24 _protected prototype_ `virtual bool ProcessInput(const FGameInputEventParams& Params) override;`
- L25 _protected prototype_ `virtual bool PostProcessInput(const FGameInputEventParams& Params) override;`
- L26 _protected prototype_ `virtual void ClearState(const FGameInputEventParams& Params) override;`
- L27 _protected prototype_ `virtual GameInputKind GetSupportedReadingKind() const override;`
- L33 _protected prototype_ `const GameInputRawDeviceReportInfo* ReadCurrentRawInputState(const FGameInputEventParams& Params, IGameInputReading* ReadingToUse);` — `UE_DEPRECATED(5.9, "Use ReadCurrentRawInputStateInfo instead.")` — Reads the current state of the raw input buffer and populates CurrentRawData and PreviousRawData
- L40 _private prototype_ `const GameInputRawDeviceReportInfo* Internal_AttemptToReadCurrentRawInputState(const FGameInputEventParams& Params, IGameInputReading* ReadingToUse);` — Reads the raw report info for GameInput API version 0. If the Api version is different then 0, this will return nullptr.
- L46 _protected prototype_ `GameInputRawDeviceReportInfo ReadCurrentRawInputStateInfo(const FGameInputEventParams& Params, IGameInputReading* ReadingToUse);` — Returns the raw report info about the given reading which can be used to access the raw serialized data such as the size, report id, and more.
- L55 _protected prototype_ `constexpr float RawValueToFloatTrigger(const uint8 RawValue) const;` — Translates the given uint8 RawValue to a float between 0.0 and +1.0, like most gamepad analog "triggers" @param RawValue @return			A float between 0.0 and +1.0
- L60 _protected prototype_ `constexpr float RawValueNibbleValueToFloat(const uint8 RawValue, const float Scale = 15.0f) const;` — Converts the lower 4 bits of the given raw value to a value between 0.0f and +1.0f based on the given scale.
- L70 _protected prototype_ `const float RawValueToFloatAnalog(uint8 RawValue, const uint8 DeadZone = 2) const;` — Translates the given uint8 RawValue to a float between -1.0 and +1.0. @param RawValue @param Deadzone @return A float between -1.0 and +1.0. Will be 0.0 if the value is within the deadzone.
- L76 _protected prototype_ `bool ProcessAllRawValues(const FGameInputEventParams& Params, const FGameInputDeviceConfiguration* DeviceConfig, const bool bShouldProcessButtons, const bool bShouldProcessAnalog);` — Processes all the current raw input data. This should only be called after we have read our current raw input report or we have manually set the values (i.e. when we clear the input)
- L82 _protected prototype_ `bool ProcessRawInputValueAsBitmask(const FGameInputEventParams& Params, const int32 RawValueIndex, const FGameInputRawDeviceReportData* AxisData);` — Processes the raw value at the given index as a button bitmask. For every bit in the raw value and treat it as 0 for pressed and 1 for on.
- L88 _protected prototype_ `bool ProcessRawInputValueAsButton(const FGameInputEventParams& Params, const int32 RawValueIndex, const FGameInputRawDeviceReportData* AxisData);` — Processes the raw value at the given index as a button value. If the value is non-zero, then treat it as pressed. If the value is zero, treat it as unpressed.
- L94 _protected prototype_ `bool ProcessRawInputValueAsAanalog(const FGameInputEventParams& Params, const int32 RawValueIndex, const FGameInputRawDeviceReportData* AxisData);` — Processes the raw value at the given index as an analog value. This will translate the uint8 to a float value and call OnControllerAnalog for it.
- L99 _protected prototype_ `bool ProcessRawInputValueAsAanalogPaired(const FGameInputEventParams& Params, const FGameInputRawDeviceReportData* AxisData);` — Processes a pair of raw input indexes. This allows you to combine the values of multiple uint8 axis readings and combine them
- L101 _protected prototype_ `bool ProcessRawInputValuePackedUInt8(const FGameInputEventParams& Params, const int32 RawValueIndex, const FGameInputRawDeviceReportData* AxisData);`
- L103 _protected prototype_ `void EvaluatePackedUInt8ButtonChordsAsAnalog( const FGameInputEventParams& Params, const uint8 CurrentValue, const uint8 PreviousValue, const TArray<FGamepadKeyNames::Type>& ButtonNames);`
- L109 _protected prototype_ `void EvaluatePackedUInt8ButtonChordsAsButtonEvents( const FGameInputEventParams& Params, const uint8 CurrentValue, const uint8 PreviousValue, double* RepeatTime, const TArray<FGamepadKeyNames::Type>& ButtonNames);`
- L119 _protected member_ `TArray<uint8> CurrentRawData;` — The current raw input data that is populated by IGameInputRawDeviceReport::GetRawData
- L124 _protected member_ `TArray<uint8> PreviousRawData;` — The previous frame's raw input data that is set at the end of ProcessInput.
- L146 _protected member_ `TMap<int32, FPerRawInputIndexData> RawInputIndexDataMap;` — A map of an index to some raw data associated with it. This is only used for button evaluation, not analog.
- L153 _protected member_ `int32 NumReadingsProcessedThisFrame = 0;` — Keeps track of how many times this gamepad has been processed this frame. Every successful processing of button input in ProcessInput will increment this value. This will get reset at the end of the input frame in PostProcessInput.

#### struct `FGameInputRawDeviceProcessor::FPerRawInputIndexData`  
`struct FPerRawInputIndexData`  
_L127-140_
- desc: A struct that contains info about each raw input index
- L134 _public member_ `double RepeatTime[MaxSupportedButtons];` — Stores the times that each button index has been pressed so we can detect key repeats
- L139 _public member_ `TMap<uint32, FName> KeyNameMap;` — A map of key names to int values that is generated dynamically based on the button mapping.

#### enum `FGameInputRawDeviceProcessor::FPerRawInputIndexData::(anonymous)`  
`enum`  
_L131-131_
- desc: The max number of buttons possibly associated with this raw input data. The raw input data is a uint8, so we can have at maximum a button per-bit, so 8.

#### Free symbols / members of external scopes

- L131 _enumerator_ `enum { MaxSupportedButtons = 8 }; double RepeatTime[MaxSupportedButtons]; /** * A map of key names to int values that is generated dynamically based on the button mapping. */` (scope `FGameInputRawDeviceProcessor::FPerRawInputIndexData::__anon6c2759300103`) — The max number of buttons possibly associated with this raw input data. The raw input data is a uint8, so we can have at maximum a button per-bit, so 8.

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/Processors/GameInputDeviceProcessor_Sensor.h` (Public)


#### class `FGameInputGamepadSensorDeviceProcessor`  
`class FGameInputGamepadSensorDeviceProcessor final : public IGameInputDeviceProcessor`  
_L14-46_
- inherits: `IGameInputDeviceProcessor`
- desc: Processor for Gamepad "Sensor" Inputs such as gyro or accelerometers
- L17 _protected prototype_ `virtual bool ProcessInput(const FGameInputEventParams& Params) override;`
- L18 _protected prototype_ `virtual bool PostProcessInput(const FGameInputEventParams& Params) override;`
- L19 _protected prototype_ `virtual void ClearState(const FGameInputEventParams& Params) override;`
- L20 _protected prototype_ `virtual GameInputKind GetSupportedReadingKind() const override;`
- L29 _protected prototype_ `bool ProcessGamepadSensorState(const FGameInputEventParams& Params, GameInputSensorsState& CurrentState);` — Process the current sensor state and report it to the engine via the message handler. @param Params Current input param data @param CurrentState The current sensor state for this frame @return True if there was any sensor data reported.
- L33 _protected member_ `GameInputSensorsState PreviousState = {};` — The sensor data from the previous reading that was processed
- L38 _protected member_ `GameInputSensorsState AccumulatedState = {};` — Accumulated sensor state for passing on once all input has been processed.
- L45 _protected member_ `int32 NumReadingsProcessedThisFrame = 0;` — Keeps track of how many times this gamepad has been processed this frame. Every successful processing of sensor input in ProcessInput will increment this value. This will get set to 0 or a negative value at the end of the input frame in PostProcessInput.

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/Processors/GameInputDeviceProcessor_Touch.h` (Public)


#### class `FGameInputTouchDeviceProcessor`  
`class FGameInputTouchDeviceProcessor : public IGameInputDeviceProcessor`  
_L14-44_
- inherits: `IGameInputDeviceProcessor`
- desc: Processor for touch inputs
- L17 _protected prototype_ `virtual bool ProcessInput(const FGameInputEventParams& Params) override;`
- L18 _protected prototype_ `virtual void ClearState(const FGameInputEventParams& Params) override;`
- L19 _protected prototype_ `virtual GameInputKind GetSupportedReadingKind() const override;`
- L38 _protected member_ `TArray<FTouchData> PreviousTouchData;`
- L39 _protected member_ `int32 ActiveTouchPoints = 0;`
- L42 _protected member_ `int32 MaxTouchX = 1920;` — The max touch X and Y of the touch region to let us scale input based on the size of the touch area
- L43 _protected member_ `int32 MaxTouchY = 1080;`

#### struct `FGameInputTouchDeviceProcessor::FTouchData`  
`struct FTouchData`  
_L21-37_
- L23 _public function_ `FTouchData()`
- L32 _public member_ `int64 TouchId;`
- L33 _public member_ `FVector2D Position;`
- L34 _public member_ `float Pressure;`
- L35 _public member_ `bool bHasMoved;`
- L36 _public member_ `bool bIsActive;`

### `Plugins/Runtime/GameInput/Source/GameInputBase/Public/Processors/IGameInputDeviceProcessor.h` (Public)


#### class `IGameInputDeviceProcessor`  
`class IGameInputDeviceProcessor`  
_L21-148_
- desc: A Game Input Device Processor is used to determine the state of a device each frame and send messages to the given Message Handler when we want to. Each processor represents a single "kind" of Game Input device. They are created by the owning GameInput Device Container (GameInputDeviceContainer.h) and polled each frame when possible. Each Human Interface Device can be made up of multiple Game Input Kinds, so a single device container may have multiple different processors associated with it.
- L24 _public prototype_ `IGameInputDeviceProcessor();`
- L26 _public prototype_ `virtual ~IGameInputDeviceProcessor() = default;`
- L63 _public prototype_ `virtual bool ProcessInput(const FGameInputEventParams& Params) = 0;` — Process any input events from the given reading and send events to the message handler using the given Platform User and Input Device Id's. This can be called multiple times per frame, like if we are running at a lower FPS. This is because GameInput may accumulate multiple readings to use by the time the game thread gets here. If you have inputs that you only want to process once per frame, then use PostProcessInput instead. @return True if any input events have been processed, false if nothing happened
- L83 _public prototype_ `virtual bool PostProcessInput(const FGameInputEventParams& Params);` — Called after all current Game Input readings have been processed this frame and there are no more readings for a device (GetNextReading returns GAMEINPUT_E_READING_NOT_FOUND). This is called regardless of if an accompanying ProcessInput call has happened. This function is useful for dealing with multiple readings in a single frame for analog devices. It is recommended that processors override this function and only process analog input events here at the end of the frame, once, instead of multiple times in ProcessInput. That is because at lower frame rates or hitches you will end up with more then one GameInput reading in the stack that we need to process. If you were to process all of those analog inputs in a single frame, the values would accumulate to above or below +-1.0, which could have unexpected behavior in Slate. @param Params		Game Input event params sent from the owning FGameInputDeviceContainer. Params.Reading should always be null here, as there is no current reading. Params.PreviousReading will contain the most recent Game Input reading from the input stack. @return			True if any input events have been processed, false if nothing happened
- L89 _public prototype_ `virtual void ClearState(const FGameInputEventParams& Params) = 0;` — Clear any input state related to this processor, typically by sending events to the message handler that each FKey related to this processor now has a value of 0.
- L98 _public prototype_ `virtual GameInputKind GetSupportedReadingKind() const = 0;` — Returns the kind of reading that this processor supports. If the current GameInput reading is not included in this bitmask, then this processor will not have it's "ProcessInput" function called. @see FGameInputDeviceContainer::ProcessInput
- L107 _protected prototype_ `const FString GetHardwareDeviceIdentifierName(const IGameInputDeviceProcessor::FGameInputEventParams& Params) const;` — `UE_DEPRECATED(5.8, "Use UE::GameInput::GetHardwareDeviceIdentifierName instead")` — Returns the string hardware device identifier for the given input event params that can be used to create an FInputDeviceScope
- L110 _protected prototype_ `void OnControllerAnalog(const FGameInputEventParams& Params, const FName& GamePadKey, float NewAxisValueNormalized, float OldAxisValueNormalized, float DeadZone, const bool bSetDeviceScope = true);` — A general use function to call the message handler and tell it about a controller analog key being used
- L121 _protected prototype_ `void EvaluateButtonStates( const FGameInputEventParams& Params, const uint32 CurrentButtonHeldMask, uint32& PreviousButtonMask, double* RepeatTime, const TMap<uint32, FGamepadKeyNames::Type>& UnrealButtonNameMap, const uint32 SupportedButtonCount);` — Helper function for processing the button states of Game input. @param CurrentButtonHeldMask			The current state of the button mask to evaluate @param PreviousButtonMask		The previous state of the button mask. This value will be modified to store the current button mask after evaluation @param RepeatTime				A map of the button index to a time that it was last active, used to determine if the key meets the qualifications for a repeat event @param UnrealButtonNameMap		A map of Unreal Engine Gamepad key names to their uint32 mapping from Game Input. @param SupportedButtonCount		The maximum number of buttons we can process
- L137 _protected prototype_ `void EvaluateSwitchState( const FGameInputEventParams& Params, GameInputSwitchPosition CurrentPosition, GameInputSwitchPosition& PreviousPosition, TArray<double>& RepeatTimes);` — Helper function to processing the state of a Switch position (aka a DPad, like left/right/up/down) @param Params		The GameInput event params @param CurrentPosition	The current position of the switch @param PreviousPosition	The previous position of the switch. This will be set to the value of the current switch at the end of this function @param RepeatTimes		Array of doubles that represent the time at which a switch was last pressed that we can use to check for when to send repeat events
- L144 _protected member_ `float InitialButtonRepeatDelay;` — Delay before sending a repeat message after a button was first pressed
- L147 _protected member_ `float ButtonRepeatDelay;` — Delay before sending a repeat message after a button has been pressed for a while

#### struct `IGameInputDeviceProcessor::FGameInputEventParams`  
`struct FGameInputEventParams`  
_L28-50_
- L31 _public member_ `IGameInputReading* Reading = nullptr;` — The current reading for this input event
- L34 _public member_ `IGameInputReading* PreviousReading = nullptr;` — The previous reading from the last frame.
- L37 _public member_ `IGameInputDevice* Device = nullptr;` — Device associated with this reading
- L40 _public member_ `TSharedPtr<FGenericApplicationMessageHandler> MessageHandler = nullptr;` — The message handler to use to send any input events
- L43 _public member_ `FPlatformUserId PlatformUserId = PLATFORMUSERID_NONE;` — The platform user that is associated with the input device that triggered this event
- L46 _public member_ `FInputDeviceId InputDeviceId = INPUTDEVICEID_NONE;` — The Input device ID of the device that triggered this event.
- L49 _public prototype_ `const GameInputDeviceInfo* GetDeviceInfo() const;` — Gets the Input Device Info for this GameInput Device if it is valid. Can be null.
