# Plugins / RemoteSession

- module root: `Plugins/Experimental/RemoteSession/Source/RemoteSession`
- headers: 21; symbols: 710
- symbol kinds: class=29, delegate=6, enum=5, enumerator=14, function=92, macro=11, member=201, prototype=337, struct=15
- PrivateDependencyModuleNames: AnalyticsET, AppleImageUtils, AugmentedReality, CoreUObject, EditorFramework, Engine, EngineSettings, HeadMountedDisplay, ImageWrapper, InputCore, InputDevice, MovieSceneCapture, PixelStreaming, PixelStreaming2, PixelStreaming2Editor, PixelStreaming2Servers, PixelStreaming2Settings, PixelStreamingEditor, PixelStreamingServers, RHI, RenderCore, Renderer, Slate, SlateCore, Sockets, UnrealEd
- PublicDependencyModuleNames: ApplicationCore, BackChannel, Core, MediaIOCore, XRBase

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Private/MessageHandler/Messages.h` (Private)


#### struct `NoParamMsg`  
`struct NoParamMsg`  
_L7-22_
- L9 _public function_ `NoParamMsg()`
- L13 _public function_ `NoParamMsg(FArchive& Ar)`
- L17 _public function_ `TArray<uint8> AsData()`

#### struct `TwoParamMsg`  
`template <typename P1, typename P2> struct TwoParamMsg`  
_L25-50_
- L27 _public member_ `P1 Param1;`
- L28 _public member_ `P2 Param2;`
- L30 _public function_ `TwoParamMsg(FArchive& Ar)`
- L38 _public function_ `TwoParamMsg(P1 InParam1, P2 InParam2)`
- L44 _public function_ `TArray<uint8> AsData()`

#### struct `ThreeParamMsg`  
`template <typename P1, typename P2, typename P3> struct ThreeParamMsg`  
_L53-82_
- L55 _public member_ `P1 Param1;`
- L56 _public member_ `P2 Param2;`
- L57 _public member_ `P3 Param3;`
- L59 _public function_ `ThreeParamMsg(FArchive& Ar)`
- L69 _public function_ `ThreeParamMsg(P1 InParam1, P2 InParam2, P3 InParam3)`
- L76 _public function_ `TArray<uint8> AsData()`

#### struct `FourParamMsg`  
`template <typename P1, typename P2, typename P3, typename P4> struct FourParamMsg`  
_L85-118_
- L87 _public member_ `P1 Param1;`
- L88 _public member_ `P2 Param2;`
- L89 _public member_ `P3 Param3;`
- L90 _public member_ `P4 Param4;`
- L92 _public function_ `FourParamMsg(FArchive& Ar)`
- L104 _public function_ `FourParamMsg(P1 InParam1, P2 InParam2, P3 InParam3, P4 InParam4)`
- L112 _public function_ `TArray<uint8> AsData()`

#### struct `FiveParamMsg`  
`template <typename P1, typename P2, typename P3, typename P4, typename P5> struct FiveParamMsg`  
_L121-158_
- L123 _public member_ `P1 Param1;`
- L124 _public member_ `P2 Param2;`
- L125 _public member_ `P3 Param3;`
- L126 _public member_ `P4 Param4;`
- L127 _public member_ `P5 Param5;`
- L129 _public function_ `FiveParamMsg(FArchive& Ar)`
- L143 _public function_ `FiveParamMsg(P1 InParam1, P2 InParam2, P3 InParam3, P4 InParam4, P5 InParam5)`
- L152 _public function_ `TArray<uint8> AsData()`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Private/MessageHandler/ProxyMessageHandler.h` (Private)


