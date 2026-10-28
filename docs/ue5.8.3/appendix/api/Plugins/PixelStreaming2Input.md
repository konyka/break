# Plugins / PixelStreaming2Input

- module root: `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input`
- headers: 16; symbols: 414
- symbol kinds: class=11, delegate=3, enum=5, enumerator=25, externvar=57, function=24, macro=3, member=59, namespace=22, prototype=193, struct=8, typedef=3, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, HeadMountedDisplay, Json, PixelStreaming2Settings, Slate, SlateCore
- PublicDependencyModuleNames: ApplicationCore, Core, InputCore, InputDevice, PixelStreaming2HMD, XRBase

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Internal/InputHandler.h` (Internal)


#### class `UE::PixelStreaming2Input::FPixelStreaming2InputHandler`  
`class FPixelStreaming2InputHandler : public IPixelStreaming2InputHandler, public FXRMotionControllerBase`  
_L14-245_
- inherits: `IPixelStreaming2InputHandler,FXRMotionControllerBase`
- L17 _public prototype_ `FPixelStreaming2InputHandler();`
- L18 _public prototype_ `virtual ~FPixelStreaming2InputHandler();`
- L20 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L23 _public function_ `virtual void SendControllerEvents() override` — Poll for controller state and send events if needed
- L26 _public prototype_ `virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InTargetHandler) override;` — Set which MessageHandler will route input
- L29 _public prototype_ `virtual void SetCommandHandler(const FString& CommandName, const CommandHandlerFn& Handler) override;` — Register a custom function to execute when command JSON is received.
- L31 _public prototype_ `virtual void SetElevatedCheck(const TFunction<bool(FString)>& CheckFn) override;`
- L32 _public prototype_ `virtual bool IsElevated(const FString& Id) override;`
- L34 _public prototype_ `virtual TSharedPtr<IPixelStreaming2DataProtocol> GetToStreamerProtocol() override;`
- L35 _public prototype_ `virtual TSharedPtr<IPixelStreaming2DataProtocol> GetFromStreamerProtocol() override;`
- L38 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — Exec handler to allow console commands to be passed through for debugging
- L43 _public prototype_ `virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;` — IInputInterface pass through functions
- L44 _public prototype_ `virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues& values) override;`
- L45 _public prototype_ `virtual void OnMessage(FString SourceId, TArray<uint8> Buffer) override;`
- L46 _public prototype_ `virtual void SetTargetWindow(TWeakPtr<SWindow> InWindow) override;`
- L47 _public prototype_ `virtual TWeakPtr<SWindow> GetTargetWindow() override;`
- L48 _public prototype_ `virtual void SetTargetViewport(TWeakPtr<SViewport> InViewport) override;`
- L49 _public prototype_ `virtual TWeakPtr<SViewport> GetTargetViewport() override;`
- L50 _public prototype_ `virtual void SetTargetScreenRect(TWeakPtr<FIntRect> InScreenRect) override;`
- L51 _public prototype_ `virtual TWeakPtr<FIntRect> GetTargetScreenRect() override;`
- L52 _public function_ `virtual bool IsFakingTouchEvents() const override`
- L53 _public prototype_ `virtual void RegisterMessageHandler(const FString& MessageType, const MessageHandlerFn& Handler) override;`
- L54 _public prototype_ `virtual MessageHandlerFn FindMessageHandler(const FString& MessageType) override;`
- L55 _public function_ `virtual void SetInputType(EPixelStreaming2InputType InInputType) override`
- L57 _public prototype_ `virtual FName GetMotionControllerDeviceTypeName() const override;` — IMotionController Interface
- L58 _public prototype_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, float WorldToMetersScale) const override;`
- L59 _public prototype_ `virtual ETrackingStatus GetControllerTrackingStatus(const int32 ControllerIndex, const FName MotionSource) const override;`
- L60 _public prototype_ `virtual void EnumerateSources(TArray<FMotionControllerSource>& SourcesOut) const override;`
- L63 _public prototype_ `virtual bool OnKeyChar(TCHAR Character) override;`
- L64 _public prototype_ `virtual bool OnKeyDown(FKey Key, bool bIsRepeat) override;`
- L65 _public prototype_ `virtual bool OnKeyUp(FKey Key) override;`
- L67 _public prototype_ `virtual bool OnMouseEnter() override;`
- L68 _public prototype_ `virtual bool OnMouseLeave() override;`
- L69 _public prototype_ `virtual bool OnMouseDown(EMouseButtons::Type Button, FIntPoint ScreenPosition) override;`
- L70 _public prototype_ `virtual bool OnMouseUp(EMouseButtons::Type Button) override;`
- L71 _public prototype_ `virtual bool OnMouseMove(FIntPoint ScreenLocation, FIntPoint Delta) override;`
- L72 _public prototype_ `virtual bool OnMouseWheel(FIntPoint ScreenLocation, float MouseWheelDelta) override;`
- L73 _public prototype_ `virtual bool OnMouseDoubleClick(EMouseButtons::Type Button, FIntPoint ScreenPosition) override;`
- L75 _public prototype_ `virtual bool OnTouchStarted(FIntPoint TouchLocation, int32 TouchIndex, float Force) override;`
- L76 _public prototype_ `virtual bool OnTouchMoved(FIntPoint TouchLocation, int32 TouchIndex, float Force) override;`
- L77 _public prototype_ `virtual bool OnTouchEnded(FIntPoint TouchLocation, int32 TouchIndex) override;`
- L79 _public prototype_ `virtual uint8 OnControllerConnected() override;`
- L80 _public prototype_ `virtual bool OnControllerAnalog(uint8 ControllerIndex, FKey Key, double AxisValue) override;`
- L81 _public prototype_ `virtual bool OnControllerButtonPressed(uint8 ControllerIndex, FKey Key, bool bIsRepeat) override;`
- L82 _public prototype_ `virtual bool OnControllerButtonReleased(uint8 ControllerIndex, FKey Key) override;`
- L83 _public prototype_ `virtual bool OnControllerDisconnected(uint8 ControllerIndex) override;`
- L85 _public prototype_ `virtual bool OnXREyeViews(FTransform LeftEyeTransform, FMatrix LeftEyeProjectionMatrix, FTransform RightEyeTransform, FMatrix RightEyeProjectionMatrix, FTransform HMDTransform) override;`
- L86 _public prototype_ `virtual bool OnXRHMDTransform(FTransform HMDTransform) override;`
- L87 _public prototype_ `virtual bool OnXRControllerTransform(FTransform ControllerTransform, EControllerHand Handedness) override;`
- L88 _public prototype_ `virtual bool OnXRButtonTouched(EControllerHand Handedness, FKey Key, bool bIsRepeat) override;`
- L89 _public prototype_ `virtual bool OnXRButtonTouchReleased(EControllerHand Handedness, FKey Key) override;`
- L90 _public prototype_ `virtual bool OnXRButtonPressed(EControllerHand Handedness, FKey Key, bool bIsRepeat) override;`
- L91 _public prototype_ `virtual bool OnXRButtonReleased(EControllerHand Handedness, FKey Key) override;`
- L92 _public prototype_ `virtual bool OnXRAnalog(EControllerHand Handedness, FKey Key, double AnalogValue) override;`
- L93 _public prototype_ `virtual bool OnXRSystem(EPixelStreaming2XRSystem System) override;`
- L96 _protected prototype_ `FVector2D ConvertToNormalizedScreenLocation(FVector2D Point);`
- L97 _protected prototype_ `FIntPoint ConvertFromNormalizedScreenLocation(const FVector2D& ScreenLocation, bool bIncludeOffset = true);`
- L98 _protected prototype_ `FWidgetPath FindRoutingMessageWidget(const FVector2D& Location) const;`
- L99 _protected prototype_ `FKey TranslateMouseButtonToKey(const EMouseButtons::Type Button);`
- L122 _protected member_ `TMap<int32, FCachedTouchEvent> CachedTouchEvents;` — Keep a cache of the last touch events as we need to fire Touch Moved every frame while touch is down
- L124 _protected typedef_ `using FKeyId = uint8;`
- L136 _protected member_ `TMap<FInputDeviceId, TMap<FKey, FAnalogValue>> AnalogEventsReceivedThisTick;` — If more values are received in a single tick (e.g. could be temp network issue), then we only forward the latest value. Reason: The input system seems to expect at most one raw analog value per FKey per Tick. If this is not done, the input system can get stuck on non-zero input value even if the user has already stopped moving the analog stick. It would stay stuck until the next time the user moves the stick. The values arrive in the order of recording: that means once the player releases the analog, the last analog value would be 0.
- L139 _protected prototype_ `void ProcessLatestAnalogInputFromThisTick();` — Forwards the latest analog input received for each key this tick.
- L142 _protected member_ `TSet<int32> TouchIndicesProcessedThisFrame;` — Track which touch events we processed this frame so we can avoid re-processing them
- L145 _protected prototype_ `void BroadcastActiveTouchMoveEvents();` — Sends Touch Moved events for any touch index which is currently down but wasn't already updated this frame
- L147 _protected prototype_ `void FindFocusedWidget();`
- L153 _protected prototype_ `void SynthesizeMouseMove() const;` — Create an artificial mouse 'movement' to allow widgets to focus under a static mouse cursor. This will not actually change the cursor position.
- L155 _protected member_ `TArray<FKey> FilteredKeys;`
- L156 _protected prototype_ `void OnFilteredKeysChanged(IConsoleVariable* Var);`
- L157 _protected prototype_ `bool FilterKey(const FKey& Key);`
- L166 _protected member_ `TWeakPtr<SWindow> TargetWindow;`
- L167 _protected member_ `TWeakPtr<SViewport> TargetViewport;`
- L168 _protected member_ `TWeakPtr<FIntPoint> TargetScreenSize;` — Deprecated functionality but remaining until it can be removed
- L169 _protected member_ `TWeakPtr<FIntRect> TargetScreenRect;` — Manual size override used when we don't have a single window/viewport target
- L170 _protected member_ `uint8 NumActiveTouches;`
- L171 _protected member_ `bool bIsMouseActive;`
- L172 _protected member_ `TQueue<FMessage> Messages;`
- L173 _protected member_ `EPixelStreaming2InputType InputType = EPixelStreaming2InputType::RouteToWindow;`
- L174 _protected member_ `FVector2D LastTouchLocation = FVector2D(EForceInit::ForceInitToZero);`
- L175 _protected member_ `TMap<uint8, MessageHandlerFn> DispatchTable;`
- L178 _protected member_ `TSharedPtr<FGenericApplicationMessageHandler> MessageHandler;` — Reference to the message handler which events should be passed to.
- L181 _protected member_ `TSharedPtr<class FPixelStreaming2ApplicationWrapper> PixelStreamerApplicationWrapper;` — For convenience, we keep a reference to the application wrapper owned by the input channel
- L188 _protected member_ `bool bFakingTouchEvents;` — Is the application faking touch events by dragging the mouse along the canvas? If so then we must put the browser canvas in a special state to replicate the behavior of the application.
- L195 _protected member_ `const size_t MessageHeaderOffset = 1;` — Padding for string parsing when handling messages. 1 character for the actual message and then 2 characters for the length which are skipped
- L201 _protected member_ `const FVector2D UnfocusedPos = FVector2D(-1.f, -1.f);` — Touch only. A special position which indicates that no UI widget is focused.
- L207 _protected member_ `FVector2D FocusedPos;` — Touch only. Location of the focused UI widget. If no UI widget is focused then this has the UnfocusedPos value.
- L214 _protected member_ `bool bSynthesizeMouseMoveForNextMouseDown = false;` — Whether an artificial mouse 'movement' should be created the next time a mouse button down event occurs. This allows a widget to be focused immediately when the browser window is focused.
- L223 _protected member_ `TMap<EControllerHand, FPixelStreaming2XRController> XRControllers;`
- L233 _protected member_ `TMap<FString, CommandHandlerFn> CommandHandlers;` — A map of named commands we respond to when we receive a datachannel message of type "command". Key = command name (e.g "Encoder.MaxQP") Value = The command handler lambda function whose parameters are as follows: FString - the source id of the user who sent the message FString - the descriptor (e.g. the full json payload of the command message) FString - the parsed value of the command, e.g. if key was "Encoder.MaxQP" and descriptor was { type: "Command", "Encoder.MaxQP": 51 }, then parsed value is "51".
- L235 _protected member_ `TFunction<bool(FString)> ElevatedCheck;`
- L237 _protected member_ `TSharedPtr<IPixelStreaming2DataProtocol> ToStreamerProtocol;`
- L238 _protected member_ `TSharedPtr<IPixelStreaming2DataProtocol> FromStreamerProtocol;`
- L240 _protected member_ `float uint16_MAX = (float)UINT16_MAX;`
- L241 _protected member_ `float int16_MAX = (float)SHRT_MAX;`
- L244 _private member_ `FDelegateHandle OnInputKeyFilterChangedHandle;`

