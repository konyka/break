# Plugins / ScreenReader

- module root: `Plugins/Experimental/ScreenReader/Source/ScreenReader`
- headers: 10; symbols: 223
- symbol kinds: class=8, delegate=5, enum=1, enumerator=3, function=35, member=23, prototype=141, struct=7
- PrivateDependencyModuleNames: ApplicationCore, Engine, TextToSpeech
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Experimental/ScreenReader/Source/ScreenReader/Private/Announcement/ScreenReaderWidgetAnnouncementBuilder.h` (Private)


#### class `FScreenReaderWidgetAnnouncementBuilder`  
`class FScreenReaderWidgetAnnouncementBuilder`  
_L10-26_
- L13 _public prototype_ `FScreenReaderWidgetAnnouncementBuilder() = default;`
- L14 _public prototype_ `~FScreenReaderWidgetAnnouncementBuilder() = default;`
- L15 _public prototype_ `FString BuildWidgetAnnouncement(const TSharedRef<IAccessibleWidget>& InWidget);`
- L18 _private prototype_ `FString BuildLabel(const TSharedRef<IAccessibleWidget>& InWidget) const;`
- L19 _private prototype_ `FString BuildRole(const TSharedRef<IAccessibleWidget>& InWidget) const;`
- L20 _private prototype_ `FString BuildValue(const TSharedRef<IAccessibleWidget>& InWidget) const;`
- L21 _private prototype_ `FString BuildHelpText(const TSharedRef<IAccessibleWidget>& InWidget) const;`
- L22 _private prototype_ `FString BuildInteractionDescription(const TSharedRef<IAccessibleWidget>& InWidget) const;`
- L24 _private member_ `static const TMap<EAccessibleWidgetType, FText> WidgetTypeToAccessibleRoleMap;`
- L25 _private member_ `static const TMap<EAccessibleWidgetType, FText> WidgetTypeToInteractionDescriptionMap;`

### `Plugins/Experimental/ScreenReader/Source/ScreenReader/Private/ScreenReaderLog.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogScreenReader, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogScreenReader, Log, All);`
- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogScreenReaderInput, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogScreenReaderInput, Log, All);`
- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogScreenReaderAnnouncement, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogScreenReaderAnnouncement, Log, All);`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogScreenReaderNavigation, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogScreenReaderNavigation, Log, All);`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogScreenReaderAction, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogScreenReaderAction, Log, All);`

### `Plugins/Experimental/ScreenReader/Source/ScreenReader/Public/Announcement/ScreenReaderAnnouncement.h` (Public)


#### enum `EScreenReaderAnnouncementPriority`  
`enum class EScreenReaderAnnouncementPriority : uint8`  
_L13-18_
- reflection: `UENUM()`
- desc: The priority level associated with a screen reader announcement. The priority of an announcement could be used to determine if an announcement A could interrupt announcement B or to help order the announcements if multiple are queued.
- L15 _public enumerator_ `High = 0`
- L16 _public enumerator_ `Medium`
- L17 _public enumerator_ `Low`

#### struct `FScreenReaderAnnouncementInfo`  
`struct FScreenReaderAnnouncementInfo`  
_L30-103_
- reflection: `USTRUCT(BlueprintType)`
- desc: A struct that contains information about how a screen reader announcement should behave when the announcement is requested to be spoken. This struct holds information to determine an announcement's priority in relation to other announcements and determines if an announcement can be interrupted by other announcements and if an announcement should be queued if it cannot be made immendiately. For C++ users, please use the static methods provided to create instances of FScreenReaderInfo with pre-defined defaults that will satisfy 80% of your use cases. Please see FScreenReaderUser::RequestSpeak() for examples of how to use this struct. @see FScreenReaderUser, FScreenReaderAnnouncement
- L36 _public prototype_ `FScreenReaderAnnouncementInfo() = default;` — Only used to satisfy USTRUCT constraints Please use ctor that takes parameters
- L37 _public prototype_ `FScreenReaderAnnouncementInfo(bool bInShouldQueue, bool bInInterruptable, EScreenReaderAnnouncementPriority InPriority);`
- L38 _public function_ `bool ShouldQueue() const`
- L42 _public function_ `bool IsInterruptable() const`
- L46 _public function_ `EScreenReaderAnnouncementPriority GetPriority() const`
- L50 _public function_ `double GetTimestamp() const`
- L55 _public prototype_ `FString ToString() const;` — Returns a string that represents all of the data reflected in this struct.
- L64 _public function_ `static FScreenReaderAnnouncementInfo DefaultWidgetAnnouncement()` — The announcement info used for announcements concerning widgets and their content. These are the lowest priority, are interruptable and will not be queued if interrupted. Use this when requestin any announcements related to widgets that the user can easily access again E.g Useful for announcing widgets that the user is currently focused on. The user can always refocus on the widget to hear its contents spoken so it doesn't matter if it is interrupted.
- L74 _public function_ `static FScreenReaderAnnouncementInfo Important()` — An announcement info used for announcements that are of critical importance to the end user. Announcements with this announcement info have the highest priority, are not interruptable by other announcements and will be queued if multiple important announcements are requested. Use this for communicating critical information to an end user. E.g Use this for announcements concerning the system (battery low, accessibility enabled etc) or important in game events that cannot be revisted or played again.
- L85 _public function_ `FScreenReaderAnnouncementInfo UserFeedback()` — This announcement info is used for announcements to provide feedback for end user actions or inform them of changes. Announcements with this announcement info have medium priority, can be interrupted and will not be queued if interrupted by an announcement of equal or higher priority. User this announcement info for announcements that provide feedback to the end user. E.g When they have successfully activated a UI element, the screen has changed to display a different meny or when new elements have appeared on screen that the user should know about.
- L93 _private member_ `bool bShouldQueue = false;` — `UPROPERTY(BlueprintReadWrite, Category="ScreenReaderAnnouncementInfo", meta = (AllowPrivateAccess = "true"))` — True if the associated announcement should be queued if it cannot be spoken immediately or is interrupted. Else false.
- L96 _private member_ `bool bInterruptable= true;` — `UPROPERTY(BlueprintReadWrite, Category="ScreenReaderAnnouncementInfo", meta = (AllowPrivateAccess = "true"))` — True if the associazted announcement can be intrrupted by another announcement. Else false.
- L99 _private member_ `EScreenReaderAnnouncementPriority Priority = EScreenReaderAnnouncementPriority::Medium;` — `UPROPERTY(BlueprintReadWrite, Category="ScreenReaderAnnouncementInfo", meta = (AllowPrivateAccess = "true"))` — The priority level of the associated announcement.
- L102 _private member_ `double Timestamp = FPlatformTime::Seconds();` — The timestamp for when the associated announcement was created.

#### struct `FScreenReaderAnnouncement`  
`struct FScreenReaderAnnouncement`  
_L112-186_
- reflection: `USTRUCT(BlueprintType)`
- desc: A screen reader announcement represents a localized message that a user wants to speak to an end user. This class is used to request announcements to be spoken to an end user via the FScreenReaderUser class. FScreenReaderUser::RequestSpeak() for instructions on how to use the class. @see FScreenReaderUser
- L118 _public prototype_ `FScreenReaderAnnouncement() = default;` — Only used to satisfy USTRUCT requirements Please use ctor that takes arguments
- L126 _public prototype_ `FScreenReaderAnnouncement(FString InAnnouncementString, FScreenReaderAnnouncementInfo );` — The constructor that should be used in most cases. @param InAnnouncementString The localized string that a user wishes to rquest to speak to a user FScreenReaderAnnouncement(FString InAnnouncementString, FScreenReaderAnnouncementInfo ); @param The announcement info associated with the announcement string to control if this announcement can be interrupted or queued when a request the speak this announcement is made.
- L127 _public function_ `const FString& GetAnnouncementString() const`
- L128 _public function_ `const FScreenReaderAnnouncementInfo& GetAnnouncementInfo() const`
- L130 _public prototype_ `FString ToString() const;` — Converts the contents of the announcement to a string for easy printing. Useful for debugging.
- L175 _public function_ `template<typename InterruptionPolicy> static bool CanBeInterruptedBy(const FScreenReaderAnnouncement& Interruptee, const FScreenReaderAnnouncement& Interrupter, const InterruptionPolicy& InInterruptionPolicy)` — A static function that determines if one announcement can be interrupted by another based on a provided interruption policy.true @param Interruptee The announcement that the Interruptor will try to interrupt @param Interrupter The announcement that is trying to interrupt Interruptee @param InInterruptionPolicy The policy used to determine if the Interruptee can be interrupted by the Interrupter. Users can create their own interruption policies that satisfy the interface provided by FDefaultInterruptionPolicy. @return Returns true if the Interruptee can be interrupted by the Interrupter based on the passed in interruption policy. Else returns false. @see FDefaultInterruptionPolicy
- L182 _public member_ `FString AnnouncementString;` — `UPROPERTY(BlueprintReadWrite, Category="ScreenReaderAnnouncement")` — A localized string that represents the message to be spoken to a end user
- L185 _public member_ `FScreenReaderAnnouncementInfo AnnouncementInfo;` — `UPROPERTY(BlueprintReadWrite, Category="ScreenReaderAnnouncement")` — The announcement info associated with the announcement which controls how the announcement behaves when a user requests this announcement to be spoken to an end user

#### struct `FScreenReaderAnnouncement::FDefaultComparator`  
`struct FDefaultComparator`  
_L136-147_
- desc: The default comparator for screen reader announcements. Can be used to order screen announcements in a priority queue Users can provide their own comaprators by implementing the same interface.
- L139 _public function_ `bool operator()(const FScreenReaderAnnouncement& A, const FScreenReaderAnnouncement& B) const` — Returns true if A is less than B

#### struct `FScreenReaderAnnouncement::FDefaultInterruptionPolicy`  
`struct FDefaultInterruptionPolicy`  
_L153-163_
- desc: The default interruption policy to determine if announcement A can be interrupted by announcement B. Users can provide their own implementation by creating their own struct and implementing the same interface.
- L156 _public function_ `bool CanBeInterruptedBy(const FScreenReaderAnnouncement& Interruptee, const FScreenReaderAnnouncement& Interrupter) const` — Returns true if the interruptee can be interrupted by the interruptor. Else returns false

### `Plugins/Experimental/ScreenReader/Source/ScreenReader/Public/Announcement/ScreenReaderAnnouncementChannel.h` (Public)


#### class `FScreenReaderAnnouncementChannel`  
`class FScreenReaderAnnouncementChannel`  
_L18-54_
- desc: An announcement channel handles processing of announcements and speaking announcements through text to speech (TTS). Announcements are forwarded here from a screen reader user and the announcements will be spoken immediately, queued or interrupt the currently spoken announcement. See FScreenReaderUser for an explanation of these functions and FScreenReaderAnnouncement for how announcements are used. @see FScreenReaderUser, FScreenReaderAnnouncement, FScreenReaderAnnouncementInfo
- L21 _public prototype_ `explicit FScreenReaderAnnouncementChannel(const TSharedRef<FTextToSpeechBase>& InTextToSpeech);`
- L22 _public prototype_ `virtual ~FScreenReaderAnnouncementChannel();`
- L23 _public prototype_ `FScreenReaderAnnouncementChannel(const FScreenReaderAnnouncementChannel& OtherAnnouncementChannel) = delete;`
- L24 _public prototype_ `FScreenReaderAnnouncementChannel& operator=(const FScreenReaderAnnouncementChannel& OtherAnnouncementChannel) = delete;`
- L26 _public prototype_ `void Activate();`
- L27 _public prototype_ `void Deactivate();`
- L29 _public prototype_ `FScreenReaderReply RequestSpeak(FScreenReaderAnnouncement InAnnouncement);`
- L30 _public prototype_ `FScreenReaderReply StopSpeaking();`
- L31 _public prototype_ `bool IsSpeaking() const;`
- L32 _public prototype_ `FScreenReaderReply ClearAllAnnouncements();`
- L33 _public prototype_ `FScreenReaderReply RequestSpeakWidget(const TSharedRef<IAccessibleWidget>& InWidget);`
- L35 _public prototype_ `float GetSpeechVolume() const;`
- L36 _public prototype_ `FScreenReaderReply SetSpeechVolume(float InVolume);`
- L37 _public prototype_ `float GetSpeechRate() const;`
- L38 _public prototype_ `FScreenReaderReply SetSpeechRate(float InRate);`
- L39 _public prototype_ `FScreenReaderReply MuteSpeech();`
- L40 _public prototype_ `FScreenReaderReply UnmuteSpeech();`
- L41 _public prototype_ `bool IsSpeechMuted() const;`
- L48 _private prototype_ `void OnTextToSpeechFinishSpeaking();` — A callback that is bound to the text to speech delegate. The delegate fires when a string is fully synthesized and played to an end userwithout any interruption or stopping. This function i sused to respond to that event and speak the next queued announcement.
- L50 _private member_ `FScreenReaderAnnouncement CurrentAnnouncement;` — The current announcement that is being spoken. Will have an empty string if no announcements are currently being spoken.
- L52 _private member_ `TArray<FScreenReaderAnnouncement> AnnouncementQueue;` — TheA priority queue for all of the queued announcements.
- L53 _private member_ `TSharedRef<FTextToSpeechBase> TextToSpeech;`

### `Plugins/Experimental/ScreenReader/Source/ScreenReader/Public/GenericPlatform/IScreenReaderBuilder.h` (Public)


#### class `IScreenReaderBuilder`  
`class IScreenReaderBuilder`  
_L14-39_
- desc: The abstract interface for builders of all screen readers. Users should subclass and provide a concrete implementation for building their custom screen readers.
- L17 _public prototype_ `IScreenReaderBuilder() = default;`
- L18 _public prototype_ `virtual ~IScreenReaderBuilder() = default;`
- L38 _public prototype_ `virtual TSharedRef<FScreenReaderBase> Create(const IScreenReaderBuilder::FArgs& InArgs) = 0;` — A pure virtual function to build a screen reader. Users must override this class to provide logic for building their custom screen readers. @param InArgs The arguments used to build a screen reader @return The constructed screen reader built from the passed in arguments

#### struct `IScreenReaderBuilder::FArgs`  
`struct FArgs`  
_L21-31_
- desc: The arguments to be passed to the screen reader to be built
- L24 _public prototype_ `FArgs() = delete;`
- L25 _public function_ `explicit FArgs(const TSharedRef<GenericApplication>& InPlatformApplication) : PlatformApplication(InPlatformApplication)`
- L28 _public prototype_ `~FArgs() = default;`
- L30 _public member_ `const TSharedRef<GenericApplication> PlatformApplication;` — The platform application to be passed to the screen reader for initialization.

### `Plugins/Experimental/ScreenReader/Source/ScreenReader/Public/GenericPlatform/ScreenReaderApplicationMessageHandlerBase.h` (Public)


#### class `FScreenReaderApplicationMessageHandlerBase`  
`class FScreenReaderApplicationMessageHandlerBase : public FGenericApplicationMessageHandler`  
_L17-106_
- inherits: `FGenericApplicationMessageHandler`
- desc: The base class all screen reader application message handlers should derive from. By default, this is just a proxy for the underlying target message handler. The screen reader application message handler will intercept all application messages and may perform processing on the events before consuming the event or passing it to the underlying target message handler. Child classes should override the virtual event handlers from FGenericAccessibleMessageHandler to perform input processing for thier needs. For example: A mobile screen reader application message handler can subclass this class and intercept touch inputs to perform gesture detection to provide alternative navigation schemes for users. A desktop screen reader application message handler can subclass this class and intercept mouse movement events to speak widgets that the user mouses over.
- L20 _public prototype_ `FScreenReaderApplicationMessageHandlerBase() = delete;`
- L21 _public prototype_ `FScreenReaderApplicationMessageHandlerBase(const TSharedRef<FGenericApplicationMessageHandler>& InTargetMessageHandler, FScreenReaderBase& InOwningScreenReader);`
- L22 _public prototype_ `virtual ~FScreenReaderApplicationMessageHandlerBase() = default;`
- L25 _public function_ `bool ShouldProcessMouseInput() const` — Returns true if mouse events should be processed. Else returns false.
- L27 _public function_ `void SetProcessMouseInput(bool bInProcessMouseInput)` — Sets whether mouse events should be intercepted and processed. If false, the mouse events will bubble straight down to the target message handler.
- L30 _public function_ `bool ShouldProcessKeyInput() const` — Retursn true if the key inputs should be intercepted and processed. Else returns false.
- L32 _public function_ `void SetProcessKeyInput(bool bInProcessKeyInput)` — Sets whether key inputs should be intercepted and processed. If set to false, the key inputs will ubble straight down to the target message handler.
- L35 _public function_ `TSharedRef<FGenericApplicationMessageHandler> GetTargetMessageHandler() const` — Returns the underlying message handler that application messages bubble down to if the screen reader application message handler does not handle the event.
- L41 _public prototype_ `virtual bool ShouldProcessUserInputMessages(const TSharedPtr< FGenericWindow >& PlatformWindow) const override;` — FGenericApplicationMessageHandler By default all the following functions just forward the call to the underlying message handler. Child classes should only override functions where they want to intercept the message first and perform pre-processing or handling @see TargetMessageHandler
- L42 _public prototype_ `virtual bool OnKeyChar(const TCHAR Character, const bool IsRepeat) override;`
- L43 _public prototype_ `virtual bool OnKeyDown(const int32 KeyCode, const uint32 CharacterCode, const bool IsRepeat) override;`
- L44 _public prototype_ `virtual bool OnKeyUp(const int32 KeyCode, const uint32 CharacterCode, const bool IsRepeat) override;`
- L45 _public prototype_ `virtual bool OnMouseDown(const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button) override;`
- L46 _public prototype_ `virtual bool OnMouseDown(const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button, const FVector2D CursorPos) override;`
- L47 _public prototype_ `virtual bool OnMouseUp(const EMouseButtons::Type Button) override;`
- L48 _public prototype_ `virtual bool OnMouseUp(const EMouseButtons::Type Button, const FVector2D CursorPos) override;`
- L49 _public prototype_ `virtual bool OnMouseDoubleClick(const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button) override;`
- L50 _public prototype_ `virtual bool OnMouseDoubleClick(const TSharedPtr< FGenericWindow >& Window, const EMouseButtons::Type Button, const FVector2D CursorPos) override;`
- L51 _public prototype_ `virtual bool OnMouseWheel(const float Delta) override;`
- L52 _public prototype_ `virtual bool OnMouseWheel(const float Delta, const FVector2D CursorPos) override;`
- L53 _public prototype_ `virtual bool OnMouseMove() override;`
- L54 _public prototype_ `virtual bool OnRawMouseMove(const int32 X, const int32 Y) override;`
- L55 _public prototype_ `virtual bool OnCursorSet() override;`
- L56 _public prototype_ `virtual bool OnControllerAnalog(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, float AnalogValue) override;`
- L57 _public prototype_ `virtual bool OnControllerButtonPressed(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, bool IsRepeat) override;`
- L58 _public prototype_ `virtual bool OnControllerButtonReleased(FGamepadKeyNames::Type KeyName, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId, bool IsRepeat) override;`
- L59 _public prototype_ `virtual void OnBeginGesture() override;`
- L60 _public prototype_ `virtual bool OnTouchGesture(EGestureEvent GestureType, const FVector2D& Delta, float WheelDelta, bool bIsDirectionInvertedFromDevice) override;`
- L61 _public prototype_ `virtual void OnEndGesture() override;`
- L62 _public prototype_ `virtual bool OnTouchStarted(const TSharedPtr< FGenericWindow >& Window, const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId) override;`
- L63 _public prototype_ `virtual bool OnTouchMoved(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId) override;`
- L64 _public prototype_ `virtual bool OnTouchEnded(const FVector2D& Location, int32 TouchIndex, int32 ControllerId) override;`
- L65 _public prototype_ `virtual bool OnTouchForceChanged(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId) override;`
- L66 _public prototype_ `virtual bool OnTouchFirstMove(const FVector2D& Location, float Force, int32 TouchIndex, int32 ControllerId) override;`
- L67 _public prototype_ `virtual void ShouldSimulateGesture(EGestureEvent Gesture, bool bEnable) override;`
- L68 _public prototype_ `virtual bool OnMotionDetected(const FVector& Tilt, const FVector& RotationRate, const FVector& Gravity, const FVector& Acceleration, int32 ControllerId) override;`
- L69 _public prototype_ `virtual bool OnSizeChanged(const TSharedRef< FGenericWindow >& Window, const int32 Width, const int32 Height, bool bWasMinimized = false) override;`
- L70 _public prototype_ `virtual void OnOSPaint(const TSharedRef<FGenericWindow>& Window) override;`
- L71 _public prototype_ `virtual FWindowSizeLimits GetSizeLimitsForWindow(const TSharedRef<FGenericWindow>& Window) const override;`
- L72 _public prototype_ `virtual void OnResizingWindow(const TSharedRef< FGenericWindow >& Window) override;`
- L73 _public prototype_ `virtual bool BeginReshapingWindow(const TSharedRef< FGenericWindow >& Window) override;`
- L74 _public prototype_ `virtual void FinishedReshapingWindow(const TSharedRef< FGenericWindow >& Window) override;`
- L75 _public prototype_ `virtual void HandleDPIScaleChanged(const TSharedRef< FGenericWindow >& Window) override;`
- L76 _public prototype_ `virtual void OnMovedWindow(const TSharedRef< FGenericWindow >& Window, const int32 X, const int32 Y) override;`
- L77 _public prototype_ `virtual bool OnWindowActivationChanged(const TSharedRef< FGenericWindow >& Window, const EWindowActivation ActivationType) override;`
- L78 _public prototype_ `virtual bool OnApplicationActivationChanged(const bool IsActive) override;`
- L79 _public prototype_ `virtual bool OnConvertibleLaptopModeChanged() override;`
- L80 _public prototype_ `virtual EWindowZone::Type GetWindowZoneForPoint(const TSharedRef< FGenericWindow >& Window, const int32 X, const int32 Y) override;`
- L81 _public prototype_ `virtual void OnWindowClose(const TSharedRef< FGenericWindow >& Window) override;`
- L82 _public prototype_ `virtual EDropEffect::Type OnDragEnterText(const TSharedRef< FGenericWindow >& Window, const FString& Text) override;`
- L83 _public prototype_ `virtual EDropEffect::Type OnDragEnterFiles(const TSharedRef< FGenericWindow >& Window, const TArray< FString >& Files) override;`
- L84 _public prototype_ `virtual EDropEffect::Type OnDragEnterExternal(const TSharedRef< FGenericWindow >& Window, const FString& Text, const TArray< FString >& Files) override;`
- L85 _public prototype_ `virtual EDropEffect::Type OnDragOver(const TSharedPtr< FGenericWindow >& Window) override;`
- L86 _public prototype_ `virtual void OnDragLeave(const TSharedPtr< FGenericWindow >& Window) override;`
- L87 _public prototype_ `virtual EDropEffect::Type OnDragDrop(const TSharedPtr< FGenericWindow >& Window) override;`
- L88 _public prototype_ `virtual bool OnWindowAction(const TSharedRef< FGenericWindow >& Window, const EWindowAction::Type InActionType) override;`
- L98 _protected member_ `FScreenReaderBase& OwningScreenReader;` — The screen reader that owns this screen reader application message handler. The lifetime of the screen reader message handler follows its owning screen reader. The owning screen reader can be used to retrieve screen reader users to request accessible services such as requesting nnouncements be spoken or to handle accessible events. @see FScreenReaderBase
- L101 _private member_ `TSharedRef<FGenericApplicationMessageHandler> TargetMessageHandler;` — The underlying message handler that application messages will bubble down to if the screen reader applicaiton message handler does not consume or handle the app.application messages.
- L103 _private member_ `bool bProcessMouseInput;` — True if the screen reader application message handler should process mouse input. Else false.
- L105 _private member_ `bool bProcessKeyInput;` — True if the screen reader application message handler should process key inputs. Else false.

### `Plugins/Experimental/ScreenReader/Source/ScreenReader/Public/GenericPlatform/ScreenReaderBase.h` (Public)


#### class `FScreenReaderBase`  
`class FScreenReaderBase`  
_L22-118_
- desc: The abstract base class all screen readers must derive from. The screen reader sets up and tears down the screen reader framework with Activate() and Deactivate() respectively. When active, the screen reader will intercept all application messages, perform necessary input pre-processing and dispatch the accessible events and inputs to all registered screen reader users. Users of derived classes must activate the screen reader to ensure the accessible inputs and accessible events are dispatched properly. Derived classes must implement the pure virtual OnAccessibleEventRaised function to handle accessible events. @see FScreenReaderUser
- L25 _public prototype_ `FScreenReaderBase() = delete;`
- L26 _public prototype_ `explicit FScreenReaderBase(const TSharedRef<GenericApplication>& InPlatformApplication);`
- L28 _public prototype_ `FScreenReaderBase(const FScreenReaderBase& Other) = delete;` — We disallow copying
- L29 _public prototype_ `FScreenReaderBase& operator=(const FScreenReaderBase& Other) = delete;`
- L30 _public prototype_ `virtual ~FScreenReaderBase();`
- L32 _public function_ `void SetScreenReaderApplicationMessageHandler(const TSharedRef<FScreenReaderApplicationMessageHandlerBase>& InScreenReaderApplicationMessageHandler)`
- L39 _public prototype_ `void Activate();` — Activates the screen reader and sets up the screen reader framework if the screen reader is inactive. Once this is called, the screen reader can intercept application messages, perform input pre-processing and dispatch accessibility events to the registered screen reader users. OnActivated() is called at the end of the function. Users can override the function to perform additional setup. @see OnActivated()
- L46 _public prototype_ `void Deactivate();` — Deactivates the screen reader and tears down the screen reading framework if the screen reader is active. The screen reader will no longer intercept application input messages and no accessible events will be dispatched to the registered screen reader users. OnDeactivated() is called at the start of this function. Users can override the function to perform additional teardown. @see OnDeactivated()
- L48 _public function_ `bool IsActive() const` — Returns true if the screen reader is active. Else false.
- L54 _public prototype_ `bool RegisterUser(int32 InUserId);` — Registers a provided user Id to the screen reader framework and allows the user to receive and respond to accessible events and accessible input. Does nothing if the passed in Id is already registered. @ return Returns true if the Id is successfully registered with the screen reader. Else returns false.
- L61 _public prototype_ `bool UnregisterUser(int32 InUserId);` — Unregisters a provided user Id from the screen reader framework and deactivates the user. The unregistered user will no longer receive or respond to accessible events and input. Nothing will happen if the provided user Id has not been registered with the screen reader. @param InUserId The user Id to unregister from the screen reader framework. @return Returns true if the provided user Id has been successfully unregistered. Else returns false.
- L66 _public prototype_ `bool IsUserRegistered(int32 InUserId) const;` — Returns true if the passed in user Id is already registered. Else returns false. @param InUserId The user Id to check for registration.
- L68 _public prototype_ `void UnregisterAllUsers();` — Unregisteres all screen reader users. No users can receive or respond to accessible events or accessible input upon calling this function.
- L75 _public prototype_ `TSharedRef<FScreenReaderUser> GetUserChecked(int32 InUserId) const;` — Returns the screen reader user associated with the passed in Id. An assertion will trigger if the User Id is not registered. It is up to the user to ensure that the Id is valid and mapped to a valid screen reader user. @param InUserId The Id of the screen reader user to be retrieved. @return The screen reader user associated with the passed in Id
- L81 _public prototype_ `TSharedPtr<FScreenReaderUser> GetUser(int32 InUserId) const;` — Returns a screen reader user associated with the passed in Id if the Id is registered. Otherwise, a nullptr is returned. @param InUserId The user Id of the screen reader to be retrieved. @return The screen reader user associated with the Id if the user is registered. Else nullptr.
- L89 _protected function_ `virtual void OnActivate()` — Called at the end of Activate(). Override this function in child classes to do additional set up such as subscribing to accessible events, binding handlers for focus events or providing feedback to users that the screen reader has been activated.
- L94 _protected function_ `virtual void OnDeactivate()` — Called at the start of Deactivate(). Override this function in child classes to provide additional teardown such as unsubscribing from accessible events or providing feedback to alert the user that the screen reader is deactivated.
- L101 _protected prototype_ `virtual void OnAccessibleEventRaised(const FAccessibleEventArgs& Args) = 0;` — The handler for all accessible events raised from FGenericAccessibleMessageHandler. Is bound to the accessible event delegate in FGenericAccessibleMessageHandler. This handler is bound during activation and unbound during deactivation. A sample implementation can be found in FSlateScreenReader. @see FSlateScreenReader
- L103 _protected function_ `TWeakPtr<GenericApplication> GetPlatformApplicationWeak() const` — Returns the weak pointer to the platform application. Use this to access the accessible message handler and or retrieve cursor information.
- L113 _private member_ `TSharedRef<FScreenReaderApplicationMessageHandlerBase> ScreenReaderApplicationMessageHandler;` — The screen reader's application message handler. It processes input events before passing them down to the target application message handler @see FScreenReaderApplicationMessageHandlerBase
- L115 _private member_ `TWeakPtr<GenericApplication> PlatformApplication;` — The platform application. Used to access the accessible message handler and swap the application message handler with the screen reader application message handler.
- L117 _private member_ `bool bActive;` — True if the screen reader is active. Else false.

### `Plugins/Experimental/ScreenReader/Source/ScreenReader/Public/GenericPlatform/ScreenReaderReply.h` (Public)


#### struct `FScreenReaderReply`  
`struct FScreenReaderReply`  
_L13-42_
- reflection: `USTRUCT(BlueprintType)`
- desc: A struct passed around the the screen reader framework to indicate if a request has been successfully handled. Use this class to determine if a request to the screen reader user was successfully handled and provide user feedback accordingly. // @TODOAccessibility: Provide examples @see FScreenReaderUser
- L17 _public prototype_ `FScreenReaderReply() = default;`
- L18 _public prototype_ `~FScreenReaderReply() = default;`
- L20 _public function_ `static FScreenReaderReply Handled()`
- L25 _public function_ `static FScreenReaderReply Unhandled()`
- L30 _public function_ `bool IsHandled() const`
- L35 _private function_ `FScreenReaderReply(bool bInHandled) : bHandled(bInHandled)`
- L41 _private member_ `bool bHandled = false;` — `UPROPERTY(BlueprintReadOnly, Category=ScreenReaderReply, meta=(AllowPrivateAccess = "true"))`

### `Plugins/Experimental/ScreenReader/Source/ScreenReader/Public/GenericPlatform/ScreenReaderUser.h` (Public)


#### class `FScreenReaderUser`  
`class FScreenReaderUser : public FGenericAccessibleUser`  
_L25-158_
- inherits: `FGenericAccessibleUser`
- desc: A user of the screen reader. Corresponds to a hardware device that users use. This class is a facade that acts as a one stop shop for all screen reading services on a per user basis. Multiple screen reader users can exist simultaneoulsy to facilitate local multiplayer and users can opt in or out of receiving screen reader feedback by registering and unregistering with the screen reader respectively. A screen user is inactive by default when it is first registered through the screen reader. Users must explicitly activate the screen reader user after successful registration with the screen reader to use its services. Responsibilities of the class are: 1. Text to speech (TTS) requests - Users can request an announcement to be spoken via text to speech to  screen reader user 2. Accessible focus handling - A screen reader user holds information about the accessible widget it is currently focused on 3. Accessible Navigation - Screen reader users have finer navigation controls around the accessible widget hierarchy as compared to regular tab navigation with keyboard or D-pad controls with a gamepad. @see FScreenReaderBase, FScreenReaderAnnouncement, FGenericAccessibleUser
- L28 _public prototype_ `explicit FScreenReaderUser(FAccessibleUserIndex InUserIndex);`
- L29 _public prototype_ `~FScreenReaderUser();`
- L52 _public prototype_ `FScreenReaderReply RequestSpeak(FScreenReaderAnnouncement InAnnouncement);` — Requests an announcement to be spoken to the screen reader user. This is the main mechanism to provide text to speech auditory feedback to users. Calling this function does not guarantee that the announcement will be spoken via text to speech and be heard by a user. All announcements spoken via text to speech will be asynchronous and iwll not block the game thread. If the screen reader user is active and no announcements are currently spoken, the announcement will be spoken immediately. If another announcement is currently being spoken, the passed in announcement could be queued or interrupt the currently spoken announcement. Examples: TSharedRef<FScreenReaderUser> MyUser = ScreenReader->GetUser(MyScreenReaderUserIndex); // All announcements to be spoken should be localized to provide language support for the text to speech system. static const FText MyText = LOCTEXT("ExampleUserFeedback", "Feedback to user."); // This makes the announcement interrupt any currently spoken announcement with lower priority and is played immediately. The announcement will be uninterruptable and guarantees the user will hear the announcement. // Use this sparingly for only critical information that the user needs to hear such as registration to the screen reader or important in game events. MyUser->RequestSpeak(FScreenReaderAnnouncement(MyText.ToString(), FScreenReaderAnnouncementInfo::Important())); // This makes the announcement a feedback for a user action or event. It is interruptable. // Use
- L58 _public prototype_ `FScreenReaderReply StopSpeaking();` — Immediately stops speaking any currently spoken announcement. Does nothing if there is no announcement currently being spoken. @return FScreenReader::Handled() if the request to stop speaking is successfully processed. Else returns FScreenReaderReply::Unhandled()
- L60 _public prototype_ `bool IsSpeaking() const;` — Returns true if an announcement is currently being spoken. Else returns false.
- L67 _public prototype_ `FScreenReaderReply RequestSpeakWidget(const TSharedRef<IAccessibleWidget>& InWidget);` — Requests the information about an accessibility widget to be read out to a user. The same guarantees about the announcement being spoken in RequestSpeak() apply for this function. @param InWidget The widget to ahve its contents spoken to a user. @return FScreenReaderReply::Handled() if the widget's information is successfully spoken. Else returns FScreenReaderReply::Unhandled();
- L69 _public prototype_ `float GetSpeechVolume() const;` — Returns the speech volume for text to speech. Value will be between 0.0f and 1.0f.
- L74 _public prototype_ `FScreenReaderReply SetSpeechVolume(float InVolume);` — Sets the speech volume for text to speech to speak at. The passed in value will be clamped between 0.0f and 1.0f. @return FScreenReaderReply::Handled() if the volume is successfully set. Else FScreenReader::Unhandled() is returned.
- L76 _public prototype_ `float GetSpeechRate() const;` — Returns the speech rate text to speech is speaking at for this user. Value will be between 0.0f and 1.0f.
- L81 _public prototype_ `FScreenReaderReply SetSpeechRate(float InRate);` — Sets the speech rate text to speech will speak at for this user. Passed in value is clamped between 0.0f and 1.0f. @return FScreenReaderReply::Handled() if the speech rate is successfully set. Else, FScreenReaderReply::Unhandled() is returned.
- L86 _public prototype_ `FScreenReaderReply MuteSpeech();` — Mutes the text to speech for this user so requests to speak strings will be inaudible. @return FScreenReaderReply::Handled() if the text to speech is successfully muted. Else, FScreenReaderReply::Unhandled() is returned.
- L91 _public prototype_ `FScreenReaderReply UnmuteSpeech();` — Unmutes the text to speech for this user so that requests to speak strings will be audible again. @return FScreenReaderReply::Handled() if the text to speech si successfully unmuted. Else, FScreenReaderReply::Unhandled() is returned.
- L93 _public prototype_ `bool IsSpeechMuted() const;` — Returns true if the text to speech for this user is muted. Else returns false.
- L98 _public prototype_ `void SetNavigationPolicy(const TSharedRef<IScreenReaderNavigationPolicy>& InNavigationPolicy);` — Sets the navigation policy this screen reader user will be using. The screen reader navigation policy will affect all functionality to do with shifting focus to the next available widget.
- L103 _public prototype_ `FScreenReaderReply NavigateToNextSibling();` — Shifts focus to the next sibling from the user's currently focused accessible widget based on the current navigation policy. @return FScreenReaderReply::Handled() if focus has successfully shifted to a next sibling from the currently focused accessible widget. Else returns FScreenReaderReply::Unhandled()
- L108 _public prototype_ `FScreenReaderReply NavigateToPreviousSibling();` — Shifts focus to the previous sibling from the user's currently focused accessible widget based on the current navigation policy. @return FScreenReaderReply::Handled() if focus has successfully shifted to a previous sibling from the currently focused accessible widget. Else returns FScreenReaderReply::Unhandled()
- L113 _public prototype_ `FScreenReaderReply NavigateToFirstAncestor();` — Shifts focus to the first ancestor of the user's currently focused accessible widget based on the current navigation policy. @return FScreenReaderReply::Handled() if focus has successfully shifted to the first ancestor of the currently focused accessible widget. Else returns FScreenReaderReply::Unhandled()
- L119 _public prototype_ `FScreenReaderReply NavigateToFirstChild();` — Shifts focus to the first child from the user's currently focused accessible widget based on the current navigation policy. Focus is unaffected if the user's currently focused accessible widget has no children. @return FScreenReaderReply::Handled() if focus has successfully shifted to the first child from the currently focused accessible widget based on the navigation policy. Else returns FScreenReaderReply::Unhandled()
- L125 _public prototype_ `FScreenReaderReply NavigateToNextWidgetInHierarchy();` — Shifts focus to the logical next widget in the accessible widget hierarchy from the user's currently focused accessible widget based on the current navigation policy. See IAccessibleWidget::GetNextWidgetInHierarchy for an explanation of what the logical next widget in the accessible hierarchy means. @return FScreenReaderReply::Handled() if focus has successfully shifted to a next widget from the currently focused accessible widget. Else returns FScreenReaderReply::Unhandled()
- L131 _public prototype_ `FScreenReaderReply NavigateToPreviousWidgetInHierarchy();` — Shifts focus to the logical previous widget in the accessible widget hierarchy from the user's currently focused accessible widget based on the current navigation policy. See IAccessibleWidget::GetPreviousWidgetInHierarchy for an explanation of what the logical previous widget in the accessible hierarchy means. @return FScreenReaderReply::Handled() if focus has successfully shifted to a logical previous widget from the currently focused accessible widget. Else returns FScreenReaderReply::Unhandled()
- L136 _public prototype_ `void Activate();` — Activates the screen reader user and fulfill requests for accessibility services such as text to speech that clients can make. When screen reader users are firstr registered with a screen reader, they are deactivated by default. Users must explicitly activate the screen reader user.
- L141 _public prototype_ `void Deactivate();` — Deactivates the screen reader and disables all announcement and text to speech services making them do nothing.
- L143 _public function_ `bool IsActive() const` — Returns true if the screen reader user is active. Else returns false.
- L150 _protected prototype_ `virtual void OnUnregistered() override;`
- L155 _private member_ `TUniquePtr<FScreenReaderAnnouncementChannel> AnnouncementChannel;` — Responsible for handling all incoming announcement requests and speaking them via text to speech if possible
- L156 _private member_ `TSharedRef<IScreenReaderNavigationPolicy> NavigationPolicy;`
- L157 _private member_ `bool bActive;`

### `Plugins/Experimental/ScreenReader/Source/ScreenReader/Public/Navigation/ScreenReaderNavigationPolicy.h` (Public)


#### class `IScreenReaderNavigationPolicy`  
`class IScreenReaderNavigationPolicy`  
_L14-38_
- desc: An interface that controls how a screen reader user navigates around the accessible widget hierarchy and what accessible widgets can be navigated to from a source widget. Clients can provide custom implementations to provide different navigation behaviors for screen reader users at runtime. A sample implementation is FDefaultScreenReaderNavigationPolicy. @see FScreenReaderUser, FDefaultScreenReaderNavigaitonPolicy
- L17 _public prototype_ `virtual ~IScreenReaderNavigationPolicy() = default;`
- L19 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetNextSiblingFrom(const TSharedRef<IAccessibleWidget>& Source) const = 0;` — Returns the first instance of a next sibling from the source widget that satisfies the navigation policy.
- L21 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetPreviousSiblingFrom(const TSharedRef<IAccessibleWidget>& Source) const = 0;` — Returns the first instance of a previous sibling from the source widget that satisfies the navigation policy.
- L23 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetFirstAncestorFrom(const TSharedRef<IAccessibleWidget>& Source) const = 0;` — Returns the first ancestor from the source widget that satisfies the navigation policy.
- L25 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetFirstChildFrom(const TSharedRef<IAccessibleWidget>& Source) const = 0;` — Returns the first child from the source widget that satisfies the navigation policy.
- L31 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetNextWidgetInHierarchyFrom(const TSharedRef<IAccessibleWidget>& Source) const = 0;` — Returns the first instance of a logical next widget from the source widget that satisfies the navigation policy. See IAccessibleWidget::GetNextWidgetInHierarchy for an explanation of what the logical next widget in the accessible hierarchy means. @see IAccessibleWidget
- L37 _public prototype_ `virtual TSharedPtr<IAccessibleWidget> GetPreviousWidgetInHierarchyFrom(const TSharedRef<IAccessibleWidget>& Source) const = 0;` — Returns the first instance of a logical previous widget from the source widget that satisfies the navigation policy. See IAccessibleWidget::GetPreviousWidgetInHierarchy for an explanation of what the logical previous widget in the accessible hierarchy means. @see IAccessibleWidget