#### class `FProxyMessageHandler`  
`class FProxyMessageHandler : public FGenericApplicationMessageHandler`  
_L10-125_
- inherits: `FGenericApplicationMessageHandler`
- desc: Class that can act as a proxy for places where FGenericApplicationMessageHandler is used.
- L15 _public prototype_ `FProxyMessageHandler() = default;`
- L17 _public prototype_ `FProxyMessageHandler(const TSharedPtr<FGenericApplicationMessageHandler>& InTargetHandler);`
- L21 _public prototype_ `void SetTargetHandler(const TSharedPtr<FGenericApplicationMessageHandler>& InTargetHandler);`
- L23 _public prototype_ `const TSharedPtr<FGenericApplicationMessageHandler> GetTargetHandler() const;`
- L25 _public prototype_ `virtual bool ShouldProcessUserInputMessages(const TSharedPtr< FGenericWindow >& PlatformWindow) const override;`
- L27 _public prototype_ `virtual bool OnKeyChar(const TCHAR Character, const bool IsRepeat) override;`
- L29 _public prototype_ `virtual bool OnKeyDown(const int32 KeyCode, const uint32 CharacterCode, const bool IsRepeat) override;`
- L31 _public prototype_ `virtual bool OnKeyUp(const int32 KeyCode, const uint32 CharacterCode, const bool IsRepeat) override;`
- L33 _public prototype_ `virtual bool OnMouseDown(const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button) override;`
- L35 _public prototype_ `virtual bool OnMouseDown(const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button, const FVector2D CursorPos) override;`
- L37 _public prototype_ `virtual bool OnMouseUp(const EMouseButtons::Type Button) override;`
- L39 _public prototype_ `virtual bool OnMouseUp(const EMouseButtons::Type Button, const FVector2D CursorPos) override;`
- L41 _public prototype_ `virtual bool OnMouseDoubleClick(const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button) override;`
- L43 _public prototype_ `virtual bool OnMouseDoubleClick(const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button, const FVector2D CursorPos) override;`
- L45 _public prototype_ `virtual bool OnMouseWheel(const float Delta) override;`
- L47 _public prototype_ `virtual bool OnMouseWheel(const float Delta, const FVector2D CursorPos) override;`
- L49 _public prototype_ `virtual bool OnMouseMove() override;`
- L51 _public prototype_ `virtual bool OnRawMouseMove(const int32 X, const int32 Y) override;`
- L53 _public prototype_ `virtual bool OnCursorSet() override;`
- L55 _public prototype_ `virtual bool OnControllerAnalog(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, float AnalogValue) override;`
- L57 _public prototype_ `virtual bool OnControllerButtonPressed(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, bool IsRepeat) override;`
- L59 _public prototype_ `virtual bool OnControllerButtonReleased(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, bool IsRepeat) override;`
- L61 _public prototype_ `virtual void OnBeginGesture() override;`
- L63 _public prototype_ `virtual bool OnTouchGesture(EGestureEvent GestureType, const FVector2D& Delta, float WheelDelta, bool bIsDirectionInvertedFromDevice) override;`
- L65 _public prototype_ `virtual void OnEndGesture() override;`
- L67 _public prototype_ `virtual bool OnTouchStarted(const TSharedPtr< FGenericWindow >& Window, const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId) override;`
- L69 _public prototype_ `virtual bool OnTouchMoved(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId) override;`
- L71 _public prototype_ `virtual bool OnTouchEnded(const FVector2D& Location, int32 TouchIndex, int32 ControllerId) override;`
- L73 _public prototype_ `virtual bool OnTouchForceChanged(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId);`
- L75 _public prototype_ `virtual bool OnTouchFirstMove(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId);`
- L77 _public prototype_ `virtual void ShouldSimulateGesture(EGestureEvent Gesture, bool bEnable) override;`
- L79 _public prototype_ `virtual bool OnMotionDetected(const FVector& Tilt, const FVector& RotationRate, const FVector& Gravity, const FVector& Acceleration, int32 ControllerId) override;`
- L81 _public prototype_ `virtual bool OnSizeChanged(const TSharedRef< FGenericWindow >& Window, const int32 Width, const int32 Height, bool bWasMinimized = false) override;`
- L83 _public prototype_ `virtual void OnOSPaint(const TSharedRef<FGenericWindow>& Window) override;`
- L85 _public prototype_ `virtual FWindowSizeLimits GetSizeLimitsForWindow(const TSharedRef<FGenericWindow>& Window) const override;`
- L87 _public prototype_ `virtual void OnResizingWindow(const TSharedRef< FGenericWindow >& Window) override;`
- L89 _public prototype_ `virtual bool BeginReshapingWindow(const TSharedRef< FGenericWindow >& Window) override;`
- L91 _public prototype_ `virtual void FinishedReshapingWindow(const TSharedRef< FGenericWindow >& Window) override;`
- L93 _public prototype_ `virtual void HandleDPIScaleChanged(const TSharedRef< FGenericWindow >& Window) override;`
- L95 _public prototype_ `virtual void OnMovedWindow(const TSharedRef< FGenericWindow >& Window, const int32 X, const int32 Y) override;`
- L97 _public prototype_ `virtual bool OnWindowActivationChanged(const TSharedRef< FGenericWindow >& Window, const EWindowActivation ActivationType) override;`
- L99 _public prototype_ `virtual bool OnApplicationActivationChanged(const bool IsActive) override;`
- L101 _public prototype_ `virtual bool OnConvertibleLaptopModeChanged() override;`
- L103 _public prototype_ `virtual EWindowZone::Type GetWindowZoneForPoint(const TSharedRef< FGenericWindow >& Window, const int32 X, const int32 Y) override;`
- L105 _public prototype_ `virtual void OnWindowClose(const TSharedRef< FGenericWindow >& Window) override;`
- L107 _public prototype_ `virtual EDropEffect::Type OnDragEnterText(const TSharedRef< FGenericWindow >& Window, const FString& Text) override;`
- L109 _public prototype_ `virtual EDropEffect::Type OnDragEnterFiles(const TSharedRef< FGenericWindow >& Window, const TArray< FString >& Files) override;`
- L111 _public prototype_ `virtual EDropEffect::Type OnDragEnterExternal(const TSharedRef< FGenericWindow >& Window, const FString& Text, const TArray< FString >& Files) override;`
- L113 _public prototype_ `virtual EDropEffect::Type OnDragOver(const TSharedPtr< FGenericWindow >& Window) override;`
- L115 _public prototype_ `virtual void OnDragLeave(const TSharedPtr< FGenericWindow >& Window) override;`
- L117 _public prototype_ `virtual EDropEffect::Type OnDragDrop(const TSharedPtr< FGenericWindow >& Window) override;`
- L119 _public prototype_ `virtual bool OnWindowAction(const TSharedRef< FGenericWindow >& Window, const EWindowAction::Type InActionType) override;`
- L123 _protected member_ `TSharedPtr<FGenericApplicationMessageHandler> TargetHandler;`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Private/MessageHandler/RecordingMessageHandler.h` (Private)


#### class `IRecordingMessageHandlerWriter`  
`class IRecordingMessageHandlerWriter`  
_L12-17_
- L16 _public prototype_ `virtual void RecordMessage(const TCHAR* MsgName, const TArray<uint8>& Data) = 0;`

#### class `FRecordingMessageHandler`  
`class FRecordingMessageHandler : public FProxyMessageHandler, public TSharedFromThis<FRecordingMessageHandler>`  
_L22-192_
- inherits: `FProxyMessageHandler,TSharedFromThis<FRecordingMessageHandler>`
- L61 _public prototype_ `FRecordingMessageHandler(const TSharedPtr<FGenericApplicationMessageHandler>& InTargetHandler);`
- L63 _public prototype_ `void Tick(const float DeltaTime);`
- L65 _public prototype_ `bool PlayMessage(const TCHAR* Message, TArray<uint8> Data);`
- L67 _public prototype_ `void SetRecordingHandler(IRecordingMessageHandlerWriter* InOutputWriter);`
- L72 _public function_ `void SetConsumeInput(bool bConsume)` — Do not pass input to the target handler
- L77 _public function_ `bool IsConsumingInput() const` — Returns true/false depending on whether input is blocked
- L82 _public function_ `bool IsRecording() const` — Returns true/false depending on whether we are recording (RecordingHandler is != null)
- L87 _public prototype_ `void SetPlaybackWindow(TWeakPtr<SWindow> InWindow, TWeakPtr<FSceneViewport> InViewport);` — Set the window to which the input should be forward to
- L89 _public prototype_ `void SetInputRect(const FVector2D& TopLeft, const FVector2D& Extents);`
- L94 _public function_ `void TryRouteTouchMessageToWidget(bool bInRouteMessageToWidget)` — Send any received touch event from the client to the widget directly bypassing the message handler
- L96 _public function_ `FOnRouteTouchDownToWidgetFailedDelegate& GetOnRouteTouchDownToWidgetFailedDelegate()`
- L101 _public function_ `virtual bool ShouldUsePlatformUserId() const override` — FRecordingMessageHandler does not support sending PlatformUserId
- L109 _public prototype_ `virtual bool OnKeyChar(const TCHAR Character, const bool IsRepeat) override;` — Keyboard handling
- L110 _public prototype_ `virtual bool OnKeyDown(const int32 KeyCode, const uint32 CharacterCode, const bool IsRepeat) override;`
- L111 _public prototype_ `virtual bool OnKeyUp(const int32 KeyCode, const uint32 CharacterCode, const bool IsRepeat) override;`
- L116 _public prototype_ `virtual void OnBeginGesture() override;` — High-level gesture events
- L117 _public prototype_ `virtual bool OnTouchGesture(EGestureEvent GestureType, const FVector2D& Delta, float WheelDelta, bool bIsDirectionInvertedFromDevice) override;`
- L118 _public prototype_ `virtual void OnEndGesture() override;`
- L123 _public prototype_ `virtual bool OnTouchStarted(const TSharedPtr< FGenericWindow >& Window, const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId) override;` — Raw touch events
- L124 _public prototype_ `virtual bool OnTouchMoved(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId) override;`
- L125 _public prototype_ `virtual bool OnTouchEnded(const FVector2D& Location, int32 TouchIndex, int32 ControllerId) override;`
- L126 _public prototype_ `virtual bool OnTouchForceChanged(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId) override;`
- L127 _public prototype_ `virtual bool OnTouchFirstMove(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId) override;`
- L128 _public prototype_ `virtual bool OnMotionDetected(const FVector& Tilt, const FVector& RotationRate, const FVector& Gravity, const FVector& Acceleration, int32 ControllerId) override;`
- L133 _public prototype_ `virtual bool OnControllerAnalog(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, float AnalogValue) override;` — Controller handling
- L134 _public prototype_ `virtual bool OnControllerButtonPressed(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, bool IsRepeat) override;`
- L135 _public prototype_ `virtual bool OnControllerButtonReleased(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, bool IsRepeat) override;`
- L140 _protected prototype_ `bool ConvertToNormalizedScreenLocation(const FVector2D& InLocation, FVector2f& OutLocation);`
- L141 _protected prototype_ `FVector2D ConvertFromNormalizedScreenLocation(const FVector2f& ScreenLocation);`
- L143 _protected prototype_ `void RecordMessage(const TCHAR* MsgName, const TArray<uint8>& Data);`
- L145 _protected prototype_ `virtual void PlayOnKeyChar(FArchive& Ar);`
- L146 _protected prototype_ `virtual void PlayOnKeyDown(FArchive& Ar);`
- L147 _protected prototype_ `virtual void PlayOnKeyUp(FArchive& Ar);`
- L149 _protected prototype_ `virtual void PlayOnBeginGesture(FArchive& Ar);`
- L150 _protected prototype_ `virtual void PlayOnTouchGesture(FArchive& Ar);`
- L151 _protected prototype_ `virtual void PlayOnEndGesture(FArchive& Ar);`
- L153 _protected prototype_ `virtual void PlayOnTouchStarted(FArchive& Ar);`
- L154 _protected prototype_ `virtual void PlayOnTouchMoved(FArchive& Ar);`
- L155 _protected prototype_ `virtual void PlayOnTouchEnded(FArchive& Ar);`
- L156 _protected prototype_ `virtual void PlayOnTouchForceChanged(FArchive& Ar);`
- L157 _protected prototype_ `virtual void PlayOnTouchFirstMove(FArchive& Ar);`
- L158 _protected prototype_ `virtual void PlayOnMotionDetected(FArchive& Ar);`
- L160 _protected prototype_ `virtual void PlayOnControllerAnalog(FArchive& Ar);`
- L161 _protected prototype_ `virtual void PlayOnControllerButtonPressed(FArchive& Ar);`
- L162 _protected prototype_ `virtual void PlayOnControllerButtonReleased(FArchive& Ar);`
- L164 _protected prototype_ `virtual void PlayOnControllerAnalogWithPlatformUser(FArchive& Ar);`
- L165 _protected prototype_ `virtual void PlayOnControllerButtonPressedWithPlatformUser(FArchive& Ar);`
- L166 _protected prototype_ `virtual void PlayOnControllerButtonReleasedWithPlatformUser(FArchive& Ar);`
- L168 _protected prototype_ `FWidgetPath FindRoutingMessageWidget(const FVector2D& Location) const;`
- L176 _protected member_ `IRecordingMessageHandlerWriter* OutputWriter;`
- L177 _protected member_ `bool bConsumeInput;`
- L178 _protected member_ `TWeakPtr<SWindow> PlaybackWindow;`
- L179 _protected member_ `TWeakPtr<FSceneViewport> PlaybackViewport;`
- L181 _protected member_ `TMap<FString, FRecordedMessageDispatch> DispatchTable;`
- L183 _protected member_ `mutable FCriticalSection MessagesCriticalSection;`
- L184 _protected member_ `TArray<FDelayPlayMessage> DelayMessages;`
- L186 _protected member_ `FRect InputRect;`
- L187 _protected member_ `FVector2D LastTouchLocation;`
- L188 _protected member_ `bool bIsTouching;`
- L189 _protected member_ `bool bTryRouteTouchMessageToWidget;`
- L191 _protected member_ `FOnRouteTouchDownToWidgetFailedDelegate OnRouteTouchDownToWidgetFailedDelegate;`

#### struct `FRecordingMessageHandler::FRect`  
`struct FRect`  
_L24-58_
- L26 _public prototype_ `FRect() = default;`
- L28 _public function_ `FRect(EForceInit) : X(0.0f) , Y(0.0f) , Width(0.0f) , Height(0.0f)`
- L35 _public function_ `FRect(float InX, float InY, float InWidth, float InHeight) : X(InX) , Y(InY) , Width(InWidth) , Height(InHeight)`
- L42 _public function_ `FRect(const FVector2D& Point, const FVector2D& Extents) : X(Point.X) , Y(Point.Y) , Width(Extents.X) , Height(Extents.Y)`
- L49 _public function_ `FORCEINLINE bool Contains(FVector2D P) const`
- L54 _public member_ `float X;`
- L55 _public member_ `float Y;`
- L56 _public member_ `float Width;`
- L57 _public member_ `float Height;`

#### struct `FRecordingMessageHandler::FDelayPlayMessage`  
`struct FDelayPlayMessage`  
_L170-174_
- L172 _public member_ `FRecordedMessageDispatch* Dispatch;`
- L173 _public member_ `TArray<uint8> Data;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FRecordedMessageDispatch, FArchive&);`
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FRecordedMessageDispatch, FArchive&);`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRouteTouchDownToWidgetFailedDelegate, const FVector2D& );`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRouteTouchDownToWidgetFailedDelegate, const FVector2D& );`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Private/RemoteSessionClient.h` (Private)


#### class `FRemoteSessionClient`  
`class FRemoteSessionClient : public FRemoteSessionRole`  
_L12-49_
- inherits: `FRemoteSessionRole`
- L16 _public prototype_ `FRemoteSessionClient(const TCHAR* InHostAddress);`
- L17 _public prototype_ `~FRemoteSessionClient();`
- L19 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L21 _public prototype_ `virtual bool IsConnected() const override;`
- L25 _protected prototype_ `void StartConnection();`
- L26 _protected prototype_ `void CheckConnection();`
- L28 _protected prototype_ `virtual void BindEndpoints(TBackChannelSharedPtr<IBackChannelConnection> InConnection);`
- L29 _protected prototype_ `virtual bool ProcessStateChange(const ConnectionState NewState, const ConnectionState OldState) override;`
- L31 _protected prototype_ `void OnReceiveChannelList(IBackChannelPacket& Message);`
- L33 _protected prototype_ `void RequestChannel(const FRemoteSessionChannelInfo& Info);`
- L35 _protected prototype_ `void OnReceiveHello(IBackChannelPacket& Message);`
- L36 _protected prototype_ `virtual void AppendExtraInfoToBackChannelPacket(TBackChannelSharedPtr<IBackChannelPacket> Packet) override;`
- L38 _protected member_ `FString HostAddress;`
- L40 _protected member_ `bool IsConnecting;`
- L41 _protected member_ `float ConnectionTimeout;`
- L43 _protected member_ `double ConnectionAttemptTimer;`
- L44 _protected member_ `double TimeConnectionAttemptStarted;`
- L46 _protected member_ `FDelegateHandle ChannelCallbackHandle;`
- L48 _protected member_ `TArray<FRemoteSessionChannelInfo> AvailableChannels;`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Private/RemoteSessionHost.h` (Private)


