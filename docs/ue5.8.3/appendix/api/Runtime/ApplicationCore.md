# Runtime / ApplicationCore

- module root: `Source/Runtime/ApplicationCore`
- headers: 113; symbols: 3992
- symbol kinds: class=87, delegate=32, enum=66, enumerator=422, externvar=10, function=486, macro=53, member=1083, namespace=28, prototype=1530, struct=118, typedef=47, union=1, variable=29
- PrivateDependencyModuleNames: BackgroundHTTPFileHash, BackgroundHttpIOS, BuildSettings, CoreUObject, WindowsD3D
- PrivateIncludePathModuleNames: Analytics, ImageWrapper, InputDevice, Launch, Media, SynthBenchmark, VulkanRHI
- PublicDependencyModuleNames: Core
- PublicIncludePathModuleNames: BackgroundHTTP, RHI

### `Source/Runtime/ApplicationCore/Internal/GenericPlatform/CursorUtils.h` (Internal)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Cursor` (scope `UE`)
- L10 _prototype_ `float CalculateDeltaWithAcceleration(int32 Delta, float Sensitivity);` (scope `UE::Cursor`)

### `Source/Runtime/ApplicationCore/Internal/Windows/WindowsRedistributableValidation.h` (Internal)


#### struct `VersionInfo`  
`struct VersionInfo`  
_L8-36_
- desc: Visual C++ redistributable version information.
- L10 _public prototype_ `constexpr VersionInfo() = default;`
- L12 _public function_ `constexpr VersionInfo(unsigned long InMajor, unsigned long InMinor, unsigned long InBld, unsigned long InRbld) : Major(InMajor) , Minor(InMinor) , Bld(InBld) , Rbld(InRbld)`
- L19 _public function_ `constexpr VersionInfo(unsigned long long InVersion) : Major((InVersion >> 48) & 0xffff) , Minor((InVersion >> 32) & 0xffff) , Bld((InVersion >> 16) & 0xffff) , Rbld((InVersion >> 0) & 0xffff)`
- L27 _public function_ `inline bool IsSet() const` — Set if any version number is non-zero.
- L32 _public member_ `unsigned long Major = 0;`
- L33 _public member_ `unsigned long Minor = 0;`
- L34 _public member_ `unsigned long Bld = 0;`
- L35 _public member_ `unsigned long Rbld = 0;`

#### Free symbols / members of external scopes

- L40 _variable_ `inline constexpr VersionInfo MinRedistVersion = { 14, 50, 35719, 0 };` — This minimum should match the version installed by Engine/Extras/Redist/en-us/vc_redist.x64.exe
- L42 _variable_ `inline constexpr VersionInfo MinGameInputRedistVersion = { 3, 1, 26100, 6879 };`
- L45 _function_ `inline bool IsVersionValid(const VersionInfo& Version, const VersionInfo& MinVersion)` — Valid if the specified version is greater or equal than the minimum version.

### `Source/Runtime/ApplicationCore/Private/Apple/AppleControllerInterface.h` (Private)


#### enum `ControllerType`  
`enum ControllerType`  
_L22-30_
- L24 _public enumerator_ `Unassigned`
- L25 _public enumerator_ `SiriRemote`
- L26 _public enumerator_ `ExtendedGamepad`
- L27 _public enumerator_ `XboxGamepad`
- L28 _public enumerator_ `DualShockGamepad`
- L29 _public enumerator_ `DualSenseGamepad`

#### enum `PlayerIndex`  
`enum PlayerIndex`  
_L32-40_
- L34 _public enumerator_ `PlayerOne`
- L35 _public enumerator_ `PlayerTwo`
- L36 _public enumerator_ `PlayerThree`
- L37 _public enumerator_ `PlayerFour`
- L39 _public enumerator_ `PlayerUnset = -1`

#### enum `EAppleControllerEventType`  
`enum class EAppleControllerEventType : int32`  
_L42-48_
- L44 _public enumerator_ `Invalid`
- L45 _public enumerator_ `Connect`
- L46 _public enumerator_ `Disconnect`
- L47 _public enumerator_ `BecomeCurrent`

#### struct `FDeferredAppleControllerEvent`  
`struct FDeferredAppleControllerEvent`  
_L50-67_
- L52 _public function_ `FDeferredAppleControllerEvent(EAppleControllerEventType InEventType, GCController* InController) : EventType(InEventType) , Controller([InController retain])`
- L56 _public function_ `FDeferredAppleControllerEvent(const FDeferredAppleControllerEvent& Other)`
- L61 _public function_ `~FDeferredAppleControllerEvent()`
- L65 _public member_ `EAppleControllerEventType EventType;`
- L66 _public member_ `GCController* Controller;`

#### class `FAppleControllerInterface`  
`class FAppleControllerInterface : public IInputInterface`  
_L72-205_
- inherits: `IInputInterface`
- desc: Interface class for Apple Controllers
- L76 _public prototype_ `static TSharedRef< FAppleControllerInterface > Create( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler );`
- L77 _public prototype_ `static TSharedPtr< FAppleControllerInterface > Get();`
- L81 _public function_ `virtual ~FAppleControllerInterface()`
- L83 _public prototype_ `virtual void SetMessageHandler( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler );`
- L86 _public prototype_ `void Tick( float DeltaTime );` — Tick the interface (i.e check for new controllers)
- L91 _public prototype_ `void SendControllerEvents();` — Poll for controller state and send events if needed
- L96 _public prototype_ `virtual void SetForceFeedbackChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;` — Force Feedback / haptics / lightbar / adaptive trigger implementation routed through GameController and CoreHaptics.
- L97 _public prototype_ `virtual void SetForceFeedbackChannelValues(int32 ControllerId, const FForceFeedbackValues &Values) override;`
- L98 _public prototype_ `virtual void SetLightColor(int32 ControllerId, FColor Color) override;`
- L99 _public prototype_ `virtual void ResetLightColor(int32 ControllerId) override;`
- L100 _public prototype_ `virtual void SetDeviceProperty(int32 ControllerId, const FInputDeviceProperty* Property) override;`
- L103 _public prototype_ `bool ControllerHasHaptics(int32 ControllerId) const;` — Returns true when the controller bound to ControllerId exposes a non-nil GCDeviceHaptics.
- L105 _public prototype_ `bool IsControllerAssignedToGamepad(int32 ControllerId) const;`
- L106 _public prototype_ `bool IsGamepadAttached() const;`
- L108 _public prototype_ `const ControllerType GetControllerType(uint32 ControllerIndex);`
- L109 _public prototype_ `void SetControllerType(uint32 ControllerIndex);`
- L110 _public prototype_ `FName GetControllerTypeName(const ControllerType InControllerType);`
- L112 _public prototype_ `GCControllerButtonInput* GetGCControllerButton(const FGamepadKeyNames::Type& ButtonKey, uint32 ControllerIndex);`
- L114 _public prototype_ `void HandleInputInternal(const FGamepadKeyNames::Type& UEButton, uint32 ControllerIndex, bool bIsPressed, bool bWasPressed);`
- L115 _public prototype_ `void HandleButtonGamepad(const FGamepadKeyNames::Type& UEButton, uint32 ControllerIndex);`
- L116 _public prototype_ `void HandleAnalogGamepad(const FGamepadKeyNames::Type& UEAxis, uint32 ControllerIndex);`
- L117 _public prototype_ `void HandleVirtualButtonGamepad(const FGamepadKeyNames::Type& UEButtonNegative, const FGamepadKeyNames::Type& UEButtonPositive, uint32 ControllerIndex);`
- L121 _protected prototype_ `FAppleControllerInterface( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler );`
- L123 _protected prototype_ `void SignalEvent(EAppleControllerEventType InEventType, GCController* InController);`
- L129 _private prototype_ `void HandleConnection(GCController* Controller);`
- L130 _private prototype_ `void HandleDisconnect(GCController* Controller);`
- L132 _private prototype_ `void SetCurrentController(GCController* Controller);`
- L134 _private prototype_ `void CaptureControllerState(const GCController* Controller, uint32 ControllerIndex);`
- L136 _private prototype_ `void InitializeHapticsForController(FUserController& UserController);`
- L137 _private prototype_ `void TearDownHapticsForController(FUserController& UserController);`
- L138 _private prototype_ `void ApplyForceFeedbackValues(FUserController& UserController, const FForceFeedbackValues& Values);`
- L142 _protected member_ `TSharedRef< FGenericApplicationMessageHandler > MessageHandler;`
- L187 _protected member_ `FCriticalSection DeferredEventCS;` — Controller Event Callbacks are on the main thread - defer to tick processing
- L188 _protected member_ `TArray<FDeferredAppleControllerEvent> DeferredEvents;`
- L191 _protected member_ `FUserController Controllers[MAX_NUM_CONTROLLERS];` — there is a hardcoded limit of 4 controllers in the API
- L193 _protected member_ `uint32 CurrentButtonIndex = 0;`
- L194 _protected member_ `uint32 PrevButtonIndex = 1;`
- L197 _protected member_ `TMap<FName, FControllerButton> ControllerButtons[MAX_CONTROLLER_CAPTURE_STATES][MAX_NUM_CONTROLLERS];` — We track 2 sets of buttons - the current state and the previous state And there is a hardcoded limit of 4 controllers in the API
- L199 _protected member_ `TMap<FName, double> NextKeyRepeatTime;`
- L202 _protected member_ `bool bAllowControllers;` — should we allow controllers to send input
- L204 _protected member_ `static FString HardwareDeviceIdentifier_DefaultGamepad;`

#### struct `FAppleControllerInterface::FUserController`  
`struct FUserController`  
_L145-169_
- desc: Game controller objects (per user)
- L147 _public member_ `GCController* Controller;`
- L148 _public member_ `ControllerType ControllerType;`
- L149 _public member_ `PlayerIndex PlayerIndex;`
- L153 _public member_ `CHHapticEngine* EngineHandlesLeft;` — CoreHaptics state — lazily initialized on first SetForceFeedback* call when the controller exposes a non-nil GCController.haptics. All fields start nil/zeroed via FMemory::Memzero on connect/disconnect;
- L154 _public member_ `CHHapticEngine* EngineHandlesRight;`
- L155 _public member_ `id<CHHapticPatternPlayer> PlayerHandlesLeft;`
- L156 _public member_ `id<CHHapticPatternPlayer> PlayerHandlesRight;`
- L157 _public member_ `bool bHapticsInitialized;`
- L158 _public member_ `bool bHapticsInitFailed;`
- L159 _public member_ `bool bSplitHandleLocalities;`
- L160 _public member_ `bool bHapticsPlayersStarted;` — true while at least one player is in the running state
- L161 _public member_ `FForceFeedbackValues LastForceFeedbackValues;`
- L162 _public member_ `FColor DefaultLightColor;` — captured at connect time, used by ResetLightColor
- L165 _public member_ `FQuat ReferenceAttitude;`
- L166 _public member_ `bool bNeedsReferenceAttitude;`
- L167 _public member_ `bool bHasReferenceAttitude;`

#### struct `FAppleControllerInterface::FControllerButton`  
`struct FControllerButton`  
_L172-184_
- desc: Track individual buttons and axis values
- L174 _public member_ `bool bPressed = false;`
- L175 _public member_ `float PressedValue = 0;` — the level of pressure being applied to the button
- L176 _public member_ `float AxisValue = 0;`
- L178 _public function_ `void Reset()`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAppleController, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAppleController, Log, All);`
- L19 _macro_ `#define MAX_NUM_CONTROLLERS 4 // reasonable limit for now`
- L20 _macro_ `#define MAX_CONTROLLER_CAPTURE_STATES 2 // track current and previous button states`

### `Source/Runtime/ApplicationCore/Private/Apple/AppleKeyboardController.h` (Private)


#### class `FAppleKeyboardController`  
`class FAppleKeyboardController`  
_L22-221_
- desc: Class that intercepts, queues and forwards keyboard events from GCKeyboard to UE's input system
- L39 _public prototype_ `explicit FAppleKeyboardController(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler, EInitFlags InitFlags = EInitFlags::None);`
- L40 _public prototype_ `~FAppleKeyboardController();`
- L46 _public prototype_ `void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);` — Sets the message handler to which any input even will be forwarded to @param InMessageHandler New Message handler instance
- L49 _public prototype_ `void SendControllerEvents();` — Process and dispatches all queued key events to UE's input system
- L52 _public prototype_ `FModifierKeysState GetModifierKeys() const;` — Returns the current state of all modifier keys
- L54 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(uint32, FKeyCodeTranslator, uint32);`
- L60 _public prototype_ `void SetGCKeyCodeToCharTranslator(const FKeyCodeTranslator& InExternalTranslatorDelegate);` — Sets an external callback that will perform any key code translation from GC Keycodes to an ASCII character if needed. @param InExternalTranslatorDelegate Callback that performs the transaltion
- L66 _public prototype_ `void SetGCKeyCodeToPlatformCodeTranslator(const FKeyCodeTranslator& InExternalTranslatorDelegate);` — Sets an external callback that will perform any key code translation from GC Keycodes to other keycode format if needed @param InExternalTranslatorDelegate Callback that performs the transaltion
- L71 _public prototype_ `void ForceUpdatePressedKeysState();` — Sets a flag to make sure in the next update look any currently key tracked as being pressed, re-queries the pressed state from the GCKeyboard API
- L77 _public prototype_ `void SetInhibited(bool bNewIsInhibited);` — If set to true, keyboard input will be ignored @param bNewIsInhibited new inhibited state
- L80 _public function_ `bool IsInhibited() const` — Returns true if we are ignoring keyboard inputs
- L86 _public prototype_ `bool IsAnyKeyboardConnected() const;` — Returns true if any physical keyboard is connected
- L88 _public function_ `DECLARE_MULTICAST_DELEGATE(FKeyboardAvailabilityChanged) FKeyboardAvailabilityChanged& OnAvailabilityChanged()`
- L123 _public prototype_ `void QueueExternalKeyChangeEvent(const FDeferredEvent& InExternalKeyEvent);` — Queues a key event built externally  to be dispatched in the game thread @param Event to queue
- L129 _public prototype_ `void QueueOneOffExternalKeyEvent(const FDeferredEvent& InExternalKeyEvent);` — Queues a key event built externally to be dispatched in the game thread. The event will be transformed in its respective key up and key down events, to act as a one off key event @param Event to queue
- L135 _public prototype_ `bool IsPrintableChar(TCHAR InChar) const;` — Evaluates a character to see if it is a printable character (ASCII or Unicode) @return true if the character is printable
- L150 _public prototype_ `FRIEND_ENUM_CLASS_FLAGS(EModifierKeyFlags);`
- L157 _public prototype_ `void IncreaseModifierKeyMapAllocation(int32 ElementCount);` — Increases the memory allocation of the modifier keys map container by the specified number of elements. Use this if you expect to a known elements of mappings in a row @param ElementCount Number of elements you need room for
- L164 _public prototype_ `void AddModifierKeyMapping(uint32 KeyCode, EModifierKeyFlags ModifierFlag);` — Maps a specific key code to a key modifier flag @param KeyCode Key code to map @param ModifierFlag Modifier flag to map
- L168 _protected member_ `EInitFlags InitializationFlags;`
- L170 _protected member_ `FKeyboardAvailabilityChanged AvailabilityChangedDelegate;`
- L172 _protected member_ `FKeyCodeTranslator KeyCodeToPlatformCodeTranslator;`
- L173 _protected member_ `FKeyCodeTranslator KeyCodeToCharTranslator;`
- L175 _protected member_ `TSharedRef<FGenericApplicationMessageHandler> MessageHandler;`
- L191 _protected prototype_ `void RegisterGCKeyboardModifierKeyMappings();`
- L193 _protected prototype_ `void HandleKeyboardConnected();`
- L194 _protected prototype_ `void HandleKeyboardDisconnected();`
- L195 _protected prototype_ `void HandleKeyChangeEvent(GCKeyCode keyCode, BOOL pressed);`
- L197 _protected prototype_ `EKeyEvent GetUpdatedKeyStateForKey(const FDeferredEvent& InDeferredEvent);`
- L199 _protected prototype_ `void ProcessModifierKeyEvent(const FDeferredEvent& InDeferredEvent);`
- L200 _protected prototype_ `void DispatchEvent(const FDeferredEvent& InDeferredEvent);`
- L201 _protected prototype_ `void UpdateAndDispatchRepeatEvents();`
- L202 _protected prototype_ `void UpdateEventTracking(const FDeferredEvent& InDeferredEvent, double CurrentTime);`
- L204 _protected member_ `FInternalModifierKeyState CurrentModifierKeys;`
- L206 _protected member_ `bool bHandledKeyboardConnection = false;`
- L208 _protected member_ `TMap<uint32, FDeferredEvent> CurrentlyPressedKeyStates;`
- L210 _protected member_ `TSpscQueue<FDeferredEvent> DeferredKeyEvents;`
- L212 _protected member_ `std::atomic<bool> bNeedUpdatePressedKeyState = false;`
- L213 _protected member_ `std::atomic<bool> bIsKeyboardInhibited = false;`
- L215 _protected member_ `bool bIsInitialized = false;`
- L217 _protected member_ `id ConnectedEventObserverID = nil;`
- L218 _protected member_ `id DisconnectedEventObserverID = nil;`
- L220 _protected member_ `TMap<uint32, EModifierKeyFlags> ModifierKeysKeymap;`

#### enum `FAppleKeyboardController::EInitFlags`  
`enum class EInitFlags : uint8`  
_L27-35_
- desc: Set of flags used to determine how keyboard input events are handled
- L30 _public enumerator_ `None = 0` — Default option where the internal GC Keyboard key change handler will be initialized
- L34 _public enumerator_ `GCKeyboardKeyHandlerDisabled = 1 << 0` — If set, the GC keyboard Key Change handler will not be initialized, and this controller will only work with external input events. GC Keyboard will still be used to report if a physical keyboard is connected or not

#### enum `FAppleKeyboardController::EKeyEvent`  
`enum class EKeyEvent : uint8`  
_L99-104_
- desc: Type of key events
- L101 _public enumerator_ `Invalid`
- L102 _public enumerator_ `KeyUp`
- L103 _public enumerator_ `KeyDown`

#### struct `FAppleKeyboardController::FDeferredEvent`  
`struct FDeferredEvent`  
_L109-117_
- desc: Structure containing information about a key event that will be dispatched in the game thread
- L111 _public member_ `EKeyEvent KeyEventType = EKeyEvent::Invalid;`
- L112 _public member_ `TOptional<uint32> GCKeyCode;`
- L113 _public member_ `uint32 TranslatedKeyCode = 0;`
- L114 _public member_ `uint32 CharCode = 0;`
- L115 _public member_ `bool bIsRepeat = false;`
- L116 _public member_ `double LastRepeatTime = 0.0;`

#### enum `FAppleKeyboardController::EModifierKeyFlags`  
`enum class EModifierKeyFlags : uint16`  
_L137-149_
- L139 _public enumerator_ `None = 0`
- L140 _public enumerator_ `LeftShiftDown = 1 << 0`
- L141 _public enumerator_ `RightShiftDown = 1 << 1`
- L142 _public enumerator_ `LeftControlDown = 1 << 2`
- L143 _public enumerator_ `RightControlDown = 1 << 3`
- L144 _public enumerator_ `LeftAltDown = 1 << 4`
- L145 _public enumerator_ `RightAltDown = 1 << 5`
- L146 _public enumerator_ `LeftCommandDown = 1 << 6`
- L147 _public enumerator_ `RightCommandDown = 1 << 7`
- L148 _public enumerator_ `CapsLocked = 1 << 8`

#### struct `FAppleKeyboardController::FInternalModifierKeyState`  
`struct FInternalModifierKeyState`  
_L177-189_
- L179 _public member_ `EModifierKeyFlags ModifierFlags = EModifierKeyFlags::None;`
- L181 _public function_ `FModifierKeysState ToUEModifierKeyStates() const`

#### Free symbols / members of external scopes

- L54 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(uint32, FKeyCodeTranslator, uint32);`
- L88 _delegate_ `DECLARE_MULTICAST_DELEGATE(FKeyboardAvailabilityChanged) FKeyboardAvailabilityChanged& OnAvailabilityChanged() { return AvailabilityChangedDelegate; } enum class EKeyEvent : uint8 { Invalid, KeyUp, KeyDown };`

### `Source/Runtime/ApplicationCore/Private/Apple/AppleMouseController.h` (Private)


#### enum `EMouseControllerCapabilities`  
`enum class EMouseControllerCapabilities : uint8`  
_L19-26_
- desc: Controls which GCMouse handlers FAppleMouseController binds
- L21 _public enumerator_ `None = 0`
- L22 _public enumerator_ `Movement = 1 << 0`
- L23 _public enumerator_ `Scroll = 1 << 1`
- L24 _public enumerator_ `Buttons = 1 << 2`
- L25 _public enumerator_ `All = Movement | Scroll | Buttons`

#### class `FAppleMouseController`  
`class FAppleMouseController`  
_L32-136_
- desc: Class that intercepts, queues and dispatches GCMouse events to UE's input system
- L35 _public prototype_ `explicit FAppleMouseController(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler, EMouseControllerCapabilities InCapabilities = EMouseControllerCapabilities::All);`
- L37 _public prototype_ `~FAppleMouseController();`
- L43 _public prototype_ `void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);` — Sets the message handler to which any input even will be forwarded to @param InMessageHandler New Message handler instance
- L46 _public prototype_ `void SendControllerEvents();` — Process and dispatches all queued key events to UE's input system
- L53 _public prototype_ `void SetEnabled(bool bInEnabled);` — Enables or disables mouse event accumulation and dispatch. Used it to in practice disable this controller, but keeping it initialized @param bInEnabled new enabled state
- L56 _public prototype_ `bool IsEnabled() const;` — Returns true if event accumulation and dispatch are active
- L58 _public prototype_ `bool IsAnyMouseConnected() const;`
- L62 _public prototype_ `void RebindMouseHandlers();` — Re-enumerate connected mice and re-bind GCMouse handlers. Call after macOS state transitions (sleep, minimize) that may silently invalidate existing handlers.
- L66 _public prototype_ `void SuspendMovementHandler();` — Nil out the GCMouse movement handler on all connected mice so macOS routes mouse deltas back through NSEvent. Call from ReassociateMouseInput.
- L68 _public function_ `DECLARE_MULTICAST_DELEGATE(FAvailabilityChanged) FAvailabilityChanged& OnAvailabilityChanged()`
- L78 _public function_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMouseMovementDispatched, FIntVector2) FMouseMovementDispatched& OnMovementDispatched()`
- L90 _protected member_ `FAvailabilityChanged AvailabilityChangedDelegate;`
- L91 _protected member_ `FMouseMovementDispatched MovementDispatchedDelegate;`
- L106 _protected prototype_ `void DispatchMovementUpdates();`
- L107 _protected prototype_ `void DispatchKeyUpdates();`
- L108 _protected prototype_ `void DispatchKeyUpdate(const FDeferredKeyEvent& Event);`
- L110 _protected prototype_ `void HandleMouseConnected(GCMouse* Mouse);`
- L111 _protected prototype_ `void HandleMouseDisconnected();`
- L112 _protected prototype_ `void HandleKeyEvent(bool bIsPressed, EMouseButtons::Type Button);`
- L124 _protected member_ `FMouseMovementState CurrentMovementState;`
- L126 _protected member_ `TSpscQueue<FDeferredKeyEvent> DeferredKeyEvents;`
- L127 _protected member_ `TSharedRef<FGenericApplicationMessageHandler> MessageHandler;`
- L128 _protected member_ `EMouseControllerCapabilities EnabledCapabilities;`
- L130 _protected member_ `bool bIsInitialized = false;`
- L131 _protected member_ `std::atomic<bool> bEnabled = true;`
- L132 _protected member_ `std::atomic<bool> bNeedFlushPendingState = false;`
- L134 _protected member_ `id ConnectedEventObserverID = nil;`
- L135 _protected member_ `id DisconnectedEventObserverID = nil;`

#### enum `FAppleMouseController::EKeyEventType`  
`enum class EKeyEventType`  
_L93-98_
- L95 _public enumerator_ `Invalid`
- L96 _public enumerator_ `Up`
- L97 _public enumerator_ `Down`

#### struct `FAppleMouseController::FDeferredKeyEvent`  
`struct FDeferredKeyEvent`  
_L100-104_
- L102 _public member_ `EKeyEventType Type = EKeyEventType::Invalid;`
- L103 _public member_ `EMouseButtons::Type ButtonID;`

#### struct `FAppleMouseController::FMouseMovementState`  
`struct FMouseMovementState`  
_L114-122_
- L116 _public member_ `std::atomic<float> MouseDeltaX = 0.0f;`
- L117 _public member_ `std::atomic<float> MouseDeltaY = 0.0f;`
- L118 _public member_ `std::atomic<float> ScrollDelta = 0.0f;`
- L121 _public member_ `FVector2D PendingDeltaXY = FVector2D::ZeroVector;` — The UE API only takes integer values. This property accumulates fractional delta (if any) to be consumed in the next iteration

#### Free symbols / members of external scopes

- L68 _delegate_ `DECLARE_MULTICAST_DELEGATE(FAvailabilityChanged) FAvailabilityChanged& OnAvailabilityChanged() { return AvailabilityChangedDelegate; } DECLARE_MULTICAST_DELEGATE_OneParam(FMouseMovementDispatched, FIntVector2) FMouseMovementDispatched& OnMovementDispatched() { return MovementDispatchedDelegate; } protected: FAvailabilityChanged AvailabilityChangedDelegate;`
- L78 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMouseMovementDispatched, FIntVector2) FMouseMovementDispatched& OnMovementDispatched() { return MovementDispatchedDelegate; } protected: FAvailabilityChanged AvailabilityChangedDelegate;`

### `Source/Runtime/ApplicationCore/Private/Mac/HIDInputInterface.h` (Private)


#### class `HIDInputInterface`  
`class HIDInputInterface`  
_L17-126_
- desc: Interface class for HID Input devices
- L21 _public prototype_ `static TSharedRef<HIDInputInterface> Create(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);`
- L23 _public prototype_ `void SendControllerEvents();`
- L25 _public function_ `void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)`
- L30 _public function_ `bool IsGamepadAttached() const`
- L34 _private prototype_ `HIDInputInterface(const TSharedRef<FGenericApplicationMessageHandler>& MessageHandler);`
- L36 _private prototype_ `void OnNewHIDController(IOReturn Result, IOHIDDeviceRef DeviceRef);`
- L38 _private prototype_ `static CFMutableDictionaryRef CreateDeviceMatchingDictionary(UInt32 UsagePage, UInt32 Usage);`
- L39 _private prototype_ `static void HIDDeviceMatchingCallback(void* Context, IOReturn Result, void* Sender, IOHIDDeviceRef DeviceRef);`
- L40 _private prototype_ `static void HIDDeviceRemovalCallback(void* Context, IOReturn Result, void* Sender, IOHIDDeviceRef DeviceRef);`
- L110 _private member_ `FGamepadKeyNames::Type Buttons[MAX_NUM_CONTROLLER_BUTTONS];` — Names of all the buttons
- L113 _private member_ `FControllerState ControllerStates[MAX_NUM_HIDINPUT_CONTROLLERS];` — Controller states
- L116 _private member_ `float InitialButtonRepeatDelay;` — Delay before sending a repeat message after a button was first pressed
- L119 _private member_ `float ButtonRepeatDelay;` — Delay before sendign a repeat message after a button has been pressed for a while
- L121 _private member_ `bool bIsGamepadAttached;`
- L123 _private member_ `IOHIDManagerRef HIDManager;`
- L125 _private member_ `TSharedRef<FGenericApplicationMessageHandler> MessageHandler;`

#### struct `HIDInputInterface::FHIDElementInfo`  
`struct FHIDElementInfo`  
_L44-52_
- L46 _public member_ `IOHIDElementRef ElementRef;`
- L47 _public member_ `IOHIDElementType Type;`
- L48 _public member_ `uint32 UsagePage;`
- L49 _public member_ `uint32 Usage;`
- L50 _public member_ `int32 MinValue;`
- L51 _public member_ `int32 MaxValue;`

#### struct `HIDInputInterface::FHIDDeviceInfo`  
`struct FHIDDeviceInfo`  
_L54-67_
- L56 _public member_ `IOHIDDeviceRef DeviceRef;`
- L57 _public member_ `TArray<FHIDElementInfo> Elements;`
- L58 _public member_ `int8 ButtonsMapping[MAX_NUM_CONTROLLER_BUTTONS];`
- L59 _public member_ `uint16 LeftAnalogXMapping;`
- L60 _public member_ `uint16 LeftAnalogYMapping;`
- L61 _public member_ `uint16 LeftTriggerAnalogMapping;`
- L62 _public member_ `uint16 RightAnalogXMapping;`
- L63 _public member_ `uint16 RightAnalogYMapping;`
- L64 _public member_ `uint16 RightTriggerAnalogMapping;`
- L66 _public prototype_ `void SetupMappings();`

#### struct `HIDInputInterface::FXBox360ControllerID`  
`struct FXBox360ControllerID`  
_L69-73_
- L71 _public member_ `const int32 VendorID;`
- L72 _public member_ `const int32 ProductID;`

#### struct `HIDInputInterface::FControllerState`  
`struct FControllerState`  
_L75-105_
- L78 _public member_ `bool ButtonStates[MAX_NUM_CONTROLLER_BUTTONS];` — Last frame's button states, so we only send events on edges
- L81 _public member_ `double NextRepeatTime[MAX_NUM_CONTROLLER_BUTTONS];` — Next time a repeat event should be generated for each button
- L84 _public member_ `int32 LeftAnalogX;` — Raw Left thumb x analog value
- L87 _public member_ `int32 LeftAnalogY;` — Raw left thumb y analog value
- L90 _public member_ `int32 RightAnalogX;` — Raw Right thumb x analog value
- L93 _public member_ `int32 RightAnalogY;` — Raw Right thumb x analog value
- L96 _public member_ `int32 LeftTriggerAnalog;` — Left Trigger analog value
- L99 _public member_ `int32 RightTriggerAnalog;` — Right trigger analog value
- L102 _public member_ `int32 ControllerId;` — Id of the controller
- L104 _public member_ `FHIDDeviceInfo Device;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define MAX_NUM_HIDINPUT_CONTROLLERS 4`
- L12 _macro_ `#define MAX_NUM_CONTROLLER_BUTTONS 24` — Max number of controller buttons.  Must be < 256

### `Source/Runtime/ApplicationCore/Public/Android/AndroidApplication.h` (Public)


#### class `FAndroidApplication`  
`class FAndroidApplication : public GenericApplication`  
_L29-139_
- inherits: `GenericApplication`
- L33 _public prototype_ `static FAndroidApplication* CreateAndroidApplication();`
- L37 _public function_ `static inline void InitializeJavaEnv(JavaVM* VM, jint Version, jobject GlobalThis)` — `UE_DEPRECATED(5.7, "Use InitializeJavaEnv() instead.")`
- L41 _public function_ `static FORCEINLINE void InitializeJavaEnv()`
- L45 _public function_ `static inline jobject GetGameActivityThis()`
- L49 _public function_ `static inline jobject GetClassLoader()`
- L53 _public function_ `static inline JNIEnv* GetJavaEnv(bool bRequireGlobalThis = true)`
- L57 _public function_ `static inline jclass FindJavaClass(const char* name)`
- L61 _public function_ `static inline jclass FindJavaClassGlobalRef(const char* name)`
- L66 _public function_ `static inline void DetachJavaEnv()` — `UE_DEPRECATED(5.7, "Don't call this.")`
- L70 _public function_ `static inline bool CheckJavaException()`
- L76 _public function_ `static FAndroidApplication* Get()`
- L82 _public prototype_ `void SetMessageHandler( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler );`
- L84 _public prototype_ `virtual void PollGameDeviceState( const float TimeDelta ) override;`
- L86 _public prototype_ `virtual FPlatformRect GetWorkArea( const FPlatformRect& CurrentWindow ) const override;`
- L88 _public prototype_ `virtual IInputInterface* GetInputInterface() override;`
- L90 _public prototype_ `virtual TSharedRef< FGenericWindow > MakeWindow() override;`
- L92 _public prototype_ `virtual void AddExternalInputDevice(TSharedPtr<class IInputDevice> InputDevice);`
- L94 _public prototype_ `void InitializeWindow( const TSharedRef< FGenericWindow >& InWindow, const TSharedRef< FGenericWindowDefinition >& InDefinition, const TSharedPtr< FGenericWindow >& InParent, const bool bShowImmediately );`
- L96 _public prototype_ `static void OnWindowSizeChanged();`
- L98 _public prototype_ `virtual void Tick(const float TimeDelta) override;`
- L100 _public prototype_ `virtual bool IsGamepadAttached() const override;`
- L102 _public prototype_ `bool GetNativeWindowResolution(int32_t& OutWidth, int32_t& OutHeight) const;`
- L104 _public prototype_ `virtual TSharedPtr<FGenericWindow> GetWindowUnderCursor() override;`
- L107 _public prototype_ `void SetCurrentlyTouchedWindow(TSharedPtr<FGenericWindow> InWindow);` — Game thread only; the touch loop brackets each OnTouch* call with set / clear.
- L110 _public prototype_ `TSharedPtr<FAndroidWindow> GetPrimaryWindow() const;` — Returns the primary (first-created) Android window, or nullptr if none has been added yet.
- L112 _public member_ `static TAutoConsoleVariable<bool> CVarAndroidSupportsTimestampQueries;`
- L113 _public member_ `static TAutoConsoleVariable<bool> CVarAndroidSupportsDynamicResolution;`
- L117 _protected prototype_ `FAndroidApplication();`
- L118 _protected prototype_ `FAndroidApplication(TSharedPtr<class FAndroidInputInterface> InInputInterface);`
- L123 _private prototype_ `void OnInputDeviceModuleRegistered(const FName& Type, IModularFeature* ModularFeature);`
- L125 _private member_ `TSharedPtr< class FAndroidInputInterface > InputInterface;`
- L126 _private member_ `bool bHasLoadedInputPlugins;`
- L129 _private member_ `TSharedPtr<FGenericWindow> CurrentlyTouchedWindow;` — See GetWindowUnderCursor. Game thread only.
- L131 _private member_ `TArray< TSharedRef< FAndroidWindow > > Windows;`
- L133 _private member_ `static bool bWindowSizeChanged;`
- L135 _private member_ `static FAndroidApplication* _application;`
- L137 _private member_ `EDeviceScreenOrientation DeviceOrientation;`
- L138 _private prototype_ `void HandleDeviceOrientation();`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace FAndroidAppEntry`
- L16 _prototype_ `void PlatformInit();` (scope `FAndroidAppEntry`)
- L19 _prototype_ `void ReInitWindow(const TOptional<FAndroidWindow::FNativeAccessor>& WindowContainer);` (scope `FAndroidAppEntry`) — if the native window handle has changed then the new handle is required.
- L21 _prototype_ `void ReleaseEGL();` (scope `FAndroidAppEntry`)
- L22 _prototype_ `void OnPauseEvent();` (scope `FAndroidAppEntry`)

### `Source/Runtime/ApplicationCore/Public/Android/AndroidCursor.h` (Public)


#### class `FAndroidCursor`  
`class FAndroidCursor : public ICursor`  
_L8-45_
- inherits: `ICursor`
- L12 _public prototype_ `FAndroidCursor();`
- L14 _public prototype_ `virtual ~FAndroidCursor() = default;`
- L16 _public function_ `virtual FVector2D GetPosition() const override`
- L21 _public prototype_ `virtual void SetPosition(const int32 X, const int32 Y) override;`
- L23 _public prototype_ `virtual void SetType(const EMouseCursor::Type InNewCursor) override;`
- L25 _public function_ `virtual EMouseCursor::Type GetType() const override`
- L30 _public prototype_ `virtual void GetSize(int32& Width, int32& Height) const override;`
- L32 _public prototype_ `virtual void Show(bool bInShow) override;`
- L34 _public prototype_ `virtual void Lock(const RECT* const Bounds) override;`
- L36 _public function_ `virtual void SetTypeShape(EMouseCursor::Type InCursorType, void* CursorHandle) override`
- L39 _private prototype_ `bool UpdateCursorClipping(FVector2D& CursorPosition);`
- L41 _private member_ `EMouseCursor::Type CurrentType;`
- L42 _private member_ `FVector2D CurrentPosition;`
- L43 _private member_ `FIntRect CursorClipRect;`
- L44 _private member_ `bool bShow;`

### `Source/Runtime/ApplicationCore/Public/Android/AndroidFeedbackContext.h` (Public)


#### class `FAndroidFeedbackContext`  
`class FAndroidFeedbackContext : public FFeedbackContext`  
_L9-11_
- inherits: `FFeedbackContext`

### `Source/Runtime/ApplicationCore/Public/Android/AndroidGameControllerMapper.h` (Public)


#### enum `GameControllerMapping::ControllerClassType`  
`enum ControllerClassType : int`  
_L14-25_
- L16 _public enumerator_ `Generic`
- L17 _public enumerator_ `XBoxWired`
- L18 _public enumerator_ `XBoxWireless`
- L19 _public enumerator_ `PlaystationWireless`
- L21 _public enumerator_ `XBoxWired_AndroidAPIBefore31`
- L22 _public enumerator_ `XBoxWireless_OlderFirmware`
- L23 _public enumerator_ `PS4Wireless_AndroidAPIBefore10_CPUNotSony`
- L24 _public enumerator_ `PS5Wireless_AndroidAPIBefore31`

#### enum `GameControllerMapping::ButtonRemapType`  
`enum ButtonRemapType : int`  
_L27-34_
- L29 _public enumerator_ `Normal`
- L30 _public enumerator_ `XBox`
- L31 _public enumerator_ `PS4`
- L32 _public enumerator_ `PS5`
- L33 _public enumerator_ `PS5New`

#### struct `GameControllerMapping::DeviceConfig`  
`struct DeviceConfig`  
_L41-74_
- L44 _public member_ `ControllerClassType ControllerClass = ControllerClassType::Generic;` — Type of controller
- L47 _public member_ `float LTAnalogRangeMinimum = .0f;` — Sets the analog range of the trigger minimum (normally 0).  Final value is mapped as (input - Minimum) / (1 - Minimum) to [0,1] output.
- L48 _public member_ `float RTAnalogRangeMinimum = .0f;`
- L51 _public member_ `bool SupportsHat = true;` — Device supports hat as dpad
- L54 _public member_ `bool TriggersUseThresholdForClick = false;` — Device uses threshold to send button pressed events.
- L57 _public member_ `bool MapL1R1ToTriggers = false;` — Map L1 and R1 to LTRIGGER and RTRIGGER
- L60 _public member_ `bool MapZRZToTriggers = false;` — Map Z and RZ to LTAnalog and RTAnalog
- L63 _public member_ `bool RightStickZRZ = true;` — Right stick on Z/RZ
- L66 _public member_ `bool RightStickRXRY = false;` — Right stick on RX/RY
- L69 _public member_ `bool MapRXRYToTriggers = false;` — Map RX and RY to LTAnalog and RTAnalog
- L71 _public member_ `int DeviceNameIndex = -1;`
- L73 _public member_ `TWeakPtr<KeyCodeToKeyNameMap> ButtonMapping;`

#### class `GameControllerMapping::FAndroidGameControllerMapper`  
`class FAndroidGameControllerMapper`  
_L80-116_
- L83 _public function_ `~FAndroidGameControllerMapper()`
- L85 _public prototype_ `static TWeakPtr<FAndroidGameControllerMapper> GetInstance();`
- L87 _public prototype_ `const DeviceConfig_WPtr GetDeviceConfig(int32 VendorId, int32 ProductId, const FName DeviceName);`
- L89 _public prototype_ `void RegisterDeviceConfig(int32 VendorId, int32 ProductId, DeviceConfig_SRef& DeviceCfg);`
- L92 _private function_ `FAndroidGameControllerMapper()`
- L94 _private prototype_ `bool Init();`
- L96 _private prototype_ `bool InitByDataFile();`
- L98 _private prototype_ `const DeviceConfig_SPtr GetDeviceConfig(const FName DeviceName);`
- L100 _private prototype_ `void AppendKeyCodeKeyNameMapping(KeyCodeToKeyNameMap_SRef& TargetContainer, int32 KeyCode, int32 KeyNameIndex);`
- L102 _private function_ `uint64 PackDeviceKey(int32 VendorId, int32 ProductId) const`
- L107 _private member_ `TArray<KeyCodeToKeyNameMap_SRef> ButtonMappings;`
- L109 _private member_ `TMap<uint64, DeviceConfig_SRef> DeviceConfigurationMap;`
- L111 _private member_ `TMap<uint64, DeviceConfig_SRef> DeviceConfigurationMap_Special;`
- L113 _private member_ `TArray<const FName> DeviceNames;`
- L115 _private member_ `static TSharedPtr<FAndroidGameControllerMapper> Instance;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace GameControllerMapping`
- L36 _typedef_ `typedef TMap<int32 , TArray<int32 >> KeyCodeToKeyNameMap;` (scope `GameControllerMapping`) — ButtonStates[] and ButtonMapping[] use same indices
- L37 _typedef_ `typedef TWeakPtr<KeyCodeToKeyNameMap> KeyCodeToKeyNameMap_WPtr;` (scope `GameControllerMapping`)
- L38 _typedef_ `typedef TSharedPtr<KeyCodeToKeyNameMap> KeyCodeToKeyNameMap_SPtr;` (scope `GameControllerMapping`)
- L39 _typedef_ `typedef TSharedRef<KeyCodeToKeyNameMap> KeyCodeToKeyNameMap_SRef;` (scope `GameControllerMapping`)
- L76 _typedef_ `typedef TWeakPtr<DeviceConfig> DeviceConfig_WPtr;` (scope `GameControllerMapping`)
- L77 _typedef_ `typedef TSharedPtr<DeviceConfig> DeviceConfig_SPtr;` (scope `GameControllerMapping`)
- L78 _typedef_ `typedef TSharedRef<DeviceConfig> DeviceConfig_SRef;` (scope `GameControllerMapping`)

### `Source/Runtime/ApplicationCore/Public/Android/AndroidInputInterface.h` (Public)


#### enum `(anonymous)`  
``  
_L26-69_

#### enum `(anonymous)`  
``  
_L71-73_

#### enum `(anonymous)`  
``  
_L75-78_

#### enum `InputDeviceType`  
`enum InputDeviceType`  
_L81-86_
- L83 _public enumerator_ `UnknownInputDeviceType`
- L84 _public enumerator_ `TouchScreen`
- L85 _public enumerator_ `GameController`

#### enum `TouchType`  
`enum TouchType`  
_L88-93_
- L90 _public enumerator_ `TouchBegan`
- L91 _public enumerator_ `TouchMoved`
- L92 _public enumerator_ `TouchEnded`

#### enum `InputDeviceStateEvent`  
`enum class InputDeviceStateEvent`  
_L95-100_
- L97 _public enumerator_ `Added = 0`
- L98 _public enumerator_ `Removed`
- L99 _public enumerator_ `Changed`

#### enum `MappingState`  
`enum MappingState`  
_L102-108_
- L104 _public enumerator_ `Unassigned = 0`
- L105 _public enumerator_ `ToActivate`
- L106 _public enumerator_ `ToValidate`
- L107 _public enumerator_ `Valid`

#### struct `FAndroidInputDeviceInfo`  
`struct FAndroidInputDeviceInfo`  
_L110-129_
- L112 _public function_ `FAndroidInputDeviceInfo()`
- L117 _public member_ `int32 DeviceId = 0;`
- L118 _public member_ `int32 VendorId = 0;`
- L119 _public member_ `int32 ProductId = 0;`
- L120 _public member_ `int32 ControllerId = 0;`
- L121 _public member_ `FName Name;`
- L122 _public member_ `FString Descriptor;`
- L123 _public member_ `int32 FeedbackMotorCount = 0;`
- L124 _public member_ `bool IsExternal = false;`
- L126 _public member_ `InputDeviceType DeviceType = InputDeviceType::UnknownInputDeviceType;`
- L127 _public member_ `MappingState DeviceState = MappingState::Unassigned;`
- L128 _public member_ `int32 DataIndex = -1;` — -1 = invalid

#### struct `TouchInput`  
`struct TouchInput`  
_L131-144_
- L134 _public member_ `int32 DeviceId;` — This is the Android kernel-provided "Device ID", NOT the Unreal "Device ID".
- L135 _public member_ `int32 Handle;`
- L136 _public member_ `FVector2D LastPosition;`
- L137 _public member_ `FVector2D Position;`
- L142 _public member_ `FInputDeviceId InputDeviceId;` — When valid, the touch loop uses this directly instead of resolving DeviceId through InputDeviceInfoMap. See FAndroidInputInterface::RegisterSurfaceForTouch.
- L143 _public member_ `TouchType Type;`

#### struct `FAndroidControllerData`  
`struct FAndroidControllerData`  
_L152-168_
- L155 _public member_ `int32 DeviceId;` — ID of the controller
- L158 _public member_ `bool ButtonStates[MAX_NUM_CONTROLLER_BUTTONS];` — Current button states and the next time a repeat event should be generated for each button
- L159 _public member_ `double NextRepeatTime[MAX_NUM_CONTROLLER_BUTTONS];`
- L162 _public member_ `float LXAnalog;` — Raw analog values for various axes (sticks and triggers)
- L163 _public member_ `float LYAnalog;`
- L164 _public member_ `float RXAnalog;`
- L165 _public member_ `float RYAnalog;`
- L166 _public member_ `float LTAnalog;`
- L167 _public member_ `float RTAnalog;`

#### struct `FAndroidControllerVibeState`  
`struct FAndroidControllerVibeState`  
_L170-176_
- L172 _public member_ `FForceFeedbackValues VibeValues;`
- L173 _public member_ `int32 LeftIntensity;`
- L174 _public member_ `int32 RightIntensity;`
- L175 _public member_ `double LastVibeUpdateTime;`

#### struct `FAndroidGamepadDeviceMapping`  
`struct FAndroidGamepadDeviceMapping`  
_L178-199_
- L180 _public function_ `FAndroidGamepadDeviceMapping(const int32 InVendorId, const int32 InProductId, const FName InDeviceName)`
- L185 _public prototype_ `void Init(const int32 InVendorId, const int32 InProductId, const FName InDeviceName);`
- L187 _public function_ `void ResetRuntimeData()`
- L194 _public member_ `GameControllerMapping::DeviceConfig_WPtr DeviceConfig;`
- L196 _public member_ `FAndroidControllerData OldControllerData;`
- L197 _public member_ `FAndroidControllerData NewControllerData;`
- L198 _public member_ `FAndroidControllerVibeState ControllerVibeState;`

#### enum `FAndroidMessageType`  
`enum FAndroidMessageType`  
_L201-205_
- L203 _public enumerator_ `MessageType_KeyDown`
- L204 _public enumerator_ `MessageType_KeyUp`

#### struct `FDeferredAndroidMessage`  
`struct FDeferredAndroidMessage`  
_L207-224_
- L209 _public function_ `FDeferredAndroidMessage()`
- L211 _public member_ `FAndroidMessageType messageType;`

#### union `FDeferredAndroidMessage::(anonymous)`  
``  
_L213-223_

#### struct `FDeferredAndroidMessage::__anon79d29d8b040a::(anonymous)`  
``  
_L215-220_

#### class `FAndroidInputInterface`  
`class FAndroidInputInterface : public IInputInterface`  
_L230-414_
- inherits: `IInputInterface`
- desc: Interface class for Android input devices
- L234 _public prototype_ `static TSharedRef< FAndroidInputInterface > Create( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler, const TSharedPtr< ICursor >& InCursor);`
- L239 _public prototype_ `~FAndroidInputInterface();`
- L241 _public prototype_ `void SetMessageHandler( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler );`
- L244 _public prototype_ `void Tick( float DeltaTime );` — Tick the interface (i.e check for new controllers)
- L249 _public prototype_ `void SendControllerEvents();` — Poll for controller state and send events if needed
- L251 _public prototype_ `static void QueueTouchInput(const TArray<TouchInput>& InTouchEvents);`
- L260 _public prototype_ `static FInputDeviceId RegisterSurfaceForTouch(const TSharedRef<FAndroidWindow>& Window);` — Register an Android Surface so that touches associated with it can be processed properly by QueueTouchInput. This is necessary when allocating any Surfaces other than the primary activity one that the engine owns, because Android reports touch device ID based on the physical hardware, but tracks finger indices uniquely per Surface.  Unreal expects finger indices to be unique per device. Caller is responsible for mapping the returned device to an FPlatformUserId, and for forwarding touch events to QueueTouchInput.
- L263 _public prototype_ `static void UnregisterSurface(FInputDeviceId DeviceId);` — Release a virtual touchscreen previously returned by RegisterSurfaceForTouch.
- L265 _public prototype_ `static void ResetGamepadAssignments();`
- L266 _public prototype_ `static void ResetGamepadAssignmentToController(int32 ControllerId);`
- L267 _public prototype_ `static bool IsControllerAssignedToGamepad(int32 ControllerId);`
- L268 _public prototype_ `static const FInputDeviceId GetMappedInputDeviceId(int32 ControllerId);`
- L269 _public prototype_ `static const FName GetGamepadControllerName(int32 ControllerId);`
- L271 _public prototype_ `static void HandleInputDeviceStateEvent(int32 DeviceId, InputDeviceStateEvent StateEvent, InputDeviceType DeviceType);`
- L273 _public prototype_ `static void JoystickAxisEvent(int32 deviceId, int32 axisId, float axisValue);`
- L274 _public prototype_ `static void JoystickButtonEvent(int32 deviceId, int32 buttonId, bool buttonDown);`
- L276 _public prototype_ `static int32 GetAlternateKeyEventForMouse(int32 deviceId, int32 buttonId);`
- L277 _public prototype_ `static void MouseMoveEvent(int32 deviceId, float absoluteX, float absoluteY, float deltaX, float deltaY);`
- L278 _public prototype_ `static void MouseWheelEvent(int32 deviceId, float wheelDelta);`
- L279 _public prototype_ `static void MouseButtonEvent(int32 deviceId, int32 buttonId, bool buttonDown);`
- L281 _public prototype_ `static void DeferMessage(const FDeferredAndroidMessage& DeferredMessage);`
- L283 _public prototype_ `static void QueueMotionData(const FVector& Tilt, const FVector& RotationRate, const FVector& Gravity, const FVector& Acceleration);`
- L288 _public prototype_ `virtual void SetForceFeedbackChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;` — Force Feedback implementation
- L289 _public prototype_ `virtual void SetForceFeedbackChannelValues(int32 ControllerId, const FForceFeedbackValues &values) override;`
- L290 _public prototype_ `virtual void SetHapticFeedbackValues(int32 ControllerId, int32 Hand, const FHapticFeedbackValues& Values) override;`
- L291 _public prototype_ `virtual void SetLightColor(int32 ControllerId, FColor Color) override;`
- L292 _public prototype_ `virtual void ResetLightColor(int32 ControllerId) override;`
- L294 _public function_ `void SetGamepadsAllowed(bool bAllowed)`
- L295 _public function_ `void SetGamepadsBlockDeviceFeedback(bool bBlock)`
- L297 _public prototype_ `virtual bool IsGamepadAttached() const;`
- L300 _public prototype_ `virtual void AddExternalInputDevice(TSharedPtr<class IInputDevice> InputDevice);`
- L302 _public function_ `const TSharedPtr< ICursor > GetCursor() const`
- L306 _private prototype_ `FAndroidInputInterface( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler, const TSharedPtr< ICursor >& InCursor);`
- L308 _private prototype_ `static bool GetInputDeviceByDeviceId(int32 DeviceId, FAndroidInputDeviceInfo** OutDeviceInfo, FAndroidGamepadDeviceMapping** OutDeviceData = nullptr);`
- L309 _private prototype_ `static bool GetInputDeviceByControllerId(int32 ControllerId, FAndroidInputDeviceInfo** OutDeviceInfo, FAndroidGamepadDeviceMapping** OutDeviceData = nullptr);`
- L311 _private prototype_ `static void MapControllerToPlayer(const FString& ControllerDesciptor, EInputDeviceConnectionState State);`
- L312 _private prototype_ `static void AddPendingInputDevice(int32 DeviceId, InputDeviceType DeviceType);`
- L313 _private prototype_ `static void RemoveInputDevice(int32 DeviceId);`
- L314 _private prototype_ `static void DumpInputDevices();`
- L318 _public prototype_ `ControllerClassType GetControllerClass(int32 ControllerId) const;`
- L323 _private prototype_ `static int32 FindControllerId(int32 DeviceId);` — Find controller ID(index) corresponding to validated deviceId (returns -1 if not found)
- L326 _private prototype_ `void UpdateVibeMotors();` — Push Vibration changes to the main device
- L329 _private prototype_ `void UpdateControllerVibeMotors(int32 DeviceId, ControllerClassType ControllerClass, FAndroidControllerVibeState& State);` — Push Vibration changes to the controller
- L359 _private member_ `static FCriticalSection TouchInputCriticalSection;` — protects the input stack
- L361 _private member_ `static TArray<TouchInput> TouchInputStack;`
- L364 _private member_ `static int32 CurrentVibeIntensity;` — Vibration settings
- L366 _private member_ `static int32 MaxVibeTime;` — Maximum time vibration will be triggered without an update
- L367 _private member_ `static double LastVibeUpdateTime;`
- L368 _private member_ `static FForceFeedbackValues VibeValues;`
- L371 _private member_ `static bool bAllowControllers;` — should we allow controllers to send input
- L374 _private member_ `static bool bControllersBlockDeviceFeedback;` — bluetooth connected controllers will block force feedback.
- L377 _private member_ `static bool bBlockAndroidKeysOnControllers;` — should we allow controllers to send Android_Back and Android_Menu events
- L379 _private member_ `static TInputDeviceMap<FString> InternalDeviceIdMappings;`
- L380 _private member_ `static TArray<int32 > GameControllerIdMapping;`
- L381 _private member_ `static TMap<int32 , FAndroidInputDeviceInfo> InputDeviceInfoMap;`
- L382 _private member_ `static TMap<FInputDeviceId, FAndroidGamepadDeviceMapping> GameControllerDataMap;`
- L384 _private member_ `static TMap<FInputDeviceId, TWeakPtr<FGenericWindow>> InputMappedSurfaces;` — Windows registered via RegisterSurfaceForTouch, looked up during touch dispatch. Guarded by TouchInputCriticalSection.
- L389 _private member_ `static TArray<FInputDeviceId> FreeSurfaceInputDeviceIds;` — FInputDeviceIds previously returned by RegisterSurfaceForTouch and freed via UnregisterSurface, available for reuse. Bounds the FInputDeviceId allocation counter across repeated attach/detach cycles.  Guarded by TouchInputCriticalSection.
- L391 _private member_ `static FName InputClassName_DefaultMobileTouch;`
- L392 _private member_ `static FName InputClassName_DefaultGamepad;`
- L394 _private member_ `static FString HardwareDeviceIdentifier_DefaultMobileTouch;` — The following two vars should be FName. Waiting for a refactoring of the FInputDeviceScope's ctor
- L395 _private member_ `static FString HardwareDeviceIdentifier_DefaultGamepad;`
- L397 _private member_ `static FGamepadKeyNames::Type ButtonMapping[MAX_NUM_CONTROLLER_BUTTONS];`
- L399 _private member_ `static float InitialButtonRepeatDelay;`
- L400 _private member_ `static float ButtonRepeatDelay;`
- L402 _private member_ `static FDeferredAndroidMessage DeferredMessages[MAX_DEFERRED_MESSAGE_QUEUE_SIZE];`
- L403 _private member_ `static int32 DeferredMessageQueueLastEntryIndex;`
- L404 _private member_ `static int32 DeferredMessageQueueDroppedCount;`
- L406 _private member_ `static TArray<MotionData> MotionDataStack;`
- L407 _private member_ `static TArray<MouseData> MouseDataStack;`
- L409 _private member_ `TSharedRef< FGenericApplicationMessageHandler > MessageHandler;`
- L410 _private member_ `const TSharedPtr< ICursor > Cursor;`
- L413 _private member_ `TArray<TSharedPtr<class IInputDevice>> ExternalInputDevices;` — List of input devices implemented in external modules.

#### struct `FAndroidInputInterface::MotionData`  
`struct MotionData`  
_L331-337_
- L333 _public member_ `FVector Tilt;`
- L334 _public member_ `FVector RotationRate;`
- L335 _public member_ `FVector Gravity;`
- L336 _public member_ `FVector Acceleration;`

#### enum `FAndroidInputInterface::MouseEventType`  
`enum MouseEventType`  
_L339-345_
- L341 _public enumerator_ `MouseMove`
- L342 _public enumerator_ `MouseWheel`
- L343 _public enumerator_ `MouseButtonDown`
- L344 _public enumerator_ `MouseButtonUp`

#### struct `FAndroidInputInterface::MouseData`  
`struct MouseData`  
_L347-356_
- L349 _public member_ `MouseEventType EventType;`
- L350 _public member_ `EMouseButtons::Type Button;`
- L351 _public member_ `int32 AbsoluteX;`
- L352 _public member_ `int32 AbsoluteY;`
- L353 _public member_ `int32 DeltaX;`
- L354 _public member_ `int32 DeltaY;`
- L355 _public member_ `float WheelDelta;`

#### Free symbols / members of external scopes

- L27 _enumerator_ `AMOTION_EVENT_AXIS_X = 0` (scope `__anon79d29d8b0103`)
- L28 _enumerator_ `AMOTION_EVENT_AXIS_Y = 1` (scope `__anon79d29d8b0103`)
- L29 _enumerator_ `AMOTION_EVENT_AXIS_PRESSURE = 2` (scope `__anon79d29d8b0103`)
- L30 _enumerator_ `AMOTION_EVENT_AXIS_SIZE = 3` (scope `__anon79d29d8b0103`)
- L31 _enumerator_ `AMOTION_EVENT_AXIS_TOUCH_MAJOR = 4` (scope `__anon79d29d8b0103`)
- L32 _enumerator_ `AMOTION_EVENT_AXIS_TOUCH_MINOR = 5` (scope `__anon79d29d8b0103`)
- L33 _enumerator_ `AMOTION_EVENT_AXIS_TOOL_MAJOR = 6` (scope `__anon79d29d8b0103`)
- L34 _enumerator_ `AMOTION_EVENT_AXIS_TOOL_MINOR = 7` (scope `__anon79d29d8b0103`)
- L35 _enumerator_ `AMOTION_EVENT_AXIS_ORIENTATION = 8` (scope `__anon79d29d8b0103`)
- L36 _enumerator_ `AMOTION_EVENT_AXIS_VSCROLL = 9` (scope `__anon79d29d8b0103`)
- L37 _enumerator_ `AMOTION_EVENT_AXIS_HSCROLL = 10` (scope `__anon79d29d8b0103`)
- L38 _enumerator_ `AMOTION_EVENT_AXIS_Z = 11` (scope `__anon79d29d8b0103`)
- L39 _enumerator_ `AMOTION_EVENT_AXIS_RX = 12` (scope `__anon79d29d8b0103`)
- L40 _enumerator_ `AMOTION_EVENT_AXIS_RY = 13` (scope `__anon79d29d8b0103`)
- L41 _enumerator_ `AMOTION_EVENT_AXIS_RZ = 14` (scope `__anon79d29d8b0103`)
- L42 _enumerator_ `AMOTION_EVENT_AXIS_HAT_X = 15` (scope `__anon79d29d8b0103`)
- L43 _enumerator_ `AMOTION_EVENT_AXIS_HAT_Y = 16` (scope `__anon79d29d8b0103`)
- L44 _enumerator_ `AMOTION_EVENT_AXIS_LTRIGGER = 17` (scope `__anon79d29d8b0103`)
- L45 _enumerator_ `AMOTION_EVENT_AXIS_RTRIGGER = 18` (scope `__anon79d29d8b0103`)
- L46 _enumerator_ `AMOTION_EVENT_AXIS_THROTTLE = 19` (scope `__anon79d29d8b0103`)
- L47 _enumerator_ `AMOTION_EVENT_AXIS_RUDDER = 20` (scope `__anon79d29d8b0103`)
- L48 _enumerator_ `AMOTION_EVENT_AXIS_WHEEL = 21` (scope `__anon79d29d8b0103`)
- L49 _enumerator_ `AMOTION_EVENT_AXIS_GAS = 22` (scope `__anon79d29d8b0103`)
- L50 _enumerator_ `AMOTION_EVENT_AXIS_BRAKE = 23` (scope `__anon79d29d8b0103`)
- L51 _enumerator_ `AMOTION_EVENT_AXIS_DISTANCE = 24` (scope `__anon79d29d8b0103`)
- L52 _enumerator_ `AMOTION_EVENT_AXIS_TILT = 25` (scope `__anon79d29d8b0103`)
- L53 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_1 = 32` (scope `__anon79d29d8b0103`)
- L54 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_2 = 33` (scope `__anon79d29d8b0103`)
- L55 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_3 = 34` (scope `__anon79d29d8b0103`)
- L56 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_4 = 35` (scope `__anon79d29d8b0103`)
- L57 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_5 = 36` (scope `__anon79d29d8b0103`)
- L58 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_6 = 37` (scope `__anon79d29d8b0103`)
- L59 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_7 = 38` (scope `__anon79d29d8b0103`)
- L60 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_8 = 39` (scope `__anon79d29d8b0103`)
- L61 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_9 = 40` (scope `__anon79d29d8b0103`)
- L62 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_10 = 41` (scope `__anon79d29d8b0103`)
- L63 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_11 = 42` (scope `__anon79d29d8b0103`)
- L64 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_12 = 43` (scope `__anon79d29d8b0103`)
- L65 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_13 = 44` (scope `__anon79d29d8b0103`)
- L66 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_14 = 45` (scope `__anon79d29d8b0103`)
- L67 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_15 = 46` (scope `__anon79d29d8b0103`)
- L68 _enumerator_ `AMOTION_EVENT_AXIS_GENERIC_16 = 47` (scope `__anon79d29d8b0103`)
- L72 _enumerator_ `AINPUT_SOURCE_CLASS_JOYSTICK = 0x00000010` (scope `__anon79d29d8b0203`)
- L76 _enumerator_ `AINPUT_SOURCE_GAMEPAD = 0x00000400 | AINPUT_SOURCE_CLASS_BUTTON` (scope `__anon79d29d8b0303`)
- L77 _enumerator_ `AINPUT_SOURCE_JOYSTICK = 0x01000000 | AINPUT_SOURCE_CLASS_JOYSTICK` (scope `__anon79d29d8b0303`)
- L146 _macro_ `#define MAX_NUM_CONTROLLERS 8 // reasonable limit for now`
- L147 _macro_ `#define MAX_NUM_PHYSICAL_CONTROLLER_BUTTONS 18`
- L148 _macro_ `#define MAX_NUM_VIRTUAL_CONTROLLER_BUTTONS 8`
- L149 _macro_ `#define MAX_NUM_CONTROLLER_BUTTONS MAX_NUM_PHYSICAL_CONTROLLER_BUTTONS + MAX_NUM_VIRTUAL_CONTROLLER_BUTTONS`
- L150 _macro_ `#define MAX_DEFERRED_MESSAGE_QUEUE_SIZE 128`
- L216 _member_ `int32 keyId{};` (scope `FDeferredAndroidMessage::__anon79d29d8b040a::__anon79d29d8b0508`)
- L217 _member_ `int32 unichar{};` (scope `FDeferredAndroidMessage::__anon79d29d8b040a::__anon79d29d8b0508`)
- L218 _member_ `uint32 modifier{};` (scope `FDeferredAndroidMessage::__anon79d29d8b040a::__anon79d29d8b0508`)
- L219 _member_ `bool isRepeat{};` (scope `FDeferredAndroidMessage::__anon79d29d8b040a::__anon79d29d8b0508`)
- L226 _typedef_ `typedef GameControllerMapping::ControllerClassType ControllerClassType;`

### `Source/Runtime/ApplicationCore/Public/Android/AndroidJavaMediaFrameData.h` (Public)


#### class `FAndroidJavaMediaFrameData`  
`class FAndroidJavaMediaFrameData`  
_L12-58_
- L15 _public prototype_ `FAndroidJavaMediaFrameData();`
- L16 _public prototype_ `virtual ~FAndroidJavaMediaFrameData();`
- L18 _public prototype_ `FAndroidJavaMediaFrameData(const FAndroidJavaMediaFrameData& Other) = delete;`
- L19 _public prototype_ `FAndroidJavaMediaFrameData& operator=(const FAndroidJavaMediaFrameData& Other) = delete;`
- L21 _public prototype_ `FAndroidJavaMediaFrameData& operator=(FAndroidJavaMediaFrameData& Other);`
- L23 _public function_ `operator bool() const`
- L28 _public function_ `bool IsReadyToClean()`
- L37 _public prototype_ `bool Set(jobject InFrameData);`
- L38 _public prototype_ `void CleanUp();`
- L40 _public prototype_ `jobject Extract();`
- L41 _public prototype_ `bool ExtractToTextureVulkan(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InDstTexture, IMediaTextureSample* TextureSample);`
- L42 _public prototype_ `bool ExtractToTextureOES(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InDstTexture, IMediaTextureSample* TextureSample);`
- L45 _private member_ `TRefCountPtr<FRHITexture> Texture;`
- L46 _private member_ `TRefCountPtr<FRHIGPUFence> Fence;`
- L49 _private member_ `jobject FrameDataGlobalRef;` — The java frame data from the surface provider
- L52 _private member_ `static jfieldID FrameData_HardwareBufferHandle;` — FrameData members / methods
- L53 _private member_ `static jfieldID FrameData_UScale;`
- L54 _private member_ `static jfieldID FrameData_UOffset;`
- L55 _private member_ `static jfieldID FrameData_VScale;`
- L56 _private member_ `static jfieldID FrameData_VOffset;`
- L57 _private member_ `static jmethodID FrameData_ReleaseFN;`

### `Source/Runtime/ApplicationCore/Public/Android/AndroidJavaMediaPlayer.h` (Public)


#### class `FJavaAndroidMediaDataSource`  
`class FJavaAndroidMediaDataSource`  
_L11-30_
- L14 _public prototype_ `FJavaAndroidMediaDataSource(const TSharedRef<FArchive, ESPMode::ThreadSafe>& InArchive);`
- L17 _public prototype_ `virtual ~FJavaAndroidMediaDataSource();` — Virtual destructor.
- L20 _public prototype_ `int64 GetSize();`
- L21 _public prototype_ `int64 GetCurrentPosition();`
- L22 _public prototype_ `int32 ReadAt(int64 Position, uint8* Buffer, int32 Count);`
- L26 _private member_ `TSharedRef<FArchive, ESPMode::ThreadSafe> Archive;` — Holds the archive to stream from.
- L29 _private member_ `mutable FCriticalSection CriticalSection;` — Critical section for locking access to this class.

#### struct `UE::Jni::Nio::FByteBuffer`  
`struct FByteBuffer: Java::Lang::FObject`  
_L35-38_
- inherits: `Java::Lang::FObject`
- L37 _public member_ `static constexpr FAnsiStringView ClassName = "ja`

#### struct `UE::Jni::FMediaPlayer14`  
`struct FMediaPlayer14: Java::Lang::FObject`  
_L43-60_
- inherits: `Java::Lang::FObject`
- L45 _public member_ `static constexpr FAnsiStringView ClassName = "co`
- L47 _public member_ `inline static TConstructor<FMediaPlayer14(jboolean SwizzlePixels, jboolean VulkanRenderer, jboolean NeedTrackInfo)> New;`
- L49 _public prototype_ `static jint JNICALL nativeReadAt(JNIEnv* env, jobject thiz, jlong Identifier, jlong Position, Nio::FByteBuffer* Buffer, jint Offset, jint Count);`
- L51 _public member_ `static constexpr FMember Members[] { UE_JNI_MEMBER(New) };`
- L56 _public member_ `static constexpr FNativeMethod NativeMethods[] { UE_JNI_NATIVE_METHOD(nativeReadAt) };`

#### class `FJavaAndroidMediaPlayer`  
`class FJavaAndroidMediaPlayer : public UE::Jni::TClassObject<UE::Jni::FMediaPlayer14>`  
_L66-274_
- inherits: `UE::Jni::TClassObject<UE::Jni::FMediaPlayer14>`
- desc: Wrapper for com/epicgames/unreal/MediaPlayer*.java.
- L102 _public prototype_ `FJavaAndroidMediaPlayer(bool swizzlePixels, bool vulkanRenderer, bool needTrackInfo, bool forceBitmapRenderLegacy = false);`
- L103 _public prototype_ `virtual ~FJavaAndroidMediaPlayer();`
- L104 _public prototype_ `int32 GetDuration();`
- L105 _public prototype_ `void Reset();`
- L106 _public prototype_ `void Stop();`
- L107 _public prototype_ `int32 GetCurrentPosition();`
- L108 _public prototype_ `bool IsLooping();`
- L109 _public prototype_ `bool IsPlaying();`
- L110 _public prototype_ `bool IsPrepared();`
- L111 _public prototype_ `bool DidComplete();`
- L112 _public prototype_ `bool SetDataSource(const FString & Url);`
- L113 _public prototype_ `bool SetDataSource(const TSharedRef<FArchive, ESPMode::ThreadSafe>& InArchive);`
- L114 _public prototype_ `bool SetDataSource(const FString& MoviePathOnDevice, int64 offset, int64 size);`
- L115 _public prototype_ `bool SetDataSource(jobject AssetMgr, const FString& AssetPath, int64 offset, int64 size);`
- L116 _public prototype_ `bool Prepare();`
- L117 _public prototype_ `bool PrepareAsync();`
- L118 _public prototype_ `void SeekTo(int32 Milliseconds);`
- L119 _public prototype_ `void SetLooping(bool Looping);`
- L120 _public prototype_ `void Release();`
- L121 _public prototype_ `int32 GetVideoHeight();`
- L122 _public prototype_ `int32 GetVideoWidth();`
- L123 _public prototype_ `void SetVideoEnabled(bool enabled = true);`
- L124 _public prototype_ `void SetAudioEnabled(bool enabled = true);`
- L125 _public prototype_ `void SetAudioVolume(float Volume);`
- L126 _public prototype_ `bool IsUsingBitmapRendererImageReader();`
- L127 _public prototype_ `jobject GetVideoLastMediaFrameData();`
- L128 _public prototype_ `bool GetVideoLastFrameData(void* & outPixels, int64 & outCount);`
- L129 _public prototype_ `void Start();`
- L130 _public prototype_ `void Pause();`
- L131 _public prototype_ `bool GetVideoLastFrame(int32 destTexture);`
- L132 _public prototype_ `bool SelectTrack(int32 index);`
- L133 _public prototype_ `bool GetAudioTracks(TArray<FAudioTrack>& AudioTracks);`
- L134 _public prototype_ `bool GetCaptionTracks(TArray<FCaptionTrack>& CaptionTracks);`
- L135 _public prototype_ `bool GetVideoTracks(TArray<FVideoTrack>& VideoTracks);`
- L136 _public prototype_ `bool DidResolutionChange();`
- L137 _public prototype_ `int32 GetExternalTextureId();`
- L138 _public prototype_ `bool UpdateVideoFrame(int32 ExternalTextureId, int32 *CurrentPosition, bool *bRegionChanged);`
- L141 _private prototype_ `static FName GetClassName();`
- L143 _private member_ `bool bTrackInfoSupported;`
- L145 _private member_ `FJavaClassMethod GetDurationMethod;`
- L146 _private member_ `FJavaClassMethod ResetMethod;`
- L147 _private member_ `FJavaClassMethod StopMethod;`
- L148 _private member_ `FJavaClassMethod GetCurrentPositionMethod;`
- L149 _private member_ `FJavaClassMethod IsLoopingMethod;`
- L150 _private member_ `FJavaClassMethod IsPlayingMethod;`
- L151 _private member_ `FJavaClassMethod IsPreparedMethod;`
- L152 _private member_ `FJavaClassMethod DidCompleteMethod;`
- L153 _private member_ `FJavaClassMethod SetDataSourceURLMethod;`
- L154 _private member_ `FJavaClassMethod SetDataSourceArchiveMethod;`
- L155 _private member_ `FJavaClassMethod SetDataSourceFileMethod;`
- L156 _private member_ `FJavaClassMethod SetDataSourceAssetMethod;`
- L157 _private member_ `FJavaClassMethod PrepareMethod;`
- L158 _private member_ `FJavaClassMethod PrepareAsyncMethod;`
- L159 _private member_ `FJavaClassMethod SeekToMethod;`
- L160 _private member_ `FJavaClassMethod SetLoopingMethod;`
- L161 _private member_ `FJavaClassMethod ReleaseMethod;`
- L162 _private member_ `FJavaClassMethod GetVideoHeightMethod;`
- L163 _private member_ `FJavaClassMethod GetVideoWidthMethod;`
- L164 _private member_ `FJavaClassMethod SetVideoEnabledMethod;`
- L165 _private member_ `FJavaClassMethod SetAudioEnabledMethod;`
- L166 _private member_ `FJavaClassMethod SetAudioVolumeMethod;`
- L167 _private member_ `FJavaClassMethod GetVideoLastFrameDataMethod;`
- L168 _private member_ `FJavaClassMethod StartMethod;`
- L169 _private member_ `FJavaClassMethod PauseMethod;`
- L170 _private member_ `FJavaClassMethod GetVideoLastFrameMethod;`
- L171 _private member_ `FJavaClassMethod SelectTrackMethod;`
- L172 _private member_ `FJavaClassMethod GetAudioTracksMethod;`
- L173 _private member_ `FJavaClassMethod GetCaptionTracksMethod;`
- L174 _private member_ `FJavaClassMethod GetVideoTracksMethod;`
- L175 _private member_ `FJavaClassMethod DidResolutionChangeMethod;`
- L176 _private member_ `FJavaClassMethod GetExternalTextureIdMethod;`
- L177 _private member_ `FJavaClassMethod UpdateVideoFrameMethod;`
- L179 _private member_ `FJavaClassMethod SetUsingBitmapRendererImageReaderMethod;` — new way of getting video frame data
- L180 _private member_ `FJavaClassMethod GetVideoLastMediaFrameDataMethod;`
- L183 _private member_ `jclass FrameUpdateInfoClass;` — FrameUpdateInfo member field ids
- L184 _private member_ `jfieldID FrameUpdateInfo_CurrentPosition;`
- L185 _private member_ `jfieldID FrameUpdateInfo_FrameReady;`
- L186 _private member_ `jfieldID FrameUpdateInfo_RegionChanged;`
- L187 _private member_ `jfieldID FrameUpdateInfo_UScale;`
- L188 _private member_ `jfieldID FrameUpdateInfo_UOffset;`
- L189 _private member_ `jfieldID FrameUpdateInfo_VScale;`
- L190 _private member_ `jfieldID FrameUpdateInfo_VOffset;`
- L193 _private member_ `jclass AudioTrackInfoClass;` — AudioDeviceInfo member field ids
- L194 _private member_ `jfieldID AudioTrackInfo_Index;`
- L195 _private member_ `jfieldID AudioTrackInfo_MimeType;`
- L196 _private member_ `jfieldID AudioTrackInfo_DisplayName;`
- L197 _private member_ `jfieldID AudioTrackInfo_Language;`
- L198 _private member_ `jfieldID AudioTrackInfo_Channels;`
- L199 _private member_ `jfieldID AudioTrackInfo_SampleRate;`
- L202 _private member_ `jclass CaptionTrackInfoClass;` — AudioDeviceInfo member field ids
- L203 _private member_ `jfieldID CaptionTrackInfo_Index;`
- L204 _private member_ `jfieldID CaptionTrackInfo_MimeType;`
- L205 _private member_ `jfieldID CaptionTrackInfo_DisplayName;`
- L206 _private member_ `jfieldID CaptionTrackInfo_Language;`
- L209 _private member_ `jclass VideoTrackInfoClass;` — AudioDeviceInfo member field ids
- L210 _private member_ `jfieldID VideoTrackInfo_Index;`
- L211 _private member_ `jfieldID VideoTrackInfo_MimeType;`
- L212 _private member_ `jfieldID VideoTrackInfo_DisplayName;`
- L213 _private member_ `jfieldID VideoTrackInfo_Language;`
- L214 _private member_ `jfieldID VideoTrackInfo_BitRate;`
- L215 _private member_ `jfieldID VideoTrackInfo_Width;`
- L216 _private member_ `jfieldID VideoTrackInfo_Height;`
- L217 _private member_ `jfieldID VideoTrackInfo_FrameRate;`
- L219 _private member_ `FTextureRHIRef VideoTexture;`
- L220 _private member_ `bool bVideoTextureValid;`
- L222 _private member_ `float UScale, UOffset;`
- L222 _private member_ `float UScale, UOffset;`
- L223 _private member_ `float VScale, VOffset;`
- L223 _private member_ `float VScale, VOffset;`
- L226 _private member_ `TSharedPtr<FJavaAndroidMediaDataSource, ESPMode::ThreadSafe> MediaDataSource;` — Current media data source if using one.
- L235 _private member_ `BitmapRendererSelection BRSelection;` — BR - BitmapRenderer
- L236 _private member_ `bool UsingVulkanRenderer;`
- L238 _private prototype_ `void SelectBitmapRenderer();`
- L241 _public function_ `FTextureRHIRef GetVideoTexture()`
- L246 _public function_ `void SetVideoTexture(FTextureRHIRef Texture)`
- L251 _public function_ `void SetVideoTextureValid(bool Condition)`
- L256 _public function_ `bool IsVideoTextureValid()`
- L261 _public function_ `float GetUScale()`
- L262 _public function_ `float GetUOffset()`
- L264 _public function_ `float GetVScale()`
- L265 _public function_ `float GetVOffset()`
- L268 _protected member_ `static FCriticalSection MediaDataSourcesCS;`
- L269 _protected member_ `static TMap<int64, TWeakPtr<FJavaAndroidMediaDataSource, ESPMode::ThreadSafe>> AllMediaDataSources;`
- L272 _public prototype_ `static TSharedPtr<FJavaAndroidMediaDataSource, ESPMode::ThreadSafe> GetMediaDataSourcePtr(int64 Identifier);`
- L273 _public prototype_ `static void AddMediaDataSourcePtr(int64 Identifier, TSharedPtr<FJavaAndroidMediaDataSource, ESPMode::ThreadSafe> MediaDataSource);`

#### struct `FJavaAndroidMediaPlayer::FAudioTrack`  
`struct FAudioTrack`  
_L69-78_
- L71 _public member_ `int32 Index;`
- L72 _public member_ `FString MimeType;`
- L73 _public member_ `FString DisplayName;`
- L74 _public member_ `FString Language;`
- L75 _public member_ `FString Name;`
- L76 _public member_ `uint32 Channels;`
- L77 _public member_ `uint32 SampleRate;`

#### struct `FJavaAndroidMediaPlayer::FCaptionTrack`  
`struct FCaptionTrack`  
_L80-87_
- L82 _public member_ `int32 Index;`
- L83 _public member_ `FString MimeType;`
- L84 _public member_ `FString DisplayName;`
- L85 _public member_ `FString Language;`
- L86 _public member_ `FString Name;`

#### struct `FJavaAndroidMediaPlayer::FVideoTrack`  
`struct FVideoTrack`  
_L89-99_
- L91 _public member_ `int32 Index;`
- L92 _public member_ `FString MimeType;`
- L93 _public member_ `FString DisplayName;`
- L94 _public member_ `FString Language;`
- L95 _public member_ `FString Name;`
- L96 _public member_ `uint32 BitRate;`
- L97 _public member_ `FIntPoint Dimensions;`
- L98 _public member_ `float FrameRate;`

#### enum `FJavaAndroidMediaPlayer::BitmapRendererSelection`  
`enum BitmapRendererSelection`  
_L228-233_
- L230 _public enumerator_ `Unknown`
- L231 _public enumerator_ `Legacy`
- L232 _public enumerator_ `ImageReader`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace Jni` (scope `UE`)
- L33 _namespace_ `namespace Nio` (scope `UE::Jni`)
- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace Jni` (scope `UE`)
- L62 _variable_ `template struct TInitialize<FMediaPlayer14>;` (scope `UE::Jni`)

### `Source/Runtime/ApplicationCore/Public/Android/AndroidPlatformApplicationMisc.h` (Public)


#### struct `FAndroidApplicationMisc`  
`struct FAndroidApplicationMisc : public FGenericPlatformApplicationMisc`  
_L7-30_
- inherits: `FGenericPlatformApplicationMisc`
- L9 _public prototype_ `static void LoadPreInitModules();`
- L10 _public prototype_ `static class FFeedbackContext* GetFeedbackContext();`
- L11 _public prototype_ `static class FOutputDeviceError* GetErrorOutputDevice();`
- L12 _public prototype_ `static class GenericApplication* CreateApplication();`
- L13 _public prototype_ `static void RequestMinimize();`
- L14 _public prototype_ `static bool IsScreensaverEnabled();`
- L15 _public prototype_ `static bool ControlScreensaver(EScreenSaverAction Action);`
- L16 _public prototype_ `static void SetGamepadsAllowed(bool bAllowed);`
- L17 _public prototype_ `static void SetGamepadsBlockDeviceFeedback(bool bBlock);`
- L18 _public prototype_ `static void ResetGamepadAssignments();`
- L19 _public prototype_ `static void ResetGamepadAssignmentToController(int32 ControllerId);`
- L20 _public prototype_ `static bool IsControllerAssignedToGamepad(int32 ControllerId);`
- L21 _public prototype_ `static FString GetGamepadControllerName(int32 ControllerId);`
- L22 _public prototype_ `static void ClipboardCopy(const TCHAR* Str);`
- L23 _public prototype_ `static void ClipboardPaste(class FString& Dest);`
- L24 _public prototype_ `static EScreenPhysicalAccuracy ComputePhysicalScreenDensity(int32& OutScreenDensity);`
- L25 _public prototype_ `static EScreenPhysicalAccuracy ComputePhysicalScreenDimensions(FVector2f& OutScreenDimensions, float& OutScreenSize);`
- L26 _public prototype_ `static void EnableMotionData(bool bEnable);`
- L28 _public prototype_ `static EScreenPhysicalAccuracy GetNativePhysicalScreenDensity(int32& OutScreenDensity);`
- L29 _public prototype_ `static void GetNativePhysicalScreenResolution(FIntVector2& OutScreenResolution);`

#### Free symbols / members of external scopes

- L32 _typedef_ `typedef FAndroidApplicationMisc FPlatformApplicationMisc;`

### `Source/Runtime/ApplicationCore/Public/Android/AndroidPlatformFramePacer.h` (Public)


#### struct `IAndroidFramePacer`  
`struct IAndroidFramePacer`  
_L15-21_
- L17 _public prototype_ `virtual void Init() = 0;`
- L18 _public prototype_ `virtual ~IAndroidFramePacer() = default;`
- L19 _public function_ `virtual bool SwapBuffers(struct FPlatformOpenGLSurfaceContext* SurfaceContext, bool bLockToVsync)`
- L20 _public prototype_ `virtual bool SupportsFramePace(int32 QueryFramePace) = 0;`

#### struct `FAndroidOpenGLFramePacer`  
`struct FAndroidOpenGLFramePacer : public IAndroidFramePacer`  
_L23-49_
- inherits: `IAndroidFramePacer`
- L25 _public prototype_ `virtual void Init() override;`
- L26 _public prototype_ `virtual ~FAndroidOpenGLFramePacer();`
- L27 _public prototype_ `virtual bool SwapBuffers(struct FPlatformOpenGLSurfaceContext* SurfaceContext, bool bLockToVsync) override;`
- L28 _public prototype_ `virtual bool SupportsFramePace(int32 QueryFramePace) override;`
- L31 _private prototype_ `void InitSwappy();`
- L32 _private prototype_ `bool SupportsFramePaceInternal(int32 QueryFramePace, int32& OutRefreshRate, int32& OutSyncInterval);`
- L35 _private member_ `bool bSwappyInit = false;` — swappy state
- L36 _private member_ `int32 CachedFramePace = 60;`
- L37 _private member_ `int32 CachedRefreshRate = 60;`
- L38 _private member_ `int32 CachedSyncInterval = 1;`
- L39 _private member_ `struct ANativeWindow* CachedNativeWindow = nullptr;`
- L42 _private member_ `int32 DesiredSyncIntervalRelativeTo60Hz = -1;` — legacy framepacer state
- L43 _private member_ `int32 DesiredSyncIntervalRelativeToDevice = -1;`
- L44 _private member_ `int32 DriverSyncIntervalRelativeToDevice = -1;`
- L45 _private member_ `float DriverRefreshRate = 60.0f;`
- L46 _private member_ `int64 DriverRefreshNanos = 16666666;`
- L47 _private member_ `double LastTimeEmulatedSync = -1.0;`
- L48 _private member_ `uint32 SwapBufferFailureCount = 0;`

#### struct `FAndroidVulkanFramePacer`  
`struct FAndroidVulkanFramePacer : public IAndroidFramePacer`  
_L51-59_
- inherits: `IAndroidFramePacer`
- L53 _public prototype_ `virtual void Init() override;`
- L54 _public prototype_ `virtual ~FAndroidVulkanFramePacer() = default;`
- L55 _public prototype_ `virtual bool SupportsFramePace(int32 QueryFramePace) override;`
- L57 _private prototype_ `bool SupportsFramePaceInternal(int32 QueryFramePace, int32& OutRefreshRate, int32& OutSyncInterval);`

#### struct `FAndroidPlatformRHIFramePacer`  
`struct FAndroidPlatformRHIFramePacer : public FGenericPlatformRHIFramePacer`  
_L61-95_
- inherits: `FGenericPlatformRHIFramePacer`
- L64 _public prototype_ `static bool IsEnabled();` — FGenericPlatformRHIFramePacer interface
- L65 _public prototype_ `static void Destroy();`
- L66 _public prototype_ `static int32 GetFramePace();`
- L67 _public prototype_ `static int32 SetFramePace(int32 FramePace);`
- L68 _public function_ `static bool SupportsFramePace(int32 QueryFramePace)`
- L71 _public prototype_ `static void Init(IAndroidFramePacer* InFramePacer);` — FAndroidPlatformRHIFramePacer interface
- L72 _public prototype_ `static int32 GetLegacySyncInterval();`
- L73 _public function_ `static void SwapBuffers(struct FPlatformOpenGLSurfaceContext* SurfaceContext, bool bLockToVsync)`
- L75 _public member_ `static TAutoConsoleVariable<int32> CVarUseSwappyForFramePacing;`
- L76 _public member_ `static TAutoConsoleVariable<int32> CVarSwappyGPUFrameTimeFence;`
- L77 _public member_ `static TAutoConsoleVariable<int32> CVarSupportNonVSyncMultipleFrameRates;`
- L80 _public member_ `static TAutoConsoleVariable<int32> CVarAllowFrameTimestamps;` — Legacy pacer stuff
- L81 _public member_ `static TAutoConsoleVariable<int32> CVarTimeStampErrorRetryCount;`
- L82 _public member_ `static TAutoConsoleVariable<int32> CVarUseGetFrameTimestamps;`
- L83 _public member_ `static TAutoConsoleVariable<int32> CVarSpewGetFrameTimestamps;`
- L84 _public member_ `static TAutoConsoleVariable<float> CVarStallSwap;`
- L85 _public member_ `static TAutoConsoleVariable<int32> CVarDisableOpenGLGPUSync;`
- L89 _private member_ `static IAndroidFramePacer* FramePacer;` — The actual GL or Vulkan frame pacer
- L94 _private member_ `static int32 InternalFramePace;` — Actual current frame pace

#### Free symbols / members of external scopes

- L97 _typedef_ `typedef FAndroidPlatformRHIFramePacer FPlatformRHIFramePacer;`

### `Source/Runtime/ApplicationCore/Public/Android/AndroidPlatformSplash.h` (Public)


#### struct `FAndroidSplash`  
`struct FAndroidSplash : public FGenericPlatformSplash`  
_L13-16_
- inherits: `FGenericPlatformSplash`
- desc: Android splash implementation

#### Free symbols / members of external scopes

- L19 _typedef_ `typedef FAndroidSplash FPlatformSplash;`

### `Source/Runtime/ApplicationCore/Public/Android/AndroidPlatformSurvey.h` (Public)


#### struct `FAndroidPlatformSurvey`  
`struct FAndroidPlatformSurvey : public FGenericPlatformSurvey`  
_L14-17_
- inherits: `FGenericPlatformSurvey`
- desc: Android implementation of FGenericPlatformSurvey
- L16 _public prototype_ `static bool GetSurveyResults(FHardwareSurveyResults& OutResults, bool bWait=false);`

#### Free symbols / members of external scopes

- L19 _typedef_ `typedef FAndroidPlatformSurvey FPlatformSurvey;`

### `Source/Runtime/ApplicationCore/Public/Android/AndroidWindow.h` (Public)


#### class `FAndroidWindow`  
`class FAndroidWindow : public FGenericWindow, public TSharedFromThis<FAndroidWindow>`  
_L21-168_
- inherits: `FGenericWindow,TSharedFromThis<FAndroidWindow>`
- L24 _public prototype_ `~FAndroidWindow();`
- L31 _public prototype_ `static TSharedRef<FAndroidWindow> Make();` — Create a new FAndroidWindow. @param OwnerWindow		The SlateWindow for which we are crating a backing AndroidWindow @param InParent			Parent iOS window; usually NULL.
- L33 _public prototype_ `virtual void Destroy() override;`
- L35 _public function_ `virtual void* GetOSWindowHandle() const override`
- L37 _public prototype_ `void Initialize( class FAndroidApplication* const Application, const TSharedRef< FGenericWindowDefinition >& InDefinition, const TSharedPtr< FAndroidWindow >& InParent, const bool bShowImmediately );`
- L40 _public prototype_ `virtual bool GetFullScreenInfo( int32& X, int32& Y, int32& Width, int32& Height ) const override;` — Returns the rectangle of the screen the window is associated with
- L42 _public prototype_ `virtual void SetOSWindowHandle(void*);`
- L44 _public prototype_ `static FPlatformRect GetScreenRect(bool bUseEventThreadWindow = false);`
- L45 _public prototype_ `static void InvalidateCachedScreenRect();`
- L49 _public prototype_ `static void CalculateSurfaceSize(int32_t& SurfaceWidth, int32_t& SurfaceHeight, bool bUseEventThreadWindow = false);` — When bUseEventThreadWindow == false this uses dimensions cached when the game thread processes android events. When bUseEventThreadWindow == true this uses dimensions directly from the android event thread, unless called from event thread this requires acquiring GAndroidWindowLock to use.
- L50 _public prototype_ `static bool OnWindowOrientationChanged(EDeviceScreenOrientation DeviceScreenOrientation);`
- L52 _public prototype_ `static int32 GetDepthBufferPreference();`
- L54 _public prototype_ `static void AcquireWindowRef(ANativeWindow* InWindow);`
- L55 _public prototype_ `static void ReleaseWindowRef(ANativeWindow* InWindow);`
- L58 _public prototype_ `static void* GetHardwareWindow_EventThread();` — This returns the current hardware window as set from the event thread.
- L59 _public prototype_ `static void SetHardwareWindow_EventThread(void* InWindow);`
- L64 _public prototype_ `static void* WaitForHardwareWindow();` — Waits on the current thread for a hardware window and returns it. May return nullptr if the application is shutting down.
- L66 _public prototype_ `static bool IsPortraitOrientation();`
- L67 _public prototype_ `static FVector4 GetSafezone(bool bPortrait);`
- L70 _public prototype_ `static void SetWindowDimensions_EventThread(ANativeWindow* DimensionWindow);` — called by the Android event thread to initially set the current window dimensions.
- L73 _public prototype_ `static void EventManagerUpdateWindowDimensions(int32 Width, int32 Height);` — Called by the event manager to update the cached window dimensions to match the event it is processing.
- L75 _public prototype_ `bool GetNativeWindowResolution(int32_t& OutWidth, int32_t& OutHeight) const;`
- L77 _public function_ `virtual void SetWindowMode(EWindowMode::Type InNewWindowMode)`
- L136 _public function_ `FNativeAccessor GetANativeAccessor(bool bWriteAccess)`
- L143 _protected function_ `virtual EWindowMode::Type GetWindowMode() const override` — @return true if the native window is currently in fullscreen mode, false otherwise
- L146 _private member_ `ANativeWindow* CurrentANativeHandle = nullptr;`
- L147 _private member_ `ANativeWindow* PreviousANativeHandle = nullptr;`
- L148 _private member_ `UE::FSharedMutex ANativeHandleMutex;`
- L149 _private member_ `EWindowMode::Type WindowMode = EWindowMode::Fullscreen;`
- L154 _private prototype_ `FAndroidWindow();` — Protect the constructor; only TSharedRefs of this class can be made.
- L156 _private member_ `FAndroidApplication* OwningApplication;`
- L158 _private member_ `static void* NativeWindow;`
- L161 _private prototype_ `static bool WaitForWindowDimensions();` — Waits for the event thread to report an initial window size.
- L163 _private member_ `static bool bAreCachedNativeDimensionsValid;`
- L164 _private member_ `static int32 CachedNativeWindowWidth;`
- L165 _private member_ `static int32 CachedNativeWindowHeight;`

#### class `FAndroidWindow::FNativeAccessor`  
`class FNativeAccessor`  
_L79-134_
- L81 _private member_ `bool bWriteAccess;`
- L82 _private member_ `class FAndroidWindow* ProtectedObj = nullptr;`
- L83 _private function_ `FNativeAccessor()`
- L85 _public function_ `FNativeAccessor(FNativeAccessor&& obj)`
- L92 _public prototype_ `FNativeAccessor(const FNativeAccessor&) = delete;`
- L93 _public function_ `FNativeAccessor(bool bWriteAccessIn, FAndroidWindow* ProtectedObjIn) : bWriteAccess(bWriteAccessIn), ProtectedObj(ProtectedObjIn)`
- L105 _public function_ `~FNativeAccessor()`
- L120 _public function_ `FAndroidWindow* Get()`
- L121 _public function_ `const FAndroidWindow* Get() const`
- L123 _public function_ `FAndroidWindow* operator ->()`
- L124 _public function_ `const FAndroidWindow* operator ->() const`
- L126 _public function_ `void SetANativeWindow(ANativeWindow* ANativeHandle)`
- L132 _public function_ `ANativeWindow* GetANativeWindow() const`
- L133 _public function_ `ANativeWindow* GetPreviousANativeWindow() const`

#### class `FAndroidWindowManager`  
`class FAndroidWindowManager`  
_L170-255_
- L176 _public function_ `static FAndroidWindowManager& Get()`
- L182 _public function_ `TOptional<FAndroidWindow::FNativeAccessor> GetMainWindowAsNativeAccessor(bool bWriteAccess)`
- L195 _public function_ `TOptional<FAndroidWindow::FNativeAccessor > FindFromANativeWindow(bool bWriteAccess, bool bSearchPrevious, const void* SearchANativeHandle)`
- L233 _public function_ `static FPendingWindowAccessor GetPendingWindowAccessor()`
- L239 _private member_ `TArray< TSharedRef<FAndroidWindow>> Windows;`
- L241 _private function_ `int AddWindow(TSharedRef<FAndroidWindow> AddMe)`
- L248 _private function_ `void RemoveWindow(TSharedRef<FAndroidWindow> RemoveMe)`
- L254 _private member_ `mutable UE::FMutex WindowManagerLock;`

#### class `FAndroidWindowManager::FPendingWindowAccessor`  
`class FPendingWindowAccessor`  
_L212-231_
- desc: Android native window handling. this is used to collect the native window before the game has created its own FAndroidWindow.
- L214 _private member_ `static inline ANativeWindow* PreviousPendingANativeWindow = nullptr;`
- L215 _private member_ `static inline ANativeWindow* PendingANativeWindow = nullptr;`
- L216 _private member_ `static inline UE::FMutex Lock;`
- L217 _private prototype_ `FPendingWindowAccessor(const FPendingWindowAccessor&) = delete;`
- L218 _private prototype_ `FPendingWindowAccessor(FPendingWindowAccessor&&) = delete;`
- L220 _public function_ `FPendingWindowAccessor()`
- L221 _public function_ `~FPendingWindowAccessor()`
- L223 _public function_ `void SetANativeWindow(ANativeWindow* ANativeHandle)`
- L229 _public function_ `ANativeWindow* GetPreviousANativeWindow() const`
- L230 _public function_ `ANativeWindow* GetANativeWindow() const`

### `Source/Runtime/ApplicationCore/Public/Android/AndroidWindowUtils.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace AndroidWindowUtils`
- L18 _function_ `FIntVector2 SanitizeAndroidScreenSize(const FIntVector2&& MaxScreenDims, const FIntVector2&& RequestedScreenDims)` (scope `AndroidWindowUtils`)
- L31 _function_ `void ApplyContentScaleFactor(int32& InOutScreenWidth, int32& InOutScreenHeight)` (scope `AndroidWindowUtils`)

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/Accessibility/GenericAccessibleInterfaces.h` (Public)


#### enum `EAccessibleBehavior`  
`enum class EAccessibleBehavior : uint8`  
_L21-33_
- desc: Whether a widget should be included in accessibility, and if so, how its text should be retrieved.
- L24 _public enumerator_ `NotAccessible` — Not accessible.
- L26 _public enumerator_ `Auto` — Accessible, for the implementing library to decide what it means. Given all data about a particular widget, it should try to choose the most-relevant text automatically.
- L28 _public enumerator_ `Summary` — Accessible, and traverse all child widgets and concat their summary text together.
- L30 _public enumerator_ `Custom` — Accessible, and retrieve manually-assigned text from a TAttribute.
- L32 _public enumerator_ `ToolTip` — Accessible, and use the tooltip's accessible text.

#### enum `EAccessibleWidgetType`  
`enum class EAccessibleWidgetType : uint8`  
_L45-61_
- desc: What kind of widget to tell the operating system this is. This may be translated to a different type depending on the platform.
- L47 _public enumerator_ `Unknown`
- L48 _public enumerator_ `Button`
- L49 _public enumerator_ `CheckBox`
- L50 _public enumerator_ `ComboBox`
- L51 _public enumerator_ `Hyperlink`
- L52 _public enumerator_ `Image`
- L53 _public enumerator_ `Layout`
- L54 _public enumerator_ `ScrollBar`
- L55 _public enumerator_ `Slider`
- L56 _public enumerator_ `Text`
- L57 _public enumerator_ `TextEdit`
- L58 _public enumerator_ `Window`
- L59 _public enumerator_ `List`
- L60 _public enumerator_ `ListItem`

#### enum `EAccessibleEvent`  
`enum class EAccessibleEvent : uint8`  
_L64-97_
- desc: Events that can be raised from accessible widgets to report back to the platform
- L71 _public enumerator_ `FocusChange` — A widget has become focused or unfocused. OldValue - The old focus state of the widget NewValue - The new focus state of the widget
- L77 _public enumerator_ `Activate` — A widget has been clicked, checked, or otherwise activated. OldValue - N/A NewValue - N/A
- L84 _public enumerator_ `Notification` — Warning: Partial implementation Notify the user that something has happened. The user is not guaranteed to get this message. OldValue - N/A NewValue - An FString of the message to read
- L90 _public enumerator_ `ParentChanged` — A widget's parent is about to be changed. OldValue - The AccessibleWidgetId of the old parent, or InvalidAccessibleWidgetId if there was none NewValue - The AccessibleWidgetId of the new parent, or InvalidAccessibleWidgetId if there was none
- L96 _public enumerator_ `WidgetRemoved` — The widget was removed from the UI tree or deleted. OldValue - N/A NewValue - N/A

#### class `FGenericAccessibleUser`  
`class FGenericAccessibleUser`  
_L109-169_
- desc: An accessible user is an input source that can interact with the application and needs to provide accessibility services such as a screen reader. This base class provides the basic information all accessible users need to implement to ensure accessibility services function properly. Users should subclass this class to provide additional functionality for their custom accessible users. All accessible users must be registered with an FGenericAccessibleUserRegistry for the users to be retrieved and interacted with. @see FGenericAccessibleUserRegistry
- L113 _public function_ `FGenericAccessibleUser(const FAccessibleUserIndex InUserIndex) : UserIndex(InUserIndex)`
- L118 _public prototype_ `virtual ~FGenericAccessibleUser() = default;`
- L120 _public function_ `FAccessibleUserIndex GetIndex() const` — Returns the unique index that identifies this accessible user.
- L128 _public function_ `TSharedPtr<IAccessibleWidget> GetFocusedAccessibleWidget() const` — Returns the accessible widget the accessible user is currently focused on. If no accessible widget is focused, nullptr is returned. @see IAccessibleWidget
- L142 _public function_ `bool SetFocusedAccessibleWidget(const TSharedRef<IAccessibleWidget>& InWidget)` — Sets which accessible widget the accessible user is currently focused on. Note: This function is meant to directly set the widget an accessible user is focused on, bypassing all of the focus change accessible events. This should only be used by FGenericAccessibleMessageHandler and its subclasses to update the  the accessible focus for an accessible user. Most of the time, you want to use IAccessibleWidget::SetUserFocus to request an accessible widget be focused on by a user. It raises the appropriate accessible events so listeners for accessible events can do the appropriate event handling for the focus change event. @param InWidget The widget this accessible user will be focused on. @return True if the passed in widget was successfully set. Else returns false.
- L148 _public function_ `void ClearFocusedAccessibleWidget()` — Clear the accessible focused widget.
- L157 _protected function_ `virtual void OnRegistered()` — Called by FGenericAccessibleUserRegistry::RegisterUser. @see FGenericAccessibleUserRegistry
- L162 _protected function_ `virtual void OnUnregistered()` — Called by FGenericAccessibleUserRegistry::UnregisterUser. @see FGenericAccessibleUserRegistry
- L166 _private member_ `FAccessibleUserIndex UserIndex;` — The unique index for this accessible user
- L168 _private member_ `TWeakPtr<IAccessibleWidget> FocusedAccessibleWidget;` — The focused accessible widget widget associated with this user.

#### class `FGenericAccessibleUserRegistry`  
`class FGenericAccessibleUserRegistry`  
_L179-229_
- desc: The base class for an accessible user registry that all accessible users must register with. The registry controls the lifetime of all accessible users. All created accessible users must be registered with an accessible user registry. This should be the only means of retrieving and interacting with accessible users in other parts of the application. Users can subclass this class to provide additional functionality for their custom use cases. @see FGenericAccessibleUser, FGenericAccessibleMessageHandler
- L182 _public prototype_ `virtual ~FGenericAccessibleUserRegistry() = default;`
- L192 _public prototype_ `bool RegisterUser(const TSharedRef<FGenericAccessibleUser>& User);` — Registers an accessible user with the accessible registry. It is up to the caller to ensure that the passed in user has the correct user index. The passed in user will not be registered if another user with the same user index has already been registered. This function calls FGenericAccessibleUser::OnRegistered if the passed in user is successfully registered. Once an accessible user has been successfully registered, it can be retrieved and interacted with by the rest of the application. @param User An accessible user you want to register with the accessible user registry. @return True if the passed in user was successfully registered. Else, returns false.
- L201 _public prototype_ `bool UnregisterUser(const FAccessibleUserIndex UserIndex);` — Unregisters an accessible user from the accessible registry. If the passed in user index is not associated with a registered accessible user, nothing will happen. This function calls FGenericAccessibleUser::OnUnregistered if the passed in user is successfully unregistered. Once an accessible user has been unregistered, the rest of the application should have no way of retrieving or interacting with the accessible user. @param UserIndex The index of the accessible user you want to unregister. @return True if the accessible user with the associated user index is successfully unregistered. Else, returns false.
- L206 _public prototype_ `void UnregisterAllUsers();` — Unregisters all accessible users from the accessible registry. This function calls FGenericAccessibleUser::OnUnregistered when each registered user is successfully unregistered.
- L208 _public prototype_ `bool IsUserRegistered(const FAccessibleUserIndex UserIndex) const;` — Returns true if the passed in user index is associated with a registered accessible user. Else, returns false.
- L210 _public prototype_ `TSharedPtr<FGenericAccessibleUser> GetUser(const FAccessibleUserIndex UserIndex) const;` — Returns the accessible user associated with the passed in user index. If the passed in user index is not associated with any accessible user, nullptr is returned.
- L212 _public prototype_ `int32 GetNumberofUsers() const;` — Returns the number of accessible users registered with the accessible user registry.
- L214 _public prototype_ `TArray<TSharedRef<FGenericAccessibleUser>> GetAllUsers() const;` — Returns an array of all accessible users that are currently registered with the accessible registry.
- L220 _public function_ `static FAccessibleUserIndex GetPrimaryUserIndex()` — Returns the index of the primary accessible user. The primary accessible user should correspond to the default input source that every application should have. This user should also be the primary cursor user. E.g On desktop platforms, that would correspond to the keyboard user.
- L228 _protected member_ `TMap<FAccessibleUserIndex, TSharedRef<FGenericAccessibleUser>> UsersMap;` — A map of accessible user indices to their associated accessible users.

#### class `IAccessibleWindow`  
`class IAccessibleWindow`  
_L235-302_
- desc: An accessible window corresponds to a native OS window. Fake windows that are embedded within other widgets that simply look and feel like windows are not IAccessibleWindows.
- L252 _public prototype_ `virtual TSharedPtr<FGenericWindow> GetNativeWindow() const = 0;` — Retrieve the native OS window backing this accessible window. This can be safely casted if you know what OS you're in (ie FWindowsWindows on Windows platform). @return The native window causing this accessible window to exist
- L263 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetChildAtPosition(int32 X, int32 Y) = 0;` — Finds the deepest accessible widget in the hierarchy at the specified coordinates. The window may return a pointer to itself in the case where there are no accessible children at the position. This could return nullptr in the case where the coordinates are outside the window bounds. @param X The X coordinate in absolute screen space @param Y The Y coordinate in absolute screen space @return The deepest widget in the UI heirarchy at X,Y
- L271 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetUserFocusedWidget(const FAccessibleUserIndex UserIndex) const = 0;` — Retrieves the focused accessible widget for a user. If the passed in user index is not registered with an accessible user registry, nullptr will be returned. @param UserIndex The user index of the accessible user to query for its accessible focus widget. @return The accessible widget that is focused by the accessible user. Returns nullptr if the accessible user index does not correspond to a registered accessible user.
- L275 _public prototype_ `virtual void Close() = 0;` — Request that the window closes itself. This may not happen immediately.
- L283 _public prototype_ `virtual bool SupportsDisplayState(EWindowDisplayState State) const = 0;` — Check if the window can be minimized or maximized. @param State Whether to check for minimize or maximize. @return True if the display state can be switched to, otherwise false.
- L289 _public prototype_ `virtual EWindowDisplayState GetDisplayState() const = 0;` — Gets the current state minimize/maximize state of the window. @return The display state corresponding to how the window is displayed.
- L295 _public prototype_ `virtual void SetDisplayState(EWindowDisplayState State) = 0;` — Sets a window to be minimized, maximized, or restored to normal. @param State What to change the window's display to.
- L301 _public prototype_ `virtual bool IsModal() const = 0;` — Whether or not the window is modal. @return true if the window is modal, otherwise false.

#### enum `IAccessibleWindow::EWindowDisplayState`  
`enum class EWindowDisplayState`  
_L239-244_
- desc: The different states a window can be in to describe its screen anchors
- L241 _public enumerator_ `Normal`
- L242 _public enumerator_ `Minimize`
- L243 _public enumerator_ `Maximize`

#### class `IAccessibleActivatable`  
`class IAccessibleActivatable`  
_L307-325_
- desc: A widget that can be triggered to fire an event, such as buttons or checkboxes.
- L311 _public prototype_ `virtual void Activate() = 0;` — Trigger the widget
- L317 _public function_ `virtual bool IsCheckable() const` — Check whether this widget can be toggled between various check states @return true if this widget supports being in different states
- L324 _public function_ `virtual bool GetCheckedState() const` — If IsCheckable() is true, this gets the current state that the widget is in. //todo: return ECheckState @return true if the current state is considered "on" or "checked"

#### class `IAccessibleProperty`  
`class IAccessibleProperty`  
_L331-386_
- desc: An accessible widget that stores an arbitrary value of any type capable of being serialized into a string. Optional overrides add support for slider-like functionality.
- L339 _public function_ `virtual bool IsReadOnly() const` — Whether the widget is in read-only mode, which could be different than IsEnabled(). @return true if the widget is in read-only mode.
- L345 _public function_ `virtual bool IsPassword() const` — Check if this text is storing password data, indicating that it may need special handling to presenting itself to the user. @return true if the text is storing a password or otherwise senstive data that should be hidden.
- L352 _public function_ `virtual float GetStepSize() const` — How much the value should increase/decrease when the user attempts to modify the value using UI controls. Note: This should always return a positive value. The caller is responsible for negating it when attempting to decrease. @return A number suggesting how much to modify GetValue() by when the user wants to increase/decrease the value.
- L358 _public function_ `virtual float GetMaximum() const` — The maximum allowed value for this property. This should only be used if GetStepSize is not 0. @return The maximum value that this property can be assigned when using step sizes.
- L364 _public function_ `virtual float GetMinimum() const` — The minimum allowed value for this property. This should only be used if GetStepSize is not 0. @return The minimum value that this property can be assigned when using step sizes.
- L371 _public prototype_ `virtual FString GetValue() const = 0;` — The current value stored by the widget. Even if the underlying value is not a String, it should be serialized to one in order to match the return type. @return A string representing the serialized value stored in the widget.
- L377 _public function_ `virtual FVariant GetValueAsVariant() const` — The current value stored by the widget as a FVariant. Used on platforms where the type of the value is important for accessibility methods such as on Mac. . @return An FVariant that holds the widget's current value and type of value.
- L385 _public function_ `virtual void SetValue(const FString& Value)` — Set the value stored by the widget. While this function accepts a String, there is no way to know what the underlying data is stored as. The platform layer must retain some additional information about what kind of widget this is, and ensure it's being called with valid arguments. @param Value The new value to assign to the widget, which may need to be converted before assigning to a variable.

#### class `IAccessibleText`  
`class IAccessibleText`  
_L392-401_
- desc: A widget that contains text, with the potential ability to select sections, read specific words/paragraphs, etc. Note: This class is currently incomplete.
- L400 _public prototype_ `virtual const FString& GetText() const = 0;` — Get the full text contained in this widget, even if some if it is clipped. @return All the text held by this widget.

#### class `IAccessibleTable`  
`class IAccessibleTable`  
_L407-430_
- desc: A widget that represents a table such as list views, tile views or tree views Data about the items that are selected in the table or if selection is supported can be queried.
- L415 _public function_ `virtual TArray<TSharedPtr<IAccessibleWidget>> GetSelectedItems() const` — Get all of the elements that are selected in the table. @return All the items selected in this table. Returns an empty array if nothing is selected.
- L422 _public function_ `virtual bool CanSupportMultiSelection() const` — Check if the table can select more than one element at a time. @return True if the table can support selection for more than one element at a time. Else false.
- L429 _public function_ `virtual bool IsSelectionRequired() const` — Checks if the table must have an element selected at all times. @return True if an element of the table must be selected at all times, else false

#### class `IAccessibleTableRow`  
`class IAccessibleTableRow`  
_L437-463_
- desc: A widget that is an element in an accessible table. These widgets can be interacted with by selecting them or querying them for the owning table. NOTE: All accessible table rows must have an accessible table as an owner
- L441 _public function_ `virtual void Select()` — Selects this table row in the owning table.
- L444 _public function_ `virtual void AddToSelection()` — Adds this table row to the list of selected items in the owning table
- L447 _public function_ `virtual void RemoveFromSelection()` — Removes this table row from the list of selected items in the owning table
- L454 _public function_ `virtual bool IsSelected() const` — Checks if this table row is currently selected in the owning table. @return True if this table row is currently selected in the owning table. Else false
- L462 _public function_ `virtual TSharedPtr<IAccessibleWidget> GetOwningTable() const` — Get the accessible table that owns this accessible table row. NOTE: This should always return a valid pointer in concrete classes. An accessible table row must ALWAYS have an accessible table as an owner. @return The owning table

#### class `IAccessibleWidget`  
`class IAccessibleWidget : public TSharedFromThis<IAccessibleWidget>`  
_L472-824_
- inherits: `TSharedFromThis<IAccessibleWidget>`
- desc: Provides the core set of accessible data that is necessary in order for widget traversal and TTS to be implemented. In order to support functionality beyond this, subclasses must implement the other accessible interfaces and then override the As*() functions.
- L475 _public function_ `IAccessibleWidget()`
- L476 _public prototype_ `virtual ~IAccessibleWidget() = default;`
- L478 _public member_ `static const AccessibleWidgetId InvalidAccessibleWidgetId = -1;`
- L486 _public prototype_ `virtual AccessibleWidgetId GetId() const = 0;` — Get an application-unique identifier for this widget. If the widget is destroyed, a different widget is allowed to re-use that ID. @return A unique ID that specifically refers to this widget.
- L492 _public prototype_ `virtual bool IsValid() const = 0;` — Whether or not the underlying widget backing this interface still exists @return true if functions can be called on this interface and should return valid results
- L500 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetWindow() const = 0;` — Returns the window at the top of this widget's hierarchy. This function may return itself for accessible windows, and could return nullptr in cases where the widget is not currently part of a hierarchy. @return The root window in this widget's widget tree, or nullptr if there is no window.
- L506 _public prototype_ `virtual FBox2D GetBounds() const = 0;` — Retrieving the bounding rect in absolute coordinates for this widget. On some platforms this may be used for hit testing. @return The bounds of the widget.
- L513 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetParent() = 0;` — Get the accessible parent of this widget. This may be nullptr if this widget is a window, or if the widget is currently disconnected from the UI tree. @return The accessible parent widget of this widget.
- L524 _public function_ `template<typename PredicateType> static TSharedPtr<IAccessibleWidget> SearchForAncestorFrom(const TSharedRef<IAccessibleWidget>& Source, PredicateType Predicate)` — Returns the first instance of an ancestor from a source widget that satisfies a search criteria. If the passed in source widget does not have any ancestors or if there are no ancestors that satisfy the search criteria, nullptr is returned. The search criteria can be either a functor or lambda that acts as a predicate. It must return a bool and take in a const TSharedRef<IAccessibleWidget>& as an argument. @param Source The accessible widget to start searching from. @param SearchCriteria A predicate that takes a const TSharedRef<IAccessibleWidget>& as an argument and returns true if the passed in widget satisfies the search criteria. When an accessible widget that satisfies the SearchCriteria is found, it is returned by the function. @return The first instance of an ancestor from the source widget that satisfies the search criteria.
- L542 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetNextSibling() = 0;` — Retrieves the widget after this one in the parent's list of children. This should return nullptr for the last widget. @return The next widget on the same level of the UI hierarchy.
- L553 _public function_ `template<typename PredicateType> static TSharedPtr<IAccessibleWidget> SearchForNextSiblingFrom(const TSharedRef<IAccessibleWidget>& Source, PredicateType Predicate)` — Returns the first instance of a next sibling from a source widget that satisfies a search criteria. If the passed in source widget does not have any next siblings or if there are no next siblings that satisfy the search criteria, nullptr is returned. The search criteria can be either a functor or lambda that acts as a predicate. It must return a bool and take in a const TSharedRef<IAccessibleWidget>& as an argument. @param Source The accessible widget to start searching from. @param SearchCriteria A predicate that takes a const TSharedRef<IAccessibleWidget>& as an argument and returns true if the passed in widget satisfies the search criteria. When an accessible widget that satisfies the SearchCriteria is found, it is returned by the function. @return The first instance of a next sibling from the source widget that satisfies the search criteria.
- L571 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetPreviousSibling() = 0;` — Retrieves the widget before this one in the parent's list of children. This should return nullptr for the first widget. @return The previous widget on the same level of the UI hierarchy.
- L582 _public function_ `template<typename PredicateType> static TSharedPtr<IAccessibleWidget> SearchForPreviousSiblingFrom(const TSharedRef<IAccessibleWidget>& Source, PredicateType Predicate)` — Returns the first instance of a previous sibling from a source widget that satisfies a search criteria. If the passed in source widget does not have any previous siblings or if there are no previous siblings that satisfy the search criteria, nullptr is returned. The search criteria can be either a functor or lambda that acts as a predicate. It must return a bool and take in a const TSharedRef<IAccessibleWidget>& as an argument. @param Source The accessible widget to start searching from. @param SearchCriteria A predicate that takes a const TSharedRef<IAccessibleWidget>& as an argument and returns true if the passed in widget satisfies the search criteria. When an accessible widget that satisfies the SearchCriteria is found, it is returned by the function. @return The first instance of a previous sibling from the source widget that satisfies the search criteria.
- L606 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetNextWidgetInHierarchy() = 0;` — Retrieves the logical next widget in the accessible widget hierarchy from this widget. This is conceptually similar to tab navigation with the keyboard. This is primarily used for mobile devices to simulate the right swipe gesture for IOS Voiceover or Android Talkback. An example algorithm to find the next widget in the accessible hierarchy is as follows: 1. If the current widget has children, return the first child. 2. If the current widget has no children, return the sibling of the current widget. 3. If the current widget has no next sibling, search for the first ancestor from the current widget with a next sibling. Return that ancestor's next sibling. @return The logical next widget in the accessible widget hierarchy.
- L617 _public function_ `template<typename PredicateType> static TSharedPtr<IAccessibleWidget> SearchForNextWidgetInHierarchyFrom(const TSharedRef<IAccessibleWidget>& Source, PredicateType Predicate)` — Returns the first instance of a next widget in the accessible hierarchy from a source widget that satisfies a search criteria. If the passed in source widget does not have any next widgets or if there are no next widgets that satisfy the search criteria, nullptr is returned. The search criteria can be either a functor or lambda that acts as a predicate. It must return a bool and take in a const TSharedRef<IAccessibleWidget>& as an argument. @param Source The accessible widget to start searching from. @param SearchCriteria A predicate that takes a const TSharedRef<IAccessibleWidget>& as an argument and returns true if the passed in widget satisfies the search criteria. When an accessible widget that satisfies the SearchCriteria is found, it is returned by the function. @return The first instance of a next widget from the source widget that satisfies the search criteria.
- L642 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetPreviousWidgetInHierarchy() = 0;` — Retrieves the logical previous widget in the accessible widget hierarchy from this current widget. This is conceptually similar to shift tab navigation with the keyboard. This is primarily used for mobile devices to simulate the left swipe gesture for IOS Voiceover or Android Talkback. An example algorithm to find the previous widget in the hierarchy is as follows: 1. Find the previous sibling of the current widget and check if it has children. 2. If the previous sibling has children, we will call the last child of the previous sibling C. Recursively take the last child from C until a leaf is found. Return the leaf. 3. If the previous sibling has no children, return the previous sibling. 4. If the current widget has no previous sibling, we return the parent of the current widget. @return The logical previous widget in the accessible widget hierarchy.
- L653 _public function_ `template<typename PredicateType> static TSharedPtr<IAccessibleWidget> SearchForPreviousWidgetInHierarchyFrom(const TSharedRef<IAccessibleWidget>& Source, PredicateType Predicate)` — Returns the first instance of a previous widget in the accessible hierarchy from a source widget that satisfies a search criteria. If the passed in source widget does not have any previous widgets or if there are no previous widgets that satisfy the search criteria, nullptr is returned. The search criteria can be either a functor or lambda that acts as a predicate. It must return a bool and take in a const TSharedRef<IAccessibleWidget>& as an argument. @param Source The accessible widget to start searching from. @param SearchCriteria A predicate that takes a const TSharedRef<IAccessibleWidget>& as an argument and returns true if the passed in widget satisfies the search criteria. When an accessible widget that satisfies the SearchCriteria is found, it is returned by the function. @return The first instance of a previous widget from the source widget that satisfies the search criteria.
- L672 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetChildAt(int32 Index) = 0;` — Retrieves the accessible child widget at a certain index. This should return nullptr if Index < 0 or Index >= GetNumberOfChildren(). @param The index of the child widget to get @return The accessible child widget at the specified index.
- L678 _public prototype_ `virtual int32 GetNumberOfChildren() = 0;` — How many accessible children this widget has. @return The number of accessible children that exist for this widget.
- L689 _public function_ `template<typename PredicateType> static TSharedPtr<IAccessibleWidget> SearchForFirstChildFrom(const TSharedRef<IAccessibleWidget>& Source, PredicateType Predicate)` — Returns the first instance of a child from a source widget that satisfies a search criteria. If the passed in source widget does not have any children or if there are no children that satisfy the search criteria, nullptr is returned. The search criteria can be either a functor or lambda that acts as a predicate. It must return a bool and take in a const TSharedRef<IAccessibleWidget>& as an argument. @param Source The accessible widget to start searching from. @param SearchCriteria A predicate that takes a const TSharedRef<IAccessibleWidget>& as an argument and returns true if the passed in widget satisfies the search criteria. When an accessible widget that satisfies the SearchCriteria is found, it is returned by the function. @return The first child from the source widget that satisfies the search criteria.
- L713 _public prototype_ `virtual EAccessibleWidgetType GetWidgetType() const = 0;` — What type of accessible widget the underlying widget should be treated as. A widget may be capable of presenting itself as multiple different types of widgets, but only one can be reported back to the platform. @return Which type of widget the platform layer should treat this as.
- L720 _public prototype_ `virtual FString GetClassName() const = 0;` — The name of the underlying class that this accessible widget represents. @return The class name of the underlying widget.
- L726 _public prototype_ `virtual FString GetWidgetName() const = 0;` — The name of the widget to report to the platform layer. For screen readers, this is often the text that will be spoken. @return Ideally, a human-readable name that represents what the widget does.
- L732 _public prototype_ `virtual FString GetHelpText() const = 0;` — Additional information a user may need in order to effectively interact or use the widget, such as a tooltip. @return A more-detailed description of what the widget is or how its used.
- L734 _public function_ `virtual FString ToString() const` — Returns a string representation of this widget. Primarily used for debugging.
- L746 _public prototype_ `virtual bool IsEnabled() const = 0;` — Whether the widget is enabled and can be interacted with. @return true if the widget is enabled.
- L752 _public prototype_ `virtual bool IsHidden() const = 0;` — Whether the widget is being rendered on screen or not. @return true if the widget is hidden off screen, collapsed, or something similar.
- L758 _public prototype_ `virtual bool SupportsFocus() const = 0;` — Whether the widget can ever support keyboard/gamepad focus. @return true if the widget can ever receive keyboard/gamepad focus. Else, returns false.
- L764 _public prototype_ `virtual bool SupportsAccessibleFocus() const = 0;` — Whether the widget can ever support accessible focus. @return true if the widget can ever receive accessible focus. Else, returns false.
- L770 _public prototype_ `virtual bool CanCurrentlyAcceptAccessibleFocus() const = 0;` — Whether the widget can currently support accessible focus. @return true if the widget can currently receive accessible focus. Else, returns false.
- L777 _public prototype_ `virtual bool HasUserFocus(const FAccessibleUserIndex UserIndex) const = 0;` — Whether the widget has accessible focus or not by a particular user . @param UserIndex The user index associated with the accessible user to query if this accessible widget is currently being focused. @return true if the widget currently has accessible focus by the user. Else, returns false.
- L784 _public prototype_ `virtual bool SetUserFocus(const FAccessibleUserIndex UserIndex) = 0;` — Assign accessible focus to the widget. Also sets keyboard/gamepad focus if the widget supports it. @param UserIndex The user index associated with the accessible user that requested focus for this accessible widget. @return True if focus was successfully set to this widget for the requested user. Else false.
- L791 _public function_ `virtual IAccessibleWindow* AsWindow()` — Attempt to cast this to an IAccessibleWindow @return 'this' as an IAccessibleWindow if possible, otherwise nullptr
- L797 _public function_ `virtual IAccessibleActivatable* AsActivatable()` — Attempt to cast this to an IAccessibleActivatable @return 'this' as an IAccessibleActivatable if possible, otherwise nullptr
- L803 _public function_ `virtual IAccessibleProperty* AsProperty()` — Attempt to cast this to an IAccessibleProperty @return 'this' as an IAccessibleProperty if possible, otherwise nullptr
- L809 _public function_ `virtual IAccessibleText* AsText()` — Attempt to cast this to an IAccessibleText @return 'this' as an IAccessibleText if possible, otherwise nullptr
- L816 _public function_ `virtual IAccessibleTable* AsTable()` — Attempt to cast this to an IAccessibleTable @return 'this' as an IAccessibleTable if possible, otherwise nullptr
- L823 _public function_ `virtual IAccessibleTableRow* AsTableRow()` — Attempt to cast this to an IAccessibleTableRow @return 'this' as an IAccessibleTableRow if possible, otherwise nullptr

#### struct `FAccessibleEventArgs`  
`struct FAccessibleEventArgs`  
_L832-852_
- desc: The arguments for an accessible event that is raised by accessible widgets to be passed to an accessibility event handler such as a native OS. It is up to the client to create an instance of this struct and fill in the appropriate data members. @see FGenericAccessibleMessageHandler::RaiseEvent
- L834 _public function_ `FAccessibleEventArgs(TSharedRef<IAccessibleWidget> InWidget, EAccessibleEvent InEvent, FVariant InOldValue = FVariant(), FVariant InNewValue = FVariant(), FAccessibleUserIndex InUserIndex = 0) : Widget(InWidget) , Event(InEvent) , OldValue(InOldValue) , NewValue(InNewValue) , UserIndex(InUserIndex)`
- L843 _public member_ `TSharedRef<IAccessibleWidget> Widget;` — The accessible widget that generated the event
- L845 _public member_ `EAccessibleEvent Event;` — The type of event generated
- L847 _public member_ `FVariant OldValue;` — If this was a property changed event, the 'before' value
- L849 _public member_ `FVariant NewValue;` — If this was a property changed event, the 'after' value. This may also be set for other events such as Notification.
- L851 _public member_ `FAccessibleUserIndex UserIndex;` — The Id of the user this event is intended for. Think of a hardware device such as a controller or keyboard/mouse.

#### class `FGenericAccessibleMessageHandler`  
`class FGenericAccessibleMessageHandler`  
_L869-1021_
- desc: Platform and application-agnostic messaging system for accessible events. The message handler lives in GenericApplication and any subclass that wishes to support accessibility should subclass this and use GenericAppliation::SetAccessibleMessageHandler to enable functionality. GetAccessibleWindow() is the entry point to all accessible widgets. Once the window is retrieved, it can be queried for children in various ways. RaiseEvent() allows messages to bubble back up to the native OS through anything bound to the AccessibleEventDelegate. Callers can use ApplicationIsAccessible() to see if accessibility is supported or not. Alternatively, calling GetAccessibleWindow and seeing if the result is valid should provide the same information. Callers should also use GetAccessibleUserRegistry() to register and interact with accessible users. Accessible users must be registered with the set accessible user registry for the rest of the application to be able to retrieve and interact with the accessible users.
- L876 _public prototype_ `DECLARE_DELEGATE_OneParam(FAccessibleEvent, const FAccessibleEventArgs&);` — A delegate accessible event handlers such as platform accessibility APIs can listen for accessibility events raised by widgets.  .
- L878 _public prototype_ `FGenericAccessibleMessageHandler();`
- L879 _public function_ `virtual ~FGenericAccessibleMessageHandler()`
- L889 _public prototype_ `bool ApplicationIsAccessible() const;` — Subclasses should return true to indicate that they support accessibility. @return true if the application intends to return valid accessible widgets when queried.
- L897 _public function_ `bool IsActive() const` — Checks if accessibility is enabled in the application. Usually this happens when screen-reading software is turned on. Note: On some platforms, there is no way to deactivate this after enabling it. @return The last value SetActive() was called with.
- L904 _public prototype_ `void SetActive(bool bActive);` — Notify the application to start or stop processing accessible messages from the platform layer. @param bActive Whether to enable to disable the message handler.
- L913 _public function_ `virtual TSharedPtr<IAccessibleWidget> GetAccessibleWindow(const TSharedRef<FGenericWindow>& InWindow) const` — Creates or retrieves an accessible object for a native OS window. todo: Behavior for non-native windows (virtual or others) is currently undefined. @param InWindow The native window to find the accessible window for @return The accessible object corresponding to the supplied native window
- L922 _public function_ `virtual AccessibleWidgetId GetAccessibleWindowId(const TSharedRef<FGenericWindow>& InWindow) const` — Creates or retrieves the identifier for an accessible object for a native OS window. todo: Behavior for non-native windows (virtual or others) is currently undefined. @param InWindow The native window to find the accessible window for @return The identifier for the accessible window created
- L930 _public function_ `virtual TSharedPtr<IAccessibleWidget> GetAccessibleWidgetFromId(AccessibleWidgetId Id) const` — Retrieves an accessible widget that matches the given identifier. @param Id The identifier for the widget to get. @return The widget that matches this identifier, or nullptr if the widget does not exist.
- L938 _public function_ `void RaiseEvent(const FAccessibleEventArgs& Args)` — Push an event from an accessible widget back to the platform layer. @param Args The arguments to be passed to the accessible event delegate. @see FAccessibleEventArgs
- L948 _public function_ `void SetAccessibleEventDelegate(const FAccessibleEvent& Delegate)` — Assign a function to be called whenever an accessible event is raised. @param Delegate The delegate to execute when an event is raised.
- L956 _public function_ `void UnbindAccessibleEventDelegate()` — Unbinds the delegate called during accessible events if it is bound.
- L969 _public function_ `virtual void RunInThread(const TFunction<void()>& Function, bool bWaitForCompletion = true, ENamedThreads::Type Thread = ENamedThreads::GameThread)` — Request a function to be run in a particular thread. Primarily used to service accessibility requests from the OS thread about accessible Slate widget data in the game thread. @param Function The function to execute in the game thread. @bWaitForCompletion If true, the function will block until the requested Function completes executing on the requested Thread @param Thread The thread to run the Function in.
- L976 _public function_ `virtual void MakeAccessibleAnnouncement(const FString& AnnouncementString)` — Request a string to be announced to the user. Note: Currently only supported on Win10, Mac, iOS. If requests are made too close together, earlier announcement requests will get stomped by later announcements on certain platforms.
- L981 _public function_ `FGenericAccessibleUserRegistry& GetAccessibleUserRegistry()` — Retrieves the accessible user registry. This is the means of retrieving, registering and interacting with accessible useres in the rest of the application.
- L988 _public function_ `const FGenericAccessibleUserRegistry& GetAccessibleUserRegistry() const` — Retrieves the accessible user registry. This is the means of retrieving, registering and interacting with accessible useres in the rest of the application.
- L997 _public function_ `void SetAccessibleUserRegistry(const TSharedRef<FGenericAccessibleUserRegistry>& InAccessibleUserRegistry)` — Sets a new accessible user registry for the application. Note: As of now, none of the registered users will carry over to the new accessible user manager. It is up to the caller to unregister all currently registered users and register them with the new accessible user registry.   .
- L1004 _protected function_ `virtual void OnActivate()` — Triggered when bIsActive changes from false to true.
- L1006 _protected function_ `virtual void OnDeactivate()` — Triggered when bIsActive changes from true to false.
- L1009 _protected member_ `bool bApplicationIsAccessible;` — Subclasses should override this to indicate that they support accessibility.
- L1013 _private member_ `bool bIsActive;` — Whether or not accessibility is currently enabled in the application
- L1015 _private member_ `FAccessibleEvent AccessibleEventDelegate;` — Delegate for the platform layer to listen to widget events
- L1020 _private member_ `TSharedRef<FGenericAccessibleUserRegistry> AccessibleUserRegistry;` — Registry for all accessible users in the application. Accessible users must be registered with the accessible user registry to allow other parts of the application to retrieve and interact with the accessible users.

#### Free symbols / members of external scopes

- L35 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAccessibility, Log, All);`
- L42 _delegate_ `DECLARE_STATS_GROUP(TEXT("Accessibility"), STATGROUP_Accessibility, STATC`
- L100 _typedef_ `typedef int32 FAccessibleUserIndex;` — An index that uniquely identifies every registered accessible user in the application.
- L465 _typedef_ `typedef int32 AccessibleWidgetId;`
- L876 _delegate_ `DECLARE_DELEGATE_OneParam(FAccessibleEvent, const FAccessibleEventArgs&);` — A delegate accessible event handlers such as platform accessibility APIs can listen for accessibility events raised by widgets.  .

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/GamepadUtils.h` (Public)


#### struct `FDynamicReleaseDeadZone`  
`struct FDynamicReleaseDeadZone`  
_L11-42_
- desc: Properties and functions for a trigger's Dyanamic Release DeadZone.
- L14 _public function_ `FDynamicReleaseDeadZone() : DeadZone(1.0f) , TriggerThreshold(0) , bHasOverride(false) , bWasSimplePressed(false) , bWasDynamicPressed(false)`
- L24 _public prototype_ `void RefreshSettings();`
- L26 _public prototype_ `void OverrideDeadZone(const float InDeadZone);`
- L28 _public prototype_ `bool IsDynamicReleaseEnabled() const;`
- L30 _public prototype_ `bool IsPressed(const uint8 TriggerAnalog, const uint8 PreviousTriggerAnalog);`
- L32 _public prototype_ `bool IsPressed(const uint8 TriggerAnalog, const uint8 PreviousTriggerAnalog, const bool bIsSimplePressed, const bool bPreviousSimplePressed);`
- L34 _public prototype_ `bool IsPressed(const uint8 TriggerAnalog, const bool bIsSimplePressed);`
- L37 _protected member_ `float DeadZone = 1.0f;`
- L38 _protected member_ `uint8 TriggerThreshold = 0;`
- L39 _protected member_ `uint8 bHasOverride : 1;`
- L40 _protected member_ `uint8 bWasSimplePressed : 1;`
- L41 _protected member_ `uint8 bWasDynamicPressed : 1;`

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/GenericApplication.h` (Public)


#### enum `EPopUpOrientation::Type`  
`enum Type`  
_L63-67_
- L65 _public enumerator_ `Horizontal`
- L66 _public enumerator_ `Vertical`

#### class `FModifierKeysState`  
`class FModifierKeysState`  
_L74-316_
- desc: FModifierKeysState stores the pressed state of keys that are commonly used as modifiers
- L89 _public function_ `FModifierKeysState( const bool bInIsLeftShiftDown, const bool bInIsRightShiftDown, const bool bInIsLeftControlDown, const bool bInIsRightControlDown, const bool bInIsLeftAltDown, const bool bInIsRightAltDown, const bool bInIsLeftCommandDown, const bool bInIsRightCommandDown, const bool bInAreCapsLocked) : bIsLeftShiftDown( bInIsLeftShiftDown ), bIsRightShiftDown( bInIsRightShiftDown ), bIsLeftControlDown( bInIsLeftControlDown ), bIsRightControlDown( bInIsRightControlDown ), bIsLeftAltDown( bInIsLeftAltDown ), bIsRightAltDown( bInIsRightAltDown ), bIsLeftCommandDown( bInIsLeftCommandDown ), bIsRightCommandDown( bInIsRightCommandDown ), bAreCapsLocked( bInAreCapsLocked )` — Constructor.  Events are immutable once constructed. @param  bInIsLeftShiftDown  True if left shift is pressed @param  bInIsRightShiftDown  True if right shift is pressed @param  bInIsLeftControlDown  True if left control is pressed @param  bInIsRightControlDown  True if right control is pressed @param  bInIsLeftAltDown  True if left alt is pressed @param  bInIsRightAltDown  True if right alt is pressed
- L110 _public function_ `FModifierKeysState() : bIsLeftShiftDown(false), bIsRightShiftDown(false), bIsLeftControlDown(false), bIsRightControlDown(false), bIsLeftAltDown(false), bIsRightAltDown(false), bIsLeftCommandDown(false), bIsRightCommandDown(false), bAreCapsLocked(false)`
- L128 _public function_ `bool IsShiftDown() const` — Returns true if either shift key was down when this event occurred @return  True if shift is pressed
- L138 _public function_ `bool IsLeftShiftDown() const` — Returns true if left shift key was down when this event occurred @return  True if left shift is pressed
- L148 _public function_ `bool IsRightShiftDown() const` — Returns true if right shift key was down when this event occurred @return  True if right shift is pressed
- L158 _public function_ `bool IsControlDown() const` — Returns true if either control key was down when this event occurred @return  True if control is pressed
- L168 _public function_ `bool IsLeftControlDown() const` — Returns true if left control key was down when this event occurred @return  True if left control is pressed
- L178 _public function_ `bool IsRightControlDown() const` — Returns true if right control key was down when this event occurred @return  True if right control is pressed
- L188 _public function_ `bool IsAltDown() const` — Returns true if either alt key was down when this event occurred @return  True if alt is pressed
- L198 _public function_ `bool IsLeftAltDown() const` — Returns true if left alt key was down when this event occurred @return  True if left alt is pressed
- L208 _public function_ `bool IsRightAltDown() const` — Returns true if right alt key was down when this event occurred @return  True if right alt is pressed
- L218 _public function_ `bool IsCommandDown() const` — Returns true if either command key was down when this event occurred @return  True if command is pressed
- L228 _public function_ `bool IsLeftCommandDown() const` — Returns true if left command key was down when this event occurred @return  True if left command is pressed
- L238 _public function_ `bool IsRightCommandDown() const` — Returns true if right command key was down when this event occurred @return  True if right command is pressed
- L247 _public function_ `bool AreCapsLocked() const` — @return  true if the Caps Lock key has been toggled to the enabled state.
- L256 _public function_ `bool AreModifersDown(EModifierKey::Type ModiferKeys) const` — @param ModifierKeys the modifier keys to test to see if they are pressed.  Returns true if no modifiers are specified. @return true if all modifier keys are pressed specified in the modifier keys.
- L283 _public function_ `bool AnyModifiersDown() const` — @return true if any modifier key is down
- L291 _private member_ `uint16 bIsLeftShiftDown:1;` — True if the left shift key was down when this event occurred.
- L294 _private member_ `uint16 bIsRightShiftDown:1;` — True if the right shift key was down when this event occurred.
- L297 _private member_ `uint16 bIsLeftControlDown:1;` — True if the left control key was down when this event occurred.
- L300 _private member_ `uint16 bIsRightControlDown:1;` — True if the right control key was down when this event occurred.
- L303 _private member_ `uint16 bIsLeftAltDown:1;` — True if the left alt key was down when this event occurred.
- L306 _private member_ `uint16 bIsRightAltDown:1;` — True if the right alt key was down when this event occurred.
- L309 _private member_ `uint16 bIsLeftCommandDown:1;` — True if the left command key was down when this event occurred.
- L312 _private member_ `uint16 bIsRightCommandDown:1;` — True if the right command key was down when this event occurred.
- L315 _private member_ `uint16 bAreCapsLocked:1;` — True if the Caps Lock key has been toggled to the enabled state.

#### struct `FPlatformRect`  
`struct FPlatformRect`  
_L319-333_
- L321 _public member_ `int32 Left;`
- L322 _public member_ `int32 Top;`
- L323 _public member_ `int32 Right;`
- L324 _public member_ `int32 Bottom;`
- L326 _public function_ `FPlatformRect() : Left(0), Top(0), Right(0), Bottom(0)`
- L327 _public function_ `FPlatformRect(int32 InLeft, int32 InTop, int32 InRight, int32 InBottom) : Left(InLeft), Top(InTop), Right(InRight), Bottom(InBottom)`
- L329 _public function_ `bool operator==(const FPlatformRect& Other) const`

#### struct `FMonitorInfo`  
`struct FMonitorInfo`  
_L339-358_
- desc: Contains info on a physical monitor connected to the display device
- L342 _public member_ `FString Name;` — Legacy name that may not be as friendly as FriendlyName for surfacing to UI.
- L345 _public member_ `FString FriendlyName;` — Friendly name for surfacing to UI.
- L348 _public member_ `FString ID;` — String used for monitor identification, which is less likely to alias displays than Name or FriendlyName.
- L350 _public member_ `int32 NativeWidth = 0;`
- L351 _public member_ `int32 NativeHeight = 0;`
- L352 _public member_ `FIntPoint MaxResolution = FIntPoint(ForceInitToZero);`
- L353 _public member_ `FPlatformRect DisplayRect;`
- L354 _public member_ `FPlatformRect WorkArea;`
- L355 _public member_ `bool bIsPrimary = false;`
- L356 _public member_ `int32 DPI = 0;`
- L357 _public member_ `void* NativeHandle = nullptr;`

#### struct `FDisplayMetrics`  
`struct FDisplayMetrics`  
_L364-421_
- desc: Contains metrics information for the desktop area
- L366 _public function_ `FDisplayMetrics() : TitleSafePaddingSize(0, 0, 0, 0) , ActionSafePaddingSize(0, 0, 0, 0)`
- L373 _public member_ `int32 PrimaryDisplayWidth;` — Width of the primary display in pixels
- L376 _public member_ `int32 PrimaryDisplayHeight;` — Height of the primary display in pixels
- L379 _public member_ `TArray<FMonitorInfo> MonitorInfo;` — Info on connected physical monitors. Only available on platforms where this information is accessible (PC currently)
- L382 _public member_ `FPlatformRect PrimaryDisplayWorkAreaRect;` — Area of the primary display not covered by task bars or other docked widgets
- L385 _public member_ `FPlatformRect VirtualDisplayRect;` — Virtual display coordinate range (includes all active displays)
- L394 _public member_ `FVector4 TitleSafePaddingSize;` — The safe area for all content on TVs (see http://en.wikipedia.org/wiki/Safe_area_%28television%29) - content will be inset Left - X Top - Y Right - Z Bottom - W
- L397 _public member_ `FVector4 ActionSafePaddingSize;` — The safe area for less important spill over on TVs (see TitleSafePaddingSize)
- L399 _public prototype_ `static void RebuildDisplayMetrics(struct FDisplayMetrics& OutDisplayMetrics);`
- L402 _public prototype_ `FPlatformRect GetMonitorWorkAreaFromPoint(const FVector2D& Point) const;` — Gets the monitor work area from a position in the global display rect
- L405 _public prototype_ `int32 GetClosestMonitorFromIDAndIndex(const FString& MonitorID, int32 MonitorIndex) const;` — Gets the closest monitor from monitor id and index favoring id
- L408 _public prototype_ `void PrintToLog() const;` — Logs out display metrics
- L411 _public prototype_ `static float GetDebugTitleSafeZoneRatio();` — The title safe zone ratio that will be returned by FDisplayMetrics::GetDisplayMetrics on platforms that don't have a defined safe zone
- L414 _protected prototype_ `bool TryGetTitleSafeZoneOverwrite(FVector4& InOutTitleSafePaddingSize);` — Fills the InOutTitleSafePaddingSize with CVar overwrites (Sets padding to 0 for values that are not set).
- L417 _protected prototype_ `static float GetDebugActionSafeZoneRatio();` — The action safe zone ratio that will be returned by FDisplayMetrics::GetDisplayMetrics on platforms that don't have a defined safe zone
- L420 _protected prototype_ `void ApplyDefaultSafeZones();` — Apply the debug/default safe zones

#### enum `EWindowTitleAlignment::Type`  
`enum Type`  
_L429-437_
- L432 _public enumerator_ `Left` — The window title should be aligned to the left.
- L434 _public enumerator_ `Center` — The window title should be centered within the title bar.
- L436 _public enumerator_ `Right` — The window title should be aligned to the right.

#### class `GenericApplication`  
`class GenericApplication`  
_L444-596_
- desc: Generic platform application interface
- L448 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam( FOnConsoleCommandAdded, const FString& );`
- L449 _public typedef_ `typedef FOnConsoleCommandAdded::FDelegate FOnConsoleCommandListener;`
- L451 _public prototype_ `GenericApplication(const TSharedPtr< ICursor >& InCursor);`
- L452 _public prototype_ `virtual ~GenericApplication();`
- L454 _public function_ `virtual void SetMessageHandler( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler )`
- L456 _public function_ `TSharedRef< FGenericApplicationMessageHandler > GetMessageHandler()`
- L459 _public prototype_ `virtual void SetAccessibleMessageHandler(const TSharedRef<FGenericAccessibleMessageHandler>& InAccessibleMessageHandler);`
- L460 _public prototype_ `TSharedRef<FGenericAccessibleMessageHandler> GetAccessibleMessageHandler() const;`
- L463 _public function_ `virtual void PollGameDeviceState( const float TimeDelta )`
- L465 _public function_ `virtual void PumpMessages( const float TimeDelta )`
- L467 _public function_ `virtual void ProcessDeferredEvents( const float TimeDelta )`
- L469 _public function_ `virtual void Tick ( const float TimeDelta )`
- L471 _public function_ `virtual TSharedRef< FGenericWindow > MakeWindow()`
- L473 _public function_ `virtual void InitializeWindow( const TSharedRef< FGenericWindow >& Window, const TSharedRef< FGenericWindowDefinition >& InDefinition, const TSharedPtr< FGenericWindow >& InParent, const bool bShowImmediately )`
- L475 _public function_ `virtual void SetCapture( const TSharedPtr< FGenericWindow >& InWindow )`
- L477 _public function_ `virtual void* GetCapture( void ) const`
- L479 _public function_ `virtual FModifierKeysState GetModifierKeys() const`
- L482 _public function_ `virtual bool IsCursorDirectlyOverSlateWindow() const` — @return true if the system cursor is currently directly over a slate window.
- L485 _public function_ `virtual TSharedPtr< FGenericWindow > GetWindowUnderCursor()` — @return Native window under the mouse cursor.
- L487 _public function_ `virtual bool IsMinimized() const`
- L489 _public function_ `virtual void SetHighPrecisionMouseMode( const bool Enable, const TSharedPtr< FGenericWindow >& InWindow )`
- L491 _public function_ `virtual bool IsUsingHighPrecisionMouseMode() const`
- L493 _public function_ `virtual bool IsUsingTrackpad() const`
- L495 _public function_ `virtual bool IsMouseAttached() const`
- L497 _public function_ `virtual bool IsGamepadAttached() const`
- L499 _public function_ `virtual void RegisterConsoleCommandListener(const FOnConsoleCommandListener& InListener)`
- L501 _public function_ `virtual void AddPendingConsoleCommand(const FString& InCommand)`
- L503 _public function_ `virtual FPlatformRect GetWorkArea( const FPlatformRect& CurrentWindow ) const`
- L514 _public function_ `virtual bool TryCalculatePopupWindowPosition( const FPlatformRect& InAnchor, const FVector2D& InSize, const FVector2D& ProposedPlacement, const EPopUpOrientation::Type Orientation, FVector2D* const CalculatedPopUpPosition ) const`
- L516 _public prototype_ `DECLARE_EVENT_OneParam(GenericApplication, FOnDisplayMetricsChanged, const FDisplayMetrics&);`
- L519 _public function_ `FOnDisplayMetricsChanged& OnDisplayMetricsChanged()` — Notifies subscribers when any of the display metrics change: e.g. resolution changes or monitor sare re-arranged.
- L521 _public function_ `virtual void GetInitialDisplayMetrics( FDisplayMetrics& OutDisplayMetrics ) const`
- L525 _public prototype_ `DECLARE_EVENT_OneParam(FSlateApplication, FVirtualKeyboardShownEvent, FPlatformRect);` — Delegate for virtual keyboard being shown/hidden in case UI wants to slide out of the way
- L526 _public function_ `FVirtualKeyboardShownEvent& OnVirtualKeyboardShown()`
- L528 _public prototype_ `DECLARE_EVENT(FSlateApplication, FVirtualKeyboardHiddenEvent);`
- L529 _public function_ `FVirtualKeyboardHiddenEvent& OnVirtualKeyboardHidden()`
- L531 _public prototype_ `DECLARE_EVENT(FSlateApplication, FOnClipboardContentChanged);`
- L532 _public function_ `FOnClipboardContentChanged& OnClipboardContentChanged()`
- L535 _public function_ `virtual EWindowTitleAlignment::Type GetWindowTitleAlignment() const` — Gets the horizontal alignment of the window title bar's title text.
- L540 _public function_ `virtual EWindowTransparency GetWindowTransparencySupport() const`
- L545 _public function_ `virtual void DestroyApplication()`
- L547 _public function_ `virtual IInputInterface* GetInputInterface()`
- L550 _public function_ `virtual ITextInputMethodSystem *GetTextInputMethodSystem()` — Function to return the current implementation of the Text Input Method System
- L553 _public function_ `virtual void SendAnalytics(IAnalyticsProvider* Provider)` — Send any analytics captured by the application
- L555 _public function_ `virtual bool SupportsSystemHelp() const`
- L560 _public function_ `virtual bool RequiresPerWindowTooltips() const` — Whether the platform requires a separate tooltip window per toplevel window. On platforms where tooltip popups cannot be re-parented at runtime (e.g. Linux/Wayland), Slate must destroy and recreate the tooltip when the mouse moves to a different toplevel.
- L562 _public function_ `virtual void ShowSystemHelp()`
- L564 _public function_ `virtual bool ApplicationLicenseValid(FPlatformUserId PlatformUser = PLATFORMUSERID_NONE)`
- L566 _public function_ `virtual bool IsAllowedToRender() const`
- L568 _public function_ `virtual void FinishedInputThisFrame()`
- L571 _public member_ `const TSharedPtr< ICursor > Cursor;`
- L575 _protected member_ `TSharedRef< class FGenericApplicationMessageHandler > MessageHandler;`
- L578 _protected member_ `TSharedRef<FGenericAccessibleMessageHandler> AccessibleMessageHandler;`
- L583 _protected function_ `void BroadcastDisplayMetricsChanged( const FDisplayMetrics& InMetrics )` — Trigger the OnDisplayMetricsChanged event with the argument 'InMetrics'
- L586 _protected member_ `FOnDisplayMetricsChanged OnDisplayMetricsChangedEvent;` — Notifies subscribers when any of the display metrics change: e.g. resolution changes or monitor sare re-arranged.
- L589 _protected member_ `FVirtualKeyboardShownEvent VirtualKeyboardShownEvent;` — Delegate for virtual keyboard being shown
- L592 _protected member_ `FVirtualKeyboardHiddenEvent VirtualKeyboardHiddenEvent;` — Delegate for virtual keyboard being shown
- L595 _protected member_ `FOnClipboardContentChanged OnClipboardContentChangedEvent;` — Delegate for clipboard contents change

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace EModifierKey`
- L31 _typedef_ `typedef uint8 Type;` (scope `EModifierKey`)
- L34 _variable_ `inline const Type None = 0;` (scope `EModifierKey`) — No key.
- L37 _variable_ `inline const Type Control = 1 << 0;` (scope `EModifierKey`) — Ctrl key (Command key on Mac, Control key on Windows).
- L40 _variable_ `inline const Type Alt = 1 << 1;` (scope `EModifierKey`) — Alt key.
- L43 _variable_ `inline const Type Shift = 1 << 2;` (scope `EModifierKey`) — Shift key.
- L46 _variable_ `inline const Type Command = 1 << 3;` (scope `EModifierKey`) — Cmd key (Control key on Mac, Win key on Windows)
- L48 _function_ `inline EModifierKey::Type FromBools(const bool bControl, const bool bAlt, const bool bShift, const bool bCommand)` (scope `EModifierKey`)
- L61 _namespace_ `namespace EPopUpOrientation`
- L427 _namespace_ `namespace EWindowTitleAlignment`
- L448 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam( FOnConsoleCommandAdded, const FString& );`
- L516 _delegate_ `DECLARE_EVENT_OneParam(GenericApplication, FOnDisplayMetricsChanged, const FDisplayMetrics&);`
- L525 _delegate_ `DECLARE_EVENT_OneParam(FSlateApplication, FVirtualKeyboardShownEvent, FPlatformRect);` — Delegate for virtual keyboard being shown/hidden in case UI wants to slide out of the way
- L528 _delegate_ `DECLARE_EVENT(FSlateApplication, FVirtualKeyboardHiddenEvent);`
- L531 _delegate_ `DECLARE_EVENT(FSlateApplication, FOnClipboardContentChanged);`

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/GenericApplicationMessageHandler.h` (Public)


#### enum `EMouseButtons::Type`  
`enum Type`  
_L18-27_
- L20 _public enumerator_ `Left = 0`
- L21 _public enumerator_ `Middle`
- L22 _public enumerator_ `Right`
- L23 _public enumerator_ `Thumb01`
- L24 _public enumerator_ `Thumb02`
- L26 _public enumerator_ `Invalid`

#### struct `FGamepadKeyNames`  
`struct FGamepadKeyNames`  
_L30-72_
- L32 _public typedef_ `typedef FName Type;`
- L34 _public member_ `static const FName Invalid;`
- L36 _public member_ `static const FName LeftAnalogX;`
- L37 _public member_ `static const FName LeftAnalogY;`
- L38 _public member_ `static const FName RightAnalogX;`
- L39 _public member_ `static const FName RightAnalogY;`
- L40 _public member_ `static const FName LeftTriggerAnalog;`
- L41 _public member_ `static const FName RightTriggerAnalog;`
- L43 _public member_ `static const FName LeftThumb;`
- L44 _public member_ `static const FName RightThumb;`
- L45 _public member_ `static const FName SpecialLeft;`
- L46 _public member_ `static const FName SpecialLeft_X;`
- L47 _public member_ `static const FName SpecialLeft_Y;`
- L48 _public member_ `static const FName SpecialLeft_Touched;`
- L49 _public member_ `static const FName SpecialRight;`
- L50 _public member_ `static const FName FaceButtonBottom;`
- L51 _public member_ `static const FName FaceButtonRight;`
- L52 _public member_ `static const FName FaceButtonLeft;`
- L53 _public member_ `static const FName FaceButtonTop;`
- L54 _public member_ `static const FName LeftShoulder;`
- L55 _public member_ `static const FName RightShoulder;`
- L56 _public member_ `static const FName LeftTriggerThreshold;`
- L57 _public member_ `static const FName RightTriggerThreshold;`
- L58 _public member_ `static const FName DPadUp;`
- L59 _public member_ `static const FName DPadDown;`
- L60 _public member_ `static const FName DPadRight;`
- L61 _public member_ `static const FName DPadLeft;`
- L63 _public member_ `static const FName LeftStickUp;`
- L64 _public member_ `static const FName LeftStickDown;`
- L65 _public member_ `static const FName LeftStickRight;`
- L66 _public member_ `static const FName LeftStickLeft;`
- L68 _public member_ `static const FName RightStickUp;`
- L69 _public member_ `static const FName RightStickDown;`
- L70 _public member_ `static const FName RightStickRight;`
- L71 _public member_ `static const FName RightStickLeft;`

#### enum `EWindowActivation`  
`enum class EWindowActivation : uint8`  
_L74-79_
- L76 _public enumerator_ `Activate`
- L77 _public enumerator_ `ActivateByMouse`
- L78 _public enumerator_ `Deactivate`

#### enum `EWindowZone::Type`  
`enum Type`  
_L88-113_
- desc: The Window Zone is the window area we are currently over to send back to the operating system for operating system compliance. Must remain synchronized with platform enum maps in FWindowsApplication::ProcessMessage and FLinuxWindow::HitTest.
- L90 _public enumerator_ `NotInWindow = 0`
- L91 _public enumerator_ `ClientArea = 1`
- L94 _public enumerator_ `TopLeftBorder = 2` — IsBorder below assumes these are contiguous in this order
- L95 _public enumerator_ `TopBorder = 3`
- L96 _public enumerator_ `TopRightBorder = 4`
- L97 _public enumerator_ `LeftBorder = 5`
- L98 _public enumerator_ `RightBorder = 6`
- L99 _public enumerator_ `BottomLeftBorder = 7`
- L100 _public enumerator_ `BottomBorder = 8`
- L101 _public enumerator_ `BottomRightBorder = 9`
- L103 _public enumerator_ `TitleBar = 10`
- L104 _public enumerator_ `MinimizeButton = 11`
- L105 _public enumerator_ `MaximizeButton = 12`
- L106 _public enumerator_ `CloseButton = 13`
- L107 _public enumerator_ `SysMenu = 14`
- L109 _public enumerator_ `COUNT = 15`
- L112 _public enumerator_ `Unspecified = 0` — No zone specified

#### enum `EWindowAction::Type`  
`enum Type`  
_L124-130_
- L126 _public enumerator_ `ClickedNonClientArea = 1`
- L127 _public enumerator_ `Maximize = 2`
- L128 _public enumerator_ `Restore = 3`
- L129 _public enumerator_ `WindowMenu = 4`

#### enum `EDropEffect::Type`  
`enum Type`  
_L139-145_
- L141 _public enumerator_ `None = 0`
- L142 _public enumerator_ `Copy = 1`
- L143 _public enumerator_ `Move = 2`
- L144 _public enumerator_ `Link = 3`

#### enum `EGesturePhase`  
`enum class EGesturePhase : uint8`  
_L149-155_
- L151 _public enumerator_ `None`
- L152 _public enumerator_ `Update`
- L153 _public enumerator_ `Started`
- L154 _public enumerator_ `Ended`

#### enum `EGestureEvent`  
`enum class EGestureEvent : uint8`  
_L157-169_
- L159 _public enumerator_ `None`
- L160 _public enumerator_ `Scroll`
- L161 _public enumerator_ `Magnify`
- L162 _public enumerator_ `Swipe`
- L163 _public enumerator_ `Rotate`
- L164 _public enumerator_ `LongPress`
- L165 _public enumerator_ `Pan`
- L166 _public enumerator_ `Tap`
- L167 _public enumerator_ `Flick`
- L168 _public enumerator_ `Count`

#### struct `FWindowSizeLimits`  
`struct FWindowSizeLimits`  
_L173-193_
- desc: Defines the minimum and maximum dimensions that a window can take on.
- L176 _public function_ `FWindowSizeLimits& SetMinWidth(TOptional<float> InValue)`
- L177 _public function_ `const TOptional<float>& GetMinWidth() const`
- L179 _public function_ `FWindowSizeLimits& SetMinHeight(TOptional<float> InValue)`
- L180 _public function_ `const TOptional<float>& GetMinHeight() const`
- L182 _public function_ `FWindowSizeLimits& SetMaxWidth(TOptional<float> InValue)`
- L183 _public function_ `const TOptional<float>& GetMaxWidth() const`
- L185 _public function_ `FWindowSizeLimits& SetMaxHeight(TOptional<float> InValue)`
- L186 _public function_ `const TOptional<float>& GetMaxHeight() const`
- L189 _private member_ `TOptional<float> MinWidth;`
- L190 _private member_ `TOptional<float> MinHeight;`
- L191 _private member_ `TOptional<float> MaxWidth;`
- L192 _private member_ `TOptional<float> MaxHeight;`

#### class `FInputDeviceScope`  
`class FInputDeviceScope`  
_L207-237_
- desc: Context scope that indicates which IInputDevice is currently being handled. This can be used to determine hardware-specific information when handling input from FGenericApplicationMessageHandler subclasses. This is generally set during SendControllerEvents or Tick and is only valid on the game thread. @deprecated FInputDeviceScope is being superseded by FInputDeviceRegistry, which provides the same hardware metadata in a thread-safe manner keyed on FInputDeviceId. All call sites should migrate to FInputDeviceRegistry::FindDescriptor(DeviceId) and FInputDeviceScope will be removed once the migration is complete.
- L211 _public member_ `class IInputDevice* InputDevice;` — The specific InputDevice that is currently being polled. This is only valid within the current function scope and may be null
- L214 _public member_ `FName InputDeviceName;` — Logical name of the input device interface. This is not translated but is platform-specific
- L217 _public member_ `int32 HardwareDeviceHandle;` — A system-specific device id, this is not the same as controllerId and represents a physical device instead of logical user. -1 represents an unknown device
- L220 _public member_ `FString HardwareDeviceIdentifier;` — Logical string identifying the hardware device. This is not translated and is system-specific, it may be empty
- L223 _public prototype_ `FInputDeviceScope(IInputDevice* InInputDevice, FName InInputDeviceName, int32 InHardwareDeviceHandle = -1, FString InHardwareDeviceIdentifier = FString());` — Constructor, this should only be allocated directly on the stack
- L224 _public prototype_ `~FInputDeviceScope();`
- L228 _public prototype_ `FInputDeviceScope() = delete;` — Cannot be copied/moved
- L229 _public prototype_ `FInputDeviceScope(const FInputDeviceScope&) = delete;`
- L230 _public prototype_ `FInputDeviceScope& operator=(const FInputDeviceScope&) = delete;`
- L231 _public prototype_ `FInputDeviceScope(FInputDeviceScope&&) = delete;`
- L232 _public prototype_ `FInputDeviceScope& operator=(FInputDeviceScope&&) = delete;`
- L236 _public prototype_ `static const FInputDeviceScope* GetCurrent();` — Returns the currently active InputDeviceScope. This is only valid to call on the game thread and may return null

#### class `FGenericApplicationMessageHandler`  
`class FGenericApplicationMessageHandler`  
_L240-629_
- desc: Interface that defines how to handle interaction with a user via hardware input and output
- L244 _public prototype_ `virtual ~FGenericApplicationMessageHandler() = default;`
- L246 _public function_ `virtual bool ShouldProcessUserInputMessages( const TSharedPtr< FGenericWindow >& PlatformWindow ) const`
- L251 _public function_ `virtual bool OnKeyChar( const TCHAR Character, const bool IsRepeat )`
- L256 _public function_ `virtual bool OnKeyDown( const int32 KeyCode, const uint32 CharacterCode, const bool IsRepeat )`
- L261 _public function_ `virtual bool OnKeyUp( const int32 KeyCode, const uint32 CharacterCode, const bool IsRepeat )`
- L266 _public function_ `virtual void OnInputLanguageChanged()`
- L270 _public function_ `virtual bool OnMouseDown( const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button )`
- L275 _public function_ `virtual bool OnMouseDown( const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button, const FVector2D CursorPos )`
- L280 _public function_ `virtual bool OnMouseUp( const EMouseButtons::Type Button )`
- L285 _public function_ `virtual bool OnMouseUp( const EMouseButtons::Type Button, const FVector2D CursorPos )`
- L290 _public function_ `virtual bool OnMouseDoubleClick( const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button )`
- L295 _public function_ `virtual bool OnMouseDoubleClick( const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button, const FVector2D CursorPos )`
- L300 _public function_ `virtual bool OnMouseWheel( const float Delta )`
- L305 _public function_ `virtual bool OnMouseWheel( const float Delta, const FVector2D CursorPos )`
- L310 _public function_ `virtual bool OnMouseMove()`
- L315 _public function_ `virtual bool OnRawMouseMove( const int32 X, const int32 Y )`
- L320 _public function_ `virtual bool OnCursorSet()`
- L330 _public function_ `virtual bool ShouldUsePlatformUserId() const` — Return true if this message handler expects FPlatformUserIds. This base class will convert both directions. As part of a larger fixup to allow mapping of multiple input devices to the same player, physical device id will be passed as part of the InputScope above and used to compute a logical input user.
- L335 _public function_ `virtual bool OnControllerAnalog(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, float AnalogValue)`
- L340 _public function_ `virtual bool OnControllerButtonPressed(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, bool IsRepeat)`
- L345 _public function_ `virtual bool OnControllerButtonReleased(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, bool IsRepeat)`
- L350 _public function_ `virtual void OnBeginGesture()`
- L354 _public function_ `virtual bool OnTouchGesture( EGestureEvent GestureType, const FVector2D& Delta, float WheelDelta, bool bIsDirectionInvertedFromDevice )`
- L359 _public function_ `virtual void OnEndGesture()`
- L363 _public function_ `virtual bool OnNativeGestureBegin(EGestureEvent GestureType, const FVector2D& Delta, float Value, bool bIsDirectionInvertedFromDevice, FPlatformUserId PlatformUserId, FInputDeviceId DeviceId)`
- L368 _public function_ `virtual bool OnNativeGestureUpdate(EGestureEvent GestureType, const FVector2D& Delta, float Value, bool bIsDirectionInvertedFromDevice, FPlatformUserId PlatformUserId, FInputDeviceId DeviceId)`
- L373 _public function_ `virtual bool OnNativeGestureEnd(EGestureEvent GestureType, const FVector2D& Delta, float Value, bool bIsDirectionInvertedFromDevice, FPlatformUserId PlatformUserId, FInputDeviceId DeviceId)`
- L378 _public function_ `virtual bool OnTouchStarted( const TSharedPtr< FGenericWindow >& Window, const FVector2D& Location, float Force, int32 TouchIndex, FPlatformUserId PlatformUserId, FInputDeviceId DeviceId )`
- L387 _public function_ `virtual bool OnTouchMoved( const FVector2D& Location, float Force, int32 TouchIndex, FPlatformUserId PlatformUserId, FInputDeviceId DeviceID )`
- L396 _public function_ `virtual bool OnTouchEnded( const FVector2D& Location, int32 TouchIndex, FPlatformUserId PlatformUserId, FInputDeviceId DeviceID )`
- L405 _public function_ `virtual bool OnTouchForceChanged(const FVector2D& Location, float Force, int32 TouchIndex, FPlatformUserId PlatformUserId, FInputDeviceId DeviceID)`
- L414 _public function_ `virtual bool OnTouchFirstMove(const FVector2D& Location, float Force, int32 TouchIndex, FPlatformUserId PlatformUserId, FInputDeviceId DeviceID)`
- L423 _public function_ `virtual void ShouldSimulateGesture(EGestureEvent Gesture, bool bEnable)`
- L428 _public function_ `virtual bool OnMotionDetected( const FVector& Tilt, const FVector& RotationRate, const FVector& Gravity, const FVector& Acceleration, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId )`
- L437 _public function_ `virtual bool OnSizeChanged( const TSharedRef< FGenericWindow >& Window, const int32 Width, const int32 Height, bool bWasMinimized = false )`
- L442 _public function_ `virtual void OnOSPaint( const TSharedRef<FGenericWindow>& Window )`
- L447 _public function_ `virtual FWindowSizeLimits GetSizeLimitsForWindow( const TSharedRef<FGenericWindow>& Window ) const`
- L452 _public function_ `virtual void OnResizingWindow( const TSharedRef< FGenericWindow >& Window )`
- L457 _public function_ `virtual bool BeginReshapingWindow( const TSharedRef< FGenericWindow >& Window )`
- L462 _public function_ `virtual void FinishedReshapingWindow( const TSharedRef< FGenericWindow >& Window )`
- L467 _public function_ `virtual void DismissAllMenus()`
- L472 _public function_ `virtual void HandleDPIScaleChanged( const TSharedRef< FGenericWindow >& Window )`
- L477 _public function_ `virtual void SignalSystemDPIChanged(const TSharedRef< FGenericWindow >& Window)`
- L482 _public function_ `virtual void OnRegularWindowMovedOrResized(const TSharedRef< FGenericWindow >& Window)`
- L487 _public function_ `virtual void OnMovedWindow( const TSharedRef< FGenericWindow >& Window, const int32 X, const int32 Y )`
- L492 _public function_ `virtual bool OnWindowActivationChanged( const TSharedRef< FGenericWindow >& Window, const EWindowActivation ActivationType )`
- L497 _public function_ `virtual bool OnApplicationActivationChanged( const bool IsActive )`
- L502 _public function_ `virtual bool OnConvertibleLaptopModeChanged()`
- L507 _public function_ `virtual EWindowZone::Type GetWindowZoneForPoint( const TSharedRef< FGenericWindow >& Window, const int32 X, const int32 Y )`
- L512 _public function_ `virtual void OnWindowClose( const TSharedRef< FGenericWindow >& Window )`
- L517 _public function_ `virtual EDropEffect::Type OnDragEnterText( const TSharedRef< FGenericWindow >& Window, const FString& Text )`
- L522 _public function_ `virtual EDropEffect::Type OnDragEnterFiles( const TSharedRef< FGenericWindow >& Window, const TArray< FString >& Files )`
- L527 _public function_ `virtual EDropEffect::Type OnDragEnterExternal( const TSharedRef< FGenericWindow >& Window, const FString& Text, const TArray< FString >& Files )`
- L532 _public function_ `virtual EDropEffect::Type OnDragOver( const TSharedPtr< FGenericWindow >& Window )`
- L537 _public function_ `virtual void OnDragLeave( const TSharedPtr< FGenericWindow >& Window )`
- L542 _public function_ `virtual EDropEffect::Type OnDragDrop( const TSharedPtr< FGenericWindow >& Window )`
- L547 _public function_ `virtual bool OnWindowAction( const TSharedRef< FGenericWindow >& Window, const EWindowAction::Type InActionType)`
- L552 _public function_ `virtual void SetCursorPos(const FVector2D& MouseCoordinate)`
- L557 _public function_ `virtual bool OnTouchStarted(const TSharedPtr< FGenericWindow >& Window, const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId)`
- L569 _public function_ `virtual bool OnTouchMoved(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId)`
- L581 _public function_ `virtual bool OnTouchEnded(const FVector2D& Location, int32 TouchIndex, int32 ControllerId)`
- L593 _public function_ `virtual bool OnTouchForceChanged(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId)`
- L605 _public function_ `virtual bool OnTouchFirstMove(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId)`
- L617 _public function_ `virtual bool OnMotionDetected(const FVector& Tilt, const FVector& RotationRate, const FVector& Gravity, const FVector& Acceleration, int32 ControllerId)`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace EMouseButtons`
- L81 _namespace_ `namespace EWindowZone`
- L115 _function_ `inline bool IsBorder(Type Zone)` (scope `EWindowZone`)
- L122 _namespace_ `namespace EWindowAction`
- L137 _namespace_ `namespace EDropEffect`

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/GenericConfigRules.h` (Public)


#### class `FGenericConfigRules`  
`class FGenericConfigRules`  
_L9-14_
- L13 _public prototype_ `static TMap<FString, FString> ParseConfigRules(TConstArrayView<uint8> ConfigRulesData, TMap<FString, FString>&& PredefinedVariables);` — Parses a rule file based on PredefinedVariables and returns the Variable Map.

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogConfigRules, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogConfigRules, Log, All);`

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/GenericInputDeviceMap.h` (Public)


#### class `TInputDeviceMap`  
`template <class TDeviceKeyType> class TInputDeviceMap`  
_L19-124_
- desc: An interface which can be added to any IInputDevice (or any other type which is creating Human Interface Devices) to store it's unique identifier for those physical devices and associate them with a FInputDeviceId so that the rest of the Unreal Engine can interact with them Some input interfaces use simple int32's to identify input devices, while others may have more specific GUID types types which are needed.
- L23 _public prototype_ `TInputDeviceMap() = default;`
- L24 _public prototype_ `~TInputDeviceMap() = default;`
- L32 _public function_ `[[nodiscard]] FInputDeviceId GetOrCreateDeviceId(const TDeviceKeyType& DeviceKey)` — Given the DeviceKey, find it's associated FInputDeviceId. If one does not exist yet, such as for a newly connected device, then create one from the IPlatformInputDeviceMapper.
- L60 _public function_ `[[nodiscard]] FInputDeviceId MapDefaultInputDevice(const TDeviceKeyType& DeviceKey)` — Maps a DeviceKey to the default FInputDeviceId which has the internal value 0. Returns the default FInputDeviceId for straightforward use.
- L75 _public function_ `[[nodiscard]] FInputDeviceId FindDeviceId(const TDeviceKeyType& DeviceKey) const` — Returns the FInputDeviceId for the given device key. Returns FInputDeviceId::Invalid if it is not yet mapped.
- L91 _public function_ `[[nodiscard]] FInputDeviceId FindDeviceIdChecked(const TDeviceKeyType& DeviceKey) const` — Returns the FInputDeviceId associated with the given device key. Asserts if not found.
- L99 _public function_ `[[nodiscard]] const TDeviceKeyType& GetDeviceKeyChecked(const FInputDeviceId DeviceId) const` — Returns the device key for the given FInputDeviceId. Nullptr if not found.
- L107 _public function_ `[[nodiscard]] const TDeviceKeyType* FindDeviceKey(const FInputDeviceId DeviceId) const` — Returns the device key for the given FInputDeviceId. Nullptr if not found.
- L117 _protected member_ `TMap<TDeviceKeyType, FInputDeviceId> MappedDeviceIds;` — Map of the assigned DeviceKeyType to their assigned FInputDeviceId's from the engine.
- L123 _protected member_ `TMap<FInputDeviceId, TDeviceKeyType> MappedIdToKey;` — A map of the assigned FInputDeviceId to their associated Device Key type for fast lookup.

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/GenericPlatformApplicationMisc.h` (Public)


#### enum `EScreenPhysicalAccuracy`  
`enum class EScreenPhysicalAccuracy`  
_L26-31_
- desc: The accuracy when dealing with physical characteristics of the monitor/screen of the device we're running on.
- L28 _public enumerator_ `Unknown`
- L29 _public enumerator_ `Approximation`
- L30 _public enumerator_ `Truth`

#### struct `FShowInputDeviceSelectorParams`  
`struct FShowInputDeviceSelectorParams`  
_L36-40_
- desc: Callback for when FindInputDeviceForUserWithUI has completed
- L38 _public member_ `FInputDeviceId InputDeviceId;`
- L39 _public member_ `FPlatformUserId PlatformUserId;`

#### struct `FPlatformUserSelectionCompleteParams`  
`struct FPlatformUserSelectionCompleteParams`  
_L46-50_
- desc: Callback for when ShowPlatformUserSelector has completed.
- L48 _public member_ `FPlatformUserId SelectedUserId;`
- L49 _public member_ `bool bSuccess;`

#### enum `EPlatformUserSelectorFlags`  
`enum class EPlatformUserSelectorFlags : uint8`  
_L56-65_
- desc: Options for ShowPlatformUserSelector. Not all platforms will support all flags
- L58 _public enumerator_ `None = 0`
- L59 _public enumerator_ `RequiresOnlineEnabledProfile = (1 << 1)` — whether to only show profiles that have an online account
- L60 _public enumerator_ `ShowSkipButton = (1 << 2)` — display a 'skip' button UI to be closed & return the initiating user
- L61 _public enumerator_ `AllowGuests = (1 << 3)` — temporary guest accounts, throwaways etc.
- L62 _public enumerator_ `ShowNewUsersOnly = (1 << 4)` — do not show profiles that are already in-use by the title
- L64 _public enumerator_ `Default = ShowSkipButton` — most commonly used options

#### struct `FGenericPlatformApplicationMisc`  
`struct FGenericPlatformApplicationMisc`  
_L69-416_
- L71 _public prototype_ `static void PreInit();`
- L73 _public prototype_ `static void Init();`
- L75 _public prototype_ `static void PostInit();`
- L77 _public prototype_ `static void TearDown();`
- L82 _public function_ `static void LoadPreInitModules()` — Load the preinit modules required by this platform, typically they are the renderer modules
- L89 _public function_ `static void LoadStartupModules()` — Load the platform-specific startup modules
- L96 _public prototype_ `static FOutputDeviceConsole* CreateConsoleOutputDevice();` — Creates a console output device for this platform. Should only be called once.
- L101 _public prototype_ `static FOutputDeviceError* GetErrorOutputDevice();` — Gets a pointer to the platform error output device singleton.
- L106 _public prototype_ `static FFeedbackContext* GetFeedbackContext();` — Gets a pointer to the default platform feedback context implementation.
- L111 _public prototype_ `static IPlatformInputDeviceMapper* CreatePlatformInputDeviceManager();` — Gets a pointer to the default platform input device manager.
- L116 _public prototype_ `static class GenericApplication* CreateApplication();` — Creates an application instance.
- L119 _public prototype_ `static void RequestMinimize();` — Request application to minimize (goto background).
- L122 _public prototype_ `static bool IsThisApplicationForeground();` — Returns true if the specified application has a visible window, and that window is active/has focus/is selected
- L127 _public prototype_ `static bool RequiresVirtualKeyboard();` — Returns whether the platform wants to use a touch screen for a virtual keyboard.
- L133 _public function_ `inline static void PumpMessages(bool bFromMainLoop)` — Pumps Windows messages. @param bFromMainLoop if true, this is from the main loop, otherwise we are spinning waiting for the render thread
- L141 _public function_ `static void PreventScreenSaver()` — Prevents screen-saver from kicking in by moving the mouse by 0 pixels. This works even in the presence of a group policy for password protected screen saver.
- L157 _public function_ `static bool IsScreensaverEnabled()` — Returns state of screensaver (if platform supports it) @return	true if screensaver enabled (returns false if platform does not support it)
- L168 _public function_ `static bool ControlScreensaver(EScreenSaverAction Action)` — Disables screensaver (if platform supports such an API) @param Action enable or disable @return true if succeeded, false if platform does not have this API and PreventScreenSaver() hack is needed
- L180 _public prototype_ `static struct FLinearColor GetScreenPixelColor(const FVector2D& InScreenPos, float InGamma = 1.0f);` — Sample the displayed pixel color from anywhere on the screen using the OS @param	InScreenPos		The screen coords to sample for current pixel color @param	InGamma			Optional gamma correction to apply to the screen color @return					The color of the pixel displayed at the chosen location
- L191 _public function_ `static bool GetWindowTitleMatchingText(const TCHAR* TitleStartsWith, FString& OutTitle)` — Searches for a window that matches the window name or the title starts with a particular text. When found, it returns the title text for that window @param TitleStartsWith an alternative search method that knows part of the title text @param OutTitle the string the data is copied into @return whether the window was found and the text copied or not
- L199 _public function_ `static void SetHighDPIMode()` — Allows the OS to enable high DPI mode
- L208 _public function_ `static float GetDPIScaleFactorAtPoint(float X, float Y)` — Returns monitor's DPI scale factor at given screen coordinates (expressed in pixels) @return Monitor's DPI scale factor at given point
- L216 _public prototype_ `static bool IsHighDPIAwarenessEnabled();`
- L222 _public function_ `static bool AnchorWindowWindowPositionTopLeft()` — UE expects mouse coordinates in screen space. Some platforms provides in client space. Return true to anchor the window at the top/left corner to make sure client space coordinates and screen space coordinates match up.
- L231 _public function_ `static bool RequiresParentedNotifications()` — Return true if notification windows must be parented to an existing window and anchored to it, for platforms that cannot position top-level windows at an absolute screen coordinate (pure Wayland).
- L239 _public function_ `static void SetGamepadsAllowed(bool bAllowed)` — Set whether gamepads are allowed at the platform level.
- L245 _public function_ `static void SetGamepadsBlockDeviceFeedback(bool bAllowed)` — Set whether gamepads are allowed at the platform level.
- L251 _public function_ `static void ResetGamepadAssignments()` — Resets the gamepad to player controller id assignments
- L257 _public function_ `static void ResetGamepadAssignmentToController(int32 ControllerId)` — Resets the gamepad assignment to player controller id
- L263 _public function_ `static bool IsControllerAssignedToGamepad(int32 ControllerId)` — Returns true if controller id assigned to a gamepad
- L271 _public function_ `static FString GetGamepadControllerName(int32 ControllerId)` — Returns name of gamepad if controller id assigned to a gamepad
- L283 _public function_ `static class UTexture2D* GetGamepadButtonGlyph(const FGamepadKeyNames::Type& ButtonKey, uint32 ControllerIndex)` — Returns a texture of the glyph representing the specified button on the specified controller, or nullptr if not supported.
- L292 _public function_ `static void EnableMotionData(bool bEnable)` — Whether to enable controller motion data polling (by default motion data is enabled) Some platforms may want to disable it to reduce battery drain
- L298 _public function_ `static bool IsMotionDataEnabled()` — Whether controller motion data polling is enabled (by default motion data is enabled)
- L304 _public prototype_ `static void ClipboardCopy(const TCHAR* Str);` — Copies text to the operating system clipboard.
- L307 _public prototype_ `static void ClipboardPaste(class FString& Dest);` — Pastes in text from the operating system clipboard.
- L312 _public prototype_ `static EScreenPhysicalAccuracy GetPhysicalScreenDensity(int32& OutScreenDensity);` — Gets the physical size of the screen if possible.  Some platforms lie, some platforms don't know.
- L314 _public prototype_ `static EScreenPhysicalAccuracy GetPhysicalScreenDimensions(FVector2f& OutScreenDimensions);`
- L316 _public prototype_ `static EScreenPhysicalAccuracy GetPhysicalScreenSize(float& OutScreenSize);`
- L321 _public prototype_ `static EScreenPhysicalAccuracy ComputePhysicalScreenDensity(int32& OutScreenDensity);` — Gets the physical size of the screen if possible.  Some platforms lie, some platforms don't know.
- L323 _public prototype_ `static EScreenPhysicalAccuracy ComputePhysicalScreenDimensions(FVector2f& OutScreenDimensions, float& OutScreenSize);`
- L325 _public prototype_ `static void ComputePhysicalScreenData();`
- L332 _public function_ `template<typename T, typename T2 UE_REQUIRES(std::is_floating_point_v<T> && std::is_floating_point_v<T2>)> static EScreenPhysicalAccuracy ConvertInchesToPixels(T Inches, T2& OutPixels)` — If we know or can approximate the pixel density of the screen we will convert the incoming inches to pixels on the device.  If the accuracy is unknown OutPixels will be set to 0.
- L354 _public function_ `template<typename T, typename T2 UE_REQUIRES(std::is_floating_point_v<T> && std::is_floating_point_v<T2>)> static EScreenPhysicalAccuracy ConvertPixelsToInches(T Pixels, T2& OutInches)` — If we know or can approximate the pixel density of the screen we will convert the incoming pixels to inches on the device.  If the accuracy is unknown OutInches will be set to 0.
- L379 _public function_ `static bool ShowInputDeviceSelector( FPlatformUserId InitiatingUserId, FShowInputDeviceSelectorComplete OnShowInputDeviceSelectorComplete )` — Asyncronously display the platform-specific input device selection UI, if supported. @param InitiatingUserId The platform user to find an input device for. @param OnShowInputDeviceSelectorComplete Callback for when the input device selection operation has completed @return true if the UI will be shown and the callback will be called @return false if the platform does not support an input device selection API, or it is not currently available (the callback will not be called)
- L394 _public function_ `static bool ShowPlatformUserSelector(FInputDeviceId InitiatingInputDeviceId, EPlatformUserSelectorFlags Flags, FPlatformUserSelectionComplete OnUserSelectionComplete)` — Asyncronously display the platform-specific user selection UI, if supported. @param InitiatingInputDeviceId The input device that prompted showing the UI, if applicable. The input device may be re-paired with the newly-selected user, depending on the platform @param Flags customization options for the user selection UI. @param OnUserSelectionComplete callback for when the user selection operation has completed @return true if the UI will be shown and the callback will be called @return false if the platform does not support a user-selection API, or it is not currently available (the callback will not be called)
- L401 _public prototype_ `static bool AreNativeGesturesEnabled();` — Returns true when native platform gesture recognizers should be used instead of software gesture detection.
- L404 _protected member_ `static bool CachedPhysicalScreenData;`
- L405 _protected member_ `static EScreenPhysicalAccuracy CachedPhysicalScreenAccuracy;`
- L406 _protected member_ `static int32 CachedPhysicalScreenDensity;`
- L407 _protected member_ `static FAutoConsoleVariableRef CVarEnableHighDPIAwareness;`
- L408 _protected member_ `static FAutoConsoleVariableRef CVarAllowVirtualKeyboard;`
- L410 _protected member_ `static EScreenPhysicalAccuracy CachedPhysicalScreenDimensionsAccuracy;`
- L411 _protected member_ `static FVector2f CachedPhysicalScreenDimensions;`
- L412 _protected member_ `static float CachedPhysicalScreenSize;`
- L415 _private member_ `static TAutoConsoleVariable<bool> CVarEnableNativeGestureRecognition;`

#### enum `FGenericPlatformApplicationMisc::EScreenSaverAction`  
`enum EScreenSaverAction`  
_L145-149_
- L147 _public enumerator_ `Disable`
- L148 _public enumerator_ `Enable`

#### Free symbols / members of external scopes

- L41 _typedef_ `typedef TFunction<void(const FShowInputDeviceSelectorParams&)> FShowInputDeviceSelectorComplete;`
- L51 _typedef_ `typedef TFunction<void(const FPlatformUserSelectionCompleteParams& Params)> FPlatformUserSelectionComplete;`
- L66 _prototype_ `ENUM_CLASS_FLAGS(EPlatformUserSelectorFlags);`

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/GenericPlatformFramePacer.h` (Public)


#### struct `FGenericPlatformRHIFramePacer`  
`struct FGenericPlatformRHIFramePacer`  
_L17-56_
- desc: Generic implementation for most platforms
- L23 _public function_ `static inline int32 GetFramePace()` — The pace we are running at (30 = 30fps, 0 = unpaced) The generic implementation returns a result based on rhi.SyncInterval and FPlatformMisc::GetMaxRefreshRate().
- L34 _public function_ `static inline int32 SetFramePace(int32 FramePace)` — Sets the pace we would like to running at (30 = 30fps, 0 = unpaced). The generic implementation sets the value for rhi.SyncInterval according to FPlatformMisc::GetMaxRefreshRate(). @return the pace we will run at.
- L42 _public prototype_ `static bool SupportsFramePace(int32 QueryFramePace);` — Returns whether the hardware is able to frame pace at the specified frame rate
- L48 _protected prototype_ `static int32 GetFramePaceFromSyncInterval();` — The generic implementation returns a result based on rhi.SyncInterval and FPlatformMisc::GetMaxRefreshRate().
- L55 _protected prototype_ `static int32 SetFramePaceToSyncInterval(int32 FramePace);` — The generic implementation sets rhi.SyncInterval based on FPlatformMisc::GetMaxRefreshRate(). @return the pace we will run at.

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/GenericPlatformInputDeviceMapper.h` (Public)


#### class `IPlatformInputDeviceMapper`  
`class IPlatformInputDeviceMapper`  
_L27-342_
- desc: Base class to private a mapping of Platform Users (FPlatformUserID) to their associated available input devices (FInputDeviceID). This will handle the allocation of the globally unique identifier of the FInputDeviceID, and allow overrides of how each platform maps input devices to their users. Some platforms may desire to have each new input device assigned to a different user, while others may want multiple input devices associated with a single user. @note Keep any function comments up to date with those in PlatformInputDeviceMapperLibrary.h!
- L32 _public prototype_ `static IPlatformInputDeviceMapper& Get();` — Get the platform input device mapper
- L34 _public prototype_ `IPlatformInputDeviceMapper();`
- L37 _public prototype_ `virtual ~IPlatformInputDeviceMapper();` — Virtual destructor
- L46 _public prototype_ `virtual int32 GetAllInputDevicesForUser(const FPlatformUserId UserId, TArray<FInputDeviceId>& OutInputDevices) const;` — Populates the OutInputDevices array with any InputDeviceID's that are mapped to the given platform user @param UserId				The Platform User to gather the input devices of. @param OutInputDevices		Array of input device ID's that will be populated with the mapped devices. @return						The number of mapped devices, INDEX_NONE if the user was not found.
- L54 _public prototype_ `virtual int32 GetAllInputDevices(TArray<FInputDeviceId>& OutInputDevices) const;` — Get all mapped input devices on this platform regardless of their connection state. @param OutInputDevices	Array of input devices to populate @return					The number of connected input devices
- L62 _public prototype_ `virtual int32 GetAllConnectedInputDevices(TArray<FInputDeviceId>& OutInputDevices) const;` — Gather all currently connected input devices @param OutInputDevices	Array of input devices to populate @return					The number of connected input devices
- L71 _public prototype_ `virtual int32 GetAllConnectedInputDevicesForUser(const FPlatformUserId UserId, TArray<FInputDeviceId>& OutInputDevices) const;` — Gather all currently connected input devices for specific user @param UserId				The Platform User to gather the input devices of. @param OutInputDevices		Array of input device ID's that will be populated with the mapped devices. @return						The number of mapped devices, INDEX_NONE if the user was not found.
- L79 _public prototype_ `virtual int32 GetAllActiveUsers(TArray<FPlatformUserId>& OutUsers) const;` — Get all currently active platform ids, anyone who has a mapped input device @param OutUsers		Array that will be populated with the platform users. @return				The number of active platform users
- L88 _public prototype_ `virtual FPlatformUserId GetFirstPlatformUserWithNoInputDevice() const;` — Finds the first FPlatformUserId which was already allocated with no input devices. Returns PLATFORMUSERID_NONE if every current platform user has a valid input device mapped to it. Will not return the Unpaired platform user.
- L94 _public prototype_ `virtual FPlatformUserId GetUserForUnpairedInputDevices() const = 0;` — Returns the platform user id that is being used for unmapped input devices. Will be PLATFORMUSERID_NONE if platform does not support this (this is the default behavior)
- L97 _public prototype_ `virtual bool IsUnpairedUserId(const FPlatformUserId PlatformId) const;` — Returns true if the given Platform User Id is the user for unpaired input devices on this platform.
- L100 _public prototype_ `virtual bool IsInputDeviceMappedToUnpairedUser(const FInputDeviceId InputDevice) const;` — Returns true if the given input device is mapped to the unpaired platform user id.
- L108 _public prototype_ `virtual FPlatformUserId GetPrimaryPlatformUser() const = 0;` — Returns the 'Primary' Platform user for this platform. This typically has an internal ID of '0' and is used as the default platform user to map devices such as the keyboard and mouse that don't get assigned unique ID's from their owning platform code.
- L111 _public prototype_ `virtual FInputDeviceId GetDefaultInputDevice() const = 0;` — Returns the default device id used for things like keyboard/mouse input
- L122 _public prototype_ `virtual FPlatformUserId GetPlatformUserForNewlyConnectedDevice(const int32 InUserId = -1);` — Returns the platform user id that a newly connected device should be mapped to. If "ShouldCreateUniqueUserForEachDevice" is true, then a new platform user id will be allocated for this device. Otherwise, this will return the primary platform user. @param InUserId		An optional user index which can be passed in. If this is not -1, and IsUsingControllerIdAsUserId is true, then the platform user id for that user will be returned.
- L125 _public prototype_ `virtual FPlatformUserId GetUserForInputDevice(FInputDeviceId DeviceId) const;` — Returns the platform user attached to this input device, or PLATFORMUSERID_NONE if invalid
- L128 _public prototype_ `virtual FInputDeviceId GetPrimaryInputDeviceForUser(FPlatformUserId UserId) const;` — Returns the primary input device used by a specific player, or INPUTDEVICEID_NONE if invalid
- L139 _public prototype_ `virtual bool Internal_SetInputDeviceConnectionState(FInputDeviceId DeviceId, EInputDeviceConnectionState NewState);` — Set the connection state of a given Input Device to something new. This will broadcast the OnInputDeviceConnectionChange delegate. This should be called by the platform's implementation. @param DeviceId		The device id that has had a connection change @param NewState		The new connection state of the given device @return				True if the connection state was set successfully
- L147 _public prototype_ `virtual EInputDeviceConnectionState GetInputDeviceConnectionState(const FInputDeviceId DeviceId) const;` — Gets the connection state of the given input device. @param DeviceId		The device to get the connection state of @return				The connection state of the given device. EInputDeviceConnectionState::Unknown if the device is not mapped
- L158 _public prototype_ `virtual bool Internal_MapInputDeviceToUser(FInputDeviceId DeviceId, FPlatformUserId UserId, EInputDeviceConnectionState ConnectionState);` — Maps the given Input Device to the given userID. This will broadcast the OnInputDeviceConnectionChange delegate. This should be called by the platform's implementation. @param DeviceId			The device id to map @param UserId			The Platform User that owns the given device @param ConnectionState	The connection state of the device @return					True if the input device was successfully mapped
- L171 _public prototype_ `virtual bool Internal_ChangeInputDeviceUserMapping(FInputDeviceId DeviceId, FPlatformUserId NewUserId, FPlatformUserId OldUserId);` — Change the user mapping of the given input device from an old user to a new one. This will broadcast the OnInputDevicePairingChange delegate. Use this when you know that an input device is already mapped, but it has changed platform users This should be called by the platform's implementation. @param DeviceId		The input device to change the owner on @param NewUserId		The new platform user that this input device should be mapped to @param OldUserId		The old platform user that this input device is currently mapped to @return				True if the device was successfully remapped
- L178 _public prototype_ `virtual int32 GetMaxPlatformUserCount() const;` — Returns the max allowed number of platform users this platform can have. By default, this will return the value specified in the input settings ini file
- L194 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnInputDeviceHardwareInfoAvailable, EInputDeviceConnectionState , FPlatformUserId , FInputDeviceId );` — Callback which is fired before the "user" input device connection change. When this is fired, the input device metadata may not yet be populated. This is intended for any "lower level" systems which want to directly access device connection changes before other engine plugins and game code does. This should only be fired if there is a valid FInputDeviceScope which can be used to derive the hardware info from. @param NewConnectionState	The new connection state of this device @param FPlatformUserId		The User ID whose input device has changed @param FInputDeviceId		The Input Device ID that has changed connection
- L203 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUserInputDeviceConnectionChange, EInputDeviceConnectionState , FPlatformUserId , FInputDeviceId );` — Callback for handling an Input Device's connection state change. @param NewConnectionState	The new connection state of this device @param FPlatformUserId		The User ID whose input device has changed @param FInputDeviceId		The Input Device ID that has changed connection
- L212 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUserInputDevicePairingChange, FInputDeviceId , FPlatformUserId , FPlatformUserId );` — Callback for handling an Input Device pairing change. @param FInputDeviceId	Input device ID @param FPlatformUserId	The NewUserPlatformId @param FPlatformUserId	The OldUserPlatformId
- L214 _public function_ `FOnInputDeviceHardwareInfoAvailable& GetOnInputDeviceHardwareInfoAvailable() const`
- L215 _public function_ `FOnUserInputDeviceConnectionChange& GetOnInputDeviceConnectionChange() const`
- L216 _public function_ `FOnUserInputDevicePairingChange& GetOnInputDevicePairingChange() const`
- L223 _public prototype_ `void HandleInputDevicePolicyChanged(const EInputDeviceMappingPolicy NewPolicy);` — Remaps the currently connected input devices based on the new given policy. This property can only be changed at editor time and should not be used at runtime.
- L239 _public prototype_ `virtual bool RemapUserAndDeviceToControllerId(FPlatformUserId UserId, int32& OutControllerId, FInputDeviceId OptionalDeviceId = INPUTDEVICEID_NONE) = 0;` — Remap a FPlatformUserId to a ControllerId that is needed by legacy code. Use this function to add compatibility to platforms that may not have implemented this device mapper yet. @param UserId				The platform user that should be converted @param OutControllerId		Set to the old plain "int32" that represented gamepad id or user index depending on the context. @param OptionalDeviceId		Set this to a specific device id if known @return						True if this maps to a real user
- L248 _public prototype_ `virtual int32 GetUserIndexForPlatformUser(FPlatformUserId UserId) = 0;` — Remap a FPlatformUserId to the legacy platform LocalUserIndex (often the same as ControllerId). This is useful in cases where the input device id is not needed. @param UserId			The platform user that should be converted @returns					A valid platform user index, or INDEX_NONE
- L263 _public prototype_ `virtual bool RemapControllerIdToPlatformUserAndDevice(int32 ControllerId, FPlatformUserId& InOutUserId, FInputDeviceId& OutInputDeviceId) = 0;` — Remap the legacy "int32 ControllerId" to the updated FPlatformUserId and FInputDeviceId. Use this function to add compatibility to platforms that may not have implemented this device mapper yet. This is useful for functions such as FGenericApplicationMessageHandler::OnControllerAnalog that used to use the "int32 ControllerId" as a parameter so that you can call the new FGenericApplicationMessageHandler that take in a PlatformUserId and an InputDeviceId. @param ControllerId			The old plain "int32" that represented gamepad id or user index depending on the context. @param InOutUserId			If the old function provides a PlatformId then pass it here, otherwise pass PLATFORMUSERID_NONE. @param OutInputDeviceId		The best guess for an InputDeviceId based on the legacy int32 ControllerId. This may be INPUTDEVICEID_NONE. @return						True if this maps to a real user
- L272 _public prototype_ `virtual FPlatformUserId GetPlatformUserForUserIndex(int32 LocalUserIndex) = 0;` — Remap the legacy platform LocalUserIndex (often the same as ControllerId) to a FPlatformUserId. This is useful in cases where the input device id is not needed. @param LocalUserIndex	A platform user index where 0 should always be a valid user @returns					A platform-allocated user id, or PLATFORMUSERID_NONE
- L275 _public prototype_ `virtual FPlatformUserId AllocateNewUserId() = 0;` — Allocates a new user id when a user becomes active, will return none if no more can be created
- L278 _public prototype_ `virtual FInputDeviceId AllocateNewInputDeviceId() = 0;` — Returns the next available input device id. This ID should be globally unique!
- L280 _public prototype_ `virtual const EInputDeviceMappingPolicy GetCurrentDeviceMappingPolicy() const;`
- L287 _protected prototype_ `virtual void BindCoreDelegates();` — Binds to any core delegates that the platform may broadcast. By default it is only the OnUserLoginChangedEvent delegate. Called during the constructor of this device mapper.
- L293 _protected prototype_ `virtual void UnbindCoreDelegates();` — Unbind from any delegates that have been hooked into. Called during the destructor of this device mapper.
- L296 _protected prototype_ `virtual void OnUserLoginChangedEvent(bool bLoggedIn, int32 UserId, int32 UserIndex) = 0;` — Callback for when FCoreDelegates::OnUserLoginChangedEvent is broadcasted
- L302 _protected prototype_ `virtual bool IsUsingControllerIdAsUserId() const = 0;` — If true, this device mapper is operating in a backward compatible mode where there is a 1:1 mapping between controller id and user id
- L309 _protected prototype_ `virtual bool ShouldCreateUniqueUserForEachDevice() const;` — If true, then when we remap the platform's raw int32 ControllerId to its FInputDeviceId and owning FPlatformUserId we should create a new platform user id if this controller id is not already mapped.
- L317 _protected prototype_ `virtual bool ShouldBroadcastLegacyDelegates() const = 0;` — If true, than this device mapper will broadcast the older CoreDelegates as well as the new delegates. Set this to true if your platform needs calls from OnControllerConnectionChange or OnControllerPairingChange
- L323 _protected member_ `static FOnInputDeviceHardwareInfoAvailable OnInputDeviceHardwareInfoAvailable;` — Callback which is fired right before the actual OnInputDeviceConnectionChange function for any systems which want to be notified before any game code is, if there is a valid FInputDeviceScope.
- L326 _protected member_ `static FOnUserInputDeviceConnectionChange OnInputDeviceConnectionChange;` — Callback when input devices are disconnected/reconnected
- L329 _protected member_ `static FOnUserInputDevicePairingChange OnInputDevicePairingChange;` — Callback when an input device's owning platform user pairing changes
- L332 _protected member_ `TMap<FInputDeviceId, FPlatformInputDeviceState> MappedInputDevices;` — A map of all input devices to their current state
- L335 _protected member_ `FPlatformUserId LastPlatformUserId = PLATFORMUSERID_NONE;` — Highest used platform user id. Incremented in AllocateNewUserId and Internal_MapInputDeviceToUser by default.
- L338 _protected member_ `FInputDeviceId LastInputDeviceId = INPUTDEVICEID_NONE;` — Highest used input device id. Incremented in AllocateNewInputDeviceId and Internal_MapInputDeviceToUser by default.
- L341 _protected member_ `TArray<FPlatformUserId> AllocatedPlatformUserIds;` — Keeps track of any allocated platform user ID's by this device mapper.

#### class `FGenericPlatformInputDeviceMapper`  
`class FGenericPlatformInputDeviceMapper : public IPlatformInputDeviceMapper`  
_L348-386_
- inherits: `IPlatformInputDeviceMapper`
- desc: Generic implementation of the IPlatformInputDeviceMapper. This provides the base functionality that can be used on most platforms.
- L352 _public prototype_ `FGenericPlatformInputDeviceMapper(const bool InbUsingControllerIdAsUserId, const bool InbShouldBroadcastLegacyDelegates);`
- L355 _public prototype_ `virtual FPlatformUserId GetUserForUnpairedInputDevices() const override;` — This is unsupported by default and will return PLATFORMUSERID_NONE on the generic platform
- L356 _public prototype_ `virtual FPlatformUserId GetPrimaryPlatformUser() const override;`
- L357 _public prototype_ `virtual FInputDeviceId GetDefaultInputDevice() const override;`
- L359 _public prototype_ `virtual bool RemapControllerIdToPlatformUserAndDevice(int32 ControllerId, FPlatformUserId& InOutUserId, FInputDeviceId& OutInputDeviceId) override;`
- L360 _public prototype_ `virtual FPlatformUserId GetPlatformUserForUserIndex(int32 LocalUserIndex) override;`
- L361 _public prototype_ `virtual bool RemapUserAndDeviceToControllerId(FPlatformUserId UserId, int32& OutControllerId, FInputDeviceId OptionalDeviceId = INPUTDEVICEID_NONE) override;`
- L362 _public prototype_ `virtual int32 GetUserIndexForPlatformUser(FPlatformUserId UserId) override;`
- L363 _public prototype_ `virtual bool IsUsingControllerIdAsUserId() const override;`
- L364 _public prototype_ `virtual bool ShouldBroadcastLegacyDelegates() const override;`
- L367 _public prototype_ `virtual FPlatformUserId AllocateNewUserId() override;` — Allocates a new user id when a user becomes active, will return none if no more can be created
- L370 _public prototype_ `virtual FInputDeviceId AllocateNewInputDeviceId() override;` — Returns the next available input device id
- L378 _protected prototype_ `virtual void OnUserLoginChangedEvent(bool bLoggedIn, int32 RawPlatformUserId, int32 UserIndex) override;` — Callback for when FCoreDelegates::OnUserLoginChangedEvent is broadcasted. If the user has logged out, then remap any input devices that the user had to the "Unpaired" user on this platform (if bUnpairInputDevicesWhenLoggingOut is true)
- L381 _protected member_ `const bool bUsingControllerIdAsUserId = true;` — Flags for backwards compatibility with the older "int32 ControllerId" implementation
- L382 _protected member_ `const bool bShouldBroadcastLegacyDelegates = true;`
- L385 _protected member_ `bool bUnpairInputDevicesWhenLoggingOut = false;` — Additional functionality that specializations can customize

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInputDeviceMapper, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInputDeviceMapper, Log, All);`
- L194 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnInputDeviceHardwareInfoAvailable, EInputDeviceConnectionState , FPlatformUserId , FInputDeviceId );` — Callback which is fired before the "user" input device connection change. When this is fired, the input device metadata may not yet be populated. This is intended for any "lower level" systems which want to directly access device connection changes before other engine plugins and game code does. This should only be fired if there is a valid FInputDeviceScope which can be used to derive the hardware info from. @param NewConnectionState	The new connection state of this device @param FPlatformUserId		The User ID whose input device has changed @param FInputDeviceId		The Input Device ID that has changed connection
- L203 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUserInputDeviceConnectionChange, EInputDeviceConnectionState , FPlatformUserId , FInputDeviceId );` — Callback for handling an Input Device's connection state change. @param NewConnectionState	The new connection state of this device @param FPlatformUserId		The User ID whose input device has changed @param FInputDeviceId		The Input Device ID that has changed connection
- L212 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUserInputDevicePairingChange, FInputDeviceId , FPlatformUserId , FPlatformUserId );` — Callback for handling an Input Device pairing change. @param FInputDeviceId	Input device ID @param FPlatformUserId	The NewUserPlatformId @param FPlatformUserId	The OldUserPlatformId

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/GenericPlatformSoftwareCursor.h` (Public)


#### class `FGenericPlatformSoftwareCursor`  
`class FGenericPlatformSoftwareCursor : public ICursor`  
_L13-50_
- inherits: `ICursor`
- L17 _public prototype_ `FGenericPlatformSoftwareCursor();`
- L19 _public prototype_ `virtual ~FGenericPlatformSoftwareCursor() = default;`
- L21 _public function_ `virtual FVector2D GetPosition() const override`
- L26 _public prototype_ `virtual void SetPosition(const int32 X, const int32 Y) override;`
- L28 _public prototype_ `virtual void SetType(const EMouseCursor::Type InNewCursor) override;`
- L30 _public function_ `virtual EMouseCursor::Type GetType() const override`
- L35 _public prototype_ `virtual void GetSize(int32& Width, int32& Height) const override;`
- L37 _public prototype_ `virtual void Show(bool bInShow) override;`
- L39 _public prototype_ `virtual void Lock(const RECT* const Bounds) override;`
- L41 _public function_ `virtual void SetTypeShape(EMouseCursor::Type InCursorType, void* CursorHandle) override`
- L44 _private prototype_ `bool UpdateCursorClipping(FVector2D& CursorPosition);`
- L46 _private member_ `EMouseCursor::Type CurrentType;`
- L47 _private member_ `FVector2D CurrentPosition;`
- L48 _private member_ `FIntRect CursorClipRect;`
- L49 _private member_ `bool bShow;`

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/GenericPlatformSplash.h` (Public)


#### enum `SplashTextType::Type`  
`enum Type`  
_L16-44_
- L19 _public enumerator_ `StartupProgress = 0` — Startup progress text
- L22 _public enumerator_ `VersionInfo1` — Version information text line 1
- L25 _public enumerator_ `CopyrightInfo` — Copyright information text
- L28 _public enumerator_ `GameName` — Game Name
- L33 _public enumerator_ `User1` — Licensee-usable slots
- L34 _public enumerator_ `User2`
- L35 _public enumerator_ `User3`
- L36 _public enumerator_ `User4`
- L37 _public enumerator_ `User5`
- L38 _public enumerator_ `User6`
- L43 _public enumerator_ `NumTextTypes` — Number of text types (must be final enum value)

#### enum `SplashImageType::Type`  
`enum Type`  
_L52-71_
- L55 _public enumerator_ `Background` — The main background image
- L60 _public enumerator_ `User1` — Licensee-usable slots
- L61 _public enumerator_ `User2`
- L62 _public enumerator_ `User3`
- L63 _public enumerator_ `User4`
- L64 _public enumerator_ `User5`
- L65 _public enumerator_ `User6`
- L70 _public enumerator_ `NumImageTypes` — Number of image types (must be final enum value)

#### enum `ESplashTextSizeType`  
`enum class ESplashTextSizeType : uint8`  
_L74-79_
- L76 _public enumerator_ `Small`
- L77 _public enumerator_ `Normal`
- L78 _public enumerator_ `Title`

#### enum `ESplashTextBrightnessType`  
`enum class ESplashTextBrightnessType : uint8`  
_L81-86_
- L83 _public enumerator_ `Low`
- L84 _public enumerator_ `Medium`
- L85 _public enumerator_ `High`

#### enum `ESplashTextFlags`  
`enum class ESplashTextFlags : uint8`  
_L88-92_
- L90 _public enumerator_ `None`
- L91 _public enumerator_ `WordWrap = 1 << 0`

#### struct `FGenericPlatformSplash`  
`struct FGenericPlatformSplash`  
_L101-169_
- desc: Generic implementation for most platforms
- L104 _public function_ `inline static void Show()` — Show the splash screen.
- L107 _public function_ `inline static void Hide()` — Hide the splash screen.
- L114 _public prototype_ `static void SetCustomSplashImage(const TCHAR* SplashFilename);` — Sets a custom splash image to display @param SplashFilename Full path to the splash image to display
- L122 _public function_ `inline static void SetProgress(int ProgressPercent)` — Sets the progress displayed on the application icon (for startup/loading progress). @param ProgressPercent Progress value in percent.
- L134 _public prototype_ `static void SetSplashText( const SplashTextType::Type InType, const TCHAR* InText );` — `UE_DEPRECATED(5.6, "Use the overload of FPlatformSlash::SetSplashText that takes a FText")` — Sets the text displayed on the splash screen (for startup/loading progress) @param	InType		Type of text to change @param	InText		Text to display
- L135 _public function_ `inline static void SetSplashText(const SplashTextType::Type InType, const FText& InText)`
- L140 _public function_ `inline static void SetSplashImage(const SplashImageType::Type InType, const TCHAR* InFilename)` — Sets the image to be assigned to the specific slot
- L143 _public function_ `inline static void RegisterUserSplashText(const SplashTextType::Type InType, const FPlatformRect& InRect, ESplashTextSizeType InSize, ESplashTextBrightnessType InBrightness, ESplashTextFlags Flags = ESplashTextFlags::None)` — Registers a new licensee text. Only User types are allowed, and only before the splash screen is initialized!
- L146 _public function_ `inline static void RegisterUserSplashImage(const SplashImageType::Type InType, const FIntPoint& InPos, const TCHAR* InFilename)` — Registers a new licensee image. Only User types are allowed, and only before the splash screen is initialized!
- L151 _public function_ `inline static bool IsShown()` — Return whether the splash screen is being shown or not
- L167 _protected prototype_ `static bool GetSplashPath(const TCHAR* SplashFilename, FString& OutPath, bool& OutIsCustom, bool bAllowCustom = true);` — Finds a usable splash pathname for the given filename @param SplashFilename Name of the desired splash name("Splash") @param IconFilename Name of the desired icon name("Splash") @param OutPath String containing the path to the file, if this function returns true @param OutIconPath String containing the path to the icon, if this function returns true @return true if a splash screen was found
- L168 _protected prototype_ `static bool GetSplashPath(const TCHAR* SplashFilename, const TCHAR* IconFilename, FString& OutPath, FString& OutIconPath, bool& OutIsCustom);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace SplashTextType`
- L50 _namespace_ `namespace SplashImageType`

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/GenericPlatformSurvey.h` (Public)


#### struct `FTimeSample`  
`struct FTimeSample`  
_L14-26_
- desc: time and amount of work that was measured
- L16 _public function_ `FTimeSample(float InTotalTime, float InNormalizedTime) : TotalTime(InTotalTime) , NormalizedTime(InNormalizedTime)`
- L23 _public member_ `float TotalTime;` — in seconds, >=0
- L25 _public member_ `float NormalizedTime;` — Time / WorkScale, WorkScale might have been adjusted (e.g. quantized), >0

#### struct `FSynthBenchmarkStat`  
`struct FSynthBenchmarkStat`  
_L29-120_
- L31 _public function_ `FSynthBenchmarkStat() : Desc(0) , MeasuredTotalTime(-1) , MeasuredNormalizedTime(-1) , IndexNormalizedTime(-1) , ValueType(0) , Confidence(0) , Weight(1.f)`
- L42 _public function_ `FSynthBenchmarkStat(const TCHAR* InDesc, float InIndexNormalizedTime, const TCHAR* InValueType, float InWeight) : Desc(InDesc) , MeasuredTotalTime(-1) , MeasuredNormalizedTime(-1) , IndexNormalizedTime(InIndexNormalizedTime) , ValueType(InValueType) , Confidence(0) , Weight(InWeight)` — @param InDesc descriptions
- L56 _public function_ `float ComputePerfIndex() const` — Computes the linear performance index (>0), around 100 with good hardware but higher numbers are possible
- L63 _public function_ `void SetMeasuredTime(const FTimeSample& TimeSample, float InConfidence = 90)` — @param TimeSample seconds and normalized time (e.g. seconds / GPixels) @param InConfidence 0..100
- L72 _public function_ `const TCHAR* GetDesc() const` — @return can be 0
- L78 _public function_ `const TCHAR* GetValueType() const` — @return can be 0
- L83 _public function_ `float GetNormalizedTime() const`
- L88 _public function_ `float GetMeasuredTotalTime() const`
- L94 _public function_ `float GetConfidence() const` — @return 0=no..100=full
- L99 _public function_ `float GetWeight() const`
- L107 _private member_ `const TCHAR *Desc;` — 0 if not valid
- L109 _private member_ `float MeasuredTotalTime;` — -1 if not defined, in seconds, useful to see if a test did run too long (some slower GPUs might timeout)
- L111 _private member_ `float MeasuredNormalizedTime;` — -1 if not defined, depends on the test (e.g. s/GPixels), WorkScale is divided out
- L113 _private member_ `float IndexNormalizedTime;` — -1 if not defined, timing value expected on a norm GPU (index value 100, here NVidia 670)
- L115 _private member_ `const TCHAR *ValueType;` — 0 if not valid
- L117 _private member_ `float Confidence;` — 0..100, 100: fully confident
- L119 _private member_ `float Weight;` — 1 is normal weight, 0 is no weight, > 1 is unbounded additional weight

#### struct `FSynthBenchmarkResults`  
`struct FSynthBenchmarkResults`  
_L123-145_
- L125 _public member_ `FSynthBenchmarkStat CPUStats[2];`
- L126 _public member_ `FSynthBenchmarkStat GPUStats[7];`
- L129 _public prototype_ `float ComputeCPUPerfIndex(TArray<float>* OutIndividualResults = nullptr) const;` — 100: avg good CPU, <100:slower, >100:faster
- L132 _public prototype_ `float ComputeGPUPerfIndex(TArray<float>* OutIndividualResults = nullptr) const;` — 100: avg good GPU, <100:slower, >100:faster
- L135 _public function_ `float ComputeTotalGPUTime() const` — @return in seconds, useful to check if a benchmark takes too long (very slow hardware, don't make tests with large WorkScale)

#### struct `FHardwareDisplay`  
`struct FHardwareDisplay`  
_L148-158_
- L150 _public member_ `static const uint32 MaxStringLength = 260;`
- L152 _public member_ `uint32 CurrentModeWidth;`
- L153 _public member_ `uint32 CurrentModeHeight;`
- L155 _public member_ `TCHAR GPUCardName_DEPRECATED[MaxStringLength];`
- L156 _public member_ `uint32 GPUDedicatedMemoryMB_DEPRECATED;`
- L157 _public member_ `TCHAR GPUDriverVersion_DEPRECATED[MaxStringLength];`

#### struct `FGPUAdpater`  
`struct FGPUAdpater`  
_L161-174_
- L163 _public member_ `static const uint32 MaxStringLength = 260;`
- L165 _public member_ `TCHAR AdapterName[MaxStringLength];`
- L167 _public member_ `TCHAR AdapterInternalDriverVersion[MaxStringLength];`
- L169 _public member_ `TCHAR AdapterUserDriverVersion[MaxStringLength];` — extra data when RHI starts up, AMD has the Catalyst Driver version which is more useful for the user, otherwise it's the same as GRHIAdapterInternalDriverVersion
- L171 _public member_ `TCHAR AdapterDriverDate[MaxStringLength];` — extra data when RHI starts up
- L173 _public member_ `TCHAR AdapterDedicatedMemoryMB[MaxStringLength];`

#### struct `FHardwareSurveyResults`  
`struct FHardwareSurveyResults`  
_L177-221_
- L179 _public member_ `static const int32 MaxDisplayCount = 8;`
- L180 _public member_ `static const int32 MaxStringLength = 260;`
- L182 _public member_ `TCHAR Platform[MaxStringLength];`
- L184 _public member_ `TCHAR OSVersion[MaxStringLength];`
- L185 _public member_ `TCHAR OSSubVersion[MaxStringLength];`
- L186 _public member_ `uint32 OSBits;`
- L187 _public member_ `TCHAR OSLanguage[MaxStringLength];`
- L189 _public member_ `TCHAR RenderingAPI[MaxStringLength];`
- L190 _public member_ `TCHAR MultimediaAPI_DEPRECATED[MaxStringLength];`
- L192 _public member_ `uint32 HardDriveGB;`
- L193 _public member_ `uint32 HardDriveFreeMB;`
- L194 _public member_ `uint32 MemoryMB;`
- L196 _public member_ `float CPUPerformanceIndex;`
- L197 _public member_ `float GPUPerformanceIndex;`
- L198 _public member_ `float RAMPerformanceIndex;`
- L200 _public member_ `uint32 bIsLaptopComputer:1;`
- L201 _public member_ `uint32 bIsRemoteSession:1;`
- L203 _public member_ `uint32 CPUCount;`
- L204 _public member_ `float CPUClockGHz;`
- L205 _public member_ `TCHAR CPUBrand[MaxStringLength];`
- L206 _public member_ `TCHAR CPUNameString[MaxStringLength];`
- L207 _public member_ `uint32 CPUInfo;`
- L209 _public member_ `uint32 DisplayCount;`
- L210 _public member_ `FHardwareDisplay Displays[MaxDisplayCount];`
- L212 _public member_ `FGPUAdpater RHIAdapter;` — RHI chosen adapter, only if RHI started on Windows DX11
- L214 _public member_ `uint32 ErrorCount;`
- L215 _public member_ `TCHAR LastSurveyError[MaxStringLength];`
- L216 _public member_ `TCHAR LastSurveyErrorDetail[MaxStringLength];`
- L217 _public member_ `TCHAR LastPerformanceIndexError[MaxStringLength];`
- L218 _public member_ `TCHAR LastPerformanceIndexErrorDetail[MaxStringLength];`
- L220 _public member_ `FSynthBenchmarkResults SynthBenchmark;`

#### struct `FGenericPlatformSurvey`  
`struct FGenericPlatformSurvey`  
_L227-241_
- desc: Generic implementation for most platforms, these tend to be unused and unimplemented
- L237 _public function_ `static bool GetSurveyResults( FHardwareSurveyResults& OutResults, bool bWait = false )` — Attempt to get hardware survey results now. If they aren't available the survey will be started/ticked until complete. @param OutResults	The struct that receives the results if available. @param bWait			If true, the function won't return until the results are available or the survey fails. Defaults to false. @return				True if the results were available, false otherwise.

#### Free symbols / members of external scopes

- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSynthBenchmark, Log, All);`

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/GenericWindow.h` (Public)


#### enum `EWindowMode::Type`  
`enum Type : int`  
_L16-27_
- L19 _public enumerator_ `Fullscreen` — The window is in true fullscreen mode
- L21 _public enumerator_ `WindowedFullscreen` — The window has no border and takes up the entire area of the screen
- L23 _public enumerator_ `Windowed` — The window has a border and may not take up the entire screen area
- L26 _public enumerator_ `NumWindowModes` — The total number of supported window modes

#### enum `EWindowDrawAttentionRequestType`  
`enum class EWindowDrawAttentionRequestType`  
_L61-73_
- L67 _public enumerator_ `UntilActivated` — Indicates that the attention-drawing behavior continues until the application or window is activated.
- L72 _public enumerator_ `Stop` — Indicates that the attention-drawing behavior, if any, should stop.

#### struct `FWindowDrawAttentionParameters`  
`struct FWindowDrawAttentionParameters`  
_L79-91_
- desc: Parameters for drawing attention to a window or application. Some parameters may only be used on certain platforms.
- L81 _public prototype_ `FWindowDrawAttentionParameters() = default;`
- L83 _public function_ `explicit FWindowDrawAttentionParameters( EWindowDrawAttentionRequestType InRequestType ) : RequestType(InRequestType)`
- L90 _public member_ `EWindowDrawAttentionRequestType RequestType = EWindowDrawAttentionRequestType::UntilActivated;`

#### class `FGenericWindow`  
`class FGenericWindow`  
_L93-248_
- L97 _public prototype_ `FGenericWindow();`
- L99 _public prototype_ `virtual ~FGenericWindow();`
- L102 _public prototype_ `virtual void ReshapeWindow( int32 X, int32 Y, int32 Width, int32 Height );` — Native windows should implement ReshapeWindow by changing the platform-specific window to be located at (X,Y) and be the dimensions Width x Height.
- L105 _public prototype_ `virtual bool GetFullScreenInfo( int32& X, int32& Y, int32& Width, int32& Height ) const;` — Returns the rectangle of the screen the window is associated with
- L108 _public prototype_ `virtual void MoveWindowTo ( int32 X, int32 Y );` — Native windows should implement MoveWindowTo by relocating the platform-specific window to (X,Y).
- L111 _public prototype_ `virtual void BringToFront( bool bForce = false );` — Native windows should implement BringToFront by making this window the top-most window (i.e. focused).
- L114 _public prototype_ `virtual void HACK_ForceToFront();` — @hack Force a window to front even if a different application is in front.
- L117 _public prototype_ `virtual void Destroy();` — Native windows should implement this function by asking the OS to destroy OS-specific resource associated with the window (e.g. Win32 window handle)
- L120 _public prototype_ `virtual void Minimize();` — Native window should implement this function by performing the equivalent of the Win32 minimize-to-taskbar operation
- L123 _public prototype_ `virtual void Maximize();` — Native window should implement this function by performing the equivalent of the Win32 maximize operation
- L126 _public prototype_ `virtual void Restore();` — Native window should implement this function by performing the equivalent of the Win32 restore operation
- L129 _public prototype_ `virtual void Show();` — Native window should make itself visible
- L132 _public prototype_ `virtual void Hide();` — Native window should hide itself
- L135 _public prototype_ `virtual void SetWindowMode( EWindowMode::Type InNewWindowMode );` — Toggle native window between fullscreen and normal mode
- L138 _public prototype_ `virtual EWindowMode::Type GetWindowMode() const;` — @return true if the native window is currently in fullscreen mode, false otherwise
- L141 _public prototype_ `virtual bool IsMaximized() const;` — @return true if the native window is maximized, false otherwise
- L144 _public prototype_ `virtual bool IsMinimized() const;` — @return true if the native window is minimized, false otherwise
- L147 _public prototype_ `virtual bool IsVisible() const;` — @return true if the native window is visible, false otherwise
- L155 _public prototype_ `virtual bool GetRestoredDimensions(int32& X, int32& Y, int32& Width, int32& Height);` — Populates the size and location of the window when it is restored. If the function fails, false is returned and X,Y,Width,Height will be undefined. @return true when the size and location and successfully retrieved; false otherwise.
- L161 _public prototype_ `virtual void SetWindowFocus();` — Native windows should implement SetWindowFocus to let the OS know that a window has taken focus. Slate handles focus on a per widget basis internally but the OS still needs to know what window has focus for proper message routing
- L168 _public prototype_ `virtual void SetOpacity( const float InOpacity );` — Sets the opacity of this window @param	InOpacity	The new window opacity represented as a floating point scalar
- L175 _public prototype_ `virtual void Enable( bool bEnable );` — Enables or disables the window.  If disabled the window receives no input @param bEnable	true to enable the window, false to disable it.
- L178 _public prototype_ `virtual bool IsPointInWindow( int32 X, int32 Y ) const;` — @return true if native window exists underneath the coordinates
- L181 _public prototype_ `virtual int32 GetWindowBorderSize() const;` — Gets OS specific window border size. This is necessary because Win32 does not give control over this size.
- L184 _public prototype_ `virtual int32 GetWindowTitleBarSize() const;` — Gets OS specific window title bar size
- L187 _public prototype_ `virtual void* GetOSWindowHandle() const;` — Gets the OS Window handle in the form of a void pointer for other API's
- L190 _public prototype_ `virtual bool IsForegroundWindow() const;` — @return true if the window is in the foreground
- L193 _public prototype_ `virtual bool SupportsDynamicCursorLock() const;` — @return true if the window supports dynamic cursor locking
- L196 _public prototype_ `virtual bool IsFullscreenSupported() const;` — @return true if the window supports fullscreen
- L203 _public prototype_ `virtual void SetText(const TCHAR* const Text);` — Sets the window text - usually the title but can also be text content for things like controls @param Text	The window's title or content text
- L206 _public prototype_ `virtual const FGenericWindowDefinition& GetDefinition() const;` — @return	The definition describing properties of the window
- L209 _public prototype_ `virtual bool IsDefinitionValid() const;` — @return	Returns true if the window definition is valid
- L212 _public prototype_ `virtual void AdjustCachedSize( FVector2D& Size ) const;` — @return	Gives the native window a chance to adjust our stored window size before we cache it off
- L218 _public prototype_ `virtual float GetDPIScaleFactor() const;` — @return ratio of pixels to SlateUnits in this window. E.g. DPIScale of 2.0 means there is a 2x2 pixel square for every 1x1 SlateUnit.
- L221 _public prototype_ `virtual void SetDPIScaleFactor(const float Factor);` — sets a new DPI scale factor
- L224 _public prototype_ `virtual bool IsManualManageDPIChanges() const;` — determines whether or not this window does its own DPI management
- L227 _public prototype_ `virtual void SetManualManageDPIChanges(const bool bAutoHandle);` — call with a true argument if this window need to do its custom size management in response to DPI variations
- L237 _public prototype_ `virtual void DrawAttention(const FWindowDrawAttentionParameters& Parameters);` — Attempts to draw the user's attention to this window in whatever way is appropriate for the platform if this window is not the current active window. @param Parameters The parameters for drawing attention. Depending on the platform, not all parameters may be supported.
- L240 _public prototype_ `virtual void SetNativeWindowButtonsVisibility(bool bVisible);` — Shows or hides native window buttons on platforms that use them
- L243 _public prototype_ `virtual bool IsRenderingOffScreen() const;` — Returns true if this window will not be used for presenting rendered frames to a display.
- L247 _protected member_ `TSharedPtr< FGenericWindowDefinition > Definition;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace EWindowMode`
- L29 _function_ `inline Type ConvertIntToWindowMode(int32 InWindowMode)` (scope `EWindowMode`)
- L49 _function_ `inline const TCHAR* LexToString(EWindowMode::Type WindowMode)`

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/GenericWindowDefinition.h` (Public)


#### enum `EWindowType`  
`enum class EWindowType`  
_L16-30_
- desc: Enumeration to specify different window types for SWindows
- L19 _public enumerator_ `Normal` — Value indicating that this is a standard, general-purpose window
- L21 _public enumerator_ `Menu` — Value indicating that this is a window used for a popup menu
- L23 _public enumerator_ `ToolTip` — Value indicating that this is a window used for a tooltip
- L25 _public enumerator_ `Notification` — Value indicating that this is a window used for a notification toast
- L27 _public enumerator_ `CursorDecorator` — Value indicating that this is a window used for a cursor decorator
- L29 _public enumerator_ `GameWindow UE_DEPRECATED(5.8, "There is no longer any meaningful distinction between game and normal window. Use Normal instead. Windows now opt in to the Slate Console Debugger using a boolean property.")`

#### enum `EWindowTransparency`  
`enum class EWindowTransparency`  
_L34-46_
- desc: Enumeration to specify different transparency options for SWindows
- L37 _public enumerator_ `None` — Value indicating that a window does not support transparency
- L40 _public enumerator_ `PerWindow` — Value indicating that a window supports transparency at the window level (one opacity applies to the entire window)
- L44 _public enumerator_ `PerPixel` — Value indicating that a window supports per-pixel alpha blended transparency

#### enum `EWindowActivationPolicy`  
`enum class EWindowActivationPolicy`  
_L50-60_
- desc: Enumeration to specify whether the window gets activated upon showing it
- L53 _public enumerator_ `Never` — Value indicating that a window never activates when it is shown
- L56 _public enumerator_ `Always` — Value indicating that a window always activates when it is shown
- L59 _public enumerator_ `FirstShown` — Value indicating that a window only activates when it is first shown

#### struct `FGenericWindowDefinition`  
`struct FGenericWindowDefinition`  
_L63-126_
- L66 _public member_ `EWindowType Type;` — Window type
- L69 _public member_ `float XDesiredPositionOnScreen;` — The initially desired horizontal screen position
- L71 _public member_ `float YDesiredPositionOnScreen;` — The initially desired vertical screen position
- L74 _public member_ `float WidthDesiredOnScreen;` — The initially desired width
- L76 _public member_ `float HeightDesiredOnScreen;` — The initially desired height
- L79 _public member_ `EWindowTransparency TransparencySupport;` — the level of transparency supported by this window
- L82 _public member_ `bool HasOSWindowBorder;` — true if the window is using the os window border instead of a slate created one
- L84 _public member_ `bool AppearsInTaskbar;` — should this window show up in the taskbar
- L86 _public member_ `bool IsTopmostWindow;` — true if the window should be on top of all other windows; false otherwise
- L88 _public member_ `bool AcceptsInput;` — true if the window accepts input; false if the window is non-interactive
- L90 _public member_ `EWindowActivationPolicy ActivationPolicy;` — the policy for activating the window upon each show
- L92 _public member_ `bool FocusWhenFirstShown;` — true if this window will be focused when it is first shown
- L94 _public member_ `bool HasCloseButton;` — true if this window displays an enabled close button on the toolbar area
- L96 _public member_ `bool SupportsMinimize;` — true if this window displays an enabled minimize button on the toolbar area
- L98 _public member_ `bool SupportsMaximize;` — true if this window displays an enabled maximize button on the toolbar area
- L101 _public member_ `bool IsModalWindow;` — true if the window is modal (prevents interacting with its parent)
- L103 _public member_ `bool IsRegularWindow;` — true if this is a vanilla window, or one being used for some special purpose: e.g. tooltip or menu
- L105 _public member_ `bool HasSizingFrame;` — true if this is a user-sized window with a thick edge
- L107 _public member_ `bool SizeWillChangeOften;` — true if we expect the size of this window to change often, such as if its animated, or if it recycled for tool-tips.
- L109 _public member_ `bool ShouldPreserveAspectRatio;` — true if the window should preserve its aspect ratio when resized by user
- L111 _public member_ `int32 ExpectedMaxWidth;` — The expected maximum width of the window.  May be used for performance optimization when SizeWillChangeOften is set.
- L113 _public member_ `int32 ExpectedMaxHeight;` — The expected maximum height of the window.  May be used for performance optimization when SizeWillChangeOften is set.
- L116 _public member_ `FString Title;` — the title of the window
- L118 _public member_ `float Opacity;` — opacity of the window (0-1)
- L120 _public member_ `int32 CornerRadius;` — the radius of the corner rounding of the window
- L122 _public member_ `FWindowSizeLimits SizeLimits;`
- L125 _public member_ `bool bManualDPI = false;` — false if the window should respond to system DPI changes, otherwise this will be handled, internally, by the application

#### Free symbols / members of external scopes

- L11 _macro_ `#define ALPHA_BLENDED_WINDOWS IS_PROGRAM || WITH_EDITOR`

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/ICursor.h` (Public)


#### enum `EMouseCursor::Type`  
`enum Type : int`  
_L18-67_
- L21 _public enumerator_ `None` — Causes no mouse cursor to be visible
- L24 _public enumerator_ `Default` — Default cursor (arrow)
- L27 _public enumerator_ `TextEditBeam` — Text edit beam
- L30 _public enumerator_ `ResizeLeftRight` — Resize horizontal
- L33 _public enumerator_ `ResizeUpDown` — Resize vertical
- L36 _public enumerator_ `ResizeSouthEast` — Resize diagonal
- L39 _public enumerator_ `ResizeSouthWest` — Resize other diagonal
- L42 _public enumerator_ `CardinalCross` — MoveItem
- L45 _public enumerator_ `Crosshairs` — Target Cross
- L48 _public enumerator_ `Hand` — Hand cursor
- L51 _public enumerator_ `GrabHand` — Grab Hand cursor
- L54 _public enumerator_ `GrabHandClosed` — Grab Hand cursor closed
- L57 _public enumerator_ `SlashedCircle` — a circle with a diagonal line through it
- L60 _public enumerator_ `EyeDropper` — Eye-dropper cursor for picking colors
- L63 _public enumerator_ `Custom` — Custom cursor shape for platforms that support setting a native cursor shape. Same as specifying None if not set.
- L66 _public enumerator_ `TotalCursorCount` — Number of cursors we support

#### class `ICursor`  
`class ICursor`  
_L74-126_
- L77 _public prototype_ `virtual ~ICursor() = default;`
- L80 _public function_ `virtual void* CreateCursorFromFile(const FString& InPathToCursorWithoutExtension, FVector2D HotSpot)` — Creates a hardware cursor from file. Can return nullptr when not available.
- L83 _public function_ `virtual bool IsCreateCursorFromRGBABufferSupported() const` — Is CreateCursorFromRGBABuffer() supported by this cursor?
- L86 _public function_ `virtual void* CreateCursorFromRGBABuffer(const FColor* Pixels, int32 Width, int32 Height, FVector2D InHotSpot)` — Creates a hardware cursor from bitmap data. Can return nullptr when not available.
- L89 _public prototype_ `virtual FVector2D GetPosition() const = 0;` — The position of the cursor
- L92 _public prototype_ `virtual void SetPosition( const int32 X, const int32 Y ) = 0;` — Sets the position of the cursor
- L95 _public prototype_ `virtual void SetType( const EMouseCursor::Type InNewCursor ) = 0;` — Sets the cursor
- L98 _public prototype_ `virtual EMouseCursor::Type GetType() const = 0;` — Gets the current type of the cursor
- L101 _public prototype_ `virtual void GetSize( int32& Width, int32& Height ) const = 0;` — Gets the size of the cursor
- L108 _public prototype_ `virtual void Show( bool bShow ) = 0;` — Shows or hides the cursor @param bShow	true to show the mouse cursor, false to hide it
- L113 _public function_ `virtual void Tick()` — Perform operations that can't be done on an event-basis
- L120 _public prototype_ `virtual void Lock( const RECT* const Bounds ) = 0;` — Locks the cursor to the passed in bounds @param Bounds	The bounds to lock the cursor to.  Pass NULL to unlock.
- L125 _public prototype_ `virtual void SetTypeShape(EMouseCursor::Type InCursorType, void* CursorHandle) = 0;` — Allows overriding the shape of a particular cursor.

#### Free symbols / members of external scopes

- L10 _typedef_ `typedef struct tagRECT RECT;`
- L16 _namespace_ `namespace EMouseCursor`
- L71 _prototype_ `template<> UEnum* StaticEnum<EMouseCursor::Type>();`

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/IForceFeedbackSystem.h` (Public)


#### class `IForceFeedbackSystem`  
`class IForceFeedbackSystem : public IInputInterface`  
_L23-29_
- reflection: `UE_DEPRECATED(5.1, "IForceFeedbackSystem has been deprecated, use IInputInterface instead.")`
- inherits: `IInputInterface`
- desc: Interface for the force feedback system. Note: This class is deprecated and will be removed in favor of IInputInterface
- L28 _public prototype_ `virtual ~IForceFeedbackSystem() = default;`

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/IInputInterface.h` (Public)


#### enum `FForceFeedbackChannelType`  
`enum class FForceFeedbackChannelType`  
_L17-23_
- desc: General identifiers for potential force feedback channels. These will be mapped according to the platform specific implementation. For example, Platform A only listens to the XXX_LARGE channels and ignores the rest, while Platform B could map the XXX_LARGE to the handle motors and XXX_SMALL to the trigger motors. And others can map LEFT_SMALL to its single motor.
- L19 _public enumerator_ `LEFT_LARGE`
- L20 _public enumerator_ `LEFT_SMALL`
- L21 _public enumerator_ `RIGHT_LARGE`
- L22 _public enumerator_ `RIGHT_SMALL`

#### struct `FForceFeedbackValues`  
`struct FForceFeedbackValues`  
_L26-39_
- L28 _public member_ `float LeftLarge;`
- L29 _public member_ `float LeftSmall;`
- L30 _public member_ `float RightLarge;`
- L31 _public member_ `float RightSmall;`
- L33 _public function_ `FForceFeedbackValues() : LeftLarge(0.f) , LeftSmall(0.f) , RightLarge(0.f) , RightSmall(0.f)`

#### struct `FHapticFeedbackBuffer`  
`struct FHapticFeedbackBuffer`  
_L41-68_
- L43 _public member_ `const uint8* RawData;`
- L44 _public member_ `uint32 CurrentPtr;`
- L45 _public member_ `int BufferLength;`
- L46 _public member_ `int SamplesSent;`
- L47 _public member_ `bool bFinishedPlaying;`
- L48 _public member_ `int SamplingRate;`
- L49 _public member_ `float ScaleFactor;`
- L50 _public member_ `bool bUseStereo;`
- L51 _public member_ `uint32 CurrentSampleIndex[2];`
- L53 _public function_ `FHapticFeedbackBuffer() : CurrentPtr(0) , BufferLength(0) , SamplesSent(0) , bFinishedPlaying(false) , SamplingRate(0) , bUseStereo(false) , CurrentSampleIndex`
- L64 _public function_ `bool NeedsUpdate() const`

#### struct `FHapticFeedbackValues`  
`struct FHapticFeedbackValues`  
_L70-91_
- L72 _public member_ `float Frequency;`
- L73 _public member_ `float Amplitude;`
- L75 _public member_ `FHapticFeedbackBuffer* HapticBuffer;`
- L77 _public function_ `FHapticFeedbackValues() : Frequency(0.f) , Amplitude(0.f) , HapticBuffer(NULL)`
- L84 _public function_ `FHapticFeedbackValues(const float InFrequency, const float InAmplitude)`

#### enum `EInputDeviceTriggerMask`  
`enum class EInputDeviceTriggerMask : uint8`  
_L98-104_
- desc: Represents input device triggers that are available NOTE: Make sure to keep this type in sync with the reflected version in NoExportTypes.h!
- L100 _public enumerator_ `None = 0x00`
- L101 _public enumerator_ `Left = 0x01`
- L102 _public enumerator_ `Right = 0x02`
- L103 _public enumerator_ `All = Left | Right`

#### enum `EInputDeviceAnalogStickMask`  
`enum class EInputDeviceAnalogStickMask : uint8`  
_L116-121_
- desc: Represents input device analog sticks that are available NOTE: Make sure to keep this type in sync with the reflected version in NoExportTypes.h!
- L118 _public enumerator_ `None = 0x00`
- L119 _public enumerator_ `Left = 0x01`
- L120 _public enumerator_ `Right = 0x02`

#### struct `FInputDeviceProperty`  
`struct FInputDeviceProperty`  
_L128-135_
- L130 _public function_ `FInputDeviceProperty(FName InName) : Name(InName)`
- L134 _public member_ `FName Name;`

#### struct `FInputDeviceGyroAutoCalibrationProperty`  
`struct FInputDeviceGyroAutoCalibrationProperty : public FInputDeviceProperty`  
_L138-153_
- inherits: `FInputDeviceProperty`
- desc: A generic gyro calibration property for input devices whose gyroscopes (angular velocity sensors) can have their calibration enabled or disabled
- L140 _public function_ `FInputDeviceGyroAutoCalibrationProperty() : FInputDeviceProperty(PropertyName())`
- L144 _public function_ `FInputDeviceGyroAutoCalibrationProperty(bool bInEnable) : FInputDeviceProperty(PropertyName()) , bEnable(bInEnable)`
- L149 _public function_ `static FName PropertyName()`
- L152 _public member_ `bool bEnable = true;` — If gyro auto calibration should be enabled.

#### struct `FInputDeviceLightColorProperty`  
`struct FInputDeviceLightColorProperty : public FInputDeviceProperty`  
_L156-175_
- inherits: `FInputDeviceProperty`
- desc: A generic light color property for input devices that have lights on them
- L158 _public function_ `FInputDeviceLightColorProperty() : FInputDeviceProperty(PropertyName())`
- L162 _public function_ `FInputDeviceLightColorProperty(bool bInEnable, FColor InColor) : FInputDeviceProperty(PropertyName()) , bEnable(bInEnable) , Color(InColor)`
- L168 _public function_ `static FName PropertyName()`
- L171 _public member_ `bool bEnable = true;` — If the light should be enabled or not.
- L174 _public member_ `FColor Color = FColor::White;` — The color to set the light

#### struct `FInputDeviceTriggerProperty`  
`struct FInputDeviceTriggerProperty : public FInputDeviceProperty`  
_L178-186_
- inherits: `FInputDeviceProperty`
- desc: Base class for device properties that affect Triggers
- L180 _public function_ `FInputDeviceTriggerProperty(FName InName) : FInputDeviceProperty(InName)`
- L185 _public member_ `EInputDeviceTriggerMask AffectedTriggers = EInputDeviceTriggerMask::None;` — Which trigger this property should effect

#### struct `FInputDeviceTriggerResetProperty`  
`struct FInputDeviceTriggerResetProperty : public FInputDeviceTriggerProperty`  
_L189-198_
- inherits: `FInputDeviceTriggerProperty`
- desc: This property can be used to reset the state of a given trigger.
- L191 _public function_ `FInputDeviceTriggerResetProperty() : FInputDeviceTriggerProperty(PropertyName())`
- L197 _public function_ `static FName PropertyName()`

#### struct `FInputDeviceTriggerFeedbackProperty`  
`struct FInputDeviceTriggerFeedbackProperty : public FInputDeviceTriggerProperty`  
_L201-212_
- inherits: `FInputDeviceTriggerProperty`
- desc: Trigger resistance that is applied at a single position with the given strength.
- L203 _public function_ `FInputDeviceTriggerFeedbackProperty() : FInputDeviceTriggerProperty(PropertyName())`
- L207 _public function_ `static FName PropertyName()`
- L209 _public member_ `int32 Position = 0;`
- L211 _public member_ `int32 Strengh = 0;`

#### struct `FInputDeviceTriggerResistanceProperty`  
`struct FInputDeviceTriggerResistanceProperty : public FInputDeviceTriggerProperty`  
_L215-234_
- inherits: `FInputDeviceTriggerProperty`
- desc: A generic trigger effect that allows analog triggers to have a resistance curve between two points (Start and End)
- L217 _public function_ `FInputDeviceTriggerResistanceProperty() : FInputDeviceTriggerProperty(PropertyName())`
- L221 _public function_ `static FName PropertyName()`
- L224 _public member_ `int32 StartPosition = 0;` — The position that the trigger should start providing resistance
- L227 _public member_ `int32 StartStrengh = 0;` — How strong the resistance is
- L230 _public member_ `int32 EndPosition = 0;` — The position that the trigger should start providing resistance
- L233 _public member_ `int32 EndStrengh = 0;` — How strong the resistance is

#### struct `FInputDeviceTriggerVibrationProperty`  
`struct FInputDeviceTriggerVibrationProperty : public FInputDeviceTriggerProperty`  
_L237-250_
- inherits: `FInputDeviceTriggerProperty`
- desc: A generic input device property that sets vibration on triggers
- L239 _public function_ `FInputDeviceTriggerVibrationProperty() : FInputDeviceTriggerProperty(PropertyName())`
- L243 _public function_ `static FName PropertyName()`
- L245 _public member_ `int32 TriggerPosition = 0;`
- L247 _public member_ `int32 VibrationFrequency = 0;`
- L249 _public member_ `int32 VibrationAmplitude = 0;`

#### struct `FInputDeviceAnalogStickProperty`  
`struct FInputDeviceAnalogStickProperty : public FInputDeviceProperty`  
_L253-266_
- inherits: `FInputDeviceProperty`
- desc: Base class for device properties that affect Analog Sticks
- L255 _public function_ `FInputDeviceAnalogStickProperty(FName InName) : FInputDeviceProperty(InName)`
- L259 _public function_ `FInputDeviceAnalogStickProperty(FName InName, EInputDeviceAnalogStickMask InAffectedStick) : FInputDeviceProperty(InName) , AffectedStick(InAffectedStick)`
- L265 _public member_ `EInputDeviceAnalogStickMask AffectedStick = EInputDeviceAnalogStickMask::None;` — Which stick this property should effect

#### struct `FInputDeviceAnalogStickDeadZoneProperty`  
`struct FInputDeviceAnalogStickDeadZoneProperty : public FInputDeviceAnalogStickProperty`  
_L274-288_
- inherits: `FInputDeviceAnalogStickProperty`
- desc: A generic input device property that sets Deadzone for Analog Sticks. NOTE: Not all input device libraries do their own deadzone filtering, so the game must still do it. This is just to tell those device libraries that do some filtering not to ignore inputs of this size (circular) or larger.
- L276 _public function_ `FInputDeviceAnalogStickDeadZoneProperty() : FInputDeviceAnalogStickProperty(PropertyName())`
- L280 _public function_ `FInputDeviceAnalogStickDeadZoneProperty(EInputDeviceAnalogStickMask InAffectedStick, float InDeadZone) : FInputDeviceAnalogStickProperty(PropertyName(), InAffectedStick) , DeadZone(InDeadZone)`
- L285 _public function_ `static FName PropertyName()`
- L287 _public member_ `float DeadZone = 0;`

#### struct `FInputDeviceTriggerDynamicReleaseDeadZoneProperty`  
`struct FInputDeviceTriggerDynamicReleaseDeadZoneProperty : public FInputDeviceTriggerProperty`  
_L296-312_
- inherits: `FInputDeviceTriggerProperty`
- desc: A generic input device property that sets "Dynamic Release DeadZones" for Analog Triggers. NOTE: Dynamic Triggers allow for Release and Press to be triggered even if the user fails to fully release the trigger before beginning another press. Smaller deadzones increase this effect. A deadzone of 1.0 isn't dynamic at all.
- L298 _public function_ `FInputDeviceTriggerDynamicReleaseDeadZoneProperty() : FInputDeviceTriggerProperty(PropertyName())`
- L302 _public function_ `FInputDeviceTriggerDynamicReleaseDeadZoneProperty(EInputDeviceTriggerMask InAffectedTriggers, float InDeadZone) : FInputDeviceTriggerProperty(PropertyName()) , DeadZone(InDeadZone)`
- L309 _public function_ `static FName PropertyName()`
- L311 _public member_ `float DeadZone = 1.0f;`

#### class `IInputInterface`  
`class IInputInterface`  
_L317-371_
- desc: Interface for the input interface.
- L322 _public prototype_ `virtual ~IInputInterface() = default;` — Virtual destructor.
- L332 _public prototype_ `virtual void SetForceFeedbackChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) = 0;` — Sets the strength/speed of the given channel for the given controller id. NOTE: If the channel is not supported, the call will silently fail @param ControllerId the id of the controller whose value is to be set @param ChannelType the type of channel whose value should be set @param Value strength or speed of feedback, 0.0f to 1.0f. 0.0f will disable
- L341 _public prototype_ `virtual void SetForceFeedbackChannelValues(int32 ControllerId, const FForceFeedbackValues &Values) = 0;` — Sets the strength/speed of all the channels for the given controller id. NOTE: Unsupported channels are silently ignored @param ControllerId the id of the controller whose value is to be set @param FForceFeedbackChannelValues strength or speed of feedback for all channels
- L351 _public function_ `virtual void SetHapticFeedbackValues(int32 ControllerId, int32 Hand, const FHapticFeedbackValues& Values)` — Sets the frequency and amplitude of haptic feedback channels for a given controller id. Some devices / platforms may support just haptics, or just force feedback. @param ControllerId	ID of the controller to issue haptic feedback for @param HandId			Which hand id (e.g. left or right) to issue the feedback for.  These usually correspond to EControllerHands @param Values			Frequency and amplitude to haptics at
- L360 _public function_ `virtual void SetDeviceProperty(int32 ControllerId, const FInputDeviceProperty* Property)` — Sets a property for a given controller id. Will be ignored for devices which don't support the property. @param ControllerId the id of the controller whose property is to be applied @param Property Base class pointer to property that will be applied
- L365 _public prototype_ `virtual void SetLightColor(int32 ControllerId, FColor Color) = 0;` — Sets the light color for the given controller.  Ignored if controller does not support a color.
- L370 _public prototype_ `virtual void ResetLightColor(int32 ControllerId) = 0;` — Resets the light color for the given controller.  Ignored if controller does not support a color.

#### Free symbols / members of external scopes

- L105 _prototype_ `ENUM_CLASS_FLAGS(EInputDeviceTriggerMask) #ifdef template<> UEnum* StaticEnum<EInputDeviceTriggerMask>();`
- L122 _prototype_ `ENUM_CLASS_FLAGS(EInputDeviceAnalogStickMask) #ifdef template<> UEnum* StaticEnum<EInputDeviceAnalogStickMask>();`

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/ITextInputMethodSystem.h` (Public)


#### class `ITextInputMethodContext`  
`class ITextInputMethodContext`  
_L14-139_
- desc: Editable texts should implement this class and maintain an object of this type after registering it. Methods of this class are called by the system to query contextual information about the state of the editable text. This information is used by the text input method system to provide appropriate processed input. Methods of this class are also called by the system to provide processed text input.
- L24 _public prototype_ `virtual ~ITextInputMethodContext() = default;`
- L32 _public prototype_ `virtual bool IsComposing() = 0;` — Returns whether or not this context is currently composing. @note This should be set to true when BeginComposition is called, and false when EndComposition is called. @return	True if we are composing, false otherwise.
- L39 _public prototype_ `virtual bool IsReadOnly() = 0;` — Returns whether or not this text is read-only. @return	True if the text is read-only, false otherwise.
- L46 _public prototype_ `virtual uint32 GetTextLength() = 0;` — Returns the number of code points in the text. @return	The number of code points in the text.
- L55 _public prototype_ `virtual void GetSelectionRange(uint32& OutBeginIndex, uint32& OutLength, ECaretPosition& OutCaretPosition) = 0;` — Gets the range of code point indices that are selected and which end of the selection the caret is at. @param	OutBeginIndex		The code point index at the beginning of the selection range. @param	OutLength			The number of code points selected after the beginning index. @param	OutCaretPosition	A flag indicating whether the caret is at the beginning or ending of the range. Irrelevant if the Length is zero.
- L64 _public prototype_ `virtual void SetSelectionRange(const uint32 InBeginIndex, const uint32 InLength, const ECaretPosition InCaretPosition) = 0;` — Sets the range of code point indices that are selected and which end of the selection the caret is at. @param	InBeginIndex	The code point index at the beginning of the selection range. @param	InLength		The number of code points selected after the beginning index. @param	InCaretPosition	A flag indicating whether the caret is at the beginning or ending of the range. Irrelevant if the Length is zero.
- L73 _public prototype_ `virtual void GetTextInRange(const uint32 InBeginIndex, const uint32 InLength, FString& OutString) = 0;` — Gets the code points in a range of indices. @param	InBeginIndex	The code point index at the beginning of the range to get. @param	InLength		The number of code points to get after the beginning index. @param	OutString		A string to store the code points being returned.
- L82 _public prototype_ `virtual void SetTextInRange(const uint32 InBeginIndex, const uint32 InLength, const FString& InString) = 0;` — Sets the code points in a range of indices. @param	InBeginIndex	The code point index at the beginning of the range to set. @param	InLength		The number of code points to set after the beginning index. @param	InString		A string of the code points to be set.
- L91 _public prototype_ `virtual int32 GetCharacterIndexFromPoint(const FVector2D& InPoint) = 0;` — Gets the index of the code point at the point on the screen. @param	InPoint	The 2D point on the screen to test for a code point. @return	The index of the code point at the point on the screen. INDEX_NONE if none was found.
- L103 _public prototype_ `virtual bool GetTextBounds(const uint32 InBeginIndex, const uint32 InLength, FVector2D& OutPosition, FVector2D& OutSize) = 0;` — Measures the screen-space bounds of the text in the specified range of code points. @param	InBeginIndex	The code point index at the beginning of the range to measure. @param	InLength		The number of code points to measure after the beginning index. @param	OutPosition		The screen-space position of the top-left bound of the specified range of code points. @param	OutSize			The screen-space size of the of the specified range of code points. @return	True if the specified range of code points is drawn clipped. False otherwise.
- L111 _public prototype_ `virtual void GetScreenBounds(FVector2D& OutPosition, FVector2D& OutSize) = 0;` — Measures the screen-space bounds of the display area available for text. @param	OutPosition		The screen-space position of the top-left bound of the display area. @param	OutSize			The screen-space size of the of the display area.
- L118 _public prototype_ `virtual TSharedPtr<FGenericWindow> GetWindow() = 0;` — Returns the window in which the text is displayed. @return	The window in which the text is displayed.
- L123 _public prototype_ `virtual void BeginComposition() = 0;` — Begins composition.
- L133 _public prototype_ `virtual void UpdateCompositionRange(const int32 InBeginIndex, const uint32 InLength) = 0;` — Updates the range of code point indices being composed. These code points should be displayed in some manner to communicate they are being composed. IE: Highlighted and underlined. @param	InBeginIndex	The code point index at the beginning of the range being composed. @param	InLength		The number of code points to measure after the beginning index.
- L138 _public prototype_ `virtual void EndComposition() = 0;` — Ends composition. May or may not mean the composition was committed.

#### enum `ITextInputMethodContext::ECaretPosition`  
`enum class ECaretPosition`  
_L17-21_
- L19 _public enumerator_ `Beginning`
- L20 _public enumerator_ `Ending`

#### class `ITextInputMethodChangeNotifier`  
`class ITextInputMethodChangeNotifier`  
_L146-163_
- desc: Platform owners implement this class to react to changes in the view/model of editable text widgets. Methods of this class should be called by the user to notify the system of changes not caused by system calls to methods of a ITextInputMethodContext implementation.
- L157 _public prototype_ `virtual ~ITextInputMethodChangeNotifier() = default;`
- L159 _public prototype_ `virtual void NotifyLayoutChanged(const ELayoutChangeType ChangeType) = 0;`
- L160 _public prototype_ `virtual void NotifySelectionChanged() = 0;`
- L161 _public prototype_ `virtual void NotifyTextChanged(const uint32 BeginIndex, const uint32 OldLength, const uint32 NewLength) = 0;`
- L162 _public prototype_ `virtual void CancelComposition() = 0;`

#### enum `ITextInputMethodChangeNotifier::ELayoutChangeType`  
`enum class ELayoutChangeType`  
_L149-154_
- L151 _public enumerator_ `Created`
- L152 _public enumerator_ `Changed`
- L153 _public enumerator_ `Destroyed`

#### class `ITextInputMethodSystem`  
`class ITextInputMethodSystem`  
_L168-219_
- desc: Platform owners implement this class to interface with the platform's input method system.
- L171 _public prototype_ `virtual ~ITextInputMethodSystem() = default;`
- L176 _public prototype_ `virtual void ApplyDefaults(const TSharedRef<FGenericWindow>& InWindow) = 0;` — Called when a window is first created to allow the text input system to apply any default settings
- L187 _public prototype_ `virtual TSharedPtr<ITextInputMethodChangeNotifier> RegisterContext(const TSharedRef<ITextInputMethodContext>& Context) = 0;` — Registers an implemented context interface object with the system to receive callbacks and provides an implemented notifier interface object. Editable text should call this method after constructing an implemented context interface object. @param	Context	The implemented context interface object to be registered. @return	An implemented notifier interface object
- L195 _public prototype_ `virtual void UnregisterContext(const TSharedRef<ITextInputMethodContext>& Context) = 0;` — Unregisters an implemented context interface object with the system. Editable text should call this method before destroying an implemented context interface object. @param	Context	The implemented context interface object to be unregistered.
- L202 _public prototype_ `virtual void ActivateContext(const TSharedRef<ITextInputMethodContext>& Context) = 0;` — Activates the provided context. Editable text should call this method when keyboard focus is received. @param	Context	The context to be activated.
- L209 _public prototype_ `virtual void DeactivateContext(const TSharedRef<ITextInputMethodContext>& Context) = 0;` — Deactivates the provided context. Editable text should call this method when keyboard focus is lost. @param	Context	The context to be activated.
- L218 _public prototype_ `virtual bool IsActiveContext(const TSharedRef<ITextInputMethodContext>& Context) const = 0;` — Test to see whether the provided context is the currently active context @param	Context	The context to be checked. @return	True if the context is active, false otherwise

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/InputDeviceMappingPolicy.h` (Public)


#### enum `EInputDeviceMappingPolicy`  
`enum class EInputDeviceMappingPolicy : int32`  
_L16-91_
- desc: The input device mapping policy controls how Human Interface Devices (HID's) are "mapped" or "assigned" to local players in your game. Depending on this policy, the creation of FPlatformUserId's and FInputDeviceId's can change. This policy is only in affect on platforms which do NOT have a managed user login or some kind of dedicated input mapping OS functionality (consoles).
- L21 _public enumerator_ `Invalid = -1` — Invalid mapping policy. Used to validate that the one in the settings is correct.
- L30 _public enumerator_ `UseManagedPlatformLogin = 0` — Use the current build target's built in platform login functionality. This is often times a prompt which is displayed by the target system to assign an input device to a specific player. Note: The behavior of this setting on non-user managed platforms (such as PC targets) is undefined.
- L51 _public enumerator_ `PrimaryUserSharesKeyboardAndFirstGamepad = 1` — Maps the keyboard/mouse and the first connected controller to the primary platform user. Any subsequently connected gamepads will be mapped to the next platform user without a valid input device already assigned to them. An example of this policy when you have 3 gamepads and a keyboard/mouse connected would be: -- Platform User 0 (Primary) ---> Keyboard and mouse ---> Gamepad 0 | -- Platform User 1 ---> Gamepad 1 | -- PlatformUser 2 ---> Gamepad 2 This is the default device mapping policy for PC.
- L76 _public enumerator_ `CreateUniquePlatformUserForEachDevice = 2` — If this policy is set, then every input device that is connected will be mapped to a unique platform user, meaning that each device is treated as a separate local player. This is what you want if you want plugging in a new controller to mean that you have a new local player in your game. This only defines the default behavior upon connection of a new device, you can still remap these input devices to new platform users later in the application lifecycle. An example of this policy when you have 3 gamepads and a keyboard/mouse connected would be: -- Platform User 0 (Primary) ---> Keyboard and mouse | -- Platform User 1 ---> Gamepad 0 | -- PlatformUser 2 ---> Gamepad 1 | -- PlatformUser 3 ---> Gamepad 2
- L90 _public enumerator_ `MapAllDevicesToPrimaryUser = 3` — If this policy is set, then every connected input device will be mapped to the primary platform user and new platform user Id's will not be created from input devices. An example of this policy when you have 3 gamepads and a keyboard/mouse connected would be: -- Platform User 0 (Primary) ---> Keyboard and mouse ---> Gamepad 0 ---> Gamepad 1 ---> Gamepad 2

#### Free symbols / members of external scopes

- L94 _prototype_ `template<> UEnum* StaticEnum<EInputDeviceMappingPolicy>();`

### `Source/Runtime/ApplicationCore/Public/GenericPlatform/InputDeviceRegistry.h` (Public)


#### struct `FInputDeviceDescriptor`  
`struct FInputDeviceDescriptor final`  
_L20-57_
- desc: Stable per-device descriptor stored in FInputDeviceRegistry. Mirrors the data held by FInputDeviceScope but is keyed on FInputDeviceId and lives for the lifetime of the device rather than just the dispatch call.
- L23 _public member_ `FInputDeviceId HardwareDeviceHandle = INPUTDEVICEID_NONE;` — The engine-assigned device ID. INPUTDEVICEID_NONE if unknown.
- L32 _public member_ `FName InputDeviceName = NAME_None;` — Logical name of the input device interface or module which created this descriptor. This is often times the name of the C++ class which is being used to create this event, like "XInputInterface". It is a generic grouping for input devices.
- L41 _public member_ `FName HardwareDeviceIdentifier = NAME_None;` — Logical identifier for the hardware device. Platform-specific, not translated. Stored as FName (replaces the FString used in FInputDeviceScope) This is a more specific name that represents a specific human interface device such as "<PlatformName>_Controller".
- L44 _public prototype_ `FString ToString() const;` — Returns a human-readable string representation of this descriptor, suitable for logging.
- L46 _public function_ `bool operator==(const FInputDeviceDescriptor& Other) const`
- L53 _public function_ `bool operator!=(const FInputDeviceDescriptor& Other) const`

#### class `FInputDeviceRegistry`  
`class FInputDeviceRegistry final`  
_L75-165_
- desc: Thread-safe singleton registry mapping FInputDeviceId to FInputDeviceDescriptor. This is the intended replacement for FInputDeviceScope::GetCurrent() and is safe to call from multiple threads.
- L80 _private prototype_ `static FInputDeviceRegistry& Get();` — Returns the process-wide singleton instance.
- L90 _public prototype_ `static bool RegisterDevice(const FInputDeviceDescriptor& Descriptor);` — Register or update the descriptor for a device. Called by FInputDeviceScope's constructor and may be called directly at device-connect time once all call sites have migrated away from FInputDeviceScope. @return True if the descriptor was registered successfully, false if the descriptor's HardwareDeviceHandle is not valid (INPUTDEVICEID_NONE).
- L100 _public prototype_ `static void RemoveDevice(const FInputDeviceId DeviceId);` — Explicitly remove the descriptor for a device from the registry. The registry is intentionally persistent across connect/disconnect cycles so that hardware metadata remains queryable for disconnected devices. Only call this when the device ID itself is being permanently retired (e.g., device ID recycled by the mapper, or engine shutdown cleanup). No-op if the device was never registered. Safe to call from any thread.
- L110 _public prototype_ `static TOptional<FInputDeviceDescriptor> FindDescriptor(const FInputDeviceId DeviceId);` — Look up the descriptor for a device by its FInputDeviceId. Returns an empty optional if the device has not been registered yet. If a simulated descriptor has been set for this device (see SetSimulatedDescriptor), that takes priority over the real descriptor. Safe to call from any thread.
- L124 _public prototype_ `static void SetSimulatedDescriptor(const FInputDeviceId DeviceId, const FInputDeviceDescriptor& SimulatedDescriptor);` — Override the descriptor returned by FindDescriptor for a specific device ID with a simulated one. Intended for tooling and non-shipping testing (e.g. input preview, device simulation) that needs to pretend a particular device is connected without affecting the real runtime registry. The simulated descriptor is stored separately from the real registry and is never written to by the platform layer. Call ClearSimulatedDescriptor to remove it. Not available in Shipping builds.
- L132 _public prototype_ `static void ClearSimulatedDescriptor(const FInputDeviceId DeviceId);` — Remove the simulated descriptor for a device, restoring FindDescriptor to return the real registered descriptor (if any). Not available in Shipping builds.
- L139 _public prototype_ `static void ClearAllSimulatedDescriptors();` — Remove all simulated descriptors at once (e.g. on PIE end or tool teardown). Not available in Shipping builds.
- L147 _public prototype_ `static void LogRegistryContents();` — Log the current contents of the registry to LogInputDeviceRegistry. In non-shipping builds this also includes any simulated descriptors. Safe to call from any thread.
- L154 _public prototype_ `static FOnInputDeviceDescriptorChanged& OnInputDeviceDescriptorChanged();` — Returns the singleton's "descriptor changed" multicast delegate. See FOnInputDeviceDescriptorChanged above for broadcast semantics — fires only when a registration ACTUALLY changes the stored descriptor (first registration counts as a change).
- L157 _private member_ `mutable FRWLock Lock;`
- L158 _private member_ `TMap<FInputDeviceId, FInputDeviceDescriptor> Descriptors;`
- L159 _private member_ `FOnInputDeviceDescriptorChanged DescriptorChangedDelegate;`
- L163 _private member_ `TMap<FInputDeviceId, FInputDeviceDescriptor> SimulatedDescriptors;` — Descriptors set via SetSimulatedDescriptor. Checked first by FindDescriptor.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API APPLICATIONCORE_API`
- L67 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputDeviceDescriptorChanged, const FInputDeviceDescriptor& );` — Broadcast when RegisterDevice() stores a descriptor that DIFFERS from the previously-registered descriptor for the same FInputDeviceId. Threading: broadcast runs on whichever thread called RegisterDevice and AFTER the registry's write lock is released, so handlers may safely call back into FInputDeviceRegistry. Game-thread work must be marshalled by the subscriber.
- L67 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputDeviceDescriptorChanged, const FInputDeviceDescriptor& );` — Broadcast when RegisterDevice() stores a descriptor that DIFFERS from the previously-registered descriptor for the same FInputDeviceId. Threading: broadcast runs on whichever thread called RegisterDevice and AFTER the registry's write lock is released, so handlers may safely call back into FInputDeviceRegistry. Game-thread work must be marshalled by the subscriber.

### `Source/Runtime/ApplicationCore/Public/HAL/PlatformApplicationMisc.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/ApplicationCore/Public/HAL/PlatformFramePacer.h` (Public)


#### Free symbols / members of external scopes

- L14 _typedef_ `typedef FGenericPlatformRHIFramePacer FPlatformRHIFramePacer;`

### `Source/Runtime/ApplicationCore/Public/HAL/PlatformSplash.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/ApplicationCore/Public/HAL/PlatformSurvey.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/ApplicationCore/Public/IOS/Accessibility/IOSAccessibilityCache.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/ApplicationCore/Public/IOS/Accessibility/IOSAccessibilityElement.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/ApplicationCore/Public/IOS/IOSAppDelegate.h` (Public)


#### enum `EAudioFeature`  
`enum class EAudioFeature : uint8`  
_L34-52_
- L36 _public enumerator_ `Playback` — Audio Not affected by the ringer switch
- L37 _public enumerator_ `Record` — Recording only, unless Playback or VoiceChat is also set
- L39 _public enumerator_ `DoNotMixWithOthers` — Do not mix audio with other applications
- L41 _public enumerator_ `VoiceChat` — set AVAudioSessionModeVoiceChat when both Playback and Record are enabled
- L42 _public enumerator_ `UseReceiver` — use receiver instead of speaker when both Playback and Record are enabled. Headsets will still be preferred if they are present
- L43 _public enumerator_ `DisableBluetoothSpeaker` — disable the use of Bluetooth A2DP speakers when both Playback and Record are enabled
- L45 _public enumerator_ `BluetoothMicrophone` — enable the use of Bluetooth HFP headsets when Record is enabled
- L47 _public enumerator_ `BackgroundAudio` — continue to play audio in the background. Requires an appropriate background mode to be set in Info.plist
- L49 _public enumerator_ `AllowHapticsAndSystemSoundsDuringRecording` — allow haptic feedback and system sounds when Record or PlayAndRecord category is active
- L51 _public enumerator_ `NumFeatures`

#### class `FIOSCoreDelegates`  
`class FIOSCoreDelegates`  
_L60-92_
- L64 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnOpenURL, UIApplication*, NSURL*, NSString*, id);` — Broadcast when this application is opened from an external source.
- L65 _public member_ `static FOnOpenURL OnOpenURL;`
- L68 _public prototype_ `static FDelegateHandle AddPushNotificationFilter(const FPushNotificationFilter& FilterDel);` — Add a filter to decide whether each push notification should be processed
- L71 _public prototype_ `static void RemovePushNotificationFilter(FDelegateHandle Handle);` — Remove a previously processed push notification filter
- L74 _public prototype_ `static bool PassesPushNotificationFilters(NSDictionary* Payload);` — INTERNAL - check if a push notification payload passes all registered filters
- L77 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnWillResignActive);` — INTERNAL - called when entering the background - this is not thread-safe with the game thread or render thread as it is called from the app's Main thread
- L78 _public member_ `static FOnWillResignActive OnWillResignActive;`
- L81 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnDidBecomeActive);` — INTERNAL - called when becoming active - this is not thread-safe with the game thread or render thread as it is called from the app's Main thread
- L82 _public member_ `static FOnWillResignActive OnDidBecomeActive;`
- L91 _private member_ `static TArray<FFilterDelegateAndHandle> PushNotificationFilters;`

#### struct `FIOSCoreDelegates::FFilterDelegateAndHandle`  
`struct FFilterDelegateAndHandle`  
_L85-89_
- L87 _public member_ `FPushNotificationFilter Filter;`
- L88 _public member_ `FDelegateHandle Handle;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define USE_MUTE_SWITCH_DETECTION 0`
- L27 _externvar_ `extern bool GIOSDelayRotationUntilPresent;`
- L31 _macro_ `#define WITH_IOS_UNIVERSAL_LINKS 0`
- L54 _prototype_ `void LexFromString(EAudioFeature& OutFeature, const TCHAR* String);`
- L55 _prototype_ `FString LexToString(EAudioFeature Feature);`
- L58 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FPushNotificationFilter, NSDictionary*);` — Predicate to decide whether a push notification message should be processed
- L58 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FPushNotificationFilter, NSDictionary*);` — Predicate to decide whether a push notification message should be processed
- L64 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnOpenURL, UIApplication*, NSURL*, NSString*, id);` — Broadcast when this application is opened from an external source.
- L77 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnWillResignActive);` — INTERNAL - called when entering the background - this is not thread-safe with the game thread or render thread as it is called from the app's Main thread
- L81 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnDidBecomeActive);` — INTERNAL - called when becoming active - this is not thread-safe with the game thread or render thread as it is called from the app's Main thread
- L94 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogIOSAudioSession, Log, All);`
- L94 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIOSAudioSession, Log, All);`
- L98 _namespace_ `namespace FAppEntry`
- L100 _prototype_ `void PlatformInit();` (scope `FAppEntry`)
- L101 _prototype_ `void PreInit(IOSAppDelegate* AppDelegate, UIApplication* Application);` (scope `FAppEntry`)
- L102 _prototype_ `void Init();` (scope `FAppEntry`)
- L103 _prototype_ `void Tick();` (scope `FAppEntry`)
- L104 _prototype_ `void SuspendTick();` (scope `FAppEntry`)
- L105 _prototype_ `void ResumeAudioContext();` (scope `FAppEntry`)
- L106 _prototype_ `void ResetAudioContextResumeTime();` (scope `FAppEntry`)
- L107 _prototype_ `void Shutdown();` (scope `FAppEntry`)
- L108 _prototype_ `void Suspend(bool bIsInterrupt = false);` (scope `FAppEntry`)
- L109 _prototype_ `void Resume(bool bIsInterrupt = false);` (scope `FAppEntry`)
- L110 _prototype_ `void RestartAudio();` (scope `FAppEntry`)
- L111 _prototype_ `void IncrementAudioSuspendCounters();` (scope `FAppEntry`)
- L112 _prototype_ `void DecrementAudioSuspendCounters();` (scope `FAppEntry`)
- L114 _prototype_ `bool IsStartupMoviePlaying();` (scope `FAppEntry`)
- L116 _externvar_ `extern bool gAppLaunchedWithLocalNotification;` (scope `FAppEntry`)
- L117 _externvar_ `extern FString gLaunchLocalNotificationActivationEvent;` (scope `FAppEntry`)
- L118 _externvar_ `extern int32 gLaunchLocalNotificationFireDate;` (scope `FAppEntry`)
- L140 _variable_ `bool bForceExit;`
- L156 _variable_ `@property class FIOSApplication* IOSApplication;`
- L328 _prototype_ `static void interruptionListener(void* ClientData, UInt32 Interruption);`

### `Source/Runtime/ApplicationCore/Public/IOS/IOSApplication.h` (Public)


#### class `FIOSApplication`  
`class FIOSApplication : public GenericApplication`  
_L23-108_
- inherits: `GenericApplication`
- L27 _public prototype_ `static FIOSApplication* CreateIOSApplication();`
- L32 _public prototype_ `virtual ~FIOSApplication();`
- L34 _public prototype_ `void HandlePhysicalKeyboardConnectionChanged();`
- L36 _public prototype_ `void HandlePhysicalMouseConnectionChanged();`
- L38 _public prototype_ `void HandleMouseMovement(FIntVector2 MovementDelta);`
- L40 _public prototype_ `virtual FModifierKeysState GetModifierKeys() const override;`
- L42 _public prototype_ `virtual bool IsMouseAttached() const override;`
- L44 _public prototype_ `void SetMessageHandler( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler );`
- L46 _public prototype_ `virtual void SetAccessibleMessageHandler(const TSharedRef<FGenericAccessibleMessageHandler>& InAccessibleMessageHandler) override;`
- L49 _public prototype_ `virtual void PollGameDeviceState( const float TimeDelta ) override;`
- L51 _public prototype_ `virtual FPlatformRect GetWorkArea( const FPlatformRect& CurrentWindow ) const override;`
- L53 _public prototype_ `virtual TSharedRef< FGenericWindow > MakeWindow() override;`
- L55 _public prototype_ `virtual void AddExternalInputDevice(TSharedPtr<class IInputDevice> InputDevice);`
- L59 _public prototype_ `static void OrientationChanged(UIInterfaceOrientation NewOrientation);`
- L60 _public prototype_ `static void UpdateSafeZoneAfterRotation();`
- L62 _public member_ `static UIInterfaceOrientation CachedOrientation;`
- L65 _public function_ `virtual IInputInterface* GetInputInterface() override`
- L66 _public function_ `FIOSInputInterface* GetIOSInputInterface()`
- L68 _public prototype_ `virtual bool IsGamepadAttached() const override;`
- L70 _public prototype_ `TSharedRef<FIOSWindow> FindWindowByAppDelegateView();`
- L73 _protected prototype_ `virtual void InitializeWindow( const TSharedRef< FGenericWindow >& Window, const TSharedRef< FGenericWindowDefinition >& InDefinition, const TSharedPtr< FGenericWindow >& InParent, const bool bShowImmediately ) override;`
- L76 _private prototype_ `FIOSApplication();`
- L78 _private prototype_ `void OnAccessibleEventRaised(const FAccessibleEventArgs& Args);`
- L81 _private prototype_ `void OnInputDeviceModuleRegistered(const FName& Type, IModularFeature* ModularFeature);`
- L85 _private member_ `TSharedPtr< FIOSInputInterface > InputInterface;`
- L88 _private member_ `TArray< TSharedPtr<class IInputDevice> > ExternalInputDevices;` — List of input devices implemented in external modules.
- L89 _private member_ `bool bHasLoadedInputPlugins;`
- L91 _private member_ `TArray< TSharedRef< FIOSWindow > > Windows;`
- L97 _private member_ `NSTimer* AccessibilityAnnouncementDelayTimer;` — A timer used to introduce a small delay before accessibility announcement requests to Avoid our requested accessibility announcement from being stompd by system accessibility requests.
- L100 _private member_ `static FCriticalSection CriticalSection;`
- L101 _private member_ `static bool bOrientationChanged;`
- L103 _private member_ `std::atomic<bool> bIsMouseAttached = false;`
- L106 _private prototype_ `void CacheDisplayMetrics(UIInterfaceOrientation Orientation);`

#### Free symbols / members of external scopes

- L16 _macro_ `#define IOS_ROTATION_DEBUG_LOGGING 0`

### `Source/Runtime/ApplicationCore/Public/IOS/IOSBackgroundURLSessionHandler.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/ApplicationCore/Public/IOS/IOSConfigRules.h` (Public)


#### class `FIOSConfigRules`  
`class FIOSConfigRules : public FGenericConfigRules`  
_L28-48_
- inherits: `FGenericConfigRules`
- L36 _private member_ `static inline TArray<FConfigRuleParams> ConfigRulesParams;`
- L38 _private prototype_ `static void InitRules();`
- L39 _private member_ `static inline TMap<FString, FString> ConfigRuleVariablesMap;`
- L46 _public prototype_ `static bool Init(TMap<FString, FString>&& PredefinedVariables);` — Initialize the config rules, PredefinedVariables contains a set of K/V pairs that are used while processing the rules. They are included in the map returned by GetConfigRulesMap. returns true if a config rule file was processed.
- L47 _public function_ `static const TMap<FString, FString>& GetConfigRulesMap()`

#### struct `FIOSConfigRules::FConfigRuleParams`  
`struct FConfigRuleParams`  
_L30-35_
- L32 _public member_ `FString Path;`
- L33 _public member_ `FString Key;`
- L34 _public member_ `FString IV;`

### `Source/Runtime/ApplicationCore/Public/IOS/IOSCursor.h` (Public)


#### class `FIOSCursor`  
`class FIOSCursor : public FGenericPlatformSoftwareCursor`  
_L9-16_
- inherits: `FGenericPlatformSoftwareCursor`
- L13 _public prototype_ `FIOSCursor();`
- L15 _public prototype_ `virtual ~FIOSCursor();`

### `Source/Runtime/ApplicationCore/Public/IOS/IOSDebugOutputDevice.h` (Public)


#### class `FIOSDebugOutputDevice`  
`class FIOSDebugOutputDevice : public FOutputDevice`  
_L10-23_
- inherits: `FOutputDevice`
- desc: Generic Output device that writes to Windows Event Log
- L14 _public prototype_ `FIOSDebugOutputDevice();` — Constructor, initializing member variables
- L22 _public prototype_ `virtual void Serialize( const TCHAR* Msg, ELogVerbosity::Type Verbosity, const class FName& Category ) override;` — Serializes the passed in data unless the current event is suppressed. @param	Data	Text to log @param	Event	Event name used for suppression purposes

### `Source/Runtime/ApplicationCore/Public/IOS/IOSFeedbackContext.h` (Public)


#### class `FIOSFeedbackContext`  
`class FIOSFeedbackContext : public FFeedbackContext`  
_L9-11_
- inherits: `FFeedbackContext`

### `Source/Runtime/ApplicationCore/Public/IOS/IOSInputDefinitions.h` (Public)


#### enum `IOS::EUnrealKeyCode`  
`enum class EUnrealKeyCode : uint32`  
_L11-81_
- desc: Unreal engine key codes used for key mapping in IOS Platforms. Apple has GCKeyCodes and UIKit USB Hid codes. We use these to map to a single key code in the UE side
- L13 _public enumerator_ `Unknown = 0`
- L15 _public enumerator_ `Enter = 1000`
- L16 _public enumerator_ `Backspace`
- L17 _public enumerator_ `Escape`
- L18 _public enumerator_ `Tab`
- L19 _public enumerator_ `Left`
- L20 _public enumerator_ `Right`
- L21 _public enumerator_ `Down`
- L22 _public enumerator_ `Up`
- L23 _public enumerator_ `LeftControl`
- L24 _public enumerator_ `LeftShift`
- L25 _public enumerator_ `LeftAlt`
- L26 _public enumerator_ `LeftCommand`
- L27 _public enumerator_ `CapsLock`
- L28 _public enumerator_ `RightControl`
- L29 _public enumerator_ `RightShift`
- L30 _public enumerator_ `RightAlt`
- L31 _public enumerator_ `RightCommand`
- L32 _public enumerator_ `F1`
- L33 _public enumerator_ `F2`
- L34 _public enumerator_ `F3`
- L35 _public enumerator_ `F4`
- L36 _public enumerator_ `F5`
- L37 _public enumerator_ `F6`
- L38 _public enumerator_ `F7`
- L39 _public enumerator_ `F8`
- L40 _public enumerator_ `F9`
- L41 _public enumerator_ `F10`
- L42 _public enumerator_ `F11`
- L43 _public enumerator_ `F12`
- L44 _public enumerator_ `F13`
- L45 _public enumerator_ `F14`
- L46 _public enumerator_ `F15`
- L47 _public enumerator_ `F16`
- L48 _public enumerator_ `F17`
- L49 _public enumerator_ `F18`
- L50 _public enumerator_ `F19`
- L51 _public enumerator_ `F20`
- L53 _public enumerator_ `PageUp`
- L54 _public enumerator_ `PageDown`
- L55 _public enumerator_ `Home`
- L56 _public enumerator_ `End`
- L57 _public enumerator_ `Insert`
- L59 _public enumerator_ `Multiply`
- L60 _public enumerator_ `Add`
- L61 _public enumerator_ `Subtract`
- L62 _public enumerator_ `Divide`
- L64 _public enumerator_ `ScrollLock`
- L65 _public enumerator_ `Pause`
- L67 _public enumerator_ `NumLock`
- L68 _public enumerator_ `NumPad0`
- L69 _public enumerator_ `NumPad1`
- L70 _public enumerator_ `NumPad2`
- L71 _public enumerator_ `NumPad3`
- L72 _public enumerator_ `NumPad4`
- L73 _public enumerator_ `NumPad5`
- L74 _public enumerator_ `NumPad6`
- L75 _public enumerator_ `NumPad7`
- L76 _public enumerator_ `NumPad8`
- L77 _public enumerator_ `NumPad9`
- L78 _public enumerator_ `Delete`
- L79 _public enumerator_ `Decimal`
- L80 _public enumerator_ `SpaceBar`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace IOS`

### `Source/Runtime/ApplicationCore/Public/IOS/IOSInputInterface.h` (Public)


#### enum `TouchType`  
`enum TouchType`  
_L59-66_
- L61 _public enumerator_ `TouchBegan`
- L62 _public enumerator_ `TouchMoved`
- L63 _public enumerator_ `TouchEnded`
- L64 _public enumerator_ `ForceChanged`
- L65 _public enumerator_ `FirstMove`

#### struct `TouchInput`  
`struct TouchInput`  
_L68-75_
- L70 _public member_ `int Handle;`
- L71 _public member_ `TouchType Type;`
- L72 _public member_ `FVector2D LastPosition;`
- L73 _public member_ `FVector2D Position;`
- L74 _public member_ `float Force;`

#### struct `GestureInput`  
`struct GestureInput`  
_L77-83_
- L79 _public member_ `EGestureEvent Type;`
- L80 _public member_ `FVector2D Delta;` — gesture delta (pan offset, swipe direction)
- L81 _public member_ `bool bIsStart;` — UIGestureRecognizerStateBegan
- L82 _public member_ `bool bIsEnd;` — UIGestureRecognizerStateEnded/Cancelled

#### enum `EIOSEventType`  
`enum class EIOSEventType : int32`  
_L85-98_
- L87 _public enumerator_ `Invalid = 0`
- L88 _public enumerator_ `LeftMouseDown = 1`
- L89 _public enumerator_ `LeftMouseUp = 2`
- L90 _public enumerator_ `RightMouseDown = 3`
- L91 _public enumerator_ `RightMouseUp = 4`
- L92 _public enumerator_ `KeyDown = 10`
- L93 _public enumerator_ `KeyUp = 11`
- L94 _public enumerator_ `MiddleMouseDown = 25`
- L95 _public enumerator_ `MiddleMouseUp = 26`
- L96 _public enumerator_ `ThumbDown = 50`
- L97 _public enumerator_ `ThumbUp = 70`

#### struct `FDeferredIOSEvent`  
`struct FDeferredIOSEvent`  
_L100-105_
- L102 _public member_ `EIOSEventType type;`
- L103 _public member_ `uint32 keycode;`
- L104 _public member_ `uint32 charcode;`

#### class `FIOSInputInterface`  
`class FIOSInputInterface : public FAppleControllerInterface, FSelfRegisteringExec`  
_L110-247_
- inherits: `FAppleControllerInterface,FSelfRegisteringExec`
- desc: Interface class for IOS input devices
- L114 _public prototype_ `static TSharedRef< FIOSInputInterface > Create( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler );`
- L115 _public prototype_ `void MapKeyboardModifierKeys();`
- L116 _public prototype_ `static TSharedPtr< FIOSInputInterface > Get();`
- L120 _public function_ `virtual ~FIOSInputInterface()`
- L125 _public prototype_ `void SendControllerEvents();` — Poll for controller state and send events if needed
- L127 _public prototype_ `virtual void SetMessageHandler( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler );`
- L132 _public prototype_ `virtual void SetForceFeedbackChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;` — IInputInterface implementation
- L133 _public prototype_ `virtual void SetForceFeedbackChannelValues(int32 ControllerId, const FForceFeedbackValues &values) override;`
- L135 _public prototype_ `static void QueueTouchInput(const TArray<TouchInput>& InTouchEvents);`
- L136 _public prototype_ `static void QueueGestureInput(const TArray<GestureInput>& InGestureInputs);`
- L138 _public function_ `void SetGamepadsAllowed(bool bAllowed)`
- L139 _public function_ `void SetGamepadsBlockDeviceFeedback(bool bBlock)`
- L141 _public prototype_ `void EnableMotionData(bool bEnable);`
- L142 _public prototype_ `bool IsMotionDataEnabled() const;`
- L145 _public function_ `static void SetKeyboardInhibited(bool bInhibited)` — `UE_DEPRECATED(5.8, "Please use SetKeyboardControllerInhibited")`
- L149 _public function_ `static bool IsKeyboardInhibited()` — `UE_DEPRECATED(5.8, "Please use IsKeyboardControllerInhibited")`
- L154 _public prototype_ `TWeakPtr<FAppleKeyboardController> GetKeyboardController();`
- L156 _public prototype_ `TWeakPtr<FAppleMouseController> GetMouseController();`
- L158 _public prototype_ `void SetKeyboardControllerInhibited(bool bInhibited);`
- L160 _public prototype_ `bool IsKeyboardControllerInhibited() const;`
- L162 _public prototype_ `bool IsAnyPhysicalKeyboardConnected() const;`
- L164 _public prototype_ `NSData* GetGamepadGlyphRawData(const FGamepadKeyNames::Type& ButtonKey, uint32 ControllerIndex);`
- L169 _protected prototype_ `virtual bool Exec_Runtime(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L174 _private prototype_ `FIOSInputInterface( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler );`
- L184 _private prototype_ `void GetMovementData(FVector& Attitude, FVector& RotationRate, FVector& Gravity, FVector& Acceleration);` — Get the current Movement data from the device @param Attitude The current Roll/Pitch/Yaw of the device @param RotationRate The current rate of change of the attitude @param Gravity A vector that describes the direction of gravity for the device @param Acceleration returns the current acceleration of the device
- L189 _private prototype_ `void CalibrateMotion(uint32 PlayerIndex);` — Calibrate the devices motion
- L192 _private prototype_ `void ProcessTouchesAndKeys(uint32 ControllerId, const TArray<TouchInput>& InTouchInputStack);`
- L194 _private prototype_ `void ProcessGestures(uint32 ControllerId, const TArray<GestureInput>& InGestureInputStack);`
- L197 _private member_ `bool bAllowRemoteRotation;` — can the remote be rotated to landscape
- L200 _private member_ `bool bGameSupportsMultipleActiveControllers;` — can the game handle multiple gamepads at the same time (siri remote is a gamepad) ?
- L203 _private member_ `bool bControllersBlockDeviceFeedback;` — bluetooth connected controllers will block force feedback.
- L206 _private member_ `bool bPauseMotion;` — Is motion paused or not?
- L210 _private member_ `CMMotionManager* MotionManager;` — Access to the ios devices motion
- L213 _private member_ `CMAttitude* ReferenceAttitude;` — Access to the ios devices tilt information
- L217 _private member_ `float LastRoll;` — Last frames roll, for calculating rate
- L220 _private member_ `float LastPitch;` — Last frames pitch, for calculating rate
- L223 _private member_ `bool bIsCalibrationRequested;` — True if a calibration is requested
- L226 _private member_ `float CenterRoll;` — The center roll value for tilt calibration
- L229 _private member_ `float CenterPitch;` — The center pitch value for tilt calibration
- L232 _private member_ `FVector FilteredAccelerometer;` — When using just acceleration (without full motion) we store a frame of accel data to filter by
- L235 _private member_ `float LastHapticValue;` — Last value sent to mobile haptics
- L238 _private member_ `float CumulativePinchScale = 1.0f;` — Cumulative pinch scale ratio for native gesture value conversion.
- L240 _private member_ `int HapticFeedbackSupportLevel;`
- L242 _private member_ `static FName InputClassName_DefaultMobileTouch;`
- L243 _private member_ `static FString HardwareDeviceIdentifier_DefaultMobileTouch;`
- L245 _private member_ `TSharedRef<FAppleKeyboardController> KeyboardController;`
- L246 _private member_ `TSharedRef<FAppleMouseController> MouseController;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define KEYCODE_ENTER UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1000`
- L22 _macro_ `#define KEYCODE_BACKSPACE UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1001`
- L23 _macro_ `#define KEYCODE_ESCAPE UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1002`
- L24 _macro_ `#define KEYCODE_TAB UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1003`
- L25 _macro_ `#define KEYCODE_LEFT UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1004`
- L26 _macro_ `#define KEYCODE_RIGHT UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1005`
- L27 _macro_ `#define KEYCODE_DOWN UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1006`
- L28 _macro_ `#define KEYCODE_UP UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1007`
- L29 _macro_ `#define KEYCODE_LEFT_CONTROL UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1008`
- L30 _macro_ `#define KEYCODE_LEFT_SHIFT UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1009`
- L31 _macro_ `#define KEYCODE_LEFT_ALT UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1010`
- L32 _macro_ `#define KEYCODE_LEFT_COMMAND UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1011`
- L33 _macro_ `#define KEYCODE_CAPS_LOCK UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1012`
- L34 _macro_ `#define KEYCODE_RIGHT_CONTROL UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1013`
- L35 _macro_ `#define KEYCODE_RIGHT_SHIFT UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1014`
- L36 _macro_ `#define KEYCODE_RIGHT_ALT UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1015`
- L37 _macro_ `#define KEYCODE_RIGHT_COMMAND UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1016`
- L38 _macro_ `#define KEYCODE_F1 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1017`
- L39 _macro_ `#define KEYCODE_F2 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1018`
- L40 _macro_ `#define KEYCODE_F3 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1019`
- L41 _macro_ `#define KEYCODE_F4 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1020`
- L42 _macro_ `#define KEYCODE_F5 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1021`
- L43 _macro_ `#define KEYCODE_F6 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1022`
- L44 _macro_ `#define KEYCODE_F7 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1023`
- L45 _macro_ `#define KEYCODE_F8 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1024`
- L46 _macro_ `#define KEYCODE_F9 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1025`
- L47 _macro_ `#define KEYCODE_F10 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1026`
- L48 _macro_ `#define KEYCODE_F11 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1027`
- L49 _macro_ `#define KEYCODE_F12 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1028`
- L50 _macro_ `#define KEYCODE_F13 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1029`
- L51 _macro_ `#define KEYCODE_F14 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1030`
- L52 _macro_ `#define KEYCODE_F15 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1031`
- L53 _macro_ `#define KEYCODE_F16 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1032`
- L54 _macro_ `#define KEYCODE_F17 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1033`
- L55 _macro_ `#define KEYCODE_F18 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1034`
- L56 _macro_ `#define KEYCODE_F19 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1035`
- L57 _macro_ `#define KEYCODE_F20 UE_DEPRECATED_MACRO(5.8, "IOS KEYCODE Define has been deprecated. Use enum IOS::EUnrealKeyCode") 1036`

### `Source/Runtime/ApplicationCore/Public/IOS/IOSInputUtils.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace IOS`
- L15 _prototype_ `EUnrealKeyCode TranslateUSBHIDToUnrealKeycode(UIKeyboardHIDUsage HIDKeycode);` (scope `IOS`) — Translate UI Kit USB Hid keycodes into Unreal Keycodes

### `Source/Runtime/ApplicationCore/Public/IOS/IOSPlatformApplicationMisc.h` (Public)


#### struct `FIOSPlatformApplicationMisc`  
`struct FIOSPlatformApplicationMisc : public FGenericPlatformApplicationMisc`  
_L10-43_
- inherits: `FGenericPlatformApplicationMisc`
- L12 _public prototype_ `static void LoadPreInitModules();`
- L14 _public prototype_ `static class FFeedbackContext* GetFeedbackContext();`
- L15 _public prototype_ `static class FOutputDeviceError* GetErrorOutputDevice();`
- L16 _public prototype_ `static class GenericApplication* CreateApplication();`
- L17 _public prototype_ `static bool IsScreensaverEnabled();`
- L18 _public prototype_ `static bool ControlScreensaver(EScreenSaverAction Action);`
- L20 _public prototype_ `static void SetGamepadsAllowed(bool bAllowed);`
- L21 _public prototype_ `static void SetGamepadsBlockDeviceFeedback(bool bBlock);`
- L22 _public prototype_ `static void ResetGamepadAssignments();`
- L23 _public prototype_ `static void ResetGamepadAssignmentToController(int32 ControllerId);`
- L24 _public prototype_ `static bool IsControllerAssignedToGamepad(int32 ControllerId);`
- L25 _public prototype_ `static class UTexture2D* GetGamepadButtonGlyph(const FGamepadKeyNames::Type& ButtonKey, uint32 ControllerIndex);`
- L27 _public prototype_ `static void EnableMotionData(bool bEnable);`
- L28 _public prototype_ `static bool IsMotionDataEnabled();`
- L30 _public prototype_ `static void ClipboardCopy(const TCHAR* Str);`
- L31 _public prototype_ `static void ClipboardPaste(class FString& Dest);`
- L33 _public prototype_ `static EScreenPhysicalAccuracy ComputePhysicalScreenDensity(int32& ScreenDensity);`
- L34 _public prototype_ `static EScreenPhysicalAccuracy ComputePhysicalScreenDimensions(FVector2f& OutScreenDimensions, float& OutScreenSize);`
- L36 _public prototype_ `static bool RequiresVirtualKeyboard();`
- L39 _private member_ `static class FIOSApplication* CachedApplication;`
- L42 _private member_ `static FGetGamePadGlyphDelegate GetGamePadGlyphDelegate;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(class UTexture2D*, FGetGamePadGlyphDelegate, const FGamepadKeyNames::Type&, uint32);`
- L8 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(class UTexture2D*, FGetGamePadGlyphDelegate, const FGamepadKeyNames::Type&, uint32);`
- L45 _typedef_ `typedef FIOSPlatformApplicationMisc FPlatformApplicationMisc;`

### `Source/Runtime/ApplicationCore/Public/IOS/IOSPlatformFramePacer.h` (Public)


#### struct `FIOSPlatformRHIFramePacer`  
`struct FIOSPlatformRHIFramePacer : public FGenericPlatformRHIFramePacer`  
_L20-52_
- inherits: `FGenericPlatformRHIFramePacer`
- desc: iOS implementation of FGenericPlatformRHIFramePacer
- L23 _public prototype_ `static bool IsEnabled();` — FGenericPlatformRHIFramePacer interface
- L24 _public prototype_ `static void Destroy();`
- L25 _public prototype_ `static int32 SetFramePace(int32 FramePace);`
- L26 _public prototype_ `static int32 GetFramePace();`
- L27 _public prototype_ `static bool SupportsFramePace(int32 QueryFramePace);`
- L30 _public prototype_ `static void InitWithEvent(class FEvent* TriggeredEvent);` — FIOSPlatformRHIFramePacer interface
- L31 _public prototype_ `static void AddHandler(FIOSFramePacerHandler Handler);`
- L32 _public prototype_ `static void RemoveHandler(FIOSFramePacerHandler Handler);`
- L33 _public prototype_ `static uint32 GetMaxRefreshRate();`
- L36 _public member_ `static FIOSFramePacer* FramePacer;` — Access to the IOS Frame Pacer: CADisplayLink
- L39 _public member_ `static uint32 FrameInterval;` — Number of frames before the CADisplayLink triggers it's readied callback
- L42 _public member_ `static uint32 MinFrameInterval;` — The minimum frame interval dictated by project settings on startup
- L45 _public member_ `static uint32 Pace;` — Frame rate we are pacing to
- L48 _public prototype_ `static void Suspend();` — Suspend the frame pacer so we can enter the background state
- L51 _public prototype_ `static void Resume();` — Resume the frame pacer so we can enter the foreground state

#### Free symbols / members of external scopes

- L15 _typedef_ `typedef void (^FIOSFramePacerHandler)(uint32 IgnoredId, double OutputSeconds, double OutputDuration);`
- L55 _typedef_ `typedef FIOSPlatformRHIFramePacer FPlatformRHIFramePacer;`
- L56 _typedef_ `typedef FIOSFramePacerHandler FPlatformRHIFramePacerHandler;`

### `Source/Runtime/ApplicationCore/Public/IOS/IOSPlatformSplash.h` (Public)


#### struct `FIOSPlatformSplash`  
`struct FIOSPlatformSplash : public FGenericPlatformSplash`  
_L13-16_
- inherits: `FGenericPlatformSplash`
- desc: IOS splash implementation

#### Free symbols / members of external scopes

- L18 _typedef_ `typedef FIOSPlatformSplash FPlatformSplash;`

### `Source/Runtime/ApplicationCore/Public/IOS/IOSPlatformSurvey.h` (Public)


#### struct `FIOSPlatformSurvey`  
`struct FIOSPlatformSurvey : public FGenericPlatformSurvey`  
_L14-17_
- inherits: `FGenericPlatformSurvey`
- desc: iOS implementation of FGenericPlatformSurvey
- L16 _public prototype_ `static bool GetSurveyResults(FHardwareSurveyResults& OutResults, bool bWait = false);`

#### Free symbols / members of external scopes

- L19 _typedef_ `typedef FIOSPlatformSurvey FPlatformSurvey;`

### `Source/Runtime/ApplicationCore/Public/IOS/IOSSceneDelegate.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/ApplicationCore/Public/IOS/IOSView.h` (Public)


#### struct `FKeyboardConfig`  
`struct FKeyboardConfig`  
_L22-34_
- L24 _public member_ `UIKeyboardType KeyboardType;`
- L25 _public member_ `UITextAutocorrectionType AutocorrectionType;`
- L26 _public member_ `UITextAutocapitalizationType AutocapitalizationType;`
- L27 _public member_ `BOOL bSecureTextEntry;`
- L29 _public function_ `inline FKeyboardConfig() : KeyboardType(UIKeyboardTypeDefault), AutocorrectionType(UITextAutocorrectionTypeNo), AutocapitalizationType(UITextAutocapitalizationTypeNone), bSecureTextEntry(NO)`

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace MTL`

### `Source/Runtime/ApplicationCore/Public/IOS/IOSWindow.h` (Public)


#### class `FIOSWindow`  
`class FIOSWindow : public FGenericWindow`  
_L13-58_
- inherits: `FGenericWindow`
- desc: A platform specific implementation of FNativeWindow. Native windows provide platform-specific backing for and are always owned by an SWindow.
- L16 _public prototype_ `~FIOSWindow();`
- L23 _public prototype_ `static TSharedRef<FIOSWindow> Make();` — Create a new FIOSWindow. @param OwnerWindow		The SlateWindow for which we are crating a backing IOSWindow @param InParent			Parent iOS window; usually NULL.
- L26 _public prototype_ `static FPlatformRect GetScreenRect();` — Returns a rect describing the main screen
- L29 _public function_ `virtual void* GetOSWindowHandle() const override` — Returns a void pointer to the hWnd (for other apis)
- L31 _public prototype_ `void Initialize( class FIOSApplication* const Application, const TSharedRef< FGenericWindowDefinition >& InDefinition, const TSharedPtr< FIOSWindow >& InParent, const bool bShowImmediately );`
- L34 _public prototype_ `virtual bool GetFullScreenInfo( int32& X, int32& Y, int32& Width, int32& Height ) const override;` — Returns the rectangle of the screen the window is associated with
- L37 _public prototype_ `static void OnScaleFactorChanged(IConsoleVariable* CVar);` — Callbacks for Cvar changes "r.MobileContentScaleFactor" and "r.Mobile.DesiredResX/Y" respectively
- L38 _public prototype_ `static void OnConsoleResolutionChanged(IConsoleVariable* CVar);`
- L42 _protected function_ `virtual EWindowMode::Type GetWindowMode() const override` — @return true if the native window is currently in fullscreen mode, false otherwise
- L48 _private prototype_ `FIOSWindow();` — Protect the constructor; only TSharedRefs of this class can be made.
- L50 _private member_ `FIOSApplication* OwningApplication;`
- L53 _private member_ `UIWindow *Window;` — iOS window handle, typically, only one should ever exist
- L56 _private member_ `int32 RegionX;` — Store the window region size for querying whether a point lies within the window
- L57 _private member_ `int32 RegionY;`

### `Source/Runtime/ApplicationCore/Public/Linux/LinuxApplication.h` (Public)


#### class `FLinuxApplication`  
`class FLinuxApplication : public GenericApplication, public FSelfRegisteringExec, public IInputInterface`  
_L24-384_
- inherits: `GenericApplication,FSelfRegisteringExec,IInputInterface`
- L39 _public prototype_ `static FLinuxApplication* CreateLinuxApplication();`
- L47 _public prototype_ `virtual ~FLinuxApplication();`
- L49 _public prototype_ `virtual void DestroyApplication() override;`
- L52 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — FSelfRegisteringExec
- L55 _public prototype_ `virtual void SetMessageHandler( const TSharedRef< class FGenericApplicationMessageHandler >& InMessageHandler ) override;`
- L57 _public prototype_ `virtual void PollGameDeviceState( const float TimeDelta ) override;`
- L59 _public prototype_ `virtual void PumpMessages( const float TimeDelta ) override;`
- L61 _public prototype_ `virtual void ProcessDeferredEvents( const float TimeDelta ) override;`
- L63 _public prototype_ `virtual TSharedRef< FGenericWindow > MakeWindow() override;`
- L65 _public prototype_ `virtual void InitializeWindow( const TSharedRef< FGenericWindow >& Window, const TSharedRef< FGenericWindowDefinition >& InDefinition, const TSharedPtr< FGenericWindow >& InParent, const bool bShowImmediately ) override;`
- L67 _public prototype_ `virtual void SetCapture( const TSharedPtr< FGenericWindow >& InWindow ) override;`
- L69 _public prototype_ `virtual void* GetCapture( void ) const override;`
- L71 _public prototype_ `virtual void SetHighPrecisionMouseMode( const bool Enable, const TSharedPtr< FGenericWindow >& InWindow ) override;`
- L73 _public function_ `virtual bool IsUsingHighPrecisionMouseMode() const override`
- L75 _public prototype_ `virtual bool IsGamepadAttached() const override;`
- L77 _public prototype_ `virtual FModifierKeysState GetModifierKeys() const override;`
- L79 _public prototype_ `virtual FPlatformRect GetWorkArea( const FPlatformRect& CurrentWindow ) const override;`
- L81 _public function_ `virtual EWindowTransparency GetWindowTransparencySupport() const override`
- L86 _public prototype_ `void AddPendingEvent( SDL_Event event );`
- L88 _public prototype_ `void RemoveEventWindow(SDL_HWindow Window);`
- L90 _public prototype_ `void RemoveRevertFocusWindow(SDL_HWindow HWnd);`
- L92 _public prototype_ `void RaiseNotificationWindows( const TSharedPtr< FLinuxWindow >& ParentWindow);`
- L94 _public prototype_ `void RemoveNotificationWindow(SDL_HWindow HWnd);`
- L96 _public prototype_ `void CheckIfApplicatioNeedsDeactivation();`
- L98 _public prototype_ `EWindowZone::Type WindowHitTest( const TSharedPtr< FLinuxWindow > &window, int x, int y );`
- L100 _public prototype_ `TSharedPtr< FLinuxWindow > FindWindowBySDLWindow( SDL_Window *win );`
- L102 _public prototype_ `virtual bool IsCursorDirectlyOverSlateWindow() const override;`
- L104 _public prototype_ `virtual bool RequiresPerWindowTooltips() const override;`
- L106 _public prototype_ `virtual TSharedPtr<FGenericWindow> GetWindowUnderCursor() override;`
- L109 _public function_ `inline bool IsForeground()` — Returns true if this application is foreground
- L123 _public prototype_ `void SaveWindowPropertiesForEventLoop(void);` — Windows can move during an event loop (like in FLinuxPlatformMisc::PumpMessages(), but SDL queues many events up before any windows move. This can lead to the screen-space position of the mouse cursor being calculated incorrectly with the old event data and new window location data. Use this to save the window locations for use during the loop.
- L126 _public prototype_ `void ClearWindowPropertiesAfterEventLoop(void);` — Clear out data saved in SaveWindowLocationsForEventLoop().
- L139 _public prototype_ `void GetWindowPropertiesInEventLoop(SDL_HWindow NativeWindow, FWindowProperties& Properties);` — Get a window position inside the event loop. Fall back on SDL_GetWindowPosition if not present in the saved window locations. @param NativeWindow The native SDL_HWindow to look up. This is a drop-in replacement for SDL_GetWindowPosition, so it uses the native window type. @param WindowProperties link to properties structure
- L141 _public prototype_ `virtual bool IsMouseAttached() const override;`
- L148 _public function_ `TSharedPtr< FLinuxWindow > GetCurrentActiveWindow()` — Returns the current active foreground window. @return pointer to the window, if any
- L158 _public function_ `TSharedPtr< FLinuxWindow > GetCurrentFocusWindow()` — Returns the current active foreground window. @return pointer to the window, if any
- L165 _private prototype_ `FLinuxApplication();`
- L175 _private prototype_ `TSharedPtr< FLinuxWindow > FindEventWindow(SDL_Event *Event, bool& bOutWindowlessEvent);` — Finds a window associated with the event (if there is such an association). @param Event event in question @param bOutWindowlessEvent whether or not the event needs to have a window at all @return pointer to the window, if any
- L177 _private prototype_ `void UpdateMouseCaptureWindow( SDL_HWindow TargetWindow );`
- L179 _private prototype_ `void ProcessDeferredMessage( SDL_Event Event );`
- L188 _private prototype_ `static bool GeneratesKeyCharMessage(const SDL_KeyboardEvent & KeyDownEvent);` — Determines whether this particular SDL_KEYDOWN event should also be routed to OnKeyChar() @param KeyDownEvent event in question @return true if character needs to be passed to OnKeyChar
- L191 _private prototype_ `void ActivateApplication();` — Activate this Slate application
- L194 _private prototype_ `void DeactivateApplication();` — Deactivate this Slate application
- L200 _private prototype_ `void ActivateWindow(const TSharedPtr< FLinuxWindow >& Window);` — Acivate the specified Window. That includes the deactivation of the previous window if one was active.
- L202 _private prototype_ `void ActivateRootWindow(const TSharedPtr< FLinuxWindow >& Window);`
- L204 _private prototype_ `TSharedPtr< FLinuxWindow > GetRootWindow(const TSharedPtr< FLinuxWindow >& Window);`
- L207 _private prototype_ `bool HandleCursorCommand(const TCHAR* Cmd, FOutputDevice& Ar);` — Handles "Cursor" exec commands"
- L210 _private prototype_ `bool HandleWindowCommand(const TCHAR* Cmd, FOutputDevice& Ar);` — Handles "Window" exec commands"
- L214 _private prototype_ `void RefreshDisplayCache();`
- L217 _private prototype_ `FVector2D GetTouchEventLocation(SDL_HWindow NativeWindow, SDL_Event TouchEvent);` — Gets the location from a given touch event.
- L220 _private prototype_ `int GetFirstFreeTouchId();` — Searches for a free touch index.
- L223 _public function_ `virtual IInputInterface* GetInputInterface() override`
- L228 _public prototype_ `virtual void SetForceFeedbackChannelValue (int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;` — IInputInterface overrides
- L229 _public prototype_ `virtual void SetForceFeedbackChannelValues(int32 ControllerId, const FForceFeedbackValues &Values) override;`
- L230 _public prototype_ `virtual void SetHapticFeedbackValues(int32 ControllerId, int32 Hand, const FHapticFeedbackValues& Values) override;`
- L231 _public function_ `virtual void SetLightColor(int32 ControllerId, FColor Color) override`
- L232 _public function_ `virtual void ResetLightColor(int32 ControllerId) override`
- L235 _private prototype_ `void AddGameController(SDL_JoystickID Id);`
- L236 _private prototype_ `void RemoveGameController(SDL_JoystickID Id);`
- L238 _private prototype_ `void OnInputDeviceModuleRegistered(const FName& Type, IModularFeature* ModularFeature);`
- L240 _private member_ `uint32 SDLDoubleClickTime;`
- L241 _private member_ `uint32 SDLDoubleClickRadius;`
- L243 _private prototype_ `const uint32 GetSDLDoubleClickTime();`
- L244 _private prototype_ `const uint32 GetSDLDoubleClickRadius();`
- L260 _private member_ `TMap<uint64, FTouchContext> Touches;` — Holds currently active touches (i.e. fingers pressed but not released)
- L263 _private member_ `TArray<TOptional<uint64>> TouchIds;` — Maps touch indexes to SDL touch IDs.
- L292 _private member_ `TArray< SDL_Event > PendingEvents;`
- L294 _private member_ `TArray< TSharedRef< FLinuxWindow > > Windows;`
- L297 _private member_ `TArray< TSharedRef< FLinuxWindow > > NotificationWindows;` — Array of notificaion windows to raise when activating toplevel window
- L300 _private member_ `TArray< TSharedRef< FLinuxWindow > > RevertFocusStack;` — Array of windows to focus when current gets removed.
- L307 _private member_ `TMap<SDL_HWindow, FWindowProperties> SavedWindowPropertiesForEventLoop;` — Saved window properties used for event loop, because the These keys should not be de-referenced (but comparison is okay).
- L309 _private member_ `int32 bAllowedToDeferMessageProcessing;`
- L312 _private member_ `bool bUsingHighPrecisionMouseInput;` — Using high precision mouse input
- L315 _private member_ `bool bIsMouseCursorLocked;` — TODO: describe
- L318 _private member_ `bool bIsMouseCaptureEnabled;` — TODO: describe
- L321 _private member_ `bool bFirstFrameOfWindowMove = false;` — True after every SDL_WINDOWEVENT_HIT_TEST until a following SDL_WINDOWEVENT_MOVED
- L324 _private member_ `float LastTitleBarClickX;` — Used to detect a double click on the title bar area of the window
- L325 _private member_ `float LastTitleBarClickY;`
- L326 _private member_ `uint64 LastTitleBarClickTimestampNS;`
- L327 _private member_ `TSharedPtr< FLinuxWindow > LastTitleBarClickWindow;`
- L334 _private member_ `uint64 LastHitTestTimestampNS;` — Timestamp (ns) of the last SDL_EVENT_WINDOW_HIT_TEST. Used to coalesce the duplicate HIT_TEST events that SDL3 X11 XInput2 emits for every Button1 press
- L337 _private member_ `TSharedPtr< FLinuxWindow > CurrentlyActiveWindow;` — Window that we think has been activated last.
- L338 _private member_ `TSharedPtr< FLinuxWindow > CurrentFocusWindow;`
- L339 _private member_ `TSharedPtr< FLinuxWindow > CurrentClipWindow;`
- L340 _private member_ `TSharedPtr< FLinuxWindow > CurrentUnderCursorWindow;`
- L343 _private member_ `TArray<FString> DragAndDropQueue;` — Stores (unescaped) file URIs received during current drag-n-drop operation.
- L346 _private member_ `TArray<FString> DragAndDropTextQueue;` — Stores text received during current drag-n-drop operation.
- L349 _private member_ `TSharedPtr< FLinuxWindow > PreviousActiveWindow;` — Window that we think has been previously active.
- L351 _private member_ `SDL_HWindow MouseCaptureWindow;`
- L353 _private member_ `TMap<SDL_JoystickID, SDLControllerState> ControllerStates;`
- L355 _private member_ `float fMouseWheelScrollAccel;`
- L358 _private member_ `TArray< TSharedPtr<class IInputDevice> > ExternalInputDevices;` — List of input devices implemented in external modules.
- L361 _private member_ `bool bHasLoadedInputPlugins;` — Whether input plugins have been loaded
- L364 _private member_ `bool bInsideOwnWindow;` — Whether we entered one of our own windows
- L367 _private member_ `bool bIsDragWindowButtonPressed;` — This is used to assist the drag/drop on tabs.
- L370 _private member_ `bool bActivateApp;` — Used to check if the application is active or not.
- L373 _private member_ `double FocusOutDeactivationTime;` — Time before deactivating the application if no FocusIn event happens on any of our Windows
- L382 _private member_ `mutable TArray<FCachedDisplay> CachedDisplays;` — SDL caches full display bounds in-memory but re-fetches _NET_WORKAREA per call for usable bounds.
- L383 _private member_ `mutable double LastTimeCachedDisplays;`

#### struct `FLinuxApplication::FWindowProperties`  
`struct FWindowProperties`  
_L30-37_
- desc: Stores window properties at the beginning of handling the events.
- L33 _public member_ `FVector2D Location;` — Location at the moment of receiving events
- L36 _public member_ `FVector2D Size;` — Size at the moment of receiving events

#### enum `FLinuxApplication::UserDefinedEvents`  
`enum UserDefinedEvents`  
_L41-44_
- L43 _public enumerator_ `CheckForDeactivation`

#### struct `FLinuxApplication::FTouchContext`  
`struct FTouchContext`  
_L247-257_
- desc: Stores context information about a currently active touch.
- L250 _public member_ `int TouchIndex;` — Internal touch index (0-9 normally).
- L253 _public member_ `SDL_TouchID DeviceId;` — Device id
- L256 _public member_ `FVector2D Location;` — Last known location.

#### struct `FLinuxApplication::SDLControllerState`  
`struct SDLControllerState`  
_L265-290_
- L268 _public member_ `SDL_Gamepad* Controller;` — SDL controller
- L271 _public member_ `bool AnalogOverThreshold[10];` — Tracks whether the "button" was previously pressed so we don't generate extra events
- L274 _public member_ `FInputDeviceId DeviceId;` — The input device Id of the controller that can be used to find the matching ULocalPlayer
- L277 _public member_ `TMap<FGamepadKeyNames::Type, float> AxisEvents;` — Store axis values from events here to be handled once per frame.
- L280 _public member_ `FForceFeedbackValues ForceFeedbackValues;` — Current force feedback values
- L282 _public function_ `SDLControllerState() : Controller(nullptr) , DeviceId(INPUTDEVICEID_NONE)`
- L289 _public prototype_ `void UpdateHapticEffect();`

#### struct `FLinuxApplication::FCachedDisplay`  
`struct FCachedDisplay`  
_L375-379_
- L377 _public member_ `SDL_DisplayID Id;`
- L378 _public member_ `SDL_Rect UsableBounds;`

#### Free symbols / members of external scopes

- L386 _externvar_ `extern FLinuxApplication* LinuxApplication;`

### `Source/Runtime/ApplicationCore/Public/Linux/LinuxConsoleOutputDevice.h` (Public)


#### class `FLinuxConsoleOutputDevice`  
`class FLinuxConsoleOutputDevice : public FOutputDeviceConsole`  
_L11-66_
- inherits: `FOutputDeviceConsole`
- desc: Linux implementation of console log window, just a printf to the terminal for now
- L17 _private member_ `bool bOverrideColorSet;` — true if the color is currently set by the caller
- L20 _private member_ `bool bOutputtingToTerminal;` — true if we are outputting to a terminal
- L23 _private member_ `bool bIsWindowShown;` — true if window is visible
- L26 _private member_ `bool bIsStdoutSet;` — true if stdout is set via the command line
- L29 _private member_ `ELogVerbosity::Type AllowedLogVerbosity = ELogVerbosity::All;` — maximum allowed log verbosity
- L36 _public prototype_ `FLinuxConsoleOutputDevice();` — Constructor, setting console control handler.
- L37 _public prototype_ `~FLinuxConsoleOutputDevice();`
- L44 _public prototype_ `virtual void Show(bool bShowWindow);` — Shows or hides the console window. @param ShowWindow	Whether to show (true) or hide (false) the console window.
- L51 _public prototype_ `virtual bool IsShown();` — Returns whether console is currently shown or not @return true if console is shown, false otherwise
- L53 _public function_ `virtual bool IsAttached()`
- L55 _public prototype_ `virtual bool CanBeUsedOnAnyThread() const override;`
- L56 _public prototype_ `virtual bool CanBeUsedOnPanicThread() const override;`
- L64 _public prototype_ `void Serialize(const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category);` — Displays text on the console and scrolls if necessary. @param Data	Text to display @param Event	Event type, used for filtering/ suppression

### `Source/Runtime/ApplicationCore/Public/Linux/LinuxCursor.h` (Public)


#### class `FLinuxCursor`  
`class FLinuxCursor : public ICursor`  
_L12-85_
- inherits: `ICursor`
- L15 _public prototype_ `FLinuxCursor();`
- L17 _public prototype_ `virtual ~FLinuxCursor();`
- L19 _public function_ `virtual bool IsCreateCursorFromRGBABufferSupported() const override`
- L24 _public prototype_ `virtual void* CreateCursorFromRGBABuffer(const FColor* Pixels, int32 Width, int32 Height, FVector2D InHotSpot) override;`
- L26 _public prototype_ `virtual FVector2D GetPosition() const override;`
- L28 _public prototype_ `virtual void SetPosition( const int32 X, const int32 Y ) override;`
- L30 _public prototype_ `virtual void SetType( const EMouseCursor::Type InNewCursor ) override;`
- L32 _public function_ `virtual EMouseCursor::Type GetType() const override`
- L37 _public prototype_ `virtual void GetSize( int32& Width, int32& Height ) const override;`
- L39 _public prototype_ `virtual void Show( bool bShow ) override;`
- L41 _public prototype_ `virtual void Lock( const RECT* const Bounds ) override;`
- L43 _public prototype_ `virtual void SetTypeShape(EMouseCursor::Type InCursorType, void* CursorHandle) override;`
- L52 _public prototype_ `virtual void SetCustomShape( SDL_HCursor CursorHandle );` — Defines a custom cursor shape for the EMouseCursor::Custom type. @param CursorHandle	A native cursor handle to show when EMouseCursor::Custom is selected.
- L54 _public prototype_ `bool IsHidden();`
- L59 _public prototype_ `void InvalidateCaches();` — Invalidates whatever cached data cursor may have
- L62 _public prototype_ `void SetCachedPosition( const float X, const float Y );` — Set the internal cached position, setting the cache to valid
- L66 _private member_ `EMouseCursor::Type CurrentType;`
- L67 _private member_ `bool bHidden;`
- L70 _private member_ `SDL_HCursor CursorHandles[ EMouseCursor::TotalCursorCount ];` — Cursors
- L73 _private member_ `SDL_HCursor CursorOverrideHandles[ EMouseCursor::TotalCursorCount ];` — Override Cursors
- L75 _private member_ `SDL_Rect CursorClipRect;`
- L78 _private member_ `mutable float CachedGlobalXPosition;` — Cached global X position
- L81 _private member_ `mutable float CachedGlobalYPosition;` — Cached global Y position
- L84 _private member_ `mutable bool bPositionCacheIsValid;` — Whether mouse position cache is valid

#### Free symbols / members of external scopes

- L10 _typedef_ `typedef SDL_Cursor* SDL_HCursor;`

### `Source/Runtime/ApplicationCore/Public/Linux/LinuxPlatformApplicationMisc.h` (Public)


#### struct `FLinuxPlatformApplicationMisc`  
`struct FLinuxPlatformApplicationMisc : public FGenericPlatformApplicationMisc`  
_L7-67_
- inherits: `FGenericPlatformApplicationMisc`
- L9 _public prototype_ `static void PreInit();`
- L10 _public prototype_ `static void Init();`
- L11 _public prototype_ `static bool InitSDL();`
- L12 _public prototype_ `static void TearDown();`
- L13 _public prototype_ `static void LoadPreInitModules();`
- L14 _public prototype_ `static void LoadStartupModules();`
- L15 _public prototype_ `static uint64 WindowStyle();`
- L16 _public prototype_ `static class FOutputDeviceConsole* CreateConsoleOutputDevice();`
- L17 _public prototype_ `static class FOutputDeviceError* GetErrorOutputDevice();`
- L18 _public prototype_ `static class FFeedbackContext* GetFeedbackContext();`
- L19 _public prototype_ `static class GenericApplication* CreateApplication();`
- L20 _public prototype_ `static bool IsThisApplicationForeground();`
- L21 _public prototype_ `static void PumpMessages(bool bFromMainLoop);`
- L22 _public prototype_ `static bool IsScreensaverEnabled();`
- L23 _public prototype_ `static bool ControlScreensaver(EScreenSaverAction Action);`
- L24 _public prototype_ `static float GetDPIScaleFactorAtPoint(float X, float Y);`
- L25 _public prototype_ `static void ClipboardCopy(const TCHAR* Str);`
- L26 _public prototype_ `static void ClipboardPaste(class FString& Dest);`
- L27 _public function_ `static bool FullscreenSameAsWindowedFullscreen()`
- L28 _public prototype_ `static bool IsUsingWayland();` — Is SDL using native Wayland video driver
- L29 _public prototype_ `static bool IsUsingX11();` — Is SDL using X11 video driver
- L30 _public prototype_ `static bool RequiresParentedNotifications();` — True on pure Wayland (cannot position top-level windows)
- L33 _public prototype_ `static void EarlyUnixInitialization(class FString& OutCommandLine);` — Unix specific
- L34 _public function_ `static bool ShouldIncreaseProcessLimits()`
- L39 _public prototype_ `static void DeferDestroyWindow(struct SDL_Window* Window);` — Mark a window for destruction once all RHI surface refs are released. The actual SDL_DestroyWindow runs on the game thread in PumpMessages once the refcount reaches zero (or a wall-clock backstop elapses). Replaces the old fixed-frame defer.
- L46 _public prototype_ `static uint32 AcquireWindowForRHI(void* SdlWindow);` — Register that an RHI surface now backs this window. Called from the RHI right after a Vulkan surface is created for the window. Thread-safe (RHI thread). Returns the SDL window id the ref was recorded under (0 on failure). Release must be keyed on this immutable, never-recycled id (the RHI carries it on the window context / swapchain) rather than on a pointer that may be stale or reused by destroy time.
- L53 _public prototype_ `static void ReleaseWindowForRHI(uint32 WindowId);` — Release an RHI surface ref for the window previously acquired under WindowId. Called from the RHI right after the Vulkan surface is destroyed. Thread-safe (RHI thread). Never destroys the window itself. Keyed on the immutable, never-recycled SDL window id, so a release that arrives after the window is already gone (e.g. via the destroy backstop) is a safe no-op and can never decrement a different window's refcount.
- L57 _public prototype_ `static void DeferHideWindow(struct SDL_Window* Window);` — Queue SDL_HideWindow for 3 PumpMessages ticks. Caller must set UE.window.present_enabled=false on the window first.
- L60 _public prototype_ `static void CancelDeferredHideWindow(struct SDL_Window* Window);` — Remove a window from the deferred-hide queue. No-op if not queued.
- L64 _public prototype_ `static void UsingVulkan();` — Informs ApplicationCore that it needs to create Vulkan-compatible windows (mutually exclusive with OpenGL)
- L66 _public prototype_ `static void UsingOpenGL();` — Informs ApplicationCore that it needs to create OpenGL-compatible windows (mutually exclusive with Vulkan)

#### Free symbols / members of external scopes

- L69 _typedef_ `typedef FLinuxPlatformApplicationMisc FPlatformApplicationMisc;`

### `Source/Runtime/ApplicationCore/Public/Linux/LinuxPlatformSplash.h` (Public)


#### struct `FLinuxPlatformSplash`  
`struct FLinuxPlatformSplash : public FGenericPlatformSplash`  
_L15-34_
- inherits: `FGenericPlatformSplash`
- desc: Linux splash implementation
- L20 _public prototype_ `static void Show();` — Show the splash screen
- L24 _public prototype_ `static void Hide();` — Hide the splash screen
- L33 _public prototype_ `static void SetSplashText(const SplashTextType::Type InType, const FText& InText);`

#### Free symbols / members of external scopes

- L36 _typedef_ `typedef FLinuxPlatformSplash FPlatformSplash;`

### `Source/Runtime/ApplicationCore/Public/Linux/LinuxPlatformSurvey.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/ApplicationCore/Public/Linux/LinuxWindow.h` (Public)


#### class `FLinuxWindow`  
`class FLinuxWindow : public FGenericWindow`  
_L27-300_
- inherits: `FGenericWindow`
- desc: A platform specific implementation of FNativeWindow. Native Windows provide platform-specific backing for and are always owned by an SWindow.
- L30 _public prototype_ `~FLinuxWindow();`
- L40 _public prototype_ `static TSharedRef< FLinuxWindow > Make();` — Create a new SDLWindow. @param SlateWindows		List of all top level Slate windows.  This function will add the owner window to this list. @param OwnerWindow		The SlateWindow for which we are crating a backing Win32Window @param InHInstance		Win32 application instance handle @param InParent			Parent Win32 window; usually NULL. @param bShowImmediately	True to show this window as soon as its initialized
- L42 _public prototype_ `SDL_HWindow GetHWnd() const;`
- L44 _public prototype_ `void Initialize( class FLinuxApplication* const Application, const TSharedRef< FGenericWindowDefinition >& InDefinition, const TSharedPtr< FLinuxWindow >& InParent, const bool bShowImmediately );`
- L47 _public prototype_ `bool IsRegularWindow() const;` — TODO: describe
- L50 _public prototype_ `bool IsPopupMenuWindow() const;` — TODO: describe
- L53 _public prototype_ `bool IsTooltipWindow() const;` — TODO: describe
- L56 _public prototype_ `bool IsNotificationWindow() const;` — TODO: describe
- L59 _public prototype_ `bool IsTopLevelWindow() const;` — TODO: describe
- L62 _public prototype_ `bool IsModalWindow() const;` — @return true if this is a modal window
- L65 _public prototype_ `bool IsDialogWindow() const;` — TODO: describe
- L68 _public prototype_ `bool IsDragAndDropWindow() const;` — TODO: describe
- L71 _public prototype_ `bool IsUtilityWindow() const;` — TODO: describe
- L74 _public prototype_ `EWindowActivationPolicy GetActivationPolicy() const;` — @return the window activation policy used when showing the window
- L77 _public prototype_ `bool IsFocusWhenFirstShown() const;` — TODO: describe
- L80 _public prototype_ `const TSharedPtr< FLinuxWindow >& GetParent() const;` — TODO: describe
- L83 _public prototype_ `uint32 GetID() const;` — Internal ID using for debugging
- L86 _public prototype_ `void LogInfo();` — Debugging function - dumps window info to log
- L88 _public prototype_ `bool IsNativeMoving() const;`
- L89 _public prototype_ `bool BeginNativeMove();`
- L90 _public prototype_ `void AfterNativeMove();`
- L91 _public prototype_ `void EndNativeMove();`
- L107 _public prototype_ `bool IsNativeResizing() const;`
- L108 _public prototype_ `bool BeginNativeResize( NativeResizeDirection Direction );`
- L109 _public prototype_ `void AfterNativeResize();`
- L110 _public prototype_ `void EndNativeResize();`
- L113 _public prototype_ `virtual void ReshapeWindow( int32 X, int32 Y, int32 Width, int32 Height ) override;`
- L115 _public function_ `virtual void* GetOSWindowHandle() const override`
- L118 _public prototype_ `virtual bool GetFullScreenInfo( int32& X, int32& Y, int32& Width, int32& Height ) const override;` — not finished
- L120 _public prototype_ `virtual void MoveWindowTo ( int32 X, int32 Y ) override;`
- L122 _public prototype_ `virtual void BringToFront( bool bForce = false ) override;`
- L124 _public prototype_ `virtual void Destroy() override;`
- L126 _public prototype_ `virtual void Minimize() override;`
- L128 _public prototype_ `virtual void Maximize() override;`
- L130 _public prototype_ `virtual void Restore() override;`
- L132 _public prototype_ `virtual void Show() override;`
- L134 _public prototype_ `virtual void Hide() override;`
- L136 _public prototype_ `virtual void SetWindowMode( EWindowMode::Type NewWindowMode ) override;`
- L138 _public function_ `virtual EWindowMode::Type GetWindowMode() const override`
- L140 _public prototype_ `virtual bool IsMaximized() const override;`
- L142 _public prototype_ `virtual bool IsVisible() const override;`
- L144 _public prototype_ `virtual bool IsMinimized() const override;`
- L146 _public prototype_ `virtual bool GetRestoredDimensions(int32& X, int32& Y, int32& Width, int32& Height) override;`
- L148 _public prototype_ `virtual void SetWindowFocus() override;`
- L150 _public prototype_ `virtual void SetOpacity( const float InOpacity ) override;`
- L152 _public prototype_ `virtual void Enable( bool bEnable ) override;`
- L154 _public prototype_ `virtual bool IsPointInWindow( int32 X, int32 Y ) const override;`
- L156 _public prototype_ `virtual int32 GetWindowBorderSize() const override;`
- L158 _public prototype_ `virtual bool IsForegroundWindow() const override;`
- L164 _public prototype_ `virtual void SetText(const TCHAR* const Text) override;` — Sets the window text - usually the title but can also be text content for things like controls @param Text	The window's title or content text
- L167 _public prototype_ `virtual void AdjustCachedSize( FVector2D& Size ) const override;` — @return	Gives the native window a chance to adjust our stored window size before we cache it off
- L169 _public function_ `virtual float GetDPIScaleFactor() const override`
- L174 _public function_ `virtual void SetDPIScaleFactor(float Value) override`
- L185 _public prototype_ `void GetNativeBordersSize(int32& OutLeftBorderWidth, int32& OutTopBorderHeight) const;` — Returns window border sizes (frame extents). @param BorderWidth - width of a vertical border (left side) @param BorderHeight - height of a horizontal border (from the top)
- L191 _public prototype_ `void CacheNativeProperties();` — Caches window properties that are too expensive to query all the time. (e.g. border sizes)
- L198 _private prototype_ `FLinuxWindow();` — Protect the constructor; only TSharedRefs of this class can be made.
- L202 _private member_ `FLinuxApplication* OwningApplication;`
- L205 _private member_ `SDL_HWindow HWnd;` — linux window handle
- L208 _private member_ `int32 RegionWidth;` — Store the window region size for querying whether a point lies within the window
- L209 _private member_ `int32 RegionHeight;`
- L212 _private member_ `EWindowMode::Type WindowMode;` — The mode that the window is in (windowed, fullscreen, windowedfullscreen )
- L214 _private member_ `RECT PreFullscreenWindowRect;`
- L220 _private member_ `int32 VirtualWidth;` — Virtual width and height of the window.  This is only different than the actual width and height for windows which we're trying to optimize because their size changes frequently.  We'll create a larger window and have Windows draw it "cropped" so that it appears smaller, rather than actually resizing it and incurring a GPU buffer resize performance hit
- L221 _private member_ `int32 VirtualHeight;`
- L224 _private member_ `bool bIsVisible;` — TODO: describe
- L227 _private member_ `bool bWasFullscreen;` — TODO: describe
- L230 _private member_ `bool bIsPopupWindow;` — TODO: describe
- L233 _private member_ `bool bIsTooltipWindow;` — TODO: describe
- L236 _private member_ `bool bIsConsoleWindow;` — TODO: describe
- L239 _private member_ `bool bIsDialogWindow;` — TODO: describe
- L242 _private member_ `bool bIsNotificationWindow;` — TODO: describe
- L245 _private member_ `bool bIsTopLevelWindow;` — TODO: describe
- L248 _private member_ `bool bIsDragAndDropWindow;` — TODO: describe
- L251 _private member_ `bool bIsUtilityWindow;` — TODO: describe
- L254 _private member_ `bool bIsPointerInsideWindow;` — Whether the is inside this window
- L257 _private member_ `uint32 WindowSDLID;` — SDL ID (for debugging purposes)
- L260 _private member_ `TSharedPtr< FLinuxWindow > ParentWindow;` — Parent window as given by Slate
- L261 _private prototype_ `static SDL_HitTestResult HitTest( SDL_Window *SDLwin, const SDL_Point *point, void *data );`
- L272 _private prototype_ `static void ConvertToParentRelativePosition(SDL_Window* ThisWindow, int32& X, int32& Y);` — Converts screen-absolute coordinates to parent-relative coordinates for popup menu and tooltip windows. Walks the parent chain to accumulate offsets. For windows that are not parent-relative, X and Y are left unmodified. @param ThisWindow	The window whose position is being converted. @param X				In/out X coordinate to convert. @param Y				In/out Y coordinate to convert.
- L284 _private prototype_ `static void GetParentRelativeOffset(SDL_PropertiesID Props, SDL_Window* StartParent, int32& X, int32& Y);` — Gets the offset from screen-absolute to parent-relative coordinates during window creation. If Props indicates the window is not parent-relative, X and Y are set to 0. Use ConvertToParentRelativePosition() if the window already exists. @param Props			SDL properties for the window being created. @param StartParent	The parent window for the window being created. @param X				Out: X offset to apply. @param Y				Out: Y offset to apply.
- L287 _private member_ `int32 LeftBorderWidth;` — Cached width of the left border
- L290 _private member_ `int32 TopBorderHeight;` — Cached height of the top border
- L293 _private member_ `bool bValidNativePropertiesCache;` — Whether native properties cache is valid
- L299 _private member_ `float DPIScaleFactor;` — Ratio of pixels to SlateUnits in this window. E.g. DPIScale of 2.0 means there is a 2x2 pixel square for every 1x1 SlateUnit.

#### enum `FLinuxWindow::NativeResizeDirection`  
`enum NativeResizeDirection`  
_L93-105_
- L95 _public enumerator_ `ResizeSouthWest = 0`
- L96 _public enumerator_ `ResizeSouth`
- L97 _public enumerator_ `ResizeSouthEast`
- L98 _public enumerator_ `ResizeEast`
- L99 _public enumerator_ `ResizeNorthEast`
- L100 _public enumerator_ `ResizeNorth`
- L101 _public enumerator_ `ResizeNorthWest`
- L102 _public enumerator_ `ResizeWest`
- L104 _public enumerator_ `InvalidDirection`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN( LogLinuxWindow, Log, All );`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN( LogLinuxWindow, Log, All );`
- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN( LogLinuxWindowType, Log, All );`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN( LogLinuxWindowType, Log, All );`
- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN( LogLinuxWindowEvent, Log, All );`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN( LogLinuxWindowEvent, Log, All );`
- L19 _typedef_ `typedef SDL_Window* SDL_HWindow;`

### `Source/Runtime/ApplicationCore/Public/Mac/Accessibility/CocoaAccessibilityView.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/ApplicationCore/Public/Mac/Accessibility/MacAccessibilityElement.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/ApplicationCore/Public/Mac/Accessibility/MacAccessibilityManager.h` (Public)


#### Free symbols / members of external scopes

- L30 _variable_ `@property (nonatomic) class FMacApplication* MacApplication;` — Pointer to the Mac Application that initialized this Singleton

### `Source/Runtime/ApplicationCore/Public/Mac/CocoaMenu.h` (Public)


#### Free symbols / members of external scopes

- L7 _variable_ `OBJC_EXPORT @interface FCocoaMenu : NSMenu { @private bool bHighlightingKeyEquivalent; } - (bool)isHighlightingKeyEquivalent;`

### `Source/Runtime/ApplicationCore/Public/Mac/CocoaTextView.h` (Public)


#### Free symbols / members of external scopes

- L19 _variable_ `TSharedPtr<ITextInputMethodContext> IMMContext;`
- L20 _variable_ `NSRange markedRange;`
- L21 _variable_ `bool reallyHandledEvent;`

### `Source/Runtime/ApplicationCore/Public/Mac/CocoaWindow.h` (Public)


#### Free symbols / members of external scopes

- L19 _variable_ `EWindowMode::Type WindowMode;`
- L20 _variable_ `bool bRenderInitialized;`
- L21 _variable_ `bool bIsBeingOrderedFront;`
- L22 _variable_ `CGFloat Opacity;`
- L25 _variable_ `bool bZoomed;`
- L26 _variable_ `bool bIsOnActiveSpace;`
- L27 _variable_ `bool bIsBeingResized;`
- L28 _variable_ `bool bMinimized;`
- L29 _variable_ `bool bKeyWindow;`
- L30 _variable_ `NSScreen* CachedScreen;`
- L31 _variable_ `CGFloat CachedBackingScaleFactor;`
- L70 _externvar_ `extern NSString* NSDraggingUpdated;`
- L71 _externvar_ `extern NSString* NSPrepareForDragOperation;`
- L72 _externvar_ `extern NSString* NSPerformDragOperation;`

### `Source/Runtime/ApplicationCore/Public/Mac/MacApplication.h` (Public)


#### struct `FDeferredMacEvent`  
`struct FDeferredMacEvent`  
_L17-119_
- L19 _public function_ `FDeferredMacEvent() : Event(nullptr) , Window(nullptr) , Type(0) , LocationInWindow(FVector2D::ZeroVector) , ModifierFlags(0) , Timestamp(0.0) , WindowNumber(0) , Context(nullptr) , Delta(FVector2D::ZeroVector) , ScrollingDelta(FVector2D::ZeroVector) , ButtonNumber(0) , ClickCount(0) , Phase(NSEventPhaseNone) , MomentumPhase(NSEventPhaseNone) , IsDirectionInvertedFromDevice(false) , Character(0) , CharCode(0) , IsRepeat(false) , IsPrintable(false) , KeyCode(0) , NotificationName(nullptr) , DraggingPasteboard(nullptr)`
- L45 _public function_ `FDeferredMacEvent(const FDeferredMacEvent& Other) : Event(Other.Event ? [Other.Event retain] : nullptr) , Window(Other.Window) , Type(Other.Type) , LocationInWindow(Other.LocationInWindow) , ModifierFlags(Other.ModifierFlags) , Timestamp(Other.Timestamp) , WindowNumber(Other.WindowNumber) , Context(Other.Context ? [Other.Context retain] : nullptr) , Delta(Other.Delta) , ScrollingDelta(Other.ScrollingDelta) , ButtonNumber(Other.ButtonNumber) , ClickCount(Other.ClickCount) , Phase(Other.Phase) , MomentumPhase(Other.MomentumPhase) , IsDirectionInvertedFromDevice(Other.IsDirectionInvertedFromDevice) , Character(Other.Character) , CharCode(Other.CharCode) , IsRepeat(Other.IsRepeat) , IsPrintable(Other.IsPrintable) , KeyCode(Other.KeyCode) , NotificationName(Other.NotificationName ? [Other.NotificationName retain] : nullptr) , DraggingPasteboard(Other.DraggingPasteboard ? [Other.DraggingPasteboard retain] : nullptr)`
- L71 _public function_ `~FDeferredMacEvent()`
- L94 _public member_ `NSEvent* Event;` — Using NSEvent on the game thread is unsafe, so we copy of all its properties and use them when processing the event. However, in some cases we need the original NSEvent (highlighting menus, resending unhandled key events), so we store it as well.
- L96 _public member_ `FCocoaWindow* Window;`
- L98 _public member_ `int32 Type;`
- L99 _public member_ `FVector2D LocationInWindow;`
- L100 _public member_ `uint32 ModifierFlags;`
- L101 _public member_ `NSTimeInterval Timestamp;`
- L102 _public member_ `int32 WindowNumber;`
- L103 _public member_ `NSGraphicsContext* Context;`
- L104 _public member_ `FVector2D Delta;`
- L105 _public member_ `FVector2D ScrollingDelta;`
- L106 _public member_ `int32 ButtonNumber;`
- L107 _public member_ `int32 ClickCount;`
- L108 _public member_ `NSEventPhase Phase;`
- L109 _public member_ `NSEventPhase MomentumPhase;`
- L110 _public member_ `bool IsDirectionInvertedFromDevice;`
- L111 _public member_ `TCHAR Character;`
- L112 _public member_ `TCHAR CharCode;`
- L113 _public member_ `bool IsRepeat;`
- L114 _public member_ `bool IsPrintable;`
- L115 _public member_ `uint32 KeyCode;`
- L117 _public member_ `NSString* NotificationName;`
- L118 _public member_ `NSPasteboard* DraggingPasteboard;`

#### struct `FMacScreen`  
`struct FMacScreen`  
_L121-134_
- L123 _public member_ `NSScreen* Screen;`
- L124 _public member_ `NSRect Frame;`
- L125 _public member_ `NSRect VisibleFrame;`
- L126 _public member_ `NSRect FramePixels;`
- L127 _public member_ `NSRect VisibleFramePixels;`
- L128 _public member_ `NSEdgeInsets SafeAreaInsets;`
- L130 _public function_ `FMacScreen(NSScreen* InScreen) : Screen([InScreen retain]), Frame(InScreen.frame), VisibleFrame(InScreen.visibleFrame), FramePixels(InScreen.frame), VisibleFramePixels(InScreen.visibleFrame), SafeAreaInsets(InScreen.safeAreaInsets)`
- L133 _public function_ `~FMacScreen()`

#### class `FMacApplication`  
`class FMacApplication : public GenericApplication , public IInputInterface`  
_L140-448_
- inherits: `GenericApplication,IInputInterface`
- desc: Mac-specific application implementation.
- L146 _public prototype_ `static FMacApplication* CreateMacApplication();`
- L150 _public prototype_ `~FMacApplication();`
- L154 _public prototype_ `virtual void SetMessageHandler(const TSharedRef<class FGenericApplicationMessageHandler>& InMessageHandler) override;`
- L156 _public prototype_ `virtual void SetAccessibleMessageHandler(const TSharedRef<FGenericAccessibleMessageHandler>& InAccessibleMessageHandler) override;`
- L159 _public prototype_ `void OnVoiceoverEnabled();` — Called when Voiceover is enabled. FMacAccessibilityManager should be the only class to call this
- L162 _public prototype_ `void OnVoiceoverDisabled();` — Called when Voiceover is disabled. FMacAccessibilityManager should be the only class to call this
- L166 _public prototype_ `virtual void PollGameDeviceState(const float TimeDelta) override;`
- L168 _public prototype_ `virtual void PumpMessages(const float TimeDelta) override;`
- L170 _public prototype_ `virtual void ProcessDeferredEvents(const float TimeDelta) override;`
- L172 _public prototype_ `void DismissAllMenusOnGameThread();`
- L174 _public prototype_ `virtual TSharedRef<FGenericWindow> MakeWindow() override;`
- L176 _public prototype_ `virtual void InitializeWindow(const TSharedRef<FGenericWindow>& Window, const TSharedRef<FGenericWindowDefinition>& InDefinition, const TSharedPtr<FGenericWindow>& InParent, const bool bShowImmediately) override;`
- L178 _public prototype_ `virtual FModifierKeysState GetModifierKeys() const override;`
- L180 _public prototype_ `virtual bool IsCursorDirectlyOverSlateWindow() const override;`
- L182 _public prototype_ `virtual TSharedPtr<FGenericWindow> GetWindowUnderCursor() override;`
- L184 _public prototype_ `virtual void SetHighPrecisionMouseMode(const bool Enable, const TSharedPtr<FGenericWindow>& InWindow) override;`
- L186 _public function_ `virtual bool IsUsingHighPrecisionMouseMode() const override`
- L188 _public function_ `virtual bool IsUsingTrackpad() const override`
- L190 _public prototype_ `virtual bool IsGamepadAttached() const override;`
- L192 _public prototype_ `virtual FPlatformRect GetWorkArea(const FPlatformRect& CurrentWindow) const override;`
- L194 _public function_ `virtual EWindowTitleAlignment::Type GetWindowTitleAlignment() const override`
- L196 _public function_ `virtual EWindowTransparency GetWindowTransparencySupport() const override`
- L198 _public function_ `virtual ITextInputMethodSystem *GetTextInputMethodSystem() override`
- L201 _public prototype_ `virtual void SendAnalytics(IAnalyticsProvider* Provider) override;`
- L203 _public prototype_ `void StartScopedModalEvent(const FCoreDelegates::FModalWindowContext& Context);`
- L205 _public prototype_ `void EndScopedModalEvent(const FCoreDelegates::FModalWindowContext& Context);`
- L209 _public prototype_ `void ResendLastEvent();`
- L211 _public prototype_ `void CloseWindow(TSharedRef<FMacWindow> Window);`
- L213 _public prototype_ `void DeferEvent(NSObject* Object);`
- L215 _public function_ `bool IsProcessingDeferredEvents() const`
- L217 _public prototype_ `TSharedPtr<FMacWindow> FindWindowByNSWindow(FCocoaWindow* WindowHandle);`
- L219 _public prototype_ `void OnWindowWillResize(TSharedRef<FMacWindow> Window);`
- L222 _public prototype_ `void InvalidateTextLayout(FCocoaWindow* Window);` — Queues a window for text layout invalidation when safe
- L224 _public function_ `void ResetModifierKeys()`
- L228 _public prototype_ `void ReassociateMouseInput();` — Restore mouse input state after macOS state transitions (sleep, minimize, app switch) that may silently reset CGAssociate or invalidate GCMouse handlers.
- L230 _public function_ `bool IsWorkspaceSessionActive() const`
- L232 _public function_ `void SystemModalMode(bool const bInSystemModalMode)`
- L234 _public function_ `const TArray<TSharedRef<FMacWindow>>& GetAllWindows() const`
- L236 _public function_ `FCriticalSection& GetWindowsArrayMutex()`
- L238 _public prototype_ `void OnCursorLock();`
- L240 _public function_ `void IgnoreMouseMoveDelta()`
- L242 _public function_ `void SetIsRightClickEmulationEnabled(bool bEnabled)`
- L244 _public prototype_ `void OnWindowDidResize(TSharedRef<FMacWindow> Window, bool bRestoreMouseCursorLocking = false);`
- L246 _public prototype_ `void OnWindowChangedScreen(TSharedRef<FMacWindow> Window);`
- L248 _public prototype_ `void OnWindowOrderedFront(TSharedRef<FMacWindow> Window);`
- L250 _public prototype_ `void OnWindowActivationChanged(const TSharedRef<FMacWindow>& Window, const EWindowActivation ActivationType);`
- L252 _public prototype_ `static void OnDisplayReconfiguration(CGDirectDisplayID Display, CGDisplayChangeSummaryFlags Flags, void* UserInfo);`
- L254 _public function_ `inline bool IsDisplayReconfiguring() const`
- L257 _public function_ `virtual IInputInterface* GetInputInterface() override`
- L261 _public prototype_ `virtual void SetForceFeedbackChannelValue (int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;`
- L262 _public prototype_ `virtual void SetForceFeedbackChannelValues(int32 ControllerId, const FForceFeedbackValues &Values) override;`
- L263 _public prototype_ `virtual void SetHapticFeedbackValues(int32 ControllerId, int32 Hand, const FHapticFeedbackValues& Values) override;`
- L264 _public prototype_ `virtual void SetLightColor(int32 ControllerId, FColor Color) override;`
- L265 _public prototype_ `virtual void ResetLightColor(int32 ControllerId) override;`
- L266 _public prototype_ `virtual void SetDeviceProperty(int32 ControllerId, const FInputDeviceProperty* Property) override;`
- L269 _public prototype_ `static void UpdateScreensArray();`
- L271 _public prototype_ `static FMacScreenRef FindScreenBySlatePosition(double X, double Y);`
- L273 _public prototype_ `static FMacScreenRef FindScreenByCocoaPosition(double X, double Y);`
- L275 _public prototype_ `static FVector2D ConvertSlatePositionToCocoa(double X, double Y);`
- L277 _public prototype_ `static FVector2D ConvertCocoaPositionToSlate(double X, double Y);`
- L279 _public prototype_ `static CGPoint ConvertSlatePositionToCGPoint(double X, double Y);`
- L281 _public prototype_ `static FVector2D CalculateScreenOrigin(NSScreen* Screen);`
- L283 _public prototype_ `static float GetPrimaryScreenBackingScaleFactor();`
- L285 _public typedef_ `typedef void (*MenuBarShutdownFuncPtr)();`
- L286 _public member_ `static MenuBarShutdownFuncPtr MenuBarShutdownFunc;`
- L288 _public prototype_ `static unichar TranslateKeyCodeToUniCode(uint32 KeyCode, uint32 Modifier);`
- L292 _private prototype_ `static NSEvent* HandleNSEvent(NSEvent* Event);`
- L294 _private prototype_ `static int32 MTContactCallback(void* Device, void* Data, int32 NumFingers, double TimeStamp, int32 Frame);`
- L297 _private prototype_ `FMacApplication();`
- L299 _private prototype_ `void ProcessEvent(const FDeferredMacEvent& Event);`
- L300 _private prototype_ `void ResendEvent(NSEvent* Event);`
- L302 _private prototype_ `void ProcessMouseMovedEvent(const FDeferredMacEvent& Event, TSharedPtr<FMacWindow> EventWindow);`
- L303 _private prototype_ `void ProcessMouseDownEvent(const FDeferredMacEvent& Event, TSharedPtr<FMacWindow> EventWindow);`
- L304 _private prototype_ `void ProcessMouseUpEvent(const FDeferredMacEvent& Event, TSharedPtr<FMacWindow> EventWindow);`
- L305 _private prototype_ `void ProcessScrollWheelEvent(const FDeferredMacEvent& Event, TSharedPtr<FMacWindow> EventWindow);`
- L306 _private prototype_ `void ProcessGestureEvent(const FDeferredMacEvent& Event);`
- L307 _private prototype_ `void ProcessKeyDownEvent(const FDeferredMacEvent& Event, TSharedPtr<FMacWindow> EventWindow);`
- L308 _private prototype_ `void ProcessKeyUpEvent(const FDeferredMacEvent& Event);`
- L310 _private prototype_ `void OnWindowDidMove(TSharedRef<FMacWindow> Window);`
- L311 _private prototype_ `bool OnWindowDestroyed(TSharedRef<FMacWindow> DestroyedWindow);`
- L312 _private prototype_ `void OnWindowActivated(TSharedRef<FMacWindow> Window);`
- L314 _private prototype_ `void OnApplicationDidBecomeActive();`
- L315 _private prototype_ `void OnApplicationWillResignActive();`
- L316 _private prototype_ `void OnWindowsReordered();`
- L317 _private prototype_ `void OnActiveSpaceDidChange();`
- L319 _private prototype_ `void CacheKeyboardInputSource();`
- L321 _private prototype_ `void ConditionallyUpdateModifierKeys(const FDeferredMacEvent& Event);`
- L322 _private prototype_ `void HandleModifierChange(NSUInteger NewModifierFlags, NSUInteger FlagsShift, NSUInteger UEShift, EMacModifierKeys TranslatedCode);`
- L324 _private prototype_ `FCocoaWindow* FindEventWindow(NSEvent* CocoaEvent) const;`
- L325 _private prototype_ `FCocoaWindow* FindSlateWindowUnderCursor() const;`
- L326 _private prototype_ `EWindowZone::Type GetCurrentWindowZone(const TSharedRef<FMacWindow>& Window) const;`
- L327 _private prototype_ `bool IsEdgeZone(EWindowZone::Type Zone) const;`
- L328 _private prototype_ `bool IsPrintableKey(uint32 Character) const;`
- L329 _private prototype_ `TCHAR ConvertChar(TCHAR Character) const;`
- L330 _private prototype_ `TCHAR TranslateCharCode(TCHAR CharCode, uint32 KeyCode) const;`
- L332 _private prototype_ `void CloseQueuedWindows();`
- L335 _private prototype_ `void InvalidateTextLayouts();` — Invalidates all queued windows requiring text layout changes
- L338 _private prototype_ `void RecordUsage(EGestureEvent Gesture);`
- L340 _private function_ `void RecordUsage(EGestureEvent Gesture)`
- L344 _private prototype_ `void OnAccessibleEventRaised(const FAccessibleEventArgs& Args);`
- L347 _private prototype_ `void OnInputDeviceModuleRegistered(const FName& Type, IModularFeature* ModularFeature);`
- L351 _private member_ `bool bUsingHighPrecisionMouseInput;`
- L353 _private member_ `bool bUsingTrackpad;`
- L355 _private member_ `EMouseButtons::Type LastPressedMouseButton;`
- L357 _private member_ `FCriticalSection EventsMutex;`
- L358 _private member_ `TArray<FDeferredMacEvent> DeferredEvents;`
- L360 _private member_ `FCriticalSection WindowsMutex;`
- L361 _private member_ `TArray<TSharedRef<FMacWindow>> Windows;`
- L363 _private member_ `bool bIsProcessingDeferredEvents;`
- L371 _private member_ `TArray<FSavedWindowOrderInfo> SavedWindowsOrder;`
- L373 _private member_ `TSharedRef<class FMacControllerInterface> HIDInput;`
- L375 _private member_ `TSharedPtr<FAppleMouseController> MouseController;`
- L377 _private prototype_ `void HandleMouseControllerMovement(FIntVector2 Delta);`
- L380 _private member_ `TArray<TSharedPtr<class IInputDevice>> ExternalInputDevices;` — List of input devices implemented in external modules.
- L381 _private member_ `bool bHasLoadedInputPlugins;`
- L383 _private member_ `FCocoaWindow* DraggedWindow;`
- L384 _private member_ `FCocoaWindow* WindowUnderCursor;`
- L386 _private member_ `TSharedPtr<FMacWindow> ActiveWindow;`
- L387 _private member_ `uint32 SystemResolutionX;`
- L388 _private member_ `uint32 SystemResolutionY;`
- L390 _private member_ `bool bSystemModalMode;`
- L393 _private member_ `uint32 ModifierKeysFlags;` — The current set of modifier keys that are pressed. This is used to detect differences between left and right modifier keys on key up events
- L396 _private member_ `NSUInteger CurrentModifierFlags;` — The current set of Cocoa modifier flags, used to detect when Mission Control has been invoked & returned so that we can synthesis the modifier events it steals
- L398 _private member_ `bool bIsRightClickEmulationEnabled;`
- L399 _private member_ `bool bEmulatingRightClick;`
- L401 _private member_ `volatile int32 bIgnoreMouseMoveDelta;`
- L402 _private member_ `std::atomic<bool> bMouseInputNeedsReassociation;`
- L404 _private member_ `FCriticalSection WindowsToCloseMutex;`
- L405 _private member_ `TArray<FCocoaWindow*> CocoaWindowsToClose;`
- L406 _private member_ `TArray<TSharedRef<FMacWindow>> SlateWindowsToClose;`
- L408 _private member_ `TArray<FCocoaWindow*> WindowsRequiringTextInvalidation;`
- L410 _private member_ `TSharedPtr<FMacTextInputMethodSystem> TextInputMethodSystem;`
- L412 _private member_ `bool bIsWorkspaceSessionActive;`
- L415 _private member_ `id AppActivationObserver;` — Notification center observers
- L416 _private member_ `id AppDeactivationObserver;`
- L417 _private member_ `id WorkspaceActivationObserver;`
- L418 _private member_ `id WorkspaceDeactivationObserver;`
- L419 _private member_ `id WorkspaceActiveSpaceChangeObserver;`
- L420 _private member_ `id ScreensDidWakeObserver;`
- L421 _private member_ `id SystemDidWakeObserver;`
- L423 _private member_ `id EventMonitor;`
- L424 _private member_ `id MouseMovedEventMonitor;`
- L428 _private member_ `EGestureEvent LastGestureUsed;` — Holds the last gesture used to try and capture unique uses for gestures.
- L431 _private member_ `int32 GestureUsage[(int32)EGestureEvent::Count];` — Stores the number of times a gesture has been used for analytics
- L434 _private member_ `NSData* KeyBoardLayoutData;`
- L438 _private member_ `NSTimer* AccessibilityCacheTimer;` — Timer used to refresh the accessibility cache
- L440 _private member_ `NSTimer* AccessibilityAnnouncementDelayTimer;`
- L443 _private member_ `NSEvent* LastNativeEvent;`
- L445 _private member_ `bool bDisplayReconfiguring;`

#### struct `FMacApplication::FSavedWindowOrderInfo`  
`struct FSavedWindowOrderInfo`  
_L365-370_
- L367 _public member_ `int32 WindowNumber;`
- L368 _public member_ `int32 Level;`
- L369 _public function_ `FSavedWindowOrderInfo(int32 InWindowNumber, int32 InLevel) : WindowNumber(InWindowNumber), Level(InLevel)`

#### Free symbols / members of external scopes

- L135 _typedef_ `typedef TSharedRef<FMacScreen, ESPMode::ThreadSafe> FMacScreenRef;`
- L450 _externvar_ `extern FMacApplication* MacApplication;`

### `Source/Runtime/ApplicationCore/Public/Mac/MacApplicationErrorOutputDevice.h` (Public)


#### class `FMacApplicationErrorOutputDevice`  
`class FMacApplicationErrorOutputDevice : public FMacErrorOutputDevice`  
_L8-12_
- inherits: `FMacErrorOutputDevice`
- L11 _protected prototype_ `virtual void HandleErrorRestoreUI() override;`

### `Source/Runtime/ApplicationCore/Public/Mac/MacConsoleOutputDevice.h` (Public)


#### class `FMacConsoleOutputDevice`  
`class FMacConsoleOutputDevice : public FOutputDeviceConsole`  
_L15-90_
- inherits: `FOutputDeviceConsole`
- desc: Mac implementation of console log window, utilizing the Win32 console API
- L19 _private member_ `FMacConsoleWindow* ConsoleHandle;` — Handle to the console log window
- L22 _private member_ `NSTextView* TextView;` — Handle to window's content view
- L25 _private member_ `NSScrollView* ScrollView;` — Handle to window's scroll view
- L28 _private member_ `NSDictionary* TextViewTextColor;` — Handle text color of TextView
- L31 _private member_ `FCriticalSection CriticalSection;` — Critical section for Serialize()
- L34 _private member_ `uint64 OutstandingTasks;` — Number of outstanding dispatched Cocoa tasks
- L37 _private member_ `ELogVerbosity::Type AllowedLogVerbosity = ELogVerbosity::All;` — Maximum allowed log verbosity
- L42 _private prototype_ `void SaveToINI();` — Saves the console window's position and size to the game .ini
- L47 _private prototype_ `void CreateConsole();` — Creates console window
- L52 _private prototype_ `void DestroyConsole();` — Destroys console window
- L57 _private prototype_ `void SetDefaultTextColor();`
- L64 _public prototype_ `FMacConsoleOutputDevice();` — Constructor, setting console control handler.
- L65 _public prototype_ `~FMacConsoleOutputDevice();`
- L72 _public prototype_ `virtual void Show( bool ShowWindow );` — Shows or hides the console window. @param ShowWindow	Whether to show (true) or hide (false) the console window.
- L79 _public prototype_ `virtual bool IsShown();` — Returns whether console is currently shown or not @return true if console is shown, false otherwise
- L81 _public function_ `virtual bool IsAttached()`
- L89 _public prototype_ `void Serialize( const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category );` — Displays text on the console and scrolls if necessary. @param Data	Text to display @param Event	Event type, used for filtering/ suppression

### `Source/Runtime/ApplicationCore/Public/Mac/MacCursor.h` (Public)


#### class `FMacCursor`  
`class FMacCursor : public ICursor`  
_L12-83_
- inherits: `ICursor`
- L16 _public prototype_ `FMacCursor();`
- L18 _public prototype_ `virtual ~FMacCursor();`
- L20 _public prototype_ `virtual void* CreateCursorFromFile(const FString& InPathToCursorWithoutExtension, FVector2D HotSpot) override;`
- L22 _public function_ `virtual bool IsCreateCursorFromRGBABufferSupported() const override`
- L24 _public prototype_ `virtual void* CreateCursorFromRGBABuffer(const FColor* Pixels, int32 Width, int32 Height, FVector2D InHotSpot) override;`
- L26 _public prototype_ `virtual FVector2D GetPosition() const override;`
- L28 _public prototype_ `virtual void SetPosition(const int32 X, const int32 Y) override;`
- L30 _public prototype_ `virtual void SetType(const EMouseCursor::Type InNewCursor) override;`
- L32 _public function_ `virtual EMouseCursor::Type GetType() const override`
- L34 _public prototype_ `virtual void GetSize(int32& Width, int32& Height) const override;`
- L36 _public prototype_ `virtual void Show(bool bShow) override;`
- L38 _public prototype_ `virtual void Lock(const RECT* const Bounds) override;`
- L40 _public prototype_ `virtual void SetTypeShape(EMouseCursor::Type InCursorType, void* CursorHandle) override;`
- L44 _public prototype_ `bool UpdateCursorClipping(FIntVector2& CursorPosition);`
- L46 _public prototype_ `void WarpCursor(const int32 X, const int32 Y);`
- L48 _public prototype_ `FIntVector2 GetIntPosition() const;`
- L50 _public prototype_ `FIntVector2 GetMouseWarpDelta();`
- L52 _public prototype_ `void SetHighPrecisionMouseMode(const bool bEnable);`
- L54 _public prototype_ `void UpdateCurrentPosition(const FIntVector2& Position);`
- L56 _public prototype_ `void UpdateVisibility();`
- L58 _public function_ `bool IsLocked() const`
- L60 _public function_ `void SetShouldIgnoreLocking(bool bIgnore)`
- L64 _private member_ `EMouseCursor::Type CurrentType;`
- L66 _private member_ `NSCursor* CursorHandles[EMouseCursor::TotalCursorCount];`
- L67 _private member_ `NSCursor* CursorOverrideHandles[EMouseCursor::TotalCursorCount];`
- L69 _private member_ `FIntRect CursorClipRect;`
- L71 _private member_ `bool bIsVisible;`
- L72 _private member_ `bool bUseHighPrecisionMode;`
- L73 _private member_ `NSCursor* CurrentCursor;`
- L74 _private member_ `int32 CursorTypeOverride;`
- L76 _private member_ `FIntVector2 CurrentPosition;`
- L77 _private member_ `FIntVector2 MouseWarpDelta;`
- L78 _private member_ `bool bIsPositionInitialised;`
- L79 _private member_ `bool bShouldIgnoreLocking;`
- L81 _private member_ `io_object_t HIDInterface;`
- L82 _private member_ `double SavedAcceleration;`

### `Source/Runtime/ApplicationCore/Public/Mac/MacFeedbackContext.h` (Public)


#### class `FMacFeedbackContext`  
`class FMacFeedbackContext : public FFeedbackContext`  
_L14-27_
- inherits: `FFeedbackContext`
- desc: Feedback context implementation for Mac.
- L17 _private member_ `FContextSupplier* Context = nullptr;` — Context information for warning and error messages
- L20 _public function_ `bool YesNof(const FText& Question) override`
- L25 _public function_ `FContextSupplier* GetContext() const override`
- L26 _public function_ `void SetContext(FContextSupplier* InContext) override`

### `Source/Runtime/ApplicationCore/Public/Mac/MacPlatformApplicationMisc.h` (Public)


#### struct `FMacPlatformApplicationMisc`  
`struct FMacPlatformApplicationMisc : public FGenericPlatformApplicationMisc`  
_L14-64_
- inherits: `FGenericPlatformApplicationMisc`
- L16 _public prototype_ `static void PreInit();`
- L17 _public prototype_ `static void PostInit();`
- L18 _public prototype_ `static void TearDown();`
- L19 _public prototype_ `static void LoadPreInitModules();`
- L20 _public prototype_ `static class FOutputDeviceConsole* CreateConsoleOutputDevice();`
- L21 _public prototype_ `static class FOutputDeviceError* GetErrorOutputDevice();`
- L22 _public prototype_ `static class FFeedbackContext* GetFeedbackContext();`
- L23 _public prototype_ `static class GenericApplication* CreateApplication();`
- L24 _public prototype_ `static void RequestMinimize();`
- L25 _public prototype_ `static bool IsThisApplicationForeground();`
- L26 _public prototype_ `static bool IsScreensaverEnabled();`
- L27 _public prototype_ `static bool ControlScreensaver(EScreenSaverAction Action);`
- L28 _public prototype_ `static void ActivateApplication();`
- L29 _public prototype_ `static void UpdateApplicationMenu();`
- L30 _public prototype_ `static void LanguageChanged();`
- L31 _public prototype_ `static void UpdateWindowMenu();`
- L32 _public prototype_ `static void UpdateCocoaWindows();`
- L33 _public prototype_ `static struct FLinearColor GetScreenPixelColor(const FVector2D& InScreenPos, float InGamma = 1.0f);`
- L34 _public prototype_ `static float GetDPIScaleFactorAtPoint(float X, float Y);`
- L35 _public function_ `static bool IsHighDPIModeEnabled()`
- L36 _public prototype_ `static void PumpMessages(bool bFromMainLoop);`
- L37 _public prototype_ `static void ClipboardCopy(const TCHAR* Str);`
- L38 _public prototype_ `static void ClipboardPaste(class FString& Dest);`
- L40 _public prototype_ `static void* GetActiveWindowPtr();`
- L43 _public prototype_ `static void ProcessAsyncTasks();` — MAC ONLY
- L44 _public prototype_ `static bool IsMainThread();`
- L46 _public member_ `static MacApplicationExternalCb UpdateCachedMacMenuStateCb;`
- L47 _public member_ `static MacApplicationExternalCb PostInitMacMenuStartupCb;`
- L48 _public member_ `static MacApplicationExternalCbOneBool UpdateApplicationMenuCb;`
- L49 _public member_ `static MacApplicationExternalCbOneBool UpdateWindowMenuCb;`
- L50 _public member_ `static MacApplicationExternalCb LanguageChangedCb;`
- L52 _public member_ `static bool bChachedMacMenuStateNeedsUpdate;`
- L54 _public member_ `static bool bLanguageChanged;`
- L56 _public member_ `static bool bMacApplicationModalMode;`
- L58 _public member_ `static bool bIsHighResolutionCapable;`
- L60 _public member_ `static id<NSObject> CommandletActivity;`
- L63 _private member_ `static bool bDisplaySleepEnabled;`

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef void (*MacApplicationExternalCb)(void);`
- L12 _typedef_ `typedef void (*MacApplicationExternalCbOneBool)(bool);`
- L66 _typedef_ `typedef FMacPlatformApplicationMisc FPlatformApplicationMisc;`

### `Source/Runtime/ApplicationCore/Public/Mac/MacPlatformFramePacer.h` (Public)


#### struct `FMacPlatformRHIFramePacer`  
`struct FMacPlatformRHIFramePacer : public FGenericPlatformRHIFramePacer`  
_L19-31_
- inherits: `FGenericPlatformRHIFramePacer`
- desc: Mac implementation of FGenericPlatformRHIFramePacer
- L22 _public prototype_ `static bool IsEnabled();` — FGenericPlatformRHIFramePacer interface
- L23 _public prototype_ `static void InitWithEvent(class FEvent* TriggeredEvent);`
- L24 _public prototype_ `static void AddHandler(FMacFramePacerHandler Handler);`
- L25 _public prototype_ `static void AddEvent(uint32 CGDirectDisplayID, class FEvent* TriggeredEvent);`
- L26 _public prototype_ `static void RemoveHandler(FMacFramePacerHandler Handler);`
- L27 _public prototype_ `static void Destroy();`
- L30 _public member_ `static FMacFramePacer* FramePacer;` — Access to the Mac Frame Pacer: CVDisplayLink

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef void (^FMacFramePacerHandler)(uint32 CGDirectDisplayID, double OutputSeconds, double OutputDuration);`
- L34 _typedef_ `typedef FMacPlatformRHIFramePacer FPlatformRHIFramePacer;`
- L35 _typedef_ `typedef FMacFramePacerHandler FPlatformRHIFramePacerHandler;`

### `Source/Runtime/ApplicationCore/Public/Mac/MacPlatformSplash.h` (Public)


#### struct `FMacPlatformSplash`  
`struct FMacPlatformSplash : public FGenericPlatformSplash`  
_L12-36_
- inherits: `FGenericPlatformSplash`
- desc: Mac splash implementation
- L17 _public prototype_ `static void Show();` — Show the splash screen
- L21 _public prototype_ `static void Hide();` — Hide the splash screen
- L30 _public prototype_ `static void SetSplashText( const SplashTextType::Type InType, const FText& InText );`
- L35 _public prototype_ `static bool IsShown();` — Return whether the splash screen is being shown or not

#### Free symbols / members of external scopes

- L38 _typedef_ `typedef FMacPlatformSplash FPlatformSplash;`

### `Source/Runtime/ApplicationCore/Public/Mac/MacPlatformSurvey.h` (Public)


#### struct `FMacPlatformSurvey`  
`struct FMacPlatformSurvey : public FGenericPlatformSurvey`  
_L16-26_
- inherits: `FGenericPlatformSurvey`
- desc: Mac implementation of FGenericPlatformSurvey
- L19 _public prototype_ `static bool GetSurveyResults( FHardwareSurveyResults& OutResults, bool bWait = false );` — Start, or check on, the hardware survey
- L25 _private prototype_ `static void WriteFStringToResults(TCHAR* OutBuffer, const FString& InString);` — Safely write strings into the fixed length TCHAR buffers of a FHardwareSurveyResults member

#### Free symbols / members of external scopes

- L28 _typedef_ `typedef FMacPlatformSurvey FPlatformSurvey;`

### `Source/Runtime/ApplicationCore/Public/Mac/MacProgramDelegate.h` (Public)


#### Free symbols / members of external scopes

- L8 _typedef_ `using ProgramMainType=int32(*)(const TCHAR *);`
- L9 _typedef_ `using ProgramExitType=void(*)();`
- L14 _variable_ `ProgramMainType ProgramMain;` — the main function for the program (shared with other platforms)
- L17 _variable_ `ProgramExitType ProgramExit;` — the function to run at exit time, on the game thread (very probagly FEngineLoop::Exit)
- L20 _variable_ `FString SavedCommandLine;` — the commandline made from argv, but a subclass could modify it

### `Source/Runtime/ApplicationCore/Public/Mac/MacTextInputMethodSystem.h` (Public)


#### class `FMacTextInputMethodSystem`  
`class FMacTextInputMethodSystem : public ITextInputMethodSystem`  
_L7-25_
- inherits: `ITextInputMethodSystem`
- L10 _public function_ `virtual ~FMacTextInputMethodSystem()`
- L11 _public prototype_ `bool Initialize();`
- L12 _public prototype_ `void Terminate();`
- L15 _public prototype_ `virtual void ApplyDefaults(const TSharedRef<FGenericWindow>& InWindow) override;` — ITextInputMethodSystem Interface Begin
- L16 _public prototype_ `virtual TSharedPtr<ITextInputMethodChangeNotifier> RegisterContext(const TSharedRef<ITextInputMethodContext>& Context) override;`
- L17 _public prototype_ `virtual void UnregisterContext(const TSharedRef<ITextInputMethodContext>& Context) override;`
- L18 _public prototype_ `virtual void ActivateContext(const TSharedRef<ITextInputMethodContext>& Context) override;`
- L19 _public prototype_ `virtual void DeactivateContext(const TSharedRef<ITextInputMethodContext>& Context) override;`
- L20 _public prototype_ `virtual bool IsActiveContext(const TSharedRef<ITextInputMethodContext>& Context) const override;`
- L24 _private member_ `TMap< TWeakPtr<ITextInputMethodContext>, TWeakPtr<ITextInputMethodChangeNotifier> > ContextMap;`

### `Source/Runtime/ApplicationCore/Public/Mac/MacWindow.h` (Public)


#### class `FMacWindow`  
`class FMacWindow : public FGenericWindow, public TSharedFromThis<FMacWindow>`  
_L13-126_
- inherits: `FGenericWindow,TSharedFromThis<FMacWindow>`
- desc: A platform specific implementation of FGenericWindow. Native Windows provide platform-specific backing for and are always owned by an SWindow.
- L16 _public prototype_ `~FMacWindow();`
- L18 _public prototype_ `static TSharedRef< FMacWindow > Make();`
- L20 _public prototype_ `FCocoaWindow* GetWindowHandle() const;`
- L22 _public prototype_ `void Initialize( class FMacApplication* const Application, const TSharedRef< FGenericWindowDefinition >& InDefinition, const TSharedPtr< FMacWindow >& InParent, const bool bShowImmediately );`
- L24 _public prototype_ `void OnDisplayReconfiguration(CGDirectDisplayID Display, CGDisplayChangeSummaryFlags Flags);`
- L26 _public prototype_ `void OnWindowDidChangeScreen();`
- L30 _public prototype_ `virtual void ReshapeWindow( int32 X, int32 Y, int32 Width, int32 Height ) override;`
- L32 _public prototype_ `virtual bool GetFullScreenInfo( int32& X, int32& Y, int32& Width, int32& Height ) const override;`
- L34 _public prototype_ `virtual void MoveWindowTo ( int32 X, int32 Y ) override;`
- L36 _public prototype_ `virtual void BringToFront( bool bForce = false ) override;`
- L38 _public prototype_ `virtual void Destroy() override;`
- L40 _public prototype_ `virtual void Minimize() override;`
- L42 _public prototype_ `virtual void Maximize() override;`
- L44 _public prototype_ `virtual void Restore() override;`
- L46 _public prototype_ `virtual void Show() override;`
- L48 _public prototype_ `virtual void Hide() override;`
- L50 _public prototype_ `virtual void SetWindowMode( EWindowMode::Type NewWindowMode ) override;`
- L52 _public prototype_ `virtual EWindowMode::Type GetWindowMode() const override;`
- L54 _public prototype_ `virtual bool IsMaximized() const override;`
- L56 _public prototype_ `virtual bool IsMinimized() const override;`
- L58 _public prototype_ `virtual bool IsVisible() const override;`
- L60 _public prototype_ `virtual bool GetRestoredDimensions(int32& X, int32& Y, int32& Width, int32& Height) override;`
- L62 _public prototype_ `virtual void SetWindowFocus() override;`
- L64 _public prototype_ `virtual void SetOpacity( const float InOpacity ) override;`
- L66 _public prototype_ `virtual bool IsPointInWindow( int32 X, int32 Y ) const override;`
- L68 _public prototype_ `virtual int32 GetWindowBorderSize() const override;`
- L70 _public function_ `virtual void* GetOSWindowHandle() const override`
- L72 _public prototype_ `virtual bool IsForegroundWindow() const override;`
- L74 _public prototype_ `virtual void SetText(const TCHAR* const Text) override;`
- L76 _public prototype_ `virtual float GetDPIScaleFactor() const override;`
- L78 _public prototype_ `virtual void SetNativeWindowButtonsVisibility(bool bVisible);`
- L80 _public prototype_ `bool IsRegularWindow() const;`
- L82 _public member_ `int32 PositionX;`
- L83 _public member_ `int32 PositionY;`
- L91 _private prototype_ `FMacWindow();` — Protect the constructor; only TSharedRefs of this class can be made.
- L93 _private function_ `const CGDirectDisplayID GetDisplayID() const`
- L95 _private prototype_ `void ApplySizeAndModeChanges(int32 X, int32 Y, int32 Width, int32 Height, EWindowMode::Type WindowMode);`
- L96 _private prototype_ `void UpdateFullScreenState(bool bToggleFullScreen);`
- L97 _private prototype_ `void WaitForFullScreenTransition();`
- L101 _private member_ `FMacApplication* OwningApplication;`
- L104 _private member_ `FCocoaWindow* WindowHandle;` — Mac window handle
- L106 _private member_ `CGDirectDisplayID DisplayID;`
- L108 _private member_ `float CachedOpacity;`
- L117 _private member_ `} WindowedModeSavedState;`
- L119 _private member_ `bool bIsVisible : 1;`
- L120 _private member_ `bool bIsClosed : 1;`
- L123 _private member_ `bool bIsFirstTimeVisible : 1;` — Whether the window is yet to have its first Show() call. This is set false after first Show().
- L125 _private member_ `bool bIsMainEditorWindow : 1;`

#### struct `FMacWindow::FWindowedModeSavedState`  
`struct FWindowedModeSavedState`  
_L110-117_
- L112 _public member_ `CGDirectDisplayID CapturedDisplayID;`
- L113 _public member_ `CGDisplayModeRef DesktopDisplayMode;`
- L114 _public member_ `int32 WindowLevel;`
- L116 _public function_ `FWindowedModeSavedState() : CapturedDisplayID(kCGNullDirectDisplay), DesktopDisplayMode(nullptr), WindowLevel(NSNormalWindowLevel)`

### `Source/Runtime/ApplicationCore/Public/Null/NullApplication.h` (Public)


#### struct `FNullPlatformDisplayMetrics`  
`struct FNullPlatformDisplayMetrics : public FDisplayMetrics`  
_L25-28_
- inherits: `FDisplayMetrics`
- L27 _public prototype_ `static void RebuildDisplayMetrics(struct FDisplayMetrics& OutDisplayMetrics);`

#### class `FNullApplication`  
`class FNullApplication : public GenericApplication, public FSelfRegisteringExec, public IInputInterface`  
_L34-150_
- inherits: `GenericApplication,FSelfRegisteringExec,IInputInterface`
- desc: An implementation of GenericApplication specifically for use when rendering off screen. This application has no platform backing so instead keeps track of its associated NullWindows itself.
- L37 _public prototype_ `static FNullApplication* CreateNullApplication();`
- L39 _public prototype_ `static void MoveWindowTo(FGenericWindow* Window, const int32 X, const int32 Y);`
- L41 _public prototype_ `static void OnSizeChanged(FGenericWindow* Window, const int32 Width, const int32 Height);`
- L43 _public prototype_ `static void GetFullscreenInfo(int32& X, int32& Y, int32& Width, int32& Height);`
- L45 _public prototype_ `static void ShowWindow(FGenericWindow* Window);`
- L47 _public prototype_ `static void HideWindow(FGenericWindow* Window);`
- L49 _public prototype_ `static void DestroyWindow(FGenericWindow* Window);`
- L52 _public prototype_ `virtual ~FNullApplication();`
- L54 _public prototype_ `virtual void DestroyApplication() override;`
- L57 _public prototype_ `virtual bool Exec_Dev(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — FSelfRegisteringExec
- L59 _public prototype_ `TSharedPtr<FNullWindow> FindWindowByPtr(FGenericWindow* WindowToFind);`
- L61 _public prototype_ `void ActivateWindow(const TSharedPtr<FNullWindow>& Window);`
- L64 _public prototype_ `virtual void SetMessageHandler(const TSharedRef<class FGenericApplicationMessageHandler>& InMessageHandler) override;`
- L66 _public prototype_ `virtual void PollGameDeviceState(const float TimeDelta) override;`
- L68 _public prototype_ `virtual void PumpMessages(const float TimeDelta) override;`
- L70 _public prototype_ `virtual void ProcessDeferredEvents(const float TimeDelta) override;`
- L72 _public prototype_ `virtual TSharedRef<FGenericWindow> MakeWindow() override;`
- L74 _public prototype_ `virtual void InitializeWindow(const TSharedRef<FGenericWindow>& Window, const TSharedRef<FGenericWindowDefinition>& InDefinition, const TSharedPtr<FGenericWindow>& InParent, const bool bShowImmediately) override;`
- L76 _public prototype_ `void DestroyWindow(TSharedRef<FNullWindow> WindowToRemove);`
- L78 _public prototype_ `virtual void SetCapture(const TSharedPtr<FGenericWindow>& InWindow) override;`
- L80 _public prototype_ `virtual void* GetCapture(void) const override;`
- L82 _public prototype_ `virtual void SetHighPrecisionMouseMode(const bool Enable, const TSharedPtr<FGenericWindow>& InWindow) override;`
- L84 _public function_ `virtual bool IsUsingHighPrecisionMouseMode() const override`
- L86 _public prototype_ `virtual bool IsGamepadAttached() const override;`
- L88 _public prototype_ `virtual FModifierKeysState GetModifierKeys() const override;`
- L90 _public prototype_ `virtual FPlatformRect GetWorkArea(const FPlatformRect& CurrentWindow) const override;`
- L92 _public prototype_ `void SetWorkArea(const FPlatformRect& NewWorkArea);`
- L94 _public function_ `virtual EWindowTransparency GetWindowTransparencySupport() const override`
- L99 _public prototype_ `virtual bool IsCursorDirectlyOverSlateWindow() const override;`
- L101 _public prototype_ `virtual TSharedPtr<FGenericWindow> GetWindowUnderCursor() override;`
- L103 _public function_ `virtual bool IsMouseAttached() const override`
- L106 _private prototype_ `FNullApplication();`
- L109 _private prototype_ `bool HandleCursorCommand(const TCHAR* Cmd, FOutputDevice& Ar);` — Handles "Cursor" exec commands"
- L112 _private prototype_ `bool HandleWindowCommand(const TCHAR* Cmd, FOutputDevice& Ar);` — Handles "Window" exec commands"
- L115 _private prototype_ `bool ParseResolution(const TCHAR* InResolution, uint32& OutX, uint32& OutY);` — Handles parsing the work area resolution from the command line
- L117 _private prototype_ `void OnInputDeviceModuleRegistered(const FName& Type, IModularFeature* ModularFeature);`
- L120 _public function_ `virtual IInputInterface* GetInputInterface() override`
- L126 _public prototype_ `virtual void SetForceFeedbackChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;` — IInputInterface overrides
- L127 _public prototype_ `virtual void SetForceFeedbackChannelValues(int32 ControllerId, const FForceFeedbackValues& Values) override;`
- L128 _public prototype_ `virtual void SetHapticFeedbackValues(int32 ControllerId, int32 Hand, const FHapticFeedbackValues& Values) override;`
- L129 _public function_ `virtual void SetLightColor(int32 ControllerId, FColor Color) override`
- L130 _public function_ `virtual void ResetLightColor(int32 ControllerId) override`
- L133 _private member_ `TArray<TSharedRef<FNullWindow>> Windows;`
- L136 _private member_ `TArray<TSharedPtr<class IInputDevice>> ExternalInputDevices;` — List of input devices implemented in external modules.
- L137 _private member_ `bool bHasLoadedInputPlugins;`
- L140 _private member_ `bool bUsingHighPrecisionMouseInput;` — Using high precision mouse input
- L143 _private member_ `TSharedPtr<FNullWindow> CurrentlyActiveWindow;` — Window that we think has been activated last.
- L146 _private member_ `TSharedPtr<FNullWindow> PreviousActiveWindow;` — Window that we think has been previously active.
- L149 _private member_ `FPlatformRect WorkArea;` — The virtual work area

#### Free symbols / members of external scopes

- L152 _externvar_ `extern FNullApplication* NullApplication;`

### `Source/Runtime/ApplicationCore/Public/Null/NullCursor.h` (Public)


#### class `FNullCursor`  
`class FNullCursor : public ICursor`  
_L13-60_
- inherits: `ICursor`
- desc: An implementation of an ICursor specifically for use when rendering off screen. This cursor has no platform backing so instead keeps track of its position and other properties itself.
- L16 _public prototype_ `FNullCursor();`
- L18 _public prototype_ `virtual ~FNullCursor();`
- L21 _public prototype_ `virtual FVector2D GetPosition() const override;` — The position of the cursor
- L24 _public prototype_ `virtual void SetPosition(const int32 X, const int32 Y) override;` — Sets the position of the cursor
- L27 _public prototype_ `virtual void SetType(const EMouseCursor::Type InNewCursor) override;` — Sets the cursor
- L30 _public prototype_ `virtual EMouseCursor::Type GetType() const override;` — Gets the current type of the cursor
- L33 _public prototype_ `virtual void GetSize(int32& Width, int32& Height) const override;` — Gets the size of the cursor
- L40 _public prototype_ `virtual void Show(bool bShow) override;` — Shows or hides the cursor @param bShow	true to show the mouse cursor, false to hide it
- L47 _public prototype_ `virtual void Lock(const RECT* const Bounds) override;` — Locks the cursor to the passed in bounds @param Bounds	The bounds to lock the cursor to.  Pass NULL to unlock.
- L52 _public prototype_ `virtual void SetTypeShape(EMouseCursor::Type InCursorType, void* CursorHandle) override;` — Allows overriding the shape of a particular cursor.
- L56 _private member_ `int32 CachedGlobalXPosition;` — Cached global X position
- L59 _private member_ `int32 CachedGlobalYPosition;` — Cached global Y position

### `Source/Runtime/ApplicationCore/Public/Null/NullPlatformApplicationMisc.h` (Public)


#### struct `FNullPlatformApplicationMisc`  
`struct FNullPlatformApplicationMisc : public FGenericPlatformApplicationMisc`  
_L7-12_
- inherits: `FGenericPlatformApplicationMisc`
- L9 _public prototype_ `static class GenericApplication* CreateApplication();`
- L11 _public prototype_ `static bool IsUsingNullApplication();`

### `Source/Runtime/ApplicationCore/Public/Null/NullWindow.h` (Public)


#### class `FNullWindow`  
`class FNullWindow : public FGenericWindow`  
_L22-191_
- inherits: `FGenericWindow`
- desc: An implementation of FGenericWindow specifically for use when rendering off screen. This window has no platform backing so instead keeps track of its position and other properties itself.
- L25 _public prototype_ `static TSharedRef<FNullWindow> Make();`
- L27 _public prototype_ `virtual ~FNullWindow();`
- L29 _public prototype_ `void Initialize(class FNullApplication* const Application, const TSharedRef<FGenericWindowDefinition>& InDefinition, const TSharedPtr<FNullWindow>& InParent, const bool bShowImmediately);`
- L32 _public prototype_ `virtual void ReshapeWindow(int32 X, int32 Y, int32 Width, int32 Height) override;` — Native windows should implement ReshapeWindow by changing the platform-specific window to be located at (X,Y) and be the dimensions Width x Height.
- L35 _public prototype_ `virtual bool GetFullScreenInfo(int32& X, int32& Y, int32& Width, int32& Height) const override;` — Returns the rectangle of the screen the window is associated with
- L38 _public prototype_ `virtual void MoveWindowTo(int32 X, int32 Y) override;` — Native windows should implement MoveWindowTo by relocating the platform-specific window to (X,Y).
- L41 _public prototype_ `virtual void BringToFront(bool bForce = false) override;` — Native windows should implement BringToFront by making this window the top-most window (i.e. focused).
- L44 _public prototype_ `virtual void HACK_ForceToFront() override;` — @hack Force a window to front even if a different application is in front.
- L47 _public prototype_ `virtual void Destroy() override;` — Native windows should implement this function by asking the OS to destroy OS-specific resource associated with the window (e.g. Win32 window handle)
- L50 _public prototype_ `virtual void Minimize() override;` — Native window should implement this function by performing the equivalent of the Win32 minimize-to-taskbar operation
- L53 _public prototype_ `virtual void Maximize() override;` — Native window should implement this function by performing the equivalent of the Win32 maximize operation
- L56 _public prototype_ `virtual void Restore() override;` — Native window should implement this function by performing the equivalent of the Win32 restore operation
- L59 _public prototype_ `virtual void Show() override;` — Native window should make itself visible
- L62 _public prototype_ `virtual void Hide() override;` — Native window should hide itself
- L65 _public prototype_ `virtual void SetWindowMode(EWindowMode::Type InNewWindowMode) override;` — Toggle native window between fullscreen and normal mode
- L68 _public prototype_ `virtual EWindowMode::Type GetWindowMode() const override;` — @return true if the native window is currently in fullscreen mode, false otherwise
- L71 _public prototype_ `virtual bool IsMaximized() const override;` — @return true if the native window is maximized, false otherwise
- L74 _public prototype_ `virtual bool IsMinimized() const override;` — @return true if the native window is minimized, false otherwise
- L77 _public prototype_ `virtual bool IsVisible() const override;` — @return true if the native window is visible, false otherwise
- L85 _public prototype_ `virtual bool GetRestoredDimensions(int32& X, int32& Y, int32& Width, int32& Height) override;` — Populates the size and location of the window when it is restored. If the function fails, false is returned and X,Y,Width,Height will be undefined. @return true when the size and location and successfully retrieved; false otherwise.
- L91 _public prototype_ `virtual void SetWindowFocus() override;` — Native windows should implement SetWindowFocus to let the OS know that a window has taken focus. Slate handles focus on a per widget basis internally but the OS still needs to know what window has focus for proper message routing
- L98 _public prototype_ `virtual void SetOpacity(const float InOpacity) override;` — Sets the opacity of this window @param	InOpacity	The new window opacity represented as a floating point scalar
- L105 _public prototype_ `virtual void Enable(bool bEnable) override;` — Enables or disables the window.  If disabled the window receives no input @param bEnable	true to enable the window, false to disable it.
- L108 _public prototype_ `virtual bool IsPointInWindow(int32 X, int32 Y) const override;` — @return true if native window exists underneath the coordinates
- L111 _public prototype_ `virtual int32 GetWindowBorderSize() const override;` — Gets OS specific window border size. This is necessary because Win32 does not give control over this size.
- L114 _public prototype_ `virtual int32 GetWindowTitleBarSize() const override;` — Gets OS specific window title bar size
- L117 _public prototype_ `virtual void* GetOSWindowHandle() const override;` — Gets the OS Window handle in the form of a void pointer for other API's
- L120 _public prototype_ `virtual bool IsForegroundWindow() const override;` — @return true if the window is in the foreground
- L123 _public prototype_ `virtual bool IsFullscreenSupported() const override;` — @return true if the window is in the foreground
- L130 _public prototype_ `virtual void SetText(const TCHAR* const Text) override;` — Sets the window text - usually the title but can also be text content for things like controls @param Text	The window's title or content text
- L133 _public prototype_ `virtual const FGenericWindowDefinition& GetDefinition() const override;` — @return	The definition describing properties of the window
- L136 _public prototype_ `virtual bool IsDefinitionValid() const override;` — @return	Returns true if the window definition is valid
- L139 _public prototype_ `virtual void AdjustCachedSize(FVector2D& Size) const override;` — @return	Gives the native window a chance to adjust our stored window size before we cache it off
- L141 _public function_ `virtual float GetDPIScaleFactor() const override`
- L146 _public function_ `virtual void SetDPIScaleFactor(float Value) override`
- L152 _public prototype_ `virtual bool IsManualManageDPIChanges() const override;` — determines whether or not this window does its own DPI management
- L155 _public prototype_ `virtual void SetManualManageDPIChanges(const bool bAutoHandle) override;` — call with a true argument if this window need to do its custom size management in response to DPI variations
- L165 _public prototype_ `virtual void DrawAttention(const FWindowDrawAttentionParameters& Parameters) override;` — Attempts to draw the user's attention to this window in whatever way is appropriate for the platform if this window is not the current active window. @param Parameters The parameters for drawing attention. Depending on the platform, not all parameters may be supported.
- L168 _public prototype_ `virtual void SetNativeWindowButtonsVisibility(bool bVisible);` — Shows or hides native window buttons on platforms that use them
- L171 _public prototype_ `virtual bool IsRenderingOffScreen() const override;` — Always returns true, since null windows won't present frames to a display.
- L177 _private prototype_ `FNullWindow();` — Protect the constructor; only TSharedRefs of this class can be made.
- L179 _private member_ `FNullApplication* OwningApplication;`
- L181 _private member_ `float DPIScaleFactor;`
- L183 _private member_ `FIntPoint ScreenPosition;`
- L185 _private member_ `FIntPoint SizeInScreen;`
- L188 _private member_ `bool bIsVisible;` — Manually store window visibility as OS doesn't do that for us in nullplatform
- L190 _private member_ `bool bIsInitialized;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNullWindow, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNullWindow, Log, All);`
- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNullWindowType, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNullWindowType, Log, All);`
- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNullWindowEvent, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNullWindowEvent, Log, All);`

### `Source/Runtime/ApplicationCore/Public/Unix/UnixApplicationErrorOutputDevice.h` (Public)


#### struct `FUnixApplicationErrorOutputDevice`  
`struct FUnixApplicationErrorOutputDevice : public FUnixErrorOutputDevice`  
_L8-12_
- inherits: `FUnixErrorOutputDevice`
- L11 _protected prototype_ `virtual void HandleErrorRestoreUI() override;`

### `Source/Runtime/ApplicationCore/Public/Unix/UnixFeedbackContext.h` (Public)


#### class `FUnixFeedbackContext`  
`class FUnixFeedbackContext : public FFeedbackContext`  
_L19-71_
- inherits: `FFeedbackContext`
- desc: Feedback context implementation for Unix.
- L22 _private member_ `FContextSupplier* Context;` — Context information for warning and error messages
- L26 _public member_ `int32 SlowTaskCount;` — Variables.
- L29 _public function_ `FUnixFeedbackContext() : FFeedbackContext() , Context( NULL ) , SlowTaskCount( 0 )` — Constructor.
- L35 _public prototype_ `void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override;`
- L36 _public prototype_ `void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category, double Time) override;`
- L37 _public prototype_ `void SerializeRecord(const UE::FLogRecord& Record) override;`
- L40 _public prototype_ `bool YesNof(const FText& Question) override;` — Ask the user a binary question, returning their answer
- L42 _public function_ `void BeginSlowTask(const FText& Task, bool ShowProgressDialog, bool bShowCancelButton=false)`
- L47 _public function_ `void EndSlowTask()`
- L53 _public function_ `bool StatusUpdate(int32 Numerator, int32 Denominator, const FText& StatusText)`
- L58 _public function_ `FContextSupplier* GetContext() const override`
- L63 _public function_ `void SetContext(FContextSupplier* InSupplier) override`
- L69 _private prototype_ `void LogErrorToSysLog(const TCHAR* V, const FName& Category, double Time) const;`
- L70 _private prototype_ `void LogErrorRecordToSysLog(const UE::FLogRecord& Record) const;`

### `Source/Runtime/ApplicationCore/Public/Unix/UnixPlatformSurvey.h` (Public)


#### struct `FUnixPlatformSurvey`  
`struct FUnixPlatformSurvey : public FGenericPlatformSurvey`  
_L15-26_
- inherits: `FGenericPlatformSurvey`
- desc: Unix implementation of FGenericPlatformSurvey
- L18 _public prototype_ `static bool GetSurveyResults(FHardwareSurveyResults& OutResults, bool bWait = false);` — Start, or check on, the hardware survey
- L25 _private prototype_ `static void WriteFStringToResults(TCHAR* OutBuffer, const FString& InString);` — Safely write strings into the fixed length TCHAR buffers of a FHardwareSurveyResults member

#### Free symbols / members of external scopes

- L28 _typedef_ `typedef FUnixPlatformSurvey FPlatformSurvey;`

### `Source/Runtime/ApplicationCore/Public/Windows/Accessibility/WindowsUIABaseProvider.h` (Public)


#### class `FWindowsUIABaseProvider`  
`class FWindowsUIABaseProvider`  
_L21-53_
- desc: Base class for all Windows UIA Providers to inherit from. Provides implementation of IUnknown's reference counting functions as well as integration with the UIA Manager class.
- L25 _public prototype_ `void OnUIAManagerDestroyed();` — Notify the Provider that the backing application no longer exists.
- L28 _protected prototype_ `FWindowsUIABaseProvider(FWindowsUIAManager& InManager, TSharedRef<IAccessibleWidget> InWidget);`
- L29 _protected prototype_ `virtual ~FWindowsUIABaseProvider();`
- L35 _protected prototype_ `bool IsValid() const;` — Check whether this Provider can have operations called on it. This might return false if the application is being destroyed, or if the underlying accessible widget is no longer valid.
- L38 _protected prototype_ `uint32 IncrementRef();` — Add one to RefCount, and return the new RefCount
- L40 _protected prototype_ `uint32 DecrementRef();` — Subtract one from RefCount, and return the new RefCount. If RefCount is 0, deletes the Provider and returns 0.
- L43 _protected member_ `FWindowsUIAManager* UIAManager;` — A pointer to the UIA Manager which is guaranteed to be valid so long as the application is still running.
- L48 _protected member_ `TSharedRef<IAccessibleWidget> Widget;` — All Providers must have a valid accessible widget, even if the accessible widget itself does not have any valid data backing it. In this case, the accessible widget will return some default values.
- L52 _private member_ `uint32 RefCount;` — Counter for the number of strong references to this object. Many of these will be from external applications.

### `Source/Runtime/ApplicationCore/Public/Windows/Accessibility/WindowsUIAControlProvider.h` (Public)


#### class `FWindowsUIATextRangeProvider`  
`class FWindowsUIATextRangeProvider : public FWindowsUIABaseProvider , public ITextRangeProvider`  
_L17-65_
- inherits: `FWindowsUIABaseProvider,ITextRangeProvider`
- desc: A TextRange Provider represents a start and end position within an ITextProvider. This can reference a word, a paragraph, a selection, etc. Multiple text ranges can exist for a single piece of text.
- L22 _public prototype_ `FWindowsUIATextRangeProvider(FWindowsUIAManager& InManager, TSharedRef<IAccessibleWidget> InWidget, FTextRange InRange);`
- L25 _public prototype_ `HRESULT STDCALL QueryInterface(REFIID riid, void** ppInterface) override;` — IUnknown
- L26 _public prototype_ `ULONG STDCALL AddRef() override;`
- L27 _public prototype_ `ULONG STDCALL Release() override;`
- L31 _public prototype_ `virtual HRESULT STDCALL Clone(ITextRangeProvider** pRetVal) override;` — ITextRangeProvider
- L32 _public prototype_ `virtual HRESULT STDCALL Compare(ITextRangeProvider* range, BOOL* pRetVal) override;`
- L33 _public prototype_ `virtual HRESULT STDCALL CompareEndpoints(TextPatternRangeEndpoint endpoint, ITextRangeProvider* targetRange, TextPatternRangeEndpoint targetEndpoint, int* pRetVal) override;`
- L34 _public prototype_ `virtual HRESULT STDCALL ExpandToEnclosingUnit(TextUnit unit) override;`
- L35 _public prototype_ `virtual HRESULT STDCALL FindAttribute(TEXTATTRIBUTEID attributeId, VARIANT val, BOOL backward, ITextRangeProvider** pRetVal) override;`
- L36 _public prototype_ `virtual HRESULT STDCALL FindText(BSTR text, BOOL backward, BOOL ignoreCase, ITextRangeProvider** pRetVal) override;`
- L37 _public prototype_ `virtual HRESULT STDCALL GetAttributeValue(TEXTATTRIBUTEID attributeId, VARIANT* pRetVal) override;`
- L38 _public prototype_ `virtual HRESULT STDCALL GetBoundingRectangles(SAFEARRAY** pRetVal) override;`
- L39 _public prototype_ `virtual HRESULT STDCALL GetEnclosingElement(IRawElementProviderSimple** pRetVal) override;`
- L40 _public prototype_ `virtual HRESULT STDCALL GetText(int maxLength, BSTR* pRetVal) override;`
- L41 _public prototype_ `virtual HRESULT STDCALL Move(TextUnit unit, int count, int* pRetVal) override;`
- L42 _public prototype_ `virtual HRESULT STDCALL MoveEndpointByUnit(TextPatternRangeEndpoint endpoint, TextUnit unit, int count, int* pRetVal) override;`
- L43 _public prototype_ `virtual HRESULT STDCALL MoveEndpointByRange(TextPatternRangeEndpoint endpoint, ITextRangeProvider* targetRange, TextPatternRangeEndpoint targetEndpoint) override;`
- L44 _public prototype_ `virtual HRESULT STDCALL Select() override;`
- L45 _public prototype_ `virtual HRESULT STDCALL AddToSelection() override;`
- L46 _public prototype_ `virtual HRESULT STDCALL RemoveFromSelection() override;`
- L47 _public prototype_ `virtual HRESULT STDCALL ScrollIntoView(BOOL alignToTop) override;`
- L48 _public prototype_ `virtual HRESULT STDCALL GetChildren(SAFEARRAY** pRetVal) override;`
- L57 _protected prototype_ `FString TextFromTextRange();` — Gets the substring that this text range Provider represents. @return A substring of the underlying widget's text from TextRange's begin/end indices.
- L58 _protected prototype_ `static FString TextFromTextRange(const FString& InString, const FTextRange& InRange);`
- L61 _protected member_ `FTextRange TextRange;` — The range that this Provider represents in the underlying text.
- L64 _private prototype_ `virtual ~FWindowsUIATextRangeProvider();`

#### class `FWindowsUIAControlProvider`  
`class FWindowsUIAControlProvider : public FWindowsUIABaseProvider , public IInvokeProvider , public IRangeValueProvider , public ITextProvider , public IToggleProvider , public ITransformProvider , public IValueProvider , public IWindowProvider , public ISelectionProvider , public ISelectionItemProvider`  
_L74-165_
- inherits: `FWindowsUIABaseProvider,IInvokeProvider,IRangeValueProvider,ITextProvider,IToggleProvider,ITransformProvider,IValueProvider,IWindowProvider,ISelectionProvider,ISelectionItemProvider`
- desc: The control Provider handles all control pattern-related functionality for the widget Provider. Control Providers should only be generated through widget Providers in their GetPatternProvider() function. In doing this, a control Pattern is only guaranteed to support functions that match the pattern Provider that it was generated for. This means that if GetPatternProvider() is called for UIA_ValuePatternId, the control Provider is only guaranteed to work with functions that implement IValueProvider. It is up to the caller to ensure that they are making valid function calls.
- L87 _public prototype_ `FWindowsUIAControlProvider(FWindowsUIAManager& Manager, TSharedRef<IAccessibleWidget> InWidget);`
- L90 _public prototype_ `HRESULT STDCALL QueryInterface(REFIID riid, void** ppInterface) override;` — IUnknown
- L91 _public prototype_ `ULONG STDCALL AddRef() override;`
- L92 _public prototype_ `ULONG STDCALL Release() override;`
- L96 _public prototype_ `virtual HRESULT STDCALL Invoke() override;` — IInvokeProvider
- L100 _public prototype_ `virtual HRESULT STDCALL SetValue(double val) override;` — IRangeValueProvider
- L101 _public prototype_ `virtual HRESULT STDCALL get_Value(double* pRetVal) override;`
- L102 _public prototype_ `virtual HRESULT STDCALL get_IsReadOnly(BOOL* pRetVal) override;`
- L103 _public prototype_ `virtual HRESULT STDCALL get_Maximum(double* pRetVal) override;`
- L104 _public prototype_ `virtual HRESULT STDCALL get_Minimum(double* pRetVal) override;`
- L105 _public prototype_ `virtual HRESULT STDCALL get_LargeChange(double* pRetVal) override;`
- L106 _public prototype_ `virtual HRESULT STDCALL get_SmallChange(double* pRetVal) override;`
- L110 _public prototype_ `virtual HRESULT STDCALL get_DocumentRange(ITextRangeProvider** pRetVal) override;` — ITextProvider
- L111 _public prototype_ `virtual HRESULT STDCALL get_SupportedTextSelection(SupportedTextSelection* pRetVal) override;`
- L112 _public prototype_ `virtual HRESULT STDCALL GetSelection(SAFEARRAY** pRetVal) override;`
- L113 _public prototype_ `virtual HRESULT STDCALL GetVisibleRanges(SAFEARRAY** pRetVal) override;`
- L114 _public prototype_ `virtual HRESULT STDCALL RangeFromChild(IRawElementProviderSimple* childElement, ITextRangeProvider** pRetVal) override;`
- L115 _public prototype_ `virtual HRESULT STDCALL RangeFromPoint(UiaPoint point, ITextRangeProvider** pRetVal) override;`
- L119 _public prototype_ `virtual HRESULT STDCALL get_ToggleState(ToggleState* pRetVal) override;` — IToggleState
- L120 _public prototype_ `virtual HRESULT STDCALL Toggle() override;`
- L124 _public prototype_ `virtual HRESULT STDCALL get_CanMove(BOOL *pRetVal) override;` — ITransformProvider
- L125 _public prototype_ `virtual HRESULT STDCALL get_CanResize(BOOL *pRetVal) override;`
- L126 _public prototype_ `virtual HRESULT STDCALL get_CanRotate(BOOL *pRetVal) override;`
- L127 _public prototype_ `virtual HRESULT STDCALL Move(double x, double y) override;`
- L128 _public prototype_ `virtual HRESULT STDCALL Resize(double width, double height) override;`
- L129 _public prototype_ `virtual HRESULT STDCALL Rotate(double degrees) override;`
- L133 _public prototype_ `virtual HRESULT STDCALL SetValue(LPCWSTR val) override;` — IValueProvider
- L134 _public prototype_ `virtual HRESULT STDCALL get_Value(BSTR* pRetVal) override;`
- L139 _public prototype_ `virtual HRESULT STDCALL Close() override;` — IWindowProvider
- L140 _public prototype_ `virtual HRESULT STDCALL get_CanMaximize(BOOL* pRetVal) override;`
- L141 _public prototype_ `virtual HRESULT STDCALL get_CanMinimize(BOOL* pRetVal) override;`
- L142 _public prototype_ `virtual HRESULT STDCALL get_IsModal(BOOL* pRetVal) override;`
- L143 _public prototype_ `virtual HRESULT STDCALL get_IsTopmost(BOOL* pRetVal) override;`
- L144 _public prototype_ `virtual HRESULT STDCALL get_WindowInteractionState(WindowInteractionState* pRetVal) override;`
- L145 _public prototype_ `virtual HRESULT STDCALL get_WindowVisualState(WindowVisualState* pRetVal) override;`
- L146 _public prototype_ `virtual HRESULT STDCALL SetVisualState(WindowVisualState state) override;`
- L147 _public prototype_ `virtual HRESULT STDCALL WaitForInputIdle(int milliseconds, BOOL* pRetVal) override;`
- L152 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE get_CanSelectMultiple(BOOL* pRetVal) override;` — ISelectionProvider HRESULT STDMETHODCALLTYPE GetSelection(SAFEARRAY** pRetVal) override; // duplicate from ITextProvider. Implementation also there
- L153 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE get_IsSelectionRequired(BOOL* pRetVal) override;`
- L157 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE Select() override;` — ISelectionItemProvider
- L158 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE AddToSelection() override;`
- L159 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE RemoveFromSelection() override;`
- L160 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE get_IsSelected(BOOL* pRetVal) override;`
- L161 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE get_SelectionContainer(IRawElementProviderSimple** pRetVal) override;`
- L164 _private prototype_ `virtual ~FWindowsUIAControlProvider();`

### `Source/Runtime/ApplicationCore/Public/Windows/Accessibility/WindowsUIAManager.h` (Public)


#### class `FWindowsUIAManager`  
`class FWindowsUIAManager`  
_L24-118_
- desc: Manager for Windows implementation of UE's accessibility API, utilizing Microsoft's UI Automation API. It provides a central location for message passing to/from the WindowsApplication, AccessibleMessageHandler, and Windows UIA Providers. This class only accepts and returns references, so callers should ensure their objects are valid before using it.
- L29 _public prototype_ `FWindowsUIAManager(const FWindowsApplication& InApplication);`
- L30 _public prototype_ `~FWindowsUIAManager();`
- L42 _public prototype_ `FWindowsUIAWidgetProvider& GetWidgetProvider(TSharedRef<IAccessibleWidget> InWidget);` — Create a Windows UIA IRawElementProviderSimple from a given accessible widget. Providers are stored in a local cache, and this function will allocate a new Provider if one does not already exist for the given widget. Using this function will always increase the RefCount of the Provider by one. If InWidget->IsWindow() returns true, a FWindowsUIAWindowProvider will be created instead of a FWindowsUIAWidgetProvider. @param InWidget A non-null reference to an accessible widget @return A reference to the cached Provider
- L54 _public prototype_ `FWindowsUIAWindowProvider& GetWindowProvider(TSharedRef<FWindowsWindow> InWindow);` — Create a Windows UIA IRawElementProviderSimple from a given native window handle. Providers are stored in a local cache, and this function will allocate a new Provider if one does not already exist for the given widget. Using this function will always increase the RefCount of the Provider by one. If the Provider cache is empty upon calling this function, it will activate accessibility in the entire application. @param InWindow A non-null reference to a native window @return A reference to the cached Provider
- L63 _public prototype_ `void OnWidgetProviderRemoved(TSharedRef<IAccessibleWidget> InWidget);` — Notify the Manager that the RefCount for a Provider has reached 0, which will cause it to be removed from the cache. If the Provider cache is empty after removing the Provider, accessibility will be disabled through the entire application. @param InWidget The accessible widget backing the Provider that was removed
- L68 _public prototype_ `void OnAccessibleMessageHandlerChanged();` — Notify the Manager that the accessible message handler for the application has changed, in order to relink to the accessible event delegate.
- L70 _public function_ `uint32 GetCachedCurrentLocaleLCID() const`
- L78 _public prototype_ `void RunInGameThreadBlocking(const TFunction<void()>& Function) const;` — Runs the passed in function in the game thread. Blocks until the function completes execution in the game thread. @param Function The function to run in the game thread
- L80 _public member_ `static TMap<EAccessibleWidgetType, ULONG> WidgetTypeToWindowsTypeMap;`
- L81 _public member_ `static TMap<EAccessibleWidgetType, FText> WidgetTypeToTextMap;`
- L84 _public prototype_ `void DumpAccessibilityStats() const;`
- L89 _private prototype_ `void OnEventRaised(const FAccessibleEventArgs& Args);` — Callback function for processing events raised from the AccessibleMessageHandler
- L92 _private prototype_ `void OnAccessibilityEnabled();` — Called when the first window widget provider is requested.
- L95 _private prototype_ `void OnAccessibilityDisabled();` — Called when the last widget provider is removed.
- L98 _private prototype_ `void UpdateCachedCurrentLocaleLCID();` — Updates the cached current locale LCID to match the current locale LCID in FInternationalization
- L101 _private member_ `TMap<TSharedRef<IAccessibleWidget>, FWindowsUIAWidgetProvider*> CachedWidgetProviders;` — Cache of all Providers with a RefCount of at least 1 that map to an accessible widget.
- L106 _private member_ `TSet<FWindowsUIABaseProvider*> ProviderList;` — A set of all Providers with a RefCount of at least 1. This also includes non-widget Providers such as text ranges. When the application is closed, this is used to notify Providers held by external applications that they are invalid.
- L108 _private member_ `const FWindowsApplication& WindowsApplication;` — A reference back to the owning application that can be used to access the AccessibleMessageHandler
- L111 _private member_ `FDelegateHandle OnCultureChangedHandle;` — Handle associated with registering for culture change events from FInternationalization
- L117 _private member_ `uint32 CachedCurrentLocaleLCID;` — Current LCID of the current locale in FInternationalization. Used to ensure screen readers pronounce localized text in a native voice. For more info: https://docs.microsoft.com/en-us/windows/win32/intl/language-identifier-constants-and-strings

### `Source/Runtime/ApplicationCore/Public/Windows/Accessibility/WindowsUIAPropertyGetters.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace WindowsUIAPropertyGetters`
- L19 _prototype_ `VARIANT GetPropertyValueWindows(TSharedRef<IAccessibleWidget> AccessibleWidget, PROPERTYID WindowsPropertyId);` (scope `WindowsUIAPropertyGetters`)
- L20 _prototype_ `FVariant GetPropertyValue(TSharedRef<IAccessibleWidget> AccessibleWidget, PROPERTYID WindowsPropertyId);` (scope `WindowsUIAPropertyGetters`)
- L26 _prototype_ `VARIANT FVariantToWindowsVariant(const FVariant& Value);` (scope `WindowsUIAPropertyGetters`) — Convert an FVariant to a Windows VARIANT. Only necessary conversions are implemented.

### `Source/Runtime/ApplicationCore/Public/Windows/Accessibility/WindowsUIAWidgetProvider.h` (Public)


#### class `FWindowsUIAWidgetProvider`  
`class FWindowsUIAWidgetProvider : public FWindowsUIABaseProvider , public IRawElementProviderSimple , public IRawElementProviderFragment`  
_L20-67_
- inherits: `FWindowsUIABaseProvider,IRawElementProviderSimple,IRawElementProviderFragment`
- desc: Windows UIA Provider implementation for all non-Window widgets. WidgetProvider does not inherit from IRawElementProviderFragmentRoot and thus cannot be queried by external applications for ElementProviderFromPoint(). This should work fine but there could be unforeseen consquences for cases like modal popup dialogs which are not necessarily windows.
- L28 _public prototype_ `virtual HRESULT STDCALL QueryInterface(REFIID riid, void** ppInterface) override;` — IUnknown
- L29 _public prototype_ `virtual ULONG STDCALL AddRef() override;`
- L30 _public prototype_ `virtual ULONG STDCALL Release() override;`
- L34 _public prototype_ `virtual HRESULT STDCALL get_ProviderOptions(ProviderOptions* pRetVal) override;` — IRawElementProviderSimple
- L35 _public prototype_ `virtual HRESULT STDCALL GetPatternProvider(PATTERNID patternId, IUnknown** pRetVal) override;`
- L36 _public prototype_ `virtual HRESULT STDCALL GetPropertyValue(PROPERTYID propertyId, VARIANT* pRetVal) override;`
- L37 _public prototype_ `virtual HRESULT STDCALL get_HostRawElementProvider(IRawElementProviderSimple** pRetVal) override;`
- L41 _public prototype_ `virtual HRESULT STDCALL Navigate(NavigateDirection direction, IRawElementProviderFragment** pRetVal) override;` — IRawElementProviderFragment
- L42 _public prototype_ `virtual HRESULT STDCALL GetRuntimeId(SAFEARRAY** pRetVal) override;`
- L43 _public prototype_ `virtual HRESULT STDCALL get_BoundingRectangle(UiaRect* pRetVal) override;`
- L44 _public prototype_ `virtual HRESULT STDCALL GetEmbeddedFragmentRoots(SAFEARRAY** pRetVal) override;`
- L45 _public prototype_ `virtual HRESULT STDCALL SetFocus() override;`
- L46 _public prototype_ `virtual HRESULT STDCALL get_FragmentRoot(IRawElementProviderFragmentRoot** pRetVal) override;`
- L57 _public prototype_ `bool SupportsInterface(PATTERNID PatternId) const;` — Check if this Provider implements a specific control pattern. A FWindowsUIAControlProvider can then be created of the pattern is supported. Since this is a helper function, the caller should separately ensure IsValid() before doing anything with the result. @param PatternId The control pattern to check for @return true if a control Provider can be created for this Provider for this control pattern
- L60 _protected prototype_ `FWindowsUIAWidgetProvider(FWindowsUIAManager& InManager, TSharedRef<IAccessibleWidget> InWidget);`
- L61 _protected prototype_ `virtual ~FWindowsUIAWidgetProvider();`

#### class `FWindowsUIAWindowProvider`  
`class FWindowsUIAWindowProvider : public FWindowsUIAWidgetProvider , public IRawElementProviderFragmentRoot`  
_L72-98_
- inherits: `FWindowsUIAWidgetProvider,IRawElementProviderFragmentRoot`
- desc: Windows UIA Provider implementation for all Window widgets. Widget->AsWindow() must return a valid pointer.
- L79 _public prototype_ `virtual HRESULT STDCALL QueryInterface(REFIID riid, void** ppInterface) override;` — IUnknown
- L80 _public prototype_ `virtual ULONG STDCALL AddRef() override;`
- L81 _public prototype_ `virtual ULONG STDCALL Release() override;`
- L85 _public prototype_ `virtual HRESULT STDCALL get_HostRawElementProvider(IRawElementProviderSimple** pRetVal) override;` — IRawElementProviderSimple
- L86 _public prototype_ `virtual HRESULT STDCALL GetPatternProvider(PATTERNID patternId, IUnknown** pRetVal) override;`
- L90 _public prototype_ `virtual HRESULT STDCALL ElementProviderFromPoint(double x, double y, IRawElementProviderFragment** pRetVal) override;` — IRawElementProviderFragmentRoot
- L91 _public prototype_ `virtual HRESULT STDCALL GetFocus(IRawElementProviderFragment** pRetVal) override;`
- L96 _protected prototype_ `FWindowsUIAWindowProvider(FWindowsUIAManager& InManager, TSharedRef<IAccessibleWidget> InWidget);` — Note: InWidget must also be an IAccessibleWindow
- L97 _protected prototype_ `virtual ~FWindowsUIAWindowProvider();`

#### class `FScopedWidgetProvider`  
`class FScopedWidgetProvider`  
_L105-117_
- desc: Helper class which can be used in conjunction with FWindowsUIAManager::GetWidgetProvider, which will automatically calls Release on the Provider when the variable goes out of scope. Note that GetWidgetProvider already increments the ref count when its called, so the scoped provider does not have to also increase it.
- L108 _public function_ `FScopedWidgetProvider(FWindowsUIAWidgetProvider& InProvider) : Provider(InProvider)`
- L112 _public function_ `~FScopedWidgetProvider()`
- L116 _public member_ `FWindowsUIAWidgetProvider& Provider;`

### `Source/Runtime/ApplicationCore/Public/Windows/TextStoreACP.h` (Public)


#### class `FTextStoreACP`  
`class FTextStoreACP : public ITextStoreACP, public ITfContextOwnerCompositionSink`  
_L17-140_
- inherits: `ITextStoreACP,ITfContextOwnerCompositionSink`
- L20 _public prototype_ `FTextStoreACP(const TSharedRef<ITextInputMethodContext>& Context);`
- L21 _public prototype_ `virtual ~FTextStoreACP() = default;`
- L24 _public prototype_ `STDMETHODIMP QueryInterface(REFIID riid, void **ppvObj);` — IUnknown Interface Begin
- L25 _public prototype_ `STDMETHODIMP_(ULONG) AddRef(void);`
- L26 _public prototype_ `STDMETHODIMP_(ULONG) Release(void);`
- L30 _public prototype_ `STDMETHODIMP AdviseSink(__RPC__in REFIID riid, __RPC__in_opt IUnknown *punk, DWORD dwMask);` — ITextStoreACP Interface Begin
- L31 _public prototype_ `STDMETHODIMP UnadviseSink(__RPC__in_opt IUnknown *punk);`
- L32 _public prototype_ `STDMETHODIMP RequestLock(DWORD dwLockFlags, HRESULT *phrSession);`
- L34 _public prototype_ `STDMETHODIMP GetStatus(__RPC__out TS_STATUS *pdcs);`
- L35 _public prototype_ `STDMETHODIMP GetEndACP(__RPC__out LONG *pacp);`
- L38 _public prototype_ `STDMETHODIMP GetSelection(ULONG ulIndex, ULONG ulCount, __RPC__out_ecount_part(ulCount, *pcFetched) TS_SELECTION_ACP *pSelection, __RPC__out ULONG *pcFetched);` — Selection Methods
- L39 _public prototype_ `STDMETHODIMP SetSelection(ULONG ulCount, __RPC__in_ecount_full(ulCount) const TS_SELECTION_ACP *pSelection);`
- L42 _public prototype_ `STDMETHODIMP RequestSupportedAttrs(DWORD dwFlags, ULONG cFilterAttrs, __RPC__in_ecount_full_opt(cFilterAttrs) const TS_ATTRID *paFilterAttrs);` — Attributes Methods
- L43 _public prototype_ `STDMETHODIMP RequestAttrsAtPosition(LONG acpPos, ULONG cFilterAttrs, __RPC__in_ecount_full_opt(cFilterAttrs) const TS_ATTRID *paFilterAttrs, DWORD dwFlags);`
- L44 _public prototype_ `STDMETHODIMP RequestAttrsTransitioningAtPosition(LONG acpPos, ULONG cFilterAttrs, __RPC__in_ecount_full_opt(cFilterAttrs) const TS_ATTRID *paFilterAttrs, DWORD dwFlags);`
- L45 _public prototype_ `STDMETHODIMP FindNextAttrTransition(LONG acpStart, LONG acpHalt, ULONG cFilterAttrs, __RPC__in_ecount_full_opt(cFilterAttrs) const TS_ATTRID *paFilterAttrs, DWORD dwFlags, __RPC__out LONG *pacpNext, __RPC__out BOOL *pfFound, __RPC__out LONG *plFoundOffset);`
- L46 _public prototype_ `STDMETHODIMP RetrieveRequestedAttrs(ULONG ulCount, __RPC__out_ecount_part(ulCount, *pcFetched) TS_ATTRVAL *paAttrVals, __RPC__out ULONG *pcFetched);`
- L49 _public prototype_ `STDMETHODIMP GetActiveView(__RPC__out TsViewCookie *pvcView);` — View Methods
- L50 _public prototype_ `STDMETHODIMP GetACPFromPoint(TsViewCookie vcView, __RPC__in const POINT *pt, DWORD dwFlags, __RPC__out LONG *pacp);`
- L51 _public prototype_ `STDMETHODIMP GetTextExt(TsViewCookie vcView, LONG acpStart, LONG acpEnd, __RPC__out RECT *prc, __RPC__out BOOL *pfClipped);`
- L52 _public prototype_ `STDMETHODIMP GetScreenExt(TsViewCookie vcView, __RPC__out RECT *prc);`
- L53 _public prototype_ `STDMETHODIMP GetWnd(TsViewCookie vcView, __RPC__deref_out_opt HWND *phwnd);`
- L56 _public prototype_ `STDMETHODIMP GetText(LONG acpStart, LONG acpEnd, __RPC__out_ecount_part(cchPlainReq, *pcchPlainOut) WCHAR *pchPlain, ULONG cchPlainReq, __RPC__out ULONG *pcchPlainOut, __RPC__out_ecount_part(ulRunInfoReq, *pulRunInfoOut) TS_RUNINFO *prgRunInfo, ULONG ulRunInfoReq, __RPC__out ULONG *pulRunInfoOut, __RPC__out LONG *pacpNext);` — Plain Character Methods
- L57 _public prototype_ `STDMETHODIMP QueryInsert(LONG acpInsertStart, LONG acpInsertEnd, ULONG cch, __RPC__out LONG *pacpResultStart, __RPC__out LONG *pacpResultEnd);`
- L58 _public prototype_ `STDMETHODIMP InsertTextAtSelection(DWORD dwFlags, __RPC__in_ecount_full(cch) const WCHAR *pchText, ULONG cch, __RPC__out LONG *pacpStart, __RPC__out LONG *pacpEnd, __RPC__out TS_TEXTCHANGE *pChange);`
- L59 _public prototype_ `STDMETHODIMP SetText(DWORD dwFlags, LONG acpStart, LONG acpEnd, __RPC__in_ecount_full(cch) const WCHAR *pchText, ULONG cch, __RPC__out TS_TEXTCHANGE *pChange);`
- L62 _public prototype_ `STDMETHODIMP GetEmbedded(LONG acpPos, __RPC__in REFGUID rguidService, __RPC__in REFIID riid, __RPC__deref_out_opt IUnknown **ppunk);` — Embedded Character Methods
- L63 _public prototype_ `STDMETHODIMP GetFormattedText(LONG acpStart, LONG acpEnd, __RPC__deref_out_opt IDataObject **ppDataObject);`
- L64 _public prototype_ `STDMETHODIMP QueryInsertEmbedded(__RPC__in const GUID *pguidService, __RPC__in const FORMATETC *pFormatEtc, __RPC__out BOOL *pfInsertable);`
- L65 _public prototype_ `STDMETHODIMP InsertEmbedded(DWORD dwFlags, LONG acpStart, LONG acpEnd, __RPC__in_opt IDataObject *pDataObject, __RPC__out TS_TEXTCHANGE *pChange);`
- L66 _public prototype_ `STDMETHODIMP InsertEmbeddedAtSelection(DWORD dwFlags, __RPC__in_opt IDataObject *pDataObject, __RPC__out LONG *pacpStart, __RPC__out LONG *pacpEnd, __RPC__out TS_TEXTCHANGE *pChange);`
- L70 _public prototype_ `STDMETHODIMP OnStartComposition(__RPC__in_opt ITfCompositionView *pComposition, __RPC__out BOOL *pfOk);` — ITfContextOwnerCompositionSink Interface Begin
- L71 _public prototype_ `STDMETHODIMP OnUpdateComposition(__RPC__in_opt ITfCompositionView *pComposition, __RPC__in_opt ITfRange *pRangeNew);`
- L72 _public prototype_ `STDMETHODIMP OnEndComposition(__RPC__in_opt ITfCompositionView *pComposition);`
- L77 _private member_ `ULONG ReferenceCount;` — Reference count for IUnknown Implementation
- L80 _private member_ `const TSharedRef<ITextInputMethodContext> TextContext;` — Associated text context that genericizes interfacing with text editing widgets.
- L94 _private member_ `TArray<FSupportedAttribute> SupportedAttributes;`
- L103 _private member_ `} LockManager;`
- L117 _public member_ `} AdviseSinkObject;`
- L127 _public member_ `} Composition;`
- L131 _public member_ `TComPtr<ITfDocumentMgr> TSFDocumentManager;` — Document manager object for managing contexts.
- L134 _public member_ `TComPtr<ITfContext> TSFContext;` — Context object for pushing context on to document manager.
- L137 _public member_ `TComPtr<ITfContextOwnerCompositionServices> TSFContextOwnerCompositionServices;` — Context owner composition services object for terminating compositions.
- L139 _public member_ `TfEditCookie TSFEditCookie;`

#### struct `FTextStoreACP::FSupportedAttribute`  
`struct FSupportedAttribute`  
_L82-92_
- L84 _public function_ `FSupportedAttribute(const TS_ATTRID* const InId) : WantsDefault(false), Id(InId)`
- L89 _public member_ `bool WantsDefault;`
- L90 _public member_ `const TS_ATTRID* const Id;`
- L91 _public member_ `VARIANT DefaultValue;`

#### struct `FTextStoreACP::FLockManager`  
`struct FLockManager`  
_L96-103_
- L98 _public function_ `FLockManager() : LockType(0), IsPendingLockUpgrade(false)`
- L101 _public member_ `DWORD LockType;`
- L102 _public member_ `bool IsPendingLockUpgrade;`

#### struct `FTextStoreACP::FAdviseSinkObject`  
`struct FAdviseSinkObject`  
_L106-117_
- L108 _public function_ `FAdviseSinkObject() : TextStoreACPSink(nullptr), SinkFlags(0)`
- L111 _public member_ `TComPtr<ITextStoreACPSink> TextStoreACPSink;` — Sink object for ITextStoreACP Implementation
- L113 _public member_ `TComPtr<ITextStoreACPServices> TextStoreACPServices;`
- L116 _public member_ `DWORD SinkFlags;` — Flags defining what events the sink object should be notified of.

#### struct `FTextStoreACP::FComposition`  
`struct FComposition`  
_L119-127_
- L121 _public function_ `FComposition() : TSFCompositionView(nullptr)`
- L125 _public member_ `TComPtr<ITfCompositionView> TSFCompositionView;` — Composition view object for managing compositions.

### `Source/Runtime/ApplicationCore/Public/Windows/WindowsApplication.h` (Public)


#### enum `ETaskbarProgressState::Type`  
`enum Type`  
_L35-63_
- L38 _public enumerator_ `NoProgress = 0x0` — Stops displaying progress and returns the button to its normal state.
- L44 _public enumerator_ `Indeterminate = 0x1` — The progress indicator does not grow in size, but cycles repeatedly along the length of the task bar button. This indicates activity without specifying what proportion of the progress is complete. Progress is taking place, but there is no prediction as to how long the operation will take.
- L49 _public enumerator_ `Normal = 0x2` — The progress indicator grows in size from left to right in proportion to the estimated amount of the operation completed. This is a determinate progress indicator; a prediction is being made as to the duration of the operation.
- L55 _public enumerator_ `Error = 0x4` — The progress indicator turns red to show that an error has occurred in one of the windows that is broadcasting progress. This is a determinate state. If the progress indicator is in the indeterminate state, it switches to a red determinate display of a generic percentage not indicative of actual progress.
- L62 _public enumerator_ `Paused = 0x8` — The progress indicator turns yellow to show that progress is currently stopped in one of the windows but can be resumed by the user. No error condition exists and nothing is preventing the progress from continuing. This is a determinate state. If the progress indicator is in the indeterminate state, it switches to a yellow determinate display of a generic percentage not indicative of actual progress.

#### class `FTaskbarList`  
`class FTaskbarList`  
_L73-125_
- desc: Allows access to task bar lists. This class can be used to change the appearance of a window's entry in the windows task bar, such as setting an overlay icon or showing a progress indicator.
- L82 _public prototype_ `static TSharedRef<FTaskbarList> Create();` — Create and initialize a new task bar list. @return The new task bar list.
- L91 _public prototype_ `void SetOverlayIcon(HWND WindowHandle, HICON Icon, FText Description);` — Sets the overlay icon of a task bar entry. @param WindowHandle The window handle to change the overlay icon for. @param Icon The overlay icon to set. @param Description The overlay icon's description text.
- L99 _public prototype_ `void SetProgressState(HWND WindowHandle, ETaskbarProgressState::Type State);` — Sets the progress state of a task bar entry. @param WindowHandle The window handle to change the progress state for. @param State The new progress state.
- L108 _public prototype_ `void SetProgressValue(HWND WindowHandle, uint64 Current, uint64 Total);` — Sets the progress value of a task bar entry. @param WindowHandle The window handle to change the progress value for. @param Current The current progress value. @param Total The total progress value.
- L111 _public prototype_ `~FTaskbarList();` — Destructor.
- L116 _private prototype_ `FTaskbarList();` — Hidden constructor (use FTaskbarList::Create).
- L119 _private prototype_ `void Initialize();` — Initializes the task bar list instance.
- L124 _private member_ `ITaskbarList3* TaskBarList3;` — Holds the internal task bar object.

#### struct `FDeferredWindowsMessage`  
`struct FDeferredWindowsMessage`  
_L128-158_
- L130 _public function_ `FDeferredWindowsMessage( const TSharedPtr<FWindowsWindow>& InNativeWindow, HWND InHWnd, uint32 InMessage, WPARAM InWParam, LPARAM InLParam, int32 InX=0, int32 InY=0, uint32 InRawInputFlags = 0 ) : NativeWindow( InNativeWindow ) , hWND( InHWnd ) , Message( InMessage ) , wParam( InWParam ) , lParam( InLParam ) , X( InX ) , Y( InY ) , RawInputFlags( InRawInputFlags )`
- L142 _public member_ `TWeakPtr<FWindowsWindow> NativeWindow;` — Native window that received the message
- L145 _public member_ `HWND hWND;` — Window handle
- L148 _public member_ `uint32 Message;` — Message code
- L151 _public member_ `WPARAM wParam;` — Message data
- L152 _public member_ `LPARAM lParam;`
- L155 _public member_ `int32 X;` — Mouse coordinates
- L156 _public member_ `int32 Y;`
- L157 _public member_ `uint32 RawInputFlags;`

#### enum `EWindowsDragDropOperationType::Type`  
`enum Type`  
_L163-169_
- L165 _public enumerator_ `DragEnter`
- L166 _public enumerator_ `DragOver`
- L167 _public enumerator_ `DragLeave`
- L168 _public enumerator_ `Drop`

#### struct `FDragDropOLEData`  
`struct FDragDropOLEData`  
_L173-189_
- L182 _public function_ `FDragDropOLEData() : Type(None)`
- L186 _public member_ `FString OperationText;`
- L187 _public member_ `TArray<FString> OperationFilenames;`
- L188 _public member_ `uint8 Type;`

#### enum `FDragDropOLEData::EWindowsOLEDataType`  
`enum EWindowsOLEDataType`  
_L175-180_
- L177 _public enumerator_ `None = 0`
- L178 _public enumerator_ `Text = 1<<0`
- L179 _public enumerator_ `Files = 1<<1`

#### struct `FDeferredWindowsDragDropOperation`  
`struct FDeferredWindowsDragDropOperation`  
_L192-253_
- L197 _private function_ `FDeferredWindowsDragDropOperation() : HWnd(NULL) , KeyState(0)` — Private constructor. Use the factory functions below.
- L207 _public function_ `static FDeferredWindowsDragDropOperation MakeDragEnter(HWND InHwnd, const FDragDropOLEData& InOLEData, ::DWORD InKeyState, POINTL InCursorPosition)`
- L218 _public function_ `static FDeferredWindowsDragDropOperation MakeDragOver(HWND InHwnd, ::DWORD InKeyState, POINTL InCursorPosition)`
- L228 _public function_ `static FDeferredWindowsDragDropOperation MakeDragLeave(HWND InHwnd)`
- L236 _public function_ `static FDeferredWindowsDragDropOperation MakeDrop(HWND InHwnd, const FDragDropOLEData& InOLEData, ::DWORD InKeyState, POINTL InCursorPosition)`
- L247 _public member_ `EWindowsDragDropOperationType::Type OperationType;`
- L249 _public member_ `HWND HWnd;`
- L250 _public member_ `FDragDropOLEData OLEData;`
- L252 _public member_ `POINTL CursorPosition;`

#### class `IWindowsMessageHandler`  
`class IWindowsMessageHandler`  
_L262-277_
- desc: Interface for classes that handle Windows events.
- L276 _public prototype_ `virtual bool ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam, int32& OutResult) = 0;` — Processes a Windows message. @param hwnd Handle to the window that received the message. @param msg The message. @param wParam Additional message information. @param lParam Additional message information. @param OutResult Will contain the result if the message was handled. @return true if the message was handled, false otherwise.

#### class `FWindowsApplication`  
`class FWindowsApplication : public GenericApplication , public IInputInterface`  
_L283-618_
- inherits: `GenericApplication,IInputInterface`
- desc: Windows-specific application implementation.
- L296 _public prototype_ `static FWindowsApplication* CreateWindowsApplication( const HINSTANCE InstanceHandle, const HICON IconHandle );` — Static: Creates a new Win32 application @param InstanceHandle Win32 instance handle. @param IconHandle Win32 application icon handle. @return New application object.
- L299 _public prototype_ `static void StaticPostPumpMessages();` — Perform operations after pumping messages on global application.
- L302 _public prototype_ `void PostPumpMessages();` — Perform operations after pumping messages.
- L313 _public prototype_ `void ProcessRawMouseInput(const RAWMOUSE& Mouse, RawMouseInputResult& OutResult);` — Process raw mouse input.
- L316 _public prototype_ `void ProcessWorkerInputs();` — Process raw mouse inputs gathered from a helper thread/window.
- L319 _public prototype_ `virtual ~FWindowsApplication();` — Virtual destructor.
- L324 _public prototype_ `void DeferDragDropOperation( const FDeferredWindowsDragDropOperation& DeferredDragDropOperation );` — Called by a window when an OLE Drag and Drop operation occurred on a non-game thread
- L326 _public prototype_ `TSharedPtr<FTaskbarList> GetTaskbarList();`
- L329 _public prototype_ `HRESULT OnOLEDragEnter( const HWND HWnd, const FDragDropOLEData& OLEData, ::DWORD KeyState, POINTL CursorPosition, ::DWORD *CursorEffect);` — Invoked by a window when an OLE Drag and Drop first enters it.
- L332 _public prototype_ `HRESULT OnOLEDragOver( const HWND HWnd, ::DWORD KeyState, POINTL CursorPosition, ::DWORD *CursorEffect);` — Invoked by a window when an OLE Drag and Drop moves over the window.
- L335 _public prototype_ `HRESULT OnOLEDragOut( const HWND HWnd );` — Invoked by a window when an OLE Drag and Drop exits the window.
- L338 _public prototype_ `HRESULT OnOLEDrop( const HWND HWnd, const FDragDropOLEData& OLEData, ::DWORD KeyState, POINTL CursorPosition, ::DWORD *CursorEffect);` — Invoked by a window when an OLE Drag and Drop is dropped onto the window.
- L346 _public prototype_ `virtual void AddMessageHandler(IWindowsMessageHandler& InMessageHandler);` — Adds a Windows message handler with the application instance. @param MessageHandler The message handler to register. @see RemoveMessageHandler
- L354 _public prototype_ `virtual void RemoveMessageHandler(IWindowsMessageHandler& InMessageHandler);` — Removes a Windows message handler with the application instance. @param MessageHandler The message handler to register. @see AddMessageHandler
- L360 _public prototype_ `virtual void SetMessageHandler( const TSharedRef< class FGenericApplicationMessageHandler >& InMessageHandler ) override;`
- L362 _public prototype_ `virtual void SetAccessibleMessageHandler(const TSharedRef<FGenericAccessibleMessageHandler>& InAccessibleMessageHandler) override;`
- L364 _public prototype_ `virtual void PollGameDeviceState( const float TimeDelta ) override;`
- L365 _public prototype_ `virtual void PumpMessages( const float TimeDelta ) override;`
- L366 _public prototype_ `virtual void ProcessDeferredEvents( const float TimeDelta ) override;`
- L367 _public prototype_ `virtual TSharedRef< FGenericWindow > MakeWindow() override;`
- L368 _public prototype_ `virtual void InitializeWindow( const TSharedRef< FGenericWindow >& Window, const TSharedRef< FGenericWindowDefinition >& InDefinition, const TSharedPtr< FGenericWindow >& InParent, const bool bShowImmediately ) override;`
- L369 _public prototype_ `virtual void SetCapture( const TSharedPtr< FGenericWindow >& InWindow ) override;`
- L370 _public prototype_ `virtual void* GetCapture( void ) const override;`
- L371 _public function_ `virtual bool IsMinimized() const override`
- L372 _public prototype_ `virtual void SetHighPrecisionMouseMode( const bool Enable, const TSharedPtr< FGenericWindow >& InWindow ) override;`
- L373 _public prototype_ `void UpdateHighPrecisionMouseMode();`
- L374 _public function_ `virtual bool IsUsingHighPrecisionMouseMode() const override`
- L375 _public function_ `virtual bool IsMouseAttached() const override`
- L376 _public prototype_ `virtual bool IsGamepadAttached() const override;`
- L377 _public prototype_ `virtual FModifierKeysState GetModifierKeys() const override;`
- L378 _public prototype_ `virtual bool IsCursorDirectlyOverSlateWindow() const override;`
- L379 _public prototype_ `virtual FPlatformRect GetWorkArea( const FPlatformRect& CurrentWindow ) const override;`
- L380 _public prototype_ `virtual void GetInitialDisplayMetrics( FDisplayMetrics& OutDisplayMetrics ) const override;`
- L381 _public prototype_ `virtual EWindowTitleAlignment::Type GetWindowTitleAlignment() const override;`
- L382 _public prototype_ `virtual EWindowTransparency GetWindowTransparencySupport() const override;`
- L383 _public prototype_ `virtual void DestroyApplication() override;`
- L385 _public function_ `virtual IInputInterface* GetInputInterface() override`
- L390 _public function_ `virtual ITextInputMethodSystem *GetTextInputMethodSystem() override`
- L395 _public prototype_ `virtual void AddExternalInputDevice(TSharedPtr<class IInputDevice> InputDevice);`
- L397 _public prototype_ `virtual void FinishedInputThisFrame() override;`
- L402 _public prototype_ `virtual void SetForceFeedbackChannelValue (int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;`
- L403 _public prototype_ `virtual void SetForceFeedbackChannelValues(int32 ControllerId, const FForceFeedbackValues &Values) override;`
- L404 _public prototype_ `virtual void SetHapticFeedbackValues(int32 ControllerId, int32 Hand, const FHapticFeedbackValues& Values) override;`
- L405 _public prototype_ `virtual void SetLightColor(int32 ControllerId, FColor Color) override;`
- L406 _public prototype_ `virtual void ResetLightColor(int32 ControllerId) override;`
- L407 _public prototype_ `virtual void SetDeviceProperty(int32 ControllerId, const FInputDeviceProperty* Property) override;`
- L423 _public prototype_ `bool SupportsForceMaxTouchpadSensitivity();`
- L424 _public prototype_ `void ApplyForceMaxTouchpadSensitivity();`
- L425 _public prototype_ `void RemoveForceMaxTouchpadSensitivity();`
- L442 _public prototype_ `EForceMaxTouchpadSensitivityRestorationValues GetForceMaxTouchpadSensitivityRestorationValue();`
- L448 _protected prototype_ `static LRESULT CALLBACK AppWndProc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);` — Windows callback for message processing (forwards messages to the FWindowsApplication instance).
- L451 _protected prototype_ `int32 ProcessMessage( HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam );` — Processes a single Windows message.
- L454 _protected prototype_ `void ProcessMouseButton(double CurrentTime, const TSharedPtr< FGenericWindow >& Window, USHORT ButtonFlags, USHORT DownFlag, USHORT UpFlag, EMouseButtons::Type MouseButton, FVector2D CursorPos);` — Processes mouse button.
- L457 _protected prototype_ `int32 ProcessDeferredMessage( const FDeferredWindowsMessage& DeferredMessage );` — Processes a deferred Windows message.
- L460 _protected prototype_ `void ProcessDeferredDragDropOperation(const FDeferredWindowsDragDropOperation& Op);` — Processes deferred drag and drop operations.
- L463 _protected prototype_ `FWindowsApplication( const HINSTANCE HInstance, const HICON IconHandle );` — Hidden constructor.
- L465 _protected prototype_ `void ApplyLowLevelMouseFilter();`
- L466 _protected prototype_ `void RemoveLowLevelMouseFilter();`
- L468 _protected prototype_ `static LRESULT CALLBACK HandleLowLevelMouseFilterHook(int nCode, WPARAM wParam, LPARAM lParam);`
- L470 _protected member_ `HHOOK LowLevelMouseFilterHook;`
- L471 _protected member_ `bool bLowLevelMouseFilterIsApplied = false;`
- L476 _private prototype_ `static bool RegisterClass( const HINSTANCE HInstance, const HICON HIcon );` — Registers the Windows class for windows and assigns the application instance and icon
- L479 _private prototype_ `static bool IsKeyboardInputMessage( uint32 msg );` — @return  True if a windows message is related to user input from the keyboard
- L482 _private prototype_ `static bool IsMouseInputMessage( uint32 msg );` — @return  True if a windows message is related to user input from the mouse
- L485 _private prototype_ `static bool IsFakeMouseInputMessage(uint32 msg);` — @return  True if a windows message is a fake mouse input message generated after a WM_TOUCH event
- L488 _private prototype_ `static bool IsInputMessage( uint32 msg );` — @return  True if a windows message is related to user input (mouse, keyboard)
- L491 _private prototype_ `void DeferMessage( TSharedPtr<FWindowsWindow>& NativeWindow, HWND InHWnd, uint32 InMessage, WPARAM InWParam, LPARAM InLParam, int32 MouseX = 0, int32 MouseY = 0, uint32 RawInputFlags = 0 );` — Defers a Windows message for later processing.
- L494 _private prototype_ `void CheckForShiftUpEvents(const int32 KeyCode);` — Checks a key code for release of the Shift key.
- L497 _private prototype_ `void ShutDownAfterError();` — Shuts down the application (called after an unrecoverable error occurred).
- L500 _private prototype_ `void AllowAccessibilityShortcutKeys(const bool bAllowKeys);` — Enables or disables Windows accessibility features, such as sticky keys.
- L503 _private prototype_ `void QueryConnectedMice();` — Queries and caches the number of connected mouse devices.
- L506 _private prototype_ `uint32 GetTouchIndexForID(int32 TouchID);` — Gets the touch index for a given windows touch ID.
- L509 _private prototype_ `uint32 GetFirstFreeTouchIndex();` — Searches for a free touch index.
- L512 _private prototype_ `void UpdateAllModifierKeyStates();` — Helper function to update the cached states of all modifier keys
- L514 _private prototype_ `FPlatformRect GetWorkAreaFromOS(const FPlatformRect& CurrentWindow) const;`
- L517 _private prototype_ `void RegisterHighPrecisionMouseMode();` — Registers for raw input
- L520 _private prototype_ `void UnregisterHighPrecisionMouseMode();` — Unregisters for raw input
- L522 _private prototype_ `void OnInputDeviceModuleRegistered(const FName& Type, IModularFeature* ModularFeature);`
- L526 _private member_ `static const FIntPoint MinimizedWindowPosition;`
- L528 _private member_ `HINSTANCE InstanceHandle;`
- L530 _private member_ `bool bMinimized;`
- L532 _private member_ `bool bUsingHighPrecisionMouseInput;`
- L533 _private member_ `bool bCachedUseWorkerThreadForRawInput;`
- L534 _private member_ `HWND HighPrecisionMouseInputWindowHandle;`
- L535 _private member_ `HWND CaptureWindowHandle;`
- L537 _private member_ `bool bIsMouseAttached;`
- L539 _private member_ `bool bForceActivateByMouse;`
- L541 _private member_ `bool bForceNoGamepads;`
- L543 _private member_ `bool bConsumeAltSpace;`
- L545 _private member_ `TArray<FDeferredWindowsMessage> DeferredMessages;`
- L547 _private member_ `TArray<FDeferredWindowsDragDropOperation> DeferredDragDropOperations;`
- L550 _private member_ `TArray<IWindowsMessageHandler*> MessageHandlers;` — Registered Windows message handlers.
- L552 _private member_ `TArray<TSharedRef<FWindowsWindow>> Windows;`
- L555 _private member_ `TArray<TSharedPtr<class IInputDevice>> ExternalInputDevices;` — List of input devices implemented in external modules.
- L556 _private member_ `bool bHasLoadedInputPlugins;`
- L573 _private member_ `bool ModifierKeyState[EModifierKey::Count];` — Cached state of the modifier keys. True if the modifier key is pressed (or toggled in the case of caps lock), false otherwise
- L575 _private member_ `int32 bAllowedToDeferMessageProcessing;`
- L577 _private member_ `FAutoConsoleVariableRef CVarDeferMessageProcessing;`
- L579 _private member_ `FDisplayMetrics InitialDisplayMetrics;`
- L581 _private member_ `TSharedPtr<FWindowsTextInputMethodSystem> TextInputMethodSystem;`
- L583 _private member_ `TSharedPtr<FTaskbarList> TaskbarList;`
- L587 _private member_ `TUniquePtr<class FWindowsUIAManager> UIAManager;` — Handler for WM_GetObject messages that come in
- L591 _private member_ `STICKYKEYS StartupStickyKeys;` — Accessibility shortcut keys
- L592 _private member_ `TOGGLEKEYS StartupToggleKeys;`
- L593 _private member_ `FILTERKEYS StartupFilterKeys;`
- L607 _private member_ `TArray<TouchInfo> TouchInfoArray;` — Maps touch information such as TouchID PreviousLocation and HasMoved to windows touch IDs.
- L609 _private member_ `bool bSimulatingHighPrecisionMouseInputForRDP;`
- L611 _private member_ `FIntPoint LastCursorPoint;`
- L612 _private member_ `FIntPoint LastCursorPointPreWrap;`
- L613 _private member_ `int32 NumPreWrapMsgsToRespect;`
- L614 _private member_ `RECT ClipCursorRect;`
- L615 _private member_ `DWORD CachedDragAndDropKeyState;`
- L617 _private member_ `double RepeatTime[EMouseButtons::Invalid];`

#### struct `FWindowsApplication::RawMouseInputResult`  
`struct RawMouseInputResult`  
_L304-310_
- L306 _public member_ `bool bIsAbsoluteInput;`
- L307 _public member_ `bool bSimulateRelativeMovement;`
- L308 _public member_ `int32 DeltaX;`
- L309 _public member_ `int32 DeltaY;`

#### enum `FWindowsApplication::EForceMaxTouchpadSensitivityAsyncBehavior`  
`enum class EForceMaxTouchpadSensitivityAsyncBehavior : uint8`  
_L418-422_
- desc: On Windows 10 22H2 and later where we can set the touchpad sensitivity system wide setting force it to most sensitive so that touch swipes are not ignored while keyboard keys are being depressed. In Windows 11 24H2 a new api was added which can change this setting only for this app. We reccomend that this feature be exposed as a user setting which is enabled by default and hidden/disabled if SupportsForceMaxTouchpadSensitivity() returns false and that the CVar be used to activate it rather than directly calling ApplyForceMaxTouchpadSensitivity/RemoveForceMaxTouchpadSensitivity due to the complexity of handling the focus/exit/crash cases with the SetTouchpadParameters api. See WindowsApplication.cpp namespace UE::WindowsApplication::TouchpadSensitivity for more information about this system.
- L420 _public enumerator_ `AllowAsynchronous` — This function may defer the system call that actually changes the setting in order to avoid blocking for a long time.
- L421 _public enumerator_ `RequireBlocking` — This function will not return until the system call returns.

#### enum `FWindowsApplication::EForceMaxTouchpadSensitivityRestorationValues`  
`enum class EForceMaxTouchpadSensitivityRestorationValues : int32`  
_L432-441_
- desc: If we are using the system wide setting it is possible that we could crash and fail to set it back.  Call this function to find out if we have a system setting value we would like to restore after a crash. If this information was passed to a separate process (perhaps by writing it to a file) that process might be able to restore the setting after a crash.
- L434 _public enumerator_ `SystemCallFailed = -2` — Indicates we are in a mode where restoration is desirable, but the system call failed.  Most likely callers should do nothing.
- L435 _public enumerator_ `RestorationNotNeeded = -1` — Indicates restoration is unnecessary (either the system setting was already MostSensitive, we can't change the setting, or the system is fully capable of restoring itself.)
- L436 _public enumerator_ `TOUCHPAD_SENSITIVITY_LEVEL_MOST_SENSITIVE = 0x00000000` — These values one would restore with ::SystemParametersInfo(SPI_SETTOUCHPADPARAMETERS, ...
- L437 _public enumerator_ `TOUCHPAD_SENSITIVITY_LEVEL_HIGH_SENSITIVITY = 0x00000001`
- L438 _public enumerator_ `TOUCHPAD_SENSITIVITY_LEVEL_MEDIUM_SENSITIVITY = 0x00000002`
- L439 _public enumerator_ `TOUCHPAD_SENSITIVITY_LEVEL_LOW_SENSITIVITY = 0x00000003`
- L440 _public enumerator_ `TOUCHPAD_SENSITIVITY_LEVEL_LEAST_SENSITIVE = 0x00000004`

#### struct `FWindowsApplication::EModifierKey`  
`struct EModifierKey`  
_L558-571_

#### enum `FWindowsApplication::EModifierKey::Type`  
`enum Type`  
_L560-570_
- L562 _public enumerator_ `LeftShift` — VK_LSHIFT
- L563 _public enumerator_ `RightShift` — VK_RSHIFT
- L564 _public enumerator_ `LeftControl` — VK_LCONTROL
- L565 _public enumerator_ `RightControl` — VK_RCONTROL
- L566 _public enumerator_ `LeftAlt` — VK_LMENU
- L567 _public enumerator_ `RightAlt` — VK_RMENU
- L568 _public enumerator_ `CapsLock` — VK_CAPITAL
- L569 _public enumerator_ `Count`

#### struct `FWindowsApplication::TouchInfo`  
`struct TouchInfo`  
_L595-605_
- L597 _public member_ `bool HasMoved;`
- L598 _public member_ `FVector2D PreviousLocation;`
- L599 _public member_ `TOptional<int32> TouchID;`
- L601 _public function_ `TouchInfo() : HasMoved(false) , PreviousLocation(0.f, 0.f)`

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWindowsDesktop, Log, All);`
- L26 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWindowsDesktop, Log, All);`
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FWindowsApplication_OnWindowCreated, HWND);`
- L31 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FWindowsApplication_OnWindowCreated, HWND);`
- L33 _namespace_ `namespace ETaskbarProgressState`
- L161 _namespace_ `namespace EWindowsDragDropOperationType`

### `Source/Runtime/ApplicationCore/Public/Windows/WindowsApplicationErrorOutputDevice.h` (Public)


#### class `FWindowsApplicationErrorOutputDevice`  
`class FWindowsApplicationErrorOutputDevice : public FWindowsErrorOutputDevice`  
_L11-15_
- inherits: `FWindowsErrorOutputDevice`
- desc: Windows implementation of console log window, utilizing the Win32 console API
- L14 _protected prototype_ `virtual void HandleErrorRestoreUI() override;`

### `Source/Runtime/ApplicationCore/Public/Windows/WindowsConfigRules.h` (Public)


#### class `FWindowsConfigRules`  
`class FWindowsConfigRules : public FGenericConfigRules`  
_L14-51_
- inherits: `FGenericConfigRules`
- L16 _private member_ `static TMap<FString, FString> PredefinedConfigRuleVars;`
- L17 _private member_ `static TMap<FString, FString> ConfigRuleVariablesMap;`
- L18 _private member_ `static TArray<uint8> ConfigRulesBytes;`
- L23 _public prototype_ `static void Init();` — Finds the best config rules file and loads it for parsing
- L34 _public prototype_ `static void Parse();` — Parse the loaded config rules file and updates the variable map. A concrete use case for Reparsing is when some data in PredefinedVars is not available during the first parse and we'd like to update the RulesMap with new data. E.g. RHI might not be initialized during first Parse but we'd still like to apply other values before RHIInit. Then during RHIInit call Parse() again to get updated data. Can be reparsed until EndOfEngineInit or Release()
- L37 _public prototype_ `static void SetStandardPredefinedVars();` — Sets a number of standard predefined variables such as build version, CPU information, etc.
- L43 _public prototype_ `static void SetRHIPredefinedVars(const FString& DynamicRHIModuleName, const FString& RequestedFeatureLevel);` — Sets a number of RHI-specific predefined variables such as adapter name, driver version, etc. Requires the global GRHIAdapterName to be set by the time this is called.
- L45 _public prototype_ `static void SetAdditionalPredefinedVars(TMap<FString, FString>&& AdditionalPredefinedVars);`
- L48 _public prototype_ `static void Release();` — Frees resources used to parse config rules
- L50 _public function_ `static const TMap<FString, FString>& GetConfigRulesMap()`

#### Free symbols / members of external scopes

- L6 _macro_ `#define WITH_WINDOWS_CONFIGRULES 0`

### `Source/Runtime/ApplicationCore/Public/Windows/WindowsConsoleOutputDevice.h` (Public)


#### class `FWindowsConsoleOutputDevice`  
`class FWindowsConsoleOutputDevice : public FOutputDeviceConsole`  
_L12-102_
- inherits: `FOutputDeviceConsole`
- desc: Windows implementation of console log window, utilizing the Win32 console API
- L16 _private member_ `Windows::HANDLE ConsoleHandle;` — Handle to the console log window
- L19 _private member_ `bool OverrideColorSet;` — true if the color is currently set by the caller
- L22 _private member_ `bool bIsAttached;` — true if this console device is attached to an existing console window.
- L25 _private member_ `ELogVerbosity::Type AllowedLogVerbosity = ELogVerbosity::All;` — maximum allowed log verbosity
- L44 _private member_ `TArray<FLogHighlight, TInlineAllocator<8>> LogHighlights;` — Log categories to be highlighted
- L57 _private member_ `TArray<FLogStringHighlight, TInlineAllocator<8>> LogStringHighlights;` — Log strings to be highlighted
- L63 _private prototype_ `void SaveToINI();` — Saves the console window's position and size to the game .ini
- L70 _public prototype_ `FWindowsConsoleOutputDevice();` — Constructor, setting console control handler.
- L71 _public prototype_ `~FWindowsConsoleOutputDevice();`
- L78 _public prototype_ `virtual void Show( bool ShowWindow );` — Shows or hides the console window. @param ShowWindow	Whether to show (true) or hide (false) the console window.
- L85 _public prototype_ `virtual bool IsShown();` — Returns whether console is currently shown or not @return true if console is shown, false otherwise
- L87 _public prototype_ `virtual bool IsAttached();`
- L89 _public prototype_ `virtual bool CanBeUsedOnAnyThread() const override;`
- L90 _public prototype_ `virtual bool CanBeUsedOnPanicThread() const override;`
- L98 _public prototype_ `virtual void Serialize( const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category, const double Time ) override;` — Displays text on the console and scrolls if necessary. @param Data	Text to display @param Event	Event type, used for filtering/ suppression
- L99 _public prototype_ `virtual void Serialize( const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category ) override;`
- L101 _public prototype_ `void SetColor( const TCHAR* Color );`

#### struct `FWindowsConsoleOutputDevice::FLogHighlight`  
`struct FLogHighlight`  
_L29-41_
- desc: An entry for log category highlighting
- L32 _public member_ `FName Category;` — The category to highlight
- L35 _public member_ `const TCHAR* Color = nullptr;` — The 4 digit color code to highlight with
- L37 _public function_ `bool operator == (FName InCategory) const`

#### struct `FWindowsConsoleOutputDevice::FLogStringHighlight`  
`struct FLogStringHighlight`  
_L47-54_
- desc: An entry for log string highlighting
- L50 _public member_ `TArray<TCHAR, TInlineAllocator<128>> SearchString;` — The string to search for and highlight
- L53 _public member_ `const TCHAR* Color = nullptr;` — The 4 digit color code to highlight with

### `Source/Runtime/ApplicationCore/Public/Windows/WindowsConsoleOutputDevice2.h` (Public)


#### class `FWindowsConsoleOutputDevice2`  
`class FWindowsConsoleOutputDevice2 final : public FOutputDeviceConsole`  
_L12-113_
- inherits: `FOutputDeviceConsole`
- desc: Windows implementation of console log window, utilizing the Win32 console API
- L15 _private member_ `uint16 TextAttribute;`
- L18 _private member_ `bool OverrideColorSet;` — true if the color is currently set by the caller
- L21 _private member_ `FConsoleWindow* Window;`
- L22 _private member_ `FRWLock WindowRWLock;`
- L23 _private member_ `TArray<FString> CommandHistory;`
- L24 _private member_ `int32 CommandHistoryCursor = 0;`
- L27 _private member_ `ELogVerbosity::Type AllowedLogVerbosity = ELogVerbosity::All;` — maximum allowed log verbosity
- L46 _private member_ `TArray<FLogHighlight, TInlineAllocator<8>> LogHighlights;` — Log categories to be highlighted
- L59 _private member_ `TArray<FLogStringHighlight, TInlineAllocator<8>> LogStringHighlights;` — Log strings to be highlighted
- L65 _private prototype_ `void SaveToINI();` — Saves the console window's position and size to the game .ini
- L67 _private prototype_ `static const FString& GetConfigFilename();`
- L74 _public prototype_ `FWindowsConsoleOutputDevice2();` — Constructor, setting console control handler.
- L75 _public prototype_ `~FWindowsConsoleOutputDevice2();`
- L82 _public prototype_ `virtual void Show( bool ShowWindow );` — Shows or hides the console window. @param ShowWindow	Whether to show (true) or hide (false) the console window.
- L89 _public prototype_ `virtual bool IsShown();` — Returns whether console is currently shown or not @return true if console is shown, false otherwise
- L91 _public prototype_ `virtual bool IsAttached();`
- L93 _public prototype_ `virtual bool CanBeUsedOnAnyThread() const override;`
- L101 _public prototype_ `virtual void Serialize( const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category, const double Time ) override;` — Displays text on the console and scrolls if necessary. @param Data	Text to display @param Event	Event type, used for filtering/ suppression
- L102 _public prototype_ `virtual void Serialize( const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category ) override;`
- L104 _public prototype_ `void SetColor( const TCHAR* Color );`
- L106 _public prototype_ `bool GetPreviousCommand(FString& OutCommand);`
- L107 _public prototype_ `bool GetNextCommand(FString& OutCommand);`
- L108 _public prototype_ `bool GetLastCommand(FString& OutCommand);`
- L109 _public prototype_ `void AddCommand(const FString& InCommand);`
- L111 _private prototype_ `FWindowsConsoleOutputDevice2(const FWindowsConsoleOutputDevice2&) = delete;`
- L112 _private prototype_ `FWindowsConsoleOutputDevice2& operator=(const FWindowsConsoleOutputDevice2&) = delete;`

#### struct `FWindowsConsoleOutputDevice2::FLogHighlight`  
`struct FLogHighlight`  
_L31-43_
- desc: An entry for log category highlighting
- L34 _public member_ `FName Category;` — The category to highlight
- L37 _public member_ `const TCHAR* Color = nullptr;` — The 4 digit color code to highlight with
- L39 _public function_ `bool operator == (FName InCategory) const`

#### struct `FWindowsConsoleOutputDevice2::FLogStringHighlight`  
`struct FLogStringHighlight`  
_L49-56_
- desc: An entry for log string highlighting
- L52 _public member_ `TStringBuilder<128> SearchString;` — The string to search for and highlight
- L55 _public member_ `const TCHAR* Color = nullptr;` — The 4 digit color code to highlight with

### `Source/Runtime/ApplicationCore/Public/Windows/WindowsCursor.h` (Public)


#### class `FWindowsCursor`  
`class FWindowsCursor : public ICursor`  
_L10-56_
- inherits: `ICursor`
- L14 _public prototype_ `FWindowsCursor();`
- L16 _public prototype_ `virtual ~FWindowsCursor();`
- L18 _public prototype_ `virtual void* CreateCursorFromFile(const FString& InPathToCursorWithoutExtension, FVector2D HotSpot) override;`
- L20 _public function_ `virtual bool IsCreateCursorFromRGBABufferSupported() const override`
- L25 _public prototype_ `virtual void* CreateCursorFromRGBABuffer(const FColor* Pixels, int32 Width, int32 Height, FVector2D InHotSpot) override;`
- L27 _public prototype_ `virtual FVector2D GetPosition() const override;`
- L29 _public prototype_ `virtual void SetPosition( const int32 X, const int32 Y ) override;`
- L31 _public prototype_ `virtual void SetType( const EMouseCursor::Type InNewCursor ) override;`
- L33 _public function_ `virtual EMouseCursor::Type GetType() const override`
- L38 _public prototype_ `virtual void GetSize( int32& Width, int32& Height ) const override;`
- L40 _public prototype_ `virtual void Show( bool bShow ) override;`
- L42 _public prototype_ `virtual void Tick() override;`
- L43 _public prototype_ `virtual void Lock( const RECT* const Bounds ) override;`
- L45 _public prototype_ `virtual void SetTypeShape(EMouseCursor::Type InCursorType, void* CursorHandle) override;`
- L49 _private member_ `EMouseCursor::Type CurrentType;`
- L52 _private member_ `HCURSOR CursorHandles[ EMouseCursor::TotalCursorCount ];` — Cursors
- L55 _private member_ `HCURSOR CursorOverrideHandles[EMouseCursor::TotalCursorCount];` — Override Cursors

### `Source/Runtime/ApplicationCore/Public/Windows/WindowsFeedbackContext.h` (Public)


#### class `FWindowsFeedbackContext`  
`class FWindowsFeedbackContext : public FFeedbackContext`  
_L15-25_
- inherits: `FFeedbackContext`
- desc: Feedback context implementation for windows.
- L18 _private member_ `FContextSupplier* Context = nullptr;` — Context information for warning and error messages
- L21 _public prototype_ `bool YesNof(const FText& Question) override;`
- L23 _public function_ `FContextSupplier* GetContext() const`
- L24 _public function_ `void SetContext(FContextSupplier* InContext)`

### `Source/Runtime/ApplicationCore/Public/Windows/WindowsPlatformApplicationMisc.h` (Public)


#### struct `FWindowsPlatformApplicationMisc`  
`struct FWindowsPlatformApplicationMisc : public FGenericPlatformApplicationMisc`  
_L7-41_
- inherits: `FGenericPlatformApplicationMisc`
- L9 _public prototype_ `static void PreInit();`
- L10 _public prototype_ `static void LoadStartupModules();`
- L11 _public prototype_ `static class FOutputDeviceConsole* CreateConsoleOutputDevice();`
- L12 _public prototype_ `static class FOutputDeviceError* GetErrorOutputDevice();`
- L13 _public prototype_ `static class FFeedbackContext* GetFeedbackContext();`
- L14 _public prototype_ `static class GenericApplication* CreateApplication();`
- L15 _public prototype_ `static void RequestMinimize();`
- L16 _public prototype_ `static bool IsThisApplicationForeground();`
- L17 _public prototype_ `static int32 GetAppIcon();`
- L18 _public prototype_ `static void PumpMessages(bool bFromMainLoop);`
- L19 _public prototype_ `static void PreventScreenSaver();`
- L20 _public prototype_ `static struct FLinearColor GetScreenPixelColor(const FVector2D& InScreenPos, float InGamma = 1.0f);`
- L21 _public prototype_ `static void SetHighDPIMode();`
- L22 _public prototype_ `static bool GetWindowTitleMatchingText(const TCHAR* TitleStartsWith, FString& OutTitle);`
- L23 _public prototype_ `static float GetDPIScaleFactorAtPoint(float X, float Y);`
- L24 _public prototype_ `static void ClipboardCopy(const TCHAR* Str);`
- L25 _public prototype_ `static void ClipboardPaste(class FString& Dest);`
- L29 _public prototype_ `static int32 GetMonitorDPI(const FMonitorInfo& MonitorInfo);` — Function should retrieve the DPI value for the provided monitor information structure
- L30 _public prototype_ `static int32 GetMonitorDPI(void* NativeHandle);`
- L39 _public prototype_ `static FGPUInfo GetBestGPUInfo();`

#### struct `FWindowsPlatformApplicationMisc::FGPUInfo`  
`struct FGPUInfo`  
_L32-37_
- L34 _public member_ `uint32 VendorId = 0;`
- L35 _public member_ `uint32 DeviceId = 0;`
- L36 _public member_ `uint64 DedicatedVideoMemory = 0;`

#### Free symbols / members of external scopes

- L44 _typedef_ `typedef FWindowsPlatformApplicationMisc FPlatformApplicationMisc;`

### `Source/Runtime/ApplicationCore/Public/Windows/WindowsPlatformSplash.h` (Public)


#### struct `FWindowsPlatformSplash`  
`struct FWindowsPlatformSplash : public FGenericPlatformSplash`  
_L11-49_
- inherits: `FGenericPlatformSplash`
- desc: Windows splash implementation.
- L15 _public prototype_ `static void Show();` — Show the splash screen.
- L18 _public prototype_ `static void Hide();` — Hide the splash screen.
- L25 _public prototype_ `static void SetProgress(int ProgressPercent);` — Sets the progress displayed on the application icon (for startup/loading progress). @param ProgressPercent Progress value in percent.
- L34 _public prototype_ `static void SetSplashText( const SplashTextType::Type InType, const FText& InText );`
- L37 _public prototype_ `static void SetSplashImage(const SplashImageType::Type InType, const TCHAR* InFilename);` — Sets the image to be assigned to the specific slot
- L40 _public prototype_ `static void RegisterUserSplashText(const SplashTextType::Type InType, const FPlatformRect& InRect, ESplashTextSizeType InSize, ESplashTextBrightnessType InBrightness, ESplashTextFlags InFlags = ESplashTextFlags::None);` — Registers a new licensee text. Only User types are allowed, and only before the splash screen is initialized!
- L43 _public prototype_ `static void RegisterUserSplashImage(const SplashImageType::Type InType, const FIntPoint& InPos, const TCHAR* InFilename);` — Registers a new licensee image. Only User types are allowed, and only before the splash screen is initialized!
- L48 _public prototype_ `static bool IsShown();` — Return whether the splash screen is being shown or not

#### Free symbols / members of external scopes

- L52 _typedef_ `typedef FWindowsPlatformSplash FPlatformSplash;`

### `Source/Runtime/ApplicationCore/Public/Windows/WindowsPlatformSurvey.h` (Public)


#### struct `FWindowsPlatformSurvey`  
`struct FWindowsPlatformSurvey : public FGenericPlatformSurvey`  
_L12-35_
- inherits: `FGenericPlatformSurvey`
- desc: Windows implementation of FGenericPlatformSurvey.
- L16 _public prototype_ `static bool GetSurveyResults( FHardwareSurveyResults& OutResults, bool bWait = false );` — Start, or check on, the hardware survey
- L23 _private prototype_ `static bool GetSubComponentIndex( struct IProvideWinSATResultsInfo* WinSATResults, FHardwareSurveyResults& OutSurveyResults, int32 SubComponent, float& OutSubComponentIndex );` — Helper used by SurveyHardware to get the Windows Experience Index score for individual sub-components @return True if successful
- L29 _private prototype_ `static bool GetLineFollowing(const FString& Token, const TArray<FString>& Lines, FString& OutString, int32 NthHit = 0);` — Find the line that contains Token and return the contents of the line after the token @return True if the line is found and the function has written the following string to OutString
- L34 _private prototype_ `static bool GetNamedSection(FString SectionName, const TArray<FString>& InLines, TArray<FString>& OutSectionLines);` — Look for a section of a file beginning with SectionName

#### Free symbols / members of external scopes

- L38 _typedef_ `typedef FWindowsPlatformSurvey FPlatformSurvey;`

### `Source/Runtime/ApplicationCore/Public/Windows/WindowsRemoteConsoleOutputDevice.h` (Public)


#### class `FPlaceholder_WindowsRemoteConsoleOutputDevice`  
`class FPlaceholder_WindowsRemoteConsoleOutputDevice : public FOutputDeviceConsole`  
_L24-43_
- inherits: `FOutputDeviceConsole`
- desc: Implementation of console logging for a remote windows deployment Likely placeholder until the wdremote tools support process lifetime management & output redirection. Paired with Placeholder_RemoteWinProcessMonitor in UAT Not enabled in shipping builds by default (see WITH_REMOTEWIN_CONSOLE)
- L29 _public prototype_ `FPlaceholder_WindowsRemoteConsoleOutputDevice( const FString& RemoteConsoleHost );` — Default constructor.
- L32 _public prototype_ `~FPlaceholder_WindowsRemoteConsoleOutputDevice();` — Destructor.
- L35 _public prototype_ `void Serialize( const TCHAR* Msg, ELogVerbosity::Type Verbosity, const class FName& Category );` — Sends the string to the remote logging host
- L38 _private function_ `virtual void Show(bool ShowWindow)`
- L39 _private function_ `virtual bool IsShown()`
- L41 _private member_ `class FRemoteConsoleRunnable* Runnable;`
- L42 _private member_ `class FRunnableThread* Thread;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define WITH_REMOTEWIN_CONSOLE (!UE_BUILD_SHIPPING) && (!WITH_EDITOR)`

### `Source/Runtime/ApplicationCore/Public/Windows/WindowsTextInputMethodSystem.h` (Public)


#### class `FTSFActivationProxy`  
`class FTSFActivationProxy : public ITfInputProcessorProfileActivationSink , public ITfActiveLanguageProfileNotifySink`  
_L20-59_
- inherits: `ITfInputProcessorProfileActivationSink,ITfActiveLanguageProfileNotifySink`
- L25 _public function_ `FTSFActivationProxy(FWindowsTextInputMethodSystem* InOwner) : TSFProfileCookie(TF_INVALID_COOKIE) , TSFLanguageCookie(TF_INVALID_COOKIE) , Owner(InOwner) , ReferenceCount(1)`
- L32 _public prototype_ `virtual ~FTSFActivationProxy() = default;`
- L35 _public prototype_ `STDMETHODIMP QueryInterface(REFIID riid, void **ppvObj) override;` — IUnknown Interface Begin
- L36 _public prototype_ `STDMETHODIMP_(ULONG) AddRef() override;`
- L37 _public prototype_ `STDMETHODIMP_(ULONG) Release() override;`
- L41 _public prototype_ `STDMETHODIMP OnActivated(DWORD dwProfileType, LANGID langid, __RPC__in REFCLSID clsid, __RPC__in REFGUID catid, __RPC__in REFGUID guidProfile, HKL hkl, DWORD dwFlags) override;` — ITfInputProcessorProfileActivationSink Interface Begin
- L45 _public prototype_ `STDMETHODIMP OnActivated(REFCLSID clsid, REFGUID guidProfile, BOOL fActivated) override;` — ITfActiveLanguageProfileNotifySink Interface Begin
- L50 _public member_ `DWORD TSFProfileCookie;`
- L51 _public member_ `DWORD TSFLanguageCookie;`
- L55 _private member_ `FWindowsTextInputMethodSystem* Owner;`
- L58 _private member_ `ULONG ReferenceCount;` — Reference count for IUnknown Implementation

#### class `FWindowsTextInputMethodSystem`  
`class FWindowsTextInputMethodSystem : public ITextInputMethodSystem`  
_L62-148_
- inherits: `ITextInputMethodSystem`
- L69 _public prototype_ `virtual ~FWindowsTextInputMethodSystem() = default;`
- L71 _public prototype_ `bool Initialize();`
- L72 _public prototype_ `void Terminate();`
- L74 _public prototype_ `int32 ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);`
- L80 _public prototype_ `virtual void ApplyDefaults(const TSharedRef<FGenericWindow>& InWindow) override;`
- L81 _public prototype_ `virtual TSharedPtr<ITextInputMethodChangeNotifier> RegisterContext(const TSharedRef<ITextInputMethodContext>& Context) override;`
- L82 _public prototype_ `virtual void UnregisterContext(const TSharedRef<ITextInputMethodContext>& Context) override;`
- L83 _public prototype_ `virtual void ActivateContext(const TSharedRef<ITextInputMethodContext>& Context) override;`
- L84 _public prototype_ `virtual void DeactivateContext(const TSharedRef<ITextInputMethodContext>& Context) override;`
- L85 _public prototype_ `virtual bool IsActiveContext(const TSharedRef<ITextInputMethodContext>& Context) const override;`
- L89 _private prototype_ `void LogActiveInputMethod();`
- L93 _private prototype_ `bool InitializeIMM();`
- L94 _private prototype_ `void UpdateIMMProperty(HKL KeyboardLatoutHandle);`
- L95 _private prototype_ `bool ShouldDrawIMMCompositionString() const;`
- L96 _private prototype_ `void UpdateIMMWindowPositions(HIMC IMMContext);`
- L97 _private prototype_ `void BeginIMMComposition();`
- L98 _private prototype_ `void EndIMMComposition();`
- L99 _private prototype_ `void CancelIMMComposition();`
- L103 _private prototype_ `bool InitializeTSF();`
- L104 _private prototype_ `void OnIMEActivationStateChanged(const bool bIsEnabled);`
- L105 _private prototype_ `void ClearStaleWindowHandles();`
- L114 _private member_ `} CurrentAPI;`
- L117 _private member_ `TComPtr<ITfInputProcessorProfiles> TSFInputProcessorProfiles;` — TSF Implementation
- L118 _private member_ `TComPtr<ITfInputProcessorProfileMgr> TSFInputProcessorProfileManager;`
- L119 _private member_ `TComPtr<ITfThreadMgr> TSFThreadManager;`
- L120 _private member_ `TfClientId TSFClientId = 0;`
- L121 _private member_ `TComPtr<ITfDocumentMgr> TSFDisabledDocumentManager;`
- L122 _private member_ `TComPtr<FTSFActivationProxy> TSFActivationProxy;`
- L125 _private member_ `HIMC IMMContextId = nullptr;` — IMM Implementation
- L126 _private member_ `DWORD IMMProperties = 0;`
- L143 _private member_ `TSharedPtr<ITextInputMethodContext> ActiveContext;`
- L145 _private member_ `TMap< TWeakPtr<ITextInputMethodContext>, FInternalContext > ContextToInternalContextMap;`
- L147 _private member_ `TSet<TWeakPtr<FGenericWindow>> KnownWindows;`

#### enum `FWindowsTextInputMethodSystem::EAPI`  
`enum class EAPI`  
_L109-114_
- L111 _public enumerator_ `Unknown`
- L112 _public enumerator_ `IMM`
- L113 _public enumerator_ `TSF`

#### struct `FWindowsTextInputMethodSystem::FInternalContext`  
`struct FInternalContext`  
_L128-141_
- L130 _public member_ `HWND WindowHandle = nullptr;`
- L132 _public member_ `TComPtr<FTextStoreACP> TSFContext;`
- L140 _public member_ `} IMMContext;`

#### struct `FWindowsTextInputMethodSystem::FInternalContext::(anonymous)`  
``  
_L135-140_

#### Free symbols / members of external scopes

- L136 _member_ `bool IsComposing = false;` (scope `FWindowsTextInputMethodSystem::FInternalContext::__anon442117190108`)
- L137 _member_ `bool IsDeactivating = false;` (scope `FWindowsTextInputMethodSystem::FInternalContext::__anon442117190108`)
- L138 _member_ `int32 CompositionBeginIndex = 0;` (scope `FWindowsTextInputMethodSystem::FInternalContext::__anon442117190108`)
- L139 _member_ `uint32 CompositionLength = 0;` (scope `FWindowsTextInputMethodSystem::FInternalContext::__anon442117190108`)

### `Source/Runtime/ApplicationCore/Public/Windows/WindowsWindow.h` (Public)


#### class `FWindowsWindow`  
`class FWindowsWindow : public FGenericWindow , public IDropTarget`  
_L23-231_
- inherits: `FGenericWindow,IDropTarget`
- desc: A platform specific implementation of FNativeWindow. Native Windows provide platform-specific backing for and are always owned by an SWindow.
- L30 _public member_ `static const TCHAR AppWindowClass[];` — Win32 requirement: see CreateWindowEx and RegisterClassEx.
- L35 _public prototype_ `~FWindowsWindow();` — Destructor.
- L38 _public prototype_ `static TSharedRef<FWindowsWindow> Make();` — Create a new FWin32Window.
- L45 _public prototype_ `HWND GetHWnd() const;` — Gets the Window's handle. @return The window's HWND handle.
- L47 _public prototype_ `void Initialize( class FWindowsApplication* const Application, const TSharedRef<FGenericWindowDefinition>& InDefinition, HINSTANCE InHInstance, const TSharedPtr<FWindowsWindow>& InParent, const bool bShowImmediately );`
- L54 _public prototype_ `bool IsRegularWindow() const;` — Sets the window text (usually the title but can also be text content for things like controls). @param Text The window's title or content text
- L62 _public prototype_ `void AdjustWindowRegion(int32 Width, int32 Height);` — Sets the window region to specified dimensions. @param Width The width of the window region (in pixels). @param Height The height of the window region (in pixels).
- L65 _public prototype_ `virtual void AdjustCachedSize(FVector2D& Size) const override;` — @return	Gives the native window a chance to adjust our stored window size before we cache it off.
- L67 _public function_ `virtual float GetDPIScaleFactor() const override`
- L72 _public function_ `virtual void SetDPIScaleFactor(float Value) override`
- L78 _public prototype_ `virtual bool IsManualManageDPIChanges() const override;` — determines whether or not this window does its own DPI management
- L81 _public prototype_ `virtual void SetManualManageDPIChanges(const bool bManualDPIChanges) override;` — call with a true argument if this window need to do its custom size management in response to DPI variations
- L83 _public function_ `bool IsInModalSizeLoop() const`
- L84 _public function_ `void EnterModalSizeLoop()`
- L85 _public function_ `void ExitModalSizeLoop()`
- L88 _public prototype_ `void OnParentWindowMinimized();` — Called when our parent window is minimized (which will in turn cause us to become minimized).
- L91 _public prototype_ `void OnParentWindowRestored();` — Called when our parent window is restored (which will in turn cause us to become restored).
- L94 _public prototype_ `void OnTransparencySupportChanged(EWindowTransparency NewTransparency);` — Called by the owning application when the level of transparency support has changed
- L96 _public function_ `float GetAspectRatio() const`
- L99 _public prototype_ `bool IsEnabled();` — @return True if the window is enabled
- L103 _public prototype_ `TArray<FColor> GetWindowPixels(uint32& OutWidth, uint32& OutHeight);` — Attempts to retrieve the window's pixels using PrintWindow (https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-printwindow). Only the client area's pixels are retrieved, which excludes the title bar, border, etc.
- L109 _public prototype_ `virtual void ReshapeWindow( int32 X, int32 Y, int32 Width, int32 Height ) override;`
- L110 _public prototype_ `virtual bool GetFullScreenInfo( int32& X, int32& Y, int32& Width, int32& Height ) const override;`
- L111 _public prototype_ `virtual void MoveWindowTo ( int32 X, int32 Y ) override;`
- L112 _public prototype_ `virtual void BringToFront( bool bForce = false ) override;`
- L113 _public prototype_ `virtual void HACK_ForceToFront() override;`
- L114 _public prototype_ `virtual void Destroy() override;`
- L115 _public prototype_ `virtual void Minimize() override;`
- L116 _public prototype_ `virtual void Maximize() override;`
- L117 _public prototype_ `virtual void Restore() override;`
- L118 _public prototype_ `virtual void Show() override;`
- L119 _public prototype_ `virtual void Hide() override;`
- L120 _public prototype_ `virtual void SetWindowMode( EWindowMode::Type NewWindowMode ) override;`
- L121 _public function_ `virtual EWindowMode::Type GetWindowMode() const override`
- L122 _public prototype_ `virtual bool IsMaximized() const override;`
- L123 _public prototype_ `virtual bool IsMinimized() const override;`
- L124 _public prototype_ `virtual bool IsVisible() const override;`
- L125 _public prototype_ `virtual bool GetRestoredDimensions(int32& X, int32& Y, int32& Width, int32& Height) override;`
- L126 _public prototype_ `virtual void SetWindowFocus() override;`
- L127 _public prototype_ `virtual void SetOpacity( const float InOpacity ) override;`
- L128 _public prototype_ `virtual void Enable( bool bEnable ) override;`
- L129 _public prototype_ `virtual bool IsPointInWindow( int32 X, int32 Y ) const override;`
- L130 _public prototype_ `virtual int32 GetWindowBorderSize() const override;`
- L131 _public prototype_ `virtual int32 GetWindowTitleBarSize() const override;`
- L132 _public function_ `virtual void* GetOSWindowHandle() const override`
- L133 _public prototype_ `virtual bool IsForegroundWindow() const override;`
- L134 _public prototype_ `virtual bool SupportsDynamicCursorLock() const override;`
- L135 _public prototype_ `virtual bool IsFullscreenSupported() const override;`
- L136 _public prototype_ `virtual void SetText(const TCHAR* const Text) override;`
- L137 _public prototype_ `virtual void DrawAttention(const FWindowDrawAttentionParameters& Parameters) override;`
- L143 _public prototype_ `HRESULT STDCALL QueryInterface(REFIID iid, void ** ppvObject) override;`
- L144 _public prototype_ `ULONG STDCALL AddRef(void) override;`
- L145 _public prototype_ `ULONG STDCALL Release(void) override;`
- L151 _public prototype_ `virtual HRESULT STDCALL DragEnter( __RPC__in_opt IDataObject *DataObjectPointer, ::DWORD KeyState, POINTL CursorPosition, __RPC__inout ::DWORD *CursorEffect) override;`
- L152 _public prototype_ `virtual HRESULT STDCALL DragOver( ::DWORD KeyState, POINTL CursorPosition, __RPC__inout ::DWORD *CursorEffect) override;`
- L153 _public prototype_ `virtual HRESULT STDCALL DragLeave( void ) override;`
- L154 _public prototype_ `virtual HRESULT STDCALL Drop( __RPC__in_opt IDataObject *DataObjectPointer, ::DWORD KeyState, POINTL CursorPosition, __RPC__inout ::DWORD *CursorEffect) override;`
- L159 _private prototype_ `FWindowsWindow();` — Protect the constructor; only TSharedRefs of this class can be made.
- L161 _private prototype_ `void UpdateVisibility();`
- L170 _private prototype_ `HRGN MakeWindowRegionObject(bool bForQuery) const;` — Creates an HRGN for the window's current region.  Remember to delete the returned handle when you're done with it using ::DeleteObject, unless you're passing it to SetWindowRgn(), which will absorb the reference itself. @param bForQuery Bypasses situational behavior compensation, so that the same compensation does not also need to be applied to the queried location.
- L172 _private prototype_ `void DisableTouchFeedback();`
- L174 _private prototype_ `int32 GetWin32BorderSize() const;`
- L179 _private member_ `FWindowsApplication* OwningApplication;` — The application that owns this window.
- L182 _private member_ `HWND HWnd;` — The window's handle.
- L185 _private member_ `int32 RegionWidth;` — Store the window region size for querying whether a point lies within the window.
- L186 _private member_ `int32 RegionHeight;`
- L189 _private member_ `EWindowMode::Type WindowMode;` — The mode that the window is in (windowed, fullscreen, windowedfullscreen )
- L192 _private member_ `int32 OLEReferenceCount;` — This object's reference count (for the IUnknown interface).
- L195 _private member_ `WINDOWPLACEMENT PreFullscreenWindowPlacement;` — The placement of the window before it entered a fullscreen state.
- L198 _private member_ `WINDOWPLACEMENT PreParentMinimizedWindowPlacement;` — The placement of the window before it entered a minimized state due to its parent window being minimized.
- L204 _private member_ `int32 VirtualWidth;` — Virtual width and height of the window.  This is only different than the actual width and height for windows which we're trying to optimize because their size changes frequently.  We'll create a larger window and have Windows draw it "cropped" so that it appears smaller, rather than actually resizing it and incurring a GPU buffer resize performance hit
- L205 _private member_ `int32 VirtualHeight;`
- L208 _private member_ `float AspectRatio;` — Current aspect ratio of window's client area
- L211 _private member_ `bool bIsVisible : 1;` — Whether the window is currently shown
- L214 _private member_ `bool bIsFirstTimeVisible : 1;` — Whether the window is yet to have its first Show() call. This is set false after first Show().
- L217 _private member_ `bool bInitiallyMinimized : 1;` — We cache the min/max state for any Minimize, Maximize, or Restore calls that were made before the first Show
- L218 _private member_ `bool bInitiallyMaximized : 1;`
- L224 _private member_ `float DPIScaleFactor;` — Ratio of pixels to SlateUnits in this window. E.g. DPIScale of 2.0 means there is a 2x2 pixel square for every 1x1 SlateUnit.
- L227 _private member_ `bool bHandleManualDPIChanges = false;` — when true the window is responsible for its own size adjustments in response to a DPI change
- L230 _private member_ `bool bInModalSizeLoop = false;` — when true the window in the middle of a windows modal size loop