#### struct `UE::PixelStreaming2Input::FPixelStreaming2InputHandler::FCachedTouchEvent`  
`struct FCachedTouchEvent`  
_L101-106_
- L103 _public member_ `FVector2D Location;`
- L104 _public member_ `float Force;`
- L105 _public member_ `int32 ControllerIndex;`

#### struct `UE::PixelStreaming2Input::FPixelStreaming2InputHandler::FAnalogValue`  
`struct FAnalogValue`  
_L108-119_
- L111 _public member_ `double Value;` — The actual analog value from the controller axis, typical 0.0..1.0
- L116 _public member_ `bool bKeepUnlessZero = false;` — If value is non-zero then keep applying this analog values across frames. This is useful for trigger axis inputs where if a value is not transmitted UE will assume a gap in input means a full trigger press (which is not accurate if we were still pressing).
- L118 _public member_ `bool bIsRepeat = false;` — Has this key event already been fired once?

#### struct `UE::PixelStreaming2Input::FPixelStreaming2InputHandler::FMessage`  
`struct FMessage`  
_L159-164_
- L161 _public member_ `FString SourceId;`
- L162 _public member_ `TFunction<void(FString, FMemoryReader)>* Handler;`
- L163 _public member_ `TArray<uint8> Data;`

#### struct `UE::PixelStreaming2Input::FPixelStreaming2InputHandler::FPixelStreaming2XRController`  
`struct FPixelStreaming2XRController`  
_L216-221_
- L219 _public member_ `FTransform Transform;`
- L220 _public member_ `EControllerHand Handedness;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PIXELSTREAMING2INPUT_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PixelStreaming2Input` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Internal/InputProtocolMap.h` (Internal)


#### class `UE::PixelStreaming2Input::FInputProtocolMap`  
`class FInputProtocolMap : public IPixelStreaming2DataProtocol`  
_L18-51_
- inherits: `IPixelStreaming2DataProtocol`
- desc: @brief An map type that broadcasts the OnProtocolUpdated whenever it's inner map is updated
- L21 _public function_ `FInputProtocolMap(EPixelStreaming2MessageDirection InDirection) : Direction(InDirection)`
- L25 _public prototype_ `TSharedPtr<IPixelStreaming2InputMessage> Add(FString Key) override;`
- L26 _public prototype_ `TSharedPtr<IPixelStreaming2InputMessage> Add(FString Key, TArray<EPixelStreaming2MessageTypes> InStructure) override;`
- L27 _public prototype_ `TSharedPtr<IPixelStreaming2InputMessage> Find(FString Key) override;`
- L28 _public function_ `FOnProtocolUpdated& OnProtocolUpdated() override`
- L29 _public prototype_ `TSharedPtr<FJsonObject> ToJson() override;`
- L32 _public prototype_ `bool AddInternal(FString Key, uint8 Id);`
- L33 _public prototype_ `bool AddInternal(FString Key, uint8 Id, TArray<EPixelStreaming2MessageTypes> InStructure);`
- L34 _public prototype_ `int Remove(FString Key);`
- L35 _public prototype_ `const TSharedPtr<IPixelStreaming2InputMessage> Find(FString Key) const;`
- L37 _public prototype_ `void Clear();`
- L38 _public prototype_ `bool IsEmpty() const;`
- L40 _public prototype_ `void Apply(const TFunction<void(FString, TSharedPtr<IPixelStreaming2InputMessage>)>& Visitor);`
- L43 _private prototype_ `TSharedPtr<IPixelStreaming2InputMessage> AddMessageInternal(FString Key, uint8 Id, TArray<EPixelStreaming2MessageTypes> InStructure);`
- L46 _private member_ `TSet<uint8> Ids;`
- L47 _private member_ `TMap<FString, TSharedPtr<IPixelStreaming2InputMessage>> InnerMap;`
- L48 _private member_ `FOnProtocolUpdated OnProtocolUpdatedDelegate;`
- L49 _private member_ `EPixelStreaming2MessageDirection Direction;`
- L50 _private member_ `uint8 UserMessageId = 200;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PIXELSTREAMING2INPUT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2Input` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Private/ApplicationWrapper.h` (Private)


