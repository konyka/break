# Plugins / PixelStreamingVCam

- module root: `Plugins/VirtualProduction/VirtualCameraCore/Source/PixelStreamingVCam`
- headers: 13; symbols: 196
- symbol kinds: class=13, delegate=2, enum=2, enumerator=6, function=15, member=42, namespace=16, prototype=99, struct=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, DecoupledOutputProvider, DiscoveryBeaconReceiver, Engine, InputCore, Json, LevelEditor, LiveLinkInterface, Networking, PixelCapture, PixelStreamingEditor, PixelStreamingInput, Projects, RHI, SceneOutliner, Slate, SlateCore, UMG, UnrealEd, ViewportWidgetOverlay
- PublicDependencyModuleNames: InputDevice, MediaIOCore, PixelStreaming, PixelStreamingServers, VCamCore

### `Plugins/VirtualProduction/VirtualCameraCore/Source/PixelStreamingVCam/Private/LiveLink/LiveLinkManager.h` (Private)


#### class `UE::PixelStreamingVCam::FLiveLinkManager`  
`class FLiveLinkManager : public FNoncopyable`  
_L13-41_
- inherits: `FNoncopyable`
- desc: Manages the live link subjects for the UVCamPixelStreamingSession.
- L18 _public prototype_ `void CreateOrRefreshSubjectFor(const UVCamPixelStreamingSession& Session);` — If Live Link is enabled, creates a live link subject (if not already) and sets its name to the StreamerId of Session.
- L20 _public prototype_ `void DestroySubjectFor(const UVCamPixelStreamingSession& Session);` — If a subject is associated with Session, destroys it.
- L23 _public prototype_ `void PushTransformForSubject(const UVCamPixelStreamingSession& Session, const FTransform& Transform, double Timestamp);` — Pushes transform data for the given Session.
- L28 _private member_ `TSharedPtr<FPixelStreamingLiveLinkSource> LiveLinkSource;` — Holds all the live link subjects for Pixel Streaming. Created when the first subject is created.
- L37 _private member_ `TMap<TWeakObjectPtr<const UVCamPixelStreamingSession>, FStreamingSessionData> SessionData;` — Maps the last subject names used by each session, so it can be cleaned up.
- L40 _private prototype_ `FPixelStreamingLiveLinkSource* GetOrCreateLiveLinkSource();` — Inits LiveLinkSource if not yet created.

#### struct `UE::PixelStreamingVCam::FLiveLinkManager::FStreamingSessionData`  
`struct FStreamingSessionData`  
_L30-34_
- L33 _public member_ `FName LastSubjectName;` — The last subject name used by the associated UVCamPixelStreamingSession.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreamingVCam` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/PixelStreamingVCam/Private/LiveLink/VCamPixelStreamingLiveLink.h` (Private)


#### class `UPixelStreamingLiveLinkSourceSettings`  
`class UPixelStreamingLiveLinkSourceSettings : public ULiveLinkSourceSettings`  
_L10-16_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceSettings`
- L15 _public prototype_ `UPixelStreamingLiveLinkSourceSettings();`

#### class `FPixelStreamingLiveLinkSource`  
`class FPixelStreamingLiveLinkSource : public ILiveLinkSource, public FNoncopyable`  
_L18-67_
- inherits: `ILiveLinkSource,FNoncopyable`
- L22 _public prototype_ `FPixelStreamingLiveLinkSource();`
- L26 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;`
- L27 _public prototype_ `virtual void Update() override;`
- L28 _public prototype_ `virtual bool CanBeDisplayedInUI() const override;`
- L29 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L30 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L31 _public prototype_ `virtual FText GetSourceType() const override;`
- L32 _public prototype_ `virtual FText GetSourceMachineName() const override;`
- L33 _public prototype_ `virtual FText GetSourceStatus() const override;`
- L35 _public function_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const override` — Override the settings class to allow us to customize the default values
- L40 _public prototype_ `void CreateSubject(FName SubjectName);` — Registers a new subject with the Transform Role to the Live Link Client If called with a subject name that already exists in this source then this will reset any buffered data for that subject
- L41 _public prototype_ `void RemoveSubject(FName SubjectName);`
- L42 _public prototype_ `void PushTransformForSubject(FName SubjectName, FTransform Transform);`
- L43 _public prototype_ `void PushTransformForSubject(FName SubjectName, FTransform Transform, double Timestamp);`
- L48 _private member_ `ILiveLinkClient* LiveLinkClient;` — Cached information for communicating with the live link client.
- L49 _private member_ `FGuid SourceGuid;`
- L50 _private member_ `uint64 NTransformsPushed = 0;`
- L51 _private member_ `uint64 LastTransformGraphedCycles = 0.0f;`
- L63 _private member_ `TArray<FName> PendingSubjectsToCreate;` — Subjects to create at the end of the frame. CreateSubject uses PushSubjectStaticData_AnyThread, which is processed latently by LiveLink; once processed, the subject appears in the UI. RemoveSubject uses RemoveSubject_AnyThread has, which an immediate effect. If PushSubjectStaticData_AnyThread is immediately followed by RemoveSubject_AnyThread, which happens if CreateSubject and RemoveSubject are called in the same frame, the subject technically does not exist internally in LiveLink, yet. To solve this, we check at the end of the frame whether the API user wants a subject to exist this frame or not.
- L65 _private function_ `void OnEndOfFrame()`
- L66 _private prototype_ `void ProcessEndOfFrameSubjectCreation();`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/PixelStreamingVCam/Private/Media/PixelStreamingMediaOutput.h` (Private)


