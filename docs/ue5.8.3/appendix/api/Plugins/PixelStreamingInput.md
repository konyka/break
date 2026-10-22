# Plugins / PixelStreamingInput

- module root: `Plugins/Media/PixelStreaming/Source/PixelStreamingInput`
- headers: 16; symbols: 335
- symbol kinds: class=10, delegate=2, enum=4, enumerator=18, externvar=3, function=68, member=76, namespace=17, prototype=120, struct=13, typedef=3, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, HeadMountedDisplay, InputDevice, Json, Slate, SlateCore, XRBase
- PublicDependencyModuleNames: ApplicationCore, Core, InputCore, PixelStreamingHMD

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Private/ApplicationWrapper.h` (Private)


#### class `UE::PixelStreamingInput::FPixelStreamingApplicationWrapper`  
`class FPixelStreamingApplicationWrapper : public GenericApplication`  
_L14-66_
- inherits: `GenericApplication`
- desc: Wrap the GenericApplication layer so we can replace the cursor and override certain behavior.
- L17 _public prototype_ `FPixelStreamingApplicationWrapper(TSharedPtr<GenericApplication> InWrappedApplication);`
- L22 _public function_ `virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)` — Functions passed directly to the wrapped application.
- L23 _public function_ `virtual void PollGameDeviceState(const float TimeDelta)`
- L24 _public function_ `virtual void PumpMessages(const float TimeDelta)`
- L25 _public function_ `virtual void ProcessDeferredEvents(const float TimeDelta)`
- L26 _public function_ `virtual void Tick(const float TimeDelta)`
- L27 _public function_ `virtual TSharedRef<FGenericWindow> MakeWindow()`
- L28 _public function_ `virtual void InitializeWindow(const TSharedRef<FGenericWindow>& Window, const TSharedRef<FGenericWindowDefinition>& InDefinition, const TSharedPtr<FGenericWindow>& InParent, const bool bShowImmediately)`
- L29 _public function_ `virtual void SetCapture(const TSharedPtr<FGenericWindow>& InWindow)`
- L30 _public function_ `virtual void* GetCapture(void) const`
- L31 _public function_ `virtual FModifierKeysState GetModifierKeys() const`
- L32 _public function_ `virtual void SetHighPrecisionMouseMode(const bool Enable, const TSharedPtr<FGenericWindow>& InWindow)`
- L33 _public function_ `virtual bool IsUsingHighPrecisionMouseMode() const`
- L34 _public function_ `virtual bool IsUsingTrackpad() const`
- L35 _public function_ `virtual bool IsGamepadAttached() const`
- L36 _public function_ `virtual void RegisterConsoleCommandListener(const FOnConsoleCommandListener& InListener)`
- L37 _public function_ `virtual void AddPendingConsoleCommand(const FString& InCommand)`
- L38 _public function_ `virtual FPlatformRect GetWorkArea(const FPlatformRect& CurrentWindow) const`
- L39 _public function_ `virtual bool TryCalculatePopupWindowPosition(const FPlatformRect& InAnchor, const FVector2D& InSize, const FVector2D& ProposedPlacement, const EPopUpOrientation::Type Orientation, FVector2D* const CalculatedPopUpPosition) const`
- L40 _public function_ `virtual void GetInitialDisplayMetrics(FDisplayMetrics& OutDisplayMetrics) const`
- L41 _public function_ `virtual EWindowTitleAlignment::Type GetWindowTitleAlignment() const`
- L42 _public function_ `virtual EWindowTransparency GetWindowTransparencySupport() const`
- L43 _public function_ `virtual void DestroyApplication()`
- L44 _public function_ `virtual IInputInterface* GetInputInterface()`
- L45 _public function_ `virtual ITextInputMethodSystem* GetTextInputMethodSystem()`
- L46 _public function_ `virtual void SendAnalytics(IAnalyticsProvider* Provider)`
- L47 _public function_ `virtual bool SupportsSystemHelp() const`
- L48 _public function_ `virtual void ShowSystemHelp()`
- L49 _public function_ `virtual bool ApplicationLicenseValid(FPlatformUserId PlatformUser = PLATFORMUSERID_NONE)`
- L54 _public function_ `virtual bool IsMouseAttached() const` — Functions with overridden behavior.
- L55 _public function_ `virtual bool IsCursorDirectlyOverSlateWindow() const`
- L56 _public prototype_ `virtual TSharedPtr<FGenericWindow> GetWindowUnderCursor() override;`
- L61 _public prototype_ `virtual void SetTargetWindow(TWeakPtr<SWindow> InTargetWindow);` — Custom functions
- L63 _public member_ `TSharedPtr<GenericApplication> WrappedApplication;`
- L64 _public member_ `TWeakPtr<SWindow> TargetWindow;`
- L65 _public member_ `bool bMouseAlwaysAttached;`

#### class `UE::PixelStreamingInput::FCursor`  
`class FCursor : public ICursor`  
_L74-91_
- inherits: `ICursor`
- desc: When reading input from a browser then the cursor position will be sent across with mouse events. We want to use this position and avoid getting the cursor position from the operating system. This is not relevant to touch events.
- L77 _public function_ `FCursor()`
- L78 _public prototype_ `virtual ~FCursor() = default;`
- L79 _public function_ `virtual FVector2D GetPosition() const override`
- L80 _public function_ `virtual void SetPosition(const int32 X, const int32 Y) override`
- L81 _public function_ `virtual void SetType(const EMouseCursor::Type InNewCursor) override`
- L82 _public function_ `virtual EMouseCursor::Type GetType() const override`
- L83 _public function_ `virtual void GetSize(int32& Width, int32& Height) const override`
- L84 _public function_ `virtual void Show(bool bShow) override`
- L85 _public function_ `virtual void Lock(const RECT* const Bounds) override`
- L86 _public function_ `virtual void SetTypeShape(EMouseCursor::Type InCursorType, void* CursorHandle) override`
- L90 _private member_ `FVector2D Position;` — The cursor position sent across with mouse events.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreamingInput` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Private/InputStructures.h` (Private)


#### struct `UE::PixelStreamingInput::TPayloadNoParam`  
`struct TPayloadNoParam`  
_L11-26_
- L13 _public function_ `TPayloadNoParam()`
- L17 _public function_ `TPayloadNoParam(FArchive& Ar)`
- L21 _public function_ `TArray<uint8> AsData()`

#### struct `UE::PixelStreamingInput::TPayloadOneParam`  
`template <typename ParamOneType> struct TPayloadOneParam`  
_L29-50_
- L31 _public member_ `ParamOneType Param1;`
- L33 _public function_ `TPayloadOneParam(FArchive& Ar)`
- L39 _public function_ `TPayloadOneParam(ParamOneType InParam1)`
- L44 _public function_ `TArray<uint8> AsData()`

#### struct `UE::PixelStreamingInput::TPayloadTwoParam`  
`template <typename ParamOneType, typename ParamTwoType> struct TPayloadTwoParam`  
_L53-78_
- L55 _public member_ `ParamOneType Param1;`
- L56 _public member_ `ParamTwoType Param2;`
- L58 _public function_ `TPayloadTwoParam(FArchive& Ar)`
- L66 _public function_ `TPayloadTwoParam(ParamOneType InParam1, ParamTwoType InParam2)`
- L72 _public function_ `TArray<uint8> AsData()`

#### struct `UE::PixelStreamingInput::TPayloadThreeParam`  
`template <typename ParamOneType, typename ParamTwoType, typename ParamThreeType> struct TPayloadThreeParam`  
_L81-110_
- L83 _public member_ `ParamOneType Param1;`
- L84 _public member_ `ParamTwoType Param2;`
- L85 _public member_ `ParamThreeType Param3;`
- L87 _public function_ `TPayloadThreeParam(FArchive& Ar)`
- L97 _public function_ `TPayloadThreeParam(ParamOneType InParam1, ParamTwoType InParam2, ParamThreeType InParam3)`
- L104 _public function_ `TArray<uint8> AsData()`

#### struct `UE::PixelStreamingInput::TPayloadFourParam`  
`template <typename ParamOneType, typename ParamTwoType, typename ParamThreeType, typename ParamFourType> struct TPayloadFourParam`  
_L113-146_
- L115 _public member_ `ParamOneType Param1;`
- L116 _public member_ `ParamTwoType Param2;`
- L117 _public member_ `ParamThreeType Param3;`
- L118 _public member_ `ParamFourType Param4;`
- L120 _public function_ `TPayloadFourParam(FArchive& Ar)`
- L132 _public function_ `TPayloadFourParam(ParamOneType InParam1, ParamTwoType InParam2, ParamThreeType InParam3, ParamFourType InParam4)`
- L140 _public function_ `TArray<uint8> AsData()`

#### struct `UE::PixelStreamingInput::TPayloadFiveParam`  
`template <typename ParamOneType, typename ParamTwoType, typename ParamThreeType, typename ParamFourType, typename ParamFiveType> struct TPayloadFiveParam`  
_L149-186_
- L151 _public member_ `ParamOneType Param1;`
- L152 _public member_ `ParamTwoType Param2;`
- L153 _public member_ `ParamThreeType Param3;`
- L154 _public member_ `ParamFourType Param4;`
- L155 _public member_ `ParamFiveType Param5;`
- L157 _public function_ `TPayloadFiveParam(FArchive& Ar)`
- L171 _public function_ `TPayloadFiveParam(ParamOneType InParam1, ParamTwoType InParam2, ParamThreeType InParam3, ParamFourType InParam4, ParamFiveType InParam5)`
- L180 _public function_ `TArray<uint8> AsData()`

#### struct `UE::PixelStreamingInput::FTouch`  
`struct FTouch`  
_L192-199_
- desc: A touch is a specific finger placed on the canvas as a specific position.
- L194 _public member_ `uint16 PosX;` — X position of finger.
- L195 _public member_ `uint16 PosY;` — Y position of finger.
- L196 _public member_ `uint8 TouchIndex;` — Index of finger for tracking multi-touch events.
- L197 _public member_ `uint8 Force;` — Amount of pressure being applied by the finger.
- L198 _public member_ `uint8 Valid;` — 1 if the touch was within bounds.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreamingInput` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Private/JavaScriptKeyCodes.inl` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PixelStreamingInput` (scope `UE`)
- L19 _variable_ `static const FKey* JavaScriptKeyCodeToFKey[256] = { &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::BackSpace, &EKeys::Tab, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Enter, &EKeys::Invalid, &EKeys::Invalid, &EKeys::LeftShift, &EKeys::LeftControl, &EKeys::LeftAlt, &EKeys::Pause, &EKeys::CapsLock, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Escape, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::Invalid, &EKeys::SpaceBar, &EKeys::PageUp, &EKeys::PageDown, &EKeys::End, &EKeys::Home, &EKeys::Left,` (scope `UE::PixelStreamingInput`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Private/PixelStreamingInputDevice.h` (Private)


#### class `UE::PixelStreamingInput::FPixelStreamingInputDevice`  
`class FPixelStreamingInputDevice : public IInputDevice`  
_L14-61_
- inherits: `IInputDevice`
- desc: @brief The input device used to interface the multiple streamers and the single input device created by the OS
- L17 _public prototype_ `void Tick(float DeltaTime) override;`
- L19 _public function_ `virtual void SendControllerEvents() override` — Poll for controller state and send events if needed
- L22 _public prototype_ `virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InTargetHandler) override;` — Set which MessageHandler will route input
- L25 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — Exec handler to allow console commands to be passed through for debugging
- L26 _public prototype_ `virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;`
- L27 _public prototype_ `virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values) override;`
- L29 _public prototype_ `void AddInputHandler(TSharedPtr<IPixelStreamingInputHandler> InputHandler);`
- L30 _public prototype_ `uint8 OnControllerConnected();`
- L31 _public prototype_ `void OnControllerDisconnected(uint8 DeleteControllerId);`
- L33 _public prototype_ `static TSharedPtr<FPixelStreamingInputDevice> GetInputDevice();`
- L36 _private prototype_ `FPixelStreamingInputDevice();`
- L43 _private member_ `static TSharedPtr<FPixelStreamingInputDevice> InputDevice;` — A singleton pointer to the input device. We only want a single input device that has multiple input handlers. The reason for a single input device is that only one is created by the application, so make sure we always use that one
- L51 _private member_ `TArray<TWeakPtr<IPixelStreamingInputHandler>> InputHandlers;` — The array of input handlers. Each input handler belongs to a single streamer NOTE: We store each input handler as a weakptr as we don't want to be the reason the handler doesn't get deleted. Each handler should be tied to a Streamer's lifecycle
- L60 _private member_ `TArray<uint8> ConnectedControllers;` — The array of connected controllers. As each device can have multiple controllers, we want to make sure that each controller of each device is unique As such, a simple incrementer approach is not applicable and we must instead keep track of all the connected controllers NOTE: We store each input handler as a weakptr as we don't want to be the reason the handler doesn't get deleted. Each handler should be tied to a Streamer's lifecycle

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreamingInput` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Private/PixelStreamingInputHandler.h` (Private)


#### class `UE::PixelStreamingInput::FPixelStreamingInputHandler`  
`class FPixelStreamingInputHandler : public IPixelStreamingInputHandler, public FXRMotionControllerBase`  
_L18-255_
- inherits: `IPixelStreamingInputHandler,FXRMotionControllerBase`
- L21 _public prototype_ `FPixelStreamingInputHandler(TSharedPtr<FPixelStreamingApplicationWrapper> InApplicationWrapper, const TSharedPtr<FGenericApplicationMessageHandler>& InTargetHandler);`
- L23 _public prototype_ `virtual ~FPixelStreamingInputHandler();`
- L25 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L28 _public function_ `virtual void SendControllerEvents() override` — Poll for controller state and send events if needed
- L31 _public prototype_ `virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InTargetHandler) override;` — Set which MessageHandler will route input
- L34 _public prototype_ `virtual void SetCommandHandler(const FString& CommandName, const CommandHandlerFn& Handler) override;` — Register a custom function to execute when command JSON is received.
- L36 _public prototype_ `virtual void SetElevatedCheck(const TFunction<bool(FString)>& CheckFn) override;`
- L37 _public prototype_ `virtual bool IsElevated(const FString& Id) override;`
- L40 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — Exec handler to allow console commands to be passed through for debugging
- L44 _public prototype_ `virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;` — IInputInterface pass through functions
- L45 _public prototype_ `virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues& values) override;`
- L46 _public prototype_ `virtual void OnMessage(FString SourceId, TArray<uint8> Buffer) override;`
- L47 _public prototype_ `virtual void SetTargetWindow(TWeakPtr<SWindow> InWindow) override;`
- L48 _public prototype_ `virtual TWeakPtr<SWindow> GetTargetWindow() override;`
- L49 _public prototype_ `virtual void SetTargetViewport(TWeakPtr<SViewport> InViewport) override;`
- L50 _public prototype_ `virtual TWeakPtr<SViewport> GetTargetViewport() override;`
- L51 _public prototype_ `virtual void SetTargetScreenRect(TWeakPtr<FIntRect> InScreenRect) override;`
- L52 _public prototype_ `virtual TWeakPtr<FIntRect> GetTargetScreenRect() override;`
- L53 _public function_ `virtual bool IsFakingTouchEvents() const override`
- L54 _public prototype_ `virtual void RegisterMessageHandler(const FString& MessageType, const MessageHandlerFn& Handler) override;`
- L55 _public prototype_ `virtual MessageHandlerFn FindMessageHandler(const FString& MessageType) override;`
- L56 _public function_ `virtual void SetInputType(EPixelStreamingInputType InInputType) override`
- L58 _public prototype_ `virtual FName GetMotionControllerDeviceTypeName() const override;` — IMotionController Interface
- L59 _public prototype_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, float WorldToMetersScale) const override;`
- L60 _public prototype_ `virtual ETrackingStatus GetControllerTrackingStatus(const int32 ControllerIndex, const FName MotionSource) const override;`
- L61 _public prototype_ `virtual void EnumerateSources(TArray<FMotionControllerSource>& SourcesOut) const override;`
- L69 _protected prototype_ `virtual void HandleOnKeyChar(FMemoryReader Ar);` — Key press handling
- L70 _protected prototype_ `virtual void HandleOnKeyDown(FMemoryReader Ar);`
- L71 _protected prototype_ `virtual void HandleOnKeyUp(FMemoryReader Ar);`
- L75 _protected prototype_ `virtual void HandleOnTouchStarted(FMemoryReader Ar);` — Touch handling
- L76 _protected prototype_ `virtual void HandleOnTouchMoved(FMemoryReader Ar);`
- L77 _protected prototype_ `virtual void HandleOnTouchEnded(FMemoryReader Ar);`
- L81 _protected prototype_ `virtual void HandleOnControllerConnected(FMemoryReader Ar);` — Controller handling
- L82 _protected prototype_ `virtual void HandleOnControllerAnalog(FMemoryReader Ar);`
- L83 _protected prototype_ `virtual void HandleOnControllerButtonPressed(FMemoryReader Ar);`
- L84 _protected prototype_ `virtual void HandleOnControllerButtonReleased(FMemoryReader Ar);`
- L85 _protected prototype_ `virtual void HandleOnControllerDisconnected(FMemoryReader Ar);`
- L89 _protected prototype_ `virtual void HandleOnMouseEnter(FMemoryReader Ar);` — Mouse handling
- L90 _protected prototype_ `virtual void HandleOnMouseLeave(FMemoryReader Ar);`
- L91 _protected prototype_ `virtual void HandleOnMouseUp(FMemoryReader Ar);`
- L92 _protected prototype_ `virtual void HandleOnMouseDown(FMemoryReader Ar);`
- L93 _protected prototype_ `virtual void HandleOnMouseMove(FMemoryReader Ar);`
- L94 _protected prototype_ `virtual void HandleOnMouseWheel(FMemoryReader Ar);`
- L95 _protected prototype_ `virtual void HandleOnMouseDoubleClick(FMemoryReader Ar);`
- L99 _protected prototype_ `virtual void HandleOnXREyeViews(FMemoryReader Ar);` — XR handling
- L100 _protected prototype_ `virtual void HandleOnXRHMDTransform(FMemoryReader Ar);`
- L101 _protected prototype_ `virtual void HandleOnXRControllerTransform(FMemoryReader Ar);`
- L102 _protected prototype_ `virtual void HandleOnXRButtonPressed(FMemoryReader Ar);`
- L103 _protected prototype_ `virtual void HandleOnXRButtonTouched(FMemoryReader Ar);`
- L104 _protected prototype_ `virtual void HandleOnXRButtonTouchReleased(FMemoryReader Ar);`
- L105 _protected prototype_ `virtual void HandleOnXRButtonReleased(FMemoryReader Ar);`
- L106 _protected prototype_ `virtual void HandleOnXRAnalog(FMemoryReader Ar);`
- L107 _protected prototype_ `virtual void HandleOnXRSystem(FMemoryReader Ar);`
- L111 _protected prototype_ `virtual void HandleOnCommand(FString SourceId, FMemoryReader Ar);` — Command handling
- L115 _protected prototype_ `virtual void HandleUIInteraction(FMemoryReader Ar);` — UI Interaction handling
- L119 _protected prototype_ `virtual void HandleOnTextboxEntry(FMemoryReader Ar);` — Textbox Entry handling
- L124 _protected prototype_ `void PopulateDefaultCommandHandlers();` — Populate default command handlers for data channel messages sent with "{ type: "Command" }".
- L129 _protected prototype_ `FMatrix ExtractWebXRMatrix(FMemoryReader& Ar);` — Extract 4x4 WebXR ordered matrix and convert to FMatrix.
- L137 _protected prototype_ `FTransform WebXRMatrixToUETransform(FMatrix Mat);` — Converts the 'Y up' 'right handed' WebXR coordinate system transform to Unreal's 'Z up' 'left handed' coordinate system. Note: Ignores scale. Assumes WebXR conforms to the following: (https://developer.mozilla.org/en-US/docs/Web/API/WebXR_Device_API/Geometry) @return A 4x4 z-up transform matrix for use with UE.
- L139 _protected prototype_ `FIntPoint ConvertFromNormalizedScreenLocation(const FVector2D& ScreenLocation, bool bIncludeOffset = true);`
- L140 _protected prototype_ `FWidgetPath FindRoutingMessageWidget(const FVector2D& Location) const;`
- L141 _protected prototype_ `FKey TranslateMouseButtonToKey(const EMouseButtons::Type Button);`
- L164 _protected member_ `TMap<int32, FCachedTouchEvent> CachedTouchEvents;` — Keep a cache of the last touch events as we need to fire Touch Moved every frame while touch is down
- L166 _protected typedef_ `using FKeyId = uint8;`
- L179 _protected member_ `TMap<FInputDeviceId, TMap<FKey*, FAnalogValue>> AnalogEventsReceivedThisTick;` — If more values are received in a single tick (e.g. could be temp network issue), then we only forward the latest value. Reason: The input system seems to expect at most one raw analog value per FKey per Tick. If this is not done, the input system can get stuck on non-zero input value even if the user has already stopped moving the analog stick. It would stay stuck until the next time the user moves the stick. The values arrive in the order of recording: that means once the player releases the analog, the last analog value would be 0.
- L182 _protected prototype_ `void ProcessLatestAnalogInputFromThisTick();` — Forwards the latest analog input received for each key this tick.
- L185 _protected member_ `TSet<int32> TouchIndicesProcessedThisFrame;` — Track which touch events we processed this frame so we can avoid re-processing them
- L188 _protected prototype_ `void BroadcastActiveTouchMoveEvents();` — Sends Touch Moved events for any touch index which is currently down but wasn't already updated this frame
- L190 _protected prototype_ `void FindFocusedWidget();`
- L191 _protected prototype_ `bool FilterKey(const FKey& Key);`
- L200 _protected member_ `TWeakPtr<SWindow> TargetWindow;`
- L201 _protected member_ `TWeakPtr<SViewport> TargetViewport;`
- L202 _protected member_ `TWeakPtr<FIntPoint> TargetScreenSize;` — Deprecated functionality but remaining until it can be removed
- L203 _protected member_ `TWeakPtr<FIntRect> TargetScreenRect;` — Manual size override used when we don't have a single window/viewport target
- L204 _protected member_ `uint8 NumActiveTouches;`
- L205 _protected member_ `bool bIsMouseActive;`
- L206 _protected member_ `TQueue<FMessage> Messages;`
- L207 _protected member_ `EPixelStreamingInputType InputType = EPixelStreamingInputType::RouteToWindow;`
- L208 _protected member_ `FVector2D LastTouchLocation = FVector2D(EForceInit::ForceInitToZero);`
- L209 _protected member_ `TMap<uint8, MessageHandlerFn> DispatchTable;`
- L212 _protected member_ `TSharedPtr<FGenericApplicationMessageHandler> MessageHandler;` — Reference to the message handler which events should be passed to.
- L215 _protected member_ `TSharedPtr<FPixelStreamingApplicationWrapper> PixelStreamerApplicationWrapper;` — For convenience, we keep a reference to the application wrapper owned by the input channel
- L222 _protected member_ `bool bFakingTouchEvents;` — Is the application faking touch events by dragging the mouse along the canvas? If so then we must put the browser canvas in a special state to replicate the behavior of the application.
- L229 _protected member_ `const size_t MessageHeaderOffset = 1;` — Padding for string parsing when handling messages. 1 character for the actual message and then 2 characters for the length which are skipped
- L238 _protected member_ `TMap<EControllerHand, FPixelStreamingXRController> XRControllers;`
- L248 _protected member_ `TMap<FString, CommandHandlerFn> CommandHandlers;` — A map of named commands we respond to when we receive a datachannel message of type "command". Key = command name (e.g "Encoder.MaxQP") Value = The command handler lambda function whose parameters are as follows: FString - the source id of the user who sent the message FString - the descriptor (e.g. the full json payload of the command message) FString - the parsed value of the command, e.g. if key was "Encoder.MaxQP" and descriptor was { type: "Command", "Encoder.MaxQP": 51 }, then parsed value is "51".
- L250 _protected member_ `TFunction<bool(FString)> ElevatedCheck;`
- L253 _private member_ `float uint16_MAX = (float)UINT16_MAX;`
- L254 _private member_ `float int16_MAX = (float)SHRT_MAX;`