#### class `UE::PixelStreaming2Input::FPixelStreaming2ApplicationWrapper`  
`class FPixelStreaming2ApplicationWrapper : public GenericApplication`  
_L14-111_
- inherits: `GenericApplication`
- desc: Wrap the GenericApplication layer so we can replace the cursor and override certain behavior.
- L17 _public prototype_ `FPixelStreaming2ApplicationWrapper(TSharedPtr<GenericApplication> InWrappedApplication);`
- L18 _public prototype_ `~FPixelStreaming2ApplicationWrapper();`
- L20 _public prototype_ `void OnEnginePreExit();`
- L25 _public prototype_ `virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;` — Functions passed directly to the wrapped application.
- L26 _public prototype_ `virtual void PollGameDeviceState(const float TimeDelta) override;`
- L27 _public prototype_ `virtual void PumpMessages(const float TimeDelta) override;`
- L28 _public prototype_ `virtual void ProcessDeferredEvents(const float TimeDelta) override;`
- L29 _public prototype_ `virtual void Tick(const float TimeDelta) override;`
- L30 _public prototype_ `virtual TSharedRef<FGenericWindow> MakeWindow() override;`
- L31 _public prototype_ `virtual void InitializeWindow(const TSharedRef<FGenericWindow>& Window, const TSharedRef<FGenericWindowDefinition>& InDefinition, const TSharedPtr<FGenericWindow>& InParent, const bool bShowImmediately) override;`
- L32 _public prototype_ `virtual void SetCapture(const TSharedPtr<FGenericWindow>& InWindow) override;`
- L33 _public prototype_ `virtual void* GetCapture(void) const override;`
- L34 _public prototype_ `virtual void SetHighPrecisionMouseMode(const bool Enable, const TSharedPtr<FGenericWindow>& InWindow) override;`
- L35 _public prototype_ `virtual bool IsUsingHighPrecisionMouseMode() const override;`
- L36 _public prototype_ `virtual bool IsUsingTrackpad() const override;`
- L37 _public prototype_ `virtual bool IsGamepadAttached() const override;`
- L38 _public prototype_ `virtual void RegisterConsoleCommandListener(const FOnConsoleCommandListener& InListener) override;`
- L39 _public prototype_ `virtual void AddPendingConsoleCommand(const FString& InCommand) override;`
- L40 _public prototype_ `virtual FPlatformRect GetWorkArea(const FPlatformRect& CurrentWindow) const override;`
- L41 _public prototype_ `virtual bool TryCalculatePopupWindowPosition(const FPlatformRect& InAnchor, const FVector2D& InSize, const FVector2D& ProposedPlacement, const EPopUpOrientation::Type Orientation, FVector2D* const CalculatedPopUpPosition) const override;`
- L42 _public prototype_ `virtual void GetInitialDisplayMetrics(FDisplayMetrics& OutDisplayMetrics) const override;`
- L43 _public prototype_ `virtual EWindowTitleAlignment::Type GetWindowTitleAlignment() const override;`
- L44 _public prototype_ `virtual EWindowTransparency GetWindowTransparencySupport() const override;`
- L45 _public prototype_ `virtual void DestroyApplication() override;`
- L46 _public prototype_ `virtual IInputInterface* GetInputInterface() override;`
- L47 _public prototype_ `virtual ITextInputMethodSystem* GetTextInputMethodSystem() override;`
- L48 _public prototype_ `virtual void SendAnalytics(IAnalyticsProvider* Provider) override;`
- L49 _public prototype_ `virtual bool SupportsSystemHelp() const override;`
- L50 _public prototype_ `virtual void ShowSystemHelp() override;`
- L51 _public prototype_ `virtual bool ApplicationLicenseValid(FPlatformUserId PlatformUser = PLATFORMUSERID_NONE) override;`
- L56 _public prototype_ `virtual bool IsMouseAttached() const override;` — Functions with overridden behavior.
- L57 _public prototype_ `virtual bool IsCursorDirectlyOverSlateWindow() const override;`
- L58 _public prototype_ `virtual TSharedPtr<FGenericWindow> GetWindowUnderCursor() override;`
- L63 _public prototype_ `virtual void SetTargetWindow(TWeakPtr<SWindow> InTargetWindow);` — Custom functions
- L65 _public member_ `TSharedPtr<GenericApplication> WrappedApplication;`
- L66 _public member_ `TWeakPtr<SWindow> TargetWindow;`
- L90 _public member_ `FModifierKey ModifierKeys[EModifierKey::Count];` — Whether a particular modifier key, such as Ctrl, is pressed.
- L93 _public prototype_ `void InitModifierKeys();` — Initialize the list of possible modifier keys.
- L101 _public prototype_ `void UpdateModifierKey(const FKey* InAgnosticKey, bool bInActive);` — When the user presses or releases a modifier key then update its state to active or back to inactive. @param InAgnosticKey - The key the user is pressing. @param bInActive - Whether the key is pressed (active) or released (inactive).
- L107 _public prototype_ `virtual FModifierKeysState GetModifierKeys() const;` — Return the current set of active modifier keys. @return The current set of active modifier keys.
- L110 _private member_ `FDelegateHandle OnEnginePreExitDelegateHandle;`