#### class `UPixelStreamingMediaOutput`  
`class UPixelStreamingMediaOutput : public UMediaOutput`  
_L13-52_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMediaOutput`
- L19 _public function_ `virtual FIntPoint GetRequestedSize() const override`
- L20 _public function_ `virtual EPixelFormat GetRequestedPixelFormat() const override`
- L21 _public function_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override`
- L23 _public prototype_ `virtual void BeginDestroy() override;`
- L26 _protected prototype_ `virtual UMediaCapture* CreateMediaCaptureImpl() override;`
- L30 _public prototype_ `static UPixelStreamingMediaOutput* Create(UObject* Outer, const FString& StreamerId);`
- L32 _public function_ `bool IsValid() const`
- L33 _public function_ `TSharedPtr<IPixelStreamingStreamer> GetStreamer() const`
- L35 _public prototype_ `void StartStreaming();`
- L36 _public prototype_ `void StopStreaming();`
- L38 _public function_ `DECLARE_EVENT_OneParam(UPixelStreamingMediaOutput, FRemoteResolutionChangedEvent, const FIntPoint&) FRemoteResolutionChangedEvent& OnRemoteResolutionChanged()`
- L42 _private member_ `TSharedPtr<IPixelStreamingStreamer> Streamer;`
- L45 _private member_ `FRemoteResolutionChangedEvent RemoteResolutionChangedEvent;` — Broadcasts whenever the layer changes
- L47 _private prototype_ `void OnCaptureStateChanged();`
- L48 _private prototype_ `void OnCaptureViewportInitialized();`
- L51 _private prototype_ `void RegisterRemoteResolutionCommandHandler();` — When the remote device sends a resolution change request back to the VCam we can respond here.

#### Free symbols / members of external scopes

- L38 _delegate_ `DECLARE_EVENT_OneParam(UPixelStreamingMediaOutput, FRemoteResolutionChangedEvent, const FIntPoint&) FRemoteResolutionChangedEvent& OnRemoteResolutionChanged() { return RemoteResolutionChangedEvent; } private: TSharedPtr<IPixelStreamingStreamer> Streamer;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/PixelStreamingVCam/Private/Media/PixelStreamingVideoInputVCam.h` (Private)


#### class `FPixelStreamingVideoInputVCam`  
`class FPixelStreamingVideoInputVCam : public FPixelStreamingVideoInputRHI`  
_L10-23_
- inherits: `FPixelStreamingVideoInputRHI`
- desc: Use this if you want to send VCam output as video input.
- L13 _public prototype_ `static TSharedPtr<FPixelStreamingVideoInputVCam> Create();`
- L14 _public prototype_ `virtual ~FPixelStreamingVideoInputVCam();`
- L16 _public prototype_ `virtual FString ToString() override;`
- L19 _protected prototype_ `virtual TSharedPtr<FPixelCaptureCapturer> CreateCapturer(int32 FinalFormat, FIntPoint OutputResolution) override;`
- L22 _private prototype_ `FPixelStreamingVideoInputVCam();`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/PixelStreamingVCam/Private/Misc/CVarCountedSetter.h` (Private)


#### class `UE::PixelStreamingVCam::TCVarCountedSetter`  
`template<typename T> class TCVarCountedSetter`  
_L12-60_
- desc: Counter that while non-zero, sets the specified CVar a desired value and once it reaches zero, the CVar is reset to the previous value.
- L16 _public function_ `explicit TCVarCountedSetter(FString InName, T InDesiredValue) : Name(MoveTemp(InName)), DesiredValue(InDesiredValue)`
- L20 _public function_ `void Increment()`
- L37 _public function_ `void Decrement()`
- L55 _private member_ `const FString Name;`
- L56 _private member_ `const T DesiredValue;`
- L57 _private member_ `T RestoreValue;`
- L59 _private member_ `int32 Count = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreamingVCam` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/PixelStreamingVCam/Private/Networking/SignalingServerLifecycle.h` (Private)