#### struct `UE::PixelStreamingInput::FPixelStreamingInputHandler::FCachedTouchEvent`  
`struct FCachedTouchEvent`  
_L143-148_
- L145 _public member_ `FVector2D Location;`
- L146 _public member_ `float Force;`
- L147 _public member_ `int32 ControllerIndex;`

#### struct `UE::PixelStreamingInput::FPixelStreamingInputHandler::FAnalogValue`  
`struct FAnalogValue`  
_L150-161_
- L153 _public member_ `double Value;` — The actual analog value from the controller axis, typical 0.0..1.0
- L158 _public member_ `bool bKeepUnlessZero = false;` — If value is non-zero then keep applying this analog values across frames. This is useful for trigger axis inputs where if a value is not transmitted UE will assume a gap in input means a full trigger press (which is not accurate if we were still pressing).
- L160 _public member_ `bool bIsRepeat = false;` — Has this key event already been fired once?

#### struct `UE::PixelStreamingInput::FPixelStreamingInputHandler::FMessage`  
`struct FMessage`  
_L193-198_
- L195 _public member_ `FString SourceId;`
- L196 _public member_ `TFunction<void(FString, FMemoryReader)>* Handler;`
- L197 _public member_ `TArray<uint8> Data;`

#### struct `UE::PixelStreamingInput::FPixelStreamingInputHandler::FPixelStreamingXRController`  
`struct FPixelStreamingXRController`  
_L231-236_
- L234 _public member_ `FTransform Transform;`
- L235 _public member_ `EControllerHand Handedness;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace PixelStreamingInput` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Private/PixelStreamingInputModule.h` (Private)


#### class `UE::PixelStreamingInput::FPixelStreamingInputModule`  
`class FPixelStreamingInputModule : public IPixelStreamingInputModule`  
_L10-28_
- inherits: `IPixelStreamingInputModule`
- L13 _public prototype_ `virtual TSharedPtr<IPixelStreamingInputHandler> CreateInputHandler() override;`
- L17 _private prototype_ `void StartupModule() override;` — IModuleInterface implementation
- L18 _private prototype_ `void ShutdownModule() override;`
- L22 _private prototype_ `virtual TSharedPtr<IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;` — IInputDeviceModule implementation
- L25 _private member_ `TSharedPtr<FPixelStreamingInputDevice> InputDevice;`
- L27 _private prototype_ `void PopulateProtocol();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreamingInput` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Private/Settings.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreamingInput` (scope `UE`)
- L10 _namespace_ `namespace Settings` (scope `UE::PixelStreamingInput`)
- L13 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingInputAllowConsoleCommands;` (scope `UE::PixelStreamingInput::Settings`)
- L14 _externvar_ `extern TAutoConsoleVariable<FString> CVarPixelStreamingInputKeyFilter;` (scope `UE::PixelStreamingInput::Settings`)
- L15 _externvar_ `extern TArray<FKey> FilteredKeys;` (scope `UE::PixelStreamingInput::Settings`)
- L18 _prototype_ `extern void InitialiseSettings();` (scope `UE::PixelStreamingInput::Settings`)
- L19 _prototype_ `extern void CommandLineParseOption();` (scope `UE::PixelStreamingInput::Settings`)
- L21 _prototype_ `template <typename T> extern void CommandLineParseValue(const TCHAR* Match, TAutoConsoleVariable<T>& CVar);` (scope `UE::PixelStreamingInput::Settings`)
- L22 _prototype_ `extern void CommandLineParseValue(const TCHAR* Match, TAutoConsoleVariable<FString>& CVar, bool bStopOnSeparator = false);` (scope `UE::PixelStreamingInput::Settings`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Private/Utils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreamingInput` (scope `UE`)
- L13 _function_ `inline void ExtendJsonWithField(const FString& Descriptor, FString FieldName, FString StringValue, FString& NewDescriptor, bool& Success)` (scope `UE::PixelStreamingInput`)
- L34 _function_ `inline void ExtractJsonFromDescriptor(FString Descriptor, FString FieldName, FString& StringValue, bool& Success)` (scope `UE::PixelStreamingInput`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Public/EditorPixelStreamingSettings.h` (Public)


#### class `UPixelStreamingSettings`  
`class UPixelStreamingSettings : public UDeveloperSettings`  
_L12-61_
- reflection: `UCLASS(config = PixelStreaming, defaultconfig, meta = (DisplayName = "PixelStreaming"))`
- inherits: `UDeveloperSettings`
- desc: Config loaded/saved to an .ini file. It is also exposed through the plugin settings page in editor.
- L22 _public member_ `bool EnablePixelStreamingToolbar = true;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( ConfigRestartRequired = true, DisplayName = "Enable Pixel Streaming Toolbar", ToolTip = "Adds the Pixel Streaming toolbar to the main viewport toolbar." ))`
- L30 _public member_ `FSoftClassPath DefaultCursorClassName;` — `UPROPERTY(config, EditAnywhere, Category = PixelStreaming)` — Pixel streaming always requires various software cursors so they will be visible in the video stream sent to the browser to allow the user to click and interact with UI elements.
- L32 _public member_ `FSoftClassPath TextEditBeamCursorClassName;` — `UPROPERTY(config, EditAnywhere, Category = PixelStreaming)`
- L41 _public member_ `FSoftClassPath HiddenCursorClassName;` — `UPROPERTY(config, EditAnywhere, Category = PixelStreaming)` — Pixel Streaming can have a server-side cursor (where the cursor itself is shown as part of the video), or a client-side cursor (where the cursor is shown by the browser). In the latter case we need to turn the UE4 cursor invisible.
- L49 _public member_ `bool bMouseAlwaysAttached = true;` — `UPROPERTY(config, EditAnywhere, Category = PixelStreaming)` — Pixel Streaming may be running on a machine which has no physical mouse attached, and yet the browser is sending mouse positions. As such, we fake the presence of a mouse.
- L52 _public prototype_ `virtual FName GetCategoryName() const override;`
- L54 _public prototype_ `virtual FText GetSectionText() const override;`
- L59 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Public/IPixelStreamingInputHandler.h` (Public)