#### struct `UE::PixelStreaming2Input::FPixelStreaming2ApplicationWrapper::EModifierKey`  
`struct EModifierKey`  
_L68-81_

#### enum `UE::PixelStreaming2Input::FPixelStreaming2ApplicationWrapper::EModifierKey::Type`  
`enum Type`  
_L70-80_
- L72 _public enumerator_ `LeftShift`
- L73 _public enumerator_ `RightShift`
- L74 _public enumerator_ `LeftControl`
- L75 _public enumerator_ `RightControl`
- L76 _public enumerator_ `LeftAlt`
- L77 _public enumerator_ `RightAlt`
- L78 _public enumerator_ `CapsLock`
- L79 _public enumerator_ `Count`

#### struct `UE::PixelStreaming2Input::FPixelStreaming2ApplicationWrapper::FModifierKey`  
`struct FModifierKey`  
_L83-87_
- L85 _public member_ `bool bActive = false;`
- L86 _public member_ `const FKey* AgnosticKey;`

#### class `UE::PixelStreaming2Input::FCursor`  
`class FCursor : public ICursor`  
_L119-136_
- inherits: `ICursor`
- desc: When reading input from a browser then the cursor position will be sent across with mouse events. We want to use this position and avoid getting the cursor position from the operating system. This is not relevant to touch events.
- L122 _public function_ `FCursor()`
- L123 _public prototype_ `virtual ~FCursor() = default;`
- L124 _public function_ `virtual FVector2D GetPosition() const override`
- L125 _public function_ `virtual void SetPosition(const int32 X, const int32 Y) override`
- L126 _public function_ `virtual void SetType(const EMouseCursor::Type InNewCursor) override`
- L127 _public function_ `virtual EMouseCursor::Type GetType() const override`
- L128 _public function_ `virtual void GetSize(int32& Width, int32& Height) const override`
- L129 _public function_ `virtual void Show(bool bShow) override`
- L130 _public function_ `virtual void Lock(const RECT* const Bounds) override`
- L131 _public function_ `virtual void SetTypeShape(EMouseCursor::Type InCursorType, void* CursorHandle) override`
- L135 _private member_ `FVector2D Position;` — The cursor position sent across with mouse events.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming2Input` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Private/InputDevice.h` (Private)


#### class `UE::PixelStreaming2Input::FInputDevice`  
`class FInputDevice : public IInputDevice`  
_L14-62_
- inherits: `IInputDevice`
- desc: @brief The input device used to interface the multiple streamers and the single input device created by the OS
- L17 _public prototype_ `void Tick(float DeltaTime) override;`
- L19 _public function_ `virtual void SendControllerEvents() override` — Poll for controller state and send events if needed
- L22 _public prototype_ `virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InTargetHandler) override;` — Set which MessageHandler will route input
- L25 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — Exec handler to allow console commands to be passed through for debugging
- L26 _public prototype_ `virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;`
- L27 _public prototype_ `virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values) override;`
- L29 _public prototype_ `void AddInputHandler(IPixelStreaming2InputHandler* InputHandler);`
- L30 _public prototype_ `void RemoveInputHandler(IPixelStreaming2InputHandler* InputHandler);`
- L31 _public prototype_ `uint8 OnControllerConnected();`
- L32 _public prototype_ `void OnControllerDisconnected(uint8 DeleteControllerId);`
- L33 _public prototype_ `bool GetPlatformUserAndDevice(uint8 ControllerId, FInputDeviceId& OutDeviceId, FPlatformUserId& OutPlatformUser);`
- L34 _public prototype_ `bool GetControllerIdFromDeviceId(FInputDeviceId DeviceId, uint8& OutControllerId);`
- L36 _public prototype_ `static TSharedPtr<FInputDevice> GetInputDevice();`
- L39 _private prototype_ `FInputDevice();`
- L46 _private member_ `static TSharedPtr<FInputDevice> InputDevice;` — A singleton pointer to the input device. We only want a single input device that has multiple input handlers. The reason for a single input device is that only one is created by the application, so make sure we always use that one
- L54 _private member_ `TSet<IPixelStreaming2InputHandler*> InputHandlers;` — The array of input handlers. Each input handler belongs to a single streamer NOTE: We store each input handler as a raw pointer as registering and deregistering is handled in the FPixelStreaming2InputHandler ctor and dtor NOTE: This pointer is non-owning. It is up to user code to keep the original IPixelStreaming2InputHandler alive to avoid deregistration
- L61 _private member_ `TMap<uint8, TPair<FInputDeviceId, FPlatformUserId>> InputDevices;` — The map of connected controllers. As each handler can have multiple input devices, we want to make sure that each controller of each device is unique As such, a simple incrementer approach is not applicable and we must instead keep track of all the connected controllers

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming2Input` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Private/InputMessage.h` (Private)