#### class `FRemoteSessionHost`  
`class FRemoteSessionHost : public FRemoteSessionRole, public TSharedFromThis<FRemoteSessionHost>`  
_L16-55_
- inherits: `FRemoteSessionRole,TSharedFromThis<FRemoteSessionHost>`
- L20 _public prototype_ `FRemoteSessionHost(TArray<FRemoteSessionChannelInfo> SupportedChannels);`
- L21 _public prototype_ `~FRemoteSessionHost();`
- L23 _public prototype_ `bool StartListening(const uint16 Port);`
- L25 _public prototype_ `void SetScreenSharing(const bool bEnabled);`
- L27 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L32 _protected prototype_ `virtual void CloseConnections() override;` — Closes all connections. Called by public Close() function which first send a graceful goodbye
- L34 _protected prototype_ `virtual bool ProcessStateChange(const ConnectionState NewState, const ConnectionState OldState) override;`
- L36 _protected prototype_ `virtual void BindEndpoints(TBackChannelSharedPtr<IBackChannelConnection> InConnection) override;`
- L38 _protected prototype_ `void SendChannelListToConnection();`
- L40 _protected prototype_ `bool ProcessIncomingConnection(TSharedRef<IBackChannelSocketConnection> NewConnection);`
- L42 _protected prototype_ `void OnReceiveHello(IBackChannelPacket& Message);`
- L43 _protected prototype_ `virtual void AppendExtraInfoToBackChannelPacket(TBackChannelSharedPtr<IBackChannelPacket> Packet) override;`
- L45 _protected member_ `TSharedPtr<IBackChannelSocketConnection> Listener;`
- L48 _protected member_ `float SavedEditorDragTriggerDistance;` — Saved information about the editor and viewport we possessed, so we can restore it after exiting VR mode
- L51 _protected member_ `uint16 HostTCPPort;` — Host's TCP port
- L54 _protected member_ `bool IsListenerConnected;` — True if the host TCP socket is connected

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Private/RemoteSessionModule.h` (Private)


#### class `FRemoteSessionModule`  
`class FRemoteSessionModule : public IRemoteSessionModule, public FTickableGameObject`  
_L22-85_
- inherits: `IRemoteSessionModule,FTickableGameObject`
- L26 _private member_ `TSharedPtr<FRemoteSessionHost> Host;`
- L27 _private member_ `TSharedPtr<FRemoteSessionClient> Client;`
- L29 _private member_ `int32 DefaultPort = IRemoteSessionModule::kDefaultPort;`
- L31 _private member_ `bool bAutoHostWithPIE = true;`
- L32 _private member_ `bool bAutoHostWithGame = true;`
- L34 _private member_ `FDelegateHandle PostPieDelegate;`
- L35 _private member_ `FDelegateHandle EndPieDelegate;`
- L36 _private member_ `FDelegateHandle GameStartDelegate;`
- L37 _private member_ `FDelegateHandle ConnectionChangeDelegateHandle;`
- L39 _private member_ `static constexpr const TCHAR* DefaultHostAnalyticsEventName = TEXT("Usa`
- L40 _private member_ `static constexpr EAnalyticsRecordEventMode DefaultHostAnalyticsEventMode = EAnalyticsRecordEventMode::Cached;`
- L41 _private member_ `FString HostAnalyticsEventName = DefaultHostAnalyticsEventName;`
- L42 _private member_ `EAnalyticsRecordEventMode HostAnalyticsEventMode = DefaultHostAnalyticsEventMode;`
- L47 _public prototype_ `virtual void StartupModule() override;`
- L48 _public prototype_ `virtual void ShutdownModule() override;`
- L50 _public prototype_ `void AddChannelFactory(const FStringView InChannelName, ERemoteSessionChannelMode InHostMode, TWeakPtr<IRemoteSessionChannelFactoryWorker> Worker) override;`
- L51 _public prototype_ `void RemoveChannelFactory(TWeakPtr<IRemoteSessionChannelFactoryWorker> Worker) override;`
- L53 _public prototype_ `virtual TSharedPtr<IRemoteSessionRole> CreateClient(const TCHAR* RemoteAddress) override;`
- L54 _public prototype_ `virtual void StopClient(TSharedPtr<IRemoteSessionRole> InClient, const FString& InReason) override;`
- L56 _public prototype_ `virtual void InitHost(const int16 Port = 0) override;`
- L57 _public function_ `virtual bool IsHostRunning() const override`
- L58 _public prototype_ `virtual bool IsHostConnected() const override;`
- L59 _public prototype_ `virtual void StopHost(const FString& InReason) override;`
- L60 _public prototype_ `virtual TSharedPtr<IRemoteSessionRole> GetHost() const override;`
- L61 _public prototype_ `virtual TSharedPtr<IRemoteSessionUnmanagedRole> CreateHost(TArray<FRemoteSessionChannelInfo> SupportedChannels, int32 Port) const override;`
- L62 _public function_ `virtual void SetHostAnalyticsEventName(const FString& EventName) override`
- L63 _public function_ `virtual void SetHostAnalyticsEventMode(EAnalyticsRecordEventMode Mode) override`
- L67 _public function_ `virtual TStatId GetStatId() const override`
- L68 _public function_ `virtual bool IsTickable() const override`
- L69 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L72 _public prototype_ `void SetAutoStartWithPIE(bool bEnable);`
- L75 _private prototype_ `void OnPostInit();`
- L76 _private prototype_ `void OnPreExit();`
- L77 _private prototype_ `bool HandleSettingsSaved();`
- L79 _private prototype_ `TSharedPtr<FRemoteSessionHost> CreateHostInternal(TArray<FRemoteSessionChannelInfo> SupportedChannels, int32 Port) const;`
- L81 _private prototype_ `void OnPIEStarted(bool bSimulating);`
- L82 _private prototype_ `void OnPIEEnded(bool bSimulating);`
- L84 _private prototype_ `void OnHostConnectionChanged(IRemoteSessionRole* Role, ERemoteSessionConnectionChange Change);`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Private/RemoteSessionRole.h` (Private)


#### class `FRemoteSessionRole`  
`class FRemoteSessionRole : public IRemoteSessionUnmanagedRole`  
_L14-226_
- inherits: `IRemoteSessionUnmanagedRole`
- L26 _protected function_ `const TCHAR* LexToString(ConnectionState InState)`
- L46 _protected member_ `const TCHAR* kLegacyVersionEndPoint = TEXT("/Ve`
- L47 _protected member_ `const TCHAR* kLegacyChannelSelectionEndPoint = TEXT("/Ch`
- L49 _protected member_ `const TCHAR* kHelloEndPoint = TEXT("/RS`
- L50 _protected member_ `const TCHAR* kHelloV2EndPoint = TEXT("/RS`
- L51 _protected member_ `const TCHAR* kGoodbyeEndPoint = TEXT("/RS`
- L52 _protected member_ `const TCHAR* kChannelListEndPoint = TEXT("/RS`
- L53 _protected member_ `const TCHAR* kChangeChannelEndPoint = TEXT("/RS`
- L54 _protected member_ `const TCHAR* kPingEndPoint = TEXT("/RS`
- L55 _protected member_ `const TCHAR* kPongEndPoint = TEXT("/RS`
- L59 _public prototype_ `FRemoteSessionRole();`
- L60 _public prototype_ `virtual ~FRemoteSessionRole();`
- L62 _public prototype_ `virtual void Close(const FString& Message) override;`
- L64 _public prototype_ `virtual bool IsConnected() const override;`
- L66 _public prototype_ `virtual bool HasError() const override;`
- L68 _public prototype_ `virtual FString GetErrorMessage() const override;`
- L70 _public prototype_ `virtual void Tick( float DeltaTime ) override;`
- L73 _public prototype_ `virtual FDelegateHandle RegisterConnectionChangeDelegate(FOnRemoteSessionConnectionChange::FDelegate InDelegate) override;` — Registers a delegate for notifications of connection changes
- L76 _public prototype_ `virtual FDelegateHandle RegisterChannelListDelegate(FOnRemoteSessionReceiveChannelList::FDelegate InDelegate) override;` — Register for notifications when the host sends a list of available channels
- L79 _public prototype_ `virtual FDelegateHandle RegisterChannelChangeDelegate(FOnRemoteSessionChannelChange::FDelegate InDelegate) override;` — Register for notifications whenever a change in the state of a channel occurs
- L82 _public prototype_ `virtual void RegisterHelloRouteMessageDelegate(FBackChannelRouteDelegate::FDelegate InDelegate) override;` — Register for notifications whenever a hello route message arrives
- L85 _public prototype_ `virtual void RemoveAllDelegates(FDelegateUserObject UserObject) override;` — Unregister all delegates for the specified object
- L87 _public prototype_ `virtual TSharedPtr<IRemoteSessionChannel> GetChannel(const TCHAR* Type) override;`
- L89 _public prototype_ `virtual bool OpenChannel(const FRemoteSessionChannelInfo& Info) override;`
- L91 _public prototype_ `virtual bool IsLegacyConnection() const override;`
- L93 _public function_ `virtual FString GetRemoteVersion() const override`
- L95 _public function_ `virtual bool IsUsingPixelStreaming() const override`
- L97 _public function_ `virtual FString GetRemotePixelStreamingVersion() const override`
- L99 _public function_ `virtual FString GetRemoteBuildInfo() const override`
- L101 _public function_ `virtual float GetPeerResponseInSeconds() const`
- L106 _protected prototype_ `virtual void CloseConnections();` — Closes all connections. Called by public Close() function which first send a graceful goodbye
- L109 _protected prototype_ `void CloseWithError(const FString& Message);` — Similar (and calls) Close(Message), but marks us as having closed due to an error
- L111 _protected prototype_ `void CreateOSCConnection(TSharedRef<IBackChannelSocketConnection> InConnection);`
- L113 _protected prototype_ `void SendLegacyVersionCheck();`
- L115 _protected prototype_ `virtual void BindEndpoints(TBackChannelSharedPtr<IBackChannelConnection> InConnection);`
- L117 _protected prototype_ `void OnReceiveLegacyVersion(IBackChannelPacket& Message);`
- L119 _protected prototype_ `void SendHello();`
- L120 _protected prototype_ `void OnReceiveHello(IBackChannelPacket& Message);`
- L122 _protected prototype_ `void SendHelloV2();`
- L123 _protected prototype_ `void OnReceiveHelloV2(IBackChannelPacket& Message);`
- L125 _protected prototype_ `void SendGoodbye(const FString& InMessage);`
- L126 _protected prototype_ `void OnReceiveGoodbye(IBackChannelPacket& Message);`
- L128 _protected prototype_ `void SendPing();`
- L129 _protected prototype_ `void OnReceivePing(IBackChannelPacket& Message);`
- L130 _protected prototype_ `void OnReceivePong(IBackChannelPacket& Message);`
- L132 _protected prototype_ `void CreateChannels(const TArray<FRemoteSessionChannelInfo>& Channels);`
- L138 _protected prototype_ `void OnReceiveChangeChannel(IBackChannelPacket& Message);` — Called when the other side wants to open a channel. The connection that is the original requester will receive this message will receive this message when the other end has created the channel so the successful connection state can be broadcast
- L140 _protected prototype_ `void OnReceiveChannelChanged(IBackChannelPacket& Message);`
- L142 _protected prototype_ `void ClearChannels();`
- L145 _protected function_ `virtual void AppendExtraInfoToBackChannelPacket(TBackChannelSharedPtr<IBackChannelPacket> Packet)` — Children of RemoteSessionRole can use this function to extend the information that a package will carry
- L148 _protected prototype_ `void SetPendingState(const ConnectionState InState);` — Queues the next state to be processed on the next tick. It's an error to call this when there is another state pending
- L154 _protected prototype_ `virtual bool ProcessStateChange(const ConnectionState NewState, const ConnectionState OldState) = 0;` — Called from the tick loop to perform any state changes. When called GetCurrentState() will return the current state. If the function returnstrue  CurrentState will be set to IncomingState. If not the connection will be disconnected
- L157 _protected function_ `ConnectionState GetCurrentState(void) const` — Returns the current processed state
- L159 _protected function_ `bool IsStateCurrentOrPending(ConnectionState InState) const`
- L164 _protected member_ `mutable FCriticalSection CriticalSectionForMainThread;`
- L166 _protected member_ `TSharedPtr<IBackChannelSocketConnection> Connection;`
- L168 _protected member_ `TSharedPtr<FBackChannelOSCConnection, ESPMode::ThreadSafe> OSCConnection;`
- L170 _protected member_ `FOnRemoteSessionChannelChange ChannelChangeDelegate;`
- L172 _protected member_ `FOnRemoteSessionConnectionChange ConnectionChangeDelegate;`
- L174 _protected member_ `FOnRemoteSessionReceiveChannelList ReceiveChannelListDelegate;`
- L177 _protected member_ `TArray<FRemoteSessionChannelInfo> SupportedChannels;`
- L179 _protected member_ `bool bIsUsingPixelStreaming;`
- L181 _protected member_ `FString RemotePixelStreamingVersion;`
- L183 _protected member_ `FString RemoteBuildInfo;`
- L186 _private prototype_ `void RemoveRouteDelegates();`
- L189 _private member_ `FString RemoteVersion;`
- L191 _private member_ `FString ErrorMessage;`
- L193 _private member_ `TSharedPtr<struct FRemoteSessionRoleCancellationToken> CancelCloseToken;`
- L195 _private member_ `TArray<TSharedPtr<IRemoteSessionChannel>> Channels;`
- L197 _private member_ `TWeakPtr<IBackChannelConnection, ESPMode::ThreadSafe> BackChannelConnection;`
- L209 _private member_ `FRouteDelegates RouteDelegates;`
- L211 _private member_ `TArray<FBackChannelRouteDelegate::FDelegate> ExternalHelloRouteDelegates;`
- L212 _private member_ `TArray<FDelegateHandle> ExternalHelloRouteDelegateHandles;`
- L214 _private member_ `ConnectionState CurrentState = ConnectionState::Disconnected;`
- L216 _private member_ `ConnectionState PendingState = ConnectionState::Unknown;`
- L219 _private member_ `double LastPingTime = 0;` — Time since last ping
- L222 _private member_ `double LastReponseTime = 0;` — Time since last response
- L225 _private member_ `float SecondsForPeerResponse = 0;` — Latency based on most recent ping/ping

#### enum `FRemoteSessionRole::ConnectionState`  
`enum class ConnectionState`  
_L17-24_
- L19 _public enumerator_ `Unknown`
- L20 _public enumerator_ `Disconnected`
- L21 _public enumerator_ `UnversionedConnection`
- L22 _public enumerator_ `EstablishingVersion`
- L23 _public enumerator_ `Connected`

#### struct `FRemoteSessionRole::FRouteDelegates`  
`struct FRouteDelegates`  
_L199-208_
- L201 _public member_ `FDelegateHandle Hello;`
- L202 _public member_ `FDelegateHandle HelloV2;`
- L203 _public member_ `FDelegateHandle Goodbye;`
- L204 _public member_ `FDelegateHandle Ping;`
- L205 _public member_ `FDelegateHandle Pong;`
- L206 _public member_ `FDelegateHandle LegacyReceive;`
- L207 _public member_ `FDelegateHandle ChangeChannel;`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Private/RemoteSessionUtils.h` (Private)


#### struct `FRemoteSessionUtils`  
`struct FRemoteSessionUtils`  
_L11-14_
- L13 _public prototype_ `static void FindSceneViewport(TWeakPtr<SWindow>& OutInputWindow, TWeakPtr<FSceneViewport>& OutSceneViewport);`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Public/Channels/RemoteSessionARCameraChannel.h` (Public)


#### class `FRemoteSessionARCameraChannel`  
`class FRemoteSessionARCameraChannel : public IRemoteSessionChannel, public FGCObject`  
_L21-106_
- inherits: `IRemoteSessionChannel,FGCObject`
- L27 _public prototype_ `FRemoteSessionARCameraChannel(ERemoteSessionChannelMode InRole, TSharedPtr<IBackChannelConnection, ESPMode::ThreadSafe> InConnection);`
- L29 _public prototype_ `~FRemoteSessionARCameraChannel();`
- L31 _public prototype_ `virtual void Tick(const float InDeltaTime) override;`
- L34 _public function_ `static const TCHAR* StaticType()` — Begin IRemoteSessionChannel implementation
- L35 _public function_ `virtual const TCHAR* GetType() const override`
- L39 _public prototype_ `UMaterialInterface* GetPostProcessMaterial() const;` — Returns the post process material to render with. The textures are set on the fly
- L43 _protected prototype_ `void SendARCameraImage();` — Sends the most recent compressed AR camera image to the remote
- L45 _protected prototype_ `void QueueARCameraImage();` — Compresses in the background and queues for sending
- L48 _protected prototype_ `void ReceiveARCameraImage(IBackChannelPacket& Message);` — Handles data coming from the client
- L51 _protected prototype_ `void UpdateRenderingTexture();` — Updates the next texture to be rendered
- L54 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L55 _protected function_ `virtual FString GetReferencerName() const override`
- L82 _private member_ `TSharedPtr<FCompressionTask, ESPMode::ThreadSafe> CompressionTask;` — Only compress one frame at a time to prevent flooding the GPU
- L85 _private member_ `TArray<TSharedPtr<FDecompressedImage, ESPMode::ThreadSafe>> DecompressionQueue;` — Images that have been received and are available for rendering
- L86 _private member_ `FThreadSafeCounter DecompressionTaskCount;`
- L87 _private member_ `FCriticalSection DecompressionQueueLock;`
- L90 _private member_ `TObjectPtr<UMaterialInterface> PPMaterial;` — The post process material that the overlay will render with
- L92 _private member_ `TObjectPtr<UMaterialInstanceDynamic> MaterialInstanceDynamic;` — To set the current texture for rendering
- L94 _private member_ `TObjectPtr<UTexture2D> RenderingTextures[2];` — Textures to use when rendering
- L95 _private member_ `UTexture2D* LastSetTexture;`
- L96 _private member_ `FThreadSafeCounter RenderingTextureIndex;`
- L97 _private member_ `FThreadSafeCounter RenderingTexturesUpdateCount[2];`
- L99 _private member_ `TSharedPtr<ISceneViewExtension, ESPMode::ThreadSafe> SceneViewExtension;`
- L101 _private member_ `TSharedPtr<IBackChannelConnection, ESPMode::ThreadSafe> Connection;`
- L102 _private member_ `ERemoteSessionChannelMode Role;`
- L105 _private member_ `FDelegateHandle MessageCallbackHandle;` — So we can manage callback lifetimes properly

#### struct `FRemoteSessionARCameraChannel::FCompressionTask`  
`struct FCompressionTask`  
_L63-70_
- desc: A wrapper around the async compression task
- L65 _public function_ `FCompressionTask() : Width(0), Height(0)`
- L67 _public member_ `int32 Width;`
- L68 _public member_ `int32 Height;`
- L69 _public member_ `TSharedPtr<FAppleImageUtilsConversionTaskBase, ESPMode::ThreadSafe> AsyncTask;`

#### struct `FRemoteSessionARCameraChannel::FDecompressedImage`  
`struct FDecompressedImage`  
_L72-79_
- L74 _public function_ `FDecompressedImage() : Width(0), Height(0)`
- L76 _public member_ `int32 Width;`
- L77 _public member_ `int32 Height;`
- L78 _public member_ `TArray<uint8> ImageData;`

#### class `FRemoteSessionARCameraChannelFactoryWorker`  
`class FRemoteSessionARCameraChannelFactoryWorker : public IRemoteSessionChannelFactoryWorker`  
_L108-112_
- inherits: `IRemoteSessionChannelFactoryWorker`
- L111 _public prototype_ `virtual TSharedPtr<IRemoteSessionChannel> Construct(ERemoteSessionChannelMode InMode, TSharedPtr<IBackChannelConnection, ESPMode::ThreadSafe> InConnection) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API REMOTESESSION_API`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Public/Channels/RemoteSessionARSystemChannel.h` (Public)


#### class `FARSystemProxy`  
`class FARSystemProxy : public IARSystemSupport, public FGCObject, public TSharedFromThis<FARSystemProxy, ESPMode::ThreadSafe>`  
_L21-106_
- inherits: `IARSystemSupport,FGCObject,TSharedFromThis<FARSystemProxy,ESPMode::ThreadSafe>`
- desc: This class acts as if there is a AR system present on the desktop that is receiving data from a remote device
- L28 _public prototype_ `FARSystemProxy();` — Only the factory method should construct this
- L29 _public prototype_ `virtual ~FARSystemProxy();`
- L31 _public prototype_ `static TSharedPtr<FARSystemProxy, ESPMode::ThreadSafe> Get();`
- L32 _public prototype_ `static IARSystemSupport* GetARSystemPtr();`
- L33 _public prototype_ `static void Destroy();`
- L38 _public prototype_ `virtual bool IsARAvailable() const override;` — Returns true/false based on whether AR features are available
- L40 _public prototype_ `virtual EARTrackingQuality OnGetTrackingQuality() const override;`
- L42 _public prototype_ `virtual EARTrackingQualityReason OnGetTrackingQualityReason() const override;` — @return the reason of limited tracking quality; if the state is not limited, return EARTrackingQualityReason::None
- L43 _public prototype_ `virtual FARSessionStatus OnGetARSessionStatus() const override;`
- L44 _public prototype_ `virtual TArray<UARTrackedGeometry*> OnGetAllTrackedGeometries() const override;`
- L45 _public prototype_ `virtual bool OnIsTrackingTypeSupported(EARSessionType SessionType) const override;`
- L46 _public prototype_ `virtual EARWorldMappingState OnGetWorldMappingStatus() const override;`
- L47 _public prototype_ `virtual TArray<FARVideoFormat> OnGetSupportedVideoFormats(EARSessionType SessionType) const override;`
- L50 _public function_ `virtual UARLightEstimate* OnGetCurrentLightEstimate() const override` — Not supported methods @todo JoeG -- Look at supporting this
- L51 _public function_ `virtual UARTextureCameraImage* OnGetCameraImage()`
- L52 _public function_ `virtual UARTextureCameraDepth* OnGetCameraDepth()`
- L54 _public function_ `virtual void OnStartARSession(UARSessionConfig* Config) override`
- L55 _public function_ `virtual void OnPauseARSession() override`
- L56 _public function_ `virtual void OnStopARSession() override`
- L57 _public function_ `virtual void OnSetAlignmentTransform(const FTransform& InAlignmentTransform) override`
- L58 _public function_ `virtual bool OnAddManualEnvironmentCaptureProbe(FVector Location, FVector Extent) override`
- L59 _public function_ `virtual TSharedPtr<FARSaveWorldAsyncTask, ESPMode::ThreadSafe> OnSaveWorld() const override`
- L63 _public function_ `virtual TSharedPtr<FARGetCandidateObjectAsyncTask, ESPMode::ThreadSafe> OnGetCandidateObject(FVector Location, FVector Extent) const override`
- L67 _public function_ `virtual bool OnAddRuntimeCandidateImage(UARSessionConfig* Config, UTexture2D* CandidateTexture, FString FriendlyName, float PhysicalWidth) override`
- L68 _public function_ `virtual TArray<FVector> OnGetPointCloud() const override`
- L69 _public function_ `virtual TArray<UARPin*> OnGetAllPins() const override`
- L70 _public function_ `virtual UARPin* OnPinComponent(USceneComponent* ComponentToPin, const FTransform& PinToWorldTransform, UARTrackedGeometry* TrackedGeometry = nullptr, const FName DebugName = NAME_None)`
- L71 _public function_ `virtual void OnRemovePin(UARPin* PinToRemove) override`
- L72 _public function_ `virtual UARPin* FindARPinByComponent(const USceneComponent* Component) const override`
- L73 _public function_ `virtual bool OnPinComponentToARPin(USceneComponent* ComponentToPin, UARPin* Pin) override`
- L74 _public function_ `virtual TArray<FARTraceResult> OnLineTraceTrackedObjects( const FVector2D ScreenCoord, EARLineTraceChannels TraceChannels ) override`
- L75 _public function_ `virtual TArray<FARTraceResult> OnLineTraceTrackedObjects( const FVector Start, const FVector End, EARLineTraceChannels TraceChannels ) override`
- L76 _public function_ `virtual void* GetARSessionRawPointer() override`
- L77 _public function_ `virtual void* GetGameThreadARFrameRawPointer() override`
- L81 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L82 _public function_ `virtual FString GetReferencerName() const override`
- L89 _public prototype_ `void SetSupportedVideoFormats(const TArray<FARVideoFormat>& InFormats);` — Methods called by the message handlers
- L90 _public prototype_ `void SetSessionConfig(UARSessionConfig* InConfig);`
- L91 _public prototype_ `void AddTrackable(UARTrackedGeometry* Added);`
- L92 _public prototype_ `UARTrackedGeometry* GetTrackable(FGuid UniqueId);`
- L93 _public prototype_ `void NotifyUpdated(UARTrackedGeometry* Updated);`
- L94 _public prototype_ `void RemoveTrackable(FGuid UniqueId);`
- L98 _private member_ `static TSharedPtr<FARSystemProxy, ESPMode::ThreadSafe> FactoryInstance;`
- L101 _private member_ `TObjectPtr<UARSessionConfig> SessionConfig;` — Used to return the session config object the remote is using
- L103 _private member_ `TMap<FGuid, TObjectPtr<UARTrackedGeometry>> TrackedGeometries;` — Map of unique ids to tracked geometries
- L105 _private member_ `TArray<FARVideoFormat> SupportedFormats;` — The video formats that are supported

#### class `FRemoteSessionARSystemChannel`  
`class FRemoteSessionARSystemChannel : public FRemoteSessionXRTrackingChannel`  
_L114-161_
- inherits: `FRemoteSessionXRTrackingChannel`
- desc: Class used to deliver AR trackable items to the remote machine. Inherits from the XR tracking channel which handles sending all of the position & orientation updates. Do not use both this channel and the XR tracking at the same time, since they both hook GEngine->XRSystem and you will get inconsistent results
- L118 _public prototype_ `FRemoteSessionARSystemChannel(ERemoteSessionChannelMode InRole, TSharedPtr<IBackChannelConnection, ESPMode::ThreadSafe> InConnection);`
- L120 _public prototype_ `virtual ~FRemoteSessionARSystemChannel();`
- L123 _public function_ `static const TCHAR* StaticType()` — Begin IRemoteSessionChannel implementation
- L124 _public function_ `virtual const TCHAR* GetType() const override`
- L128 _public prototype_ `void ReceiveARInit(IBackChannelPacket& Message);` — Message handlers
- L129 _public prototype_ `void ReceiveAddTrackable(IBackChannelPacket& Message);`
- L130 _public prototype_ `void ReceiveUpdateTrackable(IBackChannelPacket& Message);`
- L131 _public prototype_ `void ReceiveRemoveTrackable(IBackChannelPacket& Message);`
- L134 _public prototype_ `void ReceiveARInit_GameThread(FString ConfigObjectPathName, TArray<FARVideoFormat> Formats);` — Game thead message handlers
- L135 _public prototype_ `void ReceiveAddTrackable_GameThread(FString ClassPathName, TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> DataCopy);`
- L136 _public prototype_ `void ReceiveUpdateTrackable_GameThread(FGuid UniqueId, TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> DataCopy);`
- L137 _public prototype_ `void ReceiveRemoveTrackable_GameThread(FGuid UniqueId);`
- L140 _public prototype_ `void SendAddedMessage(UARTrackedGeometry* Added);` — AR notification handlers that send the data to the listener
- L141 _public prototype_ `void SendUpdatedMessage(UARTrackedGeometry* Updated);`
- L142 _public prototype_ `void SendRemovedMessage(UARTrackedGeometry* Removed);`
- L145 _public prototype_ `void SendARInitMessage();` — Sends the name of the config object we're using so it can be loaded on the remote. Also passes the video settings and supported session types
- L149 _private member_ `TArray<uint8> SerializeBuffer;` — The buffer that objects are serialized into. Cached to reduce malloc/free pressure
- L152 _private member_ `FDelegateHandle InitMessageCallbackHandle;` — Channel message handles
- L153 _private member_ `FDelegateHandle AddMessageCallbackHandle;`
- L154 _private member_ `FDelegateHandle UpdateMessageCallbackHandle;`
- L155 _private member_ `FDelegateHandle RemoveMessageCallbackHandle;`
- L158 _private member_ `FDelegateHandle OnTrackableAddedDelegateHandle;` — AR system notification handles
- L159 _private member_ `FDelegateHandle OnTrackableUpdatedDelegateHandle;`
- L160 _private member_ `FDelegateHandle OnTrackableRemovedDelegateHandle;`

#### class `FRemoteSessionARSystemChannelFactoryWorker`  
`class FRemoteSessionARSystemChannelFactoryWorker : public IRemoteSessionChannelFactoryWorker`  
_L163-167_
- inherits: `IRemoteSessionChannelFactoryWorker`
- L166 _public prototype_ `virtual TSharedPtr<IRemoteSessionChannel> Construct(ERemoteSessionChannelMode InMode, TSharedPtr<IBackChannelConnection, ESPMode::ThreadSafe> InConnection) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API REMOTESESSION_API`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Public/Channels/RemoteSessionChannel.h` (Public)


#### class `IRemoteSessionChannel`  
`class IRemoteSessionChannel`  
_L12-23_
- L16 _public function_ `IRemoteSessionChannel(ERemoteSessionChannelMode InRole, TBackChannelSharedPtr<IBackChannelConnection> InConnection)`
- L18 _public prototype_ `virtual ~IRemoteSessionChannel() = default;`
- L20 _public prototype_ `virtual void Tick(const float InDeltaTime) = 0;`
- L22 _public prototype_ `virtual const TCHAR* GetType() const = 0;`

#### class `IRemoteSessionChannelFactoryWorker`  
`class IRemoteSessionChannelFactoryWorker`  
_L25-30_
- L28 _public prototype_ `virtual ~IRemoteSessionChannelFactoryWorker() = default;`
- L29 _public prototype_ `virtual TSharedPtr<IRemoteSessionChannel> Construct(ERemoteSessionChannelMode InMode, TBackChannelSharedPtr<IBackChannelConnection> InConnection) const = 0;`

#### class `FRemoteSessionChannelRegistry`  
`class FRemoteSessionChannelRegistry`  
_L33-53_
- L36 _public function_ `static FRemoteSessionChannelRegistry& Get()`
- L42 _public prototype_ `void RegisterChannelFactory(const TCHAR* InChannelName, ERemoteSessionChannelMode InHostMode, TWeakPtr<IRemoteSessionChannelFactoryWorker> InFactory);`
- L43 _public prototype_ `void RemoveChannelFactory(TWeakPtr<IRemoteSessionChannelFactoryWorker> InFactory);`
- L45 _public prototype_ `TSharedPtr<IRemoteSessionChannel> CreateChannel(const FStringView InChannelName, ERemoteSessionChannelMode InMode, TBackChannelSharedPtr<IBackChannelConnection> InConnection);`
- L46 _public prototype_ `const TArray<FRemoteSessionChannelInfo>& GetRegisteredFactories() const;`
- L50 _protected prototype_ `FRemoteSessionChannelRegistry() = default;`
- L51 _protected member_ `TMap<FString, TWeakPtr<IRemoteSessionChannelFactoryWorker>> RegisteredFactories;`
- L52 _protected member_ `TArray<FRemoteSessionChannelInfo> KnownChannels;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API REMOTESESSION_API`
- L56 _macro_ `#define REGISTER_CHANNEL_FACTORY(ChannelName, FactoryClass, HostMode ) \`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Public/Channels/RemoteSessionFrameBufferChannel.h` (Public)
_(no declarations extracted)_

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Public/Channels/RemoteSessionImageChannel.h` (Public)


#### class `IRemoteSessionImageProvider`  
`class IRemoteSessionImageProvider`  
_L21-26_
- L24 _public prototype_ `virtual ~IRemoteSessionImageProvider() = default;`
- L25 _public prototype_ `virtual void Tick(const float InDeltaTime) = 0;`

#### struct `FRemoteSesstionImageCaptureStats`  
`struct FRemoteSesstionImageCaptureStats`  
_L47-52_
- L49 _public member_ `int32 FramesCaptured = 0;`
- L50 _public member_ `int32 FramesSkipped = 0;`
- L51 _public member_ `double LastUpdateTime = 0;`

#### struct `FRemoteSessionImageReceiveStats`  
`struct FRemoteSessionImageReceiveStats`  
_L55-61_
- L57 _public member_ `int32 FramesWaiting = 0;`
- L58 _public member_ `int32 FramesSkipped = 0;`
- L59 _public member_ `double MaxImageProcessTime = 0;`
- L60 _public member_ `double LastUpdateTime = 0;`

#### class `FRemoteSessionImageChannel`  
`class FRemoteSessionImageChannel : public IRemoteSessionChannel, FRunnable`  
_L68-195_
- inherits: `IRemoteSessionChannel,FRunnable`
- desc: A channel that takes an image (created by an IRemoteSessionImageProvider), then sends it to the client (with a FRemoteSessionImageSender). On the client images are decoded into a double-buffered texture that can be accessed via GetHostScreen.
- L103 _public prototype_ `FRemoteSessionImageChannel(ERemoteSessionChannelMode InRole, TSharedPtr<IBackChannelConnection, ESPMode::ThreadSafe> InConnection);`
- L105 _public prototype_ `~FRemoteSessionImageChannel();`
- L108 _public prototype_ `virtual void Tick(const float InDeltaTime) override;` — Tick this channel
- L111 _public prototype_ `UTexture2D* GetHostScreen() const;` — Get the client Texture2D to display
- L114 _public prototype_ `void SetImageProvider(TSharedPtr<IRemoteSessionImageProvider> ImageProvider);` — Set the ImageProvider that will produce the images that will be sent to the client
- L117 _public prototype_ `void SetFramebufferAsImageProvider();` — Sets up an image provider that mirrors the games framebuffer. WIll be the default if no ImageProvider is set.
- L120 _public prototype_ `void SetCompressQuality(int32 InQuality);` — Set the jpg compression quality
- L123 _public function_ `TSharedPtr<FRemoteSessionImageChannel::FImageSender, ESPMode::ThreadSafe> GetImageSender()` — Return the image sender connected to the clients
- L126 _public function_ `static const TCHAR* StaticType()` — Begin IRemoteSessionChannel implementation
- L127 _public function_ `virtual const TCHAR* GetType() const override`
- L133 _protected member_ `TWeakPtr<IBackChannelConnection, ESPMode::ThreadSafe> Connection;` — Underlying connection
- L136 _protected member_ `ERemoteSessionChannelMode Role;` — Our role
- L139 _protected member_ `TSharedPtr<IRemoteSessionImageProvider> ImageProvider;`
- L142 _protected prototype_ `void ReceiveHostImage(IBackChannelPacket& Message);` — Bound to receive incoming images
- L145 _protected prototype_ `void CreateTexture(const int32 InSlot, const int32 InWidth, const int32 InHeight);` — Creates a texture to receive images into
- L156 _protected member_ `FCriticalSection IncomingImageMutex;`
- L157 _protected member_ `TArray<TUniquePtr<FImageData>> IncomingEncodedImages;`
- L159 _protected member_ `FCriticalSection DecodedImageMutex;`
- L160 _protected member_ `TArray<TUniquePtr<FImageData>> IncomingDecodedImages;`
- L162 _protected member_ `UTexture2D* DecodedTextures[2];`
- L163 _protected member_ `TSharedPtr<TAtomic<int32>, ESPMode::ThreadSafe> DecodedTextureIndex;`
- L166 _protected member_ `TSharedPtr<FImageSender, ESPMode::ThreadSafe> ImageSender;` — Image sender used by the channel
- L169 _protected member_ `FDelegateHandle MessageCallbackHandle;` — So we can manage callback lifetimes properly
- L172 _protected member_ `int32 LastIncomingImageIndex;` — Last processed incoming image
- L175 _protected member_ `int32 LastDecodedImageIndex;` — Last processed decode image
- L178 _protected prototype_ `void ProcessIncomingTextures();` — Decode the incoming images on a dedicated thread
- L183 _protected prototype_ `uint32 Run();` — Background thread for decoding incoming images
- L184 _protected prototype_ `void StartBackgroundThread();`
- L185 _protected prototype_ `void ExitBackgroundThread();`
- L187 _protected member_ `FRunnableThread* BackgroundThread;`
- L188 _protected member_ `FEvent * ScreenshotEvent;`
- L190 _protected member_ `FThreadSafeBool ExitRequested;`
- L192 _protected member_ `bool HaveConfiguredImageProvider;`
- L194 _protected member_ `FRemoteSessionImageReceiveStats ReceiveStats;`

#### class `FRemoteSessionImageChannel::FImageSender`  
`class FImageSender`  
_L75-99_
- desc: A helper object responsible to take the raw data, encode it to jpg and send it to the client for the RemoteSessionImageChannel
- L79 _public prototype_ `FImageSender(TSharedPtr<IBackChannelConnection, ESPMode::ThreadSafe> InConnection);`
- L82 _public prototype_ `void SetCompressQuality(int32 InQuality);` — Set the jpg compression quality
- L85 _public prototype_ `void SendRawImageToClients(int32 Width, int32 Height, const TArray<FColor>& ImageData, int32 BytesPerRow = 0);` — Send an image to the connected clients
- L88 _public prototype_ `void SendRawImageToClients(int32 Width, int32 Height, const void* ImageData, int32 AllocatedImageDataSize, int32 BytesPerRow = 0);` — Send an image to the connected clients
- L93 _private member_ `TWeakPtr<IBackChannelConnection, ESPMode::ThreadSafe> Connection;` — Underlying connection
- L96 _private member_ `TAtomic<int32> CompressQuality;` — Compression quality of the raw image we wish to send to client
- L98 _private member_ `int32 NumSentImages;`

#### struct `FRemoteSessionImageChannel::FImageData`  
`struct FImageData`  
_L147-154_
- L149 _public member_ `int32 Width = 0;`
- L150 _public member_ `int32 Height = 0;`
- L151 _public member_ `int32 ImageIndex = 0;`
- L152 _public member_ `double TimeCreated = 0;`
- L153 _public member_ `TArray<uint8> ImageData;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API REMOTESESSION_API`
- L29 _delegate_ `DECLARE_STATS_GROUP(TEXT("RemoteSession"), STATGROUP_RemoteSession, STATC`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Public/Channels/RemoteSessionInputChannel.h` (Public)


#### class `FRemoteSessionInputChannel`  
`class FRemoteSessionInputChannel : public IRemoteSessionChannel, public IRecordingMessageHandlerWriter`  
_L17-61_
- inherits: `IRemoteSessionChannel,IRecordingMessageHandlerWriter`
- L21 _public prototype_ `FRemoteSessionInputChannel(ERemoteSessionChannelMode InRole, TSharedPtr<IBackChannelConnection, ESPMode::ThreadSafe> InConnection);`
- L23 _public prototype_ `~FRemoteSessionInputChannel();`
- L25 _public prototype_ `virtual void Tick(const float InDeltaTime) override;`
- L27 _public prototype_ `virtual void RecordMessage(const TCHAR* MsgName, const TArray<uint8>& Data) override;`
- L29 _public prototype_ `void OnRemoteMessage(IBackChannelPacket& Message);`
- L31 _public prototype_ `void SetPlaybackWindow(TWeakPtr<SWindow> InWindow, TWeakPtr<FSceneViewport> InViewport);`
- L33 _public prototype_ `void SetInputRect(const FVector2D& TopLeft, const FVector2D& Extents);`
- L35 _public prototype_ `void TryRouteTouchMessageToWidget(bool bRouteMessageToWidget);`
- L42 _public prototype_ `FOnRouteTouchDownToWidgetFailedDelegate* GetOnRouteTouchDownToWidgetFailedDelegate();` — Delegate that fires when routing a touch message to the widget did not work. @note Only useful during playback. @return Null when recording, Pointer to delegate during playback.
- L44 _public function_ `static const TCHAR* StaticType()`
- L45 _public function_ `virtual const TCHAR* GetType() const override`
- L49 _protected member_ `TSharedPtr<FGenericApplicationMessageHandler> DefaultHandler;`
- L51 _protected member_ `TSharedPtr<FRecordingMessageHandler> RecordingHandler;`
- L53 _protected member_ `TSharedPtr<FRecordingMessageHandler> PlaybackHandler;`
- L55 _protected member_ `TSharedPtr<IBackChannelConnection, ESPMode::ThreadSafe> Connection;`
- L57 _protected member_ `ERemoteSessionChannelMode Role;`
- L60 _protected member_ `FDelegateHandle MessageCallbackHandle;` — So we can manage callback lifetimes properly

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API REMOTESESSION_API`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Public/Channels/RemoteSessionLiveLinkChannel.h` (Public)


#### class `FRemoteSessionLiveLinkChannel`  
`class FRemoteSessionLiveLinkChannel : public IRemoteSessionChannel`  
_L16-47_
- inherits: `IRemoteSessionChannel`
- L20 _public prototype_ `FRemoteSessionLiveLinkChannel(ERemoteSessionChannelMode InRole, TSharedPtr<IBackChannelConnection, ESPMode::ThreadSafe> InConnection);`
- L22 _public prototype_ `virtual ~FRemoteSessionLiveLinkChannel();`
- L24 _public prototype_ `virtual void Tick(const float InDeltaTime) override;`
- L27 _public prototype_ `void SendLiveLinkHello(const FStringView InSubjectName);` — Sends the current location and rotation for the XRTracking system to the remote
- L30 _public function_ `static const TCHAR* StaticType()` — Begin IRemoteSessionChannel implementation
- L31 _public function_ `virtual const TCHAR* GetType() const override`
- L38 _protected prototype_ `void ReceiveLiveLinkHello(IBackChannelPacket& Message);` — Handles data coming from the client
- L40 _protected member_ `TSharedPtr<IBackChannelConnection, ESPMode::ThreadSafe> Connection;`
- L42 _protected member_ `ERemoteSessionChannelMode Role;`
- L45 _protected member_ `FDelegateHandle RouteHandle;` — So we can manage callback lifetimes properly

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API REMOTESESSION_API`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Public/Channels/RemoteSessionXRTrackingChannel.h` (Public)


#### class `FXRTrackingProxy`  
`class FXRTrackingProxy : public FXRTrackingSystemBase`  
_L17-35_
- inherits: `FXRTrackingSystemBase`
- L21 _public function_ `FXRTrackingProxy(IARSystemSupport* InARSystemSupport) : FXRTrackingSystemBase(InARSystemSupport)`
- L25 _public function_ `virtual bool IsTracking(int32 DeviceId) override`
- L26 _public function_ `virtual bool DoesSupportPositionalTracking() const override`
- L27 _public function_ `virtual bool IsHeadTrackingAllowed() const override`
- L28 _public function_ `virtual void ResetOrientationAndPosition(float Yaw = 0.f) override`
- L29 _public function_ `virtual float GetWorldToMetersScale() const override`
- L31 _public prototype_ `virtual bool EnumerateTrackedDevices(TArray<int32>& OutDevices, EXRTrackedDeviceType Type) override;`
- L32 _public prototype_ `virtual bool GetCurrentPose(int32 DeviceId, FQuat& OutOrientation, FVector& OutPosition) override;`
- L33 _public prototype_ `virtual FName GetSystemName() const override;`
- L34 _public function_ `virtual int32 GetXRSystemFlags() const override`

#### class `FRemoteSessionXRTrackingChannel`  
`class FRemoteSessionXRTrackingChannel : public IRemoteSessionChannel`  
_L37-80_
- inherits: `IRemoteSessionChannel`
- L42 _public prototype_ `FRemoteSessionXRTrackingChannel(ERemoteSessionChannelMode InRole, TSharedPtr<IBackChannelConnection, ESPMode::ThreadSafe> InConnection);`
- L44 _public prototype_ `virtual ~FRemoteSessionXRTrackingChannel();`
- L46 _public prototype_ `virtual void Tick(const float InDeltaTime) override;`
- L49 _public prototype_ `void SendXRTracking();` — Sends the current location and rotation for the XRTracking system to the remote
- L52 _public prototype_ `void ReceiveXRTracking(IBackChannelPacket& Message);` — Handles data coming from the client
- L55 _public function_ `static const TCHAR* StaticType()` — Begin IRemoteSessionChannel implementation
- L56 _public function_ `virtual const TCHAR* GetType() const override`
- L61 _protected prototype_ `FRemoteSessionXRTrackingChannel(ERemoteSessionChannelMode InRole, TSharedPtr<IBackChannelConnection, ESPMode::ThreadSafe> InConnection, IARSystemSupport* ARSystemSupport);` — Only to be called by child classes
- L63 _protected member_ `TSharedPtr<IBackChannelConnection, ESPMode::ThreadSafe> Connection;`
- L64 _protected member_ `ERemoteSessionChannelMode Role;`
- L67 _protected member_ `TSharedPtr<IXRTrackingSystem, ESPMode::ThreadSafe> XRSystem;` — If we're sending, this is GEngine->XRSystem. If we are receiving, this is the previous GEngine->XRSystem
- L69 _protected member_ `TSharedPtr<FXRTrackingProxy, ESPMode::ThreadSafe> ProxyXRSystem;` — Used to set the values from the remote client as the XRTracking's pose
- L72 _protected member_ `IARSystemSupport* ARSystemSupport;` — Used by a child class to pass in a AR system to use as part of the proxy
- L76 _private member_ `FDelegateHandle MessageCallbackHandle;` — So we can manage callback lifetimes properly
- L79 _private prototype_ `void Init();` — Used to finish construction of the class. Should be called from within the ctors

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API REMOTESESSION_API`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Public/IRemoteSessionRole.h` (Public)


#### class `IRemoteSessionRole`  
`class IRemoteSessionRole`  
_L11-69_
- L14 _public prototype_ `virtual~IRemoteSessionRole() = default;`
- L16 _public prototype_ `virtual bool IsConnected() const = 0;`
- L18 _public prototype_ `virtual bool HasError() const = 0;`
- L20 _public prototype_ `virtual FString GetErrorMessage() const = 0;`
- L23 _public prototype_ `virtual bool IsLegacyConnection() const = 0;` — Future versions will support querying the version type, at the moment we just have old & new
- L26 _public prototype_ `virtual FString GetRemoteVersion() const = 0;` — Returns the version string reported by the remote peer during the Hello handshake. Empty before Connected.
- L29 _public prototype_ `virtual bool IsUsingPixelStreaming() const = 0;` — True when PixelStreaming was negotiated as the streaming transport for this session.
- L32 _public prototype_ `virtual FString GetRemotePixelStreamingVersion() const = 0;` — PixelStreaming version advertised by the remote peer (e.g. "PS2"). Empty when the peer did not advertise PS.
- L35 _public prototype_ `virtual FString GetRemoteBuildInfo() const = 0;` — Opaque build identifier advertised by the remote peer in the Hello handshake. Empty when the peer did not advertise one.
- L39 _public prototype_ `virtual FDelegateHandle RegisterConnectionChangeDelegate(FOnRemoteSessionConnectionChange::FDelegate InDelegate) = 0;` — Registers a delegate for notifications of connection changes
- L42 _public prototype_ `virtual FDelegateHandle RegisterChannelListDelegate(FOnRemoteSessionReceiveChannelList::FDelegate InDelegate) = 0;` — Register for notifications when the host sends a list of available channels
- L45 _public prototype_ `virtual FDelegateHandle RegisterChannelChangeDelegate(FOnRemoteSessionChannelChange::FDelegate InDelegate) = 0;` — Register for notifications whenever a change in the state of a channel occurs
- L47 _public prototype_ `virtual void RegisterHelloRouteMessageDelegate(FBackChannelRouteDelegate::FDelegate InDelegate) = 0;`
- L50 _public prototype_ `virtual void RemoveAllDelegates(FDelegateUserObject UserObject) = 0;` — Unregister all delegates for the specified object
- L52 _public prototype_ `virtual TSharedPtr<IRemoteSessionChannel> GetChannel(const TCHAR* Type) = 0;`
- L55 _public function_ `template<class T> TSharedPtr<T> GetChannel()`
- L67 _public prototype_ `virtual bool OpenChannel(const FRemoteSessionChannelInfo& Info) = 0;`

#### class `IRemoteSessionUnmanagedRole`  
`class IRemoteSessionUnmanagedRole : public IRemoteSessionRole`  
_L71-76_
- inherits: `IRemoteSessionRole`
- L74 _public prototype_ `virtual void Tick(float DeltaTime) = 0;`
- L75 _public prototype_ `virtual void Close(const FString& InReason) = 0;`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Public/ImageProviders/RemoteSessionFrameBufferImageProvider.h` (Public)


#### class `FRemoteSessionFrameBufferImageProvider`  
`class FRemoteSessionFrameBufferImageProvider : public IRemoteSessionImageProvider`  
_L19-68_
- inherits: `IRemoteSessionImageProvider`
- desc: Use the FrameGrabber on the host to provide an image to the image channel.
- L23 _public prototype_ `FRemoteSessionFrameBufferImageProvider(TSharedPtr<FRemoteSessionImageChannel::FImageSender, ESPMode::ThreadSafe> ImageSender);`
- L24 _public prototype_ `~FRemoteSessionFrameBufferImageProvider();`
- L27 _public prototype_ `void SetCaptureViewport(TSharedRef<FSceneViewport> Viewport);` — Specifies which viewport to capture
- L30 _public prototype_ `void SetCaptureFrameRate(int32 InFramerate);` — Specifies the framerate at
- L33 _public prototype_ `virtual void Tick(const float InDeltaTime) override;` — Tick this channel
- L36 _public prototype_ `void OnViewportResized(FVector2D NewSize);` — Signals that the viewport was resized
- L41 _protected prototype_ `void ReleaseFrameGrabber();` — Release the FrameGrabber
- L44 _protected prototype_ `void OnWindowClosedEvent(const TSharedRef<SWindow>&);` — When the window is destroyed
- L47 _protected prototype_ `void CreateFrameGrabber(TSharedRef<FSceneViewport> Viewport);` — Safely create the frame grabber
- L49 _protected member_ `TWeakPtr<FRemoteSessionImageChannel::FImageSender, ESPMode::ThreadSafe> ImageSender;`
- L51 _protected member_ `TSharedPtr<FFrameGrabber> FrameGrabber;`
- L53 _protected member_ `TSharedPtr<FThreadSafeCounter, ESPMode::ThreadSafe> NumDecodingTasks;`
- L56 _protected member_ `double LastSentImageTime;` — Time we last sent an image
- L59 _protected member_ `bool ViewportResized;` — Shows that the viewport was just resized
- L62 _protected member_ `TWeakPtr<FSceneViewport> SceneViewport;` — Holds a reference to the scene viewport
- L65 _protected member_ `TWeakPtr<SWindow> SceneViewportWindow;` — Holds a reference to the SceneViewport SWindow
- L67 _protected member_ `FRemoteSesstionImageCaptureStats CaptureStats;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API REMOTESESSION_API`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Public/ImageProviders/RemoteSessionMediaOutput.h` (Public)


#### class `URemoteSessionMediaOutput`  
`class URemoteSessionMediaOutput : public UMediaOutput`  
_L13-34_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMediaOutput`
- L19 _public function_ `virtual FIntPoint GetRequestedSize() const override`
- L20 _public function_ `virtual EPixelFormat GetRequestedPixelFormat() const override`
- L21 _public function_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override`
- L23 _protected prototype_ `virtual UMediaCapture* CreateMediaCaptureImpl() override;`
- L28 _public prototype_ `void SetImageChannel(TWeakPtr<FRemoteSessionImageChannel> ImageChannel);`
- L29 _public function_ `TWeakPtr<FRemoteSessionImageChannel> GetImageChannel() const`
- L33 _private member_ `TWeakPtr<FRemoteSessionImageChannel> ImageChannel;`

#### class `URemoteSessionMediaCapture`  
`class URemoteSessionMediaCapture : public UMediaCapture`  
_L38-56_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMediaCapture`
- L45 _public prototype_ `virtual void OnFrameCaptured_RenderingThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, void* InBuffer, int32 Width, int32 Height, int BytesPerRow) override;`
- L46 _public prototype_ `virtual bool InitializeCapture() override;`
- L51 _private prototype_ `void CacheValues();`
- L55 _private member_ `TSharedPtr<FRemoteSessionImageChannel> ImageChannel;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API REMOTESESSION_API`

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Public/RemoteSession.h` (Public)


#### class `IRemoteSessionModule`  
`class IRemoteSessionModule : public IModuleInterface`  
_L22-94_
- inherits: `IModuleInterface`
- L27 _public prototype_ `virtual void StartupModule() override = 0;` — IModuleInterface implementation
- L28 _public prototype_ `virtual void ShutdownModule() override = 0;`
- L41 _public prototype_ `virtual void AddChannelFactory(const FStringView InChannelName, ERemoteSessionChannelMode InHostMode, TWeakPtr<IRemoteSessionChannelFactoryWorker> Worker) = 0;` — Register a third party channel
- L44 _public prototype_ `virtual void RemoveChannelFactory(TWeakPtr<IRemoteSessionChannelFactoryWorker> Worker) = 0;` — Unregister a channel factory
- L51 _public prototype_ `virtual TSharedPtr<IRemoteSessionRole> CreateClient(const TCHAR* RemoteAddress) = 0;` — Returns a reference to the client role (if any)
- L54 _public prototype_ `virtual void StopClient(TSharedPtr<IRemoteSessionRole> Client, const FString& InReason) = 0;` — Stops the client. After this CreateClient() must be called if a new connection is desired
- L56 _public prototype_ `static FString GetLocalVersion();`
- L58 _public prototype_ `static FString GetLastSupportedVersion();`
- L61 _public prototype_ `static void SetClientBuildInfo(const FString& BuildInfo);` — Opaque build identifier sent in the Hello handshake; surfaced to the peer as "BuildInfo".
- L63 _public prototype_ `static FString GetClientBuildInfo();`
- L66 _public prototype_ `static void SetAnalyticsProvider(TSharedPtr<IAnalyticsProviderET> Provider);` — Analytics provider for RemoteSession events; falls back to FEngineAnalytics when unset.
- L72 _public prototype_ `virtual void InitHost(const int16 Port=0) = 0;` — Starts a RemoteSession server that listens for clients on the provided port
- L75 _public prototype_ `virtual bool IsHostRunning() const = 0;` — Returns true/false based on the running state of the host server
- L78 _public prototype_ `virtual bool IsHostConnected() const = 0;` — Returns true/false if a client is connected
- L81 _public prototype_ `virtual void StopHost(const FString& InReason) = 0;` — Stops the server, after this InitHost() must be called if a new connection is desired
- L84 _public prototype_ `virtual TSharedPtr<IRemoteSessionRole> GetHost() const = 0;` — Returns a reference to the server role (if any)
- L87 _public prototype_ `virtual TSharedPtr<IRemoteSessionUnmanagedRole> CreateHost(TArray<FRemoteSessionChannelInfo> SupportedChannels, int32 Port) const = 0;` — Returns host that is not controlled by the module
- L90 _public prototype_ `virtual void SetHostAnalyticsEventName(const FString& EventName) = 0;` — Event name for the host connection-established analytics event. Resets on StopHost.
- L93 _public prototype_ `virtual void SetHostAnalyticsEventMode(EAnalyticsRecordEventMode Mode) = 0;` — Record mode for the host connection-established analytics event. Resets to Cached on StopHost.

#### enum `IRemoteSessionModule::(anonymous)`  
``  
_L34-36_

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API REMOTESESSION_API`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRemoteSession, Log, All);`
- L35 _enumerator_ `kDefaultPort = 2049` (scope `IRemoteSessionModule::__anon237ef5b60103`)

### `Plugins/Experimental/RemoteSession/Source/RemoteSession/Public/RemoteSessionTypes.h` (Public)


#### enum `ERemoteSessionChannelMode`  
`enum class ERemoteSessionChannelMode : int32`  
_L12-18_
- reflection: `UENUM()`
- L14 _public enumerator_ `Unknown`
- L15 _public enumerator_ `Read`
- L16 _public enumerator_ `Write`
- L17 _public enumerator_ `MaxValue`

#### enum `ERemoteSessionChannelChange`  
`enum class ERemoteSessionChannelChange : int32`  
_L21-25_
- reflection: `UENUM()`
- L23 _public enumerator_ `Created`
- L24 _public enumerator_ `Destroyed`

#### enum `ERemoteSessionConnectionChange`  
`enum class ERemoteSessionConnectionChange : int32`  
_L28-32_
- reflection: `UENUM()`
- L30 _public enumerator_ `Connected`
- L31 _public enumerator_ `Disconnected`

#### struct `FRemoteSessionChannelInfo`  
`struct FRemoteSessionChannelInfo`  
_L36-50_
- reflection: `USTRUCT()`
- L41 _public member_ `FString Type;` — `UPROPERTY(config)`
- L44 _public member_ `ERemoteSessionChannelMode Mode = ERemoteSessionChannelMode::Unknown;` — `UPROPERTY(config)`
- L46 _public prototype_ `FRemoteSessionChannelInfo() = default;`
- L47 _public function_ `FRemoteSessionChannelInfo(FString InType, ERemoteSessionChannelMode InMode) : Type(InType), Mode(InMode)`

#### class `URemoteSessionSettings`  
`class URemoteSessionSettings : public UObject`  
_L63-112_
- reflection: `UCLASS(MinimalAPI, config = Engine)`
- inherits: `UObject`
- desc: Settings for the Asset Management framework, which can be used to discover, load, and audit game-specific asset types
- L71 _public member_ `int32 HostPort = 2049;` — `UPROPERTY(config)` — Port that the host will listen on
- L75 _public member_ `int32 ConnectionTimeout = 7;` — `UPROPERTY(config)` — Time until a connection will timeout
- L79 _public member_ `int32 ConnectionTimeoutWhenDebugging = 30;` — `UPROPERTY(config)` — Time until a connection will timeout when a debugger is attached
- L83 _public member_ `int32 PingTime = 1;` — `UPROPERTY(config)` — Time between pings
- L87 _public member_ `bool bAllowInShipping = false;` — `UPROPERTY(config)` — Whether RemoteSession is functional in a shipping build
- L91 _public member_ `bool bAutoHostWithPIE = true;` — `UPROPERTY(config)` — Does PIE automatically start hosting a session?
- L95 _public member_ `bool bAutoHostWithGame = true;` — `UPROPERTY(config)` — Does launching a game automatically host a session?
- L99 _public member_ `int32 ImageQuality = 80;` — `UPROPERTY(config)` — Image quality (1-100)
- L103 _public member_ `int32 FrameRate = 60;` — `UPROPERTY(config)` — Framerate of images from the host (will be min of this value and the actual framerate of the game
- L107 _public member_ `TArray<FString> AllowedChannels;` — `UPROPERTY(config)` — Restrict remote session to these channels. If empty all registered channels are available
- L111 _public member_ `TArray<FString> DeniedChannels;` — `UPROPERTY(config)` — Don't allow these channels to be used

#### Free symbols / members of external scopes

- L53 _prototype_ `const TCHAR* LexToString(ERemoteSessionChannelMode InMode);`
- L54 _prototype_ `void LexFromString(ERemoteSessionChannelMode& Value, const TCHAR* String);`
- L56 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRemoteSessionConnectionChange, IRemoteSessionRole* , ERemoteSessionConnectionChange );`
- L56 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRemoteSessionConnectionChange, IRemoteSessionRole* , ERemoteSessionConnectionChange );`
- L57 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnRemoteSessionChannelChange, IRemoteSessionRole* , TWeakPtr<IRemoteSessionChannel> , ERemoteSessionChannelChange );`
- L57 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnRemoteSessionChannelChange, IRemoteSessionRole* , TWeakPtr<IRemoteSessionChannel> , ERemoteSessionChannelChange );`
- L58 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRemoteSessionReceiveChannelList, IRemoteSessionRole* , TArrayView< FRemoteSessionChannelInfo> );`
- L58 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRemoteSessionReceiveChannelList, IRemoteSessionRole* , TArrayView< FRemoteSessionChannelInfo> );`
