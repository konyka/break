# Runtime / InputDevice

- module root: `Source/Runtime/InputDevice`
- headers: 4; symbols: 33
- symbol kinds: class=3, enum=1, enumerator=2, function=14, member=1, prototype=11, struct=1
- PrivateDependencyModuleNames: Core, Engine

### `Source/Runtime/InputDevice/Public/IHapticDevice.h` (Public)


#### class `IHapticDevice`  
`class IHapticDevice`  
_L9-30_
- L19 _public prototype_ `virtual void SetHapticFeedbackValues(int32 ControllerId, int32 Hand, const FHapticFeedbackValues& Values) = 0;` — Sets the frequency / amplitude of the haptic channel of a controller. @param ControllerId	Id of the controller to set haptic feedback parameters on @param Hand			Which hand, if supported, to add the haptic feedback to (corresponds to EControllerHand) @param Values		The values to haptic parameter values (e.g. frequency and amplitude) set for the device
- L24 _public prototype_ `virtual void GetHapticFrequencyRange(float& MinFrequency, float& MaxFrequency) const = 0;` — Determines the valid range of frequencies this haptic device supports, to limit input ranges from UHapticFeedbackEffects
- L29 _public prototype_ `virtual float GetHapticAmplitudeScale() const = 0;` — Returns the scaling factor to map the amplitude of UHapticFeedbackEvents from [0.0, 1.0] to the actual range handled by the device

### `Source/Runtime/InputDevice/Public/IInputDevice.h` (Public)


#### enum `EInputDeviceThreadAffinity`  
`enum class EInputDeviceThreadAffinity : uint8`  
_L19-26_
- desc: Governs which thread is allowed to call Tick() and SendControllerEvents() on an IInputDevice. Output methods (SetChannelValue, SetChannelValues, SetLightColor, SetDeviceProperty, haptics, etc.) are always called from the game thread regardless of this affinity declaration. Default is GameThreadOnly — existing third-party IInputDevice plugins require no changes.
- L22 _public enumerator_ `GameThreadOnly` — Device must be ticked by the game thread. Safe for all legacy and Win32 message-pump devices.
- L25 _public enumerator_ `InputThreadSafe` — Device may be ticked by the dedicated input thread. Tick() and SendControllerEvents() must be thread-safe.

#### class `IInputDevice`  
`class IInputDevice`  
_L32-89_
- desc: Input device interface. Useful for plugins/modules to support custom external input devices.
- L35 _public prototype_ `virtual ~IInputDevice() = default;`
- L38 _public prototype_ `virtual void Tick( float DeltaTime ) = 0;` — Tick the interface (e.g. check for new controllers)
- L41 _public prototype_ `virtual void SendControllerEvents() = 0;` — Poll for controller state and send events if needed
- L49 _public function_ `virtual EInputDeviceThreadAffinity GetThreadAffinity() const` — Returns the thread affinity for this input device — which thread is permitted to call Tick() and SendControllerEvents(). Defaults to GameThreadOnly so existing devices require no changes. Override and return InputThreadSafe only if both methods are fully thread-safe (no game-thread-only APIs, no UObjects, no Slate calls).
- L52 _public prototype_ `virtual void SetMessageHandler( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler ) = 0;` — Set which MessageHandler will get the events from SendControllerEvents.
- L55 _public prototype_ `virtual bool Exec( UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar ) = 0;` — Exec handler to allow console commands to be passed through for debugging
- L60 _public prototype_ `virtual void SetChannelValue (int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) = 0;` — Force Feedback pass through functions
- L61 _public prototype_ `virtual void SetChannelValues (int32 ControllerId, const FForceFeedbackValues &values) = 0;`
- L62 _public function_ `virtual bool SupportsForceFeedback(int32 ControllerId)`
- L67 _public function_ `virtual void SetLightColor(int32 ControllerId, FColor Color)` — Pass though functions for light color
- L68 _public function_ `virtual void ResetLightColor(int32 ControllerId)`
- L77 _public function_ `virtual void SetDeviceProperty(int32 ControllerId, const FInputDeviceProperty* Property)` — Sets a property for a given controller id. Will be ignored for devices which don't support the property. @param ControllerId the id of the controller whose property is to be applied @param Property Base class pointer to property that will be applied
- L80 _public function_ `virtual class IHapticDevice* GetHapticDevice()` — If this device supports a haptic interface, implement this, and inherit the IHapticDevice interface
- L85 _public function_ `virtual bool IsGamepadAttached() const`

### `Source/Runtime/InputDevice/Public/IInputDeviceModule.h` (Public)


#### struct `FInputDeviceCreationParameters`  
`struct FInputDeviceCreationParameters`  
_L15-19_
- desc: Input parameters to device creation.
- L18 _public member_ `bool bInitAsPrimaryDevice = true;` — Indicates if this device is operating as a primary device and thus a part of game input system.

#### class `IInputDeviceModule`  
`class IInputDeviceModule : public IModuleInterface, public IModularFeature`  
_L24-114_
- inherits: `IModuleInterface,IModularFeature`
- desc: The public interface of the InputDeviceModule
- L27 _public function_ `static FName GetModularFeatureName()`
- L33 _public function_ `virtual void StartupModule() override`
- L43 _public function_ `static inline IInputDeviceModule& Get()` — Singleton-like access to IInputDeviceModule @return Returns IInputDeviceModule singleton instance, loading the module on demand if needed
- L53 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L63 _public function_ `TSharedPtr<IInputDevice> CreateInputDeviceIfPreferred(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)` — Calls the normal "CreateInputDevice" logic only if this input device module is preferred. Returns null if this device is not preferred
- L79 _public prototype_ `virtual TSharedPtr<IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) = 0;` — Attempts to create a new input device with the given message handler.  This version will eventually be deprecated and users should migrate to the new version with an additional parameters struct. @return	Interface to the new input device, if we were able to successfully create one
- L89 _public function_ `virtual TSharedPtr<IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler, FInputDeviceCreationParameters InParams)` — Attempts to create a new input device interface with the specified input device creation parameters. This override is for advanced use cases where users would like to create devices that are not a part of the input system. @return	Interface to the new input device, if we were able to successfully create one
- L110 _protected function_ `virtual const TCHAR* GetPreferredDeviceAPIString() const` — Override this function if you would like your IInputDeviceModule to support "Preferred Device API" settings. @return Name of the input API as it would appear in the list of preferred input API names in the user settings. If null, then this input device module will never be checked for if the user prefers it and will always be created.

### `Source/Runtime/InputDevice/Public/InputDevice.h` (Public)
_(no declarations extracted)_