#### class `UE::PixelStreaming2Input::FInputMessage`  
`class FInputMessage : public IPixelStreaming2InputMessage`  
_L14-31_
- inherits: `IPixelStreaming2InputMessage`
- L18 _public prototype_ `FInputMessage(uint8 InId);` — Internal use constructor taking an ID. Sets Structure to []
- L21 _public prototype_ `FInputMessage(uint8 InId, TArray<EPixelStreaming2MessageTypes> InStructure);` — Constructor taking an ID and a Structure
- L23 _public prototype_ `virtual ~FInputMessage() = default;`
- L25 _public function_ `uint8 GetID() const override`
- L26 _public function_ `TArray<EPixelStreaming2MessageTypes> GetStructure() const override`
- L29 _private member_ `uint8 Id;`
- L30 _private member_ `TArray<EPixelStreaming2MessageTypes> Structure;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2Input` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Private/Logging.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2Input, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2Input, Log, All);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Private/PixelStreaming2InputModule.h` (Private)


#### class `UE::PixelStreaming2Input::FPixelStreaming2InputModule`  
`class FPixelStreaming2InputModule : public IPixelStreaming2InputModule`  
_L10-26_
- inherits: `IPixelStreaming2InputModule`
- L13 _public prototype_ `virtual TSharedPtr<IPixelStreaming2InputHandler> CreateInputHandler() override;`
- L17 _private prototype_ `void StartupModule() override;` — IModuleInterface implementation
- L18 _private prototype_ `void ShutdownModule() override;`
- L22 _private prototype_ `virtual TSharedPtr<IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;` — IInputDeviceModule implementation
- L25 _private member_ `TSharedPtr<FInputDevice> InputDevice;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming2Input` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Private/Utils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2Input` (scope `UE`)
- L13 _function_ `inline void ExtendJsonWithField(const FString& Descriptor, FString FieldName, FString StringValue, FString& NewDescriptor, bool& Success)` (scope `UE::PixelStreaming2Input`)
- L34 _function_ `inline void ExtractJsonFromDescriptor(FString Descriptor, FString FieldName, FString& StringValue, bool& Success)` (scope `UE::PixelStreaming2Input`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Public/IPixelStreaming2DataProtocol.h` (Public)


#### class `IPixelStreaming2DataProtocol`  
`class IPixelStreaming2DataProtocol`  
_L13-53_
- desc: Interface for a datachannel protocol. The user is not meant to extend this through polymorphism, but rather request the appropriate protocol from the InputHandler and extend it using Add().
- L16 _public prototype_ `IPixelStreaming2DataProtocol() = default;`
- L17 _public prototype_ `virtual ~IPixelStreaming2DataProtocol() = default;`
- L24 _public prototype_ `virtual TSharedPtr<IPixelStreaming2InputMessage> Add(FString Key) = 0;` — Adds a custom message type, with no message body, to the protocol. @param Key The string identifier used to uniquely identify and query this message inside the protocol. @return True if the new message was added to the protocol (fails if key is already present).
- L31 _public prototype_ `virtual TSharedPtr<IPixelStreaming2InputMessage> Add(FString Key, TArray<EPixelStreaming2MessageTypes> InStructure) = 0;` — Adds a custom message type, with associated message structured, to the protocol. @param Key The string identifier used to uniquely identify and query this message inside the protocol. @return True if the new message was added to the protocol (fails if key is already present).
- L40 _public prototype_ `virtual TSharedPtr<IPixelStreaming2InputMessage> Find(FString Key) = 0;` — Looks for the supplied message type in this protocol. This call should primarily be made from user code when the user has supplied a custom message type to the protocol. Note: If you are looking for a default message type consider using the Get() methods and passing one of the From/ToStreamer message enums to avoid typos. @param Key The string representation of the message type we are looking for. @return The message type associated with the `FromStreamer` message type passed.
- L45 _public prototype_ `virtual TSharedPtr<FJsonObject> ToJson() = 0;` — @return A JSON schema representing the data protocol.
- L47 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnProtocolUpdated);`
- L52 _public prototype_ `virtual FOnProtocolUpdated& OnProtocolUpdated() = 0;` — Called any time to protocol has a new data type added to it. Internally this will force Pixel Streaming to resend the entire data protocol.

#### Free symbols / members of external scopes

- L47 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnProtocolUpdated);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Public/IPixelStreaming2InputHandler.h` (Public)


#### class `IPixelStreaming2InputHandler`  
`class IPixelStreaming2InputHandler : public IInputDevice`  
_L18-417_
- inherits: `IInputDevice`
- desc: The IPixelStreaming2InputHandler, used to handle input from a remote peer and pass it to UE accordingly. Setting the target viewport allows for scaling of input from browser to application, and setting the target window ensure that if windows are tiled (eg editor) that the streamed input only affect the target window.
- L21 _public prototype_ `IPixelStreaming2InputHandler();`
- L22 _public prototype_ `virtual ~IPixelStreaming2InputHandler();`
- L29 _public prototype_ `virtual void OnMessage(FString SourceId, TArray<uint8> Buffer) = 0;` — @brief Handle the message from the WebRTC data channel. @param SourceId A source ID for this message @param Buffer The data channel message
- L35 _public prototype_ `virtual void SetTargetViewport(TWeakPtr<SViewport> InTargetViewport) = 0;` — @brief Set the viewport this input device is associated with. @param InTargetViewport The viewport to set
- L41 _public prototype_ `virtual TWeakPtr<SViewport> GetTargetViewport() = 0;` — @brief Get the viewport this input device is associated with. @return The viewport this input device is associated with
- L47 _public prototype_ `virtual void SetTargetWindow(TWeakPtr<SWindow> InTargetWindow) = 0;` — @brief Set the viewport this input device is associated with. @param InTargetWindow The viewport to set
- L53 _public prototype_ `virtual TWeakPtr<SWindow> GetTargetWindow() = 0;` — @brief Get the viewport this input device is associated with. @return The viewport this input device is associated with
- L60 _public prototype_ `virtual void SetTargetScreenRect(TWeakPtr<FIntRect> InTargetScreenRect) = 0;` — @brief Set the target screen rectangle for this streamer. This is used to when the streamer doesn't have a singular target window / viewport and as such we just use the manual scale @param InTargetScreenRect The target screen rectangle
- L66 _public prototype_ `virtual TWeakPtr<FIntRect> GetTargetScreenRect() = 0;` — @brief Get the target screen rectangle for this streamer @return The target screen rectangle
- L73 _public prototype_ `virtual bool IsFakingTouchEvents() const = 0;` — @brief Set whether the input devices is faking touch events using keyboard and mouse this can be useful for debugging. @return true @return false
- L81 _public typedef_ `using MessageHandlerFn = TFunction<void(FString SourceId, FMemoryReader Message)>;` — @brief The callback signature for handling a command sent to the data channel. @param SourceId The source id of the sender of this message. @param Message The full message in the form of a FMemoryReader.
- L89 _public prototype_ `virtual void RegisterMessageHandler(const FString& MessageType, const MessageHandlerFn& Handler) = 0;` — @brief Register a function to be called whenever the specified message type is received. @param MessageType The human readable identifier for the message @param Handler The function called when this message type is received. This handler must take a single parameter (an FMemoryReader) and have a return type of void
- L98 _public typedef_ `using CommandHandlerFn = TFunction<void(FString SourceId, FString Descriptor, FString CommandString)>;` — @brief The callback signature for handling a command sent to the data channel. @param SourceId The source id of the sender of this message. @param Descriptor The full descriptor of the commaand. @param CommandString The relevant string parameters for the command.
- L106 _public prototype_ `virtual void SetCommandHandler(const FString& CommandName, const CommandHandlerFn& Handler) = 0;` — @brief Register a custom function to execute when command JSON is received over the data channel: "{ type: "Command", YourCommand: YourCommandValue }". Note: You can also override the default Pixel Streaming command handlers by setting handlers with the same name as those already used, e.g. "Stat.FPS". @param CommandName The name of the command to handle. This corresponds to the key in the JSON message and is used to identify the command. @param Handler The function that will be executed when the command is received.
- L113 _public prototype_ `virtual void SetElevatedCheck(const TFunction<bool(FString)>& CheckFn) = 0;` — @brief Some behaviours might want to be limited to a specific source or group of sources. This method sets a check function to test of a given source id is "elevated". @param CheckFn A callback that takes a SourceId and returns true if the source id is an elevated user.
- L120 _public prototype_ `virtual bool IsElevated(const FString& Id) = 0;` — @brief Checks whether the given id has elevated priviledges. @return True if id is elevated and false is not elevated.
- L128 _public prototype_ `virtual MessageHandlerFn FindMessageHandler(const FString& MessageType) = 0;` — @brief Find the function to be called whenever the specified message type is received. @param MessageType The human readable identifier for the message @return TFunction<void(FString, FMemoryReader)> The function called when this message type is received.
- L133 _public prototype_ `virtual TSharedPtr<IPixelStreaming2DataProtocol> GetToStreamerProtocol() = 0;` — @return The "ToStreamer" data protocol. This can be used to modify the protocol with custom data channel messages.
- L138 _public prototype_ `virtual TSharedPtr<IPixelStreaming2DataProtocol> GetFromStreamerProtocol() = 0;` — @return The "FromStreamer" data protocol. This can be used to modify the protocol with custom data channel messages.
- L144 _public prototype_ `virtual void SetInputType(EPixelStreaming2InputType InputType) = 0;` — @brief Set the input handlers type. This controls whether input is routed to widgets or windows. @param InputType The input routing type.
- L146 _public prototype_ `DECLARE_EVENT_TwoParams(IPixelStreaming2InputHandler, FOnSendMessage, FString, FMemoryReader);`
- L151 _public member_ `FOnSendMessage OnSendMessage;` — An event that is only fired internally of the InputHandler when it wants to send a message to all connected players. Examples include when a virtual gamepad controller is "connected" and given a unique id.
- L160 _public prototype_ `virtual bool OnKeyChar(TCHAR Character) = 0;` — @brief Notify the input handler of a character event. @param Character The character @return true if the event was handled. false otherwise
- L170 _public prototype_ `virtual bool OnKeyDown(FKey Key, bool bIsRepeat) = 0;` — @brief Notify the input handler of a key down event. @param Key The key @param bIsRepeat Is this a repeat of a previous Key down (ie has the key been held down) @return true if the event was handled. false otherwise
- L179 _public prototype_ `virtual bool OnKeyUp(FKey Key) = 0;` — @brief Notify the input handler of a key up event. @param Key The key @return true if the event was handled. false otherwise
- L186 _public prototype_ `virtual bool OnMouseEnter() = 0;` — @brief Notify the input handler of the mouse entering the application (typically the browser window). @return true if the event was handled. false otherwise
- L193 _public prototype_ `virtual bool OnMouseLeave() = 0;` — @brief Notify the input handler of the mouse leaving the application (typically the browser window). @return true if the event was handled. false otherwise
- L203 _public prototype_ `virtual bool OnMouseDown(EMouseButtons::Type Button, FIntPoint ScreenPosition) = 0;` — @brief Notify the input handler of a mouse down event. @param Button The mouse button @param ScreenPosition The position of the mouse event in UE screen space @return true if the event was handled. false otherwise
- L212 _public prototype_ `virtual bool OnMouseUp(EMouseButtons::Type Button) = 0;` — @brief Notify the input handler of a mouse up event. @param Button The mouse button @return true if the event was handled. false otherwise
- L222 _public prototype_ `virtual bool OnMouseMove(FIntPoint ScreenPosition, FIntPoint Delta) = 0;` — @brief Notify the input handler of a mouse move event. @param ScreenPosition The starting position of the mouse event in UE screen space @param Delta The amount the mouse moves in this event in UE screen space @return true if the event was handled. false otherwise
- L232 _public prototype_ `virtual bool OnMouseWheel(FIntPoint ScreenPosition, float MouseWheelDelta) = 0;` — @brief Notify the input handler of a mouse wheel event. @param ScreenPosition The position of the mouse event in UE screen space @param MouseWheelDelta The amount the mouse wheel moved @return true if the event was handled. false otherwise
- L242 _public prototype_ `virtual bool OnMouseDoubleClick(EMouseButtons::Type Button, FIntPoint ScreenPosition) = 0;` — @brief Notify the input handler of a mouse double click event. @param Button The mouse button @param ScreenPosition The position of the mouse event in UE screen space @return true if the event was handled. false otherwise
- L253 _public prototype_ `virtual bool OnTouchStarted(FIntPoint TouchPosition, int32 TouchIndex, float Force) = 0;` — @brief Notify the input handler of a touch start event. @param TouchPosition The position of the touch event in UE screen space @param TouchIndex The index of the finger that started touching @param Force The force of the touch in the range 0 (no force) to 1 (maximum force) @return true if the event was handled. false otherwise
- L264 _public prototype_ `virtual bool OnTouchMoved(FIntPoint TouchPosition, int32 TouchIndex, float Force) = 0;` — @brief Notify the input handler of a touch moved event. @param TouchPosition The position of the touch event after the move has completed in UE screen space @param TouchIndex The index of the finger that moved @param Force The force of the touch in the range 0 (no force) to 1 (maximum force) @return true if the event was handled. false otherwise
- L274 _public prototype_ `virtual bool OnTouchEnded(FIntPoint TouchPosition, int32 TouchIndex) = 0;` — @brief Notify the input handler of a touch ended event. @param TouchPosition The position of the touch event in UE screen space @param TouchIndex The index of the finger that stopped touching @return true if the event was handled. false otherwise
- L281 _public prototype_ `virtual uint8 OnControllerConnected() = 0;` — @brief Notify the input handler of a controller connecting. @return the index to use for this new controller
- L292 _public prototype_ `virtual bool OnControllerAnalog(uint8 ControllerIndex, FKey Axis, double AxisValue) = 0;` — @brief Notify the input handler of a controller analog event. @param ControlledIndex The index of the controller received from OnControllerConnected @param Axis The axis FKey @param AxisValue The value of the axis in the range -1 to 1 @return true if the event was handled. false otherwise
- L303 _public prototype_ `virtual bool OnControllerButtonPressed(uint8 ControllerIndex, FKey Key, bool bIsRepeat) = 0;` — @brief Notify the input handler of a controller button press event. @param ControlledIndex The index of the controller received from OnControllerConnected @param Key The button FKey @param bIsRepeat Is this a repeat of a previous button press (ie has the button been held down) @return true if the event was handled. false otherwise
- L313 _public prototype_ `virtual bool OnControllerButtonReleased(uint8 ControllerIndex, FKey Key) = 0;` — @brief Notify the input handler of a controller button release event. @param ControlledIndex The index of the controller received from OnControllerConnected @param Key The button FKey @return true if the event was handled. false otherwise
- L322 _public prototype_ `virtual bool OnControllerDisconnected(uint8 ControllerIndex) = 0;` — @brief Notify the input handler of a controller disconnecting. @param ControlledIndex The index of the controller received from OnControllerConnected @return true if the event was handled. false otherwise
- L335 _public prototype_ `virtual bool OnXREyeViews(FTransform LeftEyeTransform, FMatrix LeftEyeProjectionMatrix, FTransform RightEyeTransform, FMatrix RightEyeProjectionMatrix, FTransform HMDTransform) = 0;` — @brief Notify the input handler of receiving the Eye Views to use with XR streaming (usually received oncne at the start of a stream) @param LeftEyeTransform The transform of the left eye @param LeftEyeProjectionMatrix The projection matrix of the left eye @param RightEyeTransform The transform of the right eye @param RightEyeProjectionMatrix The projection matrix of the right eye @param HMDTransform The transform of the HMD itself @return true if the event was handled. false otherwise
- L344 _public prototype_ `virtual bool OnXRHMDTransform(FTransform HMDTransform) = 0;` — @brief Notify the input handler of receiving the transform of the HMD to use with XR streaming (received once per frame that the HMD displays). @param HMDTransform The transform of the HMD itself @return true if the event was handled. false otherwise
- L354 _public prototype_ `virtual bool OnXRControllerTransform(FTransform ControllerTransform, EControllerHand Handedness) = 0;` — @brief Notify the input handler of receiving the transform of an XR controller to use with XR streaming (received once per frame that the HMD displays). @param ControllerTransform The transform of the controller @param Handedness Specifies the hand this transform applies to @return true if the event was handled. false otherwise
- L365 _public prototype_ `virtual bool OnXRButtonTouched(EControllerHand Handedness, FKey Key, bool bIsRepeat) = 0;` — @brief Notify the input handler of receiving a XR controller button touch event to use with XR streaming @param Handedness Specifies the hand this button touch event applies to @param Key The button FKey @param bIsRepeat Is this a repeat of a previous button press (ie has the button been held down) @return true if the event was handled. false otherwise
- L375 _public prototype_ `virtual bool OnXRButtonTouchReleased(EControllerHand Handedness, FKey Key) = 0;` — @brief Notify the input handler of receiving a XR controller button touch release event to use with XR streaming @param Handedness Specifies the hand this button touch event applies to @param Key The button FKey @return true if the event was handled. false otherwise
- L386 _public prototype_ `virtual bool OnXRButtonPressed(EControllerHand Handedness, FKey Key, bool bIsRepeat) = 0;` — @brief Notify the input handler of receiving a XR controller button press event to use with XR streaming @param Handedness Specifies the hand this button press event applies to @param Key The button FKey @param bIsRepeat Is this a repeat of a previous button press (ie has the button been held down) @return true if the event was handled. false otherwise
- L396 _public prototype_ `virtual bool OnXRButtonReleased(EControllerHand Handedness, FKey Key) = 0;` — @brief Notify the input handler of receiving a XR controller button release event to use with XR streaming @param Handedness Specifies the hand this button release event applies to @param Key The button FKey @return true if the event was handled. false otherwise
- L407 _public prototype_ `virtual bool OnXRAnalog(EControllerHand Handedness, FKey Key, double AnalogValue) = 0;` — @brief Notify the input handler of receiving a XR controller button release event to use with XR streaming @param Handedness Specifies the hand this button release event applies to @param Key The axis FKey @param AnalogValue The value of the axis in the range -1 to 1 @return true if the event was handled. false otherwise
- L416 _public prototype_ `virtual bool OnXRSystem(EPixelStreaming2XRSystem System) = 0;` — @brief Notify the input handler of the headset system connected to the frontend to use with XR streaming @param System The system @return true if the event was handled. false otherwise

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PIXELSTREAMING2INPUT_API`
- L146 _delegate_ `DECLARE_EVENT_TwoParams(IPixelStreaming2InputHandler, FOnSendMessage, FString, FMemoryReader);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Public/IPixelStreaming2InputMessage.h` (Public)