#### class `IPixelStreamingInputHandler`  
`class IPixelStreamingInputHandler : public IInputDevice`  
_L18-133_
- inherits: `IInputDevice`
- desc: The IPixelStreamingInputHandler, used to handle input from a remote peer and pass it to UE accordingly. Setting the target viewport allows for scaling of input from browser to application, and setting the target window ensure that if windows are tiled (eg editor) that the streamed input only affect the target window.
- L26 _public prototype_ `virtual void OnMessage(FString SourceId, TArray<uint8> Buffer) = 0;` — @brief Handle the message from the WebRTC data channel. @param SourceId A source ID for this message @param Buffer The data channel message
- L32 _public prototype_ `virtual void SetTargetViewport(TWeakPtr<SViewport> InTargetViewport) = 0;` — @brief Set the viewport this input device is associated with. @param InTargetViewport The viewport to set
- L38 _public prototype_ `virtual TWeakPtr<SViewport> GetTargetViewport() = 0;` — @brief Get the viewport this input device is associated with. @return The viewport this input device is associated with
- L44 _public prototype_ `virtual void SetTargetWindow(TWeakPtr<SWindow> InTargetWindow) = 0;` — @brief Set the viewport this input device is associated with. @param InTargetWindow The viewport to set
- L50 _public prototype_ `virtual TWeakPtr<SWindow> GetTargetWindow() = 0;` — @brief Get the viewport this input device is associated with. @return The viewport this input device is associated with
- L57 _public prototype_ `virtual void SetTargetScreenRect(TWeakPtr<FIntRect> InTargetScreenRect) = 0;` — @brief Set the target screen rectangle for this streamer. This is used to when the streamer doesn't have a singular target window / viewport and as such we just use the manual scale @param InTargetScreenRect The target screen rectangle
- L63 _public prototype_ `virtual TWeakPtr<FIntRect> GetTargetScreenRect() = 0;` — @brief Get the target screen rectangle for this streamer @return The target screen rectangle
- L70 _public prototype_ `virtual bool IsFakingTouchEvents() const = 0;` — @brief Set whether the input devices is faking touch events using keyboard and mouse this can be useful for debugging. @return true @return false
- L78 _public typedef_ `using MessageHandlerFn = TFunction<void(FString SourceId, FMemoryReader Message)>;` — @brief The callback signature for handling a command sent to the data channel. @param SourceId The source id of the sender of this message. @param Message The full message in the form of a FMemoryReader.
- L86 _public prototype_ `virtual void RegisterMessageHandler(const FString& MessageType, const MessageHandlerFn& Handler) = 0;` — @brief Register a function to be called whenever the specified message type is received. @param MessageType The human readable identifier for the message @param Handler The function called when this message type is received. This handler must take a single parameter (an FMemoryReader) and have a return type of void
- L95 _public typedef_ `using CommandHandlerFn = TFunction<void(FString SourceId, FString Descriptor, FString CommandString)>;` — @brief The callback signature for handling a command sent to the data channel. @param SourceId The source id of the sender of this message. @param Descriptor The full descriptor of the commaand. @param CommandString The relevant string parameters for the command.
- L101 _public prototype_ `virtual void SetCommandHandler(const FString& CommandName, const CommandHandlerFn& Handler) = 0;` — @brief Register a custom function to execute when command JSON is received over the data channel: "{ type: "Command", YourCommand: YourCommandValue }". Note: You can also override the default Pixel Streaming command handlers by setting handlers with the same name as those already used, e.g. "Stat.FPS".
- L108 _public prototype_ `virtual void SetElevatedCheck(const TFunction<bool(FString)>& CheckFn) = 0;` — @brief Some behaviours might want to be limited to a specific source or group of sources. This method sets a check function to test of a given source id is "elevated". @param CheckFn A callback that takes a SourceId and returns true if the source id is an elevated user.
- L116 _public prototype_ `virtual bool IsElevated(const FString& Id) = 0;` — @brief Checks whether the given id has elevated priviledges. @return true The id is elevated. @return false The id is not elevated.
- L124 _public prototype_ `virtual MessageHandlerFn FindMessageHandler(const FString& MessageType) = 0;` — @brief Find the function to be called whenever the specified message type is received. @param MessageType The human readable identifier for the message @return TFunction<void(FString, FMemoryReader)> The function called when this message type is received.
- L129 _public prototype_ `virtual void SetInputType(EPixelStreamingInputType InputType) = 0;` — @brief Set the input handlers type. This controls whether input is routed to widgets or windows
- L131 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSendMessage, FString, FMemoryReader);`
- L132 _public member_ `FOnSendMessage OnSendMessage;`

#### Free symbols / members of external scopes

- L131 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSendMessage, FString, FMemoryReader);`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Public/IPixelStreamingInputModule.h` (Public)


#### class `IPixelStreamingInputModule`  
`class IPixelStreamingInputModule : public IInputDeviceModule`  
_L13-50_
- inherits: `IInputDeviceModule`
- desc: The public interface of the Pixel Streaming Input module.
- L22 _public function_ `static inline IPixelStreamingInputModule& Get()` — Singleton-like access to this module's interface. Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded. @return True if the module is loaded.
- L39 _public prototype_ `virtual TSharedPtr<IPixelStreamingInputHandler> CreateInputHandler() = 0;` — @brief Create a Input Handler object @return TSharedPtr<IPixelStreamingInputHandler> the input handler for this streamer
- L46 _public prototype_ `virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override = 0;` — Attempts to create a new input device interface @return	Interface to the new input device, if we were able to successfully create one
- L48 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnProtocolUpdated);`
- L49 _public member_ `FOnProtocolUpdated OnProtocolUpdated;`