#### class `UE::PixelStreamingVCam::FSignalingServerLifecycle`  
`class FSignalingServerLifecycle : public FNoncopyable`  
_L23-48_
- inherits: `FNoncopyable`
- desc: Controls the lifetime of the builtin signalling server for Pixel Streaming. Generally ensures that the server is launched when the first FVCamPixelStreamingSessionLogic launches and that it is shutdown when the last FVCamPixelStreamingSessionLogic shuts down. If the server was already running before the first FVCamPixelStreamingSessionLogic was launched, it stays alive. This logic does not handle the case of when the server is lost during streaming and manually relaunched. It will either shutdown or keep the server alive depending on whether there was one running before the first session started.
- L27 _public prototype_ `FSignalingServerLifecycle(UVCamPixelStreamingSubsystem& Subsystem UE_LIFETIMEBOUND);`
- L30 _public prototype_ `void LaunchSignallingServerIfNeeded(UVCamPixelStreamingSession& Session);` — Called when a streamer requires a signalling server.
- L32 _public prototype_ `void StopSignallingServerIfNeeded(UVCamPixelStreamingSession& Session);` — Called when a
- L37 _private member_ `UVCamPixelStreamingSubsystem& Subsystem;` — Notifies us when a VCam session starts / stops.
- L47 _private member_ `} LifecycleState = ELifecycleState::NoClients;`

#### enum `UE::PixelStreamingVCam::FSignalingServerLifecycle::ELifecycleState`  
`enum class ELifecycleState`  
_L39-47_
- L42 _public enumerator_ `NoClients` — There's nobody streaming and the server is no longer managed by us.
- L44 _public enumerator_ `ShutdownOnLastSession` — We manually launched a server for VCam. Shut it down when the last session stops streaming.
- L46 _public enumerator_ `KeepAliveOnLastSession` — There was a server that had been launched before the first session started streaming. Do not shutdown the server when the last session stops streaming.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreamingVCam` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/PixelStreamingVCam/Private/Networking/VirtualCameraBeaconReceiver.h` (Private)


#### class `UE::PixelStreamingVCam::FVirtualCameraBeaconReceiver`  
`class FVirtualCameraBeaconReceiver : public FDiscoveryBeaconReceiver`  
_L13-40_
- inherits: `FDiscoveryBeaconReceiver`
- desc: Receives beacon messages from the VCAM app and replies with connection information. This allows the app to detect compatible Unreal instances on the local network and list them for the user.
- L17 _public prototype_ `FVirtualCameraBeaconReceiver();`
- L20 _public prototype_ `void SetIsStreamingReady(bool bNewValue);` — Set whether streaming should be reported to beacon senders as available.
- L23 _public prototype_ `virtual void Startup() override;`
- L26 _protected prototype_ `virtual bool GetDiscoveryAddress(FIPv4Address& OutAddress) const override;`
- L27 _protected prototype_ `virtual int32 GetDiscoveryPort() const override;`
- L28 _protected prototype_ `virtual bool MakeBeaconResponse(uint8 BeaconProtocolVersion, FArrayReader& InMessageData, FArrayWriter& OutResponseData) const override;`
- L33 _private prototype_ `FString GetFriendlyName() const;` — Get the name to report to apps searching for the engine.
- L36 _private member_ `uint32 PixelStreamingPort;` — The Pixel Streaming port with which to reply.
- L39 _private member_ `bool bIsStreamingReady = true;` — Whether streaming should be reported to beacon senders as available.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PixelStreamingVCam` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/PixelStreamingVCam/Private/Notifications/MissingSignallingServerNotifier.h` (Private)