#### class `IPixelStreaming2InputMessage`  
`class IPixelStreaming2InputMessage`  
_L12-28_
- desc: A message that is sent over the Pixel Streaming data channel.
- L20 _public prototype_ `virtual uint8 GetID() const = 0;` — Gets the id of the message. Note: All messages required a unique id. @return The id of the message.
- L27 _public prototype_ `virtual TArray<EPixelStreaming2MessageTypes> GetStructure() const = 0;` — Get the message structure, e.g. the array of types that make up this message. Note: The types are packed tightly and sent in a byte buffer. @return The structure of the message.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Public/IPixelStreaming2InputModule.h` (Public)


#### class `IPixelStreaming2InputModule`  
`class IPixelStreaming2InputModule : public IInputDeviceModule`  
_L11-45_
- inherits: `IInputDeviceModule`
- desc: Provides mechanism for managing input handlers and devices in Pixel Streaming.
- L20 _public function_ `static inline IPixelStreaming2InputModule& Get()` — Singleton-like access to this module's interface. Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed.
- L30 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded. @return True if the module is loaded.
- L37 _public prototype_ `virtual TSharedPtr<IPixelStreaming2InputHandler> CreateInputHandler() = 0;` — @brief Create a Input Handler object. @return TSharedPtr<IPixelStreaming2InputHandler> the input handler for this streamer.
- L44 _public prototype_ `virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override = 0;` — Attempts to create a new input device interface @param InMessageHandler A reference to the message handler that will process input events from the device. @return	Interface to the new input device, if we were able to successfully create one.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Public/PixelStreaming2DefaultDataProtocol.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming2Input` (scope `UE`)
- L14 _prototype_ `TSharedPtr<IPixelStreaming2DataProtocol> GetDefaultToStreamerProtocol();` (scope `UE::PixelStreaming2Input`) — @return The default "ToStreamer" data protocol.
- L19 _prototype_ `TSharedPtr<IPixelStreaming2DataProtocol> GetDefaultFromStreamerProtocol();` (scope `UE::PixelStreaming2Input`) — @return The default "FromStreamer" data protocol.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Public/PixelStreaming2InputEnums.h` (Public)


#### enum `EPixelStreaming2MessageTypes`  
`enum class EPixelStreaming2MessageTypes`  
_L10-19_
- desc: @brief The data types supported when sending messages across the data channel to/from peers.
- L12 _public enumerator_ `Uint8 = 0`
- L13 _public enumerator_ `Uint16 = 1`
- L14 _public enumerator_ `Int16 = 2`
- L15 _public enumerator_ `Float = 3`
- L16 _public enumerator_ `Double = 4`
- L17 _public enumerator_ `String = 5`
- L18 _public enumerator_ `Undefined = 6`

#### enum `EPixelStreaming2MessageDirection`  
`enum class EPixelStreaming2MessageDirection : uint8`  
_L24-28_
- desc: @brief The message directions
- L26 _public enumerator_ `ToStreamer = 0`
- L27 _public enumerator_ `FromStreamer = 1`

#### enum `EPixelStreaming2InputAction`  
`enum class EPixelStreaming2InputAction : uint8`  
_L33-41_
- desc: @brief The possible actions pixel streaming supports. These actions help differentiate input received from the browser.
- L35 _public enumerator_ `X = 0`
- L36 _public enumerator_ `Y = 1`
- L37 _public enumerator_ `Axis = 2`
- L38 _public enumerator_ `Click = 3`
- L39 _public enumerator_ `Touch = 4`
- L40 _public enumerator_ `None = 5`

#### enum `EPixelStreaming2InputType`  
`enum class EPixelStreaming2InputType : uint8`  
_L46-50_
- desc: @brief The possible control schemes pixel streaming supports. RouteToWindow routes input at an application level. RouteToWidget routes input to a specific widget, ignoring the rest of the application.
- L48 _public enumerator_ `RouteToWindow = 0`
- L49 _public enumerator_ `RouteToWidget = 1`

#### Free symbols / members of external scopes

- L55 _namespace_ `namespace EPixelStreaming2ToStreamerMessage`
- L57 _externvar_ `extern const FString IFrameRequest;` (scope `EPixelStreaming2ToStreamerMessage`)
- L58 _externvar_ `extern const FString RequestQualityControl;` (scope `EPixelStreaming2ToStreamerMessage`)
- L59 _externvar_ `extern const FString FpsRequest;` (scope `EPixelStreaming2ToStreamerMessage`)
- L60 _externvar_ `extern const FString AverageBitrateRequest;` (scope `EPixelStreaming2ToStreamerMessage`)
- L61 _externvar_ `extern const FString StartStreaming;` (scope `EPixelStreaming2ToStreamerMessage`)
- L62 _externvar_ `extern const FString StopStreaming;` (scope `EPixelStreaming2ToStreamerMessage`)
- L63 _externvar_ `extern const FString LatencyTest;` (scope `EPixelStreaming2ToStreamerMessage`)
- L64 _externvar_ `extern const FString RequestInitialSettings;` (scope `EPixelStreaming2ToStreamerMessage`)
- L65 _externvar_ `extern const FString TestEcho;` (scope `EPixelStreaming2ToStreamerMessage`)
- L66 _externvar_ `extern const FString UIInteraction;` (scope `EPixelStreaming2ToStreamerMessage`)
- L67 _externvar_ `extern const FString Command;` (scope `EPixelStreaming2ToStreamerMessage`)
- L68 _externvar_ `extern const FString TextboxEntry;` (scope `EPixelStreaming2ToStreamerMessage`)
- L69 _externvar_ `extern const FString KeyDown;` (scope `EPixelStreaming2ToStreamerMessage`)
- L70 _externvar_ `extern const FString KeyUp;` (scope `EPixelStreaming2ToStreamerMessage`)
- L71 _externvar_ `extern const FString KeyPress;` (scope `EPixelStreaming2ToStreamerMessage`)
- L72 _externvar_ `extern const FString MouseEnter;` (scope `EPixelStreaming2ToStreamerMessage`)
- L73 _externvar_ `extern const FString MouseLeave;` (scope `EPixelStreaming2ToStreamerMessage`)
- L74 _externvar_ `extern const FString MouseDown;` (scope `EPixelStreaming2ToStreamerMessage`)
- L75 _externvar_ `extern const FString MouseUp;` (scope `EPixelStreaming2ToStreamerMessage`)
- L76 _externvar_ `extern const FString MouseMove;` (scope `EPixelStreaming2ToStreamerMessage`)
- L77 _externvar_ `extern const FString MouseWheel;` (scope `EPixelStreaming2ToStreamerMessage`)
- L78 _externvar_ `extern const FString MouseDouble;` (scope `EPixelStreaming2ToStreamerMessage`)
- L79 _externvar_ `extern const FString TouchStart;` (scope `EPixelStreaming2ToStreamerMessage`)
- L80 _externvar_ `extern const FString TouchEnd;` (scope `EPixelStreaming2ToStreamerMessage`)
- L81 _externvar_ `extern const FString TouchMove;` (scope `EPixelStreaming2ToStreamerMessage`)
- L82 _externvar_ `extern const FString GamepadButtonPressed;` (scope `EPixelStreaming2ToStreamerMessage`)
- L83 _externvar_ `extern const FString GamepadButtonReleased;` (scope `EPixelStreaming2ToStreamerMessage`)
- L84 _externvar_ `extern const FString GamepadAnalog;` (scope `EPixelStreaming2ToStreamerMessage`)
- L85 _externvar_ `extern const FString GamepadConnected;` (scope `EPixelStreaming2ToStreamerMessage`)
- L86 _externvar_ `extern const FString GamepadDisconnected;` (scope `EPixelStreaming2ToStreamerMessage`)
- L87 _externvar_ `extern const FString XREyeViews;` (scope `EPixelStreaming2ToStreamerMessage`)
- L88 _externvar_ `extern const FString XRHMDTransform;` (scope `EPixelStreaming2ToStreamerMessage`)
- L89 _externvar_ `extern const FString XRControllerTransform;` (scope `EPixelStreaming2ToStreamerMessage`)
- L90 _externvar_ `extern const FString XRButtonPressed;` (scope `EPixelStreaming2ToStreamerMessage`)
- L91 _externvar_ `extern const FString XRButtonTouched;` (scope `EPixelStreaming2ToStreamerMessage`)
- L92 _externvar_ `extern const FString XRButtonReleased;` (scope `EPixelStreaming2ToStreamerMessage`)
- L93 _externvar_ `extern const FString XRAnalog;` (scope `EPixelStreaming2ToStreamerMessage`)
- L94 _externvar_ `extern const FString XRSystem;` (scope `EPixelStreaming2ToStreamerMessage`)
- L95 _externvar_ `extern const FString XRButtonTouchReleased;` (scope `EPixelStreaming2ToStreamerMessage`)
- L96 _externvar_ `extern const FString Multiplexed;` (scope `EPixelStreaming2ToStreamerMessage`)
- L97 _externvar_ `extern const FString ChannelRelayStatus;` (scope `EPixelStreaming2ToStreamerMessage`)
- L103 _namespace_ `namespace EPixelStreaming2FromStreamerMessage`
- L105 _externvar_ `extern const FString QualityControlOwnership;` (scope `EPixelStreaming2FromStreamerMessage`)
- L106 _externvar_ `extern const FString Response;` (scope `EPixelStreaming2FromStreamerMessage`)
- L107 _externvar_ `extern const FString Command;` (scope `EPixelStreaming2FromStreamerMessage`)
- L108 _externvar_ `extern const FString FreezeFrame;` (scope `EPixelStreaming2FromStreamerMessage`)
- L109 _externvar_ `extern const FString UnfreezeFrame;` (scope `EPixelStreaming2FromStreamerMessage`)
- L110 _externvar_ `extern const FString VideoEncoderAvgQP;` (scope `EPixelStreaming2FromStreamerMessage`)
- L111 _externvar_ `extern const FString LatencyTest;` (scope `EPixelStreaming2FromStreamerMessage`)
- L112 _externvar_ `extern const FString InitialSettings;` (scope `EPixelStreaming2FromStreamerMessage`)
- L113 _externvar_ `extern const FString FileExtension;` (scope `EPixelStreaming2FromStreamerMessage`)
- L114 _externvar_ `extern const FString FileMimeType;` (scope `EPixelStreaming2FromStreamerMessage`)
- L115 _externvar_ `extern const FString FileContents;` (scope `EPixelStreaming2FromStreamerMessage`)
- L116 _externvar_ `extern const FString TestEcho;` (scope `EPixelStreaming2FromStreamerMessage`)
- L117 _externvar_ `extern const FString InputControlOwnership;` (scope `EPixelStreaming2FromStreamerMessage`)
- L118 _externvar_ `extern const FString GamepadResponse;` (scope `EPixelStreaming2FromStreamerMessage`)
- L119 _externvar_ `extern const FString Multiplexed;` (scope `EPixelStreaming2FromStreamerMessage`)
- L120 _externvar_ `extern const FString Protocol;` (scope `EPixelStreaming2FromStreamerMessage`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Public/PixelStreaming2InputStructures.h` (Public)


