# Plugins / XInputDevice

- module root: `Plugins/Runtime/Windows/XInputDevice/Source/XInputDevice`
- headers: 2; symbols: 48
- symbol kinds: class=2, function=5, macro=2, member=26, prototype=12, struct=1
- PublicDependencyModuleNames: ApplicationCore, Core, Engine, InputDevice

### `Plugins/Runtime/Windows/XInputDevice/Source/XInputDevice/Private/XInputInterface.h` (Private)


#### class `XInputInterface`  
`class XInputInterface : public IInputDevice`  
_L24-169_
- inherits: `IInputDevice`
- desc: Interface class for XInput devices (xbox 360 controller)
- L28 _public prototype_ `static TSharedRef< XInputInterface > Create( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler, bool bShouldBePrimaryDevice );`
- L35 _public prototype_ `virtual void SendControllerEvents() override;` — Poll for controller state and send events if needed @param PathToJoystickCaptureWidget	The path to the joystick capture widget.  If invalid this function does not poll
- L37 _public prototype_ `virtual void SetMessageHandler( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler ) override;`
- L39 _public function_ `void SetNeedsControllerStateUpdate()`
- L49 _public prototype_ `virtual void SetChannelValue( int32 ControllerId, const FForceFeedbackChannelType ChannelType, const float Value ) override;` — Sets the strength/speed of the given channel for the given controller id. NOTE: If the channel is not supported, the call will silently fail @param ControllerId the id of the controller whose value is to be set @param ChannelType the type of channel whose value should be set @param Value strength or speed of feedback, 0.0f to 1.0f. 0.0f will disable
- L58 _public prototype_ `virtual void SetDeviceProperty(int32 ControllerId, const FInputDeviceProperty* Property) override;` — Sets a property for a given controller id. Will be ignored for devices which don't support the property. @param ControllerId the id of the controller whose property is to be applied @param Property Base class pointer to property that will be applied
- L67 _public prototype_ `virtual void SetChannelValues( int32 ControllerId, const FForceFeedbackValues& Values ) override;` — Sets the strength/speed of all the channels for the given controller id. NOTE: Unsupported channels are silently ignored @param ControllerId the id of the controller whose value is to be set @param Values strength or speed of feedback for all channels
- L69 _public function_ `virtual bool IsGamepadAttached() const override`
- L70 _public function_ `virtual void Tick( float DeltaTime ) override`
- L71 _public function_ `virtual bool Exec( UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar )`
- L74 _public function_ `virtual EInputDeviceThreadAffinity GetThreadAffinity() const override` — XInputGetState() is a stateless poll with no game-thread restrictions per Microsoft docs.
- L78 _private prototype_ `XInputInterface( const TSharedRef< FGenericApplicationMessageHandler >& MessageHandler, bool bShouldBePrimaryDevice );`
- L83 _private prototype_ `void GetPlatformUserAndDevice( int32 InControllerId, EInputDeviceConnectionState InDeviceState, FPlatformUserId& OutPlatformUserId, FInputDeviceId& OutDeviceId );` — Maps the given controller id to the platform user and device id. It will use the device mapper when used with the input system.
- L86 _private prototype_ `void SetDynamicTriggerThreshold(const int32 ControllerId, const EInputDeviceTriggerMask TriggerMask, const float Threshold);` — Sets dynamic trigger release threshold for the given trigger(s) on the given controller.
- L139 _private member_ `bool bNeedsControllerStateUpdate;` — If we've been notified by the system that the controller state may have changed
- L141 _private member_ `bool bIsGamepadAttached;`
- L144 _private member_ `bool bIsPrimaryDevice;` — Indicates if this device is operating as a primary device and thus part of game input system.
- L147 _private member_ `uint8 X360ToXboxControllerMapping[MAX_NUM_CONTROLLER_BUTTONS];` — In the engine, all controllers map to xbox controllers for consistency
- L150 _private member_ `FControllerState ControllerStates[MAX_NUM_XINPUT_CONTROLLERS];` — Controller states
- L153 _private member_ `float InitialButtonRepeatDelay;` — Delay before sending a repeat message after a button was first pressed
- L156 _private member_ `float ButtonRepeatDelay;` — Delay before sending a repeat message after a button has been pressed for a while
- L159 _private member_ `FGamepadKeyNames::Type Buttons[MAX_NUM_CONTROLLER_BUTTONS];` — Array of gamepad button names where the index in the array is the XInput button
- L162 _private member_ `TSharedRef<FGenericApplicationMessageHandler> MessageHandler;` — Reference to the message handler, used to send the input state to the application.
- L168 _private member_ `TInputDeviceMap<int32> InternalDeviceIdMappings;` — A map of XInput device identifiers (int32's) to their uniquely assigned FInputDeviceId from the engine.

#### struct `XInputInterface::FControllerState`  
`struct FControllerState`  
_L88-136_
- L91 _public member_ `bool ButtonStates[MAX_NUM_CONTROLLER_BUTTONS];` — Last frame's button states, so we only send events on edges
- L94 _public member_ `double NextRepeatTime[MAX_NUM_CONTROLLER_BUTTONS];` — Next time a repeat event should be generated for each button
- L97 _public member_ `int16 LeftXAnalog;` — Raw Left thumb x analog value
- L100 _public member_ `int16 LeftYAnalog;` — Raw left thumb y analog value
- L103 _public member_ `int16 RightXAnalog;` — Raw Right thumb x analog value
- L106 _public member_ `int16 RightYAnalog;` — Raw Right thumb x analog value
- L109 _public member_ `uint8 LeftTriggerAnalog;` — Left Trigger analog value
- L112 _public member_ `uint8 RightTriggerAnalog;` — Right trigger analog value
- L115 _public member_ `bool bIsConnected;` — If the controller is currently connected
- L118 _public member_ `int32 ControllerId;` — Id of the controller
- L121 _public member_ `FForceFeedbackValues ForceFeedback;` — Current force feedback values
- L123 _public member_ `float LastLargeValue;`
- L124 _public member_ `float LastSmallValue;`
- L129 _public member_ `FPlatformUserId LastUsedValidPlatformUserId;` — The last valid FPlatformUserId that can be used on the frame where the input device is disconnected
- L132 _public member_ `FDynamicReleaseDeadZone LeftTriggerReleaseDeadZone;` — Dynamic Release DeadZone for Left Trigger
- L135 _public member_ `FDynamicReleaseDeadZone RightTriggerReleaseDeadZone;` — Dynamic Release DeadZone for Right Trigger

#### Free symbols / members of external scopes

- L14 _macro_ `#define MAX_NUM_XINPUT_CONTROLLERS 4` — Max number of controllers.
- L17 _macro_ `#define MAX_NUM_CONTROLLER_BUTTONS 24` — Max number of controller buttons.  Must be < 256

### `Plugins/Runtime/Windows/XInputDevice/Source/XInputDevice/Public/XInputDeviceModule.h` (Public)


#### class `FXInputDeviceModule`  
`class FXInputDeviceModule final : public IInputDeviceModule`  
_L10-18_
- inherits: `IInputDeviceModule`
- desc: Input Device Module for XInput, an input API for Windows.
- L14 _public prototype_ `virtual TSharedPtr<IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;`
- L15 _public prototype_ `virtual TSharedPtr<IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler, FInputDeviceCreationParameters InParameters) override;`
- L16 _public prototype_ `virtual const TCHAR* GetPreferredDeviceAPIString() const override;`