#### class `UE::PixelStreamingVCam::FMissingSignallingServerNotifier`  
`class FMissingSignallingServerNotifier : public FNoncopyable`  
_L14-46_
- inherits: `FNoncopyable`
- desc: Displays a toaster message to the user when a signalling server is not available
- L19 _public prototype_ `FMissingSignallingServerNotifier(UVCamPixelStreamingSubsystem& Subsystem UE_LIFETIMEBOUND);`
- L20 _public prototype_ `~FMissingSignallingServerNotifier();`
- L25 _private member_ `UVCamPixelStreamingSubsystem& OwningSubsystem;` — System that created us
- L32 _private member_ `} NotificationState = ENotificationState::NotDisplayed;`
- L34 _private member_ `bool bAreNotificationsMuted = false;` — Whether the user set to not receive notifications about this anymore
- L37 _private member_ `TSharedPtr<SNotificationItem> CurrentNotification;` — The notification that was created. Used to fade it out if the server comes back online.
- L39 _private prototype_ `void DisplayNotificationIfNeeded();`
- L40 _private prototype_ `void DisplayNotification();`
- L42 _private prototype_ `void OnClickLaunch();`
- L43 _private prototype_ `void OnClickSkip();`
- L45 _private prototype_ `void CloseNotification(const FText& NewTitle, SNotificationItem::ECompletionState NewCompletionState = SNotificationItem::CS_None, const FText& Subtext = FText::GetEmpty());`

#### enum `UE::PixelStreamingVCam::FMissingSignallingServerNotifier::ENotificationState`  
`enum class ENotificationState : uint8`  
_L27-32_
- L29 _public enumerator_ `NotDisplayed`
- L30 _public enumerator_ `AwaitingUserAction`
- L31 _public enumerator_ `Displayed`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreamingVCam` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/PixelStreamingVCam/Private/PixelStreamingVCamLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreamingVCam, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreamingVCam, Log, All);`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/PixelStreamingVCam/Private/PixelStreamingVCamModule.h` (Private)


#### class `UE::PixelStreamingVCam::FPixelStreamingVCamModule`  
`class FPixelStreamingVCamModule : public IModuleInterface`  
_L14-44_
- inherits: `IModuleInterface`
- L18 _public prototype_ `static FPixelStreamingVCamModule& Get();`
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _public prototype_ `void AddActiveSession(const TWeakObjectPtr<UVCamPixelStreamingSession>& Session);` — Indicate that a VCAM pixel streaming session has become active.
- L29 _public prototype_ `void RemoveActiveSession(const TWeakObjectPtr<UVCamPixelStreamingSession>& Session);` — Indicate that a VCAM pixel streaming session has become inactive.
- L34 _private member_ `FVirtualCameraBeaconReceiver BeaconReceiver;` — Receiver that responds to beacon messages from the VCAM app.
- L37 _private member_ `TSet<TWeakObjectPtr<UVCamPixelStreamingSession>, TWeakObjectPtrSetKeyFuncs<TWeakObjectPtr<UVCamPixelStreamingSession>>> ActiveSessions;` — VCAM Pixel Streaming sessions that are currently active.
- L40 _private prototype_ `void ConfigurePixelStreaming();` — Configure CVars and session logic for Pixel Streaming.
- L43 _private prototype_ `void UpdateBeaconReceiverStreamReadiness();` — Update the beacon receiver's streaming readiness state based on the number of active sessions.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PixelStreamingVCam` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/PixelStreamingVCam/Private/PixelStreamingVCamUtil.h` (Private)


#### class `FPixelStreamingVCamUtil`  
`class FPixelStreamingVCamUtil`  
_L11-37_
- L14 _public function_ `static bool GetSignallingServerBinaryAbsPath(FString& OutPath)`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/PixelStreamingVCam/Private/VCamPixelStreamingSessionLogic.h` (Private)