#### Free symbols / members of external scopes

- L48 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnProtocolUpdated);`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Public/PixelStreamingInputConversion.h` (Public)


#### struct `FPixelStreamingInputConverter`  
`struct FPixelStreamingInputConverter`  
_L11-16_
- L14 _public member_ `static TMap<TTuple<EPixelStreamingXRSystem, EControllerHand, uint8, EPixelStreamingInputAction>, FKey> XRInputToFKey;`
- L15 _public member_ `static TMap<TTuple<uint8, EPixelStreamingInputAction>, FKey> GamepadInputToFKey;`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Public/PixelStreamingInputEnums.h` (Public)


#### enum `EPixelStreamingMessageTypes`  
`enum class EPixelStreamingMessageTypes`  
_L11-21_
- desc: @brief The data types supported when sending messages across the data channel to/from peers
- L13 _public enumerator_ `Uint8`
- L14 _public enumerator_ `Uint16`
- L15 _public enumerator_ `Int16`
- L16 _public enumerator_ `Float`
- L17 _public enumerator_ `Double`
- L18 _public enumerator_ `Variable UE_DEPRECATED(5.3, "EPixelStreamingMessageTypes::Variable has been deprecated. Please use either String or Undefined instead")`
- L19 _public enumerator_ `String`
- L20 _public enumerator_ `Undefined`

#### enum `EPixelStreamingMessageDirection`  
`enum class EPixelStreamingMessageDirection : uint8`  
_L27-31_
- desc: @brief The message directions
- L29 _public enumerator_ `ToStreamer = 0`
- L30 _public enumerator_ `FromStreamer = 1`

#### enum `EPixelStreamingInputAction`  
`enum class EPixelStreamingInputAction : uint8`  
_L37-45_
- desc: @brief The possible actions pixel streaming supports. These actions help differentiate input received from the browser
- L39 _public enumerator_ `X = 0`
- L40 _public enumerator_ `Y = 1`
- L41 _public enumerator_ `Axis`
- L42 _public enumerator_ `Click`
- L43 _public enumerator_ `Touch`
- L44 _public enumerator_ `None`

#### enum `EPixelStreamingInputType`  
`enum class EPixelStreamingInputType : uint8`  
_L51-55_
- desc: @brief The possible control schemes pixel streaming supports. RouteToWindow routes input at an application level. RouteToWidget routes input to a specific widget, ignoring the rest of the application.
- L53 _public enumerator_ `RouteToWindow`
- L54 _public enumerator_ `RouteToWidget`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Public/PixelStreamingInputMessage.h` (Public)