#### class `FScreenReaderDefaultNavigationPolicy`  
`class FScreenReaderDefaultNavigationPolicy final : public IScreenReaderNavigationPolicy`  
_L40-77_
- inherits: `IScreenReaderNavigationPolicy`
- L50 _public prototype_ `virtual ~FScreenReaderDefaultNavigationPolicy() = default;`
- L52 _public function_ `virtual TSharedPtr<IAccessibleWidget> GetNextSiblingFrom(const TSharedRef<IAccessibleWidget>& Source) const override final`
- L56 _public function_ `virtual TSharedPtr<IAccessibleWidget> GetPreviousSiblingFrom(const TSharedRef<IAccessibleWidget>& Source) const override final`
- L60 _public function_ `virtual TSharedPtr<IAccessibleWidget> GetFirstAncestorFrom(const TSharedRef<IAccessibleWidget>& Source) const override final`
- L64 _public function_ `virtual TSharedPtr<IAccessibleWidget> GetFirstChildFrom(const TSharedRef<IAccessibleWidget>& Source) const override final`
- L68 _public function_ `virtual TSharedPtr<IAccessibleWidget> GetNextWidgetInHierarchyFrom(const TSharedRef<IAccessibleWidget>& Source) const override final`
- L72 _public function_ `virtual TSharedPtr<IAccessibleWidget> GetPreviousWidgetInHierarchyFrom(const TSharedRef<IAccessibleWidget>& Source) const override final`

#### struct `FScreenReaderDefaultNavigationPolicy::FScreenReaderDefaultNavigationPredicate`  
`struct FScreenReaderDefaultNavigationPredicate`  
_L43-49_
- L45 _public function_ `bool operator()(const TSharedRef<IAccessibleWidget>& InWidget) const`