#### struct `UE::PixelStreaming2Input::TPayloadParser`  
`template <uint32... Indices> struct TPayloadParser<TIntegerSequence<uint32, Indices...>>`  
_L15-22_
- L18 _public function_ `template <typename TupleType> static void Parse(TupleType&& Tuple, FArchive& Ar)`

#### struct `UE::PixelStreaming2Input::TPayload`  
`template <typename... Types> struct TPayload : public TTuple<std::decay_t<Types>...>`  
_L25-31_
- inherits: `TTuple<std::decay_t<Types>...>`
- L27 _public function_ `TPayload(FArchive& Ar)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreaming2Input` (scope `UE`)
- L20 _function_ `([](auto& Arg, FArchive& Ar) { Ar << Arg; }(Forward<TupleType>(Tuple).template Get<Indices>(), Ar), ...);` (scope `UE::PixelStreaming2Input::TPayloadParser::Parse`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Input/Public/PixelStreaming2JavaScriptKeyCodes.inl` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PixelStreaming2Input` (scope `UE`)
- L19 _variable_ `static const FKey* JavaScriptKeyCodeToFKey[256] = { &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::BackSpace, &EKeys::Tab, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Enter, &EKeys::Invalid, &EKeys::Invalid, &EKeys::LeftShift, &EKeys::LeftControl, &EKeys::LeftAlt, &EKeys::Pause, &EKeys::CapsLock, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Escape, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::SpaceBar, &EKeys::PageUp, &EKeys::PageDown, &EKeys::End, &EKeys::Home, &EKeys::Left,` (scope `UE::PixelStreaming2Input`)