#### class `FPixelStreamingInputMessage`  
`class FPixelStreamingInputMessage`  
_L10-35_
- L14 _public prototype_ `FPixelStreamingInputMessage();` — Emtpy constructor. Sets ID to next available ID, and Structure to []
- L17 _public prototype_ `FPixelStreamingInputMessage(uint8 InId);` — Constructor taking an ID. Sets Structure to []
- L20 _public prototype_ `FPixelStreamingInputMessage(TArray<EPixelStreamingMessageTypes> InStructure);` — Constructor taking a Structure. Sets ID to next available ID
- L23 _public prototype_ `FPixelStreamingInputMessage(uint8 InId, TArray<EPixelStreamingMessageTypes> InStructure);` — Constructor taking an ID and a Structure
- L26 _public function_ `uint8 GetByteLength() const` — `UE_DEPRECATED(5.3, "ByteLength no longer exists on FPixelStreamingInputMessage.")`
- L27 _public function_ `uint8 GetID() const`
- L28 _public function_ `TArray<EPixelStreamingMessageTypes> GetStructure() const`
- L31 _private member_ `uint8 Id;`
- L32 _private member_ `TArray<EPixelStreamingMessageTypes> Structure;`
- L34 _private member_ `static uint8 CurrentId;`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Public/PixelStreamingInputProtocol.h` (Public)


#### struct `FPixelStreamingInputProtocol`  
`struct FPixelStreamingInputProtocol`  
_L13-20_
- L16 _public member_ `static FInputProtocolMap ToStreamerProtocol;`
- L17 _public member_ `static FInputProtocolMap FromStreamerProtocol;`
- L19 _public prototype_ `static TSharedPtr<FJsonObject> ToJson(EPixelStreamingMessageDirection Direction);`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Public/PixelStreamingInputProtocolMap.h` (Public)


#### class `FInputProtocolMap`  
`class FInputProtocolMap`  
_L13-29_
- desc: @brief An map type that broadcasts the OnProtocolUpdated whenever it's inner map is updated
- L16 _public prototype_ `FPixelStreamingInputMessage& Add(FString Key, const FPixelStreamingInputMessage& Value);`
- L17 _public prototype_ `int Remove(FString Key);`
- L18 _public prototype_ `FPixelStreamingInputMessage& GetOrAdd(FString Key);`
- L19 _public prototype_ `FPixelStreamingInputMessage* Find(FString Key);`
- L20 _public prototype_ `const FPixelStreamingInputMessage* Find(FString Key) const;`
- L22 _public prototype_ `void Clear();`
- L23 _public prototype_ `bool IsEmpty() const;`
- L25 _public prototype_ `void Apply(const TFunction<void(FString, FPixelStreamingInputMessage)>& Visitor);`
- L28 _private member_ `TMap<FString, FPixelStreamingInputMessage> InnerMap;`