#### class `UE::PixelStreamingVCam::FVCamPixelStreamingSessionLogic`  
`class FVCamPixelStreamingSessionLogic : public DecoupledOutputProvider::IOutputProviderLogic`  
_L23-128_
- inherits: `DecoupledOutputProvider::IOutputProviderLogic`
- desc: Implements logic for UVCamPixelStreamingSession so it can be loaded on all platforms.
- L27 _public prototype_ `FVCamPixelStreamingSessionLogic(const DecoupledOutputProvider::FOutputProviderLogicCreationArgs& Args);`
- L28 _public prototype_ `virtual ~FVCamPixelStreamingSessionLogic();`
- L31 _public prototype_ `virtual void OnDeinitialize(DecoupledOutputProvider::IOutputProviderEvent& Args) override;`
- L32 _public prototype_ `virtual void OnActivate(DecoupledOutputProvider::IOutputProviderEvent& Args) override;`
- L33 _public prototype_ `virtual void OnDeactivate(DecoupledOutputProvider::IOutputProviderEvent& Args) override;`
- L34 _public prototype_ `virtual VCamCore::EViewportChangeReply PreReapplyViewport(DecoupledOutputProvider::IOutputProviderEvent& Args) override;`
- L35 _public prototype_ `virtual void PostReapplyViewport(DecoupledOutputProvider::IOutputProviderEvent& Args) override;`
- L36 _public prototype_ `virtual void OnAddReferencedObjects(DecoupledOutputProvider::IOutputProviderEvent& Args, FReferenceCollector& Collector) override;`
- L37 _public prototype_ `virtual TFuture<FVCamStringPromptResponse> PromptClientForString(DecoupledOutputProvider::IOutputProviderEvent& Args, const FVCamStringPromptRequest& Request) override;`
- L39 _public prototype_ `virtual void OnPostEditChangeProperty(DecoupledOutputProvider::IOutputProviderEvent& Args, FPropertyChangedEvent& PropertyChangedEvent) override;`
- L46 _private member_ `static int NextDefaultStreamerId;` — Used to generate unique streamer IDs
- L49 _private member_ `TWeakObjectPtr<UVCamPixelStreamingSession> ManagedOutputProvider;` — The output provider being managed by this logic object.
- L52 _private member_ `FHitResult LastViewportTouchResult;` — Last time viewport was touched. Updated every tick.
- L54 _private member_ `bool bUsingDummyUMG = false;` — Whether we overwrote the widget class with the empty widget class; remember: PS needs a widget.
- L56 _private member_ `bool bOldThrottleCPUWhenNotForeground;` — Cached setting from settings object.
- L58 _private member_ `TObjectPtr<UPixelStreamingMediaOutput> MediaOutput = nullptr;`
- L59 _private member_ `TObjectPtr<UPixelStreamingMediaIOCapture> MediaCapture = nullptr;`
- L62 _private member_ `FTimerHandle ARKitResponseTimer;` — Handle for ARKit stats timer
- L63 _private member_ `size_t NumARKitEvents = 0;`
- L66 _private member_ `int32 NextStringRequestId = 0;` — The next ID to use for a string request
- L69 _private member_ `TMap<int32, TPromise<FVCamStringPromptResponse>> StringPromptPromises;` — A map from string request IDs to promises to fulfill when the corresponding request is completed
- L72 _private member_ `TOptional<FString> TransformControlHolder;` — The ID of the player holding control of the transform. If empty, no player has requested control.
- L75 _private member_ `TArray<FString> TransformControlQueue;` — Queue of connected players that have requested transform control, but not received it
- L78 _private prototype_ `void OnEditStreamId(UVCamPixelStreamingSession& This) const;`
- L79 _private prototype_ `void OnActorLabelChanged(AActor* Actor) const;`
- L81 _private prototype_ `void RefreshStreamerName(UVCamPixelStreamingSession& Session) const;`
- L83 _private prototype_ `void SetupSignallingServer(UVCamPixelStreamingSession& Session);`
- L84 _private prototype_ `void StopSignallingServer(UVCamPixelStreamingSession& Session);`
- L86 _private prototype_ `void SetupCapture(TWeakObjectPtr<UVCamPixelStreamingSession> WeakThisUObjectPtr);`
- L87 _private prototype_ `void StartCapture(TWeakObjectPtr<UVCamPixelStreamingSession> WeakThisUObjectPtr);`
- L88 _private prototype_ `void StopCapture();`
- L90 _private prototype_ `void OnPreStreaming(IPixelStreamingStreamer* PreConnectionStreamer, TWeakObjectPtr<UVCamPixelStreamingSession> WeakThisUObjectPtr);`
- L91 _private prototype_ `void StopStreaming();`
- L92 _private prototype_ `void OnStreamingStarted(IPixelStreamingStreamer* StartedStreamer, TWeakObjectPtr<UVCamPixelStreamingSession> WeakThisUObjectPtr);`
- L93 _private prototype_ `void OnStreamingStopped(IPixelStreamingStreamer* StoppedStreamer);`
- L94 _private prototype_ `void StopEverything(UVCamPixelStreamingSession& Session);`
- L96 _private prototype_ `void SetupCustomInputHandling(UVCamPixelStreamingSession* This);`
- L98 _private prototype_ `void OnCaptureStateChanged(TWeakObjectPtr<UVCamPixelStreamingSession> WeakThisUObjectPtr);`
- L99 _private prototype_ `void OnRemoteResolutionChanged(const FIntPoint& RemoteResolution, TWeakObjectPtr<UVCamPixelStreamingSession> WeakThisUObjectPtr);`
- L102 _private prototype_ `void SetupARKitResponseTimer(TWeakObjectPtr<UVCamPixelStreamingSession> WeakThisUObjectPtr);`
- L103 _private prototype_ `void StopARKitResponseTimer();`
- L106 _private prototype_ `void OnAllConnectionsClosed(FString StreamerId);` — Called when all pixel streaming connections to a streamer are closed
- L109 _private prototype_ `void OnConnectionClosed(FString StreamerId, FString PlayerId, bool bWasQualityController);` — Called when the pixel streaming connections to a streamer is closed for a player
- L112 _private prototype_ `void UnregisterPixelStreamingDelegates();` — Unregister any handlers for pixel streaming delegates
- L115 _private prototype_ `void CleanupMediaOutput();` — Sets MediaOutput to nullptr and unsubscribes from relevant delegates.
- L118 _private prototype_ `void SetTransformControlHolder(const TOptional<FString>& NewPlayerId);` — Change which player controls the transform to the one with the provided ID.
- L121 _private prototype_ `void SendTransformControlStatus(const FString& PlayerId, bool bHasControl);` — Send a message to a player indicating whether it has control of the transform.
- L127 _private prototype_ `bool TryTakeTransformControl(const FString& PlayerId, bool bForce = false);` — Return true if the player has control of the transform. If the player doesn't currently have control, take control if nobody else has it (or if bForce is true).

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DecoupledOutputProvider` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace PixelStreamingVCam` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/PixelStreamingVCam/Private/VCamPixelStreamingSubsystem.h` (Private)


#### class `UVCamPixelStreamingSubsystem`  
`class UVCamPixelStreamingSubsystem : public UEngineSubsystem`  
_L20-67_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: Keeps track of which UVCamPixelStreamingSessions are active and manages systems related to the list of active sessions.
- L26 _public prototype_ `static UVCamPixelStreamingSubsystem* Get();` — Convenience function for accessing the subsystem
- L29 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L30 _public prototype_ `virtual void Deinitialize() override;`
- L34 _public prototype_ `void RegisterActiveOutputProvider(UVCamPixelStreamingSession* OutputProvider);` — Tracks this OutputProvider creating its Live Link subject. It is valid to call this multiple times doing so updates is subject.
- L36 _public prototype_ `void UnregisterActiveOutputProvider(UVCamPixelStreamingSession* OutputProvider);` — Stops tracking this OutputProvider and clears the Live Link subject.
- L39 _public function_ `void UpdateLiveLinkSource(const UVCamPixelStreamingSession& OutputProvider) const` — Updates the live link source possibly updating its name to match the StreamerId.
- L43 _public function_ `void PushTransformForSubject(const UVCamPixelStreamingSession& OutputProvider, const FTransform& Transform, double Timestamp) const`
- L48 _public prototype_ `void LaunchSignallingServerIfNeeded(UVCamPixelStreamingSession& Session);`
- L49 _public prototype_ `void StopSignallingServerIfNeeded(UVCamPixelStreamingSession& Session);`
- L51 _public function_ `const TArray<TWeakObjectPtr<UVCamPixelStreamingSession>>& GetRegisteredSessions() const`
- L55 _private member_ `TSharedPtr<FPixelStreamingLiveLinkSource> LiveLinkSource;`
- L58 _private member_ `TArray<TWeakObjectPtr<UVCamPixelStreamingSession>> RegisteredSessions;` — The active sessions.
- L61 _private member_ `TUniquePtr<UE::PixelStreamingVCam::FMissingSignallingServerNotifier> MissingSignallingServerNotifier;` — Tells the user when the server needs manual launching.
- L63 _private member_ `TUniquePtr<UE::PixelStreamingVCam::FSignalingServerLifecycle> SignalingServerLifecycle;` — Manages the lifecycle of the signalling server.
- L66 _private member_ `TUniquePtr<UE::PixelStreamingVCam::FLiveLinkManager> LiveLinkManager;` — Manages a Live Link Source shared by all output providers.
